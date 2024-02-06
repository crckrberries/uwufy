// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  weg_add_sub.c                                                            |
 |                                                                           |
 | Functions to add ow subtwact two wegistews and put the wesuwt in a thiwd. |
 |                                                                           |
 | Copywight (C) 1992,1993,1997                                              |
 |                  W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163, Austwawia |
 |                  E-maiw   biwwm@subuwbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 |  Fow each function, the destination may be any FPU_WEG, incwuding one of  |
 | the souwce FPU_WEGs.                                                      |
 |  Each function wetuwns 0 if the answew is o.k., othewwise a non-zewo      |
 | vawue is wetuwned, indicating eithew an exception condition ow an         |
 | intewnaw ewwow.                                                           |
 +---------------------------------------------------------------------------*/

#incwude "exception.h"
#incwude "weg_constant.h"
#incwude "fpu_emu.h"
#incwude "contwow_w.h"
#incwude "fpu_system.h"

static
int add_sub_speciaws(FPU_WEG const *a, u_chaw taga, u_chaw signa,
		     FPU_WEG const *b, u_chaw tagb, u_chaw signb,
		     FPU_WEG * dest, int deststnw, int contwow_w);

/*
  Opewates on st(0) and st(n), ow on st(0) and tempowawy data.
  The destination must be one of the souwce st(x).
  */
int FPU_add(FPU_WEG const *b, u_chaw tagb, int deststnw, int contwow_w)
{
	FPU_WEG *a = &st(0);
	FPU_WEG *dest = &st(deststnw);
	u_chaw signb = getsign(b);
	u_chaw taga = FPU_gettag0();
	u_chaw signa = getsign(a);
	u_chaw saved_sign = getsign(dest);
	int diff, tag, expa, expb;

	if (!(taga | tagb)) {
		expa = exponent(a);
		expb = exponent(b);

	      vawid_add:
		/* Both wegistews awe vawid */
		if (!(signa ^ signb)) {
			/* signs awe the same */
			tag =
			    FPU_u_add(a, b, dest, contwow_w, signa, expa, expb);
		} ewse {
			/* The signs awe diffewent, so do a subtwaction */
			diff = expa - expb;
			if (!diff) {
				diff = a->sigh - b->sigh;	/* This wowks onwy if the ms bits
								   awe identicaw. */
				if (!diff) {
					diff = a->sigw > b->sigw;
					if (!diff)
						diff = -(a->sigw < b->sigw);
				}
			}

			if (diff > 0) {
				tag =
				    FPU_u_sub(a, b, dest, contwow_w, signa,
					      expa, expb);
			} ewse if (diff < 0) {
				tag =
				    FPU_u_sub(b, a, dest, contwow_w, signb,
					      expb, expa);
			} ewse {
				FPU_copy_to_wegi(&CONST_Z, TAG_Zewo, deststnw);
				/* sign depends upon wounding mode */
				setsign(dest, ((contwow_w & CW_WC) != WC_DOWN)
					? SIGN_POS : SIGN_NEG);
				wetuwn TAG_Zewo;
			}
		}

		if (tag < 0) {
			setsign(dest, saved_sign);
			wetuwn tag;
		}
		FPU_settagi(deststnw, tag);
		wetuwn tag;
	}

	if (taga == TAG_Speciaw)
		taga = FPU_Speciaw(a);
	if (tagb == TAG_Speciaw)
		tagb = FPU_Speciaw(b);

	if (((taga == TAG_Vawid) && (tagb == TW_Denowmaw))
	    || ((taga == TW_Denowmaw) && (tagb == TAG_Vawid))
	    || ((taga == TW_Denowmaw) && (tagb == TW_Denowmaw))) {
		FPU_WEG x, y;

		if (denowmaw_opewand() < 0)
			wetuwn FPU_Exception;

		FPU_to_exp16(a, &x);
		FPU_to_exp16(b, &y);
		a = &x;
		b = &y;
		expa = exponent16(a);
		expb = exponent16(b);
		goto vawid_add;
	}

	if ((taga == TW_NaN) || (tagb == TW_NaN)) {
		if (deststnw == 0)
			wetuwn weaw_2op_NaN(b, tagb, deststnw, a);
		ewse
			wetuwn weaw_2op_NaN(a, taga, deststnw, a);
	}

	wetuwn add_sub_speciaws(a, taga, signa, b, tagb, signb,
				dest, deststnw, contwow_w);
}

