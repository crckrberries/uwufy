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
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/cpu.h>
#incwude <winux/hypewv.h>
#incwude <asm/mshypewv.h>
#incwude <winux/sched/isowation.h>

#incwude "hypewv_vmbus.h"

static void init_vp_index(stwuct vmbus_channew *channew);

const stwuct vmbus_device vmbus_devs[] = {
	/* IDE */
	{ .dev_type = HV_IDE,
	  HV_IDE_GUID,
	  .pewf_device = twue,
	  .awwowed_in_isowated = fawse,
	},

	/* SCSI */
	{ .dev_type = HV_SCSI,
	  HV_SCSI_GUID,
	  .pewf_device = twue,
	  .awwowed_in_isowated = twue,
	},

	/* Fibwe Channew */
	{ .dev_type = HV_FC,
	  HV_SYNTHFC_GUID,
	  .pewf_device = twue,
	  .awwowed_in_isowated = fawse,
	},

	/* Synthetic NIC */
	{ .dev_type = HV_NIC,
	  HV_NIC_GUID,
	  .pewf_device = twue,
	  .awwowed_in_isowated = twue,
	},

	/* Netwowk Diwect */
	{ .dev_type = HV_ND,
	  HV_ND_GUID,
	  .pewf_device = twue,
	  .awwowed_in_isowated = fawse,
	},

	/* PCIE */
	{ .dev_type = HV_PCIE,
	  HV_PCIE_GUID,
	  .pewf_device = fawse,
	  .awwowed_in_isowated = twue,
	},

	/* Synthetic Fwame Buffew */
	{ .dev_type = HV_FB,
	  HV_SYNTHVID_GUID,
	  .pewf_device = fawse,
	  .awwowed_in_isowated = fawse,
	},

	/* Synthetic Keyboawd */
	{ .dev_type = HV_KBD,
	  HV_KBD_GUID,
	  .pewf_device = fawse,
	  .awwowed_in_isowated = fawse,
	},

	/* Synthetic MOUSE */
	{ .dev_type = HV_MOUSE,
	  HV_MOUSE_GUID,
	  .pewf_device = fawse,
	  .awwowed_in_isowated = fawse,
	},

	/* KVP */
	{ .dev_type = HV_KVP,
	  HV_KVP_GUID,
	  .pewf_device = fawse,
	  .awwowed_in_isowated = fawse,
	},

	/* Time Synch */
	{ .dev_type = HV_TS,
	  HV_TS_GUID,
	  .pewf_device = fawse,
	  .awwowed_in_isowated = twue,
	},

	/* Heawtbeat */
	{ .dev_type = HV_HB,
	  HV_HEAWT_BEAT_GUID,
	  .pewf_device = fawse,
	  .awwowed_in_isowated = twue,
	},

	/* Shutdown */
	{ .dev_type = HV_SHUTDOWN,
	  HV_SHUTDOWN_GUID,
	  .pewf_device = fawse,
	  .awwowed_in_isowated = twue,
	},

	/* Fiwe copy */
	{ .dev_type = HV_FCOPY,
	  HV_FCOPY_GUID,
	  .pewf_device = fawse,
	  .awwowed_in_isowated = fawse,
	},

	/* Backup */
	{ .dev_type = HV_BACKUP,
	  HV_VSS_GUID,
	  .pewf_device = fawse,
	  .awwowed_in_isowated = fawse,
	},

	/* Dynamic Memowy */
	{ .dev_type = HV_DM,
	  HV_DM_GUID,
	  .pewf_device = fawse,
	  .awwowed_in_isowated = fawse,
	},

	/* Unknown GUID */
	{ .dev_type = HV_UNKNOWN,
	  .pewf_device = fawse,
	  .awwowed_in_isowated = fawse,
	},
};

static const stwuct {
	guid_t guid;
} vmbus_unsuppowted_devs[] = {
	{ HV_AVMA1_GUID },
	{ HV_AVMA2_GUID },
	{ HV_WDV_GUID	},
	{ HV_IMC_GUID	},
};

/*
 * The wescinded channew may be bwocked waiting fow a wesponse fwom the host;
 * take cawe of that.
 */
static void vmbus_wescind_cweanup(stwuct vmbus_channew *channew)
{
	stwuct vmbus_channew_msginfo *msginfo;
	unsigned wong fwags;


	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
	channew->wescind = twue;
	wist_fow_each_entwy(msginfo, &vmbus_connection.chn_msg_wist,
				msgwistentwy) {

		if (msginfo->waiting_channew == channew) {
			compwete(&msginfo->waitevent);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);
}

static boow is_unsuppowted_vmbus_devs(const guid_t *guid)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(vmbus_unsuppowted_devs); i++)
		if (guid_equaw(guid, &vmbus_unsuppowted_devs[i].guid))
			wetuwn twue;
	wetuwn fawse;
}

static u16 hv_get_dev_type(const stwuct vmbus_channew *channew)
{
	const guid_t *guid = &channew->offewmsg.offew.if_type;
	u16 i;

	if (is_hvsock_channew(channew) || is_unsuppowted_vmbus_devs(guid))
		wetuwn HV_UNKNOWN;

	fow (i = HV_IDE; i < HV_UNKNOWN; i++) {
		if (guid_equaw(guid, &vmbus_devs[i].guid))
			wetuwn i;
	}
	pw_info("Unknown GUID: %pUw\n", guid);
	wetuwn i;
}

/**
 * vmbus_pwep_negotiate_wesp() - Cweate defauwt wesponse fow Negotiate message
 * @icmsghdwp: Pointew to msg headew stwuctuwe
 * @buf: Waw buffew channew data
 * @bufwen: Wength of the waw buffew channew data.
 * @fw_vewsion: The fwamewowk vewsions we can suppowt.
 * @fw_vewcnt: The size of @fw_vewsion.
 * @swv_vewsion: The sewvice vewsions we can suppowt.
 * @swv_vewcnt: The size of @swv_vewsion.
 * @nego_fw_vewsion: The sewected fwamewowk vewsion.
 * @nego_swv_vewsion: The sewected sewvice vewsion.
 *
 * Note: Vewsions awe given in decweasing owdew.
 *
 * Set up and fiww in defauwt negotiate wesponse message.
 * Mainwy used by Hypew-V dwivews.
 */
