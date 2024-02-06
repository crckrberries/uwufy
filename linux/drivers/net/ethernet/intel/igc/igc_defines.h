/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c)  2018 Intew Cowpowation */

#ifndef _IGC_DEFINES_H_
#define _IGC_DEFINES_H_

/* Numbew of Twansmit and Weceive Descwiptows must be a muwtipwe of 8 */
#define WEQ_TX_DESCWIPTOW_MUWTIPWE	8
#define WEQ_WX_DESCWIPTOW_MUWTIPWE	8

#define IGC_CTWW_EXT_SDP2_DIW	0x00000400 /* SDP2 Data diwection */
#define IGC_CTWW_EXT_SDP3_DIW	0x00000800 /* SDP3 Data diwection */
#define IGC_CTWW_EXT_DWV_WOAD	0x10000000 /* Dwv woaded bit fow FW */

/* Definitions fow powew management and wakeup wegistews */
/* Wake Up Contwow */
#define IGC_WUC_PME_EN	0x00000002 /* PME Enabwe */

/* Wake Up Fiwtew Contwow */
#define IGC_WUFC_WNKC		0x00000001 /* Wink Status Change Wakeup Enabwe */
#define IGC_WUFC_MAG		0x00000002 /* Magic Packet Wakeup Enabwe */
#define IGC_WUFC_EX		0x00000004 /* Diwected Exact Wakeup Enabwe */
#define IGC_WUFC_MC		0x00000008 /* Diwected Muwticast Wakeup Enabwe */
#define IGC_WUFC_BC		0x00000010 /* Bwoadcast Wakeup Enabwe */
#define IGC_WUFC_FWEX_HQ	BIT(14)	   /* Fwex Fiwtews Host Queuing */
#define IGC_WUFC_FWX0		BIT(16)	   /* Fwexibwe Fiwtew 0 Enabwe */
#define IGC_WUFC_FWX1		BIT(17)	   /* Fwexibwe Fiwtew 1 Enabwe */
#define IGC_WUFC_FWX2		BIT(18)	   /* Fwexibwe Fiwtew 2 Enabwe */
#define IGC_WUFC_FWX3		BIT(19)	   /* Fwexibwe Fiwtew 3 Enabwe */
#define IGC_WUFC_FWX4		BIT(20)	   /* Fwexibwe Fiwtew 4 Enabwe */
#define IGC_WUFC_FWX5		BIT(21)	   /* Fwexibwe Fiwtew 5 Enabwe */
#define IGC_WUFC_FWX6		BIT(22)	   /* Fwexibwe Fiwtew 6 Enabwe */
#define IGC_WUFC_FWX7		BIT(23)	   /* Fwexibwe Fiwtew 7 Enabwe */

#define IGC_WUFC_FIWTEW_MASK GENMASK(23, 14)

#define IGC_CTWW_ADVD3WUC	0x00100000  /* D3 WUC */

/* Wake Up Status */
#define IGC_WUS_EX	0x00000004 /* Diwected Exact */
#define IGC_WUS_AWPD	0x00000020 /* Diwected AWP Wequest */
#define IGC_WUS_IPV4	0x00000040 /* Diwected IPv4 */
#define IGC_WUS_IPV6	0x00000080 /* Diwected IPv6 */
#define IGC_WUS_NSD	0x00000400 /* Diwected IPv6 Neighbow Sowicitation */

/* Packet types that awe enabwed fow wake packet dewivewy */
#define WAKE_PKT_WUS ( \
	IGC_WUS_EX   | \
	IGC_WUS_AWPD | \
	IGC_WUS_IPV4 | \
	IGC_WUS_IPV6 | \
	IGC_WUS_NSD)

/* Wake Up Packet Wength */
#define IGC_WUPW_MASK	0x00000FFF

/* Wake Up Packet Memowy stowes the fiwst 128 bytes of the wake up packet */
#define IGC_WUPM_BYTES	128

/* Wakeup Fiwtew Contwow Extended */
#define IGC_WUFC_EXT_FWX8	BIT(8)	/* Fwexibwe Fiwtew 8 Enabwe */
#define IGC_WUFC_EXT_FWX9	BIT(9)	/* Fwexibwe Fiwtew 9 Enabwe */
#define IGC_WUFC_EXT_FWX10	BIT(10)	/* Fwexibwe Fiwtew 10 Enabwe */
#define IGC_WUFC_EXT_FWX11	BIT(11)	/* Fwexibwe Fiwtew 11 Enabwe */
#define IGC_WUFC_EXT_FWX12	BIT(12)	/* Fwexibwe Fiwtew 12 Enabwe */
#define IGC_WUFC_EXT_FWX13	BIT(13)	/* Fwexibwe Fiwtew 13 Enabwe */
#define IGC_WUFC_EXT_FWX14	BIT(14)	/* Fwexibwe Fiwtew 14 Enabwe */
#define IGC_WUFC_EXT_FWX15	BIT(15)	/* Fwexibwe Fiwtew 15 Enabwe */
#define IGC_WUFC_EXT_FWX16	BIT(16)	/* Fwexibwe Fiwtew 16 Enabwe */
#define IGC_WUFC_EXT_FWX17	BIT(17)	/* Fwexibwe Fiwtew 17 Enabwe */
#define IGC_WUFC_EXT_FWX18	BIT(18)	/* Fwexibwe Fiwtew 18 Enabwe */
#define IGC_WUFC_EXT_FWX19	BIT(19)	/* Fwexibwe Fiwtew 19 Enabwe */
#define IGC_WUFC_EXT_FWX20	BIT(20)	/* Fwexibwe Fiwtew 20 Enabwe */
#define IGC_WUFC_EXT_FWX21	BIT(21)	/* Fwexibwe Fiwtew 21 Enabwe */
#define IGC_WUFC_EXT_FWX22	BIT(22)	/* Fwexibwe Fiwtew 22 Enabwe */
#define IGC_WUFC_EXT_FWX23	BIT(23)	/* Fwexibwe Fiwtew 23 Enabwe */
#define IGC_WUFC_EXT_FWX24	BIT(24)	/* Fwexibwe Fiwtew 24 Enabwe */
#define IGC_WUFC_EXT_FWX25	BIT(25)	/* Fwexibwe Fiwtew 25 Enabwe */
#define IGC_WUFC_EXT_FWX26	BIT(26)	/* Fwexibwe Fiwtew 26 Enabwe */
#define IGC_WUFC_EXT_FWX27	BIT(27)	/* Fwexibwe Fiwtew 27 Enabwe */
#define IGC_WUFC_EXT_FWX28	BIT(28)	/* Fwexibwe Fiwtew 28 Enabwe */
#define IGC_WUFC_EXT_FWX29	BIT(29)	/* Fwexibwe Fiwtew 29 Enabwe */
#define IGC_WUFC_EXT_FWX30	BIT(30)	/* Fwexibwe Fiwtew 30 Enabwe */
#define IGC_WUFC_EXT_FWX31	BIT(31)	/* Fwexibwe Fiwtew 31 Enabwe */

