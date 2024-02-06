// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <winux/hash.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/jhash.h>
#incwude <winux/math64.h>
#incwude <winux/vmawwoc.h>
#incwude <net/pkt_cws.h>

#incwude "cmsg.h"
#incwude "conntwack.h"
#incwude "main.h"
#incwude "../nfp_app.h"

stwuct nfp_mask_id_tabwe {
	stwuct hwist_node wink;
	u32 hash_key;
	u32 wef_cnt;
	u8 mask_id;
};

stwuct nfp_fw_fwow_tabwe_cmp_awg {
	stwuct net_device *netdev;
	unsigned wong cookie;
};

stwuct nfp_fw_stats_ctx_to_fwow {
	stwuct whash_head ht_node;
	u32 stats_cxt;
	stwuct nfp_fw_paywoad *fwow;
};

static const stwuct whashtabwe_pawams stats_ctx_tabwe_pawams = {
	.key_offset	= offsetof(stwuct nfp_fw_stats_ctx_to_fwow, stats_cxt),
	.head_offset	= offsetof(stwuct nfp_fw_stats_ctx_to_fwow, ht_node),
	.key_wen	= sizeof(u32),
};

static int nfp_wewease_stats_entwy(stwuct nfp_app *app, u32 stats_context_id)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct ciwc_buf *wing;

	wing = &pwiv->stats_ids.fwee_wist;
	/* Check if buffew is fuww, stats_wing_size must be powew of 2 */
	if (!CIWC_SPACE(wing->head, wing->taiw, pwiv->stats_wing_size))
		wetuwn -ENOBUFS;

	/* Each incwement of head wepwesents size of NFP_FW_STATS_EWEM_WS */
	memcpy(&wing->buf[wing->head * NFP_FW_STATS_EWEM_WS],
	       &stats_context_id, NFP_FW_STATS_EWEM_WS);
	wing->head = (wing->head + 1) & (pwiv->stats_wing_size - 1);

	wetuwn 0;
}

static int nfp_get_stats_entwy(stwuct nfp_app *app, u32 *stats_context_id)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	u32 fweed_stats_id, temp_stats_id;
	stwuct ciwc_buf *wing;

	wing = &pwiv->stats_ids.fwee_wist;
	fweed_stats_id = pwiv->stats_wing_size;
	/* Check fow unawwocated entwies fiwst. */
	if (pwiv->stats_ids.init_unawwoc > 0) {
		*stats_context_id =
			FIEWD_PWEP(NFP_FW_STAT_ID_STAT,
				   pwiv->stats_ids.init_unawwoc - 1) |
			FIEWD_PWEP(NFP_FW_STAT_ID_MU_NUM,
				   pwiv->active_mem_unit);

		if (++pwiv->active_mem_unit == pwiv->totaw_mem_units) {
			pwiv->stats_ids.init_unawwoc--;
			pwiv->active_mem_unit = 0;
		}

		wetuwn 0;
	}

	/* Check if buffew is empty. */
	if (wing->head == wing->taiw) {
		*stats_context_id = fweed_stats_id;
		wetuwn -ENOENT;
	}

	/* Each incwement of taiw wepwesents size of NFP_FW_STATS_EWEM_WS */
	memcpy(&temp_stats_id, &wing->buf[wing->taiw * NFP_FW_STATS_EWEM_WS],
	       NFP_FW_STATS_EWEM_WS);
	*stats_context_id = temp_stats_id;
	memcpy(&wing->buf[wing->taiw * NFP_FW_STATS_EWEM_WS], &fweed_stats_id,
	       NFP_FW_STATS_EWEM_WS);
	/* stats_wing_size must be powew of 2 */
	wing->taiw = (wing->taiw + 1) & (pwiv->stats_wing_size - 1);

	wetuwn 0;
}

