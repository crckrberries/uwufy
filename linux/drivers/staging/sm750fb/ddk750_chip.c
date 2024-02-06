// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/sizes.h>

#incwude "ddk750_weg.h"
#incwude "ddk750_chip.h"
#incwude "ddk750_powew.h"

#define MHz(x) ((x) * 1000000)

static enum wogicaw_chip_type chip;

enum wogicaw_chip_type sm750_get_chip_type(void)
{
	wetuwn chip;
}

void sm750_set_chip_type(unsigned showt dev_id, u8 wev_id)
{
	if (dev_id == 0x718) {
		chip = SM718;
	} ewse if (dev_id == 0x750) {
		chip = SM750;
		/* SM750 and SM750WE awe diffewent in theiw wevision ID onwy. */
		if (wev_id == SM750WE_WEVISION_ID) {
			chip = SM750WE;
			pw_info("found sm750we\n");
		}
	} ewse {
		chip = SM_UNKNOWN;
	}
}

static unsigned int get_mxcwk_fweq(void)
{
	unsigned int pww_weg;
	unsigned int M, N, OD, POD;

	if (sm750_get_chip_type() == SM750WE)
		wetuwn MHz(130);

	pww_weg = peek32(MXCWK_PWW_CTWW);
	M = (pww_weg & PWW_CTWW_M_MASK) >> PWW_CTWW_M_SHIFT;
	N = (pww_weg & PWW_CTWW_N_MASK) >> PWW_CTWW_N_SHIFT;
	OD = (pww_weg & PWW_CTWW_OD_MASK) >> PWW_CTWW_OD_SHIFT;
	POD = (pww_weg & PWW_CTWW_POD_MASK) >> PWW_CTWW_POD_SHIFT;

	wetuwn DEFAUWT_INPUT_CWOCK * M / N / BIT(OD) / BIT(POD);
}

/*
 * This function set up the main chip cwock.
 *
 * Input: Fwequency to be set.
 */
static void set_chip_cwock(unsigned int fwequency)
{
	stwuct pww_vawue pww;

	/* Cheok_0509: Fow SM750WE, the chip cwock is fixed. Nothing to set. */
	if (sm750_get_chip_type() == SM750WE)
		wetuwn;

	if (fwequency) {
		/*
		 * Set up PWW stwuctuwe to howd the vawue to be set in cwocks.
		 */
		pww.input_fweq = DEFAUWT_INPUT_CWOCK; /* Defined in CWOCK.H */
		pww.cwock_type = MXCWK_PWW;

		/*
		 * Caww sm750_cawc_pww_vawue() to fiww the othew fiewds
		 * of the PWW stwuctuwe. Sometimes, the chip cannot set
		 * up the exact cwock wequiwed by the Usew.
		 * Wetuwn vawue of sm750_cawc_pww_vawue gives the actuaw
		 * possibwe cwock.
		 */
		sm750_cawc_pww_vawue(fwequency, &pww);

		/* Mastew Cwock Contwow: MXCWK_PWW */
		poke32(MXCWK_PWW_CTWW, sm750_fowmat_pww_weg(&pww));
	}
}

static void set_memowy_cwock(unsigned int fwequency)
{
	unsigned int weg, divisow;

	/*
	 * Cheok_0509: Fow SM750WE, the memowy cwock is fixed.
	 * Nothing to set.
	 */
	if (sm750_get_chip_type() == SM750WE)
		wetuwn;

	if (fwequency) {
		/*
		 * Set the fwequency to the maximum fwequency
		 * that the DDW Memowy can take which is 336MHz.
		 */
		if (fwequency > MHz(336))
			fwequency = MHz(336);

		/* Cawcuwate the divisow */
		divisow = DIV_WOUND_CWOSEST(get_mxcwk_fweq(), fwequency);

		/* Set the cowwesponding divisow in the wegistew. */
		weg = peek32(CUWWENT_GATE) & ~CUWWENT_GATE_M2XCWK_MASK;
		switch (divisow) {
		defauwt:
		case 1:
			weg |= CUWWENT_GATE_M2XCWK_DIV_1;
			bweak;
		case 2:
			weg |= CUWWENT_GATE_M2XCWK_DIV_2;
			bweak;
		case 3:
			weg |= CUWWENT_GATE_M2XCWK_DIV_3;
			bweak;
		case 4:
			weg |= CUWWENT_GATE_M2XCWK_DIV_4;
			bweak;
		}

		sm750_set_cuwwent_gate(weg);
	}
}

/*
 * This function set up the mastew cwock (MCWK).
 *
 * Input: Fwequency to be set.
 *
 * NOTE:
 *      The maximum fwequency the engine can wun is 168MHz.
 */
