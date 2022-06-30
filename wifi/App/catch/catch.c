#include "catch.h"

int catch_temp_value;
//u8 temp_buf[6];

void mycatch(u8 *temp_buf, int* old){
//	ds18b20_init();
	catch_temp_value = ds18b20_read_temperture() * 10;//保留温度值小数后一位
	*old = catch_temp_value;
	if (catch_temp_value < 0)//负温度
	{
		catch_temp_value = -catch_temp_value;
		temp_buf[0] = '-';//显示负号	
	}
	else
		temp_buf[0] = ' ';//不显示
	temp_buf[1] = catch_temp_value / 1000 + '0';//百位
	temp_buf[2] = catch_temp_value % 1000 / 100 + '0';//十位
	temp_buf[3] = catch_temp_value % 1000 % 100 / 10 + '0';//个位
	temp_buf[4] = '.';
	temp_buf[5] = catch_temp_value % 1000 % 100 % 10 + '0';//小数点后一位
	temp_buf[6] = '\0';
	return ;
//	return temp_buf;
}