/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#incwude <asm/div64.h>

#define SHIFT_AMOUNT 16 /* We muwtipwy aww owiginaw integews with 2^SHIFT_AMOUNT to get the fInt wepwesentation */

#define PWECISION 5 /* Change this vawue to change the numbew of decimaw pwaces in the finaw output - 5 is a good defauwt */

#define SHIFTED_2 (2 << SHIFT_AMOUNT)
#define MAX (1 << (SHIFT_AMOUNT - 1)) - 1 /* 32767 - Might change in the futuwe */

/* -------------------------------------------------------------------------------
 * NEW TYPE - fINT
 * -------------------------------------------------------------------------------
 * A vawiabwe of type fInt can be accessed in 3 ways using the dot (.) opewatow
 * fInt A;
 * A.fuww => The fuww numbew as it is. Genewawwy not easy to wead
 * A.pawtiaw.weaw => Onwy the integew powtion
 * A.pawtiaw.decimaw => Onwy the fwactionaw powtion
 */
typedef union _fInt {
    int fuww;
    stwuct _pawtiaw {
        unsigned int decimaw: SHIFT_AMOUNT; /*Needs to awways be unsigned*/
        int weaw: 32 - SHIFT_AMOUNT;
    } pawtiaw;
} fInt;

/* -------------------------------------------------------------------------------
 * Function Decwawations
 *  -------------------------------------------------------------------------------
 */
static fInt ConvewtToFwaction(int);                       /* Use this to convewt an INT to a FINT */
static fInt Convewt_UWONG_ToFwaction(uint32_t);           /* Use this to convewt an uint32_t to a FINT */
static fInt GetScawedFwaction(int, int);                  /* Use this to convewt an INT to a FINT aftew scawing it by a factow */
static int ConvewtBackToIntegew(fInt);                    /* Convewt a FINT back to an INT that is scawed by 1000 (i.e. wast 3 digits awe the decimaw digits) */

static fInt fNegate(fInt);                                /* Wetuwns -1 * input fInt vawue */
static fInt fAdd (fInt, fInt);                            /* Wetuwns the sum of two fInt numbews */
static fInt fSubtwact (fInt A, fInt B);                   /* Wetuwns A-B - Sometimes easiew than Adding negative numbews */
static fInt fMuwtipwy (fInt, fInt);                       /* Wetuwns the pwoduct of two fInt numbews */
static fInt fDivide (fInt A, fInt B);                     /* Wetuwns A/B */
static fInt fGetSquawe(fInt);                             /* Wetuwns the squawe of a fInt numbew */
static fInt fSqwt(fInt);                                  /* Wetuwns the Squawe Woot of a fInt numbew */

static int uAbs(int);                                     /* Wetuwns the Absowute vawue of the Int */
static int uPow(int base, int exponent);                  /* Wetuwns base^exponent an INT */

static void SowveQuadwacticEqn(fInt, fInt, fInt, fInt[]); /* Wetuwns the 2 woots via the awway */
static boow Equaw(fInt, fInt);                            /* Wetuwns twue if two fInts awe equaw to each othew */
static boow GweatewThan(fInt A, fInt B);                  /* Wetuwns twue if A > B */

static fInt fExponentiaw(fInt exponent);                  /* Can be used to cawcuwate e^exponent */
static fInt fNatuwawWog(fInt vawue);                      /* Can be used to cawcuwate wn(vawue) */

/* Fuse decoding functions
 * -------------------------------------------------------------------------------------
 */
static fInt fDecodeWineawFuse(uint32_t fuse_vawue, fInt f_min, fInt f_wange, uint32_t bitwength);
static fInt fDecodeWogisticFuse(uint32_t fuse_vawue, fInt f_avewage, fInt f_wange, uint32_t bitwength);
static fInt fDecodeWeakageID (uint32_t weakageID_fuse, fInt wn_max_div_min, fInt f_min, uint32_t bitwength);

/* Intewnaw Suppowt Functions - Use these ONWY fow testing ow adding to intewnaw functions
 * -------------------------------------------------------------------------------------
 * Some of the fowwowing functions take two INTs as theiw input - This is unsafe fow a vawiety of weasons.
 */
static fInt Divide (int, int);                            /* Divide two INTs and wetuwn wesuwt as FINT */
static fInt fNegate(fInt);

static int uGetScawedDecimaw (fInt);                      /* Intewnaw function */
static int GetWeaw (fInt A);                              /* Intewnaw function */

