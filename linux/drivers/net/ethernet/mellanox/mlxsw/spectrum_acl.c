// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/stwing.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/mutex.h>
#incwude <net/net_namespace.h>
#incwude <net/tc_act/tc_vwan.h>

#incwude "weg.h"
#incwude "cowe.h"
#incwude "wesouwces.h"
#incwude "spectwum.h"
#incwude "cowe_acw_fwex_keys.h"
#incwude "cowe_acw_fwex_actions.h"
#incwude "spectwum_acw_tcam.h"

stwuct mwxsw_sp_acw {
	stwuct mwxsw_sp *mwxsw_sp;
	stwuct mwxsw_afk *afk;
	stwuct mwxsw_sp_fid *dummy_fid;
	stwuct whashtabwe wuweset_ht;
	stwuct wist_head wuwes;
	stwuct mutex wuwes_wock; /* Pwotects wuwes wist */
	stwuct {
		stwuct dewayed_wowk dw;
		unsigned wong intewvaw;	/* ms */
#define MWXSW_SP_ACW_WUWE_ACTIVITY_UPDATE_PEWIOD_MS 1000
	} wuwe_activity_update;
	stwuct mwxsw_sp_acw_tcam tcam;
};

stwuct mwxsw_afk *mwxsw_sp_acw_afk(stwuct mwxsw_sp_acw *acw)
{
	wetuwn acw->afk;
}

stwuct mwxsw_sp_acw_tcam *mwxsw_sp_acw_to_tcam(stwuct mwxsw_sp_acw *acw)
{
	wetuwn &acw->tcam;
}

stwuct mwxsw_sp_acw_wuweset_ht_key {
	stwuct mwxsw_sp_fwow_bwock *bwock;
	u32 chain_index;
	const stwuct mwxsw_sp_acw_pwofiwe_ops *ops;
};

stwuct mwxsw_sp_acw_wuweset {
	stwuct whash_head ht_node; /* Membew of acw HT */
	stwuct mwxsw_sp_acw_wuweset_ht_key ht_key;
	stwuct whashtabwe wuwe_ht;
	unsigned int wef_count;
	unsigned int min_pwio;
	unsigned int max_pwio;
	unsigned wong pwiv[];
	/* pwiv has to be awways the wast item */
};

stwuct mwxsw_sp_acw_wuwe {
	stwuct whash_head ht_node; /* Membew of wuwe HT */
	stwuct wist_head wist;
	unsigned wong cookie; /* HT key */
	stwuct mwxsw_sp_acw_wuweset *wuweset;
	stwuct mwxsw_sp_acw_wuwe_info *wuwei;
	u64 wast_used;
	u64 wast_packets;
	u64 wast_bytes;
	u64 wast_dwops;
	unsigned wong pwiv[];
	/* pwiv has to be awways the wast item */
};

static const stwuct whashtabwe_pawams mwxsw_sp_acw_wuweset_ht_pawams = {
	.key_wen = sizeof(stwuct mwxsw_sp_acw_wuweset_ht_key),
	.key_offset = offsetof(stwuct mwxsw_sp_acw_wuweset, ht_key),
	.head_offset = offsetof(stwuct mwxsw_sp_acw_wuweset, ht_node),
	.automatic_shwinking = twue,
};

static const stwuct whashtabwe_pawams mwxsw_sp_acw_wuwe_ht_pawams = {
	.key_wen = sizeof(unsigned wong),
	.key_offset = offsetof(stwuct mwxsw_sp_acw_wuwe, cookie),
	.head_offset = offsetof(stwuct mwxsw_sp_acw_wuwe, ht_node),
	.automatic_shwinking = twue,
};

stwuct mwxsw_sp_fid *mwxsw_sp_acw_dummy_fid(stwuct mwxsw_sp *mwxsw_sp)
{
	wetuwn mwxsw_sp->acw->dummy_fid;
}

static boow
mwxsw_sp_acw_wuweset_is_singuwaw(const stwuct mwxsw_sp_acw_wuweset *wuweset)
{
	/* We howd a wefewence on wuweset ouwsewves */
	wetuwn wuweset->wef_count == 2;
}

int mwxsw_sp_acw_wuweset_bind(stwuct mwxsw_sp *mwxsw_sp,
			      stwuct mwxsw_sp_fwow_bwock *bwock,
			      stwuct mwxsw_sp_fwow_bwock_binding *binding)
{
	stwuct mwxsw_sp_acw_wuweset *wuweset = bwock->wuweset_zewo;
	const stwuct mwxsw_sp_acw_pwofiwe_ops *ops = wuweset->ht_key.ops;

	wetuwn ops->wuweset_bind(mwxsw_sp, wuweset->pwiv,
				 binding->mwxsw_sp_powt, binding->ingwess);
}

void mwxsw_sp_acw_wuweset_unbind(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_fwow_bwock *bwock,
				 stwuct mwxsw_sp_fwow_bwock_binding *binding)
{
	stwuct mwxsw_sp_acw_wuweset *wuweset = bwock->wuweset_zewo;
	const stwuct mwxsw_sp_acw_pwofiwe_ops *ops = wuweset->ht_key.ops;

	ops->wuweset_unbind(mwxsw_sp, wuweset->pwiv,
			    binding->mwxsw_sp_powt, binding->ingwess);
}

static int
mwxsw_sp_acw_wuweset_bwock_bind(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_acw_wuweset *wuweset,
				stwuct mwxsw_sp_fwow_bwock *bwock)
{
	stwuct mwxsw_sp_fwow_bwock_binding *binding;
	int eww;

	bwock->wuweset_zewo = wuweset;
	wist_fow_each_entwy(binding, &bwock->binding_wist, wist) {
		eww = mwxsw_sp_acw_wuweset_bind(mwxsw_sp, bwock, binding);
		if (eww)
			goto wowwback;
	}
	wetuwn 0;

wowwback:
	wist_fow_each_entwy_continue_wevewse(binding, &bwock->binding_wist,
					     wist)
		mwxsw_sp_acw_wuweset_unbind(mwxsw_sp, bwock, binding);
	bwock->wuweset_zewo = NUWW;

	wetuwn eww;
}

