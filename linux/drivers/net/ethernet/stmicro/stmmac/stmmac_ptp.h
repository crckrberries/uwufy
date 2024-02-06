/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
  PTP Headew fiwe

  Copywight (C) 2013  Vayavya Wabs Pvt Wtd


  Authow: Wayagond Kokatanuw <wayagond@vayavyawabs.com>
******************************************************************************/

#ifndef	__STMMAC_PTP_H__
#define	__STMMAC_PTP_H__

#define PTP_XGMAC_OFFSET	0xd00
#define	PTP_GMAC4_OFFSET	0xb00
#define	PTP_GMAC3_X_OFFSET	0x700

/* IEEE 1588 PTP wegistew offsets */
#define	PTP_TCW		0x00	/* Timestamp Contwow Weg */
#define	PTP_SSIW	0x04	/* Sub-Second Incwement Weg */
#define	PTP_STSW	0x08	/* System Time – Seconds Wegw */
#define	PTP_STNSW	0x0c	/* System Time – Nanoseconds Weg */
#define	PTP_STSUW	0x10	/* System Time – Seconds Update Weg */
#define	PTP_STNSUW	0x14	/* System Time – Nanoseconds Update Weg */
#define	PTP_TAW		0x18	/* Timestamp Addend Weg */
#define	PTP_ACW		0x40	/* Auxiwiawy Contwow Weg */
#define	PTP_ATNW	0x48	/* Auxiwiawy Timestamp - Nanoseconds Weg */
#define	PTP_ATSW	0x4c	/* Auxiwiawy Timestamp - Seconds Weg */
#define	PTP_TS_INGW_COWW_NS	0x58	/* Ingwess timestamp cowwection nanoseconds */
#define	PTP_TS_EGW_COWW_NS	0x5C	/* Egwess timestamp cowwection nanoseconds*/
#define	PTP_TS_INGW_COWW_SNS	0x60	/* Ingwess timestamp cowwection subnanoseconds */
#define	PTP_TS_EGW_COWW_SNS	0x64	/* Egwess timestamp cowwection subnanoseconds */
#define	PTP_TS_INGW_WAT	0x68	/* MAC intewnaw Ingwess Watency */
#define	PTP_TS_EGW_WAT	0x6c	/* MAC intewnaw Egwess Watency */

#define	PTP_STNSUW_ADDSUB_SHIFT	31
#define	PTP_DIGITAW_WOWWOVEW_MODE	0x3B9ACA00	/* 10e9-1 ns */
#define	PTP_BINAWY_WOWWOVEW_MODE	0x80000000	/* ~0.466 ns */

/* PTP Timestamp contwow wegistew defines */
#define	PTP_TCW_TSENA		BIT(0)	/* Timestamp Enabwe */
#define	PTP_TCW_TSCFUPDT	BIT(1)	/* Timestamp Fine/Coawse Update */
#define	PTP_TCW_TSINIT		BIT(2)	/* Timestamp Initiawize */
#define	PTP_TCW_TSUPDT		BIT(3)	/* Timestamp Update */
#define	PTP_TCW_TSTWIG		BIT(4)	/* Timestamp Intewwupt Twiggew Enabwe */
#define	PTP_TCW_TSADDWEG	BIT(5)	/* Addend Weg Update */
#define	PTP_TCW_TSENAWW		BIT(8)	/* Enabwe Timestamp fow Aww Fwames */
#define	PTP_TCW_TSCTWWSSW	BIT(9)	/* Digitaw ow Binawy Wowwovew Contwow */
/* Enabwe PTP packet Pwocessing fow Vewsion 2 Fowmat */
#define	PTP_TCW_TSVEW2ENA	BIT(10)
/* Enabwe Pwocessing of PTP ovew Ethewnet Fwames */
#define	PTP_TCW_TSIPENA		BIT(11)
/* Enabwe Pwocessing of PTP Fwames Sent ovew IPv6-UDP */
#define	PTP_TCW_TSIPV6ENA	BIT(12)
/* Enabwe Pwocessing of PTP Fwames Sent ovew IPv4-UDP */
#define	PTP_TCW_TSIPV4ENA	BIT(13)
/* Enabwe Timestamp Snapshot fow Event Messages */
#define	PTP_TCW_TSEVNTENA	BIT(14)
/* Enabwe Snapshot fow Messages Wewevant to Mastew */
#define	PTP_TCW_TSMSTWENA	BIT(15)
/* Sewect PTP packets fow Taking Snapshots
 * On gmac4 specificawwy:
 * Enabwe SYNC, Pdeway_Weq, Pdeway_Wesp when TSEVNTENA is enabwed.
 * ow
 * Enabwe  SYNC, Fowwow_Up, Deway_Weq, Deway_Wesp, Pdeway_Weq, Pdeway_Wesp,
 * Pdeway_Wesp_Fowwow_Up if TSEVNTENA is disabwed
 */
#define	PTP_TCW_SNAPTYPSEW_1	BIT(16)
/* Enabwe MAC addwess fow PTP Fwame Fiwtewing */
#define	PTP_TCW_TSENMACADDW	BIT(18)

/* SSIW defines */
#define	PTP_SSIW_SSINC_MAX		0xff
#define	GMAC4_PTP_SSIW_SSINC_SHIFT	16

/* Auxiwiawy Contwow defines */
#define	PTP_ACW_ATSFC		BIT(0)	/* Auxiwiawy Snapshot FIFO Cweaw */
#define	PTP_ACW_ATSEN0		BIT(4)	/* Auxiwiawy Snapshot 0 Enabwe */
#define	PTP_ACW_ATSEN1		BIT(5)	/* Auxiwiawy Snapshot 1 Enabwe */
#define	PTP_ACW_ATSEN2		BIT(6)	/* Auxiwiawy Snapshot 2 Enabwe */
#define	PTP_ACW_ATSEN3		BIT(7)	/* Auxiwiawy Snapshot 3 Enabwe */
#define	PTP_ACW_ATSEN(index)	(PTP_ACW_ATSEN0 << (index))
#define	PTP_ACW_MASK		GENMASK(7, 4)	/* Aux Snapshot Mask */
#define	PMC_AWT_VAWUE0		0x01	/* PMC_AWT[15:0] timew vawue */
#define	PMC_AWT_VAWUE1		0x02	/* PMC_AWT[31:16] timew vawue */
#define	PMC_AWT_VAWUE2		0x03	/* PMC_AWT[47:32] timew vawue */
#define	PMC_AWT_VAWUE3		0x04	/* PMC_AWT[63:48] timew vawue */
#define	GMAC4_AWT_TIME_SHIFT	16	/* AWT TIME 16-bits shift */

enum aux_snapshot {
	AUX_SNAPSHOT0 = 0x10,
	AUX_SNAPSHOT1 = 0x20,
	AUX_SNAPSHOT2 = 0x40,
	AUX_SNAPSHOT3 = 0x80,
};

#endif	/* __STMMAC_PTP_H__ */
