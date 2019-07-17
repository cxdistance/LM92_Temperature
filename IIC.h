#ifndef _I2C_H
#define _I2C_H

#include <reg52.h>
sbit SCL = P2 ^ 1;
sbit SDA = P2 ^ 0;

void IIC_Start(void);
void IIC_Stop(void);
unsigned char IIC_SendByte(unsigned char dat);
unsigned char IIC_ReadByte(void);
unsigned int ReadTemp(void);
void Delay10us(void);
void Response92(void);
void Response00(void);
void noresponse00(void);
#endif
