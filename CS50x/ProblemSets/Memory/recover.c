// Recover image files
#include <stdint.h>
#include <stdio.h>

// Constants
#define BLOCKSIZE 512
#define NAMELEN 8
#define FTBYTE 0xff
#define SBYTE 0xd8
#define FBYTEL 0xe0
#define FBYTEH 0xef

// Declare for BYTE
typedef uint8_t BYTE;

// Main function
int main(int argc, char* argv[])
{
    // Check for command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover [filename]\n");
        return 1;
    }
    else
    {
        // Try to open the src file
        FILE* file = fopen(argv[1], "r");
        if (file == NULL)
        {
            printf("Cann't open the src file\n");
            return 1;
        }

        // Recover
        int image_count = 0;
        char filename[NAMELEN];
        BYTE buffer[BLOCKSIZE];
        FILE* tmp = NULL;

        while (fread(buffer, BLOCKSIZE, 1, file) > 0)
        {
            // Check the sign of jpeg
            if (buffer[0] == FTBYTE && buffer[1] == SBYTE && buffer[2] == FTBYTE &&
                (buffer[3] >= FBYTEL && buffer[3] <= FBYTEH))
            {
                // Close the previous file
                if (tmp)
                {
                    fclose(tmp);
                    tmp = NULL;
                }

                // Open a new file | %03d for format
                sprintf(filename, "%03d.jpg", image_count);
                tmp = fopen(filename, "w");
                if (tmp == NULL)
                {
                    printf("Cann't open the dst file\n");
                    return 1;
                }
                image_count++;
            }

            // If the current file is not NULL, write it
            if (tmp)
                fwrite(buffer, BLOCKSIZE, 1, tmp);
        }

        // Close the file
        fclose(tmp);
        fclose(file);
    }
}
