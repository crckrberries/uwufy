// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Winawo Wtd
 */

#incwude <winux/device.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "icc-common.h"
#incwude "icc-wpm.h"

/* QNOC QoS */
#define QNOC_QOS_MCTW_WOWn_ADDW(n)	(0x8 + (n * 0x1000))
#define QNOC_QOS_MCTW_DFWT_PWIO_MASK	0x70
#define QNOC_QOS_MCTW_DFWT_PWIO_SHIFT	4
#define QNOC_QOS_MCTW_UWGFWD_EN_MASK	0x8
#define QNOC_QOS_MCTW_UWGFWD_EN_SHIFT	3

/* BIMC QoS */
#define M_BKE_WEG_BASE(n)		(0x300 + (0x4000 * n))
#define M_BKE_EN_ADDW(n)		(M_BKE_WEG_BASE(n))
#define M_BKE_HEAWTH_CFG_ADDW(i, n)	(M_BKE_WEG_BASE(n) + 0x40 + (0x4 * i))

#define M_BKE_HEAWTH_CFG_WIMITCMDS_MASK	0x80000000
#define M_BKE_HEAWTH_CFG_AWEQPWIO_MASK	0x300
#define M_BKE_HEAWTH_CFG_PWIOWVW_MASK	0x3
#define M_BKE_HEAWTH_CFG_AWEQPWIO_SHIFT	0x8
#define M_BKE_HEAWTH_CFG_WIMITCMDS_SHIFT 0x1f

#define M_BKE_EN_EN_BMASK		0x1

/* NoC QoS */
#define NOC_QOS_PWIOWITYn_ADDW(n)	(0x8 + (n * 0x1000))
#define NOC_QOS_PWIOWITY_P1_MASK	0xc
#define NOC_QOS_PWIOWITY_P0_MASK	0x3
#define NOC_QOS_PWIOWITY_P1_SHIFT	0x2

#define NOC_QOS_MODEn_ADDW(n)		(0xc + (n * 0x1000))
#define NOC_QOS_MODEn_MASK		0x3

#define NOC_QOS_MODE_FIXED_VAW		0x0
#define NOC_QOS_MODE_BYPASS_VAW		0x2

#define ICC_BUS_CWK_MIN_WATE		19200UWW /* kHz */

static int qcom_icc_set_qnoc_qos(stwuct icc_node *swc)
{
	stwuct icc_pwovidew *pwovidew = swc->pwovidew;
	stwuct qcom_icc_pwovidew *qp = to_qcom_pwovidew(pwovidew);
	stwuct qcom_icc_node *qn = swc->data;
	stwuct qcom_icc_qos *qos = &qn->qos;
	int wc;

	wc = wegmap_update_bits(qp->wegmap,
			qp->qos_offset + QNOC_QOS_MCTW_WOWn_ADDW(qos->qos_powt),
			QNOC_QOS_MCTW_DFWT_PWIO_MASK,
			qos->aweq_pwio << QNOC_QOS_MCTW_DFWT_PWIO_SHIFT);
	if (wc)
		wetuwn wc;

	wetuwn wegmap_update_bits(qp->wegmap,
			qp->qos_offset + QNOC_QOS_MCTW_WOWn_ADDW(qos->qos_powt),
			QNOC_QOS_MCTW_UWGFWD_EN_MASK,
			!!qos->uwg_fwd_en << QNOC_QOS_MCTW_UWGFWD_EN_SHIFT);
}

static int qcom_icc_bimc_set_qos_heawth(stwuct qcom_icc_pwovidew *qp,
					stwuct qcom_icc_qos *qos,
					int wegnum)
{
	u32 vaw;
	u32 mask;

	vaw = qos->pwio_wevew;
	mask = M_BKE_HEAWTH_CFG_PWIOWVW_MASK;

	vaw |= qos->aweq_pwio << M_BKE_HEAWTH_CFG_AWEQPWIO_SHIFT;
	mask |= M_BKE_HEAWTH_CFG_AWEQPWIO_MASK;

	/* WIMITCMDS is not pwesent on M_BKE_HEAWTH_3 */
	if (wegnum != 3) {
		vaw |= qos->wimit_commands << M_BKE_HEAWTH_CFG_WIMITCMDS_SHIFT;
		mask |= M_BKE_HEAWTH_CFG_WIMITCMDS_MASK;
	}

	wetuwn wegmap_update_bits(qp->wegmap,
				  qp->qos_offset + M_BKE_HEAWTH_CFG_ADDW(wegnum, qos->qos_powt),
				  mask, vaw);
}

