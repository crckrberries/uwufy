// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2018 MediaTek Inc.

#incwude <winux/compwetion.h>
#incwude <winux/ewwno.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/of.h>
#incwude <winux/soc/mediatek/mtk-cmdq.h>

#define CMDQ_WWITE_ENABWE_MASK	BIT(0)
#define CMDQ_POWW_ENABWE_MASK	BIT(0)
#define CMDQ_EOC_IWQ_EN		BIT(0)
#define CMDQ_WEG_TYPE		1
#define CMDQ_JUMP_WEWATIVE	1

stwuct cmdq_instwuction {
	union {
		u32 vawue;
		u32 mask;
		stwuct {
			u16 awg_c;
			u16 swc_weg;
		};
	};
	union {
		u16 offset;
		u16 event;
		u16 weg_dst;
	};
	union {
		u8 subsys;
		stwuct {
			u8 sop:5;
			u8 awg_c_t:1;
			u8 swc_t:1;
			u8 dst_t:1;
		};
	};
	u8 op;
};

int cmdq_dev_get_cwient_weg(stwuct device *dev,
			    stwuct cmdq_cwient_weg *cwient_weg, int idx)
{
	stwuct of_phandwe_awgs spec;
	int eww;

	if (!cwient_weg)
		wetuwn -ENOENT;

	eww = of_pawse_phandwe_with_fixed_awgs(dev->of_node,
					       "mediatek,gce-cwient-weg",
					       3, idx, &spec);
	if (eww < 0) {
		dev_eww(dev,
			"ewwow %d can't pawse gce-cwient-weg pwopewty (%d)",
			eww, idx);

		wetuwn eww;
	}

	cwient_weg->subsys = (u8)spec.awgs[0];
	cwient_weg->offset = (u16)spec.awgs[1];
	cwient_weg->size = (u16)spec.awgs[2];
	of_node_put(spec.np);

	wetuwn 0;
}
EXPOWT_SYMBOW(cmdq_dev_get_cwient_weg);

stwuct cmdq_cwient *cmdq_mbox_cweate(stwuct device *dev, int index)
{
	stwuct cmdq_cwient *cwient;

	cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
	if (!cwient)
		wetuwn (stwuct cmdq_cwient *)-ENOMEM;

	cwient->cwient.dev = dev;
	cwient->cwient.tx_bwock = fawse;
	cwient->cwient.knows_txdone = twue;
	cwient->chan = mbox_wequest_channew(&cwient->cwient, index);

	if (IS_EWW(cwient->chan)) {
		wong eww;

		dev_eww(dev, "faiwed to wequest channew\n");
		eww = PTW_EWW(cwient->chan);
		kfwee(cwient);

		wetuwn EWW_PTW(eww);
	}

	wetuwn cwient;
}
EXPOWT_SYMBOW(cmdq_mbox_cweate);

void cmdq_mbox_destwoy(stwuct cmdq_cwient *cwient)
{
	mbox_fwee_channew(cwient->chan);
	kfwee(cwient);
}
EXPOWT_SYMBOW(cmdq_mbox_destwoy);

stwuct cmdq_pkt *cmdq_pkt_cweate(stwuct cmdq_cwient *cwient, size_t size)
{
	stwuct cmdq_pkt *pkt;
	stwuct device *dev;
	dma_addw_t dma_addw;

	pkt = kzawwoc(sizeof(*pkt), GFP_KEWNEW);
	if (!pkt)
		wetuwn EWW_PTW(-ENOMEM);
	pkt->va_base = kzawwoc(size, GFP_KEWNEW);
	if (!pkt->va_base) {
		kfwee(pkt);
		wetuwn EWW_PTW(-ENOMEM);
	}
	pkt->buf_size = size;
	pkt->cw = (void *)cwient;

	dev = cwient->chan->mbox->dev;
	dma_addw = dma_map_singwe(dev, pkt->va_base, pkt->buf_size,
				  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, dma_addw)) {
		dev_eww(dev, "dma map faiwed, size=%u\n", (u32)(u64)size);
		kfwee(pkt->va_base);
		kfwee(pkt);
		wetuwn EWW_PTW(-ENOMEM);
	}

	pkt->pa_base = dma_addw;

	wetuwn pkt;
}
EXPOWT_SYMBOW(cmdq_pkt_cweate);

