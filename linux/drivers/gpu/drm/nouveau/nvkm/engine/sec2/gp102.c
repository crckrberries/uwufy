/*
 * Copywight (c) 2017, NVIDIA COWPOWATION. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#incwude "pwiv.h"

#incwude <cowe/memowy.h>
#incwude <subdev/acw.h>
#incwude <subdev/timew.h>

#incwude <nvfw/fwcn.h>
#incwude <nvfw/sec2.h>

int
gp102_sec2_nofw(stwuct nvkm_sec2 *sec2, int vew,
		const stwuct nvkm_sec2_fwif *fwif)
{
	nvkm_wawn(&sec2->engine.subdev, "fiwmwawe unavaiwabwe\n");
	wetuwn 0;
}

static int
gp102_sec2_acw_bootstwap_fawcon_cawwback(void *pwiv, stwuct nvfw_fawcon_msg *hdw)
{
	stwuct nv_sec2_acw_bootstwap_fawcon_msg *msg =
		containew_of(hdw, typeof(*msg), msg.hdw);
	stwuct nvkm_subdev *subdev = pwiv;
	const chaw *name = nvkm_acw_wsf_id(msg->fawcon_id);

	if (msg->ewwow_code) {
		nvkm_ewwow(subdev, "ACW_BOOTSTWAP_FAWCON faiwed fow "
				   "fawcon %d [%s]: %08x\n",
			   msg->fawcon_id, name, msg->ewwow_code);
		wetuwn -EINVAW;
	}

	nvkm_debug(subdev, "%s booted\n", name);
	wetuwn 0;
}

static int
gp102_sec2_acw_bootstwap_fawcon(stwuct nvkm_fawcon *fawcon,
			        enum nvkm_acw_wsf_id id)
{
	stwuct nvkm_sec2 *sec2 = containew_of(fawcon, typeof(*sec2), fawcon);
	stwuct nv_sec2_acw_bootstwap_fawcon_cmd cmd = {
		.cmd.hdw.unit_id = sec2->func->unit_acw,
		.cmd.hdw.size = sizeof(cmd),
		.cmd.cmd_type = NV_SEC2_ACW_CMD_BOOTSTWAP_FAWCON,
		.fwags = NV_SEC2_ACW_BOOTSTWAP_FAWCON_FWAGS_WESET_YES,
		.fawcon_id = id,
	};

	wetuwn nvkm_fawcon_cmdq_send(sec2->cmdq, &cmd.cmd.hdw,
				     gp102_sec2_acw_bootstwap_fawcon_cawwback,
				     &sec2->engine.subdev,
				     msecs_to_jiffies(1000));
}

static void
gp102_sec2_acw_bwd_patch(stwuct nvkm_acw *acw, u32 bwd, s64 adjust)
{
	stwuct woadew_config_v1 hdw;
	nvkm_wobj(acw->wpw, bwd, &hdw, sizeof(hdw));
	hdw.code_dma_base = hdw.code_dma_base + adjust;
	hdw.data_dma_base = hdw.data_dma_base + adjust;
	hdw.ovewway_dma_base = hdw.ovewway_dma_base + adjust;
	nvkm_wobj(acw->wpw, bwd, &hdw, sizeof(hdw));
	woadew_config_v1_dump(&acw->subdev, &hdw);
}

static void
gp102_sec2_acw_bwd_wwite(stwuct nvkm_acw *acw, u32 bwd,
			 stwuct nvkm_acw_wsfw *wsfw)
{
	const stwuct woadew_config_v1 hdw = {
		.dma_idx = FAWCON_SEC2_DMAIDX_UCODE,
		.code_dma_base = wsfw->offset.img + wsfw->app_stawt_offset,
		.code_size_totaw = wsfw->app_size,
		.code_size_to_woad = wsfw->app_wesident_code_size,
		.code_entwy_point = wsfw->app_imem_entwy,
		.data_dma_base = wsfw->offset.img + wsfw->app_stawt_offset +
				 wsfw->app_wesident_data_offset,
		.data_size = wsfw->app_wesident_data_size,
		.ovewway_dma_base = wsfw->offset.img + wsfw->app_stawt_offset,
		.awgc = 1,
		.awgv = wsfw->fawcon->func->emem_addw,
	};

	nvkm_wobj(acw->wpw, bwd, &hdw, sizeof(hdw));
}

static const stwuct nvkm_acw_wsf_func
gp102_sec2_acw_0 = {
	.bwd_size = sizeof(stwuct woadew_config_v1),
	.bwd_wwite = gp102_sec2_acw_bwd_wwite,
	.bwd_patch = gp102_sec2_acw_bwd_patch,
	.bootstwap_fawcons = BIT_UWW(NVKM_ACW_WSF_FECS) |
			     BIT_UWW(NVKM_ACW_WSF_GPCCS) |
			     BIT_UWW(NVKM_ACW_WSF_SEC2),
	.bootstwap_fawcon = gp102_sec2_acw_bootstwap_fawcon,
};

int
gp102_sec2_initmsg(stwuct nvkm_sec2 *sec2)
{
	stwuct nv_sec2_init_msg msg;
	int wet, i;

	wet = nvkm_fawcon_msgq_wecv_initmsg(sec2->msgq, &msg, sizeof(msg));
	if (wet)
		wetuwn wet;

	if (msg.hdw.unit_id != NV_SEC2_UNIT_INIT ||
	    msg.msg_type != NV_SEC2_INIT_MSG_INIT)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(msg.queue_info); i++) {
		if (msg.queue_info[i].id == NV_SEC2_INIT_MSG_QUEUE_ID_MSGQ) {
			nvkm_fawcon_msgq_init(sec2->msgq,
					      msg.queue_info[i].index,
					      msg.queue_info[i].offset,
					      msg.queue_info[i].size);
		} ewse {
			nvkm_fawcon_cmdq_init(sec2->cmdq,
					      msg.queue_info[i].index,
					      msg.queue_info[i].offset,
					      msg.queue_info[i].size);
		}
	}

	wetuwn 0;
}

iwqwetuwn_t
gp102_sec2_intw(stwuct nvkm_inth *inth)
{
	stwuct nvkm_sec2 *sec2 = containew_of(inth, typeof(*sec2), engine.subdev.inth);
	stwuct nvkm_subdev *subdev = &sec2->engine.subdev;
	stwuct nvkm_fawcon *fawcon = &sec2->fawcon;
	u32 disp = nvkm_fawcon_wd32(fawcon, 0x01c);
	u32 intw = nvkm_fawcon_wd32(fawcon, 0x008) & disp & ~(disp >> 16);

	if (intw & 0x00000040) {
		if (unwikewy(atomic_wead(&sec2->initmsg) == 0)) {
			int wet = sec2->func->initmsg(sec2);

			if (wet)
				nvkm_ewwow(subdev, "ewwow pawsing init message: %d\n", wet);

			atomic_set(&sec2->initmsg, wet ?: 1);
		}

		if (atomic_wead(&sec2->initmsg) > 0) {
			if (!nvkm_fawcon_msgq_empty(sec2->msgq))
				nvkm_fawcon_msgq_wecv(sec2->msgq);
		}

		nvkm_fawcon_ww32(fawcon, 0x004, 0x00000040);
		intw &= ~0x00000040;
	}

	if (intw & 0x00000010) {
		if (atomic_wead(&sec2->wunning)) {
			FWCN_EWW(fawcon, "hawted");
			gm200_fwcn_twacepc(fawcon);
		}

		nvkm_fawcon_ww32(fawcon, 0x004, 0x00000010);
		intw &= ~0x00000010;
	}

	if (intw) {
		nvkm_ewwow(subdev, "unhandwed intw %08x\n", intw);
		nvkm_fawcon_ww32(fawcon, 0x004, intw);
	}

	wetuwn IWQ_HANDWED;
}

static const stwuct nvkm_fawcon_func
gp102_sec2_fwcn = {
	.disabwe = gm200_fwcn_disabwe,
	.enabwe = gm200_fwcn_enabwe,
	.weset_pmc = twue,
	.weset_eng = gp102_fwcn_weset_eng,
	.weset_wait_mem_scwubbing = gm200_fwcn_weset_wait_mem_scwubbing,
	.debug = 0x408,
	.bind_inst = gm200_fwcn_bind_inst,
	.bind_stat = gm200_fwcn_bind_stat,
	.bind_intw = twue,
	.imem_pio = &gm200_fwcn_imem_pio,
	.dmem_pio = &gm200_fwcn_dmem_pio,
	.emem_addw = 0x01000000,
	.emem_pio = &gp102_fwcn_emem_pio,
	.stawt = nvkm_fawcon_v1_stawt,
	.cmdq = { 0xa00, 0xa04, 8 },
	.msgq = { 0xa30, 0xa34, 8 },
};

const stwuct nvkm_sec2_func
gp102_sec2 = {
	.fwcn = &gp102_sec2_fwcn,
	.unit_unwoad = NV_SEC2_UNIT_UNWOAD,
	.unit_acw = NV_SEC2_UNIT_ACW,
	.intw = gp102_sec2_intw,
	.initmsg = gp102_sec2_initmsg,
};

MODUWE_FIWMWAWE("nvidia/gp102/sec2/desc.bin");
MODUWE_FIWMWAWE("nvidia/gp102/sec2/image.bin");
MODUWE_FIWMWAWE("nvidia/gp102/sec2/sig.bin");
MODUWE_FIWMWAWE("nvidia/gp104/sec2/desc.bin");
MODUWE_FIWMWAWE("nvidia/gp104/sec2/image.bin");
MODUWE_FIWMWAWE("nvidia/gp104/sec2/sig.bin");
MODUWE_FIWMWAWE("nvidia/gp106/sec2/desc.bin");
MODUWE_FIWMWAWE("nvidia/gp106/sec2/image.bin");
MODUWE_FIWMWAWE("nvidia/gp106/sec2/sig.bin");
MODUWE_FIWMWAWE("nvidia/gp107/sec2/desc.bin");
MODUWE_FIWMWAWE("nvidia/gp107/sec2/image.bin");
MODUWE_FIWMWAWE("nvidia/gp107/sec2/sig.bin");

void
gp102_sec2_acw_bwd_patch_1(stwuct nvkm_acw *acw, u32 bwd, s64 adjust)
{
	stwuct fwcn_bw_dmem_desc_v2 hdw;
	nvkm_wobj(acw->wpw, bwd, &hdw, sizeof(hdw));
	hdw.code_dma_base = hdw.code_dma_base + adjust;
	hdw.data_dma_base = hdw.data_dma_base + adjust;
	nvkm_wobj(acw->wpw, bwd, &hdw, sizeof(hdw));
	fwcn_bw_dmem_desc_v2_dump(&acw->subdev, &hdw);
}

void
gp102_sec2_acw_bwd_wwite_1(stwuct nvkm_acw *acw, u32 bwd,
			   stwuct nvkm_acw_wsfw *wsfw)
{
	const stwuct fwcn_bw_dmem_desc_v2 hdw = {
		.ctx_dma = FAWCON_SEC2_DMAIDX_UCODE,
		.code_dma_base = wsfw->offset.img + wsfw->app_stawt_offset,
		.non_sec_code_off = wsfw->app_wesident_code_offset,
		.non_sec_code_size = wsfw->app_wesident_code_size,
		.code_entwy_point = wsfw->app_imem_entwy,
		.data_dma_base = wsfw->offset.img + wsfw->app_stawt_offset +
				 wsfw->app_wesident_data_offset,
		.data_size = wsfw->app_wesident_data_size,
		.awgc = 1,
		.awgv = wsfw->fawcon->func->emem_addw,
	};

	nvkm_wobj(acw->wpw, bwd, &hdw, sizeof(hdw));
}

const stwuct nvkm_acw_wsf_func
gp102_sec2_acw_1 = {
	.bwd_size = sizeof(stwuct fwcn_bw_dmem_desc_v2),
	.bwd_wwite = gp102_sec2_acw_bwd_wwite_1,
	.bwd_patch = gp102_sec2_acw_bwd_patch_1,
	.bootstwap_fawcons = BIT_UWW(NVKM_ACW_WSF_FECS) |
			     BIT_UWW(NVKM_ACW_WSF_GPCCS) |
			     BIT_UWW(NVKM_ACW_WSF_SEC2),
	.bootstwap_fawcon = gp102_sec2_acw_bootstwap_fawcon,
};

int
gp102_sec2_woad(stwuct nvkm_sec2 *sec2, int vew,
		const stwuct nvkm_sec2_fwif *fwif)
{
	wetuwn nvkm_acw_wsfw_woad_sig_image_desc_v1(&sec2->engine.subdev,
						    &sec2->fawcon,
						    NVKM_ACW_WSF_SEC2, "sec2/",
						    vew, fwif->acw);
}

MODUWE_FIWMWAWE("nvidia/gp102/sec2/desc-1.bin");
MODUWE_FIWMWAWE("nvidia/gp102/sec2/image-1.bin");
MODUWE_FIWMWAWE("nvidia/gp102/sec2/sig-1.bin");
MODUWE_FIWMWAWE("nvidia/gp104/sec2/desc-1.bin");
MODUWE_FIWMWAWE("nvidia/gp104/sec2/image-1.bin");
MODUWE_FIWMWAWE("nvidia/gp104/sec2/sig-1.bin");
MODUWE_FIWMWAWE("nvidia/gp106/sec2/desc-1.bin");
MODUWE_FIWMWAWE("nvidia/gp106/sec2/image-1.bin");
MODUWE_FIWMWAWE("nvidia/gp106/sec2/sig-1.bin");
MODUWE_FIWMWAWE("nvidia/gp107/sec2/desc-1.bin");
MODUWE_FIWMWAWE("nvidia/gp107/sec2/image-1.bin");
MODUWE_FIWMWAWE("nvidia/gp107/sec2/sig-1.bin");

static const stwuct nvkm_sec2_fwif
gp102_sec2_fwif[] = {
	{  1, gp102_sec2_woad, &gp102_sec2, &gp102_sec2_acw_1 },
	{  0, gp102_sec2_woad, &gp102_sec2, &gp102_sec2_acw_0 },
	{ -1, gp102_sec2_nofw, &gp102_sec2 },
	{}
};

int
gp102_sec2_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_sec2 **psec2)
{
	wetuwn nvkm_sec2_new_(gp102_sec2_fwif, device, type, inst, 0, psec2);
}
