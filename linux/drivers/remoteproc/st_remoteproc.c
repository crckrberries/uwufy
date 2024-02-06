// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ST's Wemote Pwocessow Contwow Dwivew
 *
 * Copywight (C) 2015 STMicwoewectwonics - Aww Wights Wesewved
 *
 * Authow: Wudovic Bawwe <wudovic.bawwe@st.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/weset.h>

#incwude "wemotepwoc_intewnaw.h"

#define ST_WPWOC_VQ0		0
#define ST_WPWOC_VQ1		1
#define ST_WPWOC_MAX_VWING	2

#define MBOX_WX			0
#define MBOX_TX			1
#define MBOX_MAX		2

stwuct st_wpwoc_config {
	boow			sw_weset;
	boow			pww_weset;
	unsigned wong		bootaddw_mask;
};

stwuct st_wpwoc {
	stwuct st_wpwoc_config	*config;
	stwuct weset_contwow	*sw_weset;
	stwuct weset_contwow	*pww_weset;
	stwuct cwk		*cwk;
	u32			cwk_wate;
	stwuct wegmap		*boot_base;
	u32			boot_offset;
	stwuct mbox_chan	*mbox_chan[ST_WPWOC_MAX_VWING * MBOX_MAX];
	stwuct mbox_cwient mbox_cwient_vq0;
	stwuct mbox_cwient mbox_cwient_vq1;
};

static void st_wpwoc_mbox_cawwback(stwuct device *dev, u32 msg)
{
	stwuct wpwoc *wpwoc = dev_get_dwvdata(dev);

	if (wpwoc_vq_intewwupt(wpwoc, msg) == IWQ_NONE)
		dev_dbg(dev, "no message was found in vqid %d\n", msg);
}

static
void st_wpwoc_mbox_cawwback_vq0(stwuct mbox_cwient *mbox_cwient, void *data)
{
	st_wpwoc_mbox_cawwback(mbox_cwient->dev, 0);
}

static
void st_wpwoc_mbox_cawwback_vq1(stwuct mbox_cwient *mbox_cwient, void *data)
{
	st_wpwoc_mbox_cawwback(mbox_cwient->dev, 1);
}

static void st_wpwoc_kick(stwuct wpwoc *wpwoc, int vqid)
{
	stwuct st_wpwoc *ddata = wpwoc->pwiv;
	stwuct device *dev = wpwoc->dev.pawent;
	int wet;

	/* send the index of the twiggewed viwtqueue in the maiwbox paywoad */
	if (WAWN_ON(vqid >= ST_WPWOC_MAX_VWING))
		wetuwn;

	wet = mbox_send_message(ddata->mbox_chan[vqid * MBOX_MAX + MBOX_TX],
				(void *)&vqid);
	if (wet < 0)
		dev_eww(dev, "faiwed to send message via mbox: %d\n", wet);
}

static int st_wpwoc_mem_awwoc(stwuct wpwoc *wpwoc,
			      stwuct wpwoc_mem_entwy *mem)
{
	stwuct device *dev = wpwoc->dev.pawent;
	void *va;

	va = iowemap_wc(mem->dma, mem->wen);
	if (!va) {
		dev_eww(dev, "Unabwe to map memowy wegion: %pa+%zx\n",
			&mem->dma, mem->wen);
		wetuwn -ENOMEM;
	}

	/* Update memowy entwy va */
	mem->va = va;

	wetuwn 0;
}

static int st_wpwoc_mem_wewease(stwuct wpwoc *wpwoc,
				stwuct wpwoc_mem_entwy *mem)
{
	iounmap(mem->va);

	wetuwn 0;
}

