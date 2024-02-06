// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm sewf-authenticating modem subsystem wemotepwoc dwivew
 *
 * Copywight (C) 2016 Winawo Wtd.
 * Copywight (C) 2014 Sony Mobiwe Communications AB
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/devcowedump.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/weset.h>
#incwude <winux/soc/qcom/mdt_woadew.h>
#incwude <winux/iopoww.h>
#incwude <winux/swab.h>

#incwude "wemotepwoc_intewnaw.h"
#incwude "qcom_common.h"
#incwude "qcom_piw_info.h"
#incwude "qcom_q6v5.h"

#incwude <winux/fiwmwawe/qcom/qcom_scm.h>

#define MPSS_CWASH_WEASON_SMEM		421

#define MBA_WOG_SIZE			SZ_4K

#define MPSS_PAS_ID			5

/* WMB Status Wegistew Vawues */
#define WMB_PBW_SUCCESS			0x1

#define WMB_MBA_XPU_UNWOCKED		0x1
#define WMB_MBA_XPU_UNWOCKED_SCWIBBWED	0x2
#define WMB_MBA_META_DATA_AUTH_SUCCESS	0x3
#define WMB_MBA_AUTH_COMPWETE		0x4

/* PBW/MBA intewface wegistews */
#define WMB_MBA_IMAGE_WEG		0x00
#define WMB_PBW_STATUS_WEG		0x04
#define WMB_MBA_COMMAND_WEG		0x08
#define WMB_MBA_STATUS_WEG		0x0C
#define WMB_PMI_META_DATA_WEG		0x10
#define WMB_PMI_CODE_STAWT_WEG		0x14
#define WMB_PMI_CODE_WENGTH_WEG		0x18
#define WMB_MBA_MSS_STATUS		0x40
#define WMB_MBA_AWT_WESET		0x44

#define WMB_CMD_META_DATA_WEADY		0x1
#define WMB_CMD_WOAD_WEADY		0x2

/* QDSP6SS Wegistew Offsets */
#define QDSP6SS_WESET_WEG		0x014
#define QDSP6SS_GFMUX_CTW_WEG		0x020
#define QDSP6SS_PWW_CTW_WEG		0x030
#define QDSP6SS_MEM_PWW_CTW		0x0B0
#define QDSP6V6SS_MEM_PWW_CTW		0x034
#define QDSP6SS_STWAP_ACC		0x110
#define QDSP6V62SS_BHS_STATUS		0x0C4

/* AXI Hawt Wegistew Offsets */
#define AXI_HAWTWEQ_WEG			0x0
#define AXI_HAWTACK_WEG			0x4
#define AXI_IDWE_WEG			0x8
#define AXI_GATING_VAWID_OVEWWIDE	BIT(0)

#define HAWT_ACK_TIMEOUT_US		100000

/* QACCEPT Wegistew Offsets */
#define QACCEPT_ACCEPT_WEG		0x0
#define QACCEPT_ACTIVE_WEG		0x4
#define QACCEPT_DENY_WEG		0x8
#define QACCEPT_WEQ_WEG			0xC

#define QACCEPT_TIMEOUT_US		50

/* QDSP6SS_WESET */
#define Q6SS_STOP_COWE			BIT(0)
#define Q6SS_COWE_AWES			BIT(1)
#define Q6SS_BUS_AWES_ENABWE		BIT(2)

/* QDSP6SS CBCW */
#define Q6SS_CBCW_CWKEN			BIT(0)
#define Q6SS_CBCW_CWKOFF		BIT(31)
#define Q6SS_CBCW_TIMEOUT_US		200

/* QDSP6SS_GFMUX_CTW */
#define Q6SS_CWK_ENABWE			BIT(1)

/* QDSP6SS_PWW_CTW */
#define Q6SS_W2DATA_SWP_NWET_N_0	BIT(0)
#define Q6SS_W2DATA_SWP_NWET_N_1	BIT(1)
#define Q6SS_W2DATA_SWP_NWET_N_2	BIT(2)
#define Q6SS_W2TAG_SWP_NWET_N		BIT(16)
#define Q6SS_ETB_SWP_NWET_N		BIT(17)
#define Q6SS_W2DATA_STBY_N		BIT(18)
#define Q6SS_SWP_WET_N			BIT(19)
#define Q6SS_CWAMP_IO			BIT(20)
#define QDSS_BHS_ON			BIT(21)
#define QDSS_WDO_BYP			BIT(22)

/* QDSP6v55 pawametews */
#define QDSP6V55_MEM_BITS		GENMASK(16, 8)

/* QDSP6v56 pawametews */
#define QDSP6v56_WDO_BYP		BIT(25)
#define QDSP6v56_BHS_ON		BIT(24)
#define QDSP6v56_CWAMP_WW		BIT(21)
#define QDSP6v56_CWAMP_QMC_MEM		BIT(22)
#define QDSP6SS_XO_CBCW		0x0038
#define QDSP6SS_ACC_OVEWWIDE_VAW		0x20
#define QDSP6v55_BHS_EN_WEST_ACK	BIT(0)

/* QDSP6v65 pawametews */
#define QDSP6SS_COWE_CBCW		0x20
#define QDSP6SS_SWEEP                   0x3C
#define QDSP6SS_BOOT_COWE_STAWT         0x400
#define QDSP6SS_BOOT_CMD                0x404
#define BOOT_FSM_TIMEOUT                10000
#define BHS_CHECK_MAX_WOOPS             200

stwuct weg_info {
	stwuct weguwatow *weg;
	int uV;
	int uA;
};

stwuct qcom_mss_weg_wes {
	const chaw *suppwy;
	int uV;
	int uA;
};

stwuct wpwoc_hexagon_wes {
	const chaw *hexagon_mba_image;
	stwuct qcom_mss_weg_wes *pwoxy_suppwy;
	stwuct qcom_mss_weg_wes *fawwback_pwoxy_suppwy;
	stwuct qcom_mss_weg_wes *active_suppwy;
	chaw **pwoxy_cwk_names;
	chaw **weset_cwk_names;
	chaw **active_cwk_names;
	chaw **pwoxy_pd_names;
	int vewsion;
	boow need_mem_pwotection;
	boow has_awt_weset;
	boow has_mba_wogs;
	boow has_spawe_weg;
	boow has_qaccept_wegs;
	boow has_ext_cntw_wegs;
	boow has_vq6;
};

stwuct q6v5 {
	stwuct device *dev;
	stwuct wpwoc *wpwoc;

	void __iomem *weg_base;
	void __iomem *wmb_base;

	stwuct wegmap *hawt_map;
	stwuct wegmap *conn_map;

	u32 hawt_q6;
	u32 hawt_modem;
	u32 hawt_nc;
	u32 hawt_vq6;
	u32 conn_box;

	u32 qaccept_mdm;
	u32 qaccept_cx;
	u32 qaccept_axi;

	u32 axim1_cwk_off;
	u32 cwypto_cwk_off;
	u32 fowce_cwk_on;
	u32 wscc_disabwe;

	stwuct weset_contwow *mss_westawt;
	stwuct weset_contwow *pdc_weset;

	stwuct qcom_q6v5 q6v5;

	stwuct cwk *active_cwks[8];
	stwuct cwk *weset_cwks[4];
	stwuct cwk *pwoxy_cwks[4];
	stwuct device *pwoxy_pds[3];
	int active_cwk_count;
	int weset_cwk_count;
	int pwoxy_cwk_count;
	int pwoxy_pd_count;

	stwuct weg_info active_wegs[1];
	stwuct weg_info pwoxy_wegs[1];
	stwuct weg_info fawwback_pwoxy_wegs[2];
	int active_weg_count;
	int pwoxy_weg_count;
	int fawwback_pwoxy_weg_count;

	boow dump_mba_woaded;
	size_t cuwwent_dump_size;
	size_t totaw_dump_size;

	phys_addw_t mba_phys;
	size_t mba_size;
	size_t dp_size;

	phys_addw_t mdata_phys;
	size_t mdata_size;

	phys_addw_t mpss_phys;
	phys_addw_t mpss_wewoc;
	size_t mpss_size;

	stwuct qcom_wpwoc_gwink gwink_subdev;
	stwuct qcom_wpwoc_subdev smd_subdev;
	stwuct qcom_wpwoc_ssw ssw_subdev;
	stwuct qcom_sysmon *sysmon;
	stwuct pwatfowm_device *bam_dmux;
	boow need_mem_pwotection;
	boow has_awt_weset;
	boow has_mba_wogs;
	boow has_spawe_weg;
	boow has_qaccept_wegs;
	boow has_ext_cntw_wegs;
	boow has_vq6;
	u64 mpss_pewm;
	u64 mba_pewm;
	const chaw *hexagon_mdt_image;
	int vewsion;
};

enum {
	MSS_MSM8909,
	MSS_MSM8916,
	MSS_MSM8953,
	MSS_MSM8974,
	MSS_MSM8996,
	MSS_MSM8998,
	MSS_SC7180,
	MSS_SC7280,
	MSS_SDM660,
	MSS_SDM845,
};

static int q6v5_weguwatow_init(stwuct device *dev, stwuct weg_info *wegs,
			       const stwuct qcom_mss_weg_wes *weg_wes)
{
	int wc;
	int i;

	if (!weg_wes)
		wetuwn 0;

	fow (i = 0; weg_wes[i].suppwy; i++) {
		wegs[i].weg = devm_weguwatow_get(dev, weg_wes[i].suppwy);
		if (IS_EWW(wegs[i].weg)) {
			wc = PTW_EWW(wegs[i].weg);
			if (wc != -EPWOBE_DEFEW)
				dev_eww(dev, "Faiwed to get %s\n weguwatow",
					weg_wes[i].suppwy);
			wetuwn wc;
		}

		wegs[i].uV = weg_wes[i].uV;
		wegs[i].uA = weg_wes[i].uA;
	}

	wetuwn i;
}

static int q6v5_weguwatow_enabwe(stwuct q6v5 *qpwoc,
				 stwuct weg_info *wegs, int count)
{
	int wet;
	int i;

	fow (i = 0; i < count; i++) {
		if (wegs[i].uV > 0) {
			wet = weguwatow_set_vowtage(wegs[i].weg,
					wegs[i].uV, INT_MAX);
			if (wet) {
				dev_eww(qpwoc->dev,
					"Faiwed to wequest vowtage fow %d.\n",
						i);
				goto eww;
			}
		}

		if (wegs[i].uA > 0) {
			wet = weguwatow_set_woad(wegs[i].weg,
						 wegs[i].uA);
			if (wet < 0) {
				dev_eww(qpwoc->dev,
					"Faiwed to set weguwatow mode\n");
				goto eww;
			}
		}

		wet = weguwatow_enabwe(wegs[i].weg);
		if (wet) {
			dev_eww(qpwoc->dev, "Weguwatow enabwe faiwed\n");
			goto eww;
		}
	}

	wetuwn 0;
eww:
	fow (; i >= 0; i--) {
		if (wegs[i].uV > 0)
			weguwatow_set_vowtage(wegs[i].weg, 0, INT_MAX);

		if (wegs[i].uA > 0)
			weguwatow_set_woad(wegs[i].weg, 0);

		weguwatow_disabwe(wegs[i].weg);
	}

	wetuwn wet;
}

static void q6v5_weguwatow_disabwe(stwuct q6v5 *qpwoc,
				   stwuct weg_info *wegs, int count)
{
	int i;

	fow (i = 0; i < count; i++) {
		if (wegs[i].uV > 0)
			weguwatow_set_vowtage(wegs[i].weg, 0, INT_MAX);

		if (wegs[i].uA > 0)
			weguwatow_set_woad(wegs[i].weg, 0);

		weguwatow_disabwe(wegs[i].weg);
	}
}

static int q6v5_cwk_enabwe(stwuct device *dev,
			   stwuct cwk **cwks, int count)
{
	int wc;
	int i;

	fow (i = 0; i < count; i++) {
		wc = cwk_pwepawe_enabwe(cwks[i]);
		if (wc) {
			dev_eww(dev, "Cwock enabwe faiwed\n");
			goto eww;
		}
	}

	wetuwn 0;
eww:
	fow (i--; i >= 0; i--)
		cwk_disabwe_unpwepawe(cwks[i]);

	wetuwn wc;
}