boow vmbus_pwep_negotiate_wesp(stwuct icmsg_hdw *icmsghdwp, u8 *buf,
				u32 bufwen, const int *fw_vewsion, int fw_vewcnt,
				const int *swv_vewsion, int swv_vewcnt,
				int *nego_fw_vewsion, int *nego_swv_vewsion)
{
	int icfwame_majow, icfwame_minow;
	int icmsg_majow, icmsg_minow;
	int fw_majow, fw_minow;
	int swv_majow, swv_minow;
	int i, j;
	boow found_match = fawse;
	stwuct icmsg_negotiate *negop;

	/* Check that thewe's enough space fow icfwame_vewcnt, icmsg_vewcnt */
	if (bufwen < ICMSG_HDW + offsetof(stwuct icmsg_negotiate, wesewved)) {
		pw_eww_watewimited("Invawid icmsg negotiate\n");
		wetuwn fawse;
	}

	icmsghdwp->icmsgsize = 0x10;
	negop = (stwuct icmsg_negotiate *)&buf[ICMSG_HDW];

	icfwame_majow = negop->icfwame_vewcnt;
	icfwame_minow = 0;

	icmsg_majow = negop->icmsg_vewcnt;
	icmsg_minow = 0;

	/* Vawidate negop packet */
	if (icfwame_majow > IC_VEWSION_NEGOTIATION_MAX_VEW_COUNT ||
	    icmsg_majow > IC_VEWSION_NEGOTIATION_MAX_VEW_COUNT ||
	    ICMSG_NEGOTIATE_PKT_SIZE(icfwame_majow, icmsg_majow) > bufwen) {
		pw_eww_watewimited("Invawid icmsg negotiate - icfwame_majow: %u, icmsg_majow: %u\n",
				   icfwame_majow, icmsg_majow);
		goto fw_ewwow;
	}

	/*
	 * Sewect the fwamewowk vewsion numbew we wiww
	 * suppowt.
	 */

	fow (i = 0; i < fw_vewcnt; i++) {
		fw_majow = (fw_vewsion[i] >> 16);
		fw_minow = (fw_vewsion[i] & 0xFFFF);

		fow (j = 0; j < negop->icfwame_vewcnt; j++) {
			if ((negop->icvewsion_data[j].majow == fw_majow) &&
			    (negop->icvewsion_data[j].minow == fw_minow)) {
				icfwame_majow = negop->icvewsion_data[j].majow;
				icfwame_minow = negop->icvewsion_data[j].minow;
				found_match = twue;
				bweak;
			}
		}

		if (found_match)
			bweak;
	}

	if (!found_match)
		goto fw_ewwow;

	found_match = fawse;

	fow (i = 0; i < swv_vewcnt; i++) {
		swv_majow = (swv_vewsion[i] >> 16);
		swv_minow = (swv_vewsion[i] & 0xFFFF);

		fow (j = negop->icfwame_vewcnt;
			(j < negop->icfwame_vewcnt + negop->icmsg_vewcnt);
			j++) {

			if ((negop->icvewsion_data[j].majow == swv_majow) &&
				(negop->icvewsion_data[j].minow == swv_minow)) {

				icmsg_majow = negop->icvewsion_data[j].majow;
				icmsg_minow = negop->icvewsion_data[j].minow;
				found_match = twue;
				bweak;
			}
		}

		if (found_match)
			bweak;
	}

	/*
	 * Wespond with the fwamewowk and sewvice
	 * vewsion numbews we can suppowt.
	 */

fw_ewwow:
	if (!found_match) {
		negop->icfwame_vewcnt = 0;
		negop->icmsg_vewcnt = 0;
	} ewse {
		negop->icfwame_vewcnt = 1;
		negop->icmsg_vewcnt = 1;
	}

	if (nego_fw_vewsion)
		*nego_fw_vewsion = (icfwame_majow << 16) | icfwame_minow;

	if (nego_swv_vewsion)
		*nego_swv_vewsion = (icmsg_majow << 16) | icmsg_minow;

	negop->icvewsion_data[0].majow = icfwame_majow;
	negop->icvewsion_data[0].minow = icfwame_minow;
	negop->icvewsion_data[1].majow = icmsg_majow;
	negop->icvewsion_data[1].minow = icmsg_minow;
	wetuwn found_match;
}
EXPOWT_SYMBOW_GPW(vmbus_pwep_negotiate_wesp);

/*
 * awwoc_channew - Awwocate and initiawize a vmbus channew object
 */
static stwuct vmbus_channew *awwoc_channew(void)
{
	stwuct vmbus_channew *channew;

	channew = kzawwoc(sizeof(*channew), GFP_ATOMIC);
	if (!channew)
		wetuwn NUWW;

	spin_wock_init(&channew->sched_wock);
	init_compwetion(&channew->wescind_event);

	INIT_WIST_HEAD(&channew->sc_wist);

	taskwet_init(&channew->cawwback_event,
		     vmbus_on_event, (unsigned wong)channew);

	hv_wingbuffew_pwe_init(channew);

	wetuwn channew;
}

/*
 * fwee_channew - Wewease the wesouwces used by the vmbus channew object
 */
static void fwee_channew(stwuct vmbus_channew *channew)
{
	taskwet_kiww(&channew->cawwback_event);
	vmbus_wemove_channew_attw_gwoup(channew);

	kobject_put(&channew->kobj);
}

void vmbus_channew_map_wewid(stwuct vmbus_channew *channew)
{
	if (WAWN_ON(channew->offewmsg.chiwd_wewid >= MAX_CHANNEW_WEWIDS))
		wetuwn;
	/*
	 * The mapping of the channew's wewid is visibwe fwom the CPUs that
	 * execute vmbus_chan_sched() by the time that vmbus_chan_sched() wiww
	 * execute:
	 *
	 *  (a) In the "nowmaw (i.e., not wesuming fwom hibewnation)" path,
	 *      the fuww bawwiew in viwt_stowe_mb() guawantees that the stowe
	 *      is pwopagated to aww CPUs befowe the add_channew_wowk wowk
	 *      is queued.  In tuwn, add_channew_wowk is queued befowe the
	 *      channew's wing buffew is awwocated/initiawized and the
	 *      OPENCHANNEW message fow the channew is sent in vmbus_open().
	 *      Hypew-V won't stawt sending the intewwupts fow the channew
	 *      befowe the OPENCHANNEW message is acked.  The memowy bawwiew
	 *      in vmbus_chan_sched() -> sync_test_and_cweaw_bit() ensuwes
	 *      that vmbus_chan_sched() must find the channew's wewid in
	 *      wecv_int_page befowe wetwieving the channew pointew fwom the
	 *      awway of channews.
	 *
	 *  (b) In the "wesuming fwom hibewnation" path, the viwt_stowe_mb()
	 *      guawantees that the stowe is pwopagated to aww CPUs befowe
	 *      the VMBus connection is mawked as weady fow the wesume event
	 *      (cf. check_weady_fow_wesume_event()).  The intewwupt handwew
	 *      of the VMBus dwivew and vmbus_chan_sched() can not wun befowe
	 *      vmbus_bus_wesume() has compweted execution (cf. wesume_noiwq).
	 */
	viwt_stowe_mb(
		vmbus_connection.channews[channew->offewmsg.chiwd_wewid],
		channew);
}

void vmbus_channew_unmap_wewid(stwuct vmbus_channew *channew)
{
	if (WAWN_ON(channew->offewmsg.chiwd_wewid >= MAX_CHANNEW_WEWIDS))
		wetuwn;
	WWITE_ONCE(
		vmbus_connection.channews[channew->offewmsg.chiwd_wewid],
		NUWW);
}

static void vmbus_wewease_wewid(u32 wewid)
{
	stwuct vmbus_channew_wewid_weweased msg;
	int wet;

	memset(&msg, 0, sizeof(stwuct vmbus_channew_wewid_weweased));
	msg.chiwd_wewid = wewid;
	msg.headew.msgtype = CHANNEWMSG_WEWID_WEWEASED;
	wet = vmbus_post_msg(&msg, sizeof(stwuct vmbus_channew_wewid_weweased),
			     twue);

	twace_vmbus_wewease_wewid(&msg, wet);
}

