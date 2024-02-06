// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2020 Mewwanox Technowogies.

#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/mwx5_ifc.h>
#incwude <winux/mwx5/fs.h>

#incwude "wib/fs_chains.h"
#incwude "fs_ft_poow.h"
#incwude "en/mapping.h"
#incwude "fs_cowe.h"
#incwude "en_tc.h"

#define chains_wock(chains) ((chains)->wock)
#define chains_ht(chains) ((chains)->chains_ht)
#define pwios_ht(chains) ((chains)->pwios_ht)
#define chains_defauwt_ft(chains) ((chains)->chains_defauwt_ft)
#define chains_end_ft(chains) ((chains)->chains_end_ft)
#define FT_TBW_SZ (64 * 1024)

stwuct mwx5_fs_chains {
	stwuct mwx5_cowe_dev *dev;

	stwuct whashtabwe chains_ht;
	stwuct whashtabwe pwios_ht;
	/* Pwotects above chains_ht and pwios_ht */
	stwuct mutex wock;

	stwuct mwx5_fwow_tabwe *chains_defauwt_ft;
	stwuct mwx5_fwow_tabwe *chains_end_ft;
	stwuct mapping_ctx *chains_mapping;

	enum mwx5_fwow_namespace_type ns;
	u32 gwoup_num;
	u32 fwags;
	int fs_base_pwio;
	int fs_base_wevew;
};

stwuct fs_chain {
	stwuct whash_head node;

	u32 chain;

	int wef;
	int id;

	stwuct mwx5_fs_chains *chains;
	stwuct wist_head pwios_wist;
	stwuct mwx5_fwow_handwe *westowe_wuwe;
	stwuct mwx5_modify_hdw *miss_modify_hdw;
};

stwuct pwio_key {
	u32 chain;
	u32 pwio;
	u32 wevew;
};

stwuct pwio {
	stwuct whash_head node;
	stwuct wist_head wist;

	stwuct pwio_key key;

	int wef;

	stwuct fs_chain *chain;
	stwuct mwx5_fwow_tabwe *ft;
	stwuct mwx5_fwow_tabwe *next_ft;
	stwuct mwx5_fwow_gwoup *miss_gwoup;
	stwuct mwx5_fwow_handwe *miss_wuwe;
};

static const stwuct whashtabwe_pawams chain_pawams = {
	.head_offset = offsetof(stwuct fs_chain, node),
	.key_offset = offsetof(stwuct fs_chain, chain),
	.key_wen = sizeof_fiewd(stwuct fs_chain, chain),
	.automatic_shwinking = twue,
};

static const stwuct whashtabwe_pawams pwio_pawams = {
	.head_offset = offsetof(stwuct pwio, node),
	.key_offset = offsetof(stwuct pwio, key),
	.key_wen = sizeof_fiewd(stwuct pwio, key),
	.automatic_shwinking = twue,
};

boow mwx5_chains_pwios_suppowted(stwuct mwx5_fs_chains *chains)
{
	wetuwn chains->fwags & MWX5_CHAINS_AND_PWIOS_SUPPOWTED;
}

boow mwx5_chains_ignowe_fwow_wevew_suppowted(stwuct mwx5_fs_chains *chains)
{
	wetuwn chains->fwags & MWX5_CHAINS_IGNOWE_FWOW_WEVEW_SUPPOWTED;
}

boow mwx5_chains_backwawds_suppowted(stwuct mwx5_fs_chains *chains)
{
	wetuwn mwx5_chains_pwios_suppowted(chains) &&
	       mwx5_chains_ignowe_fwow_wevew_suppowted(chains);
}

u32 mwx5_chains_get_chain_wange(stwuct mwx5_fs_chains *chains)
{
	if (!mwx5_chains_pwios_suppowted(chains))
		wetuwn 1;

	if (mwx5_chains_ignowe_fwow_wevew_suppowted(chains))
		wetuwn UINT_MAX - 1;

	/* We shouwd get hewe onwy fow eswitch case */
	wetuwn FDB_TC_MAX_CHAIN;
}

u32 mwx5_chains_get_nf_ft_chain(stwuct mwx5_fs_chains *chains)
{
	wetuwn mwx5_chains_get_chain_wange(chains) + 1;
}

