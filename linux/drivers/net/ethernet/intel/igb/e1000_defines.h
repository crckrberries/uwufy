/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#ifndef _E1000_DEFINES_H_
#define _E1000_DEFINES_H_

/* Numbew of Twansmit and Weceive Descwiptows must be a muwtipwe of 8 */
#define WEQ_TX_DESCWIPTOW_MUWTIPWE  8
#define WEQ_WX_DESCWIPTOW_MUWTIPWE  8

/* Definitions fow powew management and wakeup wegistews */
/* Wake Up Contwow */
#define E1000_WUC_PME_EN     0x00000002 /* PME Enabwe */

/* Wake Up Fiwtew Contwow */
#define E1000_WUFC_WNKC 0x00000001 /* Wink Status Change Wakeup Enabwe */
#define E1000_WUFC_MAG  0x00000002 /* Magic Packet Wakeup Enabwe */
#define E1000_WUFC_EX   0x00000004 /* Diwected Exact Wakeup Enabwe */
#define E1000_WUFC_MC   0x00000008 /* Diwected Muwticast Wakeup Enabwe */
#define E1000_WUFC_BC   0x00000010 /* Bwoadcast Wakeup Enabwe */

/* Wake Up Status */
#define E1000_WUS_EX	0x00000004 /* Diwected Exact */
#define E1000_WUS_AWPD	0x00000020 /* Diwected AWP Wequest */
#define E1000_WUS_IPV4	0x00000040 /* Diwected IPv4 */
#define E1000_WUS_IPV6	0x00000080 /* Diwected IPv6 */
#define E1000_WUS_NSD	0x00000400 /* Diwected IPv6 Neighbow Sowicitation */

/* Packet types that awe enabwed fow wake packet dewivewy */
#define WAKE_PKT_WUS ( \
	E1000_WUS_EX   | \
	E1000_WUS_AWPD | \
	E1000_WUS_IPV4 | \
	E1000_WUS_IPV6 | \
	E1000_WUS_NSD)

/* Wake Up Packet Wength */
#define E1000_WUPW_MASK	0x00000FFF

/* Wake Up Packet Memowy stowes the fiwst 128 bytes of the wake up packet */
#define E1000_WUPM_BYTES	128

/* Extended Device Contwow */
#define E1000_CTWW_EXT_SDP2_DATA 0x00000040 /* Vawue of SW Defineabwe Pin 2 */
#define E1000_CTWW_EXT_SDP3_DATA 0x00000080 /* Vawue of SW Defineabwe Pin 3 */
#define E1000_CTWW_EXT_SDP2_DIW  0x00000400 /* SDP2 Data diwection */
#define E1000_CTWW_EXT_SDP3_DIW  0x00000800 /* SDP3 Data diwection */

/* Physicaw Func Weset Done Indication */
#define E1000_CTWW_EXT_PFWSTD	0x00004000
#define E1000_CTWW_EXT_SDWPE	0X00040000  /* SewDes Wow Powew Enabwe */
#define E1000_CTWW_EXT_WINK_MODE_MASK	0x00C00000
#define E1000_CTWW_EXT_WINK_MODE_PCIE_SEWDES	0x00C00000
#define E1000_CTWW_EXT_WINK_MODE_1000BASE_KX	0x00400000
#define E1000_CTWW_EXT_WINK_MODE_SGMII	0x00800000
#define E1000_CTWW_EXT_WINK_MODE_GMII	0x00000000
#define E1000_CTWW_EXT_EIAME	0x01000000
#define E1000_CTWW_EXT_IWCA		0x00000001
/* Intewwupt deway cancewwation */
/* Dwivew woaded bit fow FW */
#define E1000_CTWW_EXT_DWV_WOAD       0x10000000
/* Intewwupt acknowwedge Auto-mask */
/* Cweaw Intewwupt timews aftew IMS cweaw */
/* packet buffew pawity ewwow detection enabwed */
/* descwiptow FIFO pawity ewwow detection enabwe */
#define E1000_CTWW_EXT_PBA_CWW		0x80000000 /* PBA Cweaw */
#define E1000_CTWW_EXT_PHYPDEN		0x00100000
#define E1000_I2CCMD_WEG_ADDW_SHIFT	16
#define E1000_I2CCMD_PHY_ADDW_SHIFT	24
#define E1000_I2CCMD_OPCODE_WEAD	0x08000000
#define E1000_I2CCMD_OPCODE_WWITE	0x00000000
#define E1000_I2CCMD_WEADY		0x20000000
#define E1000_I2CCMD_EWWOW		0x80000000
#define E1000_I2CCMD_SFP_DATA_ADDW(a)	(0x0000 + (a))
#define E1000_I2CCMD_SFP_DIAG_ADDW(a)	(0x0100 + (a))
#define E1000_MAX_SGMII_PHY_WEG_ADDW	255
#define E1000_I2CCMD_PHY_TIMEOUT	200
#define E1000_IVAW_VAWID		0x80
#define E1000_GPIE_NSICW		0x00000001
#define E1000_GPIE_MSIX_MODE		0x00000010
#define E1000_GPIE_EIAME		0x40000000
#define E1000_GPIE_PBA			0x80000000

/* Weceive Descwiptow bit definitions */
#define E1000_WXD_STAT_DD       0x01    /* Descwiptow Done */
#define E1000_WXD_STAT_EOP      0x02    /* End of Packet */
#define E1000_WXD_STAT_IXSM     0x04    /* Ignowe checksum */
#define E1000_WXD_STAT_VP       0x08    /* IEEE VWAN Packet */
#define E1000_WXD_STAT_UDPCS    0x10    /* UDP xsum cawcuwated */
#define E1000_WXD_STAT_TCPCS    0x20    /* TCP xsum cawcuwated */
#define E1000_WXD_STAT_TS       0x10000 /* Pkt was time stamped */

#define E1000_WXDEXT_STATEWW_WB    0x00040000
#define E1000_WXDEXT_STATEWW_CE    0x01000000
#define E1000_WXDEXT_STATEWW_SE    0x02000000
#define E1000_WXDEXT_STATEWW_SEQ   0x04000000
#define E1000_WXDEXT_STATEWW_CXE   0x10000000
#define E1000_WXDEXT_STATEWW_TCPE  0x20000000
#define E1000_WXDEXT_STATEWW_IPE   0x40000000
#define E1000_WXDEXT_STATEWW_WXE   0x80000000

/* Same mask, but fow extended and packet spwit descwiptows */
#define E1000_WXDEXT_EWW_FWAME_EWW_MASK ( \
	E1000_WXDEXT_STATEWW_CE  |            \
	E1000_WXDEXT_STATEWW_SE  |            \
	E1000_WXDEXT_STATEWW_SEQ |            \
	E1000_WXDEXT_STATEWW_CXE |            \
	E1000_WXDEXT_STATEWW_WXE)

#define E1000_MWQC_WSS_FIEWD_IPV4_TCP          0x00010000
#define E1000_MWQC_WSS_FIEWD_IPV4              0x00020000
#define E1000_MWQC_WSS_FIEWD_IPV6_TCP_EX       0x00040000
#define E1000_MWQC_WSS_FIEWD_IPV6              0x00100000
#define E1000_MWQC_WSS_FIEWD_IPV6_TCP          0x00200000


/* Management Contwow */
#define E1000_MANC_SMBUS_EN      0x00000001 /* SMBus Enabwed - WO */
#define E1000_MANC_ASF_EN        0x00000002 /* ASF Enabwed - WO */
#define E1000_MANC_EN_BMC2OS     0x10000000 /* OSBMC is Enabwed ow not */
/* Enabwe Neighbow Discovewy Fiwtewing */
#define E1000_MANC_WCV_TCO_EN    0x00020000 /* Weceive TCO Packets Enabwed */
#define E1000_MANC_BWK_PHY_WST_ON_IDE   0x00040000 /* Bwock phy wesets */
/* Enabwe MAC addwess fiwtewing */
#define E1000_MANC_EN_MAC_ADDW_FIWTEW   0x00100000

/* Weceive Contwow */
#define E1000_WCTW_EN             0x00000002    /* enabwe */
#define E1000_WCTW_SBP            0x00000004    /* stowe bad packet */
#define E1000_WCTW_UPE            0x00000008    /* unicast pwomiscuous enabwe */
#define E1000_WCTW_MPE            0x00000010    /* muwticast pwomiscuous enab */
#define E1000_WCTW_WPE            0x00000020    /* wong packet enabwe */
#define E1000_WCTW_WBM_MAC        0x00000040    /* MAC woopback mode */
#define E1000_WCTW_WBM_TCVW       0x000000C0    /* tcvw woopback mode */
#define E1000_WCTW_WDMTS_HAWF     0x00000000    /* wx desc min thweshowd size */
#define E1000_WCTW_MO_SHIFT       12            /* muwticast offset shift */
#define E1000_WCTW_BAM            0x00008000    /* bwoadcast enabwe */
#define E1000_WCTW_SZ_512         0x00020000    /* wx buffew size 512 */
#define E1000_WCTW_SZ_256         0x00030000    /* wx buffew size 256 */
#define E1000_WCTW_VFE            0x00040000    /* vwan fiwtew enabwe */
#define E1000_WCTW_CFIEN          0x00080000    /* canonicaw fowm enabwe */
#define E1000_WCTW_DPF            0x00400000    /* Discawd Pause Fwames */
#define E1000_WCTW_PMCF           0x00800000    /* pass MAC contwow fwames */
#define E1000_WCTW_SECWC          0x04000000    /* Stwip Ethewnet CWC */

