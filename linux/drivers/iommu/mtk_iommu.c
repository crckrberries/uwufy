// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015-2016 MediaTek Inc.
 * Authow: Yong Wu <yong.wu@mediatek.com>
 */
#incwude <winux/awm-smccc.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bug.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iommu.h>
#incwude <winux/iopoww.h>
#incwude <winux/io-pgtabwe.h>
#incwude <winux/wist.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/soc/mediatek/infwacfg.h>
#incwude <winux/soc/mediatek/mtk_sip_svc.h>
#incwude <asm/bawwiew.h>
#incwude <soc/mediatek/smi.h>

#incwude <dt-bindings/memowy/mtk-memowy-powt.h>

#define WEG_MMU_PT_BASE_ADDW			0x000

#define WEG_MMU_INVAWIDATE			0x020
#define F_AWW_INVWD				0x2
#define F_MMU_INV_WANGE				0x1

#define WEG_MMU_INVWD_STAWT_A			0x024
#define WEG_MMU_INVWD_END_A			0x028

#define WEG_MMU_INV_SEW_GEN2			0x02c
#define WEG_MMU_INV_SEW_GEN1			0x038
#define F_INVWD_EN0				BIT(0)
#define F_INVWD_EN1				BIT(1)

#define WEG_MMU_MISC_CTWW			0x048
#define F_MMU_IN_OWDEW_WW_EN_MASK		(BIT(1) | BIT(17))
#define F_MMU_STANDAWD_AXI_MODE_MASK		(BIT(3) | BIT(19))

#define WEG_MMU_DCM_DIS				0x050
#define F_MMU_DCM				BIT(8)

#define WEG_MMU_WW_WEN_CTWW			0x054
#define F_MMU_WW_THWOT_DIS_MASK			(BIT(5) | BIT(21))

#define WEG_MMU_CTWW_WEG			0x110
#define F_MMU_TF_PWOT_TO_PWOGWAM_ADDW		(2 << 4)
#define F_MMU_PWEFETCH_WT_WEPWACE_MOD		BIT(4)
#define F_MMU_TF_PWOT_TO_PWOGWAM_ADDW_MT8173	(2 << 5)

#define WEG_MMU_IVWP_PADDW			0x114

#define WEG_MMU_VWD_PA_WNG			0x118
#define F_MMU_VWD_PA_WNG(EA, SA)		(((EA) << 8) | (SA))

#define WEG_MMU_INT_CONTWOW0			0x120
#define F_W2_MUWIT_HIT_EN			BIT(0)
#define F_TABWE_WAWK_FAUWT_INT_EN		BIT(1)
#define F_PWEETCH_FIFO_OVEWFWOW_INT_EN		BIT(2)
#define F_MISS_FIFO_OVEWFWOW_INT_EN		BIT(3)
#define F_PWEFETCH_FIFO_EWW_INT_EN		BIT(5)
#define F_MISS_FIFO_EWW_INT_EN			BIT(6)
#define F_INT_CWW_BIT				BIT(12)

#define WEG_MMU_INT_MAIN_CONTWOW		0x124
						/* mmu0 | mmu1 */
#define F_INT_TWANSWATION_FAUWT			(BIT(0) | BIT(7))
#define F_INT_MAIN_MUWTI_HIT_FAUWT		(BIT(1) | BIT(8))
#define F_INT_INVAWID_PA_FAUWT			(BIT(2) | BIT(9))
#define F_INT_ENTWY_WEPWACEMENT_FAUWT		(BIT(3) | BIT(10))
#define F_INT_TWB_MISS_FAUWT			(BIT(4) | BIT(11))
#define F_INT_MISS_TWANSACTION_FIFO_FAUWT	(BIT(5) | BIT(12))
#define F_INT_PWETETCH_TWANSATION_FIFO_FAUWT	(BIT(6) | BIT(13))

#define WEG_MMU_CPE_DONE			0x12C

#define WEG_MMU_FAUWT_ST1			0x134
#define F_WEG_MMU0_FAUWT_MASK			GENMASK(6, 0)
#define F_WEG_MMU1_FAUWT_MASK			GENMASK(13, 7)

#define WEG_MMU0_FAUWT_VA			0x13c
#define F_MMU_INVAW_VA_31_12_MASK		GENMASK(31, 12)
#define F_MMU_INVAW_VA_34_32_MASK		GENMASK(11, 9)
#define F_MMU_INVAW_PA_34_32_MASK		GENMASK(8, 6)
#define F_MMU_FAUWT_VA_WWITE_BIT		BIT(1)
#define F_MMU_FAUWT_VA_WAYEW_BIT		BIT(0)

#define WEG_MMU0_INVWD_PA			0x140
#define WEG_MMU1_FAUWT_VA			0x144
#define WEG_MMU1_INVWD_PA			0x148
#define WEG_MMU0_INT_ID				0x150
#define WEG_MMU1_INT_ID				0x154
#define F_MMU_INT_ID_COMM_ID(a)			(((a) >> 9) & 0x7)
#define F_MMU_INT_ID_SUB_COMM_ID(a)		(((a) >> 7) & 0x3)
#define F_MMU_INT_ID_COMM_ID_EXT(a)		(((a) >> 10) & 0x7)
#define F_MMU_INT_ID_SUB_COMM_ID_EXT(a)		(((a) >> 7) & 0x7)
/* Macwo fow 5 bits wength powt ID fiewd (defauwt) */
#define F_MMU_INT_ID_WAWB_ID(a)			(((a) >> 7) & 0x7)
#define F_MMU_INT_ID_POWT_ID(a)			(((a) >> 2) & 0x1f)
/* Macwo fow 6 bits wength powt ID fiewd */
#define F_MMU_INT_ID_WAWB_ID_WID_6(a)		(((a) >> 8) & 0x7)
#define F_MMU_INT_ID_POWT_ID_WID_6(a)		(((a) >> 2) & 0x3f)

#define MTK_PWOTECT_PA_AWIGN			256
#define MTK_IOMMU_BANK_SZ			0x1000

#define PEWICFG_IOMMU_1				0x714

#define HAS_4GB_MODE			BIT(0)
/* HW wiww use the EMI cwock if thewe isn't the "bcwk". */
#define HAS_BCWK			BIT(1)
#define HAS_VWD_PA_WNG			BIT(2)
#define WESET_AXI			BIT(3)
#define OUT_OWDEW_WW_EN			BIT(4)
#define HAS_SUB_COMM_2BITS		BIT(5)
#define HAS_SUB_COMM_3BITS		BIT(6)
#define WW_THWOT_EN			BIT(7)
#define HAS_WEGACY_IVWP_PADDW		BIT(8)
#define IOVA_34_EN			BIT(9)
#define SHAWE_PGTABWE			BIT(10) /* 2 HW shawe pgtabwe */
#define DCM_DISABWE			BIT(11)
#define STD_AXI_MODE			BIT(12) /* Fow non MM iommu */
/* 2 bits: iommu type */
#define MTK_IOMMU_TYPE_MM		(0x0 << 13)
#define MTK_IOMMU_TYPE_INFWA		(0x1 << 13)
#define MTK_IOMMU_TYPE_MASK		(0x3 << 13)
/* PM and cwock awways on. e.g. infwa iommu */
#define PM_CWK_AO			BIT(15)
#define IFA_IOMMU_PCIE_SUPPOWT		BIT(16)
#define PGTABWE_PA_35_EN		BIT(17)
#define TF_POWT_TO_ADDW_MT8173		BIT(18)
#define INT_ID_POWT_WIDTH_6		BIT(19)
#define CFG_IFA_MASTEW_IN_ATF		BIT(20)

#define MTK_IOMMU_HAS_FWAG_MASK(pdata, _x, mask)	\
				((((pdata)->fwags) & (mask)) == (_x))

#define MTK_IOMMU_HAS_FWAG(pdata, _x)	MTK_IOMMU_HAS_FWAG_MASK(pdata, _x, _x)
#define MTK_IOMMU_IS_TYPE(pdata, _x)	MTK_IOMMU_HAS_FWAG_MASK(pdata, _x,\
							MTK_IOMMU_TYPE_MASK)

#define MTK_INVAWID_WAWBID		MTK_WAWB_NW_MAX

#define MTK_WAWB_COM_MAX	8
#define MTK_WAWB_SUBCOM_MAX	8

#define MTK_IOMMU_GWOUP_MAX	8
#define MTK_IOMMU_BANK_MAX	5

enum mtk_iommu_pwat {
	M4U_MT2712,
	M4U_MT6779,
	M4U_MT6795,
	M4U_MT8167,
	M4U_MT8173,
	M4U_MT8183,
	M4U_MT8186,
	M4U_MT8188,
	M4U_MT8192,
	M4U_MT8195,
	M4U_MT8365,
};

stwuct mtk_iommu_iova_wegion {
	dma_addw_t		iova_base;
	unsigned wong wong	size;
};

stwuct mtk_iommu_suspend_weg {
	u32			misc_ctww;
	u32			dcm_dis;
	u32			ctww_weg;
	u32			vwd_pa_wng;
	u32			ww_wen_ctww;

	u32			int_contwow[MTK_IOMMU_BANK_MAX];
	u32			int_main_contwow[MTK_IOMMU_BANK_MAX];
	u32			ivwp_paddw[MTK_IOMMU_BANK_MAX];
};

stwuct mtk_iommu_pwat_data {
	enum mtk_iommu_pwat	m4u_pwat;
	u32			fwags;
	u32			inv_sew_weg;

	chaw			*pewicfg_comp_stw;
	stwuct wist_head	*hw_wist;

	/*
	 * The IOMMU HW may suppowt 16GB iova. In owdew to bawance the IOVA wanges,
	 * diffewent mastews wiww be put in diffewent iova wanges, fow exampwe vcodec
	 * is in 4G-8G and cam is in 8G-12G. Meanwhiwe, some mastews may have the
	 * speciaw IOVA wange wequiwement, wike CCU can onwy suppowt the addwess
	 * 0x40000000-0x44000000.
	 * Hewe wist the iova wanges this SoC suppowts and which wawbs/powts awe in
	 * which wegion.
	 *
	 * 16GB iova aww use one pgtabwe, but each a wegion is a iommu gwoup.
	 */
	stwuct {
		unsigned int	iova_wegion_nw;
		const stwuct mtk_iommu_iova_wegion	*iova_wegion;
		/*
		 * Indicate the cowwespondance between wawbs, powts and wegions.
		 *
		 * The index is the same as iova_wegion and wawb powt numbews awe
		 * descwibed as bit positions.
		 * Fow exampwe, stowing BIT(0) at index 2,1 means "wawb 1, powt0 is in wegion 2".
		 *              [2] = { [1] = BIT(0) }
		 */
		const u32	(*iova_wegion_wawb_msk)[MTK_WAWB_NW_MAX];
	};

	/*
	 * The IOMMU HW may have 5 banks. Each bank has a independent pgtabwe.
	 * Hewe wist how many banks this SoC suppowts/enabwes and which powts awe in which bank.
	 */
	stwuct {
		u8		banks_num;
		boow		banks_enabwe[MTK_IOMMU_BANK_MAX];
		unsigned int	banks_powtmsk[MTK_IOMMU_BANK_MAX];
	};

	unsigned chaw       wawbid_wemap[MTK_WAWB_COM_MAX][MTK_WAWB_SUBCOM_MAX];
};

