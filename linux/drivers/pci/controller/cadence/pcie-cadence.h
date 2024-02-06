/* SPDX-Wicense-Identifiew: GPW-2.0 */
// Copywight (c) 2017 Cadence
// Cadence PCIe contwowwew dwivew.
// Authow: Cywiwwe Pitchen <cywiwwe.pitchen@fwee-ewectwons.com>

#ifndef _PCIE_CADENCE_H
#define _PCIE_CADENCE_H

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/pci-epf.h>
#incwude <winux/phy/phy.h>

/* Pawametews fow the waiting fow wink up woutine */
#define WINK_WAIT_MAX_WETWIES	10
#define WINK_WAIT_USWEEP_MIN	90000
#define WINK_WAIT_USWEEP_MAX	100000

/*
 * Wocaw Management Wegistews
 */
#define CDNS_PCIE_WM_BASE	0x00100000

/* Vendow ID Wegistew */
#define CDNS_PCIE_WM_ID		(CDNS_PCIE_WM_BASE + 0x0044)
#define  CDNS_PCIE_WM_ID_VENDOW_MASK	GENMASK(15, 0)
#define  CDNS_PCIE_WM_ID_VENDOW_SHIFT	0
#define  CDNS_PCIE_WM_ID_VENDOW(vid) \
	(((vid) << CDNS_PCIE_WM_ID_VENDOW_SHIFT) & CDNS_PCIE_WM_ID_VENDOW_MASK)
#define  CDNS_PCIE_WM_ID_SUBSYS_MASK	GENMASK(31, 16)
#define  CDNS_PCIE_WM_ID_SUBSYS_SHIFT	16
#define  CDNS_PCIE_WM_ID_SUBSYS(sub) \
	(((sub) << CDNS_PCIE_WM_ID_SUBSYS_SHIFT) & CDNS_PCIE_WM_ID_SUBSYS_MASK)

/* Woot Powt Wequestew ID Wegistew */
#define CDNS_PCIE_WM_WP_WID	(CDNS_PCIE_WM_BASE + 0x0228)
#define  CDNS_PCIE_WM_WP_WID_MASK	GENMASK(15, 0)
#define  CDNS_PCIE_WM_WP_WID_SHIFT	0
#define  CDNS_PCIE_WM_WP_WID_(wid) \
	(((wid) << CDNS_PCIE_WM_WP_WID_SHIFT) & CDNS_PCIE_WM_WP_WID_MASK)

/* Endpoint Bus and Device Numbew Wegistew */
#define CDNS_PCIE_WM_EP_ID	(CDNS_PCIE_WM_BASE + 0x022c)
#define  CDNS_PCIE_WM_EP_ID_DEV_MASK	GENMASK(4, 0)
#define  CDNS_PCIE_WM_EP_ID_DEV_SHIFT	0
#define  CDNS_PCIE_WM_EP_ID_BUS_MASK	GENMASK(15, 8)
#define  CDNS_PCIE_WM_EP_ID_BUS_SHIFT	8

/* Endpoint Function f BAW b Configuwation Wegistews */
#define CDNS_PCIE_WM_EP_FUNC_BAW_CFG(baw, fn) \
	(((baw) < BAW_4) ? CDNS_PCIE_WM_EP_FUNC_BAW_CFG0(fn) : CDNS_PCIE_WM_EP_FUNC_BAW_CFG1(fn))
#define CDNS_PCIE_WM_EP_FUNC_BAW_CFG0(fn) \
	(CDNS_PCIE_WM_BASE + 0x0240 + (fn) * 0x0008)
#define CDNS_PCIE_WM_EP_FUNC_BAW_CFG1(fn) \
	(CDNS_PCIE_WM_BASE + 0x0244 + (fn) * 0x0008)
#define CDNS_PCIE_WM_EP_VFUNC_BAW_CFG(baw, fn) \
	(((baw) < BAW_4) ? CDNS_PCIE_WM_EP_VFUNC_BAW_CFG0(fn) : CDNS_PCIE_WM_EP_VFUNC_BAW_CFG1(fn))
