
#include "../../lib/cub3d.h"
#include <ctype.h>

void special_cont(const char *file_name)
{
    int fd;
    char buffer[1024];
    int bytes_read;
    int i, j, color_value;
    int color_count; // To track the number of colors

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        exit(1); // Exit immediately on error opening the file
    }

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytes_read] = '\0'; // Null-terminate the buffer
        for (i = 0; buffer[i]; i++)
        {
            // Check for color definitions
            if (buffer[i] == 'C' || buffer[i] == 'F') 
            {
                color_value = 0;
                color_count = 0; // Reset color count for each color definition
                for (j = i + 1; buffer[j] && buffer[j] != '\n'; j++)
                {
                    if (isdigit(buffer[j]))
                    {
                        color_value = color_value * 10 + (buffer[j] - '0');
                    }
                    else if (buffer[j] == ',')
                    {
                        if (color_value < 0 || color_value > 255)
                        {
                            fprintf(stderr, "Error: Invalid color value.\n");
                            close(fd);
                            exit(1); // Exit if color value is invalid
                        }
                        color_count++;
                        color_value = 0; // Reset for the next color value
                    }
                    else if (!isspace(buffer[j]))
                    {
                        fprintf(stderr, "Error: Invalid character in color.\n");
                        close(fd);
                        exit(1);
                    }
                }
                if (color_value < 0 || color_value > 255 || color_count != 2)
                {
                    fprintf(stderr, "Error: Invalid color value.\n");
                    close(fd);
                    exit(1);
                }
            }
            // Check map characters
            else if (buffer[i] != '\n' && !isspace(buffer[i]))
            {
                continue; // Skip invalid characters but allow for newlines and spaces
            }
        }
    }
    close(fd);
}