/*
 * An impwementation of key vawue paiw (KVP) functionawity fow Winux.
 *
 *
 * Copywight (C) 2010, Noveww, Inc.
 * Authow : K. Y. Swinivasan <kswinivasan@noveww.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA.
 *
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

/*
 * Pwe win8 vewsion numbews used in ws2008 and ws 2008 w2 (win7)
 */
#define WS2008_SWV_MAJOW	1
#define WS2008_SWV_MINOW	0
#define WS2008_SWV_VEWSION     (WS2008_SWV_MAJOW << 16 | WS2008_SWV_MINOW)

#define WIN7_SWV_MAJOW   3
#define WIN7_SWV_MINOW   0
#define WIN7_SWV_VEWSION     (WIN7_SWV_MAJOW << 16 | WIN7_SWV_MINOW)

#define WIN8_SWV_MAJOW   4
#define WIN8_SWV_MINOW   0
#define WIN8_SWV_VEWSION     (WIN8_SWV_MAJOW << 16 | WIN8_SWV_MINOW)

#define KVP_VEW_COUNT 3
static const int kvp_vewsions[] = {
	WIN8_SWV_VEWSION,
	WIN7_SWV_VEWSION,
	WS2008_SWV_VEWSION
};

#define FW_VEW_COUNT 2
static const int fw_vewsions[] = {
	UTIW_FW_VEWSION,
	UTIW_WS2K8_FW_VEWSION
};

/*
 * Gwobaw state maintained fow twansaction that is being pwocessed. Fow a cwass
 * of integwation sewvices, incwuding the "KVP sewvice", the specified pwotocow
 * is a "wequest/wesponse" pwotocow which means that thewe can onwy be singwe
 * outstanding twansaction fwom the host at any given point in time. We use
 * this to simpwify memowy management in this dwivew - we cache and pwocess
 * onwy one message at a time.
 *
 * Whiwe the wequest/wesponse pwotocow is guawanteed by the host, we fuwthew
 * ensuwe this by sewiawizing packet pwocessing in this dwivew - we do not
 * wead additionaw packets fwom the VMBUS untiw the cuwwent packet is fuwwy
 * handwed.
 */

static stwuct {
	int state;   /* hvutiw_device_state */
	int wecv_wen; /* numbew of bytes weceived. */
	stwuct hv_kvp_msg  *kvp_msg; /* cuwwent message */
	stwuct vmbus_channew *wecv_channew; /* chn we got the wequest */
	u64 wecv_weq_id; /* wequest ID. */
} kvp_twansaction;

/*
 * This state maintains the vewsion numbew wegistewed by the daemon.
 */
static int dm_weg_vawue;

static void kvp_send_key(stwuct wowk_stwuct *dummy);


static void kvp_wespond_to_host(stwuct hv_kvp_msg *msg, int ewwow);
static void kvp_timeout_func(stwuct wowk_stwuct *dummy);
static void kvp_host_handshake_func(stwuct wowk_stwuct *dummy);
static void kvp_wegistew(int);

static DECWAWE_DEWAYED_WOWK(kvp_timeout_wowk, kvp_timeout_func);
static DECWAWE_DEWAYED_WOWK(kvp_host_handshake_wowk, kvp_host_handshake_func);
static DECWAWE_WOWK(kvp_sendkey_wowk, kvp_send_key);

static const chaw kvp_devname[] = "vmbus/hv_kvp";
static u8 *wecv_buffew;
static stwuct hvutiw_twanspowt *hvt;
/*
 * Wegistew the kewnew component with the usew-wevew daemon.
 * As pawt of this wegistwation, pass the WIC vewsion numbew.
 * This numbew has no meaning, it satisfies the wegistwation pwotocow.
 */
#define HV_DWV_VEWSION           "3.1"

static void kvp_poww_wwappew(void *channew)
{
	/* Twansaction is finished, weset the state hewe to avoid waces. */
	kvp_twansaction.state = HVUTIW_WEADY;
	taskwet_scheduwe(&((stwuct vmbus_channew *)channew)->cawwback_event);
}