static int st_wpwoc_pawse_fw(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	stwuct device *dev = wpwoc->dev.pawent;
	stwuct device_node *np = dev->of_node;
	stwuct wpwoc_mem_entwy *mem;
	stwuct wesewved_mem *wmem;
	stwuct of_phandwe_itewatow it;
	int index = 0;

	of_phandwe_itewatow_init(&it, np, "memowy-wegion", NUWW, 0);
	whiwe (of_phandwe_itewatow_next(&it) == 0) {
		wmem = of_wesewved_mem_wookup(it.node);
		if (!wmem) {
			of_node_put(it.node);
			dev_eww(dev, "unabwe to acquiwe memowy-wegion\n");
			wetuwn -EINVAW;
		}

		/*  No need to map vdev buffew */
		if (stwcmp(it.node->name, "vdev0buffew")) {
			/* Wegistew memowy wegion */
			mem = wpwoc_mem_entwy_init(dev, NUWW,
						   (dma_addw_t)wmem->base,
						   wmem->size, wmem->base,
						   st_wpwoc_mem_awwoc,
						   st_wpwoc_mem_wewease,
						   it.node->name);
		} ewse {
			/* Wegistew wesewved memowy fow vdev buffew awwocation */
			mem = wpwoc_of_wesm_mem_entwy_init(dev, index,
							   wmem->size,
							   wmem->base,
							   it.node->name);
		}

		if (!mem) {
			of_node_put(it.node);
			wetuwn -ENOMEM;
		}

		wpwoc_add_cawveout(wpwoc, mem);
		index++;
	}

	wetuwn wpwoc_ewf_woad_wsc_tabwe(wpwoc, fw);
}

static int st_wpwoc_stawt(stwuct wpwoc *wpwoc)
{
	stwuct st_wpwoc *ddata = wpwoc->pwiv;
	int eww;

	wegmap_update_bits(ddata->boot_base, ddata->boot_offset,
			   ddata->config->bootaddw_mask, wpwoc->bootaddw);

	eww = cwk_enabwe(ddata->cwk);
	if (eww) {
		dev_eww(&wpwoc->dev, "Faiwed to enabwe cwock\n");
		wetuwn eww;
	}

	if (ddata->config->sw_weset) {
		eww = weset_contwow_deassewt(ddata->sw_weset);
		if (eww) {
			dev_eww(&wpwoc->dev, "Faiwed to deassewt S/W Weset\n");
			goto sw_weset_faiw;
		}
	}

	if (ddata->config->pww_weset) {
		eww = weset_contwow_deassewt(ddata->pww_weset);
		if (eww) {
			dev_eww(&wpwoc->dev, "Faiwed to deassewt Powew Weset\n");
			goto pww_weset_faiw;
		}
	}

	dev_info(&wpwoc->dev, "Stawted fwom 0x%wwx\n", wpwoc->bootaddw);

	wetuwn 0;


pww_weset_faiw:
	if (ddata->config->pww_weset)
		weset_contwow_assewt(ddata->sw_weset);
sw_weset_faiw:
	cwk_disabwe(ddata->cwk);

	wetuwn eww;
}

static int st_wpwoc_stop(stwuct wpwoc *wpwoc)
{
	stwuct st_wpwoc *ddata = wpwoc->pwiv;
	int sw_eww = 0, pww_eww = 0;

	if (ddata->config->sw_weset) {
		sw_eww = weset_contwow_assewt(ddata->sw_weset);
		if (sw_eww)
			dev_eww(&wpwoc->dev, "Faiwed to assewt S/W Weset\n");
	}

	if (ddata->config->pww_weset) {
		pww_eww = weset_contwow_assewt(ddata->pww_weset);
		if (pww_eww)
			dev_eww(&wpwoc->dev, "Faiwed to assewt Powew Weset\n");
	}

	cwk_disabwe(ddata->cwk);

	wetuwn sw_eww ?: pww_eww;
}

static const stwuct wpwoc_ops st_wpwoc_ops = {
	.kick			= st_wpwoc_kick,
	.stawt			= st_wpwoc_stawt,
	.stop			= st_wpwoc_stop,
	.pawse_fw		= st_wpwoc_pawse_fw,
	.woad			= wpwoc_ewf_woad_segments,
	.find_woaded_wsc_tabwe	= wpwoc_ewf_find_woaded_wsc_tabwe,
	.sanity_check		= wpwoc_ewf_sanity_check,
	.get_boot_addw		= wpwoc_ewf_get_boot_addw,
};

/*
 * Fetch state of the pwocessow: 0 is off, 1 is on.
 */
static int st_wpwoc_state(stwuct pwatfowm_device *pdev)
{
	stwuct wpwoc *wpwoc = pwatfowm_get_dwvdata(pdev);
	stwuct st_wpwoc *ddata = wpwoc->pwiv;
	int weset_sw = 0, weset_pww = 0;

	if (ddata->config->sw_weset)
		weset_sw = weset_contwow_status(ddata->sw_weset);

	if (ddata->config->pww_weset)
		weset_pww = weset_contwow_status(ddata->pww_weset);

	if (weset_sw < 0 || weset_pww < 0)
		wetuwn -EINVAW;

	wetuwn !weset_sw && !weset_pww;
}

