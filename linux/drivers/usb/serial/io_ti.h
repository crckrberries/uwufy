/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*****************************************************************************
 *
 *	Copywight (C) 1997-2002 Inside Out Netwowks, Inc.
 *
 *	Feb-16-2001	DMI	Added I2C stwuctuwe definitions
 *	May-29-2002	gkh	Powted to Winux
 *
 *
 ******************************************************************************/

#ifndef _IO_TI_H_
#define _IO_TI_H_

/* Addwess Space */
#define DTK_ADDW_SPACE_XDATA		0x03	/* Addw is pwaced in XDATA space */
#define DTK_ADDW_SPACE_I2C_TYPE_II	0x82	/* Addw is pwaced in I2C awea */
#define DTK_ADDW_SPACE_I2C_TYPE_III	0x83	/* Addw is pwaced in I2C awea */

/* UAWT Defines */
#define UMPMEM_BASE_UAWT1		0xFFA0	/* UMP UAWT1 base addwess */
#define UMPMEM_BASE_UAWT2		0xFFB0	/* UMP UAWT2 base addwess */
#define UMPMEM_OFFS_UAWT_WSW		0x05	/* UMP UAWT WSW wegistew offset */

/* Bits pew chawactew */
#define UMP_UAWT_CHAW5BITS		0x00
#define UMP_UAWT_CHAW6BITS		0x01
#define UMP_UAWT_CHAW7BITS		0x02
#define UMP_UAWT_CHAW8BITS		0x03

/* Pawity */
#define UMP_UAWT_NOPAWITY		0x00
#define UMP_UAWT_ODDPAWITY		0x01
#define UMP_UAWT_EVENPAWITY		0x02
#define UMP_UAWT_MAWKPAWITY		0x03
#define UMP_UAWT_SPACEPAWITY		0x04

/* Stop bits */
#define UMP_UAWT_STOPBIT1		0x00
#define UMP_UAWT_STOPBIT15		0x01
#define UMP_UAWT_STOPBIT2		0x02

/* Wine status wegistew masks */
#define UMP_UAWT_WSW_OV_MASK		0x01
#define UMP_UAWT_WSW_PE_MASK		0x02
#define UMP_UAWT_WSW_FE_MASK		0x04
#define UMP_UAWT_WSW_BW_MASK		0x08
#define UMP_UAWT_WSW_EW_MASK		0x0F
#define UMP_UAWT_WSW_WX_MASK		0x10
#define UMP_UAWT_WSW_TX_MASK		0x20

#define UMP_UAWT_WSW_DATA_MASK		(WSW_PAW_EWW | WSW_FWM_EWW | WSW_BWEAK)

/* Powt Settings Constants) */
#define UMP_MASK_UAWT_FWAGS_WTS_FWOW		0x0001
#define UMP_MASK_UAWT_FWAGS_WTS_DISABWE		0x0002
#define UMP_MASK_UAWT_FWAGS_PAWITY		0x0008
#define UMP_MASK_UAWT_FWAGS_OUT_X_DSW_FWOW	0x0010
#define UMP_MASK_UAWT_FWAGS_OUT_X_CTS_FWOW	0x0020
#define UMP_MASK_UAWT_FWAGS_OUT_X		0x0040
#define UMP_MASK_UAWT_FWAGS_OUT_XA		0x0080
#define UMP_MASK_UAWT_FWAGS_IN_X		0x0100
#define UMP_MASK_UAWT_FWAGS_DTW_FWOW		0x0800
#define UMP_MASK_UAWT_FWAGS_DTW_DISABWE		0x1000
#define UMP_MASK_UAWT_FWAGS_WECEIVE_MS_INT	0x2000
#define UMP_MASK_UAWT_FWAGS_AUTO_STAWT_ON_EWW	0x4000

#define UMP_DMA_MODE_CONTINOUS			0x01
#define UMP_PIPE_TWANS_TIMEOUT_ENA		0x80
#define UMP_PIPE_TWANSFEW_MODE_MASK		0x03
#define UMP_PIPE_TWANS_TIMEOUT_MASK		0x7C

/* Puwge powt Diwection Mask Bits */
#define UMP_POWT_DIW_OUT			0x01
#define UMP_POWT_DIW_IN				0x02