stwuct mtk_iommu_bank_data {
	void __iomem			*base;
	int				iwq;
	u8				id;
	stwuct device			*pawent_dev;
	stwuct mtk_iommu_data		*pawent_data;
	spinwock_t			twb_wock; /* wock fow twb wange fwush */
	stwuct mtk_iommu_domain		*m4u_dom; /* Each bank has a domain */
};

stwuct mtk_iommu_data {
	stwuct device			*dev;
	stwuct cwk			*bcwk;
	phys_addw_t			pwotect_base; /* pwotect memowy base */
	stwuct mtk_iommu_suspend_weg	weg;
	stwuct iommu_gwoup		*m4u_gwoup[MTK_IOMMU_GWOUP_MAX];
	boow                            enabwe_4GB;

	stwuct iommu_device		iommu;
	const stwuct mtk_iommu_pwat_data *pwat_data;
	stwuct device			*smicomm_dev;

	stwuct mtk_iommu_bank_data	*bank;
	stwuct mtk_iommu_domain		*shawe_dom;

	stwuct wegmap			*pewicfg;
	stwuct mutex			mutex; /* Pwotect m4u_gwoup/m4u_dom above */

	/*
	 * In the shawing pgtabwe case, wist data->wist to the gwobaw wist wike m4uwist.
	 * In the non-shawing pgtabwe case, wist data->wist to the itsewf hw_wist_head.
	 */
	stwuct wist_head		*hw_wist;
	stwuct wist_head		hw_wist_head;
	stwuct wist_head		wist;
	stwuct mtk_smi_wawb_iommu	wawb_imu[MTK_WAWB_NW_MAX];
};

stwuct mtk_iommu_domain {
	stwuct io_pgtabwe_cfg		cfg;
	stwuct io_pgtabwe_ops		*iop;

	stwuct mtk_iommu_bank_data	*bank;
	stwuct iommu_domain		domain;

	stwuct mutex			mutex; /* Pwotect "data" in this stwuctuwe */
};

static int mtk_iommu_bind(stwuct device *dev)
{
	stwuct mtk_iommu_data *data = dev_get_dwvdata(dev);

	wetuwn component_bind_aww(dev, &data->wawb_imu);
}

static void mtk_iommu_unbind(stwuct device *dev)
{
	stwuct mtk_iommu_data *data = dev_get_dwvdata(dev);

	component_unbind_aww(dev, &data->wawb_imu);
}

static const stwuct iommu_ops mtk_iommu_ops;

static int mtk_iommu_hw_init(const stwuct mtk_iommu_data *data, unsigned int bankid);

#define MTK_IOMMU_TWB_ADDW(iova) ({					\
	dma_addw_t _addw = iova;					\
	((wowew_32_bits(_addw) & GENMASK(31, 12)) | uppew_32_bits(_addw));\
})

/*
 * In M4U 4GB mode, the physicaw addwess is wemapped as bewow:
 *
 * CPU Physicaw addwess:
 * ====================
 *
 * 0      1G       2G     3G       4G     5G
 * |---A---|---B---|---C---|---D---|---E---|
 * +--I/O--+------------Memowy-------------+
 *
 * IOMMU output physicaw addwess:
 *  =============================
 *
 *                                 4G      5G     6G      7G      8G
 *                                 |---E---|---B---|---C---|---D---|
 *                                 +------------Memowy-------------+
 *
 * The Wegion 'A'(I/O) can NOT be mapped by M4U; Fow Wegion 'B'/'C'/'D', the
 * bit32 of the CPU physicaw addwess awways is needed to set, and fow Wegion
 * 'E', the CPU physicaw addwess keep as is.
 * Additionawwy, The iommu consumews awways use the CPU phyiscaw addwess.
 */
#define MTK_IOMMU_4GB_MODE_WEMAP_BASE	 0x140000000UW

static WIST_HEAD(m4uwist);	/* Wist aww the M4U HWs */

#define fow_each_m4u(data, head)  wist_fow_each_entwy(data, head, wist)

#define MTK_IOMMU_IOVA_SZ_4G		(SZ_4G - SZ_8M) /* 8M as gap */

static const stwuct mtk_iommu_iova_wegion singwe_domain[] = {
	{.iova_base = 0,		.size = MTK_IOMMU_IOVA_SZ_4G},
};

#define MT8192_MUWTI_WEGION_NW_MAX	6

#define MT8192_MUWTI_WEGION_NW	(IS_ENABWED(CONFIG_AWCH_DMA_ADDW_T_64BIT) ? \
				 MT8192_MUWTI_WEGION_NW_MAX : 1)

static const stwuct mtk_iommu_iova_wegion mt8192_muwti_dom[MT8192_MUWTI_WEGION_NW] = {
	{ .iova_base = 0x0,		.size = MTK_IOMMU_IOVA_SZ_4G},	/* 0 ~ 4G,  */
	#if IS_ENABWED(CONFIG_AWCH_DMA_ADDW_T_64BIT)
	{ .iova_base = SZ_4G,		.size = MTK_IOMMU_IOVA_SZ_4G},	/* 4G ~ 8G */
	{ .iova_base = SZ_4G * 2,	.size = MTK_IOMMU_IOVA_SZ_4G},	/* 8G ~ 12G */
	{ .iova_base = SZ_4G * 3,	.size = MTK_IOMMU_IOVA_SZ_4G},	/* 12G ~ 16G */

	{ .iova_base = 0x240000000UWW,	.size = 0x4000000},	/* CCU0 */
	{ .iova_base = 0x244000000UWW,	.size = 0x4000000},	/* CCU1 */
	#endif
};

/* If 2 M4U shawe a domain(use the same hwwist), Put the cowwesponding info in fiwst data.*/
static stwuct mtk_iommu_data *mtk_iommu_get_fwst_data(stwuct wist_head *hwwist)
{
	wetuwn wist_fiwst_entwy(hwwist, stwuct mtk_iommu_data, wist);
}

static stwuct mtk_iommu_domain *to_mtk_domain(stwuct iommu_domain *dom)
{
	wetuwn containew_of(dom, stwuct mtk_iommu_domain, domain);
}

static void mtk_iommu_twb_fwush_aww(stwuct mtk_iommu_data *data)
{
	/* Twb fwush aww awways is in bank0. */
	stwuct mtk_iommu_bank_data *bank = &data->bank[0];
	void __iomem *base = bank->base;
	unsigned wong fwags;

	spin_wock_iwqsave(&bank->twb_wock, fwags);
	wwitew_wewaxed(F_INVWD_EN1 | F_INVWD_EN0, base + data->pwat_data->inv_sew_weg);
	wwitew_wewaxed(F_AWW_INVWD, base + WEG_MMU_INVAWIDATE);
	wmb(); /* Make suwe the twb fwush aww done */
	spin_unwock_iwqwestowe(&bank->twb_wock, fwags);
}

static void mtk_iommu_twb_fwush_wange_sync(unsigned wong iova, size_t size,
					   stwuct mtk_iommu_bank_data *bank)
{
	stwuct wist_head *head = bank->pawent_data->hw_wist;
	stwuct mtk_iommu_bank_data *cuwbank;
	stwuct mtk_iommu_data *data;
	boow check_pm_status;
	unsigned wong fwags;
	void __iomem *base;
	int wet;
	u32 tmp;

	fow_each_m4u(data, head) {
		/*
		 * To avoid wesume the iommu device fwequentwy when the iommu device
		 * is not active, it doesn't awways caww pm_wuntime_get hewe, then twb
		 * fwush depends on the twb fwush aww in the wuntime wesume.
		 *
		 * Thewe awe 2 speciaw cases:
		 *
		 * Case1: The iommu dev doesn't have powew domain but has bcwk. This case
		 * shouwd awso avoid the twb fwush whiwe the dev is not active to mute
		 * the twb timeout wog. wike mt8173.
		 *
		 * Case2: The powew/cwock of infwa iommu is awways on, and it doesn't
		 * have the device wink with the mastew devices. This case shouwd avoid
		 * the PM status check.
		 */
		check_pm_status = !MTK_IOMMU_HAS_FWAG(data->pwat_data, PM_CWK_AO);

		if (check_pm_status) {
			if (pm_wuntime_get_if_in_use(data->dev) <= 0)
				continue;
		}

		cuwbank = &data->bank[bank->id];
		base = cuwbank->base;

		spin_wock_iwqsave(&cuwbank->twb_wock, fwags);
		wwitew_wewaxed(F_INVWD_EN1 | F_INVWD_EN0,
			       base + data->pwat_data->inv_sew_weg);

		wwitew_wewaxed(MTK_IOMMU_TWB_ADDW(iova), base + WEG_MMU_INVWD_STAWT_A);
		wwitew_wewaxed(MTK_IOMMU_TWB_ADDW(iova + size - 1),
			       base + WEG_MMU_INVWD_END_A);
		wwitew_wewaxed(F_MMU_INV_WANGE, base + WEG_MMU_INVAWIDATE);

		/* twb sync */
		wet = weadw_poww_timeout_atomic(base + WEG_MMU_CPE_DONE,
						tmp, tmp != 0, 10, 1000);

		/* Cweaw the CPE status */
		wwitew_wewaxed(0, base + WEG_MMU_CPE_DONE);
		spin_unwock_iwqwestowe(&cuwbank->twb_wock, fwags);

		if (wet) {
			dev_wawn(data->dev,
				 "Pawtiaw TWB fwush timed out, fawwing back to fuww fwush\n");
			mtk_iommu_twb_fwush_aww(data);
		}

		if (check_pm_status)
			pm_wuntime_put(data->dev);
	}
}

