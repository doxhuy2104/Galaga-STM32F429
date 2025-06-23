#include "flash_score.h"
#include "stm32f4xx_hal.h"

#define FLASH_SECTOR_SCORE      FLASH_SECTOR_11
#define FLASH_SCORE_ADDRESS     0x080E0000  // Sector 11 start
#define SCORE_FLASH_MAGIC       0xA5A5A5A5  // Dùng để xác nhận dữ liệu hợp lệ

typedef struct {
    uint32_t magic;
    uint32_t score;
} FlashScore_t;

static FlashScore_t* flash_score_ptr = (FlashScore_t*)FLASH_SCORE_ADDRESS;

void Flash_SaveHighScore(uint32_t score) {
    HAL_FLASH_Unlock();

    // Xóa sector 11
    FLASH_EraseInitTypeDef eraseInit;
    uint32_t sectorError;

    eraseInit.TypeErase    = FLASH_TYPEERASE_SECTORS;
    eraseInit.Sector       = FLASH_SECTOR_SCORE;
    eraseInit.NbSectors    = 1;
    eraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3; // 2.7V - 3.6V

    if (HAL_FLASHEx_Erase(&eraseInit, &sectorError) != HAL_OK) {
        HAL_FLASH_Lock();
        return; // Lỗi khi xóa
    }

    // Ghi magic + score
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_SCORE_ADDRESS, SCORE_FLASH_MAGIC);
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_SCORE_ADDRESS + 4, score);

    HAL_FLASH_Lock();
}

void Flash_ResetHighScore() {
    Flash_SaveHighScore(0);
}


uint32_t Flash_LoadHighScore(void) {
    if (flash_score_ptr->magic == SCORE_FLASH_MAGIC) {
        return flash_score_ptr->score;
    } else {
        return 0; // Nếu chưa có gì thì coi như điểm là 0
    }
}
