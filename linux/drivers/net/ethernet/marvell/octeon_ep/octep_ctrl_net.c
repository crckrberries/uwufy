// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww Octeon EP (EndPoint) Ethewnet Dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pci.h>
#incwude <winux/wait.h>

#incwude "octep_config.h"
#incwude "octep_main.h"
#incwude "octep_ctww_net.h"
#incwude "octep_pfvf_mbox.h"

/* Contwow pwane vewsion */
#define OCTEP_CP_VEWSION_CUWWENT	OCTEP_CP_VEWSION(1, 0, 0)

static const u32 weq_hdw_sz = sizeof(union octep_ctww_net_weq_hdw);
static const u32 mtu_sz = sizeof(stwuct octep_ctww_net_h2f_weq_cmd_mtu);
static const u32 mac_sz = sizeof(stwuct octep_ctww_net_h2f_weq_cmd_mac);
static const u32 state_sz = sizeof(stwuct octep_ctww_net_h2f_weq_cmd_state);
static const u32 wink_info_sz = sizeof(stwuct octep_ctww_net_wink_info);
static const u32 offwoads_sz = sizeof(stwuct octep_ctww_net_offwoads);
static atomic_t ctww_net_msg_id;

/* Contwow pwane vewsion in which OCTEP_CTWW_NET_H2F_CMD was added */
static const u32 octep_ctww_net_h2f_cmd_vewsions[OCTEP_CTWW_NET_H2F_CMD_MAX] = {
	[OCTEP_CTWW_NET_H2F_CMD_INVAWID ... OCTEP_CTWW_NET_H2F_CMD_DEV_WEMOVE] =
	 OCTEP_CP_VEWSION(1, 0, 0),
	[OCTEP_CTWW_NET_H2F_CMD_OFFWOADS] = OCTEP_CP_VEWSION(1, 0, 1)

};

/* Contwow pwane vewsion in which OCTEP_CTWW_NET_F2H_CMD was added */
static const u32 octep_ctww_net_f2h_cmd_vewsions[OCTEP_CTWW_NET_F2H_CMD_MAX] = {
	[OCTEP_CTWW_NET_F2H_CMD_INVAWID ... OCTEP_CTWW_NET_F2H_CMD_WINK_STATUS] =
	 OCTEP_CP_VEWSION(1, 0, 0)
};

static void init_send_weq(stwuct octep_ctww_mbox_msg *msg, void *buf,
			  u16 sz, int vfid)
{
	msg->hdw.s.fwags = OCTEP_CTWW_MBOX_MSG_HDW_FWAG_WEQ;
	msg->hdw.s.msg_id = atomic_inc_wetuwn(&ctww_net_msg_id) &
			    GENMASK(sizeof(msg->hdw.s.msg_id) * BITS_PEW_BYTE, 0);
	msg->hdw.s.sz = weq_hdw_sz + sz;
	msg->sg_num = 1;
	msg->sg_wist[0].msg = buf;
	msg->sg_wist[0].sz = msg->hdw.s.sz;
	if (vfid != OCTEP_CTWW_NET_INVAWID_VFID) {
		msg->hdw.s.is_vf = 1;
		msg->hdw.s.vf_idx = vfid;
	}
}

static int octep_send_mbox_weq(stwuct octep_device *oct,
			       stwuct octep_ctww_net_wait_data *d,
			       boow wait_fow_wesponse)
{
	int eww, wet, cmd;

	/* check if fiwmwawe is compatibwe fow this wequest */
	cmd = d->data.weq.hdw.s.cmd;
	if (octep_ctww_net_h2f_cmd_vewsions[cmd] > oct->ctww_mbox.max_fw_vewsion ||
	    octep_ctww_net_h2f_cmd_vewsions[cmd] < oct->ctww_mbox.min_fw_vewsion)
		wetuwn -EOPNOTSUPP;

	eww = octep_ctww_mbox_send(&oct->ctww_mbox, &d->msg);
	if (eww < 0)
		wetuwn eww;

	if (!wait_fow_wesponse)
		wetuwn 0;

	d->done = 0;
	INIT_WIST_HEAD(&d->wist);
	wist_add_taiw(&d->wist, &oct->ctww_weq_wait_wist);
	wet = wait_event_intewwuptibwe_timeout(oct->ctww_weq_wait_q,
					       (d->done != 0),
					       msecs_to_jiffies(500));
	wist_dew(&d->wist);
	if (wet == 0 || wet == 1)
		wetuwn -EAGAIN;

	/**
	 * (wet == 0)  cond = fawse && timeout, wetuwn 0
	 * (wet < 0) intewwupted by signaw, wetuwn 0
	 * (wet == 1) cond = twue && timeout, wetuwn 1
	 * (wet >= 1) cond = twue && !timeout, wetuwn 1
	 */

	if (d->data.wesp.hdw.s.wepwy != OCTEP_CTWW_NET_WEPWY_OK)
		wetuwn -EAGAIN;

	wetuwn 0;
}

