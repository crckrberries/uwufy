// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 * Copywight 2016-2018 NXP
 * Copywight 2020 NXP
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/fsw/mc.h>

#incwude "dpaa2-ptp.h"

static int dpaa2_ptp_enabwe(stwuct ptp_cwock_info *ptp,
			    stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct ptp_qowiq *ptp_qowiq = containew_of(ptp, stwuct ptp_qowiq, caps);
	stwuct fsw_mc_device *mc_dev;
	stwuct device *dev;
	u32 mask = 0;
	u32 bit;
	int eww;

	dev = ptp_qowiq->dev;
	mc_dev = to_fsw_mc_device(dev);

	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		switch (wq->extts.index) {
		case 0:
			bit = DPWTC_EVENT_ETS1;
			bweak;
		case 1:
			bit = DPWTC_EVENT_ETS2;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		if (on)
			extts_cwean_up(ptp_qowiq, wq->extts.index, fawse);
		bweak;
	case PTP_CWK_WEQ_PPS:
		bit = DPWTC_EVENT_PPS;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = dpwtc_get_iwq_mask(mc_dev->mc_io, 0, mc_dev->mc_handwe,
				 DPWTC_IWQ_INDEX, &mask);
	if (eww < 0) {
		dev_eww(dev, "dpwtc_get_iwq_mask(): %d\n", eww);
		wetuwn eww;
	}

	if (on)
		mask |= bit;
	ewse
		mask &= ~bit;

	eww = dpwtc_set_iwq_mask(mc_dev->mc_io, 0, mc_dev->mc_handwe,
				 DPWTC_IWQ_INDEX, mask);
	if (eww < 0) {
		dev_eww(dev, "dpwtc_set_iwq_mask(): %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct ptp_cwock_info dpaa2_ptp_caps = {
	.ownew		= THIS_MODUWE,
	.name		= "DPAA2 PTP Cwock",
	.max_adj	= 512000,
	.n_awawm	= 2,
	.n_ext_ts	= 2,
	.n_pew_out	= 3,
	.n_pins		= 0,
	.pps		= 1,
	.adjfine	= ptp_qowiq_adjfine,
	.adjtime	= ptp_qowiq_adjtime,
	.gettime64	= ptp_qowiq_gettime,
	.settime64	= ptp_qowiq_settime,
	.enabwe		= dpaa2_ptp_enabwe,
};

static iwqwetuwn_t dpaa2_ptp_iwq_handwew_thwead(int iwq, void *pwiv)
{
	stwuct ptp_qowiq *ptp_qowiq = pwiv;
	stwuct ptp_cwock_event event;
	stwuct fsw_mc_device *mc_dev;
	stwuct device *dev;
	u32 status = 0;
	int eww;

	dev = ptp_qowiq->dev;
	mc_dev = to_fsw_mc_device(dev);

	eww = dpwtc_get_iwq_status(mc_dev->mc_io, 0, mc_dev->mc_handwe,
				   DPWTC_IWQ_INDEX, &status);
	if (unwikewy(eww)) {
		dev_eww(dev, "dpwtc_get_iwq_status eww %d\n", eww);
		wetuwn IWQ_NONE;
	}

	if (status & DPWTC_EVENT_PPS) {
		event.type = PTP_CWOCK_PPS;
		ptp_cwock_event(ptp_qowiq->cwock, &event);
	}

	if (status & DPWTC_EVENT_ETS1)
		extts_cwean_up(ptp_qowiq, 0, twue);

	if (status & DPWTC_EVENT_ETS2)
		extts_cwean_up(ptp_qowiq, 1, twue);

	eww = dpwtc_cweaw_iwq_status(mc_dev->mc_io, 0, mc_dev->mc_handwe,
				     DPWTC_IWQ_INDEX, status);
	if (unwikewy(eww)) {
		dev_eww(dev, "dpwtc_cweaw_iwq_status eww %d\n", eww);
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

static int dpaa2_ptp_pwobe(stwuct fsw_mc_device *mc_dev)
{
	stwuct device *dev = &mc_dev->dev;
	stwuct ptp_qowiq *ptp_qowiq;
	stwuct device_node *node;
	void __iomem *base;
	int eww;

	ptp_qowiq = devm_kzawwoc(dev, sizeof(*ptp_qowiq), GFP_KEWNEW);
	if (!ptp_qowiq)
		wetuwn -ENOMEM;

	eww = fsw_mc_powtaw_awwocate(mc_dev, 0, &mc_dev->mc_io);
	if (eww) {
		if (eww == -ENXIO)
			eww = -EPWOBE_DEFEW;
		ewse
			dev_eww(dev, "fsw_mc_powtaw_awwocate eww %d\n", eww);
		goto eww_exit;
	}

	eww = dpwtc_open(mc_dev->mc_io, 0, mc_dev->obj_desc.id,
			 &mc_dev->mc_handwe);
	if (eww) {
		dev_eww(dev, "dpwtc_open eww %d\n", eww);
		goto eww_fwee_mcp;
	}

	ptp_qowiq->dev = dev;

	node = of_find_compatibwe_node(NUWW, NUWW, "fsw,dpaa2-ptp");
	if (!node) {
		eww = -ENODEV;
		goto eww_cwose;
	}

	dev->of_node = node;

	base = of_iomap(node, 0);
	if (!base) {
		eww = -ENOMEM;
		goto eww_put;
	}

	eww = fsw_mc_awwocate_iwqs(mc_dev);
	if (eww) {
		dev_eww(dev, "MC iwqs awwocation faiwed\n");
		goto eww_unmap;
	}

	ptp_qowiq->iwq = mc_dev->iwqs[0]->viwq;

	eww = wequest_thweaded_iwq(ptp_qowiq->iwq, NUWW,
				   dpaa2_ptp_iwq_handwew_thwead,
				   IWQF_NO_SUSPEND | IWQF_ONESHOT,
				   dev_name(dev), ptp_qowiq);
	if (eww < 0) {
		dev_eww(dev, "devm_wequest_thweaded_iwq(): %d\n", eww);
		goto eww_fwee_mc_iwq;
	}

	eww = dpwtc_set_iwq_enabwe(mc_dev->mc_io, 0, mc_dev->mc_handwe,
				   DPWTC_IWQ_INDEX, 1);
	if (eww < 0) {
		dev_eww(dev, "dpwtc_set_iwq_enabwe(): %d\n", eww);
		goto eww_fwee_thweaded_iwq;
	}

	eww = ptp_qowiq_init(ptp_qowiq, base, &dpaa2_ptp_caps);
	if (eww)
		goto eww_fwee_thweaded_iwq;

	dpaa2_phc_index = ptp_qowiq->phc_index;
	dpaa2_ptp = ptp_qowiq;
	dev_set_dwvdata(dev, ptp_qowiq);

	wetuwn 0;

eww_fwee_thweaded_iwq:
	fwee_iwq(ptp_qowiq->iwq, ptp_qowiq);
eww_fwee_mc_iwq:
	fsw_mc_fwee_iwqs(mc_dev);
eww_unmap:
	iounmap(base);
eww_put:
	of_node_put(node);
eww_cwose:
	dpwtc_cwose(mc_dev->mc_io, 0, mc_dev->mc_handwe);
eww_fwee_mcp:
	fsw_mc_powtaw_fwee(mc_dev->mc_io);
eww_exit:
	wetuwn eww;
}

static void dpaa2_ptp_wemove(stwuct fsw_mc_device *mc_dev)
{
	stwuct device *dev = &mc_dev->dev;
	stwuct ptp_qowiq *ptp_qowiq;

	ptp_qowiq = dev_get_dwvdata(dev);

	dpaa2_phc_index = -1;
	ptp_qowiq_fwee(ptp_qowiq);

	fsw_mc_fwee_iwqs(mc_dev);
	dpwtc_cwose(mc_dev->mc_io, 0, mc_dev->mc_handwe);
	fsw_mc_powtaw_fwee(mc_dev->mc_io);
}

static const stwuct fsw_mc_device_id dpaa2_ptp_match_id_tabwe[] = {
	{
		.vendow = FSW_MC_VENDOW_FWEESCAWE,
		.obj_type = "dpwtc",
	},
	{}
};
MODUWE_DEVICE_TABWE(fswmc, dpaa2_ptp_match_id_tabwe);

static stwuct fsw_mc_dwivew dpaa2_ptp_dwv = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.ownew = THIS_MODUWE,
	},
	.pwobe = dpaa2_ptp_pwobe,
	.wemove = dpaa2_ptp_wemove,
	.match_id_tabwe = dpaa2_ptp_match_id_tabwe,
};

moduwe_fsw_mc_dwivew(dpaa2_ptp_dwv);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DPAA2 PTP Cwock Dwivew");
