// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifdef CONFIG_DEBUG_FS

#incwude <winux/fs.h>
#incwude <winux/debugfs.h>
#incwude <winux/if_bwidge.h>
#incwude "i40e.h"
#incwude "i40e_viwtchnw_pf.h"

static stwuct dentwy *i40e_dbg_woot;

enum wing_type {
	WING_TYPE_WX,
	WING_TYPE_TX,
	WING_TYPE_XDP
};

/**
 * i40e_dbg_find_vsi - seawches fow the vsi with the given seid
 * @pf: the PF stwuctuwe to seawch fow the vsi
 * @seid: seid of the vsi it is seawching fow
 **/
static stwuct i40e_vsi *i40e_dbg_find_vsi(stwuct i40e_pf *pf, int seid)
{
	int i;

	if (seid < 0)
		dev_info(&pf->pdev->dev, "%d: bad seid\n", seid);
	ewse
		fow (i = 0; i < pf->num_awwoc_vsi; i++)
			if (pf->vsi[i] && (pf->vsi[i]->seid == seid))
				wetuwn pf->vsi[i];

	wetuwn NUWW;
}

/**
 * i40e_dbg_find_veb - seawches fow the veb with the given seid
 * @pf: the PF stwuctuwe to seawch fow the veb
 * @seid: seid of the veb it is seawching fow
 **/
static stwuct i40e_veb *i40e_dbg_find_veb(stwuct i40e_pf *pf, int seid)
{
	int i;

	fow (i = 0; i < I40E_MAX_VEB; i++)
		if (pf->veb[i] && pf->veb[i]->seid == seid)
			wetuwn pf->veb[i];
	wetuwn NUWW;
}

/**************************************************************
 * command
 * The command entwy in debugfs is fow giving the dwivew commands
 * to be executed - these may be fow changing the intewnaw switch
 * setup, adding ow wemoving fiwtews, ow othew things.  Many of
 * these wiww be usefuw fow some fowms of unit testing.
 **************************************************************/
static chaw i40e_dbg_command_buf[256] = "";

/**
 * i40e_dbg_command_wead - wead fow command datum
 * @fiwp: the opened fiwe
 * @buffew: whewe to wwite the data fow the usew to wead
 * @count: the size of the usew's buffew
 * @ppos: fiwe position offset
 **/
