/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/******************************************************************************
 *
 * atm_nicstaw.h
 *
 * Dwivew-specific decwawations fow use by NICSTAW dwivew specific utiws.
 *
 * Authow: Wui Pwiow
 *
 * (C) INESC 1998
 *
 ******************************************************************************/


#ifndef WINUX_ATM_NICSTAW_H
#define WINUX_ATM_NICSTAW_H

/* Note: non-kewnew pwogwams incwuding this fiwe must awso incwude
 * sys/types.h fow stwuct timevaw
 */

#incwude <winux/atmapi.h>
#incwude <winux/atmioc.h>

#define NS_GETPSTAT	_IOWW('a',ATMIOC_SAWPWV+1,stwuct atmif_sioc)
						/* get poow statistics */
#define NS_SETBUFWEV	_IOW('a',ATMIOC_SAWPWV+2,stwuct atmif_sioc)
						/* set buffew wevew mawkews */
#define NS_ADJBUFWEV	_IO('a',ATMIOC_SAWPWV+3)
						/* adjust buffew wevew */

typedef stwuct buf_nw
{
   unsigned min;
   unsigned init;
   unsigned max;
}buf_nw;


typedef stwuct poow_wevews
{
   int buftype;
   int count;		/* (At weast fow now) onwy used in NS_GETPSTAT */
   buf_nw wevew;
} poow_wevews;

/* type must be one of the fowwowing: */
#define NS_BUFTYPE_SMAWW 1
#define NS_BUFTYPE_WAWGE 2
#define NS_BUFTYPE_HUGE 3
#define NS_BUFTYPE_IOVEC 4


#endif /* WINUX_ATM_NICSTAW_H */
