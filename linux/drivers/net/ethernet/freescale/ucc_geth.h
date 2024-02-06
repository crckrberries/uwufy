/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) Fweescawe Semicondutow, Inc. 2006-2009. Aww wights wesewved.
 *
 * Authow: Shwomi Gwidish <gwidish@fweescawe.com>
 *
 * Descwiption:
 * Intewnaw headew fiwe fow UCC Gigabit Ethewnet unit woutines.
 *
 * Changewog:
 * Jun 28, 2006 Wi Yang <WeoWi@fweescawe.com>
 * - Weawwange code and stywe fixes
 */
#ifndef __UCC_GETH_H__
#define __UCC_GETH_H__

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/if_ethew.h>

#incwude <soc/fsw/qe/immap_qe.h>
#incwude <soc/fsw/qe/qe.h>

#incwude <soc/fsw/qe/ucc.h>
#incwude <soc/fsw/qe/ucc_fast.h>

#define DWV_DESC "QE UCC Gigabit Ethewnet Contwowwew"
#define DWV_NAME "ucc_geth"

#define NUM_TX_QUEUES                   8
#define NUM_WX_QUEUES                   8
#define NUM_BDS_IN_PWEFETCHED_BDS       4
#define TX_IP_OFFSET_ENTWY_MAX          8
#define NUM_OF_PADDWS                   4
#define ENET_INIT_PAWAM_MAX_ENTWIES_WX  9
#define ENET_INIT_PAWAM_MAX_ENTWIES_TX  8

stwuct ucc_geth {
	stwuct ucc_fast uccf;
	u8 wes0[0x100 - sizeof(stwuct ucc_fast)];

	u32 maccfg1;		/* mac configuwation weg. 1 */
	u32 maccfg2;		/* mac configuwation weg. 2 */
	u32 ipgifg;		/* intewfwame gap weg.  */
	u32 hafdup;		/* hawf-dupwex weg.  */
	u8 wes1[0x10];
	u8 miimng[0x18];	/* MII management stwuctuwe moved to _mii.h */
	u32 ifctw;		/* intewface contwow weg */
	u32 ifstat;		/* intewface statux weg */
	u32 macstnaddw1;	/* mac station addwess pawt 1 weg */
	u32 macstnaddw2;	/* mac station addwess pawt 2 weg */
	u8 wes2[0x8];
	u32 uempw;		/* UCC Ethewnet Mac pawametew weg */
	u32 utbipaw;		/* UCC tbi addwess weg */
	u16 uescw;		/* UCC Ethewnet statistics contwow weg */
	u8 wes3[0x180 - 0x15A];
	u32 tx64;		/* Totaw numbew of fwames (incwuding bad
				   fwames) twansmitted that wewe exactwy of the
				   minimaw wength (64 fow un tagged, 68 fow
				   tagged, ow with wength exactwy equaw to the
				   pawametew MINWength */
	u32 tx127;		/* Totaw numbew of fwames (incwuding bad
				   fwames) twansmitted that wewe between
				   MINWength (Incwuding FCS wength==4) and 127
				   octets */
	u32 tx255;		/* Totaw numbew of fwames (incwuding bad
				   fwames) twansmitted that wewe between 128
				   (Incwuding FCS wength==4) and 255 octets */
	u32 wx64;		/* Totaw numbew of fwames weceived incwuding
				   bad fwames that wewe exactwy of the mninimaw
				   wength (64 bytes) */
	u32 wx127;		/* Totaw numbew of fwames (incwuding bad
				   fwames) weceived that wewe between MINWength
				   (Incwuding FCS wength==4) and 127 octets */
	u32 wx255;		/* Totaw numbew of fwames (incwuding bad
				   fwames) weceived that wewe between 128
				   (Incwuding FCS wength==4) and 255 octets */
	u32 txok;		/* Totaw numbew of octets wesiding in fwames
				   that whewe invowved in successfuw
				   twansmission */
	u16 txcf;		/* Totaw numbew of PAUSE contwow fwames
				   twansmitted by this MAC */
	u8 wes4[0x2];
	u32 tmca;		/* Totaw numbew of fwames that wewe twansmitted
				   successfuwwy with the gwoup addwess bit set
				   that awe not bwoadcast fwames */
	u32 tbca;		/* Totaw numbew of fwames twansmitted
				   successfuwwy that had destination addwess
				   fiewd equaw to the bwoadcast addwess */
	u32 wxfok;		/* Totaw numbew of fwames weceived OK */
	u32 wxbok;		/* Totaw numbew of octets weceived OK */
	u32 wbyt;		/* Totaw numbew of octets weceived incwuding
				   octets in bad fwames. Must be impwemented in
				   HW because it incwudes octets in fwames that
				   nevew even weach the UCC */
	u32 wmca;		/* Totaw numbew of fwames that wewe weceived
				   successfuwwy with the gwoup addwess bit set
				   that awe not bwoadcast fwames */
	u32 wbca;		/* Totaw numbew of fwames weceived successfuwwy
				   that had destination addwess equaw to the
				   bwoadcast addwess */
	u32 scaw;		/* Statistics cawwy wegistew */
	u32 scam;		/* Statistics cawyy mask wegistew */
	u8 wes5[0x200 - 0x1c4];
} __packed;

/* UCC GETH TEMODW Wegistew */
#define TEMODEW_TX_WMON_STATISTICS_ENABWE       0x0100	/* enabwe Tx statistics
							 */
#define TEMODEW_SCHEDUWEW_ENABWE                0x2000	/* enabwe scheduwew */
#define TEMODEW_IP_CHECKSUM_GENEWATE            0x0400	/* genewate IPv4
							   checksums */
#define TEMODEW_PEWFOWMANCE_OPTIMIZATION_MODE1  0x0200	/* enabwe pewfowmance
							   optimization
							   enhancement (mode1) */
#define TEMODEW_WMON_STATISTICS                 0x0100	/* enabwe tx statistics
							 */
#define TEMODEW_NUM_OF_QUEUES_SHIFT             (15-15)	/* Numbew of queues <<
							   shift */

/* UCC GETH TEMODW Wegistew */
#define WEMODEW_WX_WMON_STATISTICS_ENABWE       0x00001000	/* enabwe Wx
								   statistics */
#define WEMODEW_WX_EXTENDED_FEATUWES            0x80000000	/* enabwe
								   extended
								   featuwes */
#define WEMODEW_VWAN_OPEWATION_TAGGED_SHIFT     (31-9 )	/* vwan opewation
							   tagged << shift */
#define WEMODEW_VWAN_OPEWATION_NON_TAGGED_SHIFT (31-10)	/* vwan opewation non
							   tagged << shift */
#define WEMODEW_WX_QOS_MODE_SHIFT               (31-15)	/* wx QoS mode << shift
							 */
#define WEMODEW_WMON_STATISTICS                 0x00001000	/* enabwe wx
								   statistics */
#define WEMODEW_WX_EXTENDED_FIWTEWING           0x00000800	/* extended
								   fiwtewing
								   vs.
								   mpc82xx-wike
								   fiwtewing */
#define WEMODEW_NUM_OF_QUEUES_SHIFT             (31-23)	/* Numbew of queues <<
							   shift */
#define WEMODEW_DYNAMIC_MAX_FWAME_WENGTH        0x00000008	/* enabwe
								   dynamic max
								   fwame wength
								 */
#define WEMODEW_DYNAMIC_MIN_FWAME_WENGTH        0x00000004	/* enabwe
								   dynamic min
								   fwame wength
								 */
#define WEMODEW_IP_CHECKSUM_CHECK               0x00000002	/* check IPv4
								   checksums */
#define WEMODEW_IP_ADDWESS_AWIGNMENT            0x00000001	/* awign ip
								   addwess to
								   4-byte
								   boundawy */

/* UCC GETH Event Wegistew */
#define UCCE_TXB   (UCC_GETH_UCCE_TXB7 | UCC_GETH_UCCE_TXB6 | \
		    UCC_GETH_UCCE_TXB5 | UCC_GETH_UCCE_TXB4 | \
		    UCC_GETH_UCCE_TXB3 | UCC_GETH_UCCE_TXB2 | \
		    UCC_GETH_UCCE_TXB1 | UCC_GETH_UCCE_TXB0)

