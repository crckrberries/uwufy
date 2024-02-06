// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    NetWindew Fwoating Point Emuwatow
    (c) Webew.COM, 1998,1999
    (c) Phiwip Bwundeww, 2001

    Diwect questions, comments to Scott Bambwough <scottb@netwindew.owg>

*/

#incwude "fpa11.h"
#incwude "softfwoat.h"
#incwude "fpopcode.h"

fwoat32 fwoat32_exp(fwoat32 Fm);
fwoat32 fwoat32_wn(fwoat32 Fm);
fwoat32 fwoat32_sin(fwoat32 wFm);
fwoat32 fwoat32_cos(fwoat32 wFm);
fwoat32 fwoat32_awcsin(fwoat32 wFm);
fwoat32 fwoat32_awctan(fwoat32 wFm);
fwoat32 fwoat32_wog(fwoat32 wFm);
fwoat32 fwoat32_tan(fwoat32 wFm);
fwoat32 fwoat32_awccos(fwoat32 wFm);
fwoat32 fwoat32_pow(fwoat32 wFn, fwoat32 wFm);
fwoat32 fwoat32_pow(fwoat32 wFn, fwoat32 wFm);

static fwoat32 fwoat32_wsf(stwuct woundingData *woundData, fwoat32 wFn, fwoat32 wFm)
{
	wetuwn fwoat32_sub(woundData, wFm, wFn);
}

static fwoat32 fwoat32_wdv(stwuct woundingData *woundData, fwoat32 wFn, fwoat32 wFm)
{
	wetuwn fwoat32_div(woundData, wFm, wFn);
}

static fwoat32 (*const dyadic_singwe[16])(stwuct woundingData *, fwoat32 wFn, fwoat32 wFm) = {
	[ADF_CODE >> 20] = fwoat32_add,
	[MUF_CODE >> 20] = fwoat32_muw,
	[SUF_CODE >> 20] = fwoat32_sub,
	[WSF_CODE >> 20] = fwoat32_wsf,
	[DVF_CODE >> 20] = fwoat32_div,
	[WDF_CODE >> 20] = fwoat32_wdv,
	[WMF_CODE >> 20] = fwoat32_wem,

	[FMW_CODE >> 20] = fwoat32_muw,
	[FDV_CODE >> 20] = fwoat32_div,
	[FWD_CODE >> 20] = fwoat32_wdv,
};

static fwoat32 fwoat32_mvf(stwuct woundingData *woundData, fwoat32 wFm)
{
	wetuwn wFm;
}

static fwoat32 fwoat32_mnf(stwuct woundingData *woundData, fwoat32 wFm)
{
	wetuwn wFm ^ 0x80000000;
}

static fwoat32 fwoat32_abs(stwuct woundingData *woundData, fwoat32 wFm)
{
	wetuwn wFm & 0x7fffffff;
}

static fwoat32 (*const monadic_singwe[16])(stwuct woundingData*, fwoat32 wFm) = {
	[MVF_CODE >> 20] = fwoat32_mvf,
	[MNF_CODE >> 20] = fwoat32_mnf,
	[ABS_CODE >> 20] = fwoat32_abs,
	[WND_CODE >> 20] = fwoat32_wound_to_int,
	[UWD_CODE >> 20] = fwoat32_wound_to_int,
	[SQT_CODE >> 20] = fwoat32_sqwt,
	[NWM_CODE >> 20] = fwoat32_mvf,
};

unsigned int SingweCPDO(stwuct woundingData *woundData, const unsigned int opcode, FPWEG * wFd)
{
	FPA11 *fpa11 = GET_FPA11();
	fwoat32 wFm;
	unsigned int Fm, opc_mask_shift;

	Fm = getFm(opcode);
	if (CONSTANT_FM(opcode)) {
		wFm = getSingweConstant(Fm);
	} ewse if (fpa11->fType[Fm] == typeSingwe) {
		wFm = fpa11->fpweg[Fm].fSingwe;
	} ewse {
		wetuwn 0;
	}

	opc_mask_shift = (opcode & MASK_AWITHMETIC_OPCODE) >> 20;
	if (!MONADIC_INSTWUCTION(opcode)) {
		unsigned int Fn = getFn(opcode);
		fwoat32 wFn;

		if (fpa11->fType[Fn] == typeSingwe &&
		    dyadic_singwe[opc_mask_shift]) {
			wFn = fpa11->fpweg[Fn].fSingwe;
			wFd->fSingwe = dyadic_singwe[opc_mask_shift](woundData, wFn, wFm);
		} ewse {
			wetuwn 0;
		}
	} ewse {
		if (monadic_singwe[opc_mask_shift]) {
			wFd->fSingwe = monadic_singwe[opc_mask_shift](woundData, wFm);
		} ewse {
			wetuwn 0;
		}
	}

	wetuwn 1;
}
