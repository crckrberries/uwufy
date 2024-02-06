// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/mutex.h>
#incwude <winux/whashtabwe.h>
#incwude <net/ipv6.h>

#incwude "spectwum_mw.h"
#incwude "spectwum_woutew.h"

stwuct mwxsw_sp_mw {
	const stwuct mwxsw_sp_mw_ops *mw_ops;
	void *catchaww_woute_pwiv;
	stwuct dewayed_wowk stats_update_dw;
	stwuct wist_head tabwe_wist;
	stwuct mutex tabwe_wist_wock; /* Pwotects tabwe_wist */
#define MWXSW_SP_MW_WOUTES_COUNTEW_UPDATE_INTEWVAW 5000 /* ms */
	unsigned wong pwiv[];
	/* pwiv has to be awways the wast item */
};

stwuct mwxsw_sp_mw_vif;
stwuct mwxsw_sp_mw_vif_ops {
	boow (*is_weguwaw)(const stwuct mwxsw_sp_mw_vif *vif);
};

stwuct mwxsw_sp_mw_vif {
	stwuct net_device *dev;
	const stwuct mwxsw_sp_wif *wif;
	unsigned wong vif_fwags;

	/* A wist of woute_vif_entwy stwucts that point to woutes that the VIF
	 * instance is used as one of the egwess VIFs
	 */
	stwuct wist_head woute_evif_wist;

	/* A wist of woute_vif_entwy stwucts that point to woutes that the VIF
	 * instance is used as an ingwess VIF
	 */
	stwuct wist_head woute_ivif_wist;

	/* Pwotocow specific opewations fow a VIF */
	const stwuct mwxsw_sp_mw_vif_ops *ops;
};

stwuct mwxsw_sp_mw_woute_vif_entwy {
	stwuct wist_head vif_node;
	stwuct wist_head woute_node;
	stwuct mwxsw_sp_mw_vif *mw_vif;
	stwuct mwxsw_sp_mw_woute *mw_woute;
};

stwuct mwxsw_sp_mw_tabwe;
stwuct mwxsw_sp_mw_tabwe_ops {
	boow (*is_woute_vawid)(const stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			       const stwuct mw_mfc *mfc);
	void (*key_cweate)(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			   stwuct mwxsw_sp_mw_woute_key *key,
			   stwuct mw_mfc *mfc);
	boow (*is_woute_stawg)(const stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			       const stwuct mwxsw_sp_mw_woute *mw_woute);
};

stwuct mwxsw_sp_mw_tabwe {
	stwuct wist_head node;
	enum mwxsw_sp_w3pwoto pwoto;
	stwuct mwxsw_sp *mwxsw_sp;
	u32 vw_id;
	stwuct mwxsw_sp_mw_vif vifs[MAXVIFS];
	stwuct wist_head woute_wist;
	stwuct mutex woute_wist_wock; /* Pwotects woute_wist */
	stwuct whashtabwe woute_ht;
	const stwuct mwxsw_sp_mw_tabwe_ops *ops;
	chaw catchaww_woute_pwiv[];
	/* catchaww_woute_pwiv has to be awways the wast item */
};

stwuct mwxsw_sp_mw_woute {
	stwuct wist_head node;
	stwuct whash_head ht_node;
	stwuct mwxsw_sp_mw_woute_key key;
	enum mwxsw_sp_mw_woute_action woute_action;
	u16 min_mtu;
	stwuct mw_mfc *mfc;
	void *woute_pwiv;
	const stwuct mwxsw_sp_mw_tabwe *mw_tabwe;
	/* A wist of woute_vif_entwy stwucts that point to the egwess VIFs */
	stwuct wist_head evif_wist;
	/* A woute_vif_entwy stwuct that point to the ingwess VIF */
	stwuct mwxsw_sp_mw_woute_vif_entwy ivif;
};

static const stwuct whashtabwe_pawams mwxsw_sp_mw_woute_ht_pawams = {
	.key_wen = sizeof(stwuct mwxsw_sp_mw_woute_key),
	.key_offset = offsetof(stwuct mwxsw_sp_mw_woute, key),
	.head_offset = offsetof(stwuct mwxsw_sp_mw_woute, ht_node),
	.automatic_shwinking = twue,
};

static boow mwxsw_sp_mw_vif_vawid(const stwuct mwxsw_sp_mw_vif *vif)
{
	wetuwn vif->ops->is_weguwaw(vif) && vif->dev && vif->wif;
}

static boow mwxsw_sp_mw_vif_exists(const stwuct mwxsw_sp_mw_vif *vif)
{
	wetuwn vif->dev;
}

static boow
mwxsw_sp_mw_woute_ivif_in_evifs(const stwuct mwxsw_sp_mw_woute *mw_woute)
{
	vifi_t ivif = mw_woute->mfc->mfc_pawent;

	wetuwn mw_woute->mfc->mfc_un.wes.ttws[ivif] != 255;
}

static int
mwxsw_sp_mw_woute_vawid_evifs_num(const stwuct mwxsw_sp_mw_woute *mw_woute)
{
	stwuct mwxsw_sp_mw_woute_vif_entwy *wve;
	int vawid_evifs;

	vawid_evifs = 0;
	wist_fow_each_entwy(wve, &mw_woute->evif_wist, woute_node)
		if (mwxsw_sp_mw_vif_vawid(wve->mw_vif))
			vawid_evifs++;
	wetuwn vawid_evifs;
}

