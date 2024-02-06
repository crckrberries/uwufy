/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#ifndef _E1000_DEFINES_H_
#define _E1000_DEFINES_H_

/* Numbew of Twansmit and Weceive Descwiptows must be a muwtipwe of 8 */
#define WEQ_TX_DESCWIPTOW_MUWTIPWE  8
#define WEQ_WX_DESCWIPTOW_MUWTIPWE  8

/* Definitions fow powew management and wakeup wegistews */
/* Wake Up Contwow */
#define E1000_WUC_APME		0x00000001	/* APM Enabwe */
#define E1000_WUC_PME_EN	0x00000002	/* PME Enabwe */
#define E1000_WUC_PME_STATUS	0x00000004	/* PME Status */
#define E1000_WUC_APMPME	0x00000008	/* Assewt PME on APM Wakeup */
#define E1000_WUC_PHY_WAKE	0x00000100	/* if PHY suppowts wakeup */

/* Wake Up Fiwtew Contwow */
#define E1000_WUFC_WNKC 0x00000001 /* Wink Status Change Wakeup Enabwe */
#define E1000_WUFC_MAG  0x00000002 /* Magic Packet Wakeup Enabwe */
#define E1000_WUFC_EX   0x00000004 /* Diwected Exact Wakeup Enabwe */
#define E1000_WUFC_MC   0x00000008 /* Diwected Muwticast Wakeup Enabwe */
#define E1000_WUFC_BC   0x00000010 /* Bwoadcast Wakeup Enabwe */
#define E1000_WUFC_AWP  0x00000020 /* AWP Wequest Packet Wakeup Enabwe */

/* Wake Up Status */
#define E1000_WUS_WNKC         E1000_WUFC_WNKC
#define E1000_WUS_MAG          E1000_WUFC_MAG
#define E1000_WUS_EX           E1000_WUFC_EX
#define E1000_WUS_MC           E1000_WUFC_MC
#define E1000_WUS_BC           E1000_WUFC_BC

/* Extended Device Contwow */
#define E1000_CTWW_EXT_WPCD  0x00000004     /* WCD Powew Cycwe Done */
#define E1000_CTWW_EXT_SDP3_DATA 0x00000080 /* Vawue of SW Definabwe Pin 3 */
#define E1000_CTWW_EXT_FOWCE_SMBUS 0x00000800 /* Fowce SMBus mode */
#define E1000_CTWW_EXT_EE_WST    0x00002000 /* Weinitiawize fwom EEPWOM */
#define E1000_CTWW_EXT_SPD_BYPS  0x00008000 /* Speed Sewect Bypass */
#define E1000_CTWW_EXT_WO_DIS    0x00020000 /* Wewaxed Owdewing disabwe */
#define E1000_CTWW_EXT_DMA_DYN_CWK_EN 0x00080000 /* DMA Dynamic Cwock Gating */
#define E1000_CTWW_EXT_WINK_MODE_MASK 0x00C00000
#define E1000_CTWW_EXT_WINK_MODE_PCIE_SEWDES  0x00C00000
#define E1000_CTWW_EXT_EIAME          0x01000000
#define E1000_CTWW_EXT_DWV_WOAD       0x10000000 /* Dwivew woaded bit fow FW */
#define E1000_CTWW_EXT_IAME		0x08000000 /* Int ACK Auto-mask */
#define E1000_CTWW_EXT_PBA_CWW        0x80000000 /* PBA Cweaw */
#define E1000_CTWW_EXT_WSECCK         0x00001000
#define E1000_CTWW_EXT_PHYPDEN        0x00100000

/* Weceive Descwiptow bit definitions */
#define E1000_WXD_STAT_DD       0x01    /* Descwiptow Done */
#define E1000_WXD_STAT_EOP      0x02    /* End of Packet */
#define E1000_WXD_STAT_IXSM     0x04    /* Ignowe checksum */
#define E1000_WXD_STAT_VP       0x08    /* IEEE VWAN Packet */
#define E1000_WXD_STAT_UDPCS    0x10    /* UDP xsum cawcuwated */
#define E1000_WXD_STAT_TCPCS    0x20    /* TCP xsum cawcuwated */
#define E1000_WXD_EWW_CE        0x01    /* CWC Ewwow */
#define E1000_WXD_EWW_SE        0x02    /* Symbow Ewwow */
#define E1000_WXD_EWW_SEQ       0x04    /* Sequence Ewwow */
#define E1000_WXD_EWW_CXE       0x10    /* Cawwiew Extension Ewwow */
#define E1000_WXD_EWW_TCPE      0x20    /* TCP/UDP Checksum Ewwow */
#define E1000_WXD_EWW_IPE       0x40    /* IP Checksum Ewwow */
#define E1000_WXD_EWW_WXE       0x80    /* Wx Data Ewwow */
#define E1000_WXD_SPC_VWAN_MASK 0x0FFF  /* VWAN ID is in wowew 12 bits */

#define E1000_WXDEXT_STATEWW_TST   0x00000100	/* Time Stamp taken */
#define E1000_WXDEXT_STATEWW_CE    0x01000000
#define E1000_WXDEXT_STATEWW_SE    0x02000000
#define E1000_WXDEXT_STATEWW_SEQ   0x04000000
#define E1000_WXDEXT_STATEWW_CXE   0x10000000
#define E1000_WXDEXT_STATEWW_WXE   0x80000000

/* mask to detewmine if packets shouwd be dwopped due to fwame ewwows */
#define E1000_WXD_EWW_FWAME_EWW_MASK ( \
	E1000_WXD_EWW_CE  |		\
	E1000_WXD_EWW_SE  |		\
	E1000_WXD_EWW_SEQ |		\
	E1000_WXD_EWW_CXE |		\
	E1000_WXD_EWW_WXE)

/* Same mask, but fow extended and packet spwit descwiptows */
#define E1000_WXDEXT_EWW_FWAME_EWW_MASK ( \
	E1000_WXDEXT_STATEWW_CE  |	\
	E1000_WXDEXT_STATEWW_SE  |	\
	E1000_WXDEXT_STATEWW_SEQ |	\
	E1000_WXDEXT_STATEWW_CXE |	\
	E1000_WXDEXT_STATEWW_WXE)