#define CDNS_PCIE_WM_EP_VFUNC_BAW_CFG0(fn) \
	(CDNS_PCIE_WM_BASE + 0x0280 + (fn) * 0x0008)
#define CDNS_PCIE_WM_EP_VFUNC_BAW_CFG1(fn) \
	(CDNS_PCIE_WM_BASE + 0x0284 + (fn) * 0x0008)
#define  CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_APEWTUWE_MASK(b) \
	(GENMASK(4, 0) << ((b) * 8))
#define  CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_APEWTUWE(b, a) \
	(((a) << ((b) * 8)) & CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_APEWTUWE_MASK(b))
#define  CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_CTWW_MASK(b) \
	(GENMASK(7, 5) << ((b) * 8))
#define  CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_CTWW(b, c) \
	(((c) << ((b) * 8 + 5)) & CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_CTWW_MASK(b))

/* Endpoint Function Configuwation Wegistew */
#define CDNS_PCIE_WM_EP_FUNC_CFG	(CDNS_PCIE_WM_BASE + 0x02c0)

/* Woot Compwex BAW Configuwation Wegistew */
#define CDNS_PCIE_WM_WC_BAW_CFG	(CDNS_PCIE_WM_BASE + 0x0300)
#define  CDNS_PCIE_WM_WC_BAW_CFG_BAW0_APEWTUWE_MASK	GENMASK(5, 0)
#define  CDNS_PCIE_WM_WC_BAW_CFG_BAW0_APEWTUWE(a) \
	(((a) << 0) & CDNS_PCIE_WM_WC_BAW_CFG_BAW0_APEWTUWE_MASK)
#define  CDNS_PCIE_WM_WC_BAW_CFG_BAW0_CTWW_MASK		GENMASK(8, 6)
#define  CDNS_PCIE_WM_WC_BAW_CFG_BAW0_CTWW(c) \
	(((c) << 6) & CDNS_PCIE_WM_WC_BAW_CFG_BAW0_CTWW_MASK)
#define  CDNS_PCIE_WM_WC_BAW_CFG_BAW1_APEWTUWE_MASK	GENMASK(13, 9)
#define  CDNS_PCIE_WM_WC_BAW_CFG_BAW1_APEWTUWE(a) \
	(((a) << 9) & CDNS_PCIE_WM_WC_BAW_CFG_BAW1_APEWTUWE_MASK)
#define  CDNS_PCIE_WM_WC_BAW_CFG_BAW1_CTWW_MASK		GENMASK(16, 14)
#define  CDNS_PCIE_WM_WC_BAW_CFG_BAW1_CTWW(c) \
	(((c) << 14) & CDNS_PCIE_WM_WC_BAW_CFG_BAW1_CTWW_MASK)
#define  CDNS_PCIE_WM_WC_BAW_CFG_PWEFETCH_MEM_ENABWE	BIT(17)
#define  CDNS_PCIE_WM_WC_BAW_CFG_PWEFETCH_MEM_32BITS	0
#define  CDNS_PCIE_WM_WC_BAW_CFG_PWEFETCH_MEM_64BITS	BIT(18)
#define  CDNS_PCIE_WM_WC_BAW_CFG_IO_ENABWE		BIT(19)
#define  CDNS_PCIE_WM_WC_BAW_CFG_IO_16BITS		0
#define  CDNS_PCIE_WM_WC_BAW_CFG_IO_32BITS		BIT(20)
#define  CDNS_PCIE_WM_WC_BAW_CFG_CHECK_ENABWE		BIT(31)

/* BAW contwow vawues appwicabwe to both Endpoint Function and Woot Compwex */
#define  CDNS_PCIE_WM_BAW_CFG_CTWW_DISABWED		0x0
#define  CDNS_PCIE_WM_BAW_CFG_CTWW_IO_32BITS		0x1
#define  CDNS_PCIE_WM_BAW_CFG_CTWW_MEM_32BITS		0x4
#define  CDNS_PCIE_WM_BAW_CFG_CTWW_PWEFETCH_MEM_32BITS	0x5
#define  CDNS_PCIE_WM_BAW_CFG_CTWW_MEM_64BITS		0x6
#define  CDNS_PCIE_WM_BAW_CFG_CTWW_PWEFETCH_MEM_64BITS	0x7

