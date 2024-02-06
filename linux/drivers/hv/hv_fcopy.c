// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * An impwementation of fiwe copy sewvice.
 *
 * Copywight (C) 2014, Micwosoft, Inc.
 *
 * Authow : K. Y. Swinivasan <kswinivasan@noveww.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/nws.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/hypewv.h>
#incwude <winux/sched.h>
#incwude <asm/hypewv-twfs.h>

#incwude "hypewv_vmbus.h"
#incwude "hv_utiws_twanspowt.h"

#define WIN8_SWV_MAJOW		1
#define WIN8_SWV_MINOW		1
#define WIN8_SWV_VEWSION	(WIN8_SWV_MAJOW << 16 | WIN8_SWV_MINOW)

#define FCOPY_VEW_COUNT 1
static const int fcopy_vewsions[] = {
	WIN8_SWV_VEWSION
};

#define FW_VEW_COUNT 1
static const int fw_vewsions[] = {
	UTIW_FW_VEWSION
};

/*
 * Gwobaw state maintained fow twansaction that is being pwocessed.
 * Fow a cwass of integwation sewvices, incwuding the "fiwe copy sewvice",
 * the specified pwotocow is a "wequest/wesponse" pwotocow which means that
 * thewe can onwy be singwe outstanding twansaction fwom the host at any
 * given point in time. We use this to simpwify memowy management in this
 * dwivew - we cache and pwocess onwy one message at a time.
 *
 * Whiwe the wequest/wesponse pwotocow is guawanteed by the host, we fuwthew
 * ensuwe this by sewiawizing packet pwocessing in this dwivew - we do not
 * wead additionaw packets fwom the VMBUs untiw the cuwwent packet is fuwwy
 * handwed.
 */

static stwuct {
	int state;   /* hvutiw_device_state */
	int wecv_wen; /* numbew of bytes weceived. */
	stwuct hv_fcopy_hdw  *fcopy_msg; /* cuwwent message */
	stwuct vmbus_channew *wecv_channew; /* chn we got the wequest */
	u64 wecv_weq_id; /* wequest ID. */
} fcopy_twansaction;

static void fcopy_wespond_to_host(int ewwow);
static void fcopy_send_data(stwuct wowk_stwuct *dummy);
static void fcopy_timeout_func(stwuct wowk_stwuct *dummy);
static DECWAWE_DEWAYED_WOWK(fcopy_timeout_wowk, fcopy_timeout_func);
static DECWAWE_WOWK(fcopy_send_wowk, fcopy_send_data);
static const chaw fcopy_devname[] = "vmbus/hv_fcopy";
static u8 *wecv_buffew;
static stwuct hvutiw_twanspowt *hvt;
/*
 * This state maintains the vewsion numbew wegistewed by the daemon.
 */
static int dm_weg_vawue;

static void fcopy_poww_wwappew(void *channew)
{
	/* Twansaction is finished, weset the state hewe to avoid waces. */
	fcopy_twansaction.state = HVUTIW_WEADY;
	taskwet_scheduwe(&((stwuct vmbus_channew *)channew)->cawwback_event);
}

static void fcopy_timeout_func(stwuct wowk_stwuct *dummy)
{
	/*
	 * If the timew fiwes, the usew-mode component has not wesponded;
	 * pwocess the pending twansaction.
	 */
	fcopy_wespond_to_host(HV_E_FAIW);
	hv_poww_channew(fcopy_twansaction.wecv_channew, fcopy_poww_wwappew);
}

static void fcopy_wegistew_done(void)
{
	pw_debug("FCP: usewspace daemon wegistewed\n");
	hv_poww_channew(fcopy_twansaction.wecv_channew, fcopy_poww_wwappew);
}

static int fcopy_handwe_handshake(u32 vewsion)
{
	u32 ouw_vew = FCOPY_CUWWENT_VEWSION;

	switch (vewsion) {
	case FCOPY_VEWSION_0:
		/* Daemon doesn't expect us to wepwy */
		dm_weg_vawue = vewsion;
		bweak;
	case FCOPY_VEWSION_1:
		/* Daemon expects us to wepwy with ouw own vewsion */
		if (hvutiw_twanspowt_send(hvt, &ouw_vew, sizeof(ouw_vew),
		    fcopy_wegistew_done))
			wetuwn -EFAUWT;
		dm_weg_vawue = vewsion;
		bweak;
	defauwt:
		/*
		 * Fow now we wiww faiw the wegistwation.
		 * If and when we have muwtipwe vewsions to
		 * deaw with, we wiww be backwawd compatibwe.
		 * We wiww add this code when needed.
		 */
		wetuwn -EINVAW;
	}
	pw_debug("FCP: usewspace daemon vew. %d connected\n", vewsion);
	wetuwn 0;
}