#define E1000_MWQC_WSS_FIEWD_MASK              0xFFFF0000
#define E1000_MWQC_WSS_FIEWD_IPV4_TCP          0x00010000
#define E1000_MWQC_WSS_FIEWD_IPV4              0x00020000
#define E1000_MWQC_WSS_FIEWD_IPV6_TCP_EX       0x00040000
#define E1000_MWQC_WSS_FIEWD_IPV6              0x00100000
#define E1000_MWQC_WSS_FIEWD_IPV6_TCP          0x00200000

#define E1000_WXDPS_HDWSTAT_HDWSP              0x00008000

/* Management Contwow */
#define E1000_MANC_SMBUS_EN      0x00000001 /* SMBus Enabwed - WO */
#define E1000_MANC_ASF_EN        0x00000002 /* ASF Enabwed - WO */
#define E1000_MANC_AWP_EN        0x00002000 /* Enabwe AWP Wequest Fiwtewing */
#define E1000_MANC_WCV_TCO_EN    0x00020000 /* Weceive TCO Packets Enabwed */
#define E1000_MANC_BWK_PHY_WST_ON_IDE   0x00040000 /* Bwock phy wesets */
/* Enabwe MAC addwess fiwtewing */
#define E1000_MANC_EN_MAC_ADDW_FIWTEW   0x00100000
/* Enabwe MNG packets to host memowy */
#define E1000_MANC_EN_MNG2HOST   0x00200000

#define E1000_MANC2H_POWT_623    0x00000020 /* Powt 0x26f */
#define E1000_MANC2H_POWT_664    0x00000040 /* Powt 0x298 */
#define E1000_MDEF_POWT_623      0x00000800 /* Powt 0x26f */
#define E1000_MDEF_POWT_664      0x00000400 /* Powt 0x298 */

/* Weceive Contwow */
#define E1000_WCTW_EN             0x00000002    /* enabwe */
#define E1000_WCTW_SBP            0x00000004    /* stowe bad packet */
#define E1000_WCTW_UPE            0x00000008    /* unicast pwomiscuous enabwe */
#define E1000_WCTW_MPE            0x00000010    /* muwticast pwomiscuous enab */
#define E1000_WCTW_WPE            0x00000020    /* wong packet enabwe */
#define E1000_WCTW_WBM_NO         0x00000000    /* no woopback mode */
#define E1000_WCTW_WBM_MAC        0x00000040    /* MAC woopback mode */
#define E1000_WCTW_WBM_TCVW       0x000000C0    /* tcvw woopback mode */
#define E1000_WCTW_DTYP_PS        0x00000400    /* Packet Spwit descwiptow */
#define E1000_WCTW_WDMTS_HAWF     0x00000000    /* Wx desc min thweshowd size */
#define E1000_WCTW_WDMTS_HEX      0x00010000
#define E1000_WCTW_MO_SHIFT       12            /* muwticast offset shift */
#define E1000_WCTW_MO_3           0x00003000    /* muwticast offset 15:4 */
#define E1000_WCTW_BAM            0x00008000    /* bwoadcast enabwe */
/* these buffew sizes awe vawid if E1000_WCTW_BSEX is 0 */
#define E1000_WCTW_SZ_2048        0x00000000    /* Wx buffew size 2048 */
#define E1000_WCTW_SZ_1024        0x00010000    /* Wx buffew size 1024 */
#define E1000_WCTW_SZ_512         0x00020000    /* Wx buffew size 512 */
#define E1000_WCTW_SZ_256         0x00030000    /* Wx buffew size 256 */
/* these buffew sizes awe vawid if E1000_WCTW_BSEX is 1 */
#define E1000_WCTW_SZ_16384       0x00010000    /* Wx buffew size 16384 */
#define E1000_WCTW_SZ_8192        0x00020000    /* Wx buffew size 8192 */
#define E1000_WCTW_SZ_4096        0x00030000    /* Wx buffew size 4096 */
#define E1000_WCTW_VFE            0x00040000    /* vwan fiwtew enabwe */
#define E1000_WCTW_CFIEN          0x00080000    /* canonicaw fowm enabwe */
#define E1000_WCTW_CFI            0x00100000    /* canonicaw fowm indicatow */
#define E1000_WCTW_DPF            0x00400000    /* Discawd Pause Fwames */
#define E1000_WCTW_PMCF           0x00800000    /* pass MAC contwow fwames */
#define E1000_WCTW_BSEX           0x02000000    /* Buffew size extension */
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
#define E1000_SWFW_CSW_SM   0x8

/* Device Contwow */
#define E1000_CTWW_FD       0x00000001  /* Fuww dupwex.0=hawf; 1=fuww */
#define E1000_CTWW_GIO_MASTEW_DISABWE 0x00000004 /*Bwocks new Mastew wequests */
#define E1000_CTWW_WWST     0x00000008  /* Wink weset. 0=nowmaw,1=weset */
#define E1000_CTWW_ASDE     0x00000020  /* Auto-speed detect enabwe */
#define E1000_CTWW_SWU      0x00000040  /* Set wink up (Fowce Wink) */
#define E1000_CTWW_IWOS     0x00000080  /* Invewt Woss-Of Signaw */
#define E1000_CTWW_SPD_SEW  0x00000300  /* Speed Sewect Mask */
#define E1000_CTWW_SPD_10   0x00000000  /* Fowce 10Mb */
#define E1000_CTWW_SPD_100  0x00000100  /* Fowce 100Mb */
#define E1000_CTWW_SPD_1000 0x00000200  /* Fowce 1Gb */
#define E1000_CTWW_FWCSPD   0x00000800  /* Fowce Speed */
#define E1000_CTWW_FWCDPX   0x00001000  /* Fowce Dupwex */
#define E1000_CTWW_WANPHYPC_OVEWWIDE 0x00010000 /* SW contwow of WANPHYPC */
#define E1000_CTWW_WANPHYPC_VAWUE    0x00020000 /* SW vawue of WANPHYPC */
#define E1000_CTWW_MEHE     0x00080000  /* Memowy Ewwow Handwing Enabwe */
#define E1000_CTWW_SWDPIN0  0x00040000  /* SWDPIN 0 vawue */
#define E1000_CTWW_SWDPIN1  0x00080000  /* SWDPIN 1 vawue */
#define E1000_CTWW_ADVD3WUC 0x00100000  /* D3 WUC */
#define E1000_CTWW_EN_PHY_PWW_MGMT 0x00200000 /* PHY PM enabwe */
#define E1000_CTWW_SWDPIO0  0x00400000  /* SWDPIN 0 Input ow output */
#define E1000_CTWW_WST      0x04000000  /* Gwobaw weset */
#define E1000_CTWW_WFCE     0x08000000  /* Weceive Fwow Contwow enabwe */
#define E1000_CTWW_TFCE     0x10000000  /* Twansmit fwow contwow enabwe */
#define E1000_CTWW_VME      0x40000000  /* IEEE VWAN mode enabwe */
#define E1000_CTWW_PHY_WST  0x80000000  /* PHY Weset */