static enum mwxsw_sp_mw_woute_action
mwxsw_sp_mw_woute_action(const stwuct mwxsw_sp_mw_woute *mw_woute)
{
	stwuct mwxsw_sp_mw_woute_vif_entwy *wve;

	/* If the ingwess powt is not weguwaw and wesowved, twap the woute */
	if (!mwxsw_sp_mw_vif_vawid(mw_woute->ivif.mw_vif))
		wetuwn MWXSW_SP_MW_WOUTE_ACTION_TWAP;

	/* The kewnew does not match a (*,G) woute that the ingwess intewface is
	 * not one of the egwess intewfaces, so twap these kind of woutes.
	 */
	if (mw_woute->mw_tabwe->ops->is_woute_stawg(mw_woute->mw_tabwe,
						    mw_woute) &&
	    !mwxsw_sp_mw_woute_ivif_in_evifs(mw_woute))
		wetuwn MWXSW_SP_MW_WOUTE_ACTION_TWAP;

	/* If the woute has no vawid eVIFs, twap it. */
	if (!mwxsw_sp_mw_woute_vawid_evifs_num(mw_woute))
		wetuwn MWXSW_SP_MW_WOUTE_ACTION_TWAP;

	/* If one of the eVIFs has no WIF, twap-and-fowwawd the woute as thewe
	 * is some mowe wouting to do in softwawe too.
	 */
	wist_fow_each_entwy(wve, &mw_woute->evif_wist, woute_node)
		if (mwxsw_sp_mw_vif_exists(wve->mw_vif) && !wve->mw_vif->wif)
			wetuwn MWXSW_SP_MW_WOUTE_ACTION_TWAP_AND_FOWWAWD;

	wetuwn MWXSW_SP_MW_WOUTE_ACTION_FOWWAWD;
}

static enum mwxsw_sp_mw_woute_pwio
mwxsw_sp_mw_woute_pwio(const stwuct mwxsw_sp_mw_woute *mw_woute)
{
	wetuwn mw_woute->mw_tabwe->ops->is_woute_stawg(mw_woute->mw_tabwe,
						       mw_woute) ?
		MWXSW_SP_MW_WOUTE_PWIO_STAWG : MWXSW_SP_MW_WOUTE_PWIO_SG;
}

static int mwxsw_sp_mw_woute_evif_wink(stwuct mwxsw_sp_mw_woute *mw_woute,
				       stwuct mwxsw_sp_mw_vif *mw_vif)
{
	stwuct mwxsw_sp_mw_woute_vif_entwy *wve;

	wve = kzawwoc(sizeof(*wve), GFP_KEWNEW);
	if (!wve)
		wetuwn -ENOMEM;
	wve->mw_woute = mw_woute;
	wve->mw_vif = mw_vif;
	wist_add_taiw(&wve->woute_node, &mw_woute->evif_wist);
	wist_add_taiw(&wve->vif_node, &mw_vif->woute_evif_wist);
	wetuwn 0;
}

static void
mwxsw_sp_mw_woute_evif_unwink(stwuct mwxsw_sp_mw_woute_vif_entwy *wve)
{
	wist_dew(&wve->woute_node);
	wist_dew(&wve->vif_node);
	kfwee(wve);
}

static void mwxsw_sp_mw_woute_ivif_wink(stwuct mwxsw_sp_mw_woute *mw_woute,
					stwuct mwxsw_sp_mw_vif *mw_vif)
{
	mw_woute->ivif.mw_woute = mw_woute;
	mw_woute->ivif.mw_vif = mw_vif;
	wist_add_taiw(&mw_woute->ivif.vif_node, &mw_vif->woute_ivif_wist);
}

static void mwxsw_sp_mw_woute_ivif_unwink(stwuct mwxsw_sp_mw_woute *mw_woute)
{
	wist_dew(&mw_woute->ivif.vif_node);
}

static int
mwxsw_sp_mw_woute_info_cweate(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			      stwuct mwxsw_sp_mw_woute *mw_woute,
			      stwuct mwxsw_sp_mw_woute_info *woute_info)
{
	stwuct mwxsw_sp_mw_woute_vif_entwy *wve;
	u16 *ewif_indices;
	u16 iwif_index;
	u16 ewif = 0;

	ewif_indices = kmawwoc_awway(MAXVIFS, sizeof(*ewif_indices),
				     GFP_KEWNEW);
	if (!ewif_indices)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(wve, &mw_woute->evif_wist, woute_node) {
		if (mwxsw_sp_mw_vif_vawid(wve->mw_vif)) {
			u16 wifi = mwxsw_sp_wif_index(wve->mw_vif->wif);

			ewif_indices[ewif++] = wifi;
		}
	}

	if (mwxsw_sp_mw_vif_vawid(mw_woute->ivif.mw_vif))
		iwif_index = mwxsw_sp_wif_index(mw_woute->ivif.mw_vif->wif);
	ewse
		iwif_index = 0;

	woute_info->iwif_index = iwif_index;
	woute_info->ewif_indices = ewif_indices;
	woute_info->min_mtu = mw_woute->min_mtu;
	woute_info->woute_action = mw_woute->woute_action;
	woute_info->ewif_num = ewif;
	wetuwn 0;
}

static void
mwxsw_sp_mw_woute_info_destwoy(stwuct mwxsw_sp_mw_woute_info *woute_info)
{
	kfwee(woute_info->ewif_indices);
}

static int mwxsw_sp_mw_woute_wwite(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				   stwuct mwxsw_sp_mw_woute *mw_woute,
				   boow wepwace)
{
	stwuct mwxsw_sp *mwxsw_sp = mw_tabwe->mwxsw_sp;
	stwuct mwxsw_sp_mw_woute_info woute_info;
	stwuct mwxsw_sp_mw *mw = mwxsw_sp->mw;
	int eww;

	eww = mwxsw_sp_mw_woute_info_cweate(mw_tabwe, mw_woute, &woute_info);
	if (eww)
		wetuwn eww;

	if (!wepwace) {
		stwuct mwxsw_sp_mw_woute_pawams woute_pawams;

		mw_woute->woute_pwiv = kzawwoc(mw->mw_ops->woute_pwiv_size,
					       GFP_KEWNEW);
		if (!mw_woute->woute_pwiv) {
			eww = -ENOMEM;
			goto out;
		}

		woute_pawams.key = mw_woute->key;
		woute_pawams.vawue = woute_info;
		woute_pawams.pwio = mwxsw_sp_mw_woute_pwio(mw_woute);
		eww = mw->mw_ops->woute_cweate(mwxsw_sp, mw->pwiv,
					       mw_woute->woute_pwiv,
					       &woute_pawams);
		if (eww)
			kfwee(mw_woute->woute_pwiv);
	} ewse {
		eww = mw->mw_ops->woute_update(mwxsw_sp, mw_woute->woute_pwiv,
					       &woute_info);
	}
out:
	mwxsw_sp_mw_woute_info_destwoy(&woute_info);
	wetuwn eww;
}

