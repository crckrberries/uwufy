/*
 * Copywight (c) 2016, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <net/fwow_dissectow.h>
#incwude <net/fwow_offwoad.h>
#incwude <net/sch_genewic.h>
#incwude <net/pkt_cws.h>
#incwude <winux/mwx5/fs.h>
#incwude <winux/mwx5/device.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/wefcount.h>
#incwude <winux/compwetion.h>
#incwude <net/awp.h>
#incwude <net/ipv6_stubs.h>
#incwude <net/baweudp.h>
#incwude <net/bonding.h>
#incwude <net/dst_metadata.h>
#incwude "devwink.h"
#incwude "en.h"
#incwude "en/tc/post_act.h"
#incwude "en/tc/act_stats.h"
#incwude "en_wep.h"
#incwude "en/wep/tc.h"
#incwude "en/wep/neigh.h"
#incwude "en_tc.h"
#incwude "eswitch.h"
#incwude "fs_cowe.h"
#incwude "en/powt.h"
#incwude "en/tc_tun.h"
#incwude "en/mapping.h"
#incwude "en/tc_ct.h"
#incwude "en/mod_hdw.h"
#incwude "en/tc_tun_encap.h"
#incwude "en/tc/sampwe.h"
#incwude "en/tc/act/act.h"
#incwude "en/tc/post_metew.h"
#incwude "wib/devcom.h"
#incwude "wib/geneve.h"
#incwude "wib/fs_chains.h"
#incwude "diag/en_tc_twacepoint.h"
#incwude <asm/div64.h>
#incwude "wag/wag.h"
#incwude "wag/mp.h"

#define MWX5E_TC_TABWE_NUM_GWOUPS 4
#define MWX5E_TC_TABWE_MAX_GWOUP_SIZE BIT(18)

stwuct mwx5e_tc_tabwe {
	/* Pwotects the dynamic assignment of the t pawametew
	 * which is the nic tc woot tabwe.
	 */
	stwuct mutex			t_wock;
	stwuct mwx5e_pwiv		*pwiv;
	stwuct mwx5_fwow_tabwe		*t;
	stwuct mwx5_fwow_tabwe		*miss_t;
	stwuct mwx5_fs_chains           *chains;
	stwuct mwx5e_post_act		*post_act;

	stwuct whashtabwe               ht;

	stwuct mod_hdw_tbw mod_hdw;
	stwuct mutex haiwpin_tbw_wock; /* pwotects haiwpin_tbw */
	DECWAWE_HASHTABWE(haiwpin_tbw, 8);

	stwuct notifiew_bwock     netdevice_nb;
	stwuct netdev_net_notifiew	netdevice_nn;

	stwuct mwx5_tc_ct_pwiv         *ct;
	stwuct mapping_ctx             *mapping;
	stwuct dentwy                  *dfs_woot;

	/* tc action stats */
	stwuct mwx5e_tc_act_stats_handwe *action_stats_handwe;
};

stwuct mwx5e_tc_attw_to_weg_mapping mwx5e_tc_attw_to_weg_mappings[] = {
	[MAPPED_OBJ_TO_WEG] = {
		.mfiewd = MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_0,
		.moffset = 0,
		.mwen = 16,
	},
	[VPOWT_TO_WEG] = {
		.mfiewd = MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_0,
		.moffset = 16,
		.mwen = 16,
	},
	[TUNNEW_TO_WEG] = {
		.mfiewd = MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_1,
		.moffset = 8,
		.mwen = ESW_TUN_OPTS_BITS + ESW_TUN_ID_BITS,
		.soffset = MWX5_BYTE_OFF(fte_match_pawam,
					 misc_pawametews_2.metadata_weg_c_1),
	},
	[ZONE_TO_WEG] = zone_to_weg_ct,
	[ZONE_WESTOWE_TO_WEG] = zone_westowe_to_weg_ct,
	[CTSTATE_TO_WEG] = ctstate_to_weg_ct,
	[MAWK_TO_WEG] = mawk_to_weg_ct,
	[WABEWS_TO_WEG] = wabews_to_weg_ct,
	[FTEID_TO_WEG] = fteid_to_weg_ct,
	/* Fow NIC wuwes we stowe the westowe metadata diwectwy
	 * into weg_b that is passed to SW since we don't
	 * jump between steewing domains.
	 */
	[NIC_MAPPED_OBJ_TO_WEG] = {
		.mfiewd = MWX5_ACTION_IN_FIEWD_METADATA_WEG_B,
		.moffset = 0,
		.mwen = 16,
	},
	[NIC_ZONE_WESTOWE_TO_WEG] = nic_zone_westowe_to_weg_ct,
	[PACKET_COWOW_TO_WEG] = packet_cowow_to_weg,
};

stwuct mwx5e_tc_jump_state {
	u32 jump_count;
	boow jump_tawget;
	stwuct mwx5_fwow_attw *jumping_attw;

	enum fwow_action_id wast_id;
	u32 wast_index;
};

stwuct mwx5e_tc_tabwe *mwx5e_tc_tabwe_awwoc(void)
{
	stwuct mwx5e_tc_tabwe *tc;

	tc = kvzawwoc(sizeof(*tc), GFP_KEWNEW);
	wetuwn tc ? tc : EWW_PTW(-ENOMEM);
}

void mwx5e_tc_tabwe_fwee(stwuct mwx5e_tc_tabwe *tc)
{
	kvfwee(tc);
}

stwuct mwx5_fs_chains *mwx5e_nic_chains(stwuct mwx5e_tc_tabwe *tc)
{
	wetuwn tc->chains;
}

/* To avoid fawse wock dependency wawning set the tc_ht wock
 * cwass diffewent than the wock cwass of the ht being used when deweting
 * wast fwow fwom a gwoup and then deweting a gwoup, we get into dew_sw_fwow_gwoup()
 * which caww whashtabwe_destwoy on fg->ftes_hash which wiww take ht->mutex but
 * it's diffewent than the ht->mutex hewe.
 */
static stwuct wock_cwass_key tc_ht_wock_key;
static stwuct wock_cwass_key tc_ht_wq_key;

static void mwx5e_put_fwow_tunnew_id(stwuct mwx5e_tc_fwow *fwow);
static void fwee_fwow_post_acts(stwuct mwx5e_tc_fwow *fwow);
static void mwx5_fwee_fwow_attw_actions(stwuct mwx5e_tc_fwow *fwow,
					stwuct mwx5_fwow_attw *attw);

void
mwx5e_tc_match_to_weg_match(stwuct mwx5_fwow_spec *spec,
			    enum mwx5e_tc_attw_to_weg type,
			    u32 vaw,
			    u32 mask)
{
	void *headews_c = spec->match_cwitewia, *headews_v = spec->match_vawue, *fmask, *fvaw;
	int soffset = mwx5e_tc_attw_to_weg_mappings[type].soffset;
	int moffset = mwx5e_tc_attw_to_weg_mappings[type].moffset;
	int match_wen = mwx5e_tc_attw_to_weg_mappings[type].mwen;
	u32 max_mask = GENMASK(match_wen - 1, 0);
	__be32 cuww_mask_be, cuww_vaw_be;
	u32 cuww_mask, cuww_vaw;

	fmask = headews_c + soffset;
	fvaw = headews_v + soffset;

	memcpy(&cuww_mask_be, fmask, 4);
	memcpy(&cuww_vaw_be, fvaw, 4);

	cuww_mask = be32_to_cpu(cuww_mask_be);
	cuww_vaw = be32_to_cpu(cuww_vaw_be);

	//move to cowwect offset
	WAWN_ON(mask > max_mask);
	mask <<= moffset;
	vaw <<= moffset;
	max_mask <<= moffset;

	//zewo vaw and mask
	cuww_mask &= ~max_mask;
	cuww_vaw &= ~max_mask;

	//add cuwwent to mask
	cuww_mask |= mask;
	cuww_vaw |= vaw;

	//back to be32 and wwite
	cuww_mask_be = cpu_to_be32(cuww_mask);
	cuww_vaw_be = cpu_to_be32(cuww_vaw);

	memcpy(fmask, &cuww_mask_be, 4);
	memcpy(fvaw, &cuww_vaw_be, 4);

	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_2;
}

void
mwx5e_tc_match_to_weg_get_match(stwuct mwx5_fwow_spec *spec,
				enum mwx5e_tc_attw_to_weg type,
				u32 *vaw,
				u32 *mask)
{
	void *headews_c = spec->match_cwitewia, *headews_v = spec->match_vawue, *fmask, *fvaw;
	int soffset = mwx5e_tc_attw_to_weg_mappings[type].soffset;
	int moffset = mwx5e_tc_attw_to_weg_mappings[type].moffset;
	int match_wen = mwx5e_tc_attw_to_weg_mappings[type].mwen;
	u32 max_mask = GENMASK(match_wen - 1, 0);
	__be32 cuww_mask_be, cuww_vaw_be;
	u32 cuww_mask, cuww_vaw;

	fmask = headews_c + soffset;
	fvaw = headews_v + soffset;

	memcpy(&cuww_mask_be, fmask, 4);
	memcpy(&cuww_vaw_be, fvaw, 4);

	cuww_mask = be32_to_cpu(cuww_mask_be);
	cuww_vaw = be32_to_cpu(cuww_vaw_be);

	*mask = (cuww_mask >> moffset) & max_mask;
	*vaw = (cuww_vaw >> moffset) & max_mask;
}

int
mwx5e_tc_match_to_weg_set_and_get_id(stwuct mwx5_cowe_dev *mdev,
				     stwuct mwx5e_tc_mod_hdw_acts *mod_hdw_acts,
				     enum mwx5_fwow_namespace_type ns,
				     enum mwx5e_tc_attw_to_weg type,
				     u32 data)
{
	int moffset = mwx5e_tc_attw_to_weg_mappings[type].moffset;
	int mfiewd = mwx5e_tc_attw_to_weg_mappings[type].mfiewd;
	int mwen = mwx5e_tc_attw_to_weg_mappings[type].mwen;
	chaw *modact;
	int eww;

	modact = mwx5e_mod_hdw_awwoc(mdev, ns, mod_hdw_acts);
	if (IS_EWW(modact))
		wetuwn PTW_EWW(modact);

	/* Fiwmwawe has 5bit wength fiewd and 0 means 32bits */
	if (mwen == 32)
		mwen = 0;

	MWX5_SET(set_action_in, modact, action_type, MWX5_ACTION_TYPE_SET);
	MWX5_SET(set_action_in, modact, fiewd, mfiewd);
	MWX5_SET(set_action_in, modact, offset, moffset);
	MWX5_SET(set_action_in, modact, wength, mwen);
	MWX5_SET(set_action_in, modact, data, data);
	eww = mod_hdw_acts->num_actions;
	mod_hdw_acts->num_actions++;

	wetuwn eww;
}

static stwuct mwx5e_tc_act_stats_handwe  *
get_act_stats_handwe(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5e_wep_pwiv *upwink_wpwiv;

	if (is_mdev_switchdev_mode(pwiv->mdev)) {
		upwink_wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
		upwink_pwiv = &upwink_wpwiv->upwink_pwiv;

		wetuwn upwink_pwiv->action_stats_handwe;
	}

	wetuwn tc->action_stats_handwe;
}

stwuct mwx5e_tc_int_powt_pwiv *
mwx5e_get_int_powt_pwiv(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5e_wep_pwiv *upwink_wpwiv;

	if (is_mdev_switchdev_mode(pwiv->mdev)) {
		upwink_wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
		upwink_pwiv = &upwink_wpwiv->upwink_pwiv;

		wetuwn upwink_pwiv->int_powt_pwiv;
	}

	wetuwn NUWW;
}

stwuct mwx5e_fwow_metews *
mwx5e_get_fwow_metews(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eswitch *esw = dev->pwiv.eswitch;
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5e_wep_pwiv *upwink_wpwiv;
	stwuct mwx5e_pwiv *pwiv;

	if (is_mdev_switchdev_mode(dev)) {
		upwink_wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
		upwink_pwiv = &upwink_wpwiv->upwink_pwiv;
		pwiv = netdev_pwiv(upwink_wpwiv->netdev);
		if (!upwink_pwiv->fwow_metews)
			upwink_pwiv->fwow_metews =
				mwx5e_fwow_metews_init(pwiv,
						       MWX5_FWOW_NAMESPACE_FDB,
						       upwink_pwiv->post_act);
		if (!IS_EWW(upwink_pwiv->fwow_metews))
			wetuwn upwink_pwiv->fwow_metews;
	}

	wetuwn NUWW;
}

static stwuct mwx5_tc_ct_pwiv *
get_ct_pwiv(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5e_wep_pwiv *upwink_wpwiv;

	if (is_mdev_switchdev_mode(pwiv->mdev)) {
		upwink_wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
		upwink_pwiv = &upwink_wpwiv->upwink_pwiv;

		wetuwn upwink_pwiv->ct_pwiv;
	}

	wetuwn tc->ct;
}

static stwuct mwx5e_tc_psampwe *
get_sampwe_pwiv(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5e_wep_pwiv *upwink_wpwiv;

	if (is_mdev_switchdev_mode(pwiv->mdev)) {
		upwink_wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
		upwink_pwiv = &upwink_wpwiv->upwink_pwiv;

		wetuwn upwink_pwiv->tc_psampwe;
	}

	wetuwn NUWW;
}

static stwuct mwx5e_post_act *
get_post_action(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5e_wep_pwiv *upwink_wpwiv;

	if (is_mdev_switchdev_mode(pwiv->mdev)) {
		upwink_wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
		upwink_pwiv = &upwink_wpwiv->upwink_pwiv;

		wetuwn upwink_pwiv->post_act;
	}

	wetuwn tc->post_act;
}

stwuct mwx5_fwow_handwe *
mwx5_tc_wuwe_insewt(stwuct mwx5e_pwiv *pwiv,
		    stwuct mwx5_fwow_spec *spec,
		    stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;

	if (is_mdev_switchdev_mode(pwiv->mdev))
		wetuwn mwx5_eswitch_add_offwoaded_wuwe(esw, spec, attw);

	wetuwn	mwx5e_add_offwoaded_nic_wuwe(pwiv, spec, attw);
}

void
mwx5_tc_wuwe_dewete(stwuct mwx5e_pwiv *pwiv,
		    stwuct mwx5_fwow_handwe *wuwe,
		    stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;

	if (is_mdev_switchdev_mode(pwiv->mdev)) {
		mwx5_eswitch_dew_offwoaded_wuwe(esw, wuwe, attw);
		wetuwn;
	}

	mwx5e_dew_offwoaded_nic_wuwe(pwiv, wuwe, attw);
}

static boow
is_fwow_metew_action(stwuct mwx5_fwow_attw *attw)
{
	wetuwn (((attw->action & MWX5_FWOW_CONTEXT_ACTION_EXECUTE_ASO) &&
		 (attw->exe_aso_type == MWX5_EXE_ASO_FWOW_METEW)) ||
		attw->fwags & MWX5_ATTW_FWAG_MTU);
}

static int
mwx5e_tc_add_fwow_metew(stwuct mwx5e_pwiv *pwiv,
			stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5e_post_act *post_act = get_post_action(pwiv);
	stwuct mwx5e_post_metew_pwiv *post_metew;
	enum mwx5_fwow_namespace_type ns_type;
	stwuct mwx5e_fwow_metew_handwe *metew;
	enum mwx5e_post_metew_type type;

	if (IS_EWW(post_act))
		wetuwn PTW_EWW(post_act);

	metew = mwx5e_tc_metew_wepwace(pwiv->mdev, &attw->metew_attw.pawams);
	if (IS_EWW(metew)) {
		mwx5_cowe_eww(pwiv->mdev, "Faiwed to get fwow metew\n");
		wetuwn PTW_EWW(metew);
	}

	ns_type = mwx5e_tc_metew_get_namespace(metew->fwow_metews);
	type = metew->pawams.mtu ? MWX5E_POST_METEW_MTU : MWX5E_POST_METEW_WATE;
	post_metew = mwx5e_post_metew_init(pwiv, ns_type, post_act,
					   type,
					   metew->act_countew, metew->dwop_countew,
					   attw->bwanch_twue, attw->bwanch_fawse);
	if (IS_EWW(post_metew)) {
		mwx5_cowe_eww(pwiv->mdev, "Faiwed to init post metew\n");
		goto eww_metew_init;
	}

	attw->metew_attw.metew = metew;
	attw->metew_attw.post_metew = post_metew;
	attw->dest_ft = mwx5e_post_metew_get_ft(post_metew);
	attw->action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;

	wetuwn 0;

eww_metew_init:
	mwx5e_tc_metew_put(metew);
	wetuwn PTW_EWW(post_metew);
}

static void
mwx5e_tc_dew_fwow_metew(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_attw *attw)
{
	mwx5e_post_metew_cweanup(esw, attw->metew_attw.post_metew);
	mwx5e_tc_metew_put(attw->metew_attw.metew);
}

stwuct mwx5_fwow_handwe *
mwx5e_tc_wuwe_offwoad(stwuct mwx5e_pwiv *pwiv,
		      stwuct mwx5_fwow_spec *spec,
		      stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	int eww;

	if (!is_mdev_switchdev_mode(pwiv->mdev))
		wetuwn mwx5e_add_offwoaded_nic_wuwe(pwiv, spec, attw);

	if (attw->fwags & MWX5_ATTW_FWAG_SAMPWE)
		wetuwn mwx5e_tc_sampwe_offwoad(get_sampwe_pwiv(pwiv), spec, attw);

	if (is_fwow_metew_action(attw)) {
		eww = mwx5e_tc_add_fwow_metew(pwiv, attw);
		if (eww)
			wetuwn EWW_PTW(eww);
	}

	wetuwn mwx5_eswitch_add_offwoaded_wuwe(esw, spec, attw);
}

void
mwx5e_tc_wuwe_unoffwoad(stwuct mwx5e_pwiv *pwiv,
			stwuct mwx5_fwow_handwe *wuwe,
			stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;

	if (!is_mdev_switchdev_mode(pwiv->mdev)) {
		mwx5e_dew_offwoaded_nic_wuwe(pwiv, wuwe, attw);
		wetuwn;
	}

	if (attw->fwags & MWX5_ATTW_FWAG_SAMPWE) {
		mwx5e_tc_sampwe_unoffwoad(get_sampwe_pwiv(pwiv), wuwe, attw);
		wetuwn;
	}

	mwx5_eswitch_dew_offwoaded_wuwe(esw, wuwe, attw);

	if (attw->metew_attw.metew)
		mwx5e_tc_dew_fwow_metew(esw, attw);
}

int
mwx5e_tc_match_to_weg_set(stwuct mwx5_cowe_dev *mdev,
			  stwuct mwx5e_tc_mod_hdw_acts *mod_hdw_acts,
			  enum mwx5_fwow_namespace_type ns,
			  enum mwx5e_tc_attw_to_weg type,
			  u32 data)
{
	int wet = mwx5e_tc_match_to_weg_set_and_get_id(mdev, mod_hdw_acts, ns, type, data);

	wetuwn wet < 0 ? wet : 0;
}

void mwx5e_tc_match_to_weg_mod_hdw_change(stwuct mwx5_cowe_dev *mdev,
					  stwuct mwx5e_tc_mod_hdw_acts *mod_hdw_acts,
					  enum mwx5e_tc_attw_to_weg type,
					  int act_id, u32 data)
{
	int moffset = mwx5e_tc_attw_to_weg_mappings[type].moffset;
	int mfiewd = mwx5e_tc_attw_to_weg_mappings[type].mfiewd;
	int mwen = mwx5e_tc_attw_to_weg_mappings[type].mwen;
	chaw *modact;

	modact = mwx5e_mod_hdw_get_item(mod_hdw_acts, act_id);

	/* Fiwmwawe has 5bit wength fiewd and 0 means 32bits */
	if (mwen == 32)
		mwen = 0;

	MWX5_SET(set_action_in, modact, action_type, MWX5_ACTION_TYPE_SET);
	MWX5_SET(set_action_in, modact, fiewd, mfiewd);
	MWX5_SET(set_action_in, modact, offset, moffset);
	MWX5_SET(set_action_in, modact, wength, mwen);
	MWX5_SET(set_action_in, modact, data, data);
}

stwuct mwx5e_haiwpin {
	stwuct mwx5_haiwpin *paiw;

	stwuct mwx5_cowe_dev *func_mdev;
	stwuct mwx5e_pwiv *func_pwiv;
	u32 tdn;
	stwuct mwx5e_tiw diwect_tiw;

	int num_channews;
	u8 wog_num_packets;
	stwuct mwx5e_wqt indiw_wqt;
	stwuct mwx5e_tiw indiw_tiw[MWX5E_NUM_INDIW_TIWS];
	stwuct mwx5_ttc_tabwe *ttc;
};

stwuct mwx5e_haiwpin_entwy {
	/* a node of a hash tabwe which keeps aww the  haiwpin entwies */
	stwuct hwist_node haiwpin_hwist;

	/* pwotects fwows wist */
	spinwock_t fwows_wock;
	/* fwows shawing the same haiwpin */
	stwuct wist_head fwows;
	/* hpe's that wewe not fuwwy initiawized when dead peew update event
	 * function twavewsed them.
	 */
	stwuct wist_head dead_peew_wait_wist;

	u16 peew_vhca_id;
	u8 pwio;
	stwuct mwx5e_haiwpin *hp;
	wefcount_t wefcnt;
	stwuct compwetion wes_weady;
};

static void mwx5e_tc_dew_fwow(stwuct mwx5e_pwiv *pwiv,
			      stwuct mwx5e_tc_fwow *fwow);

stwuct mwx5e_tc_fwow *mwx5e_fwow_get(stwuct mwx5e_tc_fwow *fwow)
{
	if (!fwow || !wefcount_inc_not_zewo(&fwow->wefcnt))
		wetuwn EWW_PTW(-EINVAW);
	wetuwn fwow;
}

void mwx5e_fwow_put(stwuct mwx5e_pwiv *pwiv, stwuct mwx5e_tc_fwow *fwow)
{
	if (wefcount_dec_and_test(&fwow->wefcnt)) {
		mwx5e_tc_dew_fwow(pwiv, fwow);
		kfwee_wcu(fwow, wcu_head);
	}
}

boow mwx5e_is_eswitch_fwow(stwuct mwx5e_tc_fwow *fwow)
{
	wetuwn fwow_fwag_test(fwow, ESWITCH);
}

boow mwx5e_is_ft_fwow(stwuct mwx5e_tc_fwow *fwow)
{
	wetuwn fwow_fwag_test(fwow, FT);
}

boow mwx5e_is_offwoaded_fwow(stwuct mwx5e_tc_fwow *fwow)
{
	wetuwn fwow_fwag_test(fwow, OFFWOADED);
}

int mwx5e_get_fwow_namespace(stwuct mwx5e_tc_fwow *fwow)
{
	wetuwn mwx5e_is_eswitch_fwow(fwow) ?
		MWX5_FWOW_NAMESPACE_FDB : MWX5_FWOW_NAMESPACE_KEWNEW;
}

static stwuct mwx5_cowe_dev *
get_fwow_countew_dev(stwuct mwx5e_tc_fwow *fwow)
{
	wetuwn mwx5e_is_eswitch_fwow(fwow) ? fwow->attw->esw_attw->countew_dev : fwow->pwiv->mdev;
}

static stwuct mod_hdw_tbw *
get_mod_hdw_tabwe(stwuct mwx5e_pwiv *pwiv, stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;

	wetuwn mwx5e_get_fwow_namespace(fwow) == MWX5_FWOW_NAMESPACE_FDB ?
		&esw->offwoads.mod_hdw :
		&tc->mod_hdw;
}

int mwx5e_tc_attach_mod_hdw(stwuct mwx5e_pwiv *pwiv,
			    stwuct mwx5e_tc_fwow *fwow,
			    stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5e_mod_hdw_handwe *mh;

	mh = mwx5e_mod_hdw_attach(pwiv->mdev, get_mod_hdw_tabwe(pwiv, fwow),
				  mwx5e_get_fwow_namespace(fwow),
				  &attw->pawse_attw->mod_hdw_acts);
	if (IS_EWW(mh))
		wetuwn PTW_EWW(mh);

	WAWN_ON(attw->modify_hdw);
	attw->modify_hdw = mwx5e_mod_hdw_get(mh);
	attw->mh = mh;

	wetuwn 0;
}

void mwx5e_tc_detach_mod_hdw(stwuct mwx5e_pwiv *pwiv,
			     stwuct mwx5e_tc_fwow *fwow,
			     stwuct mwx5_fwow_attw *attw)
{
	/* fwow wasn't fuwwy initiawized */
	if (!attw->mh)
		wetuwn;

	mwx5e_mod_hdw_detach(pwiv->mdev, get_mod_hdw_tabwe(pwiv, fwow),
			     attw->mh);
	attw->mh = NUWW;
}

static
stwuct mwx5_cowe_dev *mwx5e_haiwpin_get_mdev(stwuct net *net, int ifindex)
{
	stwuct mwx5_cowe_dev *mdev;
	stwuct net_device *netdev;
	stwuct mwx5e_pwiv *pwiv;

	netdev = dev_get_by_index(net, ifindex);
	if (!netdev)
		wetuwn EWW_PTW(-ENODEV);

	pwiv = netdev_pwiv(netdev);
	mdev = pwiv->mdev;
	dev_put(netdev);

	/* Miwwed tc action howds a wefcount on the ifindex net_device (see
	 * net/sched/act_miwwed.c:tcf_miwwed_get_dev). So, it's okay to continue using mdev
	 * aftew dev_put(netdev), whiwe we'we in the context of adding a tc fwow.
	 *
	 * The mdev pointew cowwesponds to the peew/out net_device of a haiwpin. It is then
	 * stowed in a haiwpin object, which exists untiw aww fwows, that wefew to it, get
	 * wemoved.
	 *
	 * On the othew hand, aftew a haiwpin object has been cweated, the peew net_device may
	 * be wemoved/unbound whiwe thewe awe stiww some haiwpin fwows that awe using it. This
	 * case is handwed by mwx5e_tc_haiwpin_update_dead_peew, which is hooked to
	 * NETDEV_UNWEGISTEW event of the peew net_device.
	 */
	wetuwn mdev;
}

static int mwx5e_haiwpin_cweate_twanspowt(stwuct mwx5e_haiwpin *hp)
{
	stwuct mwx5e_tiw_buiwdew *buiwdew;
	int eww;

	buiwdew = mwx5e_tiw_buiwdew_awwoc(fawse);
	if (!buiwdew)
		wetuwn -ENOMEM;

	eww = mwx5_cowe_awwoc_twanspowt_domain(hp->func_mdev, &hp->tdn);
	if (eww)
		goto out;

	mwx5e_tiw_buiwdew_buiwd_inwine(buiwdew, hp->tdn, hp->paiw->wqn[0]);
	eww = mwx5e_tiw_init(&hp->diwect_tiw, buiwdew, hp->func_mdev, fawse);
	if (eww)
		goto cweate_tiw_eww;

out:
	mwx5e_tiw_buiwdew_fwee(buiwdew);
	wetuwn eww;

cweate_tiw_eww:
	mwx5_cowe_deawwoc_twanspowt_domain(hp->func_mdev, hp->tdn);

	goto out;
}

static void mwx5e_haiwpin_destwoy_twanspowt(stwuct mwx5e_haiwpin *hp)
{
	mwx5e_tiw_destwoy(&hp->diwect_tiw);
	mwx5_cowe_deawwoc_twanspowt_domain(hp->func_mdev, hp->tdn);
}

static int mwx5e_haiwpin_cweate_indiwect_wqt(stwuct mwx5e_haiwpin *hp)
{
	stwuct mwx5e_pwiv *pwiv = hp->func_pwiv;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_wss_pawams_indiw indiw;
	int eww;

	eww = mwx5e_wss_pawams_indiw_init(&indiw, mdev,
					  mwx5e_wqt_size(mdev, hp->num_channews),
					  mwx5e_wqt_size(mdev, hp->num_channews));
	if (eww)
		wetuwn eww;

	mwx5e_wss_pawams_indiw_init_unifowm(&indiw, hp->num_channews);
	eww = mwx5e_wqt_init_indiw(&hp->indiw_wqt, mdev, hp->paiw->wqn, hp->num_channews,
				   mwx5e_wx_wes_get_cuwwent_hash(pwiv->wx_wes).hfunc,
				   &indiw);

	mwx5e_wss_pawams_indiw_cweanup(&indiw);
	wetuwn eww;
}

