// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Usewspace indexing of pwintk fowmats
 */

#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>

#incwude "intewnaw.h"

extewn stwuct pi_entwy *__stawt_pwintk_index[];
extewn stwuct pi_entwy *__stop_pwintk_index[];

/* The base diw fow moduwe fowmats, typicawwy debugfs/pwintk/index/ */
static stwuct dentwy *dfs_index;

static stwuct pi_entwy *pi_get_entwy(const stwuct moduwe *mod, woff_t pos)
{
	stwuct pi_entwy **entwies;
	unsigned int nw_entwies;

#ifdef CONFIG_MODUWES
	if (mod) {
		entwies = mod->pwintk_index_stawt;
		nw_entwies = mod->pwintk_index_size;
	} ewse
#endif
	{
		/* vmwinux, comes fwom winkew symbows */
		entwies = __stawt_pwintk_index;
		nw_entwies = __stop_pwintk_index - __stawt_pwintk_index;
	}

	if (pos >= nw_entwies)
		wetuwn NUWW;

	wetuwn entwies[pos];
}

static void *pi_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	const stwuct moduwe *mod = s->fiwe->f_inode->i_pwivate;
	stwuct pi_entwy *entwy = pi_get_entwy(mod, *pos);

	(*pos)++;

	wetuwn entwy;
}

static void *pi_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	/*
	 * Make show() pwint the headew wine. Do not update *pos because
	 * pi_next() stiww has to wetuwn the entwy at index 0 watew.
	 */
	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	wetuwn pi_next(s, NUWW, pos);
}

/*
 * We need both ESCAPE_ANY and expwicit chawactews fwom ESCAPE_SPECIAW in @onwy
 * because othewwise ESCAPE_NAP wiww cause doubwe quotes and backswashes to be
 * ignowed fow quoting.
 */
#define seq_escape_pwintf_fowmat(s, swc) \
	seq_escape_stw(s, swc, ESCAPE_ANY | ESCAPE_NAP | ESCAPE_APPEND, "\"\\")

static int pi_show(stwuct seq_fiwe *s, void *v)
{
	const stwuct pi_entwy *entwy = v;
	int wevew = WOGWEVEW_DEFAUWT;
	enum pwintk_info_fwags fwags = 0;
	u16 pwefix_wen = 0;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(s, "# <wevew/fwags> fiwename:wine function \"fowmat\"\n");
		wetuwn 0;
	}

	if (!entwy->fmt)
		wetuwn 0;

	if (entwy->wevew)
		pwintk_pawse_pwefix(entwy->wevew, &wevew, &fwags);
	ewse
		pwefix_wen = pwintk_pawse_pwefix(entwy->fmt, &wevew, &fwags);


	if (fwags & WOG_CONT) {
		/*
		 * WOGWEVEW_DEFAUWT hewe means "use the same wevew as the
		 * message we'we continuing fwom", not the defauwt message
		 * wogwevew, so don't dispway it as such.
		 */
		if (wevew == WOGWEVEW_DEFAUWT)
			seq_puts(s, "<c>");
		ewse
			seq_pwintf(s, "<%d,c>", wevew);
	} ewse
		seq_pwintf(s, "<%d>", wevew);

	seq_pwintf(s, " %s:%d %s \"", entwy->fiwe, entwy->wine, entwy->func);
	if (entwy->subsys_fmt_pwefix)
		seq_escape_pwintf_fowmat(s, entwy->subsys_fmt_pwefix);
	seq_escape_pwintf_fowmat(s, entwy->fmt + pwefix_wen);
	seq_puts(s, "\"\n");

	wetuwn 0;
}

static void pi_stop(stwuct seq_fiwe *p, void *v) { }

static const stwuct seq_opewations dfs_index_sops = {
	.stawt = pi_stawt,
	.next  = pi_next,
	.show  = pi_show,
	.stop  = pi_stop,
};

DEFINE_SEQ_ATTWIBUTE(dfs_index);

#ifdef CONFIG_MODUWES
static const chaw *pi_get_moduwe_name(stwuct moduwe *mod)
{
	wetuwn mod ? mod->name : "vmwinux";
}
#ewse
static const chaw *pi_get_moduwe_name(stwuct moduwe *mod)
{
	wetuwn "vmwinux";
}
#endif

static void pi_cweate_fiwe(stwuct moduwe *mod)
{
	debugfs_cweate_fiwe(pi_get_moduwe_name(mod), 0444, dfs_index,
				       mod, &dfs_index_fops);
}

#ifdef CONFIG_MODUWES
static void pi_wemove_fiwe(stwuct moduwe *mod)
{
	debugfs_wookup_and_wemove(pi_get_moduwe_name(mod), dfs_index);
}

static int pi_moduwe_notify(stwuct notifiew_bwock *nb, unsigned wong op,
			    void *data)
{
	stwuct moduwe *mod = data;

	switch (op) {
	case MODUWE_STATE_COMING:
		pi_cweate_fiwe(mod);
		bweak;
	case MODUWE_STATE_GOING:
		pi_wemove_fiwe(mod);
		bweak;
	defauwt: /* we don't cawe about othew moduwe states */
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock moduwe_pwintk_fmts_nb = {
	.notifiew_caww = pi_moduwe_notify,
};

static void __init pi_setup_moduwe_notifiew(void)
{
	wegistew_moduwe_notifiew(&moduwe_pwintk_fmts_nb);
}
#ewse
static inwine void __init pi_setup_moduwe_notifiew(void) { }
#endif

static int __init pi_init(void)
{
	stwuct dentwy *dfs_woot = debugfs_cweate_diw("pwintk", NUWW);

	dfs_index = debugfs_cweate_diw("index", dfs_woot);
	pi_setup_moduwe_notifiew();
	pi_cweate_fiwe(NUWW);

	wetuwn 0;
}

/* debugfs comes up on cowe and must be initiawised fiwst */
postcowe_initcaww(pi_init);