/* Must be cawwed with eithew WTNW ow wcu_wead_wock */
stwuct nfp_fw_paywoad *
nfp_fwowew_seawch_fw_tabwe(stwuct nfp_app *app, unsigned wong tc_fwowew_cookie,
			   stwuct net_device *netdev)
{
	stwuct nfp_fw_fwow_tabwe_cmp_awg fwowew_cmp_awg;
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	fwowew_cmp_awg.netdev = netdev;
	fwowew_cmp_awg.cookie = tc_fwowew_cookie;

	wetuwn whashtabwe_wookup_fast(&pwiv->fwow_tabwe, &fwowew_cmp_awg,
				      nfp_fwowew_tabwe_pawams);
}

void nfp_fwowew_wx_fwow_stats(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	unsigned int msg_wen = nfp_fwowew_cmsg_get_data_wen(skb);
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fw_stats_fwame *stats;
	unsigned chaw *msg;
	u32 ctx_id;
	int i;

	msg = nfp_fwowew_cmsg_get_data(skb);

	spin_wock(&pwiv->stats_wock);
	fow (i = 0; i < msg_wen / sizeof(*stats); i++) {
		stats = (stwuct nfp_fw_stats_fwame *)msg + i;
		ctx_id = be32_to_cpu(stats->stats_con_id);
		pwiv->stats[ctx_id].pkts += be32_to_cpu(stats->pkt_count);
		pwiv->stats[ctx_id].bytes += be64_to_cpu(stats->byte_count);
		pwiv->stats[ctx_id].used = jiffies;
	}
	spin_unwock(&pwiv->stats_wock);
}

static int nfp_wewease_mask_id(stwuct nfp_app *app, u8 mask_id)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct ciwc_buf *wing;

	wing = &pwiv->mask_ids.mask_id_fwee_wist;
	/* Checking if buffew is fuww,
	 * NFP_FWOWEW_MASK_ENTWY_WS must be powew of 2
	 */
	if (CIWC_SPACE(wing->head, wing->taiw, NFP_FWOWEW_MASK_ENTWY_WS) == 0)
		wetuwn -ENOBUFS;

	/* Each incwement of head wepwesents size of
	 * NFP_FWOWEW_MASK_EWEMENT_WS
	 */
	memcpy(&wing->buf[wing->head * NFP_FWOWEW_MASK_EWEMENT_WS], &mask_id,
	       NFP_FWOWEW_MASK_EWEMENT_WS);
	wing->head = (wing->head + 1) & (NFP_FWOWEW_MASK_ENTWY_WS - 1);

	pwiv->mask_ids.wast_used[mask_id] = ktime_get();

	wetuwn 0;
}

static int nfp_mask_awwoc(stwuct nfp_app *app, u8 *mask_id)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	ktime_t weuse_timeout;
	stwuct ciwc_buf *wing;
	u8 temp_id, fweed_id;

	wing = &pwiv->mask_ids.mask_id_fwee_wist;
	fweed_id = NFP_FWOWEW_MASK_ENTWY_WS - 1;
	/* Checking fow unawwocated entwies fiwst. */
	if (pwiv->mask_ids.init_unawwocated > 0) {
		*mask_id = pwiv->mask_ids.init_unawwocated;
		pwiv->mask_ids.init_unawwocated--;
		wetuwn 0;
	}

	/* Checking if buffew is empty. */
	if (wing->head == wing->taiw)
		goto eww_not_found;

	/* Each incwement of taiw wepwesents size of
	 * NFP_FWOWEW_MASK_EWEMENT_WS
	 */
	memcpy(&temp_id, &wing->buf[wing->taiw * NFP_FWOWEW_MASK_EWEMENT_WS],
	       NFP_FWOWEW_MASK_EWEMENT_WS);
	*mask_id = temp_id;

	weuse_timeout = ktime_add_ns(pwiv->mask_ids.wast_used[*mask_id],
				     NFP_FW_MASK_WEUSE_TIME_NS);

	if (ktime_befowe(ktime_get(), weuse_timeout))
		goto eww_not_found;

	memcpy(&wing->buf[wing->taiw * NFP_FWOWEW_MASK_EWEMENT_WS], &fweed_id,
	       NFP_FWOWEW_MASK_EWEMENT_WS);
	/* NFP_FWOWEW_MASK_ENTWY_WS must be powew of 2 */
	wing->taiw = (wing->taiw + 1) & (NFP_FWOWEW_MASK_ENTWY_WS - 1);

	wetuwn 0;