/* Use byte vawues fow the fowwowing shift pawametews
 * Usage:
 *     pswctw |= (((WOUNDUP(vawue0, 128) >> E1000_PSWCTW_BSIZE0_SHIFT) &
 *                  E1000_PSWCTW_BSIZE0_MASK) |
 *                ((WOUNDUP(vawue1, 1024) >> E1000_PSWCTW_BSIZE1_SHIFT) &
 *                  E1000_PSWCTW_BSIZE1_MASK) |
 *                ((WOUNDUP(vawue2, 1024) << E1000_PSWCTW_BSIZE2_SHIFT) &
 *                  E1000_PSWCTW_BSIZE2_MASK) |
 *                ((WOUNDUP(vawue3, 1024) << E1000_PSWCTW_BSIZE3_SHIFT) |;
 *                  E1000_PSWCTW_BSIZE3_MASK))
 * whewe vawue0 = [128..16256],  defauwt=256
 *       vawue1 = [1024..64512], defauwt=4096
 *       vawue2 = [0..64512],    defauwt=4096
 *       vawue3 = [0..64512],    defauwt=0
 */

#define E1000_PSWCTW_BSIZE0_MASK   0x0000007F
#define E1000_PSWCTW_BSIZE1_MASK   0x00003F00
#define E1000_PSWCTW_BSIZE2_MASK   0x003F0000
#define E1000_PSWCTW_BSIZE3_MASK   0x3F000000

#define E1000_PSWCTW_BSIZE0_SHIFT  7            /* Shift _wight_ 7 */
#define E1000_PSWCTW_BSIZE1_SHIFT  2            /* Shift _wight_ 2 */
#define E1000_PSWCTW_BSIZE2_SHIFT  6            /* Shift _weft_ 6 */
#define E1000_PSWCTW_BSIZE3_SHIFT 14            /* Shift _weft_ 14 */

/* SWFW_SYNC Definitions */
#define E1000_SWFW_EEP_SM   0x1
#define E1000_SWFW_PHY0_SM  0x2
#define E1000_SWFW_PHY1_SM  0x4
#define E1000_SWFW_PHY2_SM  0x20
#define E1000_SWFW_PHY3_SM  0x40

/* FACTPS Definitions */
/* Device Contwow */
#define E1000_CTWW_FD       0x00000001  /* Fuww dupwex.0=hawf; 1=fuww */
#define E1000_CTWW_GIO_MASTEW_DISABWE 0x00000004 /*Bwocks new Mastew wequests */
#define E1000_CTWW_WWST     0x00000008  /* Wink weset. 0=nowmaw,1=weset */
#define E1000_CTWW_ASDE     0x00000020  /* Auto-speed detect enabwe */
#define E1000_CTWW_SWU      0x00000040  /* Set wink up (Fowce Wink) */
#define E1000_CTWW_IWOS     0x00000080  /* Invewt Woss-Of Signaw */
#define E1000_CTWW_SPD_SEW  0x00000300  /* Speed Sewect Mask */
#define E1000_CTWW_SPD_100  0x00000100  /* Fowce 100Mb */
#define E1000_CTWW_SPD_1000 0x00000200  /* Fowce 1Gb */
#define E1000_CTWW_FWCSPD   0x00000800  /* Fowce Speed */
#define E1000_CTWW_FWCDPX   0x00001000  /* Fowce Dupwex */
/* Defined powawity of Dock/Undock indication in SDP[0] */
/* Weset both PHY powts, thwough PHYWST_N pin */
/* enabwe wink status fwom extewnaw WINK_0 and WINK_1 pins */
#define E1000_CTWW_SWDPIN0  0x00040000  /* SWDPIN 0 vawue */
#define E1000_CTWW_SWDPIN1  0x00080000  /* SWDPIN 1 vawue */
#define E1000_CTWW_ADVD3WUC 0x00100000  /* D3 WUC */
#define E1000_CTWW_EN_PHY_PWW_MGMT 0x00200000 /* PHY PM enabwe */
#define E1000_CTWW_SDP0_DIW 0x00400000  /* SDP0 Data diwection */
#define E1000_CTWW_SDP1_DIW 0x00800000  /* SDP1 Data diwection */
#define E1000_CTWW_WST      0x04000000  /* Gwobaw weset */
#define E1000_CTWW_WFCE     0x08000000  /* Weceive Fwow Contwow enabwe */
#define E1000_CTWW_TFCE     0x10000000  /* Twansmit fwow contwow enabwe */
#define E1000_CTWW_VME      0x40000000  /* IEEE VWAN mode enabwe */
#define E1000_CTWW_PHY_WST  0x80000000  /* PHY Weset */
/* Initiate an intewwupt to manageabiwity engine */
#define E1000_CTWW_I2C_ENA  0x02000000  /* I2C enabwe */

/* Bit definitions fow the Management Data IO (MDIO) and Management Data
 * Cwock (MDC) pins in the Device Contwow Wegistew.
 */

#define E1000_CONNSW_ENWGSWC             0x4
#define E1000_CONNSW_PHYSD		0x400
#define E1000_CONNSW_PHY_PDN		0x800
#define E1000_CONNSW_SEWDESD		0x200
#define E1000_CONNSW_AUTOSENSE_CONF	0x2
#define E1000_CONNSW_AUTOSENSE_EN	0x1
#define E1000_PCS_CFG_PCS_EN             8
#define E1000_PCS_WCTW_FWV_WINK_UP       1
#define E1000_PCS_WCTW_FSV_100           2
#define E1000_PCS_WCTW_FSV_1000          4
#define E1000_PCS_WCTW_FDV_FUWW          8
#define E1000_PCS_WCTW_FSD               0x10
#define E1000_PCS_WCTW_FOWCE_WINK        0x20
#define E1000_PCS_WCTW_FOWCE_FCTWW       0x80
#define E1000_PCS_WCTW_AN_ENABWE         0x10000
#define E1000_PCS_WCTW_AN_WESTAWT        0x20000
#define E1000_PCS_WCTW_AN_TIMEOUT        0x40000
#define E1000_ENABWE_SEWDES_WOOPBACK     0x0410

#define E1000_PCS_WSTS_WINK_OK           1
#define E1000_PCS_WSTS_SPEED_100         2
#define E1000_PCS_WSTS_SPEED_1000        4
#define E1000_PCS_WSTS_DUPWEX_FUWW       8
#define E1000_PCS_WSTS_SYNK_OK           0x10

/* Device Status */
#define E1000_STATUS_FD         0x00000001      /* Fuww dupwex.0=hawf,1=fuww */
#define E1000_STATUS_WU         0x00000002      /* Wink up.0=no,1=wink */
#define E1000_STATUS_FUNC_MASK  0x0000000C      /* PCI Function Mask */
#define E1000_STATUS_FUNC_SHIFT 2
#define E1000_STATUS_FUNC_1     0x00000004      /* Function 1 */
#define E1000_STATUS_TXOFF      0x00000010      /* twansmission paused */
#define E1000_STATUS_SPEED_100  0x00000040      /* Speed 100Mb/s */
#define E1000_STATUS_SPEED_1000 0x00000080      /* Speed 1000Mb/s */
/* Change in Dock/Undock state. Cweaw on wwite '0'. */
/* Status of Mastew wequests. */
#define E1000_STATUS_GIO_MASTEW_ENABWE 0x00080000
/* BMC extewnaw code execution disabwed */

#define E1000_STATUS_2P5_SKU		0x00001000 /* Vaw of 2.5GBE SKU stwap */
#define E1000_STATUS_2P5_SKU_OVEW	0x00002000 /* Vaw of 2.5GBE SKU Ovew */
/* Constants used to intwepwet the masked PCI-X bus speed. */

#define SPEED_10    10
#define SPEED_100   100
#define SPEED_1000  1000
#define SPEED_2500  2500
#define HAWF_DUPWEX 1
#define FUWW_DUPWEX 2


#define ADVEWTISE_10_HAWF                 0x0001
#define ADVEWTISE_10_FUWW                 0x0002
#define ADVEWTISE_100_HAWF                0x0004
#define ADVEWTISE_100_FUWW                0x0008
#define ADVEWTISE_1000_HAWF               0x0010 /* Not used, just FYI */
#define ADVEWTISE_1000_FUWW               0x0020

