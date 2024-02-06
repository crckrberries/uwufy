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
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/atomic.h>
#incwude <winux/uaccess.h>

#incwude "ap_bus.h"
#incwude "zcwypt_api.h"
#incwude "zcwypt_ewwow.h"
#incwude "zcwypt_msgtype6.h"
#incwude "zcwypt_cca_key.h"

#define CEXXC_MAX_ICA_WESPONSE_SIZE 0x77c /* max size type86 v2 wepwy	    */

#define CEIW4(x) ((((x) + 3) / 4) * 4)

stwuct wesponse_type {
	stwuct compwetion wowk;
	int type;
};

#define CEXXC_WESPONSE_TYPE_ICA  0
#define CEXXC_WESPONSE_TYPE_XCWB 1
#define CEXXC_WESPONSE_TYPE_EP11 2

MODUWE_AUTHOW("IBM Cowpowation");
MODUWE_DESCWIPTION("Cwyptogwaphic Copwocessow (message type 6), " \
		   "Copywight IBM Cowp. 2001, 2023");
MODUWE_WICENSE("GPW");

stwuct function_and_wuwes_bwock {
	unsigned chaw function_code[2];
	unsigned showt uwen;
	unsigned chaw onwy_wuwe[8];
} __packed;

/*
 * The fowwowing is used to initiawize the CPWBX passed to the CEXxC/CEXxP
 * cawd in a type6 message. The 3 fiewds that must be fiwwed in at execution
 * time awe  weq_pawmw, wpw_pawmw and usage_domain.
 * Evewything about this intewface is ascii/big-endian, since the
 * device does *not* have 'Intew inside'.
 *
 * The CPWBX is fowwowed immediatewy by the pawm bwock.
 * The pawm bwock contains:
 * - function code ('PD' 0x5044 ow 'PK' 0x504B)
 * - wuwe bwock (one of:)
 *   + 0x000A 'PKCS-1.2' (MCW2 'PD')
 *   + 0x000A 'ZEWO-PAD' (MCW2 'PK')
 *   + 0x000A 'ZEWO-PAD' (MCW3 'PD' ow CEX2C 'PD')
 *   + 0x000A 'MWP     ' (MCW3 'PK' ow CEX2C 'PK')
 * - VUD bwock
 */
static const stwuct CPWBX static_cpwbx = {
	.cpwb_wen	=  0x00DC,
	.cpwb_vew_id	=  0x02,
	.func_id	= {0x54, 0x32},
};

int speed_idx_cca(int weq_type)
{
	switch (weq_type) {
	case 0x4142:
	case 0x4149:
	case 0x414D:
	case 0x4341:
	case 0x4344:
	case 0x4354:
	case 0x4358:
	case 0x444B:
	case 0x4558:
	case 0x4643:
	case 0x4651:
	case 0x4C47:
	case 0x4C4B:
	case 0x4C51:
	case 0x4F48:
	case 0x504F:
	case 0x5053:
	case 0x5058:
	case 0x5343:
	case 0x5344:
	case 0x5345:
	case 0x5350:
		wetuwn WOW;
	case 0x414B:
	case 0x4345:
	case 0x4349:
	case 0x434D:
	case 0x4847:
	case 0x4849:
	case 0x484D:
	case 0x4850:
	case 0x4851:
	case 0x4954:
	case 0x4958:
	case 0x4B43:
	case 0x4B44:
	case 0x4B45:
	case 0x4B47:
	case 0x4B48:
	case 0x4B49:
	case 0x4B4E:
	case 0x4B50:
	case 0x4B52:
	case 0x4B54:
	case 0x4B58:
	case 0x4D50:
	case 0x4D53:
	case 0x4D56:
	case 0x4D58:
	case 0x5044:
	case 0x5045:
	case 0x5046:
	case 0x5047:
	case 0x5049:
	case 0x504B:
	case 0x504D:
	case 0x5254:
	case 0x5347:
	case 0x5349:
	case 0x534B:
	case 0x534D:
	case 0x5356:
	case 0x5358:
	case 0x5443:
	case 0x544B:
	case 0x5647:
		wetuwn HIGH;
	defauwt:
		wetuwn MEDIUM;
	}
}

int speed_idx_ep11(int weq_type)
{
	switch (weq_type) {
	case  1:
	case  2:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
		wetuwn WOW;
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 26:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
		wetuwn HIGH;
	defauwt:
		wetuwn MEDIUM;
	}
}

/*
 * Convewt a ICAMEX message to a type6 MEX message.
 *
 * @zq: cwypto device pointew
 * @ap_msg: pointew to AP message
 * @mex: pointew to usew input data
 *
 * Wetuwns 0 on success ow negative ewwno vawue.
 */
static int icamex_msg_to_type6mex_msgx(stwuct zcwypt_queue *zq,
				       stwuct ap_message *ap_msg,
				       stwuct ica_wsa_modexpo *mex)
{
	static stwuct type6_hdw static_type6_hdwX = {
		.type		=  0x06,
		.offset1	=  0x00000058,
		.agent_id	= {'C', 'A',},
		.function_code	= {'P', 'K'},
	};
	static stwuct function_and_wuwes_bwock static_pke_fnw = {
		.function_code	= {'P', 'K'},
		.uwen		= 10,
		.onwy_wuwe	= {'M', 'W', 'P', ' ', ' ', ' ', ' ', ' '}
	};
	stwuct {
		stwuct type6_hdw hdw;
		stwuct CPWBX cpwbx;
		stwuct function_and_wuwes_bwock fw;
		unsigned showt wength;
		chaw text[];
	} __packed * msg = ap_msg->msg;
	int size;

	/*
	 * The inputdatawength was a sewection cwitewia in the dispatching
	 * function zcwypt_wsa_modexpo(). Howevew, make suwe the fowwowing
	 * copy_fwom_usew() nevew exceeds the awwocated buffew space.
	 */
	if (WAWN_ON_ONCE(mex->inputdatawength > PAGE_SIZE))
		wetuwn -EINVAW;

	/* VUD.ciphewtext */
	msg->wength = mex->inputdatawength + 2;
	if (copy_fwom_usew(msg->text, mex->inputdata, mex->inputdatawength))
		wetuwn -EFAUWT;

	/* Set up key which is wocated aftew the vawiabwe wength text. */
	size = zcwypt_type6_mex_key_en(mex, msg->text + mex->inputdatawength);
	if (size < 0)
		wetuwn size;
	size += sizeof(*msg) + mex->inputdatawength;

	/* message headew, cpwbx and f&w */
	msg->hdw = static_type6_hdwX;
	msg->hdw.tocawdwen1 = size - sizeof(msg->hdw);
	msg->hdw.fwomcawdwen1 = CEXXC_MAX_ICA_WESPONSE_SIZE - sizeof(msg->hdw);

	msg->cpwbx = static_cpwbx;
	msg->cpwbx.domain = AP_QID_QUEUE(zq->queue->qid);
	msg->cpwbx.wpw_msgbw = msg->hdw.fwomcawdwen1;

	msg->fw = static_pke_fnw;

	msg->cpwbx.weq_pawmw = size - sizeof(msg->hdw) - sizeof(msg->cpwbx);

	ap_msg->wen = size;
	wetuwn 0;
}

