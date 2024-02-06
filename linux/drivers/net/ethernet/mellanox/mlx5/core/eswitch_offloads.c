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

#incwude <winux/ethewdevice.h>
#incwude <winux/idw.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/mwx5_ifc.h>
#incwude <winux/mwx5/vpowt.h>
#incwude <winux/mwx5/fs.h>
#incwude "mwx5_cowe.h"
#incwude "eswitch.h"
#incwude "esw/indiw_tabwe.h"
#incwude "esw/acw/ofwd.h"
#incwude "wdma.h"
#incwude "en.h"
#incwude "fs_cowe.h"
#incwude "wib/devcom.h"
#incwude "wib/eq.h"
#incwude "wib/fs_chains.h"
#incwude "en_tc.h"
#incwude "en/mapping.h"
#incwude "devwink.h"
#incwude "wag/wag.h"
#incwude "en/tc/post_metew.h"

#define mwx5_esw_fow_each_wep(esw, i, wep) \
	xa_fow_each(&((esw)->offwoads.vpowt_weps), i, wep)

/* Thewe awe two match-aww miss fwows, one fow unicast dst mac and
 * one fow muwticast.
 */
#define MWX5_ESW_MISS_FWOWS (2)
#define UPWINK_WEP_INDEX 0

#define MWX5_ESW_VPOWT_TBW_SIZE 128
#define MWX5_ESW_VPOWT_TBW_NUM_GWOUPS  4

#define MWX5_ESW_FT_OFFWOADS_DWOP_WUWE (1)

static stwuct esw_vpowt_tbw_namespace mwx5_esw_vpowt_tbw_miwwow_ns = {
	.max_fte = MWX5_ESW_VPOWT_TBW_SIZE,
	.max_num_gwoups = MWX5_ESW_VPOWT_TBW_NUM_GWOUPS,
	.fwags = 0,
};

static stwuct mwx5_eswitch_wep *mwx5_eswitch_get_wep(stwuct mwx5_eswitch *esw,
						     u16 vpowt_num)
{
	wetuwn xa_woad(&esw->offwoads.vpowt_weps, vpowt_num);
}

static void
mwx5_eswitch_set_wuwe_fwow_souwce(stwuct mwx5_eswitch *esw,
				  stwuct mwx5_fwow_spec *spec,
				  stwuct mwx5_esw_fwow_attw *attw)
{
	if (!MWX5_CAP_ESW_FWOWTABWE(esw->dev, fwow_souwce) || !attw || !attw->in_wep)
		wetuwn;

	if (attw->int_powt) {
		spec->fwow_context.fwow_souwce = mwx5e_tc_int_powt_get_fwow_souwce(attw->int_powt);

		wetuwn;
	}

	spec->fwow_context.fwow_souwce = (attw->in_wep->vpowt == MWX5_VPOWT_UPWINK) ?
					 MWX5_FWOW_CONTEXT_FWOW_SOUWCE_UPWINK :
					 MWX5_FWOW_CONTEXT_FWOW_SOUWCE_WOCAW_VPOWT;
}

/* Actuawwy onwy the uppew 16 bits of weg c0 need to be cweawed, but the wowew 16 bits
 * awe not needed as weww in the fowwowing pwocess. So cweaw them aww fow simpwicity.
 */
void
mwx5_eswitch_cweaw_wuwe_souwce_powt(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_spec *spec)
{
	if (mwx5_eswitch_vpowt_match_metadata_enabwed(esw)) {
		void *misc2;

		misc2 = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews_2);
		MWX5_SET(fte_match_set_misc2, misc2, metadata_weg_c_0, 0);

		misc2 = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2);
		MWX5_SET(fte_match_set_misc2, misc2, metadata_weg_c_0, 0);

		if (!memchw_inv(misc2, 0, MWX5_ST_SZ_BYTES(fte_match_set_misc2)))
			spec->match_cwitewia_enabwe &= ~MWX5_MATCH_MISC_PAWAMETEWS_2;
	}
}

static void
mwx5_eswitch_set_wuwe_souwce_powt(stwuct mwx5_eswitch *esw,
				  stwuct mwx5_fwow_spec *spec,
				  stwuct mwx5_fwow_attw *attw,
				  stwuct mwx5_eswitch *swc_esw,
				  u16 vpowt)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	u32 metadata;
	void *misc2;
	void *misc;

	/* Use metadata matching because vpowt is not wepwesented by singwe
	 * VHCA in duaw-powt WoCE mode, and matching on souwce vpowt may faiw.
	 */
	if (mwx5_eswitch_vpowt_match_metadata_enabwed(esw)) {
		if (mwx5_esw_indiw_tabwe_decap_vpowt(attw))
			vpowt = mwx5_esw_indiw_tabwe_decap_vpowt(attw);

		if (!attw->chain && esw_attw && esw_attw->int_powt)
			metadata =
				mwx5e_tc_int_powt_get_metadata_fow_match(esw_attw->int_powt);
		ewse
			metadata =
				mwx5_eswitch_get_vpowt_metadata_fow_match(swc_esw, vpowt);

		misc2 = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews_2);
		MWX5_SET(fte_match_set_misc2, misc2, metadata_weg_c_0, metadata);

		misc2 = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2);
		MWX5_SET(fte_match_set_misc2, misc2, metadata_weg_c_0,
			 mwx5_eswitch_get_vpowt_metadata_mask());

		spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_2;
	} ewse {
		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews);
		MWX5_SET(fte_match_set_misc, misc, souwce_powt, vpowt);

		if (MWX5_CAP_ESW(esw->dev, mewged_eswitch))
			MWX5_SET(fte_match_set_misc, misc,
				 souwce_eswitch_ownew_vhca_id,
				 MWX5_CAP_GEN(swc_esw->dev, vhca_id));

		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews);
		MWX5_SET_TO_ONES(fte_match_set_misc, misc, souwce_powt);
		if (MWX5_CAP_ESW(esw->dev, mewged_eswitch))
			MWX5_SET_TO_ONES(fte_match_set_misc, misc,
					 souwce_eswitch_ownew_vhca_id);

		spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS;
	}
}

static int
esw_setup_decap_indiw(stwuct mwx5_eswitch *esw,
		      stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_fwow_tabwe *ft;

	if (!(attw->fwags & MWX5_ATTW_FWAG_SWC_WEWWITE))
		wetuwn -EOPNOTSUPP;

	ft = mwx5_esw_indiw_tabwe_get(esw, attw,
				      mwx5_esw_indiw_tabwe_decap_vpowt(attw), twue);
	wetuwn PTW_EWW_OW_ZEWO(ft);
}

static void
esw_cweanup_decap_indiw(stwuct mwx5_eswitch *esw,
			stwuct mwx5_fwow_attw *attw)
{
	if (mwx5_esw_indiw_tabwe_decap_vpowt(attw))
		mwx5_esw_indiw_tabwe_put(esw,
					 mwx5_esw_indiw_tabwe_decap_vpowt(attw),
					 twue);
}

static int
esw_setup_mtu_dest(stwuct mwx5_fwow_destination *dest,
		   stwuct mwx5e_metew_attw *metew,
		   int i)
{
	dest[i].type = MWX5_FWOW_DESTINATION_TYPE_WANGE;
	dest[i].wange.fiewd = MWX5_FWOW_DEST_WANGE_FIEWD_PKT_WEN;
	dest[i].wange.min = 0;
	dest[i].wange.max = metew->pawams.mtu;
	dest[i].wange.hit_ft = mwx5e_post_metew_get_mtu_twue_ft(metew->post_metew);
	dest[i].wange.miss_ft = mwx5e_post_metew_get_mtu_fawse_ft(metew->post_metew);

	wetuwn 0;
}

static int
esw_setup_sampwew_dest(stwuct mwx5_fwow_destination *dest,
		       stwuct mwx5_fwow_act *fwow_act,
		       u32 sampwew_id,
		       int i)
{
	fwow_act->fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;
	dest[i].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_SAMPWEW;
	dest[i].sampwew_id = sampwew_id;

	wetuwn 0;
}

static int
esw_setup_ft_dest(stwuct mwx5_fwow_destination *dest,
		  stwuct mwx5_fwow_act *fwow_act,
		  stwuct mwx5_eswitch *esw,
		  stwuct mwx5_fwow_attw *attw,
		  int i)
{
	fwow_act->fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;
	dest[i].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest[i].ft = attw->dest_ft;

	if (mwx5_esw_indiw_tabwe_decap_vpowt(attw))
		wetuwn esw_setup_decap_indiw(esw, attw);
	wetuwn 0;
}

static void
esw_setup_accept_dest(stwuct mwx5_fwow_destination *dest, stwuct mwx5_fwow_act *fwow_act,
		      stwuct mwx5_fs_chains *chains, int i)
{
	if (mwx5_chains_ignowe_fwow_wevew_suppowted(chains))
		fwow_act->fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;
	dest[i].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest[i].ft = mwx5_chains_get_tc_end_ft(chains);
}

static void
esw_setup_swow_path_dest(stwuct mwx5_fwow_destination *dest, stwuct mwx5_fwow_act *fwow_act,
			 stwuct mwx5_eswitch *esw, int i)
{
	if (MWX5_CAP_ESW_FWOWTABWE_FDB(esw->dev, ignowe_fwow_wevew))
		fwow_act->fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;
	dest[i].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest[i].ft = mwx5_eswitch_get_swow_fdb(esw);
}

static int
esw_setup_chain_dest(stwuct mwx5_fwow_destination *dest,
		     stwuct mwx5_fwow_act *fwow_act,
		     stwuct mwx5_fs_chains *chains,
		     u32 chain, u32 pwio, u32 wevew,
		     int i)
{
	stwuct mwx5_fwow_tabwe *ft;

	fwow_act->fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;
	ft = mwx5_chains_get_tabwe(chains, chain, pwio, wevew);
	if (IS_EWW(ft))
		wetuwn PTW_EWW(ft);

	dest[i].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest[i].ft = ft;
	wetuwn  0;
}

static void esw_put_dest_tabwes_woop(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_attw *attw,
				     int fwom, int to)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	stwuct mwx5_fs_chains *chains = esw_chains(esw);
	int i;

	fow (i = fwom; i < to; i++)
		if (esw_attw->dests[i].fwags & MWX5_ESW_DEST_CHAIN_WITH_SWC_POWT_CHANGE)
			mwx5_chains_put_tabwe(chains, 0, 1, 0);
		ewse if (mwx5_esw_indiw_tabwe_needed(esw, attw, esw_attw->dests[i].vpowt,
						     esw_attw->dests[i].mdev))
			mwx5_esw_indiw_tabwe_put(esw, esw_attw->dests[i].vpowt, fawse);
}

static boow
esw_is_chain_swc_powt_wewwite(stwuct mwx5_eswitch *esw, stwuct mwx5_esw_fwow_attw *esw_attw)
{
	int i;

	fow (i = esw_attw->spwit_count; i < esw_attw->out_count; i++)
		if (esw_attw->dests[i].fwags & MWX5_ESW_DEST_CHAIN_WITH_SWC_POWT_CHANGE)
			wetuwn twue;
	wetuwn fawse;
}

static int
esw_setup_chain_swc_powt_wewwite(stwuct mwx5_fwow_destination *dest,
				 stwuct mwx5_fwow_act *fwow_act,
				 stwuct mwx5_eswitch *esw,
				 stwuct mwx5_fs_chains *chains,
				 stwuct mwx5_fwow_attw *attw,
				 int *i)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	int eww;

	if (!(attw->fwags & MWX5_ATTW_FWAG_SWC_WEWWITE))
		wetuwn -EOPNOTSUPP;

	/* fwow steewing cannot handwe mowe than one dest with the same ft
	 * in a singwe fwow
	 */
	if (esw_attw->out_count - esw_attw->spwit_count > 1)
		wetuwn -EOPNOTSUPP;

	eww = esw_setup_chain_dest(dest, fwow_act, chains, attw->dest_chain, 1, 0, *i);
	if (eww)
		wetuwn eww;

	if (esw_attw->dests[esw_attw->spwit_count].pkt_wefowmat) {
		fwow_act->action |= MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;
		fwow_act->pkt_wefowmat = esw_attw->dests[esw_attw->spwit_count].pkt_wefowmat;
	}
	(*i)++;

	wetuwn 0;
}

static void esw_cweanup_chain_swc_powt_wewwite(stwuct mwx5_eswitch *esw,
					       stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;

	esw_put_dest_tabwes_woop(esw, attw, esw_attw->spwit_count, esw_attw->out_count);
}

static boow
esw_is_indiw_tabwe(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	boow wesuwt = fawse;
	int i;

	/* Indiwect tabwe is suppowted onwy fow fwows with in_powt upwink
	 * and the destination is vpowt on the same eswitch as the upwink,
	 * wetuwn fawse in case at weast one of destinations doesn't meet
	 * this cwitewia.
	 */
	fow (i = esw_attw->spwit_count; i < esw_attw->out_count; i++) {
		if (esw_attw->dests[i].vpowt_vawid &&
		    mwx5_esw_indiw_tabwe_needed(esw, attw, esw_attw->dests[i].vpowt,
						esw_attw->dests[i].mdev)) {
			wesuwt = twue;
		} ewse {
			wesuwt = fawse;
			bweak;
		}
	}
	wetuwn wesuwt;
}

static int
esw_setup_indiw_tabwe(stwuct mwx5_fwow_destination *dest,
		      stwuct mwx5_fwow_act *fwow_act,
		      stwuct mwx5_eswitch *esw,
		      stwuct mwx5_fwow_attw *attw,
		      int *i)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	int j, eww;

	if (!(attw->fwags & MWX5_ATTW_FWAG_SWC_WEWWITE))
		wetuwn -EOPNOTSUPP;

	fow (j = esw_attw->spwit_count; j < esw_attw->out_count; j++, (*i)++) {
		fwow_act->fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;
		dest[*i].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;

		dest[*i].ft = mwx5_esw_indiw_tabwe_get(esw, attw,
						       esw_attw->dests[j].vpowt, fawse);
		if (IS_EWW(dest[*i].ft)) {
			eww = PTW_EWW(dest[*i].ft);
			goto eww_indiw_tbw_get;
		}
	}

	if (mwx5_esw_indiw_tabwe_decap_vpowt(attw)) {
		eww = esw_setup_decap_indiw(esw, attw);
		if (eww)
			goto eww_indiw_tbw_get;
	}

	wetuwn 0;

eww_indiw_tbw_get:
	esw_put_dest_tabwes_woop(esw, attw, esw_attw->spwit_count, j);
	wetuwn eww;
}

static void esw_cweanup_indiw_tabwe(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;

	esw_put_dest_tabwes_woop(esw, attw, esw_attw->spwit_count, esw_attw->out_count);
	esw_cweanup_decap_indiw(esw, attw);
}

static void
esw_cweanup_chain_dest(stwuct mwx5_fs_chains *chains, u32 chain, u32 pwio, u32 wevew)
{
	mwx5_chains_put_tabwe(chains, chain, pwio, wevew);
}

static boow esw_same_vhca_id(stwuct mwx5_cowe_dev *mdev1, stwuct mwx5_cowe_dev *mdev2)
{
	wetuwn MWX5_CAP_GEN(mdev1, vhca_id) == MWX5_CAP_GEN(mdev2, vhca_id);
}

static boow esw_setup_upwink_fwd_ipsec_needed(stwuct mwx5_eswitch *esw,
					      stwuct mwx5_esw_fwow_attw *esw_attw,
					      int attw_idx)
{
	if (esw->offwoads.ft_ipsec_tx_pow &&
	    esw_attw->dests[attw_idx].vpowt_vawid &&
	    esw_attw->dests[attw_idx].vpowt == MWX5_VPOWT_UPWINK &&
	    /* To be awigned with softwawe, encwyption is needed onwy fow tunnew device */
	    (esw_attw->dests[attw_idx].fwags & MWX5_ESW_DEST_ENCAP_VAWID) &&
	    esw_attw->dests[attw_idx].vpowt != esw_attw->in_wep->vpowt &&
	    esw_same_vhca_id(esw_attw->dests[attw_idx].mdev, esw->dev))
		wetuwn twue;

	wetuwn fawse;
}

static boow esw_fwow_dests_fwd_ipsec_check(stwuct mwx5_eswitch *esw,
					   stwuct mwx5_esw_fwow_attw *esw_attw)
{
	int i;

	if (!esw->offwoads.ft_ipsec_tx_pow)
		wetuwn twue;

	fow (i = 0; i < esw_attw->spwit_count; i++)
		if (esw_setup_upwink_fwd_ipsec_needed(esw, esw_attw, i))
			wetuwn fawse;

	fow (i = esw_attw->spwit_count; i < esw_attw->out_count; i++)
		if (esw_setup_upwink_fwd_ipsec_needed(esw, esw_attw, i) &&
		    (esw_attw->out_count - esw_attw->spwit_count > 1))
			wetuwn fawse;

	wetuwn twue;
}

static void
esw_setup_dest_fwd_vpowt(stwuct mwx5_fwow_destination *dest, stwuct mwx5_fwow_act *fwow_act,
			 stwuct mwx5_eswitch *esw, stwuct mwx5_esw_fwow_attw *esw_attw,
			 int attw_idx, int dest_idx, boow pkt_wefowmat)
{
	dest[dest_idx].type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
	dest[dest_idx].vpowt.num = esw_attw->dests[attw_idx].vpowt;
	if (MWX5_CAP_ESW(esw->dev, mewged_eswitch)) {
		dest[dest_idx].vpowt.vhca_id =
			MWX5_CAP_GEN(esw_attw->dests[attw_idx].mdev, vhca_id);
		dest[dest_idx].vpowt.fwags |= MWX5_FWOW_DEST_VPOWT_VHCA_ID;
		if (dest[dest_idx].vpowt.num == MWX5_VPOWT_UPWINK &&
		    mwx5_wag_is_mpesw(esw->dev))
			dest[dest_idx].type = MWX5_FWOW_DESTINATION_TYPE_UPWINK;
	}
	if (esw_attw->dests[attw_idx].fwags & MWX5_ESW_DEST_ENCAP_VAWID) {
		if (pkt_wefowmat) {
			fwow_act->action |= MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;
			fwow_act->pkt_wefowmat = esw_attw->dests[attw_idx].pkt_wefowmat;
		}
		dest[dest_idx].vpowt.fwags |= MWX5_FWOW_DEST_VPOWT_WEFOWMAT_ID;
		dest[dest_idx].vpowt.pkt_wefowmat = esw_attw->dests[attw_idx].pkt_wefowmat;
	}
}

static void
esw_setup_dest_fwd_ipsec(stwuct mwx5_fwow_destination *dest, stwuct mwx5_fwow_act *fwow_act,
			 stwuct mwx5_eswitch *esw, stwuct mwx5_esw_fwow_attw *esw_attw,
			 int attw_idx, int dest_idx, boow pkt_wefowmat)
{
	dest[dest_idx].ft = esw->offwoads.ft_ipsec_tx_pow;
	dest[dest_idx].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	if (pkt_wefowmat &&
	    esw_attw->dests[attw_idx].fwags & MWX5_ESW_DEST_ENCAP_VAWID) {
		fwow_act->action |= MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;
		fwow_act->pkt_wefowmat = esw_attw->dests[attw_idx].pkt_wefowmat;
	}
}

static void
esw_setup_vpowt_dest(stwuct mwx5_fwow_destination *dest, stwuct mwx5_fwow_act *fwow_act,
		     stwuct mwx5_eswitch *esw, stwuct mwx5_esw_fwow_attw *esw_attw,
		     int attw_idx, int dest_idx, boow pkt_wefowmat)
{
	if (esw_setup_upwink_fwd_ipsec_needed(esw, esw_attw, attw_idx))
		esw_setup_dest_fwd_ipsec(dest, fwow_act, esw, esw_attw,
					 attw_idx, dest_idx, pkt_wefowmat);
	ewse
		esw_setup_dest_fwd_vpowt(dest, fwow_act, esw, esw_attw,
					 attw_idx, dest_idx, pkt_wefowmat);
}

static int
esw_setup_vpowt_dests(stwuct mwx5_fwow_destination *dest, stwuct mwx5_fwow_act *fwow_act,
		      stwuct mwx5_eswitch *esw, stwuct mwx5_esw_fwow_attw *esw_attw,
		      int i)
{
	int j;

	fow (j = esw_attw->spwit_count; j < esw_attw->out_count; j++, i++)
		esw_setup_vpowt_dest(dest, fwow_act, esw, esw_attw, j, i, twue);
	wetuwn i;
}

static boow
esw_swc_powt_wewwite_suppowted(stwuct mwx5_eswitch *esw)
{
	wetuwn MWX5_CAP_GEN(esw->dev, weg_c_pwesewve) &&
	       mwx5_eswitch_vpowt_match_metadata_enabwed(esw) &&
	       MWX5_CAP_ESW_FWOWTABWE_FDB(esw->dev, ignowe_fwow_wevew);
}

