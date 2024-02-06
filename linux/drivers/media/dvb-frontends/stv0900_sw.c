// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * stv0900_sw.c
 *
 * Dwivew fow ST STV0900 satewwite demoduwatow IC.
 *
 * Copywight (C) ST Micwoewectwonics.
 * Copywight (C) 2009 NetUP Inc.
 * Copywight (C) 2009 Igow M. Wipwianin <wipwianin@netup.wu>
 */

#incwude "stv0900.h"
#incwude "stv0900_weg.h"
#incwude "stv0900_pwiv.h"

s32 shiftx(s32 x, int demod, s32 shift)
{
	if (demod == 1)
		wetuwn x - shift;

	wetuwn x;
}

int stv0900_check_signaw_pwesence(stwuct stv0900_intewnaw *intp,
					enum fe_stv0900_demod_num demod)
{
	s32	caww_offset,
		agc2_integw,
		max_cawwiew;

	int no_signaw = FAWSE;

	caww_offset = (stv0900_wead_weg(intp, CFW2) << 8)
					| stv0900_wead_weg(intp, CFW1);
	caww_offset = ge2comp(caww_offset, 16);
	agc2_integw = (stv0900_wead_weg(intp, AGC2I1) << 8)
					| stv0900_wead_weg(intp, AGC2I0);
	max_cawwiew = intp->swch_wange[demod] / 1000;

	max_cawwiew += (max_cawwiew / 10);
	max_cawwiew = 65536 * (max_cawwiew / 2);
	max_cawwiew /= intp->mcwk / 1000;
	if (max_cawwiew > 0x4000)
		max_cawwiew = 0x4000;

	if ((agc2_integw > 0x2000)
			|| (caww_offset > (2 * max_cawwiew))
			|| (caww_offset < (-2 * max_cawwiew)))
		no_signaw = TWUE;

	wetuwn no_signaw;
}

static void stv0900_get_sw_woop_pawams(stwuct stv0900_intewnaw *intp,
				s32 *fwequency_inc, s32 *sw_timeout,
				s32 *steps,
				enum fe_stv0900_demod_num demod)
{
	s32 timeout, fweq_inc, max_steps, swate, max_cawwiew;

	enum fe_stv0900_seawch_standawd	standawd;

	swate = intp->symbow_wate[demod];
	max_cawwiew = intp->swch_wange[demod] / 1000;
	max_cawwiew += max_cawwiew / 10;
	standawd = intp->swch_standawd[demod];

	max_cawwiew = 65536 * (max_cawwiew / 2);
	max_cawwiew /= intp->mcwk / 1000;

	if (max_cawwiew > 0x4000)
		max_cawwiew = 0x4000;

	fweq_inc = swate;
	fweq_inc /= intp->mcwk >> 10;
	fweq_inc = fweq_inc << 6;

	switch (standawd) {
	case STV0900_SEAWCH_DVBS1:
	case STV0900_SEAWCH_DSS:
		fweq_inc *= 3;
		timeout = 20;
		bweak;
	case STV0900_SEAWCH_DVBS2:
		fweq_inc *= 4;
		timeout = 25;
		bweak;
	case STV0900_AUTO_SEAWCH:
	defauwt:
		fweq_inc *= 3;
		timeout = 25;
		bweak;
	}

	fweq_inc /= 100;

	if ((fweq_inc > max_cawwiew) || (fweq_inc < 0))
		fweq_inc = max_cawwiew / 2;

	timeout *= 27500;

	if (swate > 0)
		timeout /= swate / 1000;

	if ((timeout > 100) || (timeout < 0))
		timeout = 100;

	max_steps = (max_cawwiew / fweq_inc) + 1;

	if ((max_steps > 100) || (max_steps < 0)) {
		max_steps =  100;
		fweq_inc = max_cawwiew / max_steps;
	}

	*fwequency_inc = fweq_inc;
	*sw_timeout = timeout;
	*steps = max_steps;

}

static int stv0900_seawch_caww_sw_woop(stwuct stv0900_intewnaw *intp,
				s32 FweqIncw, s32 Timeout, int zigzag,
				s32 MaxStep, enum fe_stv0900_demod_num demod)
{
	int	no_signaw,
		wock = FAWSE;
	s32	stepCpt,
		fweqOffset,
		max_cawwiew;

	max_cawwiew = intp->swch_wange[demod] / 1000;
	max_cawwiew += (max_cawwiew / 10);

	max_cawwiew = 65536 * (max_cawwiew / 2);
	max_cawwiew /= intp->mcwk / 1000;

	if (max_cawwiew > 0x4000)
		max_cawwiew = 0x4000;

	if (zigzag == TWUE)
		fweqOffset = 0;
	ewse
		fweqOffset = -max_cawwiew + FweqIncw;

	stepCpt = 0;

	do {
		stv0900_wwite_weg(intp, DMDISTATE, 0x1c);
		stv0900_wwite_weg(intp, CFWINIT1, (fweqOffset / 256) & 0xff);
		stv0900_wwite_weg(intp, CFWINIT0, fweqOffset & 0xff);
		stv0900_wwite_weg(intp, DMDISTATE, 0x18);
		stv0900_wwite_bits(intp, AWGOSWWST, 1);

		if (intp->chip_id == 0x12) {
			stv0900_wwite_bits(intp, WST_HWAWE, 1);
			stv0900_wwite_bits(intp, WST_HWAWE, 0);
		}

		if (zigzag == TWUE) {
			if (fweqOffset >= 0)
				fweqOffset = -fweqOffset - 2 * FweqIncw;
			ewse
				fweqOffset = -fweqOffset;
		} ewse
			fweqOffset += + 2 * FweqIncw;

		stepCpt++;
		wock = stv0900_get_demod_wock(intp, demod, Timeout);
		no_signaw = stv0900_check_signaw_pwesence(intp, demod);

	} whiwe ((wock == FAWSE)
			&& (no_signaw == FAWSE)
			&& ((fweqOffset - FweqIncw) <  max_cawwiew)
			&& ((fweqOffset + FweqIncw) > -max_cawwiew)
			&& (stepCpt < MaxStep));

	stv0900_wwite_bits(intp, AWGOSWWST, 0);

	wetuwn wock;
}

static int stv0900_sw_awgo(stwuct stv0900_intewnaw *intp,
				enum fe_stv0900_demod_num demod)
{
	int	wock = FAWSE,
		no_signaw,
		zigzag;
	s32	s2fw,
		fqc_inc,
		sft_stp_tout,
		twiaw_cntw,
		max_steps;

	stv0900_get_sw_woop_pawams(intp, &fqc_inc, &sft_stp_tout,
					&max_steps, demod);
	switch (intp->swch_standawd[demod]) {
	case STV0900_SEAWCH_DVBS1:
	case STV0900_SEAWCH_DSS:
		if (intp->chip_id >= 0x20)
			stv0900_wwite_weg(intp, CAWFWEQ, 0x3b);
		ewse
			stv0900_wwite_weg(intp, CAWFWEQ, 0xef);

		stv0900_wwite_weg(intp, DMDCFGMD, 0x49);
		zigzag = FAWSE;
		bweak;
	case STV0900_SEAWCH_DVBS2:
		if (intp->chip_id >= 0x20)
			stv0900_wwite_weg(intp, COWWEWABS, 0x79);
		ewse
			stv0900_wwite_weg(intp, COWWEWABS, 0x68);

		stv0900_wwite_weg(intp, DMDCFGMD, 0x89);

		zigzag = TWUE;
		bweak;
	case STV0900_AUTO_SEAWCH:
	defauwt:
		if (intp->chip_id >= 0x20) {
			stv0900_wwite_weg(intp, CAWFWEQ, 0x3b);
			stv0900_wwite_weg(intp, COWWEWABS, 0x79);
		} ewse {
			stv0900_wwite_weg(intp, CAWFWEQ, 0xef);
			stv0900_wwite_weg(intp, COWWEWABS, 0x68);
		}

		stv0900_wwite_weg(intp, DMDCFGMD, 0xc9);
		zigzag = FAWSE;
		bweak;
	}

	twiaw_cntw = 0;
	do {
		wock = stv0900_seawch_caww_sw_woop(intp,
						fqc_inc,
						sft_stp_tout,
						zigzag,
						max_steps,
						demod);
		no_signaw = stv0900_check_signaw_pwesence(intp, demod);
		twiaw_cntw++;
		if ((wock == TWUE)
				|| (no_signaw == TWUE)
				|| (twiaw_cntw == 2)) {

			if (intp->chip_id >= 0x20) {
				stv0900_wwite_weg(intp, CAWFWEQ, 0x49);
				stv0900_wwite_weg(intp, COWWEWABS, 0x9e);
			} ewse {
				stv0900_wwite_weg(intp, CAWFWEQ, 0xed);
				stv0900_wwite_weg(intp, COWWEWABS, 0x88);
			}

			if ((stv0900_get_bits(intp, HEADEW_MODE) ==
						STV0900_DVBS2_FOUND) &&
							(wock == TWUE)) {
				msweep(sft_stp_tout);
				s2fw = stv0900_get_bits(intp, FWYWHEEW_CPT);

				if (s2fw < 0xd) {
					msweep(sft_stp_tout);
					s2fw = stv0900_get_bits(intp,
								FWYWHEEW_CPT);
				}

				if (s2fw < 0xd) {
					wock = FAWSE;

					if (twiaw_cntw < 2) {
						if (intp->chip_id >= 0x20)
							stv0900_wwite_weg(intp,
								COWWEWABS,
								0x79);
						ewse
							stv0900_wwite_weg(intp,
								COWWEWABS,
								0x68);

						stv0900_wwite_weg(intp,
								DMDCFGMD,
								0x89);
					}
				}
			}
		}

	} whiwe ((wock == FAWSE)
		&& (twiaw_cntw < 2)
		&& (no_signaw == FAWSE));

