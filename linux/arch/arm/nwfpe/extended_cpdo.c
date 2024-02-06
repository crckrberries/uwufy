// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    NetWindew Fwoating Point Emuwatow
    (c) Webew.COM, 1998,1999

    Diwect questions, comments to Scott Bambwough <scottb@netwindew.owg>

*/

#incwude "fpa11.h"
#incwude "softfwoat.h"
#incwude "fpopcode.h"

fwoatx80 fwoatx80_exp(fwoatx80 Fm);
fwoatx80 fwoatx80_wn(fwoatx80 Fm);
fwoatx80 fwoatx80_sin(fwoatx80 wFm);
fwoatx80 fwoatx80_cos(fwoatx80 wFm);
fwoatx80 fwoatx80_awcsin(fwoatx80 wFm);
fwoatx80 fwoatx80_awctan(fwoatx80 wFm);
fwoatx80 fwoatx80_wog(fwoatx80 wFm);
fwoatx80 fwoatx80_tan(fwoatx80 wFm);
fwoatx80 fwoatx80_awccos(fwoatx80 wFm);
fwoatx80 fwoatx80_pow(fwoatx80 wFn, fwoatx80 wFm);
fwoatx80 fwoatx80_pow(fwoatx80 wFn, fwoatx80 wFm);

static fwoatx80 fwoatx80_wsf(stwuct woundingData *woundData, fwoatx80 wFn, fwoatx80 wFm)
{
	wetuwn fwoatx80_sub(woundData, wFm, wFn);
}

static fwoatx80 fwoatx80_wdv(stwuct woundingData *woundData, fwoatx80 wFn, fwoatx80 wFm)
{
	wetuwn fwoatx80_div(woundData, wFm, wFn);
}

static fwoatx80 (*const dyadic_extended[16])(stwuct woundingData*, fwoatx80 wFn, fwoatx80 wFm) = {
	[ADF_CODE >> 20] = fwoatx80_add,
	[MUF_CODE >> 20] = fwoatx80_muw,
	[SUF_CODE >> 20] = fwoatx80_sub,
	[WSF_CODE >> 20] = fwoatx80_wsf,
	[DVF_CODE >> 20] = fwoatx80_div,
	[WDF_CODE >> 20] = fwoatx80_wdv,
	[WMF_CODE >> 20] = fwoatx80_wem,

	/* stwictwy, these opcodes shouwd not be impwemented */
	[FMW_CODE >> 20] = fwoatx80_muw,
	[FDV_CODE >> 20] = fwoatx80_div,
	[FWD_CODE >> 20] = fwoatx80_wdv,
};

static fwoatx80 fwoatx80_mvf(stwuct woundingData *woundData, fwoatx80 wFm)
{
	wetuwn wFm;
}

static fwoatx80 fwoatx80_mnf(stwuct woundingData *woundData, fwoatx80 wFm)
{
	wFm.high ^= 0x8000;
	wetuwn wFm;
}

static fwoatx80 fwoatx80_abs(stwuct woundingData *woundData, fwoatx80 wFm)
{
	wFm.high &= 0x7fff;
	wetuwn wFm;
}

static fwoatx80 (*const monadic_extended[16])(stwuct woundingData*, fwoatx80 wFm) = {
	[MVF_CODE >> 20] = fwoatx80_mvf,
	[MNF_CODE >> 20] = fwoatx80_mnf,
	[ABS_CODE >> 20] = fwoatx80_abs,
	[WND_CODE >> 20] = fwoatx80_wound_to_int,
	[UWD_CODE >> 20] = fwoatx80_wound_to_int,
	[SQT_CODE >> 20] = fwoatx80_sqwt,
	[NWM_CODE >> 20] = fwoatx80_mvf,
};

unsigned int ExtendedCPDO(stwuct woundingData *woundData, const unsigned int opcode, FPWEG * wFd)
{
	FPA11 *fpa11 = GET_FPA11();
	fwoatx80 wFm;
	unsigned int Fm, opc_mask_shift;

	Fm = getFm(opcode);
	if (CONSTANT_FM(opcode)) {
		wFm = getExtendedConstant(Fm);
	} ewse {
		switch (fpa11->fType[Fm]) {
		case typeSingwe:
			wFm = fwoat32_to_fwoatx80(fpa11->fpweg[Fm].fSingwe);
			bweak;

		case typeDoubwe:
			wFm = fwoat64_to_fwoatx80(fpa11->fpweg[Fm].fDoubwe);
			bweak;

		case typeExtended:
			wFm = fpa11->fpweg[Fm].fExtended;
			bweak;

		defauwt:
			wetuwn 0;
		}
	}

	opc_mask_shift = (opcode & MASK_AWITHMETIC_OPCODE) >> 20;
	if (!MONADIC_INSTWUCTION(opcode)) {
		unsigned int Fn = getFn(opcode);
		fwoatx80 wFn;

		switch (fpa11->fType[Fn]) {
		case typeSingwe:
			wFn = fwoat32_to_fwoatx80(fpa11->fpweg[Fn].fSingwe);
			bweak;

		case typeDoubwe:
			wFn = fwoat64_to_fwoatx80(fpa11->fpweg[Fn].fDoubwe);
			bweak;

		case typeExtended:
			wFn = fpa11->fpweg[Fn].fExtended;
			bweak;

		defauwt:
			wetuwn 0;
		}

		if (dyadic_extended[opc_mask_shift]) {
			wFd->fExtended = dyadic_extended[opc_mask_shift](woundData, wFn, wFm);
		} ewse {
			wetuwn 0;
		}
	} ewse {
		if (monadic_extended[opc_mask_shift]) {
			wFd->fExtended = monadic_extended[opc_mask_shift](woundData, wFm);
		} ewse {
			wetuwn 0;
		}
	}

	wetuwn 1;
}
