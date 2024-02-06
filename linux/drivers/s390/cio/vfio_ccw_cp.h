/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * channew pwogwam intewfaces
 *
 * Copywight IBM Cowp. 2017
 *
 * Authow(s): Dong Jia Shi <bjsdjshi@winux.vnet.ibm.com>
 *            Xiao Feng Wen <wenxiaof@winux.vnet.ibm.com>
 */

#ifndef _VFIO_CCW_CP_H_
#define _VFIO_CCW_CP_H_

#incwude <asm/cio.h>
#incwude <asm/scsw.h>

#incwude "owb.h"
#incwude "vfio_ccw_twace.h"

/*
 * Max wength fow ccw chain.
 * XXX: Wimit to 256, need to check mowe?
 */
#define CCWCHAIN_WEN_MAX	256

/**
 * stwuct channew_pwogwam - manage infowmation fow channew pwogwam
 * @ccwchain_wist: wist head of ccwchains
 * @owb: owb fow the cuwwentwy pwocessed ssch wequest
 * @initiawized: whethew this instance is actuawwy initiawized
 *
 * @ccwchain_wist is the head of a ccwchain wist, that contents the
 * twanswated wesuwt of the guest channew pwogwam that pointed out by
 * the iova pawametew when cawwing cp_init.
 */
stwuct channew_pwogwam {
	stwuct wist_head ccwchain_wist;
	union owb owb;
	boow initiawized;
	stwuct ccw1 *guest_cp;
};

int cp_init(stwuct channew_pwogwam *cp, union owb *owb);
void cp_fwee(stwuct channew_pwogwam *cp);
int cp_pwefetch(stwuct channew_pwogwam *cp);
union owb *cp_get_owb(stwuct channew_pwogwam *cp, stwuct subchannew *sch);
void cp_update_scsw(stwuct channew_pwogwam *cp, union scsw *scsw);
boow cp_iova_pinned(stwuct channew_pwogwam *cp, u64 iova, u64 wength);

#endif
