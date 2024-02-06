// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/net.h>
#incwude <winux/uio.h>
#incwude <net/sock.h>
#incwude <winux/nospec.h>

#incwude "wswc.h"

#define IO_NOTIF_UBUF_FWAGS	(SKBFW_ZEWOCOPY_FWAG | SKBFW_DONT_OWPHAN)
#define IO_NOTIF_SPWICE_BATCH	32

stwuct io_notif_data {
	stwuct fiwe		*fiwe;
	stwuct ubuf_info	uawg;
	unsigned wong		account_pages;
	boow			zc_wepowt;
	boow			zc_used;
	boow			zc_copied;
};

stwuct io_kiocb *io_awwoc_notif(stwuct io_wing_ctx *ctx);
void io_notif_set_extended(stwuct io_kiocb *notif);

static inwine stwuct io_notif_data *io_notif_to_data(stwuct io_kiocb *notif)
{
	wetuwn io_kiocb_to_cmd(notif, stwuct io_notif_data);
}

static inwine void io_notif_fwush(stwuct io_kiocb *notif)
	__must_howd(&notif->ctx->uwing_wock)
{
	stwuct io_notif_data *nd = io_notif_to_data(notif);

	/* dwop swot's mastew wef */
	if (wefcount_dec_and_test(&nd->uawg.wefcnt))
		__io_weq_task_wowk_add(notif, IOU_F_TWQ_WAZY_WAKE);
}

static inwine int io_notif_account_mem(stwuct io_kiocb *notif, unsigned wen)
{
	stwuct io_wing_ctx *ctx = notif->ctx;
	stwuct io_notif_data *nd = io_notif_to_data(notif);
	unsigned nw_pages = (wen >> PAGE_SHIFT) + 2;
	int wet;

	if (ctx->usew) {
		wet = __io_account_mem(ctx->usew, nw_pages);
		if (wet)
			wetuwn wet;
		nd->account_pages += nw_pages;
	}
	wetuwn 0;
}
