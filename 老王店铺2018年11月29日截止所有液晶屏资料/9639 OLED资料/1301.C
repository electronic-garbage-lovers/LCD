//〖说明〗I2C总线驱动OLED 1301 芯片演示程序(用两个普通IO模拟I2C总线)   
02.//〖文件〗I2C.C ﹫2004/7/12   
03.// 作者：   
04. #include <AT89X51.H>   
05. #include "intrins.h"   
06. #include <bin2hex.h>   
07.    
08. #ifndef SDA   
09. #define SDA P1_3   
10. #define SCL P1_4   
11. #endif   
12.   
13.   
14. #define uchar unsigned char   
15. #define uint unsigned int   
16. #define Byte unsigned char   
17. #define Word unsigned int   
18. #define bool bit   
19. #define true 1   
20. #define false 0   
21. #define SomeNOP(); _nop_();//_nop_();_nop_();_nop_();    
22.   
23. extern uchar SystemError;   
24.    
25. /**--------------------------------------------------------------------------------  
26. 调用方式：void I2CStart(void) ﹫2001/07/0 4  
27. 函数说明：私有函数，I2C专用  
28. ---------------------------------------------------------------------------------*/   
29. void I2CStart(void)   
30. {   
31. EA=0;   
32. SDA=1; SCL=1; SomeNOP();//INI   
33. SDA=0; SomeNOP(); //START   
34. SCL=0;   
35. }   
36.   
37. /**--------------------------------------------------------------------------------  
38. 调用方式：void I2CStop(void) ﹫2001/07/0 4  
39. 函数说明：私有函数，I2C专用  
40. ---------------------------------------------------------------------------------*/   
41. void I2CStop(void)   
42. {   
43. SCL=0; SDA=0; SomeNOP(); //INI   
44. SCL=1; SomeNOP(); SDA=1; //STOP   
45. EA=1;   
46. }   
47.   
48. /**--------------------------------------------------------------------------------  
49. 调用方式：bit I2CAck(void) ﹫2001/07/0 4  
50. 函数说明：私有函数，I2C专用，等待从器件接收方的应答  
51. ---------------------------------------------------------------------------------*/   
52. bool WaitAck(void)   
53. {   
54. uchar errtime=255;//因故障接收方无ACK，超时值为255。   
55. SDA=1;SomeNOP();   
56. SCL=1;SomeNOP();   
57. while(SDA) {errtime--; if (!errtime) {I2CStop();SystemError=0x11;return false;}}   
58. SCL=0;   
59. return true;   
60.}   
61.   
62. /**--------------------------------------------------------------------------------  
63. 调用方式：void SendAck(void) ﹫2001/07/0 4  
64. 函数说明：私有函数，I2C专用，主器件为接收方，从器件为发送方时，应答信号。  
65. ---------------------------------------------------------------------------------*/   
66. /*void SendAck(void)  
67. {  
68. SDA=0; SomeNOP();  
69. SCL=1; SomeNOP();  
70. SCL=0;  
71. }  
72.*/   
73. /**--------------------------------------------------------------------------------  
74. 调用方式：void SendAck(void) ﹫2001/07/0 4  
75. 函数说明：私有函数，I2C专用，主器件为接收方，从器件为发送方时，非应答信号。  
76. --------------------------------------------------------------------------------*/   
77. /*void SendNotAck(void)  
78. {  
79. SDA=1; SomeNOP();  
80. SCL=1; SomeNOP();  
81. SCL=0;  
82. }  
83.*/   
84. /**--------------------------------------------------------------------------------  
85. 调用方式：void I2CSend(uchar ch) ﹫2001/07/0 5  
86. 函数说明：私有函数，I2C专用  
87. ---------------------------------------------------------------------------------*/   
88. void I2CSendByte(Byte ch)   
89. {   
90. uchar i=8;   
91. while (i--)   
92. {   
93. SCL=0;_nop_();   
94. SDA=(bit)(ch&0x80); ch=ch<<1; SomeNOP();    
95. SCL=1; SomeNOP();   
96. }   
97. SCL=0;   
98. }   
99.   
100. /**--------------------------------------------------------------------------------  
101. 调用方式：uchar I2CReceive(void) ﹫2001/07/0 5  
102. 函数说明：私有函数，I2C专用  
103. ---------------------------------------------------------------------------------*/   
104. /*Byte I2CReceiveByte(void)  
105. {  
106. uchar i=8;  
107. Byte ddata=0;  
108. SDA=1;  
109. while (i--)  
110. {  
111. ddata<<=1;  
112. SCL=0;SomeNOP();  
113. SCL=1;SomeNOP();  
114. ddata|=SDA;  
115. }  
116. SCL=0;  
117. return ddata;  
118. }  
119.*/    
120.const unsigned char code  LOGO[270]={   
121.    B00000000,B00000000,B00000000,B10000000,B11000000,B11100000,B11100000,B11110000,B11111000,   
122.    B01111000,B00111100,B00111100,B00011100,B00011110,B00011110,B00001110,B00001111,B00001111,   
123.    B00000111,B00000111,B00000111,B00000111,B10000111,B11000111,B11100111,B11100011,B11110011,   
124.    B11111011,B11111011,B11111111,B11111111,B11111110,B11111111,B11111111,B11111111,B00001110,   
125.    B00001110,B00001110,B00001110,B00011110,B00011100,B00111100,B00111100,B01111000,B11111000,   
126.    B11110000,B11110000,B11100000,B11000000,B10000000,B00000000,B00000000,B00000000,B00000000,   
127.                                                                                                 
128.    B11110000,B11111100,B11111111,B11111111,B00011111,B00000111,B00000011,B00000001,B00000000,   
129.    B00000000,B10000000,B11000000,B11000000,B11100000,B11110000,B11110000,B01111000,B00111100,   
130.    B10011100,B10011110,B11001111,B11100111,B11100111,B11110111,B11111111,B11111111,B11111111,   
131.    B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111110,   
132.    B01111110,B00111110,B00111110,B00011110,B00001110,B00001110,B00000110,B00000000,B00000000,   
133.    B00000000,B00000001,B00000011,B00001111,B00111111,B11111111,B11111110,B11111000,B11100000,   
134.                                                                                                 
135.    B00111111,B11111111,B11111111,B11111111,B11111000,B01111000,B00111100,B00111110,B10011110,   
136.    B11001111,B11100111,B11100111,B01110011,B01111001,B00111100,B10011100,B10011110,B11001111,   
137.    B11100111,B11110011,B01110011,B00111001,B10011100,B11011110,B11111111,B11111111,B11111111,   
138.    B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B00000000,   
139.    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,   
140.    B00000000,B00000000,B10000000,B11100000,B11111000,B11111111,B11111111,B01111111,B00011111,   
141.                                                                                                 
142.    B00000000,B00000000,B00000001,B00000001,B00001100,B00001110,B00001111,B00100111,B00110011,   
143.    B00110001,B00111000,B00011100,B10011110,B11001110,B11100111,B01100111,B01110011,B00111001,   
144.    B10011100,B11001100,B11001110,B11100111,B11110011,B11111011,B11111111,B11111111,B11011111,   
145.    B11011111,B11001111,B11000111,B11000111,B11000011,B11000001,B11000001,B11000000,B11100000,   
146.    B11100000,B11100000,B11110000,B11110000,B11110000,B11111000,B11111000,B11111100,B01111110,   
147.    B00111110,B00111111,B00011111,B00001111,B00001111,B00000111,B00000001,B00000000,B00000000,   
148.                                                                                                 
149.    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,   
150.    B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000000,B00000000,B00000011,   
151.    B00000011,B00000011,B00000011,B00000011,B00000011,B00000011,B00000011,B00000011,B00000011,   
152.    B00000011,B00000011,B00000011,B00000011,B00000011,B00000011,B00000011,B00000011,B00000011,   
153.    B00000011,B00000011,B00000001,B00000001,B00000001,B00000000,B00000000,B00000000,B00000000,   
154.    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};   
155./*const unsigned char code  T[42]={  
156.    B00001111,B00001111,B00001111,B00001111,B00001111,B11111111,B11111111,  
157.    B11111111,B11111111,B00001111,B00001111,B00001111,B00001111,B00001111,  
158.                                                                             
159.    B00000000,B00000000,B00000000,B00000000,B00000000,B11111111,B11111111,  
160.    B11111111,B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,  
161.                                                                             
162.    B00000000,B00000000,B00000000,B00000000,B00000000,B01111111,B01111111,  
163.    B01111111,B01111111,B00000000,B00000000,B00000000,B00000000,B00000000};  
164.const unsigned char code  C[48]={  
165.    B10000000,B11110000,B11111000,B11111100,B01111110,B00011110,B00001111,B00001111,  
166.    B00001111,B00001111,B00011111,B00111110,B11111110,B11111100,B01111000,B01100000,  
167.                                                                                       
168.    B11111111,B11111111,B11111111,B11111111,B00000000,B00000000,B00000000,B00000000,  
169.    B00000000,B00000000,B00000000,B00000000,B11000000,B11000000,B10000000,B10000000,  
170.                                                                                       
171.    B00000000,B00000111,B00001111,B00011111,B00111111,B00111100,B01111000,B01111000,  
172.    B01111000,B01111000,B01111100,B00111111,B00111111,B00011111,B00000111,B00000001};  
173.const unsigned char code  L[39]={  
174.    B11111111,B11111111,B11111111,B11111111,B00000000,B00000000,B00000000,  
175.    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,           
176.                                                                            
177.    B11111111,B11111111,B11111111,B11111111,B00000000,B00000000,B00000000,  
178.    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,           
179.                                                                            
180.    B01111111,B01111111,B01111111,B01111111,B01111000,B01111000,B01111000,  
181.    B01111000,B01111000,B01111000,B01111000,B01111000,B01111000}; */   
182.const unsigned char code OLED_O[36]={   
183.    B00000000,B00000000,B10000000,B10000000,B01000000,B01000000,B01000000,B01000000,B10000000,B10000000,B00000000,B00000000,   
184.    B11111000,B11111110,B00000011,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000011,B11111110,B11111000,   
185.    B00000111,B00011111,B00111000,B01000000,B10000000,B10000000,B10000000,B10000000,B01000000,B01110000,B00011111,B00000111};      
186.const unsigned char code OLED_L[36]={   
187.    B01000000,B11000000,B11000000,B01000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,   
188.    B00000000,B11111111,B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,   
189.    B10000000,B11111111,B11111111,B10000000,B10000000,B10000000,B10000000,B10000000,B10000000,B11000000,B00110000,B00000000};    
190.const unsigned char code OLED_E[36]={   
191.    B01000000,B11000000,B11000000,B01000000,B01000000,B01000000,B01000000,B01000000,B11000000,B11000000,B00000000,B00000000,   
192.    B00000000,B11111111,B11111111,B01000000,B01000000,B01000000,B01000000,B11111000,B00000000,B00000000,B00000011,B00000000,   
193.    B10000000,B11111111,B11111111,B10000000,B10000000,B10000000,B10000000,B10000011,B10000000,B11000000,B00110000,B00000000};    
194.const unsigned char code OLED_D[36]={   
195.    B00000000,B01000000,B11000000,B11000000,B01000000,B01000000,B01000000,B11000000,B10000000,B10000000,B00000000,B00000000,   
196.    B00000000,B00000000,B11111111,B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000011,B11111111,B11111000,   
197.    B00000000,B10000000,B11111111,B11111111,B10000000,B10000000,B10000000,B11000000,B01100000,B01111000,B00011111,B00000111};    
198.const unsigned char code T5X8[5]={B00000110,B10000010,B11111110,B10000010,B00000110};   
199.const unsigned char code C5X8[5]={B01111100,B10000010,B10000010,B10000010,B01000110};   
200.const unsigned char code L5X8[5]={B10000010,B11111110,B10000010,B10000000,B11000000};   
201.const unsigned char code O5X8[5]={B01111100,B10000010,B10000010,B10000010,B01111100};   
202.const unsigned char code R5X8[5]={B10000010,B11111110,B10001010,B00011010,B11100100};   
203.const unsigned char code P5X8[5]={B10000010,B11111110,B10010010,B00010010,B00001100};   
204.const unsigned char code A5X8[5]={B10000000,B11111000,B00100110,B11111000,B10000000};   
205.const unsigned char code I5X8[5]={B10000010,B10000010,B11111110,B10000010,B10000010};   
206.const unsigned char code N6X8[6]={B10000010,B11111110,B10011000,B00100010,B11111110,B00000010};    
207.   
208.void init()   
209.{   
210.    uchar   i;     
211.    P1_2=0;//Reset SSD1301   
212.    for(i=0;i<255;i++){;}   
213.    P1_2=1;//Reset SSD1301         
214.       
215.    I2CStart();   
216.    I2CSendByte(0x78);//Write the slave address   
217.    WaitAck();   
218.    I2CSendByte(0x80);//Write control byte for command   
219.    WaitAck();   
220.    I2CSendByte(0xc8);//Set COM output Scan Driection   
221.    WaitAck();   
222.    //I2CSendByte(0x80);//Write control byte for command   
223.    //WaitAck();   
224.    //I2CSendByte(0xa4);//Set entire display normal   
225.    //WaitAck();   
226.    I2CSendByte(0x80);//Write control byte for command   
227.    WaitAck();   
228.    I2CSendByte(0xaf);//Turn on OLED panel   
229.    WaitAck();   
230.    I2CSendByte(0x80);//Write control byte for command   
231.    WaitAck();   
232.    I2CSendByte(0xa1);//Set Segment Re-map   
233.    WaitAck();         
234.    //I2CSendByte(0x80);//Write control byte for command   
235.    //WaitAck();   
236.    //I2CSendByte(0xd1);//Set Icon mode on   
237.    //WaitAck();       
238.    I2CStop();     
239.}   
240.   
241./*void ClearScreen(unsigned char pstart,unsigned char pend,unsigned char cstart,unsigned char cend)  
242.{  
243.    unsigned char c,p;  
244.    for(p=pstart;p<pend;p++)  
245.    {  
246.        I2CStart();  
247.        I2CSendByte(0x78);//Write the slave address  
248.        WaitAck();  
249.        I2CSendByte(0x80);//Write control byte for command  
250.        WaitAck();  
251.        I2CSendByte(p|0xb0);//Set Page Address  
252.        WaitAck();  
253.        I2CSendByte(0x80);////Write control byte  
254.        WaitAck();  
255.        I2CSendByte(cstart&0x0f);//Set Lower Column Address  
256.        WaitAck();  
257.        I2CSendByte(0x80);////Write control byte  
258.        WaitAck();  
259.        I2CSendByte((cstart>>4)|0x10);//Set Higher Column Address  
260.        WaitAck();    
261.        I2CSendByte(0x40);//Write control byte for the following data  
262.        WaitAck();            
263.        for(c=cstart;c<cend;c++)  
264.        {             
265.            I2CSendByte(0);//Write 0 to all of the RAM  
266.            WaitAck();  
267.        }     
268.        I2CStop();                    
269.    }  
270.      
271.}*/    
272.void DelayMs(unsigned int number)    
273.{   
274.    unsigned char temp;    
275.    for(;number!=0;number--)    
276.    {   
277.        for(temp=112;temp!=0;temp--){}   
278.    }   
279.}   
280.void WriteData(unsigned char *char_data,unsigned char c_start,unsigned char c_end,   
281.           unsigned char p_start,unsigned char p_end,bool vscroll)   
282.{   
283.    unsigned char c,p,csize=c_end-c_start;   
284.       
285.    for(p=p_start;p<p_end;p++)   
286.    {   
287.        I2CStart();   
288.        I2CSendByte(0x78);//Write the slave address   
289.        WaitAck();   
290.        I2CSendByte(0x80);//Write control byte for command   
291.        WaitAck();   
292.        I2CSendByte(p|0xb0);//Set Page Address   
293.        WaitAck();   
294.        I2CSendByte(0x80);////Write control byte   
295.        WaitAck();   
296.        I2CSendByte(c_start&0x0f);//Set Lower Column Address   
297.        WaitAck();   
298.        I2CSendByte(0x80);////Write control byte   
299.        WaitAck();   
300.        I2CSendByte((c_start>>4)|0x10);//Set Higher Column Address   
301.        WaitAck();     
302.        I2CSendByte(0x40);//Write control byte for the following data   
303.        WaitAck();     
304.        if(vscroll)   
305.        {   
306.            I2CSendByte(0); //Clear the first column   
307.            WaitAck();   
308.        }                  
309.        for(c=0;c<csize;c++)   
310.        {   
311.            if(char_data==0)   
312.            {   
313.                I2CSendByte(0);//Write 0 to GDDRAM                 
314.                WaitAck();   
315.            }   
316.            else    
317.            {   
318.                I2CSendByte(char_data[(p-p_start)*csize+c]);//Write Data to GDDRAM                 
319.                WaitAck();                 
320.            }   
321.        }              
322.        I2CStop();                     
323.    }   
324.       
325.}    
326.   
327.   
328.void main()   
329. {   
330.    unsigned int  i,k=0;       
331.    unsigned char j=0;   
332.    init();        
333.       
334.    while(1)   
335.    {   
336.        //WriteData(0,38,40,0,1,0);//Clear Screen    
337.        //WriteData(0,68,132,0,1,0);//Clear Screen     
338.           
339.        /*I2CStart();  
340.        I2CSendByte(0x78);//Write the slave address  
341.        WaitAck();            
342.        I2CSendByte(0x80);//Write control byte for command  
343.        WaitAck();  
344.        I2CSendByte(0xa6);//Set Nomarl/Inverse Display  
345.        WaitAck();  
346.        I2CStop();*/   
347.        WriteData(0,0,132,0,8,0);//Clear Screen                
348.        /*WriteData(T5X8,k+20,k+25,0,1,1);  
349.        WriteData(C5X8,k+26,k+31,0,1,1);  
350.        WriteData(L5X8,k+32,k+37,0,1,1);          
351.        WriteData(C5X8,k+45,k+50,0,1,1);  
352.        WriteData(O5X8,k+51,k+56,0,1,1);  
353.        WriteData(R5X8,k+57,k+62,0,1,1);  
354.        WriteData(P5X8,k+63,k+68,0,1,1);    */   
355.        /*WriteData(O5X8,k+69,k+74,0,1,1);  
356.        WriteData(R5X8,k+75,k+80,0,1,1);  
357.        WriteData(A5X8,k+81,k+86,0,1,1);          
358.        WriteData(T5X8,k+87,k+92,0,1,1);  
359.        WriteData(I5X8,k+93,k+98,0,1,1);  
360.        WriteData(O5X8,k+99,k+104,0,1,1);  
361.        WriteData(N6X8,k+105,k+111,0,1,1);*/   
362.        //k=k+1;           
363.        for(i=0;i<46;i++)    
364.        {   
365.            if(i==45)DelayMs(20000);               
366.            WriteData(LOGO,i,i+54,1,6,1);          
367.            WriteData(T5X8,i+3,i+8,0,1,1);   
368.            WriteData(C5X8,i+9,i+14,0,1,1);   
369.            WriteData(L5X8,i+15,i+20,0,1,1);           
370.            WriteData(C5X8,i+28,i+33,0,1,1);   
371.            WriteData(O5X8,i+34,i+39,0,1,1);   
372.            WriteData(R5X8,i+40,i+45,0,1,1);   
373.            WriteData(P5X8,i+46,i+51,0,1,1);       
374.        }   
375.        /*WriteData(T,43,57,0,3,0);   
376.        WriteData(C,60,76,0,3,0);     
377.        WriteData(L,80,93,0,3,0);             
378.        for(j=0;j<65;j++)  
379.        {             
380.            DelayMs(200);         
381.            I2CStart();  
382.            I2CSendByte(0x78);//Write the slave address  
383.            WaitAck();    
384.            I2CSendByte(0x80);//Write control byte for command  
385.            WaitAck();  
386.            I2CSendByte(0xd3);//Set Display Offset    
387.            WaitAck();                                    
388.            I2CSendByte(0x80);//Write control byte for command  
389.            WaitAck();  
390.            I2CSendByte(j);//Set Display Offset  
391.            if(j==12)DelayMs(10000);      
392.            WaitAck();    
393.            I2CStop();  
394.        }*/   
395.        //DelayMs(6000);           
396.           
397.        WriteData(0,0,132,0,8,0);//Clear Screen   
398.        for(i=0;i<132;i++)   
399.        {   
400.            if(i==40)DelayMs(20000);       
401.            WriteData(OLED_O,i,i+12,1,4,1);    
402.            WriteData(OLED_L,i+15,i+27,1,4,1);     
403.            WriteData(OLED_E,i+30,i+42,1,4,1);     
404.            WriteData(OLED_D,i+45,i+57,1,4,1);   
405.            WriteData(T5X8,i+6,i+11,0,1,1);   
406.            WriteData(C5X8,i+12,i+17,0,1,1);   
407.            WriteData(L5X8,i+18,i+23,0,1,1);           
408.            WriteData(C5X8,i+31,i+36,0,1,1);   
409.            WriteData(O5X8,i+37,i+42,0,1,1);   
410.            WriteData(R5X8,i+43,i+48,0,1,1);   
411.            WriteData(P5X8,i+49,i+54,0,1,1);       
412.               
413.        }      
414.        //DelayMs(3000);   
415.        /*I2CStart();  
416.        I2CSendByte(0x78);//Write the slave address  
417.        WaitAck();            
418.        I2CSendByte(0x80);//Write control byte for command  
419.        WaitAck();  
420.        I2CSendByte(0xa7);//Set Nomarl/Inverse Display  
421.        WaitAck();  
422.        I2CStop();  
423.        ClearScreen();  
424.        WriteData(OLED_O,40,52,3,6,0);    
425.        WriteData(OLED_L,55,67,2,5,0);    
426.        WriteData(OLED_E,70,82,1,4,0);    
427.        WriteData(OLED_D,85,97,0,3,0);    
428.        DelayMs(5000);  
429.        ClearScreen();  
430.        WriteData(OLED_O,40,52,0,3,0);    
431.        WriteData(OLED_L,55,67,1,4,0);    
432.        WriteData(OLED_E,70,82,2,5,0);    
433.        WriteData(OLED_D,85,97,3,7,0);    
434.        DelayMs(5000);*/   
435.        /*ClearScreen();  
436.        WriteData(OLED_O,40,52,2,5,0);    
437.        WriteData(OLED_L,55,67,2,5,0);    
438.        WriteData(OLED_E,70,82,2,5,0);    
439.        WriteData(OLED_D,85,97,2,5,0);    
440.        DelayMs(5000);  */   
441.    }          
442. }   
443.  
