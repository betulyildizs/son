#include "../../lib/cub3d.h"

void check_texture_file(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error: Unable to open texture file '%s'.\n", path);
        exit(1); // Hata durumunda çık
    }
    close(fd); // Dosyayı kapat
}

char* get_texture_path(char *buffer, int *index) {
    char *start = &buffer[*index + 3];
    while (*start && isspace(*start)) start++; // Boşlukları atla
    char *texture_path = start;
    while (*start && !isspace(*start)) start++; // Texture yolunu al
    *start = '\0'; // Yolu sonlandır
    *index += 3; // İndeksi güncelle
    return texture_path;
}

void check_texture_in_map(char *buffer, int bytes_read) {
    for (int i = 0; i < bytes_read; i++) {
        if (ft_strncmp(&buffer[i], "NO ", 3) == 0 ||
            ft_strncmp(&buffer[i], "SO ", 3) == 0 ||
            ft_strncmp(&buffer[i], "WE ", 3) == 0 ||
            ft_strncmp(&buffer[i], "EA ", 3) == 0) {
            char *texture_path = get_texture_path(buffer, &i);
            check_texture_file(texture_path);
        }
    }
}

void check_textures_in_map(const char *map_file) {
    
    int fd = open(map_file, O_RDONLY);
    if (fd < 0) {
        perror("Error opening map file");
        exit(1);
    }

    char buffer[1024];
    int bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        check_texture_in_map(buffer, bytes_read);
    }
    close(fd);
}