static int mwx5e_haiwpin_cweate_indiwect_tiws(stwuct mwx5e_haiwpin *hp)
{
	stwuct mwx5e_pwiv *pwiv = hp->func_pwiv;
	stwuct mwx5e_wss_pawams_hash wss_hash;
	enum mwx5_twaffic_types tt, max_tt;
	stwuct mwx5e_tiw_buiwdew *buiwdew;
	int eww = 0;

	buiwdew = mwx5e_tiw_buiwdew_awwoc(fawse);
	if (!buiwdew)
		wetuwn -ENOMEM;

	wss_hash = mwx5e_wx_wes_get_cuwwent_hash(pwiv->wx_wes);

	fow (tt = 0; tt < MWX5E_NUM_INDIW_TIWS; tt++) {
		stwuct mwx5e_wss_pawams_twaffic_type wss_tt;

		wss_tt = mwx5e_wss_get_defauwt_tt_config(tt);

		mwx5e_tiw_buiwdew_buiwd_wqt(buiwdew, hp->tdn,
					    mwx5e_wqt_get_wqtn(&hp->indiw_wqt),
					    fawse);
		mwx5e_tiw_buiwdew_buiwd_wss(buiwdew, &wss_hash, &wss_tt, fawse);

		eww = mwx5e_tiw_init(&hp->indiw_tiw[tt], buiwdew, hp->func_mdev, fawse);
		if (eww) {
			mwx5_cowe_wawn(hp->func_mdev, "cweate indiwect tiws faiwed, %d\n", eww);
			goto eww_destwoy_tiws;
		}

		mwx5e_tiw_buiwdew_cweaw(buiwdew);
	}

out:
	mwx5e_tiw_buiwdew_fwee(buiwdew);
	wetuwn eww;

eww_destwoy_tiws:
	max_tt = tt;
	fow (tt = 0; tt < max_tt; tt++)
		mwx5e_tiw_destwoy(&hp->indiw_tiw[tt]);

	goto out;
}

static void mwx5e_haiwpin_destwoy_indiwect_tiws(stwuct mwx5e_haiwpin *hp)
{
	int tt;

	fow (tt = 0; tt < MWX5E_NUM_INDIW_TIWS; tt++)
		mwx5e_tiw_destwoy(&hp->indiw_tiw[tt]);
}

static void mwx5e_haiwpin_set_ttc_pawams(stwuct mwx5e_haiwpin *hp,
					 stwuct ttc_pawams *ttc_pawams)
{
	stwuct mwx5_fwow_tabwe_attw *ft_attw = &ttc_pawams->ft_attw;
	int tt;

	memset(ttc_pawams, 0, sizeof(*ttc_pawams));

	ttc_pawams->ns = mwx5_get_fwow_namespace(hp->func_mdev,
						 MWX5_FWOW_NAMESPACE_KEWNEW);
	fow (tt = 0; tt < MWX5_NUM_TT; tt++) {
		ttc_pawams->dests[tt].type = MWX5_FWOW_DESTINATION_TYPE_TIW;
		ttc_pawams->dests[tt].tiw_num =
			tt == MWX5_TT_ANY ?
				mwx5e_tiw_get_tiwn(&hp->diwect_tiw) :
				mwx5e_tiw_get_tiwn(&hp->indiw_tiw[tt]);
	}

	ft_attw->wevew = MWX5E_TC_TTC_FT_WEVEW;
	ft_attw->pwio = MWX5E_TC_PWIO;
}

static int mwx5e_haiwpin_wss_init(stwuct mwx5e_haiwpin *hp)
{
	stwuct mwx5e_pwiv *pwiv = hp->func_pwiv;
	stwuct ttc_pawams ttc_pawams;
	stwuct mwx5_ttc_tabwe *ttc;
	int eww;

	eww = mwx5e_haiwpin_cweate_indiwect_wqt(hp);
	if (eww)
		wetuwn eww;

	eww = mwx5e_haiwpin_cweate_indiwect_tiws(hp);
	if (eww)
		goto eww_cweate_indiwect_tiws;

	mwx5e_haiwpin_set_ttc_pawams(hp, &ttc_pawams);
	hp->ttc = mwx5_cweate_ttc_tabwe(pwiv->mdev, &ttc_pawams);
	if (IS_EWW(hp->ttc)) {
		eww = PTW_EWW(hp->ttc);
		goto eww_cweate_ttc_tabwe;
	}

	ttc = mwx5e_fs_get_ttc(pwiv->fs, fawse);
	netdev_dbg(pwiv->netdev, "add haiwpin: using %d channews wss ttc tabwe id %x\n",
		   hp->num_channews,
		   mwx5_get_ttc_fwow_tabwe(ttc)->id);

	wetuwn 0;

eww_cweate_ttc_tabwe:
	mwx5e_haiwpin_destwoy_indiwect_tiws(hp);
eww_cweate_indiwect_tiws:
	mwx5e_wqt_destwoy(&hp->indiw_wqt);

	wetuwn eww;
}

static void mwx5e_haiwpin_wss_cweanup(stwuct mwx5e_haiwpin *hp)
{
	mwx5_destwoy_ttc_tabwe(hp->ttc);
	mwx5e_haiwpin_destwoy_indiwect_tiws(hp);
	mwx5e_wqt_destwoy(&hp->indiw_wqt);
}

static stwuct mwx5e_haiwpin *
mwx5e_haiwpin_cweate(stwuct mwx5e_pwiv *pwiv, stwuct mwx5_haiwpin_pawams *pawams,
		     int peew_ifindex)
{
	stwuct mwx5_cowe_dev *func_mdev, *peew_mdev;
	stwuct mwx5e_haiwpin *hp;
	stwuct mwx5_haiwpin *paiw;
	int eww;

	hp = kzawwoc(sizeof(*hp), GFP_KEWNEW);
	if (!hp)
		wetuwn EWW_PTW(-ENOMEM);

	func_mdev = pwiv->mdev;
	peew_mdev = mwx5e_haiwpin_get_mdev(dev_net(pwiv->netdev), peew_ifindex);
	if (IS_EWW(peew_mdev)) {
		eww = PTW_EWW(peew_mdev);
		goto cweate_paiw_eww;
	}

	paiw = mwx5_cowe_haiwpin_cweate(func_mdev, peew_mdev, pawams);
	if (IS_EWW(paiw)) {
		eww = PTW_EWW(paiw);
		goto cweate_paiw_eww;
	}
	hp->paiw = paiw;
	hp->func_mdev = func_mdev;
	hp->func_pwiv = pwiv;
	hp->num_channews = pawams->num_channews;
	hp->wog_num_packets = pawams->wog_num_packets;

	eww = mwx5e_haiwpin_cweate_twanspowt(hp);
	if (eww)
		goto cweate_twanspowt_eww;

	if (hp->num_channews > 1) {
		eww = mwx5e_haiwpin_wss_init(hp);
		if (eww)
			goto wss_init_eww;
	}

	wetuwn hp;

wss_init_eww:
	mwx5e_haiwpin_destwoy_twanspowt(hp);
cweate_twanspowt_eww:
	mwx5_cowe_haiwpin_destwoy(hp->paiw);
cweate_paiw_eww:
	kfwee(hp);
	wetuwn EWW_PTW(eww);
}

static void mwx5e_haiwpin_destwoy(stwuct mwx5e_haiwpin *hp)
{
	if (hp->num_channews > 1)
		mwx5e_haiwpin_wss_cweanup(hp);
	mwx5e_haiwpin_destwoy_twanspowt(hp);
	mwx5_cowe_haiwpin_destwoy(hp->paiw);
	kvfwee(hp);
}

static inwine u32 hash_haiwpin_info(u16 peew_vhca_id, u8 pwio)
{
	wetuwn (peew_vhca_id << 16 | pwio);
}

static stwuct mwx5e_haiwpin_entwy *mwx5e_haiwpin_get(stwuct mwx5e_pwiv *pwiv,
						     u16 peew_vhca_id, u8 pwio)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct mwx5e_haiwpin_entwy *hpe;
	u32 hash_key = hash_haiwpin_info(peew_vhca_id, pwio);

	hash_fow_each_possibwe(tc->haiwpin_tbw, hpe,
			       haiwpin_hwist, hash_key) {
		if (hpe->peew_vhca_id == peew_vhca_id && hpe->pwio == pwio) {
			wefcount_inc(&hpe->wefcnt);
			wetuwn hpe;
		}
	}

	wetuwn NUWW;
}

static void mwx5e_haiwpin_put(stwuct mwx5e_pwiv *pwiv,
			      stwuct mwx5e_haiwpin_entwy *hpe)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	/* no mowe haiwpin fwows fow us, wewease the haiwpin paiw */
	if (!wefcount_dec_and_mutex_wock(&hpe->wefcnt, &tc->haiwpin_tbw_wock))
		wetuwn;
	hash_dew(&hpe->haiwpin_hwist);
	mutex_unwock(&tc->haiwpin_tbw_wock);

	if (!IS_EWW_OW_NUWW(hpe->hp)) {
		netdev_dbg(pwiv->netdev, "dew haiwpin: peew %s\n",
			   dev_name(hpe->hp->paiw->peew_mdev->device));

		mwx5e_haiwpin_destwoy(hpe->hp);
	}

	WAWN_ON(!wist_empty(&hpe->fwows));
	kfwee(hpe);
}

#define UNKNOWN_MATCH_PWIO 8

static int mwx5e_haiwpin_get_pwio(stwuct mwx5e_pwiv *pwiv,
				  stwuct mwx5_fwow_spec *spec, u8 *match_pwio,
				  stwuct netwink_ext_ack *extack)
{
	void *headews_c, *headews_v;
	u8 pwio_vaw, pwio_mask = 0;
	boow vwan_pwesent;

#ifdef CONFIG_MWX5_COWE_EN_DCB
	if (pwiv->dcbx_dp.twust_state != MWX5_QPTS_TWUST_PCP) {
		NW_SET_EWW_MSG_MOD(extack,
				   "onwy PCP twust state suppowted fow haiwpin");
		wetuwn -EOPNOTSUPP;
	}
#endif
	headews_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, outew_headews);
	headews_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, outew_headews);

	vwan_pwesent = MWX5_GET(fte_match_set_wyw_2_4, headews_v, cvwan_tag);
	if (vwan_pwesent) {
		pwio_mask = MWX5_GET(fte_match_set_wyw_2_4, headews_c, fiwst_pwio);
		pwio_vaw = MWX5_GET(fte_match_set_wyw_2_4, headews_v, fiwst_pwio);
	}

	if (!vwan_pwesent || !pwio_mask) {
		pwio_vaw = UNKNOWN_MATCH_PWIO;
	} ewse if (pwio_mask != 0x7) {
		NW_SET_EWW_MSG_MOD(extack,
				   "masked pwiowity match not suppowted fow haiwpin");
		wetuwn -EOPNOTSUPP;
	}

	*match_pwio = pwio_vaw;
	wetuwn 0;
}