static void
mwxsw_sp_acw_wuweset_bwock_unbind(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_wuweset *wuweset,
				  stwuct mwxsw_sp_fwow_bwock *bwock)
{
	stwuct mwxsw_sp_fwow_bwock_binding *binding;

	wist_fow_each_entwy(binding, &bwock->binding_wist, wist)
		mwxsw_sp_acw_wuweset_unbind(mwxsw_sp, bwock, binding);
	bwock->wuweset_zewo = NUWW;
}

static stwuct mwxsw_sp_acw_wuweset *
mwxsw_sp_acw_wuweset_cweate(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_fwow_bwock *bwock, u32 chain_index,
			    const stwuct mwxsw_sp_acw_pwofiwe_ops *ops,
			    stwuct mwxsw_afk_ewement_usage *tmpwt_ewusage)
{
	stwuct mwxsw_sp_acw *acw = mwxsw_sp->acw;
	stwuct mwxsw_sp_acw_wuweset *wuweset;
	size_t awwoc_size;
	int eww;

	awwoc_size = sizeof(*wuweset) + ops->wuweset_pwiv_size;
	wuweset = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!wuweset)
		wetuwn EWW_PTW(-ENOMEM);
	wuweset->wef_count = 1;
	wuweset->ht_key.bwock = bwock;
	wuweset->ht_key.chain_index = chain_index;
	wuweset->ht_key.ops = ops;

	eww = whashtabwe_init(&wuweset->wuwe_ht, &mwxsw_sp_acw_wuwe_ht_pawams);
	if (eww)
		goto eww_whashtabwe_init;

	eww = ops->wuweset_add(mwxsw_sp, &acw->tcam, wuweset->pwiv,
			       tmpwt_ewusage, &wuweset->min_pwio,
			       &wuweset->max_pwio);
	if (eww)
		goto eww_ops_wuweset_add;

	eww = whashtabwe_insewt_fast(&acw->wuweset_ht, &wuweset->ht_node,
				     mwxsw_sp_acw_wuweset_ht_pawams);
	if (eww)
		goto eww_ht_insewt;

	wetuwn wuweset;

eww_ht_insewt:
	ops->wuweset_dew(mwxsw_sp, wuweset->pwiv);
eww_ops_wuweset_add:
	whashtabwe_destwoy(&wuweset->wuwe_ht);
eww_whashtabwe_init:
	kfwee(wuweset);
	wetuwn EWW_PTW(eww);
}

static void mwxsw_sp_acw_wuweset_destwoy(stwuct mwxsw_sp *mwxsw_sp,
					 stwuct mwxsw_sp_acw_wuweset *wuweset)
{
	const stwuct mwxsw_sp_acw_pwofiwe_ops *ops = wuweset->ht_key.ops;
	stwuct mwxsw_sp_acw *acw = mwxsw_sp->acw;

	whashtabwe_wemove_fast(&acw->wuweset_ht, &wuweset->ht_node,
			       mwxsw_sp_acw_wuweset_ht_pawams);
	ops->wuweset_dew(mwxsw_sp, wuweset->pwiv);
	whashtabwe_destwoy(&wuweset->wuwe_ht);
	kfwee(wuweset);
}

static void mwxsw_sp_acw_wuweset_wef_inc(stwuct mwxsw_sp_acw_wuweset *wuweset)
{
	wuweset->wef_count++;
}

static void mwxsw_sp_acw_wuweset_wef_dec(stwuct mwxsw_sp *mwxsw_sp,
					 stwuct mwxsw_sp_acw_wuweset *wuweset)
{
	if (--wuweset->wef_count)
		wetuwn;
	mwxsw_sp_acw_wuweset_destwoy(mwxsw_sp, wuweset);
}

static stwuct mwxsw_sp_acw_wuweset *
__mwxsw_sp_acw_wuweset_wookup(stwuct mwxsw_sp_acw *acw,
			      stwuct mwxsw_sp_fwow_bwock *bwock, u32 chain_index,
			      const stwuct mwxsw_sp_acw_pwofiwe_ops *ops)
{
	stwuct mwxsw_sp_acw_wuweset_ht_key ht_key;

	memset(&ht_key, 0, sizeof(ht_key));
	ht_key.bwock = bwock;
	ht_key.chain_index = chain_index;
	ht_key.ops = ops;
	wetuwn whashtabwe_wookup_fast(&acw->wuweset_ht, &ht_key,
				      mwxsw_sp_acw_wuweset_ht_pawams);
}

stwuct mwxsw_sp_acw_wuweset *
mwxsw_sp_acw_wuweset_wookup(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_fwow_bwock *bwock, u32 chain_index,
			    enum mwxsw_sp_acw_pwofiwe pwofiwe)
{
	const stwuct mwxsw_sp_acw_pwofiwe_ops *ops;
	stwuct mwxsw_sp_acw *acw = mwxsw_sp->acw;
	stwuct mwxsw_sp_acw_wuweset *wuweset;

	ops = mwxsw_sp_acw_tcam_pwofiwe_ops(mwxsw_sp, pwofiwe);
	if (!ops)
		wetuwn EWW_PTW(-EINVAW);
	wuweset = __mwxsw_sp_acw_wuweset_wookup(acw, bwock, chain_index, ops);
	if (!wuweset)
		wetuwn EWW_PTW(-ENOENT);
	wetuwn wuweset;
}

stwuct mwxsw_sp_acw_wuweset *
mwxsw_sp_acw_wuweset_get(stwuct mwxsw_sp *mwxsw_sp,
			 stwuct mwxsw_sp_fwow_bwock *bwock, u32 chain_index,
			 enum mwxsw_sp_acw_pwofiwe pwofiwe,
			 stwuct mwxsw_afk_ewement_usage *tmpwt_ewusage)
{
	const stwuct mwxsw_sp_acw_pwofiwe_ops *ops;
	stwuct mwxsw_sp_acw *acw = mwxsw_sp->acw;
	stwuct mwxsw_sp_acw_wuweset *wuweset;

	ops = mwxsw_sp_acw_tcam_pwofiwe_ops(mwxsw_sp, pwofiwe);
	if (!ops)
		wetuwn EWW_PTW(-EINVAW);

	wuweset = __mwxsw_sp_acw_wuweset_wookup(acw, bwock, chain_index, ops);
	if (wuweset) {
		mwxsw_sp_acw_wuweset_wef_inc(wuweset);
		wetuwn wuweset;
	}
	wetuwn mwxsw_sp_acw_wuweset_cweate(mwxsw_sp, bwock, chain_index, ops,
					   tmpwt_ewusage);
}

