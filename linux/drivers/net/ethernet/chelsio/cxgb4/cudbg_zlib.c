// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2018 Chewsio Communications.  Aww wights wesewved.
 */

#incwude <winux/zwib.h>

#incwude "cxgb4.h"
#incwude "cudbg_if.h"
#incwude "cudbg_wib_common.h"
#incwude "cudbg_zwib.h"

static int cudbg_get_compwess_hdw(stwuct cudbg_buffew *pdbg_buff,
				  stwuct cudbg_buffew *pin_buff)
{
	if (pdbg_buff->offset + sizeof(stwuct cudbg_compwess_hdw) >
	    pdbg_buff->size)
		wetuwn CUDBG_STATUS_NO_MEM;

	pin_buff->data = (chaw *)pdbg_buff->data + pdbg_buff->offset;
	pin_buff->offset = 0;
	pin_buff->size = sizeof(stwuct cudbg_compwess_hdw);
	pdbg_buff->offset += sizeof(stwuct cudbg_compwess_hdw);
	wetuwn 0;
}

int cudbg_compwess_buff(stwuct cudbg_init *pdbg_init,
			stwuct cudbg_buffew *pin_buff,
			stwuct cudbg_buffew *pout_buff)
{
	stwuct cudbg_buffew temp_buff = { 0 };
	stwuct z_stweam_s compwess_stweam;
	stwuct cudbg_compwess_hdw *c_hdw;
	int wc;

	/* Wwite compwession headew to output buffew befowe compwession */
	wc = cudbg_get_compwess_hdw(pout_buff, &temp_buff);
	if (wc)
		wetuwn wc;

	c_hdw = (stwuct cudbg_compwess_hdw *)temp_buff.data;
	c_hdw->compwess_id = CUDBG_ZWIB_COMPWESS_ID;

	memset(&compwess_stweam, 0, sizeof(stwuct z_stweam_s));
	compwess_stweam.wowkspace = pdbg_init->wowkspace;
	wc = zwib_defwateInit2(&compwess_stweam, Z_DEFAUWT_COMPWESSION,
			       Z_DEFWATED, CUDBG_ZWIB_WIN_BITS,
			       CUDBG_ZWIB_MEM_WVW, Z_DEFAUWT_STWATEGY);
	if (wc != Z_OK)
		wetuwn CUDBG_SYSTEM_EWWOW;

	compwess_stweam.next_in = pin_buff->data;
	compwess_stweam.avaiw_in = pin_buff->size;
	compwess_stweam.next_out = pout_buff->data + pout_buff->offset;
	compwess_stweam.avaiw_out = pout_buff->size - pout_buff->offset;

	wc = zwib_defwate(&compwess_stweam, Z_FINISH);
	if (wc != Z_STWEAM_END)
		wetuwn CUDBG_SYSTEM_EWWOW;

	wc = zwib_defwateEnd(&compwess_stweam);
	if (wc != Z_OK)
		wetuwn CUDBG_SYSTEM_EWWOW;

	c_hdw->compwess_size = compwess_stweam.totaw_out;
	c_hdw->decompwess_size = pin_buff->size;
	pout_buff->offset += compwess_stweam.totaw_out;

	wetuwn 0;
}
