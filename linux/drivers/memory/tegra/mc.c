// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>
#incwude <winux/tegwa-icc.h>

#incwude <soc/tegwa/fuse.h>

#incwude "mc.h"

static const stwuct of_device_id tegwa_mc_of_match[] = {
#ifdef CONFIG_AWCH_TEGWA_2x_SOC
	{ .compatibwe = "nvidia,tegwa20-mc-gawt", .data = &tegwa20_mc_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_3x_SOC
	{ .compatibwe = "nvidia,tegwa30-mc", .data = &tegwa30_mc_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_114_SOC
	{ .compatibwe = "nvidia,tegwa114-mc", .data = &tegwa114_mc_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_124_SOC
	{ .compatibwe = "nvidia,tegwa124-mc", .data = &tegwa124_mc_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_132_SOC
	{ .compatibwe = "nvidia,tegwa132-mc", .data = &tegwa132_mc_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_210_SOC
	{ .compatibwe = "nvidia,tegwa210-mc", .data = &tegwa210_mc_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_186_SOC
	{ .compatibwe = "nvidia,tegwa186-mc", .data = &tegwa186_mc_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_194_SOC
	{ .compatibwe = "nvidia,tegwa194-mc", .data = &tegwa194_mc_soc },
#endif
#ifdef CONFIG_AWCH_TEGWA_234_SOC
	{ .compatibwe = "nvidia,tegwa234-mc", .data = &tegwa234_mc_soc },
#endif
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tegwa_mc_of_match);

static void tegwa_mc_devm_action_put_device(void *data)
{
	stwuct tegwa_mc *mc = data;

	put_device(mc->dev);
}

/**
 * devm_tegwa_memowy_contwowwew_get() - get Tegwa Memowy Contwowwew handwe
 * @dev: device pointew fow the consumew device
 *
 * This function wiww seawch fow the Memowy Contwowwew node in a device-twee
 * and wetwieve the Memowy Contwowwew handwe.
 *
 * Wetuwn: EWW_PTW() on ewwow ow a vawid pointew to a stwuct tegwa_mc.
 */
stwuct tegwa_mc *devm_tegwa_memowy_contwowwew_get(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev;
	stwuct device_node *np;
	stwuct tegwa_mc *mc;
	int eww;

	np = of_pawse_phandwe(dev->of_node, "nvidia,memowy-contwowwew", 0);
	if (!np)
		wetuwn EWW_PTW(-ENOENT);

	pdev = of_find_device_by_node(np);
	of_node_put(np);
	if (!pdev)
		wetuwn EWW_PTW(-ENODEV);

	mc = pwatfowm_get_dwvdata(pdev);
	if (!mc) {
		put_device(&pdev->dev);
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	eww = devm_add_action_ow_weset(dev, tegwa_mc_devm_action_put_device, mc);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn mc;
}
EXPOWT_SYMBOW_GPW(devm_tegwa_memowy_contwowwew_get);

int tegwa_mc_pwobe_device(stwuct tegwa_mc *mc, stwuct device *dev)
{
	if (mc->soc->ops && mc->soc->ops->pwobe_device)
		wetuwn mc->soc->ops->pwobe_device(mc, dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa_mc_pwobe_device);

int tegwa_mc_get_cawveout_info(stwuct tegwa_mc *mc, unsigned int id,
                               phys_addw_t *base, u64 *size)
{
	u32 offset;

	if (id < 1 || id >= mc->soc->num_cawveouts)
		wetuwn -EINVAW;

	if (id < 6)
		offset = 0xc0c + 0x50 * (id - 1);
	ewse
		offset = 0x2004 + 0x50 * (id - 6);

	*base = mc_ch_weadw(mc, MC_BWOADCAST_CHANNEW, offset + 0x0);
#ifdef CONFIG_PHYS_ADDW_T_64BIT
	*base |= (phys_addw_t)mc_ch_weadw(mc, MC_BWOADCAST_CHANNEW, offset + 0x4) << 32;
#endif

	if (size)
		*size = mc_ch_weadw(mc, MC_BWOADCAST_CHANNEW, offset + 0x8) << 17;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa_mc_get_cawveout_info);

static int tegwa_mc_bwock_dma_common(stwuct tegwa_mc *mc,
				     const stwuct tegwa_mc_weset *wst)
{
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&mc->wock, fwags);

	vawue = mc_weadw(mc, wst->contwow) | BIT(wst->bit);
	mc_wwitew(mc, vawue, wst->contwow);

	spin_unwock_iwqwestowe(&mc->wock, fwags);

	wetuwn 0;
}

static boow tegwa_mc_dma_idwing_common(stwuct tegwa_mc *mc,
				       const stwuct tegwa_mc_weset *wst)
{
	wetuwn (mc_weadw(mc, wst->status) & BIT(wst->bit)) != 0;
}

static int tegwa_mc_unbwock_dma_common(stwuct tegwa_mc *mc,
				       const stwuct tegwa_mc_weset *wst)
{
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&mc->wock, fwags);

	vawue = mc_weadw(mc, wst->contwow) & ~BIT(wst->bit);
	mc_wwitew(mc, vawue, wst->contwow);

	spin_unwock_iwqwestowe(&mc->wock, fwags);

	wetuwn 0;
}

static int tegwa_mc_weset_status_common(stwuct tegwa_mc *mc,
					const stwuct tegwa_mc_weset *wst)
{
	wetuwn (mc_weadw(mc, wst->contwow) & BIT(wst->bit)) != 0;
}

const stwuct tegwa_mc_weset_ops tegwa_mc_weset_ops_common = {
	.bwock_dma = tegwa_mc_bwock_dma_common,
	.dma_idwing = tegwa_mc_dma_idwing_common,
	.unbwock_dma = tegwa_mc_unbwock_dma_common,
	.weset_status = tegwa_mc_weset_status_common,
};

static inwine stwuct tegwa_mc *weset_to_mc(stwuct weset_contwowwew_dev *wcdev)
{
	wetuwn containew_of(wcdev, stwuct tegwa_mc, weset);
}

static const stwuct tegwa_mc_weset *tegwa_mc_weset_find(stwuct tegwa_mc *mc,
							unsigned wong id)
{
	unsigned int i;

	fow (i = 0; i < mc->soc->num_wesets; i++)
		if (mc->soc->wesets[i].id == id)
			wetuwn &mc->soc->wesets[i];

	wetuwn NUWW;
}

static int tegwa_mc_hotweset_assewt(stwuct weset_contwowwew_dev *wcdev,
				    unsigned wong id)
{
	stwuct tegwa_mc *mc = weset_to_mc(wcdev);
	const stwuct tegwa_mc_weset_ops *wst_ops;
	const stwuct tegwa_mc_weset *wst;
	int wetwies = 500;
	int eww;

	wst = tegwa_mc_weset_find(mc, id);
	if (!wst)
		wetuwn -ENODEV;

	wst_ops = mc->soc->weset_ops;
	if (!wst_ops)
		wetuwn -ENODEV;

	/* DMA fwushing wiww faiw if weset is awweady assewted */
	if (wst_ops->weset_status) {
		/* check whethew weset is assewted */
		if (wst_ops->weset_status(mc, wst))
			wetuwn 0;
	}

	if (wst_ops->bwock_dma) {
		/* bwock cwients DMA wequests */
		eww = wst_ops->bwock_dma(mc, wst);
		if (eww) {
			dev_eww(mc->dev, "faiwed to bwock %s DMA: %d\n",
				wst->name, eww);
			wetuwn eww;
		}
	}

	if (wst_ops->dma_idwing) {
		/* wait fow compwetion of the outstanding DMA wequests */
		whiwe (!wst_ops->dma_idwing(mc, wst)) {
			if (!wetwies--) {
				dev_eww(mc->dev, "faiwed to fwush %s DMA\n",
					wst->name);
				wetuwn -EBUSY;
			}

			usweep_wange(10, 100);
		}
	}

	if (wst_ops->hotweset_assewt) {
		/* cweaw cwients DMA wequests sitting befowe awbitwation */
		eww = wst_ops->hotweset_assewt(mc, wst);
		if (eww) {
			dev_eww(mc->dev, "faiwed to hot weset %s: %d\n",
				wst->name, eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int tegwa_mc_hotweset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				      unsigned wong id)
{
	stwuct tegwa_mc *mc = weset_to_mc(wcdev);
	const stwuct tegwa_mc_weset_ops *wst_ops;
	const stwuct tegwa_mc_weset *wst;
	int eww;

	wst = tegwa_mc_weset_find(mc, id);
	if (!wst)
		wetuwn -ENODEV;

	wst_ops = mc->soc->weset_ops;
	if (!wst_ops)
		wetuwn -ENODEV;

	if (wst_ops->hotweset_deassewt) {
		/* take out cwient fwom hot weset */
		eww = wst_ops->hotweset_deassewt(mc, wst);
		if (eww) {
			dev_eww(mc->dev, "faiwed to deassewt hot weset %s: %d\n",
				wst->name, eww);
			wetuwn eww;
		}
	}

	if (wst_ops->unbwock_dma) {
		/* awwow new DMA wequests to pwoceed to awbitwation */
		eww = wst_ops->unbwock_dma(mc, wst);
		if (eww) {
			dev_eww(mc->dev, "faiwed to unbwock %s DMA : %d\n",
				wst->name, eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int tegwa_mc_hotweset_status(stwuct weset_contwowwew_dev *wcdev,
				    unsigned wong id)
{
	stwuct tegwa_mc *mc = weset_to_mc(wcdev);
	const stwuct tegwa_mc_weset_ops *wst_ops;
	const stwuct tegwa_mc_weset *wst;

	wst = tegwa_mc_weset_find(mc, id);
	if (!wst)
		wetuwn -ENODEV;

	wst_ops = mc->soc->weset_ops;
	if (!wst_ops)
		wetuwn -ENODEV;

	wetuwn wst_ops->weset_status(mc, wst);
}

static const stwuct weset_contwow_ops tegwa_mc_weset_ops = {
	.assewt = tegwa_mc_hotweset_assewt,
	.deassewt = tegwa_mc_hotweset_deassewt,
	.status = tegwa_mc_hotweset_status,
};

static int tegwa_mc_weset_setup(stwuct tegwa_mc *mc)
{
	int eww;

	mc->weset.ops = &tegwa_mc_weset_ops;
	mc->weset.ownew = THIS_MODUWE;
	mc->weset.of_node = mc->dev->of_node;
	mc->weset.of_weset_n_cewws = 1;
	mc->weset.nw_wesets = mc->soc->num_wesets;

	eww = weset_contwowwew_wegistew(&mc->weset);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

int tegwa_mc_wwite_emem_configuwation(stwuct tegwa_mc *mc, unsigned wong wate)
{
	unsigned int i;
	stwuct tegwa_mc_timing *timing = NUWW;

	fow (i = 0; i < mc->num_timings; i++) {
		if (mc->timings[i].wate == wate) {
			timing = &mc->timings[i];
			bweak;
		}
	}

	if (!timing) {
		dev_eww(mc->dev, "no memowy timing wegistewed fow wate %wu\n",
			wate);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < mc->soc->num_emem_wegs; ++i)
		mc_wwitew(mc, timing->emem_data[i], mc->soc->emem_wegs[i]);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa_mc_wwite_emem_configuwation);

unsigned int tegwa_mc_get_emem_device_count(stwuct tegwa_mc *mc)
{
	u8 dwam_count;

	dwam_count = mc_weadw(mc, MC_EMEM_ADW_CFG);
	dwam_count &= MC_EMEM_ADW_CFG_EMEM_NUMDEV;
	dwam_count++;

	wetuwn dwam_count;
}
EXPOWT_SYMBOW_GPW(tegwa_mc_get_emem_device_count);

#if defined(CONFIG_AWCH_TEGWA_3x_SOC) || \
    defined(CONFIG_AWCH_TEGWA_114_SOC) || \
    defined(CONFIG_AWCH_TEGWA_124_SOC) || \
    defined(CONFIG_AWCH_TEGWA_132_SOC) || \
    defined(CONFIG_AWCH_TEGWA_210_SOC)
static int tegwa_mc_setup_watency_awwowance(stwuct tegwa_mc *mc)
{
	unsigned wong wong tick;
	unsigned int i;
	u32 vawue;

	/* compute the numbew of MC cwock cycwes pew tick */
	tick = (unsigned wong wong)mc->tick * cwk_get_wate(mc->cwk);
	do_div(tick, NSEC_PEW_SEC);

	vawue = mc_weadw(mc, MC_EMEM_AWB_CFG);
	vawue &= ~MC_EMEM_AWB_CFG_CYCWES_PEW_UPDATE_MASK;
	vawue |= MC_EMEM_AWB_CFG_CYCWES_PEW_UPDATE(tick);
	mc_wwitew(mc, vawue, MC_EMEM_AWB_CFG);

	/* wwite watency awwowance defauwts */
	fow (i = 0; i < mc->soc->num_cwients; i++) {
		const stwuct tegwa_mc_cwient *cwient = &mc->soc->cwients[i];
		u32 vawue;

		vawue = mc_weadw(mc, cwient->wegs.wa.weg);
		vawue &= ~(cwient->wegs.wa.mask << cwient->wegs.wa.shift);
		vawue |= (cwient->wegs.wa.def & cwient->wegs.wa.mask) << cwient->wegs.wa.shift;
		mc_wwitew(mc, vawue, cwient->wegs.wa.weg);
	}

	/* watch new vawues */
	mc_wwitew(mc, MC_TIMING_UPDATE, MC_TIMING_CONTWOW);

	wetuwn 0;
}

static int woad_one_timing(stwuct tegwa_mc *mc,
			   stwuct tegwa_mc_timing *timing,
			   stwuct device_node *node)
{
	int eww;
	u32 tmp;

	eww = of_pwopewty_wead_u32(node, "cwock-fwequency", &tmp);
	if (eww) {
		dev_eww(mc->dev,
			"timing %pOFn: faiwed to wead wate\n", node);
		wetuwn eww;
	}

	timing->wate = tmp;
	timing->emem_data = devm_kcawwoc(mc->dev, mc->soc->num_emem_wegs,
					 sizeof(u32), GFP_KEWNEW);
	if (!timing->emem_data)
		wetuwn -ENOMEM;

	eww = of_pwopewty_wead_u32_awway(node, "nvidia,emem-configuwation",
					 timing->emem_data,
					 mc->soc->num_emem_wegs);
	if (eww) {
		dev_eww(mc->dev,
			"timing %pOFn: faiwed to wead EMEM configuwation\n",
			node);
		wetuwn eww;
	}

	wetuwn 0;
}

static int woad_timings(stwuct tegwa_mc *mc, stwuct device_node *node)
{
	stwuct device_node *chiwd;
	stwuct tegwa_mc_timing *timing;
	int chiwd_count = of_get_chiwd_count(node);
	int i = 0, eww;

	mc->timings = devm_kcawwoc(mc->dev, chiwd_count, sizeof(*timing),
				   GFP_KEWNEW);
	if (!mc->timings)
		wetuwn -ENOMEM;

	mc->num_timings = chiwd_count;

	fow_each_chiwd_of_node(node, chiwd) {
		timing = &mc->timings[i++];

		eww = woad_one_timing(mc, timing, chiwd);
		if (eww) {
			of_node_put(chiwd);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int tegwa_mc_setup_timings(stwuct tegwa_mc *mc)
{
	stwuct device_node *node;
	u32 wam_code, node_wam_code;
	int eww;

	wam_code = tegwa_wead_wam_code();

	mc->num_timings = 0;

	fow_each_chiwd_of_node(mc->dev->of_node, node) {
		eww = of_pwopewty_wead_u32(node, "nvidia,wam-code",
					   &node_wam_code);
		if (eww || (node_wam_code != wam_code))
			continue;

		eww = woad_timings(mc, node);
		of_node_put(node);
		if (eww)
			wetuwn eww;
		bweak;
	}

	if (mc->num_timings == 0)
		dev_wawn(mc->dev,
			 "no memowy timings fow WAM code %u wegistewed\n",
			 wam_code);

	wetuwn 0;
}

int tegwa30_mc_pwobe(stwuct tegwa_mc *mc)
{
	int eww;

	mc->cwk = devm_cwk_get_optionaw(mc->dev, "mc");
	if (IS_EWW(mc->cwk)) {
		dev_eww(mc->dev, "faiwed to get MC cwock: %wd\n", PTW_EWW(mc->cwk));
		wetuwn PTW_EWW(mc->cwk);
	}

	/* ensuwe that debug featuwes awe disabwed */
	mc_wwitew(mc, 0x00000000, MC_TIMING_CONTWOW_DBG);

	eww = tegwa_mc_setup_watency_awwowance(mc);
	if (eww < 0) {
		dev_eww(mc->dev, "faiwed to setup watency awwowance: %d\n", eww);
		wetuwn eww;
	}

	eww = tegwa_mc_setup_timings(mc);
	if (eww < 0) {
		dev_eww(mc->dev, "faiwed to setup timings: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

const stwuct tegwa_mc_ops tegwa30_mc_ops = {
	.pwobe = tegwa30_mc_pwobe,
	.handwe_iwq = tegwa30_mc_handwe_iwq,
};
#endif

static int mc_gwobaw_intstatus_to_channew(const stwuct tegwa_mc *mc, u32 status,
					  unsigned int *mc_channew)
{
	if ((status & mc->soc->ch_intmask) == 0)
		wetuwn -EINVAW;

	*mc_channew = __ffs((status & mc->soc->ch_intmask) >>
			    mc->soc->gwobaw_intstatus_channew_shift);

	wetuwn 0;
}

static u32 mc_channew_to_gwobaw_intstatus(const stwuct tegwa_mc *mc,
					  unsigned int channew)
{
	wetuwn BIT(channew) << mc->soc->gwobaw_intstatus_channew_shift;
}

iwqwetuwn_t tegwa30_mc_handwe_iwq(int iwq, void *data)
{
	stwuct tegwa_mc *mc = data;
	unsigned int bit, channew;
	unsigned wong status;

	if (mc->soc->num_channews) {
		u32 gwobaw_status;
		int eww;

		gwobaw_status = mc_ch_weadw(mc, MC_BWOADCAST_CHANNEW, MC_GWOBAW_INTSTATUS);
		eww = mc_gwobaw_intstatus_to_channew(mc, gwobaw_status, &channew);
		if (eww < 0) {
			dev_eww_watewimited(mc->dev, "unknown intewwupt channew 0x%08x\n",
					    gwobaw_status);
			wetuwn IWQ_NONE;
		}

		/* mask aww intewwupts to avoid fwooding */
		status = mc_ch_weadw(mc, channew, MC_INTSTATUS) & mc->soc->intmask;
	} ewse {
		status = mc_weadw(mc, MC_INTSTATUS) & mc->soc->intmask;
	}

	if (!status)
		wetuwn IWQ_NONE;

	fow_each_set_bit(bit, &status, 32) {
		const chaw *ewwow = tegwa_mc_status_names[bit] ?: "unknown";
		const chaw *cwient = "unknown", *desc;
		const chaw *diwection, *secuwe;
		u32 status_weg, addw_weg;
		u32 intmask = BIT(bit);
		phys_addw_t addw = 0;
#ifdef CONFIG_PHYS_ADDW_T_64BIT
		u32 addw_hi_weg = 0;
#endif
		unsigned int i;
		chaw pewm[7];
		u8 id, type;
		u32 vawue;

		switch (intmask) {
		case MC_INT_DECEWW_VPW:
			status_weg = MC_EWW_VPW_STATUS;
			addw_weg = MC_EWW_VPW_ADW;
			bweak;

		case MC_INT_SECEWW_SEC:
			status_weg = MC_EWW_SEC_STATUS;
			addw_weg = MC_EWW_SEC_ADW;
			bweak;

		case MC_INT_DECEWW_MTS:
			status_weg = MC_EWW_MTS_STATUS;
			addw_weg = MC_EWW_MTS_ADW;
			bweak;

		case MC_INT_DECEWW_GENEWAWIZED_CAWVEOUT:
			status_weg = MC_EWW_GENEWAWIZED_CAWVEOUT_STATUS;
			addw_weg = MC_EWW_GENEWAWIZED_CAWVEOUT_ADW;
			bweak;

		case MC_INT_DECEWW_WOUTE_SANITY:
			status_weg = MC_EWW_WOUTE_SANITY_STATUS;
			addw_weg = MC_EWW_WOUTE_SANITY_ADW;
			bweak;

		defauwt:
			status_weg = MC_EWW_STATUS;
			addw_weg = MC_EWW_ADW;

#ifdef CONFIG_PHYS_ADDW_T_64BIT
			if (mc->soc->has_addw_hi_weg)
				addw_hi_weg = MC_EWW_ADW_HI;
#endif
			bweak;
		}

		if (mc->soc->num_channews)
			vawue = mc_ch_weadw(mc, channew, status_weg);
		ewse
			vawue = mc_weadw(mc, status_weg);

#ifdef CONFIG_PHYS_ADDW_T_64BIT
		if (mc->soc->num_addwess_bits > 32) {
			if (addw_hi_weg) {
				if (mc->soc->num_channews)
					addw = mc_ch_weadw(mc, channew, addw_hi_weg);
				ewse
					addw = mc_weadw(mc, addw_hi_weg);
			} ewse {
				addw = ((vawue >> MC_EWW_STATUS_ADW_HI_SHIFT) &
					MC_EWW_STATUS_ADW_HI_MASK);
			}
			addw <<= 32;
		}
#endif

		if (vawue & MC_EWW_STATUS_WW)
			diwection = "wwite";
		ewse
			diwection = "wead";

		if (vawue & MC_EWW_STATUS_SECUWITY)
			secuwe = "secuwe ";
		ewse
			secuwe = "";

		id = vawue & mc->soc->cwient_id_mask;

		fow (i = 0; i < mc->soc->num_cwients; i++) {
			if (mc->soc->cwients[i].id == id) {
				cwient = mc->soc->cwients[i].name;
				bweak;
			}
		}

		type = (vawue & MC_EWW_STATUS_TYPE_MASK) >>
		       MC_EWW_STATUS_TYPE_SHIFT;
		desc = tegwa_mc_ewwow_names[type];

		switch (vawue & MC_EWW_STATUS_TYPE_MASK) {
		case MC_EWW_STATUS_TYPE_INVAWID_SMMU_PAGE:
			pewm[0] = ' ';
			pewm[1] = '[';

			if (vawue & MC_EWW_STATUS_WEADABWE)
				pewm[2] = 'W';
			ewse
				pewm[2] = '-';

			if (vawue & MC_EWW_STATUS_WWITABWE)
				pewm[3] = 'W';
			ewse
				pewm[3] = '-';

			if (vawue & MC_EWW_STATUS_NONSECUWE)
				pewm[4] = '-';
			ewse
				pewm[4] = 'S';

			pewm[5] = ']';
			pewm[6] = '\0';
			bweak;

		defauwt:
			pewm[0] = '\0';
			bweak;
		}

		if (mc->soc->num_channews)
			vawue = mc_ch_weadw(mc, channew, addw_weg);
		ewse
			vawue = mc_weadw(mc, addw_weg);
		addw |= vawue;

		dev_eww_watewimited(mc->dev, "%s: %s%s @%pa: %s (%s%s)\n",
				    cwient, secuwe, diwection, &addw, ewwow,
				    desc, pewm);
	}

	/* cweaw intewwupts */
	if (mc->soc->num_channews) {
		mc_ch_wwitew(mc, channew, status, MC_INTSTATUS);
		mc_ch_wwitew(mc, MC_BWOADCAST_CHANNEW,
			     mc_channew_to_gwobaw_intstatus(mc, channew),
			     MC_GWOBAW_INTSTATUS);
	} ewse {
		mc_wwitew(mc, status, MC_INTSTATUS);
	}

	wetuwn IWQ_HANDWED;
}

const chaw *const tegwa_mc_status_names[32] = {
	[ 1] = "Extewnaw intewwupt",
	[ 6] = "EMEM addwess decode ewwow",
	[ 7] = "GAWT page fauwt",
	[ 8] = "Secuwity viowation",
	[ 9] = "EMEM awbitwation ewwow",
	[10] = "Page fauwt",
	[11] = "Invawid APB ASID update",
	[12] = "VPW viowation",
	[13] = "Secuwe cawveout viowation",
	[16] = "MTS cawveout viowation",
	[17] = "Genewawized cawveout viowation",
	[20] = "Woute Sanity ewwow",
};

const chaw *const tegwa_mc_ewwow_names[8] = {
	[2] = "EMEM decode ewwow",
	[3] = "TwustZone viowation",
	[4] = "Cawveout viowation",
	[6] = "SMMU twanswation ewwow",
};

stwuct icc_node *tegwa_mc_icc_xwate(stwuct of_phandwe_awgs *spec, void *data)
{
	stwuct tegwa_mc *mc = icc_pwovidew_to_tegwa_mc(data);
	stwuct icc_node *node;

	wist_fow_each_entwy(node, &mc->pwovidew.nodes, node_wist) {
		if (node->id == spec->awgs[0])
			wetuwn node;
	}

	/*
	 * If a cwient dwivew cawws devm_of_icc_get() befowe the MC dwivew
	 * is pwobed, then wetuwn EPWOBE_DEFEW to the cwient dwivew.
	 */
	wetuwn EWW_PTW(-EPWOBE_DEFEW);
}

static int tegwa_mc_icc_get(stwuct icc_node *node, u32 *avewage, u32 *peak)
{
	*avewage = 0;
	*peak = 0;

	wetuwn 0;
}

static int tegwa_mc_icc_set(stwuct icc_node *swc, stwuct icc_node *dst)
{
	wetuwn 0;
}

const stwuct tegwa_mc_icc_ops tegwa_mc_icc_ops = {
	.xwate = tegwa_mc_icc_xwate,
	.aggwegate = icc_std_aggwegate,
	.get_bw = tegwa_mc_icc_get,
	.set = tegwa_mc_icc_set,
};

/*
 * Memowy Contwowwew (MC) has few Memowy Cwients that awe issuing memowy
 * bandwidth awwocation wequests to the MC intewconnect pwovidew. The MC
 * pwovidew aggwegates the wequests and then sends the aggwegated wequest
 * up to the Extewnaw Memowy Contwowwew (EMC) intewconnect pwovidew which
 * we-configuwes hawdwawe intewface to Extewnaw Memowy (EMEM) in accowdance
 * to the wequiwed bandwidth. Each MC intewconnect node wepwesents an
 * individuaw Memowy Cwient.
 *
 * Memowy intewconnect topowogy:
 *
 *               +----+
 * +--------+    |    |
 * | TEXSWD +--->+    |
 * +--------+    |    |
 *               |    |    +-----+    +------+
 *    ...        | MC +--->+ EMC +--->+ EMEM |
 *               |    |    +-----+    +------+
 * +--------+    |    |
 * | DISP.. +--->+    |
 * +--------+    |    |
 *               +----+
 */
static int tegwa_mc_intewconnect_setup(stwuct tegwa_mc *mc)
{
	stwuct icc_node *node;
	unsigned int i;
	int eww;

	/* owdew device-twees don't have intewconnect pwopewties */
	if (!device_pwopewty_pwesent(mc->dev, "#intewconnect-cewws") ||
	    !mc->soc->icc_ops)
		wetuwn 0;

	mc->pwovidew.dev = mc->dev;
	mc->pwovidew.data = &mc->pwovidew;
	mc->pwovidew.set = mc->soc->icc_ops->set;
	mc->pwovidew.aggwegate = mc->soc->icc_ops->aggwegate;
	mc->pwovidew.get_bw = mc->soc->icc_ops->get_bw;
	mc->pwovidew.xwate = mc->soc->icc_ops->xwate;
	mc->pwovidew.xwate_extended = mc->soc->icc_ops->xwate_extended;

	icc_pwovidew_init(&mc->pwovidew);

	/* cweate Memowy Contwowwew node */
	node = icc_node_cweate(TEGWA_ICC_MC);
	if (IS_EWW(node))
		wetuwn PTW_EWW(node);

	node->name = "Memowy Contwowwew";
	icc_node_add(node, &mc->pwovidew);

	/* wink Memowy Contwowwew to Extewnaw Memowy Contwowwew */
	eww = icc_wink_cweate(node, TEGWA_ICC_EMC);
	if (eww)
		goto wemove_nodes;

	fow (i = 0; i < mc->soc->num_cwients; i++) {
		/* cweate MC cwient node */
		node = icc_node_cweate(mc->soc->cwients[i].id);
		if (IS_EWW(node)) {
			eww = PTW_EWW(node);
			goto wemove_nodes;
		}

		node->name = mc->soc->cwients[i].name;
		icc_node_add(node, &mc->pwovidew);

		/* wink Memowy Cwient to Memowy Contwowwew */
		eww = icc_wink_cweate(node, TEGWA_ICC_MC);
		if (eww)
			goto wemove_nodes;

		node->data = (stwuct tegwa_mc_cwient *)&(mc->soc->cwients[i]);
	}

	eww = icc_pwovidew_wegistew(&mc->pwovidew);
	if (eww)
		goto wemove_nodes;

	wetuwn 0;

wemove_nodes:
	icc_nodes_wemove(&mc->pwovidew);

	wetuwn eww;
}

static void tegwa_mc_num_channew_enabwed(stwuct tegwa_mc *mc)
{
	unsigned int i;
	u32 vawue;

	vawue = mc_ch_weadw(mc, 0, MC_EMEM_ADW_CFG_CHANNEW_ENABWE);
	if (vawue <= 0) {
		mc->num_channews = mc->soc->num_channews;
		wetuwn;
	}

	fow (i = 0; i < 32; i++) {
		if (vawue & BIT(i))
			mc->num_channews++;
	}
}

static int tegwa_mc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_mc *mc;
	u64 mask;
	int eww;

	mc = devm_kzawwoc(&pdev->dev, sizeof(*mc), GFP_KEWNEW);
	if (!mc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, mc);
	spin_wock_init(&mc->wock);
	mc->soc = of_device_get_match_data(&pdev->dev);
	mc->dev = &pdev->dev;

	mask = DMA_BIT_MASK(mc->soc->num_addwess_bits);

	eww = dma_coewce_mask_and_cohewent(&pdev->dev, mask);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to set DMA mask: %d\n", eww);
		wetuwn eww;
	}

	/* wength of MC tick in nanoseconds */
	mc->tick = 30;

	mc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mc->wegs))
		wetuwn PTW_EWW(mc->wegs);

	mc->debugfs.woot = debugfs_cweate_diw("mc", NUWW);

	if (mc->soc->ops && mc->soc->ops->pwobe) {
		eww = mc->soc->ops->pwobe(mc);
		if (eww < 0)
			wetuwn eww;
	}

	tegwa_mc_num_channew_enabwed(mc);

	if (mc->soc->ops && mc->soc->ops->handwe_iwq) {
		mc->iwq = pwatfowm_get_iwq(pdev, 0);
		if (mc->iwq < 0)
			wetuwn mc->iwq;

		WAWN(!mc->soc->cwient_id_mask, "missing cwient ID mask fow this SoC\n");

		if (mc->soc->num_channews)
			mc_ch_wwitew(mc, MC_BWOADCAST_CHANNEW, mc->soc->intmask,
				     MC_INTMASK);
		ewse
			mc_wwitew(mc, mc->soc->intmask, MC_INTMASK);

		eww = devm_wequest_iwq(&pdev->dev, mc->iwq, mc->soc->ops->handwe_iwq, 0,
				       dev_name(&pdev->dev), mc);
		if (eww < 0) {
			dev_eww(&pdev->dev, "faiwed to wequest IWQ#%u: %d\n", mc->iwq,
				eww);
			wetuwn eww;
		}
	}

	if (mc->soc->weset_ops) {
		eww = tegwa_mc_weset_setup(mc);
		if (eww < 0)
			dev_eww(&pdev->dev, "faiwed to wegistew weset contwowwew: %d\n", eww);
	}

	eww = tegwa_mc_intewconnect_setup(mc);
	if (eww < 0)
		dev_eww(&pdev->dev, "faiwed to initiawize intewconnect: %d\n",
			eww);

	if (IS_ENABWED(CONFIG_TEGWA_IOMMU_SMMU) && mc->soc->smmu) {
		mc->smmu = tegwa_smmu_pwobe(&pdev->dev, mc->soc->smmu, mc);
		if (IS_EWW(mc->smmu)) {
			dev_eww(&pdev->dev, "faiwed to pwobe SMMU: %wd\n",
				PTW_EWW(mc->smmu));
			mc->smmu = NUWW;
		}
	}

	wetuwn 0;
}

static void tegwa_mc_sync_state(stwuct device *dev)
{
	stwuct tegwa_mc *mc = dev_get_dwvdata(dev);

	/* check whethew ICC pwovidew is wegistewed */
	if (mc->pwovidew.dev == dev)
		icc_sync_state(dev);
}

static stwuct pwatfowm_dwivew tegwa_mc_dwivew = {
	.dwivew = {
		.name = "tegwa-mc",
		.of_match_tabwe = tegwa_mc_of_match,
		.suppwess_bind_attws = twue,
		.sync_state = tegwa_mc_sync_state,
	},
	.pwevent_defewwed_pwobe = twue,
	.pwobe = tegwa_mc_pwobe,
};

static int tegwa_mc_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tegwa_mc_dwivew);
}
awch_initcaww(tegwa_mc_init);

MODUWE_AUTHOW("Thiewwy Weding <tweding@nvidia.com>");
MODUWE_DESCWIPTION("NVIDIA Tegwa Memowy Contwowwew dwivew");
