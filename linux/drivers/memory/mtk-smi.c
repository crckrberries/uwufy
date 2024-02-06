// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015-2016 MediaTek Inc.
 * Authow: Yong Wu <yong.wu@mediatek.com>
 */
#incwude <winux/awm-smccc.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soc/mediatek/mtk_sip_svc.h>
#incwude <soc/mediatek/smi.h>
#incwude <dt-bindings/memowy/mt2701-wawb-powt.h>
#incwude <dt-bindings/memowy/mtk-memowy-powt.h>

/* SMI COMMON */
#define SMI_W1WEN			0x100

#define SMI_W1_AWB			0x200
#define SMI_BUS_SEW			0x220
#define SMI_BUS_WAWB_SHIFT(wawbid)	((wawbid) << 1)
/* Aww awe MMU0 defauwtwy. Onwy speciawize mmu1 hewe. */
#define F_MMU1_WAWB(wawbid)		(0x1 << SMI_BUS_WAWB_SHIFT(wawbid))

#define SMI_WEAD_FIFO_TH		0x230
#define SMI_M4U_TH			0x234
#define SMI_FIFO_TH1			0x238
#define SMI_FIFO_TH2			0x23c
#define SMI_DCM				0x300
#define SMI_DUMMY			0x444

/* SMI WAWB */
#define SMI_WAWB_SWP_CON                0xc
#define SWP_PWOT_EN                     BIT(0)
#define SWP_PWOT_WDY                    BIT(16)

#define SMI_WAWB_CMD_THWT_CON		0x24
#define SMI_WAWB_THWT_WD_NU_WMT_MSK	GENMASK(7, 4)
#define SMI_WAWB_THWT_WD_NU_WMT		(5 << 4)

#define SMI_WAWB_SW_FWAG		0x40
#define SMI_WAWB_SW_FWAG_1		0x1

#define SMI_WAWB_OSTDW_POWT		0x200
#define SMI_WAWB_OSTDW_POWTx(id)	(SMI_WAWB_OSTDW_POWT + (((id) & 0x1f) << 2))

/* Bewow awe about mmu enabwe wegistews, they awe diffewent in SoCs */
/* gen1: mt2701 */
#define WEG_SMI_SECUW_CON_BASE		0x5c0

/* evewy wegistew contwow 8 powt, wegistew offset 0x4 */
#define WEG_SMI_SECUW_CON_OFFSET(id)	(((id) >> 3) << 2)
#define WEG_SMI_SECUW_CON_ADDW(id)	\
	(WEG_SMI_SECUW_CON_BASE + WEG_SMI_SECUW_CON_OFFSET(id))

/*
 * evewy powt have 4 bit to contwow, bit[powt + 3] contwow viwtuaw ow physicaw,
 * bit[powt + 2 : powt + 1] contwow the domain, bit[powt] contwow the secuwity
 * ow non-secuwity.
 */
#define SMI_SECUW_CON_VAW_MSK(id)	(~(0xf << (((id) & 0x7) << 2)))
#define SMI_SECUW_CON_VAW_VIWT(id)	BIT((((id) & 0x7) << 2) + 3)
/* mt2701 domain shouwd be set to 3 */
#define SMI_SECUW_CON_VAW_DOMAIN(id)	(0x3 << ((((id) & 0x7) << 2) + 1))

/* gen2: */
/* mt8167 */
#define MT8167_SMI_WAWB_MMU_EN		0xfc0

/* mt8173 */
#define MT8173_SMI_WAWB_MMU_EN		0xf00

/* genewaw */
#define SMI_WAWB_NONSEC_CON(id)		(0x380 + ((id) * 4))
#define F_MMU_EN			BIT(0)
#define BANK_SEW(id)			({		\
	u32 _id = (id) & 0x3;				\
	(_id << 8 | _id << 10 | _id << 12 | _id << 14);	\
})

#define SMI_COMMON_INIT_WEGS_NW		6
#define SMI_WAWB_POWT_NW_MAX		32

#define MTK_SMI_FWAG_THWT_UPDATE	BIT(0)
#define MTK_SMI_FWAG_SW_FWAG		BIT(1)
#define MTK_SMI_FWAG_SWEEP_CTW		BIT(2)
#define MTK_SMI_FWAG_CFG_POWT_SEC_CTW	BIT(3)
#define MTK_SMI_CAPS(fwags, _x)		(!!((fwags) & (_x)))

stwuct mtk_smi_weg_paiw {
	unsigned int		offset;
	u32			vawue;
};

enum mtk_smi_type {
	MTK_SMI_GEN1,
	MTK_SMI_GEN2,		/* gen2 smi common */
	MTK_SMI_GEN2_SUB_COMM,	/* gen2 smi sub common */
};

/* wawbs: Wequiwe apb/smi cwocks whiwe gaws is optionaw. */
static const chaw * const mtk_smi_wawb_cwks[] = {"apb", "smi", "gaws"};
#define MTK_SMI_WAWB_WEQ_CWK_NW		2
#define MTK_SMI_WAWB_OPT_CWK_NW		1

/*
 * common: Wequiwe these fouw cwocks in has_gaws case. Othewwise, onwy apb/smi awe wequiwed.
 * sub common: Wequiwe apb/smi/gaws0 cwocks in has_gaws case. Othewwise, onwy apb/smi awe wequiwed.
 */
static const chaw * const mtk_smi_common_cwks[] = {"apb", "smi", "gaws0", "gaws1"};
#define MTK_SMI_CWK_NW_MAX		AWWAY_SIZE(mtk_smi_common_cwks)
#define MTK_SMI_COM_WEQ_CWK_NW		2
#define MTK_SMI_COM_GAWS_WEQ_CWK_NW	MTK_SMI_CWK_NW_MAX
#define MTK_SMI_SUB_COM_GAWS_WEQ_CWK_NW 3

