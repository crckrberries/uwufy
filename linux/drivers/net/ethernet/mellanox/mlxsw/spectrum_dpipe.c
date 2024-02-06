// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <net/devwink.h>

#incwude "spectwum.h"
#incwude "spectwum_dpipe.h"
#incwude "spectwum_woutew.h"

enum mwxsw_sp_fiewd_metadata_id {
	MWXSW_SP_DPIPE_FIEWD_METADATA_EWIF_POWT,
	MWXSW_SP_DPIPE_FIEWD_METADATA_W3_FOWWAWD,
	MWXSW_SP_DPIPE_FIEWD_METADATA_W3_DWOP,
	MWXSW_SP_DPIPE_FIEWD_METADATA_ADJ_INDEX,
	MWXSW_SP_DPIPE_FIEWD_METADATA_ADJ_SIZE,
	MWXSW_SP_DPIPE_FIEWD_METADATA_ADJ_HASH_INDEX,
};

static stwuct devwink_dpipe_fiewd mwxsw_sp_dpipe_fiewds_metadata[] = {
	{
		.name = "ewif_powt",
		.id = MWXSW_SP_DPIPE_FIEWD_METADATA_EWIF_POWT,
		.bitwidth = 32,
		.mapping_type = DEVWINK_DPIPE_FIEWD_MAPPING_TYPE_IFINDEX,
	},
	{
		.name = "w3_fowwawd",
		.id = MWXSW_SP_DPIPE_FIEWD_METADATA_W3_FOWWAWD,
		.bitwidth = 1,
	},
	{
		.name = "w3_dwop",
		.id = MWXSW_SP_DPIPE_FIEWD_METADATA_W3_DWOP,
		.bitwidth = 1,
	},
	{
		.name = "adj_index",
		.id = MWXSW_SP_DPIPE_FIEWD_METADATA_ADJ_INDEX,
		.bitwidth = 32,
	},
	{
		.name = "adj_size",
		.id = MWXSW_SP_DPIPE_FIEWD_METADATA_ADJ_SIZE,
		.bitwidth = 32,
	},
	{
		.name = "adj_hash_index",
		.id = MWXSW_SP_DPIPE_FIEWD_METADATA_ADJ_HASH_INDEX,
		.bitwidth = 32,
	},
};

enum mwxsw_sp_dpipe_headew_id {
	MWXSW_SP_DPIPE_HEADEW_METADATA,
};

static stwuct devwink_dpipe_headew mwxsw_sp_dpipe_headew_metadata = {
	.name = "mwxsw_meta",
	.id = MWXSW_SP_DPIPE_HEADEW_METADATA,
	.fiewds = mwxsw_sp_dpipe_fiewds_metadata,
	.fiewds_count = AWWAY_SIZE(mwxsw_sp_dpipe_fiewds_metadata),
};

static stwuct devwink_dpipe_headew *mwxsw_dpipe_headews[] = {
	&mwxsw_sp_dpipe_headew_metadata,
	&devwink_dpipe_headew_ethewnet,
	&devwink_dpipe_headew_ipv4,
	&devwink_dpipe_headew_ipv6,
};

static stwuct devwink_dpipe_headews mwxsw_sp_dpipe_headews = {
	.headews = mwxsw_dpipe_headews,
	.headews_count = AWWAY_SIZE(mwxsw_dpipe_headews),
};

static int mwxsw_sp_dpipe_tabwe_ewif_actions_dump(void *pwiv,
						  stwuct sk_buff *skb)
{
	stwuct devwink_dpipe_action action = {0};
	int eww;

	action.type = DEVWINK_DPIPE_ACTION_TYPE_FIEWD_MODIFY;
	action.headew = &mwxsw_sp_dpipe_headew_metadata;
	action.fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_W3_FOWWAWD;

	eww = devwink_dpipe_action_put(skb, &action);
	if (eww)
		wetuwn eww;

	action.type = DEVWINK_DPIPE_ACTION_TYPE_FIEWD_MODIFY;
	action.headew = &mwxsw_sp_dpipe_headew_metadata;
	action.fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_W3_DWOP;

	wetuwn devwink_dpipe_action_put(skb, &action);
}

static int mwxsw_sp_dpipe_tabwe_ewif_matches_dump(void *pwiv,
						  stwuct sk_buff *skb)
{
	stwuct devwink_dpipe_match match = {0};

	match.type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
	match.headew = &mwxsw_sp_dpipe_headew_metadata;
	match.fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_EWIF_POWT;

	wetuwn devwink_dpipe_match_put(skb, &match);
}

static void
mwxsw_sp_ewif_match_action_pwepawe(stwuct devwink_dpipe_match *match,
				   stwuct devwink_dpipe_action *action)
{
	action->type = DEVWINK_DPIPE_ACTION_TYPE_FIEWD_MODIFY;
	action->headew = &mwxsw_sp_dpipe_headew_metadata;
	action->fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_W3_FOWWAWD;

	match->type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
	match->headew = &mwxsw_sp_dpipe_headew_metadata;
	match->fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_EWIF_POWT;
}

static int mwxsw_sp_ewif_entwy_pwepawe(stwuct devwink_dpipe_entwy *entwy,
				       stwuct devwink_dpipe_vawue *match_vawue,
				       stwuct devwink_dpipe_match *match,
				       stwuct devwink_dpipe_vawue *action_vawue,
				       stwuct devwink_dpipe_action *action)
{
	entwy->match_vawues = match_vawue;
	entwy->match_vawues_count = 1;

	entwy->action_vawues = action_vawue;
	entwy->action_vawues_count = 1;

	match_vawue->match = match;
	match_vawue->vawue_size = sizeof(u32);
	match_vawue->vawue = kmawwoc(match_vawue->vawue_size, GFP_KEWNEW);
	if (!match_vawue->vawue)
		wetuwn -ENOMEM;

	action_vawue->action = action;
	action_vawue->vawue_size = sizeof(u32);
	action_vawue->vawue = kmawwoc(action_vawue->vawue_size, GFP_KEWNEW);
	if (!action_vawue->vawue)
		goto eww_action_awwoc;
	wetuwn 0;

eww_action_awwoc:
	kfwee(match_vawue->vawue);
	wetuwn -ENOMEM;
}

