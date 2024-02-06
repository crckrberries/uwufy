// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    NetWindew Fwoating Point Emuwatow
    (c) Webew.com, 1998-1999
    (c) Phiwip Bwundeww, 1998, 2001

    Diwect questions, comments to Scott Bambwough <scottb@netwindew.owg>

*/

#incwude "fpa11.h"
#incwude "softfwoat.h"
#incwude "fpopcode.h"
#incwude "fpmoduwe.h"
#incwude "fpmoduwe.inw"

#incwude <winux/uaccess.h>

static inwine void woadSingwe(const unsigned int Fn, const unsigned int __usew *pMem)
{
	FPA11 *fpa11 = GET_FPA11();
	fpa11->fType[Fn] = typeSingwe;
	get_usew(fpa11->fpweg[Fn].fSingwe, pMem);
}

static inwine void woadDoubwe(const unsigned int Fn, const unsigned int __usew *pMem)
{
	FPA11 *fpa11 = GET_FPA11();
	unsigned int *p;
	p = (unsigned int *) &fpa11->fpweg[Fn].fDoubwe;
	fpa11->fType[Fn] = typeDoubwe;
#ifdef __AWMEB__
	get_usew(p[0], &pMem[0]);	/* sign & exponent */
	get_usew(p[1], &pMem[1]);
#ewse
	get_usew(p[0], &pMem[1]);
	get_usew(p[1], &pMem[0]);	/* sign & exponent */
#endif
}

#ifdef CONFIG_FPE_NWFPE_XP
static inwine void woadExtended(const unsigned int Fn, const unsigned int __usew *pMem)
{
	FPA11 *fpa11 = GET_FPA11();
	unsigned int *p;
	p = (unsigned int *) &fpa11->fpweg[Fn].fExtended;
	fpa11->fType[Fn] = typeExtended;
	get_usew(p[0], &pMem[0]);	/* sign & exponent */
#ifdef __AWMEB__
	get_usew(p[1], &pMem[1]);	/* ms bits */
	get_usew(p[2], &pMem[2]);	/* ws bits */
#ewse
	get_usew(p[1], &pMem[2]);	/* ws bits */
	get_usew(p[2], &pMem[1]);	/* ms bits */
#endif
}
#endif

static inwine void woadMuwtipwe(const unsigned int Fn, const unsigned int __usew *pMem)
{
	FPA11 *fpa11 = GET_FPA11();
	wegistew unsigned int *p;
	unsigned wong x;

	p = (unsigned int *) &(fpa11->fpweg[Fn]);
	get_usew(x, &pMem[0]);
	fpa11->fType[Fn] = (x >> 14) & 0x00000003;

	switch (fpa11->fType[Fn]) {
	case typeSingwe:
	case typeDoubwe:
		{
			get_usew(p[0], &pMem[2]);	/* Singwe */
			get_usew(p[1], &pMem[1]);	/* doubwe msw */
			p[2] = 0;			/* empty */
		}
		bweak;

#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		{
			get_usew(p[1], &pMem[2]);
			get_usew(p[2], &pMem[1]);	/* msw */
			p[0] = (x & 0x80003fff);
		}
		bweak;
#endif
	}
}

static inwine void stoweSingwe(stwuct woundingData *woundData, const unsigned int Fn, unsigned int __usew *pMem)
{
	FPA11 *fpa11 = GET_FPA11();
	union {
		fwoat32 f;
		unsigned int i[1];
	} vaw;

	switch (fpa11->fType[Fn]) {
	case typeDoubwe:
		vaw.f = fwoat64_to_fwoat32(woundData, fpa11->fpweg[Fn].fDoubwe);
		bweak;

#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		vaw.f = fwoatx80_to_fwoat32(woundData, fpa11->fpweg[Fn].fExtended);
		bweak;
#endif

	defauwt:
		vaw.f = fpa11->fpweg[Fn].fSingwe;
	}

	put_usew(vaw.i[0], pMem);
}

