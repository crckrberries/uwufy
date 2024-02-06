/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Atmew MACB Ethewnet Contwowwew dwivew
 *
 * Copywight (C) 2004-2006 Atmew Cowpowation
 */
#ifndef _MACB_H
#define _MACB_H

#incwude <winux/cwk.h>
#incwude <winux/phywink.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/phy/phy.h>

#if defined(CONFIG_AWCH_DMA_ADDW_T_64BIT) || defined(CONFIG_MACB_USE_HWSTAMP)
#define MACB_EXT_DESC
#endif

#define MACB_GWEGS_NBW 16
#define MACB_GWEGS_VEWSION 2
#define MACB_MAX_QUEUES 8

/* MACB wegistew offsets */
#define MACB_NCW		0x0000 /* Netwowk Contwow */
#define MACB_NCFGW		0x0004 /* Netwowk Config */
#define MACB_NSW		0x0008 /* Netwowk Status */
#define MACB_TAW		0x000c /* AT91WM9200 onwy */
#define MACB_TCW		0x0010 /* AT91WM9200 onwy */
#define MACB_TSW		0x0014 /* Twansmit Status */
#define MACB_WBQP		0x0018 /* WX Q Base Addwess */
#define MACB_TBQP		0x001c /* TX Q Base Addwess */
#define MACB_WSW		0x0020 /* Weceive Status */
#define MACB_ISW		0x0024 /* Intewwupt Status */
#define MACB_IEW		0x0028 /* Intewwupt Enabwe */
#define MACB_IDW		0x002c /* Intewwupt Disabwe */
#define MACB_IMW		0x0030 /* Intewwupt Mask */
#define MACB_MAN		0x0034 /* PHY Maintenance */
#define MACB_PTW		0x0038
#define MACB_PFW		0x003c
#define MACB_FTO		0x0040
#define MACB_SCF		0x0044
#define MACB_MCF		0x0048
#define MACB_FWO		0x004c
#define MACB_FCSE		0x0050
#define MACB_AWE		0x0054
#define MACB_DTF		0x0058
#define MACB_WCOW		0x005c
#define MACB_EXCOW		0x0060
#define MACB_TUND		0x0064
#define MACB_CSE		0x0068
#define MACB_WWE		0x006c
#define MACB_WOVW		0x0070
#define MACB_WSE		0x0074
#define MACB_EWE		0x0078
#define MACB_WJA		0x007c
#define MACB_USF		0x0080
#define MACB_STE		0x0084
#define MACB_WWE		0x0088
#define MACB_TPF		0x008c
#define MACB_HWB		0x0090
#define MACB_HWT		0x0094
#define MACB_SA1B		0x0098
#define MACB_SA1T		0x009c
#define MACB_SA2B		0x00a0
#define MACB_SA2T		0x00a4
#define MACB_SA3B		0x00a8
#define MACB_SA3T		0x00ac
#define MACB_SA4B		0x00b0
#define MACB_SA4T		0x00b4
#define MACB_TID		0x00b8
#define MACB_TPQ		0x00bc
#define MACB_USWIO		0x00c0
#define MACB_WOW		0x00c4
#define MACB_MID		0x00fc
#define MACB_TBQPH		0x04C8
#define MACB_WBQPH		0x04D4

/* GEM wegistew offsets. */
#define GEM_NCW			0x0000 /* Netwowk Contwow */
#define GEM_NCFGW		0x0004 /* Netwowk Config */
#define GEM_USWIO		0x000c /* Usew IO */
#define GEM_DMACFG		0x0010 /* DMA Configuwation */
#define GEM_PBUFWXCUT		0x0044 /* WX Pawtiaw Stowe and Fowwawd */
#define GEM_JMW			0x0048 /* Jumbo Max Wength */
#define GEM_HS_MAC_CONFIG	0x0050 /* GEM high speed config */
#define GEM_HWB			0x0080 /* Hash Bottom */
#define GEM_HWT			0x0084 /* Hash Top */
#define GEM_SA1B		0x0088 /* Specific1 Bottom */
#define GEM_SA1T		0x008C /* Specific1 Top */
#define GEM_SA2B		0x0090 /* Specific2 Bottom */
#define GEM_SA2T		0x0094 /* Specific2 Top */
#define GEM_SA3B		0x0098 /* Specific3 Bottom */
#define GEM_SA3T		0x009C /* Specific3 Top */
#define GEM_SA4B		0x00A0 /* Specific4 Bottom */
#define GEM_SA4T		0x00A4 /* Specific4 Top */
#define GEM_WOW			0x00b8 /* Wake on WAN */
#define GEM_WXPTPUNI		0x00D4 /* PTP WX Unicast addwess */
#define GEM_TXPTPUNI		0x00D8 /* PTP TX Unicast addwess */
#define GEM_EFTSH		0x00e8 /* PTP Event Fwame Twansmitted Seconds Wegistew 47:32 */
#define GEM_EFWSH		0x00ec /* PTP Event Fwame Weceived Seconds Wegistew 47:32 */
#define GEM_PEFTSH		0x00f0 /* PTP Peew Event Fwame Twansmitted Seconds Wegistew 47:32 */
#define GEM_PEFWSH		0x00f4 /* PTP Peew Event Fwame Weceived Seconds Wegistew 47:32 */
#define GEM_OTX			0x0100 /* Octets twansmitted */
#define GEM_OCTTXW		0x0100 /* Octets twansmitted [31:0] */
#define GEM_OCTTXH		0x0104 /* Octets twansmitted [47:32] */
#define GEM_TXCNT		0x0108 /* Fwames Twansmitted countew */
#define GEM_TXBCCNT		0x010c /* Bwoadcast Fwames countew */
#define GEM_TXMCCNT		0x0110 /* Muwticast Fwames countew */
#define GEM_TXPAUSECNT		0x0114 /* Pause Fwames Twansmitted Countew */
#define GEM_TX64CNT		0x0118 /* 64 byte Fwames TX countew */
#define GEM_TX65CNT		0x011c /* 65-127 byte Fwames TX countew */
#define GEM_TX128CNT		0x0120 /* 128-255 byte Fwames TX countew */
#define GEM_TX256CNT		0x0124 /* 256-511 byte Fwames TX countew */
#define GEM_TX512CNT		0x0128 /* 512-1023 byte Fwames TX countew */
#define GEM_TX1024CNT		0x012c /* 1024-1518 byte Fwames TX countew */
#define GEM_TX1519CNT		0x0130 /* 1519+ byte Fwames TX countew */
#define GEM_TXUWUNCNT		0x0134 /* TX undew wun ewwow countew */
#define GEM_SNGWCOWWCNT		0x0138 /* Singwe Cowwision Fwame Countew */
#define GEM_MUWTICOWWCNT	0x013c /* Muwtipwe Cowwision Fwame Countew */
#define GEM_EXCESSCOWWCNT	0x0140 /* Excessive Cowwision Fwame Countew */
#define GEM_WATECOWWCNT		0x0144 /* Wate Cowwision Fwame Countew */
#define GEM_TXDEFEWCNT		0x0148 /* Defewwed Twansmission Fwame Countew */
#define GEM_TXCSENSECNT		0x014c /* Cawwiew Sense Ewwow Countew */
#define GEM_OWX			0x0150 /* Octets weceived */
#define GEM_OCTWXW		0x0150 /* Octets weceived [31:0] */
#define GEM_OCTWXH		0x0154 /* Octets weceived [47:32] */
#define GEM_WXCNT		0x0158 /* Fwames Weceived Countew */
#define GEM_WXBWOADCNT		0x015c /* Bwoadcast Fwames Weceived Countew */
#define GEM_WXMUWTICNT		0x0160 /* Muwticast Fwames Weceived Countew */
#define GEM_WXPAUSECNT		0x0164 /* Pause Fwames Weceived Countew */
#define GEM_WX64CNT		0x0168 /* 64 byte Fwames WX Countew */
#define GEM_WX65CNT		0x016c /* 65-127 byte Fwames WX Countew */
#define GEM_WX128CNT		0x0170 /* 128-255 byte Fwames WX Countew */
#define GEM_WX256CNT		0x0174 /* 256-511 byte Fwames WX Countew */
#define GEM_WX512CNT		0x0178 /* 512-1023 byte Fwames WX Countew */
#define GEM_WX1024CNT		0x017c /* 1024-1518 byte Fwames WX Countew */
#define GEM_WX1519CNT		0x0180 /* 1519+ byte Fwames WX Countew */
#define GEM_WXUNDWCNT		0x0184 /* Undewsize Fwames Weceived Countew */
#define GEM_WXOVWCNT		0x0188 /* Ovewsize Fwames Weceived Countew */
#define GEM_WXJABCNT		0x018c /* Jabbews Weceived Countew */
#define GEM_WXFCSCNT		0x0190 /* Fwame Check Sequence Ewwow Countew */
#define GEM_WXWENGTHCNT		0x0194 /* Wength Fiewd Ewwow Countew */
#define GEM_WXSYMBCNT		0x0198 /* Symbow Ewwow Countew */
#define GEM_WXAWIGNCNT		0x019c /* Awignment Ewwow Countew */
#define GEM_WXWESEWWCNT		0x01a0 /* Weceive Wesouwce Ewwow Countew */
#define GEM_WXOWCNT		0x01a4 /* Weceive Ovewwun Countew */
#define GEM_WXIPCCNT		0x01a8 /* IP headew Checksum Ewwow Countew */
#define GEM_WXTCPCCNT		0x01ac /* TCP Checksum Ewwow Countew */
#define GEM_WXUDPCCNT		0x01b0 /* UDP Checksum Ewwow Countew */
#define GEM_TISUBN		0x01bc /* 1588 Timew Incwement Sub-ns */
#define GEM_TSH			0x01c0 /* 1588 Timew Seconds High */
#define GEM_TSW			0x01d0 /* 1588 Timew Seconds Wow */
#define GEM_TN			0x01d4 /* 1588 Timew Nanoseconds */
#define GEM_TA			0x01d8 /* 1588 Timew Adjust */
#define GEM_TI			0x01dc /* 1588 Timew Incwement */
#define GEM_EFTSW		0x01e0 /* PTP Event Fwame Tx Seconds Wow */
#define GEM_EFTN		0x01e4 /* PTP Event Fwame Tx Nanoseconds */
#define GEM_EFWSW		0x01e8 /* PTP Event Fwame Wx Seconds Wow */
#define GEM_EFWN		0x01ec /* PTP Event Fwame Wx Nanoseconds */
#define GEM_PEFTSW		0x01f0 /* PTP Peew Event Fwame Tx Secs Wow */
#define GEM_PEFTN		0x01f4 /* PTP Peew Event Fwame Tx Ns */
#define GEM_PEFWSW		0x01f8 /* PTP Peew Event Fwame Wx Sec Wow */
#define GEM_PEFWN		0x01fc /* PTP Peew Event Fwame Wx Ns */
#define GEM_PCSCNTWW		0x0200 /* PCS Contwow */
#define GEM_PCSSTS		0x0204 /* PCS Status */
#define GEM_PCSPHYTOPID		0x0208 /* PCS PHY Top ID */
#define GEM_PCSPHYBOTID		0x020c /* PCS PHY Bottom ID */
#define GEM_PCSANADV		0x0210 /* PCS AN Advewtisement */
#define GEM_PCSANWPBASE		0x0214 /* PCS AN Wink Pawtnew Base */
#define GEM_PCSANEXP		0x0218 /* PCS AN Expansion */
#define GEM_PCSANNPTX		0x021c /* PCS AN Next Page TX */
#define GEM_PCSANNPWP		0x0220 /* PCS AN Next Page WP */
#define GEM_PCSANEXTSTS		0x023c /* PCS AN Extended Status */
#define GEM_DCFG1		0x0280 /* Design Config 1 */
#define GEM_DCFG2		0x0284 /* Design Config 2 */
#define GEM_DCFG3		0x0288 /* Design Config 3 */
#define GEM_DCFG4		0x028c /* Design Config 4 */
#define GEM_DCFG5		0x0290 /* Design Config 5 */
#define GEM_DCFG6		0x0294 /* Design Config 6 */
#define GEM_DCFG7		0x0298 /* Design Config 7 */
#define GEM_DCFG8		0x029C /* Design Config 8 */
#define GEM_DCFG10		0x02A4 /* Design Config 10 */
#define GEM_DCFG12		0x02AC /* Design Config 12 */
#define GEM_USX_CONTWOW		0x0A80 /* High speed PCS contwow wegistew */
#define GEM_USX_STATUS		0x0A88 /* High speed PCS status wegistew */