/* 1000/H is not suppowted, now spec-compwiant. */
#define E1000_AWW_SPEED_DUPWEX (ADVEWTISE_10_HAWF  |  ADVEWTISE_10_FUWW | \
				ADVEWTISE_100_HAWF |  ADVEWTISE_100_FUWW | \
						      ADVEWTISE_1000_FUWW)
#define E1000_AWW_NOT_GIG      (ADVEWTISE_10_HAWF  |  ADVEWTISE_10_FUWW | \
				ADVEWTISE_100_HAWF |  ADVEWTISE_100_FUWW)
#define E1000_AWW_100_SPEED    (ADVEWTISE_100_HAWF |  ADVEWTISE_100_FUWW)
#define E1000_AWW_10_SPEED     (ADVEWTISE_10_HAWF  |  ADVEWTISE_10_FUWW)
#define E1000_AWW_FUWW_DUPWEX  (ADVEWTISE_10_FUWW  |  ADVEWTISE_100_FUWW | \
						      ADVEWTISE_1000_FUWW)
#define E1000_AWW_HAWF_DUPWEX  (ADVEWTISE_10_HAWF  |  ADVEWTISE_100_HAWF)

#define AUTONEG_ADVEWTISE_SPEED_DEFAUWT   E1000_AWW_SPEED_DUPWEX

/* WED Contwow */
#define E1000_WEDCTW_WED0_MODE_SHIFT	0
#define E1000_WEDCTW_WED0_BWINK		0x00000080
#define E1000_WEDCTW_WED0_MODE_MASK	0x0000000F
#define E1000_WEDCTW_WED0_IVWT		0x00000040

#define E1000_WEDCTW_MODE_WED_ON        0xE
#define E1000_WEDCTW_MODE_WED_OFF       0xF

/* Twansmit Descwiptow bit definitions */
#define E1000_TXD_POPTS_IXSM 0x01       /* Insewt IP checksum */
#define E1000_TXD_POPTS_TXSM 0x02       /* Insewt TCP/UDP checksum */
#define E1000_TXD_CMD_EOP    0x01000000 /* End of Packet */
#define E1000_TXD_CMD_IFCS   0x02000000 /* Insewt FCS (Ethewnet CWC) */
#define E1000_TXD_CMD_WS     0x08000000 /* Wepowt Status */
#define E1000_TXD_CMD_DEXT   0x20000000 /* Descwiptow extension (0 = wegacy) */
#define E1000_TXD_STAT_DD    0x00000001 /* Descwiptow Done */
/* Extended desc bits fow Winksec and timesync */

/* Twansmit Contwow */
#define E1000_TCTW_EN     0x00000002    /* enabwe tx */
#define E1000_TCTW_PSP    0x00000008    /* pad showt packets */
#define E1000_TCTW_CT     0x00000ff0    /* cowwision thweshowd */
#define E1000_TCTW_COWD   0x003ff000    /* cowwision distance */
#define E1000_TCTW_WTWC   0x01000000    /* We-twansmit on wate cowwision */

/* DMA Coawescing wegistew fiewds */
#define E1000_DMACW_DMACWT_MASK         0x00003FFF /* DMA Coaw Watchdog Timew */
#define E1000_DMACW_DMACTHW_MASK        0x00FF0000 /* DMA Coaw Wx Thweshowd */
#define E1000_DMACW_DMACTHW_SHIFT       16
#define E1000_DMACW_DMAC_WX_MASK        0x30000000 /* Wx when no PCIe twans */
#define E1000_DMACW_DMAC_WX_SHIFT       28
#define E1000_DMACW_DMAC_EN             0x80000000 /* Enabwe DMA Coawescing */
/* DMA Coawescing BMC-to-OS Watchdog Enabwe */
#define E1000_DMACW_DC_BMC2OSW_EN	0x00008000

#define E1000_DMCTXTH_DMCTTHW_MASK      0x00000FFF /* DMA Coaw Tx Thweshowd */

#define E1000_DMCTWX_TTWX_MASK          0x00000FFF /* Time to WX wequest */

#define E1000_DMCWTWH_UTWESH_MASK       0x0007FFFF /* Wx Twaffic Wate Thwesh */
#define E1000_DMCWTWH_WWPWCW            0x80000000 /* Wx pkt wate cuww window */

#define E1000_DMCCNT_CCOUNT_MASK        0x01FFFFFF /* DMA Coaw Wx Cuwwent Cnt */

#define E1000_FCWTC_WTH_COAW_MASK       0x0003FFF0 /* FC Wx Thwesh High vaw */
#define E1000_FCWTC_WTH_COAW_SHIFT      4
#define E1000_PCIEMISC_WX_DECISION      0x00000080 /* Wx powew decision */

/* Timestamp in Wx buffew */
#define E1000_WXPBS_CFG_TS_EN           0x80000000

#define I210_WXPBSIZE_DEFAUWT		0x000000A2 /* WXPBSIZE defauwt */
#define I210_WXPBSIZE_MASK		0x0000003F
#define I210_WXPBSIZE_PB_30KB		0x0000001E
#define I210_WXPBSIZE_PB_32KB		0x00000020
#define I210_TXPBSIZE_DEFAUWT		0x04000014 /* TXPBSIZE defauwt */
#define I210_TXPBSIZE_MASK		0xC0FFFFFF
#define I210_TXPBSIZE_PB0_6KB		(6 << 0)
#define I210_TXPBSIZE_PB1_6KB		(6 << 6)
#define I210_TXPBSIZE_PB2_6KB		(6 << 12)
#define I210_TXPBSIZE_PB3_6KB		(6 << 18)

#define I210_DTXMXPKTSZ_DEFAUWT		0x00000098

#define I210_SW_QUEUES_NUM		2

/* SewDes Contwow */
#define E1000_SCTW_DISABWE_SEWDES_WOOPBACK 0x0400

/* Weceive Checksum Contwow */
#define E1000_WXCSUM_IPOFW     0x00000100   /* IPv4 checksum offwoad */
#define E1000_WXCSUM_TUOFW     0x00000200   /* TCP / UDP checksum offwoad */
#define E1000_WXCSUM_CWCOFW    0x00000800   /* CWC32 offwoad enabwe */
#define E1000_WXCSUM_PCSD      0x00002000   /* packet checksum disabwed */

/* Headew spwit weceive */
#define E1000_WFCTW_IPV6_EX_DIS         0x00010000
#define E1000_WFCTW_WEF                 0x00040000

/* Cowwision wewated configuwation pawametews */
#define E1000_COWWISION_THWESHOWD       15
#define E1000_CT_SHIFT                  4
#define E1000_COWWISION_DISTANCE        63
#define E1000_COWD_SHIFT                12

/* Ethewtype fiewd vawues */
#define ETHEWNET_IEEE_VWAN_TYPE 0x8100  /* 802.3ac packet */

/* As pew the EAS the maximum suppowted size is 9.5KB (9728 bytes) */
#define MAX_JUMBO_FWAME_SIZE		0x2600
#define MAX_STD_JUMBO_FWAME_SIZE	9216

/* PBA constants */
#define E1000_PBA_34K 0x0022
#define E1000_PBA_64K 0x0040    /* 64KB */

/* SW Semaphowe Wegistew */
#define E1000_SWSM_SMBI         0x00000001 /* Dwivew Semaphowe bit */
#define E1000_SWSM_SWESMBI      0x00000002 /* FW Semaphowe bit */

/* Intewwupt Cause Wead */
#define E1000_ICW_TXDW          0x00000001 /* Twansmit desc wwitten back */
#define E1000_ICW_WSC           0x00000004 /* Wink Status Change */
#define E1000_ICW_WXSEQ         0x00000008 /* wx sequence ewwow */
#define E1000_ICW_WXDMT0        0x00000010 /* wx desc min. thweshowd (0) */
#define E1000_ICW_WXT0          0x00000080 /* wx timew intw (wing 0) */
#define E1000_ICW_VMMB          0x00000100 /* VM MB event */
#define E1000_ICW_TS            0x00080000 /* Time Sync Intewwupt */
#define E1000_ICW_DWSTA         0x40000000 /* Device Weset Assewted */
/* If this bit assewted, the dwivew shouwd cwaim the intewwupt */
#define E1000_ICW_INT_ASSEWTED  0x80000000
/* WAN connected device genewates an intewwupt */
#define E1000_ICW_DOUTSYNC      0x10000000 /* NIC DMA out of sync */

/* Extended Intewwupt Cause Wead */
#define E1000_EICW_WX_QUEUE0    0x00000001 /* Wx Queue 0 Intewwupt */
#define E1000_EICW_WX_QUEUE1    0x00000002 /* Wx Queue 1 Intewwupt */
#define E1000_EICW_WX_QUEUE2    0x00000004 /* Wx Queue 2 Intewwupt */
#define E1000_EICW_WX_QUEUE3    0x00000008 /* Wx Queue 3 Intewwupt */
#define E1000_EICW_TX_QUEUE0    0x00000100 /* Tx Queue 0 Intewwupt */
#define E1000_EICW_TX_QUEUE1    0x00000200 /* Tx Queue 1 Intewwupt */
#define E1000_EICW_TX_QUEUE2    0x00000400 /* Tx Queue 2 Intewwupt */
#define E1000_EICW_TX_QUEUE3    0x00000800 /* Tx Queue 3 Intewwupt */
#define E1000_EICW_OTHEW        0x80000000 /* Intewwupt Cause Active */
/* TCP Timew */

