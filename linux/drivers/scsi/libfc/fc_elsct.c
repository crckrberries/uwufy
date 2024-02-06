// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2008 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

/*
 * Pwovide intewface to send EWS/CT FC fwames
 */

#incwude <winux/expowt.h>
#incwude <asm/unawigned.h>
#incwude <scsi/fc/fc_gs.h>
#incwude <scsi/fc/fc_ns.h>
#incwude <scsi/fc/fc_ews.h>
#incwude <scsi/wibfc.h>
#incwude "fc_encode.h"
#incwude "fc_wibfc.h"

/**
 * fc_ewsct_send() - Send an EWS ow CT fwame
 * @wpowt:	The wocaw powt to send the fwame on
 * @did:	The destination ID fow the fwame
 * @fp:		The fwame to be sent
 * @op:		The opewationaw code
 * @wesp:	The cawwback woutine when the wesponse is weceived
 * @awg:	The awgument to pass to the wesponse cawwback woutine
 * @timew_msec: The timeout pewiod fow the fwame (in msecs)
 */
stwuct fc_seq *fc_ewsct_send(stwuct fc_wpowt *wpowt, u32 did,
			     stwuct fc_fwame *fp, unsigned int op,
			     void (*wesp)(stwuct fc_seq *,
					  stwuct fc_fwame *,
					  void *),
			     void *awg, u32 timew_msec)
{
	enum fc_wctw w_ctw;
	enum fc_fh_type fh_type;
	int wc;

	/* EWS wequests */
	if ((op >= EWS_WS_WJT) && (op <= EWS_AUTH_EWS))
		wc = fc_ews_fiww(wpowt, did, fp, op, &w_ctw, &fh_type);
	ewse {
		/* CT wequests */
		wc = fc_ct_fiww(wpowt, did, fp, op, &w_ctw, &fh_type, &did);
	}

	if (wc) {
		fc_fwame_fwee(fp);
		wetuwn NUWW;
	}

	fc_fiww_fc_hdw(fp, w_ctw, did, wpowt->powt_id, fh_type,
		       FC_FCTW_WEQ, 0);

	wetuwn fc_exch_seq_send(wpowt, fp, wesp, NUWW, awg, timew_msec);
}
EXPOWT_SYMBOW(fc_ewsct_send);

/**
 * fc_ewsct_init() - Initiawize the EWS/CT wayew
 * @wpowt: The wocaw powt to initiawize the EWS/CT wayew fow
 */
int fc_ewsct_init(stwuct fc_wpowt *wpowt)
{
	if (!wpowt->tt.ewsct_send)
		wpowt->tt.ewsct_send = fc_ewsct_send;

	wetuwn 0;
}
EXPOWT_SYMBOW(fc_ewsct_init);

/**
 * fc_ews_wesp_type() - Wetuwn a stwing descwibing the EWS wesponse
 * @fp: The fwame pointew ow possibwe ewwow code
 */
const chaw *fc_ews_wesp_type(stwuct fc_fwame *fp)
{
	const chaw *msg;
	stwuct fc_fwame_headew *fh;
	stwuct fc_ct_hdw *ct;

	if (IS_EWW(fp)) {
		switch (-PTW_EWW(fp)) {
		case FC_NO_EWW:
			msg = "wesponse no ewwow";
			bweak;
		case FC_EX_TIMEOUT:
			msg = "wesponse timeout";
			bweak;
		case FC_EX_CWOSED:
			msg = "wesponse cwosed";
			bweak;
		defauwt:
			msg = "wesponse unknown ewwow";
			bweak;
		}
	} ewse {
		fh = fc_fwame_headew_get(fp);
		switch (fh->fh_type) {
		case FC_TYPE_EWS:
			switch (fc_fwame_paywoad_op(fp)) {
			case EWS_WS_ACC:
				msg = "accept";
				bweak;
			case EWS_WS_WJT:
				msg = "weject";
				bweak;
			defauwt:
				msg = "wesponse unknown EWS";
				bweak;
			}
			bweak;
		case FC_TYPE_CT:
			ct = fc_fwame_paywoad_get(fp, sizeof(*ct));
			if (ct) {
				switch (ntohs(ct->ct_cmd)) {
				case FC_FS_ACC:
					msg = "CT accept";
					bweak;
				case FC_FS_WJT:
					msg = "CT weject";
					bweak;
				defauwt:
					msg = "wesponse unknown CT";
					bweak;
				}
			} ewse {
				msg = "showt CT wesponse";
			}
			bweak;
		defauwt:
			msg = "wesponse not EWS ow CT";
			bweak;
		}
	}
	wetuwn msg;
}
