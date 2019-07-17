#include <reg52.h>
#include "I2C.h"

void Delay10us(void)
{
    unsigned char a, b;
    for (b = 1; b > 0; b--)
        for (a = 2; a > 0; a--)
            ;
}
void IIC_Start()
{
    SDA = 1;
    Delay10us();
    SCL = 1;
    Delay10us();
    SDA = 0;
    Delay10us();
    SCL = 0;
    Delay10us();
}
void IIC_Stop()
{
    SDA = 0;
    Delay10us();
    SCL = 1;
    Delay10us();
    SDA = 1;
    Delay10us();
}
unsigned char IIC_SendByte(unsigned char dat)
{
    unsigned char i = 0;
    unsigned char a = 0;
    unsigned char temp = dat;
    for (i = 0; i < 8; i++)
    {
        temp <<= 1;
        SDA = CY;
        Delay10us();
        SCL = 1;
        Delay10us();
        SCL = 0;
        Delay10us();
    }
    return 1;
}
unsigned char IIC_ReadByte()
{
    unsigned char i;
    unsigned char dat;
    SDA = 1;
    for (i = 0; i < 8; i++)
    {
        SCL = 1;
        Delay10us();
        dat <<= 1;
        dat |= SDA;
        Delay10us();
        SCL = 0;
        Delay10us();
    }
    return dat;
}
void Response92(void)
{
    SDA = 1;
    Delay10us();
    SCL = 1;
    Delay10us();
    SCL = 0;
    Delay10us();
    SDA = 1;
    Delay10us();
}
void Response00(void)
{
    SDA = 0;
    Delay10us();
    SCL = 1;
    Delay10us();
    SCL = 0;
    Delay10us();
    SDA = 1;
    Delay10us();
}
void noresponse00(void)
{
    SDA = 1;
    Delay10us();
    SCL = 1;
    Delay10us();
    SCL = 0;
    Delay10us();
    SDA = 0;
    Delay10us();
}
unsigned int ReadTemp()
{
    unsigned int Temp1, Temp2;
    IIC_Start();
    IIC_SendByte(0x90); //A0: 0      A1: 0
    Response92();
    IIC_SendByte(0x00); //temperature register
    Response92();
    IIC_Start();
    IIC_SendByte(0x91);
    Response92();
    Temp1 = IIC_ReadByte(); //most significant 8 bits
    Response00();
    Temp2 = IIC_ReadByte(); //least significant 8 bits
    noresponse00();
    IIC_Stop();
    Temp1 <<= 8;
    Temp1 |= Temp2;
    return Temp1;
}