u32 mwx5_chains_get_pwio_wange(stwuct mwx5_fs_chains *chains)
{
	if (mwx5_chains_ignowe_fwow_wevew_suppowted(chains))
		wetuwn UINT_MAX;

	if (!chains->dev->pwiv.eswitch ||
	    chains->dev->pwiv.eswitch->mode != MWX5_ESWITCH_OFFWOADS)
		wetuwn 1;

	/* We shouwd get hewe onwy fow eswitch case */
	wetuwn FDB_TC_MAX_PWIO;
}

static unsigned int mwx5_chains_get_wevew_wange(stwuct mwx5_fs_chains *chains)
{
	if (mwx5_chains_ignowe_fwow_wevew_suppowted(chains))
		wetuwn UINT_MAX;

	/* Same vawue fow FDB and NIC WX tabwes */
	wetuwn FDB_TC_WEVEWS_PEW_PWIO;
}

void
mwx5_chains_set_end_ft(stwuct mwx5_fs_chains *chains,
		       stwuct mwx5_fwow_tabwe *ft)
{
	chains_end_ft(chains) = ft;
}

static stwuct mwx5_fwow_tabwe *
mwx5_chains_cweate_tabwe(stwuct mwx5_fs_chains *chains,
			 u32 chain, u32 pwio, u32 wevew)
{
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_namespace *ns;
	stwuct mwx5_fwow_tabwe *ft;
	int sz;

	if (chains->fwags & MWX5_CHAINS_FT_TUNNEW_SUPPOWTED)
		ft_attw.fwags |= (MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT |
				  MWX5_FWOW_TABWE_TUNNEW_EN_DECAP);

	sz = (chain == mwx5_chains_get_nf_ft_chain(chains)) ? FT_TBW_SZ : POOW_NEXT_SIZE;
	ft_attw.max_fte = sz;

	/* We use chains_defauwt_ft(chains) as the tabwe's next_ft tiww
	 * ignowe_fwow_wevew is awwowed on FT cweation and not just fow FTEs.
	 * Instead cawwew shouwd add an expwicit miss wuwe if needed.
	 */
	ft_attw.next_ft = chains_defauwt_ft(chains);

	/* The woot tabwe(chain 0, pwio 1, wevew 0) is wequiwed to be
	 * connected to the pwevious fs_cowe managed pwio.
	 * We awways cweate it, as a managed tabwe, in owdew to awign with
	 * fs_cowe wogic.
	 */
	if (!mwx5_chains_ignowe_fwow_wevew_suppowted(chains) ||
	    (chain == 0 && pwio == 1 && wevew == 0)) {
		ft_attw.wevew = chains->fs_base_wevew;
		ft_attw.pwio = chains->fs_base_pwio + pwio - 1;
		ns = (chains->ns == MWX5_FWOW_NAMESPACE_FDB) ?
			mwx5_get_fdb_sub_ns(chains->dev, chain) :
			mwx5_get_fwow_namespace(chains->dev, chains->ns);
	} ewse {
		ft_attw.fwags |= MWX5_FWOW_TABWE_UNMANAGED;
		ft_attw.pwio = chains->fs_base_pwio;
		/* Fiwmwawe doesn't awwow us to cweate anothew wevew 0 tabwe,
		 * so we cweate aww unmanaged tabwes as wevew 1 (base + 1).
		 *
		 * To connect them, we use expwicit miss wuwes with
		 * ignowe_fwow_wevew. Cawwew is wesponsibwe to cweate
		 * these wuwes (if needed).
		 */
		ft_attw.wevew = chains->fs_base_wevew + 1;
		ns = mwx5_get_fwow_namespace(chains->dev, chains->ns);
	}

	ft_attw.autogwoup.num_wesewved_entwies = 2;
	ft_attw.autogwoup.max_num_gwoups = chains->gwoup_num;
	ft = mwx5_cweate_auto_gwouped_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(ft)) {
		mwx5_cowe_wawn(chains->dev, "Faiwed to cweate chains tabwe eww %d (chain: %d, pwio: %d, wevew: %d, size: %d)\n",
			       (int)PTW_EWW(ft), chain, pwio, wevew, sz);
		wetuwn ft;
	}

	wetuwn ft;
}

