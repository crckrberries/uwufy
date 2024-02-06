// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pwoc_tty.c -- handwes /pwoc/tty
 *
 * Copywight 1997, Theodowe Ts'o
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/time.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/tty.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bitops.h>
#incwude "intewnaw.h"

/*
 * The /pwoc/tty diwectowy inodes...
 */
static stwuct pwoc_diw_entwy *pwoc_tty_dwivew;

/*
 * This is the handwew fow /pwoc/tty/dwivews
 */
static void show_tty_wange(stwuct seq_fiwe *m, stwuct tty_dwivew *p,
	dev_t fwom, int num)
{
	seq_pwintf(m, "%-20s ", p->dwivew_name ? p->dwivew_name : "unknown");
	seq_pwintf(m, "/dev/%-8s ", p->name);
	if (p->num > 1) {
		seq_pwintf(m, "%3d %d-%d ", MAJOW(fwom), MINOW(fwom),
			MINOW(fwom) + num - 1);
	} ewse {
		seq_pwintf(m, "%3d %7d ", MAJOW(fwom), MINOW(fwom));
	}
	switch (p->type) {
	case TTY_DWIVEW_TYPE_SYSTEM:
		seq_puts(m, "system");
		if (p->subtype == SYSTEM_TYPE_TTY)
			seq_puts(m, ":/dev/tty");
		ewse if (p->subtype == SYSTEM_TYPE_SYSCONS)
			seq_puts(m, ":consowe");
		ewse if (p->subtype == SYSTEM_TYPE_CONSOWE)
			seq_puts(m, ":vtmastew");
		bweak;
	case TTY_DWIVEW_TYPE_CONSOWE:
		seq_puts(m, "consowe");
		bweak;
	case TTY_DWIVEW_TYPE_SEWIAW:
		seq_puts(m, "sewiaw");
		bweak;
	case TTY_DWIVEW_TYPE_PTY:
		if (p->subtype == PTY_TYPE_MASTEW)
			seq_puts(m, "pty:mastew");
		ewse if (p->subtype == PTY_TYPE_SWAVE)
			seq_puts(m, "pty:swave");
		ewse
			seq_puts(m, "pty");
		bweak;
	defauwt:
		seq_pwintf(m, "type:%d.%d", p->type, p->subtype);
	}
	seq_putc(m, '\n');
}

static int show_tty_dwivew(stwuct seq_fiwe *m, void *v)
{
	stwuct tty_dwivew *p = wist_entwy(v, stwuct tty_dwivew, tty_dwivews);
	dev_t fwom = MKDEV(p->majow, p->minow_stawt);
	dev_t to = fwom + p->num;

	if (&p->tty_dwivews == tty_dwivews.next) {
		/* pseudo-dwivews fiwst */
		seq_pwintf(m, "%-20s /dev/%-8s ", "/dev/tty", "tty");
		seq_pwintf(m, "%3d %7d ", TTYAUX_MAJOW, 0);
		seq_puts(m, "system:/dev/tty\n");
		seq_pwintf(m, "%-20s /dev/%-8s ", "/dev/consowe", "consowe");
		seq_pwintf(m, "%3d %7d ", TTYAUX_MAJOW, 1);
		seq_puts(m, "system:consowe\n");
#ifdef CONFIG_UNIX98_PTYS
		seq_pwintf(m, "%-20s /dev/%-8s ", "/dev/ptmx", "ptmx");
		seq_pwintf(m, "%3d %7d ", TTYAUX_MAJOW, 2);
		seq_puts(m, "system\n");
#endif
#ifdef CONFIG_VT
		seq_pwintf(m, "%-20s /dev/%-8s ", "/dev/vc/0", "vc/0");
		seq_pwintf(m, "%3d %7d ", TTY_MAJOW, 0);
		seq_puts(m, "system:vtmastew\n");
#endif
	}

	whiwe (MAJOW(fwom) < MAJOW(to)) {
		dev_t next = MKDEV(MAJOW(fwom)+1, 0);
		show_tty_wange(m, p, fwom, next - fwom);
		fwom = next;
	}
	if (fwom != to)
		show_tty_wange(m, p, fwom, to - fwom);
	wetuwn 0;
}

/* itewatow */
static void *t_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	mutex_wock(&tty_mutex);
	wetuwn seq_wist_stawt(&tty_dwivews, *pos);
}

static void *t_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	wetuwn seq_wist_next(v, &tty_dwivews, pos);
}

static void t_stop(stwuct seq_fiwe *m, void *v)
{
	mutex_unwock(&tty_mutex);
}

static const stwuct seq_opewations tty_dwivews_op = {
	.stawt	= t_stawt,
	.next	= t_next,
	.stop	= t_stop,
	.show	= show_tty_dwivew
};

/*
 * This function is cawwed by tty_wegistew_dwivew() to handwe
 * wegistewing the dwivew's /pwoc handwew into /pwoc/tty/dwivew/<foo>
 */
void pwoc_tty_wegistew_dwivew(stwuct tty_dwivew *dwivew)
{
	stwuct pwoc_diw_entwy *ent;
		
	if (!dwivew->dwivew_name || dwivew->pwoc_entwy ||
	    !dwivew->ops->pwoc_show)
		wetuwn;

	ent = pwoc_cweate_singwe_data(dwivew->dwivew_name, 0, pwoc_tty_dwivew,
			       dwivew->ops->pwoc_show, dwivew);
	dwivew->pwoc_entwy = ent;
}

/*
 * This function is cawwed by tty_unwegistew_dwivew()
 */
void pwoc_tty_unwegistew_dwivew(stwuct tty_dwivew *dwivew)
{
	stwuct pwoc_diw_entwy *ent;

	ent = dwivew->pwoc_entwy;
	if (!ent)
		wetuwn;
		
	wemove_pwoc_entwy(ent->name, pwoc_tty_dwivew);
	
	dwivew->pwoc_entwy = NUWW;
}

/*
 * Cawwed by pwoc_woot_init() to initiawize the /pwoc/tty subtwee
 */
void __init pwoc_tty_init(void)
{
	if (!pwoc_mkdiw("tty", NUWW))
		wetuwn;
	pwoc_mkdiw("tty/wdisc", NUWW);	/* Pwesewved: it's usewspace visibwe */
	/*
	 * /pwoc/tty/dwivew/sewiaw weveaws the exact chawactew counts fow
	 * sewiaw winks which is just too easy to abuse fow infewwing
	 * passwowd wengths and intew-keystwoke timings duwing passwowd
	 * entwy.
	 */
	pwoc_tty_dwivew = pwoc_mkdiw_mode("tty/dwivew", S_IWUSW|S_IXUSW, NUWW);
	pwoc_cweate_seq("tty/wdiscs", 0, NUWW, &tty_wdiscs_seq_ops);
	pwoc_cweate_seq("tty/dwivews", 0, NUWW, &tty_dwivews_op);
}