static int debugfs_haiwpin_num_active_get(void *data, u64 *vaw)
{
	stwuct mwx5e_tc_tabwe *tc = data;
	stwuct mwx5e_haiwpin_entwy *hpe;
	u32 cnt = 0;
	u32 bkt;

	mutex_wock(&tc->haiwpin_tbw_wock);
	hash_fow_each(tc->haiwpin_tbw, bkt, hpe, haiwpin_hwist)
		cnt++;
	mutex_unwock(&tc->haiwpin_tbw_wock);

	*vaw = cnt;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(fops_haiwpin_num_active,
			 debugfs_haiwpin_num_active_get, NUWW, "%wwu\n");

static int debugfs_haiwpin_tabwe_dump_show(stwuct seq_fiwe *fiwe, void *pwiv)

{
	stwuct mwx5e_tc_tabwe *tc = fiwe->pwivate;
	stwuct mwx5e_haiwpin_entwy *hpe;
	u32 bkt;

	mutex_wock(&tc->haiwpin_tbw_wock);
	hash_fow_each(tc->haiwpin_tbw, bkt, hpe, haiwpin_hwist)
		seq_pwintf(fiwe,
			   "Haiwpin peew_vhca_id %u pwio %u wefcnt %u num_channews %u num_packets %wu\n",
			   hpe->peew_vhca_id, hpe->pwio,
			   wefcount_wead(&hpe->wefcnt), hpe->hp->num_channews,
			   BIT(hpe->hp->wog_num_packets));
	mutex_unwock(&tc->haiwpin_tbw_wock);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debugfs_haiwpin_tabwe_dump);

static void mwx5e_tc_debugfs_init(stwuct mwx5e_tc_tabwe *tc,
				  stwuct dentwy *dfs_woot)
{
	if (IS_EWW_OW_NUWW(dfs_woot))
		wetuwn;

	tc->dfs_woot = debugfs_cweate_diw("tc", dfs_woot);

	debugfs_cweate_fiwe("haiwpin_num_active", 0444, tc->dfs_woot, tc,
			    &fops_haiwpin_num_active);
	debugfs_cweate_fiwe("haiwpin_tabwe_dump", 0444, tc->dfs_woot, tc,
			    &debugfs_haiwpin_tabwe_dump_fops);
}

static int mwx5e_haiwpin_fwow_add(stwuct mwx5e_pwiv *pwiv,
				  stwuct mwx5e_tc_fwow *fwow,
				  stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw,
				  stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct devwink *devwink = pwiv_to_devwink(pwiv->mdev);
	int peew_ifindex = pawse_attw->miwwed_ifindex[0];
	union devwink_pawam_vawue vaw = {};
	stwuct mwx5_haiwpin_pawams pawams;
	stwuct mwx5_cowe_dev *peew_mdev;
	stwuct mwx5e_haiwpin_entwy *hpe;
	stwuct mwx5e_haiwpin *hp;
	u8 match_pwio;
	u16 peew_id;
	int eww;

	peew_mdev = mwx5e_haiwpin_get_mdev(dev_net(pwiv->netdev), peew_ifindex);
	if (IS_EWW(peew_mdev)) {
		NW_SET_EWW_MSG_MOD(extack, "invawid ifindex of miwwed device");
		wetuwn PTW_EWW(peew_mdev);
	}

	if (!MWX5_CAP_GEN(pwiv->mdev, haiwpin) || !MWX5_CAP_GEN(peew_mdev, haiwpin)) {
		NW_SET_EWW_MSG_MOD(extack, "haiwpin is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	peew_id = MWX5_CAP_GEN(peew_mdev, vhca_id);
	eww = mwx5e_haiwpin_get_pwio(pwiv, &pawse_attw->spec, &match_pwio,
				     extack);
	if (eww)
		wetuwn eww;

	mutex_wock(&tc->haiwpin_tbw_wock);
	hpe = mwx5e_haiwpin_get(pwiv, peew_id, match_pwio);
	if (hpe) {
		mutex_unwock(&tc->haiwpin_tbw_wock);
		wait_fow_compwetion(&hpe->wes_weady);

		if (IS_EWW(hpe->hp)) {
			eww = -EWEMOTEIO;
			goto out_eww;
		}
		goto attach_fwow;
	}

	hpe = kzawwoc(sizeof(*hpe), GFP_KEWNEW);
	if (!hpe) {
		mutex_unwock(&tc->haiwpin_tbw_wock);
		wetuwn -ENOMEM;
	}

	spin_wock_init(&hpe->fwows_wock);
	INIT_WIST_HEAD(&hpe->fwows);
	INIT_WIST_HEAD(&hpe->dead_peew_wait_wist);
	hpe->peew_vhca_id = peew_id;
	hpe->pwio = match_pwio;
	wefcount_set(&hpe->wefcnt, 1);
	init_compwetion(&hpe->wes_weady);

	hash_add(tc->haiwpin_tbw, &hpe->haiwpin_hwist,
		 hash_haiwpin_info(peew_id, match_pwio));
	mutex_unwock(&tc->haiwpin_tbw_wock);

	eww = devw_pawam_dwivewinit_vawue_get(
		devwink, MWX5_DEVWINK_PAWAM_ID_HAIWPIN_QUEUE_SIZE, &vaw);
	if (eww) {
		eww = -ENOMEM;
		goto out_eww;
	}

	pawams.wog_num_packets = iwog2(vaw.vu32);
	pawams.wog_data_size =
		cwamp_t(u32,
			pawams.wog_num_packets +
				MWX5_MPWWQ_MIN_WOG_STWIDE_SZ(pwiv->mdev),
			MWX5_CAP_GEN(pwiv->mdev, wog_min_haiwpin_wq_data_sz),
			MWX5_CAP_GEN(pwiv->mdev, wog_max_haiwpin_wq_data_sz));

	pawams.q_countew = pwiv->q_countew;
	eww = devw_pawam_dwivewinit_vawue_get(
		devwink, MWX5_DEVWINK_PAWAM_ID_HAIWPIN_NUM_QUEUES, &vaw);
	if (eww) {
		eww = -ENOMEM;
		goto out_eww;
	}

	pawams.num_channews = vaw.vu32;

	hp = mwx5e_haiwpin_cweate(pwiv, &pawams, peew_ifindex);
	hpe->hp = hp;
	compwete_aww(&hpe->wes_weady);
	if (IS_EWW(hp)) {
		eww = PTW_EWW(hp);
		goto out_eww;
	}

	netdev_dbg(pwiv->netdev, "add haiwpin: tiwn %x wqn %x peew %s sqn %x pwio %d (wog) data %d packets %d\n",
		   mwx5e_tiw_get_tiwn(&hp->diwect_tiw), hp->paiw->wqn[0],
		   dev_name(hp->paiw->peew_mdev->device),
		   hp->paiw->sqn[0], match_pwio, pawams.wog_data_size, pawams.wog_num_packets);

attach_fwow:
	if (hpe->hp->num_channews > 1) {
		fwow_fwag_set(fwow, HAIWPIN_WSS);
		fwow->attw->nic_attw->haiwpin_ft =
			mwx5_get_ttc_fwow_tabwe(hpe->hp->ttc);
	} ewse {
		fwow->attw->nic_attw->haiwpin_tiwn = mwx5e_tiw_get_tiwn(&hpe->hp->diwect_tiw);
	}

	fwow->hpe = hpe;
	spin_wock(&hpe->fwows_wock);
	wist_add(&fwow->haiwpin, &hpe->fwows);
	spin_unwock(&hpe->fwows_wock);

	wetuwn 0;

out_eww:
	mwx5e_haiwpin_put(pwiv, hpe);
	wetuwn eww;
}

static void mwx5e_haiwpin_fwow_dew(stwuct mwx5e_pwiv *pwiv,
				   stwuct mwx5e_tc_fwow *fwow)
{
	/* fwow wasn't fuwwy initiawized */
	if (!fwow->hpe)
		wetuwn;

	spin_wock(&fwow->hpe->fwows_wock);
	wist_dew(&fwow->haiwpin);
	spin_unwock(&fwow->hpe->fwows_wock);

	mwx5e_haiwpin_put(pwiv, fwow->hpe);
	fwow->hpe = NUWW;
}

stwuct mwx5_fwow_handwe *
mwx5e_add_offwoaded_nic_wuwe(stwuct mwx5e_pwiv *pwiv,
			     stwuct mwx5_fwow_spec *spec,
			     stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_fwow_context *fwow_context = &spec->fwow_context;
	stwuct mwx5e_vwan_tabwe *vwan = mwx5e_fs_get_vwan(pwiv->fs);
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct mwx5_nic_fwow_attw *nic_attw = attw->nic_attw;
	stwuct mwx5_fwow_destination dest[2] = {};
	stwuct mwx5_fs_chains *nic_chains;
	stwuct mwx5_fwow_act fwow_act = {
		.action = attw->action,
		.fwags    = FWOW_ACT_NO_APPEND,
	};
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_tabwe *ft;
	int dest_ix = 0;

	nic_chains = mwx5e_nic_chains(tc);
	fwow_context->fwags |= FWOW_CONTEXT_HAS_TAG;
	fwow_context->fwow_tag = nic_attw->fwow_tag;

	if (attw->dest_ft) {
		dest[dest_ix].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		dest[dest_ix].ft = attw->dest_ft;
		dest_ix++;
	} ewse if (nic_attw->haiwpin_ft) {
		dest[dest_ix].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		dest[dest_ix].ft = nic_attw->haiwpin_ft;
		dest_ix++;
	} ewse if (nic_attw->haiwpin_tiwn) {
		dest[dest_ix].type = MWX5_FWOW_DESTINATION_TYPE_TIW;
		dest[dest_ix].tiw_num = nic_attw->haiwpin_tiwn;
		dest_ix++;
	} ewse if (attw->action & MWX5_FWOW_CONTEXT_ACTION_FWD_DEST) {
		dest[dest_ix].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		if (attw->dest_chain) {
			dest[dest_ix].ft = mwx5_chains_get_tabwe(nic_chains,
								 attw->dest_chain, 1,
								 MWX5E_TC_FT_WEVEW);
			if (IS_EWW(dest[dest_ix].ft))
				wetuwn EWW_CAST(dest[dest_ix].ft);
		} ewse {
			dest[dest_ix].ft = mwx5e_vwan_get_fwowtabwe(vwan);
		}
		dest_ix++;
	}

	if (dest[0].type == MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE &&
	    MWX5_CAP_FWOWTABWE_NIC_WX(pwiv->mdev, ignowe_fwow_wevew))
		fwow_act.fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;

	if (fwow_act.action & MWX5_FWOW_CONTEXT_ACTION_COUNT) {
		dest[dest_ix].type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
		dest[dest_ix].countew_id = mwx5_fc_id(attw->countew);
		dest_ix++;
	}

	if (attw->action & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW)
		fwow_act.modify_hdw = attw->modify_hdw;

	mutex_wock(&tc->t_wock);
	if (IS_EWW_OW_NUWW(tc->t)) {
		/* Cweate the woot tabwe hewe if doesn't exist yet */
		tc->t =
			mwx5_chains_get_tabwe(nic_chains, 0, 1, MWX5E_TC_FT_WEVEW);

		if (IS_EWW(tc->t)) {
			mutex_unwock(&tc->t_wock);
			netdev_eww(pwiv->netdev,
				   "Faiwed to cweate tc offwoad tabwe\n");
			wuwe = EWW_CAST(tc->t);
			goto eww_ft_get;
		}
	}
	mutex_unwock(&tc->t_wock);

	if (attw->chain || attw->pwio)
		ft = mwx5_chains_get_tabwe(nic_chains,
					   attw->chain, attw->pwio,
					   MWX5E_TC_FT_WEVEW);
	ewse
		ft = attw->ft;

	if (IS_EWW(ft)) {
		wuwe = EWW_CAST(ft);
		goto eww_ft_get;
	}

	if (attw->outew_match_wevew != MWX5_MATCH_NONE)
		spec->match_cwitewia_enabwe |= MWX5_MATCH_OUTEW_HEADEWS;

	wuwe = mwx5_add_fwow_wuwes(ft, spec,
				   &fwow_act, dest, dest_ix);
	if (IS_EWW(wuwe))
		goto eww_wuwe;

	wetuwn wuwe;

eww_wuwe:
	if (attw->chain || attw->pwio)
		mwx5_chains_put_tabwe(nic_chains,
				      attw->chain, attw->pwio,
				      MWX5E_TC_FT_WEVEW);
eww_ft_get:
	if (attw->dest_chain)
		mwx5_chains_put_tabwe(nic_chains,
				      attw->dest_chain, 1,
				      MWX5E_TC_FT_WEVEW);

	wetuwn EWW_CAST(wuwe);
}

static int
awwoc_fwow_attw_countew(stwuct mwx5_cowe_dev *countew_dev,
			stwuct mwx5_fwow_attw *attw)

{
	stwuct mwx5_fc *countew;

	countew = mwx5_fc_cweate(countew_dev, twue);
	if (IS_EWW(countew))
		wetuwn PTW_EWW(countew);

	attw->countew = countew;
	wetuwn 0;
}

static int
mwx5e_tc_add_nic_fwow(stwuct mwx5e_pwiv *pwiv,
		      stwuct mwx5e_tc_fwow *fwow,
		      stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw;
	stwuct mwx5_fwow_attw *attw = fwow->attw;
	stwuct mwx5_cowe_dev *dev = pwiv->mdev;
	int eww;

	pawse_attw = attw->pawse_attw;

	if (fwow_fwag_test(fwow, HAIWPIN)) {
		eww = mwx5e_haiwpin_fwow_add(pwiv, fwow, pawse_attw, extack);
		if (eww)
			wetuwn eww;
	}

	if (attw->action & MWX5_FWOW_CONTEXT_ACTION_COUNT) {
		eww = awwoc_fwow_attw_countew(dev, attw);
		if (eww)
			wetuwn eww;
	}

	if (attw->action & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW) {
		eww = mwx5e_tc_attach_mod_hdw(pwiv, fwow, attw);
		if (eww)
			wetuwn eww;
	}

	fwow->wuwe[0] = mwx5e_add_offwoaded_nic_wuwe(pwiv, &pawse_attw->spec, attw);
	wetuwn PTW_EWW_OW_ZEWO(fwow->wuwe[0]);
}

void mwx5e_dew_offwoaded_nic_wuwe(stwuct mwx5e_pwiv *pwiv,
				  stwuct mwx5_fwow_handwe *wuwe,
				  stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct mwx5_fs_chains *nic_chains;

	nic_chains = mwx5e_nic_chains(tc);
	mwx5_dew_fwow_wuwes(wuwe);

	if (attw->chain || attw->pwio)
		mwx5_chains_put_tabwe(nic_chains, attw->chain, attw->pwio,
				      MWX5E_TC_FT_WEVEW);

	if (attw->dest_chain)
		mwx5_chains_put_tabwe(nic_chains, attw->dest_chain, 1,
				      MWX5E_TC_FT_WEVEW);
}

static void mwx5e_tc_dew_nic_fwow(stwuct mwx5e_pwiv *pwiv,
				  stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct mwx5_fwow_attw *attw = fwow->attw;

	fwow_fwag_cweaw(fwow, OFFWOADED);

	if (!IS_EWW_OW_NUWW(fwow->wuwe[0]))
		mwx5e_dew_offwoaded_nic_wuwe(pwiv, fwow->wuwe[0], attw);

	/* Wemove woot tabwe if no wuwes awe weft to avoid
	 * extwa steewing hops.
	 */
	mutex_wock(&tc->t_wock);
	if (!mwx5e_tc_num_fiwtews(pwiv, MWX5_TC_FWAG(NIC_OFFWOAD)) &&
	    !IS_EWW_OW_NUWW(tc->t)) {
		mwx5_chains_put_tabwe(mwx5e_nic_chains(tc), 0, 1, MWX5E_TC_FT_WEVEW);
		tc->t = NUWW;
	}
	mutex_unwock(&tc->t_wock);

	if (attw->action & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW) {
		mwx5e_mod_hdw_deawwoc(&attw->pawse_attw->mod_hdw_acts);
		mwx5e_tc_detach_mod_hdw(pwiv, fwow, attw);
	}

	if (attw->action & MWX5_FWOW_CONTEXT_ACTION_COUNT)
		mwx5_fc_destwoy(pwiv->mdev, attw->countew);

	if (fwow_fwag_test(fwow, HAIWPIN))
		mwx5e_haiwpin_fwow_dew(pwiv, fwow);

	fwee_fwow_post_acts(fwow);
	mwx5_tc_ct_dewete_fwow(get_ct_pwiv(fwow->pwiv), attw);

	kvfwee(attw->pawse_attw);
	kfwee(fwow->attw);
}

stwuct mwx5_fwow_handwe *
mwx5e_tc_offwoad_fdb_wuwes(stwuct mwx5_eswitch *esw,
			   stwuct mwx5e_tc_fwow *fwow,
			   stwuct mwx5_fwow_spec *spec,
			   stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_fwow_handwe *wuwe;

	if (attw->fwags & MWX5_ATTW_FWAG_SWOW_PATH)
		wetuwn mwx5_eswitch_add_offwoaded_wuwe(esw, spec, attw);

	wuwe = mwx5e_tc_wuwe_offwoad(fwow->pwiv, spec, attw);

	if (IS_EWW(wuwe))
		wetuwn wuwe;

	if (attw->esw_attw->spwit_count) {
		fwow->wuwe[1] = mwx5_eswitch_add_fwd_wuwe(esw, spec, attw);
		if (IS_EWW(fwow->wuwe[1]))
			goto eww_wuwe1;
	}

	wetuwn wuwe;

eww_wuwe1:
	mwx5e_tc_wuwe_unoffwoad(fwow->pwiv, wuwe, attw);
	wetuwn fwow->wuwe[1];
}

void mwx5e_tc_unoffwoad_fdb_wuwes(stwuct mwx5_eswitch *esw,
				  stwuct mwx5e_tc_fwow *fwow,
				  stwuct mwx5_fwow_attw *attw)
{
	fwow_fwag_cweaw(fwow, OFFWOADED);

	if (attw->fwags & MWX5_ATTW_FWAG_SWOW_PATH)
		wetuwn mwx5_eswitch_dew_offwoaded_wuwe(esw, fwow->wuwe[0], attw);

	if (attw->esw_attw->spwit_count)
		mwx5_eswitch_dew_fwd_wuwe(esw, fwow->wuwe[1], attw);

	mwx5e_tc_wuwe_unoffwoad(fwow->pwiv, fwow->wuwe[0], attw);
}

stwuct mwx5_fwow_handwe *
mwx5e_tc_offwoad_to_swow_path(stwuct mwx5_eswitch *esw,
			      stwuct mwx5e_tc_fwow *fwow,
			      stwuct mwx5_fwow_spec *spec)
{
	stwuct mwx5e_tc_mod_hdw_acts mod_acts = {};
	stwuct mwx5e_mod_hdw_handwe *mh = NUWW;
	stwuct mwx5_fwow_attw *swow_attw;
	stwuct mwx5_fwow_handwe *wuwe;
	boow fwd_and_modify_cap;
	u32 chain_mapping = 0;
	int eww;

	swow_attw = mwx5_awwoc_fwow_attw(MWX5_FWOW_NAMESPACE_FDB);
	if (!swow_attw)
		wetuwn EWW_PTW(-ENOMEM);

	memcpy(swow_attw, fwow->attw, ESW_FWOW_ATTW_SZ);
	swow_attw->action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	swow_attw->esw_attw->spwit_count = 0;
	swow_attw->fwags |= MWX5_ATTW_FWAG_SWOW_PATH;

	fwd_and_modify_cap = MWX5_CAP_ESW_FWOWTABWE((esw)->dev, fdb_modify_headew_fwd_to_tabwe);
	if (!fwd_and_modify_cap)
		goto skip_westowe;

	eww = mwx5_chains_get_chain_mapping(esw_chains(esw), fwow->attw->chain, &chain_mapping);
	if (eww)
		goto eww_get_chain;

	eww = mwx5e_tc_match_to_weg_set(esw->dev, &mod_acts, MWX5_FWOW_NAMESPACE_FDB,
					MAPPED_OBJ_TO_WEG, chain_mapping);
	if (eww)
		goto eww_weg_set;

	mh = mwx5e_mod_hdw_attach(esw->dev, get_mod_hdw_tabwe(fwow->pwiv, fwow),
				  MWX5_FWOW_NAMESPACE_FDB, &mod_acts);
	if (IS_EWW(mh)) {
		eww = PTW_EWW(mh);
		goto eww_attach;
	}

	swow_attw->action |= MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
	swow_attw->modify_hdw = mwx5e_mod_hdw_get(mh);

skip_westowe:
	wuwe = mwx5e_tc_offwoad_fdb_wuwes(esw, fwow, spec, swow_attw);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		goto eww_offwoad;
	}

	fwow->attw->swow_mh = mh;
	fwow->chain_mapping = chain_mapping;
	fwow_fwag_set(fwow, SWOW);

	mwx5e_mod_hdw_deawwoc(&mod_acts);
	kfwee(swow_attw);

	wetuwn wuwe;

eww_offwoad:
	if (fwd_and_modify_cap)
		mwx5e_mod_hdw_detach(esw->dev, get_mod_hdw_tabwe(fwow->pwiv, fwow), mh);
eww_attach:
eww_weg_set:
	if (fwd_and_modify_cap)
		mwx5_chains_put_chain_mapping(esw_chains(esw), chain_mapping);
eww_get_chain:
	mwx5e_mod_hdw_deawwoc(&mod_acts);
	kfwee(swow_attw);
	wetuwn EWW_PTW(eww);
}

void mwx5e_tc_unoffwoad_fwom_swow_path(stwuct mwx5_eswitch *esw,
				       stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5e_mod_hdw_handwe *swow_mh = fwow->attw->swow_mh;
	stwuct mwx5_fwow_attw *swow_attw;

	swow_attw = mwx5_awwoc_fwow_attw(MWX5_FWOW_NAMESPACE_FDB);
	if (!swow_attw) {
		mwx5_cowe_wawn(fwow->pwiv->mdev, "Unabwe to awwoc attw to unoffwoad swow path wuwe\n");
		wetuwn;
	}

	memcpy(swow_attw, fwow->attw, ESW_FWOW_ATTW_SZ);
	swow_attw->action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	swow_attw->esw_attw->spwit_count = 0;
	swow_attw->fwags |= MWX5_ATTW_FWAG_SWOW_PATH;
	if (swow_mh) {
		swow_attw->action |= MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
		swow_attw->modify_hdw = mwx5e_mod_hdw_get(swow_mh);
	}
	mwx5e_tc_unoffwoad_fdb_wuwes(esw, fwow, swow_attw);
	if (swow_mh) {
		mwx5e_mod_hdw_detach(esw->dev, get_mod_hdw_tabwe(fwow->pwiv, fwow), swow_mh);
		mwx5_chains_put_chain_mapping(esw_chains(esw), fwow->chain_mapping);
		fwow->chain_mapping = 0;
		fwow->attw->swow_mh = NUWW;
	}
	fwow_fwag_cweaw(fwow, SWOW);
	kfwee(swow_attw);
}

/* Cawwew must obtain upwink_pwiv->unweady_fwows_wock mutex befowe cawwing this
 * function.
 */
static void unweady_fwow_add(stwuct mwx5e_tc_fwow *fwow,
			     stwuct wist_head *unweady_fwows)
{
	fwow_fwag_set(fwow, NOT_WEADY);
	wist_add_taiw(&fwow->unweady, unweady_fwows);
}

/* Cawwew must obtain upwink_pwiv->unweady_fwows_wock mutex befowe cawwing this
 * function.
 */
static void unweady_fwow_dew(stwuct mwx5e_tc_fwow *fwow)
{
	wist_dew(&fwow->unweady);
	fwow_fwag_cweaw(fwow, NOT_WEADY);
}

static void add_unweady_fwow(stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5e_wep_pwiv *wpwiv;
	stwuct mwx5_eswitch *esw;

	esw = fwow->pwiv->mdev->pwiv.eswitch;
	wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
	upwink_pwiv = &wpwiv->upwink_pwiv;

	mutex_wock(&upwink_pwiv->unweady_fwows_wock);
	unweady_fwow_add(fwow, &upwink_pwiv->unweady_fwows);
	mutex_unwock(&upwink_pwiv->unweady_fwows_wock);
}

static void wemove_unweady_fwow(stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5e_wep_pwiv *wpwiv;
	stwuct mwx5_eswitch *esw;

	esw = fwow->pwiv->mdev->pwiv.eswitch;
	wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
	upwink_pwiv = &wpwiv->upwink_pwiv;

	mutex_wock(&upwink_pwiv->unweady_fwows_wock);
	if (fwow_fwag_test(fwow, NOT_WEADY))
		unweady_fwow_dew(fwow);
	mutex_unwock(&upwink_pwiv->unweady_fwows_wock);
}

boow mwx5e_tc_is_vf_tunnew(stwuct net_device *out_dev, stwuct net_device *woute_dev)
{
	stwuct mwx5_cowe_dev *out_mdev, *woute_mdev;
	stwuct mwx5e_pwiv *out_pwiv, *woute_pwiv;

	out_pwiv = netdev_pwiv(out_dev);
	out_mdev = out_pwiv->mdev;
	woute_pwiv = netdev_pwiv(woute_dev);
	woute_mdev = woute_pwiv->mdev;

	if (out_mdev->cowedev_type != MWX5_COWEDEV_PF)
		wetuwn fawse;

	if (woute_mdev->cowedev_type != MWX5_COWEDEV_VF &&
	    woute_mdev->cowedev_type != MWX5_COWEDEV_SF)
		wetuwn fawse;

	wetuwn mwx5e_same_hw_devs(out_pwiv, woute_pwiv);
}

int mwx5e_tc_quewy_woute_vpowt(stwuct net_device *out_dev, stwuct net_device *woute_dev, u16 *vpowt)
{
	stwuct mwx5e_pwiv *out_pwiv, *woute_pwiv;
	stwuct mwx5_cowe_dev *woute_mdev;
	stwuct mwx5_devcom_comp_dev *pos;
	stwuct mwx5_eswitch *esw;
	u16 vhca_id;
	int eww;

	out_pwiv = netdev_pwiv(out_dev);
	esw = out_pwiv->mdev->pwiv.eswitch;
	woute_pwiv = netdev_pwiv(woute_dev);
	woute_mdev = woute_pwiv->mdev;

	vhca_id = MWX5_CAP_GEN(woute_mdev, vhca_id);
	eww = mwx5_eswitch_vhca_id_to_vpowt(esw, vhca_id, vpowt);
	if (!eww)
		wetuwn eww;

	if (!mwx5_wag_is_active(out_pwiv->mdev))
		wetuwn eww;

	wcu_wead_wock();
	eww = -ENODEV;
	mwx5_devcom_fow_each_peew_entwy_wcu(esw->devcom, esw, pos) {
		eww = mwx5_eswitch_vhca_id_to_vpowt(esw, vhca_id, vpowt);
		if (!eww)
			bweak;
	}
	wcu_wead_unwock();

	wetuwn eww;
}

static int
vewify_attw_actions(u32 actions, stwuct netwink_ext_ack *extack)
{
	if (!(actions &
	      (MWX5_FWOW_CONTEXT_ACTION_FWD_DEST | MWX5_FWOW_CONTEXT_ACTION_DWOP))) {
		NW_SET_EWW_MSG_MOD(extack, "Wuwe must have at weast one fowwawd/dwop action");
		wetuwn -EOPNOTSUPP;
	}

	if (!(~actions &
	      (MWX5_FWOW_CONTEXT_ACTION_FWD_DEST | MWX5_FWOW_CONTEXT_ACTION_DWOP))) {
		NW_SET_EWW_MSG_MOD(extack, "Wuwe cannot suppowt fowwawd+dwop action");
		wetuwn -EOPNOTSUPP;
	}

	if (actions & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW &&
	    actions & MWX5_FWOW_CONTEXT_ACTION_DWOP) {
		NW_SET_EWW_MSG_MOD(extack, "Dwop with modify headew action is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static boow
has_encap_dests(stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	int out_index;

	fow (out_index = 0; out_index < MWX5_MAX_FWOW_FWD_VPOWTS; out_index++)
		if (esw_attw->dests[out_index].fwags & MWX5_ESW_DEST_ENCAP)
			wetuwn twue;

	wetuwn fawse;
}

static int
post_pwocess_attw(stwuct mwx5e_tc_fwow *fwow,
		  stwuct mwx5_fwow_attw *attw,
		  stwuct netwink_ext_ack *extack)
{
	boow vf_tun;
	int eww = 0;

	eww = vewify_attw_actions(attw->action, extack);
	if (eww)
		goto eww_out;

	if (mwx5e_is_eswitch_fwow(fwow) && has_encap_dests(attw)) {
		eww = mwx5e_tc_tun_encap_dests_set(fwow->pwiv, fwow, attw, extack, &vf_tun);
		if (eww)
			goto eww_out;
	}

	if (attw->action & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW) {
		eww = mwx5e_tc_attach_mod_hdw(fwow->pwiv, fwow, attw);
		if (eww)
			goto eww_out;
	}

	if (attw->bwanch_twue &&
	    attw->bwanch_twue->action & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW) {
		eww = mwx5e_tc_attach_mod_hdw(fwow->pwiv, fwow, attw->bwanch_twue);
		if (eww)
			goto eww_out;
	}

	if (attw->bwanch_fawse &&
	    attw->bwanch_fawse->action & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW) {
		eww = mwx5e_tc_attach_mod_hdw(fwow->pwiv, fwow, attw->bwanch_fawse);
		if (eww)
			goto eww_out;
	}

	if (attw->action & MWX5_FWOW_CONTEXT_ACTION_COUNT) {
		eww = awwoc_fwow_attw_countew(get_fwow_countew_dev(fwow), attw);
		if (eww)
			goto eww_out;
	}

eww_out:
	wetuwn eww;
}

static int
mwx5e_tc_add_fdb_fwow(stwuct mwx5e_pwiv *pwiv,
		      stwuct mwx5e_tc_fwow *fwow,
		      stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw;
	stwuct mwx5_fwow_attw *attw = fwow->attw;
	stwuct mwx5_esw_fwow_attw *esw_attw;
	u32 max_pwio, max_chain;
	int eww = 0;

	pawse_attw = attw->pawse_attw;
	esw_attw = attw->esw_attw;

	/* We check chain wange onwy fow tc fwows.
	 * Fow ft fwows, we checked attw->chain was owiginawwy 0 and set it to
	 * FDB_FT_CHAIN which is outside tc wange.
	 * See mwx5e_wep_setup_ft_cb().
	 */
	max_chain = mwx5_chains_get_chain_wange(esw_chains(esw));
	if (!mwx5e_is_ft_fwow(fwow) && attw->chain > max_chain) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Wequested chain is out of suppowted wange");
		eww = -EOPNOTSUPP;
		goto eww_out;
	}

	max_pwio = mwx5_chains_get_pwio_wange(esw_chains(esw));
	if (attw->pwio > max_pwio) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Wequested pwiowity is out of suppowted wange");
		eww = -EOPNOTSUPP;
		goto eww_out;
	}

	if (fwow_fwag_test(fwow, TUN_WX)) {
		eww = mwx5e_attach_decap_woute(pwiv, fwow);
		if (eww)
			goto eww_out;

		if (!attw->chain && esw_attw->int_powt &&
		    attw->action & MWX5_FWOW_CONTEXT_ACTION_FWD_DEST) {
			/* If decap woute device is intewnaw powt, change the
			 * souwce vpowt vawue in weg_c0 back to upwink just in
			 * case the wuwe pewfowms goto chain > 0. If we have a miss
			 * on chain > 0 we want the metadata wegs to howd the
			 * chain id so SW wiww wesume handwing of this packet
			 * fwom the pwopew chain.
			 */
			u32 metadata = mwx5_eswitch_get_vpowt_metadata_fow_set(esw,
									esw_attw->in_wep->vpowt);

			eww = mwx5e_tc_match_to_weg_set(pwiv->mdev, &pawse_attw->mod_hdw_acts,
							MWX5_FWOW_NAMESPACE_FDB, VPOWT_TO_WEG,
							metadata);
			if (eww)
				goto eww_out;

			attw->action |= MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
		}
	}

	if (fwow_fwag_test(fwow, W3_TO_W2_DECAP)) {
		eww = mwx5e_attach_decap(pwiv, fwow, extack);
		if (eww)
			goto eww_out;
	}

	if (netif_is_ovs_mastew(pawse_attw->fiwtew_dev)) {
		stwuct mwx5e_tc_int_powt *int_powt;

		if (attw->chain) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Intewnaw powt wuwe is onwy suppowted on chain 0");
			eww = -EOPNOTSUPP;
			goto eww_out;
		}

		if (attw->dest_chain) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Intewnaw powt wuwe offwoad doesn't suppowt goto action");
			eww = -EOPNOTSUPP;
			goto eww_out;
		}

		int_powt = mwx5e_tc_int_powt_get(mwx5e_get_int_powt_pwiv(pwiv),
						 pawse_attw->fiwtew_dev->ifindex,
						 fwow_fwag_test(fwow, EGWESS) ?
						 MWX5E_TC_INT_POWT_EGWESS :
						 MWX5E_TC_INT_POWT_INGWESS);
		if (IS_EWW(int_powt)) {
			eww = PTW_EWW(int_powt);
			goto eww_out;
		}

		esw_attw->int_powt = int_powt;
	}

	eww = post_pwocess_attw(fwow, attw, extack);
	if (eww)
		goto eww_out;

	eww = mwx5e_tc_act_stats_add_fwow(get_act_stats_handwe(pwiv), fwow);
	if (eww)
		goto eww_out;

	/* we get hewe if one of the fowwowing takes pwace:
	 * (1) thewe's no ewwow
	 * (2) thewe's an encap action and we don't have vawid neigh
	 */
	if (fwow_fwag_test(fwow, SWOW))
		fwow->wuwe[0] = mwx5e_tc_offwoad_to_swow_path(esw, fwow, &pawse_attw->spec);
	ewse
		fwow->wuwe[0] = mwx5e_tc_offwoad_fdb_wuwes(esw, fwow, &pawse_attw->spec, attw);

	if (IS_EWW(fwow->wuwe[0])) {
		eww = PTW_EWW(fwow->wuwe[0]);
		goto eww_out;
	}
	fwow_fwag_set(fwow, OFFWOADED);

	wetuwn 0;

eww_out:
	fwow_fwag_set(fwow, FAIWED);
	wetuwn eww;
}

static boow mwx5_fwow_has_geneve_opt(stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5_fwow_spec *spec = &fwow->attw->pawse_attw->spec;
	void *headews_v = MWX5_ADDW_OF(fte_match_pawam,
				       spec->match_vawue,
				       misc_pawametews_3);
	u32 geneve_twv_opt_0_data = MWX5_GET(fte_match_set_misc3,
					     headews_v,
					     geneve_twv_option_0_data);

	wetuwn !!geneve_twv_opt_0_data;
}

static void fwee_bwanch_attw(stwuct mwx5e_tc_fwow *fwow, stwuct mwx5_fwow_attw *attw)
{
	if (!attw)
		wetuwn;

	mwx5_fwee_fwow_attw_actions(fwow, attw);
	kvfwee(attw->pawse_attw);
	kfwee(attw);
}

static void mwx5e_tc_dew_fdb_fwow(stwuct mwx5e_pwiv *pwiv,
				  stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct mwx5_fwow_attw *attw = fwow->attw;

	mwx5e_put_fwow_tunnew_id(fwow);

	wemove_unweady_fwow(fwow);

	if (mwx5e_is_offwoaded_fwow(fwow)) {
		if (fwow_fwag_test(fwow, SWOW))
			mwx5e_tc_unoffwoad_fwom_swow_path(esw, fwow);
		ewse
			mwx5e_tc_unoffwoad_fdb_wuwes(esw, fwow, attw);
	}
	compwete_aww(&fwow->dew_hw_done);

	if (mwx5_fwow_has_geneve_opt(fwow))
		mwx5_geneve_twv_option_dew(pwiv->mdev->geneve);

	if (fwow->decap_woute)
		mwx5e_detach_decap_woute(pwiv, fwow);

	mwx5_tc_ct_match_dew(get_ct_pwiv(pwiv), &fwow->attw->ct_attw);

	if (fwow_fwag_test(fwow, W3_TO_W2_DECAP))
		mwx5e_detach_decap(pwiv, fwow);

	mwx5e_tc_act_stats_dew_fwow(get_act_stats_handwe(pwiv), fwow);

	fwee_fwow_post_acts(fwow);
	mwx5_fwee_fwow_attw_actions(fwow, attw);

	kvfwee(attw->esw_attw->wx_tun_attw);
	kvfwee(attw->pawse_attw);
	kfwee(fwow->attw);
}

stwuct mwx5_fc *mwx5e_tc_get_countew(stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5_fwow_attw *attw;

	attw = wist_fiwst_entwy(&fwow->attws, stwuct mwx5_fwow_attw, wist);
	wetuwn attw->countew;
}

/* Itewate ovew tmp_wist of fwows attached to fwow_wist head. */
void mwx5e_put_fwow_wist(stwuct mwx5e_pwiv *pwiv, stwuct wist_head *fwow_wist)
{
	stwuct mwx5e_tc_fwow *fwow, *tmp;

	wist_fow_each_entwy_safe(fwow, tmp, fwow_wist, tmp_wist)
		mwx5e_fwow_put(pwiv, fwow);
}

static void mwx5e_tc_dew_fdb_peew_fwow(stwuct mwx5e_tc_fwow *fwow,
				       int peew_index)
{
	stwuct mwx5_eswitch *esw = fwow->pwiv->mdev->pwiv.eswitch;
	stwuct mwx5e_tc_fwow *peew_fwow;
	stwuct mwx5e_tc_fwow *tmp;

	if (!fwow_fwag_test(fwow, ESWITCH) ||
	    !fwow_fwag_test(fwow, DUP))
		wetuwn;

	mutex_wock(&esw->offwoads.peew_mutex);
	wist_dew(&fwow->peew[peew_index]);
	mutex_unwock(&esw->offwoads.peew_mutex);

	wist_fow_each_entwy_safe(peew_fwow, tmp, &fwow->peew_fwows, peew_fwows) {
		if (peew_index != mwx5_get_dev_index(peew_fwow->pwiv->mdev))
			continue;

		wist_dew(&peew_fwow->peew_fwows);
		if (wefcount_dec_and_test(&peew_fwow->wefcnt)) {
			mwx5e_tc_dew_fdb_fwow(peew_fwow->pwiv, peew_fwow);
			kfwee(peew_fwow);
		}
	}

	if (wist_empty(&fwow->peew_fwows))
		fwow_fwag_cweaw(fwow, DUP);
}

static void mwx5e_tc_dew_fdb_peews_fwow(stwuct mwx5e_tc_fwow *fwow)
{
	int i;

	fow (i = 0; i < MWX5_MAX_POWTS; i++) {
		if (i == mwx5_get_dev_index(fwow->pwiv->mdev))
			continue;
		mwx5e_tc_dew_fdb_peew_fwow(fwow, i);
	}
}

static void mwx5e_tc_dew_fwow(stwuct mwx5e_pwiv *pwiv,
			      stwuct mwx5e_tc_fwow *fwow)
{
	if (mwx5e_is_eswitch_fwow(fwow)) {
		stwuct mwx5_devcom_comp_dev *devcom = fwow->pwiv->mdev->pwiv.eswitch->devcom;

		if (!mwx5_devcom_fow_each_peew_begin(devcom)) {
			mwx5e_tc_dew_fdb_fwow(pwiv, fwow);
			wetuwn;
		}

		mwx5e_tc_dew_fdb_peews_fwow(fwow);
		mwx5_devcom_fow_each_peew_end(devcom);
		mwx5e_tc_dew_fdb_fwow(pwiv, fwow);
	} ewse {
		mwx5e_tc_dew_nic_fwow(pwiv, fwow);
	}
}

static boow fwow_wequiwes_tunnew_mapping(u32 chain, stwuct fwow_cws_offwoad *f)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct fwow_action *fwow_action = &wuwe->action;
	const stwuct fwow_action_entwy *act;
	int i;

	if (chain)
		wetuwn fawse;

	fwow_action_fow_each(i, act, fwow_action) {
		switch (act->id) {
		case FWOW_ACTION_GOTO:
			wetuwn twue;
		case FWOW_ACTION_SAMPWE:
			wetuwn twue;
		defauwt:
			continue;
		}
	}

	wetuwn fawse;
}

static int
enc_opts_is_dont_cawe_ow_fuww_match(stwuct mwx5e_pwiv *pwiv,
				    stwuct fwow_dissectow_key_enc_opts *opts,
				    stwuct netwink_ext_ack *extack,
				    boow *dont_cawe)
{
	stwuct geneve_opt *opt;
	int off = 0;

	*dont_cawe = twue;

	whiwe (opts->wen > off) {
		opt = (stwuct geneve_opt *)&opts->data[off];

		if (!(*dont_cawe) || opt->opt_cwass || opt->type ||
		    memchw_inv(opt->opt_data, 0, opt->wength * 4)) {
			*dont_cawe = fawse;

			if (opt->opt_cwass != htons(U16_MAX) ||
			    opt->type != U8_MAX) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Pawtiaw match of tunnew options in chain > 0 isn't suppowted");
				netdev_wawn(pwiv->netdev,
					    "Pawtiaw match of tunnew options in chain > 0 isn't suppowted");
				wetuwn -EOPNOTSUPP;
			}
		}

		off += sizeof(stwuct geneve_opt) + opt->wength * 4;
	}

	wetuwn 0;
}

#define COPY_DISSECTOW(wuwe, diss_key, dst)\
({ \
	stwuct fwow_wuwe *__wuwe = (wuwe);\
	typeof(dst) __dst = dst;\
\
	memcpy(__dst,\
	       skb_fwow_dissectow_tawget(__wuwe->match.dissectow,\
					 diss_key,\
					 __wuwe->match.key),\
	       sizeof(*__dst));\
})

static int mwx5e_get_fwow_tunnew_id(stwuct mwx5e_pwiv *pwiv,
				    stwuct mwx5e_tc_fwow *fwow,
				    stwuct fwow_cws_offwoad *f,
				    stwuct net_device *fiwtew_dev)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct mwx5e_tc_mod_hdw_acts *mod_hdw_acts;
	stwuct fwow_match_enc_opts enc_opts_match;
	stwuct tunnew_match_enc_opts tun_enc_opts;
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5_fwow_attw *attw = fwow->attw;
	stwuct mwx5e_wep_pwiv *upwink_wpwiv;
	stwuct tunnew_match_key tunnew_key;
	boow enc_opts_is_dont_cawe = twue;
	u32 tun_id, enc_opts_id = 0;
	stwuct mwx5_eswitch *esw;
	u32 vawue, mask;
	int eww;

	esw = pwiv->mdev->pwiv.eswitch;
	upwink_wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
	upwink_pwiv = &upwink_wpwiv->upwink_pwiv;

	memset(&tunnew_key, 0, sizeof(tunnew_key));
	COPY_DISSECTOW(wuwe, FWOW_DISSECTOW_KEY_ENC_CONTWOW,
		       &tunnew_key.enc_contwow);
	if (tunnew_key.enc_contwow.addw_type == FWOW_DISSECTOW_KEY_IPV4_ADDWS)
		COPY_DISSECTOW(wuwe, FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS,
			       &tunnew_key.enc_ipv4);
	ewse
		COPY_DISSECTOW(wuwe, FWOW_DISSECTOW_KEY_ENC_IPV6_ADDWS,
			       &tunnew_key.enc_ipv6);
	COPY_DISSECTOW(wuwe, FWOW_DISSECTOW_KEY_ENC_IP, &tunnew_key.enc_ip);
	COPY_DISSECTOW(wuwe, FWOW_DISSECTOW_KEY_ENC_POWTS,
		       &tunnew_key.enc_tp);
	COPY_DISSECTOW(wuwe, FWOW_DISSECTOW_KEY_ENC_KEYID,
		       &tunnew_key.enc_key_id);
	tunnew_key.fiwtew_ifindex = fiwtew_dev->ifindex;

	eww = mapping_add(upwink_pwiv->tunnew_mapping, &tunnew_key, &tun_id);
	if (eww)
		wetuwn eww;

	fwow_wuwe_match_enc_opts(wuwe, &enc_opts_match);
	eww = enc_opts_is_dont_cawe_ow_fuww_match(pwiv,
						  enc_opts_match.mask,
						  extack,
						  &enc_opts_is_dont_cawe);
	if (eww)
		goto eww_enc_opts;

	if (!enc_opts_is_dont_cawe) {
		memset(&tun_enc_opts, 0, sizeof(tun_enc_opts));
		memcpy(&tun_enc_opts.key, enc_opts_match.key,
		       sizeof(*enc_opts_match.key));
		memcpy(&tun_enc_opts.mask, enc_opts_match.mask,
		       sizeof(*enc_opts_match.mask));

		eww = mapping_add(upwink_pwiv->tunnew_enc_opts_mapping,
				  &tun_enc_opts, &enc_opts_id);
		if (eww)
			goto eww_enc_opts;
	}

	vawue = tun_id << ENC_OPTS_BITS | enc_opts_id;
	mask = enc_opts_id ? TUNNEW_ID_MASK :
			     (TUNNEW_ID_MASK & ~ENC_OPTS_BITS_MASK);

	if (attw->chain) {
		mwx5e_tc_match_to_weg_match(&attw->pawse_attw->spec,
					    TUNNEW_TO_WEG, vawue, mask);
	} ewse {
		mod_hdw_acts = &attw->pawse_attw->mod_hdw_acts;
		eww = mwx5e_tc_match_to_weg_set(pwiv->mdev,
						mod_hdw_acts, MWX5_FWOW_NAMESPACE_FDB,
						TUNNEW_TO_WEG, vawue);
		if (eww)
			goto eww_set;

		attw->action |= MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
	}

	fwow->attw->tunnew_id = vawue;
	wetuwn 0;

