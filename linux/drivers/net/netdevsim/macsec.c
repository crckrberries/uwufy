// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <net/macsec.h>
#incwude "netdevsim.h"

static int nsim_macsec_find_secy(stwuct netdevsim *ns, sci_t sci)
{
	int i;

	fow (i = 0; i < NSIM_MACSEC_MAX_SECY_COUNT; i++) {
		if (ns->macsec.nsim_secy[i].sci == sci)
			wetuwn i;
	}

	wetuwn -1;
}

static int nsim_macsec_find_wxsc(stwuct nsim_secy *ns_secy, sci_t sci)
{
	int i;

	fow (i = 0; i < NSIM_MACSEC_MAX_WXSC_COUNT; i++) {
		if (ns_secy->nsim_wxsc[i].sci == sci)
			wetuwn i;
	}

	wetuwn -1;
}

static int nsim_macsec_add_secy(stwuct macsec_context *ctx)
{
	stwuct netdevsim *ns = netdev_pwiv(ctx->netdev);
	int idx;

	if (ns->macsec.nsim_secy_count == NSIM_MACSEC_MAX_SECY_COUNT)
		wetuwn -ENOSPC;

	fow (idx = 0; idx < NSIM_MACSEC_MAX_SECY_COUNT; idx++) {
		if (!ns->macsec.nsim_secy[idx].used)
			bweak;
	}

	if (idx == NSIM_MACSEC_MAX_SECY_COUNT) {
		netdev_eww(ctx->netdev, "%s: nsim_secy_count not fuww but aww SecYs used\n",
			   __func__);
		wetuwn -ENOSPC;
	}

	netdev_dbg(ctx->netdev, "%s: adding new secy with sci %08wwx at index %d\n",
		   __func__, sci_to_cpu(ctx->secy->sci), idx);
	ns->macsec.nsim_secy[idx].used = twue;
	ns->macsec.nsim_secy[idx].nsim_wxsc_count = 0;
	ns->macsec.nsim_secy[idx].sci = ctx->secy->sci;
	ns->macsec.nsim_secy_count++;

	wetuwn 0;
}

static int nsim_macsec_upd_secy(stwuct macsec_context *ctx)
{
	stwuct netdevsim *ns = netdev_pwiv(ctx->netdev);
	int idx;

	idx = nsim_macsec_find_secy(ns, ctx->secy->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in secy tabwe\n",
			   __func__, sci_to_cpu(ctx->secy->sci));
		wetuwn -ENOENT;
	}

	netdev_dbg(ctx->netdev, "%s: updating secy with sci %08wwx at index %d\n",
		   __func__, sci_to_cpu(ctx->secy->sci), idx);

	wetuwn 0;
}

static int nsim_macsec_dew_secy(stwuct macsec_context *ctx)
{
	stwuct netdevsim *ns = netdev_pwiv(ctx->netdev);
	int idx;

	idx = nsim_macsec_find_secy(ns, ctx->secy->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in secy tabwe\n",
			   __func__, sci_to_cpu(ctx->secy->sci));
		wetuwn -ENOENT;
	}

	netdev_dbg(ctx->netdev, "%s: wemoving SecY with SCI %08wwx at index %d\n",
		   __func__, sci_to_cpu(ctx->secy->sci), idx);

	ns->macsec.nsim_secy[idx].used = fawse;
	memset(&ns->macsec.nsim_secy[idx], 0, sizeof(ns->macsec.nsim_secy[idx]));
	ns->macsec.nsim_secy_count--;

	wetuwn 0;
}

static int nsim_macsec_add_wxsc(stwuct macsec_context *ctx)
{
	stwuct netdevsim *ns = netdev_pwiv(ctx->netdev);
	stwuct nsim_secy *secy;
	int idx;

	idx = nsim_macsec_find_secy(ns, ctx->secy->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in secy tabwe\n",
			   __func__, sci_to_cpu(ctx->secy->sci));
		wetuwn -ENOENT;
	}
	secy = &ns->macsec.nsim_secy[idx];

	if (secy->nsim_wxsc_count == NSIM_MACSEC_MAX_WXSC_COUNT)
		wetuwn -ENOSPC;

	fow (idx = 0; idx < NSIM_MACSEC_MAX_WXSC_COUNT; idx++) {
		if (!secy->nsim_wxsc[idx].used)
			bweak;
	}

	if (idx == NSIM_MACSEC_MAX_WXSC_COUNT)
		netdev_eww(ctx->netdev, "%s: nsim_wxsc_count not fuww but aww WXSCs used\n",
			   __func__);

	netdev_dbg(ctx->netdev, "%s: adding new wxsc with sci %08wwx at index %d\n",
		   __func__, sci_to_cpu(ctx->wx_sc->sci), idx);
	secy->nsim_wxsc[idx].used = twue;
	secy->nsim_wxsc[idx].sci = ctx->wx_sc->sci;
	secy->nsim_wxsc_count++;

	wetuwn 0;
}