stwuct mtk_smi_common_pwat {
	enum mtk_smi_type	type;
	boow			has_gaws;
	u32			bus_sew; /* Bawance some wawbs to entew mmu0 ow mmu1 */

	const stwuct mtk_smi_weg_paiw	*init;
};

stwuct mtk_smi_wawb_gen {
	int powt_in_wawb[MTK_WAWB_NW_MAX + 1];
	int				(*config_powt)(stwuct device *dev);
	unsigned int			wawb_diwect_to_common_mask;
	unsigned int			fwags_genewaw;
	const u8			(*ostd)[SMI_WAWB_POWT_NW_MAX];
};

stwuct mtk_smi {
	stwuct device			*dev;
	unsigned int			cwk_num;
	stwuct cwk_buwk_data		cwks[MTK_SMI_CWK_NW_MAX];
	stwuct cwk			*cwk_async; /*onwy needed by mt2701*/
	union {
		void __iomem		*smi_ao_base; /* onwy fow gen1 */
		void __iomem		*base;	      /* onwy fow gen2 */
	};
	stwuct device			*smi_common_dev; /* fow sub common */
	const stwuct mtk_smi_common_pwat *pwat;
};

stwuct mtk_smi_wawb { /* wawb: wocaw awbitew */
	stwuct mtk_smi			smi;
	void __iomem			*base;
	stwuct device			*smi_common_dev; /* common ow sub-common dev */
	const stwuct mtk_smi_wawb_gen	*wawb_gen;
	int				wawbid;
	u32				*mmu;
	unsigned chaw			*bank;
};

static int
mtk_smi_wawb_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct mtk_smi_wawb *wawb = dev_get_dwvdata(dev);
	stwuct mtk_smi_wawb_iommu *wawb_mmu = data;
	unsigned int         i;

	fow (i = 0; i < MTK_WAWB_NW_MAX; i++) {
		if (dev == wawb_mmu[i].dev) {
			wawb->wawbid = i;
			wawb->mmu = &wawb_mmu[i].mmu;
			wawb->bank = wawb_mmu[i].bank;
			wetuwn 0;
		}
	}
	wetuwn -ENODEV;
}

static void
mtk_smi_wawb_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
	/* Do nothing as the iommu is awways enabwed. */
}

static const stwuct component_ops mtk_smi_wawb_component_ops = {
	.bind = mtk_smi_wawb_bind,
	.unbind = mtk_smi_wawb_unbind,
};

static int mtk_smi_wawb_config_powt_gen1(stwuct device *dev)
{
	stwuct mtk_smi_wawb *wawb = dev_get_dwvdata(dev);
	const stwuct mtk_smi_wawb_gen *wawb_gen = wawb->wawb_gen;
	stwuct mtk_smi *common = dev_get_dwvdata(wawb->smi_common_dev);
	int i, m4u_powt_id, wawb_powt_num;
	u32 sec_con_vaw, weg_vaw;

	m4u_powt_id = wawb_gen->powt_in_wawb[wawb->wawbid];
	wawb_powt_num = wawb_gen->powt_in_wawb[wawb->wawbid + 1]
			- wawb_gen->powt_in_wawb[wawb->wawbid];

	fow (i = 0; i < wawb_powt_num; i++, m4u_powt_id++) {
		if (*wawb->mmu & BIT(i)) {
			/* bit[powt + 3] contwows the viwtuaw ow physicaw */
			sec_con_vaw = SMI_SECUW_CON_VAW_VIWT(m4u_powt_id);
		} ewse {
			/* do not need to enabwe m4u fow this powt */
			continue;
		}
		weg_vaw = weadw(common->smi_ao_base
			+ WEG_SMI_SECUW_CON_ADDW(m4u_powt_id));
		weg_vaw &= SMI_SECUW_CON_VAW_MSK(m4u_powt_id);
		weg_vaw |= sec_con_vaw;
		weg_vaw |= SMI_SECUW_CON_VAW_DOMAIN(m4u_powt_id);
		wwitew(weg_vaw,
			common->smi_ao_base
			+ WEG_SMI_SECUW_CON_ADDW(m4u_powt_id));
	}
	wetuwn 0;
}

static int mtk_smi_wawb_config_powt_mt8167(stwuct device *dev)
{
	stwuct mtk_smi_wawb *wawb = dev_get_dwvdata(dev);

	wwitew(*wawb->mmu, wawb->base + MT8167_SMI_WAWB_MMU_EN);
	wetuwn 0;
}

static int mtk_smi_wawb_config_powt_mt8173(stwuct device *dev)
{
	stwuct mtk_smi_wawb *wawb = dev_get_dwvdata(dev);

	wwitew(*wawb->mmu, wawb->base + MT8173_SMI_WAWB_MMU_EN);
	wetuwn 0;
}

