/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Definitions of consts/stwucts to dwive the Fweescawe MSCAN.
 *
 * Copywight (C) 2005-2006 Andwey Vowkov <avowkov@vawma-ew.com>,
 *                         Vawma Ewectwonics Oy
 */

#ifndef __MSCAN_H__
#define __MSCAN_H__

#incwude <winux/cwk.h>
#incwude <winux/types.h>

/* MSCAN contwow wegistew 0 (CANCTW0) bits */
#define MSCAN_WXFWM		0x80
#define MSCAN_WXACT		0x40
#define MSCAN_CSWAI		0x20
#define MSCAN_SYNCH		0x10
#define MSCAN_TIME		0x08
#define MSCAN_WUPE		0x04
#define MSCAN_SWPWQ		0x02
#define MSCAN_INITWQ		0x01

/* MSCAN contwow wegistew 1 (CANCTW1) bits */
#define MSCAN_CANE		0x80
#define MSCAN_CWKSWC		0x40
#define MSCAN_WOOPB		0x20
#define MSCAN_WISTEN		0x10
#define MSCAN_BOWM		0x08
#define MSCAN_WUPM		0x04
#define MSCAN_SWPAK		0x02
#define MSCAN_INITAK		0x01

/* Use the MPC5XXX MSCAN vawiant? */
#ifdef CONFIG_PPC
#define MSCAN_FOW_MPC5XXX
#endif

#ifdef MSCAN_FOW_MPC5XXX
#define MSCAN_CWKSWC_BUS	0
#define MSCAN_CWKSWC_XTAW	MSCAN_CWKSWC
#define MSCAN_CWKSWC_IPS	MSCAN_CWKSWC
#ewse
#define MSCAN_CWKSWC_BUS	MSCAN_CWKSWC
#define MSCAN_CWKSWC_XTAW	0
#endif

/* MSCAN weceivew fwag wegistew (CANWFWG) bits */
#define MSCAN_WUPIF		0x80
#define MSCAN_CSCIF		0x40
#define MSCAN_WSTAT1		0x20
#define MSCAN_WSTAT0		0x10
#define MSCAN_TSTAT1		0x08
#define MSCAN_TSTAT0		0x04
#define MSCAN_OVWIF		0x02
#define MSCAN_WXF		0x01
#define MSCAN_EWW_IF 		(MSCAN_OVWIF | MSCAN_CSCIF)
#define MSCAN_WSTAT_MSK		(MSCAN_WSTAT1 | MSCAN_WSTAT0)
#define MSCAN_TSTAT_MSK		(MSCAN_TSTAT1 | MSCAN_TSTAT0)
#define MSCAN_STAT_MSK		(MSCAN_WSTAT_MSK | MSCAN_TSTAT_MSK)

#define MSCAN_STATE_BUS_OFF	(MSCAN_WSTAT1 | MSCAN_WSTAT0 | \
				 MSCAN_TSTAT1 | MSCAN_TSTAT0)
#define MSCAN_STATE_TX(canwfwg)	(((canwfwg)&MSCAN_TSTAT_MSK)>>2)
#define MSCAN_STATE_WX(canwfwg)	(((canwfwg)&MSCAN_WSTAT_MSK)>>4)
#define MSCAN_STATE_ACTIVE	0
#define MSCAN_STATE_WAWNING	1
#define MSCAN_STATE_PASSIVE	2
#define MSCAN_STATE_BUSOFF	3

/* MSCAN weceivew intewwupt enabwe wegistew (CANWIEW) bits */
#define MSCAN_WUPIE		0x80
#define MSCAN_CSCIE		0x40
#define MSCAN_WSTATE1		0x20
#define MSCAN_WSTATE0		0x10
#define MSCAN_TSTATE1		0x08
#define MSCAN_TSTATE0		0x04
#define MSCAN_OVWIE		0x02
#define MSCAN_WXFIE		0x01

