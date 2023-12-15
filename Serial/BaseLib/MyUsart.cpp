/**
*********************************************************************
*********
* @project_name :car0
* @file : MyUsart.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/11/6
*********************************************************************
*********
*/
//

#include "WString.h"
#include "MyUsart.h"
#ifdef HAL_UART_MODULE_ENABLED
uint8_t BufferArray;
bool openDMATransmit= false;

void MyUsart::uart_init() {
    selectUART_enum(m_uart);
    buf=selectBuff(m_uartEnum);
    HAL_UART_Receive_IT(m_uart,&BufferArray,1);
}
void MyUsart::uart_DMAInit() {
    selectUART_enum(m_uart);
    buf=selectBuff(m_uartEnum);
    openDMATransmit= true;
    HAL_UART_Receive_DMA(m_uart,&BufferArray,1);
}
void MyUsart::uart_deinit() {
    HAL_UART_DeInit(m_uart);
}

void MyUsart::uart_write_byte(uint8_t data) {
    HAL_UART_Transmit(m_uart, (uint8_t *)&data, 1, MAXWait);
}

void MyUsart::uart_write_buffer(const uint8_t *buf, int len) {
    HAL_UART_Transmit(m_uart, (uint8_t *)buf, len, MAXWait);
}

void MyUsart::uart_write_string(const char *str) {
    int len = strlen(str);
    HAL_UART_Transmit(m_uart, (uint8_t *)str, len, MAXWait);
}

uint16_t MyUsart::uart_rec_size() {
    auto uart_buf = selectBuff(m_uartEnum);
    return uart_buf->data_size;
}

uint8_t MyUsart::uart_read_byte() {
     __rec_buf *uart_recbuf =selectBuff(m_uartEnum);
    while (uart_recbuf->data_size == 0)
        ;
    uint8_t res = uart_recbuf->buf[uart_recbuf->read_index++];
    uart_recbuf->data_size--;
    return res;
}

void MyUsart::uart_dma_write_byte(uint8_t data) {
    HAL_UART_Transmit_DMA(m_uart, &data, 1);
}

void MyUsart::uart_dma_write_buffer(const uint8_t *buf, int len) {
    HAL_UART_Transmit_DMA(m_uart, buf, len);
}


__rec_buf *MyUsart::selectBuff(UART_enum uart) {
    switch (uart) {
#ifdef HAVE_SERIAL1
        case UART_1:
            return &UART1_recbuf;
#endif
#ifdef HAVE_SERIAL2
        case UART_2:
            return &UART2_recbuf;
#endif
#ifdef HAVE_SERIAL3
        case UART_3:
            return &UART3_recbuf;
#endif
#ifdef HAVE_SERIAL4
        case UART_4:
            return &UART4_recbuf;
#endif
#ifdef HAVE_SERIAL5
        case UART_5:
            return &UART5_recbuf;
#endif
#ifdef HAVE_SERIAL6
        case UART_6:
            return &UART6_recbuf;
#endif
        default:
            return nullptr;
    }
}



void MyUsart::selectUART_enum(UART_HandleTypeDef *huart) {
#ifdef HAVE_SERIAL1
    if (huart->Instance==USART1){
        m_uartEnum=UART_1;
    }
#endif
#ifdef HAVE_SERIAL2
            if (huart->Instance==USART2){
                m_uartEnum=UART_2;
             }
#endif
#ifdef HAVE_SERIAL3
    if (huart->Instance==USART3){
        m_uartEnum=UART_3;
    }
#endif
#ifdef HAVE_SERIAL4
    if (huart->Instance==USART3){
        m_uartEnum=UART_4;
    }
#endif
#ifdef HAVE_SERIAL5
    if (huart->Instance==USART3){
        m_uartEnum=UART_5;
    }
#endif
#ifdef HAVE_SERIAL6
    if (huart->Instance==USART3){
        m_uartEnum=UART_6;
    }
#endif
}

size_t MyUsart::write(uint8_t data) {
    if (openDMATransmit){
        this->uart_dma_write_byte(data);
    }else{
        this->uart_write_byte(data);
    }
    return 1;
}

size_t MyUsart::write(const uint8_t *data, size_t size) {
    if (openDMATransmit){
        this->uart_dma_write_buffer(data,size);
    }else{
        this->uart_write_buffer(data,size);
    }
    return 1;
}

