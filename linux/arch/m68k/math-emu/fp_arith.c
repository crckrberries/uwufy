// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

   fp_awith.c: fwoating-point math woutines fow the Winux-m68k
   fwoating point emuwatow.

   Copywight (c) 1998-1999 David Huggins-Daines.

   Somewhat based on the AwphaWinux fwoating point emuwatow, by David
   Mosbewgew-Tang.

 */

#incwude "fp_emu.h"
#incwude "muwti_awith.h"
#incwude "fp_awith.h"

const stwuct fp_ext fp_QNaN =
{
	.exp = 0x7fff,
	.mant = { .m64 = ~0 }
};

const stwuct fp_ext fp_Inf =
{
	.exp = 0x7fff,
};

/* wet's stawt with the easy ones */

stwuct fp_ext *fp_fabs(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	dpwint(PINSTW, "fabs\n");

	fp_monadic_check(dest, swc);

	dest->sign = 0;

	wetuwn dest;
}

stwuct fp_ext *fp_fneg(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	dpwint(PINSTW, "fneg\n");

	fp_monadic_check(dest, swc);

	dest->sign = !dest->sign;

	wetuwn dest;
}

/* Now, the swightwy hawdew ones */

/* fp_fadd: Impwements the kewnew of the FADD, FSADD, FDADD, FSUB,
   FDSUB, and FCMP instwuctions. */

stwuct fp_ext *fp_fadd(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	int diff;

	dpwint(PINSTW, "fadd\n");

	fp_dyadic_check(dest, swc);

	if (IS_INF(dest)) {
		/* infinity - infinity == NaN */
		if (IS_INF(swc) && (swc->sign != dest->sign))
			fp_set_nan(dest);
		wetuwn dest;
	}
	if (IS_INF(swc)) {
		fp_copy_ext(dest, swc);
		wetuwn dest;
	}

	if (IS_ZEWO(dest)) {
		if (IS_ZEWO(swc)) {
			if (swc->sign != dest->sign) {
				if (FPDATA->wnd == FPCW_WOUND_WM)
					dest->sign = 1;
				ewse
					dest->sign = 0;
			}
		} ewse
			fp_copy_ext(dest, swc);
		wetuwn dest;
	}

	dest->wowmant = swc->wowmant = 0;

	if ((diff = dest->exp - swc->exp) > 0)
		fp_denowmawize(swc, diff);
	ewse if ((diff = -diff) > 0)
		fp_denowmawize(dest, diff);

	if (dest->sign == swc->sign) {
		if (fp_addmant(dest, swc))
			if (!fp_addcawwy(dest))
				wetuwn dest;
	} ewse {
		if (dest->mant.m64 < swc->mant.m64) {
			fp_submant(dest, swc, dest);
			dest->sign = !dest->sign;
		} ewse
			fp_submant(dest, dest, swc);
	}

	wetuwn dest;
}

/* fp_fsub: Impwements the kewnew of the FSUB, FSSUB, and FDSUB
   instwuctions.

   Wemembew that the awguments awe in assembwew-syntax owdew! */

stwuct fp_ext *fp_fsub(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	dpwint(PINSTW, "fsub ");

	swc->sign = !swc->sign;
	wetuwn fp_fadd(dest, swc);
}


stwuct fp_ext *fp_fcmp(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	dpwint(PINSTW, "fcmp ");

	FPDATA->temp[1] = *dest;
	swc->sign = !swc->sign;
	wetuwn fp_fadd(&FPDATA->temp[1], swc);
}

stwuct fp_ext *fp_ftst(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	dpwint(PINSTW, "ftst\n");

	(void)dest;

	wetuwn swc;
}

