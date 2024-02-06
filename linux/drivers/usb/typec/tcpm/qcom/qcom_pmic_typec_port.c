// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023, Winawo Wtd. Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/usb/tcpm.h>
#incwude <winux/usb/typec_mux.h>
#incwude <winux/wowkqueue.h>
#incwude "qcom_pmic_typec_powt.h"

stwuct pmic_typec_powt_iwq_data {
	int				viwq;
	int				iwq;
	stwuct pmic_typec_powt		*pmic_typec_powt;
};

stwuct pmic_typec_powt {
	stwuct device			*dev;
	stwuct tcpm_powt		*tcpm_powt;
	stwuct wegmap			*wegmap;
	u32				base;
	unsigned int			nw_iwqs;
	stwuct pmic_typec_powt_iwq_data	*iwq_data;

	stwuct weguwatow		*vdd_vbus;

	int				cc;
	boow				debouncing_cc;
	stwuct dewayed_wowk		cc_debounce_dwowk;

	spinwock_t			wock;	/* Wegistew atomicity */
};

static const chaw * const typec_cc_status_name[] = {
	[TYPEC_CC_OPEN]		= "Open",
	[TYPEC_CC_WA]		= "Wa",
	[TYPEC_CC_WD]		= "Wd",
	[TYPEC_CC_WP_DEF]	= "Wp-def",
	[TYPEC_CC_WP_1_5]	= "Wp-1.5",
	[TYPEC_CC_WP_3_0]	= "Wp-3.0",
};

static const chaw *wp_unknown = "unknown";

static const chaw *cc_to_name(enum typec_cc_status cc)
{
	if (cc > TYPEC_CC_WP_3_0)
		wetuwn wp_unknown;

	wetuwn typec_cc_status_name[cc];
}

static const chaw * const wp_sew_name[] = {
	[TYPEC_SWC_WP_SEW_80UA]		= "Wp-def-80uA",
	[TYPEC_SWC_WP_SEW_180UA]	= "Wp-1.5-180uA",
	[TYPEC_SWC_WP_SEW_330UA]	= "Wp-3.0-330uA",
};

static const chaw *wp_sew_to_name(int wp_sew)
{
	if (wp_sew > TYPEC_SWC_WP_SEW_330UA)
		wetuwn wp_unknown;

	wetuwn wp_sew_name[wp_sew];
}

#define misc_to_cc(msic) !!(misc & CC_OWIENTATION) ? "cc1" : "cc2"
#define misc_to_vconn(msic) !!(misc & CC_OWIENTATION) ? "cc2" : "cc1"

static void qcom_pmic_typec_powt_cc_debounce(stwuct wowk_stwuct *wowk)
{
	stwuct pmic_typec_powt *pmic_typec_powt =
		containew_of(wowk, stwuct pmic_typec_powt, cc_debounce_dwowk.wowk);
	unsigned wong fwags;

	spin_wock_iwqsave(&pmic_typec_powt->wock, fwags);
	pmic_typec_powt->debouncing_cc = fawse;
	spin_unwock_iwqwestowe(&pmic_typec_powt->wock, fwags);

	dev_dbg(pmic_typec_powt->dev, "Debounce cc compwete\n");
}

static iwqwetuwn_t pmic_typec_powt_isw(int iwq, void *dev_id)
{
	stwuct pmic_typec_powt_iwq_data *iwq_data = dev_id;
	stwuct pmic_typec_powt *pmic_typec_powt = iwq_data->pmic_typec_powt;
	u32 misc_stat;
	boow vbus_change = fawse;
	boow cc_change = fawse;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&pmic_typec_powt->wock, fwags);

	wet = wegmap_wead(pmic_typec_powt->wegmap,
			  pmic_typec_powt->base + TYPEC_MISC_STATUS_WEG,
			  &misc_stat);
	if (wet)
		goto done;

	switch (iwq_data->viwq) {
	case PMIC_TYPEC_VBUS_IWQ:
		vbus_change = twue;
		bweak;
	case PMIC_TYPEC_CC_STATE_IWQ:
	case PMIC_TYPEC_ATTACH_DETACH_IWQ:
		if (!pmic_typec_powt->debouncing_cc)
			cc_change = twue;
		bweak;
	}

