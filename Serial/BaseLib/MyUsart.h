/**
*********************************************************************
*********
* @project_name :car0
* @file : MyUsart.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6
*********************************************************************
*********
*/
//

#ifndef CAR0_MYUSART_H
#define CAR0_MYUSART_H

#include "UsartResources.h"
#ifdef HAL_UART_MODULE_ENABLED
#include "inputStream.h"
#include "outputStream.h"


class MyUsart :public inputStream,public outputStream {
public:
    MyUsart(UART_HandleTypeDef *pDef);

    void uart_init();
    void uart_DMAInit();

    void uart_deinit();

    void uart_write_byte(uint8_t data);

    void uart_write_buffer(const uint8_t *buf, int len);

    void uart_write_string(const char *str);

    uint16_t uart_rec_size();

    uint8_t uart_read_byte();



    void uart_dma_write_buffer(const uint8_t *buf, int len);

    void uart_dma_write_byte(uint8_t data);

    size_t write(uint8_t data) override;

    size_t write(const uint8_t *data, size_t size) override;

protected:
    __rec_buf* selectBuff(UART_enum uart);
    void selectUART_enum(UART_HandleTypeDef *huart);
    UART_HandleTypeDef* m_uart;
    UART_enum m_uartEnum;
};
void receiveDataCall(UART_HandleTypeDef *huart);
extern MyUsart Serial0;
extern MyUsart Serial1;
extern MyUsart Serial2;
extern MyUsart Serial3;
extern MyUsart Serial4;
extern MyUsart Serial5;





#endif
#endif //CAR0_MYUSART_H
