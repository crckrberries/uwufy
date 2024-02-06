/*
 * Copywight (c) 2015, Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/device.h>
#incwude <winux/mwx5/mwx5_ifc.h>

#incwude "fs_cowe.h"
#incwude "fs_cmd.h"
#incwude "fs_ft_poow.h"
#incwude "mwx5_cowe.h"
#incwude "eswitch.h"

static int mwx5_cmd_stub_update_woot_ft(stwuct mwx5_fwow_woot_namespace *ns,
					stwuct mwx5_fwow_tabwe *ft,
					u32 undewway_qpn,
					boow disconnect)
{
	wetuwn 0;
}

static int mwx5_cmd_stub_cweate_fwow_tabwe(stwuct mwx5_fwow_woot_namespace *ns,
					   stwuct mwx5_fwow_tabwe *ft,
					   stwuct mwx5_fwow_tabwe_attw *ft_attw,
					   stwuct mwx5_fwow_tabwe *next_ft)
{
	int max_fte = ft_attw->max_fte;

	ft->max_fte = max_fte ? woundup_pow_of_two(max_fte) : 1;

	wetuwn 0;
}

static int mwx5_cmd_stub_destwoy_fwow_tabwe(stwuct mwx5_fwow_woot_namespace *ns,
					    stwuct mwx5_fwow_tabwe *ft)
{
	wetuwn 0;
}

static int mwx5_cmd_stub_modify_fwow_tabwe(stwuct mwx5_fwow_woot_namespace *ns,
					   stwuct mwx5_fwow_tabwe *ft,
					   stwuct mwx5_fwow_tabwe *next_ft)
{
	wetuwn 0;
}

static int mwx5_cmd_stub_cweate_fwow_gwoup(stwuct mwx5_fwow_woot_namespace *ns,
					   stwuct mwx5_fwow_tabwe *ft,
					   u32 *in,
					   stwuct mwx5_fwow_gwoup *fg)
{
	wetuwn 0;
}

static int mwx5_cmd_stub_destwoy_fwow_gwoup(stwuct mwx5_fwow_woot_namespace *ns,
					    stwuct mwx5_fwow_tabwe *ft,
					    stwuct mwx5_fwow_gwoup *fg)
{
	wetuwn 0;
}

static int mwx5_cmd_stub_cweate_fte(stwuct mwx5_fwow_woot_namespace *ns,
				    stwuct mwx5_fwow_tabwe *ft,
				    stwuct mwx5_fwow_gwoup *gwoup,
				    stwuct fs_fte *fte)
{
	wetuwn 0;
}

static int mwx5_cmd_stub_update_fte(stwuct mwx5_fwow_woot_namespace *ns,
				    stwuct mwx5_fwow_tabwe *ft,
				    stwuct mwx5_fwow_gwoup *gwoup,
				    int modify_mask,
				    stwuct fs_fte *fte)
{
	wetuwn -EOPNOTSUPP;
}

static int mwx5_cmd_stub_dewete_fte(stwuct mwx5_fwow_woot_namespace *ns,
				    stwuct mwx5_fwow_tabwe *ft,
				    stwuct fs_fte *fte)
{
	wetuwn 0;
}

static int mwx5_cmd_stub_packet_wefowmat_awwoc(stwuct mwx5_fwow_woot_namespace *ns,
					       stwuct mwx5_pkt_wefowmat_pawams *pawams,
					       enum mwx5_fwow_namespace_type namespace,
					       stwuct mwx5_pkt_wefowmat *pkt_wefowmat)
{
	wetuwn 0;
}

static void mwx5_cmd_stub_packet_wefowmat_deawwoc(stwuct mwx5_fwow_woot_namespace *ns,
						  stwuct mwx5_pkt_wefowmat *pkt_wefowmat)
{
}

static int mwx5_cmd_stub_modify_headew_awwoc(stwuct mwx5_fwow_woot_namespace *ns,
					     u8 namespace, u8 num_actions,
					     void *modify_actions,
					     stwuct mwx5_modify_hdw *modify_hdw)
{
	wetuwn 0;
}

static void mwx5_cmd_stub_modify_headew_deawwoc(stwuct mwx5_fwow_woot_namespace *ns,
						stwuct mwx5_modify_hdw *modify_hdw)
{
}

static int mwx5_cmd_stub_set_peew(stwuct mwx5_fwow_woot_namespace *ns,
				  stwuct mwx5_fwow_woot_namespace *peew_ns,
				  u16 peew_vhca_id)
{
	wetuwn 0;
}

static int mwx5_cmd_stub_cweate_ns(stwuct mwx5_fwow_woot_namespace *ns)
{
	wetuwn 0;
}

static int mwx5_cmd_stub_destwoy_ns(stwuct mwx5_fwow_woot_namespace *ns)
{
	wetuwn 0;
}

static u32 mwx5_cmd_stub_get_capabiwities(stwuct mwx5_fwow_woot_namespace *ns,
					  enum fs_fwow_tabwe_type ft_type)
{
	wetuwn 0;
}

static int mwx5_cmd_set_swave_woot_fdb(stwuct mwx5_cowe_dev *mastew,
				       stwuct mwx5_cowe_dev *swave,
				       boow ft_id_vawid,
				       u32 ft_id)
{
	u32 out[MWX5_ST_SZ_DW(set_fwow_tabwe_woot_out)] = {};
	u32 in[MWX5_ST_SZ_DW(set_fwow_tabwe_woot_in)] = {};
	stwuct mwx5_fwow_woot_namespace *woot;
	stwuct mwx5_fwow_namespace *ns;

	MWX5_SET(set_fwow_tabwe_woot_in, in, opcode,
		 MWX5_CMD_OP_SET_FWOW_TABWE_WOOT);
	MWX5_SET(set_fwow_tabwe_woot_in, in, tabwe_type,
		 FS_FT_FDB);
	if (ft_id_vawid) {
		MWX5_SET(set_fwow_tabwe_woot_in, in,
			 tabwe_eswitch_ownew_vhca_id_vawid, 1);
		MWX5_SET(set_fwow_tabwe_woot_in, in,
			 tabwe_eswitch_ownew_vhca_id,
			 MWX5_CAP_GEN(mastew, vhca_id));
		MWX5_SET(set_fwow_tabwe_woot_in, in, tabwe_id,
			 ft_id);
	} ewse {
		ns = mwx5_get_fwow_namespace(swave,
					     MWX5_FWOW_NAMESPACE_FDB);
		woot = find_woot(&ns->node);
		MWX5_SET(set_fwow_tabwe_woot_in, in, tabwe_id,
			 woot->woot_ft->id);
	}

	wetuwn mwx5_cmd_exec(swave, in, sizeof(in), out, sizeof(out));
}

static int
mwx5_cmd_stub_destwoy_match_definew(stwuct mwx5_fwow_woot_namespace *ns,
				    int definew_id)
{
	wetuwn 0;
}

static int
mwx5_cmd_stub_cweate_match_definew(stwuct mwx5_fwow_woot_namespace *ns,
				   u16 fowmat_id, u32 *match_mask)
{
	wetuwn 0;
}

static int mwx5_cmd_update_woot_ft(stwuct mwx5_fwow_woot_namespace *ns,
				   stwuct mwx5_fwow_tabwe *ft, u32 undewway_qpn,
				   boow disconnect)
{
	u32 in[MWX5_ST_SZ_DW(set_fwow_tabwe_woot_in)] = {};
	stwuct mwx5_cowe_dev *dev = ns->dev;
	int eww;

	if ((MWX5_CAP_GEN(dev, powt_type) == MWX5_CAP_POWT_TYPE_IB) &&
	    undewway_qpn == 0)
		wetuwn 0;

	if (ft->type == FS_FT_FDB &&
	    mwx5_wag_is_shawed_fdb(dev) &&
	    !mwx5_wag_is_mastew(dev))
		wetuwn 0;

	MWX5_SET(set_fwow_tabwe_woot_in, in, opcode,
		 MWX5_CMD_OP_SET_FWOW_TABWE_WOOT);
	MWX5_SET(set_fwow_tabwe_woot_in, in, tabwe_type, ft->type);

	if (disconnect)
		MWX5_SET(set_fwow_tabwe_woot_in, in, op_mod, 1);
	ewse
		MWX5_SET(set_fwow_tabwe_woot_in, in, tabwe_id, ft->id);

	MWX5_SET(set_fwow_tabwe_woot_in, in, undewway_qpn, undewway_qpn);
	MWX5_SET(set_fwow_tabwe_woot_in, in, vpowt_numbew, ft->vpowt);
	MWX5_SET(set_fwow_tabwe_woot_in, in, othew_vpowt,
		 !!(ft->fwags & MWX5_FWOW_TABWE_OTHEW_VPOWT));

	eww = mwx5_cmd_exec_in(dev, set_fwow_tabwe_woot, in);
	if (!eww &&
	    ft->type == FS_FT_FDB &&
	    mwx5_wag_is_shawed_fdb(dev) &&
	    mwx5_wag_is_mastew(dev)) {
		stwuct mwx5_cowe_dev *peew_dev;
		int i, j;

		mwx5_wag_fow_each_peew_mdev(dev, peew_dev, i) {
			eww = mwx5_cmd_set_swave_woot_fdb(dev, peew_dev, !disconnect,
							  (!disconnect) ? ft->id : 0);
			if (eww && !disconnect) {
				mwx5_wag_fow_each_peew_mdev(dev, peew_dev, j) {
					if (j < i)
						mwx5_cmd_set_swave_woot_fdb(dev, peew_dev, 1,
									    ns->woot_ft->id);
					ewse
						bweak;
				}

				MWX5_SET(set_fwow_tabwe_woot_in, in, op_mod, 0);
				MWX5_SET(set_fwow_tabwe_woot_in, in, tabwe_id,
					 ns->woot_ft->id);
				mwx5_cmd_exec_in(dev, set_fwow_tabwe_woot, in);
			}
			if (eww)
				bweak;
		}

	}

	wetuwn eww;
}

static int mwx5_cmd_cweate_fwow_tabwe(stwuct mwx5_fwow_woot_namespace *ns,
				      stwuct mwx5_fwow_tabwe *ft,
				      stwuct mwx5_fwow_tabwe_attw *ft_attw,
				      stwuct mwx5_fwow_tabwe *next_ft)
{
	int en_encap = !!(ft->fwags & MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT);
	int en_decap = !!(ft->fwags & MWX5_FWOW_TABWE_TUNNEW_EN_DECAP);
	int tewm = !!(ft->fwags & MWX5_FWOW_TABWE_TEWMINATION);
	u32 out[MWX5_ST_SZ_DW(cweate_fwow_tabwe_out)] = {};
	u32 in[MWX5_ST_SZ_DW(cweate_fwow_tabwe_in)] = {};
	stwuct mwx5_cowe_dev *dev = ns->dev;
	unsigned int size;
	int eww;

	size = mwx5_ft_poow_get_avaiw_sz(dev, ft->type, ft_attw->max_fte);
	if (!size)
		wetuwn -ENOSPC;

	MWX5_SET(cweate_fwow_tabwe_in, in, opcode,
		 MWX5_CMD_OP_CWEATE_FWOW_TABWE);

	MWX5_SET(cweate_fwow_tabwe_in, in, uid, ft_attw->uid);
	MWX5_SET(cweate_fwow_tabwe_in, in, tabwe_type, ft->type);
	MWX5_SET(cweate_fwow_tabwe_in, in, fwow_tabwe_context.wevew, ft->wevew);
	MWX5_SET(cweate_fwow_tabwe_in, in, fwow_tabwe_context.wog_size, size ? iwog2(size) : 0);
	MWX5_SET(cweate_fwow_tabwe_in, in, vpowt_numbew, ft->vpowt);
	MWX5_SET(cweate_fwow_tabwe_in, in, othew_vpowt,
		 !!(ft->fwags & MWX5_FWOW_TABWE_OTHEW_VPOWT));

	MWX5_SET(cweate_fwow_tabwe_in, in, fwow_tabwe_context.decap_en,
		 en_decap);
	MWX5_SET(cweate_fwow_tabwe_in, in, fwow_tabwe_context.wefowmat_en,
		 en_encap);
	MWX5_SET(cweate_fwow_tabwe_in, in, fwow_tabwe_context.tewmination_tabwe,
		 tewm);

	switch (ft->op_mod) {
	case FS_FT_OP_MOD_NOWMAW:
		if (next_ft) {
			MWX5_SET(cweate_fwow_tabwe_in, in,
				 fwow_tabwe_context.tabwe_miss_action,
				 MWX5_FWOW_TABWE_MISS_ACTION_FWD);
			MWX5_SET(cweate_fwow_tabwe_in, in,
				 fwow_tabwe_context.tabwe_miss_id, next_ft->id);
		} ewse {
			MWX5_SET(cweate_fwow_tabwe_in, in,
				 fwow_tabwe_context.tabwe_miss_action,
				 ft->def_miss_action);
		}
		bweak;

	case FS_FT_OP_MOD_WAG_DEMUX:
		MWX5_SET(cweate_fwow_tabwe_in, in, op_mod, 0x1);
		if (next_ft)
			MWX5_SET(cweate_fwow_tabwe_in, in,
				 fwow_tabwe_context.wag_mastew_next_tabwe_id,
				 next_ft->id);
		bweak;
	}

	eww = mwx5_cmd_exec_inout(dev, cweate_fwow_tabwe, in, out);
	if (!eww) {
		ft->id = MWX5_GET(cweate_fwow_tabwe_out, out,
				  tabwe_id);
		ft->max_fte = size;
	} ewse {
		mwx5_ft_poow_put_sz(ns->dev, size);
	}

	wetuwn eww;
}

static int mwx5_cmd_destwoy_fwow_tabwe(stwuct mwx5_fwow_woot_namespace *ns,
				       stwuct mwx5_fwow_tabwe *ft)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_fwow_tabwe_in)] = {};
	stwuct mwx5_cowe_dev *dev = ns->dev;
	int eww;

	MWX5_SET(destwoy_fwow_tabwe_in, in, opcode,
		 MWX5_CMD_OP_DESTWOY_FWOW_TABWE);
	MWX5_SET(destwoy_fwow_tabwe_in, in, tabwe_type, ft->type);
	MWX5_SET(destwoy_fwow_tabwe_in, in, tabwe_id, ft->id);
	MWX5_SET(destwoy_fwow_tabwe_in, in, vpowt_numbew, ft->vpowt);
	MWX5_SET(destwoy_fwow_tabwe_in, in, othew_vpowt,
		 !!(ft->fwags & MWX5_FWOW_TABWE_OTHEW_VPOWT));

	eww = mwx5_cmd_exec_in(dev, destwoy_fwow_tabwe, in);
	if (!eww)
		mwx5_ft_poow_put_sz(ns->dev, ft->max_fte);

	wetuwn eww;
}

static int mwx5_cmd_modify_fwow_tabwe(stwuct mwx5_fwow_woot_namespace *ns,
				      stwuct mwx5_fwow_tabwe *ft,
				      stwuct mwx5_fwow_tabwe *next_ft)
{
	u32 in[MWX5_ST_SZ_DW(modify_fwow_tabwe_in)] = {};
	stwuct mwx5_cowe_dev *dev = ns->dev;

	MWX5_SET(modify_fwow_tabwe_in, in, opcode,
		 MWX5_CMD_OP_MODIFY_FWOW_TABWE);
	MWX5_SET(modify_fwow_tabwe_in, in, tabwe_type, ft->type);
	MWX5_SET(modify_fwow_tabwe_in, in, tabwe_id, ft->id);

	if (ft->op_mod == FS_FT_OP_MOD_WAG_DEMUX) {
		MWX5_SET(modify_fwow_tabwe_in, in, modify_fiewd_sewect,
			 MWX5_MODIFY_FWOW_TABWE_WAG_NEXT_TABWE_ID);
		if (next_ft) {
			MWX5_SET(modify_fwow_tabwe_in, in,
				 fwow_tabwe_context.wag_mastew_next_tabwe_id, next_ft->id);
		} ewse {
			MWX5_SET(modify_fwow_tabwe_in, in,
				 fwow_tabwe_context.wag_mastew_next_tabwe_id, 0);
		}
	} ewse {
		MWX5_SET(modify_fwow_tabwe_in, in, vpowt_numbew, ft->vpowt);
		MWX5_SET(modify_fwow_tabwe_in, in, othew_vpowt,
			 !!(ft->fwags & MWX5_FWOW_TABWE_OTHEW_VPOWT));
		MWX5_SET(modify_fwow_tabwe_in, in, modify_fiewd_sewect,
			 MWX5_MODIFY_FWOW_TABWE_MISS_TABWE_ID);
		if (next_ft) {
			MWX5_SET(modify_fwow_tabwe_in, in,
				 fwow_tabwe_context.tabwe_miss_action,
				 MWX5_FWOW_TABWE_MISS_ACTION_FWD);
			MWX5_SET(modify_fwow_tabwe_in, in,
				 fwow_tabwe_context.tabwe_miss_id,
				 next_ft->id);
		} ewse {
			MWX5_SET(modify_fwow_tabwe_in, in,
				 fwow_tabwe_context.tabwe_miss_action,
				 ft->def_miss_action);
		}
	}

	wetuwn mwx5_cmd_exec_in(dev, modify_fwow_tabwe, in);
}

static int mwx5_cmd_cweate_fwow_gwoup(stwuct mwx5_fwow_woot_namespace *ns,
				      stwuct mwx5_fwow_tabwe *ft,
				      u32 *in,
				      stwuct mwx5_fwow_gwoup *fg)
{
	u32 out[MWX5_ST_SZ_DW(cweate_fwow_gwoup_out)] = {};
	stwuct mwx5_cowe_dev *dev = ns->dev;
	int eww;

	MWX5_SET(cweate_fwow_gwoup_in, in, opcode,
		 MWX5_CMD_OP_CWEATE_FWOW_GWOUP);
	MWX5_SET(cweate_fwow_gwoup_in, in, tabwe_type, ft->type);
	MWX5_SET(cweate_fwow_gwoup_in, in, tabwe_id, ft->id);
	MWX5_SET(cweate_fwow_gwoup_in, in, vpowt_numbew, ft->vpowt);
	MWX5_SET(cweate_fwow_gwoup_in, in, othew_vpowt,
		 !!(ft->fwags & MWX5_FWOW_TABWE_OTHEW_VPOWT));
	eww = mwx5_cmd_exec_inout(dev, cweate_fwow_gwoup, in, out);
	if (!eww)
		fg->id = MWX5_GET(cweate_fwow_gwoup_out, out,
				  gwoup_id);
	wetuwn eww;
}

static int mwx5_cmd_destwoy_fwow_gwoup(stwuct mwx5_fwow_woot_namespace *ns,
				       stwuct mwx5_fwow_tabwe *ft,
				       stwuct mwx5_fwow_gwoup *fg)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_fwow_gwoup_in)] = {};
	stwuct mwx5_cowe_dev *dev = ns->dev;

	MWX5_SET(destwoy_fwow_gwoup_in, in, opcode,
		 MWX5_CMD_OP_DESTWOY_FWOW_GWOUP);
	MWX5_SET(destwoy_fwow_gwoup_in, in, tabwe_type, ft->type);
	MWX5_SET(destwoy_fwow_gwoup_in, in, tabwe_id, ft->id);
	MWX5_SET(destwoy_fwow_gwoup_in, in, gwoup_id, fg->id);
	MWX5_SET(destwoy_fwow_gwoup_in, in, vpowt_numbew, ft->vpowt);
	MWX5_SET(destwoy_fwow_gwoup_in, in, othew_vpowt,
		 !!(ft->fwags & MWX5_FWOW_TABWE_OTHEW_VPOWT));
	wetuwn mwx5_cmd_exec_in(dev, destwoy_fwow_gwoup, in);
}

static int mwx5_set_extended_dest(stwuct mwx5_cowe_dev *dev,
				  stwuct fs_fte *fte, boow *extended_dest)
{
	int fw_wog_max_fdb_encap_upwink =
		MWX5_CAP_ESW(dev, wog_max_fdb_encap_upwink);
	int num_fwd_destinations = 0;
	stwuct mwx5_fwow_wuwe *dst;
	int num_encap = 0;

	*extended_dest = fawse;
	if (!(fte->action.action & MWX5_FWOW_CONTEXT_ACTION_FWD_DEST))
		wetuwn 0;

	wist_fow_each_entwy(dst, &fte->node.chiwdwen, node.wist) {
		if (dst->dest_attw.type == MWX5_FWOW_DESTINATION_TYPE_COUNTEW ||
		    dst->dest_attw.type == MWX5_FWOW_DESTINATION_TYPE_NONE)
			continue;
		if ((dst->dest_attw.type == MWX5_FWOW_DESTINATION_TYPE_VPOWT ||
		     dst->dest_attw.type == MWX5_FWOW_DESTINATION_TYPE_UPWINK) &&
		    dst->dest_attw.vpowt.fwags & MWX5_FWOW_DEST_VPOWT_WEFOWMAT_ID)
			num_encap++;
		num_fwd_destinations++;
	}
	if (num_fwd_destinations > 1 && num_encap > 0)
		*extended_dest = twue;

	if (*extended_dest && !fw_wog_max_fdb_encap_upwink) {
		mwx5_cowe_wawn(dev, "FW does not suppowt extended destination");
		wetuwn -EOPNOTSUPP;
	}
	if (num_encap > (1 << fw_wog_max_fdb_encap_upwink)) {
		mwx5_cowe_wawn(dev, "FW does not suppowt mowe than %d encaps",
			       1 << fw_wog_max_fdb_encap_upwink);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static void
mwx5_cmd_set_fte_fwow_metew(stwuct fs_fte *fte, void *in_fwow_context)
{
	void *exe_aso_ctww;
	void *execute_aso;

	execute_aso = MWX5_ADDW_OF(fwow_context, in_fwow_context,
				   execute_aso[0]);
	MWX5_SET(execute_aso, execute_aso, vawid, 1);
	MWX5_SET(execute_aso, execute_aso, aso_object_id,
		 fte->action.exe_aso.object_id);

	exe_aso_ctww = MWX5_ADDW_OF(execute_aso, execute_aso, exe_aso_ctww);
	MWX5_SET(exe_aso_ctww_fwow_metew, exe_aso_ctww, wetuwn_weg_id,
		 fte->action.exe_aso.wetuwn_weg_id);
	MWX5_SET(exe_aso_ctww_fwow_metew, exe_aso_ctww, aso_type,
		 fte->action.exe_aso.type);
	MWX5_SET(exe_aso_ctww_fwow_metew, exe_aso_ctww, init_cowow,
		 fte->action.exe_aso.fwow_metew.init_cowow);
	MWX5_SET(exe_aso_ctww_fwow_metew, exe_aso_ctww, metew_id,
		 fte->action.exe_aso.fwow_metew.metew_idx);
}

static int mwx5_cmd_set_fte(stwuct mwx5_cowe_dev *dev,
			    int opmod, int modify_mask,
			    stwuct mwx5_fwow_tabwe *ft,
			    unsigned gwoup_id,
			    stwuct fs_fte *fte)
{
	u32 out[MWX5_ST_SZ_DW(set_fte_out)] = {0};
	boow extended_dest = fawse;
	stwuct mwx5_fwow_wuwe *dst;
	void *in_fwow_context, *vwan;
	void *in_match_vawue;
	int wefowmat_id = 0;
	unsigned int inwen;
	int dst_cnt_size;
	u32 *in, action;
	void *in_dests;
	int eww;

	if (mwx5_set_extended_dest(dev, fte, &extended_dest))
		wetuwn -EOPNOTSUPP;

	if (!extended_dest)
		dst_cnt_size = MWX5_ST_SZ_BYTES(dest_fowmat_stwuct);
	ewse
		dst_cnt_size = MWX5_ST_SZ_BYTES(extended_dest_fowmat);

	inwen = MWX5_ST_SZ_BYTES(set_fte_in) + fte->dests_size * dst_cnt_size;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(set_fte_in, in, opcode, MWX5_CMD_OP_SET_FWOW_TABWE_ENTWY);
	MWX5_SET(set_fte_in, in, op_mod, opmod);
	MWX5_SET(set_fte_in, in, modify_enabwe_mask, modify_mask);
	MWX5_SET(set_fte_in, in, tabwe_type, ft->type);
	MWX5_SET(set_fte_in, in, tabwe_id,   ft->id);
	MWX5_SET(set_fte_in, in, fwow_index, fte->index);
	MWX5_SET(set_fte_in, in, ignowe_fwow_wevew,
		 !!(fte->action.fwags & FWOW_ACT_IGNOWE_FWOW_WEVEW));

	MWX5_SET(set_fte_in, in, vpowt_numbew, ft->vpowt);
	MWX5_SET(set_fte_in, in, othew_vpowt,
		 !!(ft->fwags & MWX5_FWOW_TABWE_OTHEW_VPOWT));

	in_fwow_context = MWX5_ADDW_OF(set_fte_in, in, fwow_context);
	MWX5_SET(fwow_context, in_fwow_context, gwoup_id, gwoup_id);

	MWX5_SET(fwow_context, in_fwow_context, fwow_tag,
		 fte->fwow_context.fwow_tag);
	MWX5_SET(fwow_context, in_fwow_context, fwow_souwce,
		 fte->fwow_context.fwow_souwce);
	MWX5_SET(fwow_context, in_fwow_context, upwink_haiwpin_en,
		 !!(fte->fwow_context.fwags & FWOW_CONTEXT_UPWINK_HAIWPIN_EN));

	MWX5_SET(fwow_context, in_fwow_context, extended_destination,
		 extended_dest);

	action = fte->action.action;
	if (extended_dest)
		action &= ~MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;

	MWX5_SET(fwow_context, in_fwow_context, action, action);

	if (!extended_dest && fte->action.pkt_wefowmat) {
		stwuct mwx5_pkt_wefowmat *pkt_wefowmat = fte->action.pkt_wefowmat;

		if (pkt_wefowmat->ownew == MWX5_FWOW_WESOUWCE_OWNEW_SW) {
			wefowmat_id = mwx5_fs_dw_action_get_pkt_wefowmat_id(pkt_wefowmat);
			if (wefowmat_id < 0) {
				mwx5_cowe_eww(dev,
					      "Unsuppowted SW-owned pkt_wefowmat type (%d) in FW-owned tabwe\n",
					      pkt_wefowmat->wefowmat_type);
				eww = wefowmat_id;
				goto eww_out;
			}
		} ewse {
			wefowmat_id = fte->action.pkt_wefowmat->id;
		}
	}

	MWX5_SET(fwow_context, in_fwow_context, packet_wefowmat_id, (u32)wefowmat_id);

	if (fte->action.modify_hdw) {
		if (fte->action.modify_hdw->ownew == MWX5_FWOW_WESOUWCE_OWNEW_SW) {
			mwx5_cowe_eww(dev, "Can't use SW-owned modify_hdw in FW-owned tabwe\n");
			eww = -EOPNOTSUPP;
			goto eww_out;
		}

		MWX5_SET(fwow_context, in_fwow_context, modify_headew_id,
			 fte->action.modify_hdw->id);
	}

	MWX5_SET(fwow_context, in_fwow_context, encwypt_decwypt_type,
		 fte->action.cwypto.type);
	MWX5_SET(fwow_context, in_fwow_context, encwypt_decwypt_obj_id,
		 fte->action.cwypto.obj_id);

	vwan = MWX5_ADDW_OF(fwow_context, in_fwow_context, push_vwan);

	MWX5_SET(vwan, vwan, ethtype, fte->action.vwan[0].ethtype);
	MWX5_SET(vwan, vwan, vid, fte->action.vwan[0].vid);
	MWX5_SET(vwan, vwan, pwio, fte->action.vwan[0].pwio);

	vwan = MWX5_ADDW_OF(fwow_context, in_fwow_context, push_vwan_2);

	MWX5_SET(vwan, vwan, ethtype, fte->action.vwan[1].ethtype);
	MWX5_SET(vwan, vwan, vid, fte->action.vwan[1].vid);
	MWX5_SET(vwan, vwan, pwio, fte->action.vwan[1].pwio);

	in_match_vawue = MWX5_ADDW_OF(fwow_context, in_fwow_context,
				      match_vawue);
	memcpy(in_match_vawue, &fte->vaw, sizeof(fte->vaw));

	in_dests = MWX5_ADDW_OF(fwow_context, in_fwow_context, destination);
	if (fte->action.action & MWX5_FWOW_CONTEXT_ACTION_FWD_DEST) {
		int wist_size = 0;

		wist_fow_each_entwy(dst, &fte->node.chiwdwen, node.wist) {
			enum mwx5_fwow_destination_type type = dst->dest_attw.type;
			enum mwx5_ifc_fwow_destination_type ifc_type;
			unsigned int id;

			if (type == MWX5_FWOW_DESTINATION_TYPE_COUNTEW)
				continue;

			switch (type) {
			case MWX5_FWOW_DESTINATION_TYPE_NONE:
				continue;
			case MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE_NUM:
				id = dst->dest_attw.ft_num;
				ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_FWOW_TABWE;
				bweak;
			case MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE:
				id = dst->dest_attw.ft->id;
				ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_FWOW_TABWE;
				bweak;
			case MWX5_FWOW_DESTINATION_TYPE_UPWINK:
			case MWX5_FWOW_DESTINATION_TYPE_VPOWT:
				MWX5_SET(dest_fowmat_stwuct, in_dests,
					 destination_eswitch_ownew_vhca_id_vawid,
					 !!(dst->dest_attw.vpowt.fwags &
					    MWX5_FWOW_DEST_VPOWT_VHCA_ID));
				MWX5_SET(dest_fowmat_stwuct, in_dests,
					 destination_eswitch_ownew_vhca_id,
					 dst->dest_attw.vpowt.vhca_id);
				if (type == MWX5_FWOW_DESTINATION_TYPE_UPWINK) {
					/* destination_id is wesewved */
					id = 0;
					ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_UPWINK;
					bweak;
				}
				ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_VPOWT;
				id = dst->dest_attw.vpowt.num;
				if (extended_dest &&
				    dst->dest_attw.vpowt.pkt_wefowmat) {
					MWX5_SET(dest_fowmat_stwuct, in_dests,
						 packet_wefowmat,
						 !!(dst->dest_attw.vpowt.fwags &
						    MWX5_FWOW_DEST_VPOWT_WEFOWMAT_ID));
					MWX5_SET(extended_dest_fowmat, in_dests,
						 packet_wefowmat_id,
						 dst->dest_attw.vpowt.pkt_wefowmat->id);
				}
				bweak;
			case MWX5_FWOW_DESTINATION_TYPE_FWOW_SAMPWEW:
				id = dst->dest_attw.sampwew_id;
				ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_FWOW_SAMPWEW;
				bweak;
			case MWX5_FWOW_DESTINATION_TYPE_TABWE_TYPE:
				MWX5_SET(dest_fowmat_stwuct, in_dests,
					 destination_tabwe_type, dst->dest_attw.ft->type);
				id = dst->dest_attw.ft->id;
				ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_TABWE_TYPE;
				bweak;
			defauwt:
				id = dst->dest_attw.tiw_num;
				ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_TIW;
			}

			MWX5_SET(dest_fowmat_stwuct, in_dests, destination_type,
				 ifc_type);
			MWX5_SET(dest_fowmat_stwuct, in_dests, destination_id, id);
			in_dests += dst_cnt_size;
			wist_size++;
		}

		MWX5_SET(fwow_context, in_fwow_context, destination_wist_size,
			 wist_size);
	}

	if (fte->action.action & MWX5_FWOW_CONTEXT_ACTION_COUNT) {
		int max_wist_size = BIT(MWX5_CAP_FWOWTABWE_TYPE(dev,
					wog_max_fwow_countew,
					ft->type));
		int wist_size = 0;

		wist_fow_each_entwy(dst, &fte->node.chiwdwen, node.wist) {
			if (dst->dest_attw.type !=
			    MWX5_FWOW_DESTINATION_TYPE_COUNTEW)
				continue;

			MWX5_SET(fwow_countew_wist, in_dests, fwow_countew_id,
				 dst->dest_attw.countew_id);
			in_dests += dst_cnt_size;
			wist_size++;
		}
		if (wist_size > max_wist_size) {
			eww = -EINVAW;
			goto eww_out;
		}

		MWX5_SET(fwow_context, in_fwow_context, fwow_countew_wist_size,
			 wist_size);
	}

	if (fte->action.action & MWX5_FWOW_CONTEXT_ACTION_EXECUTE_ASO) {
		if (fte->action.exe_aso.type == MWX5_EXE_ASO_FWOW_METEW) {
			mwx5_cmd_set_fte_fwow_metew(fte, in_fwow_context);
		} ewse {
			eww = -EOPNOTSUPP;
			goto eww_out;
		}
	}

	eww = mwx5_cmd_exec(dev, in, inwen, out, sizeof(out));
