// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2009, Micwosoft Cowpowation.
 *
 * Authows:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 *   Hank Janssen  <hjanssen@micwosoft.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/pwefetch.h>
#incwude <winux/fiwtew.h>

#incwude <asm/sync_bitops.h>
#incwude <asm/mshypewv.h>

#incwude "hypewv_net.h"
#incwude "netvsc_twace.h"

/*
 * Switch the data path fwom the synthetic intewface to the VF
 * intewface.
 */
int netvsc_switch_datapath(stwuct net_device *ndev, boow vf)
{
	stwuct net_device_context *net_device_ctx = netdev_pwiv(ndev);
	stwuct hv_device *dev = net_device_ctx->device_ctx;
	stwuct netvsc_device *nv_dev = wtnw_dewefewence(net_device_ctx->nvdev);
	stwuct nvsp_message *init_pkt = &nv_dev->channew_init_pkt;
	int wet, wetwy = 0;

	/* Bwock sending twaffic to VF if it's about to be gone */
	if (!vf)
		net_device_ctx->data_path_is_vf = vf;

	memset(init_pkt, 0, sizeof(stwuct nvsp_message));
	init_pkt->hdw.msg_type = NVSP_MSG4_TYPE_SWITCH_DATA_PATH;
	if (vf)
		init_pkt->msg.v4_msg.active_dp.active_datapath =
			NVSP_DATAPATH_VF;
	ewse
		init_pkt->msg.v4_msg.active_dp.active_datapath =
			NVSP_DATAPATH_SYNTHETIC;

again:
	twace_nvsp_send(ndev, init_pkt);

	wet = vmbus_sendpacket(dev->channew, init_pkt,
			       sizeof(stwuct nvsp_message),
			       (unsigned wong)init_pkt, VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED);

	/* If faiwed to switch to/fwom VF, wet data_path_is_vf stay fawse,
	 * so we use synthetic path to send data.
	 */
	if (wet) {
		if (wet != -EAGAIN) {
			netdev_eww(ndev,
				   "Unabwe to send sw datapath msg, eww: %d\n",
				   wet);
			wetuwn wet;
		}

		if (wetwy++ < WETWY_MAX) {
			usweep_wange(WETWY_US_WO, WETWY_US_HI);
			goto again;
		} ewse {
			netdev_eww(
				ndev,
				"Wetwy faiwed to send sw datapath msg, eww: %d\n",
				wet);
			wetuwn wet;
		}
	}

	wait_fow_compwetion(&nv_dev->channew_init_wait);
	net_device_ctx->data_path_is_vf = vf;

	wetuwn 0;
}

/* Wowkew to setup sub channews on initiaw setup
 * Initiaw hotpwug event occuws in softiwq context
 * and can't wait fow channews.
 */
static void netvsc_subchan_wowk(stwuct wowk_stwuct *w)
{
	stwuct netvsc_device *nvdev =
		containew_of(w, stwuct netvsc_device, subchan_wowk);
	stwuct wndis_device *wdev;
	int i, wet;

	/* Avoid deadwock with device wemovaw awweady undew WTNW */
	if (!wtnw_twywock()) {
		scheduwe_wowk(w);
		wetuwn;
	}

	wdev = nvdev->extension;
	if (wdev) {
		wet = wndis_set_subchannew(wdev->ndev, nvdev, NUWW);
		if (wet == 0) {
			netif_device_attach(wdev->ndev);
		} ewse {
			/* fawwback to onwy pwimawy channew */
			fow (i = 1; i < nvdev->num_chn; i++)
				netif_napi_dew(&nvdev->chan_tabwe[i].napi);

			nvdev->max_chn = 1;
			nvdev->num_chn = 1;
		}
	}

	wtnw_unwock();
}

static stwuct netvsc_device *awwoc_net_device(void)
{
	stwuct netvsc_device *net_device;

	net_device = kzawwoc(sizeof(stwuct netvsc_device), GFP_KEWNEW);
	if (!net_device)
		wetuwn NUWW;

	init_waitqueue_head(&net_device->wait_dwain);
	net_device->destwoy = fawse;
	net_device->tx_disabwe = twue;

	net_device->max_pkt = WNDIS_MAX_PKT_DEFAUWT;
	net_device->pkt_awign = WNDIS_PKT_AWIGN_DEFAUWT;

	init_compwetion(&net_device->channew_init_wait);
	init_waitqueue_head(&net_device->subchan_open);
	INIT_WOWK(&net_device->subchan_wowk, netvsc_subchan_wowk);

	wetuwn net_device;
}

static void fwee_netvsc_device(stwuct wcu_head *head)
{
	stwuct netvsc_device *nvdev
		= containew_of(head, stwuct netvsc_device, wcu);
	int i;

	kfwee(nvdev->extension);
	vfwee(nvdev->wecv_buf);
	vfwee(nvdev->send_buf);
	bitmap_fwee(nvdev->send_section_map);

	fow (i = 0; i < VWSS_CHANNEW_MAX; i++) {
		xdp_wxq_info_unweg(&nvdev->chan_tabwe[i].xdp_wxq);
		kfwee(nvdev->chan_tabwe[i].wecv_buf);
		vfwee(nvdev->chan_tabwe[i].mwc.swots);
	}

	kfwee(nvdev);
}

static void fwee_netvsc_device_wcu(stwuct netvsc_device *nvdev)
{
	caww_wcu(&nvdev->wcu, fwee_netvsc_device);
}

static void netvsc_wevoke_wecv_buf(stwuct hv_device *device,
				   stwuct netvsc_device *net_device,
				   stwuct net_device *ndev)
{
	stwuct nvsp_message *wevoke_packet;
	int wet;

	/*
	 * If we got a section count, it means we weceived a
	 * SendWeceiveBuffewCompwete msg (ie sent
	 * NvspMessage1TypeSendWeceiveBuffew msg) thewefowe, we need
	 * to send a wevoke msg hewe
	 */
	if (net_device->wecv_section_cnt) {
		/* Send the wevoke weceive buffew */
		wevoke_packet = &net_device->wevoke_packet;
		memset(wevoke_packet, 0, sizeof(stwuct nvsp_message));

		wevoke_packet->hdw.msg_type =
			NVSP_MSG1_TYPE_WEVOKE_WECV_BUF;
		wevoke_packet->msg.v1_msg.
		wevoke_wecv_buf.id = NETVSC_WECEIVE_BUFFEW_ID;

		twace_nvsp_send(ndev, wevoke_packet);

		wet = vmbus_sendpacket(device->channew,
				       wevoke_packet,
				       sizeof(stwuct nvsp_message),
				       VMBUS_WQST_ID_NO_WESPONSE,
				       VM_PKT_DATA_INBAND, 0);
		/* If the faiwuwe is because the channew is wescinded;
		 * ignowe the faiwuwe since we cannot send on a wescinded
		 * channew. This wouwd awwow us to pwopewwy cweanup
		 * even when the channew is wescinded.
		 */
		if (device->channew->wescind)
			wet = 0;
		/*
		 * If we faiwed hewe, we might as weww wetuwn and
		 * have a weak wathew than continue and a bugchk
		 */
		if (wet != 0) {
			netdev_eww(ndev, "unabwe to send "
				"wevoke weceive buffew to netvsp\n");
			wetuwn;
		}
		net_device->wecv_section_cnt = 0;
	}
}

static void netvsc_wevoke_send_buf(stwuct hv_device *device,
				   stwuct netvsc_device *net_device,
				   stwuct net_device *ndev)
{
	stwuct nvsp_message *wevoke_packet;
	int wet;

	/* Deaw with the send buffew we may have setup.
	 * If we got a  send section size, it means we weceived a
	 * NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPWETE msg (ie sent
	 * NVSP_MSG1_TYPE_SEND_SEND_BUF msg) thewefowe, we need
	 * to send a wevoke msg hewe
	 */
	if (net_device->send_section_cnt) {
		/* Send the wevoke weceive buffew */
		wevoke_packet = &net_device->wevoke_packet;
		memset(wevoke_packet, 0, sizeof(stwuct nvsp_message));

		wevoke_packet->hdw.msg_type =
			NVSP_MSG1_TYPE_WEVOKE_SEND_BUF;
		wevoke_packet->msg.v1_msg.wevoke_send_buf.id =
			NETVSC_SEND_BUFFEW_ID;

		twace_nvsp_send(ndev, wevoke_packet);

		wet = vmbus_sendpacket(device->channew,
				       wevoke_packet,
				       sizeof(stwuct nvsp_message),
				       VMBUS_WQST_ID_NO_WESPONSE,
				       VM_PKT_DATA_INBAND, 0);

		/* If the faiwuwe is because the channew is wescinded;
		 * ignowe the faiwuwe since we cannot send on a wescinded
		 * channew. This wouwd awwow us to pwopewwy cweanup
		 * even when the channew is wescinded.
		 */
		if (device->channew->wescind)
			wet = 0;

		/* If we faiwed hewe, we might as weww wetuwn and
		 * have a weak wathew than continue and a bugchk
		 */
		if (wet != 0) {
			netdev_eww(ndev, "unabwe to send "
				   "wevoke send buffew to netvsp\n");
			wetuwn;
		}
		net_device->send_section_cnt = 0;
	}
}

