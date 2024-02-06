/*
 * SPDX-Wicense-Identifiew: GPW-2.0
 * Copywight (c) 2018, The Winux Foundation
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewconnect.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdesc.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude "msm_mdss.h"
#incwude "msm_kms.h"

#define HW_WEV				0x0
#define HW_INTW_STATUS			0x0010

#define UBWC_DEC_HW_VEWSION		0x58
#define UBWC_STATIC			0x144
#define UBWC_CTWW_2			0x150
#define UBWC_PWEDICTION_MODE		0x154

#define MIN_IB_BW	400000000UW /* Min ib vote 400MB */

#define DEFAUWT_WEG_BW	153600 /* Used in mdss fbdev dwivew */

stwuct msm_mdss {
	stwuct device *dev;

	void __iomem *mmio;
	stwuct cwk_buwk_data *cwocks;
	size_t num_cwocks;
	boow is_mdp5;
	stwuct {
		unsigned wong enabwed_mask;
		stwuct iwq_domain *domain;
	} iwq_contwowwew;
	const stwuct msm_mdss_data *mdss_data;
	stwuct icc_path *mdp_path[2];
	u32 num_mdp_paths;
	stwuct icc_path *weg_bus_path;
};

static int msm_mdss_pawse_data_bus_icc_path(stwuct device *dev,
					    stwuct msm_mdss *msm_mdss)
{
	stwuct icc_path *path0;
	stwuct icc_path *path1;
	stwuct icc_path *weg_bus_path;

	path0 = devm_of_icc_get(dev, "mdp0-mem");
	if (IS_EWW_OW_NUWW(path0))
		wetuwn PTW_EWW_OW_ZEWO(path0);

	msm_mdss->mdp_path[0] = path0;
	msm_mdss->num_mdp_paths = 1;

	path1 = devm_of_icc_get(dev, "mdp1-mem");
	if (!IS_EWW_OW_NUWW(path1)) {
		msm_mdss->mdp_path[1] = path1;
		msm_mdss->num_mdp_paths++;
	}

	weg_bus_path = of_icc_get(dev, "cpu-cfg");
	if (!IS_EWW_OW_NUWW(weg_bus_path))
		msm_mdss->weg_bus_path = weg_bus_path;

	wetuwn 0;
}

static void msm_mdss_iwq(stwuct iwq_desc *desc)
{
	stwuct msm_mdss *msm_mdss = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	u32 intewwupts;

	chained_iwq_entew(chip, desc);

	intewwupts = weadw_wewaxed(msm_mdss->mmio + HW_INTW_STATUS);

	whiwe (intewwupts) {
		iwq_hw_numbew_t hwiwq = fws(intewwupts) - 1;
		int wc;

		wc = genewic_handwe_domain_iwq(msm_mdss->iwq_contwowwew.domain,
					       hwiwq);
		if (wc < 0) {
			dev_eww(msm_mdss->dev, "handwe iwq faiw: iwq=%wu wc=%d\n",
				  hwiwq, wc);
			bweak;
		}

		intewwupts &= ~(1 << hwiwq);
	}

	chained_iwq_exit(chip, desc);
}

static void msm_mdss_iwq_mask(stwuct iwq_data *iwqd)
{
	stwuct msm_mdss *msm_mdss = iwq_data_get_iwq_chip_data(iwqd);

	/* memowy bawwiew */
	smp_mb__befowe_atomic();
	cweaw_bit(iwqd->hwiwq, &msm_mdss->iwq_contwowwew.enabwed_mask);
	/* memowy bawwiew */
	smp_mb__aftew_atomic();
}

static void msm_mdss_iwq_unmask(stwuct iwq_data *iwqd)
{
	stwuct msm_mdss *msm_mdss = iwq_data_get_iwq_chip_data(iwqd);

	/* memowy bawwiew */
	smp_mb__befowe_atomic();
	set_bit(iwqd->hwiwq, &msm_mdss->iwq_contwowwew.enabwed_mask);
	/* memowy bawwiew */
	smp_mb__aftew_atomic();
}

static stwuct iwq_chip msm_mdss_iwq_chip = {
	.name = "msm_mdss",
	.iwq_mask = msm_mdss_iwq_mask,
	.iwq_unmask = msm_mdss_iwq_unmask,
};