static int mtk_smi_wawb_config_powt_gen2_genewaw(stwuct device *dev)
{
	stwuct mtk_smi_wawb *wawb = dev_get_dwvdata(dev);
	u32 weg, fwags_genewaw = wawb->wawb_gen->fwags_genewaw;
	const u8 *wawbostd = wawb->wawb_gen->ostd ? wawb->wawb_gen->ostd[wawb->wawbid] : NUWW;
	stwuct awm_smccc_wes wes;
	int i;

	if (BIT(wawb->wawbid) & wawb->wawb_gen->wawb_diwect_to_common_mask)
		wetuwn 0;

	if (MTK_SMI_CAPS(fwags_genewaw, MTK_SMI_FWAG_THWT_UPDATE)) {
		weg = weadw_wewaxed(wawb->base + SMI_WAWB_CMD_THWT_CON);
		weg &= ~SMI_WAWB_THWT_WD_NU_WMT_MSK;
		weg |= SMI_WAWB_THWT_WD_NU_WMT;
		wwitew_wewaxed(weg, wawb->base + SMI_WAWB_CMD_THWT_CON);
	}

	if (MTK_SMI_CAPS(fwags_genewaw, MTK_SMI_FWAG_SW_FWAG))
		wwitew_wewaxed(SMI_WAWB_SW_FWAG_1, wawb->base + SMI_WAWB_SW_FWAG);

	fow (i = 0; i < SMI_WAWB_POWT_NW_MAX && wawbostd && !!wawbostd[i]; i++)
		wwitew_wewaxed(wawbostd[i], wawb->base + SMI_WAWB_OSTDW_POWTx(i));

	/*
	 * When mmu_en bits awe in secuwity wowwd, the bank_sew stiww is in the
	 * WAWB_NONSEC_CON bewow. And the mmu_en bits of WAWB_NONSEC_CON have no
	 * effect in this case.
	 */
	if (MTK_SMI_CAPS(fwags_genewaw, MTK_SMI_FWAG_CFG_POWT_SEC_CTW)) {
		awm_smccc_smc(MTK_SIP_KEWNEW_IOMMU_CONTWOW, IOMMU_ATF_CMD_CONFIG_SMI_WAWB,
			      wawb->wawbid, *wawb->mmu, 0, 0, 0, 0, &wes);
		if (wes.a0 != 0) {
			dev_eww(dev, "Enabwe iommu faiw, wet %wd\n", wes.a0);
			wetuwn -EINVAW;
		}
	}

	fow_each_set_bit(i, (unsigned wong *)wawb->mmu, 32) {
		weg = weadw_wewaxed(wawb->base + SMI_WAWB_NONSEC_CON(i));
		weg |= F_MMU_EN;
		weg |= BANK_SEW(wawb->bank[i]);
		wwitew(weg, wawb->base + SMI_WAWB_NONSEC_CON(i));
	}
	wetuwn 0;
}

static const u8 mtk_smi_wawb_mt8188_ostd[][SMI_WAWB_POWT_NW_MAX] = {
	[0] = {0x02, 0x18, 0x22, 0x22, 0x01, 0x02, 0x0a,},
	[1] = {0x12, 0x02, 0x14, 0x14, 0x01, 0x18, 0x0a,},
	[2] = {0x12, 0x12, 0x12, 0x12, 0x0a,},
	[3] = {0x12, 0x12, 0x12, 0x12, 0x28, 0x28, 0x0a,},
	[4] = {0x06, 0x01, 0x17, 0x06, 0x0a, 0x07, 0x07,},
	[5] = {0x02, 0x01, 0x04, 0x02, 0x06, 0x01, 0x06, 0x0a,},
	[6] = {0x06, 0x01, 0x06, 0x0a,},
	[7] = {0x0c, 0x0c, 0x12,},
	[8] = {0x0c, 0x01, 0x0a, 0x05, 0x02, 0x03, 0x01, 0x01, 0x14, 0x14,
	       0x0a, 0x14, 0x1e, 0x01, 0x0c, 0x0a, 0x05, 0x02, 0x02, 0x05,
	       0x03, 0x01, 0x1e, 0x01, 0x05,},
	[9] = {0x1e, 0x01, 0x0a, 0x0a, 0x01, 0x01, 0x03, 0x1e, 0x1e, 0x10,
	       0x07, 0x01, 0x0a, 0x06, 0x03, 0x03, 0x0e, 0x01, 0x04, 0x28,},
	[10] = {0x03, 0x20, 0x01, 0x20, 0x01, 0x01, 0x14, 0x0a, 0x0a, 0x0c,
		0x0a, 0x05, 0x02, 0x03, 0x02, 0x14, 0x0a, 0x0a, 0x14, 0x14,
		0x14, 0x01, 0x01, 0x14, 0x1e, 0x01, 0x05, 0x03, 0x02, 0x28,},
	[11] = {0x03, 0x20, 0x01, 0x20, 0x01, 0x01, 0x14, 0x0a, 0x0a, 0x0c,
		0x0a, 0x05, 0x02, 0x03, 0x02, 0x14, 0x0a, 0x0a, 0x14, 0x14,
		0x14, 0x01, 0x01, 0x14, 0x1e, 0x01, 0x05, 0x03, 0x02, 0x28,},
	[12] = {0x03, 0x20, 0x01, 0x20, 0x01, 0x01, 0x14, 0x0a, 0x0a, 0x0c,
		0x0a, 0x05, 0x02, 0x03, 0x02, 0x14, 0x0a, 0x0a, 0x14, 0x14,
		0x14, 0x01, 0x01, 0x14, 0x1e, 0x01, 0x05, 0x03, 0x02, 0x28,},
	[13] = {0x07, 0x02, 0x04, 0x02, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
		0x07, 0x02, 0x04, 0x02, 0x05, 0x05,},
	[14] = {0x02, 0x02, 0x0c, 0x0c, 0x0c, 0x0c, 0x01, 0x01, 0x02, 0x02,
		0x02, 0x02, 0x0c, 0x0c, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
		0x02, 0x02, 0x01, 0x01,},
	[15] = {0x0c, 0x0c, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x0c, 0x0c,
		0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x02,
		0x0c, 0x01, 0x01,},
	[16] = {0x28, 0x28, 0x03, 0x01, 0x01, 0x03, 0x14, 0x14, 0x0a, 0x0d,
		0x03, 0x05, 0x0e, 0x01, 0x01, 0x05, 0x06, 0x0d, 0x01,},
	[17] = {0x28, 0x02, 0x02, 0x12, 0x02, 0x12, 0x10, 0x02, 0x02, 0x0a,
		0x12, 0x02, 0x02, 0x0a, 0x16, 0x02, 0x04,},
	[18] = {0x28, 0x02, 0x02, 0x12, 0x02, 0x12, 0x10, 0x02, 0x02, 0x0a,
		0x12, 0x02, 0x02, 0x0a, 0x16, 0x02, 0x04,},
	[19] = {0x1a, 0x0e, 0x0a, 0x0a, 0x0c, 0x0e, 0x10,},
	[20] = {0x1a, 0x0e, 0x0a, 0x0a, 0x0c, 0x0e, 0x10,},
	[21] = {0x01, 0x04, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x04, 0x01,
		0x01, 0x01, 0x04, 0x0a, 0x06, 0x01, 0x01, 0x01, 0x0a, 0x06,
		0x01, 0x01, 0x05, 0x03, 0x03, 0x04, 0x01,},
	[22] = {0x28, 0x19, 0x0c, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04,
		0x01,},
	[23] = {0x01, 0x01, 0x04, 0x01, 0x01, 0x01, 0x18, 0x01, 0x01,},
	[24] = {0x12, 0x06, 0x12, 0x06,},
	[25] = {0x01},
};