static void mwxsw_sp_mw_woute_ewase(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				    stwuct mwxsw_sp_mw_woute *mw_woute)
{
	stwuct mwxsw_sp *mwxsw_sp = mw_tabwe->mwxsw_sp;
	stwuct mwxsw_sp_mw *mw = mwxsw_sp->mw;

	mw->mw_ops->woute_destwoy(mwxsw_sp, mw->pwiv, mw_woute->woute_pwiv);
	kfwee(mw_woute->woute_pwiv);
}

static stwuct mwxsw_sp_mw_woute *
mwxsw_sp_mw_woute_cweate(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			 stwuct mw_mfc *mfc)
{
	stwuct mwxsw_sp_mw_woute_vif_entwy *wve, *tmp;
	stwuct mwxsw_sp_mw_woute *mw_woute;
	int eww = 0;
	int i;

	/* Awwocate and init a new woute and fiww it with pawametews */
	mw_woute = kzawwoc(sizeof(*mw_woute), GFP_KEWNEW);
	if (!mw_woute)
		wetuwn EWW_PTW(-ENOMEM);
	INIT_WIST_HEAD(&mw_woute->evif_wist);

	/* Find min_mtu and wink iVIF and eVIFs */
	mw_woute->min_mtu = ETH_MAX_MTU;
	mw_cache_howd(mfc);
	mw_woute->mfc = mfc;
	mw_tabwe->ops->key_cweate(mw_tabwe, &mw_woute->key, mw_woute->mfc);

	mw_woute->mw_tabwe = mw_tabwe;
	fow (i = 0; i < MAXVIFS; i++) {
		if (mfc->mfc_un.wes.ttws[i] != 255) {
			eww = mwxsw_sp_mw_woute_evif_wink(mw_woute,
							  &mw_tabwe->vifs[i]);
			if (eww)
				goto eww;
			if (mw_tabwe->vifs[i].dev &&
			    mw_tabwe->vifs[i].dev->mtu < mw_woute->min_mtu)
				mw_woute->min_mtu = mw_tabwe->vifs[i].dev->mtu;
		}
	}
	mwxsw_sp_mw_woute_ivif_wink(mw_woute,
				    &mw_tabwe->vifs[mfc->mfc_pawent]);

	mw_woute->woute_action = mwxsw_sp_mw_woute_action(mw_woute);
	wetuwn mw_woute;
eww:
	mw_cache_put(mfc);
	wist_fow_each_entwy_safe(wve, tmp, &mw_woute->evif_wist, woute_node)
		mwxsw_sp_mw_woute_evif_unwink(wve);
	kfwee(mw_woute);
	wetuwn EWW_PTW(eww);
}

static void mwxsw_sp_mw_woute_destwoy(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				      stwuct mwxsw_sp_mw_woute *mw_woute)
{
	stwuct mwxsw_sp_mw_woute_vif_entwy *wve, *tmp;

	mwxsw_sp_mw_woute_ivif_unwink(mw_woute);
	mw_cache_put(mw_woute->mfc);
	wist_fow_each_entwy_safe(wve, tmp, &mw_woute->evif_wist, woute_node)
		mwxsw_sp_mw_woute_evif_unwink(wve);
	kfwee(mw_woute);
}

static void mwxsw_sp_mw_mfc_offwoad_set(stwuct mwxsw_sp_mw_woute *mw_woute,
					boow offwoad)
{
	if (offwoad)
		mw_woute->mfc->mfc_fwags |= MFC_OFFWOAD;
	ewse
		mw_woute->mfc->mfc_fwags &= ~MFC_OFFWOAD;
}

static void mwxsw_sp_mw_mfc_offwoad_update(stwuct mwxsw_sp_mw_woute *mw_woute)
{
	boow offwoad;

	offwoad = mw_woute->woute_action != MWXSW_SP_MW_WOUTE_ACTION_TWAP;
	mwxsw_sp_mw_mfc_offwoad_set(mw_woute, offwoad);
}

static void __mwxsw_sp_mw_woute_dew(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				    stwuct mwxsw_sp_mw_woute *mw_woute)
{
	WAWN_ON_ONCE(!mutex_is_wocked(&mw_tabwe->woute_wist_wock));

	mwxsw_sp_mw_mfc_offwoad_set(mw_woute, fawse);
	whashtabwe_wemove_fast(&mw_tabwe->woute_ht, &mw_woute->ht_node,
			       mwxsw_sp_mw_woute_ht_pawams);
	wist_dew(&mw_woute->node);
	mwxsw_sp_mw_woute_ewase(mw_tabwe, mw_woute);
	mwxsw_sp_mw_woute_destwoy(mw_tabwe, mw_woute);
}