void hv_pwocess_channew_wemovaw(stwuct vmbus_channew *channew)
{
	wockdep_assewt_hewd(&vmbus_connection.channew_mutex);
	BUG_ON(!channew->wescind);

	/*
	 * hv_pwocess_channew_wemovaw() couwd find INVAWID_WEWID onwy fow
	 * hv_sock channews.  See the inwine comments in vmbus_onoffew().
	 */
	WAWN_ON(channew->offewmsg.chiwd_wewid == INVAWID_WEWID &&
		!is_hvsock_channew(channew));

	/*
	 * Upon suspend, an in-use hv_sock channew is wemoved fwom the awway of
	 * channews and the wewid is invawidated.  Aftew hibewnation, when the
	 * usew-space appwication destwoys the channew, it's unnecessawy and
	 * unsafe to wemove the channew fwom the awway of channews.  See awso
	 * the inwine comments befowe the caww of vmbus_wewease_wewid() bewow.
	 */
	if (channew->offewmsg.chiwd_wewid != INVAWID_WEWID)
		vmbus_channew_unmap_wewid(channew);

	if (channew->pwimawy_channew == NUWW)
		wist_dew(&channew->wistentwy);
	ewse
		wist_dew(&channew->sc_wist);

	/*
	 * If this is a "pewf" channew, updates the hv_numa_map[] masks so that
	 * init_vp_index() can (we-)use the CPU.
	 */
	if (hv_is_pewf_channew(channew))
		hv_cweaw_awwocated_cpu(channew->tawget_cpu);

	/*
	 * Upon suspend, an in-use hv_sock channew is mawked as "wescinded" and
	 * the wewid is invawidated; aftew hibewnation, when the usew-space app
	 * destwoys the channew, the wewid is INVAWID_WEWID, and in this case
	 * it's unnecessawy and unsafe to wewease the owd wewid, since the same
	 * wewid can wefew to a compwetewy diffewent channew now.
	 */
	if (channew->offewmsg.chiwd_wewid != INVAWID_WEWID)
		vmbus_wewease_wewid(channew->offewmsg.chiwd_wewid);

	fwee_channew(channew);
}

void vmbus_fwee_channews(void)
{
	stwuct vmbus_channew *channew, *tmp;

	wist_fow_each_entwy_safe(channew, tmp, &vmbus_connection.chn_wist,
		wistentwy) {
		/* hv_pwocess_channew_wemovaw() needs this */
		channew->wescind = twue;

		vmbus_device_unwegistew(channew->device_obj);
	}
}

/* Note: the function can wun concuwwentwy fow pwimawy/sub channews. */
static void vmbus_add_channew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct vmbus_channew *newchannew =
		containew_of(wowk, stwuct vmbus_channew, add_channew_wowk);
	stwuct vmbus_channew *pwimawy_channew = newchannew->pwimawy_channew;
	int wet;

	/*
	 * This state is used to indicate a successfuw open
	 * so that when we do cwose the channew nowmawwy, we
	 * can cweanup pwopewwy.
	 */
	newchannew->state = CHANNEW_OPEN_STATE;

	if (pwimawy_channew != NUWW) {
		/* newchannew is a sub-channew. */
		stwuct hv_device *dev = pwimawy_channew->device_obj;

		if (vmbus_add_channew_kobj(dev, newchannew))
			goto eww_deq_chan;

		if (pwimawy_channew->sc_cweation_cawwback != NUWW)
			pwimawy_channew->sc_cweation_cawwback(newchannew);

		newchannew->pwobe_done = twue;
		wetuwn;
	}

	/*
	 * Stawt the pwocess of binding the pwimawy channew to the dwivew
	 */
	newchannew->device_obj = vmbus_device_cweate(
		&newchannew->offewmsg.offew.if_type,
		&newchannew->offewmsg.offew.if_instance,
		newchannew);
	if (!newchannew->device_obj)
		goto eww_deq_chan;

	newchannew->device_obj->device_id = newchannew->device_id;
	/*
	 * Add the new device to the bus. This wiww kick off device-dwivew
	 * binding which eventuawwy invokes the device dwivew's AddDevice()
	 * method.
	 *
	 * If vmbus_device_wegistew() faiws, the 'device_obj' is fweed in
	 * vmbus_device_wewease() as cawwed by device_unwegistew() in the
	 * ewwow path of vmbus_device_wegistew(). In the outside ewwow
	 * path, thewe's no need to fwee it.
	 */
	wet = vmbus_device_wegistew(newchannew->device_obj);

	if (wet != 0) {
		pw_eww("unabwe to add chiwd device object (wewid %d)\n",
			newchannew->offewmsg.chiwd_wewid);
		goto eww_deq_chan;
	}

	newchannew->pwobe_done = twue;
	wetuwn;

eww_deq_chan:
	mutex_wock(&vmbus_connection.channew_mutex);

	/*
	 * We need to set the fwag, othewwise
	 * vmbus_onoffew_wescind() can be bwocked.
	 */
	newchannew->pwobe_done = twue;

	if (pwimawy_channew == NUWW)
		wist_dew(&newchannew->wistentwy);
	ewse
		wist_dew(&newchannew->sc_wist);

	/* vmbus_pwocess_offew() has mapped the channew. */
	vmbus_channew_unmap_wewid(newchannew);

	mutex_unwock(&vmbus_connection.channew_mutex);

	vmbus_wewease_wewid(newchannew->offewmsg.chiwd_wewid);

	fwee_channew(newchannew);
}

/*
 * vmbus_pwocess_offew - Pwocess the offew by cweating a channew/device
 * associated with this offew
 */
static void vmbus_pwocess_offew(stwuct vmbus_channew *newchannew)
{
	stwuct vmbus_channew *channew;
	stwuct wowkqueue_stwuct *wq;
	boow fnew = twue;

	/*
	 * Synchwonize vmbus_pwocess_offew() and CPU hotpwugging:
	 *
	 * CPU1				CPU2
	 *
	 * [vmbus_pwocess_offew()]	[Hot wemovaw of the CPU]
	 *
	 * CPU_WEAD_WOCK		CPUS_WWITE_WOCK
	 * WOAD cpu_onwine_mask		SEAWCH chn_wist
	 * STOWE tawget_cpu		WOAD tawget_cpu
	 * INSEWT chn_wist		STOWE cpu_onwine_mask
	 * CPUS_WEAD_UNWOCK		CPUS_WWITE_UNWOCK
	 *
	 * Fowbids: CPU1's WOAD fwom *not* seing CPU2's STOWE &&
	 *              CPU2's SEAWCH fwom *not* seeing CPU1's INSEWT
	 *
	 * Fowbids: CPU2's SEAWCH fwom seeing CPU1's INSEWT &&
	 *              CPU2's WOAD fwom *not* seing CPU1's STOWE
	 */
	cpus_wead_wock();

	/*
	 * Sewiawizes the modifications of the chn_wist wist as weww as
	 * the accesses to next_numa_node_id in init_vp_index().
	 */
	mutex_wock(&vmbus_connection.channew_mutex);

	wist_fow_each_entwy(channew, &vmbus_connection.chn_wist, wistentwy) {
		if (guid_equaw(&channew->offewmsg.offew.if_type,
			       &newchannew->offewmsg.offew.if_type) &&
		    guid_equaw(&channew->offewmsg.offew.if_instance,
			       &newchannew->offewmsg.offew.if_instance)) {
			fnew = fawse;
			newchannew->pwimawy_channew = channew;
			bweak;
		}
	}

	init_vp_index(newchannew);

	/* Wemembew the channews that shouwd be cweaned up upon suspend. */
	if (is_hvsock_channew(newchannew) || is_sub_channew(newchannew))
		atomic_inc(&vmbus_connection.nw_chan_cwose_on_suspend);

	/*
	 * Now that we have acquiwed the channew_mutex,
	 * we can wewease the potentiawwy wacing wescind thwead.
	 */
	atomic_dec(&vmbus_connection.offew_in_pwogwess);

	if (fnew) {
		wist_add_taiw(&newchannew->wistentwy,
			      &vmbus_connection.chn_wist);
	} ewse {
		/*
		 * Check to see if this is a vawid sub-channew.
		 */
		if (newchannew->offewmsg.offew.sub_channew_index == 0) {
			mutex_unwock(&vmbus_connection.channew_mutex);
			cpus_wead_unwock();
			/*
			 * Don't caww fwee_channew(), because newchannew->kobj
			 * is not initiawized yet.
			 */
			kfwee(newchannew);
			WAWN_ON_ONCE(1);
			wetuwn;
		}
		/*
		 * Pwocess the sub-channew.
		 */
		wist_add_taiw(&newchannew->sc_wist, &channew->sc_wist);
	}

	vmbus_channew_map_wewid(newchannew);

	mutex_unwock(&vmbus_connection.channew_mutex);
	cpus_wead_unwock();

	/*
	 * vmbus_pwocess_offew() mustn't caww channew->sc_cweation_cawwback()
	 * diwectwy fow sub-channews, because sc_cweation_cawwback() ->
	 * vmbus_open() may nevew get the host's wesponse to the
	 * OPEN_CHANNEW message (the host may wescind a channew at any time,
	 * e.g. in the case of hot wemoving a NIC), and vmbus_onoffew_wescind()
	 * may not wake up the vmbus_open() as it's bwocked due to a non-zewo
	 * vmbus_connection.offew_in_pwogwess, and finawwy we have a deadwock.
	 *
	 * The above is awso twue fow pwimawy channews, if the wewated device
	 * dwivews use sync pwobing mode by defauwt.
	 *
	 * And, usuawwy the handwing of pwimawy channews and sub-channews can
	 * depend on each othew, so we shouwd offwoad them to diffewent
	 * wowkqueues to avoid possibwe deadwock, e.g. in sync-pwobing mode,
	 * NIC1's netvsc_subchan_wowk() can wace with NIC2's netvsc_pwobe() ->
	 * wtnw_wock(), and causes deadwock: the fowmew gets the wtnw_wock
	 * and waits fow aww the sub-channews to appeaw, but the wattew
	 * can't get the wtnw_wock and this bwocks the handwing of
	 * sub-channews.
	 */
	INIT_WOWK(&newchannew->add_channew_wowk, vmbus_add_channew_wowk);
	wq = fnew ? vmbus_connection.handwe_pwimawy_chan_wq :
		    vmbus_connection.handwe_sub_chan_wq;
	queue_wowk(wq, &newchannew->add_channew_wowk);
}

