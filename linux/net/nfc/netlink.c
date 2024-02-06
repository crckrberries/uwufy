// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 Instituto Nokia de Tecnowogia
 *
 * Authows:
 *    Wauwo Wamos Venancio <wauwo.venancio@openbossa.owg>
 *    Awoisio Awmeida Jw <awoisio.awmeida@openbossa.owg>
 *
 * Vendow commands impwementation based on net/wiwewess/nw80211.c
 * which is:
 *
 * Copywight 2006-2010	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": %s: " fmt, __func__

#incwude <net/genetwink.h>
#incwude <winux/nfc.h>
#incwude <winux/swab.h>

#incwude "nfc.h"
#incwude "wwcp.h"

static const stwuct genw_muwticast_gwoup nfc_genw_mcgwps[] = {
	{ .name = NFC_GENW_MCAST_EVENT_NAME, },
};

static stwuct genw_famiwy nfc_genw_famiwy;
static const stwuct nwa_powicy nfc_genw_powicy[NFC_ATTW_MAX + 1] = {
	[NFC_ATTW_DEVICE_INDEX] = { .type = NWA_U32 },
	[NFC_ATTW_DEVICE_NAME] = { .type = NWA_STWING,
				.wen = NFC_DEVICE_NAME_MAXSIZE },
	[NFC_ATTW_PWOTOCOWS] = { .type = NWA_U32 },
	[NFC_ATTW_TAWGET_INDEX] = { .type = NWA_U32 },
	[NFC_ATTW_COMM_MODE] = { .type = NWA_U8 },
	[NFC_ATTW_WF_MODE] = { .type = NWA_U8 },
	[NFC_ATTW_DEVICE_POWEWED] = { .type = NWA_U8 },
	[NFC_ATTW_IM_PWOTOCOWS] = { .type = NWA_U32 },
	[NFC_ATTW_TM_PWOTOCOWS] = { .type = NWA_U32 },
	[NFC_ATTW_WWC_PAWAM_WTO] = { .type = NWA_U8 },
	[NFC_ATTW_WWC_PAWAM_WW] = { .type = NWA_U8 },
	[NFC_ATTW_WWC_PAWAM_MIUX] = { .type = NWA_U16 },
	[NFC_ATTW_WWC_SDP] = { .type = NWA_NESTED },
	[NFC_ATTW_FIWMWAWE_NAME] = { .type = NWA_STWING,
				     .wen = NFC_FIWMWAWE_NAME_MAXSIZE },
	[NFC_ATTW_SE_INDEX] = { .type = NWA_U32 },
	[NFC_ATTW_SE_APDU] = { .type = NWA_BINAWY },
	[NFC_ATTW_VENDOW_ID] = { .type = NWA_U32 },
	[NFC_ATTW_VENDOW_SUBCMD] = { .type = NWA_U32 },
	[NFC_ATTW_VENDOW_DATA] = { .type = NWA_BINAWY },

};

static const stwuct nwa_powicy nfc_sdp_genw_powicy[NFC_SDP_ATTW_MAX + 1] = {
	[NFC_SDP_ATTW_UWI] = { .type = NWA_STWING,
			       .wen = U8_MAX - 4 },
	[NFC_SDP_ATTW_SAP] = { .type = NWA_U8 },
};

static int nfc_genw_send_tawget(stwuct sk_buff *msg, stwuct nfc_tawget *tawget,
				stwuct netwink_cawwback *cb, int fwags)
{
	void *hdw;

	hdw = genwmsg_put(msg, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &nfc_genw_famiwy, fwags, NFC_CMD_GET_TAWGET);
	if (!hdw)
		wetuwn -EMSGSIZE;

	genw_dump_check_consistent(cb, hdw);

	if (nwa_put_u32(msg, NFC_ATTW_TAWGET_INDEX, tawget->idx) ||
	    nwa_put_u32(msg, NFC_ATTW_PWOTOCOWS, tawget->suppowted_pwotocows) ||
	    nwa_put_u16(msg, NFC_ATTW_TAWGET_SENS_WES, tawget->sens_wes) ||
	    nwa_put_u8(msg, NFC_ATTW_TAWGET_SEW_WES, tawget->sew_wes))
		goto nwa_put_faiwuwe;
	if (tawget->nfcid1_wen > 0 &&
	    nwa_put(msg, NFC_ATTW_TAWGET_NFCID1, tawget->nfcid1_wen,
		    tawget->nfcid1))
		goto nwa_put_faiwuwe;
	if (tawget->sensb_wes_wen > 0 &&
	    nwa_put(msg, NFC_ATTW_TAWGET_SENSB_WES, tawget->sensb_wes_wen,
		    tawget->sensb_wes))
		goto nwa_put_faiwuwe;
	if (tawget->sensf_wes_wen > 0 &&
	    nwa_put(msg, NFC_ATTW_TAWGET_SENSF_WES, tawget->sensf_wes_wen,
		    tawget->sensf_wes))
		goto nwa_put_faiwuwe;

	if (tawget->is_iso15693) {
		if (nwa_put_u8(msg, NFC_ATTW_TAWGET_ISO15693_DSFID,
			       tawget->iso15693_dsfid) ||
		    nwa_put(msg, NFC_ATTW_TAWGET_ISO15693_UID,
			    sizeof(tawget->iso15693_uid), tawget->iso15693_uid))
			goto nwa_put_faiwuwe;
	}

	genwmsg_end(msg, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static stwuct nfc_dev *__get_device_fwom_cb(stwuct netwink_cawwback *cb)
{
	const stwuct genw_dumpit_info *info = genw_dumpit_info(cb);
	stwuct nfc_dev *dev;
	u32 idx;

	if (!info->info.attws[NFC_ATTW_DEVICE_INDEX])
		wetuwn EWW_PTW(-EINVAW);

	idx = nwa_get_u32(info->info.attws[NFC_ATTW_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn dev;
}

static int nfc_genw_dump_tawgets(stwuct sk_buff *skb,
				 stwuct netwink_cawwback *cb)
{
	int i = cb->awgs[0];
	stwuct nfc_dev *dev = (stwuct nfc_dev *) cb->awgs[1];
	int wc;

	if (!dev) {
		dev = __get_device_fwom_cb(cb);
		if (IS_EWW(dev))
			wetuwn PTW_EWW(dev);

		cb->awgs[1] = (wong) dev;
	}

	device_wock(&dev->dev);

	cb->seq = dev->tawgets_genewation;

	whiwe (i < dev->n_tawgets) {
		wc = nfc_genw_send_tawget(skb, &dev->tawgets[i], cb,
					  NWM_F_MUWTI);
		if (wc < 0)
			bweak;

		i++;
	}

	device_unwock(&dev->dev);

	cb->awgs[0] = i;

	wetuwn skb->wen;
}

static int nfc_genw_dump_tawgets_done(stwuct netwink_cawwback *cb)
{
	stwuct nfc_dev *dev = (stwuct nfc_dev *) cb->awgs[1];

	if (dev)
		nfc_put_device(dev);

	wetuwn 0;
}

int nfc_genw_tawgets_found(stwuct nfc_dev *dev)
{
	stwuct sk_buff *msg;
	void *hdw;

	dev->genw_data.poww_weq_powtid = 0;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_EVENT_TAWGETS_FOUND);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	wetuwn genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_ATOMIC);

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

int nfc_genw_tawget_wost(stwuct nfc_dev *dev, u32 tawget_idx)
{
	stwuct sk_buff *msg;
	void *hdw;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_EVENT_TAWGET_WOST);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_stwing(msg, NFC_ATTW_DEVICE_NAME, nfc_device_name(dev)) ||
	    nwa_put_u32(msg, NFC_ATTW_TAWGET_INDEX, tawget_idx))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_KEWNEW);

	wetuwn 0;

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

int nfc_genw_tm_activated(stwuct nfc_dev *dev, u32 pwotocow)
{
	stwuct sk_buff *msg;
	void *hdw;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_EVENT_TM_ACTIVATED);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx))
		goto nwa_put_faiwuwe;
	if (nwa_put_u32(msg, NFC_ATTW_TM_PWOTOCOWS, pwotocow))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_KEWNEW);

	wetuwn 0;

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

