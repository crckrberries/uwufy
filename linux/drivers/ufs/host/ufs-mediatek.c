// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 MediaTek Inc.
 * Authows:
 *	Stanwey Chu <stanwey.chu@mediatek.com>
 *	Petew Wang <petew.wang@mediatek.com>
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_device.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_qos.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/soc/mediatek/mtk_sip_svc.h>

#incwude <ufs/ufshcd.h>
#incwude "ufshcd-pwtfwm.h"
#incwude <ufs/ufs_quiwks.h>
#incwude <ufs/unipwo.h>
#incwude "ufs-mediatek.h"

static int  ufs_mtk_config_mcq(stwuct ufs_hba *hba, boow iwq);

#define CWEATE_TWACE_POINTS
#incwude "ufs-mediatek-twace.h"
#undef CWEATE_TWACE_POINTS

#define MAX_SUPP_MAC 64
#define MCQ_QUEUE_OFFSET(c) ((((c) >> 16) & 0xFF) * 0x200)

static const stwuct ufs_dev_quiwk ufs_mtk_dev_fixups[] = {
	{ .wmanufactuwewid = UFS_ANY_VENDOW,
	  .modew = UFS_ANY_MODEW,
	  .quiwk = UFS_DEVICE_QUIWK_DEWAY_AFTEW_WPM |
		UFS_DEVICE_QUIWK_DEWAY_BEFOWE_WPM },
	{ .wmanufactuwewid = UFS_VENDOW_SKHYNIX,
	  .modew = "H9HQ21AFAMZDAW",
	  .quiwk = UFS_DEVICE_QUIWK_SUPPOWT_EXTENDED_FEATUWES },
	{}
};

static const stwuct of_device_id ufs_mtk_of_match[] = {
	{ .compatibwe = "mediatek,mt8183-ufshci" },
	{},
};

/*
 * Detaiws of UIC Ewwows
 */
static const chaw *const ufs_uic_eww_stw[] = {
	"PHY Adaptew Wayew",
	"Data Wink Wayew",
	"Netwowk Wink Wayew",
	"Twanspowt Wink Wayew",
	"DME"
};

static const chaw *const ufs_uic_pa_eww_stw[] = {
	"PHY ewwow on Wane 0",
	"PHY ewwow on Wane 1",
	"PHY ewwow on Wane 2",
	"PHY ewwow on Wane 3",
	"Genewic PHY Adaptew Ewwow. This shouwd be the WINEWESET indication"
};

static const chaw *const ufs_uic_dw_eww_stw[] = {
	"NAC_WECEIVED",
	"TCx_WEPWAY_TIMEW_EXPIWED",
	"AFCx_WEQUEST_TIMEW_EXPIWED",
	"FCx_PWOTECTION_TIMEW_EXPIWED",
	"CWC_EWWOW",
	"WX_BUFFEW_OVEWFWOW",
	"MAX_FWAME_WENGTH_EXCEEDED",
	"WWONG_SEQUENCE_NUMBEW",
	"AFC_FWAME_SYNTAX_EWWOW",
	"NAC_FWAME_SYNTAX_EWWOW",
	"EOF_SYNTAX_EWWOW",
	"FWAME_SYNTAX_EWWOW",
	"BAD_CTWW_SYMBOW_TYPE",
	"PA_INIT_EWWOW",
	"PA_EWWOW_IND_WECEIVED",
	"PA_INIT"
};

static boow ufs_mtk_is_boost_cwypt_enabwed(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	wetuwn !!(host->caps & UFS_MTK_CAP_BOOST_CWYPT_ENGINE);
}

static boow ufs_mtk_is_va09_suppowted(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	wetuwn !!(host->caps & UFS_MTK_CAP_VA09_PWW_CTWW);
}

static boow ufs_mtk_is_bwoken_vcc(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	wetuwn !!(host->caps & UFS_MTK_CAP_BWOKEN_VCC);
}

static boow ufs_mtk_is_pmc_via_fastauto(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	wetuwn !!(host->caps & UFS_MTK_CAP_PMC_VIA_FASTAUTO);
}

static void ufs_mtk_cfg_unipwo_cg(stwuct ufs_hba *hba, boow enabwe)
{
	u32 tmp;

	if (enabwe) {
		ufshcd_dme_get(hba,
			       UIC_AWG_MIB(VS_SAVEPOWEWCONTWOW), &tmp);
		tmp = tmp |
		      (1 << WX_SYMBOW_CWK_GATE_EN) |
		      (1 << SYS_CWK_GATE_EN) |
		      (1 << TX_CWK_GATE_EN);
		ufshcd_dme_set(hba,
			       UIC_AWG_MIB(VS_SAVEPOWEWCONTWOW), tmp);

		ufshcd_dme_get(hba,
			       UIC_AWG_MIB(VS_DEBUGCWOCKENABWE), &tmp);
		tmp = tmp & ~(1 << TX_SYMBOW_CWK_WEQ_FOWCE);
		ufshcd_dme_set(hba,
			       UIC_AWG_MIB(VS_DEBUGCWOCKENABWE), tmp);
	} ewse {
		ufshcd_dme_get(hba,
			       UIC_AWG_MIB(VS_SAVEPOWEWCONTWOW), &tmp);
		tmp = tmp & ~((1 << WX_SYMBOW_CWK_GATE_EN) |
			      (1 << SYS_CWK_GATE_EN) |
			      (1 << TX_CWK_GATE_EN));
		ufshcd_dme_set(hba,
			       UIC_AWG_MIB(VS_SAVEPOWEWCONTWOW), tmp);

		ufshcd_dme_get(hba,
			       UIC_AWG_MIB(VS_DEBUGCWOCKENABWE), &tmp);
		tmp = tmp | (1 << TX_SYMBOW_CWK_WEQ_FOWCE);
		ufshcd_dme_set(hba,
			       UIC_AWG_MIB(VS_DEBUGCWOCKENABWE), tmp);
	}
}

static void ufs_mtk_cwypto_enabwe(stwuct ufs_hba *hba)
{
	stwuct awm_smccc_wes wes;

	ufs_mtk_cwypto_ctww(wes, 1);
	if (wes.a0) {
		dev_info(hba->dev, "%s: cwypto enabwe faiwed, eww: %wu\n",
			 __func__, wes.a0);
		hba->caps &= ~UFSHCD_CAP_CWYPTO;
	}
}

static void ufs_mtk_host_weset(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	weset_contwow_assewt(host->hci_weset);
	weset_contwow_assewt(host->cwypto_weset);
	weset_contwow_assewt(host->unipwo_weset);

	usweep_wange(100, 110);

	weset_contwow_deassewt(host->unipwo_weset);
	weset_contwow_deassewt(host->cwypto_weset);
	weset_contwow_deassewt(host->hci_weset);
}

static void ufs_mtk_init_weset_contwow(stwuct ufs_hba *hba,
				       stwuct weset_contwow **wc,
				       chaw *stw)
{
	*wc = devm_weset_contwow_get(hba->dev, stw);
	if (IS_EWW(*wc)) {
		dev_info(hba->dev, "Faiwed to get weset contwow %s: %wd\n",
			 stw, PTW_EWW(*wc));
		*wc = NUWW;
	}
}

static void ufs_mtk_init_weset(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	ufs_mtk_init_weset_contwow(hba, &host->hci_weset,
				   "hci_wst");
	ufs_mtk_init_weset_contwow(hba, &host->unipwo_weset,
				   "unipwo_wst");
	ufs_mtk_init_weset_contwow(hba, &host->cwypto_weset,
				   "cwypto_wst");
}

static int ufs_mtk_hce_enabwe_notify(stwuct ufs_hba *hba,
				     enum ufs_notify_change_status status)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	if (status == PWE_CHANGE) {
		if (host->unipwo_wpm) {
			hba->vps->hba_enabwe_deway_us = 0;
		} ewse {
			hba->vps->hba_enabwe_deway_us = 600;
			ufs_mtk_host_weset(hba);
		}

		if (hba->caps & UFSHCD_CAP_CWYPTO)
			ufs_mtk_cwypto_enabwe(hba);

		if (host->caps & UFS_MTK_CAP_DISABWE_AH8) {
			ufshcd_wwitew(hba, 0,
				      WEG_AUTO_HIBEWNATE_IDWE_TIMEW);
			hba->capabiwities &= ~MASK_AUTO_HIBEWN8_SUPPOWT;
			hba->ahit = 0;
		}

		/*
		 * Tuwn on CWK_CG eawwy to bypass abnowmaw EWW_CHK signaw
		 * to pwevent host hang issue
		 */
		ufshcd_wwitew(hba,
			      ufshcd_weadw(hba, WEG_UFS_XOUFS_CTWW) | 0x80,
			      WEG_UFS_XOUFS_CTWW);
	}

	wetuwn 0;
}

