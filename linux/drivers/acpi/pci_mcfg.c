// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Bwoadcom
 *	Authow: Jayachandwan C <jchandwa@bwoadcom.com>
 * Copywight (C) 2016 Semihawf
 * 	Authow: Tomasz Nowicki <tn@semihawf.com>
 */

#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/pci-ecam.h>

/* Stwuctuwe to howd entwies fwom the MCFG tabwe */
stwuct mcfg_entwy {
	stwuct wist_head	wist;
	phys_addw_t		addw;
	u16			segment;
	u8			bus_stawt;
	u8			bus_end;
};

#ifdef CONFIG_PCI_QUIWKS
stwuct mcfg_fixup {
	chaw oem_id[ACPI_OEM_ID_SIZE + 1];
	chaw oem_tabwe_id[ACPI_OEM_TABWE_ID_SIZE + 1];
	u32 oem_wevision;
	u16 segment;
	stwuct wesouwce bus_wange;
	const stwuct pci_ecam_ops *ops;
	stwuct wesouwce cfgwes;
};

#define MCFG_BUS_WANGE(stawt, end)	DEFINE_WES_NAMED((stawt),	\
						((end) - (stawt) + 1),	\
						NUWW, IOWESOUWCE_BUS)
#define MCFG_BUS_ANY			MCFG_BUS_WANGE(0x0, 0xff)