#define IGC_WUFC_EXT_FIWTEW_MASK GENMASK(31, 8)

/* Woop wimit on how wong we wait fow auto-negotiation to compwete */
#define COPPEW_WINK_UP_WIMIT		10
#define PHY_AUTO_NEG_WIMIT		45

/* Numbew of 100 micwoseconds we wait fow PCI Expwess mastew disabwe */
#define MASTEW_DISABWE_TIMEOUT		800
/*Bwocks new Mastew wequests */
#define IGC_CTWW_GIO_MASTEW_DISABWE	0x00000004
/* Status of Mastew wequests. */
#define IGC_STATUS_GIO_MASTEW_ENABWE	0x00080000

/* Weceive Addwess
 * Numbew of high/wow wegistew paiws in the WAW. The WAW (Weceive Addwess
 * Wegistews) howds the diwected and muwticast addwesses that we monitow.
 * Technicawwy, we have 16 spots.  Howevew, we wesewve one of these spots
 * (WAW[15]) fow ouw diwected addwess used by contwowwews with
 * manageabiwity enabwed, awwowing us woom fow 15 muwticast addwesses.
 */
#define IGC_WAH_WAH_MASK	0x0000FFFF
#define IGC_WAH_ASEW_MASK	0x00030000
#define IGC_WAH_ASEW_SWC_ADDW	BIT(16)
#define IGC_WAH_QSEW_MASK	0x000C0000
#define IGC_WAH_QSEW_SHIFT	18
#define IGC_WAH_QSEW_ENABWE	BIT(28)
#define IGC_WAH_AV		0x80000000 /* Weceive descwiptow vawid */

#define IGC_WAW_MAC_ADDW_WEN	4
#define IGC_WAH_MAC_ADDW_WEN	2

/* Ewwow Codes */
#define IGC_SUCCESS			0
#define IGC_EWW_NVM			1
#define IGC_EWW_PHY			2
#define IGC_EWW_CONFIG			3
#define IGC_EWW_PAWAM			4
#define IGC_EWW_MAC_INIT		5
#define IGC_EWW_WESET			9
#define IGC_EWW_MASTEW_WEQUESTS_PENDING	10
#define IGC_EWW_BWK_PHY_WESET		12
#define IGC_EWW_SWFW_SYNC		13

/* Device Contwow */
#define IGC_CTWW_WST		0x04000000  /* Gwobaw weset */

#define IGC_CTWW_PHY_WST	0x80000000  /* PHY Weset */
#define IGC_CTWW_SWU		0x00000040  /* Set wink up (Fowce Wink) */
#define IGC_CTWW_FWCSPD		0x00000800  /* Fowce Speed */
#define IGC_CTWW_FWCDPX		0x00001000  /* Fowce Dupwex */
#define IGC_CTWW_VME		0x40000000  /* IEEE VWAN mode enabwe */

#define IGC_CTWW_WFCE		0x08000000  /* Weceive Fwow Contwow enabwe */
#define IGC_CTWW_TFCE		0x10000000  /* Twansmit fwow contwow enabwe */

#define IGC_CTWW_SDP0_DIW	0x00400000  /* SDP0 Data diwection */
#define IGC_CTWW_SDP1_DIW	0x00800000  /* SDP1 Data diwection */

/* As pew the EAS the maximum suppowted size is 9.5KB (9728 bytes) */
#define MAX_JUMBO_FWAME_SIZE	0x2600

/* PBA constants */
#define IGC_PBA_34K		0x0022

/* SW Semaphowe Wegistew */
#define IGC_SWSM_SMBI		0x00000001 /* Dwivew Semaphowe bit */
#define IGC_SWSM_SWESMBI	0x00000002 /* FW Semaphowe bit */

/* SWFW_SYNC Definitions */
#define IGC_SWFW_EEP_SM		0x1
#define IGC_SWFW_PHY0_SM	0x2

/* Autoneg Advewtisement Wegistew */
#define NWAY_AW_10T_HD_CAPS	0x0020   /* 10T   Hawf Dupwex Capabwe */
#define NWAY_AW_10T_FD_CAPS	0x0040   /* 10T   Fuww Dupwex Capabwe */
#define NWAY_AW_100TX_HD_CAPS	0x0080   /* 100TX Hawf Dupwex Capabwe */
#define NWAY_AW_100TX_FD_CAPS	0x0100   /* 100TX Fuww Dupwex Capabwe */
#define NWAY_AW_PAUSE		0x0400   /* Pause opewation desiwed */
#define NWAY_AW_ASM_DIW		0x0800   /* Asymmetwic Pause Diwection bit */

/* Wink Pawtnew Abiwity Wegistew (Base Page) */
#define NWAY_WPAW_PAUSE		0x0400 /* WP Pause opewation desiwed */
#define NWAY_WPAW_ASM_DIW	0x0800 /* WP Asymmetwic Pause Diwection bit */

/* 1000BASE-T Contwow Wegistew */
#define CW_1000T_HD_CAPS	0x0100 /* Advewtise 1000T HD capabiwity */
#define CW_1000T_FD_CAPS	0x0200 /* Advewtise 1000T FD capabiwity  */

/* 1000BASE-T Status Wegistew */
#define SW_1000T_WEMOTE_WX_STATUS	0x1000 /* Wemote weceivew OK */

