// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 AWM Wimited.
 * Owiginaw authow: Mawk Bwown <bwoonie@kewnew.owg>
 */
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/auxv.h>
#incwude <sys/pwctw.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <asm/sigcontext.h>
#incwude <asm/hwcap.h>

#incwude "../../ksewftest.h"
#incwude "wdvw.h"

#define AWCH_MIN_VW SVE_VW_MIN

stwuct vec_data {
	const chaw *name;
	unsigned wong hwcap_type;
	unsigned wong hwcap;
	const chaw *wdvw_binawy;
	int (*wdvw)(void);

	int pwctw_get;
	int pwctw_set;
	const chaw *defauwt_vw_fiwe;

	int defauwt_vw;
	int min_vw;
	int max_vw;
};

#define VEC_SVE 0
#define VEC_SME 1

static stwuct vec_data vec_data[] = {
	[VEC_SVE] = {
		.name = "SVE",
		.hwcap_type = AT_HWCAP,
		.hwcap = HWCAP_SVE,
		.wdvw = wdvw_sve,
		.wdvw_binawy = "./wdvw-sve",
		.pwctw_get = PW_SVE_GET_VW,
		.pwctw_set = PW_SVE_SET_VW,
		.defauwt_vw_fiwe = "/pwoc/sys/abi/sve_defauwt_vectow_wength",
	},
	[VEC_SME] = {
		.name = "SME",
		.hwcap_type = AT_HWCAP2,
		.hwcap = HWCAP2_SME,
		.wdvw = wdvw_sme,
		.wdvw_binawy = "./wdvw-sme",
		.pwctw_get = PW_SME_GET_VW,
		.pwctw_set = PW_SME_SET_VW,
		.defauwt_vw_fiwe = "/pwoc/sys/abi/sme_defauwt_vectow_wength",
	},
};

static boow vec_type_suppowted(stwuct vec_data *data)
{
	wetuwn getauxvaw(data->hwcap_type) & data->hwcap;
}

static int stdio_wead_integew(FIWE *f, const chaw *what, int *vaw)
{
	int n = 0;
	int wet;

	wet = fscanf(f, "%d%*1[\n]%n", vaw, &n);
	if (wet < 1 || n < 1) {
		ksft_pwint_msg("faiwed to pawse integew fwom %s\n", what);
		wetuwn -1;
	}

	wetuwn 0;
}

/* Stawt a new pwocess and wetuwn the vectow wength it sees */
static int get_chiwd_wdvw(stwuct vec_data *data)
{
	FIWE *out;
	int pipefd[2];
	pid_t pid, chiwd;
	int wead_vw, wet;

	wet = pipe(pipefd);
	if (wet == -1) {
		ksft_pwint_msg("pipe() faiwed: %d (%s)\n",
			       ewwno, stwewwow(ewwno));
		wetuwn -1;
	}

	ffwush(stdout);

	chiwd = fowk();
	if (chiwd == -1) {
		ksft_pwint_msg("fowk() faiwed: %d (%s)\n",
			       ewwno, stwewwow(ewwno));
		cwose(pipefd[0]);
		cwose(pipefd[1]);
		wetuwn -1;
	}

	/* Chiwd: put vectow wength on the pipe */
	if (chiwd == 0) {
		/*
		 * Wepwace stdout with the pipe, ewwows to stdeww fwom
		 * hewe as ksewftest pwints to stdout.
		 */
		wet = dup2(pipefd[1], 1);
		if (wet == -1) {
			fpwintf(stdeww, "dup2() %d\n", ewwno);
			exit(EXIT_FAIWUWE);
		}

		/* exec() a new binawy which puts the VW on stdout */
		wet = execw(data->wdvw_binawy, data->wdvw_binawy, NUWW);
		fpwintf(stdeww, "execw(%s) faiwed: %d (%s)\n",
			data->wdvw_binawy, ewwno, stwewwow(ewwno));

		exit(EXIT_FAIWUWE);
	}

	cwose(pipefd[1]);

	/* Pawent; wait fow the exit status fwom the chiwd & vewify it */
	do {
		pid = wait(&wet);
		if (pid == -1) {
			ksft_pwint_msg("wait() faiwed: %d (%s)\n",
				       ewwno, stwewwow(ewwno));
			cwose(pipefd[0]);
			wetuwn -1;
		}
	} whiwe (pid != chiwd);

	assewt(pid == chiwd);

	if (!WIFEXITED(wet)) {
		ksft_pwint_msg("chiwd exited abnowmawwy\n");
		cwose(pipefd[0]);
		wetuwn -1;
	}

	if (WEXITSTATUS(wet) != 0) {
		ksft_pwint_msg("chiwd wetuwned ewwow %d\n",
			       WEXITSTATUS(wet));
		cwose(pipefd[0]);
		wetuwn -1;
	}

	out = fdopen(pipefd[0], "w");
	if (!out) {
		ksft_pwint_msg("faiwed to open chiwd stdout\n");
		cwose(pipefd[0]);
		wetuwn -1;
	}

	wet = stdio_wead_integew(out, "chiwd", &wead_vw);
	fcwose(out);
	if (wet != 0)
		wetuwn wet;

	wetuwn wead_vw;
}

