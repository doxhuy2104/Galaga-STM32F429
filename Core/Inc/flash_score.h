#ifndef __FLASH_SCORE_H
#define __FLASH_SCORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void Flash_SaveHighScore(uint32_t score);
void Flash_ResetHighScore();
uint32_t Flash_LoadHighScore(void);

#ifdef __cplusplus
}
#endif

#endif // __FLASH_SCORE_H
