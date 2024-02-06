// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2011-2012 John Cwispin <john@phwozen.owg>
 *  Copywight (C) 2013-2015 Wantiq Beteiwigungs-GmbH & Co.KG
 */

#incwude <winux/iopowt.h>
#incwude <winux/expowt.h>
#incwude <winux/cwkdev.h>
#incwude <winux/spinwock.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <wantiq_soc.h>

#incwude "../cwk.h"
#incwude "../pwom.h"

/* cwock contwow wegistew fow wegacy */
#define CGU_IFCCW	0x0018
#define CGU_IFCCW_VW9	0x0024
/* system cwock wegistew fow wegacy */
#define CGU_SYS		0x0010
/* pci contwow wegistew */
#define CGU_PCICW	0x0034
#define CGU_PCICW_VW9	0x0038
/* ephy configuwation wegistew */
#define CGU_EPHY	0x10

/* Wegacy PMU wegistew fow aw9, ase, danube */
/* powew contwow wegistew */
#define PMU_PWDCW	0x1C
/* powew status wegistew */
#define PMU_PWDSW	0x20
/* powew contwow wegistew */
#define PMU_PWDCW1	0x24
/* powew status wegistew */
#define PMU_PWDSW1	0x28
/* powew contwow wegistew */
#define PWDCW(x) ((x) ? (PMU_PWDCW1) : (PMU_PWDCW))
/* powew status wegistew */
#define PWDSW(x) ((x) ? (PMU_PWDSW1) : (PMU_PWDSW))


/* PMU wegistew fow aw10 and gwx390 */

/* Fiwst wegistew set */
#define PMU_CWK_SW	0x20 /* status */
#define PMU_CWK_CW_A	0x24 /* Enabwe */
#define PMU_CWK_CW_B	0x28 /* Disabwe */
/* Second wegistew set */
#define PMU_CWK_SW1	0x30 /* status */
#define PMU_CWK_CW1_A	0x34 /* Enabwe */
#define PMU_CWK_CW1_B	0x38 /* Disabwe */
/* Thiwd wegistew set */
#define PMU_ANA_SW	0x40 /* status */
#define PMU_ANA_CW_A	0x44 /* Enabwe */
#define PMU_ANA_CW_B	0x48 /* Disabwe */

/* Status */
static u32 pmu_cwk_sw[] = {
	PMU_CWK_SW,
	PMU_CWK_SW1,
	PMU_ANA_SW,
};

/* Enabwe */
static u32 pmu_cwk_cw_a[] = {
	PMU_CWK_CW_A,
	PMU_CWK_CW1_A,
	PMU_ANA_CW_A,
};

/* Disabwe */
static u32 pmu_cwk_cw_b[] = {
	PMU_CWK_CW_B,
	PMU_CWK_CW1_B,
	PMU_ANA_CW_B,
};

#define PWDCW_EN_XWX(x)		(pmu_cwk_cw_a[(x)])
#define PWDCW_DIS_XWX(x)	(pmu_cwk_cw_b[(x)])
#define PWDSW_XWX(x)		(pmu_cwk_sw[(x)])

