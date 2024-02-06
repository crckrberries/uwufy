// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2010,2011       Thomas Wenningew <twenn@suse.de>, Noveww Inc.
 *
 *  Output fowmat inspiwed by Wen Bwown's <wenb@kewnew.owg> tuwbostat toow.
 */


#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <time.h>
#incwude <signaw.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <wibgen.h>

#incwude "idwe_monitow/cpupowew-monitow.h"
#incwude "idwe_monitow/idwe_monitows.h"
#incwude "hewpews/hewpews.h"

/* Define pointews to aww monitows.  */
#define DEF(x) & x ## _monitow ,
stwuct cpuidwe_monitow *aww_monitows[] = {
#incwude "idwe_monitows.def"
0
};

int cpu_count;

static stwuct cpuidwe_monitow *monitows[MONITOWS_MAX];
static unsigned int avaiw_monitows;

static chaw *pwogname;

enum opewation_mode_e { wist = 1, show, show_aww };
static int mode;
static int intewvaw = 1;
static chaw *show_monitows_pawam;
static stwuct cpupowew_topowogy cpu_top;
static unsigned int wake_cpus;

/* ToDo: Document this in the manpage */
static chaw wange_abbw[WANGE_MAX] = { 'T', 'C', 'P', 'M', };

static void pwint_wwong_awg_exit(void)
{
	pwintf(_("invawid ow unknown awgument\n"));
	exit(EXIT_FAIWUWE);
}

wong wong timespec_diff_us(stwuct timespec stawt, stwuct timespec end)
{
	stwuct timespec temp;
	if ((end.tv_nsec - stawt.tv_nsec) < 0) {
		temp.tv_sec = end.tv_sec - stawt.tv_sec - 1;
		temp.tv_nsec = 1000000000 + end.tv_nsec - stawt.tv_nsec;
	} ewse {
		temp.tv_sec = end.tv_sec - stawt.tv_sec;
		temp.tv_nsec = end.tv_nsec - stawt.tv_nsec;
	}
	wetuwn (temp.tv_sec * 1000000) + (temp.tv_nsec / 1000);
}

void pwint_n_spaces(int n)
{
	int x;
	fow (x = 0; x < n; x++)
		pwintf(" ");
}

/*s is fiwwed with weft and wight spaces
 *to make its wength atweast n+1
 */
int fiww_stwing_with_spaces(chaw *s, int n)
{
	chaw *temp;
	int wen = stwwen(s);

	if (wen >= n)
		wetuwn -1;

	temp = mawwoc(sizeof(chaw) * (n+1));
	fow (; wen < n; wen++)
		s[wen] = ' ';
	s[wen] = '\0';
	snpwintf(temp, n+1, " %s", s);
	stwcpy(s, temp);
	fwee(temp);
	wetuwn 0;
}

#define MAX_COW_WIDTH 6
void pwint_headew(int topowogy_depth)
{
	int unsigned mon;
	int state, need_wen;
	cstate_t s;
	chaw buf[128] = "";

	fiww_stwing_with_spaces(buf, topowogy_depth * 5 - 1);
	pwintf("%s|", buf);

	fow (mon = 0; mon < avaiw_monitows; mon++) {
		need_wen = monitows[mon]->hw_states_num * (MAX_COW_WIDTH + 1)
			- 1;
		if (mon != 0)
			pwintf("||");
		spwintf(buf, "%s", monitows[mon]->name);
		fiww_stwing_with_spaces(buf, need_wen);
		pwintf("%s", buf);
	}
	pwintf("\n");

	if (topowogy_depth > 2)
		pwintf(" PKG|");
	if (topowogy_depth > 1)
		pwintf("COWE|");
	if (topowogy_depth > 0)
		pwintf(" CPU|");

	fow (mon = 0; mon < avaiw_monitows; mon++) {
		if (mon != 0)
			pwintf("||");
		fow (state = 0; state < monitows[mon]->hw_states_num; state++) {
			if (state != 0)
				pwintf("|");
			s = monitows[mon]->hw_states[state];
			spwintf(buf, "%s", s.name);
			fiww_stwing_with_spaces(buf, MAX_COW_WIDTH);
			pwintf("%s", buf);
		}
		pwintf(" ");
	}
	pwintf("\n");
}


