/* https://blog.csdn.net/qq_42012736/article/details/80555951 */

unsigned char IrValue[4];//用于存储数据码，对应前两个是地址位，后两个是数据位和校验位
unsigned char Time;//计时变量，
bit ture //校验变量，表示是否校验通过，如果不能成功校验，很可能发生了错误

sbit IRIN = P3 ^ 3;

void IrInit()
{
    IT0=1;//下降沿触发
    EX0=1;//打开中断0允许
    EA=1;   //打开总中断

    IRIN=1;//初始化红外端口
}

void ReadIr() interrupt 0
{
    unsigned char j,k;//循环控制变量
    unsigned int err;
    Time=0;                  
    delay(700); //7ms
    if(IRIN==0)     //确认是否真的接收到正确的信号；与开关消抖类似
    {    

        err=1000;               //1000*10us=10ms,超过说明接收到错误的信号.
        //这里10ms是大于9ms的，这么做更保险一点，下面的做法类似

        //读取数据的头，即开始信号
        while((IRIN==0)&&(err>0))   //等待前面9ms的低电平过去         
        {           
            delay(1);
            err--;
        } 
        if(IRIN==1)         //开始信号校验成功      
        {
            err=500; //500*10us=5ms；
            while((IRIN==1)&&(err>0))        //等待4.5ms的起始高电平过去
            {
                delay(1);
                err--;
            }
            for(k=0;k<4;k++)        //共有4组数据
            {               
                for(j=0;j<8;j++)    //接收一组数据
                {

                    err=60; //校验上限600us 
                    while((IRIN==0)&&(err>0))//等待信号前面的560us低电平过去
                    {
                        delay(1);
                        err--;
                    }
                    err=500;
                    while((IRIN==1)&&(err>0))    //计算高电平的时间长度。
                    {
                        delay(10);   //0.1ms
                        Time++;
                        err--;
                        if(Time>30) //超时太久时退出
                        {
                            return;
                        }
                    }
                    IrValue[k]>>=1;  //k表示第几组数据
                    if(Time>=8)         //如果高电平出现大于565us，那么是1
                        //注意这里高电平理论时间长是1680us，低电平的是560us
                        //取Time大于6来检验当然就可以了，但不太保险，网上各类教程都是娶了一个中间值8
                    {
                        IrValue[k]|=0x80;//在最高为写1，通过按位与运算实现
                        //如果不写默认是0；
                    }
                    Time=0;     //用完时间要重新赋值                         
                }
            }
        }
        //下面要对数据进行校验，校验的方式位判断第四位数据是否位第三位数据吗的反码
        if(IrValue[2]!=~IrValue[3])
        {
            ture=1;
        }
        else
        {
            ture=0;
        }
    }           
}