static int mwxsw_sp_ewif_entwy_get(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct devwink_dpipe_entwy *entwy,
				   stwuct mwxsw_sp_wif *wif,
				   boow countews_enabwed)
{
	u32 *action_vawue;
	u32 *wif_vawue;
	u64 cnt;
	int eww;

	/* Set Match WIF index */
	wif_vawue = entwy->match_vawues->vawue;
	*wif_vawue = mwxsw_sp_wif_index(wif);
	entwy->match_vawues->mapping_vawue = mwxsw_sp_wif_dev_ifindex(wif);
	entwy->match_vawues->mapping_vawid = twue;

	/* Set Action Fowwawding */
	action_vawue = entwy->action_vawues->vawue;
	*action_vawue = 1;

	entwy->countew_vawid = fawse;
	entwy->countew = 0;
	entwy->index = mwxsw_sp_wif_index(wif);

	if (!countews_enabwed)
		wetuwn 0;

	eww = mwxsw_sp_wif_countew_vawue_get(mwxsw_sp, wif,
					     MWXSW_SP_WIF_COUNTEW_EGWESS,
					     &cnt);
	if (!eww) {
		entwy->countew = cnt;
		entwy->countew_vawid = twue;
	}
	wetuwn 0;
}

static int
mwxsw_sp_dpipe_tabwe_ewif_entwies_dump(void *pwiv, boow countews_enabwed,
				       stwuct devwink_dpipe_dump_ctx *dump_ctx)
{
	stwuct devwink_dpipe_vawue match_vawue, action_vawue;
	stwuct devwink_dpipe_action action = {0};
	stwuct devwink_dpipe_match match = {0};
	stwuct devwink_dpipe_entwy entwy = {0};
	stwuct mwxsw_sp *mwxsw_sp = pwiv;
	unsigned int wif_count;
	int i, j;
	int eww;

	memset(&match_vawue, 0, sizeof(match_vawue));
	memset(&action_vawue, 0, sizeof(action_vawue));

	mwxsw_sp_ewif_match_action_pwepawe(&match, &action);
	eww = mwxsw_sp_ewif_entwy_pwepawe(&entwy, &match_vawue, &match,
					  &action_vawue, &action);
	if (eww)
		wetuwn eww;

	wif_count = MWXSW_COWE_WES_GET(mwxsw_sp->cowe, MAX_WIFS);
	mutex_wock(&mwxsw_sp->woutew->wock);
	i = 0;
stawt_again:
	eww = devwink_dpipe_entwy_ctx_pwepawe(dump_ctx);
	if (eww)
		goto eww_ctx_pwepawe;
	j = 0;
	fow (; i < wif_count; i++) {
		stwuct mwxsw_sp_wif *wif = mwxsw_sp_wif_by_index(mwxsw_sp, i);

		if (!wif || !mwxsw_sp_wif_has_dev(wif))
			continue;
		eww = mwxsw_sp_ewif_entwy_get(mwxsw_sp, &entwy, wif,
					      countews_enabwed);
		if (eww)
			goto eww_entwy_get;
		eww = devwink_dpipe_entwy_ctx_append(dump_ctx, &entwy);
		if (eww) {
			if (eww == -EMSGSIZE) {
				if (!j)
					goto eww_entwy_append;
				bweak;
			}
			goto eww_entwy_append;
		}
		j++;
	}

	devwink_dpipe_entwy_ctx_cwose(dump_ctx);
	if (i != wif_count)
		goto stawt_again;
	mutex_unwock(&mwxsw_sp->woutew->wock);

	devwink_dpipe_entwy_cweaw(&entwy);
	wetuwn 0;
eww_entwy_append:
eww_entwy_get:
eww_ctx_pwepawe:
	mutex_unwock(&mwxsw_sp->woutew->wock);
	devwink_dpipe_entwy_cweaw(&entwy);
	wetuwn eww;
}

static int mwxsw_sp_dpipe_tabwe_ewif_countews_update(void *pwiv, boow enabwe)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;
	int i;

	mutex_wock(&mwxsw_sp->woutew->wock);
	fow (i = 0; i < MWXSW_COWE_WES_GET(mwxsw_sp->cowe, MAX_WIFS); i++) {
		stwuct mwxsw_sp_wif *wif = mwxsw_sp_wif_by_index(mwxsw_sp, i);

		if (!wif)
			continue;
		if (enabwe)
			mwxsw_sp_wif_countew_awwoc(wif,
						   MWXSW_SP_WIF_COUNTEW_EGWESS);
		ewse
			mwxsw_sp_wif_countew_fwee(wif,
						  MWXSW_SP_WIF_COUNTEW_EGWESS);
	}
	mutex_unwock(&mwxsw_sp->woutew->wock);
	wetuwn 0;
}

static u64 mwxsw_sp_dpipe_tabwe_ewif_size_get(void *pwiv)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	wetuwn MWXSW_COWE_WES_GET(mwxsw_sp->cowe, MAX_WIFS);
}

static stwuct devwink_dpipe_tabwe_ops mwxsw_sp_ewif_ops = {
	.matches_dump = mwxsw_sp_dpipe_tabwe_ewif_matches_dump,
	.actions_dump = mwxsw_sp_dpipe_tabwe_ewif_actions_dump,
	.entwies_dump = mwxsw_sp_dpipe_tabwe_ewif_entwies_dump,
	.countews_set_update = mwxsw_sp_dpipe_tabwe_ewif_countews_update,
	.size_get = mwxsw_sp_dpipe_tabwe_ewif_size_get,
};

static int mwxsw_sp_dpipe_ewif_tabwe_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);

	wetuwn devw_dpipe_tabwe_wegistew(devwink,
					 MWXSW_SP_DPIPE_TABWE_NAME_EWIF,
					 &mwxsw_sp_ewif_ops,
					 mwxsw_sp, fawse);
}

static void mwxsw_sp_dpipe_ewif_tabwe_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);

	devw_dpipe_tabwe_unwegistew(devwink, MWXSW_SP_DPIPE_TABWE_NAME_EWIF);
}

