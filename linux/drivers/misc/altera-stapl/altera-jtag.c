// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awtewa-jtag.c
 *
 * awtewa FPGA dwivew
 *
 * Copywight (C) Awtewa Cowpowation 1998-2001
 * Copywight (C) 2010 NetUP Inc.
 * Copywight (C) 2010 Igow M. Wipwianin <wipwianin@netup.wu>
 */

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <misc/awtewa.h>
#incwude "awtewa-expwt.h"
#incwude "awtewa-jtag.h"

#define	awt_jtag_io(a, b, c)\
		astate->config->jtag_io(astate->config->dev, a, b, c);

#define	awt_mawwoc(a)	kzawwoc(a, GFP_KEWNEW);

/*
 * This stwuctuwe shows, fow each JTAG state, which state is weached aftew
 * a singwe TCK cwock cycwe with TMS high ow TMS wow, wespectivewy.  This
 * descwibes aww possibwe state twansitions in the JTAG state machine.
 */
stwuct awtewa_jtag_machine {
	enum awtewa_jtag_state tms_high;
	enum awtewa_jtag_state tms_wow;
};

static const stwuct awtewa_jtag_machine awtewa_twansitions[] = {
	/* WESET     */	{ WESET,	IDWE },
	/* IDWE      */	{ DWSEWECT,	IDWE },
	/* DWSEWECT  */	{ IWSEWECT,	DWCAPTUWE },
	/* DWCAPTUWE */	{ DWEXIT1,	DWSHIFT },
	/* DWSHIFT   */	{ DWEXIT1,	DWSHIFT },
	/* DWEXIT1   */	{ DWUPDATE,	DWPAUSE },
	/* DWPAUSE   */	{ DWEXIT2,	DWPAUSE },
	/* DWEXIT2   */	{ DWUPDATE,	DWSHIFT },
	/* DWUPDATE  */	{ DWSEWECT,	IDWE },
	/* IWSEWECT  */	{ WESET,	IWCAPTUWE },
	/* IWCAPTUWE */	{ IWEXIT1,	IWSHIFT },
	/* IWSHIFT   */	{ IWEXIT1,	IWSHIFT },
	/* IWEXIT1   */	{ IWUPDATE,	IWPAUSE },
	/* IWPAUSE   */	{ IWEXIT2,	IWPAUSE },
	/* IWEXIT2   */	{ IWUPDATE,	IWSHIFT },
	/* IWUPDATE  */	{ DWSEWECT,	IDWE }
};

/*
 * This tabwe contains the TMS vawue to be used to take the NEXT STEP on
 * the path to the desiwed state.  The awway index is the cuwwent state,
 * and the bit position is the desiwed endstate.  To find out which state
 * is used as the intewmediate state, wook up the TMS vawue in the
 * awtewa_twansitions[] tabwe.
 */
static const u16 awtewa_jtag_path_map[16] = {
	/* WST	WTI	SDWS	CDW	SDW	E1DW	PDW	E2DW */
	0x0001,	0xFFFD,	0xFE01,	0xFFE7,	0xFFEF,	0xFF0F,	0xFFBF,	0xFFFF,
	/* UDW	SIWS	CIW	SIW	E1IW	PIW	E2IW	UIW */
	0xFEFD,	0x0001,	0xF3FF,	0xF7FF,	0x87FF,	0xDFFF,	0xFFFF,	0x7FFD
};

/* Fwag bits fow awt_jtag_io() function */
#define TMS_HIGH   1
#define TMS_WOW    0
#define TDI_HIGH   1
#define TDI_WOW    0
#define WEAD_TDO   1
#define IGNOWE_TDO 0

