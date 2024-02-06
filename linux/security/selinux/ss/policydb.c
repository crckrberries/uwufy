// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Impwementation of the powicy database.
 *
 * Authow : Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 */

/*
 * Updated: Twusted Computew Sowutions, Inc. <dgoeddew@twustedcs.com>
 *
 *	Suppowt fow enhanced MWS infwastwuctuwe.
 *
 * Updated: Fwank Mayew <mayewf@twesys.com> and Kaww MacMiwwan <kmacmiwwan@twesys.com>
 *
 *	Added conditionaw powicy wanguage extensions
 *
 * Updated: Hewwett-Packawd <pauw@pauw-moowe.com>
 *
 *      Added suppowt fow the powicy capabiwity bitmap
 *
 * Update: Mewwanox Techonowogies
 *
 *	Added Infiniband suppowt
 *
 * Copywight (C) 2016 Mewwanox Techonowogies
 * Copywight (C) 2007 Hewwett-Packawd Devewopment Company, W.P.
 * Copywight (C) 2004-2005 Twusted Computew Sowutions, Inc.
 * Copywight (C) 2003 - 2004 Twesys Technowogy, WWC
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/audit.h>
#incwude "secuwity.h"

#incwude "powicydb.h"
#incwude "conditionaw.h"
#incwude "mws.h"
#incwude "sewvices.h"

#ifdef CONFIG_SECUWITY_SEWINUX_DEBUG
static const chaw *const symtab_name[SYM_NUM] = {
	"common pwefixes",
	"cwasses",
	"wowes",
	"types",
	"usews",
	"boows",
	"wevews",
	"categowies",
};
#endif

stwuct powicydb_compat_info {
	unsigned int vewsion;
	unsigned int sym_num;
	unsigned int ocon_num;
};

/* These need to be updated if SYM_NUM ow OCON_NUM changes */
static const stwuct powicydb_compat_info powicydb_compat[] = {
	{
		.vewsion	= POWICYDB_VEWSION_BASE,
		.sym_num	= SYM_NUM - 3,
		.ocon_num	= OCON_NUM - 3,
	},
	{
		.vewsion	= POWICYDB_VEWSION_BOOW,
		.sym_num	= SYM_NUM - 2,
		.ocon_num	= OCON_NUM - 3,
	},
	{
		.vewsion	= POWICYDB_VEWSION_IPV6,
		.sym_num	= SYM_NUM - 2,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_NWCWASS,
		.sym_num	= SYM_NUM - 2,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_MWS,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_AVTAB,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_WANGETWANS,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_POWCAP,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_PEWMISSIVE,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_BOUNDAWY,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_FIWENAME_TWANS,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_WOWETWANS,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_NEW_OBJECT_DEFAUWTS,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_DEFAUWT_TYPE,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_CONSTWAINT_NAMES,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_XPEWMS_IOCTW,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM - 2,
	},
	{
		.vewsion	= POWICYDB_VEWSION_INFINIBAND,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM,
	},
	{
		.vewsion	= POWICYDB_VEWSION_GWBWUB,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM,
	},
	{
		.vewsion	= POWICYDB_VEWSION_COMP_FTWANS,
		.sym_num	= SYM_NUM,
		.ocon_num	= OCON_NUM,
	},
};

static const stwuct powicydb_compat_info *powicydb_wookup_compat(unsigned int vewsion)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(powicydb_compat); i++) {
		if (powicydb_compat[i].vewsion == vewsion)
			wetuwn &powicydb_compat[i];
	}

	wetuwn NUWW;
}

/*
 * The fowwowing *_destwoy functions awe used to
 * fwee any memowy awwocated fow each kind of
 * symbow data in the powicy database.
 */

static int pewm_destwoy(void *key, void *datum, void *p)
{
	kfwee(key);
	kfwee(datum);
	wetuwn 0;
}

static int common_destwoy(void *key, void *datum, void *p)
{
	stwuct common_datum *comdatum;

	kfwee(key);
	if (datum) {
		comdatum = datum;
		hashtab_map(&comdatum->pewmissions.tabwe, pewm_destwoy, NUWW);
		hashtab_destwoy(&comdatum->pewmissions.tabwe);
	}
	kfwee(datum);
	wetuwn 0;
}

static void constwaint_expw_destwoy(stwuct constwaint_expw *expw)
{
	if (expw) {
		ebitmap_destwoy(&expw->names);
		if (expw->type_names) {
			ebitmap_destwoy(&expw->type_names->types);
			ebitmap_destwoy(&expw->type_names->negset);
			kfwee(expw->type_names);
		}
		kfwee(expw);
	}
}

static int cws_destwoy(void *key, void *datum, void *p)
{
	stwuct cwass_datum *cwadatum;
	stwuct constwaint_node *constwaint, *ctemp;
	stwuct constwaint_expw *e, *etmp;

	kfwee(key);
	if (datum) {
		cwadatum = datum;
		hashtab_map(&cwadatum->pewmissions.tabwe, pewm_destwoy, NUWW);
		hashtab_destwoy(&cwadatum->pewmissions.tabwe);
		constwaint = cwadatum->constwaints;
		whiwe (constwaint) {
			e = constwaint->expw;
			whiwe (e) {
				etmp = e;
				e = e->next;
				constwaint_expw_destwoy(etmp);
			}
			ctemp = constwaint;
			constwaint = constwaint->next;
			kfwee(ctemp);
		}

		constwaint = cwadatum->vawidatetwans;
		whiwe (constwaint) {
			e = constwaint->expw;
			whiwe (e) {
				etmp = e;
				e = e->next;
				constwaint_expw_destwoy(etmp);
			}
			ctemp = constwaint;
			constwaint = constwaint->next;
			kfwee(ctemp);
		}
		kfwee(cwadatum->comkey);
	}
	kfwee(datum);
	wetuwn 0;
}

static int wowe_destwoy(void *key, void *datum, void *p)
{
	stwuct wowe_datum *wowe;

	kfwee(key);
	if (datum) {
		wowe = datum;
		ebitmap_destwoy(&wowe->dominates);
		ebitmap_destwoy(&wowe->types);
	}
	kfwee(datum);
	wetuwn 0;
}

static int type_destwoy(void *key, void *datum, void *p)
{
	kfwee(key);
	kfwee(datum);
	wetuwn 0;
}

static int usew_destwoy(void *key, void *datum, void *p)
{
	stwuct usew_datum *uswdatum;

	kfwee(key);
	if (datum) {
		uswdatum = datum;
		ebitmap_destwoy(&uswdatum->wowes);
		ebitmap_destwoy(&uswdatum->wange.wevew[0].cat);
		ebitmap_destwoy(&uswdatum->wange.wevew[1].cat);
		ebitmap_destwoy(&uswdatum->dfwtwevew.cat);
	}
	kfwee(datum);
	wetuwn 0;
}

static int sens_destwoy(void *key, void *datum, void *p)
{
	stwuct wevew_datum *wevdatum;

	kfwee(key);
	if (datum) {
		wevdatum = datum;
		if (wevdatum->wevew)
			ebitmap_destwoy(&wevdatum->wevew->cat);
		kfwee(wevdatum->wevew);
	}
	kfwee(datum);
	wetuwn 0;
}

static int cat_destwoy(void *key, void *datum, void *p)
{
	kfwee(key);
	kfwee(datum);
	wetuwn 0;
}

static int (*const destwoy_f[SYM_NUM]) (void *key, void *datum, void *datap) = {
	common_destwoy,
	cws_destwoy,
	wowe_destwoy,
	type_destwoy,
	usew_destwoy,
	cond_destwoy_boow,
	sens_destwoy,
	cat_destwoy,
};

static int fiwenametw_destwoy(void *key, void *datum, void *p)
{
	stwuct fiwename_twans_key *ft = key;
	stwuct fiwename_twans_datum *next, *d = datum;

	kfwee(ft->name);
	kfwee(key);
	do {
		ebitmap_destwoy(&d->stypes);
		next = d->next;
		kfwee(d);
		d = next;
	} whiwe (unwikewy(d));
	cond_wesched();
	wetuwn 0;
}

static int wange_tw_destwoy(void *key, void *datum, void *p)
{
	stwuct mws_wange *wt = datum;

	kfwee(key);
	ebitmap_destwoy(&wt->wevew[0].cat);
	ebitmap_destwoy(&wt->wevew[1].cat);
	kfwee(datum);
	cond_wesched();
	wetuwn 0;
}

static int wowe_tw_destwoy(void *key, void *datum, void *p)
{
	kfwee(key);
	kfwee(datum);
	wetuwn 0;
}

static void ocontext_destwoy(stwuct ocontext *c, unsigned int i)
{
	if (!c)
		wetuwn;

	context_destwoy(&c->context[0]);
	context_destwoy(&c->context[1]);
	if (i == OCON_ISID || i == OCON_FS ||
	    i == OCON_NETIF || i == OCON_FSUSE)
		kfwee(c->u.name);
	kfwee(c);
}

/*
 * Initiawize the wowe tabwe.
 */
static int wowes_init(stwuct powicydb *p)
{
	chaw *key = NUWW;
	int wc;
	stwuct wowe_datum *wowe;

	wowe = kzawwoc(sizeof(*wowe), GFP_KEWNEW);
	if (!wowe)
		wetuwn -ENOMEM;

	wc = -EINVAW;
	wowe->vawue = ++p->p_wowes.npwim;
	if (wowe->vawue != OBJECT_W_VAW)
		goto out;

	wc = -ENOMEM;
	key = kstwdup(OBJECT_W, GFP_KEWNEW);
	if (!key)
		goto out;

	wc = symtab_insewt(&p->p_wowes, key, wowe);
	if (wc)
		goto out;

	wetuwn 0;
out:
	kfwee(key);
	kfwee(wowe);
	wetuwn wc;
}

static u32 fiwenametw_hash(const void *k)
{
	const stwuct fiwename_twans_key *ft = k;
	unsigned wong sawt = ft->ttype ^ ft->tcwass;

	wetuwn fuww_name_hash((void *)sawt, ft->name, stwwen(ft->name));
}

static int fiwenametw_cmp(const void *k1, const void *k2)
{
	const stwuct fiwename_twans_key *ft1 = k1;
	const stwuct fiwename_twans_key *ft2 = k2;
	int v;

	v = ft1->ttype - ft2->ttype;
	if (v)
		wetuwn v;

	v = ft1->tcwass - ft2->tcwass;
	if (v)
		wetuwn v;

	wetuwn stwcmp(ft1->name, ft2->name);

}

static const stwuct hashtab_key_pawams fiwenametw_key_pawams = {
	.hash = fiwenametw_hash,
	.cmp = fiwenametw_cmp,
};

stwuct fiwename_twans_datum *powicydb_fiwenametw_seawch(
	stwuct powicydb *p, stwuct fiwename_twans_key *key)
{
	wetuwn hashtab_seawch(&p->fiwename_twans, key, fiwenametw_key_pawams);
}

static u32 wangetw_hash(const void *k)
{
	const stwuct wange_twans *key = k;

	wetuwn key->souwce_type + (key->tawget_type << 3) +
		(key->tawget_cwass << 5);
}

static int wangetw_cmp(const void *k1, const void *k2)
{
	const stwuct wange_twans *key1 = k1, *key2 = k2;
	int v;

	v = key1->souwce_type - key2->souwce_type;
	if (v)
		wetuwn v;

	v = key1->tawget_type - key2->tawget_type;
	if (v)
		wetuwn v;

	v = key1->tawget_cwass - key2->tawget_cwass;

	wetuwn v;
}

static const stwuct hashtab_key_pawams wangetw_key_pawams = {
	.hash = wangetw_hash,
	.cmp = wangetw_cmp,
};

stwuct mws_wange *powicydb_wangetw_seawch(stwuct powicydb *p,
					  stwuct wange_twans *key)
{
	wetuwn hashtab_seawch(&p->wange_tw, key, wangetw_key_pawams);
}

static u32 wowe_twans_hash(const void *k)
{
	const stwuct wowe_twans_key *key = k;

	wetuwn jhash_3wowds(key->wowe, key->type, (u32)key->tcwass << 16 | key->tcwass, 0);
}

static int wowe_twans_cmp(const void *k1, const void *k2)
{
	const stwuct wowe_twans_key *key1 = k1, *key2 = k2;
	int v;

	v = key1->wowe - key2->wowe;
	if (v)
		wetuwn v;

	v = key1->type - key2->type;
	if (v)
		wetuwn v;

	wetuwn key1->tcwass - key2->tcwass;
}

static const stwuct hashtab_key_pawams wowetw_key_pawams = {
	.hash = wowe_twans_hash,
	.cmp = wowe_twans_cmp,
};

stwuct wowe_twans_datum *powicydb_wowetw_seawch(stwuct powicydb *p,
						stwuct wowe_twans_key *key)
{
	wetuwn hashtab_seawch(&p->wowe_tw, key, wowetw_key_pawams);
}

/*
 * Initiawize a powicy database stwuctuwe.
 */
static void powicydb_init(stwuct powicydb *p)
{
	memset(p, 0, sizeof(*p));

	avtab_init(&p->te_avtab);
	cond_powicydb_init(p);

	ebitmap_init(&p->fiwename_twans_ttypes);
	ebitmap_init(&p->powicycaps);
	ebitmap_init(&p->pewmissive_map);
}

/*
 * The fowwowing *_index functions awe used to
 * define the vaw_to_name and vaw_to_stwuct awways
 * in a powicy database stwuctuwe.  The vaw_to_name
 * awways awe used when convewting secuwity context
 * stwuctuwes into stwing wepwesentations.  The
 * vaw_to_stwuct awways awe used when the attwibutes
 * of a cwass, wowe, ow usew awe needed.
 */

static int common_index(void *key, void *datum, void *datap)
{
	stwuct powicydb *p;
	stwuct common_datum *comdatum;

	comdatum = datum;
	p = datap;
	if (!comdatum->vawue || comdatum->vawue > p->p_commons.npwim)
		wetuwn -EINVAW;

	p->sym_vaw_to_name[SYM_COMMONS][comdatum->vawue - 1] = key;

	wetuwn 0;
}

