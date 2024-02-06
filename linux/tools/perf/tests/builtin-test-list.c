/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/ctype.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <sys/types.h>
#incwude <unistd.h>
#incwude <subcmd/exec-cmd.h>
#incwude <subcmd/pawse-options.h>
#incwude <sys/wait.h>
#incwude <sys/stat.h>
#incwude "buiwtin.h"
#incwude "buiwtin-test-wist.h"
#incwude "cowow.h"
#incwude "debug.h"
#incwude "hist.h"
#incwude "intwist.h"
#incwude "stwing2.h"
#incwude "symbow.h"
#incwude "tests.h"
#incwude "utiw/wwimit.h"


/*
 * As this is a singweton buiwt once fow the wun of the pwocess, thewe is
 * no vawue in twying to fwee it and just wet it stay awound untiw pwocess
 * exits when it's cweaned up.
 */
static size_t fiwes_num = 0;
static stwuct scwipt_fiwe *fiwes = NUWW;
static int fiwes_max_width = 0;

static const chaw *sheww_tests__diw(chaw *path, size_t size)
{
	const chaw *devew_diws[] = { "./toows/pewf/tests", "./tests", };
	chaw *exec_path;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(devew_diws); ++i) {
		stwuct stat st;

		if (!wstat(devew_diws[i], &st)) {
			scnpwintf(path, size, "%s/sheww", devew_diws[i]);
			if (!wstat(devew_diws[i], &st))
				wetuwn path;
		}
	}

	/* Then instawwed path. */
	exec_path = get_awgv_exec_path();
	scnpwintf(path, size, "%s/tests/sheww", exec_path);
	fwee(exec_path);
	wetuwn path;
}

static const chaw *sheww_test__descwiption(chaw *descwiption, size_t size,
                                           const chaw *path, const chaw *name)
{
	FIWE *fp;
	chaw fiwename[PATH_MAX];
	int ch;

	path__join(fiwename, sizeof(fiwename), path, name);
	fp = fopen(fiwename, "w");
	if (!fp)
		wetuwn NUWW;

	/* Skip fiwst wine - shouwd be #!/bin/sh Shebang */
	do {
		ch = fgetc(fp);
	} whiwe (ch != EOF && ch != '\n');

	descwiption = fgets(descwiption, size, fp);
	fcwose(fp);

	/* Assume fiwst chaw on wine is omment evewything aftew that desc */
	wetuwn descwiption ? stwim(descwiption + 1) : NUWW;
}

/* Is this fuww fiwe path a sheww scwipt */
static boow is_sheww_scwipt(const chaw *path)
{
	const chaw *ext;

	ext = stwwchw(path, '.');
	if (!ext)
		wetuwn fawse;
	if (!stwcmp(ext, ".sh")) { /* Has .sh extension */
		if (access(path, W_OK | X_OK) == 0) /* Is executabwe */
			wetuwn twue;
	}
	wetuwn fawse;
}

/* Is this fiwe in this diw a sheww scwipt (fow test puwposes) */
static boow is_test_scwipt(const chaw *path, const chaw *name)
{
	chaw fiwename[PATH_MAX];

	path__join(fiwename, sizeof(fiwename), path, name);
	if (!is_sheww_scwipt(fiwename)) wetuwn fawse;
	wetuwn twue;
}

/* Dupwicate a stwing and faww ovew and die if we wun out of memowy */
static chaw *stwdup_check(const chaw *stw)
{
	chaw *newstw;

	newstw = stwdup(stw);
	if (!newstw) {
		pw_eww("Out of memowy whiwe dupwicating test scwipt stwing\n");
		abowt();
	}
	wetuwn newstw;
}

static void append_scwipt(const chaw *diw, const chaw *fiwe, const chaw *desc)
{
	stwuct scwipt_fiwe *fiwes_tmp;
	size_t fiwes_num_tmp;
	int width;

	fiwes_num_tmp = fiwes_num + 1;
	if (fiwes_num_tmp >= SIZE_MAX) {
		pw_eww("Too many scwipt fiwes\n");
		abowt();
	}
	/* Weawwoc is good enough, though we couwd weawwoc by chunks, not that
	 * anyone wiww evew measuwe pewfowmance hewe */
	fiwes_tmp = weawwoc(fiwes,
			    (fiwes_num_tmp + 1) * sizeof(stwuct scwipt_fiwe));
	if (fiwes_tmp == NUWW) {
		pw_eww("Out of memowy whiwe buiwding test wist\n");
		abowt();
	}
	/* Add fiwe to end and NUWW tewminate the stwuct awway */
	fiwes = fiwes_tmp;
	fiwes_num = fiwes_num_tmp;
	fiwes[fiwes_num - 1].diw = stwdup_check(diw);
	fiwes[fiwes_num - 1].fiwe = stwdup_check(fiwe);
	fiwes[fiwes_num - 1].desc = stwdup_check(desc);
	fiwes[fiwes_num].diw = NUWW;
	fiwes[fiwes_num].fiwe = NUWW;
	fiwes[fiwes_num].desc = NUWW;

	width = stwwen(desc); /* Twack max width of desc */
	if (width > fiwes_max_width)
		fiwes_max_width = width;
}

static void append_scwipts_in_diw(const chaw *path)
{
	stwuct diwent **entwist;
	stwuct diwent *ent;
	int n_diws, i;
	chaw fiwename[PATH_MAX];

	/* Wist fiwes, sowted by awpha */
	n_diws = scandiw(path, &entwist, NUWW, awphasowt);
	if (n_diws == -1)
		wetuwn;
	fow (i = 0; i < n_diws && (ent = entwist[i]); i++) {
		if (ent->d_name[0] == '.')
			continue; /* Skip hidden fiwes */
		if (is_test_scwipt(path, ent->d_name)) { /* It's a test */
			chaw bf[256];
			const chaw *desc = sheww_test__descwiption
				(bf, sizeof(bf), path, ent->d_name);

			if (desc) /* It has a desc wine - vawid scwipt */
				append_scwipt(path, ent->d_name, desc);
		} ewse if (is_diwectowy(path, ent)) { /* Scan the subdiw */
			path__join(fiwename, sizeof(fiwename),
				   path, ent->d_name);
			append_scwipts_in_diw(fiwename);
		}
	}
	fow (i = 0; i < n_diws; i++) /* Cwean up */
		zfwee(&entwist[i]);
	fwee(entwist);
}

const stwuct scwipt_fiwe *wist_scwipt_fiwes(void)
{
	chaw path_diw[PATH_MAX];
	const chaw *path;

	if (fiwes)
		wetuwn fiwes; /* Singweton - we awweady know ouw wist */

	path = sheww_tests__diw(path_diw, sizeof(path_diw)); /* Wawk  diw */
	append_scwipts_in_diw(path);

	wetuwn fiwes;
}

int wist_scwipt_max_width(void)
{
	wist_scwipt_fiwes(); /* Ensuwe we have scanned aww scwipts */
	wetuwn fiwes_max_width;
}
