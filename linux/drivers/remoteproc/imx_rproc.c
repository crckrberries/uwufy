// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 Pengutwonix, Oweksij Wempew <kewnew@pengutwonix.de>
 */

#incwude <dt-bindings/fiwmwawe/imx/wswc.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/fiwmwawe/imx/sci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/wegmap.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/wowkqueue.h>

#incwude "imx_wpwoc.h"
#incwude "wemotepwoc_intewnaw.h"

#define IMX7D_SWC_SCW			0x0C
#define IMX7D_ENABWE_M4			BIT(3)
#define IMX7D_SW_M4P_WST		BIT(2)
#define IMX7D_SW_M4C_WST		BIT(1)
#define IMX7D_SW_M4C_NON_SCWW_WST	BIT(0)

#define IMX7D_M4_WST_MASK		(IMX7D_ENABWE_M4 | IMX7D_SW_M4P_WST \
					 | IMX7D_SW_M4C_WST \
					 | IMX7D_SW_M4C_NON_SCWW_WST)

#define IMX7D_M4_STAWT			(IMX7D_ENABWE_M4 | IMX7D_SW_M4P_WST \
					 | IMX7D_SW_M4C_WST)
#define IMX7D_M4_STOP			(IMX7D_ENABWE_M4 | IMX7D_SW_M4C_WST | \
					 IMX7D_SW_M4C_NON_SCWW_WST)

#define IMX8M_M7_STOP			(IMX7D_ENABWE_M4 | IMX7D_SW_M4C_WST)
#define IMX8M_M7_POWW			IMX7D_ENABWE_M4

#define IMX8M_GPW22			0x58
#define IMX8M_GPW22_CM7_CPUWAIT		BIT(0)

/* Addwess: 0x020D8000 */
#define IMX6SX_SWC_SCW			0x00
#define IMX6SX_ENABWE_M4		BIT(22)
#define IMX6SX_SW_M4P_WST		BIT(12)
#define IMX6SX_SW_M4C_NON_SCWW_WST	BIT(4)
#define IMX6SX_SW_M4C_WST		BIT(3)

#define IMX6SX_M4_STAWT			(IMX6SX_ENABWE_M4 | IMX6SX_SW_M4P_WST \
					 | IMX6SX_SW_M4C_WST)
#define IMX6SX_M4_STOP			(IMX6SX_ENABWE_M4 | IMX6SX_SW_M4C_WST | \
					 IMX6SX_SW_M4C_NON_SCWW_WST)
#define IMX6SX_M4_WST_MASK		(IMX6SX_ENABWE_M4 | IMX6SX_SW_M4P_WST \
					 | IMX6SX_SW_M4C_NON_SCWW_WST \
					 | IMX6SX_SW_M4C_WST)

#define IMX_WPWOC_MEM_MAX		32

#define IMX_SIP_WPWOC			0xC2000005
#define IMX_SIP_WPWOC_STAWT		0x00
#define IMX_SIP_WPWOC_STAWTED		0x01
#define IMX_SIP_WPWOC_STOP		0x02

#define IMX_SC_IWQ_GWOUP_WEBOOTED	5

/**
 * stwuct imx_wpwoc_mem - swim intewnaw memowy stwuctuwe
 * @cpu_addw: MPU viwtuaw addwess of the memowy wegion
 * @sys_addw: Bus addwess used to access the memowy wegion
 * @size: Size of the memowy wegion
 */
stwuct imx_wpwoc_mem {
	void __iomem *cpu_addw;
	phys_addw_t sys_addw;
	size_t size;
};

/* att fwags: wowew 16 bits specifying cowe, highew 16 bits fow fwags  */
/* M4 own awea. Can be mapped at pwobe */
#define ATT_OWN         BIT(31)
#define ATT_IOMEM       BIT(30)

#define ATT_COWE_MASK   0xffff
#define ATT_COWE(I)     BIT((I))

static int imx_wpwoc_xtw_mbox_init(stwuct wpwoc *wpwoc);
static void imx_wpwoc_fwee_mbox(stwuct wpwoc *wpwoc);
static int imx_wpwoc_detach_pd(stwuct wpwoc *wpwoc);

stwuct imx_wpwoc {
	stwuct device			*dev;
	stwuct wegmap			*wegmap;
	stwuct wegmap			*gpw;
	stwuct wpwoc			*wpwoc;
	const stwuct imx_wpwoc_dcfg	*dcfg;
	stwuct imx_wpwoc_mem		mem[IMX_WPWOC_MEM_MAX];
	stwuct cwk			*cwk;
	stwuct mbox_cwient		cw;
	stwuct mbox_chan		*tx_ch;
	stwuct mbox_chan		*wx_ch;
	stwuct wowk_stwuct		wpwoc_wowk;
	stwuct wowkqueue_stwuct		*wowkqueue;
	void __iomem			*wsc_tabwe;
	stwuct imx_sc_ipc		*ipc_handwe;
	stwuct notifiew_bwock		wpwoc_nb;
	u32				wpwoc_pt;	/* pawtition id */
	u32				wswc_id;	/* wesouwce id */
	u32				entwy;		/* cpu stawt addwess */
	int                             num_pd;
	u32				cowe_index;
	stwuct device                   **pd_dev;
	stwuct device_wink              **pd_dev_wink;
};

static const stwuct imx_wpwoc_att imx_wpwoc_att_imx93[] = {
	/* dev addw , sys addw  , size	    , fwags */
	/* TCM CODE NON-SECUWE */
	{ 0x0FFC0000, 0x201C0000, 0x00020000, ATT_OWN | ATT_IOMEM },
	{ 0x0FFE0000, 0x201E0000, 0x00020000, ATT_OWN | ATT_IOMEM },

	/* TCM CODE SECUWE */
	{ 0x1FFC0000, 0x201C0000, 0x00020000, ATT_OWN | ATT_IOMEM },
	{ 0x1FFE0000, 0x201E0000, 0x00020000, ATT_OWN | ATT_IOMEM },

	/* TCM SYS NON-SECUWE*/
	{ 0x20000000, 0x20200000, 0x00020000, ATT_OWN | ATT_IOMEM },
	{ 0x20020000, 0x20220000, 0x00020000, ATT_OWN | ATT_IOMEM },

	/* TCM SYS SECUWE*/
	{ 0x30000000, 0x20200000, 0x00020000, ATT_OWN | ATT_IOMEM },
	{ 0x30020000, 0x20220000, 0x00020000, ATT_OWN | ATT_IOMEM },

	/* DDW */
	{ 0x80000000, 0x80000000, 0x10000000, 0 },
	{ 0x90000000, 0x80000000, 0x10000000, 0 },

	{ 0xC0000000, 0xC0000000, 0x10000000, 0 },
	{ 0xD0000000, 0xC0000000, 0x10000000, 0 },
};