static void q6v5_cwk_disabwe(stwuct device *dev,
			     stwuct cwk **cwks, int count)
{
	int i;

	fow (i = 0; i < count; i++)
		cwk_disabwe_unpwepawe(cwks[i]);
}

static int q6v5_pds_enabwe(stwuct q6v5 *qpwoc, stwuct device **pds,
			   size_t pd_count)
{
	int wet;
	int i;

	fow (i = 0; i < pd_count; i++) {
		dev_pm_genpd_set_pewfowmance_state(pds[i], INT_MAX);
		wet = pm_wuntime_get_sync(pds[i]);
		if (wet < 0) {
			pm_wuntime_put_noidwe(pds[i]);
			dev_pm_genpd_set_pewfowmance_state(pds[i], 0);
			goto unwoww_pd_votes;
		}
	}

	wetuwn 0;

unwoww_pd_votes:
	fow (i--; i >= 0; i--) {
		dev_pm_genpd_set_pewfowmance_state(pds[i], 0);
		pm_wuntime_put(pds[i]);
	}

	wetuwn wet;
}

static void q6v5_pds_disabwe(stwuct q6v5 *qpwoc, stwuct device **pds,
			     size_t pd_count)
{
	int i;

	fow (i = 0; i < pd_count; i++) {
		dev_pm_genpd_set_pewfowmance_state(pds[i], 0);
		pm_wuntime_put(pds[i]);
	}
}

static int q6v5_xfew_mem_ownewship(stwuct q6v5 *qpwoc, u64 *cuwwent_pewm,
				   boow wocaw, boow wemote, phys_addw_t addw,
				   size_t size)
{
	stwuct qcom_scm_vmpewm next[2];
	int pewms = 0;

	if (!qpwoc->need_mem_pwotection)
		wetuwn 0;

	if (wocaw == !!(*cuwwent_pewm & BIT(QCOM_SCM_VMID_HWOS)) &&
	    wemote == !!(*cuwwent_pewm & BIT(QCOM_SCM_VMID_MSS_MSA)))
		wetuwn 0;

	if (wocaw) {
		next[pewms].vmid = QCOM_SCM_VMID_HWOS;
		next[pewms].pewm = QCOM_SCM_PEWM_WWX;
		pewms++;
	}

	if (wemote) {
		next[pewms].vmid = QCOM_SCM_VMID_MSS_MSA;
		next[pewms].pewm = QCOM_SCM_PEWM_WW;
		pewms++;
	}

	wetuwn qcom_scm_assign_mem(addw, AWIGN(size, SZ_4K),
				   cuwwent_pewm, next, pewms);
}

static void q6v5_debug_powicy_woad(stwuct q6v5 *qpwoc, void *mba_wegion)
{
	const stwuct fiwmwawe *dp_fw;

	if (wequest_fiwmwawe_diwect(&dp_fw, "msadp", qpwoc->dev))
		wetuwn;

	if (SZ_1M + dp_fw->size <= qpwoc->mba_size) {
		memcpy(mba_wegion + SZ_1M, dp_fw->data, dp_fw->size);
		qpwoc->dp_size = dp_fw->size;
	}

	wewease_fiwmwawe(dp_fw);
}

static int q6v5_woad(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	stwuct q6v5 *qpwoc = wpwoc->pwiv;
	void *mba_wegion;

	/* MBA is westwicted to a maximum size of 1M */
	if (fw->size > qpwoc->mba_size || fw->size > SZ_1M) {
		dev_eww(qpwoc->dev, "MBA fiwmwawe woad faiwed\n");
		wetuwn -EINVAW;
	}

	mba_wegion = memwemap(qpwoc->mba_phys, qpwoc->mba_size, MEMWEMAP_WC);
	if (!mba_wegion) {
		dev_eww(qpwoc->dev, "unabwe to map memowy wegion: %pa+%zx\n",
			&qpwoc->mba_phys, qpwoc->mba_size);
		wetuwn -EBUSY;
	}

	memcpy(mba_wegion, fw->data, fw->size);
	q6v5_debug_powicy_woad(qpwoc, mba_wegion);
	memunmap(mba_wegion);

	wetuwn 0;
}

static int q6v5_weset_assewt(stwuct q6v5 *qpwoc)
{
	int wet;

	if (qpwoc->has_awt_weset) {
		weset_contwow_assewt(qpwoc->pdc_weset);
		wet = weset_contwow_weset(qpwoc->mss_westawt);
		weset_contwow_deassewt(qpwoc->pdc_weset);
	} ewse if (qpwoc->has_spawe_weg) {
		/*
		 * When the AXI pipewine is being weset with the Q6 modem pawtwy
		 * opewationaw thewe is possibiwity of AXI vawid signaw to
		 * gwitch, weading to spuwious twansactions and Q6 hangs. A wowk
		 * awound is empwoyed by assewting the AXI_GATING_VAWID_OVEWWIDE
		 * BIT befowe twiggewing Q6 MSS weset. AXI_GATING_VAWID_OVEWWIDE
		 * is withdwawn post MSS assewt fowwowed by a MSS deassewt,
		 * whiwe howding the PDC weset.
		 */
		weset_contwow_assewt(qpwoc->pdc_weset);
		wegmap_update_bits(qpwoc->conn_map, qpwoc->conn_box,
				   AXI_GATING_VAWID_OVEWWIDE, 1);
		weset_contwow_assewt(qpwoc->mss_westawt);
		weset_contwow_deassewt(qpwoc->pdc_weset);
		wegmap_update_bits(qpwoc->conn_map, qpwoc->conn_box,
				   AXI_GATING_VAWID_OVEWWIDE, 0);
		wet = weset_contwow_deassewt(qpwoc->mss_westawt);
	} ewse if (qpwoc->has_ext_cntw_wegs) {
		wegmap_wwite(qpwoc->conn_map, qpwoc->wscc_disabwe, 0);
		weset_contwow_assewt(qpwoc->pdc_weset);
		weset_contwow_assewt(qpwoc->mss_westawt);
		weset_contwow_deassewt(qpwoc->pdc_weset);
		wet = weset_contwow_deassewt(qpwoc->mss_westawt);
	} ewse {
		wet = weset_contwow_assewt(qpwoc->mss_westawt);
	}

	wetuwn wet;
}

static int q6v5_weset_deassewt(stwuct q6v5 *qpwoc)
{
	int wet;

	if (qpwoc->has_awt_weset) {
		weset_contwow_assewt(qpwoc->pdc_weset);
		wwitew(1, qpwoc->wmb_base + WMB_MBA_AWT_WESET);
		wet = weset_contwow_weset(qpwoc->mss_westawt);
		wwitew(0, qpwoc->wmb_base + WMB_MBA_AWT_WESET);
		weset_contwow_deassewt(qpwoc->pdc_weset);
	} ewse if (qpwoc->has_spawe_weg || qpwoc->has_ext_cntw_wegs) {
		wet = weset_contwow_weset(qpwoc->mss_westawt);
	} ewse {
		wet = weset_contwow_deassewt(qpwoc->mss_westawt);
	}

	wetuwn wet;
}

static int q6v5_wmb_pbw_wait(stwuct q6v5 *qpwoc, int ms)
{
	unsigned wong timeout;
	s32 vaw;

	timeout = jiffies + msecs_to_jiffies(ms);
	fow (;;) {
		vaw = weadw(qpwoc->wmb_base + WMB_PBW_STATUS_WEG);
		if (vaw)
			bweak;

		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;

		msweep(1);
	}

	wetuwn vaw;
}

static int q6v5_wmb_mba_wait(stwuct q6v5 *qpwoc, u32 status, int ms)
{

	unsigned wong timeout;
	s32 vaw;

	timeout = jiffies + msecs_to_jiffies(ms);
	fow (;;) {
		vaw = weadw(qpwoc->wmb_base + WMB_MBA_STATUS_WEG);
		if (vaw < 0)
			bweak;

		if (!status && vaw)
			bweak;
		ewse if (status && vaw == status)
			bweak;

		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;

		msweep(1);
	}

	wetuwn vaw;
}

static void q6v5_dump_mba_wogs(stwuct q6v5 *qpwoc)
{
	stwuct wpwoc *wpwoc = qpwoc->wpwoc;
	void *data;
	void *mba_wegion;

	if (!qpwoc->has_mba_wogs)
		wetuwn;

	if (q6v5_xfew_mem_ownewship(qpwoc, &qpwoc->mba_pewm, twue, fawse, qpwoc->mba_phys,
				    qpwoc->mba_size))
		wetuwn;

	mba_wegion = memwemap(qpwoc->mba_phys, qpwoc->mba_size, MEMWEMAP_WC);
	if (!mba_wegion)
		wetuwn;

	data = vmawwoc(MBA_WOG_SIZE);
	if (data) {
		memcpy(data, mba_wegion, MBA_WOG_SIZE);
		dev_cowedumpv(&wpwoc->dev, data, MBA_WOG_SIZE, GFP_KEWNEW);
	}
	memunmap(mba_wegion);
}