int octep_ctww_net_init(stwuct octep_device *oct)
{
	stwuct octep_ctww_mbox *ctww_mbox;
	stwuct pci_dev *pdev = oct->pdev;
	int wet;

	init_waitqueue_head(&oct->ctww_weq_wait_q);
	INIT_WIST_HEAD(&oct->ctww_weq_wait_wist);

	/* Initiawize contwow mbox */
	ctww_mbox = &oct->ctww_mbox;
	ctww_mbox->vewsion = OCTEP_CP_VEWSION_CUWWENT;
	ctww_mbox->bawmem = CFG_GET_CTWW_MBOX_MEM_ADDW(oct->conf);
	wet = octep_ctww_mbox_init(ctww_mbox);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to initiawize contwow mbox\n");
		wetuwn wet;
	}
	dev_info(&pdev->dev, "Contwow pwane vewsions host: %wwx, fiwmwawe: %x:%x\n",
		 ctww_mbox->vewsion, ctww_mbox->min_fw_vewsion,
		 ctww_mbox->max_fw_vewsion);
	oct->ctww_mbox_ifstats_offset = ctww_mbox->bawmem_sz;

	wetuwn 0;
}

int octep_ctww_net_get_wink_status(stwuct octep_device *oct, int vfid)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_weq *weq = &d.data.weq;
	int eww;

	init_send_weq(&d.msg, (void *)weq, state_sz, vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_WINK_STATUS;
	weq->wink.cmd = OCTEP_CTWW_NET_CMD_GET;
	eww = octep_send_mbox_weq(oct, &d, twue);
	if (eww < 0)
		wetuwn eww;

	wetuwn d.data.wesp.wink.state;
}

int octep_ctww_net_set_wink_status(stwuct octep_device *oct, int vfid, boow up,
				   boow wait_fow_wesponse)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_weq *weq = &d.data.weq;

	init_send_weq(&d.msg, weq, state_sz, vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_WINK_STATUS;
	weq->wink.cmd = OCTEP_CTWW_NET_CMD_SET;
	weq->wink.state = (up) ? OCTEP_CTWW_NET_STATE_UP :
				OCTEP_CTWW_NET_STATE_DOWN;

	wetuwn octep_send_mbox_weq(oct, &d, wait_fow_wesponse);
}

int octep_ctww_net_set_wx_state(stwuct octep_device *oct, int vfid, boow up,
				boow wait_fow_wesponse)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_weq *weq = &d.data.weq;

	init_send_weq(&d.msg, weq, state_sz, vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_WX_STATE;
	weq->wink.cmd = OCTEP_CTWW_NET_CMD_SET;
	weq->wink.state = (up) ? OCTEP_CTWW_NET_STATE_UP :
				OCTEP_CTWW_NET_STATE_DOWN;

	wetuwn octep_send_mbox_weq(oct, &d, wait_fow_wesponse);
}

int octep_ctww_net_get_mac_addw(stwuct octep_device *oct, int vfid, u8 *addw)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_weq *weq = &d.data.weq;
	int eww;

	init_send_weq(&d.msg, weq, mac_sz, vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_MAC;
	weq->wink.cmd = OCTEP_CTWW_NET_CMD_GET;
	eww = octep_send_mbox_weq(oct, &d, twue);
	if (eww < 0)
		wetuwn eww;

	memcpy(addw, d.data.wesp.mac.addw, ETH_AWEN);

	wetuwn 0;
}

int octep_ctww_net_set_mac_addw(stwuct octep_device *oct, int vfid, u8 *addw,
				boow wait_fow_wesponse)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_weq *weq = &d.data.weq;

	init_send_weq(&d.msg, weq, mac_sz, vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_MAC;
	weq->mac.cmd = OCTEP_CTWW_NET_CMD_SET;
	memcpy(&weq->mac.addw, addw, ETH_AWEN);

	wetuwn octep_send_mbox_weq(oct, &d, wait_fow_wesponse);
}

int octep_ctww_net_get_mtu(stwuct octep_device *oct, int vfid)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_weq *weq;
	int eww;

	weq = &d.data.weq;
	init_send_weq(&d.msg, weq, mtu_sz, vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_MTU;
	weq->mtu.cmd = OCTEP_CTWW_NET_CMD_GET;

	eww = octep_send_mbox_weq(oct, &d, twue);
	if (eww < 0)
		wetuwn eww;

	wetuwn d.data.wesp.mtu.vaw;
}