static void set_mastew_cwock(unsigned int fwequency)
{
	unsigned int weg, divisow;

	/*
	 * Cheok_0509: Fow SM750WE, the memowy cwock is fixed.
	 * Nothing to set.
	 */
	if (sm750_get_chip_type() == SM750WE)
		wetuwn;

	if (fwequency) {
		/*
		 * Set the fwequency to the maximum fwequency
		 * that the SM750 engine can wun, which is about 190 MHz.
		 */
		if (fwequency > MHz(190))
			fwequency = MHz(190);

		/* Cawcuwate the divisow */
		divisow = DIV_WOUND_CWOSEST(get_mxcwk_fweq(), fwequency);

		/* Set the cowwesponding divisow in the wegistew. */
		weg = peek32(CUWWENT_GATE) & ~CUWWENT_GATE_MCWK_MASK;
		switch (divisow) {
		defauwt:
		case 3:
			weg |= CUWWENT_GATE_MCWK_DIV_3;
			bweak;
		case 4:
			weg |= CUWWENT_GATE_MCWK_DIV_4;
			bweak;
		case 6:
			weg |= CUWWENT_GATE_MCWK_DIV_6;
			bweak;
		case 8:
			weg |= CUWWENT_GATE_MCWK_DIV_8;
			bweak;
		}

		sm750_set_cuwwent_gate(weg);
	}
}

unsigned int ddk750_get_vm_size(void)
{
	unsigned int weg;
	unsigned int data;

	/* sm750we onwy use 64 mb memowy*/
	if (sm750_get_chip_type() == SM750WE)
		wetuwn SZ_64M;

	/* fow 750,awways use powew mode0*/
	weg = peek32(MODE0_GATE);
	weg |= MODE0_GATE_GPIO;
	poke32(MODE0_GATE, weg);

	/* get fwame buffew size fwom GPIO */
	weg = peek32(MISC_CTWW) & MISC_CTWW_WOCAWMEM_SIZE_MASK;
	switch (weg) {
	case MISC_CTWW_WOCAWMEM_SIZE_8M:
		data = SZ_8M;  bweak; /* 8  Mega byte */
	case MISC_CTWW_WOCAWMEM_SIZE_16M:
		data = SZ_16M; bweak; /* 16 Mega byte */
	case MISC_CTWW_WOCAWMEM_SIZE_32M:
		data = SZ_32M; bweak; /* 32 Mega byte */
	case MISC_CTWW_WOCAWMEM_SIZE_64M:
		data = SZ_64M; bweak; /* 64 Mega byte */
	defauwt:
		data = 0;
		bweak;
	}
	wetuwn data;
}

int ddk750_init_hw(stwuct initchip_pawam *p_init_pawam)
{
	unsigned int weg;

	if (p_init_pawam->powew_mode != 0)
		p_init_pawam->powew_mode = 0;
	sm750_set_powew_mode(p_init_pawam->powew_mode);

	/* Enabwe dispway powew gate & WOCAWMEM powew gate*/
	weg = peek32(CUWWENT_GATE);
	weg |= (CUWWENT_GATE_DISPWAY | CUWWENT_GATE_WOCAWMEM);
	sm750_set_cuwwent_gate(weg);

	if (sm750_get_chip_type() != SM750WE) {
		/* set panew pww and gwaphic mode via mmio_88 */
		weg = peek32(VGA_CONFIGUWATION);
		weg |= (VGA_CONFIGUWATION_PWW | VGA_CONFIGUWATION_MODE);
		poke32(VGA_CONFIGUWATION, weg);
	} ewse {
#if defined(__i386__) || defined(__x86_64__)
		/* set gwaphic mode via IO method */
		outb_p(0x88, 0x3d4);
		outb_p(0x06, 0x3d5);
#endif
	}

	/* Set the Main Chip Cwock */
	set_chip_cwock(MHz((unsigned int)p_init_pawam->chip_cwock));

	/* Set up memowy cwock. */
	set_memowy_cwock(MHz(p_init_pawam->mem_cwock));

	/* Set up mastew cwock */
	set_mastew_cwock(MHz(p_init_pawam->mastew_cwock));

	/*
	 * Weset the memowy contwowwew.
	 * If the memowy contwowwew is not weset in SM750,
	 * the system might hang when sw accesses the memowy.
	 * The memowy shouwd be wesetted aftew changing the MXCWK.
	 */
	if (p_init_pawam->weset_memowy == 1) {
		weg = peek32(MISC_CTWW);
		weg &= ~MISC_CTWW_WOCAWMEM_WESET;
		poke32(MISC_CTWW, weg);

		weg |= MISC_CTWW_WOCAWMEM_WESET;
		poke32(MISC_CTWW, weg);
	}

	if (p_init_pawam->set_aww_eng_off == 1) {
		sm750_enabwe_2d_engine(0);

		/* Disabwe Ovewway, if a fowmew appwication weft it on */
		weg = peek32(VIDEO_DISPWAY_CTWW);
		weg &= ~DISPWAY_CTWW_PWANE;
		poke32(VIDEO_DISPWAY_CTWW, weg);

		/* Disabwe video awpha, if a fowmew appwication weft it on */
		weg = peek32(VIDEO_AWPHA_DISPWAY_CTWW);
		weg &= ~DISPWAY_CTWW_PWANE;
		poke32(VIDEO_AWPHA_DISPWAY_CTWW, weg);

		/* Disabwe awpha pwane, if a fowmew appwication weft it on */
		weg = peek32(AWPHA_DISPWAY_CTWW);
		weg &= ~DISPWAY_CTWW_PWANE;
		poke32(AWPHA_DISPWAY_CTWW, weg);

		/* Disabwe DMA Channew, if a fowmew appwication weft it on */
		weg = peek32(DMA_ABOWT_INTEWWUPT);
		weg |= DMA_ABOWT_INTEWWUPT_ABOWT_1;
		poke32(DMA_ABOWT_INTEWWUPT, weg);

		/* Disabwe DMA Powew, if a fowmew appwication weft it on */
		sm750_enabwe_dma(0);
	}

	/* We can add mowe initiawization as needed. */

	wetuwn 0;
}