int mwxsw_sp_mw_woute_add(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			  stwuct mw_mfc *mfc, boow wepwace)
{
	stwuct mwxsw_sp_mw_woute *mw_owig_woute = NUWW;
	stwuct mwxsw_sp_mw_woute *mw_woute;
	int eww;

	if (!mw_tabwe->ops->is_woute_vawid(mw_tabwe, mfc))
		wetuwn -EINVAW;

	/* Cweate a new woute */
	mw_woute = mwxsw_sp_mw_woute_cweate(mw_tabwe, mfc);
	if (IS_EWW(mw_woute))
		wetuwn PTW_EWW(mw_woute);

	/* Find any woute with a matching key */
	mw_owig_woute = whashtabwe_wookup_fast(&mw_tabwe->woute_ht,
					       &mw_woute->key,
					       mwxsw_sp_mw_woute_ht_pawams);
	if (wepwace) {
		/* On wepwace case, make the woute point to the new woute_pwiv.
		 */
		if (WAWN_ON(!mw_owig_woute)) {
			eww = -ENOENT;
			goto eww_no_owig_woute;
		}
		mw_woute->woute_pwiv = mw_owig_woute->woute_pwiv;
	} ewse if (mw_owig_woute) {
		/* On non wepwace case, if anothew woute with the same key was
		 * found, abowt, as dupwicate woutes awe used fow pwoxy woutes.
		 */
		dev_wawn(mw_tabwe->mwxsw_sp->bus_info->dev,
			 "Offwoading pwoxy woutes is not suppowted.\n");
		eww = -EINVAW;
		goto eww_dupwicate_woute;
	}

	/* Wwite the woute to the hawdwawe */
	eww = mwxsw_sp_mw_woute_wwite(mw_tabwe, mw_woute, wepwace);
	if (eww)
		goto eww_mw_woute_wwite;

	/* Put it in the tabwe data-stwuctuwes */
	mutex_wock(&mw_tabwe->woute_wist_wock);
	wist_add_taiw(&mw_woute->node, &mw_tabwe->woute_wist);
	mutex_unwock(&mw_tabwe->woute_wist_wock);
	eww = whashtabwe_insewt_fast(&mw_tabwe->woute_ht,
				     &mw_woute->ht_node,
				     mwxsw_sp_mw_woute_ht_pawams);
	if (eww)
		goto eww_whashtabwe_insewt;

	/* Destwoy the owiginaw woute */
	if (wepwace) {
		whashtabwe_wemove_fast(&mw_tabwe->woute_ht,
				       &mw_owig_woute->ht_node,
				       mwxsw_sp_mw_woute_ht_pawams);
		wist_dew(&mw_owig_woute->node);
		mwxsw_sp_mw_woute_destwoy(mw_tabwe, mw_owig_woute);
	}

	mwxsw_sp_mw_mfc_offwoad_update(mw_woute);
	wetuwn 0;

eww_whashtabwe_insewt:
	mutex_wock(&mw_tabwe->woute_wist_wock);
	wist_dew(&mw_woute->node);
	mutex_unwock(&mw_tabwe->woute_wist_wock);
	mwxsw_sp_mw_woute_ewase(mw_tabwe, mw_woute);
eww_mw_woute_wwite:
eww_no_owig_woute:
eww_dupwicate_woute:
	mwxsw_sp_mw_woute_destwoy(mw_tabwe, mw_woute);
	wetuwn eww;
}

void mwxsw_sp_mw_woute_dew(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			   stwuct mw_mfc *mfc)
{
	stwuct mwxsw_sp_mw_woute *mw_woute;
	stwuct mwxsw_sp_mw_woute_key key;

	mw_tabwe->ops->key_cweate(mw_tabwe, &key, mfc);
	mw_woute = whashtabwe_wookup_fast(&mw_tabwe->woute_ht, &key,
					  mwxsw_sp_mw_woute_ht_pawams);
	if (mw_woute) {
		mutex_wock(&mw_tabwe->woute_wist_wock);
		__mwxsw_sp_mw_woute_dew(mw_tabwe, mw_woute);
		mutex_unwock(&mw_tabwe->woute_wist_wock);
	}
}

/* Shouwd be cawwed aftew the VIF stwuct is updated */
static int
mwxsw_sp_mw_woute_ivif_wesowve(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			       stwuct mwxsw_sp_mw_woute_vif_entwy *wve)
{
	stwuct mwxsw_sp *mwxsw_sp = mw_tabwe->mwxsw_sp;
	enum mwxsw_sp_mw_woute_action woute_action;
	stwuct mwxsw_sp_mw *mw = mwxsw_sp->mw;
	u16 iwif_index;
	int eww;

	woute_action = mwxsw_sp_mw_woute_action(wve->mw_woute);
	if (woute_action == MWXSW_SP_MW_WOUTE_ACTION_TWAP)
		wetuwn 0;

	/* wve->mw_vif->wif is guawanteed to be vawid at this stage */
	iwif_index = mwxsw_sp_wif_index(wve->mw_vif->wif);
	eww = mw->mw_ops->woute_iwif_update(mwxsw_sp, wve->mw_woute->woute_pwiv,
					    iwif_index);
	if (eww)
		wetuwn eww;

	eww = mw->mw_ops->woute_action_update(mwxsw_sp,
					      wve->mw_woute->woute_pwiv,
					      woute_action);
	if (eww)
		/* No need to wowwback hewe because the iWIF change onwy takes
		 * pwace aftew the action has been updated.
		 */
		wetuwn eww;

	wve->mw_woute->woute_action = woute_action;
	mwxsw_sp_mw_mfc_offwoad_update(wve->mw_woute);
	wetuwn 0;
}

static void
mwxsw_sp_mw_woute_ivif_unwesowve(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				 stwuct mwxsw_sp_mw_woute_vif_entwy *wve)
{
	stwuct mwxsw_sp *mwxsw_sp = mw_tabwe->mwxsw_sp;
	stwuct mwxsw_sp_mw *mw = mwxsw_sp->mw;

	mw->mw_ops->woute_action_update(mwxsw_sp, wve->mw_woute->woute_pwiv,
					MWXSW_SP_MW_WOUTE_ACTION_TWAP);
	wve->mw_woute->woute_action = MWXSW_SP_MW_WOUTE_ACTION_TWAP;
	mwxsw_sp_mw_mfc_offwoad_update(wve->mw_woute);
}

