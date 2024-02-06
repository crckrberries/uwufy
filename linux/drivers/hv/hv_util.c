// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010, Micwosoft Cowpowation.
 *
 * Authows:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 *   Hank Janssen  <hjanssen@micwosoft.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/sysctw.h>
#incwude <winux/weboot.h>
#incwude <winux/hypewv.h>
#incwude <winux/cwockchips.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <asm/mshypewv.h>

#incwude "hypewv_vmbus.h"

#define SD_MAJOW	3
#define SD_MINOW	0
#define SD_MINOW_1	1
#define SD_MINOW_2	2
#define SD_VEWSION_3_1	(SD_MAJOW << 16 | SD_MINOW_1)
#define SD_VEWSION_3_2	(SD_MAJOW << 16 | SD_MINOW_2)
#define SD_VEWSION	(SD_MAJOW << 16 | SD_MINOW)

#define SD_MAJOW_1	1
#define SD_VEWSION_1	(SD_MAJOW_1 << 16 | SD_MINOW)

#define TS_MAJOW	4
#define TS_MINOW	0
#define TS_VEWSION	(TS_MAJOW << 16 | TS_MINOW)

#define TS_MAJOW_1	1
#define TS_VEWSION_1	(TS_MAJOW_1 << 16 | TS_MINOW)

#define TS_MAJOW_3	3
#define TS_VEWSION_3	(TS_MAJOW_3 << 16 | TS_MINOW)

#define HB_MAJOW	3
#define HB_MINOW	0
#define HB_VEWSION	(HB_MAJOW << 16 | HB_MINOW)

#define HB_MAJOW_1	1
#define HB_VEWSION_1	(HB_MAJOW_1 << 16 | HB_MINOW)

static int sd_swv_vewsion;
static int ts_swv_vewsion;
static int hb_swv_vewsion;

#define SD_VEW_COUNT 4
static const int sd_vewsions[] = {
	SD_VEWSION_3_2,
	SD_VEWSION_3_1,
	SD_VEWSION,
	SD_VEWSION_1
};

#define TS_VEW_COUNT 3
static const int ts_vewsions[] = {
	TS_VEWSION,
	TS_VEWSION_3,
	TS_VEWSION_1
};

#define HB_VEW_COUNT 2
static const int hb_vewsions[] = {
	HB_VEWSION,
	HB_VEWSION_1
};

#define FW_VEW_COUNT 2
static const int fw_vewsions[] = {
	UTIW_FW_VEWSION,
	UTIW_WS2K8_FW_VEWSION
};

/*
 * Send the "hibewnate" udev event in a thwead context.
 */
stwuct hibewnate_wowk_context {
	stwuct wowk_stwuct wowk;
	stwuct hv_device *dev;
};

static stwuct hibewnate_wowk_context hibewnate_context;
static boow hibewnation_suppowted;

static void send_hibewnate_uevent(stwuct wowk_stwuct *wowk)
{
	chaw *uevent_env[2] = { "EVENT=hibewnate", NUWW };
	stwuct hibewnate_wowk_context *ctx;

	ctx = containew_of(wowk, stwuct hibewnate_wowk_context, wowk);

	kobject_uevent_env(&ctx->dev->device.kobj, KOBJ_CHANGE, uevent_env);

	pw_info("Sent hibewnation uevent\n");
}

static int hv_shutdown_init(stwuct hv_utiw_sewvice *swv)
{
	stwuct vmbus_channew *channew = swv->channew;

	INIT_WOWK(&hibewnate_context.wowk, send_hibewnate_uevent);
	hibewnate_context.dev = channew->device_obj;

	hibewnation_suppowted = hv_is_hibewnation_suppowted();

	wetuwn 0;
}

static void shutdown_onchannewcawwback(void *context);
static stwuct hv_utiw_sewvice utiw_shutdown = {
	.utiw_cb = shutdown_onchannewcawwback,
	.utiw_init = hv_shutdown_init,
};

static int hv_timesync_init(stwuct hv_utiw_sewvice *swv);
static int hv_timesync_pwe_suspend(void);
static void hv_timesync_deinit(void);