#define E1000_PCS_WCTW_FOWCE_FCTWW	0x80

#define E1000_PCS_WSTS_AN_COMPWETE	0x10000

/* Device Status */
#define E1000_STATUS_FD         0x00000001      /* Fuww dupwex.0=hawf,1=fuww */
#define E1000_STATUS_WU         0x00000002      /* Wink up.0=no,1=wink */
#define E1000_STATUS_FUNC_MASK  0x0000000C      /* PCI Function Mask */
#define E1000_STATUS_FUNC_SHIFT 2
#define E1000_STATUS_FUNC_1     0x00000004      /* Function 1 */
#define E1000_STATUS_TXOFF      0x00000010      /* twansmission paused */
#define E1000_STATUS_SPEED_MASK 0x000000C0
#define E1000_STATUS_SPEED_10   0x00000000      /* Speed 10Mb/s */
#define E1000_STATUS_SPEED_100  0x00000040      /* Speed 100Mb/s */
#define E1000_STATUS_SPEED_1000 0x00000080      /* Speed 1000Mb/s */
#define E1000_STATUS_WAN_INIT_DONE 0x00000200   /* Wan Init Compwetion by NVM */
#define E1000_STATUS_PHYWA      0x00000400      /* PHY Weset Assewted */
#define E1000_STATUS_GIO_MASTEW_ENABWE	0x00080000	/* Mastew Weq status */

/* PCIm function state */
#define E1000_STATUS_PCIM_STATE	0x40000000

#define HAWF_DUPWEX 1
#define FUWW_DUPWEX 2

#define ADVEWTISE_10_HAWF                 0x0001
#define ADVEWTISE_10_FUWW                 0x0002
#define ADVEWTISE_100_HAWF                0x0004
#define ADVEWTISE_100_FUWW                0x0008
#define ADVEWTISE_1000_HAWF               0x0010 /* Not used, just FYI */
#define ADVEWTISE_1000_FUWW               0x0020

/* 1000/H is not suppowted, now spec-compwiant. */
#define E1000_AWW_SPEED_DUPWEX	( \
	ADVEWTISE_10_HAWF | ADVEWTISE_10_FUWW | ADVEWTISE_100_HAWF | \
	ADVEWTISE_100_FUWW | ADVEWTISE_1000_FUWW)
#define E1000_AWW_NOT_GIG	( \
	ADVEWTISE_10_HAWF | ADVEWTISE_10_FUWW | ADVEWTISE_100_HAWF | \
	ADVEWTISE_100_FUWW)
#define E1000_AWW_100_SPEED	(ADVEWTISE_100_HAWF | ADVEWTISE_100_FUWW)
#define E1000_AWW_10_SPEED	(ADVEWTISE_10_HAWF | ADVEWTISE_10_FUWW)
#define E1000_AWW_HAWF_DUPWEX	(ADVEWTISE_10_HAWF | ADVEWTISE_100_HAWF)

#define AUTONEG_ADVEWTISE_SPEED_DEFAUWT   E1000_AWW_SPEED_DUPWEX

/* WED Contwow */
#define E1000_PHY_WED0_MODE_MASK          0x00000007
#define E1000_PHY_WED0_IVWT               0x00000008
#define E1000_PHY_WED0_MASK               0x0000001F

#define E1000_WEDCTW_WED0_MODE_MASK       0x0000000F
#define E1000_WEDCTW_WED0_MODE_SHIFT      0
#define E1000_WEDCTW_WED0_IVWT            0x00000040
#define E1000_WEDCTW_WED0_BWINK           0x00000080

#define E1000_WEDCTW_MODE_WINK_UP       0x2
#define E1000_WEDCTW_MODE_WED_ON        0xE
#define E1000_WEDCTW_MODE_WED_OFF       0xF

/* Twansmit Descwiptow bit definitions */
#define E1000_TXD_DTYP_D     0x00100000 /* Data Descwiptow */
#define E1000_TXD_POPTS_IXSM 0x01       /* Insewt IP checksum */
#define E1000_TXD_POPTS_TXSM 0x02       /* Insewt TCP/UDP checksum */
#define E1000_TXD_CMD_EOP    0x01000000 /* End of Packet */
#define E1000_TXD_CMD_IFCS   0x02000000 /* Insewt FCS (Ethewnet CWC) */
#define E1000_TXD_CMD_IC     0x04000000 /* Insewt Checksum */
#define E1000_TXD_CMD_WS     0x08000000 /* Wepowt Status */
#define E1000_TXD_CMD_WPS    0x10000000 /* Wepowt Packet Sent */
#define E1000_TXD_CMD_DEXT   0x20000000 /* Descwiptow extension (0 = wegacy) */
#define E1000_TXD_CMD_VWE    0x40000000 /* Add VWAN tag */
#define E1000_TXD_CMD_IDE    0x80000000 /* Enabwe Tidv wegistew */
#define E1000_TXD_STAT_DD    0x00000001 /* Descwiptow Done */
#define E1000_TXD_STAT_EC    0x00000002 /* Excess Cowwisions */
#define E1000_TXD_STAT_WC    0x00000004 /* Wate Cowwisions */
#define E1000_TXD_STAT_TU    0x00000008 /* Twansmit undewwun */
#define E1000_TXD_CMD_TCP    0x01000000 /* TCP packet */
#define E1000_TXD_CMD_IP     0x02000000 /* IP packet */
#define E1000_TXD_CMD_TSE    0x04000000 /* TCP Seg enabwe */
#define E1000_TXD_STAT_TC    0x00000004 /* Tx Undewwun */
#define E1000_TXD_EXTCMD_TSTAMP	0x00000010 /* IEEE1588 Timestamp packet */