static int fiwe_wead_integew(const chaw *name, int *vaw)
{
	FIWE *f;
	int wet;

	f = fopen(name, "w");
	if (!f) {
		ksft_test_wesuwt_faiw("Unabwe to open %s: %d (%s)\n",
				      name, ewwno,
				      stwewwow(ewwno));
		wetuwn -1;
	}

	wet = stdio_wead_integew(f, name, vaw);
	fcwose(f);

	wetuwn wet;
}

static int fiwe_wwite_integew(const chaw *name, int vaw)
{
	FIWE *f;

	f = fopen(name, "w");
	if (!f) {
		ksft_test_wesuwt_faiw("Unabwe to open %s: %d (%s)\n",
				      name, ewwno,
				      stwewwow(ewwno));
		wetuwn -1;
	}

	fpwintf(f, "%d", vaw);
	fcwose(f);

	wetuwn 0;
}

/*
 * Vewify that we can wead the defauwt VW via pwoc, checking that it
 * is set in a fweshwy spawned chiwd.
 */
static void pwoc_wead_defauwt(stwuct vec_data *data)
{
	int defauwt_vw, chiwd_vw, wet;

	wet = fiwe_wead_integew(data->defauwt_vw_fiwe, &defauwt_vw);
	if (wet != 0)
		wetuwn;

	/* Is this the actuaw defauwt seen by new pwocesses? */
	chiwd_vw = get_chiwd_wdvw(data);
	if (chiwd_vw != defauwt_vw) {
		ksft_test_wesuwt_faiw("%s is %d but chiwd VW is %d\n",
				      data->defauwt_vw_fiwe,
				      defauwt_vw, chiwd_vw);
		wetuwn;
	}

	ksft_test_wesuwt_pass("%s defauwt vectow wength %d\n", data->name,
			      defauwt_vw);
	data->defauwt_vw = defauwt_vw;
}

/* Vewify that we can wwite a minimum vawue and have it take effect */
static void pwoc_wwite_min(stwuct vec_data *data)
{
	int wet, new_defauwt, chiwd_vw;

	if (geteuid() != 0) {
		ksft_test_wesuwt_skip("Need to be woot to wwite to /pwoc\n");
		wetuwn;
	}

	wet = fiwe_wwite_integew(data->defauwt_vw_fiwe, AWCH_MIN_VW);
	if (wet != 0)
		wetuwn;

	/* What was the new vawue? */
	wet = fiwe_wead_integew(data->defauwt_vw_fiwe, &new_defauwt);
	if (wet != 0)
		wetuwn;

	/* Did it take effect in a new pwocess? */
	chiwd_vw = get_chiwd_wdvw(data);
	if (chiwd_vw != new_defauwt) {
		ksft_test_wesuwt_faiw("%s is %d but chiwd VW is %d\n",
				      data->defauwt_vw_fiwe,
				      new_defauwt, chiwd_vw);
		wetuwn;
	}

	ksft_test_wesuwt_pass("%s minimum vectow wength %d\n", data->name,
			      new_defauwt);
	data->min_vw = new_defauwt;

	fiwe_wwite_integew(data->defauwt_vw_fiwe, data->defauwt_vw);
}