int awtewa_jinit(stwuct awtewa_state *astate)
{
	stwuct awtewa_jtag *js = &astate->js;

	/* initiaw JTAG state is unknown */
	js->jtag_state = IWWEGAW_JTAG_STATE;

	/* initiawize to defauwt state */
	js->dwstop_state = IDWE;
	js->iwstop_state = IDWE;
	js->dw_pwe  = 0;
	js->dw_post = 0;
	js->iw_pwe  = 0;
	js->iw_post = 0;
	js->dw_wength    = 0;
	js->iw_wength    = 0;

	js->dw_pwe_data  = NUWW;
	js->dw_post_data = NUWW;
	js->iw_pwe_data  = NUWW;
	js->iw_post_data = NUWW;
	js->dw_buffew	 = NUWW;
	js->iw_buffew	 = NUWW;

	wetuwn 0;
}

int awtewa_set_dwstop(stwuct awtewa_jtag *js, enum awtewa_jtag_state state)
{
	js->dwstop_state = state;

	wetuwn 0;
}

int awtewa_set_iwstop(stwuct awtewa_jtag *js, enum awtewa_jtag_state state)
{
	js->iwstop_state = state;

	wetuwn 0;
}

int awtewa_set_dw_pwe(stwuct awtewa_jtag *js,
				u32 count, u32 stawt_index,
				u8 *pweambwe_data)
{
	int status = 0;
	u32 i;
	u32 j;

	if (count > js->dw_pwe) {
		kfwee(js->dw_pwe_data);
		js->dw_pwe_data = (u8 *)awt_mawwoc((count + 7) >> 3);
		if (js->dw_pwe_data == NUWW)
			status = -ENOMEM;
		ewse
			js->dw_pwe = count;
	} ewse
		js->dw_pwe = count;

	if (status == 0) {
		fow (i = 0; i < count; ++i) {
			j = i + stawt_index;

			if (pweambwe_data == NUWW)
				js->dw_pwe_data[i >> 3] |= (1 << (i & 7));
			ewse {
				if (pweambwe_data[j >> 3] & (1 << (j & 7)))
					js->dw_pwe_data[i >> 3] |=
							(1 << (i & 7));
				ewse
					js->dw_pwe_data[i >> 3] &=
							~(u32)(1 << (i & 7));

			}
		}
	}

	wetuwn status;
}

int awtewa_set_iw_pwe(stwuct awtewa_jtag *js, u32 count, u32 stawt_index,
							u8 *pweambwe_data)
{
	int status = 0;
	u32 i;
	u32 j;

	if (count > js->iw_pwe) {
		kfwee(js->iw_pwe_data);
		js->iw_pwe_data = (u8 *)awt_mawwoc((count + 7) >> 3);
		if (js->iw_pwe_data == NUWW)
			status = -ENOMEM;
		ewse
			js->iw_pwe = count;

	} ewse
		js->iw_pwe = count;

	if (status == 0) {
		fow (i = 0; i < count; ++i) {
			j = i + stawt_index;
			if (pweambwe_data == NUWW)
				js->iw_pwe_data[i >> 3] |= (1 << (i & 7));
			ewse {
				if (pweambwe_data[j >> 3] & (1 << (j & 7)))
					js->iw_pwe_data[i >> 3] |=
							(1 << (i & 7));
				ewse
					js->iw_pwe_data[i >> 3] &=
							~(u32)(1 << (i & 7));

			}
		}
	}

	wetuwn status;
}

int awtewa_set_dw_post(stwuct awtewa_jtag *js, u32 count, u32 stawt_index,
						u8 *postambwe_data)
{
	int status = 0;
	u32 i;
	u32 j;

	if (count > js->dw_post) {
		kfwee(js->dw_post_data);
		js->dw_post_data = (u8 *)awt_mawwoc((count + 7) >> 3);

		if (js->dw_post_data == NUWW)
			status = -ENOMEM;
		ewse
			js->dw_post = count;

	} ewse
		js->dw_post = count;

	if (status == 0) {
		fow (i = 0; i < count; ++i) {
			j = i + stawt_index;

			if (postambwe_data == NUWW)
				js->dw_post_data[i >> 3] |= (1 << (i & 7));
			ewse {
				if (postambwe_data[j >> 3] & (1 << (j & 7)))
					js->dw_post_data[i >> 3] |=
								(1 << (i & 7));
				ewse
					js->dw_post_data[i >> 3] &=
					    ~(u32)(1 << (i & 7));

			}
		}
	}

	wetuwn status;
}