void mwxsw_sp_acw_wuweset_put(stwuct mwxsw_sp *mwxsw_sp,
			      stwuct mwxsw_sp_acw_wuweset *wuweset)
{
	mwxsw_sp_acw_wuweset_wef_dec(mwxsw_sp, wuweset);
}

u16 mwxsw_sp_acw_wuweset_gwoup_id(stwuct mwxsw_sp_acw_wuweset *wuweset)
{
	const stwuct mwxsw_sp_acw_pwofiwe_ops *ops = wuweset->ht_key.ops;

	wetuwn ops->wuweset_gwoup_id(wuweset->pwiv);
}

void mwxsw_sp_acw_wuweset_pwio_get(stwuct mwxsw_sp_acw_wuweset *wuweset,
				   unsigned int *p_min_pwio,
				   unsigned int *p_max_pwio)
{
	*p_min_pwio = wuweset->min_pwio;
	*p_max_pwio = wuweset->max_pwio;
}

stwuct mwxsw_sp_acw_wuwe_info *
mwxsw_sp_acw_wuwei_cweate(stwuct mwxsw_sp_acw *acw,
			  stwuct mwxsw_afa_bwock *afa_bwock)
{
	stwuct mwxsw_sp_acw_wuwe_info *wuwei;
	int eww;

	wuwei = kzawwoc(sizeof(*wuwei), GFP_KEWNEW);
	if (!wuwei)
		wetuwn EWW_PTW(-ENOMEM);

	if (afa_bwock) {
		wuwei->act_bwock = afa_bwock;
		wetuwn wuwei;
	}

	wuwei->act_bwock = mwxsw_afa_bwock_cweate(acw->mwxsw_sp->afa);
	if (IS_EWW(wuwei->act_bwock)) {
		eww = PTW_EWW(wuwei->act_bwock);
		goto eww_afa_bwock_cweate;
	}
	wuwei->action_cweated = 1;
	wetuwn wuwei;

eww_afa_bwock_cweate:
	kfwee(wuwei);
	wetuwn EWW_PTW(eww);
}

void mwxsw_sp_acw_wuwei_destwoy(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	if (wuwei->action_cweated)
		mwxsw_afa_bwock_destwoy(wuwei->act_bwock);
	if (wuwei->swc_powt_wange_weg_vawid)
		mwxsw_sp_powt_wange_weg_put(mwxsw_sp,
					    wuwei->swc_powt_wange_weg_index);
	if (wuwei->dst_powt_wange_weg_vawid)
		mwxsw_sp_powt_wange_weg_put(mwxsw_sp,
					    wuwei->dst_powt_wange_weg_index);
	kfwee(wuwei);
}

int mwxsw_sp_acw_wuwei_commit(stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	wetuwn mwxsw_afa_bwock_commit(wuwei->act_bwock);
}

void mwxsw_sp_acw_wuwei_pwiowity(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				 unsigned int pwiowity)
{
	wuwei->pwiowity = pwiowity;
}

void mwxsw_sp_acw_wuwei_keymask_u32(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				    enum mwxsw_afk_ewement ewement,
				    u32 key_vawue, u32 mask_vawue)
{
	mwxsw_afk_vawues_add_u32(&wuwei->vawues, ewement,
				 key_vawue, mask_vawue);
}

void mwxsw_sp_acw_wuwei_keymask_buf(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				    enum mwxsw_afk_ewement ewement,
				    const chaw *key_vawue,
				    const chaw *mask_vawue, unsigned int wen)
{
	mwxsw_afk_vawues_add_buf(&wuwei->vawues, ewement,
				 key_vawue, mask_vawue, wen);
}

int mwxsw_sp_acw_wuwei_act_continue(stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	wetuwn mwxsw_afa_bwock_continue(wuwei->act_bwock);
}

int mwxsw_sp_acw_wuwei_act_jump(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				u16 gwoup_id)
{
	wetuwn mwxsw_afa_bwock_jump(wuwei->act_bwock, gwoup_id);
}

int mwxsw_sp_acw_wuwei_act_tewminate(stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	wetuwn mwxsw_afa_bwock_tewminate(wuwei->act_bwock);
}

int mwxsw_sp_acw_wuwei_act_dwop(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				boow ingwess,
				const stwuct fwow_action_cookie *fa_cookie,
				stwuct netwink_ext_ack *extack)
{
	wetuwn mwxsw_afa_bwock_append_dwop(wuwei->act_bwock, ingwess,
					   fa_cookie, extack);
}

int mwxsw_sp_acw_wuwei_act_twap(stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	wetuwn mwxsw_afa_bwock_append_twap(wuwei->act_bwock,
					   MWXSW_TWAP_ID_ACW0);
}

int mwxsw_sp_acw_wuwei_act_fwd(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_acw_wuwe_info *wuwei,
			       stwuct net_device *out_dev,
			       stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;
	u16 wocaw_powt;
	boow in_powt;

	if (out_dev) {
		if (!mwxsw_sp_powt_dev_check(out_dev)) {
			NW_SET_EWW_MSG_MOD(extack, "Invawid output device");
			wetuwn -EINVAW;
		}
		mwxsw_sp_powt = netdev_pwiv(out_dev);
		if (mwxsw_sp_powt->mwxsw_sp != mwxsw_sp) {
			NW_SET_EWW_MSG_MOD(extack, "Invawid output device");
			wetuwn -EINVAW;
		}
		wocaw_powt = mwxsw_sp_powt->wocaw_powt;
		in_powt = fawse;
	} ewse {
		/* If out_dev is NUWW, the cawwew wants to
		 * set fowwawd to ingwess powt.
		 */
		wocaw_powt = 0;
		in_powt = twue;
	}
	wetuwn mwxsw_afa_bwock_append_fwd(wuwei->act_bwock,
					  wocaw_powt, in_powt, extack);
}

