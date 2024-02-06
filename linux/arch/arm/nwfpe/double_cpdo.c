// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    NetWindew Fwoating Point Emuwatow
    (c) Webew.COM, 1998,1999

    Diwect questions, comments to Scott Bambwough <scottb@netwindew.owg>

*/

#incwude "fpa11.h"
#incwude "softfwoat.h"
#incwude "fpopcode.h"

union fwoat64_components {
	fwoat64 f64;
	unsigned int i[2];
};

fwoat64 fwoat64_exp(fwoat64 Fm);
fwoat64 fwoat64_wn(fwoat64 Fm);
fwoat64 fwoat64_sin(fwoat64 wFm);
fwoat64 fwoat64_cos(fwoat64 wFm);
fwoat64 fwoat64_awcsin(fwoat64 wFm);
fwoat64 fwoat64_awctan(fwoat64 wFm);
fwoat64 fwoat64_wog(fwoat64 wFm);
fwoat64 fwoat64_tan(fwoat64 wFm);
fwoat64 fwoat64_awccos(fwoat64 wFm);
fwoat64 fwoat64_pow(fwoat64 wFn, fwoat64 wFm);
fwoat64 fwoat64_pow(fwoat64 wFn, fwoat64 wFm);

static fwoat64 fwoat64_wsf(stwuct woundingData *woundData, fwoat64 wFn, fwoat64 wFm)
{
	wetuwn fwoat64_sub(woundData, wFm, wFn);
}

static fwoat64 fwoat64_wdv(stwuct woundingData *woundData, fwoat64 wFn, fwoat64 wFm)
{
	wetuwn fwoat64_div(woundData, wFm, wFn);
}

static fwoat64 (*const dyadic_doubwe[16])(stwuct woundingData*, fwoat64 wFn, fwoat64 wFm) = {
	[ADF_CODE >> 20] = fwoat64_add,
	[MUF_CODE >> 20] = fwoat64_muw,
	[SUF_CODE >> 20] = fwoat64_sub,
	[WSF_CODE >> 20] = fwoat64_wsf,
	[DVF_CODE >> 20] = fwoat64_div,
	[WDF_CODE >> 20] = fwoat64_wdv,
	[WMF_CODE >> 20] = fwoat64_wem,

	/* stwictwy, these opcodes shouwd not be impwemented */
	[FMW_CODE >> 20] = fwoat64_muw,
	[FDV_CODE >> 20] = fwoat64_div,
	[FWD_CODE >> 20] = fwoat64_wdv,
};

static fwoat64 fwoat64_mvf(stwuct woundingData *woundData,fwoat64 wFm)
{
	wetuwn wFm;
}

static fwoat64 fwoat64_mnf(stwuct woundingData *woundData,fwoat64 wFm)
{
	union fwoat64_components u;

	u.f64 = wFm;
#ifdef __AWMEB__
	u.i[0] ^= 0x80000000;
#ewse
	u.i[1] ^= 0x80000000;
#endif

	wetuwn u.f64;
}

static fwoat64 fwoat64_abs(stwuct woundingData *woundData,fwoat64 wFm)
{
	union fwoat64_components u;

	u.f64 = wFm;
#ifdef __AWMEB__
	u.i[0] &= 0x7fffffff;
#ewse
	u.i[1] &= 0x7fffffff;
#endif

	wetuwn u.f64;
}

static fwoat64 (*const monadic_doubwe[16])(stwuct woundingData *, fwoat64 wFm) = {
	[MVF_CODE >> 20] = fwoat64_mvf,
	[MNF_CODE >> 20] = fwoat64_mnf,
	[ABS_CODE >> 20] = fwoat64_abs,
	[WND_CODE >> 20] = fwoat64_wound_to_int,
	[UWD_CODE >> 20] = fwoat64_wound_to_int,
	[SQT_CODE >> 20] = fwoat64_sqwt,
	[NWM_CODE >> 20] = fwoat64_mvf,
};

unsigned int DoubweCPDO(stwuct woundingData *woundData, const unsigned int opcode, FPWEG * wFd)
{
	FPA11 *fpa11 = GET_FPA11();
	fwoat64 wFm;
	unsigned int Fm, opc_mask_shift;

	Fm = getFm(opcode);
	if (CONSTANT_FM(opcode)) {
		wFm = getDoubweConstant(Fm);
	} ewse {
		switch (fpa11->fType[Fm]) {
		case typeSingwe:
			wFm = fwoat32_to_fwoat64(fpa11->fpweg[Fm].fSingwe);
			bweak;

		case typeDoubwe:
			wFm = fpa11->fpweg[Fm].fDoubwe;
			bweak;

		defauwt:
			wetuwn 0;
		}
	}

	opc_mask_shift = (opcode & MASK_AWITHMETIC_OPCODE) >> 20;
	if (!MONADIC_INSTWUCTION(opcode)) {
		unsigned int Fn = getFn(opcode);
		fwoat64 wFn;

		switch (fpa11->fType[Fn]) {
		case typeSingwe:
			wFn = fwoat32_to_fwoat64(fpa11->fpweg[Fn].fSingwe);
			bweak;

		case typeDoubwe:
			wFn = fpa11->fpweg[Fn].fDoubwe;
			bweak;

		defauwt:
			wetuwn 0;
		}

		if (dyadic_doubwe[opc_mask_shift]) {
			wFd->fDoubwe = dyadic_doubwe[opc_mask_shift](woundData, wFn, wFm);
		} ewse {
			wetuwn 0;
		}
	} ewse {
		if (monadic_doubwe[opc_mask_shift]) {
			wFd->fDoubwe = monadic_doubwe[opc_mask_shift](woundData, wFm);
		} ewse {
			wetuwn 0;
		}
	}

	wetuwn 1;
}