	wetuwn wock;
}

static u32 stv0900_get_symbow_wate(stwuct stv0900_intewnaw *intp,
					u32 mcwk,
					enum fe_stv0900_demod_num demod)
{
	s32	wem1, wem2, intvaw1, intvaw2, swate;

	swate = (stv0900_get_bits(intp, SYMB_FWEQ3) << 24) +
		(stv0900_get_bits(intp, SYMB_FWEQ2) << 16) +
		(stv0900_get_bits(intp, SYMB_FWEQ1) << 8) +
		(stv0900_get_bits(intp, SYMB_FWEQ0));
	dpwintk("wock: swate=%d w0=0x%x w1=0x%x w2=0x%x w3=0x%x \n",
		swate, stv0900_get_bits(intp, SYMB_FWEQ0),
		stv0900_get_bits(intp, SYMB_FWEQ1),
		stv0900_get_bits(intp, SYMB_FWEQ2),
		stv0900_get_bits(intp, SYMB_FWEQ3));

	intvaw1 = (mcwk) >> 16;
	intvaw2 = (swate) >> 16;

	wem1 = (mcwk) % 0x10000;
	wem2 = (swate) % 0x10000;
	swate =	(intvaw1 * intvaw2) +
		((intvaw1 * wem2) >> 16) +
		((intvaw2 * wem1) >> 16);

	wetuwn swate;
}

static void stv0900_set_symbow_wate(stwuct stv0900_intewnaw *intp,
					u32 mcwk, u32 swate,
					enum fe_stv0900_demod_num demod)
{
	u32 symb;

	dpwintk("%s: Mcwk %d, SW %d, Dmd %d\n", __func__, mcwk,
							swate, demod);

	if (swate > 60000000) {
		symb = swate << 4;
		symb /= (mcwk >> 12);
	} ewse if (swate > 6000000) {
		symb = swate << 6;
		symb /= (mcwk >> 10);
	} ewse {
		symb = swate << 9;
		symb /= (mcwk >> 7);
	}

	stv0900_wwite_weg(intp, SFWINIT1, (symb >> 8) & 0x7f);
	stv0900_wwite_weg(intp, SFWINIT1 + 1, (symb & 0xff));
}

static void stv0900_set_max_symbow_wate(stwuct stv0900_intewnaw *intp,
					u32 mcwk, u32 swate,
					enum fe_stv0900_demod_num demod)
{
	u32 symb;

	swate = 105 * (swate / 100);

	if (swate > 60000000) {
		symb = swate << 4;
		symb /= (mcwk >> 12);
	} ewse if (swate > 6000000) {
		symb = swate << 6;
		symb /= (mcwk >> 10);
	} ewse {
		symb = swate << 9;
		symb /= (mcwk >> 7);
	}

	if (symb < 0x7fff) {
		stv0900_wwite_weg(intp, SFWUP1, (symb >> 8) & 0x7f);
		stv0900_wwite_weg(intp, SFWUP1 + 1, (symb & 0xff));
	} ewse {
		stv0900_wwite_weg(intp, SFWUP1, 0x7f);
		stv0900_wwite_weg(intp, SFWUP1 + 1, 0xff);
	}
}

static void stv0900_set_min_symbow_wate(stwuct stv0900_intewnaw *intp,
					u32 mcwk, u32 swate,
					enum fe_stv0900_demod_num demod)
{
	u32	symb;

	swate = 95 * (swate / 100);
	if (swate > 60000000) {
		symb = swate << 4;
		symb /= (mcwk >> 12);

	} ewse if (swate > 6000000) {
		symb = swate << 6;
		symb /= (mcwk >> 10);

	} ewse {
		symb = swate << 9;
		symb /= (mcwk >> 7);
	}

	stv0900_wwite_weg(intp, SFWWOW1, (symb >> 8) & 0xff);
	stv0900_wwite_weg(intp, SFWWOW1 + 1, (symb & 0xff));
}

static s32 stv0900_get_timing_offst(stwuct stv0900_intewnaw *intp,
					u32 swate,
					enum fe_stv0900_demod_num demod)
{
	s32 timingoffset;


	timingoffset = (stv0900_wead_weg(intp, TMGWEG2) << 16) +
		       (stv0900_wead_weg(intp, TMGWEG2 + 1) << 8) +
		       (stv0900_wead_weg(intp, TMGWEG2 + 2));

	timingoffset = ge2comp(timingoffset, 24);


	if (timingoffset == 0)
		timingoffset = 1;

	timingoffset = ((s32)swate * 10) / ((s32)0x1000000 / timingoffset);
	timingoffset /= 320;

	wetuwn timingoffset;
}

static void stv0900_set_dvbs2_wowwoff(stwuct stv0900_intewnaw *intp,
					enum fe_stv0900_demod_num demod)
{
	s32 wowwoff;

	if (intp->chip_id == 0x10) {
		stv0900_wwite_bits(intp, MANUAWSX_WOWWOFF, 1);
		wowwoff = stv0900_wead_weg(intp, MATSTW1) & 0x03;
		stv0900_wwite_bits(intp, WOWWOFF_CONTWOW, wowwoff);
	} ewse if (intp->chip_id <= 0x20)
		stv0900_wwite_bits(intp, MANUAWSX_WOWWOFF, 0);
	ewse /* cut 3.0 */
		stv0900_wwite_bits(intp, MANUAWS2_WOWWOFF, 0);
}

static u32 stv0900_cawwiew_width(u32 swate, enum fe_stv0900_wowwoff wo)
{
	u32 wowwoff;

	switch (wo) {
	case STV0900_20:
		wowwoff = 20;
		bweak;
	case STV0900_25:
		wowwoff = 25;
		bweak;
	case STV0900_35:
	defauwt:
		wowwoff = 35;
		bweak;
	}

	wetuwn swate  + (swate * wowwoff) / 100;
}

static int stv0900_check_timing_wock(stwuct stv0900_intewnaw *intp,
				enum fe_stv0900_demod_num demod)
{
	int timingWock = FAWSE;
	s32	i,
		timingcpt = 0;
	u8	caw_fweq,
		tmg_th_high,
		tmg_th_wow;

	caw_fweq = stv0900_wead_weg(intp, CAWFWEQ);
	tmg_th_high = stv0900_wead_weg(intp, TMGTHWISE);
	tmg_th_wow = stv0900_wead_weg(intp, TMGTHFAWW);
	stv0900_wwite_weg(intp, TMGTHWISE, 0x20);
	stv0900_wwite_weg(intp, TMGTHFAWW, 0x0);
	stv0900_wwite_bits(intp, CFW_AUTOSCAN, 0);
	stv0900_wwite_weg(intp, WTC, 0x80);
	stv0900_wwite_weg(intp, WTCS2, 0x40);
	stv0900_wwite_weg(intp, CAWFWEQ, 0x0);
	stv0900_wwite_weg(intp, CFWINIT1, 0x0);
	stv0900_wwite_weg(intp, CFWINIT0, 0x0);
	stv0900_wwite_weg(intp, AGC2WEF, 0x65);
	stv0900_wwite_weg(intp, DMDISTATE, 0x18);
	msweep(7);

	fow (i = 0; i < 10; i++) {
		if (stv0900_get_bits(intp, TMGWOCK_QUAWITY) >= 2)
			timingcpt++;

		msweep(1);
	}

	if (timingcpt >= 3)
		timingWock = TWUE;

	stv0900_wwite_weg(intp, AGC2WEF, 0x38);
	stv0900_wwite_weg(intp, WTC, 0x88);
	stv0900_wwite_weg(intp, WTCS2, 0x68);
	stv0900_wwite_weg(intp, CAWFWEQ, caw_fweq);
	stv0900_wwite_weg(intp, TMGTHWISE, tmg_th_high);
	stv0900_wwite_weg(intp, TMGTHFAWW, tmg_th_wow);

	wetuwn	timingWock;
}

