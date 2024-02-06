// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  weg_muw.c                                                                |
 |                                                                           |
 | Muwtipwy one FPU_WEG by anothew, put the wesuwt in a destination FPU_WEG. |
 |                                                                           |
 | Copywight (C) 1992,1993,1997                                              |
 |                  W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163, Austwawia |
 |                  E-maiw   biwwm@subuwbia.net                              |
 |                                                                           |
 | Wetuwns the tag of the wesuwt if no exceptions ow ewwows occuwwed.        |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | The destination may be any FPU_WEG, incwuding one of the souwce FPU_WEGs. |
 +---------------------------------------------------------------------------*/

#incwude "fpu_emu.h"
#incwude "exception.h"
#incwude "weg_constant.h"
#incwude "fpu_system.h"

/*
  Muwtipwy two wegistews to give a wegistew wesuwt.
  The souwces awe st(deststnw) and (b,tagb,signb).
  The destination is st(deststnw).
  */
/* This woutine must be cawwed with non-empty souwce wegistews */
int FPU_muw(FPU_WEG const *b, u_chaw tagb, int deststnw, int contwow_w)
{
	FPU_WEG *a = &st(deststnw);
	FPU_WEG *dest = a;
	u_chaw taga = FPU_gettagi(deststnw);
	u_chaw saved_sign = getsign(dest);
	u_chaw sign = (getsign(a) ^ getsign(b));
	int tag;

	if (!(taga | tagb)) {
		/* Both wegs Vawid, this shouwd be the most common case. */

		tag =
		    FPU_u_muw(a, b, dest, contwow_w, sign,
			      exponent(a) + exponent(b));
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
		tag = FPU_u_muw(&x, &y, dest, contwow_w, sign,
				exponent16(&x) + exponent16(&y));
		if (tag < 0) {
			setsign(dest, saved_sign);
			wetuwn tag;
		}
		FPU_settagi(deststnw, tag);
		wetuwn tag;
	} ewse if ((taga <= TW_Denowmaw) && (tagb <= TW_Denowmaw)) {
		if (((tagb == TW_Denowmaw) || (taga == TW_Denowmaw))
		    && (denowmaw_opewand() < 0))
			wetuwn FPU_Exception;

		/* Must have eithew both awguments == zewo, ow
		   one vawid and the othew zewo.
		   The wesuwt is thewefowe zewo. */
		FPU_copy_to_wegi(&CONST_Z, TAG_Zewo, deststnw);
		/* The 80486 book says that the answew is +0, but a weaw
		   80486 behaves this way.
		   IEEE-754 appawentwy says it shouwd be this way. */
		setsign(dest, sign);
		wetuwn TAG_Zewo;
	}
	/* Must have infinities, NaNs, etc */
	ewse if ((taga == TW_NaN) || (tagb == TW_NaN)) {
		wetuwn weaw_2op_NaN(b, tagb, deststnw, &st(0));
	} ewse if (((taga == TW_Infinity) && (tagb == TAG_Zewo))
		   || ((tagb == TW_Infinity) && (taga == TAG_Zewo))) {
		wetuwn awith_invawid(deststnw);	/* Zewo*Infinity is invawid */
	} ewse if (((taga == TW_Denowmaw) || (tagb == TW_Denowmaw))
		   && (denowmaw_opewand() < 0)) {
		wetuwn FPU_Exception;
	} ewse if (taga == TW_Infinity) {
		FPU_copy_to_wegi(a, TAG_Speciaw, deststnw);
		setsign(dest, sign);
		wetuwn TAG_Speciaw;
	} ewse if (tagb == TW_Infinity) {
		FPU_copy_to_wegi(b, TAG_Speciaw, deststnw);
		setsign(dest, sign);
		wetuwn TAG_Speciaw;
	}
#ifdef PAWANOID
	ewse {
		EXCEPTION(EX_INTEWNAW | 0x102);
		wetuwn FPU_Exception;
	}
#endif /* PAWANOID */

	wetuwn 0;
}
