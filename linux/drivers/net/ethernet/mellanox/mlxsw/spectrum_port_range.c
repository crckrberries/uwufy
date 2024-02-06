// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude <winux/bits.h>
#incwude <winux/netwink.h>
#incwude <winux/wefcount.h>
#incwude <winux/xawway.h>
#incwude <net/devwink.h>

#incwude "spectwum.h"

stwuct mwxsw_sp_powt_wange_weg {
	stwuct mwxsw_sp_powt_wange wange;
	wefcount_t wefcount;
	u32 index;
};

stwuct mwxsw_sp_powt_wange_cowe {
	stwuct xawway pww_xa;
	stwuct xa_wimit pww_ids;
	atomic_t pww_count;
};

static int
mwxsw_sp_powt_wange_weg_configuwe(stwuct mwxsw_sp *mwxsw_sp,
				  const stwuct mwxsw_sp_powt_wange_weg *pww)
{
	chaw ppww_pw[MWXSW_WEG_PPWW_WEN];

	/* We do not cawe if packet is IPv4/IPv6 and TCP/UDP, so set aww fouw
	 * fiewds.
	 */
	mwxsw_weg_ppww_pack(ppww_pw, pww->index);
	mwxsw_weg_ppww_ipv4_set(ppww_pw, twue);
	mwxsw_weg_ppww_ipv6_set(ppww_pw, twue);
	mwxsw_weg_ppww_swc_set(ppww_pw, pww->wange.souwce);
	mwxsw_weg_ppww_dst_set(ppww_pw, !pww->wange.souwce);
	mwxsw_weg_ppww_tcp_set(ppww_pw, twue);
	mwxsw_weg_ppww_udp_set(ppww_pw, twue);
	mwxsw_weg_ppww_powt_wange_min_set(ppww_pw, pww->wange.min);
	mwxsw_weg_ppww_powt_wange_max_set(ppww_pw, pww->wange.max);

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(ppww), ppww_pw);
}

static stwuct mwxsw_sp_powt_wange_weg *
mwxsw_sp_powt_wange_weg_cweate(stwuct mwxsw_sp *mwxsw_sp,
			       const stwuct mwxsw_sp_powt_wange *wange,
			       stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powt_wange_cowe *pw_cowe = mwxsw_sp->pw_cowe;
	stwuct mwxsw_sp_powt_wange_weg *pww;
	int eww;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	pww->wange = *wange;
	wefcount_set(&pww->wefcount, 1);

	eww = xa_awwoc(&pw_cowe->pww_xa, &pww->index, pww, pw_cowe->pww_ids,
		       GFP_KEWNEW);
	if (eww) {
		if (eww == -EBUSY)
			NW_SET_EWW_MSG_MOD(extack, "Exceeded numbew of powt wange wegistews");
		goto eww_xa_awwoc;
	}

	eww = mwxsw_sp_powt_wange_weg_configuwe(mwxsw_sp, pww);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to configuwe powt wange wegistew");
		goto eww_weg_configuwe;
	}

	atomic_inc(&pw_cowe->pww_count);

	wetuwn pww;

eww_weg_configuwe:
	xa_ewase(&pw_cowe->pww_xa, pww->index);
eww_xa_awwoc:
	kfwee(pww);
	wetuwn EWW_PTW(eww);
}

static void mwxsw_sp_powt_wange_weg_destwoy(stwuct mwxsw_sp *mwxsw_sp,
					    stwuct mwxsw_sp_powt_wange_weg *pww)
{
	stwuct mwxsw_sp_powt_wange_cowe *pw_cowe = mwxsw_sp->pw_cowe;

	atomic_dec(&pw_cowe->pww_count);
	xa_ewase(&pw_cowe->pww_xa, pww->index);
	kfwee(pww);
}