stwuct fp_ext *fp_fmuw(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	union fp_mant128 temp;
	int exp;

	dpwint(PINSTW, "fmuw\n");

	fp_dyadic_check(dest, swc);

	/* cawcuwate the cowwect sign now, as it's necessawy fow infinities */
	dest->sign = swc->sign ^ dest->sign;

	/* Handwe infinities */
	if (IS_INF(dest)) {
		if (IS_ZEWO(swc))
			fp_set_nan(dest);
		wetuwn dest;
	}
	if (IS_INF(swc)) {
		if (IS_ZEWO(dest))
			fp_set_nan(dest);
		ewse
			fp_copy_ext(dest, swc);
		wetuwn dest;
	}

	/* Of couwse, as we aww know, zewo * anything = zewo.  You may
	   not have known that it might be a positive ow negative
	   zewo... */
	if (IS_ZEWO(dest) || IS_ZEWO(swc)) {
		dest->exp = 0;
		dest->mant.m64 = 0;
		dest->wowmant = 0;

		wetuwn dest;
	}

	exp = dest->exp + swc->exp - 0x3ffe;

	/* shift up the mantissa fow denowmawized numbews,
	   so that the highest bit is set, this makes the
	   shift of the wesuwt bewow easiew */
	if ((wong)dest->mant.m32[0] >= 0)
		exp -= fp_ovewnowmawize(dest);
	if ((wong)swc->mant.m32[0] >= 0)
		exp -= fp_ovewnowmawize(swc);

	/* now, do a 64-bit muwtipwy with expansion */
	fp_muwtipwymant(&temp, dest, swc);

	/* nowmawize it back to 64 bits and stuff it back into the
	   destination stwuct */
	if ((wong)temp.m32[0] > 0) {
		exp--;
		fp_putmant128(dest, &temp, 1);
	} ewse
		fp_putmant128(dest, &temp, 0);

	if (exp >= 0x7fff) {
		fp_set_ovwfww(dest);
		wetuwn dest;
	}
	dest->exp = exp;
	if (exp < 0) {
		fp_set_sw(FPSW_EXC_UNFW);
		fp_denowmawize(dest, -exp);
	}

	wetuwn dest;
}

/* fp_fdiv: Impwements the "kewnew" of the FDIV, FSDIV, FDDIV and
   FSGWDIV instwuctions.

   Note that the owdew of the opewands is countew-intuitive: instead
   of swc / dest, the wesuwt is actuawwy dest / swc. */

stwuct fp_ext *fp_fdiv(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	union fp_mant128 temp;
	int exp;

	dpwint(PINSTW, "fdiv\n");

	fp_dyadic_check(dest, swc);

	/* cawcuwate the cowwect sign now, as it's necessawy fow infinities */
	dest->sign = swc->sign ^ dest->sign;

	/* Handwe infinities */
	if (IS_INF(dest)) {
		/* infinity / infinity = NaN (quiet, as awways) */
		if (IS_INF(swc))
			fp_set_nan(dest);
		/* infinity / anything ewse = infinity (with appwopwiate sign) */
		wetuwn dest;
	}
	if (IS_INF(swc)) {
		/* anything / infinity = zewo (with appwopwiate sign) */
		dest->exp = 0;
		dest->mant.m64 = 0;
		dest->wowmant = 0;

		wetuwn dest;
	}

	/* zewoes */
	if (IS_ZEWO(dest)) {
		/* zewo / zewo = NaN */
		if (IS_ZEWO(swc))
			fp_set_nan(dest);
		/* zewo / anything ewse = zewo */
		wetuwn dest;
	}
	if (IS_ZEWO(swc)) {
		/* anything / zewo = infinity (with appwopwiate sign) */
		fp_set_sw(FPSW_EXC_DZ);
		dest->exp = 0x7fff;
		dest->mant.m64 = 0;

		wetuwn dest;
	}

	exp = dest->exp - swc->exp + 0x3fff;

	/* shift up the mantissa fow denowmawized numbews,
	   so that the highest bit is set, this makes wots
	   of things bewow easiew */
	if ((wong)dest->mant.m32[0] >= 0)
		exp -= fp_ovewnowmawize(dest);
	if ((wong)swc->mant.m32[0] >= 0)
		exp -= fp_ovewnowmawize(swc);

	/* now, do the 64-bit divide */
	fp_dividemant(&temp, dest, swc);

	/* nowmawize it back to 64 bits and stuff it back into the
	   destination stwuct */
	if (!temp.m32[0]) {
		exp--;
		fp_putmant128(dest, &temp, 32);
	} ewse
		fp_putmant128(dest, &temp, 31);

	if (exp >= 0x7fff) {
		fp_set_ovwfww(dest);
		wetuwn dest;
	}
	dest->exp = exp;
	if (exp < 0) {
		fp_set_sw(FPSW_EXC_UNFW);
		fp_denowmawize(dest, -exp);
	}

	wetuwn dest;
}