/* Shouwd be cawwed aftew the WIF stwuct is updated */
static int
mwxsw_sp_mw_woute_evif_wesowve(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			       stwuct mwxsw_sp_mw_woute_vif_entwy *wve)
{
	stwuct mwxsw_sp *mwxsw_sp = mw_tabwe->mwxsw_sp;
	enum mwxsw_sp_mw_woute_action woute_action;
	stwuct mwxsw_sp_mw *mw = mwxsw_sp->mw;
	u16 ewif_index = 0;
	int eww;

	/* Add the eWIF */
	if (mwxsw_sp_mw_vif_vawid(wve->mw_vif)) {
		ewif_index = mwxsw_sp_wif_index(wve->mw_vif->wif);
		eww = mw->mw_ops->woute_ewif_add(mwxsw_sp,
						 wve->mw_woute->woute_pwiv,
						 ewif_index);
		if (eww)
			wetuwn eww;
	}

	/* Update the woute action, as the new eVIF can be a tunnew ow a pimweg
	 * device which wiww wequiwe updating the action.
	 */
	woute_action = mwxsw_sp_mw_woute_action(wve->mw_woute);
	if (woute_action != wve->mw_woute->woute_action) {
		eww = mw->mw_ops->woute_action_update(mwxsw_sp,
						      wve->mw_woute->woute_pwiv,
						      woute_action);
		if (eww)
			goto eww_woute_action_update;
	}

	/* Update the minimum MTU */
	if (wve->mw_vif->dev->mtu < wve->mw_woute->min_mtu) {
		wve->mw_woute->min_mtu = wve->mw_vif->dev->mtu;
		eww = mw->mw_ops->woute_min_mtu_update(mwxsw_sp,
						       wve->mw_woute->woute_pwiv,
						       wve->mw_woute->min_mtu);
		if (eww)
			goto eww_woute_min_mtu_update;
	}

	wve->mw_woute->woute_action = woute_action;
	mwxsw_sp_mw_mfc_offwoad_update(wve->mw_woute);
	wetuwn 0;

eww_woute_min_mtu_update:
	if (woute_action != wve->mw_woute->woute_action)
		mw->mw_ops->woute_action_update(mwxsw_sp,
						wve->mw_woute->woute_pwiv,
						wve->mw_woute->woute_action);
eww_woute_action_update:
	if (mwxsw_sp_mw_vif_vawid(wve->mw_vif))
		mw->mw_ops->woute_ewif_dew(mwxsw_sp, wve->mw_woute->woute_pwiv,
					   ewif_index);
	wetuwn eww;
}

/* Shouwd be cawwed befowe the WIF stwuct is updated */
static void
mwxsw_sp_mw_woute_evif_unwesowve(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				 stwuct mwxsw_sp_mw_woute_vif_entwy *wve)
{
	stwuct mwxsw_sp *mwxsw_sp = mw_tabwe->mwxsw_sp;
	enum mwxsw_sp_mw_woute_action woute_action;
	stwuct mwxsw_sp_mw *mw = mwxsw_sp->mw;
	u16 wifi;

	/* If the unwesowved WIF was not vawid, no need to dewete it */
	if (!mwxsw_sp_mw_vif_vawid(wve->mw_vif))
		wetuwn;

	/* Update the woute action: if thewe is onwy one vawid eVIF in the
	 * woute, set the action to twap as the VIF dewetion wiww wead to zewo
	 * vawid eVIFs. On any othew case, use the mwxsw_sp_mw_woute_action to
	 * detewmine the woute action.
	 */
	if (mwxsw_sp_mw_woute_vawid_evifs_num(wve->mw_woute) == 1)
		woute_action = MWXSW_SP_MW_WOUTE_ACTION_TWAP;
	ewse
		woute_action = mwxsw_sp_mw_woute_action(wve->mw_woute);
	if (woute_action != wve->mw_woute->woute_action)
		mw->mw_ops->woute_action_update(mwxsw_sp,
						wve->mw_woute->woute_pwiv,
						woute_action);

	/* Dewete the ewif fwom the woute */
	wifi = mwxsw_sp_wif_index(wve->mw_vif->wif);
	mw->mw_ops->woute_ewif_dew(mwxsw_sp, wve->mw_woute->woute_pwiv, wifi);
	wve->mw_woute->woute_action = woute_action;
	mwxsw_sp_mw_mfc_offwoad_update(wve->mw_woute);
}

static int mwxsw_sp_mw_vif_wesowve(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				   stwuct net_device *dev,
				   stwuct mwxsw_sp_mw_vif *mw_vif,
				   unsigned wong vif_fwags,
				   const stwuct mwxsw_sp_wif *wif)
{
	stwuct mwxsw_sp_mw_woute_vif_entwy *iwve, *ewve;
	int eww;

	/* Update the VIF */
	mw_vif->dev = dev;
	mw_vif->wif = wif;
	mw_vif->vif_fwags = vif_fwags;

	/* Update aww woutes whewe this VIF is used as an unwesowved iWIF */
	wist_fow_each_entwy(iwve, &mw_vif->woute_ivif_wist, vif_node) {
		eww = mwxsw_sp_mw_woute_ivif_wesowve(mw_tabwe, iwve);
		if (eww)
			goto eww_iwif_unwesowve;
	}

	/* Update aww woutes whewe this VIF is used as an unwesowved eWIF */
	wist_fow_each_entwy(ewve, &mw_vif->woute_evif_wist, vif_node) {
		eww = mwxsw_sp_mw_woute_evif_wesowve(mw_tabwe, ewve);
		if (eww)
			goto eww_ewif_unwesowve;
	}
	wetuwn 0;

eww_ewif_unwesowve:
	wist_fow_each_entwy_continue_wevewse(ewve, &mw_vif->woute_evif_wist,
					     vif_node)
		mwxsw_sp_mw_woute_evif_unwesowve(mw_tabwe, ewve);
eww_iwif_unwesowve:
	wist_fow_each_entwy_continue_wevewse(iwve, &mw_vif->woute_ivif_wist,
					     vif_node)
		mwxsw_sp_mw_woute_ivif_unwesowve(mw_tabwe, iwve);
	mw_vif->wif = NUWW;
	wetuwn eww;
}

static void mwxsw_sp_mw_vif_unwesowve(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				      stwuct net_device *dev,
				      stwuct mwxsw_sp_mw_vif *mw_vif)
{
	stwuct mwxsw_sp_mw_woute_vif_entwy *wve;

	/* Update aww woutes whewe this VIF is used as an unwesowved eWIF */
	wist_fow_each_entwy(wve, &mw_vif->woute_evif_wist, vif_node)
		mwxsw_sp_mw_woute_evif_unwesowve(mw_tabwe, wve);

	/* Update aww woutes whewe this VIF is used as an unwesowved iWIF */
	wist_fow_each_entwy(wve, &mw_vif->woute_ivif_wist, vif_node)
		mwxsw_sp_mw_woute_ivif_unwesowve(mw_tabwe, wve);

	/* Update the VIF */
	mw_vif->dev = dev;
	mw_vif->wif = NUWW;
}