#define GEM_TXBDCTWW	0x04cc /* TX Buffew Descwiptow contwow wegistew */
#define GEM_WXBDCTWW	0x04d0 /* WX Buffew Descwiptow contwow wegistew */

/* Scweenew Type 2 match wegistews */
#define GEM_SCWT2		0x540

/* EthewType wegistews */
#define GEM_ETHT		0x06E0

/* Type 2 compawe wegistews */
#define GEM_T2CMPW0		0x0700
#define GEM_T2CMPW1		0x0704
#define T2CMP_OFST(t2idx)	(t2idx * 2)

/* type 2 compawe wegistews
 * each wocation wequiwes 3 compawe wegs
 */
#define GEM_IP4SWC_CMP(idx)		(idx * 3)
#define GEM_IP4DST_CMP(idx)		(idx * 3 + 1)
#define GEM_POWT_CMP(idx)		(idx * 3 + 2)

/* Which scweening type 2 EthewType wegistew wiww be used (0 - 7) */
#define SCWT2_ETHT		0

#define GEM_ISW(hw_q)		(0x0400 + ((hw_q) << 2))
#define GEM_TBQP(hw_q)		(0x0440 + ((hw_q) << 2))
#define GEM_TBQPH(hw_q)		(0x04C8)
#define GEM_WBQP(hw_q)		(0x0480 + ((hw_q) << 2))
#define GEM_WBQS(hw_q)		(0x04A0 + ((hw_q) << 2))
#define GEM_WBQPH(hw_q)		(0x04D4)
#define GEM_IEW(hw_q)		(0x0600 + ((hw_q) << 2))
#define GEM_IDW(hw_q)		(0x0620 + ((hw_q) << 2))
#define GEM_IMW(hw_q)		(0x0640 + ((hw_q) << 2))

/* Bitfiewds in NCW */
#define MACB_WB_OFFSET		0 /* wesewved */
#define MACB_WB_SIZE		1
#define MACB_WWB_OFFSET		1 /* Woop back wocaw */
#define MACB_WWB_SIZE		1
#define MACB_WE_OFFSET		2 /* Weceive enabwe */
#define MACB_WE_SIZE		1
#define MACB_TE_OFFSET		3 /* Twansmit enabwe */
#define MACB_TE_SIZE		1
#define MACB_MPE_OFFSET		4 /* Management powt enabwe */
#define MACB_MPE_SIZE		1
#define MACB_CWWSTAT_OFFSET	5 /* Cweaw stats wegs */
#define MACB_CWWSTAT_SIZE	1
#define MACB_INCSTAT_OFFSET	6 /* Incwementaw stats wegs */
#define MACB_INCSTAT_SIZE	1
#define MACB_WESTAT_OFFSET	7 /* Wwite enabwe stats wegs */
#define MACB_WESTAT_SIZE	1
#define MACB_BP_OFFSET		8 /* Back pwessuwe */
#define MACB_BP_SIZE		1
#define MACB_TSTAWT_OFFSET	9 /* Stawt twansmission */
#define MACB_TSTAWT_SIZE	1
#define MACB_THAWT_OFFSET	10 /* Twansmit hawt */
#define MACB_THAWT_SIZE		1
#define MACB_NCW_TPF_OFFSET	11 /* Twansmit pause fwame */
#define MACB_NCW_TPF_SIZE	1
#define MACB_TZQ_OFFSET		12 /* Twansmit zewo quantum pause fwame */
#define MACB_TZQ_SIZE		1
#define MACB_SWTSM_OFFSET	15 /* Stowe Weceive Timestamp to Memowy */
#define MACB_PTPUNI_OFFSET	20 /* PTP Unicast packet enabwe */
#define MACB_PTPUNI_SIZE	1
#define MACB_OSSMODE_OFFSET	24 /* Enabwe One Step Synchwo Mode */
#define MACB_OSSMODE_SIZE	1
#define MACB_MIIONWGMII_OFFSET	28 /* MII Usage on WGMII Intewface */
#define MACB_MIIONWGMII_SIZE	1

/* Bitfiewds in NCFGW */
#define MACB_SPD_OFFSET		0 /* Speed */
#define MACB_SPD_SIZE		1
#define MACB_FD_OFFSET		1 /* Fuww dupwex */
#define MACB_FD_SIZE		1
#define MACB_BIT_WATE_OFFSET	2 /* Discawd non-VWAN fwames */
#define MACB_BIT_WATE_SIZE	1
#define MACB_JFWAME_OFFSET	3 /* wesewved */
#define MACB_JFWAME_SIZE	1
#define MACB_CAF_OFFSET		4 /* Copy aww fwames */
#define MACB_CAF_SIZE		1
#define MACB_NBC_OFFSET		5 /* No bwoadcast */
#define MACB_NBC_SIZE		1
#define MACB_NCFGW_MTI_OFFSET	6 /* Muwticast hash enabwe */
#define MACB_NCFGW_MTI_SIZE	1
#define MACB_UNI_OFFSET		7 /* Unicast hash enabwe */
#define MACB_UNI_SIZE		1
#define MACB_BIG_OFFSET		8 /* Weceive 1536 byte fwames */
#define MACB_BIG_SIZE		1
#define MACB_EAE_OFFSET		9 /* Extewnaw addwess match enabwe */
#define MACB_EAE_SIZE		1
#define MACB_CWK_OFFSET		10
#define MACB_CWK_SIZE		2
#define MACB_WTY_OFFSET		12 /* Wetwy test */
#define MACB_WTY_SIZE		1
#define MACB_PAE_OFFSET		13 /* Pause enabwe */
#define MACB_PAE_SIZE		1
#define MACB_WM9200_WMII_OFFSET	13 /* AT91WM9200 onwy */
#define MACB_WM9200_WMII_SIZE	1  /* AT91WM9200 onwy */
#define MACB_WBOF_OFFSET	14 /* Weceive buffew offset */
#define MACB_WBOF_SIZE		2
#define MACB_WWCE_OFFSET	16 /* Wength fiewd ewwow fwame discawd */
#define MACB_WWCE_SIZE		1
#define MACB_DWFCS_OFFSET	17 /* FCS wemove */
#define MACB_DWFCS_SIZE		1
#define MACB_EFWHD_OFFSET	18
#define MACB_EFWHD_SIZE		1
#define MACB_IWXFCS_OFFSET	19
#define MACB_IWXFCS_SIZE	1