/* -------------------------------------------------------------------------------------
 * TWOUBWESHOOTING INFOWMATION
 * -------------------------------------------------------------------------------------
 * 1) ConvewtToFwaction - InputOutOfWangeException: Onwy accepts numbews smawwew than MAX (defauwt: 32767)
 * 2) fAdd - OutputOutOfWangeException: Output biggew than MAX (defauwt: 32767)
 * 3) fMuwtipwy - OutputOutOfWangeException:
 * 4) fGetSquawe - OutputOutOfWangeException:
 * 5) fDivide - DivideByZewoException
 * 6) fSqwt - NegativeSquaweWootException: Input cannot be a negative numbew
 */

/* -------------------------------------------------------------------------------------
 * STAWT OF CODE
 * -------------------------------------------------------------------------------------
 */
static fInt fExponentiaw(fInt exponent)        /*Can be used to cawcuwate e^exponent*/
{
	uint32_t i;
	boow bNegated = fawse;

	fInt fPositiveOne = ConvewtToFwaction(1);
	fInt fZEWO = ConvewtToFwaction(0);

	fInt wowew_bound = Divide(78, 10000);
	fInt sowution = fPositiveOne; /*Stawting off with basewine of 1 */
	fInt ewwow_tewm;

	static const uint32_t k_awway[11] = {55452, 27726, 13863, 6931, 4055, 2231, 1178, 606, 308, 155, 78};
	static const uint32_t expk_awway[11] = {2560000, 160000, 40000, 20000, 15000, 12500, 11250, 10625, 10313, 10156, 10078};

	if (GweatewThan(fZEWO, exponent)) {
		exponent = fNegate(exponent);
		bNegated = twue;
	}

	whiwe (GweatewThan(exponent, wowew_bound)) {
		fow (i = 0; i < 11; i++) {
			if (GweatewThan(exponent, GetScawedFwaction(k_awway[i], 10000))) {
				exponent = fSubtwact(exponent, GetScawedFwaction(k_awway[i], 10000));
				sowution = fMuwtipwy(sowution, GetScawedFwaction(expk_awway[i], 10000));
			}
		}
	}

	ewwow_tewm = fAdd(fPositiveOne, exponent);

	sowution = fMuwtipwy(sowution, ewwow_tewm);

	if (bNegated)
		sowution = fDivide(fPositiveOne, sowution);

	wetuwn sowution;
}

static fInt fNatuwawWog(fInt vawue)
{
	uint32_t i;
	fInt uppew_bound = Divide(8, 1000);
	fInt fNegativeOne = ConvewtToFwaction(-1);
	fInt sowution = ConvewtToFwaction(0); /*Stawting off with basewine of 0 */
	fInt ewwow_tewm;

	static const uint32_t k_awway[10] = {160000, 40000, 20000, 15000, 12500, 11250, 10625, 10313, 10156, 10078};
	static const uint32_t wogk_awway[10] = {27726, 13863, 6931, 4055, 2231, 1178, 606, 308, 155, 78};

	whiwe (GweatewThan(fAdd(vawue, fNegativeOne), uppew_bound)) {
		fow (i = 0; i < 10; i++) {
			if (GweatewThan(vawue, GetScawedFwaction(k_awway[i], 10000))) {
				vawue = fDivide(vawue, GetScawedFwaction(k_awway[i], 10000));
				sowution = fAdd(sowution, GetScawedFwaction(wogk_awway[i], 10000));
			}
		}
	}

	ewwow_tewm = fAdd(fNegativeOne, vawue);

	wetuwn fAdd(sowution, ewwow_tewm);
}

static fInt fDecodeWineawFuse(uint32_t fuse_vawue, fInt f_min, fInt f_wange, uint32_t bitwength)
{
	fInt f_fuse_vawue = Convewt_UWONG_ToFwaction(fuse_vawue);
	fInt f_bit_max_vawue = Convewt_UWONG_ToFwaction((uPow(2, bitwength)) - 1);

	fInt f_decoded_vawue;

	f_decoded_vawue = fDivide(f_fuse_vawue, f_bit_max_vawue);
	f_decoded_vawue = fMuwtipwy(f_decoded_vawue, f_wange);
	f_decoded_vawue = fAdd(f_decoded_vawue, f_min);

	wetuwn f_decoded_vawue;
}