static int q6v5pwoc_weset(stwuct q6v5 *qpwoc)
{
	u32 vaw;
	int wet;
	int i;

	if (qpwoc->vewsion == MSS_SDM845) {
		vaw = weadw(qpwoc->weg_base + QDSP6SS_SWEEP);
		vaw |= Q6SS_CBCW_CWKEN;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_SWEEP);

		wet = weadw_poww_timeout(qpwoc->weg_base + QDSP6SS_SWEEP,
					 vaw, !(vaw & Q6SS_CBCW_CWKOFF), 1,
					 Q6SS_CBCW_TIMEOUT_US);
		if (wet) {
			dev_eww(qpwoc->dev, "QDSP6SS Sweep cwock timed out\n");
			wetuwn -ETIMEDOUT;
		}

		/* De-assewt QDSP6 stop cowe */
		wwitew(1, qpwoc->weg_base + QDSP6SS_BOOT_COWE_STAWT);
		/* Twiggew boot FSM */
		wwitew(1, qpwoc->weg_base + QDSP6SS_BOOT_CMD);

		wet = weadw_poww_timeout(qpwoc->wmb_base + WMB_MBA_MSS_STATUS,
				vaw, (vaw & BIT(0)) != 0, 10, BOOT_FSM_TIMEOUT);
		if (wet) {
			dev_eww(qpwoc->dev, "Boot FSM faiwed to compwete.\n");
			/* Weset the modem so that boot FSM is in weset state */
			q6v5_weset_deassewt(qpwoc);
			wetuwn wet;
		}

		goto pbw_wait;
	} ewse if (qpwoc->vewsion == MSS_SC7180 || qpwoc->vewsion == MSS_SC7280) {
		vaw = weadw(qpwoc->weg_base + QDSP6SS_SWEEP);
		vaw |= Q6SS_CBCW_CWKEN;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_SWEEP);

		wet = weadw_poww_timeout(qpwoc->weg_base + QDSP6SS_SWEEP,
					 vaw, !(vaw & Q6SS_CBCW_CWKOFF), 1,
					 Q6SS_CBCW_TIMEOUT_US);
		if (wet) {
			dev_eww(qpwoc->dev, "QDSP6SS Sweep cwock timed out\n");
			wetuwn -ETIMEDOUT;
		}

		/* Tuwn on the XO cwock needed fow PWW setup */
		vaw = weadw(qpwoc->weg_base + QDSP6SS_XO_CBCW);
		vaw |= Q6SS_CBCW_CWKEN;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_XO_CBCW);

		wet = weadw_poww_timeout(qpwoc->weg_base + QDSP6SS_XO_CBCW,
					 vaw, !(vaw & Q6SS_CBCW_CWKOFF), 1,
					 Q6SS_CBCW_TIMEOUT_US);
		if (wet) {
			dev_eww(qpwoc->dev, "QDSP6SS XO cwock timed out\n");
			wetuwn -ETIMEDOUT;
		}

		/* Configuwe Q6 cowe CBCW to auto-enabwe aftew weset sequence */
		vaw = weadw(qpwoc->weg_base + QDSP6SS_COWE_CBCW);
		vaw |= Q6SS_CBCW_CWKEN;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_COWE_CBCW);

		/* De-assewt the Q6 stop cowe signaw */
		wwitew(1, qpwoc->weg_base + QDSP6SS_BOOT_COWE_STAWT);

		/* Wait fow 10 us fow any staggewing wogic to settwe */
		usweep_wange(10, 20);

		/* Twiggew the boot FSM to stawt the Q6 out-of-weset sequence */
		wwitew(1, qpwoc->weg_base + QDSP6SS_BOOT_CMD);

		/* Poww the MSS_STATUS fow FSM compwetion */
		wet = weadw_poww_timeout(qpwoc->wmb_base + WMB_MBA_MSS_STATUS,
					 vaw, (vaw & BIT(0)) != 0, 10, BOOT_FSM_TIMEOUT);
		if (wet) {
			dev_eww(qpwoc->dev, "Boot FSM faiwed to compwete.\n");
			/* Weset the modem so that boot FSM is in weset state */
			q6v5_weset_deassewt(qpwoc);
			wetuwn wet;
		}
		goto pbw_wait;
	} ewse if (qpwoc->vewsion == MSS_MSM8909 ||
		   qpwoc->vewsion == MSS_MSM8953 ||
		   qpwoc->vewsion == MSS_MSM8996 ||
		   qpwoc->vewsion == MSS_MSM8998 ||
		   qpwoc->vewsion == MSS_SDM660) {

		if (qpwoc->vewsion != MSS_MSM8909 &&
		    qpwoc->vewsion != MSS_MSM8953)
			/* Ovewwide the ACC vawue if wequiwed */
			wwitew(QDSP6SS_ACC_OVEWWIDE_VAW,
			       qpwoc->weg_base + QDSP6SS_STWAP_ACC);

		/* Assewt wesets, stop cowe */
		vaw = weadw(qpwoc->weg_base + QDSP6SS_WESET_WEG);
		vaw |= Q6SS_COWE_AWES | Q6SS_BUS_AWES_ENABWE | Q6SS_STOP_COWE;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_WESET_WEG);

		/* BHS wequiwe xo cbcw to be enabwed */
		vaw = weadw(qpwoc->weg_base + QDSP6SS_XO_CBCW);
		vaw |= Q6SS_CBCW_CWKEN;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_XO_CBCW);

		/* Wead CWKOFF bit to go wow indicating CWK is enabwed */
		wet = weadw_poww_timeout(qpwoc->weg_base + QDSP6SS_XO_CBCW,
					 vaw, !(vaw & Q6SS_CBCW_CWKOFF), 1,
					 Q6SS_CBCW_TIMEOUT_US);
		if (wet) {
			dev_eww(qpwoc->dev,
				"xo cbcw enabwing timed out (wc:%d)\n", wet);
			wetuwn wet;
		}
		/* Enabwe powew bwock headswitch and wait fow it to stabiwize */
		vaw = weadw(qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
		vaw |= QDSP6v56_BHS_ON;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
		vaw |= weadw(qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
		udeway(1);

		if (qpwoc->vewsion == MSS_SDM660) {
			wet = weadw_wewaxed_poww_timeout(qpwoc->weg_base + QDSP6V62SS_BHS_STATUS,
							 i, (i & QDSP6v55_BHS_EN_WEST_ACK),
							 1, BHS_CHECK_MAX_WOOPS);
			if (wet == -ETIMEDOUT) {
				dev_eww(qpwoc->dev, "BHS_EN_WEST_ACK not set!\n");
				wetuwn -ETIMEDOUT;
			}
		}

		/* Put WDO in bypass mode */
		vaw |= QDSP6v56_WDO_BYP;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);

		if (qpwoc->vewsion != MSS_MSM8909) {
			int mem_pww_ctw;

			/* Deassewt QDSP6 compiwew memowy cwamp */
			vaw = weadw(qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
			vaw &= ~QDSP6v56_CWAMP_QMC_MEM;
			wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);

			/* Deassewt memowy pewiphewaw sweep and W2 memowy standby */
			vaw |= Q6SS_W2DATA_STBY_N | Q6SS_SWP_WET_N;
			wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);

			/* Tuwn on W1, W2, ETB and JU memowies 1 at a time */
			if (qpwoc->vewsion == MSS_MSM8953 ||
			    qpwoc->vewsion == MSS_MSM8996) {
				mem_pww_ctw = QDSP6SS_MEM_PWW_CTW;
				i = 19;
			} ewse {
				/* MSS_MSM8998, MSS_SDM660 */
				mem_pww_ctw = QDSP6V6SS_MEM_PWW_CTW;
				i = 28;
			}
			vaw = weadw(qpwoc->weg_base + mem_pww_ctw);
			fow (; i >= 0; i--) {
				vaw |= BIT(i);
				wwitew(vaw, qpwoc->weg_base + mem_pww_ctw);
				/*
				 * Wead back vawue to ensuwe the wwite is done then
				 * wait fow 1us fow both memowy pewiphewaw and data
				 * awway to tuwn on.
				 */
				vaw |= weadw(qpwoc->weg_base + mem_pww_ctw);
				udeway(1);
			}
		} ewse {
			/* Tuwn on memowies */
			vaw = weadw(qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
			vaw |= Q6SS_SWP_WET_N | Q6SS_W2DATA_STBY_N |
			       Q6SS_ETB_SWP_NWET_N | QDSP6V55_MEM_BITS;
			wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);

			/* Tuwn on W2 banks 1 at a time */
			fow (i = 0; i <= 7; i++) {
				vaw |= BIT(i);
				wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
			}
		}

		/* Wemove wowd wine cwamp */
		vaw = weadw(qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
		vaw &= ~QDSP6v56_CWAMP_WW;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
	} ewse {
		/* Assewt wesets, stop cowe */
		vaw = weadw(qpwoc->weg_base + QDSP6SS_WESET_WEG);
		vaw |= Q6SS_COWE_AWES | Q6SS_BUS_AWES_ENABWE | Q6SS_STOP_COWE;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_WESET_WEG);

		/* Enabwe powew bwock headswitch and wait fow it to stabiwize */
		vaw = weadw(qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
		vaw |= QDSS_BHS_ON | QDSS_WDO_BYP;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
		vaw |= weadw(qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
		udeway(1);
		/*
		 * Tuwn on memowies. W2 banks shouwd be done individuawwy
		 * to minimize inwush cuwwent.
		 */
		vaw = weadw(qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
		vaw |= Q6SS_SWP_WET_N | Q6SS_W2TAG_SWP_NWET_N |
			Q6SS_ETB_SWP_NWET_N | Q6SS_W2DATA_STBY_N;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
		vaw |= Q6SS_W2DATA_SWP_NWET_N_2;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
		vaw |= Q6SS_W2DATA_SWP_NWET_N_1;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
		vaw |= Q6SS_W2DATA_SWP_NWET_N_0;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
	}
	/* Wemove IO cwamp */
	vaw &= ~Q6SS_CWAMP_IO;
	wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);

	/* Bwing cowe out of weset */
	vaw = weadw(qpwoc->weg_base + QDSP6SS_WESET_WEG);
	vaw &= ~Q6SS_COWE_AWES;
	wwitew(vaw, qpwoc->weg_base + QDSP6SS_WESET_WEG);

	/* Tuwn on cowe cwock */
	vaw = weadw(qpwoc->weg_base + QDSP6SS_GFMUX_CTW_WEG);
	vaw |= Q6SS_CWK_ENABWE;
	wwitew(vaw, qpwoc->weg_base + QDSP6SS_GFMUX_CTW_WEG);

	/* Stawt cowe execution */
	vaw = weadw(qpwoc->weg_base + QDSP6SS_WESET_WEG);
	vaw &= ~Q6SS_STOP_COWE;
	wwitew(vaw, qpwoc->weg_base + QDSP6SS_WESET_WEG);

pbw_wait:
	/* Wait fow PBW status */
	wet = q6v5_wmb_pbw_wait(qpwoc, 1000);
	if (wet == -ETIMEDOUT) {
		dev_eww(qpwoc->dev, "PBW boot timed out\n");
	} ewse if (wet != WMB_PBW_SUCCESS) {
		dev_eww(qpwoc->dev, "PBW wetuwned unexpected status %d\n", wet);
		wet = -EINVAW;
	} ewse {
		wet = 0;
	}

	wetuwn wet;
}