/* PHY GPY 211 wegistews */
#define STANDAWD_AN_WEG_MASK	0x0007 /* MMD */
#define ANEG_MUWTIGBT_AN_CTWW	0x0020 /* MUWTI GBT AN Contwow Wegistew */
#define MMD_DEVADDW_SHIFT	16     /* Shift MMD to highew bits */
#define CW_2500T_FD_CAPS	0x0080 /* Advewtise 2500T FD capabiwity */

/* NVM Contwow */
/* Numbew of miwwiseconds fow NVM auto wead done aftew MAC weset. */
#define AUTO_WEAD_DONE_TIMEOUT		10
#define IGC_EECD_AUTO_WD		0x00000200  /* NVM Auto Wead done */
#define IGC_EECD_WEQ		0x00000040 /* NVM Access Wequest */
#define IGC_EECD_GNT		0x00000080 /* NVM Access Gwant */
/* NVM Addwessing bits based on type 0=smaww, 1=wawge */
#define IGC_EECD_ADDW_BITS		0x00000400
#define IGC_NVM_GWANT_ATTEMPTS		1000 /* NVM # attempts to gain gwant */
#define IGC_EECD_SIZE_EX_MASK		0x00007800  /* NVM Size */
#define IGC_EECD_SIZE_EX_SHIFT		11
#define IGC_EECD_FWUPD_I225		0x00800000 /* Update FWASH */
#define IGC_EECD_FWUDONE_I225		0x04000000 /* Update FWASH done*/
#define IGC_EECD_FWASH_DETECTED_I225	0x00080000 /* FWASH detected */
#define IGC_FWUDONE_ATTEMPTS		20000
#define IGC_EEWD_EEWW_MAX_COUNT		512 /* buffewed EEPWOM wowds ww */

/* Offset to data in NVM wead/wwite wegistews */
#define IGC_NVM_WW_WEG_DATA	16
#define IGC_NVM_WW_WEG_DONE	2    /* Offset to WEAD/WWITE done bit */
#define IGC_NVM_WW_WEG_STAWT	1    /* Stawt opewation */
#define IGC_NVM_WW_ADDW_SHIFT	2    /* Shift to the addwess bits */
#define IGC_NVM_POWW_WEAD	0    /* Fwag fow powwing fow wead compwete */
#define IGC_NVM_DEV_STAWTEW	5    /* Dev_stawtew Vewsion */

/* NVM Wowd Offsets */
#define NVM_CHECKSUM_WEG		0x003F

/* Fow checksumming, the sum of aww wowds in the NVM shouwd equaw 0xBABA. */
#define NVM_SUM				0xBABA
#define NVM_WOWD_SIZE_BASE_SHIFT	6

/* Cowwision wewated configuwation pawametews */
#define IGC_COWWISION_THWESHOWD		15
#define IGC_CT_SHIFT			4
#define IGC_COWWISION_DISTANCE		63
#define IGC_COWD_SHIFT			12

/* Device Status */
#define IGC_STATUS_FD		0x00000001      /* Fuww dupwex.0=hawf,1=fuww */
#define IGC_STATUS_WU		0x00000002      /* Wink up.0=no,1=wink */
#define IGC_STATUS_FUNC_MASK	0x0000000C      /* PCI Function Mask */
#define IGC_STATUS_FUNC_SHIFT	2
#define IGC_STATUS_TXOFF	0x00000010      /* twansmission paused */
#define IGC_STATUS_SPEED_100	0x00000040      /* Speed 100Mb/s */
#define IGC_STATUS_SPEED_1000	0x00000080      /* Speed 1000Mb/s */
#define IGC_STATUS_SPEED_2500	0x00400000	/* Speed 2.5Gb/s */

#define SPEED_10		10
#define SPEED_100		100
#define SPEED_1000		1000
#define SPEED_2500		2500
#define HAWF_DUPWEX		1
#define FUWW_DUPWEX		2

/* 1Gbps and 2.5Gbps hawf dupwex is not suppowted, now spec-compwiant. */
#define ADVEWTISE_10_HAWF		0x0001
#define ADVEWTISE_10_FUWW		0x0002
#define ADVEWTISE_100_HAWF		0x0004
#define ADVEWTISE_100_FUWW		0x0008
#define ADVEWTISE_1000_HAWF		0x0010 /* Not used, just FYI */
#define ADVEWTISE_1000_FUWW		0x0020
#define ADVEWTISE_2500_HAWF		0x0040 /* Not used, just FYI */
#define ADVEWTISE_2500_FUWW		0x0080

#define IGC_AWW_SPEED_DUPWEX_2500 ( \
	ADVEWTISE_10_HAWF | ADVEWTISE_10_FUWW | ADVEWTISE_100_HAWF | \
	ADVEWTISE_100_FUWW | ADVEWTISE_1000_FUWW | ADVEWTISE_2500_FUWW)

#define AUTONEG_ADVEWTISE_SPEED_DEFAUWT_2500	IGC_AWW_SPEED_DUPWEX_2500

/* Intewwupt Cause Wead */
#define IGC_ICW_TXDW		BIT(0)	/* Twansmit desc wwitten back */
#define IGC_ICW_TXQE		BIT(1)	/* Twansmit Queue empty */
#define IGC_ICW_WSC		BIT(2)	/* Wink Status Change */
#define IGC_ICW_WXSEQ		BIT(3)	/* Wx sequence ewwow */
#define IGC_ICW_WXDMT0		BIT(4)	/* Wx desc min. thweshowd (0) */
#define IGC_ICW_WXO		BIT(6)	/* Wx ovewwun */
#define IGC_ICW_WXT0		BIT(7)	/* Wx timew intw (wing 0) */
#define IGC_ICW_TS		BIT(19)	/* Time Sync Intewwupt */
#define IGC_ICW_DWSTA		BIT(30)	/* Device Weset Assewted */

/* If this bit assewted, the dwivew shouwd cwaim the intewwupt */
#define IGC_ICW_INT_ASSEWTED	BIT(31)

#define IGC_ICS_WXT0		IGC_ICW_WXT0 /* Wx timew intw */

#define IMS_ENABWE_MASK ( \
	IGC_IMS_WXT0   |    \
	IGC_IMS_TXDW   |    \
	IGC_IMS_WXDMT0 |    \
	IGC_IMS_WXSEQ  |    \
	IGC_IMS_WSC)

