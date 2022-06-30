#include "wifi.h"
#include "ds18b20.h"
#include "uart.h"
#include "smg.h"
#include "change.h"

//定义LED1管脚													 
sbit LED1=P2^0;

//ESP8266 WIFI发送AT指令
//pbuf：AT指令，字符串格式，如："AT"
void ESP8266_SendCmd(u8 *pbuf)
{
	while(*pbuf!='\0') //遇到空格跳出循环	
	{
		UART_SendData(*pbuf);
		delay_10us(5);
		pbuf++;	
	}
	delay_10us(5);
	UART_SendData('\r');//回车
	delay_10us(5);
	UART_SendData('\n');//换行
	delay_ms(10);
}

//ESP8266 WIFI发送数据到APP
//pbuf：数据
void ESP8266_SendData(u8 *pbuf)
{
	ESP8266_SendCmd("AT+CIPSEND=0,7");
	while(*pbuf!='\0') //遇到空格跳出循环	
	{
		UART_SendData(*pbuf);
		delay_10us(5);
		pbuf++;	
	}
	UART_SendData('\n');//换行	
//	delay_ms(10);
}

//ESP8266-WIFI模块工作模式初始化
void ESP8266_ModeInit(void)
{
	ESP8266_SendCmd("AT+CWMODE=2");//设置路由器模式 1 staTIon模式 2 AP点 路由器模式 3 station+AP混合模式
	ESP8266_SendCmd("AT+CWSAP=\"ESP8266\",\"123456\",11,0"); //设置WIFI热点名及密码
	ESP8266_SendCmd("AT+CIPAP=\"192.168.4.1\"");
//	ESP8266_SendCmd("AT+RST");//重新启动wifi模块
//	delay_ms(2000);
	ESP8266_SendCmd("AT+CIPMUX=1");	//开启多连接模式，允许多个各客户端接入
	ESP8266_SendCmd("AT+CIPSERVER=1,8080");	//启动TCP/IP 端口为8080 实现基于网络控制	
} 

//WIFI控制初始化
void wifi_control_init(void)
{
	UART_Init();
	ds18b20_init();//初始化DS18B20
	ESP8266_ModeInit();
	ES=1;//允许串口中断
}

//WIFI控制
void wifi_control(void)
{
	static u16 i=0, j;
	u8 temp_buf[5];
	int temp_value;
	u8 wifi_send_buf[7];
#if 1
	{
		i++;		
		if(i%200==0)//间隔一段时间将读取的温度发送到APP
		{
			ESP8266_SendData("yes\0");//通过串口发送温度数据到APP
		}			
	}	
#endif
}