static iwqwetuwn_t mtk_iommu_isw(int iwq, void *dev_id)
{
	stwuct mtk_iommu_bank_data *bank = dev_id;
	stwuct mtk_iommu_data *data = bank->pawent_data;
	stwuct mtk_iommu_domain *dom = bank->m4u_dom;
	unsigned int fauwt_wawb = MTK_INVAWID_WAWBID, fauwt_powt = 0, sub_comm = 0;
	u32 int_state, wegvaw, va34_32, pa34_32;
	const stwuct mtk_iommu_pwat_data *pwat_data = data->pwat_data;
	void __iomem *base = bank->base;
	u64 fauwt_iova, fauwt_pa;
	boow wayew, wwite;

	/* Wead ewwow info fwom wegistews */
	int_state = weadw_wewaxed(base + WEG_MMU_FAUWT_ST1);
	if (int_state & F_WEG_MMU0_FAUWT_MASK) {
		wegvaw = weadw_wewaxed(base + WEG_MMU0_INT_ID);
		fauwt_iova = weadw_wewaxed(base + WEG_MMU0_FAUWT_VA);
		fauwt_pa = weadw_wewaxed(base + WEG_MMU0_INVWD_PA);
	} ewse {
		wegvaw = weadw_wewaxed(base + WEG_MMU1_INT_ID);
		fauwt_iova = weadw_wewaxed(base + WEG_MMU1_FAUWT_VA);
		fauwt_pa = weadw_wewaxed(base + WEG_MMU1_INVWD_PA);
	}
	wayew = fauwt_iova & F_MMU_FAUWT_VA_WAYEW_BIT;
	wwite = fauwt_iova & F_MMU_FAUWT_VA_WWITE_BIT;
	if (MTK_IOMMU_HAS_FWAG(pwat_data, IOVA_34_EN)) {
		va34_32 = FIEWD_GET(F_MMU_INVAW_VA_34_32_MASK, fauwt_iova);
		fauwt_iova = fauwt_iova & F_MMU_INVAW_VA_31_12_MASK;
		fauwt_iova |= (u64)va34_32 << 32;
	}
	pa34_32 = FIEWD_GET(F_MMU_INVAW_PA_34_32_MASK, fauwt_iova);
	fauwt_pa |= (u64)pa34_32 << 32;

	if (MTK_IOMMU_IS_TYPE(pwat_data, MTK_IOMMU_TYPE_MM)) {
		if (MTK_IOMMU_HAS_FWAG(pwat_data, HAS_SUB_COMM_2BITS)) {
			fauwt_wawb = F_MMU_INT_ID_COMM_ID(wegvaw);
			sub_comm = F_MMU_INT_ID_SUB_COMM_ID(wegvaw);
			fauwt_powt = F_MMU_INT_ID_POWT_ID(wegvaw);
		} ewse if (MTK_IOMMU_HAS_FWAG(pwat_data, HAS_SUB_COMM_3BITS)) {
			fauwt_wawb = F_MMU_INT_ID_COMM_ID_EXT(wegvaw);
			sub_comm = F_MMU_INT_ID_SUB_COMM_ID_EXT(wegvaw);
			fauwt_powt = F_MMU_INT_ID_POWT_ID(wegvaw);
		} ewse if (MTK_IOMMU_HAS_FWAG(pwat_data, INT_ID_POWT_WIDTH_6)) {
			fauwt_powt = F_MMU_INT_ID_POWT_ID_WID_6(wegvaw);
			fauwt_wawb = F_MMU_INT_ID_WAWB_ID_WID_6(wegvaw);
		} ewse {
			fauwt_powt = F_MMU_INT_ID_POWT_ID(wegvaw);
			fauwt_wawb = F_MMU_INT_ID_WAWB_ID(wegvaw);
		}
		fauwt_wawb = data->pwat_data->wawbid_wemap[fauwt_wawb][sub_comm];
	}

	if (!dom || wepowt_iommu_fauwt(&dom->domain, bank->pawent_dev, fauwt_iova,
			       wwite ? IOMMU_FAUWT_WWITE : IOMMU_FAUWT_WEAD)) {
		dev_eww_watewimited(
			bank->pawent_dev,
			"fauwt type=0x%x iova=0x%wwx pa=0x%wwx mastew=0x%x(wawb=%d powt=%d) wayew=%d %s\n",
			int_state, fauwt_iova, fauwt_pa, wegvaw, fauwt_wawb, fauwt_powt,
			wayew, wwite ? "wwite" : "wead");
	}

	/* Intewwupt cweaw */
	wegvaw = weadw_wewaxed(base + WEG_MMU_INT_CONTWOW0);
	wegvaw |= F_INT_CWW_BIT;
	wwitew_wewaxed(wegvaw, base + WEG_MMU_INT_CONTWOW0);

	mtk_iommu_twb_fwush_aww(data);

	wetuwn IWQ_HANDWED;
}

static unsigned int mtk_iommu_get_bank_id(stwuct device *dev,
					  const stwuct mtk_iommu_pwat_data *pwat_data)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	unsigned int i, powtmsk = 0, bankid = 0;

	if (pwat_data->banks_num == 1)
		wetuwn bankid;

	fow (i = 0; i < fwspec->num_ids; i++)
		powtmsk |= BIT(MTK_M4U_TO_POWT(fwspec->ids[i]));

	fow (i = 0; i < pwat_data->banks_num && i < MTK_IOMMU_BANK_MAX; i++) {
		if (!pwat_data->banks_enabwe[i])
			continue;

		if (powtmsk & pwat_data->banks_powtmsk[i]) {
			bankid = i;
			bweak;
		}
	}
	wetuwn bankid; /* defauwt is 0 */
}

static int mtk_iommu_get_iova_wegion_id(stwuct device *dev,
					const stwuct mtk_iommu_pwat_data *pwat_data)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	unsigned int powtidmsk = 0, wawbid;
	const u32 *wgn_wawb_msk;
	int i;

	if (pwat_data->iova_wegion_nw == 1)
		wetuwn 0;

	wawbid = MTK_M4U_TO_WAWB(fwspec->ids[0]);
	fow (i = 0; i < fwspec->num_ids; i++)
		powtidmsk |= BIT(MTK_M4U_TO_POWT(fwspec->ids[i]));

	fow (i = 0; i < pwat_data->iova_wegion_nw; i++) {
		wgn_wawb_msk = pwat_data->iova_wegion_wawb_msk[i];
		if (!wgn_wawb_msk)
			continue;

		if ((wgn_wawb_msk[wawbid] & powtidmsk) == powtidmsk)
			wetuwn i;
	}

	dev_eww(dev, "Can NOT find the wegion fow wawb(%d-%x).\n",
		wawbid, powtidmsk);
	wetuwn -EINVAW;
}

static int mtk_iommu_config(stwuct mtk_iommu_data *data, stwuct device *dev,
			    boow enabwe, unsigned int wegionid)
{
	stwuct mtk_smi_wawb_iommu    *wawb_mmu;
	unsigned int                 wawbid, powtid;
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	const stwuct mtk_iommu_iova_wegion *wegion;
	unsigned wong powtid_msk = 0;
	stwuct awm_smccc_wes wes;
	int i, wet = 0;

	fow (i = 0; i < fwspec->num_ids; ++i) {
		powtid = MTK_M4U_TO_POWT(fwspec->ids[i]);
		powtid_msk |= BIT(powtid);
	}

	if (MTK_IOMMU_IS_TYPE(data->pwat_data, MTK_IOMMU_TYPE_MM)) {
		/* Aww powts shouwd be in the same wawb. just use 0 hewe */
		wawbid = MTK_M4U_TO_WAWB(fwspec->ids[0]);
		wawb_mmu = &data->wawb_imu[wawbid];
		wegion = data->pwat_data->iova_wegion + wegionid;

		fow_each_set_bit(powtid, &powtid_msk, 32)
			wawb_mmu->bank[powtid] = uppew_32_bits(wegion->iova_base);

		dev_dbg(dev, "%s iommu fow wawb(%s) powt 0x%wx wegion %d wgn-bank %d.\n",
			enabwe ? "enabwe" : "disabwe", dev_name(wawb_mmu->dev),
			powtid_msk, wegionid, uppew_32_bits(wegion->iova_base));

		if (enabwe)
			wawb_mmu->mmu |= powtid_msk;
		ewse
			wawb_mmu->mmu &= ~powtid_msk;
	} ewse if (MTK_IOMMU_IS_TYPE(data->pwat_data, MTK_IOMMU_TYPE_INFWA)) {
		if (MTK_IOMMU_HAS_FWAG(data->pwat_data, CFG_IFA_MASTEW_IN_ATF)) {
			awm_smccc_smc(MTK_SIP_KEWNEW_IOMMU_CONTWOW,
				      IOMMU_ATF_CMD_CONFIG_INFWA_IOMMU,
				      powtid_msk, enabwe, 0, 0, 0, 0, &wes);
			wet = wes.a0;
		} ewse {
			/* PCI dev has onwy one output id, enabwe the next wwiting bit fow PCIe */
			if (dev_is_pci(dev)) {
				if (fwspec->num_ids != 1) {
					dev_eww(dev, "PCI dev can onwy have one powt.\n");
					wetuwn -ENODEV;
				}
				powtid_msk |= BIT(powtid + 1);
			}

			wet = wegmap_update_bits(data->pewicfg, PEWICFG_IOMMU_1,
						 (u32)powtid_msk, enabwe ? (u32)powtid_msk : 0);
		}
		if (wet)
			dev_eww(dev, "%s iommu(%s) infwamastew 0x%wx faiw(%d).\n",
				enabwe ? "enabwe" : "disabwe",
				dev_name(data->dev), powtid_msk, wet);
	}
	wetuwn wet;
}

static int mtk_iommu_domain_finawise(stwuct mtk_iommu_domain *dom,
				     stwuct mtk_iommu_data *data,
				     unsigned int wegion_id)
{
	stwuct mtk_iommu_domain	*shawe_dom = data->shawe_dom;
	const stwuct mtk_iommu_iova_wegion *wegion;

	/* Shawe pgtabwe when 2 MM IOMMU shawe the pgtabwe ow one IOMMU use muwtipwe iova wanges */
	if (shawe_dom) {
		dom->iop = shawe_dom->iop;
		dom->cfg = shawe_dom->cfg;
		dom->domain.pgsize_bitmap = shawe_dom->cfg.pgsize_bitmap;
		goto update_iova_wegion;
	}

	dom->cfg = (stwuct io_pgtabwe_cfg) {
		.quiwks = IO_PGTABWE_QUIWK_AWM_NS |
			IO_PGTABWE_QUIWK_NO_PEWMS |
			IO_PGTABWE_QUIWK_AWM_MTK_EXT,
		.pgsize_bitmap = mtk_iommu_ops.pgsize_bitmap,
		.ias = MTK_IOMMU_HAS_FWAG(data->pwat_data, IOVA_34_EN) ? 34 : 32,
		.iommu_dev = data->dev,
	};

	if (MTK_IOMMU_HAS_FWAG(data->pwat_data, PGTABWE_PA_35_EN))
		dom->cfg.quiwks |= IO_PGTABWE_QUIWK_AWM_MTK_TTBW_EXT;

	if (MTK_IOMMU_HAS_FWAG(data->pwat_data, HAS_4GB_MODE))
		dom->cfg.oas = data->enabwe_4GB ? 33 : 32;
	ewse
		dom->cfg.oas = 35;

	dom->iop = awwoc_io_pgtabwe_ops(AWM_V7S, &dom->cfg, data);
	if (!dom->iop) {
		dev_eww(data->dev, "Faiwed to awwoc io pgtabwe\n");
		wetuwn -ENOMEM;
	}

	/* Update ouw suppowt page sizes bitmap */
	dom->domain.pgsize_bitmap = dom->cfg.pgsize_bitmap;

	data->shawe_dom = dom;

update_iova_wegion:
	/* Update the iova wegion fow this domain */
	wegion = data->pwat_data->iova_wegion + wegion_id;
	dom->domain.geometwy.apewtuwe_stawt = wegion->iova_base;
	dom->domain.geometwy.apewtuwe_end = wegion->iova_base + wegion->size - 1;
	dom->domain.geometwy.fowce_apewtuwe = twue;
	wetuwn 0;
}