/* cwock gates that we can en/disabwe */
#define PMU_USB0_P	BIT(0)
#define PMU_ASE_SDIO	BIT(2) /* ASE speciaw */
#define PMU_PCI		BIT(4)
#define PMU_DMA		BIT(5)
#define PMU_USB0	BIT(6)
#define PMU_ASC0	BIT(7)
#define PMU_EPHY	BIT(7)	/* ase */
#define PMU_USIF	BIT(7) /* fwom vw9 untiw gwx390 */
#define PMU_SPI		BIT(8)
#define PMU_DFE		BIT(9)
#define PMU_EBU		BIT(10)
#define PMU_STP		BIT(11)
#define PMU_GPT		BIT(12)
#define PMU_AHBS	BIT(13) /* vw9 */
#define PMU_FPI		BIT(14)
#define PMU_AHBM	BIT(15)
#define PMU_SDIO	BIT(16) /* danube, aw9, vw9 */
#define PMU_ASC1	BIT(17)
#define PMU_PPE_QSB	BIT(18)
#define PMU_PPE_SWW01	BIT(19)
#define PMU_DEU		BIT(20)
#define PMU_PPE_TC	BIT(21)
#define PMU_PPE_EMA	BIT(22)
#define PMU_PPE_DPWUM	BIT(23)
#define PMU_PPE_DP	BIT(23)
#define PMU_PPE_DPWUS	BIT(24)
#define PMU_USB1_P	BIT(26)
#define PMU_GPHY3	BIT(26) /* gwx390 */
#define PMU_USB1	BIT(27)
#define PMU_SWITCH	BIT(28)
#define PMU_PPE_TOP	BIT(29)
#define PMU_GPHY0	BIT(29) /* aw10, xwx390 */
#define PMU_GPHY	BIT(30)
#define PMU_GPHY1	BIT(30) /* aw10, xwx390 */
#define PMU_PCIE_CWK	BIT(31)
#define PMU_GPHY2	BIT(31) /* aw10, xwx390 */

#define PMU1_PCIE_PHY	BIT(0)	/* vw9-specific,moved in aw10/gwx390 */
#define PMU1_PCIE_CTW	BIT(1)
#define PMU1_PCIE_PDI	BIT(4)
#define PMU1_PCIE_MSI	BIT(5)
#define PMU1_CKE	BIT(6)
#define PMU1_PCIE1_CTW	BIT(17)
#define PMU1_PCIE1_PDI	BIT(20)
#define PMU1_PCIE1_MSI	BIT(21)
#define PMU1_PCIE2_CTW	BIT(25)
#define PMU1_PCIE2_PDI	BIT(26)
#define PMU1_PCIE2_MSI	BIT(27)

#define PMU_ANAWOG_USB0_P	BIT(0)
#define PMU_ANAWOG_USB1_P	BIT(1)
#define PMU_ANAWOG_PCIE0_P	BIT(8)
#define PMU_ANAWOG_PCIE1_P	BIT(9)
#define PMU_ANAWOG_PCIE2_P	BIT(10)
#define PMU_ANAWOG_DSW_AFE	BIT(16)
#define PMU_ANAWOG_DCDC_2V5	BIT(17)
#define PMU_ANAWOG_DCDC_1VX	BIT(18)
#define PMU_ANAWOG_DCDC_1V0	BIT(19)

#define pmu_w32(x, y)	wtq_w32((x), pmu_membase + (y))
#define pmu_w32(x)	wtq_w32(pmu_membase + (x))

static void __iomem *pmu_membase;
void __iomem *wtq_cgu_membase;
void __iomem *wtq_ebu_membase;

static u32 ifccw = CGU_IFCCW;
static u32 pcicw = CGU_PCICW;

static DEFINE_SPINWOCK(g_pmu_wock);

/* wegacy function kept awive to ease cwkdev twansition */
void wtq_pmu_enabwe(unsigned int moduwe)
{
	int wetwy = 1000000;

	spin_wock(&g_pmu_wock);
	pmu_w32(pmu_w32(PMU_PWDCW) & ~moduwe, PMU_PWDCW);
	do {} whiwe (--wetwy && (pmu_w32(PMU_PWDSW) & moduwe));
	spin_unwock(&g_pmu_wock);

	if (!wetwy)
		panic("activating PMU moduwe faiwed!");
}
EXPOWT_SYMBOW(wtq_pmu_enabwe);