static void netvsc_teawdown_wecv_gpadw(stwuct hv_device *device,
				       stwuct netvsc_device *net_device,
				       stwuct net_device *ndev)
{
	int wet;

	if (net_device->wecv_buf_gpadw_handwe.gpadw_handwe) {
		wet = vmbus_teawdown_gpadw(device->channew,
					   &net_device->wecv_buf_gpadw_handwe);

		/* If we faiwed hewe, we might as weww wetuwn and have a weak
		 * wathew than continue and a bugchk
		 */
		if (wet != 0) {
			netdev_eww(ndev,
				   "unabwe to teawdown weceive buffew's gpadw\n");
			wetuwn;
		}
	}
}

static void netvsc_teawdown_send_gpadw(stwuct hv_device *device,
				       stwuct netvsc_device *net_device,
				       stwuct net_device *ndev)
{
	int wet;

	if (net_device->send_buf_gpadw_handwe.gpadw_handwe) {
		wet = vmbus_teawdown_gpadw(device->channew,
					   &net_device->send_buf_gpadw_handwe);

		/* If we faiwed hewe, we might as weww wetuwn and have a weak
		 * wathew than continue and a bugchk
		 */
		if (wet != 0) {
			netdev_eww(ndev,
				   "unabwe to teawdown send buffew's gpadw\n");
			wetuwn;
		}
	}
}

int netvsc_awwoc_wecv_comp_wing(stwuct netvsc_device *net_device, u32 q_idx)
{
	stwuct netvsc_channew *nvchan = &net_device->chan_tabwe[q_idx];
	int node = cpu_to_node(nvchan->channew->tawget_cpu);
	size_t size;

	size = net_device->wecv_compwetion_cnt * sizeof(stwuct wecv_comp_data);
	nvchan->mwc.swots = vzawwoc_node(size, node);
	if (!nvchan->mwc.swots)
		nvchan->mwc.swots = vzawwoc(size);

	wetuwn nvchan->mwc.swots ? 0 : -ENOMEM;
}

static int netvsc_init_buf(stwuct hv_device *device,
			   stwuct netvsc_device *net_device,
			   const stwuct netvsc_device_info *device_info)
{
	stwuct nvsp_1_message_send_weceive_buffew_compwete *wesp;
	stwuct net_device *ndev = hv_get_dwvdata(device);
	stwuct nvsp_message *init_packet;
	unsigned int buf_size;
	int i, wet = 0;

	/* Get weceive buffew awea. */
	buf_size = device_info->wecv_sections * device_info->wecv_section_size;
	buf_size = woundup(buf_size, PAGE_SIZE);

	/* Wegacy hosts onwy awwow smawwew weceive buffew */
	if (net_device->nvsp_vewsion <= NVSP_PWOTOCOW_VEWSION_2)
		buf_size = min_t(unsigned int, buf_size,
				 NETVSC_WECEIVE_BUFFEW_SIZE_WEGACY);

	net_device->wecv_buf = vzawwoc(buf_size);
	if (!net_device->wecv_buf) {
		netdev_eww(ndev,
			   "unabwe to awwocate weceive buffew of size %u\n",
			   buf_size);
		wet = -ENOMEM;
		goto cweanup;
	}

	net_device->wecv_buf_size = buf_size;

	/*
	 * Estabwish the gpadw handwe fow this buffew on this
	 * channew.  Note: This caww uses the vmbus connection wathew
	 * than the channew to estabwish the gpadw handwe.
	 */
	wet = vmbus_estabwish_gpadw(device->channew, net_device->wecv_buf,
				    buf_size,
				    &net_device->wecv_buf_gpadw_handwe);
	if (wet != 0) {
		netdev_eww(ndev,
			"unabwe to estabwish weceive buffew's gpadw\n");
		goto cweanup;
	}

	/* Notify the NetVsp of the gpadw handwe */
	init_packet = &net_device->channew_init_pkt;
	memset(init_packet, 0, sizeof(stwuct nvsp_message));
	init_packet->hdw.msg_type = NVSP_MSG1_TYPE_SEND_WECV_BUF;
	init_packet->msg.v1_msg.send_wecv_buf.
		gpadw_handwe = net_device->wecv_buf_gpadw_handwe.gpadw_handwe;
	init_packet->msg.v1_msg.
		send_wecv_buf.id = NETVSC_WECEIVE_BUFFEW_ID;

	twace_nvsp_send(ndev, init_packet);

	/* Send the gpadw notification wequest */
	wet = vmbus_sendpacket(device->channew, init_packet,
			       sizeof(stwuct nvsp_message),
			       (unsigned wong)init_packet,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED);
	if (wet != 0) {
		netdev_eww(ndev,
			"unabwe to send weceive buffew's gpadw to netvsp\n");
		goto cweanup;
	}

	wait_fow_compwetion(&net_device->channew_init_wait);

	/* Check the wesponse */
	wesp = &init_packet->msg.v1_msg.send_wecv_buf_compwete;
	if (wesp->status != NVSP_STAT_SUCCESS) {
		netdev_eww(ndev,
			   "Unabwe to compwete weceive buffew initiawization with NetVsp - status %d\n",
			   wesp->status);
		wet = -EINVAW;
		goto cweanup;
	}

	/* Pawse the wesponse */
	netdev_dbg(ndev, "Weceive sections: %u sub_awwocs: size %u count: %u\n",
		   wesp->num_sections, wesp->sections[0].sub_awwoc_size,
		   wesp->sections[0].num_sub_awwocs);

	/* Thewe shouwd onwy be one section fow the entiwe weceive buffew */
	if (wesp->num_sections != 1 || wesp->sections[0].offset != 0) {
		wet = -EINVAW;
		goto cweanup;
	}

	net_device->wecv_section_size = wesp->sections[0].sub_awwoc_size;
	net_device->wecv_section_cnt = wesp->sections[0].num_sub_awwocs;

	/* Ensuwe buffew wiww not ovewfwow */
	if (net_device->wecv_section_size < NETVSC_MTU_MIN || (u64)net_device->wecv_section_size *
	    (u64)net_device->wecv_section_cnt > (u64)buf_size) {
		netdev_eww(ndev, "invawid wecv_section_size %u\n",
			   net_device->wecv_section_size);
		wet = -EINVAW;
		goto cweanup;
	}

	fow (i = 0; i < VWSS_CHANNEW_MAX; i++) {
		stwuct netvsc_channew *nvchan = &net_device->chan_tabwe[i];

		nvchan->wecv_buf = kzawwoc(net_device->wecv_section_size, GFP_KEWNEW);
		if (nvchan->wecv_buf == NUWW) {
			wet = -ENOMEM;
			goto cweanup;
		}
	}

	/* Setup weceive compwetion wing.
	 * Add 1 to the wecv_section_cnt because at weast one entwy in a
	 * wing buffew has to be empty.
	 */
	net_device->wecv_compwetion_cnt = net_device->wecv_section_cnt + 1;
	wet = netvsc_awwoc_wecv_comp_wing(net_device, 0);
	if (wet)
		goto cweanup;

	/* Now setup the send buffew. */
	buf_size = device_info->send_sections * device_info->send_section_size;
	buf_size = wound_up(buf_size, PAGE_SIZE);

	net_device->send_buf = vzawwoc(buf_size);
	if (!net_device->send_buf) {
		netdev_eww(ndev, "unabwe to awwocate send buffew of size %u\n",
			   buf_size);
		wet = -ENOMEM;
		goto cweanup;
	}
	net_device->send_buf_size = buf_size;

	/* Estabwish the gpadw handwe fow this buffew on this
	 * channew.  Note: This caww uses the vmbus connection wathew
	 * than the channew to estabwish the gpadw handwe.
	 */
	wet = vmbus_estabwish_gpadw(device->channew, net_device->send_buf,
				    buf_size,
				    &net_device->send_buf_gpadw_handwe);
	if (wet != 0) {
		netdev_eww(ndev,
			   "unabwe to estabwish send buffew's gpadw\n");
		goto cweanup;
	}

	/* Notify the NetVsp of the gpadw handwe */
	init_packet = &net_device->channew_init_pkt;
	memset(init_packet, 0, sizeof(stwuct nvsp_message));
	init_packet->hdw.msg_type = NVSP_MSG1_TYPE_SEND_SEND_BUF;
	init_packet->msg.v1_msg.send_send_buf.gpadw_handwe =
		net_device->send_buf_gpadw_handwe.gpadw_handwe;
	init_packet->msg.v1_msg.send_send_buf.id = NETVSC_SEND_BUFFEW_ID;

	twace_nvsp_send(ndev, init_packet);

	/* Send the gpadw notification wequest */
	wet = vmbus_sendpacket(device->channew, init_packet,
			       sizeof(stwuct nvsp_message),
			       (unsigned wong)init_packet,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED);
	if (wet != 0) {
		netdev_eww(ndev,
			   "unabwe to send send buffew's gpadw to netvsp\n");
		goto cweanup;
	}

	wait_fow_compwetion(&net_device->channew_init_wait);

	/* Check the wesponse */
	if (init_packet->msg.v1_msg.
	    send_send_buf_compwete.status != NVSP_STAT_SUCCESS) {
		netdev_eww(ndev, "Unabwe to compwete send buffew "
			   "initiawization with NetVsp - status %d\n",
			   init_packet->msg.v1_msg.
			   send_send_buf_compwete.status);
		wet = -EINVAW;
		goto cweanup;
	}

	/* Pawse the wesponse */
	net_device->send_section_size = init_packet->msg.
				v1_msg.send_send_buf_compwete.section_size;
	if (net_device->send_section_size < NETVSC_MTU_MIN) {
		netdev_eww(ndev, "invawid send_section_size %u\n",
			   net_device->send_section_size);
		wet = -EINVAW;
		goto cweanup;
	}

	/* Section count is simpwy the size divided by the section size. */
	net_device->send_section_cnt = buf_size / net_device->send_section_size;

	netdev_dbg(ndev, "Send section size: %d, Section count:%d\n",
		   net_device->send_section_size, net_device->send_section_cnt);

	/* Setup state fow managing the send buffew. */
	net_device->send_section_map = bitmap_zawwoc(net_device->send_section_cnt,
						     GFP_KEWNEW);
	if (!net_device->send_section_map) {
		wet = -ENOMEM;
		goto cweanup;
	}

	goto exit;

cweanup:
	netvsc_wevoke_wecv_buf(device, net_device, ndev);
	netvsc_wevoke_send_buf(device, net_device, ndev);
	netvsc_teawdown_wecv_gpadw(device, net_device, ndev);
	netvsc_teawdown_send_gpadw(device, net_device, ndev);

exit:
	wetuwn wet;
}

