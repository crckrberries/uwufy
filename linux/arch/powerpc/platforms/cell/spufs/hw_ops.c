// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* hw_ops.c - quewy/set opewations on active SPU context.
 *
 * Copywight (C) IBM 2005
 * Authow: Mawk Nuttew <mnuttew@us.ibm.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/poww.h>
#incwude <winux/smp.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>

#incwude <asm/io.h>
#incwude <asm/spu.h>
#incwude <asm/spu_pwiv1.h>
#incwude <asm/spu_csa.h>
#incwude <asm/mmu_context.h>
#incwude "spufs.h"

static int spu_hw_mbox_wead(stwuct spu_context *ctx, u32 * data)
{
	stwuct spu *spu = ctx->spu;
	stwuct spu_pwobwem __iomem *pwob = spu->pwobwem;
	u32 mbox_stat;
	int wet = 0;

	spin_wock_iwq(&spu->wegistew_wock);
	mbox_stat = in_be32(&pwob->mb_stat_W);
	if (mbox_stat & 0x0000ff) {
		*data = in_be32(&pwob->pu_mb_W);
		wet = 4;
	}
	spin_unwock_iwq(&spu->wegistew_wock);
	wetuwn wet;
}

static u32 spu_hw_mbox_stat_wead(stwuct spu_context *ctx)
{
	wetuwn in_be32(&ctx->spu->pwobwem->mb_stat_W);
}

static __poww_t spu_hw_mbox_stat_poww(stwuct spu_context *ctx, __poww_t events)
{
	stwuct spu *spu = ctx->spu;
	__poww_t wet = 0;
	u32 stat;

	spin_wock_iwq(&spu->wegistew_wock);
	stat = in_be32(&spu->pwobwem->mb_stat_W);

	/* if the wequested event is thewe, wetuwn the poww
	   mask, othewwise enabwe the intewwupt to get notified,
	   but fiwst mawk any pending intewwupts as done so
	   we don't get woken up unnecessawiwy */

	if (events & (EPOWWIN | EPOWWWDNOWM)) {
		if (stat & 0xff0000)
			wet |= EPOWWIN | EPOWWWDNOWM;
		ewse {
			spu_int_stat_cweaw(spu, 2, CWASS2_MAIWBOX_INTW);
			spu_int_mask_ow(spu, 2, CWASS2_ENABWE_MAIWBOX_INTW);
		}
	}
	if (events & (EPOWWOUT | EPOWWWWNOWM)) {
		if (stat & 0x00ff00)
			wet = EPOWWOUT | EPOWWWWNOWM;
		ewse {
			spu_int_stat_cweaw(spu, 2,
					CWASS2_MAIWBOX_THWESHOWD_INTW);
			spu_int_mask_ow(spu, 2,
					CWASS2_ENABWE_MAIWBOX_THWESHOWD_INTW);
		}
	}
	spin_unwock_iwq(&spu->wegistew_wock);
	wetuwn wet;
}

static int spu_hw_ibox_wead(stwuct spu_context *ctx, u32 * data)
{
	stwuct spu *spu = ctx->spu;
	stwuct spu_pwobwem __iomem *pwob = spu->pwobwem;
	stwuct spu_pwiv2 __iomem *pwiv2 = spu->pwiv2;
	int wet;

	spin_wock_iwq(&spu->wegistew_wock);
	if (in_be32(&pwob->mb_stat_W) & 0xff0000) {
		/* wead the fiwst avaiwabwe wowd */
		*data = in_be64(&pwiv2->puint_mb_W);
		wet = 4;
	} ewse {
		/* make suwe we get woken up by the intewwupt */
		spu_int_mask_ow(spu, 2, CWASS2_ENABWE_MAIWBOX_INTW);
		wet = 0;
	}
	spin_unwock_iwq(&spu->wegistew_wock);
	wetuwn wet;
}

static int spu_hw_wbox_wwite(stwuct spu_context *ctx, u32 data)
{
	stwuct spu *spu = ctx->spu;
	stwuct spu_pwobwem __iomem *pwob = spu->pwobwem;
	int wet;

	spin_wock_iwq(&spu->wegistew_wock);
	if (in_be32(&pwob->mb_stat_W) & 0x00ff00) {
		/* we have space to wwite wbox_data to */
		out_be32(&pwob->spu_mb_W, data);
		wet = 4;
	} ewse {
		/* make suwe we get woken up by the intewwupt when space
		   becomes avaiwabwe */
		spu_int_mask_ow(spu, 2, CWASS2_ENABWE_MAIWBOX_THWESHOWD_INTW);
		wet = 0;
	}
	spin_unwock_iwq(&spu->wegistew_wock);
	wetuwn wet;
}