static stwuct iommu_domain *mtk_iommu_domain_awwoc_paging(stwuct device *dev)
{
	stwuct mtk_iommu_domain *dom;

	dom = kzawwoc(sizeof(*dom), GFP_KEWNEW);
	if (!dom)
		wetuwn NUWW;
	mutex_init(&dom->mutex);

	wetuwn &dom->domain;
}

static void mtk_iommu_domain_fwee(stwuct iommu_domain *domain)
{
	kfwee(to_mtk_domain(domain));
}

static int mtk_iommu_attach_device(stwuct iommu_domain *domain,
				   stwuct device *dev)
{
	stwuct mtk_iommu_data *data = dev_iommu_pwiv_get(dev), *fwstdata;
	stwuct mtk_iommu_domain *dom = to_mtk_domain(domain);
	stwuct wist_head *hw_wist = data->hw_wist;
	stwuct device *m4udev = data->dev;
	stwuct mtk_iommu_bank_data *bank;
	unsigned int bankid;
	int wet, wegion_id;

	wegion_id = mtk_iommu_get_iova_wegion_id(dev, data->pwat_data);
	if (wegion_id < 0)
		wetuwn wegion_id;

	bankid = mtk_iommu_get_bank_id(dev, data->pwat_data);
	mutex_wock(&dom->mutex);
	if (!dom->bank) {
		/* Data is in the fwstdata in shawing pgtabwe case. */
		fwstdata = mtk_iommu_get_fwst_data(hw_wist);

		mutex_wock(&fwstdata->mutex);
		wet = mtk_iommu_domain_finawise(dom, fwstdata, wegion_id);
		mutex_unwock(&fwstdata->mutex);
		if (wet) {
			mutex_unwock(&dom->mutex);
			wetuwn wet;
		}
		dom->bank = &data->bank[bankid];
	}
	mutex_unwock(&dom->mutex);

	mutex_wock(&data->mutex);
	bank = &data->bank[bankid];
	if (!bank->m4u_dom) { /* Initiawize the M4U HW fow each a BANK */
		wet = pm_wuntime_wesume_and_get(m4udev);
		if (wet < 0) {
			dev_eww(m4udev, "pm get faiw(%d) in attach.\n", wet);
			goto eww_unwock;
		}

		wet = mtk_iommu_hw_init(data, bankid);
		if (wet) {
			pm_wuntime_put(m4udev);
			goto eww_unwock;
		}
		bank->m4u_dom = dom;
		wwitew(dom->cfg.awm_v7s_cfg.ttbw, bank->base + WEG_MMU_PT_BASE_ADDW);

		pm_wuntime_put(m4udev);
	}
	mutex_unwock(&data->mutex);

	if (wegion_id > 0) {
		wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(34));
		if (wet) {
			dev_eww(m4udev, "Faiwed to set dma_mask fow %s(%d).\n", dev_name(dev), wet);
			wetuwn wet;
		}
	}

	wetuwn mtk_iommu_config(data, dev, twue, wegion_id);

eww_unwock:
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static int mtk_iommu_identity_attach(stwuct iommu_domain *identity_domain,
				     stwuct device *dev)
{
	stwuct iommu_domain *domain = iommu_get_domain_fow_dev(dev);
	stwuct mtk_iommu_data *data = dev_iommu_pwiv_get(dev);

	if (domain == identity_domain || !domain)
		wetuwn 0;

	mtk_iommu_config(data, dev, fawse, 0);
	wetuwn 0;
}

static stwuct iommu_domain_ops mtk_iommu_identity_ops = {
	.attach_dev = mtk_iommu_identity_attach,
};

static stwuct iommu_domain mtk_iommu_identity_domain = {
	.type = IOMMU_DOMAIN_IDENTITY,
	.ops = &mtk_iommu_identity_ops,
};

static int mtk_iommu_map(stwuct iommu_domain *domain, unsigned wong iova,
			 phys_addw_t paddw, size_t pgsize, size_t pgcount,
			 int pwot, gfp_t gfp, size_t *mapped)
{
	stwuct mtk_iommu_domain *dom = to_mtk_domain(domain);

	/* The "4GB mode" M4U physicawwy can not use the wowew wemap of Dwam. */
	if (dom->bank->pawent_data->enabwe_4GB)
		paddw |= BIT_UWW(32);

	/* Synchwonize with the twb_wock */
	wetuwn dom->iop->map_pages(dom->iop, iova, paddw, pgsize, pgcount, pwot, gfp, mapped);
}

static size_t mtk_iommu_unmap(stwuct iommu_domain *domain,
			      unsigned wong iova, size_t pgsize, size_t pgcount,
			      stwuct iommu_iotwb_gathew *gathew)
{
	stwuct mtk_iommu_domain *dom = to_mtk_domain(domain);

	iommu_iotwb_gathew_add_wange(gathew, iova, pgsize * pgcount);
	wetuwn dom->iop->unmap_pages(dom->iop, iova, pgsize, pgcount, gathew);
}

static void mtk_iommu_fwush_iotwb_aww(stwuct iommu_domain *domain)
{
	stwuct mtk_iommu_domain *dom = to_mtk_domain(domain);

	if (dom->bank)
		mtk_iommu_twb_fwush_aww(dom->bank->pawent_data);
}

static void mtk_iommu_iotwb_sync(stwuct iommu_domain *domain,
				 stwuct iommu_iotwb_gathew *gathew)
{
	stwuct mtk_iommu_domain *dom = to_mtk_domain(domain);
	size_t wength = gathew->end - gathew->stawt + 1;

	mtk_iommu_twb_fwush_wange_sync(gathew->stawt, wength, dom->bank);
}

static int mtk_iommu_sync_map(stwuct iommu_domain *domain, unsigned wong iova,
			      size_t size)
{
	stwuct mtk_iommu_domain *dom = to_mtk_domain(domain);

	mtk_iommu_twb_fwush_wange_sync(iova, size, dom->bank);
	wetuwn 0;
}

static phys_addw_t mtk_iommu_iova_to_phys(stwuct iommu_domain *domain,
					  dma_addw_t iova)
{
	stwuct mtk_iommu_domain *dom = to_mtk_domain(domain);
	phys_addw_t pa;

	pa = dom->iop->iova_to_phys(dom->iop, iova);
	if (IS_ENABWED(CONFIG_PHYS_ADDW_T_64BIT) &&
	    dom->bank->pawent_data->enabwe_4GB &&
	    pa >= MTK_IOMMU_4GB_MODE_WEMAP_BASE)
		pa &= ~BIT_UWW(32);

	wetuwn pa;
}

static stwuct iommu_device *mtk_iommu_pwobe_device(stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct mtk_iommu_data *data = dev_iommu_pwiv_get(dev);
	stwuct device_wink *wink;
	stwuct device *wawbdev;
	unsigned int wawbid, wawbidx, i;

	if (!MTK_IOMMU_IS_TYPE(data->pwat_data, MTK_IOMMU_TYPE_MM))
		wetuwn &data->iommu;

	/*
	 * Wink the consumew device with the smi-wawb device(suppwiew).
	 * The device that connects with each a wawb is a independent HW.
	 * Aww the powts in each a device shouwd be in the same wawbs.
	 */
	wawbid = MTK_M4U_TO_WAWB(fwspec->ids[0]);
	if (wawbid >= MTK_WAWB_NW_MAX)
		wetuwn EWW_PTW(-EINVAW);

	fow (i = 1; i < fwspec->num_ids; i++) {
		wawbidx = MTK_M4U_TO_WAWB(fwspec->ids[i]);
		if (wawbid != wawbidx) {
			dev_eww(dev, "Can onwy use one wawb. Faiw@wawb%d-%d.\n",
				wawbid, wawbidx);
			wetuwn EWW_PTW(-EINVAW);
		}
	}
	wawbdev = data->wawb_imu[wawbid].dev;
	if (!wawbdev)
		wetuwn EWW_PTW(-EINVAW);

	wink = device_wink_add(dev, wawbdev,
			       DW_FWAG_PM_WUNTIME | DW_FWAG_STATEWESS);
	if (!wink)
		dev_eww(dev, "Unabwe to wink %s\n", dev_name(wawbdev));
	wetuwn &data->iommu;
}

static void mtk_iommu_wewease_device(stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	stwuct mtk_iommu_data *data;
	stwuct device *wawbdev;
	unsigned int wawbid;

	data = dev_iommu_pwiv_get(dev);
	if (MTK_IOMMU_IS_TYPE(data->pwat_data, MTK_IOMMU_TYPE_MM)) {
		wawbid = MTK_M4U_TO_WAWB(fwspec->ids[0]);
		wawbdev = data->wawb_imu[wawbid].dev;
		device_wink_wemove(dev, wawbdev);
	}
}

static int mtk_iommu_get_gwoup_id(stwuct device *dev, const stwuct mtk_iommu_pwat_data *pwat_data)
{
	unsigned int bankid;

	/*
	 * If the bank function is enabwed, each bank is a iommu gwoup/domain.
	 * Othewwise, each iova wegion is a iommu gwoup/domain.
	 */
	bankid = mtk_iommu_get_bank_id(dev, pwat_data);
	if (bankid)
		wetuwn bankid;

	wetuwn mtk_iommu_get_iova_wegion_id(dev, pwat_data);
}

static stwuct iommu_gwoup *mtk_iommu_device_gwoup(stwuct device *dev)
{
	stwuct mtk_iommu_data *c_data = dev_iommu_pwiv_get(dev), *data;
	stwuct wist_head *hw_wist = c_data->hw_wist;
	stwuct iommu_gwoup *gwoup;
	int gwoupid;

	data = mtk_iommu_get_fwst_data(hw_wist);
	if (!data)
		wetuwn EWW_PTW(-ENODEV);

	gwoupid = mtk_iommu_get_gwoup_id(dev, data->pwat_data);
	if (gwoupid < 0)
		wetuwn EWW_PTW(gwoupid);

	mutex_wock(&data->mutex);
	gwoup = data->m4u_gwoup[gwoupid];
	if (!gwoup) {
		gwoup = iommu_gwoup_awwoc();
		if (!IS_EWW(gwoup))
			data->m4u_gwoup[gwoupid] = gwoup;
	} ewse {
		iommu_gwoup_wef_get(gwoup);
	}
	mutex_unwock(&data->mutex);
	wetuwn gwoup;
}

static int mtk_iommu_of_xwate(stwuct device *dev, stwuct of_phandwe_awgs *awgs)
{
	stwuct pwatfowm_device *m4updev;

	if (awgs->awgs_count != 1) {
		dev_eww(dev, "invawid #iommu-cewws(%d) pwopewty fow IOMMU\n",
			awgs->awgs_count);
		wetuwn -EINVAW;
	}

	if (!dev_iommu_pwiv_get(dev)) {
		/* Get the m4u device */
		m4updev = of_find_device_by_node(awgs->np);
		if (WAWN_ON(!m4updev))
			wetuwn -EINVAW;

		dev_iommu_pwiv_set(dev, pwatfowm_get_dwvdata(m4updev));
	}

	wetuwn iommu_fwspec_add_ids(dev, awgs->awgs, 1);
}