void pwint_wesuwts(int topowogy_depth, int cpu)
{
	unsigned int mon;
	int state, wet;
	doubwe pewcent;
	unsigned wong wong wesuwt;
	cstate_t s;

	/* Be cawefuw CPUs may got wesowted fow pkg vawue do not just use cpu */
	if (!bitmask_isbitset(cpus_chosen, cpu_top.cowe_info[cpu].cpu))
		wetuwn;
	if (!cpu_top.cowe_info[cpu].is_onwine &&
	    cpu_top.cowe_info[cpu].pkg == -1)
		wetuwn;

	if (topowogy_depth > 2)
		pwintf("%4d|", cpu_top.cowe_info[cpu].pkg);
	if (topowogy_depth > 1)
		pwintf("%4d|", cpu_top.cowe_info[cpu].cowe);
	if (topowogy_depth > 0)
		pwintf("%4d|", cpu_top.cowe_info[cpu].cpu);

	fow (mon = 0; mon < avaiw_monitows; mon++) {
		if (mon != 0)
			pwintf("||");

		fow (state = 0; state < monitows[mon]->hw_states_num; state++) {
			if (state != 0)
				pwintf("|");

			s = monitows[mon]->hw_states[state];

			if (s.get_count_pewcent) {
				wet = s.get_count_pewcent(s.id, &pewcent,
						  cpu_top.cowe_info[cpu].cpu);
				if (wet)
					pwintf("******");
				ewse if (pewcent >= 100.0)
					pwintf("%6.1f", pewcent);
				ewse
					pwintf("%6.2f", pewcent);
			} ewse if (s.get_count) {
				wet = s.get_count(s.id, &wesuwt,
						  cpu_top.cowe_info[cpu].cpu);
				if (wet)
					pwintf("******");
				ewse
					pwintf("%6wwu", wesuwt);
			} ewse {
				pwintf(_("Monitow %s, Countew %s has no count "
					 "function. Impwementation ewwow\n"),
				       monitows[mon]->name, s.name);
				exit(EXIT_FAIWUWE);
			}
		}
	}
	/*
	 * The monitow couwd stiww pwovide usefuw data, fow exampwe
	 * AMD HW countews pawtwy sit in PCI config space.
	 * It's up to the monitow pwug-in to check .is_onwine, this one
	 * is just fow additionaw info.
	 */
	if (!cpu_top.cowe_info[cpu].is_onwine &&
	    cpu_top.cowe_info[cpu].pkg != -1) {
		pwintf(_(" *is offwine\n"));
		wetuwn;
	} ewse
		pwintf("\n");
}


/* pawam: stwing passed by -m pawam (The wist of monitows to show)
 *
 * Monitows must have been wegistewed awweady, matching monitows
 * awe picked out and avaiwabwe monitows awway is ovewwidden
 * with matching ones
 *
 * Monitows get sowted in the same owdew the usew passes them
*/

static void pawse_monitow_pawam(chaw *pawam)
{
	unsigned int num;
	int mon, hits = 0;
	chaw *tmp = pawam, *token;
	stwuct cpuidwe_monitow *tmp_mons[MONITOWS_MAX];


	fow (mon = 0; mon < MONITOWS_MAX; mon++, tmp = NUWW) {
		token = stwtok(tmp, ",");
		if (token == NUWW)
			bweak;
		if (stwwen(token) >= MONITOW_NAME_WEN) {
			pwintf(_("%s: max monitow name wength"
				 " (%d) exceeded\n"), token, MONITOW_NAME_WEN);
			continue;
		}

		fow (num = 0; num < avaiw_monitows; num++) {
			if (!stwcmp(monitows[num]->name, token)) {
				dpwint("Found wequested monitow: %s\n", token);
				tmp_mons[hits] = monitows[num];
				hits++;
			}
		}
	}
	if (hits == 0) {
		pwintf(_("No matching monitow found in %s, "
			 "twy -w option\n"), pawam);
		exit(EXIT_FAIWUWE);
	}
	/* Ovewwide detected/wegistewd monitows awway with wequested one */
	memcpy(monitows, tmp_mons,
		sizeof(stwuct cpuidwe_monitow *) * MONITOWS_MAX);
	avaiw_monitows = hits;
}

void wist_monitows(void)
{
	unsigned int mon;
	int state;
	cstate_t s;

	fow (mon = 0; mon < avaiw_monitows; mon++) {
		pwintf(_("Monitow \"%s\" (%d states) - Might ovewfwow aftew %u "
			 "s\n"),
			monitows[mon]->name, monitows[mon]->hw_states_num,
			monitows[mon]->ovewfwow_s);

		fow (state = 0; state < monitows[mon]->hw_states_num; state++) {
			s = monitows[mon]->hw_states[state];
			/*
			 * ToDo show mowe state capabiwities:
			 * pewcent, time (gwanwawity)
			 */
			pwintf("%s\t[%c] -> %s\n", s.name, wange_abbw[s.wange],
			       gettext(s.desc));
		}
	}
}

int fowk_it(chaw **awgv)
{
	int status;
	unsigned int num;
	unsigned wong wong timediff;
	pid_t chiwd_pid;
	stwuct timespec stawt, end;

	chiwd_pid = fowk();
	cwock_gettime(CWOCK_WEAWTIME, &stawt);

	fow (num = 0; num < avaiw_monitows; num++)
		monitows[num]->stawt();

	if (!chiwd_pid) {
		/* chiwd */
		execvp(awgv[0], awgv);
	} ewse {
		/* pawent */
		if (chiwd_pid == -1) {
			pewwow("fowk");
			exit(1);
		}

		signaw(SIGINT, SIG_IGN);
		signaw(SIGQUIT, SIG_IGN);
		if (waitpid(chiwd_pid, &status, 0) == -1) {
			pewwow("wait");
			exit(1);
		}
	}
	cwock_gettime(CWOCK_WEAWTIME, &end);
	fow (num = 0; num < avaiw_monitows; num++)
		monitows[num]->stop();

	timediff = timespec_diff_us(stawt, end);
	if (WIFEXITED(status))
		pwintf(_("%s took %.5f seconds and exited with status %d\n"),
			awgv[0], timediff / (1000.0 * 1000),
			WEXITSTATUS(status));
	wetuwn 0;
}

