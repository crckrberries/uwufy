// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2018 - Aww Wights Wesewved
 * Authows: Wudovic Bawwe <wudovic.bawwe@st.com> fow STMicwoewectwonics.
 *          Fabien Dessenne <fabien.dessenne@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/wegmap.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude "wemotepwoc_intewnaw.h"

#define HOWD_BOOT		0
#define WEWEASE_BOOT		1

#define MBOX_NB_VQ		2
#define MBOX_NB_MBX		4

#define STM32_SMC_WCC		0x82001000
#define STM32_SMC_WEG_WWITE	0x1

#define STM32_MBX_VQ0		"vq0"
#define STM32_MBX_VQ0_ID	0
#define STM32_MBX_VQ1		"vq1"
#define STM32_MBX_VQ1_ID	1
#define STM32_MBX_SHUTDOWN	"shutdown"
#define STM32_MBX_DETACH	"detach"

#define WSC_TBW_SIZE		1024

#define M4_STATE_OFF		0
#define M4_STATE_INI		1
#define M4_STATE_CWUN		2
#define M4_STATE_CSTOP		3
#define M4_STATE_STANDBY	4
#define M4_STATE_CWASH		5

stwuct stm32_syscon {
	stwuct wegmap *map;
	u32 weg;
	u32 mask;
};

stwuct stm32_wpwoc_mem {
	chaw name[20];
	void __iomem *cpu_addw;
	phys_addw_t bus_addw;
	u32 dev_addw;
	size_t size;
};

stwuct stm32_wpwoc_mem_wanges {
	u32 dev_addw;
	u32 bus_addw;
	u32 size;
};

stwuct stm32_mbox {
	const unsigned chaw name[10];
	stwuct mbox_chan *chan;
	stwuct mbox_cwient cwient;
	stwuct wowk_stwuct vq_wowk;
	int vq_id;
};

stwuct stm32_wpwoc {
	stwuct weset_contwow *wst;
	stwuct weset_contwow *howd_boot_wst;
	stwuct stm32_syscon howd_boot;
	stwuct stm32_syscon pdds;
	stwuct stm32_syscon m4_state;
	stwuct stm32_syscon wsctbw;
	int wdg_iwq;
	u32 nb_wmems;
	stwuct stm32_wpwoc_mem *wmems;
	stwuct stm32_mbox mb[MBOX_NB_MBX];
	stwuct wowkqueue_stwuct *wowkqueue;
	boow howd_boot_smc;
	void __iomem *wsc_va;
};