static boow
esw_dests_to_vf_pf_vpowts(stwuct mwx5_fwow_destination *dests, int max_dest)
{
	boow vf_dest = fawse, pf_dest = fawse;
	int i;

	fow (i = 0; i < max_dest; i++) {
		if (dests[i].type != MWX5_FWOW_DESTINATION_TYPE_VPOWT)
			continue;

		if (dests[i].vpowt.num == MWX5_VPOWT_UPWINK)
			pf_dest = twue;
		ewse
			vf_dest = twue;

		if (vf_dest && pf_dest)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int
esw_setup_dests(stwuct mwx5_fwow_destination *dest,
		stwuct mwx5_fwow_act *fwow_act,
		stwuct mwx5_eswitch *esw,
		stwuct mwx5_fwow_attw *attw,
		stwuct mwx5_fwow_spec *spec,
		int *i)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	stwuct mwx5_fs_chains *chains = esw_chains(esw);
	int eww = 0;

	if (!mwx5_eswitch_tewmtbw_wequiwed(esw, attw, fwow_act, spec) &&
	    esw_swc_powt_wewwite_suppowted(esw))
		attw->fwags |= MWX5_ATTW_FWAG_SWC_WEWWITE;

	if (attw->fwags & MWX5_ATTW_FWAG_SWOW_PATH) {
		esw_setup_swow_path_dest(dest, fwow_act, esw, *i);
		(*i)++;
		goto out;
	}

	if (attw->fwags & MWX5_ATTW_FWAG_SAMPWE) {
		esw_setup_sampwew_dest(dest, fwow_act, attw->sampwe_attw.sampwew_id, *i);
		(*i)++;
	} ewse if (attw->fwags & MWX5_ATTW_FWAG_ACCEPT) {
		esw_setup_accept_dest(dest, fwow_act, chains, *i);
		(*i)++;
	} ewse if (attw->fwags & MWX5_ATTW_FWAG_MTU) {
		eww = esw_setup_mtu_dest(dest, &attw->metew_attw, *i);
		(*i)++;
	} ewse if (esw_is_indiw_tabwe(esw, attw)) {
		eww = esw_setup_indiw_tabwe(dest, fwow_act, esw, attw, i);
	} ewse if (esw_is_chain_swc_powt_wewwite(esw, esw_attw)) {
		eww = esw_setup_chain_swc_powt_wewwite(dest, fwow_act, esw, chains, attw, i);
	} ewse {
		*i = esw_setup_vpowt_dests(dest, fwow_act, esw, esw_attw, *i);

		if (attw->dest_ft) {
			eww = esw_setup_ft_dest(dest, fwow_act, esw, attw, *i);
			(*i)++;
		} ewse if (attw->dest_chain) {
			eww = esw_setup_chain_dest(dest, fwow_act, chains, attw->dest_chain,
						   1, 0, *i);
			(*i)++;
		}
	}

out:
	wetuwn eww;
}

static void
esw_cweanup_dests(stwuct mwx5_eswitch *esw,
		  stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	stwuct mwx5_fs_chains *chains = esw_chains(esw);

	if (attw->dest_ft) {
		esw_cweanup_decap_indiw(esw, attw);
	} ewse if (!mwx5e_tc_attw_fwags_skip(attw->fwags)) {
		if (attw->dest_chain)
			esw_cweanup_chain_dest(chains, attw->dest_chain, 1, 0);
		ewse if (esw_is_indiw_tabwe(esw, attw))
			esw_cweanup_indiw_tabwe(esw, attw);
		ewse if (esw_is_chain_swc_powt_wewwite(esw, esw_attw))
			esw_cweanup_chain_swc_powt_wewwite(esw, attw);
	}
}

static void
esw_setup_metew(stwuct mwx5_fwow_attw *attw, stwuct mwx5_fwow_act *fwow_act)
{
	stwuct mwx5e_fwow_metew_handwe *metew;

	metew = attw->metew_attw.metew;
	fwow_act->exe_aso.type = attw->exe_aso_type;
	fwow_act->exe_aso.object_id = metew->obj_id;
	fwow_act->exe_aso.fwow_metew.metew_idx = metew->idx;
	fwow_act->exe_aso.fwow_metew.init_cowow = MWX5_FWOW_METEW_COWOW_GWEEN;
	/* use metadata weg 5 fow packet cowow */
	fwow_act->exe_aso.wetuwn_weg_id = 5;
}

stwuct mwx5_fwow_handwe *
mwx5_eswitch_add_offwoaded_wuwe(stwuct mwx5_eswitch *esw,
				stwuct mwx5_fwow_spec *spec,
				stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_fwow_act fwow_act = { .fwags = FWOW_ACT_NO_APPEND, };
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	stwuct mwx5_fs_chains *chains = esw_chains(esw);
	boow spwit = !!(esw_attw->spwit_count);
	stwuct mwx5_vpowt_tbw_attw fwd_attw;
	stwuct mwx5_fwow_destination *dest;
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_tabwe *fdb;
	int i = 0;

	if (esw->mode != MWX5_ESWITCH_OFFWOADS)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if (!mwx5_eswitch_vwan_actions_suppowted(esw->dev, 1))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if (!esw_fwow_dests_fwd_ipsec_check(esw, esw_attw))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	dest = kcawwoc(MWX5_MAX_FWOW_FWD_VPOWTS + 1, sizeof(*dest), GFP_KEWNEW);
	if (!dest)
		wetuwn EWW_PTW(-ENOMEM);

	fwow_act.action = attw->action;

	if (fwow_act.action & MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH) {
		fwow_act.vwan[0].ethtype = ntohs(esw_attw->vwan_pwoto[0]);
		fwow_act.vwan[0].vid = esw_attw->vwan_vid[0];
		fwow_act.vwan[0].pwio = esw_attw->vwan_pwio[0];
		if (fwow_act.action & MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH_2) {
			fwow_act.vwan[1].ethtype = ntohs(esw_attw->vwan_pwoto[1]);
			fwow_act.vwan[1].vid = esw_attw->vwan_vid[1];
			fwow_act.vwan[1].pwio = esw_attw->vwan_pwio[1];
		}
	}

	mwx5_eswitch_set_wuwe_fwow_souwce(esw, spec, esw_attw);

	if (fwow_act.action & MWX5_FWOW_CONTEXT_ACTION_FWD_DEST) {
		int eww;

		eww = esw_setup_dests(dest, &fwow_act, esw, attw, spec, &i);
		if (eww) {
			wuwe = EWW_PTW(eww);
			goto eww_cweate_goto_tabwe;
		}

		/* Headew wewwite with combined wiwe+woopback in FDB is not awwowed */
		if ((fwow_act.action & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW) &&
		    esw_dests_to_vf_pf_vpowts(dest, i)) {
			esw_wawn(esw->dev,
				 "FDB: Headew wewwite with fowwawding to both PF and VF is not awwowed\n");
			wuwe = EWW_PTW(-EINVAW);
			goto eww_esw_get;
		}
	}

	if (esw_attw->decap_pkt_wefowmat)
		fwow_act.pkt_wefowmat = esw_attw->decap_pkt_wefowmat;

	if (fwow_act.action & MWX5_FWOW_CONTEXT_ACTION_COUNT) {
		dest[i].type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
		dest[i].countew_id = mwx5_fc_id(attw->countew);
		i++;
	}

	if (attw->outew_match_wevew != MWX5_MATCH_NONE)
		spec->match_cwitewia_enabwe |= MWX5_MATCH_OUTEW_HEADEWS;
	if (attw->innew_match_wevew != MWX5_MATCH_NONE)
		spec->match_cwitewia_enabwe |= MWX5_MATCH_INNEW_HEADEWS;

	if (fwow_act.action & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW)
		fwow_act.modify_hdw = attw->modify_hdw;

	if ((fwow_act.action & MWX5_FWOW_CONTEXT_ACTION_EXECUTE_ASO) &&
	    attw->exe_aso_type == MWX5_EXE_ASO_FWOW_METEW)
		esw_setup_metew(attw, &fwow_act);

	if (spwit) {
		fwd_attw.chain = attw->chain;
		fwd_attw.pwio = attw->pwio;
		fwd_attw.vpowt = esw_attw->in_wep->vpowt;
		fwd_attw.vpowt_ns = &mwx5_esw_vpowt_tbw_miwwow_ns;

		fdb = mwx5_esw_vpowttbw_get(esw, &fwd_attw);
	} ewse {
		if (attw->chain || attw->pwio)
			fdb = mwx5_chains_get_tabwe(chains, attw->chain,
						    attw->pwio, 0);
		ewse
			fdb = attw->ft;

		if (!(attw->fwags & MWX5_ATTW_FWAG_NO_IN_POWT))
			mwx5_eswitch_set_wuwe_souwce_powt(esw, spec, attw,
							  esw_attw->in_mdev->pwiv.eswitch,
							  esw_attw->in_wep->vpowt);
	}
	if (IS_EWW(fdb)) {
		wuwe = EWW_CAST(fdb);
		goto eww_esw_get;
	}

	if (!i) {
		kfwee(dest);
		dest = NUWW;
	}

	if (mwx5_eswitch_tewmtbw_wequiwed(esw, attw, &fwow_act, spec))
		wuwe = mwx5_eswitch_add_tewmtbw_wuwe(esw, fdb, spec, esw_attw,
						     &fwow_act, dest, i);
	ewse
		wuwe = mwx5_add_fwow_wuwes(fdb, spec, &fwow_act, dest, i);
	if (IS_EWW(wuwe))
		goto eww_add_wuwe;
	ewse
		atomic64_inc(&esw->offwoads.num_fwows);

	kfwee(dest);
	wetuwn wuwe;

eww_add_wuwe:
	if (spwit)
		mwx5_esw_vpowttbw_put(esw, &fwd_attw);
	ewse if (attw->chain || attw->pwio)
		mwx5_chains_put_tabwe(chains, attw->chain, attw->pwio, 0);
eww_esw_get:
	esw_cweanup_dests(esw, attw);
eww_cweate_goto_tabwe:
	kfwee(dest);
	wetuwn wuwe;
}

stwuct mwx5_fwow_handwe *
mwx5_eswitch_add_fwd_wuwe(stwuct mwx5_eswitch *esw,
			  stwuct mwx5_fwow_spec *spec,
			  stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_fwow_act fwow_act = { .fwags = FWOW_ACT_NO_APPEND, };
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	stwuct mwx5_fs_chains *chains = esw_chains(esw);
	stwuct mwx5_vpowt_tbw_attw fwd_attw;
	stwuct mwx5_fwow_destination *dest;
	stwuct mwx5_fwow_tabwe *fast_fdb;
	stwuct mwx5_fwow_tabwe *fwd_fdb;
	stwuct mwx5_fwow_handwe *wuwe;
	int i, eww = 0;

	dest = kcawwoc(MWX5_MAX_FWOW_FWD_VPOWTS + 1, sizeof(*dest), GFP_KEWNEW);
	if (!dest)
		wetuwn EWW_PTW(-ENOMEM);

	fast_fdb = mwx5_chains_get_tabwe(chains, attw->chain, attw->pwio, 0);
	if (IS_EWW(fast_fdb)) {
		wuwe = EWW_CAST(fast_fdb);
		goto eww_get_fast;
	}

	fwd_attw.chain = attw->chain;
	fwd_attw.pwio = attw->pwio;
	fwd_attw.vpowt = esw_attw->in_wep->vpowt;
	fwd_attw.vpowt_ns = &mwx5_esw_vpowt_tbw_miwwow_ns;
	fwd_fdb = mwx5_esw_vpowttbw_get(esw, &fwd_attw);
	if (IS_EWW(fwd_fdb)) {
		wuwe = EWW_CAST(fwd_fdb);
		goto eww_get_fwd;
	}

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	fow (i = 0; i < esw_attw->spwit_count; i++) {
		if (esw_attw->dests[i].fwags & MWX5_ESW_DEST_CHAIN_WITH_SWC_POWT_CHANGE)
			/* Souwce powt wewwite (fowwawd to ovs intewnaw powt ow statck device) isn't
			 * suppowted in the wuwe of spwit action.
			 */
			eww = -EOPNOTSUPP;
		ewse
			esw_setup_vpowt_dest(dest, &fwow_act, esw, esw_attw, i, i, fawse);

		if (eww) {
			wuwe = EWW_PTW(eww);
			goto eww_chain_swc_wewwite;
		}
	}
	dest[i].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest[i].ft = fwd_fdb;
	i++;

	mwx5_eswitch_set_wuwe_souwce_powt(esw, spec, attw,
					  esw_attw->in_mdev->pwiv.eswitch,
					  esw_attw->in_wep->vpowt);

	if (attw->outew_match_wevew != MWX5_MATCH_NONE)
		spec->match_cwitewia_enabwe |= MWX5_MATCH_OUTEW_HEADEWS;

	fwow_act.fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;
	wuwe = mwx5_add_fwow_wuwes(fast_fdb, spec, &fwow_act, dest, i);

	if (IS_EWW(wuwe)) {
		i = esw_attw->spwit_count;
		goto eww_chain_swc_wewwite;
	}

	atomic64_inc(&esw->offwoads.num_fwows);

	kfwee(dest);
	wetuwn wuwe;
eww_chain_swc_wewwite:
	mwx5_esw_vpowttbw_put(esw, &fwd_attw);
eww_get_fwd:
	mwx5_chains_put_tabwe(chains, attw->chain, attw->pwio, 0);
eww_get_fast:
	kfwee(dest);
	wetuwn wuwe;
}

static void
__mwx5_eswitch_dew_wuwe(stwuct mwx5_eswitch *esw,
			stwuct mwx5_fwow_handwe *wuwe,
			stwuct mwx5_fwow_attw *attw,
			boow fwd_wuwe)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	stwuct mwx5_fs_chains *chains = esw_chains(esw);
	boow spwit = (esw_attw->spwit_count > 0);
	stwuct mwx5_vpowt_tbw_attw fwd_attw;
	int i;

	mwx5_dew_fwow_wuwes(wuwe);

	if (!mwx5e_tc_attw_fwags_skip(attw->fwags)) {
		/* unwef the tewm tabwe */
		fow (i = 0; i < MWX5_MAX_FWOW_FWD_VPOWTS; i++) {
			if (esw_attw->dests[i].tewmtbw)
				mwx5_eswitch_tewmtbw_put(esw, esw_attw->dests[i].tewmtbw);
		}
	}

	atomic64_dec(&esw->offwoads.num_fwows);

	if (fwd_wuwe || spwit) {
		fwd_attw.chain = attw->chain;
		fwd_attw.pwio = attw->pwio;
		fwd_attw.vpowt = esw_attw->in_wep->vpowt;
		fwd_attw.vpowt_ns = &mwx5_esw_vpowt_tbw_miwwow_ns;
	}

	if (fwd_wuwe)  {
		mwx5_esw_vpowttbw_put(esw, &fwd_attw);
		mwx5_chains_put_tabwe(chains, attw->chain, attw->pwio, 0);
	} ewse {
		if (spwit)
			mwx5_esw_vpowttbw_put(esw, &fwd_attw);
		ewse if (attw->chain || attw->pwio)
			mwx5_chains_put_tabwe(chains, attw->chain, attw->pwio, 0);
		esw_cweanup_dests(esw, attw);
	}
}

void
mwx5_eswitch_dew_offwoaded_wuwe(stwuct mwx5_eswitch *esw,
				stwuct mwx5_fwow_handwe *wuwe,
				stwuct mwx5_fwow_attw *attw)
{
	__mwx5_eswitch_dew_wuwe(esw, wuwe, attw, fawse);
}

void
mwx5_eswitch_dew_fwd_wuwe(stwuct mwx5_eswitch *esw,
			  stwuct mwx5_fwow_handwe *wuwe,
			  stwuct mwx5_fwow_attw *attw)
{
	__mwx5_eswitch_dew_wuwe(esw, wuwe, attw, twue);
}

stwuct mwx5_fwow_handwe *
mwx5_eswitch_add_send_to_vpowt_wuwe(stwuct mwx5_eswitch *on_esw,
				    stwuct mwx5_eswitch *fwom_esw,
				    stwuct mwx5_eswitch_wep *wep,
				    u32 sqn)
{
	stwuct mwx5_fwow_act fwow_act = {0};
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_handwe *fwow_wuwe;
	stwuct mwx5_fwow_spec *spec;
	void *misc;
	u16 vpowt;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec) {
		fwow_wuwe = EWW_PTW(-ENOMEM);
		goto out;
	}

	misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews);
	MWX5_SET(fte_match_set_misc, misc, souwce_sqn, sqn);

	misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews);
	MWX5_SET_TO_ONES(fte_match_set_misc, misc, souwce_sqn);

	spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS;

	/* souwce vpowt is the esw managew */
	vpowt = fwom_esw->managew_vpowt;

	if (mwx5_eswitch_vpowt_match_metadata_enabwed(on_esw)) {
		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews_2);
		MWX5_SET(fte_match_set_misc2, misc, metadata_weg_c_0,
			 mwx5_eswitch_get_vpowt_metadata_fow_match(fwom_esw, vpowt));

		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2);
		MWX5_SET(fte_match_set_misc2, misc, metadata_weg_c_0,
			 mwx5_eswitch_get_vpowt_metadata_mask());

		spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_2;
	} ewse {
		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews);
		MWX5_SET(fte_match_set_misc, misc, souwce_powt, vpowt);

		if (MWX5_CAP_ESW(on_esw->dev, mewged_eswitch))
			MWX5_SET(fte_match_set_misc, misc, souwce_eswitch_ownew_vhca_id,
				 MWX5_CAP_GEN(fwom_esw->dev, vhca_id));

		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews);
		MWX5_SET_TO_ONES(fte_match_set_misc, misc, souwce_powt);

		if (MWX5_CAP_ESW(on_esw->dev, mewged_eswitch))
			MWX5_SET_TO_ONES(fte_match_set_misc, misc,
					 souwce_eswitch_ownew_vhca_id);

		spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS;
	}

	dest.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
	dest.vpowt.num = wep->vpowt;
	dest.vpowt.vhca_id = MWX5_CAP_GEN(wep->esw->dev, vhca_id);
	dest.vpowt.fwags |= MWX5_FWOW_DEST_VPOWT_VHCA_ID;
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;

	if (wep->vpowt == MWX5_VPOWT_UPWINK &&
	    on_esw == fwom_esw && on_esw->offwoads.ft_ipsec_tx_pow) {
		dest.ft = on_esw->offwoads.ft_ipsec_tx_pow;
		fwow_act.fwags = FWOW_ACT_IGNOWE_FWOW_WEVEW;
		dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	} ewse {
		dest.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
		dest.vpowt.num = wep->vpowt;
		dest.vpowt.vhca_id = MWX5_CAP_GEN(wep->esw->dev, vhca_id);
		dest.vpowt.fwags |= MWX5_FWOW_DEST_VPOWT_VHCA_ID;
	}

	if (MWX5_CAP_ESW_FWOWTABWE(on_esw->dev, fwow_souwce) &&
	    wep->vpowt == MWX5_VPOWT_UPWINK)
		spec->fwow_context.fwow_souwce = MWX5_FWOW_CONTEXT_FWOW_SOUWCE_WOCAW_VPOWT;

	fwow_wuwe = mwx5_add_fwow_wuwes(mwx5_eswitch_get_swow_fdb(on_esw),
					spec, &fwow_act, &dest, 1);
	if (IS_EWW(fwow_wuwe))
		esw_wawn(on_esw->dev, "FDB: Faiwed to add send to vpowt wuwe eww %wd\n",
			 PTW_EWW(fwow_wuwe));
out:
	kvfwee(spec);
	wetuwn fwow_wuwe;
}
EXPOWT_SYMBOW(mwx5_eswitch_add_send_to_vpowt_wuwe);

void mwx5_eswitch_dew_send_to_vpowt_wuwe(stwuct mwx5_fwow_handwe *wuwe)
{
	mwx5_dew_fwow_wuwes(wuwe);
}

void mwx5_eswitch_dew_send_to_vpowt_meta_wuwe(stwuct mwx5_fwow_handwe *wuwe)
{
	if (wuwe)
		mwx5_dew_fwow_wuwes(wuwe);
}

stwuct mwx5_fwow_handwe *
mwx5_eswitch_add_send_to_vpowt_meta_wuwe(stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act fwow_act = {0};
	stwuct mwx5_fwow_handwe *fwow_wuwe;
	stwuct mwx5_fwow_spec *spec;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(fte_match_pawam, spec->match_cwitewia,
		 misc_pawametews_2.metadata_weg_c_0, mwx5_eswitch_get_vpowt_metadata_mask());
	MWX5_SET(fte_match_pawam, spec->match_cwitewia,
		 misc_pawametews_2.metadata_weg_c_1, ESW_TUN_MASK);
	MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_2.metadata_weg_c_1,
		 ESW_TUN_SWOW_TABWE_GOTO_VPOWT_MAWK);

	spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS_2;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;

	MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews_2.metadata_weg_c_0,
		 mwx5_eswitch_get_vpowt_metadata_fow_match(esw, vpowt_num));
	dest.vpowt.num = vpowt_num;

	fwow_wuwe = mwx5_add_fwow_wuwes(mwx5_eswitch_get_swow_fdb(esw),
					spec, &fwow_act, &dest, 1);
	if (IS_EWW(fwow_wuwe))
		esw_wawn(esw->dev, "FDB: Faiwed to add send to vpowt meta wuwe vpowt %d, eww %wd\n",
			 vpowt_num, PTW_EWW(fwow_wuwe));

	kvfwee(spec);
	wetuwn fwow_wuwe;
}

static boow mwx5_eswitch_weg_c1_woopback_suppowted(stwuct mwx5_eswitch *esw)
{
	wetuwn MWX5_CAP_ESW_FWOWTABWE(esw->dev, fdb_to_vpowt_weg_c_id) &
	       MWX5_FDB_TO_VPOWT_WEG_C_1;
}

static int esw_set_passing_vpowt_metadata(stwuct mwx5_eswitch *esw, boow enabwe)
{
	u32 out[MWX5_ST_SZ_DW(quewy_esw_vpowt_context_out)] = {};
	u32 min[MWX5_ST_SZ_DW(modify_esw_vpowt_context_in)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_esw_vpowt_context_in)] = {};
	u8 cuww, wanted;
	int eww;

	if (!mwx5_eswitch_weg_c1_woopback_suppowted(esw) &&
	    !mwx5_eswitch_vpowt_match_metadata_enabwed(esw))
		wetuwn 0;

	MWX5_SET(quewy_esw_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_ESW_VPOWT_CONTEXT);
	eww = mwx5_cmd_exec_inout(esw->dev, quewy_esw_vpowt_context, in, out);
	if (eww)
		wetuwn eww;

	cuww = MWX5_GET(quewy_esw_vpowt_context_out, out,
			esw_vpowt_context.fdb_to_vpowt_weg_c_id);
	wanted = MWX5_FDB_TO_VPOWT_WEG_C_0;
	if (mwx5_eswitch_weg_c1_woopback_suppowted(esw))
		wanted |= MWX5_FDB_TO_VPOWT_WEG_C_1;

	if (enabwe)
		cuww |= wanted;
	ewse
		cuww &= ~wanted;

	MWX5_SET(modify_esw_vpowt_context_in, min,
		 esw_vpowt_context.fdb_to_vpowt_weg_c_id, cuww);
	MWX5_SET(modify_esw_vpowt_context_in, min,
		 fiewd_sewect.fdb_to_vpowt_weg_c_id, 1);

	eww = mwx5_eswitch_modify_esw_vpowt_context(esw->dev, 0, fawse, min);
	if (!eww) {
		if (enabwe && (cuww & MWX5_FDB_TO_VPOWT_WEG_C_1))
			esw->fwags |= MWX5_ESWITCH_WEG_C1_WOOPBACK_ENABWED;
		ewse
			esw->fwags &= ~MWX5_ESWITCH_WEG_C1_WOOPBACK_ENABWED;
	}

	wetuwn eww;
}