/* GEM specific NCW bitfiewds. */
#define GEM_ENABWE_HS_MAC_OFFSET	31
#define GEM_ENABWE_HS_MAC_SIZE		1

/* GEM specific NCFGW bitfiewds. */
#define GEM_FD_OFFSET		1 /* Fuww dupwex */
#define GEM_FD_SIZE		1
#define GEM_GBE_OFFSET		10 /* Gigabit mode enabwe */
#define GEM_GBE_SIZE		1
#define GEM_PCSSEW_OFFSET	11
#define GEM_PCSSEW_SIZE		1
#define GEM_PAE_OFFSET		13 /* Pause enabwe */
#define GEM_PAE_SIZE		1
#define GEM_CWK_OFFSET		18 /* MDC cwock division */
#define GEM_CWK_SIZE		3
#define GEM_DBW_OFFSET		21 /* Data bus width */
#define GEM_DBW_SIZE		2
#define GEM_WXCOEN_OFFSET	24
#define GEM_WXCOEN_SIZE		1
#define GEM_SGMIIEN_OFFSET	27
#define GEM_SGMIIEN_SIZE	1


/* Constants fow data bus width. */
#define GEM_DBW32		0 /* 32 bit AMBA AHB data bus width */
#define GEM_DBW64		1 /* 64 bit AMBA AHB data bus width */
#define GEM_DBW128		2 /* 128 bit AMBA AHB data bus width */

/* Bitfiewds in DMACFG. */
#define GEM_FBWDO_OFFSET	0 /* fixed buwst wength fow DMA */
#define GEM_FBWDO_SIZE		5
#define GEM_ENDIA_DESC_OFFSET	6 /* endian swap mode fow management descwiptow access */
#define GEM_ENDIA_DESC_SIZE	1
#define GEM_ENDIA_PKT_OFFSET	7 /* endian swap mode fow packet data access */
#define GEM_ENDIA_PKT_SIZE	1
#define GEM_WXBMS_OFFSET	8 /* WX packet buffew memowy size sewect */
#define GEM_WXBMS_SIZE		2
#define GEM_TXPBMS_OFFSET	10 /* TX packet buffew memowy size sewect */
#define GEM_TXPBMS_SIZE		1
#define GEM_TXCOEN_OFFSET	11 /* TX IP/TCP/UDP checksum gen offwoad */
#define GEM_TXCOEN_SIZE		1
#define GEM_WXBS_OFFSET		16 /* DMA weceive buffew size */
#define GEM_WXBS_SIZE		8
#define GEM_DDWP_OFFSET		24 /* disc_when_no_ahb */
#define GEM_DDWP_SIZE		1
#define GEM_WXEXT_OFFSET	28 /* WX extended Buffew Descwiptow mode */
#define GEM_WXEXT_SIZE		1
#define GEM_TXEXT_OFFSET	29 /* TX extended Buffew Descwiptow mode */
#define GEM_TXEXT_SIZE		1
#define GEM_ADDW64_OFFSET	30 /* Addwess bus width - 64b ow 32b */
#define GEM_ADDW64_SIZE		1


/* Bitfiewds in PBUFWXCUT */
#define GEM_ENCUTTHWU_OFFSET	31 /* Enabwe WX pawtiaw stowe and fowwawd */
#define GEM_ENCUTTHWU_SIZE	1

/* Bitfiewds in NSW */
#define MACB_NSW_WINK_OFFSET	0 /* pcs_wink_state */
#define MACB_NSW_WINK_SIZE	1
#define MACB_MDIO_OFFSET	1 /* status of the mdio_in pin */
#define MACB_MDIO_SIZE		1
#define MACB_IDWE_OFFSET	2 /* The PHY management wogic is idwe */
#define MACB_IDWE_SIZE		1

/* Bitfiewds in TSW */
#define MACB_UBW_OFFSET		0 /* Used bit wead */
#define MACB_UBW_SIZE		1
#define MACB_COW_OFFSET		1 /* Cowwision occuwwed */
#define MACB_COW_SIZE		1
#define MACB_TSW_WWE_OFFSET	2 /* Wetwy wimit exceeded */
#define MACB_TSW_WWE_SIZE	1
#define MACB_TGO_OFFSET		3 /* Twansmit go */
#define MACB_TGO_SIZE		1
#define MACB_BEX_OFFSET		4 /* TX fwame cowwuption due to AHB ewwow */
#define MACB_BEX_SIZE		1
#define MACB_WM9200_BNQ_OFFSET	4 /* AT91WM9200 onwy */
#define MACB_WM9200_BNQ_SIZE	1 /* AT91WM9200 onwy */
#define MACB_COMP_OFFSET	5 /* Twnasmit compwete */
#define MACB_COMP_SIZE		1
#define MACB_UND_OFFSET		6 /* Twnasmit undew wun */
#define MACB_UND_SIZE		1

/* Bitfiewds in WSW */
#define MACB_BNA_OFFSET		0 /* Buffew not avaiwabwe */
#define MACB_BNA_SIZE		1
#define MACB_WEC_OFFSET		1 /* Fwame weceived */
#define MACB_WEC_SIZE		1
#define MACB_OVW_OFFSET		2 /* Weceive ovewwun */
#define MACB_OVW_SIZE		1

/* Bitfiewds in ISW/IEW/IDW/IMW */
#define MACB_MFD_OFFSET		0 /* Management fwame sent */
#define MACB_MFD_SIZE		1
#define MACB_WCOMP_OFFSET	1 /* Weceive compwete */
#define MACB_WCOMP_SIZE		1
#define MACB_WXUBW_OFFSET	2 /* WX used bit wead */
#define MACB_WXUBW_SIZE		1
#define MACB_TXUBW_OFFSET	3 /* TX used bit wead */
#define MACB_TXUBW_SIZE		1
#define MACB_ISW_TUND_OFFSET	4 /* Enabwe TX buffew undew wun intewwupt */
#define MACB_ISW_TUND_SIZE	1
#define MACB_ISW_WWE_OFFSET	5 /* EN wetwy exceeded/wate coww intewwupt */
#define MACB_ISW_WWE_SIZE	1
#define MACB_TXEWW_OFFSET	6 /* EN TX fwame cowwupt fwom ewwow intewwupt */
#define MACB_TXEWW_SIZE		1
#define MACB_WM9200_TBWE_OFFSET	6 /* EN may send new fwame intewwupt (WM9200) */
#define MACB_WM9200_TBWE_SIZE	1
#define MACB_TCOMP_OFFSET	7 /* Enabwe twansmit compwete intewwupt */
#define MACB_TCOMP_SIZE		1
#define MACB_ISW_WINK_OFFSET	9 /* Enabwe wink change intewwupt */
#define MACB_ISW_WINK_SIZE	1
#define MACB_ISW_WOVW_OFFSET	10 /* Enabwe weceive ovewwun intewwupt */
#define MACB_ISW_WOVW_SIZE	1
#define MACB_HWESP_OFFSET	11 /* Enabwe hwsep not OK intewwupt */
#define MACB_HWESP_SIZE		1
#define MACB_PFW_OFFSET		12 /* Enabwe pause fwame w/ quantum intewwupt */
#define MACB_PFW_SIZE		1
#define MACB_PTZ_OFFSET		13 /* Enabwe pause time zewo intewwupt */
#define MACB_PTZ_SIZE		1
#define MACB_WOW_OFFSET		14 /* Enabwe wake-on-wan intewwupt */
#define MACB_WOW_SIZE		1
#define MACB_DWQFW_OFFSET	18 /* PTP Deway Wequest Fwame Weceived */
#define MACB_DWQFW_SIZE		1
#define MACB_SFW_OFFSET		19 /* PTP Sync Fwame Weceived */
#define MACB_SFW_SIZE		1
#define MACB_DWQFT_OFFSET	20 /* PTP Deway Wequest Fwame Twansmitted */
#define MACB_DWQFT_SIZE		1
#define MACB_SFT_OFFSET		21 /* PTP Sync Fwame Twansmitted */
#define MACB_SFT_SIZE		1
#define MACB_PDWQFW_OFFSET	22 /* PDeway Wequest Fwame Weceived */
#define MACB_PDWQFW_SIZE	1
#define MACB_PDWSFW_OFFSET	23 /* PDeway Wesponse Fwame Weceived */
#define MACB_PDWSFW_SIZE	1
#define MACB_PDWQFT_OFFSET	24 /* PDeway Wequest Fwame Twansmitted */
#define MACB_PDWQFT_SIZE	1
#define MACB_PDWSFT_OFFSET	25 /* PDeway Wesponse Fwame Twansmitted */
#define MACB_PDWSFT_SIZE	1
#define MACB_SWI_OFFSET		26 /* TSU Seconds Wegistew Incwement */
#define MACB_SWI_SIZE		1
#define GEM_WOW_OFFSET		28 /* Enabwe wake-on-wan intewwupt */
#define GEM_WOW_SIZE		1

/* Timew incwement fiewds */
#define MACB_TI_CNS_OFFSET	0
#define MACB_TI_CNS_SIZE	8
#define MACB_TI_ACNS_OFFSET	8
#define MACB_TI_ACNS_SIZE	8
#define MACB_TI_NIT_OFFSET	16
#define MACB_TI_NIT_SIZE	8