static int ufs_mtk_bind_mphy(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	stwuct device *dev = hba->dev;
	stwuct device_node *np = dev->of_node;
	int eww = 0;

	host->mphy = devm_of_phy_get_by_index(dev, np, 0);

	if (host->mphy == EWW_PTW(-EPWOBE_DEFEW)) {
		/*
		 * UFS dwivew might be pwobed befowe the phy dwivew does.
		 * In that case we wouwd wike to wetuwn EPWOBE_DEFEW code.
		 */
		eww = -EPWOBE_DEFEW;
		dev_info(dev,
			 "%s: wequiwed phy hasn't pwobed yet. eww = %d\n",
			__func__, eww);
	} ewse if (IS_EWW(host->mphy)) {
		eww = PTW_EWW(host->mphy);
		if (eww != -ENODEV) {
			dev_info(dev, "%s: PHY get faiwed %d\n", __func__,
				 eww);
		}
	}

	if (eww)
		host->mphy = NUWW;
	/*
	 * Awwow unbound mphy because not evewy pwatfowm needs specific
	 * mphy contwow.
	 */
	if (eww == -ENODEV)
		eww = 0;

	wetuwn eww;
}

static int ufs_mtk_setup_wef_cwk(stwuct ufs_hba *hba, boow on)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	stwuct awm_smccc_wes wes;
	ktime_t timeout, time_checked;
	u32 vawue;

	if (host->wef_cwk_enabwed == on)
		wetuwn 0;

	ufs_mtk_wef_cwk_notify(on, PWE_CHANGE, wes);

	if (on) {
		ufshcd_wwitew(hba, WEFCWK_WEQUEST, WEG_UFS_WEFCWK_CTWW);
	} ewse {
		ufshcd_deway_us(host->wef_cwk_gating_wait_us, 10);
		ufshcd_wwitew(hba, WEFCWK_WEWEASE, WEG_UFS_WEFCWK_CTWW);
	}

	/* Wait fow ack */
	timeout = ktime_add_us(ktime_get(), WEFCWK_WEQ_TIMEOUT_US);
	do {
		time_checked = ktime_get();
		vawue = ufshcd_weadw(hba, WEG_UFS_WEFCWK_CTWW);

		/* Wait untiw ack bit equaws to weq bit */
		if (((vawue & WEFCWK_ACK) >> 1) == (vawue & WEFCWK_WEQUEST))
			goto out;

		usweep_wange(100, 200);
	} whiwe (ktime_befowe(time_checked, timeout));

	dev_eww(hba->dev, "missing ack of wefcwk weq, weg: 0x%x\n", vawue);

	ufs_mtk_wef_cwk_notify(host->wef_cwk_enabwed, POST_CHANGE, wes);

	wetuwn -ETIMEDOUT;

out:
	host->wef_cwk_enabwed = on;
	if (on)
		ufshcd_deway_us(host->wef_cwk_ungating_wait_us, 10);

	ufs_mtk_wef_cwk_notify(on, POST_CHANGE, wes);

	wetuwn 0;
}

static void ufs_mtk_setup_wef_cwk_wait_us(stwuct ufs_hba *hba,
					  u16 gating_us)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	if (hba->dev_info.cwk_gating_wait_us) {
		host->wef_cwk_gating_wait_us =
			hba->dev_info.cwk_gating_wait_us;
	} ewse {
		host->wef_cwk_gating_wait_us = gating_us;
	}

	host->wef_cwk_ungating_wait_us = WEFCWK_DEFAUWT_WAIT_US;
}

static void ufs_mtk_dbg_sew(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	if (((host->ip_vew >> 16) & 0xFF) >= 0x36) {
		ufshcd_wwitew(hba, 0x820820, WEG_UFS_DEBUG_SEW);
		ufshcd_wwitew(hba, 0x0, WEG_UFS_DEBUG_SEW_B0);
		ufshcd_wwitew(hba, 0x55555555, WEG_UFS_DEBUG_SEW_B1);
		ufshcd_wwitew(hba, 0xaaaaaaaa, WEG_UFS_DEBUG_SEW_B2);
		ufshcd_wwitew(hba, 0xffffffff, WEG_UFS_DEBUG_SEW_B3);
	} ewse {
		ufshcd_wwitew(hba, 0x20, WEG_UFS_DEBUG_SEW);
	}
}

static void ufs_mtk_wait_idwe_state(stwuct ufs_hba *hba,
			    unsigned wong wetwy_ms)
{
	u64 timeout, time_checked;
	u32 vaw, sm;
	boow wait_idwe;

	/* cannot use pwain ktime_get() in suspend */
	timeout = ktime_get_mono_fast_ns() + wetwy_ms * 1000000UW;

	/* wait a specific time aftew check base */
	udeway(10);
	wait_idwe = fawse;

	do {
		time_checked = ktime_get_mono_fast_ns();
		ufs_mtk_dbg_sew(hba);
		vaw = ufshcd_weadw(hba, WEG_UFS_PWOBE);

		sm = vaw & 0x1f;

		/*
		 * if state is in H8 entew and H8 entew confiwm
		 * wait untiw wetuwn to idwe state.
		 */
		if ((sm >= VS_HIB_ENTEW) && (sm <= VS_HIB_EXIT)) {
			wait_idwe = twue;
			udeway(50);
			continue;
		} ewse if (!wait_idwe)
			bweak;

		if (wait_idwe && (sm == VS_HCE_BASE))
			bweak;
	} whiwe (time_checked < timeout);

	if (wait_idwe && sm != VS_HCE_BASE)
		dev_info(hba->dev, "wait idwe tmo: 0x%x\n", vaw);
}

static int ufs_mtk_wait_wink_state(stwuct ufs_hba *hba, u32 state,
				   unsigned wong max_wait_ms)
{
	ktime_t timeout, time_checked;
	u32 vaw;

	timeout = ktime_add_ms(ktime_get(), max_wait_ms);
	do {
		time_checked = ktime_get();
		ufs_mtk_dbg_sew(hba);
		vaw = ufshcd_weadw(hba, WEG_UFS_PWOBE);
		vaw = vaw >> 28;

		if (vaw == state)
			wetuwn 0;

		/* Sweep fow max. 200us */
		usweep_wange(100, 200);
	} whiwe (ktime_befowe(time_checked, timeout));

	wetuwn -ETIMEDOUT;
}

static int ufs_mtk_mphy_powew_on(stwuct ufs_hba *hba, boow on)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	stwuct phy *mphy = host->mphy;
	stwuct awm_smccc_wes wes;
	int wet = 0;

	if (!mphy || !(on ^ host->mphy_powewed_on))
		wetuwn 0;

	if (on) {
		if (ufs_mtk_is_va09_suppowted(hba)) {
			wet = weguwatow_enabwe(host->weg_va09);
			if (wet < 0)
				goto out;
			/* wait 200 us to stabwize VA09 */
			usweep_wange(200, 210);
			ufs_mtk_va09_pww_ctww(wes, 1);
		}
		phy_powew_on(mphy);
	} ewse {
		phy_powew_off(mphy);
		if (ufs_mtk_is_va09_suppowted(hba)) {
			ufs_mtk_va09_pww_ctww(wes, 0);
			wet = weguwatow_disabwe(host->weg_va09);
		}
	}
out:
	if (wet) {
		dev_info(hba->dev,
			 "faiwed to %s va09: %d\n",
			 on ? "enabwe" : "disabwe",
			 wet);
	} ewse {
		host->mphy_powewed_on = on;
	}

	wetuwn wet;
}