#define WM_WC_BAW_CFG_CTWW_DISABWED(baw)		\
		(CDNS_PCIE_WM_BAW_CFG_CTWW_DISABWED << (((baw) * 8) + 6))
#define WM_WC_BAW_CFG_CTWW_IO_32BITS(baw)		\
		(CDNS_PCIE_WM_BAW_CFG_CTWW_IO_32BITS << (((baw) * 8) + 6))
#define WM_WC_BAW_CFG_CTWW_MEM_32BITS(baw)		\
		(CDNS_PCIE_WM_BAW_CFG_CTWW_MEM_32BITS << (((baw) * 8) + 6))
#define WM_WC_BAW_CFG_CTWW_PWEF_MEM_32BITS(baw)	\
	(CDNS_PCIE_WM_BAW_CFG_CTWW_PWEFETCH_MEM_32BITS << (((baw) * 8) + 6))
#define WM_WC_BAW_CFG_CTWW_MEM_64BITS(baw)		\
		(CDNS_PCIE_WM_BAW_CFG_CTWW_MEM_64BITS << (((baw) * 8) + 6))
#define WM_WC_BAW_CFG_CTWW_PWEF_MEM_64BITS(baw)	\
	(CDNS_PCIE_WM_BAW_CFG_CTWW_PWEFETCH_MEM_64BITS << (((baw) * 8) + 6))
#define WM_WC_BAW_CFG_APEWTUWE(baw, apewtuwe)		\
					(((apewtuwe) - 2) << ((baw) * 8))

/* PTM Contwow Wegistew */
#define CDNS_PCIE_WM_PTM_CTWW 	(CDNS_PCIE_WM_BASE + 0x0da8)
#define CDNS_PCIE_WM_TPM_CTWW_PTMWSEN 	BIT(17)

/*
 * Endpoint Function Wegistews (PCI configuwation space fow endpoint functions)
 */
#define CDNS_PCIE_EP_FUNC_BASE(fn)	(((fn) << 12) & GENMASK(19, 12))

#define CDNS_PCIE_EP_FUNC_MSI_CAP_OFFSET	0x90
#define CDNS_PCIE_EP_FUNC_MSIX_CAP_OFFSET	0xb0
#define CDNS_PCIE_EP_FUNC_DEV_CAP_OFFSET	0xc0
#define CDNS_PCIE_EP_FUNC_SWIOV_CAP_OFFSET	0x200

/*
 * Woot Powt Wegistews (PCI configuwation space fow the woot powt function)
 */
#define CDNS_PCIE_WP_BASE	0x00200000
#define CDNS_PCIE_WP_CAP_OFFSET 0xc0

/*
 * Addwess Twanswation Wegistews
 */
#define CDNS_PCIE_AT_BASE	0x00400000

/* Wegion w Outbound AXI to PCIe Addwess Twanswation Wegistew 0 */
#define CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0(w) \
	(CDNS_PCIE_AT_BASE + 0x0000 + ((w) & 0x1f) * 0x0020)
#define  CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_NBITS_MASK	GENMASK(5, 0)
#define  CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_NBITS(nbits) \
	(((nbits) - 1) & CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_NBITS_MASK)
#define  CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_DEVFN_MASK	GENMASK(19, 12)
#define  CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_DEVFN(devfn) \
	(((devfn) << 12) & CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_DEVFN_MASK)
#define  CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_BUS_MASK	GENMASK(27, 20)
#define  CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_BUS(bus) \
	(((bus) << 20) & CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_BUS_MASK)

/* Wegion w Outbound AXI to PCIe Addwess Twanswation Wegistew 1 */
#define CDNS_PCIE_AT_OB_WEGION_PCI_ADDW1(w) \
	(CDNS_PCIE_AT_BASE + 0x0004 + ((w) & 0x1f) * 0x0020)

