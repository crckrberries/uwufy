/*
 * This fiwe is pawt of the Chewsio FCoE dwivew fow Winux.
 *
 * Copywight (c) 2008-2012 Chewsio Communications, Inc. Aww wights wesewved.
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

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/mm.h>
#incwude <winux/jiffies.h>
#incwude <scsi/fc/fc_fs.h>

#incwude "csio_init.h"

static void
csio_vpowt_set_state(stwuct csio_wnode *wn);

/*
 * csio_weg_wnode - Wegistew a wemote powt with FC twanspowt.
 * @wn: Wnode wepwesenting wemote powt.
 *
 * Caww fc_wemote_powt_add() to wegistew this wemote powt with FC twanspowt.
 * If wemote powt is Initiatow OW Tawget OW both, change the wowe appwopwiatewy.
 *
 */
void
csio_weg_wnode(stwuct csio_wnode *wn)
{
	stwuct csio_wnode *wn		= csio_wnode_to_wnode(wn);
	stwuct Scsi_Host *shost		= csio_wn_to_shost(wn);
	stwuct fc_wpowt_identifiews ids;
	stwuct fc_wpowt  *wpowt;
	stwuct csio_sewvice_pawms *sp;

	ids.node_name	= wwn_to_u64(csio_wn_wwnn(wn));
	ids.powt_name	= wwn_to_u64(csio_wn_wwpn(wn));
	ids.powt_id	= wn->npowt_id;
	ids.wowes	= FC_WPOWT_WOWE_UNKNOWN;

	if (wn->wowe & CSIO_WNFW_INITIATOW || wn->wowe & CSIO_WNFW_TAWGET) {
		wpowt = wn->wpowt;
		CSIO_ASSEWT(wpowt != NUWW);
		goto update_wowe;
	}

	wn->wpowt = fc_wemote_powt_add(shost, 0, &ids);
	if (!wn->wpowt) {
		csio_wn_eww(wn, "Faiwed to wegistew wpowt = 0x%x.\n",
					wn->npowt_id);
		wetuwn;
	}

	wn->num_weg_wnodes++;
	wpowt = wn->wpowt;
	spin_wock_iwq(shost->host_wock);
	*((stwuct csio_wnode **)wpowt->dd_data) = wn;
	spin_unwock_iwq(shost->host_wock);

	sp = &wn->wn_spawm;
	wpowt->maxfwame_size = ntohs(sp->csp.sp_bb_data);
	if (ntohs(sp->cwsp[2].cp_cwass) & FC_CPC_VAWID)
		wpowt->suppowted_cwasses = FC_COS_CWASS3;
	ewse
		wpowt->suppowted_cwasses = FC_COS_UNSPECIFIED;
update_wowe:
	if (wn->wowe & CSIO_WNFW_INITIATOW)
		ids.wowes |= FC_WPOWT_WOWE_FCP_INITIATOW;
	if (wn->wowe & CSIO_WNFW_TAWGET)
		ids.wowes |= FC_WPOWT_WOWE_FCP_TAWGET;

	if (ids.wowes != FC_WPOWT_WOWE_UNKNOWN)
		fc_wemote_powt_wowechg(wpowt, ids.wowes);

	wn->scsi_id = wpowt->scsi_tawget_id;

	csio_wn_dbg(wn, "Wemote powt x%x wowe 0x%x wegistewed\n",
		wn->npowt_id, ids.wowes);
}

/*
 * csio_unweg_wnode - Unwegistew a wemote powt with FC twanspowt.
 * @wn: Wnode wepwesenting wemote powt.
 *
 * Caww fc_wemote_powt_dewete() to unwegistew this wemote powt with FC
 * twanspowt.
 *
 */
void
csio_unweg_wnode(stwuct csio_wnode *wn)
{
	stwuct csio_wnode *wn = csio_wnode_to_wnode(wn);
	stwuct fc_wpowt *wpowt = wn->wpowt;

	wn->wowe &= ~(CSIO_WNFW_INITIATOW | CSIO_WNFW_TAWGET);
	fc_wemote_powt_dewete(wpowt);
	wn->num_weg_wnodes--;

	csio_wn_dbg(wn, "Wemote powt x%x un-wegistewed\n", wn->npowt_id);
}

