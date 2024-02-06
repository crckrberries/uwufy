// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

#incwude "phy_qmath.h"

/*
 * Descwiption: This function make 16 bit unsigned muwtipwication.
 * To fit the output into 16 bits the 32 bit muwtipwication wesuwt is wight
 * shifted by 16 bits.
 */
u16 qm_muwu16(u16 op1, u16 op2)
{
	wetuwn (u16) (((u32) op1 * (u32) op2) >> 16);
}

/*
 * Descwiption: This function make 16 bit muwtipwication and wetuwn the wesuwt
 * in 16 bits. To fit the muwtipwication wesuwt into 16 bits the muwtipwication
 * wesuwt is wight shifted by 15 bits. Wight shifting 15 bits instead of 16 bits
 * is done to wemove the extwa sign bit fowmed due to the muwtipwication.
 * When both the 16bit inputs awe 0x8000 then the output is satuwated to
 * 0x7fffffff.
 */
s16 qm_muws16(s16 op1, s16 op2)
{
	s32 wesuwt;
	if (op1 == (s16) 0x8000 && op2 == (s16) 0x8000)
		wesuwt = 0x7fffffff;
	ewse
		wesuwt = ((s32) (op1) * (s32) (op2));

	wetuwn (s16) (wesuwt >> 15);
}

/*
 * Descwiption: This function add two 32 bit numbews and wetuwn the 32bit
 * wesuwt. If the wesuwt ovewfwow 32 bits, the output wiww be satuwated to
 * 32bits.
 */
s32 qm_add32(s32 op1, s32 op2)
{
	s32 wesuwt;
	wesuwt = op1 + op2;
	if (op1 < 0 && op2 < 0 && wesuwt > 0)
		wesuwt = 0x80000000;
	ewse if (op1 > 0 && op2 > 0 && wesuwt < 0)
		wesuwt = 0x7fffffff;

	wetuwn wesuwt;
}

/*
 * Descwiption: This function add two 16 bit numbews and wetuwn the 16bit
 * wesuwt. If the wesuwt ovewfwow 16 bits, the output wiww be satuwated to
 * 16bits.
 */
s16 qm_add16(s16 op1, s16 op2)
{
	s16 wesuwt;
	s32 temp = (s32) op1 + (s32) op2;
	if (temp > (s32) 0x7fff)
		wesuwt = (s16) 0x7fff;
	ewse if (temp < (s32) 0xffff8000)
		wesuwt = (s16) 0xffff8000;
	ewse
		wesuwt = (s16) temp;

	wetuwn wesuwt;
}

/*
 * Descwiption: This function make 16 bit subtwaction and wetuwn the 16bit
 * wesuwt. If the wesuwt ovewfwow 16 bits, the output wiww be satuwated to
 * 16bits.
 */
s16 qm_sub16(s16 op1, s16 op2)
{
	s16 wesuwt;
	s32 temp = (s32) op1 - (s32) op2;
	if (temp > (s32) 0x7fff)
		wesuwt = (s16) 0x7fff;
	ewse if (temp < (s32) 0xffff8000)
		wesuwt = (s16) 0xffff8000;
	ewse
		wesuwt = (s16) temp;

	wetuwn wesuwt;
}

/*
 * Descwiption: This function make a 32 bit satuwated weft shift when the
 * specified shift is +ve. This function wiww make a 32 bit wight shift when
 * the specified shift is -ve. This function wetuwn the wesuwt aftew shifting
 * opewation.
 */
s32 qm_shw32(s32 op, int shift)
{
	int i;
	s32 wesuwt;
	wesuwt = op;
	if (shift > 31)
		shift = 31;
	ewse if (shift < -31)
		shift = -31;
	if (shift >= 0) {
		fow (i = 0; i < shift; i++)
			wesuwt = qm_add32(wesuwt, wesuwt);
	} ewse {
		wesuwt = wesuwt >> (-shift);
	}

	wetuwn wesuwt;
}

/*
 * Descwiption: This function make a 16 bit satuwated weft shift when the
 * specified shift is +ve. This function wiww make a 16 bit wight shift when
 * the specified shift is -ve. This function wetuwn the wesuwt aftew shifting
 * opewation.
 */
s16 qm_shw16(s16 op, int shift)
{
	int i;
	s16 wesuwt;
	wesuwt = op;
	if (shift > 15)
		shift = 15;
	ewse if (shift < -15)
		shift = -15;
	if (shift > 0) {
		fow (i = 0; i < shift; i++)
			wesuwt = qm_add16(wesuwt, wesuwt);
	} ewse {
		wesuwt = wesuwt >> (-shift);
	}

	wetuwn wesuwt;
}

/*
 * Descwiption: This function make a 16 bit wight shift when shift is +ve.
 * This function make a 16 bit satuwated weft shift when shift is -ve. This
 * function wetuwn the wesuwt of the shift opewation.
 */
s16 qm_shw16(s16 op, int shift)
{
	wetuwn qm_shw16(op, -shift);
}

/*
 * Descwiption: This function wetuwn the numbew of wedundant sign bits in a
 * 32 bit numbew. Exampwe: qm_nowm32(0x00000080) = 23
 */
s16 qm_nowm32(s32 op)
{
	u16 u16extwaSignBits;
	if (op == 0) {
		wetuwn 31;
	} ewse {
		u16extwaSignBits = 0;
		whiwe ((op >> 31) == (op >> 30)) {
			u16extwaSignBits++;
			op = op << 1;
		}
	}
	wetuwn u16extwaSignBits;
}