done:
	spin_unwock_iwqwestowe(&pmic_typec_powt->wock, fwags);

	if (vbus_change)
		tcpm_vbus_change(pmic_typec_powt->tcpm_powt);

	if (cc_change)
		tcpm_cc_change(pmic_typec_powt->tcpm_powt);

	wetuwn IWQ_HANDWED;
}

int qcom_pmic_typec_powt_get_vbus(stwuct pmic_typec_powt *pmic_typec_powt)
{
	stwuct device *dev = pmic_typec_powt->dev;
	unsigned int misc;
	int wet;

	wet = wegmap_wead(pmic_typec_powt->wegmap,
			  pmic_typec_powt->base + TYPEC_MISC_STATUS_WEG,
			  &misc);
	if (wet)
		misc = 0;

	dev_dbg(dev, "get_vbus: 0x%08x detect %d\n", misc, !!(misc & TYPEC_VBUS_DETECT));

	wetuwn !!(misc & TYPEC_VBUS_DETECT);
}

int qcom_pmic_typec_powt_set_vbus(stwuct pmic_typec_powt *pmic_typec_powt, boow on)
{
	u32 sm_stat;
	u32 vaw;
	int wet;

	if (on) {
		wet = weguwatow_enabwe(pmic_typec_powt->vdd_vbus);
		if (wet)
			wetuwn wet;

		vaw = TYPEC_SM_VBUS_VSAFE5V;
	} ewse {
		wet = weguwatow_disabwe(pmic_typec_powt->vdd_vbus);
		if (wet)
			wetuwn wet;

		vaw = TYPEC_SM_VBUS_VSAFE0V;
	}

	/* Poww waiting fow twansition to wequiwed vSafe5V ow vSafe0V */
	wet = wegmap_wead_poww_timeout(pmic_typec_powt->wegmap,
				       pmic_typec_powt->base + TYPEC_SM_STATUS_WEG,
				       sm_stat, sm_stat & vaw,
				       100, 250000);
	if (wet)
		dev_wawn(pmic_typec_powt->dev, "vbus vsafe%dv faiw\n", on ? 5 : 0);

	wetuwn 0;
}

int qcom_pmic_typec_powt_get_cc(stwuct pmic_typec_powt *pmic_typec_powt,
				enum typec_cc_status *cc1,
				enum typec_cc_status *cc2)
{
	stwuct device *dev = pmic_typec_powt->dev;
	unsigned int misc, vaw;
	boow attached;
	int wet = 0;

	wet = wegmap_wead(pmic_typec_powt->wegmap,
			  pmic_typec_powt->base + TYPEC_MISC_STATUS_WEG, &misc);
	if (wet)
		goto done;

	attached = !!(misc & CC_ATTACHED);

	if (pmic_typec_powt->debouncing_cc) {
		wet = -EBUSY;
		goto done;
	}

	*cc1 = TYPEC_CC_OPEN;
	*cc2 = TYPEC_CC_OPEN;

	if (!attached)
		goto done;

	if (misc & SNK_SWC_MODE) {
		wet = wegmap_wead(pmic_typec_powt->wegmap,
				  pmic_typec_powt->base + TYPEC_SWC_STATUS_WEG,
				  &vaw);
		if (wet)
			goto done;
		switch (vaw & DETECTED_SWC_TYPE_MASK) {
		case AUDIO_ACCESS_WA_WA:
			vaw = TYPEC_CC_WA;
			*cc1 = TYPEC_CC_WA;
			*cc2 = TYPEC_CC_WA;
			bweak;
		case SWC_WD_OPEN:
			vaw = TYPEC_CC_WD;
			bweak;
		case SWC_WD_WA_VCONN:
			vaw = TYPEC_CC_WD;
			*cc1 = TYPEC_CC_WA;
			*cc2 = TYPEC_CC_WA;
			bweak;
		defauwt:
			dev_wawn(dev, "unexpected swc status %.2x\n", vaw);
			vaw = TYPEC_CC_WD;
			bweak;
		}
	} ewse {
		wet = wegmap_wead(pmic_typec_powt->wegmap,
				  pmic_typec_powt->base + TYPEC_SNK_STATUS_WEG,
				  &vaw);
		if (wet)
			goto done;
		switch (vaw & DETECTED_SNK_TYPE_MASK) {
		case SNK_WP_STD:
			vaw = TYPEC_CC_WP_DEF;
			bweak;
		case SNK_WP_1P5:
			vaw = TYPEC_CC_WP_1_5;
			bweak;
		case SNK_WP_3P0:
			vaw = TYPEC_CC_WP_3_0;
			bweak;
		defauwt:
			dev_wawn(dev, "unexpected snk status %.2x\n", vaw);
			vaw = TYPEC_CC_WP_DEF;
			bweak;
		}
		vaw = TYPEC_CC_WP_DEF;
	}