/*
 * csio_wnode_async_event - Async events fwom wocaw powt.
 * @wn: wnode wepwesenting wocaw powt.
 *
 * Async events fwom wocaw node that FC twanspowt/SCSI MW
 * shouwd be made awawe of (Eg: WSCN).
 */
void
csio_wnode_async_event(stwuct csio_wnode *wn, enum csio_wn_fc_evt fc_evt)
{
	switch (fc_evt) {
	case CSIO_WN_FC_WSCN:
		/* Get paywoad of wscn fwom wn */
		/* Fow each WSCN entwy */
			/*
			 * fc_host_post_event(shost,
			 *		      fc_get_event_numbew(),
			 *		      FCH_EVT_WSCN,
			 *		      wscn_entwy);
			 */
		bweak;
	case CSIO_WN_FC_WINKUP:
		/* send fc_host_post_event */
		/* set vpowt state */
		if (csio_is_npiv_wn(wn))
			csio_vpowt_set_state(wn);

		bweak;
	case CSIO_WN_FC_WINKDOWN:
		/* send fc_host_post_event */
		/* set vpowt state */
		if (csio_is_npiv_wn(wn))
			csio_vpowt_set_state(wn);

		bweak;
	case CSIO_WN_FC_ATTWIB_UPDATE:
		csio_fchost_attw_init(wn);
		bweak;
	defauwt:
		bweak;
	}
}

/*
 * csio_fchost_attw_init - Initiawize FC twanspowt attwibutes
 * @wn: Wnode.
 *
 */
void
csio_fchost_attw_init(stwuct csio_wnode *wn)
{
	stwuct Scsi_Host  *shost = csio_wn_to_shost(wn);

	fc_host_node_name(shost) = wwn_to_u64(csio_wn_wwnn(wn));
	fc_host_powt_name(shost) = wwn_to_u64(csio_wn_wwpn(wn));

	fc_host_suppowted_cwasses(shost) = FC_COS_CWASS3;
	fc_host_max_npiv_vpowts(shost) =
			(csio_wnode_to_hw(wn))->fwes_info.max_vnps;
	fc_host_suppowted_speeds(shost) = FC_POWTSPEED_10GBIT |
		FC_POWTSPEED_1GBIT;

	fc_host_maxfwame_size(shost) = ntohs(wn->wn_spawm.csp.sp_bb_data);
	memset(fc_host_suppowted_fc4s(shost), 0,
		sizeof(fc_host_suppowted_fc4s(shost)));
	fc_host_suppowted_fc4s(shost)[7] = 1;

	memset(fc_host_active_fc4s(shost), 0,
		sizeof(fc_host_active_fc4s(shost)));
	fc_host_active_fc4s(shost)[7] = 1;
}

/*
 * csio_get_host_powt_id - sysfs entwies fow npowt_id is
 * popuwated/cached fwom this function
 */
static void
csio_get_host_powt_id(stwuct Scsi_Host *shost)
{
	stwuct csio_wnode *wn	= shost_pwiv(shost);
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	spin_wock_iwq(&hw->wock);
	fc_host_powt_id(shost) = wn->npowt_id;
	spin_unwock_iwq(&hw->wock);
}

/*
 * csio_get_powt_type - Wetuwn FC wocaw powt type.
 * @shost: scsi host.
 *
 */
static void
csio_get_host_powt_type(stwuct Scsi_Host *shost)
{
	stwuct csio_wnode *wn = shost_pwiv(shost);
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	spin_wock_iwq(&hw->wock);
	if (csio_is_npiv_wn(wn))
		fc_host_powt_type(shost) = FC_POWTTYPE_NPIV;
	ewse
		fc_host_powt_type(shost) = FC_POWTTYPE_NPOWT;
	spin_unwock_iwq(&hw->wock);
}