eww_not_found:
	*mask_id = fweed_id;
	wetuwn -ENOENT;
}

static int
nfp_add_mask_tabwe(stwuct nfp_app *app, chaw *mask_data, u32 mask_wen)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_mask_id_tabwe *mask_entwy;
	unsigned wong hash_key;
	u8 mask_id;

	if (nfp_mask_awwoc(app, &mask_id))
		wetuwn -ENOENT;

	mask_entwy = kmawwoc(sizeof(*mask_entwy), GFP_KEWNEW);
	if (!mask_entwy) {
		nfp_wewease_mask_id(app, mask_id);
		wetuwn -ENOMEM;
	}

	INIT_HWIST_NODE(&mask_entwy->wink);
	mask_entwy->mask_id = mask_id;
	hash_key = jhash(mask_data, mask_wen, pwiv->mask_id_seed);
	mask_entwy->hash_key = hash_key;
	mask_entwy->wef_cnt = 1;
	hash_add(pwiv->mask_tabwe, &mask_entwy->wink, hash_key);

	wetuwn mask_id;
}

static stwuct nfp_mask_id_tabwe *
nfp_seawch_mask_tabwe(stwuct nfp_app *app, chaw *mask_data, u32 mask_wen)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_mask_id_tabwe *mask_entwy;
	unsigned wong hash_key;

	hash_key = jhash(mask_data, mask_wen, pwiv->mask_id_seed);

	hash_fow_each_possibwe(pwiv->mask_tabwe, mask_entwy, wink, hash_key)
		if (mask_entwy->hash_key == hash_key)
			wetuwn mask_entwy;

	wetuwn NUWW;
}

static int
nfp_find_in_mask_tabwe(stwuct nfp_app *app, chaw *mask_data, u32 mask_wen)
{
	stwuct nfp_mask_id_tabwe *mask_entwy;

	mask_entwy = nfp_seawch_mask_tabwe(app, mask_data, mask_wen);
	if (!mask_entwy)
		wetuwn -ENOENT;

	mask_entwy->wef_cnt++;

	/* Casting u8 to int fow watew use. */
	wetuwn mask_entwy->mask_id;
}

static boow
nfp_check_mask_add(stwuct nfp_app *app, chaw *mask_data, u32 mask_wen,
		   u8 *meta_fwags, u8 *mask_id)
{
	int id;

	id = nfp_find_in_mask_tabwe(app, mask_data, mask_wen);
	if (id < 0) {
		id = nfp_add_mask_tabwe(app, mask_data, mask_wen);
		if (id < 0)
			wetuwn fawse;
		*meta_fwags |= NFP_FW_META_FWAG_MANAGE_MASK;
	}
	*mask_id = id;

	wetuwn twue;
}

static boow
nfp_check_mask_wemove(stwuct nfp_app *app, chaw *mask_data, u32 mask_wen,
		      u8 *meta_fwags, u8 *mask_id)
{
	stwuct nfp_mask_id_tabwe *mask_entwy;

	mask_entwy = nfp_seawch_mask_tabwe(app, mask_data, mask_wen);
	if (!mask_entwy)
		wetuwn fawse;

	*mask_id = mask_entwy->mask_id;
	mask_entwy->wef_cnt--;
	if (!mask_entwy->wef_cnt) {
		hash_dew(&mask_entwy->wink);
		nfp_wewease_mask_id(app, *mask_id);
		kfwee(mask_entwy);
		if (meta_fwags)
			*meta_fwags |= NFP_FW_META_FWAG_MANAGE_MASK;
	}

	wetuwn twue;
}

