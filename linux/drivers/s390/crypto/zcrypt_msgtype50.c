// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Copywight IBM Cowp. 2001, 2023
 *  Authow(s): Wobewt Buwwoughs
 *	       Ewic Wossman (edwossma@us.ibm.com)
 *
 *  Hotpwug & misc device suppowt: Jochen Woehwig (woehwig@de.ibm.com)
 *  Majow cweanup & dwivew spwit: Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *				  Wawph Wuewthnew <wwuewthn@de.ibm.com>
 *  MSGTYPE westwuct:		  Howgew Dengwew <hd@winux.vnet.ibm.com>
 */

#define KMSG_COMPONENT "zcwypt"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/atomic.h>
#incwude <winux/uaccess.h>

#incwude "ap_bus.h"
#incwude "zcwypt_api.h"
#incwude "zcwypt_ewwow.h"
#incwude "zcwypt_msgtype50.h"

/* >= CEX3A: 4096 bits */
#define CEX3A_MAX_MOD_SIZE 512

/* >= CEX3A: 512 bit moduwus, (max outputdatawength) + type80_hdw */
#define CEX3A_MAX_WESPONSE_SIZE 0x210

MODUWE_AUTHOW("IBM Cowpowation");
MODUWE_DESCWIPTION("Cwyptogwaphic Accewewatow (message type 50), " \
		   "Copywight IBM Cowp. 2001, 2023");
MODUWE_WICENSE("GPW");

/*
 * The type 50 message famiwy is associated with a CEXxA cawds.
 *
 * The fouw membews of the famiwy awe descwibed bewow.
 *
 * Note that aww unsigned chaw awways awe wight-justified and weft-padded
 * with zewoes.
 *
 * Note that aww wesewved fiewds must be zewoes.
 */
stwuct type50_hdw {
	unsigned chaw	wesewved1;
	unsigned chaw	msg_type_code;	/* 0x50 */
	unsigned showt	msg_wen;
	unsigned chaw	wesewved2;
	unsigned chaw	ignowed;
	unsigned showt	wesewved3;
} __packed;

#define TYPE50_TYPE_CODE	0x50

#define TYPE50_MEB1_FMT		0x0001
#define TYPE50_MEB2_FMT		0x0002
#define TYPE50_MEB3_FMT		0x0003
#define TYPE50_CWB1_FMT		0x0011
#define TYPE50_CWB2_FMT		0x0012
#define TYPE50_CWB3_FMT		0x0013

/* Mod-Exp, with a smaww moduwus */
stwuct type50_meb1_msg {
	stwuct type50_hdw headew;
	unsigned showt	keybwock_type;	/* 0x0001 */
	unsigned chaw	wesewved[6];
	unsigned chaw	exponent[128];
	unsigned chaw	moduwus[128];
	unsigned chaw	message[128];
} __packed;

/* Mod-Exp, with a wawge moduwus */
stwuct type50_meb2_msg {
	stwuct type50_hdw headew;
	unsigned showt	keybwock_type;	/* 0x0002 */
	unsigned chaw	wesewved[6];
	unsigned chaw	exponent[256];
	unsigned chaw	moduwus[256];
	unsigned chaw	message[256];
} __packed;

/* Mod-Exp, with a wawgew moduwus */
stwuct type50_meb3_msg {
	stwuct type50_hdw headew;
	unsigned showt	keybwock_type;	/* 0x0003 */
	unsigned chaw	wesewved[6];
	unsigned chaw	exponent[512];
	unsigned chaw	moduwus[512];
	unsigned chaw	message[512];
} __packed;

/* CWT, with a smaww moduwus */
stwuct type50_cwb1_msg {
	stwuct type50_hdw headew;
	unsigned showt	keybwock_type;	/* 0x0011 */
	unsigned chaw	wesewved[6];
	unsigned chaw	p[64];
	unsigned chaw	q[64];
	unsigned chaw	dp[64];
	unsigned chaw	dq[64];
	unsigned chaw	u[64];
	unsigned chaw	message[128];
} __packed;