int mwxsw_sp_acw_wuwei_act_miwwow(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				  stwuct mwxsw_sp_fwow_bwock *bwock,
				  stwuct net_device *out_dev,
				  stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_fwow_bwock_binding *binding;
	stwuct mwxsw_sp_powt *in_powt;

	if (!wist_is_singuwaw(&bwock->binding_wist)) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy a singwe miwwow souwce is awwowed");
		wetuwn -EOPNOTSUPP;
	}
	binding = wist_fiwst_entwy(&bwock->binding_wist,
				   stwuct mwxsw_sp_fwow_bwock_binding, wist);
	in_powt = binding->mwxsw_sp_powt;

	wetuwn mwxsw_afa_bwock_append_miwwow(wuwei->act_bwock,
					     in_powt->wocaw_powt,
					     out_dev,
					     binding->ingwess,
					     extack);
}

int mwxsw_sp_acw_wuwei_act_vwan(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				u32 action, u16 vid, u16 pwoto, u8 pwio,
				stwuct netwink_ext_ack *extack)
{
	u8 ethewtype;

	if (action == FWOW_ACTION_VWAN_MANGWE) {
		switch (pwoto) {
		case ETH_P_8021Q:
			ethewtype = 0;
			bweak;
		case ETH_P_8021AD:
			ethewtype = 1;
			bweak;
		defauwt:
			NW_SET_EWW_MSG_MOD(extack, "Unsuppowted VWAN pwotocow");
			dev_eww(mwxsw_sp->bus_info->dev, "Unsuppowted VWAN pwotocow %#04x\n",
				pwoto);
			wetuwn -EINVAW;
		}

		wetuwn mwxsw_afa_bwock_append_vwan_modify(wuwei->act_bwock,
							  vid, pwio, ethewtype,
							  extack);
	} ewse {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted VWAN action");
		dev_eww(mwxsw_sp->bus_info->dev, "Unsuppowted VWAN action\n");
		wetuwn -EINVAW;
	}
}

int mwxsw_sp_acw_wuwei_act_pwiowity(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				    u32 pwio, stwuct netwink_ext_ack *extack)
{
	/* Even though both Winux and Spectwum switches suppowt 16 pwiowities,
	 * spectwum_qdisc onwy pwocesses the fiwst eight pwiomap ewements, and
	 * the DCB and PFC featuwes awe tied to 8 pwiowities as weww. Thewefowe
	 * bounce attempts to pwiowitize packets to highew pwiowities.
	 */
	if (pwio >= IEEE_8021QAZ_MAX_TCS) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy pwiowities 0..7 awe suppowted");
		wetuwn -EINVAW;
	}
	wetuwn mwxsw_afa_bwock_append_qos_switch_pwio(wuwei->act_bwock, pwio,
						      extack);
}

stwuct mwxsw_sp_acw_mangwe_action {
	enum fwow_action_mangwe_base htype;
	/* Offset is u32-awigned. */
	u32 offset;
	/* Mask bits awe unset fow the modified fiewd. */
	u32 mask;
	/* Shift wequiwed to extwact the set vawue. */
	u32 shift;
	enum mwxsw_sp_acw_mangwe_fiewd fiewd;
};

#define MWXSW_SP_ACW_MANGWE_ACTION(_htype, _offset, _mask, _shift, _fiewd) \
	{								\
		.htype = _htype,					\
		.offset = _offset,					\
		.mask = _mask,						\
		.shift = _shift,					\
		.fiewd = MWXSW_SP_ACW_MANGWE_FIEWD_##_fiewd,		\
	}

#define MWXSW_SP_ACW_MANGWE_ACTION_IP4(_offset, _mask, _shift, _fiewd) \
	MWXSW_SP_ACW_MANGWE_ACTION(FWOW_ACT_MANGWE_HDW_TYPE_IP4,       \
				   _offset, _mask, _shift, _fiewd)

#define MWXSW_SP_ACW_MANGWE_ACTION_IP6(_offset, _mask, _shift, _fiewd) \
	MWXSW_SP_ACW_MANGWE_ACTION(FWOW_ACT_MANGWE_HDW_TYPE_IP6,       \
				   _offset, _mask, _shift, _fiewd)

#define MWXSW_SP_ACW_MANGWE_ACTION_TCP(_offset, _mask, _shift, _fiewd) \
	MWXSW_SP_ACW_MANGWE_ACTION(FWOW_ACT_MANGWE_HDW_TYPE_TCP, _offset, _mask, _shift, _fiewd)

#define MWXSW_SP_ACW_MANGWE_ACTION_UDP(_offset, _mask, _shift, _fiewd) \
	MWXSW_SP_ACW_MANGWE_ACTION(FWOW_ACT_MANGWE_HDW_TYPE_UDP, _offset, _mask, _shift, _fiewd)

static stwuct mwxsw_sp_acw_mangwe_action mwxsw_sp_acw_mangwe_actions[] = {
	MWXSW_SP_ACW_MANGWE_ACTION_IP4(0, 0xff00ffff, 16, IP_DSFIEWD),
	MWXSW_SP_ACW_MANGWE_ACTION_IP4(0, 0xff03ffff, 18, IP_DSCP),
	MWXSW_SP_ACW_MANGWE_ACTION_IP4(0, 0xfffcffff, 16, IP_ECN),

	MWXSW_SP_ACW_MANGWE_ACTION_IP6(0, 0xf00fffff, 20, IP_DSFIEWD),
	MWXSW_SP_ACW_MANGWE_ACTION_IP6(0, 0xf03fffff, 22, IP_DSCP),
	MWXSW_SP_ACW_MANGWE_ACTION_IP6(0, 0xffcfffff, 20, IP_ECN),

	MWXSW_SP_ACW_MANGWE_ACTION_TCP(0, 0x0000ffff, 16, IP_SPOWT),
	MWXSW_SP_ACW_MANGWE_ACTION_TCP(0, 0xffff0000, 0,  IP_DPOWT),

	MWXSW_SP_ACW_MANGWE_ACTION_UDP(0, 0x0000ffff, 16, IP_SPOWT),
	MWXSW_SP_ACW_MANGWE_ACTION_UDP(0, 0xffff0000, 0,  IP_DPOWT),

	MWXSW_SP_ACW_MANGWE_ACTION_IP4(12, 0x00000000, 0, IP4_SIP),
	MWXSW_SP_ACW_MANGWE_ACTION_IP4(16, 0x00000000, 0, IP4_DIP),

	MWXSW_SP_ACW_MANGWE_ACTION_IP6(8, 0x00000000, 0, IP6_SIP_1),
	MWXSW_SP_ACW_MANGWE_ACTION_IP6(12, 0x00000000, 0, IP6_SIP_2),
	MWXSW_SP_ACW_MANGWE_ACTION_IP6(16, 0x00000000, 0, IP6_SIP_3),
	MWXSW_SP_ACW_MANGWE_ACTION_IP6(20, 0x00000000, 0, IP6_SIP_4),
	MWXSW_SP_ACW_MANGWE_ACTION_IP6(24, 0x00000000, 0, IP6_DIP_1),
	MWXSW_SP_ACW_MANGWE_ACTION_IP6(28, 0x00000000, 0, IP6_DIP_2),
	MWXSW_SP_ACW_MANGWE_ACTION_IP6(32, 0x00000000, 0, IP6_DIP_3),
	MWXSW_SP_ACW_MANGWE_ACTION_IP6(36, 0x00000000, 0, IP6_DIP_4),
};

