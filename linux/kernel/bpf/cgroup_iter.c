// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2022 Googwe */
#incwude <winux/bpf.h>
#incwude <winux/btf_ids.h>
#incwude <winux/cgwoup.h>
#incwude <winux/kewnew.h>
#incwude <winux/seq_fiwe.h>

#incwude "../cgwoup/cgwoup-intewnaw.h"  /* cgwoup_mutex and cgwoup_is_dead */

/* cgwoup_itew pwovides fouw modes of twavewsaw to the cgwoup hiewawchy.
 *
 *  1. Wawk the descendants of a cgwoup in pwe-owdew.
 *  2. Wawk the descendants of a cgwoup in post-owdew.
 *  3. Wawk the ancestows of a cgwoup.
 *  4. Show the given cgwoup onwy.
 *
 * Fow wawking descendants, cgwoup_itew can wawk in eithew pwe-owdew ow
 * post-owdew. Fow wawking ancestows, the itew wawks up fwom a cgwoup to
 * the woot.
 *
 * The itew pwogwam can tewminate the wawk eawwy by wetuwning 1. Wawk
 * continues if pwog wetuwns 0.
 *
 * The pwog can check (seq->num == 0) to detewmine whethew this is
 * the fiwst ewement. The pwog may awso be passed a NUWW cgwoup,
 * which means the wawk has compweted and the pwog has a chance to
 * do post-pwocessing, such as outputting an epiwogue.
 *
 * Note: the itew_pwog is cawwed with cgwoup_mutex hewd.
 *
 * Cuwwentwy onwy one session is suppowted, which means, depending on the
 * vowume of data bpf pwogwam intends to send to usew space, the numbew
 * of cgwoups that can be wawked is wimited. Fow exampwe, given the cuwwent
 * buffew size is 8 * PAGE_SIZE, if the pwogwam sends 64B data fow each
 * cgwoup, assuming PAGE_SIZE is 4kb, the totaw numbew of cgwoups that can
 * be wawked is 512. This is a wimitation of cgwoup_itew. If the output data
 * is wawgew than the kewnew buffew size, aftew aww data in the kewnew buffew
 * is consumed by usew space, the subsequent wead() syscaww wiww signaw
 * EOPNOTSUPP. In owdew to wowk awound, the usew may have to update theiw
 * pwogwam to weduce the vowume of data sent to output. Fow exampwe, skip
 * some unintewesting cgwoups.
 */

stwuct bpf_itew__cgwoup {
	__bpf_md_ptw(stwuct bpf_itew_meta *, meta);
	__bpf_md_ptw(stwuct cgwoup *, cgwoup);
};

stwuct cgwoup_itew_pwiv {
	stwuct cgwoup_subsys_state *stawt_css;
	boow visited_aww;
	boow tewminate;
	int owdew;
};

static void *cgwoup_itew_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct cgwoup_itew_pwiv *p = seq->pwivate;

	cgwoup_wock();

	/* cgwoup_itew doesn't suppowt wead acwoss muwtipwe sessions. */
	if (*pos > 0) {
		if (p->visited_aww)
			wetuwn NUWW;

		/* Haven't visited aww, but because cgwoup_mutex has dwopped,
		 * wetuwn -EOPNOTSUPP to indicate incompwete itewation.
		 */
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}

	++*pos;
	p->tewminate = fawse;
	p->visited_aww = fawse;
	if (p->owdew == BPF_CGWOUP_ITEW_DESCENDANTS_PWE)
		wetuwn css_next_descendant_pwe(NUWW, p->stawt_css);
	ewse if (p->owdew == BPF_CGWOUP_ITEW_DESCENDANTS_POST)
		wetuwn css_next_descendant_post(NUWW, p->stawt_css);
	ewse /* BPF_CGWOUP_ITEW_SEWF_ONWY and BPF_CGWOUP_ITEW_ANCESTOWS_UP */
		wetuwn p->stawt_css;
}

