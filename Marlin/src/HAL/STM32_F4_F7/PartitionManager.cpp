#include "PartitionManager.h"

#include "stm32f4xx_conf.h"

// Sector0-3:16K per page
// Sector4:64K
// Sector5-11:128K per page

// Size define
#define SIZE_BOOTLOAD         (32 * 1024) //Sector0-1 
#define SIZE_BOOT_INFO        (16 * 1024) //Sector2
#define SIZE_SETTINGS         (16 *1024)  //Sector3
#define SIZE_POWER_LOSS_DATA  (64 * 1024) //Sector4
#define SIZE_UPDATE_INFO      (128 * 1024) //Sector5
#define SIZE_APP              (384 * 1024) //Sector6-8
#define SIZE_UPDATE_CONTENT   (384 * 1024) //Sector9-11

// Flash address
#define FLASH_BOOT            0x8000000
#define FLASH_BOOT_INFO       (FLASH_BOOT + SIZE_BOOTLOAD)
#define FLASH_SETTINGS        (FLASH_BOOT_INFO + SIZE_BOOT_INFO)
#define FLASH_POWER_LOSS_DATA (FLASH_SETTINGS + SIZE_SETTINGS)
#define FLASH_UPDATE_INFO     (FLASH_POWER_LOSS_DATA + SIZE_POWER_LOSS_DATA)
#define FLASH_APP             (FLASH_UPDATE_INFO + SIZE_UPDATE_INFO)
#define FLASH_UPDATE_CONTENT  (FLASH_APP + SIZE_APP)

#define UPDATE_PACKAGE_SIZE     512

// Flag
#define FLAG_VALID              0x112233ee

// Offset
// Boot information
#define OFFSET_AOO_PROGRAMED    4
#define OFFSET_APP_VALID        8
#define OFFSET_APP_VERSION      12

// Update information
#define OFFSET_DOWNLOAD_COMPLETE  8
#define OFFSET_FIRMWARE_VERSION   12

uint8_t PartitionManager::content_of_setting[4096];
bool PartitionManager::setting_restored = false;


void PartitionManager::StoreSetting() {
  uint32_t addr;
  uint16_t u16_value;
  
  addr = FLASH_SETTINGS;

  FLASH_Unlock();
  FLASH_EraseSector(FLASH_Sector_3, VoltageRange_2);
  for(uint32_t i=0;i<sizeof(content_of_setting);i=i+2) {
    u16_value = (content_of_setting[i+1] << 8) | content_of_setting[i];
    FLASH_ProgramHalfWord(addr, u16_value);
    addr = addr + 2;
  }
  FLASH_Lock();
}


void PartitionManager::RestoreSetting() {
  if(setting_restored == false) {
    uint32_t addr;
    addr = FLASH_SETTINGS;
    for(uint32_t i=0;i<sizeof(content_of_setting);i++) {
      content_of_setting[i] = *((uint8_t*)addr);
      addr++;
    }
    setting_restored = true;
  }
}


void PartitionManager::SettingWriteOneByte(uint32_t pos, uint8_t value) {
  if(setting_restored == false) 
    RestoreSetting();
  content_of_setting[pos] = value;
}


uint8_t PartitionManager::SettingReadOneByte(uint32_t pos) {
  if(setting_restored == false) 
    RestoreSetting();
  return content_of_setting[pos];
}


uint32_t PartitionManager::GetCapacity() {
  return sizeof(content_of_setting);
}


void PartitionManager::GetPowerlossData() {

}


void PartitionManager::StorePowerlossData() {

}


void PartitionManager::EraseUpdateInfo() {
  FLASH_Unlock();
  FLASH_EraseSector(FLASH_Sector_5, VoltageRange_2);
  FLASH_Lock();
}


bool PartitionManager::MarkDownloadComplete() {
  uint32_t addr;
  uint32_t u32_value;
  addr = FLASH_UPDATE_INFO + OFFSET_DOWNLOAD_COMPLETE;
  u32_value = *((uint32_t *)addr);
  FLASH_Unlock();
  FLASH_ProgramWord(addr, FLAG_VALID);
  FLASH_Lock();

  if(u32_value != 0xffffffff)
    return false;
  else
    return true;
}


void PartitionManager::EraseUpdateRegion() {
  FLASH_Unlock();
  FLASH_EraseSector(FLASH_Sector_9, VoltageRange_2);
  FLASH_EraseSector(FLASH_Sector_10, VoltageRange_2);
  FLASH_EraseSector(FLASH_Sector_11, VoltageRange_2);
  FLASH_Lock();
}


void PartitionManager::PragramUpdatePack(uint8_t *pData, uint16_t Packindex) {
  uint32_t addr;
  uint32_t i;
  uint16_t u16_value;

  addr = Packindex * UPDATE_PACKAGE_SIZE + FLASH_UPDATE_CONTENT;
  for(i=0;i<512;i=i+2) {
    u16_value = (pData[i + 1] << 8) | pData[i];
    FLASH_ProgramHalfWord(addr, u16_value);
    addr = addr + 2;
  }
}