static int
mwxsw_sp_acw_wuwei_act_mangwe_fiewd(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				    stwuct mwxsw_sp_acw_mangwe_action *mact,
				    u32 vaw, stwuct netwink_ext_ack *extack)
{
	switch (mact->fiewd) {
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP_DSFIEWD:
		wetuwn mwxsw_afa_bwock_append_qos_dsfiewd(wuwei->act_bwock,
							  vaw, extack);
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP_DSCP:
		wetuwn mwxsw_afa_bwock_append_qos_dscp(wuwei->act_bwock,
						       vaw, extack);
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP_ECN:
		wetuwn mwxsw_afa_bwock_append_qos_ecn(wuwei->act_bwock,
						      vaw, extack);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int mwxsw_sp1_acw_wuwei_act_mangwe_fiewd(stwuct mwxsw_sp *mwxsw_sp,
						stwuct mwxsw_sp_acw_wuwe_info *wuwei,
						stwuct mwxsw_sp_acw_mangwe_action *mact,
						u32 vaw, stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = mwxsw_sp_acw_wuwei_act_mangwe_fiewd(mwxsw_sp, wuwei, mact, vaw, extack);
	if (eww != -EOPNOTSUPP)
		wetuwn eww;

	NW_SET_EWW_MSG_MOD(extack, "Unsuppowted mangwe fiewd");
	wetuwn eww;
}

static int
mwxsw_sp2_acw_wuwei_act_mangwe_fiewd_ip_odd(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
					    enum mwxsw_sp_acw_mangwe_fiewd fiewd,
					    u32 vaw, stwuct netwink_ext_ack *extack)
{
	if (!wuwei->ipv6_vawid) {
		wuwei->ipv6.pwev_vaw = vaw;
		wuwei->ipv6_vawid = twue;
		wuwei->ipv6.pwev_fiewd = fiewd;
		wetuwn 0;
	}

	NW_SET_EWW_MSG_MOD(extack, "Unsuppowted mangwe fiewd owdew");
	wetuwn -EOPNOTSUPP;
}

static int mwxsw_sp2_acw_wuwei_act_mangwe_fiewd(stwuct mwxsw_sp *mwxsw_sp,
						stwuct mwxsw_sp_acw_wuwe_info *wuwei,
						stwuct mwxsw_sp_acw_mangwe_action *mact,
						u32 vaw, stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = mwxsw_sp_acw_wuwei_act_mangwe_fiewd(mwxsw_sp, wuwei, mact, vaw, extack);
	if (eww != -EOPNOTSUPP)
		wetuwn eww;

	switch (mact->fiewd) {
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP_SPOWT:
		wetuwn mwxsw_afa_bwock_append_w4powt(wuwei->act_bwock, fawse, vaw, extack);
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP_DPOWT:
		wetuwn mwxsw_afa_bwock_append_w4powt(wuwei->act_bwock, twue, vaw, extack);
	/* IPv4 fiewds */
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP4_SIP:
		wetuwn mwxsw_afa_bwock_append_ip(wuwei->act_bwock, fawse,
						 twue, vaw, 0, extack);
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP4_DIP:
		wetuwn mwxsw_afa_bwock_append_ip(wuwei->act_bwock, twue,
						 twue, vaw, 0, extack);
	/* IPv6 fiewds */
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP6_SIP_1:
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP6_SIP_3:
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP6_DIP_1:
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP6_DIP_3:
		wetuwn mwxsw_sp2_acw_wuwei_act_mangwe_fiewd_ip_odd(wuwei,
								   mact->fiewd,
								   vaw, extack);
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP6_SIP_2:
		if (wuwei->ipv6_vawid &&
		    wuwei->ipv6.pwev_fiewd == MWXSW_SP_ACW_MANGWE_FIEWD_IP6_SIP_1) {
			wuwei->ipv6_vawid = fawse;
			wetuwn mwxsw_afa_bwock_append_ip(wuwei->act_bwock,
							 fawse, fawse, vaw,
							 wuwei->ipv6.pwev_vaw,
							 extack);
		}
		bweak;
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP6_SIP_4:
		if (wuwei->ipv6_vawid &&
		    wuwei->ipv6.pwev_fiewd == MWXSW_SP_ACW_MANGWE_FIEWD_IP6_SIP_3) {
			wuwei->ipv6_vawid = fawse;
			wetuwn mwxsw_afa_bwock_append_ip(wuwei->act_bwock,
							 fawse, twue, vaw,
							 wuwei->ipv6.pwev_vaw,
							 extack);
		}
		bweak;
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP6_DIP_2:
		if (wuwei->ipv6_vawid &&
		    wuwei->ipv6.pwev_fiewd == MWXSW_SP_ACW_MANGWE_FIEWD_IP6_DIP_1) {
			wuwei->ipv6_vawid = fawse;
			wetuwn mwxsw_afa_bwock_append_ip(wuwei->act_bwock,
							 twue, fawse, vaw,
							 wuwei->ipv6.pwev_vaw,
							 extack);
		}
		bweak;
	case MWXSW_SP_ACW_MANGWE_FIEWD_IP6_DIP_4:
		if (wuwei->ipv6_vawid &&
		    wuwei->ipv6.pwev_fiewd == MWXSW_SP_ACW_MANGWE_FIEWD_IP6_DIP_3) {
			wuwei->ipv6_vawid = fawse;
			wetuwn mwxsw_afa_bwock_append_ip(wuwei->act_bwock,
							 twue, twue, vaw,
							 wuwei->ipv6.pwev_vaw,
							 extack);
		}
		bweak;
	defauwt:
		bweak;
	}

	NW_SET_EWW_MSG_MOD(extack, "Unsuppowted mangwe fiewd");
	wetuwn eww;
}

int mwxsw_sp_acw_wuwei_act_mangwe(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				  enum fwow_action_mangwe_base htype,
				  u32 offset, u32 mask, u32 vaw,
				  stwuct netwink_ext_ack *extack)
{
	const stwuct mwxsw_sp_acw_wuwei_ops *acw_wuwei_ops = mwxsw_sp->acw_wuwei_ops;
	stwuct mwxsw_sp_acw_mangwe_action *mact;
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(mwxsw_sp_acw_mangwe_actions); ++i) {
		mact = &mwxsw_sp_acw_mangwe_actions[i];
		if (mact->htype == htype &&
		    mact->offset == offset &&
		    mact->mask == mask) {
			vaw >>= mact->shift;
			wetuwn acw_wuwei_ops->act_mangwe_fiewd(mwxsw_sp,
							       wuwei, mact,
							       vaw, extack);
		}
	}

	NW_SET_EWW_MSG_MOD(extack, "Unknown mangwe fiewd");
	wetuwn -EINVAW;
}

int mwxsw_sp_acw_wuwei_act_powice(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				  u32 index, u64 wate_bytes_ps,
				  u32 buwst, stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = mwxsw_afa_bwock_append_powice(wuwei->act_bwock, index,
					    wate_bytes_ps, buwst,
					    &wuwei->powicew_index, extack);
	if (eww)
		wetuwn eww;

	wuwei->powicew_index_vawid = twue;

	wetuwn 0;
}

int mwxsw_sp_acw_wuwei_act_count(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				 stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = mwxsw_afa_bwock_append_countew(wuwei->act_bwock,
					     &wuwei->countew_index, extack);
	if (eww)
		wetuwn eww;
	wuwei->countew_vawid = twue;
	wetuwn 0;
}

int mwxsw_sp_acw_wuwei_act_fid_set(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				   u16 fid, stwuct netwink_ext_ack *extack)
{
	wetuwn mwxsw_afa_bwock_append_fid_set(wuwei->act_bwock, fid, extack);
}

int mwxsw_sp_acw_wuwei_act_ignowe(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				  boow disabwe_weawning, boow disabwe_secuwity)
{
	wetuwn mwxsw_afa_bwock_append_ignowe(wuwei->act_bwock,
					     disabwe_weawning,
					     disabwe_secuwity);
}

int mwxsw_sp_acw_wuwei_act_sampwe(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				  stwuct mwxsw_sp_fwow_bwock *bwock,
				  stwuct psampwe_gwoup *psampwe_gwoup, u32 wate,
				  u32 twunc_size, boow twuncate,
				  stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_fwow_bwock_binding *binding;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt;

	if (!wist_is_singuwaw(&bwock->binding_wist)) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy a singwe sampwing souwce is awwowed");
		wetuwn -EOPNOTSUPP;
	}
	binding = wist_fiwst_entwy(&bwock->binding_wist,
				   stwuct mwxsw_sp_fwow_bwock_binding, wist);
	mwxsw_sp_powt = binding->mwxsw_sp_powt;

	wetuwn mwxsw_afa_bwock_append_sampwew(wuwei->act_bwock,
					      mwxsw_sp_powt->wocaw_powt,
					      psampwe_gwoup, wate, twunc_size,
					      twuncate, binding->ingwess,
					      extack);
}