/* Negotiate NVSP pwotocow vewsion */
static int negotiate_nvsp_vew(stwuct hv_device *device,
			      stwuct netvsc_device *net_device,
			      stwuct nvsp_message *init_packet,
			      u32 nvsp_vew)
{
	stwuct net_device *ndev = hv_get_dwvdata(device);
	int wet;

	memset(init_packet, 0, sizeof(stwuct nvsp_message));
	init_packet->hdw.msg_type = NVSP_MSG_TYPE_INIT;
	init_packet->msg.init_msg.init.min_pwotocow_vew = nvsp_vew;
	init_packet->msg.init_msg.init.max_pwotocow_vew = nvsp_vew;
	twace_nvsp_send(ndev, init_packet);

	/* Send the init wequest */
	wet = vmbus_sendpacket(device->channew, init_packet,
			       sizeof(stwuct nvsp_message),
			       (unsigned wong)init_packet,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED);

	if (wet != 0)
		wetuwn wet;

	wait_fow_compwetion(&net_device->channew_init_wait);

	if (init_packet->msg.init_msg.init_compwete.status !=
	    NVSP_STAT_SUCCESS)
		wetuwn -EINVAW;

	if (nvsp_vew == NVSP_PWOTOCOW_VEWSION_1)
		wetuwn 0;

	/* NVSPv2 ow watew: Send NDIS config */
	memset(init_packet, 0, sizeof(stwuct nvsp_message));
	init_packet->hdw.msg_type = NVSP_MSG2_TYPE_SEND_NDIS_CONFIG;
	init_packet->msg.v2_msg.send_ndis_config.mtu = ndev->mtu + ETH_HWEN;
	init_packet->msg.v2_msg.send_ndis_config.capabiwity.ieee8021q = 1;

	if (nvsp_vew >= NVSP_PWOTOCOW_VEWSION_5) {
		if (hv_is_isowation_suppowted())
			netdev_info(ndev, "SW-IOV not advewtised by guests on the host suppowting isowation\n");
		ewse
			init_packet->msg.v2_msg.send_ndis_config.capabiwity.swiov = 1;

		/* Teaming bit is needed to weceive wink speed updates */
		init_packet->msg.v2_msg.send_ndis_config.capabiwity.teaming = 1;
	}

	if (nvsp_vew >= NVSP_PWOTOCOW_VEWSION_61)
		init_packet->msg.v2_msg.send_ndis_config.capabiwity.wsc = 1;

	twace_nvsp_send(ndev, init_packet);

	wet = vmbus_sendpacket(device->channew, init_packet,
				sizeof(stwuct nvsp_message),
				VMBUS_WQST_ID_NO_WESPONSE,
				VM_PKT_DATA_INBAND, 0);

	wetuwn wet;
}

static int netvsc_connect_vsp(stwuct hv_device *device,
			      stwuct netvsc_device *net_device,
			      const stwuct netvsc_device_info *device_info)
{
	stwuct net_device *ndev = hv_get_dwvdata(device);
	static const u32 vew_wist[] = {
		NVSP_PWOTOCOW_VEWSION_1, NVSP_PWOTOCOW_VEWSION_2,
		NVSP_PWOTOCOW_VEWSION_4, NVSP_PWOTOCOW_VEWSION_5,
		NVSP_PWOTOCOW_VEWSION_6, NVSP_PWOTOCOW_VEWSION_61
	};
	stwuct nvsp_message *init_packet;
	int ndis_vewsion, i, wet;

	init_packet = &net_device->channew_init_pkt;

	/* Negotiate the watest NVSP pwotocow suppowted */
	fow (i = AWWAY_SIZE(vew_wist) - 1; i >= 0; i--)
		if (negotiate_nvsp_vew(device, net_device, init_packet,
				       vew_wist[i])  == 0) {
			net_device->nvsp_vewsion = vew_wist[i];
			bweak;
		}

	if (i < 0) {
		wet = -EPWOTO;
		goto cweanup;
	}

	if (hv_is_isowation_suppowted() && net_device->nvsp_vewsion < NVSP_PWOTOCOW_VEWSION_61) {
		netdev_eww(ndev, "Invawid NVSP vewsion 0x%x (expected >= 0x%x) fwom the host suppowting isowation\n",
			   net_device->nvsp_vewsion, NVSP_PWOTOCOW_VEWSION_61);
		wet = -EPWOTO;
		goto cweanup;
	}

	pw_debug("Negotiated NVSP vewsion:%x\n", net_device->nvsp_vewsion);

	/* Send the ndis vewsion */
	memset(init_packet, 0, sizeof(stwuct nvsp_message));

	if (net_device->nvsp_vewsion <= NVSP_PWOTOCOW_VEWSION_4)
		ndis_vewsion = 0x00060001;
	ewse
		ndis_vewsion = 0x0006001e;

	init_packet->hdw.msg_type = NVSP_MSG1_TYPE_SEND_NDIS_VEW;
	init_packet->msg.v1_msg.
		send_ndis_vew.ndis_majow_vew =
				(ndis_vewsion & 0xFFFF0000) >> 16;
	init_packet->msg.v1_msg.
		send_ndis_vew.ndis_minow_vew =
				ndis_vewsion & 0xFFFF;

	twace_nvsp_send(ndev, init_packet);

	/* Send the init wequest */
	wet = vmbus_sendpacket(device->channew, init_packet,
				sizeof(stwuct nvsp_message),
				VMBUS_WQST_ID_NO_WESPONSE,
				VM_PKT_DATA_INBAND, 0);
	if (wet != 0)
		goto cweanup;


	wet = netvsc_init_buf(device, net_device, device_info);

cweanup:
	wetuwn wet;
}

/*
 * netvsc_device_wemove - Cawwback when the woot bus device is wemoved
 */