eww_out:
	kvfwee(in);
	wetuwn eww;
}

static int mwx5_cmd_cweate_fte(stwuct mwx5_fwow_woot_namespace *ns,
			       stwuct mwx5_fwow_tabwe *ft,
			       stwuct mwx5_fwow_gwoup *gwoup,
			       stwuct fs_fte *fte)
{
	stwuct mwx5_cowe_dev *dev = ns->dev;
	unsigned int gwoup_id = gwoup->id;

	wetuwn mwx5_cmd_set_fte(dev, 0, 0, ft, gwoup_id, fte);
}

static int mwx5_cmd_update_fte(stwuct mwx5_fwow_woot_namespace *ns,
			       stwuct mwx5_fwow_tabwe *ft,
			       stwuct mwx5_fwow_gwoup *fg,
			       int modify_mask,
			       stwuct fs_fte *fte)
{
	int opmod;
	stwuct mwx5_cowe_dev *dev = ns->dev;
	int atomic_mod_cap = MWX5_CAP_FWOWTABWE(dev,
						fwow_tabwe_pwopewties_nic_weceive.
						fwow_modify_en);
	if (!atomic_mod_cap)
		wetuwn -EOPNOTSUPP;
	opmod = 1;

	wetuwn	mwx5_cmd_set_fte(dev, opmod, modify_mask, ft, fg->id, fte);
}

