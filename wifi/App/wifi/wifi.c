#include "wifi.h"
#include "ds18b20.h"
#include "uart.h"
#include "smg.h"
#include "change.h"

//����LED1�ܽ�													 
sbit LED1=P2^0;

//ESP8266 WIFI����ATָ��
//pbuf��ATָ��ַ�����ʽ���磺"AT"
void ESP8266_SendCmd(u8 *pbuf)
{
	while(*pbuf!='\0') //�����ո�����ѭ��	
	{
		UART_SendData(*pbuf);
		delay_10us(5);
		pbuf++;	
	}
	delay_10us(5);
	UART_SendData('\r');//�س�
	delay_10us(5);
	UART_SendData('\n');//����
	delay_ms(10);
}

//ESP8266 WIFI�������ݵ�APP
//pbuf������
void ESP8266_SendData(u8 *pbuf)
{
	ESP8266_SendCmd("AT+CIPSEND=0,7");
	while(*pbuf!='\0') //�����ո�����ѭ��	
	{
		UART_SendData(*pbuf);
		delay_10us(5);
		pbuf++;	
	}
	UART_SendData('\n');//����	
//	delay_ms(10);
}

//ESP8266-WIFIģ�鹤��ģʽ��ʼ��
void ESP8266_ModeInit(void)
{
	ESP8266_SendCmd("AT+CWMODE=2");//����·����ģʽ 1 staTIonģʽ 2 AP�� ·����ģʽ 3 station+AP���ģʽ
	ESP8266_SendCmd("AT+CWSAP=\"ESP8266\",\"123456\",11,0"); //����WIFI�ȵ���������
	ESP8266_SendCmd("AT+CIPAP=\"192.168.4.1\"");
//	ESP8266_SendCmd("AT+RST");//��������wifiģ��
//	delay_ms(2000);
	ESP8266_SendCmd("AT+CIPMUX=1");	//����������ģʽ�����������ͻ��˽���
	ESP8266_SendCmd("AT+CIPSERVER=1,8080");	//����TCP/IP �˿�Ϊ8080 ʵ�ֻ����������	
} 

//WIFI���Ƴ�ʼ��
void wifi_control_init(void)
{
	UART_Init();
	ds18b20_init();//��ʼ��DS18B20
	ESP8266_ModeInit();
	ES=1;//�������ж�
}

//WIFI����
void wifi_control(void)
{
	static u16 i=0, j;
	u8 temp_buf[5];
	int temp_value;
	u8 wifi_send_buf[7];
#if 1
	{
		i++;		
		if(i%200==0)//���һ��ʱ�佫��ȡ���¶ȷ��͵�APP
		{
			ESP8266_SendData("yes\0");//ͨ�����ڷ����¶����ݵ�APP
		}			
	}	
#endif
}




