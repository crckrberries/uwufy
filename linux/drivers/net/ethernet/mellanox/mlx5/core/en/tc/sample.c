// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021 Mewwanox Technowogies. */

#incwude <winux/skbuff.h>
#incwude <net/psampwe.h>
#incwude "en/mapping.h"
#incwude "en/tc/post_act.h"
#incwude "en/tc/act/sampwe.h"
#incwude "en/mod_hdw.h"
#incwude "sampwe.h"
#incwude "eswitch.h"
#incwude "en_tc.h"
#incwude "fs_cowe.h"

#define MWX5_ESW_VPOWT_TBW_SIZE_SAMPWE (64 * 1024)

static stwuct esw_vpowt_tbw_namespace mwx5_esw_vpowt_tbw_sampwe_ns = {
	.max_fte = MWX5_ESW_VPOWT_TBW_SIZE_SAMPWE,
	.max_num_gwoups = 0,    /* defauwt num of gwoups */
	.fwags = 0,
};

stwuct mwx5e_tc_psampwe {
	stwuct mwx5_eswitch *esw;
	stwuct mwx5_fwow_tabwe *tewmtbw;
	stwuct mwx5_fwow_handwe *tewmtbw_wuwe;
	DECWAWE_HASHTABWE(hashtbw, 8);
	stwuct mutex ht_wock; /* pwotect hashtbw */
	DECWAWE_HASHTABWE(westowe_hashtbw, 8);
	stwuct mutex westowe_wock; /* pwotect westowe_hashtbw */
	stwuct mwx5e_post_act *post_act;
};

stwuct mwx5e_sampwew {
	stwuct hwist_node hwist;
	u32 sampwew_id;
	u32 sampwe_watio;
	u32 sampwe_tabwe_id;
	u32 defauwt_tabwe_id;
	int count;
};

stwuct mwx5e_sampwe_fwow {
	stwuct mwx5e_sampwew *sampwew;
	stwuct mwx5e_sampwe_westowe *westowe;
	stwuct mwx5_fwow_attw *pwe_attw;
	stwuct mwx5_fwow_handwe *pwe_wuwe;
	stwuct mwx5_fwow_attw *post_attw;
	stwuct mwx5_fwow_handwe *post_wuwe;
};

stwuct mwx5e_sampwe_westowe {
	stwuct hwist_node hwist;
	stwuct mwx5_modify_hdw *modify_hdw;
	stwuct mwx5_fwow_handwe *wuwe;
	u32 obj_id;
	int count;
};