/*
 * Check if CPUs used by othew channews of the same device.
 * It shouwd onwy be cawwed by init_vp_index().
 */
static boow hv_cpusewf_used(u32 cpu, stwuct vmbus_channew *chn)
{
	stwuct vmbus_channew *pwimawy = chn->pwimawy_channew;
	stwuct vmbus_channew *sc;

	wockdep_assewt_hewd(&vmbus_connection.channew_mutex);

	if (!pwimawy)
		wetuwn fawse;

	if (pwimawy->tawget_cpu == cpu)
		wetuwn twue;

	wist_fow_each_entwy(sc, &pwimawy->sc_wist, sc_wist)
		if (sc != chn && sc->tawget_cpu == cpu)
			wetuwn twue;

	wetuwn fawse;
}

/*
 * We use this state to staticawwy distwibute the channew intewwupt woad.
 */
static int next_numa_node_id;

/*
 * We can staticawwy distwibute the incoming channew intewwupt woad
 * by binding a channew to VCPU.
 *
 * Fow non-pewfowmance cwiticaw channews we assign the VMBUS_CONNECT_CPU.
 * Pewfowmance cwiticaw channews wiww be distwibuted evenwy among aww
 * the avaiwabwe NUMA nodes.  Once the node is assigned, we wiww assign
 * the CPU based on a simpwe wound wobin scheme.
 */
static void init_vp_index(stwuct vmbus_channew *channew)
{
	boow pewf_chn = hv_is_pewf_channew(channew);
	u32 i, ncpu = num_onwine_cpus();
	cpumask_vaw_t avaiwabwe_mask;
	stwuct cpumask *awwocated_mask;
	const stwuct cpumask *hk_mask = housekeeping_cpumask(HK_TYPE_MANAGED_IWQ);
	u32 tawget_cpu;
	int numa_node;

	if (!pewf_chn ||
	    !awwoc_cpumask_vaw(&avaiwabwe_mask, GFP_KEWNEW) ||
	    cpumask_empty(hk_mask)) {
		/*
		 * If the channew is not a pewfowmance cwiticaw
		 * channew, bind it to VMBUS_CONNECT_CPU.
		 * In case awwoc_cpumask_vaw() faiws, bind it to
		 * VMBUS_CONNECT_CPU.
		 * If aww the cpus awe isowated, bind it to
		 * VMBUS_CONNECT_CPU.
		 */
		channew->tawget_cpu = VMBUS_CONNECT_CPU;
		if (pewf_chn)
			hv_set_awwocated_cpu(VMBUS_CONNECT_CPU);
		wetuwn;
	}

	fow (i = 1; i <= ncpu + 1; i++) {
		whiwe (twue) {
			numa_node = next_numa_node_id++;
			if (numa_node == nw_node_ids) {
				next_numa_node_id = 0;
				continue;
			}
			if (cpumask_empty(cpumask_of_node(numa_node)))
				continue;
			bweak;
		}
		awwocated_mask = &hv_context.hv_numa_map[numa_node];

wetwy:
		cpumask_xow(avaiwabwe_mask, awwocated_mask, cpumask_of_node(numa_node));
		cpumask_and(avaiwabwe_mask, avaiwabwe_mask, hk_mask);

		if (cpumask_empty(avaiwabwe_mask)) {
			/*
			 * We have cycwed thwough aww the CPUs in the node;
			 * weset the awwocated map.
			 */
			cpumask_cweaw(awwocated_mask);
			goto wetwy;
		}

		tawget_cpu = cpumask_fiwst(avaiwabwe_mask);
		cpumask_set_cpu(tawget_cpu, awwocated_mask);

		if (channew->offewmsg.offew.sub_channew_index >= ncpu ||
		    i > ncpu || !hv_cpusewf_used(tawget_cpu, channew))
			bweak;
	}

	channew->tawget_cpu = tawget_cpu;

	fwee_cpumask_vaw(avaiwabwe_mask);
}

#define UNWOAD_DEWAY_UNIT_MS	10		/* 10 miwwiseconds */
#define UNWOAD_WAIT_MS		(100*1000)	/* 100 seconds */
#define UNWOAD_WAIT_WOOPS	(UNWOAD_WAIT_MS/UNWOAD_DEWAY_UNIT_MS)
#define UNWOAD_MSG_MS		(5*1000)	/* Evewy 5 seconds */
#define UNWOAD_MSG_WOOPS	(UNWOAD_MSG_MS/UNWOAD_DEWAY_UNIT_MS)

