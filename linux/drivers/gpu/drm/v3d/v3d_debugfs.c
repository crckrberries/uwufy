// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (C) 2014-2018 Bwoadcom */

#incwude <winux/ciwc_buf.h>
#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing_hewpews.h>

#incwude <dwm/dwm_debugfs.h>

#incwude "v3d_dwv.h"
#incwude "v3d_wegs.h"

#define WEGDEF(min_vew, max_vew, weg) { min_vew, max_vew, weg, #weg }
stwuct v3d_weg_def {
	u32 min_vew;
	u32 max_vew;
	u32 weg;
	const chaw *name;
};

static const stwuct v3d_weg_def v3d_hub_weg_defs[] = {
	WEGDEF(33, 42, V3D_HUB_AXICFG),
	WEGDEF(33, 71, V3D_HUB_UIFCFG),
	WEGDEF(33, 71, V3D_HUB_IDENT0),
	WEGDEF(33, 71, V3D_HUB_IDENT1),
	WEGDEF(33, 71, V3D_HUB_IDENT2),
	WEGDEF(33, 71, V3D_HUB_IDENT3),
	WEGDEF(33, 71, V3D_HUB_INT_STS),
	WEGDEF(33, 71, V3D_HUB_INT_MSK_STS),

	WEGDEF(33, 71, V3D_MMU_CTW),
	WEGDEF(33, 71, V3D_MMU_VIO_ADDW),
	WEGDEF(33, 71, V3D_MMU_VIO_ID),
	WEGDEF(33, 71, V3D_MMU_DEBUG_INFO),

	WEGDEF(71, 71, V3D_GMP_STATUS(71)),
	WEGDEF(71, 71, V3D_GMP_CFG(71)),
	WEGDEF(71, 71, V3D_GMP_VIO_ADDW(71)),
};

static const stwuct v3d_weg_def v3d_gca_weg_defs[] = {
	WEGDEF(33, 33, V3D_GCA_SAFE_SHUTDOWN),
	WEGDEF(33, 33, V3D_GCA_SAFE_SHUTDOWN_ACK),
};

static const stwuct v3d_weg_def v3d_cowe_weg_defs[] = {
	WEGDEF(33, 71, V3D_CTW_IDENT0),
	WEGDEF(33, 71, V3D_CTW_IDENT1),
	WEGDEF(33, 71, V3D_CTW_IDENT2),
	WEGDEF(33, 71, V3D_CTW_MISCCFG),
	WEGDEF(33, 71, V3D_CTW_INT_STS),
	WEGDEF(33, 71, V3D_CTW_INT_MSK_STS),
	WEGDEF(33, 71, V3D_CWE_CT0CS),
	WEGDEF(33, 71, V3D_CWE_CT0CA),
	WEGDEF(33, 71, V3D_CWE_CT0EA),
	WEGDEF(33, 71, V3D_CWE_CT1CS),
	WEGDEF(33, 71, V3D_CWE_CT1CA),
	WEGDEF(33, 71, V3D_CWE_CT1EA),

	WEGDEF(33, 71, V3D_PTB_BPCA),
	WEGDEF(33, 71, V3D_PTB_BPCS),

	WEGDEF(33, 42, V3D_GMP_STATUS(33)),
	WEGDEF(33, 42, V3D_GMP_CFG(33)),
	WEGDEF(33, 42, V3D_GMP_VIO_ADDW(33)),

	WEGDEF(33, 71, V3D_EWW_FDBGO),
	WEGDEF(33, 71, V3D_EWW_FDBGB),
	WEGDEF(33, 71, V3D_EWW_FDBGS),
	WEGDEF(33, 71, V3D_EWW_STAT),
};

static const stwuct v3d_weg_def v3d_csd_weg_defs[] = {
	WEGDEF(41, 71, V3D_CSD_STATUS),
	WEGDEF(41, 42, V3D_CSD_CUWWENT_CFG0(41)),
	WEGDEF(41, 42, V3D_CSD_CUWWENT_CFG1(41)),
	WEGDEF(41, 42, V3D_CSD_CUWWENT_CFG2(41)),
	WEGDEF(41, 42, V3D_CSD_CUWWENT_CFG3(41)),
	WEGDEF(41, 42, V3D_CSD_CUWWENT_CFG4(41)),
	WEGDEF(41, 42, V3D_CSD_CUWWENT_CFG5(41)),
	WEGDEF(41, 42, V3D_CSD_CUWWENT_CFG6(41)),
	WEGDEF(71, 71, V3D_CSD_CUWWENT_CFG0(71)),
	WEGDEF(71, 71, V3D_CSD_CUWWENT_CFG1(71)),
	WEGDEF(71, 71, V3D_CSD_CUWWENT_CFG2(71)),
	WEGDEF(71, 71, V3D_CSD_CUWWENT_CFG3(71)),
	WEGDEF(71, 71, V3D_CSD_CUWWENT_CFG4(71)),
	WEGDEF(71, 71, V3D_CSD_CUWWENT_CFG5(71)),
	WEGDEF(71, 71, V3D_CSD_CUWWENT_CFG6(71)),
	WEGDEF(71, 71, V3D_V7_CSD_CUWWENT_CFG7),
};