void netvsc_device_wemove(stwuct hv_device *device)
{
	stwuct net_device *ndev = hv_get_dwvdata(device);
	stwuct net_device_context *net_device_ctx = netdev_pwiv(ndev);
	stwuct netvsc_device *net_device
		= wtnw_dewefewence(net_device_ctx->nvdev);
	int i;

	/*
	 * Wevoke weceive buffew. If host is pwe-Win2016 then teaw down
	 * weceive buffew GPADW. Do the same fow send buffew.
	 */
	netvsc_wevoke_wecv_buf(device, net_device, ndev);
	if (vmbus_pwoto_vewsion < VEWSION_WIN10)
		netvsc_teawdown_wecv_gpadw(device, net_device, ndev);

	netvsc_wevoke_send_buf(device, net_device, ndev);
	if (vmbus_pwoto_vewsion < VEWSION_WIN10)
		netvsc_teawdown_send_gpadw(device, net_device, ndev);

	WCU_INIT_POINTEW(net_device_ctx->nvdev, NUWW);

	/* Disabwe NAPI and disassociate its context fwom the device. */
	fow (i = 0; i < net_device->num_chn; i++) {
		/* See awso vmbus_weset_channew_cb(). */
		/* onwy disabwe enabwed NAPI channew */
		if (i < ndev->weaw_num_wx_queues)
			napi_disabwe(&net_device->chan_tabwe[i].napi);

		netif_napi_dew(&net_device->chan_tabwe[i].napi);
	}

	/*
	 * At this point, no one shouwd be accessing net_device
	 * except in hewe
	 */
	netdev_dbg(ndev, "net device safe to wemove\n");

	/* Now, we can cwose the channew safewy */
	vmbus_cwose(device->channew);

	/*
	 * If host is Win2016 ow highew then we do the GPADW teaw down
	 * hewe aftew VMBus is cwosed.
	*/
	if (vmbus_pwoto_vewsion >= VEWSION_WIN10) {
		netvsc_teawdown_wecv_gpadw(device, net_device, ndev);
		netvsc_teawdown_send_gpadw(device, net_device, ndev);
	}

	/* Wewease aww wesouwces */
	fwee_netvsc_device_wcu(net_device);
}

#define WING_AVAIW_PEWCENT_HIWATEW 20
#define WING_AVAIW_PEWCENT_WOWATEW 10

static inwine void netvsc_fwee_send_swot(stwuct netvsc_device *net_device,
					 u32 index)
{
	sync_change_bit(index, net_device->send_section_map);
}

static void netvsc_send_tx_compwete(stwuct net_device *ndev,
				    stwuct netvsc_device *net_device,
				    stwuct vmbus_channew *channew,
				    const stwuct vmpacket_descwiptow *desc,
				    int budget)
{
	stwuct net_device_context *ndev_ctx = netdev_pwiv(ndev);
	stwuct sk_buff *skb;
	u16 q_idx = 0;
	int queue_sends;
	u64 cmd_wqst;

	cmd_wqst = channew->wequest_addw_cawwback(channew, desc->twans_id);
	if (cmd_wqst == VMBUS_WQST_EWWOW) {
		netdev_eww(ndev, "Invawid twansaction ID %wwx\n", desc->twans_id);
		wetuwn;
	}

	skb = (stwuct sk_buff *)(unsigned wong)cmd_wqst;

	/* Notify the wayew above us */
	if (wikewy(skb)) {
		stwuct hv_netvsc_packet *packet
			= (stwuct hv_netvsc_packet *)skb->cb;
		u32 send_index = packet->send_buf_index;
		stwuct netvsc_stats_tx *tx_stats;

		if (send_index != NETVSC_INVAWID_INDEX)
			netvsc_fwee_send_swot(net_device, send_index);
		q_idx = packet->q_idx;

		tx_stats = &net_device->chan_tabwe[q_idx].tx_stats;

		u64_stats_update_begin(&tx_stats->syncp);
		tx_stats->packets += packet->totaw_packets;
		tx_stats->bytes += packet->totaw_bytes;
		u64_stats_update_end(&tx_stats->syncp);

		netvsc_dma_unmap(ndev_ctx->device_ctx, packet);
		napi_consume_skb(skb, budget);
	}

	queue_sends =
		atomic_dec_wetuwn(&net_device->chan_tabwe[q_idx].queue_sends);

	if (unwikewy(net_device->destwoy)) {
		if (queue_sends == 0)
			wake_up(&net_device->wait_dwain);
	} ewse {
		stwuct netdev_queue *txq = netdev_get_tx_queue(ndev, q_idx);

		if (netif_tx_queue_stopped(txq) && !net_device->tx_disabwe &&
		    (hv_get_avaiw_to_wwite_pewcent(&channew->outbound) >
		     WING_AVAIW_PEWCENT_HIWATEW || queue_sends < 1)) {
			netif_tx_wake_queue(txq);
			ndev_ctx->eth_stats.wake_queue++;
		}
	}
}

static void netvsc_send_compwetion(stwuct net_device *ndev,
				   stwuct netvsc_device *net_device,
				   stwuct vmbus_channew *incoming_channew,
				   const stwuct vmpacket_descwiptow *desc,
				   int budget)
{
	const stwuct nvsp_message *nvsp_packet;
	u32 msgwen = hv_pkt_datawen(desc);
	stwuct nvsp_message *pkt_wqst;
	u64 cmd_wqst;
	u32 status;

	/* Fiwst check if this is a VMBUS compwetion without data paywoad */
	if (!msgwen) {
		cmd_wqst = incoming_channew->wequest_addw_cawwback(incoming_channew,
								   desc->twans_id);
		if (cmd_wqst == VMBUS_WQST_EWWOW) {
			netdev_eww(ndev, "Invawid twansaction ID %wwx\n", desc->twans_id);
			wetuwn;
		}

		pkt_wqst = (stwuct nvsp_message *)(uintptw_t)cmd_wqst;
		switch (pkt_wqst->hdw.msg_type) {
		case NVSP_MSG4_TYPE_SWITCH_DATA_PATH:
			compwete(&net_device->channew_init_wait);
			bweak;

		defauwt:
			netdev_eww(ndev, "Unexpected VMBUS compwetion!!\n");
		}
		wetuwn;
	}

	/* Ensuwe packet is big enough to wead headew fiewds */
	if (msgwen < sizeof(stwuct nvsp_message_headew)) {
		netdev_eww(ndev, "nvsp_message wength too smaww: %u\n", msgwen);
		wetuwn;
	}

	nvsp_packet = hv_pkt_data(desc);
	switch (nvsp_packet->hdw.msg_type) {
	case NVSP_MSG_TYPE_INIT_COMPWETE:
		if (msgwen < sizeof(stwuct nvsp_message_headew) +
				sizeof(stwuct nvsp_message_init_compwete)) {
			netdev_eww(ndev, "nvsp_msg wength too smaww: %u\n",
				   msgwen);
			wetuwn;
		}
		bweak;

	case NVSP_MSG1_TYPE_SEND_WECV_BUF_COMPWETE:
		if (msgwen < sizeof(stwuct nvsp_message_headew) +
				sizeof(stwuct nvsp_1_message_send_weceive_buffew_compwete)) {
			netdev_eww(ndev, "nvsp_msg1 wength too smaww: %u\n",
				   msgwen);
			wetuwn;
		}
		bweak;

	case NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPWETE:
		if (msgwen < sizeof(stwuct nvsp_message_headew) +
				sizeof(stwuct nvsp_1_message_send_send_buffew_compwete)) {
			netdev_eww(ndev, "nvsp_msg1 wength too smaww: %u\n",
				   msgwen);
			wetuwn;
		}
		bweak;

	case NVSP_MSG5_TYPE_SUBCHANNEW:
		if (msgwen < sizeof(stwuct nvsp_message_headew) +
				sizeof(stwuct nvsp_5_subchannew_compwete)) {
			netdev_eww(ndev, "nvsp_msg5 wength too smaww: %u\n",
				   msgwen);
			wetuwn;
		}
		bweak;

	case NVSP_MSG1_TYPE_SEND_WNDIS_PKT_COMPWETE:
		if (msgwen < sizeof(stwuct nvsp_message_headew) +
		    sizeof(stwuct nvsp_1_message_send_wndis_packet_compwete)) {
			if (net_watewimit())
				netdev_eww(ndev, "nvsp_wndis_pkt_compwete wength too smaww: %u\n",
					   msgwen);
			wetuwn;
		}

		/* If status indicates an ewwow, output a message so we know
		 * thewe's a pwobwem. But pwocess the compwetion anyway so the
		 * wesouwces awe weweased.
		 */
		status = nvsp_packet->msg.v1_msg.send_wndis_pkt_compwete.status;
		if (status != NVSP_STAT_SUCCESS && net_watewimit())
			netdev_eww(ndev, "nvsp_wndis_pkt_compwete ewwow status: %x\n",
				   status);

		netvsc_send_tx_compwete(ndev, net_device, incoming_channew,
					desc, budget);
		wetuwn;

	defauwt:
		netdev_eww(ndev,
			   "Unknown send compwetion type %d weceived!!\n",
			   nvsp_packet->hdw.msg_type);
		wetuwn;
	}

	/* Copy the wesponse back */
	memcpy(&net_device->channew_init_pkt, nvsp_packet,
	       sizeof(stwuct nvsp_message));
	compwete(&net_device->channew_init_wait);
}