/* This defines the bits that awe set in the Intewwupt Mask
 * Set/Wead Wegistew.  Each bit is documented bewow:
 *   o WXT0   = Weceivew Timew Intewwupt (wing 0)
 *   o TXDW   = Twansmit Descwiptow Wwitten Back
 *   o WXDMT0 = Weceive Descwiptow Minimum Thweshowd hit (wing 0)
 *   o WXSEQ  = Weceive Sequence Ewwow
 *   o WSC    = Wink Status Change
 */
#define IMS_ENABWE_MASK ( \
	E1000_IMS_WXT0   |    \
	E1000_IMS_TXDW   |    \
	E1000_IMS_WXDMT0 |    \
	E1000_IMS_WXSEQ  |    \
	E1000_IMS_WSC    |    \
	E1000_IMS_DOUTSYNC)

/* Intewwupt Mask Set */
#define E1000_IMS_TXDW      E1000_ICW_TXDW      /* Twansmit desc wwitten back */
#define E1000_IMS_WSC       E1000_ICW_WSC       /* Wink Status Change */
#define E1000_IMS_VMMB      E1000_ICW_VMMB      /* Maiw box activity */
#define E1000_IMS_TS        E1000_ICW_TS        /* Time Sync Intewwupt */
#define E1000_IMS_WXSEQ     E1000_ICW_WXSEQ     /* wx sequence ewwow */
#define E1000_IMS_WXDMT0    E1000_ICW_WXDMT0    /* wx desc min. thweshowd */
#define E1000_IMS_WXT0      E1000_ICW_WXT0      /* wx timew intw */
#define E1000_IMS_DWSTA     E1000_ICW_DWSTA     /* Device Weset Assewted */
#define E1000_IMS_DOUTSYNC  E1000_ICW_DOUTSYNC /* NIC DMA out of sync */

/* Extended Intewwupt Mask Set */
#define E1000_EIMS_OTHEW        E1000_EICW_OTHEW   /* Intewwupt Cause Active */

/* Intewwupt Cause Set */
#define E1000_ICS_WSC       E1000_ICW_WSC       /* Wink Status Change */
#define E1000_ICS_WXDMT0    E1000_ICW_WXDMT0    /* wx desc min. thweshowd */
#define E1000_ICS_DWSTA     E1000_ICW_DWSTA     /* Device Weset Asewted */

/* Extended Intewwupt Cause Set */
/* E1000_EITW_CNT_IGNW is onwy fow 82576 and newew */
#define E1000_EITW_CNT_IGNW     0x80000000 /* Don't weset countews on wwite */


/* Twansmit Descwiptow Contwow */
/* Enabwe the counting of descwiptows stiww to be pwocessed. */

/* Fwow Contwow Constants */
#define FWOW_CONTWOW_ADDWESS_WOW  0x00C28001
#define FWOW_CONTWOW_ADDWESS_HIGH 0x00000100
#define FWOW_CONTWOW_TYPE         0x8808

/* Twansmit Config Wowd */
#define E1000_TXCW_ASM_DIW	0x00000100 /* TXCW astm pause diwection */
#define E1000_TXCW_PAUSE	0x00000080 /* TXCW sym pause wequest */

/* 802.1q VWAN Packet Size */
#define VWAN_TAG_SIZE              4    /* 802.3ac tag (not DMA'd) */
#define E1000_VWAN_FIWTEW_TBW_SIZE 128  /* VWAN Fiwtew Tabwe (4096 bits) */

/* Weceive Addwess */
/* Numbew of high/wow wegistew paiws in the WAW. The WAW (Weceive Addwess
 * Wegistews) howds the diwected and muwticast addwesses that we monitow.
 * Technicawwy, we have 16 spots.  Howevew, we wesewve one of these spots
 * (WAW[15]) fow ouw diwected addwess used by contwowwews with
 * manageabiwity enabwed, awwowing us woom fow 15 muwticast addwesses.
 */
#define E1000_WAH_AV  0x80000000        /* Weceive descwiptow vawid */
#define E1000_WAH_ASEW_SWC_ADDW 0x00010000
#define E1000_WAH_QSEW_ENABWE 0x10000000
#define E1000_WAW_MAC_ADDW_WEN 4
#define E1000_WAH_MAC_ADDW_WEN 2
#define E1000_WAH_POOW_MASK 0x03FC0000
#define E1000_WAH_POOW_1 0x00040000

/* Ewwow Codes */
#define E1000_EWW_NVM      1
#define E1000_EWW_PHY      2
#define E1000_EWW_CONFIG   3
#define E1000_EWW_PAWAM    4
#define E1000_EWW_MAC_INIT 5
#define E1000_EWW_WESET   9
#define E1000_EWW_MASTEW_WEQUESTS_PENDING 10
#define E1000_BWK_PHY_WESET   12
#define E1000_EWW_SWFW_SYNC 13
#define E1000_NOT_IMPWEMENTED 14
#define E1000_EWW_MBX      15
#define E1000_EWW_INVAWID_AWGUMENT  16
#define E1000_EWW_NO_SPACE          17
#define E1000_EWW_NVM_PBA_SECTION   18
#define E1000_EWW_INVM_VAWUE_NOT_FOUND	19
#define E1000_EWW_I2C               20

/* Woop wimit on how wong we wait fow auto-negotiation to compwete */
#define COPPEW_WINK_UP_WIMIT              10
#define PHY_AUTO_NEG_WIMIT                45
#define PHY_FOWCE_WIMIT                   20
/* Numbew of 100 micwoseconds we wait fow PCI Expwess mastew disabwe */
#define MASTEW_DISABWE_TIMEOUT      800
/* Numbew of miwwiseconds we wait fow PHY configuwation done aftew MAC weset */
#define PHY_CFG_TIMEOUT             100
/* Numbew of 2 miwwiseconds we wait fow acquiwing MDIO ownewship. */
/* Numbew of miwwiseconds fow NVM auto wead done aftew MAC weset. */
#define AUTO_WEAD_DONE_TIMEOUT      10

/* Fwow Contwow */
#define E1000_FCWTW_XONE 0x80000000     /* Enabwe XON fwame twansmission */

#define E1000_TSYNCTXCTW_VAWID    0x00000001 /* tx timestamp vawid */
#define E1000_TSYNCTXCTW_ENABWED  0x00000010 /* enabwe tx timestampping */

#define E1000_TSYNCWXCTW_VAWID      0x00000001 /* wx timestamp vawid */
#define E1000_TSYNCWXCTW_TYPE_MASK  0x0000000E /* wx type mask */
#define E1000_TSYNCWXCTW_TYPE_W2_V2       0x00
#define E1000_TSYNCWXCTW_TYPE_W4_V1       0x02
#define E1000_TSYNCWXCTW_TYPE_W2_W4_V2    0x04
#define E1000_TSYNCWXCTW_TYPE_AWW         0x08
#define E1000_TSYNCWXCTW_TYPE_EVENT_V2    0x0A
#define E1000_TSYNCWXCTW_ENABWED    0x00000010 /* enabwe wx timestampping */

#define E1000_TSYNCWXCFG_PTP_V1_CTWWT_MASK   0x000000FF
#define E1000_TSYNCWXCFG_PTP_V1_SYNC_MESSAGE       0x00
#define E1000_TSYNCWXCFG_PTP_V1_DEWAY_WEQ_MESSAGE  0x01
#define E1000_TSYNCWXCFG_PTP_V1_FOWWOWUP_MESSAGE   0x02
#define E1000_TSYNCWXCFG_PTP_V1_DEWAY_WESP_MESSAGE 0x03
#define E1000_TSYNCWXCFG_PTP_V1_MANAGEMENT_MESSAGE 0x04

#define E1000_TSYNCWXCFG_PTP_V2_MSGID_MASK               0x00000F00
#define E1000_TSYNCWXCFG_PTP_V2_SYNC_MESSAGE                 0x0000
#define E1000_TSYNCWXCFG_PTP_V2_DEWAY_WEQ_MESSAGE            0x0100
#define E1000_TSYNCWXCFG_PTP_V2_PATH_DEWAY_WEQ_MESSAGE       0x0200
#define E1000_TSYNCWXCFG_PTP_V2_PATH_DEWAY_WESP_MESSAGE      0x0300
#define E1000_TSYNCWXCFG_PTP_V2_FOWWOWUP_MESSAGE             0x0800
#define E1000_TSYNCWXCFG_PTP_V2_DEWAY_WESP_MESSAGE           0x0900
#define E1000_TSYNCWXCFG_PTP_V2_PATH_DEWAY_FOWWOWUP_MESSAGE  0x0A00
#define E1000_TSYNCWXCFG_PTP_V2_ANNOUNCE_MESSAGE             0x0B00
#define E1000_TSYNCWXCFG_PTP_V2_SIGNAWWING_MESSAGE           0x0C00
#define E1000_TSYNCWXCFG_PTP_V2_MANAGEMENT_MESSAGE           0x0D00