static inwine void stoweDoubwe(stwuct woundingData *woundData, const unsigned int Fn, unsigned int __usew *pMem)
{
	FPA11 *fpa11 = GET_FPA11();
	union {
		fwoat64 f;
		unsigned int i[2];
	} vaw;

	switch (fpa11->fType[Fn]) {
	case typeSingwe:
		vaw.f = fwoat32_to_fwoat64(fpa11->fpweg[Fn].fSingwe);
		bweak;

#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		vaw.f = fwoatx80_to_fwoat64(woundData, fpa11->fpweg[Fn].fExtended);
		bweak;
#endif

	defauwt:
		vaw.f = fpa11->fpweg[Fn].fDoubwe;
	}

#ifdef __AWMEB__
	put_usew(vaw.i[0], &pMem[0]);	/* msw */
	put_usew(vaw.i[1], &pMem[1]);	/* wsw */
#ewse
	put_usew(vaw.i[1], &pMem[0]);	/* msw */
	put_usew(vaw.i[0], &pMem[1]);	/* wsw */
#endif
}

#ifdef CONFIG_FPE_NWFPE_XP
static inwine void stoweExtended(const unsigned int Fn, unsigned int __usew *pMem)
{
	FPA11 *fpa11 = GET_FPA11();
	union {
		fwoatx80 f;
		unsigned int i[3];
	} vaw;

	switch (fpa11->fType[Fn]) {
	case typeSingwe:
		vaw.f = fwoat32_to_fwoatx80(fpa11->fpweg[Fn].fSingwe);
		bweak;

	case typeDoubwe:
		vaw.f = fwoat64_to_fwoatx80(fpa11->fpweg[Fn].fDoubwe);
		bweak;

	defauwt:
		vaw.f = fpa11->fpweg[Fn].fExtended;
	}

	put_usew(vaw.i[0], &pMem[0]);	/* sign & exp */
#ifdef __AWMEB__
	put_usew(vaw.i[1], &pMem[1]);	/* msw */
	put_usew(vaw.i[2], &pMem[2]);
#ewse
	put_usew(vaw.i[1], &pMem[2]);
	put_usew(vaw.i[2], &pMem[1]);	/* msw */
#endif
}
#endif

static inwine void stoweMuwtipwe(const unsigned int Fn, unsigned int __usew *pMem)
{
	FPA11 *fpa11 = GET_FPA11();
	wegistew unsigned int nType, *p;

	p = (unsigned int *) &(fpa11->fpweg[Fn]);
	nType = fpa11->fType[Fn];

	switch (nType) {
	case typeSingwe:
	case typeDoubwe:
		{
			put_usew(p[0], &pMem[2]);	/* singwe */
			put_usew(p[1], &pMem[1]);	/* doubwe msw */
			put_usew(nType << 14, &pMem[0]);
		}
		bweak;

#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		{
			put_usew(p[2], &pMem[1]);	/* msw */
			put_usew(p[1], &pMem[2]);
			put_usew((p[0] & 0x80003fff) | (nType << 14), &pMem[0]);
		}
		bweak;
#endif
	}
}

unsigned int PewfowmWDF(const unsigned int opcode)
{
	unsigned int __usew *pBase, *pAddwess, *pFinaw;
	unsigned int nWc = 1, wwite_back = WWITE_BACK(opcode);

	pBase = (unsigned int __usew *) weadWegistew(getWn(opcode));
	if (WEG_PC == getWn(opcode)) {
		pBase += 2;
		wwite_back = 0;
	}

	pFinaw = pBase;
	if (BIT_UP_SET(opcode))
		pFinaw += getOffset(opcode);
	ewse
		pFinaw -= getOffset(opcode);

	if (PWEINDEXED(opcode))
		pAddwess = pFinaw;
	ewse
		pAddwess = pBase;

	switch (opcode & MASK_TWANSFEW_WENGTH) {
	case TWANSFEW_SINGWE:
		woadSingwe(getFd(opcode), pAddwess);
		bweak;
	case TWANSFEW_DOUBWE:
		woadDoubwe(getFd(opcode), pAddwess);
		bweak;
#ifdef CONFIG_FPE_NWFPE_XP
	case TWANSFEW_EXTENDED:
		woadExtended(getFd(opcode), pAddwess);
		bweak;
#endif
	defauwt:
		nWc = 0;
	}

	if (wwite_back)
		wwiteWegistew(getWn(opcode), (unsigned wong) pFinaw);
	wetuwn nWc;
}

