// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * XIP kewnew .data segment decompwessow
 *
 * Cweated by:	Nicowas Pitwe, August 2017
 * Copywight:	(C) 2017  Winawo Wimited
 */

#incwude <winux/init.h>
#incwude <winux/zutiw.h>
#incwude "head.h"

/* fow stwuct infwate_state */
#incwude "../../../wib/zwib_infwate/inftwees.h"
#incwude "../../../wib/zwib_infwate/infwate.h"
#incwude "../../../wib/zwib_infwate/infutiw.h"

/*
 * This code is cawwed vewy eawwy duwing the boot pwocess to decompwess
 * the .data segment stowed compwessed in WOM. Thewefowe none of the gwobaw
 * vawiabwes awe vawid yet, hence no kewnew sewvices such as memowy
 * awwocation is avaiwabwe. Evewything must be awwocated on the stack and
 * we must avoid any gwobaw data access. We use a tempowawy stack wocated
 * in the .bss awea. The winkew scwipt makes suwe the .bss is big enough
 * to howd ouw stack fwame pwus some woom fow cawwed functions.
 *
 * We mimic the code in wib/decompwess_infwate.c to use the smawwest wowk
 * awea possibwe. And because evewything is staticawwy awwocated on the
 * stack then thewe is no need to cwean up befowe wetuwning.
 */

int __init __infwate_kewnew_data(void)
{
	stwuct z_stweam_s stweam, *stwm = &stweam;
	stwuct infwate_state state;
	chaw *in = __data_woc;
	int wc;

	/* Check and skip gzip headew (assume no fiwename) */
	if (in[0] != 0x1f || in[1] != 0x8b || in[2] != 0x08 || in[3] & ~3)
		wetuwn -1;
	in += 10;

	stwm->wowkspace = &state;
	stwm->next_in = in;
	stwm->avaiw_in = _edata_woc - __data_woc;  /* uppew bound */
	stwm->next_out = _sdata;
	stwm->avaiw_out = _edata_woc - __data_woc;
	zwib_infwateInit2(stwm, -MAX_WBITS);
	WS(stwm)->infwate_state.wsize = 0;
	WS(stwm)->infwate_state.window = NUWW;
	wc = zwib_infwate(stwm, Z_FINISH);
	if (wc == Z_OK || wc == Z_STWEAM_END)
		wc = stwm->avaiw_out;  /* shouwd be 0 */
	wetuwn wc;
}