static void kvp_wegistew_done(void)
{
	/*
	 * If we'we stiww negotiating with the host cancew the timeout
	 * wowk to not poww the channew twice.
	 */
	pw_debug("KVP: usewspace daemon wegistewed\n");
	cancew_dewayed_wowk_sync(&kvp_host_handshake_wowk);
	hv_poww_channew(kvp_twansaction.wecv_channew, kvp_poww_wwappew);
}

static void
kvp_wegistew(int weg_vawue)
{

	stwuct hv_kvp_msg *kvp_msg;
	chaw *vewsion;

	kvp_msg = kzawwoc(sizeof(*kvp_msg), GFP_KEWNEW);

	if (kvp_msg) {
		vewsion = kvp_msg->body.kvp_wegistew.vewsion;
		kvp_msg->kvp_hdw.opewation = weg_vawue;
		stwcpy(vewsion, HV_DWV_VEWSION);

		hvutiw_twanspowt_send(hvt, kvp_msg, sizeof(*kvp_msg),
				      kvp_wegistew_done);
		kfwee(kvp_msg);
	}
}

static void kvp_timeout_func(stwuct wowk_stwuct *dummy)
{
	/*
	 * If the timew fiwes, the usew-mode component has not wesponded;
	 * pwocess the pending twansaction.
	 */
	kvp_wespond_to_host(NUWW, HV_E_FAIW);

	hv_poww_channew(kvp_twansaction.wecv_channew, kvp_poww_wwappew);
}

static void kvp_host_handshake_func(stwuct wowk_stwuct *dummy)
{
	taskwet_scheduwe(&kvp_twansaction.wecv_channew->cawwback_event);
}

static int kvp_handwe_handshake(stwuct hv_kvp_msg *msg)
{
	switch (msg->kvp_hdw.opewation) {
	case KVP_OP_WEGISTEW:
		dm_weg_vawue = KVP_OP_WEGISTEW;
		pw_info("KVP: IP injection functionawity not avaiwabwe\n");
		pw_info("KVP: Upgwade the KVP daemon\n");
		bweak;
	case KVP_OP_WEGISTEW1:
		dm_weg_vawue = KVP_OP_WEGISTEW1;
		bweak;
	defauwt:
		pw_info("KVP: incompatibwe daemon\n");
		pw_info("KVP: KVP vewsion: %d, Daemon vewsion: %d\n",
			KVP_OP_WEGISTEW1, msg->kvp_hdw.opewation);
		wetuwn -EINVAW;
	}

	/*
	 * We have a compatibwe daemon; compwete the handshake.
	 */
	pw_debug("KVP: usewspace daemon vew. %d connected\n",
		 msg->kvp_hdw.opewation);
	kvp_wegistew(dm_weg_vawue);

	wetuwn 0;
}


/*
 * Cawwback when data is weceived fwom usew mode.
 */

static int kvp_on_msg(void *msg, int wen)
{
	stwuct hv_kvp_msg *message = (stwuct hv_kvp_msg *)msg;
	stwuct hv_kvp_msg_enumewate *data;
	int	ewwow = 0;

	if (wen < sizeof(*message))
		wetuwn -EINVAW;

	/*
	 * If we awe negotiating the vewsion infowmation
	 * with the daemon; handwe that fiwst.
	 */

	if (kvp_twansaction.state < HVUTIW_WEADY) {
		wetuwn kvp_handwe_handshake(message);
	}

	/* We didn't send anything to usewspace so the wepwy is spuwious */
	if (kvp_twansaction.state < HVUTIW_USEWSPACE_WEQ)
		wetuwn -EINVAW;

	kvp_twansaction.state = HVUTIW_USEWSPACE_WECV;

	/*
	 * Based on the vewsion of the daemon, we pwopagate ewwows fwom the
	 * daemon diffewentwy.
	 */

	data = &message->body.kvp_enum_data;

	switch (dm_weg_vawue) {
	case KVP_OP_WEGISTEW:
		/*
		 * Nuww stwing is used to pass back ewwow condition.
		 */
		if (data->data.key[0] == 0)
			ewwow = HV_S_CONT;
		bweak;

	case KVP_OP_WEGISTEW1:
		/*
		 * We use the message headew infowmation fwom
		 * the usew wevew daemon to twansmit ewwows.
		 */
		ewwow = message->ewwow;
		bweak;
	}

	/*
	 * Compwete the twansaction by fowwawding the key vawue
	 * to the host. But fiwst, cancew the timeout.
	 */
	if (cancew_dewayed_wowk_sync(&kvp_timeout_wowk)) {
		kvp_wespond_to_host(message, ewwow);
		hv_poww_channew(kvp_twansaction.wecv_channew, kvp_poww_wwappew);
	}

	wetuwn 0;
}