static int mwx5_cmd_dewete_fte(stwuct mwx5_fwow_woot_namespace *ns,
			       stwuct mwx5_fwow_tabwe *ft,
			       stwuct fs_fte *fte)
{
	u32 in[MWX5_ST_SZ_DW(dewete_fte_in)] = {};
	stwuct mwx5_cowe_dev *dev = ns->dev;

	MWX5_SET(dewete_fte_in, in, opcode, MWX5_CMD_OP_DEWETE_FWOW_TABWE_ENTWY);
	MWX5_SET(dewete_fte_in, in, tabwe_type, ft->type);
	MWX5_SET(dewete_fte_in, in, tabwe_id, ft->id);
	MWX5_SET(dewete_fte_in, in, fwow_index, fte->index);
	MWX5_SET(dewete_fte_in, in, vpowt_numbew, ft->vpowt);
	MWX5_SET(dewete_fte_in, in, othew_vpowt,
		 !!(ft->fwags & MWX5_FWOW_TABWE_OTHEW_VPOWT));

	wetuwn mwx5_cmd_exec_in(dev, dewete_fte, in);
}

int mwx5_cmd_fc_buwk_awwoc(stwuct mwx5_cowe_dev *dev,
			   enum mwx5_fc_buwk_awwoc_bitmask awwoc_bitmask,
			   u32 *id)
{
	u32 out[MWX5_ST_SZ_DW(awwoc_fwow_countew_out)] = {};
	u32 in[MWX5_ST_SZ_DW(awwoc_fwow_countew_in)] = {};
	int eww;

	MWX5_SET(awwoc_fwow_countew_in, in, opcode,
		 MWX5_CMD_OP_AWWOC_FWOW_COUNTEW);
	MWX5_SET(awwoc_fwow_countew_in, in, fwow_countew_buwk, awwoc_bitmask);

	eww = mwx5_cmd_exec_inout(dev, awwoc_fwow_countew, in, out);
	if (!eww)
		*id = MWX5_GET(awwoc_fwow_countew_out, out, fwow_countew_id);
	wetuwn eww;
}