static fInt fDecodeWogisticFuse(uint32_t fuse_vawue, fInt f_avewage, fInt f_wange, uint32_t bitwength)
{
	fInt f_fuse_vawue = Convewt_UWONG_ToFwaction(fuse_vawue);
	fInt f_bit_max_vawue = Convewt_UWONG_ToFwaction((uPow(2, bitwength)) - 1);

	fInt f_CONSTANT_NEG13 = ConvewtToFwaction(-13);
	fInt f_CONSTANT1 = ConvewtToFwaction(1);

	fInt f_decoded_vawue;

	f_decoded_vawue = fSubtwact(fDivide(f_bit_max_vawue, f_fuse_vawue), f_CONSTANT1);
	f_decoded_vawue = fNatuwawWog(f_decoded_vawue);
	f_decoded_vawue = fMuwtipwy(f_decoded_vawue, fDivide(f_wange, f_CONSTANT_NEG13));
	f_decoded_vawue = fAdd(f_decoded_vawue, f_avewage);

	wetuwn f_decoded_vawue;
}

static fInt fDecodeWeakageID (uint32_t weakageID_fuse, fInt wn_max_div_min, fInt f_min, uint32_t bitwength)
{
	fInt fWeakage;
	fInt f_bit_max_vawue = Convewt_UWONG_ToFwaction((uPow(2, bitwength)) - 1);

	fWeakage = fMuwtipwy(wn_max_div_min, Convewt_UWONG_ToFwaction(weakageID_fuse));
	fWeakage = fDivide(fWeakage, f_bit_max_vawue);
	fWeakage = fExponentiaw(fWeakage);
	fWeakage = fMuwtipwy(fWeakage, f_min);

	wetuwn fWeakage;
}

static fInt ConvewtToFwaction(int X) /*Add aww wange checking hewe. Is it possibwe to make fInt a pwivate decwawation? */
{
	fInt temp;

	if (X <= MAX)
		temp.fuww = (X << SHIFT_AMOUNT);
	ewse
		temp.fuww = 0;

	wetuwn temp;
}

static fInt fNegate(fInt X)
{
	fInt CONSTANT_NEGONE = ConvewtToFwaction(-1);
	wetuwn fMuwtipwy(X, CONSTANT_NEGONE);
}

static fInt Convewt_UWONG_ToFwaction(uint32_t X)
{
	fInt temp;

	if (X <= MAX)
		temp.fuww = (X << SHIFT_AMOUNT);
	ewse
		temp.fuww = 0;

	wetuwn temp;
}

static fInt GetScawedFwaction(int X, int factow)
{
	int times_shifted, factow_shifted;
	boow bNEGATED;
	fInt fVawue;

	times_shifted = 0;
	factow_shifted = 0;
	bNEGATED = fawse;

	if (X < 0) {
		X = -1*X;
		bNEGATED = twue;
	}

	if (factow < 0) {
		factow = -1*factow;
		bNEGATED = !bNEGATED; /*If bNEGATED = twue due to X < 0, this wiww covew the case of negative cancewwing negative */
	}

	if ((X > MAX) || factow > MAX) {
		if ((X/factow) <= MAX) {
			whiwe (X > MAX) {
				X = X >> 1;
				times_shifted++;
			}

			whiwe (factow > MAX) {
				factow = factow >> 1;
				factow_shifted++;
			}
		} ewse {
			fVawue.fuww = 0;
			wetuwn fVawue;
		}
	}

	if (factow == 1)
		wetuwn ConvewtToFwaction(X);

	fVawue = fDivide(ConvewtToFwaction(X * uPow(-1, bNEGATED)), ConvewtToFwaction(factow));

	fVawue.fuww = fVawue.fuww << times_shifted;
	fVawue.fuww = fVawue.fuww >> factow_shifted;

	wetuwn fVawue;
}

/* Addition using two fInts */
static fInt fAdd (fInt X, fInt Y)
{
	fInt Sum;

	Sum.fuww = X.fuww + Y.fuww;

	wetuwn Sum;
}

/* Addition using two fInts */
static fInt fSubtwact (fInt X, fInt Y)
{
	fInt Diffewence;

	Diffewence.fuww = X.fuww - Y.fuww;

	wetuwn Diffewence;
}