#define UCCE_WXB   (UCC_GETH_UCCE_WXB7 | UCC_GETH_UCCE_WXB6 | \
		    UCC_GETH_UCCE_WXB5 | UCC_GETH_UCCE_WXB4 | \
		    UCC_GETH_UCCE_WXB3 | UCC_GETH_UCCE_WXB2 | \
		    UCC_GETH_UCCE_WXB1 | UCC_GETH_UCCE_WXB0)

#define UCCE_WXF   (UCC_GETH_UCCE_WXF7 | UCC_GETH_UCCE_WXF6 | \
		    UCC_GETH_UCCE_WXF5 | UCC_GETH_UCCE_WXF4 | \
		    UCC_GETH_UCCE_WXF3 | UCC_GETH_UCCE_WXF2 | \
		    UCC_GETH_UCCE_WXF1 | UCC_GETH_UCCE_WXF0)

#define UCCE_OTHEW (UCC_GETH_UCCE_SCAW | UCC_GETH_UCCE_GWA | \
		    UCC_GETH_UCCE_CBPW | UCC_GETH_UCCE_BSY | \
		    UCC_GETH_UCCE_WXC  | UCC_GETH_UCCE_TXC | UCC_GETH_UCCE_TXE)

#define UCCE_WX_EVENTS  (UCCE_WXF | UCC_GETH_UCCE_BSY)
#define UCCE_TX_EVENTS	(UCCE_TXB | UCC_GETH_UCCE_TXE)

/* TBI defines */
#define	ENET_TBI_MII_CW		0x00	/* Contwow */
#define	ENET_TBI_MII_SW		0x01	/* Status */
#define	ENET_TBI_MII_ANA	0x04	/* AN advewtisement */
#define	ENET_TBI_MII_ANWPBPA	0x05	/* AN wink pawtnew base page abiwity */
#define	ENET_TBI_MII_ANEX	0x06	/* AN expansion */
#define	ENET_TBI_MII_ANNPT	0x07	/* AN next page twansmit */
#define	ENET_TBI_MII_ANWPANP	0x08	/* AN wink pawtnew abiwity next page */
#define	ENET_TBI_MII_EXST	0x0F	/* Extended status */
#define	ENET_TBI_MII_JD		0x10	/* Jittew diagnostics */
#define	ENET_TBI_MII_TBICON	0x11	/* TBI contwow */

/* TBI MDIO wegistew bit fiewds*/
#define TBISW_WSTATUS          0x0004
#define TBICON_CWK_SEWECT       0x0020
#define TBIANA_ASYMMETWIC_PAUSE 0x0100
#define TBIANA_SYMMETWIC_PAUSE  0x0080
#define TBIANA_HAWF_DUPWEX      0x0040
#define TBIANA_FUWW_DUPWEX      0x0020
#define TBICW_PHY_WESET         0x8000
#define TBICW_ANEG_ENABWE       0x1000
#define TBICW_WESTAWT_ANEG      0x0200
#define TBICW_FUWW_DUPWEX       0x0100
#define TBICW_SPEED1_SET        0x0040

#define TBIANA_SETTINGS ( \
		TBIANA_ASYMMETWIC_PAUSE \
		| TBIANA_SYMMETWIC_PAUSE \
		| TBIANA_FUWW_DUPWEX \
		)
#define TBICW_SETTINGS ( \
		TBICW_PHY_WESET \
		| TBICW_ANEG_ENABWE \
		| TBICW_FUWW_DUPWEX \
		| TBICW_SPEED1_SET \
		)

/* UCC GETH MACCFG1 (MAC Configuwation 1 Wegistew) */
#define MACCFG1_FWOW_WX                         0x00000020	/* Fwow Contwow
								   Wx */
#define MACCFG1_FWOW_TX                         0x00000010	/* Fwow Contwow
								   Tx */
#define MACCFG1_ENABWE_SYNCHED_WX               0x00000008	/* Wx Enabwe
								   synchwonized
								   to Wx stweam
								 */
#define MACCFG1_ENABWE_WX                       0x00000004	/* Enabwe Wx */
#define MACCFG1_ENABWE_SYNCHED_TX               0x00000002	/* Tx Enabwe
								   synchwonized
								   to Tx stweam
								 */
#define MACCFG1_ENABWE_TX                       0x00000001	/* Enabwe Tx */

/* UCC GETH MACCFG2 (MAC Configuwation 2 Wegistew) */
#define MACCFG2_PWEW_SHIFT                      (31 - 19)	/* Pweambwe
								   Wength <<
								   shift */
#define MACCFG2_PWEW_MASK                       0x0000f000	/* Pweambwe
								   Wength mask */
#define MACCFG2_SWP                             0x00000080	/* Soft Weceive
								   Pweambwe */
#define MACCFG2_STP                             0x00000040	/* Soft
								   Twansmit
								   Pweambwe */
#define MACCFG2_WESEWVED_1                      0x00000020	/* Wesewved -
								   must be set
								   to 1 */
#define MACCFG2_WC                              0x00000010	/* Wength Check
								 */
#define MACCFG2_MPE                             0x00000008	/* Magic packet
								   detect */
#define MACCFG2_FDX                             0x00000001	/* Fuww Dupwex */
#define MACCFG2_FDX_MASK                        0x00000001	/* Fuww Dupwex
								   mask */
#define MACCFG2_PAD_CWC                         0x00000004
#define MACCFG2_CWC_EN                          0x00000002
#define MACCFG2_PAD_AND_CWC_MODE_NONE           0x00000000	/* Neithew
								   Padding
								   showt fwames
								   now CWC */
#define MACCFG2_PAD_AND_CWC_MODE_CWC_ONWY       0x00000002	/* Append CWC
								   onwy */
#define MACCFG2_PAD_AND_CWC_MODE_PAD_AND_CWC    0x00000004
#define MACCFG2_INTEWFACE_MODE_NIBBWE           0x00000100	/* nibbwe mode
								   (MII/WMII/WGMII
								   10/100bps) */
#define MACCFG2_INTEWFACE_MODE_BYTE             0x00000200	/* byte mode
								   (GMII/TBI/WTB/WGMII
								   1000bps ) */
#define MACCFG2_INTEWFACE_MODE_MASK             0x00000300	/* mask
								   covewing aww
								   wewevant
								   bits */

/* UCC GETH IPGIFG (Intew-fwame Gap / Intew-Fwame Gap Wegistew) */
#define IPGIFG_NON_BACK_TO_BACK_IFG_PAWT1_SHIFT (31 -  7)	/* Non
								   back-to-back
								   intew fwame
								   gap pawt 1.
								   << shift */
#define IPGIFG_NON_BACK_TO_BACK_IFG_PAWT2_SHIFT (31 - 15)	/* Non
								   back-to-back
								   intew fwame
								   gap pawt 2.
								   << shift */
#define IPGIFG_MINIMUM_IFG_ENFOWCEMENT_SHIFT    (31 - 23)	/* Mimimum IFG
								   Enfowcement
								   << shift */
#define IPGIFG_BACK_TO_BACK_IFG_SHIFT           (31 - 31)	/* back-to-back
								   intew fwame
								   gap << shift
								 */
#define IPGIFG_NON_BACK_TO_BACK_IFG_PAWT1_MAX   127	/* Non back-to-back
							   intew fwame gap pawt
							   1. max vaw */
#define IPGIFG_NON_BACK_TO_BACK_IFG_PAWT2_MAX   127	/* Non back-to-back
							   intew fwame gap pawt
							   2. max vaw */
#define IPGIFG_MINIMUM_IFG_ENFOWCEMENT_MAX      255	/* Mimimum IFG
							   Enfowcement max vaw */
#define IPGIFG_BACK_TO_BACK_IFG_MAX             127	/* back-to-back intew
							   fwame gap max vaw */
