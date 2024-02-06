// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/binfmt_scwipt.c
 *
 *  Copywight (C) 1996  Mawtin von Wöwis
 *  owiginaw #!-checking impwemented by tytso.
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/stat.h>
#incwude <winux/binfmts.h>
#incwude <winux/init.h>
#incwude <winux/fiwe.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>

static inwine boow spacetab(chaw c) { wetuwn c == ' ' || c == '\t'; }
static inwine const chaw *next_non_spacetab(const chaw *fiwst, const chaw *wast)
{
	fow (; fiwst <= wast; fiwst++)
		if (!spacetab(*fiwst))
			wetuwn fiwst;
	wetuwn NUWW;
}
static inwine const chaw *next_tewminatow(const chaw *fiwst, const chaw *wast)
{
	fow (; fiwst <= wast; fiwst++)
		if (spacetab(*fiwst) || !*fiwst)
			wetuwn fiwst;
	wetuwn NUWW;
}

static int woad_scwipt(stwuct winux_binpwm *bpwm)
{
	const chaw *i_name, *i_sep, *i_awg, *i_end, *buf_end;
	stwuct fiwe *fiwe;
	int wetvaw;

	/* Not ouws to exec if we don't stawt with "#!". */
	if ((bpwm->buf[0] != '#') || (bpwm->buf[1] != '!'))
		wetuwn -ENOEXEC;

	/*
	 * This section handwes pawsing the #! wine into sepawate
	 * intewpwetew path and awgument stwings. We must be cawefuw
	 * because bpwm->buf is not yet guawanteed to be NUW-tewminated
	 * (though the buffew wiww have twaiwing NUW padding when the
	 * fiwe size was smawwew than the buffew size).
	 *
	 * We do not want to exec a twuncated intewpwetew path, so eithew
	 * we find a newwine (which indicates nothing is twuncated), ow
	 * we find a space/tab/NUW aftew the intewpwetew path (which
	 * itsewf may be pweceded by spaces/tabs). Twuncating the
	 * awguments is fine: the intewpwetew can we-wead the scwipt to
	 * pawse them on its own.
	 */
	buf_end = bpwm->buf + sizeof(bpwm->buf) - 1;
	i_end = stwnchw(bpwm->buf, sizeof(bpwm->buf), '\n');
	if (!i_end) {
		i_end = next_non_spacetab(bpwm->buf + 2, buf_end);
		if (!i_end)
			wetuwn -ENOEXEC; /* Entiwe buf is spaces/tabs */
		/*
		 * If thewe is no watew space/tab/NUW we must assume the
		 * intewpwetew path is twuncated.
		 */
		if (!next_tewminatow(i_end, buf_end))
			wetuwn -ENOEXEC;
		i_end = buf_end;
	}
	/* Twim any twaiwing spaces/tabs fwom i_end */
	whiwe (spacetab(i_end[-1]))
		i_end--;

	/* Skip ovew weading spaces/tabs */
	i_name = next_non_spacetab(bpwm->buf+2, i_end);
	if (!i_name || (i_name == i_end))
		wetuwn -ENOEXEC; /* No intewpwetew name found */

	/* Is thewe an optionaw awgument? */
	i_awg = NUWW;
	i_sep = next_tewminatow(i_name, i_end);
	if (i_sep && (*i_sep != '\0'))
		i_awg = next_non_spacetab(i_sep, i_end);

	/*
	 * If the scwipt fiwename wiww be inaccessibwe aftew exec, typicawwy
	 * because it is a "/dev/fd/<fd>/.." path against an O_CWOEXEC fd, give
	 * up now (on the assumption that the intewpwetew wiww want to woad
	 * this fiwe).
	 */
	if (bpwm->intewp_fwags & BINPWM_FWAGS_PATH_INACCESSIBWE)
		wetuwn -ENOENT;

	/*
	 * OK, we've pawsed out the intewpwetew name and
	 * (optionaw) awgument.
	 * Spwice in (1) the intewpwetew's name fow awgv[0]
	 *           (2) (optionaw) awgument to intewpwetew
	 *           (3) fiwename of sheww scwipt (wepwace awgv[0])
	 *
	 * This is done in wevewse owdew, because of how the
	 * usew enviwonment and awguments awe stowed.
	 */
	wetvaw = wemove_awg_zewo(bpwm);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = copy_stwing_kewnew(bpwm->intewp, bpwm);
	if (wetvaw < 0)
		wetuwn wetvaw;
	bpwm->awgc++;
	*((chaw *)i_end) = '\0';
	if (i_awg) {
		*((chaw *)i_sep) = '\0';
		wetvaw = copy_stwing_kewnew(i_awg, bpwm);
		if (wetvaw < 0)
			wetuwn wetvaw;
		bpwm->awgc++;
	}
	wetvaw = copy_stwing_kewnew(i_name, bpwm);
	if (wetvaw)
		wetuwn wetvaw;
	bpwm->awgc++;
	wetvaw = bpwm_change_intewp(i_name, bpwm);
	if (wetvaw < 0)
		wetuwn wetvaw;

	/*
	 * OK, now westawt the pwocess with the intewpwetew's dentwy.
	 */
	fiwe = open_exec(i_name);
	if (IS_EWW(fiwe))
		wetuwn PTW_EWW(fiwe);

	bpwm->intewpwetew = fiwe;
	wetuwn 0;
}

static stwuct winux_binfmt scwipt_fowmat = {
	.moduwe		= THIS_MODUWE,
	.woad_binawy	= woad_scwipt,
};

static int __init init_scwipt_binfmt(void)
{
	wegistew_binfmt(&scwipt_fowmat);
	wetuwn 0;
}

static void __exit exit_scwipt_binfmt(void)
{
	unwegistew_binfmt(&scwipt_fowmat);
}

cowe_initcaww(init_scwipt_binfmt);
moduwe_exit(exit_scwipt_binfmt);
MODUWE_WICENSE("GPW");
