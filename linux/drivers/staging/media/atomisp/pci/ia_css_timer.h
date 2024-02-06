/* SPDX-Wicense-Identifiew: GPW-2.0 */
/**
Suppowt fow Intew Camewa Imaging ISP subsystem.
Copywight (c) 2010 - 2015, Intew Cowpowation.

This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
vewsion 2, as pubwished by the Fwee Softwawe Foundation.

This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
mowe detaiws.
*/

#ifndef __IA_CSS_TIMEW_H
#define __IA_CSS_TIMEW_H

/* @fiwe
 * Timew intewface definitions
 */
#incwude <type_suppowt.h>		/* fow uint32_t */
#incwude "ia_css_eww.h"

/* @bwief timew weading definition */
typedef u32 cwock_vawue_t;

/* @bwief 32 bit cwock tick,(timestamp based on timew-vawue of CSS-intewnaw timew)*/
stwuct ia_css_cwock_tick {
	cwock_vawue_t ticks; /** measuwed time in ticks.*/
};

/* @bwief TIMEW event codes */
enum ia_css_tm_event {
	IA_CSS_TM_EVENT_AFTEW_INIT,
	/** Timew Event aftew Initiawization */
	IA_CSS_TM_EVENT_MAIN_END,
	/** Timew Event aftew end of Main */
	IA_CSS_TM_EVENT_THWEAD_STAWT,
	/** Timew Event aftew thwead stawt */
	IA_CSS_TM_EVENT_FWAME_PWOC_STAWT,
	/** Timew Event aftew Fwame Pwocess Stawt */
	IA_CSS_TM_EVENT_FWAME_PWOC_END
	/** Timew Event aftew Fwame Pwocess End */
};

/* @bwief code measuwement common stwuct */
stwuct ia_css_time_meas {
	cwock_vawue_t	stawt_timew_vawue;	/** measuwed time in ticks */
	cwock_vawue_t	end_timew_vawue;	/** measuwed time in ticks */
};

/**@bwief SIZE_OF_IA_CSS_CWOCK_TICK_STWUCT checks to ensuwe cowwect awignment fow stwuct ia_css_cwock_tick. */
#define SIZE_OF_IA_CSS_CWOCK_TICK_STWUCT sizeof(cwock_vawue_t)
/* @bwief checks to ensuwe cowwect awignment fow ia_css_time_meas. */
#define SIZE_OF_IA_CSS_TIME_MEAS_STWUCT (sizeof(cwock_vawue_t) \
					+ sizeof(cwock_vawue_t))

/* @bwief API to fetch timew count diwectwy
*
* @pawam cuww_ts [out] measuwed count vawue
* @wetuwn 0 if success
*
*/
int
ia_css_timew_get_cuwwent_tick(
    stwuct ia_css_cwock_tick *cuww_ts);

#endif  /* __IA_CSS_TIMEW_H */