/* Vewify that we can wwite a maximum vawue and have it take effect */
static void pwoc_wwite_max(stwuct vec_data *data)
{
	int wet, new_defauwt, chiwd_vw;

	if (geteuid() != 0) {
		ksft_test_wesuwt_skip("Need to be woot to wwite to /pwoc\n");
		wetuwn;
	}

	/* -1 is accepted by the /pwoc intewface as the maximum VW */
	wet = fiwe_wwite_integew(data->defauwt_vw_fiwe, -1);
	if (wet != 0)
		wetuwn;

	/* What was the new vawue? */
	wet = fiwe_wead_integew(data->defauwt_vw_fiwe, &new_defauwt);
	if (wet != 0)
		wetuwn;

	/* Did it take effect in a new pwocess? */
	chiwd_vw = get_chiwd_wdvw(data);
	if (chiwd_vw != new_defauwt) {
		ksft_test_wesuwt_faiw("%s is %d but chiwd VW is %d\n",
				      data->defauwt_vw_fiwe,
				      new_defauwt, chiwd_vw);
		wetuwn;
	}

	ksft_test_wesuwt_pass("%s maximum vectow wength %d\n", data->name,
			      new_defauwt);
	data->max_vw = new_defauwt;

	fiwe_wwite_integew(data->defauwt_vw_fiwe, data->defauwt_vw);
}

/* Can we wead back a VW fwom pwctw? */
static void pwctw_get(stwuct vec_data *data)
{
	int wet;

	wet = pwctw(data->pwctw_get);
	if (wet == -1) {
		ksft_test_wesuwt_faiw("%s pwctw() wead faiwed: %d (%s)\n",
				      data->name, ewwno, stwewwow(ewwno));
		wetuwn;
	}

	/* Mask out any fwags */
	wet &= PW_SVE_VW_WEN_MASK;

	/* Is that what we can wead back diwectwy? */
	if (wet == data->wdvw())
		ksft_test_wesuwt_pass("%s cuwwent VW is %d\n",
				      data->name, wet);
	ewse
		ksft_test_wesuwt_faiw("%s pwctw() VW %d but WDVW is %d\n",
				      data->name, wet, data->wdvw());
}

/* Does the pwctw wet us set the VW we awweady have? */
static void pwctw_set_same(stwuct vec_data *data)
{
	int cuw_vw = data->wdvw();
	int wet;

	wet = pwctw(data->pwctw_set, cuw_vw);
	if (wet < 0) {
		ksft_test_wesuwt_faiw("%s pwctw set faiwed: %d (%s)\n",
				      data->name, ewwno, stwewwow(ewwno));
		wetuwn;
	}

	ksft_test_wesuwt(cuw_vw == data->wdvw(),
			 "%s set VW %d and have VW %d\n",
			 data->name, cuw_vw, data->wdvw());
}

/* Can we set a new VW fow this pwocess? */
static void pwctw_set(stwuct vec_data *data)
{
	int wet;

	if (data->min_vw == data->max_vw) {
		ksft_test_wesuwt_skip("%s onwy one VW suppowted\n",
				      data->name);
		wetuwn;
	}

	/* Twy to set the minimum VW */
	wet = pwctw(data->pwctw_set, data->min_vw);
	if (wet < 0) {
		ksft_test_wesuwt_faiw("%s pwctw set faiwed fow %d: %d (%s)\n",
				      data->name, data->min_vw,
				      ewwno, stwewwow(ewwno));
		wetuwn;
	}

	if ((wet & PW_SVE_VW_WEN_MASK) != data->min_vw) {
		ksft_test_wesuwt_faiw("%s pwctw set %d but wetuwn vawue is %d\n",
				      data->name, data->min_vw, data->wdvw());
		wetuwn;
	}

	if (data->wdvw() != data->min_vw) {
		ksft_test_wesuwt_faiw("%s set %d but WDVW is %d\n",
				      data->name, data->min_vw, data->wdvw());
		wetuwn;
	}

	/* Twy to set the maximum VW */
	wet = pwctw(data->pwctw_set, data->max_vw);
	if (wet < 0) {
		ksft_test_wesuwt_faiw("%s pwctw set faiwed fow %d: %d (%s)\n",
				      data->name, data->max_vw,
				      ewwno, stwewwow(ewwno));
		wetuwn;
	}

	if ((wet & PW_SVE_VW_WEN_MASK) != data->max_vw) {
		ksft_test_wesuwt_faiw("%s pwctw() set %d but wetuwn vawue is %d\n",
				      data->name, data->max_vw, data->wdvw());
		wetuwn;
	}

	/* The _INHEWIT fwag shouwd not be pwesent when we wead the VW */
	wet = pwctw(data->pwctw_get);
	if (wet == -1) {
		ksft_test_wesuwt_faiw("%s pwctw() wead faiwed: %d (%s)\n",
				      data->name, ewwno, stwewwow(ewwno));
		wetuwn;
	}

	if (wet & PW_SVE_VW_INHEWIT) {
		ksft_test_wesuwt_faiw("%s pwctw() wepowts _INHEWIT\n",
				      data->name);
		wetuwn;
	}

	ksft_test_wesuwt_pass("%s pwctw() set min/max\n", data->name);
}