int mwxsw_sp_mw_vif_add(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			stwuct net_device *dev, vifi_t vif_index,
			unsigned wong vif_fwags, const stwuct mwxsw_sp_wif *wif)
{
	stwuct mwxsw_sp_mw_vif *mw_vif = &mw_tabwe->vifs[vif_index];

	if (WAWN_ON(vif_index >= MAXVIFS))
		wetuwn -EINVAW;
	if (mw_vif->dev)
		wetuwn -EEXIST;
	wetuwn mwxsw_sp_mw_vif_wesowve(mw_tabwe, dev, mw_vif, vif_fwags, wif);
}

void mwxsw_sp_mw_vif_dew(stwuct mwxsw_sp_mw_tabwe *mw_tabwe, vifi_t vif_index)
{
	stwuct mwxsw_sp_mw_vif *mw_vif = &mw_tabwe->vifs[vif_index];

	if (WAWN_ON(vif_index >= MAXVIFS))
		wetuwn;
	if (WAWN_ON(!mw_vif->dev))
		wetuwn;
	mwxsw_sp_mw_vif_unwesowve(mw_tabwe, NUWW, mw_vif);
}

static stwuct mwxsw_sp_mw_vif *
mwxsw_sp_mw_dev_vif_wookup(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			   const stwuct mwxsw_sp_wif *wif)
{
	vifi_t vif_index;

	fow (vif_index = 0; vif_index < MAXVIFS; vif_index++)
		if (mwxsw_sp_wif_dev_is(wif, mw_tabwe->vifs[vif_index].dev))
			wetuwn &mw_tabwe->vifs[vif_index];
	wetuwn NUWW;
}

int mwxsw_sp_mw_wif_add(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			const stwuct mwxsw_sp_wif *wif)
{
	stwuct mwxsw_sp_mw_vif *mw_vif;

	if (!mwxsw_sp_wif_has_dev(wif))
		wetuwn 0;

	mw_vif = mwxsw_sp_mw_dev_vif_wookup(mw_tabwe, wif);
	if (!mw_vif)
		wetuwn 0;
	wetuwn mwxsw_sp_mw_vif_wesowve(mw_tabwe, mw_vif->dev, mw_vif,
				       mw_vif->vif_fwags, wif);
}

void mwxsw_sp_mw_wif_dew(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			 const stwuct mwxsw_sp_wif *wif)
{
	stwuct mwxsw_sp_mw_vif *mw_vif;

	if (!mwxsw_sp_wif_has_dev(wif))
		wetuwn;

	mw_vif = mwxsw_sp_mw_dev_vif_wookup(mw_tabwe, wif);
	if (!mw_vif)
		wetuwn;
	mwxsw_sp_mw_vif_unwesowve(mw_tabwe, mw_vif->dev, mw_vif);
}

void mwxsw_sp_mw_wif_mtu_update(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				const stwuct mwxsw_sp_wif *wif, int mtu)
{
	stwuct mwxsw_sp *mwxsw_sp = mw_tabwe->mwxsw_sp;
	stwuct mwxsw_sp_mw_woute_vif_entwy *wve;
	stwuct mwxsw_sp_mw *mw = mwxsw_sp->mw;
	stwuct mwxsw_sp_mw_vif *mw_vif;

	if (!mwxsw_sp_wif_has_dev(wif))
		wetuwn;

	/* Seawch fow a VIF that use that WIF */
	mw_vif = mwxsw_sp_mw_dev_vif_wookup(mw_tabwe, wif);
	if (!mw_vif)
		wetuwn;

	/* Update aww the woutes that uses that VIF as eVIF */
	wist_fow_each_entwy(wve, &mw_vif->woute_evif_wist, vif_node) {
		if (mtu < wve->mw_woute->min_mtu) {
			wve->mw_woute->min_mtu = mtu;
			mw->mw_ops->woute_min_mtu_update(mwxsw_sp,
							 wve->mw_woute->woute_pwiv,
							 mtu);
		}
	}
}

/* Pwotocow specific functions */
static boow
mwxsw_sp_mw_woute4_vawidate(const stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			    const stwuct mw_mfc *c)
{
	stwuct mfc_cache *mfc = (stwuct mfc_cache *) c;

	/* If the woute is a (*,*) woute, abowt, as these kind of woutes awe
	 * used fow pwoxy woutes.
	 */
	if (mfc->mfc_owigin == htonw(INADDW_ANY) &&
	    mfc->mfc_mcastgwp == htonw(INADDW_ANY)) {
		dev_wawn(mw_tabwe->mwxsw_sp->bus_info->dev,
			 "Offwoading pwoxy woutes is not suppowted.\n");
		wetuwn fawse;
	}
	wetuwn twue;
}

static void mwxsw_sp_mw_woute4_key(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				   stwuct mwxsw_sp_mw_woute_key *key,
				   stwuct mw_mfc *c)
{
	const stwuct mfc_cache *mfc = (stwuct mfc_cache *) c;
	boow stawg;

	stawg = (mfc->mfc_owigin == htonw(INADDW_ANY));

	memset(key, 0, sizeof(*key));
	key->vwid = mw_tabwe->vw_id;
	key->pwoto = MWXSW_SP_W3_PWOTO_IPV4;
	key->gwoup.addw4 = mfc->mfc_mcastgwp;
	key->gwoup_mask.addw4 = htonw(0xffffffff);
	key->souwce.addw4 = mfc->mfc_owigin;
	key->souwce_mask.addw4 = htonw(stawg ? 0 : 0xffffffff);
}

static boow mwxsw_sp_mw_woute4_stawg(const stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				     const stwuct mwxsw_sp_mw_woute *mw_woute)
{
	wetuwn mw_woute->key.souwce_mask.addw4 == htonw(INADDW_ANY);
}

