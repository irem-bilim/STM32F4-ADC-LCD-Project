#include "lcd.h"
#include "main.h" // Pin tanımlarını buradan alır (LCD_RS_Pin, LCD_EN_Pin vb.)

// Yardımcı Fonksiyon: 4-Bit Veri Gönder
void LCD_Send4Bits(uint8_t data) {
    HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (data & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, ((data >> 1) & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, ((data >> 2) & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, ((data >> 3) & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// Komut Gönderme Fonksiyonu
void LCD_SendCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET); // RS = 0 (Komut)

    LCD_Send4Bits(cmd >> 4); // Üst 4 bit
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);

    LCD_Send4Bits(cmd & 0x0F); // Alt 4 bit
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);
    HAL_Delay(2);
}

// Veri Gönderme Fonksiyonu
void LCD_SendData(uint8_t data) {
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET); // RS = 1 (Veri)

    LCD_Send4Bits(data >> 4);
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);

    LCD_Send4Bits(data & 0x0F);
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}

// LCD Başlatma (4-Bit Modu)
void LCD_Init(void) {
    HAL_Delay(50);
    LCD_SendCommand(0x02); // 4-bit moda geçiş
    LCD_SendCommand(0x28); // 2 satır, 5x8 font
    LCD_SendCommand(0x0C); // Ekran Açık
    LCD_SendCommand(0x06); // Sağa kaydır
    LCD_SendCommand(0x01); // Temizle
    HAL_Delay(2);
}

void LCD_Clear(void) {
    LCD_SendCommand(0x01);
    HAL_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address;
    if (row == 0) address = 0x80 + col;
    else address = 0xC0 + col;
    LCD_SendCommand(address);
}

void LCD_Print(char *str) {
    while (*str) {
        LCD_SendData(*str++);
    }
}