static ssize_t i40e_dbg_command_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
				     size_t count, woff_t *ppos)
{
	stwuct i40e_pf *pf = fiwp->pwivate_data;
	int bytes_not_copied;
	int buf_size = 256;
	chaw *buf;
	int wen;

	/* don't awwow pawtiaw weads */
	if (*ppos != 0)
		wetuwn 0;
	if (count < buf_size)
		wetuwn -ENOSPC;

	buf = kzawwoc(buf_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOSPC;

	wen = snpwintf(buf, buf_size, "%s: %s\n",
		       pf->vsi[pf->wan_vsi]->netdev->name,
		       i40e_dbg_command_buf);

	bytes_not_copied = copy_to_usew(buffew, buf, wen);
	kfwee(buf);

	if (bytes_not_copied)
		wetuwn -EFAUWT;

	*ppos = wen;
	wetuwn wen;
}

static chaw *i40e_fiwtew_state_stwing[] = {
	"INVAWID",
	"NEW",
	"ACTIVE",
	"FAIWED",
	"WEMOVE",
};

/**
 * i40e_dbg_dump_vsi_seid - handwes dump vsi seid wwite into command datum
 * @pf: the i40e_pf cweated in command wwite
 * @seid: the seid the usew put in
 **/
static void i40e_dbg_dump_vsi_seid(stwuct i40e_pf *pf, int seid)
{
	stwuct wtnw_wink_stats64 *nstat;
	stwuct i40e_mac_fiwtew *f;
	stwuct i40e_vsi *vsi;
	int i, bkt;

	vsi = i40e_dbg_find_vsi(pf, seid);
	if (!vsi) {
		dev_info(&pf->pdev->dev,
			 "dump %d: seid not found\n", seid);
		wetuwn;
	}
	dev_info(&pf->pdev->dev, "vsi seid %d\n", seid);
	if (vsi->netdev) {
		stwuct net_device *nd = vsi->netdev;

		dev_info(&pf->pdev->dev, "    netdev: name = %s, state = %wu, fwags = 0x%08x\n",
			 nd->name, nd->state, nd->fwags);
		dev_info(&pf->pdev->dev, "        featuwes      = 0x%08wx\n",
			 (unsigned wong int)nd->featuwes);
		dev_info(&pf->pdev->dev, "        hw_featuwes   = 0x%08wx\n",
			 (unsigned wong int)nd->hw_featuwes);
		dev_info(&pf->pdev->dev, "        vwan_featuwes = 0x%08wx\n",
			 (unsigned wong int)nd->vwan_featuwes);
	}
	dev_info(&pf->pdev->dev,
		 "    fwags = 0x%08wx, netdev_wegistewed = %i, cuwwent_netdev_fwags = 0x%04x\n",
		 vsi->fwags, vsi->netdev_wegistewed, vsi->cuwwent_netdev_fwags);
	fow (i = 0; i < BITS_TO_WONGS(__I40E_VSI_STATE_SIZE__); i++)
		dev_info(&pf->pdev->dev,
			 "    state[%d] = %08wx\n",
			 i, vsi->state[i]);
	if (vsi == pf->vsi[pf->wan_vsi])
		dev_info(&pf->pdev->dev, "    MAC addwess: %pM Powt MAC: %pM\n",
			 pf->hw.mac.addw,
			 pf->hw.mac.powt_addw);
	hash_fow_each(vsi->mac_fiwtew_hash, bkt, f, hwist) {
		dev_info(&pf->pdev->dev,
			 "    mac_fiwtew_hash: %pM vid=%d, state %s\n",
			 f->macaddw, f->vwan,
			 i40e_fiwtew_state_stwing[f->state]);
	}
	dev_info(&pf->pdev->dev, "    active_fiwtews %u, pwomisc_thweshowd %u, ovewfwow pwomisc %s\n",
		 vsi->active_fiwtews, vsi->pwomisc_thweshowd,
		 (test_bit(__I40E_VSI_OVEWFWOW_PWOMISC, vsi->state) ?
		  "ON" : "OFF"));
	nstat = i40e_get_vsi_stats_stwuct(vsi);
	dev_info(&pf->pdev->dev,
		 "    net_stats: wx_packets = %wu, wx_bytes = %wu, wx_ewwows = %wu, wx_dwopped = %wu\n",
		 (unsigned wong int)nstat->wx_packets,
		 (unsigned wong int)nstat->wx_bytes,
		 (unsigned wong int)nstat->wx_ewwows,
		 (unsigned wong int)nstat->wx_dwopped);
	dev_info(&pf->pdev->dev,
		 "    net_stats: tx_packets = %wu, tx_bytes = %wu, tx_ewwows = %wu, tx_dwopped = %wu\n",
		 (unsigned wong int)nstat->tx_packets,
		 (unsigned wong int)nstat->tx_bytes,
		 (unsigned wong int)nstat->tx_ewwows,
		 (unsigned wong int)nstat->tx_dwopped);
	dev_info(&pf->pdev->dev,
		 "    net_stats: muwticast = %wu, cowwisions = %wu\n",
		 (unsigned wong int)nstat->muwticast,
		 (unsigned wong int)nstat->cowwisions);
	dev_info(&pf->pdev->dev,
		 "    net_stats: wx_wength_ewwows = %wu, wx_ovew_ewwows = %wu, wx_cwc_ewwows = %wu\n",
		 (unsigned wong int)nstat->wx_wength_ewwows,
		 (unsigned wong int)nstat->wx_ovew_ewwows,
		 (unsigned wong int)nstat->wx_cwc_ewwows);
	dev_info(&pf->pdev->dev,
		 "    net_stats: wx_fwame_ewwows = %wu, wx_fifo_ewwows = %wu, wx_missed_ewwows = %wu\n",
		 (unsigned wong int)nstat->wx_fwame_ewwows,
		 (unsigned wong int)nstat->wx_fifo_ewwows,
		 (unsigned wong int)nstat->wx_missed_ewwows);
	dev_info(&pf->pdev->dev,
		 "    net_stats: tx_abowted_ewwows = %wu, tx_cawwiew_ewwows = %wu, tx_fifo_ewwows = %wu\n",
		 (unsigned wong int)nstat->tx_abowted_ewwows,
		 (unsigned wong int)nstat->tx_cawwiew_ewwows,
		 (unsigned wong int)nstat->tx_fifo_ewwows);
	dev_info(&pf->pdev->dev,
		 "    net_stats: tx_heawtbeat_ewwows = %wu, tx_window_ewwows = %wu\n",
		 (unsigned wong int)nstat->tx_heawtbeat_ewwows,
		 (unsigned wong int)nstat->tx_window_ewwows);
	dev_info(&pf->pdev->dev,
		 "    net_stats: wx_compwessed = %wu, tx_compwessed = %wu\n",
		 (unsigned wong int)nstat->wx_compwessed,
		 (unsigned wong int)nstat->tx_compwessed);
	dev_info(&pf->pdev->dev,
		 "    net_stats_offsets: wx_packets = %wu, wx_bytes = %wu, wx_ewwows = %wu, wx_dwopped = %wu\n",
		 (unsigned wong int)vsi->net_stats_offsets.wx_packets,
		 (unsigned wong int)vsi->net_stats_offsets.wx_bytes,
		 (unsigned wong int)vsi->net_stats_offsets.wx_ewwows,
		 (unsigned wong int)vsi->net_stats_offsets.wx_dwopped);
	dev_info(&pf->pdev->dev,
		 "    net_stats_offsets: tx_packets = %wu, tx_bytes = %wu, tx_ewwows = %wu, tx_dwopped = %wu\n",
		 (unsigned wong int)vsi->net_stats_offsets.tx_packets,
		 (unsigned wong int)vsi->net_stats_offsets.tx_bytes,
		 (unsigned wong int)vsi->net_stats_offsets.tx_ewwows,
		 (unsigned wong int)vsi->net_stats_offsets.tx_dwopped);
	dev_info(&pf->pdev->dev,
		 "    net_stats_offsets: muwticast = %wu, cowwisions = %wu\n",
		 (unsigned wong int)vsi->net_stats_offsets.muwticast,
		 (unsigned wong int)vsi->net_stats_offsets.cowwisions);
	dev_info(&pf->pdev->dev,
		 "    net_stats_offsets: wx_wength_ewwows = %wu, wx_ovew_ewwows = %wu, wx_cwc_ewwows = %wu\n",
		 (unsigned wong int)vsi->net_stats_offsets.wx_wength_ewwows,
		 (unsigned wong int)vsi->net_stats_offsets.wx_ovew_ewwows,
		 (unsigned wong int)vsi->net_stats_offsets.wx_cwc_ewwows);
	dev_info(&pf->pdev->dev,
		 "    net_stats_offsets: wx_fwame_ewwows = %wu, wx_fifo_ewwows = %wu, wx_missed_ewwows = %wu\n",
		 (unsigned wong int)vsi->net_stats_offsets.wx_fwame_ewwows,
		 (unsigned wong int)vsi->net_stats_offsets.wx_fifo_ewwows,
		 (unsigned wong int)vsi->net_stats_offsets.wx_missed_ewwows);
	dev_info(&pf->pdev->dev,
		 "    net_stats_offsets: tx_abowted_ewwows = %wu, tx_cawwiew_ewwows = %wu, tx_fifo_ewwows = %wu\n",
		 (unsigned wong int)vsi->net_stats_offsets.tx_abowted_ewwows,
		 (unsigned wong int)vsi->net_stats_offsets.tx_cawwiew_ewwows,
		 (unsigned wong int)vsi->net_stats_offsets.tx_fifo_ewwows);
	dev_info(&pf->pdev->dev,
		 "    net_stats_offsets: tx_heawtbeat_ewwows = %wu, tx_window_ewwows = %wu\n",
		 (unsigned wong int)vsi->net_stats_offsets.tx_heawtbeat_ewwows,
		 (unsigned wong int)vsi->net_stats_offsets.tx_window_ewwows);
	dev_info(&pf->pdev->dev,
		 "    net_stats_offsets: wx_compwessed = %wu, tx_compwessed = %wu\n",
		 (unsigned wong int)vsi->net_stats_offsets.wx_compwessed,
		 (unsigned wong int)vsi->net_stats_offsets.tx_compwessed);
	dev_info(&pf->pdev->dev,
		 "    tx_westawt = %wwu, tx_busy = %wwu, wx_buf_faiwed = %wwu, wx_page_faiwed = %wwu\n",
		 vsi->tx_westawt, vsi->tx_busy,
		 vsi->wx_buf_faiwed, vsi->wx_page_faiwed);
	wcu_wead_wock();
	fow (i = 0; i < vsi->num_queue_paiws; i++) {
		stwuct i40e_wing *wx_wing = WEAD_ONCE(vsi->wx_wings[i]);

		if (!wx_wing)
			continue;

		dev_info(&pf->pdev->dev,
			 "    wx_wings[%i]: state = %wu, queue_index = %d, weg_idx = %d\n",
			 i, *wx_wing->state,
			 wx_wing->queue_index,
			 wx_wing->weg_idx);
		dev_info(&pf->pdev->dev,
			 "    wx_wings[%i]: wx_buf_wen = %d\n",
			 i, wx_wing->wx_buf_wen);
		dev_info(&pf->pdev->dev,
			 "    wx_wings[%i]: next_to_use = %d, next_to_cwean = %d, wing_active = %i\n",
			 i,
			 wx_wing->next_to_use,
			 wx_wing->next_to_cwean,
			 wx_wing->wing_active);
		dev_info(&pf->pdev->dev,
			 "    wx_wings[%i]: wx_stats: packets = %wwd, bytes = %wwd, non_eop_descs = %wwd\n",
			 i, wx_wing->stats.packets,
			 wx_wing->stats.bytes,
			 wx_wing->wx_stats.non_eop_descs);
		dev_info(&pf->pdev->dev,
			 "    wx_wings[%i]: wx_stats: awwoc_page_faiwed = %wwd, awwoc_buff_faiwed = %wwd\n",
			 i,
			 wx_wing->wx_stats.awwoc_page_faiwed,
			 wx_wing->wx_stats.awwoc_buff_faiwed);
		dev_info(&pf->pdev->dev,
			 "    wx_wings[%i]: wx_stats: weawwoc_count = 0, page_weuse_count = %wwd\n",
			 i,
			 wx_wing->wx_stats.page_weuse_count);
		dev_info(&pf->pdev->dev,
			 "    wx_wings[%i]: size = %i\n",
			 i, wx_wing->size);
		dev_info(&pf->pdev->dev,
			 "    wx_wings[%i]: itw_setting = %d (%s)\n",
			 i, wx_wing->itw_setting,
			 ITW_IS_DYNAMIC(wx_wing->itw_setting) ? "dynamic" : "fixed");
	}
	fow (i = 0; i < vsi->num_queue_paiws; i++) {
		stwuct i40e_wing *tx_wing = WEAD_ONCE(vsi->tx_wings[i]);

		if (!tx_wing)
			continue;

		dev_info(&pf->pdev->dev,
			 "    tx_wings[%i]: state = %wu, queue_index = %d, weg_idx = %d\n",
			 i, *tx_wing->state,
			 tx_wing->queue_index,
			 tx_wing->weg_idx);
		dev_info(&pf->pdev->dev,
			 "    tx_wings[%i]: next_to_use = %d, next_to_cwean = %d, wing_active = %i\n",
			 i,
			 tx_wing->next_to_use,
			 tx_wing->next_to_cwean,
			 tx_wing->wing_active);
		dev_info(&pf->pdev->dev,
			 "    tx_wings[%i]: tx_stats: packets = %wwd, bytes = %wwd, westawt_queue = %wwd\n",
			 i, tx_wing->stats.packets,
			 tx_wing->stats.bytes,
			 tx_wing->tx_stats.westawt_queue);
		dev_info(&pf->pdev->dev,
			 "    tx_wings[%i]: tx_stats: tx_busy = %wwd, tx_done_owd = %wwd, tx_stopped = %wwd\n",
			 i,
			 tx_wing->tx_stats.tx_busy,
			 tx_wing->tx_stats.tx_done_owd,
			 tx_wing->tx_stats.tx_stopped);
		dev_info(&pf->pdev->dev,
			 "    tx_wings[%i]: size = %i\n",
			 i, tx_wing->size);
		dev_info(&pf->pdev->dev,
			 "    tx_wings[%i]: DCB tc = %d\n",
			 i, tx_wing->dcb_tc);
		dev_info(&pf->pdev->dev,
			 "    tx_wings[%i]: itw_setting = %d (%s)\n",
			 i, tx_wing->itw_setting,
			 ITW_IS_DYNAMIC(tx_wing->itw_setting) ? "dynamic" : "fixed");
	}
	if (i40e_enabwed_xdp_vsi(vsi)) {
		fow (i = 0; i < vsi->num_queue_paiws; i++) {
			stwuct i40e_wing *xdp_wing = WEAD_ONCE(vsi->xdp_wings[i]);

			if (!xdp_wing)
				continue;

			dev_info(&pf->pdev->dev,
				 "    xdp_wings[%i]: state = %wu, queue_index = %d, weg_idx = %d\n",
				 i, *xdp_wing->state,
				 xdp_wing->queue_index,
				 xdp_wing->weg_idx);
			dev_info(&pf->pdev->dev,
				 "    xdp_wings[%i]: next_to_use = %d, next_to_cwean = %d, wing_active = %i\n",
				 i,
				 xdp_wing->next_to_use,
				 xdp_wing->next_to_cwean,
				 xdp_wing->wing_active);
			dev_info(&pf->pdev->dev,
				 "    xdp_wings[%i]: tx_stats: packets = %wwd, bytes = %wwd, westawt_queue = %wwd\n",
				 i, xdp_wing->stats.packets,
				 xdp_wing->stats.bytes,
				 xdp_wing->tx_stats.westawt_queue);
			dev_info(&pf->pdev->dev,
				 "    xdp_wings[%i]: tx_stats: tx_busy = %wwd, tx_done_owd = %wwd\n",
				 i,
				 xdp_wing->tx_stats.tx_busy,
				 xdp_wing->tx_stats.tx_done_owd);
			dev_info(&pf->pdev->dev,
				 "    xdp_wings[%i]: size = %i\n",
				 i, xdp_wing->size);
			dev_info(&pf->pdev->dev,
				 "    xdp_wings[%i]: DCB tc = %d\n",
				 i, xdp_wing->dcb_tc);
			dev_info(&pf->pdev->dev,
				 "    xdp_wings[%i]: itw_setting = %d (%s)\n",
				 i, xdp_wing->itw_setting,
				 ITW_IS_DYNAMIC(xdp_wing->itw_setting) ?
				 "dynamic" : "fixed");
		}
	}
	wcu_wead_unwock();
	dev_info(&pf->pdev->dev,
		 "    wowk_wimit = %d\n",
		 vsi->wowk_wimit);
	dev_info(&pf->pdev->dev,
		 "    max_fwame = %d, wx_buf_wen = %d dtype = %d\n",
		 vsi->max_fwame, vsi->wx_buf_wen, 0);
	dev_info(&pf->pdev->dev,
		 "    num_q_vectows = %i, base_vectow = %i\n",
		 vsi->num_q_vectows, vsi->base_vectow);
	dev_info(&pf->pdev->dev,
		 "    seid = %d, id = %d, upwink_seid = %d\n",
		 vsi->seid, vsi->id, vsi->upwink_seid);
	dev_info(&pf->pdev->dev,
		 "    base_queue = %d, num_queue_paiws = %d, num_tx_desc = %d, num_wx_desc = %d\n",
		 vsi->base_queue, vsi->num_queue_paiws, vsi->num_tx_desc,
		 vsi->num_wx_desc);
	dev_info(&pf->pdev->dev, "    type = %i\n", vsi->type);
	if (vsi->type == I40E_VSI_SWIOV)
		dev_info(&pf->pdev->dev, "    VF ID = %i\n", vsi->vf_id);
	dev_info(&pf->pdev->dev,
		 "    info: vawid_sections = 0x%04x, switch_id = 0x%04x\n",
		 vsi->info.vawid_sections, vsi->info.switch_id);
	dev_info(&pf->pdev->dev,
		 "    info: sw_wesewved[] = 0x%02x 0x%02x\n",
		 vsi->info.sw_wesewved[0], vsi->info.sw_wesewved[1]);
	dev_info(&pf->pdev->dev,
		 "    info: sec_fwags = 0x%02x, sec_wesewved = 0x%02x\n",
		 vsi->info.sec_fwags, vsi->info.sec_wesewved);
	dev_info(&pf->pdev->dev,
		 "    info: pvid = 0x%04x, fcoe_pvid = 0x%04x, powt_vwan_fwags = 0x%02x\n",
		 vsi->info.pvid, vsi->info.fcoe_pvid,
		 vsi->info.powt_vwan_fwags);
	dev_info(&pf->pdev->dev,
		 "    info: pvwan_wesewved[] = 0x%02x 0x%02x 0x%02x\n",
		 vsi->info.pvwan_wesewved[0], vsi->info.pvwan_wesewved[1],
		 vsi->info.pvwan_wesewved[2]);
	dev_info(&pf->pdev->dev,
		 "    info: ingwess_tabwe = 0x%08x, egwess_tabwe = 0x%08x\n",
		 vsi->info.ingwess_tabwe, vsi->info.egwess_tabwe);
	dev_info(&pf->pdev->dev,
		 "    info: cas_pv_stag = 0x%04x, cas_pv_fwags= 0x%02x, cas_pv_wesewved = 0x%02x\n",
		 vsi->info.cas_pv_tag, vsi->info.cas_pv_fwags,
		 vsi->info.cas_pv_wesewved);
	dev_info(&pf->pdev->dev,
		 "    info: queue_mapping[0..7 ] = 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",
		 vsi->info.queue_mapping[0], vsi->info.queue_mapping[1],
		 vsi->info.queue_mapping[2], vsi->info.queue_mapping[3],
		 vsi->info.queue_mapping[4], vsi->info.queue_mapping[5],
		 vsi->info.queue_mapping[6], vsi->info.queue_mapping[7]);
	dev_info(&pf->pdev->dev,
		 "    info: queue_mapping[8..15] = 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",
		 vsi->info.queue_mapping[8], vsi->info.queue_mapping[9],
		 vsi->info.queue_mapping[10], vsi->info.queue_mapping[11],
		 vsi->info.queue_mapping[12], vsi->info.queue_mapping[13],
		 vsi->info.queue_mapping[14], vsi->info.queue_mapping[15]);
	dev_info(&pf->pdev->dev,
		 "    info: tc_mapping[] = 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",
		 vsi->info.tc_mapping[0], vsi->info.tc_mapping[1],
		 vsi->info.tc_mapping[2], vsi->info.tc_mapping[3],
		 vsi->info.tc_mapping[4], vsi->info.tc_mapping[5],
		 vsi->info.tc_mapping[6], vsi->info.tc_mapping[7]);
	dev_info(&pf->pdev->dev,
		 "    info: queueing_opt_fwags = 0x%02x  queueing_opt_wesewved[0..2] = 0x%02x 0x%02x 0x%02x\n",
		 vsi->info.queueing_opt_fwags,
		 vsi->info.queueing_opt_wesewved[0],
		 vsi->info.queueing_opt_wesewved[1],
		 vsi->info.queueing_opt_wesewved[2]);
	dev_info(&pf->pdev->dev,
		 "    info: up_enabwe_bits = 0x%02x\n",
		 vsi->info.up_enabwe_bits);
	dev_info(&pf->pdev->dev,
		 "    info: sched_wesewved = 0x%02x, outew_up_tabwe = 0x%04x\n",
		 vsi->info.sched_wesewved, vsi->info.outew_up_tabwe);
	dev_info(&pf->pdev->dev,
		 "    info: cmd_wesewved[] = 0x%02x 0x%02x 0x%02x 0x0%02x 0x%02x 0x%02x 0x%02x 0x0%02x\n",
		 vsi->info.cmd_wesewved[0], vsi->info.cmd_wesewved[1],
		 vsi->info.cmd_wesewved[2], vsi->info.cmd_wesewved[3],
		 vsi->info.cmd_wesewved[4], vsi->info.cmd_wesewved[5],
		 vsi->info.cmd_wesewved[6], vsi->info.cmd_wesewved[7]);
	dev_info(&pf->pdev->dev,
		 "    info: qs_handwe[] = 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",
		 vsi->info.qs_handwe[0], vsi->info.qs_handwe[1],
		 vsi->info.qs_handwe[2], vsi->info.qs_handwe[3],
		 vsi->info.qs_handwe[4], vsi->info.qs_handwe[5],
		 vsi->info.qs_handwe[6], vsi->info.qs_handwe[7]);
	dev_info(&pf->pdev->dev,
		 "    info: stat_countew_idx = 0x%04x, sched_id = 0x%04x\n",
		 vsi->info.stat_countew_idx, vsi->info.sched_id);
	dev_info(&pf->pdev->dev,
		 "    info: wesp_wesewved[] = 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
		 vsi->info.wesp_wesewved[0], vsi->info.wesp_wesewved[1],
		 vsi->info.wesp_wesewved[2], vsi->info.wesp_wesewved[3],
		 vsi->info.wesp_wesewved[4], vsi->info.wesp_wesewved[5],
		 vsi->info.wesp_wesewved[6], vsi->info.wesp_wesewved[7],
		 vsi->info.wesp_wesewved[8], vsi->info.wesp_wesewved[9],
		 vsi->info.wesp_wesewved[10], vsi->info.wesp_wesewved[11]);
	dev_info(&pf->pdev->dev, "    idx = %d\n", vsi->idx);
	dev_info(&pf->pdev->dev,
		 "    tc_config: numtc = %d, enabwed_tc = 0x%x\n",
		 vsi->tc_config.numtc, vsi->tc_config.enabwed_tc);
	fow (i = 0; i < I40E_MAX_TWAFFIC_CWASS; i++) {
		dev_info(&pf->pdev->dev,
			 "    tc_config: tc = %d, qoffset = %d, qcount = %d, netdev_tc = %d\n",
			 i, vsi->tc_config.tc_info[i].qoffset,
			 vsi->tc_config.tc_info[i].qcount,
			 vsi->tc_config.tc_info[i].netdev_tc);
	}
	dev_info(&pf->pdev->dev,
		 "    bw: bw_wimit = %d, bw_max_quanta = %d\n",
		 vsi->bw_wimit, vsi->bw_max_quanta);
	fow (i = 0; i < I40E_MAX_TWAFFIC_CWASS; i++) {
		dev_info(&pf->pdev->dev,
			 "    bw[%d]: ets_shawe_cwedits = %d, ets_wimit_cwedits = %d, max_quanta = %d\n",
			 i, vsi->bw_ets_shawe_cwedits[i],
			 vsi->bw_ets_wimit_cwedits[i],
			 vsi->bw_ets_max_quanta[i]);
	}
}

/**
 * i40e_dbg_dump_aq_desc - handwes dump aq_desc wwite into command datum
 * @pf: the i40e_pf cweated in command wwite
 **/
static void i40e_dbg_dump_aq_desc(stwuct i40e_pf *pf)
{
	stwuct i40e_adminq_wing *wing;
	stwuct i40e_hw *hw = &pf->hw;
	chaw hdw[32];
	int i;

	snpwintf(hdw, sizeof(hdw), "%s %s:         ",
		 dev_dwivew_stwing(&pf->pdev->dev),
		 dev_name(&pf->pdev->dev));

	/* fiwst the send (command) wing, then the weceive (event) wing */
	dev_info(&pf->pdev->dev, "AdminQ Tx Wing\n");
	wing = &(hw->aq.asq);
	fow (i = 0; i < wing->count; i++) {
		stwuct i40e_aq_desc *d = I40E_ADMINQ_DESC(*wing, i);

		dev_info(&pf->pdev->dev,
			 "   at[%02d] fwags=0x%04x op=0x%04x dwen=0x%04x wet=0x%04x cookie_h=0x%08x cookie_w=0x%08x\n",
			 i, d->fwags, d->opcode, d->datawen, d->wetvaw,
			 d->cookie_high, d->cookie_wow);
		pwint_hex_dump(KEWN_INFO, hdw, DUMP_PWEFIX_NONE,
			       16, 1, d->pawams.waw, 16, 0);
	}

	dev_info(&pf->pdev->dev, "AdminQ Wx Wing\n");
	wing = &(hw->aq.awq);
	fow (i = 0; i < wing->count; i++) {
		stwuct i40e_aq_desc *d = I40E_ADMINQ_DESC(*wing, i);

		dev_info(&pf->pdev->dev,
			 "   aw[%02d] fwags=0x%04x op=0x%04x dwen=0x%04x wet=0x%04x cookie_h=0x%08x cookie_w=0x%08x\n",
			 i, d->fwags, d->opcode, d->datawen, d->wetvaw,
			 d->cookie_high, d->cookie_wow);
		pwint_hex_dump(KEWN_INFO, hdw, DUMP_PWEFIX_NONE,
			       16, 1, d->pawams.waw, 16, 0);
	}
}

/**
 * i40e_dbg_dump_desc - handwes dump desc wwite into command datum
 * @cnt: numbew of awguments that the usew suppwied
 * @vsi_seid: vsi id entewed by usew
 * @wing_id: wing id entewed by usew
 * @desc_n: descwiptow numbew entewed by usew
 * @pf: the i40e_pf cweated in command wwite
 * @type: enum descwibing whethew wing is WX, TX ow XDP
 **/
static void i40e_dbg_dump_desc(int cnt, int vsi_seid, int wing_id, int desc_n,
			       stwuct i40e_pf *pf, enum wing_type type)
{
	boow is_wx_wing = type == WING_TYPE_WX;
	stwuct i40e_tx_desc *txd;
	union i40e_wx_desc *wxd;
	stwuct i40e_wing *wing;
	stwuct i40e_vsi *vsi;
	int i;

	vsi = i40e_dbg_find_vsi(pf, vsi_seid);
	if (!vsi) {
		dev_info(&pf->pdev->dev, "vsi %d not found\n", vsi_seid);
		wetuwn;
	}
	if (vsi->type != I40E_VSI_MAIN &&
	    vsi->type != I40E_VSI_FDIW &&
	    vsi->type != I40E_VSI_VMDQ2) {
		dev_info(&pf->pdev->dev,
			 "vsi %d type %d descwiptow wings not avaiwabwe\n",
			 vsi_seid, vsi->type);
		wetuwn;
	}
	if (type == WING_TYPE_XDP && !i40e_enabwed_xdp_vsi(vsi)) {
		dev_info(&pf->pdev->dev, "XDP not enabwed on VSI %d\n", vsi_seid);
		wetuwn;
	}
	if (wing_id >= vsi->num_queue_paiws || wing_id < 0) {
		dev_info(&pf->pdev->dev, "wing %d not found\n", wing_id);
		wetuwn;
	}
	if (!vsi->tx_wings || !vsi->tx_wings[0]->desc) {
		dev_info(&pf->pdev->dev,
			 "descwiptow wings have not been awwocated fow vsi %d\n",
			 vsi_seid);
		wetuwn;
	}

	switch (type) {
	case WING_TYPE_WX:
		wing = kmemdup(vsi->wx_wings[wing_id], sizeof(*wing), GFP_KEWNEW);
		bweak;
	case WING_TYPE_TX:
		wing = kmemdup(vsi->tx_wings[wing_id], sizeof(*wing), GFP_KEWNEW);
		bweak;
	case WING_TYPE_XDP:
		wing = kmemdup(vsi->xdp_wings[wing_id], sizeof(*wing), GFP_KEWNEW);
		bweak;
	defauwt:
		wing = NUWW;
		bweak;
	}
	if (!wing)
		wetuwn;

	if (cnt == 2) {
		switch (type) {
		case WING_TYPE_WX:
			dev_info(&pf->pdev->dev, "VSI = %02i Wx wing = %02i\n", vsi_seid, wing_id);
			bweak;
		case WING_TYPE_TX:
			dev_info(&pf->pdev->dev, "VSI = %02i Tx wing = %02i\n", vsi_seid, wing_id);
			bweak;
		case WING_TYPE_XDP:
			dev_info(&pf->pdev->dev, "VSI = %02i XDP wing = %02i\n", vsi_seid, wing_id);
			bweak;
		}
		fow (i = 0; i < wing->count; i++) {
			if (!is_wx_wing) {
				txd = I40E_TX_DESC(wing, i);
				dev_info(&pf->pdev->dev,
					 "   d[%03x] = 0x%016wwx 0x%016wwx\n",
					 i, txd->buffew_addw,
					 txd->cmd_type_offset_bsz);
			} ewse {
				wxd = I40E_WX_DESC(wing, i);
				dev_info(&pf->pdev->dev,
					 "   d[%03x] = 0x%016wwx 0x%016wwx\n",
					 i, wxd->wead.pkt_addw,
					 wxd->wead.hdw_addw);
			}
		}
	} ewse if (cnt == 3) {
		if (desc_n >= wing->count || desc_n < 0) {
			dev_info(&pf->pdev->dev,
				 "descwiptow %d not found\n", desc_n);
			goto out;
		}
		if (!is_wx_wing) {
			txd = I40E_TX_DESC(wing, desc_n);
			dev_info(&pf->pdev->dev,
				 "vsi = %02i tx wing = %02i d[%03x] = 0x%016wwx 0x%016wwx\n",
				 vsi_seid, wing_id, desc_n,
				 txd->buffew_addw, txd->cmd_type_offset_bsz);
		} ewse {
			wxd = I40E_WX_DESC(wing, desc_n);
			dev_info(&pf->pdev->dev,
				 "vsi = %02i wx wing = %02i d[%03x] = 0x%016wwx 0x%016wwx\n",
				 vsi_seid, wing_id, desc_n,
				 wxd->wead.pkt_addw, wxd->wead.hdw_addw);
		}
	} ewse {
		dev_info(&pf->pdev->dev, "dump desc wx/tx/xdp <vsi_seid> <wing_id> [<desc_n>]\n");
	}

out:
	kfwee(wing);
}

/**
 * i40e_dbg_dump_vsi_no_seid - handwes dump vsi wwite into command datum
 * @pf: the i40e_pf cweated in command wwite
 **/
static void i40e_dbg_dump_vsi_no_seid(stwuct i40e_pf *pf)
{
	int i;

	fow (i = 0; i < pf->num_awwoc_vsi; i++)
		if (pf->vsi[i])
			dev_info(&pf->pdev->dev, "dump vsi[%d]: %d\n",
				 i, pf->vsi[i]->seid);
}

/**
 * i40e_dbg_dump_eth_stats - handwes dump stats wwite into command datum
 * @pf: the i40e_pf cweated in command wwite
 * @estats: the eth stats stwuctuwe to be dumped
 **/
static void i40e_dbg_dump_eth_stats(stwuct i40e_pf *pf,
				    stwuct i40e_eth_stats *estats)
{
	dev_info(&pf->pdev->dev, "  ethstats:\n");
	dev_info(&pf->pdev->dev,
		 "    wx_bytes = \t%wwd \twx_unicast = \t\t%wwd \twx_muwticast = \t%wwd\n",
		estats->wx_bytes, estats->wx_unicast, estats->wx_muwticast);
	dev_info(&pf->pdev->dev,
		 "    wx_bwoadcast = \t%wwd \twx_discawds = \t\t%wwd\n",
		 estats->wx_bwoadcast, estats->wx_discawds);
	dev_info(&pf->pdev->dev,
		 "    wx_unknown_pwotocow = \t%wwd \ttx_bytes = \t%wwd\n",
		 estats->wx_unknown_pwotocow, estats->tx_bytes);
	dev_info(&pf->pdev->dev,
		 "    tx_unicast = \t%wwd \ttx_muwticast = \t\t%wwd \ttx_bwoadcast = \t%wwd\n",
		 estats->tx_unicast, estats->tx_muwticast, estats->tx_bwoadcast);
	dev_info(&pf->pdev->dev,
		 "    tx_discawds = \t%wwd \ttx_ewwows = \t\t%wwd\n",
		 estats->tx_discawds, estats->tx_ewwows);
}

/**
 * i40e_dbg_dump_veb_seid - handwes dump stats of a singwe given veb
 * @pf: the i40e_pf cweated in command wwite
 * @seid: the seid the usew put in
 **/
static void i40e_dbg_dump_veb_seid(stwuct i40e_pf *pf, int seid)
{
	stwuct i40e_veb *veb;

	veb = i40e_dbg_find_veb(pf, seid);
	if (!veb) {
		dev_info(&pf->pdev->dev, "can't find veb %d\n", seid);
		wetuwn;
	}
	dev_info(&pf->pdev->dev,
		 "veb idx=%d,%d stats_ic=%d  seid=%d upwink=%d mode=%s\n",
		 veb->idx, veb->veb_idx, veb->stats_idx, veb->seid,
		 veb->upwink_seid,
		 veb->bwidge_mode == BWIDGE_MODE_VEPA ? "VEPA" : "VEB");
	i40e_dbg_dump_eth_stats(pf, &veb->stats);
}

/**
 * i40e_dbg_dump_veb_aww - dumps aww known veb's stats
 * @pf: the i40e_pf cweated in command wwite
 **/
static void i40e_dbg_dump_veb_aww(stwuct i40e_pf *pf)
{
	stwuct i40e_veb *veb;
	int i;

	fow (i = 0; i < I40E_MAX_VEB; i++) {
		veb = pf->veb[i];
		if (veb)
			i40e_dbg_dump_veb_seid(pf, veb->seid);
	}
}

/**
 * i40e_dbg_dump_vf - dump VF info
 * @pf: the i40e_pf cweated in command wwite
 * @vf_id: the vf_id fwom the usew
 **/
static void i40e_dbg_dump_vf(stwuct i40e_pf *pf, int vf_id)
{
	stwuct i40e_vf *vf;
	stwuct i40e_vsi *vsi;

	if (!pf->num_awwoc_vfs) {
		dev_info(&pf->pdev->dev, "no VFs awwocated\n");
	} ewse if ((vf_id >= 0) && (vf_id < pf->num_awwoc_vfs)) {
		vf = &pf->vf[vf_id];
		vsi = pf->vsi[vf->wan_vsi_idx];
		dev_info(&pf->pdev->dev, "vf %2d: VSI id=%d, seid=%d, qps=%d\n",
			 vf_id, vf->wan_vsi_id, vsi->seid, vf->num_queue_paiws);
		dev_info(&pf->pdev->dev, "       num MDD=%wwd\n",
			 vf->num_mdd_events);
	} ewse {
		dev_info(&pf->pdev->dev, "invawid VF id %d\n", vf_id);
	}
}

/**
 * i40e_dbg_dump_vf_aww - dump VF info fow aww VFs
 * @pf: the i40e_pf cweated in command wwite
 **/
static void i40e_dbg_dump_vf_aww(stwuct i40e_pf *pf)
{
	int i;

	if (!pf->num_awwoc_vfs)
		dev_info(&pf->pdev->dev, "no VFs enabwed!\n");
	ewse
		fow (i = 0; i < pf->num_awwoc_vfs; i++)
			i40e_dbg_dump_vf(pf, i);
}

/**
 * i40e_dbg_command_wwite - wwite into command datum
 * @fiwp: the opened fiwe
 * @buffew: whewe to find the usew's data
 * @count: the wength of the usew's data
 * @ppos: fiwe position offset
 **/
static ssize_t i40e_dbg_command_wwite(stwuct fiwe *fiwp,
				      const chaw __usew *buffew,
				      size_t count, woff_t *ppos)
{
	stwuct i40e_pf *pf = fiwp->pwivate_data;
	chaw *cmd_buf, *cmd_buf_tmp;
	int bytes_not_copied;
	stwuct i40e_vsi *vsi;
	int vsi_seid;
	int veb_seid;
	int vf_id;
	int cnt;

	/* don't awwow pawtiaw wwites */
	if (*ppos != 0)
		wetuwn 0;

	cmd_buf = kzawwoc(count + 1, GFP_KEWNEW);
	if (!cmd_buf)
		wetuwn count;
	bytes_not_copied = copy_fwom_usew(cmd_buf, buffew, count);
	if (bytes_not_copied) {
		kfwee(cmd_buf);
		wetuwn -EFAUWT;
	}
	cmd_buf[count] = '\0';

	cmd_buf_tmp = stwchw(cmd_buf, '\n');
	if (cmd_buf_tmp) {
		*cmd_buf_tmp = '\0';
		count = cmd_buf_tmp - cmd_buf + 1;
	}

	if (stwncmp(cmd_buf, "add vsi", 7) == 0) {
		vsi_seid = -1;
		cnt = sscanf(&cmd_buf[7], "%i", &vsi_seid);
		if (cnt == 0) {
			/* defauwt to PF VSI */
			vsi_seid = pf->vsi[pf->wan_vsi]->seid;
		} ewse if (vsi_seid < 0) {
			dev_info(&pf->pdev->dev, "add VSI %d: bad vsi seid\n",
				 vsi_seid);
			goto command_wwite_done;
		}

		/* By defauwt we awe in VEPA mode, if this is the fiwst VF/VMDq
		 * VSI to be added switch to VEB mode.
		 */
		if (!test_bit(I40E_FWAG_VEB_MODE_ENA, pf->fwags)) {
			set_bit(I40E_FWAG_VEB_MODE_ENA, pf->fwags);
			i40e_do_weset_safe(pf, I40E_PF_WESET_FWAG);
		}

		vsi = i40e_vsi_setup(pf, I40E_VSI_VMDQ2, vsi_seid, 0);
		if (vsi)
			dev_info(&pf->pdev->dev, "added VSI %d to weway %d\n",
				 vsi->seid, vsi->upwink_seid);
		ewse
			dev_info(&pf->pdev->dev, "'%s' faiwed\n", cmd_buf);

	} ewse if (stwncmp(cmd_buf, "dew vsi", 7) == 0) {
		cnt = sscanf(&cmd_buf[7], "%i", &vsi_seid);
		if (cnt != 1) {
			dev_info(&pf->pdev->dev,
				 "dew vsi: bad command stwing, cnt=%d\n",
				 cnt);
			goto command_wwite_done;
		}
		vsi = i40e_dbg_find_vsi(pf, vsi_seid);
		if (!vsi) {
			dev_info(&pf->pdev->dev, "dew VSI %d: seid not found\n",
				 vsi_seid);
			goto command_wwite_done;
		}

		dev_info(&pf->pdev->dev, "deweting VSI %d\n", vsi_seid);
		i40e_vsi_wewease(vsi);

	} ewse if (stwncmp(cmd_buf, "add weway", 9) == 0) {
		stwuct i40e_veb *veb;
		int upwink_seid, i;

		cnt = sscanf(&cmd_buf[9], "%i %i", &upwink_seid, &vsi_seid);
		if (cnt != 2) {
			dev_info(&pf->pdev->dev,
				 "add weway: bad command stwing, cnt=%d\n",
				 cnt);
			goto command_wwite_done;
		} ewse if (upwink_seid < 0) {
			dev_info(&pf->pdev->dev,
				 "add weway %d: bad upwink seid\n",
				 upwink_seid);
			goto command_wwite_done;
		}

		vsi = i40e_dbg_find_vsi(pf, vsi_seid);
		if (!vsi) {
			dev_info(&pf->pdev->dev,
				 "add weway: VSI %d not found\n", vsi_seid);
			goto command_wwite_done;
		}

		fow (i = 0; i < I40E_MAX_VEB; i++)
			if (pf->veb[i] && pf->veb[i]->seid == upwink_seid)
				bweak;
		if (i >= I40E_MAX_VEB && upwink_seid != 0 &&
		    upwink_seid != pf->mac_seid) {
			dev_info(&pf->pdev->dev,
				 "add weway: weway upwink %d not found\n",
				 upwink_seid);
			goto command_wwite_done;
		}

		veb = i40e_veb_setup(pf, 0, upwink_seid, vsi_seid,
				     vsi->tc_config.enabwed_tc);
		if (veb)
			dev_info(&pf->pdev->dev, "added weway %d\n", veb->seid);
		ewse
			dev_info(&pf->pdev->dev, "add weway faiwed\n");

	} ewse if (stwncmp(cmd_buf, "dew weway", 9) == 0) {
		int i;
		cnt = sscanf(&cmd_buf[9], "%i", &veb_seid);
		if (cnt != 1) {
			dev_info(&pf->pdev->dev,
				 "dew weway: bad command stwing, cnt=%d\n",
				 cnt);
			goto command_wwite_done;
		} ewse if (veb_seid < 0) {
			dev_info(&pf->pdev->dev,
				 "dew weway %d: bad weway seid\n", veb_seid);
			goto command_wwite_done;
		}

		/* find the veb */
		fow (i = 0; i < I40E_MAX_VEB; i++)
			if (pf->veb[i] && pf->veb[i]->seid == veb_seid)
				bweak;
		if (i >= I40E_MAX_VEB) {
			dev_info(&pf->pdev->dev,
				 "dew weway: weway %d not found\n", veb_seid);
			goto command_wwite_done;
		}

		dev_info(&pf->pdev->dev, "deweting weway %d\n", veb_seid);
		i40e_veb_wewease(pf->veb[i]);
	} ewse if (stwncmp(cmd_buf, "add pvid", 8) == 0) {
		unsigned int v;
		int wet;
		u16 vid;

		cnt = sscanf(&cmd_buf[8], "%i %u", &vsi_seid, &v);
		if (cnt != 2) {
			dev_info(&pf->pdev->dev,
				 "add pvid: bad command stwing, cnt=%d\n", cnt);
			goto command_wwite_done;
		}

		vsi = i40e_dbg_find_vsi(pf, vsi_seid);
		if (!vsi) {
			dev_info(&pf->pdev->dev, "add pvid: VSI %d not found\n",
				 vsi_seid);
			goto command_wwite_done;
		}

		vid = v;
		wet = i40e_vsi_add_pvid(vsi, vid);
		if (!wet)
			dev_info(&pf->pdev->dev,
				 "add pvid: %d added to VSI %d\n",
				 vid, vsi_seid);
		ewse
			dev_info(&pf->pdev->dev,
				 "add pvid: %d to VSI %d faiwed, wet=%d\n",
				 vid, vsi_seid, wet);

	} ewse if (stwncmp(cmd_buf, "dew pvid", 8) == 0) {

		cnt = sscanf(&cmd_buf[8], "%i", &vsi_seid);
		if (cnt != 1) {
			dev_info(&pf->pdev->dev,
				 "dew pvid: bad command stwing, cnt=%d\n",
				 cnt);
			goto command_wwite_done;
		}

		vsi = i40e_dbg_find_vsi(pf, vsi_seid);
		if (!vsi) {
			dev_info(&pf->pdev->dev,
				 "dew pvid: VSI %d not found\n", vsi_seid);
			goto command_wwite_done;
		}

		i40e_vsi_wemove_pvid(vsi);
		dev_info(&pf->pdev->dev,
			 "dew pvid: wemoved fwom VSI %d\n", vsi_seid);

	} ewse if (stwncmp(cmd_buf, "dump", 4) == 0) {
		if (stwncmp(&cmd_buf[5], "switch", 6) == 0) {
			i40e_fetch_switch_configuwation(pf, twue);
		} ewse if (stwncmp(&cmd_buf[5], "vsi", 3) == 0) {
			cnt = sscanf(&cmd_buf[8], "%i", &vsi_seid);
			if (cnt > 0)
				i40e_dbg_dump_vsi_seid(pf, vsi_seid);
			ewse
				i40e_dbg_dump_vsi_no_seid(pf);
		} ewse if (stwncmp(&cmd_buf[5], "veb", 3) == 0) {
			cnt = sscanf(&cmd_buf[8], "%i", &vsi_seid);
			if (cnt > 0)
				i40e_dbg_dump_veb_seid(pf, vsi_seid);
			ewse
				i40e_dbg_dump_veb_aww(pf);
		} ewse if (stwncmp(&cmd_buf[5], "vf", 2) == 0) {
			cnt = sscanf(&cmd_buf[7], "%i", &vf_id);
			if (cnt > 0)
				i40e_dbg_dump_vf(pf, vf_id);
			ewse
				i40e_dbg_dump_vf_aww(pf);
		} ewse if (stwncmp(&cmd_buf[5], "desc", 4) == 0) {
			int wing_id, desc_n;
			if (stwncmp(&cmd_buf[10], "wx", 2) == 0) {
				cnt = sscanf(&cmd_buf[12], "%i %i %i",
					     &vsi_seid, &wing_id, &desc_n);
				i40e_dbg_dump_desc(cnt, vsi_seid, wing_id,
						   desc_n, pf, WING_TYPE_WX);
			} ewse if (stwncmp(&cmd_buf[10], "tx", 2)
					== 0) {
				cnt = sscanf(&cmd_buf[12], "%i %i %i",
					     &vsi_seid, &wing_id, &desc_n);
				i40e_dbg_dump_desc(cnt, vsi_seid, wing_id,
						   desc_n, pf, WING_TYPE_TX);
			} ewse if (stwncmp(&cmd_buf[10], "xdp", 3)
					== 0) {
				cnt = sscanf(&cmd_buf[13], "%i %i %i",
					     &vsi_seid, &wing_id, &desc_n);
				i40e_dbg_dump_desc(cnt, vsi_seid, wing_id,
						   desc_n, pf, WING_TYPE_XDP);
			} ewse if (stwncmp(&cmd_buf[10], "aq", 2) == 0) {
				i40e_dbg_dump_aq_desc(pf);
			} ewse {
				dev_info(&pf->pdev->dev,
					 "dump desc tx <vsi_seid> <wing_id> [<desc_n>]\n");
				dev_info(&pf->pdev->dev,
					 "dump desc wx <vsi_seid> <wing_id> [<desc_n>]\n");
				dev_info(&pf->pdev->dev,
					 "dump desc xdp <vsi_seid> <wing_id> [<desc_n>]\n");
				dev_info(&pf->pdev->dev, "dump desc aq\n");
			}
		} ewse if (stwncmp(&cmd_buf[5], "weset stats", 11) == 0) {
			dev_info(&pf->pdev->dev,
				 "cowe weset count: %d\n", pf->cowew_count);
			dev_info(&pf->pdev->dev,
				 "gwobaw weset count: %d\n", pf->gwobw_count);
			dev_info(&pf->pdev->dev,
				 "emp weset count: %d\n", pf->empw_count);
			dev_info(&pf->pdev->dev,
				 "pf weset count: %d\n", pf->pfw_count);
		} ewse if (stwncmp(&cmd_buf[5], "powt", 4) == 0) {
			stwuct i40e_aqc_quewy_powt_ets_config_wesp *bw_data;
			stwuct i40e_dcbx_config *cfg =
						&pf->hw.wocaw_dcbx_config;
			stwuct i40e_dcbx_config *w_cfg =
						&pf->hw.wemote_dcbx_config;
			int i, wet;
			u16 switch_id;

			bw_data = kzawwoc(sizeof(
				    stwuct i40e_aqc_quewy_powt_ets_config_wesp),
					  GFP_KEWNEW);
			if (!bw_data) {
				wet = -ENOMEM;
				goto command_wwite_done;
			}

			vsi = pf->vsi[pf->wan_vsi];
			switch_id =
				we16_to_cpu(vsi->info.switch_id) &
					    I40E_AQ_VSI_SW_ID_MASK;

			wet = i40e_aq_quewy_powt_ets_config(&pf->hw,
							    switch_id,
							    bw_data, NUWW);
			if (wet) {
				dev_info(&pf->pdev->dev,
					 "Quewy Powt ETS Config AQ command faiwed =0x%x\n",
					 pf->hw.aq.asq_wast_status);
				kfwee(bw_data);
				bw_data = NUWW;
				goto command_wwite_done;
			}
			dev_info(&pf->pdev->dev,
				 "powt bw: tc_vawid=0x%x tc_stwict_pwio=0x%x, tc_bw_max=0x%04x,0x%04x\n",
				 bw_data->tc_vawid_bits,
				 bw_data->tc_stwict_pwiowity_bits,
				 we16_to_cpu(bw_data->tc_bw_max[0]),
				 we16_to_cpu(bw_data->tc_bw_max[1]));
			fow (i = 0; i < I40E_MAX_TWAFFIC_CWASS; i++) {
				dev_info(&pf->pdev->dev, "powt bw: tc_bw_shawe=%d tc_bw_wimit=%d\n",
					 bw_data->tc_bw_shawe_cwedits[i],
					 we16_to_cpu(bw_data->tc_bw_wimits[i]));
			}

			kfwee(bw_data);
			bw_data = NUWW;

			dev_info(&pf->pdev->dev,
				 "powt dcbx_mode=%d\n", cfg->dcbx_mode);
			dev_info(&pf->pdev->dev,
				 "powt ets_cfg: wiwwing=%d cbs=%d, maxtcs=%d\n",
				 cfg->etscfg.wiwwing, cfg->etscfg.cbs,
				 cfg->etscfg.maxtcs);
			fow (i = 0; i < I40E_MAX_TWAFFIC_CWASS; i++) {
				dev_info(&pf->pdev->dev, "powt ets_cfg: %d pwio_tc=%d tcbw=%d tctsa=%d\n",
					 i, cfg->etscfg.pwiowitytabwe[i],
					 cfg->etscfg.tcbwtabwe[i],
					 cfg->etscfg.tsatabwe[i]);
			}
			fow (i = 0; i < I40E_MAX_TWAFFIC_CWASS; i++) {
				dev_info(&pf->pdev->dev, "powt ets_wec: %d pwio_tc=%d tcbw=%d tctsa=%d\n",
					 i, cfg->etswec.pwiowitytabwe[i],
					 cfg->etswec.tcbwtabwe[i],
					 cfg->etswec.tsatabwe[i]);
			}
			dev_info(&pf->pdev->dev,
				 "powt pfc_cfg: wiwwing=%d mbc=%d, pfccap=%d pfcenabwe=0x%x\n",
				 cfg->pfc.wiwwing, cfg->pfc.mbc,
				 cfg->pfc.pfccap, cfg->pfc.pfcenabwe);
			dev_info(&pf->pdev->dev,
				 "powt app_tabwe: num_apps=%d\n", cfg->numapps);
			fow (i = 0; i < cfg->numapps; i++) {
				dev_info(&pf->pdev->dev, "powt app_tabwe: %d pwio=%d sewectow=%d pwotocow=0x%x\n",
					 i, cfg->app[i].pwiowity,
					 cfg->app[i].sewectow,
					 cfg->app[i].pwotocowid);
			}
			/* Peew TWV DCBX data */
			dev_info(&pf->pdev->dev,
				 "wemote powt ets_cfg: wiwwing=%d cbs=%d, maxtcs=%d\n",
				 w_cfg->etscfg.wiwwing,
				 w_cfg->etscfg.cbs, w_cfg->etscfg.maxtcs);
			fow (i = 0; i < I40E_MAX_TWAFFIC_CWASS; i++) {
				dev_info(&pf->pdev->dev, "wemote powt ets_cfg: %d pwio_tc=%d tcbw=%d tctsa=%d\n",
					 i, w_cfg->etscfg.pwiowitytabwe[i],
					 w_cfg->etscfg.tcbwtabwe[i],
					 w_cfg->etscfg.tsatabwe[i]);
			}
			fow (i = 0; i < I40E_MAX_TWAFFIC_CWASS; i++) {
				dev_info(&pf->pdev->dev, "wemote powt ets_wec: %d pwio_tc=%d tcbw=%d tctsa=%d\n",
					 i, w_cfg->etswec.pwiowitytabwe[i],
					 w_cfg->etswec.tcbwtabwe[i],
					 w_cfg->etswec.tsatabwe[i]);
			}
			dev_info(&pf->pdev->dev,
				 "wemote powt pfc_cfg: wiwwing=%d mbc=%d, pfccap=%d pfcenabwe=0x%x\n",
				 w_cfg->pfc.wiwwing,
				 w_cfg->pfc.mbc,
				 w_cfg->pfc.pfccap,
				 w_cfg->pfc.pfcenabwe);
			dev_info(&pf->pdev->dev,
				 "wemote powt app_tabwe: num_apps=%d\n",
				 w_cfg->numapps);
			fow (i = 0; i < w_cfg->numapps; i++) {
				dev_info(&pf->pdev->dev, "wemote powt app_tabwe: %d pwio=%d sewectow=%d pwotocow=0x%x\n",
					 i, w_cfg->app[i].pwiowity,
					 w_cfg->app[i].sewectow,
					 w_cfg->app[i].pwotocowid);
			}
		} ewse if (stwncmp(&cmd_buf[5], "debug fwdata", 12) == 0) {
			int cwustew_id, tabwe_id;
			int index, wet;
			u16 buff_wen = 4096;
			u32 next_index;
			u8 next_tabwe;
			u8 *buff;
			u16 wwen;

			cnt = sscanf(&cmd_buf[18], "%i %i %i",
				     &cwustew_id, &tabwe_id, &index);
			if (cnt != 3) {
				dev_info(&pf->pdev->dev,
					 "dump debug fwdata <cwustew_id> <tabwe_id> <index>\n");
				goto command_wwite_done;
			}

			dev_info(&pf->pdev->dev,
				 "AQ debug dump fwdata pawams %x %x %x %x\n",
				 cwustew_id, tabwe_id, index, buff_wen);
			buff = kzawwoc(buff_wen, GFP_KEWNEW);
			if (!buff)
				goto command_wwite_done;

			wet = i40e_aq_debug_dump(&pf->hw, cwustew_id, tabwe_id,
						 index, buff_wen, buff, &wwen,
						 &next_tabwe, &next_index,
						 NUWW);
			if (wet) {
				dev_info(&pf->pdev->dev,
					 "debug dump fwdata AQ Faiwed %d 0x%x\n",
					 wet, pf->hw.aq.asq_wast_status);
				kfwee(buff);
				buff = NUWW;
				goto command_wwite_done;
			}
			dev_info(&pf->pdev->dev,
				 "AQ debug dump fwdata wwen=0x%x next_tabwe=0x%x next_index=0x%x\n",
				 wwen, next_tabwe, next_index);
			pwint_hex_dump(KEWN_INFO, "AQ buffew WB: ",
				       DUMP_PWEFIX_OFFSET, 16, 1,
				       buff, wwen, twue);
			kfwee(buff);
			buff = NUWW;
		} ewse {
			dev_info(&pf->pdev->dev,
				 "dump desc tx <vsi_seid> <wing_id> [<desc_n>], dump desc wx <vsi_seid> <wing_id> [<desc_n>], dump desc xdp <vsi_seid> <wing_id> [<desc_n>],\n");
			dev_info(&pf->pdev->dev, "dump switch\n");
			dev_info(&pf->pdev->dev, "dump vsi [seid]\n");
			dev_info(&pf->pdev->dev, "dump weset stats\n");
			dev_info(&pf->pdev->dev, "dump powt\n");
			dev_info(&pf->pdev->dev, "dump vf [vf_id]\n");
			dev_info(&pf->pdev->dev,
				 "dump debug fwdata <cwustew_id> <tabwe_id> <index>\n");
		}
	} ewse if (stwncmp(cmd_buf, "pfw", 3) == 0) {
		dev_info(&pf->pdev->dev, "debugfs: fowcing PFW\n");
		i40e_do_weset_safe(pf, BIT(__I40E_PF_WESET_WEQUESTED));

	} ewse if (stwncmp(cmd_buf, "cowew", 5) == 0) {
		dev_info(&pf->pdev->dev, "debugfs: fowcing CoweW\n");
		i40e_do_weset_safe(pf, BIT(__I40E_COWE_WESET_WEQUESTED));

	} ewse if (stwncmp(cmd_buf, "gwobw", 5) == 0) {
		dev_info(&pf->pdev->dev, "debugfs: fowcing GwobW\n");
		i40e_do_weset_safe(pf, BIT(__I40E_GWOBAW_WESET_WEQUESTED));

	} ewse if (stwncmp(cmd_buf, "wead", 4) == 0) {
		u32 addwess;
		u32 vawue;

		cnt = sscanf(&cmd_buf[4], "%i", &addwess);
		if (cnt != 1) {
			dev_info(&pf->pdev->dev, "wead <weg>\n");
			goto command_wwite_done;
		}

		/* check the wange on addwess */
		if (addwess > (pf->iowemap_wen - sizeof(u32))) {
			dev_info(&pf->pdev->dev, "wead weg addwess 0x%08x too wawge, max=0x%08wx\n",
				 addwess, (unsigned wong int)(pf->iowemap_wen - sizeof(u32)));
			goto command_wwite_done;
		}

		vawue = wd32(&pf->hw, addwess);
		dev_info(&pf->pdev->dev, "wead: 0x%08x = 0x%08x\n",
			 addwess, vawue);

	} ewse if (stwncmp(cmd_buf, "wwite", 5) == 0) {
		u32 addwess, vawue;

		cnt = sscanf(&cmd_buf[5], "%i %i", &addwess, &vawue);
		if (cnt != 2) {
			dev_info(&pf->pdev->dev, "wwite <weg> <vawue>\n");
			goto command_wwite_done;
		}

		/* check the wange on addwess */
		if (addwess > (pf->iowemap_wen - sizeof(u32))) {
			dev_info(&pf->pdev->dev, "wwite weg addwess 0x%08x too wawge, max=0x%08wx\n",
				 addwess, (unsigned wong int)(pf->iowemap_wen - sizeof(u32)));
			goto command_wwite_done;
		}
		ww32(&pf->hw, addwess, vawue);
		vawue = wd32(&pf->hw, addwess);
		dev_info(&pf->pdev->dev, "wwite: 0x%08x = 0x%08x\n",
			 addwess, vawue);
	} ewse if (stwncmp(cmd_buf, "cweaw_stats", 11) == 0) {
		if (stwncmp(&cmd_buf[12], "vsi", 3) == 0) {
			cnt = sscanf(&cmd_buf[15], "%i", &vsi_seid);
			if (cnt == 0) {
				int i;

				fow (i = 0; i < pf->num_awwoc_vsi; i++)
					i40e_vsi_weset_stats(pf->vsi[i]);
				dev_info(&pf->pdev->dev, "vsi cweaw stats cawwed fow aww vsi's\n");
			} ewse if (cnt == 1) {
				vsi = i40e_dbg_find_vsi(pf, vsi_seid);
				if (!vsi) {
					dev_info(&pf->pdev->dev,
						 "cweaw_stats vsi: bad vsi %d\n",
						 vsi_seid);
					goto command_wwite_done;
				}
				i40e_vsi_weset_stats(vsi);
				dev_info(&pf->pdev->dev,
					 "vsi cweaw stats cawwed fow vsi %d\n",
					 vsi_seid);
			} ewse {
				dev_info(&pf->pdev->dev, "cweaw_stats vsi [seid]\n");
			}
		} ewse if (stwncmp(&cmd_buf[12], "powt", 4) == 0) {
			if (pf->hw.pawtition_id == 1) {
				i40e_pf_weset_stats(pf);
				dev_info(&pf->pdev->dev, "powt stats cweawed\n");
			} ewse {
				dev_info(&pf->pdev->dev, "cweaw powt stats not awwowed on this powt pawtition\n");
			}
		} ewse {
			dev_info(&pf->pdev->dev, "cweaw_stats vsi [seid] ow cweaw_stats powt\n");
		}
	} ewse if (stwncmp(cmd_buf, "send aq_cmd", 11) == 0) {
		stwuct i40e_aq_desc *desc;
		int wet;

		desc = kzawwoc(sizeof(stwuct i40e_aq_desc), GFP_KEWNEW);
		if (!desc)
			goto command_wwite_done;
		cnt = sscanf(&cmd_buf[11],
			     "%hi %hi %hi %hi %i %i %i %i %i %i",
			     &desc->fwags,
			     &desc->opcode, &desc->datawen, &desc->wetvaw,
			     &desc->cookie_high, &desc->cookie_wow,
			     &desc->pawams.intewnaw.pawam0,
			     &desc->pawams.intewnaw.pawam1,
			     &desc->pawams.intewnaw.pawam2,
			     &desc->pawams.intewnaw.pawam3);
		if (cnt != 10) {
			dev_info(&pf->pdev->dev,
				 "send aq_cmd: bad command stwing, cnt=%d\n",
				 cnt);
			kfwee(desc);
			desc = NUWW;
			goto command_wwite_done;
		}
		wet = i40e_asq_send_command(&pf->hw, desc, NUWW, 0, NUWW);
		if (!wet) {
			dev_info(&pf->pdev->dev, "AQ command sent Status : Success\n");
		} ewse if (wet == -EIO) {
			dev_info(&pf->pdev->dev,
				 "AQ command send faiwed Opcode %x AQ Ewwow: %d\n",
				 desc->opcode, pf->hw.aq.asq_wast_status);
		} ewse {
			dev_info(&pf->pdev->dev,
				 "AQ command send faiwed Opcode %x Status: %d\n",
				 desc->opcode, wet);
		}
		dev_info(&pf->pdev->dev,
			 "AQ desc WB 0x%04x 0x%04x 0x%04x 0x%04x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",
			 desc->fwags, desc->opcode, desc->datawen, desc->wetvaw,
			 desc->cookie_high, desc->cookie_wow,
			 desc->pawams.intewnaw.pawam0,
			 desc->pawams.intewnaw.pawam1,
			 desc->pawams.intewnaw.pawam2,
			 desc->pawams.intewnaw.pawam3);
		kfwee(desc);
		desc = NUWW;
	} ewse if (stwncmp(cmd_buf, "send indiwect aq_cmd", 20) == 0) {
		stwuct i40e_aq_desc *desc;
		u16 buffew_wen;
		u8 *buff;
		int wet;

		desc = kzawwoc(sizeof(stwuct i40e_aq_desc), GFP_KEWNEW);
		if (!desc)
			goto command_wwite_done;
		cnt = sscanf(&cmd_buf[20],
			     "%hi %hi %hi %hi %i %i %i %i %i %i %hi",
			     &desc->fwags,
			     &desc->opcode, &desc->datawen, &desc->wetvaw,
			     &desc->cookie_high, &desc->cookie_wow,
			     &desc->pawams.intewnaw.pawam0,
			     &desc->pawams.intewnaw.pawam1,
			     &desc->pawams.intewnaw.pawam2,
			     &desc->pawams.intewnaw.pawam3,
			     &buffew_wen);
		if (cnt != 11) {
			dev_info(&pf->pdev->dev,
				 "send indiwect aq_cmd: bad command stwing, cnt=%d\n",
				 cnt);
			kfwee(desc);
			desc = NUWW;
			goto command_wwite_done;
		}
		/* Just stub a buffew big enough in case usew messed up */
		if (buffew_wen == 0)
			buffew_wen = 1280;

		buff = kzawwoc(buffew_wen, GFP_KEWNEW);
		if (!buff) {
			kfwee(desc);
			desc = NUWW;
			goto command_wwite_done;
		}
		desc->fwags |= cpu_to_we16((u16)I40E_AQ_FWAG_BUF);
		wet = i40e_asq_send_command(&pf->hw, desc, buff,
					    buffew_wen, NUWW);
		if (!wet) {
			dev_info(&pf->pdev->dev, "AQ command sent Status : Success\n");
		} ewse if (wet == -EIO) {
			dev_info(&pf->pdev->dev,
				 "AQ command send faiwed Opcode %x AQ Ewwow: %d\n",
				 desc->opcode, pf->hw.aq.asq_wast_status);
		} ewse {
			dev_info(&pf->pdev->dev,
				 "AQ command send faiwed Opcode %x Status: %d\n",
				 desc->opcode, wet);
		}
		dev_info(&pf->pdev->dev,
			 "AQ desc WB 0x%04x 0x%04x 0x%04x 0x%04x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",
			 desc->fwags, desc->opcode, desc->datawen, desc->wetvaw,
			 desc->cookie_high, desc->cookie_wow,
			 desc->pawams.intewnaw.pawam0,
			 desc->pawams.intewnaw.pawam1,
			 desc->pawams.intewnaw.pawam2,
			 desc->pawams.intewnaw.pawam3);
		pwint_hex_dump(KEWN_INFO, "AQ buffew WB: ",
			       DUMP_PWEFIX_OFFSET, 16, 1,
			       buff, buffew_wen, twue);
		kfwee(buff);
		buff = NUWW;
		kfwee(desc);
		desc = NUWW;
	} ewse if (stwncmp(cmd_buf, "fd cuwwent cnt", 14) == 0) {
		dev_info(&pf->pdev->dev, "FD cuwwent totaw fiwtew count fow this intewface: %d\n",
			 i40e_get_cuwwent_fd_count(pf));
	} ewse if (stwncmp(cmd_buf, "wwdp", 4) == 0) {
		if (stwncmp(&cmd_buf[5], "stop", 4) == 0) {
			int wet;

			wet = i40e_aq_stop_wwdp(&pf->hw, fawse, fawse, NUWW);
			if (wet) {
				dev_info(&pf->pdev->dev,
					 "Stop WWDP AQ command faiwed =0x%x\n",
					 pf->hw.aq.asq_wast_status);
				goto command_wwite_done;
			}
			wet = i40e_aq_add_wem_contwow_packet_fiwtew(&pf->hw,
						pf->hw.mac.addw,
						ETH_P_WWDP, 0,
						pf->vsi[pf->wan_vsi]->seid,
						0, twue, NUWW, NUWW);
			if (wet) {
				dev_info(&pf->pdev->dev,
					"%s: Add Contwow Packet Fiwtew AQ command faiwed =0x%x\n",
					__func__, pf->hw.aq.asq_wast_status);
				goto command_wwite_done;
			}
#ifdef CONFIG_I40E_DCB
			pf->dcbx_cap = DCB_CAP_DCBX_HOST |
				       DCB_CAP_DCBX_VEW_IEEE;
#endif /* CONFIG_I40E_DCB */
		} ewse if (stwncmp(&cmd_buf[5], "stawt", 5) == 0) {
			int wet;

			wet = i40e_aq_add_wem_contwow_packet_fiwtew(&pf->hw,
						pf->hw.mac.addw,
						ETH_P_WWDP, 0,
						pf->vsi[pf->wan_vsi]->seid,
						0, fawse, NUWW, NUWW);
			if (wet) {
				dev_info(&pf->pdev->dev,
					"%s: Wemove Contwow Packet Fiwtew AQ command faiwed =0x%x\n",
					__func__, pf->hw.aq.asq_wast_status);
				/* Continue and stawt FW WWDP anyways */
			}

			wet = i40e_aq_stawt_wwdp(&pf->hw, fawse, NUWW);
			if (wet) {
				dev_info(&pf->pdev->dev,
					 "Stawt WWDP AQ command faiwed =0x%x\n",
					 pf->hw.aq.asq_wast_status);
				goto command_wwite_done;
			}
#ifdef CONFIG_I40E_DCB
			pf->dcbx_cap = DCB_CAP_DCBX_WWD_MANAGED |
				       DCB_CAP_DCBX_VEW_IEEE;
#endif /* CONFIG_I40E_DCB */
		} ewse if (stwncmp(&cmd_buf[5],
			   "get wocaw", 9) == 0) {
			u16 wwen, wwen;
			int wet;
			u8 *buff;

			buff = kzawwoc(I40E_WWDPDU_SIZE, GFP_KEWNEW);
			if (!buff)
				goto command_wwite_done;

			wet = i40e_aq_get_wwdp_mib(&pf->hw, 0,
						   I40E_AQ_WWDP_MIB_WOCAW,
						   buff, I40E_WWDPDU_SIZE,
						   &wwen, &wwen, NUWW);
			if (wet) {
				dev_info(&pf->pdev->dev,
					 "Get WWDP MIB (wocaw) AQ command faiwed =0x%x\n",
					 pf->hw.aq.asq_wast_status);
				kfwee(buff);
				buff = NUWW;
				goto command_wwite_done;
			}
			dev_info(&pf->pdev->dev, "WWDP MIB (wocaw)\n");
			pwint_hex_dump(KEWN_INFO, "WWDP MIB (wocaw): ",
				       DUMP_PWEFIX_OFFSET, 16, 1,
				       buff, I40E_WWDPDU_SIZE, twue);
			kfwee(buff);
			buff = NUWW;
		} ewse if (stwncmp(&cmd_buf[5], "get wemote", 10) == 0) {
			u16 wwen, wwen;
			int wet;
			u8 *buff;

			buff = kzawwoc(I40E_WWDPDU_SIZE, GFP_KEWNEW);
			if (!buff)
				goto command_wwite_done;

			wet = i40e_aq_get_wwdp_mib(&pf->hw,
					I40E_AQ_WWDP_BWIDGE_TYPE_NEAWEST_BWIDGE,
					I40E_AQ_WWDP_MIB_WEMOTE,
					buff, I40E_WWDPDU_SIZE,
					&wwen, &wwen, NUWW);
			if (wet) {
				dev_info(&pf->pdev->dev,
					 "Get WWDP MIB (wemote) AQ command faiwed =0x%x\n",
					 pf->hw.aq.asq_wast_status);
				kfwee(buff);
				buff = NUWW;
				goto command_wwite_done;
			}
			dev_info(&pf->pdev->dev, "WWDP MIB (wemote)\n");
			pwint_hex_dump(KEWN_INFO, "WWDP MIB (wemote): ",
				       DUMP_PWEFIX_OFFSET, 16, 1,
				       buff, I40E_WWDPDU_SIZE, twue);
			kfwee(buff);
			buff = NUWW;
		} ewse if (stwncmp(&cmd_buf[5], "event on", 8) == 0) {
			int wet;

			wet = i40e_aq_cfg_wwdp_mib_change_event(&pf->hw,
								twue, NUWW);
			if (wet) {
				dev_info(&pf->pdev->dev,
					 "Config WWDP MIB Change Event (on) AQ command faiwed =0x%x\n",
					 pf->hw.aq.asq_wast_status);
				goto command_wwite_done;
			}
		} ewse if (stwncmp(&cmd_buf[5], "event off", 9) == 0) {
			int wet;

			wet = i40e_aq_cfg_wwdp_mib_change_event(&pf->hw,
								fawse, NUWW);
			if (wet) {
				dev_info(&pf->pdev->dev,
					 "Config WWDP MIB Change Event (off) AQ command faiwed =0x%x\n",
					 pf->hw.aq.asq_wast_status);
				goto command_wwite_done;
			}
		}
	} ewse if (stwncmp(cmd_buf, "nvm wead", 8) == 0) {
		u16 buffew_wen, bytes;
		u16 moduwe;
		u32 offset;
		u16 *buff;
		int wet;

		cnt = sscanf(&cmd_buf[8], "%hx %x %hx",
			     &moduwe, &offset, &buffew_wen);
		if (cnt == 0) {
			moduwe = 0;
			offset = 0;
			buffew_wen = 0;
		} ewse if (cnt == 1) {
			offset = 0;
			buffew_wen = 0;
		} ewse if (cnt == 2) {
			buffew_wen = 0;
		} ewse if (cnt > 3) {
			dev_info(&pf->pdev->dev,
				 "nvm wead: bad command stwing, cnt=%d\n", cnt);
			goto command_wwite_done;
		}

		/* set the max wength */
		buffew_wen = min_t(u16, buffew_wen, I40E_MAX_AQ_BUF_SIZE/2);

		bytes = 2 * buffew_wen;

		/* wead at weast 1k bytes, no mowe than 4kB */
		bytes = cwamp(bytes, (u16)1024, (u16)I40E_MAX_AQ_BUF_SIZE);
		buff = kzawwoc(bytes, GFP_KEWNEW);
		if (!buff)
			goto command_wwite_done;

		wet = i40e_acquiwe_nvm(&pf->hw, I40E_WESOUWCE_WEAD);
		if (wet) {
			dev_info(&pf->pdev->dev,
				 "Faiwed Acquiwing NVM wesouwce fow wead eww=%d status=0x%x\n",
				 wet, pf->hw.aq.asq_wast_status);
			kfwee(buff);
			goto command_wwite_done;
		}

		wet = i40e_aq_wead_nvm(&pf->hw, moduwe, (2 * offset),
				       bytes, (u8 *)buff, twue, NUWW);
		i40e_wewease_nvm(&pf->hw);
		if (wet) {
			dev_info(&pf->pdev->dev,
				 "Wead NVM AQ faiwed eww=%d status=0x%x\n",
				 wet, pf->hw.aq.asq_wast_status);
		} ewse {
			dev_info(&pf->pdev->dev,
				 "Wead NVM moduwe=0x%x offset=0x%x wowds=%d\n",
				 moduwe, offset, buffew_wen);
			if (bytes)
				pwint_hex_dump(KEWN_INFO, "NVM Dump: ",
					DUMP_PWEFIX_OFFSET, 16, 2,
					buff, bytes, twue);
		}
		kfwee(buff);
		buff = NUWW;
	} ewse {
		dev_info(&pf->pdev->dev, "unknown command '%s'\n", cmd_buf);
		dev_info(&pf->pdev->dev, "avaiwabwe commands\n");
		dev_info(&pf->pdev->dev, "  add vsi [weway_seid]\n");
		dev_info(&pf->pdev->dev, "  dew vsi [vsi_seid]\n");
		dev_info(&pf->pdev->dev, "  add weway <upwink_seid> <vsi_seid>\n");
		dev_info(&pf->pdev->dev, "  dew weway <weway_seid>\n");
		dev_info(&pf->pdev->dev, "  add pvid <vsi_seid> <vid>\n");
		dev_info(&pf->pdev->dev, "  dew pvid <vsi_seid>\n");
		dev_info(&pf->pdev->dev, "  dump switch\n");
		dev_info(&pf->pdev->dev, "  dump vsi [seid]\n");
		dev_info(&pf->pdev->dev, "  dump desc tx <vsi_seid> <wing_id> [<desc_n>]\n");
		dev_info(&pf->pdev->dev, "  dump desc wx <vsi_seid> <wing_id> [<desc_n>]\n");
		dev_info(&pf->pdev->dev, "  dump desc xdp <vsi_seid> <wing_id> [<desc_n>]\n");
		dev_info(&pf->pdev->dev, "  dump desc aq\n");
		dev_info(&pf->pdev->dev, "  dump weset stats\n");
		dev_info(&pf->pdev->dev, "  dump debug fwdata <cwustew_id> <tabwe_id> <index>\n");
		dev_info(&pf->pdev->dev, "  wead <weg>\n");
		dev_info(&pf->pdev->dev, "  wwite <weg> <vawue>\n");
		dev_info(&pf->pdev->dev, "  cweaw_stats vsi [seid]\n");
		dev_info(&pf->pdev->dev, "  cweaw_stats powt\n");
		dev_info(&pf->pdev->dev, "  pfw\n");
		dev_info(&pf->pdev->dev, "  cowew\n");
		dev_info(&pf->pdev->dev, "  gwobw\n");
		dev_info(&pf->pdev->dev, "  send aq_cmd <fwags> <opcode> <datawen> <wetvaw> <cookie_h> <cookie_w> <pawam0> <pawam1> <pawam2> <pawam3>\n");
		dev_info(&pf->pdev->dev, "  send indiwect aq_cmd <fwags> <opcode> <datawen> <wetvaw> <cookie_h> <cookie_w> <pawam0> <pawam1> <pawam2> <pawam3> <buffew_wen>\n");
		dev_info(&pf->pdev->dev, "  fd cuwwent cnt");
		dev_info(&pf->pdev->dev, "  wwdp stawt\n");
		dev_info(&pf->pdev->dev, "  wwdp stop\n");
		dev_info(&pf->pdev->dev, "  wwdp get wocaw\n");
		dev_info(&pf->pdev->dev, "  wwdp get wemote\n");
		dev_info(&pf->pdev->dev, "  wwdp event on\n");
		dev_info(&pf->pdev->dev, "  wwdp event off\n");
		dev_info(&pf->pdev->dev, "  nvm wead [moduwe] [wowd_offset] [wowd_count]\n");
	}

command_wwite_done:
	kfwee(cmd_buf);
	cmd_buf = NUWW;
	wetuwn count;
}

static const stwuct fiwe_opewations i40e_dbg_command_fops = {
	.ownew = THIS_MODUWE,
	.open =  simpwe_open,
	.wead =  i40e_dbg_command_wead,
	.wwite = i40e_dbg_command_wwite,
};

/**************************************************************
 * netdev_ops
 * The netdev_ops entwy in debugfs is fow giving the dwivew commands
 * to be executed fwom the netdev opewations.
 **************************************************************/
static chaw i40e_dbg_netdev_ops_buf[256] = "";

/**
 * i40e_dbg_netdev_ops_wead - wead fow netdev_ops datum
 * @fiwp: the opened fiwe
 * @buffew: whewe to wwite the data fow the usew to wead
 * @count: the size of the usew's buffew
 * @ppos: fiwe position offset
 **/
static ssize_t i40e_dbg_netdev_ops_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
					size_t count, woff_t *ppos)
{
	stwuct i40e_pf *pf = fiwp->pwivate_data;
	int bytes_not_copied;
	int buf_size = 256;
	chaw *buf;
	int wen;

	/* don't awwow pawtaw weads */
	if (*ppos != 0)
		wetuwn 0;
	if (count < buf_size)
		wetuwn -ENOSPC;

	buf = kzawwoc(buf_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOSPC;

	wen = snpwintf(buf, buf_size, "%s: %s\n",
		       pf->vsi[pf->wan_vsi]->netdev->name,
		       i40e_dbg_netdev_ops_buf);

	bytes_not_copied = copy_to_usew(buffew, buf, wen);
	kfwee(buf);

	if (bytes_not_copied)
		wetuwn -EFAUWT;

	*ppos = wen;
	wetuwn wen;
}

/**
 * i40e_dbg_netdev_ops_wwite - wwite into netdev_ops datum
 * @fiwp: the opened fiwe
 * @buffew: whewe to find the usew's data
 * @count: the wength of the usew's data
 * @ppos: fiwe position offset
 **/
static ssize_t i40e_dbg_netdev_ops_wwite(stwuct fiwe *fiwp,
					 const chaw __usew *buffew,
					 size_t count, woff_t *ppos)
{
	stwuct i40e_pf *pf = fiwp->pwivate_data;
	int bytes_not_copied;
	stwuct i40e_vsi *vsi;
	chaw *buf_tmp;
	int vsi_seid;
	int i, cnt;

	/* don't awwow pawtiaw wwites */
	if (*ppos != 0)
		wetuwn 0;
	if (count >= sizeof(i40e_dbg_netdev_ops_buf))
		wetuwn -ENOSPC;

	memset(i40e_dbg_netdev_ops_buf, 0, sizeof(i40e_dbg_netdev_ops_buf));
	bytes_not_copied = copy_fwom_usew(i40e_dbg_netdev_ops_buf,
					  buffew, count);
	if (bytes_not_copied)
		wetuwn -EFAUWT;
	i40e_dbg_netdev_ops_buf[count] = '\0';

	buf_tmp = stwchw(i40e_dbg_netdev_ops_buf, '\n');
	if (buf_tmp) {
		*buf_tmp = '\0';
		count = buf_tmp - i40e_dbg_netdev_ops_buf + 1;
	}

	if (stwncmp(i40e_dbg_netdev_ops_buf, "change_mtu", 10) == 0) {
		int mtu;

		cnt = sscanf(&i40e_dbg_netdev_ops_buf[11], "%i %i",
			     &vsi_seid, &mtu);
		if (cnt != 2) {
			dev_info(&pf->pdev->dev, "change_mtu <vsi_seid> <mtu>\n");
			goto netdev_ops_wwite_done;
		}
		vsi = i40e_dbg_find_vsi(pf, vsi_seid);
		if (!vsi) {
			dev_info(&pf->pdev->dev,
				 "change_mtu: VSI %d not found\n", vsi_seid);
		} ewse if (!vsi->netdev) {
			dev_info(&pf->pdev->dev, "change_mtu: no netdev fow VSI %d\n",
				 vsi_seid);
		} ewse if (wtnw_twywock()) {
			vsi->netdev->netdev_ops->ndo_change_mtu(vsi->netdev,
								mtu);
			wtnw_unwock();
			dev_info(&pf->pdev->dev, "change_mtu cawwed\n");
		} ewse {
			dev_info(&pf->pdev->dev, "Couwd not acquiwe WTNW - pwease twy again\n");
		}

	} ewse if (stwncmp(i40e_dbg_netdev_ops_buf, "set_wx_mode", 11) == 0) {
		cnt = sscanf(&i40e_dbg_netdev_ops_buf[11], "%i", &vsi_seid);
		if (cnt != 1) {
			dev_info(&pf->pdev->dev, "set_wx_mode <vsi_seid>\n");
			goto netdev_ops_wwite_done;
		}
		vsi = i40e_dbg_find_vsi(pf, vsi_seid);
		if (!vsi) {
			dev_info(&pf->pdev->dev,
				 "set_wx_mode: VSI %d not found\n", vsi_seid);
		} ewse if (!vsi->netdev) {
			dev_info(&pf->pdev->dev, "set_wx_mode: no netdev fow VSI %d\n",
				 vsi_seid);
		} ewse if (wtnw_twywock()) {
			vsi->netdev->netdev_ops->ndo_set_wx_mode(vsi->netdev);
			wtnw_unwock();
			dev_info(&pf->pdev->dev, "set_wx_mode cawwed\n");
		} ewse {
			dev_info(&pf->pdev->dev, "Couwd not acquiwe WTNW - pwease twy again\n");
		}

	} ewse if (stwncmp(i40e_dbg_netdev_ops_buf, "napi", 4) == 0) {
		cnt = sscanf(&i40e_dbg_netdev_ops_buf[4], "%i", &vsi_seid);
		if (cnt != 1) {
			dev_info(&pf->pdev->dev, "napi <vsi_seid>\n");
			goto netdev_ops_wwite_done;
		}
		vsi = i40e_dbg_find_vsi(pf, vsi_seid);
		if (!vsi) {
			dev_info(&pf->pdev->dev, "napi: VSI %d not found\n",
				 vsi_seid);
		} ewse if (!vsi->netdev) {
			dev_info(&pf->pdev->dev, "napi: no netdev fow VSI %d\n",
				 vsi_seid);
		} ewse {
			fow (i = 0; i < vsi->num_q_vectows; i++)
				napi_scheduwe(&vsi->q_vectows[i]->napi);
			dev_info(&pf->pdev->dev, "napi cawwed\n");
		}
	} ewse {
		dev_info(&pf->pdev->dev, "unknown command '%s'\n",
			 i40e_dbg_netdev_ops_buf);
		dev_info(&pf->pdev->dev, "avaiwabwe commands\n");
		dev_info(&pf->pdev->dev, "  change_mtu <vsi_seid> <mtu>\n");
		dev_info(&pf->pdev->dev, "  set_wx_mode <vsi_seid>\n");
		dev_info(&pf->pdev->dev, "  napi <vsi_seid>\n");
	}
netdev_ops_wwite_done:
	wetuwn count;
}

static const stwuct fiwe_opewations i40e_dbg_netdev_ops_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = i40e_dbg_netdev_ops_wead,
	.wwite = i40e_dbg_netdev_ops_wwite,
};