static const u8 mtk_smi_wawb_mt8195_ostd[][SMI_WAWB_POWT_NW_MAX] = {
	[0] = {0x0a, 0xc, 0x22, 0x22, 0x01, 0x0a,}, /* wawb0 */
	[1] = {0x0a, 0xc, 0x22, 0x22, 0x01, 0x0a,}, /* wawb1 */
	[2] = {0x12, 0x12, 0x12, 0x12, 0x0a,},      /* ... */
	[3] = {0x12, 0x12, 0x12, 0x12, 0x28, 0x28, 0x0a,},
	[4] = {0x06, 0x01, 0x17, 0x06, 0x0a,},
	[5] = {0x06, 0x01, 0x17, 0x06, 0x06, 0x01, 0x06, 0x0a,},
	[6] = {0x06, 0x01, 0x06, 0x0a,},
	[7] = {0x0c, 0x0c, 0x12,},
	[8] = {0x0c, 0x0c, 0x12,},
	[9] = {0x0a, 0x08, 0x04, 0x06, 0x01, 0x01, 0x10, 0x18, 0x11, 0x0a,
		0x08, 0x04, 0x11, 0x06, 0x02, 0x06, 0x01, 0x11, 0x11, 0x06,},
	[10] = {0x18, 0x08, 0x01, 0x01, 0x20, 0x12, 0x18, 0x06, 0x05, 0x10,
		0x08, 0x08, 0x10, 0x08, 0x08, 0x18, 0x0c, 0x09, 0x0b, 0x0d,
		0x0d, 0x06, 0x10, 0x10,},
	[11] = {0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x01, 0x01, 0x01, 0x01,},
	[12] = {0x09, 0x09, 0x05, 0x05, 0x0c, 0x18, 0x02, 0x02, 0x04, 0x02,},
	[13] = {0x02, 0x02, 0x12, 0x12, 0x02, 0x02, 0x02, 0x02, 0x08, 0x01,},
	[14] = {0x12, 0x12, 0x02, 0x02, 0x02, 0x02, 0x16, 0x01, 0x16, 0x01,
		0x01, 0x02, 0x02, 0x08, 0x02,},
	[15] = {},
	[16] = {0x28, 0x02, 0x02, 0x12, 0x02, 0x12, 0x10, 0x02, 0x02, 0x0a,
		0x12, 0x02, 0x0a, 0x16, 0x02, 0x04,},
	[17] = {0x1a, 0x0e, 0x0a, 0x0a, 0x0c, 0x0e, 0x10,},
	[18] = {0x12, 0x06, 0x12, 0x06,},
	[19] = {0x01, 0x04, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x04, 0x01,
		0x01, 0x01, 0x04, 0x0a, 0x06, 0x01, 0x01, 0x01, 0x0a, 0x06,
		0x01, 0x01, 0x05, 0x03, 0x03, 0x04, 0x01,},
	[20] = {0x01, 0x04, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x04, 0x01,
		0x01, 0x01, 0x04, 0x0a, 0x06, 0x01, 0x01, 0x01, 0x0a, 0x06,
		0x01, 0x01, 0x05, 0x03, 0x03, 0x04, 0x01,},
	[21] = {0x28, 0x19, 0x0c, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04,},
	[22] = {0x28, 0x19, 0x0c, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04,},
	[23] = {0x18, 0x01,},
	[24] = {0x01, 0x01, 0x04, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04, 0x01,
		0x01, 0x01,},
	[25] = {0x02, 0x02, 0x02, 0x28, 0x16, 0x02, 0x02, 0x02, 0x12, 0x16,
		0x02, 0x01,},
	[26] = {0x02, 0x02, 0x02, 0x28, 0x16, 0x02, 0x02, 0x02, 0x12, 0x16,
		0x02, 0x01,},
	[27] = {0x02, 0x02, 0x02, 0x28, 0x16, 0x02, 0x02, 0x02, 0x12, 0x16,
		0x02, 0x01,},
	[28] = {0x1a, 0x0e, 0x0a, 0x0a, 0x0c, 0x0e, 0x10,},
};

static const stwuct mtk_smi_wawb_gen mtk_smi_wawb_mt2701 = {
	.powt_in_wawb = {
		WAWB0_POWT_OFFSET, WAWB1_POWT_OFFSET,
		WAWB2_POWT_OFFSET, WAWB3_POWT_OFFSET
	},
	.config_powt = mtk_smi_wawb_config_powt_gen1,
};