MyUsart::MyUsart(UART_HandleTypeDef *pDef) {
    m_uart=pDef;
    uart_init();
}

#ifdef HAVE_SERIAL1
__rec_buf UART1_recbuf={0};

#endif

#ifdef HAVE_SERIAL2
__rec_buf UART2_recbuf={0};
#endif

#ifdef HAVE_SERIAL3
__rec_buf UART3_recbuf={0};

#endif

#ifdef HAVE_SERIAL4
__rec_buf UART4_recbuf={0};

#endif

#ifdef HAVE_SERIAL5
__rec_buf UART5_recbuf={0};

#endif
#ifdef HAVE_SERIAL6
__rec_buf UART6_recbuf={0};

#endif
void receiveDataCall(UART_HandleTypeDef *huart){
#ifdef HAVE_SERIAL1
    if (huart->Instance==USART1){
        if (UART1_recbuf.data_size>256) return;
        UART1_recbuf.buf[UART1_recbuf.write_index++]=BufferArray;
        UART1_recbuf.data_size++;
        if (openDMATransmit){
            HAL_UART_Receive_DMA(huart,&BufferArray,1);
        } else{
            HAL_UART_Receive_IT(huart,&BufferArray,1);
        }
    }
#endif
#ifdef HAVE_SERIAL2
    if (huart->Instance==USART2){
        if (UART2_recbuf.data_size>256) return;
        UART2_recbuf.buf[UART2_recbuf.write_index++]=BufferArray;
        UART2_recbuf.data_size++;
        if (openDMATransmit){
            HAL_UART_Receive_DMA(huart,&BufferArray,1);
        } else{
            HAL_UART_Receive_IT(huart,&BufferArray,1);
        }
    }
#endif
#ifdef HAVE_SERIAL3
    if (huart->Instance==USART3){
        if (UART3_recbuf.data_size>256) return;
        UART3_recbuf.buf[UART3_recbuf.write_index++]=BufferArray;
        UART3_recbuf.data_size++;
        if (openDMATransmit){
            HAL_UART_Receive_DMA(huart,&BufferArray,1);
        } else{
            HAL_UART_Receive_IT(huart,&BufferArray,1);
        }
    }
#endif
#ifdef HAVE_SERIAL4
    if (huart->Instance==UART4){
        if (UART4_recbuf.data_size>256) return;
        UART4_recbuf.buf[UART4_recbuf.write_index++]=BufferArray;
        UART4_recbuf.data_size++;
        if (openDMATransmit){
            HAL_UART_Receive_DMA(huart,&BufferArray,1);
        } else{
            HAL_UART_Receive_IT(huart,&BufferArray,1);
        }
    }
#endif
#ifdef HAVE_SERIAL5
    if (huart->Instance==UART5){
        if (UART5_recbuf.data_size>256) return;
        UART5_recbuf.buf[UART5_recbuf.write_index++]=BufferArray;
        UART5_recbuf.data_size++;
        if (openDMATransmit){
            HAL_UART_Receive_DMA(huart,&BufferArray,1);
        } else{
            HAL_UART_Receive_IT(huart,&BufferArray,1);
        }
    }
#endif
#ifdef HAVE_SERIAL6
    if (huart->Instance==USART6){
        if (UART6_recbuf.data_size>256) return;
        UART6_recbuf.buf[UART6_recbuf.write_index++]=BufferArray;
        UART6_recbuf.data_size++;
        if (openDMATransmit){
            HAL_UART_Receive_DMA(huart,&BufferArray,1);
        } else{
            HAL_UART_Receive_IT(huart,&BufferArray,1);
        }
    }
#endif
}
#endif

/*****************************************************************************************************************************/
#ifdef HAVE_SERIAL1
MyUsart Serial0(&huart1);
#endif
#ifdef HAVE_SERIAL2
MyUsart Serial1(&huart2);
#endif
#ifdef HAVE_SERIAL3
MyUsart Serial2(&huart3);
#endif
#ifdef HAVE_SERIAL4
MyUsart Serial3(&hart4);
#endif
#ifdef HAVE_SERIAL5
MyUsart Serial4(&hart5);
#endif
#ifdef HAVE_SERIAL6
MyUsart Serial5(&huart6);
#endif
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    receiveDataCall(huart);
}