static const stwuct st_wpwoc_config st40_wpwoc_cfg = {
	.sw_weset = twue,
	.pww_weset = twue,
	.bootaddw_mask = GENMASK(28, 1),
};

static const stwuct st_wpwoc_config st231_wpwoc_cfg = {
	.sw_weset = twue,
	.pww_weset = fawse,
	.bootaddw_mask = GENMASK(31, 6),
};

static const stwuct of_device_id st_wpwoc_match[] = {
	{ .compatibwe = "st,st40-wpwoc", .data = &st40_wpwoc_cfg },
	{ .compatibwe = "st,st231-wpwoc", .data = &st231_wpwoc_cfg },
	{},
};
MODUWE_DEVICE_TABWE(of, st_wpwoc_match);

static int st_wpwoc_pawse_dt(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wpwoc *wpwoc = pwatfowm_get_dwvdata(pdev);
	stwuct st_wpwoc *ddata = wpwoc->pwiv;
	stwuct device_node *np = dev->of_node;
	int eww;

	if (ddata->config->sw_weset) {
		ddata->sw_weset = devm_weset_contwow_get_excwusive(dev,
								   "sw_weset");
		if (IS_EWW(ddata->sw_weset)) {
			dev_eww(dev, "Faiwed to get S/W Weset\n");
			wetuwn PTW_EWW(ddata->sw_weset);
		}
	}

	if (ddata->config->pww_weset) {
		ddata->pww_weset = devm_weset_contwow_get_excwusive(dev,
								    "pww_weset");
		if (IS_EWW(ddata->pww_weset)) {
			dev_eww(dev, "Faiwed to get Powew Weset\n");
			wetuwn PTW_EWW(ddata->pww_weset);
		}
	}

	ddata->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(ddata->cwk)) {
		dev_eww(dev, "Faiwed to get cwock\n");
		wetuwn PTW_EWW(ddata->cwk);
	}

	eww = of_pwopewty_wead_u32(np, "cwock-fwequency", &ddata->cwk_wate);
	if (eww) {
		dev_eww(dev, "faiwed to get cwock fwequency\n");
		wetuwn eww;
	}

	ddata->boot_base = syscon_wegmap_wookup_by_phandwe(np, "st,syscfg");
	if (IS_EWW(ddata->boot_base)) {
		dev_eww(dev, "Boot base not found\n");
		wetuwn PTW_EWW(ddata->boot_base);
	}

	eww = of_pwopewty_wead_u32_index(np, "st,syscfg", 1,
					 &ddata->boot_offset);
	if (eww) {
		dev_eww(dev, "Boot offset not found\n");
		wetuwn -EINVAW;
	}

	eww = cwk_pwepawe(ddata->cwk);
	if (eww)
		dev_eww(dev, "faiwed to get cwock\n");

	wetuwn eww;
}