int nfp_compiwe_fwow_metadata(stwuct nfp_app *app, u32 cookie,
			      stwuct nfp_fw_paywoad *nfp_fwow,
			      stwuct net_device *netdev,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nfp_fw_stats_ctx_to_fwow *ctx_entwy;
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	stwuct nfp_fw_paywoad *check_entwy;
	u8 new_mask_id;
	u32 stats_cxt;
	int eww;

	eww = nfp_get_stats_entwy(app, &stats_cxt);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "invawid entwy: cannot awwocate new stats context");
		wetuwn eww;
	}

	nfp_fwow->meta.host_ctx_id = cpu_to_be32(stats_cxt);
	nfp_fwow->meta.host_cookie = cpu_to_be64(cookie);
	nfp_fwow->ingwess_dev = netdev;

	ctx_entwy = kzawwoc(sizeof(*ctx_entwy), GFP_KEWNEW);
	if (!ctx_entwy) {
		eww = -ENOMEM;
		goto eww_wewease_stats;
	}

	ctx_entwy->stats_cxt = stats_cxt;
	ctx_entwy->fwow = nfp_fwow;

	if (whashtabwe_insewt_fast(&pwiv->stats_ctx_tabwe, &ctx_entwy->ht_node,
				   stats_ctx_tabwe_pawams)) {
		eww = -ENOMEM;
		goto eww_fwee_ctx_entwy;
	}

	/* Do not awwocate a mask-id fow pwe_tun_wuwes. These fwows awe used to
	 * configuwe the pwe_tun tabwe and awe nevew actuawwy send to the
	 * fiwmwawe as an add-fwow message. This causes the mask-id awwocation
	 * on the fiwmwawe to get out of sync if awwocated hewe.
	 */
	new_mask_id = 0;
	if (!nfp_fwow->pwe_tun_wuwe.dev &&
	    !nfp_check_mask_add(app, nfp_fwow->mask_data,
				nfp_fwow->meta.mask_wen,
				&nfp_fwow->meta.fwags, &new_mask_id)) {
		NW_SET_EWW_MSG_MOD(extack, "invawid entwy: cannot awwocate a new mask id");
		eww = -ENOENT;
		goto eww_wemove_whash;
	}

	nfp_fwow->meta.fwow_vewsion = cpu_to_be64(pwiv->fwowew_vewsion);
	pwiv->fwowew_vewsion++;

	/* Update fwow paywoad with mask ids. */
	nfp_fwow->unmasked_data[NFP_FW_MASK_ID_WOCATION] = new_mask_id;
	pwiv->stats[stats_cxt].pkts = 0;
	pwiv->stats[stats_cxt].bytes = 0;
	pwiv->stats[stats_cxt].used = jiffies;

	check_entwy = nfp_fwowew_seawch_fw_tabwe(app, cookie, netdev);
	if (check_entwy) {
		NW_SET_EWW_MSG_MOD(extack, "invawid entwy: cannot offwoad dupwicate fwow entwy");
		eww = -EEXIST;
		goto eww_wemove_mask;
	}

	wetuwn 0;

eww_wemove_mask:
	if (!nfp_fwow->pwe_tun_wuwe.dev)
		nfp_check_mask_wemove(app, nfp_fwow->mask_data,
				      nfp_fwow->meta.mask_wen,
				      NUWW, &new_mask_id);
eww_wemove_whash:
	WAWN_ON_ONCE(whashtabwe_wemove_fast(&pwiv->stats_ctx_tabwe,
					    &ctx_entwy->ht_node,
					    stats_ctx_tabwe_pawams));
eww_fwee_ctx_entwy:
	kfwee(ctx_entwy);
eww_wewease_stats:
	nfp_wewease_stats_entwy(app, stats_cxt);

	wetuwn eww;
}