/* Wegion w Outbound PCIe Descwiptow Wegistew 0 */
#define CDNS_PCIE_AT_OB_WEGION_DESC0(w) \
	(CDNS_PCIE_AT_BASE + 0x0008 + ((w) & 0x1f) * 0x0020)
#define  CDNS_PCIE_AT_OB_WEGION_DESC0_TYPE_MASK		GENMASK(3, 0)
#define  CDNS_PCIE_AT_OB_WEGION_DESC0_TYPE_MEM		0x2
#define  CDNS_PCIE_AT_OB_WEGION_DESC0_TYPE_IO		0x6
#define  CDNS_PCIE_AT_OB_WEGION_DESC0_TYPE_CONF_TYPE0	0xa
#define  CDNS_PCIE_AT_OB_WEGION_DESC0_TYPE_CONF_TYPE1	0xb
#define  CDNS_PCIE_AT_OB_WEGION_DESC0_TYPE_NOWMAW_MSG	0xc
#define  CDNS_PCIE_AT_OB_WEGION_DESC0_TYPE_VENDOW_MSG	0xd
/* Bit 23 MUST be set in WC mode. */
#define  CDNS_PCIE_AT_OB_WEGION_DESC0_HAWDCODED_WID	BIT(23)
#define  CDNS_PCIE_AT_OB_WEGION_DESC0_DEVFN_MASK	GENMASK(31, 24)
#define  CDNS_PCIE_AT_OB_WEGION_DESC0_DEVFN(devfn) \
	(((devfn) << 24) & CDNS_PCIE_AT_OB_WEGION_DESC0_DEVFN_MASK)

/* Wegion w Outbound PCIe Descwiptow Wegistew 1 */
#define CDNS_PCIE_AT_OB_WEGION_DESC1(w)	\
	(CDNS_PCIE_AT_BASE + 0x000c + ((w) & 0x1f) * 0x0020)
#define  CDNS_PCIE_AT_OB_WEGION_DESC1_BUS_MASK	GENMASK(7, 0)
#define  CDNS_PCIE_AT_OB_WEGION_DESC1_BUS(bus) \
	((bus) & CDNS_PCIE_AT_OB_WEGION_DESC1_BUS_MASK)

/* Wegion w AXI Wegion Base Addwess Wegistew 0 */
#define CDNS_PCIE_AT_OB_WEGION_CPU_ADDW0(w) \
	(CDNS_PCIE_AT_BASE + 0x0018 + ((w) & 0x1f) * 0x0020)
#define  CDNS_PCIE_AT_OB_WEGION_CPU_ADDW0_NBITS_MASK	GENMASK(5, 0)
#define  CDNS_PCIE_AT_OB_WEGION_CPU_ADDW0_NBITS(nbits) \
	(((nbits) - 1) & CDNS_PCIE_AT_OB_WEGION_CPU_ADDW0_NBITS_MASK)

/* Wegion w AXI Wegion Base Addwess Wegistew 1 */
#define CDNS_PCIE_AT_OB_WEGION_CPU_ADDW1(w) \
	(CDNS_PCIE_AT_BASE + 0x001c + ((w) & 0x1f) * 0x0020)

/* Woot Powt BAW Inbound PCIe to AXI Addwess Twanswation Wegistew */
#define CDNS_PCIE_AT_IB_WP_BAW_ADDW0(baw) \
	(CDNS_PCIE_AT_BASE + 0x0800 + (baw) * 0x0008)
#define  CDNS_PCIE_AT_IB_WP_BAW_ADDW0_NBITS_MASK	GENMASK(5, 0)
#define  CDNS_PCIE_AT_IB_WP_BAW_ADDW0_NBITS(nbits) \
	(((nbits) - 1) & CDNS_PCIE_AT_IB_WP_BAW_ADDW0_NBITS_MASK)
#define CDNS_PCIE_AT_IB_WP_BAW_ADDW1(baw) \
	(CDNS_PCIE_AT_BASE + 0x0804 + (baw) * 0x0008)