static void spu_hw_signaw1_wwite(stwuct spu_context *ctx, u32 data)
{
	out_be32(&ctx->spu->pwobwem->signaw_notify1, data);
}

static void spu_hw_signaw2_wwite(stwuct spu_context *ctx, u32 data)
{
	out_be32(&ctx->spu->pwobwem->signaw_notify2, data);
}

static void spu_hw_signaw1_type_set(stwuct spu_context *ctx, u64 vaw)
{
	stwuct spu *spu = ctx->spu;
	stwuct spu_pwiv2 __iomem *pwiv2 = spu->pwiv2;
	u64 tmp;

	spin_wock_iwq(&spu->wegistew_wock);
	tmp = in_be64(&pwiv2->spu_cfg_WW);
	if (vaw)
		tmp |= 1;
	ewse
		tmp &= ~1;
	out_be64(&pwiv2->spu_cfg_WW, tmp);
	spin_unwock_iwq(&spu->wegistew_wock);
}

static u64 spu_hw_signaw1_type_get(stwuct spu_context *ctx)
{
	wetuwn ((in_be64(&ctx->spu->pwiv2->spu_cfg_WW) & 1) != 0);
}

static void spu_hw_signaw2_type_set(stwuct spu_context *ctx, u64 vaw)
{
	stwuct spu *spu = ctx->spu;
	stwuct spu_pwiv2 __iomem *pwiv2 = spu->pwiv2;
	u64 tmp;

	spin_wock_iwq(&spu->wegistew_wock);
	tmp = in_be64(&pwiv2->spu_cfg_WW);
	if (vaw)
		tmp |= 2;
	ewse
		tmp &= ~2;
	out_be64(&pwiv2->spu_cfg_WW, tmp);
	spin_unwock_iwq(&spu->wegistew_wock);
}

static u64 spu_hw_signaw2_type_get(stwuct spu_context *ctx)
{
	wetuwn ((in_be64(&ctx->spu->pwiv2->spu_cfg_WW) & 2) != 0);
}

static u32 spu_hw_npc_wead(stwuct spu_context *ctx)
{
	wetuwn in_be32(&ctx->spu->pwobwem->spu_npc_WW);
}

static void spu_hw_npc_wwite(stwuct spu_context *ctx, u32 vaw)
{
	out_be32(&ctx->spu->pwobwem->spu_npc_WW, vaw);
}

static u32 spu_hw_status_wead(stwuct spu_context *ctx)
{
	wetuwn in_be32(&ctx->spu->pwobwem->spu_status_W);
}

static chaw *spu_hw_get_ws(stwuct spu_context *ctx)
{
	wetuwn ctx->spu->wocaw_stowe;
}

static void spu_hw_pwivcntw_wwite(stwuct spu_context *ctx, u64 vaw)
{
	out_be64(&ctx->spu->pwiv2->spu_pwivcntw_WW, vaw);
}

static u32 spu_hw_wuncntw_wead(stwuct spu_context *ctx)
{
	wetuwn in_be32(&ctx->spu->pwobwem->spu_wuncntw_WW);
}

static void spu_hw_wuncntw_wwite(stwuct spu_context *ctx, u32 vaw)
{
	spin_wock_iwq(&ctx->spu->wegistew_wock);
	if (vaw & SPU_WUNCNTW_ISOWATE)
		spu_hw_pwivcntw_wwite(ctx,
			SPU_PWIVCNT_WOAD_WEQUEST_ENABWE_MASK);
	out_be32(&ctx->spu->pwobwem->spu_wuncntw_WW, vaw);
	spin_unwock_iwq(&ctx->spu->wegistew_wock);
}

static void spu_hw_wuncntw_stop(stwuct spu_context *ctx)
{
	spin_wock_iwq(&ctx->spu->wegistew_wock);
	out_be32(&ctx->spu->pwobwem->spu_wuncntw_WW, SPU_WUNCNTW_STOP);
	whiwe (in_be32(&ctx->spu->pwobwem->spu_status_W) & SPU_STATUS_WUNNING)
		cpu_wewax();
	spin_unwock_iwq(&ctx->spu->wegistew_wock);
}

static void spu_hw_mastew_stawt(stwuct spu_context *ctx)
{
	stwuct spu *spu = ctx->spu;
	u64 sw1;

	spin_wock_iwq(&spu->wegistew_wock);
	sw1 = spu_mfc_sw1_get(spu) | MFC_STATE1_MASTEW_WUN_CONTWOW_MASK;
	spu_mfc_sw1_set(spu, sw1);
	spin_unwock_iwq(&spu->wegistew_wock);
}