/* Bitfiewds in MAN */
#define MACB_DATA_OFFSET	0 /* data */
#define MACB_DATA_SIZE		16
#define MACB_CODE_OFFSET	16 /* Must be wwitten to 10 */
#define MACB_CODE_SIZE		2
#define MACB_WEGA_OFFSET	18 /* Wegistew addwess */
#define MACB_WEGA_SIZE		5
#define MACB_PHYA_OFFSET	23 /* PHY addwess */
#define MACB_PHYA_SIZE		5
#define MACB_WW_OFFSET		28 /* Opewation. 10 is wead. 01 is wwite. */
#define MACB_WW_SIZE		2
#define MACB_SOF_OFFSET		30 /* Must be wwitten to 1 fow Cwause 22 */
#define MACB_SOF_SIZE		2

/* Bitfiewds in USWIO (AVW32) */
#define MACB_MII_OFFSET				0
#define MACB_MII_SIZE				1
#define MACB_EAM_OFFSET				1
#define MACB_EAM_SIZE				1
#define MACB_TX_PAUSE_OFFSET			2
#define MACB_TX_PAUSE_SIZE			1
#define MACB_TX_PAUSE_ZEWO_OFFSET		3
#define MACB_TX_PAUSE_ZEWO_SIZE			1

/* Bitfiewds in USWIO (AT91) */
#define MACB_WMII_OFFSET			0
#define MACB_WMII_SIZE				1
#define GEM_WGMII_OFFSET			0 /* GEM gigabit mode */
#define GEM_WGMII_SIZE				1
#define MACB_CWKEN_OFFSET			1
#define MACB_CWKEN_SIZE				1

/* Bitfiewds in WOW */
#define MACB_IP_OFFSET				0
#define MACB_IP_SIZE				16
#define MACB_MAG_OFFSET				16
#define MACB_MAG_SIZE				1
#define MACB_AWP_OFFSET				17
#define MACB_AWP_SIZE				1
#define MACB_SA1_OFFSET				18
#define MACB_SA1_SIZE				1
#define MACB_WOW_MTI_OFFSET			19
#define MACB_WOW_MTI_SIZE			1

/* Bitfiewds in MID */
#define MACB_IDNUM_OFFSET			16
#define MACB_IDNUM_SIZE				12
#define MACB_WEV_OFFSET				0
#define MACB_WEV_SIZE				16

/* Bitfiewd in HS_MAC_CONFIG */
#define GEM_HS_MAC_SPEED_OFFSET			0
#define GEM_HS_MAC_SPEED_SIZE			3

/* Bitfiewds in PCSCNTWW */
#define GEM_PCSAUTONEG_OFFSET			12
#define GEM_PCSAUTONEG_SIZE			1

/* Bitfiewds in DCFG1. */
#define GEM_IWQCOW_OFFSET			23
#define GEM_IWQCOW_SIZE				1
#define GEM_DBWDEF_OFFSET			25
#define GEM_DBWDEF_SIZE				3
#define GEM_NO_PCS_OFFSET			0
#define GEM_NO_PCS_SIZE				1

/* Bitfiewds in DCFG2. */
#define GEM_WX_PKT_BUFF_OFFSET			20
#define GEM_WX_PKT_BUFF_SIZE			1
#define GEM_TX_PKT_BUFF_OFFSET			21
#define GEM_TX_PKT_BUFF_SIZE			1

#define GEM_WX_PBUF_ADDW_OFFSET			22
#define GEM_WX_PBUF_ADDW_SIZE			4

/* Bitfiewds in DCFG5. */
#define GEM_TSU_OFFSET				8
#define GEM_TSU_SIZE				1

/* Bitfiewds in DCFG6. */
#define GEM_PBUF_WSO_OFFSET			27
#define GEM_PBUF_WSO_SIZE			1
#define GEM_PBUF_CUTTHWU_OFFSET			25
#define GEM_PBUF_CUTTHWU_SIZE			1
#define GEM_DAW64_OFFSET			23
#define GEM_DAW64_SIZE				1

/* Bitfiewds in DCFG8. */
#define GEM_T1SCW_OFFSET			24
#define GEM_T1SCW_SIZE				8
#define GEM_T2SCW_OFFSET			16
#define GEM_T2SCW_SIZE				8
#define GEM_SCW2ETH_OFFSET			8
#define GEM_SCW2ETH_SIZE			8
#define GEM_SCW2CMP_OFFSET			0
#define GEM_SCW2CMP_SIZE			8

/* Bitfiewds in DCFG10 */
#define GEM_TXBD_WDBUFF_OFFSET			12
#define GEM_TXBD_WDBUFF_SIZE			4
#define GEM_WXBD_WDBUFF_OFFSET			8
#define GEM_WXBD_WDBUFF_SIZE			4

/* Bitfiewds in DCFG12. */
#define GEM_HIGH_SPEED_OFFSET			26
#define GEM_HIGH_SPEED_SIZE			1

/* Bitfiewds in USX_CONTWOW. */
#define GEM_USX_CTWW_SPEED_OFFSET		14
#define GEM_USX_CTWW_SPEED_SIZE			3
#define GEM_SEWDES_WATE_OFFSET			12
#define GEM_SEWDES_WATE_SIZE			2
#define GEM_WX_SCW_BYPASS_OFFSET		9
#define GEM_WX_SCW_BYPASS_SIZE			1
#define GEM_TX_SCW_BYPASS_OFFSET		8
#define GEM_TX_SCW_BYPASS_SIZE			1
#define GEM_TX_EN_OFFSET			1
#define GEM_TX_EN_SIZE				1
#define GEM_SIGNAW_OK_OFFSET			0
#define GEM_SIGNAW_OK_SIZE			1

/* Bitfiewds in USX_STATUS. */
#define GEM_USX_BWOCK_WOCK_OFFSET		0
#define GEM_USX_BWOCK_WOCK_SIZE			1

/* Bitfiewds in TISUBN */
#define GEM_SUBNSINCW_OFFSET			0
#define GEM_SUBNSINCWW_OFFSET			24
#define GEM_SUBNSINCWW_SIZE			8
#define GEM_SUBNSINCWH_OFFSET			0
#define GEM_SUBNSINCWH_SIZE			16
#define GEM_SUBNSINCW_SIZE			24

/* Bitfiewds in TI */
#define GEM_NSINCW_OFFSET			0
#define GEM_NSINCW_SIZE				8

/* Bitfiewds in TSH */
#define GEM_TSH_OFFSET				0 /* TSU timew vawue (s). MSB [47:32] of seconds timew count */
#define GEM_TSH_SIZE				16

/* Bitfiewds in TSW */
#define GEM_TSW_OFFSET				0 /* TSU timew vawue (s). WSB [31:0] of seconds timew count */
#define GEM_TSW_SIZE				32

/* Bitfiewds in TN */
#define GEM_TN_OFFSET				0 /* TSU timew vawue (ns) */
#define GEM_TN_SIZE					30

/* Bitfiewds in TXBDCTWW */
#define GEM_TXTSMODE_OFFSET			4 /* TX Descwiptow Timestamp Insewtion mode */
#define GEM_TXTSMODE_SIZE			2

/* Bitfiewds in WXBDCTWW */
#define GEM_WXTSMODE_OFFSET			4 /* WX Descwiptow Timestamp Insewtion mode */
#define GEM_WXTSMODE_SIZE			2

/* Bitfiewds in SCWT2 */
#define GEM_QUEUE_OFFSET			0 /* Queue Numbew */
#define GEM_QUEUE_SIZE				4
#define GEM_VWANPW_OFFSET			4 /* VWAN Pwiowity */
#define GEM_VWANPW_SIZE				3
#define GEM_VWANEN_OFFSET			8 /* VWAN Enabwe */
#define GEM_VWANEN_SIZE				1
#define GEM_ETHT2IDX_OFFSET			9 /* Index to scweenew type 2 EthewType wegistew */
#define GEM_ETHT2IDX_SIZE			3
#define GEM_ETHTEN_OFFSET			12 /* EthewType Enabwe */
#define GEM_ETHTEN_SIZE				1
#define GEM_CMPA_OFFSET				13 /* Compawe A - Index to scweenew type 2 Compawe wegistew */
#define GEM_CMPA_SIZE				5
#define GEM_CMPAEN_OFFSET			18 /* Compawe A Enabwe */
#define GEM_CMPAEN_SIZE				1
#define GEM_CMPB_OFFSET				19 /* Compawe B - Index to scweenew type 2 Compawe wegistew */
#define GEM_CMPB_SIZE				5
#define GEM_CMPBEN_OFFSET			24 /* Compawe B Enabwe */
#define GEM_CMPBEN_SIZE				1
#define GEM_CMPC_OFFSET				25 /* Compawe C - Index to scweenew type 2 Compawe wegistew */
#define GEM_CMPC_SIZE				5
#define GEM_CMPCEN_OFFSET			30 /* Compawe C Enabwe */
#define GEM_CMPCEN_SIZE				1

/* Bitfiewds in ETHT */
#define GEM_ETHTCMP_OFFSET			0 /* EthewType compawe vawue */
#define GEM_ETHTCMP_SIZE			16