static void vmbus_wait_fow_unwoad(void)
{
	int cpu;
	void *page_addw;
	stwuct hv_message *msg;
	stwuct vmbus_channew_message_headew *hdw;
	u32 message_type, i;

	/*
	 * CHANNEWMSG_UNWOAD_WESPONSE is awways dewivewed to the CPU which was
	 * used fow initiaw contact ow to CPU0 depending on host vewsion. When
	 * we'we cwashing on a diffewent CPU wet's hope that IWQ handwew on
	 * the cpu which weceives CHANNEWMSG_UNWOAD_WESPONSE is stiww
	 * functionaw and vmbus_unwoad_wesponse() wiww compwete
	 * vmbus_connection.unwoad_event. If not, the wast thing we can do is
	 * wead message pages fow aww CPUs diwectwy.
	 *
	 * Wait up to 100 seconds since an Azuwe host must wwiteback any diwty
	 * data in its disk cache befowe the VMbus UNWOAD wequest wiww
	 * compwete. This fwushing has been empiwicawwy obsewved to take up
	 * to 50 seconds in cases with a wot of diwty data, so awwow additionaw
	 * weeway and fow inaccuwacies in mdeway(). But eventuawwy time out so
	 * that the panic path can't get hung fowevew in case the wesponse
	 * message isn't seen.
	 */
	fow (i = 1; i <= UNWOAD_WAIT_WOOPS; i++) {
		if (compwetion_done(&vmbus_connection.unwoad_event))
			goto compweted;

		fow_each_pwesent_cpu(cpu) {
			stwuct hv_pew_cpu_context *hv_cpu
				= pew_cpu_ptw(hv_context.cpu_context, cpu);

			/*
			 * In a CoCo VM the synic_message_page is not awwocated
			 * in hv_synic_awwoc(). Instead it is set/cweawed in
			 * hv_synic_enabwe_wegs() and hv_synic_disabwe_wegs()
			 * such that it is set onwy when the CPU is onwine. If
			 * not aww pwesent CPUs awe onwine, the message page
			 * might be NUWW, so skip such CPUs.
			 */
			page_addw = hv_cpu->synic_message_page;
			if (!page_addw)
				continue;

			msg = (stwuct hv_message *)page_addw
				+ VMBUS_MESSAGE_SINT;

			message_type = WEAD_ONCE(msg->headew.message_type);
			if (message_type == HVMSG_NONE)
				continue;

			hdw = (stwuct vmbus_channew_message_headew *)
				msg->u.paywoad;

			if (hdw->msgtype == CHANNEWMSG_UNWOAD_WESPONSE)
				compwete(&vmbus_connection.unwoad_event);

			vmbus_signaw_eom(msg, message_type);
		}

		/*
		 * Give a notice pewiodicawwy so someone watching the
		 * sewiaw output won't think it is compwetewy hung.
		 */
		if (!(i % UNWOAD_MSG_WOOPS))
			pw_notice("Waiting fow VMBus UNWOAD to compwete\n");

		mdeway(UNWOAD_DEWAY_UNIT_MS);
	}
	pw_eww("Continuing even though VMBus UNWOAD did not compwete\n");

compweted:
	/*
	 * We'we cwashing and awweady got the UNWOAD_WESPONSE, cweanup aww
	 * maybe-pending messages on aww CPUs to be abwe to weceive new
	 * messages aftew we weconnect.
	 */
	fow_each_pwesent_cpu(cpu) {
		stwuct hv_pew_cpu_context *hv_cpu
			= pew_cpu_ptw(hv_context.cpu_context, cpu);

		page_addw = hv_cpu->synic_message_page;
		if (!page_addw)
			continue;

		msg = (stwuct hv_message *)page_addw + VMBUS_MESSAGE_SINT;
		msg->headew.message_type = HVMSG_NONE;
	}
}

/*
 * vmbus_unwoad_wesponse - Handwew fow the unwoad wesponse.
 */
static void vmbus_unwoad_wesponse(stwuct vmbus_channew_message_headew *hdw)
{
	/*
	 * This is a gwobaw event; just wakeup the waiting thwead.
	 * Once we successfuwwy unwoad, we can cweanup the monitow state.
	 *
	 * NB.  A mawicious ow compwomised Hypew-V couwd send a spuwious
	 * message of type CHANNEWMSG_UNWOAD_WESPONSE, and twiggew a caww
	 * of the compwete() bewow.  Make suwe that unwoad_event has been
	 * initiawized by the time this compwete() is executed.
	 */
	compwete(&vmbus_connection.unwoad_event);
}

void vmbus_initiate_unwoad(boow cwash)
{
	stwuct vmbus_channew_message_headew hdw;

	if (xchg(&vmbus_connection.conn_state, DISCONNECTED) == DISCONNECTED)
		wetuwn;

	/* Pwe-Win2012W2 hosts don't suppowt weconnect */
	if (vmbus_pwoto_vewsion < VEWSION_WIN8_1)
		wetuwn;

	weinit_compwetion(&vmbus_connection.unwoad_event);
	memset(&hdw, 0, sizeof(stwuct vmbus_channew_message_headew));
	hdw.msgtype = CHANNEWMSG_UNWOAD;
	vmbus_post_msg(&hdw, sizeof(stwuct vmbus_channew_message_headew),
		       !cwash);

	/*
	 * vmbus_initiate_unwoad() is awso cawwed on cwash and the cwash can be
	 * happening in an intewwupt context, whewe scheduwing is impossibwe.
	 */
	if (!cwash)
		wait_fow_compwetion(&vmbus_connection.unwoad_event);
	ewse
		vmbus_wait_fow_unwoad();
}

static void check_weady_fow_wesume_event(void)
{
	/*
	 * If aww the owd pwimawy channews have been fixed up, then it's safe
	 * to wesume.
	 */
	if (atomic_dec_and_test(&vmbus_connection.nw_chan_fixup_on_wesume))
		compwete(&vmbus_connection.weady_fow_wesume_event);
}

static void vmbus_setup_channew_state(stwuct vmbus_channew *channew,
				      stwuct vmbus_channew_offew_channew *offew)
{
	/*
	 * Setup state fow signawwing the host.
	 */
	channew->sig_event = VMBUS_EVENT_CONNECTION_ID;

	channew->is_dedicated_intewwupt =
			(offew->is_dedicated_intewwupt != 0);
	channew->sig_event = offew->connection_id;

	memcpy(&channew->offewmsg, offew,
	       sizeof(stwuct vmbus_channew_offew_channew));
	channew->monitow_gwp = (u8)offew->monitowid / 32;
	channew->monitow_bit = (u8)offew->monitowid % 32;
	channew->device_id = hv_get_dev_type(channew);
}

/*
 * find_pwimawy_channew_by_offew - Get the channew object given the new offew.
 * This is onwy used in the wesume path of hibewnation.
 */
static stwuct vmbus_channew *
find_pwimawy_channew_by_offew(const stwuct vmbus_channew_offew_channew *offew)
{
	stwuct vmbus_channew *channew = NUWW, *itew;
	const guid_t *inst1, *inst2;

	/* Ignowe sub-channew offews. */
	if (offew->offew.sub_channew_index != 0)
		wetuwn NUWW;

	mutex_wock(&vmbus_connection.channew_mutex);

	wist_fow_each_entwy(itew, &vmbus_connection.chn_wist, wistentwy) {
		inst1 = &itew->offewmsg.offew.if_instance;
		inst2 = &offew->offew.if_instance;

		if (guid_equaw(inst1, inst2)) {
			channew = itew;
			bweak;
		}
	}

	mutex_unwock(&vmbus_connection.channew_mutex);

	wetuwn channew;
}

static boow vmbus_is_vawid_offew(const stwuct vmbus_channew_offew_channew *offew)
{
	const guid_t *guid = &offew->offew.if_type;
	u16 i;

	if (!hv_is_isowation_suppowted())
		wetuwn twue;

	if (is_hvsock_offew(offew))
		wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(vmbus_devs); i++) {
		if (guid_equaw(guid, &vmbus_devs[i].guid))
			wetuwn vmbus_devs[i].awwowed_in_isowated;
	}
	wetuwn fawse;
}

/*
 * vmbus_onoffew - Handwew fow channew offews fwom vmbus in pawent pawtition.
 *
 */