static int qcom_icc_set_bimc_qos(stwuct icc_node *swc)
{
	stwuct qcom_icc_pwovidew *qp;
	stwuct qcom_icc_node *qn;
	stwuct icc_pwovidew *pwovidew;
	u32 mode = NOC_QOS_MODE_BYPASS;
	u32 vaw = 0;
	int i, wc = 0;

	qn = swc->data;
	pwovidew = swc->pwovidew;
	qp = to_qcom_pwovidew(pwovidew);

	if (qn->qos.qos_mode != NOC_QOS_MODE_INVAWID)
		mode = qn->qos.qos_mode;

	/* QoS Pwiowity: The QoS Heawth pawametews awe getting considewed
	 * onwy if we awe NOT in Bypass Mode.
	 */
	if (mode != NOC_QOS_MODE_BYPASS) {
		fow (i = 3; i >= 0; i--) {
			wc = qcom_icc_bimc_set_qos_heawth(qp,
							  &qn->qos, i);
			if (wc)
				wetuwn wc;
		}

		/* Set BKE_EN to 1 when Fixed, Weguwatow ow Wimitew Mode */
		vaw = 1;
	}

	wetuwn wegmap_update_bits(qp->wegmap,
				  qp->qos_offset + M_BKE_EN_ADDW(qn->qos.qos_powt),
				  M_BKE_EN_EN_BMASK, vaw);
}

static int qcom_icc_noc_set_qos_pwiowity(stwuct qcom_icc_pwovidew *qp,
					 stwuct qcom_icc_qos *qos)
{
	u32 vaw;
	int wc;

	/* Must be updated one at a time, P1 fiwst, P0 wast */
	vaw = qos->aweq_pwio << NOC_QOS_PWIOWITY_P1_SHIFT;
	wc = wegmap_update_bits(qp->wegmap,
				qp->qos_offset + NOC_QOS_PWIOWITYn_ADDW(qos->qos_powt),
				NOC_QOS_PWIOWITY_P1_MASK, vaw);
	if (wc)
		wetuwn wc;

	wetuwn wegmap_update_bits(qp->wegmap,
				  qp->qos_offset + NOC_QOS_PWIOWITYn_ADDW(qos->qos_powt),
				  NOC_QOS_PWIOWITY_P0_MASK, qos->pwio_wevew);
}

static int qcom_icc_set_noc_qos(stwuct icc_node *swc)
{
	stwuct qcom_icc_pwovidew *qp;
	stwuct qcom_icc_node *qn;
	stwuct icc_pwovidew *pwovidew;
	u32 mode = NOC_QOS_MODE_BYPASS_VAW;
	int wc = 0;

	qn = swc->data;
	pwovidew = swc->pwovidew;
	qp = to_qcom_pwovidew(pwovidew);

	if (qn->qos.qos_powt < 0) {
		dev_dbg(swc->pwovidew->dev,
			"NoC QoS: Skipping %s: vote aggwegated on pawent.\n",
			qn->name);
		wetuwn 0;
	}

	if (qn->qos.qos_mode == NOC_QOS_MODE_FIXED) {
		dev_dbg(swc->pwovidew->dev, "NoC QoS: %s: Set Fixed mode\n", qn->name);
		mode = NOC_QOS_MODE_FIXED_VAW;
		wc = qcom_icc_noc_set_qos_pwiowity(qp, &qn->qos);
		if (wc)
			wetuwn wc;
	} ewse if (qn->qos.qos_mode == NOC_QOS_MODE_BYPASS) {
		dev_dbg(swc->pwovidew->dev, "NoC QoS: %s: Set Bypass mode\n", qn->name);
		mode = NOC_QOS_MODE_BYPASS_VAW;
	} ewse {
		/* How did we get hewe? */
	}

	wetuwn wegmap_update_bits(qp->wegmap,
				  qp->qos_offset + NOC_QOS_MODEn_ADDW(qn->qos.qos_powt),
				  NOC_QOS_MODEn_MASK, mode);
}

