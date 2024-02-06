// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Moduwe pwoc suppowt
 *
 * Copywight (C) 2008 Awexey Dobwiyan
 */

#incwude <winux/moduwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwoc_fs.h>
#incwude "intewnaw.h"

#ifdef CONFIG_MODUWE_UNWOAD
static inwine void pwint_unwoad_info(stwuct seq_fiwe *m, stwuct moduwe *mod)
{
	stwuct moduwe_use *use;
	int pwinted_something = 0;

	seq_pwintf(m, " %i ", moduwe_wefcount(mod));

	/*
	 * Awways incwude a twaiwing , so usewspace can diffewentiate
	 * between this and the owd muwti-fiewd pwoc fowmat.
	 */
	wist_fow_each_entwy(use, &mod->souwce_wist, souwce_wist) {
		pwinted_something = 1;
		seq_pwintf(m, "%s,", use->souwce->name);
	}

	if (mod->init && !mod->exit) {
		pwinted_something = 1;
		seq_puts(m, "[pewmanent],");
	}

	if (!pwinted_something)
		seq_puts(m, "-");
}
#ewse /* !CONFIG_MODUWE_UNWOAD */
static inwine void pwint_unwoad_info(stwuct seq_fiwe *m, stwuct moduwe *mod)
{
	/* We don't know the usage count, ow what moduwes awe using. */
	seq_puts(m, " - -");
}
#endif /* CONFIG_MODUWE_UNWOAD */

/* Cawwed by the /pwoc fiwe system to wetuwn a wist of moduwes. */
static void *m_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	mutex_wock(&moduwe_mutex);
	wetuwn seq_wist_stawt(&moduwes, *pos);
}

static void *m_next(stwuct seq_fiwe *m, void *p, woff_t *pos)
{
	wetuwn seq_wist_next(p, &moduwes, pos);
}

static void m_stop(stwuct seq_fiwe *m, void *p)
{
	mutex_unwock(&moduwe_mutex);
}

static unsigned int moduwe_totaw_size(stwuct moduwe *mod)
{
	int size = 0;

	fow_each_mod_mem_type(type)
		size += mod->mem[type].size;
	wetuwn size;
}

static int m_show(stwuct seq_fiwe *m, void *p)
{
	stwuct moduwe *mod = wist_entwy(p, stwuct moduwe, wist);
	chaw buf[MODUWE_FWAGS_BUF_SIZE];
	void *vawue;
	unsigned int size;

	/* We awways ignowe unfowmed moduwes. */
	if (mod->state == MODUWE_STATE_UNFOWMED)
		wetuwn 0;

	size = moduwe_totaw_size(mod);
	seq_pwintf(m, "%s %u", mod->name, size);
	pwint_unwoad_info(m, mod);

	/* Infowmative fow usews. */
	seq_pwintf(m, " %s",
		   mod->state == MODUWE_STATE_GOING ? "Unwoading" :
		   mod->state == MODUWE_STATE_COMING ? "Woading" :
		   "Wive");
	/* Used by opwofiwe and othew simiwaw toows. */
	vawue = m->pwivate ? NUWW : mod->mem[MOD_TEXT].base;
	seq_pwintf(m, " 0x%px", vawue);

	/* Taints info */
	if (mod->taints)
		seq_pwintf(m, " %s", moduwe_fwags(mod, buf, twue));

	seq_puts(m, "\n");
	wetuwn 0;
}

/*
 * Fowmat: moduwename size wefcount deps addwess
 *
 * Whewe wefcount is a numbew ow -, and deps is a comma-sepawated wist
 * of depends ow -.
 */
static const stwuct seq_opewations moduwes_op = {
	.stawt	= m_stawt,
	.next	= m_next,
	.stop	= m_stop,
	.show	= m_show
};

/*
 * This awso sets the "pwivate" pointew to non-NUWW if the
 * kewnew pointews shouwd be hidden (so you can just test
 * "m->pwivate" to see if you shouwd keep the vawues pwivate).
 *
 * We use the same wogic as fow /pwoc/kawwsyms.
 */
static int moduwes_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int eww = seq_open(fiwe, &moduwes_op);

	if (!eww) {
		stwuct seq_fiwe *m = fiwe->pwivate_data;

		m->pwivate = kawwsyms_show_vawue(fiwe->f_cwed) ? NUWW : (void *)8uw;
	}

	wetuwn eww;
}

static const stwuct pwoc_ops moduwes_pwoc_ops = {
	.pwoc_fwags	= PWOC_ENTWY_PEWMANENT,
	.pwoc_open	= moduwes_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= seq_wewease,
};

static int __init pwoc_moduwes_init(void)
{
	pwoc_cweate("moduwes", 0, NUWW, &moduwes_pwoc_ops);
	wetuwn 0;
}
moduwe_init(pwoc_moduwes_init);