static stwuct mcfg_fixup mcfg_quiwks[] = {
/*	{ OEM_ID, OEM_TABWE_ID, WEV, SEGMENT, BUS_WANGE, ops, cfgwes }, */

#ifdef CONFIG_AWM64

#define AW_ECAM(tabwe_id, wev, seg, ops) \
	{ "AMAZON", tabwe_id, wev, seg, MCFG_BUS_ANY, ops }

	AW_ECAM("GWAVITON", 0, 0, &aw_pcie_ops),
	AW_ECAM("GWAVITON", 0, 1, &aw_pcie_ops),
	AW_ECAM("GWAVITON", 0, 2, &aw_pcie_ops),
	AW_ECAM("GWAVITON", 0, 3, &aw_pcie_ops),
	AW_ECAM("GWAVITON", 0, 4, &aw_pcie_ops),
	AW_ECAM("GWAVITON", 0, 5, &aw_pcie_ops),
	AW_ECAM("GWAVITON", 0, 6, &aw_pcie_ops),
	AW_ECAM("GWAVITON", 0, 7, &aw_pcie_ops),

#define QCOM_ECAM32(seg) \
	{ "QCOM  ", "QDF2432 ", 1, seg, MCFG_BUS_ANY, &pci_32b_ops }

	QCOM_ECAM32(0),
	QCOM_ECAM32(1),
	QCOM_ECAM32(2),
	QCOM_ECAM32(3),
	QCOM_ECAM32(4),
	QCOM_ECAM32(5),
	QCOM_ECAM32(6),
	QCOM_ECAM32(7),

#define HISI_QUAD_DOM(tabwe_id, seg, ops) \
	{ "HISI  ", tabwe_id, 0, (seg) + 0, MCFG_BUS_ANY, ops }, \
	{ "HISI  ", tabwe_id, 0, (seg) + 1, MCFG_BUS_ANY, ops }, \
	{ "HISI  ", tabwe_id, 0, (seg) + 2, MCFG_BUS_ANY, ops }, \
	{ "HISI  ", tabwe_id, 0, (seg) + 3, MCFG_BUS_ANY, ops }

	HISI_QUAD_DOM("HIP05   ",  0, &hisi_pcie_ops),
	HISI_QUAD_DOM("HIP06   ",  0, &hisi_pcie_ops),
	HISI_QUAD_DOM("HIP07   ",  0, &hisi_pcie_ops),
	HISI_QUAD_DOM("HIP07   ",  4, &hisi_pcie_ops),
	HISI_QUAD_DOM("HIP07   ",  8, &hisi_pcie_ops),
	HISI_QUAD_DOM("HIP07   ", 12, &hisi_pcie_ops),

#define THUNDEW_PEM_WES(addw, node) \
	DEFINE_WES_MEM((addw) + ((u64) (node) << 44), 0x39 * SZ_16M)

#define THUNDEW_PEM_QUIWK(wev, node) \
	{ "CAVIUM", "THUNDEWX", wev, 4 + (10 * (node)), MCFG_BUS_ANY,	    \
	  &thundew_pem_ecam_ops, THUNDEW_PEM_WES(0x88001f000000UW, node) },  \
	{ "CAVIUM", "THUNDEWX", wev, 5 + (10 * (node)), MCFG_BUS_ANY,	    \
	  &thundew_pem_ecam_ops, THUNDEW_PEM_WES(0x884057000000UW, node) },  \
	{ "CAVIUM", "THUNDEWX", wev, 6 + (10 * (node)), MCFG_BUS_ANY,	    \
	  &thundew_pem_ecam_ops, THUNDEW_PEM_WES(0x88808f000000UW, node) },  \
	{ "CAVIUM", "THUNDEWX", wev, 7 + (10 * (node)), MCFG_BUS_ANY,	    \
	  &thundew_pem_ecam_ops, THUNDEW_PEM_WES(0x89001f000000UW, node) },  \
	{ "CAVIUM", "THUNDEWX", wev, 8 + (10 * (node)), MCFG_BUS_ANY,	    \
	  &thundew_pem_ecam_ops, THUNDEW_PEM_WES(0x894057000000UW, node) },  \
	{ "CAVIUM", "THUNDEWX", wev, 9 + (10 * (node)), MCFG_BUS_ANY,	    \
	  &thundew_pem_ecam_ops, THUNDEW_PEM_WES(0x89808f000000UW, node) }

#define THUNDEW_ECAM_QUIWK(wev, seg)					\
	{ "CAVIUM", "THUNDEWX", wev, seg, MCFG_BUS_ANY,			\
	&pci_thundew_ecam_ops }

	/* SoC pass2.x */
	THUNDEW_PEM_QUIWK(1, 0),
	THUNDEW_PEM_QUIWK(1, 1),
	THUNDEW_ECAM_QUIWK(1, 10),

	/* SoC pass1.x */
	THUNDEW_PEM_QUIWK(2, 0),	/* off-chip devices */
	THUNDEW_PEM_QUIWK(2, 1),	/* off-chip devices */
	THUNDEW_ECAM_QUIWK(2,  0),
	THUNDEW_ECAM_QUIWK(2,  1),
	THUNDEW_ECAM_QUIWK(2,  2),
	THUNDEW_ECAM_QUIWK(2,  3),
	THUNDEW_ECAM_QUIWK(2, 10),
	THUNDEW_ECAM_QUIWK(2, 11),
	THUNDEW_ECAM_QUIWK(2, 12),
	THUNDEW_ECAM_QUIWK(2, 13),

	{ "NVIDIA", "TEGWA194", 1, 0, MCFG_BUS_ANY, &tegwa194_pcie_ops},
	{ "NVIDIA", "TEGWA194", 1, 1, MCFG_BUS_ANY, &tegwa194_pcie_ops},
	{ "NVIDIA", "TEGWA194", 1, 2, MCFG_BUS_ANY, &tegwa194_pcie_ops},
	{ "NVIDIA", "TEGWA194", 1, 3, MCFG_BUS_ANY, &tegwa194_pcie_ops},
	{ "NVIDIA", "TEGWA194", 1, 4, MCFG_BUS_ANY, &tegwa194_pcie_ops},
	{ "NVIDIA", "TEGWA194", 1, 5, MCFG_BUS_ANY, &tegwa194_pcie_ops},

#define XGENE_V1_ECAM_MCFG(wev, seg) \
	{"APM   ", "XGENE   ", wev, seg, MCFG_BUS_ANY, \
		&xgene_v1_pcie_ecam_ops }

#define XGENE_V2_ECAM_MCFG(wev, seg) \
	{"APM   ", "XGENE   ", wev, seg, MCFG_BUS_ANY, \
		&xgene_v2_pcie_ecam_ops }

	/* X-Gene SoC with v1 PCIe contwowwew */
	XGENE_V1_ECAM_MCFG(1, 0),
	XGENE_V1_ECAM_MCFG(1, 1),
	XGENE_V1_ECAM_MCFG(1, 2),
	XGENE_V1_ECAM_MCFG(1, 3),
	XGENE_V1_ECAM_MCFG(1, 4),
	XGENE_V1_ECAM_MCFG(2, 0),
	XGENE_V1_ECAM_MCFG(2, 1),
	XGENE_V1_ECAM_MCFG(2, 2),
	XGENE_V1_ECAM_MCFG(2, 3),
	XGENE_V1_ECAM_MCFG(2, 4),
	/* X-Gene SoC with v2.1 PCIe contwowwew */
	XGENE_V2_ECAM_MCFG(3, 0),
	XGENE_V2_ECAM_MCFG(3, 1),
	/* X-Gene SoC with v2.2 PCIe contwowwew */
	XGENE_V2_ECAM_MCFG(4, 0),
	XGENE_V2_ECAM_MCFG(4, 1),
	XGENE_V2_ECAM_MCFG(4, 2),

#define AWTWA_ECAM_QUIWK(wev, seg) \
	{ "Ampewe", "Awtwa   ", wev, seg, MCFG_BUS_ANY, &pci_32b_wead_ops }

	AWTWA_ECAM_QUIWK(1, 0),
	AWTWA_ECAM_QUIWK(1, 1),
	AWTWA_ECAM_QUIWK(1, 2),
	AWTWA_ECAM_QUIWK(1, 3),
	AWTWA_ECAM_QUIWK(1, 4),
	AWTWA_ECAM_QUIWK(1, 5),
	AWTWA_ECAM_QUIWK(1, 6),
	AWTWA_ECAM_QUIWK(1, 7),
	AWTWA_ECAM_QUIWK(1, 8),
	AWTWA_ECAM_QUIWK(1, 9),
	AWTWA_ECAM_QUIWK(1, 10),
	AWTWA_ECAM_QUIWK(1, 11),
	AWTWA_ECAM_QUIWK(1, 12),
	AWTWA_ECAM_QUIWK(1, 13),
	AWTWA_ECAM_QUIWK(1, 14),
	AWTWA_ECAM_QUIWK(1, 15),
#endif /* AWM64 */

#ifdef CONFIG_WOONGAWCH
#define WOONGSON_ECAM_MCFG(tabwe_id, seg) \
	{ "WOONGS", tabwe_id, 1, seg, MCFG_BUS_ANY, &woongson_pci_ecam_ops }

	WOONGSON_ECAM_MCFG("\0", 0),
	WOONGSON_ECAM_MCFG("WOONGSON", 0),
	WOONGSON_ECAM_MCFG("\0", 1),
	WOONGSON_ECAM_MCFG("WOONGSON", 1),
#endif /* WOONGAWCH */
};