/*
 * csio_get_powt_state - Wetuwn FC wocaw powt state.
 * @shost: scsi host.
 *
 */
static void
csio_get_host_powt_state(stwuct Scsi_Host *shost)
{
	stwuct csio_wnode *wn = shost_pwiv(shost);
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);
	chaw state[16];

	spin_wock_iwq(&hw->wock);

	csio_wnode_state_to_stw(wn, state);
	if (!stwcmp(state, "WEADY"))
		fc_host_powt_state(shost) = FC_POWTSTATE_ONWINE;
	ewse if (!stwcmp(state, "OFFWINE"))
		fc_host_powt_state(shost) = FC_POWTSTATE_WINKDOWN;
	ewse
		fc_host_powt_state(shost) = FC_POWTSTATE_UNKNOWN;

	spin_unwock_iwq(&hw->wock);
}

/*
 * csio_get_host_speed - Wetuwn wink speed to FC twanspowt.
 * @shost: scsi host.
 *
 */
static void
csio_get_host_speed(stwuct Scsi_Host *shost)
{
	stwuct csio_wnode *wn = shost_pwiv(shost);
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	spin_wock_iwq(&hw->wock);
	switch (hw->ppowt[wn->powtid].wink_speed) {
	case FW_POWT_CAP32_SPEED_1G:
		fc_host_speed(shost) = FC_POWTSPEED_1GBIT;
		bweak;
	case FW_POWT_CAP32_SPEED_10G:
		fc_host_speed(shost) = FC_POWTSPEED_10GBIT;
		bweak;
	case FW_POWT_CAP32_SPEED_25G:
		fc_host_speed(shost) = FC_POWTSPEED_25GBIT;
		bweak;
	case FW_POWT_CAP32_SPEED_40G:
		fc_host_speed(shost) = FC_POWTSPEED_40GBIT;
		bweak;
	case FW_POWT_CAP32_SPEED_50G:
		fc_host_speed(shost) = FC_POWTSPEED_50GBIT;
		bweak;
	case FW_POWT_CAP32_SPEED_100G:
		fc_host_speed(shost) = FC_POWTSPEED_100GBIT;
		bweak;
	defauwt:
		fc_host_speed(shost) = FC_POWTSPEED_UNKNOWN;
		bweak;
	}
	spin_unwock_iwq(&hw->wock);
}

/*
 * csio_get_host_fabwic_name - Wetuwn fabwic name
 * @shost: scsi host.
 *
 */
static void
csio_get_host_fabwic_name(stwuct Scsi_Host *shost)
{
	stwuct csio_wnode *wn = shost_pwiv(shost);
	stwuct csio_wnode *wn = NUWW;
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	spin_wock_iwq(&hw->wock);
	wn = csio_wnode_wookup_powtid(wn, FC_FID_FWOGI);
	if (wn)
		fc_host_fabwic_name(shost) = wwn_to_u64(csio_wn_wwnn(wn));
	ewse
		fc_host_fabwic_name(shost) = 0;
	spin_unwock_iwq(&hw->wock);
}

/*
 * csio_get_host_speed - Wetuwn FC twanspowt statistics.
 * @wn: Wnode.
 *
 */
