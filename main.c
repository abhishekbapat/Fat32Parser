#include <stdio.h>
#include "include\fat32parser.h"


int main()
{
    FILE* fat32img = fopen(".\\images\\fat32.img", "r");
    BootSector bs;
    //dir_entry dir_entry[]; Will use in future
    //Fat32Entry fat32entry[]; Will use in future

    load_boot_sector(&bs, fat32img); //instantiates the boot sector and prints boot sector data on screen

    Fat32Entry root_entries[10];
    get_root_entries(&bs, fat32img, root_entries);
    char ip;
    while(1){
        printf("What do you want to do next?\n");
        printf("Input 'c' for contents of sub-directory\n");
        printf("Input 'f' to copy file in local directory D:\\Fat32Objs\\Output \n");
        printf("Input 'e' to exit\n");
        scanf("%c", &ip);
        //printf("%c\n",ip);

        if(ip == 'e'){
            break;
        }
        else if(ip == 'c'){
            Fat32Entry entry = *root_entries;
            int lower_bytes = entry.dir_entry.low_starting_cluster;
            int higher_bytes = entry.dir_entry.high_starting_cluster;
            int cluster = (higher_bytes*16)+lower_bytes;
            int cluster_offset = ((cluster-2)*bs.sectors_per_cluster)+(bs.reserved_sectors)+(bs.number_of_fats*bs.sectors_per_fat);
            get_dir_entries(cluster_offset*bs.bytes_per_sector,fat32img);
        }
        else if(ip == 'f'){
            Fat32Entry entry = *(root_entries+1);
            int lower_bytes = entry.dir_entry.low_starting_cluster;
            int higher_bytes = entry.dir_entry.high_starting_cluster;
            int cluster = (higher_bytes*16)+lower_bytes;
            int cluster_offset = ((cluster-2)*bs.sectors_per_cluster)+(bs.reserved_sectors)+(bs.number_of_fats*bs.sectors_per_fat);
            char *file_data = malloc(entry.dir_entry.file_size);
            fseek(fat32img, cluster_offset*bs.bytes_per_sector, SEEK_SET);
            fread(file_data, entry.dir_entry.file_size, 1, fat32img);

            FILE* output_file = fopen("D:\\Fat32Objs\\Output\\test.txt", "w");

            fwrite(file_data, entry.dir_entry.file_size, 1, output_file);

            printf("File created!");

        }
    }

    return 0;
}