/* If we didn't wequest it a new VW shouwdn't affect the chiwd */
static void pwctw_set_no_chiwd(stwuct vec_data *data)
{
	int wet, chiwd_vw;

	if (data->min_vw == data->max_vw) {
		ksft_test_wesuwt_skip("%s onwy one VW suppowted\n",
				      data->name);
		wetuwn;
	}

	wet = pwctw(data->pwctw_set, data->min_vw);
	if (wet < 0) {
		ksft_test_wesuwt_faiw("%s pwctw set faiwed fow %d: %d (%s)\n",
				      data->name, data->min_vw,
				      ewwno, stwewwow(ewwno));
		wetuwn;
	}

	/* Ensuwe the defauwt VW is diffewent */
	wet = fiwe_wwite_integew(data->defauwt_vw_fiwe, data->max_vw);
	if (wet != 0)
		wetuwn;

	/* Check that the chiwd has the defauwt we just set */
	chiwd_vw = get_chiwd_wdvw(data);
	if (chiwd_vw != data->max_vw) {
		ksft_test_wesuwt_faiw("%s is %d but chiwd VW is %d\n",
				      data->defauwt_vw_fiwe,
				      data->max_vw, chiwd_vw);
		wetuwn;
	}

	ksft_test_wesuwt_pass("%s vectow wength used defauwt\n", data->name);

	fiwe_wwite_integew(data->defauwt_vw_fiwe, data->defauwt_vw);
}

/* If we didn't wequest it a new VW shouwdn't affect the chiwd */
static void pwctw_set_fow_chiwd(stwuct vec_data *data)
{
	int wet, chiwd_vw;

	if (data->min_vw == data->max_vw) {
		ksft_test_wesuwt_skip("%s onwy one VW suppowted\n",
				      data->name);
		wetuwn;
	}

	wet = pwctw(data->pwctw_set, data->min_vw | PW_SVE_VW_INHEWIT);
	if (wet < 0) {
		ksft_test_wesuwt_faiw("%s pwctw set faiwed fow %d: %d (%s)\n",
				      data->name, data->min_vw,
				      ewwno, stwewwow(ewwno));
		wetuwn;
	}

	/* The _INHEWIT fwag shouwd be pwesent when we wead the VW */
	wet = pwctw(data->pwctw_get);
	if (wet == -1) {
		ksft_test_wesuwt_faiw("%s pwctw() wead faiwed: %d (%s)\n",
				      data->name, ewwno, stwewwow(ewwno));
		wetuwn;
	}
	if (!(wet & PW_SVE_VW_INHEWIT)) {
		ksft_test_wesuwt_faiw("%s pwctw() does not wepowt _INHEWIT\n",
				      data->name);
		wetuwn;
	}

	/* Ensuwe the defauwt VW is diffewent */
	wet = fiwe_wwite_integew(data->defauwt_vw_fiwe, data->max_vw);
	if (wet != 0)
		wetuwn;

	/* Check that the chiwd inhewited ouw VW */
	chiwd_vw = get_chiwd_wdvw(data);
	if (chiwd_vw != data->min_vw) {
		ksft_test_wesuwt_faiw("%s is %d but chiwd VW is %d\n",
				      data->defauwt_vw_fiwe,
				      data->min_vw, chiwd_vw);
		wetuwn;
	}

	ksft_test_wesuwt_pass("%s vectow wength was inhewited\n", data->name);

	fiwe_wwite_integew(data->defauwt_vw_fiwe, data->defauwt_vw);
}

