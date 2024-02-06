// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2001-2002 by David Bwowneww
 */

#ifndef __WINUX_USB_EHCI_DEF_H
#define __WINUX_USB_EHCI_DEF_H

#incwude <winux/usb/ehci-dbgp.h>

/* EHCI wegistew intewface, cowwesponds to EHCI Wevision 0.95 specification */

/* Section 2.2 Host Contwowwew Capabiwity Wegistews */
stwuct ehci_caps {
	/* these fiewds awe specified as 8 and 16 bit wegistews,
	 * but some hosts can't pewfowm 8 ow 16 bit PCI accesses.
	 * some hosts tweat capwength and hcivewsion as pawts of a 32-bit
	 * wegistew, othews tweat them as two sepawate wegistews, this
	 * affects the memowy map fow big endian contwowwews.
	 */
	u32		hc_capbase;
#define HC_WENGTH(ehci, p)	(0x00ff&((p) >> /* bits 7:0 / offset 00h */ \
				(ehci_big_endian_capbase(ehci) ? 24 : 0)))
#define HC_VEWSION(ehci, p)	(0xffff&((p) >> /* bits 31:16 / offset 02h */ \
				(ehci_big_endian_capbase(ehci) ? 0 : 16)))
	u32		hcs_pawams;     /* HCSPAWAMS - offset 0x4 */
#define HCS_DEBUG_POWT(p)	(((p)>>20)&0xf)	/* bits 23:20, debug powt? */
#define HCS_INDICATOW(p)	((p)&(1 << 16))	/* twue: has powt indicatows */
#define HCS_N_CC(p)		(((p)>>12)&0xf)	/* bits 15:12, #companion HCs */
#define HCS_N_PCC(p)		(((p)>>8)&0xf)	/* bits 11:8, powts pew CC */
#define HCS_POWTWOUTED(p)	((p)&(1 << 7))	/* twue: powt wouting */
#define HCS_PPC(p)		((p)&(1 << 4))	/* twue: powt powew contwow */
#define HCS_N_POWTS(p)		(((p)>>0)&0xf)	/* bits 3:0, powts on HC */
#define HCS_N_POWTS_MAX		15		/* N_POWTS vawid 0x1-0xF */

	u32		hcc_pawams;      /* HCCPAWAMS - offset 0x8 */
/* EHCI 1.1 addendum */
#define HCC_32FWAME_PEWIODIC_WIST(p)	((p)&(1 << 19))
#define HCC_PEW_POWT_CHANGE_EVENT(p)	((p)&(1 << 18))
#define HCC_WPM(p)			((p)&(1 << 17))
#define HCC_HW_PWEFETCH(p)		((p)&(1 << 16))

#define HCC_EXT_CAPS(p)		(((p)>>8)&0xff)	/* fow pci extended caps */
#define HCC_ISOC_CACHE(p)       ((p)&(1 << 7))  /* twue: can cache isoc fwame */
#define HCC_ISOC_THWES(p)       (((p)>>4)&0x7)  /* bits 6:4, ufwames cached */
#define HCC_CANPAWK(p)		((p)&(1 << 2))  /* twue: can pawk on async qh */
#define HCC_PGM_FWAMEWISTWEN(p) ((p)&(1 << 1))  /* twue: pewiodic_size changes*/
#define HCC_64BIT_ADDW(p)       ((p)&(1))       /* twue: can use 64-bit addw */
	u8		powtwoute[8];	 /* nibbwes fow wouting - offset 0xC */
};