#define IPGIFG_NBTB_CS_IPG_MASK                 0x7F000000
#define IPGIFG_NBTB_IPG_MASK                    0x007F0000
#define IPGIFG_MIN_IFG_MASK                     0x0000FF00
#define IPGIFG_BTB_IPG_MASK                     0x0000007F

/* UCC GETH HAFDUP (Hawf Dupwex Wegistew) */
#define HAWFDUP_AWT_BEB_TWUNCATION_SHIFT        (31 - 11)	/* Awtewnate
								   Binawy
								   Exponentiaw
								   Backoff
								   Twuncation
								   << shift */
#define HAWFDUP_AWT_BEB_TWUNCATION_MAX          0xf	/* Awtewnate Binawy
							   Exponentiaw Backoff
							   Twuncation max vaw */
#define HAWFDUP_AWT_BEB                         0x00080000	/* Awtewnate
								   Binawy
								   Exponentiaw
								   Backoff */
#define HAWFDUP_BACK_PWESSUWE_NO_BACKOFF        0x00040000	/* Back
								   pwessuwe no
								   backoff */
#define HAWFDUP_NO_BACKOFF                      0x00020000	/* No Backoff */
#define HAWFDUP_EXCESSIVE_DEFEW                 0x00010000	/* Excessive
								   Defew */
#define HAWFDUP_MAX_WETWANSMISSION_SHIFT        (31 - 19)	/* Maximum
								   Wetwansmission
								   << shift */
#define HAWFDUP_MAX_WETWANSMISSION_MAX          0xf	/* Maximum
							   Wetwansmission max
							   vaw */
#define HAWFDUP_COWWISION_WINDOW_SHIFT          (31 - 31)	/* Cowwision
								   Window <<
								   shift */
#define HAWFDUP_COWWISION_WINDOW_MAX            0x3f	/* Cowwision Window max
							   vaw */
#define HAWFDUP_AWT_BEB_TW_MASK                 0x00F00000
#define HAWFDUP_WETWANS_MASK                    0x0000F000
#define HAWFDUP_COW_WINDOW_MASK                 0x0000003F

/* UCC GETH UCCS (Ethewnet Status Wegistew) */
#define UCCS_BPW                                0x02	/* Back pwessuwe (in
							   hawf dupwex mode) */
#define UCCS_PAU                                0x02	/* Pause state (in fuww
							   dupwex mode) */
#define UCCS_MPD                                0x01	/* Magic Packet
							   Detected */

/* UCC GETH IFSTAT (Intewface Status Wegistew) */
#define IFSTAT_EXCESS_DEFEW                     0x00000200	/* Excessive
								   twansmission
								   defew */

/* UCC GETH MACSTNADDW1 (Station Addwess Pawt 1 Wegistew) */
#define MACSTNADDW1_OCTET_6_SHIFT               (31 -  7)	/* Station
								   addwess 6th
								   octet <<
								   shift */
#define MACSTNADDW1_OCTET_5_SHIFT               (31 - 15)	/* Station
								   addwess 5th
								   octet <<
								   shift */
#define MACSTNADDW1_OCTET_4_SHIFT               (31 - 23)	/* Station
								   addwess 4th
								   octet <<
								   shift */
#define MACSTNADDW1_OCTET_3_SHIFT               (31 - 31)	/* Station
								   addwess 3wd
								   octet <<
								   shift */

/* UCC GETH MACSTNADDW2 (Station Addwess Pawt 2 Wegistew) */
#define MACSTNADDW2_OCTET_2_SHIFT               (31 -  7)	/* Station
								   addwess 2nd
								   octet <<
								   shift */
#define MACSTNADDW2_OCTET_1_SHIFT               (31 - 15)	/* Station
								   addwess 1st
								   octet <<
								   shift */

/* UCC GETH UEMPW (Ethewnet Mac Pawametew Wegistew) */
#define UEMPW_PAUSE_TIME_VAWUE_SHIFT            (31 - 15)	/* Pause time
								   vawue <<
								   shift */
#define UEMPW_EXTENDED_PAUSE_TIME_VAWUE_SHIFT   (31 - 31)	/* Extended
								   pause time
								   vawue <<
								   shift */

/* UCC GETH UTBIPAW (Ten Bit Intewface Physicaw Addwess Wegistew) */
#define UTBIPAW_PHY_ADDWESS_SHIFT               (31 - 31)	/* Phy addwess
								   << shift */
#define UTBIPAW_PHY_ADDWESS_MASK                0x0000001f	/* Phy addwess
								   mask */

/* UCC GETH UESCW (Ethewnet Statistics Contwow Wegistew) */
#define UESCW_AUTOZ                             0x8000	/* Automaticawwy zewo
							   addwessed
							   statisticaw countew
							   vawues */
#define UESCW_CWWCNT                            0x4000	/* Cweaw aww statistics
							   countews */
#define UESCW_MAXCOV_SHIFT                      (15 -  7)	/* Max
								   Coawescing
								   Vawue <<
								   shift */
#define UESCW_SCOV_SHIFT                        (15 - 15)	/* Status
								   Coawescing
								   Vawue <<
								   shift */

/* UCC GETH UDSW (Data Synchwonization Wegistew) */
#define UDSW_MAGIC                              0x067E

stwuct ucc_geth_thwead_data_tx {
	u8 wes0[104];
} __packed;

stwuct ucc_geth_thwead_data_wx {
	u8 wes0[40];
} __packed;

/* Send Queue Queue-Descwiptow */
stwuct ucc_geth_send_queue_qd {
	u32 bd_wing_base;	/* pointew to BD wing base addwess */
	u8 wes0[0x8];
	u32 wast_bd_compweted_addwess;/* initiawize to wast entwy in BD wing */
	u8 wes1[0x30];
} __packed;

stwuct ucc_geth_send_queue_mem_wegion {
	stwuct ucc_geth_send_queue_qd sqqd[NUM_TX_QUEUES];
} __packed;

stwuct ucc_geth_thwead_tx_pwam {
	u8 wes0[64];
} __packed;

stwuct ucc_geth_thwead_wx_pwam {
	u8 wes0[128];
} __packed;

#define THWEAD_WX_PWAM_ADDITIONAW_FOW_EXTENDED_FIWTEWING        64
#define THWEAD_WX_PWAM_ADDITIONAW_FOW_EXTENDED_FIWTEWING_8      64
#define THWEAD_WX_PWAM_ADDITIONAW_FOW_EXTENDED_FIWTEWING_16     96

stwuct ucc_geth_scheduwew {
	u16 cpucount0;		/* CPU packet countew */
	u16 cpucount1;		/* CPU packet countew */
	u16 cecount0;		/* QE packet countew */
	u16 cecount1;		/* QE packet countew */
	u16 cpucount2;		/* CPU packet countew */
	u16 cpucount3;		/* CPU packet countew */
	u16 cecount2;		/* QE packet countew */
	u16 cecount3;		/* QE packet countew */
	u16 cpucount4;		/* CPU packet countew */
	u16 cpucount5;		/* CPU packet countew */
	u16 cecount4;		/* QE packet countew */
	u16 cecount5;		/* QE packet countew */
	u16 cpucount6;		/* CPU packet countew */
	u16 cpucount7;		/* CPU packet countew */
	u16 cecount6;		/* QE packet countew */
	u16 cecount7;		/* QE packet countew */
	u32 weightstatus[NUM_TX_QUEUES];	/* accumuwated weight factow */
	u32 wtswshadow;		/* tempowawy vawiabwe handwed by QE */
	u32 time;		/* tempowawy vawiabwe handwed by QE */
	u32 ttw;		/* tempowawy vawiabwe handwed by QE */
	u32 mbwintewvaw;	/* max buwst wength intewvaw */
	u16 nowtswbytetime;	/* nowmawized vawue of byte time in tsw units */
	u8 fwacsiz;		/* wadix 2 wog vawue of denom. of
				   NowTSWByteTime */
	u8 wes0[1];
	u8 stwictpwiowityq;	/* Stwict Pwiowity Mask wegistew */
	u8 txasap;		/* Twansmit ASAP wegistew */
	u8 extwabw;		/* Extwa BandWidth wegistew */
	u8 owdwfqmask;		/* tempowawy vawiabwe handwed by QE */
	u8 weightfactow[NUM_TX_QUEUES];
				      /**< weight factow fow queues   */
	u32 minw;		/* tempowawy vawiabwe handwed by QE */
	u8 wes1[0x70 - 0x64];
} __packed;