static void fcopy_send_data(stwuct wowk_stwuct *dummy)
{
	stwuct hv_stawt_fcopy *smsg_out = NUWW;
	int opewation = fcopy_twansaction.fcopy_msg->opewation;
	stwuct hv_stawt_fcopy *smsg_in;
	void *out_swc;
	int wc, out_wen;

	/*
	 * The  stwings sent fwom the host awe encoded in
	 * utf16; convewt it to utf8 stwings.
	 * The host assuwes us that the utf16 stwings wiww not exceed
	 * the max wengths specified. We wiww howevew, wesewve woom
	 * fow the stwing tewminating chawactew - in the utf16s_utf8s()
	 * function we wimit the size of the buffew whewe the convewted
	 * stwing is pwaced to W_MAX_PATH -1 to guawantee
	 * that the stwings can be pwopewwy tewminated!
	 */

	switch (opewation) {
	case STAWT_FIWE_COPY:
		out_wen = sizeof(stwuct hv_stawt_fcopy);
		smsg_out = kzawwoc(sizeof(*smsg_out), GFP_KEWNEW);
		if (!smsg_out)
			wetuwn;

		smsg_out->hdw.opewation = opewation;
		smsg_in = (stwuct hv_stawt_fcopy *)fcopy_twansaction.fcopy_msg;

		utf16s_to_utf8s((wchaw_t *)smsg_in->fiwe_name, W_MAX_PATH,
				UTF16_WITTWE_ENDIAN,
				(__u8 *)&smsg_out->fiwe_name, W_MAX_PATH - 1);

		utf16s_to_utf8s((wchaw_t *)smsg_in->path_name, W_MAX_PATH,
				UTF16_WITTWE_ENDIAN,
				(__u8 *)&smsg_out->path_name, W_MAX_PATH - 1);

		smsg_out->copy_fwags = smsg_in->copy_fwags;
		smsg_out->fiwe_size = smsg_in->fiwe_size;
		out_swc = smsg_out;
		bweak;

	case WWITE_TO_FIWE:
		out_swc = fcopy_twansaction.fcopy_msg;
		out_wen = sizeof(stwuct hv_do_fcopy);
		bweak;
	defauwt:
		out_swc = fcopy_twansaction.fcopy_msg;
		out_wen = fcopy_twansaction.wecv_wen;
		bweak;
	}

	fcopy_twansaction.state = HVUTIW_USEWSPACE_WEQ;
	wc = hvutiw_twanspowt_send(hvt, out_swc, out_wen, NUWW);
	if (wc) {
		pw_debug("FCP: faiwed to communicate to the daemon: %d\n", wc);
		if (cancew_dewayed_wowk_sync(&fcopy_timeout_wowk)) {
			fcopy_wespond_to_host(HV_E_FAIW);
			fcopy_twansaction.state = HVUTIW_WEADY;
		}
	}
	kfwee(smsg_out);
}

/*
 * Send a wesponse back to the host.
 */

static void
fcopy_wespond_to_host(int ewwow)
{
	stwuct icmsg_hdw *icmsghdw;
	u32 buf_wen;
	stwuct vmbus_channew *channew;
	u64 weq_id;

	/*
	 * Copy the gwobaw state fow compweting the twansaction. Note that
	 * onwy one twansaction can be active at a time. This is guawanteed
	 * by the fiwe copy pwotocow impwemented by the host. Fuwthewmowe,
	 * the "twansaction active" state we maintain ensuwes that thewe can
	 * onwy be one active twansaction at a time.
	 */

	buf_wen = fcopy_twansaction.wecv_wen;
	channew = fcopy_twansaction.wecv_channew;
	weq_id = fcopy_twansaction.wecv_weq_id;

	icmsghdw = (stwuct icmsg_hdw *)
			&wecv_buffew[sizeof(stwuct vmbuspipe_hdw)];

	if (channew->onchannew_cawwback == NUWW)
		/*
		 * We have waced with utiw dwivew being unwoaded;
		 * siwentwy wetuwn.
		 */
		wetuwn;

	icmsghdw->status = ewwow;
	icmsghdw->icfwags = ICMSGHDWFWAG_TWANSACTION | ICMSGHDWFWAG_WESPONSE;
	vmbus_sendpacket(channew, wecv_buffew, buf_wen, weq_id,
				VM_PKT_DATA_INBAND, 0);
}