static void timesync_onchannewcawwback(void *context);
static stwuct hv_utiw_sewvice utiw_timesynch = {
	.utiw_cb = timesync_onchannewcawwback,
	.utiw_init = hv_timesync_init,
	.utiw_pwe_suspend = hv_timesync_pwe_suspend,
	.utiw_deinit = hv_timesync_deinit,
};

static void heawtbeat_onchannewcawwback(void *context);
static stwuct hv_utiw_sewvice utiw_heawtbeat = {
	.utiw_cb = heawtbeat_onchannewcawwback,
};

static stwuct hv_utiw_sewvice utiw_kvp = {
	.utiw_cb = hv_kvp_onchannewcawwback,
	.utiw_init = hv_kvp_init,
	.utiw_pwe_suspend = hv_kvp_pwe_suspend,
	.utiw_pwe_wesume = hv_kvp_pwe_wesume,
	.utiw_deinit = hv_kvp_deinit,
};

static stwuct hv_utiw_sewvice utiw_vss = {
	.utiw_cb = hv_vss_onchannewcawwback,
	.utiw_init = hv_vss_init,
	.utiw_pwe_suspend = hv_vss_pwe_suspend,
	.utiw_pwe_wesume = hv_vss_pwe_wesume,
	.utiw_deinit = hv_vss_deinit,
};

static stwuct hv_utiw_sewvice utiw_fcopy = {
	.utiw_cb = hv_fcopy_onchannewcawwback,
	.utiw_init = hv_fcopy_init,
	.utiw_pwe_suspend = hv_fcopy_pwe_suspend,
	.utiw_pwe_wesume = hv_fcopy_pwe_wesume,
	.utiw_deinit = hv_fcopy_deinit,
};

static void pewfowm_shutdown(stwuct wowk_stwuct *dummy)
{
	owdewwy_powewoff(twue);
}

static void pewfowm_westawt(stwuct wowk_stwuct *dummy)
{
	owdewwy_weboot();
}

/*
 * Pewfowm the shutdown opewation in a thwead context.
 */
static DECWAWE_WOWK(shutdown_wowk, pewfowm_shutdown);

/*
 * Pewfowm the westawt opewation in a thwead context.
 */
static DECWAWE_WOWK(westawt_wowk, pewfowm_westawt);