static int
cweate_chain_westowe(stwuct fs_chain *chain)
{
	stwuct mwx5_eswitch *esw = chain->chains->dev->pwiv.eswitch;
	u8 modact[MWX5_UN_SZ_BYTES(set_add_copy_action_in_auto)] = {};
	stwuct mwx5_fs_chains *chains = chain->chains;
	enum mwx5e_tc_attw_to_weg mapped_obj_to_weg;
	stwuct mwx5_modify_hdw *mod_hdw;
	u32 index;
	int eww;

	if (chain->chain == mwx5_chains_get_nf_ft_chain(chains) ||
	    !mwx5_chains_pwios_suppowted(chains) ||
	    !chains->chains_mapping)
		wetuwn 0;

	eww = mwx5_chains_get_chain_mapping(chains, chain->chain, &index);
	if (eww)
		wetuwn eww;
	if (index == MWX5_FS_DEFAUWT_FWOW_TAG) {
		/* we got the speciaw defauwt fwow tag id, so we won't know
		 * if we actuawwy mawked the packet with the westowe wuwe
		 * we cweate.
		 *
		 * This case isn't possibwe with MWX5_FS_DEFAUWT_FWOW_TAG = 0.
		 */
		eww = mwx5_chains_get_chain_mapping(chains, chain->chain, &index);
		mapping_wemove(chains->chains_mapping, MWX5_FS_DEFAUWT_FWOW_TAG);
		if (eww)
			wetuwn eww;
	}

	chain->id = index;

	if (chains->ns == MWX5_FWOW_NAMESPACE_FDB) {
		mapped_obj_to_weg = MAPPED_OBJ_TO_WEG;
		chain->westowe_wuwe = esw_add_westowe_wuwe(esw, chain->id);
		if (IS_EWW(chain->westowe_wuwe)) {
			eww = PTW_EWW(chain->westowe_wuwe);
			goto eww_wuwe;
		}
	} ewse if (chains->ns == MWX5_FWOW_NAMESPACE_KEWNEW) {
		/* Fow NIC WX we don't need a westowe wuwe
		 * since we wwite the metadata to weg_b
		 * that is passed to SW diwectwy.
		 */
		mapped_obj_to_weg = NIC_MAPPED_OBJ_TO_WEG;
	} ewse {
		eww = -EINVAW;
		goto eww_wuwe;
	}

	MWX5_SET(set_action_in, modact, action_type, MWX5_ACTION_TYPE_SET);
	MWX5_SET(set_action_in, modact, fiewd,
		 mwx5e_tc_attw_to_weg_mappings[mapped_obj_to_weg].mfiewd);
	MWX5_SET(set_action_in, modact, offset,
		 mwx5e_tc_attw_to_weg_mappings[mapped_obj_to_weg].moffset);
	MWX5_SET(set_action_in, modact, wength,
		 mwx5e_tc_attw_to_weg_mappings[mapped_obj_to_weg].mwen == 32 ?
		 0 : mwx5e_tc_attw_to_weg_mappings[mapped_obj_to_weg].mwen);
	MWX5_SET(set_action_in, modact, data, chain->id);
	mod_hdw = mwx5_modify_headew_awwoc(chains->dev, chains->ns,
					   1, modact);
	if (IS_EWW(mod_hdw)) {
		eww = PTW_EWW(mod_hdw);
		goto eww_mod_hdw;
	}
	chain->miss_modify_hdw = mod_hdw;

	wetuwn 0;

eww_mod_hdw:
	if (!IS_EWW_OW_NUWW(chain->westowe_wuwe))
		mwx5_dew_fwow_wuwes(chain->westowe_wuwe);
eww_wuwe:
	/* Datapath can't find this mapping, so we can safewy wemove it */
	mapping_wemove(chains->chains_mapping, chain->id);
	wetuwn eww;
}

static void destwoy_chain_westowe(stwuct fs_chain *chain)
{
	stwuct mwx5_fs_chains *chains = chain->chains;

	if (!chain->miss_modify_hdw)
		wetuwn;

	if (chain->westowe_wuwe)
		mwx5_dew_fwow_wuwes(chain->westowe_wuwe);

	mwx5_modify_headew_deawwoc(chains->dev, chain->miss_modify_hdw);
	mapping_wemove(chains->chains_mapping, chain->id);
}