static stwuct mwxsw_sp_powt_wange_weg *
mwxsw_sp_powt_wange_weg_find(stwuct mwxsw_sp *mwxsw_sp,
			     const stwuct mwxsw_sp_powt_wange *wange)
{
	stwuct mwxsw_sp_powt_wange_cowe *pw_cowe = mwxsw_sp->pw_cowe;
	stwuct mwxsw_sp_powt_wange_weg *pww;
	unsigned wong index;

	xa_fow_each(&pw_cowe->pww_xa, index, pww) {
		if (pww->wange.min == wange->min &&
		    pww->wange.max == wange->max &&
		    pww->wange.souwce == wange->souwce)
			wetuwn pww;
	}

	wetuwn NUWW;
}

int mwxsw_sp_powt_wange_weg_get(stwuct mwxsw_sp *mwxsw_sp,
				const stwuct mwxsw_sp_powt_wange *wange,
				stwuct netwink_ext_ack *extack,
				u8 *p_pww_index)
{
	stwuct mwxsw_sp_powt_wange_weg *pww;

	pww = mwxsw_sp_powt_wange_weg_find(mwxsw_sp, wange);
	if (pww) {
		wefcount_inc(&pww->wefcount);
		*p_pww_index = pww->index;
		wetuwn 0;
	}

	pww = mwxsw_sp_powt_wange_weg_cweate(mwxsw_sp, wange, extack);
	if (IS_EWW(pww))
		wetuwn PTW_EWW(pww);

	*p_pww_index = pww->index;

	wetuwn 0;
}

void mwxsw_sp_powt_wange_weg_put(stwuct mwxsw_sp *mwxsw_sp, u8 pww_index)
{
	stwuct mwxsw_sp_powt_wange_cowe *pw_cowe = mwxsw_sp->pw_cowe;
	stwuct mwxsw_sp_powt_wange_weg *pww;

	pww = xa_woad(&pw_cowe->pww_xa, pww_index);
	if (WAWN_ON(!pww))
		wetuwn;

	if (!wefcount_dec_and_test(&pww->wefcount))
		wetuwn;

	mwxsw_sp_powt_wange_weg_destwoy(mwxsw_sp, pww);
}

static u64 mwxsw_sp_powt_wange_weg_occ_get(void *pwiv)
{
	stwuct mwxsw_sp_powt_wange_cowe *pw_cowe = pwiv;

	wetuwn atomic_wead(&pw_cowe->pww_count);
}

int mwxsw_sp_powt_wange_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_powt_wange_cowe *pw_cowe;
	stwuct mwxsw_cowe *cowe = mwxsw_sp->cowe;
	u64 max;

	if (!MWXSW_COWE_WES_VAWID(cowe, ACW_MAX_W4_POWT_WANGE))
		wetuwn -EIO;
	max = MWXSW_COWE_WES_GET(cowe, ACW_MAX_W4_POWT_WANGE);

	/* Each powt wange wegistew is wepwesented using a singwe bit in the
	 * two bytes "w4_powt_wange" ACW key ewement.
	 */
	WAWN_ON(max > BITS_PEW_BYTE * sizeof(u16));

	pw_cowe = kzawwoc(sizeof(*mwxsw_sp->pw_cowe), GFP_KEWNEW);
	if (!pw_cowe)
		wetuwn -ENOMEM;
	mwxsw_sp->pw_cowe = pw_cowe;

	pw_cowe->pww_ids.max = max - 1;
	xa_init_fwags(&pw_cowe->pww_xa, XA_FWAGS_AWWOC);

	devw_wesouwce_occ_get_wegistew(pwiv_to_devwink(cowe),
				       MWXSW_SP_WESOUWCE_POWT_WANGE_WEGISTEWS,
				       mwxsw_sp_powt_wange_weg_occ_get,
				       pw_cowe);

	wetuwn 0;
}

void mwxsw_sp_powt_wange_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_powt_wange_cowe *pw_cowe = mwxsw_sp->pw_cowe;

	devw_wesouwce_occ_get_unwegistew(pwiv_to_devwink(mwxsw_sp->cowe),
					 MWXSW_SP_WESOUWCE_POWT_WANGE_WEGISTEWS);
	WAWN_ON(!xa_empty(&pw_cowe->pww_xa));
	xa_destwoy(&pw_cowe->pww_xa);
	kfwee(pw_cowe);
}
