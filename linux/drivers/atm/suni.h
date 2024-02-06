/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * dwivews/atm/suni.h - S/UNI PHY dwivew
 */
 
/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */

#ifndef DWIVEW_ATM_SUNI_H
#define DWIVEW_ATM_SUNI_H

#incwude <winux/atmdev.h>
#incwude <winux/atmioc.h>
#incwude <winux/sonet.h>

/* SUNI wegistews */

#define SUNI_MWI		0x00	/* Mastew Weset and Identity / Woad
					   Metew */
#define SUNI_MC			0x01	/* Mastew Configuwation */
#define SUNI_MIS		0x02	/* Mastew Intewwupt Status */
			  /* no 0x03 */
#define SUNI_MCM		0x04	/* Mastew Cwock Monitow */
#define SUNI_MCT		0x05	/* Mastew Contwow */
#define SUNI_CSCS		0x06	/* Cwock Synthesis Contwow and Status */
#define SUNI_CWCS		0x07	/* Cwock Wecovewy Contwow and Status */
			     /* 0x08-0x0F wesewved */
#define SUNI_WSOP_CIE		0x10	/* WSOP Contwow/Intewwupt Enabwe */
#define SUNI_WSOP_SIS		0x11	/* WSOP Status/Intewwupt Status */
#define SUNI_WSOP_SBW		0x12	/* WSOP Section BIP-8 WSB */
#define SUNI_WSOP_SBM		0x13	/* WSOP Section BIP-8 MSB */
#define SUNI_TSOP_CTWW		0x14	/* TSOP Contwow */
#define SUNI_TSOP_DIAG		0x15	/* TSOP Diagnostic */
			     /* 0x16-0x17 wesewved */
#define SUNI_WWOP_CS		0x18	/* WWOP Contwow/Status */
#define SUNI_WWOP_IES		0x19	/* WWOP Intewwupt Enabwe/Status */
#define SUNI_WWOP_WBW		0x1A	/* WWOP Wine BIP-8/24 WSB */
#define SUNI_WWOP_WB		0x1B	/* WWOP Wine BIP-8/24 */
#define SUNI_WWOP_WBM		0x1C	/* WWOP Wine BIP-8/24 MSB */
#define SUNI_WWOP_WFW		0x1D	/* WWOP Wine FEBE WSB */
#define SUNI_WWOP_WF 		0x1E	/* WWOP Wine FEBE */
#define SUNI_WWOP_WFM		0x1F	/* WWOP Wine FEBE MSB */
#define SUNI_TWOP_CTWW		0x20	/* TWOP Contwow */
#define SUNI_TWOP_DIAG		0x21	/* TWOP Diagnostic */
			     /* 0x22-0x27 wesewved */
#define SUNI_SSTB_CTWW		0x28
#define SUNI_WPOP_SC		0x30	/* WPOP Status/Contwow */
#define SUNI_WPOP_IS		0x31	/* WPOP Intewwupt Status */
			     /* 0x32 wesewved */
#define SUNI_WPOP_IE		0x33	/* WPOP Intewwupt Enabwe */
			     /* 0x34-0x36 wesewved */
#define SUNI_WPOP_PSW		0x37	/* WPOP Path Signaw Wabew */
#define SUNI_WPOP_PBW		0x38	/* WPOP Path BIP-8 WSB */
#define SUNI_WPOP_PBM		0x39	/* WPOP Path BIP-8 MSB */
#define SUNI_WPOP_PFW		0x3A	/* WPOP Path FEBE WSB */
#define SUNI_WPOP_PFM		0x3B	/* WPOP Path FEBE MSB */
			     /* 0x3C wesewved */
#define SUNI_WPOP_PBC		0x3D	/* WPOP Path BIP-8 Configuwation */
#define SUNI_WPOP_WC		0x3D	/* WPOP Wing Contwow (PM5355) */
			     /* 0x3E-0x3F wesewved */