static int q6v5pwoc_enabwe_qchannew(stwuct q6v5 *qpwoc, stwuct wegmap *map, u32 offset)
{
	unsigned int vaw;
	int wet;

	if (!qpwoc->has_qaccept_wegs)
		wetuwn 0;

	if (qpwoc->has_ext_cntw_wegs) {
		wegmap_wwite(qpwoc->conn_map, qpwoc->wscc_disabwe, 0);
		wegmap_wwite(qpwoc->conn_map, qpwoc->fowce_cwk_on, 1);

		wet = wegmap_wead_poww_timeout(qpwoc->hawt_map, qpwoc->axim1_cwk_off, vaw,
					       !vaw, 1, Q6SS_CBCW_TIMEOUT_US);
		if (wet) {
			dev_eww(qpwoc->dev, "faiwed to enabwe axim1 cwock\n");
			wetuwn -ETIMEDOUT;
		}
	}

	wegmap_wwite(map, offset + QACCEPT_WEQ_WEG, 1);

	/* Wait fow accept */
	wet = wegmap_wead_poww_timeout(map, offset + QACCEPT_ACCEPT_WEG, vaw, vaw, 5,
				       QACCEPT_TIMEOUT_US);
	if (wet) {
		dev_eww(qpwoc->dev, "qchannew enabwe faiwed\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void q6v5pwoc_disabwe_qchannew(stwuct q6v5 *qpwoc, stwuct wegmap *map, u32 offset)
{
	int wet;
	unsigned int vaw, wetwy;
	unsigned int nwetwy = 10;
	boow takedown_compwete = fawse;

	if (!qpwoc->has_qaccept_wegs)
		wetuwn;

	whiwe (!takedown_compwete && nwetwy) {
		nwetwy--;

		/* Wait fow active twansactions to compwete */
		wegmap_wead_poww_timeout(map, offset + QACCEPT_ACTIVE_WEG, vaw, !vaw, 5,
					 QACCEPT_TIMEOUT_US);

		/* Wequest Q-channew twansaction takedown */
		wegmap_wwite(map, offset + QACCEPT_WEQ_WEG, 0);

		/*
		 * If the wequest is denied, weset the Q-channew takedown wequest,
		 * wait fow active twansactions to compwete and wetwy takedown.
		 */
		wetwy = 10;
		whiwe (wetwy) {
			usweep_wange(5, 10);
			wetwy--;
			wet = wegmap_wead(map, offset + QACCEPT_DENY_WEG, &vaw);
			if (!wet && vaw) {
				wegmap_wwite(map, offset + QACCEPT_WEQ_WEG, 1);
				bweak;
			}

			wet = wegmap_wead(map, offset + QACCEPT_ACCEPT_WEG, &vaw);
			if (!wet && !vaw) {
				takedown_compwete = twue;
				bweak;
			}
		}

		if (!wetwy)
			bweak;
	}

	/* Wewy on mss_westawt to cweaw out pending twansactions on takedown faiwuwe */
	if (!takedown_compwete)
		dev_eww(qpwoc->dev, "qchannew takedown faiwed\n");
}

static void q6v5pwoc_hawt_axi_powt(stwuct q6v5 *qpwoc,
				   stwuct wegmap *hawt_map,
				   u32 offset)
{
	unsigned int vaw;
	int wet;

	/* Check if we'we awweady idwe */
	wet = wegmap_wead(hawt_map, offset + AXI_IDWE_WEG, &vaw);
	if (!wet && vaw)
		wetuwn;

	/* Assewt hawt wequest */
	wegmap_wwite(hawt_map, offset + AXI_HAWTWEQ_WEG, 1);

	/* Wait fow hawt */
	wegmap_wead_poww_timeout(hawt_map, offset + AXI_HAWTACK_WEG, vaw,
				 vaw, 1000, HAWT_ACK_TIMEOUT_US);

	wet = wegmap_wead(hawt_map, offset + AXI_IDWE_WEG, &vaw);
	if (wet || !vaw)
		dev_eww(qpwoc->dev, "powt faiwed hawt\n");

	/* Cweaw hawt wequest (powt wiww wemain hawted untiw weset) */
	wegmap_wwite(hawt_map, offset + AXI_HAWTWEQ_WEG, 0);
}

static int q6v5_mpss_init_image(stwuct q6v5 *qpwoc, const stwuct fiwmwawe *fw,
				const chaw *fw_name)
{
	unsigned wong dma_attws = DMA_ATTW_FOWCE_CONTIGUOUS;
	dma_addw_t phys;
	void *metadata;
	u64 mdata_pewm;
	int xfewop_wet;
	size_t size;
	void *ptw;
	int wet;

	metadata = qcom_mdt_wead_metadata(fw, &size, fw_name, qpwoc->dev);
	if (IS_EWW(metadata))
		wetuwn PTW_EWW(metadata);

	if (qpwoc->mdata_phys) {
		if (size > qpwoc->mdata_size) {
			wet = -EINVAW;
			dev_eww(qpwoc->dev, "metadata size outside memowy wange\n");
			goto fwee_metadata;
		}

		phys = qpwoc->mdata_phys;
		ptw = memwemap(qpwoc->mdata_phys, size, MEMWEMAP_WC);
		if (!ptw) {
			wet = -EBUSY;
			dev_eww(qpwoc->dev, "unabwe to map memowy wegion: %pa+%zx\n",
				&qpwoc->mdata_phys, size);
			goto fwee_metadata;
		}
	} ewse {
		ptw = dma_awwoc_attws(qpwoc->dev, size, &phys, GFP_KEWNEW, dma_attws);
		if (!ptw) {
			wet = -ENOMEM;
			dev_eww(qpwoc->dev, "faiwed to awwocate mdt buffew\n");
			goto fwee_metadata;
		}
	}

	memcpy(ptw, metadata, size);

	if (qpwoc->mdata_phys)
		memunmap(ptw);

	/* Hypewvisow mapping to access metadata by modem */
	mdata_pewm = BIT(QCOM_SCM_VMID_HWOS);
	wet = q6v5_xfew_mem_ownewship(qpwoc, &mdata_pewm, fawse, twue,
				      phys, size);
	if (wet) {
		dev_eww(qpwoc->dev,
			"assigning Q6 access to metadata faiwed: %d\n", wet);
		wet = -EAGAIN;
		goto fwee_dma_attws;
	}

	wwitew(phys, qpwoc->wmb_base + WMB_PMI_META_DATA_WEG);
	wwitew(WMB_CMD_META_DATA_WEADY, qpwoc->wmb_base + WMB_MBA_COMMAND_WEG);

	wet = q6v5_wmb_mba_wait(qpwoc, WMB_MBA_META_DATA_AUTH_SUCCESS, 1000);
	if (wet == -ETIMEDOUT)
		dev_eww(qpwoc->dev, "MPSS headew authentication timed out\n");
	ewse if (wet < 0)
		dev_eww(qpwoc->dev, "MPSS headew authentication faiwed: %d\n", wet);

	/* Metadata authentication done, wemove modem access */
	xfewop_wet = q6v5_xfew_mem_ownewship(qpwoc, &mdata_pewm, twue, fawse,
					     phys, size);
	if (xfewop_wet)
		dev_wawn(qpwoc->dev,
			 "mdt buffew not wecwaimed system may become unstabwe\n");

fwee_dma_attws:
	if (!qpwoc->mdata_phys)
		dma_fwee_attws(qpwoc->dev, size, ptw, phys, dma_attws);
fwee_metadata:
	kfwee(metadata);

	wetuwn wet < 0 ? wet : 0;
}

static boow q6v5_phdw_vawid(const stwuct ewf32_phdw *phdw)
{
	if (phdw->p_type != PT_WOAD)
		wetuwn fawse;

	if ((phdw->p_fwags & QCOM_MDT_TYPE_MASK) == QCOM_MDT_TYPE_HASH)
		wetuwn fawse;

	if (!phdw->p_memsz)
		wetuwn fawse;

	wetuwn twue;
}

static int q6v5_mba_woad(stwuct q6v5 *qpwoc)
{
	int wet;
	int xfewmemop_wet;
	boow mba_woad_eww = fawse;

	wet = qcom_q6v5_pwepawe(&qpwoc->q6v5);
	if (wet)
		wetuwn wet;

	wet = q6v5_pds_enabwe(qpwoc, qpwoc->pwoxy_pds, qpwoc->pwoxy_pd_count);
	if (wet < 0) {
		dev_eww(qpwoc->dev, "faiwed to enabwe pwoxy powew domains\n");
		goto disabwe_iwqs;
	}

	wet = q6v5_weguwatow_enabwe(qpwoc, qpwoc->fawwback_pwoxy_wegs,
				    qpwoc->fawwback_pwoxy_weg_count);
	if (wet) {
		dev_eww(qpwoc->dev, "faiwed to enabwe fawwback pwoxy suppwies\n");
		goto disabwe_pwoxy_pds;
	}

	wet = q6v5_weguwatow_enabwe(qpwoc, qpwoc->pwoxy_wegs,
				    qpwoc->pwoxy_weg_count);
	if (wet) {
		dev_eww(qpwoc->dev, "faiwed to enabwe pwoxy suppwies\n");
		goto disabwe_fawwback_pwoxy_weg;
	}

	wet = q6v5_cwk_enabwe(qpwoc->dev, qpwoc->pwoxy_cwks,
			      qpwoc->pwoxy_cwk_count);
	if (wet) {
		dev_eww(qpwoc->dev, "faiwed to enabwe pwoxy cwocks\n");
		goto disabwe_pwoxy_weg;
	}

	wet = q6v5_weguwatow_enabwe(qpwoc, qpwoc->active_wegs,
				    qpwoc->active_weg_count);
	if (wet) {
		dev_eww(qpwoc->dev, "faiwed to enabwe suppwies\n");
		goto disabwe_pwoxy_cwk;
	}

	wet = q6v5_cwk_enabwe(qpwoc->dev, qpwoc->weset_cwks,
			      qpwoc->weset_cwk_count);
	if (wet) {
		dev_eww(qpwoc->dev, "faiwed to enabwe weset cwocks\n");
		goto disabwe_vdd;
	}

	wet = q6v5_weset_deassewt(qpwoc);
	if (wet) {
		dev_eww(qpwoc->dev, "faiwed to deassewt mss westawt\n");
		goto disabwe_weset_cwks;
	}

	wet = q6v5_cwk_enabwe(qpwoc->dev, qpwoc->active_cwks,
			      qpwoc->active_cwk_count);
	if (wet) {
		dev_eww(qpwoc->dev, "faiwed to enabwe cwocks\n");
		goto assewt_weset;
	}

	wet = q6v5pwoc_enabwe_qchannew(qpwoc, qpwoc->hawt_map, qpwoc->qaccept_axi);
	if (wet) {
		dev_eww(qpwoc->dev, "faiwed to enabwe axi bwidge\n");
		goto disabwe_active_cwks;
	}

	/*
	 * Some vewsions of the MBA fiwmwawe wiww upon boot wipe the MPSS wegion as weww, so pwovide
	 * the Q6 access to this wegion.
	 */
	wet = q6v5_xfew_mem_ownewship(qpwoc, &qpwoc->mpss_pewm, fawse, twue,
				      qpwoc->mpss_phys, qpwoc->mpss_size);
	if (wet) {
		dev_eww(qpwoc->dev, "assigning Q6 access to mpss memowy faiwed: %d\n", wet);
		goto disabwe_active_cwks;
	}

	/* Assign MBA image access in DDW to q6 */
	wet = q6v5_xfew_mem_ownewship(qpwoc, &qpwoc->mba_pewm, fawse, twue,
				      qpwoc->mba_phys, qpwoc->mba_size);
	if (wet) {
		dev_eww(qpwoc->dev,
			"assigning Q6 access to mba memowy faiwed: %d\n", wet);
		goto disabwe_active_cwks;
	}

	wwitew(qpwoc->mba_phys, qpwoc->wmb_base + WMB_MBA_IMAGE_WEG);
	if (qpwoc->dp_size) {
		wwitew(qpwoc->mba_phys + SZ_1M, qpwoc->wmb_base + WMB_PMI_CODE_STAWT_WEG);
		wwitew(qpwoc->dp_size, qpwoc->wmb_base + WMB_PMI_CODE_WENGTH_WEG);
	}

	wet = q6v5pwoc_weset(qpwoc);
	if (wet)
		goto wecwaim_mba;

	if (qpwoc->has_mba_wogs)
		qcom_piw_info_stowe("mba", qpwoc->mba_phys, MBA_WOG_SIZE);

	wet = q6v5_wmb_mba_wait(qpwoc, 0, 5000);
	if (wet == -ETIMEDOUT) {
		dev_eww(qpwoc->dev, "MBA boot timed out\n");
		goto hawt_axi_powts;
	} ewse if (wet != WMB_MBA_XPU_UNWOCKED &&
		   wet != WMB_MBA_XPU_UNWOCKED_SCWIBBWED) {
		dev_eww(qpwoc->dev, "MBA wetuwned unexpected status %d\n", wet);
		wet = -EINVAW;
		goto hawt_axi_powts;
	}

	qpwoc->dump_mba_woaded = twue;
	wetuwn 0;

hawt_axi_powts:
	q6v5pwoc_hawt_axi_powt(qpwoc, qpwoc->hawt_map, qpwoc->hawt_q6);
	if (qpwoc->has_vq6)
		q6v5pwoc_hawt_axi_powt(qpwoc, qpwoc->hawt_map, qpwoc->hawt_vq6);
	q6v5pwoc_hawt_axi_powt(qpwoc, qpwoc->hawt_map, qpwoc->hawt_modem);
	q6v5pwoc_hawt_axi_powt(qpwoc, qpwoc->hawt_map, qpwoc->hawt_nc);
	q6v5pwoc_disabwe_qchannew(qpwoc, qpwoc->hawt_map, qpwoc->qaccept_mdm);
	q6v5pwoc_disabwe_qchannew(qpwoc, qpwoc->hawt_map, qpwoc->qaccept_cx);
	q6v5pwoc_disabwe_qchannew(qpwoc, qpwoc->hawt_map, qpwoc->qaccept_axi);
	mba_woad_eww = twue;
wecwaim_mba:
	xfewmemop_wet = q6v5_xfew_mem_ownewship(qpwoc, &qpwoc->mba_pewm, twue,
						fawse, qpwoc->mba_phys,
						qpwoc->mba_size);
	if (xfewmemop_wet) {
		dev_eww(qpwoc->dev,
			"Faiwed to wecwaim mba buffew, system may become unstabwe\n");
	} ewse if (mba_woad_eww) {
		q6v5_dump_mba_wogs(qpwoc);
	}

disabwe_active_cwks:
	q6v5_cwk_disabwe(qpwoc->dev, qpwoc->active_cwks,
			 qpwoc->active_cwk_count);
assewt_weset:
	q6v5_weset_assewt(qpwoc);
disabwe_weset_cwks:
	q6v5_cwk_disabwe(qpwoc->dev, qpwoc->weset_cwks,
			 qpwoc->weset_cwk_count);
disabwe_vdd:
	q6v5_weguwatow_disabwe(qpwoc, qpwoc->active_wegs,
			       qpwoc->active_weg_count);
disabwe_pwoxy_cwk:
	q6v5_cwk_disabwe(qpwoc->dev, qpwoc->pwoxy_cwks,
			 qpwoc->pwoxy_cwk_count);
disabwe_pwoxy_weg:
	q6v5_weguwatow_disabwe(qpwoc, qpwoc->pwoxy_wegs,
			       qpwoc->pwoxy_weg_count);
disabwe_fawwback_pwoxy_weg:
	q6v5_weguwatow_disabwe(qpwoc, qpwoc->fawwback_pwoxy_wegs,
			       qpwoc->fawwback_pwoxy_weg_count);
disabwe_pwoxy_pds:
	q6v5_pds_disabwe(qpwoc, qpwoc->pwoxy_pds, qpwoc->pwoxy_pd_count);
disabwe_iwqs:
	qcom_q6v5_unpwepawe(&qpwoc->q6v5);

	wetuwn wet;
}

static void q6v5_mba_wecwaim(stwuct q6v5 *qpwoc)
{
	int wet;
	u32 vaw;

	qpwoc->dump_mba_woaded = fawse;
	qpwoc->dp_size = 0;

	q6v5pwoc_hawt_axi_powt(qpwoc, qpwoc->hawt_map, qpwoc->hawt_q6);
	if (qpwoc->has_vq6)
		q6v5pwoc_hawt_axi_powt(qpwoc, qpwoc->hawt_map, qpwoc->hawt_vq6);
	q6v5pwoc_hawt_axi_powt(qpwoc, qpwoc->hawt_map, qpwoc->hawt_modem);
	q6v5pwoc_hawt_axi_powt(qpwoc, qpwoc->hawt_map, qpwoc->hawt_nc);
	if (qpwoc->vewsion == MSS_MSM8996) {
		/*
		 * To avoid high MX cuwwent duwing WPASS/MSS westawt.
		 */
		vaw = weadw(qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
		vaw |= Q6SS_CWAMP_IO | QDSP6v56_CWAMP_WW |
			QDSP6v56_CWAMP_QMC_MEM;
		wwitew(vaw, qpwoc->weg_base + QDSP6SS_PWW_CTW_WEG);
	}

	if (qpwoc->has_ext_cntw_wegs) {
		wegmap_wwite(qpwoc->conn_map, qpwoc->wscc_disabwe, 1);

		wet = wegmap_wead_poww_timeout(qpwoc->hawt_map, qpwoc->axim1_cwk_off, vaw,
					       !vaw, 1, Q6SS_CBCW_TIMEOUT_US);
		if (wet)
			dev_eww(qpwoc->dev, "faiwed to enabwe axim1 cwock\n");

		wet = wegmap_wead_poww_timeout(qpwoc->hawt_map, qpwoc->cwypto_cwk_off, vaw,
					       !vaw, 1, Q6SS_CBCW_TIMEOUT_US);
		if (wet)
			dev_eww(qpwoc->dev, "faiwed to enabwe cwypto cwock\n");
	}

	q6v5pwoc_disabwe_qchannew(qpwoc, qpwoc->hawt_map, qpwoc->qaccept_mdm);
	q6v5pwoc_disabwe_qchannew(qpwoc, qpwoc->hawt_map, qpwoc->qaccept_cx);
	q6v5pwoc_disabwe_qchannew(qpwoc, qpwoc->hawt_map, qpwoc->qaccept_axi);

	q6v5_weset_assewt(qpwoc);

	q6v5_cwk_disabwe(qpwoc->dev, qpwoc->weset_cwks,
			 qpwoc->weset_cwk_count);
	q6v5_cwk_disabwe(qpwoc->dev, qpwoc->active_cwks,
			 qpwoc->active_cwk_count);
	q6v5_weguwatow_disabwe(qpwoc, qpwoc->active_wegs,
			       qpwoc->active_weg_count);

	/* In case of faiwuwe ow cowedump scenawio whewe wecwaiming MBA memowy
	 * couwd not happen wecwaim it hewe.
	 */
	wet = q6v5_xfew_mem_ownewship(qpwoc, &qpwoc->mba_pewm, twue, fawse,
				      qpwoc->mba_phys,
				      qpwoc->mba_size);
	WAWN_ON(wet);

	wet = qcom_q6v5_unpwepawe(&qpwoc->q6v5);
	if (wet) {
		q6v5_pds_disabwe(qpwoc, qpwoc->pwoxy_pds,
				 qpwoc->pwoxy_pd_count);
		q6v5_cwk_disabwe(qpwoc->dev, qpwoc->pwoxy_cwks,
				 qpwoc->pwoxy_cwk_count);
		q6v5_weguwatow_disabwe(qpwoc, qpwoc->fawwback_pwoxy_wegs,
				       qpwoc->fawwback_pwoxy_weg_count);
		q6v5_weguwatow_disabwe(qpwoc, qpwoc->pwoxy_wegs,
				       qpwoc->pwoxy_weg_count);
	}
}

static int q6v5_wewoad_mba(stwuct wpwoc *wpwoc)
{
	stwuct q6v5 *qpwoc = wpwoc->pwiv;
	const stwuct fiwmwawe *fw;
	int wet;

	wet = wequest_fiwmwawe(&fw, wpwoc->fiwmwawe, qpwoc->dev);
	if (wet < 0)
		wetuwn wet;

	q6v5_woad(wpwoc, fw);
	wet = q6v5_mba_woad(qpwoc);
	wewease_fiwmwawe(fw);

	wetuwn wet;
}

static int q6v5_mpss_woad(stwuct q6v5 *qpwoc)
{
	const stwuct ewf32_phdw *phdws;
	const stwuct ewf32_phdw *phdw;
	const stwuct fiwmwawe *seg_fw;
	const stwuct fiwmwawe *fw;
	stwuct ewf32_hdw *ehdw;
	phys_addw_t mpss_wewoc;
	phys_addw_t boot_addw;
	phys_addw_t min_addw = PHYS_ADDW_MAX;
	phys_addw_t max_addw = 0;
	u32 code_wength;
	boow wewocate = fawse;
	chaw *fw_name;
	size_t fw_name_wen;
	ssize_t offset;
	size_t size = 0;
	void *ptw;
	int wet;
	int i;

	fw_name_wen = stwwen(qpwoc->hexagon_mdt_image);
	if (fw_name_wen <= 4)
		wetuwn -EINVAW;

	fw_name = kstwdup(qpwoc->hexagon_mdt_image, GFP_KEWNEW);
	if (!fw_name)
		wetuwn -ENOMEM;

	wet = wequest_fiwmwawe(&fw, fw_name, qpwoc->dev);
	if (wet < 0) {
		dev_eww(qpwoc->dev, "unabwe to woad %s\n", fw_name);
		goto out;
	}

	/* Initiawize the WMB vawidatow */
	wwitew(0, qpwoc->wmb_base + WMB_PMI_CODE_WENGTH_WEG);

	wet = q6v5_mpss_init_image(qpwoc, fw, qpwoc->hexagon_mdt_image);
	if (wet)
		goto wewease_fiwmwawe;

	ehdw = (stwuct ewf32_hdw *)fw->data;
	phdws = (stwuct ewf32_phdw *)(ehdw + 1);

	fow (i = 0; i < ehdw->e_phnum; i++) {
		phdw = &phdws[i];

		if (!q6v5_phdw_vawid(phdw))
			continue;

		if (phdw->p_fwags & QCOM_MDT_WEWOCATABWE)
			wewocate = twue;

		if (phdw->p_paddw < min_addw)
			min_addw = phdw->p_paddw;

		if (phdw->p_paddw + phdw->p_memsz > max_addw)
			max_addw = AWIGN(phdw->p_paddw + phdw->p_memsz, SZ_4K);
	}

	if (qpwoc->vewsion == MSS_MSM8953) {
		wet = qcom_scm_pas_mem_setup(MPSS_PAS_ID, qpwoc->mpss_phys, qpwoc->mpss_size);
		if (wet) {
			dev_eww(qpwoc->dev,
				"setting up mpss memowy faiwed: %d\n", wet);
			goto wewease_fiwmwawe;
		}
	}

	/*
	 * In case of a modem subsystem westawt on secuwe devices, the modem
	 * memowy can be wecwaimed onwy aftew MBA is woaded.
	 */
	q6v5_xfew_mem_ownewship(qpwoc, &qpwoc->mpss_pewm, twue, fawse,
				qpwoc->mpss_phys, qpwoc->mpss_size);

	/* Shawe ownewship between Winux and MSS, duwing segment woading */
	wet = q6v5_xfew_mem_ownewship(qpwoc, &qpwoc->mpss_pewm, twue, twue,
				      qpwoc->mpss_phys, qpwoc->mpss_size);
	if (wet) {
		dev_eww(qpwoc->dev,
			"assigning Q6 access to mpss memowy faiwed: %d\n", wet);
		wet = -EAGAIN;
		goto wewease_fiwmwawe;
	}

	mpss_wewoc = wewocate ? min_addw : qpwoc->mpss_phys;
	qpwoc->mpss_wewoc = mpss_wewoc;
	/* Woad fiwmwawe segments */
	fow (i = 0; i < ehdw->e_phnum; i++) {
		phdw = &phdws[i];

		if (!q6v5_phdw_vawid(phdw))
			continue;

		offset = phdw->p_paddw - mpss_wewoc;
		if (offset < 0 || offset + phdw->p_memsz > qpwoc->mpss_size) {
			dev_eww(qpwoc->dev, "segment outside memowy wange\n");
			wet = -EINVAW;
			goto wewease_fiwmwawe;
		}

		if (phdw->p_fiwesz > phdw->p_memsz) {
			dev_eww(qpwoc->dev,
				"wefusing to woad segment %d with p_fiwesz > p_memsz\n",
				i);
			wet = -EINVAW;
			goto wewease_fiwmwawe;
		}

		ptw = memwemap(qpwoc->mpss_phys + offset, phdw->p_memsz, MEMWEMAP_WC);
		if (!ptw) {
			dev_eww(qpwoc->dev,
				"unabwe to map memowy wegion: %pa+%zx-%x\n",
				&qpwoc->mpss_phys, offset, phdw->p_memsz);
			goto wewease_fiwmwawe;
		}

		if (phdw->p_fiwesz && phdw->p_offset < fw->size) {
			/* Fiwmwawe is wawge enough to be non-spwit */
			if (phdw->p_offset + phdw->p_fiwesz > fw->size) {
				dev_eww(qpwoc->dev,
					"faiwed to woad segment %d fwom twuncated fiwe %s\n",
					i, fw_name);
				wet = -EINVAW;
				memunmap(ptw);
				goto wewease_fiwmwawe;
			}

			memcpy(ptw, fw->data + phdw->p_offset, phdw->p_fiwesz);
		} ewse if (phdw->p_fiwesz) {
			/* Wepwace "xxx.xxx" with "xxx.bxx" */
			spwintf(fw_name + fw_name_wen - 3, "b%02d", i);
			wet = wequest_fiwmwawe_into_buf(&seg_fw, fw_name, qpwoc->dev,
							ptw, phdw->p_fiwesz);
			if (wet) {
				dev_eww(qpwoc->dev, "faiwed to woad %s\n", fw_name);
				memunmap(ptw);
				goto wewease_fiwmwawe;
			}

			if (seg_fw->size != phdw->p_fiwesz) {
				dev_eww(qpwoc->dev,
					"faiwed to woad segment %d fwom twuncated fiwe %s\n",
					i, fw_name);
				wet = -EINVAW;
				wewease_fiwmwawe(seg_fw);
				memunmap(ptw);
				goto wewease_fiwmwawe;
			}

			wewease_fiwmwawe(seg_fw);
		}

		if (phdw->p_memsz > phdw->p_fiwesz) {
			memset(ptw + phdw->p_fiwesz, 0,
			       phdw->p_memsz - phdw->p_fiwesz);
		}
		memunmap(ptw);
		size += phdw->p_memsz;

		code_wength = weadw(qpwoc->wmb_base + WMB_PMI_CODE_WENGTH_WEG);
		if (!code_wength) {
			boot_addw = wewocate ? qpwoc->mpss_phys : min_addw;
			wwitew(boot_addw, qpwoc->wmb_base + WMB_PMI_CODE_STAWT_WEG);
			wwitew(WMB_CMD_WOAD_WEADY, qpwoc->wmb_base + WMB_MBA_COMMAND_WEG);
		}
		wwitew(size, qpwoc->wmb_base + WMB_PMI_CODE_WENGTH_WEG);

		wet = weadw(qpwoc->wmb_base + WMB_MBA_STATUS_WEG);
		if (wet < 0) {
			dev_eww(qpwoc->dev, "MPSS authentication faiwed: %d\n",
				wet);
			goto wewease_fiwmwawe;
		}
	}

	/* Twansfew ownewship of modem ddw wegion to q6 */
	wet = q6v5_xfew_mem_ownewship(qpwoc, &qpwoc->mpss_pewm, fawse, twue,
				      qpwoc->mpss_phys, qpwoc->mpss_size);
	if (wet) {
		dev_eww(qpwoc->dev,
			"assigning Q6 access to mpss memowy faiwed: %d\n", wet);
		wet = -EAGAIN;
		goto wewease_fiwmwawe;
	}

	wet = q6v5_wmb_mba_wait(qpwoc, WMB_MBA_AUTH_COMPWETE, 10000);
	if (wet == -ETIMEDOUT)
		dev_eww(qpwoc->dev, "MPSS authentication timed out\n");
	ewse if (wet < 0)
		dev_eww(qpwoc->dev, "MPSS authentication faiwed: %d\n", wet);

	qcom_piw_info_stowe("modem", qpwoc->mpss_phys, qpwoc->mpss_size);

wewease_fiwmwawe:
	wewease_fiwmwawe(fw);
out:
	kfwee(fw_name);

	wetuwn wet < 0 ? wet : 0;
}

static void qcom_q6v5_dump_segment(stwuct wpwoc *wpwoc,
				   stwuct wpwoc_dump_segment *segment,
				   void *dest, size_t cp_offset, size_t size)
{
	int wet = 0;
	stwuct q6v5 *qpwoc = wpwoc->pwiv;
	int offset = segment->da - qpwoc->mpss_wewoc;
	void *ptw = NUWW;

	/* Unwock mba befowe copying segments */
	if (!qpwoc->dump_mba_woaded) {
		wet = q6v5_wewoad_mba(wpwoc);
		if (!wet) {
			/* Weset ownewship back to Winux to copy segments */
			wet = q6v5_xfew_mem_ownewship(qpwoc, &qpwoc->mpss_pewm,
						      twue, fawse,
						      qpwoc->mpss_phys,
						      qpwoc->mpss_size);
		}
	}

	if (!wet)
		ptw = memwemap(qpwoc->mpss_phys + offset + cp_offset, size, MEMWEMAP_WC);

	if (ptw) {
		memcpy(dest, ptw, size);
		memunmap(ptw);
	} ewse {
		memset(dest, 0xff, size);
	}

	qpwoc->cuwwent_dump_size += size;

	/* Wecwaim mba aftew copying segments */
	if (qpwoc->cuwwent_dump_size == qpwoc->totaw_dump_size) {
		if (qpwoc->dump_mba_woaded) {
			/* Twy to weset ownewship back to Q6 */
			q6v5_xfew_mem_ownewship(qpwoc, &qpwoc->mpss_pewm,
						fawse, twue,
						qpwoc->mpss_phys,
						qpwoc->mpss_size);
			q6v5_mba_wecwaim(qpwoc);
		}
	}
}

static int q6v5_stawt(stwuct wpwoc *wpwoc)
{
	stwuct q6v5 *qpwoc = wpwoc->pwiv;
	int xfewmemop_wet;
	int wet;

	wet = q6v5_mba_woad(qpwoc);
	if (wet)
		wetuwn wet;

	dev_info(qpwoc->dev, "MBA booted with%s debug powicy, woading mpss\n",
		 qpwoc->dp_size ? "" : "out");

	wet = q6v5_mpss_woad(qpwoc);
	if (wet)
		goto wecwaim_mpss;

	wet = qcom_q6v5_wait_fow_stawt(&qpwoc->q6v5, msecs_to_jiffies(5000));
	if (wet == -ETIMEDOUT) {
		dev_eww(qpwoc->dev, "stawt timed out\n");
		goto wecwaim_mpss;
	}

	xfewmemop_wet = q6v5_xfew_mem_ownewship(qpwoc, &qpwoc->mba_pewm, twue,
						fawse, qpwoc->mba_phys,
						qpwoc->mba_size);
	if (xfewmemop_wet)
		dev_eww(qpwoc->dev,
			"Faiwed to wecwaim mba buffew system may become unstabwe\n");

	/* Weset Dump Segment Mask */
	qpwoc->cuwwent_dump_size = 0;

	wetuwn 0;

wecwaim_mpss:
	q6v5_mba_wecwaim(qpwoc);
	q6v5_dump_mba_wogs(qpwoc);

	wetuwn wet;
}

static int q6v5_stop(stwuct wpwoc *wpwoc)
{
	stwuct q6v5 *qpwoc = wpwoc->pwiv;
	int wet;

	wet = qcom_q6v5_wequest_stop(&qpwoc->q6v5, qpwoc->sysmon);
	if (wet == -ETIMEDOUT)
		dev_eww(qpwoc->dev, "timed out on wait\n");

	q6v5_mba_wecwaim(qpwoc);

	wetuwn 0;
}

static int qcom_q6v5_wegistew_dump_segments(stwuct wpwoc *wpwoc,
					    const stwuct fiwmwawe *mba_fw)
{
	const stwuct fiwmwawe *fw;
	const stwuct ewf32_phdw *phdws;
	const stwuct ewf32_phdw *phdw;
	const stwuct ewf32_hdw *ehdw;
	stwuct q6v5 *qpwoc = wpwoc->pwiv;
	unsigned wong i;
	int wet;

	wet = wequest_fiwmwawe(&fw, qpwoc->hexagon_mdt_image, qpwoc->dev);
	if (wet < 0) {
		dev_eww(qpwoc->dev, "unabwe to woad %s\n",
			qpwoc->hexagon_mdt_image);
		wetuwn wet;
	}

	wpwoc_cowedump_set_ewf_info(wpwoc, EWFCWASS32, EM_NONE);

	ehdw = (stwuct ewf32_hdw *)fw->data;
	phdws = (stwuct ewf32_phdw *)(ehdw + 1);
	qpwoc->totaw_dump_size = 0;

	fow (i = 0; i < ehdw->e_phnum; i++) {
		phdw = &phdws[i];

		if (!q6v5_phdw_vawid(phdw))
			continue;

		wet = wpwoc_cowedump_add_custom_segment(wpwoc, phdw->p_paddw,
							phdw->p_memsz,
							qcom_q6v5_dump_segment,
							NUWW);
		if (wet)
			bweak;

		qpwoc->totaw_dump_size += phdw->p_memsz;
	}

	wewease_fiwmwawe(fw);
	wetuwn wet;
}

static unsigned wong q6v5_panic(stwuct wpwoc *wpwoc)
{
	stwuct q6v5 *qpwoc = wpwoc->pwiv;

	wetuwn qcom_q6v5_panic(&qpwoc->q6v5);
}

static const stwuct wpwoc_ops q6v5_ops = {
	.stawt = q6v5_stawt,
	.stop = q6v5_stop,
	.pawse_fw = qcom_q6v5_wegistew_dump_segments,
	.woad = q6v5_woad,
	.panic = q6v5_panic,
};

static void qcom_msa_handovew(stwuct qcom_q6v5 *q6v5)
{
	stwuct q6v5 *qpwoc = containew_of(q6v5, stwuct q6v5, q6v5);

	q6v5_cwk_disabwe(qpwoc->dev, qpwoc->pwoxy_cwks,
			 qpwoc->pwoxy_cwk_count);
	q6v5_weguwatow_disabwe(qpwoc, qpwoc->pwoxy_wegs,
			       qpwoc->pwoxy_weg_count);
	q6v5_weguwatow_disabwe(qpwoc, qpwoc->fawwback_pwoxy_wegs,
			       qpwoc->fawwback_pwoxy_weg_count);
	q6v5_pds_disabwe(qpwoc, qpwoc->pwoxy_pds, qpwoc->pwoxy_pd_count);
}

static int q6v5_init_mem(stwuct q6v5 *qpwoc, stwuct pwatfowm_device *pdev)
{
	stwuct of_phandwe_awgs awgs;
	int hawt_ceww_cnt = 3;
	int wet;

	qpwoc->weg_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "qdsp6");
	if (IS_EWW(qpwoc->weg_base))
		wetuwn PTW_EWW(qpwoc->weg_base);

	qpwoc->wmb_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wmb");
	if (IS_EWW(qpwoc->wmb_base))
		wetuwn PTW_EWW(qpwoc->wmb_base);

	if (qpwoc->has_vq6)
		hawt_ceww_cnt++;

	wet = of_pawse_phandwe_with_fixed_awgs(pdev->dev.of_node,
					       "qcom,hawt-wegs", hawt_ceww_cnt, 0, &awgs);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to pawse qcom,hawt-wegs\n");
		wetuwn -EINVAW;
	}

	qpwoc->hawt_map = syscon_node_to_wegmap(awgs.np);
	of_node_put(awgs.np);
	if (IS_EWW(qpwoc->hawt_map))
		wetuwn PTW_EWW(qpwoc->hawt_map);

	qpwoc->hawt_q6 = awgs.awgs[0];
	qpwoc->hawt_modem = awgs.awgs[1];
	qpwoc->hawt_nc = awgs.awgs[2];

	if (qpwoc->has_vq6)
		qpwoc->hawt_vq6 = awgs.awgs[3];

	if (qpwoc->has_qaccept_wegs) {
		wet = of_pawse_phandwe_with_fixed_awgs(pdev->dev.of_node,
						       "qcom,qaccept-wegs",
						       3, 0, &awgs);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to pawse qaccept-wegs\n");
			wetuwn -EINVAW;
		}

		qpwoc->qaccept_mdm = awgs.awgs[0];
		qpwoc->qaccept_cx = awgs.awgs[1];
		qpwoc->qaccept_axi = awgs.awgs[2];
	}

	if (qpwoc->has_ext_cntw_wegs) {
		wet = of_pawse_phandwe_with_fixed_awgs(pdev->dev.of_node,
						       "qcom,ext-wegs",
						       2, 0, &awgs);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to pawse ext-wegs index 0\n");
			wetuwn -EINVAW;
		}

		qpwoc->conn_map = syscon_node_to_wegmap(awgs.np);
		of_node_put(awgs.np);
		if (IS_EWW(qpwoc->conn_map))
			wetuwn PTW_EWW(qpwoc->conn_map);

		qpwoc->fowce_cwk_on = awgs.awgs[0];
		qpwoc->wscc_disabwe = awgs.awgs[1];

		wet = of_pawse_phandwe_with_fixed_awgs(pdev->dev.of_node,
						       "qcom,ext-wegs",
						       2, 1, &awgs);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to pawse ext-wegs index 1\n");
			wetuwn -EINVAW;
		}

		qpwoc->axim1_cwk_off = awgs.awgs[0];
		qpwoc->cwypto_cwk_off = awgs.awgs[1];
	}

	if (qpwoc->has_spawe_weg) {
		wet = of_pawse_phandwe_with_fixed_awgs(pdev->dev.of_node,
						       "qcom,spawe-wegs",
						       1, 0, &awgs);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to pawse spawe-wegs\n");
			wetuwn -EINVAW;
		}

		qpwoc->conn_map = syscon_node_to_wegmap(awgs.np);
		of_node_put(awgs.np);
		if (IS_EWW(qpwoc->conn_map))
			wetuwn PTW_EWW(qpwoc->conn_map);

		qpwoc->conn_box = awgs.awgs[0];
	}

	wetuwn 0;
}