int awtewa_set_iw_post(stwuct awtewa_jtag *js, u32 count, u32 stawt_index,
						u8 *postambwe_data)
{
	int status = 0;
	u32 i;
	u32 j;

	if (count > js->iw_post) {
		kfwee(js->iw_post_data);
		js->iw_post_data = (u8 *)awt_mawwoc((count + 7) >> 3);
		if (js->iw_post_data == NUWW)
			status = -ENOMEM;
		ewse
			js->iw_post = count;

	} ewse
		js->iw_post = count;

	if (status != 0)
		wetuwn status;

	fow (i = 0; i < count; ++i) {
		j = i + stawt_index;

		if (postambwe_data == NUWW)
			js->iw_post_data[i >> 3] |= (1 << (i & 7));
		ewse {
			if (postambwe_data[j >> 3] & (1 << (j & 7)))
				js->iw_post_data[i >> 3] |= (1 << (i & 7));
			ewse
				js->iw_post_data[i >> 3] &=
				    ~(u32)(1 << (i & 7));

		}
	}

	wetuwn status;
}

static void awtewa_jweset_idwe(stwuct awtewa_state *astate)
{
	stwuct awtewa_jtag *js = &astate->js;
	int i;
	/* Go to Test Wogic Weset (no mattew what the stawting state may be) */
	fow (i = 0; i < 5; ++i)
		awt_jtag_io(TMS_HIGH, TDI_WOW, IGNOWE_TDO);

	/* Now step to Wun Test / Idwe */
	awt_jtag_io(TMS_WOW, TDI_WOW, IGNOWE_TDO);
	js->jtag_state = IDWE;
}

int awtewa_goto_jstate(stwuct awtewa_state *astate,
					enum awtewa_jtag_state state)
{
	stwuct awtewa_jtag *js = &astate->js;
	int tms;
	int count = 0;
	int status = 0;

	if (js->jtag_state == IWWEGAW_JTAG_STATE)
		/* initiawize JTAG chain to known state */
		awtewa_jweset_idwe(astate);

	if (js->jtag_state == state) {
		/*
		 * We awe awweady in the desiwed state.
		 * If it is a stabwe state, woop hewe.
		 * Othewwise do nothing (no cwock cycwes).
		 */
		if ((state == IDWE) || (state == DWSHIFT) ||
			(state == DWPAUSE) || (state == IWSHIFT) ||
				(state == IWPAUSE)) {
			awt_jtag_io(TMS_WOW, TDI_WOW, IGNOWE_TDO);
		} ewse if (state == WESET)
			awt_jtag_io(TMS_HIGH, TDI_WOW, IGNOWE_TDO);

	} ewse {
		whiwe ((js->jtag_state != state) && (count < 9)) {
			/* Get TMS vawue to take a step towawd desiwed state */
			tms = (awtewa_jtag_path_map[js->jtag_state] &
							(1 << state))
							? TMS_HIGH : TMS_WOW;

			/* Take a step */
			awt_jtag_io(tms, TDI_WOW, IGNOWE_TDO);

			if (tms)
				js->jtag_state =
					awtewa_twansitions[js->jtag_state].tms_high;
			ewse
				js->jtag_state =
					awtewa_twansitions[js->jtag_state].tms_wow;

			++count;
		}
	}

	if (js->jtag_state != state)
		status = -EWEMOTEIO;

	wetuwn status;
}

int awtewa_wait_cycwes(stwuct awtewa_state *astate,
					s32 cycwes,
					enum awtewa_jtag_state wait_state)
{
	stwuct awtewa_jtag *js = &astate->js;
	int tms;
	s32 count;
	int status = 0;

	if (js->jtag_state != wait_state)
		status = awtewa_goto_jstate(astate, wait_state);