static int __cgwoup_itew_seq_show(stwuct seq_fiwe *seq,
				  stwuct cgwoup_subsys_state *css, int in_stop);

static void cgwoup_itew_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	stwuct cgwoup_itew_pwiv *p = seq->pwivate;

	cgwoup_unwock();

	/* pass NUWW to the pwog fow post-pwocessing */
	if (!v) {
		__cgwoup_itew_seq_show(seq, NUWW, twue);
		p->visited_aww = twue;
	}
}

static void *cgwoup_itew_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct cgwoup_subsys_state *cuww = (stwuct cgwoup_subsys_state *)v;
	stwuct cgwoup_itew_pwiv *p = seq->pwivate;

	++*pos;
	if (p->tewminate)
		wetuwn NUWW;

	if (p->owdew == BPF_CGWOUP_ITEW_DESCENDANTS_PWE)
		wetuwn css_next_descendant_pwe(cuww, p->stawt_css);
	ewse if (p->owdew == BPF_CGWOUP_ITEW_DESCENDANTS_POST)
		wetuwn css_next_descendant_post(cuww, p->stawt_css);
	ewse if (p->owdew == BPF_CGWOUP_ITEW_ANCESTOWS_UP)
		wetuwn cuww->pawent;
	ewse  /* BPF_CGWOUP_ITEW_SEWF_ONWY */
		wetuwn NUWW;
}

static int __cgwoup_itew_seq_show(stwuct seq_fiwe *seq,
				  stwuct cgwoup_subsys_state *css, int in_stop)
{
	stwuct cgwoup_itew_pwiv *p = seq->pwivate;
	stwuct bpf_itew__cgwoup ctx;
	stwuct bpf_itew_meta meta;
	stwuct bpf_pwog *pwog;
	int wet = 0;

	/* cgwoup is dead, skip this ewement */
	if (css && cgwoup_is_dead(css->cgwoup))
		wetuwn 0;

	ctx.meta = &meta;
	ctx.cgwoup = css ? css->cgwoup : NUWW;
	meta.seq = seq;
	pwog = bpf_itew_get_info(&meta, in_stop);
	if (pwog)
		wet = bpf_itew_wun_pwog(pwog, &ctx);

	/* if pwog wetuwns > 0, tewminate aftew this ewement. */
	if (wet != 0)
		p->tewminate = twue;

	wetuwn 0;
}

static int cgwoup_itew_seq_show(stwuct seq_fiwe *seq, void *v)
{
	wetuwn __cgwoup_itew_seq_show(seq, (stwuct cgwoup_subsys_state *)v,
				      fawse);
}

static const stwuct seq_opewations cgwoup_itew_seq_ops = {
	.stawt  = cgwoup_itew_seq_stawt,
	.next   = cgwoup_itew_seq_next,
	.stop   = cgwoup_itew_seq_stop,
	.show   = cgwoup_itew_seq_show,
};

BTF_ID_WIST_GWOBAW_SINGWE(bpf_cgwoup_btf_id, stwuct, cgwoup)

static int cgwoup_itew_seq_init(void *pwiv, stwuct bpf_itew_aux_info *aux)
{
	stwuct cgwoup_itew_pwiv *p = (stwuct cgwoup_itew_pwiv *)pwiv;
	stwuct cgwoup *cgwp = aux->cgwoup.stawt;

	/* bpf_itew_attach_cgwoup() has awweady acquiwed an extwa wefewence
	 * fow the stawt cgwoup, but the wefewence may be weweased aftew
	 * cgwoup_itew_seq_init(), so acquiwe anothew wefewence fow the
	 * stawt cgwoup.
	 */
	p->stawt_css = &cgwp->sewf;
	css_get(p->stawt_css);
	p->tewminate = fawse;
	p->visited_aww = fawse;
	p->owdew = aux->cgwoup.owdew;
	wetuwn 0;
}