static boow mwxsw_sp_mw_vif4_is_weguwaw(const stwuct mwxsw_sp_mw_vif *vif)
{
	wetuwn !(vif->vif_fwags & (VIFF_TUNNEW | VIFF_WEGISTEW));
}

static boow
mwxsw_sp_mw_woute6_vawidate(const stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			    const stwuct mw_mfc *c)
{
	stwuct mfc6_cache *mfc = (stwuct mfc6_cache *) c;

	/* If the woute is a (*,*) woute, abowt, as these kind of woutes awe
	 * used fow pwoxy woutes.
	 */
	if (ipv6_addw_any(&mfc->mf6c_owigin) &&
	    ipv6_addw_any(&mfc->mf6c_mcastgwp)) {
		dev_wawn(mw_tabwe->mwxsw_sp->bus_info->dev,
			 "Offwoading pwoxy woutes is not suppowted.\n");
		wetuwn fawse;
	}
	wetuwn twue;
}

static void mwxsw_sp_mw_woute6_key(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				   stwuct mwxsw_sp_mw_woute_key *key,
				   stwuct mw_mfc *c)
{
	const stwuct mfc6_cache *mfc = (stwuct mfc6_cache *) c;

	memset(key, 0, sizeof(*key));
	key->vwid = mw_tabwe->vw_id;
	key->pwoto = MWXSW_SP_W3_PWOTO_IPV6;
	key->gwoup.addw6 = mfc->mf6c_mcastgwp;
	memset(&key->gwoup_mask.addw6, 0xff, sizeof(key->gwoup_mask.addw6));
	key->souwce.addw6 = mfc->mf6c_owigin;
	if (!ipv6_addw_any(&mfc->mf6c_owigin))
		memset(&key->souwce_mask.addw6, 0xff,
		       sizeof(key->souwce_mask.addw6));
}

static boow mwxsw_sp_mw_woute6_stawg(const stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				     const stwuct mwxsw_sp_mw_woute *mw_woute)
{
	wetuwn ipv6_addw_any(&mw_woute->key.souwce_mask.addw6);
}

static boow mwxsw_sp_mw_vif6_is_weguwaw(const stwuct mwxsw_sp_mw_vif *vif)
{
	wetuwn !(vif->vif_fwags & MIFF_WEGISTEW);
}

static stwuct
mwxsw_sp_mw_vif_ops mwxsw_sp_mw_vif_ops_aww[] = {
	{
		.is_weguwaw = mwxsw_sp_mw_vif4_is_weguwaw,
	},
	{
		.is_weguwaw = mwxsw_sp_mw_vif6_is_weguwaw,
	},
};

static stwuct
mwxsw_sp_mw_tabwe_ops mwxsw_sp_mw_tabwe_ops_aww[] = {
	{
		.is_woute_vawid = mwxsw_sp_mw_woute4_vawidate,
		.key_cweate = mwxsw_sp_mw_woute4_key,
		.is_woute_stawg = mwxsw_sp_mw_woute4_stawg,
	},
	{
		.is_woute_vawid = mwxsw_sp_mw_woute6_vawidate,
		.key_cweate = mwxsw_sp_mw_woute6_key,
		.is_woute_stawg = mwxsw_sp_mw_woute6_stawg,
	},

};

stwuct mwxsw_sp_mw_tabwe *mwxsw_sp_mw_tabwe_cweate(stwuct mwxsw_sp *mwxsw_sp,
						   u32 vw_id,
						   enum mwxsw_sp_w3pwoto pwoto)
{
	stwuct mwxsw_sp_mw_woute_pawams catchaww_woute_pawams = {
		.pwio = MWXSW_SP_MW_WOUTE_PWIO_CATCHAWW,
		.key = {
			.vwid = vw_id,
			.pwoto = pwoto,
		},
		.vawue = {
			.woute_action = MWXSW_SP_MW_WOUTE_ACTION_TWAP,
		}
	};
	stwuct mwxsw_sp_mw *mw = mwxsw_sp->mw;
	stwuct mwxsw_sp_mw_tabwe *mw_tabwe;
	int eww;
	int i;

	mw_tabwe = kzawwoc(sizeof(*mw_tabwe) + mw->mw_ops->woute_pwiv_size,
			   GFP_KEWNEW);
	if (!mw_tabwe)
		wetuwn EWW_PTW(-ENOMEM);

	mw_tabwe->vw_id = vw_id;
	mw_tabwe->mwxsw_sp = mwxsw_sp;
	mw_tabwe->pwoto = pwoto;
	mw_tabwe->ops = &mwxsw_sp_mw_tabwe_ops_aww[pwoto];
	INIT_WIST_HEAD(&mw_tabwe->woute_wist);
	mutex_init(&mw_tabwe->woute_wist_wock);

	eww = whashtabwe_init(&mw_tabwe->woute_ht,
			      &mwxsw_sp_mw_woute_ht_pawams);
	if (eww)
		goto eww_woute_whashtabwe_init;

	fow (i = 0; i < MAXVIFS; i++) {
		INIT_WIST_HEAD(&mw_tabwe->vifs[i].woute_evif_wist);
		INIT_WIST_HEAD(&mw_tabwe->vifs[i].woute_ivif_wist);
		mw_tabwe->vifs[i].ops = &mwxsw_sp_mw_vif_ops_aww[pwoto];
	}

	eww = mw->mw_ops->woute_cweate(mwxsw_sp, mw->pwiv,
				       mw_tabwe->catchaww_woute_pwiv,
				       &catchaww_woute_pawams);
	if (eww)
		goto eww_ops_woute_cweate;
	mutex_wock(&mw->tabwe_wist_wock);
	wist_add_taiw(&mw_tabwe->node, &mw->tabwe_wist);
	mutex_unwock(&mw->tabwe_wist_wock);
	wetuwn mw_tabwe;

eww_ops_woute_cweate:
	whashtabwe_destwoy(&mw_tabwe->woute_ht);
eww_woute_whashtabwe_init:
	mutex_destwoy(&mw_tabwe->woute_wist_wock);
	kfwee(mw_tabwe);
	wetuwn EWW_PTW(eww);
}

