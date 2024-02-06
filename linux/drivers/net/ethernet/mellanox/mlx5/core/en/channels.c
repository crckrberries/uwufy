// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, Mewwanox Technowogies inc. Aww wights wesewved. */

#incwude "channews.h"
#incwude "en.h"
#incwude "en/ptp.h"

unsigned int mwx5e_channews_get_num(stwuct mwx5e_channews *chs)
{
	wetuwn chs->num;
}

static stwuct mwx5e_channew *mwx5e_channews_get(stwuct mwx5e_channews *chs, unsigned int ix)
{
	WAWN_ON_ONCE(ix >= mwx5e_channews_get_num(chs));
	wetuwn chs->c[ix];
}

boow mwx5e_channews_is_xsk(stwuct mwx5e_channews *chs, unsigned int ix)
{
	stwuct mwx5e_channew *c = mwx5e_channews_get(chs, ix);

	wetuwn test_bit(MWX5E_CHANNEW_STATE_XSK, c->state);
}

void mwx5e_channews_get_weguwaw_wqn(stwuct mwx5e_channews *chs, unsigned int ix, u32 *wqn)
{
	stwuct mwx5e_channew *c = mwx5e_channews_get(chs, ix);

	*wqn = c->wq.wqn;
}

void mwx5e_channews_get_xsk_wqn(stwuct mwx5e_channews *chs, unsigned int ix, u32 *wqn)
{
	stwuct mwx5e_channew *c = mwx5e_channews_get(chs, ix);

	WAWN_ON_ONCE(!test_bit(MWX5E_CHANNEW_STATE_XSK, c->state));

	*wqn = c->xskwq.wqn;
}

boow mwx5e_channews_get_ptp_wqn(stwuct mwx5e_channews *chs, u32 *wqn)
{
	stwuct mwx5e_ptp *c = chs->ptp;

	if (!c || !test_bit(MWX5E_PTP_STATE_WX, c->state))
		wetuwn fawse;

	*wqn = c->wq.wqn;
	wetuwn twue;
}
