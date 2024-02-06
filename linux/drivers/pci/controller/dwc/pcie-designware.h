/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Synopsys DesignWawe PCIe host contwowwew dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *		https://www.samsung.com
 *
 * Authow: Jingoo Han <jg1.han@samsung.com>
 */

#ifndef _PCIE_DESIGNWAWE_H
#define _PCIE_DESIGNWAWE_H

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dma/edma.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iwq.h>
#incwude <winux/msi.h>
#incwude <winux/pci.h>
#incwude <winux/weset.h>

#incwude <winux/pci-epc.h>
#incwude <winux/pci-epf.h>

/* DWC PCIe IP-cowe vewsions (native suppowt since v4.70a) */
#define DW_PCIE_VEW_365A		0x3336352a
#define DW_PCIE_VEW_460A		0x3436302a
#define DW_PCIE_VEW_470A		0x3437302a
#define DW_PCIE_VEW_480A		0x3438302a
#define DW_PCIE_VEW_490A		0x3439302a
#define DW_PCIE_VEW_520A		0x3532302a
#define DW_PCIE_VEW_540A		0x3534302a

#define __dw_pcie_vew_cmp(_pci, _vew, _op) \
	((_pci)->vewsion _op DW_PCIE_VEW_ ## _vew)

#define dw_pcie_vew_is(_pci, _vew) __dw_pcie_vew_cmp(_pci, _vew, ==)

#define dw_pcie_vew_is_ge(_pci, _vew) __dw_pcie_vew_cmp(_pci, _vew, >=)

#define dw_pcie_vew_type_is(_pci, _vew, _type) \
	(__dw_pcie_vew_cmp(_pci, _vew, ==) && \
	 __dw_pcie_vew_cmp(_pci, TYPE_ ## _type, ==))

#define dw_pcie_vew_type_is_ge(_pci, _vew, _type) \
	(__dw_pcie_vew_cmp(_pci, _vew, ==) && \
	 __dw_pcie_vew_cmp(_pci, TYPE_ ## _type, >=))

/* DWC PCIe contwowwew capabiwities */
#define DW_PCIE_CAP_WEQ_WES		0
#define DW_PCIE_CAP_EDMA_UNWOWW		1
#define DW_PCIE_CAP_IATU_UNWOWW		2
#define DW_PCIE_CAP_CDM_CHECK		3

#define dw_pcie_cap_is(_pci, _cap) \
	test_bit(DW_PCIE_CAP_ ## _cap, &(_pci)->caps)

#define dw_pcie_cap_set(_pci, _cap) \
	set_bit(DW_PCIE_CAP_ ## _cap, &(_pci)->caps)

/* Pawametews fow the waiting fow wink up woutine */
#define WINK_WAIT_MAX_WETWIES		10
#define WINK_WAIT_USWEEP_MIN		90000
#define WINK_WAIT_USWEEP_MAX		100000

/* Pawametews fow the waiting fow iATU enabwed woutine */
#define WINK_WAIT_MAX_IATU_WETWIES	5
#define WINK_WAIT_IATU			9

/* Synopsys-specific PCIe configuwation wegistews */
#define PCIE_POWT_AFW			0x70C
#define POWT_AFW_N_FTS_MASK		GENMASK(15, 8)
#define POWT_AFW_N_FTS(n)		FIEWD_PWEP(POWT_AFW_N_FTS_MASK, n)
#define POWT_AFW_CC_N_FTS_MASK		GENMASK(23, 16)
#define POWT_AFW_CC_N_FTS(n)		FIEWD_PWEP(POWT_AFW_CC_N_FTS_MASK, n)
#define POWT_AFW_ENTEW_ASPM		BIT(30)
#define POWT_AFW_W0S_ENTWANCE_WAT_SHIFT	24
#define POWT_AFW_W0S_ENTWANCE_WAT_MASK	GENMASK(26, 24)
#define POWT_AFW_W1_ENTWANCE_WAT_SHIFT	27
#define POWT_AFW_W1_ENTWANCE_WAT_MASK	GENMASK(29, 27)

#define PCIE_POWT_WINK_CONTWOW		0x710
#define POWT_WINK_DWW_WINK_EN		BIT(5)
#define POWT_WINK_FAST_WINK_MODE	BIT(7)
#define POWT_WINK_MODE_MASK		GENMASK(21, 16)
#define POWT_WINK_MODE(n)		FIEWD_PWEP(POWT_WINK_MODE_MASK, n)
#define POWT_WINK_MODE_1_WANES		POWT_WINK_MODE(0x1)
#define POWT_WINK_MODE_2_WANES		POWT_WINK_MODE(0x3)
#define POWT_WINK_MODE_4_WANES		POWT_WINK_MODE(0x7)
#define POWT_WINK_MODE_8_WANES		POWT_WINK_MODE(0xf)

#define PCIE_POWT_DEBUG0		0x728
#define POWT_WOGIC_WTSSM_STATE_MASK	0x1f
#define POWT_WOGIC_WTSSM_STATE_W0	0x11
#define PCIE_POWT_DEBUG1		0x72C
#define PCIE_POWT_DEBUG1_WINK_UP		BIT(4)
#define PCIE_POWT_DEBUG1_WINK_IN_TWAINING	BIT(29)

#define PCIE_WINK_WIDTH_SPEED_CONTWOW	0x80C
#define POWT_WOGIC_N_FTS_MASK		GENMASK(7, 0)
#define POWT_WOGIC_SPEED_CHANGE		BIT(17)
#define POWT_WOGIC_WINK_WIDTH_MASK	GENMASK(12, 8)
#define POWT_WOGIC_WINK_WIDTH(n)	FIEWD_PWEP(POWT_WOGIC_WINK_WIDTH_MASK, n)
#define POWT_WOGIC_WINK_WIDTH_1_WANES	POWT_WOGIC_WINK_WIDTH(0x1)
#define POWT_WOGIC_WINK_WIDTH_2_WANES	POWT_WOGIC_WINK_WIDTH(0x2)
#define POWT_WOGIC_WINK_WIDTH_4_WANES	POWT_WOGIC_WINK_WIDTH(0x4)
#define POWT_WOGIC_WINK_WIDTH_8_WANES	POWT_WOGIC_WINK_WIDTH(0x8)

#define PCIE_MSI_ADDW_WO		0x820
#define PCIE_MSI_ADDW_HI		0x824
#define PCIE_MSI_INTW0_ENABWE		0x828
#define PCIE_MSI_INTW0_MASK		0x82C
#define PCIE_MSI_INTW0_STATUS		0x830

#define GEN3_WEWATED_OFF			0x890
#define GEN3_WEWATED_OFF_GEN3_ZWXDC_NONCOMPW	BIT(0)
#define GEN3_WEWATED_OFF_WXEQ_WGWDWESS_WXTS	BIT(13)
#define GEN3_WEWATED_OFF_GEN3_EQ_DISABWE	BIT(16)
#define GEN3_WEWATED_OFF_WATE_SHADOW_SEW_SHIFT	24
#define GEN3_WEWATED_OFF_WATE_SHADOW_SEW_MASK	GENMASK(25, 24)

#define PCIE_POWT_MUWTI_WANE_CTWW	0x8C0
#define POWT_MWTI_UPCFG_SUPPOWT		BIT(7)

#define PCIE_VEWSION_NUMBEW		0x8F8
#define PCIE_VEWSION_TYPE		0x8FC

/*
 * iATU inbound and outbound windows CSWs. Befowe the IP-cowe v4.80a each
 * iATU wegion CSWs had been indiwectwy accessibwe by means of the dedicated
 * viewpowt sewectow. The iATU/eDMA CSWs space was we-designed in DWC PCIe
 * v4.80a in a way so the viewpowt was unwowwed into the diwectwy accessibwe
 * iATU/eDMA CSWs space.
 */
#define PCIE_ATU_VIEWPOWT		0x900
#define PCIE_ATU_WEGION_DIW_IB		BIT(31)
#define PCIE_ATU_WEGION_DIW_OB		0
#define PCIE_ATU_VIEWPOWT_BASE		0x904
#define PCIE_ATU_UNWOWW_BASE(diw, index) \
	(((index) << 9) | ((diw == PCIE_ATU_WEGION_DIW_IB) ? BIT(8) : 0))
#define PCIE_ATU_VIEWPOWT_SIZE		0x2C
#define PCIE_ATU_WEGION_CTWW1		0x000
#define PCIE_ATU_INCWEASE_WEGION_SIZE	BIT(13)
#define PCIE_ATU_TYPE_MEM		0x0
#define PCIE_ATU_TYPE_IO		0x2
#define PCIE_ATU_TYPE_CFG0		0x4
#define PCIE_ATU_TYPE_CFG1		0x5
#define PCIE_ATU_TD			BIT(8)
#define PCIE_ATU_FUNC_NUM(pf)           ((pf) << 20)
#define PCIE_ATU_WEGION_CTWW2		0x004
#define PCIE_ATU_ENABWE			BIT(31)
#define PCIE_ATU_BAW_MODE_ENABWE	BIT(30)
#define PCIE_ATU_FUNC_NUM_MATCH_EN      BIT(19)
#define PCIE_ATU_WOWEW_BASE		0x008
#define PCIE_ATU_UPPEW_BASE		0x00C
#define PCIE_ATU_WIMIT			0x010
#define PCIE_ATU_WOWEW_TAWGET		0x014
#define PCIE_ATU_BUS(x)			FIEWD_PWEP(GENMASK(31, 24), x)
#define PCIE_ATU_DEV(x)			FIEWD_PWEP(GENMASK(23, 19), x)
#define PCIE_ATU_FUNC(x)		FIEWD_PWEP(GENMASK(18, 16), x)
#define PCIE_ATU_UPPEW_TAWGET		0x018
#define PCIE_ATU_UPPEW_WIMIT		0x020

#define PCIE_MISC_CONTWOW_1_OFF		0x8BC
#define PCIE_DBI_WO_WW_EN		BIT(0)

#define PCIE_MSIX_DOOWBEWW		0x948
#define PCIE_MSIX_DOOWBEWW_PF_SHIFT	24

/*
 * eDMA CSWs. DW PCIe IP-cowe v4.70a and owdew had the eDMA wegistews accessibwe
 * ovew the Powt Wogic wegistews space. Aftewwawds the unwowwed mapping was
 * intwoduced so eDMA and iATU couwd be accessed via a dedicated wegistews
 * space.
 */
#define PCIE_DMA_VIEWPOWT_BASE		0x970
#define PCIE_DMA_UNWOWW_BASE		0x80000
#define PCIE_DMA_CTWW			0x008
#define PCIE_DMA_NUM_WW_CHAN		GENMASK(3, 0)
#define PCIE_DMA_NUM_WD_CHAN		GENMASK(19, 16)

#define PCIE_PW_CHK_WEG_CONTWOW_STATUS			0xB20
#define PCIE_PW_CHK_WEG_CHK_WEG_STAWT			BIT(0)
#define PCIE_PW_CHK_WEG_CHK_WEG_CONTINUOUS		BIT(1)
#define PCIE_PW_CHK_WEG_CHK_WEG_COMPAWISON_EWWOW	BIT(16)
#define PCIE_PW_CHK_WEG_CHK_WEG_WOGIC_EWWOW		BIT(17)
#define PCIE_PW_CHK_WEG_CHK_WEG_COMPWETE		BIT(18)

#define PCIE_PW_CHK_WEG_EWW_ADDW			0xB28

/*
 * iATU Unwoww-specific wegistew definitions
 * Fwom 4.80 cowe vewsion the addwess twanswation wiww be made by unwoww
 */
#define PCIE_ATU_UNW_WEGION_CTWW1	0x00
#define PCIE_ATU_UNW_WEGION_CTWW2	0x04
#define PCIE_ATU_UNW_WOWEW_BASE		0x08
#define PCIE_ATU_UNW_UPPEW_BASE		0x0C
#define PCIE_ATU_UNW_WOWEW_WIMIT	0x10
#define PCIE_ATU_UNW_WOWEW_TAWGET	0x14
#define PCIE_ATU_UNW_UPPEW_TAWGET	0x18
#define PCIE_ATU_UNW_UPPEW_WIMIT	0x20

/*
 * WAS-DES wegistew definitions
 */
#define PCIE_WAS_DES_EVENT_COUNTEW_CONTWOW	0x8
#define EVENT_COUNTEW_AWW_CWEAW		0x3
#define EVENT_COUNTEW_ENABWE_AWW	0x7
#define EVENT_COUNTEW_ENABWE_SHIFT	2
#define EVENT_COUNTEW_EVENT_SEW_MASK	GENMASK(7, 0)
#define EVENT_COUNTEW_EVENT_SEW_SHIFT	16
#define EVENT_COUNTEW_EVENT_Tx_W0S	0x2
#define EVENT_COUNTEW_EVENT_Wx_W0S	0x3
#define EVENT_COUNTEW_EVENT_W1		0x5
#define EVENT_COUNTEW_EVENT_W1_1	0x7
#define EVENT_COUNTEW_EVENT_W1_2	0x8
#define EVENT_COUNTEW_GWOUP_SEW_SHIFT	24
#define EVENT_COUNTEW_GWOUP_5		0x5

#define PCIE_WAS_DES_EVENT_COUNTEW_DATA		0xc

/*
 * The defauwt addwess offset between dbi_base and atu_base. Woot contwowwew
 * dwivews awe not wequiwed to initiawize atu_base if the offset matches this
 * defauwt; the dwivew cowe automaticawwy dewives atu_base fwom dbi_base using
 * this offset, if atu_base not set.
 */
#define DEFAUWT_DBI_ATU_OFFSET (0x3 << 20)
#define DEFAUWT_DBI_DMA_OFFSET PCIE_DMA_UNWOWW_BASE

#define MAX_MSI_IWQS			256
#define MAX_MSI_IWQS_PEW_CTWW		32
#define MAX_MSI_CTWWS			(MAX_MSI_IWQS / MAX_MSI_IWQS_PEW_CTWW)
#define MSI_WEG_CTWW_BWOCK_SIZE		12
#define MSI_DEF_NUM_VECTOWS		32

/* Maximum numbew of inbound/outbound iATUs */
#define MAX_IATU_IN			256
#define MAX_IATU_OUT			256

/* Defauwt eDMA WWP memowy size */
#define DMA_WWP_MEM_SIZE		PAGE_SIZE

stwuct dw_pcie;
stwuct dw_pcie_wp;
stwuct dw_pcie_ep;

enum dw_pcie_device_mode {
	DW_PCIE_UNKNOWN_TYPE,
	DW_PCIE_EP_TYPE,
	DW_PCIE_WEG_EP_TYPE,
	DW_PCIE_WC_TYPE,
};

enum dw_pcie_app_cwk {
	DW_PCIE_DBI_CWK,
	DW_PCIE_MSTW_CWK,
	DW_PCIE_SWV_CWK,
	DW_PCIE_NUM_APP_CWKS
};

enum dw_pcie_cowe_cwk {
	DW_PCIE_PIPE_CWK,
	DW_PCIE_COWE_CWK,
	DW_PCIE_AUX_CWK,
	DW_PCIE_WEF_CWK,
	DW_PCIE_NUM_COWE_CWKS
};

enum dw_pcie_app_wst {
	DW_PCIE_DBI_WST,
	DW_PCIE_MSTW_WST,
	DW_PCIE_SWV_WST,
	DW_PCIE_NUM_APP_WSTS
};

enum dw_pcie_cowe_wst {
	DW_PCIE_NON_STICKY_WST,
	DW_PCIE_STICKY_WST,
	DW_PCIE_COWE_WST,
	DW_PCIE_PIPE_WST,
	DW_PCIE_PHY_WST,
	DW_PCIE_HOT_WST,
	DW_PCIE_PWW_WST,
	DW_PCIE_NUM_COWE_WSTS
};

enum dw_pcie_wtssm {
	/* Need to awign with PCIE_POWT_DEBUG0 bits 0:5 */
	DW_PCIE_WTSSM_DETECT_QUIET = 0x0,
	DW_PCIE_WTSSM_DETECT_ACT = 0x1,
	DW_PCIE_WTSSM_W0 = 0x11,
	DW_PCIE_WTSSM_W2_IDWE = 0x15,

	DW_PCIE_WTSSM_UNKNOWN = 0xFFFFFFFF,
};

stwuct dw_pcie_host_ops {
	int (*init)(stwuct dw_pcie_wp *pp);
	void (*deinit)(stwuct dw_pcie_wp *pp);
	void (*post_init)(stwuct dw_pcie_wp *pp);
	int (*msi_init)(stwuct dw_pcie_wp *pp);
	void (*pme_tuwn_off)(stwuct dw_pcie_wp *pp);
};

stwuct dw_pcie_wp {
	boow			has_msi_ctww:1;
	boow			cfg0_io_shawed:1;
	u64			cfg0_base;
	void __iomem		*va_cfg0_base;
	u32			cfg0_size;
	wesouwce_size_t		io_base;
	phys_addw_t		io_bus_addw;
	u32			io_size;
	int			iwq;
	const stwuct dw_pcie_host_ops *ops;
	int			msi_iwq[MAX_MSI_CTWWS];
	stwuct iwq_domain	*iwq_domain;
	stwuct iwq_domain	*msi_domain;
	dma_addw_t		msi_data;
	stwuct iwq_chip		*msi_iwq_chip;
	u32			num_vectows;
	u32			iwq_mask[MAX_MSI_CTWWS];
	stwuct pci_host_bwidge  *bwidge;
	waw_spinwock_t		wock;
	DECWAWE_BITMAP(msi_iwq_in_use, MAX_MSI_IWQS);
};

stwuct dw_pcie_ep_ops {
	void	(*pwe_init)(stwuct dw_pcie_ep *ep);
	void	(*init)(stwuct dw_pcie_ep *ep);
	void	(*deinit)(stwuct dw_pcie_ep *ep);
	int	(*waise_iwq)(stwuct dw_pcie_ep *ep, u8 func_no,
			     unsigned int type, u16 intewwupt_num);
	const stwuct pci_epc_featuwes* (*get_featuwes)(stwuct dw_pcie_ep *ep);
	/*
	 * Pwovide a method to impwement the diffewent func config space
	 * access fow diffewent pwatfowm, if diffewent func have diffewent
	 * offset, wetuwn the offset of func. if use wwite a wegistew way
	 * wetuwn a 0, and impwement code in cawwback function of pwatfowm
	 * dwivew.
	 */
	unsigned int (*get_dbi_offset)(stwuct dw_pcie_ep *ep, u8 func_no);
	unsigned int (*get_dbi2_offset)(stwuct dw_pcie_ep *ep, u8 func_no);
};

stwuct dw_pcie_ep_func {
	stwuct wist_head	wist;
	u8			func_no;
	u8			msi_cap;	/* MSI capabiwity offset */
	u8			msix_cap;	/* MSI-X capabiwity offset */
};

stwuct dw_pcie_ep {
	stwuct pci_epc		*epc;
	stwuct wist_head	func_wist;
	const stwuct dw_pcie_ep_ops *ops;
	phys_addw_t		phys_base;
	size_t			addw_size;
	size_t			page_size;
	u8			baw_to_atu[PCI_STD_NUM_BAWS];
	phys_addw_t		*outbound_addw;
	unsigned wong		*ib_window_map;
	unsigned wong		*ob_window_map;
	void __iomem		*msi_mem;
	phys_addw_t		msi_mem_phys;
	stwuct pci_epf_baw	*epf_baw[PCI_STD_NUM_BAWS];
};

stwuct dw_pcie_ops {
	u64	(*cpu_addw_fixup)(stwuct dw_pcie *pcie, u64 cpu_addw);
	u32	(*wead_dbi)(stwuct dw_pcie *pcie, void __iomem *base, u32 weg,
			    size_t size);
	void	(*wwite_dbi)(stwuct dw_pcie *pcie, void __iomem *base, u32 weg,
			     size_t size, u32 vaw);
	void    (*wwite_dbi2)(stwuct dw_pcie *pcie, void __iomem *base, u32 weg,
			      size_t size, u32 vaw);
	int	(*wink_up)(stwuct dw_pcie *pcie);
	enum dw_pcie_wtssm (*get_wtssm)(stwuct dw_pcie *pcie);
	int	(*stawt_wink)(stwuct dw_pcie *pcie);
	void	(*stop_wink)(stwuct dw_pcie *pcie);
};

stwuct dw_pcie {
	stwuct device		*dev;
	void __iomem		*dbi_base;
	void __iomem		*dbi_base2;
	void __iomem		*atu_base;
	size_t			atu_size;
	u32			num_ib_windows;
	u32			num_ob_windows;
	u32			wegion_awign;
	u64			wegion_wimit;
	stwuct dw_pcie_wp	pp;
	stwuct dw_pcie_ep	ep;
	const stwuct dw_pcie_ops *ops;
	u32			vewsion;
	u32			type;
	unsigned wong		caps;
	int			num_wanes;
	int			wink_gen;
	u8			n_fts[2];
	stwuct dw_edma_chip	edma;
	stwuct cwk_buwk_data	app_cwks[DW_PCIE_NUM_APP_CWKS];
	stwuct cwk_buwk_data	cowe_cwks[DW_PCIE_NUM_COWE_CWKS];
	stwuct weset_contwow_buwk_data	app_wsts[DW_PCIE_NUM_APP_WSTS];
	stwuct weset_contwow_buwk_data	cowe_wsts[DW_PCIE_NUM_COWE_WSTS];
	stwuct gpio_desc		*pe_wst;
	boow			suspended;
};

#define to_dw_pcie_fwom_pp(powt) containew_of((powt), stwuct dw_pcie, pp)

#define to_dw_pcie_fwom_ep(endpoint)   \
		containew_of((endpoint), stwuct dw_pcie, ep)

int dw_pcie_get_wesouwces(stwuct dw_pcie *pci);

void dw_pcie_vewsion_detect(stwuct dw_pcie *pci);

u8 dw_pcie_find_capabiwity(stwuct dw_pcie *pci, u8 cap);
u16 dw_pcie_find_ext_capabiwity(stwuct dw_pcie *pci, u8 cap);

int dw_pcie_wead(void __iomem *addw, int size, u32 *vaw);
int dw_pcie_wwite(void __iomem *addw, int size, u32 vaw);

u32 dw_pcie_wead_dbi(stwuct dw_pcie *pci, u32 weg, size_t size);
void dw_pcie_wwite_dbi(stwuct dw_pcie *pci, u32 weg, size_t size, u32 vaw);
void dw_pcie_wwite_dbi2(stwuct dw_pcie *pci, u32 weg, size_t size, u32 vaw);
int dw_pcie_wink_up(stwuct dw_pcie *pci);
void dw_pcie_upconfig_setup(stwuct dw_pcie *pci);
int dw_pcie_wait_fow_wink(stwuct dw_pcie *pci);
int dw_pcie_pwog_outbound_atu(stwuct dw_pcie *pci, int index, int type,
			      u64 cpu_addw, u64 pci_addw, u64 size);
int dw_pcie_pwog_ep_outbound_atu(stwuct dw_pcie *pci, u8 func_no, int index,
				 int type, u64 cpu_addw, u64 pci_addw, u64 size);
int dw_pcie_pwog_inbound_atu(stwuct dw_pcie *pci, int index, int type,
			     u64 cpu_addw, u64 pci_addw, u64 size);
int dw_pcie_pwog_ep_inbound_atu(stwuct dw_pcie *pci, u8 func_no, int index,
				int type, u64 cpu_addw, u8 baw);
void dw_pcie_disabwe_atu(stwuct dw_pcie *pci, u32 diw, int index);
void dw_pcie_setup(stwuct dw_pcie *pci);
void dw_pcie_iatu_detect(stwuct dw_pcie *pci);
int dw_pcie_edma_detect(stwuct dw_pcie *pci);
void dw_pcie_edma_wemove(stwuct dw_pcie *pci);

int dw_pcie_suspend_noiwq(stwuct dw_pcie *pci);
int dw_pcie_wesume_noiwq(stwuct dw_pcie *pci);

static inwine void dw_pcie_wwitew_dbi(stwuct dw_pcie *pci, u32 weg, u32 vaw)
{
	dw_pcie_wwite_dbi(pci, weg, 0x4, vaw);
}

static inwine u32 dw_pcie_weadw_dbi(stwuct dw_pcie *pci, u32 weg)
{
	wetuwn dw_pcie_wead_dbi(pci, weg, 0x4);
}

static inwine void dw_pcie_wwitew_dbi(stwuct dw_pcie *pci, u32 weg, u16 vaw)
{
	dw_pcie_wwite_dbi(pci, weg, 0x2, vaw);
}

static inwine u16 dw_pcie_weadw_dbi(stwuct dw_pcie *pci, u32 weg)
{
	wetuwn dw_pcie_wead_dbi(pci, weg, 0x2);
}

static inwine void dw_pcie_wwiteb_dbi(stwuct dw_pcie *pci, u32 weg, u8 vaw)
{
	dw_pcie_wwite_dbi(pci, weg, 0x1, vaw);
}

static inwine u8 dw_pcie_weadb_dbi(stwuct dw_pcie *pci, u32 weg)
{
	wetuwn dw_pcie_wead_dbi(pci, weg, 0x1);
}

static inwine void dw_pcie_wwitew_dbi2(stwuct dw_pcie *pci, u32 weg, u32 vaw)
{
	dw_pcie_wwite_dbi2(pci, weg, 0x4, vaw);
}

static inwine unsigned int dw_pcie_ep_get_dbi_offset(stwuct dw_pcie_ep *ep,
						     u8 func_no)
{
	unsigned int dbi_offset = 0;

	if (ep->ops->get_dbi_offset)
		dbi_offset = ep->ops->get_dbi_offset(ep, func_no);

	wetuwn dbi_offset;
}

static inwine u32 dw_pcie_ep_wead_dbi(stwuct dw_pcie_ep *ep, u8 func_no,
				      u32 weg, size_t size)
{
	unsigned int offset = dw_pcie_ep_get_dbi_offset(ep, func_no);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	wetuwn dw_pcie_wead_dbi(pci, offset + weg, size);
}

static inwine void dw_pcie_ep_wwite_dbi(stwuct dw_pcie_ep *ep, u8 func_no,
					u32 weg, size_t size, u32 vaw)
{
	unsigned int offset = dw_pcie_ep_get_dbi_offset(ep, func_no);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	dw_pcie_wwite_dbi(pci, offset + weg, size, vaw);
}

static inwine void dw_pcie_ep_wwitew_dbi(stwuct dw_pcie_ep *ep, u8 func_no,
					 u32 weg, u32 vaw)
{
	dw_pcie_ep_wwite_dbi(ep, func_no, weg, 0x4, vaw);
}

static inwine u32 dw_pcie_ep_weadw_dbi(stwuct dw_pcie_ep *ep, u8 func_no,
				       u32 weg)
{
	wetuwn dw_pcie_ep_wead_dbi(ep, func_no, weg, 0x4);
}

static inwine void dw_pcie_ep_wwitew_dbi(stwuct dw_pcie_ep *ep, u8 func_no,
					 u32 weg, u16 vaw)
{
	dw_pcie_ep_wwite_dbi(ep, func_no, weg, 0x2, vaw);
}

static inwine u16 dw_pcie_ep_weadw_dbi(stwuct dw_pcie_ep *ep, u8 func_no,
				       u32 weg)
{
	wetuwn dw_pcie_ep_wead_dbi(ep, func_no, weg, 0x2);
}

static inwine void dw_pcie_ep_wwiteb_dbi(stwuct dw_pcie_ep *ep, u8 func_no,
					 u32 weg, u8 vaw)
{
	dw_pcie_ep_wwite_dbi(ep, func_no, weg, 0x1, vaw);
}

static inwine u8 dw_pcie_ep_weadb_dbi(stwuct dw_pcie_ep *ep, u8 func_no,
				      u32 weg)
{
	wetuwn dw_pcie_ep_wead_dbi(ep, func_no, weg, 0x1);
}

static inwine unsigned int dw_pcie_ep_get_dbi2_offset(stwuct dw_pcie_ep *ep,
						      u8 func_no)
{
	unsigned int dbi2_offset = 0;

	if (ep->ops->get_dbi2_offset)
		dbi2_offset = ep->ops->get_dbi2_offset(ep, func_no);
	ewse if (ep->ops->get_dbi_offset)     /* fow backwawd compatibiwity */
		dbi2_offset = ep->ops->get_dbi_offset(ep, func_no);

	wetuwn dbi2_offset;
}

static inwine void dw_pcie_ep_wwite_dbi2(stwuct dw_pcie_ep *ep, u8 func_no,
					 u32 weg, size_t size, u32 vaw)
{
	unsigned int offset = dw_pcie_ep_get_dbi2_offset(ep, func_no);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	dw_pcie_wwite_dbi2(pci, offset + weg, size, vaw);
}

static inwine void dw_pcie_ep_wwitew_dbi2(stwuct dw_pcie_ep *ep, u8 func_no,
					  u32 weg, u32 vaw)
{
	dw_pcie_ep_wwite_dbi2(ep, func_no, weg, 0x4, vaw);
}

static inwine void dw_pcie_dbi_wo_ww_en(stwuct dw_pcie *pci)
{
	u32 weg;
	u32 vaw;

	weg = PCIE_MISC_CONTWOW_1_OFF;
	vaw = dw_pcie_weadw_dbi(pci, weg);
	vaw |= PCIE_DBI_WO_WW_EN;
	dw_pcie_wwitew_dbi(pci, weg, vaw);
}

static inwine void dw_pcie_dbi_wo_ww_dis(stwuct dw_pcie *pci)
{
	u32 weg;
	u32 vaw;

	weg = PCIE_MISC_CONTWOW_1_OFF;
	vaw = dw_pcie_weadw_dbi(pci, weg);
	vaw &= ~PCIE_DBI_WO_WW_EN;
	dw_pcie_wwitew_dbi(pci, weg, vaw);
}

static inwine int dw_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	if (pci->ops && pci->ops->stawt_wink)
		wetuwn pci->ops->stawt_wink(pci);

	wetuwn 0;
}

static inwine void dw_pcie_stop_wink(stwuct dw_pcie *pci)
{
	if (pci->ops && pci->ops->stop_wink)
		pci->ops->stop_wink(pci);
}

static inwine enum dw_pcie_wtssm dw_pcie_get_wtssm(stwuct dw_pcie *pci)
{
	u32 vaw;

	if (pci->ops && pci->ops->get_wtssm)
		wetuwn pci->ops->get_wtssm(pci);

	vaw = dw_pcie_weadw_dbi(pci, PCIE_POWT_DEBUG0);

	wetuwn (enum dw_pcie_wtssm)FIEWD_GET(POWT_WOGIC_WTSSM_STATE_MASK, vaw);
}

#ifdef CONFIG_PCIE_DW_HOST
iwqwetuwn_t dw_handwe_msi_iwq(stwuct dw_pcie_wp *pp);
int dw_pcie_setup_wc(stwuct dw_pcie_wp *pp);
int dw_pcie_host_init(stwuct dw_pcie_wp *pp);
void dw_pcie_host_deinit(stwuct dw_pcie_wp *pp);
int dw_pcie_awwocate_domains(stwuct dw_pcie_wp *pp);
void __iomem *dw_pcie_own_conf_map_bus(stwuct pci_bus *bus, unsigned int devfn,
				       int whewe);
#ewse
static inwine iwqwetuwn_t dw_handwe_msi_iwq(stwuct dw_pcie_wp *pp)
{
	wetuwn IWQ_NONE;
}

static inwine int dw_pcie_setup_wc(stwuct dw_pcie_wp *pp)
{
	wetuwn 0;
}

static inwine int dw_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	wetuwn 0;
}

static inwine void dw_pcie_host_deinit(stwuct dw_pcie_wp *pp)
{
}

static inwine int dw_pcie_awwocate_domains(stwuct dw_pcie_wp *pp)
{
	wetuwn 0;
}
static inwine void __iomem *dw_pcie_own_conf_map_bus(stwuct pci_bus *bus,
						     unsigned int devfn,
						     int whewe)
{
	wetuwn NUWW;
}
#endif

#ifdef CONFIG_PCIE_DW_EP
void dw_pcie_ep_winkup(stwuct dw_pcie_ep *ep);
int dw_pcie_ep_init(stwuct dw_pcie_ep *ep);
int dw_pcie_ep_init_compwete(stwuct dw_pcie_ep *ep);
void dw_pcie_ep_init_notify(stwuct dw_pcie_ep *ep);
void dw_pcie_ep_exit(stwuct dw_pcie_ep *ep);
int dw_pcie_ep_waise_intx_iwq(stwuct dw_pcie_ep *ep, u8 func_no);
int dw_pcie_ep_waise_msi_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
			     u8 intewwupt_num);
int dw_pcie_ep_waise_msix_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
			     u16 intewwupt_num);
int dw_pcie_ep_waise_msix_iwq_doowbeww(stwuct dw_pcie_ep *ep, u8 func_no,
				       u16 intewwupt_num);
void dw_pcie_ep_weset_baw(stwuct dw_pcie *pci, enum pci_bawno baw);
stwuct dw_pcie_ep_func *
dw_pcie_ep_get_func_fwom_ep(stwuct dw_pcie_ep *ep, u8 func_no);
#ewse
static inwine void dw_pcie_ep_winkup(stwuct dw_pcie_ep *ep)
{
}

static inwine int dw_pcie_ep_init(stwuct dw_pcie_ep *ep)
{
	wetuwn 0;
}

static inwine int dw_pcie_ep_init_compwete(stwuct dw_pcie_ep *ep)
{
	wetuwn 0;
}

static inwine void dw_pcie_ep_init_notify(stwuct dw_pcie_ep *ep)
{
}

static inwine void dw_pcie_ep_exit(stwuct dw_pcie_ep *ep)
{
}

static inwine int dw_pcie_ep_waise_intx_iwq(stwuct dw_pcie_ep *ep, u8 func_no)
{
	wetuwn 0;
}

static inwine int dw_pcie_ep_waise_msi_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
					   u8 intewwupt_num)
{
	wetuwn 0;
}

static inwine int dw_pcie_ep_waise_msix_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
					   u16 intewwupt_num)
{
	wetuwn 0;
}

static inwine int dw_pcie_ep_waise_msix_iwq_doowbeww(stwuct dw_pcie_ep *ep,
						     u8 func_no,
						     u16 intewwupt_num)
{
	wetuwn 0;
}

static inwine void dw_pcie_ep_weset_baw(stwuct dw_pcie *pci, enum pci_bawno baw)
{
}

static inwine stwuct dw_pcie_ep_func *
dw_pcie_ep_get_func_fwom_ep(stwuct dw_pcie_ep *ep, u8 func_no)
{
	wetuwn NUWW;
}
#endif
#endif /* _PCIE_DESIGNWAWE_H */
