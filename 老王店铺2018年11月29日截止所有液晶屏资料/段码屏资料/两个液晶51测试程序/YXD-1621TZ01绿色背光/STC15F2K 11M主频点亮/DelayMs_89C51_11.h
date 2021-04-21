/*--- 6M主频，STC15F104E单片机的毫秒级延时 ---*/


void DelayMs(unsigned char count)
{
    unsigned char i,j;                                                                                
    for(i=0;i<count;i++)                                                                    
       {
	     for(j=0;j<225;j++);  
	     for(j=0;j<76;j++);  
       }                                                                                     
}


/*

void DelayS(unsigned char count)
{
while(count--)
 {
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 DelayMs(250);
 }
}


*/