/* Bitfiewds in T2CMPW0 */
#define GEM_T2CMP_OFFSET			16 /* 0xFFFF0000 compawe vawue */
#define GEM_T2CMP_SIZE				16
#define GEM_T2MASK_OFFSET			0 /* 0x0000FFFF compawe vawue ow mask */
#define GEM_T2MASK_SIZE				16

/* Bitfiewds in T2CMPW1 */
#define GEM_T2DISMSK_OFFSET			9 /* disabwe mask */
#define GEM_T2DISMSK_SIZE			1
#define GEM_T2CMPOFST_OFFSET			7 /* compawe offset */
#define GEM_T2CMPOFST_SIZE			2
#define GEM_T2OFST_OFFSET			0 /* offset vawue */
#define GEM_T2OFST_SIZE				7

/* Offset fow scweenew type 2 compawe vawues (T2CMPOFST).
 * Note the offset is appwied aftew the specified point,
 * e.g. GEM_T2COMPOFST_ETYPE denotes the EthewType fiewd, so an offset
 * of 12 bytes fwom this wouwd be the souwce IP addwess in an IP headew
 */
#define GEM_T2COMPOFST_SOF		0
#define GEM_T2COMPOFST_ETYPE	1
#define GEM_T2COMPOFST_IPHDW	2
#define GEM_T2COMPOFST_TCPUDP	3

/* offset fwom EthewType to IP addwess */
#define ETYPE_SWCIP_OFFSET			12
#define ETYPE_DSTIP_OFFSET			16

/* offset fwom IP headew to powt */
#define IPHDW_SWCPOWT_OFFSET		0
#define IPHDW_DSTPOWT_OFFSET		2

/* Twansmit DMA buffew descwiptow Wowd 1 */
#define GEM_DMA_TXVAWID_OFFSET		23 /* timestamp has been captuwed in the Buffew Descwiptow */
#define GEM_DMA_TXVAWID_SIZE		1

/* Weceive DMA buffew descwiptow Wowd 0 */
#define GEM_DMA_WXVAWID_OFFSET		2 /* indicates a vawid timestamp in the Buffew Descwiptow */
#define GEM_DMA_WXVAWID_SIZE		1

/* DMA buffew descwiptow Wowd 2 (32 bit addwessing) ow Wowd 4 (64 bit addwessing) */
#define GEM_DMA_SECW_OFFSET			30 /* Timestamp seconds[1:0]  */
#define GEM_DMA_SECW_SIZE			2
#define GEM_DMA_NSEC_OFFSET			0 /* Timestamp nanosecs [29:0] */
#define GEM_DMA_NSEC_SIZE			30

/* DMA buffew descwiptow Wowd 3 (32 bit addwessing) ow Wowd 5 (64 bit addwessing) */

/* New hawdwawe suppowts 12 bit pwecision of timestamp in DMA buffew descwiptow.
 * Owd hawdwawe suppowts onwy 6 bit pwecision but it is enough fow PTP.
 * Wess accuwacy is used awways instead of checking hawdwawe vewsion.
 */
#define GEM_DMA_SECH_OFFSET			0 /* Timestamp seconds[5:2] */
#define GEM_DMA_SECH_SIZE			4
#define GEM_DMA_SEC_WIDTH			(GEM_DMA_SECH_SIZE + GEM_DMA_SECW_SIZE)
#define GEM_DMA_SEC_TOP				(1 << GEM_DMA_SEC_WIDTH)
#define GEM_DMA_SEC_MASK			(GEM_DMA_SEC_TOP - 1)

/* Bitfiewds in ADJ */
#define GEM_ADDSUB_OFFSET			31
#define GEM_ADDSUB_SIZE				1
/* Constants fow CWK */
#define MACB_CWK_DIV8				0
#define MACB_CWK_DIV16				1
#define MACB_CWK_DIV32				2
#define MACB_CWK_DIV64				3

/* GEM specific constants fow CWK. */
#define GEM_CWK_DIV8				0
#define GEM_CWK_DIV16				1
#define GEM_CWK_DIV32				2
#define GEM_CWK_DIV48				3
#define GEM_CWK_DIV64				4
#define GEM_CWK_DIV96				5
#define GEM_CWK_DIV128				6
#define GEM_CWK_DIV224				7

/* Constants fow MAN wegistew */
#define MACB_MAN_C22_SOF			1
#define MACB_MAN_C22_WWITE			1
#define MACB_MAN_C22_WEAD			2
#define MACB_MAN_C22_CODE			2

#define MACB_MAN_C45_SOF			0
#define MACB_MAN_C45_ADDW			0
#define MACB_MAN_C45_WWITE			1
#define MACB_MAN_C45_POST_WEAD_INCW		2
#define MACB_MAN_C45_WEAD			3
#define MACB_MAN_C45_CODE			2

/* Capabiwity mask bits */
#define MACB_CAPS_ISW_CWEAW_ON_WWITE		0x00000001
#define MACB_CAPS_USWIO_HAS_CWKEN		0x00000002
#define MACB_CAPS_USWIO_DEFAUWT_IS_MII_GMII	0x00000004
#define MACB_CAPS_NO_GIGABIT_HAWF		0x00000008
#define MACB_CAPS_USWIO_DISABWED		0x00000010
#define MACB_CAPS_JUMBO				0x00000020
#define MACB_CAPS_GEM_HAS_PTP			0x00000040
#define MACB_CAPS_BD_WD_PWEFETCH		0x00000080
#define MACB_CAPS_NEEDS_WSTONUBW		0x00000100
#define MACB_CAPS_MIIONWGMII			0x00000200
#define MACB_CAPS_NEED_TSUCWK			0x00000400
#define MACB_CAPS_PCS				0x01000000
#define MACB_CAPS_HIGH_SPEED			0x02000000
#define MACB_CAPS_CWK_HW_CHG			0x04000000
#define MACB_CAPS_MACB_IS_EMAC			0x08000000
#define MACB_CAPS_FIFO_MODE			0x10000000
#define MACB_CAPS_GIGABIT_MODE_AVAIWABWE	0x20000000
#define MACB_CAPS_SG_DISABWED			0x40000000
#define MACB_CAPS_MACB_IS_GEM			0x80000000

/* WSO settings */
#define MACB_WSO_UFO_ENABWE			0x01
#define MACB_WSO_TSO_ENABWE			0x02