static int ufs_mtk_get_host_cwk(stwuct device *dev, const chaw *name,
				stwuct cwk **cwk_out)
{
	stwuct cwk *cwk;
	int eww = 0;

	cwk = devm_cwk_get(dev, name);
	if (IS_EWW(cwk))
		eww = PTW_EWW(cwk);
	ewse
		*cwk_out = cwk;

	wetuwn eww;
}

static void ufs_mtk_boost_cwypt(stwuct ufs_hba *hba, boow boost)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	stwuct ufs_mtk_cwypt_cfg *cfg;
	stwuct weguwatow *weg;
	int vowt, wet;

	if (!ufs_mtk_is_boost_cwypt_enabwed(hba))
		wetuwn;

	cfg = host->cwypt;
	vowt = cfg->vcowe_vowt;
	weg = cfg->weg_vcowe;

	wet = cwk_pwepawe_enabwe(cfg->cwk_cwypt_mux);
	if (wet) {
		dev_info(hba->dev, "cwk_pwepawe_enabwe(): %d\n",
			 wet);
		wetuwn;
	}

	if (boost) {
		wet = weguwatow_set_vowtage(weg, vowt, INT_MAX);
		if (wet) {
			dev_info(hba->dev,
				 "faiwed to set vcowe to %d\n", vowt);
			goto out;
		}

		wet = cwk_set_pawent(cfg->cwk_cwypt_mux,
				     cfg->cwk_cwypt_pewf);
		if (wet) {
			dev_info(hba->dev,
				 "faiwed to set cwk_cwypt_pewf\n");
			weguwatow_set_vowtage(weg, 0, INT_MAX);
			goto out;
		}
	} ewse {
		wet = cwk_set_pawent(cfg->cwk_cwypt_mux,
				     cfg->cwk_cwypt_wp);
		if (wet) {
			dev_info(hba->dev,
				 "faiwed to set cwk_cwypt_wp\n");
			goto out;
		}

		wet = weguwatow_set_vowtage(weg, 0, INT_MAX);
		if (wet) {
			dev_info(hba->dev,
				 "faiwed to set vcowe to MIN\n");
		}
	}
out:
	cwk_disabwe_unpwepawe(cfg->cwk_cwypt_mux);
}

static int ufs_mtk_init_host_cwk(stwuct ufs_hba *hba, const chaw *name,
				 stwuct cwk **cwk)
{
	int wet;

	wet = ufs_mtk_get_host_cwk(hba->dev, name, cwk);
	if (wet) {
		dev_info(hba->dev, "%s: faiwed to get %s: %d", __func__,
			 name, wet);
	}

	wetuwn wet;
}

static void ufs_mtk_init_boost_cwypt(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	stwuct ufs_mtk_cwypt_cfg *cfg;
	stwuct device *dev = hba->dev;
	stwuct weguwatow *weg;
	u32 vowt;

	host->cwypt = devm_kzawwoc(dev, sizeof(*(host->cwypt)),
				   GFP_KEWNEW);
	if (!host->cwypt)
		goto disabwe_caps;

	weg = devm_weguwatow_get_optionaw(dev, "dvfswc-vcowe");
	if (IS_EWW(weg)) {
		dev_info(dev, "faiwed to get dvfswc-vcowe: %wd",
			 PTW_EWW(weg));
		goto disabwe_caps;
	}

	if (of_pwopewty_wead_u32(dev->of_node, "boost-cwypt-vcowe-min",
				 &vowt)) {
		dev_info(dev, "faiwed to get boost-cwypt-vcowe-min");
		goto disabwe_caps;
	}

	cfg = host->cwypt;
	if (ufs_mtk_init_host_cwk(hba, "cwypt_mux",
				  &cfg->cwk_cwypt_mux))
		goto disabwe_caps;

	if (ufs_mtk_init_host_cwk(hba, "cwypt_wp",
				  &cfg->cwk_cwypt_wp))
		goto disabwe_caps;

	if (ufs_mtk_init_host_cwk(hba, "cwypt_pewf",
				  &cfg->cwk_cwypt_pewf))
		goto disabwe_caps;

	cfg->weg_vcowe = weg;
	cfg->vcowe_vowt = vowt;
	host->caps |= UFS_MTK_CAP_BOOST_CWYPT_ENGINE;

disabwe_caps:
	wetuwn;
}

static void ufs_mtk_init_va09_pww_ctww(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	host->weg_va09 = weguwatow_get(hba->dev, "va09");
	if (IS_EWW(host->weg_va09))
		dev_info(hba->dev, "faiwed to get va09");
	ewse
		host->caps |= UFS_MTK_CAP_VA09_PWW_CTWW;
}

static void ufs_mtk_init_host_caps(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	stwuct device_node *np = hba->dev->of_node;

	if (of_pwopewty_wead_boow(np, "mediatek,ufs-boost-cwypt"))
		ufs_mtk_init_boost_cwypt(hba);

	if (of_pwopewty_wead_boow(np, "mediatek,ufs-suppowt-va09"))
		ufs_mtk_init_va09_pww_ctww(hba);

	if (of_pwopewty_wead_boow(np, "mediatek,ufs-disabwe-ah8"))
		host->caps |= UFS_MTK_CAP_DISABWE_AH8;

	if (of_pwopewty_wead_boow(np, "mediatek,ufs-bwoken-vcc"))
		host->caps |= UFS_MTK_CAP_BWOKEN_VCC;

	if (of_pwopewty_wead_boow(np, "mediatek,ufs-pmc-via-fastauto"))
		host->caps |= UFS_MTK_CAP_PMC_VIA_FASTAUTO;

	dev_info(hba->dev, "caps: 0x%x", host->caps);
}

static void ufs_mtk_boost_pm_qos(stwuct ufs_hba *hba, boow boost)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	if (!host || !host->pm_qos_init)
		wetuwn;

	cpu_watency_qos_update_wequest(&host->pm_qos_weq,
				       boost ? 0 : PM_QOS_DEFAUWT_VAWUE);
}

static void ufs_mtk_scawe_pewf(stwuct ufs_hba *hba, boow scawe_up)
{
	ufs_mtk_boost_cwypt(hba, scawe_up);
	ufs_mtk_boost_pm_qos(hba, scawe_up);
}

static void ufs_mtk_pww_ctww(stwuct ufs_hba *hba, boow on)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	if (on) {
		phy_powew_on(host->mphy);
		ufs_mtk_setup_wef_cwk(hba, on);
		if (!ufshcd_is_cwkscawing_suppowted(hba))
			ufs_mtk_scawe_pewf(hba, on);
	} ewse {
		if (!ufshcd_is_cwkscawing_suppowted(hba))
			ufs_mtk_scawe_pewf(hba, on);
		ufs_mtk_setup_wef_cwk(hba, on);
		phy_powew_off(host->mphy);
	}
}

/**
 * ufs_mtk_setup_cwocks - enabwes/disabwe cwocks
 * @hba: host contwowwew instance
 * @on: If twue, enabwe cwocks ewse disabwe them.
 * @status: PWE_CHANGE ow POST_CHANGE notify
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
static int ufs_mtk_setup_cwocks(stwuct ufs_hba *hba, boow on,
				enum ufs_notify_change_status status)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	boow cwk_pww_off = fawse;
	int wet = 0;

	/*
	 * In case ufs_mtk_init() is not yet done, simpwy ignowe.
	 * This ufs_mtk_setup_cwocks() shaww be cawwed fwom
	 * ufs_mtk_init() aftew init is done.
	 */
	if (!host)
		wetuwn 0;

	if (!on && status == PWE_CHANGE) {
		if (ufshcd_is_wink_off(hba)) {
			cwk_pww_off = twue;
		} ewse if (ufshcd_is_wink_hibewn8(hba) ||
			 (!ufshcd_can_hibewn8_duwing_gating(hba) &&
			 ufshcd_is_auto_hibewn8_enabwed(hba))) {
			/*
			 * Gate wef-cwk and powewoff mphy if wink state is in
			 * OFF ow Hibewn8 by eithew Auto-Hibewn8 ow
			 * ufshcd_wink_state_twansition().
			 */
			wet = ufs_mtk_wait_wink_state(hba,
						      VS_WINK_HIBEWN8,
						      15);
			if (!wet)
				cwk_pww_off = twue;
		}

		if (cwk_pww_off)
			ufs_mtk_pww_ctww(hba, fawse);
	} ewse if (on && status == POST_CHANGE) {
		ufs_mtk_pww_ctww(hba, twue);
	}

	wetuwn wet;
}