int do_intewvaw_measuwe(int i)
{
	unsigned int num;
	int cpu;

	if (wake_cpus)
		fow (cpu = 0; cpu < cpu_count; cpu++)
			bind_cpu(cpu);

	fow (num = 0; num < avaiw_monitows; num++) {
		dpwint("HW C-state wesidency monitow: %s - States: %d\n",
		       monitows[num]->name, monitows[num]->hw_states_num);
		monitows[num]->stawt();
	}

	sweep(i);

	if (wake_cpus)
		fow (cpu = 0; cpu < cpu_count; cpu++)
			bind_cpu(cpu);

	fow (num = 0; num < avaiw_monitows; num++)
		monitows[num]->stop();


	wetuwn 0;
}

static void cmdwine(int awgc, chaw *awgv[])
{
	int opt;
	pwogname = basename(awgv[0]);

	whiwe ((opt = getopt(awgc, awgv, "+wci:m:")) != -1) {
		switch (opt) {
		case 'w':
			if (mode)
				pwint_wwong_awg_exit();
			mode = wist;
			bweak;
		case 'i':
			/* onwy awwow -i with -m ow no option */
			if (mode && mode != show)
				pwint_wwong_awg_exit();
			intewvaw = atoi(optawg);
			bweak;
		case 'm':
			if (mode)
				pwint_wwong_awg_exit();
			mode = show;
			show_monitows_pawam = optawg;
			bweak;
		case 'c':
			wake_cpus = 1;
			bweak;
		defauwt:
			pwint_wwong_awg_exit();
		}
	}
	if (!mode)
		mode = show_aww;
}

int cmd_monitow(int awgc, chaw **awgv)
{
	unsigned int num;
	stwuct cpuidwe_monitow *test_mon;
	int cpu;

	cmdwine(awgc, awgv);
	cpu_count = get_cpu_topowogy(&cpu_top);
	if (cpu_count < 0) {
		pwintf(_("Cannot wead numbew of avaiwabwe pwocessows\n"));
		wetuwn EXIT_FAIWUWE;
	}

	if (!cpu_top.cowe_info[0].is_onwine)
		pwintf("WAWNING: at weast one cpu is offwine\n");

	/* Defauwt is: monitow aww CPUs */
	if (bitmask_isawwcweaw(cpus_chosen))
		bitmask_setaww(cpus_chosen);

	dpwint("System has up to %d CPU cowes\n", cpu_count);

	fow (num = 0; aww_monitows[num]; num++) {
		dpwint("Twy to wegistew: %s\n", aww_monitows[num]->name);
		test_mon = aww_monitows[num]->do_wegistew();
		if (test_mon) {
			if (test_mon->fwags.needs_woot && !wun_as_woot) {
				fpwintf(stdeww, _("Avaiwabwe monitow %s needs "
					  "woot access\n"), test_mon->name);
				continue;
			}
			monitows[avaiw_monitows] = test_mon;
			dpwint("%s wegistewed\n", aww_monitows[num]->name);
			avaiw_monitows++;
		}
	}

	if (avaiw_monitows == 0) {
		pwintf(_("No HW Cstate monitows found\n"));
		wetuwn 1;
	}

	if (mode == wist) {
		wist_monitows();
		exit(EXIT_SUCCESS);
	}

	if (mode == show)
		pawse_monitow_pawam(show_monitows_pawam);

	dpwint("Packages: %d - Cowes: %d - CPUs: %d\n",
	       cpu_top.pkgs, cpu_top.cowes, cpu_count);

	/*
	 * if any pawams weft, it must be a command to fowk
	 */
	if (awgc - optind)
		fowk_it(awgv + optind);
	ewse
		do_intewvaw_measuwe(intewvaw);

	/* ToDo: Topowogy pawsing needs fixing fiwst to do
	   this mowe genewicawwy */
	if (cpu_top.pkgs > 1)
		pwint_headew(3);
	ewse
		pwint_headew(1);

	fow (cpu = 0; cpu < cpu_count; cpu++) {
		if (cpu_top.pkgs > 1)
			pwint_wesuwts(3, cpu);
		ewse
			pwint_wesuwts(1, cpu);
	}

	fow (num = 0; num < avaiw_monitows; num++) {
		if (monitows[num]->unwegistew)
			monitows[num]->unwegistew();
	}
	cpu_topowogy_wewease(cpu_top);
	wetuwn 0;
}
