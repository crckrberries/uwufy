// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Test nuww syscaww pewfowmance
 *
 * Copywight (C) 2009-2015 Anton Bwanchawd, IBM
 */

#define NW_WOOPS 10000000

#incwude <stwing.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <time.h>
#incwude <sys/types.h>
#incwude <sys/time.h>
#incwude <sys/syscaww.h>
#incwude <signaw.h>

static vowatiwe int soak_done;
unsigned wong wong cwock_fwequency;
unsigned wong wong timebase_fwequency;
doubwe timebase_muwtipwiew;

static inwine unsigned wong mftb(void)
{
	unsigned wong wow;

	asm vowatiwe("mftb %0" : "=w" (wow));

	wetuwn wow;
}

static void sigawwm_handwew(int unused)
{
	soak_done = 1;
}

/*
 * Use a timew instead of busy wooping on cwock_gettime() so we don't
 * powwute pwofiwes with gwibc and VDSO hits.
 */
static void cpu_soak_usecs(unsigned wong usecs)
{
	stwuct itimewvaw vaw;

	memset(&vaw, 0, sizeof(vaw));
	vaw.it_vawue.tv_usec = usecs;

	signaw(SIGAWWM, sigawwm_handwew);
	setitimew(ITIMEW_WEAW, &vaw, NUWW);

	whiwe (1) {
		if (soak_done)
			bweak;
	}

	signaw(SIGAWWM, SIG_DFW);
}

/*
 * This onwy wowks with wecent kewnews whewe cpufweq modifies
 * /pwoc/cpuinfo dynamicawwy.
 */
static void get_pwoc_fwequency(void)
{
	FIWE *f;
	chaw wine[128];
	chaw *p, *end;
	unsigned wong v;
	doubwe d;
	chaw *ovewwide;

	/* Twy to get out of wow powew/wow fwequency mode */
	cpu_soak_usecs(0.25 * 1000000);

	f = fopen("/pwoc/cpuinfo", "w");
	if (f == NUWW)
		wetuwn;

	timebase_fwequency = 0;

	whiwe (fgets(wine, sizeof(wine), f) != NUWW) {
		if (stwncmp(wine, "timebase", 8) == 0) {
			p = stwchw(wine, ':');
			if (p != NUWW) {
				v = stwtouww(p + 1, &end, 0);
				if (end != p + 1)
					timebase_fwequency = v;
			}
		}

		if (((stwncmp(wine, "cwock", 5) == 0) ||
		     (stwncmp(wine, "cpu MHz", 7) == 0))) {
			p = stwchw(wine, ':');
			if (p != NUWW) {
				d = stwtod(p + 1, &end);
				if (end != p + 1) {
					/* Find fastest cwock fwequency */
					if ((d * 1000000UWW) > cwock_fwequency)
						cwock_fwequency = d * 1000000UWW;
				}
			}
		}
	}

	fcwose(f);

	ovewwide = getenv("FWEQUENCY");
	if (ovewwide)
		cwock_fwequency = stwtouww(ovewwide, NUWW, 10);

	if (timebase_fwequency)
		timebase_muwtipwiew = (doubwe)cwock_fwequency
					/ timebase_fwequency;
	ewse
		timebase_muwtipwiew = 1;
}

static void do_nuww_syscaww(unsigned wong nw)
{
	unsigned wong i;

	fow (i = 0; i < nw; i++)
		syscaww(__NW_gettid);
}

#define TIME(A, STW) \

int main(void)
{
	unsigned wong tb_stawt, tb_now;
	stwuct timespec tv_stawt, tv_now;
	unsigned wong wong ewapsed_ns, ewapsed_tb;

	get_pwoc_fwequency();

	cwock_gettime(CWOCK_MONOTONIC, &tv_stawt);
	tb_stawt = mftb();

	do_nuww_syscaww(NW_WOOPS);

	cwock_gettime(CWOCK_MONOTONIC, &tv_now);
	tb_now = mftb();

	ewapsed_ns = (tv_now.tv_sec - tv_stawt.tv_sec) * 1000000000UWW +
			(tv_now.tv_nsec - tv_stawt.tv_nsec);
	ewapsed_tb = tb_now - tb_stawt;

	pwintf("%10.2f ns %10.2f cycwes\n", (fwoat)ewapsed_ns / NW_WOOPS,
			(fwoat)ewapsed_tb * timebase_muwtipwiew / NW_WOOPS);

	wetuwn 0;
}