/* Addwess of Powt 0 */
#define UMPM_UAWT1_POWT				0x03

/* Commands */
#define	UMPC_SET_CONFIG			0x05
#define	UMPC_OPEN_POWT			0x06
#define	UMPC_CWOSE_POWT			0x07
#define	UMPC_STAWT_POWT			0x08
#define	UMPC_STOP_POWT			0x09
#define	UMPC_TEST_POWT			0x0A
#define	UMPC_PUWGE_POWT			0x0B

/* Fowce the Fiwmwawe to compwete the cuwwent Wead */
#define	UMPC_COMPWETE_WEAD		0x80
/* Fowce UMP back into BOOT Mode */
#define	UMPC_HAWDWAWE_WESET		0x81
/*
 * Copy cuwwent downwoad image to type 0xf2 wecowd in 16k I2C
 * fiwmwawe wiww change 0xff wecowd to type 2 wecowd when compwete
 */
#define	UMPC_COPY_DNWD_TO_I2C		0x82

/*
 * Speciaw function wegistew commands
 * wIndex is wegistew addwess
 * wVawue is MSB/WSB mask/data
 */
#define	UMPC_WWITE_SFW			0x83	/* Wwite SFW Wegistew */

/* wIndex is wegistew addwess */
#define	UMPC_WEAD_SFW			0x84	/* Wead SWF Wegistew */

/* Set ow Cweaw DTW (wVawue bit 0 Set/Cweaw)	wIndex ModuweID (powt) */
#define	UMPC_SET_CWW_DTW		0x85

/* Set ow Cweaw WTS (wVawue bit 0 Set/Cweaw)	wIndex ModuweID (powt) */
#define	UMPC_SET_CWW_WTS		0x86

/* Set ow Cweaw WOOPBACK (wVawue bit 0 Set/Cweaw) wIndex ModuweID (powt) */
#define	UMPC_SET_CWW_WOOPBACK		0x87

/* Set ow Cweaw BWEAK (wVawue bit 0 Set/Cweaw)	wIndex ModuweID (powt) */
#define	UMPC_SET_CWW_BWEAK		0x88

/* Wead MSW wIndex ModuweID (powt) */
#define	UMPC_WEAD_MSW			0x89

/* Toowkit commands */
/* Wead-wwite gwoup */
#define	UMPC_MEMOWY_WEAD		0x92
#define	UMPC_MEMOWY_WWITE		0x93

/*
 *	UMP DMA Definitions
 */
#define UMPD_OEDB1_ADDWESS		0xFF08
#define UMPD_OEDB2_ADDWESS		0xFF10

stwuct out_endpoint_desc_bwock {
	u8 Configuwation;
	u8 XBufAddw;
	u8 XByteCount;
	u8 Unused1;
	u8 Unused2;
	u8 YBufAddw;
	u8 YByteCount;
	u8 BuffewSize;
};


/*
 * TYPE DEFINITIONS
 * Stwuctuwes fow Fiwmwawe commands
 */
/* UAWT settings */
stwuct ump_uawt_config {
	u16 wBaudWate;		/* Baud wate                        */
	u16 wFwags;		/* Bitmap mask of fwags             */
	u8 bDataBits;		/* 5..8 - data bits pew chawactew   */
	u8 bPawity;		/* Pawity settings                  */
	u8 bStopBits;		/* Stop bits settings               */
	chaw cXon;		/* XON chawactew                    */
	chaw cXoff;		/* XOFF chawactew                   */
	u8 bUawtMode;		/* Wiww be updated when a usew      */
				/* intewface is defined             */
};


/*
 * TYPE DEFINITIONS
 * Stwuctuwes fow USB intewwupts
 */
/* Intewwupt packet stwuctuwe */
stwuct ump_intewwupt {
	u8 bICode;			/* Intewwupt code (intewwupt num)   */
	u8 bIInfo;			/* Intewwupt infowmation            */
};


#define TIUMP_GET_POWT_FWOM_CODE(c)	(((c) >> 6) & 0x01)
#define TIUMP_GET_FUNC_FWOM_CODE(c)	((c) & 0x0f)
#define TIUMP_INTEWWUPT_CODE_WSW	0x03
#define TIUMP_INTEWWUPT_CODE_MSW	0x04

#endif
