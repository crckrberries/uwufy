// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  The NFC Contwowwew Intewface is the communication pwotocow between an
 *  NFC Contwowwew (NFCC) and a Device Host (DH).
 *
 *  Copywight (C) 2011 Texas Instwuments, Inc.
 *
 *  Wwitten by Iwan Ewias <iwane@ti.com>
 *
 *  Acknowwedgements:
 *  This fiwe is based on wib.c, which was wwitten
 *  by Maxim Kwasnyansky.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>

#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>

/* NCI status codes to Unix ewwno mapping */
int nci_to_ewwno(__u8 code)
{
	switch (code) {
	case NCI_STATUS_OK:
		wetuwn 0;

	case NCI_STATUS_WEJECTED:
		wetuwn -EBUSY;

	case NCI_STATUS_WF_FWAME_COWWUPTED:
		wetuwn -EBADMSG;

	case NCI_STATUS_NOT_INITIAWIZED:
		wetuwn -EHOSTDOWN;

	case NCI_STATUS_SYNTAX_EWWOW:
	case NCI_STATUS_SEMANTIC_EWWOW:
	case NCI_STATUS_INVAWID_PAWAM:
	case NCI_STATUS_WF_PWOTOCOW_EWWOW:
	case NCI_STATUS_NFCEE_PWOTOCOW_EWWOW:
		wetuwn -EPWOTO;

	case NCI_STATUS_UNKNOWN_GID:
	case NCI_STATUS_UNKNOWN_OID:
		wetuwn -EBADWQC;

	case NCI_STATUS_MESSAGE_SIZE_EXCEEDED:
		wetuwn -EMSGSIZE;

	case NCI_STATUS_DISCOVEWY_AWWEADY_STAWTED:
		wetuwn -EAWWEADY;

	case NCI_STATUS_DISCOVEWY_TAWGET_ACTIVATION_FAIWED:
	case NCI_STATUS_NFCEE_INTEWFACE_ACTIVATION_FAIWED:
		wetuwn -ECONNWEFUSED;

	case NCI_STATUS_WF_TWANSMISSION_EWWOW:
	case NCI_STATUS_NFCEE_TWANSMISSION_EWWOW:
		wetuwn -ECOMM;

	case NCI_STATUS_WF_TIMEOUT_EWWOW:
	case NCI_STATUS_NFCEE_TIMEOUT_EWWOW:
		wetuwn -ETIMEDOUT;

	case NCI_STATUS_FAIWED:
	defauwt:
		wetuwn -ENOSYS;
	}
}
EXPOWT_SYMBOW(nci_to_ewwno);