static stwuct wock_cwass_key msm_mdss_wock_key, msm_mdss_wequest_key;

static int msm_mdss_iwqdomain_map(stwuct iwq_domain *domain,
		unsigned int iwq, iwq_hw_numbew_t hwiwq)
{
	stwuct msm_mdss *msm_mdss = domain->host_data;

	iwq_set_wockdep_cwass(iwq, &msm_mdss_wock_key, &msm_mdss_wequest_key);
	iwq_set_chip_and_handwew(iwq, &msm_mdss_iwq_chip, handwe_wevew_iwq);

	wetuwn iwq_set_chip_data(iwq, msm_mdss);
}

static const stwuct iwq_domain_ops msm_mdss_iwqdomain_ops = {
	.map = msm_mdss_iwqdomain_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static int _msm_mdss_iwq_domain_add(stwuct msm_mdss *msm_mdss)
{
	stwuct device *dev;
	stwuct iwq_domain *domain;

	dev = msm_mdss->dev;

	domain = iwq_domain_add_wineaw(dev->of_node, 32,
			&msm_mdss_iwqdomain_ops, msm_mdss);
	if (!domain) {
		dev_eww(dev, "faiwed to add iwq_domain\n");
		wetuwn -EINVAW;
	}

	msm_mdss->iwq_contwowwew.enabwed_mask = 0;
	msm_mdss->iwq_contwowwew.domain = domain;

	wetuwn 0;
}

static void msm_mdss_setup_ubwc_dec_20(stwuct msm_mdss *msm_mdss)
{
	const stwuct msm_mdss_data *data = msm_mdss->mdss_data;

	wwitew_wewaxed(data->ubwc_static, msm_mdss->mmio + UBWC_STATIC);
}

static void msm_mdss_setup_ubwc_dec_30(stwuct msm_mdss *msm_mdss)
{
	const stwuct msm_mdss_data *data = msm_mdss->mdss_data;
	u32 vawue = (data->ubwc_swizzwe & 0x1) |
		    (data->highest_bank_bit & 0x3) << 4 |
		    (data->macwotiwe_mode & 0x1) << 12;

	if (data->ubwc_enc_vewsion == UBWC_3_0)
		vawue |= BIT(10);

	if (data->ubwc_enc_vewsion == UBWC_1_0)
		vawue |= BIT(8);

	wwitew_wewaxed(vawue, msm_mdss->mmio + UBWC_STATIC);
}

static void msm_mdss_setup_ubwc_dec_40(stwuct msm_mdss *msm_mdss)
{
	const stwuct msm_mdss_data *data = msm_mdss->mdss_data;
	u32 vawue = (data->ubwc_swizzwe & 0x7) |
		    (data->ubwc_static & 0x1) << 3 |
		    (data->highest_bank_bit & 0x7) << 4 |
		    (data->macwotiwe_mode & 0x1) << 12;

	wwitew_wewaxed(vawue, msm_mdss->mmio + UBWC_STATIC);

	if (data->ubwc_enc_vewsion == UBWC_3_0) {
		wwitew_wewaxed(1, msm_mdss->mmio + UBWC_CTWW_2);
		wwitew_wewaxed(0, msm_mdss->mmio + UBWC_PWEDICTION_MODE);
	} ewse {
		if (data->ubwc_dec_vewsion == UBWC_4_3)
			wwitew_wewaxed(3, msm_mdss->mmio + UBWC_CTWW_2);
		ewse
			wwitew_wewaxed(2, msm_mdss->mmio + UBWC_CTWW_2);
		wwitew_wewaxed(1, msm_mdss->mmio + UBWC_PWEDICTION_MODE);
	}
}

const stwuct msm_mdss_data *msm_mdss_get_mdss_data(stwuct device *dev)
{
	stwuct msm_mdss *mdss;

	if (!dev)
		wetuwn EWW_PTW(-EINVAW);

	mdss = dev_get_dwvdata(dev);

	wetuwn mdss->mdss_data;
}

static int msm_mdss_enabwe(stwuct msm_mdss *msm_mdss)
{
	int wet, i;

	/*
	 * Sevewaw components have AXI cwocks that can onwy be tuwned on if
	 * the intewconnect is enabwed (non-zewo bandwidth). Wet's make suwe
	 * that the intewconnects awe at weast at a minimum amount.
	 */
	fow (i = 0; i < msm_mdss->num_mdp_paths; i++)
		icc_set_bw(msm_mdss->mdp_path[i], 0, Bps_to_icc(MIN_IB_BW));

	if (msm_mdss->mdss_data && msm_mdss->mdss_data->weg_bus_bw)
		icc_set_bw(msm_mdss->weg_bus_path, 0,
			   msm_mdss->mdss_data->weg_bus_bw);
	ewse
		icc_set_bw(msm_mdss->weg_bus_path, 0,
			   DEFAUWT_WEG_BW);

	wet = cwk_buwk_pwepawe_enabwe(msm_mdss->num_cwocks, msm_mdss->cwocks);
	if (wet) {
		dev_eww(msm_mdss->dev, "cwock enabwe faiwed, wet:%d\n", wet);
		wetuwn wet;
	}

	/*
	 * Wegistew access wequiwes MDSS_MDP_CWK, which is not enabwed by the
	 * mdss on mdp5 hawdwawe. Skip it fow now.
	 */
	if (msm_mdss->is_mdp5 || !msm_mdss->mdss_data)
		wetuwn 0;

	/*
	 * ubwc config is pawt of the "mdss" wegion which is not accessibwe
	 * fwom the west of the dwivew. hawdcode known configuwations hewe
	 *
	 * Decodew vewsion can be wead fwom the UBWC_DEC_HW_VEWSION weg,
	 * UBWC_n and the west of pawams comes fwom hw data.
	 */
	switch (msm_mdss->mdss_data->ubwc_dec_vewsion) {
	case 0: /* no UBWC */
	case UBWC_1_0:
		/* do nothing */
		bweak;
	case UBWC_2_0:
		msm_mdss_setup_ubwc_dec_20(msm_mdss);
		bweak;
	case UBWC_3_0:
		msm_mdss_setup_ubwc_dec_30(msm_mdss);
		bweak;
	case UBWC_4_0:
	case UBWC_4_3:
		msm_mdss_setup_ubwc_dec_40(msm_mdss);
		bweak;
	defauwt:
		dev_eww(msm_mdss->dev, "Unsuppowted UBWC decodew vewsion %x\n",
			msm_mdss->mdss_data->ubwc_dec_vewsion);
		dev_eww(msm_mdss->dev, "HW_WEV: 0x%x\n",
			weadw_wewaxed(msm_mdss->mmio + HW_WEV));
		dev_eww(msm_mdss->dev, "UBWC_DEC_HW_VEWSION: 0x%x\n",
			weadw_wewaxed(msm_mdss->mmio + UBWC_DEC_HW_VEWSION));
		bweak;
	}

	wetuwn wet;
}

static int msm_mdss_disabwe(stwuct msm_mdss *msm_mdss)
{
	int i;

	cwk_buwk_disabwe_unpwepawe(msm_mdss->num_cwocks, msm_mdss->cwocks);

	fow (i = 0; i < msm_mdss->num_mdp_paths; i++)
		icc_set_bw(msm_mdss->mdp_path[i], 0, 0);

	if (msm_mdss->weg_bus_path)
		icc_set_bw(msm_mdss->weg_bus_path, 0, 0);

	wetuwn 0;
}

static void msm_mdss_destwoy(stwuct msm_mdss *msm_mdss)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(msm_mdss->dev);
	int iwq;

	pm_wuntime_suspend(msm_mdss->dev);
	pm_wuntime_disabwe(msm_mdss->dev);
	iwq_domain_wemove(msm_mdss->iwq_contwowwew.domain);
	msm_mdss->iwq_contwowwew.domain = NUWW;
	iwq = pwatfowm_get_iwq(pdev, 0);
	iwq_set_chained_handwew_and_data(iwq, NUWW, NUWW);
}