static int
sampwew_tewmtbw_cweate(stwuct mwx5e_tc_psampwe *tc_psampwe)
{
	stwuct mwx5_eswitch *esw = tc_psampwe->esw;
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct mwx5_fwow_namespace *woot_ns;
	stwuct mwx5_fwow_act act = {};
	int eww;

	if (!MWX5_CAP_ESW_FWOWTABWE_FDB(dev, tewmination_tabwe))  {
		mwx5_cowe_wawn(dev, "tewmination tabwe is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	woot_ns = mwx5_get_fwow_namespace(dev, MWX5_FWOW_NAMESPACE_FDB);
	if (!woot_ns) {
		mwx5_cowe_wawn(dev, "faiwed to get FDB fwow namespace\n");
		wetuwn -EOPNOTSUPP;
	}

	ft_attw.fwags = MWX5_FWOW_TABWE_TEWMINATION | MWX5_FWOW_TABWE_UNMANAGED;
	ft_attw.autogwoup.max_num_gwoups = 1;
	ft_attw.pwio = FDB_SWOW_PATH;
	ft_attw.max_fte = 1;
	ft_attw.wevew = 1;
	tc_psampwe->tewmtbw = mwx5_cweate_auto_gwouped_fwow_tabwe(woot_ns, &ft_attw);
	if (IS_EWW(tc_psampwe->tewmtbw)) {
		eww = PTW_EWW(tc_psampwe->tewmtbw);
		mwx5_cowe_wawn(dev, "faiwed to cweate tewmtbw, eww: %d\n", eww);
		wetuwn eww;
	}

	act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	dest.vpowt.num = esw->managew_vpowt;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
	tc_psampwe->tewmtbw_wuwe = mwx5_add_fwow_wuwes(tc_psampwe->tewmtbw, NUWW, &act, &dest, 1);
	if (IS_EWW(tc_psampwe->tewmtbw_wuwe)) {
		eww = PTW_EWW(tc_psampwe->tewmtbw_wuwe);
		mwx5_cowe_wawn(dev, "faiwed to cweate tewmtbw wuwe, eww: %d\n", eww);
		mwx5_destwoy_fwow_tabwe(tc_psampwe->tewmtbw);
		wetuwn eww;
	}

	wetuwn 0;
}

static void
sampwew_tewmtbw_destwoy(stwuct mwx5e_tc_psampwe *tc_psampwe)
{
	mwx5_dew_fwow_wuwes(tc_psampwe->tewmtbw_wuwe);
	mwx5_destwoy_fwow_tabwe(tc_psampwe->tewmtbw);
}

static int
sampwew_obj_cweate(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_sampwew *sampwew)
{
	u32 in[MWX5_ST_SZ_DW(cweate_sampwew_obj_in)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)];
	u64 genewaw_obj_types;
	void *obj;
	int eww;

	genewaw_obj_types = MWX5_CAP_GEN_64(mdev, genewaw_obj_types);
	if (!(genewaw_obj_types & MWX5_HCA_CAP_GENEWAW_OBJECT_TYPES_SAMPWEW))
		wetuwn -EOPNOTSUPP;
	if (!MWX5_CAP_ESW_FWOWTABWE_FDB(mdev, ignowe_fwow_wevew))
		wetuwn -EOPNOTSUPP;

	obj = MWX5_ADDW_OF(cweate_sampwew_obj_in, in, sampwew_object);
	MWX5_SET(sampwew_obj, obj, tabwe_type, FS_FT_FDB);
	MWX5_SET(sampwew_obj, obj, ignowe_fwow_wevew, 1);
	MWX5_SET(sampwew_obj, obj, wevew, 1);
	MWX5_SET(sampwew_obj, obj, sampwe_watio, sampwew->sampwe_watio);
	MWX5_SET(sampwew_obj, obj, sampwe_tabwe_id, sampwew->sampwe_tabwe_id);
	MWX5_SET(sampwew_obj, obj, defauwt_tabwe_id, sampwew->defauwt_tabwe_id);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode, MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type, MWX5_GENEWAW_OBJECT_TYPES_SAMPWEW);

	eww = mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
	if (!eww)
		sampwew->sampwew_id = MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);

	wetuwn eww;
}

static void
sampwew_obj_destwoy(stwuct mwx5_cowe_dev *mdev, u32 sampwew_id)
{
	u32 in[MWX5_ST_SZ_DW(genewaw_obj_in_cmd_hdw)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)];

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode, MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type, MWX5_GENEWAW_OBJECT_TYPES_SAMPWEW);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, sampwew_id);

	mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
}

static u32
sampwew_hash(u32 sampwe_watio, u32 defauwt_tabwe_id)
{
	wetuwn jhash_2wowds(sampwe_watio, defauwt_tabwe_id, 0);
}

static int
sampwew_cmp(u32 sampwe_watio1, u32 defauwt_tabwe_id1, u32 sampwe_watio2, u32 defauwt_tabwe_id2)
{
	wetuwn sampwe_watio1 != sampwe_watio2 || defauwt_tabwe_id1 != defauwt_tabwe_id2;
}

static stwuct mwx5e_sampwew *
sampwew_get(stwuct mwx5e_tc_psampwe *tc_psampwe, u32 sampwe_watio, u32 defauwt_tabwe_id)
{
	stwuct mwx5e_sampwew *sampwew;
	u32 hash_key;
	int eww;

	mutex_wock(&tc_psampwe->ht_wock);
	hash_key = sampwew_hash(sampwe_watio, defauwt_tabwe_id);
	hash_fow_each_possibwe(tc_psampwe->hashtbw, sampwew, hwist, hash_key)
		if (!sampwew_cmp(sampwew->sampwe_watio, sampwew->defauwt_tabwe_id,
				 sampwe_watio, defauwt_tabwe_id))
			goto add_wef;

	sampwew = kzawwoc(sizeof(*sampwew), GFP_KEWNEW);
	if (!sampwew) {
		eww = -ENOMEM;
		goto eww_awwoc;
	}

	sampwew->sampwe_tabwe_id = tc_psampwe->tewmtbw->id;
	sampwew->defauwt_tabwe_id = defauwt_tabwe_id;
	sampwew->sampwe_watio = sampwe_watio;

	eww = sampwew_obj_cweate(tc_psampwe->esw->dev, sampwew);
	if (eww)
		goto eww_cweate;

	hash_add(tc_psampwe->hashtbw, &sampwew->hwist, hash_key);

add_wef:
	sampwew->count++;
	mutex_unwock(&tc_psampwe->ht_wock);
	wetuwn sampwew;

eww_cweate:
	kfwee(sampwew);
eww_awwoc:
	mutex_unwock(&tc_psampwe->ht_wock);
	wetuwn EWW_PTW(eww);
}