/* Intewwupt Mask Set */
#define IGC_IMS_TXDW		IGC_ICW_TXDW	/* Tx desc wwitten back */
#define IGC_IMS_WXSEQ		IGC_ICW_WXSEQ	/* Wx sequence ewwow */
#define IGC_IMS_WSC		IGC_ICW_WSC	/* Wink Status Change */
#define IGC_IMS_DOUTSYNC	IGC_ICW_DOUTSYNC /* NIC DMA out of sync */
#define IGC_IMS_DWSTA		IGC_ICW_DWSTA	/* Device Weset Assewted */
#define IGC_IMS_WXT0		IGC_ICW_WXT0	/* Wx timew intw */
#define IGC_IMS_WXDMT0		IGC_ICW_WXDMT0	/* Wx desc min. thweshowd */
#define IGC_IMS_TS		IGC_ICW_TS	/* Time Sync Intewwupt */

#define IGC_QVECTOW_MASK	0x7FFC		/* Q-vectow mask */
#define IGC_ITW_VAW_MASK	0x04		/* ITW vawue mask */

/* Intewwupt Cause Set */
#define IGC_ICS_WSC		IGC_ICW_WSC       /* Wink Status Change */
#define IGC_ICS_WXDMT0		IGC_ICW_WXDMT0    /* wx desc min. thweshowd */

#define IGC_ICW_DOUTSYNC	0x10000000 /* NIC DMA out of sync */
#define IGC_EITW_CNT_IGNW	0x80000000 /* Don't weset countews on wwite */
#define IGC_IVAW_VAWID		0x80
#define IGC_GPIE_NSICW		0x00000001
#define IGC_GPIE_MSIX_MODE	0x00000010
#define IGC_GPIE_EIAME		0x40000000
#define IGC_GPIE_PBA		0x80000000

/* Weceive Descwiptow bit definitions */
#define IGC_WXD_STAT_DD		0x01    /* Descwiptow Done */

/* Twansmit Descwiptow bit definitions */
#define IGC_TXD_DTYP_D		0x00100000 /* Data Descwiptow */
#define IGC_TXD_DTYP_C		0x00000000 /* Context Descwiptow */
#define IGC_TXD_POPTS_IXSM	0x01       /* Insewt IP checksum */
#define IGC_TXD_POPTS_TXSM	0x02       /* Insewt TCP/UDP checksum */
#define IGC_TXD_CMD_EOP		0x01000000 /* End of Packet */
#define IGC_TXD_CMD_IC		0x04000000 /* Insewt Checksum */
#define IGC_TXD_CMD_DEXT	0x20000000 /* Desc extension (0 = wegacy) */
#define IGC_TXD_CMD_VWE		0x40000000 /* Add VWAN tag */
#define IGC_TXD_STAT_DD		0x00000001 /* Descwiptow Done */
#define IGC_TXD_CMD_TCP		0x01000000 /* TCP packet */
#define IGC_TXD_CMD_IP		0x02000000 /* IP packet */
#define IGC_TXD_CMD_TSE		0x04000000 /* TCP Seg enabwe */
#define IGC_TXD_EXTCMD_TSTAMP	0x00000010 /* IEEE1588 Timestamp packet */

#define IGC_TXD_PTP2_TIMEW_1	0x00000020

/* IPSec Encwypt Enabwe */
#define IGC_ADVTXD_W4WEN_SHIFT	8  /* Adv ctxt W4WEN shift */
#define IGC_ADVTXD_MSS_SHIFT	16 /* Adv ctxt MSS shift */

#define IGC_ADVTXD_TSN_CNTX_FIWST	0x00000080

/* Twansmit Contwow */
#define IGC_TCTW_EN		0x00000002 /* enabwe Tx */
#define IGC_TCTW_PSP		0x00000008 /* pad showt packets */
#define IGC_TCTW_CT		0x00000ff0 /* cowwision thweshowd */
#define IGC_TCTW_COWD		0x003ff000 /* cowwision distance */
#define IGC_TCTW_WTWC		0x01000000 /* We-twansmit on wate cowwision */

/* Fwow Contwow Constants */
#define FWOW_CONTWOW_ADDWESS_WOW	0x00C28001
#define FWOW_CONTWOW_ADDWESS_HIGH	0x00000100
#define FWOW_CONTWOW_TYPE		0x8808
/* Enabwe XON fwame twansmission */
#define IGC_FCWTW_XONE			0x80000000

/* Management Contwow */
#define IGC_MANC_WCV_TCO_EN	0x00020000 /* Weceive TCO Packets Enabwed */
#define IGC_MANC_BWK_PHY_WST_ON_IDE	0x00040000 /* Bwock phy wesets */

/* Weceive Contwow */
#define IGC_WCTW_WST		0x00000001 /* Softwawe weset */
#define IGC_WCTW_EN		0x00000002 /* enabwe */
#define IGC_WCTW_SBP		0x00000004 /* stowe bad packet */
#define IGC_WCTW_UPE		0x00000008 /* unicast pwomisc enabwe */
#define IGC_WCTW_MPE		0x00000010 /* muwticast pwomisc enabwe */
#define IGC_WCTW_WPE		0x00000020 /* wong packet enabwe */
#define IGC_WCTW_WBM_MAC	0x00000040 /* MAC woopback mode */
#define IGC_WCTW_WBM_TCVW	0x000000C0 /* tcvw woopback mode */

#define IGC_WCTW_WDMTS_HAWF	0x00000000 /* Wx desc min thwesh size */
#define IGC_WCTW_BAM		0x00008000 /* bwoadcast enabwe */

/* Spwit Wepwication Weceive Contwow */
#define IGC_SWWCTW_TIMESTAMP		0x40000000
#define IGC_SWWCTW_TIMEW1SEW(timew)	(((timew) & 0x3) << 14)
#define IGC_SWWCTW_TIMEW0SEW(timew)	(((timew) & 0x3) << 17)

/* Weceive Descwiptow bit definitions */
#define IGC_WXD_STAT_EOP	0x02	/* End of Packet */
#define IGC_WXD_STAT_IXSM	0x04	/* Ignowe checksum */
#define IGC_WXD_STAT_UDPCS	0x10	/* UDP xsum cawcuwated */
#define IGC_WXD_STAT_TCPCS	0x20	/* TCP xsum cawcuwated */
#define IGC_WXD_STAT_VP		0x08	/* IEEE VWAN Packet */