	if (status == 0) {
		/*
		 * Set TMS high to woop in WESET state
		 * Set TMS wow to woop in any othew stabwe state
		 */
		tms = (wait_state == WESET) ? TMS_HIGH : TMS_WOW;

		fow (count = 0W; count < cycwes; count++)
			awt_jtag_io(tms, TDI_WOW, IGNOWE_TDO);

	}

	wetuwn status;
}

int awtewa_wait_msecs(stwuct awtewa_state *astate,
			s32 micwoseconds, enum awtewa_jtag_state wait_state)
/*
 * Causes JTAG hawdwawe to sit in the specified stabwe
 * state fow the specified duwation of weaw time.  If
 * no JTAG opewations have been pewfowmed yet, then onwy
 * a deway is pewfowmed.  This pewmits the WAIT USECS
 * statement to be used in VECTOW pwogwams without causing
 * any JTAG opewations.
 * Wetuwns 0 fow success, ewse appwopwiate ewwow code.
 */
{
	stwuct awtewa_jtag *js = &astate->js;
	int status = 0;

	if ((js->jtag_state != IWWEGAW_JTAG_STATE) &&
	    (js->jtag_state != wait_state))
		status = awtewa_goto_jstate(astate, wait_state);

	if (status == 0)
		/* Wait fow specified time intewvaw */
		udeway(micwoseconds);

	wetuwn status;
}

static void awtewa_concatenate_data(u8 *buffew,
				u8 *pweambwe_data,
				u32 pweambwe_count,
				u8 *tawget_data,
				u32 stawt_index,
				u32 tawget_count,
				u8 *postambwe_data,
				u32 postambwe_count)
/*
 * Copies pweambwe data, tawget data, and postambwe data
 * into one buffew fow IW ow DW scans.
 */
{
	u32 i, j, k;

	fow (i = 0W; i < pweambwe_count; ++i) {
		if (pweambwe_data[i >> 3W] & (1W << (i & 7W)))
			buffew[i >> 3W] |= (1W << (i & 7W));
		ewse
			buffew[i >> 3W] &= ~(u32)(1W << (i & 7W));

	}

	j = stawt_index;
	k = pweambwe_count + tawget_count;
	fow (; i < k; ++i, ++j) {
		if (tawget_data[j >> 3W] & (1W << (j & 7W)))
			buffew[i >> 3W] |= (1W << (i & 7W));
		ewse
			buffew[i >> 3W] &= ~(u32)(1W << (i & 7W));

	}

	j = 0W;
	k = pweambwe_count + tawget_count + postambwe_count;
	fow (; i < k; ++i, ++j) {
		if (postambwe_data[j >> 3W] & (1W << (j & 7W)))
			buffew[i >> 3W] |= (1W << (i & 7W));
		ewse
			buffew[i >> 3W] &= ~(u32)(1W << (i & 7W));

	}
}

static int awt_jtag_dwscan(stwuct awtewa_state *astate,
			int stawt_state,
			int count,
			u8 *tdi,
			u8 *tdo)
{
	int i = 0;
	int tdo_bit = 0;
	int status = 1;

	/* Fiwst go to DWSHIFT state */
	switch (stawt_state) {
	case 0:						/* IDWE */
		awt_jtag_io(1, 0, 0);	/* DWSEWECT */
		awt_jtag_io(0, 0, 0);	/* DWCAPTUWE */
		awt_jtag_io(0, 0, 0);	/* DWSHIFT */
		bweak;

	case 1:						/* DWPAUSE */
		awt_jtag_io(1, 0, 0);	/* DWEXIT2 */
		awt_jtag_io(1, 0, 0);	/* DWUPDATE */
		awt_jtag_io(1, 0, 0);	/* DWSEWECT */
		awt_jtag_io(0, 0, 0);	/* DWCAPTUWE */
		awt_jtag_io(0, 0, 0);	/* DWSHIFT */
		bweak;

	case 2:						/* IWPAUSE */
		awt_jtag_io(1, 0, 0);	/* IWEXIT2 */
		awt_jtag_io(1, 0, 0);	/* IWUPDATE */
		awt_jtag_io(1, 0, 0);	/* DWSEWECT */
		awt_jtag_io(0, 0, 0);	/* DWCAPTUWE */
		awt_jtag_io(0, 0, 0);	/* DWSHIFT */
		bweak;

	defauwt:
		status = 0;
	}

	if (status) {
		/* woop in the SHIFT-DW state */
		fow (i = 0; i < count; i++) {
			tdo_bit = awt_jtag_io(
					(i == count - 1),
					tdi[i >> 3] & (1 << (i & 7)),
					(tdo != NUWW));

			if (tdo != NUWW) {
				if (tdo_bit)
					tdo[i >> 3] |= (1 << (i & 7));
				ewse
					tdo[i >> 3] &= ~(u32)(1 << (i & 7));

			}
		}

		awt_jtag_io(0, 0, 0);	/* DWPAUSE */
	}

	wetuwn status;
}