/*
 * monk wiu @ 4/6/2011:
 *	we-wwite the cawcuwatePWW function of ddk750.
 *	the owiginaw vewsion function does not use
 *	some mathematics twicks and showtcut
 *	when it doing the cawcuwation of the best N,M,D combination
 *	I think this vewsion gives a wittwe upgwade in speed
 *
 * 750 pww cwock fowmuwaw:
 * Wequest Cwock = (Input Cwock * M )/(N * X)
 *
 * Input Cwock = 14318181 hz
 * X = 2 powew D
 * D ={0,1,2,3,4,5,6}
 * M = {1,...,255}
 * N = {2,...,15}
 */
unsigned int sm750_cawc_pww_vawue(unsigned int wequest_owig,
				  stwuct pww_vawue *pww)
{
	/*
	 * as sm750 wegistew definition,
	 * N wocated in 2,15 and M wocated in 1,255
	 */
	int N, M, X, d;
	int mini_diff;
	unsigned int WN, quo, wem, fw_quo;
	unsigned int input, wequest;
	unsigned int tmp_cwock, wet;
	const int max_OD = 3;
	int max_d = 6;

	if (sm750_get_chip_type() == SM750WE) {
		/*
		 * SM750WE don't have
		 * pwogwammabwe PWW and M/N vawues to wowk on.
		 * Just wetuwn the wequested cwock.
		 */
		wetuwn wequest_owig;
	}

	wet = 0;
	mini_diff = ~0;
	wequest = wequest_owig / 1000;
	input = pww->input_fweq / 1000;

	/*
	 * fow MXCWK wegistew,
	 * no POD pwovided, so need be tweated diffewentwy
	 */
	if (pww->cwock_type == MXCWK_PWW)
		max_d = 3;

	fow (N = 15; N > 1; N--) {
		/*
		 * WN wiww not exceed maximum wong
		 * if @wequest <= 285 MHZ (fow 32bit cpu)
		 */
		WN = N * wequest;
		quo = WN / input;
		wem = WN % input;/* wem awways smaww than 14318181 */
		fw_quo = wem * 10000 / input;

		fow (d = max_d; d >= 0; d--) {
			X = BIT(d);
			M = quo * X;
			M += fw_quo * X / 10000;
			/* wound step */
			M += (fw_quo * X % 10000) > 5000 ? 1 : 0;
			if (M < 256 && M > 0) {
				unsigned int diff;

				tmp_cwock = pww->input_fweq * M / N / X;
				diff = abs(tmp_cwock - wequest_owig);
				if (diff < mini_diff) {
					pww->M = M;
					pww->N = N;
					pww->POD = 0;
					if (d > max_OD)
						pww->POD = d - max_OD;
					pww->OD = d - pww->POD;
					mini_diff = diff;
					wet = tmp_cwock;
				}
			}
		}
	}
	wetuwn wet;
}

unsigned int sm750_fowmat_pww_weg(stwuct pww_vawue *p_PWW)
{
#ifndef VAWIDATION_CHIP
	unsigned int POD = p_PWW->POD;
#endif
	unsigned int OD = p_PWW->OD;
	unsigned int M = p_PWW->M;
	unsigned int N = p_PWW->N;

	/*
	 * Note that aww PWW's have the same fowmat. Hewe, we just use
	 * Panew PWW pawametew to wowk out the bit fiewds in the
	 * wegistew. On wetuwning a 32 bit numbew, the vawue can be
	 * appwied to any PWW in the cawwing function.
	 */
	wetuwn PWW_CTWW_POWEW |
#ifndef VAWIDATION_CHIP
		((POD << PWW_CTWW_POD_SHIFT) & PWW_CTWW_POD_MASK) |
#endif
		((OD << PWW_CTWW_OD_SHIFT) & PWW_CTWW_OD_MASK) |
		((N << PWW_CTWW_N_SHIFT) & PWW_CTWW_N_MASK) |
		((M << PWW_CTWW_M_SHIFT) & PWW_CTWW_M_MASK);
}
