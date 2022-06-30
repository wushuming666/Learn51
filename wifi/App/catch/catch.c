#include "catch.h"

int catch_temp_value;
//u8 temp_buf[6];

void mycatch(u8 *temp_buf, int* old){
//	ds18b20_init();
	catch_temp_value = ds18b20_read_temperture() * 10;//�����¶�ֵС����һλ
	*old = catch_temp_value;
	if (catch_temp_value < 0)//���¶�
	{
		catch_temp_value = -catch_temp_value;
		temp_buf[0] = '-';//��ʾ����	
	}
	else
		temp_buf[0] = ' ';//����ʾ
	temp_buf[1] = catch_temp_value / 1000 + '0';//��λ
	temp_buf[2] = catch_temp_value % 1000 / 100 + '0';//ʮλ
	temp_buf[3] = catch_temp_value % 1000 % 100 / 10 + '0';//��λ
	temp_buf[4] = '.';
	temp_buf[5] = catch_temp_value % 1000 % 100 % 10 + '0';//С�����һλ
	temp_buf[6] = '\0';
	return ;
//	return temp_buf;
}