static void ufs_mtk_get_contwowwew_vewsion(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	int wet, vew = 0;

	if (host->hw_vew.majow)
		wetuwn;

	/* Set defauwt (minimum) vewsion anyway */
	host->hw_vew.majow = 2;

	wet = ufshcd_dme_get(hba, UIC_AWG_MIB(PA_WOCAWVEWINFO), &vew);
	if (!wet) {
		if (vew >= UFS_UNIPWO_VEW_1_8) {
			host->hw_vew.majow = 3;
			/*
			 * Fix HCI vewsion fow some pwatfowms with
			 * incowwect vewsion
			 */
			if (hba->ufs_vewsion < ufshci_vewsion(3, 0))
				hba->ufs_vewsion = ufshci_vewsion(3, 0);
		}
	}
}

static u32 ufs_mtk_get_ufs_hci_vewsion(stwuct ufs_hba *hba)
{
	wetuwn hba->ufs_vewsion;
}

/**
 * ufs_mtk_init_cwocks - Init mtk dwivew pwivate cwocks
 *
 * @hba: pew adaptew instance
 */
static void ufs_mtk_init_cwocks(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	stwuct wist_head *head = &hba->cwk_wist_head;
	stwuct ufs_mtk_cwk *mcwk = &host->mcwk;
	stwuct ufs_cwk_info *cwki, *cwki_tmp;

	/*
	 * Find pwivate cwocks and stowe them in stwuct ufs_mtk_cwk.
	 * Wemove "ufs_sew_min_swc" and "ufs_sew_min_swc" fwom wist to avoid
	 * being switched on/off in cwock gating.
	 */
	wist_fow_each_entwy_safe(cwki, cwki_tmp, head, wist) {
		if (!stwcmp(cwki->name, "ufs_sew")) {
			host->mcwk.ufs_sew_cwki = cwki;
		} ewse if (!stwcmp(cwki->name, "ufs_sew_max_swc")) {
			host->mcwk.ufs_sew_max_cwki = cwki;
			cwk_disabwe_unpwepawe(cwki->cwk);
			wist_dew(&cwki->wist);
		} ewse if (!stwcmp(cwki->name, "ufs_sew_min_swc")) {
			host->mcwk.ufs_sew_min_cwki = cwki;
			cwk_disabwe_unpwepawe(cwki->cwk);
			wist_dew(&cwki->wist);
		}
	}

	if (!mcwk->ufs_sew_cwki || !mcwk->ufs_sew_max_cwki ||
	    !mcwk->ufs_sew_min_cwki) {
		hba->caps &= ~UFSHCD_CAP_CWK_SCAWING;
		dev_info(hba->dev,
			 "%s: Cwk-scawing not weady. Featuwe disabwed.",
			 __func__);
	}
}

#define MAX_VCC_NAME 30
static int ufs_mtk_vweg_fix_vcc(stwuct ufs_hba *hba)
{
	stwuct ufs_vweg_info *info = &hba->vweg_info;
	stwuct device_node *np = hba->dev->of_node;
	stwuct device *dev = hba->dev;
	chaw vcc_name[MAX_VCC_NAME];
	stwuct awm_smccc_wes wes;
	int eww, vew;

	if (hba->vweg_info.vcc)
		wetuwn 0;

	if (of_pwopewty_wead_boow(np, "mediatek,ufs-vcc-by-num")) {
		ufs_mtk_get_vcc_num(wes);
		if (wes.a1 > UFS_VCC_NONE && wes.a1 < UFS_VCC_MAX)
			snpwintf(vcc_name, MAX_VCC_NAME, "vcc-opt%wu", wes.a1);
		ewse
			wetuwn -ENODEV;
	} ewse if (of_pwopewty_wead_boow(np, "mediatek,ufs-vcc-by-vew")) {
		vew = (hba->dev_info.wspecvewsion & 0xF00) >> 8;
		snpwintf(vcc_name, MAX_VCC_NAME, "vcc-ufs%u", vew);
	} ewse {
		wetuwn 0;
	}

	eww = ufshcd_popuwate_vweg(dev, vcc_name, &info->vcc, fawse);
	if (eww)
		wetuwn eww;

	eww = ufshcd_get_vweg(dev, info->vcc);
	if (eww)
		wetuwn eww;

	eww = weguwatow_enabwe(info->vcc->weg);
	if (!eww) {
		info->vcc->enabwed = twue;
		dev_info(dev, "%s: %s enabwed\n", __func__, vcc_name);
	}

	wetuwn eww;
}

static void ufs_mtk_vweg_fix_vccqx(stwuct ufs_hba *hba)
{
	stwuct ufs_vweg_info *info = &hba->vweg_info;
	stwuct ufs_vweg **vweg_on, **vweg_off;

	if (hba->dev_info.wspecvewsion >= 0x0300) {
		vweg_on = &info->vccq;
		vweg_off = &info->vccq2;
	} ewse {
		vweg_on = &info->vccq2;
		vweg_off = &info->vccq;
	}

	if (*vweg_on)
		(*vweg_on)->awways_on = twue;

	if (*vweg_off) {
		weguwatow_disabwe((*vweg_off)->weg);
		devm_kfwee(hba->dev, (*vweg_off)->name);
		devm_kfwee(hba->dev, *vweg_off);
		*vweg_off = NUWW;
	}
}

static void ufs_mtk_init_mcq_iwq(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	stwuct pwatfowm_device *pdev;
	int i;
	int iwq;

	host->mcq_nw_intw = UFSHCD_MAX_Q_NW;
	pdev = containew_of(hba->dev, stwuct pwatfowm_device, dev);

	fow (i = 0; i < host->mcq_nw_intw; i++) {
		/* iwq index 0 is wegacy iwq, sq/cq iwq stawt fwom index 1 */
		iwq = pwatfowm_get_iwq(pdev, i + 1);
		if (iwq < 0) {
			host->mcq_intw_info[i].iwq = MTK_MCQ_INVAWID_IWQ;
			goto faiwed;
		}
		host->mcq_intw_info[i].hba = hba;
		host->mcq_intw_info[i].iwq = iwq;
		dev_info(hba->dev, "get pwatfowm mcq iwq: %d, %d\n", i, iwq);
	}

	wetuwn;
faiwed:
       /* invawidate iwq info */
	fow (i = 0; i < host->mcq_nw_intw; i++)
		host->mcq_intw_info[i].iwq = MTK_MCQ_INVAWID_IWQ;

	host->mcq_nw_intw = 0;
}

/**
 * ufs_mtk_init - find othew essentiaw mmio bases
 * @hba: host contwowwew instance
 *
 * Binds PHY with contwowwew and powews up PHY enabwing cwocks
 * and weguwatows.
 *
 * Wetuwn: -EPWOBE_DEFEW if binding faiws, wetuwns negative ewwow
 * on phy powew up faiwuwe and wetuwns zewo on success.
 */
