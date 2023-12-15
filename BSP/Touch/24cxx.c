/**
 ****************************************************************************************************
 * @file        24cxx.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-23
 * @brief       24CXX ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20211023
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "myiic.h"
#include "24cxx.h"
#include "delay.h"


/**
 * @brief       ��ʼ��IIC�ӿ�
 * @param       ��
 * @retval      ��
 */
void at24cxx_init(void)
{
    iic_init();
}

/**
 * @brief       ��AT24CXXָ����ַ����һ������
 * @param       readaddr: ��ʼ�����ĵ�ַ
 * @retval      ����������
 */
uint8_t at24cxx_read_one_byte(uint16_t addr)
{
    uint8_t temp = 0;
    iic_start();    /* ������ʼ�ź� */

    /* ���ݲ�ͬ��24CXX�ͺ�, ���͸�λ��ַ
     * 1, 24C16���ϵ��ͺ�, ��2���ֽڷ��͵�ַ
     * 2, 24C16�����µ��ͺ�, ��1�����ֽڵ�ַ + ռ��������ַ��bit1~bit3λ ���ڱ�ʾ��λ��ַ, ���11λ��ַ
     *    ����24C01/02, ��������ַ��ʽ(8bit)Ϊ: 1  0  1  0  A2  A1  A0  R/W
     *    ����24C04,    ��������ַ��ʽ(8bit)Ϊ: 1  0  1  0  A2  A1  a8  R/W
     *    ����24C08,    ��������ַ��ʽ(8bit)Ϊ: 1  0  1  0  A2  a9  a8  R/W
     *    ����24C16,    ��������ַ��ʽ(8bit)Ϊ: 1  0  1  0  a10 a9  a8  R/W
     *    R/W      : ��/д����λ 0,��ʾд; 1,��ʾ��;
     *    A0/A1/A2 : ��Ӧ������1,2,3����(ֻ��24C01/02/04/8����Щ��)
     *    a8/a9/a10: ��Ӧ�洢���еĸ�λ��ַ, 11bit��ַ�����Ա�ʾ2048��λ��, ����Ѱַ24C16�����ڵ��ͺ�
     */    
    if (EE_TYPE > AT24C16)      /* 24C16���ϵ��ͺ�, ��2���ֽڷ��͵�ַ */
    {
        iic_send_byte(0xA0);    /* ����д����, IIC�涨���λ��0, ��ʾд�� */
        iic_wait_ack();         /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
        iic_send_byte(addr >> 8);   /* ���͸��ֽڵ�ַ */
    }
    else 
    {
        iic_send_byte(0xA0 + ((addr >> 8) << 1));   /* �������� 0xA0 + ��λa8/a9/a10��ַ,д���� */
    }
    
    iic_wait_ack();             /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    iic_send_byte(addr % 256);  /* ���͵�λ��ַ */
    iic_wait_ack();             /* �ȴ�ACK, ��ʱ��ַ��������� */
    
    iic_start();                /* ���·�����ʼ�ź� */ 
    iic_send_byte(0xA1);        /* �������ģʽ, IIC�涨���λ��1, ��ʾ��ȡ */
    iic_wait_ack();             /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    temp = iic_read_byte(0);    /* ����һ���ֽ����� */
    iic_stop();                 /* ����һ��ֹͣ���� */
    return temp;
}

/**
 * @brief       ��AT24CXXָ����ַд��һ������
 * @param       addr: д�����ݵ�Ŀ�ĵ�ַ
 * @param       data: Ҫд�������
 * @retval      ��
 */
void at24cxx_write_one_byte(uint16_t addr, uint8_t data)
{
    /* ԭ��˵����:at24cxx_read_one_byte����, ��������ȫ���� */
    iic_start();    /* ������ʼ�ź� */

    if (EE_TYPE > AT24C16)      /* 24C16���ϵ��ͺ�, ��2���ֽڷ��͵�ַ */
    {
        iic_send_byte(0xA0);    /* ����д����, IIC�涨���λ��0, ��ʾд�� */
        iic_wait_ack();         /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
        iic_send_byte(addr >> 8);   /* ���͸��ֽڵ�ַ */
    }
    else
    {
        iic_send_byte(0xA0 + ((addr >> 8) << 1));   /* �������� 0xA0 + ��λa8/a9/a10��ַ,д���� */
    }
    
    iic_wait_ack();             /* ÿ�η�����һ���ֽ�,��Ҫ�ȴ�ACK */
    iic_send_byte(addr % 256);  /* ���͵�λ��ַ */
    iic_wait_ack();             /* �ȴ�ACK, ��ʱ��ַ��������� */
    
    /* ��Ϊд���ݵ�ʱ��,����Ҫ�������ģʽ��,�������ﲻ�����·�����ʼ�ź��� */
    iic_send_byte(data);        /* ����1�ֽ� */
    iic_wait_ack();             /* �ȴ�ACK */
    iic_stop();                 /* ����һ��ֹͣ���� */
    delay_ms(10);               /* ע��: EEPROM д��Ƚ���,����ȵ�10ms����д��һ���ֽ� */
}
 
/**
 * @brief       ���AT24CXX�Ƿ�����
 *   @note      ���ԭ��: ��������ĩ��ַд��0X55, Ȼ���ٶ�ȡ, �����ȡֵΪ0X55
 *              ���ʾ�������. ����,���ʾ���ʧ��.
 *
 * @param       ��
 * @retval      �����
 *              0: ���ɹ�
 *              1: ���ʧ��
 */
uint8_t at24cxx_check(void)
{
    uint8_t temp;
    uint16_t addr = EE_TYPE;
    temp = at24cxx_read_one_byte(addr);     /* ����ÿ�ο�����дAT24CXX */

    if (temp == 0x55)   /* ��ȡ�������� */
    {
        return 0;
    }
    else    /* �ų���һ�γ�ʼ������� */
    {
        at24cxx_write_one_byte(addr, 0x55); /* ��д������ */
        temp = at24cxx_read_one_byte(255);  /* �ٶ�ȡ���� */

        if (temp == 0x55)return 0;
    }

    return 1;
}

/**
 * @brief       ��AT24CXX�����ָ����ַ��ʼ����ָ������������
 * @param       addr    : ��ʼ�����ĵ�ַ ��24c02Ϊ0~255
 * @param       pbuf    : ���������׵�ַ
 * @param       datalen : Ҫ�������ݵĸ���
 * @retval      ��
 */
void at24cxx_read(uint16_t addr, uint8_t *pbuf, uint16_t datalen)
{
    while (datalen--)
    {
        *pbuf++ = at24cxx_read_one_byte(addr++);
    }
}

/**
 * @brief       ��AT24CXX�����ָ����ַ��ʼд��ָ������������
 * @param       addr    : ��ʼд��ĵ�ַ ��24c02Ϊ0~255
 * @param       pbuf    : ���������׵�ַ
 * @param       datalen : Ҫд�����ݵĸ���
 * @retval      ��
 */
void at24cxx_write(uint16_t addr, uint8_t *pbuf, uint16_t datalen)
{
    while (datalen--)
    {
        at24cxx_write_one_byte(addr, *pbuf);
        addr++;
        pbuf++;
    }
}