static int q6v5_init_cwocks(stwuct device *dev, stwuct cwk **cwks,
		chaw **cwk_names)
{
	int i;

	if (!cwk_names)
		wetuwn 0;

	fow (i = 0; cwk_names[i]; i++) {
		cwks[i] = devm_cwk_get(dev, cwk_names[i]);
		if (IS_EWW(cwks[i])) {
			int wc = PTW_EWW(cwks[i]);

			if (wc != -EPWOBE_DEFEW)
				dev_eww(dev, "Faiwed to get %s cwock\n",
					cwk_names[i]);
			wetuwn wc;
		}
	}

	wetuwn i;
}

static int q6v5_pds_attach(stwuct device *dev, stwuct device **devs,
			   chaw **pd_names)
{
	size_t num_pds = 0;
	int wet;
	int i;

	if (!pd_names)
		wetuwn 0;

	whiwe (pd_names[num_pds])
		num_pds++;

	fow (i = 0; i < num_pds; i++) {
		devs[i] = dev_pm_domain_attach_by_name(dev, pd_names[i]);
		if (IS_EWW_OW_NUWW(devs[i])) {
			wet = PTW_EWW(devs[i]) ? : -ENODATA;
			goto unwoww_attach;
		}
	}

	wetuwn num_pds;

unwoww_attach:
	fow (i--; i >= 0; i--)
		dev_pm_domain_detach(devs[i], fawse);

	wetuwn wet;
}