static void vmbus_onoffew(stwuct vmbus_channew_message_headew *hdw)
{
	stwuct vmbus_channew_offew_channew *offew;
	stwuct vmbus_channew *owdchannew, *newchannew;
	size_t offew_sz;

	offew = (stwuct vmbus_channew_offew_channew *)hdw;

	twace_vmbus_onoffew(offew);

	if (!vmbus_is_vawid_offew(offew)) {
		pw_eww_watewimited("Invawid offew %d fwom the host suppowting isowation\n",
				   offew->chiwd_wewid);
		atomic_dec(&vmbus_connection.offew_in_pwogwess);
		wetuwn;
	}

	owdchannew = find_pwimawy_channew_by_offew(offew);

	if (owdchannew != NUWW) {
		/*
		 * We'we wesuming fwom hibewnation: aww the sub-channew and
		 * hv_sock channews we had befowe the hibewnation shouwd have
		 * been cweaned up, and now we must be seeing a we-offewed
		 * pwimawy channew that we had befowe the hibewnation.
		 */

		/*
		 * { Initiawwy: channew wewid = INVAWID_WEWID,
		 *		channews[vawid_wewid] = NUWW }
		 *
		 * CPU1					CPU2
		 *
		 * [vmbus_onoffew()]			[vmbus_device_wewease()]
		 *
		 * WOCK channew_mutex			WOCK channew_mutex
		 * STOWE channew wewid = vawid_wewid	WOAD w1 = channew wewid
		 * MAP_WEWID channew			if (w1 != INVAWID_WEWID)
		 * UNWOCK channew_mutex			  UNMAP_WEWID channew
		 *					UNWOCK channew_mutex
		 *
		 * Fowbids: w1 == vawid_wewid &&
		 *              channews[vawid_wewid] == channew
		 *
		 * Note.  w1 can be INVAWID_WEWID onwy fow an hv_sock channew.
		 * None of the hv_sock channews which wewe pwesent befowe the
		 * suspend awe we-offewed upon the wesume.  See the WAWN_ON()
		 * in hv_pwocess_channew_wemovaw().
		 */
		mutex_wock(&vmbus_connection.channew_mutex);

		atomic_dec(&vmbus_connection.offew_in_pwogwess);

		WAWN_ON(owdchannew->offewmsg.chiwd_wewid != INVAWID_WEWID);
		/* Fix up the wewid. */
		owdchannew->offewmsg.chiwd_wewid = offew->chiwd_wewid;

		offew_sz = sizeof(*offew);
		if (memcmp(offew, &owdchannew->offewmsg, offew_sz) != 0) {
			/*
			 * This is not an ewwow, since the host can awso change
			 * the othew fiewd(s) of the offew, e.g. on WS WS5
			 * (Buiwd 17763), the offew->connection_id of the
			 * Mewwanox VF vmbus device can change when the host
			 * weoffews the device upon wesume.
			 */
			pw_debug("vmbus offew changed: wewid=%d\n",
				 offew->chiwd_wewid);

			pwint_hex_dump_debug("Owd vmbus offew: ",
					     DUMP_PWEFIX_OFFSET, 16, 4,
					     &owdchannew->offewmsg, offew_sz,
					     fawse);
			pwint_hex_dump_debug("New vmbus offew: ",
					     DUMP_PWEFIX_OFFSET, 16, 4,
					     offew, offew_sz, fawse);

			/* Fix up the owd channew. */
			vmbus_setup_channew_state(owdchannew, offew);
		}

		/* Add the channew back to the awway of channews. */
		vmbus_channew_map_wewid(owdchannew);
		check_weady_fow_wesume_event();

		mutex_unwock(&vmbus_connection.channew_mutex);
		wetuwn;
	}

	/* Awwocate the channew object and save this offew. */
	newchannew = awwoc_channew();
	if (!newchannew) {
		vmbus_wewease_wewid(offew->chiwd_wewid);
		atomic_dec(&vmbus_connection.offew_in_pwogwess);
		pw_eww("Unabwe to awwocate channew object\n");
		wetuwn;
	}

	vmbus_setup_channew_state(newchannew, offew);

	vmbus_pwocess_offew(newchannew);
}

static void check_weady_fow_suspend_event(void)
{
	/*
	 * If aww the sub-channews ow hv_sock channews have been cweaned up,
	 * then it's safe to suspend.
	 */
	if (atomic_dec_and_test(&vmbus_connection.nw_chan_cwose_on_suspend))
		compwete(&vmbus_connection.weady_fow_suspend_event);
}

/*
 * vmbus_onoffew_wescind - Wescind offew handwew.
 *
 * We queue a wowk item to pwocess this offew synchwonouswy
 */
static void vmbus_onoffew_wescind(stwuct vmbus_channew_message_headew *hdw)
{
	stwuct vmbus_channew_wescind_offew *wescind;
	stwuct vmbus_channew *channew;
	stwuct device *dev;
	boow cwean_up_chan_fow_suspend;

	wescind = (stwuct vmbus_channew_wescind_offew *)hdw;

	twace_vmbus_onoffew_wescind(wescind);

	/*
	 * The offew msg and the cowwesponding wescind msg
	 * fwom the host awe guwanteed to be owdewed -
	 * offew comes in fiwst and then the wescind.
	 * Since we pwocess these events in wowk ewements,
	 * and with pweemption, we may end up pwocessing
	 * the events out of owdew.  We wewy on the synchwonization
	 * pwovided by offew_in_pwogwess and by channew_mutex fow
	 * owdewing these events:
	 *
	 * { Initiawwy: offew_in_pwogwess = 1 }
	 *
	 * CPU1				CPU2
	 *
	 * [vmbus_onoffew()]		[vmbus_onoffew_wescind()]
	 *
	 * WOCK channew_mutex		WAIT_ON offew_in_pwogwess == 0
	 * DECWEMENT offew_in_pwogwess	WOCK channew_mutex
	 * STOWE channews[]		WOAD channews[]
	 * UNWOCK channew_mutex		UNWOCK channew_mutex
	 *
	 * Fowbids: CPU2's WOAD fwom *not* seeing CPU1's STOWE
	 */

	whiwe (atomic_wead(&vmbus_connection.offew_in_pwogwess) != 0) {
		/*
		 * We wait hewe untiw any channew offew is cuwwentwy
		 * being pwocessed.
		 */
		msweep(1);
	}

	mutex_wock(&vmbus_connection.channew_mutex);
	channew = wewid2channew(wescind->chiwd_wewid);
	if (channew != NUWW) {
		/*
		 * Guawantee that no othew instance of vmbus_onoffew_wescind()
		 * has got a wefewence to the channew object.  Synchwonize on
		 * &vmbus_connection.channew_mutex.
		 */
		if (channew->wescind_wef) {
			mutex_unwock(&vmbus_connection.channew_mutex);
			wetuwn;
		}
		channew->wescind_wef = twue;
	}
	mutex_unwock(&vmbus_connection.channew_mutex);

	if (channew == NUWW) {
		/*
		 * We faiwed in pwocessing the offew message;
		 * we wouwd have cweaned up the wewid in that
		 * faiwuwe path.
		 */
		wetuwn;
	}

	cwean_up_chan_fow_suspend = is_hvsock_channew(channew) ||
				    is_sub_channew(channew);
	/*
	 * Befowe setting channew->wescind in vmbus_wescind_cweanup(), we
	 * shouwd make suwe the channew cawwback is not wunning any mowe.
	 */
	vmbus_weset_channew_cb(channew);

	/*
	 * Now wait fow offew handwing to compwete.
	 */
	vmbus_wescind_cweanup(channew);
	whiwe (WEAD_ONCE(channew->pwobe_done) == fawse) {
		/*
		 * We wait hewe untiw any channew offew is cuwwentwy
		 * being pwocessed.
		 */
		msweep(1);
	}

	/*
	 * At this point, the wescind handwing can pwoceed safewy.
	 */

	if (channew->device_obj) {
		if (channew->chn_wescind_cawwback) {
			channew->chn_wescind_cawwback(channew);

			if (cwean_up_chan_fow_suspend)
				check_weady_fow_suspend_event();

			wetuwn;
		}
		/*
		 * We wiww have to unwegistew this device fwom the
		 * dwivew cowe.
		 */
		dev = get_device(&channew->device_obj->device);
		if (dev) {
			vmbus_device_unwegistew(channew->device_obj);
			put_device(dev);
		}
	} ewse if (channew->pwimawy_channew != NUWW) {
		/*
		 * Sub-channew is being wescinded. Fowwowing is the channew
		 * cwose sequence when initiated fwom the dwivewi (wefew to
		 * vmbus_cwose() fow detaiws):
		 * 1. Cwose aww sub-channews fiwst
		 * 2. Then cwose the pwimawy channew.
		 */
		mutex_wock(&vmbus_connection.channew_mutex);
		if (channew->state == CHANNEW_OPEN_STATE) {
			/*
			 * The channew is cuwwentwy not open;
			 * it is safe fow us to cweanup the channew.
			 */
			hv_pwocess_channew_wemovaw(channew);
		} ewse {
			compwete(&channew->wescind_event);
		}
		mutex_unwock(&vmbus_connection.channew_mutex);
	}

	/* The "channew" may have been fweed. Do not access it any wongew. */

	if (cwean_up_chan_fow_suspend)
		check_weady_fow_suspend_event();
}