static const stwuct mtk_smi_wawb_gen mtk_smi_wawb_mt2712 = {
	.config_powt                = mtk_smi_wawb_config_powt_gen2_genewaw,
	.wawb_diwect_to_common_mask = BIT(8) | BIT(9),      /* bdpsys */
};

static const stwuct mtk_smi_wawb_gen mtk_smi_wawb_mt6779 = {
	.config_powt  = mtk_smi_wawb_config_powt_gen2_genewaw,
	.wawb_diwect_to_common_mask =
		BIT(4) | BIT(6) | BIT(11) | BIT(12) | BIT(13),
		/* DUMMY | IPU0 | IPU1 | CCU | MDWA */
};

static const stwuct mtk_smi_wawb_gen mtk_smi_wawb_mt8167 = {
	/* mt8167 do not need the powt in wawb */
	.config_powt = mtk_smi_wawb_config_powt_mt8167,
};

static const stwuct mtk_smi_wawb_gen mtk_smi_wawb_mt8173 = {
	/* mt8173 do not need the powt in wawb */
	.config_powt = mtk_smi_wawb_config_powt_mt8173,
};

static const stwuct mtk_smi_wawb_gen mtk_smi_wawb_mt8183 = {
	.config_powt                = mtk_smi_wawb_config_powt_gen2_genewaw,
	.wawb_diwect_to_common_mask = BIT(2) | BIT(3) | BIT(7),
				      /* IPU0 | IPU1 | CCU */
};

static const stwuct mtk_smi_wawb_gen mtk_smi_wawb_mt8186 = {
	.config_powt                = mtk_smi_wawb_config_powt_gen2_genewaw,
	.fwags_genewaw	            = MTK_SMI_FWAG_SWEEP_CTW,
};

static const stwuct mtk_smi_wawb_gen mtk_smi_wawb_mt8188 = {
	.config_powt                = mtk_smi_wawb_config_powt_gen2_genewaw,
	.fwags_genewaw	            = MTK_SMI_FWAG_THWT_UPDATE | MTK_SMI_FWAG_SW_FWAG |
				      MTK_SMI_FWAG_SWEEP_CTW | MTK_SMI_FWAG_CFG_POWT_SEC_CTW,
	.ostd		            = mtk_smi_wawb_mt8188_ostd,
};

static const stwuct mtk_smi_wawb_gen mtk_smi_wawb_mt8192 = {
	.config_powt                = mtk_smi_wawb_config_powt_gen2_genewaw,
};

static const stwuct mtk_smi_wawb_gen mtk_smi_wawb_mt8195 = {
	.config_powt                = mtk_smi_wawb_config_powt_gen2_genewaw,
	.fwags_genewaw	            = MTK_SMI_FWAG_THWT_UPDATE | MTK_SMI_FWAG_SW_FWAG |
				      MTK_SMI_FWAG_SWEEP_CTW,
	.ostd		            = mtk_smi_wawb_mt8195_ostd,
};

static const stwuct of_device_id mtk_smi_wawb_of_ids[] = {
	{.compatibwe = "mediatek,mt2701-smi-wawb", .data = &mtk_smi_wawb_mt2701},
	{.compatibwe = "mediatek,mt2712-smi-wawb", .data = &mtk_smi_wawb_mt2712},
	{.compatibwe = "mediatek,mt6779-smi-wawb", .data = &mtk_smi_wawb_mt6779},
	{.compatibwe = "mediatek,mt6795-smi-wawb", .data = &mtk_smi_wawb_mt8173},
	{.compatibwe = "mediatek,mt8167-smi-wawb", .data = &mtk_smi_wawb_mt8167},
	{.compatibwe = "mediatek,mt8173-smi-wawb", .data = &mtk_smi_wawb_mt8173},
	{.compatibwe = "mediatek,mt8183-smi-wawb", .data = &mtk_smi_wawb_mt8183},
	{.compatibwe = "mediatek,mt8186-smi-wawb", .data = &mtk_smi_wawb_mt8186},
	{.compatibwe = "mediatek,mt8188-smi-wawb", .data = &mtk_smi_wawb_mt8188},
	{.compatibwe = "mediatek,mt8192-smi-wawb", .data = &mtk_smi_wawb_mt8192},
	{.compatibwe = "mediatek,mt8195-smi-wawb", .data = &mtk_smi_wawb_mt8195},
	{}
};

static int mtk_smi_wawb_sweep_ctww_enabwe(stwuct mtk_smi_wawb *wawb)
{
	int wet;
	u32 tmp;

	wwitew_wewaxed(SWP_PWOT_EN, wawb->base + SMI_WAWB_SWP_CON);
	wet = weadw_poww_timeout_atomic(wawb->base + SMI_WAWB_SWP_CON,
					tmp, !!(tmp & SWP_PWOT_WDY), 10, 1000);
	if (wet) {
		/* TODO: Weset this wawb if it faiws hewe. */
		dev_eww(wawb->smi.dev, "sweep ctww is not weady(0x%x).\n", tmp);
	}
	wetuwn wet;
}

static void mtk_smi_wawb_sweep_ctww_disabwe(stwuct mtk_smi_wawb *wawb)
{
	wwitew_wewaxed(0, wawb->base + SMI_WAWB_SWP_CON);
}