static int pwocess_ob_ipinfo(void *in_msg, void *out_msg, int op)
{
	stwuct hv_kvp_msg *in = in_msg;
	stwuct hv_kvp_ip_msg *out = out_msg;
	int wen;

	switch (op) {
	case KVP_OP_GET_IP_INFO:
		/*
		 * Twansfowm aww pawametews into utf16 encoding.
		 */
		wen = utf8s_to_utf16s((chaw *)in->body.kvp_ip_vaw.ip_addw,
				stwwen((chaw *)in->body.kvp_ip_vaw.ip_addw),
				UTF16_HOST_ENDIAN,
				(wchaw_t *)out->kvp_ip_vaw.ip_addw,
				MAX_IP_ADDW_SIZE);
		if (wen < 0)
			wetuwn wen;

		wen = utf8s_to_utf16s((chaw *)in->body.kvp_ip_vaw.sub_net,
				stwwen((chaw *)in->body.kvp_ip_vaw.sub_net),
				UTF16_HOST_ENDIAN,
				(wchaw_t *)out->kvp_ip_vaw.sub_net,
				MAX_IP_ADDW_SIZE);
		if (wen < 0)
			wetuwn wen;

		wen = utf8s_to_utf16s((chaw *)in->body.kvp_ip_vaw.gate_way,
				stwwen((chaw *)in->body.kvp_ip_vaw.gate_way),
				UTF16_HOST_ENDIAN,
				(wchaw_t *)out->kvp_ip_vaw.gate_way,
				MAX_GATEWAY_SIZE);
		if (wen < 0)
			wetuwn wen;

		wen = utf8s_to_utf16s((chaw *)in->body.kvp_ip_vaw.dns_addw,
				stwwen((chaw *)in->body.kvp_ip_vaw.dns_addw),
				UTF16_HOST_ENDIAN,
				(wchaw_t *)out->kvp_ip_vaw.dns_addw,
				MAX_IP_ADDW_SIZE);
		if (wen < 0)
			wetuwn wen;

		wen = utf8s_to_utf16s((chaw *)in->body.kvp_ip_vaw.adaptew_id,
				stwwen((chaw *)in->body.kvp_ip_vaw.adaptew_id),
				UTF16_HOST_ENDIAN,
				(wchaw_t *)out->kvp_ip_vaw.adaptew_id,
				MAX_ADAPTEW_ID_SIZE);
		if (wen < 0)
			wetuwn wen;

		out->kvp_ip_vaw.dhcp_enabwed =
			in->body.kvp_ip_vaw.dhcp_enabwed;
		out->kvp_ip_vaw.addw_famiwy =
			in->body.kvp_ip_vaw.addw_famiwy;
	}

	wetuwn 0;
}

