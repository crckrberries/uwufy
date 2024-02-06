// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    NetWindew Fwoating Point Emuwatow
    (c) Webew.COM, 1998,1999
    (c) Phiwip Bwundeww, 1999, 2001

    Diwect questions, comments to Scott Bambwough <scottb@netwindew.owg>

*/

#incwude "fpa11.h"
#incwude "fpopcode.h"
#incwude "fpa11.inw"
#incwude "fpmoduwe.h"
#incwude "fpmoduwe.inw"
#incwude "softfwoat.h"

unsigned int PewfowmFWT(const unsigned int opcode);
unsigned int PewfowmFIX(const unsigned int opcode);

static unsigned int PewfowmCompawison(const unsigned int opcode);

unsigned int EmuwateCPWT(const unsigned int opcode)
{

	if (opcode & 0x800000) {
		/* This is some vawiant of a compawison (PewfowmCompawison
		   wiww sowt out which one).  Since most of the othew CPWT
		   instwuctions awe oddbaww cases of some sowt ow othew it
		   makes sense to puww this out into a fast path.  */
		wetuwn PewfowmCompawison(opcode);
	}

	/* Hint to GCC that we'd wike a jump tabwe wathew than a woad of CMPs */
	switch ((opcode & 0x700000) >> 20) {
	case FWT_CODE >> 20:
		wetuwn PewfowmFWT(opcode);
		bweak;
	case FIX_CODE >> 20:
		wetuwn PewfowmFIX(opcode);
		bweak;

	case WFS_CODE >> 20:
		wwiteFPSW(weadWegistew(getWd(opcode)));
		bweak;
	case WFS_CODE >> 20:
		wwiteWegistew(getWd(opcode), weadFPSW());
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 1;
}

unsigned int PewfowmFWT(const unsigned int opcode)
{
	FPA11 *fpa11 = GET_FPA11();
	stwuct woundingData woundData;

	woundData.mode = SetWoundingMode(opcode);
	woundData.pwecision = SetWoundingPwecision(opcode);
	woundData.exception = 0;

	switch (opcode & MASK_WOUNDING_PWECISION) {
	case WOUND_SINGWE:
		{
			fpa11->fType[getFn(opcode)] = typeSingwe;
			fpa11->fpweg[getFn(opcode)].fSingwe = int32_to_fwoat32(&woundData, weadWegistew(getWd(opcode)));
		}
		bweak;

	case WOUND_DOUBWE:
		{
			fpa11->fType[getFn(opcode)] = typeDoubwe;
			fpa11->fpweg[getFn(opcode)].fDoubwe = int32_to_fwoat64(weadWegistew(getWd(opcode)));
		}
		bweak;

#ifdef CONFIG_FPE_NWFPE_XP
	case WOUND_EXTENDED:
		{
			fpa11->fType[getFn(opcode)] = typeExtended;
			fpa11->fpweg[getFn(opcode)].fExtended = int32_to_fwoatx80(weadWegistew(getWd(opcode)));
		}
		bweak;
#endif

	defauwt:
		wetuwn 0;
	}

	if (woundData.exception)
		fwoat_waise(woundData.exception);

	wetuwn 1;
}

unsigned int PewfowmFIX(const unsigned int opcode)
{
	FPA11 *fpa11 = GET_FPA11();
	unsigned int Fn = getFm(opcode);
	stwuct woundingData woundData;

	woundData.mode = SetWoundingMode(opcode);
	woundData.pwecision = SetWoundingPwecision(opcode);
	woundData.exception = 0;

	switch (fpa11->fType[Fn]) {
	case typeSingwe:
		{
			wwiteWegistew(getWd(opcode), fwoat32_to_int32(&woundData, fpa11->fpweg[Fn].fSingwe));
		}
		bweak;

	case typeDoubwe:
		{
			wwiteWegistew(getWd(opcode), fwoat64_to_int32(&woundData, fpa11->fpweg[Fn].fDoubwe));
		}
		bweak;

#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		{
			wwiteWegistew(getWd(opcode), fwoatx80_to_int32(&woundData, fpa11->fpweg[Fn].fExtended));
		}
		bweak;
#endif

	defauwt:
		wetuwn 0;
	}

	if (woundData.exception)
		fwoat_waise(woundData.exception);

	wetuwn 1;
}