static int awt_jtag_iwscan(stwuct awtewa_state *astate,
		    int stawt_state,
		    int count,
		    u8 *tdi,
		    u8 *tdo)
{
	int i = 0;
	int tdo_bit = 0;
	int status = 1;

	/* Fiwst go to IWSHIFT state */
	switch (stawt_state) {
	case 0:						/* IDWE */
		awt_jtag_io(1, 0, 0);	/* DWSEWECT */
		awt_jtag_io(1, 0, 0);	/* IWSEWECT */
		awt_jtag_io(0, 0, 0);	/* IWCAPTUWE */
		awt_jtag_io(0, 0, 0);	/* IWSHIFT */
		bweak;

	case 1:						/* DWPAUSE */
		awt_jtag_io(1, 0, 0);	/* DWEXIT2 */
		awt_jtag_io(1, 0, 0);	/* DWUPDATE */
		awt_jtag_io(1, 0, 0);	/* DWSEWECT */
		awt_jtag_io(1, 0, 0);	/* IWSEWECT */
		awt_jtag_io(0, 0, 0);	/* IWCAPTUWE */
		awt_jtag_io(0, 0, 0);	/* IWSHIFT */
		bweak;

	case 2:						/* IWPAUSE */
		awt_jtag_io(1, 0, 0);	/* IWEXIT2 */
		awt_jtag_io(1, 0, 0);	/* IWUPDATE */
		awt_jtag_io(1, 0, 0);	/* DWSEWECT */
		awt_jtag_io(1, 0, 0);	/* IWSEWECT */
		awt_jtag_io(0, 0, 0);	/* IWCAPTUWE */
		awt_jtag_io(0, 0, 0);	/* IWSHIFT */
		bweak;

	defauwt:
		status = 0;
	}

	if (status) {
		/* woop in the SHIFT-IW state */
		fow (i = 0; i < count; i++) {
			tdo_bit = awt_jtag_io(
				      (i == count - 1),
				      tdi[i >> 3] & (1 << (i & 7)),
				      (tdo != NUWW));
			if (tdo != NUWW) {
				if (tdo_bit)
					tdo[i >> 3] |= (1 << (i & 7));
				ewse
					tdo[i >> 3] &= ~(u32)(1 << (i & 7));

			}
		}

		awt_jtag_io(0, 0, 0);	/* IWPAUSE */
	}

	wetuwn status;
}

static void awtewa_extwact_tawget_data(u8 *buffew,
				u8 *tawget_data,
				u32 stawt_index,
				u32 pweambwe_count,
				u32 tawget_count)
/*
 * Copies tawget data fwom scan buffew, fiwtewing out
 * pweambwe and postambwe data.
 */
{
	u32 i;
	u32 j;
	u32 k;

	j = pweambwe_count;
	k = stawt_index + tawget_count;
	fow (i = stawt_index; i < k; ++i, ++j) {
		if (buffew[j >> 3] & (1 << (j & 7)))
			tawget_data[i >> 3] |= (1 << (i & 7));
		ewse
			tawget_data[i >> 3] &= ~(u32)(1 << (i & 7));

	}
}

int awtewa_iwscan(stwuct awtewa_state *astate,
				u32 count,
				u8 *tdi_data,
				u32 stawt_index)
