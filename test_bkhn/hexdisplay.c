#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


/***
 * 1. Kiem tra co phai la file hex khong ?
 *  - Neu khong doc duoc file thi thong bao loi: "Error: <FILENAME> could not be opened"
 *  - Neu khong phai file hex thi thong bao loi va thoat chuong trinh
 *  - Neu khong la file hex thi se luu vi tri dong loi la X
 * 2. doc du lieu vao bo nho
 * 3. in noi dung ra man hinh
 *  3.1 hien thi toi das 25 dong
 *  3.2 hoi user co muon hien thi tiep khong ?
 *      - yes: xoa 25 dong truoc do va in tiep 25 dong 
 *      - no: dung chuong trinh 
 *      - neu ko phai file hex, gap dong thu X thi in ra loi khi gap dong do 
***/
char buffer[70000];
long totalChar=0;
const int MAX_LEN_LINE = 1000;


int readFile(char* filePath) {
    /***
     * Doc file vao bo nho dem buffer
     * Args:
     *  filePath (char*): duong dan file
     * 
     * Return:
     *  (int) : trang thai doc file (1 ~ thanh cong, -1 ~ error)
     * */
    FILE *fp;
    
    
    char c;
    
    fp = fopen(filePath, "r");
    if (fp == NULL) return -1;


    do {
        c = fgetc(fp);
        if (c == '\n') {
            printf("%i - enter new line\n", totalChar);
            // break;
        }
        printf("%i - %c \n", totalChar, c);
        if (c == EOF) break;
        buffer[totalChar] = c;
        totalChar++;


    } while(c != EOF);
    // printf("%s", buffer);
    printf("\nlast char: %c \n", buffer[totalChar]);
    return 1;
}

int hexCharToInt(char c)
{
/**
 * convert hext char to int
 *  0 -> 9
 *  A ~ 10, B~11,..
 */

    const int ERROR = 16;
    const int asciiNumberBetweenDigitAndAlpha = 7; // In ASCII, 7 ponctuations marks separate digits from uppercase alphabetical character
    if (c > '/' && c < ':') // In ASCII, '0' is after '/' and ':' after '9'
        return c - '0'; // In ASCII '0' = 48; '1' = 49..
    else if (c > '@' && c < 'G') // In ASCII, 'A' is after '@'
        return c - '0' - asciiNumberBetweenDigitAndAlpha;
    else
    {
        fprintf(stderr, "Not hexadecimal character, can't be parsed into a int.\n");
        return ERROR;
    }
}

int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

int* convertHexStrToHexInt(char* line, int sizeOfLine) {
    int i;
    int hexInt[MAX_LEN_LINE];

    for (i = 0; i < sizeOfLine; i++) {
        hexInt[i] = hex2int(line[i]);
    }
    return hexInt;
}


int checkHexFormat(const int* hexTab, const size_t sizeOfTab){
    /**
     *:04001c00dfff000002 =      :     |    04          | 001c        | 00             | dfff0000     | 02  
     *                      start code | byte count (2) | address (4) | record type (2)| data  (2n)   | check sum (2)  
     * 
     * line hex hop le neu 04 + 00 + 1c + 00 + df + ff + 00 + 00 = 256 -  02 
     * 
     */

    unsigned char checkSum = 0;
    for (size_t i = 0; i + 1 < sizeOfTab - 2; i += 2) // Byte by byte until checksum
    {
        printf("hex: %d\n", i, hexTab[i]);
        unsigned char currentByteValue = hexTab[i] * 16 + hexTab[i + 1];
        if (currentByteValue + checkSum < 256)
            checkSum += currentByteValue;
        else
        {
            while (currentByteValue != 0)
            {
                if (checkSum == 255)
                    checkSum = 0;
                else
                    checkSum++;
                currentByteValue--;
            }
        }
    }

    const unsigned char twoComplement = 256 - checkSum;
    const unsigned char tabCheckSum = hexTab[sizeOfTab - 2] * 16 + hexTab[sizeOfTab - 1];

    if (twoComplement == tabCheckSum)
        return 1;
    else
        return -1;
}


int main() {
    char* filePath = "Boost.X.production.hex";
    // read file, save into memory, line by line 
    int status = readFile(filePath);
    if (status == -1) {
        printf("Error: %s could not be opened", filePath);
    }
    // check hex format
    int i;
    int num_print = 0;
    int ask_print;

    printf("Num of char: %d \n", totalChar);


    for (i=0; i < totalChar+1; i++){
        char line[MAX_LEN_LINE];
        int len_line;
        int idx = 0;

        // Neu gap ky tu trang thi bo qua
        if (buffer[i] == '\0' || buffer[i] == ':') {
            printf("enter zero char\n");
            continue;
        }
        // Neu gap ky tu xuong dong thi bo qua 
        else if (buffer[i] != '\n') {
            line[idx] = buffer[i];
            idx++;

        // 
        } else if (buffer[i] == '\n') {
            len_line = idx;
            int* hex_int = convertHexStrToHexInt(line, len_line);
            int status_hex = checkHexFormat(hex_int, len_line);
            printf("Status: ", status_hex);
            if (status_hex == 1) {
                printf("line hex\n");
                num_print++;
                if (num_print % 25 == 0 && num_print != 0) {
                    printf("Ban co muon tiep tuc hien thi ? Press 1 or 2: \n1. Yes\n2. No\n");
                    scanf("%d", &ask_print);
                    if (ask_print == 2) {
                        return 0;
                    } else{
                        continue;
                    }
                }
            } else {
                printf("error hex");
                return 0;
            }
        }
        

        
        //     check hex format for that line 

        //     if number of line printed is 25, ask user

    }
    
    // print file hex 


    
}