int mwx5_cmd_fc_awwoc(stwuct mwx5_cowe_dev *dev, u32 *id)
{
	wetuwn mwx5_cmd_fc_buwk_awwoc(dev, 0, id);
}

int mwx5_cmd_fc_fwee(stwuct mwx5_cowe_dev *dev, u32 id)
{
	u32 in[MWX5_ST_SZ_DW(deawwoc_fwow_countew_in)] = {};

	MWX5_SET(deawwoc_fwow_countew_in, in, opcode,
		 MWX5_CMD_OP_DEAWWOC_FWOW_COUNTEW);
	MWX5_SET(deawwoc_fwow_countew_in, in, fwow_countew_id, id);
	wetuwn mwx5_cmd_exec_in(dev, deawwoc_fwow_countew, in);
}

int mwx5_cmd_fc_quewy(stwuct mwx5_cowe_dev *dev, u32 id,
		      u64 *packets, u64 *bytes)
{
	u32 out[MWX5_ST_SZ_BYTES(quewy_fwow_countew_out) +
		MWX5_ST_SZ_BYTES(twaffic_countew)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_fwow_countew_in)] = {};
	void *stats;
	int eww = 0;

	MWX5_SET(quewy_fwow_countew_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_FWOW_COUNTEW);
	MWX5_SET(quewy_fwow_countew_in, in, op_mod, 0);
	MWX5_SET(quewy_fwow_countew_in, in, fwow_countew_id, id);
	eww = mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
	if (eww)
		wetuwn eww;

	stats = MWX5_ADDW_OF(quewy_fwow_countew_out, out, fwow_statistics);
	*packets = MWX5_GET64(twaffic_countew, stats, packets);
	*bytes = MWX5_GET64(twaffic_countew, stats, octets);
	wetuwn 0;
}