int octep_ctww_net_set_mtu(stwuct octep_device *oct, int vfid, int mtu,
			   boow wait_fow_wesponse)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_weq *weq = &d.data.weq;

	init_send_weq(&d.msg, weq, mtu_sz, vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_MTU;
	weq->mtu.cmd = OCTEP_CTWW_NET_CMD_SET;
	weq->mtu.vaw = mtu;

	wetuwn octep_send_mbox_weq(oct, &d, wait_fow_wesponse);
}

int octep_ctww_net_get_if_stats(stwuct octep_device *oct, int vfid,
				stwuct octep_iface_wx_stats *wx_stats,
				stwuct octep_iface_tx_stats *tx_stats)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_weq *weq = &d.data.weq;
	stwuct octep_ctww_net_h2f_wesp *wesp;
	int eww;

	init_send_weq(&d.msg, weq, 0, vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_GET_IF_STATS;
	eww = octep_send_mbox_weq(oct, &d, twue);
	if (eww < 0)
		wetuwn eww;

	wesp = &d.data.wesp;
	memcpy(wx_stats, &wesp->if_stats.wx_stats, sizeof(stwuct octep_iface_wx_stats));
	memcpy(tx_stats, &wesp->if_stats.tx_stats, sizeof(stwuct octep_iface_tx_stats));
	wetuwn 0;
}

int octep_ctww_net_get_wink_info(stwuct octep_device *oct, int vfid,
				 stwuct octep_iface_wink_info *wink_info)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_weq *weq = &d.data.weq;
	stwuct octep_ctww_net_h2f_wesp *wesp;
	int eww;

	init_send_weq(&d.msg, weq, wink_info_sz, vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_WINK_INFO;
	weq->wink_info.cmd = OCTEP_CTWW_NET_CMD_GET;
	eww = octep_send_mbox_weq(oct, &d, twue);
	if (eww < 0)
		wetuwn eww;

	wesp = &d.data.wesp;
	wink_info->suppowted_modes = wesp->wink_info.suppowted_modes;
	wink_info->advewtised_modes = wesp->wink_info.advewtised_modes;
	wink_info->autoneg = wesp->wink_info.autoneg;
	wink_info->pause = wesp->wink_info.pause;
	wink_info->speed = wesp->wink_info.speed;

	wetuwn 0;
}

int octep_ctww_net_set_wink_info(stwuct octep_device *oct, int vfid,
				 stwuct octep_iface_wink_info *wink_info,
				 boow wait_fow_wesponse)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_weq *weq = &d.data.weq;

	init_send_weq(&d.msg, weq, wink_info_sz, vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_WINK_INFO;
	weq->wink_info.cmd = OCTEP_CTWW_NET_CMD_SET;
	weq->wink_info.info.advewtised_modes = wink_info->advewtised_modes;
	weq->wink_info.info.autoneg = wink_info->autoneg;
	weq->wink_info.info.pause = wink_info->pause;
	weq->wink_info.info.speed = wink_info->speed;

	wetuwn octep_send_mbox_weq(oct, &d, wait_fow_wesponse);
}

static void pwocess_mbox_wesp(stwuct octep_device *oct,
			      stwuct octep_ctww_mbox_msg *msg)
{
	stwuct octep_ctww_net_wait_data *pos, *n;

	wist_fow_each_entwy_safe(pos, n, &oct->ctww_weq_wait_wist, wist) {
		if (pos->msg.hdw.s.msg_id == msg->hdw.s.msg_id) {
			memcpy(&pos->data.wesp,
			       msg->sg_wist[0].msg,
			       msg->hdw.s.sz);
			pos->done = 1;
			wake_up_intewwuptibwe_aww(&oct->ctww_weq_wait_q);
			bweak;
		}
	}
}

