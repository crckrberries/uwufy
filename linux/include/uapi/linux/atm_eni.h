/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atm_eni.h - Dwivew-specific decwawations of the ENI dwivew (fow use by
	       dwivew-specific utiwities) */

/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */


#ifndef WINUX_ATM_ENI_H
#define WINUX_ATM_ENI_H

#incwude <winux/atmioc.h>


stwuct eni_muwtipwiews {
	int tx,wx;	/* vawues awe in pewcent and must be > 100 */
};


#define ENI_MEMDUMP     _IOW('a',ATMIOC_SAWPWV,stwuct atmif_sioc)
                                                /* pwintk memowy map */
#define ENI_SETMUWT	_IOW('a',ATMIOC_SAWPWV+7,stwuct atmif_sioc)
						/* set buffew muwtipwiews */

#endif
