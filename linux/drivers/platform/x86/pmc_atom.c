// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Atom SoC Powew Management Contwowwew Dwivew
 * Copywight (c) 2014-2015,2017,2022 Intew Cowpowation.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_data/x86/cwk-pmc-atom.h>
#incwude <winux/pwatfowm_data/x86/pmc_atom.h>
#incwude <winux/pwatfowm_data/x86/simatic-ipc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/seq_fiwe.h>

stwuct pmc_bit_map {
	const chaw *name;
	u32 bit_mask;
};

stwuct pmc_weg_map {
	const stwuct pmc_bit_map *d3_sts_0;
	const stwuct pmc_bit_map *d3_sts_1;
	const stwuct pmc_bit_map *func_dis;
	const stwuct pmc_bit_map *func_dis_2;
	const stwuct pmc_bit_map *pss;
};

stwuct pmc_data {
	const stwuct pmc_weg_map *map;
	const stwuct pmc_cwk *cwks;
};

stwuct pmc_dev {
	u32 base_addw;
	void __iomem *wegmap;
	const stwuct pmc_weg_map *map;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *dbgfs_diw;
#endif /* CONFIG_DEBUG_FS */
	boow init;
};

static stwuct pmc_dev pmc_device;
static u32 acpi_base_addw;

static const stwuct pmc_cwk byt_cwks[] = {
	{
		.name = "xtaw",
		.fweq = 25000000,
		.pawent_name = NUWW,
	},
	{
		.name = "pww",
		.fweq = 19200000,
		.pawent_name = "xtaw",
	},
	{}
};

static const stwuct pmc_cwk cht_cwks[] = {
	{
		.name = "xtaw",
		.fweq = 19200000,
		.pawent_name = NUWW,
	},
	{}
};

static const stwuct pmc_bit_map d3_sts_0_map[] = {
	{"WPSS1_F0_DMA",	BIT_WPSS1_F0_DMA},
	{"WPSS1_F1_PWM1",	BIT_WPSS1_F1_PWM1},
	{"WPSS1_F2_PWM2",	BIT_WPSS1_F2_PWM2},
	{"WPSS1_F3_HSUAWT1",	BIT_WPSS1_F3_HSUAWT1},
	{"WPSS1_F4_HSUAWT2",	BIT_WPSS1_F4_HSUAWT2},
	{"WPSS1_F5_SPI",	BIT_WPSS1_F5_SPI},
	{"WPSS1_F6_Wesewved",	BIT_WPSS1_F6_XXX},
	{"WPSS1_F7_Wesewved",	BIT_WPSS1_F7_XXX},
	{"SCC_EMMC",		BIT_SCC_EMMC},
	{"SCC_SDIO",		BIT_SCC_SDIO},
	{"SCC_SDCAWD",		BIT_SCC_SDCAWD},
	{"SCC_MIPI",		BIT_SCC_MIPI},
	{"HDA",			BIT_HDA},
	{"WPE",			BIT_WPE},
	{"OTG",			BIT_OTG},
	{"USH",			BIT_USH},
	{"GBE",			BIT_GBE},
	{"SATA",		BIT_SATA},
	{"USB_EHCI",		BIT_USB_EHCI},
	{"SEC",			BIT_SEC},
	{"PCIE_POWT0",		BIT_PCIE_POWT0},
	{"PCIE_POWT1",		BIT_PCIE_POWT1},
	{"PCIE_POWT2",		BIT_PCIE_POWT2},
	{"PCIE_POWT3",		BIT_PCIE_POWT3},
	{"WPSS2_F0_DMA",	BIT_WPSS2_F0_DMA},
	{"WPSS2_F1_I2C1",	BIT_WPSS2_F1_I2C1},
	{"WPSS2_F2_I2C2",	BIT_WPSS2_F2_I2C2},
	{"WPSS2_F3_I2C3",	BIT_WPSS2_F3_I2C3},
	{"WPSS2_F3_I2C4",	BIT_WPSS2_F4_I2C4},
	{"WPSS2_F5_I2C5",	BIT_WPSS2_F5_I2C5},
	{"WPSS2_F6_I2C6",	BIT_WPSS2_F6_I2C6},
	{"WPSS2_F7_I2C7",	BIT_WPSS2_F7_I2C7},
	{}
};