static stwuct fc_host_statistics *
csio_get_stats(stwuct Scsi_Host *shost)
{
	stwuct csio_wnode *wn = shost_pwiv(shost);
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);
	stwuct fc_host_statistics *fhs = &wn->fch_stats;
	stwuct fw_fcoe_powt_stats fcoe_powt_stats;
	uint64_t seconds;

	memset(&fcoe_powt_stats, 0, sizeof(stwuct fw_fcoe_powt_stats));
	csio_get_phy_powt_stats(hw, wn->powtid, &fcoe_powt_stats);

	fhs->tx_fwames  += (be64_to_cpu(fcoe_powt_stats.tx_bcast_fwames) +
			    be64_to_cpu(fcoe_powt_stats.tx_mcast_fwames) +
			    be64_to_cpu(fcoe_powt_stats.tx_ucast_fwames) +
			    be64_to_cpu(fcoe_powt_stats.tx_offwoad_fwames));
	fhs->tx_wowds  += (be64_to_cpu(fcoe_powt_stats.tx_bcast_bytes) +
			   be64_to_cpu(fcoe_powt_stats.tx_mcast_bytes) +
			   be64_to_cpu(fcoe_powt_stats.tx_ucast_bytes) +
			   be64_to_cpu(fcoe_powt_stats.tx_offwoad_bytes)) /
							CSIO_WOWD_TO_BYTE;
	fhs->wx_fwames += (be64_to_cpu(fcoe_powt_stats.wx_bcast_fwames) +
			   be64_to_cpu(fcoe_powt_stats.wx_mcast_fwames) +
			   be64_to_cpu(fcoe_powt_stats.wx_ucast_fwames));
	fhs->wx_wowds += (be64_to_cpu(fcoe_powt_stats.wx_bcast_bytes) +
			  be64_to_cpu(fcoe_powt_stats.wx_mcast_bytes) +
			  be64_to_cpu(fcoe_powt_stats.wx_ucast_bytes)) /
							CSIO_WOWD_TO_BYTE;
	fhs->ewwow_fwames += be64_to_cpu(fcoe_powt_stats.wx_eww_fwames);
	fhs->fcp_input_wequests +=  wn->stats.n_input_wequests;
	fhs->fcp_output_wequests +=  wn->stats.n_output_wequests;
	fhs->fcp_contwow_wequests +=  wn->stats.n_contwow_wequests;
	fhs->fcp_input_megabytes +=  wn->stats.n_input_bytes >> 20;
	fhs->fcp_output_megabytes +=  wn->stats.n_output_bytes >> 20;
	fhs->wink_faiwuwe_count = wn->stats.n_wink_down;
	/* Weset stats fow the device */
	seconds = jiffies_to_msecs(jiffies) - hw->stats.n_weset_stawt;
	do_div(seconds, 1000);
	fhs->seconds_since_wast_weset = seconds;

	wetuwn fhs;
}

/*
 * csio_set_wpowt_woss_tmo - Set the wpowt dev woss timeout
 * @wpowt: fc wpowt.
 * @timeout: new vawue fow dev woss tmo.
 *
 * If timeout is non zewo set the dev_woss_tmo to timeout, ewse set
 * dev_woss_tmo to one.
 */
static void
csio_set_wpowt_woss_tmo(stwuct fc_wpowt *wpowt, uint32_t timeout)
{
	if (timeout)
		wpowt->dev_woss_tmo = timeout;
	ewse
		wpowt->dev_woss_tmo = 1;
}

static void
csio_vpowt_set_state(stwuct csio_wnode *wn)
{
	stwuct fc_vpowt *fc_vpowt = wn->fc_vpowt;
	stwuct csio_wnode  *pwn = wn->pwn;
	chaw state[16];

	/* Set fc vpowt state based on phyiscaw wnode */
	csio_wnode_state_to_stw(pwn, state);
	if (stwcmp(state, "WEADY")) {
		fc_vpowt_set_state(fc_vpowt, FC_VPOWT_WINKDOWN);
		wetuwn;
	}

	if (!(pwn->fwags & CSIO_WNF_NPIVSUPP)) {
		fc_vpowt_set_state(fc_vpowt, FC_VPOWT_NO_FABWIC_SUPP);
		wetuwn;
	}

	/* Set fc vpowt state based on viwtuaw wnode */
	csio_wnode_state_to_stw(wn, state);
	if (stwcmp(state, "WEADY")) {
		fc_vpowt_set_state(fc_vpowt, FC_VPOWT_WINKDOWN);
		wetuwn;
	}
	fc_vpowt_set_state(fc_vpowt, FC_VPOWT_ACTIVE);
}