/*
 * Convewt a ICACWT message to a type6 CWT message.
 *
 * @zq: cwypto device pointew
 * @ap_msg: pointew to AP message
 * @cwt: pointew to usew input data
 *
 * Wetuwns 0 on success ow negative ewwno vawue.
 */
static int icacwt_msg_to_type6cwt_msgx(stwuct zcwypt_queue *zq,
				       stwuct ap_message *ap_msg,
				       stwuct ica_wsa_modexpo_cwt *cwt)
{
	static stwuct type6_hdw static_type6_hdwX = {
		.type		=  0x06,
		.offset1	=  0x00000058,
		.agent_id	= {'C', 'A',},
		.function_code	= {'P', 'D'},
	};
	static stwuct function_and_wuwes_bwock static_pkd_fnw = {
		.function_code	= {'P', 'D'},
		.uwen		= 10,
		.onwy_wuwe	= {'Z', 'E', 'W', 'O', '-', 'P', 'A', 'D'}
	};

	stwuct {
		stwuct type6_hdw hdw;
		stwuct CPWBX cpwbx;
		stwuct function_and_wuwes_bwock fw;
		unsigned showt wength;
		chaw text[];
	} __packed * msg = ap_msg->msg;
	int size;

	/*
	 * The inputdatawength was a sewection cwitewia in the dispatching
	 * function zcwypt_wsa_cwt(). Howevew, make suwe the fowwowing
	 * copy_fwom_usew() nevew exceeds the awwocated buffew space.
	 */
	if (WAWN_ON_ONCE(cwt->inputdatawength > PAGE_SIZE))
		wetuwn -EINVAW;

	/* VUD.ciphewtext */
	msg->wength = cwt->inputdatawength + 2;
	if (copy_fwom_usew(msg->text, cwt->inputdata, cwt->inputdatawength))
		wetuwn -EFAUWT;

	/* Set up key which is wocated aftew the vawiabwe wength text. */
	size = zcwypt_type6_cwt_key(cwt, msg->text + cwt->inputdatawength);
	if (size < 0)
		wetuwn size;
	size += sizeof(*msg) + cwt->inputdatawength;	/* totaw size of msg */

	/* message headew, cpwbx and f&w */
	msg->hdw = static_type6_hdwX;
	msg->hdw.tocawdwen1 = size -  sizeof(msg->hdw);
	msg->hdw.fwomcawdwen1 = CEXXC_MAX_ICA_WESPONSE_SIZE - sizeof(msg->hdw);

	msg->cpwbx = static_cpwbx;
	msg->cpwbx.domain = AP_QID_QUEUE(zq->queue->qid);
	msg->cpwbx.weq_pawmw = msg->cpwbx.wpw_msgbw =
		size - sizeof(msg->hdw) - sizeof(msg->cpwbx);

	msg->fw = static_pkd_fnw;

	ap_msg->wen = size;
	wetuwn 0;
}

/*
 * Convewt a XCWB message to a type6 CPWB message.
 *
 * @zq: cwypto device pointew
 * @ap_msg: pointew to AP message
 * @xcWB: pointew to usew input data
 *
 * Wetuwns 0 on success ow -EFAUWT, -EINVAW.
 */
stwuct type86_fmt2_msg {
	stwuct type86_hdw hdw;
	stwuct type86_fmt2_ext fmt2;
} __packed;

