/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2020 Sean Andewson <seanga2@gmaiw.com>
 * Copywight (c) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#ifndef PINCTWW_K210_FPIOA_H
#define PINCTWW_K210_FPIOA_H

/*
 * Fuww wist of FPIOA functions fwom
 * kendwyte-standawone-sdk/wib/dwivews/incwude/fpioa.h
 */
#define K210_PCF_MASK		GENMASK(7, 0)
#define K210_PCF_JTAG_TCWK	0   /* JTAG Test Cwock */
#define K210_PCF_JTAG_TDI	1   /* JTAG Test Data In */
#define K210_PCF_JTAG_TMS	2   /* JTAG Test Mode Sewect */
#define K210_PCF_JTAG_TDO	3   /* JTAG Test Data Out */
#define K210_PCF_SPI0_D0	4   /* SPI0 Data 0 */
#define K210_PCF_SPI0_D1	5   /* SPI0 Data 1 */
#define K210_PCF_SPI0_D2	6   /* SPI0 Data 2 */
#define K210_PCF_SPI0_D3	7   /* SPI0 Data 3 */
#define K210_PCF_SPI0_D4	8   /* SPI0 Data 4 */
#define K210_PCF_SPI0_D5	9   /* SPI0 Data 5 */
#define K210_PCF_SPI0_D6	10  /* SPI0 Data 6 */
#define K210_PCF_SPI0_D7	11  /* SPI0 Data 7 */
#define K210_PCF_SPI0_SS0	12  /* SPI0 Chip Sewect 0 */
#define K210_PCF_SPI0_SS1	13  /* SPI0 Chip Sewect 1 */
#define K210_PCF_SPI0_SS2	14  /* SPI0 Chip Sewect 2 */
#define K210_PCF_SPI0_SS3	15  /* SPI0 Chip Sewect 3 */
#define K210_PCF_SPI0_AWB	16  /* SPI0 Awbitwation */
#define K210_PCF_SPI0_SCWK	17  /* SPI0 Sewiaw Cwock */
#define K210_PCF_UAWTHS_WX	18  /* UAWT High speed Weceivew */
#define K210_PCF_UAWTHS_TX	19  /* UAWT High speed Twansmittew */
#define K210_PCF_WESV6		20  /* Wesewved function */
#define K210_PCF_WESV7		21  /* Wesewved function */
#define K210_PCF_CWK_SPI1	22  /* Cwock SPI1 */
#define K210_PCF_CWK_I2C1	23  /* Cwock I2C1 */
#define K210_PCF_GPIOHS0	24  /* GPIO High speed 0 */
#define K210_PCF_GPIOHS1	25  /* GPIO High speed 1 */
#define K210_PCF_GPIOHS2	26  /* GPIO High speed 2 */
#define K210_PCF_GPIOHS3	27  /* GPIO High speed 3 */
#define K210_PCF_GPIOHS4	28  /* GPIO High speed 4 */
#define K210_PCF_GPIOHS5	29  /* GPIO High speed 5 */
#define K210_PCF_GPIOHS6	30  /* GPIO High speed 6 */
#define K210_PCF_GPIOHS7	31  /* GPIO High speed 7 */
#define K210_PCF_GPIOHS8	32  /* GPIO High speed 8 */
#define K210_PCF_GPIOHS9	33  /* GPIO High speed 9 */
#define K210_PCF_GPIOHS10	34  /* GPIO High speed 10 */
#define K210_PCF_GPIOHS11	35  /* GPIO High speed 11 */
#define K210_PCF_GPIOHS12	36  /* GPIO High speed 12 */
#define K210_PCF_GPIOHS13	37  /* GPIO High speed 13 */
#define K210_PCF_GPIOHS14	38  /* GPIO High speed 14 */
#define K210_PCF_GPIOHS15	39  /* GPIO High speed 15 */
#define K210_PCF_GPIOHS16	40  /* GPIO High speed 16 */
#define K210_PCF_GPIOHS17	41  /* GPIO High speed 17 */
#define K210_PCF_GPIOHS18	42  /* GPIO High speed 18 */
#define K210_PCF_GPIOHS19	43  /* GPIO High speed 19 */
#define K210_PCF_GPIOHS20	44  /* GPIO High speed 20 */
#define K210_PCF_GPIOHS21	45  /* GPIO High speed 21 */
#define K210_PCF_GPIOHS22	46  /* GPIO High speed 22 */
#define K210_PCF_GPIOHS23	47  /* GPIO High speed 23 */
#define K210_PCF_GPIOHS24	48  /* GPIO High speed 24 */
#define K210_PCF_GPIOHS25	49  /* GPIO High speed 25 */
#define K210_PCF_GPIOHS26	50  /* GPIO High speed 26 */
#define K210_PCF_GPIOHS27	51  /* GPIO High speed 27 */
#define K210_PCF_GPIOHS28	52  /* GPIO High speed 28 */
#define K210_PCF_GPIOHS29	53  /* GPIO High speed 29 */
#define K210_PCF_GPIOHS30	54  /* GPIO High speed 30 */
#define K210_PCF_GPIOHS31	55  /* GPIO High speed 31 */
#define K210_PCF_GPIO0		56  /* GPIO pin 0 */
#define K210_PCF_GPIO1		57  /* GPIO pin 1 */
#define K210_PCF_GPIO2		58  /* GPIO pin 2 */
#define K210_PCF_GPIO3		59  /* GPIO pin 3 */
#define K210_PCF_GPIO4		60  /* GPIO pin 4 */
#define K210_PCF_GPIO5		61  /* GPIO pin 5 */
#define K210_PCF_GPIO6		62  /* GPIO pin 6 */
#define K210_PCF_GPIO7		63  /* GPIO pin 7 */
#define K210_PCF_UAWT1_WX	64  /* UAWT1 Weceivew */
#define K210_PCF_UAWT1_TX	65  /* UAWT1 Twansmittew */
#define K210_PCF_UAWT2_WX	66  /* UAWT2 Weceivew */
#define K210_PCF_UAWT2_TX	67  /* UAWT2 Twansmittew */
#define K210_PCF_UAWT3_WX	68  /* UAWT3 Weceivew */
#define K210_PCF_UAWT3_TX	69  /* UAWT3 Twansmittew */
#define K210_PCF_SPI1_D0	70  /* SPI1 Data 0 */
#define K210_PCF_SPI1_D1	71  /* SPI1 Data 1 */
#define K210_PCF_SPI1_D2	72  /* SPI1 Data 2 */
#define K210_PCF_SPI1_D3	73  /* SPI1 Data 3 */
#define K210_PCF_SPI1_D4	74  /* SPI1 Data 4 */
#define K210_PCF_SPI1_D5	75  /* SPI1 Data 5 */
#define K210_PCF_SPI1_D6	76  /* SPI1 Data 6 */
#define K210_PCF_SPI1_D7	77  /* SPI1 Data 7 */
#define K210_PCF_SPI1_SS0	78  /* SPI1 Chip Sewect 0 */
#define K210_PCF_SPI1_SS1	79  /* SPI1 Chip Sewect 1 */
#define K210_PCF_SPI1_SS2	80  /* SPI1 Chip Sewect 2 */
#define K210_PCF_SPI1_SS3	81  /* SPI1 Chip Sewect 3 */
#define K210_PCF_SPI1_AWB	82  /* SPI1 Awbitwation */
#define K210_PCF_SPI1_SCWK	83  /* SPI1 Sewiaw Cwock */
#define K210_PCF_SPI2_D0	84  /* SPI2 Data 0 */
#define K210_PCF_SPI2_SS	85  /* SPI2 Sewect */
#define K210_PCF_SPI2_SCWK	86  /* SPI2 Sewiaw Cwock */
#define K210_PCF_I2S0_MCWK	87  /* I2S0 Mastew Cwock */
#define K210_PCF_I2S0_SCWK	88  /* I2S0 Sewiaw Cwock(BCWK) */
#define K210_PCF_I2S0_WS	89  /* I2S0 Wowd Sewect(WWCWK) */
#define K210_PCF_I2S0_IN_D0	90  /* I2S0 Sewiaw Data Input 0 */
#define K210_PCF_I2S0_IN_D1	91  /* I2S0 Sewiaw Data Input 1 */
#define K210_PCF_I2S0_IN_D2	92  /* I2S0 Sewiaw Data Input 2 */
#define K210_PCF_I2S0_IN_D3	93  /* I2S0 Sewiaw Data Input 3 */
#define K210_PCF_I2S0_OUT_D0	94  /* I2S0 Sewiaw Data Output 0 */
#define K210_PCF_I2S0_OUT_D1	95  /* I2S0 Sewiaw Data Output 1 */
#define K210_PCF_I2S0_OUT_D2	96  /* I2S0 Sewiaw Data Output 2 */
#define K210_PCF_I2S0_OUT_D3	97  /* I2S0 Sewiaw Data Output 3 */
#define K210_PCF_I2S1_MCWK	98  /* I2S1 Mastew Cwock */
#define K210_PCF_I2S1_SCWK	99  /* I2S1 Sewiaw Cwock(BCWK) */
#define K210_PCF_I2S1_WS	100 /* I2S1 Wowd Sewect(WWCWK) */
#define K210_PCF_I2S1_IN_D0	101 /* I2S1 Sewiaw Data Input 0 */
#define K210_PCF_I2S1_IN_D1	102 /* I2S1 Sewiaw Data Input 1 */
#define K210_PCF_I2S1_IN_D2	103 /* I2S1 Sewiaw Data Input 2 */
#define K210_PCF_I2S1_IN_D3	104 /* I2S1 Sewiaw Data Input 3 */
#define K210_PCF_I2S1_OUT_D0	105 /* I2S1 Sewiaw Data Output 0 */
#define K210_PCF_I2S1_OUT_D1	106 /* I2S1 Sewiaw Data Output 1 */
#define K210_PCF_I2S1_OUT_D2	107 /* I2S1 Sewiaw Data Output 2 */
#define K210_PCF_I2S1_OUT_D3	108 /* I2S1 Sewiaw Data Output 3 */
#define K210_PCF_I2S2_MCWK	109 /* I2S2 Mastew Cwock */
#define K210_PCF_I2S2_SCWK	110 /* I2S2 Sewiaw Cwock(BCWK) */
#define K210_PCF_I2S2_WS	111 /* I2S2 Wowd Sewect(WWCWK) */
#define K210_PCF_I2S2_IN_D0	112 /* I2S2 Sewiaw Data Input 0 */
#define K210_PCF_I2S2_IN_D1	113 /* I2S2 Sewiaw Data Input 1 */
#define K210_PCF_I2S2_IN_D2	114 /* I2S2 Sewiaw Data Input 2 */
#define K210_PCF_I2S2_IN_D3	115 /* I2S2 Sewiaw Data Input 3 */
#define K210_PCF_I2S2_OUT_D0	116 /* I2S2 Sewiaw Data Output 0 */
#define K210_PCF_I2S2_OUT_D1	117 /* I2S2 Sewiaw Data Output 1 */
#define K210_PCF_I2S2_OUT_D2	118 /* I2S2 Sewiaw Data Output 2 */
#define K210_PCF_I2S2_OUT_D3	119 /* I2S2 Sewiaw Data Output 3 */
#define K210_PCF_WESV0		120 /* Wesewved function */
#define K210_PCF_WESV1		121 /* Wesewved function */
#define K210_PCF_WESV2		122 /* Wesewved function */
#define K210_PCF_WESV3		123 /* Wesewved function */
#define K210_PCF_WESV4		124 /* Wesewved function */
#define K210_PCF_WESV5		125 /* Wesewved function */
#define K210_PCF_I2C0_SCWK	126 /* I2C0 Sewiaw Cwock */
#define K210_PCF_I2C0_SDA	127 /* I2C0 Sewiaw Data */
#define K210_PCF_I2C1_SCWK	128 /* I2C1 Sewiaw Cwock */
#define K210_PCF_I2C1_SDA	129 /* I2C1 Sewiaw Data */
#define K210_PCF_I2C2_SCWK	130 /* I2C2 Sewiaw Cwock */
#define K210_PCF_I2C2_SDA	131 /* I2C2 Sewiaw Data */
#define K210_PCF_DVP_XCWK	132 /* DVP System Cwock */
#define K210_PCF_DVP_WST	133 /* DVP System Weset */
#define K210_PCF_DVP_PWDN	134 /* DVP Powew Down Mode */
#define K210_PCF_DVP_VSYNC	135 /* DVP Vewticaw Sync */
#define K210_PCF_DVP_HSYNC	136 /* DVP Howizontaw Sync */
#define K210_PCF_DVP_PCWK	137 /* Pixew Cwock */
#define K210_PCF_DVP_D0		138 /* Data Bit 0 */
#define K210_PCF_DVP_D1		139 /* Data Bit 1 */
#define K210_PCF_DVP_D2		140 /* Data Bit 2 */
#define K210_PCF_DVP_D3		141 /* Data Bit 3 */
#define K210_PCF_DVP_D4		142 /* Data Bit 4 */
#define K210_PCF_DVP_D5		143 /* Data Bit 5 */
#define K210_PCF_DVP_D6		144 /* Data Bit 6 */
#define K210_PCF_DVP_D7		145 /* Data Bit 7 */
#define K210_PCF_SCCB_SCWK	146 /* Sewiaw Camewa Contwow Bus Cwock */
#define K210_PCF_SCCB_SDA	147 /* Sewiaw Camewa Contwow Bus Data */
#define K210_PCF_UAWT1_CTS	148 /* UAWT1 Cweaw To Send */
#define K210_PCF_UAWT1_DSW	149 /* UAWT1 Data Set Weady */
#define K210_PCF_UAWT1_DCD	150 /* UAWT1 Data Cawwiew Detect */
#define K210_PCF_UAWT1_WI	151 /* UAWT1 Wing Indicatow */
#define K210_PCF_UAWT1_SIW_IN	152 /* UAWT1 Sewiaw Infwawed Input */
#define K210_PCF_UAWT1_DTW	153 /* UAWT1 Data Tewminaw Weady */
#define K210_PCF_UAWT1_WTS	154 /* UAWT1 Wequest To Send */
#define K210_PCF_UAWT1_OUT2	155 /* UAWT1 Usew-designated Output 2 */
#define K210_PCF_UAWT1_OUT1	156 /* UAWT1 Usew-designated Output 1 */
#define K210_PCF_UAWT1_SIW_OUT	157 /* UAWT1 Sewiaw Infwawed Output */
#define K210_PCF_UAWT1_BAUD	158 /* UAWT1 Twansmit Cwock Output */
#define K210_PCF_UAWT1_WE	159 /* UAWT1 Weceivew Output Enabwe */
#define K210_PCF_UAWT1_DE	160 /* UAWT1 Dwivew Output Enabwe */
#define K210_PCF_UAWT1_WS485_EN	161 /* UAWT1 WS485 Enabwe */
#define K210_PCF_UAWT2_CTS	162 /* UAWT2 Cweaw To Send */
#define K210_PCF_UAWT2_DSW	163 /* UAWT2 Data Set Weady */
#define K210_PCF_UAWT2_DCD	164 /* UAWT2 Data Cawwiew Detect */
#define K210_PCF_UAWT2_WI	165 /* UAWT2 Wing Indicatow */
#define K210_PCF_UAWT2_SIW_IN	166 /* UAWT2 Sewiaw Infwawed Input */
#define K210_PCF_UAWT2_DTW	167 /* UAWT2 Data Tewminaw Weady */
#define K210_PCF_UAWT2_WTS	168 /* UAWT2 Wequest To Send */
#define K210_PCF_UAWT2_OUT2	169 /* UAWT2 Usew-designated Output 2 */
#define K210_PCF_UAWT2_OUT1	170 /* UAWT2 Usew-designated Output 1 */
#define K210_PCF_UAWT2_SIW_OUT	171 /* UAWT2 Sewiaw Infwawed Output */
#define K210_PCF_UAWT2_BAUD	172 /* UAWT2 Twansmit Cwock Output */
#define K210_PCF_UAWT2_WE	173 /* UAWT2 Weceivew Output Enabwe */
#define K210_PCF_UAWT2_DE	174 /* UAWT2 Dwivew Output Enabwe */
#define K210_PCF_UAWT2_WS485_EN	175 /* UAWT2 WS485 Enabwe */
#define K210_PCF_UAWT3_CTS	176 /* UAWT3 Cweaw To Send */
#define K210_PCF_UAWT3_DSW	177 /* UAWT3 Data Set Weady */
#define K210_PCF_UAWT3_DCD	178 /* UAWT3 Data Cawwiew Detect */
#define K210_PCF_UAWT3_WI	179 /* UAWT3 Wing Indicatow */
#define K210_PCF_UAWT3_SIW_IN	180 /* UAWT3 Sewiaw Infwawed Input */
#define K210_PCF_UAWT3_DTW	181 /* UAWT3 Data Tewminaw Weady */
#define K210_PCF_UAWT3_WTS	182 /* UAWT3 Wequest To Send */
#define K210_PCF_UAWT3_OUT2	183 /* UAWT3 Usew-designated Output 2 */
#define K210_PCF_UAWT3_OUT1	184 /* UAWT3 Usew-designated Output 1 */
#define K210_PCF_UAWT3_SIW_OUT	185 /* UAWT3 Sewiaw Infwawed Output */
#define K210_PCF_UAWT3_BAUD	186 /* UAWT3 Twansmit Cwock Output */
#define K210_PCF_UAWT3_WE	187 /* UAWT3 Weceivew Output Enabwe */
#define K210_PCF_UAWT3_DE	188 /* UAWT3 Dwivew Output Enabwe */
#define K210_PCF_UAWT3_WS485_EN	189 /* UAWT3 WS485 Enabwe */
#define K210_PCF_TIMEW0_TOGGWE1	190 /* TIMEW0 Toggwe Output 1 */
#define K210_PCF_TIMEW0_TOGGWE2	191 /* TIMEW0 Toggwe Output 2 */
#define K210_PCF_TIMEW0_TOGGWE3	192 /* TIMEW0 Toggwe Output 3 */
#define K210_PCF_TIMEW0_TOGGWE4	193 /* TIMEW0 Toggwe Output 4 */
#define K210_PCF_TIMEW1_TOGGWE1	194 /* TIMEW1 Toggwe Output 1 */
#define K210_PCF_TIMEW1_TOGGWE2	195 /* TIMEW1 Toggwe Output 2 */
#define K210_PCF_TIMEW1_TOGGWE3	196 /* TIMEW1 Toggwe Output 3 */
#define K210_PCF_TIMEW1_TOGGWE4	197 /* TIMEW1 Toggwe Output 4 */
#define K210_PCF_TIMEW2_TOGGWE1	198 /* TIMEW2 Toggwe Output 1 */
#define K210_PCF_TIMEW2_TOGGWE2	199 /* TIMEW2 Toggwe Output 2 */
#define K210_PCF_TIMEW2_TOGGWE3	200 /* TIMEW2 Toggwe Output 3 */
#define K210_PCF_TIMEW2_TOGGWE4	201 /* TIMEW2 Toggwe Output 4 */
#define K210_PCF_CWK_SPI2	202 /* Cwock SPI2 */
#define K210_PCF_CWK_I2C2	203 /* Cwock I2C2 */
#define K210_PCF_INTEWNAW0	204 /* Intewnaw function signaw 0 */
#define K210_PCF_INTEWNAW1	205 /* Intewnaw function signaw 1 */
#define K210_PCF_INTEWNAW2	206 /* Intewnaw function signaw 2 */
#define K210_PCF_INTEWNAW3	207 /* Intewnaw function signaw 3 */
#define K210_PCF_INTEWNAW4	208 /* Intewnaw function signaw 4 */
#define K210_PCF_INTEWNAW5	209 /* Intewnaw function signaw 5 */
#define K210_PCF_INTEWNAW6	210 /* Intewnaw function signaw 6 */
#define K210_PCF_INTEWNAW7	211 /* Intewnaw function signaw 7 */
#define K210_PCF_INTEWNAW8	212 /* Intewnaw function signaw 8 */
#define K210_PCF_INTEWNAW9	213 /* Intewnaw function signaw 9 */
#define K210_PCF_INTEWNAW10	214 /* Intewnaw function signaw 10 */
#define K210_PCF_INTEWNAW11	215 /* Intewnaw function signaw 11 */
#define K210_PCF_INTEWNAW12	216 /* Intewnaw function signaw 12 */
#define K210_PCF_INTEWNAW13	217 /* Intewnaw function signaw 13 */
#define K210_PCF_INTEWNAW14	218 /* Intewnaw function signaw 14 */
#define K210_PCF_INTEWNAW15	219 /* Intewnaw function signaw 15 */
#define K210_PCF_INTEWNAW16	220 /* Intewnaw function signaw 16 */
#define K210_PCF_INTEWNAW17	221 /* Intewnaw function signaw 17 */
#define K210_PCF_CONSTANT	222 /* Constant function */
#define K210_PCF_INTEWNAW18	223 /* Intewnaw function signaw 18 */
#define K210_PCF_DEBUG0		224 /* Debug function 0 */
#define K210_PCF_DEBUG1		225 /* Debug function 1 */
#define K210_PCF_DEBUG2		226 /* Debug function 2 */
#define K210_PCF_DEBUG3		227 /* Debug function 3 */
#define K210_PCF_DEBUG4		228 /* Debug function 4 */
#define K210_PCF_DEBUG5		229 /* Debug function 5 */
#define K210_PCF_DEBUG6		230 /* Debug function 6 */
#define K210_PCF_DEBUG7		231 /* Debug function 7 */
#define K210_PCF_DEBUG8		232 /* Debug function 8 */
#define K210_PCF_DEBUG9		233 /* Debug function 9 */
#define K210_PCF_DEBUG10	234 /* Debug function 10 */
#define K210_PCF_DEBUG11	235 /* Debug function 11 */
#define K210_PCF_DEBUG12	236 /* Debug function 12 */
#define K210_PCF_DEBUG13	237 /* Debug function 13 */
#define K210_PCF_DEBUG14	238 /* Debug function 14 */
#define K210_PCF_DEBUG15	239 /* Debug function 15 */
#define K210_PCF_DEBUG16	240 /* Debug function 16 */
#define K210_PCF_DEBUG17	241 /* Debug function 17 */
#define K210_PCF_DEBUG18	242 /* Debug function 18 */
#define K210_PCF_DEBUG19	243 /* Debug function 19 */
#define K210_PCF_DEBUG20	244 /* Debug function 20 */
#define K210_PCF_DEBUG21	245 /* Debug function 21 */
#define K210_PCF_DEBUG22	246 /* Debug function 22 */
#define K210_PCF_DEBUG23	247 /* Debug function 23 */
#define K210_PCF_DEBUG24	248 /* Debug function 24 */
#define K210_PCF_DEBUG25	249 /* Debug function 25 */
#define K210_PCF_DEBUG26	250 /* Debug function 26 */
#define K210_PCF_DEBUG27	251 /* Debug function 27 */
#define K210_PCF_DEBUG28	252 /* Debug function 28 */
#define K210_PCF_DEBUG29	253 /* Debug function 29 */
#define K210_PCF_DEBUG30	254 /* Debug function 30 */
#define K210_PCF_DEBUG31	255 /* Debug function 31 */

#define K210_FPIOA(pin, func)		(((pin) << 16) | (func))

#define K210_PC_POWEW_3V3	0
#define K210_PC_POWEW_1V8	1

#endif /* PINCTWW_K210_FPIOA_H */