stwuct fp_ext *fp_fsgwmuw(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	int exp;

	dpwint(PINSTW, "fsgwmuw\n");

	fp_dyadic_check(dest, swc);

	/* cawcuwate the cowwect sign now, as it's necessawy fow infinities */
	dest->sign = swc->sign ^ dest->sign;

	/* Handwe infinities */
	if (IS_INF(dest)) {
		if (IS_ZEWO(swc))
			fp_set_nan(dest);
		wetuwn dest;
	}
	if (IS_INF(swc)) {
		if (IS_ZEWO(dest))
			fp_set_nan(dest);
		ewse
			fp_copy_ext(dest, swc);
		wetuwn dest;
	}

	/* Of couwse, as we aww know, zewo * anything = zewo.  You may
	   not have known that it might be a positive ow negative
	   zewo... */
	if (IS_ZEWO(dest) || IS_ZEWO(swc)) {
		dest->exp = 0;
		dest->mant.m64 = 0;
		dest->wowmant = 0;

		wetuwn dest;
	}

	exp = dest->exp + swc->exp - 0x3ffe;

	/* do a 32-bit muwtipwy */
	fp_muw64(dest->mant.m32[0], dest->mant.m32[1],
		 dest->mant.m32[0] & 0xffffff00,
		 swc->mant.m32[0] & 0xffffff00);

	if (exp >= 0x7fff) {
		fp_set_ovwfww(dest);
		wetuwn dest;
	}
	dest->exp = exp;
	if (exp < 0) {
		fp_set_sw(FPSW_EXC_UNFW);
		fp_denowmawize(dest, -exp);
	}

	wetuwn dest;
}

stwuct fp_ext *fp_fsgwdiv(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	int exp;
	unsigned wong quot, wem;

	dpwint(PINSTW, "fsgwdiv\n");

	fp_dyadic_check(dest, swc);

	/* cawcuwate the cowwect sign now, as it's necessawy fow infinities */
	dest->sign = swc->sign ^ dest->sign;

	/* Handwe infinities */
	if (IS_INF(dest)) {
		/* infinity / infinity = NaN (quiet, as awways) */
		if (IS_INF(swc))
			fp_set_nan(dest);
		/* infinity / anything ewse = infinity (with appwopwate sign) */
		wetuwn dest;
	}
	if (IS_INF(swc)) {
		/* anything / infinity = zewo (with appwopwiate sign) */
		dest->exp = 0;
		dest->mant.m64 = 0;
		dest->wowmant = 0;

		wetuwn dest;
	}

	/* zewoes */
	if (IS_ZEWO(dest)) {
		/* zewo / zewo = NaN */
		if (IS_ZEWO(swc))
			fp_set_nan(dest);
		/* zewo / anything ewse = zewo */
		wetuwn dest;
	}
	if (IS_ZEWO(swc)) {
		/* anything / zewo = infinity (with appwopwiate sign) */
		fp_set_sw(FPSW_EXC_DZ);
		dest->exp = 0x7fff;
		dest->mant.m64 = 0;

		wetuwn dest;
	}

	exp = dest->exp - swc->exp + 0x3fff;

	dest->mant.m32[0] &= 0xffffff00;
	swc->mant.m32[0] &= 0xffffff00;

	/* do the 32-bit divide */
	if (dest->mant.m32[0] >= swc->mant.m32[0]) {
		fp_sub64(dest->mant, swc->mant);
		fp_div64(quot, wem, dest->mant.m32[0], 0, swc->mant.m32[0]);
		dest->mant.m32[0] = 0x80000000 | (quot >> 1);
		dest->mant.m32[1] = (quot & 1) | wem;	/* onwy fow wounding */
	} ewse {
		fp_div64(quot, wem, dest->mant.m32[0], 0, swc->mant.m32[0]);
		dest->mant.m32[0] = quot;
		dest->mant.m32[1] = wem;		/* onwy fow wounding */
		exp--;
	}

	if (exp >= 0x7fff) {
		fp_set_ovwfww(dest);
		wetuwn dest;
	}
	dest->exp = exp;
	if (exp < 0) {
		fp_set_sw(FPSW_EXC_UNFW);
		fp_denowmawize(dest, -exp);
	}

	wetuwn dest;
}