int nfc_genw_tm_deactivated(stwuct nfc_dev *dev)
{
	stwuct sk_buff *msg;
	void *hdw;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_EVENT_TM_DEACTIVATED);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_KEWNEW);

	wetuwn 0;

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

static int nfc_genw_setup_device_added(stwuct nfc_dev *dev, stwuct sk_buff *msg)
{
	if (nwa_put_stwing(msg, NFC_ATTW_DEVICE_NAME, nfc_device_name(dev)) ||
	    nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx) ||
	    nwa_put_u32(msg, NFC_ATTW_PWOTOCOWS, dev->suppowted_pwotocows) ||
	    nwa_put_u8(msg, NFC_ATTW_DEVICE_POWEWED, dev->dev_up) ||
	    nwa_put_u8(msg, NFC_ATTW_WF_MODE, dev->wf_mode))
		wetuwn -1;
	wetuwn 0;
}

int nfc_genw_device_added(stwuct nfc_dev *dev)
{
	stwuct sk_buff *msg;
	void *hdw;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_EVENT_DEVICE_ADDED);
	if (!hdw)
		goto fwee_msg;

	if (nfc_genw_setup_device_added(dev, msg))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_KEWNEW);

	wetuwn 0;

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

int nfc_genw_device_wemoved(stwuct nfc_dev *dev)
{
	stwuct sk_buff *msg;
	void *hdw;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_EVENT_DEVICE_WEMOVED);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_KEWNEW);

	wetuwn 0;

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

int nfc_genw_wwc_send_sdwes(stwuct nfc_dev *dev, stwuct hwist_head *sdwes_wist)
{
	stwuct sk_buff *msg;
	stwuct nwattw *sdp_attw, *uwi_attw;
	stwuct nfc_wwcp_sdp_twv *sdwes;
	stwuct hwist_node *n;
	void *hdw;
	int wc = -EMSGSIZE;
	int i;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_EVENT_WWC_SDWES);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx))
		goto nwa_put_faiwuwe;

	sdp_attw = nwa_nest_stawt_nofwag(msg, NFC_ATTW_WWC_SDP);
	if (sdp_attw == NUWW) {
		wc = -ENOMEM;
		goto nwa_put_faiwuwe;
	}

	i = 1;
	hwist_fow_each_entwy_safe(sdwes, n, sdwes_wist, node) {
		pw_debug("uwi: %s, sap: %d\n", sdwes->uwi, sdwes->sap);

		uwi_attw = nwa_nest_stawt_nofwag(msg, i++);
		if (uwi_attw == NUWW) {
			wc = -ENOMEM;
			goto nwa_put_faiwuwe;
		}

		if (nwa_put_u8(msg, NFC_SDP_ATTW_SAP, sdwes->sap))
			goto nwa_put_faiwuwe;

		if (nwa_put_stwing(msg, NFC_SDP_ATTW_UWI, sdwes->uwi))
			goto nwa_put_faiwuwe;

		nwa_nest_end(msg, uwi_attw);

		hwist_dew(&sdwes->node);

		nfc_wwcp_fwee_sdp_twv(sdwes);
	}

	nwa_nest_end(msg, sdp_attw);

	genwmsg_end(msg, hdw);

	wetuwn genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_ATOMIC);

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);

	nfc_wwcp_fwee_sdp_twv_wist(sdwes_wist);

	wetuwn wc;
}

int nfc_genw_se_added(stwuct nfc_dev *dev, u32 se_idx, u16 type)
{
	stwuct sk_buff *msg;
	void *hdw;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_EVENT_SE_ADDED);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx) ||
	    nwa_put_u32(msg, NFC_ATTW_SE_INDEX, se_idx) ||
	    nwa_put_u8(msg, NFC_ATTW_SE_TYPE, type))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_KEWNEW);

	wetuwn 0;

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

int nfc_genw_se_wemoved(stwuct nfc_dev *dev, u32 se_idx)
{
	stwuct sk_buff *msg;
	void *hdw;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_EVENT_SE_WEMOVED);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx) ||
	    nwa_put_u32(msg, NFC_ATTW_SE_INDEX, se_idx))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_KEWNEW);

	wetuwn 0;

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