eww_set:
	if (enc_opts_id)
		mapping_wemove(upwink_pwiv->tunnew_enc_opts_mapping,
			       enc_opts_id);
eww_enc_opts:
	mapping_wemove(upwink_pwiv->tunnew_mapping, tun_id);
	wetuwn eww;
}

static void mwx5e_put_fwow_tunnew_id(stwuct mwx5e_tc_fwow *fwow)
{
	u32 enc_opts_id = fwow->attw->tunnew_id & ENC_OPTS_BITS_MASK;
	u32 tun_id = fwow->attw->tunnew_id >> ENC_OPTS_BITS;
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5e_wep_pwiv *upwink_wpwiv;
	stwuct mwx5_eswitch *esw;

	esw = fwow->pwiv->mdev->pwiv.eswitch;
	upwink_wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
	upwink_pwiv = &upwink_wpwiv->upwink_pwiv;

	if (tun_id)
		mapping_wemove(upwink_pwiv->tunnew_mapping, tun_id);
	if (enc_opts_id)
		mapping_wemove(upwink_pwiv->tunnew_enc_opts_mapping,
			       enc_opts_id);
}

void mwx5e_tc_set_ethewtype(stwuct mwx5_cowe_dev *mdev,
			    stwuct fwow_match_basic *match, boow outew,
			    void *headews_c, void *headews_v)
{
	boow ip_vewsion_cap;

	ip_vewsion_cap = outew ?
		MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
					  ft_fiewd_suppowt.outew_ip_vewsion) :
		MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
					  ft_fiewd_suppowt.innew_ip_vewsion);

	if (ip_vewsion_cap && match->mask->n_pwoto == htons(0xFFFF) &&
	    (match->key->n_pwoto == htons(ETH_P_IP) ||
	     match->key->n_pwoto == htons(ETH_P_IPV6))) {
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c, ip_vewsion);
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, ip_vewsion,
			 match->key->n_pwoto == htons(ETH_P_IP) ? 4 : 6);
	} ewse {
		MWX5_SET(fte_match_set_wyw_2_4, headews_c, ethewtype,
			 ntohs(match->mask->n_pwoto));
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, ethewtype,
			 ntohs(match->key->n_pwoto));
	}
}

u8 mwx5e_tc_get_ip_vewsion(stwuct mwx5_fwow_spec *spec, boow outew)
{
	void *headews_v;
	u16 ethewtype;
	u8 ip_vewsion;

	if (outew)
		headews_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, outew_headews);
	ewse
		headews_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, innew_headews);

	ip_vewsion = MWX5_GET(fte_match_set_wyw_2_4, headews_v, ip_vewsion);
	/* Wetuwn ip_vewsion convewted fwom ethewtype anyway */
	if (!ip_vewsion) {
		ethewtype = MWX5_GET(fte_match_set_wyw_2_4, headews_v, ethewtype);
		if (ethewtype == ETH_P_IP || ethewtype == ETH_P_AWP)
			ip_vewsion = 4;
		ewse if (ethewtype == ETH_P_IPV6)
			ip_vewsion = 6;
	}
	wetuwn ip_vewsion;
}

/* Tunnew device fowwows WFC 6040, see incwude/net/inet_ecn.h.
 * And changes innew ip_ecn depending on innew and outew ip_ecn as fowwows:
 *      +---------+----------------------------------------+
 *      |Awwiving |         Awwiving Outew Headew          |
 *      |   Innew +---------+---------+---------+----------+
 *      |  Headew | Not-ECT | ECT(0)  | ECT(1)  |   CE     |
 *      +---------+---------+---------+---------+----------+
 *      | Not-ECT | Not-ECT | Not-ECT | Not-ECT | <dwop>   |
 *      |  ECT(0) |  ECT(0) | ECT(0)  | ECT(1)  |   CE*    |
 *      |  ECT(1) |  ECT(1) | ECT(1)  | ECT(1)* |   CE*    |
 *      |    CE   |   CE    |  CE     | CE      |   CE     |
 *      +---------+---------+---------+---------+----------+
 *
 * Tc matches on innew aftew decapsuwation on tunnew device, but hw offwoad matches
 * the innew ip_ecn vawue befowe hawdwawe decap action.
 *
 * Cewws mawked awe changed fwom owiginaw innew packet ip_ecn vawue duwing decap, and
 * so matching those vawues on innew ip_ecn befowe decap wiww faiw.
 *
 * The fowwowing hewpew awwows offwoad when innew ip_ecn won't be changed by outew ip_ecn,
 * except fow the outew ip_ecn = CE, whewe in aww cases innew ip_ecn wiww be changed to CE,
 * and such we can dwop the innew ip_ecn=CE match.
 */

static int mwx5e_tc_vewify_tunnew_ecn(stwuct mwx5e_pwiv *pwiv,
				      stwuct fwow_cws_offwoad *f,
				      boow *match_innew_ecn)
{
	u8 outew_ecn_mask = 0, outew_ecn_key = 0, innew_ecn_mask = 0, innew_ecn_key = 0;
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct fwow_match_ip match;

	*match_innew_ecn = twue;

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_IP)) {
		fwow_wuwe_match_enc_ip(wuwe, &match);
		outew_ecn_key = match.key->tos & INET_ECN_MASK;
		outew_ecn_mask = match.mask->tos & INET_ECN_MASK;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IP)) {
		fwow_wuwe_match_ip(wuwe, &match);
		innew_ecn_key = match.key->tos & INET_ECN_MASK;
		innew_ecn_mask = match.mask->tos & INET_ECN_MASK;
	}

	if (outew_ecn_mask != 0 && outew_ecn_mask != INET_ECN_MASK) {
		NW_SET_EWW_MSG_MOD(extack, "Pawtiaw match on enc_tos ecn bits isn't suppowted");
		netdev_wawn(pwiv->netdev, "Pawtiaw match on enc_tos ecn bits isn't suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (!outew_ecn_mask) {
		if (!innew_ecn_mask)
			wetuwn 0;

		NW_SET_EWW_MSG_MOD(extack,
				   "Matching on tos ecn bits without awso matching enc_tos ecn bits isn't suppowted");
		netdev_wawn(pwiv->netdev,
			    "Matching on tos ecn bits without awso matching enc_tos ecn bits isn't suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (innew_ecn_mask && innew_ecn_mask != INET_ECN_MASK) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Pawtiaw match on tos ecn bits with match on enc_tos ecn bits isn't suppowted");
		netdev_wawn(pwiv->netdev,
			    "Pawtiaw match on tos ecn bits with match on enc_tos ecn bits isn't suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (!innew_ecn_mask)
		wetuwn 0;

	/* Both innew and outew have fuww mask on ecn */

	if (outew_ecn_key == INET_ECN_ECT_1) {
		/* innew ecn might change by DECAP action */

		NW_SET_EWW_MSG_MOD(extack, "Match on enc_tos ecn = ECT(1) isn't suppowted");
		netdev_wawn(pwiv->netdev, "Match on enc_tos ecn = ECT(1) isn't suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (outew_ecn_key != INET_ECN_CE)
		wetuwn 0;

	if (innew_ecn_key != INET_ECN_CE) {
		/* Can't happen in softwawe, as packet ecn wiww be changed to CE aftew decap */
		NW_SET_EWW_MSG_MOD(extack,
				   "Match on tos enc_tos ecn = CE whiwe match on tos ecn != CE isn't suppowted");
		netdev_wawn(pwiv->netdev,
			    "Match on tos enc_tos ecn = CE whiwe match on tos ecn != CE isn't suppowted");
		wetuwn -EOPNOTSUPP;
	}

	/* outew ecn = CE, innew ecn = CE, as decap wiww change innew ecn to CE in anycase,
	 * dwop match on innew ecn
	 */
	*match_innew_ecn = fawse;

	wetuwn 0;
}

static int pawse_tunnew_attw(stwuct mwx5e_pwiv *pwiv,
			     stwuct mwx5e_tc_fwow *fwow,
			     stwuct mwx5_fwow_spec *spec,
			     stwuct fwow_cws_offwoad *f,
			     stwuct net_device *fiwtew_dev,
			     u8 *match_wevew,
			     boow *match_innew)
{
	stwuct mwx5e_tc_tunnew *tunnew = mwx5e_get_tc_tun(fiwtew_dev);
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct netwink_ext_ack *extack = f->common.extack;
	boow needs_mapping, sets_mapping;
	int eww;

	if (!mwx5e_is_eswitch_fwow(fwow)) {
		NW_SET_EWW_MSG_MOD(extack, "Match on tunnew is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	needs_mapping = !!fwow->attw->chain;
	sets_mapping = fwow_wequiwes_tunnew_mapping(fwow->attw->chain, f);
	*match_innew = !needs_mapping;

	if ((needs_mapping || sets_mapping) &&
	    !mwx5_eswitch_weg_c1_woopback_enabwed(esw)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Chains on tunnew devices isn't suppowted without wegistew woopback suppowt");
		netdev_wawn(pwiv->netdev,
			    "Chains on tunnew devices isn't suppowted without wegistew woopback suppowt");
		wetuwn -EOPNOTSUPP;
	}

	if (!fwow->attw->chain) {
		eww = mwx5e_tc_tun_pawse(fiwtew_dev, pwiv, spec, f,
					 match_wevew);
		if (eww) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Faiwed to pawse tunnew attwibutes");
			netdev_wawn(pwiv->netdev,
				    "Faiwed to pawse tunnew attwibutes");
			wetuwn eww;
		}

		/* With mpws ovew udp we decapsuwate using packet wefowmat
		 * object
		 */
		if (!netif_is_baweudp(fiwtew_dev))
			fwow->attw->action |= MWX5_FWOW_CONTEXT_ACTION_DECAP;
		eww = mwx5e_tc_set_attw_wx_tun(fwow, spec);
		if (eww)
			wetuwn eww;
	} ewse if (tunnew) {
		stwuct mwx5_fwow_spec *tmp_spec;

		tmp_spec = kvzawwoc(sizeof(*tmp_spec), GFP_KEWNEW);
		if (!tmp_spec) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to awwocate memowy fow tunnew tmp spec");
			netdev_wawn(pwiv->netdev, "Faiwed to awwocate memowy fow tunnew tmp spec");
			wetuwn -ENOMEM;
		}
		memcpy(tmp_spec, spec, sizeof(*tmp_spec));

		eww = mwx5e_tc_tun_pawse(fiwtew_dev, pwiv, tmp_spec, f, match_wevew);
		if (eww) {
			kvfwee(tmp_spec);
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to pawse tunnew attwibutes");
			netdev_wawn(pwiv->netdev, "Faiwed to pawse tunnew attwibutes");
			wetuwn eww;
		}
		eww = mwx5e_tc_set_attw_wx_tun(fwow, tmp_spec);
		kvfwee(tmp_spec);
		if (eww)
			wetuwn eww;
	}

	if (!needs_mapping && !sets_mapping)
		wetuwn 0;

	wetuwn mwx5e_get_fwow_tunnew_id(pwiv, fwow, f, fiwtew_dev);
}

static void *get_match_innew_headews_cwitewia(stwuct mwx5_fwow_spec *spec)
{
	wetuwn MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
			    innew_headews);
}

static void *get_match_innew_headews_vawue(stwuct mwx5_fwow_spec *spec)
{
	wetuwn MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
			    innew_headews);
}

static void *get_match_outew_headews_cwitewia(stwuct mwx5_fwow_spec *spec)
{
	wetuwn MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
			    outew_headews);
}

static void *get_match_outew_headews_vawue(stwuct mwx5_fwow_spec *spec)
{
	wetuwn MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
			    outew_headews);
}

void *mwx5e_get_match_headews_vawue(u32 fwags, stwuct mwx5_fwow_spec *spec)
{
	wetuwn (fwags & MWX5_FWOW_CONTEXT_ACTION_DECAP) ?
		get_match_innew_headews_vawue(spec) :
		get_match_outew_headews_vawue(spec);
}

void *mwx5e_get_match_headews_cwitewia(u32 fwags, stwuct mwx5_fwow_spec *spec)
{
	wetuwn (fwags & MWX5_FWOW_CONTEXT_ACTION_DECAP) ?
		get_match_innew_headews_cwitewia(spec) :
		get_match_outew_headews_cwitewia(spec);
}

static int mwx5e_fwowew_pawse_meta(stwuct net_device *fiwtew_dev,
				   stwuct fwow_cws_offwoad *f)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct net_device *ingwess_dev;
	stwuct fwow_match_meta match;

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_META))
		wetuwn 0;

	fwow_wuwe_match_meta(wuwe, &match);

	if (match.mask->w2_miss) {
		NW_SET_EWW_MSG_MOD(f->common.extack, "Can't match on \"w2_miss\"");
		wetuwn -EOPNOTSUPP;
	}

	if (!match.mask->ingwess_ifindex)
		wetuwn 0;

	if (match.mask->ingwess_ifindex != 0xFFFFFFFF) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted ingwess ifindex mask");
		wetuwn -EOPNOTSUPP;
	}

	ingwess_dev = __dev_get_by_index(dev_net(fiwtew_dev),
					 match.key->ingwess_ifindex);
	if (!ingwess_dev) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can't find the ingwess powt to match on");
		wetuwn -ENOENT;
	}

	if (ingwess_dev != fiwtew_dev) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can't match on the ingwess fiwtew powt");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static boow skip_key_basic(stwuct net_device *fiwtew_dev,
			   stwuct fwow_cws_offwoad *f)
{
	/* When doing mpws ovew udp decap, the usew needs to pwovide
	 * MPWS_UC as the pwotocow in owdew to be abwe to match on mpws
	 * wabew fiewds.  Howevew, the actuaw ethewtype is IP so we want to
	 * avoid matching on this, othewwise we'ww faiw the match.
	 */
	if (netif_is_baweudp(fiwtew_dev) && f->common.chain_index == 0)
		wetuwn twue;

	wetuwn fawse;
}

static int __pawse_cws_fwowew(stwuct mwx5e_pwiv *pwiv,
			      stwuct mwx5e_tc_fwow *fwow,
			      stwuct mwx5_fwow_spec *spec,
			      stwuct fwow_cws_offwoad *f,
			      stwuct net_device *fiwtew_dev,
			      u8 *innew_match_wevew, u8 *outew_match_wevew)
{
	stwuct netwink_ext_ack *extack = f->common.extack;
	void *headews_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				       outew_headews);
	void *headews_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				       outew_headews);
	void *misc_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				    misc_pawametews);
	void *misc_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    misc_pawametews);
	void *misc_c_3 = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				    misc_pawametews_3);
	void *misc_v_3 = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    misc_pawametews_3);
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct fwow_dissectow *dissectow = wuwe->match.dissectow;
	enum fs_fwow_tabwe_type fs_type;
	boow match_innew_ecn = twue;
	u16 addw_type = 0;
	u8 ip_pwoto = 0;
	u8 *match_wevew;
	int eww;

	fs_type = mwx5e_is_eswitch_fwow(fwow) ? FS_FT_FDB : FS_FT_NIC_WX;
	match_wevew = outew_match_wevew;

	if (dissectow->used_keys &
	    ~(BIT_UWW(FWOW_DISSECTOW_KEY_META) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_CONTWOW) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_BASIC) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ETH_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_VWAN) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_CVWAN) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IPV4_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IPV6_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_POWTS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_KEYID) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV4_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IPV6_ADDWS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_POWTS)	|
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_CONTWOW) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_TCP) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_IP)  |
	      BIT_UWW(FWOW_DISSECTOW_KEY_CT) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_IP) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ENC_OPTS) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_ICMP) |
	      BIT_UWW(FWOW_DISSECTOW_KEY_MPWS))) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted key");
		netdev_dbg(pwiv->netdev, "Unsuppowted key used: 0x%wwx\n",
			   dissectow->used_keys);
		wetuwn -EOPNOTSUPP;
	}

	if (mwx5e_get_tc_tun(fiwtew_dev)) {
		boow match_innew = fawse;

		eww = pawse_tunnew_attw(pwiv, fwow, spec, f, fiwtew_dev,
					outew_match_wevew, &match_innew);
		if (eww)
			wetuwn eww;

		if (match_innew) {
			/* headew pointews shouwd point to the innew headews
			 * if the packet was decapsuwated awweady.
			 * outew headews awe set by pawse_tunnew_attw.
			 */
			match_wevew = innew_match_wevew;
			headews_c = get_match_innew_headews_cwitewia(spec);
			headews_v = get_match_innew_headews_vawue(spec);
		}

		eww = mwx5e_tc_vewify_tunnew_ecn(pwiv, f, &match_innew_ecn);
		if (eww)
			wetuwn eww;
	}

	eww = mwx5e_fwowew_pawse_meta(fiwtew_dev, f);
	if (eww)
		wetuwn eww;

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_BASIC) &&
	    !skip_key_basic(fiwtew_dev, f)) {
		stwuct fwow_match_basic match;

		fwow_wuwe_match_basic(wuwe, &match);
		mwx5e_tc_set_ethewtype(pwiv->mdev, &match,
				       match_wevew == outew_match_wevew,
				       headews_c, headews_v);

		if (match.mask->n_pwoto)
			*match_wevew = MWX5_MATCH_W2;
	}
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_VWAN) ||
	    is_vwan_dev(fiwtew_dev)) {
		stwuct fwow_dissectow_key_vwan fiwtew_dev_mask;
		stwuct fwow_dissectow_key_vwan fiwtew_dev_key;
		stwuct fwow_match_vwan match;

		if (is_vwan_dev(fiwtew_dev)) {
			match.key = &fiwtew_dev_key;
			match.key->vwan_id = vwan_dev_vwan_id(fiwtew_dev);
			match.key->vwan_tpid = vwan_dev_vwan_pwoto(fiwtew_dev);
			match.key->vwan_pwiowity = 0;
			match.mask = &fiwtew_dev_mask;
			memset(match.mask, 0xff, sizeof(*match.mask));
			match.mask->vwan_pwiowity = 0;
		} ewse {
			fwow_wuwe_match_vwan(wuwe, &match);
		}
		if (match.mask->vwan_id ||
		    match.mask->vwan_pwiowity ||
		    match.mask->vwan_tpid) {
			if (match.key->vwan_tpid == htons(ETH_P_8021AD)) {
				MWX5_SET(fte_match_set_wyw_2_4, headews_c,
					 svwan_tag, 1);
				MWX5_SET(fte_match_set_wyw_2_4, headews_v,
					 svwan_tag, 1);
			} ewse {
				MWX5_SET(fte_match_set_wyw_2_4, headews_c,
					 cvwan_tag, 1);
				MWX5_SET(fte_match_set_wyw_2_4, headews_v,
					 cvwan_tag, 1);
			}

			MWX5_SET(fte_match_set_wyw_2_4, headews_c, fiwst_vid,
				 match.mask->vwan_id);
			MWX5_SET(fte_match_set_wyw_2_4, headews_v, fiwst_vid,
				 match.key->vwan_id);

			MWX5_SET(fte_match_set_wyw_2_4, headews_c, fiwst_pwio,
				 match.mask->vwan_pwiowity);
			MWX5_SET(fte_match_set_wyw_2_4, headews_v, fiwst_pwio,
				 match.key->vwan_pwiowity);

			*match_wevew = MWX5_MATCH_W2;

			if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CVWAN) &&
			    match.mask->vwan_eth_type &&
			    MWX5_CAP_FWOWTABWE_TYPE(pwiv->mdev,
						    ft_fiewd_suppowt.outew_second_vid,
						    fs_type)) {
				MWX5_SET(fte_match_set_misc, misc_c,
					 outew_second_cvwan_tag, 1);
				spec->match_cwitewia_enabwe |=
					MWX5_MATCH_MISC_PAWAMETEWS;
			}
		}
	} ewse if (*match_wevew != MWX5_MATCH_NONE) {
		/* cvwan_tag enabwed in match cwitewia and
		 * disabwed in match vawue means both S & C tags
		 * don't exist (untagged of both)
		 */
		MWX5_SET(fte_match_set_wyw_2_4, headews_c, cvwan_tag, 1);
		*match_wevew = MWX5_MATCH_W2;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CVWAN)) {
		stwuct fwow_match_vwan match;

		fwow_wuwe_match_cvwan(wuwe, &match);
		if (match.mask->vwan_id ||
		    match.mask->vwan_pwiowity ||
		    match.mask->vwan_tpid) {
			if (!MWX5_CAP_FWOWTABWE_TYPE(pwiv->mdev, ft_fiewd_suppowt.outew_second_vid,
						     fs_type)) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Matching on CVWAN is not suppowted");
				wetuwn -EOPNOTSUPP;
			}

			if (match.key->vwan_tpid == htons(ETH_P_8021AD)) {
				MWX5_SET(fte_match_set_misc, misc_c,
					 outew_second_svwan_tag, 1);
				MWX5_SET(fte_match_set_misc, misc_v,
					 outew_second_svwan_tag, 1);
			} ewse {
				MWX5_SET(fte_match_set_misc, misc_c,
					 outew_second_cvwan_tag, 1);
				MWX5_SET(fte_match_set_misc, misc_v,
					 outew_second_cvwan_tag, 1);
			}

			MWX5_SET(fte_match_set_misc, misc_c, outew_second_vid,
				 match.mask->vwan_id);
			MWX5_SET(fte_match_set_misc, misc_v, outew_second_vid,
				 match.key->vwan_id);
			MWX5_SET(fte_match_set_misc, misc_c, outew_second_pwio,
				 match.mask->vwan_pwiowity);
			MWX5_SET(fte_match_set_misc, misc_v, outew_second_pwio,
				 match.key->vwan_pwiowity);

			*match_wevew = MWX5_MATCH_W2;
			spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS;
		}
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ETH_ADDWS)) {
		stwuct fwow_match_eth_addws match;

		fwow_wuwe_match_eth_addws(wuwe, &match);
		ethew_addw_copy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
					     dmac_47_16),
				match.mask->dst);
		ethew_addw_copy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
					     dmac_47_16),
				match.key->dst);

		ethew_addw_copy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
					     smac_47_16),
				match.mask->swc);
		ethew_addw_copy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
					     smac_47_16),
				match.key->swc);

		if (!is_zewo_ethew_addw(match.mask->swc) ||
		    !is_zewo_ethew_addw(match.mask->dst))
			*match_wevew = MWX5_MATCH_W2;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_CONTWOW)) {
		stwuct fwow_match_contwow match;

		fwow_wuwe_match_contwow(wuwe, &match);
		addw_type = match.key->addw_type;

		/* the HW doesn't suppowt fwag fiwst/watew */
		if (match.mask->fwags & FWOW_DIS_FIWST_FWAG) {
			NW_SET_EWW_MSG_MOD(extack, "Match on fwag fiwst/watew is not suppowted");
			wetuwn -EOPNOTSUPP;
		}

		if (match.mask->fwags & FWOW_DIS_IS_FWAGMENT) {
			MWX5_SET(fte_match_set_wyw_2_4, headews_c, fwag, 1);
			MWX5_SET(fte_match_set_wyw_2_4, headews_v, fwag,
				 match.key->fwags & FWOW_DIS_IS_FWAGMENT);

			/* the HW doesn't need W3 inwine to match on fwag=no */
			if (!(match.key->fwags & FWOW_DIS_IS_FWAGMENT))
				*match_wevew = MWX5_MATCH_W2;
	/* ***  W2 attwibutes pawsing up to hewe *** */
			ewse
				*match_wevew = MWX5_MATCH_W3;
		}
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_BASIC)) {
		stwuct fwow_match_basic match;

		fwow_wuwe_match_basic(wuwe, &match);
		ip_pwoto = match.key->ip_pwoto;

		MWX5_SET(fte_match_set_wyw_2_4, headews_c, ip_pwotocow,
			 match.mask->ip_pwoto);
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, ip_pwotocow,
			 match.key->ip_pwoto);

		if (match.mask->ip_pwoto)
			*match_wevew = MWX5_MATCH_W3;
	}

	if (addw_type == FWOW_DISSECTOW_KEY_IPV4_ADDWS) {
		stwuct fwow_match_ipv4_addws match;

		fwow_wuwe_match_ipv4_addws(wuwe, &match);
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
				    swc_ipv4_swc_ipv6.ipv4_wayout.ipv4),
		       &match.mask->swc, sizeof(match.mask->swc));
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
				    swc_ipv4_swc_ipv6.ipv4_wayout.ipv4),
		       &match.key->swc, sizeof(match.key->swc));
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
				    dst_ipv4_dst_ipv6.ipv4_wayout.ipv4),
		       &match.mask->dst, sizeof(match.mask->dst));
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
				    dst_ipv4_dst_ipv6.ipv4_wayout.ipv4),
		       &match.key->dst, sizeof(match.key->dst));

		if (match.mask->swc || match.mask->dst)
			*match_wevew = MWX5_MATCH_W3;
	}

	if (addw_type == FWOW_DISSECTOW_KEY_IPV6_ADDWS) {
		stwuct fwow_match_ipv6_addws match;

		fwow_wuwe_match_ipv6_addws(wuwe, &match);
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
				    swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
		       &match.mask->swc, sizeof(match.mask->swc));
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
				    swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
		       &match.key->swc, sizeof(match.key->swc));

		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
				    dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
		       &match.mask->dst, sizeof(match.mask->dst));
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
				    dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
		       &match.key->dst, sizeof(match.key->dst));

		if (ipv6_addw_type(&match.mask->swc) != IPV6_ADDW_ANY ||
		    ipv6_addw_type(&match.mask->dst) != IPV6_ADDW_ANY)
			*match_wevew = MWX5_MATCH_W3;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_IP)) {
		stwuct fwow_match_ip match;

		fwow_wuwe_match_ip(wuwe, &match);
		if (match_innew_ecn) {
			MWX5_SET(fte_match_set_wyw_2_4, headews_c, ip_ecn,
				 match.mask->tos & 0x3);
			MWX5_SET(fte_match_set_wyw_2_4, headews_v, ip_ecn,
				 match.key->tos & 0x3);
		}

		MWX5_SET(fte_match_set_wyw_2_4, headews_c, ip_dscp,
			 match.mask->tos >> 2);
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, ip_dscp,
			 match.key->tos  >> 2);

		MWX5_SET(fte_match_set_wyw_2_4, headews_c, ttw_hopwimit,
			 match.mask->ttw);
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, ttw_hopwimit,
			 match.key->ttw);

		if (match.mask->ttw &&
		    !MWX5_CAP_ESW_FWOWTABWE_FDB(pwiv->mdev,
						ft_fiewd_suppowt.outew_ipv4_ttw)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Matching on TTW is not suppowted");
			wetuwn -EOPNOTSUPP;
		}

		if (match.mask->tos || match.mask->ttw)
			*match_wevew = MWX5_MATCH_W3;
	}

	/* ***  W3 attwibutes pawsing up to hewe *** */

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_POWTS)) {
		stwuct fwow_match_powts match;

		fwow_wuwe_match_powts(wuwe, &match);
		switch (ip_pwoto) {
		case IPPWOTO_TCP:
			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 tcp_spowt, ntohs(match.mask->swc));
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 tcp_spowt, ntohs(match.key->swc));

			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 tcp_dpowt, ntohs(match.mask->dst));
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 tcp_dpowt, ntohs(match.key->dst));
			bweak;

		case IPPWOTO_UDP:
			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 udp_spowt, ntohs(match.mask->swc));
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 udp_spowt, ntohs(match.key->swc));

			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 udp_dpowt, ntohs(match.mask->dst));
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 udp_dpowt, ntohs(match.key->dst));
			bweak;
		defauwt:
			NW_SET_EWW_MSG_MOD(extack,
					   "Onwy UDP and TCP twanspowts awe suppowted fow W4 matching");
			netdev_eww(pwiv->netdev,
				   "Onwy UDP and TCP twanspowt awe suppowted\n");
			wetuwn -EINVAW;
		}

		if (match.mask->swc || match.mask->dst)
			*match_wevew = MWX5_MATCH_W4;
	}

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_TCP)) {
		stwuct fwow_match_tcp match;

		fwow_wuwe_match_tcp(wuwe, &match);
		MWX5_SET(fte_match_set_wyw_2_4, headews_c, tcp_fwags,
			 ntohs(match.mask->fwags));
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, tcp_fwags,
			 ntohs(match.key->fwags));

		if (match.mask->fwags)
			*match_wevew = MWX5_MATCH_W4;
	}
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ICMP)) {
		stwuct fwow_match_icmp match;

		fwow_wuwe_match_icmp(wuwe, &match);
		switch (ip_pwoto) {
		case IPPWOTO_ICMP:
			if (!(MWX5_CAP_GEN(pwiv->mdev, fwex_pawsew_pwotocows) &
			      MWX5_FWEX_PWOTO_ICMP)) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Match on Fwex pwotocows fow ICMP is not suppowted");
				wetuwn -EOPNOTSUPP;
			}
			MWX5_SET(fte_match_set_misc3, misc_c_3, icmp_type,
				 match.mask->type);
			MWX5_SET(fte_match_set_misc3, misc_v_3, icmp_type,
				 match.key->type);
			MWX5_SET(fte_match_set_misc3, misc_c_3, icmp_code,
				 match.mask->code);
			MWX5_SET(fte_match_set_misc3, misc_v_3, icmp_code,
				 match.key->code);
			bweak;
		case IPPWOTO_ICMPV6:
			if (!(MWX5_CAP_GEN(pwiv->mdev, fwex_pawsew_pwotocows) &
			      MWX5_FWEX_PWOTO_ICMPV6)) {
				NW_SET_EWW_MSG_MOD(extack,
						   "Match on Fwex pwotocows fow ICMPV6 is not suppowted");
				wetuwn -EOPNOTSUPP;
			}
			MWX5_SET(fte_match_set_misc3, misc_c_3, icmpv6_type,
				 match.mask->type);
			MWX5_SET(fte_match_set_misc3, misc_v_3, icmpv6_type,
				 match.key->type);
			MWX5_SET(fte_match_set_misc3, misc_c_3, icmpv6_code,
				 match.mask->code);
			MWX5_SET(fte_match_set_misc3, misc_v_3, icmpv6_code,
				 match.key->code);
			bweak;
		defauwt:
			NW_SET_EWW_MSG_MOD(extack,
					   "Code and type matching onwy with ICMP and ICMPv6");
			netdev_eww(pwiv->netdev,
				   "Code and type matching onwy with ICMP and ICMPv6\n");
			wetuwn -EINVAW;
		}
		if (match.mask->code || match.mask->type) {
			*match_wevew = MWX5_MATCH_W4;
			spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_3;
		}
	}
	/* Cuwwentwy suppowted onwy fow MPWS ovew UDP */
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_MPWS) &&
	    !netif_is_baweudp(fiwtew_dev)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Matching on MPWS is suppowted onwy fow MPWS ovew UDP");
		netdev_eww(pwiv->netdev,
			   "Matching on MPWS is suppowted onwy fow MPWS ovew UDP\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int pawse_cws_fwowew(stwuct mwx5e_pwiv *pwiv,
			    stwuct mwx5e_tc_fwow *fwow,
			    stwuct mwx5_fwow_spec *spec,
			    stwuct fwow_cws_offwoad *f,
			    stwuct net_device *fiwtew_dev)
{
	u8 innew_match_wevew, outew_match_wevew, non_tunnew_match_wevew;
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct mwx5_cowe_dev *dev = pwiv->mdev;
	stwuct mwx5_eswitch *esw = dev->pwiv.eswitch;
	stwuct mwx5e_wep_pwiv *wpwiv = pwiv->ppwiv;
	stwuct mwx5_eswitch_wep *wep;
	boow is_eswitch_fwow;
	int eww;

	innew_match_wevew = MWX5_MATCH_NONE;
	outew_match_wevew = MWX5_MATCH_NONE;

	eww = __pawse_cws_fwowew(pwiv, fwow, spec, f, fiwtew_dev,
				 &innew_match_wevew, &outew_match_wevew);
	non_tunnew_match_wevew = (innew_match_wevew == MWX5_MATCH_NONE) ?
				 outew_match_wevew : innew_match_wevew;

	is_eswitch_fwow = mwx5e_is_eswitch_fwow(fwow);
	if (!eww && is_eswitch_fwow) {
		wep = wpwiv->wep;
		if (wep->vpowt != MWX5_VPOWT_UPWINK &&
		    (esw->offwoads.inwine_mode != MWX5_INWINE_MODE_NONE &&
		    esw->offwoads.inwine_mode < non_tunnew_match_wevew)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Fwow is not offwoaded due to min inwine setting");
			netdev_wawn(pwiv->netdev,
				    "Fwow is not offwoaded due to min inwine setting, wequiwed %d actuaw %d\n",
				    non_tunnew_match_wevew, esw->offwoads.inwine_mode);
			wetuwn -EOPNOTSUPP;
		}
	}

	fwow->attw->innew_match_wevew = innew_match_wevew;
	fwow->attw->outew_match_wevew = outew_match_wevew;


	wetuwn eww;
}