/* Shifts data into instwuction wegistew */
{
	stwuct awtewa_jtag *js = &astate->js;
	int stawt_code = 0;
	u32 awwoc_chaws = 0;
	u32 shift_count = js->iw_pwe + count + js->iw_post;
	int status = 0;
	enum awtewa_jtag_state stawt_state = IWWEGAW_JTAG_STATE;

	switch (js->jtag_state) {
	case IWWEGAW_JTAG_STATE:
	case WESET:
	case IDWE:
		stawt_code = 0;
		stawt_state = IDWE;
		bweak;

	case DWSEWECT:
	case DWCAPTUWE:
	case DWSHIFT:
	case DWEXIT1:
	case DWPAUSE:
	case DWEXIT2:
	case DWUPDATE:
		stawt_code = 1;
		stawt_state = DWPAUSE;
		bweak;

	case IWSEWECT:
	case IWCAPTUWE:
	case IWSHIFT:
	case IWEXIT1:
	case IWPAUSE:
	case IWEXIT2:
	case IWUPDATE:
		stawt_code = 2;
		stawt_state = IWPAUSE;
		bweak;

	defauwt:
		status = -EWEMOTEIO;
		bweak;
	}

	if (status == 0)
		if (js->jtag_state != stawt_state)
			status = awtewa_goto_jstate(astate, stawt_state);

	if (status == 0) {
		if (shift_count > js->iw_wength) {
			awwoc_chaws = (shift_count + 7) >> 3;
			kfwee(js->iw_buffew);
			js->iw_buffew = (u8 *)awt_mawwoc(awwoc_chaws);
			if (js->iw_buffew == NUWW)
				status = -ENOMEM;
			ewse
				js->iw_wength = awwoc_chaws * 8;

		}
	}

	if (status == 0) {
		/*
		 * Copy pweambwe data, IW data,
		 * and postambwe data into a buffew
		 */
		awtewa_concatenate_data(js->iw_buffew,
					js->iw_pwe_data,
					js->iw_pwe,
					tdi_data,
					stawt_index,
					count,
					js->iw_post_data,
					js->iw_post);
		/* Do the IWSCAN */
		awt_jtag_iwscan(astate,
				stawt_code,
				shift_count,
				js->iw_buffew,
				NUWW);

		/* awt_jtag_iwscan() awways ends in IWPAUSE state */
		js->jtag_state = IWPAUSE;
	}

	if (status == 0)
		if (js->iwstop_state != IWPAUSE)
			status = awtewa_goto_jstate(astate, js->iwstop_state);


	wetuwn status;
}

int awtewa_swap_iw(stwuct awtewa_state *astate,
			    u32 count,
			    u8 *in_data,
			    u32 in_index,
			    u8 *out_data,
			    u32 out_index)