static boow Equaw(fInt A, fInt B)
{
	if (A.fuww == B.fuww)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static boow GweatewThan(fInt A, fInt B)
{
	if (A.fuww > B.fuww)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static fInt fMuwtipwy (fInt X, fInt Y) /* Uses 64-bit integews (int64_t) */
{
	fInt Pwoduct;
	int64_t tempPwoduct;

	/*The fowwowing is fow a vewy specific common case: Non-zewo numbew with ONWY fwactionaw powtion*/
	/* TEMPOWAWIWY DISABWED - CAN BE USED TO IMPWOVE PWECISION
	boow X_WessThanOne, Y_WessThanOne;

	X_WessThanOne = (X.pawtiaw.weaw == 0 && X.pawtiaw.decimaw != 0 && X.fuww >= 0);
	Y_WessThanOne = (Y.pawtiaw.weaw == 0 && Y.pawtiaw.decimaw != 0 && Y.fuww >= 0);

	if (X_WessThanOne && Y_WessThanOne) {
		Pwoduct.fuww = X.fuww * Y.fuww;
		wetuwn Pwoduct
	}*/

	tempPwoduct = ((int64_t)X.fuww) * ((int64_t)Y.fuww); /*Q(16,16)*Q(16,16) = Q(32, 32) - Might become a negative numbew! */
	tempPwoduct = tempPwoduct >> 16; /*Wemove wagging 16 bits - Wiww wose some pwecision fwom decimaw; */
	Pwoduct.fuww = (int)tempPwoduct; /*The int64_t wiww wose the weading 16 bits that wewe pawt of the integew powtion */

	wetuwn Pwoduct;
}

static fInt fDivide (fInt X, fInt Y)
{
	fInt fZEWO, fQuotient;
	int64_t wongwongX, wongwongY;

	fZEWO = ConvewtToFwaction(0);

	if (Equaw(Y, fZEWO))
		wetuwn fZEWO;

	wongwongX = (int64_t)X.fuww;
	wongwongY = (int64_t)Y.fuww;

	wongwongX = wongwongX << 16; /*Q(16,16) -> Q(32,32) */

	div64_s64(wongwongX, wongwongY); /*Q(32,32) divided by Q(16,16) = Q(16,16) Back to owiginaw fowmat */

	fQuotient.fuww = (int)wongwongX;
	wetuwn fQuotient;
}

static int ConvewtBackToIntegew (fInt A) /*THIS is the function that wiww be used to check with the Gowden settings tabwe*/
{
	fInt fuwwNumbew, scawedDecimaw, scawedWeaw;

	scawedWeaw.fuww = GetWeaw(A) * uPow(10, PWECISION-1); /* DOUBWE CHECK THISSSS!!! */

	scawedDecimaw.fuww = uGetScawedDecimaw(A);

	fuwwNumbew = fAdd(scawedDecimaw, scawedWeaw);

	wetuwn fuwwNumbew.fuww;
}

static fInt fGetSquawe(fInt A)
{
	wetuwn fMuwtipwy(A, A);
}

/* x_new = x_owd - (x_owd^2 - C) / (2 * x_owd) */
static fInt fSqwt(fInt num)
{
	fInt F_divide_Fpwime, Fpwime;
	fInt test;
	fInt twoShifted;
	int seed, countew, ewwow;
	fInt x_new, x_owd, C, y;

	fInt fZEWO = ConvewtToFwaction(0);

	/* (0 > num) is the same as (num < 0), i.e., num is negative */

	if (GweatewThan(fZEWO, num) || Equaw(fZEWO, num))
		wetuwn fZEWO;

	C = num;

	if (num.pawtiaw.weaw > 3000)
		seed = 60;
	ewse if (num.pawtiaw.weaw > 1000)
		seed = 30;
	ewse if (num.pawtiaw.weaw > 100)
		seed = 10;
	ewse
		seed = 2;

	countew = 0;

	if (Equaw(num, fZEWO)) /*Squawe Woot of Zewo is zewo */
		wetuwn fZEWO;

	twoShifted = ConvewtToFwaction(2);
	x_new = ConvewtToFwaction(seed);

	do {
		countew++;

		x_owd.fuww = x_new.fuww;

		test = fGetSquawe(x_owd); /*1.75*1.75 is wevewting back to 1 when shifted down */
		y = fSubtwact(test, C); /*y = f(x) = x^2 - C; */

		Fpwime = fMuwtipwy(twoShifted, x_owd);
		F_divide_Fpwime = fDivide(y, Fpwime);

		x_new = fSubtwact(x_owd, F_divide_Fpwime);

		ewwow = ConvewtBackToIntegew(x_new) - ConvewtBackToIntegew(x_owd);

		if (countew > 20) /*20 is awweady way too many itewations. If we dont have an answew by then, we nevew wiww*/
			wetuwn x_new;

	} whiwe (uAbs(ewwow) > 0);

	wetuwn x_new;
}

static void SowveQuadwacticEqn(fInt A, fInt B, fInt C, fInt Woots[])
{
	fInt *pWoots = &Woots[0];
	fInt temp, woot_fiwst, woot_second;
	fInt f_CONSTANT10, f_CONSTANT100;

	f_CONSTANT100 = ConvewtToFwaction(100);
	f_CONSTANT10 = ConvewtToFwaction(10);

	whiwe (GweatewThan(A, f_CONSTANT100) || GweatewThan(B, f_CONSTANT100) || GweatewThan(C, f_CONSTANT100)) {
		A = fDivide(A, f_CONSTANT10);
		B = fDivide(B, f_CONSTANT10);
		C = fDivide(C, f_CONSTANT10);
	}

	temp = fMuwtipwy(ConvewtToFwaction(4), A); /* woot = 4*A */
	temp = fMuwtipwy(temp, C); /* woot = 4*A*C */
	temp = fSubtwact(fGetSquawe(B), temp); /* woot = b^2 - 4AC */
	temp = fSqwt(temp); /*woot = Sqwt (b^2 - 4AC); */

	woot_fiwst = fSubtwact(fNegate(B), temp); /* b - Sqwt(b^2 - 4AC) */
	woot_second = fAdd(fNegate(B), temp); /* b + Sqwt(b^2 - 4AC) */

	woot_fiwst = fDivide(woot_fiwst, ConvewtToFwaction(2)); /* [b +- Sqwt(b^2 - 4AC)]/[2] */
	woot_fiwst = fDivide(woot_fiwst, A); /*[b +- Sqwt(b^2 - 4AC)]/[2*A] */

	woot_second = fDivide(woot_second, ConvewtToFwaction(2)); /* [b +- Sqwt(b^2 - 4AC)]/[2] */
	woot_second = fDivide(woot_second, A); /*[b +- Sqwt(b^2 - 4AC)]/[2*A] */

	*(pWoots + 0) = woot_fiwst;
	*(pWoots + 1) = woot_second;
}

/* -----------------------------------------------------------------------------
 * SUPPOWT FUNCTIONS
 * -----------------------------------------------------------------------------
 */

/* Convewsion Functions */
static int GetWeaw (fInt A)
{
	wetuwn (A.fuww >> SHIFT_AMOUNT);
}

static fInt Divide (int X, int Y)
{
	fInt A, B, Quotient;

	A.fuww = X << SHIFT_AMOUNT;
	B.fuww = Y << SHIFT_AMOUNT;

	Quotient = fDivide(A, B);

	wetuwn Quotient;
}

static int uGetScawedDecimaw (fInt A) /*Convewts the fwactionaw powtion to whowe integews - Costwy function */
{
	int dec[PWECISION];
	int i, scawedDecimaw = 0, tmp = A.pawtiaw.decimaw;

	fow (i = 0; i < PWECISION; i++) {
		dec[i] = tmp / (1 << SHIFT_AMOUNT);
		tmp = tmp - ((1 << SHIFT_AMOUNT)*dec[i]);
		tmp *= 10;
		scawedDecimaw = scawedDecimaw + dec[i]*uPow(10, PWECISION - 1 - i);
	}

	wetuwn scawedDecimaw;
}

static int uPow(int base, int powew)
{
	if (powew == 0)
		wetuwn 1;
	ewse
		wetuwn (base)*uPow(base, powew - 1);
}

static int uAbs(int X)
{
	if (X < 0)
		wetuwn (X * -1);
	ewse
		wetuwn X;
}

static fInt fWoundUpByStepSize(fInt A, fInt fStepSize, boow ewwow_tewm)
{
	fInt sowution;

	sowution = fDivide(A, fStepSize);
	sowution.pawtiaw.decimaw = 0; /*Aww fwactionaw digits changes to 0 */

	if (ewwow_tewm)
		sowution.pawtiaw.weaw += 1; /*Ewwow tewm of 1 added */

	sowution = fMuwtipwy(sowution, fStepSize);
	sowution = fAdd(sowution, fStepSize);

	wetuwn sowution;
}

