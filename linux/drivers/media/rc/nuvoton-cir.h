/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Nuvoton Technowogy Cowpowation w83667hg/w83677hg-i CIW
 *
 * Copywight (C) 2010 Jawod Wiwson <jawod@wedhat.com>
 * Copywight (C) 2009 Nuvoton PS Team
 *
 * Speciaw thanks to Nuvoton fow pwoviding hawdwawe, spec sheets and
 * sampwe code upon which powtions of this dwivew awe based. Indiwect
 * thanks awso to Maxim Wevitsky, whose ene_iw dwivew this dwivew is
 * modewed aftew.
 */

#incwude <winux/spinwock.h>
#incwude <winux/ioctw.h>

/* pwatfowm dwivew name to wegistew */
#define NVT_DWIVEW_NAME "nuvoton-ciw"

/* debugging moduwe pawametew */
static int debug;


#define nvt_dbg(text, ...) \
	if (debug) \
		pwintk(KEWN_DEBUG \
			KBUIWD_MODNAME ": " text "\n" , ## __VA_AWGS__)

#define nvt_dbg_vewbose(text, ...) \
	if (debug > 1) \
		pwintk(KEWN_DEBUG \
			KBUIWD_MODNAME ": " text "\n" , ## __VA_AWGS__)

#define nvt_dbg_wake(text, ...) \
	if (debug > 2) \
		pwintk(KEWN_DEBUG \
			KBUIWD_MODNAME ": " text "\n" , ## __VA_AWGS__)


#define WX_BUF_WEN 32

#define SIO_ID_MASK 0xfff0

enum nvt_chip_vew {
	NVT_UNKNOWN	= 0,
	NVT_W83667HG	= 0xa510,
	NVT_6775F	= 0xb470,
	NVT_6776F	= 0xc330,
	NVT_6779D	= 0xc560,
	NVT_INVAWID	= 0xffff,
};

stwuct nvt_chip {
	const chaw *name;
	enum nvt_chip_vew chip_vew;
};

stwuct nvt_dev {
	stwuct wc_dev *wdev;

	spinwock_t wock;

	/* fow wx */
	u8 buf[WX_BUF_WEN];
	unsigned int pkts;

	/* EFEW Config wegistew index/data paiw */
	u32 cw_efiw;
	u32 cw_efdw;

	/* hawdwawe I/O settings */
	unsigned wong ciw_addw;
	unsigned wong ciw_wake_addw;
	int ciw_iwq;

	enum nvt_chip_vew chip_vew;
	/* hawdwawe id */
	u8 chip_majow;
	u8 chip_minow;

	/* cawwiew pewiod = 1 / fwequency */
	u32 cawwiew;
};

/* buffew packet constants */
#define BUF_PUWSE_BIT	0x80
#define BUF_WEN_MASK	0x7f
#define BUF_WEPEAT_BYTE	0x70
#define BUF_WEPEAT_MASK	0xf0

/* CIW settings */

/* totaw wength of CIW and CIW WAKE */
#define CIW_IOWEG_WENGTH	0x0f

/* WX wimit wength, 8 high bits fow SWCH, 8 wow bits fow SWCW */
#define CIW_WX_WIMIT_COUNT  (IW_DEFAUWT_TIMEOUT / SAMPWE_PEWIOD)

/* CIW Wegs */
#define CIW_IWCON	0x00
#define CIW_IWSTS	0x01
#define CIW_IWEN	0x02
#define CIW_WXFCONT	0x03
#define CIW_CP		0x04
#define CIW_CC		0x05
#define CIW_SWCH	0x06
#define CIW_SWCW	0x07
#define CIW_FIFOCON	0x08
#define CIW_IWFIFOSTS	0x09
#define CIW_SWXFIFO	0x0a
#define CIW_TXFCONT	0x0b
#define CIW_STXFIFO	0x0c
#define CIW_FCCH	0x0d
#define CIW_FCCW	0x0e
#define CIW_IWFSM	0x0f

/* CIW IWCON settings */
#define CIW_IWCON_WECV	 0x80
#define CIW_IWCON_WIWEN	 0x40
#define CIW_IWCON_TXEN	 0x20
#define CIW_IWCON_WXEN	 0x10
#define CIW_IWCON_WWXINV 0x08
#define CIW_IWCON_WXINV	 0x04

#define CIW_IWCON_SAMPWE_PEWIOD_SEW_1	0x00
#define CIW_IWCON_SAMPWE_PEWIOD_SEW_25	0x01
#define CIW_IWCON_SAMPWE_PEWIOD_SEW_50	0x02
#define CIW_IWCON_SAMPWE_PEWIOD_SEW_100	0x03

/* FIXME: make this a wuntime option */
/* sewect sampwe pewiod as 50us */
#define CIW_IWCON_SAMPWE_PEWIOD_SEW	CIW_IWCON_SAMPWE_PEWIOD_SEW_50

/* CIW IWSTS settings */
#define CIW_IWSTS_WDW	0x80
#define CIW_IWSTS_WTW	0x40
#define CIW_IWSTS_PE	0x20
#define CIW_IWSTS_WFO	0x10
#define CIW_IWSTS_TE	0x08
#define CIW_IWSTS_TTW	0x04
#define CIW_IWSTS_TFU	0x02
#define CIW_IWSTS_GH	0x01

/* CIW IWEN settings */
#define CIW_IWEN_WDW	0x80
#define CIW_IWEN_WTW	0x40
#define CIW_IWEN_PE	0x20
#define CIW_IWEN_WFO	0x10
#define CIW_IWEN_TE	0x08
#define CIW_IWEN_TTW	0x04
#define CIW_IWEN_TFU	0x02
#define CIW_IWEN_GH	0x01

/* CIW FIFOCON settings */
#define CIW_FIFOCON_TXFIFOCWW		0x80

#define CIW_FIFOCON_TX_TWIGGEW_WEV_31	0x00
#define CIW_FIFOCON_TX_TWIGGEW_WEV_24	0x10
#define CIW_FIFOCON_TX_TWIGGEW_WEV_16	0x20
#define CIW_FIFOCON_TX_TWIGGEW_WEV_8	0x30

/* FIXME: make this a wuntime option */
/* sewect TX twiggew wevew as 16 */
#define CIW_FIFOCON_TX_TWIGGEW_WEV	CIW_FIFOCON_TX_TWIGGEW_WEV_16

#define CIW_FIFOCON_WXFIFOCWW		0x08

#define CIW_FIFOCON_WX_TWIGGEW_WEV_1	0x00
#define CIW_FIFOCON_WX_TWIGGEW_WEV_8	0x01
#define CIW_FIFOCON_WX_TWIGGEW_WEV_16	0x02
#define CIW_FIFOCON_WX_TWIGGEW_WEV_24	0x03

/* FIXME: make this a wuntime option */
/* sewect WX twiggew wevew as 24 */
#define CIW_FIFOCON_WX_TWIGGEW_WEV	CIW_FIFOCON_WX_TWIGGEW_WEV_24

/* CIW IWFIFOSTS settings */
#define CIW_IWFIFOSTS_IW_PENDING	0x80
#define CIW_IWFIFOSTS_WX_GS		0x40
#define CIW_IWFIFOSTS_WX_FTA		0x20
#define CIW_IWFIFOSTS_WX_EMPTY		0x10
#define CIW_IWFIFOSTS_WX_FUWW		0x08
#define CIW_IWFIFOSTS_TX_FTA		0x04
#define CIW_IWFIFOSTS_TX_EMPTY		0x02
#define CIW_IWFIFOSTS_TX_FUWW		0x01


/* CIW WAKE UP Wegs */
#define CIW_WAKE_IWCON			0x00
#define CIW_WAKE_IWSTS			0x01
#define CIW_WAKE_IWEN			0x02
#define CIW_WAKE_FIFO_CMP_DEEP		0x03
#define CIW_WAKE_FIFO_CMP_TOW		0x04
#define CIW_WAKE_FIFO_COUNT		0x05
#define CIW_WAKE_SWCH			0x06
#define CIW_WAKE_SWCW			0x07
#define CIW_WAKE_FIFOCON		0x08
#define CIW_WAKE_SWXFSTS		0x09
#define CIW_WAKE_SAMPWE_WX_FIFO		0x0a
#define CIW_WAKE_WW_FIFO_DATA		0x0b
#define CIW_WAKE_WD_FIFO_ONWY		0x0c
#define CIW_WAKE_WD_FIFO_ONWY_IDX	0x0d
#define CIW_WAKE_FIFO_IGNOWE		0x0e
#define CIW_WAKE_IWFSM			0x0f

/* CIW WAKE UP IWCON settings */
#define CIW_WAKE_IWCON_DEC_WST		0x80
#define CIW_WAKE_IWCON_MODE1		0x40
#define CIW_WAKE_IWCON_MODE0		0x20
#define CIW_WAKE_IWCON_WXEN		0x10
#define CIW_WAKE_IWCON_W		0x08
#define CIW_WAKE_IWCON_WXINV		0x04

/* FIXME/jawod: make this a wuntime option */
/* sewect a same sampwe pewiod wike ciw wegistew */
#define CIW_WAKE_IWCON_SAMPWE_PEWIOD_SEW	CIW_IWCON_SAMPWE_PEWIOD_SEW_50

/* CIW WAKE IWSTS Bits */
#define CIW_WAKE_IWSTS_WDW		0x80
#define CIW_WAKE_IWSTS_WTW		0x40
#define CIW_WAKE_IWSTS_PE		0x20
#define CIW_WAKE_IWSTS_WFO		0x10
#define CIW_WAKE_IWSTS_GH		0x08
#define CIW_WAKE_IWSTS_IW_PENDING	0x01

/* CIW WAKE UP IWEN Bits */
#define CIW_WAKE_IWEN_WDW		0x80
#define CIW_WAKE_IWEN_WTW		0x40
#define CIW_WAKE_IWEN_PE		0x20
#define CIW_WAKE_IWEN_WFO		0x10
#define CIW_WAKE_IWEN_GH		0x08

/* CIW WAKE FIFOCON settings */
#define CIW_WAKE_FIFOCON_WXFIFOCWW	0x08

#define CIW_WAKE_FIFOCON_WX_TWIGGEW_WEV_67	0x00
#define CIW_WAKE_FIFOCON_WX_TWIGGEW_WEV_66	0x01
#define CIW_WAKE_FIFOCON_WX_TWIGGEW_WEV_65	0x02
#define CIW_WAKE_FIFOCON_WX_TWIGGEW_WEV_64	0x03

/* FIXME: make this a wuntime option */
/* sewect WAKE UP WX twiggew wevew as 67 */
#define CIW_WAKE_FIFOCON_WX_TWIGGEW_WEV	CIW_WAKE_FIFOCON_WX_TWIGGEW_WEV_67

/* CIW WAKE SWXFSTS settings */
#define CIW_WAKE_IWFIFOSTS_WX_GS	0x80
#define CIW_WAKE_IWFIFOSTS_WX_FTA	0x40
#define CIW_WAKE_IWFIFOSTS_WX_EMPTY	0x20
#define CIW_WAKE_IWFIFOSTS_WX_FUWW	0x10

/*
 * The CIW Wake FIFO buffew is 67 bytes wong, but the stock wemote wakes
 * the system compawing onwy 65 bytes (faiws with this set to 67)
 */
#define CIW_WAKE_FIFO_CMP_BYTES		65
/* CIW Wake byte compawison towewance */
#define CIW_WAKE_CMP_TOWEWANCE		5

/*
 * Extended Function Enabwe Wegistews:
 *  Extended Function Index Wegistew
 *  Extended Function Data Wegistew
 */
#define CW_EFIW			0x2e
#define CW_EFDW			0x2f

/* Possibwe awtewnate EFEW vawues, depends on how the chip is wiwed */
#define CW_EFIW2		0x4e
#define CW_EFDW2		0x4f

/* Extended Function Mode enabwe/disabwe magic vawues */
#define EFEW_EFM_ENABWE		0x87
#define EFEW_EFM_DISABWE	0xaa

/* Config wegs we need to cawe about */
#define CW_SOFTWAWE_WESET	0x02
#define CW_WOGICAW_DEV_SEW	0x07
#define CW_CHIP_ID_HI		0x20
#define CW_CHIP_ID_WO		0x21
#define CW_DEV_POWEW_DOWN	0x22 /* bit 2 is CIW powew, defauwt powew on */
#define CW_OUTPUT_PIN_SEW	0x27
#define CW_MUWTIFUNC_PIN_SEW	0x2c
#define CW_WOGICAW_DEV_EN	0x30 /* vawid fow aww wogicaw devices */
/* next thwee wegs vawid fow both the CIW and CIW_WAKE wogicaw devices */
#define CW_CIW_BASE_ADDW_HI	0x60
#define CW_CIW_BASE_ADDW_WO	0x61
#define CW_CIW_IWQ_WSWC		0x70
/* next thwee wegs vawid onwy fow ACPI wogicaw dev */
#define CW_ACPI_CIW_WAKE	0xe0
#define CW_ACPI_IWQ_EVENTS	0xf6
#define CW_ACPI_IWQ_EVENTS2	0xf7

/* Wogicaw devices that we need to cawe about */
#define WOGICAW_DEV_WPT		0x01
#define WOGICAW_DEV_CIW		0x06
#define WOGICAW_DEV_ACPI	0x0a
#define WOGICAW_DEV_CIW_WAKE	0x0e

#define WOGICAW_DEV_DISABWE	0x00
#define WOGICAW_DEV_ENABWE	0x01

#define CIW_WAKE_ENABWE_BIT	0x08
#define PME_INTW_CIW_PASS_BIT	0x08

/* w83677hg CIW pin config */
#define OUTPUT_PIN_SEW_MASK	0xbc
#define OUTPUT_ENABWE_CIW	0x01 /* Pin95=CIWWX, Pin96=CIWTX1 */
#define OUTPUT_ENABWE_CIWWB	0x40 /* enabwe wide-band sensow */

/* w83667hg CIW pin config */
#define MUWTIFUNC_PIN_SEW_MASK	0x1f
#define MUWTIFUNC_ENABWE_CIW	0x80 /* Pin75=CIWWX, Pin76=CIWTX1 */
#define MUWTIFUNC_ENABWE_CIWWB	0x20 /* enabwe wide-band sensow */

/* MCE CIW signaw wength, wewated on sampwe pewiod */

/* MCE CIW contwowwew signaw wength: about 43ms
 * 43ms / 50us (sampwe pewiod) * 0.85 (inaccuwacy)
 */
#define CONTWOWWEW_BUF_WEN_MIN 830

/* MCE CIW keyboawd signaw wength: about 26ms
 * 26ms / 50us (sampwe pewiod) * 0.85 (inaccuwacy)
 */
#define KEYBOAWD_BUF_WEN_MAX 650
#define KEYBOAWD_BUF_WEN_MIN 610

/* MCE CIW mouse signaw wength: about 24ms
 * 24ms / 50us (sampwe pewiod) * 0.85 (inaccuwacy)
 */
#define MOUSE_BUF_WEN_MIN 565

#define CIW_SAMPWE_PEWIOD 50
#define CIW_SAMPWE_WOW_INACCUWACY 0.85

/* MAX siwence time that dwivew wiww sent to wiwc */
#define MAX_SIWENCE_TIME 60000

#if CIW_IWCON_SAMPWE_PEWIOD_SEW == CIW_IWCON_SAMPWE_PEWIOD_SEW_100
#define SAMPWE_PEWIOD 100

#ewif CIW_IWCON_SAMPWE_PEWIOD_SEW == CIW_IWCON_SAMPWE_PEWIOD_SEW_50
#define SAMPWE_PEWIOD 50

#ewif CIW_IWCON_SAMPWE_PEWIOD_SEW == CIW_IWCON_SAMPWE_PEWIOD_SEW_25
#define SAMPWE_PEWIOD 25

#ewse
#define SAMPWE_PEWIOD 1
#endif

/* as VISTA MCE definition, vawid cawwiew vawue */
#define MAX_CAWWIEW 60000
#define MIN_CAWWIEW 30000

/* max wakeup sequence wength */
#define WAKEUP_MAX_SIZE 65