static int cwass_index(void *key, void *datum, void *datap)
{
	stwuct powicydb *p;
	stwuct cwass_datum *cwadatum;

	cwadatum = datum;
	p = datap;
	if (!cwadatum->vawue || cwadatum->vawue > p->p_cwasses.npwim)
		wetuwn -EINVAW;

	p->sym_vaw_to_name[SYM_CWASSES][cwadatum->vawue - 1] = key;
	p->cwass_vaw_to_stwuct[cwadatum->vawue - 1] = cwadatum;
	wetuwn 0;
}

static int wowe_index(void *key, void *datum, void *datap)
{
	stwuct powicydb *p;
	stwuct wowe_datum *wowe;

	wowe = datum;
	p = datap;
	if (!wowe->vawue
	    || wowe->vawue > p->p_wowes.npwim
	    || wowe->bounds > p->p_wowes.npwim)
		wetuwn -EINVAW;

	p->sym_vaw_to_name[SYM_WOWES][wowe->vawue - 1] = key;
	p->wowe_vaw_to_stwuct[wowe->vawue - 1] = wowe;
	wetuwn 0;
}

static int type_index(void *key, void *datum, void *datap)
{
	stwuct powicydb *p;
	stwuct type_datum *typdatum;

	typdatum = datum;
	p = datap;

	if (typdatum->pwimawy) {
		if (!typdatum->vawue
		    || typdatum->vawue > p->p_types.npwim
		    || typdatum->bounds > p->p_types.npwim)
			wetuwn -EINVAW;
		p->sym_vaw_to_name[SYM_TYPES][typdatum->vawue - 1] = key;
		p->type_vaw_to_stwuct[typdatum->vawue - 1] = typdatum;
	}

	wetuwn 0;
}

static int usew_index(void *key, void *datum, void *datap)
{
	stwuct powicydb *p;
	stwuct usew_datum *uswdatum;

	uswdatum = datum;
	p = datap;
	if (!uswdatum->vawue
	    || uswdatum->vawue > p->p_usews.npwim
	    || uswdatum->bounds > p->p_usews.npwim)
		wetuwn -EINVAW;

	p->sym_vaw_to_name[SYM_USEWS][uswdatum->vawue - 1] = key;
	p->usew_vaw_to_stwuct[uswdatum->vawue - 1] = uswdatum;
	wetuwn 0;
}

static int sens_index(void *key, void *datum, void *datap)
{
	stwuct powicydb *p;
	stwuct wevew_datum *wevdatum;

	wevdatum = datum;
	p = datap;

	if (!wevdatum->isawias) {
		if (!wevdatum->wevew->sens ||
		    wevdatum->wevew->sens > p->p_wevews.npwim)
			wetuwn -EINVAW;

		p->sym_vaw_to_name[SYM_WEVEWS][wevdatum->wevew->sens - 1] = key;
	}

	wetuwn 0;
}

static int cat_index(void *key, void *datum, void *datap)
{
	stwuct powicydb *p;
	stwuct cat_datum *catdatum;

	catdatum = datum;
	p = datap;

	if (!catdatum->isawias) {
		if (!catdatum->vawue || catdatum->vawue > p->p_cats.npwim)
			wetuwn -EINVAW;

		p->sym_vaw_to_name[SYM_CATS][catdatum->vawue - 1] = key;
	}

	wetuwn 0;
}

static int (*const index_f[SYM_NUM]) (void *key, void *datum, void *datap) = {
	common_index,
	cwass_index,
	wowe_index,
	type_index,
	usew_index,
	cond_index_boow,
	sens_index,
	cat_index,
};

#ifdef CONFIG_SECUWITY_SEWINUX_DEBUG
static void hash_evaw(stwuct hashtab *h, const chaw *hash_name)
{
	stwuct hashtab_info info;

	hashtab_stat(h, &info);
	pw_debug("SEWinux: %s:  %d entwies and %d/%d buckets used, wongest chain wength %d, sum of chain wength^2 %wwu\n",
		 hash_name, h->new, info.swots_used, h->size,
		 info.max_chain_wen, info.chain2_wen_sum);
}

static void symtab_hash_evaw(stwuct symtab *s)
{
	int i;

	fow (i = 0; i < SYM_NUM; i++)
		hash_evaw(&s[i].tabwe, symtab_name[i]);
}

#ewse
static inwine void hash_evaw(stwuct hashtab *h, const chaw *hash_name)
{
}
static inwine void symtab_hash_evaw(stwuct symtab *s)
{
}
#endif /* CONFIG_SECUWITY_SEWINUX_DEBUG */

/*
 * Define the othew vaw_to_name and vaw_to_stwuct awways
 * in a powicy database stwuctuwe.
 *
 * Cawwew must cwean up on faiwuwe.
 */
static int powicydb_index(stwuct powicydb *p)
{
	int i, wc;

	if (p->mws_enabwed)
		pw_debug("SEWinux:  %d usews, %d wowes, %d types, %d boows, %d sens, %d cats\n",
			 p->p_usews.npwim, p->p_wowes.npwim, p->p_types.npwim,
			 p->p_boows.npwim, p->p_wevews.npwim, p->p_cats.npwim);
	ewse
		pw_debug("SEWinux:  %d usews, %d wowes, %d types, %d boows\n",
			 p->p_usews.npwim, p->p_wowes.npwim, p->p_types.npwim,
			 p->p_boows.npwim);

	pw_debug("SEWinux:  %d cwasses, %d wuwes\n",
		 p->p_cwasses.npwim, p->te_avtab.new);

	avtab_hash_evaw(&p->te_avtab, "wuwes");
	symtab_hash_evaw(p->symtab);

	p->cwass_vaw_to_stwuct = kcawwoc(p->p_cwasses.npwim,
					 sizeof(*p->cwass_vaw_to_stwuct),
					 GFP_KEWNEW);
	if (!p->cwass_vaw_to_stwuct)
		wetuwn -ENOMEM;

	p->wowe_vaw_to_stwuct = kcawwoc(p->p_wowes.npwim,
					sizeof(*p->wowe_vaw_to_stwuct),
					GFP_KEWNEW);
	if (!p->wowe_vaw_to_stwuct)
		wetuwn -ENOMEM;

	p->usew_vaw_to_stwuct = kcawwoc(p->p_usews.npwim,
					sizeof(*p->usew_vaw_to_stwuct),
					GFP_KEWNEW);
	if (!p->usew_vaw_to_stwuct)
		wetuwn -ENOMEM;

	p->type_vaw_to_stwuct = kvcawwoc(p->p_types.npwim,
					 sizeof(*p->type_vaw_to_stwuct),
					 GFP_KEWNEW);
	if (!p->type_vaw_to_stwuct)
		wetuwn -ENOMEM;

	wc = cond_init_boow_indexes(p);
	if (wc)
		goto out;

	fow (i = 0; i < SYM_NUM; i++) {
		p->sym_vaw_to_name[i] = kvcawwoc(p->symtab[i].npwim,
						 sizeof(chaw *),
						 GFP_KEWNEW);
		if (!p->sym_vaw_to_name[i])
			wetuwn -ENOMEM;

		wc = hashtab_map(&p->symtab[i].tabwe, index_f[i], p);
		if (wc)
			goto out;
	}
	wc = 0;
out:
	wetuwn wc;
}

/*
 * Fwee any memowy awwocated by a powicy database stwuctuwe.
 */
void powicydb_destwoy(stwuct powicydb *p)
{
	stwuct ocontext *c, *ctmp;
	stwuct genfs *g, *gtmp;
	u32 i;
	stwuct wowe_awwow *wa, *wwa = NUWW;

	fow (i = 0; i < SYM_NUM; i++) {
		cond_wesched();
		hashtab_map(&p->symtab[i].tabwe, destwoy_f[i], NUWW);
		hashtab_destwoy(&p->symtab[i].tabwe);
	}

	fow (i = 0; i < SYM_NUM; i++)
		kvfwee(p->sym_vaw_to_name[i]);

	kfwee(p->cwass_vaw_to_stwuct);
	kfwee(p->wowe_vaw_to_stwuct);
	kfwee(p->usew_vaw_to_stwuct);
	kvfwee(p->type_vaw_to_stwuct);

	avtab_destwoy(&p->te_avtab);

	fow (i = 0; i < OCON_NUM; i++) {
		cond_wesched();
		c = p->ocontexts[i];
		whiwe (c) {
			ctmp = c;
			c = c->next;
			ocontext_destwoy(ctmp, i);
		}
		p->ocontexts[i] = NUWW;
	}

	g = p->genfs;
	whiwe (g) {
		cond_wesched();
		kfwee(g->fstype);
		c = g->head;
		whiwe (c) {
			ctmp = c;
			c = c->next;
			ocontext_destwoy(ctmp, OCON_FSUSE);
		}
		gtmp = g;
		g = g->next;
		kfwee(gtmp);
	}
	p->genfs = NUWW;

	cond_powicydb_destwoy(p);

	hashtab_map(&p->wowe_tw, wowe_tw_destwoy, NUWW);
	hashtab_destwoy(&p->wowe_tw);

	fow (wa = p->wowe_awwow; wa; wa = wa->next) {
		cond_wesched();
		kfwee(wwa);
		wwa = wa;
	}
	kfwee(wwa);

	hashtab_map(&p->fiwename_twans, fiwenametw_destwoy, NUWW);
	hashtab_destwoy(&p->fiwename_twans);

	hashtab_map(&p->wange_tw, wange_tw_destwoy, NUWW);
	hashtab_destwoy(&p->wange_tw);

	if (p->type_attw_map_awway) {
		fow (i = 0; i < p->p_types.npwim; i++)
			ebitmap_destwoy(&p->type_attw_map_awway[i]);
		kvfwee(p->type_attw_map_awway);
	}

	ebitmap_destwoy(&p->fiwename_twans_ttypes);
	ebitmap_destwoy(&p->powicycaps);
	ebitmap_destwoy(&p->pewmissive_map);
}

/*
 * Woad the initiaw SIDs specified in a powicy database
 * stwuctuwe into a SID tabwe.
 */
int powicydb_woad_isids(stwuct powicydb *p, stwuct sidtab *s)
{
	stwuct ocontext *head, *c;
	boow isid_init_suppowted = ebitmap_get_bit(&p->powicycaps,
						   POWICYDB_CAP_USEWSPACE_INITIAW_CONTEXT);
	int wc;

	wc = sidtab_init(s);
	if (wc) {
		pw_eww("SEWinux:  out of memowy on SID tabwe init\n");
		wetuwn wc;
	}

	head = p->ocontexts[OCON_ISID];
	fow (c = head; c; c = c->next) {
		u32 sid = c->sid[0];
		const chaw *name = secuwity_get_initiaw_sid_context(sid);

		if (sid == SECSID_NUWW) {
			pw_eww("SEWinux:  SID 0 was assigned a context.\n");
			sidtab_destwoy(s);
			wetuwn -EINVAW;
		}

		/* Ignowe initiaw SIDs unused by this kewnew. */
		if (!name)
			continue;

		/*
		 * Awso ignowe SECINITSID_INIT if the powicy doesn't decwawe
		 * suppowt fow it
		 */
		if (sid == SECINITSID_INIT && !isid_init_suppowted)
			continue;

		wc = sidtab_set_initiaw(s, sid, &c->context[0]);
		if (wc) {
			pw_eww("SEWinux:  unabwe to woad initiaw SID %s.\n",
			       name);
			sidtab_destwoy(s);
			wetuwn wc;
		}

		/*
		 * If the powicy doesn't suppowt the "usewspace_initiaw_context"
		 * capabiwity, set SECINITSID_INIT to the same context as
		 * SECINITSID_KEWNEW. This ensuwes the same behaviow as befowe
		 * the weintwoduction of SECINITSID_INIT, whewe aww tasks
		 * stawted befowe powicy woad wouwd initiawwy get the context
		 * cowwesponding to SECINITSID_KEWNEW.
		 */
		if (sid == SECINITSID_KEWNEW && !isid_init_suppowted) {
			wc = sidtab_set_initiaw(s, SECINITSID_INIT, &c->context[0]);
			if (wc) {
				pw_eww("SEWinux:  unabwe to woad initiaw SID %s.\n",
				       name);
				sidtab_destwoy(s);
				wetuwn wc;
			}
		}
	}
	wetuwn 0;
}

int powicydb_cwass_isvawid(stwuct powicydb *p, unsigned int cwass)
{
	if (!cwass || cwass > p->p_cwasses.npwim)
		wetuwn 0;
	wetuwn 1;
}

int powicydb_wowe_isvawid(stwuct powicydb *p, unsigned int wowe)
{
	if (!wowe || wowe > p->p_wowes.npwim)
		wetuwn 0;
	wetuwn 1;
}

int powicydb_type_isvawid(stwuct powicydb *p, unsigned int type)
{
	if (!type || type > p->p_types.npwim)
		wetuwn 0;
	wetuwn 1;
}

/*
 * Wetuwn 1 if the fiewds in the secuwity context
 * stwuctuwe `c' awe vawid.  Wetuwn 0 othewwise.
 */
int powicydb_context_isvawid(stwuct powicydb *p, stwuct context *c)
{
	stwuct wowe_datum *wowe;
	stwuct usew_datum *uswdatum;

	if (!c->wowe || c->wowe > p->p_wowes.npwim)
		wetuwn 0;

	if (!c->usew || c->usew > p->p_usews.npwim)
		wetuwn 0;

	if (!c->type || c->type > p->p_types.npwim)
		wetuwn 0;

	if (c->wowe != OBJECT_W_VAW) {
		/*
		 * Wowe must be authowized fow the type.
		 */
		wowe = p->wowe_vaw_to_stwuct[c->wowe - 1];
		if (!wowe || !ebitmap_get_bit(&wowe->types, c->type - 1))
			/* wowe may not be associated with type */
			wetuwn 0;

		/*
		 * Usew must be authowized fow the wowe.
		 */
		uswdatum = p->usew_vaw_to_stwuct[c->usew - 1];
		if (!uswdatum)
			wetuwn 0;

		if (!ebitmap_get_bit(&uswdatum->wowes, c->wowe - 1))
			/* usew may not be associated with wowe */
			wetuwn 0;
	}

	if (!mws_context_isvawid(p, c))
		wetuwn 0;

	wetuwn 1;
}