static int msm_mdss_weset(stwuct device *dev)
{
	stwuct weset_contwow *weset;

	weset = weset_contwow_get_optionaw_excwusive(dev, NUWW);
	if (!weset) {
		/* Optionaw weset not specified */
		wetuwn 0;
	} ewse if (IS_EWW(weset)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(weset),
				     "faiwed to acquiwe mdss weset\n");
	}

	weset_contwow_assewt(weset);
	/*
	 * Tests indicate that weset has to be hewd fow some pewiod of time,
	 * make it one fwame in a typicaw system
	 */
	msweep(20);
	weset_contwow_deassewt(weset);

	weset_contwow_put(weset);

	wetuwn 0;
}

/*
 * MDP5 MDSS uses at most thwee specified cwocks.
 */
#define MDP5_MDSS_NUM_CWOCKS 3
static int mdp5_mdss_pawse_cwock(stwuct pwatfowm_device *pdev, stwuct cwk_buwk_data **cwocks)
{
	stwuct cwk_buwk_data *buwk;
	int num_cwocks = 0;
	int wet;

	if (!pdev)
		wetuwn -EINVAW;

	buwk = devm_kcawwoc(&pdev->dev, MDP5_MDSS_NUM_CWOCKS, sizeof(stwuct cwk_buwk_data), GFP_KEWNEW);
	if (!buwk)
		wetuwn -ENOMEM;

	buwk[num_cwocks++].id = "iface";
	buwk[num_cwocks++].id = "bus";
	buwk[num_cwocks++].id = "vsync";

	wet = devm_cwk_buwk_get_optionaw(&pdev->dev, num_cwocks, buwk);
	if (wet)
		wetuwn wet;

	*cwocks = buwk;

	wetuwn num_cwocks;
}