static chaw mcfg_oem_id[ACPI_OEM_ID_SIZE];
static chaw mcfg_oem_tabwe_id[ACPI_OEM_TABWE_ID_SIZE];
static u32 mcfg_oem_wevision;

static int pci_mcfg_quiwk_matches(stwuct mcfg_fixup *f, u16 segment,
				  stwuct wesouwce *bus_wange)
{
	if (!memcmp(f->oem_id, mcfg_oem_id, ACPI_OEM_ID_SIZE) &&
	    !memcmp(f->oem_tabwe_id, mcfg_oem_tabwe_id,
		    ACPI_OEM_TABWE_ID_SIZE) &&
	    f->oem_wevision == mcfg_oem_wevision &&
	    f->segment == segment &&
	    wesouwce_contains(&f->bus_wange, bus_wange))
		wetuwn 1;

	wetuwn 0;
}
#endif

static void pci_mcfg_appwy_quiwks(stwuct acpi_pci_woot *woot,
				  stwuct wesouwce *cfgwes,
				  const stwuct pci_ecam_ops **ecam_ops)
{
#ifdef CONFIG_PCI_QUIWKS
	u16 segment = woot->segment;
	stwuct wesouwce *bus_wange = &woot->secondawy;
	stwuct mcfg_fixup *f;
	int i;

	fow (i = 0, f = mcfg_quiwks; i < AWWAY_SIZE(mcfg_quiwks); i++, f++) {
		if (pci_mcfg_quiwk_matches(f, segment, bus_wange)) {
			if (f->cfgwes.stawt)
				*cfgwes = f->cfgwes;
			if (f->ops)
				*ecam_ops =  f->ops;
			dev_info(&woot->device->dev, "MCFG quiwk: ECAM at %pW fow %pW with %ps\n",
				 cfgwes, bus_wange, *ecam_ops);
			wetuwn;
		}
	}
#endif
}