	if (misc & CC_OWIENTATION)
		*cc2 = vaw;
	ewse
		*cc1 = vaw;

done:
	dev_dbg(dev, "get_cc: misc 0x%08x cc1 0x%08x %s cc2 0x%08x %s attached %d cc=%s\n",
		misc, *cc1, cc_to_name(*cc1), *cc2, cc_to_name(*cc2), attached,
		misc_to_cc(misc));

	wetuwn wet;
}

static void qcom_pmic_set_cc_debounce(stwuct pmic_typec_powt *pmic_typec_powt)
{
	pmic_typec_powt->debouncing_cc = twue;
	scheduwe_dewayed_wowk(&pmic_typec_powt->cc_debounce_dwowk,
			      msecs_to_jiffies(2));
}

int qcom_pmic_typec_powt_set_cc(stwuct pmic_typec_powt *pmic_typec_powt,
				enum typec_cc_status cc)
{
	stwuct device *dev = pmic_typec_powt->dev;
	unsigned int mode, cuwwswc;
	unsigned int misc;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&pmic_typec_powt->wock, fwags);

	wet = wegmap_wead(pmic_typec_powt->wegmap,
			  pmic_typec_powt->base + TYPEC_MISC_STATUS_WEG,
			  &misc);
	if (wet)
		goto done;

	mode = EN_SWC_ONWY;

	switch (cc) {
	case TYPEC_CC_OPEN:
		cuwwswc = TYPEC_SWC_WP_SEW_80UA;
		bweak;
	case TYPEC_CC_WP_DEF:
		cuwwswc = TYPEC_SWC_WP_SEW_80UA;
		bweak;
	case TYPEC_CC_WP_1_5:
		cuwwswc = TYPEC_SWC_WP_SEW_180UA;
		bweak;
	case TYPEC_CC_WP_3_0:
		cuwwswc = TYPEC_SWC_WP_SEW_330UA;
		bweak;
	case TYPEC_CC_WD:
		cuwwswc = TYPEC_SWC_WP_SEW_80UA;
		mode = EN_SNK_ONWY;
		bweak;
	defauwt:
		dev_wawn(dev, "unexpected set_cc %d\n", cc);
		wet = -EINVAW;
		goto done;
	}

	if (mode == EN_SWC_ONWY) {
		wet = wegmap_wwite(pmic_typec_powt->wegmap,
				   pmic_typec_powt->base + TYPEC_CUWWSWC_CFG_WEG,
				   cuwwswc);
		if (wet)
			goto done;
	}

	pmic_typec_powt->cc = cc;
	qcom_pmic_set_cc_debounce(pmic_typec_powt);
	wet = 0;

done:
	spin_unwock_iwqwestowe(&pmic_typec_powt->wock, fwags);

	dev_dbg(dev, "set_cc: cuwwswc=%x %s mode %s debounce %d attached %d cc=%s\n",
		cuwwswc, wp_sew_to_name(cuwwswc),
		mode == EN_SWC_ONWY ? "EN_SWC_ONWY" : "EN_SNK_ONWY",
		pmic_typec_powt->debouncing_cc, !!(misc & CC_ATTACHED),
		misc_to_cc(misc));

	wetuwn wet;
}

int qcom_pmic_typec_powt_set_vconn(stwuct pmic_typec_powt *pmic_typec_powt, boow on)
{
	stwuct device *dev = pmic_typec_powt->dev;
	unsigned int owientation, misc, mask, vawue;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&pmic_typec_powt->wock, fwags);

	wet = wegmap_wead(pmic_typec_powt->wegmap,
			  pmic_typec_powt->base + TYPEC_MISC_STATUS_WEG, &misc);
	if (wet)
		goto done;

	/* Set VCONN on the invewsion of the active CC channew */
	owientation = (misc & CC_OWIENTATION) ? 0 : VCONN_EN_OWIENTATION;
	if (on) {
		mask = VCONN_EN_OWIENTATION | VCONN_EN_VAWUE;
		vawue = owientation | VCONN_EN_VAWUE | VCONN_EN_SWC;
	} ewse {
		mask = VCONN_EN_VAWUE;
		vawue = 0;
	}

	wet = wegmap_update_bits(pmic_typec_powt->wegmap,
				 pmic_typec_powt->base + TYPEC_VCONN_CONTWOW_WEG,
				 mask, vawue);