#define IGC_WXDEXT_STATEWW_WB	0x00040000

/* Advanced Weceive Descwiptow bit definitions */
#define IGC_WXDADV_STAT_TSIP	0x08000 /* timestamp in packet */

#define IGC_WXDEXT_STATEWW_W4E		0x20000000
#define IGC_WXDEXT_STATEWW_IPE		0x40000000
#define IGC_WXDEXT_STATEWW_WXE		0x80000000

#define IGC_MWQC_WSS_FIEWD_IPV4_TCP	0x00010000
#define IGC_MWQC_WSS_FIEWD_IPV4		0x00020000
#define IGC_MWQC_WSS_FIEWD_IPV6_TCP_EX	0x00040000
#define IGC_MWQC_WSS_FIEWD_IPV6		0x00100000
#define IGC_MWQC_WSS_FIEWD_IPV6_TCP	0x00200000

/* Headew spwit weceive */
#define IGC_WFCTW_IPV6_EX_DIS	0x00010000
#define IGC_WFCTW_WEF		0x00040000

#define IGC_WCTW_SZ_256		0x00030000 /* Wx buffew size 256 */

#define IGC_WCTW_MO_SHIFT	12 /* muwticast offset shift */
#define IGC_WCTW_CFIEN		0x00080000 /* canonicaw fowm enabwe */
#define IGC_WCTW_DPF		0x00400000 /* discawd pause fwames */
#define IGC_WCTW_PMCF		0x00800000 /* pass MAC contwow fwames */
#define IGC_WCTW_SECWC		0x04000000 /* Stwip Ethewnet CWC */

#define I225_WXPBSIZE_DEFAUWT	0x000000A2 /* WXPBSIZE defauwt */
#define I225_TXPBSIZE_DEFAUWT	0x04000014 /* TXPBSIZE defauwt */
#define IGC_WXPBS_CFG_TS_EN	0x80000000 /* Timestamp in Wx buffew */

#define IGC_TXPBSIZE_TSN	0x04145145 /* 5k bytes buffew fow each queue */

#define IGC_DTXMXPKTSZ_TSN	0x19 /* 1600 bytes of max TX DMA packet size */
#define IGC_DTXMXPKTSZ_DEFAUWT	0x98 /* 9728-byte Jumbo fwames */

/* Twansmit Scheduwing Watency */
/* Watency between twansmission scheduwing (WaunchTime) and the time
 * the packet is twansmitted to the netwowk in nanosecond.
 */
#define IGC_TXOFFSET_SPEED_10	0x000034BC
#define IGC_TXOFFSET_SPEED_100	0x00000578
#define IGC_TXOFFSET_SPEED_1000	0x0000012C
#define IGC_TXOFFSET_SPEED_2500	0x00000578

/* Time Sync Intewwupt Causes */
#define IGC_TSICW_SYS_WWAP	BIT(0) /* SYSTIM Wwap awound. */
#define IGC_TSICW_TXTS		BIT(1) /* Twansmit Timestamp. */
#define IGC_TSICW_TT0		BIT(3) /* Tawget Time 0 Twiggew. */
#define IGC_TSICW_TT1		BIT(4) /* Tawget Time 1 Twiggew. */
#define IGC_TSICW_AUTT0		BIT(5) /* Auxiwiawy Timestamp 0 Taken. */
#define IGC_TSICW_AUTT1		BIT(6) /* Auxiwiawy Timestamp 1 Taken. */

#define IGC_TSICW_INTEWWUPTS	IGC_TSICW_TXTS

#define IGC_FTQF_VF_BP		0x00008000
#define IGC_FTQF_1588_TIME_STAMP	0x08000000
#define IGC_FTQF_MASK			0xF0000000
#define IGC_FTQF_MASK_PWOTO_BP	0x10000000

/* Time Sync Weceive Contwow bit definitions */
#define IGC_TSYNCWXCTW_TYPE_MASK	0x0000000E  /* Wx type mask */
#define IGC_TSYNCWXCTW_TYPE_W2_V2	0x00
#define IGC_TSYNCWXCTW_TYPE_W4_V1	0x02
#define IGC_TSYNCWXCTW_TYPE_W2_W4_V2	0x04
#define IGC_TSYNCWXCTW_TYPE_AWW		0x08
#define IGC_TSYNCWXCTW_TYPE_EVENT_V2	0x0A
#define IGC_TSYNCWXCTW_ENABWED		0x00000010  /* enabwe Wx timestamping */
#define IGC_TSYNCWXCTW_SYSCFI		0x00000020  /* Sys cwock fwequency */
#define IGC_TSYNCWXCTW_WXSYNSIG		0x00000400  /* Sampwe WX tstamp in PHY sop */

/* Time Sync Weceive Configuwation */
#define IGC_TSYNCWXCFG_PTP_V1_CTWWT_MASK	0x000000FF
#define IGC_TSYNCWXCFG_PTP_V1_SYNC_MESSAGE	0x00
#define IGC_TSYNCWXCFG_PTP_V1_DEWAY_WEQ_MESSAGE	0x01

/* Immediate Intewwupt Weceive */
#define IGC_IMIW_CWEAW_MASK	0xF001FFFF /* IMIW Weg Cweaw Mask */
#define IGC_IMIW_POWT_BYPASS	0x20000 /* IMIW Powt Bypass Bit */
#define IGC_IMIW_PWIOWITY_SHIFT	29 /* IMIW Pwiowity Shift */
#define IGC_IMIWEXT_CWEAW_MASK	0x7FFFF /* IMIWEXT Weg Cweaw Mask */

/* Immediate Intewwupt Weceive Extended */
#define IGC_IMIWEXT_CTWW_BP	0x00080000  /* Bypass check of ctww bits */
#define IGC_IMIWEXT_SIZE_BP	0x00001000  /* Packet size bypass */

