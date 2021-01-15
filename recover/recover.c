#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }
    
    int count = -1;
    uint8_t bytes[512];
    char filename[512];
    FILE *img = NULL;
  
  
    //do
    while (fread(bytes, 512, 1, file))
    {
        
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            if (count == -1)
            {
                count++;
            }
            else
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            count++;
            
        }
        if (count >= 0)
        {
            fwrite(bytes, 512, 1, img);
        }
        
    }    
    //while(!(feof(file)));
    fclose(img);
    fclose(file);
    return 0;
}
   