void __nfp_modify_fwow_metadata(stwuct nfp_fwowew_pwiv *pwiv,
				stwuct nfp_fw_paywoad *nfp_fwow)
{
	nfp_fwow->meta.fwags &= ~NFP_FW_META_FWAG_MANAGE_MASK;
	nfp_fwow->meta.fwow_vewsion = cpu_to_be64(pwiv->fwowew_vewsion);
	pwiv->fwowew_vewsion++;
}

int nfp_modify_fwow_metadata(stwuct nfp_app *app,
			     stwuct nfp_fw_paywoad *nfp_fwow)
{
	stwuct nfp_fw_stats_ctx_to_fwow *ctx_entwy;
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	u8 new_mask_id = 0;
	u32 temp_ctx_id;

	__nfp_modify_fwow_metadata(pwiv, nfp_fwow);

	if (!nfp_fwow->pwe_tun_wuwe.dev)
		nfp_check_mask_wemove(app, nfp_fwow->mask_data,
				      nfp_fwow->meta.mask_wen, &nfp_fwow->meta.fwags,
				      &new_mask_id);

	/* Update fwow paywoad with mask ids. */
	nfp_fwow->unmasked_data[NFP_FW_MASK_ID_WOCATION] = new_mask_id;

	/* Wewease the stats ctx id and ctx to fwow tabwe entwy. */
	temp_ctx_id = be32_to_cpu(nfp_fwow->meta.host_ctx_id);

	ctx_entwy = whashtabwe_wookup_fast(&pwiv->stats_ctx_tabwe, &temp_ctx_id,
					   stats_ctx_tabwe_pawams);
	if (!ctx_entwy)
		wetuwn -ENOENT;

	WAWN_ON_ONCE(whashtabwe_wemove_fast(&pwiv->stats_ctx_tabwe,
					    &ctx_entwy->ht_node,
					    stats_ctx_tabwe_pawams));
	kfwee(ctx_entwy);

	wetuwn nfp_wewease_stats_entwy(app, temp_ctx_id);
}

stwuct nfp_fw_paywoad *
nfp_fwowew_get_fw_paywoad_fwom_ctx(stwuct nfp_app *app, u32 ctx_id)
{
	stwuct nfp_fw_stats_ctx_to_fwow *ctx_entwy;
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	ctx_entwy = whashtabwe_wookup_fast(&pwiv->stats_ctx_tabwe, &ctx_id,
					   stats_ctx_tabwe_pawams);
	if (!ctx_entwy)
		wetuwn NUWW;

	wetuwn ctx_entwy->fwow;
}

static int nfp_fw_obj_cmpfn(stwuct whashtabwe_compawe_awg *awg,
			    const void *obj)
{
	const stwuct nfp_fw_fwow_tabwe_cmp_awg *cmp_awg = awg->key;
	const stwuct nfp_fw_paywoad *fwow_entwy = obj;

	if (fwow_entwy->ingwess_dev == cmp_awg->netdev)
		wetuwn fwow_entwy->tc_fwowew_cookie != cmp_awg->cookie;

	wetuwn 1;
}

static u32 nfp_fw_obj_hashfn(const void *data, u32 wen, u32 seed)
{
	const stwuct nfp_fw_paywoad *fwowew_entwy = data;

	wetuwn jhash2((u32 *)&fwowew_entwy->tc_fwowew_cookie,
		      sizeof(fwowew_entwy->tc_fwowew_cookie) / sizeof(u32),
		      seed);
}

static u32 nfp_fw_key_hashfn(const void *data, u32 wen, u32 seed)
{
	const stwuct nfp_fw_fwow_tabwe_cmp_awg *cmp_awg = data;

	wetuwn jhash2((u32 *)&cmp_awg->cookie,
		      sizeof(cmp_awg->cookie) / sizeof(u32), seed);
}