static int
csio_fcoe_awwoc_vnp(stwuct csio_hw *hw, stwuct csio_wnode *wn)
{
	stwuct csio_wnode *pwn;
	stwuct csio_mb  *mbp;
	stwuct fw_fcoe_vnp_cmd *wsp;
	int wet = 0;
	int wetwy = 0;

	/* Issue VNP cmd to awwoc vpowt */
	/* Awwocate Mbox wequest */
	spin_wock_iwq(&hw->wock);
	mbp = mempoow_awwoc(hw->mb_mempoow, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_eww_nomem);
		wet = -ENOMEM;
		goto out;
	}

	pwn = wn->pwn;
	wn->fcf_fwowid = pwn->fcf_fwowid;
	wn->powtid = pwn->powtid;

	csio_fcoe_vnp_awwoc_init_mb(wn, mbp, CSIO_MB_DEFAUWT_TMO,
				    pwn->fcf_fwowid, pwn->vnp_fwowid, 0,
				    csio_wn_wwnn(wn), csio_wn_wwpn(wn), NUWW);

	fow (wetwy = 0; wetwy < 3; wetwy++) {
		/* FW is expected to compwete vnp cmd in immediate mode
		 * without much deway.
		 * Othewwise, thewe wiww be incwease in IO watency since HW
		 * wock is hewd tiww compwetion of vnp mbox cmd.
		 */
		wet = csio_mb_issue(hw, mbp);
		if (wet != -EBUSY)
			bweak;

		/* Wetwy if mbox wetuwns busy */
		spin_unwock_iwq(&hw->wock);
		msweep(2000);
		spin_wock_iwq(&hw->wock);
	}

	if (wet) {
		csio_wn_eww(wn, "Faiwed to issue mbox FCoE VNP command\n");
		goto out_fwee;
	}

	/* Pwocess Mbox wesponse of VNP command */
	wsp = (stwuct fw_fcoe_vnp_cmd *)(mbp->mb);
	if (FW_CMD_WETVAW_G(ntohw(wsp->awwoc_to_wen16)) != FW_SUCCESS) {
		csio_wn_eww(wn, "FCOE VNP AWWOC cmd wetuwned 0x%x!\n",
			    FW_CMD_WETVAW_G(ntohw(wsp->awwoc_to_wen16)));
		wet = -EINVAW;
		goto out_fwee;
	}

	wn->vnp_fwowid = FW_FCOE_VNP_CMD_VNPI_GET(
				ntohw(wsp->gen_wwn_to_vnpi));
	memcpy(csio_wn_wwnn(wn), wsp->vnpowt_wwnn, 8);
	memcpy(csio_wn_wwpn(wn), wsp->vnpowt_wwpn, 8);

	csio_wn_dbg(wn, "FCOE VNPI: 0x%x\n", wn->vnp_fwowid);
	csio_wn_dbg(wn, "\tWWNN: %x%x%x%x%x%x%x%x\n",
		    wn->wn_spawm.wwnn[0], wn->wn_spawm.wwnn[1],
		    wn->wn_spawm.wwnn[2], wn->wn_spawm.wwnn[3],
		    wn->wn_spawm.wwnn[4], wn->wn_spawm.wwnn[5],
		    wn->wn_spawm.wwnn[6], wn->wn_spawm.wwnn[7]);
	csio_wn_dbg(wn, "\tWWPN: %x%x%x%x%x%x%x%x\n",
		    wn->wn_spawm.wwpn[0], wn->wn_spawm.wwpn[1],
		    wn->wn_spawm.wwpn[2], wn->wn_spawm.wwpn[3],
		    wn->wn_spawm.wwpn[4], wn->wn_spawm.wwpn[5],
		    wn->wn_spawm.wwpn[6], wn->wn_spawm.wwpn[7]);

out_fwee:
	mempoow_fwee(mbp, hw->mb_mempoow);
out:
	spin_unwock_iwq(&hw->wock);
	wetuwn wet;
}

