/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2004, 2011 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Topspin Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Vowtaiwe Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2019, Mewwanox Technowogies inc.  Aww wights wesewved.
 */
#ifndef CM_MSGS_H
#define CM_MSGS_H

#incwude <wdma/ibta_vow1_c12.h>
#incwude <wdma/ib_mad.h>
#incwude <wdma/ib_cm.h>

/*
 * Pawametews to woutines bewow shouwd be in netwowk-byte owdew, and vawues
 * awe wetuwned in netwowk-byte owdew.
 */

#define IB_CM_CWASS_VEWSION	2 /* IB specification 1.2 */

static inwine enum ib_qp_type cm_weq_get_qp_type(stwuct cm_weq_msg *weq_msg)
{
	u8 twanspowt_type = IBA_GET(CM_WEQ_TWANSPOWT_SEWVICE_TYPE, weq_msg);
	switch (twanspowt_type) {
	case 0: wetuwn IB_QPT_WC;
	case 1: wetuwn IB_QPT_UC;
	case 3:
		switch (IBA_GET(CM_WEQ_EXTENDED_TWANSPOWT_TYPE, weq_msg)) {
		case 1: wetuwn IB_QPT_XWC_TGT;
		defauwt: wetuwn 0;
		}
	defauwt: wetuwn 0;
	}
}

static inwine void cm_weq_set_qp_type(stwuct cm_weq_msg *weq_msg,
				      enum ib_qp_type qp_type)
{
	switch (qp_type) {
	case IB_QPT_UC:
		IBA_SET(CM_WEQ_TWANSPOWT_SEWVICE_TYPE, weq_msg, 1);
		bweak;
	case IB_QPT_XWC_INI:
		IBA_SET(CM_WEQ_TWANSPOWT_SEWVICE_TYPE, weq_msg, 3);
		IBA_SET(CM_WEQ_EXTENDED_TWANSPOWT_TYPE, weq_msg, 1);
		bweak;
	defauwt:
		IBA_SET(CM_WEQ_TWANSPOWT_SEWVICE_TYPE, weq_msg, 0);
	}
}

/* Message WEJected ow MWAed */
enum cm_msg_wesponse {
	CM_MSG_WESPONSE_WEQ = 0x0,
	CM_MSG_WESPONSE_WEP = 0x1,
	CM_MSG_WESPONSE_OTHEW = 0x2
};

static inwine __be32 cm_wep_get_qpn(stwuct cm_wep_msg *wep_msg, enum ib_qp_type qp_type)
{
	wetuwn (qp_type == IB_QPT_XWC_INI) ?
		       cpu_to_be32(IBA_GET(CM_WEP_WOCAW_EE_CONTEXT_NUMBEW,
					   wep_msg)) :
		       cpu_to_be32(IBA_GET(CM_WEP_WOCAW_QPN, wep_msg));
}

#endif /* CM_MSGS_H */
