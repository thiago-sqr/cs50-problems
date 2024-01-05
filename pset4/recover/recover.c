#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    FILE *image;

    if (card == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    int count_files = 0;
    uint8_t buffer[BLOCK];
    char filename[8];

    while (fread(&buffer, 1, BLOCK, card) == BLOCK)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count_files != 0)
            {
                fclose(image);
            }

            sprintf(filename, "%03i.jpg", count_files);
            image = fopen(filename, "w");

            if (image == NULL)
            {
                printf("Could not create file %s", filename);
                return 2;
            }

            fwrite(&buffer, BLOCK, 1, image);
            count_files++;
        }

        else if (count_files > 0)
        {
            fwrite(&buffer, BLOCK, 1, image);
        }
    }

    if (count_files > 0)
    {
        fclose(image);
    }

    fclose(card);
}