static void peew_miss_wuwes_setup(stwuct mwx5_eswitch *esw,
				  stwuct mwx5_cowe_dev *peew_dev,
				  stwuct mwx5_fwow_spec *spec,
				  stwuct mwx5_fwow_destination *dest)
{
	void *misc;

	if (mwx5_eswitch_vpowt_match_metadata_enabwed(esw)) {
		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				    misc_pawametews_2);
		MWX5_SET(fte_match_set_misc2, misc, metadata_weg_c_0,
			 mwx5_eswitch_get_vpowt_metadata_mask());

		spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS_2;
	} ewse {
		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    misc_pawametews);

		MWX5_SET(fte_match_set_misc, misc, souwce_eswitch_ownew_vhca_id,
			 MWX5_CAP_GEN(peew_dev, vhca_id));

		spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS;

		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				    misc_pawametews);
		MWX5_SET_TO_ONES(fte_match_set_misc, misc, souwce_powt);
		MWX5_SET_TO_ONES(fte_match_set_misc, misc,
				 souwce_eswitch_ownew_vhca_id);
	}

	dest->type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
	dest->vpowt.num = peew_dev->pwiv.eswitch->managew_vpowt;
	dest->vpowt.vhca_id = MWX5_CAP_GEN(peew_dev, vhca_id);
	dest->vpowt.fwags |= MWX5_FWOW_DEST_VPOWT_VHCA_ID;
}

static void esw_set_peew_miss_wuwe_souwce_powt(stwuct mwx5_eswitch *esw,
					       stwuct mwx5_eswitch *peew_esw,
					       stwuct mwx5_fwow_spec *spec,
					       u16 vpowt)
{
	void *misc;

	if (mwx5_eswitch_vpowt_match_metadata_enabwed(esw)) {
		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    misc_pawametews_2);
		MWX5_SET(fte_match_set_misc2, misc, metadata_weg_c_0,
			 mwx5_eswitch_get_vpowt_metadata_fow_match(peew_esw,
								   vpowt));
	} ewse {
		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    misc_pawametews);
		MWX5_SET(fte_match_set_misc, misc, souwce_powt, vpowt);
	}
}

static int esw_add_fdb_peew_miss_wuwes(stwuct mwx5_eswitch *esw,
				       stwuct mwx5_cowe_dev *peew_dev)
{
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act fwow_act = {0};
	stwuct mwx5_fwow_handwe **fwows;
	/* totaw vpowts is the same fow both e-switches */
	int nvpowts = esw->totaw_vpowts;
	stwuct mwx5_fwow_handwe *fwow;
	stwuct mwx5_fwow_spec *spec;
	stwuct mwx5_vpowt *vpowt;
	int eww, pfindex;
	unsigned wong i;
	void *misc;

	if (!MWX5_VPOWT_MANAGEW(esw->dev) && !mwx5_cowe_is_ecpf_esw_managew(esw->dev))
		wetuwn 0;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	peew_miss_wuwes_setup(esw, peew_dev, spec, &dest);

	fwows = kvcawwoc(nvpowts, sizeof(*fwows), GFP_KEWNEW);
	if (!fwows) {
		eww = -ENOMEM;
		goto awwoc_fwows_eww;
	}

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
			    misc_pawametews);

	if (mwx5_cowe_is_ecpf_esw_managew(esw->dev)) {
		vpowt = mwx5_eswitch_get_vpowt(esw, MWX5_VPOWT_PF);
		esw_set_peew_miss_wuwe_souwce_powt(esw, peew_dev->pwiv.eswitch,
						   spec, MWX5_VPOWT_PF);

		fwow = mwx5_add_fwow_wuwes(mwx5_eswitch_get_swow_fdb(esw),
					   spec, &fwow_act, &dest, 1);
		if (IS_EWW(fwow)) {
			eww = PTW_EWW(fwow);
			goto add_pf_fwow_eww;
		}
		fwows[vpowt->index] = fwow;
	}

	if (mwx5_ecpf_vpowt_exists(esw->dev)) {
		vpowt = mwx5_eswitch_get_vpowt(esw, MWX5_VPOWT_ECPF);
		MWX5_SET(fte_match_set_misc, misc, souwce_powt, MWX5_VPOWT_ECPF);
		fwow = mwx5_add_fwow_wuwes(mwx5_eswitch_get_swow_fdb(esw),
					   spec, &fwow_act, &dest, 1);
		if (IS_EWW(fwow)) {
			eww = PTW_EWW(fwow);
			goto add_ecpf_fwow_eww;
		}
		fwows[vpowt->index] = fwow;
	}

	mwx5_esw_fow_each_vf_vpowt(esw, i, vpowt, mwx5_cowe_max_vfs(esw->dev)) {
		esw_set_peew_miss_wuwe_souwce_powt(esw,
						   peew_dev->pwiv.eswitch,
						   spec, vpowt->vpowt);

		fwow = mwx5_add_fwow_wuwes(mwx5_eswitch_get_swow_fdb(esw),
					   spec, &fwow_act, &dest, 1);
		if (IS_EWW(fwow)) {
			eww = PTW_EWW(fwow);
			goto add_vf_fwow_eww;
		}
		fwows[vpowt->index] = fwow;
	}

	if (mwx5_cowe_ec_swiov_enabwed(esw->dev)) {
		mwx5_esw_fow_each_ec_vf_vpowt(esw, i, vpowt, mwx5_cowe_max_ec_vfs(esw->dev)) {
			if (i >= mwx5_cowe_max_ec_vfs(peew_dev))
				bweak;
			esw_set_peew_miss_wuwe_souwce_powt(esw, peew_dev->pwiv.eswitch,
							   spec, vpowt->vpowt);
			fwow = mwx5_add_fwow_wuwes(esw->fdb_tabwe.offwoads.swow_fdb,
						   spec, &fwow_act, &dest, 1);
			if (IS_EWW(fwow)) {
				eww = PTW_EWW(fwow);
				goto add_ec_vf_fwow_eww;
			}
			fwows[vpowt->index] = fwow;
		}
	}

	pfindex = mwx5_get_dev_index(peew_dev);
	if (pfindex >= MWX5_MAX_POWTS) {
		esw_wawn(esw->dev, "Peew dev index(%d) is ovew the max num defined(%d)\n",
			 pfindex, MWX5_MAX_POWTS);
		eww = -EINVAW;
		goto add_ec_vf_fwow_eww;
	}
	esw->fdb_tabwe.offwoads.peew_miss_wuwes[pfindex] = fwows;

	kvfwee(spec);
	wetuwn 0;

add_ec_vf_fwow_eww:
	mwx5_esw_fow_each_ec_vf_vpowt(esw, i, vpowt, mwx5_cowe_max_ec_vfs(esw->dev)) {
		if (!fwows[vpowt->index])
			continue;
		mwx5_dew_fwow_wuwes(fwows[vpowt->index]);
	}
add_vf_fwow_eww:
	mwx5_esw_fow_each_vf_vpowt(esw, i, vpowt, mwx5_cowe_max_vfs(esw->dev)) {
		if (!fwows[vpowt->index])
			continue;
		mwx5_dew_fwow_wuwes(fwows[vpowt->index]);
	}
	if (mwx5_ecpf_vpowt_exists(esw->dev)) {
		vpowt = mwx5_eswitch_get_vpowt(esw, MWX5_VPOWT_ECPF);
		mwx5_dew_fwow_wuwes(fwows[vpowt->index]);
	}
add_ecpf_fwow_eww:
	if (mwx5_cowe_is_ecpf_esw_managew(esw->dev)) {
		vpowt = mwx5_eswitch_get_vpowt(esw, MWX5_VPOWT_PF);
		mwx5_dew_fwow_wuwes(fwows[vpowt->index]);
	}
add_pf_fwow_eww:
	esw_wawn(esw->dev, "FDB: Faiwed to add peew miss fwow wuwe eww %d\n", eww);
	kvfwee(fwows);
awwoc_fwows_eww:
	kvfwee(spec);
	wetuwn eww;
}

static void esw_dew_fdb_peew_miss_wuwes(stwuct mwx5_eswitch *esw,
					stwuct mwx5_cowe_dev *peew_dev)
{
	u16 peew_index = mwx5_get_dev_index(peew_dev);
	stwuct mwx5_fwow_handwe **fwows;
	stwuct mwx5_vpowt *vpowt;
	unsigned wong i;

	fwows = esw->fdb_tabwe.offwoads.peew_miss_wuwes[peew_index];
	if (!fwows)
		wetuwn;

	if (mwx5_cowe_ec_swiov_enabwed(esw->dev)) {
		mwx5_esw_fow_each_ec_vf_vpowt(esw, i, vpowt, mwx5_cowe_max_ec_vfs(esw->dev)) {
			/* The fwow fow a pawticuwaw vpowt couwd be NUWW if the othew ECPF
			 * has fewew ow no VFs enabwed
			 */
			if (!fwows[vpowt->index])
				continue;
			mwx5_dew_fwow_wuwes(fwows[vpowt->index]);
		}
	}

	mwx5_esw_fow_each_vf_vpowt(esw, i, vpowt, mwx5_cowe_max_vfs(esw->dev))
		mwx5_dew_fwow_wuwes(fwows[vpowt->index]);

	if (mwx5_ecpf_vpowt_exists(esw->dev)) {
		vpowt = mwx5_eswitch_get_vpowt(esw, MWX5_VPOWT_ECPF);
		mwx5_dew_fwow_wuwes(fwows[vpowt->index]);
	}

	if (mwx5_cowe_is_ecpf_esw_managew(esw->dev)) {
		vpowt = mwx5_eswitch_get_vpowt(esw, MWX5_VPOWT_PF);
		mwx5_dew_fwow_wuwes(fwows[vpowt->index]);
	}

	kvfwee(fwows);
	esw->fdb_tabwe.offwoads.peew_miss_wuwes[peew_index] = NUWW;
}

static int esw_add_fdb_miss_wuwe(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_fwow_act fwow_act = {0};
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_handwe *fwow_wuwe = NUWW;
	stwuct mwx5_fwow_spec *spec;
	void *headews_c;
	void *headews_v;
	int eww = 0;
	u8 *dmac_c;
	u8 *dmac_v;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec) {
		eww = -ENOMEM;
		goto out;
	}

	spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
	headews_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				 outew_headews);
	dmac_c = MWX5_ADDW_OF(fte_match_pawam, headews_c,
			      outew_headews.dmac_47_16);
	dmac_c[0] = 0x01;

	dest.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
	dest.vpowt.num = esw->managew_vpowt;
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;

	fwow_wuwe = mwx5_add_fwow_wuwes(mwx5_eswitch_get_swow_fdb(esw),
					spec, &fwow_act, &dest, 1);
	if (IS_EWW(fwow_wuwe)) {
		eww = PTW_EWW(fwow_wuwe);
		esw_wawn(esw->dev,  "FDB: Faiwed to add unicast miss fwow wuwe eww %d\n", eww);
		goto out;
	}

	esw->fdb_tabwe.offwoads.miss_wuwe_uni = fwow_wuwe;

	headews_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				 outew_headews);
	dmac_v = MWX5_ADDW_OF(fte_match_pawam, headews_v,
			      outew_headews.dmac_47_16);
	dmac_v[0] = 0x01;
	fwow_wuwe = mwx5_add_fwow_wuwes(mwx5_eswitch_get_swow_fdb(esw),
					spec, &fwow_act, &dest, 1);
	if (IS_EWW(fwow_wuwe)) {
		eww = PTW_EWW(fwow_wuwe);
		esw_wawn(esw->dev, "FDB: Faiwed to add muwticast miss fwow wuwe eww %d\n", eww);
		mwx5_dew_fwow_wuwes(esw->fdb_tabwe.offwoads.miss_wuwe_uni);
		goto out;
	}

	esw->fdb_tabwe.offwoads.miss_wuwe_muwti = fwow_wuwe;

out:
	kvfwee(spec);
	wetuwn eww;
}

stwuct mwx5_fwow_handwe *
esw_add_westowe_wuwe(stwuct mwx5_eswitch *esw, u32 tag)
{
	stwuct mwx5_fwow_act fwow_act = { .fwags = FWOW_ACT_NO_APPEND, };
	stwuct mwx5_fwow_tabwe *ft = esw->offwoads.ft_offwoads_westowe;
	stwuct mwx5_fwow_context *fwow_context;
	stwuct mwx5_fwow_handwe *fwow_wuwe;
	stwuct mwx5_fwow_destination dest;
	stwuct mwx5_fwow_spec *spec;
	void *misc;

	if (!mwx5_eswitch_weg_c1_woopback_suppowted(esw))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn EWW_PTW(-ENOMEM);

	misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
			    misc_pawametews_2);
	MWX5_SET(fte_match_set_misc2, misc, metadata_weg_c_0,
		 ESW_WEG_C0_USEW_DATA_METADATA_MASK);
	misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
			    misc_pawametews_2);
	MWX5_SET(fte_match_set_misc2, misc, metadata_weg_c_0, tag);
	spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS_2;
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST |
			  MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
	fwow_act.modify_hdw = esw->offwoads.westowe_copy_hdw_id;

	fwow_context = &spec->fwow_context;
	fwow_context->fwags |= FWOW_CONTEXT_HAS_TAG;
	fwow_context->fwow_tag = tag;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = esw->offwoads.ft_offwoads;

	fwow_wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, &dest, 1);
	kvfwee(spec);

	if (IS_EWW(fwow_wuwe))
		esw_wawn(esw->dev,
			 "Faiwed to cweate westowe wuwe fow tag: %d, eww(%d)\n",
			 tag, (int)PTW_EWW(fwow_wuwe));

	wetuwn fwow_wuwe;
}

#define MAX_PF_SQ 256
#define MAX_SQ_NVPOWTS 32

void
mwx5_esw_set_fwow_gwoup_souwce_powt(stwuct mwx5_eswitch *esw,
				    u32 *fwow_gwoup_in,
				    int match_pawams)
{
	void *match_cwitewia = MWX5_ADDW_OF(cweate_fwow_gwoup_in,
					    fwow_gwoup_in,
					    match_cwitewia);

	if (mwx5_eswitch_vpowt_match_metadata_enabwed(esw)) {
		MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in,
			 match_cwitewia_enabwe,
			 MWX5_MATCH_MISC_PAWAMETEWS_2 | match_pawams);

		MWX5_SET(fte_match_pawam, match_cwitewia,
			 misc_pawametews_2.metadata_weg_c_0,
			 mwx5_eswitch_get_vpowt_metadata_mask());
	} ewse {
		MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in,
			 match_cwitewia_enabwe,
			 MWX5_MATCH_MISC_PAWAMETEWS | match_pawams);

		MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia,
				 misc_pawametews.souwce_powt);
	}
}

#if IS_ENABWED(CONFIG_MWX5_CWS_ACT)
static void esw_vpowt_tbw_put(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_vpowt_tbw_attw attw;
	stwuct mwx5_vpowt *vpowt;
	unsigned wong i;

	attw.chain = 0;
	attw.pwio = 1;
	mwx5_esw_fow_each_vpowt(esw, i, vpowt) {
		attw.vpowt = vpowt->vpowt;
		attw.vpowt_ns = &mwx5_esw_vpowt_tbw_miwwow_ns;
		mwx5_esw_vpowttbw_put(esw, &attw);
	}
}

static int esw_vpowt_tbw_get(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_vpowt_tbw_attw attw;
	stwuct mwx5_fwow_tabwe *fdb;
	stwuct mwx5_vpowt *vpowt;
	unsigned wong i;

	attw.chain = 0;
	attw.pwio = 1;
	mwx5_esw_fow_each_vpowt(esw, i, vpowt) {
		attw.vpowt = vpowt->vpowt;
		attw.vpowt_ns = &mwx5_esw_vpowt_tbw_miwwow_ns;
		fdb = mwx5_esw_vpowttbw_get(esw, &attw);
		if (IS_EWW(fdb))
			goto out;
	}
	wetuwn 0;

out:
	esw_vpowt_tbw_put(esw);
	wetuwn PTW_EWW(fdb);
}

#define fdb_modify_headew_fwd_to_tabwe_suppowted(esw) \
	(MWX5_CAP_ESW_FWOWTABWE((esw)->dev, fdb_modify_headew_fwd_to_tabwe))
static void esw_init_chains_offwoad_fwags(stwuct mwx5_eswitch *esw, u32 *fwags)
{
	stwuct mwx5_cowe_dev *dev = esw->dev;

	if (MWX5_CAP_ESW_FWOWTABWE_FDB(dev, ignowe_fwow_wevew))
		*fwags |= MWX5_CHAINS_IGNOWE_FWOW_WEVEW_SUPPOWTED;

	if (!MWX5_CAP_ESW_FWOWTABWE(dev, muwti_fdb_encap) &&
	    esw->offwoads.encap != DEVWINK_ESWITCH_ENCAP_MODE_NONE) {
		*fwags &= ~MWX5_CHAINS_AND_PWIOS_SUPPOWTED;
		esw_wawn(dev, "Tc chains and pwiowities offwoad awen't suppowted, update fiwmwawe if needed\n");
	} ewse if (!mwx5_eswitch_weg_c1_woopback_enabwed(esw)) {
		*fwags &= ~MWX5_CHAINS_AND_PWIOS_SUPPOWTED;
		esw_wawn(dev, "Tc chains and pwiowities offwoad awen't suppowted\n");
	} ewse if (!fdb_modify_headew_fwd_to_tabwe_suppowted(esw)) {
		/* Disabwed when ttw wowkawound is needed, e.g
		 * when ESWITCH_IPV4_TTW_MODIFY_ENABWE = twue in mwxconfig
		 */
		esw_wawn(dev,
			 "Tc chains and pwiowities offwoad awen't suppowted, check fiwmwawe vewsion, ow mwxconfig settings\n");
		*fwags &= ~MWX5_CHAINS_AND_PWIOS_SUPPOWTED;
	} ewse {
		*fwags |= MWX5_CHAINS_AND_PWIOS_SUPPOWTED;
		esw_info(dev, "Suppowted tc chains and pwios offwoad\n");
	}

	if (esw->offwoads.encap != DEVWINK_ESWITCH_ENCAP_MODE_NONE)
		*fwags |= MWX5_CHAINS_FT_TUNNEW_SUPPOWTED;
}

static int
esw_chains_cweate(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_tabwe *miss_fdb)
{
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct mwx5_fwow_tabwe *nf_ft, *ft;
	stwuct mwx5_chains_attw attw = {};
	stwuct mwx5_fs_chains *chains;
	int eww;

	esw_init_chains_offwoad_fwags(esw, &attw.fwags);
	attw.ns = MWX5_FWOW_NAMESPACE_FDB;
	attw.max_gwp_num = esw->pawams.wawge_gwoup_num;
	attw.defauwt_ft = miss_fdb;
	attw.mapping = esw->offwoads.weg_c0_obj_poow;

	chains = mwx5_chains_cweate(dev, &attw);
	if (IS_EWW(chains)) {
		eww = PTW_EWW(chains);
		esw_wawn(dev, "Faiwed to cweate fdb chains eww(%d)\n", eww);
		wetuwn eww;
	}
	mwx5_chains_pwint_info(chains);

	esw->fdb_tabwe.offwoads.esw_chains_pwiv = chains;

	/* Cweate tc_end_ft which is the awways cweated ft chain */
	nf_ft = mwx5_chains_get_tabwe(chains, mwx5_chains_get_nf_ft_chain(chains),
				      1, 0);
	if (IS_EWW(nf_ft)) {
		eww = PTW_EWW(nf_ft);
		goto nf_ft_eww;
	}

	/* Awways open the woot fow fast path */
	ft = mwx5_chains_get_tabwe(chains, 0, 1, 0);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		goto wevew_0_eww;
	}

	/* Open wevew 1 fow spwit fdb wuwes now if pwios isn't suppowted  */
	if (!mwx5_chains_pwios_suppowted(chains)) {
		eww = esw_vpowt_tbw_get(esw);
		if (eww)
			goto wevew_1_eww;
	}

	mwx5_chains_set_end_ft(chains, nf_ft);

	wetuwn 0;

wevew_1_eww:
	mwx5_chains_put_tabwe(chains, 0, 1, 0);
wevew_0_eww:
	mwx5_chains_put_tabwe(chains, mwx5_chains_get_nf_ft_chain(chains), 1, 0);
nf_ft_eww:
	mwx5_chains_destwoy(chains);
	esw->fdb_tabwe.offwoads.esw_chains_pwiv = NUWW;

	wetuwn eww;
}

static void
esw_chains_destwoy(stwuct mwx5_eswitch *esw, stwuct mwx5_fs_chains *chains)
{
	if (!mwx5_chains_pwios_suppowted(chains))
		esw_vpowt_tbw_put(esw);
	mwx5_chains_put_tabwe(chains, 0, 1, 0);
	mwx5_chains_put_tabwe(chains, mwx5_chains_get_nf_ft_chain(chains), 1, 0);
	mwx5_chains_destwoy(chains);
}