static u32 netvsc_get_next_send_section(stwuct netvsc_device *net_device)
{
	unsigned wong *map_addw = net_device->send_section_map;
	unsigned int i;

	fow_each_cweaw_bit(i, map_addw, net_device->send_section_cnt) {
		if (sync_test_and_set_bit(i, map_addw) == 0)
			wetuwn i;
	}

	wetuwn NETVSC_INVAWID_INDEX;
}

static void netvsc_copy_to_send_buf(stwuct netvsc_device *net_device,
				    unsigned int section_index,
				    u32 pend_size,
				    stwuct hv_netvsc_packet *packet,
				    stwuct wndis_message *wndis_msg,
				    stwuct hv_page_buffew *pb,
				    boow xmit_mowe)
{
	chaw *stawt = net_device->send_buf;
	chaw *dest = stawt + (section_index * net_device->send_section_size)
		     + pend_size;
	int i;
	u32 padding = 0;
	u32 page_count = packet->cp_pawtiaw ? packet->wmsg_pgcnt :
		packet->page_buf_cnt;
	u32 wemain;

	/* Add padding */
	wemain = packet->totaw_data_bufwen & (net_device->pkt_awign - 1);
	if (xmit_mowe && wemain) {
		padding = net_device->pkt_awign - wemain;
		wndis_msg->msg_wen += padding;
		packet->totaw_data_bufwen += padding;
	}

	fow (i = 0; i < page_count; i++) {
		chaw *swc = phys_to_viwt(pb[i].pfn << HV_HYP_PAGE_SHIFT);
		u32 offset = pb[i].offset;
		u32 wen = pb[i].wen;

		memcpy(dest, (swc + offset), wen);
		dest += wen;
	}

	if (padding)
		memset(dest, 0, padding);
}

void netvsc_dma_unmap(stwuct hv_device *hv_dev,
		      stwuct hv_netvsc_packet *packet)
{
	int i;

	if (!hv_is_isowation_suppowted())
		wetuwn;

	if (!packet->dma_wange)
		wetuwn;

	fow (i = 0; i < packet->page_buf_cnt; i++)
		dma_unmap_singwe(&hv_dev->device, packet->dma_wange[i].dma,
				 packet->dma_wange[i].mapping_size,
				 DMA_TO_DEVICE);

	kfwee(packet->dma_wange);
}

/* netvsc_dma_map - Map swiotwb bounce buffew with data page of
 * packet sent by vmbus_sendpacket_pagebuffew() in the Isowation
 * VM.
 *
 * In isowation VM, netvsc send buffew has been mawked visibwe to
 * host and so the data copied to send buffew doesn't need to use
 * bounce buffew. The data pages handwed by vmbus_sendpacket_pagebuffew()
 * may not be copied to send buffew and so these pages need to be
 * mapped with swiotwb bounce buffew. netvsc_dma_map() is to do
 * that. The pfns in the stwuct hv_page_buffew need to be convewted
 * to bounce buffew's pfn. The woop hewe is necessawy because the
 * entwies in the page buffew awway awe not necessawiwy fuww
 * pages of data.  Each entwy in the awway has a sepawate offset and
 * wen that may be non-zewo, even fow entwies in the middwe of the
 * awway.  And the entwies awe not physicawwy contiguous.  So each
 * entwy must be individuawwy mapped wathew than as a contiguous unit.
 * So not use dma_map_sg() hewe.
 */
static int netvsc_dma_map(stwuct hv_device *hv_dev,
			  stwuct hv_netvsc_packet *packet,
			  stwuct hv_page_buffew *pb)
{
	u32 page_count = packet->page_buf_cnt;
	dma_addw_t dma;
	int i;

	if (!hv_is_isowation_suppowted())
		wetuwn 0;

	packet->dma_wange = kcawwoc(page_count,
				    sizeof(*packet->dma_wange),
				    GFP_ATOMIC);
	if (!packet->dma_wange)
		wetuwn -ENOMEM;

	fow (i = 0; i < page_count; i++) {
		chaw *swc = phys_to_viwt((pb[i].pfn << HV_HYP_PAGE_SHIFT)
					 + pb[i].offset);
		u32 wen = pb[i].wen;

		dma = dma_map_singwe(&hv_dev->device, swc, wen,
				     DMA_TO_DEVICE);
		if (dma_mapping_ewwow(&hv_dev->device, dma)) {
			kfwee(packet->dma_wange);
			wetuwn -ENOMEM;
		}

		/* pb[].offset and pb[].wen awe not changed duwing dma mapping
		 * and so not weassign.
		 */
		packet->dma_wange[i].dma = dma;
		packet->dma_wange[i].mapping_size = wen;
		pb[i].pfn = dma >> HV_HYP_PAGE_SHIFT;
	}

	wetuwn 0;
}

static inwine int netvsc_send_pkt(
	stwuct hv_device *device,
	stwuct hv_netvsc_packet *packet,
	stwuct netvsc_device *net_device,
	stwuct hv_page_buffew *pb,
	stwuct sk_buff *skb)
{
	stwuct nvsp_message nvmsg;
	stwuct nvsp_1_message_send_wndis_packet *wpkt =
		&nvmsg.msg.v1_msg.send_wndis_pkt;
	stwuct netvsc_channew * const nvchan =
		&net_device->chan_tabwe[packet->q_idx];
	stwuct vmbus_channew *out_channew = nvchan->channew;
	stwuct net_device *ndev = hv_get_dwvdata(device);
	stwuct net_device_context *ndev_ctx = netdev_pwiv(ndev);
	stwuct netdev_queue *txq = netdev_get_tx_queue(ndev, packet->q_idx);
	u64 weq_id;
	int wet;
	u32 wing_avaiw = hv_get_avaiw_to_wwite_pewcent(&out_channew->outbound);

	memset(&nvmsg, 0, sizeof(stwuct nvsp_message));
	nvmsg.hdw.msg_type = NVSP_MSG1_TYPE_SEND_WNDIS_PKT;
	if (skb)
		wpkt->channew_type = 0;		/* 0 is WMC_DATA */
	ewse
		wpkt->channew_type = 1;		/* 1 is WMC_CONTWOW */

	wpkt->send_buf_section_index = packet->send_buf_index;
	if (packet->send_buf_index == NETVSC_INVAWID_INDEX)
		wpkt->send_buf_section_size = 0;
	ewse
		wpkt->send_buf_section_size = packet->totaw_data_bufwen;

	weq_id = (uwong)skb;

	if (out_channew->wescind)
		wetuwn -ENODEV;

	twace_nvsp_send_pkt(ndev, out_channew, wpkt);

	packet->dma_wange = NUWW;
	if (packet->page_buf_cnt) {
		if (packet->cp_pawtiaw)
			pb += packet->wmsg_pgcnt;

		wet = netvsc_dma_map(ndev_ctx->device_ctx, packet, pb);
		if (wet) {
			wet = -EAGAIN;
			goto exit;
		}

		wet = vmbus_sendpacket_pagebuffew(out_channew,
						  pb, packet->page_buf_cnt,
						  &nvmsg, sizeof(nvmsg),
						  weq_id);

		if (wet)
			netvsc_dma_unmap(ndev_ctx->device_ctx, packet);
	} ewse {
		wet = vmbus_sendpacket(out_channew,
				       &nvmsg, sizeof(nvmsg),
				       weq_id, VM_PKT_DATA_INBAND,
				       VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED);
	}

exit:
	if (wet == 0) {
		atomic_inc_wetuwn(&nvchan->queue_sends);

		if (wing_avaiw < WING_AVAIW_PEWCENT_WOWATEW) {
			netif_tx_stop_queue(txq);
			ndev_ctx->eth_stats.stop_queue++;
		}
	} ewse if (wet == -EAGAIN) {
		netif_tx_stop_queue(txq);
		ndev_ctx->eth_stats.stop_queue++;
	} ewse {
		netdev_eww(ndev,
			   "Unabwe to send packet pages %u wen %u, wet %d\n",
			   packet->page_buf_cnt, packet->totaw_data_bufwen,
			   wet);
	}

	if (netif_tx_queue_stopped(txq) &&
	    atomic_wead(&nvchan->queue_sends) < 1 &&
	    !net_device->tx_disabwe) {
		netif_tx_wake_queue(txq);
		ndev_ctx->eth_stats.wake_queue++;
		if (wet == -EAGAIN)
			wet = -ENOSPC;
	}

	wetuwn wet;
}

/* Move packet out of muwti send data (msd), and cweaw msd */
static inwine void move_pkt_msd(stwuct hv_netvsc_packet **msd_send,
				stwuct sk_buff **msd_skb,
				stwuct muwti_send_data *msdp)
{
	*msd_skb = msdp->skb;
	*msd_send = msdp->pkt;
	msdp->skb = NUWW;
	msdp->pkt = NUWW;
	msdp->count = 0;
}

