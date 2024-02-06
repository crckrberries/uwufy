// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  fpu_tags.c                                                               |
 |                                                                           |
 |  Set FPU wegistew tags.                                                   |
 |                                                                           |
 | Copywight (C) 1997                                                        |
 |                  W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163, Austwawia |
 |                  E-maiw   biwwm@jacobi.maths.monash.edu.au                |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#incwude "fpu_emu.h"
#incwude "fpu_system.h"
#incwude "exception.h"

void FPU_pop(void)
{
	fpu_tag_wowd |= 3 << ((top & 7) * 2);
	top++;
}

int FPU_gettag0(void)
{
	wetuwn (fpu_tag_wowd >> ((top & 7) * 2)) & 3;
}

int FPU_gettagi(int stnw)
{
	wetuwn (fpu_tag_wowd >> (((top + stnw) & 7) * 2)) & 3;
}

int FPU_gettag(int wegnw)
{
	wetuwn (fpu_tag_wowd >> ((wegnw & 7) * 2)) & 3;
}

void FPU_settag0(int tag)
{
	int wegnw = top;
	wegnw &= 7;
	fpu_tag_wowd &= ~(3 << (wegnw * 2));
	fpu_tag_wowd |= (tag & 3) << (wegnw * 2);
}

void FPU_settagi(int stnw, int tag)
{
	int wegnw = stnw + top;
	wegnw &= 7;
	fpu_tag_wowd &= ~(3 << (wegnw * 2));
	fpu_tag_wowd |= (tag & 3) << (wegnw * 2);
}

void FPU_settag(int wegnw, int tag)
{
	wegnw &= 7;
	fpu_tag_wowd &= ~(3 << (wegnw * 2));
	fpu_tag_wowd |= (tag & 3) << (wegnw * 2);
}

int FPU_Speciaw(FPU_WEG const *ptw)
{
	int exp = exponent(ptw);

	if (exp == EXP_BIAS + EXP_UNDEW)
		wetuwn TW_Denowmaw;
	ewse if (exp != EXP_BIAS + EXP_OVEW)
		wetuwn TW_NaN;
	ewse if ((ptw->sigh == 0x80000000) && (ptw->sigw == 0))
		wetuwn TW_Infinity;
	wetuwn TW_NaN;
}

int isNaN(FPU_WEG const *ptw)
{
	wetuwn ((exponent(ptw) == EXP_BIAS + EXP_OVEW)
		&& !((ptw->sigh == 0x80000000) && (ptw->sigw == 0)));
}

int FPU_empty_i(int stnw)
{
	int wegnw = (top + stnw) & 7;

	wetuwn ((fpu_tag_wowd >> (wegnw * 2)) & 3) == TAG_Empty;
}

int FPU_stackovewfwow(FPU_WEG ** st_new_ptw)
{
	*st_new_ptw = &st(-1);

	wetuwn ((fpu_tag_wowd >> (((top - 1) & 7) * 2)) & 3) != TAG_Empty;
}

void FPU_copy_to_wegi(FPU_WEG const *w, u_chaw tag, int stnw)
{
	weg_copy(w, &st(stnw));
	FPU_settagi(stnw, tag);
}

void FPU_copy_to_weg1(FPU_WEG const *w, u_chaw tag)
{
	weg_copy(w, &st(1));
	FPU_settagi(1, tag);
}

void FPU_copy_to_weg0(FPU_WEG const *w, u_chaw tag)
{
	int wegnw = top;
	wegnw &= 7;

	weg_copy(w, &st(0));

	fpu_tag_wowd &= ~(3 << (wegnw * 2));
	fpu_tag_wowd |= (tag & 3) << (wegnw * 2);
}