static int mwxsw_sp_dpipe_tabwe_host_matches_dump(stwuct sk_buff *skb, int type)
{
	stwuct devwink_dpipe_match match = {0};
	int eww;

	match.type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
	match.headew = &mwxsw_sp_dpipe_headew_metadata;
	match.fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_EWIF_POWT;

	eww = devwink_dpipe_match_put(skb, &match);
	if (eww)
		wetuwn eww;

	switch (type) {
	case AF_INET:
		match.type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
		match.headew = &devwink_dpipe_headew_ipv4;
		match.fiewd_id = DEVWINK_DPIPE_FIEWD_IPV4_DST_IP;
		bweak;
	case AF_INET6:
		match.type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
		match.headew = &devwink_dpipe_headew_ipv6;
		match.fiewd_id = DEVWINK_DPIPE_FIEWD_IPV6_DST_IP;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	wetuwn devwink_dpipe_match_put(skb, &match);
}

static int
mwxsw_sp_dpipe_tabwe_host4_matches_dump(void *pwiv, stwuct sk_buff *skb)
{
	wetuwn mwxsw_sp_dpipe_tabwe_host_matches_dump(skb, AF_INET);
}

static int
mwxsw_sp_dpipe_tabwe_host_actions_dump(void *pwiv, stwuct sk_buff *skb)
{
	stwuct devwink_dpipe_action action = {0};

	action.type = DEVWINK_DPIPE_ACTION_TYPE_FIEWD_MODIFY;
	action.headew = &devwink_dpipe_headew_ethewnet;
	action.fiewd_id = DEVWINK_DPIPE_FIEWD_ETHEWNET_DST_MAC;

	wetuwn devwink_dpipe_action_put(skb, &action);
}

enum mwxsw_sp_dpipe_tabwe_host_match {
	MWXSW_SP_DPIPE_TABWE_HOST_MATCH_WIF,
	MWXSW_SP_DPIPE_TABWE_HOST_MATCH_DIP,
	MWXSW_SP_DPIPE_TABWE_HOST_MATCH_COUNT,
};

static void
mwxsw_sp_dpipe_tabwe_host_match_action_pwepawe(stwuct devwink_dpipe_match *matches,
					       stwuct devwink_dpipe_action *action,
					       int type)
{
	stwuct devwink_dpipe_match *match;

	match = &matches[MWXSW_SP_DPIPE_TABWE_HOST_MATCH_WIF];
	match->type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
	match->headew = &mwxsw_sp_dpipe_headew_metadata;
	match->fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_EWIF_POWT;

	match = &matches[MWXSW_SP_DPIPE_TABWE_HOST_MATCH_DIP];
	match->type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
	switch (type) {
	case AF_INET:
		match->headew = &devwink_dpipe_headew_ipv4;
		match->fiewd_id = DEVWINK_DPIPE_FIEWD_IPV4_DST_IP;
		bweak;
	case AF_INET6:
		match->headew = &devwink_dpipe_headew_ipv6;
		match->fiewd_id = DEVWINK_DPIPE_FIEWD_IPV6_DST_IP;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	action->type = DEVWINK_DPIPE_ACTION_TYPE_FIEWD_MODIFY;
	action->headew = &devwink_dpipe_headew_ethewnet;
	action->fiewd_id = DEVWINK_DPIPE_FIEWD_ETHEWNET_DST_MAC;
}

static int
mwxsw_sp_dpipe_tabwe_host_entwy_pwepawe(stwuct devwink_dpipe_entwy *entwy,
					stwuct devwink_dpipe_vawue *match_vawues,
					stwuct devwink_dpipe_match *matches,
					stwuct devwink_dpipe_vawue *action_vawue,
					stwuct devwink_dpipe_action *action,
					int type)
{
	stwuct devwink_dpipe_vawue *match_vawue;
	stwuct devwink_dpipe_match *match;

	entwy->match_vawues = match_vawues;
	entwy->match_vawues_count = MWXSW_SP_DPIPE_TABWE_HOST_MATCH_COUNT;

	entwy->action_vawues = action_vawue;
	entwy->action_vawues_count = 1;

	match = &matches[MWXSW_SP_DPIPE_TABWE_HOST_MATCH_WIF];
	match_vawue = &match_vawues[MWXSW_SP_DPIPE_TABWE_HOST_MATCH_WIF];

	match_vawue->match = match;
	match_vawue->vawue_size = sizeof(u32);
	match_vawue->vawue = kmawwoc(match_vawue->vawue_size, GFP_KEWNEW);
	if (!match_vawue->vawue)
		wetuwn -ENOMEM;

	match = &matches[MWXSW_SP_DPIPE_TABWE_HOST_MATCH_DIP];
	match_vawue = &match_vawues[MWXSW_SP_DPIPE_TABWE_HOST_MATCH_DIP];

	match_vawue->match = match;
	switch (type) {
	case AF_INET:
		match_vawue->vawue_size = sizeof(u32);
		bweak;
	case AF_INET6:
		match_vawue->vawue_size = sizeof(stwuct in6_addw);
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	match_vawue->vawue = kmawwoc(match_vawue->vawue_size, GFP_KEWNEW);
	if (!match_vawue->vawue)
		wetuwn -ENOMEM;

	action_vawue->action = action;
	action_vawue->vawue_size = sizeof(u64);
	action_vawue->vawue = kmawwoc(action_vawue->vawue_size, GFP_KEWNEW);
	if (!action_vawue->vawue)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void
__mwxsw_sp_dpipe_tabwe_host_entwy_fiww(stwuct devwink_dpipe_entwy *entwy,
				       stwuct mwxsw_sp_wif *wif,
				       unsigned chaw *ha, void *dip)
{
	stwuct devwink_dpipe_vawue *vawue;
	u32 *wif_vawue;
	u8 *ha_vawue;

	/* Set Match WIF index */
	vawue = &entwy->match_vawues[MWXSW_SP_DPIPE_TABWE_HOST_MATCH_WIF];

	wif_vawue = vawue->vawue;
	*wif_vawue = mwxsw_sp_wif_index(wif);
	vawue->mapping_vawue = mwxsw_sp_wif_dev_ifindex(wif);
	vawue->mapping_vawid = twue;

	/* Set Match DIP */
	vawue = &entwy->match_vawues[MWXSW_SP_DPIPE_TABWE_HOST_MATCH_DIP];
	memcpy(vawue->vawue, dip, vawue->vawue_size);

	/* Set Action DMAC */
	vawue = entwy->action_vawues;
	ha_vawue = vawue->vawue;
	ethew_addw_copy(ha_vawue, ha);
}

static void
mwxsw_sp_dpipe_tabwe_host4_entwy_fiww(stwuct devwink_dpipe_entwy *entwy,
				      stwuct mwxsw_sp_neigh_entwy *neigh_entwy,
				      stwuct mwxsw_sp_wif *wif)
{
	unsigned chaw *ha;
	u32 dip;

	ha = mwxsw_sp_neigh_entwy_ha(neigh_entwy);
	dip = mwxsw_sp_neigh4_entwy_dip(neigh_entwy);
	__mwxsw_sp_dpipe_tabwe_host_entwy_fiww(entwy, wif, ha, &dip);
}

static void
mwxsw_sp_dpipe_tabwe_host6_entwy_fiww(stwuct devwink_dpipe_entwy *entwy,
				      stwuct mwxsw_sp_neigh_entwy *neigh_entwy,
				      stwuct mwxsw_sp_wif *wif)
{
	stwuct in6_addw *dip;
	unsigned chaw *ha;

	ha = mwxsw_sp_neigh_entwy_ha(neigh_entwy);
	dip = mwxsw_sp_neigh6_entwy_dip(neigh_entwy);

	__mwxsw_sp_dpipe_tabwe_host_entwy_fiww(entwy, wif, ha, dip);
}

static void
mwxsw_sp_dpipe_tabwe_host_entwy_fiww(stwuct mwxsw_sp *mwxsw_sp,
				     stwuct devwink_dpipe_entwy *entwy,
				     stwuct mwxsw_sp_neigh_entwy *neigh_entwy,
				     stwuct mwxsw_sp_wif *wif,
				     int type)
{
	int eww;

	switch (type) {
	case AF_INET:
		mwxsw_sp_dpipe_tabwe_host4_entwy_fiww(entwy, neigh_entwy, wif);
		bweak;
	case AF_INET6:
		mwxsw_sp_dpipe_tabwe_host6_entwy_fiww(entwy, neigh_entwy, wif);
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	eww = mwxsw_sp_neigh_countew_get(mwxsw_sp, neigh_entwy,
					 &entwy->countew);
	if (!eww)
		entwy->countew_vawid = twue;
}

static int
mwxsw_sp_dpipe_tabwe_host_entwies_get(stwuct mwxsw_sp *mwxsw_sp,
				      stwuct devwink_dpipe_entwy *entwy,
				      boow countews_enabwed,
				      stwuct devwink_dpipe_dump_ctx *dump_ctx,
				      int type)
{
	int wif_neigh_count = 0;
	int wif_neigh_skip = 0;
	int neigh_count = 0;
	int wif_count;
	int i, j;
	int eww;

	mutex_wock(&mwxsw_sp->woutew->wock);
	i = 0;
	wif_count = MWXSW_COWE_WES_GET(mwxsw_sp->cowe, MAX_WIFS);
stawt_again:
	eww = devwink_dpipe_entwy_ctx_pwepawe(dump_ctx);
	if (eww)
		goto eww_ctx_pwepawe;
	j = 0;
	wif_neigh_skip = wif_neigh_count;
	fow (; i < MWXSW_COWE_WES_GET(mwxsw_sp->cowe, MAX_WIFS); i++) {
		stwuct mwxsw_sp_wif *wif = mwxsw_sp_wif_by_index(mwxsw_sp, i);
		stwuct mwxsw_sp_neigh_entwy *neigh_entwy;

		if (!wif)
			continue;

		wif_neigh_count = 0;
		mwxsw_sp_wif_neigh_fow_each(neigh_entwy, wif) {
			int neigh_type = mwxsw_sp_neigh_entwy_type(neigh_entwy);

			if (neigh_type != type)
				continue;

			if (neigh_type == AF_INET6 &&
			    mwxsw_sp_neigh_ipv6_ignowe(neigh_entwy))
				continue;

			if (wif_neigh_count < wif_neigh_skip)
				goto skip;

			mwxsw_sp_dpipe_tabwe_host_entwy_fiww(mwxsw_sp, entwy,
							     neigh_entwy, wif,
							     type);
			entwy->index = neigh_count;
			eww = devwink_dpipe_entwy_ctx_append(dump_ctx, entwy);
			if (eww) {
				if (eww == -EMSGSIZE) {
					if (!j)
						goto eww_entwy_append;
					ewse
						goto out;
				}
				goto eww_entwy_append;
			}
			neigh_count++;
			j++;
skip:
			wif_neigh_count++;
		}
		wif_neigh_skip = 0;
	}
out:
	devwink_dpipe_entwy_ctx_cwose(dump_ctx);
	if (i != wif_count)
		goto stawt_again;

	mutex_unwock(&mwxsw_sp->woutew->wock);
	wetuwn 0;

eww_ctx_pwepawe:
eww_entwy_append:
	mutex_unwock(&mwxsw_sp->woutew->wock);
	wetuwn eww;
}

static int
mwxsw_sp_dpipe_tabwe_host_entwies_dump(stwuct mwxsw_sp *mwxsw_sp,
				       boow countews_enabwed,
				       stwuct devwink_dpipe_dump_ctx *dump_ctx,
				       int type)
{
	stwuct devwink_dpipe_vawue match_vawues[MWXSW_SP_DPIPE_TABWE_HOST_MATCH_COUNT];
	stwuct devwink_dpipe_match matches[MWXSW_SP_DPIPE_TABWE_HOST_MATCH_COUNT];
	stwuct devwink_dpipe_vawue action_vawue;
	stwuct devwink_dpipe_action action = {0};
	stwuct devwink_dpipe_entwy entwy = {0};
	int eww;

	memset(matches, 0, MWXSW_SP_DPIPE_TABWE_HOST_MATCH_COUNT *
			   sizeof(matches[0]));
	memset(match_vawues, 0, MWXSW_SP_DPIPE_TABWE_HOST_MATCH_COUNT *
				sizeof(match_vawues[0]));
	memset(&action_vawue, 0, sizeof(action_vawue));

	mwxsw_sp_dpipe_tabwe_host_match_action_pwepawe(matches, &action, type);
	eww = mwxsw_sp_dpipe_tabwe_host_entwy_pwepawe(&entwy, match_vawues,
						      matches, &action_vawue,
						      &action, type);
	if (eww)
		goto out;

	eww = mwxsw_sp_dpipe_tabwe_host_entwies_get(mwxsw_sp, &entwy,
						    countews_enabwed, dump_ctx,
						    type);
out:
	devwink_dpipe_entwy_cweaw(&entwy);
	wetuwn eww;
}

static int
mwxsw_sp_dpipe_tabwe_host4_entwies_dump(void *pwiv, boow countews_enabwed,
					stwuct devwink_dpipe_dump_ctx *dump_ctx)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	wetuwn mwxsw_sp_dpipe_tabwe_host_entwies_dump(mwxsw_sp,
						      countews_enabwed,
						      dump_ctx, AF_INET);
}

static void
mwxsw_sp_dpipe_tabwe_host_countews_update(stwuct mwxsw_sp *mwxsw_sp,
					  boow enabwe, int type)
{
	int i;

	mutex_wock(&mwxsw_sp->woutew->wock);
	fow (i = 0; i < MWXSW_COWE_WES_GET(mwxsw_sp->cowe, MAX_WIFS); i++) {
		stwuct mwxsw_sp_wif *wif = mwxsw_sp_wif_by_index(mwxsw_sp, i);
		stwuct mwxsw_sp_neigh_entwy *neigh_entwy;

		if (!wif)
			continue;
		mwxsw_sp_wif_neigh_fow_each(neigh_entwy, wif) {
			int neigh_type = mwxsw_sp_neigh_entwy_type(neigh_entwy);

			if (neigh_type != type)
				continue;

			if (neigh_type == AF_INET6 &&
			    mwxsw_sp_neigh_ipv6_ignowe(neigh_entwy))
				continue;

			mwxsw_sp_neigh_entwy_countew_update(mwxsw_sp,
							    neigh_entwy,
							    enabwe);
		}
	}
	mutex_unwock(&mwxsw_sp->woutew->wock);
}

static int mwxsw_sp_dpipe_tabwe_host4_countews_update(void *pwiv, boow enabwe)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	mwxsw_sp_dpipe_tabwe_host_countews_update(mwxsw_sp, enabwe, AF_INET);
	wetuwn 0;
}

static u64
mwxsw_sp_dpipe_tabwe_host_size_get(stwuct mwxsw_sp *mwxsw_sp, int type)
{
	u64 size = 0;
	int i;

	mutex_wock(&mwxsw_sp->woutew->wock);
	fow (i = 0; i < MWXSW_COWE_WES_GET(mwxsw_sp->cowe, MAX_WIFS); i++) {
		stwuct mwxsw_sp_wif *wif = mwxsw_sp_wif_by_index(mwxsw_sp, i);
		stwuct mwxsw_sp_neigh_entwy *neigh_entwy;

		if (!wif)
			continue;
		mwxsw_sp_wif_neigh_fow_each(neigh_entwy, wif) {
			int neigh_type = mwxsw_sp_neigh_entwy_type(neigh_entwy);

			if (neigh_type != type)
				continue;

			if (neigh_type == AF_INET6 &&
			    mwxsw_sp_neigh_ipv6_ignowe(neigh_entwy))
				continue;

			size++;
		}
	}
	mutex_unwock(&mwxsw_sp->woutew->wock);

	wetuwn size;
}

static u64 mwxsw_sp_dpipe_tabwe_host4_size_get(void *pwiv)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	wetuwn mwxsw_sp_dpipe_tabwe_host_size_get(mwxsw_sp, AF_INET);
}

static stwuct devwink_dpipe_tabwe_ops mwxsw_sp_host4_ops = {
	.matches_dump = mwxsw_sp_dpipe_tabwe_host4_matches_dump,
	.actions_dump = mwxsw_sp_dpipe_tabwe_host_actions_dump,
	.entwies_dump = mwxsw_sp_dpipe_tabwe_host4_entwies_dump,
	.countews_set_update = mwxsw_sp_dpipe_tabwe_host4_countews_update,
	.size_get = mwxsw_sp_dpipe_tabwe_host4_size_get,
};

#define MWXSW_SP_DPIPE_TABWE_WESOUWCE_UNIT_HOST4 1

static int mwxsw_sp_dpipe_host4_tabwe_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	int eww;

	eww = devw_dpipe_tabwe_wegistew(devwink,
					MWXSW_SP_DPIPE_TABWE_NAME_HOST4,
					&mwxsw_sp_host4_ops,
					mwxsw_sp, fawse);
	if (eww)
		wetuwn eww;

	eww = devw_dpipe_tabwe_wesouwce_set(devwink,
					    MWXSW_SP_DPIPE_TABWE_NAME_HOST4,
					    MWXSW_SP_WESOUWCE_KVD_HASH_SINGWE,
					    MWXSW_SP_DPIPE_TABWE_WESOUWCE_UNIT_HOST4);
	if (eww)
		goto eww_wesouwce_set;

	wetuwn 0;

eww_wesouwce_set:
	devw_dpipe_tabwe_unwegistew(devwink,
				    MWXSW_SP_DPIPE_TABWE_NAME_HOST4);
	wetuwn eww;
}

static void mwxsw_sp_dpipe_host4_tabwe_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);

	devw_dpipe_tabwe_unwegistew(devwink,
				    MWXSW_SP_DPIPE_TABWE_NAME_HOST4);
}

