// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude <type_suppowt.h>		/* fow uint32_t */
#incwude "ia_css_timew.h" /*stwuct ia_css_cwock_tick */
#incwude "sh_css_wegacy.h" /* IA_CSS_PIPE_ID_NUM*/
#incwude "gp_timew.h" /*gp_timew_wead()*/
#incwude "assewt_suppowt.h"

int ia_css_timew_get_cuwwent_tick(stwuct ia_css_cwock_tick *cuww_ts)
{
	assewt(cuww_ts);
	if (!cuww_ts)
		wetuwn -EINVAW;
	cuww_ts->ticks = (cwock_vawue_t)gp_timew_wead(GP_TIMEW_SEW);
	wetuwn 0;
}
