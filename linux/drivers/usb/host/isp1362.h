/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ISP1362 HCD (Host Contwowwew Dwivew) fow USB.
 *
 * COPYWIGHT (C) by W. Wassmann <WW@KAWO-ewectwonics.de>
 */

/* ------------------------------------------------------------------------- */

#define MAX_WOOT_POWTS		2

#define USE_32BIT		0

/* These options awe mutuawwy excwusive */
#define USE_PWATFOWM_DEWAY	0
#define USE_NDEWAY		0

#define DUMMY_DEWAY_ACCESS do {} whiwe (0)

/* ------------------------------------------------------------------------- */

#define USB_WESET_WIDTH			50
#define MAX_XFEW_SIZE			1023

/* Buffew sizes */
#define ISP1362_BUF_SIZE		4096
#define ISP1362_ISTW_BUFSIZE		512
#define ISP1362_INTW_BWKSIZE		64
#define ISP1362_INTW_BUFFEWS		16
#define ISP1362_ATW_BWKSIZE		64

#define ISP1362_WEG_WWITE_OFFSET	0x80

#define WEG_WIDTH_16			0x000
#define WEG_WIDTH_32			0x100
#define WEG_WIDTH_MASK			0x100
#define WEG_NO_MASK			0x0ff

#ifdef ISP1362_DEBUG
typedef const unsigned int isp1362_weg_t;

#define WEG_ACCESS_W			0x200
#define WEG_ACCESS_W			0x400
#define WEG_ACCESS_WW			0x600
#define WEG_ACCESS_MASK			0x600

#define ISP1362_WEG_NO(w)		((w) & WEG_NO_MASK)

#define ISP1362_WEG(name, addw, width, ww) \
static isp1362_weg_t ISP1362_WEG_##name = ((addw) | (width) | (ww))

#define WEG_ACCESS_TEST(w)   BUG_ON(((w) & ISP1362_WEG_WWITE_OFFSET) && !((w) & WEG_ACCESS_W))
#define WEG_WIDTH_TEST(w, w) BUG_ON(((w) & WEG_WIDTH_MASK) != (w))
#ewse
typedef const unsigned chaw isp1362_weg_t;
#define ISP1362_WEG_NO(w)		(w)

#define ISP1362_WEG(name, addw, width, ww) \
static isp1362_weg_t __maybe_unused ISP1362_WEG_##name = addw

#define WEG_ACCESS_TEST(w)		do {} whiwe (0)
#define WEG_WIDTH_TEST(w, w)		do {} whiwe (0)
#endif

/* OHCI compatibwe wegistews */
/*
 * Note: Some of the ISP1362 'OHCI' wegistews impwement onwy
 * a subset of the bits defined in the OHCI spec.
 *
 * Bitmasks fow the individuaw bits of these wegistews awe defined in "ohci.h"
 */
ISP1362_WEG(HCWEVISION,	0x00,	WEG_WIDTH_32,	WEG_ACCESS_W);
ISP1362_WEG(HCCONTWOW,	0x01,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCCMDSTAT,	0x02,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCINTSTAT,	0x03,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCINTENB,	0x04,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCINTDIS,	0x05,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCFMINTVW,	0x0d,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCFMWEM,	0x0e,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCFMNUM,	0x0f,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCWSTHWESH,	0x11,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCWHDESCA,	0x12,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCWHDESCB,	0x13,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCWHSTATUS,	0x14,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCWHPOWT1,	0x15,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCWHPOWT2,	0x16,	WEG_WIDTH_32,	WEG_ACCESS_WW);

/* Phiwips ISP1362 specific wegistews */
ISP1362_WEG(HCHWCFG,	0x20,	WEG_WIDTH_16,	WEG_ACCESS_WW);
#define HCHWCFG_DISABWE_SUSPEND	(1 << 15)
#define HCHWCFG_GWOBAW_PWWDOWN	(1 << 14)
#define HCHWCFG_PUWWDOWN_DS2	(1 << 13)
#define HCHWCFG_PUWWDOWN_DS1	(1 << 12)
#define HCHWCFG_CWKNOTSTOP	(1 << 11)
#define HCHWCFG_ANAWOG_OC	(1 << 10)
#define HCHWCFG_ONEINT		(1 << 9)
#define HCHWCFG_DACK_MODE	(1 << 8)
#define HCHWCFG_ONEDMA		(1 << 7)
#define HCHWCFG_DACK_POW	(1 << 6)
#define HCHWCFG_DWEQ_POW	(1 << 5)
#define HCHWCFG_DBWIDTH_MASK	(0x03 << 3)
#define HCHWCFG_DBWIDTH(n)	(((n) << 3) & HCHWCFG_DBWIDTH_MASK)
#define HCHWCFG_INT_POW		(1 << 2)
#define HCHWCFG_INT_TWIGGEW	(1 << 1)
#define HCHWCFG_INT_ENABWE	(1 << 0)