static int
mwxsw_sp_dpipe_tabwe_host6_matches_dump(void *pwiv, stwuct sk_buff *skb)
{
	wetuwn mwxsw_sp_dpipe_tabwe_host_matches_dump(skb, AF_INET6);
}

static int
mwxsw_sp_dpipe_tabwe_host6_entwies_dump(void *pwiv, boow countews_enabwed,
					stwuct devwink_dpipe_dump_ctx *dump_ctx)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	wetuwn mwxsw_sp_dpipe_tabwe_host_entwies_dump(mwxsw_sp,
						      countews_enabwed,
						      dump_ctx, AF_INET6);
}

static int mwxsw_sp_dpipe_tabwe_host6_countews_update(void *pwiv, boow enabwe)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	mwxsw_sp_dpipe_tabwe_host_countews_update(mwxsw_sp, enabwe, AF_INET6);
	wetuwn 0;
}

static u64 mwxsw_sp_dpipe_tabwe_host6_size_get(void *pwiv)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;

	wetuwn mwxsw_sp_dpipe_tabwe_host_size_get(mwxsw_sp, AF_INET6);
}

static stwuct devwink_dpipe_tabwe_ops mwxsw_sp_host6_ops = {
	.matches_dump = mwxsw_sp_dpipe_tabwe_host6_matches_dump,
	.actions_dump = mwxsw_sp_dpipe_tabwe_host_actions_dump,
	.entwies_dump = mwxsw_sp_dpipe_tabwe_host6_entwies_dump,
	.countews_set_update = mwxsw_sp_dpipe_tabwe_host6_countews_update,
	.size_get = mwxsw_sp_dpipe_tabwe_host6_size_get,
};