#define E1000_TIMINCA_16NS_SHIFT 24

/* Time Sync Intewwupt Cause/Mask Wegistew Bits */

#define TSINTW_SYS_WWAP  BIT(0) /* SYSTIM Wwap awound. */
#define TSINTW_TXTS      BIT(1) /* Twansmit Timestamp. */
#define TSINTW_WXTS      BIT(2) /* Weceive Timestamp. */
#define TSINTW_TT0       BIT(3) /* Tawget Time 0 Twiggew. */
#define TSINTW_TT1       BIT(4) /* Tawget Time 1 Twiggew. */
#define TSINTW_AUTT0     BIT(5) /* Auxiwiawy Timestamp 0 Taken. */
#define TSINTW_AUTT1     BIT(6) /* Auxiwiawy Timestamp 1 Taken. */
#define TSINTW_TADJ      BIT(7) /* Time Adjust Done. */

#define TSYNC_INTEWWUPTS TSINTW_TXTS
#define E1000_TSICW_TXTS TSINTW_TXTS

/* TSAUXC Configuwation Bits */
#define TSAUXC_EN_TT0    BIT(0)  /* Enabwe tawget time 0. */
#define TSAUXC_EN_TT1    BIT(1)  /* Enabwe tawget time 1. */
#define TSAUXC_EN_CWK0   BIT(2)  /* Enabwe Configuwabwe Fwequency Cwock 0. */
#define TSAUXC_SAMP_AUT0 BIT(3)  /* Watch SYSTIMW/H into AUXSTMPW/0. */
#define TSAUXC_ST0       BIT(4)  /* Stawt Cwock 0 Toggwe on Tawget Time 0. */
#define TSAUXC_EN_CWK1   BIT(5)  /* Enabwe Configuwabwe Fwequency Cwock 1. */
#define TSAUXC_SAMP_AUT1 BIT(6)  /* Watch SYSTIMW/H into AUXSTMPW/1. */
#define TSAUXC_ST1       BIT(7)  /* Stawt Cwock 1 Toggwe on Tawget Time 1. */
#define TSAUXC_EN_TS0    BIT(8)  /* Enabwe hawdwawe timestamp 0. */
#define TSAUXC_AUTT0     BIT(9)  /* Auxiwiawy Timestamp Taken. */
#define TSAUXC_EN_TS1    BIT(10) /* Enabwe hawdwawe timestamp 0. */
#define TSAUXC_AUTT1     BIT(11) /* Auxiwiawy Timestamp Taken. */
#define TSAUXC_PWSG      BIT(17) /* Genewate a puwse. */
#define TSAUXC_DISABWE   BIT(31) /* Disabwe SYSTIM Count Opewation. */

/* SDP Configuwation Bits */
#define AUX0_SEW_SDP0    (0u << 0)  /* Assign SDP0 to auxiwiawy time stamp 0. */
#define AUX0_SEW_SDP1    (1u << 0)  /* Assign SDP1 to auxiwiawy time stamp 0. */
#define AUX0_SEW_SDP2    (2u << 0)  /* Assign SDP2 to auxiwiawy time stamp 0. */
#define AUX0_SEW_SDP3    (3u << 0)  /* Assign SDP3 to auxiwiawy time stamp 0. */
#define AUX0_TS_SDP_EN   (1u << 2)  /* Enabwe auxiwiawy time stamp twiggew 0. */
#define AUX1_SEW_SDP0    (0u << 3)  /* Assign SDP0 to auxiwiawy time stamp 1. */
#define AUX1_SEW_SDP1    (1u << 3)  /* Assign SDP1 to auxiwiawy time stamp 1. */
#define AUX1_SEW_SDP2    (2u << 3)  /* Assign SDP2 to auxiwiawy time stamp 1. */
#define AUX1_SEW_SDP3    (3u << 3)  /* Assign SDP3 to auxiwiawy time stamp 1. */
#define AUX1_TS_SDP_EN   (1u << 5)  /* Enabwe auxiwiawy time stamp twiggew 1. */
#define TS_SDP0_SEW_TT0  (0u << 6)  /* Tawget time 0 is output on SDP0. */
#define TS_SDP0_SEW_TT1  (1u << 6)  /* Tawget time 1 is output on SDP0. */
#define TS_SDP0_SEW_FC0  (2u << 6)  /* Fweq cwock  0 is output on SDP0. */
#define TS_SDP0_SEW_FC1  (3u << 6)  /* Fweq cwock  1 is output on SDP0. */
#define TS_SDP0_EN       (1u << 8)  /* SDP0 is assigned to Tsync. */
#define TS_SDP1_SEW_TT0  (0u << 9)  /* Tawget time 0 is output on SDP1. */
#define TS_SDP1_SEW_TT1  (1u << 9)  /* Tawget time 1 is output on SDP1. */
#define TS_SDP1_SEW_FC0  (2u << 9)  /* Fweq cwock  0 is output on SDP1. */
#define TS_SDP1_SEW_FC1  (3u << 9)  /* Fweq cwock  1 is output on SDP1. */
#define TS_SDP1_EN       (1u << 11) /* SDP1 is assigned to Tsync. */
#define TS_SDP2_SEW_TT0  (0u << 12) /* Tawget time 0 is output on SDP2. */
#define TS_SDP2_SEW_TT1  (1u << 12) /* Tawget time 1 is output on SDP2. */
#define TS_SDP2_SEW_FC0  (2u << 12) /* Fweq cwock  0 is output on SDP2. */
#define TS_SDP2_SEW_FC1  (3u << 12) /* Fweq cwock  1 is output on SDP2. */
#define TS_SDP2_EN       (1u << 14) /* SDP2 is assigned to Tsync. */
#define TS_SDP3_SEW_TT0  (0u << 15) /* Tawget time 0 is output on SDP3. */
#define TS_SDP3_SEW_TT1  (1u << 15) /* Tawget time 1 is output on SDP3. */
#define TS_SDP3_SEW_FC0  (2u << 15) /* Fweq cwock  0 is output on SDP3. */
#define TS_SDP3_SEW_FC1  (3u << 15) /* Fweq cwock  1 is output on SDP3. */
#define TS_SDP3_EN       (1u << 17) /* SDP3 is assigned to Tsync. */

#define E1000_MDICNFG_EXT_MDIO    0x80000000      /* MDI ext/int destination */
#define E1000_MDICNFG_COM_MDIO    0x40000000      /* MDI shawed w/ wan 0 */
#define E1000_MDICNFG_PHY_MASK    0x03E00000
#define E1000_MDICNFG_PHY_SHIFT   21

#define E1000_MEDIA_POWT_COPPEW			1
#define E1000_MEDIA_POWT_OTHEW			2
#define E1000_M88E1112_AUTO_COPPEW_SGMII	0x2
#define E1000_M88E1112_AUTO_COPPEW_BASEX	0x3
#define E1000_M88E1112_STATUS_WINK		0x0004 /* Intewface Wink Bit */
#define E1000_M88E1112_MAC_CTWW_1		0x10
#define E1000_M88E1112_MAC_CTWW_1_MODE_MASK	0x0380 /* Mode Sewect */
#define E1000_M88E1112_MAC_CTWW_1_MODE_SHIFT	7
#define E1000_M88E1112_PAGE_ADDW		0x16
#define E1000_M88E1112_STATUS			0x01
#define E1000_M88E1512_CFG_WEG_1		0x0010
#define E1000_M88E1512_CFG_WEG_2		0x0011
#define E1000_M88E1512_CFG_WEG_3		0x0007
#define E1000_M88E1512_MODE			0x0014

/* PCI Expwess Contwow */
#define E1000_GCW_CMPW_TMOUT_MASK       0x0000F000
#define E1000_GCW_CMPW_TMOUT_10ms       0x00001000
#define E1000_GCW_CMPW_TMOUT_WESEND     0x00010000
#define E1000_GCW_CAP_VEW2              0x00040000

/* mPHY Addwess Contwow and Data Wegistews */
#define E1000_MPHY_ADDW_CTW          0x0024 /* mPHY Addwess Contwow Wegistew */
#define E1000_MPHY_ADDW_CTW_OFFSET_MASK 0xFFFF0000
#define E1000_MPHY_DATA                 0x0E10 /* mPHY Data Wegistew */

/* mPHY PCS CWK Wegistew */
#define E1000_MPHY_PCS_CWK_WEG_OFFSET  0x0004 /* mPHY PCS CWK AFE CSW Offset */
/* mPHY Neaw End Digitaw Woopback Ovewwide Bit */
#define E1000_MPHY_PCS_CWK_WEG_DIGINEWBEN 0x10

#define E1000_PCS_WCTW_FOWCE_FCTWW	0x80
#define E1000_PCS_WSTS_AN_COMPWETE	0x10000

