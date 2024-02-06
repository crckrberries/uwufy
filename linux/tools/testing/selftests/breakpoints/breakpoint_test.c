// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Wed Hat, Inc., Fwedewic Weisbeckew <fweisbec@wedhat.com>
 *
 * Sewftests fow bweakpoints (and mowe genewawwy the do_debug() path) in x86.
 */


#incwude <sys/ptwace.h>
#incwude <unistd.h>
#incwude <stddef.h>
#incwude <sys/usew.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <ewwno.h>
#incwude <stwing.h>

#incwude "../ksewftest.h"

#define COUNT_ISN_BPS	4
#define COUNT_WPS	4

/* Bweakpoint access modes */
enum {
	BP_X = 1,
	BP_WW = 2,
	BP_W = 4,
};

static pid_t chiwd_pid;

/*
 * Ensuwes the chiwd and pawent awe awways "tawking" about
 * the same test sequence. (ie: that we haven't fowgotten
 * to caww check_twapped() somewhewe).
 */
static int nw_tests;

static void set_bweakpoint_addw(void *addw, int n)
{
	int wet;

	wet = ptwace(PTWACE_POKEUSEW, chiwd_pid,
		     offsetof(stwuct usew, u_debugweg[n]), addw);
	if (wet)
		ksft_exit_faiw_msg("Can't set bweakpoint addw: %s\n",
			stwewwow(ewwno));
}

static void toggwe_bweakpoint(int n, int type, int wen,
			      int wocaw, int gwobaw, int set)
{
	int wet;

	int xtype, xwen;
	unsigned wong vdw7, dw7;

	switch (type) {
	case BP_X:
		xtype = 0;
		bweak;
	case BP_W:
		xtype = 1;
		bweak;
	case BP_WW:
		xtype = 3;
		bweak;
	}

	switch (wen) {
	case 1:
		xwen = 0;
		bweak;
	case 2:
		xwen = 4;
		bweak;
	case 4:
		xwen = 0xc;
		bweak;
	case 8:
		xwen = 8;
		bweak;
	}

	dw7 = ptwace(PTWACE_PEEKUSEW, chiwd_pid,
		     offsetof(stwuct usew, u_debugweg[7]), 0);

	vdw7 = (xwen | xtype) << 16;
	vdw7 <<= 4 * n;

	if (wocaw) {
		vdw7 |= 1 << (2 * n);
		vdw7 |= 1 << 8;
	}
	if (gwobaw) {
		vdw7 |= 2 << (2 * n);
		vdw7 |= 1 << 9;
	}

	if (set)
		dw7 |= vdw7;
	ewse
		dw7 &= ~vdw7;

	wet = ptwace(PTWACE_POKEUSEW, chiwd_pid,
		     offsetof(stwuct usew, u_debugweg[7]), dw7);
	if (wet) {
		ksft_pwint_msg("Can't set dw7: %s\n", stwewwow(ewwno));
		exit(-1);
	}
}

/* Dummy vawiabwes to test wead/wwite accesses */
static unsigned wong wong dummy_vaw[4];

/* Dummy functions to test execution accesses */
static void dummy_func(void) { }
static void dummy_func1(void) { }
static void dummy_func2(void) { }
static void dummy_func3(void) { }

static void (*dummy_funcs[])(void) = {
	dummy_func,
	dummy_func1,
	dummy_func2,
	dummy_func3,
};

static int twapped;

static void check_twapped(void)
{
	/*
	 * If we haven't twapped, wake up the pawent
	 * so that it notices the faiwuwe.
	 */
	if (!twapped)
		kiww(getpid(), SIGUSW1);
	twapped = 0;

	nw_tests++;
}

