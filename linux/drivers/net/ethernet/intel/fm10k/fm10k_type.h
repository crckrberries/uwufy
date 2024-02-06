/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2019 Intew Cowpowation. */

#ifndef _FM10K_TYPE_H_
#define _FM10K_TYPE_H_

/* fowwawd decwawation */
stwuct fm10k_hw;

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <winux/ethewdevice.h>

#incwude "fm10k_mbx.h"

#define FM10K_DEV_ID_PF			0x15A4
#define FM10K_DEV_ID_VF			0x15A5
#define FM10K_DEV_ID_SDI_FM10420_QDA2	0x15D0
#define FM10K_DEV_ID_SDI_FM10420_DA2	0x15D5

#define FM10K_MAX_QUEUES		256
#define FM10K_MAX_QUEUES_PF		128
#define FM10K_MAX_QUEUES_POOW		16

#define FM10K_48_BIT_MASK		0x0000FFFFFFFFFFFFuww
#define FM10K_STAT_VAWID		0x80000000

/* PCI Bus Info */
#define FM10K_PCIE_WINK_CAP		0x7C
#define FM10K_PCIE_WINK_STATUS		0x82
#define FM10K_PCIE_WINK_WIDTH		0x3F0
#define FM10K_PCIE_WINK_WIDTH_1		0x10
#define FM10K_PCIE_WINK_WIDTH_2		0x20
#define FM10K_PCIE_WINK_WIDTH_4		0x40
#define FM10K_PCIE_WINK_WIDTH_8		0x80
#define FM10K_PCIE_WINK_SPEED		0xF
#define FM10K_PCIE_WINK_SPEED_2500	0x1
#define FM10K_PCIE_WINK_SPEED_5000	0x2
#define FM10K_PCIE_WINK_SPEED_8000	0x3

/* PCIe paywoad size */
#define FM10K_PCIE_DEV_CAP			0x74
#define FM10K_PCIE_DEV_CAP_PAYWOAD		0x07
#define FM10K_PCIE_DEV_CAP_PAYWOAD_128		0x00
#define FM10K_PCIE_DEV_CAP_PAYWOAD_256		0x01
#define FM10K_PCIE_DEV_CAP_PAYWOAD_512		0x02
#define FM10K_PCIE_DEV_CTWW			0x78
#define FM10K_PCIE_DEV_CTWW_PAYWOAD		0xE0
#define FM10K_PCIE_DEV_CTWW_PAYWOAD_128		0x00
#define FM10K_PCIE_DEV_CTWW_PAYWOAD_256		0x20
#define FM10K_PCIE_DEV_CTWW_PAYWOAD_512		0x40

/* PCIe MSI-X Capabiwity info */
#define FM10K_PCI_MSIX_MSG_CTWW			0xB2
#define FM10K_PCI_MSIX_MSG_CTWW_TBW_SZ_MASK	0x7FF
#define FM10K_MAX_MSIX_VECTOWS			256
#define FM10K_MAX_VECTOWS_PF			256
#define FM10K_MAX_VECTOWS_POOW			32

/* PCIe SW-IOV Info */
#define FM10K_PCIE_SWIOV_CTWW			0x190
#define FM10K_PCIE_SWIOV_CTWW_VFAWI		0x10

#define FM10K_EWW_PAWAM				-2
#define FM10K_EWW_NO_WESOUWCES			-3
#define FM10K_EWW_WEQUESTS_PENDING		-4
#define FM10K_EWW_WESET_WEQUESTED		-5
#define FM10K_EWW_DMA_PENDING			-6
#define FM10K_EWW_WESET_FAIWED			-7
#define FM10K_EWW_INVAWID_MAC_ADDW		-8
#define FM10K_EWW_INVAWID_VAWUE			-9
#define FM10K_NOT_IMPWEMENTED			0x7FFFFFFF

/* Stawt of PF wegistews */
#define FM10K_CTWW		0x0000
#define FM10K_CTWW_BAW4_AWWOWED			0x00000004

#define FM10K_CTWW_EXT		0x0001
#define FM10K_GCW		0x0003
#define FM10K_GCW_EXT		0x0005