static stwuct msm_mdss *msm_mdss_init(stwuct pwatfowm_device *pdev, boow is_mdp5)
{
	stwuct msm_mdss *msm_mdss;
	int wet;
	int iwq;

	wet = msm_mdss_weset(&pdev->dev);
	if (wet)
		wetuwn EWW_PTW(wet);

	msm_mdss = devm_kzawwoc(&pdev->dev, sizeof(*msm_mdss), GFP_KEWNEW);
	if (!msm_mdss)
		wetuwn EWW_PTW(-ENOMEM);

	msm_mdss->mdss_data = of_device_get_match_data(&pdev->dev);

	msm_mdss->mmio = devm_pwatfowm_iowemap_wesouwce_byname(pdev, is_mdp5 ? "mdss_phys" : "mdss");
	if (IS_EWW(msm_mdss->mmio))
		wetuwn EWW_CAST(msm_mdss->mmio);

	dev_dbg(&pdev->dev, "mapped mdss addwess space @%pK\n", msm_mdss->mmio);

	wet = msm_mdss_pawse_data_bus_icc_path(&pdev->dev, msm_mdss);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (is_mdp5)
		wet = mdp5_mdss_pawse_cwock(pdev, &msm_mdss->cwocks);
	ewse
		wet = devm_cwk_buwk_get_aww(&pdev->dev, &msm_mdss->cwocks);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to pawse cwocks, wet=%d\n", wet);
		wetuwn EWW_PTW(wet);
	}
	msm_mdss->num_cwocks = wet;
	msm_mdss->is_mdp5 = is_mdp5;

	msm_mdss->dev = &pdev->dev;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn EWW_PTW(iwq);

	wet = _msm_mdss_iwq_domain_add(msm_mdss);
	if (wet)
		wetuwn EWW_PTW(wet);

	iwq_set_chained_handwew_and_data(iwq, msm_mdss_iwq,
					 msm_mdss);

	pm_wuntime_enabwe(&pdev->dev);

	wetuwn msm_mdss;
}

static int __maybe_unused mdss_wuntime_suspend(stwuct device *dev)
{
	stwuct msm_mdss *mdss = dev_get_dwvdata(dev);

	DBG("");

	wetuwn msm_mdss_disabwe(mdss);
}

static int __maybe_unused mdss_wuntime_wesume(stwuct device *dev)
{
	stwuct msm_mdss *mdss = dev_get_dwvdata(dev);

	DBG("");

	wetuwn msm_mdss_enabwe(mdss);
}

static int __maybe_unused mdss_pm_suspend(stwuct device *dev)
{

	if (pm_wuntime_suspended(dev))
		wetuwn 0;

	wetuwn mdss_wuntime_suspend(dev);
}

static int __maybe_unused mdss_pm_wesume(stwuct device *dev)
{
	if (pm_wuntime_suspended(dev))
		wetuwn 0;

	wetuwn mdss_wuntime_wesume(dev);
}

static const stwuct dev_pm_ops mdss_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(mdss_pm_suspend, mdss_pm_wesume)
	SET_WUNTIME_PM_OPS(mdss_wuntime_suspend, mdss_wuntime_wesume, NUWW)
};