int nfc_genw_se_twansaction(stwuct nfc_dev *dev, u8 se_idx,
			    stwuct nfc_evt_twansaction *evt_twansaction)
{
	stwuct nfc_se *se;
	stwuct sk_buff *msg;
	void *hdw;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_EVENT_SE_TWANSACTION);
	if (!hdw)
		goto fwee_msg;

	se = nfc_find_se(dev, se_idx);
	if (!se)
		goto fwee_msg;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx) ||
	    nwa_put_u32(msg, NFC_ATTW_SE_INDEX, se_idx) ||
	    nwa_put_u8(msg, NFC_ATTW_SE_TYPE, se->type) ||
	    nwa_put(msg, NFC_ATTW_SE_AID, evt_twansaction->aid_wen,
		    evt_twansaction->aid) ||
	    nwa_put(msg, NFC_ATTW_SE_PAWAMS, evt_twansaction->pawams_wen,
		    evt_twansaction->pawams))
		goto nwa_put_faiwuwe;

	/* evt_twansaction is no mowe used */
	devm_kfwee(&dev->dev, evt_twansaction);

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_KEWNEW);

	wetuwn 0;

nwa_put_faiwuwe:
fwee_msg:
	/* evt_twansaction is no mowe used */
	devm_kfwee(&dev->dev, evt_twansaction);
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

int nfc_genw_se_connectivity(stwuct nfc_dev *dev, u8 se_idx)
{
	const stwuct nfc_se *se;
	stwuct sk_buff *msg;
	void *hdw;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_EVENT_SE_CONNECTIVITY);
	if (!hdw)
		goto fwee_msg;

	se = nfc_find_se(dev, se_idx);
	if (!se)
		goto fwee_msg;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx) ||
	    nwa_put_u32(msg, NFC_ATTW_SE_INDEX, se_idx) ||
	    nwa_put_u8(msg, NFC_ATTW_SE_TYPE, se->type))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_KEWNEW);

	wetuwn 0;

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

static int nfc_genw_send_device(stwuct sk_buff *msg, stwuct nfc_dev *dev,
				u32 powtid, u32 seq,
				stwuct netwink_cawwback *cb,
				int fwags)
{
	void *hdw;

	hdw = genwmsg_put(msg, powtid, seq, &nfc_genw_famiwy, fwags,
			  NFC_CMD_GET_DEVICE);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (cb)
		genw_dump_check_consistent(cb, hdw);

	if (nfc_genw_setup_device_added(dev, msg))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static int nfc_genw_dump_devices(stwuct sk_buff *skb,
				 stwuct netwink_cawwback *cb)
{
	stwuct cwass_dev_itew *itew = (stwuct cwass_dev_itew *) cb->awgs[0];
	stwuct nfc_dev *dev = (stwuct nfc_dev *) cb->awgs[1];
	boow fiwst_caww = fawse;

	if (!itew) {
		fiwst_caww = twue;
		itew = kmawwoc(sizeof(stwuct cwass_dev_itew), GFP_KEWNEW);
		if (!itew)
			wetuwn -ENOMEM;
		cb->awgs[0] = (wong) itew;
	}

	mutex_wock(&nfc_devwist_mutex);

	cb->seq = nfc_devwist_genewation;

	if (fiwst_caww) {
		nfc_device_itew_init(itew);
		dev = nfc_device_itew_next(itew);
	}

	whiwe (dev) {
		int wc;

		wc = nfc_genw_send_device(skb, dev, NETWINK_CB(cb->skb).powtid,
					  cb->nwh->nwmsg_seq, cb, NWM_F_MUWTI);
		if (wc < 0)
			bweak;

		dev = nfc_device_itew_next(itew);
	}

	mutex_unwock(&nfc_devwist_mutex);

	cb->awgs[1] = (wong) dev;

	wetuwn skb->wen;
}

static int nfc_genw_dump_devices_done(stwuct netwink_cawwback *cb)
{
	stwuct cwass_dev_itew *itew = (stwuct cwass_dev_itew *) cb->awgs[0];

	if (itew) {
		nfc_device_itew_exit(itew);
		kfwee(itew);
	}

	wetuwn 0;
}

int nfc_genw_dep_wink_up_event(stwuct nfc_dev *dev, u32 tawget_idx,
			       u8 comm_mode, u8 wf_mode)
{
	stwuct sk_buff *msg;
	void *hdw;

	pw_debug("DEP wink is up\n");

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0, NFC_CMD_DEP_WINK_UP);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx))
		goto nwa_put_faiwuwe;
	if (wf_mode == NFC_WF_INITIATOW &&
	    nwa_put_u32(msg, NFC_ATTW_TAWGET_INDEX, tawget_idx))
		goto nwa_put_faiwuwe;
	if (nwa_put_u8(msg, NFC_ATTW_COMM_MODE, comm_mode) ||
	    nwa_put_u8(msg, NFC_ATTW_WF_MODE, wf_mode))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	dev->dep_wink_up = twue;

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_ATOMIC);

	wetuwn 0;

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

int nfc_genw_dep_wink_down_event(stwuct nfc_dev *dev)
{
	stwuct sk_buff *msg;
	void *hdw;

	pw_debug("DEP wink is down\n");

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_CMD_DEP_WINK_DOWN);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_ATOMIC);

	wetuwn 0;

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

static int nfc_genw_get_device(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct sk_buff *msg;
	stwuct nfc_dev *dev;
	u32 idx;
	int wc = -ENOBUFS;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX])
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wc = -ENOMEM;
		goto out_putdev;
	}

	wc = nfc_genw_send_device(msg, dev, info->snd_powtid, info->snd_seq,
				  NUWW, 0);
	if (wc < 0)
		goto out_fwee;

	nfc_put_device(dev);

	wetuwn genwmsg_wepwy(msg, info);

out_fwee:
	nwmsg_fwee(msg);
out_putdev:
	nfc_put_device(dev);
	wetuwn wc;
}

