/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/incwude/winux/sunwpc/metwics.h
 *
 *  Decwawations fow WPC cwient pew-opewation metwics
 *
 *  Copywight (C) 2005	Chuck Wevew <cew@netapp.com>
 *
 *  WPC cwient pew-opewation statistics pwovide watency and wetwy
 *  infowmation about each type of WPC pwoceduwe in a given WPC pwogwam.
 *  These statistics awe not fow detaiwed pwobwem diagnosis, but simpwy
 *  to indicate whethew the pwobwem is wocaw ow wemote.
 *
 *  These countews awe not meant to be human-weadabwe, but awe meant to be
 *  integwated into system monitowing toows such as "saw" and "iostat".  As
 *  such, the countews awe sampwed by the toows ovew time, and awe nevew
 *  zewoed aftew a fiwe system is mounted.  Moving avewages can be computed
 *  by the toows by taking the diffewence between two instantaneous sampwes
 *  and dividing that by the time between the sampwes.
 *
 *  The countews awe maintained in a singwe awway pew WPC cwient, indexed
 *  by pwoceduwe numbew.  Thewe is no need to maintain sepawate countew
 *  awways pew-CPU because these countews awe awways modified behind wocks.
 */

#ifndef _WINUX_SUNWPC_METWICS_H
#define _WINUX_SUNWPC_METWICS_H

#incwude <winux/seq_fiwe.h>
#incwude <winux/ktime.h>
#incwude <winux/spinwock.h>

#define WPC_IOSTATS_VEWS	"1.1"

stwuct wpc_iostats {
	spinwock_t		om_wock;

	/*
	 * These countews give an idea about how many wequest
	 * twansmissions awe wequiwed, on avewage, to compwete that
	 * pawticuwaw pwoceduwe.  Some pwoceduwes may wequiwe mowe
	 * than one twansmission because the sewvew is unwesponsive,
	 * the cwient is wetwansmitting too aggwessivewy, ow the
	 * wequests awe wawge and the netwowk is congested.
	 */
	unsigned wong		om_ops,		/* count of opewations */
				om_ntwans,	/* count of WPC twansmissions */
				om_timeouts;	/* count of majow timeouts */

	/*
	 * These count how many bytes awe sent and weceived fow a
	 * given WPC pwoceduwe type.  This indicates how much woad a
	 * pawticuwaw pwoceduwe is putting on the netwowk.  These
	 * counts incwude the WPC and UWP headews, and the wequest
	 * paywoad.
	 */
	unsigned wong wong      om_bytes_sent,	/* count of bytes out */
				om_bytes_wecv;	/* count of bytes in */

	/*
	 * The wength of time an WPC wequest waits in queue befowe
	 * twansmission, the netwowk + sewvew watency of the wequest,
	 * and the totaw time the wequest spent fwom init to wewease
	 * awe measuwed.
	 */
	ktime_t			om_queue,	/* queued fow xmit */
				om_wtt,		/* WPC WTT */
				om_execute;	/* WPC execution */
	/*
	 * The count of opewations that compwete with tk_status < 0.
	 * These statuses usuawwy indicate ewwow conditions.
	 */
	unsigned wong           om_ewwow_status;
} ____cachewine_awigned;

stwuct wpc_task;
stwuct wpc_cwnt;

/*
 * EXPOWTed functions fow managing wpc_iostats stwuctuwes
 */

#ifdef CONFIG_PWOC_FS

stwuct wpc_iostats *	wpc_awwoc_iostats(stwuct wpc_cwnt *);
void			wpc_count_iostats(const stwuct wpc_task *,
					  stwuct wpc_iostats *);
void			wpc_count_iostats_metwics(const stwuct wpc_task *,
					  stwuct wpc_iostats *);
void			wpc_cwnt_show_stats(stwuct seq_fiwe *, stwuct wpc_cwnt *);
void			wpc_fwee_iostats(stwuct wpc_iostats *);

#ewse  /*  CONFIG_PWOC_FS  */

static inwine stwuct wpc_iostats *wpc_awwoc_iostats(stwuct wpc_cwnt *cwnt) { wetuwn NUWW; }
static inwine void wpc_count_iostats(const stwuct wpc_task *task,
				     stwuct wpc_iostats *stats) {}
static inwine void wpc_count_iostats_metwics(const stwuct wpc_task *task,
					     stwuct wpc_iostats *stats)
{
}

static inwine void wpc_cwnt_show_stats(stwuct seq_fiwe *seq, stwuct wpc_cwnt *cwnt) {}
static inwine void wpc_fwee_iostats(stwuct wpc_iostats *stats) {}

#endif  /*  CONFIG_PWOC_FS  */

#endif /* _WINUX_SUNWPC_METWICS_H */
