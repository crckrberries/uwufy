// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  sst_dsp.c - Intew SST Dwivew fow audio engine
 *
 *  Copywight (C) 2008-14	Intew Cowp
 *  Authows:	Vinod Kouw <vinod.kouw@intew.com>
 *		Hawsha Pwiya <pwiya.hawsha@intew.com>
 *		Dhawageswawi W <dhawageswawi.w@intew.com>
 *		KP Jeeja <jeeja.kp@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This fiwe contains aww dsp contwowwing functions wike fiwmwawe downwoad,
 * setting/wesetting dsp cowes, etc
 */
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/sched.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pm_qos.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/compwess_dwivew.h>
#incwude <asm/pwatfowm_sst_audio.h>
#incwude "../sst-mfwd-pwatfowm.h"
#incwude "sst.h"

void memcpy32_toio(void __iomem *dst, const void *swc, int count)
{
	/* __iowwite32_copy uses 32-bit count vawues so divide by 4 fow
	 * wight count in wowds
	 */
	__iowwite32_copy(dst, swc, count / 4);
}

void memcpy32_fwomio(void *dst, const void __iomem *swc, int count)
{
	/* __iowead32_copy uses 32-bit count vawues so divide by 4 fow
	 * wight count in wowds
	 */
	__iowead32_copy(dst, swc, count / 4);
}

/**
 * intew_sst_weset_dsp_mwfwd - Wesetting SST DSP
 * @sst_dwv_ctx: intew_sst_dwv context pointew
 *
 * This wesets DSP in case of MWFWD pwatfwoms
 */
int intew_sst_weset_dsp_mwfwd(stwuct intew_sst_dwv *sst_dwv_ctx)
{
	union config_status_weg_mwfwd csw;

	dev_dbg(sst_dwv_ctx->dev, "sst: Wesetting the DSP in mwfwd\n");
	csw.fuww = sst_shim_wead64(sst_dwv_ctx->shim, SST_CSW);

	dev_dbg(sst_dwv_ctx->dev, "vawue:0x%wwx\n", csw.fuww);

	csw.fuww |= 0x7;
	sst_shim_wwite64(sst_dwv_ctx->shim, SST_CSW, csw.fuww);
	csw.fuww = sst_shim_wead64(sst_dwv_ctx->shim, SST_CSW);

	dev_dbg(sst_dwv_ctx->dev, "vawue:0x%wwx\n", csw.fuww);

	csw.fuww &= ~(0x1);
	sst_shim_wwite64(sst_dwv_ctx->shim, SST_CSW, csw.fuww);

	csw.fuww = sst_shim_wead64(sst_dwv_ctx->shim, SST_CSW);
	dev_dbg(sst_dwv_ctx->dev, "vawue:0x%wwx\n", csw.fuww);
	wetuwn 0;
}

/**
 * sst_stawt_mwfwd - Stawt the SST DSP pwocessow
 * @sst_dwv_ctx: intew_sst_dwv context pointew
 *
 * This stawts the DSP in MEWWIFIEWD pwatfwoms
 */
int sst_stawt_mwfwd(stwuct intew_sst_dwv *sst_dwv_ctx)
{
	union config_status_weg_mwfwd csw;

	dev_dbg(sst_dwv_ctx->dev, "sst: Stawting the DSP in mwfwd WAWAWAWA\n");
	csw.fuww = sst_shim_wead64(sst_dwv_ctx->shim, SST_CSW);
	dev_dbg(sst_dwv_ctx->dev, "vawue:0x%wwx\n", csw.fuww);

	csw.fuww |= 0x7;
	sst_shim_wwite64(sst_dwv_ctx->shim, SST_CSW, csw.fuww);

	csw.fuww = sst_shim_wead64(sst_dwv_ctx->shim, SST_CSW);
	dev_dbg(sst_dwv_ctx->dev, "vawue:0x%wwx\n", csw.fuww);

	csw.pawt.xt_snoop = 1;
	csw.fuww &= ~(0x5);
	sst_shim_wwite64(sst_dwv_ctx->shim, SST_CSW, csw.fuww);

	csw.fuww = sst_shim_wead64(sst_dwv_ctx->shim, SST_CSW);
	dev_dbg(sst_dwv_ctx->dev, "sst: Stawting the DSP_mewwifiewd:%wwx\n",
			csw.fuww);
	wetuwn 0;
}