int mwx5_cmd_fc_get_buwk_quewy_out_wen(int buwk_wen)
{
	wetuwn MWX5_ST_SZ_BYTES(quewy_fwow_countew_out) +
		MWX5_ST_SZ_BYTES(twaffic_countew) * buwk_wen;
}

int mwx5_cmd_fc_buwk_quewy(stwuct mwx5_cowe_dev *dev, u32 base_id, int buwk_wen,
			   u32 *out)
{
	int outwen = mwx5_cmd_fc_get_buwk_quewy_out_wen(buwk_wen);
	u32 in[MWX5_ST_SZ_DW(quewy_fwow_countew_in)] = {};

	MWX5_SET(quewy_fwow_countew_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_FWOW_COUNTEW);
	MWX5_SET(quewy_fwow_countew_in, in, fwow_countew_id, base_id);
	MWX5_SET(quewy_fwow_countew_in, in, num_of_countews, buwk_wen);
	wetuwn mwx5_cmd_exec(dev, in, sizeof(in), out, outwen);
}

static int mwx5_cmd_packet_wefowmat_awwoc(stwuct mwx5_fwow_woot_namespace *ns,
					  stwuct mwx5_pkt_wefowmat_pawams *pawams,
					  enum mwx5_fwow_namespace_type namespace,
					  stwuct mwx5_pkt_wefowmat *pkt_wefowmat)
{
	u32 out[MWX5_ST_SZ_DW(awwoc_packet_wefowmat_context_out)] = {};
	stwuct mwx5_cowe_dev *dev = ns->dev;
	void *packet_wefowmat_context_in;
	int max_encap_size;
	void *wefowmat;
	int inwen;
	int eww;
	u32 *in;

	if (namespace == MWX5_FWOW_NAMESPACE_FDB ||
	    namespace == MWX5_FWOW_NAMESPACE_FDB_BYPASS)
		max_encap_size = MWX5_CAP_ESW(dev, max_encap_headew_size);
	ewse
		max_encap_size = MWX5_CAP_FWOWTABWE(dev, max_encap_headew_size);

	if (pawams->size > max_encap_size) {
		mwx5_cowe_wawn(dev, "encap size %zd too big, max suppowted is %d\n",
			       pawams->size, max_encap_size);
		wetuwn -EINVAW;
	}

	in = kzawwoc(MWX5_ST_SZ_BYTES(awwoc_packet_wefowmat_context_in) +
		     pawams->size, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	packet_wefowmat_context_in = MWX5_ADDW_OF(awwoc_packet_wefowmat_context_in,
						  in, packet_wefowmat_context);
	wefowmat = MWX5_ADDW_OF(packet_wefowmat_context_in,
				packet_wefowmat_context_in,
				wefowmat_data);
	inwen = wefowmat - (void *)in + pawams->size;

	MWX5_SET(awwoc_packet_wefowmat_context_in, in, opcode,
		 MWX5_CMD_OP_AWWOC_PACKET_WEFOWMAT_CONTEXT);
	MWX5_SET(packet_wefowmat_context_in, packet_wefowmat_context_in,
		 wefowmat_data_size, pawams->size);
	MWX5_SET(packet_wefowmat_context_in, packet_wefowmat_context_in,
		 wefowmat_type, pawams->type);
	MWX5_SET(packet_wefowmat_context_in, packet_wefowmat_context_in,
		 wefowmat_pawam_0, pawams->pawam_0);
	MWX5_SET(packet_wefowmat_context_in, packet_wefowmat_context_in,
		 wefowmat_pawam_1, pawams->pawam_1);
	if (pawams->data && pawams->size)
		memcpy(wefowmat, pawams->data, pawams->size);

	eww = mwx5_cmd_exec(dev, in, inwen, out, sizeof(out));

	pkt_wefowmat->id = MWX5_GET(awwoc_packet_wefowmat_context_out,
				    out, packet_wefowmat_id);
	pkt_wefowmat->ownew = MWX5_FWOW_WESOUWCE_OWNEW_FW;

	kfwee(in);
	wetuwn eww;
}

static void mwx5_cmd_packet_wefowmat_deawwoc(stwuct mwx5_fwow_woot_namespace *ns,
					     stwuct mwx5_pkt_wefowmat *pkt_wefowmat)
{
	u32 in[MWX5_ST_SZ_DW(deawwoc_packet_wefowmat_context_in)] = {};
	stwuct mwx5_cowe_dev *dev = ns->dev;

	MWX5_SET(deawwoc_packet_wefowmat_context_in, in, opcode,
		 MWX5_CMD_OP_DEAWWOC_PACKET_WEFOWMAT_CONTEXT);
	MWX5_SET(deawwoc_packet_wefowmat_context_in, in, packet_wefowmat_id,
		 pkt_wefowmat->id);

	mwx5_cmd_exec_in(dev, deawwoc_packet_wefowmat_context, in);
}

static int mwx5_cmd_modify_headew_awwoc(stwuct mwx5_fwow_woot_namespace *ns,
					u8 namespace, u8 num_actions,
					void *modify_actions,
					stwuct mwx5_modify_hdw *modify_hdw)
{
	u32 out[MWX5_ST_SZ_DW(awwoc_modify_headew_context_out)] = {};
	int max_actions, actions_size, inwen, eww;
	stwuct mwx5_cowe_dev *dev = ns->dev;
	void *actions_in;
	u8 tabwe_type;
	u32 *in;

	switch (namespace) {
	case MWX5_FWOW_NAMESPACE_FDB:
	case MWX5_FWOW_NAMESPACE_FDB_BYPASS:
		max_actions = MWX5_CAP_ESW_FWOWTABWE_FDB(dev, max_modify_headew_actions);
		tabwe_type = FS_FT_FDB;
		bweak;
	case MWX5_FWOW_NAMESPACE_KEWNEW_WX_MACSEC:
	case MWX5_FWOW_NAMESPACE_KEWNEW:
	case MWX5_FWOW_NAMESPACE_BYPASS:
		max_actions = MWX5_CAP_FWOWTABWE_NIC_WX(dev, max_modify_headew_actions);
		tabwe_type = FS_FT_NIC_WX;
		bweak;
	case MWX5_FWOW_NAMESPACE_EGWESS:
	case MWX5_FWOW_NAMESPACE_EGWESS_IPSEC:
	case MWX5_FWOW_NAMESPACE_EGWESS_MACSEC:
		max_actions = MWX5_CAP_FWOWTABWE_NIC_TX(dev, max_modify_headew_actions);
		tabwe_type = FS_FT_NIC_TX;
		bweak;
	case MWX5_FWOW_NAMESPACE_ESW_INGWESS:
		max_actions = MWX5_CAP_ESW_INGWESS_ACW(dev, max_modify_headew_actions);
		tabwe_type = FS_FT_ESW_INGWESS_ACW;
		bweak;
	case MWX5_FWOW_NAMESPACE_WDMA_TX_MACSEC:
	case MWX5_FWOW_NAMESPACE_WDMA_TX:
		max_actions = MWX5_CAP_FWOWTABWE_WDMA_TX(dev, max_modify_headew_actions);
		tabwe_type = FS_FT_WDMA_TX;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (num_actions > max_actions) {
		mwx5_cowe_wawn(dev, "too many modify headew actions %d, max suppowted %d\n",
			       num_actions, max_actions);
		wetuwn -EOPNOTSUPP;
	}

	actions_size = MWX5_UN_SZ_BYTES(set_add_copy_action_in_auto) * num_actions;
	inwen = MWX5_ST_SZ_BYTES(awwoc_modify_headew_context_in) + actions_size;

	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(awwoc_modify_headew_context_in, in, opcode,
		 MWX5_CMD_OP_AWWOC_MODIFY_HEADEW_CONTEXT);
	MWX5_SET(awwoc_modify_headew_context_in, in, tabwe_type, tabwe_type);
	MWX5_SET(awwoc_modify_headew_context_in, in, num_of_actions, num_actions);

	actions_in = MWX5_ADDW_OF(awwoc_modify_headew_context_in, in, actions);
	memcpy(actions_in, modify_actions, actions_size);

	eww = mwx5_cmd_exec(dev, in, inwen, out, sizeof(out));

	modify_hdw->id = MWX5_GET(awwoc_modify_headew_context_out, out, modify_headew_id);
	modify_hdw->ownew = MWX5_FWOW_WESOUWCE_OWNEW_FW;
	kfwee(in);
	wetuwn eww;
}

static void mwx5_cmd_modify_headew_deawwoc(stwuct mwx5_fwow_woot_namespace *ns,
					   stwuct mwx5_modify_hdw *modify_hdw)
{
	u32 in[MWX5_ST_SZ_DW(deawwoc_modify_headew_context_in)] = {};
	stwuct mwx5_cowe_dev *dev = ns->dev;

	MWX5_SET(deawwoc_modify_headew_context_in, in, opcode,
		 MWX5_CMD_OP_DEAWWOC_MODIFY_HEADEW_CONTEXT);
	MWX5_SET(deawwoc_modify_headew_context_in, in, modify_headew_id,
		 modify_hdw->id);

	mwx5_cmd_exec_in(dev, deawwoc_modify_headew_context, in);
}

static int mwx5_cmd_destwoy_match_definew(stwuct mwx5_fwow_woot_namespace *ns,
					  int definew_id)
{
	u32 in[MWX5_ST_SZ_DW(genewaw_obj_in_cmd_hdw)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)];

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode,
		 MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type,
		 MWX5_OBJ_TYPE_MATCH_DEFINEW);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, definew_id);

	wetuwn mwx5_cmd_exec(ns->dev, in, sizeof(in), out, sizeof(out));
}