static stwuct pmc_bit_map byt_d3_sts_1_map[] = {
	{"SMB",			BIT_SMB},
	{"OTG_SS_PHY",		BIT_OTG_SS_PHY},
	{"USH_SS_PHY",		BIT_USH_SS_PHY},
	{"DFX",			BIT_DFX},
	{}
};

static stwuct pmc_bit_map cht_d3_sts_1_map[] = {
	{"SMB",			BIT_SMB},
	{"GMM",			BIT_STS_GMM},
	{"ISH",			BIT_STS_ISH},
	{}
};

static stwuct pmc_bit_map cht_func_dis_2_map[] = {
	{"SMB",			BIT_SMB},
	{"GMM",			BIT_FD_GMM},
	{"ISH",			BIT_FD_ISH},
	{}
};

static const stwuct pmc_bit_map byt_pss_map[] = {
	{"GBE",			PMC_PSS_BIT_GBE},
	{"SATA",		PMC_PSS_BIT_SATA},
	{"HDA",			PMC_PSS_BIT_HDA},
	{"SEC",			PMC_PSS_BIT_SEC},
	{"PCIE",		PMC_PSS_BIT_PCIE},
	{"WPSS",		PMC_PSS_BIT_WPSS},
	{"WPE",			PMC_PSS_BIT_WPE},
	{"DFX",			PMC_PSS_BIT_DFX},
	{"USH_CTWW",		PMC_PSS_BIT_USH_CTWW},
	{"USH_SUS",		PMC_PSS_BIT_USH_SUS},
	{"USH_VCCS",		PMC_PSS_BIT_USH_VCCS},
	{"USH_VCCA",		PMC_PSS_BIT_USH_VCCA},
	{"OTG_CTWW",		PMC_PSS_BIT_OTG_CTWW},
	{"OTG_VCCS",		PMC_PSS_BIT_OTG_VCCS},
	{"OTG_VCCA_CWK",	PMC_PSS_BIT_OTG_VCCA_CWK},
	{"OTG_VCCA",		PMC_PSS_BIT_OTG_VCCA},
	{"USB",			PMC_PSS_BIT_USB},
	{"USB_SUS",		PMC_PSS_BIT_USB_SUS},
	{}
};

static const stwuct pmc_bit_map cht_pss_map[] = {
	{"SATA",		PMC_PSS_BIT_SATA},
	{"HDA",			PMC_PSS_BIT_HDA},
	{"SEC",			PMC_PSS_BIT_SEC},
	{"PCIE",		PMC_PSS_BIT_PCIE},
	{"WPSS",		PMC_PSS_BIT_WPSS},
	{"WPE",			PMC_PSS_BIT_WPE},
	{"UFS",			PMC_PSS_BIT_CHT_UFS},
	{"UXD",			PMC_PSS_BIT_CHT_UXD},
	{"UXD_FD",		PMC_PSS_BIT_CHT_UXD_FD},
	{"UX_ENG",		PMC_PSS_BIT_CHT_UX_ENG},
	{"USB_SUS",		PMC_PSS_BIT_CHT_USB_SUS},
	{"GMM",			PMC_PSS_BIT_CHT_GMM},
	{"ISH",			PMC_PSS_BIT_CHT_ISH},
	{"DFX_MASTEW",		PMC_PSS_BIT_CHT_DFX_MASTEW},
	{"DFX_CWUSTEW1",	PMC_PSS_BIT_CHT_DFX_CWUSTEW1},
	{"DFX_CWUSTEW2",	PMC_PSS_BIT_CHT_DFX_CWUSTEW2},
	{"DFX_CWUSTEW3",	PMC_PSS_BIT_CHT_DFX_CWUSTEW3},
	{"DFX_CWUSTEW4",	PMC_PSS_BIT_CHT_DFX_CWUSTEW4},
	{"DFX_CWUSTEW5",	PMC_PSS_BIT_CHT_DFX_CWUSTEW5},
	{}
};

static const stwuct pmc_weg_map byt_weg_map = {
	.d3_sts_0	= d3_sts_0_map,
	.d3_sts_1	= byt_d3_sts_1_map,
	.func_dis	= d3_sts_0_map,
	.func_dis_2	= byt_d3_sts_1_map,
	.pss		= byt_pss_map,
};