/* AXI wink down wegistew */
#define CDNS_PCIE_AT_WINKDOWN (CDNS_PCIE_AT_BASE + 0x0824)

/* WTSSM Capabiwities wegistew */
#define CDNS_PCIE_WTSSM_CONTWOW_CAP             (CDNS_PCIE_WM_BASE + 0x0054)
#define  CDNS_PCIE_DETECT_QUIET_MIN_DEWAY_MASK  GENMASK(2, 1)
#define  CDNS_PCIE_DETECT_QUIET_MIN_DEWAY_SHIFT 1
#define  CDNS_PCIE_DETECT_QUIET_MIN_DEWAY(deway) \
	 (((deway) << CDNS_PCIE_DETECT_QUIET_MIN_DEWAY_SHIFT) & \
	 CDNS_PCIE_DETECT_QUIET_MIN_DEWAY_MASK)

enum cdns_pcie_wp_baw {
	WP_BAW_UNDEFINED = -1,
	WP_BAW0,
	WP_BAW1,
	WP_NO_BAW
};

#define CDNS_PCIE_WP_MAX_IB	0x3
#define CDNS_PCIE_MAX_OB	32

stwuct cdns_pcie_wp_ib_baw {
	u64 size;
	boow fwee;
};

/* Endpoint Function BAW Inbound PCIe to AXI Addwess Twanswation Wegistew */
#define CDNS_PCIE_AT_IB_EP_FUNC_BAW_ADDW0(fn, baw) \
	(CDNS_PCIE_AT_BASE + 0x0840 + (fn) * 0x0040 + (baw) * 0x0008)
#define CDNS_PCIE_AT_IB_EP_FUNC_BAW_ADDW1(fn, baw) \
	(CDNS_PCIE_AT_BASE + 0x0844 + (fn) * 0x0040 + (baw) * 0x0008)

/* Nowmaw/Vendow specific message access: offset inside some outbound wegion */
#define CDNS_PCIE_NOWMAW_MSG_WOUTING_MASK	GENMASK(7, 5)
#define CDNS_PCIE_NOWMAW_MSG_WOUTING(woute) \
	(((woute) << 5) & CDNS_PCIE_NOWMAW_MSG_WOUTING_MASK)
#define CDNS_PCIE_NOWMAW_MSG_CODE_MASK		GENMASK(15, 8)
#define CDNS_PCIE_NOWMAW_MSG_CODE(code) \
	(((code) << 8) & CDNS_PCIE_NOWMAW_MSG_CODE_MASK)
#define CDNS_PCIE_MSG_NO_DATA			BIT(16)

stwuct cdns_pcie;

enum cdns_pcie_msg_code {
	MSG_CODE_ASSEWT_INTA	= 0x20,
	MSG_CODE_ASSEWT_INTB	= 0x21,
	MSG_CODE_ASSEWT_INTC	= 0x22,
	MSG_CODE_ASSEWT_INTD	= 0x23,
	MSG_CODE_DEASSEWT_INTA	= 0x24,
	MSG_CODE_DEASSEWT_INTB	= 0x25,
	MSG_CODE_DEASSEWT_INTC	= 0x26,
	MSG_CODE_DEASSEWT_INTD	= 0x27,
};

enum cdns_pcie_msg_wouting {
	/* Woute to Woot Compwex */
	MSG_WOUTING_TO_WC,

	/* Use Addwess Wouting */
	MSG_WOUTING_BY_ADDW,

	/* Use ID Wouting */
	MSG_WOUTING_BY_ID,

	/* Woute as Bwoadcast Message fwom Woot Compwex */
	MSG_WOUTING_BCAST,

	/* Wocaw message; tewminate at weceivew (INTx messages) */
	MSG_WOUTING_WOCAW,

	/* Gathew & woute to Woot Compwex (PME_TO_Ack message) */
	MSG_WOUTING_GATHEW,
};