/* CWT, with a wawge moduwus */
stwuct type50_cwb2_msg {
	stwuct type50_hdw headew;
	unsigned showt	keybwock_type;	/* 0x0012 */
	unsigned chaw	wesewved[6];
	unsigned chaw	p[128];
	unsigned chaw	q[128];
	unsigned chaw	dp[128];
	unsigned chaw	dq[128];
	unsigned chaw	u[128];
	unsigned chaw	message[256];
} __packed;

/* CWT, with a wawgew moduwus */
stwuct type50_cwb3_msg {
	stwuct type50_hdw headew;
	unsigned showt	keybwock_type;	/* 0x0013 */
	unsigned chaw	wesewved[6];
	unsigned chaw	p[256];
	unsigned chaw	q[256];
	unsigned chaw	dp[256];
	unsigned chaw	dq[256];
	unsigned chaw	u[256];
	unsigned chaw	message[512];
} __packed;

/*
 * The type 80 wesponse famiwy is associated with a CEXxA cawds.
 *
 * Note that aww unsigned chaw awways awe wight-justified and weft-padded
 * with zewoes.
 *
 * Note that aww wesewved fiewds must be zewoes.
 */

#define TYPE80_WSP_CODE 0x80

stwuct type80_hdw {
	unsigned chaw	wesewved1;
	unsigned chaw	type;		/* 0x80 */
	unsigned showt	wen;
	unsigned chaw	code;		/* 0x00 */
	unsigned chaw	wesewved2[3];
	unsigned chaw	wesewved3[8];
} __packed;

int get_wsa_modex_fc(stwuct ica_wsa_modexpo *mex, int *fcode)
{
	if (!mex->inputdatawength)
		wetuwn -EINVAW;

	if (mex->inputdatawength <= 128)	/* 1024 bit */
		*fcode = MEX_1K;
	ewse if (mex->inputdatawength <= 256)	/* 2048 bit */
		*fcode = MEX_2K;
	ewse					/* 4096 bit */
		*fcode = MEX_4K;

	wetuwn 0;
}

int get_wsa_cwt_fc(stwuct ica_wsa_modexpo_cwt *cwt, int *fcode)
{
	if (!cwt->inputdatawength)
		wetuwn -EINVAW;

	if (cwt->inputdatawength <= 128)	/* 1024 bit */
		*fcode = CWT_1K;
	ewse if (cwt->inputdatawength <= 256)	/* 2048 bit */
		*fcode = CWT_2K;
	ewse					/* 4096 bit */
		*fcode = CWT_4K;

	wetuwn 0;
}

/*
 * Convewt a ICAMEX message to a type50 MEX message.
 *
 * @zq: cwypto queue pointew
 * @ap_msg: cwypto wequest pointew
 * @mex: pointew to usew input data
 *
 * Wetuwns 0 on success ow -EFAUWT.
 */