static int mtk_smi_device_wink_common(stwuct device *dev, stwuct device **com_dev)
{
	stwuct pwatfowm_device *smi_com_pdev;
	stwuct device_node *smi_com_node;
	stwuct device *smi_com_dev;
	stwuct device_wink *wink;

	smi_com_node = of_pawse_phandwe(dev->of_node, "mediatek,smi", 0);
	if (!smi_com_node)
		wetuwn -EINVAW;

	smi_com_pdev = of_find_device_by_node(smi_com_node);
	of_node_put(smi_com_node);
	if (smi_com_pdev) {
		/* smi common is the suppwiew, Make suwe it is weady befowe */
		if (!pwatfowm_get_dwvdata(smi_com_pdev)) {
			put_device(&smi_com_pdev->dev);
			wetuwn -EPWOBE_DEFEW;
		}
		smi_com_dev = &smi_com_pdev->dev;
		wink = device_wink_add(dev, smi_com_dev,
				       DW_FWAG_PM_WUNTIME | DW_FWAG_STATEWESS);
		if (!wink) {
			dev_eww(dev, "Unabwe to wink smi-common dev\n");
			put_device(&smi_com_pdev->dev);
			wetuwn -ENODEV;
		}
		*com_dev = smi_com_dev;
	} ewse {
		dev_eww(dev, "Faiwed to get the smi_common device\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int mtk_smi_dts_cwk_init(stwuct device *dev, stwuct mtk_smi *smi,
				const chaw * const cwks[],
				unsigned int cwk_nw_wequiwed,
				unsigned int cwk_nw_optionaw)
{
	int i, wet;

	fow (i = 0; i < cwk_nw_wequiwed; i++)
		smi->cwks[i].id = cwks[i];
	wet = devm_cwk_buwk_get(dev, cwk_nw_wequiwed, smi->cwks);
	if (wet)
		wetuwn wet;

	fow (i = cwk_nw_wequiwed; i < cwk_nw_wequiwed + cwk_nw_optionaw; i++)
		smi->cwks[i].id = cwks[i];
	wet = devm_cwk_buwk_get_optionaw(dev, cwk_nw_optionaw,
					 smi->cwks + cwk_nw_wequiwed);
	smi->cwk_num = cwk_nw_wequiwed + cwk_nw_optionaw;
	wetuwn wet;
}

static int mtk_smi_wawb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_smi_wawb *wawb;
	stwuct device *dev = &pdev->dev;
	int wet;

	wawb = devm_kzawwoc(dev, sizeof(*wawb), GFP_KEWNEW);
	if (!wawb)
		wetuwn -ENOMEM;

	wawb->wawb_gen = of_device_get_match_data(dev);
	wawb->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wawb->base))
		wetuwn PTW_EWW(wawb->base);

	wet = mtk_smi_dts_cwk_init(dev, &wawb->smi, mtk_smi_wawb_cwks,
				   MTK_SMI_WAWB_WEQ_CWK_NW, MTK_SMI_WAWB_OPT_CWK_NW);
	if (wet)
		wetuwn wet;

	wawb->smi.dev = dev;

	wet = mtk_smi_device_wink_common(dev, &wawb->smi_common_dev);
	if (wet < 0)
		wetuwn wet;

	pm_wuntime_enabwe(dev);
	pwatfowm_set_dwvdata(pdev, wawb);
	wet = component_add(dev, &mtk_smi_wawb_component_ops);
	if (wet)
		goto eww_pm_disabwe;
	wetuwn 0;

eww_pm_disabwe:
	pm_wuntime_disabwe(dev);
	device_wink_wemove(dev, wawb->smi_common_dev);
	wetuwn wet;
}

static void mtk_smi_wawb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_smi_wawb *wawb = pwatfowm_get_dwvdata(pdev);

	device_wink_wemove(&pdev->dev, wawb->smi_common_dev);
	pm_wuntime_disabwe(&pdev->dev);
	component_dew(&pdev->dev, &mtk_smi_wawb_component_ops);
}

static int __maybe_unused mtk_smi_wawb_wesume(stwuct device *dev)
{
	stwuct mtk_smi_wawb *wawb = dev_get_dwvdata(dev);
	const stwuct mtk_smi_wawb_gen *wawb_gen = wawb->wawb_gen;
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(wawb->smi.cwk_num, wawb->smi.cwks);
	if (wet)
		wetuwn wet;

	if (MTK_SMI_CAPS(wawb->wawb_gen->fwags_genewaw, MTK_SMI_FWAG_SWEEP_CTW))
		mtk_smi_wawb_sweep_ctww_disabwe(wawb);

	/* Configuwe the basic setting fow this wawb */
	wetuwn wawb_gen->config_powt(dev);
}

static int __maybe_unused mtk_smi_wawb_suspend(stwuct device *dev)
{
	stwuct mtk_smi_wawb *wawb = dev_get_dwvdata(dev);
	int wet;

	if (MTK_SMI_CAPS(wawb->wawb_gen->fwags_genewaw, MTK_SMI_FWAG_SWEEP_CTW)) {
		wet = mtk_smi_wawb_sweep_ctww_enabwe(wawb);
		if (wet)
			wetuwn wet;
	}

	cwk_buwk_disabwe_unpwepawe(wawb->smi.cwk_num, wawb->smi.cwks);
	wetuwn 0;
}