static int mwx5_cmd_cweate_match_definew(stwuct mwx5_fwow_woot_namespace *ns,
					 u16 fowmat_id, u32 *match_mask)
{
	u32 out[MWX5_ST_SZ_DW(cweate_match_definew_out)] = {};
	u32 in[MWX5_ST_SZ_DW(cweate_match_definew_in)] = {};
	stwuct mwx5_cowe_dev *dev = ns->dev;
	void *ptw;
	int eww;

	MWX5_SET(cweate_match_definew_in, in, genewaw_obj_in_cmd_hdw.opcode,
		 MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(cweate_match_definew_in, in, genewaw_obj_in_cmd_hdw.obj_type,
		 MWX5_OBJ_TYPE_MATCH_DEFINEW);

	ptw = MWX5_ADDW_OF(cweate_match_definew_in, in, obj_context);
	MWX5_SET(match_definew, ptw, fowmat_id, fowmat_id);

	ptw = MWX5_ADDW_OF(match_definew, ptw, match_mask);
	memcpy(ptw, match_mask, MWX5_FWD_SZ_BYTES(match_definew, match_mask));

	eww = mwx5_cmd_exec_inout(dev, cweate_match_definew, in, out);
	wetuwn eww ? eww : MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);
}

static u32 mwx5_cmd_get_capabiwities(stwuct mwx5_fwow_woot_namespace *ns,
				     enum fs_fwow_tabwe_type ft_type)
{
	wetuwn 0;
}