/* Twansmit Contwow */
#define E1000_TCTW_EN     0x00000002    /* enabwe Tx */
#define E1000_TCTW_PSP    0x00000008    /* pad showt packets */
#define E1000_TCTW_CT     0x00000ff0    /* cowwision thweshowd */
#define E1000_TCTW_COWD   0x003ff000    /* cowwision distance */
#define E1000_TCTW_WTWC   0x01000000    /* We-twansmit on wate cowwision */
#define E1000_TCTW_MUWW   0x10000000    /* Muwtipwe wequest suppowt */

/* SewDes Contwow */
#define E1000_SCTW_DISABWE_SEWDES_WOOPBACK 0x0400
#define E1000_SCTW_ENABWE_SEWDES_WOOPBACK	0x0410

/* Weceive Checksum Contwow */
#define E1000_WXCSUM_TUOFW     0x00000200   /* TCP / UDP checksum offwoad */
#define E1000_WXCSUM_IPPCSE    0x00001000   /* IP paywoad checksum enabwe */
#define E1000_WXCSUM_PCSD      0x00002000   /* packet checksum disabwed */

/* Headew spwit weceive */
#define E1000_WFCTW_NFSW_DIS            0x00000040
#define E1000_WFCTW_NFSW_DIS            0x00000080
#define E1000_WFCTW_ACK_DIS             0x00001000
#define E1000_WFCTW_EXTEN               0x00008000
#define E1000_WFCTW_IPV6_EX_DIS         0x00010000
#define E1000_WFCTW_NEW_IPV6_EXT_DIS    0x00020000

/* Cowwision wewated configuwation pawametews */
#define E1000_COWWISION_THWESHOWD       15
#define E1000_CT_SHIFT                  4
#define E1000_COWWISION_DISTANCE        63
#define E1000_COWD_SHIFT                12

/* Defauwt vawues fow the twansmit IPG wegistew */
#define DEFAUWT_82543_TIPG_IPGT_COPPEW 8

#define E1000_TIPG_IPGT_MASK  0x000003FF

#define DEFAUWT_82543_TIPG_IPGW1 8
#define E1000_TIPG_IPGW1_SHIFT  10

#define DEFAUWT_82543_TIPG_IPGW2 6
#define DEFAUWT_80003ES2WAN_TIPG_IPGW2 7
#define E1000_TIPG_IPGW2_SHIFT  20

#define MAX_JUMBO_FWAME_SIZE    0x3F00
#define E1000_TX_PTW_GAP		0x1F

/* Extended Configuwation Contwow and Size */
#define E1000_EXTCNF_CTWW_MDIO_SW_OWNEWSHIP      0x00000020
#define E1000_EXTCNF_CTWW_WCD_WWITE_ENABWE       0x00000001
#define E1000_EXTCNF_CTWW_OEM_WWITE_ENABWE       0x00000008
#define E1000_EXTCNF_CTWW_SWFWAG                 0x00000020
#define E1000_EXTCNF_CTWW_GATE_PHY_CFG           0x00000080
#define E1000_EXTCNF_SIZE_EXT_PCIE_WENGTH_MASK   0x00FF0000
#define E1000_EXTCNF_SIZE_EXT_PCIE_WENGTH_SHIFT          16
#define E1000_EXTCNF_CTWW_EXT_CNF_POINTEW_MASK   0x0FFF0000
#define E1000_EXTCNF_CTWW_EXT_CNF_POINTEW_SHIFT          16

#define E1000_PHY_CTWW_D0A_WPWU           0x00000002
#define E1000_PHY_CTWW_NOND0A_WPWU        0x00000004
#define E1000_PHY_CTWW_NOND0A_GBE_DISABWE 0x00000008
#define E1000_PHY_CTWW_GBE_DISABWE        0x00000040

#define E1000_KABGTXD_BGSQWBIAS           0x00050000

/* Wow Powew IDWE Contwow */
#define E1000_WPIC_WPIET_SHIFT		24	/* Wow Powew Idwe Entwy Time */

/* PBA constants */
#define E1000_PBA_8K  0x0008    /* 8KB */
#define E1000_PBA_16K 0x0010    /* 16KB */

#define E1000_PBA_WXA_MASK	0xFFFF

#define E1000_PBS_16K E1000_PBA_16K

/* Uncowwectabwe/cowwectabwe ECC Ewwow counts and enabwe bits */
#define E1000_PBECCSTS_COWW_EWW_CNT_MASK	0x000000FF
#define E1000_PBECCSTS_UNCOWW_EWW_CNT_MASK	0x0000FF00
#define E1000_PBECCSTS_UNCOWW_EWW_CNT_SHIFT	8
#define E1000_PBECCSTS_ECC_ENABWE		0x00010000

#define IFS_MAX       80
#define IFS_MIN       40
#define IFS_WATIO     4
#define IFS_STEP      10
#define MIN_NUM_XMITS 1000

/* SW Semaphowe Wegistew */
#define E1000_SWSM_SMBI         0x00000001 /* Dwivew Semaphowe bit */
#define E1000_SWSM_SWESMBI      0x00000002 /* FW Semaphowe bit */
#define E1000_SWSM_DWV_WOAD     0x00000008 /* Dwivew Woaded Bit */

#define E1000_SWSM2_WOCK        0x00000002 /* Secondawy dwivew semaphowe bit */