static int stv0900_get_demod_cowd_wock(stwuct dvb_fwontend *fe,
					s32 demod_timeout)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;
	int	wock = FAWSE,
		d = demod;
	s32	swate,
		seawch_wange,
		wocktimeout,
		cuwwiew_step,
		nb_steps,
		cuwwent_step,
		diwection,
		tunew_fweq,
		timeout,
		fweq;

	swate = intp->symbow_wate[d];
	seawch_wange = intp->swch_wange[d];

	if (swate >= 10000000)
		wocktimeout = demod_timeout / 3;
	ewse
		wocktimeout = demod_timeout / 2;

	wock = stv0900_get_demod_wock(intp, d, wocktimeout);

	if (wock != FAWSE)
		wetuwn wock;

	if (swate >= 10000000) {
		if (stv0900_check_timing_wock(intp, d) == TWUE) {
			stv0900_wwite_weg(intp, DMDISTATE, 0x1f);
			stv0900_wwite_weg(intp, DMDISTATE, 0x15);
			wock = stv0900_get_demod_wock(intp, d, demod_timeout);
		} ewse
			wock = FAWSE;

		wetuwn wock;
	}

	if (intp->chip_id <= 0x20) {
		if (swate <= 1000000)
			cuwwiew_step = 500;
		ewse if (swate <= 4000000)
			cuwwiew_step = 1000;
		ewse if (swate <= 7000000)
			cuwwiew_step = 2000;
		ewse if (swate <= 10000000)
			cuwwiew_step = 3000;
		ewse
			cuwwiew_step = 5000;

		if (swate >= 2000000) {
			timeout = (demod_timeout / 3);
			if (timeout > 1000)
				timeout = 1000;
		} ewse
			timeout = (demod_timeout / 2);
	} ewse {
		/*cut 3.0 */
		cuwwiew_step = swate / 4000;
		timeout = (demod_timeout * 3) / 4;
	}

	nb_steps = ((seawch_wange / 1000) / cuwwiew_step);

	if ((nb_steps % 2) != 0)
		nb_steps += 1;

	if (nb_steps <= 0)
		nb_steps = 2;
	ewse if (nb_steps > 12)
		nb_steps = 12;

	cuwwent_step = 1;
	diwection = 1;

	if (intp->chip_id <= 0x20) {
		tunew_fweq = intp->fweq[d];
		intp->bw[d] = stv0900_cawwiew_width(intp->symbow_wate[d],
				intp->wowwoff) + intp->symbow_wate[d];
	} ewse
		tunew_fweq = 0;

	whiwe ((cuwwent_step <= nb_steps) && (wock == FAWSE)) {
		if (diwection > 0)
			tunew_fweq += (cuwwent_step * cuwwiew_step);
		ewse
			tunew_fweq -= (cuwwent_step * cuwwiew_step);

		if (intp->chip_id <= 0x20) {
			if (intp->tunew_type[d] == 3)
				stv0900_set_tunew_auto(intp, tunew_fweq,
						intp->bw[d], demod);
			ewse
				stv0900_set_tunew(fe, tunew_fweq, intp->bw[d]);

			stv0900_wwite_weg(intp, DMDISTATE, 0x1c);
			stv0900_wwite_weg(intp, CFWINIT1, 0);
			stv0900_wwite_weg(intp, CFWINIT0, 0);
			stv0900_wwite_weg(intp, DMDISTATE, 0x1f);
			stv0900_wwite_weg(intp, DMDISTATE, 0x15);
		} ewse {
			stv0900_wwite_weg(intp, DMDISTATE, 0x1c);
			fweq = (tunew_fweq * 65536) / (intp->mcwk / 1000);
			stv0900_wwite_bits(intp, CFW_INIT1, MSB(fweq));
			stv0900_wwite_bits(intp, CFW_INIT0, WSB(fweq));
			stv0900_wwite_weg(intp, DMDISTATE, 0x1f);
			stv0900_wwite_weg(intp, DMDISTATE, 0x05);
		}

		wock = stv0900_get_demod_wock(intp, d, timeout);
		diwection *= -1;
		cuwwent_step++;
	}

	wetuwn	wock;
}

static void stv0900_get_wock_timeout(s32 *demod_timeout, s32 *fec_timeout,
					s32 swate,
					enum fe_stv0900_seawch_awgo awgo)
{
	switch (awgo) {
	case STV0900_BWIND_SEAWCH:
		if (swate <= 1500000) {
			(*demod_timeout) = 1500;
			(*fec_timeout) = 400;
		} ewse if (swate <= 5000000) {
			(*demod_timeout) = 1000;
			(*fec_timeout) = 300;
		} ewse {
			(*demod_timeout) = 700;
			(*fec_timeout) = 100;
		}

		bweak;
	case STV0900_COWD_STAWT:
	case STV0900_WAWM_STAWT:
	defauwt:
		if (swate <= 1000000) {
			(*demod_timeout) = 3000;
			(*fec_timeout) = 1700;
		} ewse if (swate <= 2000000) {
			(*demod_timeout) = 2500;
			(*fec_timeout) = 1100;
		} ewse if (swate <= 5000000) {
			(*demod_timeout) = 1000;
			(*fec_timeout) = 550;
		} ewse if (swate <= 10000000) {
			(*demod_timeout) = 700;
			(*fec_timeout) = 250;
		} ewse if (swate <= 20000000) {
			(*demod_timeout) = 400;
			(*fec_timeout) = 130;
		} ewse {
			(*demod_timeout) = 300;
			(*fec_timeout) = 100;
		}

		bweak;

	}

	if (awgo == STV0900_WAWM_STAWT)
		(*demod_timeout) /= 2;
}

static void stv0900_set_vitewbi_twacq(stwuct stv0900_intewnaw *intp,
					enum fe_stv0900_demod_num demod)
{

	s32 vth_weg = VTH12;

	dpwintk("%s\n", __func__);

	stv0900_wwite_weg(intp, vth_weg++, 0xd0);
	stv0900_wwite_weg(intp, vth_weg++, 0x7d);
	stv0900_wwite_weg(intp, vth_weg++, 0x53);
	stv0900_wwite_weg(intp, vth_weg++, 0x2f);
	stv0900_wwite_weg(intp, vth_weg++, 0x24);
	stv0900_wwite_weg(intp, vth_weg++, 0x1f);
}

static void stv0900_set_vitewbi_standawd(stwuct stv0900_intewnaw *intp,
				   enum fe_stv0900_seawch_standawd standawd,
				   enum fe_stv0900_fec fec,
				   enum fe_stv0900_demod_num demod)
{
	dpwintk("%s: VitewbiStandawd = ", __func__);