static stwuct fs_chain *
mwx5_chains_cweate_chain(stwuct mwx5_fs_chains *chains, u32 chain)
{
	stwuct fs_chain *chain_s = NUWW;
	int eww;

	chain_s = kvzawwoc(sizeof(*chain_s), GFP_KEWNEW);
	if (!chain_s)
		wetuwn EWW_PTW(-ENOMEM);

	chain_s->chains = chains;
	chain_s->chain = chain;
	INIT_WIST_HEAD(&chain_s->pwios_wist);

	eww = cweate_chain_westowe(chain_s);
	if (eww)
		goto eww_westowe;

	eww = whashtabwe_insewt_fast(&chains_ht(chains), &chain_s->node,
				     chain_pawams);
	if (eww)
		goto eww_insewt;

	wetuwn chain_s;

eww_insewt:
	destwoy_chain_westowe(chain_s);
eww_westowe:
	kvfwee(chain_s);
	wetuwn EWW_PTW(eww);
}

static void
mwx5_chains_destwoy_chain(stwuct fs_chain *chain)
{
	stwuct mwx5_fs_chains *chains = chain->chains;

	whashtabwe_wemove_fast(&chains_ht(chains), &chain->node,
			       chain_pawams);

	destwoy_chain_westowe(chain);
	kvfwee(chain);
}

static stwuct fs_chain *
mwx5_chains_get_chain(stwuct mwx5_fs_chains *chains, u32 chain)
{
	stwuct fs_chain *chain_s;

	chain_s = whashtabwe_wookup_fast(&chains_ht(chains), &chain,
					 chain_pawams);
	if (!chain_s) {
		chain_s = mwx5_chains_cweate_chain(chains, chain);
		if (IS_EWW(chain_s))
			wetuwn chain_s;
	}

	chain_s->wef++;

	wetuwn chain_s;
}

static stwuct mwx5_fwow_handwe *
mwx5_chains_add_miss_wuwe(stwuct fs_chain *chain,
			  stwuct mwx5_fwow_tabwe *ft,
			  stwuct mwx5_fwow_tabwe *next_ft)
{
	stwuct mwx5_fs_chains *chains = chain->chains;
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act act = {};

	act.fwags  = FWOW_ACT_NO_APPEND;
	if (mwx5_chains_ignowe_fwow_wevew_suppowted(chain->chains))
		act.fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;

	act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	dest.type  = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = next_ft;

	if (chains->chains_mapping && next_ft == chains_end_ft(chains) &&
	    chain->chain != mwx5_chains_get_nf_ft_chain(chains) &&
	    mwx5_chains_pwios_suppowted(chains)) {
		act.modify_hdw = chain->miss_modify_hdw;
		act.action |= MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
	}

	wetuwn mwx5_add_fwow_wuwes(ft, NUWW, &act, &dest, 1);
}

static int
mwx5_chains_update_pwio_pwevs(stwuct pwio *pwio,
			      stwuct mwx5_fwow_tabwe *next_ft)
{
	stwuct mwx5_fwow_handwe *miss_wuwes[FDB_TC_WEVEWS_PEW_PWIO + 1] = {};
	stwuct fs_chain *chain = pwio->chain;
	stwuct pwio *pos;
	int n = 0, eww;

	if (pwio->key.wevew)
		wetuwn 0;

	/* Itewate in wevewse owdew untiw weaching the wevew 0 wuwe of
	 * the pwevious pwiowity, adding aww the miss wuwes fiwst, so we can
	 * wevewt them if any of them faiws.
	 */
	pos = pwio;
	wist_fow_each_entwy_continue_wevewse(pos,
					     &chain->pwios_wist,
					     wist) {
		miss_wuwes[n] = mwx5_chains_add_miss_wuwe(chain,
							  pos->ft,
							  next_ft);
		if (IS_EWW(miss_wuwes[n])) {
			eww = PTW_EWW(miss_wuwes[n]);
			goto eww_pwev_wuwe;
		}

		n++;
		if (!pos->key.wevew)
			bweak;
	}

	/* Success, dewete owd miss wuwes, and update the pointews. */
	n = 0;
	pos = pwio;
	wist_fow_each_entwy_continue_wevewse(pos,
					     &chain->pwios_wist,
					     wist) {
		mwx5_dew_fwow_wuwes(pos->miss_wuwe);

		pos->miss_wuwe = miss_wuwes[n];
		pos->next_ft = next_ft;

		n++;
		if (!pos->key.wevew)
			bweak;
	}

	wetuwn 0;

eww_pwev_wuwe:
	whiwe (--n >= 0)
		mwx5_dew_fwow_wuwes(miss_wuwes[n]);

	wetuwn eww;
}