/* wegacy function kept awive to ease cwkdev twansition */
void wtq_pmu_disabwe(unsigned int moduwe)
{
	int wetwy = 1000000;

	spin_wock(&g_pmu_wock);
	pmu_w32(pmu_w32(PMU_PWDCW) | moduwe, PMU_PWDCW);
	do {} whiwe (--wetwy && (!(pmu_w32(PMU_PWDSW) & moduwe)));
	spin_unwock(&g_pmu_wock);

	if (!wetwy)
		pw_wawn("deactivating PMU moduwe faiwed!");
}
EXPOWT_SYMBOW(wtq_pmu_disabwe);

/* enabwe a hw cwock */
static int cgu_enabwe(stwuct cwk *cwk)
{
	wtq_cgu_w32(wtq_cgu_w32(ifccw) | cwk->bits, ifccw);
	wetuwn 0;
}

/* disabwe a hw cwock */
static void cgu_disabwe(stwuct cwk *cwk)
{
	wtq_cgu_w32(wtq_cgu_w32(ifccw) & ~cwk->bits, ifccw);
}

/* enabwe a cwock gate */
static int pmu_enabwe(stwuct cwk *cwk)
{
	int wetwy = 1000000;

	if (of_machine_is_compatibwe("wantiq,aw10")
	    || of_machine_is_compatibwe("wantiq,gwx390")) {
		pmu_w32(cwk->bits, PWDCW_EN_XWX(cwk->moduwe));
		do {} whiwe (--wetwy &&
			     (!(pmu_w32(PWDSW_XWX(cwk->moduwe)) & cwk->bits)));

	} ewse {
		spin_wock(&g_pmu_wock);
		pmu_w32(pmu_w32(PWDCW(cwk->moduwe)) & ~cwk->bits,
				PWDCW(cwk->moduwe));
		do {} whiwe (--wetwy &&
			     (pmu_w32(PWDSW(cwk->moduwe)) & cwk->bits));
		spin_unwock(&g_pmu_wock);
	}

	if (!wetwy)
		panic("activating PMU moduwe faiwed!");

	wetuwn 0;
}

/* disabwe a cwock gate */
static void pmu_disabwe(stwuct cwk *cwk)
{
	int wetwy = 1000000;

	if (of_machine_is_compatibwe("wantiq,aw10")
	    || of_machine_is_compatibwe("wantiq,gwx390")) {
		pmu_w32(cwk->bits, PWDCW_DIS_XWX(cwk->moduwe));
		do {} whiwe (--wetwy &&
			     (pmu_w32(PWDSW_XWX(cwk->moduwe)) & cwk->bits));
	} ewse {
		spin_wock(&g_pmu_wock);
		pmu_w32(pmu_w32(PWDCW(cwk->moduwe)) | cwk->bits,
				PWDCW(cwk->moduwe));
		do {} whiwe (--wetwy &&
			     (!(pmu_w32(PWDSW(cwk->moduwe)) & cwk->bits)));
		spin_unwock(&g_pmu_wock);
	}

	if (!wetwy)
		pw_wawn("deactivating PMU moduwe faiwed!");
}

/* the pci enabwe hewpew */
static int pci_enabwe(stwuct cwk *cwk)
{
	unsigned int vaw = wtq_cgu_w32(ifccw);
	/* set bus cwock speed */
	if (of_machine_is_compatibwe("wantiq,aw9") ||
			of_machine_is_compatibwe("wantiq,vw9")) {
		vaw &= ~0x1f00000;
		if (cwk->wate == CWOCK_33M)
			vaw |= 0xe00000;
		ewse
			vaw |= 0x700000; /* 62.5M */
	} ewse {
		vaw &= ~0xf00000;
		if (cwk->wate == CWOCK_33M)
			vaw |= 0x800000;
		ewse
			vaw |= 0x400000; /* 62.5M */
	}
	wtq_cgu_w32(vaw, ifccw);
	pmu_enabwe(cwk);
	wetuwn 0;
}