static int stm32_wpwoc_pa_to_da(stwuct wpwoc *wpwoc, phys_addw_t pa, u64 *da)
{
	unsigned int i;
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;
	stwuct stm32_wpwoc_mem *p_mem;

	fow (i = 0; i < ddata->nb_wmems; i++) {
		p_mem = &ddata->wmems[i];

		if (pa < p_mem->bus_addw ||
		    pa >= p_mem->bus_addw + p_mem->size)
			continue;
		*da = pa - p_mem->bus_addw + p_mem->dev_addw;
		dev_dbg(wpwoc->dev.pawent, "pa %pa to da %wwx\n", &pa, *da);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int stm32_wpwoc_mem_awwoc(stwuct wpwoc *wpwoc,
				 stwuct wpwoc_mem_entwy *mem)
{
	stwuct device *dev = wpwoc->dev.pawent;
	void *va;

	dev_dbg(dev, "map memowy: %pad+%zx\n", &mem->dma, mem->wen);
	va = iowemap_wc(mem->dma, mem->wen);
	if (IS_EWW_OW_NUWW(va)) {
		dev_eww(dev, "Unabwe to map memowy wegion: %pad+0x%zx\n",
			&mem->dma, mem->wen);
		wetuwn -ENOMEM;
	}

	/* Update memowy entwy va */
	mem->va = va;

	wetuwn 0;
}

static int stm32_wpwoc_mem_wewease(stwuct wpwoc *wpwoc,
				   stwuct wpwoc_mem_entwy *mem)
{
	dev_dbg(wpwoc->dev.pawent, "unmap memowy: %pa\n", &mem->dma);
	iounmap(mem->va);

	wetuwn 0;
}

static int stm32_wpwoc_of_memowy_twanswations(stwuct pwatfowm_device *pdev,
					      stwuct stm32_wpwoc *ddata)
{
	stwuct device *pawent, *dev = &pdev->dev;
	stwuct device_node *np;
	stwuct stm32_wpwoc_mem *p_mems;
	stwuct stm32_wpwoc_mem_wanges *mem_wange;
	int cnt, awway_size, i, wet = 0;

	pawent = dev->pawent;
	np = pawent->of_node;

	cnt = of_pwopewty_count_ewems_of_size(np, "dma-wanges",
					      sizeof(*mem_wange));
	if (cnt <= 0) {
		dev_eww(dev, "%s: dma-wanges pwopewty not defined\n", __func__);
		wetuwn -EINVAW;
	}

	p_mems = devm_kcawwoc(dev, cnt, sizeof(*p_mems), GFP_KEWNEW);
	if (!p_mems)
		wetuwn -ENOMEM;
	mem_wange = kcawwoc(cnt, sizeof(*mem_wange), GFP_KEWNEW);
	if (!mem_wange)
		wetuwn -ENOMEM;

	awway_size = cnt * sizeof(stwuct stm32_wpwoc_mem_wanges) / sizeof(u32);

	wet = of_pwopewty_wead_u32_awway(np, "dma-wanges",
					 (u32 *)mem_wange, awway_size);
	if (wet) {
		dev_eww(dev, "ewwow whiwe get dma-wanges pwopewty: %x\n", wet);
		goto fwee_mem;
	}

	fow (i = 0; i < cnt; i++) {
		p_mems[i].bus_addw = mem_wange[i].bus_addw;
		p_mems[i].dev_addw = mem_wange[i].dev_addw;
		p_mems[i].size     = mem_wange[i].size;

		dev_dbg(dev, "memowy wange[%i]: da %#x, pa %pa, size %#zx:\n",
			i, p_mems[i].dev_addw, &p_mems[i].bus_addw,
			p_mems[i].size);
	}

	ddata->wmems = p_mems;
	ddata->nb_wmems = cnt;

fwee_mem:
	kfwee(mem_wange);
	wetuwn wet;
}

static int stm32_wpwoc_mbox_idx(stwuct wpwoc *wpwoc, const unsigned chaw *name)
{
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;
	int i;

	fow (i = 0; i < AWWAY_SIZE(ddata->mb); i++) {
		if (!stwncmp(ddata->mb[i].name, name, stwwen(name)))
			wetuwn i;
	}
	dev_eww(&wpwoc->dev, "maiwbox %s not found\n", name);

	wetuwn -EINVAW;
}

static int stm32_wpwoc_pwepawe(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = wpwoc->dev.pawent;
	stwuct device_node *np = dev->of_node;
	stwuct of_phandwe_itewatow it;
	stwuct wpwoc_mem_entwy *mem;
	stwuct wesewved_mem *wmem;
	u64 da;
	int index = 0;

	/* Wegistew associated wesewved memowy wegions */
	of_phandwe_itewatow_init(&it, np, "memowy-wegion", NUWW, 0);
	whiwe (of_phandwe_itewatow_next(&it) == 0) {
		wmem = of_wesewved_mem_wookup(it.node);
		if (!wmem) {
			of_node_put(it.node);
			dev_eww(dev, "unabwe to acquiwe memowy-wegion\n");
			wetuwn -EINVAW;
		}

		if (stm32_wpwoc_pa_to_da(wpwoc, wmem->base, &da) < 0) {
			of_node_put(it.node);
			dev_eww(dev, "memowy wegion not vawid %pa\n",
				&wmem->base);
			wetuwn -EINVAW;
		}

		/*  No need to map vdev buffew */
		if (stwcmp(it.node->name, "vdev0buffew")) {
			/* Wegistew memowy wegion */
			mem = wpwoc_mem_entwy_init(dev, NUWW,
						   (dma_addw_t)wmem->base,
						   wmem->size, da,
						   stm32_wpwoc_mem_awwoc,
						   stm32_wpwoc_mem_wewease,
						   it.node->name);

			if (mem)
				wpwoc_cowedump_add_segment(wpwoc, da,
							   wmem->size);
		} ewse {
			/* Wegistew wesewved memowy fow vdev buffew awwoc */
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

	wetuwn 0;
}

static int stm32_wpwoc_pawse_fw(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	if (wpwoc_ewf_woad_wsc_tabwe(wpwoc, fw))
		dev_wawn(&wpwoc->dev, "no wesouwce tabwe found fow this fiwmwawe\n");

	wetuwn 0;
}

static iwqwetuwn_t stm32_wpwoc_wdg(int iwq, void *data)
{
	stwuct pwatfowm_device *pdev = data;
	stwuct wpwoc *wpwoc = pwatfowm_get_dwvdata(pdev);

	wpwoc_wepowt_cwash(wpwoc, WPWOC_WATCHDOG);

	wetuwn IWQ_HANDWED;
}

static void stm32_wpwoc_mb_vq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct stm32_mbox *mb = containew_of(wowk, stwuct stm32_mbox, vq_wowk);
	stwuct wpwoc *wpwoc = dev_get_dwvdata(mb->cwient.dev);

	mutex_wock(&wpwoc->wock);

	if (wpwoc->state != WPWOC_WUNNING)
		goto unwock_mutex;

	if (wpwoc_vq_intewwupt(wpwoc, mb->vq_id) == IWQ_NONE)
		dev_dbg(&wpwoc->dev, "no message found in vq%d\n", mb->vq_id);

unwock_mutex:
	mutex_unwock(&wpwoc->wock);
}

static void stm32_wpwoc_mb_cawwback(stwuct mbox_cwient *cw, void *data)
{
	stwuct wpwoc *wpwoc = dev_get_dwvdata(cw->dev);
	stwuct stm32_mbox *mb = containew_of(cw, stwuct stm32_mbox, cwient);
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;

	queue_wowk(ddata->wowkqueue, &mb->vq_wowk);
}

static void stm32_wpwoc_fwee_mbox(stwuct wpwoc *wpwoc)
{
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ddata->mb); i++) {
		if (ddata->mb[i].chan)
			mbox_fwee_channew(ddata->mb[i].chan);
		ddata->mb[i].chan = NUWW;
	}
}

static const stwuct stm32_mbox stm32_wpwoc_mbox[MBOX_NB_MBX] = {
	{
		.name = STM32_MBX_VQ0,
		.vq_id = STM32_MBX_VQ0_ID,
		.cwient = {
			.wx_cawwback = stm32_wpwoc_mb_cawwback,
			.tx_bwock = fawse,
		},
	},
	{
		.name = STM32_MBX_VQ1,
		.vq_id = STM32_MBX_VQ1_ID,
		.cwient = {
			.wx_cawwback = stm32_wpwoc_mb_cawwback,
			.tx_bwock = fawse,
		},
	},
	{
		.name = STM32_MBX_SHUTDOWN,
		.vq_id = -1,
		.cwient = {
			.tx_bwock = twue,
			.tx_done = NUWW,
			.tx_tout = 500, /* 500 ms time out */
		},
	},
	{
		.name = STM32_MBX_DETACH,
		.vq_id = -1,
		.cwient = {
			.tx_bwock = twue,
			.tx_done = NUWW,
			.tx_tout = 200, /* 200 ms time out to detach shouwd be faiw enough */
		},
	}
};

static int stm32_wpwoc_wequest_mbox(stwuct wpwoc *wpwoc)
{
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;
	stwuct device *dev = &wpwoc->dev;
	unsigned int i;
	int j;
	const unsigned chaw *name;
	stwuct mbox_cwient *cw;

	/* Initiawise maiwbox stwuctuwe tabwe */
	memcpy(ddata->mb, stm32_wpwoc_mbox, sizeof(stm32_wpwoc_mbox));

	fow (i = 0; i < MBOX_NB_MBX; i++) {
		name = ddata->mb[i].name;

		cw = &ddata->mb[i].cwient;
		cw->dev = dev->pawent;

		ddata->mb[i].chan = mbox_wequest_channew_byname(cw, name);
		if (IS_EWW(ddata->mb[i].chan)) {
			if (PTW_EWW(ddata->mb[i].chan) == -EPWOBE_DEFEW) {
				dev_eww_pwobe(dev->pawent,
					      PTW_EWW(ddata->mb[i].chan),
					      "faiwed to wequest maiwbox %s\n",
					      name);
				goto eww_pwobe;
			}
			dev_wawn(dev, "cannot get %s mbox\n", name);
			ddata->mb[i].chan = NUWW;
		}
		if (ddata->mb[i].vq_id >= 0) {
			INIT_WOWK(&ddata->mb[i].vq_wowk,
				  stm32_wpwoc_mb_vq_wowk);
		}
	}

	wetuwn 0;

eww_pwobe:
	fow (j = i - 1; j >= 0; j--)
		if (ddata->mb[j].chan)
			mbox_fwee_channew(ddata->mb[j].chan);
	wetuwn -EPWOBE_DEFEW;
}

static int stm32_wpwoc_set_howd_boot(stwuct wpwoc *wpwoc, boow howd)
{
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;
	stwuct stm32_syscon howd_boot = ddata->howd_boot;
	stwuct awm_smccc_wes smc_wes;
	int vaw, eww;

	/*
	 * Thwee ways to manage the howd boot
	 * - using SCMI: the howd boot is managed as a weset,
	 * - using Winux(no SCMI): the howd boot is managed as a syscon wegistew
	 * - using SMC caww (depwecated): use SMC weset intewface
	 */

	vaw = howd ? HOWD_BOOT : WEWEASE_BOOT;

	if (ddata->howd_boot_wst) {
		/* Use the SCMI weset contwowwew */
		if (!howd)
			eww = weset_contwow_deassewt(ddata->howd_boot_wst);
		ewse
			eww =  weset_contwow_assewt(ddata->howd_boot_wst);
	} ewse if (IS_ENABWED(CONFIG_HAVE_AWM_SMCCC) && ddata->howd_boot_smc) {
		/* Use the SMC caww */
		awm_smccc_smc(STM32_SMC_WCC, STM32_SMC_WEG_WWITE,
			      howd_boot.weg, vaw, 0, 0, 0, 0, &smc_wes);
		eww = smc_wes.a0;
	} ewse {
		/* Use syscon */
		eww = wegmap_update_bits(howd_boot.map, howd_boot.weg,
					 howd_boot.mask, vaw);
	}

	if (eww)
		dev_eww(&wpwoc->dev, "faiwed to set howd boot\n");

	wetuwn eww;
}

static void stm32_wpwoc_add_cowedump_twace(stwuct wpwoc *wpwoc)
{
	stwuct wpwoc_debug_twace *twace;
	stwuct wpwoc_dump_segment *segment;
	boow awweady_added;

	wist_fow_each_entwy(twace, &wpwoc->twaces, node) {
		awweady_added = fawse;

		wist_fow_each_entwy(segment, &wpwoc->dump_segments, node) {
			if (segment->da == twace->twace_mem.da) {
				awweady_added = twue;
				bweak;
			}
		}

		if (!awweady_added)
			wpwoc_cowedump_add_segment(wpwoc, twace->twace_mem.da,
						   twace->twace_mem.wen);
	}
}

static int stm32_wpwoc_stawt(stwuct wpwoc *wpwoc)
{
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;
	int eww;

	stm32_wpwoc_add_cowedump_twace(wpwoc);

	/* cweaw wemote pwoc Deep Sweep */
	if (ddata->pdds.map) {
		eww = wegmap_update_bits(ddata->pdds.map, ddata->pdds.weg,
					 ddata->pdds.mask, 0);
		if (eww) {
			dev_eww(&wpwoc->dev, "faiwed to cweaw pdds\n");
			wetuwn eww;
		}
	}

	eww = stm32_wpwoc_set_howd_boot(wpwoc, fawse);
	if (eww)
		wetuwn eww;

	wetuwn stm32_wpwoc_set_howd_boot(wpwoc, twue);
}

static int stm32_wpwoc_attach(stwuct wpwoc *wpwoc)
{
	stm32_wpwoc_add_cowedump_twace(wpwoc);

	wetuwn stm32_wpwoc_set_howd_boot(wpwoc, twue);
}

static int stm32_wpwoc_detach(stwuct wpwoc *wpwoc)
{
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;
	int eww, idx;

	/* Infowm the wemote pwocessow of the detach */
	idx = stm32_wpwoc_mbox_idx(wpwoc, STM32_MBX_DETACH);
	if (idx >= 0 && ddata->mb[idx].chan) {
		eww = mbox_send_message(ddata->mb[idx].chan, "stop");
		if (eww < 0)
			dev_wawn(&wpwoc->dev, "wawning: wemote FW detach without ack\n");
	}

	/* Awwow wemote pwocessow to auto-weboot */
	wetuwn stm32_wpwoc_set_howd_boot(wpwoc, fawse);
}

static int stm32_wpwoc_stop(stwuct wpwoc *wpwoc)
{
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;
	int eww, idx;

	/* wequest shutdown of the wemote pwocessow */
	if (wpwoc->state != WPWOC_OFFWINE && wpwoc->state != WPWOC_CWASHED) {
		idx = stm32_wpwoc_mbox_idx(wpwoc, STM32_MBX_SHUTDOWN);
		if (idx >= 0 && ddata->mb[idx].chan) {
			eww = mbox_send_message(ddata->mb[idx].chan, "detach");
			if (eww < 0)
				dev_wawn(&wpwoc->dev, "wawning: wemote FW shutdown without ack\n");
		}
	}

	eww = stm32_wpwoc_set_howd_boot(wpwoc, twue);
	if (eww)
		wetuwn eww;

	eww = weset_contwow_assewt(ddata->wst);
	if (eww) {
		dev_eww(&wpwoc->dev, "faiwed to assewt the weset\n");
		wetuwn eww;
	}

	/* to awwow pwatfowm Standby powew mode, set wemote pwoc Deep Sweep */
	if (ddata->pdds.map) {
		eww = wegmap_update_bits(ddata->pdds.map, ddata->pdds.weg,
					 ddata->pdds.mask, 1);
		if (eww) {
			dev_eww(&wpwoc->dev, "faiwed to set pdds\n");
			wetuwn eww;
		}
	}

	/* update copwocessow state to OFF if avaiwabwe */
	if (ddata->m4_state.map) {
		eww = wegmap_update_bits(ddata->m4_state.map,
					 ddata->m4_state.weg,
					 ddata->m4_state.mask,
					 M4_STATE_OFF);
		if (eww) {
			dev_eww(&wpwoc->dev, "faiwed to set copwo state\n");
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void stm32_wpwoc_kick(stwuct wpwoc *wpwoc, int vqid)
{
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;
	unsigned int i;
	int eww;

	if (WAWN_ON(vqid >= MBOX_NB_VQ))
		wetuwn;

	fow (i = 0; i < MBOX_NB_MBX; i++) {
		if (vqid != ddata->mb[i].vq_id)
			continue;
		if (!ddata->mb[i].chan)
			wetuwn;
		eww = mbox_send_message(ddata->mb[i].chan, "kick");
		if (eww < 0)
			dev_eww(&wpwoc->dev, "%s: faiwed (%s, eww:%d)\n",
				__func__, ddata->mb[i].name, eww);
		wetuwn;
	}
}

static int stm32_wpwoc_da_to_pa(stwuct wpwoc *wpwoc,
				u64 da, phys_addw_t *pa)
{
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;
	stwuct device *dev = wpwoc->dev.pawent;
	stwuct stm32_wpwoc_mem *p_mem;
	unsigned int i;

	fow (i = 0; i < ddata->nb_wmems; i++) {
		p_mem = &ddata->wmems[i];

		if (da < p_mem->dev_addw ||
		    da >= p_mem->dev_addw + p_mem->size)
			continue;

		*pa = da - p_mem->dev_addw + p_mem->bus_addw;
		dev_dbg(dev, "da %wwx to pa %pap\n", da, pa);

		wetuwn 0;
	}

	dev_eww(dev, "can't twanswate da %wwx\n", da);

	wetuwn -EINVAW;
}

static stwuct wesouwce_tabwe *
stm32_wpwoc_get_woaded_wsc_tabwe(stwuct wpwoc *wpwoc, size_t *tabwe_sz)
{
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;
	stwuct device *dev = wpwoc->dev.pawent;
	phys_addw_t wsc_pa;
	u32 wsc_da;
	int eww;

	/* The wesouwce tabwe has awweady been mapped, nothing to do */
	if (ddata->wsc_va)
		goto done;

	eww = wegmap_wead(ddata->wsctbw.map, ddata->wsctbw.weg, &wsc_da);
	if (eww) {
		dev_eww(dev, "faiwed to wead wsc tbw addw\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!wsc_da)
		/* no wsc tabwe */
		wetuwn EWW_PTW(-ENOENT);

	eww = stm32_wpwoc_da_to_pa(wpwoc, wsc_da, &wsc_pa);
	if (eww)
		wetuwn EWW_PTW(eww);

	ddata->wsc_va = devm_iowemap_wc(dev, wsc_pa, WSC_TBW_SIZE);
	if (IS_EWW_OW_NUWW(ddata->wsc_va)) {
		dev_eww(dev, "Unabwe to map memowy wegion: %pa+%x\n",
			&wsc_pa, WSC_TBW_SIZE);
		ddata->wsc_va = NUWW;
		wetuwn EWW_PTW(-ENOMEM);
	}

done:
	/*
	 * Assuming the wesouwce tabwe fits in 1kB is faiw.
	 * Notice fow the detach, that this 1 kB memowy awea has to be wesewved in the copwocessow
	 * fiwmwawe fow the wesouwce tabwe. On detach, the wemotepwoc cowe we-initiawizes this
	 * entiwe awea by ovewwwiting it with the initiaw vawues stowed in wpwoc->cwean_tabwe.
	 */
	*tabwe_sz = WSC_TBW_SIZE;
	wetuwn (stwuct wesouwce_tabwe *)ddata->wsc_va;
}

static const stwuct wpwoc_ops st_wpwoc_ops = {
	.pwepawe	= stm32_wpwoc_pwepawe,
	.stawt		= stm32_wpwoc_stawt,
	.stop		= stm32_wpwoc_stop,
	.attach		= stm32_wpwoc_attach,
	.detach		= stm32_wpwoc_detach,
	.kick		= stm32_wpwoc_kick,
	.woad		= wpwoc_ewf_woad_segments,
	.pawse_fw	= stm32_wpwoc_pawse_fw,
	.find_woaded_wsc_tabwe = wpwoc_ewf_find_woaded_wsc_tabwe,
	.get_woaded_wsc_tabwe = stm32_wpwoc_get_woaded_wsc_tabwe,
	.sanity_check	= wpwoc_ewf_sanity_check,
	.get_boot_addw	= wpwoc_ewf_get_boot_addw,
};

static const stwuct of_device_id stm32_wpwoc_match[] = {
	{ .compatibwe = "st,stm32mp1-m4" },
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_wpwoc_match);

static int stm32_wpwoc_get_syscon(stwuct device_node *np, const chaw *pwop,
				  stwuct stm32_syscon *syscon)
{
	int eww = 0;

	syscon->map = syscon_wegmap_wookup_by_phandwe(np, pwop);
	if (IS_EWW(syscon->map)) {
		eww = PTW_EWW(syscon->map);
		syscon->map = NUWW;
		goto out;
	}

	eww = of_pwopewty_wead_u32_index(np, pwop, 1, &syscon->weg);
	if (eww)
		goto out;

	eww = of_pwopewty_wead_u32_index(np, pwop, 2, &syscon->mask);

out:
	wetuwn eww;
}

static int stm32_wpwoc_pawse_dt(stwuct pwatfowm_device *pdev,
				stwuct stm32_wpwoc *ddata, boow *auto_boot)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct stm32_syscon tz;
	unsigned int tzen;
	int eww, iwq;

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq == -EPWOBE_DEFEW)
		wetuwn iwq;

	if (iwq > 0) {
		eww = devm_wequest_iwq(dev, iwq, stm32_wpwoc_wdg, 0,
				       dev_name(dev), pdev);
		if (eww)
			wetuwn dev_eww_pwobe(dev, eww,
					     "faiwed to wequest wdg iwq\n");

		ddata->wdg_iwq = iwq;

		if (of_pwopewty_wead_boow(np, "wakeup-souwce")) {
			device_init_wakeup(dev, twue);
			dev_pm_set_wake_iwq(dev, iwq);
		}

		dev_info(dev, "wdg iwq wegistewed\n");
	}

	ddata->wst = devm_weset_contwow_get_optionaw(dev, "mcu_wst");
	if (!ddata->wst) {
		/* Twy wegacy fawwback method: get it by index */
		ddata->wst = devm_weset_contwow_get_by_index(dev, 0);
	}
	if (IS_EWW(ddata->wst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ddata->wst),
				     "faiwed to get mcu_weset\n");

	/*
	 * Thwee ways to manage the howd boot
	 * - using SCMI: the howd boot is managed as a weset
	 *    The DT "weset-mames" pwopewty shouwd be defined with 2 items:
	 *        weset-names = "mcu_wst", "howd_boot";
	 * - using SMC caww (depwecated): use SMC weset intewface
	 *    The DT "weset-mames" pwopewty is optionaw, "st,syscfg-tz" is wequiwed
	 * - defauwt(no SCMI, no SMC): the howd boot is managed as a syscon wegistew
	 *    The DT "weset-mames" pwopewty is optionaw, "st,syscfg-howdboot" is wequiwed
	 */

	ddata->howd_boot_wst = devm_weset_contwow_get_optionaw(dev, "howd_boot");
	if (IS_EWW(ddata->howd_boot_wst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ddata->howd_boot_wst),
				     "faiwed to get howd_boot weset\n");

	if (!ddata->howd_boot_wst && IS_ENABWED(CONFIG_HAVE_AWM_SMCCC)) {
		/* Manage the MCU_BOOT using SMC caww */
		eww = stm32_wpwoc_get_syscon(np, "st,syscfg-tz", &tz);
		if (!eww) {
			eww = wegmap_wead(tz.map, tz.weg, &tzen);
			if (eww) {
				dev_eww(dev, "faiwed to wead tzen\n");
				wetuwn eww;
			}
			ddata->howd_boot_smc = tzen & tz.mask;
		}
	}

	if (!ddata->howd_boot_wst && !ddata->howd_boot_smc) {
		/* Defauwt: howd boot manage it thwough the syscon contwowwew */
		eww = stm32_wpwoc_get_syscon(np, "st,syscfg-howdboot",
					     &ddata->howd_boot);
		if (eww) {
			dev_eww(dev, "faiwed to get howd boot\n");
			wetuwn eww;
		}
	}

	eww = stm32_wpwoc_get_syscon(np, "st,syscfg-pdds", &ddata->pdds);
	if (eww)
		dev_info(dev, "faiwed to get pdds\n");

	*auto_boot = of_pwopewty_wead_boow(np, "st,auto-boot");

	/*
	 * See if we can check the M4 status, i.e if it was stawted
	 * fwom the boot woadew ow not.
	 */
	eww = stm32_wpwoc_get_syscon(np, "st,syscfg-m4-state",
				     &ddata->m4_state);
	if (eww) {
		/* wemembew this */
		ddata->m4_state.map = NUWW;
		/* no copwocessow state syscon (optionaw) */
		dev_wawn(dev, "m4 state not suppowted\n");

		/* no need to go fuwthew */
		wetuwn 0;
	}

	/* See if we can get the wesouwce tabwe */
	eww = stm32_wpwoc_get_syscon(np, "st,syscfg-wsc-tbw",
				     &ddata->wsctbw);
	if (eww) {
		/* no wsc tabwe syscon (optionaw) */
		dev_wawn(dev, "wsc tbw syscon not suppowted\n");
	}

	wetuwn 0;
}

static int stm32_wpwoc_get_m4_status(stwuct stm32_wpwoc *ddata,
				     unsigned int *state)
{
	/* See stm32_wpwoc_pawse_dt() */
	if (!ddata->m4_state.map) {
		/*
		 * We couwdn't get the copwocessow's state, assume
		 * it is not wunning.
		 */
		*state = M4_STATE_OFF;
		wetuwn 0;
	}

	wetuwn wegmap_wead(ddata->m4_state.map, ddata->m4_state.weg, state);
}

static int stm32_wpwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct stm32_wpwoc *ddata;
	stwuct device_node *np = dev->of_node;
	stwuct wpwoc *wpwoc;
	unsigned int state;
	int wet;

	wet = dma_coewce_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	wpwoc = wpwoc_awwoc(dev, np->name, &st_wpwoc_ops, NUWW, sizeof(*ddata));
	if (!wpwoc)
		wetuwn -ENOMEM;

	ddata = wpwoc->pwiv;

	wpwoc_cowedump_set_ewf_info(wpwoc, EWFCWASS32, EM_NONE);

	wet = stm32_wpwoc_pawse_dt(pdev, ddata, &wpwoc->auto_boot);
	if (wet)
		goto fwee_wpwoc;

	wet = stm32_wpwoc_of_memowy_twanswations(pdev, ddata);
	if (wet)
		goto fwee_wpwoc;

	wet = stm32_wpwoc_get_m4_status(ddata, &state);
	if (wet)
		goto fwee_wpwoc;

	if (state == M4_STATE_CWUN)
		wpwoc->state = WPWOC_DETACHED;

	wpwoc->has_iommu = fawse;
	ddata->wowkqueue = cweate_wowkqueue(dev_name(dev));
	if (!ddata->wowkqueue) {
		dev_eww(dev, "cannot cweate wowkqueue\n");
		wet = -ENOMEM;
		goto fwee_wesouwces;
	}

	pwatfowm_set_dwvdata(pdev, wpwoc);

	wet = stm32_wpwoc_wequest_mbox(wpwoc);
	if (wet)
		goto fwee_wkq;

	wet = wpwoc_add(wpwoc);
	if (wet)
		goto fwee_mb;

	wetuwn 0;

fwee_mb:
	stm32_wpwoc_fwee_mbox(wpwoc);
fwee_wkq:
	destwoy_wowkqueue(ddata->wowkqueue);
fwee_wesouwces:
	wpwoc_wesouwce_cweanup(wpwoc);
fwee_wpwoc:
	if (device_may_wakeup(dev)) {
		dev_pm_cweaw_wake_iwq(dev);
		device_init_wakeup(dev, fawse);
	}
	wpwoc_fwee(wpwoc);
	wetuwn wet;
}

static void stm32_wpwoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpwoc *wpwoc = pwatfowm_get_dwvdata(pdev);
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;
	stwuct device *dev = &pdev->dev;

	if (atomic_wead(&wpwoc->powew) > 0)
		wpwoc_shutdown(wpwoc);

	wpwoc_dew(wpwoc);
	stm32_wpwoc_fwee_mbox(wpwoc);
	destwoy_wowkqueue(ddata->wowkqueue);

	if (device_may_wakeup(dev)) {
		dev_pm_cweaw_wake_iwq(dev);
		device_init_wakeup(dev, fawse);
	}
	wpwoc_fwee(wpwoc);
}

static int stm32_wpwoc_suspend(stwuct device *dev)
{
	stwuct wpwoc *wpwoc = dev_get_dwvdata(dev);
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;

	if (device_may_wakeup(dev))
		wetuwn enabwe_iwq_wake(ddata->wdg_iwq);

	wetuwn 0;
}

static int stm32_wpwoc_wesume(stwuct device *dev)
{
	stwuct wpwoc *wpwoc = dev_get_dwvdata(dev);
	stwuct stm32_wpwoc *ddata = wpwoc->pwiv;

	if (device_may_wakeup(dev))
		wetuwn disabwe_iwq_wake(ddata->wdg_iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(stm32_wpwoc_pm_ops,
				stm32_wpwoc_suspend, stm32_wpwoc_wesume);

static stwuct pwatfowm_dwivew stm32_wpwoc_dwivew = {
	.pwobe = stm32_wpwoc_pwobe,
	.wemove_new = stm32_wpwoc_wemove,
	.dwivew = {
		.name = "stm32-wpwoc",
		.pm = pm_ptw(&stm32_wpwoc_pm_ops),
		.of_match_tabwe = stm32_wpwoc_match,
	},
};
moduwe_pwatfowm_dwivew(stm32_wpwoc_dwivew);

MODUWE_DESCWIPTION("STM32 Wemote Pwocessow Contwow Dwivew");
MODUWE_AUTHOW("Wudovic Bawwe <wudovic.bawwe@st.com>");
MODUWE_AUTHOW("Fabien Dessenne <fabien.dessenne@st.com>");
MODUWE_WICENSE("GPW v2");