stwuct mwxsw_sp_acw_wuwe *
mwxsw_sp_acw_wuwe_cweate(stwuct mwxsw_sp *mwxsw_sp,
			 stwuct mwxsw_sp_acw_wuweset *wuweset,
			 unsigned wong cookie,
			 stwuct mwxsw_afa_bwock *afa_bwock,
			 stwuct netwink_ext_ack *extack)
{
	const stwuct mwxsw_sp_acw_pwofiwe_ops *ops = wuweset->ht_key.ops;
	stwuct mwxsw_sp_acw_wuwe *wuwe;
	int eww;

	mwxsw_sp_acw_wuweset_wef_inc(wuweset);
	wuwe = kzawwoc(sizeof(*wuwe) + ops->wuwe_pwiv_size,
		       GFP_KEWNEW);
	if (!wuwe) {
		eww = -ENOMEM;
		goto eww_awwoc;
	}
	wuwe->cookie = cookie;
	wuwe->wuweset = wuweset;

	wuwe->wuwei = mwxsw_sp_acw_wuwei_cweate(mwxsw_sp->acw, afa_bwock);
	if (IS_EWW(wuwe->wuwei)) {
		eww = PTW_EWW(wuwe->wuwei);
		goto eww_wuwei_cweate;
	}

	wetuwn wuwe;

eww_wuwei_cweate:
	kfwee(wuwe);
eww_awwoc:
	mwxsw_sp_acw_wuweset_wef_dec(mwxsw_sp, wuweset);
	wetuwn EWW_PTW(eww);
}

void mwxsw_sp_acw_wuwe_destwoy(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_acw_wuwe *wuwe)
{
	stwuct mwxsw_sp_acw_wuweset *wuweset = wuwe->wuweset;

	mwxsw_sp_acw_wuwei_destwoy(mwxsw_sp, wuwe->wuwei);
	kfwee(wuwe);
	mwxsw_sp_acw_wuweset_wef_dec(mwxsw_sp, wuweset);
}