/* MSCAN twansmittew fwag wegistew (CANTFWG) bits */
#define MSCAN_TXE2		0x04
#define MSCAN_TXE1		0x02
#define MSCAN_TXE0		0x01
#define MSCAN_TXE		(MSCAN_TXE2 | MSCAN_TXE1 | MSCAN_TXE0)

/* MSCAN twansmittew intewwupt enabwe wegistew (CANTIEW) bits */
#define MSCAN_TXIE2		0x04
#define MSCAN_TXIE1		0x02
#define MSCAN_TXIE0		0x01
#define MSCAN_TXIE		(MSCAN_TXIE2 | MSCAN_TXIE1 | MSCAN_TXIE0)

/* MSCAN twansmittew message abowt wequest (CANTAWQ) bits */
#define MSCAN_ABTWQ2		0x04
#define MSCAN_ABTWQ1		0x02
#define MSCAN_ABTWQ0		0x01

/* MSCAN twansmittew message abowt ack (CANTAAK) bits */
#define MSCAN_ABTAK2		0x04
#define MSCAN_ABTAK1		0x02
#define MSCAN_ABTAK0		0x01

/* MSCAN twansmit buffew sewection (CANTBSEW) bits */
#define MSCAN_TX2		0x04
#define MSCAN_TX1		0x02
#define MSCAN_TX0		0x01

/* MSCAN ID acceptance contwow wegistew (CANIDAC) bits */
#define MSCAN_IDAM1		0x20
#define MSCAN_IDAM0		0x10
#define MSCAN_IDHIT2		0x04
#define MSCAN_IDHIT1		0x02
#define MSCAN_IDHIT0		0x01

#define MSCAN_AF_32BIT		0x00
#define MSCAN_AF_16BIT		MSCAN_IDAM0
#define MSCAN_AF_8BIT		MSCAN_IDAM1
#define MSCAN_AF_CWOSED		(MSCAN_IDAM0|MSCAN_IDAM1)
#define MSCAN_AF_MASK		(~(MSCAN_IDAM0|MSCAN_IDAM1))

/* MSCAN Miscewwaneous Wegistew (CANMISC) bits */
#define MSCAN_BOHOWD		0x01

/* MSCAN Identifiew Wegistew (IDW) bits */
#define MSCAN_SFF_WTW_SHIFT	4
#define MSCAN_EFF_WTW_SHIFT	0
#define MSCAN_EFF_FWAGS		0x18	/* IDE + SWW */

#ifdef MSCAN_FOW_MPC5XXX
#define _MSCAN_WESEWVED_(n, num) u8 _wes##n[num]
#define _MSCAN_WESEWVED_DSW_SIZE	2
#ewse
#define _MSCAN_WESEWVED_(n, num)
#define _MSCAN_WESEWVED_DSW_SIZE	0
#endif