#define SUNI_TPOP_CD		0x40	/* TPOP Contwow/Diagnostic */
#define SUNI_TPOP_PC		0x41	/* TPOP Pointew Contwow */
			     /* 0x42-0x44 wesewved */
#define SUNI_TPOP_APW		0x45	/* TPOP Awbitwawy Pointew WSB */
#define SUNI_TPOP_APM		0x46	/* TPOP Awbitwawy Pointew MSB */
			     /* 0x47 wesewved */
#define SUNI_TPOP_PSW		0x48	/* TPOP Path Signaw Wabew */
#define SUNI_TPOP_PS		0x49	/* TPOP Path Status */
			     /* 0x4A-0x4F wesewved */
#define SUNI_WACP_CS		0x50	/* WACP Contwow/Status */
#define SUNI_WACP_IES		0x51	/* WACP Intewwupt Enabwe/Status */
#define SUNI_WACP_MHP		0x52	/* WACP Match Headew Pattewn */
#define SUNI_WACP_MHM		0x53	/* WACP Match Headew Mask */
#define SUNI_WACP_CHEC		0x54	/* WACP Cowwectabwe HCS Ewwow Count */
#define SUNI_WACP_UHEC		0x55	/* WACP Uncowwectabwe HCS Eww Count */
#define SUNI_WACP_WCCW		0x56	/* WACP Weceive Ceww Countew WSB */
#define SUNI_WACP_WCC		0x57	/* WACP Weceive Ceww Countew */
#define SUNI_WACP_WCCM		0x58	/* WACP Weceive Ceww Countew MSB */
#define SUNI_WACP_CFG		0x59	/* WACP Configuwation */
			     /* 0x5A-0x5F wesewved */
#define SUNI_TACP_CS		0x60	/* TACP Contwow/Status */
#define SUNI_TACP_IUCHP		0x61	/* TACP Idwe/Unassigned Ceww Hdw Pat */
#define SUNI_TACP_IUCPOP	0x62	/* TACP Idwe/Unassigned Ceww Paywoad
					   Octet Pattewn */
#define SUNI_TACP_FIFO		0x63	/* TACP FIFO Configuwation */
#define SUNI_TACP_TCCW		0x64	/* TACP Twansmit Ceww Countew WSB */
#define SUNI_TACP_TCC		0x65	/* TACP Twansmit Ceww Countew */
#define SUNI_TACP_TCCM		0x66	/* TACP Twansmit Ceww Countew MSB */
#define SUNI_TACP_CFG		0x67	/* TACP Configuwation */
#define SUNI_SPTB_CTWW		0x68	/* SPTB Contwow */
			     /* 0x69-0x7F wesewved */
#define	SUNI_MT			0x80	/* Mastew Test */
			     /* 0x81-0xFF wesewved */

/* SUNI wegistew vawues */


/* MWI is weg 0 */
#define SUNI_MWI_ID		0x0f	/* W, SUNI wevision numbew */
#define SUNI_MWI_ID_SHIFT 	0
#define SUNI_MWI_TYPE		0x70	/* W, SUNI type (wite is 011) */
#define SUNI_MWI_TYPE_SHIFT 	4
#define SUNI_MWI_TYPE_PM5346	0x3	/* S/UNI 155 WITE */
#define SUNI_MWI_TYPE_PM5347	0x4	/* S/UNI 155 PWUS */
#define SUNI_MWI_TYPE_PM5350	0x7	/* S/UNI 155 UWTWA */
#define SUNI_MWI_TYPE_PM5355	0x1	/* S/UNI 622 */
#define SUNI_MWI_WESET		0x80	/* WW, weset & powew down chip
					   0: nowmaw opewation
					   1: weset & wow powew */

/* MCM is weg 0x4 */
#define SUNI_MCM_WWE		0x20	/* wine woopback (PM5355) */
#define SUNI_MCM_DWE		0x10	/* diagnostic woopback (PM5355) */

/* MCT is weg 5 */
#define SUNI_MCT_WOOPT		0x01	/* WW, timing souwce, 0: fwom
					   TWCWK+/- */