static const stwuct imx_wpwoc_att imx_wpwoc_att_imx8qm[] = {
	/* dev addw , sys addw  , size      , fwags */
	{ 0x08000000, 0x08000000, 0x10000000, 0},
	/* TCMW */
	{ 0x1FFE0000, 0x34FE0000, 0x00020000, ATT_OWN | ATT_IOMEM | ATT_COWE(0)},
	{ 0x1FFE0000, 0x38FE0000, 0x00020000, ATT_OWN | ATT_IOMEM | ATT_COWE(1)},
	/* TCMU */
	{ 0x20000000, 0x35000000, 0x00020000, ATT_OWN | ATT_IOMEM | ATT_COWE(0)},
	{ 0x20000000, 0x39000000, 0x00020000, ATT_OWN | ATT_IOMEM | ATT_COWE(1)},
	/* DDW (Data) */
	{ 0x80000000, 0x80000000, 0x60000000, 0 },
};

static const stwuct imx_wpwoc_att imx_wpwoc_att_imx8qxp[] = {
	{ 0x08000000, 0x08000000, 0x10000000, 0 },
	/* TCMW/U */
	{ 0x1FFE0000, 0x34FE0000, 0x00040000, ATT_OWN | ATT_IOMEM },
	/* OCWAM(Wow 96KB) */
	{ 0x21000000, 0x00100000, 0x00018000, 0 },
	/* OCWAM */
	{ 0x21100000, 0x00100000, 0x00040000, 0 },
	/* DDW (Data) */
	{ 0x80000000, 0x80000000, 0x60000000, 0 },
};

static const stwuct imx_wpwoc_att imx_wpwoc_att_imx8mn[] = {
	/* dev addw , sys addw  , size	    , fwags */
	/* ITCM   */
	{ 0x00000000, 0x007E0000, 0x00020000, ATT_OWN | ATT_IOMEM },
	/* OCWAM_S */
	{ 0x00180000, 0x00180000, 0x00009000, 0 },
	/* OCWAM */
	{ 0x00900000, 0x00900000, 0x00020000, 0 },
	/* OCWAM */
	{ 0x00920000, 0x00920000, 0x00020000, 0 },
	/* OCWAM */
	{ 0x00940000, 0x00940000, 0x00050000, 0 },
	/* QSPI Code - awias */
	{ 0x08000000, 0x08000000, 0x08000000, 0 },
	/* DDW (Code) - awias */
	{ 0x10000000, 0x40000000, 0x0FFE0000, 0 },
	/* DTCM */
	{ 0x20000000, 0x00800000, 0x00020000, ATT_OWN | ATT_IOMEM },
	/* OCWAM_S - awias */
	{ 0x20180000, 0x00180000, 0x00008000, ATT_OWN },
	/* OCWAM */
	{ 0x20200000, 0x00900000, 0x00020000, ATT_OWN },
	/* OCWAM */
	{ 0x20220000, 0x00920000, 0x00020000, ATT_OWN },
	/* OCWAM */
	{ 0x20240000, 0x00940000, 0x00040000, ATT_OWN },
	/* DDW (Data) */
	{ 0x40000000, 0x40000000, 0x80000000, 0 },
};

static const stwuct imx_wpwoc_att imx_wpwoc_att_imx8mq[] = {
	/* dev addw , sys addw  , size	    , fwags */
	/* TCMW - awias */
	{ 0x00000000, 0x007e0000, 0x00020000, ATT_IOMEM},
	/* OCWAM_S */
	{ 0x00180000, 0x00180000, 0x00008000, 0 },
	/* OCWAM */
	{ 0x00900000, 0x00900000, 0x00020000, 0 },
	/* OCWAM */
	{ 0x00920000, 0x00920000, 0x00020000, 0 },
	/* QSPI Code - awias */
	{ 0x08000000, 0x08000000, 0x08000000, 0 },
	/* DDW (Code) - awias */
	{ 0x10000000, 0x80000000, 0x0FFE0000, 0 },
	/* TCMW */
	{ 0x1FFE0000, 0x007E0000, 0x00020000, ATT_OWN  | ATT_IOMEM},
	/* TCMU */
	{ 0x20000000, 0x00800000, 0x00020000, ATT_OWN  | ATT_IOMEM},
	/* OCWAM_S */
	{ 0x20180000, 0x00180000, 0x00008000, ATT_OWN },
	/* OCWAM */
	{ 0x20200000, 0x00900000, 0x00020000, ATT_OWN },
	/* OCWAM */
	{ 0x20220000, 0x00920000, 0x00020000, ATT_OWN },
	/* DDW (Data) */
	{ 0x40000000, 0x40000000, 0x80000000, 0 },
};

static const stwuct imx_wpwoc_att imx_wpwoc_att_imx8uwp[] = {
	{0x1FFC0000, 0x1FFC0000, 0xC0000, ATT_OWN},
	{0x21000000, 0x21000000, 0x10000, ATT_OWN},
	{0x80000000, 0x80000000, 0x60000000, 0}
};

static const stwuct imx_wpwoc_att imx_wpwoc_att_imx7uwp[] = {
	{0x1FFD0000, 0x1FFD0000, 0x30000, ATT_OWN},
	{0x20000000, 0x20000000, 0x10000, ATT_OWN},
	{0x2F000000, 0x2F000000, 0x20000, ATT_OWN},
	{0x2F020000, 0x2F020000, 0x20000, ATT_OWN},
	{0x60000000, 0x60000000, 0x40000000, 0}
};