static void
sampwew_put(stwuct mwx5e_tc_psampwe *tc_psampwe, stwuct mwx5e_sampwew *sampwew)
{
	mutex_wock(&tc_psampwe->ht_wock);
	if (--sampwew->count == 0) {
		hash_dew(&sampwew->hwist);
		sampwew_obj_destwoy(tc_psampwe->esw->dev, sampwew->sampwew_id);
		kfwee(sampwew);
	}
	mutex_unwock(&tc_psampwe->ht_wock);
}

/* obj_id is used to westowe the sampwe pawametews.
 * Set fte_id in owiginaw fwow tabwe, then match it in the defauwt tabwe.
 * Onwy set it fow NICs can pwesewve weg_c ow decap action. Fow othew cases,
 * use the same match in the defauwt tabwe.
 * Use one headew wewwite fow both obj_id and fte_id.
 */
static stwuct mwx5_modify_hdw *
sampwe_modify_hdw_get(stwuct mwx5_cowe_dev *mdev, u32 obj_id,
		      stwuct mwx5e_tc_mod_hdw_acts *mod_acts)
{
	stwuct mwx5_modify_hdw *modify_hdw;
	int eww;

	eww = mwx5e_tc_match_to_weg_set(mdev, mod_acts, MWX5_FWOW_NAMESPACE_FDB,
					MAPPED_OBJ_TO_WEG, obj_id);
	if (eww)
		goto eww_set_wegc0;

	modify_hdw = mwx5_modify_headew_awwoc(mdev, MWX5_FWOW_NAMESPACE_FDB,
					      mod_acts->num_actions,
					      mod_acts->actions);
	if (IS_EWW(modify_hdw)) {
		eww = PTW_EWW(modify_hdw);
		goto eww_modify_hdw;
	}

	mwx5e_mod_hdw_deawwoc(mod_acts);
	wetuwn modify_hdw;

eww_modify_hdw:
	mwx5e_mod_hdw_deawwoc(mod_acts);
eww_set_wegc0:
	wetuwn EWW_PTW(eww);
}

static stwuct mwx5e_sampwe_westowe *
sampwe_westowe_get(stwuct mwx5e_tc_psampwe *tc_psampwe, u32 obj_id,
		   stwuct mwx5e_tc_mod_hdw_acts *mod_acts)
{
	stwuct mwx5_eswitch *esw = tc_psampwe->esw;
	stwuct mwx5_cowe_dev *mdev = esw->dev;
	stwuct mwx5e_sampwe_westowe *westowe;
	stwuct mwx5_modify_hdw *modify_hdw;
	int eww;

	mutex_wock(&tc_psampwe->westowe_wock);
	hash_fow_each_possibwe(tc_psampwe->westowe_hashtbw, westowe, hwist, obj_id)
		if (westowe->obj_id == obj_id)
			goto add_wef;

	westowe = kzawwoc(sizeof(*westowe), GFP_KEWNEW);
	if (!westowe) {
		eww = -ENOMEM;
		goto eww_awwoc;
	}
	westowe->obj_id = obj_id;

	modify_hdw = sampwe_modify_hdw_get(mdev, obj_id, mod_acts);
	if (IS_EWW(modify_hdw)) {
		eww = PTW_EWW(modify_hdw);
		goto eww_modify_hdw;
	}
	westowe->modify_hdw = modify_hdw;

	westowe->wuwe = esw_add_westowe_wuwe(esw, obj_id);
	if (IS_EWW(westowe->wuwe)) {
		eww = PTW_EWW(westowe->wuwe);
		goto eww_westowe;
	}

	hash_add(tc_psampwe->westowe_hashtbw, &westowe->hwist, obj_id);
add_wef:
	westowe->count++;
	mutex_unwock(&tc_psampwe->westowe_wock);
	wetuwn westowe;

eww_westowe:
	mwx5_modify_headew_deawwoc(mdev, westowe->modify_hdw);
eww_modify_hdw:
	kfwee(westowe);
eww_awwoc:
	mutex_unwock(&tc_psampwe->westowe_wock);
	wetuwn EWW_PTW(eww);
}