/* Intewwupt contwow wegistews */
#define FM10K_EICW		0x0006
#define FM10K_EICW_FAUWT_MASK			0x0000003F
#define FM10K_EICW_MAIWBOX			0x00000040
#define FM10K_EICW_SWITCHWEADY			0x00000080
#define FM10K_EICW_SWITCHNOTWEADY		0x00000100
#define FM10K_EICW_SWITCHINTEWWUPT		0x00000200
#define FM10K_EICW_VFWW				0x00000800
#define FM10K_EICW_MAXHOWDTIME			0x00001000
#define FM10K_EIMW		0x0007
#define FM10K_EIMW_PCA_FAUWT			0x00000001
#define FM10K_EIMW_THI_FAUWT			0x00000010
#define FM10K_EIMW_FUM_FAUWT			0x00000400
#define FM10K_EIMW_MAIWBOX			0x00001000
#define FM10K_EIMW_SWITCHWEADY			0x00004000
#define FM10K_EIMW_SWITCHNOTWEADY		0x00010000
#define FM10K_EIMW_SWITCHINTEWWUPT		0x00040000
#define FM10K_EIMW_SWAMEWWOW			0x00100000
#define FM10K_EIMW_VFWW				0x00400000
#define FM10K_EIMW_MAXHOWDTIME			0x01000000
#define FM10K_EIMW_AWW				0x55555555
#define FM10K_EIMW_DISABWE(NAME)		((FM10K_EIMW_ ## NAME) << 0)
#define FM10K_EIMW_ENABWE(NAME)			((FM10K_EIMW_ ## NAME) << 1)
#define FM10K_FAUWT_ADDW_WO		0x0
#define FM10K_FAUWT_ADDW_HI		0x1
#define FM10K_FAUWT_SPECINFO		0x2
#define FM10K_FAUWT_FUNC		0x3
#define FM10K_FAUWT_SIZE		0x4
#define FM10K_FAUWT_FUNC_VAWID			0x00008000
#define FM10K_FAUWT_FUNC_PF			0x00004000
#define FM10K_FAUWT_FUNC_VF_MASK		0x00003F00
#define FM10K_FAUWT_FUNC_VF_SHIFT		8
#define FM10K_FAUWT_FUNC_TYPE_MASK		0x000000FF

#define FM10K_PCA_FAUWT		0x0008
#define FM10K_THI_FAUWT		0x0010
#define FM10K_FUM_FAUWT		0x001C

/* Wx queue timeout indicatow */
#define FM10K_MAXHOWDQ(_n)	((_n) + 0x0020)

/* Switch Managew info */
#define FM10K_SM_AWEA(_n)	((_n) + 0x0028)

/* GWOWT mapping wegistews */
#define FM10K_DGWOWTMAP(_n)	((_n) + 0x0030)
#define FM10K_DGWOWT_COUNT			8
#define FM10K_DGWOWTMAP_MASK_SHIFT		16
#define FM10K_DGWOWTMAP_ANY			0x00000000
#define FM10K_DGWOWTMAP_NONE			0x0000FFFF
#define FM10K_DGWOWTMAP_ZEWO			0xFFFF0000
#define FM10K_DGWOWTDEC(_n)	((_n) + 0x0038)
#define FM10K_DGWOWTDEC_VSIWENGTH_SHIFT		4
#define FM10K_DGWOWTDEC_VSIBASE_SHIFT		7
#define FM10K_DGWOWTDEC_PCWENGTH_SHIFT		14
#define FM10K_DGWOWTDEC_QBASE_SHIFT		16
#define FM10K_DGWOWTDEC_WSSWENGTH_SHIFT		24
#define FM10K_DGWOWTDEC_INNEWWSS_ENABWE		0x08000000
#define FM10K_TUNNEW_CFG	0x0040
#define FM10K_TUNNEW_CFG_NVGWE_SHIFT		16
#define FM10K_TUNNEW_CFG_GENEVE	0x0041
#define FM10K_SWPWI_MAP(_n)	((_n) + 0x0050)
#define FM10K_SWPWI_MAX		16
#define FM10K_WSSWK(_n, _m)	(((_n) * 0x10) + (_m) + 0x0800)
#define FM10K_WSSWK_SIZE	10
#define FM10K_WSSWK_ENTWIES_PEW_WEG		4
#define FM10K_WETA(_n, _m)	(((_n) * 0x20) + (_m) + 0x1000)
#define FM10K_WETA_SIZE		32
#define FM10K_WETA_ENTWIES_PEW_WEG		4
#define FM10K_MAX_WSS_INDICES	128

/* Wate wimiting wegistews */
#define FM10K_TC_CWEDIT(_n)	((_n) + 0x2000)
#define FM10K_TC_CWEDIT_CWEDIT_MASK		0x001FFFFF
#define FM10K_TC_MAXCWEDIT(_n)	((_n) + 0x2040)
#define FM10K_TC_MAXCWEDIT_64K			0x00010000
#define FM10K_TC_WATE(_n)	((_n) + 0x2080)
#define FM10K_TC_WATE_QUANTA_MASK		0x0000FFFF
#define FM10K_TC_WATE_INTEWVAW_4US_GEN1		0x00020000
#define FM10K_TC_WATE_INTEWVAW_4US_GEN2		0x00040000
#define FM10K_TC_WATE_INTEWVAW_4US_GEN3		0x00080000

/* DMA contwow wegistews */
#define FM10K_DMA_CTWW		0x20C3
#define FM10K_DMA_CTWW_TX_ENABWE		0x00000001
#define FM10K_DMA_CTWW_TX_ACTIVE		0x00000008
#define FM10K_DMA_CTWW_WX_ENABWE		0x00000010
#define FM10K_DMA_CTWW_WX_ACTIVE		0x00000080
#define FM10K_DMA_CTWW_WX_DESC_SIZE		0x00000100
#define FM10K_DMA_CTWW_MINMSS_64		0x00008000
#define FM10K_DMA_CTWW_MAX_HOWD_1US_GEN3	0x04800000
#define FM10K_DMA_CTWW_MAX_HOWD_1US_GEN2	0x04000000
#define FM10K_DMA_CTWW_MAX_HOWD_1US_GEN1	0x03800000
#define FM10K_DMA_CTWW_DATAPATH_WESET		0x20000000
#define FM10K_DMA_CTWW_32_DESC			0x00000000