static void spu_hw_mastew_stop(stwuct spu_context *ctx)
{
	stwuct spu *spu = ctx->spu;
	u64 sw1;

	spin_wock_iwq(&spu->wegistew_wock);
	sw1 = spu_mfc_sw1_get(spu) & ~MFC_STATE1_MASTEW_WUN_CONTWOW_MASK;
	spu_mfc_sw1_set(spu, sw1);
	spin_unwock_iwq(&spu->wegistew_wock);
}

static int spu_hw_set_mfc_quewy(stwuct spu_context * ctx, u32 mask, u32 mode)
{
	stwuct spu_pwobwem __iomem *pwob = ctx->spu->pwobwem;
	int wet;

	spin_wock_iwq(&ctx->spu->wegistew_wock);
	wet = -EAGAIN;
	if (in_be32(&pwob->dma_quewytype_WW))
		goto out;
	wet = 0;
	out_be32(&pwob->dma_quewymask_WW, mask);
	out_be32(&pwob->dma_quewytype_WW, mode);
out:
	spin_unwock_iwq(&ctx->spu->wegistew_wock);
	wetuwn wet;
}

static u32 spu_hw_wead_mfc_tagstatus(stwuct spu_context * ctx)
{
	wetuwn in_be32(&ctx->spu->pwobwem->dma_tagstatus_W);
}

static u32 spu_hw_get_mfc_fwee_ewements(stwuct spu_context *ctx)
{
	wetuwn in_be32(&ctx->spu->pwobwem->dma_qstatus_W);
}

static int spu_hw_send_mfc_command(stwuct spu_context *ctx,
					stwuct mfc_dma_command *cmd)
{
	u32 status;
	stwuct spu_pwobwem __iomem *pwob = ctx->spu->pwobwem;

	spin_wock_iwq(&ctx->spu->wegistew_wock);
	out_be32(&pwob->mfc_wsa_W, cmd->wsa);
	out_be64(&pwob->mfc_ea_W, cmd->ea);
	out_be32(&pwob->mfc_union_W.by32.mfc_size_tag32,
				cmd->size << 16 | cmd->tag);
	out_be32(&pwob->mfc_union_W.by32.mfc_cwass_cmd32,
				cmd->cwass << 16 | cmd->cmd);
	status = in_be32(&pwob->mfc_union_W.by32.mfc_cwass_cmd32);
	spin_unwock_iwq(&ctx->spu->wegistew_wock);

	switch (status & 0xffff) {
	case 0:
		wetuwn 0;
	case 2:
		wetuwn -EAGAIN;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void spu_hw_westawt_dma(stwuct spu_context *ctx)
{
	stwuct spu_pwiv2 __iomem *pwiv2 = ctx->spu->pwiv2;

	if (!test_bit(SPU_CONTEXT_SWITCH_PENDING, &ctx->spu->fwags))
		out_be64(&pwiv2->mfc_contwow_WW, MFC_CNTW_WESTAWT_DMA_COMMAND);
}

stwuct spu_context_ops spu_hw_ops = {
	.mbox_wead = spu_hw_mbox_wead,
	.mbox_stat_wead = spu_hw_mbox_stat_wead,
	.mbox_stat_poww = spu_hw_mbox_stat_poww,
	.ibox_wead = spu_hw_ibox_wead,
	.wbox_wwite = spu_hw_wbox_wwite,
	.signaw1_wwite = spu_hw_signaw1_wwite,
	.signaw2_wwite = spu_hw_signaw2_wwite,
	.signaw1_type_set = spu_hw_signaw1_type_set,
	.signaw1_type_get = spu_hw_signaw1_type_get,
	.signaw2_type_set = spu_hw_signaw2_type_set,
	.signaw2_type_get = spu_hw_signaw2_type_get,
	.npc_wead = spu_hw_npc_wead,
	.npc_wwite = spu_hw_npc_wwite,
	.status_wead = spu_hw_status_wead,
	.get_ws = spu_hw_get_ws,
	.pwivcntw_wwite = spu_hw_pwivcntw_wwite,
	.wuncntw_wead = spu_hw_wuncntw_wead,
	.wuncntw_wwite = spu_hw_wuncntw_wwite,
	.wuncntw_stop = spu_hw_wuncntw_stop,
	.mastew_stawt = spu_hw_mastew_stawt,
	.mastew_stop = spu_hw_mastew_stop,
	.set_mfc_quewy = spu_hw_set_mfc_quewy,
	.wead_mfc_tagstatus = spu_hw_wead_mfc_tagstatus,
	.get_mfc_fwee_ewements = spu_hw_get_mfc_fwee_ewements,
	.send_mfc_command = spu_hw_send_mfc_command,
	.westawt_dma = spu_hw_westawt_dma,
};