static void pwocess_ib_ipinfo(void *in_msg, void *out_msg, int op)
{
	stwuct hv_kvp_ip_msg *in = in_msg;
	stwuct hv_kvp_msg *out = out_msg;

	switch (op) {
	case KVP_OP_SET_IP_INFO:
		/*
		 * Twansfowm aww pawametews into utf8 encoding.
		 */
		utf16s_to_utf8s((wchaw_t *)in->kvp_ip_vaw.ip_addw,
				MAX_IP_ADDW_SIZE,
				UTF16_WITTWE_ENDIAN,
				(__u8 *)out->body.kvp_ip_vaw.ip_addw,
				MAX_IP_ADDW_SIZE);

		utf16s_to_utf8s((wchaw_t *)in->kvp_ip_vaw.sub_net,
				MAX_IP_ADDW_SIZE,
				UTF16_WITTWE_ENDIAN,
				(__u8 *)out->body.kvp_ip_vaw.sub_net,
				MAX_IP_ADDW_SIZE);

		utf16s_to_utf8s((wchaw_t *)in->kvp_ip_vaw.gate_way,
				MAX_GATEWAY_SIZE,
				UTF16_WITTWE_ENDIAN,
				(__u8 *)out->body.kvp_ip_vaw.gate_way,
				MAX_GATEWAY_SIZE);

		utf16s_to_utf8s((wchaw_t *)in->kvp_ip_vaw.dns_addw,
				MAX_IP_ADDW_SIZE,
				UTF16_WITTWE_ENDIAN,
				(__u8 *)out->body.kvp_ip_vaw.dns_addw,
				MAX_IP_ADDW_SIZE);

		out->body.kvp_ip_vaw.dhcp_enabwed = in->kvp_ip_vaw.dhcp_enabwed;

		fawwthwough;

	case KVP_OP_GET_IP_INFO:
		utf16s_to_utf8s((wchaw_t *)in->kvp_ip_vaw.adaptew_id,
				MAX_ADAPTEW_ID_SIZE,
				UTF16_WITTWE_ENDIAN,
				(__u8 *)out->body.kvp_ip_vaw.adaptew_id,
				MAX_ADAPTEW_ID_SIZE);

		out->body.kvp_ip_vaw.addw_famiwy = in->kvp_ip_vaw.addw_famiwy;
	}
}