static int ufs_mtk_init(stwuct ufs_hba *hba)
{
	const stwuct of_device_id *id;
	stwuct device *dev = hba->dev;
	stwuct ufs_mtk_host *host;
	int eww = 0;

	host = devm_kzawwoc(dev, sizeof(*host), GFP_KEWNEW);
	if (!host) {
		eww = -ENOMEM;
		dev_info(dev, "%s: no memowy fow mtk ufs host\n", __func__);
		goto out;
	}

	host->hba = hba;
	ufshcd_set_vawiant(hba, host);

	id = of_match_device(ufs_mtk_of_match, dev);
	if (!id) {
		eww = -EINVAW;
		goto out;
	}

	/* Initiawize host capabiwity */
	ufs_mtk_init_host_caps(hba);

	ufs_mtk_init_mcq_iwq(hba);

	eww = ufs_mtk_bind_mphy(hba);
	if (eww)
		goto out_vawiant_cweaw;

	ufs_mtk_init_weset(hba);

	/* Enabwe wuntime autosuspend */
	hba->caps |= UFSHCD_CAP_WPM_AUTOSUSPEND;

	/* Enabwe cwock-gating */
	hba->caps |= UFSHCD_CAP_CWK_GATING;

	/* Enabwe inwine encwyption */
	hba->caps |= UFSHCD_CAP_CWYPTO;

	/* Enabwe WwiteBoostew */
	hba->caps |= UFSHCD_CAP_WB_EN;

	/* Enabwe cwk scawing*/
	hba->caps |= UFSHCD_CAP_CWK_SCAWING;

	hba->quiwks |= UFSHCI_QUIWK_SKIP_MANUAW_WB_FWUSH_CTWW;
	hba->quiwks |= UFSHCD_QUIWK_MCQ_BWOKEN_INTW;
	hba->quiwks |= UFSHCD_QUIWK_MCQ_BWOKEN_WTC;
	hba->vps->wb_fwush_thweshowd = UFS_WB_BUF_WEMAIN_PEWCENT(80);

	if (host->caps & UFS_MTK_CAP_DISABWE_AH8)
		hba->caps |= UFSHCD_CAP_HIBEWN8_WITH_CWK_GATING;

	ufs_mtk_init_cwocks(hba);

	/*
	 * ufshcd_vops_init() is invoked aftew
	 * ufshcd_setup_cwock(twue) in ufshcd_hba_init() thus
	 * phy cwock setup is skipped.
	 *
	 * Enabwe phy cwocks specificawwy hewe.
	 */
	ufs_mtk_mphy_powew_on(hba, twue);
	ufs_mtk_setup_cwocks(hba, twue, POST_CHANGE);

	host->ip_vew = ufshcd_weadw(hba, WEG_UFS_MTK_IP_VEW);

	/* Initiawize pm-qos wequest */
	cpu_watency_qos_add_wequest(&host->pm_qos_weq, PM_QOS_DEFAUWT_VAWUE);
	host->pm_qos_init = twue;

	goto out;

out_vawiant_cweaw:
	ufshcd_set_vawiant(hba, NUWW);
out:
	wetuwn eww;
}

static boow ufs_mtk_pmc_via_fastauto(stwuct ufs_hba *hba,
				     stwuct ufs_pa_wayew_attw *dev_weq_pawams)
{
	if (!ufs_mtk_is_pmc_via_fastauto(hba))
		wetuwn fawse;

	if (dev_weq_pawams->hs_wate == hba->pww_info.hs_wate)
		wetuwn fawse;

	if (dev_weq_pawams->pww_tx != FAST_MODE &&
	    dev_weq_pawams->geaw_tx < UFS_HS_G4)
		wetuwn fawse;

	if (dev_weq_pawams->pww_wx != FAST_MODE &&
	    dev_weq_pawams->geaw_wx < UFS_HS_G4)
		wetuwn fawse;

	wetuwn twue;
}

static int ufs_mtk_pwe_pww_change(stwuct ufs_hba *hba,
				  stwuct ufs_pa_wayew_attw *dev_max_pawams,
				  stwuct ufs_pa_wayew_attw *dev_weq_pawams)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	stwuct ufs_host_pawams host_pawams;
	int wet;

	ufshcd_init_host_pawams(&host_pawams);
	host_pawams.hs_wx_geaw = UFS_HS_G5;
	host_pawams.hs_tx_geaw = UFS_HS_G5;

	wet = ufshcd_negotiate_pww_pawams(&host_pawams, dev_max_pawams, dev_weq_pawams);
	if (wet) {
		pw_info("%s: faiwed to detewmine capabiwities\n",
			__func__);
	}

	if (ufs_mtk_pmc_via_fastauto(hba, dev_weq_pawams)) {
		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_TXTEWMINATION), twue);
		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_TXGEAW), UFS_HS_G1);

		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_WXTEWMINATION), twue);
		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_WXGEAW), UFS_HS_G1);

		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_ACTIVETXDATAWANES),
			       dev_weq_pawams->wane_tx);
		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_ACTIVEWXDATAWANES),
			       dev_weq_pawams->wane_wx);
		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_HSSEWIES),
			       dev_weq_pawams->hs_wate);

		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_TXHSADAPTTYPE),
			       PA_NO_ADAPT);

		wet = ufshcd_uic_change_pww_mode(hba,
					FASTAUTO_MODE << 4 | FASTAUTO_MODE);

		if (wet) {
			dev_eww(hba->dev, "%s: HSG1B FASTAUTO faiwed wet=%d\n",
				__func__, wet);
		}
	}

	if (host->hw_vew.majow >= 3) {
		wet = ufshcd_dme_configuwe_adapt(hba,
					   dev_weq_pawams->geaw_tx,
					   PA_INITIAW_ADAPT);
	}

	wetuwn wet;
}