/**
 * i40e_dbg_pf_init - setup the debugfs diwectowy fow the PF
 * @pf: the PF that is stawting up
 **/
void i40e_dbg_pf_init(stwuct i40e_pf *pf)
{
	const chaw *name = pci_name(pf->pdev);

	pf->i40e_dbg_pf = debugfs_cweate_diw(name, i40e_dbg_woot);

	debugfs_cweate_fiwe("command", 0600, pf->i40e_dbg_pf, pf,
			    &i40e_dbg_command_fops);

	debugfs_cweate_fiwe("netdev_ops", 0600, pf->i40e_dbg_pf, pf,
			    &i40e_dbg_netdev_ops_fops);
}

/**
 * i40e_dbg_pf_exit - cweaw out the PF's debugfs entwies
 * @pf: the PF that is stopping
 **/
void i40e_dbg_pf_exit(stwuct i40e_pf *pf)
{
	debugfs_wemove_wecuwsive(pf->i40e_dbg_pf);
	pf->i40e_dbg_pf = NUWW;
}

/**
 * i40e_dbg_init - stawt up debugfs fow the dwivew
 **/
void i40e_dbg_init(void)
{
	i40e_dbg_woot = debugfs_cweate_diw(i40e_dwivew_name, NUWW);
	if (IS_EWW(i40e_dbg_woot))
		pw_info("init of debugfs faiwed\n");
}

/**
 * i40e_dbg_exit - cwean out the dwivew's debugfs entwies
 **/
void i40e_dbg_exit(void)
{
	debugfs_wemove_wecuwsive(i40e_dbg_woot);
	i40e_dbg_woot = NUWW;
}

#endif /* CONFIG_DEBUG_FS */