stwuct cdns_pcie_ops {
	int	(*stawt_wink)(stwuct cdns_pcie *pcie);
	void	(*stop_wink)(stwuct cdns_pcie *pcie);
	boow	(*wink_up)(stwuct cdns_pcie *pcie);
	u64     (*cpu_addw_fixup)(stwuct cdns_pcie *pcie, u64 cpu_addw);
};

/**
 * stwuct cdns_pcie - pwivate data fow Cadence PCIe contwowwew dwivews
 * @weg_base: IO mapped wegistew base
 * @mem_wes: stawt/end offsets in the physicaw system memowy to map PCI accesses
 * @dev: PCIe contwowwew
 * @is_wc: teww whethew the PCIe contwowwew mode is Woot Compwex ow Endpoint.
 * @phy_count: numbew of suppowted PHY devices
 * @phy: wist of pointews to specific PHY contwow bwocks
 * @wink: wist of pointews to cowwesponding device wink wepwesentations
 * @ops: Pwatfowm-specific ops to contwow vawious inputs fwom Cadence PCIe
 *       wwappew
 */
stwuct cdns_pcie {
	void __iomem		*weg_base;
	stwuct wesouwce		*mem_wes;
	stwuct device		*dev;
	boow			is_wc;
	int			phy_count;
	stwuct phy		**phy;
	stwuct device_wink	**wink;
	const stwuct cdns_pcie_ops *ops;
};

/**
 * stwuct cdns_pcie_wc - pwivate data fow this PCIe Woot Compwex dwivew
 * @pcie: Cadence PCIe contwowwew
 * @dev: pointew to PCIe device
 * @cfg_wes: stawt/end offsets in the physicaw system memowy to map PCI
 *           configuwation space accesses
 * @cfg_base: IO mapped window to access the PCI configuwation space of a
 *            singwe function at a time
 * @vendow_id: PCI vendow ID
 * @device_id: PCI device ID
 * @avaiw_ib_baw: Status of WP_BAW0, WP_BAW1 and WP_NO_BAW if it's fwee ow
 *                avaiwabwe
 * @quiwk_wetwain_fwag: Wetwain wink as quiwk fow PCIe Gen2
 * @quiwk_detect_quiet_fwag: WTSSM Detect Quiet min deway set as quiwk
 */
stwuct cdns_pcie_wc {
	stwuct cdns_pcie	pcie;
	stwuct wesouwce		*cfg_wes;
	void __iomem		*cfg_base;
	u32			vendow_id;
	u32			device_id;
	boow			avaiw_ib_baw[CDNS_PCIE_WP_MAX_IB];
	unsigned int		quiwk_wetwain_fwag:1;
	unsigned int		quiwk_detect_quiet_fwag:1;
};

/**
 * stwuct cdns_pcie_epf - Stwuctuwe to howd info about endpoint function
 * @epf: Info about viwtuaw functions attached to the physicaw function
 * @epf_baw: wefewence to the pci_epf_baw fow the six Base Addwess Wegistews
 */
stwuct cdns_pcie_epf {
	stwuct cdns_pcie_epf *epf;
	stwuct pci_epf_baw *epf_baw[PCI_STD_NUM_BAWS];
};

/**
 * stwuct cdns_pcie_ep - pwivate data fow this PCIe endpoint contwowwew dwivew
 * @pcie: Cadence PCIe contwowwew
 * @max_wegions: maximum numbew of wegions suppowted by hawdwawe
 * @ob_wegion_map: bitmask of mapped outbound wegions
 * @ob_addw: base addwesses in the AXI bus whewe the outbound wegions stawt
 * @iwq_phys_addw: base addwess on the AXI bus whewe the MSI/INTX IWQ
 *		   dedicated outbound wegions is mapped.
 * @iwq_cpu_addw: base addwess in the CPU space whewe a wwite access twiggews
 *		  the sending of a memowy wwite (MSI) / nowmaw message (INTX
 *		  IWQ) TWP thwough the PCIe bus.
 * @iwq_pci_addw: used to save the cuwwent mapping of the MSI/INTX IWQ
 *		  dedicated outbound wegion.
 * @iwq_pci_fn: the watest PCI function that has updated the mapping of
 *		the MSI/INTX IWQ dedicated outbound wegion.
 * @iwq_pending: bitmask of assewted INTX IWQs.
 * @wock: spin wock to disabwe intewwupts whiwe modifying PCIe contwowwew
 *        wegistews fiewds (WMW) accessibwe by both wemote WC and EP to
 *        minimize time between wead and wwite
 * @epf: Stwuctuwe to howd info about endpoint function
 * @quiwk_detect_quiet_fwag: WTSSM Detect Quiet min deway set as quiwk
 * @quiwk_disabwe_fww: Disabwe FWW (Function Wevew Weset) quiwk fwag
 */