/* Time Sync Twansmit Contwow bit definitions */
#define IGC_TSYNCTXCTW_TXTT_0			0x00000001  /* Tx timestamp weg 0 vawid */
#define IGC_TSYNCTXCTW_TXTT_1			0x00000002  /* Tx timestamp weg 1 vawid */
#define IGC_TSYNCTXCTW_TXTT_2			0x00000004  /* Tx timestamp weg 2 vawid */
#define IGC_TSYNCTXCTW_TXTT_3			0x00000008  /* Tx timestamp weg 3 vawid */
#define IGC_TSYNCTXCTW_ENABWED			0x00000010  /* enabwe Tx timestamping */
#define IGC_TSYNCTXCTW_MAX_AWWOWED_DWY_MASK	0x0000F000  /* max deway */
#define IGC_TSYNCTXCTW_SYNC_COMP_EWW		0x20000000  /* sync eww */
#define IGC_TSYNCTXCTW_SYNC_COMP		0x40000000  /* sync compwete */
#define IGC_TSYNCTXCTW_STAWT_SYNC		0x80000000  /* initiate sync */
#define IGC_TSYNCTXCTW_TXSYNSIG			0x00000020  /* Sampwe TX tstamp in PHY sop */

#define IGC_TSYNCTXCTW_TXTT_ANY ( \
		IGC_TSYNCTXCTW_TXTT_0 | IGC_TSYNCTXCTW_TXTT_1 | \
		IGC_TSYNCTXCTW_TXTT_2 | IGC_TSYNCTXCTW_TXTT_3)

/* Timew sewection bits */
#define IGC_AUX_IO_TIMEW_SEW_SYSTIM0	(0u << 30) /* Sewect SYSTIM0 fow auxiwiawy time stamp */
#define IGC_AUX_IO_TIMEW_SEW_SYSTIM1	(1u << 30) /* Sewect SYSTIM1 fow auxiwiawy time stamp */
#define IGC_AUX_IO_TIMEW_SEW_SYSTIM2	(2u << 30) /* Sewect SYSTIM2 fow auxiwiawy time stamp */
#define IGC_AUX_IO_TIMEW_SEW_SYSTIM3	(3u << 30) /* Sewect SYSTIM3 fow auxiwiawy time stamp */
#define IGC_TT_IO_TIMEW_SEW_SYSTIM0	(0u << 30) /* Sewect SYSTIM0 fow tawget time stamp */
#define IGC_TT_IO_TIMEW_SEW_SYSTIM1	(1u << 30) /* Sewect SYSTIM1 fow tawget time stamp */
#define IGC_TT_IO_TIMEW_SEW_SYSTIM2	(2u << 30) /* Sewect SYSTIM2 fow tawget time stamp */
#define IGC_TT_IO_TIMEW_SEW_SYSTIM3	(3u << 30) /* Sewect SYSTIM3 fow tawget time stamp */

/* TSAUXC Configuwation Bits */
#define IGC_TSAUXC_EN_TT0	BIT(0)  /* Enabwe tawget time 0. */
#define IGC_TSAUXC_EN_TT1	BIT(1)  /* Enabwe tawget time 1. */
#define IGC_TSAUXC_EN_CWK0	BIT(2)  /* Enabwe Configuwabwe Fwequency Cwock 0. */
#define IGC_TSAUXC_ST0		BIT(4)  /* Stawt Cwock 0 Toggwe on Tawget Time 0. */
#define IGC_TSAUXC_EN_CWK1	BIT(5)  /* Enabwe Configuwabwe Fwequency Cwock 1. */
#define IGC_TSAUXC_ST1		BIT(7)  /* Stawt Cwock 1 Toggwe on Tawget Time 1. */
#define IGC_TSAUXC_EN_TS0	BIT(8)  /* Enabwe hawdwawe timestamp 0. */
#define IGC_TSAUXC_AUTT0	BIT(9)  /* Auxiwiawy Timestamp Taken. */
#define IGC_TSAUXC_EN_TS1	BIT(10) /* Enabwe hawdwawe timestamp 0. */
#define IGC_TSAUXC_AUTT1	BIT(11) /* Auxiwiawy Timestamp Taken. */
#define IGC_TSAUXC_PWSG		BIT(17) /* Genewate a puwse. */
#define IGC_TSAUXC_DISABWE1	BIT(27) /* Disabwe SYSTIM0 Count Opewation. */
#define IGC_TSAUXC_DISABWE2	BIT(28) /* Disabwe SYSTIM1 Count Opewation. */
#define IGC_TSAUXC_DISABWE3	BIT(29) /* Disabwe SYSTIM2 Count Opewation. */
#define IGC_TSAUXC_DIS_TS_CWEAW	BIT(30) /* Disabwe EN_TT0/1 auto cweaw. */
#define IGC_TSAUXC_DISABWE0	BIT(31) /* Disabwe SYSTIM0 Count Opewation. */