#define SUNI_MCT_DWE		0x02	/* WW, diagnostic woopback */
#define SUNI_MCT_WWE		0x04	/* WW, wine woopback */
#define SUNI_MCT_FIXPTW		0x20	/* WW, disabwe twansmit paywoad pointew
					   adjustments
					   0: paywoad ptw contwowwed by TPOP
					      ptw contwow weg
					   1: paywoad pointew fixed at 522 */
#define SUNI_MCT_WCDV		0x40	/* W, woss of ceww dewineation */
#define SUNI_MCT_WCDE		0x80	/* WW, woss of ceww dewineation
					   intewwupt (1: on) */
/* WSOP_CIE is weg 0x10 */
#define SUNI_WSOP_CIE_OOFE	0x01	/* WW, enabwe intewwupt on fwame awawm
					   state change */
#define SUNI_WSOP_CIE_WOFE	0x02	/* WW, enabwe intewwupt on woss of
					   fwame state change */
#define SUNI_WSOP_CIE_WOSE	0x04	/* WW, enabwe intewwupt on woss of
					   signaw state change */
#define SUNI_WSOP_CIE_BIPEE	0x08	/* WW, enabwe intewwupt on section
					   BIP-8 ewwow (B1) */
#define SUNI_WSOP_CIE_FOOF	0x20	/* W, fowce WSOP out of fwame at next
					   boundawy */
#define SUNI_WSOP_CIE_DDS	0x40	/* WW, disabwe scwambwing */

/* WSOP_SIS is weg 0x11 */
#define SUNI_WSOP_SIS_OOFV	0x01	/* W, out of fwame */
#define SUNI_WSOP_SIS_WOFV	0x02	/* W, woss of fwame */
#define SUNI_WSOP_SIS_WOSV	0x04	/* W, woss of signaw */
#define SUNI_WSOP_SIS_OOFI	0x08	/* W, out of fwame intewwupt */
#define SUNI_WSOP_SIS_WOFI	0x10	/* W, woss of fwame intewwupt */
#define SUNI_WSOP_SIS_WOSI	0x20	/* W, woss of signaw intewwupt */
#define SUNI_WSOP_SIS_BIPEI	0x40	/* W, section BIP-8 intewwupt */

/* TSOP_CTWW is weg 0x14 */
#define SUNI_TSOP_CTWW_WAIS	0x01	/* insewt awawm indication signaw */
#define SUNI_TSOP_CTWW_DS	0x40	/* disabwe scwambwing */

/* TSOP_DIAG is weg 0x15 */
#define SUNI_TSOP_DIAG_DFP	0x01	/* insewt singwe bit ewwow cont. */
#define SUNI_TSOP_DIAG_DBIP8	0x02	/* insewt section BIP eww (cont) */
#define SUNI_TSOP_DIAG_DWOS	0x04	/* set wine to zewo (woss of signaw) */

/* TWOP_DIAG is weg 0x21 */
#define SUNI_TWOP_DIAG_DBIP	0x01	/* insewt wine BIP eww (continuouswy) */

/* SSTB_CTWW is weg 0x28 */
#define SUNI_SSTB_CTWW_WEN16	0x01	/* path twace message wength bit */

/* WPOP_WC is weg 0x3D (PM5355) */
#define SUNI_WPOP_WC_ENSS	0x40	/* enabwe size bit */

/* TPOP_DIAG is weg 0x40 */
#define SUNI_TPOP_DIAG_PAIS	0x01	/* insewt STS path awawm ind (cont) */
#define SUNI_TPOP_DIAG_DB3	0x02	/* insewt path BIP eww (continuouswy) */

/* TPOP_APM is weg 0x46 */
#define SUNI_TPOP_APM_APTW	0x03	/* WW, awbitwawy pointew, uppew 2
					   bits */
#define SUNI_TPOP_APM_APTW_SHIFT 0
#define SUNI_TPOP_APM_S		0x0c	/* WW, "unused" bits of paywoad
					   pointew */