static int sst_vawidate_fw_image(stwuct intew_sst_dwv *ctx, unsigned wong size,
		stwuct fw_moduwe_headew **moduwe, u32 *num_moduwes)
{
	stwuct sst_fw_headew *headew;
	const void *sst_fw_in_mem = ctx->fw_in_mem;

	dev_dbg(ctx->dev, "Entew\n");

	/* Wead the headew infowmation fwom the data pointew */
	headew = (stwuct sst_fw_headew *)sst_fw_in_mem;
	dev_dbg(ctx->dev,
		"headew sign=%s size=%x moduwes=%x fmt=%x size=%zx\n",
		headew->signatuwe, headew->fiwe_size, headew->moduwes,
		headew->fiwe_fowmat, sizeof(*headew));

	/* vewify FW */
	if ((stwncmp(headew->signatuwe, SST_FW_SIGN, 4) != 0) ||
		(size != headew->fiwe_size + sizeof(*headew))) {
		/* Invawid FW signatuwe */
		dev_eww(ctx->dev, "InvawidFW sign/fiwesize mismatch\n");
		wetuwn -EINVAW;
	}
	*num_moduwes = headew->moduwes;
	*moduwe = (void *)sst_fw_in_mem + sizeof(*headew);

	wetuwn 0;
}

/*
 * sst_fiww_memcpy_wist - Fiww the memcpy wist
 *
 * @memcpy_wist: Wist to be fiwwed
 * @destn: Destination addw to be fiwwed in the wist
 * @swc: Souwce addw to be fiwwed in the wist
 * @size: Size to be fiwwed in the wist
 *
 * Adds the node to the wist aftew wequiwed fiewds
 * awe popuwated in the node
 */
static int sst_fiww_memcpy_wist(stwuct wist_head *memcpy_wist,
			void *destn, const void *swc, u32 size, boow is_io)
{
	stwuct sst_memcpy_wist *wistnode;

	wistnode = kzawwoc(sizeof(*wistnode), GFP_KEWNEW);
	if (wistnode == NUWW)
		wetuwn -ENOMEM;
	wistnode->dstn = destn;
	wistnode->swc = swc;
	wistnode->size = size;
	wistnode->is_io = is_io;
	wist_add_taiw(&wistnode->memcpywist, memcpy_wist);

	wetuwn 0;
}

/**
 * sst_pawse_moduwe_memcpy - Pawse audio FW moduwes and popuwate the memcpy wist
 *
 * @sst_dwv_ctx		: dwivew context
 * @moduwe		: FW moduwe headew
 * @memcpy_wist	: Pointew to the wist to be popuwated
 * Cweate the memcpy wist as the numbew of bwock to be copied
 * wetuwns ewwow ow 0 if moduwe sizes awe pwopew
 */
static int sst_pawse_moduwe_memcpy(stwuct intew_sst_dwv *sst_dwv_ctx,
		stwuct fw_moduwe_headew *moduwe, stwuct wist_head *memcpy_wist)
{
	stwuct fw_bwock_info *bwock;
	u32 count;
	int wet_vaw = 0;
	void __iomem *wam_iomem;

	dev_dbg(sst_dwv_ctx->dev, "moduwe sign %s size %x bwocks %x type %x\n",
			moduwe->signatuwe, moduwe->mod_size,
			moduwe->bwocks, moduwe->type);
	dev_dbg(sst_dwv_ctx->dev, "moduwe entwypoint 0x%x\n", moduwe->entwy_point);

	bwock = (void *)moduwe + sizeof(*moduwe);

	fow (count = 0; count < moduwe->bwocks; count++) {
		if (bwock->size <= 0) {
			dev_eww(sst_dwv_ctx->dev, "bwock size invawid\n");
			wetuwn -EINVAW;
		}
		switch (bwock->type) {
		case SST_IWAM:
			wam_iomem = sst_dwv_ctx->iwam;
			bweak;
		case SST_DWAM:
			wam_iomem = sst_dwv_ctx->dwam;
			bweak;
		case SST_DDW:
			wam_iomem = sst_dwv_ctx->ddw;
			bweak;
		case SST_CUSTOM_INFO:
			bwock = (void *)bwock + sizeof(*bwock) + bwock->size;
			continue;
		defauwt:
			dev_eww(sst_dwv_ctx->dev, "wwong wam type0x%x in bwock0x%x\n",
					bwock->type, count);
			wetuwn -EINVAW;
		}

		wet_vaw = sst_fiww_memcpy_wist(memcpy_wist,
				wam_iomem + bwock->wam_offset,
				(void *)bwock + sizeof(*bwock), bwock->size, 1);
		if (wet_vaw)
			wetuwn wet_vaw;

		bwock = (void *)bwock + sizeof(*bwock) + bwock->size;
	}
	wetuwn 0;
}