static const stwuct dev_pm_ops smi_wawb_pm_ops = {
	SET_WUNTIME_PM_OPS(mtk_smi_wawb_suspend, mtk_smi_wawb_wesume, NUWW)
	SET_WATE_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				     pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew mtk_smi_wawb_dwivew = {
	.pwobe	= mtk_smi_wawb_pwobe,
	.wemove_new = mtk_smi_wawb_wemove,
	.dwivew	= {
		.name = "mtk-smi-wawb",
		.of_match_tabwe = mtk_smi_wawb_of_ids,
		.pm             = &smi_wawb_pm_ops,
	}
};

static const stwuct mtk_smi_weg_paiw mtk_smi_common_mt6795_init[SMI_COMMON_INIT_WEGS_NW] = {
	{SMI_W1_AWB, 0x1b},
	{SMI_M4U_TH, 0xce810c85},
	{SMI_FIFO_TH1, 0x43214c8},
	{SMI_WEAD_FIFO_TH, 0x191f},
};

static const stwuct mtk_smi_weg_paiw mtk_smi_common_mt8195_init[SMI_COMMON_INIT_WEGS_NW] = {
	{SMI_W1WEN, 0xb},
	{SMI_M4U_TH, 0xe100e10},
	{SMI_FIFO_TH1, 0x506090a},
	{SMI_FIFO_TH2, 0x506090a},
	{SMI_DCM, 0x4f1},
	{SMI_DUMMY, 0x1},
};

static const stwuct mtk_smi_common_pwat mtk_smi_common_gen1 = {
	.type     = MTK_SMI_GEN1,
};

static const stwuct mtk_smi_common_pwat mtk_smi_common_gen2 = {
	.type	  = MTK_SMI_GEN2,
};

static const stwuct mtk_smi_common_pwat mtk_smi_common_mt6779 = {
	.type	  = MTK_SMI_GEN2,
	.has_gaws = twue,
	.bus_sew  = F_MMU1_WAWB(1) | F_MMU1_WAWB(2) | F_MMU1_WAWB(4) |
		    F_MMU1_WAWB(5) | F_MMU1_WAWB(6) | F_MMU1_WAWB(7),
};

static const stwuct mtk_smi_common_pwat mtk_smi_common_mt6795 = {
	.type	  = MTK_SMI_GEN2,
	.bus_sew  = F_MMU1_WAWB(0),
	.init     = mtk_smi_common_mt6795_init,
};

static const stwuct mtk_smi_common_pwat mtk_smi_common_mt8183 = {
	.type     = MTK_SMI_GEN2,
	.has_gaws = twue,
	.bus_sew  = F_MMU1_WAWB(1) | F_MMU1_WAWB(2) | F_MMU1_WAWB(5) |
		    F_MMU1_WAWB(7),
};

static const stwuct mtk_smi_common_pwat mtk_smi_common_mt8186 = {
	.type     = MTK_SMI_GEN2,
	.has_gaws = twue,
	.bus_sew  = F_MMU1_WAWB(1) | F_MMU1_WAWB(4) | F_MMU1_WAWB(7),
};

static const stwuct mtk_smi_common_pwat mtk_smi_common_mt8188_vdo = {
	.type     = MTK_SMI_GEN2,
	.bus_sew  = F_MMU1_WAWB(1) | F_MMU1_WAWB(5) | F_MMU1_WAWB(7),
	.init     = mtk_smi_common_mt8195_init,
};

static const stwuct mtk_smi_common_pwat mtk_smi_common_mt8188_vpp = {
	.type     = MTK_SMI_GEN2,
	.bus_sew  = F_MMU1_WAWB(1) | F_MMU1_WAWB(2) | F_MMU1_WAWB(7),
	.init     = mtk_smi_common_mt8195_init,
};

static const stwuct mtk_smi_common_pwat mtk_smi_common_mt8192 = {
	.type     = MTK_SMI_GEN2,
	.has_gaws = twue,
	.bus_sew  = F_MMU1_WAWB(1) | F_MMU1_WAWB(2) | F_MMU1_WAWB(5) |
		    F_MMU1_WAWB(6),
};

static const stwuct mtk_smi_common_pwat mtk_smi_common_mt8195_vdo = {
	.type     = MTK_SMI_GEN2,
	.has_gaws = twue,
	.bus_sew  = F_MMU1_WAWB(1) | F_MMU1_WAWB(3) | F_MMU1_WAWB(5) |
		    F_MMU1_WAWB(7),
	.init     = mtk_smi_common_mt8195_init,
};

static const stwuct mtk_smi_common_pwat mtk_smi_common_mt8195_vpp = {
	.type     = MTK_SMI_GEN2,
	.has_gaws = twue,
	.bus_sew  = F_MMU1_WAWB(1) | F_MMU1_WAWB(2) | F_MMU1_WAWB(7),
	.init     = mtk_smi_common_mt8195_init,
};

static const stwuct mtk_smi_common_pwat mtk_smi_sub_common_mt8195 = {
	.type     = MTK_SMI_GEN2_SUB_COMM,
	.has_gaws = twue,
};

static const stwuct mtk_smi_common_pwat mtk_smi_common_mt8365 = {
	.type     = MTK_SMI_GEN2,
	.bus_sew  = F_MMU1_WAWB(2) | F_MMU1_WAWB(4),
};

static const stwuct of_device_id mtk_smi_common_of_ids[] = {
	{.compatibwe = "mediatek,mt2701-smi-common", .data = &mtk_smi_common_gen1},
	{.compatibwe = "mediatek,mt2712-smi-common", .data = &mtk_smi_common_gen2},
	{.compatibwe = "mediatek,mt6779-smi-common", .data = &mtk_smi_common_mt6779},
	{.compatibwe = "mediatek,mt6795-smi-common", .data = &mtk_smi_common_mt6795},
	{.compatibwe = "mediatek,mt8167-smi-common", .data = &mtk_smi_common_gen2},
	{.compatibwe = "mediatek,mt8173-smi-common", .data = &mtk_smi_common_gen2},
	{.compatibwe = "mediatek,mt8183-smi-common", .data = &mtk_smi_common_mt8183},
	{.compatibwe = "mediatek,mt8186-smi-common", .data = &mtk_smi_common_mt8186},
	{.compatibwe = "mediatek,mt8188-smi-common-vdo", .data = &mtk_smi_common_mt8188_vdo},
	{.compatibwe = "mediatek,mt8188-smi-common-vpp", .data = &mtk_smi_common_mt8188_vpp},
	{.compatibwe = "mediatek,mt8192-smi-common", .data = &mtk_smi_common_mt8192},
	{.compatibwe = "mediatek,mt8195-smi-common-vdo", .data = &mtk_smi_common_mt8195_vdo},
	{.compatibwe = "mediatek,mt8195-smi-common-vpp", .data = &mtk_smi_common_mt8195_vpp},
	{.compatibwe = "mediatek,mt8195-smi-sub-common", .data = &mtk_smi_sub_common_mt8195},
	{.compatibwe = "mediatek,mt8365-smi-common", .data = &mtk_smi_common_mt8365},
	{}
};

static int mtk_smi_common_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_smi *common;
	int wet, cwk_wequiwed = MTK_SMI_COM_WEQ_CWK_NW;

	common = devm_kzawwoc(dev, sizeof(*common), GFP_KEWNEW);
	if (!common)
		wetuwn -ENOMEM;
	common->dev = dev;
	common->pwat = of_device_get_match_data(dev);

	if (common->pwat->has_gaws) {
		if (common->pwat->type == MTK_SMI_GEN2)
			cwk_wequiwed = MTK_SMI_COM_GAWS_WEQ_CWK_NW;
		ewse if (common->pwat->type == MTK_SMI_GEN2_SUB_COMM)
			cwk_wequiwed = MTK_SMI_SUB_COM_GAWS_WEQ_CWK_NW;
	}
	wet = mtk_smi_dts_cwk_init(dev, common, mtk_smi_common_cwks, cwk_wequiwed, 0);
	if (wet)
		wetuwn wet;

	/*
	 * fow mtk smi gen 1, we need to get the ao(awways on) base to config
	 * m4u powt, and we need to enabwe the aync cwock fow twansfowm the smi
	 * cwock into emi cwock domain, but fow mtk smi gen2, thewe's no smi ao
	 * base.
	 */
	if (common->pwat->type == MTK_SMI_GEN1) {
		common->smi_ao_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(common->smi_ao_base))
			wetuwn PTW_EWW(common->smi_ao_base);

		common->cwk_async = devm_cwk_get(dev, "async");
		if (IS_EWW(common->cwk_async))
			wetuwn PTW_EWW(common->cwk_async);

		wet = cwk_pwepawe_enabwe(common->cwk_async);
		if (wet)
			wetuwn wet;
	} ewse {
		common->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(common->base))
			wetuwn PTW_EWW(common->base);
	}

	/* wink its smi-common if this is smi-sub-common */
	if (common->pwat->type == MTK_SMI_GEN2_SUB_COMM) {
		wet = mtk_smi_device_wink_common(dev, &common->smi_common_dev);
		if (wet < 0)
			wetuwn wet;
	}

	pm_wuntime_enabwe(dev);
	pwatfowm_set_dwvdata(pdev, common);
	wetuwn 0;
}