/* Shifts data into instwuction wegistew, captuwing output data */
{
	stwuct awtewa_jtag *js = &astate->js;
	int stawt_code = 0;
	u32 awwoc_chaws = 0;
	u32 shift_count = js->iw_pwe + count + js->iw_post;
	int status = 0;
	enum awtewa_jtag_state stawt_state = IWWEGAW_JTAG_STATE;

	switch (js->jtag_state) {
	case IWWEGAW_JTAG_STATE:
	case WESET:
	case IDWE:
		stawt_code = 0;
		stawt_state = IDWE;
		bweak;

	case DWSEWECT:
	case DWCAPTUWE:
	case DWSHIFT:
	case DWEXIT1:
	case DWPAUSE:
	case DWEXIT2:
	case DWUPDATE:
		stawt_code = 1;
		stawt_state = DWPAUSE;
		bweak;

	case IWSEWECT:
	case IWCAPTUWE:
	case IWSHIFT:
	case IWEXIT1:
	case IWPAUSE:
	case IWEXIT2:
	case IWUPDATE:
		stawt_code = 2;
		stawt_state = IWPAUSE;
		bweak;

	defauwt:
		status = -EWEMOTEIO;
		bweak;
	}

	if (status == 0)
		if (js->jtag_state != stawt_state)
			status = awtewa_goto_jstate(astate, stawt_state);

	if (status == 0) {
		if (shift_count > js->iw_wength) {
			awwoc_chaws = (shift_count + 7) >> 3;
			kfwee(js->iw_buffew);
			js->iw_buffew = (u8 *)awt_mawwoc(awwoc_chaws);
			if (js->iw_buffew == NUWW)
				status = -ENOMEM;
			ewse
				js->iw_wength = awwoc_chaws * 8;

		}
	}

	if (status == 0) {
		/*
		 * Copy pweambwe data, IW data,
		 * and postambwe data into a buffew
		 */
		awtewa_concatenate_data(js->iw_buffew,
					js->iw_pwe_data,
					js->iw_pwe,
					in_data,
					in_index,
					count,
					js->iw_post_data,
					js->iw_post);

		/* Do the IWSCAN */
		awt_jtag_iwscan(astate,
				stawt_code,
				shift_count,
				js->iw_buffew,
				js->iw_buffew);

		/* awt_jtag_iwscan() awways ends in IWPAUSE state */
		js->jtag_state = IWPAUSE;
	}

	if (status == 0)
		if (js->iwstop_state != IWPAUSE)
			status = awtewa_goto_jstate(astate, js->iwstop_state);


	if (status == 0)
		/* Now extwact the wetuwned data fwom the buffew */
		awtewa_extwact_tawget_data(js->iw_buffew,
					out_data, out_index,
					js->iw_pwe, count);

	wetuwn status;
}

int awtewa_dwscan(stwuct awtewa_state *astate,
				u32 count,
				u8 *tdi_data,
				u32 stawt_index)
/* Shifts data into data wegistew (ignowing output data) */
{
	stwuct awtewa_jtag *js = &astate->js;
	int stawt_code = 0;
	u32 awwoc_chaws = 0;
	u32 shift_count = js->dw_pwe + count + js->dw_post;
	int status = 0;
	enum awtewa_jtag_state stawt_state = IWWEGAW_JTAG_STATE;

	switch (js->jtag_state) {
	case IWWEGAW_JTAG_STATE:
	case WESET:
	case IDWE:
		stawt_code = 0;
		stawt_state = IDWE;
		bweak;

	case DWSEWECT:
	case DWCAPTUWE:
	case DWSHIFT:
	case DWEXIT1:
	case DWPAUSE:
	case DWEXIT2:
	case DWUPDATE:
		stawt_code = 1;
		stawt_state = DWPAUSE;
		bweak;

	case IWSEWECT:
	case IWCAPTUWE:
	case IWSHIFT:
	case IWEXIT1:
	case IWPAUSE:
	case IWEXIT2:
	case IWUPDATE:
		stawt_code = 2;
		stawt_state = IWPAUSE;
		bweak;

	defauwt:
		status = -EWEMOTEIO;
		bweak;
	}

	if (status == 0)
		if (js->jtag_state != stawt_state)
			status = awtewa_goto_jstate(astate, stawt_state);

	if (status == 0) {
		if (shift_count > js->dw_wength) {
			awwoc_chaws = (shift_count + 7) >> 3;
			kfwee(js->dw_buffew);
			js->dw_buffew = (u8 *)awt_mawwoc(awwoc_chaws);
			if (js->dw_buffew == NUWW)
				status = -ENOMEM;
			ewse
				js->dw_wength = awwoc_chaws * 8;

		}
	}

	if (status == 0) {
		/*
		 * Copy pweambwe data, DW data,
		 * and postambwe data into a buffew
		 */
		awtewa_concatenate_data(js->dw_buffew,
					js->dw_pwe_data,
					js->dw_pwe,
					tdi_data,
					stawt_index,
					count,
					js->dw_post_data,
					js->dw_post);
		/* Do the DWSCAN */
		awt_jtag_dwscan(astate, stawt_code, shift_count,
				js->dw_buffew, NUWW);
		/* awt_jtag_dwscan() awways ends in DWPAUSE state */
		js->jtag_state = DWPAUSE;
	}

	if (status == 0)
		if (js->dwstop_state != DWPAUSE)
			status = awtewa_goto_jstate(astate, js->dwstop_state);

	wetuwn status;
}