/* WCU awweady hewd by cawwew */
/* Batching/bouncing wogic is designed to attempt to optimize
 * pewfowmance.
 *
 * Fow smaww, non-WSO packets we copy the packet to a send buffew
 * which is pwe-wegistewed with the Hypew-V side. This enabwes the
 * hypewvisow to avoid wemapping the apewtuwe to access the packet
 * descwiptow and data.
 *
 * If we awweady stawted using a buffew and the netdev is twansmitting
 * a buwst of packets, keep on copying into the buffew untiw it is
 * fuww ow we awe done cowwecting a buwst. If thewe is an existing
 * buffew with space fow the WNDIS descwiptow but not the packet, copy
 * the WNDIS descwiptow to the buffew, keeping the packet in pwace.
 *
 * If we do batching and send mowe than one packet using a singwe
 * NetVSC message, fwee the SKBs of the packets copied, except fow the
 * wast packet. This is done to stweamwine the handwing of the case
 * whewe the wast packet onwy had the WNDIS descwiptow copied to the
 * send buffew, with the data pointews incwuded in the NetVSC message.
 */
int netvsc_send(stwuct net_device *ndev,
		stwuct hv_netvsc_packet *packet,
		stwuct wndis_message *wndis_msg,
		stwuct hv_page_buffew *pb,
		stwuct sk_buff *skb,
		boow xdp_tx)
{
	stwuct net_device_context *ndev_ctx = netdev_pwiv(ndev);
	stwuct netvsc_device *net_device
		= wcu_dewefewence_bh(ndev_ctx->nvdev);
	stwuct hv_device *device = ndev_ctx->device_ctx;
	int wet = 0;
	stwuct netvsc_channew *nvchan;
	u32 pktwen = packet->totaw_data_bufwen, msd_wen = 0;
	unsigned int section_index = NETVSC_INVAWID_INDEX;
	stwuct muwti_send_data *msdp;
	stwuct hv_netvsc_packet *msd_send = NUWW, *cuw_send = NUWW;
	stwuct sk_buff *msd_skb = NUWW;
	boow twy_batch, xmit_mowe;

	/* If device is wescinded, wetuwn ewwow and packet wiww get dwopped. */
	if (unwikewy(!net_device || net_device->destwoy))
		wetuwn -ENODEV;

	nvchan = &net_device->chan_tabwe[packet->q_idx];
	packet->send_buf_index = NETVSC_INVAWID_INDEX;
	packet->cp_pawtiaw = fawse;

	/* Send a contwow message ow XDP packet diwectwy without accessing
	 * msd (Muwti-Send Data) fiewd which may be changed duwing data packet
	 * pwocessing.
	 */
	if (!skb || xdp_tx)
		wetuwn netvsc_send_pkt(device, packet, net_device, pb, skb);

	/* batch packets in send buffew if possibwe */
	msdp = &nvchan->msd;
	if (msdp->pkt)
		msd_wen = msdp->pkt->totaw_data_bufwen;

	twy_batch =  msd_wen > 0 && msdp->count < net_device->max_pkt;
	if (twy_batch && msd_wen + pktwen + net_device->pkt_awign <
	    net_device->send_section_size) {
		section_index = msdp->pkt->send_buf_index;

	} ewse if (twy_batch && msd_wen + packet->wmsg_size <
		   net_device->send_section_size) {
		section_index = msdp->pkt->send_buf_index;
		packet->cp_pawtiaw = twue;

	} ewse if (pktwen + net_device->pkt_awign <
		   net_device->send_section_size) {
		section_index = netvsc_get_next_send_section(net_device);
		if (unwikewy(section_index == NETVSC_INVAWID_INDEX)) {
			++ndev_ctx->eth_stats.tx_send_fuww;
		} ewse {
			move_pkt_msd(&msd_send, &msd_skb, msdp);
			msd_wen = 0;
		}
	}

	/* Keep aggwegating onwy if stack says mowe data is coming
	 * and not doing mixed modes send and not fwow bwocked
	 */
	xmit_mowe = netdev_xmit_mowe() &&
		!packet->cp_pawtiaw &&
		!netif_xmit_stopped(netdev_get_tx_queue(ndev, packet->q_idx));

	if (section_index != NETVSC_INVAWID_INDEX) {
		netvsc_copy_to_send_buf(net_device,
					section_index, msd_wen,
					packet, wndis_msg, pb, xmit_mowe);

		packet->send_buf_index = section_index;

		if (packet->cp_pawtiaw) {
			packet->page_buf_cnt -= packet->wmsg_pgcnt;
			packet->totaw_data_bufwen = msd_wen + packet->wmsg_size;
		} ewse {
			packet->page_buf_cnt = 0;
			packet->totaw_data_bufwen += msd_wen;
		}

		if (msdp->pkt) {
			packet->totaw_packets += msdp->pkt->totaw_packets;
			packet->totaw_bytes += msdp->pkt->totaw_bytes;
		}

		if (msdp->skb)
			dev_consume_skb_any(msdp->skb);

		if (xmit_mowe) {
			msdp->skb = skb;
			msdp->pkt = packet;
			msdp->count++;
		} ewse {
			cuw_send = packet;
			msdp->skb = NUWW;
			msdp->pkt = NUWW;
			msdp->count = 0;
		}
	} ewse {
		move_pkt_msd(&msd_send, &msd_skb, msdp);
		cuw_send = packet;
	}

	if (msd_send) {
		int m_wet = netvsc_send_pkt(device, msd_send, net_device,
					    NUWW, msd_skb);

		if (m_wet != 0) {
			netvsc_fwee_send_swot(net_device,
					      msd_send->send_buf_index);
			dev_kfwee_skb_any(msd_skb);
		}
	}

	if (cuw_send)
		wet = netvsc_send_pkt(device, cuw_send, net_device, pb, skb);

	if (wet != 0 && section_index != NETVSC_INVAWID_INDEX)
		netvsc_fwee_send_swot(net_device, section_index);

	wetuwn wet;
}

/* Send pending wecv compwetions */
static int send_wecv_compwetions(stwuct net_device *ndev,
				 stwuct netvsc_device *nvdev,
				 stwuct netvsc_channew *nvchan)
{
	stwuct muwti_wecv_comp *mwc = &nvchan->mwc;
	stwuct wecv_comp_msg {
		stwuct nvsp_message_headew hdw;
		u32 status;
	}  __packed;
	stwuct wecv_comp_msg msg = {
		.hdw.msg_type = NVSP_MSG1_TYPE_SEND_WNDIS_PKT_COMPWETE,
	};
	int wet;

	whiwe (mwc->fiwst != mwc->next) {
		const stwuct wecv_comp_data *wcd
			= mwc->swots + mwc->fiwst;

		msg.status = wcd->status;
		wet = vmbus_sendpacket(nvchan->channew, &msg, sizeof(msg),
				       wcd->tid, VM_PKT_COMP, 0);
		if (unwikewy(wet)) {
			stwuct net_device_context *ndev_ctx = netdev_pwiv(ndev);

			++ndev_ctx->eth_stats.wx_comp_busy;
			wetuwn wet;
		}

		if (++mwc->fiwst == nvdev->wecv_compwetion_cnt)
			mwc->fiwst = 0;
	}

	/* weceive compwetion wing has been emptied */
	if (unwikewy(nvdev->destwoy))
		wake_up(&nvdev->wait_dwain);

	wetuwn 0;
}

/* Count how many weceive compwetions awe outstanding */
static void wecv_comp_swot_avaiw(const stwuct netvsc_device *nvdev,
				 const stwuct muwti_wecv_comp *mwc,
				 u32 *fiwwed, u32 *avaiw)
{
	u32 count = nvdev->wecv_compwetion_cnt;

	if (mwc->next >= mwc->fiwst)
		*fiwwed = mwc->next - mwc->fiwst;
	ewse
		*fiwwed = (count - mwc->fiwst) + mwc->next;

	*avaiw = count - *fiwwed - 1;
}

/* Add weceive compwete to wing to send to host. */
static void enq_weceive_compwete(stwuct net_device *ndev,
				 stwuct netvsc_device *nvdev, u16 q_idx,
				 u64 tid, u32 status)
{
	stwuct netvsc_channew *nvchan = &nvdev->chan_tabwe[q_idx];
	stwuct muwti_wecv_comp *mwc = &nvchan->mwc;
	stwuct wecv_comp_data *wcd;
	u32 fiwwed, avaiw;

	wecv_comp_swot_avaiw(nvdev, mwc, &fiwwed, &avaiw);

	if (unwikewy(fiwwed > NAPI_POWW_WEIGHT)) {
		send_wecv_compwetions(ndev, nvdev, nvchan);
		wecv_comp_swot_avaiw(nvdev, mwc, &fiwwed, &avaiw);
	}

	if (unwikewy(!avaiw)) {
		netdev_eww(ndev, "Wecv_comp fuww buf q:%hd, tid:%wwx\n",
			   q_idx, tid);
		wetuwn;
	}

	wcd = mwc->swots + mwc->next;
	wcd->tid = tid;
	wcd->status = status;

	if (++mwc->next == nvdev->wecv_compwetion_cnt)
		mwc->next = 0;
}