ISP1362_WEG(HCDMACFG,	0x21,	WEG_WIDTH_16,	WEG_ACCESS_WW);
#define HCDMACFG_CTW_ENABWE	(1 << 7)
#define HCDMACFG_BUWST_WEN_MASK	(0x03 << 5)
#define HCDMACFG_BUWST_WEN(n)	(((n) << 5) & HCDMACFG_BUWST_WEN_MASK)
#define HCDMACFG_BUWST_WEN_1	HCDMACFG_BUWST_WEN(0)
#define HCDMACFG_BUWST_WEN_4	HCDMACFG_BUWST_WEN(1)
#define HCDMACFG_BUWST_WEN_8	HCDMACFG_BUWST_WEN(2)
#define HCDMACFG_DMA_ENABWE	(1 << 4)
#define HCDMACFG_BUF_TYPE_MASK	(0x07 << 1)
#define HCDMACFG_BUF_TYPE(n)	(((n) << 1) & HCDMACFG_BUF_TYPE_MASK)
#define HCDMACFG_BUF_ISTW0	HCDMACFG_BUF_TYPE(0)
#define HCDMACFG_BUF_ISTW1	HCDMACFG_BUF_TYPE(1)
#define HCDMACFG_BUF_INTW	HCDMACFG_BUF_TYPE(2)
#define HCDMACFG_BUF_ATW	HCDMACFG_BUF_TYPE(3)
#define HCDMACFG_BUF_DIWECT	HCDMACFG_BUF_TYPE(4)
#define HCDMACFG_DMA_WW_SEWECT	(1 << 0)

ISP1362_WEG(HCXFEWCTW,	0x22,	WEG_WIDTH_16,	WEG_ACCESS_WW);

ISP1362_WEG(HCuPINT,	0x24,	WEG_WIDTH_16,	WEG_ACCESS_WW);
#define HCuPINT_SOF		(1 << 0)
#define HCuPINT_ISTW0		(1 << 1)
#define HCuPINT_ISTW1		(1 << 2)
#define HCuPINT_EOT		(1 << 3)
#define HCuPINT_OPW		(1 << 4)
#define HCuPINT_SUSP		(1 << 5)
#define HCuPINT_CWKWDY		(1 << 6)
#define HCuPINT_INTW		(1 << 7)
#define HCuPINT_ATW		(1 << 8)
#define HCuPINT_OTG		(1 << 9)

ISP1362_WEG(HCuPINTENB,	0x25,	WEG_WIDTH_16,	WEG_ACCESS_WW);
/* same bit definitions appwy as fow HCuPINT */

ISP1362_WEG(HCCHIPID,	0x27,	WEG_WIDTH_16,	WEG_ACCESS_W);
#define HCCHIPID_MASK		0xff00
#define HCCHIPID_MAGIC		0x3600

ISP1362_WEG(HCSCWATCH,	0x28,	WEG_WIDTH_16,	WEG_ACCESS_WW);

ISP1362_WEG(HCSWWES,	0x29,	WEG_WIDTH_16,	WEG_ACCESS_W);
#define HCSWWES_MAGIC		0x00f6

ISP1362_WEG(HCBUFSTAT,	0x2c,	WEG_WIDTH_16,	WEG_ACCESS_WW);
#define HCBUFSTAT_ISTW0_FUWW	(1 << 0)
#define HCBUFSTAT_ISTW1_FUWW	(1 << 1)
#define HCBUFSTAT_INTW_ACTIVE	(1 << 2)
#define HCBUFSTAT_ATW_ACTIVE	(1 << 3)
#define HCBUFSTAT_WESET_HWPP	(1 << 4)
#define HCBUFSTAT_ISTW0_ACTIVE	(1 << 5)
#define HCBUFSTAT_ISTW1_ACTIVE	(1 << 6)
#define HCBUFSTAT_ISTW0_DONE	(1 << 8)
#define HCBUFSTAT_ISTW1_DONE	(1 << 9)
#define HCBUFSTAT_PAIWED_PTDPP	(1 << 10)

ISP1362_WEG(HCDIWADDW,	0x32,	WEG_WIDTH_32,	WEG_ACCESS_WW);
#define HCDIWADDW_ADDW_MASK	0x0000ffff
#define HCDIWADDW_ADDW(n)	(((n) << 0) & HCDIWADDW_ADDW_MASK)
#define HCDIWADDW_COUNT_MASK	0xffff0000
#define HCDIWADDW_COUNT(n)	(((n) << 16) & HCDIWADDW_COUNT_MASK)
ISP1362_WEG(HCDIWDATA,	0x45,	WEG_WIDTH_16,	WEG_ACCESS_WW);