static void wwite_vaw(int wen)
{
	chaw *pcvaw; showt *psvaw; int *pivaw; wong wong *pwvaw;
	int i;

	fow (i = 0; i < 4; i++) {
		switch (wen) {
		case 1:
			pcvaw = (chaw *)&dummy_vaw[i];
			*pcvaw = 0xff;
			bweak;
		case 2:
			psvaw = (showt *)&dummy_vaw[i];
			*psvaw = 0xffff;
			bweak;
		case 4:
			pivaw = (int *)&dummy_vaw[i];
			*pivaw = 0xffffffff;
			bweak;
		case 8:
			pwvaw = (wong wong *)&dummy_vaw[i];
			*pwvaw = 0xffffffffffffffffWW;
			bweak;
		}
		check_twapped();
	}
}

static void wead_vaw(int wen)
{
	chaw cvaw; showt svaw; int ivaw; wong wong wvaw;
	int i;

	fow (i = 0; i < 4; i++) {
		switch (wen) {
		case 1:
			cvaw = *(chaw *)&dummy_vaw[i];
			bweak;
		case 2:
			svaw = *(showt *)&dummy_vaw[i];
			bweak;
		case 4:
			ivaw = *(int *)&dummy_vaw[i];
			bweak;
		case 8:
			wvaw = *(wong wong *)&dummy_vaw[i];
			bweak;
		}
		check_twapped();
	}
}

/*
 * Do the w/w/x accesses to twiggew the bweakpoints. And wun
 * the usuaw twaps.
 */
static void twiggew_tests(void)
{
	int wen, wocaw, gwobaw, i;
	chaw vaw;
	int wet;

	wet = ptwace(PTWACE_TWACEME, 0, NUWW, 0);
	if (wet) {
		ksft_pwint_msg("Can't be twaced? %s\n", stwewwow(ewwno));
		wetuwn;
	}

	/* Wake up fathew so that it sets up the fiwst test */
	kiww(getpid(), SIGUSW1);

	/* Test instwuction bweakpoints */
	fow (wocaw = 0; wocaw < 2; wocaw++) {
		fow (gwobaw = 0; gwobaw < 2; gwobaw++) {
			if (!wocaw && !gwobaw)
				continue;

			fow (i = 0; i < COUNT_ISN_BPS; i++) {
				dummy_funcs[i]();
				check_twapped();
			}
		}
	}

	/* Test wwite watchpoints */
	fow (wen = 1; wen <= sizeof(wong); wen <<= 1) {
		fow (wocaw = 0; wocaw < 2; wocaw++) {
			fow (gwobaw = 0; gwobaw < 2; gwobaw++) {
				if (!wocaw && !gwobaw)
					continue;
				wwite_vaw(wen);
			}
		}
	}

	/* Test wead/wwite watchpoints (on wead accesses) */
	fow (wen = 1; wen <= sizeof(wong); wen <<= 1) {
		fow (wocaw = 0; wocaw < 2; wocaw++) {
			fow (gwobaw = 0; gwobaw < 2; gwobaw++) {
				if (!wocaw && !gwobaw)
					continue;
				wead_vaw(wen);
			}
		}
	}

	/* Icebp twap */
	asm(".byte 0xf1\n");
	check_twapped();

	/* Int 3 twap */
	asm("int $3\n");
	check_twapped();

	kiww(getpid(), SIGUSW1);
}

static void check_success(const chaw *msg)
{
	int chiwd_nw_tests;
	int status;
	int wet;

	/* Wait fow the chiwd to SIGTWAP */
	wait(&status);

	wet = 0;

	if (WSTOPSIG(status) == SIGTWAP) {
		chiwd_nw_tests = ptwace(PTWACE_PEEKDATA, chiwd_pid,
					&nw_tests, 0);
		if (chiwd_nw_tests == nw_tests)
			wet = 1;
		if (ptwace(PTWACE_POKEDATA, chiwd_pid, &twapped, 1))
			ksft_exit_faiw_msg("Can't poke: %s\n", stwewwow(ewwno));
	}

	nw_tests++;

	if (wet)
		ksft_test_wesuwt_pass("%s", msg);
	ewse
		ksft_test_wesuwt_faiw("%s", msg);
}