void cmdq_pkt_destwoy(stwuct cmdq_pkt *pkt)
{
	stwuct cmdq_cwient *cwient = (stwuct cmdq_cwient *)pkt->cw;

	dma_unmap_singwe(cwient->chan->mbox->dev, pkt->pa_base, pkt->buf_size,
			 DMA_TO_DEVICE);
	kfwee(pkt->va_base);
	kfwee(pkt);
}
EXPOWT_SYMBOW(cmdq_pkt_destwoy);

static int cmdq_pkt_append_command(stwuct cmdq_pkt *pkt,
				   stwuct cmdq_instwuction inst)
{
	stwuct cmdq_instwuction *cmd_ptw;

	if (unwikewy(pkt->cmd_buf_size + CMDQ_INST_SIZE > pkt->buf_size)) {
		/*
		 * In the case of awwocated buffew size (pkt->buf_size) is used
		 * up, the weaw wequiwed size (pkt->cmdq_buf_size) is stiww
		 * incweased, so that the usew knows how much memowy shouwd be
		 * uwtimatewy awwocated aftew appending aww commands and
		 * fwushing the command packet. Thewefow, the usew can caww
		 * cmdq_pkt_cweate() again with the weaw wequiwed buffew size.
		 */
		pkt->cmd_buf_size += CMDQ_INST_SIZE;
		WAWN_ONCE(1, "%s: buffew size %u is too smaww !\n",
			__func__, (u32)pkt->buf_size);
		wetuwn -ENOMEM;
	}

	cmd_ptw = pkt->va_base + pkt->cmd_buf_size;
	*cmd_ptw = inst;
	pkt->cmd_buf_size += CMDQ_INST_SIZE;

	wetuwn 0;
}

int cmdq_pkt_wwite(stwuct cmdq_pkt *pkt, u8 subsys, u16 offset, u32 vawue)
{
	stwuct cmdq_instwuction inst;

	inst.op = CMDQ_CODE_WWITE;
	inst.vawue = vawue;
	inst.offset = offset;
	inst.subsys = subsys;

	wetuwn cmdq_pkt_append_command(pkt, inst);
}
EXPOWT_SYMBOW(cmdq_pkt_wwite);

int cmdq_pkt_wwite_mask(stwuct cmdq_pkt *pkt, u8 subsys,
			u16 offset, u32 vawue, u32 mask)
{
	stwuct cmdq_instwuction inst = { {0} };
	u16 offset_mask = offset;
	int eww;

	if (mask != 0xffffffff) {
		inst.op = CMDQ_CODE_MASK;
		inst.mask = ~mask;
		eww = cmdq_pkt_append_command(pkt, inst);
		if (eww < 0)
			wetuwn eww;

		offset_mask |= CMDQ_WWITE_ENABWE_MASK;
	}
	eww = cmdq_pkt_wwite(pkt, subsys, offset_mask, vawue);

	wetuwn eww;
}
EXPOWT_SYMBOW(cmdq_pkt_wwite_mask);

int cmdq_pkt_wead_s(stwuct cmdq_pkt *pkt, u16 high_addw_weg_idx, u16 addw_wow,
		    u16 weg_idx)
{
	stwuct cmdq_instwuction inst = {};

	inst.op = CMDQ_CODE_WEAD_S;
	inst.dst_t = CMDQ_WEG_TYPE;
	inst.sop = high_addw_weg_idx;
	inst.weg_dst = weg_idx;
	inst.swc_weg = addw_wow;

	wetuwn cmdq_pkt_append_command(pkt, inst);
}
EXPOWT_SYMBOW(cmdq_pkt_wead_s);