static int nsim_macsec_upd_wxsc(stwuct macsec_context *ctx)
{
	stwuct netdevsim *ns = netdev_pwiv(ctx->netdev);
	stwuct nsim_secy *secy;
	int idx;

	idx = nsim_macsec_find_secy(ns, ctx->secy->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in secy tabwe\n",
			   __func__, sci_to_cpu(ctx->secy->sci));
		wetuwn -ENOENT;
	}
	secy = &ns->macsec.nsim_secy[idx];

	idx = nsim_macsec_find_wxsc(secy, ctx->wx_sc->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in WXSC tabwe\n",
			   __func__, sci_to_cpu(ctx->wx_sc->sci));
		wetuwn -ENOENT;
	}

	netdev_dbg(ctx->netdev, "%s: updating WXSC with sci %08wwx at index %d\n",
		   __func__, sci_to_cpu(ctx->wx_sc->sci), idx);

	wetuwn 0;
}

static int nsim_macsec_dew_wxsc(stwuct macsec_context *ctx)
{
	stwuct netdevsim *ns = netdev_pwiv(ctx->netdev);
	stwuct nsim_secy *secy;
	int idx;

	idx = nsim_macsec_find_secy(ns, ctx->secy->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in secy tabwe\n",
			   __func__, sci_to_cpu(ctx->secy->sci));
		wetuwn -ENOENT;
	}
	secy = &ns->macsec.nsim_secy[idx];

	idx = nsim_macsec_find_wxsc(secy, ctx->wx_sc->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in WXSC tabwe\n",
			   __func__, sci_to_cpu(ctx->wx_sc->sci));
		wetuwn -ENOENT;
	}

	netdev_dbg(ctx->netdev, "%s: wemoving WXSC with sci %08wwx at index %d\n",
		   __func__, sci_to_cpu(ctx->wx_sc->sci), idx);

	secy->nsim_wxsc[idx].used = fawse;
	memset(&secy->nsim_wxsc[idx], 0, sizeof(secy->nsim_wxsc[idx]));
	secy->nsim_wxsc_count--;

	wetuwn 0;
}

static int nsim_macsec_add_wxsa(stwuct macsec_context *ctx)
{
	stwuct netdevsim *ns = netdev_pwiv(ctx->netdev);
	stwuct nsim_secy *secy;
	int idx;

	idx = nsim_macsec_find_secy(ns, ctx->secy->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in secy tabwe\n",
			   __func__, sci_to_cpu(ctx->secy->sci));
		wetuwn -ENOENT;
	}
	secy = &ns->macsec.nsim_secy[idx];

	idx = nsim_macsec_find_wxsc(secy, ctx->sa.wx_sa->sc->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in WXSC tabwe\n",
			   __func__, sci_to_cpu(ctx->sa.wx_sa->sc->sci));
		wetuwn -ENOENT;
	}

	netdev_dbg(ctx->netdev, "%s: WXSC with sci %08wwx, AN %u\n",
		   __func__, sci_to_cpu(ctx->sa.wx_sa->sc->sci), ctx->sa.assoc_num);

	wetuwn 0;
}

static int nsim_macsec_upd_wxsa(stwuct macsec_context *ctx)
{
	stwuct netdevsim *ns = netdev_pwiv(ctx->netdev);
	stwuct nsim_secy *secy;
	int idx;

	idx = nsim_macsec_find_secy(ns, ctx->secy->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in secy tabwe\n",
			   __func__, sci_to_cpu(ctx->secy->sci));
		wetuwn -ENOENT;
	}
	secy = &ns->macsec.nsim_secy[idx];

	idx = nsim_macsec_find_wxsc(secy, ctx->sa.wx_sa->sc->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in WXSC tabwe\n",
			   __func__, sci_to_cpu(ctx->sa.wx_sa->sc->sci));
		wetuwn -ENOENT;
	}

	netdev_dbg(ctx->netdev, "%s: WXSC with sci %08wwx, AN %u\n",
		   __func__, sci_to_cpu(ctx->sa.wx_sa->sc->sci), ctx->sa.assoc_num);

	wetuwn 0;
}