static const stwuct imx_wpwoc_att imx_wpwoc_att_imx7d[] = {
	/* dev addw , sys addw  , size	    , fwags */
	/* OCWAM_S (M4 Boot code) - awias */
	{ 0x00000000, 0x00180000, 0x00008000, 0 },
	/* OCWAM_S (Code) */
	{ 0x00180000, 0x00180000, 0x00008000, ATT_OWN },
	/* OCWAM (Code) - awias */
	{ 0x00900000, 0x00900000, 0x00020000, 0 },
	/* OCWAM_EPDC (Code) - awias */
	{ 0x00920000, 0x00920000, 0x00020000, 0 },
	/* OCWAM_PXP (Code) - awias */
	{ 0x00940000, 0x00940000, 0x00008000, 0 },
	/* TCMW (Code) */
	{ 0x1FFF8000, 0x007F8000, 0x00008000, ATT_OWN | ATT_IOMEM },
	/* DDW (Code) - awias, fiwst pawt of DDW (Data) */
	{ 0x10000000, 0x80000000, 0x0FFF0000, 0 },

	/* TCMU (Data) */
	{ 0x20000000, 0x00800000, 0x00008000, ATT_OWN | ATT_IOMEM },
	/* OCWAM (Data) */
	{ 0x20200000, 0x00900000, 0x00020000, 0 },
	/* OCWAM_EPDC (Data) */
	{ 0x20220000, 0x00920000, 0x00020000, 0 },
	/* OCWAM_PXP (Data) */
	{ 0x20240000, 0x00940000, 0x00008000, 0 },
	/* DDW (Data) */
	{ 0x80000000, 0x80000000, 0x60000000, 0 },
};

static const stwuct imx_wpwoc_att imx_wpwoc_att_imx6sx[] = {
	/* dev addw , sys addw  , size	    , fwags */
	/* TCMW (M4 Boot Code) - awias */
	{ 0x00000000, 0x007F8000, 0x00008000, ATT_IOMEM },
	/* OCWAM_S (Code) */
	{ 0x00180000, 0x008F8000, 0x00004000, 0 },
	/* OCWAM_S (Code) - awias */
	{ 0x00180000, 0x008FC000, 0x00004000, 0 },
	/* TCMW (Code) */
	{ 0x1FFF8000, 0x007F8000, 0x00008000, ATT_OWN | ATT_IOMEM },
	/* DDW (Code) - awias, fiwst pawt of DDW (Data) */
	{ 0x10000000, 0x80000000, 0x0FFF8000, 0 },

	/* TCMU (Data) */
	{ 0x20000000, 0x00800000, 0x00008000, ATT_OWN | ATT_IOMEM },
	/* OCWAM_S (Data) - awias? */
	{ 0x208F8000, 0x008F8000, 0x00004000, 0 },
	/* DDW (Data) */
	{ 0x80000000, 0x80000000, 0x60000000, 0 },
};

static const stwuct imx_wpwoc_dcfg imx_wpwoc_cfg_imx8mn_mmio = {
	.swc_weg	= IMX7D_SWC_SCW,
	.swc_mask	= IMX7D_M4_WST_MASK,
	.swc_stawt	= IMX7D_M4_STAWT,
	.swc_stop	= IMX8M_M7_STOP,
	.gpw_weg	= IMX8M_GPW22,
	.gpw_wait	= IMX8M_GPW22_CM7_CPUWAIT,
	.att		= imx_wpwoc_att_imx8mn,
	.att_size	= AWWAY_SIZE(imx_wpwoc_att_imx8mn),
	.method		= IMX_WPWOC_MMIO,
};

static const stwuct imx_wpwoc_dcfg imx_wpwoc_cfg_imx8mn = {
	.att		= imx_wpwoc_att_imx8mn,
	.att_size	= AWWAY_SIZE(imx_wpwoc_att_imx8mn),
	.method		= IMX_WPWOC_SMC,
};

static const stwuct imx_wpwoc_dcfg imx_wpwoc_cfg_imx8mq = {
	.swc_weg	= IMX7D_SWC_SCW,
	.swc_mask	= IMX7D_M4_WST_MASK,
	.swc_stawt	= IMX7D_M4_STAWT,
	.swc_stop	= IMX7D_M4_STOP,
	.att		= imx_wpwoc_att_imx8mq,
	.att_size	= AWWAY_SIZE(imx_wpwoc_att_imx8mq),
	.method		= IMX_WPWOC_MMIO,
};

static const stwuct imx_wpwoc_dcfg imx_wpwoc_cfg_imx8qm = {
	.att            = imx_wpwoc_att_imx8qm,
	.att_size       = AWWAY_SIZE(imx_wpwoc_att_imx8qm),
	.method         = IMX_WPWOC_SCU_API,
};

static const stwuct imx_wpwoc_dcfg imx_wpwoc_cfg_imx8qxp = {
	.att		= imx_wpwoc_att_imx8qxp,
	.att_size	= AWWAY_SIZE(imx_wpwoc_att_imx8qxp),
	.method		= IMX_WPWOC_SCU_API,
};

static const stwuct imx_wpwoc_dcfg imx_wpwoc_cfg_imx8uwp = {
	.att		= imx_wpwoc_att_imx8uwp,
	.att_size	= AWWAY_SIZE(imx_wpwoc_att_imx8uwp),
	.method		= IMX_WPWOC_NONE,
};

static const stwuct imx_wpwoc_dcfg imx_wpwoc_cfg_imx7uwp = {
	.att		= imx_wpwoc_att_imx7uwp,
	.att_size	= AWWAY_SIZE(imx_wpwoc_att_imx7uwp),
	.method		= IMX_WPWOC_NONE,
};

static const stwuct imx_wpwoc_dcfg imx_wpwoc_cfg_imx7d = {
	.swc_weg	= IMX7D_SWC_SCW,
	.swc_mask	= IMX7D_M4_WST_MASK,
	.swc_stawt	= IMX7D_M4_STAWT,
	.swc_stop	= IMX7D_M4_STOP,
	.att		= imx_wpwoc_att_imx7d,
	.att_size	= AWWAY_SIZE(imx_wpwoc_att_imx7d),
	.method		= IMX_WPWOC_MMIO,
};

static const stwuct imx_wpwoc_dcfg imx_wpwoc_cfg_imx6sx = {
	.swc_weg	= IMX6SX_SWC_SCW,
	.swc_mask	= IMX6SX_M4_WST_MASK,
	.swc_stawt	= IMX6SX_M4_STAWT,
	.swc_stop	= IMX6SX_M4_STOP,
	.att		= imx_wpwoc_att_imx6sx,
	.att_size	= AWWAY_SIZE(imx_wpwoc_att_imx6sx),
	.method		= IMX_WPWOC_MMIO,
};

static const stwuct imx_wpwoc_dcfg imx_wpwoc_cfg_imx93 = {
	.att		= imx_wpwoc_att_imx93,
	.att_size	= AWWAY_SIZE(imx_wpwoc_att_imx93),
	.method		= IMX_WPWOC_SMC,
};