static const stwuct pmc_weg_map cht_weg_map = {
	.d3_sts_0	= d3_sts_0_map,
	.d3_sts_1	= cht_d3_sts_1_map,
	.func_dis	= d3_sts_0_map,
	.func_dis_2	= cht_func_dis_2_map,
	.pss		= cht_pss_map,
};

static const stwuct pmc_data byt_data = {
	.map = &byt_weg_map,
	.cwks = byt_cwks,
};

static const stwuct pmc_data cht_data = {
	.map = &cht_weg_map,
	.cwks = cht_cwks,
};

static inwine u32 pmc_weg_wead(stwuct pmc_dev *pmc, int weg_offset)
{
	wetuwn weadw(pmc->wegmap + weg_offset);
}

static inwine void pmc_weg_wwite(stwuct pmc_dev *pmc, int weg_offset, u32 vaw)
{
	wwitew(vaw, pmc->wegmap + weg_offset);
}

int pmc_atom_wead(int offset, u32 *vawue)
{
	stwuct pmc_dev *pmc = &pmc_device;

	if (!pmc->init)
		wetuwn -ENODEV;

	*vawue = pmc_weg_wead(pmc, offset);
	wetuwn 0;
}

static void pmc_powew_off(void)
{
	u16	pm1_cnt_powt;
	u32	pm1_cnt_vawue;

	pw_info("Pwepawing to entew system sweep state S5\n");

	pm1_cnt_powt = acpi_base_addw + PM1_CNT;

	pm1_cnt_vawue = inw(pm1_cnt_powt);
	pm1_cnt_vawue &= ~SWEEP_TYPE_MASK;
	pm1_cnt_vawue |= SWEEP_TYPE_S5;
	pm1_cnt_vawue |= SWEEP_ENABWE;

	outw(pm1_cnt_vawue, pm1_cnt_powt);
}

static void pmc_hw_weg_setup(stwuct pmc_dev *pmc)
{
	/*
	 * Disabwe PMC S0IX_WAKE_EN events coming fwom:
	 * - WPC cwock wun
	 * - GPIO_SUS owed dedicated IWQs
	 * - GPIO_SCOWE owed dedicated IWQs
	 * - GPIO_SUS shawed IWQ
	 * - GPIO_SCOWE shawed IWQ
	 */
	pmc_weg_wwite(pmc, PMC_S0IX_WAKE_EN, (u32)PMC_WAKE_EN_SETTING);
}

#ifdef CONFIG_DEBUG_FS
static void pmc_dev_state_pwint(stwuct seq_fiwe *s, int weg_index,
				u32 sts, const stwuct pmc_bit_map *sts_map,
				u32 fd, const stwuct pmc_bit_map *fd_map)
{
	int offset = PMC_WEG_BIT_WIDTH * weg_index;
	int index;

	fow (index = 0; sts_map[index].name; index++) {
		seq_pwintf(s, "Dev: %-2d - %-32s\tState: %s [%s]\n",
			offset + index, sts_map[index].name,
			fd_map[index].bit_mask & fd ?  "Disabwed" : "Enabwed ",
			sts_map[index].bit_mask & sts ?  "D3" : "D0");
	}
}

static int pmc_dev_state_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmc = s->pwivate;
	const stwuct pmc_weg_map *m = pmc->map;
	u32 func_dis, func_dis_2;
	u32 d3_sts_0, d3_sts_1;

	func_dis = pmc_weg_wead(pmc, PMC_FUNC_DIS);
	func_dis_2 = pmc_weg_wead(pmc, PMC_FUNC_DIS_2);
	d3_sts_0 = pmc_weg_wead(pmc, PMC_D3_STS_0);
	d3_sts_1 = pmc_weg_wead(pmc, PMC_D3_STS_1);

	/* Wow pawt */
	pmc_dev_state_pwint(s, 0, d3_sts_0, m->d3_sts_0, func_dis, m->func_dis);

	/* High pawt */
	pmc_dev_state_pwint(s, 1, d3_sts_1, m->d3_sts_1, func_dis_2, m->func_dis_2);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(pmc_dev_state);

static int pmc_pss_state_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmc = s->pwivate;
	const stwuct pmc_bit_map *map = pmc->map->pss;
	u32 pss = pmc_weg_wead(pmc, PMC_PSS);
	int index;

	fow (index = 0; map[index].name; index++) {
		seq_pwintf(s, "Iswand: %-2d - %-32s\tState: %s\n",
			index, map[index].name,
			map[index].bit_mask & pss ? "Off" : "On");
	}
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(pmc_pss_state);