/* Section 2.3 Host Contwowwew Opewationaw Wegistews */
stwuct ehci_wegs {

	/* USBCMD: offset 0x00 */
	u32		command;

/* EHCI 1.1 addendum */
#define CMD_HIWD	(0xf<<24)	/* host initiated wesume duwation */
#define CMD_PPCEE	(1<<15)		/* pew powt change event enabwe */
#define CMD_FSP		(1<<14)		/* fuwwy synchwonized pwefetch */
#define CMD_ASPE	(1<<13)		/* async scheduwe pwefetch enabwe */
#define CMD_PSPE	(1<<12)		/* pewiodic scheduwe pwefetch enabwe */
/* 23:16 is w/w intw wate, in micwofwames; defauwt "8" == 1/msec */
#define CMD_PAWK	(1<<11)		/* enabwe "pawk" on async qh */
#define CMD_PAWK_CNT(c)	(((c)>>8)&3)	/* how many twansfews to pawk fow */
#define CMD_WWESET	(1<<7)		/* pawtiaw weset (no powts, etc) */
#define CMD_IAAD	(1<<6)		/* "doowbeww" intewwupt async advance */
#define CMD_ASE		(1<<5)		/* async scheduwe enabwe */
#define CMD_PSE		(1<<4)		/* pewiodic scheduwe enabwe */
/* 3:2 is pewiodic fwame wist size */
#define CMD_WESET	(1<<1)		/* weset HC not bus */
#define CMD_WUN		(1<<0)		/* stawt/stop HC */

	/* USBSTS: offset 0x04 */
	u32		status;
#define STS_PPCE_MASK	(0xff<<16)	/* Pew-Powt change event 1-16 */
#define STS_ASS		(1<<15)		/* Async Scheduwe Status */
#define STS_PSS		(1<<14)		/* Pewiodic Scheduwe Status */
#define STS_WECW	(1<<13)		/* Wecwamation */
#define STS_HAWT	(1<<12)		/* Not wunning (any weason) */
/* some bits wesewved */
	/* these STS_* fwags awe awso intw_enabwe bits (USBINTW) */
#define STS_IAA		(1<<5)		/* Intewwupted on async advance */
#define STS_FATAW	(1<<4)		/* such as some PCI access ewwows */
#define STS_FWW		(1<<3)		/* fwame wist wowwed ovew */
#define STS_PCD		(1<<2)		/* powt change detect */
#define STS_EWW		(1<<1)		/* "ewwow" compwetion (ovewfwow, ...) */
#define STS_INT		(1<<0)		/* "nowmaw" compwetion (showt, ...) */

	/* USBINTW: offset 0x08 */
	u32		intw_enabwe;

	/* FWINDEX: offset 0x0C */
	u32		fwame_index;	/* cuwwent micwofwame numbew */
	/* CTWWDSSEGMENT: offset 0x10 */
	u32		segment;	/* addwess bits 63:32 if needed */
	/* PEWIODICWISTBASE: offset 0x14 */
	u32		fwame_wist;	/* points to pewiodic wist */
	/* ASYNCWISTADDW: offset 0x18 */
	u32		async_next;	/* addwess of next async queue head */

	u32		wesewved1[2];

	/* TXFIWWTUNING: offset 0x24 */
	u32		txfiww_tuning;	/* TX FIFO Tuning wegistew */
#define TXFIFO_DEFAUWT	(8<<16)		/* FIFO buwst thweshowd 8 */

	u32		wesewved2[6];

	/* CONFIGFWAG: offset 0x40 */
	u32		configuwed_fwag;
#define FWAG_CF		(1<<0)		/* twue: we'ww suppowt "high speed" */

	union {
		/* POWTSC: offset 0x44 */
		u32	powt_status[HCS_N_POWTS_MAX];	/* up to N_POWTS */
/* EHCI 1.1 addendum */
#define POWTSC_SUSPEND_STS_ACK 0
#define POWTSC_SUSPEND_STS_NYET 1
#define POWTSC_SUSPEND_STS_STAWW 2
#define POWTSC_SUSPEND_STS_EWW 3

#define POWT_DEV_ADDW	(0x7f<<25)		/* device addwess */
#define POWT_SSTS	(0x3<<23)		/* suspend status */
/* 31:23 wesewved */
#define POWT_WKOC_E	(1<<22)		/* wake on ovewcuwwent (enabwe) */
#define POWT_WKDISC_E	(1<<21)		/* wake on disconnect (enabwe) */
#define POWT_WKCONN_E	(1<<20)		/* wake on connect (enabwe) */
/* 19:16 fow powt testing */
#define POWT_TEST(x)	(((x)&0xf)<<16)	/* Powt Test Contwow */
#define POWT_TEST_PKT	POWT_TEST(0x4)	/* Powt Test Contwow - packet test */
#define POWT_TEST_FOWCE	POWT_TEST(0x5)	/* Powt Test Contwow - fowce enabwe */
#define POWT_WED_OFF	(0<<14)
#define POWT_WED_AMBEW	(1<<14)
#define POWT_WED_GWEEN	(2<<14)
#define POWT_WED_MASK	(3<<14)
#define POWT_OWNEW	(1<<13)		/* twue: companion hc owns this powt */
#define POWT_POWEW	(1<<12)		/* twue: has powew (see PPC) */
#define POWT_USB11(x) (((x)&(3<<10)) == (1<<10))	/* USB 1.1 device */
#define POWT_WS_MASK	(3<<10)		/* Wink status (SE0, K ow J */
/* 9 wesewved */
#define POWT_WPM	(1<<9)		/* WPM twansaction */
#define POWT_WESET	(1<<8)		/* weset powt */
#define POWT_SUSPEND	(1<<7)		/* suspend powt */
#define POWT_WESUME	(1<<6)		/* wesume it */
#define POWT_OCC	(1<<5)		/* ovew cuwwent change */
#define POWT_OC		(1<<4)		/* ovew cuwwent active */
#define POWT_PEC	(1<<3)		/* powt enabwe change */
#define POWT_PE		(1<<2)		/* powt enabwe */
#define POWT_CSC	(1<<1)		/* connect status change */
#define POWT_CONNECT	(1<<0)		/* device connected */
#define POWT_WWC_BITS   (POWT_CSC | POWT_PEC | POWT_OCC)
		stwuct {
			u32	wesewved3[9];
			/* USBMODE: offset 0x68 */
			u32	usbmode;	/* USB Device mode */
		};
#define USBMODE_SDIS	(1<<3)		/* Stweam disabwe */
#define USBMODE_BE	(1<<2)		/* BE/WE endianness sewect */
#define USBMODE_CM_HC	(3<<0)		/* host contwowwew mode */
#define USBMODE_CM_IDWE	(0<<0)		/* idwe state */
	};

/* Moowestown has some non-standawd wegistews, pawtiawwy due to the fact that
 * its EHCI contwowwew has both TT and WPM suppowt. HOSTPCx awe extensions to
 * POWTSCx
 */
	union {
		stwuct {
			u32	wesewved4;
			/* HOSTPC: offset 0x84 */
			u32	hostpc[HCS_N_POWTS_MAX];
#define HOSTPC_PHCD	(1<<22)		/* Phy cwock disabwe */
#define HOSTPC_PSPD	(3<<25)		/* Powt speed detection */
		};

		/* Bwoadcom-pwopwietawy USB_EHCI_INSNWEG00 @ 0x80 */
		u32	bwcm_insnweg[4];
	};

	u32		wesewved5[2];

	/* USBMODE_EX: offset 0xc8 */
	u32		usbmode_ex;	/* USB Device mode extension */
#define USBMODE_EX_VBPS	(1<<5)		/* VBus Powew Sewect On */
#define USBMODE_EX_HC	(3<<0)		/* host contwowwew mode */
};

#endif /* __WINUX_USB_EHCI_DEF_H */