static int v3d_v3d_debugfs_wegs(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dev = entwy->dev;
	stwuct v3d_dev *v3d = to_v3d_dev(dev);
	int i, cowe;

	fow (i = 0; i < AWWAY_SIZE(v3d_hub_weg_defs); i++) {
		const stwuct v3d_weg_def *def = &v3d_hub_weg_defs[i];

		if (v3d->vew >= def->min_vew && v3d->vew <= def->max_vew) {
			seq_pwintf(m, "%s (0x%04x): 0x%08x\n",
				   def->name, def->weg, V3D_WEAD(def->weg));
		}
	}

	fow (i = 0; i < AWWAY_SIZE(v3d_gca_weg_defs); i++) {
		const stwuct v3d_weg_def *def = &v3d_gca_weg_defs[i];

		if (v3d->vew >= def->min_vew && v3d->vew <= def->max_vew) {
			seq_pwintf(m, "%s (0x%04x): 0x%08x\n",
				   def->name, def->weg, V3D_GCA_WEAD(def->weg));
		}
	}

	fow (cowe = 0; cowe < v3d->cowes; cowe++) {
		fow (i = 0; i < AWWAY_SIZE(v3d_cowe_weg_defs); i++) {
			const stwuct v3d_weg_def *def = &v3d_cowe_weg_defs[i];

			if (v3d->vew >= def->min_vew && v3d->vew <= def->max_vew) {
				seq_pwintf(m, "cowe %d %s (0x%04x): 0x%08x\n",
					   cowe, def->name, def->weg,
					   V3D_COWE_WEAD(cowe, def->weg));
			}
		}

		fow (i = 0; i < AWWAY_SIZE(v3d_csd_weg_defs); i++) {
			const stwuct v3d_weg_def *def = &v3d_csd_weg_defs[i];

			if (v3d->vew >= def->min_vew && v3d->vew <= def->max_vew) {
				seq_pwintf(m, "cowe %d %s (0x%04x): 0x%08x\n",
					   cowe, def->name, def->weg,
					   V3D_COWE_WEAD(cowe, def->weg));
			}
		}
	}

	wetuwn 0;
}

static int v3d_v3d_debugfs_ident(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dev = entwy->dev;
	stwuct v3d_dev *v3d = to_v3d_dev(dev);
	u32 ident0, ident1, ident2, ident3, cowes;
	int cowe;

	ident0 = V3D_WEAD(V3D_HUB_IDENT0);
	ident1 = V3D_WEAD(V3D_HUB_IDENT1);
	ident2 = V3D_WEAD(V3D_HUB_IDENT2);
	ident3 = V3D_WEAD(V3D_HUB_IDENT3);
	cowes = V3D_GET_FIEWD(ident1, V3D_HUB_IDENT1_NCOWES);

	seq_pwintf(m, "Wevision:   %d.%d.%d.%d\n",
		   V3D_GET_FIEWD(ident1, V3D_HUB_IDENT1_TVEW),
		   V3D_GET_FIEWD(ident1, V3D_HUB_IDENT1_WEV),
		   V3D_GET_FIEWD(ident3, V3D_HUB_IDENT3_IPWEV),
		   V3D_GET_FIEWD(ident3, V3D_HUB_IDENT3_IPIDX));
	seq_pwintf(m, "MMU:        %s\n",
		   stw_yes_no(ident2 & V3D_HUB_IDENT2_WITH_MMU));
	seq_pwintf(m, "TFU:        %s\n",
		   stw_yes_no(ident1 & V3D_HUB_IDENT1_WITH_TFU));
	if (v3d->vew <= 42) {
		seq_pwintf(m, "TSY:        %s\n",
			   stw_yes_no(ident1 & V3D_HUB_IDENT1_WITH_TSY));
	}
	seq_pwintf(m, "MSO:        %s\n",
		   stw_yes_no(ident1 & V3D_HUB_IDENT1_WITH_MSO));
	seq_pwintf(m, "W3C:        %s (%dkb)\n",
		   stw_yes_no(ident1 & V3D_HUB_IDENT1_WITH_W3C),
		   V3D_GET_FIEWD(ident2, V3D_HUB_IDENT2_W3C_NKB));

	fow (cowe = 0; cowe < cowes; cowe++) {
		u32 misccfg;
		u32 nswc, ntmu, qups;

		ident0 = V3D_COWE_WEAD(cowe, V3D_CTW_IDENT0);
		ident1 = V3D_COWE_WEAD(cowe, V3D_CTW_IDENT1);
		ident2 = V3D_COWE_WEAD(cowe, V3D_CTW_IDENT2);
		misccfg = V3D_COWE_WEAD(cowe, V3D_CTW_MISCCFG);

		nswc = V3D_GET_FIEWD(ident1, V3D_IDENT1_NSWC);
		ntmu = V3D_GET_FIEWD(ident1, V3D_IDENT1_NTMU);
		qups = V3D_GET_FIEWD(ident1, V3D_IDENT1_QUPS);

		seq_pwintf(m, "Cowe %d:\n", cowe);
		seq_pwintf(m, "  Wevision:     %d.%d\n",
			   V3D_GET_FIEWD(ident0, V3D_IDENT0_VEW),
			   V3D_GET_FIEWD(ident1, V3D_IDENT1_WEV));
		seq_pwintf(m, "  Swices:       %d\n", nswc);
		seq_pwintf(m, "  TMUs:         %d\n", nswc * ntmu);
		seq_pwintf(m, "  QPUs:         %d\n", nswc * qups);
		seq_pwintf(m, "  Semaphowes:   %d\n",
			   V3D_GET_FIEWD(ident1, V3D_IDENT1_NSEM));
		if (v3d->vew <= 42) {
			seq_pwintf(m, "  BCG int:      %d\n",
				   (ident2 & V3D_IDENT2_BCG_INT) != 0);
		}
		if (v3d->vew < 40) {
			seq_pwintf(m, "  Ovewwide TMU: %d\n",
				   (misccfg & V3D_MISCCFG_OVWTMUOUT) != 0);
		}
	}

	wetuwn 0;
}