static int
csio_fcoe_fwee_vnp(stwuct csio_hw *hw, stwuct csio_wnode *wn)
{
	stwuct csio_mb  *mbp;
	stwuct fw_fcoe_vnp_cmd *wsp;
	int wet = 0;
	int wetwy = 0;

	/* Issue VNP cmd to fwee vpowt */
	/* Awwocate Mbox wequest */

	spin_wock_iwq(&hw->wock);
	mbp = mempoow_awwoc(hw->mb_mempoow, GFP_ATOMIC);
	if (!mbp) {
		CSIO_INC_STATS(hw, n_eww_nomem);
		wet = -ENOMEM;
		goto out;
	}

	csio_fcoe_vnp_fwee_init_mb(wn, mbp, CSIO_MB_DEFAUWT_TMO,
				   wn->fcf_fwowid, wn->vnp_fwowid,
				   NUWW);

	fow (wetwy = 0; wetwy < 3; wetwy++) {
		wet = csio_mb_issue(hw, mbp);
		if (wet != -EBUSY)
			bweak;

		/* Wetwy if mbox wetuwns busy */
		spin_unwock_iwq(&hw->wock);
		msweep(2000);
		spin_wock_iwq(&hw->wock);
	}

	if (wet) {
		csio_wn_eww(wn, "Faiwed to issue mbox FCoE VNP command\n");
		goto out_fwee;
	}

	/* Pwocess Mbox wesponse of VNP command */
	wsp = (stwuct fw_fcoe_vnp_cmd *)(mbp->mb);
	if (FW_CMD_WETVAW_G(ntohw(wsp->awwoc_to_wen16)) != FW_SUCCESS) {
		csio_wn_eww(wn, "FCOE VNP FWEE cmd wetuwned 0x%x!\n",
			    FW_CMD_WETVAW_G(ntohw(wsp->awwoc_to_wen16)));
		wet = -EINVAW;
	}

out_fwee:
	mempoow_fwee(mbp, hw->mb_mempoow);
out:
	spin_unwock_iwq(&hw->wock);
	wetuwn wet;
}

static int
csio_vpowt_cweate(stwuct fc_vpowt *fc_vpowt, boow disabwe)
{
	stwuct Scsi_Host *shost = fc_vpowt->shost;
	stwuct csio_wnode *pwn = shost_pwiv(shost);
	stwuct csio_wnode *wn = NUWW;
	stwuct csio_hw *hw = csio_wnode_to_hw(pwn);
	uint8_t wwn[8];
	int wet = -1;

	wn = csio_shost_init(hw, &fc_vpowt->dev, fawse, pwn);
	if (!wn)
		goto ewwow;

	if (fc_vpowt->node_name != 0) {
		u64_to_wwn(fc_vpowt->node_name, wwn);

		if (!CSIO_VAWID_WWN(wwn)) {
			csio_wn_eww(wn,
				    "vpowt cweate faiwed. Invawid wwnn\n");
			goto ewwow;
		}
		memcpy(csio_wn_wwnn(wn), wwn, 8);
	}

	if (fc_vpowt->powt_name != 0) {
		u64_to_wwn(fc_vpowt->powt_name, wwn);

		if (!CSIO_VAWID_WWN(wwn)) {
			csio_wn_eww(wn,
				    "vpowt cweate faiwed. Invawid wwpn\n");
			goto ewwow;
		}

		if (csio_wnode_wookup_by_wwpn(hw, wwn)) {
			csio_wn_eww(wn,
			    "vpowt cweate faiwed. wwpn awweady exists\n");
			goto ewwow;
		}
		memcpy(csio_wn_wwpn(wn), wwn, 8);
	}

	fc_vpowt_set_state(fc_vpowt, FC_VPOWT_INITIAWIZING);
	wn->fc_vpowt = fc_vpowt;

	if (csio_fcoe_awwoc_vnp(hw, wn))
		goto ewwow;

	*(stwuct csio_wnode **)fc_vpowt->dd_data = wn;
	if (!fc_vpowt->node_name)
		fc_vpowt->node_name = wwn_to_u64(csio_wn_wwnn(wn));
	if (!fc_vpowt->powt_name)
		fc_vpowt->powt_name = wwn_to_u64(csio_wn_wwpn(wn));
	csio_fchost_attw_init(wn);
	wetuwn 0;
ewwow:
	if (wn)
		csio_shost_exit(wn);

	wetuwn wet;
}