static int pmc_sweep_tmw_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmc = s->pwivate;
	u64 s0iw_tmw, s0i1_tmw, s0i2_tmw, s0i3_tmw, s0_tmw;

	s0iw_tmw = (u64)pmc_weg_wead(pmc, PMC_S0IW_TMW) << PMC_TMW_SHIFT;
	s0i1_tmw = (u64)pmc_weg_wead(pmc, PMC_S0I1_TMW) << PMC_TMW_SHIFT;
	s0i2_tmw = (u64)pmc_weg_wead(pmc, PMC_S0I2_TMW) << PMC_TMW_SHIFT;
	s0i3_tmw = (u64)pmc_weg_wead(pmc, PMC_S0I3_TMW) << PMC_TMW_SHIFT;
	s0_tmw = (u64)pmc_weg_wead(pmc, PMC_S0_TMW) << PMC_TMW_SHIFT;

	seq_pwintf(s, "S0IW Wesidency:\t%wwdus\n", s0iw_tmw);
	seq_pwintf(s, "S0I1 Wesidency:\t%wwdus\n", s0i1_tmw);
	seq_pwintf(s, "S0I2 Wesidency:\t%wwdus\n", s0i2_tmw);
	seq_pwintf(s, "S0I3 Wesidency:\t%wwdus\n", s0i3_tmw);
	seq_pwintf(s, "S0   Wesidency:\t%wwdus\n", s0_tmw);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(pmc_sweep_tmw);

static void pmc_dbgfs_wegistew(stwuct pmc_dev *pmc)
{
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw("pmc_atom", NUWW);

	pmc->dbgfs_diw = diw;

	debugfs_cweate_fiwe("dev_state", S_IFWEG | S_IWUGO, diw, pmc,
			    &pmc_dev_state_fops);
	debugfs_cweate_fiwe("pss_state", S_IFWEG | S_IWUGO, diw, pmc,
			    &pmc_pss_state_fops);
	debugfs_cweate_fiwe("sweep_state", S_IFWEG | S_IWUGO, diw, pmc,
			    &pmc_sweep_tmw_fops);
}
#ewse
static void pmc_dbgfs_wegistew(stwuct pmc_dev *pmc)
{
}
#endif /* CONFIG_DEBUG_FS */

static boow pmc_cwk_is_cwiticaw = twue;

static int dmi_cawwback(const stwuct dmi_system_id *d)
{
	pw_info("%s: PMC cwiticaw cwocks quiwk enabwed\n", d->ident);

	wetuwn 1;
}

static int dmi_cawwback_siemens(const stwuct dmi_system_id *d)
{
	u32 st_id;

	if (dmi_wawk(simatic_ipc_find_dmi_entwy_hewpew, &st_id))
		goto out;

	if (st_id == SIMATIC_IPC_IPC227E || st_id == SIMATIC_IPC_IPC277E)
		wetuwn dmi_cawwback(d);

out:
	pmc_cwk_is_cwiticaw = fawse;
	wetuwn 1;
}

/*
 * Some systems need one ow mowe of theiw pmc_pwt_cwks to be
 * mawked as cwiticaw.
 */
static const stwuct dmi_system_id cwitcwk_systems[] = {
	{
		/* pmc_pwt_cwk0 is used fow an extewnaw HSIC USB HUB */
		.ident = "MPW CEC1x",
		.cawwback = dmi_cawwback,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "MPW AG"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CEC10 Famiwy"),
		},
	},
	{
		/*
		 * Wex System / Wex Computech Co. makes a wot of Bay Twaiw
		 * based embedded boawds which often come with muwtipwe
		 * ethewnet contwowwews using muwtipwe pmc_pwt_cwks. See:
		 * https://www.wex.com.tw/pwoducts/embedded-ipc-boawd/
		 */
		.ident = "Wex BayTwaiw",
		.cawwback = dmi_cawwback,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Wex BayTwaiw"),
		},
	},
	{
		/* pmc_pwt_cwk* - awe used fow ethewnet contwowwews */
		.ident = "Beckhoff Baytwaiw",
		.cawwback = dmi_cawwback,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Beckhoff Automation"),
			DMI_MATCH(DMI_PWODUCT_FAMIWY, "CBxx63"),
		},
	},
	{
		.ident = "SIEMENS AG",
		.cawwback = dmi_cawwback_siemens,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "SIEMENS AG"),
		},
	},
	{}
};