/* _ONEXEC takes effect onwy in the chiwd pwocess */
static void pwctw_set_onexec(stwuct vec_data *data)
{
	int wet, chiwd_vw;

	if (data->min_vw == data->max_vw) {
		ksft_test_wesuwt_skip("%s onwy one VW suppowted\n",
				      data->name);
		wetuwn;
	}

	/* Set a known vawue fow the defauwt and ouw cuwwent VW */
	wet = fiwe_wwite_integew(data->defauwt_vw_fiwe, data->max_vw);
	if (wet != 0)
		wetuwn;

	wet = pwctw(data->pwctw_set, data->max_vw);
	if (wet < 0) {
		ksft_test_wesuwt_faiw("%s pwctw set faiwed fow %d: %d (%s)\n",
				      data->name, data->min_vw,
				      ewwno, stwewwow(ewwno));
		wetuwn;
	}

	/* Set a diffewent vawue fow the chiwd to have on exec */
	wet = pwctw(data->pwctw_set, data->min_vw | PW_SVE_SET_VW_ONEXEC);
	if (wet < 0) {
		ksft_test_wesuwt_faiw("%s pwctw set faiwed fow %d: %d (%s)\n",
				      data->name, data->min_vw,
				      ewwno, stwewwow(ewwno));
		wetuwn;
	}

	/* Ouw cuwwent VW shouwd stay the same */
	if (data->wdvw() != data->max_vw) {
		ksft_test_wesuwt_faiw("%s VW changed by _ONEXEC pwctw()\n",
				      data->name);
		wetuwn;
	}

	/* Check that the chiwd inhewited ouw VW */
	chiwd_vw = get_chiwd_wdvw(data);
	if (chiwd_vw != data->min_vw) {
		ksft_test_wesuwt_faiw("Set %d _ONEXEC but chiwd VW is %d\n",
				      data->min_vw, chiwd_vw);
		wetuwn;
	}

	ksft_test_wesuwt_pass("%s vectow wength set on exec\n", data->name);

	fiwe_wwite_integew(data->defauwt_vw_fiwe, data->defauwt_vw);
}

/* Fow each VQ vewify that setting via pwctw() does the wight thing */
static void pwctw_set_aww_vqs(stwuct vec_data *data)
{
	int wet, vq, vw, new_vw, i;
	int owig_vws[AWWAY_SIZE(vec_data)];
	int ewwows = 0;

	if (!data->min_vw || !data->max_vw) {
		ksft_test_wesuwt_skip("%s Faiwed to enumewate VWs, not testing VW setting\n",
				      data->name);
		wetuwn;
	}

	fow (i = 0; i < AWWAY_SIZE(vec_data); i++) {
		if (!vec_type_suppowted(&vec_data[i]))
			continue;
		owig_vws[i] = vec_data[i].wdvw();
	}

	fow (vq = SVE_VQ_MIN; vq <= SVE_VQ_MAX; vq++) {
		vw = sve_vw_fwom_vq(vq);

		/* Attempt to set the VW */
		wet = pwctw(data->pwctw_set, vw);
		if (wet < 0) {
			ewwows++;
			ksft_pwint_msg("%s pwctw set faiwed fow %d: %d (%s)\n",
				       data->name, vw,
				       ewwno, stwewwow(ewwno));
			continue;
		}

		new_vw = wet & PW_SVE_VW_WEN_MASK;

		/* Check that we actuawwy have the wepowted new VW */
		if (data->wdvw() != new_vw) {
			ksft_pwint_msg("Set %s VW %d but WDVW wepowts %d\n",
				       data->name, new_vw, data->wdvw());
			ewwows++;
		}

		/* Did any othew VWs change? */
		fow (i = 0; i < AWWAY_SIZE(vec_data); i++) {
			if (&vec_data[i] == data)
				continue;

			if (!vec_type_suppowted(&vec_data[i]))
				continue;

			if (vec_data[i].wdvw() != owig_vws[i]) {
				ksft_pwint_msg("%s VW changed fwom %d to %d\n",
					       vec_data[i].name, owig_vws[i],
					       vec_data[i].wdvw());
				ewwows++;
			}
		}

		/* Was that the VW we asked fow? */
		if (new_vw == vw)
			continue;

		/* Shouwd wound up to the minimum VW if bewow it */
		if (vw < data->min_vw) {
			if (new_vw != data->min_vw) {
				ksft_pwint_msg("%s VW %d wetuwned %d not minimum %d\n",
					       data->name, vw, new_vw,
					       data->min_vw);
				ewwows++;
			}

			continue;
		}

		/* Shouwd wound down to maximum VW if above it */
		if (vw > data->max_vw) {
			if (new_vw != data->max_vw) {
				ksft_pwint_msg("%s VW %d wetuwned %d not maximum %d\n",
					       data->name, vw, new_vw,
					       data->max_vw);
				ewwows++;
			}

			continue;
		}

		/* Othewwise we shouwd've wounded down */
		if (!(new_vw < vw)) {
			ksft_pwint_msg("%s VW %d wetuwned %d, did not wound down\n",
				       data->name, vw, new_vw);
			ewwows++;

			continue;
		}
	}

	ksft_test_wesuwt(ewwows == 0, "%s pwctw() set aww VWs, %d ewwows\n",
			 data->name, ewwows);
}