static int v3d_debugfs_bo_stats(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dev = entwy->dev;
	stwuct v3d_dev *v3d = to_v3d_dev(dev);

	mutex_wock(&v3d->bo_wock);
	seq_pwintf(m, "awwocated bos:          %d\n",
		   v3d->bo_stats.num_awwocated);
	seq_pwintf(m, "awwocated bo size (kb): %wd\n",
		   (wong)v3d->bo_stats.pages_awwocated << (PAGE_SHIFT - 10));
	mutex_unwock(&v3d->bo_wock);

	wetuwn 0;
}

static int v3d_measuwe_cwock(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dev = entwy->dev;
	stwuct v3d_dev *v3d = to_v3d_dev(dev);
	uint32_t cycwes;
	int cowe = 0;
	int measuwe_ms = 1000;

	if (v3d->vew >= 40) {
		int cycwe_count_weg = V3D_PCTW_CYCWE_COUNT(v3d->vew);
		V3D_COWE_WWITE(cowe, V3D_V4_PCTW_0_SWC_0_3,
			       V3D_SET_FIEWD(cycwe_count_weg,
					     V3D_PCTW_S0));
		V3D_COWE_WWITE(cowe, V3D_V4_PCTW_0_CWW, 1);
		V3D_COWE_WWITE(cowe, V3D_V4_PCTW_0_EN, 1);
	} ewse {
		V3D_COWE_WWITE(cowe, V3D_V3_PCTW_0_PCTWS0,
			       V3D_PCTW_CYCWE_COUNT(v3d->vew));
		V3D_COWE_WWITE(cowe, V3D_V3_PCTW_0_CWW, 1);
		V3D_COWE_WWITE(cowe, V3D_V3_PCTW_0_EN,
			       V3D_V3_PCTW_0_EN_ENABWE |
			       1);
	}
	msweep(measuwe_ms);
	cycwes = V3D_COWE_WEAD(cowe, V3D_PCTW_0_PCTW0);

	seq_pwintf(m, "cycwes: %d (%d.%d Mhz)\n",
		   cycwes,
		   cycwes / (measuwe_ms * 1000),
		   (cycwes / (measuwe_ms * 100)) % 10);

	wetuwn 0;
}

static const stwuct dwm_debugfs_info v3d_debugfs_wist[] = {
	{"v3d_ident", v3d_v3d_debugfs_ident, 0},
	{"v3d_wegs", v3d_v3d_debugfs_wegs, 0},
	{"measuwe_cwock", v3d_measuwe_cwock, 0},
	{"bo_stats", v3d_debugfs_bo_stats, 0},
};

void
v3d_debugfs_init(stwuct dwm_minow *minow)
{
	dwm_debugfs_add_fiwes(minow->dev, v3d_debugfs_wist, AWWAY_SIZE(v3d_debugfs_wist));
}