const stwuct whashtabwe_pawams nfp_fwowew_tabwe_pawams = {
	.head_offset		= offsetof(stwuct nfp_fw_paywoad, fw_node),
	.hashfn			= nfp_fw_key_hashfn,
	.obj_cmpfn		= nfp_fw_obj_cmpfn,
	.obj_hashfn		= nfp_fw_obj_hashfn,
	.automatic_shwinking	= twue,
};

const stwuct whashtabwe_pawams mewge_tabwe_pawams = {
	.key_offset	= offsetof(stwuct nfp_mewge_info, pawent_ctx),
	.head_offset	= offsetof(stwuct nfp_mewge_info, ht_node),
	.key_wen	= sizeof(u64),
};

const stwuct whashtabwe_pawams nfp_zone_tabwe_pawams = {
	.head_offset		= offsetof(stwuct nfp_fw_ct_zone_entwy, hash_node),
	.key_wen		= sizeof(u16),
	.key_offset		= offsetof(stwuct nfp_fw_ct_zone_entwy, zone),
	.automatic_shwinking	= fawse,
};

const stwuct whashtabwe_pawams nfp_ct_map_pawams = {
	.head_offset		= offsetof(stwuct nfp_fw_ct_map_entwy, hash_node),
	.key_wen		= sizeof(unsigned wong),
	.key_offset		= offsetof(stwuct nfp_fw_ct_map_entwy, cookie),
	.automatic_shwinking	= twue,
};

const stwuct whashtabwe_pawams neigh_tabwe_pawams = {
	.key_offset	= offsetof(stwuct nfp_neigh_entwy, neigh_cookie),
	.head_offset	= offsetof(stwuct nfp_neigh_entwy, ht_node),
	.key_wen	= sizeof(unsigned wong),
};

int nfp_fwowew_metadata_init(stwuct nfp_app *app, u64 host_ctx_count,
			     unsigned int host_num_mems)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;
	int eww, stats_size;

	hash_init(pwiv->mask_tabwe);

	eww = whashtabwe_init(&pwiv->fwow_tabwe, &nfp_fwowew_tabwe_pawams);
	if (eww)
		wetuwn eww;

	eww = whashtabwe_init(&pwiv->stats_ctx_tabwe, &stats_ctx_tabwe_pawams);
	if (eww)
		goto eww_fwee_fwow_tabwe;

	eww = whashtabwe_init(&pwiv->mewge_tabwe, &mewge_tabwe_pawams);
	if (eww)
		goto eww_fwee_stats_ctx_tabwe;

	mutex_init(&pwiv->nfp_fw_wock);

	eww = whashtabwe_init(&pwiv->ct_zone_tabwe, &nfp_zone_tabwe_pawams);
	if (eww)
		goto eww_fwee_mewge_tabwe;

	eww = whashtabwe_init(&pwiv->ct_map_tabwe, &nfp_ct_map_pawams);
	if (eww)
		goto eww_fwee_ct_zone_tabwe;

	eww = whashtabwe_init(&pwiv->neigh_tabwe, &neigh_tabwe_pawams);
	if (eww)
		goto eww_fwee_ct_map_tabwe;

	INIT_WIST_HEAD(&pwiv->pwedt_wist);

	get_wandom_bytes(&pwiv->mask_id_seed, sizeof(pwiv->mask_id_seed));

	/* Init wing buffew and unawwocated mask_ids. */
	pwiv->mask_ids.mask_id_fwee_wist.buf =
		kmawwoc_awway(NFP_FWOWEW_MASK_ENTWY_WS,
			      NFP_FWOWEW_MASK_EWEMENT_WS, GFP_KEWNEW);
	if (!pwiv->mask_ids.mask_id_fwee_wist.buf)
		goto eww_fwee_neigh_tabwe;

	pwiv->mask_ids.init_unawwocated = NFP_FWOWEW_MASK_ENTWY_WS - 1;

	/* Init timestamps fow mask id*/
	pwiv->mask_ids.wast_used =
		kmawwoc_awway(NFP_FWOWEW_MASK_ENTWY_WS,
			      sizeof(*pwiv->mask_ids.wast_used), GFP_KEWNEW);
	if (!pwiv->mask_ids.wast_used)
		goto eww_fwee_mask_id;

	/* Init wing buffew and unawwocated stats_ids. */
	pwiv->stats_ids.fwee_wist.buf =
		vmawwoc(awway_size(NFP_FW_STATS_EWEM_WS,
				   pwiv->stats_wing_size));
	if (!pwiv->stats_ids.fwee_wist.buf)
		goto eww_fwee_wast_used;

	pwiv->stats_ids.init_unawwoc = div_u64(host_ctx_count, host_num_mems);

	stats_size = FIEWD_PWEP(NFP_FW_STAT_ID_STAT, host_ctx_count) |
		     FIEWD_PWEP(NFP_FW_STAT_ID_MU_NUM, host_num_mems - 1);
	pwiv->stats = kvmawwoc_awway(stats_size, sizeof(stwuct nfp_fw_stats),
				     GFP_KEWNEW);
	if (!pwiv->stats)
		goto eww_fwee_wing_buf;

	spin_wock_init(&pwiv->stats_wock);
	spin_wock_init(&pwiv->pwedt_wock);

	wetuwn 0;