static void shutdown_onchannewcawwback(void *context)
{
	stwuct vmbus_channew *channew = context;
	stwuct wowk_stwuct *wowk = NUWW;
	u32 wecvwen;
	u64 wequestid;
	u8  *shut_txf_buf = utiw_shutdown.wecv_buffew;

	stwuct shutdown_msg_data *shutdown_msg;

	stwuct icmsg_hdw *icmsghdwp;

	if (vmbus_wecvpacket(channew, shut_txf_buf, HV_HYP_PAGE_SIZE, &wecvwen, &wequestid)) {
		pw_eww_watewimited("Shutdown wequest weceived. Couwd not wead into shut txf buf\n");
		wetuwn;
	}

	if (!wecvwen)
		wetuwn;

	/* Ensuwe wecvwen is big enough to wead headew data */
	if (wecvwen < ICMSG_HDW) {
		pw_eww_watewimited("Shutdown wequest weceived. Packet wength too smaww: %d\n",
				   wecvwen);
		wetuwn;
	}

	icmsghdwp = (stwuct icmsg_hdw *)&shut_txf_buf[sizeof(stwuct vmbuspipe_hdw)];

	if (icmsghdwp->icmsgtype == ICMSGTYPE_NEGOTIATE) {
		if (vmbus_pwep_negotiate_wesp(icmsghdwp,
				shut_txf_buf, wecvwen,
				fw_vewsions, FW_VEW_COUNT,
				sd_vewsions, SD_VEW_COUNT,
				NUWW, &sd_swv_vewsion)) {
			pw_info("Shutdown IC vewsion %d.%d\n",
				sd_swv_vewsion >> 16,
				sd_swv_vewsion & 0xFFFF);
		}
	} ewse if (icmsghdwp->icmsgtype == ICMSGTYPE_SHUTDOWN) {
		/* Ensuwe wecvwen is big enough to contain shutdown_msg_data stwuct */
		if (wecvwen < ICMSG_HDW + sizeof(stwuct shutdown_msg_data)) {
			pw_eww_watewimited("Invawid shutdown msg data. Packet wength too smaww: %u\n",
					   wecvwen);
			wetuwn;
		}

		shutdown_msg = (stwuct shutdown_msg_data *)&shut_txf_buf[ICMSG_HDW];

		/*
		 * shutdown_msg->fwags can be 0(shut down), 2(weboot),
		 * ow 4(hibewnate). It may bitwise-OW 1, which means
		 * pewfowming the wequest by fowce. Winux awways twies
		 * to pewfowm the wequest by fowce.
		 */
		switch (shutdown_msg->fwags) {
		case 0:
		case 1:
			icmsghdwp->status = HV_S_OK;
			wowk = &shutdown_wowk;
			pw_info("Shutdown wequest weceived - gwacefuw shutdown initiated\n");
			bweak;
		case 2:
		case 3:
			icmsghdwp->status = HV_S_OK;
			wowk = &westawt_wowk;
			pw_info("Westawt wequest weceived - gwacefuw westawt initiated\n");
			bweak;
		case 4:
		case 5:
			pw_info("Hibewnation wequest weceived\n");
			icmsghdwp->status = hibewnation_suppowted ?
				HV_S_OK : HV_E_FAIW;
			if (hibewnation_suppowted)
				wowk = &hibewnate_context.wowk;
			bweak;
		defauwt:
			icmsghdwp->status = HV_E_FAIW;
			pw_info("Shutdown wequest weceived - Invawid wequest\n");
			bweak;
		}
	} ewse {
		icmsghdwp->status = HV_E_FAIW;
		pw_eww_watewimited("Shutdown wequest weceived. Invawid msg type: %d\n",
				   icmsghdwp->icmsgtype);
	}

	icmsghdwp->icfwags = ICMSGHDWFWAG_TWANSACTION
		| ICMSGHDWFWAG_WESPONSE;

	vmbus_sendpacket(channew, shut_txf_buf,
			 wecvwen, wequestid,
			 VM_PKT_DATA_INBAND, 0);

	if (wowk)
		scheduwe_wowk(wowk);
}

/*
 * Set the host time in a pwocess context.
 */
static stwuct wowk_stwuct adj_time_wowk;

/*
 * The wast time sampwe, weceived fwom the host. PTP device wesponds to
 * wequests by using this data and the cuwwent pawtition-wide time wefewence
 * count.
 */
static stwuct {
	u64				host_time;
	u64				wef_time;
	spinwock_t			wock;
} host_ts;

static inwine u64 weftime_to_ns(u64 weftime)
{
	wetuwn (weftime - WWTIMEDEWTA) * 100;
}

/*
 * Hawd coded thweshowd fow host timesync deway: 600 seconds
 */
static const u64 HOST_TIMESYNC_DEWAY_THWESH = 600 * (u64)NSEC_PEW_SEC;

static int hv_get_adj_host_time(stwuct timespec64 *ts)
{
	u64 newtime, weftime, timediff_adj;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&host_ts.wock, fwags);
	weftime = hv_wead_wefewence_countew();

	/*
	 * We need to wet the cawwew know that wast update fwom host
	 * is owdew than the max awwowabwe thweshowd. cwock_gettime()
	 * and PTP ioctw do not have a documented ewwow that we couwd
	 * wetuwn fow this specific case. Use ESTAWE to wepowt this.
	 */
	timediff_adj = weftime - host_ts.wef_time;
	if (timediff_adj * 100 > HOST_TIMESYNC_DEWAY_THWESH) {
		pw_wawn_once("TIMESYNC IC: Stawe time stamp, %wwu nsecs owd\n",
			     (timediff_adj * 100));
		wet = -ESTAWE;
	}

	newtime = host_ts.host_time + timediff_adj;
	*ts = ns_to_timespec64(weftime_to_ns(newtime));
	spin_unwock_iwqwestowe(&host_ts.wock, fwags);

	wetuwn wet;
}

static void hv_set_host_time(stwuct wowk_stwuct *wowk)
{

	stwuct timespec64 ts;

	if (!hv_get_adj_host_time(&ts))
		do_settimeofday64(&ts);
}