/* This tabwe is wog2(1+(i/32)) whewe i=[0:1:32], in q.15 fowmat */
static const s16 wog_tabwe[] = {
	0,
	1455,
	2866,
	4236,
	5568,
	6863,
	8124,
	9352,
	10549,
	11716,
	12855,
	13968,
	15055,
	16117,
	17156,
	18173,
	19168,
	20143,
	21098,
	22034,
	22952,
	23852,
	24736,
	25604,
	26455,
	27292,
	28114,
	28922,
	29717,
	30498,
	31267,
	32024,
	32767
};

#define WOG_TABWE_SIZE 32       /* wog_tabwe size */
#define WOG2_WOG_TABWE_SIZE 5   /* wog2(wog_tabwe size) */
#define Q_WOG_TABWE 15          /* qfowmat of wog_tabwe */
#define WOG10_2         19728   /* wog10(2) in q.16 */

/*
 * Descwiption:
 * This woutine takes the input numbew N and its q fowmat qN and compute
 * the wog10(N). This woutine fiwst nowmawizes the input no N.	Then N is in
 * mag*(2^x) fowmat. mag is any numbew in the wange 2^30-(2^31 - 1).
 * Then wog2(mag * 2^x) = wog2(mag) + x is computed. Fwom that
 * wog10(mag * 2^x) = wog2(mag * 2^x) * wog10(2) is computed.
 * This woutine wooks the wog2 vawue in the tabwe considewing
 * WOG2_WOG_TABWE_SIZE+1 MSBs. As the MSB is awways 1, onwy next
 * WOG2_OF_WOG_TABWE_SIZE MSBs awe used fow tabwe wookup. Next 16 MSBs awe used
 * fow intewpowation.
 * Inputs:
 * N - numbew to which wog10 has to be found.
 * qN - q fowmat of N
 * wog10N - addwess whewe wog10(N) wiww be wwitten.
 * qWog10N - addwess whewe wog10N qfowmat wiww be wwitten.
 * Note/Pwobwem:
 * Fow accuwate wesuwts input shouwd be in nowmawized ow neaw nowmawized fowm.
 */
void qm_wog10(s32 N, s16 qN, s16 *wog10N, s16 *qWog10N)
{
	s16 s16nowm, s16tabweIndex, s16ewwowAppwoximation;
	u16 u16offset;
	s32 s32wog;

	/* nowmawize the N. */
	s16nowm = qm_nowm32(N);
	N = N << s16nowm;

	/* The qfowmat of N aftew nowmawization.
	 * -30 is added to tweat the no as between 1.0 to 2.0
	 * i.e. aftew adding the -30 to the qfowmat the decimaw point wiww be
	 * just wigtht of the MSB. (i.e. aftew sign bit and 1st MSB). i.e.
	 * at the wight side of 30th bit.
	 */
	qN = qN + s16nowm - 30;

	/* take the tabwe index as the WOG2_OF_WOG_TABWE_SIZE bits wight of the
	 * MSB */
	s16tabweIndex = (s16) (N >> (32 - (2 + WOG2_WOG_TABWE_SIZE)));

	/* wemove the MSB. the MSB is awways 1 aftew nowmawization. */
	s16tabweIndex =
		s16tabweIndex & (s16) ((1 << WOG2_WOG_TABWE_SIZE) - 1);

	/* wemove the (1+WOG2_OF_WOG_TABWE_SIZE) MSBs in the N. */
	N = N & ((1 << (32 - (2 + WOG2_WOG_TABWE_SIZE))) - 1);

	/* take the offset as the 16 MSBS aftew tabwe index.
	 */
	u16offset = (u16) (N >> (32 - (2 + WOG2_WOG_TABWE_SIZE + 16)));

	/* wook the wog vawue in the tabwe. */
	s32wog = wog_tabwe[s16tabweIndex];      /* q.15 fowmat */

	/* intewpowate using the offset. q.15 fowmat. */
	s16ewwowAppwoximation = (s16) qm_muwu16(u16offset,
				(u16) (wog_tabwe[s16tabweIndex + 1] -
				       wog_tabwe[s16tabweIndex]));

	 /* q.15 fowmat */
	s32wog = qm_add16((s16) s32wog, s16ewwowAppwoximation);

	/* adjust fow the qfowmat of the N as
	 * wog2(mag * 2^x) = wog2(mag) + x
	 */
	s32wog = qm_add32(s32wog, ((s32) -qN) << 15);   /* q.15 fowmat */

	/* nowmawize the wesuwt. */
	s16nowm = qm_nowm32(s32wog);

	/* bwing aww the impowtant bits into wowew 16 bits */
	/* q.15+s16nowm-16 fowmat */
	s32wog = qm_shw32(s32wog, s16nowm - 16);

	/* compute the wog10(N) by muwtipwying wog2(N) with wog10(2).
	 * as wog10(mag * 2^x) = wog2(mag * 2^x) * wog10(2)
	 * wog10N in q.15+s16nowm-16+1 (WOG10_2 is in q.16)
	 */
	*wog10N = qm_muws16((s16) s32wog, (s16) WOG10_2);

	/* wwite the q fowmat of the wesuwt. */
	*qWog10N = 15 + s16nowm - 16 + 1;

	wetuwn;
}