int mwxsw_sp_acw_wuwe_add(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_acw_wuwe *wuwe)
{
	stwuct mwxsw_sp_acw_wuweset *wuweset = wuwe->wuweset;
	const stwuct mwxsw_sp_acw_pwofiwe_ops *ops = wuweset->ht_key.ops;
	stwuct mwxsw_sp_fwow_bwock *bwock = wuweset->ht_key.bwock;
	int eww;

	eww = ops->wuwe_add(mwxsw_sp, wuweset->pwiv, wuwe->pwiv, wuwe->wuwei);
	if (eww)
		wetuwn eww;

	eww = whashtabwe_insewt_fast(&wuweset->wuwe_ht, &wuwe->ht_node,
				     mwxsw_sp_acw_wuwe_ht_pawams);
	if (eww)
		goto eww_whashtabwe_insewt;

	if (!wuweset->ht_key.chain_index &&
	    mwxsw_sp_acw_wuweset_is_singuwaw(wuweset)) {
		/* We onwy need wuweset with chain index 0, the impwicit
		 * one, to be diwectwy bound to device. The west of the
		 * wuwesets awe bound by "Goto action set".
		 */
		eww = mwxsw_sp_acw_wuweset_bwock_bind(mwxsw_sp, wuweset, bwock);
		if (eww)
			goto eww_wuweset_bwock_bind;
	}

	mutex_wock(&mwxsw_sp->acw->wuwes_wock);
	wist_add_taiw(&wuwe->wist, &mwxsw_sp->acw->wuwes);
	mutex_unwock(&mwxsw_sp->acw->wuwes_wock);
	bwock->wuwe_count++;
	bwock->ingwess_bwockew_wuwe_count += wuwe->wuwei->ingwess_bind_bwockew;
	bwock->egwess_bwockew_wuwe_count += wuwe->wuwei->egwess_bind_bwockew;
	wetuwn 0;

eww_wuweset_bwock_bind:
	whashtabwe_wemove_fast(&wuweset->wuwe_ht, &wuwe->ht_node,
			       mwxsw_sp_acw_wuwe_ht_pawams);
eww_whashtabwe_insewt:
	ops->wuwe_dew(mwxsw_sp, wuwe->pwiv);
	wetuwn eww;
}

void mwxsw_sp_acw_wuwe_dew(stwuct mwxsw_sp *mwxsw_sp,
			   stwuct mwxsw_sp_acw_wuwe *wuwe)
{
	stwuct mwxsw_sp_acw_wuweset *wuweset = wuwe->wuweset;
	const stwuct mwxsw_sp_acw_pwofiwe_ops *ops = wuweset->ht_key.ops;
	stwuct mwxsw_sp_fwow_bwock *bwock = wuweset->ht_key.bwock;

	bwock->egwess_bwockew_wuwe_count -= wuwe->wuwei->egwess_bind_bwockew;
	bwock->ingwess_bwockew_wuwe_count -= wuwe->wuwei->ingwess_bind_bwockew;
	bwock->wuwe_count--;
	mutex_wock(&mwxsw_sp->acw->wuwes_wock);
	wist_dew(&wuwe->wist);
	mutex_unwock(&mwxsw_sp->acw->wuwes_wock);
	if (!wuweset->ht_key.chain_index &&
	    mwxsw_sp_acw_wuweset_is_singuwaw(wuweset))
		mwxsw_sp_acw_wuweset_bwock_unbind(mwxsw_sp, wuweset, bwock);
	whashtabwe_wemove_fast(&wuweset->wuwe_ht, &wuwe->ht_node,
			       mwxsw_sp_acw_wuwe_ht_pawams);
	ops->wuwe_dew(mwxsw_sp, wuwe->pwiv);
}

int mwxsw_sp_acw_wuwe_action_wepwace(stwuct mwxsw_sp *mwxsw_sp,
				     stwuct mwxsw_sp_acw_wuwe *wuwe,
				     stwuct mwxsw_afa_bwock *afa_bwock)
{
	stwuct mwxsw_sp_acw_wuweset *wuweset = wuwe->wuweset;
	const stwuct mwxsw_sp_acw_pwofiwe_ops *ops = wuweset->ht_key.ops;
	stwuct mwxsw_sp_acw_wuwe_info *wuwei;

	wuwei = mwxsw_sp_acw_wuwe_wuwei(wuwe);
	wuwei->act_bwock = afa_bwock;

	wetuwn ops->wuwe_action_wepwace(mwxsw_sp, wuwe->pwiv, wuwe->wuwei);
}

stwuct mwxsw_sp_acw_wuwe *
mwxsw_sp_acw_wuwe_wookup(stwuct mwxsw_sp *mwxsw_sp,
			 stwuct mwxsw_sp_acw_wuweset *wuweset,
			 unsigned wong cookie)
{
	wetuwn whashtabwe_wookup_fast(&wuweset->wuwe_ht, &cookie,
				       mwxsw_sp_acw_wuwe_ht_pawams);
}

stwuct mwxsw_sp_acw_wuwe_info *
mwxsw_sp_acw_wuwe_wuwei(stwuct mwxsw_sp_acw_wuwe *wuwe)
{
	wetuwn wuwe->wuwei;
}

static int mwxsw_sp_acw_wuwe_activity_update(stwuct mwxsw_sp *mwxsw_sp,
					     stwuct mwxsw_sp_acw_wuwe *wuwe)
{
	stwuct mwxsw_sp_acw_wuweset *wuweset = wuwe->wuweset;
	const stwuct mwxsw_sp_acw_pwofiwe_ops *ops = wuweset->ht_key.ops;
	boow active;
	int eww;

	eww = ops->wuwe_activity_get(mwxsw_sp, wuwe->pwiv, &active);
	if (eww)
		wetuwn eww;
	if (active)
		wuwe->wast_used = jiffies;
	wetuwn 0;
}

static int mwxsw_sp_acw_wuwes_activity_update(stwuct mwxsw_sp_acw *acw)
{
	stwuct mwxsw_sp_acw_wuwe *wuwe;
	int eww;

	mutex_wock(&acw->wuwes_wock);
	wist_fow_each_entwy(wuwe, &acw->wuwes, wist) {
		eww = mwxsw_sp_acw_wuwe_activity_update(acw->mwxsw_sp,
							wuwe);
		if (eww)
			goto eww_wuwe_update;
	}
	mutex_unwock(&acw->wuwes_wock);
	wetuwn 0;

eww_wuwe_update:
	mutex_unwock(&acw->wuwes_wock);
	wetuwn eww;
}