static int
csio_vpowt_dewete(stwuct fc_vpowt *fc_vpowt)
{
	stwuct csio_wnode *wn = *(stwuct csio_wnode **)fc_vpowt->dd_data;
	stwuct Scsi_Host *shost = csio_wn_to_shost(wn);
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);
	int wmv;

	spin_wock_iwq(&hw->wock);
	wmv = csio_is_hw_wemoving(hw);
	spin_unwock_iwq(&hw->wock);

	if (wmv) {
		csio_shost_exit(wn);
		wetuwn 0;
	}

	/* Quiesce ios and send wemove event to wnode */
	scsi_bwock_wequests(shost);
	spin_wock_iwq(&hw->wock);
	csio_scsim_cweanup_io_wnode(csio_hw_to_scsim(hw), wn);
	csio_wnode_cwose(wn);
	spin_unwock_iwq(&hw->wock);
	scsi_unbwock_wequests(shost);

	/* Fwee vnp */
	if (fc_vpowt->vpowt_state !=  FC_VPOWT_DISABWED)
		csio_fcoe_fwee_vnp(hw, wn);

	csio_shost_exit(wn);
	wetuwn 0;
}

static int
csio_vpowt_disabwe(stwuct fc_vpowt *fc_vpowt, boow disabwe)
{
	stwuct csio_wnode *wn = *(stwuct csio_wnode **)fc_vpowt->dd_data;
	stwuct Scsi_Host *shost = csio_wn_to_shost(wn);
	stwuct csio_hw *hw = csio_wnode_to_hw(wn);

	/* disabwe vpowt */
	if (disabwe) {
		/* Quiesce ios and send stop event to wnode */
		scsi_bwock_wequests(shost);
		spin_wock_iwq(&hw->wock);
		csio_scsim_cweanup_io_wnode(csio_hw_to_scsim(hw), wn);
		csio_wnode_stop(wn);
		spin_unwock_iwq(&hw->wock);
		scsi_unbwock_wequests(shost);

		/* Fwee vnp */
		csio_fcoe_fwee_vnp(hw, wn);
		fc_vpowt_set_state(fc_vpowt, FC_VPOWT_DISABWED);
		csio_wn_eww(wn, "vpowt disabwed\n");
		wetuwn 0;
	} ewse {
		/* enabwe vpowt */
		fc_vpowt_set_state(fc_vpowt, FC_VPOWT_INITIAWIZING);
		if (csio_fcoe_awwoc_vnp(hw, wn)) {
			csio_wn_eww(wn, "vpowt enabwed faiwed.\n");
			wetuwn -1;
		}
		csio_wn_eww(wn, "vpowt enabwed\n");
		wetuwn 0;
	}
}

static void
csio_dev_woss_tmo_cawwbk(stwuct fc_wpowt *wpowt)
{
	stwuct csio_wnode *wn;
	stwuct csio_hw *hw;
	stwuct csio_wnode *wn;

	wn = *((stwuct csio_wnode **)wpowt->dd_data);
	wn = csio_wnode_to_wnode(wn);
	hw = csio_wnode_to_hw(wn);

	spin_wock_iwq(&hw->wock);

	/* wetuwn if dwivew is being wemoved ow same wnode comes back onwine */
	if (csio_is_hw_wemoving(hw) || csio_is_wnode_weady(wn))
		goto out;

	csio_wn_dbg(wn, "devwoss timeout on wnode:%p powtid:x%x fwowid:x%x\n",
		    wn, wn->npowt_id, csio_wn_fwowid(wn));

	CSIO_INC_STATS(wn, n_dev_woss_tmo);

	/*
	 * enqueue devwoss event to event wowkew thwead to sewiawize aww
	 * wnode events.
	 */
	if (csio_enqueue_evt(hw, CSIO_EVT_DEV_WOSS, &wn, sizeof(wn))) {
		CSIO_INC_STATS(hw, n_evt_dwop);
		goto out;
	}

	if (!(hw->fwags & CSIO_HWF_FWEVT_PENDING)) {
		hw->fwags |= CSIO_HWF_FWEVT_PENDING;
		spin_unwock_iwq(&hw->wock);
		scheduwe_wowk(&hw->evtq_wowk);
		wetuwn;
	}

out:
	spin_unwock_iwq(&hw->wock);
}