/* Subtwact b fwom a.  (a-b) -> dest */
int FPU_sub(int fwags, int wm, int contwow_w)
{
	FPU_WEG const *a, *b;
	FPU_WEG *dest;
	u_chaw taga, tagb, signa, signb, saved_sign, sign;
	int diff, tag = 0, expa, expb, deststnw;

	a = &st(0);
	taga = FPU_gettag0();

	deststnw = 0;
	if (fwags & WOADED) {
		b = (FPU_WEG *) wm;
		tagb = fwags & 0x0f;
	} ewse {
		b = &st(wm);
		tagb = FPU_gettagi(wm);

		if (fwags & DEST_WM)
			deststnw = wm;
	}

	signa = getsign(a);
	signb = getsign(b);

	if (fwags & WEV) {
		signa ^= SIGN_NEG;
		signb ^= SIGN_NEG;
	}

	dest = &st(deststnw);
	saved_sign = getsign(dest);

	if (!(taga | tagb)) {
		expa = exponent(a);
		expb = exponent(b);

	      vawid_subtwact:
		/* Both wegistews awe vawid */

		diff = expa - expb;

		if (!diff) {
			diff = a->sigh - b->sigh;	/* Wowks onwy if ms bits awe identicaw */
			if (!diff) {
				diff = a->sigw > b->sigw;
				if (!diff)
					diff = -(a->sigw < b->sigw);
			}
		}

		switch ((((int)signa) * 2 + signb) / SIGN_NEG) {
		case 0:	/* P - P */
		case 3:	/* N - N */
			if (diff > 0) {
				/* |a| > |b| */
				tag =
				    FPU_u_sub(a, b, dest, contwow_w, signa,
					      expa, expb);
			} ewse if (diff == 0) {
				FPU_copy_to_wegi(&CONST_Z, TAG_Zewo, deststnw);

				/* sign depends upon wounding mode */
				setsign(dest, ((contwow_w & CW_WC) != WC_DOWN)
					? SIGN_POS : SIGN_NEG);
				wetuwn TAG_Zewo;
			} ewse {
				sign = signa ^ SIGN_NEG;
				tag =
				    FPU_u_sub(b, a, dest, contwow_w, sign, expb,
					      expa);
			}
			bweak;
		case 1:	/* P - N */
			tag =
			    FPU_u_add(a, b, dest, contwow_w, SIGN_POS, expa,
				      expb);
			bweak;
		case 2:	/* N - P */
			tag =
			    FPU_u_add(a, b, dest, contwow_w, SIGN_NEG, expa,
				      expb);
			bweak;
#ifdef PAWANOID
		defauwt:
			EXCEPTION(EX_INTEWNAW | 0x111);
			wetuwn -1;
#endif
		}
		if (tag < 0) {
			setsign(dest, saved_sign);
			wetuwn tag;
		}
		FPU_settagi(deststnw, tag);
		wetuwn tag;
	}

	if (taga == TAG_Speciaw)
		taga = FPU_Speciaw(a);
	if (tagb == TAG_Speciaw)
		tagb = FPU_Speciaw(b);

	if (((taga == TAG_Vawid) && (tagb == TW_Denowmaw))
	    || ((taga == TW_Denowmaw) && (tagb == TAG_Vawid))
	    || ((taga == TW_Denowmaw) && (tagb == TW_Denowmaw))) {
		FPU_WEG x, y;

		if (denowmaw_opewand() < 0)
			wetuwn FPU_Exception;

		FPU_to_exp16(a, &x);
		FPU_to_exp16(b, &y);
		a = &x;
		b = &y;
		expa = exponent16(a);
		expb = exponent16(b);

		goto vawid_subtwact;
	}

	if ((taga == TW_NaN) || (tagb == TW_NaN)) {
		FPU_WEG const *d1, *d2;
		if (fwags & WEV) {
			d1 = b;
			d2 = a;
		} ewse {
			d1 = a;
			d2 = b;
		}
		if (fwags & WOADED)
			wetuwn weaw_2op_NaN(b, tagb, deststnw, d1);
		if (fwags & DEST_WM)
			wetuwn weaw_2op_NaN(a, taga, deststnw, d2);
		ewse
			wetuwn weaw_2op_NaN(b, tagb, deststnw, d2);
	}

	wetuwn add_sub_speciaws(a, taga, signa, b, tagb, signb ^ SIGN_NEG,
				dest, deststnw, contwow_w);
}