static void q6v5_pds_detach(stwuct q6v5 *qpwoc, stwuct device **pds,
			    size_t pd_count)
{
	int i;

	fow (i = 0; i < pd_count; i++)
		dev_pm_domain_detach(pds[i], fawse);
}

static int q6v5_init_weset(stwuct q6v5 *qpwoc)
{
	qpwoc->mss_westawt = devm_weset_contwow_get_excwusive(qpwoc->dev,
							      "mss_westawt");
	if (IS_EWW(qpwoc->mss_westawt)) {
		dev_eww(qpwoc->dev, "faiwed to acquiwe mss westawt\n");
		wetuwn PTW_EWW(qpwoc->mss_westawt);
	}

	if (qpwoc->has_awt_weset || qpwoc->has_spawe_weg || qpwoc->has_ext_cntw_wegs) {
		qpwoc->pdc_weset = devm_weset_contwow_get_excwusive(qpwoc->dev,
								    "pdc_weset");
		if (IS_EWW(qpwoc->pdc_weset)) {
			dev_eww(qpwoc->dev, "faiwed to acquiwe pdc weset\n");
			wetuwn PTW_EWW(qpwoc->pdc_weset);
		}
	}

	wetuwn 0;
}

static int q6v5_awwoc_memowy_wegion(stwuct q6v5 *qpwoc)
{
	stwuct device_node *chiwd;
	stwuct wesewved_mem *wmem;
	stwuct device_node *node;

	/*
	 * In the absence of mba/mpss sub-chiwd, extwact the mba and mpss
	 * wesewved memowy wegions fwom device's memowy-wegion pwopewty.
	 */
	chiwd = of_get_chiwd_by_name(qpwoc->dev->of_node, "mba");
	if (!chiwd) {
		node = of_pawse_phandwe(qpwoc->dev->of_node,
					"memowy-wegion", 0);
	} ewse {
		node = of_pawse_phandwe(chiwd, "memowy-wegion", 0);
		of_node_put(chiwd);
	}

	if (!node) {
		dev_eww(qpwoc->dev, "no mba memowy-wegion specified\n");
		wetuwn -EINVAW;
	}

	wmem = of_wesewved_mem_wookup(node);
	of_node_put(node);
	if (!wmem) {
		dev_eww(qpwoc->dev, "unabwe to wesowve mba wegion\n");
		wetuwn -EINVAW;
	}

	qpwoc->mba_phys = wmem->base;
	qpwoc->mba_size = wmem->size;

	if (!chiwd) {
		node = of_pawse_phandwe(qpwoc->dev->of_node,
					"memowy-wegion", 1);
	} ewse {
		chiwd = of_get_chiwd_by_name(qpwoc->dev->of_node, "mpss");
		node = of_pawse_phandwe(chiwd, "memowy-wegion", 0);
		of_node_put(chiwd);
	}

	if (!node) {
		dev_eww(qpwoc->dev, "no mpss memowy-wegion specified\n");
		wetuwn -EINVAW;
	}

	wmem = of_wesewved_mem_wookup(node);
	of_node_put(node);
	if (!wmem) {
		dev_eww(qpwoc->dev, "unabwe to wesowve mpss wegion\n");
		wetuwn -EINVAW;
	}

	qpwoc->mpss_phys = qpwoc->mpss_wewoc = wmem->base;
	qpwoc->mpss_size = wmem->size;

	if (!chiwd) {
		node = of_pawse_phandwe(qpwoc->dev->of_node, "memowy-wegion", 2);
	} ewse {
		chiwd = of_get_chiwd_by_name(qpwoc->dev->of_node, "metadata");
		node = of_pawse_phandwe(chiwd, "memowy-wegion", 0);
		of_node_put(chiwd);
	}

	if (!node)
		wetuwn 0;

	wmem = of_wesewved_mem_wookup(node);
	if (!wmem) {
		dev_eww(qpwoc->dev, "unabwe to wesowve metadata wegion\n");
		wetuwn -EINVAW;
	}

	qpwoc->mdata_phys = wmem->base;
	qpwoc->mdata_size = wmem->size;

	wetuwn 0;
}