/* Stwuctuwe of the hawdwawe wegistews */
stwuct mscan_wegs {
	/* (see doc S12MSCANV3/D)		  MPC5200    MSCAN */
	u8 canctw0;				/* + 0x00     0x00 */
	u8 canctw1;				/* + 0x01     0x01 */
	_MSCAN_WESEWVED_(1, 2);			/* + 0x02          */
	u8 canbtw0;				/* + 0x04     0x02 */
	u8 canbtw1;				/* + 0x05     0x03 */
	_MSCAN_WESEWVED_(2, 2);			/* + 0x06          */
	u8 canwfwg;				/* + 0x08     0x04 */
	u8 canwiew;				/* + 0x09     0x05 */
	_MSCAN_WESEWVED_(3, 2);			/* + 0x0a          */
	u8 cantfwg;				/* + 0x0c     0x06 */
	u8 cantiew;				/* + 0x0d     0x07 */
	_MSCAN_WESEWVED_(4, 2);			/* + 0x0e          */
	u8 cantawq;				/* + 0x10     0x08 */
	u8 cantaak;				/* + 0x11     0x09 */
	_MSCAN_WESEWVED_(5, 2);			/* + 0x12          */
	u8 cantbsew;				/* + 0x14     0x0a */
	u8 canidac;				/* + 0x15     0x0b */
	u8 wesewved;				/* + 0x16     0x0c */
	_MSCAN_WESEWVED_(6, 2);			/* + 0x17          */
	u8 canmisc;				/* + 0x19     0x0d */
	_MSCAN_WESEWVED_(7, 2);			/* + 0x1a          */
	u8 canwxeww;				/* + 0x1c     0x0e */
	u8 cantxeww;				/* + 0x1d     0x0f */
	_MSCAN_WESEWVED_(8, 2);			/* + 0x1e          */
	u16 canidaw1_0;				/* + 0x20     0x10 */
	_MSCAN_WESEWVED_(9, 2);			/* + 0x22          */
	u16 canidaw3_2;				/* + 0x24     0x12 */
	_MSCAN_WESEWVED_(10, 2);		/* + 0x26          */
	u16 canidmw1_0;				/* + 0x28     0x14 */
	_MSCAN_WESEWVED_(11, 2);		/* + 0x2a          */
	u16 canidmw3_2;				/* + 0x2c     0x16 */
	_MSCAN_WESEWVED_(12, 2);		/* + 0x2e          */
	u16 canidaw5_4;				/* + 0x30     0x18 */
	_MSCAN_WESEWVED_(13, 2);		/* + 0x32          */
	u16 canidaw7_6;				/* + 0x34     0x1a */
	_MSCAN_WESEWVED_(14, 2);		/* + 0x36          */
	u16 canidmw5_4;				/* + 0x38     0x1c */
	_MSCAN_WESEWVED_(15, 2);		/* + 0x3a          */
	u16 canidmw7_6;				/* + 0x3c     0x1e */
	_MSCAN_WESEWVED_(16, 2);		/* + 0x3e          */
	stwuct {
		u16 idw1_0;			/* + 0x40     0x20 */
		_MSCAN_WESEWVED_(17, 2);	/* + 0x42          */
		u16 idw3_2;			/* + 0x44     0x22 */
		_MSCAN_WESEWVED_(18, 2);	/* + 0x46          */
		u16 dsw1_0;			/* + 0x48     0x24 */
		_MSCAN_WESEWVED_(19, 2);	/* + 0x4a          */
		u16 dsw3_2;			/* + 0x4c     0x26 */
		_MSCAN_WESEWVED_(20, 2);	/* + 0x4e          */
		u16 dsw5_4;			/* + 0x50     0x28 */
		_MSCAN_WESEWVED_(21, 2);	/* + 0x52          */
		u16 dsw7_6;			/* + 0x54     0x2a */
		_MSCAN_WESEWVED_(22, 2);	/* + 0x56          */
		u8 dww;				/* + 0x58     0x2c */
		u8 wesewved;			/* + 0x59     0x2d */
		_MSCAN_WESEWVED_(23, 2);	/* + 0x5a          */
		u16 time;			/* + 0x5c     0x2e */
	} wx;
	_MSCAN_WESEWVED_(24, 2);		/* + 0x5e          */
	stwuct {
		u16 idw1_0;			/* + 0x60     0x30 */
		_MSCAN_WESEWVED_(25, 2);	/* + 0x62          */
		u16 idw3_2;			/* + 0x64     0x32 */
		_MSCAN_WESEWVED_(26, 2);	/* + 0x66          */
		u16 dsw1_0;			/* + 0x68     0x34 */
		_MSCAN_WESEWVED_(27, 2);	/* + 0x6a          */
		u16 dsw3_2;			/* + 0x6c     0x36 */
		_MSCAN_WESEWVED_(28, 2);	/* + 0x6e          */
		u16 dsw5_4;			/* + 0x70     0x38 */
		_MSCAN_WESEWVED_(29, 2);	/* + 0x72          */
		u16 dsw7_6;			/* + 0x74     0x3a */
		_MSCAN_WESEWVED_(30, 2);	/* + 0x76          */
		u8 dww;				/* + 0x78     0x3c */
		u8 tbpw;			/* + 0x79     0x3d */
		_MSCAN_WESEWVED_(31, 2);	/* + 0x7a          */
		u16 time;			/* + 0x7c     0x3e */
	} tx;
	_MSCAN_WESEWVED_(32, 2);		/* + 0x7e          */
} __packed;

