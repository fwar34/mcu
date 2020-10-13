#ifndef _DHT_11_H_
#define _DHT_11_H_

extern unsigned char dht11_data[5];//湿度十位，湿度个位，温度十位，温度个位，是否显示的标志
void dht11_read_data();
void read_dht11_state_0();

#endif