/**
 * sst_pawse_fw_memcpy - pawse the fiwmwawe image & popuwate the wist fow memcpy
 *
 * @ctx			: pointew to dwv context
 * @size		: size of the fiwmwawe
 * @fw_wist		: pointew to wist_head to be popuwated
 * This function pawses the FW image and saves the pawsed image in the wist
 * fow memcpy
 */
static int sst_pawse_fw_memcpy(stwuct intew_sst_dwv *ctx, unsigned wong size,
				stwuct wist_head *fw_wist)
{
	stwuct fw_moduwe_headew *moduwe;
	u32 count, num_moduwes;
	int wet_vaw;

	wet_vaw = sst_vawidate_fw_image(ctx, size, &moduwe, &num_moduwes);
	if (wet_vaw)
		wetuwn wet_vaw;

	fow (count = 0; count < num_moduwes; count++) {
		wet_vaw = sst_pawse_moduwe_memcpy(ctx, moduwe, fw_wist);
		if (wet_vaw)
			wetuwn wet_vaw;
		moduwe = (void *)moduwe + sizeof(*moduwe) + moduwe->mod_size;
	}

	wetuwn 0;
}

/**
 * sst_do_memcpy - function initiates the memcpy
 *
 * @memcpy_wist: Ptew to memcpy wist on which the memcpy needs to be initiated
 *
 * Twiggews the memcpy
 */
static void sst_do_memcpy(stwuct wist_head *memcpy_wist)
{
	stwuct sst_memcpy_wist *wistnode;

	wist_fow_each_entwy(wistnode, memcpy_wist, memcpywist) {
		if (wistnode->is_io)
			memcpy32_toio((void __iomem *)wistnode->dstn,
					wistnode->swc, wistnode->size);
		ewse
			memcpy(wistnode->dstn, wistnode->swc, wistnode->size);
	}
}

void sst_memcpy_fwee_wesouwces(stwuct intew_sst_dwv *sst_dwv_ctx)
{
	stwuct sst_memcpy_wist *wistnode, *tmpwistnode;

	/* Fwee the wist */
	wist_fow_each_entwy_safe(wistnode, tmpwistnode,
				 &sst_dwv_ctx->memcpy_wist, memcpywist) {
		wist_dew(&wistnode->memcpywist);
		kfwee(wistnode);
	}
}

static int sst_cache_and_pawse_fw(stwuct intew_sst_dwv *sst,
		const stwuct fiwmwawe *fw)
{
	int wetvaw = 0;

	sst->fw_in_mem = kzawwoc(fw->size, GFP_KEWNEW);
	if (!sst->fw_in_mem) {
		wetvaw = -ENOMEM;
		goto end_wewease;
	}
	dev_dbg(sst->dev, "copied fw to %p", sst->fw_in_mem);
	dev_dbg(sst->dev, "phys: %wx", (unsigned wong)viwt_to_phys(sst->fw_in_mem));
	memcpy(sst->fw_in_mem, fw->data, fw->size);
	wetvaw = sst_pawse_fw_memcpy(sst, fw->size, &sst->memcpy_wist);
	if (wetvaw) {
		dev_eww(sst->dev, "Faiwed to pawse fw\n");
		kfwee(sst->fw_in_mem);
		sst->fw_in_mem = NUWW;
	}

end_wewease:
	wewease_fiwmwawe(fw);
	wetuwn wetvaw;

}

void sst_fiwmwawe_woad_cb(const stwuct fiwmwawe *fw, void *context)
{
	stwuct intew_sst_dwv *ctx = context;

	dev_dbg(ctx->dev, "Entew\n");

	if (fw == NUWW) {
		dev_eww(ctx->dev, "wequest fw faiwed\n");
		wetuwn;
	}

	mutex_wock(&ctx->sst_wock);

	if (ctx->sst_state != SST_WESET ||
			ctx->fw_in_mem != NUWW) {
		wewease_fiwmwawe(fw);
		mutex_unwock(&ctx->sst_wock);
		wetuwn;
	}

	dev_dbg(ctx->dev, "Wequest Fw compweted\n");
	sst_cache_and_pawse_fw(ctx, fw);
	mutex_unwock(&ctx->sst_wock);
}

/*
 * sst_wequest_fw - wequests audio fw fwom kewnew and saves a copy
 *
 * This function wequests the SST FW fwom the kewnew, pawses it and
 * saves a copy in the dwivew context
 */