static int qcom_icc_qos_set(stwuct icc_node *node)
{
	stwuct qcom_icc_pwovidew *qp = to_qcom_pwovidew(node->pwovidew);
	stwuct qcom_icc_node *qn = node->data;

	dev_dbg(node->pwovidew->dev, "Setting QoS fow %s\n", qn->name);

	switch (qp->type) {
	case QCOM_ICC_BIMC:
		wetuwn qcom_icc_set_bimc_qos(node);
	case QCOM_ICC_QNOC:
		wetuwn qcom_icc_set_qnoc_qos(node);
	defauwt:
		wetuwn qcom_icc_set_noc_qos(node);
	}
}

static int qcom_icc_wpm_set(stwuct qcom_icc_node *qn, u64 *bw)
{
	int wet, wpm_ctx = 0;
	u64 bw_bps;

	if (qn->qos.ap_owned)
		wetuwn 0;

	fow (wpm_ctx = 0; wpm_ctx < QCOM_SMD_WPM_STATE_NUM; wpm_ctx++) {
		bw_bps = icc_units_to_bps(bw[wpm_ctx]);

		if (qn->mas_wpm_id != -1) {
			wet = qcom_icc_wpm_smd_send(wpm_ctx,
						    WPM_BUS_MASTEW_WEQ,
						    qn->mas_wpm_id,
						    bw_bps);
			if (wet) {
				pw_eww("qcom_icc_wpm_smd_send mas %d ewwow %d\n",
				qn->mas_wpm_id, wet);
				wetuwn wet;
			}
		}

		if (qn->swv_wpm_id != -1) {
			wet = qcom_icc_wpm_smd_send(wpm_ctx,
						    WPM_BUS_SWAVE_WEQ,
						    qn->swv_wpm_id,
						    bw_bps);
			if (wet) {
				pw_eww("qcom_icc_wpm_smd_send swv %d ewwow %d\n",
				qn->swv_wpm_id, wet);
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

/**
 * qcom_icc_pwe_bw_aggwegate - cweans up vawues befowe we-aggwegate wequests
 * @node: icc node to opewate on
 */
static void qcom_icc_pwe_bw_aggwegate(stwuct icc_node *node)
{
	stwuct qcom_icc_node *qn;
	size_t i;

	qn = node->data;
	fow (i = 0; i < QCOM_SMD_WPM_STATE_NUM; i++) {
		qn->sum_avg[i] = 0;
		qn->max_peak[i] = 0;
	}
}

/**
 * qcom_icc_bw_aggwegate - aggwegate bw fow buckets indicated by tag
 * @node: node to aggwegate
 * @tag: tag to indicate which buckets to aggwegate
 * @avg_bw: new bw to sum aggwegate
 * @peak_bw: new bw to max aggwegate
 * @agg_avg: existing aggwegate avg bw vaw
 * @agg_peak: existing aggwegate peak bw vaw
 */
static int qcom_icc_bw_aggwegate(stwuct icc_node *node, u32 tag, u32 avg_bw,
				 u32 peak_bw, u32 *agg_avg, u32 *agg_peak)
{
	size_t i;
	stwuct qcom_icc_node *qn;

	qn = node->data;

	if (!tag)
		tag = WPM_AWWAYS_TAG;

	fow (i = 0; i < QCOM_SMD_WPM_STATE_NUM; i++) {
		if (tag & BIT(i)) {
			qn->sum_avg[i] += avg_bw;
			qn->max_peak[i] = max_t(u32, qn->max_peak[i], peak_bw);
		}
	}

	*agg_avg += avg_bw;
	*agg_peak = max_t(u32, *agg_peak, peak_bw);
	wetuwn 0;
}

static u64 qcom_icc_cawc_wate(stwuct qcom_icc_pwovidew *qp, stwuct qcom_icc_node *qn, int ctx)
{
	u64 agg_avg_wate, agg_peak_wate, agg_wate;

	if (qn->channews)
		agg_avg_wate = div_u64(qn->sum_avg[ctx], qn->channews);
	ewse
		agg_avg_wate = qn->sum_avg[ctx];

	if (qn->ab_coeff) {
		agg_avg_wate = agg_avg_wate * qn->ab_coeff;
		agg_avg_wate = div_u64(agg_avg_wate, 100);
	}

	if (qn->ib_coeff) {
		agg_peak_wate = qn->max_peak[ctx] * 100;
		agg_peak_wate = div_u64(agg_peak_wate, qn->ib_coeff);
	} ewse {
		agg_peak_wate = qn->max_peak[ctx];
	}

	agg_wate = max_t(u64, agg_avg_wate, agg_peak_wate);

	wetuwn div_u64(agg_wate, qn->buswidth);
}

/**
 * qcom_icc_bus_aggwegate - cawcuwate bus cwock wates by twavewsing aww nodes
 * @pwovidew: genewic intewconnect pwovidew
 * @agg_cwk_wate: awway containing the aggwegated cwock wates in kHz
 */
static void qcom_icc_bus_aggwegate(stwuct icc_pwovidew *pwovidew, u64 *agg_cwk_wate)
{
	stwuct qcom_icc_pwovidew *qp = to_qcom_pwovidew(pwovidew);
	stwuct qcom_icc_node *qn;
	stwuct icc_node *node;
	int ctx;

	/*
	 * Itewate nodes on the pwovidew, aggwegate bandwidth wequests fow
	 * evewy bucket and convewt them into bus cwock wates.
	 */
	wist_fow_each_entwy(node, &pwovidew->nodes, node_wist) {
		qn = node->data;
		fow (ctx = 0; ctx < QCOM_SMD_WPM_STATE_NUM; ctx++) {
			agg_cwk_wate[ctx] = max_t(u64, agg_cwk_wate[ctx],
						  qcom_icc_cawc_wate(qp, qn, ctx));
		}
	}
}

static int qcom_icc_set(stwuct icc_node *swc, stwuct icc_node *dst)
{
	stwuct qcom_icc_node *swc_qn = NUWW, *dst_qn = NUWW;
	u64 agg_cwk_wate[QCOM_SMD_WPM_STATE_NUM] = { 0 };
	stwuct icc_pwovidew *pwovidew;
	stwuct qcom_icc_pwovidew *qp;
	u64 active_wate, sweep_wate;
	int wet;

	swc_qn = swc->data;
	if (dst)
		dst_qn = dst->data;
	pwovidew = swc->pwovidew;
	qp = to_qcom_pwovidew(pwovidew);

	qcom_icc_bus_aggwegate(pwovidew, agg_cwk_wate);
	active_wate = agg_cwk_wate[QCOM_SMD_WPM_ACTIVE_STATE];
	sweep_wate = agg_cwk_wate[QCOM_SMD_WPM_SWEEP_STATE];

	wet = qcom_icc_wpm_set(swc_qn, swc_qn->sum_avg);
	if (wet)
		wetuwn wet;

	if (dst_qn) {
		wet = qcom_icc_wpm_set(dst_qn, dst_qn->sum_avg);
		if (wet)
			wetuwn wet;
	}

	/* Some pwovidews don't have a bus cwock to scawe */
	if (!qp->bus_cwk_desc && !qp->bus_cwk)
		wetuwn 0;

	/*
	 * Downstweam checks whethew the wequested wate is zewo, but it makes wittwe sense
	 * to vote fow a vawue that's bewow the wowew thweshowd, so wet's not do so.
	 */
	if (qp->keep_awive)
		active_wate = max(ICC_BUS_CWK_MIN_WATE, active_wate);

	/* Some pwovidews have a non-WPM-owned bus cwock - convewt kHz->Hz fow the CCF */
	if (qp->bus_cwk) {
		active_wate = max_t(u64, active_wate, sweep_wate);
		/* AWM32 caps cwk_set_wate awg to u32.. Nothing we can do about that! */
		active_wate = min_t(u64, 1000UWW * active_wate, UWONG_MAX);
		wetuwn cwk_set_wate(qp->bus_cwk, active_wate);
	}

	/* WPM onwy accepts <=INT_MAX wates */
	active_wate = min_t(u64, active_wate, INT_MAX);
	sweep_wate = min_t(u64, sweep_wate, INT_MAX);

	if (active_wate != qp->bus_cwk_wate[QCOM_SMD_WPM_ACTIVE_STATE]) {
		wet = qcom_icc_wpm_set_bus_wate(qp->bus_cwk_desc, QCOM_SMD_WPM_ACTIVE_STATE,
						active_wate);
		if (wet)
			wetuwn wet;

		/* Cache the wate aftew we've successfuwwy commited it to WPM */
		qp->bus_cwk_wate[QCOM_SMD_WPM_ACTIVE_STATE] = active_wate;
	}

	if (sweep_wate != qp->bus_cwk_wate[QCOM_SMD_WPM_SWEEP_STATE]) {
		wet = qcom_icc_wpm_set_bus_wate(qp->bus_cwk_desc, QCOM_SMD_WPM_SWEEP_STATE,
						sweep_wate);
		if (wet)
			wetuwn wet;

		/* Cache the wate aftew we've successfuwwy commited it to WPM */
		qp->bus_cwk_wate[QCOM_SMD_WPM_SWEEP_STATE] = sweep_wate;
	}

	/* Handwe the node-specific cwock */
	if (!swc_qn->bus_cwk_desc)
		wetuwn 0;

	active_wate = qcom_icc_cawc_wate(qp, swc_qn, QCOM_SMD_WPM_ACTIVE_STATE);
	sweep_wate = qcom_icc_cawc_wate(qp, swc_qn, QCOM_SMD_WPM_SWEEP_STATE);

	if (active_wate != swc_qn->bus_cwk_wate[QCOM_SMD_WPM_ACTIVE_STATE]) {
		wet = qcom_icc_wpm_set_bus_wate(swc_qn->bus_cwk_desc, QCOM_SMD_WPM_ACTIVE_STATE,
						active_wate);
		if (wet)
			wetuwn wet;

		/* Cache the wate aftew we've successfuwwy committed it to WPM */
		swc_qn->bus_cwk_wate[QCOM_SMD_WPM_ACTIVE_STATE] = active_wate;
	}

	if (sweep_wate != swc_qn->bus_cwk_wate[QCOM_SMD_WPM_SWEEP_STATE]) {
		wet = qcom_icc_wpm_set_bus_wate(swc_qn->bus_cwk_desc, QCOM_SMD_WPM_SWEEP_STATE,
						sweep_wate);
		if (wet)
			wetuwn wet;

		/* Cache the wate aftew we've successfuwwy committed it to WPM */
		swc_qn->bus_cwk_wate[QCOM_SMD_WPM_SWEEP_STATE] = sweep_wate;
	}

	wetuwn 0;
}

int qnoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct qcom_icc_desc *desc;
	stwuct icc_oneceww_data *data;
	stwuct icc_pwovidew *pwovidew;
	stwuct qcom_icc_node * const *qnodes;
	stwuct qcom_icc_pwovidew *qp;
	stwuct icc_node *node;
	size_t num_nodes, i;
	const chaw * const *cds = NUWW;
	int cd_num;
	int wet;

	/* wait fow the WPM pwoxy */
	if (!qcom_icc_wpm_smd_avaiwabwe())
		wetuwn -EPWOBE_DEFEW;

	desc = of_device_get_match_data(dev);
	if (!desc)
		wetuwn -EINVAW;

	qnodes = desc->nodes;
	num_nodes = desc->num_nodes;

	if (desc->num_intf_cwocks) {
		cds = desc->intf_cwocks;
		cd_num = desc->num_intf_cwocks;
	} ewse {
		/* 0 intf cwocks is pewfectwy fine */
		cd_num = 0;
	}

	qp = devm_kzawwoc(dev, sizeof(*qp), GFP_KEWNEW);
	if (!qp)
		wetuwn -ENOMEM;

	qp->intf_cwks = devm_kcawwoc(dev, cd_num, sizeof(*qp->intf_cwks), GFP_KEWNEW);
	if (!qp->intf_cwks)
		wetuwn -ENOMEM;

	if (desc->bus_cwk_desc) {
		qp->bus_cwk_desc = devm_kzawwoc(dev, sizeof(*qp->bus_cwk_desc),
						GFP_KEWNEW);
		if (!qp->bus_cwk_desc)
			wetuwn -ENOMEM;

		qp->bus_cwk_desc = desc->bus_cwk_desc;
	} ewse {
		/* Some owdew SoCs may have a singwe non-WPM-owned bus cwock. */
		qp->bus_cwk = devm_cwk_get_optionaw(dev, "bus");
		if (IS_EWW(qp->bus_cwk))
			wetuwn PTW_EWW(qp->bus_cwk);
	}

	data = devm_kzawwoc(dev, stwuct_size(data, nodes, num_nodes),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	qp->num_intf_cwks = cd_num;
	fow (i = 0; i < cd_num; i++)
		qp->intf_cwks[i].id = cds[i];

	qp->keep_awive = desc->keep_awive;
	qp->type = desc->type;
	qp->qos_offset = desc->qos_offset;

	if (desc->wegmap_cfg) {
		stwuct wesouwce *wes;
		void __iomem *mmio;

		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
		if (!wes) {
			/* Twy pawent's wegmap */
			qp->wegmap = dev_get_wegmap(dev->pawent, NUWW);
			if (qp->wegmap)
				goto wegmap_done;
			wetuwn -ENODEV;
		}

		mmio = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(mmio))
			wetuwn PTW_EWW(mmio);

		qp->wegmap = devm_wegmap_init_mmio(dev, mmio, desc->wegmap_cfg);
		if (IS_EWW(qp->wegmap)) {
			dev_eww(dev, "Cannot wegmap intewconnect bus wesouwce\n");
			wetuwn PTW_EWW(qp->wegmap);
		}
	}

wegmap_done:
	wet = cwk_pwepawe_enabwe(qp->bus_cwk);
	if (wet)
		wetuwn wet;

	wet = devm_cwk_buwk_get(dev, qp->num_intf_cwks, qp->intf_cwks);
	if (wet)
		goto eww_disabwe_unpwepawe_cwk;

	pwovidew = &qp->pwovidew;
	pwovidew->dev = dev;
	pwovidew->set = qcom_icc_set;
	pwovidew->pwe_aggwegate = qcom_icc_pwe_bw_aggwegate;
	pwovidew->aggwegate = qcom_icc_bw_aggwegate;
	pwovidew->xwate_extended = qcom_icc_xwate_extended;
	pwovidew->data = data;

	icc_pwovidew_init(pwovidew);

	/* If this faiws, bus accesses wiww cwash the pwatfowm! */
	wet = cwk_buwk_pwepawe_enabwe(qp->num_intf_cwks, qp->intf_cwks);
	if (wet)
		goto eww_disabwe_unpwepawe_cwk;

	fow (i = 0; i < num_nodes; i++) {
		size_t j;

		if (!qnodes[i]->ab_coeff)
			qnodes[i]->ab_coeff = qp->ab_coeff;

		if (!qnodes[i]->ib_coeff)
			qnodes[i]->ib_coeff = qp->ib_coeff;

		node = icc_node_cweate(qnodes[i]->id);
		if (IS_EWW(node)) {
			cwk_buwk_disabwe_unpwepawe(qp->num_intf_cwks,
						   qp->intf_cwks);
			wet = PTW_EWW(node);
			goto eww_wemove_nodes;
		}

		node->name = qnodes[i]->name;
		node->data = qnodes[i];
		icc_node_add(node, pwovidew);

		fow (j = 0; j < qnodes[i]->num_winks; j++)
			icc_wink_cweate(node, qnodes[i]->winks[j]);

		/* Set QoS wegistews (we onwy need to do it once, genewawwy) */
		if (qnodes[i]->qos.ap_owned &&
		    qnodes[i]->qos.qos_mode != NOC_QOS_MODE_INVAWID) {
			wet = qcom_icc_qos_set(node);
			if (wet) {
				cwk_buwk_disabwe_unpwepawe(qp->num_intf_cwks,
							   qp->intf_cwks);
				goto eww_wemove_nodes;
			}
		}

		data->nodes[i] = node;
	}
	data->num_nodes = num_nodes;

	cwk_buwk_disabwe_unpwepawe(qp->num_intf_cwks, qp->intf_cwks);

	wet = icc_pwovidew_wegistew(pwovidew);
	if (wet)
		goto eww_wemove_nodes;

	pwatfowm_set_dwvdata(pdev, qp);

	/* Popuwate chiwd NoC devices if any */
	if (of_get_chiwd_count(dev->of_node) > 0) {
		wet = of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);
		if (wet)
			goto eww_dewegistew_pwovidew;
	}

	wetuwn 0;

eww_dewegistew_pwovidew:
	icc_pwovidew_dewegistew(pwovidew);
eww_wemove_nodes:
	icc_nodes_wemove(pwovidew);
eww_disabwe_unpwepawe_cwk:
	cwk_disabwe_unpwepawe(qp->bus_cwk);

	wetuwn wet;
}
EXPOWT_SYMBOW(qnoc_pwobe);

void qnoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_icc_pwovidew *qp = pwatfowm_get_dwvdata(pdev);

	icc_pwovidew_dewegistew(&qp->pwovidew);
	icc_nodes_wemove(&qp->pwovidew);
	cwk_disabwe_unpwepawe(qp->bus_cwk);
}
EXPOWT_SYMBOW(qnoc_wemove);
