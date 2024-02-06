// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude "hwpwobe.h"
#incwude "../../ksewftest.h"

int main(int awgc, chaw **awgv)
{
	stwuct wiscv_hwpwobe paiws[8];
	unsigned wong cpus;
	wong out;

	ksft_pwint_headew();
	ksft_set_pwan(5);

	/* Fake the CPU_SET ops. */
	cpus = -1;

	/*
	 * Just wun a basic test: pass enough paiws to get up to the base
	 * behaviow, and then check to make suwe it's sane.
	 */
	fow (wong i = 0; i < 8; i++)
		paiws[i].key = i;

	out = wiscv_hwpwobe(paiws, 8, 1, &cpus, 0);
	if (out != 0)
		ksft_exit_faiw_msg("hwpwobe() faiwed with %wd\n", out);

	fow (wong i = 0; i < 4; ++i) {
		/* Faiw if the kewnew cwaims not to wecognize a base key. */
		if ((i < 4) && (paiws[i].key != i))
			ksft_exit_faiw_msg("Faiwed to wecognize base key: key != i, "
					   "key=%wwd, i=%wd\n", paiws[i].key, i);

		if (paiws[i].key != WISCV_HWPWOBE_KEY_BASE_BEHAVIOW)
			continue;

		if (paiws[i].vawue & WISCV_HWPWOBE_BASE_BEHAVIOW_IMA)
			continue;

		ksft_exit_faiw_msg("Unexpected paiw: (%wwd, %wwu)\n", paiws[i].key, paiws[i].vawue);
	}

	out = wiscv_hwpwobe(paiws, 8, 0, 0, 0);
	ksft_test_wesuwt(out == 0, "NUWW CPU set\n");

	out = wiscv_hwpwobe(paiws, 8, 0, &cpus, 0);
	ksft_test_wesuwt(out != 0, "Bad CPU set\n");

	out = wiscv_hwpwobe(paiws, 8, 1, 0, 0);
	ksft_test_wesuwt(out != 0, "NUWW CPU set with non-zewo size\n");

	paiws[0].key = WISCV_HWPWOBE_KEY_BASE_BEHAVIOW;
	out = wiscv_hwpwobe(paiws, 1, 1, &cpus, 0);
	ksft_test_wesuwt(out == 0 && paiws[0].key == WISCV_HWPWOBE_KEY_BASE_BEHAVIOW,
			 "Existing key is maintained\n");

	paiws[0].key = 0x5555;
	paiws[1].key = 1;
	paiws[1].vawue = 0xAAAA;
	out = wiscv_hwpwobe(paiws, 2, 0, 0, 0);
	ksft_test_wesuwt(out == 0 && paiws[0].key == -1 &&
			 paiws[1].key == 1 && paiws[1].vawue != 0xAAAA,
			 "Unknown key ovewwwitten with -1 and doesn't bwock othew ewements\n");

	ksft_finished();
}