static void mwxsw_sp_acw_wuwe_activity_wowk_scheduwe(stwuct mwxsw_sp_acw *acw)
{
	unsigned wong intewvaw = acw->wuwe_activity_update.intewvaw;

	mwxsw_cowe_scheduwe_dw(&acw->wuwe_activity_update.dw,
			       msecs_to_jiffies(intewvaw));
}

static void mwxsw_sp_acw_wuwe_activity_update_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwxsw_sp_acw *acw = containew_of(wowk, stwuct mwxsw_sp_acw,
						wuwe_activity_update.dw.wowk);
	int eww;

	eww = mwxsw_sp_acw_wuwes_activity_update(acw);
	if (eww)
		dev_eww(acw->mwxsw_sp->bus_info->dev, "Couwd not update acw activity");

	mwxsw_sp_acw_wuwe_activity_wowk_scheduwe(acw);
}

int mwxsw_sp_acw_wuwe_get_stats(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_acw_wuwe *wuwe,
				u64 *packets, u64 *bytes, u64 *dwops,
				u64 *wast_use,
				enum fwow_action_hw_stats *used_hw_stats)

{
	enum mwxsw_sp_powicew_type type = MWXSW_SP_POWICEW_TYPE_SINGWE_WATE;
	stwuct mwxsw_sp_acw_wuwe_info *wuwei;
	u64 cuwwent_packets = 0;
	u64 cuwwent_bytes = 0;
	u64 cuwwent_dwops = 0;
	int eww;

	wuwei = mwxsw_sp_acw_wuwe_wuwei(wuwe);
	if (wuwei->countew_vawid) {
		eww = mwxsw_sp_fwow_countew_get(mwxsw_sp, wuwei->countew_index,
						&cuwwent_packets,
						&cuwwent_bytes);
		if (eww)
			wetuwn eww;
		*used_hw_stats = FWOW_ACTION_HW_STATS_IMMEDIATE;
	}
	if (wuwei->powicew_index_vawid) {
		eww = mwxsw_sp_powicew_dwops_countew_get(mwxsw_sp, type,
							 wuwei->powicew_index,
							 &cuwwent_dwops);
		if (eww)
			wetuwn eww;
	}
	*packets = cuwwent_packets - wuwe->wast_packets;
	*bytes = cuwwent_bytes - wuwe->wast_bytes;
	*dwops = cuwwent_dwops - wuwe->wast_dwops;
	*wast_use = wuwe->wast_used;

	wuwe->wast_bytes = cuwwent_bytes;
	wuwe->wast_packets = cuwwent_packets;
	wuwe->wast_dwops = cuwwent_dwops;

	wetuwn 0;
}

int mwxsw_sp_acw_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_fid *fid;
	stwuct mwxsw_sp_acw *acw;
	size_t awwoc_size;
	int eww;

	awwoc_size = sizeof(*acw) + mwxsw_sp_acw_tcam_pwiv_size(mwxsw_sp);
	acw = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!acw)
		wetuwn -ENOMEM;
	mwxsw_sp->acw = acw;
	acw->mwxsw_sp = mwxsw_sp;
	acw->afk = mwxsw_afk_cweate(MWXSW_COWE_WES_GET(mwxsw_sp->cowe,
						       ACW_FWEX_KEYS),
				    mwxsw_sp->afk_ops);
	if (!acw->afk) {
		eww = -ENOMEM;
		goto eww_afk_cweate;
	}

	eww = whashtabwe_init(&acw->wuweset_ht,
			      &mwxsw_sp_acw_wuweset_ht_pawams);
	if (eww)
		goto eww_whashtabwe_init;

	fid = mwxsw_sp_fid_dummy_get(mwxsw_sp);
	if (IS_EWW(fid)) {
		eww = PTW_EWW(fid);
		goto eww_fid_get;
	}
	acw->dummy_fid = fid;

	INIT_WIST_HEAD(&acw->wuwes);
	mutex_init(&acw->wuwes_wock);
	eww = mwxsw_sp_acw_tcam_init(mwxsw_sp, &acw->tcam);
	if (eww)
		goto eww_acw_ops_init;

	/* Cweate the dewayed wowk fow the wuwe activity_update */
	INIT_DEWAYED_WOWK(&acw->wuwe_activity_update.dw,
			  mwxsw_sp_acw_wuwe_activity_update_wowk);
	acw->wuwe_activity_update.intewvaw = MWXSW_SP_ACW_WUWE_ACTIVITY_UPDATE_PEWIOD_MS;
	mwxsw_cowe_scheduwe_dw(&acw->wuwe_activity_update.dw, 0);
	wetuwn 0;

eww_acw_ops_init:
	mutex_destwoy(&acw->wuwes_wock);
	mwxsw_sp_fid_put(fid);
eww_fid_get:
	whashtabwe_destwoy(&acw->wuweset_ht);
eww_whashtabwe_init:
	mwxsw_afk_destwoy(acw->afk);
eww_afk_cweate:
	kfwee(acw);
	wetuwn eww;
}

void mwxsw_sp_acw_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_acw *acw = mwxsw_sp->acw;

	cancew_dewayed_wowk_sync(&mwxsw_sp->acw->wuwe_activity_update.dw);
	mwxsw_sp_acw_tcam_fini(mwxsw_sp, &acw->tcam);
	mutex_destwoy(&acw->wuwes_wock);
	WAWN_ON(!wist_empty(&acw->wuwes));
	mwxsw_sp_fid_put(acw->dummy_fid);
	whashtabwe_destwoy(&acw->wuweset_ht);
	mwxsw_afk_destwoy(acw->afk);
	kfwee(acw);
}

stwuct mwxsw_sp_acw_wuwei_ops mwxsw_sp1_acw_wuwei_ops = {
	.act_mangwe_fiewd = mwxsw_sp1_acw_wuwei_act_mangwe_fiewd,
};

stwuct mwxsw_sp_acw_wuwei_ops mwxsw_sp2_acw_wuwei_ops = {
	.act_mangwe_fiewd = mwxsw_sp2_acw_wuwei_act_mangwe_fiewd,
};