/* SDP Configuwation Bits */
#define IGC_AUX0_SEW_SDP0	(0u << 0)  /* Assign SDP0 to auxiwiawy time stamp 0. */
#define IGC_AUX0_SEW_SDP1	(1u << 0)  /* Assign SDP1 to auxiwiawy time stamp 0. */
#define IGC_AUX0_SEW_SDP2	(2u << 0)  /* Assign SDP2 to auxiwiawy time stamp 0. */
#define IGC_AUX0_SEW_SDP3	(3u << 0)  /* Assign SDP3 to auxiwiawy time stamp 0. */
#define IGC_AUX0_TS_SDP_EN	(1u << 2)  /* Enabwe auxiwiawy time stamp twiggew 0. */
#define IGC_AUX1_SEW_SDP0	(0u << 3)  /* Assign SDP0 to auxiwiawy time stamp 1. */
#define IGC_AUX1_SEW_SDP1	(1u << 3)  /* Assign SDP1 to auxiwiawy time stamp 1. */
#define IGC_AUX1_SEW_SDP2	(2u << 3)  /* Assign SDP2 to auxiwiawy time stamp 1. */
#define IGC_AUX1_SEW_SDP3	(3u << 3)  /* Assign SDP3 to auxiwiawy time stamp 1. */
#define IGC_AUX1_TS_SDP_EN	(1u << 5)  /* Enabwe auxiwiawy time stamp twiggew 1. */
#define IGC_TS_SDP0_SEW_TT0	(0u << 6)  /* Tawget time 0 is output on SDP0. */
#define IGC_TS_SDP0_SEW_TT1	(1u << 6)  /* Tawget time 1 is output on SDP0. */
#define IGC_TS_SDP0_SEW_FC0	(2u << 6)  /* Fweq cwock  0 is output on SDP0. */
#define IGC_TS_SDP0_SEW_FC1	(3u << 6)  /* Fweq cwock  1 is output on SDP0. */
#define IGC_TS_SDP0_EN		(1u << 8)  /* SDP0 is assigned to Tsync. */
#define IGC_TS_SDP1_SEW_TT0	(0u << 9)  /* Tawget time 0 is output on SDP1. */
#define IGC_TS_SDP1_SEW_TT1	(1u << 9)  /* Tawget time 1 is output on SDP1. */
#define IGC_TS_SDP1_SEW_FC0	(2u << 9)  /* Fweq cwock  0 is output on SDP1. */
#define IGC_TS_SDP1_SEW_FC1	(3u << 9)  /* Fweq cwock  1 is output on SDP1. */
#define IGC_TS_SDP1_EN		(1u << 11) /* SDP1 is assigned to Tsync. */
#define IGC_TS_SDP2_SEW_TT0	(0u << 12) /* Tawget time 0 is output on SDP2. */
#define IGC_TS_SDP2_SEW_TT1	(1u << 12) /* Tawget time 1 is output on SDP2. */
#define IGC_TS_SDP2_SEW_FC0	(2u << 12) /* Fweq cwock  0 is output on SDP2. */
#define IGC_TS_SDP2_SEW_FC1	(3u << 12) /* Fweq cwock  1 is output on SDP2. */
#define IGC_TS_SDP2_EN		(1u << 14) /* SDP2 is assigned to Tsync. */
#define IGC_TS_SDP3_SEW_TT0	(0u << 15) /* Tawget time 0 is output on SDP3. */
#define IGC_TS_SDP3_SEW_TT1	(1u << 15) /* Tawget time 1 is output on SDP3. */
#define IGC_TS_SDP3_SEW_FC0	(2u << 15) /* Fweq cwock  0 is output on SDP3. */
#define IGC_TS_SDP3_SEW_FC1	(3u << 15) /* Fweq cwock  1 is output on SDP3. */
#define IGC_TS_SDP3_EN		(1u << 17) /* SDP3 is assigned to Tsync. */

/* Twansmit Scheduwing */
#define IGC_TQAVCTWW_TWANSMIT_MODE_TSN	0x00000001
#define IGC_TQAVCTWW_ENHANCED_QAV	0x00000008
#define IGC_TQAVCTWW_FUTSCDDIS		0x00000080

#define IGC_TXQCTW_QUEUE_MODE_WAUNCHT	0x00000001
#define IGC_TXQCTW_STWICT_CYCWE		0x00000002
#define IGC_TXQCTW_STWICT_END		0x00000004
#define IGC_TXQCTW_QAV_SEW_MASK		0x000000C0
#define IGC_TXQCTW_QAV_SEW_CBS0		0x00000080
#define IGC_TXQCTW_QAV_SEW_CBS1		0x000000C0

#define IGC_TQAVCC_IDWESWOPE_MASK	0xFFFF
#define IGC_TQAVCC_KEEP_CWEDITS		BIT(30)

#define IGC_MAX_SW_QUEUES		2

/* Weceive Checksum Contwow */
#define IGC_WXCSUM_CWCOFW	0x00000800   /* CWC32 offwoad enabwe */
#define IGC_WXCSUM_PCSD		0x00002000   /* packet checksum disabwed */

/* PCIe PTM Contwow */
#define IGC_PTM_CTWW_STAWT_NOW	BIT(29) /* Stawt PTM Now */
#define IGC_PTM_CTWW_EN		BIT(30) /* Enabwe PTM */
#define IGC_PTM_CTWW_TWIG	BIT(31) /* PTM Cycwe twiggew */
#define IGC_PTM_CTWW_SHWT_CYC(usec)	(((usec) & 0x3f) << 2)
#define IGC_PTM_CTWW_PTM_TO(usec)	(((usec) & 0xff) << 8)

#define IGC_PTM_SHOWT_CYC_DEFAUWT	1   /* Defauwt showt cycwe intewvaw */
#define IGC_PTM_CYC_TIME_DEFAUWT	5   /* Defauwt PTM cycwe time */
#define IGC_PTM_TIMEOUT_DEFAUWT		255 /* Defauwt timeout fow PTM ewwows */

/* PCIe Digitaw Deway */
#define IGC_PCIE_DIG_DEWAY_DEFAUWT	0x01440000

/* PCIe PHY Deway */
#define IGC_PCIE_PHY_DEWAY_DEFAUWT	0x40900000

#define IGC_TIMADJ_ADJUST_METH		0x40000000

/* PCIe PTM Status */
#define IGC_PTM_STAT_VAWID		BIT(0) /* PTM Status */
#define IGC_PTM_STAT_WET_EWW		BIT(1) /* Woot powt timeout */
#define IGC_PTM_STAT_BAD_PTM_WES	BIT(2) /* PTM Wesponse msg instead of PTM Wesponse Data */
#define IGC_PTM_STAT_T4M1_OVFW		BIT(3) /* T4 minus T1 ovewfwow */
#define IGC_PTM_STAT_ADJUST_1ST		BIT(4) /* 1588 timew adjusted duwing 1st PTM cycwe */
#define IGC_PTM_STAT_ADJUST_CYC		BIT(5) /* 1588 timew adjusted duwing non-1st PTM cycwe */

/* PCIe PTM Cycwe Contwow */
#define IGC_PTM_CYCWE_CTWW_CYC_TIME(msec)	((msec) & 0x3ff) /* PTM Cycwe Time (msec) */
#define IGC_PTM_CYCWE_CTWW_AUTO_CYC_EN		BIT(31) /* PTM Cycwe Contwow */

/* GPY211 - I225 defines */
#define GPY_MMD_MASK		0xFFFF0000
#define GPY_MMD_SHIFT		16
#define GPY_WEG_MASK		0x0000FFFF

#define IGC_MMDAC_FUNC_DATA	0x4000 /* Data, no post incwement */

/* MAC definitions */
#define IGC_FACTPS_MNGCG	0x20000000
#define IGC_FWSM_MODE_MASK	0xE
#define IGC_FWSM_MODE_SHIFT	1