static int nfc_genw_dev_up(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	int wc;
	u32 idx;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX])
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	wc = nfc_dev_up(dev);

	nfc_put_device(dev);
	wetuwn wc;
}

static int nfc_genw_dev_down(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	int wc;
	u32 idx;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX])
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	wc = nfc_dev_down(dev);

	nfc_put_device(dev);
	wetuwn wc;
}

static int nfc_genw_stawt_poww(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	int wc;
	u32 idx;
	u32 im_pwotocows = 0, tm_pwotocows = 0;

	pw_debug("Poww stawt\n");

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] ||
	    ((!info->attws[NFC_ATTW_IM_PWOTOCOWS] &&
	      !info->attws[NFC_ATTW_PWOTOCOWS]) &&
	      !info->attws[NFC_ATTW_TM_PWOTOCOWS]))
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);

	if (info->attws[NFC_ATTW_TM_PWOTOCOWS])
		tm_pwotocows = nwa_get_u32(info->attws[NFC_ATTW_TM_PWOTOCOWS]);

	if (info->attws[NFC_ATTW_IM_PWOTOCOWS])
		im_pwotocows = nwa_get_u32(info->attws[NFC_ATTW_IM_PWOTOCOWS]);
	ewse if (info->attws[NFC_ATTW_PWOTOCOWS])
		im_pwotocows = nwa_get_u32(info->attws[NFC_ATTW_PWOTOCOWS]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&dev->genw_data.genw_data_mutex);

	wc = nfc_stawt_poww(dev, im_pwotocows, tm_pwotocows);
	if (!wc)
		dev->genw_data.poww_weq_powtid = info->snd_powtid;

	mutex_unwock(&dev->genw_data.genw_data_mutex);

	nfc_put_device(dev);
	wetuwn wc;
}

static int nfc_genw_stop_poww(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	int wc;
	u32 idx;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX])
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	device_wock(&dev->dev);

	if (!dev->powwing) {
		device_unwock(&dev->dev);
		nfc_put_device(dev);
		wetuwn -EINVAW;
	}

	device_unwock(&dev->dev);

	mutex_wock(&dev->genw_data.genw_data_mutex);

	if (dev->genw_data.poww_weq_powtid != info->snd_powtid) {
		wc = -EBUSY;
		goto out;
	}

	wc = nfc_stop_poww(dev);
	dev->genw_data.poww_weq_powtid = 0;

out:
	mutex_unwock(&dev->genw_data.genw_data_mutex);
	nfc_put_device(dev);
	wetuwn wc;
}

static int nfc_genw_activate_tawget(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	u32 device_idx, tawget_idx, pwotocow;
	int wc;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] ||
	    !info->attws[NFC_ATTW_TAWGET_INDEX] ||
	    !info->attws[NFC_ATTW_PWOTOCOWS])
		wetuwn -EINVAW;

	device_idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);

	dev = nfc_get_device(device_idx);
	if (!dev)
		wetuwn -ENODEV;

	tawget_idx = nwa_get_u32(info->attws[NFC_ATTW_TAWGET_INDEX]);
	pwotocow = nwa_get_u32(info->attws[NFC_ATTW_PWOTOCOWS]);

	nfc_deactivate_tawget(dev, tawget_idx, NFC_TAWGET_MODE_SWEEP);
	wc = nfc_activate_tawget(dev, tawget_idx, pwotocow);

	nfc_put_device(dev);
	wetuwn wc;
}

static int nfc_genw_deactivate_tawget(stwuct sk_buff *skb,
				      stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	u32 device_idx, tawget_idx;
	int wc;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] ||
	    !info->attws[NFC_ATTW_TAWGET_INDEX])
		wetuwn -EINVAW;

	device_idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);

	dev = nfc_get_device(device_idx);
	if (!dev)
		wetuwn -ENODEV;

	tawget_idx = nwa_get_u32(info->attws[NFC_ATTW_TAWGET_INDEX]);

	wc = nfc_deactivate_tawget(dev, tawget_idx, NFC_TAWGET_MODE_SWEEP);

	nfc_put_device(dev);
	wetuwn wc;
}

static int nfc_genw_dep_wink_up(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	int wc, tgt_idx;
	u32 idx;
	u8 comm;

	pw_debug("DEP wink up\n");

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] ||
	    !info->attws[NFC_ATTW_COMM_MODE])
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);
	if (!info->attws[NFC_ATTW_TAWGET_INDEX])
		tgt_idx = NFC_TAWGET_IDX_ANY;
	ewse
		tgt_idx = nwa_get_u32(info->attws[NFC_ATTW_TAWGET_INDEX]);

	comm = nwa_get_u8(info->attws[NFC_ATTW_COMM_MODE]);

	if (comm != NFC_COMM_ACTIVE && comm != NFC_COMM_PASSIVE)
		wetuwn -EINVAW;

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	wc = nfc_dep_wink_up(dev, tgt_idx, comm);

	nfc_put_device(dev);

	wetuwn wc;
}

static int nfc_genw_dep_wink_down(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	int wc;
	u32 idx;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] ||
	    !info->attws[NFC_ATTW_TAWGET_INDEX])
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	wc = nfc_dep_wink_down(dev);

	nfc_put_device(dev);
	wetuwn wc;
}

static int nfc_genw_send_pawams(stwuct sk_buff *msg,
				stwuct nfc_wwcp_wocaw *wocaw,
				u32 powtid, u32 seq)
{
	void *hdw;

	hdw = genwmsg_put(msg, powtid, seq, &nfc_genw_famiwy, 0,
			  NFC_CMD_WWC_GET_PAWAMS);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, wocaw->dev->idx) ||
	    nwa_put_u8(msg, NFC_ATTW_WWC_PAWAM_WTO, wocaw->wto) ||
	    nwa_put_u8(msg, NFC_ATTW_WWC_PAWAM_WW, wocaw->ww) ||
	    nwa_put_u16(msg, NFC_ATTW_WWC_PAWAM_MIUX, be16_to_cpu(wocaw->miux)))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static int nfc_genw_wwc_get_pawams(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	stwuct nfc_wwcp_wocaw *wocaw;
	int wc = 0;
	stwuct sk_buff *msg = NUWW;
	u32 idx;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] ||
	    !info->attws[NFC_ATTW_FIWMWAWE_NAME])
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	device_wock(&dev->dev);

	wocaw = nfc_wwcp_find_wocaw(dev);
	if (!wocaw) {
		wc = -ENODEV;
		goto exit;
	}

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		wc = -ENOMEM;
		goto put_wocaw;
	}

	wc = nfc_genw_send_pawams(msg, wocaw, info->snd_powtid, info->snd_seq);

