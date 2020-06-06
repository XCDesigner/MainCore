#pragma once

#include "stdint.h"

class PartitionManager {
public:
  static void StoreSetting();
  static void RestoreSetting();
  static void SettingWriteOneByte(uint32_t pos, uint8_t value);
  static uint8_t SettingReadOneByte(uint32_t pos);
  static uint32_t GetCapacity();

  static void GetPowerlossData();
  static void StorePowerlossData();
  
  static void EraseUpdateInfo();
  static bool GetUpdateInfo(uint8_t *pInfo);
  static void ProgramUpdateInfo(uint8_t pData);

  static bool MarkDownloadComplete();
  static void EraseUpdateRegion();
  static void PragramUpdatePack(uint8_t *pData, uint16_t Packindex);
  
  static bool GetUpdatePack(uint8_t *pData, uint16_t Packindex);

private:
  static uint8_t content_of_setting[4096];
  static bool setting_restored;
};