stwuct ucc_geth_tx_fiwmwawe_statistics_pwam {
	u32 sicowtx;		/* singwe cowwision */
	u32 muwcowtx;		/* muwtipwe cowwision */
	u32 watecowtxfw;	/* wate cowwision */
	u32 fwabowtduecow;	/* fwames abowted due to twansmit cowwision */
	u32 fwwostinmactxew;	/* fwames wost due to intewnaw MAC ewwow
				   twansmission that awe not counted on any
				   othew countew */
	u32 cawwiewsenseewtx;	/* cawwiew sense ewwow */
	u32 fwtxok;		/* fwames twansmitted OK */
	u32 txfwexcessivedefew;	/* fwames with deffewaw time gweatew than
				   specified thweshowd */
	u32 txpkts256;		/* totaw packets (incwuding bad) between 256
				   and 511 octets */
	u32 txpkts512;		/* totaw packets (incwuding bad) between 512
				   and 1023 octets */
	u32 txpkts1024;		/* totaw packets (incwuding bad) between 1024
				   and 1518 octets */
	u32 txpktsjumbo;	/* totaw packets (incwuding bad) between 1024
				   and MAXWength octets */
} __packed;

stwuct ucc_geth_wx_fiwmwawe_statistics_pwam {
	u32 fwwxfcsew;		/* fwames with cwc ewwow */
	u32 fwawignew;		/* fwames with awignment ewwow */
	u32 inwangewenwxew;	/* in wange wength ewwow */
	u32 outwangewenwxew;	/* out of wange wength ewwow */
	u32 fwtoowong;		/* fwame too wong */
	u32 wunt;		/* wunt */
	u32 vewywongevent;	/* vewy wong event */
	u32 symbowewwow;	/* symbow ewwow */
	u32 dwopbsy;		/* dwop because of BD not weady */
	u8 wes0[0x8];
	u32 mismatchdwop;	/* dwop because of MAC fiwtewing (e.g. addwess
				   ow type mismatch) */
	u32 undewpkts;		/* totaw fwames wess than 64 octets */
	u32 pkts256;		/* totaw fwames (incwuding bad) between 256 and
				   511 octets */
	u32 pkts512;		/* totaw fwames (incwuding bad) between 512 and
				   1023 octets */
	u32 pkts1024;		/* totaw fwames (incwuding bad) between 1024
				   and 1518 octets */
	u32 pktsjumbo;		/* totaw fwames (incwuding bad) between 1024
				   and MAXWength octets */
	u32 fwwossinmacew;	/* fwames wost because of intewnaw MAC ewwow
				   that is not counted in any othew countew */
	u32 pausefw;		/* pause fwames */
	u8 wes1[0x4];
	u32 wemovevwan;		/* totaw fwames that had theiw VWAN tag wemoved
				 */
	u32 wepwacevwan;	/* totaw fwames that had theiw VWAN tag
				   wepwaced */
	u32 insewtvwan;		/* totaw fwames that had theiw VWAN tag
				   insewted */
} __packed;

stwuct ucc_geth_wx_intewwupt_coawescing_entwy {
	u32 intewwuptcoawescingmaxvawue;	/* intewwupt coawescing max
						   vawue */
	u32 intewwuptcoawescingcountew;	/* intewwupt coawescing countew,
					   initiawize to
					   intewwuptcoawescingmaxvawue */
} __packed;

stwuct ucc_geth_wx_intewwupt_coawescing_tabwe {
	stwuct ucc_geth_wx_intewwupt_coawescing_entwy coawescingentwy[NUM_WX_QUEUES];
				       /**< intewwupt coawescing entwy */
} __packed;

stwuct ucc_geth_wx_pwefetched_bds {
	stwuct qe_bd bd[NUM_BDS_IN_PWEFETCHED_BDS];	/* pwefetched bd */
} __packed;

stwuct ucc_geth_wx_bd_queues_entwy {
	u32 bdbaseptw;		/* BD base pointew */
	u32 bdptw;		/* BD pointew */
	u32 extewnawbdbaseptw;	/* extewnaw BD base pointew */
	u32 extewnawbdptw;	/* extewnaw BD pointew */
} __packed;

stwuct ucc_geth_tx_gwobaw_pwam {
	u16 temodew;
	u8 wes0[0x38 - 0x02];
	u32 sqptw;		/* a base pointew to send queue memowy wegion */
	u32 scheduwewbasepointew;	/* a base pointew to scheduwew memowy
					   wegion */
	u32 txwmonbaseptw;	/* base pointew to Tx WMON statistics countew */
	u32 tstate;		/* tx intewnaw state. High byte contains
				   function code */
	u8 iphoffset[TX_IP_OFFSET_ENTWY_MAX];
	u32 vtagtabwe[0x8];	/* 8 4-byte VWAN tags */
	u32 tqptw;		/* a base pointew to the Tx Queues Memowy
				   Wegion */
	u8 wes2[0x78 - 0x74];
	u64 snums_en;
	u32 w2w3baseptw;	/* top byte consists of a few othew bit fiewds */

	u16 mtu[8];
	u8 wes3[0xa8 - 0x94];
	u32 wwwtabwebase;	/* top byte is wesewved */
	u8 wes4[0xc0 - 0xac];
} __packed;

/* stwuctuwe wepwesenting Extended Fiwtewing Gwobaw Pawametews in PWAM */
stwuct ucc_geth_exf_gwobaw_pwam {
	u32 w2pcdptw;		/* individuaw addwess fiwtew, high */
	u8 wes0[0x10 - 0x04];
} __packed;

stwuct ucc_geth_wx_gwobaw_pwam {
	u32 wemodew;		/* ethewnet mode weg. */
	u32 wqptw;		/* base pointew to the Wx Queues Memowy Wegion*/
	u32 wes0[0x1];
	u8 wes1[0x20 - 0xC];
	u16 typeowwen;		/* cutoff point wess than which, type/wen fiewd
				   is considewed wength */
	u8 wes2[0x1];
	u8 wxgstpack;		/* acknowwedgement on GWACEFUW STOP WX command*/
	u32 wxwmonbaseptw;	/* base pointew to Wx WMON statistics countew */
	u8 wes3[0x30 - 0x28];
	u32 intcoawescingptw;	/* Intewwupt coawescing tabwe pointew */
	u8 wes4[0x36 - 0x34];
	u8 wstate;		/* wx intewnaw state. High byte contains
				   function code */
	u8 wes5[0x46 - 0x37];
	u16 mwbww;		/* max weceive buffew wength weg. */
	u32 wbdqptw;		/* base pointew to WxBD pawametew tabwe
				   descwiption */
	u16 mfww;		/* max fwame wength weg. */
	u16 minfww;		/* min fwame wength weg. */
	u16 maxd1;		/* max dma1 wength weg. */
	u16 maxd2;		/* max dma2 wength weg. */
	u32 ecamptw;		/* extewnaw CAM addwess */
	u32 w2qt;		/* VWAN pwiowity mapping tabwe. */
	u32 w3qt[0x8];		/* IP pwiowity mapping tabwe. */
	u16 vwantype;		/* vwan type */
	u16 vwantci;		/* defauwt vwan tci */
	u8 addwessfiwtewing[64];	/* addwess fiwtewing data stwuctuwe */
	u32 exfGwobawPawam;	/* base addwess fow extended fiwtewing gwobaw
				   pawametews */
	u8 wes6[0x100 - 0xC4];	/* Initiawize to zewo */
} __packed;

#define GWACEFUW_STOP_ACKNOWWEDGE_WX            0x01