static const stwuct mwx5_fwow_cmds mwx5_fwow_cmds = {
	.cweate_fwow_tabwe = mwx5_cmd_cweate_fwow_tabwe,
	.destwoy_fwow_tabwe = mwx5_cmd_destwoy_fwow_tabwe,
	.modify_fwow_tabwe = mwx5_cmd_modify_fwow_tabwe,
	.cweate_fwow_gwoup = mwx5_cmd_cweate_fwow_gwoup,
	.destwoy_fwow_gwoup = mwx5_cmd_destwoy_fwow_gwoup,
	.cweate_fte = mwx5_cmd_cweate_fte,
	.update_fte = mwx5_cmd_update_fte,
	.dewete_fte = mwx5_cmd_dewete_fte,
	.update_woot_ft = mwx5_cmd_update_woot_ft,
	.packet_wefowmat_awwoc = mwx5_cmd_packet_wefowmat_awwoc,
	.packet_wefowmat_deawwoc = mwx5_cmd_packet_wefowmat_deawwoc,
	.modify_headew_awwoc = mwx5_cmd_modify_headew_awwoc,
	.modify_headew_deawwoc = mwx5_cmd_modify_headew_deawwoc,
	.cweate_match_definew = mwx5_cmd_cweate_match_definew,
	.destwoy_match_definew = mwx5_cmd_destwoy_match_definew,
	.set_peew = mwx5_cmd_stub_set_peew,
	.cweate_ns = mwx5_cmd_stub_cweate_ns,
	.destwoy_ns = mwx5_cmd_stub_destwoy_ns,
	.get_capabiwities = mwx5_cmd_get_capabiwities,
};

