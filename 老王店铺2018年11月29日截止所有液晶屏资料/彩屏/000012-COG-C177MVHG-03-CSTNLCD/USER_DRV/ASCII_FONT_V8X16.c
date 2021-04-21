//从上到下1字节(分上下部分),在从左向右8字节,
//  (0) !(1) "(2) #(3) $(4) %(5) &(6) `(7) ((8) )(9) *(10) +(11) ,(12) -(13) .(14) /(15) 0(16) 1(17) 2(18) 3(19) 4(20) 5(21) 6(22) 7(23) 8(24) 9(25) :(26) ;(27) <(28) =(29) >(30) ?(31) @(32) A(33) B(34) C(35) D(36) E(37) F(38) G(39) H(40) I(41) J(42) K(43) L(44) M(45) N(46) O(47) P(48) Q(49) R(50) S(51) T(52) U(53) V(54) W(55) X(56) Y(57) Z(58) [(59) \(60) ](61) ^(62) _(63) '(64) a(65) b(66) c(67) d(68) e(69) f(70) g(71) h(72) i(73) j(74) k(75) l(76) m(77) n(78) o(79) p(80) q(81) r(82) s(83) t(84) u(85) v(86) w(87) x(88) y(89) z(90) {(91) |(92) }(93) ~(94)
const unsigned char ASCII_16X8[][16]=
{
/* 
  (0) !(1) "(2) #(3) $(4) %(5) &(6) '(7) ((8) )(9) *(10) +(11) ,(12) -(13) .(14) /(15)
 0(16) 1(17) 2(18) 3(19) 4(20) 5(21) 6(22) 7(23) 8(24) 9(25) :(26) ;(27) <(28) =(29) >(30) ?(31)
 @(32) A(33) B(34) C(35) D(36) E(37) F(38) G(39) H(40) I(41) J(42) K(43) L(44) M(45) N(46) O(47)
 P(48) Q(49) R(50) S(51) T(52) U(53) V(54) W(55) X(56) Y(57) Z(58) [(59) \(60) ](61) ^(62) _(63)
 `(64) a(65) b(66) c(67) d(68) e(69) f(70) g(71) h(72) i(73) j(74) k(75) l(76) m(77) n(78) o(79)
 p(80) q(81) r(82) s(83) t(84) u(85) v(86) w(87) x(88) y(89) z(90) {(91) |(92) }(93) ~(94)
*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x33,0x00,0x00,0x00,0x00,0x00,0x00},/*"!",1*/

{0x00,0x00,0x02,0x00,0x0C,0x00,0x10,0x00,0x02,0x00,0x0C,0x00,0x10,0x00,0x00,0x00},/*""",2*/

{0x00,0x00,0x78,0x04,0xC0,0x3F,0x40,0x04,0x78,0x04,0xC0,0x3F,0x40,0x04,0x00,0x00},/*"#",3*/

{0x00,0x00,0x30,0x1E,0x08,0x21,0xFC,0xFF,0x88,0x20,0x88,0x20,0x70,0x18,0x00,0x00},/*"$",4*/

{0x00,0x00,0x00,0x1E,0x18,0x21,0x60,0x1E,0x80,0x03,0xF0,0x0C,0x08,0x31,0xF0,0x00},/*"%",5*/

{0x00,0x10,0x00,0x21,0x00,0x27,0x70,0x19,0x88,0x2C,0x08,0x23,0xF0,0x21,0x00,0x1E},/*"&",6*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x12,0x00,0x00,0x00},/*"'",7*/

{0x00,0x00,0x02,0x40,0x04,0x20,0x18,0x18,0xE0,0x07,0x00,0x00,0x00,0x00,0x00,0x00},/*"(",8*/

{0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x07,0x18,0x18,0x04,0x20,0x02,0x40,0x00,0x00},/*")",9*/

{0x00,0x00,0x40,0x02,0x40,0x02,0x80,0x01,0xF0,0x0F,0x80,0x01,0x40,0x02,0x40,0x02},/*"*",10*/

{0x00,0x01,0x00,0x01,0x00,0x01,0xE0,0x0F,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00},/*"+",11*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x90,0x00,0x00},/*",",12*/

{0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00},/*"-",13*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00},/*".",14*/

{0x00,0x00,0x04,0x00,0x38,0x00,0xC0,0x00,0x00,0x07,0x00,0x18,0x00,0x60,0x00,0x00},/*"/",15*/

{0x00,0x00,0xE0,0x0F,0x10,0x10,0x08,0x20,0x08,0x20,0x10,0x10,0xE0,0x0F,0x00,0x00},/*"0",16*/

{0x00,0x00,0x00,0x20,0x00,0x20,0xF8,0x3F,0x10,0x20,0x10,0x20,0x00,0x00,0x00,0x00},/*"1",17*/

{0x00,0x00,0xF0,0x30,0x08,0x21,0x08,0x22,0x08,0x24,0x08,0x28,0x70,0x30,0x00,0x00},/*"2",18*/

{0x00,0x00,0x70,0x1C,0x88,0x22,0x08,0x21,0x08,0x21,0x08,0x20,0x30,0x18,0x00,0x00},/*"3",19*/

{0x00,0x24,0x00,0x24,0xF8,0x3F,0x30,0x24,0x40,0x24,0x80,0x05,0x00,0x06,0x00,0x00},/*"4",20*/

{0x00,0x00,0x08,0x0E,0x08,0x11,0x88,0x20,0x88,0x20,0x88,0x20,0xF8,0x19,0x00,0x00},/*"5",21*/

{0x00,0x00,0x00,0x1F,0x90,0x20,0x88,0x20,0x88,0x20,0x10,0x11,0xE0,0x0F,0x00,0x00},/*"6",22*/

{0x00,0x00,0x18,0x00,0x68,0x00,0x88,0x01,0x08,0x3E,0x08,0x00,0x18,0x00,0x00,0x00},/*"7",23*/

{0x00,0x00,0x70,0x1C,0x88,0x22,0x08,0x21,0x08,0x21,0x88,0x22,0x70,0x1C,0x00,0x00},/*"8",24*/

{0x00,0x00,0xE0,0x0F,0x10,0x11,0x08,0x22,0x08,0x22,0x08,0x12,0xF0,0x01,0x00,0x00},/*"9",25*/

{0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x30,0xC0,0x30,0x00,0x00,0x00,0x00,0x00,0x00},/*":",26*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},/*";",27*/

{0x00,0x00,0x08,0x20,0x10,0x10,0x20,0x08,0x40,0x04,0x80,0x02,0x00,0x01,0x00,0x00},/*"<",28*/

{0x00,0x00,0x40,0x02,0x40,0x02,0x40,0x02,0x40,0x02,0x40,0x02,0x40,0x02,0x00,0x00},/*"=",29*/

{0x00,0x00,0x00,0x01,0x80,0x02,0x40,0x04,0x20,0x08,0x10,0x10,0x08,0x20,0x00,0x00},/*">",30*/

{0x00,0x00,0x70,0x00,0x88,0x00,0x08,0x37,0x08,0x30,0x48,0x00,0x70,0x00,0x00,0x00},/*"?",31*/

{0x00,0x00,0xE0,0x17,0x10,0x28,0xE8,0x2F,0x28,0x28,0xC8,0x27,0x30,0x18,0xC0,0x07},/*"@",32*/

{0x00,0x20,0x00,0x38,0x00,0x27,0xE0,0x02,0x38,0x02,0xC0,0x23,0x00,0x3C,0x00,0x20},/*"A",33*/

{0x00,0x00,0x00,0x0E,0x70,0x11,0x88,0x20,0x88,0x20,0x88,0x20,0xF8,0x3F,0x08,0x20},/*"B",34*/

{0x00,0x00,0x38,0x08,0x08,0x10,0x08,0x20,0x08,0x20,0x08,0x20,0x30,0x18,0xC0,0x07},/*"C",35*/

{0x00,0x00,0xE0,0x0F,0x10,0x10,0x08,0x20,0x08,0x20,0x08,0x20,0xF8,0x3F,0x08,0x20},/*"D",36*/

{0x00,0x00,0x10,0x18,0x08,0x20,0xE8,0x23,0x88,0x20,0x88,0x20,0xF8,0x3F,0x08,0x20},/*"E",37*/

{0x00,0x00,0x10,0x00,0x08,0x00,0xE8,0x03,0x88,0x00,0x88,0x20,0xF8,0x3F,0x08,0x20},/*"F",38*/

{0x00,0x00,0x00,0x02,0x38,0x1E,0x08,0x22,0x08,0x20,0x08,0x20,0x30,0x18,0xC0,0x07},/*"G",39*/

{0x08,0x20,0xF8,0x3F,0x08,0x21,0x00,0x01,0x00,0x01,0x08,0x21,0xF8,0x3F,0x08,0x20},/*"H",40*/

{0x00,0x00,0x00,0x00,0x08,0x20,0x08,0x20,0xF8,0x3F,0x08,0x20,0x08,0x20,0x00,0x00},/*"I",41*/

{0x00,0x00,0x08,0x00,0x08,0x00,0xF8,0x7F,0x08,0x80,0x08,0x80,0x00,0x80,0x00,0xC0},/*"J",42*/

{0x00,0x00,0x08,0x20,0x18,0x38,0x28,0x26,0xC0,0x01,0x88,0x20,0xF8,0x3F,0x08,0x20},/*"K",43*/

{0x00,0x00,0x00,0x30,0x00,0x20,0x00,0x20,0x00,0x20,0x08,0x20,0xF8,0x3F,0x08,0x20},/*"L",44*/

{0x00,0x00,0x08,0x20,0xF8,0x3F,0xF8,0x01,0x00,0x3E,0xF8,0x01,0xF8,0x3F,0x08,0x20},/*"M",45*/

{0x08,0x00,0xF8,0x3F,0x08,0x18,0x00,0x07,0xC0,0x00,0x30,0x20,0xF8,0x3F,0x08,0x20},/*"N",46*/

{0x00,0x00,0xE0,0x0F,0x10,0x10,0x08,0x20,0x08,0x20,0x08,0x20,0x10,0x10,0xE0,0x0F},/*"O",47*/

{0x00,0x00,0xF0,0x00,0x08,0x01,0x08,0x01,0x08,0x01,0x08,0x21,0xF8,0x3F,0x08,0x20},/*"P",48*/

{0x00,0x00,0xE0,0x4F,0x10,0x50,0x08,0x30,0x08,0x28,0x08,0x28,0x10,0x10,0xE0,0x0F},/*"Q",49*/

{0x00,0x20,0x70,0x30,0x88,0x0C,0x88,0x03,0x88,0x00,0x88,0x20,0xF8,0x3F,0x08,0x20},/*"R",50*/

{0x00,0x00,0x38,0x1C,0x08,0x22,0x08,0x21,0x08,0x21,0x88,0x20,0x70,0x38,0x00,0x00},/*"S",51*/

{0x00,0x00,0x18,0x00,0x08,0x00,0x08,0x20,0xF8,0x3F,0x08,0x20,0x08,0x00,0x18,0x00},/*"T",52*/

{0x08,0x00,0xF8,0x1F,0x08,0x20,0x00,0x20,0x00,0x20,0x08,0x20,0xF8,0x1F,0x08,0x00},/*"U",53*/

{0x08,0x00,0x38,0x00,0xC8,0x01,0x00,0x0E,0x00,0x38,0x88,0x07,0x78,0x00,0x08,0x00},/*"V",54*/

{0x00,0x00,0x08,0x00,0xF8,0x03,0x00,0x3E,0xF8,0x01,0x00,0x3E,0xF8,0x03,0x08,0x00},/*"W",55*/

{0x08,0x20,0x18,0x30,0x68,0x2C,0x80,0x03,0x80,0x03,0x68,0x2C,0x18,0x30,0x08,0x20},/*"X",56*/

{0x00,0x00,0x08,0x00,0x38,0x00,0xC8,0x20,0x00,0x3F,0xC8,0x20,0x38,0x00,0x08,0x00},/*"Y",57*/

{0x00,0x00,0x08,0x18,0x38,0x20,0xC8,0x20,0x08,0x21,0x08,0x26,0x08,0x38,0x10,0x20},/*"Z",58*/

{0x00,0x00,0x02,0x40,0x02,0x40,0x02,0x40,0xFE,0x7F,0x00,0x00,0x00,0x00,0x00,0x00},/*"[",59*/

{0x00,0x00,0x00,0xC0,0x00,0x38,0x00,0x06,0xC0,0x01,0x38,0x00,0x04,0x00,0x00,0x00},/*"\",60*/

{0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x7F,0x02,0x40,0x02,0x40,0x02,0x40,0x00,0x00},/*"]",61*/

{0x00,0x00,0x00,0x00,0x04,0x00,0x02,0x00,0x02,0x00,0x04,0x00,0x00,0x00,0x00,0x00},/*"^",62*/

{0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80},/*"_",63*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x02,0x00,0x02,0x00,0x00,0x00},/*"`",64*/

{0x00,0x00,0x00,0x20,0x00,0x3F,0x80,0x12,0x80,0x24,0x80,0x24,0x00,0x19,0x00,0x00},/*"a",65*/

{0x00,0x00,0x00,0x0E,0x00,0x11,0x80,0x20,0x80,0x20,0x00,0x11,0xF0,0x3F,0x10,0x00},/*"b",66*/

{0x00,0x00,0x00,0x11,0x80,0x20,0x80,0x20,0x80,0x20,0x00,0x11,0x00,0x0E,0x00,0x00},/*"c",67*/

{0x00,0x20,0xF0,0x3F,0x90,0x10,0x80,0x20,0x80,0x20,0x80,0x20,0x00,0x1F,0x00,0x00},/*"d",68*/

{0x00,0x00,0x00,0x17,0x80,0x24,0x80,0x24,0x80,0x24,0x80,0x24,0x00,0x1F,0x00,0x00},/*"e",69*/

{0x00,0x00,0x20,0x00,0x90,0x20,0x90,0x20,0xE0,0x3F,0x80,0x20,0x80,0x20,0x00,0x00},/*"f",70*/

{0x00,0x00,0x80,0x60,0x80,0x93,0x80,0x94,0x80,0x94,0x80,0x94,0x00,0x6B,0x00,0x00},/*"g",71*/

{0x00,0x20,0x00,0x3F,0x80,0x20,0x80,0x00,0x80,0x00,0x00,0x21,0xF0,0x3F,0x10,0x20},/*"h",72*/

{0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x20,0x98,0x3F,0x98,0x20,0x80,0x20,0x00,0x00},/*"i",73*/

{0x00,0x00,0x00,0x00,0x98,0x7F,0x98,0x80,0x80,0x80,0x00,0x80,0x00,0xC0,0x00,0x00},/*"j",74*/

{0x00,0x00,0x80,0x20,0x80,0x30,0x80,0x29,0x00,0x06,0x00,0x24,0xF0,0x3F,0x10,0x20},/*"k",75*/

{0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x20,0xF8,0x3F,0x10,0x20,0x10,0x20,0x00,0x00},/*"l",76*/

{0x00,0x3F,0x80,0x00,0x80,0x20,0x80,0x3F,0x80,0x00,0x80,0x20,0x80,0x3F,0x80,0x20},/*"m",77*/

{0x00,0x20,0x00,0x3F,0x80,0x20,0x80,0x00,0x80,0x00,0x00,0x21,0x80,0x3F,0x80,0x20},/*"n",78*/

{0x00,0x00,0x00,0x1F,0x80,0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x00,0x1F,0x00,0x00},/*"o",79*/

{0x00,0x00,0x00,0x0E,0x00,0x11,0x80,0x20,0x80,0x20,0x00,0x91,0x80,0xFF,0x80,0x80},/*"p",80*/

{0x00,0x80,0x80,0xFF,0x00,0x91,0x80,0x20,0x80,0x20,0x00,0x11,0x00,0x0E,0x00,0x00},/*"q",81*/

{0x00,0x00,0x80,0x01,0x80,0x00,0x80,0x20,0x00,0x21,0x80,0x3F,0x80,0x20,0x80,0x20},/*"r",82*/

{0x00,0x00,0x80,0x19,0x80,0x24,0x80,0x24,0x80,0x24,0x80,0x24,0x00,0x33,0x00,0x00},/*"s",83*/

{0x00,0x00,0x00,0x10,0x80,0x20,0x80,0x20,0xE0,0x1F,0x80,0x00,0x80,0x00,0x00,0x00},/*"t",84*/

{0x00,0x20,0x80,0x3F,0x80,0x10,0x00,0x20,0x00,0x20,0x00,0x20,0x80,0x1F,0x80,0x00},/*"u",85*/

{0x00,0x00,0x80,0x00,0x80,0x03,0x80,0x0C,0x00,0x30,0x80,0x0C,0x80,0x03,0x80,0x00},/*"v",86*/

{0x80,0x01,0x80,0x06,0x00,0x38,0x80,0x07,0x80,0x0C,0x00,0x30,0x80,0x0E,0x80,0x01},/*"w",87*/

{0x00,0x00,0x80,0x20,0x80,0x31,0x00,0x2E,0x80,0x0E,0x80,0x31,0x80,0x20,0x00,0x00},/*"x",88*/

{0x80,0x00,0x80,0x01,0x80,0x06,0x00,0x18,0x00,0x78,0x80,0x86,0x80,0x81,0x80,0x00},/*"y",89*/

{0x00,0x00,0x80,0x30,0x80,0x21,0x80,0x22,0x80,0x2C,0x80,0x30,0x80,0x21,0x00,0x00},/*"z",90*/

{0x02,0x40,0x02,0x40,0xFC,0x3E,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"{",91*/

{0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"|",92*/

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFC,0x3E,0x02,0x40,0x02,0x40},/*"}",93*/

{0x00,0x00,0x02,0x00,0x04,0x00,0x02,0x00,0x02,0x00,0x01,0x00,0x02,0x00,0x00,0x00},/*"~",94*/


};