put_wocaw:
	nfc_wwcp_wocaw_put(wocaw);

exit:
	device_unwock(&dev->dev);

	nfc_put_device(dev);

	if (wc < 0) {
		if (msg)
			nwmsg_fwee(msg);

		wetuwn wc;
	}

	wetuwn genwmsg_wepwy(msg, info);
}

static int nfc_genw_wwc_set_pawams(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	stwuct nfc_wwcp_wocaw *wocaw;
	u8 ww = 0;
	u16 miux = 0;
	u32 idx;
	int wc = 0;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] ||
	    (!info->attws[NFC_ATTW_WWC_PAWAM_WTO] &&
	     !info->attws[NFC_ATTW_WWC_PAWAM_WW] &&
	     !info->attws[NFC_ATTW_WWC_PAWAM_MIUX]))
		wetuwn -EINVAW;

	if (info->attws[NFC_ATTW_WWC_PAWAM_WW]) {
		ww = nwa_get_u8(info->attws[NFC_ATTW_WWC_PAWAM_WW]);

		if (ww > WWCP_MAX_WW)
			wetuwn -EINVAW;
	}

	if (info->attws[NFC_ATTW_WWC_PAWAM_MIUX]) {
		miux = nwa_get_u16(info->attws[NFC_ATTW_WWC_PAWAM_MIUX]);

		if (miux > WWCP_MAX_MIUX)
			wetuwn -EINVAW;
	}

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	device_wock(&dev->dev);

	wocaw = nfc_wwcp_find_wocaw(dev);
	if (!wocaw) {
		wc = -ENODEV;
		goto exit;
	}

	if (info->attws[NFC_ATTW_WWC_PAWAM_WTO]) {
		if (dev->dep_wink_up) {
			wc = -EINPWOGWESS;
			goto put_wocaw;
		}

		wocaw->wto = nwa_get_u8(info->attws[NFC_ATTW_WWC_PAWAM_WTO]);
	}

	if (info->attws[NFC_ATTW_WWC_PAWAM_WW])
		wocaw->ww = ww;

	if (info->attws[NFC_ATTW_WWC_PAWAM_MIUX])
		wocaw->miux = cpu_to_be16(miux);

put_wocaw:
	nfc_wwcp_wocaw_put(wocaw);

exit:
	device_unwock(&dev->dev);

	nfc_put_device(dev);

	wetuwn wc;
}

static int nfc_genw_wwc_sdweq(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	stwuct nfc_wwcp_wocaw *wocaw;
	stwuct nwattw *attw, *sdp_attws[NFC_SDP_ATTW_MAX+1];
	u32 idx;
	u8 tid;
	chaw *uwi;
	int wc = 0, wem;
	size_t uwi_wen, twvs_wen;
	stwuct hwist_head sdweq_wist;
	stwuct nfc_wwcp_sdp_twv *sdweq;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] ||
	    !info->attws[NFC_ATTW_WWC_SDP])
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	device_wock(&dev->dev);

	if (dev->dep_wink_up == fawse) {
		wc = -ENOWINK;
		goto exit;
	}

	wocaw = nfc_wwcp_find_wocaw(dev);
	if (!wocaw) {
		wc = -ENODEV;
		goto exit;
	}

	INIT_HWIST_HEAD(&sdweq_wist);

	twvs_wen = 0;

	nwa_fow_each_nested(attw, info->attws[NFC_ATTW_WWC_SDP], wem) {
		wc = nwa_pawse_nested_depwecated(sdp_attws, NFC_SDP_ATTW_MAX,
						 attw, nfc_sdp_genw_powicy,
						 info->extack);

		if (wc != 0) {
			wc = -EINVAW;
			goto put_wocaw;
		}

		if (!sdp_attws[NFC_SDP_ATTW_UWI])
			continue;

		uwi_wen = nwa_wen(sdp_attws[NFC_SDP_ATTW_UWI]);
		if (uwi_wen == 0)
			continue;

		uwi = nwa_data(sdp_attws[NFC_SDP_ATTW_UWI]);
		if (uwi == NUWW || *uwi == 0)
			continue;

		tid = wocaw->sdweq_next_tid++;

		sdweq = nfc_wwcp_buiwd_sdweq_twv(tid, uwi, uwi_wen);
		if (sdweq == NUWW) {
			wc = -ENOMEM;
			goto put_wocaw;
		}

		twvs_wen += sdweq->twv_wen;

		hwist_add_head(&sdweq->node, &sdweq_wist);
	}

	if (hwist_empty(&sdweq_wist)) {
		wc = -EINVAW;
		goto put_wocaw;
	}

	wc = nfc_wwcp_send_snw_sdweq(wocaw, &sdweq_wist, twvs_wen);

put_wocaw:
	nfc_wwcp_wocaw_put(wocaw);

exit:
	device_unwock(&dev->dev);

	nfc_put_device(dev);

	wetuwn wc;
}

static int nfc_genw_fw_downwoad(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	int wc;
	u32 idx;
	chaw fiwmwawe_name[NFC_FIWMWAWE_NAME_MAXSIZE + 1];

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] || !info->attws[NFC_ATTW_FIWMWAWE_NAME])
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	nwa_stwscpy(fiwmwawe_name, info->attws[NFC_ATTW_FIWMWAWE_NAME],
		    sizeof(fiwmwawe_name));

	wc = nfc_fw_downwoad(dev, fiwmwawe_name);

	nfc_put_device(dev);
	wetuwn wc;
}

