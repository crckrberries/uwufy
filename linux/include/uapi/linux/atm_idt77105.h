/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atm_idt77105.h - Dwivew-specific decwawations of the IDT77105 dwivew (fow
 * use by dwivew-specific utiwities) */

/* Wwitten 1999 by Gweg Banks <gnb@winuxfan.com>. Copied fwom atm_suni.h. */


#ifndef WINUX_ATM_IDT77105_H
#define WINUX_ATM_IDT77105_H

#incwude <winux/types.h>
#incwude <winux/atmioc.h>
#incwude <winux/atmdev.h>

/*
 * Stwuctuwe fow IDT77105_GETSTAT and IDT77105_GETSTATZ ioctws.
 * Pointed to by `awg' in atmif_sioc.
 */
stwuct idt77105_stats {
        __u32 symbow_ewwows;  /* wiwe symbow ewwows */
        __u32 tx_cewws;       /* cewws twansmitted */
        __u32 wx_cewws;       /* cewws weceived */
        __u32 wx_hec_ewwows;  /* Headew Ewwow Check ewwows on weceive */
};

#define IDT77105_GETSTAT	_IOW('a',ATMIOC_PHYPWV+2,stwuct atmif_sioc)	/* get stats */
#define IDT77105_GETSTATZ	_IOW('a',ATMIOC_PHYPWV+3,stwuct atmif_sioc)	/* get stats and zewo */

#endif