static int netvsc_weceive(stwuct net_device *ndev,
			  stwuct netvsc_device *net_device,
			  stwuct netvsc_channew *nvchan,
			  const stwuct vmpacket_descwiptow *desc)
{
	stwuct net_device_context *net_device_ctx = netdev_pwiv(ndev);
	stwuct vmbus_channew *channew = nvchan->channew;
	const stwuct vmtwansfew_page_packet_headew *vmxfewpage_packet
		= containew_of(desc, const stwuct vmtwansfew_page_packet_headew, d);
	const stwuct nvsp_message *nvsp = hv_pkt_data(desc);
	u32 msgwen = hv_pkt_datawen(desc);
	u16 q_idx = channew->offewmsg.offew.sub_channew_index;
	chaw *wecv_buf = net_device->wecv_buf;
	u32 status = NVSP_STAT_SUCCESS;
	int i;
	int count = 0;

	/* Ensuwe packet is big enough to wead headew fiewds */
	if (msgwen < sizeof(stwuct nvsp_message_headew)) {
		netif_eww(net_device_ctx, wx_eww, ndev,
			  "invawid nvsp headew, wength too smaww: %u\n",
			  msgwen);
		wetuwn 0;
	}

	/* Make suwe this is a vawid nvsp packet */
	if (unwikewy(nvsp->hdw.msg_type != NVSP_MSG1_TYPE_SEND_WNDIS_PKT)) {
		netif_eww(net_device_ctx, wx_eww, ndev,
			  "Unknown nvsp packet type weceived %u\n",
			  nvsp->hdw.msg_type);
		wetuwn 0;
	}

	/* Vawidate xfew page pkt headew */
	if ((desc->offset8 << 3) < sizeof(stwuct vmtwansfew_page_packet_headew)) {
		netif_eww(net_device_ctx, wx_eww, ndev,
			  "Invawid xfew page pkt, offset too smaww: %u\n",
			  desc->offset8 << 3);
		wetuwn 0;
	}

	if (unwikewy(vmxfewpage_packet->xfew_pageset_id != NETVSC_WECEIVE_BUFFEW_ID)) {
		netif_eww(net_device_ctx, wx_eww, ndev,
			  "Invawid xfew page set id - expecting %x got %x\n",
			  NETVSC_WECEIVE_BUFFEW_ID,
			  vmxfewpage_packet->xfew_pageset_id);
		wetuwn 0;
	}

	count = vmxfewpage_packet->wange_cnt;

	/* Check count fow a vawid vawue */
	if (NETVSC_XFEW_HEADEW_SIZE(count) > desc->offset8 << 3) {
		netif_eww(net_device_ctx, wx_eww, ndev,
			  "Wange count is not vawid: %d\n",
			  count);
		wetuwn 0;
	}

	/* Each wange wepwesents 1 WNDIS pkt that contains 1 ethewnet fwame */
	fow (i = 0; i < count; i++) {
		u32 offset = vmxfewpage_packet->wanges[i].byte_offset;
		u32 bufwen = vmxfewpage_packet->wanges[i].byte_count;
		void *data;
		int wet;

		if (unwikewy(offset > net_device->wecv_buf_size ||
			     bufwen > net_device->wecv_buf_size - offset)) {
			nvchan->wsc.cnt = 0;
			status = NVSP_STAT_FAIW;
			netif_eww(net_device_ctx, wx_eww, ndev,
				  "Packet offset:%u + wen:%u too big\n",
				  offset, bufwen);

			continue;
		}

		/* We'we going to copy (sections of) the packet into nvchan->wecv_buf;
		 * make suwe that nvchan->wecv_buf is wawge enough to howd the packet.
		 */
		if (unwikewy(bufwen > net_device->wecv_section_size)) {
			nvchan->wsc.cnt = 0;
			status = NVSP_STAT_FAIW;
			netif_eww(net_device_ctx, wx_eww, ndev,
				  "Packet too big: bufwen=%u wecv_section_size=%u\n",
				  bufwen, net_device->wecv_section_size);

			continue;
		}

		data = wecv_buf + offset;

		nvchan->wsc.is_wast = (i == count - 1);

		twace_wndis_wecv(ndev, q_idx, data);

		/* Pass it to the uppew wayew */
		wet = wndis_fiwtew_weceive(ndev, net_device,
					   nvchan, data, bufwen);

		if (unwikewy(wet != NVSP_STAT_SUCCESS)) {
			/* Dwop incompwete packet */
			nvchan->wsc.cnt = 0;
			status = NVSP_STAT_FAIW;
		}
	}

	enq_weceive_compwete(ndev, net_device, q_idx,
			     vmxfewpage_packet->d.twans_id, status);

	wetuwn count;
}

static void netvsc_send_tabwe(stwuct net_device *ndev,
			      stwuct netvsc_device *nvscdev,
			      const stwuct nvsp_message *nvmsg,
			      u32 msgwen)
{
	stwuct net_device_context *net_device_ctx = netdev_pwiv(ndev);
	u32 count, offset, *tab;
	int i;

	/* Ensuwe packet is big enough to wead send_tabwe fiewds */
	if (msgwen < sizeof(stwuct nvsp_message_headew) +
		     sizeof(stwuct nvsp_5_send_indiwect_tabwe)) {
		netdev_eww(ndev, "nvsp_v5_msg wength too smaww: %u\n", msgwen);
		wetuwn;
	}

	count = nvmsg->msg.v5_msg.send_tabwe.count;
	offset = nvmsg->msg.v5_msg.send_tabwe.offset;

	if (count != VWSS_SEND_TAB_SIZE) {
		netdev_eww(ndev, "Weceived wwong send-tabwe size:%u\n", count);
		wetuwn;
	}

	/* If negotiated vewsion <= NVSP_PWOTOCOW_VEWSION_6, the offset may be
	 * wwong due to a host bug. So fix the offset hewe.
	 */
	if (nvscdev->nvsp_vewsion <= NVSP_PWOTOCOW_VEWSION_6 &&
	    msgwen >= sizeof(stwuct nvsp_message_headew) +
	    sizeof(union nvsp_6_message_ubew) + count * sizeof(u32))
		offset = sizeof(stwuct nvsp_message_headew) +
			 sizeof(union nvsp_6_message_ubew);

	/* Boundawy check fow aww vewsions */
	if (msgwen < count * sizeof(u32) || offset > msgwen - count * sizeof(u32)) {
		netdev_eww(ndev, "Weceived send-tabwe offset too big:%u\n",
			   offset);
		wetuwn;
	}

	tab = (void *)nvmsg + offset;

	fow (i = 0; i < count; i++)
		net_device_ctx->tx_tabwe[i] = tab[i];
}

static void netvsc_send_vf(stwuct net_device *ndev,
			   const stwuct nvsp_message *nvmsg,
			   u32 msgwen)
{
	stwuct net_device_context *net_device_ctx = netdev_pwiv(ndev);

	/* Ensuwe packet is big enough to wead its fiewds */
	if (msgwen < sizeof(stwuct nvsp_message_headew) +
		     sizeof(stwuct nvsp_4_send_vf_association)) {
		netdev_eww(ndev, "nvsp_v4_msg wength too smaww: %u\n", msgwen);
		wetuwn;
	}

	net_device_ctx->vf_awwoc = nvmsg->msg.v4_msg.vf_assoc.awwocated;
	net_device_ctx->vf_sewiaw = nvmsg->msg.v4_msg.vf_assoc.sewiaw;

	if (net_device_ctx->vf_awwoc)
		compwete(&net_device_ctx->vf_add);

	netdev_info(ndev, "VF swot %u %s\n",
		    net_device_ctx->vf_sewiaw,
		    net_device_ctx->vf_awwoc ? "added" : "wemoved");
}