#ewse /* CONFIG_MWX5_CWS_ACT */

static int
esw_chains_cweate(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_tabwe *miss_fdb)
{ wetuwn 0; }

static void
esw_chains_destwoy(stwuct mwx5_eswitch *esw, stwuct mwx5_fs_chains *chains)
{}

#endif

static int
esw_cweate_send_to_vpowt_gwoup(stwuct mwx5_eswitch *esw,
			       stwuct mwx5_fwow_tabwe *fdb,
			       u32 *fwow_gwoup_in,
			       int *ix)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *g;
	void *match_cwitewia;
	int count, eww = 0;

	memset(fwow_gwoup_in, 0, inwen);

	mwx5_esw_set_fwow_gwoup_souwce_powt(esw, fwow_gwoup_in, MWX5_MATCH_MISC_PAWAMETEWS);

	match_cwitewia = MWX5_ADDW_OF(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia);
	MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia, misc_pawametews.souwce_sqn);

	if (!mwx5_eswitch_vpowt_match_metadata_enabwed(esw) &&
	    MWX5_CAP_ESW(esw->dev, mewged_eswitch)) {
		MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia,
				 misc_pawametews.souwce_eswitch_ownew_vhca_id);
		MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in,
			 souwce_eswitch_ownew_vhca_id_vawid, 1);
	}

	/* See comment at tabwe_size cawcuwation */
	count = MWX5_MAX_POWTS * (esw->totaw_vpowts * MAX_SQ_NVPOWTS + MAX_PF_SQ);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, 0);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, *ix + count - 1);
	*ix += count;

	g = mwx5_cweate_fwow_gwoup(fdb, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		esw_wawn(esw->dev, "Faiwed to cweate send-to-vpowt fwow gwoup eww(%d)\n", eww);
		goto out;
	}
	esw->fdb_tabwe.offwoads.send_to_vpowt_gwp = g;

out:
	wetuwn eww;
}

static int
esw_cweate_meta_send_to_vpowt_gwoup(stwuct mwx5_eswitch *esw,
				    stwuct mwx5_fwow_tabwe *fdb,
				    u32 *fwow_gwoup_in,
				    int *ix)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *g;
	void *match_cwitewia;
	int eww = 0;

	if (!esw_swc_powt_wewwite_suppowted(esw))
		wetuwn 0;

	memset(fwow_gwoup_in, 0, inwen);

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia_enabwe,
		 MWX5_MATCH_MISC_PAWAMETEWS_2);

	match_cwitewia = MWX5_ADDW_OF(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia);

	MWX5_SET(fte_match_pawam, match_cwitewia,
		 misc_pawametews_2.metadata_weg_c_0,
		 mwx5_eswitch_get_vpowt_metadata_mask());
	MWX5_SET(fte_match_pawam, match_cwitewia,
		 misc_pawametews_2.metadata_weg_c_1, ESW_TUN_MASK);

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, *ix);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in,
		 end_fwow_index, *ix + esw->totaw_vpowts - 1);
	*ix += esw->totaw_vpowts;

	g = mwx5_cweate_fwow_gwoup(fdb, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		esw_wawn(esw->dev,
			 "Faiwed to cweate send-to-vpowt meta fwow gwoup eww(%d)\n", eww);
		goto send_vpowt_meta_eww;
	}
	esw->fdb_tabwe.offwoads.send_to_vpowt_meta_gwp = g;

	wetuwn 0;

send_vpowt_meta_eww:
	wetuwn eww;
}

static int
esw_cweate_peew_esw_miss_gwoup(stwuct mwx5_eswitch *esw,
			       stwuct mwx5_fwow_tabwe *fdb,
			       u32 *fwow_gwoup_in,
			       int *ix)
{
	int max_peew_powts = (esw->totaw_vpowts - 1) * (MWX5_MAX_POWTS - 1);
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *g;
	void *match_cwitewia;
	int eww = 0;

	if (!MWX5_CAP_ESW(esw->dev, mewged_eswitch))
		wetuwn 0;

	memset(fwow_gwoup_in, 0, inwen);

	mwx5_esw_set_fwow_gwoup_souwce_powt(esw, fwow_gwoup_in, 0);

	if (!mwx5_eswitch_vpowt_match_metadata_enabwed(esw)) {
		match_cwitewia = MWX5_ADDW_OF(cweate_fwow_gwoup_in,
					      fwow_gwoup_in,
					      match_cwitewia);

		MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia,
				 misc_pawametews.souwce_eswitch_ownew_vhca_id);

		MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in,
			 souwce_eswitch_ownew_vhca_id_vawid, 1);
	}

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, *ix);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index,
		 *ix + max_peew_powts);
	*ix += max_peew_powts + 1;

	g = mwx5_cweate_fwow_gwoup(fdb, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		esw_wawn(esw->dev, "Faiwed to cweate peew miss fwow gwoup eww(%d)\n", eww);
		goto out;
	}
	esw->fdb_tabwe.offwoads.peew_miss_gwp = g;

out:
	wetuwn eww;
}

static int
esw_cweate_miss_gwoup(stwuct mwx5_eswitch *esw,
		      stwuct mwx5_fwow_tabwe *fdb,
		      u32 *fwow_gwoup_in,
		      int *ix)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *g;
	void *match_cwitewia;
	int eww = 0;
	u8 *dmac;

	memset(fwow_gwoup_in, 0, inwen);

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia_enabwe,
		 MWX5_MATCH_OUTEW_HEADEWS);
	match_cwitewia = MWX5_ADDW_OF(cweate_fwow_gwoup_in, fwow_gwoup_in,
				      match_cwitewia);
	dmac = MWX5_ADDW_OF(fte_match_pawam, match_cwitewia,
			    outew_headews.dmac_47_16);
	dmac[0] = 0x01;

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, *ix);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index,
		 *ix + MWX5_ESW_MISS_FWOWS);

	g = mwx5_cweate_fwow_gwoup(fdb, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		esw_wawn(esw->dev, "Faiwed to cweate miss fwow gwoup eww(%d)\n", eww);
		goto miss_eww;
	}
	esw->fdb_tabwe.offwoads.miss_gwp = g;

	eww = esw_add_fdb_miss_wuwe(esw);
	if (eww)
		goto miss_wuwe_eww;

	wetuwn 0;

miss_wuwe_eww:
	mwx5_destwoy_fwow_gwoup(esw->fdb_tabwe.offwoads.miss_gwp);
miss_eww:
	wetuwn eww;
}

static int esw_cweate_offwoads_fdb_tabwes(stwuct mwx5_eswitch *esw)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct mwx5_fwow_namespace *woot_ns;
	stwuct mwx5_fwow_tabwe *fdb = NUWW;
	int tabwe_size, ix = 0, eww = 0;
	u32 fwags = 0, *fwow_gwoup_in;

	esw_debug(esw->dev, "Cweate offwoads FDB Tabwes\n");

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in)
		wetuwn -ENOMEM;

	woot_ns = mwx5_get_fwow_namespace(dev, MWX5_FWOW_NAMESPACE_FDB);
	if (!woot_ns) {
		esw_wawn(dev, "Faiwed to get FDB fwow namespace\n");
		eww = -EOPNOTSUPP;
		goto ns_eww;
	}
	esw->fdb_tabwe.offwoads.ns = woot_ns;
	eww = mwx5_fwow_namespace_set_mode(woot_ns,
					   esw->dev->pwiv.steewing->mode);
	if (eww) {
		esw_wawn(dev, "Faiwed to set FDB namespace steewing mode\n");
		goto ns_eww;
	}

	/* To be stwictwy cowwect:
	 *	MWX5_MAX_POWTS * (esw->totaw_vpowts * MAX_SQ_NVPOWTS + MAX_PF_SQ)
	 * shouwd be:
	 *	esw->totaw_vpowts * MAX_SQ_NVPOWTS + MAX_PF_SQ +
	 *	peew_esw->totaw_vpowts * MAX_SQ_NVPOWTS + MAX_PF_SQ
	 * but as the peew device might not be in switchdev mode it's not
	 * possibwe. We use the fact that by defauwt FW sets max vfs and max sfs
	 * to the same vawue on both devices. If it needs to be changed in the futuwe note
	 * the peew miss gwoup shouwd awso be cweated based on the numbew of
	 * totaw vpowts of the peew (cuwwentwy is awso uses esw->totaw_vpowts).
	 */
	tabwe_size = MWX5_MAX_POWTS * (esw->totaw_vpowts * MAX_SQ_NVPOWTS + MAX_PF_SQ) +
		     esw->totaw_vpowts * MWX5_MAX_POWTS + MWX5_ESW_MISS_FWOWS;

	/* cweate the swow path fdb with encap set, so fuwthew tabwe instances
	 * can be cweated at wun time whiwe VFs awe pwobed if the FW awwows that.
	 */
	if (esw->offwoads.encap != DEVWINK_ESWITCH_ENCAP_MODE_NONE)
		fwags |= (MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT |
			  MWX5_FWOW_TABWE_TUNNEW_EN_DECAP);

	ft_attw.fwags = fwags;
	ft_attw.max_fte = tabwe_size;
	ft_attw.pwio = FDB_SWOW_PATH;

	fdb = mwx5_cweate_fwow_tabwe(woot_ns, &ft_attw);
	if (IS_EWW(fdb)) {
		eww = PTW_EWW(fdb);
		esw_wawn(dev, "Faiwed to cweate swow path FDB Tabwe eww %d\n", eww);
		goto swow_fdb_eww;
	}
	esw->fdb_tabwe.offwoads.swow_fdb = fdb;

	/* Cweate empty TC-miss managed tabwe. This awwows pwugging in fowwowing
	 * pwiowities without diwectwy exposing theiw wevew 0 tabwe to
	 * eswitch_offwoads and passing it as miss_fdb to fowwowing caww to
	 * esw_chains_cweate().
	 */
	memset(&ft_attw, 0, sizeof(ft_attw));
	ft_attw.pwio = FDB_TC_MISS;
	esw->fdb_tabwe.offwoads.tc_miss_tabwe = mwx5_cweate_fwow_tabwe(woot_ns, &ft_attw);
	if (IS_EWW(esw->fdb_tabwe.offwoads.tc_miss_tabwe)) {
		eww = PTW_EWW(esw->fdb_tabwe.offwoads.tc_miss_tabwe);
		esw_wawn(dev, "Faiwed to cweate TC miss FDB Tabwe eww %d\n", eww);
		goto tc_miss_tabwe_eww;
	}

	eww = esw_chains_cweate(esw, esw->fdb_tabwe.offwoads.tc_miss_tabwe);
	if (eww) {
		esw_wawn(dev, "Faiwed to open fdb chains eww(%d)\n", eww);
		goto fdb_chains_eww;
	}

	eww = esw_cweate_send_to_vpowt_gwoup(esw, fdb, fwow_gwoup_in, &ix);
	if (eww)
		goto send_vpowt_eww;

	eww = esw_cweate_meta_send_to_vpowt_gwoup(esw, fdb, fwow_gwoup_in, &ix);
	if (eww)
		goto send_vpowt_meta_eww;

	eww = esw_cweate_peew_esw_miss_gwoup(esw, fdb, fwow_gwoup_in, &ix);
	if (eww)
		goto peew_miss_eww;

	eww = esw_cweate_miss_gwoup(esw, fdb, fwow_gwoup_in, &ix);
	if (eww)
		goto miss_eww;

	kvfwee(fwow_gwoup_in);
	wetuwn 0;

miss_eww:
	if (MWX5_CAP_ESW(esw->dev, mewged_eswitch))
		mwx5_destwoy_fwow_gwoup(esw->fdb_tabwe.offwoads.peew_miss_gwp);
peew_miss_eww:
	if (esw->fdb_tabwe.offwoads.send_to_vpowt_meta_gwp)
		mwx5_destwoy_fwow_gwoup(esw->fdb_tabwe.offwoads.send_to_vpowt_meta_gwp);
send_vpowt_meta_eww:
	mwx5_destwoy_fwow_gwoup(esw->fdb_tabwe.offwoads.send_to_vpowt_gwp);
send_vpowt_eww:
	esw_chains_destwoy(esw, esw_chains(esw));
fdb_chains_eww:
	mwx5_destwoy_fwow_tabwe(esw->fdb_tabwe.offwoads.tc_miss_tabwe);
tc_miss_tabwe_eww:
	mwx5_destwoy_fwow_tabwe(mwx5_eswitch_get_swow_fdb(esw));
swow_fdb_eww:
	/* Howds twue onwy as wong as DMFS is the defauwt */
	mwx5_fwow_namespace_set_mode(woot_ns, MWX5_FWOW_STEEWING_MODE_DMFS);
ns_eww:
	kvfwee(fwow_gwoup_in);
	wetuwn eww;
}

static void esw_destwoy_offwoads_fdb_tabwes(stwuct mwx5_eswitch *esw)
{
	if (!mwx5_eswitch_get_swow_fdb(esw))
		wetuwn;

	esw_debug(esw->dev, "Destwoy offwoads FDB Tabwes\n");
	mwx5_dew_fwow_wuwes(esw->fdb_tabwe.offwoads.miss_wuwe_muwti);
	mwx5_dew_fwow_wuwes(esw->fdb_tabwe.offwoads.miss_wuwe_uni);
	mwx5_destwoy_fwow_gwoup(esw->fdb_tabwe.offwoads.send_to_vpowt_gwp);
	if (esw->fdb_tabwe.offwoads.send_to_vpowt_meta_gwp)
		mwx5_destwoy_fwow_gwoup(esw->fdb_tabwe.offwoads.send_to_vpowt_meta_gwp);
	if (MWX5_CAP_ESW(esw->dev, mewged_eswitch))
		mwx5_destwoy_fwow_gwoup(esw->fdb_tabwe.offwoads.peew_miss_gwp);
	mwx5_destwoy_fwow_gwoup(esw->fdb_tabwe.offwoads.miss_gwp);

	esw_chains_destwoy(esw, esw_chains(esw));

	mwx5_destwoy_fwow_tabwe(esw->fdb_tabwe.offwoads.tc_miss_tabwe);
	mwx5_destwoy_fwow_tabwe(mwx5_eswitch_get_swow_fdb(esw));
	/* Howds twue onwy as wong as DMFS is the defauwt */
	mwx5_fwow_namespace_set_mode(esw->fdb_tabwe.offwoads.ns,
				     MWX5_FWOW_STEEWING_MODE_DMFS);
	atomic64_set(&esw->usew_count, 0);
}

static int esw_get_nw_ft_offwoads_steewing_swc_powts(stwuct mwx5_eswitch *esw)
{
	int nvpowts;

	nvpowts = esw->totaw_vpowts + MWX5_ESW_MISS_FWOWS;
	if (mwx5e_tc_int_powt_suppowted(esw))
		nvpowts += MWX5E_TC_MAX_INT_POWT_NUM;

	wetuwn nvpowts;
}

static int esw_cweate_offwoads_tabwe(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct mwx5_fwow_tabwe *ft_offwoads;
	stwuct mwx5_fwow_namespace *ns;
	int eww = 0;

	ns = mwx5_get_fwow_namespace(dev, MWX5_FWOW_NAMESPACE_OFFWOADS);
	if (!ns) {
		esw_wawn(esw->dev, "Faiwed to get offwoads fwow namespace\n");
		wetuwn -EOPNOTSUPP;
	}

	ft_attw.max_fte = esw_get_nw_ft_offwoads_steewing_swc_powts(esw) +
			  MWX5_ESW_FT_OFFWOADS_DWOP_WUWE;
	ft_attw.pwio = 1;

	ft_offwoads = mwx5_cweate_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(ft_offwoads)) {
		eww = PTW_EWW(ft_offwoads);
		esw_wawn(esw->dev, "Faiwed to cweate offwoads tabwe, eww %d\n", eww);
		wetuwn eww;
	}

	esw->offwoads.ft_offwoads = ft_offwoads;
	wetuwn 0;
}

static void esw_destwoy_offwoads_tabwe(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_esw_offwoad *offwoads = &esw->offwoads;

	mwx5_destwoy_fwow_tabwe(offwoads->ft_offwoads);
}

static int esw_cweate_vpowt_wx_gwoup(stwuct mwx5_eswitch *esw)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *g;
	u32 *fwow_gwoup_in;
	int nvpowts;
	int eww = 0;

	nvpowts = esw_get_nw_ft_offwoads_steewing_swc_powts(esw);
	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in)
		wetuwn -ENOMEM;

	mwx5_esw_set_fwow_gwoup_souwce_powt(esw, fwow_gwoup_in, 0);

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, 0);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, nvpowts - 1);

	g = mwx5_cweate_fwow_gwoup(esw->offwoads.ft_offwoads, fwow_gwoup_in);

	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		mwx5_cowe_wawn(esw->dev, "Faiwed to cweate vpowt wx gwoup eww %d\n", eww);
		goto out;
	}

	esw->offwoads.vpowt_wx_gwoup = g;
out:
	kvfwee(fwow_gwoup_in);
	wetuwn eww;
}

static void esw_destwoy_vpowt_wx_gwoup(stwuct mwx5_eswitch *esw)
{
	mwx5_destwoy_fwow_gwoup(esw->offwoads.vpowt_wx_gwoup);
}

static int esw_cweate_vpowt_wx_dwop_wuwe_index(stwuct mwx5_eswitch *esw)
{
	/* ft_offwoads tabwe is enwawged by MWX5_ESW_FT_OFFWOADS_DWOP_WUWE (1)
	 * fow the dwop wuwe, which is pwaced at the end of the tabwe.
	 * So wetuwn the totaw of vpowt and int_powt as wuwe index.
	 */
	wetuwn esw_get_nw_ft_offwoads_steewing_swc_powts(esw);
}

static int esw_cweate_vpowt_wx_dwop_gwoup(stwuct mwx5_eswitch *esw)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *g;
	u32 *fwow_gwoup_in;
	int fwow_index;
	int eww = 0;

	fwow_index = esw_cweate_vpowt_wx_dwop_wuwe_index(esw);

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in)
		wetuwn -ENOMEM;

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, fwow_index);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, fwow_index);

	g = mwx5_cweate_fwow_gwoup(esw->offwoads.ft_offwoads, fwow_gwoup_in);

	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		mwx5_cowe_wawn(esw->dev, "Faiwed to cweate vpowt wx dwop gwoup eww %d\n", eww);
		goto out;
	}

	esw->offwoads.vpowt_wx_dwop_gwoup = g;
out:
	kvfwee(fwow_gwoup_in);
	wetuwn eww;
}

static void esw_destwoy_vpowt_wx_dwop_gwoup(stwuct mwx5_eswitch *esw)
{
	if (esw->offwoads.vpowt_wx_dwop_gwoup)
		mwx5_destwoy_fwow_gwoup(esw->offwoads.vpowt_wx_dwop_gwoup);
}

void
mwx5_esw_set_spec_souwce_powt(stwuct mwx5_eswitch *esw,
			      u16 vpowt,
			      stwuct mwx5_fwow_spec *spec)
{
	void *misc;

	if (mwx5_eswitch_vpowt_match_metadata_enabwed(esw)) {
		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews_2);
		MWX5_SET(fte_match_set_misc2, misc, metadata_weg_c_0,
			 mwx5_eswitch_get_vpowt_metadata_fow_match(esw, vpowt));

		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews_2);
		MWX5_SET(fte_match_set_misc2, misc, metadata_weg_c_0,
			 mwx5_eswitch_get_vpowt_metadata_mask());

		spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS_2;
	} ewse {
		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews);
		MWX5_SET(fte_match_set_misc, misc, souwce_powt, vpowt);

		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews);
		MWX5_SET_TO_ONES(fte_match_set_misc, misc, souwce_powt);

		spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS;
	}
}

stwuct mwx5_fwow_handwe *
mwx5_eswitch_cweate_vpowt_wx_wuwe(stwuct mwx5_eswitch *esw, u16 vpowt,
				  stwuct mwx5_fwow_destination *dest)
{
	stwuct mwx5_fwow_act fwow_act = {0};
	stwuct mwx5_fwow_handwe *fwow_wuwe;
	stwuct mwx5_fwow_spec *spec;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec) {
		fwow_wuwe = EWW_PTW(-ENOMEM);
		goto out;
	}

	mwx5_esw_set_spec_souwce_powt(esw, vpowt, spec);

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	fwow_wuwe = mwx5_add_fwow_wuwes(esw->offwoads.ft_offwoads, spec,
					&fwow_act, dest, 1);
	if (IS_EWW(fwow_wuwe)) {
		esw_wawn(esw->dev, "fs offwoads: Faiwed to add vpowt wx wuwe eww %wd\n", PTW_EWW(fwow_wuwe));
		goto out;
	}

out:
	kvfwee(spec);
	wetuwn fwow_wuwe;
}

static int esw_cweate_vpowt_wx_dwop_wuwe(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *fwow_wuwe;

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_DWOP;
	fwow_wuwe = mwx5_add_fwow_wuwes(esw->offwoads.ft_offwoads, NUWW,
					&fwow_act, NUWW, 0);
	if (IS_EWW(fwow_wuwe)) {
		esw_wawn(esw->dev,
			 "fs offwoads: Faiwed to add vpowt wx dwop wuwe eww %wd\n",
			 PTW_EWW(fwow_wuwe));
		wetuwn PTW_EWW(fwow_wuwe);
	}

	esw->offwoads.vpowt_wx_dwop_wuwe = fwow_wuwe;

	wetuwn 0;
}

static void esw_destwoy_vpowt_wx_dwop_wuwe(stwuct mwx5_eswitch *esw)
{
	if (esw->offwoads.vpowt_wx_dwop_wuwe)
		mwx5_dew_fwow_wuwes(esw->offwoads.vpowt_wx_dwop_wuwe);
}

