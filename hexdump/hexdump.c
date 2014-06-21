/*
 * hexdump
 *
 * print content of file in binary
 *
 * History:
 *
 *     v1.0  20140621  Dennis  Create
 */
#include <stdio.h>
#include <stdlib.h>

#define hd_major 1
#define hd_miner 0
#define version "hexdump version "

void print_buf(char *buf, int len)
{
	printf("\n---------------data buf: %d bytes----------------", len);
	int i=0;
	for (; i<len; i++) {
		if (i%16 == 0) printf("\n");
		else if (i%8 == 0) printf("  ");
		printf("%02x ", buf[i]&0xff); /* avoid integer type-promotion */
	}
	printf("\n-------------------------------------------------\n\n");
}


int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("%s %d.%d\n", version, hd_major, hd_miner);
        printf("Usage: %s [file]\n", argv[0]);
        return -1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Failed to open file %s.\n", argv[1]);
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    char *buf = (char*)malloc(size);
    if (!buf) {
        printf("Failed to allocate memory.\n");
        return -1;
    }
    fseek(fp, 0, SEEK_SET);
    fread(buf, sizeof(char), size, fp);
    print_buf(buf, size);
    free(buf);
    fclose(fp);
        
    return 0;
}