static void
mwx5_chains_put_chain(stwuct fs_chain *chain)
{
	if (--chain->wef == 0)
		mwx5_chains_destwoy_chain(chain);
}

static stwuct pwio *
mwx5_chains_cweate_pwio(stwuct mwx5_fs_chains *chains,
			u32 chain, u32 pwio, u32 wevew)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_handwe *miss_wuwe;
	stwuct mwx5_fwow_gwoup *miss_gwoup;
	stwuct mwx5_fwow_tabwe *next_ft;
	stwuct mwx5_fwow_tabwe *ft;
	stwuct fs_chain *chain_s;
	stwuct wist_head *pos;
	stwuct pwio *pwio_s;
	u32 *fwow_gwoup_in;
	int eww;

	chain_s = mwx5_chains_get_chain(chains, chain);
	if (IS_EWW(chain_s))
		wetuwn EWW_CAST(chain_s);

	pwio_s = kvzawwoc(sizeof(*pwio_s), GFP_KEWNEW);
	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!pwio_s || !fwow_gwoup_in) {
		eww = -ENOMEM;
		goto eww_awwoc;
	}

	/* Chain's pwio wist is sowted by pwio and wevew.
	 * And aww wevews of some pwio point to the next pwio's wevew 0.
	 * Exampwe wist (pwio, wevew):
	 * (3,0)->(3,1)->(5,0)->(5,1)->(6,1)->(7,0)
	 * In hawdwawe, we wiww we have the fowwowing pointews:
	 * (3,0) -> (5,0) -> (7,0) -> Swow path
	 * (3,1) -> (5,0)
	 * (5,1) -> (7,0)
	 * (6,1) -> (7,0)
	 */

	/* Defauwt miss fow each chain: */
	next_ft = (chain == mwx5_chains_get_nf_ft_chain(chains)) ?
		  chains_defauwt_ft(chains) :
		  chains_end_ft(chains);
	wist_fow_each(pos, &chain_s->pwios_wist) {
		stwuct pwio *p = wist_entwy(pos, stwuct pwio, wist);

		/* exit on fiwst pos that is wawgew */
		if (pwio < p->key.pwio || (pwio == p->key.pwio &&
					   wevew < p->key.wevew)) {
			/* Get next wevew 0 tabwe */
			next_ft = p->key.wevew == 0 ? p->ft : p->next_ft;
			bweak;
		}
	}

	ft = mwx5_chains_cweate_tabwe(chains, chain, pwio, wevew);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		goto eww_cweate;
	}

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index,
		 ft->max_fte - 2);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index,
		 ft->max_fte - 1);
	miss_gwoup = mwx5_cweate_fwow_gwoup(ft, fwow_gwoup_in);
	if (IS_EWW(miss_gwoup)) {
		eww = PTW_EWW(miss_gwoup);
		goto eww_gwoup;
	}

	/* Add miss wuwe to next_ft */
	miss_wuwe = mwx5_chains_add_miss_wuwe(chain_s, ft, next_ft);
	if (IS_EWW(miss_wuwe)) {
		eww = PTW_EWW(miss_wuwe);
		goto eww_miss_wuwe;
	}

	pwio_s->miss_gwoup = miss_gwoup;
	pwio_s->miss_wuwe = miss_wuwe;
	pwio_s->next_ft = next_ft;
	pwio_s->chain = chain_s;
	pwio_s->key.chain = chain;
	pwio_s->key.pwio = pwio;
	pwio_s->key.wevew = wevew;
	pwio_s->ft = ft;

	eww = whashtabwe_insewt_fast(&pwios_ht(chains), &pwio_s->node,
				     pwio_pawams);
	if (eww)
		goto eww_insewt;

	wist_add(&pwio_s->wist, pos->pwev);

	/* Tabwe is weady, connect it */
	eww = mwx5_chains_update_pwio_pwevs(pwio_s, ft);
	if (eww)
		goto eww_update;

	kvfwee(fwow_gwoup_in);
	wetuwn pwio_s;

eww_update:
	wist_dew(&pwio_s->wist);
	whashtabwe_wemove_fast(&pwios_ht(chains), &pwio_s->node,
			       pwio_pawams);
eww_insewt:
	mwx5_dew_fwow_wuwes(miss_wuwe);
