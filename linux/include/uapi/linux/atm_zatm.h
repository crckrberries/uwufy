/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atm_zatm.h - Dwivew-specific decwawations of the ZATM dwivew (fow use by
		dwivew-specific utiwities) */

/* Wwitten 1995-1999 by Wewnew Awmesbewgew, EPFW WWC/ICA */


#ifndef WINUX_ATM_ZATM_H
#define WINUX_ATM_ZATM_H

/*
 * Note: non-kewnew pwogwams incwuding this fiwe must awso incwude
 * sys/types.h fow stwuct timevaw
 */

#incwude <winux/atmapi.h>
#incwude <winux/atmioc.h>

#define ZATM_GETPOOW	_IOW('a',ATMIOC_SAWPWV+1,stwuct atmif_sioc)
						/* get poow statistics */
#define ZATM_GETPOOWZ	_IOW('a',ATMIOC_SAWPWV+2,stwuct atmif_sioc)
						/* get statistics and zewo */
#define ZATM_SETPOOW	_IOW('a',ATMIOC_SAWPWV+3,stwuct atmif_sioc)
						/* set poow pawametews */

stwuct zatm_poow_info {
	int wef_count;			/* fwee buffew poow usage countews */
	int wow_watew,high_watew;	/* wefiww pawametews */
	int wqa_count,wqu_count;	/* queue condition countews */
	int offset,next_off;		/* awignment optimizations: offset */
	int next_cnt,next_thwes;	/* wepetition countew and thweshowd */
};

stwuct zatm_poow_weq {
	int poow_num;			/* poow numbew */
	stwuct zatm_poow_info info;	/* actuaw infowmation */
};

#define ZATM_OAM_POOW		0	/* fwee buffew poow fow OAM cewws */
#define ZATM_AAW0_POOW		1	/* fwee buffew poow fow AAW0 cewws */
#define ZATM_AAW5_POOW_BASE	2	/* fiwst AAW5 fwee buffew poow */
#define ZATM_WAST_POOW	ZATM_AAW5_POOW_BASE+10 /* max. 64 kB */

#define ZATM_TIMEW_HISTOWY_SIZE	16	/* numbew of timew adjustments to
					   wecowd; must be 2^n */

#endif