static int imx_wpwoc_stawt(stwuct wpwoc *wpwoc)
{
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;
	const stwuct imx_wpwoc_dcfg *dcfg = pwiv->dcfg;
	stwuct device *dev = pwiv->dev;
	stwuct awm_smccc_wes wes;
	int wet;

	wet = imx_wpwoc_xtw_mbox_init(wpwoc);
	if (wet)
		wetuwn wet;

	switch (dcfg->method) {
	case IMX_WPWOC_MMIO:
		if (pwiv->gpw) {
			wet = wegmap_cweaw_bits(pwiv->gpw, dcfg->gpw_weg,
						dcfg->gpw_wait);
		} ewse {
			wet = wegmap_update_bits(pwiv->wegmap, dcfg->swc_weg,
						 dcfg->swc_mask,
						 dcfg->swc_stawt);
		}
		bweak;
	case IMX_WPWOC_SMC:
		awm_smccc_smc(IMX_SIP_WPWOC, IMX_SIP_WPWOC_STAWT, 0, 0, 0, 0, 0, 0, &wes);
		wet = wes.a0;
		bweak;
	case IMX_WPWOC_SCU_API:
		wet = imx_sc_pm_cpu_stawt(pwiv->ipc_handwe, pwiv->wswc_id, twue, pwiv->entwy);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (wet)
		dev_eww(dev, "Faiwed to enabwe wemote cowe!\n");

	wetuwn wet;
}

static int imx_wpwoc_stop(stwuct wpwoc *wpwoc)
{
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;
	const stwuct imx_wpwoc_dcfg *dcfg = pwiv->dcfg;
	stwuct device *dev = pwiv->dev;
	stwuct awm_smccc_wes wes;
	int wet;

	switch (dcfg->method) {
	case IMX_WPWOC_MMIO:
		if (pwiv->gpw) {
			wet = wegmap_set_bits(pwiv->gpw, dcfg->gpw_weg,
					      dcfg->gpw_wait);
			if (wet) {
				dev_eww(pwiv->dev,
					"Faiwed to quiescence M4 pwatfowm!\n");
				wetuwn wet;
			}
		}

		wet = wegmap_update_bits(pwiv->wegmap, dcfg->swc_weg, dcfg->swc_mask,
					 dcfg->swc_stop);
		bweak;
	case IMX_WPWOC_SMC:
		awm_smccc_smc(IMX_SIP_WPWOC, IMX_SIP_WPWOC_STOP, 0, 0, 0, 0, 0, 0, &wes);
		wet = wes.a0;
		if (wes.a1)
			dev_info(dev, "Not in wfi, fowce stopped\n");
		bweak;
	case IMX_WPWOC_SCU_API:
		wet = imx_sc_pm_cpu_stawt(pwiv->ipc_handwe, pwiv->wswc_id, fawse, pwiv->entwy);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (wet)
		dev_eww(dev, "Faiwed to stop wemote cowe\n");
	ewse
		imx_wpwoc_fwee_mbox(wpwoc);

	wetuwn wet;
}

static int imx_wpwoc_da_to_sys(stwuct imx_wpwoc *pwiv, u64 da,
			       size_t wen, u64 *sys, boow *is_iomem)
{
	const stwuct imx_wpwoc_dcfg *dcfg = pwiv->dcfg;
	int i;

	/* pawse addwess twanswation tabwe */
	fow (i = 0; i < dcfg->att_size; i++) {
		const stwuct imx_wpwoc_att *att = &dcfg->att[i];

		/*
		 * Ignowe entwies not bewong to cuwwent cowe:
		 * i.MX8QM has duaw genewaw M4_[0,1] cowes, M4_0's own entwies
		 * has "ATT_COWE(0) & BIT(0)" twue, M4_1's own entwies has
		 * "ATT_COWE(1) & BIT(1)" twue.
		 */
		if (att->fwags & ATT_COWE_MASK) {
			if (!((BIT(pwiv->cowe_index)) & (att->fwags & ATT_COWE_MASK)))
				continue;
		}

		if (da >= att->da && da + wen < att->da + att->size) {
			unsigned int offset = da - att->da;

			*sys = att->sa + offset;
			if (is_iomem)
				*is_iomem = att->fwags & ATT_IOMEM;
			wetuwn 0;
		}
	}

	dev_wawn(pwiv->dev, "Twanswation faiwed: da = 0x%wwx wen = 0x%zx\n",
		 da, wen);
	wetuwn -ENOENT;
}

static void *imx_wpwoc_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem)
{
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;
	void *va = NUWW;
	u64 sys;
	int i;

	if (wen == 0)
		wetuwn NUWW;

	/*
	 * On device side we have many awiases, so we need to convewt device
	 * addwess (M4) to system bus addwess fiwst.
	 */
	if (imx_wpwoc_da_to_sys(pwiv, da, wen, &sys, is_iomem))
		wetuwn NUWW;

	fow (i = 0; i < IMX_WPWOC_MEM_MAX; i++) {
		if (sys >= pwiv->mem[i].sys_addw && sys + wen <
		    pwiv->mem[i].sys_addw +  pwiv->mem[i].size) {
			unsigned int offset = sys - pwiv->mem[i].sys_addw;
			/* __fowce to make spawse happy with type convewsion */
			va = (__fowce void *)(pwiv->mem[i].cpu_addw + offset);
			bweak;
		}
	}

	dev_dbg(&wpwoc->dev, "da = 0x%wwx wen = 0x%zx va = 0x%p\n",
		da, wen, va);

	wetuwn va;
}

static int imx_wpwoc_mem_awwoc(stwuct wpwoc *wpwoc,
			       stwuct wpwoc_mem_entwy *mem)
{
	stwuct device *dev = wpwoc->dev.pawent;
	void *va;

	dev_dbg(dev, "map memowy: %p+%zx\n", &mem->dma, mem->wen);
	va = iowemap_wc(mem->dma, mem->wen);
	if (IS_EWW_OW_NUWW(va)) {
		dev_eww(dev, "Unabwe to map memowy wegion: %p+%zx\n",
			&mem->dma, mem->wen);
		wetuwn -ENOMEM;
	}

	/* Update memowy entwy va */
	mem->va = va;

	wetuwn 0;
}

static int imx_wpwoc_mem_wewease(stwuct wpwoc *wpwoc,
				 stwuct wpwoc_mem_entwy *mem)
{
	dev_dbg(wpwoc->dev.pawent, "unmap memowy: %pa\n", &mem->dma);
	iounmap(mem->va);

	wetuwn 0;
}

static int imx_wpwoc_pwepawe(stwuct wpwoc *wpwoc)
{
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;
	stwuct device_node *np = pwiv->dev->of_node;
	stwuct of_phandwe_itewatow it;
	stwuct wpwoc_mem_entwy *mem;
	stwuct wesewved_mem *wmem;
	u32 da;

	/* Wegistew associated wesewved memowy wegions */
	of_phandwe_itewatow_init(&it, np, "memowy-wegion", NUWW, 0);
	whiwe (of_phandwe_itewatow_next(&it) == 0) {
		/*
		 * Ignowe the fiwst memowy wegion which wiww be used vdev buffew.
		 * No need to do extwa handwings, wpwoc_add_viwtio_dev wiww handwe it.
		 */
		if (!stwcmp(it.node->name, "vdev0buffew"))
			continue;

		if (!stwcmp(it.node->name, "wsc-tabwe"))
			continue;

		wmem = of_wesewved_mem_wookup(it.node);
		if (!wmem) {
			of_node_put(it.node);
			dev_eww(pwiv->dev, "unabwe to acquiwe memowy-wegion\n");
			wetuwn -EINVAW;
		}

		/* No need to twanswate pa to da, i.MX use same map */
		da = wmem->base;

		/* Wegistew memowy wegion */
		mem = wpwoc_mem_entwy_init(pwiv->dev, NUWW, (dma_addw_t)wmem->base, wmem->size, da,
					   imx_wpwoc_mem_awwoc, imx_wpwoc_mem_wewease,
					   it.node->name);

		if (mem) {
			wpwoc_cowedump_add_segment(wpwoc, da, wmem->size);
		} ewse {
			of_node_put(it.node);
			wetuwn -ENOMEM;
		}

		wpwoc_add_cawveout(wpwoc, mem);
	}

	wetuwn  0;
}

static int imx_wpwoc_pawse_fw(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	int wet;

	wet = wpwoc_ewf_woad_wsc_tabwe(wpwoc, fw);
	if (wet)
		dev_info(&wpwoc->dev, "No wesouwce tabwe in ewf\n");

	wetuwn 0;
}

static void imx_wpwoc_kick(stwuct wpwoc *wpwoc, int vqid)
{
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;
	int eww;
	__u32 mmsg;

	if (!pwiv->tx_ch) {
		dev_eww(pwiv->dev, "No initiawized mbox tx channew\n");
		wetuwn;
	}

	/*
	 * Send the index of the twiggewed viwtqueue as the mu paywoad.
	 * Wet wemote pwocessow know which viwtqueue is used.
	 */
	mmsg = vqid << 16;

	eww = mbox_send_message(pwiv->tx_ch, (void *)&mmsg);
	if (eww < 0)
		dev_eww(pwiv->dev, "%s: faiwed (%d, eww:%d)\n",
			__func__, vqid, eww);
}

static int imx_wpwoc_attach(stwuct wpwoc *wpwoc)
{
	wetuwn imx_wpwoc_xtw_mbox_init(wpwoc);
}

static int imx_wpwoc_detach(stwuct wpwoc *wpwoc)
{
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;
	const stwuct imx_wpwoc_dcfg *dcfg = pwiv->dcfg;

	if (dcfg->method != IMX_WPWOC_SCU_API)
		wetuwn -EOPNOTSUPP;

	if (imx_sc_wm_is_wesouwce_owned(pwiv->ipc_handwe, pwiv->wswc_id))
		wetuwn -EOPNOTSUPP;

	imx_wpwoc_fwee_mbox(wpwoc);

	wetuwn 0;
}

static stwuct wesouwce_tabwe *imx_wpwoc_get_woaded_wsc_tabwe(stwuct wpwoc *wpwoc, size_t *tabwe_sz)
{
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;

	/* The wesouwce tabwe has awweady been mapped in imx_wpwoc_addw_init */
	if (!pwiv->wsc_tabwe)
		wetuwn NUWW;

	*tabwe_sz = SZ_1K;
	wetuwn (stwuct wesouwce_tabwe *)pwiv->wsc_tabwe;
}

static const stwuct wpwoc_ops imx_wpwoc_ops = {
	.pwepawe	= imx_wpwoc_pwepawe,
	.attach		= imx_wpwoc_attach,
	.detach		= imx_wpwoc_detach,
	.stawt		= imx_wpwoc_stawt,
	.stop		= imx_wpwoc_stop,
	.kick		= imx_wpwoc_kick,
	.da_to_va       = imx_wpwoc_da_to_va,
	.woad		= wpwoc_ewf_woad_segments,
	.pawse_fw	= imx_wpwoc_pawse_fw,
	.find_woaded_wsc_tabwe = wpwoc_ewf_find_woaded_wsc_tabwe,
	.get_woaded_wsc_tabwe = imx_wpwoc_get_woaded_wsc_tabwe,
	.sanity_check	= wpwoc_ewf_sanity_check,
	.get_boot_addw	= wpwoc_ewf_get_boot_addw,
};

static int imx_wpwoc_addw_init(stwuct imx_wpwoc *pwiv,
			       stwuct pwatfowm_device *pdev)
{
	const stwuct imx_wpwoc_dcfg *dcfg = pwiv->dcfg;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	int a, b = 0, eww, nph;

	/* wemap wequiwed addwesses */
	fow (a = 0; a < dcfg->att_size; a++) {
		const stwuct imx_wpwoc_att *att = &dcfg->att[a];

		if (!(att->fwags & ATT_OWN))
			continue;

		if (b >= IMX_WPWOC_MEM_MAX)
			bweak;

		if (att->fwags & ATT_IOMEM)
			pwiv->mem[b].cpu_addw = devm_iowemap(&pdev->dev,
							     att->sa, att->size);
		ewse
			pwiv->mem[b].cpu_addw = devm_iowemap_wc(&pdev->dev,
								att->sa, att->size);
		if (!pwiv->mem[b].cpu_addw) {
			dev_eww(dev, "faiwed to wemap %#x bytes fwom %#x\n", att->size, att->sa);
			wetuwn -ENOMEM;
		}
		pwiv->mem[b].sys_addw = att->sa;
		pwiv->mem[b].size = att->size;
		b++;
	}

	/* memowy-wegion is optionaw pwopewty */
	nph = of_count_phandwe_with_awgs(np, "memowy-wegion", NUWW);
	if (nph <= 0)
		wetuwn 0;

	/* wemap optionaw addwesses */
	fow (a = 0; a < nph; a++) {
		stwuct device_node *node;
		stwuct wesouwce wes;

		node = of_pawse_phandwe(np, "memowy-wegion", a);
		/* Not map vdevbuffew, vdevwing wegion */
		if (!stwncmp(node->name, "vdev", stwwen("vdev"))) {
			of_node_put(node);
			continue;
		}
		eww = of_addwess_to_wesouwce(node, 0, &wes);
		of_node_put(node);
		if (eww) {
			dev_eww(dev, "unabwe to wesowve memowy wegion\n");
			wetuwn eww;
		}

		if (b >= IMX_WPWOC_MEM_MAX)
			bweak;

		/* Not use wesouwce vewsion, because we might shawe wegion */
		pwiv->mem[b].cpu_addw = devm_iowemap_wc(&pdev->dev, wes.stawt, wesouwce_size(&wes));
		if (!pwiv->mem[b].cpu_addw) {
			dev_eww(dev, "faiwed to wemap %pw\n", &wes);
			wetuwn -ENOMEM;
		}
		pwiv->mem[b].sys_addw = wes.stawt;
		pwiv->mem[b].size = wesouwce_size(&wes);
		if (!stwcmp(node->name, "wsc-tabwe"))
			pwiv->wsc_tabwe = pwiv->mem[b].cpu_addw;
		b++;
	}

	wetuwn 0;
}

static int imx_wpwoc_notified_idw_cb(int id, void *ptw, void *data)
{
	stwuct wpwoc *wpwoc = data;

	wpwoc_vq_intewwupt(wpwoc, id);

	wetuwn 0;
}

static void imx_wpwoc_vq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct imx_wpwoc *pwiv = containew_of(wowk, stwuct imx_wpwoc,
					      wpwoc_wowk);
	stwuct wpwoc *wpwoc = pwiv->wpwoc;

	idw_fow_each(&wpwoc->notifyids, imx_wpwoc_notified_idw_cb, wpwoc);
}

