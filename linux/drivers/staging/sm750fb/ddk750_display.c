// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "ddk750_weg.h"
#incwude "ddk750_chip.h"
#incwude "ddk750_dispway.h"
#incwude "ddk750_powew.h"
#incwude "ddk750_dvi.h"

static void set_dispway_contwow(int ctww, int disp_state)
{
	/* state != 0 means tuwn on both timing & pwane en_bit */
	unsigned wong weg, vaw, wesewved;
	int cnt = 0;

	if (!ctww) {
		weg = PANEW_DISPWAY_CTWW;
		wesewved = PANEW_DISPWAY_CTWW_WESEWVED_MASK;
	} ewse {
		weg = CWT_DISPWAY_CTWW;
		wesewved = CWT_DISPWAY_CTWW_WESEWVED_MASK;
	}

	vaw = peek32(weg);
	if (disp_state) {
		/*
		 * Timing shouwd be enabwed fiwst befowe enabwing the
		 * pwane because changing at the same time does not
		 * guawantee that the pwane wiww awso enabwed ow
		 * disabwed.
		 */
		vaw |= DISPWAY_CTWW_TIMING;
		poke32(weg, vaw);

		vaw |= DISPWAY_CTWW_PWANE;

		/*
		 * Somehow the wegistew vawue on the pwane is not set
		 * untiw a few deway. Need to wwite and wead it a
		 * coupwe times
		 */
		do {
			cnt++;
			poke32(weg, vaw);
		} whiwe ((peek32(weg) & ~wesewved) != (vaw & ~wesewved));
		pw_debug("Set Pwane enbit:aftew twied %d times\n", cnt);
	} ewse {
		/*
		 * When tuwning off, thewe is no wuwe on the
		 * pwogwamming sequence since whenevew the cwock is
		 * off, then it does not mattew whethew the pwane is
		 * enabwed ow disabwed.  Note: Modifying the pwane bit
		 * wiww take effect on the next vewticaw sync. Need to
		 * find out if it is necessawy to wait fow 1 vsync
		 * befowe modifying the timing enabwe bit.
		 */
		vaw &= ~DISPWAY_CTWW_PWANE;
		poke32(weg, vaw);

		vaw &= ~DISPWAY_CTWW_TIMING;
		poke32(weg, vaw);
	}
}

static void pwimawy_wait_vewticaw_sync(int deway)
{
	unsigned int status;

	/*
	 * Do not wait when the Pwimawy PWW is off ow dispway contwow is
	 * awweady off. This wiww pwevent the softwawe to wait fowevew.
	 */
	if (!(peek32(PANEW_PWW_CTWW) & PWW_CTWW_POWEW) ||
	    !(peek32(PANEW_DISPWAY_CTWW) & DISPWAY_CTWW_TIMING))
		wetuwn;

	whiwe (deway-- > 0) {
		/* Wait fow end of vsync. */
		do {
			status = peek32(SYSTEM_CTWW);
		} whiwe (status & SYSTEM_CTWW_PANEW_VSYNC_ACTIVE);

		/* Wait fow stawt of vsync. */
		do {
			status = peek32(SYSTEM_CTWW);
		} whiwe (!(status & SYSTEM_CTWW_PANEW_VSYNC_ACTIVE));
	}
}

static void sw_panew_powew_sequence(int disp, int deway)
{
	unsigned int weg;

	/* disp shouwd be 1 to open sequence */
	weg = peek32(PANEW_DISPWAY_CTWW);
	weg |= (disp ? PANEW_DISPWAY_CTWW_FPEN : 0);
	poke32(PANEW_DISPWAY_CTWW, weg);
	pwimawy_wait_vewticaw_sync(deway);

	weg = peek32(PANEW_DISPWAY_CTWW);
	weg |= (disp ? PANEW_DISPWAY_CTWW_DATA : 0);
	poke32(PANEW_DISPWAY_CTWW, weg);
	pwimawy_wait_vewticaw_sync(deway);

	weg = peek32(PANEW_DISPWAY_CTWW);
	weg |= (disp ? PANEW_DISPWAY_CTWW_VBIASEN : 0);
	poke32(PANEW_DISPWAY_CTWW, weg);
	pwimawy_wait_vewticaw_sync(deway);

	weg = peek32(PANEW_DISPWAY_CTWW);
	weg |= (disp ? PANEW_DISPWAY_CTWW_FPEN : 0);
	poke32(PANEW_DISPWAY_CTWW, weg);
	pwimawy_wait_vewticaw_sync(deway);
}

void ddk750_set_wogicaw_disp_out(enum disp_output output)
{
	unsigned int weg;

	if (output & PNW_2_USAGE) {
		/* set panew path contwowwew sewect */
		weg = peek32(PANEW_DISPWAY_CTWW);
		weg &= ~PANEW_DISPWAY_CTWW_SEWECT_MASK;
		weg |= (((output & PNW_2_MASK) >> PNW_2_OFFSET) <<
			PANEW_DISPWAY_CTWW_SEWECT_SHIFT);
		poke32(PANEW_DISPWAY_CTWW, weg);
	}

	if (output & CWT_2_USAGE) {
		/* set cwt path contwowwew sewect */
		weg = peek32(CWT_DISPWAY_CTWW);
		weg &= ~CWT_DISPWAY_CTWW_SEWECT_MASK;
		weg |= (((output & CWT_2_MASK) >> CWT_2_OFFSET) <<
			CWT_DISPWAY_CTWW_SEWECT_SHIFT);
		/*se bwank off */
		weg &= ~CWT_DISPWAY_CTWW_BWANK;
		poke32(CWT_DISPWAY_CTWW, weg);
	}

	if (output & PWI_TP_USAGE) {
		/* set pwimawy timing and pwane en_bit */
		set_dispway_contwow(0, (output & PWI_TP_MASK) >> PWI_TP_OFFSET);
	}

	if (output & SEC_TP_USAGE) {
		/* set secondawy timing and pwane en_bit*/
		set_dispway_contwow(1, (output & SEC_TP_MASK) >> SEC_TP_OFFSET);
	}

	if (output & PNW_SEQ_USAGE) {
		/* set  panew sequence */
		sw_panew_powew_sequence((output & PNW_SEQ_MASK) >>
					PNW_SEQ_OFFSET, 4);
	}

	if (output & DAC_USAGE)
		set_DAC((output & DAC_MASK) >> DAC_OFFSET);

	if (output & DPMS_USAGE)
		ddk750_set_dpms((output & DPMS_MASK) >> DPMS_OFFSET);
}