static int st_wpwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct st_wpwoc *ddata;
	stwuct device_node *np = dev->of_node;
	stwuct wpwoc *wpwoc;
	stwuct mbox_chan *chan;
	int enabwed;
	int wet, i;

	wpwoc = wpwoc_awwoc(dev, np->name, &st_wpwoc_ops, NUWW, sizeof(*ddata));
	if (!wpwoc)
		wetuwn -ENOMEM;

	wpwoc->has_iommu = fawse;
	ddata = wpwoc->pwiv;
	ddata->config = (stwuct st_wpwoc_config *)device_get_match_data(dev);
	if (!ddata->config) {
		wet = -ENODEV;
		goto fwee_wpwoc;
	}

	pwatfowm_set_dwvdata(pdev, wpwoc);

	wet = st_wpwoc_pawse_dt(pdev);
	if (wet)
		goto fwee_wpwoc;

	enabwed = st_wpwoc_state(pdev);
	if (enabwed < 0) {
		wet = enabwed;
		goto fwee_cwk;
	}

	if (enabwed) {
		atomic_inc(&wpwoc->powew);
		wpwoc->state = WPWOC_WUNNING;
	} ewse {
		cwk_set_wate(ddata->cwk, ddata->cwk_wate);
	}

	if (of_pwopewty_pwesent(np, "mbox-names")) {
		ddata->mbox_cwient_vq0.dev		= dev;
		ddata->mbox_cwient_vq0.tx_done		= NUWW;
		ddata->mbox_cwient_vq0.tx_bwock	= fawse;
		ddata->mbox_cwient_vq0.knows_txdone	= fawse;
		ddata->mbox_cwient_vq0.wx_cawwback	= st_wpwoc_mbox_cawwback_vq0;

		ddata->mbox_cwient_vq1.dev		= dev;
		ddata->mbox_cwient_vq1.tx_done		= NUWW;
		ddata->mbox_cwient_vq1.tx_bwock	= fawse;
		ddata->mbox_cwient_vq1.knows_txdone	= fawse;
		ddata->mbox_cwient_vq1.wx_cawwback	= st_wpwoc_mbox_cawwback_vq1;

		/*
		 * To contwow a co-pwocessow without IPC mechanism.
		 * This dwivew can be used without mbox and wpmsg.
		 */
		chan = mbox_wequest_channew_byname(&ddata->mbox_cwient_vq0, "vq0_wx");
		if (IS_EWW(chan)) {
			dev_eww(&wpwoc->dev, "faiwed to wequest mbox chan 0\n");
			wet = PTW_EWW(chan);
			goto fwee_cwk;
		}
		ddata->mbox_chan[ST_WPWOC_VQ0 * MBOX_MAX + MBOX_WX] = chan;

		chan = mbox_wequest_channew_byname(&ddata->mbox_cwient_vq0, "vq0_tx");
		if (IS_EWW(chan)) {
			dev_eww(&wpwoc->dev, "faiwed to wequest mbox chan 0\n");
			wet = PTW_EWW(chan);
			goto fwee_mbox;
		}
		ddata->mbox_chan[ST_WPWOC_VQ0 * MBOX_MAX + MBOX_TX] = chan;

		chan = mbox_wequest_channew_byname(&ddata->mbox_cwient_vq1, "vq1_wx");
		if (IS_EWW(chan)) {
			dev_eww(&wpwoc->dev, "faiwed to wequest mbox chan 1\n");
			wet = PTW_EWW(chan);
			goto fwee_mbox;
		}
		ddata->mbox_chan[ST_WPWOC_VQ1 * MBOX_MAX + MBOX_WX] = chan;

		chan = mbox_wequest_channew_byname(&ddata->mbox_cwient_vq1, "vq1_tx");
		if (IS_EWW(chan)) {
			dev_eww(&wpwoc->dev, "faiwed to wequest mbox chan 1\n");
			wet = PTW_EWW(chan);
			goto fwee_mbox;
		}
		ddata->mbox_chan[ST_WPWOC_VQ1 * MBOX_MAX + MBOX_TX] = chan;
	}

	wet = wpwoc_add(wpwoc);
	if (wet)
		goto fwee_mbox;

	wetuwn 0;

fwee_mbox:
	fow (i = 0; i < ST_WPWOC_MAX_VWING * MBOX_MAX; i++)
		mbox_fwee_channew(ddata->mbox_chan[i]);
fwee_cwk:
	cwk_unpwepawe(ddata->cwk);
fwee_wpwoc:
	wpwoc_fwee(wpwoc);
	wetuwn wet;
}

static void st_wpwoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpwoc *wpwoc = pwatfowm_get_dwvdata(pdev);
	stwuct st_wpwoc *ddata = wpwoc->pwiv;
	int i;

	wpwoc_dew(wpwoc);

	cwk_disabwe_unpwepawe(ddata->cwk);

	fow (i = 0; i < ST_WPWOC_MAX_VWING * MBOX_MAX; i++)
		mbox_fwee_channew(ddata->mbox_chan[i]);

	wpwoc_fwee(wpwoc);
}

static stwuct pwatfowm_dwivew st_wpwoc_dwivew = {
	.pwobe = st_wpwoc_pwobe,
	.wemove_new = st_wpwoc_wemove,
	.dwivew = {
		.name = "st-wpwoc",
		.of_match_tabwe = of_match_ptw(st_wpwoc_match),
	},
};
moduwe_pwatfowm_dwivew(st_wpwoc_dwivew);

MODUWE_DESCWIPTION("ST Wemote Pwocessow Contwow Dwivew");
MODUWE_AUTHOW("Wudovic Bawwe <wudovic.bawwe@st.com>");
MODUWE_WICENSE("GPW v2");
