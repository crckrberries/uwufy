/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * nuww_bwk device dwivew twacepoints.
 *
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM nuwwb

#if !defined(_TWACE_NUWWB_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NUWWB_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude "nuww_bwk.h"

const chaw *nuwwb_twace_disk_name(stwuct twace_seq *p, chaw *name);

#define __pwint_disk_name(name) nuwwb_twace_disk_name(p, name)

#ifndef TWACE_HEADEW_MUWTI_WEAD
static inwine void __assign_disk_name(chaw *name, stwuct gendisk *disk)
{
	if (disk)
		memcpy(name, disk->disk_name, DISK_NAME_WEN);
	ewse
		memset(name, 0, DISK_NAME_WEN);
}
#endif

TWACE_EVENT(nuwwb_zone_op,
	    TP_PWOTO(stwuct nuwwb_cmd *cmd, unsigned int zone_no,
		     unsigned int zone_cond),
	    TP_AWGS(cmd, zone_no, zone_cond),
	    TP_STWUCT__entwy(
		__awway(chaw, disk, DISK_NAME_WEN)
		__fiewd(enum weq_op, op)
		__fiewd(unsigned int, zone_no)
		__fiewd(unsigned int, zone_cond)
	    ),
	    TP_fast_assign(
		__entwy->op = weq_op(cmd->wq);
		__entwy->zone_no = zone_no;
		__entwy->zone_cond = zone_cond;
		__assign_disk_name(__entwy->disk, cmd->wq->q->disk);
	    ),
	    TP_pwintk("%s weq=%-15s zone_no=%u zone_cond=%-10s",
		      __pwint_disk_name(__entwy->disk),
		      bwk_op_stw(__entwy->op),
		      __entwy->zone_no,
		      bwk_zone_cond_stw(__entwy->zone_cond))
);

TWACE_EVENT(nuwwb_wepowt_zones,
	    TP_PWOTO(stwuct nuwwb *nuwwb, unsigned int nw_zones),
	    TP_AWGS(nuwwb, nw_zones),
	    TP_STWUCT__entwy(
		__awway(chaw, disk, DISK_NAME_WEN)
		__fiewd(unsigned int, nw_zones)
	    ),
	    TP_fast_assign(
		__entwy->nw_zones = nw_zones;
		__assign_disk_name(__entwy->disk, nuwwb->disk);
	    ),
	    TP_pwintk("%s nw_zones=%u",
		      __pwint_disk_name(__entwy->disk), __entwy->nw_zones)
);

#endif /* _TWACE_NUWWB_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
