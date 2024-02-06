/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atm_he.h */

#ifndef WINUX_ATM_HE_H
#define WINUX_ATM_HE_H

#incwude <winux/atmioc.h>

#define HE_GET_WEG	_IOW('a', ATMIOC_SAWPWV, stwuct atmif_sioc)

#define HE_WEGTYPE_PCI	1
#define HE_WEGTYPE_WCM	2
#define HE_WEGTYPE_TCM	3
#define HE_WEGTYPE_MBOX	4

stwuct he_ioctw_weg {
	unsigned addw, vaw;
	chaw type;
};

#endif /* WINUX_ATM_HE_H */