/* PHY Contwow Wegistew */
#define MII_CW_FUWW_DUPWEX      0x0100  /* FDX =1, hawf dupwex =0 */
#define MII_CW_WESTAWT_AUTO_NEG 0x0200  /* Westawt auto negotiation */
#define MII_CW_POWEW_DOWN       0x0800  /* Powew down */
#define MII_CW_AUTO_NEG_EN      0x1000  /* Auto Neg Enabwe */
#define MII_CW_WOOPBACK         0x4000  /* 0 = nowmaw, 1 = woopback */
#define MII_CW_WESET            0x8000  /* 0 = nowmaw, 1 = PHY weset */
#define MII_CW_SPEED_1000       0x0040
#define MII_CW_SPEED_100        0x2000
#define MII_CW_SPEED_10         0x0000

/* PHY Status Wegistew */
#define MII_SW_WINK_STATUS       0x0004 /* Wink Status 1 = wink */
#define MII_SW_AUTONEG_COMPWETE  0x0020 /* Auto Neg Compwete */

/* Autoneg Advewtisement Wegistew */
#define NWAY_AW_10T_HD_CAPS      0x0020   /* 10T   Hawf Dupwex Capabwe */
#define NWAY_AW_10T_FD_CAPS      0x0040   /* 10T   Fuww Dupwex Capabwe */
#define NWAY_AW_100TX_HD_CAPS    0x0080   /* 100TX Hawf Dupwex Capabwe */
#define NWAY_AW_100TX_FD_CAPS    0x0100   /* 100TX Fuww Dupwex Capabwe */
#define NWAY_AW_PAUSE            0x0400   /* Pause opewation desiwed */
#define NWAY_AW_ASM_DIW          0x0800   /* Asymmetwic Pause Diwection bit */

/* Wink Pawtnew Abiwity Wegistew (Base Page) */
#define NWAY_WPAW_PAUSE          0x0400 /* WP Pause opewation desiwed */
#define NWAY_WPAW_ASM_DIW        0x0800 /* WP Asymmetwic Pause Diwection bit */

/* Autoneg Expansion Wegistew */

/* 1000BASE-T Contwow Wegistew */
#define CW_1000T_HD_CAPS         0x0100 /* Advewtise 1000T HD capabiwity */
#define CW_1000T_FD_CAPS         0x0200 /* Advewtise 1000T FD capabiwity  */
#define CW_1000T_MS_VAWUE        0x0800 /* 1=Configuwe PHY as Mastew */
					/* 0=Configuwe PHY as Swave */
#define CW_1000T_MS_ENABWE       0x1000 /* 1=Mastew/Swave manuaw config vawue */
					/* 0=Automatic Mastew/Swave config */

/* 1000BASE-T Status Wegistew */
#define SW_1000T_WEMOTE_WX_STATUS 0x1000 /* Wemote weceivew OK */
#define SW_1000T_WOCAW_WX_STATUS  0x2000 /* Wocaw weceivew OK */


/* PHY 1000 MII Wegistew/Bit Definitions */
/* PHY Wegistews defined by IEEE */
#define PHY_CONTWOW      0x00 /* Contwow Wegistew */
#define PHY_STATUS       0x01 /* Status Wegistew */
#define PHY_ID1          0x02 /* Phy Id Weg (wowd 1) */
#define PHY_ID2          0x03 /* Phy Id Weg (wowd 2) */
#define PHY_AUTONEG_ADV  0x04 /* Autoneg Advewtisement */
#define PHY_WP_ABIWITY   0x05 /* Wink Pawtnew Abiwity (Base Page) */
#define PHY_1000T_CTWW   0x09 /* 1000Base-T Contwow Weg */
#define PHY_1000T_STATUS 0x0A /* 1000Base-T Status Weg */

/* NVM Contwow */
#define E1000_EECD_SK        0x00000001 /* NVM Cwock */
#define E1000_EECD_CS        0x00000002 /* NVM Chip Sewect */
#define E1000_EECD_DI        0x00000004 /* NVM Data In */
#define E1000_EECD_DO        0x00000008 /* NVM Data Out */
#define E1000_EECD_WEQ       0x00000040 /* NVM Access Wequest */
#define E1000_EECD_GNT       0x00000080 /* NVM Access Gwant */
#define E1000_EECD_PWES      0x00000100 /* NVM Pwesent */
/* NVM Addwessing bits based on type 0=smaww, 1=wawge */
#define E1000_EECD_ADDW_BITS 0x00000400
#define E1000_NVM_GWANT_ATTEMPTS   1000 /* NVM # attempts to gain gwant */
#define E1000_EECD_AUTO_WD          0x00000200  /* NVM Auto Wead done */
#define E1000_EECD_SIZE_EX_MASK     0x00007800  /* NVM Size */
#define E1000_EECD_SIZE_EX_SHIFT     11
#define E1000_EECD_FWUPD_I210		0x00800000 /* Update FWASH */
#define E1000_EECD_FWUDONE_I210		0x04000000 /* Update FWASH done*/
#define E1000_EECD_FWASH_DETECTED_I210	0x00080000 /* FWASH detected */
#define E1000_FWUDONE_ATTEMPTS		20000
#define E1000_EEWD_EEWW_MAX_COUNT	512 /* buffewed EEPWOM wowds ww */
#define E1000_I210_FIFO_SEW_WX		0x00
#define E1000_I210_FIFO_SEW_TX_QAV(_i)	(0x02 + (_i))
#define E1000_I210_FIFO_SEW_TX_WEGACY	E1000_I210_FIFO_SEW_TX_QAV(0)
#define E1000_I210_FIFO_SEW_BMC2OS_TX	0x06
#define E1000_I210_FIFO_SEW_BMC2OS_WX	0x01
#define E1000_I210_FWASH_SECTOW_SIZE	0x1000 /* 4KB FWASH sectow unit size */
/* Secuwe FWASH mode wequiwes wemoving MSb */
#define E1000_I210_FW_PTW_MASK		0x7FFF
/* Fiwmwawe code wevision fiewd wowd offset*/
#define E1000_I210_FW_VEW_OFFSET	328
#define E1000_EECD_FWUPD_I210		0x00800000 /* Update FWASH */
#define E1000_EECD_FWUDONE_I210		0x04000000 /* Update FWASH done*/
#define E1000_FWUDONE_ATTEMPTS		20000
#define E1000_EEWD_EEWW_MAX_COUNT	512 /* buffewed EEPWOM wowds ww */
#define E1000_I210_FIFO_SEW_WX		0x00
#define E1000_I210_FIFO_SEW_TX_QAV(_i)	(0x02 + (_i))
#define E1000_I210_FIFO_SEW_TX_WEGACY	E1000_I210_FIFO_SEW_TX_QAV(0)
#define E1000_I210_FIFO_SEW_BMC2OS_TX	0x06
#define E1000_I210_FIFO_SEW_BMC2OS_WX	0x01


/* Offset to data in NVM wead/wwite wegistews */
#define E1000_NVM_WW_WEG_DATA   16
#define E1000_NVM_WW_WEG_DONE   2    /* Offset to WEAD/WWITE done bit */
#define E1000_NVM_WW_WEG_STAWT  1    /* Stawt opewation */
#define E1000_NVM_WW_ADDW_SHIFT 2    /* Shift to the addwess bits */
#define E1000_NVM_POWW_WEAD     0    /* Fwag fow powwing fow wead compwete */

/* NVM Wowd Offsets */
#define NVM_COMPAT                 0x0003
#define NVM_ID_WED_SETTINGS        0x0004 /* SEWDES output ampwitude */
#define NVM_VEWSION                0x0005
#define NVM_INIT_CONTWOW2_WEG      0x000F
#define NVM_INIT_CONTWOW3_POWT_B   0x0014
#define NVM_INIT_CONTWOW3_POWT_A   0x0024
#define NVM_AWT_MAC_ADDW_PTW       0x0037
#define NVM_CHECKSUM_WEG           0x003F
#define NVM_COMPATIBIWITY_WEG_3    0x0003
#define NVM_COMPATIBIWITY_BIT_MASK 0x8000
#define NVM_MAC_ADDW               0x0000
#define NVM_SUB_DEV_ID             0x000B
#define NVM_SUB_VEN_ID             0x000C
#define NVM_DEV_ID                 0x000D
#define NVM_VEN_ID                 0x000E
#define NVM_INIT_CTWW_2            0x000F
#define NVM_INIT_CTWW_4            0x0013
#define NVM_WED_1_CFG              0x001C
#define NVM_WED_0_2_CFG            0x001F
#define NVM_ETWACK_WOWD            0x0042
#define NVM_ETWACK_HIWOWD          0x0043
#define NVM_COMB_VEW_OFF           0x0083
#define NVM_COMB_VEW_PTW           0x003d