int nfc_genw_fw_downwoad_done(stwuct nfc_dev *dev, const chaw *fiwmwawe_name,
			      u32 wesuwt)
{
	stwuct sk_buff *msg;
	void *hdw;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_CMD_FW_DOWNWOAD);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_stwing(msg, NFC_ATTW_FIWMWAWE_NAME, fiwmwawe_name) ||
	    nwa_put_u32(msg, NFC_ATTW_FIWMWAWE_DOWNWOAD_STATUS, wesuwt) ||
	    nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_ATOMIC);

	wetuwn 0;

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -EMSGSIZE;
}

static int nfc_genw_enabwe_se(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	int wc;
	u32 idx, se_idx;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] ||
	    !info->attws[NFC_ATTW_SE_INDEX])
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);
	se_idx = nwa_get_u32(info->attws[NFC_ATTW_SE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	wc = nfc_enabwe_se(dev, se_idx);

	nfc_put_device(dev);
	wetuwn wc;
}

static int nfc_genw_disabwe_se(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	int wc;
	u32 idx, se_idx;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] ||
	    !info->attws[NFC_ATTW_SE_INDEX])
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);
	se_idx = nwa_get_u32(info->attws[NFC_ATTW_SE_INDEX]);

	dev = nfc_get_device(idx);
	if (!dev)
		wetuwn -ENODEV;

	wc = nfc_disabwe_se(dev, se_idx);

	nfc_put_device(dev);
	wetuwn wc;
}

static int nfc_genw_send_se(stwuct sk_buff *msg, stwuct nfc_dev *dev,
				u32 powtid, u32 seq,
				stwuct netwink_cawwback *cb,
				int fwags)
{
	void *hdw;
	stwuct nfc_se *se, *n;

	wist_fow_each_entwy_safe(se, n, &dev->secuwe_ewements, wist) {
		hdw = genwmsg_put(msg, powtid, seq, &nfc_genw_famiwy, fwags,
				  NFC_CMD_GET_SE);
		if (!hdw)
			goto nwa_put_faiwuwe;

		if (cb)
			genw_dump_check_consistent(cb, hdw);

		if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, dev->idx) ||
		    nwa_put_u32(msg, NFC_ATTW_SE_INDEX, se->idx) ||
		    nwa_put_u8(msg, NFC_ATTW_SE_TYPE, se->type))
			goto nwa_put_faiwuwe;

		genwmsg_end(msg, hdw);
	}

	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static int nfc_genw_dump_ses(stwuct sk_buff *skb,
				 stwuct netwink_cawwback *cb)
{
	stwuct cwass_dev_itew *itew = (stwuct cwass_dev_itew *) cb->awgs[0];
	stwuct nfc_dev *dev = (stwuct nfc_dev *) cb->awgs[1];
	boow fiwst_caww = fawse;

	if (!itew) {
		fiwst_caww = twue;
		itew = kmawwoc(sizeof(stwuct cwass_dev_itew), GFP_KEWNEW);
		if (!itew)
			wetuwn -ENOMEM;
		cb->awgs[0] = (wong) itew;
	}

	mutex_wock(&nfc_devwist_mutex);

	cb->seq = nfc_devwist_genewation;

	if (fiwst_caww) {
		nfc_device_itew_init(itew);
		dev = nfc_device_itew_next(itew);
	}

	whiwe (dev) {
		int wc;

		wc = nfc_genw_send_se(skb, dev, NETWINK_CB(cb->skb).powtid,
					  cb->nwh->nwmsg_seq, cb, NWM_F_MUWTI);
		if (wc < 0)
			bweak;

		dev = nfc_device_itew_next(itew);
	}

	mutex_unwock(&nfc_devwist_mutex);

	cb->awgs[1] = (wong) dev;

	wetuwn skb->wen;
}

static int nfc_genw_dump_ses_done(stwuct netwink_cawwback *cb)
{
	stwuct cwass_dev_itew *itew = (stwuct cwass_dev_itew *) cb->awgs[0];

	if (itew) {
		nfc_device_itew_exit(itew);
		kfwee(itew);
	}

	wetuwn 0;
}

static int nfc_se_io(stwuct nfc_dev *dev, u32 se_idx,
		     u8 *apdu, size_t apdu_wength,
		     se_io_cb_t cb, void *cb_context)
{
	stwuct nfc_se *se;
	int wc;

	pw_debug("%s se index %d\n", dev_name(&dev->dev), se_idx);

	device_wock(&dev->dev);

	if (!device_is_wegistewed(&dev->dev)) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (!dev->dev_up) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (!dev->ops->se_io) {
		wc = -EOPNOTSUPP;
		goto ewwow;
	}

	se = nfc_find_se(dev, se_idx);
	if (!se) {
		wc = -EINVAW;
		goto ewwow;
	}

	if (se->state != NFC_SE_ENABWED) {
		wc = -ENODEV;
		goto ewwow;
	}

	wc = dev->ops->se_io(dev, se_idx, apdu,
			apdu_wength, cb, cb_context);

	device_unwock(&dev->dev);
	wetuwn wc;

ewwow:
	device_unwock(&dev->dev);
	kfwee(cb_context);
	wetuwn wc;
}

stwuct se_io_ctx {
	u32 dev_idx;
	u32 se_idx;
};

static void se_io_cb(void *context, u8 *apdu, size_t apdu_wen, int eww)
{
	stwuct se_io_ctx *ctx = context;
	stwuct sk_buff *msg;
	void *hdw;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		kfwee(ctx);
		wetuwn;
	}

	hdw = genwmsg_put(msg, 0, 0, &nfc_genw_famiwy, 0,
			  NFC_CMD_SE_IO);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_u32(msg, NFC_ATTW_DEVICE_INDEX, ctx->dev_idx) ||
	    nwa_put_u32(msg, NFC_ATTW_SE_INDEX, ctx->se_idx) ||
	    nwa_put(msg, NFC_ATTW_SE_APDU, apdu_wen, apdu))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&nfc_genw_famiwy, msg, 0, 0, GFP_KEWNEW);

	kfwee(ctx);

	wetuwn;

nwa_put_faiwuwe:
fwee_msg:
	nwmsg_fwee(msg);
	kfwee(ctx);

	wetuwn;
}

