#include <stdio.h>
#include <stdlib.h>

void run_to_halt(int* memory);

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

  int c;
  int commas = 0;
  while((c=fgetc(fp)) != EOF){
    if(c==','){
      commas += 1;
    }
  }
  fseek(fp, 0, 0);

  int memory_size = commas + 1;
  printf("Allocating %d memory locations\n", memory_size);

  int* memory = malloc(sizeof(int) * memory_size);
  int memory_i = 0;
  
  int buf_i = 0;
  char buf[7];

  while((c=fgetc(fp)) != EOF){
    if(c==','){
      // terminate buf
      buf[buf_i]='\0';

      memory[memory_i] = atoi(buf);
      memory_i += 1;

      buf_i = 0;
    } else {
      buf[buf_i] = (char) c;
      buf_i += 1;
    }
  }
  // remember to catch last item
  buf[buf_i]='\0';
  memory[memory_i] = atoi(buf);

  fclose(fp);
  
  // must replace these two locations as part of requirements
  memory[1] = 12;
  memory[2] = 2;

  run_to_halt(memory);

  printf("0: %d\n", memory[0]);

  free(memory);
}

void run_to_halt(int* memory){
  int inst_ptr = 0;
  while(memory[inst_ptr] != 99){
    int opcode = memory[inst_ptr];
    int parameter_a = memory[inst_ptr+1];
    int parameter_b = memory[inst_ptr+2];
    int parameter_c = memory[inst_ptr+3];
    int val_a = memory[parameter_a];
    int val_b = memory[parameter_b];

    switch (opcode)
    {
    case 1:
      /* code */
      memory[parameter_c] = val_a + val_b;
      break;
    case 2:
      memory[parameter_c] = val_a * val_b;
      break;
    default:
      break;
    }

    inst_ptr += 4;
  }
}