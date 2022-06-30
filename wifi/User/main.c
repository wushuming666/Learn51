#include "public.h"
#include "ds18b20.h"
#include "reg52.h"
#include "intrins.h"
#include "lcd1602.h"
#include "catch.h"
#include "sound.h"
#include "wifi.h"
#include "uart.h"
#include "change.h"
#include "catch.h"
#include "stdio.h"

#if 1
u8 i_t = 0, j, k;
int main_idx = 0, flag = 0, main_max, idx = 0;
int temp_value;
float mymaxn = 29.7;
u8 main_temp_buf[7], show_max[8];
sbit LED1=P2^0;	//��P2.0�ܽŶ���ΪLED1
//u8 new_val[16];
#endif

void main()
{
	//��ʼ��
	ds18b20_init();//��ʼ��DS18B20
	lcd1602_init();
	wifi_control_init();
	
#if 1
	while(1)
	{
		if (flag) //�༭�¶�ģʽ
		{
			delay_ms(10);
			continue; 		 
		}
						
		i_t++;
		if(i_t % 50 == 0)//���һ��ʱ���ȡ�¶�ֵ�����ʱ��Ҫ�����¶ȴ�����ת���¶�ʱ��
		{
			i_t = 0;
			lcd1602_clear();
			for (j =0 ; j < 5; j ++)
			{
				lcd1602_show_string(0, 0, "now:");
				lcd1602_show_string(0, 1, "max:");
			}
			delay_ms(10);
			mycatch(main_temp_buf, &temp_value);	  //���ص�ǰ�¶� �ֱ������� ����
			for (j = 0; j < 5; j ++)
			{
				lcd1602_show_string(4, 0, main_temp_buf);
				main_max = mymaxn * 10;
				show_max[0] = main_max / 100;
				show_max[1] = main_max / 10 % 10;
				show_max[2] = '.';
				show_max[3] = main_max % 10;
				show_max[4] = '\0';
				for (k = 0; k < 4; k ++)
				{
					if (show_max[k] == '.') continue;
					show_max[k] += '0';
				}
				lcd1602_show_string(4, 1, show_max);
				delay_ms(10);
			}								 
			check(temp_value, mymaxn);
		}
		wifi_control();
	}
#endif
}

//�����жϷ�����
//�����ֻ�APP���͵��źź���ư�����Դ
#if 1
void UART_IRQn() interrupt 4
{
	static u8 i=0;
	static u8 mypath[5];
	u8 j = 0;
	u8 p[2];

	if(RI)
	{
		RI=0;
		UART_RX_BUF[i]=SBUF;//��ȡ���յ�������
		if(UART_RX_BUF[0]=='+')i++;
		else i=0;
		if(i==10)
		{
			i=0;
			//WIFI����
			//UART_RX_BUF[9]
			LED1 = 0;
			if ( UART_RX_BUF[9] == 'A') //����༭ģʽ
			{
				lcd1602_clear();
				delay_ms(10);
				idx = 0;
				for (k = 0; k < 5; k++) mypath[k] = '\0';
				flag = 1;
				change('A', &mymaxn, mypath, &idx);
			}			
			else if (UART_RX_BUF[9] == 'B') //�˳��༭ģʽ
			{
				flag = 0;
				change('B', &mymaxn, mypath, &idx);
			}
			else if ((UART_RX_BUF[9] >= '2' && UART_RX_BUF[9] <= '9') || (UART_RX_BUF[9] >= 'C' && UART_RX_BUF[9] <= 'D') || UART_RX_BUF[9] == '.' )
				change(UART_RX_BUF[9], &mymaxn, mypath, &idx);
			LED1 = 1;
		}			
	}	
}
#endif