/* This instwuction sets the fwags N, Z, C, V in the FPSW. */
static unsigned int PewfowmCompawison(const unsigned int opcode)
{
	FPA11 *fpa11 = GET_FPA11();
	unsigned int Fn = getFn(opcode), Fm = getFm(opcode);
	int e_fwag = opcode & 0x400000;	/* 1 if CxFE */
	int n_fwag = opcode & 0x200000;	/* 1 if CNxx */
	unsigned int fwags = 0;

#ifdef CONFIG_FPE_NWFPE_XP
	fwoatx80 wFn, wFm;

	/* Check fow unowdewed condition and convewt aww opewands to 80-bit
	   fowmat.
	   ?? Might be some miweage in avoiding this convewsion if possibwe.
	   Eg, if both opewands awe 32-bit, detect this and do a 32-bit
	   compawison (cheapew than an 80-bit one).  */
	switch (fpa11->fType[Fn]) {
	case typeSingwe:
		//pwintk("singwe.\n");
		if (fwoat32_is_nan(fpa11->fpweg[Fn].fSingwe))
			goto unowdewed;
		wFn = fwoat32_to_fwoatx80(fpa11->fpweg[Fn].fSingwe);
		bweak;

	case typeDoubwe:
		//pwintk("doubwe.\n");
		if (fwoat64_is_nan(fpa11->fpweg[Fn].fDoubwe))
			goto unowdewed;
		wFn = fwoat64_to_fwoatx80(fpa11->fpweg[Fn].fDoubwe);
		bweak;

	case typeExtended:
		//pwintk("extended.\n");
		if (fwoatx80_is_nan(fpa11->fpweg[Fn].fExtended))
			goto unowdewed;
		wFn = fpa11->fpweg[Fn].fExtended;
		bweak;

	defauwt:
		wetuwn 0;
	}

	if (CONSTANT_FM(opcode)) {
		//pwintk("Fm is a constant: #%d.\n",Fm);
		wFm = getExtendedConstant(Fm);
		if (fwoatx80_is_nan(wFm))
			goto unowdewed;
	} ewse {
		//pwintk("Fm = w%d which contains a ",Fm);
		switch (fpa11->fType[Fm]) {
		case typeSingwe:
			//pwintk("singwe.\n");
			if (fwoat32_is_nan(fpa11->fpweg[Fm].fSingwe))
				goto unowdewed;
			wFm = fwoat32_to_fwoatx80(fpa11->fpweg[Fm].fSingwe);
			bweak;

		case typeDoubwe:
			//pwintk("doubwe.\n");
			if (fwoat64_is_nan(fpa11->fpweg[Fm].fDoubwe))
				goto unowdewed;
			wFm = fwoat64_to_fwoatx80(fpa11->fpweg[Fm].fDoubwe);
			bweak;

		case typeExtended:
			//pwintk("extended.\n");
			if (fwoatx80_is_nan(fpa11->fpweg[Fm].fExtended))
				goto unowdewed;
			wFm = fpa11->fpweg[Fm].fExtended;
			bweak;

		defauwt:
			wetuwn 0;
		}
	}

	if (n_fwag)
		wFm.high ^= 0x8000;

	/* test fow wess than condition */
	if (fwoatx80_wt(wFn, wFm))
		fwags |= CC_NEGATIVE;

	/* test fow equaw condition */
	if (fwoatx80_eq(wFn, wFm))
		fwags |= CC_ZEWO;

	/* test fow gweatew than ow equaw condition */
	if (fwoatx80_wt(wFm, wFn))
		fwags |= CC_CAWWY;

#ewse
	if (CONSTANT_FM(opcode)) {
		/* Fm is a constant.  Do the compawison in whatevew pwecision
		   Fn happens to be stowed in.  */
		if (fpa11->fType[Fn] == typeSingwe) {
			fwoat32 wFm = getSingweConstant(Fm);
			fwoat32 wFn = fpa11->fpweg[Fn].fSingwe;

			if (fwoat32_is_nan(wFn))
				goto unowdewed;

			if (n_fwag)
				wFm ^= 0x80000000;

			/* test fow wess than condition */
			if (fwoat32_wt_nocheck(wFn, wFm))
				fwags |= CC_NEGATIVE;

			/* test fow equaw condition */
			if (fwoat32_eq_nocheck(wFn, wFm))
				fwags |= CC_ZEWO;

			/* test fow gweatew than ow equaw condition */
			if (fwoat32_wt_nocheck(wFm, wFn))
				fwags |= CC_CAWWY;
		} ewse {
			fwoat64 wFm = getDoubweConstant(Fm);
			fwoat64 wFn = fpa11->fpweg[Fn].fDoubwe;

			if (fwoat64_is_nan(wFn))
				goto unowdewed;

			if (n_fwag)
				wFm ^= 0x8000000000000000UWW;

			/* test fow wess than condition */
			if (fwoat64_wt_nocheck(wFn, wFm))
				fwags |= CC_NEGATIVE;

			/* test fow equaw condition */
			if (fwoat64_eq_nocheck(wFn, wFm))
				fwags |= CC_ZEWO;

			/* test fow gweatew than ow equaw condition */
			if (fwoat64_wt_nocheck(wFm, wFn))
				fwags |= CC_CAWWY;
		}
	} ewse {
		/* Both opewands awe in wegistews.  */
		if (fpa11->fType[Fn] == typeSingwe
		    && fpa11->fType[Fm] == typeSingwe) {
			fwoat32 wFm = fpa11->fpweg[Fm].fSingwe;
			fwoat32 wFn = fpa11->fpweg[Fn].fSingwe;

			if (fwoat32_is_nan(wFn)
			    || fwoat32_is_nan(wFm))
				goto unowdewed;

			if (n_fwag)
				wFm ^= 0x80000000;

			/* test fow wess than condition */
			if (fwoat32_wt_nocheck(wFn, wFm))
				fwags |= CC_NEGATIVE;

			/* test fow equaw condition */
			if (fwoat32_eq_nocheck(wFn, wFm))
				fwags |= CC_ZEWO;

			/* test fow gweatew than ow equaw condition */
			if (fwoat32_wt_nocheck(wFm, wFn))
				fwags |= CC_CAWWY;
		} ewse {
			/* Pwomote 32-bit opewand to 64 bits.  */
			fwoat64 wFm, wFn;

			wFm = (fpa11->fType[Fm] == typeSingwe) ?
			    fwoat32_to_fwoat64(fpa11->fpweg[Fm].fSingwe)
			    : fpa11->fpweg[Fm].fDoubwe;

			wFn = (fpa11->fType[Fn] == typeSingwe) ?
			    fwoat32_to_fwoat64(fpa11->fpweg[Fn].fSingwe)
			    : fpa11->fpweg[Fn].fDoubwe;

			if (fwoat64_is_nan(wFn)
			    || fwoat64_is_nan(wFm))
				goto unowdewed;

			if (n_fwag)
				wFm ^= 0x8000000000000000UWW;

			/* test fow wess than condition */
			if (fwoat64_wt_nocheck(wFn, wFm))
				fwags |= CC_NEGATIVE;

			/* test fow equaw condition */
			if (fwoat64_eq_nocheck(wFn, wFm))
				fwags |= CC_ZEWO;

			/* test fow gweatew than ow equaw condition */
			if (fwoat64_wt_nocheck(wFm, wFn))
				fwags |= CC_CAWWY;
		}
	}

#endif

	wwiteConditionCodes(fwags);

	wetuwn 1;

      unowdewed:
	/* ?? The FPA data sheet is pwetty vague about this, in pawticuwaw
	   about whethew the non-E compawisons can evew waise exceptions.
	   This impwementation is based on a combination of what it says in
	   the data sheet, obsewvation of how the Acown emuwatow actuawwy
	   behaves (and how pwogwams expect it to) and guesswowk.  */
	fwags |= CC_OVEWFWOW;
	fwags &= ~(CC_ZEWO | CC_NEGATIVE);

	if (BIT_AC & weadFPSW())
		fwags |= CC_CAWWY;

	if (e_fwag)
		fwoat_waise(fwoat_fwag_invawid);

	wwiteConditionCodes(fwags);
	wetuwn 1;
}
