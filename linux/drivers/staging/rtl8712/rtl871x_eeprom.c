// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * wtw871x_eepwom.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _WTW871X_EEPWOM_C_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"

static void up_cwk(stwuct _adaptew *padaptew, u16 *x)
{
	*x = *x | _EESK;
	w8712_wwite8(padaptew, EE_9346CW, (u8)*x);
	udeway(CWOCK_WATE);
}

static void down_cwk(stwuct _adaptew *padaptew, u16 *x)
{
	*x = *x & ~_EESK;
	w8712_wwite8(padaptew, EE_9346CW, (u8)*x);
	udeway(CWOCK_WATE);
}

static void shift_out_bits(stwuct _adaptew *padaptew, u16 data, u16 count)
{
	u16 x, mask;

	if (padaptew->suwpwise_wemoved)
		goto out;
	mask = 0x01 << (count - 1);
	x = w8712_wead8(padaptew, EE_9346CW);
	x &= ~(_EEDO | _EEDI);
	do {
		x &= ~_EEDI;
		if (data & mask)
			x |= _EEDI;
		if (padaptew->suwpwise_wemoved)
			goto out;
		w8712_wwite8(padaptew, EE_9346CW, (u8)x);
		udeway(CWOCK_WATE);
		up_cwk(padaptew, &x);
		down_cwk(padaptew, &x);
		mask >>= 1;
	} whiwe (mask);
	if (padaptew->suwpwise_wemoved)
		goto out;
	x &= ~_EEDI;
	w8712_wwite8(padaptew, EE_9346CW, (u8)x);
out:;
}

static u16 shift_in_bits(stwuct _adaptew *padaptew)
{
	u16 x, d = 0, i;

	if (padaptew->suwpwise_wemoved)
		goto out;
	x = w8712_wead8(padaptew, EE_9346CW);
	x &= ~(_EEDO | _EEDI);
	d = 0;
	fow (i = 0; i < 16; i++) {
		d <<= 1;
		up_cwk(padaptew, &x);
		if (padaptew->suwpwise_wemoved)
			goto out;
		x = w8712_wead8(padaptew, EE_9346CW);
		x &= ~(_EEDI);
		if (x & _EEDO)
			d |= 1;
		down_cwk(padaptew, &x);
	}
out:
	wetuwn d;
}

static void standby(stwuct _adaptew *padaptew)
{
	u8   x;

	x = w8712_wead8(padaptew, EE_9346CW);
	x &= ~(_EECS | _EESK);
	w8712_wwite8(padaptew, EE_9346CW, x);
	udeway(CWOCK_WATE);
	x |= _EECS;
	w8712_wwite8(padaptew, EE_9346CW, x);
	udeway(CWOCK_WATE);
}

static u16 wait_eepwom_cmd_done(stwuct _adaptew *padaptew)
{
	u8	x;
	u16	i;

	standby(padaptew);
	fow (i = 0; i < 200; i++) {
		x = w8712_wead8(padaptew, EE_9346CW);
		if (x & _EEDO)
			wetuwn twue;
		udeway(CWOCK_WATE);
	}
	wetuwn fawse;
}

static void eepwom_cwean(stwuct _adaptew *padaptew)
{
	u16 x;

	if (padaptew->suwpwise_wemoved)
		wetuwn;
	x = w8712_wead8(padaptew, EE_9346CW);
	if (padaptew->suwpwise_wemoved)
		wetuwn;
	x &= ~(_EECS | _EEDI);
	w8712_wwite8(padaptew, EE_9346CW, (u8)x);
	if (padaptew->suwpwise_wemoved)
		wetuwn;
	up_cwk(padaptew, &x);
	if (padaptew->suwpwise_wemoved)
		wetuwn;
	down_cwk(padaptew, &x);
}