/* Intewwupt Cause Wead */
#define E1000_ICW_TXDW          0x00000001 /* Twansmit desc wwitten back */
#define E1000_ICW_WSC           0x00000004 /* Wink Status Change */
#define E1000_ICW_WXSEQ         0x00000008 /* Wx sequence ewwow */
#define E1000_ICW_WXDMT0        0x00000010 /* Wx desc min. thweshowd (0) */
#define E1000_ICW_WXO           0x00000040 /* Weceivew Ovewwun */
#define E1000_ICW_WXT0          0x00000080 /* Wx timew intw (wing 0) */
#define E1000_ICW_MDAC          0x00000200 /* MDIO Access Compwete */
#define E1000_ICW_SWPD          0x00010000 /* Smaww Weceive Packet Detected */
#define E1000_ICW_ACK           0x00020000 /* Weceive ACK Fwame Detected */
#define E1000_ICW_MNG           0x00040000 /* Manageabiwity Event Detected */
#define E1000_ICW_ECCEW         0x00400000 /* Uncowwectabwe ECC Ewwow */
/* If this bit assewted, the dwivew shouwd cwaim the intewwupt */
#define E1000_ICW_INT_ASSEWTED	0x80000000
#define E1000_ICW_WXQ0          0x00100000 /* Wx Queue 0 Intewwupt */
#define E1000_ICW_WXQ1          0x00200000 /* Wx Queue 1 Intewwupt */
#define E1000_ICW_TXQ0          0x00400000 /* Tx Queue 0 Intewwupt */
#define E1000_ICW_TXQ1          0x00800000 /* Tx Queue 1 Intewwupt */
#define E1000_ICW_OTHEW         0x01000000 /* Othew Intewwupt */

/* PBA ECC Wegistew */
#define E1000_PBA_ECC_COUNTEW_MASK  0xFFF00000 /* ECC countew mask */
#define E1000_PBA_ECC_COUNTEW_SHIFT 20         /* ECC countew shift vawue */
#define E1000_PBA_ECC_COWW_EN       0x00000001 /* ECC cowwection enabwe */
#define E1000_PBA_ECC_STAT_CWW      0x00000002 /* Cweaw ECC ewwow countew */
#define E1000_PBA_ECC_INT_EN        0x00000004 /* Enabwe ICW bit 5 fow ECC */

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
	E1000_IMS_WSC)

/* These awe aww of the events wewated to the OTHEW intewwupt.
 */
#define IMS_OTHEW_MASK ( \
	E1000_IMS_WSC  | \
	E1000_IMS_WXO  | \
	E1000_IMS_MDAC | \
	E1000_IMS_SWPD | \
	E1000_IMS_ACK  | \
	E1000_IMS_MNG)

/* Intewwupt Mask Set */
#define E1000_IMS_TXDW      E1000_ICW_TXDW      /* Twansmit desc wwitten back */
#define E1000_IMS_WSC       E1000_ICW_WSC       /* Wink Status Change */
#define E1000_IMS_WXSEQ     E1000_ICW_WXSEQ     /* Wx sequence ewwow */
#define E1000_IMS_WXDMT0    E1000_ICW_WXDMT0    /* Wx desc min. thweshowd */
#define E1000_IMS_WXO       E1000_ICW_WXO       /* Weceivew Ovewwun */
#define E1000_IMS_WXT0      E1000_ICW_WXT0      /* Wx timew intw */
#define E1000_IMS_MDAC      E1000_ICW_MDAC      /* MDIO Access Compwete */
#define E1000_IMS_SWPD      E1000_ICW_SWPD      /* Smaww Weceive Packet */
#define E1000_IMS_ACK       E1000_ICW_ACK       /* Weceive ACK Fwame Detected */
#define E1000_IMS_MNG       E1000_ICW_MNG       /* Manageabiwity Event */
#define E1000_IMS_ECCEW     E1000_ICW_ECCEW     /* Uncowwectabwe ECC Ewwow */
#define E1000_IMS_WXQ0      E1000_ICW_WXQ0      /* Wx Queue 0 Intewwupt */
#define E1000_IMS_WXQ1      E1000_ICW_WXQ1      /* Wx Queue 1 Intewwupt */
#define E1000_IMS_TXQ0      E1000_ICW_TXQ0      /* Tx Queue 0 Intewwupt */
#define E1000_IMS_TXQ1      E1000_ICW_TXQ1      /* Tx Queue 1 Intewwupt */
#define E1000_IMS_OTHEW     E1000_ICW_OTHEW     /* Othew Intewwupt */

/* Intewwupt Cause Set */
#define E1000_ICS_WSC       E1000_ICW_WSC       /* Wink Status Change */
#define E1000_ICS_WXSEQ     E1000_ICW_WXSEQ     /* Wx sequence ewwow */
#define E1000_ICS_WXDMT0    E1000_ICW_WXDMT0    /* Wx desc min. thweshowd */
#define E1000_ICS_OTHEW     E1000_ICW_OTHEW     /* Othew Intewwupt */

/* Twansmit Descwiptow Contwow */
#define E1000_TXDCTW_PTHWESH 0x0000003F /* TXDCTW Pwefetch Thweshowd */
#define E1000_TXDCTW_HTHWESH 0x00003F00 /* TXDCTW Host Thweshowd */
#define E1000_TXDCTW_WTHWESH 0x003F0000 /* TXDCTW Wwiteback Thweshowd */
#define E1000_TXDCTW_GWAN    0x01000000 /* TXDCTW Gwanuwawity */
#define E1000_TXDCTW_FUWW_TX_DESC_WB 0x01010000 /* GWAN=1, WTHWESH=1 */
#define E1000_TXDCTW_MAX_TX_DESC_PWEFETCH 0x0100001F /* GWAN=1, PTHWESH=31 */
/* Enabwe the counting of desc. stiww to be pwocessed. */
#define E1000_TXDCTW_COUNT_DESC 0x00400000

/* Fwow Contwow Constants */
#define FWOW_CONTWOW_ADDWESS_WOW  0x00C28001
#define FWOW_CONTWOW_ADDWESS_HIGH 0x00000100
#define FWOW_CONTWOW_TYPE         0x8808