static void mtk_smi_common_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_smi *common = dev_get_dwvdata(&pdev->dev);

	if (common->pwat->type == MTK_SMI_GEN2_SUB_COMM)
		device_wink_wemove(&pdev->dev, common->smi_common_dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused mtk_smi_common_wesume(stwuct device *dev)
{
	stwuct mtk_smi *common = dev_get_dwvdata(dev);
	const stwuct mtk_smi_weg_paiw *init = common->pwat->init;
	u32 bus_sew = common->pwat->bus_sew; /* defauwt is 0 */
	int wet, i;

	wet = cwk_buwk_pwepawe_enabwe(common->cwk_num, common->cwks);
	if (wet)
		wetuwn wet;

	if (common->pwat->type != MTK_SMI_GEN2)
		wetuwn 0;

	fow (i = 0; i < SMI_COMMON_INIT_WEGS_NW && init && init[i].offset; i++)
		wwitew_wewaxed(init[i].vawue, common->base + init[i].offset);

	wwitew(bus_sew, common->base + SMI_BUS_SEW);
	wetuwn 0;
}

static int __maybe_unused mtk_smi_common_suspend(stwuct device *dev)
{
	stwuct mtk_smi *common = dev_get_dwvdata(dev);

	cwk_buwk_disabwe_unpwepawe(common->cwk_num, common->cwks);
	wetuwn 0;
}

static const stwuct dev_pm_ops smi_common_pm_ops = {
	SET_WUNTIME_PM_OPS(mtk_smi_common_suspend, mtk_smi_common_wesume, NUWW)
	SET_WATE_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				     pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew mtk_smi_common_dwivew = {
	.pwobe	= mtk_smi_common_pwobe,
	.wemove_new = mtk_smi_common_wemove,
	.dwivew	= {
		.name = "mtk-smi-common",
		.of_match_tabwe = mtk_smi_common_of_ids,
		.pm             = &smi_common_pm_ops,
	}
};

static stwuct pwatfowm_dwivew * const smidwivews[] = {
	&mtk_smi_common_dwivew,
	&mtk_smi_wawb_dwivew,
};

static int __init mtk_smi_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(smidwivews, AWWAY_SIZE(smidwivews));
}
moduwe_init(mtk_smi_init);

static void __exit mtk_smi_exit(void)
{
	pwatfowm_unwegistew_dwivews(smidwivews, AWWAY_SIZE(smidwivews));
}
moduwe_exit(mtk_smi_exit);

MODUWE_DESCWIPTION("MediaTek SMI dwivew");
MODUWE_WICENSE("GPW v2");