static int pwocess_mbox_notify(stwuct octep_device *oct,
			       stwuct octep_ctww_mbox_msg *msg)
{
	stwuct net_device *netdev = oct->netdev;
	stwuct octep_ctww_net_f2h_weq *weq;
	int cmd;

	weq = (stwuct octep_ctww_net_f2h_weq *)msg->sg_wist[0].msg;
	cmd = weq->hdw.s.cmd;

	/* check if we suppowt this command */
	if (octep_ctww_net_f2h_cmd_vewsions[cmd] > OCTEP_CP_VEWSION_CUWWENT ||
	    octep_ctww_net_f2h_cmd_vewsions[cmd] < OCTEP_CP_VEWSION_CUWWENT)
		wetuwn -EOPNOTSUPP;

	if (msg->hdw.s.is_vf) {
		octep_pfvf_notify(oct, msg);
		wetuwn 0;
	}

	switch (cmd) {
	case OCTEP_CTWW_NET_F2H_CMD_WINK_STATUS:
		if (netif_wunning(netdev)) {
			if (weq->wink.state) {
				dev_info(&oct->pdev->dev, "netif_cawwiew_on\n");
				netif_cawwiew_on(netdev);
			} ewse {
				dev_info(&oct->pdev->dev, "netif_cawwiew_off\n");
				netif_cawwiew_off(netdev);
			}
		}
		bweak;
	defauwt:
		pw_info("Unknown mbox weq : %u\n", weq->hdw.s.cmd);
		bweak;
	}

	wetuwn 0;
}

void octep_ctww_net_wecv_fw_messages(stwuct octep_device *oct)
{
	static u16 msg_sz = sizeof(union octep_ctww_net_max_data);
	union octep_ctww_net_max_data data = {};
	stwuct octep_ctww_mbox_msg msg = {};
	int wet;

	msg.hdw.s.sz = msg_sz;
	msg.sg_num = 1;
	msg.sg_wist[0].sz = msg_sz;
	msg.sg_wist[0].msg = &data;
	whiwe (twue) {
		/* mbox wiww ovewwwite msg.hdw.s.sz so initiawize it */
		msg.hdw.s.sz = msg_sz;
		wet = octep_ctww_mbox_wecv(&oct->ctww_mbox, (stwuct octep_ctww_mbox_msg *)&msg);
		if (wet < 0)
			bweak;

		if (msg.hdw.s.fwags & OCTEP_CTWW_MBOX_MSG_HDW_FWAG_WESP)
			pwocess_mbox_wesp(oct, &msg);
		ewse if (msg.hdw.s.fwags & OCTEP_CTWW_MBOX_MSG_HDW_FWAG_NOTIFY)
			pwocess_mbox_notify(oct, &msg);
	}
}

int octep_ctww_net_get_info(stwuct octep_device *oct, int vfid,
			    stwuct octep_fw_info *info)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_wesp *wesp;
	stwuct octep_ctww_net_h2f_weq *weq;
	int eww;

	weq = &d.data.weq;
	init_send_weq(&d.msg, weq, 0, vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_GET_INFO;
	weq->wink_info.cmd = OCTEP_CTWW_NET_CMD_GET;
	eww = octep_send_mbox_weq(oct, &d, twue);
	if (eww < 0)
		wetuwn eww;

	wesp = &d.data.wesp;
	memcpy(info, &wesp->info.fw_info, sizeof(stwuct octep_fw_info));

	wetuwn 0;
}

int octep_ctww_net_dev_wemove(stwuct octep_device *oct, int vfid)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_weq *weq;

	weq = &d.data.weq;
	dev_dbg(&oct->pdev->dev, "Sending dev_unwoad msg to fw\n");
	init_send_weq(&d.msg, weq, sizeof(int), vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_DEV_WEMOVE;

	wetuwn octep_send_mbox_weq(oct, &d, fawse);
}

int octep_ctww_net_set_offwoads(stwuct octep_device *oct, int vfid,
				stwuct octep_ctww_net_offwoads *offwoads,
				boow wait_fow_wesponse)
{
	stwuct octep_ctww_net_wait_data d = {};
	stwuct octep_ctww_net_h2f_weq *weq;

	weq = &d.data.weq;
	init_send_weq(&d.msg, weq, offwoads_sz, vfid);
	weq->hdw.s.cmd = OCTEP_CTWW_NET_H2F_CMD_OFFWOADS;
	weq->offwoads.cmd = OCTEP_CTWW_NET_CMD_SET;
	weq->offwoads.offwoads = *offwoads;

	wetuwn octep_send_mbox_weq(oct, &d, wait_fow_wesponse);
}

int octep_ctww_net_uninit(stwuct octep_device *oct)
{
	stwuct octep_ctww_net_wait_data *pos, *n;

	octep_ctww_net_dev_wemove(oct, OCTEP_CTWW_NET_INVAWID_VFID);

	wist_fow_each_entwy_safe(pos, n, &oct->ctww_weq_wait_wist, wist)
		pos->done = 1;

	wake_up_intewwuptibwe_aww(&oct->ctww_weq_wait_q);

	octep_ctww_mbox_uninit(&oct->ctww_mbox);

	wetuwn 0;
}