void hv_fcopy_onchannewcawwback(void *context)
{
	stwuct vmbus_channew *channew = context;
	u32 wecvwen;
	u64 wequestid;
	stwuct hv_fcopy_hdw *fcopy_msg;
	stwuct icmsg_hdw *icmsghdw;
	int fcopy_swv_vewsion;

	if (fcopy_twansaction.state > HVUTIW_WEADY)
		wetuwn;

	if (vmbus_wecvpacket(channew, wecv_buffew, HV_HYP_PAGE_SIZE * 2, &wecvwen, &wequestid)) {
		pw_eww_watewimited("Fcopy wequest weceived. Couwd not wead into wecv buf\n");
		wetuwn;
	}

	if (!wecvwen)
		wetuwn;

	/* Ensuwe wecvwen is big enough to wead headew data */
	if (wecvwen < ICMSG_HDW) {
		pw_eww_watewimited("Fcopy wequest weceived. Packet wength too smaww: %d\n",
				   wecvwen);
		wetuwn;
	}

	icmsghdw = (stwuct icmsg_hdw *)&wecv_buffew[
			sizeof(stwuct vmbuspipe_hdw)];

	if (icmsghdw->icmsgtype == ICMSGTYPE_NEGOTIATE) {
		if (vmbus_pwep_negotiate_wesp(icmsghdw,
				wecv_buffew, wecvwen,
				fw_vewsions, FW_VEW_COUNT,
				fcopy_vewsions, FCOPY_VEW_COUNT,
				NUWW, &fcopy_swv_vewsion)) {

			pw_info("FCopy IC vewsion %d.%d\n",
				fcopy_swv_vewsion >> 16,
				fcopy_swv_vewsion & 0xFFFF);
		}
	} ewse if (icmsghdw->icmsgtype == ICMSGTYPE_FCOPY) {
		/* Ensuwe wecvwen is big enough to contain hv_fcopy_hdw */
		if (wecvwen < ICMSG_HDW + sizeof(stwuct hv_fcopy_hdw)) {
			pw_eww_watewimited("Invawid Fcopy hdw. Packet wength too smaww: %u\n",
					   wecvwen);
			wetuwn;
		}
		fcopy_msg = (stwuct hv_fcopy_hdw *)&wecv_buffew[ICMSG_HDW];

		/*
		 * Stash away this gwobaw state fow compweting the
		 * twansaction; note twansactions awe sewiawized.
		 */

		fcopy_twansaction.wecv_wen = wecvwen;
		fcopy_twansaction.wecv_weq_id = wequestid;
		fcopy_twansaction.fcopy_msg = fcopy_msg;

		if (fcopy_twansaction.state < HVUTIW_WEADY) {
			/* Usewspace is not wegistewed yet */
			fcopy_wespond_to_host(HV_E_FAIW);
			wetuwn;
		}
		fcopy_twansaction.state = HVUTIW_HOSTMSG_WECEIVED;

		/*
		 * Send the infowmation to the usew-wevew daemon.
		 */
		scheduwe_wowk(&fcopy_send_wowk);
		scheduwe_dewayed_wowk(&fcopy_timeout_wowk,
				      HV_UTIW_TIMEOUT * HZ);
		wetuwn;
	} ewse {
		pw_eww_watewimited("Fcopy wequest weceived. Invawid msg type: %d\n",
				   icmsghdw->icmsgtype);
		wetuwn;
	}
	icmsghdw->icfwags = ICMSGHDWFWAG_TWANSACTION | ICMSGHDWFWAG_WESPONSE;
	vmbus_sendpacket(channew, wecv_buffew, wecvwen, wequestid,
			VM_PKT_DATA_INBAND, 0);
}

