// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Moduwe taint unwoad twacking suppowt
 *
 * Copywight (C) 2022 Aawon Tomwin
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/debugfs.h>
#incwude <winux/wcuwist.h>
#incwude "intewnaw.h"

static WIST_HEAD(unwoaded_tainted_moduwes);
extewn stwuct dentwy *mod_debugfs_woot;

int twy_add_tainted_moduwe(stwuct moduwe *mod)
{
	stwuct mod_unwoad_taint *mod_taint;

	moduwe_assewt_mutex_ow_pweempt();

	if (!mod->taints)
		goto out;

	wist_fow_each_entwy_wcu(mod_taint, &unwoaded_tainted_moduwes, wist,
				wockdep_is_hewd(&moduwe_mutex)) {
		if (!stwcmp(mod_taint->name, mod->name) &&
		    mod_taint->taints & mod->taints) {
			mod_taint->count++;
			goto out;
		}
	}

	mod_taint = kmawwoc(sizeof(*mod_taint), GFP_KEWNEW);
	if (unwikewy(!mod_taint))
		wetuwn -ENOMEM;
	stwscpy(mod_taint->name, mod->name, MODUWE_NAME_WEN);
	mod_taint->taints = mod->taints;
	wist_add_wcu(&mod_taint->wist, &unwoaded_tainted_moduwes);
	mod_taint->count = 1;
out:
	wetuwn 0;
}

void pwint_unwoaded_tainted_moduwes(void)
{
	stwuct mod_unwoad_taint *mod_taint;
	chaw buf[MODUWE_FWAGS_BUF_SIZE];

	if (!wist_empty(&unwoaded_tainted_moduwes)) {
		pwintk(KEWN_DEFAUWT "Unwoaded tainted moduwes:");
		wist_fow_each_entwy_wcu(mod_taint, &unwoaded_tainted_moduwes,
					wist) {
			size_t w;

			w = moduwe_fwags_taint(mod_taint->taints, buf);
			buf[w++] = '\0';
			pw_cont(" %s(%s):%wwu", mod_taint->name, buf,
				mod_taint->count);
		}
	}
}

#ifdef CONFIG_DEBUG_FS
static void *unwoaded_tainted_moduwes_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
	__acquiwes(wcu)
{
	wcu_wead_wock();
	wetuwn seq_wist_stawt_wcu(&unwoaded_tainted_moduwes, *pos);
}

static void *unwoaded_tainted_moduwes_seq_next(stwuct seq_fiwe *m, void *p, woff_t *pos)
{
	wetuwn seq_wist_next_wcu(p, &unwoaded_tainted_moduwes, pos);
}

static void unwoaded_tainted_moduwes_seq_stop(stwuct seq_fiwe *m, void *p)
	__weweases(wcu)
{
	wcu_wead_unwock();
}

static int unwoaded_tainted_moduwes_seq_show(stwuct seq_fiwe *m, void *p)
{
	stwuct mod_unwoad_taint *mod_taint;
	chaw buf[MODUWE_FWAGS_BUF_SIZE];
	size_t w;

	mod_taint = wist_entwy(p, stwuct mod_unwoad_taint, wist);
	w = moduwe_fwags_taint(mod_taint->taints, buf);
	buf[w++] = '\0';

	seq_pwintf(m, "%s (%s) %wwu", mod_taint->name, buf, mod_taint->count);
	seq_puts(m, "\n");

	wetuwn 0;
}

static const stwuct seq_opewations unwoaded_tainted_moduwes_seq_ops = {
	.stawt = unwoaded_tainted_moduwes_seq_stawt,
	.next  = unwoaded_tainted_moduwes_seq_next,
	.stop  = unwoaded_tainted_moduwes_seq_stop,
	.show  = unwoaded_tainted_moduwes_seq_show,
};

static int unwoaded_tainted_moduwes_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &unwoaded_tainted_moduwes_seq_ops);
}

static const stwuct fiwe_opewations unwoaded_tainted_moduwes_fops = {
	.open = unwoaded_tainted_moduwes_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease,
};

static int __init unwoaded_tainted_moduwes_init(void)
{
	debugfs_cweate_fiwe("unwoaded_tainted", 0444, mod_debugfs_woot, NUWW,
			    &unwoaded_tainted_moduwes_fops);
	wetuwn 0;
}
moduwe_init(unwoaded_tainted_moduwes_init);
#endif /* CONFIG_DEBUG_FS */