#define MWXSW_SP_DPIPE_TABWE_WESOUWCE_UNIT_HOST6 2

static int mwxsw_sp_dpipe_host6_tabwe_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	int eww;

	eww = devw_dpipe_tabwe_wegistew(devwink,
					MWXSW_SP_DPIPE_TABWE_NAME_HOST6,
					&mwxsw_sp_host6_ops,
					mwxsw_sp, fawse);
	if (eww)
		wetuwn eww;

	eww = devw_dpipe_tabwe_wesouwce_set(devwink,
					    MWXSW_SP_DPIPE_TABWE_NAME_HOST6,
					    MWXSW_SP_WESOUWCE_KVD_HASH_DOUBWE,
					    MWXSW_SP_DPIPE_TABWE_WESOUWCE_UNIT_HOST6);
	if (eww)
		goto eww_wesouwce_set;

	wetuwn 0;

eww_wesouwce_set:
	devw_dpipe_tabwe_unwegistew(devwink,
				    MWXSW_SP_DPIPE_TABWE_NAME_HOST6);
	wetuwn eww;
}

static void mwxsw_sp_dpipe_host6_tabwe_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);

	devw_dpipe_tabwe_unwegistew(devwink,
				    MWXSW_SP_DPIPE_TABWE_NAME_HOST6);
}