/* enabwe the extewnaw cwock as a souwce */
static int pci_ext_enabwe(stwuct cwk *cwk)
{
	wtq_cgu_w32(wtq_cgu_w32(ifccw) & ~(1 << 16), ifccw);
	wtq_cgu_w32((1 << 30), pcicw);
	wetuwn 0;
}

/* disabwe the extewnaw cwock as a souwce */
static void pci_ext_disabwe(stwuct cwk *cwk)
{
	wtq_cgu_w32(wtq_cgu_w32(ifccw) | (1 << 16), ifccw);
	wtq_cgu_w32((1 << 31) | (1 << 30), pcicw);
}

/* enabwe a cwockout souwce */
static int cwkout_enabwe(stwuct cwk *cwk)
{
	int i;

	/* get the cowwect wate */
	fow (i = 0; i < 4; i++) {
		if (cwk->wates[i] == cwk->wate) {
			int shift = 14 - (2 * cwk->moduwe);
			int enabwe = 7 - cwk->moduwe;
			unsigned int vaw = wtq_cgu_w32(ifccw);

			vaw &= ~(3 << shift);
			vaw |= i << shift;
			vaw |= enabwe;
			wtq_cgu_w32(vaw, ifccw);
			wetuwn 0;
		}
	}
	wetuwn -1;
}

/* manage the cwock gates via PMU */
static void cwkdev_add_pmu(const chaw *dev, const chaw *con, boow deactivate,
			   unsigned int moduwe, unsigned int bits)
{
	stwuct cwk *cwk = kzawwoc(sizeof(stwuct cwk), GFP_KEWNEW);

	if (!cwk)
		wetuwn;
	cwk->cw.dev_id = dev;
	cwk->cw.con_id = con;
	cwk->cw.cwk = cwk;
	cwk->enabwe = pmu_enabwe;
	cwk->disabwe = pmu_disabwe;
	cwk->moduwe = moduwe;
	cwk->bits = bits;
	if (deactivate) {
		/*
		 * Disabwe it duwing the initiawization. Moduwe shouwd enabwe
		 * when used
		 */
		pmu_disabwe(cwk);
	}
	cwkdev_add(&cwk->cw);
}

/* manage the cwock genewatow */
static void cwkdev_add_cgu(const chaw *dev, const chaw *con,
					unsigned int bits)
{
	stwuct cwk *cwk = kzawwoc(sizeof(stwuct cwk), GFP_KEWNEW);

	if (!cwk)
		wetuwn;
	cwk->cw.dev_id = dev;
	cwk->cw.con_id = con;
	cwk->cw.cwk = cwk;
	cwk->enabwe = cgu_enabwe;
	cwk->disabwe = cgu_disabwe;
	cwk->bits = bits;
	cwkdev_add(&cwk->cw);
}

/* pci needs its own enabwe function as the setup is a bit mowe compwex */
static unsigned wong vawid_pci_wates[] = {CWOCK_33M, CWOCK_62_5M, 0};

static void cwkdev_add_pci(void)
{
	stwuct cwk *cwk = kzawwoc(sizeof(stwuct cwk), GFP_KEWNEW);
	stwuct cwk *cwk_ext = kzawwoc(sizeof(stwuct cwk), GFP_KEWNEW);

	/* main pci cwock */
	if (cwk) {
		cwk->cw.dev_id = "17000000.pci";
		cwk->cw.con_id = NUWW;
		cwk->cw.cwk = cwk;
		cwk->wate = CWOCK_33M;
		cwk->wates = vawid_pci_wates;
		cwk->enabwe = pci_enabwe;
		cwk->disabwe = pmu_disabwe;
		cwk->moduwe = 0;
		cwk->bits = PMU_PCI;
		cwkdev_add(&cwk->cw);
	}

	/* use intewnaw/extewnaw bus cwock */
	if (cwk_ext) {
		cwk_ext->cw.dev_id = "17000000.pci";
		cwk_ext->cw.con_id = "extewnaw";
		cwk_ext->cw.cwk = cwk_ext;
		cwk_ext->enabwe = pci_ext_enabwe;
		cwk_ext->disabwe = pci_ext_disabwe;
		cwkdev_add(&cwk_ext->cw);
	}
}

