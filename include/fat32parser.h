#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(1)
typedef struct {
    uint8_t 	jump_instruction[3];
    uint8_t 	oem_name[8];
    uint16_t 	bytes_per_sector; // in bytes
    uint8_t 	sectors_per_cluster;
    uint16_t	reserved_sectors;
    uint8_t 	number_of_fats;
    uint16_t	root_dir_entries; //NA for FAT32
    uint16_t 	sectors_short; // if zero, later field is used
    uint8_t 	media_descriptor;
    uint16_t 	sectors_per_fat_old;
    uint16_t 	sectors_per_track;
    uint16_t 	number_of_heads;
    uint32_t 	hidden_sectors;
    uint32_t 	total_sectors;

    //BIOS Parameter Block
    uint32_t	sectors_per_fat;
    uint16_t	flags_for_fat;
    uint16_t    drive_version_number;
    uint32_t	cluster_number_for_the_root_directory;
    uint16_t	sector_number_fs_info_sector;
    uint16_t 	sector_number_for_backupboot;
    uint8_t		reserved_for_future_expansion[12];

    uint8_t 	drive_number_logical;
    uint8_t 	reserved;
    uint8_t 	boot_signature;
    uint32_t 	volume_id;
    uint8_t 	volume_label[11];
    uint8_t 	fat_name[8];
} BootSector;

#pragma pack(1)
typedef struct{
    uint8_t file_name[8];
    uint8_t extension[3];
    uint8_t attributes;
    uint8_t reserved;
    uint8_t created_time_tens_of_second;
    uint16_t created_time_hms;
    uint16_t created_day;
    uint16_t accessed_day;
    uint16_t high_starting_cluster;
    uint16_t modify_time;
    uint16_t modify_date;
    uint16_t low_starting_cluster; //represent the byte in FAT
    uint32_t file_size;
} DirEntry;

#pragma pack(1)
typedef struct{
    DirEntry dir_entry;
    char *file_name;
} Fat32Entry;

void disp_info(BootSector);

void get_to_root_entry(BootSector, FILE*, int);

void get_root_entries(BootSector*, FILE*, Fat32Entry*, Fat32Entry*);

void load_boot_sector(BootSector* , FILE*);

void get_dir_entries(int, FILE*);