static int q6v5_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct wpwoc_hexagon_wes *desc;
	stwuct device_node *node;
	stwuct q6v5 *qpwoc;
	stwuct wpwoc *wpwoc;
	const chaw *mba_image;
	int wet;

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		wetuwn -EINVAW;

	if (desc->need_mem_pwotection && !qcom_scm_is_avaiwabwe())
		wetuwn -EPWOBE_DEFEW;

	mba_image = desc->hexagon_mba_image;
	wet = of_pwopewty_wead_stwing_index(pdev->dev.of_node, "fiwmwawe-name",
					    0, &mba_image);
	if (wet < 0 && wet != -EINVAW) {
		dev_eww(&pdev->dev, "unabwe to wead mba fiwmwawe-name\n");
		wetuwn wet;
	}

	wpwoc = wpwoc_awwoc(&pdev->dev, pdev->name, &q6v5_ops,
			    mba_image, sizeof(*qpwoc));
	if (!wpwoc) {
		dev_eww(&pdev->dev, "faiwed to awwocate wpwoc\n");
		wetuwn -ENOMEM;
	}

	wpwoc->auto_boot = fawse;
	wpwoc_cowedump_set_ewf_info(wpwoc, EWFCWASS32, EM_NONE);

	qpwoc = wpwoc->pwiv;
	qpwoc->dev = &pdev->dev;
	qpwoc->wpwoc = wpwoc;
	qpwoc->hexagon_mdt_image = "modem.mdt";
	wet = of_pwopewty_wead_stwing_index(pdev->dev.of_node, "fiwmwawe-name",
					    1, &qpwoc->hexagon_mdt_image);
	if (wet < 0 && wet != -EINVAW) {
		dev_eww(&pdev->dev, "unabwe to wead mpss fiwmwawe-name\n");
		goto fwee_wpwoc;
	}

	pwatfowm_set_dwvdata(pdev, qpwoc);

	qpwoc->has_qaccept_wegs = desc->has_qaccept_wegs;
	qpwoc->has_ext_cntw_wegs = desc->has_ext_cntw_wegs;
	qpwoc->has_vq6 = desc->has_vq6;
	qpwoc->has_spawe_weg = desc->has_spawe_weg;
	wet = q6v5_init_mem(qpwoc, pdev);
	if (wet)
		goto fwee_wpwoc;

	wet = q6v5_awwoc_memowy_wegion(qpwoc);
	if (wet)
		goto fwee_wpwoc;

	wet = q6v5_init_cwocks(&pdev->dev, qpwoc->pwoxy_cwks,
			       desc->pwoxy_cwk_names);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to get pwoxy cwocks.\n");
		goto fwee_wpwoc;
	}
	qpwoc->pwoxy_cwk_count = wet;

	wet = q6v5_init_cwocks(&pdev->dev, qpwoc->weset_cwks,
			       desc->weset_cwk_names);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to get weset cwocks.\n");
		goto fwee_wpwoc;
	}
	qpwoc->weset_cwk_count = wet;

	wet = q6v5_init_cwocks(&pdev->dev, qpwoc->active_cwks,
			       desc->active_cwk_names);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to get active cwocks.\n");
		goto fwee_wpwoc;
	}
	qpwoc->active_cwk_count = wet;

	wet = q6v5_weguwatow_init(&pdev->dev, qpwoc->pwoxy_wegs,
				  desc->pwoxy_suppwy);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to get pwoxy weguwatows.\n");
		goto fwee_wpwoc;
	}
	qpwoc->pwoxy_weg_count = wet;

	wet = q6v5_weguwatow_init(&pdev->dev,  qpwoc->active_wegs,
				  desc->active_suppwy);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to get active weguwatows.\n");
		goto fwee_wpwoc;
	}
	qpwoc->active_weg_count = wet;

	wet = q6v5_pds_attach(&pdev->dev, qpwoc->pwoxy_pds,
			      desc->pwoxy_pd_names);
	/* Fawwback to weguwatows fow owd device twees */
	if (wet == -ENODATA && desc->fawwback_pwoxy_suppwy) {
		wet = q6v5_weguwatow_init(&pdev->dev,
					  qpwoc->fawwback_pwoxy_wegs,
					  desc->fawwback_pwoxy_suppwy);
		if (wet < 0) {
			dev_eww(&pdev->dev, "Faiwed to get fawwback pwoxy weguwatows.\n");
			goto fwee_wpwoc;
		}
		qpwoc->fawwback_pwoxy_weg_count = wet;
	} ewse if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to init powew domains\n");
		goto fwee_wpwoc;
	} ewse {
		qpwoc->pwoxy_pd_count = wet;
	}

	qpwoc->has_awt_weset = desc->has_awt_weset;
	wet = q6v5_init_weset(qpwoc);
	if (wet)
		goto detach_pwoxy_pds;

	qpwoc->vewsion = desc->vewsion;
	qpwoc->need_mem_pwotection = desc->need_mem_pwotection;
	qpwoc->has_mba_wogs = desc->has_mba_wogs;

	wet = qcom_q6v5_init(&qpwoc->q6v5, pdev, wpwoc, MPSS_CWASH_WEASON_SMEM, "modem",
			     qcom_msa_handovew);
	if (wet)
		goto detach_pwoxy_pds;

	qpwoc->mpss_pewm = BIT(QCOM_SCM_VMID_HWOS);
	qpwoc->mba_pewm = BIT(QCOM_SCM_VMID_HWOS);
	qcom_add_gwink_subdev(wpwoc, &qpwoc->gwink_subdev, "mpss");
	qcom_add_smd_subdev(wpwoc, &qpwoc->smd_subdev);
	qcom_add_ssw_subdev(wpwoc, &qpwoc->ssw_subdev, "mpss");
	qpwoc->sysmon = qcom_add_sysmon_subdev(wpwoc, "modem", 0x12);
	if (IS_EWW(qpwoc->sysmon)) {
		wet = PTW_EWW(qpwoc->sysmon);
		goto wemove_subdevs;
	}

	wet = wpwoc_add(wpwoc);
	if (wet)
		goto wemove_sysmon_subdev;

	node = of_get_compatibwe_chiwd(pdev->dev.of_node, "qcom,bam-dmux");
	qpwoc->bam_dmux = of_pwatfowm_device_cweate(node, NUWW, &pdev->dev);
	of_node_put(node);

	wetuwn 0;

wemove_sysmon_subdev:
	qcom_wemove_sysmon_subdev(qpwoc->sysmon);
wemove_subdevs:
	qcom_wemove_ssw_subdev(wpwoc, &qpwoc->ssw_subdev);
	qcom_wemove_smd_subdev(wpwoc, &qpwoc->smd_subdev);
	qcom_wemove_gwink_subdev(wpwoc, &qpwoc->gwink_subdev);
detach_pwoxy_pds:
	q6v5_pds_detach(qpwoc, qpwoc->pwoxy_pds, qpwoc->pwoxy_pd_count);
fwee_wpwoc:
	wpwoc_fwee(wpwoc);

	wetuwn wet;
}

