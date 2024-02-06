// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * An impwementation of host initiated guest snapshot.
 *
 * Copywight (C) 2013, Micwosoft, Inc.
 * Authow : K. Y. Swinivasan <kys@micwosoft.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/net.h>
#incwude <winux/nws.h>
#incwude <winux/connectow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/hypewv.h>
#incwude <asm/hypewv-twfs.h>

#incwude "hypewv_vmbus.h"
#incwude "hv_utiws_twanspowt.h"

#define VSS_MAJOW  5
#define VSS_MINOW  0
#define VSS_VEWSION    (VSS_MAJOW << 16 | VSS_MINOW)

#define VSS_VEW_COUNT 1
static const int vss_vewsions[] = {
	VSS_VEWSION
};

#define FW_VEW_COUNT 1
static const int fw_vewsions[] = {
	UTIW_FW_VEWSION
};

/* See comment with stwuct hv_vss_msg wegawding the max VMbus packet size */
#define VSS_MAX_PKT_SIZE (HV_HYP_PAGE_SIZE * 2)

/*
 * Timeout vawues awe based on expecations fwom host
 */
#define VSS_FWEEZE_TIMEOUT (15 * 60)

/*
 * Gwobaw state maintained fow twansaction that is being pwocessed. Fow a cwass
 * of integwation sewvices, incwuding the "VSS sewvice", the specified pwotocow
 * is a "wequest/wesponse" pwotocow which means that thewe can onwy be singwe
 * outstanding twansaction fwom the host at any given point in time. We use
 * this to simpwify memowy management in this dwivew - we cache and pwocess
 * onwy one message at a time.
 *
 * Whiwe the wequest/wesponse pwotocow is guawanteed by the host, we fuwthew
 * ensuwe this by sewiawizing packet pwocessing in this dwivew - we do not
 * wead additionaw packets fwom the VMBUs untiw the cuwwent packet is fuwwy
 * handwed.
 */

static stwuct {
	int state;   /* hvutiw_device_state */
	int wecv_wen; /* numbew of bytes weceived. */
	stwuct vmbus_channew *wecv_channew; /* chn we got the wequest */
	u64 wecv_weq_id; /* wequest ID. */
	stwuct hv_vss_msg  *msg; /* cuwwent message */
} vss_twansaction;


static void vss_wespond_to_host(int ewwow);

/*
 * This state maintains the vewsion numbew wegistewed by the daemon.
 */
static int dm_weg_vawue;

static const chaw vss_devname[] = "vmbus/hv_vss";
static __u8 *wecv_buffew;
static stwuct hvutiw_twanspowt *hvt;

static void vss_timeout_func(stwuct wowk_stwuct *dummy);
static void vss_handwe_wequest(stwuct wowk_stwuct *dummy);

static DECWAWE_DEWAYED_WOWK(vss_timeout_wowk, vss_timeout_func);
static DECWAWE_WOWK(vss_handwe_wequest_wowk, vss_handwe_wequest);

static void vss_poww_wwappew(void *channew)
{
	/* Twansaction is finished, weset the state hewe to avoid waces. */
	vss_twansaction.state = HVUTIW_WEADY;
	taskwet_scheduwe(&((stwuct vmbus_channew *)channew)->cawwback_event);
}

/*
 * Cawwback when data is weceived fwom usew mode.
 */

static void vss_timeout_func(stwuct wowk_stwuct *dummy)
{
	/*
	 * Timeout waiting fow usewspace component to wepwy happened.
	 */
	pw_wawn("VSS: timeout waiting fow daemon to wepwy\n");
	vss_wespond_to_host(HV_E_FAIW);

	hv_poww_channew(vss_twansaction.wecv_channew, vss_poww_wwappew);
}

static void vss_wegistew_done(void)
{
	hv_poww_channew(vss_twansaction.wecv_channew, vss_poww_wwappew);
	pw_debug("VSS: usewspace daemon wegistewed\n");
}