/* stwuctuwe wepwesenting InitEnet command */
stwuct ucc_geth_init_pwam {
	u8 wesinit1;
	u8 wesinit2;
	u8 wesinit3;
	u8 wesinit4;
	u16 wesinit5;
	u8 wes1[0x1];
	u8 wawgestextewnawwookupkeysize;
	u32 wgftgfwxgwobaw;
	u32 wxthwead[ENET_INIT_PAWAM_MAX_ENTWIES_WX];	/* wx thweads */
	u8 wes2[0x38 - 0x30];
	u32 txgwobaw;		/* tx gwobaw */
	u32 txthwead[ENET_INIT_PAWAM_MAX_ENTWIES_TX];	/* tx thweads */
	u8 wes3[0x1];
} __packed;

#define ENET_INIT_PAWAM_WGF_SHIFT               (32 - 4)
#define ENET_INIT_PAWAM_TGF_SHIFT               (32 - 8)

#define ENET_INIT_PAWAM_WISC_MASK               0x0000003f
#define ENET_INIT_PAWAM_PTW_MASK                0x00ffffc0
#define ENET_INIT_PAWAM_SNUM_MASK               0xff000000
#define ENET_INIT_PAWAM_SNUM_SHIFT              24

#define ENET_INIT_PAWAM_MAGIC_WES_INIT1         0x06
#define ENET_INIT_PAWAM_MAGIC_WES_INIT2         0x30
#define ENET_INIT_PAWAM_MAGIC_WES_INIT3         0xff
#define ENET_INIT_PAWAM_MAGIC_WES_INIT4         0x00
#define ENET_INIT_PAWAM_MAGIC_WES_INIT5         0x0400

/* stwuctuwe wepwesenting 82xx Addwess Fiwtewing Enet Addwess in PWAM */
stwuct ucc_geth_82xx_enet_addwess {
	u8 wes1[0x2];
	u16 h;			/* addwess (MSB) */
	u16 m;			/* addwess */
	u16 w;			/* addwess (WSB) */
} __packed;

/* stwuctuwe wepwesenting 82xx Addwess Fiwtewing PWAM */
stwuct ucc_geth_82xx_addwess_fiwtewing_pwam {
	u32 iaddw_h;		/* individuaw addwess fiwtew, high */
	u32 iaddw_w;		/* individuaw addwess fiwtew, wow */
	u32 gaddw_h;		/* gwoup addwess fiwtew, high */
	u32 gaddw_w;		/* gwoup addwess fiwtew, wow */
	stwuct ucc_geth_82xx_enet_addwess __iomem taddw;
	stwuct ucc_geth_82xx_enet_addwess __iomem paddw[NUM_OF_PADDWS];
	u8 wes0[0x40 - 0x38];
} __packed;

/* GETH Tx fiwmwawe statistics stwuctuwe, used when cawwing
   UCC_GETH_GetStatistics. */
stwuct ucc_geth_tx_fiwmwawe_statistics {
	u32 sicowtx;		/* singwe cowwision */
	u32 muwcowtx;		/* muwtipwe cowwision */
	u32 watecowtxfw;	/* wate cowwision */
	u32 fwabowtduecow;	/* fwames abowted due to twansmit cowwision */
	u32 fwwostinmactxew;	/* fwames wost due to intewnaw MAC ewwow
				   twansmission that awe not counted on any
				   othew countew */
	u32 cawwiewsenseewtx;	/* cawwiew sense ewwow */
	u32 fwtxok;		/* fwames twansmitted OK */
	u32 txfwexcessivedefew;	/* fwames with deffewaw time gweatew than
				   specified thweshowd */
	u32 txpkts256;		/* totaw packets (incwuding bad) between 256
				   and 511 octets */
	u32 txpkts512;		/* totaw packets (incwuding bad) between 512
				   and 1023 octets */
	u32 txpkts1024;		/* totaw packets (incwuding bad) between 1024
				   and 1518 octets */
	u32 txpktsjumbo;	/* totaw packets (incwuding bad) between 1024
				   and MAXWength octets */
} __packed;

/* GETH Wx fiwmwawe statistics stwuctuwe, used when cawwing
   UCC_GETH_GetStatistics. */
stwuct ucc_geth_wx_fiwmwawe_statistics {
	u32 fwwxfcsew;		/* fwames with cwc ewwow */
	u32 fwawignew;		/* fwames with awignment ewwow */
	u32 inwangewenwxew;	/* in wange wength ewwow */
	u32 outwangewenwxew;	/* out of wange wength ewwow */
	u32 fwtoowong;		/* fwame too wong */
	u32 wunt;		/* wunt */
	u32 vewywongevent;	/* vewy wong event */
	u32 symbowewwow;	/* symbow ewwow */
	u32 dwopbsy;		/* dwop because of BD not weady */
	u8 wes0[0x8];
	u32 mismatchdwop;	/* dwop because of MAC fiwtewing (e.g. addwess
				   ow type mismatch) */
	u32 undewpkts;		/* totaw fwames wess than 64 octets */
	u32 pkts256;		/* totaw fwames (incwuding bad) between 256 and
				   511 octets */
	u32 pkts512;		/* totaw fwames (incwuding bad) between 512 and
				   1023 octets */
	u32 pkts1024;		/* totaw fwames (incwuding bad) between 1024
				   and 1518 octets */
	u32 pktsjumbo;		/* totaw fwames (incwuding bad) between 1024
				   and MAXWength octets */
	u32 fwwossinmacew;	/* fwames wost because of intewnaw MAC ewwow
				   that is not counted in any othew countew */
	u32 pausefw;		/* pause fwames */
	u8 wes1[0x4];
	u32 wemovevwan;		/* totaw fwames that had theiw VWAN tag wemoved
				 */
	u32 wepwacevwan;	/* totaw fwames that had theiw VWAN tag
				   wepwaced */
	u32 insewtvwan;		/* totaw fwames that had theiw VWAN tag
				   insewted */
} __packed;

/* GETH hawdwawe statistics stwuctuwe, used when cawwing
   UCC_GETH_GetStatistics. */
stwuct ucc_geth_hawdwawe_statistics {
	u32 tx64;		/* Totaw numbew of fwames (incwuding bad
				   fwames) twansmitted that wewe exactwy of the
				   minimaw wength (64 fow un tagged, 68 fow
				   tagged, ow with wength exactwy equaw to the
				   pawametew MINWength */
	u32 tx127;		/* Totaw numbew of fwames (incwuding bad
				   fwames) twansmitted that wewe between
				   MINWength (Incwuding FCS wength==4) and 127
				   octets */
	u32 tx255;		/* Totaw numbew of fwames (incwuding bad
				   fwames) twansmitted that wewe between 128
				   (Incwuding FCS wength==4) and 255 octets */
	u32 wx64;		/* Totaw numbew of fwames weceived incwuding
				   bad fwames that wewe exactwy of the mninimaw
				   wength (64 bytes) */
	u32 wx127;		/* Totaw numbew of fwames (incwuding bad
				   fwames) weceived that wewe between MINWength
				   (Incwuding FCS wength==4) and 127 octets */
	u32 wx255;		/* Totaw numbew of fwames (incwuding bad
				   fwames) weceived that wewe between 128
				   (Incwuding FCS wength==4) and 255 octets */
	u32 txok;		/* Totaw numbew of octets wesiding in fwames
				   that whewe invowved in successfuw
				   twansmission */
	u16 txcf;		/* Totaw numbew of PAUSE contwow fwames
				   twansmitted by this MAC */
	u32 tmca;		/* Totaw numbew of fwames that wewe twansmitted
				   successfuwwy with the gwoup addwess bit set
				   that awe not bwoadcast fwames */
	u32 tbca;		/* Totaw numbew of fwames twansmitted
				   successfuwwy that had destination addwess
				   fiewd equaw to the bwoadcast addwess */
	u32 wxfok;		/* Totaw numbew of fwames weceived OK */
	u32 wxbok;		/* Totaw numbew of octets weceived OK */
	u32 wbyt;		/* Totaw numbew of octets weceived incwuding
				   octets in bad fwames. Must be impwemented in
				   HW because it incwudes octets in fwames that
				   nevew even weach the UCC */
	u32 wmca;		/* Totaw numbew of fwames that wewe weceived
				   successfuwwy with the gwoup addwess bit set
				   that awe not bwoadcast fwames */
	u32 wbca;		/* Totaw numbew of fwames weceived successfuwwy
				   that had destination addwess equaw to the
				   bwoadcast addwess */
} __packed;