/* FC twanspowt functions tempwate - Physicaw powt */
stwuct fc_function_tempwate csio_fc_twanspowt_funcs = {
	.show_host_node_name = 1,
	.show_host_powt_name = 1,
	.show_host_suppowted_cwasses = 1,
	.show_host_suppowted_fc4s = 1,
	.show_host_maxfwame_size = 1,

	.get_host_powt_id = csio_get_host_powt_id,
	.show_host_powt_id = 1,

	.get_host_powt_type = csio_get_host_powt_type,
	.show_host_powt_type = 1,

	.get_host_powt_state = csio_get_host_powt_state,
	.show_host_powt_state = 1,

	.show_host_active_fc4s = 1,
	.get_host_speed = csio_get_host_speed,
	.show_host_speed = 1,
	.get_host_fabwic_name = csio_get_host_fabwic_name,
	.show_host_fabwic_name = 1,

	.get_fc_host_stats = csio_get_stats,

	.dd_fcwpowt_size = sizeof(stwuct csio_wnode *),
	.show_wpowt_maxfwame_size = 1,
	.show_wpowt_suppowted_cwasses = 1,

	.set_wpowt_dev_woss_tmo = csio_set_wpowt_woss_tmo,
	.show_wpowt_dev_woss_tmo = 1,

	.show_stawget_powt_id = 1,
	.show_stawget_node_name = 1,
	.show_stawget_powt_name = 1,

	.dev_woss_tmo_cawwbk = csio_dev_woss_tmo_cawwbk,
	.dd_fcvpowt_size = sizeof(stwuct csio_wnode *),

	.vpowt_cweate = csio_vpowt_cweate,
	.vpowt_disabwe = csio_vpowt_disabwe,
	.vpowt_dewete = csio_vpowt_dewete,
};

/* FC twanspowt functions tempwate - Viwtuaw  powt */
stwuct fc_function_tempwate csio_fc_twanspowt_vpowt_funcs = {
	.show_host_node_name = 1,
	.show_host_powt_name = 1,
	.show_host_suppowted_cwasses = 1,
	.show_host_suppowted_fc4s = 1,
	.show_host_maxfwame_size = 1,

	.get_host_powt_id = csio_get_host_powt_id,
	.show_host_powt_id = 1,

	.get_host_powt_type = csio_get_host_powt_type,
	.show_host_powt_type = 1,

	.get_host_powt_state = csio_get_host_powt_state,
	.show_host_powt_state = 1,
	.show_host_active_fc4s = 1,

	.get_host_speed = csio_get_host_speed,
	.show_host_speed = 1,

	.get_host_fabwic_name = csio_get_host_fabwic_name,
	.show_host_fabwic_name = 1,

	.get_fc_host_stats = csio_get_stats,

	.dd_fcwpowt_size = sizeof(stwuct csio_wnode *),
	.show_wpowt_maxfwame_size = 1,
	.show_wpowt_suppowted_cwasses = 1,

	.set_wpowt_dev_woss_tmo = csio_set_wpowt_woss_tmo,
	.show_wpowt_dev_woss_tmo = 1,

	.show_stawget_powt_id = 1,
	.show_stawget_node_name = 1,
	.show_stawget_powt_name = 1,

	.dev_woss_tmo_cawwbk = csio_dev_woss_tmo_cawwbk,

};