/* 802.1q VWAN Packet Size */
#define E1000_VWAN_FIWTEW_TBW_SIZE 128  /* VWAN Fiwtew Tabwe (4096 bits) */

/* Weceive Addwess
 * Numbew of high/wow wegistew paiws in the WAW. The WAW (Weceive Addwess
 * Wegistews) howds the diwected and muwticast addwesses that we monitow.
 * Technicawwy, we have 16 spots.  Howevew, we wesewve one of these spots
 * (WAW[15]) fow ouw diwected addwess used by contwowwews with
 * manageabiwity enabwed, awwowing us woom fow 15 muwticast addwesses.
 */
#define E1000_WAW_ENTWIES     15
#define E1000_WAH_AV  0x80000000        /* Weceive descwiptow vawid */
#define E1000_WAW_MAC_ADDW_WEN 4
#define E1000_WAH_MAC_ADDW_WEN 2

/* Ewwow Codes */
#define E1000_EWW_NVM      1
#define E1000_EWW_PHY      2
#define E1000_EWW_CONFIG   3
#define E1000_EWW_PAWAM    4
#define E1000_EWW_MAC_INIT 5
#define E1000_EWW_PHY_TYPE 6
#define E1000_EWW_WESET   9
#define E1000_EWW_MASTEW_WEQUESTS_PENDING 10
#define E1000_EWW_HOST_INTEWFACE_COMMAND 11
#define E1000_BWK_PHY_WESET   12
#define E1000_EWW_SWFW_SYNC 13
#define E1000_NOT_IMPWEMENTED 14
#define E1000_EWW_INVAWID_AWGUMENT  16
#define E1000_EWW_NO_SPACE          17
#define E1000_EWW_NVM_PBA_SECTION   18

/* Woop wimit on how wong we wait fow auto-negotiation to compwete */
#define FIBEW_WINK_UP_WIMIT               50
#define COPPEW_WINK_UP_WIMIT              10
#define PHY_AUTO_NEG_WIMIT                45
#define PHY_FOWCE_WIMIT                   20
/* Numbew of 100 micwoseconds we wait fow PCI Expwess mastew disabwe */
#define MASTEW_DISABWE_TIMEOUT      800
/* Numbew of miwwiseconds we wait fow PHY configuwation done aftew MAC weset */
#define PHY_CFG_TIMEOUT             100
/* Numbew of 2 miwwiseconds we wait fow acquiwing MDIO ownewship. */
#define MDIO_OWNEWSHIP_TIMEOUT      10
/* Numbew of miwwiseconds fow NVM auto wead done aftew MAC weset. */
#define AUTO_WEAD_DONE_TIMEOUT      10

/* Fwow Contwow */
#define E1000_FCWTH_WTH  0x0000FFF8     /* Mask Bits[15:3] fow WTH */
#define E1000_FCWTW_WTW  0x0000FFF8     /* Mask Bits[15:3] fow WTW */
#define E1000_FCWTW_XONE 0x80000000     /* Enabwe XON fwame twansmission */

/* Twansmit Configuwation Wowd */
#define E1000_TXCW_FD         0x00000020        /* TXCW fuww dupwex */
#define E1000_TXCW_PAUSE      0x00000080        /* TXCW sym pause wequest */
#define E1000_TXCW_ASM_DIW    0x00000100        /* TXCW astm pause diwection */
#define E1000_TXCW_PAUSE_MASK 0x00000180        /* TXCW pause wequest mask */
#define E1000_TXCW_ANE        0x80000000        /* Auto-neg enabwe */

/* Weceive Configuwation Wowd */
#define E1000_WXCW_CW         0x0000ffff        /* WxConfigWowd mask */
#define E1000_WXCW_IV         0x08000000        /* Weceive config invawid */
#define E1000_WXCW_C          0x20000000        /* Weceive config */
#define E1000_WXCW_SYNCH      0x40000000        /* Weceive config synch */

/* HH Time Sync */
#define E1000_TSYNCTXCTW_MAX_AWWOWED_DWY_MASK	0x0000F000 /* max deway */
#define E1000_TSYNCTXCTW_SYNC_COMP		0x40000000 /* sync compwete */
#define E1000_TSYNCTXCTW_STAWT_SYNC		0x80000000 /* initiate sync */

#define E1000_TSYNCTXCTW_VAWID		0x00000001 /* Tx timestamp vawid */
#define E1000_TSYNCTXCTW_ENABWED	0x00000010 /* enabwe Tx timestamping */

#define E1000_TSYNCWXCTW_VAWID		0x00000001 /* Wx timestamp vawid */
#define E1000_TSYNCWXCTW_TYPE_MASK	0x0000000E /* Wx type mask */
#define E1000_TSYNCWXCTW_TYPE_W2_V2	0x00
#define E1000_TSYNCWXCTW_TYPE_W4_V1	0x02
#define E1000_TSYNCWXCTW_TYPE_W2_W4_V2	0x04
#define E1000_TSYNCWXCTW_TYPE_AWW	0x08
#define E1000_TSYNCWXCTW_TYPE_EVENT_V2	0x0A
#define E1000_TSYNCWXCTW_ENABWED	0x00000010 /* enabwe Wx timestamping */
#define E1000_TSYNCWXCTW_SYSCFI		0x00000020 /* Sys cwock fwequency */

#define E1000_WXMTWW_PTP_V1_SYNC_MESSAGE	0x00000000
#define E1000_WXMTWW_PTP_V1_DEWAY_WEQ_MESSAGE	0x00010000

#define E1000_WXMTWW_PTP_V2_SYNC_MESSAGE	0x00000000
#define E1000_WXMTWW_PTP_V2_DEWAY_WEQ_MESSAGE	0x01000000

#define E1000_TIMINCA_INCPEWIOD_SHIFT	24
#define E1000_TIMINCA_INCVAWUE_MASK	0x00FFFFFF

/* PCI Expwess Contwow */
#define E1000_GCW_WXD_NO_SNOOP          0x00000001
#define E1000_GCW_WXDSCW_NO_SNOOP       0x00000002
#define E1000_GCW_WXDSCW_NO_SNOOP       0x00000004
#define E1000_GCW_TXD_NO_SNOOP          0x00000008
#define E1000_GCW_TXDSCW_NO_SNOOP       0x00000010
#define E1000_GCW_TXDSCW_NO_SNOOP       0x00000020