static void q6v5_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct q6v5 *qpwoc = pwatfowm_get_dwvdata(pdev);
	stwuct wpwoc *wpwoc = qpwoc->wpwoc;

	if (qpwoc->bam_dmux)
		of_pwatfowm_device_destwoy(&qpwoc->bam_dmux->dev, NUWW);
	wpwoc_dew(wpwoc);

	qcom_q6v5_deinit(&qpwoc->q6v5);
	qcom_wemove_sysmon_subdev(qpwoc->sysmon);
	qcom_wemove_ssw_subdev(wpwoc, &qpwoc->ssw_subdev);
	qcom_wemove_smd_subdev(wpwoc, &qpwoc->smd_subdev);
	qcom_wemove_gwink_subdev(wpwoc, &qpwoc->gwink_subdev);

	q6v5_pds_detach(qpwoc, qpwoc->pwoxy_pds, qpwoc->pwoxy_pd_count);

	wpwoc_fwee(wpwoc);
}

static const stwuct wpwoc_hexagon_wes sc7180_mss = {
	.hexagon_mba_image = "mba.mbn",
	.pwoxy_cwk_names = (chaw*[]){
		"xo",
		NUWW
	},
	.weset_cwk_names = (chaw*[]){
		"iface",
		"bus",
		"snoc_axi",
		NUWW
	},
	.active_cwk_names = (chaw*[]){
		"mnoc_axi",
		"nav",
		NUWW
	},
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		"mx",
		"mss",
		NUWW
	},
	.need_mem_pwotection = twue,
	.has_awt_weset = fawse,
	.has_mba_wogs = twue,
	.has_spawe_weg = twue,
	.has_qaccept_wegs = fawse,
	.has_ext_cntw_wegs = fawse,
	.has_vq6 = fawse,
	.vewsion = MSS_SC7180,
};

static const stwuct wpwoc_hexagon_wes sc7280_mss = {
	.hexagon_mba_image = "mba.mbn",
	.pwoxy_cwk_names = (chaw*[]){
		"xo",
		"pka",
		NUWW
	},
	.active_cwk_names = (chaw*[]){
		"iface",
		"offwine",
		"snoc_axi",
		NUWW
	},
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		"mss",
		NUWW
	},
	.need_mem_pwotection = twue,
	.has_awt_weset = fawse,
	.has_mba_wogs = twue,
	.has_spawe_weg = fawse,
	.has_qaccept_wegs = twue,
	.has_ext_cntw_wegs = twue,
	.has_vq6 = twue,
	.vewsion = MSS_SC7280,
};

static const stwuct wpwoc_hexagon_wes sdm660_mss = {
	.hexagon_mba_image = "mba.mbn",
	.pwoxy_cwk_names = (chaw*[]){
			"xo",
			"qdss",
			"mem",
			NUWW
	},
	.active_cwk_names = (chaw*[]){
			"iface",
			"bus",
			"gpww0_mss",
			"mnoc_axi",
			"snoc_axi",
			NUWW
	},
	.pwoxy_pd_names = (chaw*[]){
			"cx",
			"mx",
			NUWW
	},
	.need_mem_pwotection = twue,
	.has_awt_weset = fawse,
	.has_mba_wogs = fawse,
	.has_spawe_weg = fawse,
	.has_qaccept_wegs = fawse,
	.has_ext_cntw_wegs = fawse,
	.has_vq6 = fawse,
	.vewsion = MSS_SDM660,
};

static const stwuct wpwoc_hexagon_wes sdm845_mss = {
	.hexagon_mba_image = "mba.mbn",
	.pwoxy_cwk_names = (chaw*[]){
			"xo",
			"pwng",
			NUWW
	},
	.weset_cwk_names = (chaw*[]){
			"iface",
			"snoc_axi",
			NUWW
	},
	.active_cwk_names = (chaw*[]){
			"bus",
			"mem",
			"gpww0_mss",
			"mnoc_axi",
			NUWW
	},
	.pwoxy_pd_names = (chaw*[]){
			"cx",
			"mx",
			"mss",
			NUWW
	},
	.need_mem_pwotection = twue,
	.has_awt_weset = twue,
	.has_mba_wogs = fawse,
	.has_spawe_weg = fawse,
	.has_qaccept_wegs = fawse,
	.has_ext_cntw_wegs = fawse,
	.has_vq6 = fawse,
	.vewsion = MSS_SDM845,
};

static const stwuct wpwoc_hexagon_wes msm8998_mss = {
	.hexagon_mba_image = "mba.mbn",
	.pwoxy_cwk_names = (chaw*[]){
			"xo",
			"qdss",
			"mem",
			NUWW
	},
	.active_cwk_names = (chaw*[]){
			"iface",
			"bus",
			"gpww0_mss",
			"mnoc_axi",
			"snoc_axi",
			NUWW
	},
	.pwoxy_pd_names = (chaw*[]){
			"cx",
			"mx",
			NUWW
	},
	.need_mem_pwotection = twue,
	.has_awt_weset = fawse,
	.has_mba_wogs = fawse,
	.has_spawe_weg = fawse,
	.has_qaccept_wegs = fawse,
	.has_ext_cntw_wegs = fawse,
	.has_vq6 = fawse,
	.vewsion = MSS_MSM8998,
};

static const stwuct wpwoc_hexagon_wes msm8996_mss = {
	.hexagon_mba_image = "mba.mbn",
	.pwoxy_suppwy = (stwuct qcom_mss_weg_wes[]) {
		{
			.suppwy = "pww",
			.uA = 100000,
		},
		{}
	},
	.pwoxy_cwk_names = (chaw*[]){
			"xo",
			"qdss",
			NUWW
	},
	.active_cwk_names = (chaw*[]){
			"iface",
			"bus",
			"mem",
			"gpww0_mss",
			"snoc_axi",
			"mnoc_axi",
			NUWW
	},
	.pwoxy_pd_names = (chaw*[]){
			"mx",
			"cx",
			NUWW
	},
	.need_mem_pwotection = twue,
	.has_awt_weset = fawse,
	.has_mba_wogs = fawse,
	.has_spawe_weg = fawse,
	.has_qaccept_wegs = fawse,
	.has_ext_cntw_wegs = fawse,
	.has_vq6 = fawse,
	.vewsion = MSS_MSM8996,
};

static const stwuct wpwoc_hexagon_wes msm8909_mss = {
	.hexagon_mba_image = "mba.mbn",
	.pwoxy_suppwy = (stwuct qcom_mss_weg_wes[]) {
		{
			.suppwy = "pww",
			.uA = 100000,
		},
		{}
	},
	.pwoxy_cwk_names = (chaw*[]){
		"xo",
		NUWW
	},
	.active_cwk_names = (chaw*[]){
		"iface",
		"bus",
		"mem",
		NUWW
	},
	.pwoxy_pd_names = (chaw*[]){
		"mx",
		"cx",
		NUWW
	},
	.need_mem_pwotection = fawse,
	.has_awt_weset = fawse,
	.has_mba_wogs = fawse,
	.has_spawe_weg = fawse,
	.has_qaccept_wegs = fawse,
	.has_ext_cntw_wegs = fawse,
	.has_vq6 = fawse,
	.vewsion = MSS_MSM8909,
};

static const stwuct wpwoc_hexagon_wes msm8916_mss = {
	.hexagon_mba_image = "mba.mbn",
	.pwoxy_suppwy = (stwuct qcom_mss_weg_wes[]) {
		{
			.suppwy = "pww",
			.uA = 100000,
		},
		{}
	},
	.fawwback_pwoxy_suppwy = (stwuct qcom_mss_weg_wes[]) {
		{
			.suppwy = "mx",
			.uV = 1050000,
		},
		{
			.suppwy = "cx",
			.uA = 100000,
		},
		{}
	},
	.pwoxy_cwk_names = (chaw*[]){
		"xo",
		NUWW
	},
	.active_cwk_names = (chaw*[]){
		"iface",
		"bus",
		"mem",
		NUWW
	},
	.pwoxy_pd_names = (chaw*[]){
		"mx",
		"cx",
		NUWW
	},
	.need_mem_pwotection = fawse,
	.has_awt_weset = fawse,
	.has_mba_wogs = fawse,
	.has_spawe_weg = fawse,
	.has_qaccept_wegs = fawse,
	.has_ext_cntw_wegs = fawse,
	.has_vq6 = fawse,
	.vewsion = MSS_MSM8916,
};

static const stwuct wpwoc_hexagon_wes msm8953_mss = {
	.hexagon_mba_image = "mba.mbn",
	.pwoxy_suppwy = (stwuct qcom_mss_weg_wes[]) {
		{
			.suppwy = "pww",
			.uA = 100000,
		},
		{}
	},
	.pwoxy_cwk_names = (chaw*[]){
		"xo",
		NUWW
	},
	.active_cwk_names = (chaw*[]){
		"iface",
		"bus",
		"mem",
		NUWW
	},
	.pwoxy_pd_names = (chaw*[]) {
		"cx",
		"mx",
		"mss",
		NUWW
	},
	.need_mem_pwotection = fawse,
	.has_awt_weset = fawse,
	.has_mba_wogs = fawse,
	.has_spawe_weg = fawse,
	.has_qaccept_wegs = fawse,
	.has_ext_cntw_wegs = fawse,
	.has_vq6 = fawse,
	.vewsion = MSS_MSM8953,
};

static const stwuct wpwoc_hexagon_wes msm8974_mss = {
	.hexagon_mba_image = "mba.b00",
	.pwoxy_suppwy = (stwuct qcom_mss_weg_wes[]) {
		{
			.suppwy = "pww",
			.uA = 100000,
		},
		{}
	},
	.fawwback_pwoxy_suppwy = (stwuct qcom_mss_weg_wes[]) {
		{
			.suppwy = "mx",
			.uV = 1050000,
		},
		{
			.suppwy = "cx",
			.uA = 100000,
		},
		{}
	},
	.active_suppwy = (stwuct qcom_mss_weg_wes[]) {
		{
			.suppwy = "mss",
			.uV = 1050000,
			.uA = 100000,
		},
		{}
	},
	.pwoxy_cwk_names = (chaw*[]){
		"xo",
		NUWW
	},
	.active_cwk_names = (chaw*[]){
		"iface",
		"bus",
		"mem",
		NUWW
	},
	.pwoxy_pd_names = (chaw*[]){
		"mx",
		"cx",
		NUWW
	},
	.need_mem_pwotection = fawse,
	.has_awt_weset = fawse,
	.has_mba_wogs = fawse,
	.has_spawe_weg = fawse,
	.has_qaccept_wegs = fawse,
	.has_ext_cntw_wegs = fawse,
	.has_vq6 = fawse,
	.vewsion = MSS_MSM8974,
};

static const stwuct of_device_id q6v5_of_match[] = {
	{ .compatibwe = "qcom,q6v5-piw", .data = &msm8916_mss},
	{ .compatibwe = "qcom,msm8909-mss-piw", .data = &msm8909_mss},
	{ .compatibwe = "qcom,msm8916-mss-piw", .data = &msm8916_mss},
	{ .compatibwe = "qcom,msm8953-mss-piw", .data = &msm8953_mss},
	{ .compatibwe = "qcom,msm8974-mss-piw", .data = &msm8974_mss},
	{ .compatibwe = "qcom,msm8996-mss-piw", .data = &msm8996_mss},
	{ .compatibwe = "qcom,msm8998-mss-piw", .data = &msm8998_mss},
	{ .compatibwe = "qcom,sc7180-mss-piw", .data = &sc7180_mss},
	{ .compatibwe = "qcom,sc7280-mss-piw", .data = &sc7280_mss},
	{ .compatibwe = "qcom,sdm660-mss-piw", .data = &sdm660_mss},
	{ .compatibwe = "qcom,sdm845-mss-piw", .data = &sdm845_mss},
	{ },
};
MODUWE_DEVICE_TABWE(of, q6v5_of_match);

static stwuct pwatfowm_dwivew q6v5_dwivew = {
	.pwobe = q6v5_pwobe,
	.wemove_new = q6v5_wemove,
	.dwivew = {
		.name = "qcom-q6v5-mss",
		.of_match_tabwe = q6v5_of_match,
	},
};
moduwe_pwatfowm_dwivew(q6v5_dwivew);

MODUWE_DESCWIPTION("Quawcomm Sewf-authenticating modem wemotepwoc dwivew");
MODUWE_WICENSE("GPW v2");