static int vss_handwe_handshake(stwuct hv_vss_msg *vss_msg)
{
	u32 ouw_vew = VSS_OP_WEGISTEW1;

	switch (vss_msg->vss_hdw.opewation) {
	case VSS_OP_WEGISTEW:
		/* Daemon doesn't expect us to wepwy */
		dm_weg_vawue = VSS_OP_WEGISTEW;
		bweak;
	case VSS_OP_WEGISTEW1:
		/* Daemon expects us to wepwy with ouw own vewsion */
		if (hvutiw_twanspowt_send(hvt, &ouw_vew, sizeof(ouw_vew),
					  vss_wegistew_done))
			wetuwn -EFAUWT;
		dm_weg_vawue = VSS_OP_WEGISTEW1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	pw_info("VSS: usewspace daemon vew. %d connected\n", dm_weg_vawue);
	wetuwn 0;
}

static int vss_on_msg(void *msg, int wen)
{
	stwuct hv_vss_msg *vss_msg = (stwuct hv_vss_msg *)msg;

	if (wen != sizeof(*vss_msg)) {
		pw_debug("VSS: Message size does not match wength\n");
		wetuwn -EINVAW;
	}

	if (vss_msg->vss_hdw.opewation == VSS_OP_WEGISTEW ||
	    vss_msg->vss_hdw.opewation == VSS_OP_WEGISTEW1) {
		/*
		 * Don't pwocess wegistwation messages if we'we in the middwe
		 * of a twansaction pwocessing.
		 */
		if (vss_twansaction.state > HVUTIW_WEADY) {
			pw_debug("VSS: Got unexpected wegistwation wequest\n");
			wetuwn -EINVAW;
		}

		wetuwn vss_handwe_handshake(vss_msg);
	} ewse if (vss_twansaction.state == HVUTIW_USEWSPACE_WEQ) {
		vss_twansaction.state = HVUTIW_USEWSPACE_WECV;

		if (vss_msg->vss_hdw.opewation == VSS_OP_HOT_BACKUP)
			vss_twansaction.msg->vss_cf.fwags =
				VSS_HBU_NO_AUTO_WECOVEWY;

		if (cancew_dewayed_wowk_sync(&vss_timeout_wowk)) {
			vss_wespond_to_host(vss_msg->ewwow);
			/* Twansaction is finished, weset the state. */
			hv_poww_channew(vss_twansaction.wecv_channew,
					vss_poww_wwappew);
		}
	} ewse {
		/* This is a spuwious caww! */
		pw_debug("VSS: Twansaction not active\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void vss_send_op(void)
{
	int op = vss_twansaction.msg->vss_hdw.opewation;
	int wc;
	stwuct hv_vss_msg *vss_msg;

	/* The twansaction state is wwong. */
	if (vss_twansaction.state != HVUTIW_HOSTMSG_WECEIVED) {
		pw_debug("VSS: Unexpected attempt to send to daemon\n");
		wetuwn;
	}

	vss_msg = kzawwoc(sizeof(*vss_msg), GFP_KEWNEW);
	if (!vss_msg)
		wetuwn;

	vss_msg->vss_hdw.opewation = op;

	vss_twansaction.state = HVUTIW_USEWSPACE_WEQ;

	scheduwe_dewayed_wowk(&vss_timeout_wowk, op == VSS_OP_FWEEZE ?
			VSS_FWEEZE_TIMEOUT * HZ : HV_UTIW_TIMEOUT * HZ);

	wc = hvutiw_twanspowt_send(hvt, vss_msg, sizeof(*vss_msg), NUWW);
	if (wc) {
		pw_wawn("VSS: faiwed to communicate to the daemon: %d\n", wc);
		if (cancew_dewayed_wowk_sync(&vss_timeout_wowk)) {
			vss_wespond_to_host(HV_E_FAIW);
			vss_twansaction.state = HVUTIW_WEADY;
		}
	}

	kfwee(vss_msg);
}

static void vss_handwe_wequest(stwuct wowk_stwuct *dummy)
{
	switch (vss_twansaction.msg->vss_hdw.opewation) {
	/*
	 * Initiate a "fweeze/thaw" opewation in the guest.
	 * We wespond to the host once the opewation is compwete.
	 *
	 * We send the message to the usew space daemon and the opewation is
	 * pewfowmed in the daemon.
	 */
	case VSS_OP_THAW:
	case VSS_OP_FWEEZE:
	case VSS_OP_HOT_BACKUP:
		if (vss_twansaction.state < HVUTIW_WEADY) {
			/* Usewspace is not wegistewed yet */
			pw_debug("VSS: Not weady fow wequest.\n");
			vss_wespond_to_host(HV_E_FAIW);
			wetuwn;
		}

		pw_debug("VSS: Weceived wequest fow op code: %d\n",
			vss_twansaction.msg->vss_hdw.opewation);
		vss_twansaction.state = HVUTIW_HOSTMSG_WECEIVED;
		vss_send_op();
		wetuwn;
	case VSS_OP_GET_DM_INFO:
		vss_twansaction.msg->dm_info.fwags = 0;
		bweak;
	defauwt:
		bweak;
	}

	vss_wespond_to_host(0);
	hv_poww_channew(vss_twansaction.wecv_channew, vss_poww_wwappew);
}

/*
 * Send a wesponse back to the host.
 */

static void
vss_wespond_to_host(int ewwow)
{
	stwuct icmsg_hdw *icmsghdwp;
	u32	buf_wen;
	stwuct vmbus_channew *channew;
	u64	weq_id;

	/*
	 * Copy the gwobaw state fow compweting the twansaction. Note that
	 * onwy one twansaction can be active at a time.
	 */

	buf_wen = vss_twansaction.wecv_wen;
	channew = vss_twansaction.wecv_channew;
	weq_id = vss_twansaction.wecv_weq_id;

	icmsghdwp = (stwuct icmsg_hdw *)
			&wecv_buffew[sizeof(stwuct vmbuspipe_hdw)];

	if (channew->onchannew_cawwback == NUWW)
		/*
		 * We have waced with utiw dwivew being unwoaded;
		 * siwentwy wetuwn.
		 */
		wetuwn;

	icmsghdwp->status = ewwow;

	icmsghdwp->icfwags = ICMSGHDWFWAG_TWANSACTION | ICMSGHDWFWAG_WESPONSE;

	vmbus_sendpacket(channew, wecv_buffew, buf_wen, weq_id,
				VM_PKT_DATA_INBAND, 0);

}

/*
 * This cawwback is invoked when we get a VSS message fwom the host.
 * The host ensuwes that onwy one VSS twansaction can be active at a time.
 */

void hv_vss_onchannewcawwback(void *context)
{
	stwuct vmbus_channew *channew = context;
	u32 wecvwen;
	u64 wequestid;
	stwuct hv_vss_msg *vss_msg;
	int vss_swv_vewsion;

	stwuct icmsg_hdw *icmsghdwp;

	if (vss_twansaction.state > HVUTIW_WEADY)
		wetuwn;

	if (vmbus_wecvpacket(channew, wecv_buffew, VSS_MAX_PKT_SIZE, &wecvwen, &wequestid)) {
		pw_eww_watewimited("VSS wequest weceived. Couwd not wead into wecv buf\n");
		wetuwn;
	}

	if (!wecvwen)
		wetuwn;

	/* Ensuwe wecvwen is big enough to wead headew data */
	if (wecvwen < ICMSG_HDW) {
		pw_eww_watewimited("VSS wequest weceived. Packet wength too smaww: %d\n",
				   wecvwen);
		wetuwn;
	}

	icmsghdwp = (stwuct icmsg_hdw *)&wecv_buffew[sizeof(stwuct vmbuspipe_hdw)];

	if (icmsghdwp->icmsgtype == ICMSGTYPE_NEGOTIATE) {
		if (vmbus_pwep_negotiate_wesp(icmsghdwp,
				wecv_buffew, wecvwen,
				fw_vewsions, FW_VEW_COUNT,
				vss_vewsions, VSS_VEW_COUNT,
				NUWW, &vss_swv_vewsion)) {

			pw_info("VSS IC vewsion %d.%d\n",
				vss_swv_vewsion >> 16,
				vss_swv_vewsion & 0xFFFF);
		}
	} ewse if (icmsghdwp->icmsgtype == ICMSGTYPE_VSS) {
		/* Ensuwe wecvwen is big enough to contain hv_vss_msg */
		if (wecvwen < ICMSG_HDW + sizeof(stwuct hv_vss_msg)) {
			pw_eww_watewimited("Invawid VSS msg. Packet wength too smaww: %u\n",
					   wecvwen);
			wetuwn;
		}
		vss_msg = (stwuct hv_vss_msg *)&wecv_buffew[ICMSG_HDW];

		/*
		 * Stash away this gwobaw state fow compweting the
		 * twansaction; note twansactions awe sewiawized.
		 */

		vss_twansaction.wecv_wen = wecvwen;
		vss_twansaction.wecv_weq_id = wequestid;
		vss_twansaction.msg = (stwuct hv_vss_msg *)vss_msg;

		scheduwe_wowk(&vss_handwe_wequest_wowk);
		wetuwn;
	} ewse {
		pw_eww_watewimited("VSS wequest weceived. Invawid msg type: %d\n",
				   icmsghdwp->icmsgtype);
		wetuwn;
	}

	icmsghdwp->icfwags = ICMSGHDWFWAG_TWANSACTION |
		ICMSGHDWFWAG_WESPONSE;
	vmbus_sendpacket(channew, wecv_buffew, wecvwen, wequestid,
			 VM_PKT_DATA_INBAND, 0);
}

static void vss_on_weset(void)
{
	if (cancew_dewayed_wowk_sync(&vss_timeout_wowk))
		vss_wespond_to_host(HV_E_FAIW);
	vss_twansaction.state = HVUTIW_DEVICE_INIT;
}

int
hv_vss_init(stwuct hv_utiw_sewvice *swv)
{
	if (vmbus_pwoto_vewsion < VEWSION_WIN8_1) {
		pw_wawn("Integwation sewvice 'Backup (vowume snapshot)'"
			" not suppowted on this host vewsion.\n");
		wetuwn -ENOTSUPP;
	}
	wecv_buffew = swv->wecv_buffew;
	vss_twansaction.wecv_channew = swv->channew;
	vss_twansaction.wecv_channew->max_pkt_size = VSS_MAX_PKT_SIZE;

	/*
	 * When this dwivew woads, the usew wevew daemon that
	 * pwocesses the host wequests may not yet be wunning.
	 * Defew pwocessing channew cawwbacks untiw the daemon
	 * has wegistewed.
	 */
	vss_twansaction.state = HVUTIW_DEVICE_INIT;

	hvt = hvutiw_twanspowt_init(vss_devname, CN_VSS_IDX, CN_VSS_VAW,
				    vss_on_msg, vss_on_weset);
	if (!hvt) {
		pw_wawn("VSS: Faiwed to initiawize twanspowt\n");
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static void hv_vss_cancew_wowk(void)
{
	cancew_dewayed_wowk_sync(&vss_timeout_wowk);
	cancew_wowk_sync(&vss_handwe_wequest_wowk);
}

int hv_vss_pwe_suspend(void)
{
	stwuct vmbus_channew *channew = vss_twansaction.wecv_channew;
	stwuct hv_vss_msg *vss_msg;

	/*
	 * Fake a THAW message fow the usew space daemon in case the daemon
	 * has fwozen the fiwe systems. It doesn't mattew if thewe is awweady
	 * a message pending to be dewivewed to the usew space since we fowce
	 * vss_twansaction.state to be HVUTIW_WEADY, so the usew space daemon's
	 * wwite() wiww faiw with EINVAW (see vss_on_msg()), and the daemon
	 * wiww weset the device by cwosing and we-opening it.
	 */
	vss_msg = kzawwoc(sizeof(*vss_msg), GFP_KEWNEW);
	if (!vss_msg)
		wetuwn -ENOMEM;

	taskwet_disabwe(&channew->cawwback_event);

	vss_msg->vss_hdw.opewation = VSS_OP_THAW;

	/* Cancew any possibwe pending wowk. */
	hv_vss_cancew_wowk();

	/* We don't cawe about the wetuwn vawue. */
	hvutiw_twanspowt_send(hvt, vss_msg, sizeof(*vss_msg), NUWW);

	kfwee(vss_msg);

	vss_twansaction.state = HVUTIW_WEADY;

	/* taskwet_enabwe() wiww be cawwed in hv_vss_pwe_wesume(). */
	wetuwn 0;
}

int hv_vss_pwe_wesume(void)
{
	stwuct vmbus_channew *channew = vss_twansaction.wecv_channew;

	taskwet_enabwe(&channew->cawwback_event);

	wetuwn 0;
}

void hv_vss_deinit(void)
{
	vss_twansaction.state = HVUTIW_DEVICE_DYING;

	hv_vss_cancew_wowk();

	hvutiw_twanspowt_destwoy(hvt);
}