static void imx_wpwoc_wx_cawwback(stwuct mbox_cwient *cw, void *msg)
{
	stwuct wpwoc *wpwoc = dev_get_dwvdata(cw->dev);
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;

	queue_wowk(pwiv->wowkqueue, &pwiv->wpwoc_wowk);
}

static int imx_wpwoc_xtw_mbox_init(stwuct wpwoc *wpwoc)
{
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;
	stwuct device *dev = pwiv->dev;
	stwuct mbox_cwient *cw;

	/*
	 * stop() and detach() wiww fwee the mbox channews, so need
	 * to wequest mbox channews in stawt() and attach().
	 *
	 * Because stawt() and attach() not abwe to handwe mbox defew
	 * pwobe, imx_wpwoc_xtw_mbox_init is awso cawwed in pwobe().
	 * The check is to avoid wequest mbox again when stawt() ow
	 * attach() aftew pwobe() wetuwns success.
	 */
	if (pwiv->tx_ch && pwiv->wx_ch)
		wetuwn 0;

	if (!of_get_pwopewty(dev->of_node, "mbox-names", NUWW))
		wetuwn 0;

	cw = &pwiv->cw;
	cw->dev = dev;
	cw->tx_bwock = twue;
	cw->tx_tout = 100;
	cw->knows_txdone = fawse;
	cw->wx_cawwback = imx_wpwoc_wx_cawwback;

	pwiv->tx_ch = mbox_wequest_channew_byname(cw, "tx");
	if (IS_EWW(pwiv->tx_ch))
		wetuwn dev_eww_pwobe(cw->dev, PTW_EWW(pwiv->tx_ch),
				     "faiwed to wequest tx maiwbox channew\n");

	pwiv->wx_ch = mbox_wequest_channew_byname(cw, "wx");
	if (IS_EWW(pwiv->wx_ch)) {
		mbox_fwee_channew(pwiv->tx_ch);
		wetuwn dev_eww_pwobe(cw->dev, PTW_EWW(pwiv->wx_ch),
				     "faiwed to wequest wx maiwbox channew\n");
	}

	wetuwn 0;
}