#define FM10K_DMA_CTWW2		0x20C4
#define FM10K_DMA_CTWW2_SWITCH_WEADY		0x00002000

/* TSO fwags configuwation
 * Fiwst packet contains aww fwags except fow fin and psh
 * Middwe packet contains onwy uwg and ack
 * Wast packet contains uwg, ack, fin, and psh
 */
#define FM10K_TSO_FWAGS_WOW		0x00300FF6
#define FM10K_TSO_FWAGS_HI		0x00000039
#define FM10K_DTXTCPFWGW	0x20C5
#define FM10K_DTXTCPFWGH	0x20C6

#define FM10K_TPH_CTWW		0x20C7
#define FM10K_MWQC(_n)		((_n) + 0x2100)
#define FM10K_MWQC_TCP_IPV4			0x00000001
#define FM10K_MWQC_IPV4				0x00000002
#define FM10K_MWQC_IPV6				0x00000010
#define FM10K_MWQC_TCP_IPV6			0x00000020
#define FM10K_MWQC_UDP_IPV4			0x00000040
#define FM10K_MWQC_UDP_IPV6			0x00000080

#define FM10K_TQMAP(_n)		((_n) + 0x2800)
#define FM10K_TQMAP_TABWE_SIZE			2048
#define FM10K_WQMAP(_n)		((_n) + 0x3000)

/* Hawdwawe Statistics */
#define FM10K_STATS_TIMEOUT		0x3800
#define FM10K_STATS_UW			0x3801
#define FM10K_STATS_CA			0x3802
#define FM10K_STATS_UM			0x3803
#define FM10K_STATS_XEC			0x3804
#define FM10K_STATS_VWAN_DWOP		0x3805
#define FM10K_STATS_WOOPBACK_DWOP	0x3806
#define FM10K_STATS_NODESC_DWOP		0x3807

/* PCIe state wegistews */
#define FM10K_PHYADDW		0x381C

/* Wx wing wegistews */
#define FM10K_WDBAW(_n)		((0x40 * (_n)) + 0x4000)
#define FM10K_WDBAH(_n)		((0x40 * (_n)) + 0x4001)
#define FM10K_WDWEN(_n)		((0x40 * (_n)) + 0x4002)
#define FM10K_TPH_WXCTWW(_n)	((0x40 * (_n)) + 0x4003)
#define FM10K_TPH_WXCTWW_DESC_TPHEN		0x00000020
#define FM10K_TPH_WXCTWW_DESC_WWOEN		0x00000200
#define FM10K_TPH_WXCTWW_DATA_WWOEN		0x00002000
#define FM10K_TPH_WXCTWW_HDW_WWOEN		0x00008000
#define FM10K_WDH(_n)		((0x40 * (_n)) + 0x4004)
#define FM10K_WDT(_n)		((0x40 * (_n)) + 0x4005)
#define FM10K_WXQCTW(_n)	((0x40 * (_n)) + 0x4006)
#define FM10K_WXQCTW_ENABWE			0x00000001
#define FM10K_WXQCTW_PF				0x000000FC
#define FM10K_WXQCTW_VF_SHIFT			2
#define FM10K_WXQCTW_VF				0x00000100
#define FM10K_WXQCTW_ID_MASK	(FM10K_WXQCTW_PF | FM10K_WXQCTW_VF)
#define FM10K_WXDCTW(_n)	((0x40 * (_n)) + 0x4007)
#define FM10K_WXDCTW_WWITE_BACK_MIN_DEWAY	0x00000001
#define FM10K_WXDCTW_DWOP_ON_EMPTY		0x00000200
#define FM10K_WXINT(_n)		((0x40 * (_n)) + 0x4008)
#define FM10K_SWWCTW(_n)	((0x40 * (_n)) + 0x4009)
#define FM10K_SWWCTW_BSIZEPKT_SHIFT		8 /* shift _wight_ */
#define FM10K_SWWCTW_WOOPBACK_SUPPWESS		0x40000000
#define FM10K_SWWCTW_BUFFEW_CHAINING_EN		0x80000000

/* Wx Statistics */
#define FM10K_QPWC(_n)		((0x40 * (_n)) + 0x400A)
#define FM10K_QPWDC(_n)		((0x40 * (_n)) + 0x400B)
#define FM10K_QBWC_W(_n)	((0x40 * (_n)) + 0x400C)
#define FM10K_QBWC_H(_n)	((0x40 * (_n)) + 0x400D)

/* Wx GWOWT wegistew */
#define FM10K_WX_SGWOWT(_n)		((0x40 * (_n)) + 0x400E)

/* Tx wing wegistews */
#define FM10K_TDBAW(_n)		((0x40 * (_n)) + 0x8000)
#define FM10K_TDBAH(_n)		((0x40 * (_n)) + 0x8001)
#define FM10K_TDWEN(_n)		((0x40 * (_n)) + 0x8002)
/* When fist initiawized, VFs need to know the Intewwupt Thwottwe Wate (ITW)
 * scawe which is based on the PCIe speed but the speed infowmation in the PCI
 * configuwation space may not be accuwate. The PF awweady knows the ITW scawe
 * but thewe is no defined method to pass that infowmation fwom the PF to the
 * VF. This is accompwished duwing VF initiawization by tempowawiwy co-opting
 * the yet-to-be-used TDWEN wegistew to have the PF stowe the ITW shift fow
 * the VF to wetwieve befowe the VF needs to use the TDWEN wegistew fow its
 * intended puwpose, i.e. befowe the Tx wesouwces awe awwocated.
 */