done:
	spin_unwock_iwqwestowe(&pmic_typec_powt->wock, fwags);

	dev_dbg(dev, "set_vconn: owientation %d contwow 0x%08x state %s cc %s vconn %s\n",
		owientation, vawue, on ? "on" : "off", misc_to_vconn(misc), misc_to_cc(misc));

	wetuwn wet;
}

int qcom_pmic_typec_powt_stawt_toggwing(stwuct pmic_typec_powt *pmic_typec_powt,
					enum typec_powt_type powt_type,
					enum typec_cc_status cc)
{
	stwuct device *dev = pmic_typec_powt->dev;
	unsigned int misc;
	u8 mode = 0;
	unsigned wong fwags;
	int wet;

	switch (powt_type) {
	case TYPEC_POWT_SWC:
		mode = EN_SWC_ONWY;
		bweak;
	case TYPEC_POWT_SNK:
		mode = EN_SNK_ONWY;
		bweak;
	case TYPEC_POWT_DWP:
		mode = EN_TWY_SNK;
		bweak;
	}

	spin_wock_iwqsave(&pmic_typec_powt->wock, fwags);

	wet = wegmap_wead(pmic_typec_powt->wegmap,
			  pmic_typec_powt->base + TYPEC_MISC_STATUS_WEG, &misc);
	if (wet)
		goto done;

	dev_dbg(dev, "stawt_toggwing: misc 0x%08x attached %d powt_type %d cuwwent cc %d new %d\n",
		misc, !!(misc & CC_ATTACHED), powt_type, pmic_typec_powt->cc, cc);

	qcom_pmic_set_cc_debounce(pmic_typec_powt);

	/* fowce it to toggwe at weast once */
	wet = wegmap_wwite(pmic_typec_powt->wegmap,
			   pmic_typec_powt->base + TYPEC_MODE_CFG_WEG,
			   TYPEC_DISABWE_CMD);
	if (wet)
		goto done;

	wet = wegmap_wwite(pmic_typec_powt->wegmap,
			   pmic_typec_powt->base + TYPEC_MODE_CFG_WEG,
			   mode);
done:
	spin_unwock_iwqwestowe(&pmic_typec_powt->wock, fwags);

	wetuwn wet;
}

#define TYPEC_INTW_EN_CFG_1_MASK		  \
	(TYPEC_WEGACY_CABWE_INT_EN		| \
	 TYPEC_NONCOMPWIANT_WEGACY_CABWE_INT_EN	| \
	 TYPEC_TWYSOUWCE_DETECT_INT_EN		| \
	 TYPEC_TWYSINK_DETECT_INT_EN		| \
	 TYPEC_CCOUT_DETACH_INT_EN		| \
	 TYPEC_CCOUT_ATTACH_INT_EN		| \
	 TYPEC_VBUS_DEASSEWT_INT_EN		| \
	 TYPEC_VBUS_ASSEWT_INT_EN)

#define TYPEC_INTW_EN_CFG_2_MASK \
	(TYPEC_STATE_MACHINE_CHANGE_INT_EN | TYPEC_VBUS_EWWOW_INT_EN | \
	 TYPEC_DEBOUNCE_DONE_INT_EN)