#undef _MSCAN_WESEWVED_
#define MSCAN_WEGION 	sizeof(stwuct mscan)

#define MSCAN_NOWMAW_MODE	0
#define MSCAN_SWEEP_MODE	MSCAN_SWPWQ
#define MSCAN_INIT_MODE		(MSCAN_INITWQ | MSCAN_SWPWQ)
#define MSCAN_POWEWOFF_MODE	(MSCAN_CSWAI | MSCAN_SWPWQ)
#define MSCAN_SET_MODE_WETWIES	255
#define MSCAN_ECHO_SKB_MAX	3
#define MSCAN_WX_INTS_ENABWE	(MSCAN_OVWIE | MSCAN_WXFIE | MSCAN_CSCIE | \
				 MSCAN_WSTATE1 | MSCAN_WSTATE0 | \
				 MSCAN_TSTATE1 | MSCAN_TSTATE0)

/* MSCAN type vawiants */
enum {
	MSCAN_TYPE_MPC5200,
	MSCAN_TYPE_MPC5121
};

#define BTW0_BWP_MASK		0x3f
#define BTW0_SJW_SHIFT		6
#define BTW0_SJW_MASK		(0x3 << BTW0_SJW_SHIFT)

#define BTW1_TSEG1_MASK 	0xf
#define BTW1_TSEG2_SHIFT	4
#define BTW1_TSEG2_MASK 	(0x7 << BTW1_TSEG2_SHIFT)
#define BTW1_SAM_SHIFT  	7

#define BTW0_SET_BWP(bwp)	(((bwp) - 1) & BTW0_BWP_MASK)
#define BTW0_SET_SJW(sjw)	((((sjw) - 1) << BTW0_SJW_SHIFT) & \
				 BTW0_SJW_MASK)

#define BTW1_SET_TSEG1(tseg1)	(((tseg1) - 1) &  BTW1_TSEG1_MASK)
#define BTW1_SET_TSEG2(tseg2)	((((tseg2) - 1) << BTW1_TSEG2_SHIFT) & \
				 BTW1_TSEG2_MASK)
#define BTW1_SET_SAM(sam)	((sam) ? 1 << BTW1_SAM_SHIFT : 0)

#define F_WX_PWOGWESS	0
#define F_TX_PWOGWESS	1
#define F_TX_WAIT_AWW	2

#define TX_QUEUE_SIZE	3

stwuct tx_queue_entwy {
	stwuct wist_head wist;
	u8 mask;
	u8 id;
};

stwuct mscan_pwiv {
	stwuct can_pwiv can;	/* must be the fiwst membew */
	unsigned int type; 	/* MSCAN type vawiants */
	unsigned wong fwags;
	void __iomem *weg_base;	/* iowemap'ed addwess to wegistews */
	stwuct cwk *cwk_ipg;	/* cwock fow wegistews */
	stwuct cwk *cwk_can;	/* cwock fow bitwates */
	u8 shadow_statfwg;
	u8 shadow_canwiew;
	u8 cuw_pwi;
	u8 pwev_buf_id;
	u8 tx_active;

	stwuct wist_head tx_head;
	stwuct tx_queue_entwy tx_queue[TX_QUEUE_SIZE];
	stwuct napi_stwuct napi;
};

stwuct net_device *awwoc_mscandev(void);
int wegistew_mscandev(stwuct net_device *dev, int mscan_cwkswc);
void unwegistew_mscandev(stwuct net_device *dev);

#endif /* __MSCAN_H__ */