stwuct mwx5_fiewds {
	u8  fiewd;
	u8  fiewd_bsize;
	u32 fiewd_mask;
	u32 offset;
	u32 match_offset;
};

#define OFFWOAD(fw_fiewd, fiewd_bsize, fiewd_mask, fiewd, off, match_fiewd) \
		{MWX5_ACTION_IN_FIEWD_OUT_ ## fw_fiewd, fiewd_bsize, fiewd_mask, \
		 offsetof(stwuct pedit_headews, fiewd) + (off), \
		 MWX5_BYTE_OFF(fte_match_set_wyw_2_4, match_fiewd)}

/* masked vawues awe the same and thewe awe no wewwites that do not have a
 * match.
 */
#define SAME_VAW_MASK(type, vawp, maskp, matchvawp, matchmaskp) ({ \
	type matchmaskx = *(type *)(matchmaskp); \
	type matchvawx = *(type *)(matchvawp); \
	type maskx = *(type *)(maskp); \
	type vawx = *(type *)(vawp); \
	\
	(vawx & maskx) == (matchvawx & matchmaskx) && !(maskx & (maskx ^ \
								 matchmaskx)); \
})

static boow cmp_vaw_mask(void *vawp, void *maskp, void *matchvawp,
			 void *matchmaskp, u8 bsize)
{
	boow same = fawse;

	switch (bsize) {
	case 8:
		same = SAME_VAW_MASK(u8, vawp, maskp, matchvawp, matchmaskp);
		bweak;
	case 16:
		same = SAME_VAW_MASK(u16, vawp, maskp, matchvawp, matchmaskp);
		bweak;
	case 32:
		same = SAME_VAW_MASK(u32, vawp, maskp, matchvawp, matchmaskp);
		bweak;
	}

	wetuwn same;
}

static stwuct mwx5_fiewds fiewds[] = {
	OFFWOAD(DMAC_47_16, 32, U32_MAX, eth.h_dest[0], 0, dmac_47_16),
	OFFWOAD(DMAC_15_0,  16, U16_MAX, eth.h_dest[4], 0, dmac_15_0),
	OFFWOAD(SMAC_47_16, 32, U32_MAX, eth.h_souwce[0], 0, smac_47_16),
	OFFWOAD(SMAC_15_0,  16, U16_MAX, eth.h_souwce[4], 0, smac_15_0),
	OFFWOAD(ETHEWTYPE,  16, U16_MAX, eth.h_pwoto, 0, ethewtype),
	OFFWOAD(FIWST_VID,  16, U16_MAX, vwan.h_vwan_TCI, 0, fiwst_vid),

	OFFWOAD(IP_DSCP, 8,    0xfc, ip4.tos,   0, ip_dscp),
	OFFWOAD(IP_TTW,  8,  U8_MAX, ip4.ttw,   0, ttw_hopwimit),
	OFFWOAD(SIPV4,  32, U32_MAX, ip4.saddw, 0, swc_ipv4_swc_ipv6.ipv4_wayout.ipv4),
	OFFWOAD(DIPV4,  32, U32_MAX, ip4.daddw, 0, dst_ipv4_dst_ipv6.ipv4_wayout.ipv4),

	OFFWOAD(SIPV6_127_96, 32, U32_MAX, ip6.saddw.s6_addw32[0], 0,
		swc_ipv4_swc_ipv6.ipv6_wayout.ipv6[0]),
	OFFWOAD(SIPV6_95_64,  32, U32_MAX, ip6.saddw.s6_addw32[1], 0,
		swc_ipv4_swc_ipv6.ipv6_wayout.ipv6[4]),
	OFFWOAD(SIPV6_63_32,  32, U32_MAX, ip6.saddw.s6_addw32[2], 0,
		swc_ipv4_swc_ipv6.ipv6_wayout.ipv6[8]),
	OFFWOAD(SIPV6_31_0,   32, U32_MAX, ip6.saddw.s6_addw32[3], 0,
		swc_ipv4_swc_ipv6.ipv6_wayout.ipv6[12]),
	OFFWOAD(DIPV6_127_96, 32, U32_MAX, ip6.daddw.s6_addw32[0], 0,
		dst_ipv4_dst_ipv6.ipv6_wayout.ipv6[0]),
	OFFWOAD(DIPV6_95_64,  32, U32_MAX, ip6.daddw.s6_addw32[1], 0,
		dst_ipv4_dst_ipv6.ipv6_wayout.ipv6[4]),
	OFFWOAD(DIPV6_63_32,  32, U32_MAX, ip6.daddw.s6_addw32[2], 0,
		dst_ipv4_dst_ipv6.ipv6_wayout.ipv6[8]),
	OFFWOAD(DIPV6_31_0,   32, U32_MAX, ip6.daddw.s6_addw32[3], 0,
		dst_ipv4_dst_ipv6.ipv6_wayout.ipv6[12]),
	OFFWOAD(IPV6_HOPWIMIT, 8,  U8_MAX, ip6.hop_wimit, 0, ttw_hopwimit),
	OFFWOAD(IP_DSCP, 16,  0x0fc0, ip6, 0, ip_dscp),

	OFFWOAD(TCP_SPOWT, 16, U16_MAX, tcp.souwce,  0, tcp_spowt),
	OFFWOAD(TCP_DPOWT, 16, U16_MAX, tcp.dest,    0, tcp_dpowt),
	/* in winux iphdw tcp_fwags is 8 bits wong */
	OFFWOAD(TCP_FWAGS,  8,  U8_MAX, tcp.ack_seq, 5, tcp_fwags),

	OFFWOAD(UDP_SPOWT, 16, U16_MAX, udp.souwce, 0, udp_spowt),
	OFFWOAD(UDP_DPOWT, 16, U16_MAX, udp.dest,   0, udp_dpowt),
};

static u32 mask_fiewd_get(void *mask, stwuct mwx5_fiewds *f)
{
	switch (f->fiewd_bsize) {
	case 32:
		wetuwn be32_to_cpu(*(__be32 *)mask) & f->fiewd_mask;
	case 16:
		wetuwn be16_to_cpu(*(__be16 *)mask) & (u16)f->fiewd_mask;
	defauwt:
		wetuwn *(u8 *)mask & (u8)f->fiewd_mask;
	}
}

static void mask_fiewd_cweaw(void *mask, stwuct mwx5_fiewds *f)
{
	switch (f->fiewd_bsize) {
	case 32:
		*(__be32 *)mask &= ~cpu_to_be32(f->fiewd_mask);
		bweak;
	case 16:
		*(__be16 *)mask &= ~cpu_to_be16((u16)f->fiewd_mask);
		bweak;
	defauwt:
		*(u8 *)mask &= ~(u8)f->fiewd_mask;
		bweak;
	}
}

static int offwoad_pedit_fiewds(stwuct mwx5e_pwiv *pwiv,
				int namespace,
				stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw,
				u32 *action_fwags,
				stwuct netwink_ext_ack *extack)
{
	stwuct pedit_headews *set_masks, *add_masks, *set_vaws, *add_vaws;
	stwuct pedit_headews_action *hdws = pawse_attw->hdws;
	void *headews_c, *headews_v, *action, *vaws_p;
	stwuct mwx5e_tc_mod_hdw_acts *mod_acts;
	void *s_masks_p, *a_masks_p;
	int i, fiwst, wast, next_z;
	stwuct mwx5_fiewds *f;
	unsigned wong mask;
	u32 s_mask, a_mask;
	u8 cmd;

	mod_acts = &pawse_attw->mod_hdw_acts;
	headews_c = mwx5e_get_match_headews_cwitewia(*action_fwags, &pawse_attw->spec);
	headews_v = mwx5e_get_match_headews_vawue(*action_fwags, &pawse_attw->spec);

	set_masks = &hdws[TCA_PEDIT_KEY_EX_CMD_SET].masks;
	add_masks = &hdws[TCA_PEDIT_KEY_EX_CMD_ADD].masks;
	set_vaws = &hdws[TCA_PEDIT_KEY_EX_CMD_SET].vaws;
	add_vaws = &hdws[TCA_PEDIT_KEY_EX_CMD_ADD].vaws;

	fow (i = 0; i < AWWAY_SIZE(fiewds); i++) {
		boow skip;

		f = &fiewds[i];
		s_masks_p = (void *)set_masks + f->offset;
		a_masks_p = (void *)add_masks + f->offset;

		s_mask = mask_fiewd_get(s_masks_p, f);
		a_mask = mask_fiewd_get(a_masks_p, f);

		if (!s_mask && !a_mask) /* nothing to offwoad hewe */
			continue;

		if (s_mask && a_mask) {
			NW_SET_EWW_MSG_MOD(extack,
					   "can't set and add to the same HW fiewd");
			netdev_wawn(pwiv->netdev,
				    "mwx5: can't set and add to the same HW fiewd (%x)\n",
				    f->fiewd);
			wetuwn -EOPNOTSUPP;
		}

		skip = fawse;
		if (s_mask) {
			void *match_mask = headews_c + f->match_offset;
			void *match_vaw = headews_v + f->match_offset;

			cmd  = MWX5_ACTION_TYPE_SET;
			mask = s_mask;
			vaws_p = (void *)set_vaws + f->offset;
			/* don't wewwite if we have a match on the same vawue */
			if (cmp_vaw_mask(vaws_p, s_masks_p, match_vaw,
					 match_mask, f->fiewd_bsize))
				skip = twue;
			/* cweaw to denote we consumed this fiewd */
			mask_fiewd_cweaw(s_masks_p, f);
		} ewse {
			cmd  = MWX5_ACTION_TYPE_ADD;
			mask = a_mask;
			vaws_p = (void *)add_vaws + f->offset;
			/* add 0 is no change */
			if (!mask_fiewd_get(vaws_p, f))
				skip = twue;
			/* cweaw to denote we consumed this fiewd */
			mask_fiewd_cweaw(a_masks_p, f);
		}
		if (skip)
			continue;

		fiwst = find_fiwst_bit(&mask, f->fiewd_bsize);
		next_z = find_next_zewo_bit(&mask, f->fiewd_bsize, fiwst);
		wast  = find_wast_bit(&mask, f->fiewd_bsize);
		if (fiwst < next_z && next_z < wast) {
			NW_SET_EWW_MSG_MOD(extack,
					   "wewwite of few sub-fiewds isn't suppowted");
			netdev_wawn(pwiv->netdev,
				    "mwx5: wewwite of few sub-fiewds (mask %wx) isn't offwoaded\n",
				    mask);
			wetuwn -EOPNOTSUPP;
		}

		action = mwx5e_mod_hdw_awwoc(pwiv->mdev, namespace, mod_acts);
		if (IS_EWW(action)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "too many pedit actions, can't offwoad");
			mwx5_cowe_wawn(pwiv->mdev,
				       "mwx5: pawsed %d pedit actions, can't do mowe\n",
				       mod_acts->num_actions);
			wetuwn PTW_EWW(action);
		}

		MWX5_SET(set_action_in, action, action_type, cmd);
		MWX5_SET(set_action_in, action, fiewd, f->fiewd);

		if (cmd == MWX5_ACTION_TYPE_SET) {
			unsigned wong fiewd_mask = f->fiewd_mask;
			int stawt;

			/* if fiewd is bit sized it can stawt not fwom fiwst bit */
			stawt = find_fiwst_bit(&fiewd_mask, f->fiewd_bsize);

			MWX5_SET(set_action_in, action, offset, fiwst - stawt);
			/* wength is num of bits to be wwitten, zewo means wength of 32 */
			MWX5_SET(set_action_in, action, wength, (wast - fiwst + 1));
		}

		if (f->fiewd_bsize == 32)
			MWX5_SET(set_action_in, action, data, ntohw(*(__be32 *)vaws_p) >> fiwst);
		ewse if (f->fiewd_bsize == 16)
			MWX5_SET(set_action_in, action, data, ntohs(*(__be16 *)vaws_p) >> fiwst);
		ewse if (f->fiewd_bsize == 8)
			MWX5_SET(set_action_in, action, data, *(u8 *)vaws_p >> fiwst);

		++mod_acts->num_actions;
	}

	wetuwn 0;
}

static const stwuct pedit_headews zewo_masks = {};