static void
sampwe_westowe_put(stwuct mwx5e_tc_psampwe *tc_psampwe, stwuct mwx5e_sampwe_westowe *westowe)
{
	mutex_wock(&tc_psampwe->westowe_wock);
	if (--westowe->count == 0)
		hash_dew(&westowe->hwist);
	mutex_unwock(&tc_psampwe->westowe_wock);

	if (!westowe->count) {
		mwx5_dew_fwow_wuwes(westowe->wuwe);
		mwx5_modify_headew_deawwoc(tc_psampwe->esw->dev, westowe->modify_hdw);
		kfwee(westowe);
	}
}

void mwx5e_tc_sampwe_skb(stwuct sk_buff *skb, stwuct mwx5_mapped_obj *mapped_obj)
{
	u32 twunc_size = mapped_obj->sampwe.twunc_size;
	stwuct psampwe_gwoup psampwe_gwoup = {};
	stwuct psampwe_metadata md = {};

	md.twunc_size = twunc_size ? min(twunc_size, skb->wen) : skb->wen;
	md.in_ifindex = skb->dev->ifindex;
	psampwe_gwoup.gwoup_num = mapped_obj->sampwe.gwoup_id;
	psampwe_gwoup.net = &init_net;
	skb_push(skb, skb->mac_wen);

	psampwe_sampwe_packet(&psampwe_gwoup, skb, mapped_obj->sampwe.wate, &md);
}

static int
add_post_wuwe(stwuct mwx5_eswitch *esw, stwuct mwx5e_sampwe_fwow *sampwe_fwow,
	      stwuct mwx5_fwow_spec *spec, stwuct mwx5_fwow_attw *attw,
	      u32 *defauwt_tbw_id)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	u32 attw_sz = ns_to_attw_sz(MWX5_FWOW_NAMESPACE_FDB);
	stwuct mwx5_vpowt_tbw_attw pew_vpowt_tbw_attw;
	stwuct mwx5_fwow_tabwe *defauwt_tbw;
	stwuct mwx5_fwow_attw *post_attw;
	int eww;

	/* Awwocate defauwt tabwe pew vpowt, chain and pwio. Othewwise, thewe is
	 * onwy one defauwt tabwe fow the same sampwew object. Wuwes with diffewent
	 * pwio and chain may ovewwap. Fow CT sampwe action, pew vpowt defauwt
	 * tabwe is needed to wesotwe the metadata.
	 */
	pew_vpowt_tbw_attw.chain = attw->chain;
	pew_vpowt_tbw_attw.pwio = attw->pwio;
	pew_vpowt_tbw_attw.vpowt = esw_attw->in_wep->vpowt;
	pew_vpowt_tbw_attw.vpowt_ns = &mwx5_esw_vpowt_tbw_sampwe_ns;
	defauwt_tbw = mwx5_esw_vpowttbw_get(esw, &pew_vpowt_tbw_attw);
	if (IS_EWW(defauwt_tbw)) {
		eww = PTW_EWW(defauwt_tbw);
		goto eww_defauwt_tbw;
	}
	*defauwt_tbw_id = defauwt_tbw->id;

	post_attw = mwx5_awwoc_fwow_attw(MWX5_FWOW_NAMESPACE_FDB);
	if (!post_attw) {
		eww = -ENOMEM;
		goto eww_attw;
	}
	sampwe_fwow->post_attw = post_attw;
	memcpy(post_attw, attw, attw_sz);
	/* Pewfowm the owiginaw matches on the defauwt tabwe.
	 * Offwoad aww actions except the sampwe action.
	 */
	post_attw->chain = 0;
	post_attw->pwio = 0;
	post_attw->ft = defauwt_tbw;
	post_attw->fwags = MWX5_ATTW_FWAG_NO_IN_POWT;

	/* When offwoading sampwe and encap action, if thewe is no vawid
	 * neigh data stwuct, a swow path wuwe is offwoaded fiwst. Souwce
	 * powt metadata match is set at that time. A pew vpowt tabwe is
	 * awweady awwocated. No need to match it again. So cweaw the souwce
	 * powt metadata match.
	 */
	mwx5_eswitch_cweaw_wuwe_souwce_powt(esw, spec);
	sampwe_fwow->post_wuwe = mwx5_eswitch_add_offwoaded_wuwe(esw, spec, post_attw);
	if (IS_EWW(sampwe_fwow->post_wuwe)) {
		eww = PTW_EWW(sampwe_fwow->post_wuwe);
		goto eww_wuwe;
	}
	wetuwn 0;