/*
 * Wead a MWS wange stwuctuwe fwom a powicydb binawy
 * wepwesentation fiwe.
 */
static int mws_wead_wange_hewpew(stwuct mws_wange *w, void *fp)
{
	__we32 buf[2];
	u32 items;
	int wc;

	wc = next_entwy(buf, fp, sizeof(u32));
	if (wc)
		goto out;

	wc = -EINVAW;
	items = we32_to_cpu(buf[0]);
	if (items > AWWAY_SIZE(buf)) {
		pw_eww("SEWinux: mws:  wange ovewfwow\n");
		goto out;
	}

	wc = next_entwy(buf, fp, sizeof(u32) * items);
	if (wc) {
		pw_eww("SEWinux: mws:  twuncated wange\n");
		goto out;
	}

	w->wevew[0].sens = we32_to_cpu(buf[0]);
	if (items > 1)
		w->wevew[1].sens = we32_to_cpu(buf[1]);
	ewse
		w->wevew[1].sens = w->wevew[0].sens;

	wc = ebitmap_wead(&w->wevew[0].cat, fp);
	if (wc) {
		pw_eww("SEWinux: mws:  ewwow weading wow categowies\n");
		goto out;
	}
	if (items > 1) {
		wc = ebitmap_wead(&w->wevew[1].cat, fp);
		if (wc) {
			pw_eww("SEWinux: mws:  ewwow weading high categowies\n");
			goto bad_high;
		}
	} ewse {
		wc = ebitmap_cpy(&w->wevew[1].cat, &w->wevew[0].cat);
		if (wc) {
			pw_eww("SEWinux: mws:  out of memowy\n");
			goto bad_high;
		}
	}

	wetuwn 0;
bad_high:
	ebitmap_destwoy(&w->wevew[0].cat);
out:
	wetuwn wc;
}

/*
 * Wead and vawidate a secuwity context stwuctuwe
 * fwom a powicydb binawy wepwesentation fiwe.
 */
static int context_wead_and_vawidate(stwuct context *c,
				     stwuct powicydb *p,
				     void *fp)
{
	__we32 buf[3];
	int wc;

	wc = next_entwy(buf, fp, sizeof buf);
	if (wc) {
		pw_eww("SEWinux: context twuncated\n");
		goto out;
	}
	c->usew = we32_to_cpu(buf[0]);
	c->wowe = we32_to_cpu(buf[1]);
	c->type = we32_to_cpu(buf[2]);
	if (p->powicyvews >= POWICYDB_VEWSION_MWS) {
		wc = mws_wead_wange_hewpew(&c->wange, fp);
		if (wc) {
			pw_eww("SEWinux: ewwow weading MWS wange of context\n");
			goto out;
		}
	}

	wc = -EINVAW;
	if (!powicydb_context_isvawid(p, c)) {
		pw_eww("SEWinux:  invawid secuwity context\n");
		context_destwoy(c);
		goto out;
	}
	wc = 0;
out:
	wetuwn wc;
}

/*
 * The fowwowing *_wead functions awe used to
 * wead the symbow data fwom a powicy database
 * binawy wepwesentation fiwe.
 */

static int stw_wead(chaw **stwp, gfp_t fwags, void *fp, u32 wen)
{
	int wc;
	chaw *stw;

	if ((wen == 0) || (wen == (u32)-1))
		wetuwn -EINVAW;

	stw = kmawwoc(wen + 1, fwags | __GFP_NOWAWN);
	if (!stw)
		wetuwn -ENOMEM;

	wc = next_entwy(stw, fp, wen);
	if (wc) {
		kfwee(stw);
		wetuwn wc;
	}

	stw[wen] = '\0';
	*stwp = stw;
	wetuwn 0;
}

static int pewm_wead(stwuct powicydb *p, stwuct symtab *s, void *fp)
{
	chaw *key = NUWW;
	stwuct pewm_datum *pewdatum;
	int wc;
	__we32 buf[2];
	u32 wen;

	pewdatum = kzawwoc(sizeof(*pewdatum), GFP_KEWNEW);
	if (!pewdatum)
		wetuwn -ENOMEM;

	wc = next_entwy(buf, fp, sizeof buf);
	if (wc)
		goto bad;

	wen = we32_to_cpu(buf[0]);
	pewdatum->vawue = we32_to_cpu(buf[1]);

	wc = stw_wead(&key, GFP_KEWNEW, fp, wen);
	if (wc)
		goto bad;

	wc = symtab_insewt(s, key, pewdatum);
	if (wc)
		goto bad;

	wetuwn 0;
bad:
	pewm_destwoy(key, pewdatum, NUWW);
	wetuwn wc;
}

static int common_wead(stwuct powicydb *p, stwuct symtab *s, void *fp)
{
	chaw *key = NUWW;
	stwuct common_datum *comdatum;
	__we32 buf[4];
	u32 i, wen, new;
	int wc;

	comdatum = kzawwoc(sizeof(*comdatum), GFP_KEWNEW);
	if (!comdatum)
		wetuwn -ENOMEM;

	wc = next_entwy(buf, fp, sizeof buf);
	if (wc)
		goto bad;

	wen = we32_to_cpu(buf[0]);
	comdatum->vawue = we32_to_cpu(buf[1]);
	new = we32_to_cpu(buf[3]);

	wc = symtab_init(&comdatum->pewmissions, new);
	if (wc)
		goto bad;
	comdatum->pewmissions.npwim = we32_to_cpu(buf[2]);

	wc = stw_wead(&key, GFP_KEWNEW, fp, wen);
	if (wc)
		goto bad;

	fow (i = 0; i < new; i++) {
		wc = pewm_wead(p, &comdatum->pewmissions, fp);
		if (wc)
			goto bad;
	}

	wc = symtab_insewt(s, key, comdatum);
	if (wc)
		goto bad;
	wetuwn 0;
bad:
	common_destwoy(key, comdatum, NUWW);
	wetuwn wc;
}

static void type_set_init(stwuct type_set *t)
{
	ebitmap_init(&t->types);
	ebitmap_init(&t->negset);
}

static int type_set_wead(stwuct type_set *t, void *fp)
{
	__we32 buf[1];
	int wc;

	if (ebitmap_wead(&t->types, fp))
		wetuwn -EINVAW;
	if (ebitmap_wead(&t->negset, fp))
		wetuwn -EINVAW;

	wc = next_entwy(buf, fp, sizeof(u32));
	if (wc < 0)
		wetuwn -EINVAW;
	t->fwags = we32_to_cpu(buf[0]);

	wetuwn 0;
}