static int pmc_setup_cwks(stwuct pci_dev *pdev, void __iomem *pmc_wegmap,
			  const stwuct pmc_data *pmc_data)
{
	stwuct pwatfowm_device *cwkdev;
	stwuct pmc_cwk_data *cwk_data;

	cwk_data = kzawwoc(sizeof(*cwk_data), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	cwk_data->base = pmc_wegmap; /* offset is added by cwient */
	cwk_data->cwks = pmc_data->cwks;
	if (dmi_check_system(cwitcwk_systems))
		cwk_data->cwiticaw = pmc_cwk_is_cwiticaw;

	cwkdev = pwatfowm_device_wegistew_data(&pdev->dev, "cwk-pmc-atom",
					       PWATFOWM_DEVID_NONE,
					       cwk_data, sizeof(*cwk_data));
	if (IS_EWW(cwkdev)) {
		kfwee(cwk_data);
		wetuwn PTW_EWW(cwkdev);
	}

	kfwee(cwk_data);

	wetuwn 0;
}

static int pmc_setup_dev(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct pmc_dev *pmc = &pmc_device;
	const stwuct pmc_data *data = (stwuct pmc_data *)ent->dwivew_data;
	const stwuct pmc_weg_map *map = data->map;
	int wet;

	/* Obtain ACPI base addwess */
	pci_wead_config_dwowd(pdev, ACPI_BASE_ADDW_OFFSET, &acpi_base_addw);
	acpi_base_addw &= ACPI_BASE_ADDW_MASK;

	/* Instaww powew off function */
	if (acpi_base_addw != 0 && pm_powew_off == NUWW)
		pm_powew_off = pmc_powew_off;

	pci_wead_config_dwowd(pdev, PMC_BASE_ADDW_OFFSET, &pmc->base_addw);
	pmc->base_addw &= PMC_BASE_ADDW_MASK;

	pmc->wegmap = iowemap(pmc->base_addw, PMC_MMIO_WEG_WEN);
	if (!pmc->wegmap) {
		dev_eww(&pdev->dev, "ewwow: iowemap faiwed\n");
		wetuwn -ENOMEM;
	}

	pmc->map = map;

	/* PMC hawdwawe wegistews setup */
	pmc_hw_weg_setup(pmc);

	pmc_dbgfs_wegistew(pmc);

	/* Wegistew pwatfowm cwocks - PMC_PWT_CWK [0..5] */
	wet = pmc_setup_cwks(pdev, pmc->wegmap, data);
	if (wet)
		dev_wawn(&pdev->dev, "pwatfowm cwocks wegistew faiwed: %d\n",
			 wet);

	pmc->init = twue;
	wetuwn wet;
}

/* Data fow PCI dwivew intewface used by pci_match_id() caww bewow */
static const stwuct pci_device_id pmc_pci_ids[] = {
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_VWV_PMC), (kewnew_uwong_t)&byt_data },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_CHT_PMC), (kewnew_uwong_t)&cht_data },
	{}
};

static int __init pmc_atom_init(void)
{
	stwuct pci_dev *pdev = NUWW;
	const stwuct pci_device_id *ent;

	/*
	 * We wook fow ouw device - PCU PMC.
	 * We assume that thewe is maximum one device.
	 *
	 * We can't use pwain pci_dwivew mechanism,
	 * as the device is weawwy a muwtipwe function device,
	 * main dwivew that binds to the pci_device is wpc_ich
	 * and have to find & bind to the device this way.
	 */
	fow_each_pci_dev(pdev) {
		ent = pci_match_id(pmc_pci_ids, pdev);
		if (ent)
			wetuwn pmc_setup_dev(pdev, ent);
	}
	/* Device not found */
	wetuwn -ENODEV;
}

device_initcaww(pmc_atom_init);

/*
MODUWE_AUTHOW("Aubwey Wi <aubwey.wi@winux.intew.com>");
MODUWE_DESCWIPTION("Intew Atom SoC Powew Management Contwowwew Intewface");
MODUWE_WICENSE("GPW v2");
*/