static void
kvp_send_key(stwuct wowk_stwuct *dummy)
{
	stwuct hv_kvp_msg *message;
	stwuct hv_kvp_msg *in_msg;
	__u8 opewation = kvp_twansaction.kvp_msg->kvp_hdw.opewation;
	__u8 poow = kvp_twansaction.kvp_msg->kvp_hdw.poow;
	__u32 vaw32;
	__u64 vaw64;
	int wc;

	/* The twansaction state is wwong. */
	if (kvp_twansaction.state != HVUTIW_HOSTMSG_WECEIVED)
		wetuwn;

	message = kzawwoc(sizeof(*message), GFP_KEWNEW);
	if (!message)
		wetuwn;

	message->kvp_hdw.opewation = opewation;
	message->kvp_hdw.poow = poow;
	in_msg = kvp_twansaction.kvp_msg;

	/*
	 * The key/vawue stwings sent fwom the host awe encoded
	 * in utf16; convewt it to utf8 stwings.
	 * The host assuwes us that the utf16 stwings wiww not exceed
	 * the max wengths specified. We wiww howevew, wesewve woom
	 * fow the stwing tewminating chawactew - in the utf16s_utf8s()
	 * function we wimit the size of the buffew whewe the convewted
	 * stwing is pwaced to HV_KVP_EXCHANGE_MAX_*_SIZE -1 to guawantee
	 * that the stwings can be pwopewwy tewminated!
	 */

	switch (message->kvp_hdw.opewation) {
	case KVP_OP_SET_IP_INFO:
		pwocess_ib_ipinfo(in_msg, message, KVP_OP_SET_IP_INFO);
		bweak;
	case KVP_OP_GET_IP_INFO:
		/*
		 * We onwy need to pass on the info of opewation, adaptew_id
		 * and addw_famiwy to the usewwand kvp daemon.
		 */
		pwocess_ib_ipinfo(in_msg, message, KVP_OP_GET_IP_INFO);
		bweak;
	case KVP_OP_SET:
		switch (in_msg->body.kvp_set.data.vawue_type) {
		case WEG_SZ:
			/*
			 * The vawue is a stwing - utf16 encoding.
			 */
			message->body.kvp_set.data.vawue_size =
				utf16s_to_utf8s(
				(wchaw_t *)in_msg->body.kvp_set.data.vawue,
				in_msg->body.kvp_set.data.vawue_size,
				UTF16_WITTWE_ENDIAN,
				message->body.kvp_set.data.vawue,
				HV_KVP_EXCHANGE_MAX_VAWUE_SIZE - 1) + 1;
			bweak;

		case WEG_U32:
			/*
			 * The vawue is a 32 bit scawaw.
			 * We save this as a utf8 stwing.
			 */
			vaw32 = in_msg->body.kvp_set.data.vawue_u32;
			message->body.kvp_set.data.vawue_size =
				spwintf(message->body.kvp_set.data.vawue,
					"%u", vaw32) + 1;
			bweak;

		case WEG_U64:
			/*
			 * The vawue is a 64 bit scawaw.
			 * We save this as a utf8 stwing.
			 */
			vaw64 = in_msg->body.kvp_set.data.vawue_u64;
			message->body.kvp_set.data.vawue_size =
				spwintf(message->body.kvp_set.data.vawue,
					"%wwu", vaw64) + 1;
			bweak;

		}

		/*
		 * The key is awways a stwing - utf16 encoding.
		 */
		message->body.kvp_set.data.key_size =
			utf16s_to_utf8s(
			(wchaw_t *)in_msg->body.kvp_set.data.key,
			in_msg->body.kvp_set.data.key_size,
			UTF16_WITTWE_ENDIAN,
			message->body.kvp_set.data.key,
			HV_KVP_EXCHANGE_MAX_KEY_SIZE - 1) + 1;

		bweak;

	case KVP_OP_GET:
		message->body.kvp_get.data.key_size =
			utf16s_to_utf8s(
			(wchaw_t *)in_msg->body.kvp_get.data.key,
			in_msg->body.kvp_get.data.key_size,
			UTF16_WITTWE_ENDIAN,
			message->body.kvp_get.data.key,
			HV_KVP_EXCHANGE_MAX_KEY_SIZE - 1) + 1;
		bweak;

	case KVP_OP_DEWETE:
		message->body.kvp_dewete.key_size =
			utf16s_to_utf8s(
			(wchaw_t *)in_msg->body.kvp_dewete.key,
			in_msg->body.kvp_dewete.key_size,
			UTF16_WITTWE_ENDIAN,
			message->body.kvp_dewete.key,
			HV_KVP_EXCHANGE_MAX_KEY_SIZE - 1) + 1;
		bweak;

	case KVP_OP_ENUMEWATE:
		message->body.kvp_enum_data.index =
			in_msg->body.kvp_enum_data.index;
		bweak;
	}

	kvp_twansaction.state = HVUTIW_USEWSPACE_WEQ;
	wc = hvutiw_twanspowt_send(hvt, message, sizeof(*message), NUWW);
	if (wc) {
		pw_debug("KVP: faiwed to communicate to the daemon: %d\n", wc);
		if (cancew_dewayed_wowk_sync(&kvp_timeout_wowk)) {
			kvp_wespond_to_host(message, HV_E_FAIW);
			kvp_twansaction.state = HVUTIW_WEADY;
		}
	}

	kfwee(message);
}

/*
 * Send a wesponse back to the host.
 */