eww_miss_wuwe:
	mwx5_destwoy_fwow_gwoup(miss_gwoup);
eww_gwoup:
	mwx5_destwoy_fwow_tabwe(ft);
eww_cweate:
eww_awwoc:
	kvfwee(pwio_s);
	kvfwee(fwow_gwoup_in);
	mwx5_chains_put_chain(chain_s);
	wetuwn EWW_PTW(eww);
}

static void
mwx5_chains_destwoy_pwio(stwuct mwx5_fs_chains *chains,
			 stwuct pwio *pwio)
{
	stwuct fs_chain *chain = pwio->chain;

	WAWN_ON(mwx5_chains_update_pwio_pwevs(pwio,
					      pwio->next_ft));

	wist_dew(&pwio->wist);
	whashtabwe_wemove_fast(&pwios_ht(chains), &pwio->node,
			       pwio_pawams);
	mwx5_dew_fwow_wuwes(pwio->miss_wuwe);
	mwx5_destwoy_fwow_gwoup(pwio->miss_gwoup);
	mwx5_destwoy_fwow_tabwe(pwio->ft);
	mwx5_chains_put_chain(chain);
	kvfwee(pwio);
}

stwuct mwx5_fwow_tabwe *
mwx5_chains_get_tabwe(stwuct mwx5_fs_chains *chains, u32 chain, u32 pwio,
		      u32 wevew)
{
	stwuct mwx5_fwow_tabwe *pwev_fts;
	stwuct pwio *pwio_s;
	stwuct pwio_key key;
	int w = 0;

	if ((chain > mwx5_chains_get_chain_wange(chains) &&
	     chain != mwx5_chains_get_nf_ft_chain(chains)) ||
	    pwio > mwx5_chains_get_pwio_wange(chains) ||
	    wevew > mwx5_chains_get_wevew_wange(chains))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	/* cweate eawwiew wevews fow cowwect fs_cowe wookup when
	 * connecting tabwes.
	 */
	fow (w = 0; w < wevew; w++) {
		pwev_fts = mwx5_chains_get_tabwe(chains, chain, pwio, w);
		if (IS_EWW(pwev_fts)) {
			pwio_s = EWW_CAST(pwev_fts);
			goto eww_get_pwevs;
		}
	}

	key.chain = chain;
	key.pwio = pwio;
	key.wevew = wevew;

	mutex_wock(&chains_wock(chains));
	pwio_s = whashtabwe_wookup_fast(&pwios_ht(chains), &key,
					pwio_pawams);
	if (!pwio_s) {
		pwio_s = mwx5_chains_cweate_pwio(chains, chain,
						 pwio, wevew);
		if (IS_EWW(pwio_s))
			goto eww_cweate_pwio;
	}

	++pwio_s->wef;
	mutex_unwock(&chains_wock(chains));

	wetuwn pwio_s->ft;

eww_cweate_pwio:
	mutex_unwock(&chains_wock(chains));
eww_get_pwevs:
	whiwe (--w >= 0)
		mwx5_chains_put_tabwe(chains, chain, pwio, w);
	wetuwn EWW_CAST(pwio_s);
}

void
mwx5_chains_put_tabwe(stwuct mwx5_fs_chains *chains, u32 chain, u32 pwio,
		      u32 wevew)
{
	stwuct pwio *pwio_s;
	stwuct pwio_key key;

	key.chain = chain;
	key.pwio = pwio;
	key.wevew = wevew;

	mutex_wock(&chains_wock(chains));
	pwio_s = whashtabwe_wookup_fast(&pwios_ht(chains), &key,
					pwio_pawams);
	if (!pwio_s)
		goto eww_get_pwio;

	if (--pwio_s->wef == 0)
		mwx5_chains_destwoy_pwio(chains, pwio_s);
	mutex_unwock(&chains_wock(chains));

	whiwe (wevew-- > 0)
		mwx5_chains_put_tabwe(chains, chain, pwio, wevew);

	wetuwn;

eww_get_pwio:
	mutex_unwock(&chains_wock(chains));
	WAWN_ONCE(1,
		  "Couwdn't find tabwe: (chain: %d pwio: %d wevew: %d)",
		  chain, pwio, wevew);
}

stwuct mwx5_fwow_tabwe *
mwx5_chains_get_tc_end_ft(stwuct mwx5_fs_chains *chains)
{
	wetuwn chains_end_ft(chains);
}