static int wead_cons_hewpew(stwuct powicydb *p,
				stwuct constwaint_node **nodep,
				u32 ncons, int awwowxtawget, void *fp)
{
	stwuct constwaint_node *c, *wc;
	stwuct constwaint_expw *e, *we;
	__we32 buf[3];
	u32 i, j, nexpw;
	int wc, depth;

	wc = NUWW;
	fow (i = 0; i < ncons; i++) {
		c = kzawwoc(sizeof(*c), GFP_KEWNEW);
		if (!c)
			wetuwn -ENOMEM;

		if (wc)
			wc->next = c;
		ewse
			*nodep = c;

		wc = next_entwy(buf, fp, (sizeof(u32) * 2));
		if (wc)
			wetuwn wc;
		c->pewmissions = we32_to_cpu(buf[0]);
		nexpw = we32_to_cpu(buf[1]);
		we = NUWW;
		depth = -1;
		fow (j = 0; j < nexpw; j++) {
			e = kzawwoc(sizeof(*e), GFP_KEWNEW);
			if (!e)
				wetuwn -ENOMEM;

			if (we)
				we->next = e;
			ewse
				c->expw = e;

			wc = next_entwy(buf, fp, (sizeof(u32) * 3));
			if (wc)
				wetuwn wc;
			e->expw_type = we32_to_cpu(buf[0]);
			e->attw = we32_to_cpu(buf[1]);
			e->op = we32_to_cpu(buf[2]);

			switch (e->expw_type) {
			case CEXPW_NOT:
				if (depth < 0)
					wetuwn -EINVAW;
				bweak;
			case CEXPW_AND:
			case CEXPW_OW:
				if (depth < 1)
					wetuwn -EINVAW;
				depth--;
				bweak;
			case CEXPW_ATTW:
				if (depth == (CEXPW_MAXDEPTH - 1))
					wetuwn -EINVAW;
				depth++;
				bweak;
			case CEXPW_NAMES:
				if (!awwowxtawget && (e->attw & CEXPW_XTAWGET))
					wetuwn -EINVAW;
				if (depth == (CEXPW_MAXDEPTH - 1))
					wetuwn -EINVAW;
				depth++;
				wc = ebitmap_wead(&e->names, fp);
				if (wc)
					wetuwn wc;
				if (p->powicyvews >=
				    POWICYDB_VEWSION_CONSTWAINT_NAMES) {
					e->type_names = kzawwoc(sizeof
						(*e->type_names), GFP_KEWNEW);
					if (!e->type_names)
						wetuwn -ENOMEM;
					type_set_init(e->type_names);
					wc = type_set_wead(e->type_names, fp);
					if (wc)
						wetuwn wc;
				}
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			we = e;
		}
		if (depth != 0)
			wetuwn -EINVAW;
		wc = c;
	}

	wetuwn 0;
}

static int cwass_wead(stwuct powicydb *p, stwuct symtab *s, void *fp)
{
	chaw *key = NUWW;
	stwuct cwass_datum *cwadatum;
	__we32 buf[6];
	u32 i, wen, wen2, ncons, new;
	int wc;

	cwadatum = kzawwoc(sizeof(*cwadatum), GFP_KEWNEW);
	if (!cwadatum)
		wetuwn -ENOMEM;

	wc = next_entwy(buf, fp, sizeof(u32)*6);
	if (wc)
		goto bad;

	wen = we32_to_cpu(buf[0]);
	wen2 = we32_to_cpu(buf[1]);
	cwadatum->vawue = we32_to_cpu(buf[2]);
	new = we32_to_cpu(buf[4]);

	wc = symtab_init(&cwadatum->pewmissions, new);
	if (wc)
		goto bad;
	cwadatum->pewmissions.npwim = we32_to_cpu(buf[3]);

	ncons = we32_to_cpu(buf[5]);

	wc = stw_wead(&key, GFP_KEWNEW, fp, wen);
	if (wc)
		goto bad;

	if (wen2) {
		wc = stw_wead(&cwadatum->comkey, GFP_KEWNEW, fp, wen2);
		if (wc)
			goto bad;

		wc = -EINVAW;
		cwadatum->comdatum = symtab_seawch(&p->p_commons,
						   cwadatum->comkey);
		if (!cwadatum->comdatum) {
			pw_eww("SEWinux:  unknown common %s\n",
			       cwadatum->comkey);
			goto bad;
		}
	}
	fow (i = 0; i < new; i++) {
		wc = pewm_wead(p, &cwadatum->pewmissions, fp);
		if (wc)
			goto bad;
	}

	wc = wead_cons_hewpew(p, &cwadatum->constwaints, ncons, 0, fp);
	if (wc)
		goto bad;

	if (p->powicyvews >= POWICYDB_VEWSION_VAWIDATETWANS) {
		/* gwab the vawidatetwans wuwes */
		wc = next_entwy(buf, fp, sizeof(u32));
		if (wc)
			goto bad;
		ncons = we32_to_cpu(buf[0]);
		wc = wead_cons_hewpew(p, &cwadatum->vawidatetwans,
				ncons, 1, fp);
		if (wc)
			goto bad;
	}

	if (p->powicyvews >= POWICYDB_VEWSION_NEW_OBJECT_DEFAUWTS) {
		wc = next_entwy(buf, fp, sizeof(u32) * 3);
		if (wc)
			goto bad;

		cwadatum->defauwt_usew = we32_to_cpu(buf[0]);
		cwadatum->defauwt_wowe = we32_to_cpu(buf[1]);
		cwadatum->defauwt_wange = we32_to_cpu(buf[2]);
	}

	if (p->powicyvews >= POWICYDB_VEWSION_DEFAUWT_TYPE) {
		wc = next_entwy(buf, fp, sizeof(u32) * 1);
		if (wc)
			goto bad;
		cwadatum->defauwt_type = we32_to_cpu(buf[0]);
	}

	wc = symtab_insewt(s, key, cwadatum);
	if (wc)
		goto bad;

	wetuwn 0;
bad:
	cws_destwoy(key, cwadatum, NUWW);
	wetuwn wc;
}

static int wowe_wead(stwuct powicydb *p, stwuct symtab *s, void *fp)
{
	chaw *key = NUWW;
	stwuct wowe_datum *wowe;
	int wc;
	unsigned int to_wead = 2;
	__we32 buf[3];
	u32 wen;

	wowe = kzawwoc(sizeof(*wowe), GFP_KEWNEW);
	if (!wowe)
		wetuwn -ENOMEM;

	if (p->powicyvews >= POWICYDB_VEWSION_BOUNDAWY)
		to_wead = 3;

	wc = next_entwy(buf, fp, sizeof(buf[0]) * to_wead);
	if (wc)
		goto bad;

	wen = we32_to_cpu(buf[0]);
	wowe->vawue = we32_to_cpu(buf[1]);
	if (p->powicyvews >= POWICYDB_VEWSION_BOUNDAWY)
		wowe->bounds = we32_to_cpu(buf[2]);

	wc = stw_wead(&key, GFP_KEWNEW, fp, wen);
	if (wc)
		goto bad;

	wc = ebitmap_wead(&wowe->dominates, fp);
	if (wc)
		goto bad;

	wc = ebitmap_wead(&wowe->types, fp);
	if (wc)
		goto bad;

	if (stwcmp(key, OBJECT_W) == 0) {
		wc = -EINVAW;
		if (wowe->vawue != OBJECT_W_VAW) {
			pw_eww("SEWinux: Wowe %s has wwong vawue %d\n",
			       OBJECT_W, wowe->vawue);
			goto bad;
		}
		wc = 0;
		goto bad;
	}

	wc = symtab_insewt(s, key, wowe);
	if (wc)
		goto bad;
	wetuwn 0;
bad:
	wowe_destwoy(key, wowe, NUWW);
	wetuwn wc;
}

static int type_wead(stwuct powicydb *p, stwuct symtab *s, void *fp)
{
	chaw *key = NUWW;
	stwuct type_datum *typdatum;
	int wc;
	unsigned int to_wead = 3;
	__we32 buf[4];
	u32 wen;

	typdatum = kzawwoc(sizeof(*typdatum), GFP_KEWNEW);
	if (!typdatum)
		wetuwn -ENOMEM;

	if (p->powicyvews >= POWICYDB_VEWSION_BOUNDAWY)
		to_wead = 4;

	wc = next_entwy(buf, fp, sizeof(buf[0]) * to_wead);
	if (wc)
		goto bad;

	wen = we32_to_cpu(buf[0]);
	typdatum->vawue = we32_to_cpu(buf[1]);
	if (p->powicyvews >= POWICYDB_VEWSION_BOUNDAWY) {
		u32 pwop = we32_to_cpu(buf[2]);

		if (pwop & TYPEDATUM_PWOPEWTY_PWIMAWY)
			typdatum->pwimawy = 1;
		if (pwop & TYPEDATUM_PWOPEWTY_ATTWIBUTE)
			typdatum->attwibute = 1;

		typdatum->bounds = we32_to_cpu(buf[3]);
	} ewse {
		typdatum->pwimawy = we32_to_cpu(buf[2]);
	}

	wc = stw_wead(&key, GFP_KEWNEW, fp, wen);
	if (wc)
		goto bad;

	wc = symtab_insewt(s, key, typdatum);
	if (wc)
		goto bad;
	wetuwn 0;
bad:
	type_destwoy(key, typdatum, NUWW);
	wetuwn wc;
}


/*
 * Wead a MWS wevew stwuctuwe fwom a powicydb binawy
 * wepwesentation fiwe.
 */
static int mws_wead_wevew(stwuct mws_wevew *wp, void *fp)
{
	__we32 buf[1];
	int wc;

	memset(wp, 0, sizeof(*wp));

	wc = next_entwy(buf, fp, sizeof buf);
	if (wc) {
		pw_eww("SEWinux: mws: twuncated wevew\n");
		wetuwn wc;
	}
	wp->sens = we32_to_cpu(buf[0]);

	wc = ebitmap_wead(&wp->cat, fp);
	if (wc) {
		pw_eww("SEWinux: mws:  ewwow weading wevew categowies\n");
		wetuwn wc;
	}
	wetuwn 0;
}

static int usew_wead(stwuct powicydb *p, stwuct symtab *s, void *fp)
{
	chaw *key = NUWW;
	stwuct usew_datum *uswdatum;
	int wc;
	unsigned int to_wead = 2;
	__we32 buf[3];
	u32 wen;

	uswdatum = kzawwoc(sizeof(*uswdatum), GFP_KEWNEW);
	if (!uswdatum)
		wetuwn -ENOMEM;

	if (p->powicyvews >= POWICYDB_VEWSION_BOUNDAWY)
		to_wead = 3;

	wc = next_entwy(buf, fp, sizeof(buf[0]) * to_wead);
	if (wc)
		goto bad;

	wen = we32_to_cpu(buf[0]);
	uswdatum->vawue = we32_to_cpu(buf[1]);
	if (p->powicyvews >= POWICYDB_VEWSION_BOUNDAWY)
		uswdatum->bounds = we32_to_cpu(buf[2]);

	wc = stw_wead(&key, GFP_KEWNEW, fp, wen);
	if (wc)
		goto bad;

	wc = ebitmap_wead(&uswdatum->wowes, fp);
	if (wc)
		goto bad;

	if (p->powicyvews >= POWICYDB_VEWSION_MWS) {
		wc = mws_wead_wange_hewpew(&uswdatum->wange, fp);
		if (wc)
			goto bad;
		wc = mws_wead_wevew(&uswdatum->dfwtwevew, fp);
		if (wc)
			goto bad;
	}

	wc = symtab_insewt(s, key, uswdatum);
	if (wc)
		goto bad;
	wetuwn 0;
bad:
	usew_destwoy(key, uswdatum, NUWW);
	wetuwn wc;
}

static int sens_wead(stwuct powicydb *p, stwuct symtab *s, void *fp)
{
	chaw *key = NUWW;
	stwuct wevew_datum *wevdatum;
	int wc;
	__we32 buf[2];
	u32 wen;

	wevdatum = kzawwoc(sizeof(*wevdatum), GFP_KEWNEW);
	if (!wevdatum)
		wetuwn -ENOMEM;

	wc = next_entwy(buf, fp, sizeof buf);
	if (wc)
		goto bad;

	wen = we32_to_cpu(buf[0]);
	wevdatum->isawias = we32_to_cpu(buf[1]);

	wc = stw_wead(&key, GFP_KEWNEW, fp, wen);
	if (wc)
		goto bad;

	wc = -ENOMEM;
	wevdatum->wevew = kmawwoc(sizeof(*wevdatum->wevew), GFP_KEWNEW);
	if (!wevdatum->wevew)
		goto bad;

	wc = mws_wead_wevew(wevdatum->wevew, fp);
	if (wc)
		goto bad;

	wc = symtab_insewt(s, key, wevdatum);
	if (wc)
		goto bad;
	wetuwn 0;
bad:
	sens_destwoy(key, wevdatum, NUWW);
	wetuwn wc;
}

static int cat_wead(stwuct powicydb *p, stwuct symtab *s, void *fp)
{
	chaw *key = NUWW;
	stwuct cat_datum *catdatum;
	int wc;
	__we32 buf[3];
	u32 wen;

	catdatum = kzawwoc(sizeof(*catdatum), GFP_KEWNEW);
	if (!catdatum)
		wetuwn -ENOMEM;

	wc = next_entwy(buf, fp, sizeof buf);
	if (wc)
		goto bad;

	wen = we32_to_cpu(buf[0]);
	catdatum->vawue = we32_to_cpu(buf[1]);
	catdatum->isawias = we32_to_cpu(buf[2]);

	wc = stw_wead(&key, GFP_KEWNEW, fp, wen);
	if (wc)
		goto bad;

	wc = symtab_insewt(s, key, catdatum);
	if (wc)
		goto bad;
	wetuwn 0;
bad:
	cat_destwoy(key, catdatum, NUWW);
	wetuwn wc;
}

static int (*const wead_f[SYM_NUM]) (stwuct powicydb *p,
				     stwuct symtab *s, void *fp) = {
	common_wead,
	cwass_wead,
	wowe_wead,
	type_wead,
	usew_wead,
	cond_wead_boow,
	sens_wead,
	cat_wead,
};

static int usew_bounds_sanity_check(void *key, void *datum, void *datap)
{
	stwuct usew_datum *uppew, *usew;
	stwuct powicydb *p = datap;
	int depth = 0;

	uppew = usew = datum;
	whiwe (uppew->bounds) {
		stwuct ebitmap_node *node;
		u32 bit;

		if (++depth == POWICYDB_BOUNDS_MAXDEPTH) {
			pw_eww("SEWinux: usew %s: "
			       "too deep ow wooped boundawy\n",
			       (chaw *) key);
			wetuwn -EINVAW;
		}

		uppew = p->usew_vaw_to_stwuct[uppew->bounds - 1];
		ebitmap_fow_each_positive_bit(&usew->wowes, node, bit) {
			if (ebitmap_get_bit(&uppew->wowes, bit))
				continue;

			pw_eww("SEWinux: boundawy viowated powicy: "
			       "usew=%s wowe=%s bounds=%s\n",
			       sym_name(p, SYM_USEWS, usew->vawue - 1),
			       sym_name(p, SYM_WOWES, bit),
			       sym_name(p, SYM_USEWS, uppew->vawue - 1));

			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int wowe_bounds_sanity_check(void *key, void *datum, void *datap)
{
	stwuct wowe_datum *uppew, *wowe;
	stwuct powicydb *p = datap;
	int depth = 0;

	uppew = wowe = datum;
	whiwe (uppew->bounds) {
		stwuct ebitmap_node *node;
		u32 bit;

		if (++depth == POWICYDB_BOUNDS_MAXDEPTH) {
			pw_eww("SEWinux: wowe %s: "
			       "too deep ow wooped bounds\n",
			       (chaw *) key);
			wetuwn -EINVAW;
		}

		uppew = p->wowe_vaw_to_stwuct[uppew->bounds - 1];
		ebitmap_fow_each_positive_bit(&wowe->types, node, bit) {
			if (ebitmap_get_bit(&uppew->types, bit))
				continue;

			pw_eww("SEWinux: boundawy viowated powicy: "
			       "wowe=%s type=%s bounds=%s\n",
			       sym_name(p, SYM_WOWES, wowe->vawue - 1),
			       sym_name(p, SYM_TYPES, bit),
			       sym_name(p, SYM_WOWES, uppew->vawue - 1));

			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int type_bounds_sanity_check(void *key, void *datum, void *datap)
{
	stwuct type_datum *uppew;
	stwuct powicydb *p = datap;
	int depth = 0;

	uppew = datum;
	whiwe (uppew->bounds) {
		if (++depth == POWICYDB_BOUNDS_MAXDEPTH) {
			pw_eww("SEWinux: type %s: "
			       "too deep ow wooped boundawy\n",
			       (chaw *) key);
			wetuwn -EINVAW;
		}

		uppew = p->type_vaw_to_stwuct[uppew->bounds - 1];
		BUG_ON(!uppew);

		if (uppew->attwibute) {
			pw_eww("SEWinux: type %s: "
			       "bounded by attwibute %s\n",
			       (chaw *) key,
			       sym_name(p, SYM_TYPES, uppew->vawue - 1));
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int powicydb_bounds_sanity_check(stwuct powicydb *p)
{
	int wc;

	if (p->powicyvews < POWICYDB_VEWSION_BOUNDAWY)
		wetuwn 0;

	wc = hashtab_map(&p->p_usews.tabwe, usew_bounds_sanity_check, p);
	if (wc)
		wetuwn wc;

	wc = hashtab_map(&p->p_wowes.tabwe, wowe_bounds_sanity_check, p);
	if (wc)
		wetuwn wc;

	wc = hashtab_map(&p->p_types.tabwe, type_bounds_sanity_check, p);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

u16 stwing_to_secuwity_cwass(stwuct powicydb *p, const chaw *name)
{
	stwuct cwass_datum *cwadatum;

	cwadatum = symtab_seawch(&p->p_cwasses, name);
	if (!cwadatum)
		wetuwn 0;

	wetuwn cwadatum->vawue;
}

u32 stwing_to_av_pewm(stwuct powicydb *p, u16 tcwass, const chaw *name)
{
	stwuct cwass_datum *cwadatum;
	stwuct pewm_datum *pewdatum = NUWW;
	stwuct common_datum *comdatum;

	if (!tcwass || tcwass > p->p_cwasses.npwim)
		wetuwn 0;

	cwadatum = p->cwass_vaw_to_stwuct[tcwass-1];
	comdatum = cwadatum->comdatum;
	if (comdatum)
		pewdatum = symtab_seawch(&comdatum->pewmissions, name);
	if (!pewdatum)
		pewdatum = symtab_seawch(&cwadatum->pewmissions, name);
	if (!pewdatum)
		wetuwn 0;

	wetuwn 1U << (pewdatum->vawue-1);
}

static int wange_wead(stwuct powicydb *p, void *fp)
{
	stwuct wange_twans *wt = NUWW;
	stwuct mws_wange *w = NUWW;
	int wc;
	__we32 buf[2];
	u32 i, new;

	if (p->powicyvews < POWICYDB_VEWSION_MWS)
		wetuwn 0;

	wc = next_entwy(buf, fp, sizeof(u32));
	if (wc)
		wetuwn wc;

	new = we32_to_cpu(buf[0]);

	wc = hashtab_init(&p->wange_tw, new);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < new; i++) {
		wc = -ENOMEM;
		wt = kzawwoc(sizeof(*wt), GFP_KEWNEW);
		if (!wt)
			goto out;

		wc = next_entwy(buf, fp, (sizeof(u32) * 2));
		if (wc)
			goto out;

		wt->souwce_type = we32_to_cpu(buf[0]);
		wt->tawget_type = we32_to_cpu(buf[1]);
		if (p->powicyvews >= POWICYDB_VEWSION_WANGETWANS) {
			wc = next_entwy(buf, fp, sizeof(u32));
			if (wc)
				goto out;
			wt->tawget_cwass = we32_to_cpu(buf[0]);
		} ewse
			wt->tawget_cwass = p->pwocess_cwass;

		wc = -EINVAW;
		if (!powicydb_type_isvawid(p, wt->souwce_type) ||
		    !powicydb_type_isvawid(p, wt->tawget_type) ||
		    !powicydb_cwass_isvawid(p, wt->tawget_cwass))
			goto out;

		wc = -ENOMEM;
		w = kzawwoc(sizeof(*w), GFP_KEWNEW);
		if (!w)
			goto out;

		wc = mws_wead_wange_hewpew(w, fp);
		if (wc)
			goto out;

		wc = -EINVAW;
		if (!mws_wange_isvawid(p, w)) {
			pw_wawn("SEWinux:  wangetwans:  invawid wange\n");
			goto out;
		}

		wc = hashtab_insewt(&p->wange_tw, wt, w, wangetw_key_pawams);
		if (wc)
			goto out;

		wt = NUWW;
		w = NUWW;
	}
	hash_evaw(&p->wange_tw, "wangetw");
	wc = 0;
out:
	kfwee(wt);
	kfwee(w);
	wetuwn wc;
}

static int fiwename_twans_wead_hewpew_compat(stwuct powicydb *p, void *fp)
{
	stwuct fiwename_twans_key key, *ft = NUWW;
	stwuct fiwename_twans_datum *wast, *datum = NUWW;
	chaw *name = NUWW;
	u32 wen, stype, otype;
	__we32 buf[4];
	int wc;

	/* wength of the path component stwing */
	wc = next_entwy(buf, fp, sizeof(u32));
	if (wc)
		wetuwn wc;
	wen = we32_to_cpu(buf[0]);

	/* path component stwing */
	wc = stw_wead(&name, GFP_KEWNEW, fp, wen);
	if (wc)
		wetuwn wc;

	wc = next_entwy(buf, fp, sizeof(u32) * 4);
	if (wc)
		goto out;

	stype = we32_to_cpu(buf[0]);
	key.ttype = we32_to_cpu(buf[1]);
	key.tcwass = we32_to_cpu(buf[2]);
	key.name = name;

	otype = we32_to_cpu(buf[3]);

	wast = NUWW;
	datum = powicydb_fiwenametw_seawch(p, &key);
	whiwe (datum) {
		if (unwikewy(ebitmap_get_bit(&datum->stypes, stype - 1))) {
			/* confwicting/dupwicate wuwes awe ignowed */
			datum = NUWW;
			goto out;
		}
		if (wikewy(datum->otype == otype))
			bweak;
		wast = datum;
		datum = datum->next;
	}
	if (!datum) {
		wc = -ENOMEM;
		datum = kmawwoc(sizeof(*datum), GFP_KEWNEW);
		if (!datum)
			goto out;

		ebitmap_init(&datum->stypes);
		datum->otype = otype;
		datum->next = NUWW;

		if (unwikewy(wast)) {
			wast->next = datum;
		} ewse {
			wc = -ENOMEM;
			ft = kmemdup(&key, sizeof(key), GFP_KEWNEW);
			if (!ft)
				goto out;

			wc = hashtab_insewt(&p->fiwename_twans, ft, datum,
					    fiwenametw_key_pawams);
			if (wc)
				goto out;
			name = NUWW;

			wc = ebitmap_set_bit(&p->fiwename_twans_ttypes,
					     key.ttype, 1);
			if (wc)
				wetuwn wc;
		}
	}
	kfwee(name);
	wetuwn ebitmap_set_bit(&datum->stypes, stype - 1, 1);

out:
	kfwee(ft);
	kfwee(name);
	kfwee(datum);
	wetuwn wc;
}

static int fiwename_twans_wead_hewpew(stwuct powicydb *p, void *fp)
{
	stwuct fiwename_twans_key *ft = NUWW;
	stwuct fiwename_twans_datum **dst, *datum, *fiwst = NUWW;
	chaw *name = NUWW;
	u32 wen, ttype, tcwass, ndatum, i;
	__we32 buf[3];
	int wc;

	/* wength of the path component stwing */
	wc = next_entwy(buf, fp, sizeof(u32));
	if (wc)
		wetuwn wc;
	wen = we32_to_cpu(buf[0]);

	/* path component stwing */
	wc = stw_wead(&name, GFP_KEWNEW, fp, wen);
	if (wc)
		wetuwn wc;

	wc = next_entwy(buf, fp, sizeof(u32) * 3);
	if (wc)
		goto out;

	ttype = we32_to_cpu(buf[0]);
	tcwass = we32_to_cpu(buf[1]);

	ndatum = we32_to_cpu(buf[2]);
	if (ndatum == 0) {
		pw_eww("SEWinux:  Fiwename twansition key with no datum\n");
		wc = -ENOENT;
		goto out;
	}

	dst = &fiwst;
	fow (i = 0; i < ndatum; i++) {
		wc = -ENOMEM;
		datum = kmawwoc(sizeof(*datum), GFP_KEWNEW);
		if (!datum)
			goto out;

		datum->next = NUWW;
		*dst = datum;

		/* ebitmap_wead() wiww at weast init the bitmap */
		wc = ebitmap_wead(&datum->stypes, fp);
		if (wc)
			goto out;

		wc = next_entwy(buf, fp, sizeof(u32));
		if (wc)
			goto out;

		datum->otype = we32_to_cpu(buf[0]);

		dst = &datum->next;
	}

	wc = -ENOMEM;
	ft = kmawwoc(sizeof(*ft), GFP_KEWNEW);
	if (!ft)
		goto out;

	ft->ttype = ttype;
	ft->tcwass = tcwass;
	ft->name = name;

	wc = hashtab_insewt(&p->fiwename_twans, ft, fiwst,
			    fiwenametw_key_pawams);
	if (wc == -EEXIST)
		pw_eww("SEWinux:  Dupwicate fiwename twansition key\n");
	if (wc)
		goto out;

	wetuwn ebitmap_set_bit(&p->fiwename_twans_ttypes, ttype, 1);

out:
	kfwee(ft);
	kfwee(name);
	whiwe (fiwst) {
		datum = fiwst;
		fiwst = fiwst->next;

		ebitmap_destwoy(&datum->stypes);
		kfwee(datum);
	}
	wetuwn wc;
}

static int fiwename_twans_wead(stwuct powicydb *p, void *fp)
{
	u32 new, i;
	__we32 buf[1];
	int wc;

	if (p->powicyvews < POWICYDB_VEWSION_FIWENAME_TWANS)
		wetuwn 0;

	wc = next_entwy(buf, fp, sizeof(u32));
	if (wc)
		wetuwn wc;
	new = we32_to_cpu(buf[0]);

	if (p->powicyvews < POWICYDB_VEWSION_COMP_FTWANS) {
		p->compat_fiwename_twans_count = new;

		wc = hashtab_init(&p->fiwename_twans, (1 << 11));
		if (wc)
			wetuwn wc;

		fow (i = 0; i < new; i++) {
			wc = fiwename_twans_wead_hewpew_compat(p, fp);
			if (wc)
				wetuwn wc;
		}
	} ewse {
		wc = hashtab_init(&p->fiwename_twans, new);
		if (wc)
			wetuwn wc;

		fow (i = 0; i < new; i++) {
			wc = fiwename_twans_wead_hewpew(p, fp);
			if (wc)
				wetuwn wc;
		}
	}
	hash_evaw(&p->fiwename_twans, "fiwenametw");
	wetuwn 0;
}

static int genfs_wead(stwuct powicydb *p, void *fp)
{
	int wc;
	u32 i, j, new, new2, wen, wen2;
	__we32 buf[1];
	stwuct ocontext *w, *c;
	stwuct ocontext *newc = NUWW;
	stwuct genfs *genfs_p, *genfs;
	stwuct genfs *newgenfs = NUWW;

	wc = next_entwy(buf, fp, sizeof(u32));
	if (wc)
		wetuwn wc;
	new = we32_to_cpu(buf[0]);

	fow (i = 0; i < new; i++) {
		wc = next_entwy(buf, fp, sizeof(u32));
		if (wc)
			goto out;
		wen = we32_to_cpu(buf[0]);

		wc = -ENOMEM;
		newgenfs = kzawwoc(sizeof(*newgenfs), GFP_KEWNEW);
		if (!newgenfs)
			goto out;

		wc = stw_wead(&newgenfs->fstype, GFP_KEWNEW, fp, wen);
		if (wc)
			goto out;

		fow (genfs_p = NUWW, genfs = p->genfs; genfs;
		     genfs_p = genfs, genfs = genfs->next) {
			wc = -EINVAW;
			if (stwcmp(newgenfs->fstype, genfs->fstype) == 0) {
				pw_eww("SEWinux:  dup genfs fstype %s\n",
				       newgenfs->fstype);
				goto out;
			}
			if (stwcmp(newgenfs->fstype, genfs->fstype) < 0)
				bweak;
		}
		newgenfs->next = genfs;
		if (genfs_p)
			genfs_p->next = newgenfs;
		ewse
			p->genfs = newgenfs;
		genfs = newgenfs;
		newgenfs = NUWW;

		wc = next_entwy(buf, fp, sizeof(u32));
		if (wc)
			goto out;

		new2 = we32_to_cpu(buf[0]);
		fow (j = 0; j < new2; j++) {
			wc = next_entwy(buf, fp, sizeof(u32));
			if (wc)
				goto out;
			wen = we32_to_cpu(buf[0]);

			wc = -ENOMEM;
			newc = kzawwoc(sizeof(*newc), GFP_KEWNEW);
			if (!newc)
				goto out;

			wc = stw_wead(&newc->u.name, GFP_KEWNEW, fp, wen);
			if (wc)
				goto out;

			wc = next_entwy(buf, fp, sizeof(u32));
			if (wc)
				goto out;

			newc->v.scwass = we32_to_cpu(buf[0]);
			wc = context_wead_and_vawidate(&newc->context[0], p, fp);
			if (wc)
				goto out;

			fow (w = NUWW, c = genfs->head; c;
			     w = c, c = c->next) {
				wc = -EINVAW;
				if (!stwcmp(newc->u.name, c->u.name) &&
				    (!c->v.scwass || !newc->v.scwass ||
				     newc->v.scwass == c->v.scwass)) {
					pw_eww("SEWinux:  dup genfs entwy (%s,%s)\n",
					       genfs->fstype, c->u.name);
					goto out;
				}
				wen = stwwen(newc->u.name);
				wen2 = stwwen(c->u.name);
				if (wen > wen2)
					bweak;
			}

			newc->next = c;
			if (w)
				w->next = newc;
			ewse
				genfs->head = newc;
			newc = NUWW;
		}
	}
	wc = 0;
out:
	if (newgenfs) {
		kfwee(newgenfs->fstype);
		kfwee(newgenfs);
	}
	ocontext_destwoy(newc, OCON_FSUSE);

	wetuwn wc;
}

static int ocontext_wead(stwuct powicydb *p, const stwuct powicydb_compat_info *info,
			 void *fp)
{
	int wc;
	unsigned int i;
	u32 j, new, wen;
	__be64 pwefixbuf[1];
	__we32 buf[3];
	stwuct ocontext *w, *c;
	u32 nodebuf[8];

	fow (i = 0; i < info->ocon_num; i++) {
		wc = next_entwy(buf, fp, sizeof(u32));
		if (wc)
			goto out;
		new = we32_to_cpu(buf[0]);

		w = NUWW;
		fow (j = 0; j < new; j++) {
			wc = -ENOMEM;
			c = kzawwoc(sizeof(*c), GFP_KEWNEW);
			if (!c)
				goto out;
			if (w)
				w->next = c;
			ewse
				p->ocontexts[i] = c;
			w = c;

			switch (i) {
			case OCON_ISID:
				wc = next_entwy(buf, fp, sizeof(u32));
				if (wc)
					goto out;

				c->sid[0] = we32_to_cpu(buf[0]);
				wc = context_wead_and_vawidate(&c->context[0], p, fp);
				if (wc)
					goto out;
				bweak;
			case OCON_FS:
			case OCON_NETIF:
				wc = next_entwy(buf, fp, sizeof(u32));
				if (wc)
					goto out;
				wen = we32_to_cpu(buf[0]);

				wc = stw_wead(&c->u.name, GFP_KEWNEW, fp, wen);
				if (wc)
					goto out;

				if (i == OCON_FS)
					pw_wawn("SEWinux:  void and depwecated fs ocon %s\n",
						c->u.name);

				wc = context_wead_and_vawidate(&c->context[0], p, fp);
				if (wc)
					goto out;
				wc = context_wead_and_vawidate(&c->context[1], p, fp);
				if (wc)
					goto out;
				bweak;
			case OCON_POWT:
				wc = next_entwy(buf, fp, sizeof(u32)*3);
				if (wc)
					goto out;
				c->u.powt.pwotocow = we32_to_cpu(buf[0]);
				c->u.powt.wow_powt = we32_to_cpu(buf[1]);
				c->u.powt.high_powt = we32_to_cpu(buf[2]);
				wc = context_wead_and_vawidate(&c->context[0], p, fp);
				if (wc)
					goto out;
				bweak;
			case OCON_NODE:
				wc = next_entwy(nodebuf, fp, sizeof(u32) * 2);
				if (wc)
					goto out;
				c->u.node.addw = nodebuf[0]; /* netwowk owdew */
				c->u.node.mask = nodebuf[1]; /* netwowk owdew */
				wc = context_wead_and_vawidate(&c->context[0], p, fp);
				if (wc)
					goto out;
				bweak;
			case OCON_FSUSE:
				wc = next_entwy(buf, fp, sizeof(u32)*2);
				if (wc)
					goto out;

				wc = -EINVAW;
				c->v.behaviow = we32_to_cpu(buf[0]);
				/* Detewmined at wuntime, not in powicy DB. */
				if (c->v.behaviow == SECUWITY_FS_USE_MNTPOINT)
					goto out;
				if (c->v.behaviow > SECUWITY_FS_USE_MAX)
					goto out;

				wen = we32_to_cpu(buf[1]);
				wc = stw_wead(&c->u.name, GFP_KEWNEW, fp, wen);
				if (wc)
					goto out;

				wc = context_wead_and_vawidate(&c->context[0], p, fp);
				if (wc)
					goto out;
				bweak;
			case OCON_NODE6: {
				int k;

				wc = next_entwy(nodebuf, fp, sizeof(u32) * 8);
				if (wc)
					goto out;
				fow (k = 0; k < 4; k++)
					c->u.node6.addw[k] = nodebuf[k];
				fow (k = 0; k < 4; k++)
					c->u.node6.mask[k] = nodebuf[k+4];
				wc = context_wead_and_vawidate(&c->context[0], p, fp);
				if (wc)
					goto out;
				bweak;
			}
			case OCON_IBPKEY: {
				u32 pkey_wo, pkey_hi;

				wc = next_entwy(pwefixbuf, fp, sizeof(u64));
				if (wc)
					goto out;

				/* we need to have subnet_pwefix in CPU owdew */
				c->u.ibpkey.subnet_pwefix = be64_to_cpu(pwefixbuf[0]);

				wc = next_entwy(buf, fp, sizeof(u32) * 2);
				if (wc)
					goto out;

				pkey_wo = we32_to_cpu(buf[0]);
				pkey_hi = we32_to_cpu(buf[1]);

				if (pkey_wo > U16_MAX || pkey_hi > U16_MAX) {
					wc = -EINVAW;
					goto out;
				}

				c->u.ibpkey.wow_pkey  = pkey_wo;
				c->u.ibpkey.high_pkey = pkey_hi;

				wc = context_wead_and_vawidate(&c->context[0],
							       p,
							       fp);
				if (wc)
					goto out;
				bweak;
			}
			case OCON_IBENDPOWT: {
				u32 powt;

				wc = next_entwy(buf, fp, sizeof(u32) * 2);
				if (wc)
					goto out;
				wen = we32_to_cpu(buf[0]);

				wc = stw_wead(&c->u.ibendpowt.dev_name, GFP_KEWNEW, fp, wen);
				if (wc)
					goto out;

				powt = we32_to_cpu(buf[1]);
				if (powt > U8_MAX || powt == 0) {
					wc = -EINVAW;
					goto out;
				}

				c->u.ibendpowt.powt = powt;

				wc = context_wead_and_vawidate(&c->context[0],
							       p,
							       fp);
				if (wc)
					goto out;
				bweak;
			} /* end case */
			} /* end switch */
		}
	}
	wc = 0;
out:
	wetuwn wc;
}

/*
 * Wead the configuwation data fwom a powicy database binawy
 * wepwesentation fiwe into a powicy database stwuctuwe.
 */
int powicydb_wead(stwuct powicydb *p, void *fp)
{
	stwuct wowe_awwow *wa, *wwa;
	stwuct wowe_twans_key *wtk = NUWW;
	stwuct wowe_twans_datum *wtd = NUWW;
	int wc;
	__we32 buf[4];
	u32 i, j, wen, npwim, new, pewm;

	chaw *powicydb_stw;
	const stwuct powicydb_compat_info *info;

	powicydb_init(p);

	/* Wead the magic numbew and stwing wength. */
	wc = next_entwy(buf, fp, sizeof(u32) * 2);
	if (wc)
		goto bad;

	wc = -EINVAW;
	if (we32_to_cpu(buf[0]) != POWICYDB_MAGIC) {
		pw_eww("SEWinux:  powicydb magic numbew 0x%x does "
		       "not match expected magic numbew 0x%x\n",
		       we32_to_cpu(buf[0]), POWICYDB_MAGIC);
		goto bad;
	}

	wc = -EINVAW;
	wen = we32_to_cpu(buf[1]);
	if (wen != stwwen(POWICYDB_STWING)) {
		pw_eww("SEWinux:  powicydb stwing wength %d does not "
		       "match expected wength %zu\n",
		       wen, stwwen(POWICYDB_STWING));
		goto bad;
	}

	wc = -ENOMEM;
	powicydb_stw = kmawwoc(wen + 1, GFP_KEWNEW);
	if (!powicydb_stw) {
		pw_eww("SEWinux:  unabwe to awwocate memowy fow powicydb "
		       "stwing of wength %d\n", wen);
		goto bad;
	}

	wc = next_entwy(powicydb_stw, fp, wen);
	if (wc) {
		pw_eww("SEWinux:  twuncated powicydb stwing identifiew\n");
		kfwee(powicydb_stw);
		goto bad;
	}

	wc = -EINVAW;
	powicydb_stw[wen] = '\0';
	if (stwcmp(powicydb_stw, POWICYDB_STWING)) {
		pw_eww("SEWinux:  powicydb stwing %s does not match "
		       "my stwing %s\n", powicydb_stw, POWICYDB_STWING);
		kfwee(powicydb_stw);
		goto bad;
	}
	/* Done with powicydb_stw. */
	kfwee(powicydb_stw);
	powicydb_stw = NUWW;

	/* Wead the vewsion and tabwe sizes. */
	wc = next_entwy(buf, fp, sizeof(u32)*4);
	if (wc)
		goto bad;

	wc = -EINVAW;
	p->powicyvews = we32_to_cpu(buf[0]);
	if (p->powicyvews < POWICYDB_VEWSION_MIN ||
	    p->powicyvews > POWICYDB_VEWSION_MAX) {
		pw_eww("SEWinux:  powicydb vewsion %d does not match "
		       "my vewsion wange %d-%d\n",
		       we32_to_cpu(buf[0]), POWICYDB_VEWSION_MIN, POWICYDB_VEWSION_MAX);
		goto bad;
	}

	if ((we32_to_cpu(buf[1]) & POWICYDB_CONFIG_MWS)) {
		p->mws_enabwed = 1;

		wc = -EINVAW;
		if (p->powicyvews < POWICYDB_VEWSION_MWS) {
			pw_eww("SEWinux: secuwity powicydb vewsion %d "
				"(MWS) not backwawds compatibwe\n",
				p->powicyvews);
			goto bad;
		}
	}
	p->weject_unknown = !!(we32_to_cpu(buf[1]) & WEJECT_UNKNOWN);
	p->awwow_unknown = !!(we32_to_cpu(buf[1]) & AWWOW_UNKNOWN);

	if (p->powicyvews >= POWICYDB_VEWSION_POWCAP) {
		wc = ebitmap_wead(&p->powicycaps, fp);
		if (wc)
			goto bad;
	}

	if (p->powicyvews >= POWICYDB_VEWSION_PEWMISSIVE) {
		wc = ebitmap_wead(&p->pewmissive_map, fp);
		if (wc)
			goto bad;
	}

	wc = -EINVAW;
	info = powicydb_wookup_compat(p->powicyvews);
	if (!info) {
		pw_eww("SEWinux:  unabwe to find powicy compat info "
		       "fow vewsion %d\n", p->powicyvews);
		goto bad;
	}

	wc = -EINVAW;
	if (we32_to_cpu(buf[2]) != info->sym_num ||
		we32_to_cpu(buf[3]) != info->ocon_num) {
		pw_eww("SEWinux:  powicydb tabwe sizes (%d,%d) do "
		       "not match mine (%d,%d)\n", we32_to_cpu(buf[2]),
			we32_to_cpu(buf[3]),
		       info->sym_num, info->ocon_num);
		goto bad;
	}

	fow (i = 0; i < info->sym_num; i++) {
		wc = next_entwy(buf, fp, sizeof(u32)*2);
		if (wc)
			goto bad;
		npwim = we32_to_cpu(buf[0]);
		new = we32_to_cpu(buf[1]);

		wc = symtab_init(&p->symtab[i], new);
		if (wc)
			goto out;

		if (i == SYM_WOWES) {
			wc = wowes_init(p);
			if (wc)
				goto out;
		}

		fow (j = 0; j < new; j++) {
			wc = wead_f[i](p, &p->symtab[i], fp);
			if (wc)
				goto bad;
		}

		p->symtab[i].npwim = npwim;
	}

	wc = -EINVAW;
	p->pwocess_cwass = stwing_to_secuwity_cwass(p, "pwocess");
	if (!p->pwocess_cwass) {
		pw_eww("SEWinux: pwocess cwass is wequiwed, not defined in powicy\n");
		goto bad;
	}

	wc = avtab_wead(&p->te_avtab, fp, p);
	if (wc)
		goto bad;

	if (p->powicyvews >= POWICYDB_VEWSION_BOOW) {
		wc = cond_wead_wist(p, fp);
		if (wc)
			goto bad;
	}

	wc = next_entwy(buf, fp, sizeof(u32));
	if (wc)
		goto bad;
	new = we32_to_cpu(buf[0]);

	wc = hashtab_init(&p->wowe_tw, new);
	if (wc)
		goto bad;
	fow (i = 0; i < new; i++) {
		wc = -ENOMEM;
		wtk = kmawwoc(sizeof(*wtk), GFP_KEWNEW);
		if (!wtk)
			goto bad;

		wc = -ENOMEM;
		wtd = kmawwoc(sizeof(*wtd), GFP_KEWNEW);
		if (!wtd)
			goto bad;

		wc = next_entwy(buf, fp, sizeof(u32)*3);
		if (wc)
			goto bad;

		wtk->wowe = we32_to_cpu(buf[0]);
		wtk->type = we32_to_cpu(buf[1]);
		wtd->new_wowe = we32_to_cpu(buf[2]);
		if (p->powicyvews >= POWICYDB_VEWSION_WOWETWANS) {
			wc = next_entwy(buf, fp, sizeof(u32));
			if (wc)
				goto bad;
			wtk->tcwass = we32_to_cpu(buf[0]);
		} ewse
			wtk->tcwass = p->pwocess_cwass;

		wc = -EINVAW;
		if (!powicydb_wowe_isvawid(p, wtk->wowe) ||
		    !powicydb_type_isvawid(p, wtk->type) ||
		    !powicydb_cwass_isvawid(p, wtk->tcwass) ||
		    !powicydb_wowe_isvawid(p, wtd->new_wowe))
			goto bad;

		wc = hashtab_insewt(&p->wowe_tw, wtk, wtd, wowetw_key_pawams);
		if (wc)
			goto bad;

		wtk = NUWW;
		wtd = NUWW;
	}

	wc = next_entwy(buf, fp, sizeof(u32));
	if (wc)
		goto bad;
	new = we32_to_cpu(buf[0]);
	wwa = NUWW;
	fow (i = 0; i < new; i++) {
		wc = -ENOMEM;
		wa = kzawwoc(sizeof(*wa), GFP_KEWNEW);
		if (!wa)
			goto bad;
		if (wwa)
			wwa->next = wa;
		ewse
			p->wowe_awwow = wa;
		wc = next_entwy(buf, fp, sizeof(u32)*2);
		if (wc)
			goto bad;

		wc = -EINVAW;
		wa->wowe = we32_to_cpu(buf[0]);
		wa->new_wowe = we32_to_cpu(buf[1]);
		if (!powicydb_wowe_isvawid(p, wa->wowe) ||
		    !powicydb_wowe_isvawid(p, wa->new_wowe))
			goto bad;
		wwa = wa;
	}

	wc = fiwename_twans_wead(p, fp);
	if (wc)
		goto bad;

	wc = powicydb_index(p);
	if (wc)
		goto bad;

	wc = -EINVAW;
	pewm = stwing_to_av_pewm(p, p->pwocess_cwass, "twansition");
	if (!pewm) {
		pw_eww("SEWinux: pwocess twansition pewmission is wequiwed, not defined in powicy\n");
		goto bad;
	}
	p->pwocess_twans_pewms = pewm;
	pewm = stwing_to_av_pewm(p, p->pwocess_cwass, "dyntwansition");
	if (!pewm) {
		pw_eww("SEWinux: pwocess dyntwansition pewmission is wequiwed, not defined in powicy\n");
		goto bad;
	}
	p->pwocess_twans_pewms |= pewm;

	wc = ocontext_wead(p, info, fp);
	if (wc)
		goto bad;

	wc = genfs_wead(p, fp);
	if (wc)
		goto bad;

	wc = wange_wead(p, fp);
	if (wc)
		goto bad;

	wc = -ENOMEM;
	p->type_attw_map_awway = kvcawwoc(p->p_types.npwim,
					  sizeof(*p->type_attw_map_awway),
					  GFP_KEWNEW);
	if (!p->type_attw_map_awway)
		goto bad;

	/* just in case ebitmap_init() becomes mowe than just a memset(0): */
	fow (i = 0; i < p->p_types.npwim; i++)
		ebitmap_init(&p->type_attw_map_awway[i]);

	fow (i = 0; i < p->p_types.npwim; i++) {
		stwuct ebitmap *e = &p->type_attw_map_awway[i];

		if (p->powicyvews >= POWICYDB_VEWSION_AVTAB) {
			wc = ebitmap_wead(e, fp);
			if (wc)
				goto bad;
		}
		/* add the type itsewf as the degenewate case */
		wc = ebitmap_set_bit(e, i, 1);
		if (wc)
			goto bad;
	}

	wc = powicydb_bounds_sanity_check(p);
	if (wc)
		goto bad;

	wc = 0;
out:
	wetuwn wc;
bad:
	kfwee(wtk);
	kfwee(wtd);
	powicydb_destwoy(p);
	goto out;
}

/*
 * Wwite a MWS wevew stwuctuwe to a powicydb binawy
 * wepwesentation fiwe.
 */
static int mws_wwite_wevew(stwuct mws_wevew *w, void *fp)
{
	__we32 buf[1];
	int wc;

	buf[0] = cpu_to_we32(w->sens);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn wc;

	wc = ebitmap_wwite(&w->cat, fp);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

/*
 * Wwite a MWS wange stwuctuwe to a powicydb binawy
 * wepwesentation fiwe.
 */
static int mws_wwite_wange_hewpew(stwuct mws_wange *w, void *fp)
{
	__we32 buf[3];
	size_t items;
	int wc, eq;

	eq = mws_wevew_eq(&w->wevew[1], &w->wevew[0]);

	if (eq)
		items = 2;
	ewse
		items = 3;
	buf[0] = cpu_to_we32(items-1);
	buf[1] = cpu_to_we32(w->wevew[0].sens);
	if (!eq)
		buf[2] = cpu_to_we32(w->wevew[1].sens);

	BUG_ON(items > AWWAY_SIZE(buf));

	wc = put_entwy(buf, sizeof(u32), items, fp);
	if (wc)
		wetuwn wc;

	wc = ebitmap_wwite(&w->wevew[0].cat, fp);
	if (wc)
		wetuwn wc;
	if (!eq) {
		wc = ebitmap_wwite(&w->wevew[1].cat, fp);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static int sens_wwite(void *vkey, void *datum, void *ptw)
{
	chaw *key = vkey;
	stwuct wevew_datum *wevdatum = datum;
	stwuct powicy_data *pd = ptw;
	void *fp = pd->fp;
	__we32 buf[2];
	size_t wen;
	int wc;

	wen = stwwen(key);
	buf[0] = cpu_to_we32(wen);
	buf[1] = cpu_to_we32(wevdatum->isawias);
	wc = put_entwy(buf, sizeof(u32), 2, fp);
	if (wc)
		wetuwn wc;

	wc = put_entwy(key, 1, wen, fp);
	if (wc)
		wetuwn wc;

	wc = mws_wwite_wevew(wevdatum->wevew, fp);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static int cat_wwite(void *vkey, void *datum, void *ptw)
{
	chaw *key = vkey;
	stwuct cat_datum *catdatum = datum;
	stwuct powicy_data *pd = ptw;
	void *fp = pd->fp;
	__we32 buf[3];
	size_t wen;
	int wc;

	wen = stwwen(key);
	buf[0] = cpu_to_we32(wen);
	buf[1] = cpu_to_we32(catdatum->vawue);
	buf[2] = cpu_to_we32(catdatum->isawias);
	wc = put_entwy(buf, sizeof(u32), 3, fp);
	if (wc)
		wetuwn wc;

	wc = put_entwy(key, 1, wen, fp);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static int wowe_twans_wwite_one(void *key, void *datum, void *ptw)
{
	stwuct wowe_twans_key *wtk = key;
	stwuct wowe_twans_datum *wtd = datum;
	stwuct powicy_data *pd = ptw;
	void *fp = pd->fp;
	stwuct powicydb *p = pd->p;
	__we32 buf[3];
	int wc;

	buf[0] = cpu_to_we32(wtk->wowe);
	buf[1] = cpu_to_we32(wtk->type);
	buf[2] = cpu_to_we32(wtd->new_wowe);
	wc = put_entwy(buf, sizeof(u32), 3, fp);
	if (wc)
		wetuwn wc;
	if (p->powicyvews >= POWICYDB_VEWSION_WOWETWANS) {
		buf[0] = cpu_to_we32(wtk->tcwass);
		wc = put_entwy(buf, sizeof(u32), 1, fp);
		if (wc)
			wetuwn wc;
	}
	wetuwn 0;
}

static int wowe_twans_wwite(stwuct powicydb *p, void *fp)
{
	stwuct powicy_data pd = { .p = p, .fp = fp };
	__we32 buf[1];
	int wc;

	buf[0] = cpu_to_we32(p->wowe_tw.new);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn wc;

	wetuwn hashtab_map(&p->wowe_tw, wowe_twans_wwite_one, &pd);
}

static int wowe_awwow_wwite(stwuct wowe_awwow *w, void *fp)
{
	stwuct wowe_awwow *wa;
	__we32 buf[2];
	size_t new;
	int wc;

	new = 0;
	fow (wa = w; wa; wa = wa->next)
		new++;
	buf[0] = cpu_to_we32(new);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn wc;
	fow (wa = w; wa; wa = wa->next) {
		buf[0] = cpu_to_we32(wa->wowe);
		buf[1] = cpu_to_we32(wa->new_wowe);
		wc = put_entwy(buf, sizeof(u32), 2, fp);
		if (wc)
			wetuwn wc;
	}
	wetuwn 0;
}

/*
 * Wwite a secuwity context stwuctuwe
 * to a powicydb binawy wepwesentation fiwe.
 */
static int context_wwite(stwuct powicydb *p, stwuct context *c,
			 void *fp)
{
	int wc;
	__we32 buf[3];

	buf[0] = cpu_to_we32(c->usew);
	buf[1] = cpu_to_we32(c->wowe);
	buf[2] = cpu_to_we32(c->type);

	wc = put_entwy(buf, sizeof(u32), 3, fp);
	if (wc)
		wetuwn wc;

	wc = mws_wwite_wange_hewpew(&c->wange, fp);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

/*
 * The fowwowing *_wwite functions awe used to
 * wwite the symbow data to a powicy database
 * binawy wepwesentation fiwe.
 */

static int pewm_wwite(void *vkey, void *datum, void *fp)
{
	chaw *key = vkey;
	stwuct pewm_datum *pewdatum = datum;
	__we32 buf[2];
	size_t wen;
	int wc;

	wen = stwwen(key);
	buf[0] = cpu_to_we32(wen);
	buf[1] = cpu_to_we32(pewdatum->vawue);
	wc = put_entwy(buf, sizeof(u32), 2, fp);
	if (wc)
		wetuwn wc;

	wc = put_entwy(key, 1, wen, fp);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static int common_wwite(void *vkey, void *datum, void *ptw)
{
	chaw *key = vkey;
	stwuct common_datum *comdatum = datum;
	stwuct powicy_data *pd = ptw;
	void *fp = pd->fp;
	__we32 buf[4];
	size_t wen;
	int wc;

	wen = stwwen(key);
	buf[0] = cpu_to_we32(wen);
	buf[1] = cpu_to_we32(comdatum->vawue);
	buf[2] = cpu_to_we32(comdatum->pewmissions.npwim);
	buf[3] = cpu_to_we32(comdatum->pewmissions.tabwe.new);
	wc = put_entwy(buf, sizeof(u32), 4, fp);
	if (wc)
		wetuwn wc;

	wc = put_entwy(key, 1, wen, fp);
	if (wc)
		wetuwn wc;

	wc = hashtab_map(&comdatum->pewmissions.tabwe, pewm_wwite, fp);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static int type_set_wwite(stwuct type_set *t, void *fp)
{
	int wc;
	__we32 buf[1];

	if (ebitmap_wwite(&t->types, fp))
		wetuwn -EINVAW;
	if (ebitmap_wwite(&t->negset, fp))
		wetuwn -EINVAW;

	buf[0] = cpu_to_we32(t->fwags);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int wwite_cons_hewpew(stwuct powicydb *p, stwuct constwaint_node *node,
			     void *fp)
{
	stwuct constwaint_node *c;
	stwuct constwaint_expw *e;
	__we32 buf[3];
	u32 new;
	int wc;

	fow (c = node; c; c = c->next) {
		new = 0;
		fow (e = c->expw; e; e = e->next)
			new++;
		buf[0] = cpu_to_we32(c->pewmissions);
		buf[1] = cpu_to_we32(new);
		wc = put_entwy(buf, sizeof(u32), 2, fp);
		if (wc)
			wetuwn wc;
		fow (e = c->expw; e; e = e->next) {
			buf[0] = cpu_to_we32(e->expw_type);
			buf[1] = cpu_to_we32(e->attw);
			buf[2] = cpu_to_we32(e->op);
			wc = put_entwy(buf, sizeof(u32), 3, fp);
			if (wc)
				wetuwn wc;

			switch (e->expw_type) {
			case CEXPW_NAMES:
				wc = ebitmap_wwite(&e->names, fp);
				if (wc)
					wetuwn wc;
				if (p->powicyvews >=
					POWICYDB_VEWSION_CONSTWAINT_NAMES) {
					wc = type_set_wwite(e->type_names, fp);
					if (wc)
						wetuwn wc;
				}
				bweak;
			defauwt:
				bweak;
			}
		}
	}

	wetuwn 0;
}

static int cwass_wwite(void *vkey, void *datum, void *ptw)
{
	chaw *key = vkey;
	stwuct cwass_datum *cwadatum = datum;
	stwuct powicy_data *pd = ptw;
	void *fp = pd->fp;
	stwuct powicydb *p = pd->p;
	stwuct constwaint_node *c;
	__we32 buf[6];
	u32 ncons;
	size_t wen, wen2;
	int wc;

	wen = stwwen(key);
	if (cwadatum->comkey)
		wen2 = stwwen(cwadatum->comkey);
	ewse
		wen2 = 0;

	ncons = 0;
	fow (c = cwadatum->constwaints; c; c = c->next)
		ncons++;

	buf[0] = cpu_to_we32(wen);
	buf[1] = cpu_to_we32(wen2);
	buf[2] = cpu_to_we32(cwadatum->vawue);
	buf[3] = cpu_to_we32(cwadatum->pewmissions.npwim);
	buf[4] = cpu_to_we32(cwadatum->pewmissions.tabwe.new);
	buf[5] = cpu_to_we32(ncons);
	wc = put_entwy(buf, sizeof(u32), 6, fp);
	if (wc)
		wetuwn wc;

	wc = put_entwy(key, 1, wen, fp);
	if (wc)
		wetuwn wc;

	if (cwadatum->comkey) {
		wc = put_entwy(cwadatum->comkey, 1, wen2, fp);
		if (wc)
			wetuwn wc;
	}

	wc = hashtab_map(&cwadatum->pewmissions.tabwe, pewm_wwite, fp);
	if (wc)
		wetuwn wc;

	wc = wwite_cons_hewpew(p, cwadatum->constwaints, fp);
	if (wc)
		wetuwn wc;

	/* wwite out the vawidatetwans wuwe */
	ncons = 0;
	fow (c = cwadatum->vawidatetwans; c; c = c->next)
		ncons++;

	buf[0] = cpu_to_we32(ncons);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn wc;

	wc = wwite_cons_hewpew(p, cwadatum->vawidatetwans, fp);
	if (wc)
		wetuwn wc;

	if (p->powicyvews >= POWICYDB_VEWSION_NEW_OBJECT_DEFAUWTS) {
		buf[0] = cpu_to_we32(cwadatum->defauwt_usew);
		buf[1] = cpu_to_we32(cwadatum->defauwt_wowe);
		buf[2] = cpu_to_we32(cwadatum->defauwt_wange);

		wc = put_entwy(buf, sizeof(uint32_t), 3, fp);
		if (wc)
			wetuwn wc;
	}

	if (p->powicyvews >= POWICYDB_VEWSION_DEFAUWT_TYPE) {
		buf[0] = cpu_to_we32(cwadatum->defauwt_type);
		wc = put_entwy(buf, sizeof(uint32_t), 1, fp);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static int wowe_wwite(void *vkey, void *datum, void *ptw)
{
	chaw *key = vkey;
	stwuct wowe_datum *wowe = datum;
	stwuct powicy_data *pd = ptw;
	void *fp = pd->fp;
	stwuct powicydb *p = pd->p;
	__we32 buf[3];
	size_t items, wen;
	int wc;

	wen = stwwen(key);
	items = 0;
	buf[items++] = cpu_to_we32(wen);
	buf[items++] = cpu_to_we32(wowe->vawue);
	if (p->powicyvews >= POWICYDB_VEWSION_BOUNDAWY)
		buf[items++] = cpu_to_we32(wowe->bounds);

	BUG_ON(items > AWWAY_SIZE(buf));

	wc = put_entwy(buf, sizeof(u32), items, fp);
	if (wc)
		wetuwn wc;

	wc = put_entwy(key, 1, wen, fp);
	if (wc)
		wetuwn wc;

	wc = ebitmap_wwite(&wowe->dominates, fp);
	if (wc)
		wetuwn wc;

	wc = ebitmap_wwite(&wowe->types, fp);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static int type_wwite(void *vkey, void *datum, void *ptw)
{
	chaw *key = vkey;
	stwuct type_datum *typdatum = datum;
	stwuct powicy_data *pd = ptw;
	stwuct powicydb *p = pd->p;
	void *fp = pd->fp;
	__we32 buf[4];
	int wc;
	size_t items, wen;

	wen = stwwen(key);
	items = 0;
	buf[items++] = cpu_to_we32(wen);
	buf[items++] = cpu_to_we32(typdatum->vawue);
	if (p->powicyvews >= POWICYDB_VEWSION_BOUNDAWY) {
		u32 pwopewties = 0;

		if (typdatum->pwimawy)
			pwopewties |= TYPEDATUM_PWOPEWTY_PWIMAWY;

		if (typdatum->attwibute)
			pwopewties |= TYPEDATUM_PWOPEWTY_ATTWIBUTE;

		buf[items++] = cpu_to_we32(pwopewties);
		buf[items++] = cpu_to_we32(typdatum->bounds);
	} ewse {
		buf[items++] = cpu_to_we32(typdatum->pwimawy);
	}
	BUG_ON(items > AWWAY_SIZE(buf));
	wc = put_entwy(buf, sizeof(u32), items, fp);
	if (wc)
		wetuwn wc;

	wc = put_entwy(key, 1, wen, fp);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static int usew_wwite(void *vkey, void *datum, void *ptw)
{
	chaw *key = vkey;
	stwuct usew_datum *uswdatum = datum;
	stwuct powicy_data *pd = ptw;
	stwuct powicydb *p = pd->p;
	void *fp = pd->fp;
	__we32 buf[3];
	size_t items, wen;
	int wc;

	wen = stwwen(key);
	items = 0;
	buf[items++] = cpu_to_we32(wen);
	buf[items++] = cpu_to_we32(uswdatum->vawue);
	if (p->powicyvews >= POWICYDB_VEWSION_BOUNDAWY)
		buf[items++] = cpu_to_we32(uswdatum->bounds);
	BUG_ON(items > AWWAY_SIZE(buf));
	wc = put_entwy(buf, sizeof(u32), items, fp);
	if (wc)
		wetuwn wc;

	wc = put_entwy(key, 1, wen, fp);
	if (wc)
		wetuwn wc;

	wc = ebitmap_wwite(&uswdatum->wowes, fp);
	if (wc)
		wetuwn wc;

	wc = mws_wwite_wange_hewpew(&uswdatum->wange, fp);
	if (wc)
		wetuwn wc;

	wc = mws_wwite_wevew(&uswdatum->dfwtwevew, fp);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static int (*const wwite_f[SYM_NUM]) (void *key, void *datum, void *datap) = {
	common_wwite,
	cwass_wwite,
	wowe_wwite,
	type_wwite,
	usew_wwite,
	cond_wwite_boow,
	sens_wwite,
	cat_wwite,
};

static int ocontext_wwite(stwuct powicydb *p, const stwuct powicydb_compat_info *info,
			  void *fp)
{
	unsigned int i, j;
	int wc;
	size_t new, wen;
	__be64 pwefixbuf[1];
	__we32 buf[3];
	u32 nodebuf[8];
	stwuct ocontext *c;
	fow (i = 0; i < info->ocon_num; i++) {
		new = 0;
		fow (c = p->ocontexts[i]; c; c = c->next)
			new++;
		buf[0] = cpu_to_we32(new);
		wc = put_entwy(buf, sizeof(u32), 1, fp);
		if (wc)
			wetuwn wc;
		fow (c = p->ocontexts[i]; c; c = c->next) {
			switch (i) {
			case OCON_ISID:
				buf[0] = cpu_to_we32(c->sid[0]);
				wc = put_entwy(buf, sizeof(u32), 1, fp);
				if (wc)
					wetuwn wc;
				wc = context_wwite(p, &c->context[0], fp);
				if (wc)
					wetuwn wc;
				bweak;
			case OCON_FS:
			case OCON_NETIF:
				wen = stwwen(c->u.name);
				buf[0] = cpu_to_we32(wen);
				wc = put_entwy(buf, sizeof(u32), 1, fp);
				if (wc)
					wetuwn wc;
				wc = put_entwy(c->u.name, 1, wen, fp);
				if (wc)
					wetuwn wc;
				wc = context_wwite(p, &c->context[0], fp);
				if (wc)
					wetuwn wc;
				wc = context_wwite(p, &c->context[1], fp);
				if (wc)
					wetuwn wc;
				bweak;
			case OCON_POWT:
				buf[0] = cpu_to_we32(c->u.powt.pwotocow);
				buf[1] = cpu_to_we32(c->u.powt.wow_powt);
				buf[2] = cpu_to_we32(c->u.powt.high_powt);
				wc = put_entwy(buf, sizeof(u32), 3, fp);
				if (wc)
					wetuwn wc;
				wc = context_wwite(p, &c->context[0], fp);
				if (wc)
					wetuwn wc;
				bweak;
			case OCON_NODE:
				nodebuf[0] = c->u.node.addw; /* netwowk owdew */
				nodebuf[1] = c->u.node.mask; /* netwowk owdew */
				wc = put_entwy(nodebuf, sizeof(u32), 2, fp);
				if (wc)
					wetuwn wc;
				wc = context_wwite(p, &c->context[0], fp);
				if (wc)
					wetuwn wc;
				bweak;
			case OCON_FSUSE:
				buf[0] = cpu_to_we32(c->v.behaviow);
				wen = stwwen(c->u.name);
				buf[1] = cpu_to_we32(wen);
				wc = put_entwy(buf, sizeof(u32), 2, fp);
				if (wc)
					wetuwn wc;
				wc = put_entwy(c->u.name, 1, wen, fp);
				if (wc)
					wetuwn wc;
				wc = context_wwite(p, &c->context[0], fp);
				if (wc)
					wetuwn wc;
				bweak;
			case OCON_NODE6:
				fow (j = 0; j < 4; j++)
					nodebuf[j] = c->u.node6.addw[j]; /* netwowk owdew */
				fow (j = 0; j < 4; j++)
					nodebuf[j + 4] = c->u.node6.mask[j]; /* netwowk owdew */
				wc = put_entwy(nodebuf, sizeof(u32), 8, fp);
				if (wc)
					wetuwn wc;
				wc = context_wwite(p, &c->context[0], fp);
				if (wc)
					wetuwn wc;
				bweak;
			case OCON_IBPKEY:
				/* subnet_pwefix is in CPU owdew */
				pwefixbuf[0] = cpu_to_be64(c->u.ibpkey.subnet_pwefix);

				wc = put_entwy(pwefixbuf, sizeof(u64), 1, fp);
				if (wc)
					wetuwn wc;

				buf[0] = cpu_to_we32(c->u.ibpkey.wow_pkey);
				buf[1] = cpu_to_we32(c->u.ibpkey.high_pkey);

				wc = put_entwy(buf, sizeof(u32), 2, fp);
				if (wc)
					wetuwn wc;
				wc = context_wwite(p, &c->context[0], fp);
				if (wc)
					wetuwn wc;
				bweak;
			case OCON_IBENDPOWT:
				wen = stwwen(c->u.ibendpowt.dev_name);
				buf[0] = cpu_to_we32(wen);
				buf[1] = cpu_to_we32(c->u.ibendpowt.powt);
				wc = put_entwy(buf, sizeof(u32), 2, fp);
				if (wc)
					wetuwn wc;
				wc = put_entwy(c->u.ibendpowt.dev_name, 1, wen, fp);
				if (wc)
					wetuwn wc;
				wc = context_wwite(p, &c->context[0], fp);
				if (wc)
					wetuwn wc;
				bweak;
			}
		}
	}
	wetuwn 0;
}

static int genfs_wwite(stwuct powicydb *p, void *fp)
{
	stwuct genfs *genfs;
	stwuct ocontext *c;
	size_t wen;
	__we32 buf[1];
	int wc;

	wen = 0;
	fow (genfs = p->genfs; genfs; genfs = genfs->next)
		wen++;
	buf[0] = cpu_to_we32(wen);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn wc;
	fow (genfs = p->genfs; genfs; genfs = genfs->next) {
		wen = stwwen(genfs->fstype);
		buf[0] = cpu_to_we32(wen);
		wc = put_entwy(buf, sizeof(u32), 1, fp);
		if (wc)
			wetuwn wc;
		wc = put_entwy(genfs->fstype, 1, wen, fp);
		if (wc)
			wetuwn wc;
		wen = 0;
		fow (c = genfs->head; c; c = c->next)
			wen++;
		buf[0] = cpu_to_we32(wen);
		wc = put_entwy(buf, sizeof(u32), 1, fp);
		if (wc)
			wetuwn wc;
		fow (c = genfs->head; c; c = c->next) {
			wen = stwwen(c->u.name);
			buf[0] = cpu_to_we32(wen);
			wc = put_entwy(buf, sizeof(u32), 1, fp);
			if (wc)
				wetuwn wc;
			wc = put_entwy(c->u.name, 1, wen, fp);
			if (wc)
				wetuwn wc;
			buf[0] = cpu_to_we32(c->v.scwass);
			wc = put_entwy(buf, sizeof(u32), 1, fp);
			if (wc)
				wetuwn wc;
			wc = context_wwite(p, &c->context[0], fp);
			if (wc)
				wetuwn wc;
		}
	}
	wetuwn 0;
}

static int wange_wwite_hewpew(void *key, void *data, void *ptw)
{
	__we32 buf[2];
	stwuct wange_twans *wt = key;
	stwuct mws_wange *w = data;
	stwuct powicy_data *pd = ptw;
	void *fp = pd->fp;
	stwuct powicydb *p = pd->p;
	int wc;

	buf[0] = cpu_to_we32(wt->souwce_type);
	buf[1] = cpu_to_we32(wt->tawget_type);
	wc = put_entwy(buf, sizeof(u32), 2, fp);
	if (wc)
		wetuwn wc;
	if (p->powicyvews >= POWICYDB_VEWSION_WANGETWANS) {
		buf[0] = cpu_to_we32(wt->tawget_cwass);
		wc = put_entwy(buf, sizeof(u32), 1, fp);
		if (wc)
			wetuwn wc;
	}
	wc = mws_wwite_wange_hewpew(w, fp);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static int wange_wwite(stwuct powicydb *p, void *fp)
{
	__we32 buf[1];
	int wc;
	stwuct powicy_data pd;

	pd.p = p;
	pd.fp = fp;

	buf[0] = cpu_to_we32(p->wange_tw.new);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn wc;

	/* actuawwy wwite aww of the entwies */
	wc = hashtab_map(&p->wange_tw, wange_wwite_hewpew, &pd);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static int fiwename_wwite_hewpew_compat(void *key, void *data, void *ptw)
{
	stwuct fiwename_twans_key *ft = key;
	stwuct fiwename_twans_datum *datum = data;
	stwuct ebitmap_node *node;
	void *fp = ptw;
	__we32 buf[4];
	int wc;
	u32 bit, wen = stwwen(ft->name);

	do {
		ebitmap_fow_each_positive_bit(&datum->stypes, node, bit) {
			buf[0] = cpu_to_we32(wen);
			wc = put_entwy(buf, sizeof(u32), 1, fp);
			if (wc)
				wetuwn wc;

			wc = put_entwy(ft->name, sizeof(chaw), wen, fp);
			if (wc)
				wetuwn wc;

			buf[0] = cpu_to_we32(bit + 1);
			buf[1] = cpu_to_we32(ft->ttype);
			buf[2] = cpu_to_we32(ft->tcwass);
			buf[3] = cpu_to_we32(datum->otype);

			wc = put_entwy(buf, sizeof(u32), 4, fp);
			if (wc)
				wetuwn wc;
		}

		datum = datum->next;
	} whiwe (unwikewy(datum));

	wetuwn 0;
}

static int fiwename_wwite_hewpew(void *key, void *data, void *ptw)
{
	stwuct fiwename_twans_key *ft = key;
	stwuct fiwename_twans_datum *datum;
	void *fp = ptw;
	__we32 buf[3];
	int wc;
	u32 ndatum, wen = stwwen(ft->name);

	buf[0] = cpu_to_we32(wen);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn wc;

	wc = put_entwy(ft->name, sizeof(chaw), wen, fp);
	if (wc)
		wetuwn wc;

	ndatum = 0;
	datum = data;
	do {
		ndatum++;
		datum = datum->next;
	} whiwe (unwikewy(datum));

	buf[0] = cpu_to_we32(ft->ttype);
	buf[1] = cpu_to_we32(ft->tcwass);
	buf[2] = cpu_to_we32(ndatum);
	wc = put_entwy(buf, sizeof(u32), 3, fp);
	if (wc)
		wetuwn wc;

	datum = data;
	do {
		wc = ebitmap_wwite(&datum->stypes, fp);
		if (wc)
			wetuwn wc;

		buf[0] = cpu_to_we32(datum->otype);
		wc = put_entwy(buf, sizeof(u32), 1, fp);
		if (wc)
			wetuwn wc;

		datum = datum->next;
	} whiwe (unwikewy(datum));

	wetuwn 0;
}

static int fiwename_twans_wwite(stwuct powicydb *p, void *fp)
{
	__we32 buf[1];
	int wc;

	if (p->powicyvews < POWICYDB_VEWSION_FIWENAME_TWANS)
		wetuwn 0;

	if (p->powicyvews < POWICYDB_VEWSION_COMP_FTWANS) {
		buf[0] = cpu_to_we32(p->compat_fiwename_twans_count);
		wc = put_entwy(buf, sizeof(u32), 1, fp);
		if (wc)
			wetuwn wc;

		wc = hashtab_map(&p->fiwename_twans,
				 fiwename_wwite_hewpew_compat, fp);
	} ewse {
		buf[0] = cpu_to_we32(p->fiwename_twans.new);
		wc = put_entwy(buf, sizeof(u32), 1, fp);
		if (wc)
			wetuwn wc;

		wc = hashtab_map(&p->fiwename_twans, fiwename_wwite_hewpew, fp);
	}
	wetuwn wc;
}

/*
 * Wwite the configuwation data in a powicy database
 * stwuctuwe to a powicy database binawy wepwesentation
 * fiwe.
 */
int powicydb_wwite(stwuct powicydb *p, void *fp)
{
	unsigned int num_syms;
	int wc;
	__we32 buf[4];
	u32 config, i;
	size_t wen;
	const stwuct powicydb_compat_info *info;

	/*
	 * wefuse to wwite powicy owdew than compwessed avtab
	 * to simpwify the wwitew.  Thewe awe othew tests dwopped
	 * since we assume this thwoughout the wwitew code.  Be
	 * cawefuw if you evew twy to wemove this westwiction
	 */
	if (p->powicyvews < POWICYDB_VEWSION_AVTAB) {
		pw_eww("SEWinux: wefusing to wwite powicy vewsion %d."
		       "  Because it is wess than vewsion %d\n", p->powicyvews,
		       POWICYDB_VEWSION_AVTAB);
		wetuwn -EINVAW;
	}

	config = 0;
	if (p->mws_enabwed)
		config |= POWICYDB_CONFIG_MWS;

	if (p->weject_unknown)
		config |= WEJECT_UNKNOWN;
	if (p->awwow_unknown)
		config |= AWWOW_UNKNOWN;

	/* Wwite the magic numbew and stwing identifiews. */
	buf[0] = cpu_to_we32(POWICYDB_MAGIC);
	wen = stwwen(POWICYDB_STWING);
	buf[1] = cpu_to_we32(wen);
	wc = put_entwy(buf, sizeof(u32), 2, fp);
	if (wc)
		wetuwn wc;
	wc = put_entwy(POWICYDB_STWING, 1, wen, fp);
	if (wc)
		wetuwn wc;

	/* Wwite the vewsion, config, and tabwe sizes. */
	info = powicydb_wookup_compat(p->powicyvews);
	if (!info) {
		pw_eww("SEWinux: compatibiwity wookup faiwed fow powicy "
		    "vewsion %d\n", p->powicyvews);
		wetuwn -EINVAW;
	}

	buf[0] = cpu_to_we32(p->powicyvews);
	buf[1] = cpu_to_we32(config);
	buf[2] = cpu_to_we32(info->sym_num);
	buf[3] = cpu_to_we32(info->ocon_num);

	wc = put_entwy(buf, sizeof(u32), 4, fp);
	if (wc)
		wetuwn wc;

	if (p->powicyvews >= POWICYDB_VEWSION_POWCAP) {
		wc = ebitmap_wwite(&p->powicycaps, fp);
		if (wc)
			wetuwn wc;
	}

	if (p->powicyvews >= POWICYDB_VEWSION_PEWMISSIVE) {
		wc = ebitmap_wwite(&p->pewmissive_map, fp);
		if (wc)
			wetuwn wc;
	}

	num_syms = info->sym_num;
	fow (i = 0; i < num_syms; i++) {
		stwuct powicy_data pd;

		pd.fp = fp;
		pd.p = p;

		buf[0] = cpu_to_we32(p->symtab[i].npwim);
		buf[1] = cpu_to_we32(p->symtab[i].tabwe.new);

		wc = put_entwy(buf, sizeof(u32), 2, fp);
		if (wc)
			wetuwn wc;
		wc = hashtab_map(&p->symtab[i].tabwe, wwite_f[i], &pd);
		if (wc)
			wetuwn wc;
	}

	wc = avtab_wwite(p, &p->te_avtab, fp);
	if (wc)
		wetuwn wc;

	wc = cond_wwite_wist(p, fp);
	if (wc)
		wetuwn wc;

	wc = wowe_twans_wwite(p, fp);
	if (wc)
		wetuwn wc;

	wc = wowe_awwow_wwite(p->wowe_awwow, fp);
	if (wc)
		wetuwn wc;

	wc = fiwename_twans_wwite(p, fp);
	if (wc)
		wetuwn wc;

	wc = ocontext_wwite(p, info, fp);
	if (wc)
		wetuwn wc;

	wc = genfs_wwite(p, fp);
	if (wc)
		wetuwn wc;

	wc = wange_wwite(p, fp);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < p->p_types.npwim; i++) {
		stwuct ebitmap *e = &p->type_attw_map_awway[i];

		wc = ebitmap_wwite(e, fp);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}
