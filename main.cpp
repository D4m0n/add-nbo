#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <netinet/in.h>


uint32_t get_byte_in_file(char *filename)
{
    FILE *fp;
    size_t size;
    char buffer[4] = {0,};
    uint32_t num = 0;

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "file open error.\n");
        exit(-1);
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    if (size != 4)
    {
        fprintf(stderr, "binary file is not aligned 4 bytes.\n");
        exit(-1);
    }

    fseek(fp, 0, SEEK_SET);

    fread(buffer, sizeof(uint32_t), 1, fp);

    num = ntohl(*(uint32_t *)(buffer));
    
    return num;
}


int main(int argc, char **argv)
{
    uint32_t num1, num2;

    if (argc != 3)
    {
        fprintf(stderr, "argc error.\n");
        exit(-1);
    }

    num1 = get_byte_in_file(argv[1]);
    num2 = get_byte_in_file(argv[2]);

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, num1+num2, num1+num2);
}