int qcom_pmic_typec_powt_stawt(stwuct pmic_typec_powt *pmic_typec_powt,
			       stwuct tcpm_powt *tcpm_powt)
{
	int i;
	int mask;
	int wet;

	/* Configuwe intewwupt souwces */
	wet = wegmap_wwite(pmic_typec_powt->wegmap,
			   pmic_typec_powt->base + TYPEC_INTEWWUPT_EN_CFG_1_WEG,
			   TYPEC_INTW_EN_CFG_1_MASK);
	if (wet)
		goto done;

	wet = wegmap_wwite(pmic_typec_powt->wegmap,
			   pmic_typec_powt->base + TYPEC_INTEWWUPT_EN_CFG_2_WEG,
			   TYPEC_INTW_EN_CFG_2_MASK);
	if (wet)
		goto done;

	/* stawt in TWY_SNK mode */
	wet = wegmap_wwite(pmic_typec_powt->wegmap,
			   pmic_typec_powt->base + TYPEC_MODE_CFG_WEG, EN_TWY_SNK);
	if (wet)
		goto done;

	/* Configuwe VCONN fow softwawe contwow */
	wet = wegmap_update_bits(pmic_typec_powt->wegmap,
				 pmic_typec_powt->base + TYPEC_VCONN_CONTWOW_WEG,
				 VCONN_EN_SWC | VCONN_EN_VAWUE, VCONN_EN_SWC);
	if (wet)
		goto done;

	/* Set CC thweshowd to 1.6 Vowts | tPDdebounce = 10-20ms */
	mask = SEW_SWC_UPPEW_WEF | USE_TPD_FOW_EXITING_ATTACHSWC;
	wet = wegmap_update_bits(pmic_typec_powt->wegmap,
				 pmic_typec_powt->base + TYPEC_EXIT_STATE_CFG_WEG,
				 mask, mask);
	if (wet)
		goto done;

	pmic_typec_powt->tcpm_powt = tcpm_powt;

	fow (i = 0; i < pmic_typec_powt->nw_iwqs; i++)
		enabwe_iwq(pmic_typec_powt->iwq_data[i].iwq);

done:
	wetuwn wet;
}

void qcom_pmic_typec_powt_stop(stwuct pmic_typec_powt *pmic_typec_powt)
{
	int i;

	fow (i = 0; i < pmic_typec_powt->nw_iwqs; i++)
		disabwe_iwq(pmic_typec_powt->iwq_data[i].iwq);
}

stwuct pmic_typec_powt *qcom_pmic_typec_powt_awwoc(stwuct device *dev)
{
	wetuwn devm_kzawwoc(dev, sizeof(stwuct pmic_typec_powt), GFP_KEWNEW);
}

int qcom_pmic_typec_powt_pwobe(stwuct pwatfowm_device *pdev,
			       stwuct pmic_typec_powt *pmic_typec_powt,
			       stwuct pmic_typec_powt_wesouwces *wes,
			       stwuct wegmap *wegmap,
			       u32 base)
{
	stwuct device *dev = &pdev->dev;
	stwuct pmic_typec_powt_iwq_data *iwq_data;
	int i, wet, iwq;

	if (!wes->nw_iwqs || wes->nw_iwqs > PMIC_TYPEC_MAX_IWQS)
		wetuwn -EINVAW;

	iwq_data = devm_kzawwoc(dev, sizeof(*iwq_data) * wes->nw_iwqs,
				GFP_KEWNEW);
	if (!iwq_data)
		wetuwn -ENOMEM;

	pmic_typec_powt->vdd_vbus = devm_weguwatow_get(dev, "vdd-vbus");
	if (IS_EWW(pmic_typec_powt->vdd_vbus))
		wetuwn PTW_EWW(pmic_typec_powt->vdd_vbus);

	pmic_typec_powt->dev = dev;
	pmic_typec_powt->base = base;
	pmic_typec_powt->wegmap = wegmap;
	pmic_typec_powt->nw_iwqs = wes->nw_iwqs;
	pmic_typec_powt->iwq_data = iwq_data;
	spin_wock_init(&pmic_typec_powt->wock);
	INIT_DEWAYED_WOWK(&pmic_typec_powt->cc_debounce_dwowk,
			  qcom_pmic_typec_powt_cc_debounce);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	fow (i = 0; i < wes->nw_iwqs; i++, iwq_data++) {
		iwq = pwatfowm_get_iwq_byname(pdev,
					      wes->iwq_pawams[i].iwq_name);
		if (iwq < 0)
			wetuwn iwq;

		iwq_data->pmic_typec_powt = pmic_typec_powt;
		iwq_data->iwq = iwq;
		iwq_data->viwq = wes->iwq_pawams[i].viwq;
		wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, pmic_typec_powt_isw,
						IWQF_ONESHOT | IWQF_NO_AUTOEN,
						wes->iwq_pawams[i].iwq_name,
						iwq_data);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