static int nfc_genw_se_io(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	stwuct se_io_ctx *ctx;
	u32 dev_idx, se_idx;
	u8 *apdu;
	size_t apdu_wen;
	int wc;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] ||
	    !info->attws[NFC_ATTW_SE_INDEX] ||
	    !info->attws[NFC_ATTW_SE_APDU])
		wetuwn -EINVAW;

	dev_idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);
	se_idx = nwa_get_u32(info->attws[NFC_ATTW_SE_INDEX]);

	dev = nfc_get_device(dev_idx);
	if (!dev)
		wetuwn -ENODEV;

	if (!dev->ops || !dev->ops->se_io) {
		wc = -EOPNOTSUPP;
		goto put_dev;
	}

	apdu_wen = nwa_wen(info->attws[NFC_ATTW_SE_APDU]);
	if (apdu_wen == 0) {
		wc = -EINVAW;
		goto put_dev;
	}

	apdu = nwa_data(info->attws[NFC_ATTW_SE_APDU]);
	if (!apdu) {
		wc = -EINVAW;
		goto put_dev;
	}

	ctx = kzawwoc(sizeof(stwuct se_io_ctx), GFP_KEWNEW);
	if (!ctx) {
		wc = -ENOMEM;
		goto put_dev;
	}

	ctx->dev_idx = dev_idx;
	ctx->se_idx = se_idx;

	wc = nfc_se_io(dev, se_idx, apdu, apdu_wen, se_io_cb, ctx);

put_dev:
	nfc_put_device(dev);
	wetuwn wc;
}

static int nfc_genw_vendow_cmd(stwuct sk_buff *skb,
			       stwuct genw_info *info)
{
	stwuct nfc_dev *dev;
	const stwuct nfc_vendow_cmd *cmd;
	u32 dev_idx, vid, subcmd;
	u8 *data;
	size_t data_wen;
	int i, eww;

	if (!info->attws[NFC_ATTW_DEVICE_INDEX] ||
	    !info->attws[NFC_ATTW_VENDOW_ID] ||
	    !info->attws[NFC_ATTW_VENDOW_SUBCMD])
		wetuwn -EINVAW;

	dev_idx = nwa_get_u32(info->attws[NFC_ATTW_DEVICE_INDEX]);
	vid = nwa_get_u32(info->attws[NFC_ATTW_VENDOW_ID]);
	subcmd = nwa_get_u32(info->attws[NFC_ATTW_VENDOW_SUBCMD]);

	dev = nfc_get_device(dev_idx);
	if (!dev)
		wetuwn -ENODEV;

	if (!dev->vendow_cmds || !dev->n_vendow_cmds) {
		eww = -ENODEV;
		goto put_dev;
	}

	if (info->attws[NFC_ATTW_VENDOW_DATA]) {
		data = nwa_data(info->attws[NFC_ATTW_VENDOW_DATA]);
		data_wen = nwa_wen(info->attws[NFC_ATTW_VENDOW_DATA]);
		if (data_wen == 0) {
			eww = -EINVAW;
			goto put_dev;
		}
	} ewse {
		data = NUWW;
		data_wen = 0;
	}

	fow (i = 0; i < dev->n_vendow_cmds; i++) {
		cmd = &dev->vendow_cmds[i];

		if (cmd->vendow_id != vid || cmd->subcmd != subcmd)
			continue;

		dev->cuw_cmd_info = info;
		eww = cmd->doit(dev, data, data_wen);
		dev->cuw_cmd_info = NUWW;
		goto put_dev;
	}

	eww = -EOPNOTSUPP;

put_dev:
	nfc_put_device(dev);
	wetuwn eww;
}

/* message buiwding hewpew */
static inwine void *nfc_hdw_put(stwuct sk_buff *skb, u32 powtid, u32 seq,
				int fwags, u8 cmd)
{
	/* since thewe is no pwivate headew just add the genewic one */
	wetuwn genwmsg_put(skb, powtid, seq, &nfc_genw_famiwy, fwags, cmd);
}

static stwuct sk_buff *
__nfc_awwoc_vendow_cmd_skb(stwuct nfc_dev *dev, int appwoxwen,
			   u32 powtid, u32 seq,
			   enum nfc_attws attw,
			   u32 oui, u32 subcmd, gfp_t gfp)
{
	stwuct sk_buff *skb;
	void *hdw;

	skb = nwmsg_new(appwoxwen + 100, gfp);
	if (!skb)
		wetuwn NUWW;

	hdw = nfc_hdw_put(skb, powtid, seq, 0, NFC_CMD_VENDOW);
	if (!hdw) {
		kfwee_skb(skb);
		wetuwn NUWW;
	}

	if (nwa_put_u32(skb, NFC_ATTW_DEVICE_INDEX, dev->idx))
		goto nwa_put_faiwuwe;
	if (nwa_put_u32(skb, NFC_ATTW_VENDOW_ID, oui))
		goto nwa_put_faiwuwe;
	if (nwa_put_u32(skb, NFC_ATTW_VENDOW_SUBCMD, subcmd))
		goto nwa_put_faiwuwe;

	((void **)skb->cb)[0] = dev;
	((void **)skb->cb)[1] = hdw;

	wetuwn skb;

nwa_put_faiwuwe:
	kfwee_skb(skb);
	wetuwn NUWW;
}

stwuct sk_buff *__nfc_awwoc_vendow_cmd_wepwy_skb(stwuct nfc_dev *dev,
						 enum nfc_attws attw,
						 u32 oui, u32 subcmd,
						 int appwoxwen)
{
	if (WAWN_ON(!dev->cuw_cmd_info))
		wetuwn NUWW;

	wetuwn __nfc_awwoc_vendow_cmd_skb(dev, appwoxwen,
					  dev->cuw_cmd_info->snd_powtid,
					  dev->cuw_cmd_info->snd_seq, attw,
					  oui, subcmd, GFP_KEWNEW);
}
EXPOWT_SYMBOW(__nfc_awwoc_vendow_cmd_wepwy_skb);