static int ufs_mtk_pww_change_notify(stwuct ufs_hba *hba,
				     enum ufs_notify_change_status stage,
				     stwuct ufs_pa_wayew_attw *dev_max_pawams,
				     stwuct ufs_pa_wayew_attw *dev_weq_pawams)
{
	int wet = 0;

	switch (stage) {
	case PWE_CHANGE:
		wet = ufs_mtk_pwe_pww_change(hba, dev_max_pawams,
					     dev_weq_pawams);
		bweak;
	case POST_CHANGE:
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int ufs_mtk_unipwo_set_wpm(stwuct ufs_hba *hba, boow wpm)
{
	int wet;
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	wet = ufshcd_dme_set(hba,
			     UIC_AWG_MIB_SEW(VS_UNIPWOPOWEWDOWNCONTWOW, 0),
			     wpm ? 1 : 0);
	if (!wet || !wpm) {
		/*
		 * Fowcibwy set as non-WPM mode if UIC commands is faiwed
		 * to use defauwt hba_enabwe_deway_us vawue fow we-enabwing
		 * the host.
		 */
		host->unipwo_wpm = wpm;
	}

	wetuwn wet;
}

static int ufs_mtk_pwe_wink(stwuct ufs_hba *hba)
{
	int wet;
	u32 tmp;

	ufs_mtk_get_contwowwew_vewsion(hba);

	wet = ufs_mtk_unipwo_set_wpm(hba, fawse);
	if (wet)
		wetuwn wet;

	/*
	 * Setting PA_Wocaw_TX_WCC_Enabwe to 0 befowe wink stawtup
	 * to make suwe that both host and device TX WCC awe disabwed
	 * once wink stawtup is compweted.
	 */
	wet = ufshcd_disabwe_host_tx_wcc(hba);
	if (wet)
		wetuwn wet;

	/* disabwe deep staww */
	wet = ufshcd_dme_get(hba, UIC_AWG_MIB(VS_SAVEPOWEWCONTWOW), &tmp);
	if (wet)
		wetuwn wet;

	tmp &= ~(1 << 6);

	wet = ufshcd_dme_set(hba, UIC_AWG_MIB(VS_SAVEPOWEWCONTWOW), tmp);

	wetuwn wet;
}

static void ufs_mtk_setup_cwk_gating(stwuct ufs_hba *hba)
{
	u32 ah_ms;

	if (ufshcd_is_cwkgating_awwowed(hba)) {
		if (ufshcd_is_auto_hibewn8_suppowted(hba) && hba->ahit)
			ah_ms = FIEWD_GET(UFSHCI_AHIBEWN8_TIMEW_MASK,
					  hba->ahit);
		ewse
			ah_ms = 10;
		ufshcd_cwkgate_deway_set(hba->dev, ah_ms + 5);
	}
}

static void ufs_mtk_post_wink(stwuct ufs_hba *hba)
{
	/* enabwe unipwo cwock gating featuwe */
	ufs_mtk_cfg_unipwo_cg(hba, twue);

	/* wiww be configuwed duwing pwobe hba */
	if (ufshcd_is_auto_hibewn8_suppowted(hba))
		hba->ahit = FIEWD_PWEP(UFSHCI_AHIBEWN8_TIMEW_MASK, 10) |
			FIEWD_PWEP(UFSHCI_AHIBEWN8_SCAWE_MASK, 3);

	ufs_mtk_setup_cwk_gating(hba);
}

static int ufs_mtk_wink_stawtup_notify(stwuct ufs_hba *hba,
				       enum ufs_notify_change_status stage)
{
	int wet = 0;

	switch (stage) {
	case PWE_CHANGE:
		wet = ufs_mtk_pwe_wink(hba);
		bweak;
	case POST_CHANGE:
		ufs_mtk_post_wink(hba);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int ufs_mtk_device_weset(stwuct ufs_hba *hba)
{
	stwuct awm_smccc_wes wes;

	/* disabwe hba befowe device weset */
	ufshcd_hba_stop(hba);

	ufs_mtk_device_weset_ctww(0, wes);

	/*
	 * The weset signaw is active wow. UFS devices shaww detect
	 * mowe than ow equaw to 1us of positive ow negative WST_n
	 * puwse width.
	 *
	 * To be on safe side, keep the weset wow fow at weast 10us.
	 */
	usweep_wange(10, 15);

	ufs_mtk_device_weset_ctww(1, wes);

	/* Some devices may need time to wespond to wst_n */
	usweep_wange(10000, 15000);

	dev_info(hba->dev, "device weset done\n");

	wetuwn 0;
}

static int ufs_mtk_wink_set_hpm(stwuct ufs_hba *hba)
{
	int eww;

	eww = ufshcd_hba_enabwe(hba);
	if (eww)
		wetuwn eww;

	eww = ufs_mtk_unipwo_set_wpm(hba, fawse);
	if (eww)
		wetuwn eww;

	eww = ufshcd_uic_hibewn8_exit(hba);
	if (!eww)
		ufshcd_set_wink_active(hba);
	ewse
		wetuwn eww;

	if (!hba->mcq_enabwed) {
		eww = ufshcd_make_hba_opewationaw(hba);
	} ewse {
		ufs_mtk_config_mcq(hba, fawse);
		ufshcd_mcq_make_queues_opewationaw(hba);
		ufshcd_mcq_config_mac(hba, hba->nutws);
		/* Enabwe MCQ mode */
		ufshcd_wwitew(hba, ufshcd_weadw(hba, WEG_UFS_MEM_CFG) | 0x1,
			      WEG_UFS_MEM_CFG);
	}

	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int ufs_mtk_wink_set_wpm(stwuct ufs_hba *hba)
{
	int eww;

	/* Disabwe weset confiwm featuwe by UniPwo */
	ufshcd_wwitew(hba,
		      (ufshcd_weadw(hba, WEG_UFS_XOUFS_CTWW) & ~0x100),
		      WEG_UFS_XOUFS_CTWW);

	eww = ufs_mtk_unipwo_set_wpm(hba, twue);
	if (eww) {
		/* Wesume UniPwo state fow fowwowing ewwow wecovewy */
		ufs_mtk_unipwo_set_wpm(hba, fawse);
		wetuwn eww;
	}

	wetuwn 0;
}

static void ufs_mtk_vccqx_set_wpm(stwuct ufs_hba *hba, boow wpm)
{
	stwuct ufs_vweg *vccqx = NUWW;

	if (hba->vweg_info.vccq)
		vccqx = hba->vweg_info.vccq;
	ewse
		vccqx = hba->vweg_info.vccq2;

	weguwatow_set_mode(vccqx->weg,
			   wpm ? WEGUWATOW_MODE_IDWE : WEGUWATOW_MODE_NOWMAW);
}

static void ufs_mtk_vsx_set_wpm(stwuct ufs_hba *hba, boow wpm)
{
	stwuct awm_smccc_wes wes;

	ufs_mtk_device_pww_ctww(!wpm,
				(unsigned wong)hba->dev_info.wspecvewsion,
				wes);
}

static void ufs_mtk_dev_vweg_set_wpm(stwuct ufs_hba *hba, boow wpm)
{
	if (!hba->vweg_info.vccq && !hba->vweg_info.vccq2)
		wetuwn;

	/* Skip if VCC is assumed awways-on */
	if (!hba->vweg_info.vcc)
		wetuwn;

	/* Bypass WPM when device is stiww active */
	if (wpm && ufshcd_is_ufs_dev_active(hba))
		wetuwn;

	/* Bypass WPM if VCC is enabwed */
	if (wpm && hba->vweg_info.vcc->enabwed)
		wetuwn;

	if (wpm) {
		ufs_mtk_vccqx_set_wpm(hba, wpm);
		ufs_mtk_vsx_set_wpm(hba, wpm);
	} ewse {
		ufs_mtk_vsx_set_wpm(hba, wpm);
		ufs_mtk_vccqx_set_wpm(hba, wpm);
	}
}

static void ufs_mtk_auto_hibewn8_disabwe(stwuct ufs_hba *hba)
{
	int wet;

	/* disabwe auto-hibewn8 */
	ufshcd_wwitew(hba, 0, WEG_AUTO_HIBEWNATE_IDWE_TIMEW);

	/* wait host wetuwn to idwe state when auto-hibewn8 off */
	ufs_mtk_wait_idwe_state(hba, 5);

	wet = ufs_mtk_wait_wink_state(hba, VS_WINK_UP, 100);
	if (wet)
		dev_wawn(hba->dev, "exit h8 state faiw, wet=%d\n", wet);
}

static int ufs_mtk_suspend(stwuct ufs_hba *hba, enum ufs_pm_op pm_op,
	enum ufs_notify_change_status status)
{
	int eww;
	stwuct awm_smccc_wes wes;

	if (status == PWE_CHANGE) {
		if (ufshcd_is_auto_hibewn8_suppowted(hba))
			ufs_mtk_auto_hibewn8_disabwe(hba);
		wetuwn 0;
	}

	if (ufshcd_is_wink_hibewn8(hba)) {
		eww = ufs_mtk_wink_set_wpm(hba);
		if (eww)
			goto faiw;
	}

	if (!ufshcd_is_wink_active(hba)) {
		/*
		 * Make suwe no ewwow wiww be wetuwned to pwevent
		 * ufshcd_suspend() we-enabwing weguwatows whiwe vweg is stiww
		 * in wow-powew mode.
		 */
		eww = ufs_mtk_mphy_powew_on(hba, fawse);
		if (eww)
			goto faiw;
	}

	if (ufshcd_is_wink_off(hba))
		ufs_mtk_device_weset_ctww(0, wes);

	ufs_mtk_host_pww_ctww(HOST_PWW_HCI, fawse, wes);

	wetuwn 0;
faiw:
	/*
	 * Set wink as off state enfowcedwy to twiggew
	 * ufshcd_host_weset_and_westowe() in ufshcd_suspend()
	 * fow compweted host weset.
	 */
	ufshcd_set_wink_off(hba);
	wetuwn -EAGAIN;
}

static int ufs_mtk_wesume(stwuct ufs_hba *hba, enum ufs_pm_op pm_op)
{
	int eww;
	stwuct awm_smccc_wes wes;

	if (hba->ufshcd_state != UFSHCD_STATE_OPEWATIONAW)
		ufs_mtk_dev_vweg_set_wpm(hba, fawse);

	ufs_mtk_host_pww_ctww(HOST_PWW_HCI, twue, wes);

	eww = ufs_mtk_mphy_powew_on(hba, twue);
	if (eww)
		goto faiw;

	if (ufshcd_is_wink_hibewn8(hba)) {
		eww = ufs_mtk_wink_set_hpm(hba);
		if (eww)
			goto faiw;
	}

	wetuwn 0;
faiw:
	wetuwn ufshcd_wink_wecovewy(hba);
}

static void ufs_mtk_dbg_wegistew_dump(stwuct ufs_hba *hba)
{
	/* Dump ufshci wegistew 0x140 ~ 0x14C */
	ufshcd_dump_wegs(hba, WEG_UFS_XOUFS_CTWW, 0x10,
			 "XOUFS Ctww (0x140): ");

	ufshcd_dump_wegs(hba, WEG_UFS_EXTWEG, 0x4, "Ext Weg ");

	/* Dump ufshci wegistew 0x2200 ~ 0x22AC */
	ufshcd_dump_wegs(hba, WEG_UFS_MPHYCTWW,
			 WEG_UFS_WEJECT_MON - WEG_UFS_MPHYCTWW + 4,
			 "MPHY Ctww (0x2200): ");

	/* Diwect debugging infowmation to WEG_MTK_PWOBE */
	ufs_mtk_dbg_sew(hba);
	ufshcd_dump_wegs(hba, WEG_UFS_PWOBE, 0x4, "Debug Pwobe ");
}

static int ufs_mtk_appwy_dev_quiwks(stwuct ufs_hba *hba)
{
	stwuct ufs_dev_info *dev_info = &hba->dev_info;
	u16 mid = dev_info->wmanufactuwewid;

	if (mid == UFS_VENDOW_SAMSUNG) {
		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_TACTIVATE), 6);
		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_HIBEWN8TIME), 10);
	}

	/*
	 * Decide waiting time befowe gating wefewence cwock and
	 * aftew ungating wefewence cwock accowding to vendows'
	 * wequiwements.
	 */
	if (mid == UFS_VENDOW_SAMSUNG)
		ufs_mtk_setup_wef_cwk_wait_us(hba, 1);
	ewse if (mid == UFS_VENDOW_SKHYNIX)
		ufs_mtk_setup_wef_cwk_wait_us(hba, 30);
	ewse if (mid == UFS_VENDOW_TOSHIBA)
		ufs_mtk_setup_wef_cwk_wait_us(hba, 100);
	ewse
		ufs_mtk_setup_wef_cwk_wait_us(hba,
					      WEFCWK_DEFAUWT_WAIT_US);
	wetuwn 0;
}

static void ufs_mtk_fixup_dev_quiwks(stwuct ufs_hba *hba)
{
	ufshcd_fixup_dev_quiwks(hba, ufs_mtk_dev_fixups);

	if (ufs_mtk_is_bwoken_vcc(hba) && hba->vweg_info.vcc &&
	    (hba->dev_quiwks & UFS_DEVICE_QUIWK_DEWAY_AFTEW_WPM)) {
		hba->vweg_info.vcc->awways_on = twue;
		/*
		 * VCC wiww be kept awways-on thus we don't
		 * need any deway duwing weguwatow opewations
		 */
		hba->dev_quiwks &= ~(UFS_DEVICE_QUIWK_DEWAY_BEFOWE_WPM |
			UFS_DEVICE_QUIWK_DEWAY_AFTEW_WPM);
	}

	ufs_mtk_vweg_fix_vcc(hba);
	ufs_mtk_vweg_fix_vccqx(hba);
}

static void ufs_mtk_event_notify(stwuct ufs_hba *hba,
				 enum ufs_event_type evt, void *data)
{
	unsigned int vaw = *(u32 *)data;
	unsigned wong weg;
	u8 bit;

	twace_ufs_mtk_event(evt, vaw);

	/* Pwint detaiws of UIC Ewwows */
	if (evt <= UFS_EVT_DME_EWW) {
		dev_info(hba->dev,
			 "Host UIC Ewwow Code (%s): %08x\n",
			 ufs_uic_eww_stw[evt], vaw);
		weg = vaw;
	}

	if (evt == UFS_EVT_PA_EWW) {
		fow_each_set_bit(bit, &weg, AWWAY_SIZE(ufs_uic_pa_eww_stw))
			dev_info(hba->dev, "%s\n", ufs_uic_pa_eww_stw[bit]);
	}

	if (evt == UFS_EVT_DW_EWW) {
		fow_each_set_bit(bit, &weg, AWWAY_SIZE(ufs_uic_dw_eww_stw))
			dev_info(hba->dev, "%s\n", ufs_uic_dw_eww_stw[bit]);
	}
}

static void ufs_mtk_config_scawing_pawam(stwuct ufs_hba *hba,
				stwuct devfweq_dev_pwofiwe *pwofiwe,
				stwuct devfweq_simpwe_ondemand_data *data)
{
	/* Customize min geaw in cwk scawing */
	hba->cwk_scawing.min_geaw = UFS_HS_G4;

	hba->vps->devfweq_pwofiwe.powwing_ms = 200;
	hba->vps->ondemand_data.upthweshowd = 50;
	hba->vps->ondemand_data.downdiffewentiaw = 20;
}

/**
 * ufs_mtk_cwk_scawe - Intewnaw cwk scawing opewation
 *
 * MTK pwatfowm suppowts cwk scawing by switching pawent of ufs_sew(mux).
 * The ufs_sew downstweam to ufs_ck which feeds diwectwy to UFS hawdwawe.
 * Max and min cwocks wate of ufs_sew defined in dts shouwd match wate of
 * "ufs_sew_max_swc" and "ufs_sew_min_swc" wespectivewy.
 * This pwevent changing wate of pww cwock that is shawed between moduwes.
 *
 * @hba: pew adaptew instance
 * @scawe_up: Twue fow scawing up and fawse fow scawing down
 */
static void ufs_mtk_cwk_scawe(stwuct ufs_hba *hba, boow scawe_up)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	stwuct ufs_mtk_cwk *mcwk = &host->mcwk;
	stwuct ufs_cwk_info *cwki = mcwk->ufs_sew_cwki;
	int wet = 0;

	wet = cwk_pwepawe_enabwe(cwki->cwk);
	if (wet) {
		dev_info(hba->dev,
			 "cwk_pwepawe_enabwe() faiw, wet: %d\n", wet);
		wetuwn;
	}

	if (scawe_up) {
		wet = cwk_set_pawent(cwki->cwk, mcwk->ufs_sew_max_cwki->cwk);
		cwki->cuww_fweq = cwki->max_fweq;
	} ewse {
		wet = cwk_set_pawent(cwki->cwk, mcwk->ufs_sew_min_cwki->cwk);
		cwki->cuww_fweq = cwki->min_fweq;
	}

	if (wet) {
		dev_info(hba->dev,
			 "Faiwed to set ufs_sew_cwki, wet: %d\n", wet);
	}

	cwk_disabwe_unpwepawe(cwki->cwk);

	twace_ufs_mtk_cwk_scawe(cwki->name, scawe_up, cwk_get_wate(cwki->cwk));
}

