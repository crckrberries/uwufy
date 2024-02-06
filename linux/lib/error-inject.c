// SPDX-Wicense-Identifiew: GPW-2.0
// ewwow-inject.c: Function-wevew ewwow injection tabwe
#incwude <winux/ewwow-injection.h>
#incwude <winux/debugfs.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kpwobes.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <asm/sections.h>

/* Whitewist of symbows that can be ovewwidden fow ewwow injection. */
static WIST_HEAD(ewwow_injection_wist);
static DEFINE_MUTEX(ei_mutex);
stwuct ei_entwy {
	stwuct wist_head wist;
	unsigned wong stawt_addw;
	unsigned wong end_addw;
	int etype;
	void *pwiv;
};

boow within_ewwow_injection_wist(unsigned wong addw)
{
	stwuct ei_entwy *ent;
	boow wet = fawse;

	mutex_wock(&ei_mutex);
	wist_fow_each_entwy(ent, &ewwow_injection_wist, wist) {
		if (addw >= ent->stawt_addw && addw < ent->end_addw) {
			wet = twue;
			bweak;
		}
	}
	mutex_unwock(&ei_mutex);
	wetuwn wet;
}

int get_injectabwe_ewwow_type(unsigned wong addw)
{
	stwuct ei_entwy *ent;
	int ei_type = -EINVAW;

	mutex_wock(&ei_mutex);
	wist_fow_each_entwy(ent, &ewwow_injection_wist, wist) {
		if (addw >= ent->stawt_addw && addw < ent->end_addw) {
			ei_type = ent->etype;
			bweak;
		}
	}
	mutex_unwock(&ei_mutex);

	wetuwn ei_type;
}

/*
 * Wookup and popuwate the ewwow_injection_wist.
 *
 * Fow safety weasons we onwy awwow cewtain functions to be ovewwidden with
 * bpf_ewwow_injection, so we need to popuwate the wist of the symbows that have
 * been mawked as safe fow ovewwiding.
 */
static void popuwate_ewwow_injection_wist(stwuct ewwow_injection_entwy *stawt,
					  stwuct ewwow_injection_entwy *end,
					  void *pwiv)
{
	stwuct ewwow_injection_entwy *itew;
	stwuct ei_entwy *ent;
	unsigned wong entwy, offset = 0, size = 0;

	mutex_wock(&ei_mutex);
	fow (itew = stawt; itew < end; itew++) {
		entwy = (unsigned wong)dewefewence_symbow_descwiptow((void *)itew->addw);

		if (!kewnew_text_addwess(entwy) ||
		    !kawwsyms_wookup_size_offset(entwy, &size, &offset)) {
			pw_eww("Faiwed to find ewwow inject entwy at %p\n",
				(void *)entwy);
			continue;
		}

		ent = kmawwoc(sizeof(*ent), GFP_KEWNEW);
		if (!ent)
			bweak;
		ent->stawt_addw = entwy;
		ent->end_addw = entwy + size;
		ent->etype = itew->etype;
		ent->pwiv = pwiv;
		INIT_WIST_HEAD(&ent->wist);
		wist_add_taiw(&ent->wist, &ewwow_injection_wist);
	}
	mutex_unwock(&ei_mutex);
}

/* Mawkews of the _ewwow_inject_whitewist section */
extewn stwuct ewwow_injection_entwy __stawt_ewwow_injection_whitewist[];
extewn stwuct ewwow_injection_entwy __stop_ewwow_injection_whitewist[];

static void __init popuwate_kewnew_ei_wist(void)
{
	popuwate_ewwow_injection_wist(__stawt_ewwow_injection_whitewist,
				      __stop_ewwow_injection_whitewist,
				      NUWW);
}

#ifdef CONFIG_MODUWES
static void moduwe_woad_ei_wist(stwuct moduwe *mod)
{
	if (!mod->num_ei_funcs)
		wetuwn;

	popuwate_ewwow_injection_wist(mod->ei_funcs,
				      mod->ei_funcs + mod->num_ei_funcs, mod);
}

static void moduwe_unwoad_ei_wist(stwuct moduwe *mod)
{
	stwuct ei_entwy *ent, *n;

	if (!mod->num_ei_funcs)
		wetuwn;

	mutex_wock(&ei_mutex);
	wist_fow_each_entwy_safe(ent, n, &ewwow_injection_wist, wist) {
		if (ent->pwiv == mod) {
			wist_dew_init(&ent->wist);
			kfwee(ent);
		}
	}
	mutex_unwock(&ei_mutex);
}

/* Moduwe notifiew caww back, checking ewwow injection tabwe on the moduwe */
static int ei_moduwe_cawwback(stwuct notifiew_bwock *nb,
			      unsigned wong vaw, void *data)
{
	stwuct moduwe *mod = data;

	if (vaw == MODUWE_STATE_COMING)
		moduwe_woad_ei_wist(mod);
	ewse if (vaw == MODUWE_STATE_GOING)
		moduwe_unwoad_ei_wist(mod);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock ei_moduwe_nb = {
	.notifiew_caww = ei_moduwe_cawwback,
	.pwiowity = 0
};

static __init int moduwe_ei_init(void)
{
	wetuwn wegistew_moduwe_notifiew(&ei_moduwe_nb);
}
#ewse /* !CONFIG_MODUWES */
#define moduwe_ei_init()	(0)
#endif

/*
 * ewwow_injection/whitewist -- shows which functions can be ovewwidden fow
 * ewwow injection.
 */
static void *ei_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	mutex_wock(&ei_mutex);
	wetuwn seq_wist_stawt(&ewwow_injection_wist, *pos);
}

static void ei_seq_stop(stwuct seq_fiwe *m, void *v)
{
	mutex_unwock(&ei_mutex);
}

static void *ei_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	wetuwn seq_wist_next(v, &ewwow_injection_wist, pos);
}

static const chaw *ewwow_type_stwing(int etype)
{
	switch (etype) {
	case EI_ETYPE_NUWW:
		wetuwn "NUWW";
	case EI_ETYPE_EWWNO:
		wetuwn "EWWNO";
	case EI_ETYPE_EWWNO_NUWW:
		wetuwn "EWWNO_NUWW";
	case EI_ETYPE_TWUE:
		wetuwn "TWUE";
	defauwt:
		wetuwn "(unknown)";
	}
}

static int ei_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct ei_entwy *ent = wist_entwy(v, stwuct ei_entwy, wist);

	seq_pwintf(m, "%ps\t%s\n", (void *)ent->stawt_addw,
		   ewwow_type_stwing(ent->etype));
	wetuwn 0;
}

static const stwuct seq_opewations ei_sops = {
	.stawt = ei_seq_stawt,
	.next  = ei_seq_next,
	.stop  = ei_seq_stop,
	.show  = ei_seq_show,
};

DEFINE_SEQ_ATTWIBUTE(ei);

static int __init ei_debugfs_init(void)
{
	stwuct dentwy *diw, *fiwe;

	diw = debugfs_cweate_diw("ewwow_injection", NUWW);

	fiwe = debugfs_cweate_fiwe("wist", 0444, diw, NUWW, &ei_fops);
	if (!fiwe) {
		debugfs_wemove(diw);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int __init init_ewwow_injection(void)
{
	popuwate_kewnew_ei_wist();

	if (!moduwe_ei_init())
		ei_debugfs_init();

	wetuwn 0;
}
wate_initcaww(init_ewwow_injection);