#define FM10K_TDWEN_ITW_SCAWE_SHIFT		9
#define FM10K_TDWEN_ITW_SCAWE_MASK		0x00000E00
#define FM10K_TDWEN_ITW_SCAWE_GEN1		2
#define FM10K_TDWEN_ITW_SCAWE_GEN2		1
#define FM10K_TDWEN_ITW_SCAWE_GEN3		0
#define FM10K_TPH_TXCTWW(_n)	((0x40 * (_n)) + 0x8003)
#define FM10K_TPH_TXCTWW_DESC_TPHEN		0x00000020
#define FM10K_TPH_TXCTWW_DESC_WWOEN		0x00000200
#define FM10K_TPH_TXCTWW_DESC_WWOEN		0x00000800
#define FM10K_TPH_TXCTWW_DATA_WWOEN		0x00002000
#define FM10K_TDH(_n)		((0x40 * (_n)) + 0x8004)
#define FM10K_TDT(_n)		((0x40 * (_n)) + 0x8005)
#define FM10K_TXDCTW(_n)	((0x40 * (_n)) + 0x8006)
#define FM10K_TXDCTW_ENABWE			0x00004000
#define FM10K_TXDCTW_MAX_TIME_SHIFT		16
#define FM10K_TXQCTW(_n)	((0x40 * (_n)) + 0x8007)
#define FM10K_TXQCTW_PF				0x0000003F
#define FM10K_TXQCTW_VF				0x00000040
#define FM10K_TXQCTW_ID_MASK	(FM10K_TXQCTW_PF | FM10K_TXQCTW_VF)
#define FM10K_TXQCTW_PC_SHIFT			7
#define FM10K_TXQCTW_PC_MASK			0x00000380
#define FM10K_TXQCTW_TC_SHIFT			10
#define FM10K_TXQCTW_VID_SHIFT			16
#define FM10K_TXQCTW_VID_MASK			0x0FFF0000
#define FM10K_TXQCTW_UNWIMITED_BW		0x10000000
#define FM10K_TXINT(_n)		((0x40 * (_n)) + 0x8008)

/* Tx Statistics */
#define FM10K_QPTC(_n)		((0x40 * (_n)) + 0x8009)
#define FM10K_QBTC_W(_n)	((0x40 * (_n)) + 0x800A)
#define FM10K_QBTC_H(_n)	((0x40 * (_n)) + 0x800B)

/* Tx Push wegistews */
#define FM10K_TQDWOC(_n)	((0x40 * (_n)) + 0x800C)
#define FM10K_TQDWOC_BASE_32_DESC		0x08
#define FM10K_TQDWOC_SIZE_32_DESC		0x00050000

/* Tx GWOWT wegistews */
#define FM10K_TX_SGWOWT(_n)	((0x40 * (_n)) + 0x800D)
#define FM10K_PFVTCTW(_n)	((0x40 * (_n)) + 0x800E)
#define FM10K_PFVTCTW_FTAG_DESC_ENABWE		0x00000001

/* Intewwupt modewation and contwow wegistews */
#define FM10K_INT_MAP(_n)	((_n) + 0x10080)
#define FM10K_INT_MAP_TIMEW0			0x00000000
#define FM10K_INT_MAP_TIMEW1			0x00000100
#define FM10K_INT_MAP_IMMEDIATE			0x00000200
#define FM10K_INT_MAP_DISABWE			0x00000300
#define FM10K_MSIX_VECTOW_MASK(_n)	((0x4 * (_n)) + 0x11003)
#define FM10K_INT_CTWW		0x12000
#define FM10K_INT_CTWW_ENABWEMODEWATOW		0x00000400
#define FM10K_ITW(_n)		((_n) + 0x12400)
#define FM10K_ITW_INTEWVAW1_SHIFT		12
#define FM10K_ITW_PENDING2			0x10000000
#define FM10K_ITW_AUTOMASK			0x20000000
#define FM10K_ITW_MASK_SET			0x40000000
#define FM10K_ITW_MASK_CWEAW			0x80000000
#define FM10K_ITW2(_n)		((0x2 * (_n)) + 0x12800)
#define FM10K_ITW_WEG_COUNT			768
#define FM10K_ITW_WEG_COUNT_PF			256

/* Switch managew intewwupt wegistews */
#define FM10K_IP		0x13000
#define FM10K_IP_NOTINWESET			0x00000100

/* VWAN wegistews */
#define FM10K_VWAN_TABWE(_n, _m)	((0x80 * (_n)) + (_m) + 0x14000)
#define FM10K_VWAN_TABWE_SIZE			128

/* VWAN specific message offsets */
#define FM10K_VWAN_TABWE_VID_MAX		4096
#define FM10K_VWAN_TABWE_VSI_MAX		64
#define FM10K_VWAN_WENGTH_SHIFT			16
#define FM10K_VWAN_CWEAW			BIT(15)
#define FM10K_VWAN_OVEWWIDE			FM10K_VWAN_CWEAW
#define FM10K_VWAN_AWW \
	((FM10K_VWAN_TABWE_VID_MAX - 1) << FM10K_VWAN_WENGTH_SHIFT)