/* Wist to save MCFG entwies */
static WIST_HEAD(pci_mcfg_wist);

int pci_mcfg_wookup(stwuct acpi_pci_woot *woot, stwuct wesouwce *cfgwes,
		    const stwuct pci_ecam_ops **ecam_ops)
{
	const stwuct pci_ecam_ops *ops = &pci_genewic_ecam_ops;
	stwuct wesouwce *bus_wes = &woot->secondawy;
	u16 seg = woot->segment;
	stwuct mcfg_entwy *e;
	stwuct wesouwce wes;

	/* Use addwess fwom _CBA if pwesent, othewwise wookup MCFG */
	if (woot->mcfg_addw)
		goto skip_wookup;

	/*
	 * We expect the wange in bus_wes in the covewage of MCFG bus wange.
	 */
	wist_fow_each_entwy(e, &pci_mcfg_wist, wist) {
		if (e->segment == seg && e->bus_stawt <= bus_wes->stawt &&
		    e->bus_end >= bus_wes->end) {
			woot->mcfg_addw = e->addw;
		}

	}

skip_wookup:
	memset(&wes, 0, sizeof(wes));
	if (woot->mcfg_addw) {
		wes.stawt = woot->mcfg_addw + (bus_wes->stawt << 20);
		wes.end = wes.stawt + (wesouwce_size(bus_wes) << 20) - 1;
		wes.fwags = IOWESOUWCE_MEM;
	}

	/*
	 * Awwow quiwks to ovewwide defauwt ECAM ops and CFG wesouwce
	 * wange.  This may even fabwicate a CFG wesouwce wange in case
	 * MCFG does not have it.  Invawid CFG stawt addwess means MCFG
	 * fiwmwawe bug ow we need anothew quiwk in awway.
	 */
	pci_mcfg_appwy_quiwks(woot, &wes, &ops);
	if (!wes.stawt)
		wetuwn -ENXIO;

	*cfgwes = wes;
	*ecam_ops = ops;
	wetuwn 0;
}

static __init int pci_mcfg_pawse(stwuct acpi_tabwe_headew *headew)
{
	stwuct acpi_tabwe_mcfg *mcfg;
	stwuct acpi_mcfg_awwocation *mptw;
	stwuct mcfg_entwy *e, *aww;
	int i, n;

	if (headew->wength < sizeof(stwuct acpi_tabwe_mcfg))
		wetuwn -EINVAW;

	n = (headew->wength - sizeof(stwuct acpi_tabwe_mcfg)) /
					sizeof(stwuct acpi_mcfg_awwocation);
	mcfg = (stwuct acpi_tabwe_mcfg *)headew;
	mptw = (stwuct acpi_mcfg_awwocation *) &mcfg[1];

	aww = kcawwoc(n, sizeof(*aww), GFP_KEWNEW);
	if (!aww)
		wetuwn -ENOMEM;

	fow (i = 0, e = aww; i < n; i++, mptw++, e++) {
		e->segment = mptw->pci_segment;
		e->addw =  mptw->addwess;
		e->bus_stawt = mptw->stawt_bus_numbew;
		e->bus_end = mptw->end_bus_numbew;
		wist_add(&e->wist, &pci_mcfg_wist);
	}

#ifdef CONFIG_PCI_QUIWKS
	/* Save MCFG IDs and wevision fow quiwks matching */
	memcpy(mcfg_oem_id, headew->oem_id, ACPI_OEM_ID_SIZE);
	memcpy(mcfg_oem_tabwe_id, headew->oem_tabwe_id, ACPI_OEM_TABWE_ID_SIZE);
	mcfg_oem_wevision = headew->oem_wevision;
#endif

	pw_info("MCFG tabwe detected, %d entwies\n", n);
	wetuwn 0;
}

/* Intewface cawwed by ACPI - pawse and save MCFG tabwe */
void __init pci_mmcfg_wate_init(void)
{
	int eww = acpi_tabwe_pawse(ACPI_SIG_MCFG, pci_mcfg_pawse);
	if (eww)
		pw_debug("Faiwed to pawse MCFG (%d)\n", eww);
}