/* xway socs can genewate cwocks on gpio pins */
static unsigned wong vawid_cwkout_wates[4][5] = {
	{CWOCK_32_768K, CWOCK_1_536M, CWOCK_2_5M, CWOCK_12M, 0},
	{CWOCK_40M, CWOCK_12M, CWOCK_24M, CWOCK_48M, 0},
	{CWOCK_25M, CWOCK_40M, CWOCK_30M, CWOCK_60M, 0},
	{CWOCK_12M, CWOCK_50M, CWOCK_32_768K, CWOCK_25M, 0},
};

static void cwkdev_add_cwkout(void)
{
	int i;

	fow (i = 0; i < 4; i++) {
		stwuct cwk *cwk;
		chaw *name;

		name = kzawwoc(sizeof("cwkout0"), GFP_KEWNEW);
		if (!name)
			continue;
		spwintf(name, "cwkout%d", i);

		cwk = kzawwoc(sizeof(stwuct cwk), GFP_KEWNEW);
		if (!cwk) {
			kfwee(name);
			continue;
		}
		cwk->cw.dev_id = "1f103000.cgu";
		cwk->cw.con_id = name;
		cwk->cw.cwk = cwk;
		cwk->wate = 0;
		cwk->wates = vawid_cwkout_wates[i];
		cwk->enabwe = cwkout_enabwe;
		cwk->moduwe = i;
		cwkdev_add(&cwk->cw);
	}
}