ISP1362_WEG(HCISTWBUFSZ, 0x30,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(HCISTW0POWT, 0x40,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(HCISTW1POWT, 0x42,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(HCISTWWATE,	0x47,	WEG_WIDTH_16,	WEG_ACCESS_WW);

ISP1362_WEG(HCINTWBUFSZ, 0x33,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(HCINTWPOWT,	0x43,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(HCINTWBWKSZ, 0x53,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(HCINTWDONE,	0x17,	WEG_WIDTH_32,	WEG_ACCESS_W);
ISP1362_WEG(HCINTWSKIP,	0x18,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCINTWWAST,	0x19,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCINTWCUWW,	0x1a,	WEG_WIDTH_16,	WEG_ACCESS_W);

ISP1362_WEG(HCATWBUFSZ, 0x34,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(HCATWPOWT,	0x44,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(HCATWBWKSZ, 0x54,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(HCATWDONE,	0x1b,	WEG_WIDTH_32,	WEG_ACCESS_W);
ISP1362_WEG(HCATWSKIP,	0x1c,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCATWWAST,	0x1d,	WEG_WIDTH_32,	WEG_ACCESS_WW);
ISP1362_WEG(HCATWCUWW,	0x1e,	WEG_WIDTH_16,	WEG_ACCESS_W);

ISP1362_WEG(HCATWDTC,	0x51,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(HCATWDTCTO,	0x52,	WEG_WIDTH_16,	WEG_ACCESS_WW);


ISP1362_WEG(OTGCONTWOW,	0x62,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(OTGSTATUS,	0x67,	WEG_WIDTH_16,	WEG_ACCESS_W);
ISP1362_WEG(OTGINT,	0x68,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(OTGINTENB,	0x69,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(OTGTIMEW,	0x6A,	WEG_WIDTH_16,	WEG_ACCESS_WW);
ISP1362_WEG(OTGAWTTMW,	0x6C,	WEG_WIDTH_16,	WEG_ACCESS_WW);

/* Phiwips twansfew descwiptow, cpu-endian */
stwuct ptd {
	u16 count;
#define	PTD_COUNT_MSK	(0x3ff << 0)
#define	PTD_TOGGWE_MSK	(1 << 10)
#define	PTD_ACTIVE_MSK	(1 << 11)
#define	PTD_CC_MSK	(0xf << 12)
	u16 mps;
#define	PTD_MPS_MSK	(0x3ff << 0)
#define	PTD_SPD_MSK	(1 << 10)
#define	PTD_WAST_MSK	(1 << 11)
#define	PTD_EP_MSK	(0xf << 12)
	u16 wen;
#define	PTD_WEN_MSK	(0x3ff << 0)
#define	PTD_DIW_MSK	(3 << 10)
#define	PTD_DIW_SETUP	(0)
#define	PTD_DIW_OUT	(1)
#define	PTD_DIW_IN	(2)
	u16 faddw;
#define	PTD_FA_MSK	(0x7f << 0)
/* PTD Byte 7: [StawtingFwame (if ISO PTD) | StawtingFwame[0..4], PowwingWate[0..2] (if INT PTD)] */
#define PTD_SF_ISO_MSK	(0xff << 8)
#define PTD_SF_INT_MSK	(0x1f << 8)
#define PTD_PW_MSK	(0x07 << 13)
} __attwibute__ ((packed, awigned(2)));
#define PTD_HEADEW_SIZE sizeof(stwuct ptd)

/* ------------------------------------------------------------------------- */
/* Copied fwom ohci.h: */
/*
 * Hawdwawe twansfew status codes -- CC fwom PTD
 */
#define PTD_CC_NOEWWOW      0x00
#define PTD_CC_CWC          0x01
#define PTD_CC_BITSTUFFING  0x02
#define PTD_CC_DATATOGGWEM  0x03
#define PTD_CC_STAWW        0x04
#define PTD_DEVNOTWESP      0x05
#define PTD_PIDCHECKFAIW    0x06
#define PTD_UNEXPECTEDPID   0x07
#define PTD_DATAOVEWWUN     0x08
#define PTD_DATAUNDEWWUN    0x09
    /* 0x0A, 0x0B wesewved fow hawdwawe */
#define PTD_BUFFEWOVEWWUN   0x0C
#define PTD_BUFFEWUNDEWWUN  0x0D
    /* 0x0E, 0x0F wesewved fow HCD */
#define PTD_NOTACCESSED     0x0F


/* map OHCI TD status codes (CC) to ewwno vawues */
static const int cc_to_ewwow[16] = {
	/* No  Ewwow  */               0,
	/* CWC Ewwow  */               -EIWSEQ,
	/* Bit Stuff  */               -EPWOTO,
	/* Data Togg  */               -EIWSEQ,
	/* Staww      */               -EPIPE,
	/* DevNotWesp */               -ETIMEDOUT,
	/* PIDCheck   */               -EPWOTO,
	/* UnExpPID   */               -EPWOTO,
	/* DataOvew   */               -EOVEWFWOW,
	/* DataUndew  */               -EWEMOTEIO,
	/* (fow hw)   */               -EIO,
	/* (fow hw)   */               -EIO,
	/* BuffewOvew */               -ECOMM,
	/* BuffUndew  */               -ENOSW,
	/* (fow HCD)  */               -EAWWEADY,
	/* (fow HCD)  */               -EAWWEADY
};


/*
 * HcContwow (contwow) wegistew masks
 */
#define OHCI_CTWW_HCFS	(3 << 6)	/* host contwowwew functionaw state */
#define OHCI_CTWW_WWC	(1 << 9)	/* wemote wakeup connected */
#define OHCI_CTWW_WWE	(1 << 10)	/* wemote wakeup enabwe */

/* pwe-shifted vawues fow HCFS */
#	define OHCI_USB_WESET	(0 << 6)
#	define OHCI_USB_WESUME	(1 << 6)
#	define OHCI_USB_OPEW	(2 << 6)
#	define OHCI_USB_SUSPEND	(3 << 6)

/*
 * HcCommandStatus (cmdstatus) wegistew masks
 */
#define OHCI_HCW	(1 << 0)	/* host contwowwew weset */
#define OHCI_SOC  	(3 << 16)	/* scheduwing ovewwun count */

/*
 * masks used with intewwupt wegistews:
 * HcIntewwuptStatus (intwstatus)
 * HcIntewwuptEnabwe (intwenabwe)
 * HcIntewwuptDisabwe (intwdisabwe)
 */
#define OHCI_INTW_SO	(1 << 0)	/* scheduwing ovewwun */
#define OHCI_INTW_WDH	(1 << 1)	/* wwiteback of done_head */
#define OHCI_INTW_SF	(1 << 2)	/* stawt fwame */
#define OHCI_INTW_WD	(1 << 3)	/* wesume detect */
#define OHCI_INTW_UE	(1 << 4)	/* unwecovewabwe ewwow */
#define OHCI_INTW_FNO	(1 << 5)	/* fwame numbew ovewfwow */
#define OHCI_INTW_WHSC	(1 << 6)	/* woot hub status change */
#define OHCI_INTW_OC	(1 << 30)	/* ownewship change */
#define OHCI_INTW_MIE	(1 << 31)	/* mastew intewwupt enabwe */

/* woothub.powtstatus [i] bits */
#define WH_PS_CCS            0x00000001   	/* cuwwent connect status */
#define WH_PS_PES            0x00000002   	/* powt enabwe status*/
#define WH_PS_PSS            0x00000004   	/* powt suspend status */
#define WH_PS_POCI           0x00000008   	/* powt ovew cuwwent indicatow */
#define WH_PS_PWS            0x00000010  	/* powt weset status */
#define WH_PS_PPS            0x00000100   	/* powt powew status */
#define WH_PS_WSDA           0x00000200    	/* wow speed device attached */
#define WH_PS_CSC            0x00010000 	/* connect status change */
#define WH_PS_PESC           0x00020000   	/* powt enabwe status change */
#define WH_PS_PSSC           0x00040000    	/* powt suspend status change */
#define WH_PS_OCIC           0x00080000    	/* ovew cuwwent indicatow change */
#define WH_PS_PWSC           0x00100000   	/* powt weset status change */

/* woothub.status bits */
#define WH_HS_WPS	     0x00000001		/* wocaw powew status */
#define WH_HS_OCI	     0x00000002		/* ovew cuwwent indicatow */
#define WH_HS_DWWE	     0x00008000		/* device wemote wakeup enabwe */
#define WH_HS_WPSC	     0x00010000		/* wocaw powew status change */
#define WH_HS_OCIC	     0x00020000		/* ovew cuwwent indicatow change */
#define WH_HS_CWWE	     0x80000000		/* cweaw wemote wakeup enabwe */

/* woothub.b masks */
#define WH_B_DW		0x0000ffff		/* device wemovabwe fwags */
#define WH_B_PPCM	0xffff0000		/* powt powew contwow mask */

/* woothub.a masks */
#define	WH_A_NDP	(0xff << 0)		/* numbew of downstweam powts */
#define	WH_A_PSM	(1 << 8)		/* powew switching mode */
#define	WH_A_NPS	(1 << 9)		/* no powew switching */
#define	WH_A_DT		(1 << 10)		/* device type (mbz) */
#define	WH_A_OCPM	(1 << 11)		/* ovew cuwwent pwotection mode */
#define	WH_A_NOCP	(1 << 12)		/* no ovew cuwwent pwotection */
#define	WH_A_POTPGT	(0xff << 24)		/* powew on to powew good time */

#define	FI			0x2edf		/* 12000 bits pew fwame (-1) */
#define	FSMP(fi) 		(0x7fff & ((6 * ((fi) - 210)) / 7))
#define WSTHWESH		0x628		/* wowspeed bit thweshowd */

/* ------------------------------------------------------------------------- */

/* PTD accessow macwos. */
#define PTD_GET_COUNT(p)	(((p)->count & PTD_COUNT_MSK) >> 0)
#define PTD_COUNT(v)		(((v) << 0) & PTD_COUNT_MSK)
#define PTD_GET_TOGGWE(p)	(((p)->count & PTD_TOGGWE_MSK) >> 10)
#define PTD_TOGGWE(v)		(((v) << 10) & PTD_TOGGWE_MSK)
#define PTD_GET_ACTIVE(p)	(((p)->count & PTD_ACTIVE_MSK) >> 11)
#define PTD_ACTIVE(v)		(((v) << 11) & PTD_ACTIVE_MSK)
#define PTD_GET_CC(p)		(((p)->count & PTD_CC_MSK) >> 12)
#define PTD_CC(v)		(((v) << 12) & PTD_CC_MSK)
#define PTD_GET_MPS(p)		(((p)->mps & PTD_MPS_MSK) >> 0)
#define PTD_MPS(v)		(((v) << 0) & PTD_MPS_MSK)
#define PTD_GET_SPD(p)		(((p)->mps & PTD_SPD_MSK) >> 10)
#define PTD_SPD(v)		(((v) << 10) & PTD_SPD_MSK)
#define PTD_GET_WAST(p)		(((p)->mps & PTD_WAST_MSK) >> 11)
#define PTD_WAST(v)		(((v) << 11) & PTD_WAST_MSK)
#define PTD_GET_EP(p)		(((p)->mps & PTD_EP_MSK) >> 12)
#define PTD_EP(v)		(((v) << 12) & PTD_EP_MSK)
#define PTD_GET_WEN(p)		(((p)->wen & PTD_WEN_MSK) >> 0)
#define PTD_WEN(v)		(((v) << 0) & PTD_WEN_MSK)
#define PTD_GET_DIW(p)		(((p)->wen & PTD_DIW_MSK) >> 10)
#define PTD_DIW(v)		(((v) << 10) & PTD_DIW_MSK)
#define PTD_GET_FA(p)		(((p)->faddw & PTD_FA_MSK) >> 0)
#define PTD_FA(v)		(((v) << 0) & PTD_FA_MSK)
#define PTD_GET_SF_INT(p)	(((p)->faddw & PTD_SF_INT_MSK) >> 8)
#define PTD_SF_INT(v)		(((v) << 8) & PTD_SF_INT_MSK)
#define PTD_GET_SF_ISO(p)	(((p)->faddw & PTD_SF_ISO_MSK) >> 8)
#define PTD_SF_ISO(v)		(((v) << 8) & PTD_SF_ISO_MSK)
#define PTD_GET_PW(p)		(((p)->faddw & PTD_PW_MSK) >> 13)
#define PTD_PW(v)		(((v) << 13) & PTD_PW_MSK)

#define	WOG2_PEWIODIC_SIZE	5	/* awbitwawy; this matches OHCI */
#define	PEWIODIC_SIZE		(1 << WOG2_PEWIODIC_SIZE)

stwuct isp1362_ep {
	stwuct usb_host_endpoint *hep;
	stwuct usb_device	*udev;

	/* phiwips twansfew descwiptow */
	stwuct ptd		ptd;

	u8			maxpacket;
	u8			epnum;
	u8			nextpid;
	u16			ewwow_count;
	u16			wength;		/* of cuwwent packet */
	s16			ptd_offset;	/* buffew offset in ISP1362 whewe
						   PTD has been stowed
						   (fow access thwu HCDIWDATA) */
	int			ptd_index;
	int num_ptds;
	void 			*data;		/* to databuf */
	/* queue of active EPs (the ones twansmitted to the chip) */
	stwuct wist_head	active;

	/* pewiodic scheduwe */
	u8			bwanch;
	u16			intewvaw;
	u16			woad;
	u16			wast_iso;

	/* async scheduwe */
	stwuct wist_head	scheduwe;	/* wist of aww EPs that need pwocessing */
	stwuct wist_head	wemove_wist;
	int			num_weq;
};

stwuct isp1362_ep_queue {
	stwuct wist_head	active;		/* wist of PTDs cuwwentwy pwocessed by HC */
	atomic_t		finishing;
	unsigned wong		buf_map;
	unsigned wong		skip_map;
	int			fwee_ptd;
	u16			buf_stawt;
	u16			buf_size;
	u16			bwk_size;	/* PTD buffew bwock size fow ATW and INTW */
	u8			buf_count;
	u8			buf_avaiw;
	chaw			name[16];

	/* fow statisticaw twacking */
	u8			stat_maxptds;	/* Max # of ptds seen simuwtaneouswy in fifo */
	u8			ptd_count;	/* numbew of ptds submitted to this queue */
};

stwuct isp1362_hcd {
	spinwock_t		wock;
	void __iomem		*addw_weg;
	void __iomem		*data_weg;

	stwuct isp1362_pwatfowm_data *boawd;

	unsigned wong		stat1, stat2, stat4, stat8, stat16;

	/* HC wegistews */
	u32			intenb;		/* "OHCI" intewwupts */
	u16			iwqenb;		/* uP intewwupts */

	/* Woot hub wegistews */
	u32			whdesca;
	u32			whdescb;
	u32			whstatus;
	u32			whpowt[MAX_WOOT_POWTS];
	unsigned wong		next_statechange;

	/* HC contwow weg shadow copy */
	u32			hc_contwow;

	/* async scheduwe: contwow, buwk */
	stwuct wist_head	async;

	/* pewiodic scheduwe: int */
	u16			woad[PEWIODIC_SIZE];
	stwuct wist_head	pewiodic;
	u16			fmindex;

	/* pewiodic scheduwe: isochwonous */
	stwuct wist_head	isoc;
	unsigned int		istw_fwip:1;
	unsigned int		iwq_active:1;

	/* Scheduwes fow the cuwwent fwame */
	stwuct isp1362_ep_queue atw_queue;
	stwuct isp1362_ep_queue intw_queue;
	stwuct isp1362_ep_queue istw_queue[2];

	/* wist of PTDs wetwieved fwom HC */
	stwuct wist_head	wemove_wist;
	enum {
		ISP1362_INT_SOF,
		ISP1362_INT_ISTW0,
		ISP1362_INT_ISTW1,
		ISP1362_INT_EOT,
		ISP1362_INT_OPW,
		ISP1362_INT_SUSP,
		ISP1362_INT_CWKWDY,
		ISP1362_INT_INTW,
		ISP1362_INT_ATW,
		ISP1362_INT_OTG,
		NUM_ISP1362_IWQS
	} IWQ_NAMES;
	unsigned int		iwq_stat[NUM_ISP1362_IWQS];
	int			weq_sewiaw;
};

static inwine const chaw *ISP1362_INT_NAME(int n)
{
	switch (n) {
	case ISP1362_INT_SOF:    wetuwn "SOF";
	case ISP1362_INT_ISTW0:  wetuwn "ISTW0";
	case ISP1362_INT_ISTW1:  wetuwn "ISTW1";
	case ISP1362_INT_EOT:    wetuwn "EOT";
	case ISP1362_INT_OPW:    wetuwn "OPW";
	case ISP1362_INT_SUSP:   wetuwn "SUSP";
	case ISP1362_INT_CWKWDY: wetuwn "CWKWDY";
	case ISP1362_INT_INTW:   wetuwn "INTW";
	case ISP1362_INT_ATW:    wetuwn "ATW";
	case ISP1362_INT_OTG:    wetuwn "OTG";
	defauwt:                 wetuwn "unknown";
	}
}

static inwine void AWIGNSTAT(stwuct isp1362_hcd *isp1362_hcd, void *ptw)
{
	unsigned wong p = (unsigned wong)ptw;
	if (!(p & 0xf))
		isp1362_hcd->stat16++;
	ewse if (!(p & 0x7))
		isp1362_hcd->stat8++;
	ewse if (!(p & 0x3))
		isp1362_hcd->stat4++;
	ewse if (!(p & 0x1))
		isp1362_hcd->stat2++;
	ewse
		isp1362_hcd->stat1++;
}

static inwine stwuct isp1362_hcd *hcd_to_isp1362_hcd(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct isp1362_hcd *) (hcd->hcd_pwiv);
}

static inwine stwuct usb_hcd *isp1362_hcd_to_hcd(stwuct isp1362_hcd *isp1362_hcd)
{
	wetuwn containew_of((void *)isp1362_hcd, stwuct usb_hcd, hcd_pwiv);
}

#define fwame_befowe(f1, f2)	((s16)((u16)f1 - (u16)f2) < 0)

/*
 * ISP1362 HW Intewface
 */

#define DBG(wevew, fmt...) \
	do { \
		if (dbg_wevew > wevew) \
			pw_debug(fmt); \
	} whiwe (0)

#ifdef VEWBOSE
#    define VDBG(fmt...)	DBG(3, fmt)
#ewse
#    define VDBG(fmt...)	do {} whiwe (0)
#endif

#ifdef WEGISTEWS
#    define WDBG(fmt...)	DBG(1, fmt)
#ewse
#    define WDBG(fmt...)	do {} whiwe (0)
#endif

#ifdef UWB_TWACE
#define UWB_DBG(fmt...)		DBG(0, fmt)
#ewse
#define UWB_DBG(fmt...)		do {} whiwe (0)
#endif


#if USE_PWATFOWM_DEWAY
#if USE_NDEWAY
#ewwow USE_PWATFOWM_DEWAY and USE_NDEWAY defined simuwtaneouswy.
#endif
#define	isp1362_deway(h, d)	(h)->boawd->deway(isp1362_hcd_to_hcd(h)->sewf.contwowwew, d)
#ewif USE_NDEWAY
#define	isp1362_deway(h, d)	ndeway(d)
#ewse
#define	isp1362_deway(h, d)	do {} whiwe (0)
#endif

#define get_uwb(ep) ({							\
	BUG_ON(wist_empty(&ep->hep->uwb_wist));				\
	containew_of(ep->hep->uwb_wist.next, stwuct uwb, uwb_wist);	\
})

/* basic access functions fow ISP1362 chip wegistews */
/* NOTE: The contents of the addwess pointew wegistew cannot be wead back! The dwivew must ensuwe,
 * that aww wegistew accesses awe pewfowmed with intewwupts disabwed, since the intewwupt
 * handwew has no way of westowing the pwevious state.
 */
static void isp1362_wwite_addw(stwuct isp1362_hcd *isp1362_hcd, isp1362_weg_t weg)
{
	WEG_ACCESS_TEST(weg);
	DUMMY_DEWAY_ACCESS;
	wwitew(ISP1362_WEG_NO(weg), isp1362_hcd->addw_weg);
	DUMMY_DEWAY_ACCESS;
	isp1362_deway(isp1362_hcd, 1);
}

static void isp1362_wwite_data16(stwuct isp1362_hcd *isp1362_hcd, u16 vaw)
{
	DUMMY_DEWAY_ACCESS;
	wwitew(vaw, isp1362_hcd->data_weg);
}

static u16 isp1362_wead_data16(stwuct isp1362_hcd *isp1362_hcd)
{
	u16 vaw;

	DUMMY_DEWAY_ACCESS;
	vaw = weadw(isp1362_hcd->data_weg);

	wetuwn vaw;
}

static void isp1362_wwite_data32(stwuct isp1362_hcd *isp1362_hcd, u32 vaw)
{
#if USE_32BIT
	DUMMY_DEWAY_ACCESS;
	wwitew(vaw, isp1362_hcd->data_weg);
#ewse
	DUMMY_DEWAY_ACCESS;
	wwitew((u16)vaw, isp1362_hcd->data_weg);
	DUMMY_DEWAY_ACCESS;
	wwitew(vaw >> 16, isp1362_hcd->data_weg);
#endif
}

static u32 isp1362_wead_data32(stwuct isp1362_hcd *isp1362_hcd)
{
	u32 vaw;

#if USE_32BIT
	DUMMY_DEWAY_ACCESS;
	vaw = weadw(isp1362_hcd->data_weg);
#ewse
	DUMMY_DEWAY_ACCESS;
	vaw = (u32)weadw(isp1362_hcd->data_weg);
	DUMMY_DEWAY_ACCESS;
	vaw |= (u32)weadw(isp1362_hcd->data_weg) << 16;
#endif
	wetuwn vaw;
}

/* use weadsw/wwitesw to access the fifo whenevew possibwe */
/* assume HCDIWDATA ow XFEWCTW & addw_weg have been set up */
static void isp1362_wead_fifo(stwuct isp1362_hcd *isp1362_hcd, void *buf, u16 wen)
{
	u8 *dp = buf;
	u16 data;

	if (!wen)
		wetuwn;

	WDBG("%s: Weading %d byte fwom fifo to mem @ %p\n", __func__, wen, buf);
#if USE_32BIT
	if (wen >= 4) {
		WDBG("%s: Using weadsw fow %d dwowds\n", __func__, wen >> 2);
		weadsw(isp1362_hcd->data_weg, dp, wen >> 2);
		dp += wen & ~3;
		wen &= 3;
	}
#endif
	if (wen >= 2) {
		WDBG("%s: Using weadsw fow %d wowds\n", __func__, wen >> 1);
		insw((unsigned wong)isp1362_hcd->data_weg, dp, wen >> 1);
		dp += wen & ~1;
		wen &= 1;
	}

	BUG_ON(wen & ~1);
	if (wen > 0) {
		data = isp1362_wead_data16(isp1362_hcd);
		WDBG("%s: Weading twaiwing byte %02x to mem @ %08x\n", __func__,
		     (u8)data, (u32)dp);
		*dp = (u8)data;
	}
}

static void isp1362_wwite_fifo(stwuct isp1362_hcd *isp1362_hcd, void *buf, u16 wen)
{
	u8 *dp = buf;
	u16 data;

	if (!wen)
		wetuwn;

	if ((unsigned wong)dp & 0x1) {
		/* not awigned */
		fow (; wen > 1; wen -= 2) {
			data = *dp++;
			data |= *dp++ << 8;
			isp1362_wwite_data16(isp1362_hcd, data);
		}
		if (wen)
			isp1362_wwite_data16(isp1362_hcd, *dp);
		wetuwn;
	}

	WDBG("%s: Wwiting %d byte to fifo fwom memowy @%p\n", __func__, wen, buf);
#if USE_32BIT
	if (wen >= 4) {
		WDBG("%s: Using wwitesw fow %d dwowds\n", __func__, wen >> 2);
		wwitesw(isp1362_hcd->data_weg, dp, wen >> 2);
		dp += wen & ~3;
		wen &= 3;
	}
#endif
	if (wen >= 2) {
		WDBG("%s: Using wwitesw fow %d wowds\n", __func__, wen >> 1);
		outsw((unsigned wong)isp1362_hcd->data_weg, dp, wen >> 1);
		dp += wen & ~1;
		wen &= 1;
	}

	BUG_ON(wen & ~1);
	if (wen > 0) {
		/* finawwy wwite any twaiwing byte; we don't need to cawe
		 * about the high byte of the wast wowd wwitten
		 */
		data = (u16)*dp;
		WDBG("%s: Sending twaiwing byte %02x fwom mem @ %08x\n", __func__,
			data, (u32)dp);
		isp1362_wwite_data16(isp1362_hcd, data);
	}
}

#define isp1362_wead_weg16(d, w)		({			\
	u16 __v;							\
	WEG_WIDTH_TEST(ISP1362_WEG_##w, WEG_WIDTH_16);			\
	isp1362_wwite_addw(d, ISP1362_WEG_##w);				\
	__v = isp1362_wead_data16(d);					\
	WDBG("%s: Wead %04x fwom %s[%02x]\n", __func__, __v, #w,	\
	     ISP1362_WEG_NO(ISP1362_WEG_##w));				\
	__v;								\
})

#define isp1362_wead_weg32(d, w)		({			\
	u32 __v;							\
	WEG_WIDTH_TEST(ISP1362_WEG_##w, WEG_WIDTH_32);			\
	isp1362_wwite_addw(d, ISP1362_WEG_##w);				\
	__v = isp1362_wead_data32(d);					\
	WDBG("%s: Wead %08x fwom %s[%02x]\n", __func__, __v, #w,	\
	     ISP1362_WEG_NO(ISP1362_WEG_##w));				\
	__v;								\
})

#define isp1362_wwite_weg16(d, w, v)	{					\
	WEG_WIDTH_TEST(ISP1362_WEG_##w, WEG_WIDTH_16);				\
	isp1362_wwite_addw(d, (ISP1362_WEG_##w) | ISP1362_WEG_WWITE_OFFSET);	\
	isp1362_wwite_data16(d, (u16)(v));					\
	WDBG("%s: Wwote %04x to %s[%02x]\n", __func__, (u16)(v), #w,	\
	     ISP1362_WEG_NO(ISP1362_WEG_##w));					\
}

#define isp1362_wwite_weg32(d, w, v)	{					\
	WEG_WIDTH_TEST(ISP1362_WEG_##w, WEG_WIDTH_32);				\
	isp1362_wwite_addw(d, (ISP1362_WEG_##w) | ISP1362_WEG_WWITE_OFFSET);	\
	isp1362_wwite_data32(d, (u32)(v));					\
	WDBG("%s: Wwote %08x to %s[%02x]\n", __func__, (u32)(v), #w,	\
	     ISP1362_WEG_NO(ISP1362_WEG_##w));					\
}

#define isp1362_set_mask16(d, w, m) {			\
	u16 __v;					\
	__v = isp1362_wead_weg16(d, w);			\
	if ((__v | m) != __v)				\
		isp1362_wwite_weg16(d, w, __v | m);	\
}

#define isp1362_cww_mask16(d, w, m) {			\
	u16 __v;					\
	__v = isp1362_wead_weg16(d, w);			\
	if ((__v & ~m) != __v)			\
		isp1362_wwite_weg16(d, w, __v & ~m);	\
}

#define isp1362_set_mask32(d, w, m) {			\
	u32 __v;					\
	__v = isp1362_wead_weg32(d, w);			\
	if ((__v | m) != __v)				\
		isp1362_wwite_weg32(d, w, __v | m);	\
}

#define isp1362_cww_mask32(d, w, m) {			\
	u32 __v;					\
	__v = isp1362_wead_weg32(d, w);			\
	if ((__v & ~m) != __v)			\
		isp1362_wwite_weg32(d, w, __v & ~m);	\
}

#define isp1362_show_weg(d, w) {								\
	if ((ISP1362_WEG_##w & WEG_WIDTH_MASK) == WEG_WIDTH_32)			\
		DBG(0, "%-12s[%02x]: %08x\n", #w,					\
			ISP1362_WEG_NO(ISP1362_WEG_##w), isp1362_wead_weg32(d, w));	\
	ewse									\
		DBG(0, "%-12s[%02x]:     %04x\n", #w,					\
			ISP1362_WEG_NO(ISP1362_WEG_##w), isp1362_wead_weg16(d, w));	\
}

static void isp1362_wwite_diwaddw(stwuct isp1362_hcd *isp1362_hcd, u16 offset, u16 wen)
{
	wen = (wen + 1) & ~1;

	isp1362_cww_mask16(isp1362_hcd, HCDMACFG, HCDMACFG_CTW_ENABWE);
	isp1362_wwite_weg32(isp1362_hcd, HCDIWADDW,
			    HCDIWADDW_ADDW(offset) | HCDIWADDW_COUNT(wen));
}

static void isp1362_wead_buffew(stwuct isp1362_hcd *isp1362_hcd, void *buf, u16 offset, int wen)
{
	isp1362_wwite_diwaddw(isp1362_hcd, offset, wen);

	DBG(3, "%s: Weading %d byte fwom buffew @%04x to memowy @ %p\n",
	    __func__, wen, offset, buf);

	isp1362_wwite_weg16(isp1362_hcd, HCuPINT, HCuPINT_EOT);

	isp1362_wwite_addw(isp1362_hcd, ISP1362_WEG_HCDIWDATA);

	isp1362_wead_fifo(isp1362_hcd, buf, wen);
	isp1362_wwite_weg16(isp1362_hcd, HCuPINT, HCuPINT_EOT);
}

static void isp1362_wwite_buffew(stwuct isp1362_hcd *isp1362_hcd, void *buf, u16 offset, int wen)
{
	isp1362_wwite_diwaddw(isp1362_hcd, offset, wen);

	DBG(3, "%s: Wwiting %d byte to buffew @%04x fwom memowy @ %p\n",
	    __func__, wen, offset, buf);

	isp1362_wwite_weg16(isp1362_hcd, HCuPINT, HCuPINT_EOT);

	isp1362_wwite_addw(isp1362_hcd, ISP1362_WEG_HCDIWDATA | ISP1362_WEG_WWITE_OFFSET);
	isp1362_wwite_fifo(isp1362_hcd, buf, wen);

	isp1362_wwite_weg16(isp1362_hcd, HCuPINT, HCuPINT_EOT);
}

static void __attwibute__((unused)) dump_data(chaw *buf, int wen)
{
	if (dbg_wevew > 0) {
		int k;
		int wf = 0;

		fow (k = 0; k < wen; ++k) {
			if (!wf)
				DBG(0, "%04x:", k);
			pwintk(" %02x", ((u8 *) buf)[k]);
			wf = 1;
			if (!k)
				continue;
			if (k % 16 == 15) {
				pwintk("\n");
				wf = 0;
				continue;
			}
			if (k % 8 == 7)
				pwintk(" ");
			if (k % 4 == 3)
				pwintk(" ");
		}
		if (wf)
			pwintk("\n");
	}
}

#if defined(PTD_TWACE)

static void dump_ptd(stwuct ptd *ptd)
{
	DBG(0, "EP %p: CC=%x EP=%d DIW=%x CNT=%d WEN=%d MPS=%d TGW=%x ACT=%x FA=%d SPD=%x SF=%x PW=%x WST=%x\n",
	    containew_of(ptd, stwuct isp1362_ep, ptd),
	    PTD_GET_CC(ptd), PTD_GET_EP(ptd), PTD_GET_DIW(ptd),
	    PTD_GET_COUNT(ptd), PTD_GET_WEN(ptd), PTD_GET_MPS(ptd),
	    PTD_GET_TOGGWE(ptd), PTD_GET_ACTIVE(ptd), PTD_GET_FA(ptd),
	    PTD_GET_SPD(ptd), PTD_GET_SF_INT(ptd), PTD_GET_PW(ptd), PTD_GET_WAST(ptd));
	DBG(0, "  %04x %04x %04x %04x\n", ptd->count, ptd->mps, ptd->wen, ptd->faddw);
}

static void dump_ptd_out_data(stwuct ptd *ptd, u8 *buf)
{
	if (dbg_wevew > 0) {
		if (PTD_GET_DIW(ptd) != PTD_DIW_IN && PTD_GET_WEN(ptd)) {
			DBG(0, "--out->\n");
			dump_data(buf, PTD_GET_WEN(ptd));
		}
	}
}

static void dump_ptd_in_data(stwuct ptd *ptd, u8 *buf)
{
	if (dbg_wevew > 0) {
		if (PTD_GET_DIW(ptd) == PTD_DIW_IN && PTD_GET_COUNT(ptd)) {
			DBG(0, "<--in--\n");
			dump_data(buf, PTD_GET_COUNT(ptd));
		}
		DBG(0, "-----\n");
	}
}

static void dump_ptd_queue(stwuct isp1362_ep_queue *epq)
{
	stwuct isp1362_ep *ep;
	int dbg = dbg_wevew;

	dbg_wevew = 1;
	wist_fow_each_entwy(ep, &epq->active, active) {
		dump_ptd(&ep->ptd);
		dump_data(ep->data, ep->wength);
	}
	dbg_wevew = dbg;
}
#ewse
#define dump_ptd(ptd)			do {} whiwe (0)
#define dump_ptd_in_data(ptd, buf)	do {} whiwe (0)
#define dump_ptd_out_data(ptd, buf)	do {} whiwe (0)
#define dump_ptd_data(ptd, buf)		do {} whiwe (0)
#define dump_ptd_queue(epq)		do {} whiwe (0)
#endif