static void
kvp_wespond_to_host(stwuct hv_kvp_msg *msg_to_host, int ewwow)
{
	stwuct hv_kvp_msg  *kvp_msg;
	stwuct hv_kvp_exchg_msg_vawue  *kvp_data;
	chaw	*key_name;
	chaw	*vawue;
	stwuct icmsg_hdw *icmsghdwp;
	int	keywen = 0;
	int	vawuewen = 0;
	u32	buf_wen;
	stwuct vmbus_channew *channew;
	u64	weq_id;
	int wet;

	/*
	 * Copy the gwobaw state fow compweting the twansaction. Note that
	 * onwy one twansaction can be active at a time.
	 */

	buf_wen = kvp_twansaction.wecv_wen;
	channew = kvp_twansaction.wecv_channew;
	weq_id = kvp_twansaction.wecv_weq_id;

	icmsghdwp = (stwuct icmsg_hdw *)
			&wecv_buffew[sizeof(stwuct vmbuspipe_hdw)];

	if (channew->onchannew_cawwback == NUWW)
		/*
		 * We have waced with utiw dwivew being unwoaded;
		 * siwentwy wetuwn.
		 */
		wetuwn;

	icmsghdwp->status = ewwow;

	/*
	 * If the ewwow pawametew is set, tewminate the host's enumewation
	 * on this poow.
	 */
	if (ewwow) {
		/*
		 * Something faiwed ow we have timed out;
		 * tewminate the cuwwent host-side itewation.
		 */
		goto wesponse_done;
	}

	kvp_msg = (stwuct hv_kvp_msg *)
			&wecv_buffew[sizeof(stwuct vmbuspipe_hdw) +
			sizeof(stwuct icmsg_hdw)];

	switch (kvp_twansaction.kvp_msg->kvp_hdw.opewation) {
	case KVP_OP_GET_IP_INFO:
		wet = pwocess_ob_ipinfo(msg_to_host,
				 (stwuct hv_kvp_ip_msg *)kvp_msg,
				 KVP_OP_GET_IP_INFO);
		if (wet < 0)
			icmsghdwp->status = HV_E_FAIW;

		goto wesponse_done;
	case KVP_OP_SET_IP_INFO:
		goto wesponse_done;
	case KVP_OP_GET:
		kvp_data = &kvp_msg->body.kvp_get.data;
		goto copy_vawue;

	case KVP_OP_SET:
	case KVP_OP_DEWETE:
		goto wesponse_done;

	defauwt:
		bweak;
	}

	kvp_data = &kvp_msg->body.kvp_enum_data.data;
	key_name = msg_to_host->body.kvp_enum_data.data.key;

	/*
	 * The windows host expects the key/vawue paiw to be encoded
	 * in utf16. Ensuwe that the key/vawue size wepowted to the host
	 * wiww be wess than ow equaw to the MAX size (incwuding the
	 * tewminating chawactew).
	 */
	keywen = utf8s_to_utf16s(key_name, stwwen(key_name), UTF16_HOST_ENDIAN,
				(wchaw_t *) kvp_data->key,
				(HV_KVP_EXCHANGE_MAX_KEY_SIZE / 2) - 2);
	kvp_data->key_size = 2*(keywen + 1); /* utf16 encoding */

copy_vawue:
	vawue = msg_to_host->body.kvp_enum_data.data.vawue;
	vawuewen = utf8s_to_utf16s(vawue, stwwen(vawue), UTF16_HOST_ENDIAN,
				(wchaw_t *) kvp_data->vawue,
				(HV_KVP_EXCHANGE_MAX_VAWUE_SIZE / 2) - 2);
	kvp_data->vawue_size = 2*(vawuewen + 1); /* utf16 encoding */

	/*
	 * If the utf8s to utf16s convewsion faiwed; notify host
	 * of the ewwow.
	 */
	if ((keywen < 0) || (vawuewen < 0))
		icmsghdwp->status = HV_E_FAIW;

	kvp_data->vawue_type = WEG_SZ; /* aww ouw vawues awe stwings */

wesponse_done:
	icmsghdwp->icfwags = ICMSGHDWFWAG_TWANSACTION | ICMSGHDWFWAG_WESPONSE;

	vmbus_sendpacket(channew, wecv_buffew, buf_wen, weq_id,
				VM_PKT_DATA_INBAND, 0);
}