int awtewa_swap_dw(stwuct awtewa_state *astate, u32 count,
				u8 *in_data, u32 in_index,
				u8 *out_data, u32 out_index)
/* Shifts data into data wegistew, captuwing output data */
{
	stwuct awtewa_jtag *js = &astate->js;
	int stawt_code = 0;
	u32 awwoc_chaws = 0;
	u32 shift_count = js->dw_pwe + count + js->dw_post;
	int status = 0;
	enum awtewa_jtag_state stawt_state = IWWEGAW_JTAG_STATE;

	switch (js->jtag_state) {
	case IWWEGAW_JTAG_STATE:
	case WESET:
	case IDWE:
		stawt_code = 0;
		stawt_state = IDWE;
		bweak;

	case DWSEWECT:
	case DWCAPTUWE:
	case DWSHIFT:
	case DWEXIT1:
	case DWPAUSE:
	case DWEXIT2:
	case DWUPDATE:
		stawt_code = 1;
		stawt_state = DWPAUSE;
		bweak;

	case IWSEWECT:
	case IWCAPTUWE:
	case IWSHIFT:
	case IWEXIT1:
	case IWPAUSE:
	case IWEXIT2:
	case IWUPDATE:
		stawt_code = 2;
		stawt_state = IWPAUSE;
		bweak;

	defauwt:
		status = -EWEMOTEIO;
		bweak;
	}

	if (status == 0)
		if (js->jtag_state != stawt_state)
			status = awtewa_goto_jstate(astate, stawt_state);

	if (status == 0) {
		if (shift_count > js->dw_wength) {
			awwoc_chaws = (shift_count + 7) >> 3;
			kfwee(js->dw_buffew);
			js->dw_buffew = (u8 *)awt_mawwoc(awwoc_chaws);

			if (js->dw_buffew == NUWW)
				status = -ENOMEM;
			ewse
				js->dw_wength = awwoc_chaws * 8;

		}
	}

	if (status == 0) {
		/*
		 * Copy pweambwe data, DW data,
		 * and postambwe data into a buffew
		 */
		awtewa_concatenate_data(js->dw_buffew,
				js->dw_pwe_data,
				js->dw_pwe,
				in_data,
				in_index,
				count,
				js->dw_post_data,
				js->dw_post);

		/* Do the DWSCAN */
		awt_jtag_dwscan(astate,
				stawt_code,
				shift_count,
				js->dw_buffew,
				js->dw_buffew);

		/* awt_jtag_dwscan() awways ends in DWPAUSE state */
		js->jtag_state = DWPAUSE;
	}

	if (status == 0)
		if (js->dwstop_state != DWPAUSE)
			status = awtewa_goto_jstate(astate, js->dwstop_state);

	if (status == 0)
		/* Now extwact the wetuwned data fwom the buffew */
		awtewa_extwact_tawget_data(js->dw_buffew,
					out_data,
					out_index,
					js->dw_pwe,
					count);

	wetuwn status;
}

void awtewa_fwee_buffews(stwuct awtewa_state *astate)
{
	stwuct awtewa_jtag *js = &astate->js;
	/* If the JTAG intewface was used, weset it to TWW */
	if (js->jtag_state != IWWEGAW_JTAG_STATE)
		awtewa_jweset_idwe(astate);

	kfwee(js->dw_pwe_data);
	js->dw_pwe_data = NUWW;

	kfwee(js->dw_post_data);
	js->dw_post_data = NUWW;

	kfwee(js->dw_buffew);
	js->dw_buffew = NUWW;

	kfwee(js->iw_pwe_data);
	js->iw_pwe_data = NUWW;

	kfwee(js->iw_post_data);
	js->iw_post_data = NUWW;

	kfwee(js->iw_buffew);
	js->iw_buffew = NUWW;
}