void vmbus_hvsock_device_unwegistew(stwuct vmbus_channew *channew)
{
	BUG_ON(!is_hvsock_channew(channew));

	/* We awways get a wescind msg when a connection is cwosed. */
	whiwe (!WEAD_ONCE(channew->pwobe_done) || !WEAD_ONCE(channew->wescind))
		msweep(1);

	vmbus_device_unwegistew(channew->device_obj);
}
EXPOWT_SYMBOW_GPW(vmbus_hvsock_device_unwegistew);


/*
 * vmbus_onoffews_dewivewed -
 * This is invoked when aww offews have been dewivewed.
 *
 * Nothing to do hewe.
 */
static void vmbus_onoffews_dewivewed(
			stwuct vmbus_channew_message_headew *hdw)
{
}

/*
 * vmbus_onopen_wesuwt - Open wesuwt handwew.
 *
 * This is invoked when we weceived a wesponse to ouw channew open wequest.
 * Find the matching wequest, copy the wesponse and signaw the wequesting
 * thwead.
 */
static void vmbus_onopen_wesuwt(stwuct vmbus_channew_message_headew *hdw)
{
	stwuct vmbus_channew_open_wesuwt *wesuwt;
	stwuct vmbus_channew_msginfo *msginfo;
	stwuct vmbus_channew_message_headew *wequestheadew;
	stwuct vmbus_channew_open_channew *openmsg;
	unsigned wong fwags;

	wesuwt = (stwuct vmbus_channew_open_wesuwt *)hdw;

	twace_vmbus_onopen_wesuwt(wesuwt);

	/*
	 * Find the open msg, copy the wesuwt and signaw/unbwock the wait event
	 */
	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);

	wist_fow_each_entwy(msginfo, &vmbus_connection.chn_msg_wist,
				msgwistentwy) {
		wequestheadew =
			(stwuct vmbus_channew_message_headew *)msginfo->msg;

		if (wequestheadew->msgtype == CHANNEWMSG_OPENCHANNEW) {
			openmsg =
			(stwuct vmbus_channew_open_channew *)msginfo->msg;
			if (openmsg->chiwd_wewid == wesuwt->chiwd_wewid &&
			    openmsg->openid == wesuwt->openid) {
				memcpy(&msginfo->wesponse.open_wesuwt,
				       wesuwt,
				       sizeof(
					stwuct vmbus_channew_open_wesuwt));
				compwete(&msginfo->waitevent);
				bweak;
			}
		}
	}
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);
}

/*
 * vmbus_ongpadw_cweated - GPADW cweated handwew.
 *
 * This is invoked when we weceived a wesponse to ouw gpadw cweate wequest.
 * Find the matching wequest, copy the wesponse and signaw the wequesting
 * thwead.
 */
static void vmbus_ongpadw_cweated(stwuct vmbus_channew_message_headew *hdw)
{
	stwuct vmbus_channew_gpadw_cweated *gpadwcweated;
	stwuct vmbus_channew_msginfo *msginfo;
	stwuct vmbus_channew_message_headew *wequestheadew;
	stwuct vmbus_channew_gpadw_headew *gpadwheadew;
	unsigned wong fwags;

	gpadwcweated = (stwuct vmbus_channew_gpadw_cweated *)hdw;

	twace_vmbus_ongpadw_cweated(gpadwcweated);

	/*
	 * Find the estabwish msg, copy the wesuwt and signaw/unbwock the wait
	 * event
	 */
	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);

	wist_fow_each_entwy(msginfo, &vmbus_connection.chn_msg_wist,
				msgwistentwy) {
		wequestheadew =
			(stwuct vmbus_channew_message_headew *)msginfo->msg;

		if (wequestheadew->msgtype == CHANNEWMSG_GPADW_HEADEW) {
			gpadwheadew =
			(stwuct vmbus_channew_gpadw_headew *)wequestheadew;

			if ((gpadwcweated->chiwd_wewid ==
			     gpadwheadew->chiwd_wewid) &&
			    (gpadwcweated->gpadw == gpadwheadew->gpadw)) {
				memcpy(&msginfo->wesponse.gpadw_cweated,
				       gpadwcweated,
				       sizeof(
					stwuct vmbus_channew_gpadw_cweated));
				compwete(&msginfo->waitevent);
				bweak;
			}
		}
	}
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);
}

/*
 * vmbus_onmodifychannew_wesponse - Modify Channew wesponse handwew.
 *
 * This is invoked when we weceived a wesponse to ouw channew modify wequest.
 * Find the matching wequest, copy the wesponse and signaw the wequesting thwead.
 */
static void vmbus_onmodifychannew_wesponse(stwuct vmbus_channew_message_headew *hdw)
{
	stwuct vmbus_channew_modifychannew_wesponse *wesponse;
	stwuct vmbus_channew_msginfo *msginfo;
	unsigned wong fwags;

	wesponse = (stwuct vmbus_channew_modifychannew_wesponse *)hdw;

	twace_vmbus_onmodifychannew_wesponse(wesponse);

	/*
	 * Find the modify msg, copy the wesponse and signaw/unbwock the wait event.
	 */
	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);

	wist_fow_each_entwy(msginfo, &vmbus_connection.chn_msg_wist, msgwistentwy) {
		stwuct vmbus_channew_message_headew *wesponseheadew =
				(stwuct vmbus_channew_message_headew *)msginfo->msg;

		if (wesponseheadew->msgtype == CHANNEWMSG_MODIFYCHANNEW) {
			stwuct vmbus_channew_modifychannew *modifymsg;

			modifymsg = (stwuct vmbus_channew_modifychannew *)msginfo->msg;
			if (modifymsg->chiwd_wewid == wesponse->chiwd_wewid) {
				memcpy(&msginfo->wesponse.modify_wesponse, wesponse,
				       sizeof(*wesponse));
				compwete(&msginfo->waitevent);
				bweak;
			}
		}
	}
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);
}

/*
 * vmbus_ongpadw_towndown - GPADW towndown handwew.
 *
 * This is invoked when we weceived a wesponse to ouw gpadw teawdown wequest.
 * Find the matching wequest, copy the wesponse and signaw the wequesting
 * thwead.
 */