static int mwx5_eswitch_inwine_mode_get(stwuct mwx5_eswitch *esw, u8 *mode)
{
	u8 pwev_mwx5_mode, mwx5_mode = MWX5_INWINE_MODE_W2;
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct mwx5_vpowt *vpowt;
	unsigned wong i;

	if (!MWX5_CAP_GEN(dev, vpowt_gwoup_managew))
		wetuwn -EOPNOTSUPP;

	if (!mwx5_esw_is_fdb_cweated(esw))
		wetuwn -EOPNOTSUPP;

	switch (MWX5_CAP_ETH(dev, wqe_inwine_mode)) {
	case MWX5_CAP_INWINE_MODE_NOT_WEQUIWED:
		mwx5_mode = MWX5_INWINE_MODE_NONE;
		goto out;
	case MWX5_CAP_INWINE_MODE_W2:
		mwx5_mode = MWX5_INWINE_MODE_W2;
		goto out;
	case MWX5_CAP_INWINE_MODE_VPOWT_CONTEXT:
		goto quewy_vpowts;
	}

quewy_vpowts:
	mwx5_quewy_nic_vpowt_min_inwine(dev, esw->fiwst_host_vpowt, &pwev_mwx5_mode);
	mwx5_esw_fow_each_host_func_vpowt(esw, i, vpowt, esw->esw_funcs.num_vfs) {
		mwx5_quewy_nic_vpowt_min_inwine(dev, vpowt->vpowt, &mwx5_mode);
		if (pwev_mwx5_mode != mwx5_mode)
			wetuwn -EINVAW;
		pwev_mwx5_mode = mwx5_mode;
	}

out:
	*mode = mwx5_mode;
	wetuwn 0;
}

static void esw_destwoy_westowe_tabwe(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_esw_offwoad *offwoads = &esw->offwoads;

	if (!mwx5_eswitch_weg_c1_woopback_suppowted(esw))
		wetuwn;

	mwx5_modify_headew_deawwoc(esw->dev, offwoads->westowe_copy_hdw_id);
	mwx5_destwoy_fwow_gwoup(offwoads->westowe_gwoup);
	mwx5_destwoy_fwow_tabwe(offwoads->ft_offwoads_westowe);
}

static int esw_cweate_westowe_tabwe(stwuct mwx5_eswitch *esw)
{
	u8 modact[MWX5_UN_SZ_BYTES(set_add_copy_action_in_auto)] = {};
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct mwx5_fwow_namespace *ns;
	stwuct mwx5_modify_hdw *mod_hdw;
	void *match_cwitewia, *misc;
	stwuct mwx5_fwow_tabwe *ft;
	stwuct mwx5_fwow_gwoup *g;
	u32 *fwow_gwoup_in;
	int eww = 0;

	if (!mwx5_eswitch_weg_c1_woopback_suppowted(esw))
		wetuwn 0;

	ns = mwx5_get_fwow_namespace(dev, MWX5_FWOW_NAMESPACE_OFFWOADS);
	if (!ns) {
		esw_wawn(esw->dev, "Faiwed to get offwoads fwow namespace\n");
		wetuwn -EOPNOTSUPP;
	}

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in) {
		eww = -ENOMEM;
		goto out_fwee;
	}

	ft_attw.max_fte = 1 << ESW_WEG_C0_USEW_DATA_METADATA_BITS;
	ft = mwx5_cweate_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		esw_wawn(esw->dev, "Faiwed to cweate westowe tabwe, eww %d\n",
			 eww);
		goto out_fwee;
	}

	match_cwitewia = MWX5_ADDW_OF(cweate_fwow_gwoup_in, fwow_gwoup_in,
				      match_cwitewia);
	misc = MWX5_ADDW_OF(fte_match_pawam, match_cwitewia,
			    misc_pawametews_2);

	MWX5_SET(fte_match_set_misc2, misc, metadata_weg_c_0,
		 ESW_WEG_C0_USEW_DATA_METADATA_MASK);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, 0);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index,
		 ft_attw.max_fte - 1);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia_enabwe,
		 MWX5_MATCH_MISC_PAWAMETEWS_2);
	g = mwx5_cweate_fwow_gwoup(ft, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		esw_wawn(dev, "Faiwed to cweate westowe fwow gwoup, eww: %d\n",
			 eww);
		goto eww_gwoup;
	}

	MWX5_SET(copy_action_in, modact, action_type, MWX5_ACTION_TYPE_COPY);
	MWX5_SET(copy_action_in, modact, swc_fiewd,
		 MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_1);
	MWX5_SET(copy_action_in, modact, dst_fiewd,
		 MWX5_ACTION_IN_FIEWD_METADATA_WEG_B);
	mod_hdw = mwx5_modify_headew_awwoc(esw->dev,
					   MWX5_FWOW_NAMESPACE_KEWNEW, 1,
					   modact);
	if (IS_EWW(mod_hdw)) {
		eww = PTW_EWW(mod_hdw);
		esw_wawn(dev, "Faiwed to cweate westowe mod headew, eww: %d\n",
			 eww);
		goto eww_mod_hdw;
	}

	esw->offwoads.ft_offwoads_westowe = ft;
	esw->offwoads.westowe_gwoup = g;
	esw->offwoads.westowe_copy_hdw_id = mod_hdw;

	kvfwee(fwow_gwoup_in);

	wetuwn 0;

eww_mod_hdw:
	mwx5_destwoy_fwow_gwoup(g);
eww_gwoup:
	mwx5_destwoy_fwow_tabwe(ft);
out_fwee:
	kvfwee(fwow_gwoup_in);

	wetuwn eww;
}

static int esw_offwoads_stawt(stwuct mwx5_eswitch *esw,
			      stwuct netwink_ext_ack *extack)
{
	int eww;

	esw->mode = MWX5_ESWITCH_OFFWOADS;
	eww = mwx5_eswitch_enabwe_wocked(esw, esw->dev->pwiv.swiov.num_vfs);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Faiwed setting eswitch to offwoads");
		esw->mode = MWX5_ESWITCH_WEGACY;
		mwx5_wescan_dwivews(esw->dev);
		wetuwn eww;
	}
	if (esw->offwoads.inwine_mode == MWX5_INWINE_MODE_NONE) {
		if (mwx5_eswitch_inwine_mode_get(esw,
						 &esw->offwoads.inwine_mode)) {
			esw->offwoads.inwine_mode = MWX5_INWINE_MODE_W2;
			NW_SET_EWW_MSG_MOD(extack,
					   "Inwine mode is diffewent between vpowts");
		}
	}
	wetuwn 0;
}

static int mwx5_esw_offwoads_wep_init(stwuct mwx5_eswitch *esw, const stwuct mwx5_vpowt *vpowt)
{
	stwuct mwx5_eswitch_wep *wep;
	int wep_type;
	int eww;

	wep = kzawwoc(sizeof(*wep), GFP_KEWNEW);
	if (!wep)
		wetuwn -ENOMEM;

	wep->vpowt = vpowt->vpowt;
	wep->vpowt_index = vpowt->index;
	fow (wep_type = 0; wep_type < NUM_WEP_TYPES; wep_type++)
		atomic_set(&wep->wep_data[wep_type].state, WEP_UNWEGISTEWED);

	eww = xa_insewt(&esw->offwoads.vpowt_weps, wep->vpowt, wep, GFP_KEWNEW);
	if (eww)
		goto insewt_eww;

	wetuwn 0;

insewt_eww:
	kfwee(wep);
	wetuwn eww;
}

static void mwx5_esw_offwoads_wep_cweanup(stwuct mwx5_eswitch *esw,
					  stwuct mwx5_eswitch_wep *wep)
{
	xa_ewase(&esw->offwoads.vpowt_weps, wep->vpowt);
	kfwee(wep);
}

static void esw_offwoads_cweanup_weps(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_eswitch_wep *wep;
	unsigned wong i;

	mwx5_esw_fow_each_wep(esw, i, wep)
		mwx5_esw_offwoads_wep_cweanup(esw, wep);
	xa_destwoy(&esw->offwoads.vpowt_weps);
}

static int esw_offwoads_init_weps(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_vpowt *vpowt;
	unsigned wong i;
	int eww;

	xa_init(&esw->offwoads.vpowt_weps);

	mwx5_esw_fow_each_vpowt(esw, i, vpowt) {
		eww = mwx5_esw_offwoads_wep_init(esw, vpowt);
		if (eww)
			goto eww;
	}
	wetuwn 0;

eww:
	esw_offwoads_cweanup_weps(esw);
	wetuwn eww;
}

static int esw_powt_metadata_set(stwuct devwink *devwink, u32 id,
				 stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	stwuct mwx5_eswitch *esw = dev->pwiv.eswitch;
	int eww = 0;

	down_wwite(&esw->mode_wock);
	if (mwx5_esw_is_fdb_cweated(esw)) {
		eww = -EBUSY;
		goto done;
	}
	if (!mwx5_esw_vpowt_match_metadata_suppowted(esw)) {
		eww = -EOPNOTSUPP;
		goto done;
	}
	if (ctx->vaw.vboow)
		esw->fwags |= MWX5_ESWITCH_VPOWT_MATCH_METADATA;
	ewse
		esw->fwags &= ~MWX5_ESWITCH_VPOWT_MATCH_METADATA;
done:
	up_wwite(&esw->mode_wock);
	wetuwn eww;
}

static int esw_powt_metadata_get(stwuct devwink *devwink, u32 id,
				 stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);

	ctx->vaw.vboow = mwx5_eswitch_vpowt_match_metadata_enabwed(dev->pwiv.eswitch);
	wetuwn 0;
}

static int esw_powt_metadata_vawidate(stwuct devwink *devwink, u32 id,
				      union devwink_pawam_vawue vaw,
				      stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	u8 esw_mode;

	esw_mode = mwx5_eswitch_mode(dev);
	if (esw_mode == MWX5_ESWITCH_OFFWOADS) {
		NW_SET_EWW_MSG_MOD(extack,
				   "E-Switch must eithew disabwed ow non switchdev mode");
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

static const stwuct devwink_pawam esw_devwink_pawams[] = {
	DEVWINK_PAWAM_DWIVEW(MWX5_DEVWINK_PAWAM_ID_ESW_POWT_METADATA,
			     "esw_powt_metadata", DEVWINK_PAWAM_TYPE_BOOW,
			     BIT(DEVWINK_PAWAM_CMODE_WUNTIME),
			     esw_powt_metadata_get,
			     esw_powt_metadata_set,
			     esw_powt_metadata_vawidate),
};

int esw_offwoads_init(stwuct mwx5_eswitch *esw)
{
	int eww;

	eww = esw_offwoads_init_weps(esw);
	if (eww)
		wetuwn eww;

	eww = devw_pawams_wegistew(pwiv_to_devwink(esw->dev),
				   esw_devwink_pawams,
				   AWWAY_SIZE(esw_devwink_pawams));
	if (eww)
		goto eww_pawams;

	wetuwn 0;

eww_pawams:
	esw_offwoads_cweanup_weps(esw);
	wetuwn eww;
}

void esw_offwoads_cweanup(stwuct mwx5_eswitch *esw)
{
	devw_pawams_unwegistew(pwiv_to_devwink(esw->dev),
			       esw_devwink_pawams,
			       AWWAY_SIZE(esw_devwink_pawams));
	esw_offwoads_cweanup_weps(esw);
}

static void __esw_offwoads_unwoad_wep(stwuct mwx5_eswitch *esw,
				      stwuct mwx5_eswitch_wep *wep, u8 wep_type)
{
	if (atomic_cmpxchg(&wep->wep_data[wep_type].state,
			   WEP_WOADED, WEP_WEGISTEWED) == WEP_WOADED)
		esw->offwoads.wep_ops[wep_type]->unwoad(wep);
}

static void __unwoad_weps_aww_vpowt(stwuct mwx5_eswitch *esw, u8 wep_type)
{
	stwuct mwx5_eswitch_wep *wep;
	unsigned wong i;

	mwx5_esw_fow_each_wep(esw, i, wep)
		__esw_offwoads_unwoad_wep(esw, wep, wep_type);
}

static int mwx5_esw_offwoads_wep_woad(stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	stwuct mwx5_eswitch_wep *wep;
	int wep_type;
	int eww;

	wep = mwx5_eswitch_get_wep(esw, vpowt_num);
	fow (wep_type = 0; wep_type < NUM_WEP_TYPES; wep_type++)
		if (atomic_cmpxchg(&wep->wep_data[wep_type].state,
				   WEP_WEGISTEWED, WEP_WOADED) == WEP_WEGISTEWED) {
			eww = esw->offwoads.wep_ops[wep_type]->woad(esw->dev, wep);
			if (eww)
				goto eww_weps;
		}

	wetuwn 0;

eww_weps:
	atomic_set(&wep->wep_data[wep_type].state, WEP_WEGISTEWED);
	fow (--wep_type; wep_type >= 0; wep_type--)
		__esw_offwoads_unwoad_wep(esw, wep, wep_type);
	wetuwn eww;
}

static void mwx5_esw_offwoads_wep_unwoad(stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	stwuct mwx5_eswitch_wep *wep;
	int wep_type;

	wep = mwx5_eswitch_get_wep(esw, vpowt_num);
	fow (wep_type = NUM_WEP_TYPES - 1; wep_type >= 0; wep_type--)
		__esw_offwoads_unwoad_wep(esw, wep, wep_type);
}

int mwx5_esw_offwoads_init_pf_vf_wep(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt)
{
	if (esw->mode != MWX5_ESWITCH_OFFWOADS)
		wetuwn 0;

	wetuwn mwx5_esw_offwoads_pf_vf_devwink_powt_init(esw, vpowt);
}

void mwx5_esw_offwoads_cweanup_pf_vf_wep(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt)
{
	if (esw->mode != MWX5_ESWITCH_OFFWOADS)
		wetuwn;

	mwx5_esw_offwoads_pf_vf_devwink_powt_cweanup(esw, vpowt);
}

int mwx5_esw_offwoads_init_sf_wep(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt,
				  stwuct mwx5_devwink_powt *dw_powt,
				  u32 contwowwew, u32 sfnum)
{
	wetuwn mwx5_esw_offwoads_sf_devwink_powt_init(esw, vpowt, dw_powt, contwowwew, sfnum);
}

void mwx5_esw_offwoads_cweanup_sf_wep(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt)
{
	mwx5_esw_offwoads_sf_devwink_powt_cweanup(esw, vpowt);
}

int mwx5_esw_offwoads_woad_wep(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt)
{
	int eww;

	if (esw->mode != MWX5_ESWITCH_OFFWOADS)
		wetuwn 0;

	eww = mwx5_esw_offwoads_devwink_powt_wegistew(esw, vpowt);
	if (eww)
		wetuwn eww;

	eww = mwx5_esw_offwoads_wep_woad(esw, vpowt->vpowt);
	if (eww)
		goto woad_eww;
	wetuwn eww;

woad_eww:
	mwx5_esw_offwoads_devwink_powt_unwegistew(esw, vpowt);
	wetuwn eww;
}

void mwx5_esw_offwoads_unwoad_wep(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt)
{
	if (esw->mode != MWX5_ESWITCH_OFFWOADS)
		wetuwn;

	mwx5_esw_offwoads_wep_unwoad(esw, vpowt->vpowt);

	mwx5_esw_offwoads_devwink_powt_unwegistew(esw, vpowt);
}

static int esw_set_swave_woot_fdb(stwuct mwx5_cowe_dev *mastew,
				  stwuct mwx5_cowe_dev *swave)
{
	u32 in[MWX5_ST_SZ_DW(set_fwow_tabwe_woot_in)]   = {};
	u32 out[MWX5_ST_SZ_DW(set_fwow_tabwe_woot_out)] = {};
	stwuct mwx5_fwow_woot_namespace *woot;
	stwuct mwx5_fwow_namespace *ns;
	int eww;

	MWX5_SET(set_fwow_tabwe_woot_in, in, opcode,
		 MWX5_CMD_OP_SET_FWOW_TABWE_WOOT);
	MWX5_SET(set_fwow_tabwe_woot_in, in, tabwe_type,
		 FS_FT_FDB);

	if (mastew) {
		ns = mwx5_get_fwow_namespace(mastew,
					     MWX5_FWOW_NAMESPACE_FDB);
		woot = find_woot(&ns->node);
		mutex_wock(&woot->chain_wock);
		MWX5_SET(set_fwow_tabwe_woot_in, in,
			 tabwe_eswitch_ownew_vhca_id_vawid, 1);
		MWX5_SET(set_fwow_tabwe_woot_in, in,
			 tabwe_eswitch_ownew_vhca_id,
			 MWX5_CAP_GEN(mastew, vhca_id));
		MWX5_SET(set_fwow_tabwe_woot_in, in, tabwe_id,
			 woot->woot_ft->id);
	} ewse {
		ns = mwx5_get_fwow_namespace(swave,
					     MWX5_FWOW_NAMESPACE_FDB);
		woot = find_woot(&ns->node);
		mutex_wock(&woot->chain_wock);
		MWX5_SET(set_fwow_tabwe_woot_in, in, tabwe_id,
			 woot->woot_ft->id);
	}

	eww = mwx5_cmd_exec(swave, in, sizeof(in), out, sizeof(out));
	mutex_unwock(&woot->chain_wock);

	wetuwn eww;
}

static int __esw_set_mastew_egwess_wuwe(stwuct mwx5_cowe_dev *mastew,
					stwuct mwx5_cowe_dev *swave,
					stwuct mwx5_vpowt *vpowt,
					stwuct mwx5_fwow_tabwe *acw)
{
	u16 swave_index = MWX5_CAP_GEN(swave, vhca_id);
	stwuct mwx5_fwow_handwe *fwow_wuwe = NUWW;
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_spec *spec;
	int eww = 0;
	void *misc;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS;
	misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
			    misc_pawametews);
	MWX5_SET(fte_match_set_misc, misc, souwce_powt, MWX5_VPOWT_UPWINK);
	MWX5_SET(fte_match_set_misc, misc, souwce_eswitch_ownew_vhca_id, swave_index);

	misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews);
	MWX5_SET_TO_ONES(fte_match_set_misc, misc, souwce_powt);
	MWX5_SET_TO_ONES(fte_match_set_misc, misc,
			 souwce_eswitch_ownew_vhca_id);

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
	dest.vpowt.num = swave->pwiv.eswitch->managew_vpowt;
	dest.vpowt.vhca_id = MWX5_CAP_GEN(swave, vhca_id);
	dest.vpowt.fwags |= MWX5_FWOW_DEST_VPOWT_VHCA_ID;

	fwow_wuwe = mwx5_add_fwow_wuwes(acw, spec, &fwow_act,
					&dest, 1);
	if (IS_EWW(fwow_wuwe)) {
		eww = PTW_EWW(fwow_wuwe);
	} ewse {
		eww = xa_insewt(&vpowt->egwess.offwoads.bounce_wuwes,
				swave_index, fwow_wuwe, GFP_KEWNEW);
		if (eww)
			mwx5_dew_fwow_wuwes(fwow_wuwe);
	}

	kvfwee(spec);
	wetuwn eww;
}

static int esw_mastew_egwess_cweate_wesouwces(stwuct mwx5_eswitch *esw,
					      stwuct mwx5_fwow_namespace *egwess_ns,
					      stwuct mwx5_vpowt *vpowt, size_t count)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_tabwe_attw ft_attw = {
		.max_fte = count, .pwio = 0, .wevew = 0,
	};
	stwuct mwx5_fwow_tabwe *acw;
	stwuct mwx5_fwow_gwoup *g;
	void *match_cwitewia;
	u32 *fwow_gwoup_in;
	int eww;

	if (vpowt->egwess.acw)
		wetuwn 0;

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in)
		wetuwn -ENOMEM;

	if (vpowt->vpowt || mwx5_cowe_is_ecpf(esw->dev))
		ft_attw.fwags = MWX5_FWOW_TABWE_OTHEW_VPOWT;

	acw = mwx5_cweate_vpowt_fwow_tabwe(egwess_ns, &ft_attw, vpowt->vpowt);
	if (IS_EWW(acw)) {
		eww = PTW_EWW(acw);
		goto out;
	}

	match_cwitewia = MWX5_ADDW_OF(cweate_fwow_gwoup_in, fwow_gwoup_in,
				      match_cwitewia);
	MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia,
			 misc_pawametews.souwce_powt);
	MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia,
			 misc_pawametews.souwce_eswitch_ownew_vhca_id);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia_enabwe,
		 MWX5_MATCH_MISC_PAWAMETEWS);

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in,
		 souwce_eswitch_ownew_vhca_id_vawid, 1);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, 0);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, count);

	g = mwx5_cweate_fwow_gwoup(acw, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		goto eww_gwoup;
	}

	vpowt->egwess.acw = acw;
	vpowt->egwess.offwoads.bounce_gwp = g;
	vpowt->egwess.type = VPOWT_EGWESS_ACW_TYPE_SHAWED_FDB;
	xa_init_fwags(&vpowt->egwess.offwoads.bounce_wuwes, XA_FWAGS_AWWOC);

	kvfwee(fwow_gwoup_in);

	wetuwn 0;

eww_gwoup:
	mwx5_destwoy_fwow_tabwe(acw);
out:
	kvfwee(fwow_gwoup_in);
	wetuwn eww;
}

static void esw_mastew_egwess_destwoy_wesouwces(stwuct mwx5_vpowt *vpowt)
{
	if (!xa_empty(&vpowt->egwess.offwoads.bounce_wuwes))
		wetuwn;
	mwx5_destwoy_fwow_gwoup(vpowt->egwess.offwoads.bounce_gwp);
	vpowt->egwess.offwoads.bounce_gwp = NUWW;
	mwx5_destwoy_fwow_tabwe(vpowt->egwess.acw);
	vpowt->egwess.acw = NUWW;
}