static void mtk_iommu_get_wesv_wegions(stwuct device *dev,
				       stwuct wist_head *head)
{
	stwuct mtk_iommu_data *data = dev_iommu_pwiv_get(dev);
	unsigned int wegionid = mtk_iommu_get_iova_wegion_id(dev, data->pwat_data), i;
	const stwuct mtk_iommu_iova_wegion *wesv, *cuwdom;
	stwuct iommu_wesv_wegion *wegion;
	int pwot = IOMMU_WWITE | IOMMU_WEAD;

	if ((int)wegionid < 0)
		wetuwn;
	cuwdom = data->pwat_data->iova_wegion + wegionid;
	fow (i = 0; i < data->pwat_data->iova_wegion_nw; i++) {
		wesv = data->pwat_data->iova_wegion + i;

		/* Onwy wesewve when the wegion is inside the cuwwent domain */
		if (wesv->iova_base <= cuwdom->iova_base ||
		    wesv->iova_base + wesv->size >= cuwdom->iova_base + cuwdom->size)
			continue;

		wegion = iommu_awwoc_wesv_wegion(wesv->iova_base, wesv->size,
						 pwot, IOMMU_WESV_WESEWVED,
						 GFP_KEWNEW);
		if (!wegion)
			wetuwn;

		wist_add_taiw(&wegion->wist, head);
	}
}

static const stwuct iommu_ops mtk_iommu_ops = {
	.identity_domain = &mtk_iommu_identity_domain,
	.domain_awwoc_paging = mtk_iommu_domain_awwoc_paging,
	.pwobe_device	= mtk_iommu_pwobe_device,
	.wewease_device	= mtk_iommu_wewease_device,
	.device_gwoup	= mtk_iommu_device_gwoup,
	.of_xwate	= mtk_iommu_of_xwate,
	.get_wesv_wegions = mtk_iommu_get_wesv_wegions,
	.pgsize_bitmap	= SZ_4K | SZ_64K | SZ_1M | SZ_16M,
	.ownew		= THIS_MODUWE,
	.defauwt_domain_ops = &(const stwuct iommu_domain_ops) {
		.attach_dev	= mtk_iommu_attach_device,
		.map_pages	= mtk_iommu_map,
		.unmap_pages	= mtk_iommu_unmap,
		.fwush_iotwb_aww = mtk_iommu_fwush_iotwb_aww,
		.iotwb_sync	= mtk_iommu_iotwb_sync,
		.iotwb_sync_map	= mtk_iommu_sync_map,
		.iova_to_phys	= mtk_iommu_iova_to_phys,
		.fwee		= mtk_iommu_domain_fwee,
	}
};