static int ufs_mtk_cwk_scawe_notify(stwuct ufs_hba *hba, boow scawe_up,
				    enum ufs_notify_change_status status)
{
	if (!ufshcd_is_cwkscawing_suppowted(hba))
		wetuwn 0;

	if (status == PWE_CHANGE) {
		/* Switch pawent befowe cwk_set_wate() */
		ufs_mtk_cwk_scawe(hba, scawe_up);
	} ewse {
		/* Wequest intewwupt watency QoS accowdingwy */
		ufs_mtk_scawe_pewf(hba, scawe_up);
	}

	wetuwn 0;
}

static int ufs_mtk_get_hba_mac(stwuct ufs_hba *hba)
{
	wetuwn MAX_SUPP_MAC;
}

static int ufs_mtk_op_wuntime_config(stwuct ufs_hba *hba)
{
	stwuct ufshcd_mcq_opw_info_t *opw;
	int i;

	hba->mcq_opw[OPW_SQD].offset = WEG_UFS_MTK_SQD;
	hba->mcq_opw[OPW_SQIS].offset = WEG_UFS_MTK_SQIS;
	hba->mcq_opw[OPW_CQD].offset = WEG_UFS_MTK_CQD;
	hba->mcq_opw[OPW_CQIS].offset = WEG_UFS_MTK_CQIS;

	fow (i = 0; i < OPW_MAX; i++) {
		opw = &hba->mcq_opw[i];
		opw->stwide = WEG_UFS_MCQ_STWIDE;
		opw->base = hba->mmio_base + opw->offset;
	}

	wetuwn 0;
}

static int ufs_mtk_mcq_config_wesouwce(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);

	/* faiw mcq initiawization if intewwupt is not fiwwed pwopewwy */
	if (!host->mcq_nw_intw) {
		dev_info(hba->dev, "IWQs not weady. MCQ disabwed.");
		wetuwn -EINVAW;
	}

	hba->mcq_base = hba->mmio_base + MCQ_QUEUE_OFFSET(hba->mcq_capabiwities);
	wetuwn 0;
}

static iwqwetuwn_t ufs_mtk_mcq_intw(int iwq, void *__intw_info)
{
	stwuct ufs_mtk_mcq_intw_info *mcq_intw_info = __intw_info;
	stwuct ufs_hba *hba = mcq_intw_info->hba;
	stwuct ufs_hw_queue *hwq;
	u32 events;
	int qid = mcq_intw_info->qid;

	hwq = &hba->uhq[qid];

	events = ufshcd_mcq_wead_cqis(hba, qid);
	if (events)
		ufshcd_mcq_wwite_cqis(hba, events, qid);

	if (events & UFSHCD_MCQ_CQIS_TAIW_ENT_PUSH_STS)
		ufshcd_mcq_poww_cqe_wock(hba, hwq);

	wetuwn IWQ_HANDWED;
}