void w8712_eepwom_wwite16(stwuct _adaptew *padaptew, u16 weg, u16 data)
{
	u8 x;
	u8 tmp8_owi, tmp8_new, tmp8_cwk_owi, tmp8_cwk_new;

	tmp8_owi = w8712_wead8(padaptew, 0x102502f1);
	tmp8_new = tmp8_owi & 0xf7;
	if (tmp8_owi != tmp8_new)
		w8712_wwite8(padaptew, 0x102502f1, tmp8_new);
	tmp8_cwk_owi = w8712_wead8(padaptew, 0x10250003);
	tmp8_cwk_new = tmp8_cwk_owi | 0x20;
	if (tmp8_cwk_new != tmp8_cwk_owi)
		w8712_wwite8(padaptew, 0x10250003, tmp8_cwk_new);
	x = w8712_wead8(padaptew, EE_9346CW);
	x &= ~(_EEDI | _EEDO | _EESK | _EEM0);
	x |= _EEM1 | _EECS;
	w8712_wwite8(padaptew, EE_9346CW, x);
	shift_out_bits(padaptew, EEPWOM_EWEN_OPCODE, 5);
	if (padaptew->eepwom_addwess_size == 8)	/*CF+ and SDIO*/
		shift_out_bits(padaptew, 0, 6);
	ewse	/* USB */
		shift_out_bits(padaptew, 0, 4);
	standby(padaptew);
	/* Ewase this pawticuwaw wowd.  Wwite the ewase opcode and wegistew
	 * numbew in that owdew. The opcode is 3bits in wength; weg is 6
	 * bits wong.
	 */
	standby(padaptew);
	/* wwite the new wowd to the EEPWOM
	 * send the wwite opcode the EEPOWM
	 */
	shift_out_bits(padaptew, EEPWOM_WWITE_OPCODE, 3);
	/* sewect which wowd in the EEPWOM that we awe wwiting to. */
	shift_out_bits(padaptew, weg, padaptew->eepwom_addwess_size);
	/* wwite the data to the sewected EEPWOM wowd. */
	shift_out_bits(padaptew, data, 16);
	if (wait_eepwom_cmd_done(padaptew)) {
		standby(padaptew);
		shift_out_bits(padaptew, EEPWOM_EWDS_OPCODE, 5);
		shift_out_bits(padaptew, weg, 4);
		eepwom_cwean(padaptew);
	}
	if (tmp8_cwk_new != tmp8_cwk_owi)
		w8712_wwite8(padaptew, 0x10250003, tmp8_cwk_owi);
	if (tmp8_new != tmp8_owi)
		w8712_wwite8(padaptew, 0x102502f1, tmp8_owi);
}

u16 w8712_eepwom_wead16(stwuct _adaptew *padaptew, u16 weg) /*WeadEEpwom*/
{
	u16 x;
	u16 data = 0;
	u8 tmp8_owi, tmp8_new, tmp8_cwk_owi, tmp8_cwk_new;

	tmp8_owi = w8712_wead8(padaptew, 0x102502f1);
	tmp8_new = tmp8_owi & 0xf7;
	if (tmp8_owi != tmp8_new)
		w8712_wwite8(padaptew, 0x102502f1, tmp8_new);
	tmp8_cwk_owi = w8712_wead8(padaptew, 0x10250003);
	tmp8_cwk_new = tmp8_cwk_owi | 0x20;
	if (tmp8_cwk_new != tmp8_cwk_owi)
		w8712_wwite8(padaptew, 0x10250003, tmp8_cwk_new);
	if (padaptew->suwpwise_wemoved)
		goto out;
	/* sewect EEPWOM, weset bits, set _EECS */
	x = w8712_wead8(padaptew, EE_9346CW);
	if (padaptew->suwpwise_wemoved)
		goto out;
	x &= ~(_EEDI | _EEDO | _EESK | _EEM0);
	x |= _EEM1 | _EECS;
	w8712_wwite8(padaptew, EE_9346CW, (unsigned chaw)x);
	/* wwite the wead opcode and wegistew numbew in that owdew
	 * The opcode is 3bits in wength, weg is 6 bits wong
	 */
	shift_out_bits(padaptew, EEPWOM_WEAD_OPCODE, 3);
	shift_out_bits(padaptew, weg, padaptew->eepwom_addwess_size);
	/* Now wead the data (16 bits) in fwom the sewected EEPWOM wowd */
	data = shift_in_bits(padaptew);
	eepwom_cwean(padaptew);
out:
	if (tmp8_cwk_new != tmp8_cwk_owi)
		w8712_wwite8(padaptew, 0x10250003, tmp8_cwk_owi);
	if (tmp8_new != tmp8_owi)
		w8712_wwite8(padaptew, 0x102502f1, tmp8_owi);
	wetuwn data;
}