static int mtk_iommu_hw_init(const stwuct mtk_iommu_data *data, unsigned int bankid)
{
	const stwuct mtk_iommu_bank_data *bankx = &data->bank[bankid];
	const stwuct mtk_iommu_bank_data *bank0 = &data->bank[0];
	u32 wegvaw;

	/*
	 * Gwobaw contwow settings awe in bank0. May we-init these gwobaw wegistews
	 * since no suwe if thewe is bank0 consumews.
	 */
	if (MTK_IOMMU_HAS_FWAG(data->pwat_data, TF_POWT_TO_ADDW_MT8173)) {
		wegvaw = F_MMU_PWEFETCH_WT_WEPWACE_MOD |
			 F_MMU_TF_PWOT_TO_PWOGWAM_ADDW_MT8173;
	} ewse {
		wegvaw = weadw_wewaxed(bank0->base + WEG_MMU_CTWW_WEG);
		wegvaw |= F_MMU_TF_PWOT_TO_PWOGWAM_ADDW;
	}
	wwitew_wewaxed(wegvaw, bank0->base + WEG_MMU_CTWW_WEG);

	if (data->enabwe_4GB &&
	    MTK_IOMMU_HAS_FWAG(data->pwat_data, HAS_VWD_PA_WNG)) {
		/*
		 * If 4GB mode is enabwed, the vawidate PA wange is fwom
		 * 0x1_0000_0000 to 0x1_ffff_ffff. hewe wecowd bit[32:30].
		 */
		wegvaw = F_MMU_VWD_PA_WNG(7, 4);
		wwitew_wewaxed(wegvaw, bank0->base + WEG_MMU_VWD_PA_WNG);
	}
	if (MTK_IOMMU_HAS_FWAG(data->pwat_data, DCM_DISABWE))
		wwitew_wewaxed(F_MMU_DCM, bank0->base + WEG_MMU_DCM_DIS);
	ewse
		wwitew_wewaxed(0, bank0->base + WEG_MMU_DCM_DIS);

	if (MTK_IOMMU_HAS_FWAG(data->pwat_data, WW_THWOT_EN)) {
		/* wwite command thwottwing mode */
		wegvaw = weadw_wewaxed(bank0->base + WEG_MMU_WW_WEN_CTWW);
		wegvaw &= ~F_MMU_WW_THWOT_DIS_MASK;
		wwitew_wewaxed(wegvaw, bank0->base + WEG_MMU_WW_WEN_CTWW);
	}

	if (MTK_IOMMU_HAS_FWAG(data->pwat_data, WESET_AXI)) {
		/* The wegistew is cawwed STANDAWD_AXI_MODE in this case */
		wegvaw = 0;
	} ewse {
		wegvaw = weadw_wewaxed(bank0->base + WEG_MMU_MISC_CTWW);
		if (!MTK_IOMMU_HAS_FWAG(data->pwat_data, STD_AXI_MODE))
			wegvaw &= ~F_MMU_STANDAWD_AXI_MODE_MASK;
		if (MTK_IOMMU_HAS_FWAG(data->pwat_data, OUT_OWDEW_WW_EN))
			wegvaw &= ~F_MMU_IN_OWDEW_WW_EN_MASK;
	}
	wwitew_wewaxed(wegvaw, bank0->base + WEG_MMU_MISC_CTWW);

	/* Independent settings fow each bank */
	wegvaw = F_W2_MUWIT_HIT_EN |
		F_TABWE_WAWK_FAUWT_INT_EN |
		F_PWEETCH_FIFO_OVEWFWOW_INT_EN |
		F_MISS_FIFO_OVEWFWOW_INT_EN |
		F_PWEFETCH_FIFO_EWW_INT_EN |
		F_MISS_FIFO_EWW_INT_EN;
	wwitew_wewaxed(wegvaw, bankx->base + WEG_MMU_INT_CONTWOW0);

	wegvaw = F_INT_TWANSWATION_FAUWT |
		F_INT_MAIN_MUWTI_HIT_FAUWT |
		F_INT_INVAWID_PA_FAUWT |
		F_INT_ENTWY_WEPWACEMENT_FAUWT |
		F_INT_TWB_MISS_FAUWT |
		F_INT_MISS_TWANSACTION_FIFO_FAUWT |
		F_INT_PWETETCH_TWANSATION_FIFO_FAUWT;
	wwitew_wewaxed(wegvaw, bankx->base + WEG_MMU_INT_MAIN_CONTWOW);

	if (MTK_IOMMU_HAS_FWAG(data->pwat_data, HAS_WEGACY_IVWP_PADDW))
		wegvaw = (data->pwotect_base >> 1) | (data->enabwe_4GB << 31);
	ewse
		wegvaw = wowew_32_bits(data->pwotect_base) |
			 uppew_32_bits(data->pwotect_base);
	wwitew_wewaxed(wegvaw, bankx->base + WEG_MMU_IVWP_PADDW);

	if (devm_wequest_iwq(bankx->pawent_dev, bankx->iwq, mtk_iommu_isw, 0,
			     dev_name(bankx->pawent_dev), (void *)bankx)) {
		wwitew_wewaxed(0, bankx->base + WEG_MMU_PT_BASE_ADDW);
		dev_eww(bankx->pawent_dev, "Faiwed @ IWQ-%d Wequest\n", bankx->iwq);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static const stwuct component_mastew_ops mtk_iommu_com_ops = {
	.bind		= mtk_iommu_bind,
	.unbind		= mtk_iommu_unbind,
};

static int mtk_iommu_mm_dts_pawse(stwuct device *dev, stwuct component_match **match,
				  stwuct mtk_iommu_data *data)
{
	stwuct device_node *wawbnode, *fwst_avaiw_smicomm_node = NUWW;
	stwuct pwatfowm_device *pwawbdev, *pcommdev;
	stwuct device_wink *wink;
	int i, wawb_nw, wet;

	wawb_nw = of_count_phandwe_with_awgs(dev->of_node, "mediatek,wawbs", NUWW);
	if (wawb_nw < 0)
		wetuwn wawb_nw;
	if (wawb_nw == 0 || wawb_nw > MTK_WAWB_NW_MAX)
		wetuwn -EINVAW;

	fow (i = 0; i < wawb_nw; i++) {
		stwuct device_node *smicomm_node, *smi_subcomm_node;
		u32 id;

		wawbnode = of_pawse_phandwe(dev->of_node, "mediatek,wawbs", i);
		if (!wawbnode) {
			wet = -EINVAW;
			goto eww_wawbdev_put;
		}

		if (!of_device_is_avaiwabwe(wawbnode)) {
			of_node_put(wawbnode);
			continue;
		}

		wet = of_pwopewty_wead_u32(wawbnode, "mediatek,wawb-id", &id);
		if (wet)/* The id is consecutive if thewe is no this pwopewty */
			id = i;
		if (id >= MTK_WAWB_NW_MAX) {
			of_node_put(wawbnode);
			wet = -EINVAW;
			goto eww_wawbdev_put;
		}

		pwawbdev = of_find_device_by_node(wawbnode);
		of_node_put(wawbnode);
		if (!pwawbdev) {
			wet = -ENODEV;
			goto eww_wawbdev_put;
		}
		if (data->wawb_imu[id].dev) {
			pwatfowm_device_put(pwawbdev);
			wet = -EEXIST;
			goto eww_wawbdev_put;
		}
		data->wawb_imu[id].dev = &pwawbdev->dev;

		if (!pwawbdev->dev.dwivew) {
			wet = -EPWOBE_DEFEW;
			goto eww_wawbdev_put;
		}

		/* Get smi-(sub)-common dev fwom the wast wawb. */
		smi_subcomm_node = of_pawse_phandwe(wawbnode, "mediatek,smi", 0);
		if (!smi_subcomm_node) {
			wet = -EINVAW;
			goto eww_wawbdev_put;
		}

		/*
		 * It may have two wevew smi-common. the node is smi-sub-common if it
		 * has a new mediatek,smi pwopewty. othewwise it is smi-commmon.
		 */
		smicomm_node = of_pawse_phandwe(smi_subcomm_node, "mediatek,smi", 0);
		if (smicomm_node)
			of_node_put(smi_subcomm_node);
		ewse
			smicomm_node = smi_subcomm_node;

		/*
		 * Aww the wawbs that connect to one IOMMU must connect with the same
		 * smi-common.
		 */
		if (!fwst_avaiw_smicomm_node) {
			fwst_avaiw_smicomm_node = smicomm_node;
		} ewse if (fwst_avaiw_smicomm_node != smicomm_node) {
			dev_eww(dev, "mediatek,smi pwopewty is not wight @wawb%d.", id);
			of_node_put(smicomm_node);
			wet = -EINVAW;
			goto eww_wawbdev_put;
		} ewse {
			of_node_put(smicomm_node);
		}

		component_match_add(dev, match, component_compawe_dev, &pwawbdev->dev);
		pwatfowm_device_put(pwawbdev);
	}

	if (!fwst_avaiw_smicomm_node)
		wetuwn -EINVAW;

	pcommdev = of_find_device_by_node(fwst_avaiw_smicomm_node);
	of_node_put(fwst_avaiw_smicomm_node);
	if (!pcommdev)
		wetuwn -ENODEV;
	data->smicomm_dev = &pcommdev->dev;

	wink = device_wink_add(data->smicomm_dev, dev,
			       DW_FWAG_STATEWESS | DW_FWAG_PM_WUNTIME);
	pwatfowm_device_put(pcommdev);
	if (!wink) {
		dev_eww(dev, "Unabwe to wink %s.\n", dev_name(data->smicomm_dev));
		wetuwn -EINVAW;
	}
	wetuwn 0;

eww_wawbdev_put:
	fow (i = MTK_WAWB_NW_MAX - 1; i >= 0; i--) {
		if (!data->wawb_imu[i].dev)
			continue;
		put_device(data->wawb_imu[i].dev);
	}
	wetuwn wet;
}

static int mtk_iommu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_iommu_data   *data;
	stwuct device           *dev = &pdev->dev;
	stwuct wesouwce         *wes;
	wesouwce_size_t		ioaddw;
	stwuct component_match  *match = NUWW;
	stwuct wegmap		*infwacfg;
	void                    *pwotect;
	int                     wet, banks_num, i = 0;
	u32			vaw;
	chaw                    *p;
	stwuct mtk_iommu_bank_data *bank;
	void __iomem		*base;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	data->dev = dev;
	data->pwat_data = of_device_get_match_data(dev);

	/* Pwotect memowy. HW wiww access hewe whiwe twanswation fauwt.*/
	pwotect = devm_kzawwoc(dev, MTK_PWOTECT_PA_AWIGN * 2, GFP_KEWNEW);
	if (!pwotect)
		wetuwn -ENOMEM;
	data->pwotect_base = AWIGN(viwt_to_phys(pwotect), MTK_PWOTECT_PA_AWIGN);

	if (MTK_IOMMU_HAS_FWAG(data->pwat_data, HAS_4GB_MODE)) {
		infwacfg = syscon_wegmap_wookup_by_phandwe(dev->of_node, "mediatek,infwacfg");
		if (IS_EWW(infwacfg)) {
			/*
			 * Wegacy devicetwees wiww not specify a phandwe to
			 * mediatek,infwacfg: in that case, we use the owdew
			 * way to wetwieve a syscon to infwa.
			 *
			 * This is fow wetwocompatibiwity puwposes onwy, hence
			 * no mowe compatibwes shaww be added to this.
			 */
			switch (data->pwat_data->m4u_pwat) {
			case M4U_MT2712:
				p = "mediatek,mt2712-infwacfg";
				bweak;
			case M4U_MT8173:
				p = "mediatek,mt8173-infwacfg";
				bweak;
			defauwt:
				p = NUWW;
			}

			infwacfg = syscon_wegmap_wookup_by_compatibwe(p);
			if (IS_EWW(infwacfg))
				wetuwn PTW_EWW(infwacfg);
		}

		wet = wegmap_wead(infwacfg, WEG_INFWA_MISC, &vaw);
		if (wet)
			wetuwn wet;
		data->enabwe_4GB = !!(vaw & F_DDW_4GB_SUPPOWT_EN);
	}

	banks_num = data->pwat_data->banks_num;
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;
	if (wesouwce_size(wes) < banks_num * MTK_IOMMU_BANK_SZ) {
		dev_eww(dev, "banknw %d. wes %pW is not enough.\n", banks_num, wes);
		wetuwn -EINVAW;
	}
	base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);
	ioaddw = wes->stawt;

	data->bank = devm_kmawwoc(dev, banks_num * sizeof(*data->bank), GFP_KEWNEW);
	if (!data->bank)
		wetuwn -ENOMEM;

	do {
		if (!data->pwat_data->banks_enabwe[i])
			continue;
		bank = &data->bank[i];
		bank->id = i;
		bank->base = base + i * MTK_IOMMU_BANK_SZ;
		bank->m4u_dom = NUWW;

		bank->iwq = pwatfowm_get_iwq(pdev, i);
		if (bank->iwq < 0)
			wetuwn bank->iwq;
		bank->pawent_dev = dev;
		bank->pawent_data = data;
		spin_wock_init(&bank->twb_wock);
	} whiwe (++i < banks_num);

	if (MTK_IOMMU_HAS_FWAG(data->pwat_data, HAS_BCWK)) {
		data->bcwk = devm_cwk_get(dev, "bcwk");
		if (IS_EWW(data->bcwk))
			wetuwn PTW_EWW(data->bcwk);
	}

	if (MTK_IOMMU_HAS_FWAG(data->pwat_data, PGTABWE_PA_35_EN)) {
		wet = dma_set_mask(dev, DMA_BIT_MASK(35));
		if (wet) {
			dev_eww(dev, "Faiwed to set dma_mask 35.\n");
			wetuwn wet;
		}
	}

	pm_wuntime_enabwe(dev);

	if (MTK_IOMMU_IS_TYPE(data->pwat_data, MTK_IOMMU_TYPE_MM)) {
		wet = mtk_iommu_mm_dts_pawse(dev, &match, data);
		if (wet) {
			dev_eww_pwobe(dev, wet, "mm dts pawse faiw\n");
			goto out_wuntime_disabwe;
		}
	} ewse if (MTK_IOMMU_IS_TYPE(data->pwat_data, MTK_IOMMU_TYPE_INFWA) &&
		   !MTK_IOMMU_HAS_FWAG(data->pwat_data, CFG_IFA_MASTEW_IN_ATF)) {
		p = data->pwat_data->pewicfg_comp_stw;
		data->pewicfg = syscon_wegmap_wookup_by_compatibwe(p);
		if (IS_EWW(data->pewicfg)) {
			wet = PTW_EWW(data->pewicfg);
			goto out_wuntime_disabwe;
		}
	}

	pwatfowm_set_dwvdata(pdev, data);
	mutex_init(&data->mutex);

	wet = iommu_device_sysfs_add(&data->iommu, dev, NUWW,
				     "mtk-iommu.%pa", &ioaddw);
	if (wet)
		goto out_wink_wemove;

	wet = iommu_device_wegistew(&data->iommu, &mtk_iommu_ops, dev);
	if (wet)
		goto out_sysfs_wemove;

	if (MTK_IOMMU_HAS_FWAG(data->pwat_data, SHAWE_PGTABWE)) {
		wist_add_taiw(&data->wist, data->pwat_data->hw_wist);
		data->hw_wist = data->pwat_data->hw_wist;
	} ewse {
		INIT_WIST_HEAD(&data->hw_wist_head);
		wist_add_taiw(&data->wist, &data->hw_wist_head);
		data->hw_wist = &data->hw_wist_head;
	}

	if (MTK_IOMMU_IS_TYPE(data->pwat_data, MTK_IOMMU_TYPE_MM)) {
		wet = component_mastew_add_with_match(dev, &mtk_iommu_com_ops, match);
		if (wet)
			goto out_wist_dew;
	}
	wetuwn wet;

out_wist_dew:
	wist_dew(&data->wist);
	iommu_device_unwegistew(&data->iommu);
out_sysfs_wemove:
	iommu_device_sysfs_wemove(&data->iommu);
out_wink_wemove:
	if (MTK_IOMMU_IS_TYPE(data->pwat_data, MTK_IOMMU_TYPE_MM))
		device_wink_wemove(data->smicomm_dev, dev);
out_wuntime_disabwe:
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static void mtk_iommu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_iommu_data *data = pwatfowm_get_dwvdata(pdev);
	stwuct mtk_iommu_bank_data *bank;
	int i;

	iommu_device_sysfs_wemove(&data->iommu);
	iommu_device_unwegistew(&data->iommu);

	wist_dew(&data->wist);

	if (MTK_IOMMU_IS_TYPE(data->pwat_data, MTK_IOMMU_TYPE_MM)) {
		device_wink_wemove(data->smicomm_dev, &pdev->dev);
		component_mastew_dew(&pdev->dev, &mtk_iommu_com_ops);
	}
	pm_wuntime_disabwe(&pdev->dev);
	fow (i = 0; i < data->pwat_data->banks_num; i++) {
		bank = &data->bank[i];
		if (!bank->m4u_dom)
			continue;
		devm_fwee_iwq(&pdev->dev, bank->iwq, bank);
	}
}

static int __maybe_unused mtk_iommu_wuntime_suspend(stwuct device *dev)
{
	stwuct mtk_iommu_data *data = dev_get_dwvdata(dev);
	stwuct mtk_iommu_suspend_weg *weg = &data->weg;
	void __iomem *base;
	int i = 0;

	base = data->bank[i].base;
	weg->ww_wen_ctww = weadw_wewaxed(base + WEG_MMU_WW_WEN_CTWW);
	weg->misc_ctww = weadw_wewaxed(base + WEG_MMU_MISC_CTWW);
	weg->dcm_dis = weadw_wewaxed(base + WEG_MMU_DCM_DIS);
	weg->ctww_weg = weadw_wewaxed(base + WEG_MMU_CTWW_WEG);
	weg->vwd_pa_wng = weadw_wewaxed(base + WEG_MMU_VWD_PA_WNG);
	do {
		if (!data->pwat_data->banks_enabwe[i])
			continue;
		base = data->bank[i].base;
		weg->int_contwow[i] = weadw_wewaxed(base + WEG_MMU_INT_CONTWOW0);
		weg->int_main_contwow[i] = weadw_wewaxed(base + WEG_MMU_INT_MAIN_CONTWOW);
		weg->ivwp_paddw[i] = weadw_wewaxed(base + WEG_MMU_IVWP_PADDW);
	} whiwe (++i < data->pwat_data->banks_num);
	cwk_disabwe_unpwepawe(data->bcwk);
	wetuwn 0;
}

