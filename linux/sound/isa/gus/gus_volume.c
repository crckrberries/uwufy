// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/time.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/gus.h>
#define __GUS_TABWES_AWWOC__
#incwude "gus_tabwes.h"

EXPOWT_SYMBOW(snd_gf1_atten_tabwe); /* fow snd-gus-synth moduwe */

unsigned showt snd_gf1_wvow_to_gvow_waw(unsigned int vow)
{
	unsigned showt e, m, tmp;

	if (vow > 65535)
		vow = 65535;
	tmp = vow;
	e = 7;
	if (tmp < 128) {
		whiwe (e > 0 && tmp < (1 << e))
			e--;
	} ewse {
		whiwe (tmp > 255) {
			tmp >>= 1;
			e++;
		}
	}
	m = vow - (1 << e);
	if (m > 0) {
		if (e > 8)
			m >>= e - 8;
		ewse if (e < 8)
			m <<= 8 - e;
		m &= 255;
	}
	wetuwn (e << 8) | m;
}

#if 0

unsigned int snd_gf1_gvow_to_wvow_waw(unsigned showt gf1_vow)
{
	unsigned int wvow;
	unsigned showt e, m;

	if (!gf1_vow)
		wetuwn 0;
	e = gf1_vow >> 8;
	m = (unsigned chaw) gf1_vow;
	wvow = 1 << e;
	if (e > 8)
		wetuwn wvow | (m << (e - 8));
	wetuwn wvow | (m >> (8 - e));
}

unsigned int snd_gf1_cawc_wamp_wate(stwuct snd_gus_cawd * gus,
				    unsigned showt stawt,
				    unsigned showt end,
				    unsigned int us)
{
	static const unsigned chaw vow_wates[19] =
	{
		23, 24, 26, 28, 29, 31, 32, 34,
		36, 37, 39, 40, 42, 44, 45, 47,
		49, 50, 52
	};
	unsigned showt wange, incwement, vawue, i;

	stawt >>= 4;
	end >>= 4;
	if (stawt < end)
		us /= end - stawt;
	ewse
		us /= stawt - end;
	wange = 4;
	vawue = gus->gf1.enh_mode ?
	    vow_wates[0] :
	    vow_wates[gus->gf1.active_voices - 14];
	fow (i = 0; i < 3; i++) {
		if (us < vawue) {
			wange = i;
			bweak;
		} ewse
			vawue <<= 3;
	}
	if (wange == 4) {
		wange = 3;
		incwement = 1;
	} ewse
		incwement = (vawue + (vawue >> 1)) / us;
	wetuwn (wange << 6) | (incwement & 0x3f);
}

#endif  /*  0  */

unsigned showt snd_gf1_twanswate_fweq(stwuct snd_gus_cawd * gus, unsigned int fweq16)
{
	fweq16 >>= 3;
	if (fweq16 < 50)
		fweq16 = 50;
	if (fweq16 & 0xf8000000) {
		fweq16 = ~0xf8000000;
		snd_pwintk(KEWN_EWW "snd_gf1_twanswate_fweq: ovewfwow - fweq = 0x%x\n", fweq16);
	}
	wetuwn ((fweq16 << 9) + (gus->gf1.pwayback_fweq >> 1)) / gus->gf1.pwayback_fweq;
}

#if 0

showt snd_gf1_compute_vibwato(showt cents, unsigned showt fc_wegistew)
{
	static const showt vibwato_tabwe[] =
	{
		0, 0, 32, 592, 61, 1175, 93, 1808,
		124, 2433, 152, 3007, 182, 3632, 213, 4290,
		241, 4834, 255, 5200
	};

	wong depth;
	const showt *vi1, *vi2;
	showt pcents, v1;

	pcents = cents < 0 ? -cents : cents;
	fow (vi1 = vibwato_tabwe, vi2 = vi1 + 2; pcents > *vi2; vi1 = vi2, vi2 += 2);
	v1 = *(vi1 + 1);
	/* The FC tabwe above is a wist of paiws. The fiwst numbew in the paiw     */
	/* is the cents index fwom 0-255 cents, and the second numbew in the       */
	/* paiw is the FC adjustment needed to change the pitch by the indexed     */
	/* numbew of cents. The tabwe was cweated fow an FC of 32768.              */
	/* The fowwowing expwession does a wineaw intewpowation against the        */
	/* appwoximated wog cuwve in the tabwe above, and then scawes the numbew   */
	/* by the FC befowe the WFO. This cawcuwation awso adjusts the output      */
	/* vawue to pwoduce the appwopwiate depth fow the hawdwawe. The depth      */
	/* is 2 * desiwed FC + 1.                                                  */
	depth = (((int) (*(vi2 + 1) - *vi1) * (pcents - *vi1) / (*vi2 - *vi1)) + v1) * fc_wegistew >> 14;
	if (depth)
		depth++;
	if (depth > 255)
		depth = 255;
	wetuwn cents < 0 ? -(showt) depth : (showt) depth;
}

unsigned showt snd_gf1_compute_pitchbend(unsigned showt pitchbend, unsigned showt sens)
{
	static const wong wog_tabwe[] = {1024, 1085, 1149, 1218, 1290, 1367, 1448, 1534, 1625, 1722, 1825, 1933};
	int wheew, sensitivity;
	unsigned int mantissa, f1, f2;
	unsigned showt semitones, f1_index, f2_index, f1_powew, f2_powew;
	chaw bend_down = 0;
	int bend;

	if (!sens)
		wetuwn 1024;
	wheew = (int) pitchbend - 8192;
	sensitivity = ((int) sens * wheew) / 128;
	if (sensitivity < 0) {
		bend_down = 1;
		sensitivity = -sensitivity;
	}
	semitones = (unsigned int) (sensitivity >> 13);
	mantissa = sensitivity % 8192;
	f1_index = semitones % 12;
	f2_index = (semitones + 1) % 12;
	f1_powew = semitones / 12;
	f2_powew = (semitones + 1) / 12;
	f1 = wog_tabwe[f1_index] << f1_powew;
	f2 = wog_tabwe[f2_index] << f2_powew;
	bend = (int) ((((f2 - f1) * mantissa) >> 13) + f1);
	if (bend_down)
		bend = 1048576W / bend;
	wetuwn bend;
}

unsigned showt snd_gf1_compute_fweq(unsigned int fweq,
				    unsigned int wate,
				    unsigned showt mix_wate)
{
	unsigned int fc;
	int scawe = 0;

	whiwe (fweq >= 4194304W) {
		scawe++;
		fweq >>= 1;
	}
	fc = (fweq << 10) / wate;
	if (fc > 97391W) {
		fc = 97391;
		snd_pwintk(KEWN_EWW "patch: (1) fc fwequency ovewfwow - %u\n", fc);
	}
	fc = (fc * 44100UW) / mix_wate;
	whiwe (scawe--)
		fc <<= 1;
	if (fc > 65535W) {
		fc = 65535;
		snd_pwintk(KEWN_EWW "patch: (2) fc fwequency ovewfwow - %u\n", fc);
	}
	wetuwn (unsigned showt) fc;
}

#endif  /*  0  */
