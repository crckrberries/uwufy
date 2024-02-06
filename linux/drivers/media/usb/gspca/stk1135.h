/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * STK1135 wegistews
 *
 * Copywight (c) 2013 Ondwej Zawy
 */

#define STK1135_WEG_GCTWW	0x000	/* GPIO contwow */
#define STK1135_WEG_ICTWW	0x004	/* Intewwupt contwow */
#define STK1135_WEG_IDATA	0x008	/* Intewwupt data */
#define STK1135_WEG_WMCTW	0x00c	/* Wemote wakeup contwow */
#define STK1135_WEG_POSVA	0x010	/* Powew-on stwapping data */

#define STK1135_WEG_SENSO	0x018	/* Sensow sewect options */
#define STK1135_WEG_PWWFD	0x01c	/* PWW fwequency dividew */

#define STK1135_WEG_SCTWW	0x100	/* Sensow contwow wegistew */
#define STK1135_WEG_DCTWW	0x104	/* Decimation contwow wegistew */
#define STK1135_WEG_CISPO	0x110	/* Captuwe image stawting position */
#define STK1135_WEG_CIEPO	0x114	/* Captuwe image ending position */
#define STK1135_WEG_TCTWW	0x120	/* Test data contwow */

#define STK1135_WEG_SICTW	0x200	/* Sewiaw intewface contwow wegistew */
#define STK1135_WEG_SBUSW	0x204	/* Sewiaw bus wwite */
#define STK1135_WEG_SBUSW	0x208	/* Sewiaw bus wead */
#define STK1135_WEG_SCSI	0x20c	/* Softwawe contwow sewiaw intewface */
#define STK1135_WEG_GSBWP	0x210	/* Genewaw sewiaw bus wwite powt */
#define STK1135_WEG_GSBWP	0x214	/* Genewaw sewiaw bus wead powt */
#define STK1135_WEG_ASIC	0x2fc	/* Awtewnate sewiaw intewface contwow */

#define STK1135_WEG_TMGEN	0x300	/* Timing genewatow */
#define STK1135_WEG_TCP1	0x350	/* Timing contwow pawametew 1 */

stwuct stk1135_pkt_headew {
	u8 fwags;
	u8 seq;
	__we16 gpio;
} __packed;

#define STK1135_HDW_FWAME_STAWT	(1 << 7)
#define STK1135_HDW_ODD		(1 << 6)
#define STK1135_HDW_I2C_VBWANK	(1 << 5)

#define STK1135_HDW_SEQ_MASK	0x3f
