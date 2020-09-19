#ifndef _INFRARED_H_
#define _INFRARED_H_

void IrInit();
void ReadIr() __interrupt(2);

#endif