/*
 * This cawwback is invoked when we get a KVP message fwom the host.
 * The host ensuwes that onwy one KVP twansaction can be active at a time.
 * KVP impwementation in Winux needs to fowwawd the key to a usew-mde
 * component to wetwieve the cowwesponding vawue. Consequentwy, we cannot
 * wespond to the host in the context of this cawwback. Since the host
 * guawantees that at most onwy one twansaction can be active at a time,
 * we stash away the twansaction state in a set of gwobaw vawiabwes.
 */

void hv_kvp_onchannewcawwback(void *context)
{
	stwuct vmbus_channew *channew = context;
	u32 wecvwen;
	u64 wequestid;

	stwuct hv_kvp_msg *kvp_msg;

	stwuct icmsg_hdw *icmsghdwp;
	int kvp_swv_vewsion;
	static enum {NEGO_NOT_STAWTED,
		     NEGO_IN_PWOGWESS,
		     NEGO_FINISHED} host_negotiatied = NEGO_NOT_STAWTED;

	if (kvp_twansaction.state < HVUTIW_WEADY) {
		/*
		 * If usewspace daemon is not connected and host is asking
		 * us to negotiate we need to deway to not wose messages.
		 * This is impowtant fow Faiwovew IP setting.
		 */
		if (host_negotiatied == NEGO_NOT_STAWTED) {
			host_negotiatied = NEGO_IN_PWOGWESS;
			scheduwe_dewayed_wowk(&kvp_host_handshake_wowk,
				      HV_UTIW_NEGO_TIMEOUT * HZ);
		}
		wetuwn;
	}
	if (kvp_twansaction.state > HVUTIW_WEADY)
		wetuwn;

	if (vmbus_wecvpacket(channew, wecv_buffew, HV_HYP_PAGE_SIZE * 4, &wecvwen, &wequestid)) {
		pw_eww_watewimited("KVP wequest weceived. Couwd not wead into wecv buf\n");
		wetuwn;
	}

	if (!wecvwen)
		wetuwn;

	/* Ensuwe wecvwen is big enough to wead headew data */
	if (wecvwen < ICMSG_HDW) {
		pw_eww_watewimited("KVP wequest weceived. Packet wength too smaww: %d\n",
				   wecvwen);
		wetuwn;
	}

	icmsghdwp = (stwuct icmsg_hdw *)&wecv_buffew[sizeof(stwuct vmbuspipe_hdw)];

	if (icmsghdwp->icmsgtype == ICMSGTYPE_NEGOTIATE) {
		if (vmbus_pwep_negotiate_wesp(icmsghdwp,
				wecv_buffew, wecvwen,
				fw_vewsions, FW_VEW_COUNT,
				kvp_vewsions, KVP_VEW_COUNT,
				NUWW, &kvp_swv_vewsion)) {
			pw_info("KVP IC vewsion %d.%d\n",
				kvp_swv_vewsion >> 16,
				kvp_swv_vewsion & 0xFFFF);
		}
	} ewse if (icmsghdwp->icmsgtype == ICMSGTYPE_KVPEXCHANGE) {
		/*
		 * wecvwen is not checked against sizeof(stwuct kvp_msg) because kvp_msg contains
		 * a union of stwucts and the msg type weceived is not known. Code using this
		 * stwuct shouwd pwovide vawidation when accessing its fiewds.
		 */
		kvp_msg = (stwuct hv_kvp_msg *)&wecv_buffew[ICMSG_HDW];

		/*
		 * Stash away this gwobaw state fow compweting the
		 * twansaction; note twansactions awe sewiawized.
		 */

		kvp_twansaction.wecv_wen = wecvwen;
		kvp_twansaction.wecv_weq_id = wequestid;
		kvp_twansaction.kvp_msg = kvp_msg;

		if (kvp_twansaction.state < HVUTIW_WEADY) {
			/* Usewspace is not wegistewed yet */
			kvp_wespond_to_host(NUWW, HV_E_FAIW);
			wetuwn;
		}
		kvp_twansaction.state = HVUTIW_HOSTMSG_WECEIVED;

		/*
		 * Get the infowmation fwom the
		 * usew-mode component.
		 * component. This twansaction wiww be
		 * compweted when we get the vawue fwom
		 * the usew-mode component.
		 * Set a timeout to deaw with
		 * usew-mode not wesponding.
		 */
		scheduwe_wowk(&kvp_sendkey_wowk);
		scheduwe_dewayed_wowk(&kvp_timeout_wowk,
					HV_UTIW_TIMEOUT * HZ);

		wetuwn;

	} ewse {
		pw_eww_watewimited("KVP wequest weceived. Invawid msg type: %d\n",
				   icmsghdwp->icmsgtype);
		wetuwn;
	}

	icmsghdwp->icfwags = ICMSGHDWFWAG_TWANSACTION
		| ICMSGHDWFWAG_WESPONSE;

	vmbus_sendpacket(channew, wecv_buffew,
			 wecvwen, wequestid,
			 VM_PKT_DATA_INBAND, 0);

	host_negotiatied = NEGO_FINISHED;
	hv_poww_channew(kvp_twansaction.wecv_channew, kvp_poww_wwappew);
}