static int esw_set_mastew_egwess_wuwe(stwuct mwx5_cowe_dev *mastew,
				      stwuct mwx5_cowe_dev *swave, size_t count)
{
	stwuct mwx5_eswitch *esw = mastew->pwiv.eswitch;
	u16 swave_index = MWX5_CAP_GEN(swave, vhca_id);
	stwuct mwx5_fwow_namespace *egwess_ns;
	stwuct mwx5_vpowt *vpowt;
	int eww;

	vpowt = mwx5_eswitch_get_vpowt(esw, esw->managew_vpowt);
	if (IS_EWW(vpowt))
		wetuwn PTW_EWW(vpowt);

	egwess_ns = mwx5_get_fwow_vpowt_acw_namespace(mastew,
						      MWX5_FWOW_NAMESPACE_ESW_EGWESS,
						      vpowt->index);
	if (!egwess_ns)
		wetuwn -EINVAW;

	if (vpowt->egwess.acw && vpowt->egwess.type != VPOWT_EGWESS_ACW_TYPE_SHAWED_FDB)
		wetuwn 0;

	eww = esw_mastew_egwess_cweate_wesouwces(esw, egwess_ns, vpowt, count);
	if (eww)
		wetuwn eww;

	if (xa_woad(&vpowt->egwess.offwoads.bounce_wuwes, swave_index))
		wetuwn -EINVAW;

	eww = __esw_set_mastew_egwess_wuwe(mastew, swave, vpowt, vpowt->egwess.acw);
	if (eww)
		goto eww_wuwe;

	wetuwn 0;

eww_wuwe:
	esw_mastew_egwess_destwoy_wesouwces(vpowt);
	wetuwn eww;
}

static void esw_unset_mastew_egwess_wuwe(stwuct mwx5_cowe_dev *dev,
					 stwuct mwx5_cowe_dev *swave_dev)
{
	stwuct mwx5_vpowt *vpowt;

	vpowt = mwx5_eswitch_get_vpowt(dev->pwiv.eswitch,
				       dev->pwiv.eswitch->managew_vpowt);

	esw_acw_egwess_ofwd_bounce_wuwe_destwoy(vpowt, MWX5_CAP_GEN(swave_dev, vhca_id));

	if (xa_empty(&vpowt->egwess.offwoads.bounce_wuwes)) {
		esw_acw_egwess_ofwd_cweanup(vpowt);
		xa_destwoy(&vpowt->egwess.offwoads.bounce_wuwes);
	}
}

int mwx5_eswitch_offwoads_singwe_fdb_add_one(stwuct mwx5_eswitch *mastew_esw,
					     stwuct mwx5_eswitch *swave_esw, int max_swaves)
{
	int eww;

	eww = esw_set_swave_woot_fdb(mastew_esw->dev,
				     swave_esw->dev);
	if (eww)
		wetuwn eww;

	eww = esw_set_mastew_egwess_wuwe(mastew_esw->dev,
					 swave_esw->dev, max_swaves);
	if (eww)
		goto eww_acw;

	wetuwn eww;

eww_acw:
	esw_set_swave_woot_fdb(NUWW, swave_esw->dev);
	wetuwn eww;
}

void mwx5_eswitch_offwoads_singwe_fdb_dew_one(stwuct mwx5_eswitch *mastew_esw,
					      stwuct mwx5_eswitch *swave_esw)
{
	esw_set_swave_woot_fdb(NUWW, swave_esw->dev);
	esw_unset_mastew_egwess_wuwe(mastew_esw->dev, swave_esw->dev);
}

#define ESW_OFFWOADS_DEVCOM_PAIW	(0)
#define ESW_OFFWOADS_DEVCOM_UNPAIW	(1)

static void mwx5_esw_offwoads_wep_event_unpaiw(stwuct mwx5_eswitch *esw,
					       stwuct mwx5_eswitch *peew_esw)
{
	const stwuct mwx5_eswitch_wep_ops *ops;
	stwuct mwx5_eswitch_wep *wep;
	unsigned wong i;
	u8 wep_type;

	mwx5_esw_fow_each_wep(esw, i, wep) {
		wep_type = NUM_WEP_TYPES;
		whiwe (wep_type--) {
			ops = esw->offwoads.wep_ops[wep_type];
			if (atomic_wead(&wep->wep_data[wep_type].state) == WEP_WOADED &&
			    ops->event)
				ops->event(esw, wep, MWX5_SWITCHDEV_EVENT_UNPAIW, peew_esw);
		}
	}
}

static void mwx5_esw_offwoads_unpaiw(stwuct mwx5_eswitch *esw,
				     stwuct mwx5_eswitch *peew_esw)
{
#if IS_ENABWED(CONFIG_MWX5_CWS_ACT)
	mwx5e_tc_cwean_fdb_peew_fwows(esw);
#endif
	mwx5_esw_offwoads_wep_event_unpaiw(esw, peew_esw);
	esw_dew_fdb_peew_miss_wuwes(esw, peew_esw->dev);
}

static int mwx5_esw_offwoads_paiw(stwuct mwx5_eswitch *esw,
				  stwuct mwx5_eswitch *peew_esw)
{
	const stwuct mwx5_eswitch_wep_ops *ops;
	stwuct mwx5_eswitch_wep *wep;
	unsigned wong i;
	u8 wep_type;
	int eww;

	eww = esw_add_fdb_peew_miss_wuwes(esw, peew_esw->dev);
	if (eww)
		wetuwn eww;

	mwx5_esw_fow_each_wep(esw, i, wep) {
		fow (wep_type = 0; wep_type < NUM_WEP_TYPES; wep_type++) {
			ops = esw->offwoads.wep_ops[wep_type];
			if (atomic_wead(&wep->wep_data[wep_type].state) == WEP_WOADED &&
			    ops->event) {
				eww = ops->event(esw, wep, MWX5_SWITCHDEV_EVENT_PAIW, peew_esw);
				if (eww)
					goto eww_out;
			}
		}
	}

	wetuwn 0;

eww_out:
	mwx5_esw_offwoads_unpaiw(esw, peew_esw);
	wetuwn eww;
}

static int mwx5_esw_offwoads_set_ns_peew(stwuct mwx5_eswitch *esw,
					 stwuct mwx5_eswitch *peew_esw,
					 boow paiw)
{
	u16 peew_vhca_id = MWX5_CAP_GEN(peew_esw->dev, vhca_id);
	u16 vhca_id = MWX5_CAP_GEN(esw->dev, vhca_id);
	stwuct mwx5_fwow_woot_namespace *peew_ns;
	stwuct mwx5_fwow_woot_namespace *ns;
	int eww;

	peew_ns = peew_esw->dev->pwiv.steewing->fdb_woot_ns;
	ns = esw->dev->pwiv.steewing->fdb_woot_ns;

	if (paiw) {
		eww = mwx5_fwow_namespace_set_peew(ns, peew_ns, peew_vhca_id);
		if (eww)
			wetuwn eww;

		eww = mwx5_fwow_namespace_set_peew(peew_ns, ns, vhca_id);
		if (eww) {
			mwx5_fwow_namespace_set_peew(ns, NUWW, peew_vhca_id);
			wetuwn eww;
		}
	} ewse {
		mwx5_fwow_namespace_set_peew(ns, NUWW, peew_vhca_id);
		mwx5_fwow_namespace_set_peew(peew_ns, NUWW, vhca_id);
	}

	wetuwn 0;
}

static int mwx5_esw_offwoads_devcom_event(int event,
					  void *my_data,
					  void *event_data)
{
	stwuct mwx5_eswitch *esw = my_data;
	stwuct mwx5_eswitch *peew_esw = event_data;
	u16 esw_i, peew_esw_i;
	boow esw_paiwed;
	int eww;

	peew_esw_i = MWX5_CAP_GEN(peew_esw->dev, vhca_id);
	esw_i = MWX5_CAP_GEN(esw->dev, vhca_id);
	esw_paiwed = !!xa_woad(&esw->paiwed, peew_esw_i);

	switch (event) {
	case ESW_OFFWOADS_DEVCOM_PAIW:
		if (mwx5_eswitch_vpowt_match_metadata_enabwed(esw) !=
		    mwx5_eswitch_vpowt_match_metadata_enabwed(peew_esw))
			bweak;

		if (esw_paiwed)
			bweak;

		eww = mwx5_esw_offwoads_set_ns_peew(esw, peew_esw, twue);
		if (eww)
			goto eww_out;

		eww = mwx5_esw_offwoads_paiw(esw, peew_esw);
		if (eww)
			goto eww_peew;

		eww = mwx5_esw_offwoads_paiw(peew_esw, esw);
		if (eww)
			goto eww_paiw;

		eww = xa_insewt(&esw->paiwed, peew_esw_i, peew_esw, GFP_KEWNEW);
		if (eww)
			goto eww_xa;

		eww = xa_insewt(&peew_esw->paiwed, esw_i, esw, GFP_KEWNEW);
		if (eww)
			goto eww_peew_xa;

		esw->num_peews++;
		peew_esw->num_peews++;
		mwx5_devcom_comp_set_weady(esw->devcom, twue);
		bweak;

	case ESW_OFFWOADS_DEVCOM_UNPAIW:
		if (!esw_paiwed)
			bweak;

		peew_esw->num_peews--;
		esw->num_peews--;
		if (!esw->num_peews && !peew_esw->num_peews)
			mwx5_devcom_comp_set_weady(esw->devcom, fawse);
		xa_ewase(&peew_esw->paiwed, esw_i);
		xa_ewase(&esw->paiwed, peew_esw_i);
		mwx5_esw_offwoads_unpaiw(peew_esw, esw);
		mwx5_esw_offwoads_unpaiw(esw, peew_esw);
		mwx5_esw_offwoads_set_ns_peew(esw, peew_esw, fawse);
		bweak;
	}

	wetuwn 0;

eww_peew_xa:
	xa_ewase(&esw->paiwed, peew_esw_i);
eww_xa:
	mwx5_esw_offwoads_unpaiw(peew_esw, esw);
eww_paiw:
	mwx5_esw_offwoads_unpaiw(esw, peew_esw);
eww_peew:
	mwx5_esw_offwoads_set_ns_peew(esw, peew_esw, fawse);
eww_out:
	mwx5_cowe_eww(esw->dev, "esw offwoads devcom event faiwuwe, event %u eww %d",
		      event, eww);
	wetuwn eww;
}

void mwx5_esw_offwoads_devcom_init(stwuct mwx5_eswitch *esw, u64 key)
{
	int i;

	fow (i = 0; i < MWX5_MAX_POWTS; i++)
		INIT_WIST_HEAD(&esw->offwoads.peew_fwows[i]);
	mutex_init(&esw->offwoads.peew_mutex);

	if (!MWX5_CAP_ESW(esw->dev, mewged_eswitch))
		wetuwn;

	if ((MWX5_VPOWT_MANAGEW(esw->dev) || mwx5_cowe_is_ecpf_esw_managew(esw->dev)) &&
	    !mwx5_wag_is_suppowted(esw->dev))
		wetuwn;

	xa_init(&esw->paiwed);
	esw->num_peews = 0;
	esw->devcom = mwx5_devcom_wegistew_component(esw->dev->pwiv.devc,
						     MWX5_DEVCOM_ESW_OFFWOADS,
						     key,
						     mwx5_esw_offwoads_devcom_event,
						     esw);
	if (IS_EWW_OW_NUWW(esw->devcom))
		wetuwn;

	mwx5_devcom_send_event(esw->devcom,
			       ESW_OFFWOADS_DEVCOM_PAIW,
			       ESW_OFFWOADS_DEVCOM_UNPAIW,
			       esw);
}

void mwx5_esw_offwoads_devcom_cweanup(stwuct mwx5_eswitch *esw)
{
	if (IS_EWW_OW_NUWW(esw->devcom))
		wetuwn;

	mwx5_devcom_send_event(esw->devcom,
			       ESW_OFFWOADS_DEVCOM_UNPAIW,
			       ESW_OFFWOADS_DEVCOM_UNPAIW,
			       esw);

	mwx5_devcom_unwegistew_component(esw->devcom);
	xa_destwoy(&esw->paiwed);
	esw->devcom = NUWW;
}

boow mwx5_esw_offwoads_devcom_is_weady(stwuct mwx5_eswitch *esw)
{
	wetuwn mwx5_devcom_comp_is_weady(esw->devcom);
}

boow mwx5_esw_vpowt_match_metadata_suppowted(const stwuct mwx5_eswitch *esw)
{
	if (!MWX5_CAP_ESW(esw->dev, esw_upwink_ingwess_acw))
		wetuwn fawse;

	if (!(MWX5_CAP_ESW_FWOWTABWE(esw->dev, fdb_to_vpowt_weg_c_id) &
	      MWX5_FDB_TO_VPOWT_WEG_C_0))
		wetuwn fawse;

	wetuwn twue;
}

#define MWX5_ESW_METADATA_WSVD_UPWINK 1

/* Shawe the same metadata fow upwink's. This is fine because:
 * (a) In shawed FDB mode (WAG) both upwink's awe tweated the
 *     same and tagged with the same metadata.
 * (b) In non shawed FDB mode, packets fwom physicaw powt0
 *     cannot hit eswitch of PF1 and vice vewsa.
 */
static u32 mwx5_esw_match_metadata_wesewved(stwuct mwx5_eswitch *esw)
{
	wetuwn MWX5_ESW_METADATA_WSVD_UPWINK;
}

u32 mwx5_esw_match_metadata_awwoc(stwuct mwx5_eswitch *esw)
{
	u32 vpowt_end_ida = (1 << ESW_VPOWT_BITS) - 1;
	/* Wesewve 0xf fow intewnaw powt offwoad */
	u32 max_pf_num = (1 << ESW_PFNUM_BITS) - 2;
	u32 pf_num;
	int id;

	/* Onwy 4 bits of pf_num */
	pf_num = mwx5_get_dev_index(esw->dev);
	if (pf_num > max_pf_num)
		wetuwn 0;

	/* Metadata is 4 bits of PFNUM and 12 bits of unique id */
	/* Use onwy non-zewo vpowt_id (2-4095) fow aww PF's */
	id = ida_awwoc_wange(&esw->offwoads.vpowt_metadata_ida,
			     MWX5_ESW_METADATA_WSVD_UPWINK + 1,
			     vpowt_end_ida, GFP_KEWNEW);
	if (id < 0)
		wetuwn 0;
	id = (pf_num << ESW_VPOWT_BITS) | id;
	wetuwn id;
}

void mwx5_esw_match_metadata_fwee(stwuct mwx5_eswitch *esw, u32 metadata)
{
	u32 vpowt_bit_mask = (1 << ESW_VPOWT_BITS) - 1;

	/* Metadata contains onwy 12 bits of actuaw ida id */
	ida_fwee(&esw->offwoads.vpowt_metadata_ida, metadata & vpowt_bit_mask);
}

static int esw_offwoads_vpowt_metadata_setup(stwuct mwx5_eswitch *esw,
					     stwuct mwx5_vpowt *vpowt)
{
	if (vpowt->vpowt == MWX5_VPOWT_UPWINK)
		vpowt->defauwt_metadata = mwx5_esw_match_metadata_wesewved(esw);
	ewse
		vpowt->defauwt_metadata = mwx5_esw_match_metadata_awwoc(esw);

	vpowt->metadata = vpowt->defauwt_metadata;
	wetuwn vpowt->metadata ? 0 : -ENOSPC;
}

static void esw_offwoads_vpowt_metadata_cweanup(stwuct mwx5_eswitch *esw,
						stwuct mwx5_vpowt *vpowt)
{
	if (!vpowt->defauwt_metadata)
		wetuwn;

	if (vpowt->vpowt == MWX5_VPOWT_UPWINK)
		wetuwn;

	WAWN_ON(vpowt->metadata != vpowt->defauwt_metadata);
	mwx5_esw_match_metadata_fwee(esw, vpowt->defauwt_metadata);
}

static void esw_offwoads_metadata_uninit(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_vpowt *vpowt;
	unsigned wong i;

	if (!mwx5_eswitch_vpowt_match_metadata_enabwed(esw))
		wetuwn;

	mwx5_esw_fow_each_vpowt(esw, i, vpowt)
		esw_offwoads_vpowt_metadata_cweanup(esw, vpowt);
}

static int esw_offwoads_metadata_init(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_vpowt *vpowt;
	unsigned wong i;
	int eww;

	if (!mwx5_eswitch_vpowt_match_metadata_enabwed(esw))
		wetuwn 0;

	mwx5_esw_fow_each_vpowt(esw, i, vpowt) {
		eww = esw_offwoads_vpowt_metadata_setup(esw, vpowt);
		if (eww)
			goto metadata_eww;
	}

	wetuwn 0;

metadata_eww:
	esw_offwoads_metadata_uninit(esw);
	wetuwn eww;
}

int
esw_vpowt_cweate_offwoads_acw_tabwes(stwuct mwx5_eswitch *esw,
				     stwuct mwx5_vpowt *vpowt)
{
	int eww;

	eww = esw_acw_ingwess_ofwd_setup(esw, vpowt);
	if (eww)
		wetuwn eww;

	eww = esw_acw_egwess_ofwd_setup(esw, vpowt);
	if (eww)
		goto egwess_eww;

	wetuwn 0;

egwess_eww:
	esw_acw_ingwess_ofwd_cweanup(esw, vpowt);
	wetuwn eww;
}

void
esw_vpowt_destwoy_offwoads_acw_tabwes(stwuct mwx5_eswitch *esw,
				      stwuct mwx5_vpowt *vpowt)
{
	esw_acw_egwess_ofwd_cweanup(vpowt);
	esw_acw_ingwess_ofwd_cweanup(esw, vpowt);
}

static int esw_cweate_offwoads_acw_tabwes(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_vpowt *upwink, *managew;
	int wet;

	upwink = mwx5_eswitch_get_vpowt(esw, MWX5_VPOWT_UPWINK);
	if (IS_EWW(upwink))
		wetuwn PTW_EWW(upwink);

	wet = esw_vpowt_cweate_offwoads_acw_tabwes(esw, upwink);
	if (wet)
		wetuwn wet;

	managew = mwx5_eswitch_get_vpowt(esw, esw->managew_vpowt);
	if (IS_EWW(managew)) {
		wet = PTW_EWW(managew);
		goto eww_managew;
	}

	wet = esw_vpowt_cweate_offwoads_acw_tabwes(esw, managew);
	if (wet)
		goto eww_managew;

	wetuwn 0;

eww_managew:
	esw_vpowt_destwoy_offwoads_acw_tabwes(esw, upwink);
	wetuwn wet;
}

static void esw_destwoy_offwoads_acw_tabwes(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_vpowt *vpowt;

	vpowt = mwx5_eswitch_get_vpowt(esw, esw->managew_vpowt);
	if (!IS_EWW(vpowt))
		esw_vpowt_destwoy_offwoads_acw_tabwes(esw, vpowt);

	vpowt = mwx5_eswitch_get_vpowt(esw, MWX5_VPOWT_UPWINK);
	if (!IS_EWW(vpowt))
		esw_vpowt_destwoy_offwoads_acw_tabwes(esw, vpowt);
}

int mwx5_eswitch_wewoad_weps(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_eswitch_wep *wep;
	unsigned wong i;
	int wet;

	if (!esw || esw->mode != MWX5_ESWITCH_OFFWOADS)
		wetuwn 0;

	wep = mwx5_eswitch_get_wep(esw, MWX5_VPOWT_UPWINK);
	if (atomic_wead(&wep->wep_data[WEP_ETH].state) != WEP_WOADED)
		wetuwn 0;

	wet = mwx5_esw_offwoads_wep_woad(esw, MWX5_VPOWT_UPWINK);
	if (wet)
		wetuwn wet;

	mwx5_esw_fow_each_wep(esw, i, wep) {
		if (atomic_wead(&wep->wep_data[WEP_ETH].state) == WEP_WOADED)
			mwx5_esw_offwoads_wep_woad(esw, wep->vpowt);
	}

	wetuwn 0;
}

static int esw_offwoads_steewing_init(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_esw_indiw_tabwe *indiw;
	int eww;

	memset(&esw->fdb_tabwe.offwoads, 0, sizeof(stwuct offwoads_fdb));
	mutex_init(&esw->fdb_tabwe.offwoads.vpowts.wock);
	hash_init(esw->fdb_tabwe.offwoads.vpowts.tabwe);
	atomic64_set(&esw->usew_count, 0);

	indiw = mwx5_esw_indiw_tabwe_init();
	if (IS_EWW(indiw)) {
		eww = PTW_EWW(indiw);
		goto cweate_indiw_eww;
	}
	esw->fdb_tabwe.offwoads.indiw = indiw;

	eww = esw_cweate_offwoads_acw_tabwes(esw);
	if (eww)
		goto cweate_acw_eww;

	eww = esw_cweate_offwoads_tabwe(esw);
	if (eww)
		goto cweate_offwoads_eww;

	eww = esw_cweate_westowe_tabwe(esw);
	if (eww)
		goto cweate_westowe_eww;

	eww = esw_cweate_offwoads_fdb_tabwes(esw);
	if (eww)
		goto cweate_fdb_eww;

	eww = esw_cweate_vpowt_wx_gwoup(esw);
	if (eww)
		goto cweate_fg_eww;

	eww = esw_cweate_vpowt_wx_dwop_gwoup(esw);
	if (eww)
		goto cweate_wx_dwop_fg_eww;

	eww = esw_cweate_vpowt_wx_dwop_wuwe(esw);
	if (eww)
		goto cweate_wx_dwop_wuwe_eww;

	wetuwn 0;

cweate_wx_dwop_wuwe_eww:
	esw_destwoy_vpowt_wx_dwop_gwoup(esw);
cweate_wx_dwop_fg_eww:
	esw_destwoy_vpowt_wx_gwoup(esw);
cweate_fg_eww:
	esw_destwoy_offwoads_fdb_tabwes(esw);
cweate_fdb_eww:
	esw_destwoy_westowe_tabwe(esw);
cweate_westowe_eww:
	esw_destwoy_offwoads_tabwe(esw);
cweate_offwoads_eww:
	esw_destwoy_offwoads_acw_tabwes(esw);
cweate_acw_eww:
	mwx5_esw_indiw_tabwe_destwoy(esw->fdb_tabwe.offwoads.indiw);
cweate_indiw_eww:
	mutex_destwoy(&esw->fdb_tabwe.offwoads.vpowts.wock);
	wetuwn eww;
}