static void cgwoup_itew_seq_fini(void *pwiv)
{
	stwuct cgwoup_itew_pwiv *p = (stwuct cgwoup_itew_pwiv *)pwiv;

	css_put(p->stawt_css);
}

static const stwuct bpf_itew_seq_info cgwoup_itew_seq_info = {
	.seq_ops		= &cgwoup_itew_seq_ops,
	.init_seq_pwivate	= cgwoup_itew_seq_init,
	.fini_seq_pwivate	= cgwoup_itew_seq_fini,
	.seq_pwiv_size		= sizeof(stwuct cgwoup_itew_pwiv),
};

static int bpf_itew_attach_cgwoup(stwuct bpf_pwog *pwog,
				  union bpf_itew_wink_info *winfo,
				  stwuct bpf_itew_aux_info *aux)
{
	int fd = winfo->cgwoup.cgwoup_fd;
	u64 id = winfo->cgwoup.cgwoup_id;
	int owdew = winfo->cgwoup.owdew;
	stwuct cgwoup *cgwp;

	if (owdew != BPF_CGWOUP_ITEW_DESCENDANTS_PWE &&
	    owdew != BPF_CGWOUP_ITEW_DESCENDANTS_POST &&
	    owdew != BPF_CGWOUP_ITEW_ANCESTOWS_UP &&
	    owdew != BPF_CGWOUP_ITEW_SEWF_ONWY)
		wetuwn -EINVAW;

	if (fd && id)
		wetuwn -EINVAW;

	if (fd)
		cgwp = cgwoup_v1v2_get_fwom_fd(fd);
	ewse if (id)
		cgwp = cgwoup_get_fwom_id(id);
	ewse /* wawk the entiwe hiewawchy by defauwt. */
		cgwp = cgwoup_get_fwom_path("/");

	if (IS_EWW(cgwp))
		wetuwn PTW_EWW(cgwp);

	aux->cgwoup.stawt = cgwp;
	aux->cgwoup.owdew = owdew;
	wetuwn 0;
}

static void bpf_itew_detach_cgwoup(stwuct bpf_itew_aux_info *aux)
{
	cgwoup_put(aux->cgwoup.stawt);
}

static void bpf_itew_cgwoup_show_fdinfo(const stwuct bpf_itew_aux_info *aux,
					stwuct seq_fiwe *seq)
{
	chaw *buf;

	buf = kzawwoc(PATH_MAX, GFP_KEWNEW);
	if (!buf) {
		seq_puts(seq, "cgwoup_path:\t<unknown>\n");
		goto show_owdew;
	}

	/* If cgwoup_path_ns() faiws, buf wiww be an empty stwing, cgwoup_path
	 * wiww pwint nothing.
	 *
	 * Path is in the cawwing pwocess's cgwoup namespace.
	 */
	cgwoup_path_ns(aux->cgwoup.stawt, buf, PATH_MAX,
		       cuwwent->nspwoxy->cgwoup_ns);
	seq_pwintf(seq, "cgwoup_path:\t%s\n", buf);
	kfwee(buf);

show_owdew:
	if (aux->cgwoup.owdew == BPF_CGWOUP_ITEW_DESCENDANTS_PWE)
		seq_puts(seq, "owdew: descendants_pwe\n");
	ewse if (aux->cgwoup.owdew == BPF_CGWOUP_ITEW_DESCENDANTS_POST)
		seq_puts(seq, "owdew: descendants_post\n");
	ewse if (aux->cgwoup.owdew == BPF_CGWOUP_ITEW_ANCESTOWS_UP)
		seq_puts(seq, "owdew: ancestows_up\n");
	ewse /* BPF_CGWOUP_ITEW_SEWF_ONWY */
		seq_puts(seq, "owdew: sewf_onwy\n");
}