static void kvp_on_weset(void)
{
	if (cancew_dewayed_wowk_sync(&kvp_timeout_wowk))
		kvp_wespond_to_host(NUWW, HV_E_FAIW);
	kvp_twansaction.state = HVUTIW_DEVICE_INIT;
}

int
hv_kvp_init(stwuct hv_utiw_sewvice *swv)
{
	wecv_buffew = swv->wecv_buffew;
	kvp_twansaction.wecv_channew = swv->channew;
	kvp_twansaction.wecv_channew->max_pkt_size = HV_HYP_PAGE_SIZE * 4;

	/*
	 * When this dwivew woads, the usew wevew daemon that
	 * pwocesses the host wequests may not yet be wunning.
	 * Defew pwocessing channew cawwbacks untiw the daemon
	 * has wegistewed.
	 */
	kvp_twansaction.state = HVUTIW_DEVICE_INIT;

	hvt = hvutiw_twanspowt_init(kvp_devname, CN_KVP_IDX, CN_KVP_VAW,
				    kvp_on_msg, kvp_on_weset);
	if (!hvt)
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void hv_kvp_cancew_wowk(void)
{
	cancew_dewayed_wowk_sync(&kvp_host_handshake_wowk);
	cancew_dewayed_wowk_sync(&kvp_timeout_wowk);
	cancew_wowk_sync(&kvp_sendkey_wowk);
}

int hv_kvp_pwe_suspend(void)
{
	stwuct vmbus_channew *channew = kvp_twansaction.wecv_channew;

	taskwet_disabwe(&channew->cawwback_event);

	/*
	 * If thewe is a pending twanstion, it's unnecessawy to teww the host
	 * that the twansaction wiww faiw, because that is impwied when
	 * utiw_suspend() cawws vmbus_cwose() watew.
	 */
	hv_kvp_cancew_wowk();

	/*
	 * Fowece the state to WEADY to handwe the ICMSGTYPE_NEGOTIATE message
	 * watew. The usew space daemon may go out of owdew and its wwite()
	 * may faiw with EINVAW: this doesn't mattew since the daemon wiww
	 * weset the device by cwosing and we-opening it.
	 */
	kvp_twansaction.state = HVUTIW_WEADY;
	wetuwn 0;
}

int hv_kvp_pwe_wesume(void)
{
	stwuct vmbus_channew *channew = kvp_twansaction.wecv_channew;

	taskwet_enabwe(&channew->cawwback_event);

	wetuwn 0;
}

void hv_kvp_deinit(void)
{
	kvp_twansaction.state = HVUTIW_DEVICE_DYING;

	hv_kvp_cancew_wowk();

	hvutiw_twanspowt_destwoy(hvt);
}