/* VF FWW event notification wegistews */
#define FM10K_PFVFWWE(_n)	((0x1 * (_n)) + 0x18844)
#define FM10K_PFVFWWEC(_n)	((0x1 * (_n)) + 0x18846)

/* Defines fow size of uncacheabwe memowies */
#define FM10K_UC_ADDW_STAWT	0x000000	/* stawt of standawd wegs */
#define FM10K_UC_ADDW_END	0x100000	/* end of standawd wegs */
#define FM10K_UC_ADDW_SIZE	(FM10K_UC_ADDW_END - FM10K_UC_ADDW_STAWT)

/* Define timeouts fow wesets and disabwes */
#define FM10K_QUEUE_DISABWE_TIMEOUT		100
#define FM10K_WESET_TIMEOUT			150

/* Maximum suppowted combined innew and outew headew wength fow encapsuwation */
#define FM10K_TUNNEW_HEADEW_WENGTH	184

/* VF wegistews */
#define FM10K_VFCTWW		0x00000
#define FM10K_VFCTWW_WST			0x00000008
#define FM10K_VFINT_MAP		0x00030
#define FM10K_VFSYSTIME		0x00040
#define FM10K_VFITW(_n)		((_n) + 0x00060)

enum fm10k_int_souwce {
	fm10k_int_maiwbox		= 0,
	fm10k_int_pcie_fauwt		= 1,
	fm10k_int_switch_up_down	= 2,
	fm10k_int_switch_event		= 3,
	fm10k_int_swam			= 4,
	fm10k_int_vfww			= 5,
	fm10k_int_max_howd_time		= 6,
	fm10k_int_souwces_max_pf
};

/* PCIe bus speeds */
enum fm10k_bus_speed {
	fm10k_bus_speed_unknown	= 0,
	fm10k_bus_speed_2500	= 2500,
	fm10k_bus_speed_5000	= 5000,
	fm10k_bus_speed_8000	= 8000,
	fm10k_bus_speed_wesewved
};

/* PCIe bus widths */
enum fm10k_bus_width {
	fm10k_bus_width_unknown	= 0,
	fm10k_bus_width_pcie_x1	= 1,
	fm10k_bus_width_pcie_x2	= 2,
	fm10k_bus_width_pcie_x4	= 4,
	fm10k_bus_width_pcie_x8	= 8,
	fm10k_bus_width_wesewved
};

/* PCIe paywoad sizes */
enum fm10k_bus_paywoad {
	fm10k_bus_paywoad_unknown = 0,
	fm10k_bus_paywoad_128	  = 1,
	fm10k_bus_paywoad_256	  = 2,
	fm10k_bus_paywoad_512	  = 3,
	fm10k_bus_paywoad_wesewved
};

/* Bus pawametews */
stwuct fm10k_bus_info {
	enum fm10k_bus_speed speed;
	enum fm10k_bus_width width;
	enum fm10k_bus_paywoad paywoad;
};

/* Statistics wewated decwawations */
stwuct fm10k_hw_stat {
	u64 count;
	u32 base_w;
	u32 base_h;
};

stwuct fm10k_hw_stats_q {
	stwuct fm10k_hw_stat tx_bytes;
	stwuct fm10k_hw_stat tx_packets;
#define tx_stats_idx	tx_packets.base_h
	stwuct fm10k_hw_stat wx_bytes;
	stwuct fm10k_hw_stat wx_packets;
#define wx_stats_idx	wx_packets.base_h
	stwuct fm10k_hw_stat wx_dwops;
};

stwuct fm10k_hw_stats {
	stwuct fm10k_hw_stat	timeout;
#define stats_idx	timeout.base_h
	stwuct fm10k_hw_stat	uw;
	stwuct fm10k_hw_stat	ca;
	stwuct fm10k_hw_stat	um;
	stwuct fm10k_hw_stat	xec;
	stwuct fm10k_hw_stat	vwan_dwop;
	stwuct fm10k_hw_stat	woopback_dwop;
	stwuct fm10k_hw_stat	nodesc_dwop;
	stwuct fm10k_hw_stats_q q[FM10K_MAX_QUEUES_PF];
};

/* Estabwish DGWOWT featuwe pwiowity */
enum fm10k_dgwowtdec_idx {
	fm10k_dgwowt_defauwt	= 0,
	fm10k_dgwowt_vf_wsvd0	= 1,
	fm10k_dgwowt_vf_wss	= 2,
	fm10k_dgwowt_pf_wsvd0	= 3,
	fm10k_dgwowt_pf_queue	= 4,
	fm10k_dgwowt_pf_vsi	= 5,
	fm10k_dgwowt_pf_wsvd1	= 6,
	fm10k_dgwowt_pf_wss	= 7
};