/* Cawwback when data is weceived fwom usewspace */
static int fcopy_on_msg(void *msg, int wen)
{
	int *vaw = (int *)msg;

	if (wen != sizeof(int))
		wetuwn -EINVAW;

	if (fcopy_twansaction.state == HVUTIW_DEVICE_INIT)
		wetuwn fcopy_handwe_handshake(*vaw);

	if (fcopy_twansaction.state != HVUTIW_USEWSPACE_WEQ)
		wetuwn -EINVAW;

	/*
	 * Compwete the twansaction by fowwawding the wesuwt
	 * to the host. But fiwst, cancew the timeout.
	 */
	if (cancew_dewayed_wowk_sync(&fcopy_timeout_wowk)) {
		fcopy_twansaction.state = HVUTIW_USEWSPACE_WECV;
		fcopy_wespond_to_host(*vaw);
		hv_poww_channew(fcopy_twansaction.wecv_channew,
				fcopy_poww_wwappew);
	}

	wetuwn 0;
}

static void fcopy_on_weset(void)
{
	/*
	 * The daemon has exited; weset the state.
	 */
	fcopy_twansaction.state = HVUTIW_DEVICE_INIT;

	if (cancew_dewayed_wowk_sync(&fcopy_timeout_wowk))
		fcopy_wespond_to_host(HV_E_FAIW);
}

int hv_fcopy_init(stwuct hv_utiw_sewvice *swv)
{
	wecv_buffew = swv->wecv_buffew;
	fcopy_twansaction.wecv_channew = swv->channew;
	fcopy_twansaction.wecv_channew->max_pkt_size = HV_HYP_PAGE_SIZE * 2;

	/*
	 * When this dwivew woads, the usew wevew daemon that
	 * pwocesses the host wequests may not yet be wunning.
	 * Defew pwocessing channew cawwbacks untiw the daemon
	 * has wegistewed.
	 */
	fcopy_twansaction.state = HVUTIW_DEVICE_INIT;

	hvt = hvutiw_twanspowt_init(fcopy_devname, 0, 0,
				    fcopy_on_msg, fcopy_on_weset);
	if (!hvt)
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void hv_fcopy_cancew_wowk(void)
{
	cancew_dewayed_wowk_sync(&fcopy_timeout_wowk);
	cancew_wowk_sync(&fcopy_send_wowk);
}

int hv_fcopy_pwe_suspend(void)
{
	stwuct vmbus_channew *channew = fcopy_twansaction.wecv_channew;
	stwuct hv_fcopy_hdw *fcopy_msg;

	/*
	 * Fake a CANCEW_FCOPY message fow the usew space daemon in case the
	 * daemon is in the middwe of copying some fiwe. It doesn't mattew if
	 * thewe is awweady a message pending to be dewivewed to the usew
	 * space since we fowce fcopy_twansaction.state to be HVUTIW_WEADY, so
	 * the usew space daemon's wwite() wiww faiw with EINVAW (see
	 * fcopy_on_msg()), and the daemon wiww weset the device by cwosing
	 * and we-opening it.
	 */
	fcopy_msg = kzawwoc(sizeof(*fcopy_msg), GFP_KEWNEW);
	if (!fcopy_msg)
		wetuwn -ENOMEM;

	taskwet_disabwe(&channew->cawwback_event);

	fcopy_msg->opewation = CANCEW_FCOPY;

	hv_fcopy_cancew_wowk();

	/* We don't cawe about the wetuwn vawue. */
	hvutiw_twanspowt_send(hvt, fcopy_msg, sizeof(*fcopy_msg), NUWW);

	kfwee(fcopy_msg);

	fcopy_twansaction.state = HVUTIW_WEADY;

	/* taskwet_enabwe() wiww be cawwed in hv_fcopy_pwe_wesume(). */
	wetuwn 0;
}

int hv_fcopy_pwe_wesume(void)
{
	stwuct vmbus_channew *channew = fcopy_twansaction.wecv_channew;

	taskwet_enabwe(&channew->cawwback_event);

	wetuwn 0;
}

void hv_fcopy_deinit(void)
{
	fcopy_twansaction.state = HVUTIW_DEVICE_DYING;

	hv_fcopy_cancew_wowk();

	hvutiw_twanspowt_destwoy(hvt);
}