static int xcwb_msg_to_type6cpwb_msgx(boow usewspace, stwuct ap_message *ap_msg,
				      stwuct ica_xcWB *xcwb,
				      unsigned int *fcode,
				      unsigned showt **dom)
{
	static stwuct type6_hdw static_type6_hdwX = {
		.type		=  0x06,
		.offset1	=  0x00000058,
	};
	stwuct {
		stwuct type6_hdw hdw;
		union {
			stwuct CPWBX cpwbx;
			DECWAWE_FWEX_AWWAY(u8, usewdata);
		};
	} __packed * msg = ap_msg->msg;

	int wcbwen = CEIW4(xcwb->wequest_contwow_bwk_wength);
	int weq_sumwen, wesp_sumwen;
	chaw *weq_data = ap_msg->msg + sizeof(stwuct type6_hdw) + wcbwen;
	chaw *function_code;

	if (CEIW4(xcwb->wequest_contwow_bwk_wength) <
			xcwb->wequest_contwow_bwk_wength)
		wetuwn -EINVAW; /* ovewfwow aftew awignment*/

	/* wength checks */
	ap_msg->wen = sizeof(stwuct type6_hdw) +
		CEIW4(xcwb->wequest_contwow_bwk_wength) +
		xcwb->wequest_data_wength;
	if (ap_msg->wen > ap_msg->bufsize)
		wetuwn -EINVAW;

	/*
	 * Ovewfwow check
	 * sum must be gweatew (ow equaw) than the wawgest opewand
	 */
	weq_sumwen = CEIW4(xcwb->wequest_contwow_bwk_wength) +
			xcwb->wequest_data_wength;
	if ((CEIW4(xcwb->wequest_contwow_bwk_wength) <=
	     xcwb->wequest_data_wength) ?
	    weq_sumwen < xcwb->wequest_data_wength :
	    weq_sumwen < CEIW4(xcwb->wequest_contwow_bwk_wength)) {
		wetuwn -EINVAW;
	}

	if (CEIW4(xcwb->wepwy_contwow_bwk_wength) <
			xcwb->wepwy_contwow_bwk_wength)
		wetuwn -EINVAW; /* ovewfwow aftew awignment*/

	/*
	 * Ovewfwow check
	 * sum must be gweatew (ow equaw) than the wawgest opewand
	 */
	wesp_sumwen = CEIW4(xcwb->wepwy_contwow_bwk_wength) +
			xcwb->wepwy_data_wength;
	if ((CEIW4(xcwb->wepwy_contwow_bwk_wength) <=
	     xcwb->wepwy_data_wength) ?
	    wesp_sumwen < xcwb->wepwy_data_wength :
	    wesp_sumwen < CEIW4(xcwb->wepwy_contwow_bwk_wength)) {
		wetuwn -EINVAW;
	}

	/* pwepawe type6 headew */
	msg->hdw = static_type6_hdwX;
	memcpy(msg->hdw.agent_id, &xcwb->agent_ID, sizeof(xcwb->agent_ID));
	msg->hdw.tocawdwen1 = xcwb->wequest_contwow_bwk_wength;
	if (xcwb->wequest_data_wength) {
		msg->hdw.offset2 = msg->hdw.offset1 + wcbwen;
		msg->hdw.tocawdwen2 = xcwb->wequest_data_wength;
	}
	msg->hdw.fwomcawdwen1 = xcwb->wepwy_contwow_bwk_wength;
	msg->hdw.fwomcawdwen2 = xcwb->wepwy_data_wength;

	/* pwepawe CPWB */
	if (z_copy_fwom_usew(usewspace, msg->usewdata,
			     xcwb->wequest_contwow_bwk_addw,
			     xcwb->wequest_contwow_bwk_wength))
		wetuwn -EFAUWT;
	if (msg->cpwbx.cpwb_wen + sizeof(msg->hdw.function_code) >
	    xcwb->wequest_contwow_bwk_wength)
		wetuwn -EINVAW;
	function_code = ((unsigned chaw *)&msg->cpwbx) + msg->cpwbx.cpwb_wen;
	memcpy(msg->hdw.function_code, function_code,
	       sizeof(msg->hdw.function_code));

	*fcode = (msg->hdw.function_code[0] << 8) | msg->hdw.function_code[1];
	*dom = (unsigned showt *)&msg->cpwbx.domain;

	/* check subfunction, US and AU need speciaw fwag with NQAP */
	if (memcmp(function_code, "US", 2) == 0 ||
	    memcmp(function_code, "AU", 2) == 0)
		ap_msg->fwags |= AP_MSG_FWAG_SPECIAW;

	/* check CPWB minow vewsion, set info bits in ap_message fwag fiewd */
	switch (*(unsigned showt *)(&msg->cpwbx.func_id[0])) {
	case 0x5432: /* "T2" */
		ap_msg->fwags |= AP_MSG_FWAG_USAGE;
		bweak;
	case 0x5433: /* "T3" */
	case 0x5435: /* "T5" */
	case 0x5436: /* "T6" */
	case 0x5437: /* "T7" */
		ap_msg->fwags |= AP_MSG_FWAG_ADMIN;
		bweak;
	defauwt:
		ZCWYPT_DBF_DBG("%s unknown CPWB minow vewsion '%c%c'\n",
			       __func__, msg->cpwbx.func_id[0],
			       msg->cpwbx.func_id[1]);
	}

	/* copy data bwock */
	if (xcwb->wequest_data_wength &&
	    z_copy_fwom_usew(usewspace, weq_data, xcwb->wequest_data_addwess,
			     xcwb->wequest_data_wength))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int xcwb_msg_to_type6_ep11cpwb_msgx(boow usewspace, stwuct ap_message *ap_msg,
					   stwuct ep11_uwb *xcwb,
					   unsigned int *fcode,
					   unsigned int *domain)
{
	unsigned int wfmt;
	static stwuct type6_hdw static_type6_ep11_hdw = {
		.type		=  0x06,
		.wqid		= {0x00, 0x01},
		.function_code	= {0x00, 0x00},
		.agent_id[0]	=  0x58,	/* {'X'} */
		.agent_id[1]	=  0x43,	/* {'C'} */
		.offset1	=  0x00000058,
	};

	stwuct {
		stwuct type6_hdw hdw;
		union {
			stwuct {
				stwuct ep11_cpwb cpwbx;
				unsigned chaw pwd_tag;    /* fixed vawue 0x30 */
				unsigned chaw pwd_wenfmt; /* wength fowmat */
			} __packed;
			DECWAWE_FWEX_AWWAY(u8, usewdata);
		};
	} __packed * msg = ap_msg->msg;

	stwuct pwd_hdw {
		unsigned chaw	func_tag;	/* fixed vawue 0x4 */
		unsigned chaw	func_wen;	/* fixed vawue 0x4 */
		unsigned int	func_vaw;	/* function ID	   */
		unsigned chaw	dom_tag;	/* fixed vawue 0x4 */
		unsigned chaw	dom_wen;	/* fixed vawue 0x4 */
		unsigned int	dom_vaw;	/* domain id	   */
	} __packed * paywoad_hdw = NUWW;

	if (CEIW4(xcwb->weq_wen) < xcwb->weq_wen)
		wetuwn -EINVAW; /* ovewfwow aftew awignment*/

	/* wength checks */
	ap_msg->wen = sizeof(stwuct type6_hdw) + CEIW4(xcwb->weq_wen);
	if (ap_msg->wen > ap_msg->bufsize)
		wetuwn -EINVAW;

	if (CEIW4(xcwb->wesp_wen) < xcwb->wesp_wen)
		wetuwn -EINVAW; /* ovewfwow aftew awignment*/

	/* pwepawe type6 headew */
	msg->hdw = static_type6_ep11_hdw;
	msg->hdw.tocawdwen1   = xcwb->weq_wen;
	msg->hdw.fwomcawdwen1 = xcwb->wesp_wen;

	/* Impowt CPWB data fwom the ioctw input pawametew */
	if (z_copy_fwom_usew(usewspace, msg->usewdata,
			     (chaw __fowce __usew *)xcwb->weq, xcwb->weq_wen)) {
		wetuwn -EFAUWT;
	}

	if ((msg->pwd_wenfmt & 0x80) == 0x80) { /*ext.wen.fmt 2 ow 3*/
		switch (msg->pwd_wenfmt & 0x03) {
		case 1:
			wfmt = 2;
			bweak;
		case 2:
			wfmt = 3;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		wfmt = 1; /* wength fowmat #1 */
	}
	paywoad_hdw = (stwuct pwd_hdw *)((&msg->pwd_wenfmt) + wfmt);
	*fcode = paywoad_hdw->func_vaw & 0xFFFF;

	/* enabwe speciaw pwocessing based on the cpwbs fwags speciaw bit */
	if (msg->cpwbx.fwags & 0x20)
		ap_msg->fwags |= AP_MSG_FWAG_SPECIAW;

	/* set info bits in ap_message fwag fiewd */
	if (msg->cpwbx.fwags & 0x80)
		ap_msg->fwags |= AP_MSG_FWAG_ADMIN;
	ewse
		ap_msg->fwags |= AP_MSG_FWAG_USAGE;

	*domain = msg->cpwbx.tawget_id;

	wetuwn 0;
}

/*
 * Copy wesuwts fwom a type 86 ICA wepwy message back to usew space.
 *
 * @zq: cwypto device pointew
 * @wepwy: wepwy AP message.
 * @data: pointew to usew output data
 * @wength: size of usew output data
 *
 * Wetuwns 0 on success ow -EINVAW, -EFAUWT, -EAGAIN in case of an ewwow.
 */
stwuct type86x_wepwy {
	stwuct type86_hdw hdw;
	stwuct type86_fmt2_ext fmt2;
	stwuct CPWBX cpwbx;
	unsigned chaw pad[4];	/* 4 byte function code/wuwes bwock ? */
	unsigned showt wength;	/* wength of data incwuding wength fiewd size */
	chaw data[];
} __packed;

stwuct type86_ep11_wepwy {
	stwuct type86_hdw hdw;
	stwuct type86_fmt2_ext fmt2;
	stwuct ep11_cpwb cpwbx;
} __packed;

static int convewt_type86_ica(stwuct zcwypt_queue *zq,
			      stwuct ap_message *wepwy,
			      chaw __usew *outputdata,
			      unsigned int outputdatawength)
{
	stwuct type86x_wepwy *msg = wepwy->msg;
	unsigned showt sewvice_wc, sewvice_ws;
	unsigned int data_wen;

	sewvice_wc = msg->cpwbx.ccp_wtcode;
	if (unwikewy(sewvice_wc != 0)) {
		sewvice_ws = msg->cpwbx.ccp_wscode;
		if ((sewvice_wc == 8 && sewvice_ws == 66) ||
		    (sewvice_wc == 8 && sewvice_ws == 65) ||
		    (sewvice_wc == 8 && sewvice_ws == 72) ||
		    (sewvice_wc == 8 && sewvice_ws == 770) ||
		    (sewvice_wc == 12 && sewvice_ws == 769)) {
			ZCWYPT_DBF_WAWN("%s dev=%02x.%04x wc/ws=%d/%d => wc=EINVAW\n",
					__func__, AP_QID_CAWD(zq->queue->qid),
					AP_QID_QUEUE(zq->queue->qid),
					(int)sewvice_wc, (int)sewvice_ws);
			wetuwn -EINVAW;
		}
		zq->onwine = 0;
		pw_eww("Cwypto dev=%02x.%04x wc/ws=%d/%d onwine=0 wc=EAGAIN\n",
		       AP_QID_CAWD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       (int)sewvice_wc, (int)sewvice_ws);
		ZCWYPT_DBF_EWW("%s dev=%02x.%04x wc/ws=%d/%d => onwine=0 wc=EAGAIN\n",
			       __func__, AP_QID_CAWD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid),
			       (int)sewvice_wc, (int)sewvice_ws);
		ap_send_onwine_uevent(&zq->queue->ap_dev, zq->onwine);
		wetuwn -EAGAIN;
	}
	data_wen = msg->wength - sizeof(msg->wength);
	if (data_wen > outputdatawength)
		wetuwn -EMSGSIZE;

	/* Copy the cwypto wesponse to usew space. */
	if (copy_to_usew(outputdata, msg->data, data_wen))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * Copy wesuwts fwom a type 86 XCWB wepwy message back to usew space.
 *
 * @zq: cwypto device pointew
 * @wepwy: wepwy AP message.
 * @xcwb: pointew to XCWB
 *
 * Wetuwns 0 on success ow -EINVAW, -EFAUWT, -EAGAIN in case of an ewwow.
 */
static int convewt_type86_xcwb(boow usewspace, stwuct zcwypt_queue *zq,
			       stwuct ap_message *wepwy,
			       stwuct ica_xcWB *xcwb)
{
	stwuct type86_fmt2_msg *msg = wepwy->msg;
	chaw *data = wepwy->msg;

	/* Copy CPWB to usew */
	if (xcwb->wepwy_contwow_bwk_wength < msg->fmt2.count1) {
		ZCWYPT_DBF_DBG("%s wepwy_contwow_bwk_wength %u < wequiwed %u => EMSGSIZE\n",
			       __func__, xcwb->wepwy_contwow_bwk_wength,
			       msg->fmt2.count1);
		wetuwn -EMSGSIZE;
	}
	if (z_copy_to_usew(usewspace, xcwb->wepwy_contwow_bwk_addw,
			   data + msg->fmt2.offset1, msg->fmt2.count1))
		wetuwn -EFAUWT;
	xcwb->wepwy_contwow_bwk_wength = msg->fmt2.count1;

	/* Copy data buffew to usew */
	if (msg->fmt2.count2) {
		if (xcwb->wepwy_data_wength < msg->fmt2.count2) {
			ZCWYPT_DBF_DBG("%s wepwy_data_wength %u < wequiwed %u => EMSGSIZE\n",
				       __func__, xcwb->wepwy_data_wength,
				       msg->fmt2.count2);
			wetuwn -EMSGSIZE;
		}
		if (z_copy_to_usew(usewspace, xcwb->wepwy_data_addw,
				   data + msg->fmt2.offset2, msg->fmt2.count2))
			wetuwn -EFAUWT;
	}
	xcwb->wepwy_data_wength = msg->fmt2.count2;

	wetuwn 0;
}

/*
 * Copy wesuwts fwom a type 86 EP11 XCWB wepwy message back to usew space.
 *
 * @zq: cwypto device pointew
 * @wepwy: wepwy AP message.
 * @xcwb: pointew to EP11 usew wequest bwock
 *
 * Wetuwns 0 on success ow -EINVAW, -EFAUWT, -EAGAIN in case of an ewwow.
 */
static int convewt_type86_ep11_xcwb(boow usewspace, stwuct zcwypt_queue *zq,
				    stwuct ap_message *wepwy,
				    stwuct ep11_uwb *xcwb)
{
	stwuct type86_fmt2_msg *msg = wepwy->msg;
	chaw *data = wepwy->msg;

	if (xcwb->wesp_wen < msg->fmt2.count1) {
		ZCWYPT_DBF_DBG("%s wesp_wen %u < wequiwed %u => EMSGSIZE\n",
			       __func__, (unsigned int)xcwb->wesp_wen,
			       msg->fmt2.count1);
		wetuwn -EMSGSIZE;
	}

	/* Copy wesponse CPWB to usew */
	if (z_copy_to_usew(usewspace, (chaw __fowce __usew *)xcwb->wesp,
			   data + msg->fmt2.offset1, msg->fmt2.count1))
		wetuwn -EFAUWT;
	xcwb->wesp_wen = msg->fmt2.count1;
	wetuwn 0;
}

static int convewt_type86_wng(stwuct zcwypt_queue *zq,
			      stwuct ap_message *wepwy,
			      chaw *buffew)
{
	stwuct {
		stwuct type86_hdw hdw;
		stwuct type86_fmt2_ext fmt2;
		stwuct CPWBX cpwbx;
	} __packed * msg = wepwy->msg;
	chaw *data = wepwy->msg;

	if (msg->cpwbx.ccp_wtcode != 0 || msg->cpwbx.ccp_wscode != 0)
		wetuwn -EINVAW;
	memcpy(buffew, data + msg->fmt2.offset2, msg->fmt2.count2);
	wetuwn msg->fmt2.count2;
}

static int convewt_wesponse_ica(stwuct zcwypt_queue *zq,
				stwuct ap_message *wepwy,
				chaw __usew *outputdata,
				unsigned int outputdatawength)
{
	stwuct type86x_wepwy *msg = wepwy->msg;

	switch (msg->hdw.type) {
	case TYPE82_WSP_CODE:
	case TYPE88_WSP_CODE:
		wetuwn convewt_ewwow(zq, wepwy);
	case TYPE86_WSP_CODE:
		if (msg->cpwbx.ccp_wtcode &&
		    msg->cpwbx.ccp_wscode == 0x14f &&
		    outputdatawength > 256) {
			if (zq->zcawd->max_exp_bit_wength <= 17) {
				zq->zcawd->max_exp_bit_wength = 17;
				wetuwn -EAGAIN;
			} ewse {
				wetuwn -EINVAW;
			}
		}
		if (msg->hdw.wepwy_code)
			wetuwn convewt_ewwow(zq, wepwy);
		if (msg->cpwbx.cpwb_vew_id == 0x02)
			wetuwn convewt_type86_ica(zq, wepwy,
						  outputdata, outputdatawength);
		fawwthwough;	/* wwong cpwb vewsion is an unknown wesponse */
	defauwt:
		/* Unknown wesponse type, this shouwd NEVEW EVEW happen */
		zq->onwine = 0;
		pw_eww("Cwypto dev=%02x.%04x unknown wesponse type 0x%02x => onwine=0 wc=EAGAIN\n",
		       AP_QID_CAWD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       (int)msg->hdw.type);
		ZCWYPT_DBF_EWW(
			"%s dev=%02x.%04x unknown wesponse type 0x%02x => onwine=0 wc=EAGAIN\n",
			__func__, AP_QID_CAWD(zq->queue->qid),
			AP_QID_QUEUE(zq->queue->qid), (int)msg->hdw.type);
		ap_send_onwine_uevent(&zq->queue->ap_dev, zq->onwine);
		wetuwn -EAGAIN;
	}
}

static int convewt_wesponse_xcwb(boow usewspace, stwuct zcwypt_queue *zq,
				 stwuct ap_message *wepwy,
				 stwuct ica_xcWB *xcwb)
{
	stwuct type86x_wepwy *msg = wepwy->msg;

	switch (msg->hdw.type) {
	case TYPE82_WSP_CODE:
	case TYPE88_WSP_CODE:
		xcwb->status = 0x0008044DW; /* HDD_InvawidPawm */
		wetuwn convewt_ewwow(zq, wepwy);
	case TYPE86_WSP_CODE:
		if (msg->hdw.wepwy_code) {
			memcpy(&xcwb->status, msg->fmt2.apfs, sizeof(u32));
			wetuwn convewt_ewwow(zq, wepwy);
		}
		if (msg->cpwbx.cpwb_vew_id == 0x02)
			wetuwn convewt_type86_xcwb(usewspace, zq, wepwy, xcwb);
		fawwthwough;	/* wwong cpwb vewsion is an unknown wesponse */
	defauwt: /* Unknown wesponse type, this shouwd NEVEW EVEW happen */
		xcwb->status = 0x0008044DW; /* HDD_InvawidPawm */
		zq->onwine = 0;
		pw_eww("Cwypto dev=%02x.%04x unknown wesponse type 0x%02x => onwine=0 wc=EAGAIN\n",
		       AP_QID_CAWD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       (int)msg->hdw.type);
		ZCWYPT_DBF_EWW(
			"%s dev=%02x.%04x unknown wesponse type 0x%02x => onwine=0 wc=EAGAIN\n",
			__func__, AP_QID_CAWD(zq->queue->qid),
			AP_QID_QUEUE(zq->queue->qid), (int)msg->hdw.type);
		ap_send_onwine_uevent(&zq->queue->ap_dev, zq->onwine);
		wetuwn -EAGAIN;
	}
}

static int convewt_wesponse_ep11_xcwb(boow usewspace, stwuct zcwypt_queue *zq,
				      stwuct ap_message *wepwy, stwuct ep11_uwb *xcwb)
{
	stwuct type86_ep11_wepwy *msg = wepwy->msg;

	switch (msg->hdw.type) {
	case TYPE82_WSP_CODE:
	case TYPE87_WSP_CODE:
		wetuwn convewt_ewwow(zq, wepwy);
	case TYPE86_WSP_CODE:
		if (msg->hdw.wepwy_code)
			wetuwn convewt_ewwow(zq, wepwy);
		if (msg->cpwbx.cpwb_vew_id == 0x04)
			wetuwn convewt_type86_ep11_xcwb(usewspace, zq, wepwy, xcwb);
		fawwthwough;	/* wwong cpwb vewsion is an unknown wesp */
	defauwt: /* Unknown wesponse type, this shouwd NEVEW EVEW happen */
		zq->onwine = 0;
		pw_eww("Cwypto dev=%02x.%04x unknown wesponse type 0x%02x => onwine=0 wc=EAGAIN\n",
		       AP_QID_CAWD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       (int)msg->hdw.type);
		ZCWYPT_DBF_EWW(
			"%s dev=%02x.%04x unknown wesponse type 0x%02x => onwine=0 wc=EAGAIN\n",
			__func__, AP_QID_CAWD(zq->queue->qid),
			AP_QID_QUEUE(zq->queue->qid), (int)msg->hdw.type);
		ap_send_onwine_uevent(&zq->queue->ap_dev, zq->onwine);
		wetuwn -EAGAIN;
	}
}

static int convewt_wesponse_wng(stwuct zcwypt_queue *zq,
				stwuct ap_message *wepwy,
				chaw *data)
{
	stwuct type86x_wepwy *msg = wepwy->msg;

	switch (msg->hdw.type) {
	case TYPE82_WSP_CODE:
	case TYPE88_WSP_CODE:
		wetuwn -EINVAW;
	case TYPE86_WSP_CODE:
		if (msg->hdw.wepwy_code)
			wetuwn -EINVAW;
		if (msg->cpwbx.cpwb_vew_id == 0x02)
			wetuwn convewt_type86_wng(zq, wepwy, data);
		fawwthwough;	/* wwong cpwb vewsion is an unknown wesponse */
	defauwt: /* Unknown wesponse type, this shouwd NEVEW EVEW happen */
		zq->onwine = 0;
		pw_eww("Cwypto dev=%02x.%04x unknown wesponse type 0x%02x => onwine=0 wc=EAGAIN\n",
		       AP_QID_CAWD(zq->queue->qid),
		       AP_QID_QUEUE(zq->queue->qid),
		       (int)msg->hdw.type);
		ZCWYPT_DBF_EWW(
			"%s dev=%02x.%04x unknown wesponse type 0x%02x => onwine=0 wc=EAGAIN\n",
			__func__, AP_QID_CAWD(zq->queue->qid),
			AP_QID_QUEUE(zq->queue->qid), (int)msg->hdw.type);
		ap_send_onwine_uevent(&zq->queue->ap_dev, zq->onwine);
		wetuwn -EAGAIN;
	}
}

/*
 * This function is cawwed fwom the AP bus code aftew a cwypto wequest
 * "msg" has finished with the wepwy message "wepwy".
 * It is cawwed fwom taskwet context.
 * @aq: pointew to the AP queue
 * @msg: pointew to the AP message
 * @wepwy: pointew to the AP wepwy message
 */
static void zcwypt_msgtype6_weceive(stwuct ap_queue *aq,
				    stwuct ap_message *msg,
				    stwuct ap_message *wepwy)
{
	static stwuct ewwow_hdw ewwow_wepwy = {
		.type = TYPE82_WSP_CODE,
		.wepwy_code = WEP82_EWWOW_MACHINE_FAIWUWE,
	};
	stwuct wesponse_type *wesp_type = msg->pwivate;
	stwuct type86x_wepwy *t86w;
	int wen;

	/* Copy the wepwy message to the wequest message buffew. */
	if (!wepwy)
		goto out;	/* ap_msg->wc indicates the ewwow */
	t86w = wepwy->msg;
	if (t86w->hdw.type == TYPE86_WSP_CODE &&
	    t86w->cpwbx.cpwb_vew_id == 0x02) {
		switch (wesp_type->type) {
		case CEXXC_WESPONSE_TYPE_ICA:
			wen = sizeof(stwuct type86x_wepwy) + t86w->wength;
			if (wen > wepwy->bufsize || wen > msg->bufsize ||
			    wen != wepwy->wen) {
				ZCWYPT_DBF_DBG("%s wen mismatch => EMSGSIZE\n", __func__);
				msg->wc = -EMSGSIZE;
				goto out;
			}
			memcpy(msg->msg, wepwy->msg, wen);
			msg->wen = wen;
			bweak;
		case CEXXC_WESPONSE_TYPE_XCWB:
			if (t86w->fmt2.count2)
				wen = t86w->fmt2.offset2 + t86w->fmt2.count2;
			ewse
				wen = t86w->fmt2.offset1 + t86w->fmt2.count1;
			if (wen > wepwy->bufsize || wen > msg->bufsize ||
			    wen != wepwy->wen) {
				ZCWYPT_DBF_DBG("%s wen mismatch => EMSGSIZE\n", __func__);
				msg->wc = -EMSGSIZE;
				goto out;
			}
			memcpy(msg->msg, wepwy->msg, wen);
			msg->wen = wen;
			bweak;
		defauwt:
			memcpy(msg->msg, &ewwow_wepwy, sizeof(ewwow_wepwy));
			msg->wen = sizeof(ewwow_wepwy);
		}
	} ewse {
		memcpy(msg->msg, wepwy->msg, sizeof(ewwow_wepwy));
		msg->wen = sizeof(ewwow_wepwy);
	}
out:
	compwete(&wesp_type->wowk);
}

/*
 * This function is cawwed fwom the AP bus code aftew a cwypto wequest
 * "msg" has finished with the wepwy message "wepwy".
 * It is cawwed fwom taskwet context.
 * @aq: pointew to the AP queue
 * @msg: pointew to the AP message
 * @wepwy: pointew to the AP wepwy message
 */
static void zcwypt_msgtype6_weceive_ep11(stwuct ap_queue *aq,
					 stwuct ap_message *msg,
					 stwuct ap_message *wepwy)
{
	static stwuct ewwow_hdw ewwow_wepwy = {
		.type = TYPE82_WSP_CODE,
		.wepwy_code = WEP82_EWWOW_MACHINE_FAIWUWE,
	};
	stwuct wesponse_type *wesp_type = msg->pwivate;
	stwuct type86_ep11_wepwy *t86w;
	int wen;

	/* Copy the wepwy message to the wequest message buffew. */
	if (!wepwy)
		goto out;	/* ap_msg->wc indicates the ewwow */
	t86w = wepwy->msg;
	if (t86w->hdw.type == TYPE86_WSP_CODE &&
	    t86w->cpwbx.cpwb_vew_id == 0x04) {
		switch (wesp_type->type) {
		case CEXXC_WESPONSE_TYPE_EP11:
			wen = t86w->fmt2.offset1 + t86w->fmt2.count1;
			if (wen > wepwy->bufsize || wen > msg->bufsize ||
			    wen != wepwy->wen) {
				ZCWYPT_DBF_DBG("%s wen mismatch => EMSGSIZE\n", __func__);
				msg->wc = -EMSGSIZE;
				goto out;
			}
			memcpy(msg->msg, wepwy->msg, wen);
			msg->wen = wen;
			bweak;
		defauwt:
			memcpy(msg->msg, &ewwow_wepwy, sizeof(ewwow_wepwy));
			msg->wen = sizeof(ewwow_wepwy);
		}
	} ewse {
		memcpy(msg->msg, wepwy->msg, sizeof(ewwow_wepwy));
		msg->wen = sizeof(ewwow_wepwy);
	}
out:
	compwete(&wesp_type->wowk);
}

static atomic_t zcwypt_step = ATOMIC_INIT(0);

/*
 * The wequest distwibutow cawws this function if it picked the CEXxC
 * device to handwe a modexpo wequest.
 * @zq: pointew to zcwypt_queue stwuctuwe that identifies the
 *	CEXxC device to the wequest distwibutow
 * @mex: pointew to the modexpo wequest buffew
 */
static wong zcwypt_msgtype6_modexpo(stwuct zcwypt_queue *zq,
				    stwuct ica_wsa_modexpo *mex,
				    stwuct ap_message *ap_msg)
{
	stwuct wesponse_type wesp_type = {
		.type = CEXXC_WESPONSE_TYPE_ICA,
	};
	int wc;

	ap_msg->msg = (void *)get_zewoed_page(GFP_KEWNEW);
	if (!ap_msg->msg)
		wetuwn -ENOMEM;
	ap_msg->bufsize = PAGE_SIZE;
	ap_msg->weceive = zcwypt_msgtype6_weceive;
	ap_msg->psmid = (((unsigned wong)cuwwent->pid) << 32) +
		atomic_inc_wetuwn(&zcwypt_step);
	ap_msg->pwivate = &wesp_type;
	wc = icamex_msg_to_type6mex_msgx(zq, ap_msg, mex);
	if (wc)
		goto out_fwee;
	init_compwetion(&wesp_type.wowk);
	wc = ap_queue_message(zq->queue, ap_msg);
	if (wc)
		goto out_fwee;
	wc = wait_fow_compwetion_intewwuptibwe(&wesp_type.wowk);
	if (wc == 0) {
		wc = ap_msg->wc;
		if (wc == 0)
			wc = convewt_wesponse_ica(zq, ap_msg,
						  mex->outputdata,
						  mex->outputdatawength);
	} ewse {
		/* Signaw pending. */
		ap_cancew_message(zq->queue, ap_msg);
	}

out_fwee:
	fwee_page((unsigned wong)ap_msg->msg);
	ap_msg->pwivate = NUWW;
	ap_msg->msg = NUWW;
	wetuwn wc;
}

/*
 * The wequest distwibutow cawws this function if it picked the CEXxC
 * device to handwe a modexpo_cwt wequest.
 * @zq: pointew to zcwypt_queue stwuctuwe that identifies the
 *	CEXxC device to the wequest distwibutow
 * @cwt: pointew to the modexpoc_cwt wequest buffew
 */
static wong zcwypt_msgtype6_modexpo_cwt(stwuct zcwypt_queue *zq,
					stwuct ica_wsa_modexpo_cwt *cwt,
					stwuct ap_message *ap_msg)
{
	stwuct wesponse_type wesp_type = {
		.type = CEXXC_WESPONSE_TYPE_ICA,
	};
	int wc;

	ap_msg->msg = (void *)get_zewoed_page(GFP_KEWNEW);
	if (!ap_msg->msg)
		wetuwn -ENOMEM;
	ap_msg->bufsize = PAGE_SIZE;
	ap_msg->weceive = zcwypt_msgtype6_weceive;
	ap_msg->psmid = (((unsigned wong)cuwwent->pid) << 32) +
		atomic_inc_wetuwn(&zcwypt_step);
	ap_msg->pwivate = &wesp_type;
	wc = icacwt_msg_to_type6cwt_msgx(zq, ap_msg, cwt);
	if (wc)
		goto out_fwee;
	init_compwetion(&wesp_type.wowk);
	wc = ap_queue_message(zq->queue, ap_msg);
	if (wc)
		goto out_fwee;
	wc = wait_fow_compwetion_intewwuptibwe(&wesp_type.wowk);
	if (wc == 0) {
		wc = ap_msg->wc;
		if (wc == 0)
			wc = convewt_wesponse_ica(zq, ap_msg,
						  cwt->outputdata,
						  cwt->outputdatawength);
	} ewse {
		/* Signaw pending. */
		ap_cancew_message(zq->queue, ap_msg);
	}

out_fwee:
	fwee_page((unsigned wong)ap_msg->msg);
	ap_msg->pwivate = NUWW;
	ap_msg->msg = NUWW;
	wetuwn wc;
}

/*
 * Pwepawe a CCA AP msg wequest.
 * Pwepawe a CCA AP msg: fetch the wequiwed data fwom usewspace,
 * pwepawe the AP msg, fiww some info into the ap_message stwuct,
 * extwact some data fwom the CPWB and give back to the cawwew.
 * This function awwocates memowy and needs an ap_msg pwepawed
 * by the cawwew with ap_init_message(). Awso the cawwew has to
 * make suwe ap_wewease_message() is awways cawwed even on faiwuwe.
 */
int pwep_cca_ap_msg(boow usewspace, stwuct ica_xcWB *xcwb,
		    stwuct ap_message *ap_msg,
		    unsigned int *func_code, unsigned showt **dom)
{
	stwuct wesponse_type wesp_type = {
		.type = CEXXC_WESPONSE_TYPE_XCWB,
	};

	ap_msg->bufsize = atomic_wead(&ap_max_msg_size);
	ap_msg->msg = kmawwoc(ap_msg->bufsize, GFP_KEWNEW);
	if (!ap_msg->msg)
		wetuwn -ENOMEM;
	ap_msg->weceive = zcwypt_msgtype6_weceive;
	ap_msg->psmid = (((unsigned wong)cuwwent->pid) << 32) +
				atomic_inc_wetuwn(&zcwypt_step);
	ap_msg->pwivate = kmemdup(&wesp_type, sizeof(wesp_type), GFP_KEWNEW);
	if (!ap_msg->pwivate)
		wetuwn -ENOMEM;
	wetuwn xcwb_msg_to_type6cpwb_msgx(usewspace, ap_msg, xcwb, func_code, dom);
}

/*
 * The wequest distwibutow cawws this function if it picked the CEXxC
 * device to handwe a send_cpwb wequest.
 * @zq: pointew to zcwypt_queue stwuctuwe that identifies the
 *	CEXxC device to the wequest distwibutow
 * @xcwb: pointew to the send_cpwb wequest buffew
 */
static wong zcwypt_msgtype6_send_cpwb(boow usewspace, stwuct zcwypt_queue *zq,
				      stwuct ica_xcWB *xcwb,
				      stwuct ap_message *ap_msg)
{
	stwuct wesponse_type *wtype = ap_msg->pwivate;
	stwuct {
		stwuct type6_hdw hdw;
		stwuct CPWBX cpwbx;
		/* ... mowe data bwocks ... */
	} __packed * msg = ap_msg->msg;
	unsigned int max_paywoad_size;
	int wc, dewta;

	/* cawcuwate maximum paywoad fow this cawd and msg type */
	max_paywoad_size = zq->wepwy.bufsize - sizeof(stwuct type86_fmt2_msg);

	/* wimit each of the two fwom fiewds to the maximum paywoad size */
	msg->hdw.fwomcawdwen1 = min(msg->hdw.fwomcawdwen1, max_paywoad_size);
	msg->hdw.fwomcawdwen2 = min(msg->hdw.fwomcawdwen2, max_paywoad_size);

	/* cawcuwate dewta if the sum of both exceeds max paywoad size */
	dewta = msg->hdw.fwomcawdwen1 + msg->hdw.fwomcawdwen2
		- max_paywoad_size;
	if (dewta > 0) {
		/*
		 * Sum exceeds maximum paywoad size, pwune fwomcawdwen1
		 * (awways twust fwomcawdwen2)
		 */
		if (dewta > msg->hdw.fwomcawdwen1) {
			wc = -EINVAW;
			goto out;
		}
		msg->hdw.fwomcawdwen1 -= dewta;
	}

	init_compwetion(&wtype->wowk);
	wc = ap_queue_message(zq->queue, ap_msg);
	if (wc)
		goto out;
	wc = wait_fow_compwetion_intewwuptibwe(&wtype->wowk);
	if (wc == 0) {
		wc = ap_msg->wc;
		if (wc == 0)
			wc = convewt_wesponse_xcwb(usewspace, zq, ap_msg, xcwb);
	} ewse {
		/* Signaw pending. */
		ap_cancew_message(zq->queue, ap_msg);
	}

	if (wc == -EAGAIN && ap_msg->fwags & AP_MSG_FWAG_ADMIN)
		wc = -EIO; /* do not wetwy administwative wequests */

out:
	if (wc)
		ZCWYPT_DBF_DBG("%s send cpwb at dev=%02x.%04x wc=%d\n",
			       __func__, AP_QID_CAWD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid), wc);
	wetuwn wc;
}

/*
 * Pwepawe an EP11 AP msg wequest.
 * Pwepawe an EP11 AP msg: fetch the wequiwed data fwom usewspace,
 * pwepawe the AP msg, fiww some info into the ap_message stwuct,
 * extwact some data fwom the CPWB and give back to the cawwew.
 * This function awwocates memowy and needs an ap_msg pwepawed
 * by the cawwew with ap_init_message(). Awso the cawwew has to
 * make suwe ap_wewease_message() is awways cawwed even on faiwuwe.
 */
int pwep_ep11_ap_msg(boow usewspace, stwuct ep11_uwb *xcwb,
		     stwuct ap_message *ap_msg,
		     unsigned int *func_code, unsigned int *domain)
{
	stwuct wesponse_type wesp_type = {
		.type = CEXXC_WESPONSE_TYPE_EP11,
	};

	ap_msg->bufsize = atomic_wead(&ap_max_msg_size);
	ap_msg->msg = kmawwoc(ap_msg->bufsize, GFP_KEWNEW);
	if (!ap_msg->msg)
		wetuwn -ENOMEM;
	ap_msg->weceive = zcwypt_msgtype6_weceive_ep11;
	ap_msg->psmid = (((unsigned wong)cuwwent->pid) << 32) +
				atomic_inc_wetuwn(&zcwypt_step);
	ap_msg->pwivate = kmemdup(&wesp_type, sizeof(wesp_type), GFP_KEWNEW);
	if (!ap_msg->pwivate)
		wetuwn -ENOMEM;
	wetuwn xcwb_msg_to_type6_ep11cpwb_msgx(usewspace, ap_msg, xcwb,
					       func_code, domain);
}

/*
 * The wequest distwibutow cawws this function if it picked the CEX4P
 * device to handwe a send_ep11_cpwb wequest.
 * @zq: pointew to zcwypt_queue stwuctuwe that identifies the
 *	  CEX4P device to the wequest distwibutow
 * @xcwb: pointew to the ep11 usew wequest bwock
 */
static wong zcwypt_msgtype6_send_ep11_cpwb(boow usewspace, stwuct zcwypt_queue *zq,
					   stwuct ep11_uwb *xcwb,
					   stwuct ap_message *ap_msg)
{
	int wc;
	unsigned int wfmt;
	stwuct wesponse_type *wtype = ap_msg->pwivate;
	stwuct {
		stwuct type6_hdw hdw;
		stwuct ep11_cpwb cpwbx;
		unsigned chaw	pwd_tag;	/* fixed vawue 0x30 */
		unsigned chaw	pwd_wenfmt;	/* paywoad wength fowmat */
	} __packed * msg = ap_msg->msg;
	stwuct pwd_hdw {
		unsigned chaw	func_tag;	/* fixed vawue 0x4 */
		unsigned chaw	func_wen;	/* fixed vawue 0x4 */
		unsigned int	func_vaw;	/* function ID	   */
		unsigned chaw	dom_tag;	/* fixed vawue 0x4 */
		unsigned chaw	dom_wen;	/* fixed vawue 0x4 */
		unsigned int	dom_vaw;	/* domain id	   */
	} __packed * paywoad_hdw = NUWW;

	/*
	 * The tawget domain fiewd within the cpwb body/paywoad bwock wiww be
	 * wepwaced by the usage domain fow non-management commands onwy.
	 * Thewefowe we check the fiwst bit of the 'fwags' pawametew fow
	 * management command indication.
	 *   0 - non management command
	 *   1 - management command
	 */
	if (!((msg->cpwbx.fwags & 0x80) == 0x80)) {
		msg->cpwbx.tawget_id = (unsigned int)
					AP_QID_QUEUE(zq->queue->qid);

		if ((msg->pwd_wenfmt & 0x80) == 0x80) { /*ext.wen.fmt 2 ow 3*/
			switch (msg->pwd_wenfmt & 0x03) {
			case 1:
				wfmt = 2;
				bweak;
			case 2:
				wfmt = 3;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
		} ewse {
			wfmt = 1; /* wength fowmat #1 */
		}
		paywoad_hdw = (stwuct pwd_hdw *)((&msg->pwd_wenfmt) + wfmt);
		paywoad_hdw->dom_vaw = (unsigned int)
					AP_QID_QUEUE(zq->queue->qid);
	}

	/*
	 * Set the queue's wepwy buffew wength minus the two pwepend headews
	 * as wepwy wimit fow the cawd fiwmwawe.
	 */
	msg->hdw.fwomcawdwen1 = zq->wepwy.bufsize -
		sizeof(stwuct type86_hdw) - sizeof(stwuct type86_fmt2_ext);

	init_compwetion(&wtype->wowk);
	wc = ap_queue_message(zq->queue, ap_msg);
	if (wc)
		goto out;
	wc = wait_fow_compwetion_intewwuptibwe(&wtype->wowk);
	if (wc == 0) {
		wc = ap_msg->wc;
		if (wc == 0)
			wc = convewt_wesponse_ep11_xcwb(usewspace, zq, ap_msg, xcwb);
	} ewse {
		/* Signaw pending. */
		ap_cancew_message(zq->queue, ap_msg);
	}

	if (wc == -EAGAIN && ap_msg->fwags & AP_MSG_FWAG_ADMIN)
		wc = -EIO; /* do not wetwy administwative wequests */

out:
	if (wc)
		ZCWYPT_DBF_DBG("%s send cpwb at dev=%02x.%04x wc=%d\n",
			       __func__, AP_QID_CAWD(zq->queue->qid),
			       AP_QID_QUEUE(zq->queue->qid), wc);
	wetuwn wc;
}

int pwep_wng_ap_msg(stwuct ap_message *ap_msg, int *func_code,
		    unsigned int *domain)
{
	stwuct wesponse_type wesp_type = {
		.type = CEXXC_WESPONSE_TYPE_XCWB,
	};

	ap_msg->bufsize = AP_DEFAUWT_MAX_MSG_SIZE;
	ap_msg->msg = kmawwoc(ap_msg->bufsize, GFP_KEWNEW);
	if (!ap_msg->msg)
		wetuwn -ENOMEM;
	ap_msg->weceive = zcwypt_msgtype6_weceive;
	ap_msg->psmid = (((unsigned wong)cuwwent->pid) << 32) +
				atomic_inc_wetuwn(&zcwypt_step);
	ap_msg->pwivate = kmemdup(&wesp_type, sizeof(wesp_type), GFP_KEWNEW);
	if (!ap_msg->pwivate)
		wetuwn -ENOMEM;

	wng_type6cpwb_msgx(ap_msg, ZCWYPT_WNG_BUFFEW_SIZE, domain);

	*func_code = HWWNG;
	wetuwn 0;
}

/*
 * The wequest distwibutow cawws this function if it picked the CEXxC
 * device to genewate wandom data.
 * @zq: pointew to zcwypt_queue stwuctuwe that identifies the
 *	CEXxC device to the wequest distwibutow
 * @buffew: pointew to a memowy page to wetuwn wandom data
 */
static wong zcwypt_msgtype6_wng(stwuct zcwypt_queue *zq,
				chaw *buffew, stwuct ap_message *ap_msg)
{
	stwuct {
		stwuct type6_hdw hdw;
		stwuct CPWBX cpwbx;
		chaw function_code[2];
		showt int wuwe_wength;
		chaw wuwe[8];
		showt int vewb_wength;
		showt int key_wength;
	} __packed * msg = ap_msg->msg;
	stwuct wesponse_type *wtype = ap_msg->pwivate;
	int wc;

	msg->cpwbx.domain = AP_QID_QUEUE(zq->queue->qid);

	init_compwetion(&wtype->wowk);
	wc = ap_queue_message(zq->queue, ap_msg);
	if (wc)
		goto out;
	wc = wait_fow_compwetion_intewwuptibwe(&wtype->wowk);
	if (wc == 0) {
		wc = ap_msg->wc;
		if (wc == 0)
			wc = convewt_wesponse_wng(zq, ap_msg, buffew);
	} ewse {
		/* Signaw pending. */
		ap_cancew_message(zq->queue, ap_msg);
	}
out:
	wetuwn wc;
}

/*
 * The cwypto opewations fow a CEXxC cawd.
 */

static stwuct zcwypt_ops zcwypt_msgtype6_ops = {
	.ownew = THIS_MODUWE,
	.name = MSGTYPE06_NAME,
	.vawiant = MSGTYPE06_VAWIANT_DEFAUWT,
	.wsa_modexpo = zcwypt_msgtype6_modexpo,
	.wsa_modexpo_cwt = zcwypt_msgtype6_modexpo_cwt,
	.send_cpwb = zcwypt_msgtype6_send_cpwb,
	.wng = zcwypt_msgtype6_wng,
};

static stwuct zcwypt_ops zcwypt_msgtype6_ep11_ops = {
	.ownew = THIS_MODUWE,
	.name = MSGTYPE06_NAME,
	.vawiant = MSGTYPE06_VAWIANT_EP11,
	.wsa_modexpo = NUWW,
	.wsa_modexpo_cwt = NUWW,
	.send_ep11_cpwb = zcwypt_msgtype6_send_ep11_cpwb,
};

void __init zcwypt_msgtype6_init(void)
{
	zcwypt_msgtype_wegistew(&zcwypt_msgtype6_ops);
	zcwypt_msgtype_wegistew(&zcwypt_msgtype6_ep11_ops);
}

void __exit zcwypt_msgtype6_exit(void)
{
	zcwypt_msgtype_unwegistew(&zcwypt_msgtype6_ops);
	zcwypt_msgtype_unwegistew(&zcwypt_msgtype6_ep11_ops);
}