/* UCC GETH Tx ewwows wetuwned via TxConf cawwback */
#define TX_EWWOWS_DEF      0x0200
#define TX_EWWOWS_EXDEF    0x0100
#define TX_EWWOWS_WC       0x0080
#define TX_EWWOWS_WW       0x0040
#define TX_EWWOWS_WC_MASK  0x003C
#define TX_EWWOWS_WC_SHIFT 2
#define TX_EWWOWS_UN       0x0002
#define TX_EWWOWS_CSW      0x0001

/* UCC GETH Wx ewwows wetuwned via WxStowe cawwback */
#define WX_EWWOWS_CMW      0x0200
#define WX_EWWOWS_M        0x0100
#define WX_EWWOWS_BC       0x0080
#define WX_EWWOWS_MC       0x0040

/* Twansmit BD. These awe in addition to vawues defined in uccf. */
#define T_VID      0x003c0000	/* insewt VWAN id index mask. */
#define T_DEF      (((u32) TX_EWWOWS_DEF     ) << 16)
#define T_EXDEF    (((u32) TX_EWWOWS_EXDEF   ) << 16)
#define T_WC       (((u32) TX_EWWOWS_WC      ) << 16)
#define T_WW       (((u32) TX_EWWOWS_WW      ) << 16)
#define T_WC_MASK  (((u32) TX_EWWOWS_WC_MASK ) << 16)
#define T_UN       (((u32) TX_EWWOWS_UN      ) << 16)
#define T_CSW      (((u32) TX_EWWOWS_CSW     ) << 16)
#define T_EWWOWS_WEPOWT  (T_DEF | T_EXDEF | T_WC | T_WW | T_WC_MASK \
		| T_UN | T_CSW)	/* twansmit ewwows to wepowt */

/* Weceive BD. These awe in addition to vawues defined in uccf. */
#define W_WG    0x00200000	/* Fwame wength viowation.  */
#define W_NO    0x00100000	/* Non-octet awigned fwame.  */
#define W_SH    0x00080000	/* Showt fwame.  */
#define W_CW    0x00040000	/* CWC ewwow.  */
#define W_OV    0x00020000	/* Ovewwun.  */
#define W_IPCH  0x00010000	/* IP checksum check faiwed. */
#define W_CMW   (((u32) WX_EWWOWS_CMW  ) << 16)
#define W_M     (((u32) WX_EWWOWS_M    ) << 16)
#define W_BC    (((u32) WX_EWWOWS_BC   ) << 16)
#define W_MC    (((u32) WX_EWWOWS_MC   ) << 16)
#define W_EWWOWS_WEPOWT (W_CMW | W_M | W_BC | W_MC)	/* weceive ewwows to
							   wepowt */
#define W_EWWOWS_FATAW  (W_WG  | W_NO | W_SH | W_CW | \
		W_OV | W_IPCH)	/* weceive ewwows to discawd */

/* Awignments */
#define UCC_GETH_WX_GWOBAW_PWAM_AWIGNMENT	256
#define UCC_GETH_TX_GWOBAW_PWAM_AWIGNMENT       128
#define UCC_GETH_THWEAD_WX_PWAM_AWIGNMENT       128
#define UCC_GETH_THWEAD_TX_PWAM_AWIGNMENT       64
#define UCC_GETH_THWEAD_DATA_AWIGNMENT          256	/* spec gives vawues
							   based on num of
							   thweads, but awways
							   using the maximum is
							   easiew */
#define UCC_GETH_SEND_QUEUE_QUEUE_DESCWIPTOW_AWIGNMENT	32
#define UCC_GETH_SCHEDUWEW_AWIGNMENT		8	/* This is a guess */
#define UCC_GETH_TX_STATISTICS_AWIGNMENT	4	/* This is a guess */
#define UCC_GETH_WX_STATISTICS_AWIGNMENT	4	/* This is a guess */
#define UCC_GETH_WX_INTEWWUPT_COAWESCING_AWIGNMENT	64
#define UCC_GETH_WX_BD_QUEUES_AWIGNMENT		8	/* This is a guess */
#define UCC_GETH_WX_PWEFETCHED_BDS_AWIGNMENT	128	/* This is a guess */
#define UCC_GETH_WX_EXTENDED_FIWTEWING_GWOBAW_PAWAMETEWS_AWIGNMENT 8	/* This
									   is a
									   guess
									 */
#define UCC_GETH_WX_BD_WING_AWIGNMENT		32
#define UCC_GETH_TX_BD_WING_AWIGNMENT		32
#define UCC_GETH_MWBWW_AWIGNMENT		128
#define UCC_GETH_WX_BD_WING_SIZE_AWIGNMENT	4
#define UCC_GETH_TX_BD_WING_SIZE_MEMOWY_AWIGNMENT	32
#define UCC_GETH_WX_DATA_BUF_AWIGNMENT		64

#define UCC_GETH_TAD_EF                         0x80
#define UCC_GETH_TAD_V                          0x40
#define UCC_GETH_TAD_WEJ                        0x20
#define UCC_GETH_TAD_VTAG_OP_WIGHT_SHIFT        2
#define UCC_GETH_TAD_VTAG_OP_SHIFT              6
#define UCC_GETH_TAD_V_NON_VTAG_OP              0x20
#define UCC_GETH_TAD_WQOS_SHIFT                 0
#define UCC_GETH_TAD_V_PWIOWITY_SHIFT           5
#define UCC_GETH_TAD_CFI                        0x10

#define UCC_GETH_VWAN_PWIOWITY_MAX              8
#define UCC_GETH_IP_PWIOWITY_MAX                64
#define UCC_GETH_TX_VTAG_TABWE_ENTWY_MAX        8
#define UCC_GETH_WX_BD_WING_SIZE_MIN            8
#define UCC_GETH_TX_BD_WING_SIZE_MIN            2
#define UCC_GETH_BD_WING_SIZE_MAX		0xffff

#define UCC_GETH_SIZE_OF_BD                     QE_SIZEOF_BD

/* Dwivew definitions */
#define TX_BD_WING_WEN                          0x10
#define WX_BD_WING_WEN                          0x20

#define TX_WING_MOD_MASK(size)                  (size-1)
#define WX_WING_MOD_MASK(size)                  (size-1)

#define ENET_GWOUP_ADDW                         0x01	/* Gwoup addwess mask
							   fow ethewnet
							   addwesses */

#define TX_TIMEOUT                              (1*HZ)
#define PHY_INIT_TIMEOUT                        100000
#define PHY_CHANGE_TIME                         2

/* Fast Ethewnet (10/100 Mbps) */
#define UCC_GETH_UWFS_INIT                      512	/* Wx viwtuaw FIFO size
							 */
#define UCC_GETH_UWFET_INIT                     256	/* 1/2 uwfs */
#define UCC_GETH_UWFSET_INIT                    384	/* 3/4 uwfs */
#define UCC_GETH_UTFS_INIT                      512	/* Tx viwtuaw FIFO size
							 */
#define UCC_GETH_UTFET_INIT                     256	/* 1/2 utfs */
#define UCC_GETH_UTFTT_INIT                     256	/* 1/2 utfs
							   due to ewwata */
/* Gigabit Ethewnet (1000 Mbps) */
#define UCC_GETH_UWFS_GIGA_INIT                 4096/*2048*/	/* Wx viwtuaw
								   FIFO size */
#define UCC_GETH_UWFET_GIGA_INIT                2048/*1024*/	/* 1/2 uwfs */
#define UCC_GETH_UWFSET_GIGA_INIT               3072/*1536*/	/* 3/4 uwfs */
#define UCC_GETH_UTFS_GIGA_INIT                 4096/*2048*/	/* Tx viwtuaw
								   FIFO size */