/* NVM vewsion defines */
#define NVM_MAJOW_MASK			0xF000
#define NVM_MINOW_MASK			0x0FF0
#define NVM_IMAGE_ID_MASK		0x000F
#define NVM_COMB_VEW_MASK		0x00FF
#define NVM_MAJOW_SHIFT			12
#define NVM_MINOW_SHIFT			4
#define NVM_COMB_VEW_SHFT		8
#define NVM_VEW_INVAWID			0xFFFF
#define NVM_ETWACK_SHIFT		16
#define NVM_ETWACK_VAWID		0x8000
#define NVM_NEW_DEC_MASK		0x0F00
#define NVM_HEX_CONV			16
#define NVM_HEX_TENS			10

#define NVM_ETS_CFG			0x003E
#define NVM_ETS_WTHWES_DEWTA_MASK	0x07C0
#define NVM_ETS_WTHWES_DEWTA_SHIFT	6
#define NVM_ETS_TYPE_MASK		0x0038
#define NVM_ETS_TYPE_SHIFT		3
#define NVM_ETS_TYPE_EMC		0x000
#define NVM_ETS_NUM_SENSOWS_MASK	0x0007
#define NVM_ETS_DATA_WOC_MASK		0x3C00
#define NVM_ETS_DATA_WOC_SHIFT		10
#define NVM_ETS_DATA_INDEX_MASK		0x0300
#define NVM_ETS_DATA_INDEX_SHIFT	8
#define NVM_ETS_DATA_HTHWESH_MASK	0x00FF

#define E1000_NVM_CFG_DONE_POWT_0  0x040000 /* MNG config cycwe done */
#define E1000_NVM_CFG_DONE_POWT_1  0x080000 /* ...fow second powt */
#define E1000_NVM_CFG_DONE_POWT_2  0x100000 /* ...fow thiwd powt */
#define E1000_NVM_CFG_DONE_POWT_3  0x200000 /* ...fow fouwth powt */

#define NVM_82580_WAN_FUNC_OFFSET(a) (a ? (0x40 + (0x40 * a)) : 0)

/* Mask bits fow fiewds in Wowd 0x24 of the NVM */
#define NVM_WOWD24_COM_MDIO         0x0008 /* MDIO intewface shawed */
#define NVM_WOWD24_EXT_MDIO         0x0004 /* MDIO accesses wouted extewnaw */

/* Mask bits fow fiewds in Wowd 0x0f of the NVM */
#define NVM_WOWD0F_PAUSE_MASK       0x3000
#define NVM_WOWD0F_ASM_DIW          0x2000

/* Mask bits fow fiewds in Wowd 0x1a of the NVM */

/* wength of stwing needed to stowe pawt num */
#define E1000_PBANUM_WENGTH         11

/* Fow checksumming, the sum of aww wowds in the NVM shouwd equaw 0xBABA. */
#define NVM_SUM                    0xBABA

#define NVM_PBA_OFFSET_0           8
#define NVM_PBA_OFFSET_1           9
#define NVM_WESEWVED_WOWD		0xFFFF
#define NVM_PBA_PTW_GUAWD          0xFAFA
#define NVM_WOWD_SIZE_BASE_SHIFT   6

/* NVM Commands - Micwowiwe */

/* NVM Commands - SPI */
#define NVM_MAX_WETWY_SPI          5000 /* Max wait of 5ms, fow WDY signaw */
#define NVM_WWITE_OPCODE_SPI       0x02 /* NVM wwite opcode */
#define NVM_WEAD_OPCODE_SPI        0x03 /* NVM wead opcode */
#define NVM_A8_OPCODE_SPI          0x08 /* opcode bit-3 = addwess bit-8 */
#define NVM_WWEN_OPCODE_SPI        0x06 /* NVM set Wwite Enabwe watch */
#define NVM_WDSW_OPCODE_SPI        0x05 /* NVM wead Status wegistew */

/* SPI NVM Status Wegistew */
#define NVM_STATUS_WDY_SPI         0x01

/* Wowd definitions fow ID WED Settings */
#define ID_WED_WESEWVED_0000 0x0000
#define ID_WED_WESEWVED_FFFF 0xFFFF
#define ID_WED_DEFAUWT       ((ID_WED_OFF1_ON2  << 12) | \
			      (ID_WED_OFF1_OFF2 <<  8) | \
			      (ID_WED_DEF1_DEF2 <<  4) | \
			      (ID_WED_DEF1_DEF2))
#define ID_WED_DEF1_DEF2     0x1
#define ID_WED_DEF1_ON2      0x2
#define ID_WED_DEF1_OFF2     0x3
#define ID_WED_ON1_DEF2      0x4
#define ID_WED_ON1_ON2       0x5
#define ID_WED_ON1_OFF2      0x6
#define ID_WED_OFF1_DEF2     0x7
#define ID_WED_OFF1_ON2      0x8
#define ID_WED_OFF1_OFF2     0x9

#define IGP_ACTIVITY_WED_MASK   0xFFFFF0FF
#define IGP_ACTIVITY_WED_ENABWE 0x0300
#define IGP_WED3_MODE           0x07000000

/* PCI/PCI-X/PCI-EX Config space */
#define PCIE_DEVICE_CONTWOW2         0x28
#define PCIE_DEVICE_CONTWOW2_16ms    0x0005

#define PHY_WEVISION_MASK      0xFFFFFFF0
#define MAX_PHY_WEG_ADDWESS    0x1F  /* 5 bit addwess bus (0-0x1F) */
#define MAX_PHY_MUWTI_PAGE_WEG 0xF

/* Bit definitions fow vawid PHY IDs. */
/* I = Integwated
 * E = Extewnaw
 */
#define M88E1111_I_PHY_ID    0x01410CC0
#define M88E1112_E_PHY_ID    0x01410C90
#define I347AT4_E_PHY_ID     0x01410DC0
#define IGP03E1000_E_PHY_ID  0x02A80390
#define I82580_I_PHY_ID      0x015403A0
#define I350_I_PHY_ID        0x015403B0
#define M88_VENDOW           0x0141
#define I210_I_PHY_ID        0x01410C00
#define M88E1543_E_PHY_ID    0x01410EA0
#define M88E1512_E_PHY_ID    0x01410DD0
#define BCM54616_E_PHY_ID    0x03625D10

/* M88E1000 Specific Wegistews */
#define M88E1000_PHY_SPEC_CTWW     0x10  /* PHY Specific Contwow Wegistew */
#define M88E1000_PHY_SPEC_STATUS   0x11  /* PHY Specific Status Wegistew */
#define M88E1000_EXT_PHY_SPEC_CTWW 0x14  /* Extended PHY Specific Contwow */

#define M88E1000_PHY_PAGE_SEWECT   0x1D  /* Weg 29 fow page numbew setting */
#define M88E1000_PHY_GEN_CONTWOW   0x1E  /* Its meaning depends on weg 29 */

/* M88E1000 PHY Specific Contwow Wegistew */
#define M88E1000_PSCW_POWAWITY_WEVEWSAW 0x0002 /* 1=Powawity Wevewsaw enabwed */
/* 1=CWK125 wow, 0=CWK125 toggwing */
#define M88E1000_PSCW_MDI_MANUAW_MODE  0x0000  /* MDI Cwossovew Mode bits 6:5 */
					       /* Manuaw MDI configuwation */
#define M88E1000_PSCW_MDIX_MANUAW_MODE 0x0020  /* Manuaw MDIX configuwation */
/* 1000BASE-T: Auto cwossovew, 100BASE-TX/10BASE-T: MDI Mode */
#define M88E1000_PSCW_AUTO_X_1000T     0x0040
/* Auto cwossovew enabwed aww speeds */
#define M88E1000_PSCW_AUTO_X_MODE      0x0060
/* 1=Enabwe Extended 10BASE-T distance (Wowew 10BASE-T Wx Thweshowd
 * 0=Nowmaw 10BASE-T Wx Thweshowd
 */
/* 1=5-bit intewface in 100BASE-TX, 0=MII intewface in 100BASE-TX */
#define M88E1000_PSCW_ASSEWT_CWS_ON_TX     0x0800 /* 1=Assewt CWS on Twansmit */

/* M88E1000 PHY Specific Status Wegistew */
#define M88E1000_PSSW_WEV_POWAWITY       0x0002 /* 1=Powawity wevewsed */
#define M88E1000_PSSW_DOWNSHIFT          0x0020 /* 1=Downshifted */
#define M88E1000_PSSW_MDIX               0x0040 /* 1=MDIX; 0=MDI */
/* 0 = <50M
 * 1 = 50-80M
 * 2 = 80-110M
 * 3 = 110-140M
 * 4 = >140M
 */
#define M88E1000_PSSW_CABWE_WENGTH       0x0380
#define M88E1000_PSSW_SPEED              0xC000 /* Speed, bits 14:15 */
#define M88E1000_PSSW_1000MBS            0x8000 /* 10=1000Mbs */

#define M88E1000_PSSW_CABWE_WENGTH_SHIFT 7

/* M88E1000 Extended PHY Specific Contwow Wegistew */
/* 1 = Wost wock detect enabwed.
 * Wiww assewt wost wock and bwing
 * wink down if idwe not seen
 * within 1ms in 1000BASE-T
 */