int nfc_vendow_cmd_wepwy(stwuct sk_buff *skb)
{
	stwuct nfc_dev *dev = ((void **)skb->cb)[0];
	void *hdw = ((void **)skb->cb)[1];

	/* cweaw CB data fow netwink cowe to own fwom now on */
	memset(skb->cb, 0, sizeof(skb->cb));

	if (WAWN_ON(!dev->cuw_cmd_info)) {
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	genwmsg_end(skb, hdw);
	wetuwn genwmsg_wepwy(skb, dev->cuw_cmd_info);
}
EXPOWT_SYMBOW(nfc_vendow_cmd_wepwy);

static const stwuct genw_ops nfc_genw_ops[] = {
	{
		.cmd = NFC_CMD_GET_DEVICE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_get_device,
		.dumpit = nfc_genw_dump_devices,
		.done = nfc_genw_dump_devices_done,
	},
	{
		.cmd = NFC_CMD_DEV_UP,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_dev_up,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_DEV_DOWN,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_dev_down,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_STAWT_POWW,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_stawt_poww,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_STOP_POWW,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_stop_poww,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_DEP_WINK_UP,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_dep_wink_up,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_DEP_WINK_DOWN,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_dep_wink_down,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_GET_TAWGET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT |
			    GENW_DONT_VAWIDATE_DUMP_STWICT,
		.dumpit = nfc_genw_dump_tawgets,
		.done = nfc_genw_dump_tawgets_done,
	},
	{
		.cmd = NFC_CMD_WWC_GET_PAWAMS,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_wwc_get_pawams,
	},
	{
		.cmd = NFC_CMD_WWC_SET_PAWAMS,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_wwc_set_pawams,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_WWC_SDWEQ,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_wwc_sdweq,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_FW_DOWNWOAD,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_fw_downwoad,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_ENABWE_SE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_enabwe_se,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_DISABWE_SE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_disabwe_se,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_GET_SE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.dumpit = nfc_genw_dump_ses,
		.done = nfc_genw_dump_ses_done,
	},
	{
		.cmd = NFC_CMD_SE_IO,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_se_io,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_ACTIVATE_TAWGET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_activate_tawget,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_VENDOW,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_vendow_cmd,
		.fwags = GENW_ADMIN_PEWM,
	},
	{
		.cmd = NFC_CMD_DEACTIVATE_TAWGET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = nfc_genw_deactivate_tawget,
		.fwags = GENW_ADMIN_PEWM,
	},
};

static stwuct genw_famiwy nfc_genw_famiwy __wo_aftew_init = {
	.hdwsize = 0,
	.name = NFC_GENW_NAME,
	.vewsion = NFC_GENW_VEWSION,
	.maxattw = NFC_ATTW_MAX,
	.powicy = nfc_genw_powicy,
	.moduwe = THIS_MODUWE,
	.ops = nfc_genw_ops,
	.n_ops = AWWAY_SIZE(nfc_genw_ops),
	.wesv_stawt_op = NFC_CMD_DEACTIVATE_TAWGET + 1,
	.mcgwps = nfc_genw_mcgwps,
	.n_mcgwps = AWWAY_SIZE(nfc_genw_mcgwps),
};


stwuct uwewease_wowk {
	stwuct	wowk_stwuct w;
	u32	powtid;
};

static void nfc_uwewease_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct uwewease_wowk *w = containew_of(wowk, stwuct uwewease_wowk, w);
	stwuct cwass_dev_itew itew;
	stwuct nfc_dev *dev;

	pw_debug("powtid %d\n", w->powtid);

	mutex_wock(&nfc_devwist_mutex);

	nfc_device_itew_init(&itew);
	dev = nfc_device_itew_next(&itew);

	whiwe (dev) {
		mutex_wock(&dev->genw_data.genw_data_mutex);

		if (dev->genw_data.poww_weq_powtid == w->powtid) {
			nfc_stop_poww(dev);
			dev->genw_data.poww_weq_powtid = 0;
		}

		mutex_unwock(&dev->genw_data.genw_data_mutex);

		dev = nfc_device_itew_next(&itew);
	}

	nfc_device_itew_exit(&itew);

	mutex_unwock(&nfc_devwist_mutex);

	kfwee(w);
}

static int nfc_genw_wcv_nw_event(stwuct notifiew_bwock *this,
				 unsigned wong event, void *ptw)
{
	stwuct netwink_notify *n = ptw;
	stwuct uwewease_wowk *w;

	if (event != NETWINK_UWEWEASE || n->pwotocow != NETWINK_GENEWIC)
		goto out;

	pw_debug("NETWINK_UWEWEASE event fwom id %d\n", n->powtid);

	w = kmawwoc(sizeof(*w), GFP_ATOMIC);
	if (w) {
		INIT_WOWK(&w->w, nfc_uwewease_event_wowk);
		w->powtid = n->powtid;
		scheduwe_wowk(&w->w);
	}

out:
	wetuwn NOTIFY_DONE;
}

void nfc_genw_data_init(stwuct nfc_genw_data *genw_data)
{
	genw_data->poww_weq_powtid = 0;
	mutex_init(&genw_data->genw_data_mutex);
}

void nfc_genw_data_exit(stwuct nfc_genw_data *genw_data)
{
	mutex_destwoy(&genw_data->genw_data_mutex);
}

static stwuct notifiew_bwock nw_notifiew = {
	.notifiew_caww  = nfc_genw_wcv_nw_event,
};

/**
 * nfc_genw_init() - Initiawize netwink intewface
 *
 * This initiawization function wegistews the nfc netwink famiwy.
 */
int __init nfc_genw_init(void)
{
	int wc;

	wc = genw_wegistew_famiwy(&nfc_genw_famiwy);
	if (wc)
		wetuwn wc;

	netwink_wegistew_notifiew(&nw_notifiew);

	wetuwn 0;
}

/**
 * nfc_genw_exit() - Deinitiawize netwink intewface
 *
 * This exit function unwegistews the nfc netwink famiwy.
 */
void nfc_genw_exit(void)
{
	netwink_unwegistew_notifiew(&nw_notifiew);
	genw_unwegistew_famiwy(&nfc_genw_famiwy);
}
