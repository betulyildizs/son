#include "../../lib/cub3d.h"

#include "../../lib/cub3d.h"
#include <ctype.h>

void special_cont(const char *file_name)
{
    int fd;
    char buffer[1024];
    int bytes_read;
    int i, j, color_value;
    int color_count; // To track the number of colors
    int map_section_started = 0; // Flag to track if we've reached the map section

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
            if ((buffer[i] == 'C' || buffer[i] == 'F') && !map_section_started) 
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
            // Detect the start of the map section
            else if (!map_section_started && buffer[i] == '1')
            {
                // Check if this is the start of the map (a line with consecutive 1's)
                int wall_count = 0;
                for (j = i; buffer[j] && buffer[j] != '\n'; j++) {
                    if (buffer[j] == '1') 
                        wall_count++;
                }

                // If we see multiple wall characters in a row, this is likely the map
                if (wall_count > 3) {
                    map_section_started = 1;
                }
            }
            // We're in the map section now
            else if (map_section_started)
            {
                // Skip newlines and spaces in the map (they're allowed)
                if (buffer[i] == '\n' || isspace(buffer[i]))
                    continue;

                if (buffer[i] != '0' && buffer[i] != '1' && 
                    buffer[i] != 'N' && buffer[i] != 'S' && 
                    buffer[i] != 'E' && buffer[i] != 'W')
                {
                    printf("Error: Invalid character in map.\n");
                    close(fd);
                    exit(1);
                }
            }
        }
    }
    close(fd);
}