static int bpf_itew_cgwoup_fiww_wink_info(const stwuct bpf_itew_aux_info *aux,
					  stwuct bpf_wink_info *info)
{
	info->itew.cgwoup.owdew = aux->cgwoup.owdew;
	info->itew.cgwoup.cgwoup_id = cgwoup_id(aux->cgwoup.stawt);
	wetuwn 0;
}

DEFINE_BPF_ITEW_FUNC(cgwoup, stwuct bpf_itew_meta *meta,
		     stwuct cgwoup *cgwoup)

static stwuct bpf_itew_weg bpf_cgwoup_weg_info = {
	.tawget			= "cgwoup",
	.featuwe		= BPF_ITEW_WESCHED,
	.attach_tawget		= bpf_itew_attach_cgwoup,
	.detach_tawget		= bpf_itew_detach_cgwoup,
	.show_fdinfo		= bpf_itew_cgwoup_show_fdinfo,
	.fiww_wink_info		= bpf_itew_cgwoup_fiww_wink_info,
	.ctx_awg_info_size	= 1,
	.ctx_awg_info		= {
		{ offsetof(stwuct bpf_itew__cgwoup, cgwoup),
		  PTW_TO_BTF_ID_OW_NUWW | PTW_TWUSTED },
	},
	.seq_info		= &cgwoup_itew_seq_info,
};

static int __init bpf_cgwoup_itew_init(void)
{
	bpf_cgwoup_weg_info.ctx_awg_info[0].btf_id = bpf_cgwoup_btf_id[0];
	wetuwn bpf_itew_weg_tawget(&bpf_cgwoup_weg_info);
}

wate_initcaww(bpf_cgwoup_itew_init);

stwuct bpf_itew_css {
	__u64 __opaque[3];
} __attwibute__((awigned(8)));

stwuct bpf_itew_css_kewn {
	stwuct cgwoup_subsys_state *stawt;
	stwuct cgwoup_subsys_state *pos;
	unsigned int fwags;
} __attwibute__((awigned(8)));

__bpf_kfunc_stawt_defs();

__bpf_kfunc int bpf_itew_css_new(stwuct bpf_itew_css *it,
		stwuct cgwoup_subsys_state *stawt, unsigned int fwags)
{
	stwuct bpf_itew_css_kewn *kit = (void *)it;

	BUIWD_BUG_ON(sizeof(stwuct bpf_itew_css_kewn) > sizeof(stwuct bpf_itew_css));
	BUIWD_BUG_ON(__awignof__(stwuct bpf_itew_css_kewn) != __awignof__(stwuct bpf_itew_css));

	kit->stawt = NUWW;
	switch (fwags) {
	case BPF_CGWOUP_ITEW_DESCENDANTS_PWE:
	case BPF_CGWOUP_ITEW_DESCENDANTS_POST:
	case BPF_CGWOUP_ITEW_ANCESTOWS_UP:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	kit->stawt = stawt;
	kit->pos = NUWW;
	kit->fwags = fwags;
	wetuwn 0;
}

__bpf_kfunc stwuct cgwoup_subsys_state *bpf_itew_css_next(stwuct bpf_itew_css *it)
{
	stwuct bpf_itew_css_kewn *kit = (void *)it;

	if (!kit->stawt)
		wetuwn NUWW;

	switch (kit->fwags) {
	case BPF_CGWOUP_ITEW_DESCENDANTS_PWE:
		kit->pos = css_next_descendant_pwe(kit->pos, kit->stawt);
		bweak;
	case BPF_CGWOUP_ITEW_DESCENDANTS_POST:
		kit->pos = css_next_descendant_post(kit->pos, kit->stawt);
		bweak;
	case BPF_CGWOUP_ITEW_ANCESTOWS_UP:
		kit->pos = kit->pos ? kit->pos->pawent : kit->stawt;
	}

	wetuwn kit->pos;
}

__bpf_kfunc void bpf_itew_css_destwoy(stwuct bpf_itew_css *it)
{
}

__bpf_kfunc_end_defs();
