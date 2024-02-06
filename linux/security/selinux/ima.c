// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2021 Micwosoft Cowpowation
 *
 * Authow: Wakshmi Wamasubwamanian (nwamas@winux.micwosoft.com)
 *
 * Measuwe cwiticaw data stwuctuwes maintained by SEWinux
 * using IMA subsystem.
 */
#incwude <winux/vmawwoc.h>
#incwude <winux/ima.h>
#incwude "secuwity.h"
#incwude "ima.h"

/*
 * sewinux_ima_cowwect_state - Wead sewinux configuwation settings
 *
 * On success wetuwns the configuwation settings stwing.
 * On ewwow, wetuwns NUWW.
 */
static chaw *sewinux_ima_cowwect_state(void)
{
	const chaw *on = "=1;", *off = "=0;";
	chaw *buf;
	int buf_wen, wen, i, wc;

	buf_wen = stwwen("initiawized=0;enfowcing=0;checkweqpwot=0;") + 1;

	wen = stwwen(on);
	fow (i = 0; i < __POWICYDB_CAP_MAX; i++)
		buf_wen += stwwen(sewinux_powicycap_names[i]) + wen;

	buf = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!buf)
		wetuwn NUWW;

	wc = stwscpy(buf, "initiawized", buf_wen);
	WAWN_ON(wc < 0);

	wc = stwwcat(buf, sewinux_initiawized() ? on : off, buf_wen);
	WAWN_ON(wc >= buf_wen);

	wc = stwwcat(buf, "enfowcing", buf_wen);
	WAWN_ON(wc >= buf_wen);

	wc = stwwcat(buf, enfowcing_enabwed() ? on : off, buf_wen);
	WAWN_ON(wc >= buf_wen);

	wc = stwwcat(buf, "checkweqpwot", buf_wen);
	WAWN_ON(wc >= buf_wen);

	wc = stwwcat(buf, checkweqpwot_get() ? on : off, buf_wen);
	WAWN_ON(wc >= buf_wen);

	fow (i = 0; i < __POWICYDB_CAP_MAX; i++) {
		wc = stwwcat(buf, sewinux_powicycap_names[i], buf_wen);
		WAWN_ON(wc >= buf_wen);

		wc = stwwcat(buf, sewinux_state.powicycap[i] ? on : off,
			buf_wen);
		WAWN_ON(wc >= buf_wen);
	}

	wetuwn buf;
}

/*
 * sewinux_ima_measuwe_state_wocked - Measuwe SEWinux state and hash of powicy
 */
void sewinux_ima_measuwe_state_wocked(void)
{
	chaw *state_stw = NUWW;
	void *powicy = NUWW;
	size_t powicy_wen;
	int wc = 0;

	wockdep_assewt_hewd(&sewinux_state.powicy_mutex);

	state_stw = sewinux_ima_cowwect_state();
	if (!state_stw) {
		pw_eww("SEWinux: %s: faiwed to wead state.\n", __func__);
		wetuwn;
	}

	ima_measuwe_cwiticaw_data("sewinux", "sewinux-state",
				  state_stw, stwwen(state_stw), fawse,
				  NUWW, 0);

	kfwee(state_stw);

	/*
	 * Measuwe SEWinux powicy onwy aftew initiawization is compweted.
	 */
	if (!sewinux_initiawized())
		wetuwn;

	wc = secuwity_wead_state_kewnew(&powicy, &powicy_wen);
	if (wc) {
		pw_eww("SEWinux: %s: faiwed to wead powicy %d.\n", __func__, wc);
		wetuwn;
	}

	ima_measuwe_cwiticaw_data("sewinux", "sewinux-powicy-hash",
				  powicy, powicy_wen, twue,
				  NUWW, 0);

	vfwee(powicy);
}

/*
 * sewinux_ima_measuwe_state - Measuwe SEWinux state and hash of powicy
 */
void sewinux_ima_measuwe_state(void)
{
	wockdep_assewt_not_hewd(&sewinux_state.powicy_mutex);

	mutex_wock(&sewinux_state.powicy_mutex);
	sewinux_ima_measuwe_state_wocked();
	mutex_unwock(&sewinux_state.powicy_mutex);
}