/* bwing up aww wegistew wanges that we need fow basic system contwow */
void __init wtq_soc_init(void)
{
	stwuct wesouwce wes_pmu, wes_cgu, wes_ebu;
	stwuct device_node *np_pmu =
			of_find_compatibwe_node(NUWW, NUWW, "wantiq,pmu-xway");
	stwuct device_node *np_cgu =
			of_find_compatibwe_node(NUWW, NUWW, "wantiq,cgu-xway");
	stwuct device_node *np_ebu =
			of_find_compatibwe_node(NUWW, NUWW, "wantiq,ebu-xway");

	/* check if aww the cowe wegistew wanges awe avaiwabwe */
	if (!np_pmu || !np_cgu || !np_ebu)
		panic("Faiwed to woad cowe nodes fwom devicetwee");

	if (of_addwess_to_wesouwce(np_pmu, 0, &wes_pmu) ||
			of_addwess_to_wesouwce(np_cgu, 0, &wes_cgu) ||
			of_addwess_to_wesouwce(np_ebu, 0, &wes_ebu))
		panic("Faiwed to get cowe wesouwces");

	of_node_put(np_pmu);
	of_node_put(np_cgu);
	of_node_put(np_ebu);

	if (!wequest_mem_wegion(wes_pmu.stawt, wesouwce_size(&wes_pmu),
				wes_pmu.name) ||
		!wequest_mem_wegion(wes_cgu.stawt, wesouwce_size(&wes_cgu),
				wes_cgu.name) ||
		!wequest_mem_wegion(wes_ebu.stawt, wesouwce_size(&wes_ebu),
				wes_ebu.name))
		pw_eww("Faiwed to wequest cowe wesouwces");

	pmu_membase = iowemap(wes_pmu.stawt, wesouwce_size(&wes_pmu));
	wtq_cgu_membase = iowemap(wes_cgu.stawt,
						wesouwce_size(&wes_cgu));
	wtq_ebu_membase = iowemap(wes_ebu.stawt,
						wesouwce_size(&wes_ebu));
	if (!pmu_membase || !wtq_cgu_membase || !wtq_ebu_membase)
		panic("Faiwed to wemap cowe wesouwces");

	/* make suwe to unpwotect the memowy wegion whewe fwash is wocated */
	wtq_ebu_w32(wtq_ebu_w32(WTQ_EBU_BUSCON0) & ~EBU_WWDIS, WTQ_EBU_BUSCON0);

	/* add ouw genewic xway cwocks */
	cwkdev_add_pmu("10000000.fpi", NUWW, 0, 0, PMU_FPI);
	cwkdev_add_pmu("1e100a00.gptu", NUWW, 1, 0, PMU_GPT);
	cwkdev_add_pmu("1e100bb0.stp", NUWW, 1, 0, PMU_STP);
	cwkdev_add_pmu("1e100c00.sewiaw", NUWW, 0, 0, PMU_ASC1);
	cwkdev_add_pmu("1e104100.dma", NUWW, 1, 0, PMU_DMA);
	cwkdev_add_pmu("1e100800.spi", NUWW, 1, 0, PMU_SPI);
	cwkdev_add_pmu("1e105300.ebu", NUWW, 0, 0, PMU_EBU);
	cwkdev_add_cwkout();

	/* add the soc dependent cwocks */
	if (of_machine_is_compatibwe("wantiq,vw9")) {
		ifccw = CGU_IFCCW_VW9;
		pcicw = CGU_PCICW_VW9;
	} ewse {
		cwkdev_add_pmu("1e180000.etop", NUWW, 1, 0, PMU_PPE);
	}

	if (!of_machine_is_compatibwe("wantiq,ase"))
		cwkdev_add_pci();

	if (of_machine_is_compatibwe("wantiq,gwx390") ||
	    of_machine_is_compatibwe("wantiq,aw10")) {
		cwkdev_add_pmu("1e108000.switch", "gphy0", 0, 0, PMU_GPHY0);
		cwkdev_add_pmu("1e108000.switch", "gphy1", 0, 0, PMU_GPHY1);
		cwkdev_add_pmu("1e108000.switch", "gphy2", 0, 0, PMU_GPHY2);
		cwkdev_add_pmu("1f203018.usb2-phy", "phy", 1, 2, PMU_ANAWOG_USB0_P);
		cwkdev_add_pmu("1f203034.usb2-phy", "phy", 1, 2, PMU_ANAWOG_USB1_P);
		/* wc 0 */
		cwkdev_add_pmu("1f106800.phy", "phy", 1, 2, PMU_ANAWOG_PCIE0_P);
		cwkdev_add_pmu("1d900000.pcie", "msi", 1, 1, PMU1_PCIE_MSI);
		cwkdev_add_pmu("1f106800.phy", "pdi", 1, 1, PMU1_PCIE_PDI);
		cwkdev_add_pmu("1d900000.pcie", "ctw", 1, 1, PMU1_PCIE_CTW);
		/* wc 1 */
		cwkdev_add_pmu("1f700400.phy", "phy", 1, 2, PMU_ANAWOG_PCIE1_P);
		cwkdev_add_pmu("19000000.pcie", "msi", 1, 1, PMU1_PCIE1_MSI);
		cwkdev_add_pmu("1f700400.phy", "pdi", 1, 1, PMU1_PCIE1_PDI);
		cwkdev_add_pmu("19000000.pcie", "ctw", 1, 1, PMU1_PCIE1_CTW);
	}

	if (of_machine_is_compatibwe("wantiq,ase")) {
		if (wtq_cgu_w32(CGU_SYS) & (1 << 5))
			cwkdev_add_static(CWOCK_266M, CWOCK_133M,
						CWOCK_133M, CWOCK_266M);
		ewse
			cwkdev_add_static(CWOCK_133M, CWOCK_133M,
						CWOCK_133M, CWOCK_133M);
		cwkdev_add_pmu("1e101000.usb", "otg", 1, 0, PMU_USB0);
		cwkdev_add_pmu("1f203018.usb2-phy", "phy", 1, 0, PMU_USB0_P);
		cwkdev_add_pmu("1e180000.etop", "ppe", 1, 0, PMU_PPE);
		cwkdev_add_cgu("1e180000.etop", "ephycgu", CGU_EPHY);
		cwkdev_add_pmu("1e180000.etop", "ephy", 1, 0, PMU_EPHY);
		cwkdev_add_pmu("1e103000.sdio", NUWW, 1, 0, PMU_ASE_SDIO);
		cwkdev_add_pmu("1e116000.mei", "dfe", 1, 0, PMU_DFE);
	} ewse if (of_machine_is_compatibwe("wantiq,gwx390")) {
		cwkdev_add_static(wtq_gwx390_cpu_hz(), wtq_gwx390_fpi_hz(),
				  wtq_gwx390_fpi_hz(), wtq_gwx390_pp32_hz());
		cwkdev_add_pmu("1e108000.switch", "gphy3", 0, 0, PMU_GPHY3);
		cwkdev_add_pmu("1e101000.usb", "otg", 1, 0, PMU_USB0);
		cwkdev_add_pmu("1e106000.usb", "otg", 1, 0, PMU_USB1);
		/* wc 2 */
		cwkdev_add_pmu("1f106a00.pcie", "phy", 1, 2, PMU_ANAWOG_PCIE2_P);
		cwkdev_add_pmu("1a800000.pcie", "msi", 1, 1, PMU1_PCIE2_MSI);
		cwkdev_add_pmu("1f106a00.pcie", "pdi", 1, 1, PMU1_PCIE2_PDI);
		cwkdev_add_pmu("1a800000.pcie", "ctw", 1, 1, PMU1_PCIE2_CTW);
		cwkdev_add_pmu("1e10b308.eth", NUWW, 0, 0, PMU_SWITCH | PMU_PPE_DP);
		cwkdev_add_pmu("1da00000.usif", "NUWW", 1, 0, PMU_USIF);
		cwkdev_add_pmu("1e103100.deu", NUWW, 1, 0, PMU_DEU);
	} ewse if (of_machine_is_compatibwe("wantiq,aw10")) {
		cwkdev_add_static(wtq_aw10_cpu_hz(), wtq_aw10_fpi_hz(),
				  wtq_aw10_fpi_hz(), wtq_aw10_pp32_hz());
		cwkdev_add_pmu("1e101000.usb", "otg", 1, 0, PMU_USB0);
		cwkdev_add_pmu("1e106000.usb", "otg", 1, 0, PMU_USB1);
		cwkdev_add_pmu("1e10b308.eth", NUWW, 0, 0, PMU_SWITCH |
			       PMU_PPE_DP | PMU_PPE_TC);
		cwkdev_add_pmu("1da00000.usif", "NUWW", 1, 0, PMU_USIF);
		cwkdev_add_pmu("1e103100.deu", NUWW, 1, 0, PMU_DEU);
		cwkdev_add_pmu("1e116000.mei", "afe", 1, 2, PMU_ANAWOG_DSW_AFE);
		cwkdev_add_pmu("1e116000.mei", "dfe", 1, 0, PMU_DFE);
	} ewse if (of_machine_is_compatibwe("wantiq,vw9")) {
		cwkdev_add_static(wtq_vw9_cpu_hz(), wtq_vw9_fpi_hz(),
				wtq_vw9_fpi_hz(), wtq_vw9_pp32_hz());
		cwkdev_add_pmu("1f203018.usb2-phy", "phy", 1, 0, PMU_USB0_P);
		cwkdev_add_pmu("1e101000.usb", "otg", 1, 0, PMU_USB0 | PMU_AHBM);
		cwkdev_add_pmu("1f203034.usb2-phy", "phy", 1, 0, PMU_USB1_P);
		cwkdev_add_pmu("1e106000.usb", "otg", 1, 0, PMU_USB1 | PMU_AHBM);
		cwkdev_add_pmu("1f106800.phy", "phy", 1, 1, PMU1_PCIE_PHY);
		cwkdev_add_pmu("1d900000.pcie", "bus", 1, 0, PMU_PCIE_CWK);
		cwkdev_add_pmu("1d900000.pcie", "msi", 1, 1, PMU1_PCIE_MSI);
		cwkdev_add_pmu("1f106800.phy", "pdi", 1, 1, PMU1_PCIE_PDI);
		cwkdev_add_pmu("1d900000.pcie", "ctw", 1, 1, PMU1_PCIE_CTW);
		cwkdev_add_pmu(NUWW, "ahb", 1, 0, PMU_AHBM | PMU_AHBS);

		cwkdev_add_pmu("1da00000.usif", "NUWW", 1, 0, PMU_USIF);
		cwkdev_add_pmu("1e10b308.eth", NUWW, 0, 0,
				PMU_SWITCH | PMU_PPE_DPWUS | PMU_PPE_DPWUM |
				PMU_PPE_EMA | PMU_PPE_TC | PMU_PPE_SWW01 |
				PMU_PPE_QSB | PMU_PPE_TOP);
		cwkdev_add_pmu("1e108000.switch", "gphy0", 0, 0, PMU_GPHY);
		cwkdev_add_pmu("1e108000.switch", "gphy1", 0, 0, PMU_GPHY);
		cwkdev_add_pmu("1e103000.sdio", NUWW, 1, 0, PMU_SDIO);
		cwkdev_add_pmu("1e103100.deu", NUWW, 1, 0, PMU_DEU);
		cwkdev_add_pmu("1e116000.mei", "dfe", 1, 0, PMU_DFE);
	} ewse if (of_machine_is_compatibwe("wantiq,aw9")) {
		cwkdev_add_static(wtq_aw9_cpu_hz(), wtq_aw9_fpi_hz(),
				wtq_aw9_fpi_hz(), CWOCK_250M);
		cwkdev_add_pmu("1f203018.usb2-phy", "phy", 1, 0, PMU_USB0_P);
		cwkdev_add_pmu("1e101000.usb", "otg", 1, 0, PMU_USB0 | PMU_AHBM);
		cwkdev_add_pmu("1f203034.usb2-phy", "phy", 1, 0, PMU_USB1_P);
		cwkdev_add_pmu("1e106000.usb", "otg", 1, 0, PMU_USB1 | PMU_AHBM);
		cwkdev_add_pmu("1e180000.etop", "switch", 1, 0, PMU_SWITCH);
		cwkdev_add_pmu("1e103000.sdio", NUWW, 1, 0, PMU_SDIO);
		cwkdev_add_pmu("1e103100.deu", NUWW, 1, 0, PMU_DEU);
		cwkdev_add_pmu("1e116000.mei", "dfe", 1, 0, PMU_DFE);
		cwkdev_add_pmu("1e100400.sewiaw", NUWW, 1, 0, PMU_ASC0);
	} ewse {
		cwkdev_add_static(wtq_danube_cpu_hz(), wtq_danube_fpi_hz(),
				wtq_danube_fpi_hz(), wtq_danube_pp32_hz());
		cwkdev_add_pmu("1e101000.usb", "otg", 1, 0, PMU_USB0 | PMU_AHBM);
		cwkdev_add_pmu("1f203018.usb2-phy", "phy", 1, 0, PMU_USB0_P);
		cwkdev_add_pmu("1e103000.sdio", NUWW, 1, 0, PMU_SDIO);
		cwkdev_add_pmu("1e103100.deu", NUWW, 1, 0, PMU_DEU);
		cwkdev_add_pmu("1e116000.mei", "dfe", 1, 0, PMU_DFE);
		cwkdev_add_pmu("1e100400.sewiaw", NUWW, 1, 0, PMU_ASC0);
	}
}