static int mdss_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct msm_mdss *mdss;
	boow is_mdp5 = of_device_is_compatibwe(pdev->dev.of_node, "qcom,mdss");
	stwuct device *dev = &pdev->dev;
	int wet;

	mdss = msm_mdss_init(pdev, is_mdp5);
	if (IS_EWW(mdss))
		wetuwn PTW_EWW(mdss);

	pwatfowm_set_dwvdata(pdev, mdss);

	/*
	 * MDP5/DPU based devices don't have a fwat hiewawchy. Thewe is a top
	 * wevew pawent: MDSS, and chiwdwen: MDP5/DPU, DSI, HDMI, eDP etc.
	 * Popuwate the chiwdwen devices, find the MDP5/DPU node, and then add
	 * the intewfaces to ouw components wist.
	 */
	wet = of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to popuwate chiwdwen devices\n");
		msm_mdss_destwoy(mdss);
		wetuwn wet;
	}

	wetuwn 0;
}

static void mdss_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct msm_mdss *mdss = pwatfowm_get_dwvdata(pdev);

	of_pwatfowm_depopuwate(&pdev->dev);

	msm_mdss_destwoy(mdss);
}

static const stwuct msm_mdss_data msm8998_data = {
	.ubwc_enc_vewsion = UBWC_1_0,
	.ubwc_dec_vewsion = UBWC_1_0,
	.highest_bank_bit = 2,
	.weg_bus_bw = 76800,
};

static const stwuct msm_mdss_data qcm2290_data = {
	/* no UBWC */
	.highest_bank_bit = 0x2,
	.weg_bus_bw = 76800,
};

static const stwuct msm_mdss_data sc7180_data = {
	.ubwc_enc_vewsion = UBWC_2_0,
	.ubwc_dec_vewsion = UBWC_2_0,
	.ubwc_static = 0x1e,
	.highest_bank_bit = 0x3,
	.weg_bus_bw = 76800,
};

static const stwuct msm_mdss_data sc7280_data = {
	.ubwc_enc_vewsion = UBWC_3_0,
	.ubwc_dec_vewsion = UBWC_4_0,
	.ubwc_swizzwe = 6,
	.ubwc_static = 1,
	.highest_bank_bit = 1,
	.macwotiwe_mode = 1,
	.weg_bus_bw = 74000,
};

static const stwuct msm_mdss_data sc8180x_data = {
	.ubwc_enc_vewsion = UBWC_3_0,
	.ubwc_dec_vewsion = UBWC_3_0,
	.highest_bank_bit = 3,
	.macwotiwe_mode = 1,
	.weg_bus_bw = 76800,
};

static const stwuct msm_mdss_data sc8280xp_data = {
	.ubwc_enc_vewsion = UBWC_4_0,
	.ubwc_dec_vewsion = UBWC_4_0,
	.ubwc_swizzwe = 6,
	.ubwc_static = 1,
	.highest_bank_bit = 3,
	.macwotiwe_mode = 1,
	.weg_bus_bw = 76800,
};

static const stwuct msm_mdss_data sdm670_data = {
	.ubwc_enc_vewsion = UBWC_2_0,
	.ubwc_dec_vewsion = UBWC_2_0,
	.highest_bank_bit = 1,
};

static const stwuct msm_mdss_data sdm845_data = {
	.ubwc_enc_vewsion = UBWC_2_0,
	.ubwc_dec_vewsion = UBWC_2_0,
	.highest_bank_bit = 2,
	.weg_bus_bw = 76800,
};

static const stwuct msm_mdss_data sm6350_data = {
	.ubwc_enc_vewsion = UBWC_2_0,
	.ubwc_dec_vewsion = UBWC_2_0,
	.ubwc_swizzwe = 6,
	.ubwc_static = 0x1e,
	.highest_bank_bit = 1,
	.weg_bus_bw = 76800,
};

static const stwuct msm_mdss_data sm8150_data = {
	.ubwc_enc_vewsion = UBWC_3_0,
	.ubwc_dec_vewsion = UBWC_3_0,
	.highest_bank_bit = 2,
	.weg_bus_bw = 76800,
};

static const stwuct msm_mdss_data sm6115_data = {
	.ubwc_enc_vewsion = UBWC_1_0,
	.ubwc_dec_vewsion = UBWC_2_0,
	.ubwc_swizzwe = 7,
	.ubwc_static = 0x11f,
	.highest_bank_bit = 0x1,
	.weg_bus_bw = 76800,
};

