#include <fat32parser.h>

void disp_info(BootSector boot_sector){// used in LoadBootSector
    printf("Bytes per sector: %d bytes\n",boot_sector.bytes_per_sector);
    printf("Sectors per cluster: %d\n",boot_sector.sectors_per_cluster);
    printf("Reserved Sectors: %d\n",boot_sector.reserved_sectors);
    printf("Number of FATs: %d\n",boot_sector.number_of_fats);
    printf("Sectors per FAT: %d\n",boot_sector.sectors_per_fat);
    printf("Cluster number for root: %d\n",boot_sector.cluster_number_for_the_root_directory);
    printf("Total sectors: %d\n",boot_sector.total_sectors);
}

//(boot_sector.cluster_number_for_the_root_directory*boot_sector.sectors_per_cluster*boot_sector.bytes_per_sector)+
void get_to_root_entry(BootSector boot_sector, FILE* fat32img, int index){//Gives you the (index)th entry in the root folder
    fseek(fat32img, (32*(index))+(boot_sector.reserved_sectors*boot_sector.bytes_per_sector)+(boot_sector.number_of_fats*boot_sector.sectors_per_fat*boot_sector.bytes_per_sector),SEEK_SET);
}

void get_dir_entries(int bytes, FILE* fat32img){
    int count = 0;
    int index = 0;
    DirEntry cur_dir_entry;
    while(1){
        fseek(fat32img, (32*(index))+bytes , SEEK_SET);
        fread(&cur_dir_entry, sizeof(DirEntry),1,fat32img);
        if(cur_dir_entry.file_name[0]==0&&cur_dir_entry.file_name[1]==0&&cur_dir_entry.file_name[2]==0&&cur_dir_entry.file_name[3]==0&&cur_dir_entry.file_name[4]==0&&cur_dir_entry.file_name[5]==0&&cur_dir_entry.file_name[6]==0&&cur_dir_entry.file_name[7]==00){//No entry
            break;
        }
        else if((cur_dir_entry.attributes&0b00010000) == 0b00010000){//Sub directory
            printf("First byte of folder name: %s\n", cur_dir_entry.file_name);
            index++;
            count++;
            continue;
        }
        else if((cur_dir_entry.attributes&0b00100000) == 0b00100000){//File
            printf("First byte of file name: %s\n", cur_dir_entry.file_name);
            index++;
            count++;
            continue;
        }
        else if((cur_dir_entry.attributes&0b00001111) == 0b00001111){//Skip
            index++;
            continue;
        }
    }
    printf("There are %d entries in total\n", count);
}

void get_root_entries(BootSector* bs, FILE* fat32img, Fat32Entry *fat32_file_entries, Fat32Entry *fat32_dir_entries){//return a pointer to an array of entries of the root folder
    int file_count = 0;
    int dir_count = 0;
    int index = 0;
    DirEntry cur_dir_entry;
    printf("Browsing the root directory.\n");
    while(1){
        get_to_root_entry(*bs, fat32img, index);
        fread(&cur_dir_entry, sizeof(DirEntry),1,fat32img);
        if(cur_dir_entry.file_name[0]==0 && 
        cur_dir_entry.file_name[1]==0 &&
        cur_dir_entry.file_name[2]==0 && 
        cur_dir_entry.file_name[3]==0 && 
        cur_dir_entry.file_name[4]==0 && 
        cur_dir_entry.file_name[5]==0 && 
        cur_dir_entry.file_name[6]==0 && 
        cur_dir_entry.file_name[7]==00){//No entry
            break;
        }
        else if((cur_dir_entry.attributes&0b00010000) == 0b00010000){//Sub directory
            printf("Folder num: %d. Name: %s\n", dir_count, cur_dir_entry.file_name);
            index++;
            fat32_dir_entries[dir_count].dir_entry = cur_dir_entry;
            fat32_dir_entries[dir_count].file_name = cur_dir_entry.file_name;
            dir_count++;
            continue;
        }
        else if((cur_dir_entry.attributes&0b00100000) == 0b00100000){//File
            printf("File num: %d. Name: %s\n", file_count, cur_dir_entry.file_name);
            index++;
            fat32_file_entries[file_count].dir_entry = cur_dir_entry;
            fat32_file_entries[file_count].file_name = cur_dir_entry.file_name;
            file_count++;
            continue;
        }
        else if((cur_dir_entry.attributes&0b00001111) == 0b00001111){//Skip
            index++;
            continue;
        }
    }
}


void load_boot_sector(BootSector* bs, FILE* fat32img){//is called to load boot sector and display info
    printf("Loading boot sector.\n");
    fseek(fat32img, 0, SEEK_SET);
    fread(bs, sizeof(BootSector), 1, fat32img);
}