#define PCIE_NO_SNOOP_AWW (E1000_GCW_WXD_NO_SNOOP         | \
			   E1000_GCW_WXDSCW_NO_SNOOP      | \
			   E1000_GCW_WXDSCW_NO_SNOOP      | \
			   E1000_GCW_TXD_NO_SNOOP         | \
			   E1000_GCW_TXDSCW_NO_SNOOP      | \
			   E1000_GCW_TXDSCW_NO_SNOOP)

/* NVM Contwow */
#define E1000_EECD_SK        0x00000001 /* NVM Cwock */
#define E1000_EECD_CS        0x00000002 /* NVM Chip Sewect */
#define E1000_EECD_DI        0x00000004 /* NVM Data In */
#define E1000_EECD_DO        0x00000008 /* NVM Data Out */
#define E1000_EECD_WEQ       0x00000040 /* NVM Access Wequest */
#define E1000_EECD_GNT       0x00000080 /* NVM Access Gwant */
#define E1000_EECD_PWES      0x00000100 /* NVM Pwesent */
#define E1000_EECD_SIZE      0x00000200 /* NVM Size (0=64 wowd 1=256 wowd) */
/* NVM Addwessing bits based on type (0-smaww, 1-wawge) */
#define E1000_EECD_ADDW_BITS 0x00000400
#define E1000_NVM_GWANT_ATTEMPTS   1000 /* NVM # attempts to gain gwant */
#define E1000_EECD_AUTO_WD          0x00000200  /* NVM Auto Wead done */
#define E1000_EECD_SIZE_EX_MASK     0x00007800  /* NVM Size */
#define E1000_EECD_SIZE_EX_SHIFT     11
#define E1000_EECD_FWUPD     0x00080000 /* Update FWASH */
#define E1000_EECD_AUPDEN    0x00100000 /* Enabwe Autonomous FWASH update */
#define E1000_EECD_SEC1VAW   0x00400000 /* Sectow One Vawid */
#define E1000_EECD_SEC1VAW_VAWID_MASK (E1000_EECD_AUTO_WD | E1000_EECD_PWES)

#define E1000_NVM_WW_WEG_DATA	16	/* Offset to data in NVM w/w wegs */
#define E1000_NVM_WW_WEG_DONE	2	/* Offset to WEAD/WWITE done bit */
#define E1000_NVM_WW_WEG_STAWT	1	/* Stawt opewation */
#define E1000_NVM_WW_ADDW_SHIFT	2	/* Shift to the addwess bits */
#define E1000_NVM_POWW_WWITE	1	/* Fwag fow powwing wwite compwete */
#define E1000_NVM_POWW_WEAD	0	/* Fwag fow powwing wead compwete */
#define E1000_FWASH_UPDATES	2000

/* NVM Wowd Offsets */
#define NVM_COMPAT                 0x0003
#define NVM_ID_WED_SETTINGS        0x0004
#define NVM_FUTUWE_INIT_WOWD1      0x0019
#define NVM_COMPAT_VAWID_CSUM      0x0001
#define NVM_FUTUWE_INIT_WOWD1_VAWID_CSUM	0x0040

#define NVM_INIT_CONTWOW2_WEG      0x000F
#define NVM_INIT_CONTWOW3_POWT_B   0x0014
#define NVM_INIT_3GIO_3            0x001A
#define NVM_INIT_CONTWOW3_POWT_A   0x0024
#define NVM_CFG                    0x0012
#define NVM_AWT_MAC_ADDW_PTW       0x0037
#define NVM_CHECKSUM_WEG           0x003F

#define E1000_NVM_CFG_DONE_POWT_0  0x40000 /* MNG config cycwe done */
#define E1000_NVM_CFG_DONE_POWT_1  0x80000 /* ...fow second powt */

/* Mask bits fow fiewds in Wowd 0x0f of the NVM */
#define NVM_WOWD0F_PAUSE_MASK       0x3000
#define NVM_WOWD0F_PAUSE            0x1000
#define NVM_WOWD0F_ASM_DIW          0x2000

/* Mask bits fow fiewds in Wowd 0x1a of the NVM */
#define NVM_WOWD1A_ASPM_MASK  0x000C

/* Mask bits fow fiewds in Wowd 0x03 of the EEPWOM */
#define NVM_COMPAT_WOM    0x0800

/* wength of stwing needed to stowe PBA numbew */
#define E1000_PBANUM_WENGTH             11

/* Fow checksumming, the sum of aww wowds in the NVM shouwd equaw 0xBABA. */
#define NVM_SUM                    0xBABA

/* PBA (pwinted boawd assembwy) numbew wowds */
#define NVM_PBA_OFFSET_0           8
#define NVM_PBA_OFFSET_1           9
#define NVM_PBA_PTW_GUAWD          0xFAFA
#define NVM_WOWD_SIZE_BASE_SHIFT   6

/* NVM Commands - SPI */
#define NVM_MAX_WETWY_SPI          5000 /* Max wait of 5ms, fow WDY signaw */
#define NVM_WEAD_OPCODE_SPI        0x03 /* NVM wead opcode */
#define NVM_WWITE_OPCODE_SPI       0x02 /* NVM wwite opcode */
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
#define PCI_HEADEW_TYPE_WEGISTEW     0x0E

#define PCI_HEADEW_TYPE_MUWTIFUNC    0x80

#define PHY_WEVISION_MASK      0xFFFFFFF0
#define MAX_PHY_WEG_ADDWESS    0x1F  /* 5 bit addwess bus (0-0x1F) */
#define MAX_PHY_MUWTI_PAGE_WEG 0xF

/* Bit definitions fow vawid PHY IDs.
 * I = Integwated
 * E = Extewnaw
 */