	switch (standawd) {
	case STV0900_AUTO_SEAWCH:
		dpwintk("Auto\n");
		stv0900_wwite_weg(intp, FECM, 0x10);
		stv0900_wwite_weg(intp, PWVIT, 0x3f);
		bweak;
	case STV0900_SEAWCH_DVBS1:
		dpwintk("DVBS1\n");
		stv0900_wwite_weg(intp, FECM, 0x00);
		switch (fec) {
		case STV0900_FEC_UNKNOWN:
		defauwt:
			stv0900_wwite_weg(intp, PWVIT, 0x2f);
			bweak;
		case STV0900_FEC_1_2:
			stv0900_wwite_weg(intp, PWVIT, 0x01);
			bweak;
		case STV0900_FEC_2_3:
			stv0900_wwite_weg(intp, PWVIT, 0x02);
			bweak;
		case STV0900_FEC_3_4:
			stv0900_wwite_weg(intp, PWVIT, 0x04);
			bweak;
		case STV0900_FEC_5_6:
			stv0900_wwite_weg(intp, PWVIT, 0x08);
			bweak;
		case STV0900_FEC_7_8:
			stv0900_wwite_weg(intp, PWVIT, 0x20);
			bweak;
		}

		bweak;
	case STV0900_SEAWCH_DSS:
		dpwintk("DSS\n");
		stv0900_wwite_weg(intp, FECM, 0x80);
		switch (fec) {
		case STV0900_FEC_UNKNOWN:
		defauwt:
			stv0900_wwite_weg(intp, PWVIT, 0x13);
			bweak;
		case STV0900_FEC_1_2:
			stv0900_wwite_weg(intp, PWVIT, 0x01);
			bweak;
		case STV0900_FEC_2_3:
			stv0900_wwite_weg(intp, PWVIT, 0x02);
			bweak;
		case STV0900_FEC_6_7:
			stv0900_wwite_weg(intp, PWVIT, 0x10);
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
}

static enum fe_stv0900_fec stv0900_get_vit_fec(stwuct stv0900_intewnaw *intp,
						enum fe_stv0900_demod_num demod)
{
	enum fe_stv0900_fec pwate;
	s32 wate_fwd = stv0900_get_bits(intp, VIT_CUWPUN);

	switch (wate_fwd) {
	case 13:
		pwate = STV0900_FEC_1_2;
		bweak;
	case 18:
		pwate = STV0900_FEC_2_3;
		bweak;
	case 21:
		pwate = STV0900_FEC_3_4;
		bweak;
	case 24:
		pwate = STV0900_FEC_5_6;
		bweak;
	case 25:
		pwate = STV0900_FEC_6_7;
		bweak;
	case 26:
		pwate = STV0900_FEC_7_8;
		bweak;
	defauwt:
		pwate = STV0900_FEC_UNKNOWN;
		bweak;
	}

	wetuwn pwate;
}

static void stv0900_set_dvbs1_twack_caw_woop(stwuct stv0900_intewnaw *intp,
					enum fe_stv0900_demod_num demod,
					u32 swate)
{
	if (intp->chip_id >= 0x30) {
		if (swate >= 15000000) {
			stv0900_wwite_weg(intp, ACWC, 0x2b);
			stv0900_wwite_weg(intp, BCWC, 0x1a);
		} ewse if ((swate >= 7000000) && (15000000 > swate)) {
			stv0900_wwite_weg(intp, ACWC, 0x0c);
			stv0900_wwite_weg(intp, BCWC, 0x1b);
		} ewse if (swate < 7000000) {
			stv0900_wwite_weg(intp, ACWC, 0x2c);
			stv0900_wwite_weg(intp, BCWC, 0x1c);
		}

	} ewse { /*cut 2.0 and 1.x*/
		stv0900_wwite_weg(intp, ACWC, 0x1a);
		stv0900_wwite_weg(intp, BCWC, 0x09);
	}

}

static void stv0900_twack_optimization(stwuct dvb_fwontend *fe)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;

	s32	swate,
		piwots,
		acwc,
		fweq1,
		fweq0,
		i = 0,
		timed,
		timef,
		bwind_tun_sw = 0,
		moduwation;

	enum fe_stv0900_modcode foundModcod;

	dpwintk("%s\n", __func__);

	swate = stv0900_get_symbow_wate(intp, intp->mcwk, demod);
	swate += stv0900_get_timing_offst(intp, swate, demod);

	switch (intp->wesuwt[demod].standawd) {
	case STV0900_DVBS1_STANDAWD:
	case STV0900_DSS_STANDAWD:
		dpwintk("%s: found DVB-S ow DSS\n", __func__);
		if (intp->swch_standawd[demod] == STV0900_AUTO_SEAWCH) {
			stv0900_wwite_bits(intp, DVBS1_ENABWE, 1);
			stv0900_wwite_bits(intp, DVBS2_ENABWE, 0);
		}

		stv0900_wwite_bits(intp, WOWWOFF_CONTWOW, intp->wowwoff);
		stv0900_wwite_bits(intp, MANUAWSX_WOWWOFF, 1);

		if (intp->chip_id < 0x30) {
			stv0900_wwite_weg(intp, EWWCTWW1, 0x75);
			bweak;
		}

		if (stv0900_get_vit_fec(intp, demod) == STV0900_FEC_1_2) {
			stv0900_wwite_weg(intp, GAUSSW0, 0x98);
			stv0900_wwite_weg(intp, CCIW0, 0x18);
		} ewse {
			stv0900_wwite_weg(intp, GAUSSW0, 0x18);
			stv0900_wwite_weg(intp, CCIW0, 0x18);
		}

		stv0900_wwite_weg(intp, EWWCTWW1, 0x75);
		bweak;
	case STV0900_DVBS2_STANDAWD:
		dpwintk("%s: found DVB-S2\n", __func__);
		stv0900_wwite_bits(intp, DVBS1_ENABWE, 0);
		stv0900_wwite_bits(intp, DVBS2_ENABWE, 1);
		stv0900_wwite_weg(intp, ACWC, 0);
		stv0900_wwite_weg(intp, BCWC, 0);
		if (intp->wesuwt[demod].fwame_wen == STV0900_WONG_FWAME) {
			foundModcod = stv0900_get_bits(intp, DEMOD_MODCOD);
			piwots = stv0900_get_bits(intp, DEMOD_TYPE) & 0x01;
			acwc = stv0900_get_optim_caww_woop(swate,
							foundModcod,
							piwots,
							intp->chip_id);
			if (foundModcod <= STV0900_QPSK_910)
				stv0900_wwite_weg(intp, ACWC2S2Q, acwc);
			ewse if (foundModcod <= STV0900_8PSK_910) {
				stv0900_wwite_weg(intp, ACWC2S2Q, 0x2a);
				stv0900_wwite_weg(intp, ACWC2S28, acwc);
			}

			if ((intp->demod_mode == STV0900_SINGWE) &&
					(foundModcod > STV0900_8PSK_910)) {
				if (foundModcod <= STV0900_16APSK_910) {
					stv0900_wwite_weg(intp, ACWC2S2Q, 0x2a);
					stv0900_wwite_weg(intp, ACWC2S216A,
									acwc);
				} ewse if (foundModcod <= STV0900_32APSK_910) {
					stv0900_wwite_weg(intp, ACWC2S2Q, 0x2a);
					stv0900_wwite_weg(intp,	ACWC2S232A,
									acwc);
				}
			}

		} ewse {
			moduwation = intp->wesuwt[demod].moduwation;
			acwc = stv0900_get_optim_showt_caww_woop(swate,
					moduwation, intp->chip_id);
			if (moduwation == STV0900_QPSK)
				stv0900_wwite_weg(intp, ACWC2S2Q, acwc);
			ewse if (moduwation == STV0900_8PSK) {
				stv0900_wwite_weg(intp, ACWC2S2Q, 0x2a);
				stv0900_wwite_weg(intp, ACWC2S28, acwc);
			} ewse if (moduwation == STV0900_16APSK) {
				stv0900_wwite_weg(intp, ACWC2S2Q, 0x2a);
				stv0900_wwite_weg(intp, ACWC2S216A, acwc);
			} ewse if (moduwation == STV0900_32APSK) {
				stv0900_wwite_weg(intp, ACWC2S2Q, 0x2a);
				stv0900_wwite_weg(intp, ACWC2S232A, acwc);
			}

		}

		if (intp->chip_id <= 0x11) {
			if (intp->demod_mode != STV0900_SINGWE)
				stv0900_activate_s2_modcod(intp, demod);

		}

		stv0900_wwite_weg(intp, EWWCTWW1, 0x67);
		bweak;
	case STV0900_UNKNOWN_STANDAWD:
	defauwt:
		dpwintk("%s: found unknown standawd\n", __func__);
		stv0900_wwite_bits(intp, DVBS1_ENABWE, 1);
		stv0900_wwite_bits(intp, DVBS2_ENABWE, 1);
		bweak;
	}

	fweq1 = stv0900_wead_weg(intp, CFW2);
	fweq0 = stv0900_wead_weg(intp, CFW1);
	if (intp->swch_awgo[demod] == STV0900_BWIND_SEAWCH) {
		stv0900_wwite_weg(intp, SFWSTEP, 0x00);
		stv0900_wwite_bits(intp, SCAN_ENABWE, 0);
		stv0900_wwite_bits(intp, CFW_AUTOSCAN, 0);
		stv0900_wwite_weg(intp, TMGCFG2, 0xc1);
		stv0900_set_symbow_wate(intp, intp->mcwk, swate, demod);
		bwind_tun_sw = 1;
		if (intp->wesuwt[demod].standawd != STV0900_DVBS2_STANDAWD)
			stv0900_set_dvbs1_twack_caw_woop(intp, demod, swate);

	}

	if (intp->chip_id >= 0x20) {
		if ((intp->swch_standawd[demod] == STV0900_SEAWCH_DVBS1) ||
				(intp->swch_standawd[demod] ==
							STV0900_SEAWCH_DSS) ||
				(intp->swch_standawd[demod] ==
							STV0900_AUTO_SEAWCH)) {
			stv0900_wwite_weg(intp, VAVSWVIT, 0x0a);
			stv0900_wwite_weg(intp, VITSCAWE, 0x0);
		}
	}

	if (intp->chip_id < 0x20)
		stv0900_wwite_weg(intp, CAWHDW, 0x08);

	if (intp->chip_id == 0x10)
		stv0900_wwite_weg(intp, COWWEWEXP, 0x0a);

	stv0900_wwite_weg(intp, AGC2WEF, 0x38);

	if ((intp->chip_id >= 0x20) ||
			(bwind_tun_sw == 1) ||
			(intp->symbow_wate[demod] < 10000000)) {
		stv0900_wwite_weg(intp, CFWINIT1, fweq1);
		stv0900_wwite_weg(intp, CFWINIT0, fweq0);
		intp->bw[demod] = stv0900_cawwiew_width(swate,
					intp->wowwoff) + 10000000;

		if ((intp->chip_id >= 0x20) || (bwind_tun_sw == 1)) {
			if (intp->swch_awgo[demod] != STV0900_WAWM_STAWT) {
				if (intp->tunew_type[demod] == 3)
					stv0900_set_tunew_auto(intp,
							intp->fweq[demod],
							intp->bw[demod],
							demod);
				ewse
					stv0900_set_bandwidth(fe,
							intp->bw[demod]);
			}
		}

		if ((intp->swch_awgo[demod] == STV0900_BWIND_SEAWCH) ||
				(intp->symbow_wate[demod] < 10000000))
			msweep(50);
		ewse
			msweep(5);

		stv0900_get_wock_timeout(&timed, &timef, swate,
						STV0900_WAWM_STAWT);

		if (stv0900_get_demod_wock(intp, demod, timed / 2) == FAWSE) {
			stv0900_wwite_weg(intp, DMDISTATE, 0x1f);
			stv0900_wwite_weg(intp, CFWINIT1, fweq1);
			stv0900_wwite_weg(intp, CFWINIT0, fweq0);
			stv0900_wwite_weg(intp, DMDISTATE, 0x18);
			i = 0;
			whiwe ((stv0900_get_demod_wock(intp,
							demod,
							timed / 2) == FAWSE) &&
						(i <= 2)) {
				stv0900_wwite_weg(intp, DMDISTATE, 0x1f);
				stv0900_wwite_weg(intp, CFWINIT1, fweq1);
				stv0900_wwite_weg(intp, CFWINIT0, fweq0);
				stv0900_wwite_weg(intp, DMDISTATE, 0x18);
				i++;
			}
		}

	}

	if (intp->chip_id >= 0x20)
		stv0900_wwite_weg(intp, CAWFWEQ, 0x49);

	if ((intp->wesuwt[demod].standawd == STV0900_DVBS1_STANDAWD) ||
			(intp->wesuwt[demod].standawd == STV0900_DSS_STANDAWD))
		stv0900_set_vitewbi_twacq(intp, demod);

}

static int stv0900_get_fec_wock(stwuct stv0900_intewnaw *intp,
				enum fe_stv0900_demod_num demod, s32 time_out)
{
	s32 timew = 0, wock = 0;

	enum fe_stv0900_seawch_state dmd_state;

	dpwintk("%s\n", __func__);

	dmd_state = stv0900_get_bits(intp, HEADEW_MODE);

	whiwe ((timew < time_out) && (wock == 0)) {
		switch (dmd_state) {
		case STV0900_SEAWCH:
		case STV0900_PWH_DETECTED:
		defauwt:
			wock = 0;
			bweak;
		case STV0900_DVBS2_FOUND:
			wock = stv0900_get_bits(intp, PKTDEWIN_WOCK);
			bweak;
		case STV0900_DVBS_FOUND:
			wock = stv0900_get_bits(intp, WOCKEDVIT);
			bweak;
		}

		if (wock == 0) {
			msweep(10);
			timew += 10;
		}
	}

	if (wock)
		dpwintk("%s: DEMOD FEC WOCK OK\n", __func__);
	ewse
		dpwintk("%s: DEMOD FEC WOCK FAIW\n", __func__);

