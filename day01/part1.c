#include <stdio.h>
#include <stdlib.h>

int calculate_fuel_mass(int mass){
  return (mass/3) - 2;
}

int main(int argc, char *argv[]){
  if(argc != 2){
    printf("USAGE: %s file_path\n", argv[0]);
    return(-1);
  }

  char* file_path = argv[1];
  FILE* fp = fopen(file_path, "r");
  if (!fp) {
    fprintf(stderr, "Failed to open file \"%s\"!\n", file_path);
    return(-2);
  }

  int fuel_total_mass = 0;

  int c;
  int buf_i = 0;
  char buf[7];
  while ((c = fgetc(fp)) != EOF){
    if(c=='\n'){
      buf[buf_i]='\0';

      int parsed_module_mass = atoi(buf);
      fuel_total_mass += calculate_fuel_mass(parsed_module_mass);

      buf_i=0;
    } else {
      buf[buf_i] = (char)c;
      buf_i += 1;
    }
  }

  fclose(fp);

  printf("total fuel mass => %d\n", fuel_total_mass);
}