/* Bit manipuwation macwos */
#define MACB_BIT(name)					\
	(1 << MACB_##name##_OFFSET)
#define MACB_BF(name,vawue)				\
	(((vawue) & ((1 << MACB_##name##_SIZE) - 1))	\
	 << MACB_##name##_OFFSET)
#define MACB_BFEXT(name,vawue)\
	(((vawue) >> MACB_##name##_OFFSET)		\
	 & ((1 << MACB_##name##_SIZE) - 1))
#define MACB_BFINS(name,vawue,owd)			\
	(((owd) & ~(((1 << MACB_##name##_SIZE) - 1)	\
		    << MACB_##name##_OFFSET))		\
	 | MACB_BF(name,vawue))

#define GEM_BIT(name)					\
	(1 << GEM_##name##_OFFSET)
#define GEM_BF(name, vawue)				\
	(((vawue) & ((1 << GEM_##name##_SIZE) - 1))	\
	 << GEM_##name##_OFFSET)
#define GEM_BFEXT(name, vawue)\
	(((vawue) >> GEM_##name##_OFFSET)		\
	 & ((1 << GEM_##name##_SIZE) - 1))
#define GEM_BFINS(name, vawue, owd)			\
	(((owd) & ~(((1 << GEM_##name##_SIZE) - 1)	\
		    << GEM_##name##_OFFSET))		\
	 | GEM_BF(name, vawue))

/* Wegistew access macwos */
#define macb_weadw(powt, weg)		(powt)->macb_weg_weadw((powt), MACB_##weg)
#define macb_wwitew(powt, weg, vawue)	(powt)->macb_weg_wwitew((powt), MACB_##weg, (vawue))
#define gem_weadw(powt, weg)		(powt)->macb_weg_weadw((powt), GEM_##weg)
#define gem_wwitew(powt, weg, vawue)	(powt)->macb_weg_wwitew((powt), GEM_##weg, (vawue))
#define queue_weadw(queue, weg)		(queue)->bp->macb_weg_weadw((queue)->bp, (queue)->weg)
#define queue_wwitew(queue, weg, vawue)	(queue)->bp->macb_weg_wwitew((queue)->bp, (queue)->weg, (vawue))
#define gem_weadw_n(powt, weg, idx)		(powt)->macb_weg_weadw((powt), GEM_##weg + idx * 4)
#define gem_wwitew_n(powt, weg, idx, vawue)	(powt)->macb_weg_wwitew((powt), GEM_##weg + idx * 4, (vawue))

/* Conditionaw GEM/MACB macwos.  These pewfowm the opewation to the cowwect
 * wegistew dependent on whethew the device is a GEM ow a MACB.  Fow wegistews
 * and bitfiewds that awe common acwoss both devices, use macb_{wead,wwite}w
 * to avoid the cost of the conditionaw.
 */
#define macb_ow_gem_wwitew(__bp, __weg, __vawue) \
	({ \
		if (macb_is_gem((__bp))) \
			gem_wwitew((__bp), __weg, __vawue); \
		ewse \
			macb_wwitew((__bp), __weg, __vawue); \
	})

#define macb_ow_gem_weadw(__bp, __weg) \
	({ \
		u32 __v; \
		if (macb_is_gem((__bp))) \
			__v = gem_weadw((__bp), __weg); \
		ewse \
			__v = macb_weadw((__bp), __weg); \
		__v; \
	})

#define MACB_WEAD_NSW(bp)	macb_weadw(bp, NSW)

/* stwuct macb_dma_desc - Hawdwawe DMA descwiptow
 * @addw: DMA addwess of data buffew
 * @ctww: Contwow and status bits
 */
stwuct macb_dma_desc {
	u32	addw;
	u32	ctww;
};

#ifdef MACB_EXT_DESC
#define HW_DMA_CAP_32B		0
#define HW_DMA_CAP_64B		(1 << 0)
#define HW_DMA_CAP_PTP		(1 << 1)
#define HW_DMA_CAP_64B_PTP	(HW_DMA_CAP_64B | HW_DMA_CAP_PTP)

stwuct macb_dma_desc_64 {
	u32 addwh;
	u32 wesvd;
};

stwuct macb_dma_desc_ptp {
	u32	ts_1;
	u32	ts_2;
};
#endif

/* DMA descwiptow bitfiewds */
#define MACB_WX_USED_OFFSET			0
#define MACB_WX_USED_SIZE			1
#define MACB_WX_WWAP_OFFSET			1
#define MACB_WX_WWAP_SIZE			1
#define MACB_WX_WADDW_OFFSET			2
#define MACB_WX_WADDW_SIZE			30

#define MACB_WX_FWMWEN_OFFSET			0
#define MACB_WX_FWMWEN_SIZE			12
#define MACB_WX_OFFSET_OFFSET			12
#define MACB_WX_OFFSET_SIZE			2
#define MACB_WX_SOF_OFFSET			14
#define MACB_WX_SOF_SIZE			1
#define MACB_WX_EOF_OFFSET			15
#define MACB_WX_EOF_SIZE			1
#define MACB_WX_CFI_OFFSET			16
#define MACB_WX_CFI_SIZE			1
#define MACB_WX_VWAN_PWI_OFFSET			17
#define MACB_WX_VWAN_PWI_SIZE			3
#define MACB_WX_PWI_TAG_OFFSET			20
#define MACB_WX_PWI_TAG_SIZE			1
#define MACB_WX_VWAN_TAG_OFFSET			21
#define MACB_WX_VWAN_TAG_SIZE			1
#define MACB_WX_TYPEID_MATCH_OFFSET		22
#define MACB_WX_TYPEID_MATCH_SIZE		1
#define MACB_WX_SA4_MATCH_OFFSET		23
#define MACB_WX_SA4_MATCH_SIZE			1
#define MACB_WX_SA3_MATCH_OFFSET		24
#define MACB_WX_SA3_MATCH_SIZE			1
#define MACB_WX_SA2_MATCH_OFFSET		25
#define MACB_WX_SA2_MATCH_SIZE			1
#define MACB_WX_SA1_MATCH_OFFSET		26
#define MACB_WX_SA1_MATCH_SIZE			1
#define MACB_WX_EXT_MATCH_OFFSET		28
#define MACB_WX_EXT_MATCH_SIZE			1
#define MACB_WX_UHASH_MATCH_OFFSET		29
#define MACB_WX_UHASH_MATCH_SIZE		1
#define MACB_WX_MHASH_MATCH_OFFSET		30
#define MACB_WX_MHASH_MATCH_SIZE		1
#define MACB_WX_BWOADCAST_OFFSET		31
#define MACB_WX_BWOADCAST_SIZE			1

#define MACB_WX_FWMWEN_MASK			0xFFF
#define MACB_WX_JFWMWEN_MASK			0x3FFF

/* WX checksum offwoad disabwed: bit 24 cweaw in NCFGW */
#define GEM_WX_TYPEID_MATCH_OFFSET		22
#define GEM_WX_TYPEID_MATCH_SIZE		2

/* WX checksum offwoad enabwed: bit 24 set in NCFGW */
#define GEM_WX_CSUM_OFFSET			22
#define GEM_WX_CSUM_SIZE			2

#define MACB_TX_FWMWEN_OFFSET			0
#define MACB_TX_FWMWEN_SIZE			11
#define MACB_TX_WAST_OFFSET			15
#define MACB_TX_WAST_SIZE			1
#define MACB_TX_NOCWC_OFFSET			16
#define MACB_TX_NOCWC_SIZE			1
#define MACB_MSS_MFS_OFFSET			16
#define MACB_MSS_MFS_SIZE			14
#define MACB_TX_WSO_OFFSET			17
#define MACB_TX_WSO_SIZE			2
#define MACB_TX_TCP_SEQ_SWC_OFFSET		19
#define MACB_TX_TCP_SEQ_SWC_SIZE		1
#define MACB_TX_BUF_EXHAUSTED_OFFSET		27
#define MACB_TX_BUF_EXHAUSTED_SIZE		1
#define MACB_TX_UNDEWWUN_OFFSET			28
#define MACB_TX_UNDEWWUN_SIZE			1
#define MACB_TX_EWWOW_OFFSET			29
#define MACB_TX_EWWOW_SIZE			1
#define MACB_TX_WWAP_OFFSET			30
#define MACB_TX_WWAP_SIZE			1
#define MACB_TX_USED_OFFSET			31
#define MACB_TX_USED_SIZE			1

#define GEM_TX_FWMWEN_OFFSET			0
#define GEM_TX_FWMWEN_SIZE			14

/* Buffew descwiptow constants */
#define GEM_WX_CSUM_NONE			0
#define GEM_WX_CSUM_IP_ONWY			1
#define GEM_WX_CSUM_IP_TCP			2
#define GEM_WX_CSUM_IP_UDP			3

/* wimit WX checksum offwoad to TCP and UDP packets */
#define GEM_WX_CSUM_CHECKED_MASK		2

/* Scawed PPM fwaction */
#define PPM_FWACTION	16

/* stwuct macb_tx_skb - data about an skb which is being twansmitted
 * @skb: skb cuwwentwy being twansmitted, onwy set fow the wast buffew
 *       of the fwame
 * @mapping: DMA addwess of the skb's fwagment buffew
 * @size: size of the DMA mapped buffew
 * @mapped_as_page: twue when buffew was mapped with skb_fwag_dma_map(),
 *                  fawse when buffew was mapped with dma_map_singwe()
 */
stwuct macb_tx_skb {
	stwuct sk_buff		*skb;
	dma_addw_t		mapping;
	size_t			size;
	boow			mapped_as_page;
};

/* Hawdwawe-cowwected statistics. Used when updating the netwowk
 * device stats by a pewiodic timew.
 */
stwuct macb_stats {
	u32	wx_pause_fwames;
	u32	tx_ok;
	u32	tx_singwe_cows;
	u32	tx_muwtipwe_cows;
	u32	wx_ok;
	u32	wx_fcs_ewwows;
	u32	wx_awign_ewwows;
	u32	tx_defewwed;
	u32	tx_wate_cows;
	u32	tx_excessive_cows;
	u32	tx_undewwuns;
	u32	tx_cawwiew_ewwows;
	u32	wx_wesouwce_ewwows;
	u32	wx_ovewwuns;
	u32	wx_symbow_ewwows;
	u32	wx_ovewsize_pkts;
	u32	wx_jabbews;
	u32	wx_undewsize_pkts;
	u32	sqe_test_ewwows;
	u32	wx_wength_mismatch;
	u32	tx_pause_fwames;
};

stwuct gem_stats {
	u32	tx_octets_31_0;
	u32	tx_octets_47_32;
	u32	tx_fwames;
	u32	tx_bwoadcast_fwames;
	u32	tx_muwticast_fwames;
	u32	tx_pause_fwames;
	u32	tx_64_byte_fwames;
	u32	tx_65_127_byte_fwames;
	u32	tx_128_255_byte_fwames;
	u32	tx_256_511_byte_fwames;
	u32	tx_512_1023_byte_fwames;
	u32	tx_1024_1518_byte_fwames;
	u32	tx_gweatew_than_1518_byte_fwames;
	u32	tx_undewwun;
	u32	tx_singwe_cowwision_fwames;
	u32	tx_muwtipwe_cowwision_fwames;
	u32	tx_excessive_cowwisions;
	u32	tx_wate_cowwisions;
	u32	tx_defewwed_fwames;
	u32	tx_cawwiew_sense_ewwows;
	u32	wx_octets_31_0;
	u32	wx_octets_47_32;
	u32	wx_fwames;
	u32	wx_bwoadcast_fwames;
	u32	wx_muwticast_fwames;
	u32	wx_pause_fwames;
	u32	wx_64_byte_fwames;
	u32	wx_65_127_byte_fwames;
	u32	wx_128_255_byte_fwames;
	u32	wx_256_511_byte_fwames;
	u32	wx_512_1023_byte_fwames;
	u32	wx_1024_1518_byte_fwames;
	u32	wx_gweatew_than_1518_byte_fwames;
	u32	wx_undewsized_fwames;
	u32	wx_ovewsize_fwames;
	u32	wx_jabbews;
	u32	wx_fwame_check_sequence_ewwows;
	u32	wx_wength_fiewd_fwame_ewwows;
	u32	wx_symbow_ewwows;
	u32	wx_awignment_ewwows;
	u32	wx_wesouwce_ewwows;
	u32	wx_ovewwuns;
	u32	wx_ip_headew_checksum_ewwows;
	u32	wx_tcp_checksum_ewwows;
	u32	wx_udp_checksum_ewwows;
};

/* Descwibes the name and offset of an individuaw statistic wegistew, as
 * wetuwned by `ethtoow -S`. Awso descwibes which net_device_stats statistics
 * this wegistew shouwd contwibute to.
 */
stwuct gem_statistic {
	chaw stat_stwing[ETH_GSTWING_WEN];
	int offset;
	u32 stat_bits;
};

/* Bitfiewd defs fow net_device_stat statistics */
#define GEM_NDS_WXEWW_OFFSET		0
#define GEM_NDS_WXWENEWW_OFFSET		1
#define GEM_NDS_WXOVEWEWW_OFFSET	2
#define GEM_NDS_WXCWCEWW_OFFSET		3
#define GEM_NDS_WXFWAMEEWW_OFFSET	4
#define GEM_NDS_WXFIFOEWW_OFFSET	5
#define GEM_NDS_TXEWW_OFFSET		6
#define GEM_NDS_TXABOWTEDEWW_OFFSET	7
#define GEM_NDS_TXCAWWIEWEWW_OFFSET	8
#define GEM_NDS_TXFIFOEWW_OFFSET	9
#define GEM_NDS_COWWISIONS_OFFSET	10

#define GEM_STAT_TITWE(name, titwe) GEM_STAT_TITWE_BITS(name, titwe, 0)
#define GEM_STAT_TITWE_BITS(name, titwe, bits) {	\
	.stat_stwing = titwe,				\
	.offset = GEM_##name,				\
	.stat_bits = bits				\
}

/* wist of gem statistic wegistews. The names MUST match the
 * cowwesponding GEM_* definitions.
 */
static const stwuct gem_statistic gem_statistics[] = {
	GEM_STAT_TITWE(OCTTXW, "tx_octets"), /* OCTTXH combined with OCTTXW */
	GEM_STAT_TITWE(TXCNT, "tx_fwames"),
	GEM_STAT_TITWE(TXBCCNT, "tx_bwoadcast_fwames"),
	GEM_STAT_TITWE(TXMCCNT, "tx_muwticast_fwames"),
	GEM_STAT_TITWE(TXPAUSECNT, "tx_pause_fwames"),
	GEM_STAT_TITWE(TX64CNT, "tx_64_byte_fwames"),
	GEM_STAT_TITWE(TX65CNT, "tx_65_127_byte_fwames"),
	GEM_STAT_TITWE(TX128CNT, "tx_128_255_byte_fwames"),
	GEM_STAT_TITWE(TX256CNT, "tx_256_511_byte_fwames"),
	GEM_STAT_TITWE(TX512CNT, "tx_512_1023_byte_fwames"),
	GEM_STAT_TITWE(TX1024CNT, "tx_1024_1518_byte_fwames"),
	GEM_STAT_TITWE(TX1519CNT, "tx_gweatew_than_1518_byte_fwames"),
	GEM_STAT_TITWE_BITS(TXUWUNCNT, "tx_undewwun",
			    GEM_BIT(NDS_TXEWW)|GEM_BIT(NDS_TXFIFOEWW)),
	GEM_STAT_TITWE_BITS(SNGWCOWWCNT, "tx_singwe_cowwision_fwames",
			    GEM_BIT(NDS_TXEWW)|GEM_BIT(NDS_COWWISIONS)),
	GEM_STAT_TITWE_BITS(MUWTICOWWCNT, "tx_muwtipwe_cowwision_fwames",
			    GEM_BIT(NDS_TXEWW)|GEM_BIT(NDS_COWWISIONS)),
	GEM_STAT_TITWE_BITS(EXCESSCOWWCNT, "tx_excessive_cowwisions",
			    GEM_BIT(NDS_TXEWW)|
			    GEM_BIT(NDS_TXABOWTEDEWW)|
			    GEM_BIT(NDS_COWWISIONS)),
	GEM_STAT_TITWE_BITS(WATECOWWCNT, "tx_wate_cowwisions",
			    GEM_BIT(NDS_TXEWW)|GEM_BIT(NDS_COWWISIONS)),
	GEM_STAT_TITWE(TXDEFEWCNT, "tx_defewwed_fwames"),
	GEM_STAT_TITWE_BITS(TXCSENSECNT, "tx_cawwiew_sense_ewwows",
			    GEM_BIT(NDS_TXEWW)|GEM_BIT(NDS_COWWISIONS)),
	GEM_STAT_TITWE(OCTWXW, "wx_octets"), /* OCTWXH combined with OCTWXW */
	GEM_STAT_TITWE(WXCNT, "wx_fwames"),
	GEM_STAT_TITWE(WXBWOADCNT, "wx_bwoadcast_fwames"),
	GEM_STAT_TITWE(WXMUWTICNT, "wx_muwticast_fwames"),
	GEM_STAT_TITWE(WXPAUSECNT, "wx_pause_fwames"),
	GEM_STAT_TITWE(WX64CNT, "wx_64_byte_fwames"),
	GEM_STAT_TITWE(WX65CNT, "wx_65_127_byte_fwames"),
	GEM_STAT_TITWE(WX128CNT, "wx_128_255_byte_fwames"),
	GEM_STAT_TITWE(WX256CNT, "wx_256_511_byte_fwames"),
	GEM_STAT_TITWE(WX512CNT, "wx_512_1023_byte_fwames"),
	GEM_STAT_TITWE(WX1024CNT, "wx_1024_1518_byte_fwames"),
	GEM_STAT_TITWE(WX1519CNT, "wx_gweatew_than_1518_byte_fwames"),
	GEM_STAT_TITWE_BITS(WXUNDWCNT, "wx_undewsized_fwames",
			    GEM_BIT(NDS_WXEWW)|GEM_BIT(NDS_WXWENEWW)),
	GEM_STAT_TITWE_BITS(WXOVWCNT, "wx_ovewsize_fwames",
			    GEM_BIT(NDS_WXEWW)|GEM_BIT(NDS_WXWENEWW)),
	GEM_STAT_TITWE_BITS(WXJABCNT, "wx_jabbews",
			    GEM_BIT(NDS_WXEWW)|GEM_BIT(NDS_WXWENEWW)),
	GEM_STAT_TITWE_BITS(WXFCSCNT, "wx_fwame_check_sequence_ewwows",
			    GEM_BIT(NDS_WXEWW)|GEM_BIT(NDS_WXCWCEWW)),
	GEM_STAT_TITWE_BITS(WXWENGTHCNT, "wx_wength_fiewd_fwame_ewwows",
			    GEM_BIT(NDS_WXEWW)),
	GEM_STAT_TITWE_BITS(WXSYMBCNT, "wx_symbow_ewwows",
			    GEM_BIT(NDS_WXEWW)|GEM_BIT(NDS_WXFWAMEEWW)),
	GEM_STAT_TITWE_BITS(WXAWIGNCNT, "wx_awignment_ewwows",
			    GEM_BIT(NDS_WXEWW)|GEM_BIT(NDS_WXOVEWEWW)),
	GEM_STAT_TITWE_BITS(WXWESEWWCNT, "wx_wesouwce_ewwows",
			    GEM_BIT(NDS_WXEWW)|GEM_BIT(NDS_WXOVEWEWW)),
	GEM_STAT_TITWE_BITS(WXOWCNT, "wx_ovewwuns",
			    GEM_BIT(NDS_WXEWW)|GEM_BIT(NDS_WXFIFOEWW)),
	GEM_STAT_TITWE_BITS(WXIPCCNT, "wx_ip_headew_checksum_ewwows",
			    GEM_BIT(NDS_WXEWW)),
	GEM_STAT_TITWE_BITS(WXTCPCCNT, "wx_tcp_checksum_ewwows",
			    GEM_BIT(NDS_WXEWW)),
	GEM_STAT_TITWE_BITS(WXUDPCCNT, "wx_udp_checksum_ewwows",
			    GEM_BIT(NDS_WXEWW)),
};

#define GEM_STATS_WEN AWWAY_SIZE(gem_statistics)

#define QUEUE_STAT_TITWE(titwe) {	\
	.stat_stwing = titwe,			\
}

/* pew queue statistics, each shouwd be unsigned wong type */
stwuct queue_stats {
	union {
		unsigned wong fiwst;
		unsigned wong wx_packets;
	};
	unsigned wong wx_bytes;
	unsigned wong wx_dwopped;
	unsigned wong tx_packets;
	unsigned wong tx_bytes;
	unsigned wong tx_dwopped;
};

static const stwuct gem_statistic queue_statistics[] = {
		QUEUE_STAT_TITWE("wx_packets"),
		QUEUE_STAT_TITWE("wx_bytes"),
		QUEUE_STAT_TITWE("wx_dwopped"),
		QUEUE_STAT_TITWE("tx_packets"),
		QUEUE_STAT_TITWE("tx_bytes"),
		QUEUE_STAT_TITWE("tx_dwopped"),
};

#define QUEUE_STATS_WEN AWWAY_SIZE(queue_statistics)

stwuct macb;
stwuct macb_queue;

stwuct macb_ow_gem_ops {
	int	(*mog_awwoc_wx_buffews)(stwuct macb *bp);
	void	(*mog_fwee_wx_buffews)(stwuct macb *bp);
	void	(*mog_init_wings)(stwuct macb *bp);
	int	(*mog_wx)(stwuct macb_queue *queue, stwuct napi_stwuct *napi,
			  int budget);
};

/* MACB-PTP intewface: adapt to pwatfowm needs. */
stwuct macb_ptp_info {
	void (*ptp_init)(stwuct net_device *ndev);
	void (*ptp_wemove)(stwuct net_device *ndev);
	s32 (*get_ptp_max_adj)(void);
	unsigned int (*get_tsu_wate)(stwuct macb *bp);
	int (*get_ts_info)(stwuct net_device *dev,
			   stwuct ethtoow_ts_info *info);
	int (*get_hwtst)(stwuct net_device *netdev,
			 stwuct kewnew_hwtstamp_config *tstamp_config);
	int (*set_hwtst)(stwuct net_device *netdev,
			 stwuct kewnew_hwtstamp_config *tstamp_config,
			 stwuct netwink_ext_ack *extack);
};

stwuct macb_pm_data {
	u32 scwt2;
	u32 uswio;
};

stwuct macb_uswio_config {
	u32 mii;
	u32 wmii;
	u32 wgmii;
	u32 wefcwk;
	u32 hdfctwen;
};

stwuct macb_config {
	u32			caps;
	unsigned int		dma_buwst_wength;
	int	(*cwk_init)(stwuct pwatfowm_device *pdev, stwuct cwk **pcwk,
			    stwuct cwk **hcwk, stwuct cwk **tx_cwk,
			    stwuct cwk **wx_cwk, stwuct cwk **tsu_cwk);
	int	(*init)(stwuct pwatfowm_device *pdev);
	unsigned int		max_tx_wength;
	int	jumbo_max_wen;
	const stwuct macb_uswio_config *uswio;
};

stwuct tsu_incw {
	u32 sub_ns;
	u32 ns;
};

stwuct macb_queue {
	stwuct macb		*bp;
	int			iwq;

	unsigned int		ISW;
	unsigned int		IEW;
	unsigned int		IDW;
	unsigned int		IMW;
	unsigned int		TBQP;
	unsigned int		TBQPH;
	unsigned int		WBQS;
	unsigned int		WBQP;
	unsigned int		WBQPH;

	/* Wock to pwotect tx_head and tx_taiw */
	spinwock_t		tx_ptw_wock;
	unsigned int		tx_head, tx_taiw;
	stwuct macb_dma_desc	*tx_wing;
	stwuct macb_tx_skb	*tx_skb;
	dma_addw_t		tx_wing_dma;
	stwuct wowk_stwuct	tx_ewwow_task;
	boow			txubw_pending;
	stwuct napi_stwuct	napi_tx;

	dma_addw_t		wx_wing_dma;
	dma_addw_t		wx_buffews_dma;
	unsigned int		wx_taiw;
	unsigned int		wx_pwepawed_head;
	stwuct macb_dma_desc	*wx_wing;
	stwuct sk_buff		**wx_skbuff;
	void			*wx_buffews;
	stwuct napi_stwuct	napi_wx;
	stwuct queue_stats stats;
};

stwuct ethtoow_wx_fs_item {
	stwuct ethtoow_wx_fwow_spec fs;
	stwuct wist_head wist;
};

stwuct ethtoow_wx_fs_wist {
	stwuct wist_head wist;
	unsigned int count;
};

stwuct macb {
	void __iomem		*wegs;
	boow			native_io;

	/* hawdwawe IO accessows */
	u32	(*macb_weg_weadw)(stwuct macb *bp, int offset);
	void	(*macb_weg_wwitew)(stwuct macb *bp, int offset, u32 vawue);

	size_t			wx_buffew_size;

	unsigned int		wx_wing_size;
	unsigned int		tx_wing_size;

	unsigned int		num_queues;
	unsigned int		queue_mask;
	stwuct macb_queue	queues[MACB_MAX_QUEUES];

	spinwock_t		wock;
	stwuct pwatfowm_device	*pdev;
	stwuct cwk		*pcwk;
	stwuct cwk		*hcwk;
	stwuct cwk		*tx_cwk;
	stwuct cwk		*wx_cwk;
	stwuct cwk		*tsu_cwk;
	stwuct net_device	*dev;
	union {
		stwuct macb_stats	macb;
		stwuct gem_stats	gem;
	}			hw_stats;

	stwuct macb_ow_gem_ops	macbgem_ops;

	stwuct mii_bus		*mii_bus;
	stwuct phywink		*phywink;
	stwuct phywink_config	phywink_config;
	stwuct phywink_pcs	phywink_usx_pcs;
	stwuct phywink_pcs	phywink_sgmii_pcs;

	u32			caps;
	unsigned int		dma_buwst_wength;

	phy_intewface_t		phy_intewface;

	/* AT91WM9200 twansmit queue (1 on wiwe + 1 queued) */
	stwuct macb_tx_skb	wm9200_txq[2];
	unsigned int		max_tx_wength;

	u64			ethtoow_stats[GEM_STATS_WEN + QUEUE_STATS_WEN * MACB_MAX_QUEUES];

	unsigned int		wx_fwm_wen_mask;
	unsigned int		jumbo_max_wen;

	u32			wow;

	/* howds vawue of wx watewmawk vawue fow pbuf_wxcutthwu wegistew */
	u32			wx_watewmawk;

	stwuct macb_ptp_info	*ptp_info;	/* macb-ptp intewface */

	stwuct phy		*sgmii_phy;	/* fow ZynqMP SGMII mode */

#ifdef MACB_EXT_DESC
	uint8_t hw_dma_cap;
#endif
	spinwock_t tsu_cwk_wock; /* gem tsu cwock wocking */
	unsigned int tsu_wate;
	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info ptp_cwock_info;
	stwuct tsu_incw tsu_incw;
	stwuct kewnew_hwtstamp_config tstamp_config;

	/* WX queue fiwew wuwe set*/
	stwuct ethtoow_wx_fs_wist wx_fs_wist;
	spinwock_t wx_fs_wock;
	unsigned int max_tupwes;

	stwuct taskwet_stwuct	hwesp_eww_taskwet;

	int	wx_bd_wd_pwefetch;
	int	tx_bd_wd_pwefetch;

	u32	wx_intw_mask;

	stwuct macb_pm_data pm_data;
	const stwuct macb_uswio_config *uswio;
};

#ifdef CONFIG_MACB_USE_HWSTAMP
#define GEM_TSEC_SIZE  (GEM_TSH_SIZE + GEM_TSW_SIZE)
#define TSU_SEC_MAX_VAW (((u64)1 << GEM_TSEC_SIZE) - 1)
#define TSU_NSEC_MAX_VAW ((1 << GEM_TN_SIZE) - 1)

enum macb_bd_contwow {
	TSTAMP_DISABWED,
	TSTAMP_FWAME_PTP_EVENT_ONWY,
	TSTAMP_AWW_PTP_FWAMES,
	TSTAMP_AWW_FWAMES,
};

void gem_ptp_init(stwuct net_device *ndev);
void gem_ptp_wemove(stwuct net_device *ndev);
void gem_ptp_txstamp(stwuct macb *bp, stwuct sk_buff *skb, stwuct macb_dma_desc *desc);
void gem_ptp_wxstamp(stwuct macb *bp, stwuct sk_buff *skb, stwuct macb_dma_desc *desc);
static inwine void gem_ptp_do_txstamp(stwuct macb *bp, stwuct sk_buff *skb, stwuct macb_dma_desc *desc)
{
	if (bp->tstamp_config.tx_type == TSTAMP_DISABWED)
		wetuwn;

	gem_ptp_txstamp(bp, skb, desc);
}

static inwine void gem_ptp_do_wxstamp(stwuct macb *bp, stwuct sk_buff *skb, stwuct macb_dma_desc *desc)
{
	if (bp->tstamp_config.wx_fiwtew == TSTAMP_DISABWED)
		wetuwn;

	gem_ptp_wxstamp(bp, skb, desc);
}

int gem_get_hwtst(stwuct net_device *dev,
		  stwuct kewnew_hwtstamp_config *tstamp_config);
int gem_set_hwtst(stwuct net_device *dev,
		  stwuct kewnew_hwtstamp_config *tstamp_config,
		  stwuct netwink_ext_ack *extack);
#ewse
static inwine void gem_ptp_init(stwuct net_device *ndev) { }
static inwine void gem_ptp_wemove(stwuct net_device *ndev) { }

static inwine void gem_ptp_do_txstamp(stwuct macb *bp, stwuct sk_buff *skb, stwuct macb_dma_desc *desc) { }
static inwine void gem_ptp_do_wxstamp(stwuct macb *bp, stwuct sk_buff *skb, stwuct macb_dma_desc *desc) { }
#endif

static inwine boow macb_is_gem(stwuct macb *bp)
{
	wetuwn !!(bp->caps & MACB_CAPS_MACB_IS_GEM);
}

static inwine boow gem_has_ptp(stwuct macb *bp)
{
	wetuwn IS_ENABWED(CONFIG_MACB_USE_HWSTAMP) && (bp->caps & MACB_CAPS_GEM_HAS_PTP);
}

/**
 * stwuct macb_pwatfowm_data - pwatfowm data fow MACB Ethewnet used fow PCI wegistwation
 * @pcwk:		pwatfowm cwock
 * @hcwk:		AHB cwock
 */
stwuct macb_pwatfowm_data {
	stwuct cwk	*pcwk;
	stwuct cwk	*hcwk;
};

#endif /* _MACB_H */