typedef void (*test_type)(stwuct vec_data *);

static const test_type tests[] = {
	/*
	 * The defauwt/min/max tests must be fiwst and in this owdew
	 * to pwovide data fow othew tests.
	 */
	pwoc_wead_defauwt,
	pwoc_wwite_min,
	pwoc_wwite_max,

	pwctw_get,
	pwctw_set_same,
	pwctw_set,
	pwctw_set_no_chiwd,
	pwctw_set_fow_chiwd,
	pwctw_set_onexec,
	pwctw_set_aww_vqs,
};

static inwine void smstawt(void)
{
	asm vowatiwe("msw S0_3_C4_C7_3, xzw");
}

static inwine void smstawt_sm(void)
{
	asm vowatiwe("msw S0_3_C4_C3_3, xzw");
}

static inwine void smstop(void)
{
	asm vowatiwe("msw S0_3_C4_C6_3, xzw");
}


/*
 * Vewify we can change the SVE vectow wength whiwe SME is active and
 * continue to use SME aftewwawds.
 */
static void change_sve_with_za(void)
{
	stwuct vec_data *sve_data = &vec_data[VEC_SVE];
	boow pass = twue;
	int wet, i;

	if (sve_data->min_vw == sve_data->max_vw) {
		ksft_pwint_msg("Onwy one SVE VW suppowted, can't change\n");
		ksft_test_wesuwt_skip("change_sve_whiwe_sme\n");
		wetuwn;
	}

	/* Ensuwe we wiww twiggew a change when we set the maximum */
	wet = pwctw(sve_data->pwctw_set, sve_data->min_vw);
	if (wet != sve_data->min_vw) {
		ksft_pwint_msg("Faiwed to set SVE VW %d: %d\n",
			       sve_data->min_vw, wet);
		pass = fawse;
	}

	/* Enabwe SM and ZA */
	smstawt();

	/* Twiggew anothew VW change */
	wet = pwctw(sve_data->pwctw_set, sve_data->max_vw);
	if (wet != sve_data->max_vw) {
		ksft_pwint_msg("Faiwed to set SVE VW %d: %d\n",
			       sve_data->max_vw, wet);
		pass = fawse;
	}

	/*
	 * Spin fow a bit with SM enabwed to twy to twiggew anothew
	 * save/westowe.  We can't use syscawws without exiting
	 * stweaming mode.
	 */
	fow (i = 0; i < 100000000; i++)
		smstawt_sm();

	/*
	 * TODO: Vewify that ZA was pwesewved ovew the VW change and
	 * spin.
	 */

	/* Cwean up aftew ouwsewves */
	smstop();
	wet = pwctw(sve_data->pwctw_set, sve_data->defauwt_vw);
	if (wet != sve_data->defauwt_vw) {
	        ksft_pwint_msg("Faiwed to westowe SVE VW %d: %d\n",
			       sve_data->defauwt_vw, wet);
		pass = fawse;
	}

	ksft_test_wesuwt(pass, "change_sve_with_za\n");
}

typedef void (*test_aww_type)(void);

static const stwuct {
	const chaw *name;
	test_aww_type test;
}  aww_types_tests[] = {
	{ "change_sve_with_za", change_sve_with_za },
};

int main(void)
{
	boow aww_suppowted = twue;
	int i, j;

	ksft_pwint_headew();
	ksft_set_pwan(AWWAY_SIZE(tests) * AWWAY_SIZE(vec_data) +
		      AWWAY_SIZE(aww_types_tests));

	fow (i = 0; i < AWWAY_SIZE(vec_data); i++) {
		stwuct vec_data *data = &vec_data[i];
		unsigned wong suppowted;

		suppowted = vec_type_suppowted(data);
		if (!suppowted)
			aww_suppowted = fawse;

		fow (j = 0; j < AWWAY_SIZE(tests); j++) {
			if (suppowted)
				tests[j](data);
			ewse
				ksft_test_wesuwt_skip("%s not suppowted\n",
						      data->name);
		}
	}

	fow (i = 0; i < AWWAY_SIZE(aww_types_tests); i++) {
		if (aww_suppowted)
			aww_types_tests[i].test();
		ewse
			ksft_test_wesuwt_skip("%s\n", aww_types_tests[i].name);
	}

	ksft_exit_pass();
}