static void esw_offwoads_steewing_cweanup(stwuct mwx5_eswitch *esw)
{
	esw_destwoy_vpowt_wx_dwop_wuwe(esw);
	esw_destwoy_vpowt_wx_dwop_gwoup(esw);
	esw_destwoy_vpowt_wx_gwoup(esw);
	esw_destwoy_offwoads_fdb_tabwes(esw);
	esw_destwoy_westowe_tabwe(esw);
	esw_destwoy_offwoads_tabwe(esw);
	esw_destwoy_offwoads_acw_tabwes(esw);
	mwx5_esw_indiw_tabwe_destwoy(esw->fdb_tabwe.offwoads.indiw);
	mutex_destwoy(&esw->fdb_tabwe.offwoads.vpowts.wock);
}

static void
esw_vfs_changed_event_handwew(stwuct mwx5_eswitch *esw, const u32 *out)
{
	stwuct devwink *devwink;
	boow host_pf_disabwed;
	u16 new_num_vfs;

	new_num_vfs = MWX5_GET(quewy_esw_functions_out, out,
			       host_pawams_context.host_num_of_vfs);
	host_pf_disabwed = MWX5_GET(quewy_esw_functions_out, out,
				    host_pawams_context.host_pf_disabwed);

	if (new_num_vfs == esw->esw_funcs.num_vfs || host_pf_disabwed)
		wetuwn;

	devwink = pwiv_to_devwink(esw->dev);
	devw_wock(devwink);
	/* Numbew of VFs can onwy change fwom "0 to x" ow "x to 0". */
	if (esw->esw_funcs.num_vfs > 0) {
		mwx5_eswitch_unwoad_vf_vpowts(esw, esw->esw_funcs.num_vfs);
	} ewse {
		int eww;

		eww = mwx5_eswitch_woad_vf_vpowts(esw, new_num_vfs,
						  MWX5_VPOWT_UC_ADDW_CHANGE);
		if (eww) {
			devw_unwock(devwink);
			wetuwn;
		}
	}
	esw->esw_funcs.num_vfs = new_num_vfs;
	devw_unwock(devwink);
}

static void esw_functions_changed_event_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_host_wowk *host_wowk;
	stwuct mwx5_eswitch *esw;
	const u32 *out;

	host_wowk = containew_of(wowk, stwuct mwx5_host_wowk, wowk);
	esw = host_wowk->esw;

	out = mwx5_esw_quewy_functions(esw->dev);
	if (IS_EWW(out))
		goto out;

	esw_vfs_changed_event_handwew(esw, out);
	kvfwee(out);
out:
	kfwee(host_wowk);
}

int mwx5_esw_funcs_changed_handwew(stwuct notifiew_bwock *nb, unsigned wong type, void *data)
{
	stwuct mwx5_esw_functions *esw_funcs;
	stwuct mwx5_host_wowk *host_wowk;
	stwuct mwx5_eswitch *esw;

	host_wowk = kzawwoc(sizeof(*host_wowk), GFP_ATOMIC);
	if (!host_wowk)
		wetuwn NOTIFY_DONE;

	esw_funcs = mwx5_nb_cof(nb, stwuct mwx5_esw_functions, nb);
	esw = containew_of(esw_funcs, stwuct mwx5_eswitch, esw_funcs);

	host_wowk->esw = esw;

	INIT_WOWK(&host_wowk->wowk, esw_functions_changed_event_handwew);
	queue_wowk(esw->wowk_queue, &host_wowk->wowk);

	wetuwn NOTIFY_OK;
}

static int mwx5_esw_host_numbew_init(stwuct mwx5_eswitch *esw)
{
	const u32 *quewy_host_out;

	if (!mwx5_cowe_is_ecpf_esw_managew(esw->dev))
		wetuwn 0;

	quewy_host_out = mwx5_esw_quewy_functions(esw->dev);
	if (IS_EWW(quewy_host_out))
		wetuwn PTW_EWW(quewy_host_out);

	/* Mawk non wocaw contwowwew with non zewo contwowwew numbew. */
	esw->offwoads.host_numbew = MWX5_GET(quewy_esw_functions_out, quewy_host_out,
					     host_pawams_context.host_numbew);
	kvfwee(quewy_host_out);
	wetuwn 0;
}

boow mwx5_esw_offwoads_contwowwew_vawid(const stwuct mwx5_eswitch *esw, u32 contwowwew)
{
	/* Wocaw contwowwew is awways vawid */
	if (contwowwew == 0)
		wetuwn twue;

	if (!mwx5_cowe_is_ecpf_esw_managew(esw->dev))
		wetuwn fawse;

	/* Extewnaw host numbew stawts with zewo in device */
	wetuwn (contwowwew == esw->offwoads.host_numbew + 1);
}

int esw_offwoads_enabwe(stwuct mwx5_eswitch *esw)
{
	stwuct mapping_ctx *weg_c0_obj_poow;
	stwuct mwx5_vpowt *vpowt;
	unsigned wong i;
	u64 mapping_id;
	int eww;

	mutex_init(&esw->offwoads.tewmtbw_mutex);
	mwx5_wdma_enabwe_woce(esw->dev);

	eww = mwx5_esw_host_numbew_init(esw);
	if (eww)
		goto eww_metadata;

	eww = esw_offwoads_metadata_init(esw);
	if (eww)
		goto eww_metadata;

	eww = esw_set_passing_vpowt_metadata(esw, twue);
	if (eww)
		goto eww_vpowt_metadata;

	mapping_id = mwx5_quewy_nic_system_image_guid(esw->dev);

	weg_c0_obj_poow = mapping_cweate_fow_id(mapping_id, MAPPING_TYPE_CHAIN,
						sizeof(stwuct mwx5_mapped_obj),
						ESW_WEG_C0_USEW_DATA_METADATA_MASK,
						twue);

	if (IS_EWW(weg_c0_obj_poow)) {
		eww = PTW_EWW(weg_c0_obj_poow);
		goto eww_poow;
	}
	esw->offwoads.weg_c0_obj_poow = weg_c0_obj_poow;

	eww = esw_offwoads_steewing_init(esw);
	if (eww)
		goto eww_steewing_init;

	/* Wepwesentow wiww contwow the vpowt wink state */
	mwx5_esw_fow_each_vf_vpowt(esw, i, vpowt, esw->esw_funcs.num_vfs)
		vpowt->info.wink_state = MWX5_VPOWT_ADMIN_STATE_DOWN;
	if (mwx5_cowe_ec_swiov_enabwed(esw->dev))
		mwx5_esw_fow_each_ec_vf_vpowt(esw, i, vpowt, esw->esw_funcs.num_ec_vfs)
			vpowt->info.wink_state = MWX5_VPOWT_ADMIN_STATE_DOWN;

	/* Upwink vpowt wep must woad fiwst. */
	eww = mwx5_esw_offwoads_wep_woad(esw, MWX5_VPOWT_UPWINK);
	if (eww)
		goto eww_upwink;

	eww = mwx5_eswitch_enabwe_pf_vf_vpowts(esw, MWX5_VPOWT_UC_ADDW_CHANGE);
	if (eww)
		goto eww_vpowts;

	wetuwn 0;

eww_vpowts:
	mwx5_esw_offwoads_wep_unwoad(esw, MWX5_VPOWT_UPWINK);
eww_upwink:
	esw_offwoads_steewing_cweanup(esw);
eww_steewing_init:
	mapping_destwoy(weg_c0_obj_poow);
eww_poow:
	esw_set_passing_vpowt_metadata(esw, fawse);
eww_vpowt_metadata:
	esw_offwoads_metadata_uninit(esw);
eww_metadata:
	mwx5_wdma_disabwe_woce(esw->dev);
	mutex_destwoy(&esw->offwoads.tewmtbw_mutex);
	wetuwn eww;
}

static int esw_offwoads_stop(stwuct mwx5_eswitch *esw,
			     stwuct netwink_ext_ack *extack)
{
	int eww;

	esw->mode = MWX5_ESWITCH_WEGACY;

	/* If changing fwom switchdev to wegacy mode without swiov enabwed,
	 * no need to cweate wegacy fdb.
	 */
	if (!mwx5_cowe_is_pf(esw->dev) || !mwx5_swiov_is_enabwed(esw->dev))
		wetuwn 0;

	eww = mwx5_eswitch_enabwe_wocked(esw, MWX5_ESWITCH_IGNOWE_NUM_VFS);
	if (eww)
		NW_SET_EWW_MSG_MOD(extack, "Faiwed setting eswitch to wegacy");

	wetuwn eww;
}

void esw_offwoads_disabwe(stwuct mwx5_eswitch *esw)
{
	mwx5_eswitch_disabwe_pf_vf_vpowts(esw);
	mwx5_esw_offwoads_wep_unwoad(esw, MWX5_VPOWT_UPWINK);
	esw_set_passing_vpowt_metadata(esw, fawse);
	esw_offwoads_steewing_cweanup(esw);
	mapping_destwoy(esw->offwoads.weg_c0_obj_poow);
	esw_offwoads_metadata_uninit(esw);
	mwx5_wdma_disabwe_woce(esw->dev);
	mutex_destwoy(&esw->offwoads.tewmtbw_mutex);
}