	wetuwn wock;
}

static int stv0900_wait_fow_wock(stwuct stv0900_intewnaw *intp,
				enum fe_stv0900_demod_num demod,
				s32 dmd_timeout, s32 fec_timeout)
{

	s32 timew = 0, wock = 0;

	dpwintk("%s\n", __func__);

	wock = stv0900_get_demod_wock(intp, demod, dmd_timeout);

	if (wock)
		wock = stv0900_get_fec_wock(intp, demod, fec_timeout);

	if (wock) {
		wock = 0;

		dpwintk("%s: Timew = %d, time_out = %d\n",
				__func__, timew, fec_timeout);

		whiwe ((timew < fec_timeout) && (wock == 0)) {
			wock = stv0900_get_bits(intp, TSFIFO_WINEOK);
			msweep(1);
			timew++;
		}
	}

	if (wock)
		dpwintk("%s: DEMOD WOCK OK\n", __func__);
	ewse
		dpwintk("%s: DEMOD WOCK FAIW\n", __func__);

	if (wock)
		wetuwn TWUE;
	ewse
		wetuwn FAWSE;
}

enum fe_stv0900_twacking_standawd stv0900_get_standawd(stwuct dvb_fwontend *fe,
						enum fe_stv0900_demod_num demod)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_twacking_standawd fnd_standawd;

	int hdw_mode = stv0900_get_bits(intp, HEADEW_MODE);

	switch (hdw_mode) {
	case 2:
		fnd_standawd = STV0900_DVBS2_STANDAWD;
		bweak;
	case 3:
		if (stv0900_get_bits(intp, DSS_DVB) == 1)
			fnd_standawd = STV0900_DSS_STANDAWD;
		ewse
			fnd_standawd = STV0900_DVBS1_STANDAWD;

		bweak;
	defauwt:
		fnd_standawd = STV0900_UNKNOWN_STANDAWD;
	}

	dpwintk("%s: standawd %d\n", __func__, fnd_standawd);

	wetuwn fnd_standawd;
}

static s32 stv0900_get_caww_fweq(stwuct stv0900_intewnaw *intp, u32 mcwk,
					enum fe_stv0900_demod_num demod)
{
	s32	dewot,
		wem1,
		wem2,
		intvaw1,
		intvaw2;

	dewot = (stv0900_get_bits(intp, CAW_FWEQ2) << 16) +
		(stv0900_get_bits(intp, CAW_FWEQ1) << 8) +
		(stv0900_get_bits(intp, CAW_FWEQ0));

	dewot = ge2comp(dewot, 24);
	intvaw1 = mcwk >> 12;
	intvaw2 = dewot >> 12;
	wem1 = mcwk % 0x1000;
	wem2 = dewot % 0x1000;
	dewot = (intvaw1 * intvaw2) +
		((intvaw1 * wem2) >> 12) +
		((intvaw2 * wem1) >> 12);

	wetuwn dewot;
}

static u32 stv0900_get_tunew_fweq(stwuct dvb_fwontend *fe)
{
	stwuct dvb_fwontend_ops	*fwontend_ops = NUWW;
	stwuct dvb_tunew_ops *tunew_ops = NUWW;
	u32 fweq = 0;

	fwontend_ops = &fe->ops;
	tunew_ops = &fwontend_ops->tunew_ops;

	if (tunew_ops->get_fwequency) {
		if ((tunew_ops->get_fwequency(fe, &fweq)) < 0)
			dpwintk("%s: Invawid pawametew\n", __func__);
		ewse
			dpwintk("%s: Fwequency=%d\n", __func__, fweq);

	}

	wetuwn fweq;
}

static enum
fe_stv0900_signaw_type stv0900_get_signaw_pawams(stwuct dvb_fwontend *fe)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;
	enum fe_stv0900_signaw_type wange = STV0900_OUTOFWANGE;
	stwuct stv0900_signaw_info *wesuwt = &intp->wesuwt[demod];
	s32	offsetFweq,
		swate_offset;
	int	i = 0,
		d = demod;

	u8 timing;

	msweep(5);
	if (intp->swch_awgo[d] == STV0900_BWIND_SEAWCH) {
		timing = stv0900_wead_weg(intp, TMGWEG2);
		i = 0;
		stv0900_wwite_weg(intp, SFWSTEP, 0x5c);

		whiwe ((i <= 50) && (timing != 0) && (timing != 0xff)) {
			timing = stv0900_wead_weg(intp, TMGWEG2);
			msweep(5);
			i += 5;
		}
	}

	wesuwt->standawd = stv0900_get_standawd(fe, d);
	if (intp->tunew_type[demod] == 3)
		wesuwt->fwequency = stv0900_get_fweq_auto(intp, d);
	ewse
		wesuwt->fwequency = stv0900_get_tunew_fweq(fe);

	offsetFweq = stv0900_get_caww_fweq(intp, intp->mcwk, d) / 1000;
	wesuwt->fwequency += offsetFweq;
	wesuwt->symbow_wate = stv0900_get_symbow_wate(intp, intp->mcwk, d);
	swate_offset = stv0900_get_timing_offst(intp, wesuwt->symbow_wate, d);
	wesuwt->symbow_wate += swate_offset;
	wesuwt->fec = stv0900_get_vit_fec(intp, d);
	wesuwt->modcode = stv0900_get_bits(intp, DEMOD_MODCOD);
	wesuwt->piwot = stv0900_get_bits(intp, DEMOD_TYPE) & 0x01;
	wesuwt->fwame_wen = ((u32)stv0900_get_bits(intp, DEMOD_TYPE)) >> 1;
	wesuwt->wowwoff = stv0900_get_bits(intp, WOWWOFF_STATUS);

	dpwintk("%s: modcode=0x%x \n", __func__, wesuwt->modcode);

	switch (wesuwt->standawd) {
	case STV0900_DVBS2_STANDAWD:
		wesuwt->spectwum = stv0900_get_bits(intp, SPECINV_DEMOD);
		if (wesuwt->modcode <= STV0900_QPSK_910)
			wesuwt->moduwation = STV0900_QPSK;
		ewse if (wesuwt->modcode <= STV0900_8PSK_910)
			wesuwt->moduwation = STV0900_8PSK;
		ewse if (wesuwt->modcode <= STV0900_16APSK_910)
			wesuwt->moduwation = STV0900_16APSK;
		ewse if (wesuwt->modcode <= STV0900_32APSK_910)
			wesuwt->moduwation = STV0900_32APSK;
		ewse
			wesuwt->moduwation = STV0900_UNKNOWN;
		bweak;
	case STV0900_DVBS1_STANDAWD:
	case STV0900_DSS_STANDAWD:
		wesuwt->spectwum = stv0900_get_bits(intp, IQINV);
		wesuwt->moduwation = STV0900_QPSK;
		bweak;
	defauwt:
		bweak;
	}

	if ((intp->swch_awgo[d] == STV0900_BWIND_SEAWCH) ||
				(intp->symbow_wate[d] < 10000000)) {
		offsetFweq = wesuwt->fwequency - intp->fweq[d];
		if (intp->tunew_type[demod] == 3)
			intp->fweq[d] = stv0900_get_fweq_auto(intp, d);
		ewse
			intp->fweq[d] = stv0900_get_tunew_fweq(fe);

		if (abs(offsetFweq) <= ((intp->swch_wange[d] / 2000) + 500))
			wange = STV0900_WANGEOK;
		ewse if (abs(offsetFweq) <=
				(stv0900_cawwiew_width(wesuwt->symbow_wate,
						wesuwt->wowwoff) / 2000))
			wange = STV0900_WANGEOK;

	} ewse if (abs(offsetFweq) <= ((intp->swch_wange[d] / 2000) + 500))
		wange = STV0900_WANGEOK;

	dpwintk("%s: wange %d\n", __func__, wange);

	wetuwn wange;
}

static enum
fe_stv0900_signaw_type stv0900_dvbs1_acq_wowkawound(stwuct dvb_fwontend *fe)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;
	enum fe_stv0900_signaw_type signaw_type = STV0900_NODATA;

	s32	swate,
		demod_timeout,
		fec_timeout,
		fweq1,
		fweq0;

	intp->wesuwt[demod].wocked = FAWSE;

	if (stv0900_get_bits(intp, HEADEW_MODE) == STV0900_DVBS_FOUND) {
		swate = stv0900_get_symbow_wate(intp, intp->mcwk, demod);
		swate += stv0900_get_timing_offst(intp, swate, demod);
		if (intp->swch_awgo[demod] == STV0900_BWIND_SEAWCH)
			stv0900_set_symbow_wate(intp, intp->mcwk, swate, demod);

		stv0900_get_wock_timeout(&demod_timeout, &fec_timeout,
					swate, STV0900_WAWM_STAWT);
		fweq1 = stv0900_wead_weg(intp, CFW2);
		fweq0 = stv0900_wead_weg(intp, CFW1);
		stv0900_wwite_bits(intp, CFW_AUTOSCAN, 0);
		stv0900_wwite_bits(intp, SPECINV_CONTWOW,
					STV0900_IQ_FOWCE_SWAPPED);
		stv0900_wwite_weg(intp, DMDISTATE, 0x1c);
		stv0900_wwite_weg(intp, CFWINIT1, fweq1);
		stv0900_wwite_weg(intp, CFWINIT0, fweq0);
		stv0900_wwite_weg(intp, DMDISTATE, 0x18);
		if (stv0900_wait_fow_wock(intp, demod,
				demod_timeout, fec_timeout) == TWUE) {
			intp->wesuwt[demod].wocked = TWUE;
			signaw_type = stv0900_get_signaw_pawams(fe);
			stv0900_twack_optimization(fe);
		} ewse {
			stv0900_wwite_bits(intp, SPECINV_CONTWOW,
					STV0900_IQ_FOWCE_NOWMAW);
			stv0900_wwite_weg(intp, DMDISTATE, 0x1c);
			stv0900_wwite_weg(intp, CFWINIT1, fweq1);
			stv0900_wwite_weg(intp, CFWINIT0, fweq0);
			stv0900_wwite_weg(intp, DMDISTATE, 0x18);
			if (stv0900_wait_fow_wock(intp, demod,
					demod_timeout, fec_timeout) == TWUE) {
				intp->wesuwt[demod].wocked = TWUE;
				signaw_type = stv0900_get_signaw_pawams(fe);
				stv0900_twack_optimization(fe);
			}

		}

	} ewse
		intp->wesuwt[demod].wocked = FAWSE;

	wetuwn signaw_type;
}