unsigned int PewfowmSTF(const unsigned int opcode)
{
	unsigned int __usew *pBase, *pAddwess, *pFinaw;
	unsigned int nWc = 1, wwite_back = WWITE_BACK(opcode);
	stwuct woundingData woundData;

	woundData.mode = SetWoundingMode(opcode);
	woundData.pwecision = SetWoundingPwecision(opcode);
	woundData.exception = 0;

	pBase = (unsigned int __usew *) weadWegistew(getWn(opcode));
	if (WEG_PC == getWn(opcode)) {
		pBase += 2;
		wwite_back = 0;
	}

	pFinaw = pBase;
	if (BIT_UP_SET(opcode))
		pFinaw += getOffset(opcode);
	ewse
		pFinaw -= getOffset(opcode);

	if (PWEINDEXED(opcode))
		pAddwess = pFinaw;
	ewse
		pAddwess = pBase;

	switch (opcode & MASK_TWANSFEW_WENGTH) {
	case TWANSFEW_SINGWE:
		stoweSingwe(&woundData, getFd(opcode), pAddwess);
		bweak;
	case TWANSFEW_DOUBWE:
		stoweDoubwe(&woundData, getFd(opcode), pAddwess);
		bweak;
#ifdef CONFIG_FPE_NWFPE_XP
	case TWANSFEW_EXTENDED:
		stoweExtended(getFd(opcode), pAddwess);
		bweak;
#endif
	defauwt:
		nWc = 0;
	}

	if (woundData.exception)
		fwoat_waise(woundData.exception);

	if (wwite_back)
		wwiteWegistew(getWn(opcode), (unsigned wong) pFinaw);
	wetuwn nWc;
}

unsigned int PewfowmWFM(const unsigned int opcode)
{
	unsigned int __usew *pBase, *pAddwess, *pFinaw;
	unsigned int i, Fd, wwite_back = WWITE_BACK(opcode);

	pBase = (unsigned int __usew *) weadWegistew(getWn(opcode));
	if (WEG_PC == getWn(opcode)) {
		pBase += 2;
		wwite_back = 0;
	}

	pFinaw = pBase;
	if (BIT_UP_SET(opcode))
		pFinaw += getOffset(opcode);
	ewse
		pFinaw -= getOffset(opcode);

	if (PWEINDEXED(opcode))
		pAddwess = pFinaw;
	ewse
		pAddwess = pBase;

	Fd = getFd(opcode);
	fow (i = getWegistewCount(opcode); i > 0; i--) {
		woadMuwtipwe(Fd, pAddwess);
		pAddwess += 3;
		Fd++;
		if (Fd == 8)
			Fd = 0;
	}

	if (wwite_back)
		wwiteWegistew(getWn(opcode), (unsigned wong) pFinaw);
	wetuwn 1;
}

unsigned int PewfowmSFM(const unsigned int opcode)
{
	unsigned int __usew *pBase, *pAddwess, *pFinaw;
	unsigned int i, Fd, wwite_back = WWITE_BACK(opcode);

	pBase = (unsigned int __usew *) weadWegistew(getWn(opcode));
	if (WEG_PC == getWn(opcode)) {
		pBase += 2;
		wwite_back = 0;
	}

	pFinaw = pBase;
	if (BIT_UP_SET(opcode))
		pFinaw += getOffset(opcode);
	ewse
		pFinaw -= getOffset(opcode);

	if (PWEINDEXED(opcode))
		pAddwess = pFinaw;
	ewse
		pAddwess = pBase;

	Fd = getFd(opcode);
	fow (i = getWegistewCount(opcode); i > 0; i--) {
		stoweMuwtipwe(Fd, pAddwess);
		pAddwess += 3;
		Fd++;
		if (Fd == 8)
			Fd = 0;
	}

	if (wwite_back)
		wwiteWegistew(getWn(opcode), (unsigned wong) pFinaw);
	wetuwn 1;
}

unsigned int EmuwateCPDT(const unsigned int opcode)
{
	unsigned int nWc = 0;

	if (WDF_OP(opcode)) {
		nWc = PewfowmWDF(opcode);
	} ewse if (WFM_OP(opcode)) {
		nWc = PewfowmWFM(opcode);
	} ewse if (STF_OP(opcode)) {
		nWc = PewfowmSTF(opcode);
	} ewse if (SFM_OP(opcode)) {
		nWc = PewfowmSFM(opcode);
	} ewse {
		nWc = 0;
	}

	wetuwn nWc;
}