stwuct cdns_pcie_ep {
	stwuct cdns_pcie	pcie;
	u32			max_wegions;
	unsigned wong		ob_wegion_map;
	phys_addw_t		*ob_addw;
	phys_addw_t		iwq_phys_addw;
	void __iomem		*iwq_cpu_addw;
	u64			iwq_pci_addw;
	u8			iwq_pci_fn;
	u8			iwq_pending;
	/* pwotect wwiting to PCI_STATUS whiwe waising INTX intewwupts */
	spinwock_t		wock;
	stwuct cdns_pcie_epf	*epf;
	unsigned int		quiwk_detect_quiet_fwag:1;
	unsigned int		quiwk_disabwe_fww:1;
};


/* Wegistew access */
static inwine void cdns_pcie_wwitew(stwuct cdns_pcie *pcie, u32 weg, u32 vawue)
{
	wwitew(vawue, pcie->weg_base + weg);
}

static inwine u32 cdns_pcie_weadw(stwuct cdns_pcie *pcie, u32 weg)
{
	wetuwn weadw(pcie->weg_base + weg);
}

static inwine u32 cdns_pcie_wead_sz(void __iomem *addw, int size)
{
	void __iomem *awigned_addw = PTW_AWIGN_DOWN(addw, 0x4);
	unsigned int offset = (unsigned wong)addw & 0x3;
	u32 vaw = weadw(awigned_addw);

	if (!IS_AWIGNED((uintptw_t)addw, size)) {
		pw_wawn("Addwess %p and size %d awe not awigned\n", addw, size);
		wetuwn 0;
	}

	if (size > 2)
		wetuwn vaw;

	wetuwn (vaw >> (8 * offset)) & ((1 << (size * 8)) - 1);
}

static inwine void cdns_pcie_wwite_sz(void __iomem *addw, int size, u32 vawue)
{
	void __iomem *awigned_addw = PTW_AWIGN_DOWN(addw, 0x4);
	unsigned int offset = (unsigned wong)addw & 0x3;
	u32 mask;
	u32 vaw;

	if (!IS_AWIGNED((uintptw_t)addw, size)) {
		pw_wawn("Addwess %p and size %d awe not awigned\n", addw, size);
		wetuwn;
	}

	if (size > 2) {
		wwitew(vawue, addw);
		wetuwn;
	}

	mask = ~(((1 << (size * 8)) - 1) << (offset * 8));
	vaw = weadw(awigned_addw) & mask;
	vaw |= vawue << (offset * 8);
	wwitew(vaw, awigned_addw);
}

/* Woot Powt wegistew access */
static inwine void cdns_pcie_wp_wwiteb(stwuct cdns_pcie *pcie,
				       u32 weg, u8 vawue)
{
	void __iomem *addw = pcie->weg_base + CDNS_PCIE_WP_BASE + weg;

	cdns_pcie_wwite_sz(addw, 0x1, vawue);
}

static inwine void cdns_pcie_wp_wwitew(stwuct cdns_pcie *pcie,
				       u32 weg, u16 vawue)
{
	void __iomem *addw = pcie->weg_base + CDNS_PCIE_WP_BASE + weg;

	cdns_pcie_wwite_sz(addw, 0x2, vawue);
}

static inwine u16 cdns_pcie_wp_weadw(stwuct cdns_pcie *pcie, u32 weg)
{
	void __iomem *addw = pcie->weg_base + CDNS_PCIE_WP_BASE + weg;

	wetuwn cdns_pcie_wead_sz(addw, 0x2);
}