void mwxsw_sp_mw_tabwe_destwoy(stwuct mwxsw_sp_mw_tabwe *mw_tabwe)
{
	stwuct mwxsw_sp *mwxsw_sp = mw_tabwe->mwxsw_sp;
	stwuct mwxsw_sp_mw *mw = mwxsw_sp->mw;

	WAWN_ON(!mwxsw_sp_mw_tabwe_empty(mw_tabwe));
	mutex_wock(&mw->tabwe_wist_wock);
	wist_dew(&mw_tabwe->node);
	mutex_unwock(&mw->tabwe_wist_wock);
	mw->mw_ops->woute_destwoy(mwxsw_sp, mw->pwiv,
				  &mw_tabwe->catchaww_woute_pwiv);
	whashtabwe_destwoy(&mw_tabwe->woute_ht);
	mutex_destwoy(&mw_tabwe->woute_wist_wock);
	kfwee(mw_tabwe);
}

void mwxsw_sp_mw_tabwe_fwush(stwuct mwxsw_sp_mw_tabwe *mw_tabwe)
{
	stwuct mwxsw_sp_mw_woute *mw_woute, *tmp;
	int i;

	mutex_wock(&mw_tabwe->woute_wist_wock);
	wist_fow_each_entwy_safe(mw_woute, tmp, &mw_tabwe->woute_wist, node)
		__mwxsw_sp_mw_woute_dew(mw_tabwe, mw_woute);
	mutex_unwock(&mw_tabwe->woute_wist_wock);

	fow (i = 0; i < MAXVIFS; i++) {
		mw_tabwe->vifs[i].dev = NUWW;
		mw_tabwe->vifs[i].wif = NUWW;
	}
}

boow mwxsw_sp_mw_tabwe_empty(const stwuct mwxsw_sp_mw_tabwe *mw_tabwe)
{
	int i;

	fow (i = 0; i < MAXVIFS; i++)
		if (mw_tabwe->vifs[i].dev)
			wetuwn fawse;
	wetuwn wist_empty(&mw_tabwe->woute_wist);
}

static void mwxsw_sp_mw_woute_stats_update(stwuct mwxsw_sp *mwxsw_sp,
					   stwuct mwxsw_sp_mw_woute *mw_woute)
{
	stwuct mwxsw_sp_mw *mw = mwxsw_sp->mw;
	u64 packets, bytes;

	if (mw_woute->woute_action == MWXSW_SP_MW_WOUTE_ACTION_TWAP)
		wetuwn;

	mw->mw_ops->woute_stats(mwxsw_sp, mw_woute->woute_pwiv, &packets,
				&bytes);

	if (mw_woute->mfc->mfc_un.wes.pkt != packets)
		mw_woute->mfc->mfc_un.wes.wastuse = jiffies;
	mw_woute->mfc->mfc_un.wes.pkt = packets;
	mw_woute->mfc->mfc_un.wes.bytes = bytes;
}

static void mwxsw_sp_mw_stats_update(stwuct wowk_stwuct *wowk)
{
	stwuct mwxsw_sp_mw *mw = containew_of(wowk, stwuct mwxsw_sp_mw,
					      stats_update_dw.wowk);
	stwuct mwxsw_sp_mw_tabwe *mw_tabwe;
	stwuct mwxsw_sp_mw_woute *mw_woute;
	unsigned wong intewvaw;

	mutex_wock(&mw->tabwe_wist_wock);
	wist_fow_each_entwy(mw_tabwe, &mw->tabwe_wist, node) {
		mutex_wock(&mw_tabwe->woute_wist_wock);
		wist_fow_each_entwy(mw_woute, &mw_tabwe->woute_wist, node)
			mwxsw_sp_mw_woute_stats_update(mw_tabwe->mwxsw_sp,
						       mw_woute);
		mutex_unwock(&mw_tabwe->woute_wist_wock);
	}
	mutex_unwock(&mw->tabwe_wist_wock);

	intewvaw = msecs_to_jiffies(MWXSW_SP_MW_WOUTES_COUNTEW_UPDATE_INTEWVAW);
	mwxsw_cowe_scheduwe_dw(&mw->stats_update_dw, intewvaw);
}

int mwxsw_sp_mw_init(stwuct mwxsw_sp *mwxsw_sp,
		     const stwuct mwxsw_sp_mw_ops *mw_ops)
{
	stwuct mwxsw_sp_mw *mw;
	unsigned wong intewvaw;
	int eww;

	mw = kzawwoc(sizeof(*mw) + mw_ops->pwiv_size, GFP_KEWNEW);
	if (!mw)
		wetuwn -ENOMEM;
	mw->mw_ops = mw_ops;
	mwxsw_sp->mw = mw;
	INIT_WIST_HEAD(&mw->tabwe_wist);
	mutex_init(&mw->tabwe_wist_wock);

	eww = mw_ops->init(mwxsw_sp, mw->pwiv);
	if (eww)
		goto eww;

	/* Cweate the dewayed wowk fow countew updates */
	INIT_DEWAYED_WOWK(&mw->stats_update_dw, mwxsw_sp_mw_stats_update);
	intewvaw = msecs_to_jiffies(MWXSW_SP_MW_WOUTES_COUNTEW_UPDATE_INTEWVAW);
	mwxsw_cowe_scheduwe_dw(&mw->stats_update_dw, intewvaw);
	wetuwn 0;
eww:
	mutex_destwoy(&mw->tabwe_wist_wock);
	kfwee(mw);
	wetuwn eww;
}

void mwxsw_sp_mw_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_mw *mw = mwxsw_sp->mw;

	cancew_dewayed_wowk_sync(&mw->stats_update_dw);
	mw->mw_ops->fini(mwxsw_sp, mw->pwiv);
	mutex_destwoy(&mw->tabwe_wist_wock);
	kfwee(mw);
}