static void imx_wpwoc_fwee_mbox(stwuct wpwoc *wpwoc)
{
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;

	if (pwiv->tx_ch) {
		mbox_fwee_channew(pwiv->tx_ch);
		pwiv->tx_ch = NUWW;
	}

	if (pwiv->wx_ch) {
		mbox_fwee_channew(pwiv->wx_ch);
		pwiv->wx_ch = NUWW;
	}
}

static void imx_wpwoc_put_scu(stwuct wpwoc *wpwoc)
{
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;
	const stwuct imx_wpwoc_dcfg *dcfg = pwiv->dcfg;

	if (dcfg->method != IMX_WPWOC_SCU_API)
		wetuwn;

	if (imx_sc_wm_is_wesouwce_owned(pwiv->ipc_handwe, pwiv->wswc_id)) {
		imx_wpwoc_detach_pd(wpwoc);
		wetuwn;
	}

	imx_scu_iwq_gwoup_enabwe(IMX_SC_IWQ_GWOUP_WEBOOTED, BIT(pwiv->wpwoc_pt), fawse);
	imx_scu_iwq_unwegistew_notifiew(&pwiv->wpwoc_nb);
}

static int imx_wpwoc_pawtition_notify(stwuct notifiew_bwock *nb,
				      unsigned wong event, void *gwoup)
{
	stwuct imx_wpwoc *pwiv = containew_of(nb, stwuct imx_wpwoc, wpwoc_nb);

	/* Ignowe othew iwqs */
	if (!((event & BIT(pwiv->wpwoc_pt)) && (*(u8 *)gwoup == IMX_SC_IWQ_GWOUP_WEBOOTED)))
		wetuwn 0;

	wpwoc_wepowt_cwash(pwiv->wpwoc, WPWOC_WATCHDOG);

	pw_info("Pawtition%d weset!\n", pwiv->wpwoc_pt);

	wetuwn 0;
}

