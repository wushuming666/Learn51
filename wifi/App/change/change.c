#include "public.h"
#include "lcd1602.h"
#include "change.h"

void change(u8 ch, float *maxn, u8 *path, u8 *idx){ //�µ���ֵ
	int res;
	u8 i, k;
	u8 show_path[8];
	
	if (ch == 'A') //��ʼ�༭ģʽ
	{
		lcd1602_clear();
		delay_ms(10);
		lcd1602_show_string(0, 0, "@.@new\0");	
		delay_ms(10);
	}

	//�˳��༭ģʽ 
	else if (ch == 'B')	
	{
		res = 0;
		for (k = 0; k < 5; k ++) 	 
		{
			if (path[k] == '\0') break;
			if (path[k] == '.') continue; 
			res += path[k] - '0';
			res *= 10;
		}
		*idx = 0;
		*maxn = 1.0 * res / 100;				//���˸�0 + С����
	}

	//������ֵģʽ
	else
	{
		if (ch == 'C') 	   // ɾ��
		{
			*idx = *idx - 1;
			path[*idx] = '\0';
		}	
		else
		{
			path[*idx] = ch;
			*idx = *idx + 1;
			//path[*idx] = '\0';
		}

		for (k = 0; k < 5; k++)
		{
			//if (path[k] == '\0') break;
			show_path[k] = path[k];
		}
		//show_path[k] = '\0';
		lcd1602_show_string(0, 1, "              ");	 //���ڸĳ�����!!!!!!
		delay_ms(10);
		lcd1602_show_string(0, 1, show_path);
		delay_ms(10);
	}
}
