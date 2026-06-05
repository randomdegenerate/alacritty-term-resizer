#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define FONT_SIZE 12
#define MAX_LINE 2048
#define BUF_SIZE 256
int replace_size_attribute(int font_size, char *line, FILE *file);

int main() {
  FILE *term_config;
  bool attribute_found = 0;
  int count = 0;
  char buffer[BUF_SIZE] = {0};

  term_config = fopen("/home/sandil/.config/alacritty/alacritty.toml", "r");
  if (term_config == NULL) {
    printf("File Not Found!");
    return 1;
  }

  while (fgets(buffer, BUF_SIZE, term_config) != NULL && count < MAX_LINE) {
    count++;
    if (!attribute_found) {
      if (strcmp(buffer, "[font]\n") == 0) {
        printf("font attribute found!\n");
        attribute_found = 1;
      }

      printf("%d %d: %s", attribute_found, count, buffer);
    } else {
      /* TODO fix sub_buff either not being copied to properly or printf()
       * Result bugging out */
      char sub_buff[6];
      memset(sub_buff, 0, sizeof sub_buff);
      strncpy(sub_buff, &buffer[0], sizeof sub_buff);
      printf("sub_buff: %s\n", sub_buff);
      if (strcmp(sub_buff, "size =") == 0) {
        printf("Found Font Size Attribute!\n");
        break;
      }
    }
  }

  fclose(term_config);
  return 0;
}

int replace_size_attribute(int font_size, char *line, FILE *file) { return 0; }