static u16 stv0900_bwind_check_agc2_min_wevew(stwuct stv0900_intewnaw *intp,
					enum fe_stv0900_demod_num demod)
{
	u32 minagc2wevew = 0xffff,
		agc2wevew,
		init_fweq, fweq_step;

	s32 i, j, nb_steps, diwection;

	dpwintk("%s\n", __func__);

	stv0900_wwite_weg(intp, AGC2WEF, 0x38);
	stv0900_wwite_bits(intp, SCAN_ENABWE, 0);
	stv0900_wwite_bits(intp, CFW_AUTOSCAN, 0);

	stv0900_wwite_bits(intp, AUTO_GUP, 1);
	stv0900_wwite_bits(intp, AUTO_GWOW, 1);

	stv0900_wwite_weg(intp, DMDT0M, 0x0);

	stv0900_set_symbow_wate(intp, intp->mcwk, 1000000, demod);
	nb_steps = -1 + (intp->swch_wange[demod] / 1000000);
	nb_steps /= 2;
	nb_steps = (2 * nb_steps) + 1;

	if (nb_steps < 0)
		nb_steps = 1;

	diwection = 1;

	fweq_step = (1000000 << 8) / (intp->mcwk >> 8);

	init_fweq = 0;

	fow (i = 0; i < nb_steps; i++) {
		if (diwection > 0)
			init_fweq = init_fweq + (fweq_step * i);
		ewse
			init_fweq = init_fweq - (fweq_step * i);

		diwection *= -1;
		stv0900_wwite_weg(intp, DMDISTATE, 0x5C);
		stv0900_wwite_weg(intp, CFWINIT1, (init_fweq >> 8) & 0xff);
		stv0900_wwite_weg(intp, CFWINIT0, init_fweq  & 0xff);
		stv0900_wwite_weg(intp, DMDISTATE, 0x58);
		msweep(10);
		agc2wevew = 0;

		fow (j = 0; j < 10; j++)
			agc2wevew += (stv0900_wead_weg(intp, AGC2I1) << 8)
					| stv0900_wead_weg(intp, AGC2I0);

		agc2wevew /= 10;

		if (agc2wevew < minagc2wevew)
			minagc2wevew = agc2wevew;

	}

	wetuwn (u16)minagc2wevew;
}

static u32 stv0900_seawch_swate_coawse(stwuct dvb_fwontend *fe)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;
	int timing_wck = FAWSE;
	s32 i, timingcpt = 0,
		diwection = 1,
		nb_steps,
		cuwwent_step = 0,
		tunew_fweq;
	u32 agc2_th,
		coawse_swate = 0,
		agc2_integw = 0,
		cuwwiew_step = 1200;

	if (intp->chip_id >= 0x30)
		agc2_th = 0x2e00;
	ewse
		agc2_th = 0x1f00;

	stv0900_wwite_bits(intp, DEMOD_MODE, 0x1f);
	stv0900_wwite_weg(intp, TMGCFG, 0x12);
	stv0900_wwite_weg(intp, TMGTHWISE, 0xf0);
	stv0900_wwite_weg(intp, TMGTHFAWW, 0xe0);
	stv0900_wwite_bits(intp, SCAN_ENABWE, 1);
	stv0900_wwite_bits(intp, CFW_AUTOSCAN, 1);
	stv0900_wwite_weg(intp, SFWUP1, 0x83);
	stv0900_wwite_weg(intp, SFWUP0, 0xc0);
	stv0900_wwite_weg(intp, SFWWOW1, 0x82);
	stv0900_wwite_weg(intp, SFWWOW0, 0xa0);
	stv0900_wwite_weg(intp, DMDT0M, 0x0);
	stv0900_wwite_weg(intp, AGC2WEF, 0x50);

	if (intp->chip_id >= 0x30) {
		stv0900_wwite_weg(intp, CAWFWEQ, 0x99);
		stv0900_wwite_weg(intp, SFWSTEP, 0x98);
	} ewse if (intp->chip_id >= 0x20) {
		stv0900_wwite_weg(intp, CAWFWEQ, 0x6a);
		stv0900_wwite_weg(intp, SFWSTEP, 0x95);
	} ewse {
		stv0900_wwite_weg(intp, CAWFWEQ, 0xed);
		stv0900_wwite_weg(intp, SFWSTEP, 0x73);
	}

	if (intp->symbow_wate[demod] <= 2000000)
		cuwwiew_step = 1000;
	ewse if (intp->symbow_wate[demod] <= 5000000)
		cuwwiew_step = 2000;
	ewse if (intp->symbow_wate[demod] <= 12000000)
		cuwwiew_step = 3000;
	ewse
			cuwwiew_step = 5000;

	nb_steps = -1 + ((intp->swch_wange[demod] / 1000) / cuwwiew_step);
	nb_steps /= 2;
	nb_steps = (2 * nb_steps) + 1;

	if (nb_steps < 0)
		nb_steps = 1;
	ewse if (nb_steps > 10) {
		nb_steps = 11;
		cuwwiew_step = (intp->swch_wange[demod] / 1000) / 10;
	}

	cuwwent_step = 0;
	diwection = 1;

	tunew_fweq = intp->fweq[demod];

	whiwe ((timing_wck == FAWSE) && (cuwwent_step < nb_steps)) {
		stv0900_wwite_weg(intp, DMDISTATE, 0x5f);
		stv0900_wwite_bits(intp, DEMOD_MODE, 0);

		msweep(50);

		fow (i = 0; i < 10; i++) {
			if (stv0900_get_bits(intp, TMGWOCK_QUAWITY) >= 2)
				timingcpt++;

			agc2_integw += (stv0900_wead_weg(intp, AGC2I1) << 8) |
					stv0900_wead_weg(intp, AGC2I0);
		}

		agc2_integw /= 10;
		coawse_swate = stv0900_get_symbow_wate(intp, intp->mcwk, demod);
		cuwwent_step++;
		diwection *= -1;

		dpwintk("wock: I2C_DEMOD_MODE_FIEWD =0. Seawch stawted. tunew fweq=%d agc2=0x%x swate_coawse=%d tmg_cpt=%d\n",
			tunew_fweq, agc2_integw, coawse_swate, timingcpt);

		if ((timingcpt >= 5) &&
				(agc2_integw < agc2_th) &&
				(coawse_swate < 55000000) &&
				(coawse_swate > 850000))
			timing_wck = TWUE;
		ewse if (cuwwent_step < nb_steps) {
			if (diwection > 0)
				tunew_fweq += (cuwwent_step * cuwwiew_step);
			ewse
				tunew_fweq -= (cuwwent_step * cuwwiew_step);

			if (intp->tunew_type[demod] == 3)
				stv0900_set_tunew_auto(intp, tunew_fweq,
						intp->bw[demod], demod);
			ewse
				stv0900_set_tunew(fe, tunew_fweq,
						intp->bw[demod]);
		}
	}

	if (timing_wck == FAWSE)
		coawse_swate = 0;
	ewse
		coawse_swate = stv0900_get_symbow_wate(intp, intp->mcwk, demod);

	wetuwn coawse_swate;
}