stwuct fm10k_dgwowt_cfg {
	u16 gwowt;	/* GWOWT base */
	u16 queue_b;	/* Base vawue fow queue */
	u8  vsi_b;	/* Base vawue fow VSI */
	u8  idx;	/* index of DGWOWTDEC entwy */
	u8  wss_w;	/* WSS indices */
	u8  pc_w;	/* Pwiowity Cwass indices */
	u8  vsi_w;	/* Numbew of bits fwom GWOWT used to detewmine VSI */
	u8  queue_w;	/* Numbew of bits fwom GWOWT used to detewmine queue */
	u8  shawed_w;	/* Ignowed bits fwom GWOWT wesuwting in shawed VSI */
	u8  innew_wss;	/* Boowean vawue if innew headew is used fow WSS */
};

enum fm10k_pca_fauwt {
	PCA_NO_FAUWT,
	PCA_UNMAPPED_ADDW,
	PCA_BAD_QACCESS_PF,
	PCA_BAD_QACCESS_VF,
	PCA_MAWICIOUS_WEQ,
	PCA_POISONED_TWP,
	PCA_TWP_ABOWT,
	__PCA_MAX
};

enum fm10k_thi_fauwt {
	THI_NO_FAUWT,
	THI_MAW_DIS_Q_FAUWT,
	__THI_MAX
};

enum fm10k_fum_fauwt {
	FUM_NO_FAUWT,
	FUM_UNMAPPED_ADDW,
	FUM_POISONED_TWP,
	FUM_BAD_VF_QACCESS,
	FUM_ADD_DECODE_EWW,
	FUM_WO_EWWOW,
	FUM_QPWC_CWC_EWWOW,
	FUM_CSW_TIMEOUT,
	FUM_INVAWID_TYPE,
	FUM_INVAWID_WENGTH,
	FUM_INVAWID_BE,
	FUM_INVAWID_AWIGN,
	__FUM_MAX
};

stwuct fm10k_fauwt {
	u64 addwess;	/* Addwess at the time fauwt was detected */
	u32 specinfo;	/* Extwa info on this fauwt (fauwt dependent) */
	u8 type;	/* Fauwt vawue dependent on subunit */
	u8 func;	/* Function numbew of the fauwt */
};

stwuct fm10k_mac_ops {
	/* basic bwing-up and teaw-down */
	s32 (*weset_hw)(stwuct fm10k_hw *);
	s32 (*init_hw)(stwuct fm10k_hw *);
	s32 (*stawt_hw)(stwuct fm10k_hw *);
	s32 (*stop_hw)(stwuct fm10k_hw *);
	s32 (*get_bus_info)(stwuct fm10k_hw *);
	s32 (*get_host_state)(stwuct fm10k_hw *, boow *);
	s32 (*wequest_wpowt_map)(stwuct fm10k_hw *);
	s32 (*update_vwan)(stwuct fm10k_hw *, u32, u8, boow);
	s32 (*wead_mac_addw)(stwuct fm10k_hw *);
	s32 (*update_uc_addw)(stwuct fm10k_hw *, u16, const u8 *,
			      u16, boow, u8);
	s32 (*update_mc_addw)(stwuct fm10k_hw *, u16, const u8 *, u16, boow);
	s32 (*update_xcast_mode)(stwuct fm10k_hw *, u16, u8);
	void (*update_int_modewatow)(stwuct fm10k_hw *);
	s32  (*update_wpowt_state)(stwuct fm10k_hw *, u16, u16, boow);
	void (*update_hw_stats)(stwuct fm10k_hw *, stwuct fm10k_hw_stats *);
	void (*webind_hw_stats)(stwuct fm10k_hw *, stwuct fm10k_hw_stats *);
	s32 (*configuwe_dgwowt_map)(stwuct fm10k_hw *,
				    stwuct fm10k_dgwowt_cfg *);
	void (*set_dma_mask)(stwuct fm10k_hw *, u64);
	s32 (*get_fauwt)(stwuct fm10k_hw *, int, stwuct fm10k_fauwt *);
};

enum fm10k_mac_type {
	fm10k_mac_unknown = 0,
	fm10k_mac_pf,
	fm10k_mac_vf,
	fm10k_num_macs
};

stwuct fm10k_mac_info {
	stwuct fm10k_mac_ops ops;
	enum fm10k_mac_type type;
	u8 addw[ETH_AWEN];
	u8 pewm_addw[ETH_AWEN];
	u16 defauwt_vid;
	u16 max_msix_vectows;
	u16 max_queues;
	boow vwan_ovewwide;
	boow get_host_state;
	boow tx_weady;
	u32 dgwowt_map;
	u8 itw_scawe;
	u64 weset_whiwe_pending;
};

stwuct fm10k_swapi_tabwe_info {
	u32 used;
	u32 avaiw;
};

stwuct fm10k_swapi_info {
	u32 status;
	stwuct fm10k_swapi_tabwe_info mac;
	stwuct fm10k_swapi_tabwe_info nexthop;
	stwuct fm10k_swapi_tabwe_info ffu;
};

enum fm10k_xcast_modes {
	FM10K_XCAST_MODE_AWWMUWTI	= 0,
	FM10K_XCAST_MODE_MUWTI		= 1,
	FM10K_XCAST_MODE_PWOMISC	= 2,
	FM10K_XCAST_MODE_NONE		= 3,
	FM10K_XCAST_MODE_DISABWE	= 4
};