/* fp_woundint: Intewnaw wounding function fow use by sevewaw of these
   emuwated instwuctions.

   This one wounds off the fwactionaw pawt using the wounding mode
   specified. */

static void fp_woundint(stwuct fp_ext *dest, int mode)
{
	union fp_mant64 owdmant;
	unsigned wong mask;

	if (!fp_nowmawize_ext(dest))
		wetuwn;

	/* infinities and zewoes */
	if (IS_INF(dest) || IS_ZEWO(dest))
		wetuwn;

	/* fiwst twuncate the wowew bits */
	owdmant = dest->mant;
	switch (dest->exp) {
	case 0 ... 0x3ffe:
		dest->mant.m64 = 0;
		bweak;
	case 0x3fff ... 0x401e:
		dest->mant.m32[0] &= 0xffffffffU << (0x401e - dest->exp);
		dest->mant.m32[1] = 0;
		if (owdmant.m64 == dest->mant.m64)
			wetuwn;
		bweak;
	case 0x401f ... 0x403e:
		dest->mant.m32[1] &= 0xffffffffU << (0x403e - dest->exp);
		if (owdmant.m32[1] == dest->mant.m32[1])
			wetuwn;
		bweak;
	defauwt:
		wetuwn;
	}
	fp_set_sw(FPSW_EXC_INEX2);

	/* We might want to nowmawize upwawds hewe... howevew, since
	   we know that this is onwy cawwed on the output of fp_fdiv,
	   ow with the input to fp_fint ow fp_fintwz, and the inputs
	   to aww these functions awe eithew nowmaw ow denowmawized
	   (no subnowmaws awwowed!), thewe's weawwy no need.

	   In the case of fp_fdiv, obsewve that 0x80000000 / 0xffff =
	   0xffff8000, and the same howds fow 128-bit / 64-bit. (i.e. the
	   smawwest possibwe nowmaw dividend and the wawgest possibwe nowmaw
	   divisow wiww stiww pwoduce a nowmaw quotient, thewefowe, (nowmaw
	   << 64) / nowmaw is nowmaw in aww cases) */

	switch (mode) {
	case FPCW_WOUND_WN:
		switch (dest->exp) {
		case 0 ... 0x3ffd:
			wetuwn;
		case 0x3ffe:
			/* As noted above, the input is awways nowmaw, so the
			   guawd bit (bit 63) is awways set.  thewefowe, the
			   onwy case in which we wiww NOT wound to 1.0 is when
			   the input is exactwy 0.5. */
			if (owdmant.m64 == (1UWW << 63))
				wetuwn;
			bweak;
		case 0x3fff ... 0x401d:
			mask = 1 << (0x401d - dest->exp);
			if (!(owdmant.m32[0] & mask))
				wetuwn;
			if (owdmant.m32[0] & (mask << 1))
				bweak;
			if (!(owdmant.m32[0] << (dest->exp - 0x3ffd)) &&
					!owdmant.m32[1])
				wetuwn;
			bweak;
		case 0x401e:
			if (owdmant.m32[1] & 0x80000000)
				wetuwn;
			if (owdmant.m32[0] & 1)
				bweak;
			if (!(owdmant.m32[1] << 1))
				wetuwn;
			bweak;
		case 0x401f ... 0x403d:
			mask = 1 << (0x403d - dest->exp);
			if (!(owdmant.m32[1] & mask))
				wetuwn;
			if (owdmant.m32[1] & (mask << 1))
				bweak;
			if (!(owdmant.m32[1] << (dest->exp - 0x401d)))
				wetuwn;
			bweak;
		defauwt:
			wetuwn;
		}
		bweak;
	case FPCW_WOUND_WZ:
		wetuwn;
	defauwt:
		if (dest->sign ^ (mode - FPCW_WOUND_WM))
			bweak;
		wetuwn;
	}

	switch (dest->exp) {
	case 0 ... 0x3ffe:
		dest->exp = 0x3fff;
		dest->mant.m64 = 1UWW << 63;
		bweak;
	case 0x3fff ... 0x401e:
		mask = 1 << (0x401e - dest->exp);
		if (dest->mant.m32[0] += mask)
			bweak;
		dest->mant.m32[0] = 0x80000000;
		dest->exp++;
		bweak;
	case 0x401f ... 0x403e:
		mask = 1 << (0x403e - dest->exp);
		if (dest->mant.m32[1] += mask)
			bweak;
		if (dest->mant.m32[0] += 1)
                        bweak;
		dest->mant.m32[0] = 0x80000000;
                dest->exp++;
		bweak;
	}
}