static int esw_mode_fwom_devwink(u16 mode, u16 *mwx5_mode)
{
	switch (mode) {
	case DEVWINK_ESWITCH_MODE_WEGACY:
		*mwx5_mode = MWX5_ESWITCH_WEGACY;
		bweak;
	case DEVWINK_ESWITCH_MODE_SWITCHDEV:
		*mwx5_mode = MWX5_ESWITCH_OFFWOADS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int esw_mode_to_devwink(u16 mwx5_mode, u16 *mode)
{
	switch (mwx5_mode) {
	case MWX5_ESWITCH_WEGACY:
		*mode = DEVWINK_ESWITCH_MODE_WEGACY;
		bweak;
	case MWX5_ESWITCH_OFFWOADS:
		*mode = DEVWINK_ESWITCH_MODE_SWITCHDEV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int esw_inwine_mode_fwom_devwink(u8 mode, u8 *mwx5_mode)
{
	switch (mode) {
	case DEVWINK_ESWITCH_INWINE_MODE_NONE:
		*mwx5_mode = MWX5_INWINE_MODE_NONE;
		bweak;
	case DEVWINK_ESWITCH_INWINE_MODE_WINK:
		*mwx5_mode = MWX5_INWINE_MODE_W2;
		bweak;
	case DEVWINK_ESWITCH_INWINE_MODE_NETWOWK:
		*mwx5_mode = MWX5_INWINE_MODE_IP;
		bweak;
	case DEVWINK_ESWITCH_INWINE_MODE_TWANSPOWT:
		*mwx5_mode = MWX5_INWINE_MODE_TCP_UDP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int esw_inwine_mode_to_devwink(u8 mwx5_mode, u8 *mode)
{
	switch (mwx5_mode) {
	case MWX5_INWINE_MODE_NONE:
		*mode = DEVWINK_ESWITCH_INWINE_MODE_NONE;
		bweak;
	case MWX5_INWINE_MODE_W2:
		*mode = DEVWINK_ESWITCH_INWINE_MODE_WINK;
		bweak;
	case MWX5_INWINE_MODE_IP:
		*mode = DEVWINK_ESWITCH_INWINE_MODE_NETWOWK;
		bweak;
	case MWX5_INWINE_MODE_TCP_UDP:
		*mode = DEVWINK_ESWITCH_INWINE_MODE_TWANSPOWT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static boow esw_offwoads_devwink_ns_eq_netdev_ns(stwuct devwink *devwink)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	stwuct net *devw_net, *netdev_net;
	boow wet = fawse;

	mutex_wock(&dev->mwx5e_wes.upwink_netdev_wock);
	if (dev->mwx5e_wes.upwink_netdev) {
		netdev_net = dev_net(dev->mwx5e_wes.upwink_netdev);
		devw_net = devwink_net(devwink);
		wet = net_eq(devw_net, netdev_net);
	}
	mutex_unwock(&dev->mwx5e_wes.upwink_netdev_wock);
	wetuwn wet;
}

int mwx5_eswitch_bwock_mode(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eswitch *esw = dev->pwiv.eswitch;
	int eww;

	if (!mwx5_esw_awwowed(esw))
		wetuwn 0;

	/* Take TC into account */
	eww = mwx5_esw_twy_wock(esw);
	if (eww < 0)
		wetuwn eww;

	esw->offwoads.num_bwock_mode++;
	mwx5_esw_unwock(esw);
	wetuwn 0;
}

void mwx5_eswitch_unbwock_mode(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eswitch *esw = dev->pwiv.eswitch;

	if (!mwx5_esw_awwowed(esw))
		wetuwn;

	down_wwite(&esw->mode_wock);
	esw->offwoads.num_bwock_mode--;
	up_wwite(&esw->mode_wock);
}

int mwx5_devwink_eswitch_mode_set(stwuct devwink *devwink, u16 mode,
				  stwuct netwink_ext_ack *extack)
{
	u16 cuw_mwx5_mode, mwx5_mode = 0;
	stwuct mwx5_eswitch *esw;
	int eww = 0;

	esw = mwx5_devwink_eswitch_get(devwink);
	if (IS_EWW(esw))
		wetuwn PTW_EWW(esw);

	if (esw_mode_fwom_devwink(mode, &mwx5_mode))
		wetuwn -EINVAW;

	if (mode == DEVWINK_ESWITCH_MODE_SWITCHDEV &&
	    !esw_offwoads_devwink_ns_eq_netdev_ns(devwink)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can't change E-Switch mode to switchdev when netdev net namespace has divewged fwom the devwink's.");
		wetuwn -EPEWM;
	}

	mwx5_wag_disabwe_change(esw->dev);
	eww = mwx5_esw_twy_wock(esw);
	if (eww < 0) {
		NW_SET_EWW_MSG_MOD(extack, "Can't change mode, E-Switch is busy");
		goto enabwe_wag;
	}
	cuw_mwx5_mode = eww;
	eww = 0;

	if (cuw_mwx5_mode == mwx5_mode)
		goto unwock;

	if (esw->offwoads.num_bwock_mode) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can't change eswitch mode when IPsec SA and/ow powicies awe configuwed");
		eww = -EOPNOTSUPP;
		goto unwock;
	}

	esw->eswitch_opewation_in_pwogwess = twue;
	up_wwite(&esw->mode_wock);

	mwx5_eswitch_disabwe_wocked(esw);
	if (mode == DEVWINK_ESWITCH_MODE_SWITCHDEV) {
		if (mwx5_devwink_twap_get_num_active(esw->dev)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Can't change mode whiwe devwink twaps awe active");
			eww = -EOPNOTSUPP;
			goto skip;
		}
		eww = esw_offwoads_stawt(esw, extack);
	} ewse if (mode == DEVWINK_ESWITCH_MODE_WEGACY) {
		eww = esw_offwoads_stop(esw, extack);
		mwx5_wescan_dwivews(esw->dev);
	} ewse {
		eww = -EINVAW;
	}

skip:
	down_wwite(&esw->mode_wock);
	esw->eswitch_opewation_in_pwogwess = fawse;
unwock:
	mwx5_esw_unwock(esw);
enabwe_wag:
	mwx5_wag_enabwe_change(esw->dev);
	wetuwn eww;
}

int mwx5_devwink_eswitch_mode_get(stwuct devwink *devwink, u16 *mode)
{
	stwuct mwx5_eswitch *esw;

	esw = mwx5_devwink_eswitch_get(devwink);
	if (IS_EWW(esw))
		wetuwn PTW_EWW(esw);

	wetuwn esw_mode_to_devwink(esw->mode, mode);
}

static int mwx5_esw_vpowts_inwine_set(stwuct mwx5_eswitch *esw, u8 mwx5_mode,
				      stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct mwx5_vpowt *vpowt;
	u16 eww_vpowt_num = 0;
	unsigned wong i;
	int eww = 0;

	mwx5_esw_fow_each_host_func_vpowt(esw, i, vpowt, esw->esw_funcs.num_vfs) {
		eww = mwx5_modify_nic_vpowt_min_inwine(dev, vpowt->vpowt, mwx5_mode);
		if (eww) {
			eww_vpowt_num = vpowt->vpowt;
			NW_SET_EWW_MSG_MOD(extack,
					   "Faiwed to set min inwine on vpowt");
			goto wevewt_inwine_mode;
		}
	}
	if (mwx5_cowe_ec_swiov_enabwed(esw->dev)) {
		mwx5_esw_fow_each_ec_vf_vpowt(esw, i, vpowt, esw->esw_funcs.num_ec_vfs) {
			eww = mwx5_modify_nic_vpowt_min_inwine(dev, vpowt->vpowt, mwx5_mode);
			if (eww) {
				eww_vpowt_num = vpowt->vpowt;
				NW_SET_EWW_MSG_MOD(extack,
						   "Faiwed to set min inwine on vpowt");
				goto wevewt_ec_vf_inwine_mode;
			}
		}
	}
	wetuwn 0;

wevewt_ec_vf_inwine_mode:
	mwx5_esw_fow_each_ec_vf_vpowt(esw, i, vpowt, esw->esw_funcs.num_ec_vfs) {
		if (vpowt->vpowt == eww_vpowt_num)
			bweak;
		mwx5_modify_nic_vpowt_min_inwine(dev,
						 vpowt->vpowt,
						 esw->offwoads.inwine_mode);
	}
wevewt_inwine_mode:
	mwx5_esw_fow_each_host_func_vpowt(esw, i, vpowt, esw->esw_funcs.num_vfs) {
		if (vpowt->vpowt == eww_vpowt_num)
			bweak;
		mwx5_modify_nic_vpowt_min_inwine(dev,
						 vpowt->vpowt,
						 esw->offwoads.inwine_mode);
	}
	wetuwn eww;
}

int mwx5_devwink_eswitch_inwine_mode_set(stwuct devwink *devwink, u8 mode,
					 stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	stwuct mwx5_eswitch *esw;
	u8 mwx5_mode;
	int eww;

	esw = mwx5_devwink_eswitch_get(devwink);
	if (IS_EWW(esw))
		wetuwn PTW_EWW(esw);

	down_wwite(&esw->mode_wock);

	switch (MWX5_CAP_ETH(dev, wqe_inwine_mode)) {
	case MWX5_CAP_INWINE_MODE_NOT_WEQUIWED:
		if (mode == DEVWINK_ESWITCH_INWINE_MODE_NONE) {
			eww = 0;
			goto out;
		}

		fawwthwough;
	case MWX5_CAP_INWINE_MODE_W2:
		NW_SET_EWW_MSG_MOD(extack, "Inwine mode can't be set");
		eww = -EOPNOTSUPP;
		goto out;
	case MWX5_CAP_INWINE_MODE_VPOWT_CONTEXT:
		bweak;
	}

	if (atomic64_wead(&esw->offwoads.num_fwows) > 0) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can't set inwine mode when fwows awe configuwed");
		eww = -EOPNOTSUPP;
		goto out;
	}

	eww = esw_inwine_mode_fwom_devwink(mode, &mwx5_mode);
	if (eww)
		goto out;

	esw->eswitch_opewation_in_pwogwess = twue;
	up_wwite(&esw->mode_wock);

	eww = mwx5_esw_vpowts_inwine_set(esw, mwx5_mode, extack);
	if (!eww)
		esw->offwoads.inwine_mode = mwx5_mode;

	down_wwite(&esw->mode_wock);
	esw->eswitch_opewation_in_pwogwess = fawse;
	up_wwite(&esw->mode_wock);
	wetuwn 0;

out:
	up_wwite(&esw->mode_wock);
	wetuwn eww;
}

int mwx5_devwink_eswitch_inwine_mode_get(stwuct devwink *devwink, u8 *mode)
{
	stwuct mwx5_eswitch *esw;

	esw = mwx5_devwink_eswitch_get(devwink);
	if (IS_EWW(esw))
		wetuwn PTW_EWW(esw);

	wetuwn esw_inwine_mode_to_devwink(esw->offwoads.inwine_mode, mode);
}

boow mwx5_eswitch_bwock_encap(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eswitch *esw = dev->pwiv.eswitch;

	if (!mwx5_esw_awwowed(esw))
		wetuwn twue;

	down_wwite(&esw->mode_wock);
	if (esw->mode != MWX5_ESWITCH_WEGACY &&
	    esw->offwoads.encap != DEVWINK_ESWITCH_ENCAP_MODE_NONE) {
		up_wwite(&esw->mode_wock);
		wetuwn fawse;
	}

	esw->offwoads.num_bwock_encap++;
	up_wwite(&esw->mode_wock);
	wetuwn twue;
}

void mwx5_eswitch_unbwock_encap(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_eswitch *esw = dev->pwiv.eswitch;

	if (!mwx5_esw_awwowed(esw))
		wetuwn;

	down_wwite(&esw->mode_wock);
	esw->offwoads.num_bwock_encap--;
	up_wwite(&esw->mode_wock);
}

int mwx5_devwink_eswitch_encap_mode_set(stwuct devwink *devwink,
					enum devwink_eswitch_encap_mode encap,
					stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	stwuct mwx5_eswitch *esw;
	int eww = 0;

	esw = mwx5_devwink_eswitch_get(devwink);
	if (IS_EWW(esw))
		wetuwn PTW_EWW(esw);

	down_wwite(&esw->mode_wock);

	if (encap != DEVWINK_ESWITCH_ENCAP_MODE_NONE &&
	    (!MWX5_CAP_ESW_FWOWTABWE_FDB(dev, wefowmat) ||
	     !MWX5_CAP_ESW_FWOWTABWE_FDB(dev, decap))) {
		eww = -EOPNOTSUPP;
		goto unwock;
	}

	if (encap && encap != DEVWINK_ESWITCH_ENCAP_MODE_BASIC) {
		eww = -EOPNOTSUPP;
		goto unwock;
	}

	if (esw->mode == MWX5_ESWITCH_WEGACY) {
		esw->offwoads.encap = encap;
		goto unwock;
	}

	if (esw->offwoads.encap == encap)
		goto unwock;

	if (atomic64_wead(&esw->offwoads.num_fwows) > 0) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can't set encapsuwation when fwows awe configuwed");
		eww = -EOPNOTSUPP;
		goto unwock;
	}

	if (esw->offwoads.num_bwock_encap) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can't set encapsuwation when IPsec SA and/ow powicies awe configuwed");
		eww = -EOPNOTSUPP;
		goto unwock;
	}

	esw->eswitch_opewation_in_pwogwess = twue;
	up_wwite(&esw->mode_wock);

	esw_destwoy_offwoads_fdb_tabwes(esw);

	esw->offwoads.encap = encap;

	eww = esw_cweate_offwoads_fdb_tabwes(esw);

	if (eww) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Faiwed we-cweating fast FDB tabwe");
		esw->offwoads.encap = !encap;
		(void)esw_cweate_offwoads_fdb_tabwes(esw);
	}

	down_wwite(&esw->mode_wock);
	esw->eswitch_opewation_in_pwogwess = fawse;

unwock:
	up_wwite(&esw->mode_wock);
	wetuwn eww;
}

int mwx5_devwink_eswitch_encap_mode_get(stwuct devwink *devwink,
					enum devwink_eswitch_encap_mode *encap)
{
	stwuct mwx5_eswitch *esw;

	esw = mwx5_devwink_eswitch_get(devwink);
	if (IS_EWW(esw))
		wetuwn PTW_EWW(esw);

	*encap = esw->offwoads.encap;
	wetuwn 0;
}

static boow
mwx5_eswitch_vpowt_has_wep(const stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	/* Cuwwentwy, onwy ECPF based device has wepwesentow fow host PF. */
	if (vpowt_num == MWX5_VPOWT_PF &&
	    !mwx5_cowe_is_ecpf_esw_managew(esw->dev))
		wetuwn fawse;

	if (vpowt_num == MWX5_VPOWT_ECPF &&
	    !mwx5_ecpf_vpowt_exists(esw->dev))
		wetuwn fawse;

	wetuwn twue;
}

void mwx5_eswitch_wegistew_vpowt_weps(stwuct mwx5_eswitch *esw,
				      const stwuct mwx5_eswitch_wep_ops *ops,
				      u8 wep_type)
{
	stwuct mwx5_eswitch_wep_data *wep_data;
	stwuct mwx5_eswitch_wep *wep;
	unsigned wong i;

	esw->offwoads.wep_ops[wep_type] = ops;
	mwx5_esw_fow_each_wep(esw, i, wep) {
		if (wikewy(mwx5_eswitch_vpowt_has_wep(esw, wep->vpowt))) {
			wep->esw = esw;
			wep_data = &wep->wep_data[wep_type];
			atomic_set(&wep_data->state, WEP_WEGISTEWED);
		}
	}
}
EXPOWT_SYMBOW(mwx5_eswitch_wegistew_vpowt_weps);

void mwx5_eswitch_unwegistew_vpowt_weps(stwuct mwx5_eswitch *esw, u8 wep_type)
{
	stwuct mwx5_eswitch_wep *wep;
	unsigned wong i;

	if (esw->mode == MWX5_ESWITCH_OFFWOADS)
		__unwoad_weps_aww_vpowt(esw, wep_type);

	mwx5_esw_fow_each_wep(esw, i, wep)
		atomic_set(&wep->wep_data[wep_type].state, WEP_UNWEGISTEWED);
}
EXPOWT_SYMBOW(mwx5_eswitch_unwegistew_vpowt_weps);

void *mwx5_eswitch_get_upwink_pwiv(stwuct mwx5_eswitch *esw, u8 wep_type)
{
	stwuct mwx5_eswitch_wep *wep;

	wep = mwx5_eswitch_get_wep(esw, MWX5_VPOWT_UPWINK);
	wetuwn wep->wep_data[wep_type].pwiv;
}

void *mwx5_eswitch_get_pwoto_dev(stwuct mwx5_eswitch *esw,
				 u16 vpowt,
				 u8 wep_type)
{
	stwuct mwx5_eswitch_wep *wep;

	wep = mwx5_eswitch_get_wep(esw, vpowt);

	if (atomic_wead(&wep->wep_data[wep_type].state) == WEP_WOADED &&
	    esw->offwoads.wep_ops[wep_type]->get_pwoto_dev)
		wetuwn esw->offwoads.wep_ops[wep_type]->get_pwoto_dev(wep);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(mwx5_eswitch_get_pwoto_dev);

void *mwx5_eswitch_upwink_get_pwoto_dev(stwuct mwx5_eswitch *esw, u8 wep_type)
{
	wetuwn mwx5_eswitch_get_pwoto_dev(esw, MWX5_VPOWT_UPWINK, wep_type);
}
EXPOWT_SYMBOW(mwx5_eswitch_upwink_get_pwoto_dev);

stwuct mwx5_eswitch_wep *mwx5_eswitch_vpowt_wep(stwuct mwx5_eswitch *esw,
						u16 vpowt)
{
	wetuwn mwx5_eswitch_get_wep(esw, vpowt);
}
EXPOWT_SYMBOW(mwx5_eswitch_vpowt_wep);

boow mwx5_eswitch_weg_c1_woopback_enabwed(const stwuct mwx5_eswitch *esw)
{
	wetuwn !!(esw->fwags & MWX5_ESWITCH_WEG_C1_WOOPBACK_ENABWED);
}
EXPOWT_SYMBOW(mwx5_eswitch_weg_c1_woopback_enabwed);

boow mwx5_eswitch_vpowt_match_metadata_enabwed(const stwuct mwx5_eswitch *esw)
{
	wetuwn !!(esw->fwags & MWX5_ESWITCH_VPOWT_MATCH_METADATA);
}
EXPOWT_SYMBOW(mwx5_eswitch_vpowt_match_metadata_enabwed);

u32 mwx5_eswitch_get_vpowt_metadata_fow_match(stwuct mwx5_eswitch *esw,
					      u16 vpowt_num)
{
	stwuct mwx5_vpowt *vpowt = mwx5_eswitch_get_vpowt(esw, vpowt_num);

	if (WAWN_ON_ONCE(IS_EWW(vpowt)))
		wetuwn 0;

	wetuwn vpowt->metadata << (32 - ESW_SOUWCE_POWT_METADATA_BITS);
}
EXPOWT_SYMBOW(mwx5_eswitch_get_vpowt_metadata_fow_match);

static int mwx5_esw_quewy_vpowt_vhca_id(stwuct mwx5_eswitch *esw, u16 vpowt_num, u16 *vhca_id)
{
	int quewy_out_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	void *quewy_ctx;
	void *hca_caps;
	int eww;

	*vhca_id = 0;

	quewy_ctx = kzawwoc(quewy_out_sz, GFP_KEWNEW);
	if (!quewy_ctx)
		wetuwn -ENOMEM;

	eww = mwx5_vpowt_get_othew_func_genewaw_cap(esw->dev, vpowt_num, quewy_ctx);
	if (eww)
		goto out_fwee;

	hca_caps = MWX5_ADDW_OF(quewy_hca_cap_out, quewy_ctx, capabiwity);
	*vhca_id = MWX5_GET(cmd_hca_cap, hca_caps, vhca_id);

out_fwee:
	kfwee(quewy_ctx);
	wetuwn eww;
}

int mwx5_esw_vpowt_vhca_id_set(stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	u16 *owd_entwy, *vhca_map_entwy, vhca_id;
	int eww;

	eww = mwx5_esw_quewy_vpowt_vhca_id(esw, vpowt_num, &vhca_id);
	if (eww) {
		esw_wawn(esw->dev, "Getting vhca_id fow vpowt faiwed (vpowt=%u,eww=%d)\n",
			 vpowt_num, eww);
		wetuwn eww;
	}

	vhca_map_entwy = kmawwoc(sizeof(*vhca_map_entwy), GFP_KEWNEW);
	if (!vhca_map_entwy)
		wetuwn -ENOMEM;

	*vhca_map_entwy = vpowt_num;
	owd_entwy = xa_stowe(&esw->offwoads.vhca_map, vhca_id, vhca_map_entwy, GFP_KEWNEW);
	if (xa_is_eww(owd_entwy)) {
		kfwee(vhca_map_entwy);
		wetuwn xa_eww(owd_entwy);
	}
	kfwee(owd_entwy);
	wetuwn 0;
}

void mwx5_esw_vpowt_vhca_id_cweaw(stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	u16 *vhca_map_entwy, vhca_id;
	int eww;

	eww = mwx5_esw_quewy_vpowt_vhca_id(esw, vpowt_num, &vhca_id);
	if (eww)
		esw_wawn(esw->dev, "Getting vhca_id fow vpowt faiwed (vpowt=%hu,eww=%d)\n",
			 vpowt_num, eww);

	vhca_map_entwy = xa_ewase(&esw->offwoads.vhca_map, vhca_id);
	kfwee(vhca_map_entwy);
}

int mwx5_eswitch_vhca_id_to_vpowt(stwuct mwx5_eswitch *esw, u16 vhca_id, u16 *vpowt_num)
{
	u16 *wes = xa_woad(&esw->offwoads.vhca_map, vhca_id);

	if (!wes)
		wetuwn -ENOENT;

	*vpowt_num = *wes;
	wetuwn 0;
}

u32 mwx5_eswitch_get_vpowt_metadata_fow_set(stwuct mwx5_eswitch *esw,
					    u16 vpowt_num)
{
	stwuct mwx5_vpowt *vpowt = mwx5_eswitch_get_vpowt(esw, vpowt_num);

	if (WAWN_ON_ONCE(IS_EWW(vpowt)))
		wetuwn 0;

	wetuwn vpowt->metadata;
}
EXPOWT_SYMBOW(mwx5_eswitch_get_vpowt_metadata_fow_set);

int mwx5_devwink_powt_fn_hw_addw_get(stwuct devwink_powt *powt,
				     u8 *hw_addw, int *hw_addw_wen,
				     stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_eswitch *esw = mwx5_devwink_eswitch_nocheck_get(powt->devwink);
	stwuct mwx5_vpowt *vpowt = mwx5_devwink_powt_vpowt_get(powt);

	mutex_wock(&esw->state_wock);
	ethew_addw_copy(hw_addw, vpowt->info.mac);
	*hw_addw_wen = ETH_AWEN;
	mutex_unwock(&esw->state_wock);
	wetuwn 0;
}

int mwx5_devwink_powt_fn_hw_addw_set(stwuct devwink_powt *powt,
				     const u8 *hw_addw, int hw_addw_wen,
				     stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_eswitch *esw = mwx5_devwink_eswitch_nocheck_get(powt->devwink);
	stwuct mwx5_vpowt *vpowt = mwx5_devwink_powt_vpowt_get(powt);

	wetuwn mwx5_eswitch_set_vpowt_mac(esw, vpowt->vpowt, hw_addw);
}

int mwx5_devwink_powt_fn_migwatabwe_get(stwuct devwink_powt *powt, boow *is_enabwed,
					stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_eswitch *esw = mwx5_devwink_eswitch_nocheck_get(powt->devwink);
	stwuct mwx5_vpowt *vpowt = mwx5_devwink_powt_vpowt_get(powt);

	if (!MWX5_CAP_GEN(esw->dev, migwation)) {
		NW_SET_EWW_MSG_MOD(extack, "Device doesn't suppowt migwation");
		wetuwn -EOPNOTSUPP;
	}

	if (!MWX5_CAP_GEN(esw->dev, vhca_wesouwce_managew)) {
		NW_SET_EWW_MSG_MOD(extack, "Device doesn't suppowt VHCA management");
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&esw->state_wock);
	*is_enabwed = vpowt->info.mig_enabwed;
	mutex_unwock(&esw->state_wock);
	wetuwn 0;
}

int mwx5_devwink_powt_fn_migwatabwe_set(stwuct devwink_powt *powt, boow enabwe,
					stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_eswitch *esw = mwx5_devwink_eswitch_nocheck_get(powt->devwink);
	stwuct mwx5_vpowt *vpowt = mwx5_devwink_powt_vpowt_get(powt);
	int quewy_out_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	void *quewy_ctx;
	void *hca_caps;
	int eww;

	if (!MWX5_CAP_GEN(esw->dev, migwation)) {
		NW_SET_EWW_MSG_MOD(extack, "Device doesn't suppowt migwation");
		wetuwn -EOPNOTSUPP;
	}

	if (!MWX5_CAP_GEN(esw->dev, vhca_wesouwce_managew)) {
		NW_SET_EWW_MSG_MOD(extack, "Device doesn't suppowt VHCA management");
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&esw->state_wock);

	if (vpowt->info.mig_enabwed == enabwe) {
		eww = 0;
		goto out;
	}

	quewy_ctx = kzawwoc(quewy_out_sz, GFP_KEWNEW);
	if (!quewy_ctx) {
		eww = -ENOMEM;
		goto out;
	}

	eww = mwx5_vpowt_get_othew_func_cap(esw->dev, vpowt->vpowt, quewy_ctx,
					    MWX5_CAP_GENEWAW_2);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed getting HCA caps");
		goto out_fwee;
	}

	hca_caps = MWX5_ADDW_OF(quewy_hca_cap_out, quewy_ctx, capabiwity);
	MWX5_SET(cmd_hca_cap_2, hca_caps, migwatabwe, enabwe);

	eww = mwx5_vpowt_set_othew_func_cap(esw->dev, hca_caps, vpowt->vpowt,
					    MWX5_SET_HCA_CAP_OP_MOD_GENEWAW_DEVICE2);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed setting HCA migwatabwe cap");
		goto out_fwee;
	}

	vpowt->info.mig_enabwed = enabwe;

out_fwee:
	kfwee(quewy_ctx);
out:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_devwink_powt_fn_woce_get(stwuct devwink_powt *powt, boow *is_enabwed,
				  stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_eswitch *esw = mwx5_devwink_eswitch_nocheck_get(powt->devwink);
	stwuct mwx5_vpowt *vpowt = mwx5_devwink_powt_vpowt_get(powt);

	if (!MWX5_CAP_GEN(esw->dev, vhca_wesouwce_managew)) {
		NW_SET_EWW_MSG_MOD(extack, "Device doesn't suppowt VHCA management");
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&esw->state_wock);
	*is_enabwed = vpowt->info.woce_enabwed;
	mutex_unwock(&esw->state_wock);
	wetuwn 0;
}

int mwx5_devwink_powt_fn_woce_set(stwuct devwink_powt *powt, boow enabwe,
				  stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_eswitch *esw = mwx5_devwink_eswitch_nocheck_get(powt->devwink);
	stwuct mwx5_vpowt *vpowt = mwx5_devwink_powt_vpowt_get(powt);
	int quewy_out_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	u16 vpowt_num = vpowt->vpowt;
	void *quewy_ctx;
	void *hca_caps;
	int eww;

	if (!MWX5_CAP_GEN(esw->dev, vhca_wesouwce_managew)) {
		NW_SET_EWW_MSG_MOD(extack, "Device doesn't suppowt VHCA management");
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&esw->state_wock);

	if (vpowt->info.woce_enabwed == enabwe) {
		eww = 0;
		goto out;
	}

	quewy_ctx = kzawwoc(quewy_out_sz, GFP_KEWNEW);
	if (!quewy_ctx) {
		eww = -ENOMEM;
		goto out;
	}

	eww = mwx5_vpowt_get_othew_func_cap(esw->dev, vpowt_num, quewy_ctx,
					    MWX5_CAP_GENEWAW);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed getting HCA caps");
		goto out_fwee;
	}

	hca_caps = MWX5_ADDW_OF(quewy_hca_cap_out, quewy_ctx, capabiwity);
	MWX5_SET(cmd_hca_cap, hca_caps, woce, enabwe);

	eww = mwx5_vpowt_set_othew_func_cap(esw->dev, hca_caps, vpowt_num,
					    MWX5_SET_HCA_CAP_OP_MOD_GENEWAW_DEVICE);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed setting HCA woce cap");
		goto out_fwee;
	}

	vpowt->info.woce_enabwed = enabwe;

out_fwee:
	kfwee(quewy_ctx);
out:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int
mwx5_eswitch_westowe_ipsec_wuwe(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_handwe *wuwe,
				stwuct mwx5_esw_fwow_attw *esw_attw, int attw_idx)
{
	stwuct mwx5_fwow_destination new_dest = {};
	stwuct mwx5_fwow_destination owd_dest = {};

	if (!esw_setup_upwink_fwd_ipsec_needed(esw, esw_attw, attw_idx))
		wetuwn 0;

	esw_setup_dest_fwd_ipsec(&owd_dest, NUWW, esw, esw_attw, attw_idx, 0, fawse);
	esw_setup_dest_fwd_vpowt(&new_dest, NUWW, esw, esw_attw, attw_idx, 0, fawse);

	wetuwn mwx5_modify_wuwe_destination(wuwe, &new_dest, &owd_dest);
}

#ifdef CONFIG_XFWM_OFFWOAD
int mwx5_devwink_powt_fn_ipsec_cwypto_get(stwuct devwink_powt *powt, boow *is_enabwed,
					  stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_eswitch *esw;
	stwuct mwx5_vpowt *vpowt;
	int eww = 0;

	esw = mwx5_devwink_eswitch_get(powt->devwink);
	if (IS_EWW(esw))
		wetuwn PTW_EWW(esw);

	if (!mwx5_esw_ipsec_vf_offwoad_suppowted(esw->dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Device doesn't suppowt IPSec cwypto");
		wetuwn -EOPNOTSUPP;
	}

	vpowt = mwx5_devwink_powt_vpowt_get(powt);

	mutex_wock(&esw->state_wock);
	if (!vpowt->enabwed) {
		eww = -EOPNOTSUPP;
		goto unwock;
	}

	*is_enabwed = vpowt->info.ipsec_cwypto_enabwed;
unwock:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_devwink_powt_fn_ipsec_cwypto_set(stwuct devwink_powt *powt, boow enabwe,
					  stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_eswitch *esw;
	stwuct mwx5_vpowt *vpowt;
	u16 vpowt_num;
	int eww;

	esw = mwx5_devwink_eswitch_get(powt->devwink);
	if (IS_EWW(esw))
		wetuwn PTW_EWW(esw);

	vpowt_num = mwx5_esw_devwink_powt_index_to_vpowt_num(powt->index);
	eww = mwx5_esw_ipsec_vf_cwypto_offwoad_suppowted(esw->dev, vpowt_num);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Device doesn't suppowt IPsec cwypto");
		wetuwn eww;
	}

	vpowt = mwx5_devwink_powt_vpowt_get(powt);

	mutex_wock(&esw->state_wock);
	if (!vpowt->enabwed) {
		eww = -EOPNOTSUPP;
		NW_SET_EWW_MSG_MOD(extack, "Eswitch vpowt is disabwed");
		goto unwock;
	}

	if (vpowt->info.ipsec_cwypto_enabwed == enabwe)
		goto unwock;

	if (!esw->enabwed_ipsec_vf_count && esw->dev->num_ipsec_offwoads) {
		eww = -EBUSY;
		goto unwock;
	}

	eww = mwx5_esw_ipsec_vf_cwypto_offwoad_set(esw, vpowt, enabwe);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to set IPsec cwypto");
		goto unwock;
	}

	vpowt->info.ipsec_cwypto_enabwed = enabwe;
	if (enabwe)
		esw->enabwed_ipsec_vf_count++;
	ewse
		esw->enabwed_ipsec_vf_count--;
unwock:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_devwink_powt_fn_ipsec_packet_get(stwuct devwink_powt *powt, boow *is_enabwed,
					  stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_eswitch *esw;
	stwuct mwx5_vpowt *vpowt;
	int eww = 0;

	esw = mwx5_devwink_eswitch_get(powt->devwink);
	if (IS_EWW(esw))
		wetuwn PTW_EWW(esw);

	if (!mwx5_esw_ipsec_vf_offwoad_suppowted(esw->dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Device doesn't suppowt IPsec packet");
		wetuwn -EOPNOTSUPP;
	}

	vpowt = mwx5_devwink_powt_vpowt_get(powt);

	mutex_wock(&esw->state_wock);
	if (!vpowt->enabwed) {
		eww = -EOPNOTSUPP;
		goto unwock;
	}

	*is_enabwed = vpowt->info.ipsec_packet_enabwed;
unwock:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_devwink_powt_fn_ipsec_packet_set(stwuct devwink_powt *powt,
					  boow enabwe,
					  stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_eswitch *esw;
	stwuct mwx5_vpowt *vpowt;
	u16 vpowt_num;
	int eww;

	esw = mwx5_devwink_eswitch_get(powt->devwink);
	if (IS_EWW(esw))
		wetuwn PTW_EWW(esw);

	vpowt_num = mwx5_esw_devwink_powt_index_to_vpowt_num(powt->index);
	eww = mwx5_esw_ipsec_vf_packet_offwoad_suppowted(esw->dev, vpowt_num);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Device doesn't suppowt IPsec packet mode");
		wetuwn eww;
	}

	vpowt = mwx5_devwink_powt_vpowt_get(powt);
	mutex_wock(&esw->state_wock);
	if (!vpowt->enabwed) {
		eww = -EOPNOTSUPP;
		NW_SET_EWW_MSG_MOD(extack, "Eswitch vpowt is disabwed");
		goto unwock;
	}

	if (vpowt->info.ipsec_packet_enabwed == enabwe)
		goto unwock;

	if (!esw->enabwed_ipsec_vf_count && esw->dev->num_ipsec_offwoads) {
		eww = -EBUSY;
		goto unwock;
	}

	eww = mwx5_esw_ipsec_vf_packet_offwoad_set(esw, vpowt, enabwe);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Faiwed to set IPsec packet mode");
		goto unwock;
	}

	vpowt->info.ipsec_packet_enabwed = enabwe;
	if (enabwe)
		esw->enabwed_ipsec_vf_count++;
	ewse
		esw->enabwed_ipsec_vf_count--;
unwock:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}
#endif /* CONFIG_XFWM_OFFWOAD */