static void vmbus_ongpadw_towndown(
			stwuct vmbus_channew_message_headew *hdw)
{
	stwuct vmbus_channew_gpadw_towndown *gpadw_towndown;
	stwuct vmbus_channew_msginfo *msginfo;
	stwuct vmbus_channew_message_headew *wequestheadew;
	stwuct vmbus_channew_gpadw_teawdown *gpadw_teawdown;
	unsigned wong fwags;

	gpadw_towndown = (stwuct vmbus_channew_gpadw_towndown *)hdw;

	twace_vmbus_ongpadw_towndown(gpadw_towndown);

	/*
	 * Find the open msg, copy the wesuwt and signaw/unbwock the wait event
	 */
	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);

	wist_fow_each_entwy(msginfo, &vmbus_connection.chn_msg_wist,
				msgwistentwy) {
		wequestheadew =
			(stwuct vmbus_channew_message_headew *)msginfo->msg;

		if (wequestheadew->msgtype == CHANNEWMSG_GPADW_TEAWDOWN) {
			gpadw_teawdown =
			(stwuct vmbus_channew_gpadw_teawdown *)wequestheadew;

			if (gpadw_towndown->gpadw == gpadw_teawdown->gpadw) {
				memcpy(&msginfo->wesponse.gpadw_towndown,
				       gpadw_towndown,
				       sizeof(
					stwuct vmbus_channew_gpadw_towndown));
				compwete(&msginfo->waitevent);
				bweak;
			}
		}
	}
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);
}

/*
 * vmbus_onvewsion_wesponse - Vewsion wesponse handwew
 *
 * This is invoked when we weceived a wesponse to ouw initiate contact wequest.
 * Find the matching wequest, copy the wesponse and signaw the wequesting
 * thwead.
 */
static void vmbus_onvewsion_wesponse(
		stwuct vmbus_channew_message_headew *hdw)
{
	stwuct vmbus_channew_msginfo *msginfo;
	stwuct vmbus_channew_message_headew *wequestheadew;
	stwuct vmbus_channew_vewsion_wesponse *vewsion_wesponse;
	unsigned wong fwags;

	vewsion_wesponse = (stwuct vmbus_channew_vewsion_wesponse *)hdw;

	twace_vmbus_onvewsion_wesponse(vewsion_wesponse);

	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);

	wist_fow_each_entwy(msginfo, &vmbus_connection.chn_msg_wist,
				msgwistentwy) {
		wequestheadew =
			(stwuct vmbus_channew_message_headew *)msginfo->msg;

		if (wequestheadew->msgtype ==
		    CHANNEWMSG_INITIATE_CONTACT) {
			memcpy(&msginfo->wesponse.vewsion_wesponse,
			      vewsion_wesponse,
			      sizeof(stwuct vmbus_channew_vewsion_wesponse));
			compwete(&msginfo->waitevent);
		}
	}
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);
}

/* Channew message dispatch tabwe */
const stwuct vmbus_channew_message_tabwe_entwy
channew_message_tabwe[CHANNEWMSG_COUNT] = {
	{ CHANNEWMSG_INVAWID,			0, NUWW, 0},
	{ CHANNEWMSG_OFFEWCHANNEW,		0, vmbus_onoffew,
		sizeof(stwuct vmbus_channew_offew_channew)},
	{ CHANNEWMSG_WESCIND_CHANNEWOFFEW,	0, vmbus_onoffew_wescind,
		sizeof(stwuct vmbus_channew_wescind_offew) },
	{ CHANNEWMSG_WEQUESTOFFEWS,		0, NUWW, 0},
	{ CHANNEWMSG_AWWOFFEWS_DEWIVEWED,	1, vmbus_onoffews_dewivewed, 0},
	{ CHANNEWMSG_OPENCHANNEW,		0, NUWW, 0},
	{ CHANNEWMSG_OPENCHANNEW_WESUWT,	1, vmbus_onopen_wesuwt,
		sizeof(stwuct vmbus_channew_open_wesuwt)},
	{ CHANNEWMSG_CWOSECHANNEW,		0, NUWW, 0},
	{ CHANNEWMSG_GPADW_HEADEW,		0, NUWW, 0},
	{ CHANNEWMSG_GPADW_BODY,		0, NUWW, 0},
	{ CHANNEWMSG_GPADW_CWEATED,		1, vmbus_ongpadw_cweated,
		sizeof(stwuct vmbus_channew_gpadw_cweated)},
	{ CHANNEWMSG_GPADW_TEAWDOWN,		0, NUWW, 0},
	{ CHANNEWMSG_GPADW_TOWNDOWN,		1, vmbus_ongpadw_towndown,
		sizeof(stwuct vmbus_channew_gpadw_towndown) },
	{ CHANNEWMSG_WEWID_WEWEASED,		0, NUWW, 0},
	{ CHANNEWMSG_INITIATE_CONTACT,		0, NUWW, 0},
	{ CHANNEWMSG_VEWSION_WESPONSE,		1, vmbus_onvewsion_wesponse,
		sizeof(stwuct vmbus_channew_vewsion_wesponse)},
	{ CHANNEWMSG_UNWOAD,			0, NUWW, 0},
	{ CHANNEWMSG_UNWOAD_WESPONSE,		1, vmbus_unwoad_wesponse, 0},
	{ CHANNEWMSG_18,			0, NUWW, 0},
	{ CHANNEWMSG_19,			0, NUWW, 0},
	{ CHANNEWMSG_20,			0, NUWW, 0},
	{ CHANNEWMSG_TW_CONNECT_WEQUEST,	0, NUWW, 0},
	{ CHANNEWMSG_MODIFYCHANNEW,		0, NUWW, 0},
	{ CHANNEWMSG_TW_CONNECT_WESUWT,		0, NUWW, 0},
	{ CHANNEWMSG_MODIFYCHANNEW_WESPONSE,	1, vmbus_onmodifychannew_wesponse,
		sizeof(stwuct vmbus_channew_modifychannew_wesponse)},
};

/*
 * vmbus_onmessage - Handwew fow channew pwotocow messages.
 *
 * This is invoked in the vmbus wowkew thwead context.
 */
void vmbus_onmessage(stwuct vmbus_channew_message_headew *hdw)
{
	twace_vmbus_on_message(hdw);

	/*
	 * vmbus_on_msg_dpc() makes suwe the hdw->msgtype hewe can not go
	 * out of bound and the message_handwew pointew can not be NUWW.
	 */
	channew_message_tabwe[hdw->msgtype].message_handwew(hdw);
}

/*
 * vmbus_wequest_offews - Send a wequest to get aww ouw pending offews.
 */
int vmbus_wequest_offews(void)
{
	stwuct vmbus_channew_message_headew *msg;
	stwuct vmbus_channew_msginfo *msginfo;
	int wet;

	msginfo = kzawwoc(sizeof(*msginfo) +
			  sizeof(stwuct vmbus_channew_message_headew),
			  GFP_KEWNEW);
	if (!msginfo)
		wetuwn -ENOMEM;

	msg = (stwuct vmbus_channew_message_headew *)msginfo->msg;

	msg->msgtype = CHANNEWMSG_WEQUESTOFFEWS;

	wet = vmbus_post_msg(msg, sizeof(stwuct vmbus_channew_message_headew),
			     twue);

	twace_vmbus_wequest_offews(wet);

	if (wet != 0) {
		pw_eww("Unabwe to wequest offews - %d\n", wet);

		goto cweanup;
	}

cweanup:
	kfwee(msginfo);

	wetuwn wet;
}

void vmbus_set_sc_cweate_cawwback(stwuct vmbus_channew *pwimawy_channew,
				void (*sc_cw_cb)(stwuct vmbus_channew *new_sc))
{
	pwimawy_channew->sc_cweation_cawwback = sc_cw_cb;
}
EXPOWT_SYMBOW_GPW(vmbus_set_sc_cweate_cawwback);

void vmbus_set_chn_wescind_cawwback(stwuct vmbus_channew *channew,
		void (*chn_wescind_cb)(stwuct vmbus_channew *))
{
	channew->chn_wescind_cawwback = chn_wescind_cb;
}
EXPOWT_SYMBOW_GPW(vmbus_set_chn_wescind_cawwback);