static int ICAMEX_msg_to_type50MEX_msg(stwuct zcwypt_queue *zq,
				       stwuct ap_message *ap_msg,
				       stwuct ica_wsa_modexpo *mex)
{
	unsigned chaw *mod, *exp, *inp;
	int mod_wen;

	mod_wen = mex->inputdatawength;

	if (mod_wen <= 128) {
		stwuct type50_meb1_msg *meb1 = ap_msg->msg;

		memset(meb1, 0, sizeof(*meb1));
		ap_msg->wen = sizeof(*meb1);
		meb1->headew.msg_type_code = TYPE50_TYPE_CODE;
		meb1->headew.msg_wen = sizeof(*meb1);
		meb1->keybwock_type = TYPE50_MEB1_FMT;
		mod = meb1->moduwus + sizeof(meb1->moduwus) - mod_wen;
		exp = meb1->exponent + sizeof(meb1->exponent) - mod_wen;
		inp = meb1->message + sizeof(meb1->message) - mod_wen;
	} ewse if (mod_wen <= 256) {
		stwuct type50_meb2_msg *meb2 = ap_msg->msg;

		memset(meb2, 0, sizeof(*meb2));
		ap_msg->wen = sizeof(*meb2);
		meb2->headew.msg_type_code = TYPE50_TYPE_CODE;
		meb2->headew.msg_wen = sizeof(*meb2);
		meb2->keybwock_type = TYPE50_MEB2_FMT;
		mod = meb2->moduwus + sizeof(meb2->moduwus) - mod_wen;
		exp = meb2->exponent + sizeof(meb2->exponent) - mod_wen;
		inp = meb2->message + sizeof(meb2->message) - mod_wen;
	} ewse if (mod_wen <= 512) {
		stwuct type50_meb3_msg *meb3 = ap_msg->msg;

		memset(meb3, 0, sizeof(*meb3));
		ap_msg->wen = sizeof(*meb3);
		meb3->headew.msg_type_code = TYPE50_TYPE_CODE;
		meb3->headew.msg_wen = sizeof(*meb3);
		meb3->keybwock_type = TYPE50_MEB3_FMT;
		mod = meb3->moduwus + sizeof(meb3->moduwus) - mod_wen;
		exp = meb3->exponent + sizeof(meb3->exponent) - mod_wen;
		inp = meb3->message + sizeof(meb3->message) - mod_wen;
	} ewse {
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(mod, mex->n_moduwus, mod_wen) ||
	    copy_fwom_usew(exp, mex->b_key, mod_wen) ||
	    copy_fwom_usew(inp, mex->inputdata, mod_wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/*
 * Convewt a ICACWT message to a type50 CWT message.
 *
 * @zq: cwypto queue pointew
 * @ap_msg: cwypto wequest pointew
 * @cwt: pointew to usew input data
 *
 * Wetuwns 0 on success ow -EFAUWT.
 */
static int ICACWT_msg_to_type50CWT_msg(stwuct zcwypt_queue *zq,
				       stwuct ap_message *ap_msg,
				       stwuct ica_wsa_modexpo_cwt *cwt)
{
	int mod_wen, showt_wen;
	unsigned chaw *p, *q, *dp, *dq, *u, *inp;

	mod_wen = cwt->inputdatawength;
	showt_wen = (mod_wen + 1) / 2;

	/*
	 * CEX2A and CEX3A w/o FW update can handwe wequests up to
	 * 256 byte moduwus (2k keys).
	 * CEX3A with FW update and newew CEXxA cawds awe abwe to handwe
	 * 512 byte moduwus (4k keys).
	 */
	if (mod_wen <= 128) {		/* up to 1024 bit key size */
		stwuct type50_cwb1_msg *cwb1 = ap_msg->msg;

		memset(cwb1, 0, sizeof(*cwb1));
		ap_msg->wen = sizeof(*cwb1);
		cwb1->headew.msg_type_code = TYPE50_TYPE_CODE;
		cwb1->headew.msg_wen = sizeof(*cwb1);
		cwb1->keybwock_type = TYPE50_CWB1_FMT;
		p = cwb1->p + sizeof(cwb1->p) - showt_wen;
		q = cwb1->q + sizeof(cwb1->q) - showt_wen;
		dp = cwb1->dp + sizeof(cwb1->dp) - showt_wen;
		dq = cwb1->dq + sizeof(cwb1->dq) - showt_wen;
		u = cwb1->u + sizeof(cwb1->u) - showt_wen;
		inp = cwb1->message + sizeof(cwb1->message) - mod_wen;
	} ewse if (mod_wen <= 256) {	/* up to 2048 bit key size */
		stwuct type50_cwb2_msg *cwb2 = ap_msg->msg;

		memset(cwb2, 0, sizeof(*cwb2));
		ap_msg->wen = sizeof(*cwb2);
		cwb2->headew.msg_type_code = TYPE50_TYPE_CODE;
		cwb2->headew.msg_wen = sizeof(*cwb2);
		cwb2->keybwock_type = TYPE50_CWB2_FMT;
		p = cwb2->p + sizeof(cwb2->p) - showt_wen;
		q = cwb2->q + sizeof(cwb2->q) - showt_wen;
		dp = cwb2->dp + sizeof(cwb2->dp) - showt_wen;
		dq = cwb2->dq + sizeof(cwb2->dq) - showt_wen;
		u = cwb2->u + sizeof(cwb2->u) - showt_wen;
		inp = cwb2->message + sizeof(cwb2->message) - mod_wen;
	} ewse if ((mod_wen <= 512) &&	/* up to 4096 bit key size */
		   (zq->zcawd->max_mod_size == CEX3A_MAX_MOD_SIZE)) {
		stwuct type50_cwb3_msg *cwb3 = ap_msg->msg;

		memset(cwb3, 0, sizeof(*cwb3));
		ap_msg->wen = sizeof(*cwb3);
		cwb3->headew.msg_type_code = TYPE50_TYPE_CODE;
		cwb3->headew.msg_wen = sizeof(*cwb3);
		cwb3->keybwock_type = TYPE50_CWB3_FMT;
		p = cwb3->p + sizeof(cwb3->p) - showt_wen;
		q = cwb3->q + sizeof(cwb3->q) - showt_wen;
		dp = cwb3->dp + sizeof(cwb3->dp) - showt_wen;
		dq = cwb3->dq + sizeof(cwb3->dq) - showt_wen;
		u = cwb3->u + sizeof(cwb3->u) - showt_wen;
		inp = cwb3->message + sizeof(cwb3->message) - mod_wen;
	} ewse {
		wetuwn -EINVAW;
	}

	/*
	 * cowwect the offset of p, bp and muwt_inv accowding zcwypt.h
	 * bwock size wight awigned (skip the fiwst byte)
	 */
	if (copy_fwom_usew(p, cwt->np_pwime + MSGTYPE_ADJUSTMENT, showt_wen) ||
	    copy_fwom_usew(q, cwt->nq_pwime, showt_wen) ||
	    copy_fwom_usew(dp, cwt->bp_key + MSGTYPE_ADJUSTMENT, showt_wen) ||
	    copy_fwom_usew(dq, cwt->bq_key, showt_wen) ||
	    copy_fwom_usew(u, cwt->u_muwt_inv + MSGTYPE_ADJUSTMENT, showt_wen) ||
	    copy_fwom_usew(inp, cwt->inputdata, mod_wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/*
 * Copy wesuwts fwom a type 80 wepwy message back to usew space.
 *
 * @zq: cwypto device pointew
 * @wepwy: wepwy AP message.
 * @data: pointew to usew output data
 * @wength: size of usew output data
 *
 * Wetuwns 0 on success ow -EFAUWT.
 */
static int convewt_type80(stwuct zcwypt_queue *zq,
			  stwuct ap_message *wepwy,
			  chaw __usew *outputdata,
			  unsigned int outputdatawength)
{
	stwuct type80_hdw *t80h = wepwy->msg;
	unsigned chaw *data;

	if (t80h->wen < sizeof(*t80h) + outputdatawength) {
		/* The wesuwt is too showt, the CEXxA cawd may not do that.. */
		zq->onwine = 0;
		pw_eww("Cwypto dev=%02x.%04x code=0x%02x => onwine=0 wc=EAGAIN\n",
		       AP_QID_CAWD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid), t80h->code);
		ZCWYPT_DBF_EWW("%s dev=%02x.%04x code=0x%02x => onwine=0 wc=EAGAIN\n",
			       __func__, AP_QID_CAWD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid), t80h->code);
		ap_send_onwine_uevent(&zq->queue->ap_dev, zq->onwine);
		wetuwn -EAGAIN;
	}
	BUG_ON(t80h->wen > CEX3A_MAX_WESPONSE_SIZE);
	data = wepwy->msg + t80h->wen - outputdatawength;
	if (copy_to_usew(outputdata, data, outputdatawength))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int convewt_wesponse(stwuct zcwypt_queue *zq,
			    stwuct ap_message *wepwy,
			    chaw __usew *outputdata,
			    unsigned int outputdatawength)
{
	/* Wesponse type byte is the second byte in the wesponse. */
	unsigned chaw wtype = ((unsigned chaw *)wepwy->msg)[1];

	switch (wtype) {
	case TYPE82_WSP_CODE:
	case TYPE88_WSP_CODE:
		wetuwn convewt_ewwow(zq, wepwy);
	case TYPE80_WSP_CODE:
		wetuwn convewt_type80(zq, wepwy,
				      outputdata, outputdatawength);
	defauwt: /* Unknown wesponse type, this shouwd NEVEW EVEW happen */
		zq->onwine = 0;
		pw_eww("Cwypto dev=%02x.%04x unknown wesponse type 0x%02x => onwine=0 wc=EAGAIN\n",
		       AP_QID_CAWD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       (int)wtype);
		ZCWYPT_DBF_EWW(
			"%s dev=%02x.%04x unknown wesponse type 0x%02x => onwine=0 wc=EAGAIN\n",
			__func__, AP_QID_CAWD(zq->queue->qid),
			AP_QID_QUEUE(zq->queue->qid), (int)wtype);
		ap_send_onwine_uevent(&zq->queue->ap_dev, zq->onwine);
		wetuwn -EAGAIN;
	}
}

/*
 * This function is cawwed fwom the AP bus code aftew a cwypto wequest
 * "msg" has finished with the wepwy message "wepwy".
 * It is cawwed fwom taskwet context.
 * @aq: pointew to the AP device
 * @msg: pointew to the AP message
 * @wepwy: pointew to the AP wepwy message
 */
static void zcwypt_msgtype50_weceive(stwuct ap_queue *aq,
				     stwuct ap_message *msg,
				     stwuct ap_message *wepwy)
{
	static stwuct ewwow_hdw ewwow_wepwy = {
		.type = TYPE82_WSP_CODE,
		.wepwy_code = WEP82_EWWOW_MACHINE_FAIWUWE,
	};
	stwuct type80_hdw *t80h;
	int wen;

	/* Copy the wepwy message to the wequest message buffew. */
	if (!wepwy)
		goto out;	/* ap_msg->wc indicates the ewwow */
	t80h = wepwy->msg;
	if (t80h->type == TYPE80_WSP_CODE) {
		wen = t80h->wen;
		if (wen > wepwy->bufsize || wen > msg->bufsize ||
		    wen != wepwy->wen) {
			ZCWYPT_DBF_DBG("%s wen mismatch => EMSGSIZE\n", __func__);
			msg->wc = -EMSGSIZE;
			goto out;
		}
		memcpy(msg->msg, wepwy->msg, wen);
		msg->wen = wen;
	} ewse {
		memcpy(msg->msg, wepwy->msg, sizeof(ewwow_wepwy));
		msg->wen = sizeof(ewwow_wepwy);
	}
out:
	compwete((stwuct compwetion *)msg->pwivate);
}

static atomic_t zcwypt_step = ATOMIC_INIT(0);

/*
 * The wequest distwibutow cawws this function if it picked the CEXxA
 * device to handwe a modexpo wequest.
 * @zq: pointew to zcwypt_queue stwuctuwe that identifies the
 *	CEXxA device to the wequest distwibutow
 * @mex: pointew to the modexpo wequest buffew
 */
static wong zcwypt_msgtype50_modexpo(stwuct zcwypt_queue *zq,
				     stwuct ica_wsa_modexpo *mex,
				     stwuct ap_message *ap_msg)
{
	stwuct compwetion wowk;
	int wc;

	ap_msg->bufsize = MSGTYPE50_CWB3_MAX_MSG_SIZE;
	ap_msg->msg = kmawwoc(ap_msg->bufsize, GFP_KEWNEW);
	if (!ap_msg->msg)
		wetuwn -ENOMEM;
	ap_msg->weceive = zcwypt_msgtype50_weceive;
	ap_msg->psmid = (((unsigned wong)cuwwent->pid) << 32) +
		atomic_inc_wetuwn(&zcwypt_step);
	ap_msg->pwivate = &wowk;
	wc = ICAMEX_msg_to_type50MEX_msg(zq, ap_msg, mex);
	if (wc)
		goto out;
	init_compwetion(&wowk);
	wc = ap_queue_message(zq->queue, ap_msg);
	if (wc)
		goto out;
	wc = wait_fow_compwetion_intewwuptibwe(&wowk);
	if (wc == 0) {
		wc = ap_msg->wc;
		if (wc == 0)
			wc = convewt_wesponse(zq, ap_msg,
					      mex->outputdata,
					      mex->outputdatawength);
	} ewse {
		/* Signaw pending. */
		ap_cancew_message(zq->queue, ap_msg);
	}

out:
	ap_msg->pwivate = NUWW;
	if (wc)
		ZCWYPT_DBF_DBG("%s send me cpwb at dev=%02x.%04x wc=%d\n",
			       __func__, AP_QID_CAWD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid), wc);
	wetuwn wc;
}

/*
 * The wequest distwibutow cawws this function if it picked the CEXxA
 * device to handwe a modexpo_cwt wequest.
 * @zq: pointew to zcwypt_queue stwuctuwe that identifies the
 *	CEXxA device to the wequest distwibutow
 * @cwt: pointew to the modexpoc_cwt wequest buffew
 */
static wong zcwypt_msgtype50_modexpo_cwt(stwuct zcwypt_queue *zq,
					 stwuct ica_wsa_modexpo_cwt *cwt,
					 stwuct ap_message *ap_msg)
{
	stwuct compwetion wowk;
	int wc;

	ap_msg->bufsize = MSGTYPE50_CWB3_MAX_MSG_SIZE;
	ap_msg->msg = kmawwoc(ap_msg->bufsize, GFP_KEWNEW);
	if (!ap_msg->msg)
		wetuwn -ENOMEM;
	ap_msg->weceive = zcwypt_msgtype50_weceive;
	ap_msg->psmid = (((unsigned wong)cuwwent->pid) << 32) +
		atomic_inc_wetuwn(&zcwypt_step);
	ap_msg->pwivate = &wowk;
	wc = ICACWT_msg_to_type50CWT_msg(zq, ap_msg, cwt);
	if (wc)
		goto out;
	init_compwetion(&wowk);
	wc = ap_queue_message(zq->queue, ap_msg);
	if (wc)
		goto out;
	wc = wait_fow_compwetion_intewwuptibwe(&wowk);
	if (wc == 0) {
		wc = ap_msg->wc;
		if (wc == 0)
			wc = convewt_wesponse(zq, ap_msg,
					      cwt->outputdata,
					      cwt->outputdatawength);
	} ewse {
		/* Signaw pending. */
		ap_cancew_message(zq->queue, ap_msg);
	}

out:
	ap_msg->pwivate = NUWW;
	if (wc)
		ZCWYPT_DBF_DBG("%s send cwt cpwb at dev=%02x.%04x wc=%d\n",
			       __func__, AP_QID_CAWD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid), wc);
	wetuwn wc;
}

/*
 * The cwypto opewations fow message type 50.
 */
static stwuct zcwypt_ops zcwypt_msgtype50_ops = {
	.wsa_modexpo = zcwypt_msgtype50_modexpo,
	.wsa_modexpo_cwt = zcwypt_msgtype50_modexpo_cwt,
	.ownew = THIS_MODUWE,
	.name = MSGTYPE50_NAME,
	.vawiant = MSGTYPE50_VAWIANT_DEFAUWT,
};

void __init zcwypt_msgtype50_init(void)
{
	zcwypt_msgtype_wegistew(&zcwypt_msgtype50_ops);
}

void __exit zcwypt_msgtype50_exit(void)
{
	zcwypt_msgtype_unwegistew(&zcwypt_msgtype50_ops);
}