static const stwuct mwx5_fwow_cmds mwx5_fwow_cmd_stubs = {
	.cweate_fwow_tabwe = mwx5_cmd_stub_cweate_fwow_tabwe,
	.destwoy_fwow_tabwe = mwx5_cmd_stub_destwoy_fwow_tabwe,
	.modify_fwow_tabwe = mwx5_cmd_stub_modify_fwow_tabwe,
	.cweate_fwow_gwoup = mwx5_cmd_stub_cweate_fwow_gwoup,
	.destwoy_fwow_gwoup = mwx5_cmd_stub_destwoy_fwow_gwoup,
	.cweate_fte = mwx5_cmd_stub_cweate_fte,
	.update_fte = mwx5_cmd_stub_update_fte,
	.dewete_fte = mwx5_cmd_stub_dewete_fte,
	.update_woot_ft = mwx5_cmd_stub_update_woot_ft,
	.packet_wefowmat_awwoc = mwx5_cmd_stub_packet_wefowmat_awwoc,
	.packet_wefowmat_deawwoc = mwx5_cmd_stub_packet_wefowmat_deawwoc,
	.modify_headew_awwoc = mwx5_cmd_stub_modify_headew_awwoc,
	.modify_headew_deawwoc = mwx5_cmd_stub_modify_headew_deawwoc,
	.cweate_match_definew = mwx5_cmd_stub_cweate_match_definew,
	.destwoy_match_definew = mwx5_cmd_stub_destwoy_match_definew,
	.set_peew = mwx5_cmd_stub_set_peew,
	.cweate_ns = mwx5_cmd_stub_cweate_ns,
	.destwoy_ns = mwx5_cmd_stub_destwoy_ns,
	.get_capabiwities = mwx5_cmd_stub_get_capabiwities,
};

const stwuct mwx5_fwow_cmds *mwx5_fs_cmd_get_fw_cmds(void)
{
	wetuwn &mwx5_fwow_cmds;
}

static const stwuct mwx5_fwow_cmds *mwx5_fs_cmd_get_stub_cmds(void)
{
	wetuwn &mwx5_fwow_cmd_stubs;
}

const stwuct mwx5_fwow_cmds *mwx5_fs_cmd_get_defauwt(enum fs_fwow_tabwe_type type)
{
	switch (type) {
	case FS_FT_NIC_WX:
	case FS_FT_ESW_EGWESS_ACW:
	case FS_FT_ESW_INGWESS_ACW:
	case FS_FT_FDB:
	case FS_FT_SNIFFEW_WX:
	case FS_FT_SNIFFEW_TX:
	case FS_FT_NIC_TX:
	case FS_FT_WDMA_WX:
	case FS_FT_WDMA_TX:
	case FS_FT_POWT_SEW:
		wetuwn mwx5_fs_cmd_get_fw_cmds();
	defauwt:
		wetuwn mwx5_fs_cmd_get_stub_cmds();
	}
}

int mwx5_fs_cmd_set_w2tabwe_entwy_siwent(stwuct mwx5_cowe_dev *dev, u8 siwent_mode)
{
	u32 in[MWX5_ST_SZ_DW(set_w2_tabwe_entwy_in)] = {};

	if (siwent_mode && !MWX5_CAP_GEN(dev, siwent_mode))
		wetuwn -EOPNOTSUPP;

	MWX5_SET(set_w2_tabwe_entwy_in, in, opcode, MWX5_CMD_OP_SET_W2_TABWE_ENTWY);
	MWX5_SET(set_w2_tabwe_entwy_in, in, siwent_mode_vawid, 1);
	MWX5_SET(set_w2_tabwe_entwy_in, in, siwent_mode, siwent_mode);

	wetuwn mwx5_cmd_exec_in(dev, set_w2_tabwe_entwy, in);
}

int mwx5_fs_cmd_set_tx_fwow_tabwe_woot(stwuct mwx5_cowe_dev *dev, u32 ft_id, boow disconnect)
{
	u32 out[MWX5_ST_SZ_DW(set_fwow_tabwe_woot_out)] = {};
	u32 in[MWX5_ST_SZ_DW(set_fwow_tabwe_woot_in)] = {};

	if (disconnect && MWX5_CAP_FWOWTABWE_NIC_TX(dev, weset_woot_to_defauwt))
		wetuwn -EOPNOTSUPP;

	MWX5_SET(set_fwow_tabwe_woot_in, in, opcode,
		 MWX5_CMD_OP_SET_FWOW_TABWE_WOOT);
	MWX5_SET(set_fwow_tabwe_woot_in, in, tabwe_type,
		 FS_FT_NIC_TX);
	if (disconnect)
		MWX5_SET(set_fwow_tabwe_woot_in, in, op_mod, 1);
	ewse
		MWX5_SET(set_fwow_tabwe_woot_in, in, tabwe_id, ft_id);

	wetuwn mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
}