eww_wuwe:
	kfwee(post_attw);
eww_attw:
	mwx5_esw_vpowttbw_put(esw, &pew_vpowt_tbw_attw);
eww_defauwt_tbw:
	wetuwn eww;
}

static void
dew_post_wuwe(stwuct mwx5_eswitch *esw, stwuct mwx5e_sampwe_fwow *sampwe_fwow,
	      stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	stwuct mwx5_vpowt_tbw_attw tbw_attw;

	mwx5_eswitch_dew_offwoaded_wuwe(esw, sampwe_fwow->post_wuwe, sampwe_fwow->post_attw);
	kfwee(sampwe_fwow->post_attw);
	tbw_attw.chain = attw->chain;
	tbw_attw.pwio = attw->pwio;
	tbw_attw.vpowt = esw_attw->in_wep->vpowt;
	tbw_attw.vpowt_ns = &mwx5_esw_vpowt_tbw_sampwe_ns;
	mwx5_esw_vpowttbw_put(esw, &tbw_attw);
}

/* Fow the fowwowing typicaw fwow tabwe:
 *
 * +-------------------------------+
 * +       owiginaw fwow tabwe     +
 * +-------------------------------+
 * +         owiginaw match        +
 * +-------------------------------+
 * + sampwe action + othew actions +
 * +-------------------------------+
 *
 * We twanswate the tc fiwtew with sampwe action to the fowwowing HW modew:
 *
 *         +---------------------+
 *         + owiginaw fwow tabwe +
 *         +---------------------+
 *         +   owiginaw match    +
 *         +---------------------+
 *               | set fte_id (if weg_c pwesewve cap)
 *               | do decap (if wequiwed)
 *               v
 * +------------------------------------------------+
 * +                Fwow Sampwew Object             +
 * +------------------------------------------------+
 * +                    sampwe watio                +
 * +------------------------------------------------+
 * +    sampwe tabwe id    |    defauwt tabwe id    +
 * +------------------------------------------------+
 *            |                            |
 *            v                            v
 * +-----------------------------+  +-------------------+
 * +        sampwe tabwe         +  +   defauwt tabwe   +
 * +-----------------------------+  +-------------------+
 * + fowwawd to management vpowt +             |
 * +-----------------------------+             |
 *                                     +-------+------+
 *                                     |              |weg_c pwesewve cap
 *                                     |              |ow decap action
 *                                     v              v
 *                        +-----------------+   +-------------+
 *                        + pew vpowt tabwe +   + post action +
 *                        +-----------------+   +-------------+
 *                        + owiginaw match  +
 *                        +-----------------+
 *                        + othew actions   +
 *                        +-----------------+
 */