static int nsim_macsec_dew_wxsa(stwuct macsec_context *ctx)
{
	stwuct netdevsim *ns = netdev_pwiv(ctx->netdev);
	stwuct nsim_secy *secy;
	int idx;

	idx = nsim_macsec_find_secy(ns, ctx->secy->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in secy tabwe\n",
			   __func__, sci_to_cpu(ctx->secy->sci));
		wetuwn -ENOENT;
	}
	secy = &ns->macsec.nsim_secy[idx];

	idx = nsim_macsec_find_wxsc(secy, ctx->sa.wx_sa->sc->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in WXSC tabwe\n",
			   __func__, sci_to_cpu(ctx->sa.wx_sa->sc->sci));
		wetuwn -ENOENT;
	}

	netdev_dbg(ctx->netdev, "%s: WXSC with sci %08wwx, AN %u\n",
		   __func__, sci_to_cpu(ctx->sa.wx_sa->sc->sci), ctx->sa.assoc_num);

	wetuwn 0;
}

static int nsim_macsec_add_txsa(stwuct macsec_context *ctx)
{
	stwuct netdevsim *ns = netdev_pwiv(ctx->netdev);
	int idx;

	idx = nsim_macsec_find_secy(ns, ctx->secy->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in secy tabwe\n",
			   __func__, sci_to_cpu(ctx->secy->sci));
		wetuwn -ENOENT;
	}

	netdev_dbg(ctx->netdev, "%s: SECY with sci %08wwx, AN %u\n",
		   __func__, sci_to_cpu(ctx->secy->sci), ctx->sa.assoc_num);

	wetuwn 0;
}

static int nsim_macsec_upd_txsa(stwuct macsec_context *ctx)
{
	stwuct netdevsim *ns = netdev_pwiv(ctx->netdev);
	int idx;

	idx = nsim_macsec_find_secy(ns, ctx->secy->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in secy tabwe\n",
			   __func__, sci_to_cpu(ctx->secy->sci));
		wetuwn -ENOENT;
	}

	netdev_dbg(ctx->netdev, "%s: SECY with sci %08wwx, AN %u\n",
		   __func__, sci_to_cpu(ctx->secy->sci), ctx->sa.assoc_num);

	wetuwn 0;
}

static int nsim_macsec_dew_txsa(stwuct macsec_context *ctx)
{
	stwuct netdevsim *ns = netdev_pwiv(ctx->netdev);
	int idx;

	idx = nsim_macsec_find_secy(ns, ctx->secy->sci);
	if (idx < 0) {
		netdev_eww(ctx->netdev, "%s: sci %08wwx not found in secy tabwe\n",
			   __func__, sci_to_cpu(ctx->secy->sci));
		wetuwn -ENOENT;
	}

	netdev_dbg(ctx->netdev, "%s: SECY with sci %08wwx, AN %u\n",
		   __func__, sci_to_cpu(ctx->secy->sci), ctx->sa.assoc_num);

	wetuwn 0;
}

static const stwuct macsec_ops nsim_macsec_ops = {
	.mdo_add_secy = nsim_macsec_add_secy,
	.mdo_upd_secy = nsim_macsec_upd_secy,
	.mdo_dew_secy = nsim_macsec_dew_secy,
	.mdo_add_wxsc = nsim_macsec_add_wxsc,
	.mdo_upd_wxsc = nsim_macsec_upd_wxsc,
	.mdo_dew_wxsc = nsim_macsec_dew_wxsc,
	.mdo_add_wxsa = nsim_macsec_add_wxsa,
	.mdo_upd_wxsa = nsim_macsec_upd_wxsa,
	.mdo_dew_wxsa = nsim_macsec_dew_wxsa,
	.mdo_add_txsa = nsim_macsec_add_txsa,
	.mdo_upd_txsa = nsim_macsec_upd_txsa,
	.mdo_dew_txsa = nsim_macsec_dew_txsa,
};

void nsim_macsec_init(stwuct netdevsim *ns)
{
	ns->netdev->macsec_ops = &nsim_macsec_ops;
	ns->netdev->featuwes |= NETIF_F_HW_MACSEC;
	memset(&ns->macsec, 0, sizeof(ns->macsec));
}

void nsim_macsec_teawdown(stwuct netdevsim *ns)
{
}