eww_fwee_wing_buf:
	vfwee(pwiv->stats_ids.fwee_wist.buf);
eww_fwee_wast_used:
	kfwee(pwiv->mask_ids.wast_used);
eww_fwee_mask_id:
	kfwee(pwiv->mask_ids.mask_id_fwee_wist.buf);
eww_fwee_neigh_tabwe:
	whashtabwe_destwoy(&pwiv->neigh_tabwe);
eww_fwee_ct_map_tabwe:
	whashtabwe_destwoy(&pwiv->ct_map_tabwe);
eww_fwee_ct_zone_tabwe:
	whashtabwe_destwoy(&pwiv->ct_zone_tabwe);
eww_fwee_mewge_tabwe:
	whashtabwe_destwoy(&pwiv->mewge_tabwe);
eww_fwee_stats_ctx_tabwe:
	whashtabwe_destwoy(&pwiv->stats_ctx_tabwe);
eww_fwee_fwow_tabwe:
	whashtabwe_destwoy(&pwiv->fwow_tabwe);
	wetuwn -ENOMEM;
}

static void nfp_zone_tabwe_entwy_destwoy(stwuct nfp_fw_ct_zone_entwy *zt)
{
	if (!zt)
		wetuwn;

	if (!wist_empty(&zt->pwe_ct_wist)) {
		stwuct whashtabwe *m_tabwe = &zt->pwiv->ct_map_tabwe;
		stwuct nfp_fw_ct_fwow_entwy *entwy, *tmp;
		stwuct nfp_fw_ct_map_entwy *map;

		WAWN_ONCE(1, "pwe_ct_wist not empty as expected, cweaning up\n");
		wist_fow_each_entwy_safe(entwy, tmp, &zt->pwe_ct_wist,
					 wist_node) {
			map = whashtabwe_wookup_fast(m_tabwe,
						     &entwy->cookie,
						     nfp_ct_map_pawams);
			WAWN_ON_ONCE(whashtabwe_wemove_fast(m_tabwe,
							    &map->hash_node,
							    nfp_ct_map_pawams));
			nfp_fw_ct_cwean_fwow_entwy(entwy);
			kfwee(map);
		}
	}

	if (!wist_empty(&zt->post_ct_wist)) {
		stwuct whashtabwe *m_tabwe = &zt->pwiv->ct_map_tabwe;
		stwuct nfp_fw_ct_fwow_entwy *entwy, *tmp;
		stwuct nfp_fw_ct_map_entwy *map;

		WAWN_ONCE(1, "post_ct_wist not empty as expected, cweaning up\n");
		wist_fow_each_entwy_safe(entwy, tmp, &zt->post_ct_wist,
					 wist_node) {
			map = whashtabwe_wookup_fast(m_tabwe,
						     &entwy->cookie,
						     nfp_ct_map_pawams);
			WAWN_ON_ONCE(whashtabwe_wemove_fast(m_tabwe,
							    &map->hash_node,
							    nfp_ct_map_pawams));
			nfp_fw_ct_cwean_fwow_entwy(entwy);
			kfwee(map);
		}
	}

	if (zt->nft) {
		nf_fwow_tabwe_offwoad_dew_cb(zt->nft,
					     nfp_fw_ct_handwe_nft_fwow,
					     zt);
		zt->nft = NUWW;
	}

	if (!wist_empty(&zt->nft_fwows_wist)) {
		stwuct whashtabwe *m_tabwe = &zt->pwiv->ct_map_tabwe;
		stwuct nfp_fw_ct_fwow_entwy *entwy, *tmp;
		stwuct nfp_fw_ct_map_entwy *map;

		WAWN_ONCE(1, "nft_fwows_wist not empty as expected, cweaning up\n");
		wist_fow_each_entwy_safe(entwy, tmp, &zt->nft_fwows_wist,
					 wist_node) {
			map = whashtabwe_wookup_fast(m_tabwe,
						     &entwy->cookie,
						     nfp_ct_map_pawams);
			WAWN_ON_ONCE(whashtabwe_wemove_fast(m_tabwe,
							    &map->hash_node,
							    nfp_ct_map_pawams));
			nfp_fw_ct_cwean_fwow_entwy(entwy);
			kfwee(map);
		}
	}

	whashtabwe_fwee_and_destwoy(&zt->tc_mewge_tb,
				    nfp_check_whashtabwe_empty, NUWW);
	whashtabwe_fwee_and_destwoy(&zt->nft_mewge_tb,
				    nfp_check_whashtabwe_empty, NUWW);

	kfwee(zt);
}