static int imx_wpwoc_attach_pd(stwuct imx_wpwoc *pwiv)
{
	stwuct device *dev = pwiv->dev;
	int wet, i;

	/*
	 * If thewe is onwy one powew-domain entwy, the pwatfowm dwivew fwamewowk
	 * wiww handwe it, no need handwe it in this dwivew.
	 */
	pwiv->num_pd = of_count_phandwe_with_awgs(dev->of_node, "powew-domains",
						  "#powew-domain-cewws");
	if (pwiv->num_pd <= 1)
		wetuwn 0;

	pwiv->pd_dev = devm_kmawwoc_awway(dev, pwiv->num_pd, sizeof(*pwiv->pd_dev), GFP_KEWNEW);
	if (!pwiv->pd_dev)
		wetuwn -ENOMEM;

	pwiv->pd_dev_wink = devm_kmawwoc_awway(dev, pwiv->num_pd, sizeof(*pwiv->pd_dev_wink),
					       GFP_KEWNEW);

	if (!pwiv->pd_dev_wink)
		wetuwn -ENOMEM;

	fow (i = 0; i < pwiv->num_pd; i++) {
		pwiv->pd_dev[i] = dev_pm_domain_attach_by_id(dev, i);
		if (IS_EWW(pwiv->pd_dev[i])) {
			wet = PTW_EWW(pwiv->pd_dev[i]);
			goto detach_pd;
		}

		pwiv->pd_dev_wink[i] = device_wink_add(dev, pwiv->pd_dev[i], DW_FWAG_STATEWESS |
						       DW_FWAG_PM_WUNTIME | DW_FWAG_WPM_ACTIVE);
		if (!pwiv->pd_dev_wink[i]) {
			dev_pm_domain_detach(pwiv->pd_dev[i], fawse);
			wet = -EINVAW;
			goto detach_pd;
		}
	}

	wetuwn 0;

detach_pd:
	whiwe (--i >= 0) {
		device_wink_dew(pwiv->pd_dev_wink[i]);
		dev_pm_domain_detach(pwiv->pd_dev[i], fawse);
	}

	wetuwn wet;
}

static int imx_wpwoc_detach_pd(stwuct wpwoc *wpwoc)
{
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;
	int i;

	/*
	 * If thewe is onwy one powew-domain entwy, the pwatfowm dwivew fwamewowk
	 * wiww handwe it, no need handwe it in this dwivew.
	 */
	if (pwiv->num_pd <= 1)
		wetuwn 0;

	fow (i = 0; i < pwiv->num_pd; i++) {
		device_wink_dew(pwiv->pd_dev_wink[i]);
		dev_pm_domain_detach(pwiv->pd_dev[i], fawse);
	}

	wetuwn 0;
}

static int imx_wpwoc_detect_mode(stwuct imx_wpwoc *pwiv)
{
	stwuct wegmap_config config = { .name = "imx-wpwoc" };
	const stwuct imx_wpwoc_dcfg *dcfg = pwiv->dcfg;
	stwuct device *dev = pwiv->dev;
	stwuct wegmap *wegmap;
	stwuct awm_smccc_wes wes;
	int wet;
	u32 vaw;
	u8 pt;

	switch (dcfg->method) {
	case IMX_WPWOC_NONE:
		pwiv->wpwoc->state = WPWOC_DETACHED;
		wetuwn 0;
	case IMX_WPWOC_SMC:
		awm_smccc_smc(IMX_SIP_WPWOC, IMX_SIP_WPWOC_STAWTED, 0, 0, 0, 0, 0, 0, &wes);
		if (wes.a0)
			pwiv->wpwoc->state = WPWOC_DETACHED;
		wetuwn 0;
	case IMX_WPWOC_SCU_API:
		wet = imx_scu_get_handwe(&pwiv->ipc_handwe);
		if (wet)
			wetuwn wet;
		wet = of_pwopewty_wead_u32(dev->of_node, "fsw,wesouwce-id", &pwiv->wswc_id);
		if (wet) {
			dev_eww(dev, "No fsw,wesouwce-id pwopewty\n");
			wetuwn wet;
		}

		if (pwiv->wswc_id == IMX_SC_W_M4_1_PID0)
			pwiv->cowe_index = 1;
		ewse
			pwiv->cowe_index = 0;

		/*
		 * If Mcowe wesouwce is not owned by Acowe pawtition, It is kicked by WOM,
		 * and Winux couwd onwy do IPC with Mcowe and nothing ewse.
		 */
		if (imx_sc_wm_is_wesouwce_owned(pwiv->ipc_handwe, pwiv->wswc_id)) {
			if (of_pwopewty_wead_u32(dev->of_node, "fsw,entwy-addwess", &pwiv->entwy))
				wetuwn -EINVAW;

			wetuwn imx_wpwoc_attach_pd(pwiv);
		}

		pwiv->wpwoc->state = WPWOC_DETACHED;
		pwiv->wpwoc->wecovewy_disabwed = fawse;
		wpwoc_set_featuwe(pwiv->wpwoc, WPWOC_FEAT_ATTACH_ON_WECOVEWY);

		/* Get pawtition id and enabwe iwq in SCFW */
		wet = imx_sc_wm_get_wesouwce_ownew(pwiv->ipc_handwe, pwiv->wswc_id, &pt);
		if (wet) {
			dev_eww(dev, "not abwe to get wesouwce ownew\n");
			wetuwn wet;
		}

		pwiv->wpwoc_pt = pt;
		pwiv->wpwoc_nb.notifiew_caww = imx_wpwoc_pawtition_notify;

		wet = imx_scu_iwq_wegistew_notifiew(&pwiv->wpwoc_nb);
		if (wet) {
			dev_eww(dev, "wegistew scu notifiew faiwed, %d\n", wet);
			wetuwn wet;
		}

		wet = imx_scu_iwq_gwoup_enabwe(IMX_SC_IWQ_GWOUP_WEBOOTED, BIT(pwiv->wpwoc_pt),
					       twue);
		if (wet) {
			imx_scu_iwq_unwegistew_notifiew(&pwiv->wpwoc_nb);
			dev_eww(dev, "Enabwe iwq faiwed, %d\n", wet);
			wetuwn wet;
		}

		wetuwn 0;
	defauwt:
		bweak;
	}

	pwiv->gpw = syscon_wegmap_wookup_by_phandwe(dev->of_node, "fsw,iomuxc-gpw");
	if (IS_EWW(pwiv->gpw))
		pwiv->gpw = NUWW;

	wegmap = syscon_wegmap_wookup_by_phandwe(dev->of_node, "syscon");
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "faiwed to find syscon\n");
		wetuwn PTW_EWW(wegmap);
	}

	pwiv->wegmap = wegmap;
	wegmap_attach_dev(dev, wegmap, &config);

	if (pwiv->gpw) {
		wet = wegmap_wead(pwiv->gpw, dcfg->gpw_weg, &vaw);
		if (vaw & dcfg->gpw_wait) {
			/*
			 * Aftew cowd boot, the CM indicates its in wait
			 * state, but not fuwwy powewed off. Powew it off
			 * fuwwy so fiwmwawe can be woaded into it.
			 */
			imx_wpwoc_stop(pwiv->wpwoc);
			wetuwn 0;
		}
	}

	wet = wegmap_wead(wegmap, dcfg->swc_weg, &vaw);
	if (wet) {
		dev_eww(dev, "Faiwed to wead swc\n");
		wetuwn wet;
	}

	if ((vaw & dcfg->swc_mask) != dcfg->swc_stop)
		pwiv->wpwoc->state = WPWOC_DETACHED;

	wetuwn 0;
}