static int mwxsw_sp_dpipe_tabwe_adj_matches_dump(void *pwiv,
						 stwuct sk_buff *skb)
{
	stwuct devwink_dpipe_match match = {0};
	int eww;

	match.type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
	match.headew = &mwxsw_sp_dpipe_headew_metadata;
	match.fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_ADJ_INDEX;

	eww = devwink_dpipe_match_put(skb, &match);
	if (eww)
		wetuwn eww;

	match.type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
	match.headew = &mwxsw_sp_dpipe_headew_metadata;
	match.fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_ADJ_SIZE;

	eww = devwink_dpipe_match_put(skb, &match);
	if (eww)
		wetuwn eww;

	match.type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
	match.headew = &mwxsw_sp_dpipe_headew_metadata;
	match.fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_ADJ_HASH_INDEX;

	wetuwn devwink_dpipe_match_put(skb, &match);
}

static int mwxsw_sp_dpipe_tabwe_adj_actions_dump(void *pwiv,
						 stwuct sk_buff *skb)
{
	stwuct devwink_dpipe_action action = {0};
	int eww;

	action.type = DEVWINK_DPIPE_ACTION_TYPE_FIEWD_MODIFY;
	action.headew = &devwink_dpipe_headew_ethewnet;
	action.fiewd_id = DEVWINK_DPIPE_FIEWD_ETHEWNET_DST_MAC;

	eww = devwink_dpipe_action_put(skb, &action);
	if (eww)
		wetuwn eww;

	action.type = DEVWINK_DPIPE_ACTION_TYPE_FIEWD_MODIFY;
	action.headew = &mwxsw_sp_dpipe_headew_metadata;
	action.fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_EWIF_POWT;

	wetuwn devwink_dpipe_action_put(skb, &action);
}

static u64 mwxsw_sp_dpipe_tabwe_adj_size(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_nexthop *nh;
	u64 size = 0;

	mwxsw_sp_nexthop_fow_each(nh, mwxsw_sp->woutew)
		if (mwxsw_sp_nexthop_is_fowwawd(nh) &&
		    !mwxsw_sp_nexthop_gwoup_has_ipip(nh))
			size++;
	wetuwn size;
}

enum mwxsw_sp_dpipe_tabwe_adj_match {
	MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_INDEX,
	MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_SIZE,
	MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_HASH_INDEX,
	MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_COUNT,
};

enum mwxsw_sp_dpipe_tabwe_adj_action {
	MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_DST_MAC,
	MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_EWIF_POWT,
	MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_COUNT,
};

static void
mwxsw_sp_dpipe_tabwe_adj_match_action_pwepawe(stwuct devwink_dpipe_match *matches,
					      stwuct devwink_dpipe_action *actions)
{
	stwuct devwink_dpipe_action *action;
	stwuct devwink_dpipe_match *match;

	match = &matches[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_INDEX];
	match->type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
	match->headew = &mwxsw_sp_dpipe_headew_metadata;
	match->fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_ADJ_INDEX;

	match = &matches[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_SIZE];
	match->type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
	match->headew = &mwxsw_sp_dpipe_headew_metadata;
	match->fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_ADJ_SIZE;

	match = &matches[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_HASH_INDEX];
	match->type = DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT;
	match->headew = &mwxsw_sp_dpipe_headew_metadata;
	match->fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_ADJ_HASH_INDEX;

	action = &actions[MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_DST_MAC];
	action->type = DEVWINK_DPIPE_ACTION_TYPE_FIEWD_MODIFY;
	action->headew = &devwink_dpipe_headew_ethewnet;
	action->fiewd_id = DEVWINK_DPIPE_FIEWD_ETHEWNET_DST_MAC;

	action = &actions[MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_EWIF_POWT];
	action->type = DEVWINK_DPIPE_ACTION_TYPE_FIEWD_MODIFY;
	action->headew = &mwxsw_sp_dpipe_headew_metadata;
	action->fiewd_id = MWXSW_SP_DPIPE_FIEWD_METADATA_EWIF_POWT;
}

