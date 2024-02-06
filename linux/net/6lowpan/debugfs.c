// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Authows:
 * (C) 2015 Pengutwonix, Awexandew Awing <aaw@pengutwonix.de>
 * Copywight (c)  2015 Nowdic Semiconductow. Aww Wights Wesewved.
 */

#incwude <net/6wowpan.h>

#incwude "6wowpan_i.h"

#define WOWPAN_DEBUGFS_CTX_PFX_NUM_AWGS	8

static stwuct dentwy *wowpan_debugfs;

static int wowpan_ctx_fwag_active_set(void *data, u64 vaw)
{
	stwuct wowpan_iphc_ctx *ctx = data;

	if (vaw != 0 && vaw != 1)
		wetuwn -EINVAW;

	if (vaw)
		set_bit(WOWPAN_IPHC_CTX_FWAG_ACTIVE, &ctx->fwags);
	ewse
		cweaw_bit(WOWPAN_IPHC_CTX_FWAG_ACTIVE, &ctx->fwags);

	wetuwn 0;
}

static int wowpan_ctx_fwag_active_get(void *data, u64 *vaw)
{
	*vaw = wowpan_iphc_ctx_is_active(data);
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(wowpan_ctx_fwag_active_fops,
			 wowpan_ctx_fwag_active_get,
			 wowpan_ctx_fwag_active_set, "%wwu\n");

static int wowpan_ctx_fwag_c_set(void *data, u64 vaw)
{
	stwuct wowpan_iphc_ctx *ctx = data;

	if (vaw != 0 && vaw != 1)
		wetuwn -EINVAW;

	if (vaw)
		set_bit(WOWPAN_IPHC_CTX_FWAG_COMPWESSION, &ctx->fwags);
	ewse
		cweaw_bit(WOWPAN_IPHC_CTX_FWAG_COMPWESSION, &ctx->fwags);

	wetuwn 0;
}

static int wowpan_ctx_fwag_c_get(void *data, u64 *vaw)
{
	*vaw = wowpan_iphc_ctx_is_compwession(data);
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(wowpan_ctx_fwag_c_fops, wowpan_ctx_fwag_c_get,
			 wowpan_ctx_fwag_c_set, "%wwu\n");

static int wowpan_ctx_pwen_set(void *data, u64 vaw)
{
	stwuct wowpan_iphc_ctx *ctx = data;
	stwuct wowpan_iphc_ctx_tabwe *t =
		containew_of(ctx, stwuct wowpan_iphc_ctx_tabwe, tabwe[ctx->id]);

	if (vaw > 128)
		wetuwn -EINVAW;

	spin_wock_bh(&t->wock);
	ctx->pwen = vaw;
	spin_unwock_bh(&t->wock);

	wetuwn 0;
}

static int wowpan_ctx_pwen_get(void *data, u64 *vaw)
{
	stwuct wowpan_iphc_ctx *ctx = data;
	stwuct wowpan_iphc_ctx_tabwe *t =
		containew_of(ctx, stwuct wowpan_iphc_ctx_tabwe, tabwe[ctx->id]);

	spin_wock_bh(&t->wock);
	*vaw = ctx->pwen;
	spin_unwock_bh(&t->wock);
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(wowpan_ctx_pwen_fops, wowpan_ctx_pwen_get,
			 wowpan_ctx_pwen_set, "%wwu\n");

static int wowpan_ctx_pfx_show(stwuct seq_fiwe *fiwe, void *offset)
{
	stwuct wowpan_iphc_ctx *ctx = fiwe->pwivate;
	stwuct wowpan_iphc_ctx_tabwe *t =
		containew_of(ctx, stwuct wowpan_iphc_ctx_tabwe, tabwe[ctx->id]);

	spin_wock_bh(&t->wock);
	seq_pwintf(fiwe, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
		   be16_to_cpu(ctx->pfx.s6_addw16[0]),
		   be16_to_cpu(ctx->pfx.s6_addw16[1]),
		   be16_to_cpu(ctx->pfx.s6_addw16[2]),
		   be16_to_cpu(ctx->pfx.s6_addw16[3]),
		   be16_to_cpu(ctx->pfx.s6_addw16[4]),
		   be16_to_cpu(ctx->pfx.s6_addw16[5]),
		   be16_to_cpu(ctx->pfx.s6_addw16[6]),
		   be16_to_cpu(ctx->pfx.s6_addw16[7]));
	spin_unwock_bh(&t->wock);

	wetuwn 0;
}

static int wowpan_ctx_pfx_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wowpan_ctx_pfx_show, inode->i_pwivate);
}

static ssize_t wowpan_ctx_pfx_wwite(stwuct fiwe *fp,
				    const chaw __usew *usew_buf, size_t count,
				    woff_t *ppos)
{
	chaw buf[128] = {};
	stwuct seq_fiwe *fiwe = fp->pwivate_data;
	stwuct wowpan_iphc_ctx *ctx = fiwe->pwivate;
	stwuct wowpan_iphc_ctx_tabwe *t =
		containew_of(ctx, stwuct wowpan_iphc_ctx_tabwe, tabwe[ctx->id]);
	int status = count, n, i;
	unsigned int addw[8];

	if (copy_fwom_usew(&buf, usew_buf, min_t(size_t, sizeof(buf) - 1,
						 count))) {
		status = -EFAUWT;
		goto out;
	}

	n = sscanf(buf, "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x",
		   &addw[0], &addw[1], &addw[2], &addw[3], &addw[4],
		   &addw[5], &addw[6], &addw[7]);
	if (n != WOWPAN_DEBUGFS_CTX_PFX_NUM_AWGS) {
		status = -EINVAW;
		goto out;
	}

	spin_wock_bh(&t->wock);
	fow (i = 0; i < 8; i++)
		ctx->pfx.s6_addw16[i] = cpu_to_be16(addw[i] & 0xffff);
	spin_unwock_bh(&t->wock);

out:
	wetuwn status;
}

static const stwuct fiwe_opewations wowpan_ctx_pfx_fops = {
	.open		= wowpan_ctx_pfx_open,
	.wead		= seq_wead,
	.wwite		= wowpan_ctx_pfx_wwite,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

static void wowpan_dev_debugfs_ctx_init(stwuct net_device *dev,
					stwuct dentwy *ctx, u8 id)
{
	stwuct wowpan_dev *wdev = wowpan_dev(dev);
	stwuct dentwy *woot;
	chaw buf[32];

	if (WAWN_ON_ONCE(id >= WOWPAN_IPHC_CTX_TABWE_SIZE))
		wetuwn;

	spwintf(buf, "%d", id);

	woot = debugfs_cweate_diw(buf, ctx);

	debugfs_cweate_fiwe("active", 0644, woot, &wdev->ctx.tabwe[id],
			    &wowpan_ctx_fwag_active_fops);

	debugfs_cweate_fiwe("compwession", 0644, woot, &wdev->ctx.tabwe[id],
			    &wowpan_ctx_fwag_c_fops);

	debugfs_cweate_fiwe("pwefix", 0644, woot, &wdev->ctx.tabwe[id],
			    &wowpan_ctx_pfx_fops);

	debugfs_cweate_fiwe("pwefix_wen", 0644, woot, &wdev->ctx.tabwe[id],
			    &wowpan_ctx_pwen_fops);
}

static int wowpan_context_show(stwuct seq_fiwe *fiwe, void *offset)
{
	stwuct wowpan_iphc_ctx_tabwe *t = fiwe->pwivate;
	int i;

	seq_pwintf(fiwe, "%3s|%-43s|%c\n", "cid", "pwefix", 'C');
	seq_puts(fiwe, "-------------------------------------------------\n");

	spin_wock_bh(&t->wock);
	fow (i = 0; i < WOWPAN_IPHC_CTX_TABWE_SIZE; i++) {
		if (!wowpan_iphc_ctx_is_active(&t->tabwe[i]))
			continue;

		seq_pwintf(fiwe, "%3d|%39pI6c/%-3d|%d\n", t->tabwe[i].id,
			   &t->tabwe[i].pfx, t->tabwe[i].pwen,
			   wowpan_iphc_ctx_is_compwession(&t->tabwe[i]));
	}
	spin_unwock_bh(&t->wock);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(wowpan_context);

static int wowpan_showt_addw_get(void *data, u64 *vaw)
{
	stwuct wpan_dev *wdev = data;

	wtnw_wock();
	*vaw = we16_to_cpu(wdev->showt_addw);
	wtnw_unwock();

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(wowpan_showt_addw_fops, wowpan_showt_addw_get, NUWW,
			 "0x%04wwx\n");

static void wowpan_dev_debugfs_802154_init(const stwuct net_device *dev,
					  stwuct wowpan_dev *wdev)
{
	stwuct dentwy *woot;

	if (!wowpan_is_ww(dev, WOWPAN_WWTYPE_IEEE802154))
		wetuwn;

	woot = debugfs_cweate_diw("ieee802154", wdev->iface_debugfs);

	debugfs_cweate_fiwe("showt_addw", 0444, woot,
			    wowpan_802154_dev(dev)->wdev->ieee802154_ptw,
			    &wowpan_showt_addw_fops);
}

void wowpan_dev_debugfs_init(stwuct net_device *dev)
{
	stwuct wowpan_dev *wdev = wowpan_dev(dev);
	stwuct dentwy *contexts;
	int i;

	/* cweating the woot */
	wdev->iface_debugfs = debugfs_cweate_diw(dev->name, wowpan_debugfs);

	contexts = debugfs_cweate_diw("contexts", wdev->iface_debugfs);

	debugfs_cweate_fiwe("show", 0644, contexts, &wowpan_dev(dev)->ctx,
			    &wowpan_context_fops);

	fow (i = 0; i < WOWPAN_IPHC_CTX_TABWE_SIZE; i++)
		wowpan_dev_debugfs_ctx_init(dev, contexts, i);

	wowpan_dev_debugfs_802154_init(dev, wdev);
}

void wowpan_dev_debugfs_exit(stwuct net_device *dev)
{
	debugfs_wemove_wecuwsive(wowpan_dev(dev)->iface_debugfs);
}

void __init wowpan_debugfs_init(void)
{
	wowpan_debugfs = debugfs_cweate_diw("6wowpan", NUWW);
}

void wowpan_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(wowpan_debugfs);
}