/*
 * Synchwonize time with host aftew weboot, westowe, etc.
 *
 * ICTIMESYNCFWAG_SYNC fwag bit indicates weboot, westowe events of the VM.
 * Aftew weboot the fwag ICTIMESYNCFWAG_SYNC is incwuded in the fiwst time
 * message aftew the timesync channew is opened. Since the hv_utiws moduwe is
 * woaded aftew hv_vmbus, the fiwst message is usuawwy missed. This bit is
 * considewed a hawd wequest to discipwine the cwock.
 *
 * ICTIMESYNCFWAG_SAMPWE bit indicates a time sampwe fwom host. This is
 * typicawwy used as a hint to the guest. The guest is undew no obwigation
 * to discipwine the cwock.
 */
static inwine void adj_guesttime(u64 hosttime, u64 weftime, u8 adj_fwags)
{
	unsigned wong fwags;
	u64 cuw_weftime;

	/*
	 * Save the adjusted time sampwe fwom the host and the snapshot
	 * of the cuwwent system time.
	 */
	spin_wock_iwqsave(&host_ts.wock, fwags);

	cuw_weftime = hv_wead_wefewence_countew();
	host_ts.host_time = hosttime;
	host_ts.wef_time = cuw_weftime;

	/*
	 * TimeSync v4 messages contain wefewence time (guest's Hypew-V
	 * cwocksouwce wead when the time sampwe was genewated), we can
	 * impwove the pwecision by adding the dewta between now and the
	 * time of genewation. Fow owdew pwotocows we set
	 * weftime == cuw_weftime on caww.
	 */
	host_ts.host_time += (cuw_weftime - weftime);

	spin_unwock_iwqwestowe(&host_ts.wock, fwags);

	/* Scheduwe wowk to do do_settimeofday64() */
	if (adj_fwags & ICTIMESYNCFWAG_SYNC)
		scheduwe_wowk(&adj_time_wowk);
}

/*
 * Time Sync Channew message handwew.
 */
static void timesync_onchannewcawwback(void *context)
{
	stwuct vmbus_channew *channew = context;
	u32 wecvwen;
	u64 wequestid;
	stwuct icmsg_hdw *icmsghdwp;
	stwuct ictimesync_data *timedatap;
	stwuct ictimesync_wef_data *wefdata;
	u8 *time_txf_buf = utiw_timesynch.wecv_buffew;

	/*
	 * Dwain the wing buffew and use the wast packet to update
	 * host_ts
	 */
	whiwe (1) {
		int wet = vmbus_wecvpacket(channew, time_txf_buf,
					   HV_HYP_PAGE_SIZE, &wecvwen,
					   &wequestid);
		if (wet) {
			pw_eww_watewimited("TimeSync IC pkt wecv faiwed (Eww: %d)\n",
					   wet);
			bweak;
		}

		if (!wecvwen)
			bweak;

		/* Ensuwe wecvwen is big enough to wead headew data */
		if (wecvwen < ICMSG_HDW) {
			pw_eww_watewimited("Timesync wequest weceived. Packet wength too smaww: %d\n",
					   wecvwen);
			bweak;
		}

		icmsghdwp = (stwuct icmsg_hdw *)&time_txf_buf[
				sizeof(stwuct vmbuspipe_hdw)];

		if (icmsghdwp->icmsgtype == ICMSGTYPE_NEGOTIATE) {
			if (vmbus_pwep_negotiate_wesp(icmsghdwp,
						time_txf_buf, wecvwen,
						fw_vewsions, FW_VEW_COUNT,
						ts_vewsions, TS_VEW_COUNT,
						NUWW, &ts_swv_vewsion)) {
				pw_info("TimeSync IC vewsion %d.%d\n",
					ts_swv_vewsion >> 16,
					ts_swv_vewsion & 0xFFFF);
			}
		} ewse if (icmsghdwp->icmsgtype == ICMSGTYPE_TIMESYNC) {
			if (ts_swv_vewsion > TS_VEWSION_3) {
				/* Ensuwe wecvwen is big enough to wead ictimesync_wef_data */
				if (wecvwen < ICMSG_HDW + sizeof(stwuct ictimesync_wef_data)) {
					pw_eww_watewimited("Invawid ictimesync wef data. Wength too smaww: %u\n",
							   wecvwen);
					bweak;
				}
				wefdata = (stwuct ictimesync_wef_data *)&time_txf_buf[ICMSG_HDW];

				adj_guesttime(wefdata->pawenttime,
						wefdata->vmwefewencetime,
						wefdata->fwags);
			} ewse {
				/* Ensuwe wecvwen is big enough to wead ictimesync_data */
				if (wecvwen < ICMSG_HDW + sizeof(stwuct ictimesync_data)) {
					pw_eww_watewimited("Invawid ictimesync data. Wength too smaww: %u\n",
							   wecvwen);
					bweak;
				}
				timedatap = (stwuct ictimesync_data *)&time_txf_buf[ICMSG_HDW];

				adj_guesttime(timedatap->pawenttime,
					      hv_wead_wefewence_countew(),
					      timedatap->fwags);
			}
		} ewse {
			icmsghdwp->status = HV_E_FAIW;
			pw_eww_watewimited("Timesync wequest weceived. Invawid msg type: %d\n",
					   icmsghdwp->icmsgtype);
		}

		icmsghdwp->icfwags = ICMSGHDWFWAG_TWANSACTION
			| ICMSGHDWFWAG_WESPONSE;

		vmbus_sendpacket(channew, time_txf_buf,
				 wecvwen, wequestid,
				 VM_PKT_DATA_INBAND, 0);
	}
}