stwuct mwx5_fwow_handwe *
mwx5e_tc_sampwe_offwoad(stwuct mwx5e_tc_psampwe *tc_psampwe,
			stwuct mwx5_fwow_spec *spec,
			stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	stwuct mwx5_esw_fwow_attw *pwe_esw_attw;
	stwuct mwx5_mapped_obj westowe_obj = {};
	stwuct mwx5e_tc_mod_hdw_acts *mod_acts;
	stwuct mwx5e_sampwe_fwow *sampwe_fwow;
	stwuct mwx5e_sampwe_attw *sampwe_attw;
	stwuct mwx5_fwow_attw *pwe_attw;
	stwuct mwx5_eswitch *esw;
	u32 defauwt_tbw_id;
	u32 obj_id;
	int eww;

	if (IS_EWW_OW_NUWW(tc_psampwe))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	sampwe_fwow = kzawwoc(sizeof(*sampwe_fwow), GFP_KEWNEW);
	if (!sampwe_fwow)
		wetuwn EWW_PTW(-ENOMEM);
	sampwe_attw = &attw->sampwe_attw;
	sampwe_attw->sampwe_fwow = sampwe_fwow;

	/* Fow NICs with weg_c_pwesewve suppowt ow decap action, use
	 * post action instead of the pew vpowt, chain and pwio tabwe.
	 * Onwy match the fte id instead of the same match in the
	 * owiginaw fwow tabwe.
	 */
	esw = tc_psampwe->esw;
	if (mwx5e_tc_act_sampwe_is_muwti_tabwe(esw->dev, attw)) {
		stwuct mwx5_fwow_tabwe *ft;

		ft = mwx5e_tc_post_act_get_ft(tc_psampwe->post_act);
		defauwt_tbw_id = ft->id;
	} ewse {
		eww = add_post_wuwe(esw, sampwe_fwow, spec, attw, &defauwt_tbw_id);
		if (eww)
			goto eww_post_wuwe;
	}

	/* Cweate sampwew object. */
	sampwe_fwow->sampwew = sampwew_get(tc_psampwe, sampwe_attw->wate, defauwt_tbw_id);
	if (IS_EWW(sampwe_fwow->sampwew)) {
		eww = PTW_EWW(sampwe_fwow->sampwew);
		goto eww_sampwew;
	}
	sampwe_attw->sampwew_id = sampwe_fwow->sampwew->sampwew_id;

	/* Cweate an id mapping weg_c0 vawue to sampwe object. */
	westowe_obj.type = MWX5_MAPPED_OBJ_SAMPWE;
	westowe_obj.sampwe.gwoup_id = sampwe_attw->gwoup_num;
	westowe_obj.sampwe.wate = sampwe_attw->wate;
	westowe_obj.sampwe.twunc_size = sampwe_attw->twunc_size;
	westowe_obj.sampwe.tunnew_id = attw->tunnew_id;
	eww = mapping_add(esw->offwoads.weg_c0_obj_poow, &westowe_obj, &obj_id);
	if (eww)
		goto eww_obj_id;
	sampwe_attw->westowe_obj_id = obj_id;

	/* Cweate sampwe westowe context. */
	mod_acts = &attw->pawse_attw->mod_hdw_acts;
	sampwe_fwow->westowe = sampwe_westowe_get(tc_psampwe, obj_id, mod_acts);
	if (IS_EWW(sampwe_fwow->westowe)) {
		eww = PTW_EWW(sampwe_fwow->westowe);
		goto eww_sampwe_westowe;
	}

	/* Pewfowm the owiginaw matches on the owiginaw tabwe. Offwoad the
	 * sampwe action. The destination is the sampwew object.
	 */
	pwe_attw = mwx5_awwoc_fwow_attw(MWX5_FWOW_NAMESPACE_FDB);
	if (!pwe_attw) {
		eww = -ENOMEM;
		goto eww_awwoc_pwe_fwow_attw;
	}
	pwe_attw->action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST | MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
	/* Fow decap action, do decap in the owiginaw fwow tabwe instead of the
	 * defauwt fwow tabwe.
	 */
	if (attw->action & MWX5_FWOW_CONTEXT_ACTION_DECAP)
		pwe_attw->action |= MWX5_FWOW_CONTEXT_ACTION_DECAP;
	pwe_attw->modify_hdw = sampwe_fwow->westowe->modify_hdw;
	pwe_attw->fwags = MWX5_ATTW_FWAG_SAMPWE;
	pwe_attw->innew_match_wevew = attw->innew_match_wevew;
	pwe_attw->outew_match_wevew = attw->outew_match_wevew;
	pwe_attw->chain = attw->chain;
	pwe_attw->pwio = attw->pwio;
	pwe_attw->ft = attw->ft;
	pwe_attw->sampwe_attw = *sampwe_attw;
	pwe_esw_attw = pwe_attw->esw_attw;
	pwe_esw_attw->in_mdev = esw_attw->in_mdev;
	pwe_esw_attw->in_wep = esw_attw->in_wep;
	sampwe_fwow->pwe_wuwe = mwx5_eswitch_add_offwoaded_wuwe(esw, spec, pwe_attw);
	if (IS_EWW(sampwe_fwow->pwe_wuwe)) {
		eww = PTW_EWW(sampwe_fwow->pwe_wuwe);
		goto eww_pwe_offwoad_wuwe;
	}
	sampwe_fwow->pwe_attw = pwe_attw;

	wetuwn sampwe_fwow->pwe_wuwe;

eww_pwe_offwoad_wuwe:
	kfwee(pwe_attw);
eww_awwoc_pwe_fwow_attw:
	sampwe_westowe_put(tc_psampwe, sampwe_fwow->westowe);
eww_sampwe_westowe:
	mapping_wemove(esw->offwoads.weg_c0_obj_poow, obj_id);
eww_obj_id:
	sampwew_put(tc_psampwe, sampwe_fwow->sampwew);
eww_sampwew:
	if (sampwe_fwow->post_wuwe)
		dew_post_wuwe(esw, sampwe_fwow, attw);
eww_post_wuwe:
	kfwee(sampwe_fwow);
	wetuwn EWW_PTW(eww);
}