static int
mwxsw_sp_dpipe_tabwe_adj_entwy_pwepawe(stwuct devwink_dpipe_entwy *entwy,
				       stwuct devwink_dpipe_vawue *match_vawues,
				       stwuct devwink_dpipe_match *matches,
				       stwuct devwink_dpipe_vawue *action_vawues,
				       stwuct devwink_dpipe_action *actions)
{	stwuct devwink_dpipe_vawue *action_vawue;
	stwuct devwink_dpipe_vawue *match_vawue;
	stwuct devwink_dpipe_action *action;
	stwuct devwink_dpipe_match *match;

	entwy->match_vawues = match_vawues;
	entwy->match_vawues_count = MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_COUNT;

	entwy->action_vawues = action_vawues;
	entwy->action_vawues_count = MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_COUNT;

	match = &matches[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_INDEX];
	match_vawue = &match_vawues[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_INDEX];

	match_vawue->match = match;
	match_vawue->vawue_size = sizeof(u32);
	match_vawue->vawue = kmawwoc(match_vawue->vawue_size, GFP_KEWNEW);
	if (!match_vawue->vawue)
		wetuwn -ENOMEM;

	match = &matches[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_SIZE];
	match_vawue = &match_vawues[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_SIZE];

	match_vawue->match = match;
	match_vawue->vawue_size = sizeof(u32);
	match_vawue->vawue = kmawwoc(match_vawue->vawue_size, GFP_KEWNEW);
	if (!match_vawue->vawue)
		wetuwn -ENOMEM;

	match = &matches[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_HASH_INDEX];
	match_vawue = &match_vawues[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_HASH_INDEX];

	match_vawue->match = match;
	match_vawue->vawue_size = sizeof(u32);
	match_vawue->vawue = kmawwoc(match_vawue->vawue_size, GFP_KEWNEW);
	if (!match_vawue->vawue)
		wetuwn -ENOMEM;

	action = &actions[MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_DST_MAC];
	action_vawue = &action_vawues[MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_DST_MAC];

	action_vawue->action = action;
	action_vawue->vawue_size = sizeof(u64);
	action_vawue->vawue = kmawwoc(action_vawue->vawue_size, GFP_KEWNEW);
	if (!action_vawue->vawue)
		wetuwn -ENOMEM;

	action = &actions[MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_EWIF_POWT];
	action_vawue = &action_vawues[MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_EWIF_POWT];

	action_vawue->action = action;
	action_vawue->vawue_size = sizeof(u32);
	action_vawue->vawue = kmawwoc(action_vawue->vawue_size, GFP_KEWNEW);
	if (!action_vawue->vawue)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void
__mwxsw_sp_dpipe_tabwe_adj_entwy_fiww(stwuct devwink_dpipe_entwy *entwy,
				      u32 adj_index, u32 adj_size,
				      u32 adj_hash_index, unsigned chaw *ha,
				      stwuct mwxsw_sp_wif *wif)
{
	stwuct devwink_dpipe_vawue *vawue;
	u32 *p_wif_vawue;
	u32 *p_index;

	vawue = &entwy->match_vawues[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_INDEX];
	p_index = vawue->vawue;
	*p_index = adj_index;

	vawue = &entwy->match_vawues[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_SIZE];
	p_index = vawue->vawue;
	*p_index = adj_size;

	vawue = &entwy->match_vawues[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_HASH_INDEX];
	p_index = vawue->vawue;
	*p_index = adj_hash_index;

	vawue = &entwy->action_vawues[MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_DST_MAC];
	ethew_addw_copy(vawue->vawue, ha);

	vawue = &entwy->action_vawues[MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_EWIF_POWT];
	p_wif_vawue = vawue->vawue;
	*p_wif_vawue = mwxsw_sp_wif_index(wif);
	vawue->mapping_vawue = mwxsw_sp_wif_dev_ifindex(wif);
	vawue->mapping_vawid = twue;
}

static void mwxsw_sp_dpipe_tabwe_adj_entwy_fiww(stwuct mwxsw_sp *mwxsw_sp,
						stwuct mwxsw_sp_nexthop *nh,
						stwuct devwink_dpipe_entwy *entwy)
{
	stwuct mwxsw_sp_wif *wif = mwxsw_sp_nexthop_wif(nh);
	unsigned chaw *ha = mwxsw_sp_nexthop_ha(nh);
	u32 adj_hash_index = 0;
	u32 adj_index = 0;
	u32 adj_size = 0;
	int eww;

	mwxsw_sp_nexthop_indexes(nh, &adj_index, &adj_size, &adj_hash_index);
	__mwxsw_sp_dpipe_tabwe_adj_entwy_fiww(entwy, adj_index, adj_size,
					      adj_hash_index, ha, wif);
	eww = mwxsw_sp_nexthop_countew_get(mwxsw_sp, nh, &entwy->countew);
	if (!eww)
		entwy->countew_vawid = twue;
}

static int
mwxsw_sp_dpipe_tabwe_adj_entwies_get(stwuct mwxsw_sp *mwxsw_sp,
				     stwuct devwink_dpipe_entwy *entwy,
				     boow countews_enabwed,
				     stwuct devwink_dpipe_dump_ctx *dump_ctx)
{
	stwuct mwxsw_sp_nexthop *nh;
	int entwy_index = 0;
	int nh_count_max;
	int nh_count = 0;
	int nh_skip;
	int j;
	int eww;

	mutex_wock(&mwxsw_sp->woutew->wock);
	nh_count_max = mwxsw_sp_dpipe_tabwe_adj_size(mwxsw_sp);
stawt_again:
	eww = devwink_dpipe_entwy_ctx_pwepawe(dump_ctx);
	if (eww)
		goto eww_ctx_pwepawe;
	j = 0;
	nh_skip = nh_count;
	nh_count = 0;
	mwxsw_sp_nexthop_fow_each(nh, mwxsw_sp->woutew) {
		if (!mwxsw_sp_nexthop_is_fowwawd(nh) ||
		    mwxsw_sp_nexthop_gwoup_has_ipip(nh))
			continue;

		if (nh_count < nh_skip)
			goto skip;

		mwxsw_sp_dpipe_tabwe_adj_entwy_fiww(mwxsw_sp, nh, entwy);
		entwy->index = entwy_index;
		eww = devwink_dpipe_entwy_ctx_append(dump_ctx, entwy);
		if (eww) {
			if (eww == -EMSGSIZE) {
				if (!j)
					goto eww_entwy_append;
				bweak;
			}
			goto eww_entwy_append;
		}
		entwy_index++;
		j++;
skip:
		nh_count++;
	}

	devwink_dpipe_entwy_ctx_cwose(dump_ctx);
	if (nh_count != nh_count_max)
		goto stawt_again;
	mutex_unwock(&mwxsw_sp->woutew->wock);

	wetuwn 0;

eww_ctx_pwepawe:
eww_entwy_append:
	mutex_unwock(&mwxsw_sp->woutew->wock);
	wetuwn eww;
}

static int
mwxsw_sp_dpipe_tabwe_adj_entwies_dump(void *pwiv, boow countews_enabwed,
				      stwuct devwink_dpipe_dump_ctx *dump_ctx)
{
	stwuct devwink_dpipe_vawue action_vawues[MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_COUNT];
	stwuct devwink_dpipe_vawue match_vawues[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_COUNT];
	stwuct devwink_dpipe_action actions[MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_COUNT];
	stwuct devwink_dpipe_match matches[MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_COUNT];
	stwuct devwink_dpipe_entwy entwy = {0};
	stwuct mwxsw_sp *mwxsw_sp = pwiv;
	int eww;

	memset(matches, 0, MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_COUNT *
			   sizeof(matches[0]));
	memset(match_vawues, 0, MWXSW_SP_DPIPE_TABWE_ADJ_MATCH_COUNT *
				sizeof(match_vawues[0]));
	memset(actions, 0, MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_COUNT *
			   sizeof(actions[0]));
	memset(action_vawues, 0, MWXSW_SP_DPIPE_TABWE_ADJ_ACTION_COUNT *
				 sizeof(action_vawues[0]));

	mwxsw_sp_dpipe_tabwe_adj_match_action_pwepawe(matches, actions);
	eww = mwxsw_sp_dpipe_tabwe_adj_entwy_pwepawe(&entwy,
						     match_vawues, matches,
						     action_vawues, actions);
	if (eww)
		goto out;

	eww = mwxsw_sp_dpipe_tabwe_adj_entwies_get(mwxsw_sp, &entwy,
						   countews_enabwed, dump_ctx);
out:
	devwink_dpipe_entwy_cweaw(&entwy);
	wetuwn eww;
}

static int mwxsw_sp_dpipe_tabwe_adj_countews_update(void *pwiv, boow enabwe)
{
	chaw watw_pw[MWXSW_WEG_WATW_WEN];
	stwuct mwxsw_sp *mwxsw_sp = pwiv;
	stwuct mwxsw_sp_nexthop *nh;
	u32 adj_hash_index = 0;
	u32 adj_index = 0;
	u32 adj_size = 0;

	mwxsw_sp_nexthop_fow_each(nh, mwxsw_sp->woutew) {
		if (!mwxsw_sp_nexthop_is_fowwawd(nh) ||
		    mwxsw_sp_nexthop_gwoup_has_ipip(nh))
			continue;

		mwxsw_sp_nexthop_indexes(nh, &adj_index, &adj_size,
					 &adj_hash_index);
		if (enabwe)
			mwxsw_sp_nexthop_countew_awwoc(mwxsw_sp, nh);
		ewse
			mwxsw_sp_nexthop_countew_fwee(mwxsw_sp, nh);
		mwxsw_sp_nexthop_eth_update(mwxsw_sp,
					    adj_index + adj_hash_index, nh,
					    twue, watw_pw);
	}
	wetuwn 0;
}

static u64
mwxsw_sp_dpipe_tabwe_adj_size_get(void *pwiv)
{
	stwuct mwxsw_sp *mwxsw_sp = pwiv;
	u64 size;

	mutex_wock(&mwxsw_sp->woutew->wock);
	size = mwxsw_sp_dpipe_tabwe_adj_size(mwxsw_sp);
	mutex_unwock(&mwxsw_sp->woutew->wock);

	wetuwn size;
}

static stwuct devwink_dpipe_tabwe_ops mwxsw_sp_dpipe_tabwe_adj_ops = {
	.matches_dump = mwxsw_sp_dpipe_tabwe_adj_matches_dump,
	.actions_dump = mwxsw_sp_dpipe_tabwe_adj_actions_dump,
	.entwies_dump = mwxsw_sp_dpipe_tabwe_adj_entwies_dump,
	.countews_set_update = mwxsw_sp_dpipe_tabwe_adj_countews_update,
	.size_get = mwxsw_sp_dpipe_tabwe_adj_size_get,
};

#define MWXSW_SP_DPIPE_TABWE_WESOUWCE_UNIT_ADJ 1

static int mwxsw_sp_dpipe_adj_tabwe_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	int eww;

	eww = devw_dpipe_tabwe_wegistew(devwink,
					MWXSW_SP_DPIPE_TABWE_NAME_ADJ,
					&mwxsw_sp_dpipe_tabwe_adj_ops,
					mwxsw_sp, fawse);
	if (eww)
		wetuwn eww;

	eww = devw_dpipe_tabwe_wesouwce_set(devwink,
					    MWXSW_SP_DPIPE_TABWE_NAME_ADJ,
					    MWXSW_SP_WESOUWCE_KVD_WINEAW,
					    MWXSW_SP_DPIPE_TABWE_WESOUWCE_UNIT_ADJ);
	if (eww)
		goto eww_wesouwce_set;

	wetuwn 0;

eww_wesouwce_set:
	devw_dpipe_tabwe_unwegistew(devwink,
				    MWXSW_SP_DPIPE_TABWE_NAME_ADJ);
	wetuwn eww;
}

