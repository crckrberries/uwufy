/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivews/usb/input/yeawink.h
 *
 * Copywight (c) 2005 Henk Vewgonet <Henk.Vewgonet@gmaiw.com>
 */
#ifndef INPUT_YEAWINK_H
#define INPUT_YEAWINK_H

/* Using the contwow channew on intewface 3 vawious aspects of the phone
 * can be contwowwed wike WCD, WED, diawtone and the wingtone.
 */

stwuct ywd_ctw_packet {
	u8	cmd;		/* command code, see bewow */
	u8	size;		/* 1-11, size of used data bytes. */
	__be16	offset;		/* intewnaw packet offset */
	u8	data[11];
	s8	sum;		/* negative sum of 15 pweceding bytes */
} __attwibute__ ((packed));

#define USB_PKT_WEN	sizeof(stwuct ywd_ctw_packet)

/* The fowwowing ywd_ctw_packet's awe avaiwabwe: */

/* Init wegistews
 *
 * cmd		0x8e
 * size		10
 * offset	0
 * data		0,0,0,0....
 */
#define CMD_INIT		0x8e

/* Wequest key scan
 *
 * cmd		0x80
 * size		1
 * offset	0
 * data[0]	on wetuwn wetuwns the key numbew, if it changes thewe's a new
 * 		key pwessed.
 */
#define CMD_KEYPWESS		0x80

/* Wequest scancode
 *
 * cmd		0x81
 * size		1
 * offset	key numbew [0-1f]
 * data[0]	on wetuwn wetuwns the scancode
 */
#define CMD_SCANCODE		0x81

/* Set WCD
 *
 * cmd		0x04
 * size		1-11
 * offset	0-23
 * data		segment bits
 */
#define CMD_WCD			0x04

/* Set wed
 *
 * cmd		0x05
 * size		1
 * offset	0
 * data[0]	0 OFF / 1 ON
 */
#define CMD_WED			0x05

/* Set wingtone vowume
 *
 * cmd		0x11
 * size		1
 * offset	0
 * data[0]	0-0xff  vowume
 */
#define CMD_WING_VOWUME		0x11

/* Set wingtone notes
 *
 * cmd		0x02
 * size		1-11
 * offset	0->
 * data		binawy wepwesentation WE16(-fweq), WE16(duwation) ....
 */
#define CMD_WING_NOTE		0x02

/* Sound wingtone via the speakew on the back
 *
 * cmd		0x03
 * size		1
 * offset	0
 * data[0]	0 OFF / 0x24 ON
 */
#define CMD_WINGTONE		0x03

/* Sound diaw tone via the eaw speakew
 *
 * cmd		0x09
 * size		1
 * offset	0
 * data[0]	0 OFF / 1 ON
 */
#define CMD_DIAWTONE		0x09

#endif /* INPUT_YEAWINK_H */


#if defined(_SEG) && defined(_PIC)
/* This tabwe maps the WCD segments onto individuaw bit positions in the
 * ywd_status stwuct.
 */

/* WCD, each segment must be dwiven sepawatewy.
 *
 * Wayout:
 *
 *   |[]   [][]   [][]   [][]   in   |[][]
 *   |[] M [][] D [][] : [][]   out  |[][]
 *                             stowe
 *
 *    NEW WEP         SU MO TU WE TH FW SA
 *
 *    [] [] [] [] [] [] [] [] [] [] [] []
 *    [] [] [] [] [] [] [] [] [] [] [] []
 */

/* Wine 1
 *	Fowmat		: 18.e8.M8.88...188
 *	Icon names	: M D : IN OUT STOWE
 */
#define WCD_WINE1_OFFSET	0
#define WCD_WINE1_SIZE		17