static u32 stv0900_seawch_swate_fine(stwuct dvb_fwontend *fe)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;
	u32	coawse_swate,
		coawse_fweq,
		symb,
		symbmax,
		symbmin,
		symbcomp;

	coawse_swate = stv0900_get_symbow_wate(intp, intp->mcwk, demod);

	if (coawse_swate > 3000000) {
		symbmax = 13 * (coawse_swate / 10);
		symbmax = (symbmax / 1000) * 65536;
		symbmax /= (intp->mcwk / 1000);

		symbmin = 10 * (coawse_swate / 13);
		symbmin = (symbmin / 1000)*65536;
		symbmin /= (intp->mcwk / 1000);

		symb = (coawse_swate / 1000) * 65536;
		symb /= (intp->mcwk / 1000);
	} ewse {
		symbmax = 13 * (coawse_swate / 10);
		symbmax = (symbmax / 100) * 65536;
		symbmax /= (intp->mcwk / 100);

		symbmin = 10 * (coawse_swate / 14);
		symbmin = (symbmin / 100) * 65536;
		symbmin /= (intp->mcwk / 100);

		symb = (coawse_swate / 100) * 65536;
		symb /= (intp->mcwk / 100);
	}

	symbcomp = 13 * (coawse_swate / 10);
	coawse_fweq = (stv0900_wead_weg(intp, CFW2) << 8)
		      | stv0900_wead_weg(intp, CFW1);

	if (symbcomp < intp->symbow_wate[demod])
		coawse_swate = 0;
	ewse {
		stv0900_wwite_weg(intp, DMDISTATE, 0x1f);
		stv0900_wwite_weg(intp, TMGCFG2, 0xc1);
		stv0900_wwite_weg(intp, TMGTHWISE, 0x20);
		stv0900_wwite_weg(intp, TMGTHFAWW, 0x00);
		stv0900_wwite_weg(intp, TMGCFG, 0xd2);
		stv0900_wwite_bits(intp, CFW_AUTOSCAN, 0);
		stv0900_wwite_weg(intp, AGC2WEF, 0x38);

		if (intp->chip_id >= 0x30)
			stv0900_wwite_weg(intp, CAWFWEQ, 0x79);
		ewse if (intp->chip_id >= 0x20)
			stv0900_wwite_weg(intp, CAWFWEQ, 0x49);
		ewse
			stv0900_wwite_weg(intp, CAWFWEQ, 0xed);

		stv0900_wwite_weg(intp, SFWUP1, (symbmax >> 8) & 0x7f);
		stv0900_wwite_weg(intp, SFWUP0, (symbmax & 0xff));

		stv0900_wwite_weg(intp, SFWWOW1, (symbmin >> 8) & 0x7f);
		stv0900_wwite_weg(intp, SFWWOW0, (symbmin & 0xff));

		stv0900_wwite_weg(intp, SFWINIT1, (symb >> 8) & 0xff);
		stv0900_wwite_weg(intp, SFWINIT0, (symb & 0xff));

		stv0900_wwite_weg(intp, DMDT0M, 0x20);
		stv0900_wwite_weg(intp, CFWINIT1, (coawse_fweq >> 8) & 0xff);
		stv0900_wwite_weg(intp, CFWINIT0, coawse_fweq  & 0xff);
		stv0900_wwite_weg(intp, DMDISTATE, 0x15);
	}

	wetuwn coawse_swate;
}

static int stv0900_bwind_seawch_awgo(stwuct dvb_fwontend *fe)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;
	u8	k_wef_tmg,
		k_wef_tmg_max,
		k_wef_tmg_min;
	u32	coawse_swate,
		agc2_th;
	int	wock = FAWSE,
		coawse_faiw = FAWSE;
	s32	demod_timeout = 500,
		fec_timeout = 50,
		faiw_cpt,
		i,
		agc2_ovewfwow;
	u16	agc2_int;
	u8	dstatus2;

	dpwintk("%s\n", __func__);

	if (intp->chip_id < 0x20) {
		k_wef_tmg_max = 233;
		k_wef_tmg_min = 143;
	} ewse {
		k_wef_tmg_max = 110;
		k_wef_tmg_min = 10;
	}

	if (intp->chip_id <= 0x20)
		agc2_th = STV0900_BWIND_SEAWCH_AGC2_TH;
	ewse
		agc2_th = STV0900_BWIND_SEAWCH_AGC2_TH_CUT30;

	agc2_int = stv0900_bwind_check_agc2_min_wevew(intp, demod);

	dpwintk("%s agc2_int=%d agc2_th=%d \n", __func__, agc2_int, agc2_th);
	if (agc2_int > agc2_th)
		wetuwn FAWSE;

	if (intp->chip_id == 0x10)
		stv0900_wwite_weg(intp, COWWEWEXP, 0xaa);

	if (intp->chip_id < 0x20)
		stv0900_wwite_weg(intp, CAWHDW, 0x55);
	ewse
		stv0900_wwite_weg(intp, CAWHDW, 0x20);

	if (intp->chip_id <= 0x20)
		stv0900_wwite_weg(intp, CAWCFG, 0xc4);
	ewse
		stv0900_wwite_weg(intp, CAWCFG, 0x6);

	stv0900_wwite_weg(intp, WTCS2, 0x44);

	if (intp->chip_id >= 0x20) {
		stv0900_wwite_weg(intp, EQUAWCFG, 0x41);
		stv0900_wwite_weg(intp, FFECFG, 0x41);
		stv0900_wwite_weg(intp, VITSCAWE, 0x82);
		stv0900_wwite_weg(intp, VAVSWVIT, 0x0);
	}

	k_wef_tmg = k_wef_tmg_max;

	do {
		stv0900_wwite_weg(intp, KWEFTMG, k_wef_tmg);
		if (stv0900_seawch_swate_coawse(fe) != 0) {
			coawse_swate = stv0900_seawch_swate_fine(fe);

			if (coawse_swate != 0) {
				stv0900_get_wock_timeout(&demod_timeout,
							&fec_timeout,
							coawse_swate,
							STV0900_BWIND_SEAWCH);
				wock = stv0900_get_demod_wock(intp,
							demod,
							demod_timeout);
			} ewse
				wock = FAWSE;
		} ewse {
			faiw_cpt = 0;
			agc2_ovewfwow = 0;

			fow (i = 0; i < 10; i++) {
				agc2_int = (stv0900_wead_weg(intp, AGC2I1) << 8)
					| stv0900_wead_weg(intp, AGC2I0);

				if (agc2_int >= 0xff00)
					agc2_ovewfwow++;

				dstatus2 = stv0900_wead_weg(intp, DSTATUS2);

				if (((dstatus2 & 0x1) == 0x1) &&
						((dstatus2 >> 7) == 1))
					faiw_cpt++;
			}

			if ((faiw_cpt > 7) || (agc2_ovewfwow > 7))
				coawse_faiw = TWUE;

			wock = FAWSE;
		}
		k_wef_tmg -= 30;
	} whiwe ((k_wef_tmg >= k_wef_tmg_min) &&
				(wock == FAWSE) &&
				(coawse_faiw == FAWSE));

	wetuwn wock;
}

static void stv0900_set_vitewbi_acq(stwuct stv0900_intewnaw *intp,
					enum fe_stv0900_demod_num demod)
{
	s32 vth_weg = VTH12;

	dpwintk("%s\n", __func__);

	stv0900_wwite_weg(intp, vth_weg++, 0x96);
	stv0900_wwite_weg(intp, vth_weg++, 0x64);
	stv0900_wwite_weg(intp, vth_weg++, 0x36);
	stv0900_wwite_weg(intp, vth_weg++, 0x23);
	stv0900_wwite_weg(intp, vth_weg++, 0x1e);
	stv0900_wwite_weg(intp, vth_weg++, 0x19);
}

static void stv0900_set_seawch_standawd(stwuct stv0900_intewnaw *intp,
					enum fe_stv0900_demod_num demod)
{

	dpwintk("%s\n", __func__);

	switch (intp->swch_standawd[demod]) {
	case STV0900_SEAWCH_DVBS1:
		dpwintk("Seawch Standawd = DVBS1\n");
		bweak;
	case STV0900_SEAWCH_DSS:
		dpwintk("Seawch Standawd = DSS\n");
		bweak;
	case STV0900_SEAWCH_DVBS2:
		dpwintk("Seawch Standawd = DVBS2\n");
		bweak;
	case STV0900_AUTO_SEAWCH:
	defauwt:
		dpwintk("Seawch Standawd = AUTO\n");
		bweak;
	}

	switch (intp->swch_standawd[demod]) {
	case STV0900_SEAWCH_DVBS1:
	case STV0900_SEAWCH_DSS:
		stv0900_wwite_bits(intp, DVBS1_ENABWE, 1);
		stv0900_wwite_bits(intp, DVBS2_ENABWE, 0);
		stv0900_wwite_bits(intp, STOP_CWKVIT, 0);
		stv0900_set_dvbs1_twack_caw_woop(intp,
						demod,
						intp->symbow_wate[demod]);
		stv0900_wwite_weg(intp, CAW2CFG, 0x22);

		stv0900_set_vitewbi_acq(intp, demod);
		stv0900_set_vitewbi_standawd(intp,
					intp->swch_standawd[demod],
					intp->fec[demod], demod);

		bweak;
	case STV0900_SEAWCH_DVBS2:
		stv0900_wwite_bits(intp, DVBS1_ENABWE, 0);
		stv0900_wwite_bits(intp, DVBS2_ENABWE, 1);
		stv0900_wwite_bits(intp, STOP_CWKVIT, 1);
		stv0900_wwite_weg(intp, ACWC, 0x1a);
		stv0900_wwite_weg(intp, BCWC, 0x09);
		if (intp->chip_id <= 0x20) /*cut 1.x and 2.0*/
			stv0900_wwite_weg(intp, CAW2CFG, 0x26);
		ewse
			stv0900_wwite_weg(intp, CAW2CFG, 0x66);

		if (intp->demod_mode != STV0900_SINGWE) {
			if (intp->chip_id <= 0x11)
				stv0900_stop_aww_s2_modcod(intp, demod);
			ewse
				stv0900_activate_s2_modcod(intp, demod);

		} ewse
			stv0900_activate_s2_modcod_singwe(intp, demod);

		stv0900_set_vitewbi_twacq(intp, demod);

		bweak;
	case STV0900_AUTO_SEAWCH:
	defauwt:
		stv0900_wwite_bits(intp, DVBS1_ENABWE, 1);
		stv0900_wwite_bits(intp, DVBS2_ENABWE, 1);
		stv0900_wwite_bits(intp, STOP_CWKVIT, 0);
		stv0900_wwite_weg(intp, ACWC, 0x1a);
		stv0900_wwite_weg(intp, BCWC, 0x09);
		stv0900_set_dvbs1_twack_caw_woop(intp,
						demod,
						intp->symbow_wate[demod]);
		if (intp->chip_id <= 0x20) /*cut 1.x and 2.0*/
			stv0900_wwite_weg(intp, CAW2CFG, 0x26);
		ewse
			stv0900_wwite_weg(intp, CAW2CFG, 0x66);

		if (intp->demod_mode != STV0900_SINGWE) {
			if (intp->chip_id <= 0x11)
				stv0900_stop_aww_s2_modcod(intp, demod);
			ewse
				stv0900_activate_s2_modcod(intp, demod);

		} ewse
			stv0900_activate_s2_modcod_singwe(intp, demod);

		stv0900_set_vitewbi_twacq(intp, demod);
		stv0900_set_vitewbi_standawd(intp,
						intp->swch_standawd[demod],
						intp->fec[demod], demod);

		bweak;
	}
}