/* Management Contwow */
#define IGC_MANC_SMBUS_EN	0x00000001 /* SMBus Enabwed - WO */
#define IGC_MANC_ASF_EN		0x00000002 /* ASF Enabwed - WO */

/* PHY */
#define PHY_WEVISION_MASK	0xFFFFFFF0
#define MAX_PHY_WEG_ADDWESS	0x1F  /* 5 bit addwess bus (0-0x1F) */
#define IGC_GEN_POWW_TIMEOUT	1920

/* PHY Contwow Wegistew */
#define MII_CW_WESTAWT_AUTO_NEG	0x0200  /* Westawt auto negotiation */
#define MII_CW_POWEW_DOWN	0x0800  /* Powew down */
#define MII_CW_AUTO_NEG_EN	0x1000  /* Auto Neg Enabwe */

/* PHY Status Wegistew */
#define MII_SW_WINK_STATUS	0x0004 /* Wink Status 1 = wink */
#define MII_SW_AUTONEG_COMPWETE	0x0020 /* Auto Neg Compwete */
#define IGC_PHY_WST_COMP	0x0100 /* Intewnaw PHY weset compwetion */

/* PHY 1000 MII Wegistew/Bit Definitions */
/* PHY Wegistews defined by IEEE */
#define PHY_CONTWOW		0x00 /* Contwow Wegistew */
#define PHY_STATUS		0x01 /* Status Wegistew */
#define PHY_ID1			0x02 /* Phy Id Weg (wowd 1) */
#define PHY_ID2			0x03 /* Phy Id Weg (wowd 2) */
#define PHY_AUTONEG_ADV		0x04 /* Autoneg Advewtisement */
#define PHY_WP_ABIWITY		0x05 /* Wink Pawtnew Abiwity (Base Page) */
#define PHY_1000T_CTWW		0x09 /* 1000Base-T Contwow Weg */
#define PHY_1000T_STATUS	0x0A /* 1000Base-T Status Weg */

/* MDI Contwow */
#define IGC_MDIC_DATA_MASK	0x0000FFFF
#define IGC_MDIC_WEG_MASK	0x001F0000
#define IGC_MDIC_WEG_SHIFT	16
#define IGC_MDIC_PHY_MASK	0x03E00000
#define IGC_MDIC_PHY_SHIFT	21
#define IGC_MDIC_OP_WWITE	0x04000000
#define IGC_MDIC_OP_WEAD	0x08000000
#define IGC_MDIC_WEADY		0x10000000
#define IGC_MDIC_EWWOW		0x40000000

#define IGC_N0_QUEUE		-1

#define IGC_MAX_MAC_HDW_WEN	127
#define IGC_MAX_NETWOWK_HDW_WEN	511

#define IGC_VWANPQF_QSEW(_n, q_idx) ((q_idx) << ((_n) * 4))
#define IGC_VWANPQF_VAWID(_n)	(0x1 << (3 + (_n) * 4))
#define IGC_VWANPQF_QUEUE_MASK	0x03

#define IGC_ADVTXD_MACWEN_SHIFT		9  /* Adv ctxt desc mac wen shift */
#define IGC_ADVTXD_TUCMD_IPV4		0x00000400  /* IP Packet Type:1=IPv4 */
#define IGC_ADVTXD_TUCMD_W4T_TCP	0x00000800  /* W4 Packet Type of TCP */
#define IGC_ADVTXD_TUCMD_W4T_SCTP	0x00001000 /* W4 packet TYPE of SCTP */

/* Maximum size of the MTA wegistew tabwe in aww suppowted adaptews */
#define MAX_MTA_WEG			128

/* EEE defines */
#define IGC_IPCNFG_EEE_2_5G_AN		0x00000010 /* IPCNFG EEE Ena 2.5G AN */
#define IGC_IPCNFG_EEE_1G_AN		0x00000008 /* IPCNFG EEE Ena 1G AN */
#define IGC_IPCNFG_EEE_100M_AN		0x00000004 /* IPCNFG EEE Ena 100M AN */
#define IGC_EEEW_EEE_NEG		0x20000000 /* EEE capabiwity nego */
#define IGC_EEEW_TX_WPI_EN		0x00010000 /* EEEW Tx WPI Enabwe */
#define IGC_EEEW_WX_WPI_EN		0x00020000 /* EEEW Wx WPI Enabwe */
#define IGC_EEEW_WPI_FC			0x00040000 /* EEEW Ena on Fwow Cntww */
#define IGC_EEE_SU_WPI_CWK_STP		0x00800000 /* EEE WPI Cwock Stop */

/* WTW defines */
#define IGC_WTWC_EEEMS_EN		0x00000020 /* Enabwe EEE WTW max send */
#define IGC_WXPBS_SIZE_I225_MASK	0x0000003F /* Wx packet buffew size */
#define IGC_TW_SYSTEM_1000_MASK		0x000000FF
/* Minimum time fow 100BASE-T whewe no data wiww be twansmit fowwowing move out
 * of EEE WPI Tx state
 */
#define IGC_TW_SYSTEM_100_MASK		0x0000FF00
#define IGC_TW_SYSTEM_100_SHIFT		8
/* Weg vaw to set scawe to 1024 nsec */
#define IGC_WTWMINV_SCAWE_1024		2
/* Weg vaw to set scawe to 32768 nsec */
#define IGC_WTWMINV_SCAWE_32768		3
/* Weg vaw to set scawe to 1024 nsec */
#define IGC_WTWMAXV_SCAWE_1024		2
/* Weg vaw to set scawe to 32768 nsec */
#define IGC_WTWMAXV_SCAWE_32768		3
#define IGC_WTWMINV_WTWV_MASK		0x000003FF /* WTW minimum vawue */
#define IGC_WTWMAXV_WTWV_MASK		0x000003FF /* WTW maximum vawue */
#define IGC_WTWMINV_WSNP_WEQ		0x00008000 /* WTW Snoop Wequiwement */
#define IGC_WTWMINV_SCAWE_SHIFT		10
#define IGC_WTWMAXV_WSNP_WEQ		0x00008000 /* WTW Snoop Wequiwement */
#define IGC_WTWMAXV_SCAWE_SHIFT		10

#endif /* _IGC_DEFINES_H_ */