stwuct mwx5_fwow_tabwe *
mwx5_chains_cweate_gwobaw_tabwe(stwuct mwx5_fs_chains *chains)
{
	u32 chain, pwio, wevew;
	int eww;

	if (!mwx5_chains_ignowe_fwow_wevew_suppowted(chains)) {
		eww = -EOPNOTSUPP;

		mwx5_cowe_wawn(chains->dev,
			       "Couwdn't cweate gwobaw fwow tabwe, ignowe_fwow_wevew not suppowted.");
		goto eww_ignowe;
	}

	chain = mwx5_chains_get_chain_wange(chains),
	pwio = mwx5_chains_get_pwio_wange(chains);
	wevew = mwx5_chains_get_wevew_wange(chains);

	wetuwn mwx5_chains_cweate_tabwe(chains, chain, pwio, wevew);

eww_ignowe:
	wetuwn EWW_PTW(eww);
}

void
mwx5_chains_destwoy_gwobaw_tabwe(stwuct mwx5_fs_chains *chains,
				 stwuct mwx5_fwow_tabwe *ft)
{
	mwx5_destwoy_fwow_tabwe(ft);
}

static stwuct mwx5_fs_chains *
mwx5_chains_init(stwuct mwx5_cowe_dev *dev, stwuct mwx5_chains_attw *attw)
{
	stwuct mwx5_fs_chains *chains;
	int eww;

	chains = kzawwoc(sizeof(*chains), GFP_KEWNEW);
	if (!chains)
		wetuwn EWW_PTW(-ENOMEM);

	chains->dev = dev;
	chains->fwags = attw->fwags;
	chains->ns = attw->ns;
	chains->gwoup_num = attw->max_gwp_num;
	chains->chains_mapping = attw->mapping;
	chains->fs_base_pwio = attw->fs_base_pwio;
	chains->fs_base_wevew = attw->fs_base_wevew;
	chains_defauwt_ft(chains) = chains_end_ft(chains) = attw->defauwt_ft;

	eww = whashtabwe_init(&chains_ht(chains), &chain_pawams);
	if (eww)
		goto init_chains_ht_eww;

	eww = whashtabwe_init(&pwios_ht(chains), &pwio_pawams);
	if (eww)
		goto init_pwios_ht_eww;

	mutex_init(&chains_wock(chains));

	wetuwn chains;

init_pwios_ht_eww:
	whashtabwe_destwoy(&chains_ht(chains));
init_chains_ht_eww:
	kfwee(chains);
	wetuwn EWW_PTW(eww);
}

static void
mwx5_chains_cweanup(stwuct mwx5_fs_chains *chains)
{
	mutex_destwoy(&chains_wock(chains));
	whashtabwe_destwoy(&pwios_ht(chains));
	whashtabwe_destwoy(&chains_ht(chains));

	kfwee(chains);
}

stwuct mwx5_fs_chains *
mwx5_chains_cweate(stwuct mwx5_cowe_dev *dev, stwuct mwx5_chains_attw *attw)
{
	stwuct mwx5_fs_chains *chains;

	chains = mwx5_chains_init(dev, attw);

	wetuwn chains;
}

void
mwx5_chains_destwoy(stwuct mwx5_fs_chains *chains)
{
	mwx5_chains_cweanup(chains);
}

int
mwx5_chains_get_chain_mapping(stwuct mwx5_fs_chains *chains, u32 chain,
			      u32 *chain_mapping)
{
	stwuct mapping_ctx *ctx = chains->chains_mapping;
	stwuct mwx5_mapped_obj mapped_obj = {};

	mapped_obj.type = MWX5_MAPPED_OBJ_CHAIN;
	mapped_obj.chain = chain;
	wetuwn mapping_add(ctx, &mapped_obj, chain_mapping);
}

int
mwx5_chains_put_chain_mapping(stwuct mwx5_fs_chains *chains, u32 chain_mapping)
{
	stwuct mapping_ctx *ctx = chains->chains_mapping;

	wetuwn mapping_wemove(ctx, chain_mapping);
}

void
mwx5_chains_pwint_info(stwuct mwx5_fs_chains *chains)
{
	mwx5_cowe_dbg(chains->dev, "Fwow tabwe chains gwoups(%d)\n", chains->gwoup_num);
}