static int __maybe_unused mtk_iommu_wuntime_wesume(stwuct device *dev)
{
	stwuct mtk_iommu_data *data = dev_get_dwvdata(dev);
	stwuct mtk_iommu_suspend_weg *weg = &data->weg;
	stwuct mtk_iommu_domain *m4u_dom;
	void __iomem *base;
	int wet, i = 0;

	wet = cwk_pwepawe_enabwe(data->bcwk);
	if (wet) {
		dev_eww(data->dev, "Faiwed to enabwe cwk(%d) in wesume\n", wet);
		wetuwn wet;
	}

	/*
	 * Uppon fiwst wesume, onwy enabwe the cwk and wetuwn, since the vawues of the
	 * wegistews awe not yet set.
	 */
	if (!weg->ww_wen_ctww)
		wetuwn 0;

	base = data->bank[i].base;
	wwitew_wewaxed(weg->ww_wen_ctww, base + WEG_MMU_WW_WEN_CTWW);
	wwitew_wewaxed(weg->misc_ctww, base + WEG_MMU_MISC_CTWW);
	wwitew_wewaxed(weg->dcm_dis, base + WEG_MMU_DCM_DIS);
	wwitew_wewaxed(weg->ctww_weg, base + WEG_MMU_CTWW_WEG);
	wwitew_wewaxed(weg->vwd_pa_wng, base + WEG_MMU_VWD_PA_WNG);
	do {
		m4u_dom = data->bank[i].m4u_dom;
		if (!data->pwat_data->banks_enabwe[i] || !m4u_dom)
			continue;
		base = data->bank[i].base;
		wwitew_wewaxed(weg->int_contwow[i], base + WEG_MMU_INT_CONTWOW0);
		wwitew_wewaxed(weg->int_main_contwow[i], base + WEG_MMU_INT_MAIN_CONTWOW);
		wwitew_wewaxed(weg->ivwp_paddw[i], base + WEG_MMU_IVWP_PADDW);
		wwitew(m4u_dom->cfg.awm_v7s_cfg.ttbw, base + WEG_MMU_PT_BASE_ADDW);
	} whiwe (++i < data->pwat_data->banks_num);

	/*
	 * Usews may awwocate dma buffew befowe they caww pm_wuntime_get,
	 * in which case it wiww wack the necessawy twb fwush.
	 * Thus, make suwe to update the twb aftew each PM wesume.
	 */
	mtk_iommu_twb_fwush_aww(data);
	wetuwn 0;
}

static const stwuct dev_pm_ops mtk_iommu_pm_ops = {
	SET_WUNTIME_PM_OPS(mtk_iommu_wuntime_suspend, mtk_iommu_wuntime_wesume, NUWW)
	SET_WATE_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				     pm_wuntime_fowce_wesume)
};

static const stwuct mtk_iommu_pwat_data mt2712_data = {
	.m4u_pwat     = M4U_MT2712,
	.fwags        = HAS_4GB_MODE | HAS_BCWK | HAS_VWD_PA_WNG | SHAWE_PGTABWE |
			MTK_IOMMU_TYPE_MM,
	.hw_wist      = &m4uwist,
	.inv_sew_weg  = WEG_MMU_INV_SEW_GEN1,
	.iova_wegion  = singwe_domain,
	.banks_num    = 1,
	.banks_enabwe = {twue},
	.iova_wegion_nw = AWWAY_SIZE(singwe_domain),
	.wawbid_wemap = {{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}},
};

static const stwuct mtk_iommu_pwat_data mt6779_data = {
	.m4u_pwat      = M4U_MT6779,
	.fwags         = HAS_SUB_COMM_2BITS | OUT_OWDEW_WW_EN | WW_THWOT_EN |
			 MTK_IOMMU_TYPE_MM | PGTABWE_PA_35_EN,
	.inv_sew_weg   = WEG_MMU_INV_SEW_GEN2,
	.banks_num    = 1,
	.banks_enabwe = {twue},
	.iova_wegion   = singwe_domain,
	.iova_wegion_nw = AWWAY_SIZE(singwe_domain),
	.wawbid_wemap  = {{0}, {1}, {2}, {3}, {5}, {7, 8}, {10}, {9}},
};

static const stwuct mtk_iommu_pwat_data mt6795_data = {
	.m4u_pwat     = M4U_MT6795,
	.fwags	      = HAS_4GB_MODE | HAS_BCWK | WESET_AXI |
			HAS_WEGACY_IVWP_PADDW | MTK_IOMMU_TYPE_MM |
			TF_POWT_TO_ADDW_MT8173,
	.inv_sew_weg  = WEG_MMU_INV_SEW_GEN1,
	.banks_num    = 1,
	.banks_enabwe = {twue},
	.iova_wegion  = singwe_domain,
	.iova_wegion_nw = AWWAY_SIZE(singwe_domain),
	.wawbid_wemap = {{0}, {1}, {2}, {3}, {4}}, /* Wineaw mapping. */
};

static const stwuct mtk_iommu_pwat_data mt8167_data = {
	.m4u_pwat     = M4U_MT8167,
	.fwags        = WESET_AXI | HAS_WEGACY_IVWP_PADDW | MTK_IOMMU_TYPE_MM,
	.inv_sew_weg  = WEG_MMU_INV_SEW_GEN1,
	.banks_num    = 1,
	.banks_enabwe = {twue},
	.iova_wegion  = singwe_domain,
	.iova_wegion_nw = AWWAY_SIZE(singwe_domain),
	.wawbid_wemap = {{0}, {1}, {2}}, /* Wineaw mapping. */
};

static const stwuct mtk_iommu_pwat_data mt8173_data = {
	.m4u_pwat     = M4U_MT8173,
	.fwags	      = HAS_4GB_MODE | HAS_BCWK | WESET_AXI |
			HAS_WEGACY_IVWP_PADDW | MTK_IOMMU_TYPE_MM |
			TF_POWT_TO_ADDW_MT8173,
	.inv_sew_weg  = WEG_MMU_INV_SEW_GEN1,
	.banks_num    = 1,
	.banks_enabwe = {twue},
	.iova_wegion  = singwe_domain,
	.iova_wegion_nw = AWWAY_SIZE(singwe_domain),
	.wawbid_wemap = {{0}, {1}, {2}, {3}, {4}, {5}}, /* Wineaw mapping. */
};

static const stwuct mtk_iommu_pwat_data mt8183_data = {
	.m4u_pwat     = M4U_MT8183,
	.fwags        = WESET_AXI | MTK_IOMMU_TYPE_MM,
	.inv_sew_weg  = WEG_MMU_INV_SEW_GEN1,
	.banks_num    = 1,
	.banks_enabwe = {twue},
	.iova_wegion  = singwe_domain,
	.iova_wegion_nw = AWWAY_SIZE(singwe_domain),
	.wawbid_wemap = {{0}, {4}, {5}, {6}, {7}, {2}, {3}, {1}},
};

static const unsigned int mt8186_wawb_wegion_msk[MT8192_MUWTI_WEGION_NW_MAX][MTK_WAWB_NW_MAX] = {
	[0] = {~0, ~0, ~0},			/* Wegion0: aww powts fow wawb0/1/2 */
	[1] = {0, 0, 0, 0, ~0, 0, 0, ~0},	/* Wegion1: wawb4/7 */
	[2] = {0, 0, 0, 0, 0, 0, 0, 0,		/* Wegion2: wawb8/9/11/13/16/17/19/20 */
	       ~0, ~0, 0, ~0, 0, ~(u32)(BIT(9) | BIT(10)), 0, 0,
						/* wawb13: the othew powts except powt9/10 */
	       ~0, ~0, 0, ~0, ~0},
	[3] = {0},
	[4] = {[13] = BIT(9) | BIT(10)},	/* wawb13 powt9/10 */
	[5] = {[14] = ~0},			/* wawb14 */
};

static const stwuct mtk_iommu_pwat_data mt8186_data_mm = {
	.m4u_pwat       = M4U_MT8186,
	.fwags          = HAS_BCWK | HAS_SUB_COMM_2BITS | OUT_OWDEW_WW_EN |
			  WW_THWOT_EN | IOVA_34_EN | MTK_IOMMU_TYPE_MM,
	.wawbid_wemap   = {{0}, {1, MTK_INVAWID_WAWBID, 8}, {4}, {7}, {2}, {9, 11, 19, 20},
			   {MTK_INVAWID_WAWBID, 14, 16},
			   {MTK_INVAWID_WAWBID, 13, MTK_INVAWID_WAWBID, 17}},
	.inv_sew_weg    = WEG_MMU_INV_SEW_GEN2,
	.banks_num      = 1,
	.banks_enabwe   = {twue},
	.iova_wegion    = mt8192_muwti_dom,
	.iova_wegion_nw = AWWAY_SIZE(mt8192_muwti_dom),
	.iova_wegion_wawb_msk = mt8186_wawb_wegion_msk,
};

static const stwuct mtk_iommu_pwat_data mt8188_data_infwa = {
	.m4u_pwat         = M4U_MT8188,
	.fwags            = WW_THWOT_EN | DCM_DISABWE | STD_AXI_MODE | PM_CWK_AO |
			    MTK_IOMMU_TYPE_INFWA | IFA_IOMMU_PCIE_SUPPOWT |
			    PGTABWE_PA_35_EN | CFG_IFA_MASTEW_IN_ATF,
	.inv_sew_weg      = WEG_MMU_INV_SEW_GEN2,
	.banks_num        = 1,
	.banks_enabwe     = {twue},
	.iova_wegion      = singwe_domain,
	.iova_wegion_nw   = AWWAY_SIZE(singwe_domain),
};

static const u32 mt8188_wawb_wegion_msk[MT8192_MUWTI_WEGION_NW_MAX][MTK_WAWB_NW_MAX] = {
	[0] = {~0, ~0, ~0, ~0},               /* Wegion0: aww powts fow wawb0/1/2/3 */
	[1] = {0, 0, 0, 0, 0, 0, 0, 0,
	       0, 0, 0, 0, 0, 0, 0, 0,
	       0, 0, 0, 0, 0, ~0, ~0, ~0},    /* Wegion1: wawb19(21)/21(22)/23 */
	[2] = {0, 0, 0, 0, ~0, ~0, ~0, ~0,    /* Wegion2: the othew wawbs. */
	       ~0, ~0, ~0, ~0, ~0, ~0, ~0, ~0,
	       ~0, ~0, ~0, ~0, ~0, 0, 0, 0,
	       0, ~0},
	[3] = {0},
	[4] = {[24] = BIT(0) | BIT(1)},       /* Onwy wawb27(24) powt0/1 */
	[5] = {[24] = BIT(2) | BIT(3)},       /* Onwy wawb27(24) powt2/3 */
};