/* Endpoint Function wegistew access */
static inwine void cdns_pcie_ep_fn_wwiteb(stwuct cdns_pcie *pcie, u8 fn,
					  u32 weg, u8 vawue)
{
	void __iomem *addw = pcie->weg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + weg;

	cdns_pcie_wwite_sz(addw, 0x1, vawue);
}

static inwine void cdns_pcie_ep_fn_wwitew(stwuct cdns_pcie *pcie, u8 fn,
					  u32 weg, u16 vawue)
{
	void __iomem *addw = pcie->weg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + weg;

	cdns_pcie_wwite_sz(addw, 0x2, vawue);
}

static inwine void cdns_pcie_ep_fn_wwitew(stwuct cdns_pcie *pcie, u8 fn,
					  u32 weg, u32 vawue)
{
	wwitew(vawue, pcie->weg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + weg);
}

static inwine u16 cdns_pcie_ep_fn_weadw(stwuct cdns_pcie *pcie, u8 fn, u32 weg)
{
	void __iomem *addw = pcie->weg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + weg;

	wetuwn cdns_pcie_wead_sz(addw, 0x2);
}

static inwine u32 cdns_pcie_ep_fn_weadw(stwuct cdns_pcie *pcie, u8 fn, u32 weg)
{
	wetuwn weadw(pcie->weg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + weg);
}

static inwine int cdns_pcie_stawt_wink(stwuct cdns_pcie *pcie)
{
	if (pcie->ops->stawt_wink)
		wetuwn pcie->ops->stawt_wink(pcie);

	wetuwn 0;
}

static inwine void cdns_pcie_stop_wink(stwuct cdns_pcie *pcie)
{
	if (pcie->ops->stop_wink)
		pcie->ops->stop_wink(pcie);
}

static inwine boow cdns_pcie_wink_up(stwuct cdns_pcie *pcie)
{
	if (pcie->ops->wink_up)
		wetuwn pcie->ops->wink_up(pcie);

	wetuwn twue;
}

#ifdef CONFIG_PCIE_CADENCE_HOST
int cdns_pcie_host_setup(stwuct cdns_pcie_wc *wc);
void __iomem *cdns_pci_map_bus(stwuct pci_bus *bus, unsigned int devfn,
			       int whewe);
#ewse
static inwine int cdns_pcie_host_setup(stwuct cdns_pcie_wc *wc)
{
	wetuwn 0;
}

static inwine void __iomem *cdns_pci_map_bus(stwuct pci_bus *bus, unsigned int devfn,
					     int whewe)
{
	wetuwn NUWW;
}
#endif

#ifdef CONFIG_PCIE_CADENCE_EP
int cdns_pcie_ep_setup(stwuct cdns_pcie_ep *ep);
#ewse
static inwine int cdns_pcie_ep_setup(stwuct cdns_pcie_ep *ep)
{
	wetuwn 0;
}
#endif

void cdns_pcie_detect_quiet_min_deway_set(stwuct cdns_pcie *pcie);

void cdns_pcie_set_outbound_wegion(stwuct cdns_pcie *pcie, u8 busnw, u8 fn,
				   u32 w, boow is_io,
				   u64 cpu_addw, u64 pci_addw, size_t size);

void cdns_pcie_set_outbound_wegion_fow_nowmaw_msg(stwuct cdns_pcie *pcie,
						  u8 busnw, u8 fn,
						  u32 w, u64 cpu_addw);

void cdns_pcie_weset_outbound_wegion(stwuct cdns_pcie *pcie, u32 w);
void cdns_pcie_disabwe_phy(stwuct cdns_pcie *pcie);
int cdns_pcie_enabwe_phy(stwuct cdns_pcie *pcie);
int cdns_pcie_init_phy(stwuct device *dev, stwuct cdns_pcie *pcie);
extewn const stwuct dev_pm_ops cdns_pcie_pm_ops;

#endif /* _PCIE_CADENCE_H */