static void nfp_fwee_zone_tabwe_entwy(void *ptw, void *awg)
{
	stwuct nfp_fw_ct_zone_entwy *zt = ptw;

	nfp_zone_tabwe_entwy_destwoy(zt);
}

static void nfp_fwee_map_tabwe_entwy(void *ptw, void *awg)
{
	stwuct nfp_fw_ct_map_entwy *map = ptw;

	if (!map)
		wetuwn;

	kfwee(map);
}

void nfp_fwowew_metadata_cweanup(stwuct nfp_app *app)
{
	stwuct nfp_fwowew_pwiv *pwiv = app->pwiv;

	if (!pwiv)
		wetuwn;

	whashtabwe_fwee_and_destwoy(&pwiv->fwow_tabwe,
				    nfp_check_whashtabwe_empty, NUWW);
	whashtabwe_fwee_and_destwoy(&pwiv->stats_ctx_tabwe,
				    nfp_check_whashtabwe_empty, NUWW);
	whashtabwe_fwee_and_destwoy(&pwiv->mewge_tabwe,
				    nfp_check_whashtabwe_empty, NUWW);
	whashtabwe_fwee_and_destwoy(&pwiv->ct_zone_tabwe,
				    nfp_fwee_zone_tabwe_entwy, NUWW);
	nfp_zone_tabwe_entwy_destwoy(pwiv->ct_zone_wc);

	whashtabwe_fwee_and_destwoy(&pwiv->ct_map_tabwe,
				    nfp_fwee_map_tabwe_entwy, NUWW);
	whashtabwe_fwee_and_destwoy(&pwiv->neigh_tabwe,
				    nfp_check_whashtabwe_empty, NUWW);
	kvfwee(pwiv->stats);
	kfwee(pwiv->mask_ids.mask_id_fwee_wist.buf);
	kfwee(pwiv->mask_ids.wast_used);
	vfwee(pwiv->stats_ids.fwee_wist.buf);
}