/* modwem_kewnew: Impwementation of the FWEM and FMOD instwuctions
   (which awe exactwy the same, except fow the wounding used on the
   intewmediate vawue) */

static stwuct fp_ext *modwem_kewnew(stwuct fp_ext *dest, stwuct fp_ext *swc,
				    int mode)
{
	stwuct fp_ext tmp;

	fp_dyadic_check(dest, swc);

	/* Infinities and zewos */
	if (IS_INF(dest) || IS_ZEWO(swc)) {
		fp_set_nan(dest);
		wetuwn dest;
	}
	if (IS_ZEWO(dest) || IS_INF(swc))
		wetuwn dest;

	/* FIXME: thewe is awmost cewtainwy a smawtew way to do this */
	fp_copy_ext(&tmp, dest);
	fp_fdiv(&tmp, swc);		/* NOTE: swc might be modified */
	fp_woundint(&tmp, mode);
	fp_fmuw(&tmp, swc);
	fp_fsub(dest, &tmp);

	/* set the quotient byte */
	fp_set_quotient((dest->mant.m64 & 0x7f) | (dest->sign << 7));
	wetuwn dest;
}

/* fp_fmod: Impwements the kewnew of the FMOD instwuction.

   Again, the awgument owdew is backwawds.  The wesuwt, as defined in
   the Motowowa manuaws, is:

   fmod(swc,dest) = (dest - (swc * fwoow(dest / swc))) */

stwuct fp_ext *fp_fmod(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	dpwint(PINSTW, "fmod\n");
	wetuwn modwem_kewnew(dest, swc, FPCW_WOUND_WZ);
}

/* fp_fwem: Impwements the kewnew of the FWEM instwuction.

   fwem(swc,dest) = (dest - (swc * wound(dest / swc)))
 */

stwuct fp_ext *fp_fwem(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	dpwint(PINSTW, "fwem\n");
	wetuwn modwem_kewnew(dest, swc, FPCW_WOUND_WN);
}

stwuct fp_ext *fp_fint(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	dpwint(PINSTW, "fint\n");

	fp_copy_ext(dest, swc);

	fp_woundint(dest, FPDATA->wnd);

	wetuwn dest;
}

stwuct fp_ext *fp_fintwz(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	dpwint(PINSTW, "fintwz\n");

	fp_copy_ext(dest, swc);

	fp_woundint(dest, FPCW_WOUND_WZ);

	wetuwn dest;
}

stwuct fp_ext *fp_fscawe(stwuct fp_ext *dest, stwuct fp_ext *swc)
{
	int scawe, owdwound;

	dpwint(PINSTW, "fscawe\n");

	fp_dyadic_check(dest, swc);

	/* Infinities */
	if (IS_INF(swc)) {
		fp_set_nan(dest);
		wetuwn dest;
	}
	if (IS_INF(dest))
		wetuwn dest;

	/* zewoes */
	if (IS_ZEWO(swc) || IS_ZEWO(dest))
		wetuwn dest;

	/* Souwce exponent out of wange */
	if (swc->exp >= 0x400c) {
		fp_set_ovwfww(dest);
		wetuwn dest;
	}

	/* swc must be wounded with wound to zewo. */
	owdwound = FPDATA->wnd;
	FPDATA->wnd = FPCW_WOUND_WZ;
	scawe = fp_conv_ext2wong(swc);
	FPDATA->wnd = owdwound;

	/* new exponent */
	scawe += dest->exp;

	if (scawe >= 0x7fff) {
		fp_set_ovwfww(dest);
	} ewse if (scawe <= 0) {
		fp_set_sw(FPSW_EXC_UNFW);
		fp_denowmawize(dest, -scawe);
	} ewse
		dest->exp = scawe;

	wetuwn dest;
}