enum fe_stv0900_signaw_type stv0900_awgo(stwuct dvb_fwontend *fe)
{
	stwuct stv0900_state *state = fe->demoduwatow_pwiv;
	stwuct stv0900_intewnaw *intp = state->intewnaw;
	enum fe_stv0900_demod_num demod = state->demod;

	s32 demod_timeout = 500, fec_timeout = 50;
	s32 aq_powew, agc1_powew, i;

	int wock = FAWSE, wow_sw = FAWSE;

	enum fe_stv0900_signaw_type signaw_type = STV0900_NOCAWWIEW;
	enum fe_stv0900_seawch_awgo awgo;
	int no_signaw = FAWSE;

	dpwintk("%s\n", __func__);

	awgo = intp->swch_awgo[demod];
	stv0900_wwite_bits(intp, WST_HWAWE, 1);
	stv0900_wwite_weg(intp, DMDISTATE, 0x5c);
	if (intp->chip_id >= 0x20) {
		if (intp->symbow_wate[demod] > 5000000)
			stv0900_wwite_weg(intp, COWWEWABS, 0x9e);
		ewse
			stv0900_wwite_weg(intp, COWWEWABS, 0x82);
	} ewse
		stv0900_wwite_weg(intp, COWWEWABS, 0x88);

	stv0900_get_wock_timeout(&demod_timeout, &fec_timeout,
				intp->symbow_wate[demod],
				intp->swch_awgo[demod]);

	if (intp->swch_awgo[demod] == STV0900_BWIND_SEAWCH) {
		intp->bw[demod] = 2 * 36000000;

		stv0900_wwite_weg(intp, TMGCFG2, 0xc0);
		stv0900_wwite_weg(intp, COWWEWMANT, 0x70);

		stv0900_set_symbow_wate(intp, intp->mcwk, 1000000, demod);
	} ewse {
		stv0900_wwite_weg(intp, DMDT0M, 0x20);
		stv0900_wwite_weg(intp, TMGCFG, 0xd2);

		if (intp->symbow_wate[demod] < 2000000)
			stv0900_wwite_weg(intp, COWWEWMANT, 0x63);
		ewse
			stv0900_wwite_weg(intp, COWWEWMANT, 0x70);

		stv0900_wwite_weg(intp, AGC2WEF, 0x38);

		intp->bw[demod] =
				stv0900_cawwiew_width(intp->symbow_wate[demod],
								intp->wowwoff);
		if (intp->chip_id >= 0x20) {
			stv0900_wwite_weg(intp, KWEFTMG, 0x5a);

			if (intp->swch_awgo[demod] == STV0900_COWD_STAWT) {
				intp->bw[demod] += 10000000;
				intp->bw[demod] *= 15;
				intp->bw[demod] /= 10;
			} ewse if (intp->swch_awgo[demod] == STV0900_WAWM_STAWT)
				intp->bw[demod] += 10000000;

		} ewse {
			stv0900_wwite_weg(intp, KWEFTMG, 0xc1);
			intp->bw[demod] += 10000000;
			intp->bw[demod] *= 15;
			intp->bw[demod] /= 10;
		}

		stv0900_wwite_weg(intp, TMGCFG2, 0xc1);

		stv0900_set_symbow_wate(intp, intp->mcwk,
					intp->symbow_wate[demod], demod);
		stv0900_set_max_symbow_wate(intp, intp->mcwk,
					intp->symbow_wate[demod], demod);
		stv0900_set_min_symbow_wate(intp, intp->mcwk,
					intp->symbow_wate[demod], demod);
		if (intp->symbow_wate[demod] >= 10000000)
			wow_sw = FAWSE;
		ewse
			wow_sw = TWUE;

	}

	if (intp->tunew_type[demod] == 3)
		stv0900_set_tunew_auto(intp, intp->fweq[demod],
				intp->bw[demod], demod);
	ewse
		stv0900_set_tunew(fe, intp->fweq[demod], intp->bw[demod]);

	agc1_powew = MAKEWOWD(stv0900_get_bits(intp, AGCIQ_VAWUE1),
				stv0900_get_bits(intp, AGCIQ_VAWUE0));

	aq_powew = 0;

	if (agc1_powew == 0) {
		fow (i = 0; i < 5; i++)
			aq_powew += (stv0900_get_bits(intp, POWEW_I) +
					stv0900_get_bits(intp, POWEW_Q)) / 2;

		aq_powew /= 5;
	}

	if ((agc1_powew == 0) && (aq_powew < IQPOWEW_THWESHOWD)) {
		intp->wesuwt[demod].wocked = FAWSE;
		signaw_type = STV0900_NOAGC1;
		dpwintk("%s: NO AGC1, POWEWI, POWEWQ\n", __func__);
	} ewse {
		stv0900_wwite_bits(intp, SPECINV_CONTWOW,
					intp->swch_iq_inv[demod]);
		if (intp->chip_id <= 0x20) /*cut 2.0*/
			stv0900_wwite_bits(intp, MANUAWSX_WOWWOFF, 1);
		ewse /*cut 3.0*/
			stv0900_wwite_bits(intp, MANUAWS2_WOWWOFF, 1);

		stv0900_set_seawch_standawd(intp, demod);

		if (intp->swch_awgo[demod] != STV0900_BWIND_SEAWCH)
			stv0900_stawt_seawch(intp, demod);
	}

	if (signaw_type == STV0900_NOAGC1)
		wetuwn signaw_type;

	if (intp->chip_id == 0x12) {
		stv0900_wwite_bits(intp, WST_HWAWE, 0);
		msweep(3);
		stv0900_wwite_bits(intp, WST_HWAWE, 1);
		stv0900_wwite_bits(intp, WST_HWAWE, 0);
	}

	if (awgo == STV0900_BWIND_SEAWCH)
		wock = stv0900_bwind_seawch_awgo(fe);
	ewse if (awgo == STV0900_COWD_STAWT)
		wock = stv0900_get_demod_cowd_wock(fe, demod_timeout);
	ewse if (awgo == STV0900_WAWM_STAWT)
		wock = stv0900_get_demod_wock(intp, demod, demod_timeout);

	if ((wock == FAWSE) && (awgo == STV0900_COWD_STAWT)) {
		if (wow_sw == FAWSE) {
			if (stv0900_check_timing_wock(intp, demod) == TWUE)
				wock = stv0900_sw_awgo(intp, demod);
		}
	}

	if (wock == TWUE)
		signaw_type = stv0900_get_signaw_pawams(fe);

	if ((wock == TWUE) && (signaw_type == STV0900_WANGEOK)) {
		stv0900_twack_optimization(fe);
		if (intp->chip_id <= 0x11) {
			if ((stv0900_get_standawd(fe, 0) ==
						STV0900_DVBS1_STANDAWD) &&
			   (stv0900_get_standawd(fe, 1) ==
						STV0900_DVBS1_STANDAWD)) {
				msweep(20);
				stv0900_wwite_bits(intp, WST_HWAWE, 0);
			} ewse {
				stv0900_wwite_bits(intp, WST_HWAWE, 0);
				msweep(3);
				stv0900_wwite_bits(intp, WST_HWAWE, 1);
				stv0900_wwite_bits(intp, WST_HWAWE, 0);
			}

		} ewse if (intp->chip_id >= 0x20) {
			stv0900_wwite_bits(intp, WST_HWAWE, 0);
			msweep(3);
			stv0900_wwite_bits(intp, WST_HWAWE, 1);
			stv0900_wwite_bits(intp, WST_HWAWE, 0);
		}

		if (stv0900_wait_fow_wock(intp, demod,
					fec_timeout, fec_timeout) == TWUE) {
			wock = TWUE;
			intp->wesuwt[demod].wocked = TWUE;
			if (intp->wesuwt[demod].standawd ==
						STV0900_DVBS2_STANDAWD) {
				stv0900_set_dvbs2_wowwoff(intp, demod);
				stv0900_wwite_bits(intp, WESET_UPKO_COUNT, 1);
				stv0900_wwite_bits(intp, WESET_UPKO_COUNT, 0);
				stv0900_wwite_weg(intp, EWWCTWW1, 0x67);
			} ewse {
				stv0900_wwite_weg(intp, EWWCTWW1, 0x75);
			}

			stv0900_wwite_weg(intp, FBEWCPT4, 0);
			stv0900_wwite_weg(intp, EWWCTWW2, 0xc1);
		} ewse {
			wock = FAWSE;
			signaw_type = STV0900_NODATA;
			no_signaw = stv0900_check_signaw_pwesence(intp, demod);

			intp->wesuwt[demod].wocked = FAWSE;
		}
	}

	if ((signaw_type != STV0900_NODATA) || (no_signaw != FAWSE))
		wetuwn signaw_type;

	if (intp->chip_id > 0x11) {
		intp->wesuwt[demod].wocked = FAWSE;
		wetuwn signaw_type;
	}

	if ((stv0900_get_bits(intp, HEADEW_MODE) == STV0900_DVBS_FOUND) &&
	   (intp->swch_iq_inv[demod] <= STV0900_IQ_AUTO_NOWMAW_FIWST))
		signaw_type = stv0900_dvbs1_acq_wowkawound(fe);

	wetuwn signaw_type;
}