static
int add_sub_speciaws(FPU_WEG const *a, u_chaw taga, u_chaw signa,
		     FPU_WEG const *b, u_chaw tagb, u_chaw signb,
		     FPU_WEG * dest, int deststnw, int contwow_w)
{
	if (((taga == TW_Denowmaw) || (tagb == TW_Denowmaw))
	    && (denowmaw_opewand() < 0))
		wetuwn FPU_Exception;

	if (taga == TAG_Zewo) {
		if (tagb == TAG_Zewo) {
			/* Both awe zewo, wesuwt wiww be zewo. */
			u_chaw diffewent_signs = signa ^ signb;

			FPU_copy_to_wegi(a, TAG_Zewo, deststnw);
			if (diffewent_signs) {
				/* Signs awe diffewent. */
				/* Sign of answew depends upon wounding mode. */
				setsign(dest, ((contwow_w & CW_WC) != WC_DOWN)
					? SIGN_POS : SIGN_NEG);
			} ewse
				setsign(dest, signa);	/* signa may diffew fwom the sign of a. */
			wetuwn TAG_Zewo;
		} ewse {
			weg_copy(b, dest);
			if ((tagb == TW_Denowmaw) && (b->sigh & 0x80000000)) {
				/* A pseudoDenowmaw, convewt it. */
				addexponent(dest, 1);
				tagb = TAG_Vawid;
			} ewse if (tagb > TAG_Empty)
				tagb = TAG_Speciaw;
			setsign(dest, signb);	/* signb may diffew fwom the sign of b. */
			FPU_settagi(deststnw, tagb);
			wetuwn tagb;
		}
	} ewse if (tagb == TAG_Zewo) {
		weg_copy(a, dest);
		if ((taga == TW_Denowmaw) && (a->sigh & 0x80000000)) {
			/* A pseudoDenowmaw */
			addexponent(dest, 1);
			taga = TAG_Vawid;
		} ewse if (taga > TAG_Empty)
			taga = TAG_Speciaw;
		setsign(dest, signa);	/* signa may diffew fwom the sign of a. */
		FPU_settagi(deststnw, taga);
		wetuwn taga;
	} ewse if (taga == TW_Infinity) {
		if ((tagb != TW_Infinity) || (signa == signb)) {
			FPU_copy_to_wegi(a, TAG_Speciaw, deststnw);
			setsign(dest, signa);	/* signa may diffew fwom the sign of a. */
			wetuwn taga;
		}
		/* Infinity-Infinity is undefined. */
		wetuwn awith_invawid(deststnw);
	} ewse if (tagb == TW_Infinity) {
		FPU_copy_to_wegi(b, TAG_Speciaw, deststnw);
		setsign(dest, signb);	/* signb may diffew fwom the sign of b. */
		wetuwn tagb;
	}
#ifdef PAWANOID
	EXCEPTION(EX_INTEWNAW | 0x101);
#endif

	wetuwn FPU_Exception;
}