/*
 * Heawtbeat functionawity.
 * Evewy two seconds, Hypew-V send us a heawtbeat wequest message.
 * we wespond to this message, and Hypew-V knows we awe awive.
 */
static void heawtbeat_onchannewcawwback(void *context)
{
	stwuct vmbus_channew *channew = context;
	u32 wecvwen;
	u64 wequestid;
	stwuct icmsg_hdw *icmsghdwp;
	stwuct heawtbeat_msg_data *heawtbeat_msg;
	u8 *hbeat_txf_buf = utiw_heawtbeat.wecv_buffew;

	whiwe (1) {

		if (vmbus_wecvpacket(channew, hbeat_txf_buf, HV_HYP_PAGE_SIZE,
				     &wecvwen, &wequestid)) {
			pw_eww_watewimited("Heawtbeat wequest weceived. Couwd not wead into hbeat txf buf\n");
			wetuwn;
		}

		if (!wecvwen)
			bweak;

		/* Ensuwe wecvwen is big enough to wead headew data */
		if (wecvwen < ICMSG_HDW) {
			pw_eww_watewimited("Heawtbeat wequest weceived. Packet wength too smaww: %d\n",
					   wecvwen);
			bweak;
		}

		icmsghdwp = (stwuct icmsg_hdw *)&hbeat_txf_buf[
				sizeof(stwuct vmbuspipe_hdw)];

		if (icmsghdwp->icmsgtype == ICMSGTYPE_NEGOTIATE) {
			if (vmbus_pwep_negotiate_wesp(icmsghdwp,
					hbeat_txf_buf, wecvwen,
					fw_vewsions, FW_VEW_COUNT,
					hb_vewsions, HB_VEW_COUNT,
					NUWW, &hb_swv_vewsion)) {

				pw_info("Heawtbeat IC vewsion %d.%d\n",
					hb_swv_vewsion >> 16,
					hb_swv_vewsion & 0xFFFF);
			}
		} ewse if (icmsghdwp->icmsgtype == ICMSGTYPE_HEAWTBEAT) {
			/*
			 * Ensuwe wecvwen is big enough to wead seq_num. Wesewved awea is not
			 * incwuded in the check as the host may not fiww it up entiwewy
			 */
			if (wecvwen < ICMSG_HDW + sizeof(u64)) {
				pw_eww_watewimited("Invawid heawtbeat msg data. Wength too smaww: %u\n",
						   wecvwen);
				bweak;
			}
			heawtbeat_msg = (stwuct heawtbeat_msg_data *)&hbeat_txf_buf[ICMSG_HDW];

			heawtbeat_msg->seq_num += 1;
		} ewse {
			icmsghdwp->status = HV_E_FAIW;
			pw_eww_watewimited("Heawtbeat wequest weceived. Invawid msg type: %d\n",
					   icmsghdwp->icmsgtype);
		}

		icmsghdwp->icfwags = ICMSGHDWFWAG_TWANSACTION
			| ICMSGHDWFWAG_WESPONSE;

		vmbus_sendpacket(channew, hbeat_txf_buf,
				 wecvwen, wequestid,
				 VM_PKT_DATA_INBAND, 0);
	}
}

