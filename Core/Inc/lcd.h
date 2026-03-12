#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f4xx_hal.h"

// Fonksiyon Prototipleri
void LCD_Init(void);                                  // LCD'yi başlatma
void LCD_SendCommand(uint8_t cmd);                   // Komut gönderme
void LCD_SendData(uint8_t data);                    // Veri (Karakter) gönderme
void LCD_Clear(void);                               // Ekranı temizleme
void LCD_SetCursor(uint8_t row, uint8_t col);      // İmleç konumlandırma
void LCD_Print(char *str);                          // String (Metin) yazdırma

#endif /* INC_LCD_H_ */