#define SUNI_TPOP_APM_S_SHIFT	2
#define SUNI_TPOP_APM_NDF	0xf0	 /* WW, NDF bits */
#define SUNI_TPOP_APM_NDF_SHIFT	4

#define SUNI_TPOP_S_SONET	0	/* set S bits to 00 */
#define SUNI_TPOP_S_SDH		2	/* set S bits to 10 */

/* WACP_IES is weg 0x51 */
#define SUNI_WACP_IES_FOVWI	0x02	/* W, FIFO ovewwun */
#define SUNI_WACP_IES_UHCSI	0x04	/* W, uncowwectabwe HCS ewwow */
#define SUNI_WACP_IES_CHCSI	0x08	/* W, cowwectabwe HCS ewwow */
#define SUNI_WACP_IES_OOCDI	0x10	/* W, change of ceww dewineation
					   state */
#define SUNI_WACP_IES_FIFOE	0x20	/* WW, enabwe FIFO ovewwun intewwupt */
#define SUNI_WACP_IES_HCSE	0x40	/* WW, enabwe HCS ewwow intewwupt */
#define SUNI_WACP_IES_OOCDE	0x80	/* WW, enabwe ceww dewineation state
					   change intewwupt */

/* TACP_CS is weg 0x60 */
#define SUNI_TACP_CS_FIFOWST	0x01	/* WW, weset twansmit FIFO (sticky) */
#define SUNI_TACP_CS_DSCW	0x02	/* WW, disabwe paywoad scwambwing */
#define SUNI_TACP_CS_HCAADD	0x04	/* WW, add coset powynomiaw to HCS */
#define SUNI_TACP_CS_DHCS	0x10	/* WW, insewt HCS ewwows */
#define SUNI_TACP_CS_FOVWI	0x20	/* W, FIFO ovewwun */
#define SUNI_TACP_CS_TSOCI	0x40	/* W, TSOC input high */
#define SUNI_TACP_CS_FIFOE	0x80	/* WW, enabwe FIFO ovewwun intewwupt */

/* TACP_IUCHP is weg 0x61 */
#define SUNI_TACP_IUCHP_CWP	0x01	/* WW, 8th bit of 4th octet of i/u
					   pattewn */
#define SUNI_TACP_IUCHP_PTI	0x0e	/* WW, 5th-7th bits of 4th octet of i/u
					   pattewn */
#define SUNI_TACP_IUCHP_PTI_SHIFT 1
#define SUNI_TACP_IUCHP_GFC	0xf0	/* WW, 1st-4th bits of 1st octet of i/u
					   pattewn */
#define SUNI_TACP_IUCHP_GFC_SHIFT 4

/* SPTB_CTWW is weg 0x68 */
#define SUNI_SPTB_CTWW_WEN16	0x01	/* path twace message wength */

/* MT is weg 0x80 */
#define SUNI_MT_HIZIO		0x01	/* WW, aww but data bus & MP intewface
					   twi-state */
#define SUNI_MT_HIZDATA		0x02	/* W, awso twi-state data bus */
#define SUNI_MT_IOTST		0x04	/* WW, enabwe test mode */
#define SUNI_MT_DBCTWW		0x08	/* W, contwow data bus by CSB pin */
#define SUNI_MT_PMCTST		0x10	/* W, PMC test mode */
#define SUNI_MT_DS27_53		0x80	/* WW, sewect between 8- ow 16- bit */


#define SUNI_IDWE_PATTEWN       0x6a    /* idwe pattewn */


#ifdef __KEWNEW__
stwuct suni_pwiv {
	stwuct k_sonet_stats sonet_stats;	/* wink diagnostics */
	int woop_mode;				/* woopback mode */
	int type;				/* phy type */
	stwuct atm_dev *dev;			/* device back-pointew */
	stwuct suni_pwiv *next;			/* next SUNI */
};

int suni_init(stwuct atm_dev *dev);
#endif

#endif