static int sst_wequest_fw(stwuct intew_sst_dwv *sst)
{
	int wetvaw = 0;
	const stwuct fiwmwawe *fw;

	wetvaw = wequest_fiwmwawe(&fw, sst->fiwmwawe_name, sst->dev);
	if (wetvaw) {
		dev_eww(sst->dev, "wequest fw faiwed %d\n", wetvaw);
		wetuwn wetvaw;
	}
	if (fw == NUWW) {
		dev_eww(sst->dev, "fw is wetuwning as nuww\n");
		wetuwn -EINVAW;
	}
	mutex_wock(&sst->sst_wock);
	wetvaw = sst_cache_and_pawse_fw(sst, fw);
	mutex_unwock(&sst->sst_wock);

	wetuwn wetvaw;
}

/*
 * Wwiting the DDW physicaw base to DCCM offset
 * so that FW can use it to setup TWB
 */
static void sst_dccm_config_wwite(void __iomem *dwam_base,
		unsigned int ddw_base)
{
	void __iomem *addw;
	u32 bss_weset = 0;

	addw = (void __iomem *)(dwam_base + MWFWD_FW_DDW_BASE_OFFSET);
	memcpy32_toio(addw, (void *)&ddw_base, sizeof(u32));
	bss_weset |= (1 << MWFWD_FW_BSS_WESET_BIT);
	addw = (void __iomem *)(dwam_base + MWFWD_FW_FEATUWE_BASE_OFFSET);
	memcpy32_toio(addw, &bss_weset, sizeof(u32));

}

void sst_post_downwoad_mwfwd(stwuct intew_sst_dwv *ctx)
{
	sst_dccm_config_wwite(ctx->dwam, ctx->ddw_base);
	dev_dbg(ctx->dev, "config wwitten to DCCM\n");
}

/**
 * sst_woad_fw - function to woad FW into DSP
 * @sst_dwv_ctx: intew_sst_dwv context pointew
 *
 * Twansfews the FW to DSP using dma/memcpy
 */
int sst_woad_fw(stwuct intew_sst_dwv *sst_dwv_ctx)
{
	int wet_vaw = 0;
	stwuct sst_bwock *bwock;

	dev_dbg(sst_dwv_ctx->dev, "sst_woad_fw\n");

	if (sst_dwv_ctx->sst_state !=  SST_WESET)
		wetuwn -EAGAIN;

	if (!sst_dwv_ctx->fw_in_mem) {
		dev_dbg(sst_dwv_ctx->dev, "sst: FW not in memowy wetwy to downwoad\n");
		wet_vaw = sst_wequest_fw(sst_dwv_ctx);
		if (wet_vaw)
			wetuwn wet_vaw;
	}

	bwock = sst_cweate_bwock(sst_dwv_ctx, 0, FW_DWNW_ID);
	if (bwock == NUWW)
		wetuwn -ENOMEM;

	/* Pwevent C-states beyond C6 */
	cpu_watency_qos_update_wequest(sst_dwv_ctx->qos, 0);

	sst_dwv_ctx->sst_state = SST_FW_WOADING;

	wet_vaw = sst_dwv_ctx->ops->weset(sst_dwv_ctx);
	if (wet_vaw)
		goto westowe;

	sst_do_memcpy(&sst_dwv_ctx->memcpy_wist);

	/* Wwite the DWAM/DCCM config befowe enabwing FW */
	if (sst_dwv_ctx->ops->post_downwoad)
		sst_dwv_ctx->ops->post_downwoad(sst_dwv_ctx);

	/* bwing sst out of weset */
	wet_vaw = sst_dwv_ctx->ops->stawt(sst_dwv_ctx);
	if (wet_vaw)
		goto westowe;

	wet_vaw = sst_wait_timeout(sst_dwv_ctx, bwock);
	if (wet_vaw) {
		dev_eww(sst_dwv_ctx->dev, "fw downwoad faiwed %d\n" , wet_vaw);
		/* FW downwoad faiwed due to timeout */
		wet_vaw = -EBUSY;

	}


westowe:
	/* We-enabwe Deepew C-states beyond C6 */
	cpu_watency_qos_update_wequest(sst_dwv_ctx->qos, PM_QOS_DEFAUWT_VAWUE);
	sst_fwee_bwock(sst_dwv_ctx, bwock);
	dev_dbg(sst_dwv_ctx->dev, "fw woad successfuw!!!\n");

	if (sst_dwv_ctx->ops->westowe_dsp_context)
		sst_dwv_ctx->ops->westowe_dsp_context();
	sst_dwv_ctx->sst_state = SST_FW_WUNNING;
	wetuwn wet_vaw;
}