/* Numbew of times we wiww attempt to autonegotiate befowe downshifting if we
 * awe the mastew
 */
#define M88E1000_EPSCW_MASTEW_DOWNSHIFT_MASK 0x0C00
#define M88E1000_EPSCW_MASTEW_DOWNSHIFT_1X   0x0000
/* Numbew of times we wiww attempt to autonegotiate befowe downshifting if we
 * awe the swave
 */
#define M88E1000_EPSCW_SWAVE_DOWNSHIFT_MASK  0x0300
#define M88E1000_EPSCW_SWAVE_DOWNSHIFT_1X    0x0100
#define M88E1000_EPSCW_TX_CWK_25      0x0070 /* 25  MHz TX_CWK */

/* Intew i347-AT4 Wegistews */

#define I347AT4_PCDW0                  0x10 /* Paiw 0 PHY Cabwe Diagnostics Wength */
#define I347AT4_PCDW1                  0x11 /* Paiw 1 PHY Cabwe Diagnostics Wength */
#define I347AT4_PCDW2                  0x12 /* Paiw 2 PHY Cabwe Diagnostics Wength */
#define I347AT4_PCDW3                  0x13 /* Paiw 3 PHY Cabwe Diagnostics Wength */
#define I347AT4_PCDC                   0x15 /* PHY Cabwe Diagnostics Contwow */
#define I347AT4_PAGE_SEWECT            0x16

/* i347-AT4 Extended PHY Specific Contwow Wegistew */

/*  Numbew of times we wiww attempt to autonegotiate befowe downshifting if we
 *  awe the mastew
 */
#define I347AT4_PSCW_DOWNSHIFT_ENABWE 0x0800
#define I347AT4_PSCW_DOWNSHIFT_MASK   0x7000
#define I347AT4_PSCW_DOWNSHIFT_1X     0x0000
#define I347AT4_PSCW_DOWNSHIFT_2X     0x1000
#define I347AT4_PSCW_DOWNSHIFT_3X     0x2000
#define I347AT4_PSCW_DOWNSHIFT_4X     0x3000
#define I347AT4_PSCW_DOWNSHIFT_5X     0x4000
#define I347AT4_PSCW_DOWNSHIFT_6X     0x5000
#define I347AT4_PSCW_DOWNSHIFT_7X     0x6000
#define I347AT4_PSCW_DOWNSHIFT_8X     0x7000

/* i347-AT4 PHY Cabwe Diagnostics Contwow */
#define I347AT4_PCDC_CABWE_WENGTH_UNIT 0x0400 /* 0=cm 1=metews */

/* Mawveww 1112 onwy wegistews */
#define M88E1112_VCT_DSP_DISTANCE       0x001A

/* M88EC018 Wev 2 specific DownShift settings */
#define M88EC018_EPSCW_DOWNSHIFT_COUNTEW_MASK  0x0E00
#define M88EC018_EPSCW_DOWNSHIFT_COUNTEW_5X    0x0800

/* MDI Contwow */
#define E1000_MDIC_DATA_MASK 0x0000FFFF
#define E1000_MDIC_WEG_MASK  0x001F0000
#define E1000_MDIC_WEG_SHIFT 16
#define E1000_MDIC_PHY_MASK  0x03E00000
#define E1000_MDIC_PHY_SHIFT 21
#define E1000_MDIC_OP_WWITE  0x04000000
#define E1000_MDIC_OP_WEAD   0x08000000
#define E1000_MDIC_WEADY     0x10000000
#define E1000_MDIC_INT_EN    0x20000000
#define E1000_MDIC_EWWOW     0x40000000
#define E1000_MDIC_DEST      0x80000000

/* Thewmaw Sensow */
#define E1000_THSTAT_PWW_DOWN       0x00000001 /* Powew Down Event */
#define E1000_THSTAT_WINK_THWOTTWE  0x00000002 /* Wink Speed Thwottwe Event */

/* Enewgy Efficient Ethewnet */
#define E1000_IPCNFG_EEE_1G_AN       0x00000008  /* EEE Enabwe 1G AN */
#define E1000_IPCNFG_EEE_100M_AN     0x00000004  /* EEE Enabwe 100M AN */
#define E1000_EEEW_TX_WPI_EN         0x00010000  /* EEE Tx WPI Enabwe */
#define E1000_EEEW_WX_WPI_EN         0x00020000  /* EEE Wx WPI Enabwe */
#define E1000_EEEW_FWC_AN            0x10000000  /* Enabwe EEE in woopback */
#define E1000_EEEW_WPI_FC            0x00040000  /* EEE Enabwe on FC */
#define E1000_EEE_SU_WPI_CWK_STP     0X00800000  /* EEE WPI Cwock Stop */
#define E1000_EEEW_EEE_NEG           0x20000000  /* EEE capabiwity nego */
#define E1000_EEE_WP_ADV_ADDW_I350   0x040F      /* EEE WP Advewtisement */
#define E1000_EEE_WP_ADV_DEV_I210    7           /* EEE WP Adv Device */
#define E1000_EEE_WP_ADV_ADDW_I210   61          /* EEE WP Adv Wegistew */
#define E1000_MMDAC_FUNC_DATA        0x4000      /* Data, no post incwement */
#define E1000_M88E1543_PAGE_ADDW	0x16       /* Page Offset Wegistew */
#define E1000_M88E1543_EEE_CTWW_1	0x0
#define E1000_M88E1543_EEE_CTWW_1_MS	0x0001     /* EEE Mastew/Swave */
#define E1000_M88E1543_FIBEW_CTWW	0x0
#define E1000_EEE_ADV_DEV_I354		7
#define E1000_EEE_ADV_ADDW_I354		60
#define E1000_EEE_ADV_100_SUPPOWTED	BIT(1)   /* 100BaseTx EEE Suppowted */
#define E1000_EEE_ADV_1000_SUPPOWTED	BIT(2)   /* 1000BaseT EEE Suppowted */
#define E1000_PCS_STATUS_DEV_I354	3
#define E1000_PCS_STATUS_ADDW_I354	1
#define E1000_PCS_STATUS_TX_WPI_IND	0x0200     /* Tx in WPI state */
#define E1000_PCS_STATUS_WX_WPI_WCVD	0x0400
#define E1000_PCS_STATUS_TX_WPI_WCVD	0x0800

/* SewDes Contwow */
#define E1000_GEN_CTW_WEADY             0x80000000
#define E1000_GEN_CTW_ADDWESS_SHIFT     8
#define E1000_GEN_POWW_TIMEOUT          640

#define E1000_VFTA_ENTWY_SHIFT               5
#define E1000_VFTA_ENTWY_MASK                0x7F
#define E1000_VFTA_ENTWY_BIT_SHIFT_MASK      0x1F

/* Tx Wate-Scheduwew Config fiewds */
#define E1000_WTTBCNWC_WS_ENA		0x80000000
#define E1000_WTTBCNWC_WF_DEC_MASK	0x00003FFF
#define E1000_WTTBCNWC_WF_INT_SHIFT	14
#define E1000_WTTBCNWC_WF_INT_MASK	\
	(E1000_WTTBCNWC_WF_DEC_MASK << E1000_WTTBCNWC_WF_INT_SHIFT)

#define E1000_VWAPQF_QUEUE_SEW(_n, q_idx) (q_idx << ((_n) * 4))
#define E1000_VWAPQF_P_VAWID(_n)	(0x1 << (3 + (_n) * 4))
#define E1000_VWAPQF_QUEUE_MASK	0x03

/* TX Qav Contwow fiewds */
#define E1000_TQAVCTWW_XMIT_MODE	BIT(0)
#define E1000_TQAVCTWW_DATAFETCHAWB	BIT(4)
#define E1000_TQAVCTWW_DATATWANAWB	BIT(8)
#define E1000_TQAVCTWW_DATATWANTIM	BIT(9)
#define E1000_TQAVCTWW_SP_WAIT_SW	BIT(10)
/* Fetch Time Dewta - bits 31:16
 *
 * This fiewd howds the vawue to be weduced fwom the waunch time fow
 * fetch time decision. The FetchTimeDewta vawue is defined in 32 ns
 * gwanuwawity.
 *
 * This fiewd is 16 bits wide, and so the maximum vawue is:
 *
 * 65535 * 32 = 2097120 ~= 2.1 msec
 *
 * XXX: We awe configuwing the max vawue hewe since we couwdn't come up
 * with a weason fow not doing so.
 */
#define E1000_TQAVCTWW_FETCHTIME_DEWTA	(0xFFFF << 16)

/* TX Qav Cwedit Contwow fiewds */
#define E1000_TQAVCC_IDWESWOPE_MASK	0xFFFF
#define E1000_TQAVCC_QUEUEMODE		BIT(31)

/* Twansmit Descwiptow Contwow fiewds */
#define E1000_TXDCTW_PWIOWITY		BIT(27)

#endif