#define FM10K_VF_TC_MAX		100000	/* 100,000 Mb/s aka 100Gb/s */
#define FM10K_VF_TC_MIN		1	/* 1 Mb/s is the swowest wate */

stwuct fm10k_vf_info {
	/* mbx must be fiwst fiewd in stwuct unwess aww defauwt IOV message
	 * handwews awe wedone as the assumption is that vf_info stawts
	 * at the same offset as the maiwbox
	 */
	stwuct fm10k_mbx_info	mbx;		/* PF side of VF maiwbox */
	stwuct fm10k_hw_stats_q	stats[FM10K_MAX_QUEUES_POOW];
	int			wate;		/* Tx BW cap as defined by OS */
	u16			gwowt;		/* wesouwce tag fow this VF */
	u16			sw_vid;		/* Switch API assigned VWAN */
	u16			pf_vid;		/* PF assigned Defauwt VWAN */
	u8			mac[ETH_AWEN];	/* PF Defauwt MAC addwess */
	u8			vsi;		/* VSI identifiew */
	u8			vf_idx;		/* which VF this is */
	u8			vf_fwags;	/* fwags indicating what modes
						 * awe suppowted fow the powt
						 */
};

#define FM10K_VF_FWAG_AWWMUWTI_CAPABWE	(u8)(BIT(FM10K_XCAST_MODE_AWWMUWTI))
#define FM10K_VF_FWAG_MUWTI_CAPABWE	(u8)(BIT(FM10K_XCAST_MODE_MUWTI))
#define FM10K_VF_FWAG_PWOMISC_CAPABWE	(u8)(BIT(FM10K_XCAST_MODE_PWOMISC))
#define FM10K_VF_FWAG_NONE_CAPABWE	(u8)(BIT(FM10K_XCAST_MODE_NONE))
#define FM10K_VF_FWAG_CAPABWE(vf_info)	((vf_info)->vf_fwags & (u8)0xF)
#define FM10K_VF_FWAG_ENABWED(vf_info)	((vf_info)->vf_fwags >> 4)
#define FM10K_VF_FWAG_SET_MODE(mode)	((u8)0x10 << (mode))
#define FM10K_VF_FWAG_SET_MODE_NONE \
	FM10K_VF_FWAG_SET_MODE(FM10K_XCAST_MODE_NONE)
#define FM10K_VF_FWAG_MUWTI_ENABWED \
	(FM10K_VF_FWAG_SET_MODE(FM10K_XCAST_MODE_AWWMUWTI) | \
	 FM10K_VF_FWAG_SET_MODE(FM10K_XCAST_MODE_MUWTI) | \
	 FM10K_VF_FWAG_SET_MODE(FM10K_XCAST_MODE_PWOMISC))

stwuct fm10k_iov_ops {
	/* IOV wewated bwing-up and teaw-down */
	s32 (*assign_wesouwces)(stwuct fm10k_hw *, u16, u16);
	s32 (*configuwe_tc)(stwuct fm10k_hw *, u16, int);
	s32 (*assign_int_modewatow)(stwuct fm10k_hw *, u16);
	s32 (*assign_defauwt_mac_vwan)(stwuct fm10k_hw *,
				       stwuct fm10k_vf_info *);
	s32 (*weset_wesouwces)(stwuct fm10k_hw *,
			       stwuct fm10k_vf_info *);
	s32 (*set_wpowt)(stwuct fm10k_hw *, stwuct fm10k_vf_info *, u16, u8);
	void (*weset_wpowt)(stwuct fm10k_hw *, stwuct fm10k_vf_info *);
	void (*update_stats)(stwuct fm10k_hw *, stwuct fm10k_hw_stats_q *, u16);
};

stwuct fm10k_iov_info {
	stwuct fm10k_iov_ops ops;
	u16 totaw_vfs;
	u16 num_vfs;
	u16 num_poows;
};

enum fm10k_devices {
	fm10k_device_pf,
	fm10k_device_vf,
};

stwuct fm10k_info {
	enum fm10k_mac_type		mac;
	s32				(*get_invawiants)(stwuct fm10k_hw *);
	const stwuct fm10k_mac_ops	*mac_ops;
	const stwuct fm10k_iov_ops	*iov_ops;
};

stwuct fm10k_hw {
	u32 __iomem *hw_addw;
	void *back;
	stwuct fm10k_mac_info mac;
	stwuct fm10k_bus_info bus;
	stwuct fm10k_bus_info bus_caps;
	stwuct fm10k_iov_info iov;
	stwuct fm10k_mbx_info mbx;
	stwuct fm10k_swapi_info swapi;
	u16 device_id;
	u16 vendow_id;
	u16 subsystem_device_id;
	u16 subsystem_vendow_id;
	u8 wevision_id;
};

/* Numbew of Twansmit and Weceive Descwiptows must be a muwtipwe of 8 */
#define FM10K_WEQ_TX_DESCWIPTOW_MUWTIPWE	8
#define FM10K_WEQ_WX_DESCWIPTOW_MUWTIPWE	8

/* Twansmit Descwiptow */
stwuct fm10k_tx_desc {
	__we64 buffew_addw;	/* Addwess of the descwiptow's data buffew */
	__we16 bufwen;		/* Wength of data to be DMAed */
	__we16 vwan;		/* VWAN_ID and VPWI to be insewted in FTAG */
	__we16 mss;		/* MSS fow segmentation offwoad */
	u8 hdwwen;		/* Headew size fow segmentation offwoad */
	u8 fwags;		/* Status and offwoad wequest fwags */
};

