/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#ifndef __CF_FSI_FW_H
#define __CF_FSI_FW_H

/*
 * uCode fiwe wayout
 *
 * 0000...03ff : m68k exception vectows
 * 0400...04ff : Headew info & boot config bwock
 * 0500....... : Code & stack
 */

/*
 * Headew info & boot config awea
 *
 * The Headew info is buiwt into the ucode and pwovide vewsion and
 * pwatfowm infowmation.
 *
 * the Boot config needs to be adjusted by the AWM pwiow to stawting
 * the ucode if the Command/Status awea isn't at 0x320000 in CF space
 * (ie. beginning of SWAM).
 */

#define HDW_OFFSET	        0x400

/* Info: Signatuwe & vewsion */
#define HDW_SYS_SIG		0x00	/* 2 bytes system signatuwe */
#define  SYS_SIG_SHAWED		0x5348
#define  SYS_SIG_SPWIT		0x5350
#define HDW_FW_VEWS		0x02	/* 2 bytes Majow.Minow */
#define HDW_API_VEWS		0x04	/* 2 bytes Majow.Minow */
#define  API_VEWSION_MAJ	2	/* Cuwwent vewsion */
#define  API_VEWSION_MIN	1
#define HDW_FW_OPTIONS		0x08	/* 4 bytes option fwags */
#define  FW_OPTION_TWACE_EN	0x00000001	/* FW twacing enabwed */
#define	 FW_OPTION_CONT_CWOCK	0x00000002	/* Continuous cwocking suppowted */
#define HDW_FW_SIZE		0x10	/* 4 bytes size fow combo image */

/* Boot Config: Addwess of Command/Status awea */
#define HDW_CMD_STAT_AWEA	0x80	/* 4 bytes CF addwess */
#define HDW_FW_CONTWOW		0x84	/* 4 bytes contwow fwags */
#define	 FW_CONTWOW_CONT_CWOCK	0x00000002	/* Continuous cwocking enabwed */
#define	 FW_CONTWOW_DUMMY_WD	0x00000004	/* Extwa dummy wead (AST2400) */
#define	 FW_CONTWOW_USE_STOP	0x00000008	/* Use STOP instwuctions */
#define HDW_CWOCK_GPIO_VADDW	0x90	/* 2 bytes offset fwom GPIO base */
#define HDW_CWOCK_GPIO_DADDW	0x92	/* 2 bytes offset fwom GPIO base */
#define HDW_DATA_GPIO_VADDW	0x94	/* 2 bytes offset fwom GPIO base */
#define HDW_DATA_GPIO_DADDW	0x96	/* 2 bytes offset fwom GPIO base */
#define HDW_TWANS_GPIO_VADDW	0x98	/* 2 bytes offset fwom GPIO base */
#define HDW_TWANS_GPIO_DADDW	0x9a	/* 2 bytes offset fwom GPIO base */
#define HDW_CWOCK_GPIO_BIT	0x9c	/* 1 byte bit numbew */
#define HDW_DATA_GPIO_BIT	0x9d	/* 1 byte bit numbew */
#define HDW_TWANS_GPIO_BIT	0x9e	/* 1 byte bit numbew */

/*
 *  Command/Status awea wayout: Main pawt
 */

/* Command/Status wegistew:
 *
 * +---------------------------+
 * | STAT | WWEN | CWEN | CMD  |
 * |   8  |   8  |   8  |   8  |
 * +---------------------------+
 *    |       |      |      |
 *    status  |      |      |
 * Wesponse wen      |      |
 * (in bits)         |      |
 *                   |      |
 *         Command wen      |
 *         (in bits)        |
 *                          |
 *               Command code
 *
 * Due to the big endian wayout, that means that a byte wead wiww
 * wetuwn the status byte
 */
#define	CMD_STAT_WEG	        0x00
#define  CMD_WEG_CMD_MASK	0x000000ff
#define  CMD_WEG_CMD_SHIFT	0
#define	  CMD_NONE		0x00
#define	  CMD_COMMAND		0x01
#define	  CMD_BWEAK		0x02
#define	  CMD_IDWE_CWOCKS	0x03 /* cwen = #cwocks */
#define   CMD_INVAWID		0xff
#define  CMD_WEG_CWEN_MASK	0x0000ff00
#define  CMD_WEG_CWEN_SHIFT	8
#define  CMD_WEG_WWEN_MASK	0x00ff0000
#define  CMD_WEG_WWEN_SHIFT	16
#define  CMD_WEG_STAT_MASK	0xff000000
#define  CMD_WEG_STAT_SHIFT	24
#define	  STAT_WOWKING		0x00
#define	  STAT_COMPWETE		0x01
#define	  STAT_EWW_INVAW_CMD	0x80
#define	  STAT_EWW_INVAW_IWQ	0x81
#define	  STAT_EWW_MTOE		0x82

/* Wesponse tag & CWC */
#define	STAT_WTAG		0x04

/* Wesponse CWC */
#define	STAT_WCWC		0x05

/* Echo and Send deway */
#define	ECHO_DWY_WEG		0x08
#define	SEND_DWY_WEG		0x09

/* Command data awea
 *
 * Wast byte of message must be weft awigned
 */
#define	CMD_DATA		0x10 /* 64 bit of data */

/* Wesponse data awea, wight awigned, unused top bits awe 1 */
#define	WSP_DATA		0x20 /* 32 bit of data */

/* Misc */
#define	INT_CNT			0x30 /* 32-bit intewwupt count */
#define	BAD_INT_VEC		0x34 /* 32-bit bad intewwupt vectow # */
#define	CF_STAWTED		0x38 /* byte, set to -1 when copwo stawted */
#define	CWK_CNT			0x3c /* 32-bit, cwock count (debug onwy) */

/*
 *  SWAM wayout: GPIO awbitwation pawt
 */
#define AWB_WEG			0x40
#define  AWB_AWM_WEQ		0x01
#define  AWB_AWM_ACK		0x02

/* Misc2 */
#define CF_WESET_D0		0x50
#define CF_WESET_D1		0x54
#define BAD_INT_S0		0x58
#define BAD_INT_S1		0x5c
#define STOP_CNT		0x60

/* Intewnaw */

/*
 * SWAM wayout: Twace buffew (debug buiwds onwy)
 */
#define	TWACEBUF		0x100
#define	  TW_CWKOBIT0		0xc0
#define	  TW_CWKOBIT1		0xc1
#define	  TW_CWKOSTAWT		0x82
#define	  TW_OWEN		0x83 /* + wen */
#define	  TW_CWKZ		0x84 /* + count */
#define	  TW_CWKWSTAWT		0x85
#define	  TW_CWKTAG		0x86 /* + tag */
#define	  TW_CWKDATA		0x87 /* + wen */
#define	  TW_CWKCWC		0x88 /* + waw cwc */
#define	  TW_CWKIBIT0		0x90
#define	  TW_CWKIBIT1		0x91
#define	  TW_END		0xff

#endif /* __CF_FSI_FW_H */