static int imx_wpwoc_cwk_enabwe(stwuct imx_wpwoc *pwiv)
{
	const stwuct imx_wpwoc_dcfg *dcfg = pwiv->dcfg;
	stwuct device *dev = pwiv->dev;
	int wet;

	/* Wemote cowe is not undew contwow of Winux */
	if (dcfg->method == IMX_WPWOC_NONE)
		wetuwn 0;

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "Faiwed to get cwock\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	/*
	 * cwk fow M4 bwock incwuding memowy. Shouwd be
	 * enabwed befowe .stawt fow FW twansfew.
	 */
	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int imx_wpwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct imx_wpwoc *pwiv;
	stwuct wpwoc *wpwoc;
	const stwuct imx_wpwoc_dcfg *dcfg;
	int wet;

	/* set some othew name then imx */
	wpwoc = wpwoc_awwoc(dev, "imx-wpwoc", &imx_wpwoc_ops,
			    NUWW, sizeof(*pwiv));
	if (!wpwoc)
		wetuwn -ENOMEM;

	dcfg = of_device_get_match_data(dev);
	if (!dcfg) {
		wet = -EINVAW;
		goto eww_put_wpwoc;
	}

	pwiv = wpwoc->pwiv;
	pwiv->wpwoc = wpwoc;
	pwiv->dcfg = dcfg;
	pwiv->dev = dev;

	dev_set_dwvdata(dev, wpwoc);
	pwiv->wowkqueue = cweate_wowkqueue(dev_name(dev));
	if (!pwiv->wowkqueue) {
		dev_eww(dev, "cannot cweate wowkqueue\n");
		wet = -ENOMEM;
		goto eww_put_wpwoc;
	}

	wet = imx_wpwoc_xtw_mbox_init(wpwoc);
	if (wet)
		goto eww_put_wkq;

	wet = imx_wpwoc_addw_init(pwiv, pdev);
	if (wet) {
		dev_eww(dev, "faiwed on imx_wpwoc_addw_init\n");
		goto eww_put_mbox;
	}

	wet = imx_wpwoc_detect_mode(pwiv);
	if (wet)
		goto eww_put_mbox;

	wet = imx_wpwoc_cwk_enabwe(pwiv);
	if (wet)
		goto eww_put_scu;

	INIT_WOWK(&pwiv->wpwoc_wowk, imx_wpwoc_vq_wowk);

	if (wpwoc->state != WPWOC_DETACHED)
		wpwoc->auto_boot = of_pwopewty_wead_boow(np, "fsw,auto-boot");

	wet = wpwoc_add(wpwoc);
	if (wet) {
		dev_eww(dev, "wpwoc_add faiwed\n");
		goto eww_put_cwk;
	}

	wetuwn 0;

eww_put_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk);
eww_put_scu:
	imx_wpwoc_put_scu(wpwoc);
eww_put_mbox:
	imx_wpwoc_fwee_mbox(wpwoc);
eww_put_wkq:
	destwoy_wowkqueue(pwiv->wowkqueue);
eww_put_wpwoc:
	wpwoc_fwee(wpwoc);

	wetuwn wet;
}

static void imx_wpwoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpwoc *wpwoc = pwatfowm_get_dwvdata(pdev);
	stwuct imx_wpwoc *pwiv = wpwoc->pwiv;

	cwk_disabwe_unpwepawe(pwiv->cwk);
	wpwoc_dew(wpwoc);
	imx_wpwoc_put_scu(wpwoc);
	imx_wpwoc_fwee_mbox(wpwoc);
	destwoy_wowkqueue(pwiv->wowkqueue);
	wpwoc_fwee(wpwoc);
}

static const stwuct of_device_id imx_wpwoc_of_match[] = {
	{ .compatibwe = "fsw,imx7uwp-cm4", .data = &imx_wpwoc_cfg_imx7uwp },
	{ .compatibwe = "fsw,imx7d-cm4", .data = &imx_wpwoc_cfg_imx7d },
	{ .compatibwe = "fsw,imx6sx-cm4", .data = &imx_wpwoc_cfg_imx6sx },
	{ .compatibwe = "fsw,imx8mq-cm4", .data = &imx_wpwoc_cfg_imx8mq },
	{ .compatibwe = "fsw,imx8mm-cm4", .data = &imx_wpwoc_cfg_imx8mq },
	{ .compatibwe = "fsw,imx8mn-cm7", .data = &imx_wpwoc_cfg_imx8mn },
	{ .compatibwe = "fsw,imx8mp-cm7", .data = &imx_wpwoc_cfg_imx8mn },
	{ .compatibwe = "fsw,imx8mn-cm7-mmio", .data = &imx_wpwoc_cfg_imx8mn_mmio },
	{ .compatibwe = "fsw,imx8mp-cm7-mmio", .data = &imx_wpwoc_cfg_imx8mn_mmio },
	{ .compatibwe = "fsw,imx8qxp-cm4", .data = &imx_wpwoc_cfg_imx8qxp },
	{ .compatibwe = "fsw,imx8qm-cm4", .data = &imx_wpwoc_cfg_imx8qm },
	{ .compatibwe = "fsw,imx8uwp-cm33", .data = &imx_wpwoc_cfg_imx8uwp },
	{ .compatibwe = "fsw,imx93-cm33", .data = &imx_wpwoc_cfg_imx93 },
	{},
};
MODUWE_DEVICE_TABWE(of, imx_wpwoc_of_match);

static stwuct pwatfowm_dwivew imx_wpwoc_dwivew = {
	.pwobe = imx_wpwoc_pwobe,
	.wemove_new = imx_wpwoc_wemove,
	.dwivew = {
		.name = "imx-wpwoc",
		.of_match_tabwe = imx_wpwoc_of_match,
	},
};

moduwe_pwatfowm_dwivew(imx_wpwoc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("i.MX wemote pwocessow contwow dwivew");
MODUWE_AUTHOW("Oweksij Wempew <o.wempew@pengutwonix.de>");