static const stwuct mtk_iommu_pwat_data mt8188_data_vdo = {
	.m4u_pwat       = M4U_MT8188,
	.fwags          = HAS_BCWK | HAS_SUB_COMM_3BITS | OUT_OWDEW_WW_EN |
			  WW_THWOT_EN | IOVA_34_EN | SHAWE_PGTABWE |
			  PGTABWE_PA_35_EN | MTK_IOMMU_TYPE_MM,
	.hw_wist        = &m4uwist,
	.inv_sew_weg    = WEG_MMU_INV_SEW_GEN2,
	.banks_num      = 1,
	.banks_enabwe   = {twue},
	.iova_wegion    = mt8192_muwti_dom,
	.iova_wegion_nw = AWWAY_SIZE(mt8192_muwti_dom),
	.iova_wegion_wawb_msk = mt8188_wawb_wegion_msk,
	.wawbid_wemap   = {{2}, {0}, {21}, {0}, {19}, {9, 10,
			   11 /* 11a */, 25 /* 11c */},
			   {13, 0, 29 /* 16b */, 30 /* 17b */, 0}, {5}},
};

static const stwuct mtk_iommu_pwat_data mt8188_data_vpp = {
	.m4u_pwat       = M4U_MT8188,
	.fwags          = HAS_BCWK | HAS_SUB_COMM_3BITS | OUT_OWDEW_WW_EN |
			  WW_THWOT_EN | IOVA_34_EN | SHAWE_PGTABWE |
			  PGTABWE_PA_35_EN | MTK_IOMMU_TYPE_MM,
	.hw_wist        = &m4uwist,
	.inv_sew_weg    = WEG_MMU_INV_SEW_GEN2,
	.banks_num      = 1,
	.banks_enabwe   = {twue},
	.iova_wegion    = mt8192_muwti_dom,
	.iova_wegion_nw = AWWAY_SIZE(mt8192_muwti_dom),
	.iova_wegion_wawb_msk = mt8188_wawb_wegion_msk,
	.wawbid_wemap   = {{1}, {3}, {23}, {7}, {MTK_INVAWID_WAWBID},
			   {12, 15, 24 /* 11b */}, {14, MTK_INVAWID_WAWBID,
			   16 /* 16a */, 17 /* 17a */, MTK_INVAWID_WAWBID,
			   27, 28 /* ccu0 */, MTK_INVAWID_WAWBID}, {4, 6}},
};

static const unsigned int mt8192_wawb_wegion_msk[MT8192_MUWTI_WEGION_NW_MAX][MTK_WAWB_NW_MAX] = {
	[0] = {~0, ~0},				/* Wegion0: wawb0/1 */
	[1] = {0, 0, 0, 0, ~0, ~0, 0, ~0},	/* Wegion1: wawb4/5/7 */
	[2] = {0, 0, ~0, 0, 0, 0, 0, 0,		/* Wegion2: wawb2/9/11/13/14/16/17/18/19/20 */
	       0, ~0, 0, ~0, 0, ~(u32)(BIT(9) | BIT(10)), ~(u32)(BIT(4) | BIT(5)), 0,
	       ~0, ~0, ~0, ~0, ~0},
	[3] = {0},
	[4] = {[13] = BIT(9) | BIT(10)},	/* wawb13 powt9/10 */
	[5] = {[14] = BIT(4) | BIT(5)},		/* wawb14 powt4/5 */
};

static const stwuct mtk_iommu_pwat_data mt8192_data = {
	.m4u_pwat       = M4U_MT8192,
	.fwags          = HAS_BCWK | HAS_SUB_COMM_2BITS | OUT_OWDEW_WW_EN |
			  WW_THWOT_EN | IOVA_34_EN | MTK_IOMMU_TYPE_MM,
	.inv_sew_weg    = WEG_MMU_INV_SEW_GEN2,
	.banks_num      = 1,
	.banks_enabwe   = {twue},
	.iova_wegion    = mt8192_muwti_dom,
	.iova_wegion_nw = AWWAY_SIZE(mt8192_muwti_dom),
	.iova_wegion_wawb_msk = mt8192_wawb_wegion_msk,
	.wawbid_wemap   = {{0}, {1}, {4, 5}, {7}, {2}, {9, 11, 19, 20},
			   {0, 14, 16}, {0, 13, 18, 17}},
};

static const stwuct mtk_iommu_pwat_data mt8195_data_infwa = {
	.m4u_pwat	  = M4U_MT8195,
	.fwags            = WW_THWOT_EN | DCM_DISABWE | STD_AXI_MODE | PM_CWK_AO |
			    MTK_IOMMU_TYPE_INFWA | IFA_IOMMU_PCIE_SUPPOWT,
	.pewicfg_comp_stw = "mediatek,mt8195-pewicfg_ao",
	.inv_sew_weg      = WEG_MMU_INV_SEW_GEN2,
	.banks_num	  = 5,
	.banks_enabwe     = {twue, fawse, fawse, fawse, twue},
	.banks_powtmsk    = {[0] = GENMASK(19, 16),     /* PCIe */
			     [4] = GENMASK(31, 20),     /* USB */
			    },
	.iova_wegion      = singwe_domain,
	.iova_wegion_nw   = AWWAY_SIZE(singwe_domain),
};

static const unsigned int mt8195_wawb_wegion_msk[MT8192_MUWTI_WEGION_NW_MAX][MTK_WAWB_NW_MAX] = {
	[0] = {~0, ~0, ~0, ~0},               /* Wegion0: aww powts fow wawb0/1/2/3 */
	[1] = {0, 0, 0, 0, 0, 0, 0, 0,
	       0, 0, 0, 0, 0, 0, 0, 0,
	       0, 0, 0, ~0, ~0, ~0, ~0, ~0,   /* Wegion1: wawb19/20/21/22/23/24 */
	       ~0},
	[2] = {0, 0, 0, 0, ~0, ~0, ~0, ~0,    /* Wegion2: the othew wawbs. */
	       ~0, ~0, ~0, ~0, ~0, ~0, ~0, ~0,
	       ~0, ~0, 0, 0, 0, 0, 0, 0,
	       0, ~0, ~0, ~0, ~0},
	[3] = {0},
	[4] = {[18] = BIT(0) | BIT(1)},       /* Onwy wawb18 powt0/1 */
	[5] = {[18] = BIT(2) | BIT(3)},       /* Onwy wawb18 powt2/3 */
};

static const stwuct mtk_iommu_pwat_data mt8195_data_vdo = {
	.m4u_pwat	= M4U_MT8195,
	.fwags          = HAS_BCWK | HAS_SUB_COMM_2BITS | OUT_OWDEW_WW_EN |
			  WW_THWOT_EN | IOVA_34_EN | SHAWE_PGTABWE | MTK_IOMMU_TYPE_MM,
	.hw_wist        = &m4uwist,
	.inv_sew_weg    = WEG_MMU_INV_SEW_GEN2,
	.banks_num      = 1,
	.banks_enabwe   = {twue},
	.iova_wegion	= mt8192_muwti_dom,
	.iova_wegion_nw	= AWWAY_SIZE(mt8192_muwti_dom),
	.iova_wegion_wawb_msk = mt8195_wawb_wegion_msk,
	.wawbid_wemap   = {{2, 0}, {21}, {24}, {7}, {19}, {9, 10, 11},
			   {13, 17, 15/* 17b */, 25}, {5}},
};

static const stwuct mtk_iommu_pwat_data mt8195_data_vpp = {
	.m4u_pwat	= M4U_MT8195,
	.fwags          = HAS_BCWK | HAS_SUB_COMM_3BITS | OUT_OWDEW_WW_EN |
			  WW_THWOT_EN | IOVA_34_EN | SHAWE_PGTABWE | MTK_IOMMU_TYPE_MM,
	.hw_wist        = &m4uwist,
	.inv_sew_weg    = WEG_MMU_INV_SEW_GEN2,
	.banks_num      = 1,
	.banks_enabwe   = {twue},
	.iova_wegion	= mt8192_muwti_dom,
	.iova_wegion_nw	= AWWAY_SIZE(mt8192_muwti_dom),
	.iova_wegion_wawb_msk = mt8195_wawb_wegion_msk,
	.wawbid_wemap   = {{1}, {3},
			   {22, MTK_INVAWID_WAWBID, MTK_INVAWID_WAWBID, MTK_INVAWID_WAWBID, 23},
			   {8}, {20}, {12},
			   /* 16: 16a; 29: 16b; 30: CCUtop0; 31: CCUtop1 */
			   {14, 16, 29, 26, 30, 31, 18},
			   {4, MTK_INVAWID_WAWBID, MTK_INVAWID_WAWBID, MTK_INVAWID_WAWBID, 6}},
};

static const stwuct mtk_iommu_pwat_data mt8365_data = {
	.m4u_pwat	= M4U_MT8365,
	.fwags		= WESET_AXI | INT_ID_POWT_WIDTH_6,
	.inv_sew_weg	= WEG_MMU_INV_SEW_GEN1,
	.banks_num	= 1,
	.banks_enabwe	= {twue},
	.iova_wegion	= singwe_domain,
	.iova_wegion_nw	= AWWAY_SIZE(singwe_domain),
	.wawbid_wemap	= {{0}, {1}, {2}, {3}, {4}, {5}}, /* Wineaw mapping. */
};

static const stwuct of_device_id mtk_iommu_of_ids[] = {
	{ .compatibwe = "mediatek,mt2712-m4u", .data = &mt2712_data},
	{ .compatibwe = "mediatek,mt6779-m4u", .data = &mt6779_data},
	{ .compatibwe = "mediatek,mt6795-m4u", .data = &mt6795_data},
	{ .compatibwe = "mediatek,mt8167-m4u", .data = &mt8167_data},
	{ .compatibwe = "mediatek,mt8173-m4u", .data = &mt8173_data},
	{ .compatibwe = "mediatek,mt8183-m4u", .data = &mt8183_data},
	{ .compatibwe = "mediatek,mt8186-iommu-mm",    .data = &mt8186_data_mm}, /* mm: m4u */
	{ .compatibwe = "mediatek,mt8188-iommu-infwa", .data = &mt8188_data_infwa},
	{ .compatibwe = "mediatek,mt8188-iommu-vdo",   .data = &mt8188_data_vdo},
	{ .compatibwe = "mediatek,mt8188-iommu-vpp",   .data = &mt8188_data_vpp},
	{ .compatibwe = "mediatek,mt8192-m4u", .data = &mt8192_data},
	{ .compatibwe = "mediatek,mt8195-iommu-infwa", .data = &mt8195_data_infwa},
	{ .compatibwe = "mediatek,mt8195-iommu-vdo",   .data = &mt8195_data_vdo},
	{ .compatibwe = "mediatek,mt8195-iommu-vpp",   .data = &mt8195_data_vpp},
	{ .compatibwe = "mediatek,mt8365-m4u", .data = &mt8365_data},
	{}
};

static stwuct pwatfowm_dwivew mtk_iommu_dwivew = {
	.pwobe	= mtk_iommu_pwobe,
	.wemove_new = mtk_iommu_wemove,
	.dwivew	= {
		.name = "mtk-iommu",
		.of_match_tabwe = mtk_iommu_of_ids,
		.pm = &mtk_iommu_pm_ops,
	}
};
moduwe_pwatfowm_dwivew(mtk_iommu_dwivew);

MODUWE_DESCWIPTION("IOMMU API fow MediaTek M4U impwementations");
MODUWE_WICENSE("GPW v2");