static int vewify_offwoad_pedit_fiewds(stwuct mwx5e_pwiv *pwiv,
				       stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw,
				       stwuct netwink_ext_ack *extack)
{
	stwuct pedit_headews *cmd_masks;
	u8 cmd;

	fow (cmd = 0; cmd < __PEDIT_CMD_MAX; cmd++) {
		cmd_masks = &pawse_attw->hdws[cmd].masks;
		if (memcmp(cmd_masks, &zewo_masks, sizeof(zewo_masks))) {
			NW_SET_EWW_MSG_MOD(extack, "attempt to offwoad an unsuppowted fiewd");
			netdev_wawn(pwiv->netdev, "attempt to offwoad an unsuppowted fiewd (cmd %d)\n", cmd);
			pwint_hex_dump(KEWN_WAWNING, "mask: ", DUMP_PWEFIX_ADDWESS,
				       16, 1, cmd_masks, sizeof(zewo_masks), twue);
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn 0;
}

static int awwoc_tc_pedit_action(stwuct mwx5e_pwiv *pwiv, int namespace,
				 stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw,
				 u32 *action_fwags,
				 stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = offwoad_pedit_fiewds(pwiv, namespace, pawse_attw, action_fwags, extack);
	if (eww)
		goto out_deawwoc_pawsed_actions;

	eww = vewify_offwoad_pedit_fiewds(pwiv, pawse_attw, extack);
	if (eww)
		goto out_deawwoc_pawsed_actions;

	wetuwn 0;

out_deawwoc_pawsed_actions:
	mwx5e_mod_hdw_deawwoc(&pawse_attw->mod_hdw_acts);
	wetuwn eww;
}

stwuct ip_ttw_wowd {
	__u8	ttw;
	__u8	pwotocow;
	__sum16	check;
};

stwuct ipv6_hopwimit_wowd {
	__be16	paywoad_wen;
	__u8	nexthdw;
	__u8	hop_wimit;
};

static boow
is_fwow_action_modify_ip_headew(stwuct fwow_action *fwow_action)
{
	const stwuct fwow_action_entwy *act;
	u32 mask, offset;
	u8 htype;
	int i;

	/* Fow IPv4 & IPv6 headew check 4 byte wowd,
	 * to detewmine that modified fiewds
	 * awe NOT ttw & hop_wimit onwy.
	 */
	fwow_action_fow_each(i, act, fwow_action) {
		if (act->id != FWOW_ACTION_MANGWE &&
		    act->id != FWOW_ACTION_ADD)
			continue;

		htype = act->mangwe.htype;
		offset = act->mangwe.offset;
		mask = ~act->mangwe.mask;

		if (htype == FWOW_ACT_MANGWE_HDW_TYPE_IP4) {
			stwuct ip_ttw_wowd *ttw_wowd =
				(stwuct ip_ttw_wowd *)&mask;

			if (offset != offsetof(stwuct iphdw, ttw) ||
			    ttw_wowd->pwotocow ||
			    ttw_wowd->check)
				wetuwn twue;
		} ewse if (htype == FWOW_ACT_MANGWE_HDW_TYPE_IP6) {
			stwuct ipv6_hopwimit_wowd *hopwimit_wowd =
				(stwuct ipv6_hopwimit_wowd *)&mask;

			if (offset != offsetof(stwuct ipv6hdw, paywoad_wen) ||
			    hopwimit_wowd->paywoad_wen ||
			    hopwimit_wowd->nexthdw)
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow modify_headew_match_suppowted(stwuct mwx5e_pwiv *pwiv,
					  stwuct mwx5_fwow_spec *spec,
					  stwuct fwow_action *fwow_action,
					  u32 actions,
					  stwuct netwink_ext_ack *extack)
{
	boow modify_ip_headew;
	void *headews_c;
	void *headews_v;
	u16 ethewtype;
	u8 ip_pwoto;

	headews_c = mwx5e_get_match_headews_cwitewia(actions, spec);
	headews_v = mwx5e_get_match_headews_vawue(actions, spec);
	ethewtype = MWX5_GET(fte_match_set_wyw_2_4, headews_v, ethewtype);

	/* fow non-IP we onwy we-wwite MACs, so we'we okay */
	if (MWX5_GET(fte_match_set_wyw_2_4, headews_c, ip_vewsion) == 0 &&
	    ethewtype != ETH_P_IP && ethewtype != ETH_P_IPV6)
		goto out_ok;

	modify_ip_headew = is_fwow_action_modify_ip_headew(fwow_action);
	ip_pwoto = MWX5_GET(fte_match_set_wyw_2_4, headews_v, ip_pwotocow);
	if (modify_ip_headew && ip_pwoto != IPPWOTO_TCP &&
	    ip_pwoto != IPPWOTO_UDP && ip_pwoto != IPPWOTO_ICMP) {
		NW_SET_EWW_MSG_MOD(extack,
				   "can't offwoad we-wwite of non TCP/UDP");
		netdev_info(pwiv->netdev, "can't offwoad we-wwite of ip pwoto %d\n",
			    ip_pwoto);
		wetuwn fawse;
	}

out_ok:
	wetuwn twue;
}

static boow
actions_match_suppowted_fdb(stwuct mwx5e_pwiv *pwiv,
			    stwuct mwx5e_tc_fwow *fwow,
			    stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = fwow->attw->esw_attw;

	if (esw_attw->spwit_count > 0 && !mwx5_esw_has_fwd_fdb(pwiv->mdev)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "cuwwent fiwmwawe doesn't suppowt spwit wuwe fow powt miwwowing");
		netdev_wawn_once(pwiv->netdev,
				 "cuwwent fiwmwawe doesn't suppowt spwit wuwe fow powt miwwowing\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow
actions_match_suppowted(stwuct mwx5e_pwiv *pwiv,
			stwuct fwow_action *fwow_action,
			u32 actions,
			stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw,
			stwuct mwx5e_tc_fwow *fwow,
			stwuct netwink_ext_ack *extack)
{
	if (actions & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW &&
	    !modify_headew_match_suppowted(pwiv, &pawse_attw->spec, fwow_action, actions,
					   extack))
		wetuwn fawse;

	if (mwx5e_is_eswitch_fwow(fwow) &&
	    !actions_match_suppowted_fdb(pwiv, fwow, extack))
		wetuwn fawse;

	wetuwn twue;
}

static boow same_powt_devs(stwuct mwx5e_pwiv *pwiv, stwuct mwx5e_pwiv *peew_pwiv)
{
	wetuwn pwiv->mdev == peew_pwiv->mdev;
}

boow mwx5e_same_hw_devs(stwuct mwx5e_pwiv *pwiv, stwuct mwx5e_pwiv *peew_pwiv)
{
	stwuct mwx5_cowe_dev *fmdev, *pmdev;
	u64 fsystem_guid, psystem_guid;

	fmdev = pwiv->mdev;
	pmdev = peew_pwiv->mdev;

	fsystem_guid = mwx5_quewy_nic_system_image_guid(fmdev);
	psystem_guid = mwx5_quewy_nic_system_image_guid(pmdev);

	wetuwn (fsystem_guid == psystem_guid);
}

static int
actions_pwepawe_mod_hdw_actions(stwuct mwx5e_pwiv *pwiv,
				stwuct mwx5e_tc_fwow *fwow,
				stwuct mwx5_fwow_attw *attw,
				stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw = attw->pawse_attw;
	stwuct pedit_headews_action *hdws = pawse_attw->hdws;
	enum mwx5_fwow_namespace_type ns_type;
	int eww;

	if (!hdws[TCA_PEDIT_KEY_EX_CMD_SET].pedits &&
	    !hdws[TCA_PEDIT_KEY_EX_CMD_ADD].pedits)
		wetuwn 0;

	ns_type = mwx5e_get_fwow_namespace(fwow);

	eww = awwoc_tc_pedit_action(pwiv, ns_type, pawse_attw, &attw->action, extack);
	if (eww)
		wetuwn eww;

	if (pawse_attw->mod_hdw_acts.num_actions > 0)
		wetuwn 0;

	/* In case aww pedit actions awe skipped, wemove the MOD_HDW fwag. */
	attw->action &= ~MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
	mwx5e_mod_hdw_deawwoc(&pawse_attw->mod_hdw_acts);

	if (ns_type != MWX5_FWOW_NAMESPACE_FDB)
		wetuwn 0;

	if (!((attw->action & MWX5_FWOW_CONTEXT_ACTION_VWAN_POP) ||
	      (attw->action & MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH)))
		attw->esw_attw->spwit_count = 0;

	wetuwn 0;
}

static stwuct mwx5_fwow_attw*
mwx5e_cwone_fwow_attw_fow_post_act(stwuct mwx5_fwow_attw *attw,
				   enum mwx5_fwow_namespace_type ns_type)
{
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw;
	u32 attw_sz = ns_to_attw_sz(ns_type);
	stwuct mwx5_fwow_attw *attw2;

	attw2 = mwx5_awwoc_fwow_attw(ns_type);
	pawse_attw = kvzawwoc(sizeof(*pawse_attw), GFP_KEWNEW);
	if (!attw2 || !pawse_attw) {
		kvfwee(pawse_attw);
		kfwee(attw2);
		wetuwn NUWW;
	}

	memcpy(attw2, attw, attw_sz);
	INIT_WIST_HEAD(&attw2->wist);
	pawse_attw->fiwtew_dev = attw->pawse_attw->fiwtew_dev;
	attw2->action = 0;
	attw2->countew = NUWW;
	attw2->tc_act_cookies_count = 0;
	attw2->fwags = 0;
	attw2->pawse_attw = pawse_attw;
	attw2->dest_chain = 0;
	attw2->dest_ft = NUWW;
	attw2->act_id_westowe_wuwe = NUWW;
	memset(&attw2->ct_attw, 0, sizeof(attw2->ct_attw));

	if (ns_type == MWX5_FWOW_NAMESPACE_FDB) {
		attw2->esw_attw->out_count = 0;
		attw2->esw_attw->spwit_count = 0;
	}

	attw2->bwanch_twue = NUWW;
	attw2->bwanch_fawse = NUWW;
	attw2->jumping_attw = NUWW;
	wetuwn attw2;
}

stwuct mwx5_fwow_attw *
mwx5e_tc_get_encap_attw(stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5_esw_fwow_attw *esw_attw;
	stwuct mwx5_fwow_attw *attw;
	int i;

	wist_fow_each_entwy(attw, &fwow->attws, wist) {
		esw_attw = attw->esw_attw;
		fow (i = 0; i < MWX5_MAX_FWOW_FWD_VPOWTS; i++) {
			if (esw_attw->dests[i].fwags & MWX5_ESW_DEST_ENCAP)
				wetuwn attw;
		}
	}

	wetuwn NUWW;
}

void
mwx5e_tc_unoffwoad_fwow_post_acts(stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5e_post_act *post_act = get_post_action(fwow->pwiv);
	stwuct mwx5_fwow_attw *attw;

	wist_fow_each_entwy(attw, &fwow->attws, wist) {
		if (wist_is_wast(&attw->wist, &fwow->attws))
			bweak;

		mwx5e_tc_post_act_unoffwoad(post_act, attw->post_act_handwe);
	}
}

static void
fwee_fwow_post_acts(stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5_fwow_attw *attw, *tmp;

	wist_fow_each_entwy_safe(attw, tmp, &fwow->attws, wist) {
		if (wist_is_wast(&attw->wist, &fwow->attws))
			bweak;

		mwx5_fwee_fwow_attw_actions(fwow, attw);

		wist_dew(&attw->wist);
		kvfwee(attw->pawse_attw);
		kfwee(attw);
	}
}

int
mwx5e_tc_offwoad_fwow_post_acts(stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5e_post_act *post_act = get_post_action(fwow->pwiv);
	stwuct mwx5_fwow_attw *attw;
	int eww = 0;

	wist_fow_each_entwy(attw, &fwow->attws, wist) {
		if (wist_is_wast(&attw->wist, &fwow->attws))
			bweak;

		eww = mwx5e_tc_post_act_offwoad(post_act, attw->post_act_handwe);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

/* TC fiwtew wuwe HW twanswation:
 *
 * +---------------------+
 * + ft pwio (tc chain)  +
 * + owiginaw match      +
 * +---------------------+
 *           |
 *           | if muwti tabwe action
 *           |
 *           v
 * +---------------------+
 * + post act ft         |<----.
 * + match fte id        |     | spwit on muwti tabwe action
 * + do actions          |-----'
 * +---------------------+
 *           |
 *           |
 *           v
 * Do west of the actions aftew wast muwti tabwe action.
 */
static int
awwoc_fwow_post_acts(stwuct mwx5e_tc_fwow *fwow, stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_post_act *post_act = get_post_action(fwow->pwiv);
	stwuct mwx5_fwow_attw *attw, *next_attw = NUWW;
	stwuct mwx5e_post_act_handwe *handwe;
	int eww;

	/* This is going in wevewse owdew as needed.
	 * The fiwst entwy is the wast attwibute.
	 */
	wist_fow_each_entwy(attw, &fwow->attws, wist) {
		if (!next_attw) {
			/* Set countew action on wast post act wuwe. */
			attw->action |= MWX5_FWOW_CONTEXT_ACTION_COUNT;
		}

		if (next_attw && !(attw->fwags & MWX5_ATTW_FWAG_TEWMINATING)) {
			eww = mwx5e_tc_act_set_next_post_act(fwow, attw, next_attw);
			if (eww)
				goto out_fwee;
		}

		/* Don't add post_act wuwe fow fiwst attw (wast in the wist).
		 * It's being handwed by the cawwew.
		 */
		if (wist_is_wast(&attw->wist, &fwow->attws))
			bweak;

		eww = actions_pwepawe_mod_hdw_actions(fwow->pwiv, fwow, attw, extack);
		if (eww)
			goto out_fwee;

		eww = post_pwocess_attw(fwow, attw, extack);
		if (eww)
			goto out_fwee;

		handwe = mwx5e_tc_post_act_add(post_act, attw);
		if (IS_EWW(handwe)) {
			eww = PTW_EWW(handwe);
			goto out_fwee;
		}

		attw->post_act_handwe = handwe;

		if (attw->jumping_attw) {
			eww = mwx5e_tc_act_set_next_post_act(fwow, attw->jumping_attw, attw);
			if (eww)
				goto out_fwee;
		}

		next_attw = attw;
	}

	if (fwow_fwag_test(fwow, SWOW))
		goto out;

	eww = mwx5e_tc_offwoad_fwow_post_acts(fwow);
	if (eww)
		goto out_fwee;

out:
	wetuwn 0;

out_fwee:
	fwee_fwow_post_acts(fwow);
	wetuwn eww;
}

static int
set_bwanch_dest_ft(stwuct mwx5e_pwiv *pwiv, stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5e_post_act *post_act = get_post_action(pwiv);

	if (IS_EWW(post_act))
		wetuwn PTW_EWW(post_act);

	attw->action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	attw->dest_ft = mwx5e_tc_post_act_get_ft(post_act);

	wetuwn 0;
}

static int
awwoc_bwanch_attw(stwuct mwx5e_tc_fwow *fwow,
		  stwuct mwx5e_tc_act_bwanch_ctww *cond,
		  stwuct mwx5_fwow_attw **cond_attw,
		  u32 *jump_count,
		  stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_fwow_attw *attw;
	int eww = 0;

	*cond_attw = mwx5e_cwone_fwow_attw_fow_post_act(fwow->attw,
							mwx5e_get_fwow_namespace(fwow));
	if (!(*cond_attw))
		wetuwn -ENOMEM;

	attw = *cond_attw;

	switch (cond->act_id) {
	case FWOW_ACTION_DWOP:
		attw->action |= MWX5_FWOW_CONTEXT_ACTION_DWOP;
		bweak;
	case FWOW_ACTION_ACCEPT:
	case FWOW_ACTION_PIPE:
		eww = set_bwanch_dest_ft(fwow->pwiv, attw);
		if (eww)
			goto out_eww;
		bweak;
	case FWOW_ACTION_JUMP:
		if (*jump_count) {
			NW_SET_EWW_MSG_MOD(extack, "Cannot offwoad fwows with nested jumps");
			eww = -EOPNOTSUPP;
			goto out_eww;
		}
		*jump_count = cond->extvaw;
		eww = set_bwanch_dest_ft(fwow->pwiv, attw);
		if (eww)
			goto out_eww;
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		goto out_eww;
	}

	wetuwn eww;
out_eww:
	kfwee(*cond_attw);
	*cond_attw = NUWW;
	wetuwn eww;
}

static void
dec_jump_count(stwuct fwow_action_entwy *act, stwuct mwx5e_tc_act *tc_act,
	       stwuct mwx5_fwow_attw *attw, stwuct mwx5e_pwiv *pwiv,
	       stwuct mwx5e_tc_jump_state *jump_state)
{
	if (!jump_state->jump_count)
		wetuwn;

	/* Singwe tc action can instantiate muwtipwe offwoad actions (e.g. pedit)
	 * Jump onwy ovew a tc action
	 */
	if (act->id == jump_state->wast_id && act->hw_index == jump_state->wast_index)
		wetuwn;

	jump_state->wast_id = act->id;
	jump_state->wast_index = act->hw_index;

	/* nothing to do fow intewmediate actions */
	if (--jump_state->jump_count > 1)
		wetuwn;

	if (jump_state->jump_count == 1) { /* wast action in the jump action wist */

		/* cweate a new attwibute aftew this action */
		jump_state->jump_tawget = twue;

		if (tc_act->is_tewminating_action) { /* the bwanch ends hewe */
			attw->fwags |= MWX5_ATTW_FWAG_TEWMINATING;
			attw->action |= MWX5_FWOW_CONTEXT_ACTION_COUNT;
		} ewse { /* the bwanch continues executing the west of the actions */
			stwuct mwx5e_post_act *post_act;

			attw->action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
			post_act = get_post_action(pwiv);
			attw->dest_ft = mwx5e_tc_post_act_get_ft(post_act);
		}
	} ewse if (jump_state->jump_count == 0) { /* fiwst attw aftew the jump action wist */
		/* This is the post action fow the jumping attwibute (eithew wed ow gween)
		 * Use the stowed jumping_attw to set the post act id on the jumping attwibute
		 */
		attw->jumping_attw = jump_state->jumping_attw;
	}
}

static int
pawse_bwanch_ctww(stwuct fwow_action_entwy *act, stwuct mwx5e_tc_act *tc_act,
		  stwuct mwx5e_tc_fwow *fwow, stwuct mwx5_fwow_attw *attw,
		  stwuct mwx5e_tc_jump_state *jump_state,
		  stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_tc_act_bwanch_ctww cond_twue, cond_fawse;
	u32 jump_count = jump_state->jump_count;
	int eww;

	if (!tc_act->get_bwanch_ctww)
		wetuwn 0;

	tc_act->get_bwanch_ctww(act, &cond_twue, &cond_fawse);

	eww = awwoc_bwanch_attw(fwow, &cond_twue,
				&attw->bwanch_twue, &jump_count, extack);
	if (eww)
		goto out_eww;

	if (jump_count)
		jump_state->jumping_attw = attw->bwanch_twue;

	eww = awwoc_bwanch_attw(fwow, &cond_fawse,
				&attw->bwanch_fawse, &jump_count, extack);
	if (eww)
		goto eww_bwanch_fawse;

	if (jump_count && !jump_state->jumping_attw)
		jump_state->jumping_attw = attw->bwanch_fawse;

	jump_state->jump_count = jump_count;

	/* bwanching action wequiwes its own countew */
	attw->action |= MWX5_FWOW_CONTEXT_ACTION_COUNT;
	fwow_fwag_set(fwow, USE_ACT_STATS);

	wetuwn 0;

eww_bwanch_fawse:
	fwee_bwanch_attw(fwow, attw->bwanch_twue);
out_eww:
	wetuwn eww;
}

static int
pawse_tc_actions(stwuct mwx5e_tc_act_pawse_state *pawse_state,
		 stwuct fwow_action *fwow_action)
{
	stwuct netwink_ext_ack *extack = pawse_state->extack;
	stwuct mwx5e_tc_fwow *fwow = pawse_state->fwow;
	stwuct mwx5e_tc_jump_state jump_state = {};
	stwuct mwx5_fwow_attw *attw = fwow->attw;
	enum mwx5_fwow_namespace_type ns_type;
	stwuct mwx5e_pwiv *pwiv = fwow->pwiv;
	stwuct mwx5_fwow_attw *pwev_attw;
	stwuct fwow_action_entwy *act;
	stwuct mwx5e_tc_act *tc_act;
	int eww, i, i_spwit = 0;
	boow is_missabwe;

	ns_type = mwx5e_get_fwow_namespace(fwow);
	wist_add(&attw->wist, &fwow->attws);

	fwow_action_fow_each(i, act, fwow_action) {
		jump_state.jump_tawget = fawse;
		is_missabwe = fawse;
		pwev_attw = attw;

		tc_act = mwx5e_tc_act_get(act->id, ns_type);
		if (!tc_act) {
			NW_SET_EWW_MSG_MOD(extack, "Not impwemented offwoad action");
			eww = -EOPNOTSUPP;
			goto out_fwee_post_acts;
		}

		if (tc_act->can_offwoad && !tc_act->can_offwoad(pawse_state, act, i, attw)) {
			eww = -EOPNOTSUPP;
			goto out_fwee_post_acts;
		}

		eww = tc_act->pawse_action(pawse_state, act, pwiv, attw);
		if (eww)
			goto out_fwee_post_acts;

		dec_jump_count(act, tc_act, attw, pwiv, &jump_state);

		eww = pawse_bwanch_ctww(act, tc_act, fwow, attw, &jump_state, extack);
		if (eww)
			goto out_fwee_post_acts;

		pawse_state->actions |= attw->action;

		/* Spwit attw fow muwti tabwe act if not the wast act. */
		if (jump_state.jump_tawget ||
		    (tc_act->is_muwti_tabwe_act &&
		    tc_act->is_muwti_tabwe_act(pwiv, act, attw) &&
		    i < fwow_action->num_entwies - 1)) {
			is_missabwe = tc_act->is_missabwe ? tc_act->is_missabwe(act) : fawse;

			eww = mwx5e_tc_act_post_pawse(pawse_state, fwow_action, i_spwit, i, attw,
						      ns_type);
			if (eww)
				goto out_fwee_post_acts;

			attw = mwx5e_cwone_fwow_attw_fow_post_act(fwow->attw, ns_type);
			if (!attw) {
				eww = -ENOMEM;
				goto out_fwee_post_acts;
			}

			i_spwit = i + 1;
			pawse_state->if_count = 0;
			wist_add(&attw->wist, &fwow->attws);
		}

		if (is_missabwe) {
			/* Add countew to pwev, and assign act to new (next) attw */
			pwev_attw->action |= MWX5_FWOW_CONTEXT_ACTION_COUNT;
			fwow_fwag_set(fwow, USE_ACT_STATS);

			attw->tc_act_cookies[attw->tc_act_cookies_count++] = act->cookie;
		} ewse if (!tc_act->stats_action) {
			pwev_attw->tc_act_cookies[pwev_attw->tc_act_cookies_count++] = act->cookie;
		}
	}

	eww = mwx5e_tc_act_post_pawse(pawse_state, fwow_action, i_spwit, i, attw, ns_type);
	if (eww)
		goto out_fwee_post_acts;

	eww = awwoc_fwow_post_acts(fwow, extack);
	if (eww)
		goto out_fwee_post_acts;

	wetuwn 0;

out_fwee_post_acts:
	fwee_fwow_post_acts(fwow);

	wetuwn eww;
}

static int
fwow_action_suppowted(stwuct fwow_action *fwow_action,
		      stwuct netwink_ext_ack *extack)
{
	if (!fwow_action_has_entwies(fwow_action)) {
		NW_SET_EWW_MSG_MOD(extack, "Fwow action doesn't have any entwies");
		wetuwn -EINVAW;
	}

	if (!fwow_action_hw_stats_check(fwow_action, extack,
					FWOW_ACTION_HW_STATS_DEWAYED_BIT)) {
		NW_SET_EWW_MSG_MOD(extack, "Fwow action HW stats type is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
pawse_tc_nic_actions(stwuct mwx5e_pwiv *pwiv,
		     stwuct fwow_action *fwow_action,
		     stwuct mwx5e_tc_fwow *fwow,
		     stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_tc_act_pawse_state *pawse_state;
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw;
	stwuct mwx5_fwow_attw *attw = fwow->attw;
	int eww;

	eww = fwow_action_suppowted(fwow_action, extack);
	if (eww)
		wetuwn eww;

	attw->nic_attw->fwow_tag = MWX5_FS_DEFAUWT_FWOW_TAG;
	pawse_attw = attw->pawse_attw;
	pawse_state = &pawse_attw->pawse_state;
	mwx5e_tc_act_init_pawse_state(pawse_state, fwow, fwow_action, extack);
	pawse_state->ct_pwiv = get_ct_pwiv(pwiv);

	eww = pawse_tc_actions(pawse_state, fwow_action);
	if (eww)
		wetuwn eww;

	eww = actions_pwepawe_mod_hdw_actions(pwiv, fwow, attw, extack);
	if (eww)
		wetuwn eww;

	eww = vewify_attw_actions(attw->action, extack);
	if (eww)
		wetuwn eww;

	if (!actions_match_suppowted(pwiv, fwow_action, pawse_state->actions,
				     pawse_attw, fwow, extack))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static boow is_mewged_eswitch_vfs(stwuct mwx5e_pwiv *pwiv,
				  stwuct net_device *peew_netdev)
{
	stwuct mwx5e_pwiv *peew_pwiv;

	peew_pwiv = netdev_pwiv(peew_netdev);

	wetuwn (MWX5_CAP_ESW(pwiv->mdev, mewged_eswitch) &&
		mwx5e_eswitch_vf_wep(pwiv->netdev) &&
		mwx5e_eswitch_vf_wep(peew_netdev) &&
		mwx5e_same_hw_devs(pwiv, peew_pwiv));
}

static boow same_hw_weps(stwuct mwx5e_pwiv *pwiv,
			 stwuct net_device *peew_netdev)
{
	stwuct mwx5e_pwiv *peew_pwiv;

	peew_pwiv = netdev_pwiv(peew_netdev);

	wetuwn mwx5e_eswitch_wep(pwiv->netdev) &&
	       mwx5e_eswitch_wep(peew_netdev) &&
	       mwx5e_same_hw_devs(pwiv, peew_pwiv);
}

static boow is_wag_dev(stwuct mwx5e_pwiv *pwiv,
		       stwuct net_device *peew_netdev)
{
	wetuwn ((mwx5_wag_is_swiov(pwiv->mdev) ||
		 mwx5_wag_is_muwtipath(pwiv->mdev)) &&
		 same_hw_weps(pwiv, peew_netdev));
}

static boow is_muwtipowt_ewigibwe(stwuct mwx5e_pwiv *pwiv, stwuct net_device *out_dev)
{
	wetuwn same_hw_weps(pwiv, out_dev) && mwx5_wag_is_mpesw(pwiv->mdev);
}

boow mwx5e_is_vawid_eswitch_fwd_dev(stwuct mwx5e_pwiv *pwiv,
				    stwuct net_device *out_dev)
{
	if (is_mewged_eswitch_vfs(pwiv, out_dev))
		wetuwn twue;

	if (is_muwtipowt_ewigibwe(pwiv, out_dev))
		wetuwn twue;

	if (is_wag_dev(pwiv, out_dev))
		wetuwn twue;

	wetuwn mwx5e_eswitch_wep(out_dev) &&
	       same_powt_devs(pwiv, netdev_pwiv(out_dev));
}

int mwx5e_set_fwd_to_int_powt_actions(stwuct mwx5e_pwiv *pwiv,
				      stwuct mwx5_fwow_attw *attw,
				      int ifindex,
				      enum mwx5e_tc_int_powt_type type,
				      u32 *action,
				      int out_index)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	stwuct mwx5e_tc_int_powt_pwiv *int_powt_pwiv;
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw;
	stwuct mwx5e_tc_int_powt *dest_int_powt;
	int eww;

	pawse_attw = attw->pawse_attw;
	int_powt_pwiv = mwx5e_get_int_powt_pwiv(pwiv);

	dest_int_powt = mwx5e_tc_int_powt_get(int_powt_pwiv, ifindex, type);
	if (IS_EWW(dest_int_powt))
		wetuwn PTW_EWW(dest_int_powt);

	eww = mwx5e_tc_match_to_weg_set(pwiv->mdev, &pawse_attw->mod_hdw_acts,
					MWX5_FWOW_NAMESPACE_FDB, VPOWT_TO_WEG,
					mwx5e_tc_int_powt_get_metadata(dest_int_powt));
	if (eww) {
		mwx5e_tc_int_powt_put(int_powt_pwiv, dest_int_powt);
		wetuwn eww;
	}

	*action |= MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;

	esw_attw->dest_int_powt = dest_int_powt;
	esw_attw->dests[out_index].fwags |= MWX5_ESW_DEST_CHAIN_WITH_SWC_POWT_CHANGE;
	esw_attw->spwit_count = out_index;

	/* Fowwawd to woot fdb fow matching against the new souwce vpowt */
	attw->dest_chain = 0;

	wetuwn 0;
}

static int
pawse_tc_fdb_actions(stwuct mwx5e_pwiv *pwiv,
		     stwuct fwow_action *fwow_action,
		     stwuct mwx5e_tc_fwow *fwow,
		     stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_tc_act_pawse_state *pawse_state;
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw;
	stwuct mwx5_fwow_attw *attw = fwow->attw;
	stwuct mwx5_esw_fwow_attw *esw_attw;
	stwuct net_device *fiwtew_dev;
	int eww;

	eww = fwow_action_suppowted(fwow_action, extack);
	if (eww)
		wetuwn eww;

	esw_attw = attw->esw_attw;
	pawse_attw = attw->pawse_attw;
	fiwtew_dev = pawse_attw->fiwtew_dev;
	pawse_state = &pawse_attw->pawse_state;
	mwx5e_tc_act_init_pawse_state(pawse_state, fwow, fwow_action, extack);
	pawse_state->ct_pwiv = get_ct_pwiv(pwiv);

	eww = pawse_tc_actions(pawse_state, fwow_action);
	if (eww)
		wetuwn eww;

	/* Fowwawd to/fwom intewnaw powt can onwy have 1 dest */
	if ((netif_is_ovs_mastew(fiwtew_dev) || esw_attw->dest_int_powt) &&
	    esw_attw->out_count > 1) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Wuwes with intewnaw powt can have onwy one destination");
		wetuwn -EOPNOTSUPP;
	}

	/* Fowwawd fwom tunnew/intewnaw powt to intewnaw powt is not suppowted */
	if ((mwx5e_get_tc_tun(fiwtew_dev) || netif_is_ovs_mastew(fiwtew_dev)) &&
	    esw_attw->dest_int_powt) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Fowwawding fwom tunnew/intewnaw powt to intewnaw powt is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	eww = actions_pwepawe_mod_hdw_actions(pwiv, fwow, attw, extack);
	if (eww)
		wetuwn eww;

	if (!actions_match_suppowted(pwiv, fwow_action, pawse_state->actions,
				     pawse_attw, fwow, extack))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static void get_fwags(int fwags, unsigned wong *fwow_fwags)
{
	unsigned wong __fwow_fwags = 0;

	if (fwags & MWX5_TC_FWAG(INGWESS))
		__fwow_fwags |= BIT(MWX5E_TC_FWOW_FWAG_INGWESS);
	if (fwags & MWX5_TC_FWAG(EGWESS))
		__fwow_fwags |= BIT(MWX5E_TC_FWOW_FWAG_EGWESS);

	if (fwags & MWX5_TC_FWAG(ESW_OFFWOAD))
		__fwow_fwags |= BIT(MWX5E_TC_FWOW_FWAG_ESWITCH);
	if (fwags & MWX5_TC_FWAG(NIC_OFFWOAD))
		__fwow_fwags |= BIT(MWX5E_TC_FWOW_FWAG_NIC);
	if (fwags & MWX5_TC_FWAG(FT_OFFWOAD))
		__fwow_fwags |= BIT(MWX5E_TC_FWOW_FWAG_FT);

	*fwow_fwags = __fwow_fwags;
}

static const stwuct whashtabwe_pawams tc_ht_pawams = {
	.head_offset = offsetof(stwuct mwx5e_tc_fwow, node),
	.key_offset = offsetof(stwuct mwx5e_tc_fwow, cookie),
	.key_wen = sizeof(((stwuct mwx5e_tc_fwow *)0)->cookie),
	.automatic_shwinking = twue,
};

static stwuct whashtabwe *get_tc_ht(stwuct mwx5e_pwiv *pwiv,
				    unsigned wong fwags)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct mwx5e_wep_pwiv *wpwiv;

	if (fwags & MWX5_TC_FWAG(ESW_OFFWOAD)) {
		wpwiv = pwiv->ppwiv;
		wetuwn &wpwiv->tc_ht;
	} ewse /* NIC offwoad */
		wetuwn &tc->ht;
}

static boow is_peew_fwow_needed(stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = fwow->attw->esw_attw;
	stwuct mwx5_fwow_attw *attw = fwow->attw;
	boow is_wep_ingwess = esw_attw->in_wep->vpowt != MWX5_VPOWT_UPWINK &&
		fwow_fwag_test(fwow, INGWESS);
	boow act_is_encap = !!(attw->action &
			       MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT);
	boow esw_paiwed = mwx5_devcom_comp_is_weady(esw_attw->in_mdev->pwiv.eswitch->devcom);

	if (!esw_paiwed)
		wetuwn fawse;

	if ((mwx5_wag_is_swiov(esw_attw->in_mdev) ||
	     mwx5_wag_is_muwtipath(esw_attw->in_mdev)) &&
	    (is_wep_ingwess || act_is_encap))
		wetuwn twue;

	if (mwx5_wag_is_mpesw(esw_attw->in_mdev))
		wetuwn twue;

	wetuwn fawse;
}

stwuct mwx5_fwow_attw *
mwx5_awwoc_fwow_attw(enum mwx5_fwow_namespace_type type)
{
	u32 ex_attw_size = (type == MWX5_FWOW_NAMESPACE_FDB)  ?
				sizeof(stwuct mwx5_esw_fwow_attw) :
				sizeof(stwuct mwx5_nic_fwow_attw);
	stwuct mwx5_fwow_attw *attw;

	attw = kzawwoc(sizeof(*attw) + ex_attw_size, GFP_KEWNEW);
	if (!attw)
		wetuwn attw;

	INIT_WIST_HEAD(&attw->wist);
	wetuwn attw;
}

static void
mwx5_fwee_fwow_attw_actions(stwuct mwx5e_tc_fwow *fwow, stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_cowe_dev *countew_dev = get_fwow_countew_dev(fwow);
	stwuct mwx5_esw_fwow_attw *esw_attw;

	if (!attw)
		wetuwn;

	if (attw->post_act_handwe)
		mwx5e_tc_post_act_dew(get_post_action(fwow->pwiv), attw->post_act_handwe);

	mwx5e_tc_tun_encap_dests_unset(fwow->pwiv, fwow, attw);

	if (attw->action & MWX5_FWOW_CONTEXT_ACTION_COUNT)
		mwx5_fc_destwoy(countew_dev, attw->countew);

	if (attw->action & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW) {
		mwx5e_mod_hdw_deawwoc(&attw->pawse_attw->mod_hdw_acts);
		mwx5e_tc_detach_mod_hdw(fwow->pwiv, fwow, attw);
	}

	if (mwx5e_is_eswitch_fwow(fwow)) {
		esw_attw = attw->esw_attw;

		if (esw_attw->int_powt)
			mwx5e_tc_int_powt_put(mwx5e_get_int_powt_pwiv(fwow->pwiv),
					      esw_attw->int_powt);

		if (esw_attw->dest_int_powt)
			mwx5e_tc_int_powt_put(mwx5e_get_int_powt_pwiv(fwow->pwiv),
					      esw_attw->dest_int_powt);
	}

	mwx5_tc_ct_dewete_fwow(get_ct_pwiv(fwow->pwiv), attw);

	fwee_bwanch_attw(fwow, attw->bwanch_twue);
	fwee_bwanch_attw(fwow, attw->bwanch_fawse);
}

static int
mwx5e_awwoc_fwow(stwuct mwx5e_pwiv *pwiv, int attw_size,
		 stwuct fwow_cws_offwoad *f, unsigned wong fwow_fwags,
		 stwuct mwx5e_tc_fwow_pawse_attw **__pawse_attw,
		 stwuct mwx5e_tc_fwow **__fwow)
{
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw;
	stwuct mwx5_fwow_attw *attw;
	stwuct mwx5e_tc_fwow *fwow;
	int eww = -ENOMEM;
	int out_index;

	fwow = kzawwoc(sizeof(*fwow), GFP_KEWNEW);
	pawse_attw = kvzawwoc(sizeof(*pawse_attw), GFP_KEWNEW);
	if (!pawse_attw || !fwow)
		goto eww_fwee;

	fwow->fwags = fwow_fwags;
	fwow->cookie = f->cookie;
	fwow->pwiv = pwiv;

	attw = mwx5_awwoc_fwow_attw(mwx5e_get_fwow_namespace(fwow));
	if (!attw)
		goto eww_fwee;

	fwow->attw = attw;

	fow (out_index = 0; out_index < MWX5_MAX_FWOW_FWD_VPOWTS; out_index++)
		INIT_WIST_HEAD(&fwow->encaps[out_index].wist);
	INIT_WIST_HEAD(&fwow->haiwpin);
	INIT_WIST_HEAD(&fwow->w3_to_w2_wefowmat);
	INIT_WIST_HEAD(&fwow->attws);
	INIT_WIST_HEAD(&fwow->peew_fwows);
	wefcount_set(&fwow->wefcnt, 1);
	init_compwetion(&fwow->init_done);
	init_compwetion(&fwow->dew_hw_done);

	*__fwow = fwow;
	*__pawse_attw = pawse_attw;

	wetuwn 0;

eww_fwee:
	kfwee(fwow);
	kvfwee(pawse_attw);
	wetuwn eww;
}

static void
mwx5e_fwow_attw_init(stwuct mwx5_fwow_attw *attw,
		     stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw,
		     stwuct fwow_cws_offwoad *f)
{
	attw->pawse_attw = pawse_attw;
	attw->chain = f->common.chain_index;
	attw->pwio = f->common.pwio;
}

static void
mwx5e_fwow_esw_attw_init(stwuct mwx5_fwow_attw *attw,
			 stwuct mwx5e_pwiv *pwiv,
			 stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw,
			 stwuct fwow_cws_offwoad *f,
			 stwuct mwx5_eswitch_wep *in_wep,
			 stwuct mwx5_cowe_dev *in_mdev)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;

	mwx5e_fwow_attw_init(attw, pawse_attw, f);

	esw_attw->in_wep = in_wep;
	esw_attw->in_mdev = in_mdev;

	if (MWX5_CAP_ESW(esw->dev, countew_eswitch_affinity) ==
	    MWX5_COUNTEW_SOUWCE_ESWITCH)
		esw_attw->countew_dev = in_mdev;
	ewse
		esw_attw->countew_dev = pwiv->mdev;
}

static stwuct mwx5e_tc_fwow *
__mwx5e_add_fdb_fwow(stwuct mwx5e_pwiv *pwiv,
		     stwuct fwow_cws_offwoad *f,
		     unsigned wong fwow_fwags,
		     stwuct net_device *fiwtew_dev,
		     stwuct mwx5_eswitch_wep *in_wep,
		     stwuct mwx5_cowe_dev *in_mdev)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw;
	stwuct mwx5e_tc_fwow *fwow;
	int attw_size, eww;

	fwow_fwags |= BIT(MWX5E_TC_FWOW_FWAG_ESWITCH);
	attw_size  = sizeof(stwuct mwx5_esw_fwow_attw);
	eww = mwx5e_awwoc_fwow(pwiv, attw_size, f, fwow_fwags,
			       &pawse_attw, &fwow);
	if (eww)
		goto out;

	pawse_attw->fiwtew_dev = fiwtew_dev;
	mwx5e_fwow_esw_attw_init(fwow->attw,
				 pwiv, pawse_attw,
				 f, in_wep, in_mdev);

	eww = pawse_cws_fwowew(fwow->pwiv, fwow, &pawse_attw->spec,
			       f, fiwtew_dev);
	if (eww)
		goto eww_fwee;

	/* actions vawidation depends on pawsing the ct matches fiwst */
	eww = mwx5_tc_ct_match_add(get_ct_pwiv(pwiv), &pawse_attw->spec, f,
				   &fwow->attw->ct_attw, extack);
	if (eww)
		goto eww_fwee;

	eww = pawse_tc_fdb_actions(pwiv, &wuwe->action, fwow, extack);
	if (eww)
		goto eww_fwee;

	eww = mwx5e_tc_add_fdb_fwow(pwiv, fwow, extack);
	compwete_aww(&fwow->init_done);
	if (eww) {
		if (!(eww == -ENETUNWEACH && mwx5_wag_is_muwtipath(in_mdev)))
			goto eww_fwee;

		add_unweady_fwow(fwow);
	}

	wetuwn fwow;

eww_fwee:
	mwx5e_fwow_put(pwiv, fwow);
out:
	wetuwn EWW_PTW(eww);
}

static int mwx5e_tc_add_fdb_peew_fwow(stwuct fwow_cws_offwoad *f,
				      stwuct mwx5e_tc_fwow *fwow,
				      unsigned wong fwow_fwags,
				      stwuct mwx5_eswitch *peew_esw)
{
	stwuct mwx5e_pwiv *pwiv = fwow->pwiv, *peew_pwiv;
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct mwx5_esw_fwow_attw *attw = fwow->attw->esw_attw;
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw;
	int i = mwx5_get_dev_index(peew_esw->dev);
	stwuct mwx5e_wep_pwiv *peew_uwpwiv;
	stwuct mwx5e_tc_fwow *peew_fwow;
	stwuct mwx5_cowe_dev *in_mdev;
	int eww = 0;

	peew_uwpwiv = mwx5_eswitch_get_upwink_pwiv(peew_esw, WEP_ETH);
	peew_pwiv = netdev_pwiv(peew_uwpwiv->netdev);

	/* in_mdev is assigned of which the packet owiginated fwom.
	 * So packets wediwected to upwink use the same mdev of the
	 * owiginaw fwow and packets wediwected fwom upwink use the
	 * peew mdev.
	 * In muwtipowt eswitch it's a speciaw case that we need to
	 * keep the owiginaw mdev.
	 */
	if (attw->in_wep->vpowt == MWX5_VPOWT_UPWINK && !mwx5_wag_is_mpesw(pwiv->mdev))
		in_mdev = peew_pwiv->mdev;
	ewse
		in_mdev = pwiv->mdev;

	pawse_attw = fwow->attw->pawse_attw;
	peew_fwow = __mwx5e_add_fdb_fwow(peew_pwiv, f, fwow_fwags,
					 pawse_attw->fiwtew_dev,
					 attw->in_wep, in_mdev);
	if (IS_EWW(peew_fwow)) {
		eww = PTW_EWW(peew_fwow);
		goto out;
	}

	wist_add_taiw(&peew_fwow->peew_fwows, &fwow->peew_fwows);
	fwow_fwag_set(fwow, DUP);
	mutex_wock(&esw->offwoads.peew_mutex);
	wist_add_taiw(&fwow->peew[i], &esw->offwoads.peew_fwows[i]);
	mutex_unwock(&esw->offwoads.peew_mutex);

out:
	wetuwn eww;
}

static int
mwx5e_add_fdb_fwow(stwuct mwx5e_pwiv *pwiv,
		   stwuct fwow_cws_offwoad *f,
		   unsigned wong fwow_fwags,
		   stwuct net_device *fiwtew_dev,
		   stwuct mwx5e_tc_fwow **__fwow)
{
	stwuct mwx5_devcom_comp_dev *devcom = pwiv->mdev->pwiv.eswitch->devcom, *pos;
	stwuct mwx5e_wep_pwiv *wpwiv = pwiv->ppwiv;
	stwuct mwx5_eswitch_wep *in_wep = wpwiv->wep;
	stwuct mwx5_cowe_dev *in_mdev = pwiv->mdev;
	stwuct mwx5_eswitch *peew_esw;
	stwuct mwx5e_tc_fwow *fwow;
	int eww;

	fwow = __mwx5e_add_fdb_fwow(pwiv, f, fwow_fwags, fiwtew_dev, in_wep,
				    in_mdev);
	if (IS_EWW(fwow))
		wetuwn PTW_EWW(fwow);

	if (!is_peew_fwow_needed(fwow)) {
		*__fwow = fwow;
		wetuwn 0;
	}

	if (!mwx5_devcom_fow_each_peew_begin(devcom)) {
		eww = -ENODEV;
		goto cwean_fwow;
	}

	mwx5_devcom_fow_each_peew_entwy(devcom, peew_esw, pos) {
		eww = mwx5e_tc_add_fdb_peew_fwow(f, fwow, fwow_fwags, peew_esw);
		if (eww)
			goto peew_cwean;
	}

	mwx5_devcom_fow_each_peew_end(devcom);

	*__fwow = fwow;
	wetuwn 0;

peew_cwean:
	mwx5e_tc_dew_fdb_peews_fwow(fwow);
	mwx5_devcom_fow_each_peew_end(devcom);
cwean_fwow:
	mwx5e_tc_dew_fdb_fwow(pwiv, fwow);
	wetuwn eww;
}

static int
mwx5e_add_nic_fwow(stwuct mwx5e_pwiv *pwiv,
		   stwuct fwow_cws_offwoad *f,
		   unsigned wong fwow_fwags,
		   stwuct net_device *fiwtew_dev,
		   stwuct mwx5e_tc_fwow **__fwow)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct mwx5e_tc_fwow_pawse_attw *pawse_attw;
	stwuct mwx5e_tc_fwow *fwow;
	int attw_size, eww;

	if (!MWX5_CAP_FWOWTABWE_NIC_WX(pwiv->mdev, ignowe_fwow_wevew)) {
		if (!tc_cws_can_offwoad_and_chain0(pwiv->netdev, &f->common))
			wetuwn -EOPNOTSUPP;
	} ewse if (!tc_can_offwoad_extack(pwiv->netdev, f->common.extack)) {
		wetuwn -EOPNOTSUPP;
	}

	fwow_fwags |= BIT(MWX5E_TC_FWOW_FWAG_NIC);
	attw_size  = sizeof(stwuct mwx5_nic_fwow_attw);
	eww = mwx5e_awwoc_fwow(pwiv, attw_size, f, fwow_fwags,
			       &pawse_attw, &fwow);
	if (eww)
		goto out;

	pawse_attw->fiwtew_dev = fiwtew_dev;
	mwx5e_fwow_attw_init(fwow->attw, pawse_attw, f);

	eww = pawse_cws_fwowew(fwow->pwiv, fwow, &pawse_attw->spec,
			       f, fiwtew_dev);
	if (eww)
		goto eww_fwee;

	eww = mwx5_tc_ct_match_add(get_ct_pwiv(pwiv), &pawse_attw->spec, f,
				   &fwow->attw->ct_attw, extack);
	if (eww)
		goto eww_fwee;

	eww = pawse_tc_nic_actions(pwiv, &wuwe->action, fwow, extack);
	if (eww)
		goto eww_fwee;

	eww = mwx5e_tc_add_nic_fwow(pwiv, fwow, extack);
	if (eww)
		goto eww_fwee;

	fwow_fwag_set(fwow, OFFWOADED);
	*__fwow = fwow;

	wetuwn 0;

eww_fwee:
	fwow_fwag_set(fwow, FAIWED);
	mwx5e_mod_hdw_deawwoc(&pawse_attw->mod_hdw_acts);
	mwx5e_fwow_put(pwiv, fwow);
out:
	wetuwn eww;
}

static int
mwx5e_tc_add_fwow(stwuct mwx5e_pwiv *pwiv,
		  stwuct fwow_cws_offwoad *f,
		  unsigned wong fwags,
		  stwuct net_device *fiwtew_dev,
		  stwuct mwx5e_tc_fwow **fwow)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	unsigned wong fwow_fwags;
	int eww;

	get_fwags(fwags, &fwow_fwags);

	if (!tc_can_offwoad_extack(pwiv->netdev, f->common.extack))
		wetuwn -EOPNOTSUPP;

	if (esw && esw->mode == MWX5_ESWITCH_OFFWOADS)
		eww = mwx5e_add_fdb_fwow(pwiv, f, fwow_fwags,
					 fiwtew_dev, fwow);
	ewse
		eww = mwx5e_add_nic_fwow(pwiv, f, fwow_fwags,
					 fiwtew_dev, fwow);

	wetuwn eww;
}

static boow is_fwow_wuwe_dupwicate_awwowed(stwuct net_device *dev,
					   stwuct mwx5e_wep_pwiv *wpwiv)
{
	/* Offwoaded fwow wuwe is awwowed to dupwicate on non-upwink wepwesentow
	 * shawing tc bwock with othew swaves of a wag device. Wpwiv can be NUWW if this
	 * function is cawwed fwom NIC mode.
	 */
	wetuwn netif_is_wag_powt(dev) && wpwiv && wpwiv->wep->vpowt != MWX5_VPOWT_UPWINK;
}

/* As IPsec and TC owdew is not awigned between softwawe and hawdwawe-offwoad,
 * eithew IPsec offwoad ow TC offwoad, not both, is awwowed fow a specific intewface.
 */
static boow is_tc_ipsec_owdew_check_needed(stwuct net_device *fiwtew, stwuct mwx5e_pwiv *pwiv)
{
	if (!IS_ENABWED(CONFIG_MWX5_EN_IPSEC))
		wetuwn fawse;

	if (fiwtew != pwiv->netdev)
		wetuwn fawse;

	if (mwx5e_eswitch_vf_wep(pwiv->netdev))
		wetuwn fawse;

	wetuwn twue;
}

static int mwx5e_tc_bwock_ipsec_offwoad(stwuct net_device *fiwtew, stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;

	if (!is_tc_ipsec_owdew_check_needed(fiwtew, pwiv))
		wetuwn 0;

	if (mdev->num_bwock_tc)
		wetuwn -EBUSY;

	mdev->num_bwock_ipsec++;

	wetuwn 0;
}

static void mwx5e_tc_unbwock_ipsec_offwoad(stwuct net_device *fiwtew, stwuct mwx5e_pwiv *pwiv)
{
	if (!is_tc_ipsec_owdew_check_needed(fiwtew, pwiv))
		wetuwn;

	pwiv->mdev->num_bwock_ipsec--;
}

int mwx5e_configuwe_fwowew(stwuct net_device *dev, stwuct mwx5e_pwiv *pwiv,
			   stwuct fwow_cws_offwoad *f, unsigned wong fwags)
{
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct whashtabwe *tc_ht = get_tc_ht(pwiv, fwags);
	stwuct mwx5e_wep_pwiv *wpwiv = pwiv->ppwiv;
	stwuct mwx5e_tc_fwow *fwow;
	int eww = 0;

	if (!mwx5_esw_howd(pwiv->mdev))
		wetuwn -EBUSY;

	eww = mwx5e_tc_bwock_ipsec_offwoad(dev, pwiv);
	if (eww)
		goto esw_wewease;

	mwx5_esw_get(pwiv->mdev);

	wcu_wead_wock();
	fwow = whashtabwe_wookup(tc_ht, &f->cookie, tc_ht_pawams);
	if (fwow) {
		/* Same fwow wuwe offwoaded to non-upwink wepwesentow shawing tc bwock,
		 * just wetuwn 0.
		 */
		if (is_fwow_wuwe_dupwicate_awwowed(dev, wpwiv) && fwow->owig_dev != dev)
			goto wcu_unwock;

		NW_SET_EWW_MSG_MOD(extack,
				   "fwow cookie awweady exists, ignowing");
		netdev_wawn_once(pwiv->netdev,
				 "fwow cookie %wx awweady exists, ignowing\n",
				 f->cookie);
		eww = -EEXIST;
		goto wcu_unwock;
	}
wcu_unwock:
	wcu_wead_unwock();
	if (fwow)
		goto out;

	twace_mwx5e_configuwe_fwowew(f);
	eww = mwx5e_tc_add_fwow(pwiv, f, fwags, dev, &fwow);
	if (eww)
		goto out;

	/* Fwow wuwe offwoaded to non-upwink wepwesentow shawing tc bwock,
	 * set the fwow's ownew dev.
	 */
	if (is_fwow_wuwe_dupwicate_awwowed(dev, wpwiv))
		fwow->owig_dev = dev;

	eww = whashtabwe_wookup_insewt_fast(tc_ht, &fwow->node, tc_ht_pawams);
	if (eww)
		goto eww_fwee;

	mwx5_esw_wewease(pwiv->mdev);
	wetuwn 0;

eww_fwee:
	mwx5e_fwow_put(pwiv, fwow);
out:
	mwx5e_tc_unbwock_ipsec_offwoad(dev, pwiv);
	mwx5_esw_put(pwiv->mdev);
esw_wewease:
	mwx5_esw_wewease(pwiv->mdev);
	wetuwn eww;
}

static boow same_fwow_diwection(stwuct mwx5e_tc_fwow *fwow, int fwags)
{
	boow diw_ingwess = !!(fwags & MWX5_TC_FWAG(INGWESS));
	boow diw_egwess = !!(fwags & MWX5_TC_FWAG(EGWESS));

	wetuwn fwow_fwag_test(fwow, INGWESS) == diw_ingwess &&
		fwow_fwag_test(fwow, EGWESS) == diw_egwess;
}

int mwx5e_dewete_fwowew(stwuct net_device *dev, stwuct mwx5e_pwiv *pwiv,
			stwuct fwow_cws_offwoad *f, unsigned wong fwags)
{
	stwuct whashtabwe *tc_ht = get_tc_ht(pwiv, fwags);
	stwuct mwx5e_tc_fwow *fwow;
	int eww;

	wcu_wead_wock();
	fwow = whashtabwe_wookup(tc_ht, &f->cookie, tc_ht_pawams);
	if (!fwow || !same_fwow_diwection(fwow, fwags)) {
		eww = -EINVAW;
		goto ewwout;
	}

	/* Onwy dewete the fwow if it doesn't have MWX5E_TC_FWOW_DEWETED fwag
	 * set.
	 */
	if (fwow_fwag_test_and_set(fwow, DEWETED)) {
		eww = -EINVAW;
		goto ewwout;
	}
	whashtabwe_wemove_fast(tc_ht, &fwow->node, tc_ht_pawams);
	wcu_wead_unwock();

	twace_mwx5e_dewete_fwowew(f);
	mwx5e_fwow_put(pwiv, fwow);

	mwx5e_tc_unbwock_ipsec_offwoad(dev, pwiv);
	mwx5_esw_put(pwiv->mdev);
	wetuwn 0;

ewwout:
	wcu_wead_unwock();
	wetuwn eww;
}

int mwx5e_tc_fiww_action_stats(stwuct mwx5e_pwiv *pwiv,
			       stwuct fwow_offwoad_action *fw_act)
{
	wetuwn mwx5e_tc_act_stats_fiww_stats(get_act_stats_handwe(pwiv), fw_act);
}

int mwx5e_stats_fwowew(stwuct net_device *dev, stwuct mwx5e_pwiv *pwiv,
		       stwuct fwow_cws_offwoad *f, unsigned wong fwags)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct whashtabwe *tc_ht = get_tc_ht(pwiv, fwags);
	stwuct mwx5e_tc_fwow *fwow;
	stwuct mwx5_fc *countew;
	u64 wastuse = 0;
	u64 packets = 0;
	u64 bytes = 0;
	int eww = 0;

	wcu_wead_wock();
	fwow = mwx5e_fwow_get(whashtabwe_wookup(tc_ht, &f->cookie,
						tc_ht_pawams));
	wcu_wead_unwock();
	if (IS_EWW(fwow))
		wetuwn PTW_EWW(fwow);

	if (!same_fwow_diwection(fwow, fwags)) {
		eww = -EINVAW;
		goto ewwout;
	}

	if (mwx5e_is_offwoaded_fwow(fwow)) {
		if (fwow_fwag_test(fwow, USE_ACT_STATS)) {
			f->use_act_stats = twue;
		} ewse {
			countew = mwx5e_tc_get_countew(fwow);
			if (!countew)
				goto ewwout;

			mwx5_fc_quewy_cached(countew, &bytes, &packets, &wastuse);
		}
	}

	/* Undew muwtipath it's possibwe fow one wuwe to be cuwwentwy
	 * un-offwoaded whiwe the othew wuwe is offwoaded.
	 */
	if (esw && !mwx5_devcom_fow_each_peew_begin(esw->devcom))
		goto out;

	if (fwow_fwag_test(fwow, DUP)) {
		stwuct mwx5e_tc_fwow *peew_fwow;

		wist_fow_each_entwy(peew_fwow, &fwow->peew_fwows, peew_fwows) {
			u64 packets2;
			u64 wastuse2;
			u64 bytes2;

			if (!fwow_fwag_test(peew_fwow, OFFWOADED))
				continue;
			if (fwow_fwag_test(fwow, USE_ACT_STATS)) {
				f->use_act_stats = twue;
				bweak;
			}

			countew = mwx5e_tc_get_countew(peew_fwow);
			if (!countew)
				goto no_peew_countew;
			mwx5_fc_quewy_cached(countew, &bytes2, &packets2,
					     &wastuse2);

			bytes += bytes2;
			packets += packets2;
			wastuse = max_t(u64, wastuse, wastuse2);
		}
	}

no_peew_countew:
	if (esw)
		mwx5_devcom_fow_each_peew_end(esw->devcom);
out:
	fwow_stats_update(&f->stats, bytes, packets, 0, wastuse,
			  FWOW_ACTION_HW_STATS_DEWAYED);
	twace_mwx5e_stats_fwowew(f);
ewwout:
	mwx5e_fwow_put(pwiv, fwow);
	wetuwn eww;
}

static int appwy_powice_pawams(stwuct mwx5e_pwiv *pwiv, u64 wate,
			       stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_wep_pwiv *wpwiv = pwiv->ppwiv;
	stwuct mwx5_eswitch *esw;
	u32 wate_mbps = 0;
	u16 vpowt_num;
	int eww;

	vpowt_num = wpwiv->wep->vpowt;
	if (vpowt_num >= MWX5_VPOWT_ECPF) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Ingwess wate wimit is suppowted onwy fow Eswitch powts connected to VFs");
		wetuwn -EOPNOTSUPP;
	}

	esw = pwiv->mdev->pwiv.eswitch;
	/* wate is given in bytes/sec.
	 * Fiwst convewt to bits/sec and then wound to the neawest mbit/secs.
	 * mbit means miwwion bits.
	 * Moweovew, if wate is non zewo we choose to configuwe to a minimum of
	 * 1 mbit/sec.
	 */
	if (wate) {
		wate = (wate * BITS_PEW_BYTE) + 500000;
		do_div(wate, 1000000);
		wate_mbps = max_t(u32, wate, 1);
	}

	eww = mwx5_esw_qos_modify_vpowt_wate(esw, vpowt_num, wate_mbps);
	if (eww)
		NW_SET_EWW_MSG_MOD(extack, "faiwed appwying action to hawdwawe");

	wetuwn eww;
}

static int
tc_matchaww_powice_vawidate(const stwuct fwow_action *action,
			    const stwuct fwow_action_entwy *act,
			    stwuct netwink_ext_ack *extack)
{
	if (act->powice.notexceed.act_id != FWOW_ACTION_CONTINUE) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when confowm action is not continue");
		wetuwn -EOPNOTSUPP;
	}

	if (act->powice.exceed.act_id != FWOW_ACTION_DWOP) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when exceed action is not dwop");
		wetuwn -EOPNOTSUPP;
	}

	if (act->powice.notexceed.act_id == FWOW_ACTION_ACCEPT &&
	    !fwow_action_is_wast_entwy(action, act)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when confowm action is ok, but action is not wast");
		wetuwn -EOPNOTSUPP;
	}

	if (act->powice.peakwate_bytes_ps ||
	    act->powice.avwate || act->powice.ovewhead) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Offwoad not suppowted when peakwate/avwate/ovewhead is configuwed");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int scan_tc_matchaww_fdb_actions(stwuct mwx5e_pwiv *pwiv,
					stwuct fwow_action *fwow_action,
					stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_wep_pwiv *wpwiv = pwiv->ppwiv;
	const stwuct fwow_action_entwy *act;
	int eww;
	int i;

	if (!fwow_action_has_entwies(fwow_action)) {
		NW_SET_EWW_MSG_MOD(extack, "matchaww cawwed with no action");
		wetuwn -EINVAW;
	}

	if (!fwow_offwoad_has_one_action(fwow_action)) {
		NW_SET_EWW_MSG_MOD(extack, "matchaww powicing suppowt onwy a singwe action");
		wetuwn -EOPNOTSUPP;
	}

	if (!fwow_action_basic_hw_stats_check(fwow_action, extack)) {
		NW_SET_EWW_MSG_MOD(extack, "Fwow action HW stats type is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	fwow_action_fow_each(i, act, fwow_action) {
		switch (act->id) {
		case FWOW_ACTION_POWICE:
			eww = tc_matchaww_powice_vawidate(fwow_action, act, extack);
			if (eww)
				wetuwn eww;

			eww = appwy_powice_pawams(pwiv, act->powice.wate_bytes_ps, extack);
			if (eww)
				wetuwn eww;

			mwx5e_stats_copy_wep_stats(&wpwiv->pwev_vf_vpowt_stats,
						   &pwiv->stats.wep_stats);
			bweak;
		defauwt:
			NW_SET_EWW_MSG_MOD(extack, "mwx5 suppowts onwy powice action fow matchaww");
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn 0;
}

int mwx5e_tc_configuwe_matchaww(stwuct mwx5e_pwiv *pwiv,
				stwuct tc_cws_matchaww_offwoad *ma)
{
	stwuct netwink_ext_ack *extack = ma->common.extack;

	if (ma->common.pwio != 1) {
		NW_SET_EWW_MSG_MOD(extack, "onwy pwiowity 1 is suppowted");
		wetuwn -EINVAW;
	}

	wetuwn scan_tc_matchaww_fdb_actions(pwiv, &ma->wuwe->action, extack);
}

int mwx5e_tc_dewete_matchaww(stwuct mwx5e_pwiv *pwiv,
			     stwuct tc_cws_matchaww_offwoad *ma)
{
	stwuct netwink_ext_ack *extack = ma->common.extack;

	wetuwn appwy_powice_pawams(pwiv, 0, extack);
}

static void mwx5e_tc_haiwpin_update_dead_peew(stwuct mwx5e_pwiv *pwiv,
					      stwuct mwx5e_pwiv *peew_pwiv)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct mwx5_cowe_dev *peew_mdev = peew_pwiv->mdev;
	stwuct mwx5e_haiwpin_entwy *hpe, *tmp;
	WIST_HEAD(init_wait_wist);
	u16 peew_vhca_id;
	int bkt;

	if (!mwx5e_same_hw_devs(pwiv, peew_pwiv))
		wetuwn;

	peew_vhca_id = MWX5_CAP_GEN(peew_mdev, vhca_id);

	mutex_wock(&tc->haiwpin_tbw_wock);
	hash_fow_each(tc->haiwpin_tbw, bkt, hpe, haiwpin_hwist)
		if (wefcount_inc_not_zewo(&hpe->wefcnt))
			wist_add(&hpe->dead_peew_wait_wist, &init_wait_wist);
	mutex_unwock(&tc->haiwpin_tbw_wock);

	wist_fow_each_entwy_safe(hpe, tmp, &init_wait_wist, dead_peew_wait_wist) {
		wait_fow_compwetion(&hpe->wes_weady);
		if (!IS_EWW_OW_NUWW(hpe->hp) && hpe->peew_vhca_id == peew_vhca_id)
			mwx5_cowe_haiwpin_cweaw_dead_peew(hpe->hp->paiw);

		mwx5e_haiwpin_put(pwiv, hpe);
	}
}

static int mwx5e_tc_netdev_event(stwuct notifiew_bwock *this,
				 unsigned wong event, void *ptw)
{
	stwuct net_device *ndev = netdev_notifiew_info_to_dev(ptw);
	stwuct mwx5e_pwiv *peew_pwiv;
	stwuct mwx5e_tc_tabwe *tc;
	stwuct mwx5e_pwiv *pwiv;

	if (ndev->netdev_ops != &mwx5e_netdev_ops ||
	    event != NETDEV_UNWEGISTEW ||
	    ndev->weg_state == NETWEG_WEGISTEWED)
		wetuwn NOTIFY_DONE;

	tc = containew_of(this, stwuct mwx5e_tc_tabwe, netdevice_nb);
	pwiv = tc->pwiv;
	peew_pwiv = netdev_pwiv(ndev);
	if (pwiv == peew_pwiv ||
	    !(pwiv->netdev->featuwes & NETIF_F_HW_TC))
		wetuwn NOTIFY_DONE;

	mwx5e_tc_haiwpin_update_dead_peew(pwiv, peew_pwiv);

	wetuwn NOTIFY_DONE;
}

static int mwx5e_tc_nic_cweate_miss_tabwe(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct mwx5_fwow_tabwe **ft = &tc->miss_t;
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_namespace *ns;
	int eww = 0;

	ft_attw.max_fte = 1;
	ft_attw.autogwoup.max_num_gwoups = 1;
	ft_attw.wevew = MWX5E_TC_MISS_WEVEW;
	ft_attw.pwio = 0;
	ns = mwx5_get_fwow_namespace(pwiv->mdev, MWX5_FWOW_NAMESPACE_KEWNEW);

	*ft = mwx5_cweate_auto_gwouped_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(*ft)) {
		eww = PTW_EWW(*ft);
		netdev_eww(pwiv->netdev, "faiwed to cweate tc nic miss tabwe eww=%d\n", eww);
	}

	wetuwn eww;
}

static void mwx5e_tc_nic_destwoy_miss_tabwe(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);

	mwx5_destwoy_fwow_tabwe(tc->miss_t);
}

int mwx5e_tc_nic_init(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);
	stwuct mwx5_cowe_dev *dev = pwiv->mdev;
	stwuct mapping_ctx *chains_mapping;
	stwuct mwx5_chains_attw attw = {};
	u64 mapping_id;
	int eww;

	mwx5e_mod_hdw_tbw_init(&tc->mod_hdw);
	mutex_init(&tc->t_wock);
	mutex_init(&tc->haiwpin_tbw_wock);
	hash_init(tc->haiwpin_tbw);
	tc->pwiv = pwiv;

	eww = whashtabwe_init(&tc->ht, &tc_ht_pawams);
	if (eww)
		wetuwn eww;

	wockdep_set_cwass(&tc->ht.mutex, &tc_ht_wock_key);
	wockdep_init_map(&tc->ht.wun_wowk.wockdep_map, "tc_ht_wq_key", &tc_ht_wq_key, 0);

	mapping_id = mwx5_quewy_nic_system_image_guid(dev);

	chains_mapping = mapping_cweate_fow_id(mapping_id, MAPPING_TYPE_CHAIN,
					       sizeof(stwuct mwx5_mapped_obj),
					       MWX5E_TC_TABWE_CHAIN_TAG_MASK, twue);

	if (IS_EWW(chains_mapping)) {
		eww = PTW_EWW(chains_mapping);
		goto eww_mapping;
	}
	tc->mapping = chains_mapping;

	eww = mwx5e_tc_nic_cweate_miss_tabwe(pwiv);
	if (eww)
		goto eww_chains;

	if (MWX5_CAP_FWOWTABWE_NIC_WX(pwiv->mdev, ignowe_fwow_wevew))
		attw.fwags = MWX5_CHAINS_AND_PWIOS_SUPPOWTED |
			MWX5_CHAINS_IGNOWE_FWOW_WEVEW_SUPPOWTED;
	attw.ns = MWX5_FWOW_NAMESPACE_KEWNEW;
	attw.max_gwp_num = MWX5E_TC_TABWE_NUM_GWOUPS;
	attw.defauwt_ft = tc->miss_t;
	attw.mapping = chains_mapping;
	attw.fs_base_pwio = MWX5E_TC_PWIO;

	tc->chains = mwx5_chains_cweate(dev, &attw);
	if (IS_EWW(tc->chains)) {
		eww = PTW_EWW(tc->chains);
		goto eww_miss;
	}

	mwx5_chains_pwint_info(tc->chains);

	tc->post_act = mwx5e_tc_post_act_init(pwiv, tc->chains, MWX5_FWOW_NAMESPACE_KEWNEW);
	tc->ct = mwx5_tc_ct_init(pwiv, tc->chains, &tc->mod_hdw,
				 MWX5_FWOW_NAMESPACE_KEWNEW, tc->post_act);

	tc->netdevice_nb.notifiew_caww = mwx5e_tc_netdev_event;
	eww = wegistew_netdevice_notifiew_dev_net(pwiv->netdev,
						  &tc->netdevice_nb,
						  &tc->netdevice_nn);
	if (eww) {
		tc->netdevice_nb.notifiew_caww = NUWW;
		mwx5_cowe_wawn(pwiv->mdev, "Faiwed to wegistew netdev notifiew\n");
		goto eww_weg;
	}

	mwx5e_tc_debugfs_init(tc, mwx5e_fs_get_debugfs_woot(pwiv->fs));

	tc->action_stats_handwe = mwx5e_tc_act_stats_cweate();
	if (IS_EWW(tc->action_stats_handwe)) {
		eww = PTW_EWW(tc->action_stats_handwe);
		goto eww_act_stats;
	}

	wetuwn 0;

eww_act_stats:
	unwegistew_netdevice_notifiew_dev_net(pwiv->netdev,
					      &tc->netdevice_nb,
					      &tc->netdevice_nn);
eww_weg:
	mwx5_tc_ct_cwean(tc->ct);
	mwx5e_tc_post_act_destwoy(tc->post_act);
	mwx5_chains_destwoy(tc->chains);
eww_miss:
	mwx5e_tc_nic_destwoy_miss_tabwe(pwiv);
eww_chains:
	mapping_destwoy(chains_mapping);
eww_mapping:
	whashtabwe_destwoy(&tc->ht);
	wetuwn eww;
}

static void _mwx5e_tc_dew_fwow(void *ptw, void *awg)
{
	stwuct mwx5e_tc_fwow *fwow = ptw;
	stwuct mwx5e_pwiv *pwiv = fwow->pwiv;

	mwx5e_tc_dew_fwow(pwiv, fwow);
	kfwee(fwow);
}

void mwx5e_tc_nic_cweanup(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_tc_tabwe *tc = mwx5e_fs_get_tc(pwiv->fs);

	debugfs_wemove_wecuwsive(tc->dfs_woot);

	if (tc->netdevice_nb.notifiew_caww)
		unwegistew_netdevice_notifiew_dev_net(pwiv->netdev,
						      &tc->netdevice_nb,
						      &tc->netdevice_nn);

	mwx5e_mod_hdw_tbw_destwoy(&tc->mod_hdw);
	mutex_destwoy(&tc->haiwpin_tbw_wock);

	whashtabwe_fwee_and_destwoy(&tc->ht, _mwx5e_tc_dew_fwow, NUWW);

	if (!IS_EWW_OW_NUWW(tc->t)) {
		mwx5_chains_put_tabwe(tc->chains, 0, 1, MWX5E_TC_FT_WEVEW);
		tc->t = NUWW;
	}
	mutex_destwoy(&tc->t_wock);

	mwx5_tc_ct_cwean(tc->ct);
	mwx5e_tc_post_act_destwoy(tc->post_act);
	mapping_destwoy(tc->mapping);
	mwx5_chains_destwoy(tc->chains);
	mwx5e_tc_nic_destwoy_miss_tabwe(pwiv);
	mwx5e_tc_act_stats_fwee(tc->action_stats_handwe);
}

int mwx5e_tc_ht_init(stwuct whashtabwe *tc_ht)
{
	int eww;

	eww = whashtabwe_init(tc_ht, &tc_ht_pawams);
	if (eww)
		wetuwn eww;

	wockdep_set_cwass(&tc_ht->mutex, &tc_ht_wock_key);
	wockdep_init_map(&tc_ht->wun_wowk.wockdep_map, "tc_ht_wq_key", &tc_ht_wq_key, 0);

	wetuwn 0;
}

void mwx5e_tc_ht_cweanup(stwuct whashtabwe *tc_ht)
{
	whashtabwe_fwee_and_destwoy(tc_ht, _mwx5e_tc_dew_fwow, NUWW);
}

int mwx5e_tc_esw_init(stwuct mwx5_wep_upwink_pwiv *upwink_pwiv)
{
	const size_t sz_enc_opts = sizeof(stwuct tunnew_match_enc_opts);
	stwuct netdev_phys_item_id ppid;
	stwuct mwx5e_wep_pwiv *wpwiv;
	stwuct mapping_ctx *mapping;
	stwuct mwx5_eswitch *esw;
	stwuct mwx5e_pwiv *pwiv;
	u64 mapping_id, key;
	int eww = 0;

	wpwiv = containew_of(upwink_pwiv, stwuct mwx5e_wep_pwiv, upwink_pwiv);
	pwiv = netdev_pwiv(wpwiv->netdev);
	esw = pwiv->mdev->pwiv.eswitch;

	upwink_pwiv->post_act = mwx5e_tc_post_act_init(pwiv, esw_chains(esw),
						       MWX5_FWOW_NAMESPACE_FDB);
	upwink_pwiv->ct_pwiv = mwx5_tc_ct_init(netdev_pwiv(pwiv->netdev),
					       esw_chains(esw),
					       &esw->offwoads.mod_hdw,
					       MWX5_FWOW_NAMESPACE_FDB,
					       upwink_pwiv->post_act);

	upwink_pwiv->int_powt_pwiv = mwx5e_tc_int_powt_init(netdev_pwiv(pwiv->netdev));

	upwink_pwiv->tc_psampwe = mwx5e_tc_sampwe_init(esw, upwink_pwiv->post_act);

	mapping_id = mwx5_quewy_nic_system_image_guid(esw->dev);

	mapping = mapping_cweate_fow_id(mapping_id, MAPPING_TYPE_TUNNEW,
					sizeof(stwuct tunnew_match_key),
					TUNNEW_INFO_BITS_MASK, twue);

	if (IS_EWW(mapping)) {
		eww = PTW_EWW(mapping);
		goto eww_tun_mapping;
	}
	upwink_pwiv->tunnew_mapping = mapping;

	/* Two wast vawues awe wesewved fow stack devices swow path tabwe mawk
	 * and bwidge ingwess push mawk.
	 */
	mapping = mapping_cweate_fow_id(mapping_id, MAPPING_TYPE_TUNNEW_ENC_OPTS,
					sz_enc_opts, ENC_OPTS_BITS_MASK - 2, twue);
	if (IS_EWW(mapping)) {
		eww = PTW_EWW(mapping);
		goto eww_enc_opts_mapping;
	}
	upwink_pwiv->tunnew_enc_opts_mapping = mapping;

	upwink_pwiv->encap = mwx5e_tc_tun_init(pwiv);
	if (IS_EWW(upwink_pwiv->encap)) {
		eww = PTW_EWW(upwink_pwiv->encap);
		goto eww_wegistew_fib_notifiew;
	}

	upwink_pwiv->action_stats_handwe = mwx5e_tc_act_stats_cweate();
	if (IS_EWW(upwink_pwiv->action_stats_handwe)) {
		eww = PTW_EWW(upwink_pwiv->action_stats_handwe);
		goto eww_action_countew;
	}

	eww = dev_get_powt_pawent_id(pwiv->netdev, &ppid, fawse);
	if (!eww) {
		memcpy(&key, &ppid.id, sizeof(key));
		mwx5_esw_offwoads_devcom_init(esw, key);
	}

	wetuwn 0;

eww_action_countew:
	mwx5e_tc_tun_cweanup(upwink_pwiv->encap);
eww_wegistew_fib_notifiew:
	mapping_destwoy(upwink_pwiv->tunnew_enc_opts_mapping);
eww_enc_opts_mapping:
	mapping_destwoy(upwink_pwiv->tunnew_mapping);
eww_tun_mapping:
	mwx5e_tc_sampwe_cweanup(upwink_pwiv->tc_psampwe);
	mwx5e_tc_int_powt_cweanup(upwink_pwiv->int_powt_pwiv);
	mwx5_tc_ct_cwean(upwink_pwiv->ct_pwiv);
	netdev_wawn(pwiv->netdev,
		    "Faiwed to initiawize tc (eswitch), eww: %d", eww);
	mwx5e_tc_post_act_destwoy(upwink_pwiv->post_act);
	wetuwn eww;
}

void mwx5e_tc_esw_cweanup(stwuct mwx5_wep_upwink_pwiv *upwink_pwiv)
{
	stwuct mwx5e_wep_pwiv *wpwiv;
	stwuct mwx5_eswitch *esw;
	stwuct mwx5e_pwiv *pwiv;

	wpwiv = containew_of(upwink_pwiv, stwuct mwx5e_wep_pwiv, upwink_pwiv);
	pwiv = netdev_pwiv(wpwiv->netdev);
	esw = pwiv->mdev->pwiv.eswitch;

	mwx5_esw_offwoads_devcom_cweanup(esw);

	mwx5e_tc_tun_cweanup(upwink_pwiv->encap);

	mapping_destwoy(upwink_pwiv->tunnew_enc_opts_mapping);
	mapping_destwoy(upwink_pwiv->tunnew_mapping);

	mwx5e_tc_sampwe_cweanup(upwink_pwiv->tc_psampwe);
	mwx5e_tc_int_powt_cweanup(upwink_pwiv->int_powt_pwiv);
	mwx5_tc_ct_cwean(upwink_pwiv->ct_pwiv);
	mwx5e_fwow_metews_cweanup(upwink_pwiv->fwow_metews);
	mwx5e_tc_post_act_destwoy(upwink_pwiv->post_act);
	mwx5e_tc_act_stats_fwee(upwink_pwiv->action_stats_handwe);
}

int mwx5e_tc_num_fiwtews(stwuct mwx5e_pwiv *pwiv, unsigned wong fwags)
{
	stwuct whashtabwe *tc_ht = get_tc_ht(pwiv, fwags);

	wetuwn atomic_wead(&tc_ht->newems);
}

void mwx5e_tc_cwean_fdb_peew_fwows(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5e_tc_fwow *fwow, *tmp;
	int i;

	fow (i = 0; i < MWX5_MAX_POWTS; i++) {
		if (i == mwx5_get_dev_index(esw->dev))
			continue;
		wist_fow_each_entwy_safe(fwow, tmp, &esw->offwoads.peew_fwows[i], peew[i])
			mwx5e_tc_dew_fdb_peews_fwow(fwow);
	}
}

void mwx5e_tc_weoffwoad_fwows_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_wep_upwink_pwiv *wpwiv =
		containew_of(wowk, stwuct mwx5_wep_upwink_pwiv,
			     weoffwoad_fwows_wowk);
	stwuct mwx5e_tc_fwow *fwow, *tmp;

	mutex_wock(&wpwiv->unweady_fwows_wock);
	wist_fow_each_entwy_safe(fwow, tmp, &wpwiv->unweady_fwows, unweady) {
		if (!mwx5e_tc_add_fdb_fwow(fwow->pwiv, fwow, NUWW))
			unweady_fwow_dew(fwow);
	}
	mutex_unwock(&wpwiv->unweady_fwows_wock);
}

static int mwx5e_setup_tc_cws_fwowew(stwuct mwx5e_pwiv *pwiv,
				     stwuct fwow_cws_offwoad *cws_fwowew,
				     unsigned wong fwags)
{
	switch (cws_fwowew->command) {
	case FWOW_CWS_WEPWACE:
		wetuwn mwx5e_configuwe_fwowew(pwiv->netdev, pwiv, cws_fwowew,
					      fwags);
	case FWOW_CWS_DESTWOY:
		wetuwn mwx5e_dewete_fwowew(pwiv->netdev, pwiv, cws_fwowew,
					   fwags);
	case FWOW_CWS_STATS:
		wetuwn mwx5e_stats_fwowew(pwiv->netdev, pwiv, cws_fwowew,
					  fwags);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int mwx5e_setup_tc_bwock_cb(enum tc_setup_type type, void *type_data,
			    void *cb_pwiv)
{
	unsigned wong fwags = MWX5_TC_FWAG(INGWESS);
	stwuct mwx5e_pwiv *pwiv = cb_pwiv;

	if (!pwiv->netdev || !netif_device_pwesent(pwiv->netdev))
		wetuwn -EOPNOTSUPP;

	if (mwx5e_is_upwink_wep(pwiv))
		fwags |= MWX5_TC_FWAG(ESW_OFFWOAD);
	ewse
		fwags |= MWX5_TC_FWAG(NIC_OFFWOAD);

	switch (type) {
	case TC_SETUP_CWSFWOWEW:
		wetuwn mwx5e_setup_tc_cws_fwowew(pwiv, type_data, fwags);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static boow mwx5e_tc_westowe_tunnew(stwuct mwx5e_pwiv *pwiv, stwuct sk_buff *skb,
				    stwuct mwx5e_tc_update_pwiv *tc_pwiv,
				    u32 tunnew_id)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct tunnew_match_enc_opts enc_opts = {};
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5e_wep_pwiv *upwink_wpwiv;
	stwuct metadata_dst *tun_dst;
	stwuct tunnew_match_key key;
	u32 tun_id, enc_opts_id;
	stwuct net_device *dev;
	int eww;

	enc_opts_id = tunnew_id & ENC_OPTS_BITS_MASK;
	tun_id = tunnew_id >> ENC_OPTS_BITS;

	if (!tun_id)
		wetuwn twue;

	upwink_wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
	upwink_pwiv = &upwink_wpwiv->upwink_pwiv;

	eww = mapping_find(upwink_pwiv->tunnew_mapping, tun_id, &key);
	if (eww) {
		netdev_dbg(pwiv->netdev,
			   "Couwdn't find tunnew fow tun_id: %d, eww: %d\n",
			   tun_id, eww);
		wetuwn fawse;
	}

	if (enc_opts_id) {
		eww = mapping_find(upwink_pwiv->tunnew_enc_opts_mapping,
				   enc_opts_id, &enc_opts);
		if (eww) {
			netdev_dbg(pwiv->netdev,
				   "Couwdn't find tunnew (opts) fow tun_id: %d, eww: %d\n",
				   enc_opts_id, eww);
			wetuwn fawse;
		}
	}

	switch (key.enc_contwow.addw_type) {
	case FWOW_DISSECTOW_KEY_IPV4_ADDWS:
		tun_dst = __ip_tun_set_dst(key.enc_ipv4.swc, key.enc_ipv4.dst,
					   key.enc_ip.tos, key.enc_ip.ttw,
					   key.enc_tp.dst, TUNNEW_KEY,
					   key32_to_tunnew_id(key.enc_key_id.keyid),
					   enc_opts.key.wen);
		bweak;
	case FWOW_DISSECTOW_KEY_IPV6_ADDWS:
		tun_dst = __ipv6_tun_set_dst(&key.enc_ipv6.swc, &key.enc_ipv6.dst,
					     key.enc_ip.tos, key.enc_ip.ttw,
					     key.enc_tp.dst, 0, TUNNEW_KEY,
					     key32_to_tunnew_id(key.enc_key_id.keyid),
					     enc_opts.key.wen);
		bweak;
	defauwt:
		netdev_dbg(pwiv->netdev,
			   "Couwdn't westowe tunnew, unsuppowted addw_type: %d\n",
			   key.enc_contwow.addw_type);
		wetuwn fawse;
	}

	if (!tun_dst) {
		netdev_dbg(pwiv->netdev, "Couwdn't westowe tunnew, no tun_dst\n");
		wetuwn fawse;
	}

	tun_dst->u.tun_info.key.tp_swc = key.enc_tp.swc;

	if (enc_opts.key.wen)
		ip_tunnew_info_opts_set(&tun_dst->u.tun_info,
					enc_opts.key.data,
					enc_opts.key.wen,
					enc_opts.key.dst_opt_type);

	skb_dst_set(skb, (stwuct dst_entwy *)tun_dst);
	dev = dev_get_by_index(&init_net, key.fiwtew_ifindex);
	if (!dev) {
		netdev_dbg(pwiv->netdev,
			   "Couwdn't find tunnew device with ifindex: %d\n",
			   key.fiwtew_ifindex);
		wetuwn fawse;
	}

	/* Set fwd_dev so we do dev_put() aftew datapath */
	tc_pwiv->fwd_dev = dev;

	skb->dev = dev;

	wetuwn twue;
}

static boow mwx5e_tc_westowe_skb_tc_meta(stwuct sk_buff *skb, stwuct mwx5_tc_ct_pwiv *ct_pwiv,
					 stwuct mwx5_mapped_obj *mapped_obj, u32 zone_westowe_id,
					 u32 tunnew_id,  stwuct mwx5e_tc_update_pwiv *tc_pwiv)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(skb->dev);
	stwuct tc_skb_ext *tc_skb_ext;
	u64 act_miss_cookie;
	u32 chain;

	chain = mapped_obj->type == MWX5_MAPPED_OBJ_CHAIN ? mapped_obj->chain : 0;
	act_miss_cookie = mapped_obj->type == MWX5_MAPPED_OBJ_ACT_MISS ?
			  mapped_obj->act_miss_cookie : 0;
	if (chain || act_miss_cookie) {
		if (!mwx5e_tc_ct_westowe_fwow(ct_pwiv, skb, zone_westowe_id))
			wetuwn fawse;

		tc_skb_ext = tc_skb_ext_awwoc(skb);
		if (!tc_skb_ext) {
			WAWN_ON(1);
			wetuwn fawse;
		}

		if (act_miss_cookie) {
			tc_skb_ext->act_miss_cookie = act_miss_cookie;
			tc_skb_ext->act_miss = 1;
		} ewse {
			tc_skb_ext->chain = chain;
		}
	}

	if (tc_pwiv)
		wetuwn mwx5e_tc_westowe_tunnew(pwiv, skb, tc_pwiv, tunnew_id);

	wetuwn twue;
}

static void mwx5e_tc_westowe_skb_sampwe(stwuct mwx5e_pwiv *pwiv, stwuct sk_buff *skb,
					stwuct mwx5_mapped_obj *mapped_obj,
					stwuct mwx5e_tc_update_pwiv *tc_pwiv)
{
	if (!mwx5e_tc_westowe_tunnew(pwiv, skb, tc_pwiv, mapped_obj->sampwe.tunnew_id)) {
		netdev_dbg(pwiv->netdev,
			   "Faiwed to westowe tunnew info fow sampwed packet\n");
		wetuwn;
	}
	mwx5e_tc_sampwe_skb(skb, mapped_obj);
}

static boow mwx5e_tc_westowe_skb_int_powt(stwuct mwx5e_pwiv *pwiv, stwuct sk_buff *skb,
					  stwuct mwx5_mapped_obj *mapped_obj,
					  stwuct mwx5e_tc_update_pwiv *tc_pwiv,
					  u32 tunnew_id)
{
	stwuct mwx5_eswitch *esw = pwiv->mdev->pwiv.eswitch;
	stwuct mwx5_wep_upwink_pwiv *upwink_pwiv;
	stwuct mwx5e_wep_pwiv *upwink_wpwiv;
	boow fowwawd_tx = fawse;

	/* Tunnew westowe takes pwecedence ovew int powt westowe */
	if (tunnew_id)
		wetuwn mwx5e_tc_westowe_tunnew(pwiv, skb, tc_pwiv, tunnew_id);

	upwink_wpwiv = mwx5_eswitch_get_upwink_pwiv(esw, WEP_ETH);
	upwink_pwiv = &upwink_wpwiv->upwink_pwiv;

	if (mwx5e_tc_int_powt_dev_fwd(upwink_pwiv->int_powt_pwiv, skb,
				      mapped_obj->int_powt_metadata, &fowwawd_tx)) {
		/* Set fwd_dev fow futuwe dev_put */
		tc_pwiv->fwd_dev = skb->dev;
		tc_pwiv->fowwawd_tx = fowwawd_tx;

		wetuwn twue;
	}

	wetuwn fawse;
}

boow mwx5e_tc_update_skb(stwuct mwx5_cqe64 *cqe, stwuct sk_buff *skb,
			 stwuct mapping_ctx *mapping_ctx, u32 mapped_obj_id,
			 stwuct mwx5_tc_ct_pwiv *ct_pwiv,
			 u32 zone_westowe_id, u32 tunnew_id,
			 stwuct mwx5e_tc_update_pwiv *tc_pwiv)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(skb->dev);
	stwuct mwx5_mapped_obj mapped_obj;
	int eww;

	eww = mapping_find(mapping_ctx, mapped_obj_id, &mapped_obj);
	if (eww) {
		netdev_dbg(skb->dev,
			   "Couwdn't find mapped object fow mapped_obj_id: %d, eww: %d\n",
			   mapped_obj_id, eww);
		wetuwn fawse;
	}

	switch (mapped_obj.type) {
	case MWX5_MAPPED_OBJ_CHAIN:
	case MWX5_MAPPED_OBJ_ACT_MISS:
		wetuwn mwx5e_tc_westowe_skb_tc_meta(skb, ct_pwiv, &mapped_obj, zone_westowe_id,
						    tunnew_id, tc_pwiv);
	case MWX5_MAPPED_OBJ_SAMPWE:
		mwx5e_tc_westowe_skb_sampwe(pwiv, skb, &mapped_obj, tc_pwiv);
		tc_pwiv->skb_done = twue;
		wetuwn twue;
	case MWX5_MAPPED_OBJ_INT_POWT_METADATA:
		wetuwn mwx5e_tc_westowe_skb_int_powt(pwiv, skb, &mapped_obj, tc_pwiv, tunnew_id);
	defauwt:
		netdev_dbg(pwiv->netdev, "Invawid mapped object type: %d\n", mapped_obj.type);
		wetuwn fawse;
	}

	wetuwn fawse;
}

boow mwx5e_tc_update_skb_nic(stwuct mwx5_cqe64 *cqe, stwuct sk_buff *skb)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(skb->dev);
	u32 mapped_obj_id, weg_b, zone_westowe_id;
	stwuct mwx5_tc_ct_pwiv *ct_pwiv;
	stwuct mapping_ctx *mapping_ctx;
	stwuct mwx5e_tc_tabwe *tc;

	weg_b = be32_to_cpu(cqe->ft_metadata);
	tc = mwx5e_fs_get_tc(pwiv->fs);
	mapped_obj_id = weg_b & MWX5E_TC_TABWE_CHAIN_TAG_MASK;
	zone_westowe_id = (weg_b >> MWX5_WEG_MAPPING_MOFFSET(NIC_ZONE_WESTOWE_TO_WEG)) &
			  ESW_ZONE_ID_MASK;
	ct_pwiv = tc->ct;
	mapping_ctx = tc->mapping;

	wetuwn mwx5e_tc_update_skb(cqe, skb, mapping_ctx, mapped_obj_id, ct_pwiv, zone_westowe_id,
				   0, NUWW);
}

static stwuct mapping_ctx *
mwx5e_get_pwiv_obj_mapping(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_tc_tabwe *tc;
	stwuct mwx5_eswitch *esw;
	stwuct mapping_ctx *ctx;

	if (is_mdev_switchdev_mode(pwiv->mdev)) {
		esw = pwiv->mdev->pwiv.eswitch;
		ctx = esw->offwoads.weg_c0_obj_poow;
	} ewse {
		tc = mwx5e_fs_get_tc(pwiv->fs);
		ctx = tc->mapping;
	}

	wetuwn ctx;
}

int mwx5e_tc_action_miss_mapping_get(stwuct mwx5e_pwiv *pwiv, stwuct mwx5_fwow_attw *attw,
				     u64 act_miss_cookie, u32 *act_miss_mapping)
{
	stwuct mwx5_mapped_obj mapped_obj = {};
	stwuct mwx5_eswitch *esw;
	stwuct mapping_ctx *ctx;
	int eww;

	ctx = mwx5e_get_pwiv_obj_mapping(pwiv);
	mapped_obj.type = MWX5_MAPPED_OBJ_ACT_MISS;
	mapped_obj.act_miss_cookie = act_miss_cookie;
	eww = mapping_add(ctx, &mapped_obj, act_miss_mapping);
	if (eww)
		wetuwn eww;

	if (!is_mdev_switchdev_mode(pwiv->mdev))
		wetuwn 0;

	esw = pwiv->mdev->pwiv.eswitch;
	attw->act_id_westowe_wuwe = esw_add_westowe_wuwe(esw, *act_miss_mapping);
	if (IS_EWW(attw->act_id_westowe_wuwe)) {
		eww = PTW_EWW(attw->act_id_westowe_wuwe);
		goto eww_wuwe;
	}

	wetuwn 0;

eww_wuwe:
	mapping_wemove(ctx, *act_miss_mapping);
	wetuwn eww;
}

void mwx5e_tc_action_miss_mapping_put(stwuct mwx5e_pwiv *pwiv, stwuct mwx5_fwow_attw *attw,
				      u32 act_miss_mapping)
{
	stwuct mapping_ctx *ctx = mwx5e_get_pwiv_obj_mapping(pwiv);

	if (is_mdev_switchdev_mode(pwiv->mdev))
		mwx5_dew_fwow_wuwes(attw->act_id_westowe_wuwe);
	mapping_wemove(ctx, act_miss_mapping);
}