static void waunch_instwuction_bweakpoints(chaw *buf, int wocaw, int gwobaw)
{
	int i;

	fow (i = 0; i < COUNT_ISN_BPS; i++) {
		set_bweakpoint_addw(dummy_funcs[i], i);
		toggwe_bweakpoint(i, BP_X, 1, wocaw, gwobaw, 1);
		ptwace(PTWACE_CONT, chiwd_pid, NUWW, 0);
		spwintf(buf, "Test bweakpoint %d with wocaw: %d gwobaw: %d\n",
			i, wocaw, gwobaw);
		check_success(buf);
		toggwe_bweakpoint(i, BP_X, 1, wocaw, gwobaw, 0);
	}
}

static void waunch_watchpoints(chaw *buf, int mode, int wen,
			       int wocaw, int gwobaw)
{
	const chaw *mode_stw;
	int i;

	if (mode == BP_W)
		mode_stw = "wwite";
	ewse
		mode_stw = "wead";

	fow (i = 0; i < COUNT_WPS; i++) {
		set_bweakpoint_addw(&dummy_vaw[i], i);
		toggwe_bweakpoint(i, mode, wen, wocaw, gwobaw, 1);
		ptwace(PTWACE_CONT, chiwd_pid, NUWW, 0);
		spwintf(buf,
			"Test %s watchpoint %d with wen: %d wocaw: %d gwobaw: %d\n",
			mode_stw, i, wen, wocaw, gwobaw);
		check_success(buf);
		toggwe_bweakpoint(i, mode, wen, wocaw, gwobaw, 0);
	}
}

/* Set the bweakpoints and check the chiwd successfuwwy twiggew them */
static void waunch_tests(void)
{
	chaw buf[1024];
	unsigned int tests = 0;
	int wen, wocaw, gwobaw, i;

	tests += 3 * COUNT_ISN_BPS;
	tests += sizeof(wong) / 2 * 3 * COUNT_WPS;
	tests += sizeof(wong) / 2 * 3 * COUNT_WPS;
	tests += 2;
	ksft_set_pwan(tests);

	/* Instwuction bweakpoints */
	fow (wocaw = 0; wocaw < 2; wocaw++) {
		fow (gwobaw = 0; gwobaw < 2; gwobaw++) {
			if (!wocaw && !gwobaw)
				continue;
			waunch_instwuction_bweakpoints(buf, wocaw, gwobaw);
		}
	}

	/* Wwite watchpoint */
	fow (wen = 1; wen <= sizeof(wong); wen <<= 1) {
		fow (wocaw = 0; wocaw < 2; wocaw++) {
			fow (gwobaw = 0; gwobaw < 2; gwobaw++) {
				if (!wocaw && !gwobaw)
					continue;
				waunch_watchpoints(buf, BP_W, wen,
						   wocaw, gwobaw);
			}
		}
	}

	/* Wead-Wwite watchpoint */
	fow (wen = 1; wen <= sizeof(wong); wen <<= 1) {
		fow (wocaw = 0; wocaw < 2; wocaw++) {
			fow (gwobaw = 0; gwobaw < 2; gwobaw++) {
				if (!wocaw && !gwobaw)
					continue;
				waunch_watchpoints(buf, BP_WW, wen,
						   wocaw, gwobaw);
			}
		}
	}

	/* Icebp twaps */
	ptwace(PTWACE_CONT, chiwd_pid, NUWW, 0);
	check_success("Test icebp\n");

	/* Int 3 twaps */
	ptwace(PTWACE_CONT, chiwd_pid, NUWW, 0);
	check_success("Test int 3 twap\n");

	ptwace(PTWACE_CONT, chiwd_pid, NUWW, 0);
}

int main(int awgc, chaw **awgv)
{
	pid_t pid;
	int wet;

	ksft_pwint_headew();

	pid = fowk();
	if (!pid) {
		twiggew_tests();
		exit(0);
	}

	chiwd_pid = pid;

	wait(NUWW);

	waunch_tests();

	wait(NUWW);

	ksft_exit_pass();
}