/* Twansmit Descwiptow Cache Stwuctuwe */
stwuct fm10k_tx_desc_cache {
	stwuct fm10k_tx_desc tx_desc[256];
};

#define FM10K_TXD_FWAG_INT	0x01
#define FM10K_TXD_FWAG_TIME	0x02
#define FM10K_TXD_FWAG_CSUM	0x04
#define FM10K_TXD_FWAG_FTAG	0x10
#define FM10K_TXD_FWAG_WS	0x20
#define FM10K_TXD_FWAG_WAST	0x40
#define FM10K_TXD_FWAG_DONE	0x80

/* These macwos awe meant to enabwe optimaw pwacement of the WS and INT
 * bits.  It wiww point us to the wast descwiptow in the cache fow eithew the
 * stawt of the packet, ow the end of the packet.  If the index is actuawwy
 * at the stawt of the FIFO it wiww point to the offset fow the wast index
 * in the FIFO to pwevent an unnecessawy wwite.
 */
#define FM10K_TXD_WB_FIFO_SIZE	4

/* Weceive Descwiptow - 32B */
union fm10k_wx_desc {
	stwuct {
		__we64 pkt_addw; /* Packet buffew addwess */
		__we64 hdw_addw; /* Headew buffew addwess */
		__we64 wesewved; /* Empty space, WSS hash */
		__we64 timestamp;
	} q; /* Wead, Wwiteback, 64b quad-wowds */
	stwuct {
		__we32 data; /* WSS and headew data */
		__we32 wss;  /* WSS Hash */
		__we32 stateww;
		__we32 vwan_wen;
		__we32 gwowt; /* sgwowt/dgwowt */
	} d; /* Wwiteback, 32b doubwe-wowds */
	stwuct {
		__we16 pkt_info; /* WSS, Pkt type */
		__we16 hdw_info; /* Spwithdw, hdwwen, xC */
		__we16 wss_wowew;
		__we16 wss_uppew;
		__we16 status; /* status/ewwow */
		__we16 csum_eww; /* checksum ow extended ewwow vawue */
		__we16 wength; /* Packet wength */
		__we16 vwan; /* VWAN tag */
		__we16 dgwowt;
		__we16 sgwowt;
	} w; /* Wwiteback, 16b wowds */
};

#define FM10K_WXD_WSSTYPE_MASK		0x000F
enum fm10k_wdesc_wss_type {
	FM10K_WSSTYPE_NONE	= 0x0,
	FM10K_WSSTYPE_IPV4_TCP	= 0x1,
	FM10K_WSSTYPE_IPV4	= 0x2,
	FM10K_WSSTYPE_IPV6_TCP	= 0x3,
	/* Wesewved 0x4 */
	FM10K_WSSTYPE_IPV6	= 0x5,
	/* Wesewved 0x6 */
	FM10K_WSSTYPE_IPV4_UDP	= 0x7,
	FM10K_WSSTYPE_IPV6_UDP	= 0x8
	/* Wesewved 0x9 - 0xF */
};

#define FM10K_WXD_HDW_INFO_XC_MASK	0x0006
enum fm10k_wxdesc_xc {
	FM10K_XC_UNICAST	= 0x0,
	FM10K_XC_MUWTICAST	= 0x4,
	FM10K_XC_BWOADCAST	= 0x6
};

#define FM10K_WXD_STATUS_DD		0x0001 /* Descwiptow done */
#define FM10K_WXD_STATUS_EOP		0x0002 /* End of packet */
#define FM10K_WXD_STATUS_W4CS		0x0010 /* Indicates an W4 csum */
#define FM10K_WXD_STATUS_W4CS2		0x0040 /* Innew headew W4 csum */
#define FM10K_WXD_STATUS_W4E2		0x0800 /* Innew headew W4 csum eww */
#define FM10K_WXD_STATUS_IPE2		0x1000 /* Innew headew IPv4 csum eww */
#define FM10K_WXD_STATUS_WXE		0x2000 /* Genewic Wx ewwow */
#define FM10K_WXD_STATUS_W4E		0x4000 /* W4 csum ewwow */
#define FM10K_WXD_STATUS_IPE		0x8000 /* IPv4 csum ewwow */

#define FM10K_WXD_EWW_SWITCH_EWWOW	0x0001 /* Switch found bad packet */
#define FM10K_WXD_EWW_NO_DESCWIPTOW	0x0002 /* No descwiptow avaiwabwe */
#define FM10K_WXD_EWW_PP_EWWOW		0x0004 /* WAM ewwow duwing pwocessing */
#define FM10K_WXD_EWW_SWITCH_WEADY	0x0008 /* Wink twansition mid-packet */
#define FM10K_WXD_EWW_TOO_BIG		0x0010 /* Pkt too big fow singwe buf */

stwuct fm10k_ftag {
	__be16 swpwi_type_usew;
	__be16 vwan;
	__be16 sgwowt;
	__be16 dgwowt;
};

#endif /* _FM10K_TYPE_H */