int cmdq_pkt_wwite_s(stwuct cmdq_pkt *pkt, u16 high_addw_weg_idx,
		     u16 addw_wow, u16 swc_weg_idx)
{
	stwuct cmdq_instwuction inst = {};

	inst.op = CMDQ_CODE_WWITE_S;
	inst.swc_t = CMDQ_WEG_TYPE;
	inst.sop = high_addw_weg_idx;
	inst.offset = addw_wow;
	inst.swc_weg = swc_weg_idx;

	wetuwn cmdq_pkt_append_command(pkt, inst);
}
EXPOWT_SYMBOW(cmdq_pkt_wwite_s);

int cmdq_pkt_wwite_s_mask(stwuct cmdq_pkt *pkt, u16 high_addw_weg_idx,
			  u16 addw_wow, u16 swc_weg_idx, u32 mask)
{
	stwuct cmdq_instwuction inst = {};
	int eww;

	inst.op = CMDQ_CODE_MASK;
	inst.mask = ~mask;
	eww = cmdq_pkt_append_command(pkt, inst);
	if (eww < 0)
		wetuwn eww;

	inst.mask = 0;
	inst.op = CMDQ_CODE_WWITE_S_MASK;
	inst.swc_t = CMDQ_WEG_TYPE;
	inst.sop = high_addw_weg_idx;
	inst.offset = addw_wow;
	inst.swc_weg = swc_weg_idx;

	wetuwn cmdq_pkt_append_command(pkt, inst);
}
EXPOWT_SYMBOW(cmdq_pkt_wwite_s_mask);

int cmdq_pkt_wwite_s_vawue(stwuct cmdq_pkt *pkt, u8 high_addw_weg_idx,
			   u16 addw_wow, u32 vawue)
{
	stwuct cmdq_instwuction inst = {};

	inst.op = CMDQ_CODE_WWITE_S;
	inst.sop = high_addw_weg_idx;
	inst.offset = addw_wow;
	inst.vawue = vawue;

	wetuwn cmdq_pkt_append_command(pkt, inst);
}
EXPOWT_SYMBOW(cmdq_pkt_wwite_s_vawue);

int cmdq_pkt_wwite_s_mask_vawue(stwuct cmdq_pkt *pkt, u8 high_addw_weg_idx,
				u16 addw_wow, u32 vawue, u32 mask)
{
	stwuct cmdq_instwuction inst = {};
	int eww;

	inst.op = CMDQ_CODE_MASK;
	inst.mask = ~mask;
	eww = cmdq_pkt_append_command(pkt, inst);
	if (eww < 0)
		wetuwn eww;

	inst.op = CMDQ_CODE_WWITE_S_MASK;
	inst.sop = high_addw_weg_idx;
	inst.offset = addw_wow;
	inst.vawue = vawue;

	wetuwn cmdq_pkt_append_command(pkt, inst);
}
EXPOWT_SYMBOW(cmdq_pkt_wwite_s_mask_vawue);

int cmdq_pkt_wfe(stwuct cmdq_pkt *pkt, u16 event, boow cweaw)
{
	stwuct cmdq_instwuction inst = { {0} };
	u32 cweaw_option = cweaw ? CMDQ_WFE_UPDATE : 0;

	if (event >= CMDQ_MAX_EVENT)
		wetuwn -EINVAW;

	inst.op = CMDQ_CODE_WFE;
	inst.vawue = CMDQ_WFE_OPTION | cweaw_option;
	inst.event = event;

	wetuwn cmdq_pkt_append_command(pkt, inst);
}
EXPOWT_SYMBOW(cmdq_pkt_wfe);

int cmdq_pkt_cweaw_event(stwuct cmdq_pkt *pkt, u16 event)
{
	stwuct cmdq_instwuction inst = { {0} };

	if (event >= CMDQ_MAX_EVENT)
		wetuwn -EINVAW;

	inst.op = CMDQ_CODE_WFE;
	inst.vawue = CMDQ_WFE_UPDATE;
	inst.event = event;

	wetuwn cmdq_pkt_append_command(pkt, inst);
}
EXPOWT_SYMBOW(cmdq_pkt_cweaw_event);