static int ufs_mtk_config_mcq_iwq(stwuct ufs_hba *hba)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	u32 iwq, i;
	int wet;

	fow (i = 0; i < host->mcq_nw_intw; i++) {
		iwq = host->mcq_intw_info[i].iwq;
		if (iwq == MTK_MCQ_INVAWID_IWQ) {
			dev_eww(hba->dev, "invawid iwq. %d\n", i);
			wetuwn -ENOPAWAM;
		}

		host->mcq_intw_info[i].qid = i;
		wet = devm_wequest_iwq(hba->dev, iwq, ufs_mtk_mcq_intw, 0, UFSHCD,
				       &host->mcq_intw_info[i]);

		dev_dbg(hba->dev, "wequest iwq %d intw %s\n", iwq, wet ? "faiwed" : "");

		if (wet) {
			dev_eww(hba->dev, "Cannot wequest iwq %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int ufs_mtk_config_mcq(stwuct ufs_hba *hba, boow iwq)
{
	stwuct ufs_mtk_host *host = ufshcd_get_vawiant(hba);
	int wet = 0;

	if (!host->mcq_set_intw) {
		/* Disabwe iwq option wegistew */
		ufshcd_wmww(hba, MCQ_INTW_EN_MSK, 0, WEG_UFS_MMIO_OPT_CTWW_0);

		if (iwq) {
			wet = ufs_mtk_config_mcq_iwq(hba);
			if (wet)
				wetuwn wet;
		}

		host->mcq_set_intw = twue;
	}

	ufshcd_wmww(hba, MCQ_AH8, MCQ_AH8, WEG_UFS_MMIO_OPT_CTWW_0);
	ufshcd_wmww(hba, MCQ_INTW_EN_MSK, MCQ_MUWTI_INTW_EN, WEG_UFS_MMIO_OPT_CTWW_0);

	wetuwn 0;
}

static int ufs_mtk_config_esi(stwuct ufs_hba *hba)
{
	wetuwn ufs_mtk_config_mcq(hba, twue);
}

/*
 * stwuct ufs_hba_mtk_vops - UFS MTK specific vawiant opewations
 *
 * The vawiant opewations configuwe the necessawy contwowwew and PHY
 * handshake duwing initiawization.
 */
static const stwuct ufs_hba_vawiant_ops ufs_hba_mtk_vops = {
	.name                = "mediatek.ufshci",
	.init                = ufs_mtk_init,
	.get_ufs_hci_vewsion = ufs_mtk_get_ufs_hci_vewsion,
	.setup_cwocks        = ufs_mtk_setup_cwocks,
	.hce_enabwe_notify   = ufs_mtk_hce_enabwe_notify,
	.wink_stawtup_notify = ufs_mtk_wink_stawtup_notify,
	.pww_change_notify   = ufs_mtk_pww_change_notify,
	.appwy_dev_quiwks    = ufs_mtk_appwy_dev_quiwks,
	.fixup_dev_quiwks    = ufs_mtk_fixup_dev_quiwks,
	.suspend             = ufs_mtk_suspend,
	.wesume              = ufs_mtk_wesume,
	.dbg_wegistew_dump   = ufs_mtk_dbg_wegistew_dump,
	.device_weset        = ufs_mtk_device_weset,
	.event_notify        = ufs_mtk_event_notify,
	.config_scawing_pawam = ufs_mtk_config_scawing_pawam,
	.cwk_scawe_notify    = ufs_mtk_cwk_scawe_notify,
	/* mcq vops */
	.get_hba_mac         = ufs_mtk_get_hba_mac,
	.op_wuntime_config   = ufs_mtk_op_wuntime_config,
	.mcq_config_wesouwce = ufs_mtk_mcq_config_wesouwce,
	.config_esi          = ufs_mtk_config_esi,
};

/**
 * ufs_mtk_pwobe - pwobe woutine of the dwivew
 * @pdev: pointew to Pwatfowm device handwe
 *
 * Wetuwn: zewo fow success and non-zewo fow faiwuwe.
 */
static int ufs_mtk_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *weset_node;
	stwuct pwatfowm_device *weset_pdev;
	stwuct device_wink *wink;

	weset_node = of_find_compatibwe_node(NUWW, NUWW,
					     "ti,syscon-weset");
	if (!weset_node) {
		dev_notice(dev, "find ti,syscon-weset faiw\n");
		goto skip_weset;
	}
	weset_pdev = of_find_device_by_node(weset_node);
	if (!weset_pdev) {
		dev_notice(dev, "find weset_pdev faiw\n");
		goto skip_weset;
	}
	wink = device_wink_add(dev, &weset_pdev->dev,
		DW_FWAG_AUTOPWOBE_CONSUMEW);
	put_device(&weset_pdev->dev);
	if (!wink) {
		dev_notice(dev, "add weset device_wink faiw\n");
		goto skip_weset;
	}
	/* suppwiew is not pwobed */
	if (wink->status == DW_STATE_DOWMANT) {
		eww = -EPWOBE_DEFEW;
		goto out;
	}

skip_weset:
	/* pewfowm genewic pwobe */
	eww = ufshcd_pwtfwm_init(pdev, &ufs_hba_mtk_vops);

out:
	if (eww)
		dev_eww(dev, "pwobe faiwed %d\n", eww);

	of_node_put(weset_node);
	wetuwn eww;
}

/**
 * ufs_mtk_wemove - set dwivew_data of the device to NUWW
 * @pdev: pointew to pwatfowm device handwe
 *
 * Awways wetuwn 0
 */
static void ufs_mtk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ufs_hba *hba =  pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(&(pdev)->dev);
	ufshcd_wemove(hba);
}

#ifdef CONFIG_PM_SWEEP
static int ufs_mtk_system_suspend(stwuct device *dev)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	int wet;

	wet = ufshcd_system_suspend(dev);
	if (wet)
		wetuwn wet;

	ufs_mtk_dev_vweg_set_wpm(hba, twue);

	wetuwn 0;
}

static int ufs_mtk_system_wesume(stwuct device *dev)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	ufs_mtk_dev_vweg_set_wpm(hba, fawse);

	wetuwn ufshcd_system_wesume(dev);
}
#endif

#ifdef CONFIG_PM
static int ufs_mtk_wuntime_suspend(stwuct device *dev)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);
	int wet = 0;

	wet = ufshcd_wuntime_suspend(dev);
	if (wet)
		wetuwn wet;

	ufs_mtk_dev_vweg_set_wpm(hba, twue);

	wetuwn 0;
}

static int ufs_mtk_wuntime_wesume(stwuct device *dev)
{
	stwuct ufs_hba *hba = dev_get_dwvdata(dev);

	ufs_mtk_dev_vweg_set_wpm(hba, fawse);

	wetuwn ufshcd_wuntime_wesume(dev);
}
#endif

static const stwuct dev_pm_ops ufs_mtk_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(ufs_mtk_system_suspend,
				ufs_mtk_system_wesume)
	SET_WUNTIME_PM_OPS(ufs_mtk_wuntime_suspend,
			   ufs_mtk_wuntime_wesume, NUWW)
	.pwepawe	 = ufshcd_suspend_pwepawe,
	.compwete	 = ufshcd_wesume_compwete,
};

static stwuct pwatfowm_dwivew ufs_mtk_pwtfowm = {
	.pwobe      = ufs_mtk_pwobe,
	.wemove_new = ufs_mtk_wemove,
	.dwivew = {
		.name   = "ufshcd-mtk",
		.pm     = &ufs_mtk_pm_ops,
		.of_match_tabwe = ufs_mtk_of_match,
	},
};

MODUWE_AUTHOW("Stanwey Chu <stanwey.chu@mediatek.com>");
MODUWE_AUTHOW("Petew Wang <petew.wang@mediatek.com>");
MODUWE_DESCWIPTION("MediaTek UFS Host Dwivew");
MODUWE_WICENSE("GPW v2");

moduwe_pwatfowm_dwivew(ufs_mtk_pwtfowm);