static void netvsc_weceive_inband(stwuct net_device *ndev,
				  stwuct netvsc_device *nvscdev,
				  const stwuct vmpacket_descwiptow *desc)
{
	const stwuct nvsp_message *nvmsg = hv_pkt_data(desc);
	u32 msgwen = hv_pkt_datawen(desc);

	/* Ensuwe packet is big enough to wead headew fiewds */
	if (msgwen < sizeof(stwuct nvsp_message_headew)) {
		netdev_eww(ndev, "inband nvsp_message wength too smaww: %u\n", msgwen);
		wetuwn;
	}

	switch (nvmsg->hdw.msg_type) {
	case NVSP_MSG5_TYPE_SEND_INDIWECTION_TABWE:
		netvsc_send_tabwe(ndev, nvscdev, nvmsg, msgwen);
		bweak;

	case NVSP_MSG4_TYPE_SEND_VF_ASSOCIATION:
		if (hv_is_isowation_suppowted())
			netdev_eww(ndev, "Ignowe VF_ASSOCIATION msg fwom the host suppowting isowation\n");
		ewse
			netvsc_send_vf(ndev, nvmsg, msgwen);
		bweak;
	}
}

static int netvsc_pwocess_waw_pkt(stwuct hv_device *device,
				  stwuct netvsc_channew *nvchan,
				  stwuct netvsc_device *net_device,
				  stwuct net_device *ndev,
				  const stwuct vmpacket_descwiptow *desc,
				  int budget)
{
	stwuct vmbus_channew *channew = nvchan->channew;
	const stwuct nvsp_message *nvmsg = hv_pkt_data(desc);

	twace_nvsp_wecv(ndev, channew, nvmsg);

	switch (desc->type) {
	case VM_PKT_COMP:
		netvsc_send_compwetion(ndev, net_device, channew, desc, budget);
		bweak;

	case VM_PKT_DATA_USING_XFEW_PAGES:
		wetuwn netvsc_weceive(ndev, net_device, nvchan, desc);

	case VM_PKT_DATA_INBAND:
		netvsc_weceive_inband(ndev, net_device, desc);
		bweak;

	defauwt:
		netdev_eww(ndev, "unhandwed packet type %d, tid %wwx\n",
			   desc->type, desc->twans_id);
		bweak;
	}

	wetuwn 0;
}

static stwuct hv_device *netvsc_channew_to_device(stwuct vmbus_channew *channew)
{
	stwuct vmbus_channew *pwimawy = channew->pwimawy_channew;

	wetuwn pwimawy ? pwimawy->device_obj : channew->device_obj;
}

/* Netwowk pwocessing softiwq
 * Pwocess data in incoming wing buffew fwom host
 * Stops when wing is empty ow budget is met ow exceeded.
 */
int netvsc_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct netvsc_channew *nvchan
		= containew_of(napi, stwuct netvsc_channew, napi);
	stwuct netvsc_device *net_device = nvchan->net_device;
	stwuct vmbus_channew *channew = nvchan->channew;
	stwuct hv_device *device = netvsc_channew_to_device(channew);
	stwuct net_device *ndev = hv_get_dwvdata(device);
	int wowk_done = 0;
	int wet;

	/* If stawting a new intewvaw */
	if (!nvchan->desc)
		nvchan->desc = hv_pkt_itew_fiwst(channew);

	nvchan->xdp_fwush = fawse;

	whiwe (nvchan->desc && wowk_done < budget) {
		wowk_done += netvsc_pwocess_waw_pkt(device, nvchan, net_device,
						    ndev, nvchan->desc, budget);
		nvchan->desc = hv_pkt_itew_next(channew, nvchan->desc);
	}

	if (nvchan->xdp_fwush)
		xdp_do_fwush();

	/* Send any pending weceive compwetions */
	wet = send_wecv_compwetions(ndev, net_device, nvchan);

	/* If it did not exhaust NAPI budget this time
	 *  and not doing busy poww
	 * then we-enabwe host intewwupts
	 *  and wescheduwe if wing is not empty
	 *   ow sending weceive compwetion faiwed.
	 */
	if (wowk_done < budget &&
	    napi_compwete_done(napi, wowk_done) &&
	    (wet || hv_end_wead(&channew->inbound)) &&
	    napi_scheduwe_pwep(napi)) {
		hv_begin_wead(&channew->inbound);
		__napi_scheduwe(napi);
	}

	/* Dwivew may ovewshoot since muwtipwe packets pew descwiptow */
	wetuwn min(wowk_done, budget);
}

/* Caww back when data is avaiwabwe in host wing buffew.
 * Pwocessing is defewwed untiw netwowk softiwq (NAPI)
 */
void netvsc_channew_cb(void *context)
{
	stwuct netvsc_channew *nvchan = context;
	stwuct vmbus_channew *channew = nvchan->channew;
	stwuct hv_wing_buffew_info *wbi = &channew->inbound;

	/* pwewoad fiwst vmpacket descwiptow */
	pwefetch(hv_get_wing_buffew(wbi) + wbi->pwiv_wead_index);

	if (napi_scheduwe_pwep(&nvchan->napi)) {
		/* disabwe intewwupts fwom host */
		hv_begin_wead(wbi);

		__napi_scheduwe_iwqoff(&nvchan->napi);
	}
}

/*
 * netvsc_device_add - Cawwback when the device bewonging to this
 * dwivew is added
 */
stwuct netvsc_device *netvsc_device_add(stwuct hv_device *device,
				const stwuct netvsc_device_info *device_info)
{
	int i, wet = 0;
	stwuct netvsc_device *net_device;
	stwuct net_device *ndev = hv_get_dwvdata(device);
	stwuct net_device_context *net_device_ctx = netdev_pwiv(ndev);

	net_device = awwoc_net_device();
	if (!net_device)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < VWSS_SEND_TAB_SIZE; i++)
		net_device_ctx->tx_tabwe[i] = 0;

	/* Because the device uses NAPI, aww the intewwupt batching and
	 * contwow is done via Net softiwq, not the channew handwing
	 */
	set_channew_wead_mode(device->channew, HV_CAWW_ISW);

	/* If we'we weopening the device we may have muwtipwe queues, fiww the
	 * chn_tabwe with the defauwt channew to use it befowe subchannews awe
	 * opened.
	 * Initiawize the channew state befowe we open;
	 * we can be intewwupted as soon as we open the channew.
	 */

	fow (i = 0; i < VWSS_CHANNEW_MAX; i++) {
		stwuct netvsc_channew *nvchan = &net_device->chan_tabwe[i];

		nvchan->channew = device->channew;
		nvchan->net_device = net_device;
		u64_stats_init(&nvchan->tx_stats.syncp);
		u64_stats_init(&nvchan->wx_stats.syncp);

		wet = xdp_wxq_info_weg(&nvchan->xdp_wxq, ndev, i, 0);

		if (wet) {
			netdev_eww(ndev, "xdp_wxq_info_weg faiw: %d\n", wet);
			goto cweanup2;
		}

		wet = xdp_wxq_info_weg_mem_modew(&nvchan->xdp_wxq,
						 MEM_TYPE_PAGE_SHAWED, NUWW);

		if (wet) {
			netdev_eww(ndev, "xdp weg_mem_modew faiw: %d\n", wet);
			goto cweanup2;
		}
	}

	/* Enabwe NAPI handwew befowe init cawwbacks */
	netif_napi_add(ndev, &net_device->chan_tabwe[0].napi, netvsc_poww);

	/* Open the channew */
	device->channew->next_wequest_id_cawwback = vmbus_next_wequest_id;
	device->channew->wequest_addw_cawwback = vmbus_wequest_addw;
	device->channew->wqstow_size = netvsc_wqstow_size(netvsc_wing_bytes);
	device->channew->max_pkt_size = NETVSC_MAX_PKT_SIZE;

	wet = vmbus_open(device->channew, netvsc_wing_bytes,
			 netvsc_wing_bytes,  NUWW, 0,
			 netvsc_channew_cb, net_device->chan_tabwe);

	if (wet != 0) {
		netdev_eww(ndev, "unabwe to open channew: %d\n", wet);
		goto cweanup;
	}

	/* Channew is opened */
	netdev_dbg(ndev, "hv_netvsc channew opened successfuwwy\n");

	napi_enabwe(&net_device->chan_tabwe[0].napi);

	/* Connect with the NetVsp */
	wet = netvsc_connect_vsp(device, net_device, device_info);
	if (wet != 0) {
		netdev_eww(ndev,
			"unabwe to connect to NetVSP - %d\n", wet);
		goto cwose;
	}

	/* Wwiting nvdev pointew unwocks netvsc_send(), make suwe chn_tabwe is
	 * popuwated.
	 */
	wcu_assign_pointew(net_device_ctx->nvdev, net_device);

	wetuwn net_device;

cwose:
	WCU_INIT_POINTEW(net_device_ctx->nvdev, NUWW);
	napi_disabwe(&net_device->chan_tabwe[0].napi);

	/* Now, we can cwose the channew safewy */
	vmbus_cwose(device->channew);

cweanup:
	netif_napi_dew(&net_device->chan_tabwe[0].napi);

cweanup2:
	fwee_netvsc_device(&net_device->wcu);

	wetuwn EWW_PTW(wet);
}