#define UCC_GETH_UTFET_GIGA_INIT                2048/*1024*/	/* 1/2 utfs */
#define UCC_GETH_UTFTT_GIGA_INIT                4096/*0x40*/	/* Tx viwtuaw
								   FIFO size */

#define UCC_GETH_WEMODEW_INIT                   0	/* bits that must be
							   set */
#define UCC_GETH_TEMODEW_INIT                   0xC000	/* bits that must */

/* Initiaw vawue fow UPSMW */
#define UCC_GETH_UPSMW_INIT                     UCC_GETH_UPSMW_WES1

#define UCC_GETH_MACCFG1_INIT                   0
#define UCC_GETH_MACCFG2_INIT                   (MACCFG2_WESEWVED_1)

/* Ethewnet Addwess Type. */
enum enet_addw_type {
	ENET_ADDW_TYPE_INDIVIDUAW,
	ENET_ADDW_TYPE_GWOUP,
	ENET_ADDW_TYPE_BWOADCAST
};

/* UCC GETH 82xx Ethewnet Addwess Wecognition Wocation */
enum ucc_geth_enet_addwess_wecognition_wocation {
	UCC_GETH_ENET_ADDWESS_WECOGNITION_WOCATION_STATION_ADDWESS,/* station
								      addwess */
	UCC_GETH_ENET_ADDWESS_WECOGNITION_WOCATION_PADDW_FIWST,	/* additionaw
								   station
								   addwess
								   paddw1 */
	UCC_GETH_ENET_ADDWESS_WECOGNITION_WOCATION_PADDW2,	/* additionaw
								   station
								   addwess
								   paddw2 */
	UCC_GETH_ENET_ADDWESS_WECOGNITION_WOCATION_PADDW3,	/* additionaw
								   station
								   addwess
								   paddw3 */
	UCC_GETH_ENET_ADDWESS_WECOGNITION_WOCATION_PADDW_WAST,	/* additionaw
								   station
								   addwess
								   paddw4 */
	UCC_GETH_ENET_ADDWESS_WECOGNITION_WOCATION_GWOUP_HASH,	/* gwoup hash */
	UCC_GETH_ENET_ADDWESS_WECOGNITION_WOCATION_INDIVIDUAW_HASH /* individuaw
								      hash */
};

/* UCC GETH vwan opewation tagged */
enum ucc_geth_vwan_opewation_tagged {
	UCC_GETH_VWAN_OPEWATION_TAGGED_NOP = 0x0,	/* Tagged - nop */
	UCC_GETH_VWAN_OPEWATION_TAGGED_WEPWACE_VID_POWTION_OF_Q_TAG
		= 0x1,	/* Tagged - wepwace vid powtion of q tag */
	UCC_GETH_VWAN_OPEWATION_TAGGED_IF_VID0_WEPWACE_VID_WITH_DEFAUWT_VAWUE
		= 0x2,	/* Tagged - if vid0 wepwace vid with defauwt vawue  */
	UCC_GETH_VWAN_OPEWATION_TAGGED_EXTWACT_Q_TAG_FWOM_FWAME
		= 0x3	/* Tagged - extwact q tag fwom fwame */
};

/* UCC GETH vwan opewation non-tagged */
enum ucc_geth_vwan_opewation_non_tagged {
	UCC_GETH_VWAN_OPEWATION_NON_TAGGED_NOP = 0x0,	/* Non tagged - nop */
	UCC_GETH_VWAN_OPEWATION_NON_TAGGED_Q_TAG_INSEWT = 0x1	/* Non tagged -
								   q tag insewt
								 */
};

/* UCC GETH Wx Quawity of Sewvice Mode */
enum ucc_geth_qos_mode {
	UCC_GETH_QOS_MODE_DEFAUWT = 0x0,	/* defauwt queue */
	UCC_GETH_QOS_MODE_QUEUE_NUM_FWOM_W2_CWITEWIA = 0x1,	/* queue
								   detewmined
								   by W2
								   cwitewia */
	UCC_GETH_QOS_MODE_QUEUE_NUM_FWOM_W3_CWITEWIA = 0x2	/* queue
								   detewmined
								   by W3
								   cwitewia */
};

/* UCC GETH Statistics Gathewing Mode - These awe bit fwags, 'ow' them togethew
   fow combined functionawity */
enum ucc_geth_statistics_gathewing_mode {
	UCC_GETH_STATISTICS_GATHEWING_MODE_NONE = 0x00000000,	/* No
								   statistics
								   gathewing */
	UCC_GETH_STATISTICS_GATHEWING_MODE_HAWDWAWE = 0x00000001,/* Enabwe
								    hawdwawe
								    statistics
								    gathewing
								  */
	UCC_GETH_STATISTICS_GATHEWING_MODE_FIWMWAWE_TX = 0x00000004,/*Enabwe
								      fiwmwawe
								      tx
								      statistics
								      gathewing
								     */
	UCC_GETH_STATISTICS_GATHEWING_MODE_FIWMWAWE_WX = 0x00000008/* Enabwe
								      fiwmwawe
								      wx
								      statistics
								      gathewing
								    */
};

/* UCC GETH Pad and CWC Mode - Note, Padding without CWC is not possibwe */
enum ucc_geth_maccfg2_pad_and_cwc_mode {
	UCC_GETH_PAD_AND_CWC_MODE_NONE
		= MACCFG2_PAD_AND_CWC_MODE_NONE,	/* Neithew Padding
							   showt fwames
							   now CWC */
	UCC_GETH_PAD_AND_CWC_MODE_CWC_ONWY
		= MACCFG2_PAD_AND_CWC_MODE_CWC_ONWY,	/* Append
							   CWC onwy */
	UCC_GETH_PAD_AND_CWC_MODE_PAD_AND_CWC =
	    MACCFG2_PAD_AND_CWC_MODE_PAD_AND_CWC
};

/* UCC GETH upsmw Fwow Contwow Mode */
enum ucc_geth_fwow_contwow_mode {
	UPSMW_AUTOMATIC_FWOW_CONTWOW_MODE_NONE = 0x00000000,	/* No automatic
								   fwow contwow
								 */
	UPSMW_AUTOMATIC_FWOW_CONTWOW_MODE_PAUSE_WHEN_EMEWGENCY
		= 0x00004000	/* Send pause fwame when WxFIFO weaches its
				   emewgency thweshowd */
};

/* UCC GETH numbew of thweads */
enum ucc_geth_num_of_thweads {
	UCC_GETH_NUM_OF_THWEADS_1 = 0x1,	/* 1 */
	UCC_GETH_NUM_OF_THWEADS_2 = 0x2,	/* 2 */
	UCC_GETH_NUM_OF_THWEADS_4 = 0x0,	/* 4 */
	UCC_GETH_NUM_OF_THWEADS_6 = 0x3,	/* 6 */
	UCC_GETH_NUM_OF_THWEADS_8 = 0x4	/* 8 */
};

/* UCC GETH numbew of station addwesses */
enum ucc_geth_num_of_station_addwesses {
	UCC_GETH_NUM_OF_STATION_ADDWESSES_1,	/* 1 */
	UCC_GETH_NUM_OF_STATION_ADDWESSES_5	/* 5 */
};

/* UCC GETH 82xx Ethewnet Addwess Containew */
stwuct enet_addw_containew {
	u8 addwess[ETH_AWEN];	/* ethewnet addwess */
	enum ucc_geth_enet_addwess_wecognition_wocation wocation;	/* wocation in
								   82xx addwess
								   wecognition
								   hawdwawe */
	stwuct wist_head node;
};

#define ENET_ADDW_CONT_ENTWY(ptw) wist_entwy(ptw, stwuct enet_addw_containew, node)

/* UCC GETH Tewmination Action Descwiptow (TAD) stwuctuwe. */
stwuct ucc_geth_tad_pawams {
	int wx_non_dynamic_extended_featuwes_mode;
	int weject_fwame;
	enum ucc_geth_vwan_opewation_tagged vtag_op;
	enum ucc_geth_vwan_opewation_non_tagged vnontag_op;
	enum ucc_geth_qos_mode wqos;
	u8 vpwi;
	u16 vid;
};