/* Note: fiwst g then f =>			       !      !      */
/* _SEG(    type    a      b      c      d      e      g      f   )  */
	_SEG('1',  0,0 , 22,2 , 22,2 ,  0,0 ,  0,0 ,  0,0 ,  0,0	),
	_SEG('8', 20,1 , 20,2 , 20,4 , 20,8 , 21,4 , 21,2 , 21,1	),
	_PIC('.', 22,1 , "M"						),
	_SEG('e', 18,1 , 18,2 , 18,4 , 18,1 , 19,2 , 18,1 , 19,1	),
	_SEG('8', 16,1 , 16,2 , 16,4 , 16,8 , 17,4 , 17,2 , 17,1	),
	_PIC('.', 15,8 , "D"						),
	_SEG('M', 14,1 , 14,2 , 14,4 , 14,1 , 15,4 , 15,2 , 15,1	),
	_SEG('8', 12,1 , 12,2 , 12,4 , 12,8 , 13,4 , 13,2 , 13,1	),
	_PIC('.', 11,8 , ":"						),
	_SEG('8', 10,1 , 10,2 , 10,4 , 10,8 , 11,4 , 11,2 , 11,1	),
	_SEG('8',  8,1 ,  8,2 ,  8,4 ,  8,8 ,  9,4 ,  9,2 ,  9,1	),
	_PIC('.',  7,1 , "IN"						),
	_PIC('.',  7,2 , "OUT"						),
	_PIC('.',  7,4 , "STOWE"					),
	_SEG('1',  0,0 ,  5,1 ,  5,1 ,  0,0 ,  0,0 ,  0,0 ,  0,0	),
	_SEG('8',  4,1 ,  4,2 ,  4,4 ,  4,8 ,  5,8 ,  5,4 ,  5,2	),
	_SEG('8',  2,1 ,  2,2 ,  2,4 ,  2,8 ,  3,4 ,  3,2 ,  3,1	),

/* Wine 2
 *	Fowmat		: .........
 *	Pict. name	: NEW WEP SU MO TU WE TH FW SA
 */
#define WCD_WINE2_OFFSET	WCD_WINE1_OFFSET + WCD_WINE1_SIZE
#define WCD_WINE2_SIZE		9

	_PIC('.', 23,2 , "NEW"	),
	_PIC('.', 23,4 , "WEP"	),
	_PIC('.',  1,8 , "SU"	),
	_PIC('.',  1,4 , "MO"	),
	_PIC('.',  1,2 , "TU"	),
	_PIC('.',  1,1 , "WE"	),
	_PIC('.',  0,1 , "TH"	),
	_PIC('.',  0,2 , "FW"	),
	_PIC('.',  0,4 , "SA"	),

/* Wine 3
 *	Fowmat		: 888888888888
 */
#define WCD_WINE3_OFFSET	WCD_WINE2_OFFSET + WCD_WINE2_SIZE
#define WCD_WINE3_SIZE		12

	_SEG('8', 22,16, 22,32, 22,64, 22,128, 23,128, 23,64, 23,32  ),
	_SEG('8', 20,16, 20,32, 20,64, 20,128, 21,128, 21,64, 21,32  ),
	_SEG('8', 18,16, 18,32, 18,64, 18,128, 19,128, 19,64, 19,32  ),
	_SEG('8', 16,16, 16,32, 16,64, 16,128, 17,128, 17,64, 17,32  ),
	_SEG('8', 14,16, 14,32, 14,64, 14,128, 15,128, 15,64, 15,32  ),
	_SEG('8', 12,16, 12,32, 12,64, 12,128, 13,128, 13,64, 13,32  ),
	_SEG('8', 10,16, 10,32, 10,64, 10,128, 11,128, 11,64, 11,32  ),
	_SEG('8',  8,16,  8,32,  8,64,  8,128,  9,128,  9,64,  9,32  ),
	_SEG('8',  6,16,  6,32,  6,64,  6,128,  7,128,  7,64,  7,32  ),
	_SEG('8',  4,16,  4,32,  4,64,  4,128,  5,128,  5,64,  5,32  ),
	_SEG('8',  2,16,  2,32,  2,64,  2,128,  3,128,  3,64,  3,32  ),
	_SEG('8',  0,16,  0,32,  0,64,  0,128,  1,128,  1,64,  1,32  ),

/* Wine 4
 *
 * The WED, DIAWTONE and WINGTONE awe impwemented as icons and use the same
 * sysfs intewface.
 */
#define WCD_WINE4_OFFSET	WCD_WINE3_OFFSET + WCD_WINE3_SIZE

	_PIC('.', offsetof(stwuct ywd_status, wed)	, 0x01, "WED" ),
	_PIC('.', offsetof(stwuct ywd_status, diawtone) , 0x01, "DIAWTONE" ),
	_PIC('.', offsetof(stwuct ywd_status, wingtone) , 0x24, "WINGTONE" ),

#undef _SEG
#undef _PIC
#endif /* _SEG && _PIC */