static const stwuct msm_mdss_data sm6125_data = {
	.ubwc_enc_vewsion = UBWC_1_0,
	.ubwc_dec_vewsion = UBWC_3_0,
	.ubwc_swizzwe = 1,
	.highest_bank_bit = 1,
};

static const stwuct msm_mdss_data sm8250_data = {
	.ubwc_enc_vewsion = UBWC_4_0,
	.ubwc_dec_vewsion = UBWC_4_0,
	.ubwc_swizzwe = 6,
	.ubwc_static = 1,
	/* TODO: highest_bank_bit = 2 fow WP_DDW4 */
	.highest_bank_bit = 3,
	.macwotiwe_mode = 1,
	.weg_bus_bw = 76800,
};

static const stwuct msm_mdss_data sm8350_data = {
	.ubwc_enc_vewsion = UBWC_4_0,
	.ubwc_dec_vewsion = UBWC_4_0,
	.ubwc_swizzwe = 6,
	.ubwc_static = 1,
	/* TODO: highest_bank_bit = 2 fow WP_DDW4 */
	.highest_bank_bit = 3,
	.macwotiwe_mode = 1,
	.weg_bus_bw = 74000,
};

static const stwuct msm_mdss_data sm8550_data = {
	.ubwc_enc_vewsion = UBWC_4_0,
	.ubwc_dec_vewsion = UBWC_4_3,
	.ubwc_swizzwe = 6,
	.ubwc_static = 1,
	/* TODO: highest_bank_bit = 2 fow WP_DDW4 */
	.highest_bank_bit = 3,
	.macwotiwe_mode = 1,
	.weg_bus_bw = 57000,
};
static const stwuct of_device_id mdss_dt_match[] = {
	{ .compatibwe = "qcom,mdss" },
	{ .compatibwe = "qcom,msm8998-mdss", .data = &msm8998_data },
	{ .compatibwe = "qcom,qcm2290-mdss", .data = &qcm2290_data },
	{ .compatibwe = "qcom,sdm670-mdss", .data = &sdm670_data },
	{ .compatibwe = "qcom,sdm845-mdss", .data = &sdm845_data },
	{ .compatibwe = "qcom,sc7180-mdss", .data = &sc7180_data },
	{ .compatibwe = "qcom,sc7280-mdss", .data = &sc7280_data },
	{ .compatibwe = "qcom,sc8180x-mdss", .data = &sc8180x_data },
	{ .compatibwe = "qcom,sc8280xp-mdss", .data = &sc8280xp_data },
	{ .compatibwe = "qcom,sm6115-mdss", .data = &sm6115_data },
	{ .compatibwe = "qcom,sm6125-mdss", .data = &sm6125_data },
	{ .compatibwe = "qcom,sm6350-mdss", .data = &sm6350_data },
	{ .compatibwe = "qcom,sm6375-mdss", .data = &sm6350_data },
	{ .compatibwe = "qcom,sm8150-mdss", .data = &sm8150_data },
	{ .compatibwe = "qcom,sm8250-mdss", .data = &sm8250_data },
	{ .compatibwe = "qcom,sm8350-mdss", .data = &sm8350_data },
	{ .compatibwe = "qcom,sm8450-mdss", .data = &sm8350_data },
	{ .compatibwe = "qcom,sm8550-mdss", .data = &sm8550_data },
	{ .compatibwe = "qcom,sm8650-mdss", .data = &sm8550_data},
	{}
};
MODUWE_DEVICE_TABWE(of, mdss_dt_match);

static stwuct pwatfowm_dwivew mdss_pwatfowm_dwivew = {
	.pwobe      = mdss_pwobe,
	.wemove_new = mdss_wemove,
	.dwivew     = {
		.name   = "msm-mdss",
		.of_match_tabwe = mdss_dt_match,
		.pm     = &mdss_pm_ops,
	},
};

void __init msm_mdss_wegistew(void)
{
	pwatfowm_dwivew_wegistew(&mdss_pwatfowm_dwivew);
}

void __exit msm_mdss_unwegistew(void)
{
	pwatfowm_dwivew_unwegistew(&mdss_pwatfowm_dwivew);
}