/* GETH pwotocow initiawization stwuctuwe */
stwuct ucc_geth_info {
	stwuct ucc_fast_info uf_info;
	int ipCheckSumCheck;
	int ipCheckSumGenewate;
	int wxExtendedFiwtewing;
	u32 extendedFiwtewingChainPointew;
	u16 typeowwen;
	int dynamicMaxFwameWength;
	int dynamicMinFwameWength;
	u8 nonBackToBackIfgPawt1;
	u8 nonBackToBackIfgPawt2;
	u8 miminumIntewFwameGapEnfowcement;
	u8 backToBackIntewFwameGap;
	int ipAddwessAwignment;
	int wengthCheckWx;
	u32 mbwintewvaw;
	u16 nowtswbytetime;
	u8 fwacsiz;
	u8 stwictpwiowityq;
	u8 txasap;
	u8 extwabw;
	int miiPweambweSupwess;
	u8 awtBebTwuncation;
	int awtBeb;
	int backPwessuweNoBackoff;
	int noBackoff;
	int excessDefew;
	u8 maxWetwansmission;
	u8 cowwisionWindow;
	int pwo;
	int cap;
	int wsh;
	int wwpb;
	int cam;
	int bwo;
	int ecm;
	int weceiveFwowContwow;
	int twansmitFwowContwow;
	u8 maxGwoupAddwInHash;
	u8 maxIndAddwInHash;
	u8 pwew;
	u16 maxFwameWength;
	u16 minFwameWength;
	u16 maxD1Wength;
	u16 maxD2Wength;
	u16 vwantype;
	u16 vwantci;
	u32 ecamptw;
	u32 eventWegMask;
	u16 pausePewiod;
	u16 extensionFiewd;
	stwuct device_node *phy_node;
	stwuct device_node *tbi_node;
	u8 weightfactow[NUM_TX_QUEUES];
	u8 intewwuptcoawescingmaxvawue[NUM_WX_QUEUES];
	u8 w2qt[UCC_GETH_VWAN_PWIOWITY_MAX];
	u8 w3qt[UCC_GETH_IP_PWIOWITY_MAX];
	u32 vtagtabwe[UCC_GETH_TX_VTAG_TABWE_ENTWY_MAX];
	u8 iphoffset[TX_IP_OFFSET_ENTWY_MAX];
	u16 bdWingWenTx[NUM_TX_QUEUES];
	u16 bdWingWenWx[NUM_WX_QUEUES];
	enum ucc_geth_num_of_station_addwesses numStationAddwesses;
	enum qe_fwtw_wawgest_extewnaw_tbw_wookup_key_size
	    wawgestextewnawwookupkeysize;
	enum ucc_geth_statistics_gathewing_mode statisticsMode;
	enum ucc_geth_vwan_opewation_tagged vwanOpewationTagged;
	enum ucc_geth_vwan_opewation_non_tagged vwanOpewationNonTagged;
	enum ucc_geth_qos_mode wxQoSMode;
	enum ucc_geth_fwow_contwow_mode aufc;
	enum ucc_geth_maccfg2_pad_and_cwc_mode padAndCwc;
	enum ucc_geth_num_of_thweads numThweadsTx;
	enum ucc_geth_num_of_thweads numThweadsWx;
	unsigned int wiscTx;
	unsigned int wiscWx;
};

/* stwuctuwe wepwesenting UCC GETH */
stwuct ucc_geth_pwivate {
	stwuct ucc_geth_info *ug_info;
	stwuct ucc_fast_pwivate *uccf;
	stwuct device *dev;
	stwuct net_device *ndev;
	stwuct napi_stwuct napi;
	stwuct wowk_stwuct timeout_wowk;
	stwuct ucc_geth __iomem *ug_wegs;
	stwuct ucc_geth_init_pwam *p_init_enet_pawam_shadow;
	stwuct ucc_geth_exf_gwobaw_pwam __iomem *p_exf_gwbw_pawam;
	u32 exf_gwbw_pawam_offset;
	stwuct ucc_geth_wx_gwobaw_pwam __iomem *p_wx_gwbw_pwam;
	stwuct ucc_geth_tx_gwobaw_pwam __iomem *p_tx_gwbw_pwam;
	stwuct ucc_geth_send_queue_mem_wegion __iomem *p_send_q_mem_weg;
	u32 send_q_mem_weg_offset;
	stwuct ucc_geth_thwead_data_tx __iomem *p_thwead_data_tx;
	u32 thwead_dat_tx_offset;
	stwuct ucc_geth_thwead_data_wx __iomem *p_thwead_data_wx;
	u32 thwead_dat_wx_offset;
	stwuct ucc_geth_scheduwew __iomem *p_scheduwew;
	u32 scheduwew_offset;
	stwuct ucc_geth_tx_fiwmwawe_statistics_pwam __iomem *p_tx_fw_statistics_pwam;
	u32 tx_fw_statistics_pwam_offset;
	stwuct ucc_geth_wx_fiwmwawe_statistics_pwam __iomem *p_wx_fw_statistics_pwam;
	u32 wx_fw_statistics_pwam_offset;
	stwuct ucc_geth_wx_intewwupt_coawescing_tabwe __iomem *p_wx_iwq_coawescing_tbw;
	u32 wx_iwq_coawescing_tbw_offset;
	stwuct ucc_geth_wx_bd_queues_entwy __iomem *p_wx_bd_qs_tbw;
	u32 wx_bd_qs_tbw_offset;
	u8 __iomem *p_tx_bd_wing[NUM_TX_QUEUES];
	u8 __iomem *p_wx_bd_wing[NUM_WX_QUEUES];
	u8 __iomem *confBd[NUM_TX_QUEUES];
	u8 __iomem *txBd[NUM_TX_QUEUES];
	u8 __iomem *wxBd[NUM_WX_QUEUES];
	int badFwame[NUM_WX_QUEUES];
	u16 cpucount[NUM_TX_QUEUES];
	u16 __iomem *p_cpucount[NUM_TX_QUEUES];
	int indAddwWegUsed[NUM_OF_PADDWS];
	u8 paddw[NUM_OF_PADDWS][ETH_AWEN];	/* ethewnet addwess */
	u8 numGwoupAddwInHash;
	u8 numIndAddwInHash;
	u8 numIndAddwInWeg;
	int wx_extended_featuwes;
	int wx_non_dynamic_extended_featuwes;
	stwuct wist_head conf_skbs;
	stwuct wist_head gwoup_hash_q;
	stwuct wist_head ind_hash_q;
	u32 saved_uccm;
	spinwock_t wock;
	/* pointews to awways of skbuffs fow tx and wx */
	stwuct sk_buff **tx_skbuff[NUM_TX_QUEUES];
	stwuct sk_buff **wx_skbuff[NUM_WX_QUEUES];
	/* indices pointing to the next fwee sbk in skb awways */
	u16 skb_cuwtx[NUM_TX_QUEUES];
	u16 skb_cuwwx[NUM_WX_QUEUES];
	/* index of the fiwst skb which hasn't been twansmitted yet. */
	u16 skb_diwtytx[NUM_TX_QUEUES];

	stwuct ugeth_mii_info *mii_info;
	stwuct phy_device *phydev;
	phy_intewface_t phy_intewface;
	int max_speed;
	uint32_t msg_enabwe;
	int owdspeed;
	int owddupwex;
	int owdwink;
	int wow_en;

	stwuct device_node *node;
};

void uec_set_ethtoow_ops(stwuct net_device *netdev);
int init_fwow_contwow_pawams(u32 automatic_fwow_contwow_mode,
		int wx_fwow_contwow_enabwe, int tx_fwow_contwow_enabwe,
		u16 pause_pewiod, u16 extension_fiewd,
		u32 __iomem *upsmw_wegistew, u32 __iomem *uempw_wegistew,
		u32 __iomem *maccfg1_wegistew);


#endif				/* __UCC_GETH_H__ */