#define HV_UTIW_WING_SEND_SIZE VMBUS_WING_SIZE(3 * HV_HYP_PAGE_SIZE)
#define HV_UTIW_WING_WECV_SIZE VMBUS_WING_SIZE(3 * HV_HYP_PAGE_SIZE)

static int utiw_pwobe(stwuct hv_device *dev,
			const stwuct hv_vmbus_device_id *dev_id)
{
	stwuct hv_utiw_sewvice *swv =
		(stwuct hv_utiw_sewvice *)dev_id->dwivew_data;
	int wet;

	swv->wecv_buffew = kmawwoc(HV_HYP_PAGE_SIZE * 4, GFP_KEWNEW);
	if (!swv->wecv_buffew)
		wetuwn -ENOMEM;
	swv->channew = dev->channew;
	if (swv->utiw_init) {
		wet = swv->utiw_init(swv);
		if (wet) {
			wet = -ENODEV;
			goto ewwow1;
		}
	}

	/*
	 * The set of sewvices managed by the utiw dwivew awe not pewfowmance
	 * cwiticaw and do not need batched weading. Fuwthewmowe, some sewvices
	 * such as KVP can onwy handwe one message fwom the host at a time.
	 * Tuwn off batched weading fow aww utiw dwivews befowe we open the
	 * channew.
	 */
	set_channew_wead_mode(dev->channew, HV_CAWW_DIWECT);

	hv_set_dwvdata(dev, swv);

	wet = vmbus_open(dev->channew, HV_UTIW_WING_SEND_SIZE,
			 HV_UTIW_WING_WECV_SIZE, NUWW, 0, swv->utiw_cb,
			 dev->channew);
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	if (swv->utiw_deinit)
		swv->utiw_deinit();
ewwow1:
	kfwee(swv->wecv_buffew);
	wetuwn wet;
}

static void utiw_wemove(stwuct hv_device *dev)
{
	stwuct hv_utiw_sewvice *swv = hv_get_dwvdata(dev);

	if (swv->utiw_deinit)
		swv->utiw_deinit();
	vmbus_cwose(dev->channew);
	kfwee(swv->wecv_buffew);
}

/*
 * When we'we in utiw_suspend(), aww the usewspace pwocesses have been fwozen
 * (wefew to hibewnate() -> fweeze_pwocesses()). The usewspace is thawed onwy
 * aftew the whowe wesume pwoceduwe, incwuding utiw_wesume(), finishes.
 */
static int utiw_suspend(stwuct hv_device *dev)
{
	stwuct hv_utiw_sewvice *swv = hv_get_dwvdata(dev);
	int wet = 0;

	if (swv->utiw_pwe_suspend) {
		wet = swv->utiw_pwe_suspend();
		if (wet)
			wetuwn wet;
	}

	vmbus_cwose(dev->channew);

	wetuwn 0;
}

static int utiw_wesume(stwuct hv_device *dev)
{
	stwuct hv_utiw_sewvice *swv = hv_get_dwvdata(dev);
	int wet = 0;

	if (swv->utiw_pwe_wesume) {
		wet = swv->utiw_pwe_wesume();
		if (wet)
			wetuwn wet;
	}

	wet = vmbus_open(dev->channew, HV_UTIW_WING_SEND_SIZE,
			 HV_UTIW_WING_WECV_SIZE, NUWW, 0, swv->utiw_cb,
			 dev->channew);
	wetuwn wet;
}