void
mwx5e_tc_sampwe_unoffwoad(stwuct mwx5e_tc_psampwe *tc_psampwe,
			  stwuct mwx5_fwow_handwe *wuwe,
			  stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5e_sampwe_fwow *sampwe_fwow;
	stwuct mwx5_eswitch *esw;

	if (IS_EWW_OW_NUWW(tc_psampwe))
		wetuwn;

	/* The fowwowing dewete owdew can't be changed, othewwise,
	 * wiww hit fw syndwomes.
	 */
	esw = tc_psampwe->esw;
	sampwe_fwow = attw->sampwe_attw.sampwe_fwow;
	mwx5_eswitch_dew_offwoaded_wuwe(esw, sampwe_fwow->pwe_wuwe, sampwe_fwow->pwe_attw);

	sampwe_westowe_put(tc_psampwe, sampwe_fwow->westowe);
	mapping_wemove(esw->offwoads.weg_c0_obj_poow, attw->sampwe_attw.westowe_obj_id);
	sampwew_put(tc_psampwe, sampwe_fwow->sampwew);
	if (sampwe_fwow->post_wuwe)
		dew_post_wuwe(esw, sampwe_fwow, attw);

	kfwee(sampwe_fwow->pwe_attw);
	kfwee(sampwe_fwow);
}

stwuct mwx5e_tc_psampwe *
mwx5e_tc_sampwe_init(stwuct mwx5_eswitch *esw, stwuct mwx5e_post_act *post_act)
{
	stwuct mwx5e_tc_psampwe *tc_psampwe;
	int eww;

	tc_psampwe = kzawwoc(sizeof(*tc_psampwe), GFP_KEWNEW);
	if (!tc_psampwe)
		wetuwn EWW_PTW(-ENOMEM);
	if (IS_EWW_OW_NUWW(post_act)) {
		eww = PTW_EWW(post_act);
		goto eww_post_act;
	}
	tc_psampwe->post_act = post_act;
	tc_psampwe->esw = esw;
	eww = sampwew_tewmtbw_cweate(tc_psampwe);
	if (eww)
		goto eww_post_act;

	mutex_init(&tc_psampwe->ht_wock);
	mutex_init(&tc_psampwe->westowe_wock);

	wetuwn tc_psampwe;

eww_post_act:
	kfwee(tc_psampwe);
	wetuwn EWW_PTW(eww);
}

void
mwx5e_tc_sampwe_cweanup(stwuct mwx5e_tc_psampwe *tc_psampwe)
{
	if (IS_EWW_OW_NUWW(tc_psampwe))
		wetuwn;

	mutex_destwoy(&tc_psampwe->westowe_wock);
	mutex_destwoy(&tc_psampwe->ht_wock);
	sampwew_tewmtbw_destwoy(tc_psampwe);
	kfwee(tc_psampwe);
}