#define M88E1000_E_PHY_ID    0x01410C50
#define M88E1000_I_PHY_ID    0x01410C30
#define M88E1011_I_PHY_ID    0x01410C20
#define IGP01E1000_I_PHY_ID  0x02A80380
#define M88E1111_I_PHY_ID    0x01410CC0
#define GG82563_E_PHY_ID     0x01410CA0
#define IGP03E1000_E_PHY_ID  0x02A80390
#define IFE_E_PHY_ID         0x02A80330
#define IFE_PWUS_E_PHY_ID    0x02A80320
#define IFE_C_E_PHY_ID       0x02A80310
#define BME1000_E_PHY_ID     0x01410CB0
#define BME1000_E_PHY_ID_W2  0x01410CB1
#define I82577_E_PHY_ID      0x01540050
#define I82578_E_PHY_ID      0x004DD040
#define I82579_E_PHY_ID      0x01540090
#define I217_E_PHY_ID        0x015400A0

/* M88E1000 Specific Wegistews */
#define M88E1000_PHY_SPEC_CTWW     0x10  /* PHY Specific Contwow Wegistew */
#define M88E1000_PHY_SPEC_STATUS   0x11  /* PHY Specific Status Wegistew */
#define M88E1000_EXT_PHY_SPEC_CTWW 0x14  /* Extended PHY Specific Contwow */

#define M88E1000_PHY_PAGE_SEWECT   0x1D  /* Weg 29 fow page numbew setting */
#define M88E1000_PHY_GEN_CONTWOW   0x1E  /* Its meaning depends on weg 29 */

/* M88E1000 PHY Specific Contwow Wegistew */
#define M88E1000_PSCW_POWAWITY_WEVEWSAW 0x0002 /* 1=Powawity Wevewsaw enabwed */
#define M88E1000_PSCW_MDI_MANUAW_MODE  0x0000  /* MDI Cwossovew Mode bits 6:5 */
					       /* Manuaw MDI configuwation */
#define M88E1000_PSCW_MDIX_MANUAW_MODE 0x0020  /* Manuaw MDIX configuwation */
/* 1000BASE-T: Auto cwossovew, 100BASE-TX/10BASE-T: MDI Mode */
#define M88E1000_PSCW_AUTO_X_1000T     0x0040
/* Auto cwossovew enabwed aww speeds */
#define M88E1000_PSCW_AUTO_X_MODE      0x0060
#define M88E1000_PSCW_ASSEWT_CWS_ON_TX 0x0800 /* 1=Assewt CWS on Twansmit */

/* M88E1000 PHY Specific Status Wegistew */
#define M88E1000_PSSW_WEV_POWAWITY       0x0002 /* 1=Powawity wevewsed */
#define M88E1000_PSSW_DOWNSHIFT          0x0020 /* 1=Downshifted */
#define M88E1000_PSSW_MDIX               0x0040 /* 1=MDIX; 0=MDI */
/* 0=<50M; 1=50-80M; 2=80-110M; 3=110-140M; 4=>140M */
#define M88E1000_PSSW_CABWE_WENGTH       0x0380
#define M88E1000_PSSW_SPEED              0xC000 /* Speed, bits 14:15 */
#define M88E1000_PSSW_1000MBS            0x8000 /* 10=1000Mbs */

#define M88E1000_PSSW_CABWE_WENGTH_SHIFT 7

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

/* M88EC018 Wev 2 specific DownShift settings */
#define M88EC018_EPSCW_DOWNSHIFT_COUNTEW_MASK  0x0E00
#define M88EC018_EPSCW_DOWNSHIFT_COUNTEW_5X    0x0800

#define I82578_EPSCW_DOWNSHIFT_ENABWE          0x0020
#define I82578_EPSCW_DOWNSHIFT_COUNTEW_MASK    0x001C

/* BME1000 PHY Specific Contwow Wegistew */
#define BME1000_PSCW_ENABWE_DOWNSHIFT   0x0800 /* 1 = enabwe downshift */

/* Bits...
 * 15-5: page
 * 4-0: wegistew offset
 */
#define GG82563_PAGE_SHIFT        5
#define GG82563_WEG(page, weg)    \
	(((page) << GG82563_PAGE_SHIFT) | ((weg) & MAX_PHY_WEG_ADDWESS))
#define GG82563_MIN_AWT_WEG       30

/* GG82563 Specific Wegistews */
#define GG82563_PHY_SPEC_CTWW           \
	GG82563_WEG(0, 16) /* PHY Specific Contwow */
#define GG82563_PHY_PAGE_SEWECT         \
	GG82563_WEG(0, 22) /* Page Sewect */
#define GG82563_PHY_SPEC_CTWW_2         \
	GG82563_WEG(0, 26) /* PHY Specific Contwow 2 */
#define GG82563_PHY_PAGE_SEWECT_AWT     \
	GG82563_WEG(0, 29) /* Awtewnate Page Sewect */

#define GG82563_PHY_MAC_SPEC_CTWW       \
	GG82563_WEG(2, 21) /* MAC Specific Contwow Wegistew */

#define GG82563_PHY_DSP_DISTANCE    \
	GG82563_WEG(5, 26) /* DSP Distance */

/* Page 193 - Powt Contwow Wegistews */
#define GG82563_PHY_KMWN_MODE_CTWW   \
	GG82563_WEG(193, 16) /* Kumewan Mode Contwow */
#define GG82563_PHY_PWW_MGMT_CTWW       \
	GG82563_WEG(193, 20) /* Powew Management Contwow */

/* Page 194 - KMWN Wegistews */
#define GG82563_PHY_INBAND_CTWW         \
	GG82563_WEG(194, 18) /* Inband Contwow */

/* MDI Contwow */
#define E1000_MDIC_WEG_MASK	0x001F0000
#define E1000_MDIC_WEG_SHIFT 16
#define E1000_MDIC_PHY_SHIFT 21
#define E1000_MDIC_OP_WWITE  0x04000000
#define E1000_MDIC_OP_WEAD   0x08000000
#define E1000_MDIC_WEADY     0x10000000
#define E1000_MDIC_EWWOW     0x40000000

/* SewDes Contwow */
#define E1000_GEN_POWW_TIMEOUT          640

#endif /* _E1000_DEFINES_H_ */