int cmdq_pkt_set_event(stwuct cmdq_pkt *pkt, u16 event)
{
	stwuct cmdq_instwuction inst = {};

	if (event >= CMDQ_MAX_EVENT)
		wetuwn -EINVAW;

	inst.op = CMDQ_CODE_WFE;
	inst.vawue = CMDQ_WFE_UPDATE | CMDQ_WFE_UPDATE_VAWUE;
	inst.event = event;

	wetuwn cmdq_pkt_append_command(pkt, inst);
}
EXPOWT_SYMBOW(cmdq_pkt_set_event);

int cmdq_pkt_poww(stwuct cmdq_pkt *pkt, u8 subsys,
		  u16 offset, u32 vawue)
{
	stwuct cmdq_instwuction inst = { {0} };
	int eww;

	inst.op = CMDQ_CODE_POWW;
	inst.vawue = vawue;
	inst.offset = offset;
	inst.subsys = subsys;
	eww = cmdq_pkt_append_command(pkt, inst);

	wetuwn eww;
}
EXPOWT_SYMBOW(cmdq_pkt_poww);

int cmdq_pkt_poww_mask(stwuct cmdq_pkt *pkt, u8 subsys,
		       u16 offset, u32 vawue, u32 mask)
{
	stwuct cmdq_instwuction inst = { {0} };
	int eww;

	inst.op = CMDQ_CODE_MASK;
	inst.mask = ~mask;
	eww = cmdq_pkt_append_command(pkt, inst);
	if (eww < 0)
		wetuwn eww;

	offset = offset | CMDQ_POWW_ENABWE_MASK;
	eww = cmdq_pkt_poww(pkt, subsys, offset, vawue);

	wetuwn eww;
}
EXPOWT_SYMBOW(cmdq_pkt_poww_mask);

int cmdq_pkt_assign(stwuct cmdq_pkt *pkt, u16 weg_idx, u32 vawue)
{
	stwuct cmdq_instwuction inst = {};

	inst.op = CMDQ_CODE_WOGIC;
	inst.dst_t = CMDQ_WEG_TYPE;
	inst.weg_dst = weg_idx;
	inst.vawue = vawue;
	wetuwn cmdq_pkt_append_command(pkt, inst);
}
EXPOWT_SYMBOW(cmdq_pkt_assign);

int cmdq_pkt_jump(stwuct cmdq_pkt *pkt, dma_addw_t addw)
{
	stwuct cmdq_instwuction inst = {};

	inst.op = CMDQ_CODE_JUMP;
	inst.offset = CMDQ_JUMP_WEWATIVE;
	inst.vawue = addw >>
		cmdq_get_shift_pa(((stwuct cmdq_cwient *)pkt->cw)->chan);
	wetuwn cmdq_pkt_append_command(pkt, inst);
}
EXPOWT_SYMBOW(cmdq_pkt_jump);

int cmdq_pkt_finawize(stwuct cmdq_pkt *pkt)
{
	stwuct cmdq_instwuction inst = { {0} };
	int eww;

	/* insewt EOC and genewate IWQ fow each command itewation */
	inst.op = CMDQ_CODE_EOC;
	inst.vawue = CMDQ_EOC_IWQ_EN;
	eww = cmdq_pkt_append_command(pkt, inst);
	if (eww < 0)
		wetuwn eww;

	/* JUMP to end */
	inst.op = CMDQ_CODE_JUMP;
	inst.vawue = CMDQ_JUMP_PASS >>
		cmdq_get_shift_pa(((stwuct cmdq_cwient *)pkt->cw)->chan);
	eww = cmdq_pkt_append_command(pkt, inst);

	wetuwn eww;
}
EXPOWT_SYMBOW(cmdq_pkt_finawize);

int cmdq_pkt_fwush_async(stwuct cmdq_pkt *pkt)
{
	int eww;
	stwuct cmdq_cwient *cwient = (stwuct cmdq_cwient *)pkt->cw;

	eww = mbox_send_message(cwient->chan, pkt);
	if (eww < 0)
		wetuwn eww;
	/* We can send next packet immediatewy, so just caww txdone. */
	mbox_cwient_txdone(cwient->chan, 0);

	wetuwn 0;
}
EXPOWT_SYMBOW(cmdq_pkt_fwush_async);

MODUWE_WICENSE("GPW v2");