static void mwxsw_sp_dpipe_adj_tabwe_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);

	devw_dpipe_tabwe_unwegistew(devwink,
				    MWXSW_SP_DPIPE_TABWE_NAME_ADJ);
}

int mwxsw_sp_dpipe_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	int eww;

	devw_dpipe_headews_wegistew(devwink, &mwxsw_sp_dpipe_headews);

	eww = mwxsw_sp_dpipe_ewif_tabwe_init(mwxsw_sp);
	if (eww)
		goto eww_ewif_tabwe_init;

	eww = mwxsw_sp_dpipe_host4_tabwe_init(mwxsw_sp);
	if (eww)
		goto eww_host4_tabwe_init;

	eww = mwxsw_sp_dpipe_host6_tabwe_init(mwxsw_sp);
	if (eww)
		goto eww_host6_tabwe_init;

	eww = mwxsw_sp_dpipe_adj_tabwe_init(mwxsw_sp);
	if (eww)
		goto eww_adj_tabwe_init;

	wetuwn 0;
eww_adj_tabwe_init:
	mwxsw_sp_dpipe_host6_tabwe_fini(mwxsw_sp);
eww_host6_tabwe_init:
	mwxsw_sp_dpipe_host4_tabwe_fini(mwxsw_sp);
eww_host4_tabwe_init:
	mwxsw_sp_dpipe_ewif_tabwe_fini(mwxsw_sp);
eww_ewif_tabwe_init:
	devw_dpipe_headews_unwegistew(pwiv_to_devwink(mwxsw_sp->cowe));
	wetuwn eww;
}

void mwxsw_sp_dpipe_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);

	mwxsw_sp_dpipe_adj_tabwe_fini(mwxsw_sp);
	mwxsw_sp_dpipe_host6_tabwe_fini(mwxsw_sp);
	mwxsw_sp_dpipe_host4_tabwe_fini(mwxsw_sp);
	mwxsw_sp_dpipe_ewif_tabwe_fini(mwxsw_sp);
	devw_dpipe_headews_unwegistew(devwink);
}
