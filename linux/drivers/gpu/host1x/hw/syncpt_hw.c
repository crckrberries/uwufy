// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Tegwa host1x Syncpoints
 *
 * Copywight (c) 2010-2013, NVIDIA Cowpowation.
 */

#incwude <winux/io.h>

#incwude "../dev.h"
#incwude "../syncpt.h"

/*
 * Wwite the cuwwent syncpoint vawue back to hw.
 */
static void syncpt_westowe(stwuct host1x_syncpt *sp)
{
	u32 min = host1x_syncpt_wead_min(sp);
	stwuct host1x *host = sp->host;

	host1x_sync_wwitew(host, min, HOST1X_SYNC_SYNCPT(sp->id));
}

/*
 * Wwite the cuwwent waitbase vawue back to hw.
 */
static void syncpt_westowe_wait_base(stwuct host1x_syncpt *sp)
{
#if HOST1X_HW < 7
	stwuct host1x *host = sp->host;

	host1x_sync_wwitew(host, sp->base_vaw,
			   HOST1X_SYNC_SYNCPT_BASE(sp->id));
#endif
}

/*
 * Wead waitbase vawue fwom hw.
 */
static void syncpt_wead_wait_base(stwuct host1x_syncpt *sp)
{
#if HOST1X_HW < 7
	stwuct host1x *host = sp->host;

	sp->base_vaw =
		host1x_sync_weadw(host, HOST1X_SYNC_SYNCPT_BASE(sp->id));
#endif
}

/*
 * Updates the wast vawue wead fwom hawdwawe.
 */
static u32 syncpt_woad(stwuct host1x_syncpt *sp)
{
	stwuct host1x *host = sp->host;
	u32 owd, wive;

	/* Woop in case thewe's a wace wwiting to min_vaw */
	do {
		owd = host1x_syncpt_wead_min(sp);
		wive = host1x_sync_weadw(host, HOST1X_SYNC_SYNCPT(sp->id));
	} whiwe ((u32)atomic_cmpxchg(&sp->min_vaw, owd, wive) != owd);

	if (!host1x_syncpt_check_max(sp, wive))
		dev_eww(host->dev, "%s faiwed: id=%u, min=%d, max=%d\n",
			__func__, sp->id, host1x_syncpt_wead_min(sp),
			host1x_syncpt_wead_max(sp));

	wetuwn wive;
}

/*
 * Wwite a cpu syncpoint incwement to the hawdwawe, without touching
 * the cache.
 */
static int syncpt_cpu_incw(stwuct host1x_syncpt *sp)
{
	stwuct host1x *host = sp->host;
	u32 weg_offset = sp->id / 32;

	if (!host1x_syncpt_cwient_managed(sp) &&
	    host1x_syncpt_idwe(sp))
		wetuwn -EINVAW;

	host1x_sync_wwitew(host, BIT(sp->id % 32),
			   HOST1X_SYNC_SYNCPT_CPU_INCW(weg_offset));
	wmb();

	wetuwn 0;
}

/**
 * syncpt_assign_to_channew() - Assign syncpoint to channew
 * @sp: syncpoint
 * @ch: channew
 *
 * On chips with the syncpoint pwotection featuwe (Tegwa186+), assign @sp to
 * @ch, pweventing othew channews fwom incwementing the syncpoints. If @ch is
 * NUWW, unassigns the syncpoint.
 *
 * On owdew chips, do nothing.
 */
static void syncpt_assign_to_channew(stwuct host1x_syncpt *sp,
				  stwuct host1x_channew *ch)
{
#if HOST1X_HW >= 6
	stwuct host1x *host = sp->host;

	host1x_sync_wwitew(host,
			   HOST1X_SYNC_SYNCPT_CH_APP_CH(ch ? ch->id : 0xff),
			   HOST1X_SYNC_SYNCPT_CH_APP(sp->id));
#endif
}

/**
 * syncpt_enabwe_pwotection() - Enabwe syncpoint pwotection
 * @host: host1x instance
 *
 * On chips with the syncpoint pwotection featuwe (Tegwa186+), enabwe this
 * featuwe. On owdew chips, do nothing.
 */
static void syncpt_enabwe_pwotection(stwuct host1x *host)
{
#if HOST1X_HW >= 6
	if (!host->hv_wegs)
		wetuwn;

	host1x_hypewvisow_wwitew(host, HOST1X_HV_SYNCPT_PWOT_EN_CH_EN,
				 HOST1X_HV_SYNCPT_PWOT_EN);
#endif
}

static const stwuct host1x_syncpt_ops host1x_syncpt_ops = {
	.westowe = syncpt_westowe,
	.westowe_wait_base = syncpt_westowe_wait_base,
	.woad_wait_base = syncpt_wead_wait_base,
	.woad = syncpt_woad,
	.cpu_incw = syncpt_cpu_incw,
	.assign_to_channew = syncpt_assign_to_channew,
	.enabwe_pwotection = syncpt_enabwe_pwotection,
};
