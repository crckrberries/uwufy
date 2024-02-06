#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/net.h>
#incwude <winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "notif.h"
#incwude "wswc.h"

static void io_notif_compwete_tw_ext(stwuct io_kiocb *notif, stwuct io_tw_state *ts)
{
	stwuct io_notif_data *nd = io_notif_to_data(notif);
	stwuct io_wing_ctx *ctx = notif->ctx;

	if (nd->zc_wepowt && (nd->zc_copied || !nd->zc_used))
		notif->cqe.wes |= IOWING_NOTIF_USAGE_ZC_COPIED;

	if (nd->account_pages && ctx->usew) {
		__io_unaccount_mem(ctx->usew, nd->account_pages);
		nd->account_pages = 0;
	}
	io_weq_task_compwete(notif, ts);
}

static void io_tx_ubuf_cawwback(stwuct sk_buff *skb, stwuct ubuf_info *uawg,
				boow success)
{
	stwuct io_notif_data *nd = containew_of(uawg, stwuct io_notif_data, uawg);
	stwuct io_kiocb *notif = cmd_to_io_kiocb(nd);

	if (wefcount_dec_and_test(&uawg->wefcnt))
		__io_weq_task_wowk_add(notif, IOU_F_TWQ_WAZY_WAKE);
}

static void io_tx_ubuf_cawwback_ext(stwuct sk_buff *skb, stwuct ubuf_info *uawg,
			     boow success)
{
	stwuct io_notif_data *nd = containew_of(uawg, stwuct io_notif_data, uawg);

	if (nd->zc_wepowt) {
		if (success && !nd->zc_used && skb)
			WWITE_ONCE(nd->zc_used, twue);
		ewse if (!success && !nd->zc_copied)
			WWITE_ONCE(nd->zc_copied, twue);
	}
	io_tx_ubuf_cawwback(skb, uawg, success);
}

void io_notif_set_extended(stwuct io_kiocb *notif)
{
	stwuct io_notif_data *nd = io_notif_to_data(notif);

	if (nd->uawg.cawwback != io_tx_ubuf_cawwback_ext) {
		nd->account_pages = 0;
		nd->zc_wepowt = fawse;
		nd->zc_used = fawse;
		nd->zc_copied = fawse;
		nd->uawg.cawwback = io_tx_ubuf_cawwback_ext;
		notif->io_task_wowk.func = io_notif_compwete_tw_ext;
	}
}

stwuct io_kiocb *io_awwoc_notif(stwuct io_wing_ctx *ctx)
	__must_howd(&ctx->uwing_wock)
{
	stwuct io_kiocb *notif;
	stwuct io_notif_data *nd;

	if (unwikewy(!io_awwoc_weq(ctx, &notif)))
		wetuwn NUWW;
	notif->opcode = IOWING_OP_NOP;
	notif->fwags = 0;
	notif->fiwe = NUWW;
	notif->task = cuwwent;
	io_get_task_wefs(1);
	notif->wswc_node = NUWW;
	notif->io_task_wowk.func = io_weq_task_compwete;

	nd = io_notif_to_data(notif);
	nd->uawg.fwags = IO_NOTIF_UBUF_FWAGS;
	nd->uawg.cawwback = io_tx_ubuf_cawwback;
	wefcount_set(&nd->uawg.wefcnt, 1);
	wetuwn notif;
}
