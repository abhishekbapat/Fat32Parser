#include <stdio.h>
#include <string.h>
#include <fat32parser.h>


int main(int argc, char **argv)
{
    if (argc <= 1){
        printf("Image file name to be read was not passed. Terminating.\n");
        exit(EXIT_FAILURE);
    }

    printf("Reading image file %s .\n", argv[1]);
    FILE* fat32img = fopen(argv[1], "r");
    if(!fat32img){
        perror("Error reading image file");
        exit(EXIT_FAILURE);
    }

    BootSector bs;
    load_boot_sector(&bs, fat32img); //instantiates the boot sector and prints boot sector data on screen

    Fat32Entry dir_entries[10];
    Fat32Entry file_entries[10];
    if(argc <= 2){
        get_root_entries(&bs, fat32img, file_entries, dir_entries);
        fclose(fat32img);
        return 0;
    }

    if(strcmp(argv[2], "read") == 0){
        if(argc <= 3){
            printf("Did not specify which subdir to read.");
            exit(EXIT_FAILURE);
        }

        char* dir_tok = strtok(argv[3], "/");
        
    }
    // Fat32Entry root_entries[10];
    // get_root_entries(&bs, fat32img, root_entries);
    // char ip;
    // while(1){
    //     printf("What do you want to do next?\n");
    //     printf("Input 'c' for contents of sub-directory\n");
    //     printf("Input 'f' to copy file in local directory D:\\Fat32Objs\\Output \n");
    //     printf("Input 'e' to exit\n");
    //     scanf("%c", &ip);
    //     //printf("%c\n",ip);

    //     if(ip == 'e'){
    //         break;
    //     }
    //     else if(ip == 'c'){
    //         Fat32Entry entry = *root_entries;
    //         int lower_bytes = entry.dir_entry.low_starting_cluster;
    //         int higher_bytes = entry.dir_entry.high_starting_cluster;
    //         int cluster = (higher_bytes*16)+lower_bytes;
    //         int cluster_offset = ((cluster-2)*bs.sectors_per_cluster)+(bs.reserved_sectors)+(bs.number_of_fats*bs.sectors_per_fat);
    //         get_dir_entries(cluster_offset*bs.bytes_per_sector,fat32img);
    //     }
    //     else if(ip == 'f'){
    //         Fat32Entry entry = *(root_entries+1);
    //         int lower_bytes = entry.dir_entry.low_starting_cluster;
    //         int higher_bytes = entry.dir_entry.high_starting_cluster;
    //         int cluster = (higher_bytes*16)+lower_bytes;
    //         int cluster_offset = ((cluster-2)*bs.sectors_per_cluster)+(bs.reserved_sectors)+(bs.number_of_fats*bs.sectors_per_fat);
    //         char *file_data = malloc(entry.dir_entry.file_size);
    //         fseek(fat32img, cluster_offset*bs.bytes_per_sector, SEEK_SET);
    //         fread(file_data, entry.dir_entry.file_size, 1, fat32img);

    //         FILE* output_file = fopen("D:\\test.txt", "w");

    //         fwrite(file_data, entry.dir_entry.file_size, 1, output_file);

    //         fclose(output_file);

    //         printf("File created!");

    //     }
    //}
    fclose(fat32img);
    return 0;
}