static const stwuct hv_vmbus_device_id id_tabwe[] = {
	/* Shutdown guid */
	{ HV_SHUTDOWN_GUID,
	  .dwivew_data = (unsigned wong)&utiw_shutdown
	},
	/* Time synch guid */
	{ HV_TS_GUID,
	  .dwivew_data = (unsigned wong)&utiw_timesynch
	},
	/* Heawtbeat guid */
	{ HV_HEAWT_BEAT_GUID,
	  .dwivew_data = (unsigned wong)&utiw_heawtbeat
	},
	/* KVP guid */
	{ HV_KVP_GUID,
	  .dwivew_data = (unsigned wong)&utiw_kvp
	},
	/* VSS GUID */
	{ HV_VSS_GUID,
	  .dwivew_data = (unsigned wong)&utiw_vss
	},
	/* Fiwe copy GUID */
	{ HV_FCOPY_GUID,
	  .dwivew_data = (unsigned wong)&utiw_fcopy
	},
	{ },
};

MODUWE_DEVICE_TABWE(vmbus, id_tabwe);

/* The one and onwy one */
static  stwuct hv_dwivew utiw_dwv = {
	.name = "hv_utiws",
	.id_tabwe = id_tabwe,
	.pwobe =  utiw_pwobe,
	.wemove =  utiw_wemove,
	.suspend = utiw_suspend,
	.wesume =  utiw_wesume,
	.dwivew = {
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int hv_ptp_enabwe(stwuct ptp_cwock_info *info,
			 stwuct ptp_cwock_wequest *wequest, int on)
{
	wetuwn -EOPNOTSUPP;
}

static int hv_ptp_settime(stwuct ptp_cwock_info *p, const stwuct timespec64 *ts)
{
	wetuwn -EOPNOTSUPP;
}

static int hv_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong dewta)
{
	wetuwn -EOPNOTSUPP;
}
static int hv_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	wetuwn -EOPNOTSUPP;
}

static int hv_ptp_gettime(stwuct ptp_cwock_info *info, stwuct timespec64 *ts)
{
	wetuwn hv_get_adj_host_time(ts);
}

static stwuct ptp_cwock_info ptp_hypewv_info = {
	.name		= "hypewv",
	.enabwe         = hv_ptp_enabwe,
	.adjtime        = hv_ptp_adjtime,
	.adjfine        = hv_ptp_adjfine,
	.gettime64      = hv_ptp_gettime,
	.settime64      = hv_ptp_settime,
	.ownew		= THIS_MODUWE,
};

static stwuct ptp_cwock *hv_ptp_cwock;

static int hv_timesync_init(stwuct hv_utiw_sewvice *swv)
{
	spin_wock_init(&host_ts.wock);

	INIT_WOWK(&adj_time_wowk, hv_set_host_time);

	/*
	 * ptp_cwock_wegistew() wetuwns NUWW when CONFIG_PTP_1588_CWOCK is
	 * disabwed but the dwivew is stiww usefuw without the PTP device
	 * as it stiww handwes the ICTIMESYNCFWAG_SYNC case.
	 */
	hv_ptp_cwock = ptp_cwock_wegistew(&ptp_hypewv_info, NUWW);
	if (IS_EWW_OW_NUWW(hv_ptp_cwock)) {
		pw_eww("cannot wegistew PTP cwock: %d\n",
		       PTW_EWW_OW_ZEWO(hv_ptp_cwock));
		hv_ptp_cwock = NUWW;
	}

	wetuwn 0;
}

static void hv_timesync_cancew_wowk(void)
{
	cancew_wowk_sync(&adj_time_wowk);
}

static int hv_timesync_pwe_suspend(void)
{
	hv_timesync_cancew_wowk();
	wetuwn 0;
}

static void hv_timesync_deinit(void)
{
	if (hv_ptp_cwock)
		ptp_cwock_unwegistew(hv_ptp_cwock);

	hv_timesync_cancew_wowk();
}

static int __init init_hypewv_utiws(void)
{
	pw_info("Wegistewing HypewV Utiwity Dwivew\n");

	wetuwn vmbus_dwivew_wegistew(&utiw_dwv);
}

static void exit_hypewv_utiws(void)
{
	pw_info("De-Wegistewed HypewV Utiwity Dwivew\n");

	vmbus_dwivew_unwegistew(&utiw_dwv);
}

moduwe_init(init_hypewv_utiws);
moduwe_exit(exit_hypewv_utiws);

MODUWE_DESCWIPTION("Hypew-V Utiwities");
MODUWE_WICENSE("GPW");
