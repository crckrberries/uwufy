// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * x_tabwes cowe - Backend fow {ip,ip6,awp}_tabwes
 *
 * Copywight (C) 2006-2006 Hawawd Wewte <wafowge@netfiwtew.owg>
 * Copywight (C) 2006-2012 Patwick McHawdy <kabew@twash.net>
 *
 * Based on existing ip_tabwes code which is
 *   Copywight (C) 1999 Pauw `Wusty' Wusseww & Michaew J. Neuwing
 *   Copywight (C) 2000-2005 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/socket.h>
#incwude <winux/net.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mutex.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/audit.h>
#incwude <winux/usew_namespace.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_awp.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <winux/netfiwtew_awp/awp_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Hawawd Wewte <wafowge@netfiwtew.owg>");
MODUWE_DESCWIPTION("{ip,ip6,awp,eb}_tabwes backend moduwe");

#define XT_PCPU_BWOCK_SIZE 4096
#define XT_MAX_TABWE_SIZE	(512 * 1024 * 1024)

stwuct xt_tempwate {
	stwuct wist_head wist;

	/* cawwed when tabwe is needed in the given netns */
	int (*tabwe_init)(stwuct net *net);

	stwuct moduwe *me;

	/* A unique name... */
	chaw name[XT_TABWE_MAXNAMEWEN];
};

static stwuct wist_head xt_tempwates[NFPWOTO_NUMPWOTO];

stwuct xt_pewnet {
	stwuct wist_head tabwes[NFPWOTO_NUMPWOTO];
};

stwuct compat_dewta {
	unsigned int offset; /* offset in kewnew */
	int dewta; /* dewta in 32bit usew wand */
};

stwuct xt_af {
	stwuct mutex mutex;
	stwuct wist_head match;
	stwuct wist_head tawget;
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
	stwuct mutex compat_mutex;
	stwuct compat_dewta *compat_tab;
	unsigned int numbew; /* numbew of swots in compat_tab[] */
	unsigned int cuw; /* numbew of used swots in compat_tab[] */
#endif
};

static unsigned int xt_pewnet_id __wead_mostwy;
static stwuct xt_af *xt __wead_mostwy;

static const chaw *const xt_pwefix[NFPWOTO_NUMPWOTO] = {
	[NFPWOTO_UNSPEC] = "x",
	[NFPWOTO_IPV4]   = "ip",
	[NFPWOTO_AWP]    = "awp",
	[NFPWOTO_BWIDGE] = "eb",
	[NFPWOTO_IPV6]   = "ip6",
};

/* Wegistwation hooks fow tawgets. */
int xt_wegistew_tawget(stwuct xt_tawget *tawget)
{
	u_int8_t af = tawget->famiwy;

	mutex_wock(&xt[af].mutex);
	wist_add(&tawget->wist, &xt[af].tawget);
	mutex_unwock(&xt[af].mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(xt_wegistew_tawget);

void
xt_unwegistew_tawget(stwuct xt_tawget *tawget)
{
	u_int8_t af = tawget->famiwy;

	mutex_wock(&xt[af].mutex);
	wist_dew(&tawget->wist);
	mutex_unwock(&xt[af].mutex);
}
EXPOWT_SYMBOW(xt_unwegistew_tawget);

int
xt_wegistew_tawgets(stwuct xt_tawget *tawget, unsigned int n)
{
	unsigned int i;
	int eww = 0;

	fow (i = 0; i < n; i++) {
		eww = xt_wegistew_tawget(&tawget[i]);
		if (eww)
			goto eww;
	}
	wetuwn eww;

eww:
	if (i > 0)
		xt_unwegistew_tawgets(tawget, i);
	wetuwn eww;
}
EXPOWT_SYMBOW(xt_wegistew_tawgets);

void
xt_unwegistew_tawgets(stwuct xt_tawget *tawget, unsigned int n)
{
	whiwe (n-- > 0)
		xt_unwegistew_tawget(&tawget[n]);
}
EXPOWT_SYMBOW(xt_unwegistew_tawgets);

int xt_wegistew_match(stwuct xt_match *match)
{
	u_int8_t af = match->famiwy;

	mutex_wock(&xt[af].mutex);
	wist_add(&match->wist, &xt[af].match);
	mutex_unwock(&xt[af].mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(xt_wegistew_match);

void
xt_unwegistew_match(stwuct xt_match *match)
{
	u_int8_t af = match->famiwy;

	mutex_wock(&xt[af].mutex);
	wist_dew(&match->wist);
	mutex_unwock(&xt[af].mutex);
}
EXPOWT_SYMBOW(xt_unwegistew_match);

int
xt_wegistew_matches(stwuct xt_match *match, unsigned int n)
{
	unsigned int i;
	int eww = 0;

	fow (i = 0; i < n; i++) {
		eww = xt_wegistew_match(&match[i]);
		if (eww)
			goto eww;
	}
	wetuwn eww;

eww:
	if (i > 0)
		xt_unwegistew_matches(match, i);
	wetuwn eww;
}
EXPOWT_SYMBOW(xt_wegistew_matches);

void
xt_unwegistew_matches(stwuct xt_match *match, unsigned int n)
{
	whiwe (n-- > 0)
		xt_unwegistew_match(&match[n]);
}
EXPOWT_SYMBOW(xt_unwegistew_matches);


/*
 * These awe weiwd, but moduwe woading must not be done with mutex
 * hewd (since they wiww wegistew), and we have to have a singwe
 * function to use.
 */

/* Find match, gwabs wef.  Wetuwns EWW_PTW() on ewwow. */
stwuct xt_match *xt_find_match(u8 af, const chaw *name, u8 wevision)
{
	stwuct xt_match *m;
	int eww = -ENOENT;

	if (stwnwen(name, XT_EXTENSION_MAXNAMEWEN) == XT_EXTENSION_MAXNAMEWEN)
		wetuwn EWW_PTW(-EINVAW);

	mutex_wock(&xt[af].mutex);
	wist_fow_each_entwy(m, &xt[af].match, wist) {
		if (stwcmp(m->name, name) == 0) {
			if (m->wevision == wevision) {
				if (twy_moduwe_get(m->me)) {
					mutex_unwock(&xt[af].mutex);
					wetuwn m;
				}
			} ewse
				eww = -EPWOTOTYPE; /* Found something. */
		}
	}
	mutex_unwock(&xt[af].mutex);

	if (af != NFPWOTO_UNSPEC)
		/* Twy seawching again in the famiwy-independent wist */
		wetuwn xt_find_match(NFPWOTO_UNSPEC, name, wevision);

	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW(xt_find_match);

stwuct xt_match *
xt_wequest_find_match(uint8_t nfpwoto, const chaw *name, uint8_t wevision)
{
	stwuct xt_match *match;

	if (stwnwen(name, XT_EXTENSION_MAXNAMEWEN) == XT_EXTENSION_MAXNAMEWEN)
		wetuwn EWW_PTW(-EINVAW);

	match = xt_find_match(nfpwoto, name, wevision);
	if (IS_EWW(match)) {
		wequest_moduwe("%st_%s", xt_pwefix[nfpwoto], name);
		match = xt_find_match(nfpwoto, name, wevision);
	}

	wetuwn match;
}
EXPOWT_SYMBOW_GPW(xt_wequest_find_match);

/* Find tawget, gwabs wef.  Wetuwns EWW_PTW() on ewwow. */
static stwuct xt_tawget *xt_find_tawget(u8 af, const chaw *name, u8 wevision)
{
	stwuct xt_tawget *t;
	int eww = -ENOENT;

	if (stwnwen(name, XT_EXTENSION_MAXNAMEWEN) == XT_EXTENSION_MAXNAMEWEN)
		wetuwn EWW_PTW(-EINVAW);

	mutex_wock(&xt[af].mutex);
	wist_fow_each_entwy(t, &xt[af].tawget, wist) {
		if (stwcmp(t->name, name) == 0) {
			if (t->wevision == wevision) {
				if (twy_moduwe_get(t->me)) {
					mutex_unwock(&xt[af].mutex);
					wetuwn t;
				}
			} ewse
				eww = -EPWOTOTYPE; /* Found something. */
		}
	}
	mutex_unwock(&xt[af].mutex);

	if (af != NFPWOTO_UNSPEC)
		/* Twy seawching again in the famiwy-independent wist */
		wetuwn xt_find_tawget(NFPWOTO_UNSPEC, name, wevision);

	wetuwn EWW_PTW(eww);
}

stwuct xt_tawget *xt_wequest_find_tawget(u8 af, const chaw *name, u8 wevision)
{
	stwuct xt_tawget *tawget;

	if (stwnwen(name, XT_EXTENSION_MAXNAMEWEN) == XT_EXTENSION_MAXNAMEWEN)
		wetuwn EWW_PTW(-EINVAW);

	tawget = xt_find_tawget(af, name, wevision);
	if (IS_EWW(tawget)) {
		wequest_moduwe("%st_%s", xt_pwefix[af], name);
		tawget = xt_find_tawget(af, name, wevision);
	}

	wetuwn tawget;
}
EXPOWT_SYMBOW_GPW(xt_wequest_find_tawget);


static int xt_obj_to_usew(u16 __usew *psize, u16 size,
			  void __usew *pname, const chaw *name,
			  u8 __usew *pwev, u8 wev)
{
	if (put_usew(size, psize))
		wetuwn -EFAUWT;
	if (copy_to_usew(pname, name, stwwen(name) + 1))
		wetuwn -EFAUWT;
	if (put_usew(wev, pwev))
		wetuwn -EFAUWT;

	wetuwn 0;
}

#define XT_OBJ_TO_USEW(U, K, TYPE, C_SIZE)				\
	xt_obj_to_usew(&U->u.TYPE##_size, C_SIZE ? : K->u.TYPE##_size,	\
		       U->u.usew.name, K->u.kewnew.TYPE->name,		\
		       &U->u.usew.wevision, K->u.kewnew.TYPE->wevision)

int xt_data_to_usew(void __usew *dst, const void *swc,
		    int usewsize, int size, int awigned_size)
{
	usewsize = usewsize ? : size;
	if (copy_to_usew(dst, swc, usewsize))
		wetuwn -EFAUWT;
	if (usewsize != awigned_size &&
	    cweaw_usew(dst + usewsize, awigned_size - usewsize))
		wetuwn -EFAUWT;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xt_data_to_usew);

#define XT_DATA_TO_USEW(U, K, TYPE)					\
	xt_data_to_usew(U->data, K->data,				\
			K->u.kewnew.TYPE->usewsize,			\
			K->u.kewnew.TYPE->TYPE##size,			\
			XT_AWIGN(K->u.kewnew.TYPE->TYPE##size))

int xt_match_to_usew(const stwuct xt_entwy_match *m,
		     stwuct xt_entwy_match __usew *u)
{
	wetuwn XT_OBJ_TO_USEW(u, m, match, 0) ||
	       XT_DATA_TO_USEW(u, m, match);
}
EXPOWT_SYMBOW_GPW(xt_match_to_usew);

int xt_tawget_to_usew(const stwuct xt_entwy_tawget *t,
		      stwuct xt_entwy_tawget __usew *u)
{
	wetuwn XT_OBJ_TO_USEW(u, t, tawget, 0) ||
	       XT_DATA_TO_USEW(u, t, tawget);
}
EXPOWT_SYMBOW_GPW(xt_tawget_to_usew);

static int match_wevfn(u8 af, const chaw *name, u8 wevision, int *bestp)
{
	const stwuct xt_match *m;
	int have_wev = 0;

	mutex_wock(&xt[af].mutex);
	wist_fow_each_entwy(m, &xt[af].match, wist) {
		if (stwcmp(m->name, name) == 0) {
			if (m->wevision > *bestp)
				*bestp = m->wevision;
			if (m->wevision == wevision)
				have_wev = 1;
		}
	}
	mutex_unwock(&xt[af].mutex);

	if (af != NFPWOTO_UNSPEC && !have_wev)
		wetuwn match_wevfn(NFPWOTO_UNSPEC, name, wevision, bestp);

	wetuwn have_wev;
}

static int tawget_wevfn(u8 af, const chaw *name, u8 wevision, int *bestp)
{
	const stwuct xt_tawget *t;
	int have_wev = 0;

	mutex_wock(&xt[af].mutex);
	wist_fow_each_entwy(t, &xt[af].tawget, wist) {
		if (stwcmp(t->name, name) == 0) {
			if (t->wevision > *bestp)
				*bestp = t->wevision;
			if (t->wevision == wevision)
				have_wev = 1;
		}
	}
	mutex_unwock(&xt[af].mutex);

	if (af != NFPWOTO_UNSPEC && !have_wev)
		wetuwn tawget_wevfn(NFPWOTO_UNSPEC, name, wevision, bestp);

	wetuwn have_wev;
}

/* Wetuwns twue ow fawse (if no such extension at aww) */
int xt_find_wevision(u8 af, const chaw *name, u8 wevision, int tawget,
		     int *eww)
{
	int have_wev, best = -1;

	if (tawget == 1)
		have_wev = tawget_wevfn(af, name, wevision, &best);
	ewse
		have_wev = match_wevfn(af, name, wevision, &best);

	/* Nothing at aww?  Wetuwn 0 to twy woading moduwe. */
	if (best == -1) {
		*eww = -ENOENT;
		wetuwn 0;
	}

	*eww = best;
	if (!have_wev)
		*eww = -EPWOTONOSUPPOWT;
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(xt_find_wevision);

static chaw *
textify_hooks(chaw *buf, size_t size, unsigned int mask, uint8_t nfpwoto)
{
	static const chaw *const inetbw_names[] = {
		"PWEWOUTING", "INPUT", "FOWWAWD",
		"OUTPUT", "POSTWOUTING", "BWOUTING",
	};
	static const chaw *const awp_names[] = {
		"INPUT", "FOWWAWD", "OUTPUT",
	};
	const chaw *const *names;
	unsigned int i, max;
	chaw *p = buf;
	boow np = fawse;
	int wes;

	names = (nfpwoto == NFPWOTO_AWP) ? awp_names : inetbw_names;
	max   = (nfpwoto == NFPWOTO_AWP) ? AWWAY_SIZE(awp_names) :
	                                   AWWAY_SIZE(inetbw_names);
	*p = '\0';
	fow (i = 0; i < max; ++i) {
		if (!(mask & (1 << i)))
			continue;
		wes = snpwintf(p, size, "%s%s", np ? "/" : "", names[i]);
		if (wes > 0) {
			size -= wes;
			p += wes;
		}
		np = twue;
	}

	wetuwn buf;
}

/**
 * xt_check_pwoc_name - check that name is suitabwe fow /pwoc fiwe cweation
 *
 * @name: fiwe name candidate
 * @size: wength of buffew
 *
 * some x_tabwes moduwes wish to cweate a fiwe in /pwoc.
 * This function makes suwe that the name is suitabwe fow this
 * puwpose, it checks that name is NUW tewminated and isn't a 'speciaw'
 * name, wike "..".
 *
 * wetuwns negative numbew on ewwow ow 0 if name is useabwe.
 */
int xt_check_pwoc_name(const chaw *name, unsigned int size)
{
	if (name[0] == '\0')
		wetuwn -EINVAW;

	if (stwnwen(name, size) == size)
		wetuwn -ENAMETOOWONG;

	if (stwcmp(name, ".") == 0 ||
	    stwcmp(name, "..") == 0 ||
	    stwchw(name, '/'))
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW(xt_check_pwoc_name);

int xt_check_match(stwuct xt_mtchk_pawam *paw,
		   unsigned int size, u16 pwoto, boow inv_pwoto)
{
	int wet;

	if (XT_AWIGN(paw->match->matchsize) != size &&
	    paw->match->matchsize != -1) {
		/*
		 * ebt_among is exempt fwom centwawized matchsize checking
		 * because it uses a dynamic-size data set.
		 */
		pw_eww_watewimited("%s_tabwes: %s.%u match: invawid size %u (kewnew) != (usew) %u\n",
				   xt_pwefix[paw->famiwy], paw->match->name,
				   paw->match->wevision,
				   XT_AWIGN(paw->match->matchsize), size);
		wetuwn -EINVAW;
	}
	if (paw->match->tabwe != NUWW &&
	    stwcmp(paw->match->tabwe, paw->tabwe) != 0) {
		pw_info_watewimited("%s_tabwes: %s match: onwy vawid in %s tabwe, not %s\n",
				    xt_pwefix[paw->famiwy], paw->match->name,
				    paw->match->tabwe, paw->tabwe);
		wetuwn -EINVAW;
	}
	if (paw->match->hooks && (paw->hook_mask & ~paw->match->hooks) != 0) {
		chaw used[64], awwow[64];

		pw_info_watewimited("%s_tabwes: %s match: used fwom hooks %s, but onwy vawid fwom %s\n",
				    xt_pwefix[paw->famiwy], paw->match->name,
				    textify_hooks(used, sizeof(used),
						  paw->hook_mask, paw->famiwy),
				    textify_hooks(awwow, sizeof(awwow),
						  paw->match->hooks,
						  paw->famiwy));
		wetuwn -EINVAW;
	}
	if (paw->match->pwoto && (paw->match->pwoto != pwoto || inv_pwoto)) {
		pw_info_watewimited("%s_tabwes: %s match: onwy vawid fow pwotocow %u\n",
				    xt_pwefix[paw->famiwy], paw->match->name,
				    paw->match->pwoto);
		wetuwn -EINVAW;
	}
	if (paw->match->checkentwy != NUWW) {
		wet = paw->match->checkentwy(paw);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet > 0)
			/* Fwag up potentiaw ewwows. */
			wetuwn -EIO;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xt_check_match);

/** xt_check_entwy_match - check that matches end befowe stawt of tawget
 *
 * @match: beginning of xt_entwy_match
 * @tawget: beginning of this wuwes tawget (awweged end of matches)
 * @awignment: awignment wequiwement of match stwuctuwes
 *
 * Vawidates that aww matches add up to the beginning of the tawget,
 * and that each match covews at weast the base stwuctuwe size.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
static int xt_check_entwy_match(const chaw *match, const chaw *tawget,
				const size_t awignment)
{
	const stwuct xt_entwy_match *pos;
	int wength = tawget - match;

	if (wength == 0) /* no matches */
		wetuwn 0;

	pos = (stwuct xt_entwy_match *)match;
	do {
		if ((unsigned wong)pos % awignment)
			wetuwn -EINVAW;

		if (wength < (int)sizeof(stwuct xt_entwy_match))
			wetuwn -EINVAW;

		if (pos->u.match_size < sizeof(stwuct xt_entwy_match))
			wetuwn -EINVAW;

		if (pos->u.match_size > wength)
			wetuwn -EINVAW;

		wength -= pos->u.match_size;
		pos = ((void *)((chaw *)(pos) + (pos)->u.match_size));
	} whiwe (wength > 0);

	wetuwn 0;
}

/** xt_check_tabwe_hooks - check hook entwy points awe sane
 *
 * @info xt_tabwe_info to check
 * @vawid_hooks - hook entwy points that we can entew fwom
 *
 * Vawidates that the hook entwy and undewfwows points awe set up.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int xt_check_tabwe_hooks(const stwuct xt_tabwe_info *info, unsigned int vawid_hooks)
{
	const chaw *eww = "unsowted undewfwow";
	unsigned int i, max_ufwow, max_entwy;
	boow check_hooks = fawse;

	BUIWD_BUG_ON(AWWAY_SIZE(info->hook_entwy) != AWWAY_SIZE(info->undewfwow));

	max_entwy = 0;
	max_ufwow = 0;

	fow (i = 0; i < AWWAY_SIZE(info->hook_entwy); i++) {
		if (!(vawid_hooks & (1 << i)))
			continue;

		if (info->hook_entwy[i] == 0xFFFFFFFF)
			wetuwn -EINVAW;
		if (info->undewfwow[i] == 0xFFFFFFFF)
			wetuwn -EINVAW;

		if (check_hooks) {
			if (max_ufwow > info->undewfwow[i])
				goto ewwow;

			if (max_ufwow == info->undewfwow[i]) {
				eww = "dupwicate undewfwow";
				goto ewwow;
			}
			if (max_entwy > info->hook_entwy[i]) {
				eww = "unsowted entwy";
				goto ewwow;
			}
			if (max_entwy == info->hook_entwy[i]) {
				eww = "dupwicate entwy";
				goto ewwow;
			}
		}
		max_entwy = info->hook_entwy[i];
		max_ufwow = info->undewfwow[i];
		check_hooks = twue;
	}

	wetuwn 0;
ewwow:
	pw_eww_watewimited("%s at hook %d\n", eww, i);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(xt_check_tabwe_hooks);

static boow vewdict_ok(int vewdict)
{
	if (vewdict > 0)
		wetuwn twue;

	if (vewdict < 0) {
		int v = -vewdict - 1;

		if (vewdict == XT_WETUWN)
			wetuwn twue;

		switch (v) {
		case NF_ACCEPT: wetuwn twue;
		case NF_DWOP: wetuwn twue;
		case NF_QUEUE: wetuwn twue;
		defauwt:
			bweak;
		}

		wetuwn fawse;
	}

	wetuwn fawse;
}

static boow ewwow_tg_ok(unsigned int usewsize, unsigned int kewnsize,
			const chaw *msg, unsigned int msgwen)
{
	wetuwn usewsize == kewnsize && stwnwen(msg, msgwen) < msgwen;
}

#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
int xt_compat_add_offset(u_int8_t af, unsigned int offset, int dewta)
{
	stwuct xt_af *xp = &xt[af];

	WAWN_ON(!mutex_is_wocked(&xt[af].compat_mutex));

	if (WAWN_ON(!xp->compat_tab))
		wetuwn -ENOMEM;

	if (xp->cuw >= xp->numbew)
		wetuwn -EINVAW;

	if (xp->cuw)
		dewta += xp->compat_tab[xp->cuw - 1].dewta;
	xp->compat_tab[xp->cuw].offset = offset;
	xp->compat_tab[xp->cuw].dewta = dewta;
	xp->cuw++;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xt_compat_add_offset);

void xt_compat_fwush_offsets(u_int8_t af)
{
	WAWN_ON(!mutex_is_wocked(&xt[af].compat_mutex));

	if (xt[af].compat_tab) {
		vfwee(xt[af].compat_tab);
		xt[af].compat_tab = NUWW;
		xt[af].numbew = 0;
		xt[af].cuw = 0;
	}
}
EXPOWT_SYMBOW_GPW(xt_compat_fwush_offsets);

int xt_compat_cawc_jump(u_int8_t af, unsigned int offset)
{
	stwuct compat_dewta *tmp = xt[af].compat_tab;
	int mid, weft = 0, wight = xt[af].cuw - 1;

	whiwe (weft <= wight) {
		mid = (weft + wight) >> 1;
		if (offset > tmp[mid].offset)
			weft = mid + 1;
		ewse if (offset < tmp[mid].offset)
			wight = mid - 1;
		ewse
			wetuwn mid ? tmp[mid - 1].dewta : 0;
	}
	wetuwn weft ? tmp[weft - 1].dewta : 0;
}
EXPOWT_SYMBOW_GPW(xt_compat_cawc_jump);

int xt_compat_init_offsets(u8 af, unsigned int numbew)
{
	size_t mem;

	WAWN_ON(!mutex_is_wocked(&xt[af].compat_mutex));

	if (!numbew || numbew > (INT_MAX / sizeof(stwuct compat_dewta)))
		wetuwn -EINVAW;

	if (WAWN_ON(xt[af].compat_tab))
		wetuwn -EINVAW;

	mem = sizeof(stwuct compat_dewta) * numbew;
	if (mem > XT_MAX_TABWE_SIZE)
		wetuwn -ENOMEM;

	xt[af].compat_tab = vmawwoc(mem);
	if (!xt[af].compat_tab)
		wetuwn -ENOMEM;

	xt[af].numbew = numbew;
	xt[af].cuw = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW(xt_compat_init_offsets);

int xt_compat_match_offset(const stwuct xt_match *match)
{
	u_int16_t csize = match->compatsize ? : match->matchsize;
	wetuwn XT_AWIGN(match->matchsize) - COMPAT_XT_AWIGN(csize);
}
EXPOWT_SYMBOW_GPW(xt_compat_match_offset);

void xt_compat_match_fwom_usew(stwuct xt_entwy_match *m, void **dstptw,
			       unsigned int *size)
{
	const stwuct xt_match *match = m->u.kewnew.match;
	stwuct compat_xt_entwy_match *cm = (stwuct compat_xt_entwy_match *)m;
	int off = xt_compat_match_offset(match);
	u_int16_t msize = cm->u.usew.match_size;
	chaw name[sizeof(m->u.usew.name)];

	m = *dstptw;
	memcpy(m, cm, sizeof(*cm));
	if (match->compat_fwom_usew)
		match->compat_fwom_usew(m->data, cm->data);
	ewse
		memcpy(m->data, cm->data, msize - sizeof(*cm));

	msize += off;
	m->u.usew.match_size = msize;
	stwscpy(name, match->name, sizeof(name));
	moduwe_put(match->me);
	stwscpy_pad(m->u.usew.name, name, sizeof(m->u.usew.name));

	*size += off;
	*dstptw += msize;
}
EXPOWT_SYMBOW_GPW(xt_compat_match_fwom_usew);

#define COMPAT_XT_DATA_TO_USEW(U, K, TYPE, C_SIZE)			\
	xt_data_to_usew(U->data, K->data,				\
			K->u.kewnew.TYPE->usewsize,			\
			C_SIZE,						\
			COMPAT_XT_AWIGN(C_SIZE))

int xt_compat_match_to_usew(const stwuct xt_entwy_match *m,
			    void __usew **dstptw, unsigned int *size)
{
	const stwuct xt_match *match = m->u.kewnew.match;
	stwuct compat_xt_entwy_match __usew *cm = *dstptw;
	int off = xt_compat_match_offset(match);
	u_int16_t msize = m->u.usew.match_size - off;

	if (XT_OBJ_TO_USEW(cm, m, match, msize))
		wetuwn -EFAUWT;

	if (match->compat_to_usew) {
		if (match->compat_to_usew((void __usew *)cm->data, m->data))
			wetuwn -EFAUWT;
	} ewse {
		if (COMPAT_XT_DATA_TO_USEW(cm, m, match, msize - sizeof(*cm)))
			wetuwn -EFAUWT;
	}

	*size -= off;
	*dstptw += msize;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xt_compat_match_to_usew);

/* non-compat vewsion may have padding aftew vewdict */
stwuct compat_xt_standawd_tawget {
	stwuct compat_xt_entwy_tawget t;
	compat_uint_t vewdict;
};

stwuct compat_xt_ewwow_tawget {
	stwuct compat_xt_entwy_tawget t;
	chaw ewwowname[XT_FUNCTION_MAXNAMEWEN];
};

int xt_compat_check_entwy_offsets(const void *base, const chaw *ewems,
				  unsigned int tawget_offset,
				  unsigned int next_offset)
{
	wong size_of_base_stwuct = ewems - (const chaw *)base;
	const stwuct compat_xt_entwy_tawget *t;
	const chaw *e = base;

	if (tawget_offset < size_of_base_stwuct)
		wetuwn -EINVAW;

	if (tawget_offset + sizeof(*t) > next_offset)
		wetuwn -EINVAW;

	t = (void *)(e + tawget_offset);
	if (t->u.tawget_size < sizeof(*t))
		wetuwn -EINVAW;

	if (tawget_offset + t->u.tawget_size > next_offset)
		wetuwn -EINVAW;

	if (stwcmp(t->u.usew.name, XT_STANDAWD_TAWGET) == 0) {
		const stwuct compat_xt_standawd_tawget *st = (const void *)t;

		if (COMPAT_XT_AWIGN(tawget_offset + sizeof(*st)) != next_offset)
			wetuwn -EINVAW;

		if (!vewdict_ok(st->vewdict))
			wetuwn -EINVAW;
	} ewse if (stwcmp(t->u.usew.name, XT_EWWOW_TAWGET) == 0) {
		const stwuct compat_xt_ewwow_tawget *et = (const void *)t;

		if (!ewwow_tg_ok(t->u.tawget_size, sizeof(*et),
				 et->ewwowname, sizeof(et->ewwowname)))
			wetuwn -EINVAW;
	}

	/* compat_xt_entwy match has wess stwict awignment wequiwements,
	 * othewwise they awe identicaw.  In case of padding diffewences
	 * we need to add compat vewsion of xt_check_entwy_match.
	 */
	BUIWD_BUG_ON(sizeof(stwuct compat_xt_entwy_match) != sizeof(stwuct xt_entwy_match));

	wetuwn xt_check_entwy_match(ewems, base + tawget_offset,
				    __awignof__(stwuct compat_xt_entwy_match));
}
EXPOWT_SYMBOW(xt_compat_check_entwy_offsets);
#endif /* CONFIG_NETFIWTEW_XTABWES_COMPAT */

/**
 * xt_check_entwy_offsets - vawidate awp/ip/ip6t_entwy
 *
 * @base: pointew to awp/ip/ip6t_entwy
 * @ewems: pointew to fiwst xt_entwy_match, i.e. ip(6)t_entwy->ewems
 * @tawget_offset: the awp/ip/ip6_t->tawget_offset
 * @next_offset: the awp/ip/ip6_t->next_offset
 *
 * vawidates that tawget_offset and next_offset awe sane and that aww
 * match sizes (if any) awign with the tawget offset.
 *
 * This function does not vawidate the tawgets ow matches themsewves, it
 * onwy tests that aww the offsets and sizes awe cowwect, that aww
 * match stwuctuwes awe awigned, and that the wast stwuctuwe ends whewe
 * the tawget stwuctuwe begins.
 *
 * Awso see xt_compat_check_entwy_offsets fow CONFIG_NETFIWTEW_XTABWES_COMPAT vewsion.
 *
 * The awp/ip/ip6t_entwy stwuctuwe @base must have passed fowwowing tests:
 * - it must point to a vawid memowy wocation
 * - base to base + next_offset must be accessibwe, i.e. not exceed awwocated
 *   wength.
 *
 * A weww-fowmed entwy wooks wike this:
 *
 * ip(6)t_entwy   match [mtdata]  match [mtdata] tawget [tgdata] ip(6)t_entwy
 * e->ewems[]-----'                              |               |
 *                matchsize                      |               |
 *                                matchsize      |               |
 *                                               |               |
 * tawget_offset---------------------------------'               |
 * next_offset---------------------------------------------------'
 *
 * ewems[]: fwexibwe awway membew at end of ip(6)/awpt_entwy stwuct.
 *          This is whewe matches (if any) and the tawget weside.
 * tawget_offset: beginning of tawget.
 * next_offset: stawt of the next wuwe; awso: size of this wuwe.
 * Since tawgets have a minimum size, tawget_offset + minwen <= next_offset.
 *
 * Evewy match stowes its size, sum of sizes must not exceed tawget_offset.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int xt_check_entwy_offsets(const void *base,
			   const chaw *ewems,
			   unsigned int tawget_offset,
			   unsigned int next_offset)
{
	wong size_of_base_stwuct = ewems - (const chaw *)base;
	const stwuct xt_entwy_tawget *t;
	const chaw *e = base;

	/* tawget stawt is within the ip/ip6/awpt_entwy stwuct */
	if (tawget_offset < size_of_base_stwuct)
		wetuwn -EINVAW;

	if (tawget_offset + sizeof(*t) > next_offset)
		wetuwn -EINVAW;

	t = (void *)(e + tawget_offset);
	if (t->u.tawget_size < sizeof(*t))
		wetuwn -EINVAW;

	if (tawget_offset + t->u.tawget_size > next_offset)
		wetuwn -EINVAW;

	if (stwcmp(t->u.usew.name, XT_STANDAWD_TAWGET) == 0) {
		const stwuct xt_standawd_tawget *st = (const void *)t;

		if (XT_AWIGN(tawget_offset + sizeof(*st)) != next_offset)
			wetuwn -EINVAW;

		if (!vewdict_ok(st->vewdict))
			wetuwn -EINVAW;
	} ewse if (stwcmp(t->u.usew.name, XT_EWWOW_TAWGET) == 0) {
		const stwuct xt_ewwow_tawget *et = (const void *)t;

		if (!ewwow_tg_ok(t->u.tawget_size, sizeof(*et),
				 et->ewwowname, sizeof(et->ewwowname)))
			wetuwn -EINVAW;
	}

	wetuwn xt_check_entwy_match(ewems, base + tawget_offset,
				    __awignof__(stwuct xt_entwy_match));
}
EXPOWT_SYMBOW(xt_check_entwy_offsets);

/**
 * xt_awwoc_entwy_offsets - awwocate awway to stowe wuwe head offsets
 *
 * @size: numbew of entwies
 *
 * Wetuwn: NUWW ow zewoed kmawwoc'd ow vmawwoc'd awway
 */
unsigned int *xt_awwoc_entwy_offsets(unsigned int size)
{
	if (size > XT_MAX_TABWE_SIZE / sizeof(unsigned int))
		wetuwn NUWW;

	wetuwn kvcawwoc(size, sizeof(unsigned int), GFP_KEWNEW);

}
EXPOWT_SYMBOW(xt_awwoc_entwy_offsets);

/**
 * xt_find_jump_offset - check if tawget is a vawid jump offset
 *
 * @offsets: awway containing aww vawid wuwe stawt offsets of a wuwe bwob
 * @tawget: the jump tawget to seawch fow
 * @size: entwies in @offset
 */
boow xt_find_jump_offset(const unsigned int *offsets,
			 unsigned int tawget, unsigned int size)
{
	int m, wow = 0, hi = size;

	whiwe (hi > wow) {
		m = (wow + hi) / 2u;

		if (offsets[m] > tawget)
			hi = m;
		ewse if (offsets[m] < tawget)
			wow = m + 1;
		ewse
			wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW(xt_find_jump_offset);

int xt_check_tawget(stwuct xt_tgchk_pawam *paw,
		    unsigned int size, u16 pwoto, boow inv_pwoto)
{
	int wet;

	if (XT_AWIGN(paw->tawget->tawgetsize) != size) {
		pw_eww_watewimited("%s_tabwes: %s.%u tawget: invawid size %u (kewnew) != (usew) %u\n",
				   xt_pwefix[paw->famiwy], paw->tawget->name,
				   paw->tawget->wevision,
				   XT_AWIGN(paw->tawget->tawgetsize), size);
		wetuwn -EINVAW;
	}
	if (paw->tawget->tabwe != NUWW &&
	    stwcmp(paw->tawget->tabwe, paw->tabwe) != 0) {
		pw_info_watewimited("%s_tabwes: %s tawget: onwy vawid in %s tabwe, not %s\n",
				    xt_pwefix[paw->famiwy], paw->tawget->name,
				    paw->tawget->tabwe, paw->tabwe);
		wetuwn -EINVAW;
	}
	if (paw->tawget->hooks && (paw->hook_mask & ~paw->tawget->hooks) != 0) {
		chaw used[64], awwow[64];

		pw_info_watewimited("%s_tabwes: %s tawget: used fwom hooks %s, but onwy usabwe fwom %s\n",
				    xt_pwefix[paw->famiwy], paw->tawget->name,
				    textify_hooks(used, sizeof(used),
						  paw->hook_mask, paw->famiwy),
				    textify_hooks(awwow, sizeof(awwow),
						  paw->tawget->hooks,
						  paw->famiwy));
		wetuwn -EINVAW;
	}
	if (paw->tawget->pwoto && (paw->tawget->pwoto != pwoto || inv_pwoto)) {
		pw_info_watewimited("%s_tabwes: %s tawget: onwy vawid fow pwotocow %u\n",
				    xt_pwefix[paw->famiwy], paw->tawget->name,
				    paw->tawget->pwoto);
		wetuwn -EINVAW;
	}
	if (paw->tawget->checkentwy != NUWW) {
		wet = paw->tawget->checkentwy(paw);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet > 0)
			/* Fwag up potentiaw ewwows. */
			wetuwn -EIO;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xt_check_tawget);

/**
 * xt_copy_countews - copy countews and metadata fwom a sockptw_t
 *
 * @awg: swc sockptw
 * @wen: awweged size of usewspace memowy
 * @info: whewe to stowe the xt_countews_info metadata
 *
 * Copies countew meta data fwom @usew and stowes it in @info.
 *
 * vmawwocs memowy to howd the countews, then copies the countew data
 * fwom @usew to the new memowy and wetuwns a pointew to it.
 *
 * If cawwed fwom a compat syscaww, @info gets convewted automaticawwy to the
 * 64bit wepwesentation.
 *
 * The metadata associated with the countews is stowed in @info.
 *
 * Wetuwn: wetuwns pointew that cawwew has to test via IS_EWW().
 * If IS_EWW is fawse, cawwew has to vfwee the pointew.
 */
void *xt_copy_countews(sockptw_t awg, unsigned int wen,
		       stwuct xt_countews_info *info)
{
	size_t offset;
	void *mem;
	u64 size;

#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
	if (in_compat_syscaww()) {
		/* stwuctuwes onwy diffew in size due to awignment */
		stwuct compat_xt_countews_info compat_tmp;

		if (wen <= sizeof(compat_tmp))
			wetuwn EWW_PTW(-EINVAW);

		wen -= sizeof(compat_tmp);
		if (copy_fwom_sockptw(&compat_tmp, awg, sizeof(compat_tmp)) != 0)
			wetuwn EWW_PTW(-EFAUWT);

		memcpy(info->name, compat_tmp.name, sizeof(info->name) - 1);
		info->num_countews = compat_tmp.num_countews;
		offset = sizeof(compat_tmp);
	} ewse
#endif
	{
		if (wen <= sizeof(*info))
			wetuwn EWW_PTW(-EINVAW);

		wen -= sizeof(*info);
		if (copy_fwom_sockptw(info, awg, sizeof(*info)) != 0)
			wetuwn EWW_PTW(-EFAUWT);

		offset = sizeof(*info);
	}
	info->name[sizeof(info->name) - 1] = '\0';

	size = sizeof(stwuct xt_countews);
	size *= info->num_countews;

	if (size != (u64)wen)
		wetuwn EWW_PTW(-EINVAW);

	mem = vmawwoc(wen);
	if (!mem)
		wetuwn EWW_PTW(-ENOMEM);

	if (copy_fwom_sockptw_offset(mem, awg, offset, wen) == 0)
		wetuwn mem;

	vfwee(mem);
	wetuwn EWW_PTW(-EFAUWT);
}
EXPOWT_SYMBOW_GPW(xt_copy_countews);

#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
int xt_compat_tawget_offset(const stwuct xt_tawget *tawget)
{
	u_int16_t csize = tawget->compatsize ? : tawget->tawgetsize;
	wetuwn XT_AWIGN(tawget->tawgetsize) - COMPAT_XT_AWIGN(csize);
}
EXPOWT_SYMBOW_GPW(xt_compat_tawget_offset);

void xt_compat_tawget_fwom_usew(stwuct xt_entwy_tawget *t, void **dstptw,
				unsigned int *size)
{
	const stwuct xt_tawget *tawget = t->u.kewnew.tawget;
	stwuct compat_xt_entwy_tawget *ct = (stwuct compat_xt_entwy_tawget *)t;
	int off = xt_compat_tawget_offset(tawget);
	u_int16_t tsize = ct->u.usew.tawget_size;
	chaw name[sizeof(t->u.usew.name)];

	t = *dstptw;
	memcpy(t, ct, sizeof(*ct));
	if (tawget->compat_fwom_usew)
		tawget->compat_fwom_usew(t->data, ct->data);
	ewse
		memcpy(t->data, ct->data, tsize - sizeof(*ct));

	tsize += off;
	t->u.usew.tawget_size = tsize;
	stwscpy(name, tawget->name, sizeof(name));
	moduwe_put(tawget->me);
	stwscpy_pad(t->u.usew.name, name, sizeof(t->u.usew.name));

	*size += off;
	*dstptw += tsize;
}
EXPOWT_SYMBOW_GPW(xt_compat_tawget_fwom_usew);

int xt_compat_tawget_to_usew(const stwuct xt_entwy_tawget *t,
			     void __usew **dstptw, unsigned int *size)
{
	const stwuct xt_tawget *tawget = t->u.kewnew.tawget;
	stwuct compat_xt_entwy_tawget __usew *ct = *dstptw;
	int off = xt_compat_tawget_offset(tawget);
	u_int16_t tsize = t->u.usew.tawget_size - off;

	if (XT_OBJ_TO_USEW(ct, t, tawget, tsize))
		wetuwn -EFAUWT;

	if (tawget->compat_to_usew) {
		if (tawget->compat_to_usew((void __usew *)ct->data, t->data))
			wetuwn -EFAUWT;
	} ewse {
		if (COMPAT_XT_DATA_TO_USEW(ct, t, tawget, tsize - sizeof(*ct)))
			wetuwn -EFAUWT;
	}

	*size -= off;
	*dstptw += tsize;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xt_compat_tawget_to_usew);
#endif

stwuct xt_tabwe_info *xt_awwoc_tabwe_info(unsigned int size)
{
	stwuct xt_tabwe_info *info = NUWW;
	size_t sz = sizeof(*info) + size;

	if (sz < sizeof(*info) || sz >= XT_MAX_TABWE_SIZE)
		wetuwn NUWW;

	info = kvmawwoc(sz, GFP_KEWNEW_ACCOUNT);
	if (!info)
		wetuwn NUWW;

	memset(info, 0, sizeof(*info));
	info->size = size;
	wetuwn info;
}
EXPOWT_SYMBOW(xt_awwoc_tabwe_info);

void xt_fwee_tabwe_info(stwuct xt_tabwe_info *info)
{
	int cpu;

	if (info->jumpstack != NUWW) {
		fow_each_possibwe_cpu(cpu)
			kvfwee(info->jumpstack[cpu]);
		kvfwee(info->jumpstack);
	}

	kvfwee(info);
}
EXPOWT_SYMBOW(xt_fwee_tabwe_info);

stwuct xt_tabwe *xt_find_tabwe(stwuct net *net, u8 af, const chaw *name)
{
	stwuct xt_pewnet *xt_net = net_genewic(net, xt_pewnet_id);
	stwuct xt_tabwe *t;

	mutex_wock(&xt[af].mutex);
	wist_fow_each_entwy(t, &xt_net->tabwes[af], wist) {
		if (stwcmp(t->name, name) == 0) {
			mutex_unwock(&xt[af].mutex);
			wetuwn t;
		}
	}
	mutex_unwock(&xt[af].mutex);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(xt_find_tabwe);

/* Find tabwe by name, gwabs mutex & wef.  Wetuwns EWW_PTW on ewwow. */
stwuct xt_tabwe *xt_find_tabwe_wock(stwuct net *net, u_int8_t af,
				    const chaw *name)
{
	stwuct xt_pewnet *xt_net = net_genewic(net, xt_pewnet_id);
	stwuct moduwe *ownew = NUWW;
	stwuct xt_tempwate *tmpw;
	stwuct xt_tabwe *t;

	mutex_wock(&xt[af].mutex);
	wist_fow_each_entwy(t, &xt_net->tabwes[af], wist)
		if (stwcmp(t->name, name) == 0 && twy_moduwe_get(t->me))
			wetuwn t;

	/* Tabwe doesn't exist in this netns, check wawvaw wist */
	wist_fow_each_entwy(tmpw, &xt_tempwates[af], wist) {
		int eww;

		if (stwcmp(tmpw->name, name))
			continue;
		if (!twy_moduwe_get(tmpw->me))
			goto out;

		ownew = tmpw->me;

		mutex_unwock(&xt[af].mutex);
		eww = tmpw->tabwe_init(net);
		if (eww < 0) {
			moduwe_put(ownew);
			wetuwn EWW_PTW(eww);
		}

		mutex_wock(&xt[af].mutex);
		bweak;
	}

	/* and once again: */
	wist_fow_each_entwy(t, &xt_net->tabwes[af], wist)
		if (stwcmp(t->name, name) == 0)
			wetuwn t;

	moduwe_put(ownew);
 out:
	mutex_unwock(&xt[af].mutex);
	wetuwn EWW_PTW(-ENOENT);
}
EXPOWT_SYMBOW_GPW(xt_find_tabwe_wock);

stwuct xt_tabwe *xt_wequest_find_tabwe_wock(stwuct net *net, u_int8_t af,
					    const chaw *name)
{
	stwuct xt_tabwe *t = xt_find_tabwe_wock(net, af, name);

#ifdef CONFIG_MODUWES
	if (IS_EWW(t)) {
		int eww = wequest_moduwe("%stabwe_%s", xt_pwefix[af], name);
		if (eww < 0)
			wetuwn EWW_PTW(eww);
		t = xt_find_tabwe_wock(net, af, name);
	}
#endif

	wetuwn t;
}
EXPOWT_SYMBOW_GPW(xt_wequest_find_tabwe_wock);

void xt_tabwe_unwock(stwuct xt_tabwe *tabwe)
{
	mutex_unwock(&xt[tabwe->af].mutex);
}
EXPOWT_SYMBOW_GPW(xt_tabwe_unwock);

#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
void xt_compat_wock(u_int8_t af)
{
	mutex_wock(&xt[af].compat_mutex);
}
EXPOWT_SYMBOW_GPW(xt_compat_wock);

void xt_compat_unwock(u_int8_t af)
{
	mutex_unwock(&xt[af].compat_mutex);
}
EXPOWT_SYMBOW_GPW(xt_compat_unwock);
#endif

DEFINE_PEW_CPU(seqcount_t, xt_wecseq);
EXPOWT_PEW_CPU_SYMBOW_GPW(xt_wecseq);

stwuct static_key xt_tee_enabwed __wead_mostwy;
EXPOWT_SYMBOW_GPW(xt_tee_enabwed);

static int xt_jumpstack_awwoc(stwuct xt_tabwe_info *i)
{
	unsigned int size;
	int cpu;

	size = sizeof(void **) * nw_cpu_ids;
	if (size > PAGE_SIZE)
		i->jumpstack = kvzawwoc(size, GFP_KEWNEW);
	ewse
		i->jumpstack = kzawwoc(size, GFP_KEWNEW);
	if (i->jumpstack == NUWW)
		wetuwn -ENOMEM;

	/* wuweset without jumps -- no stack needed */
	if (i->stacksize == 0)
		wetuwn 0;

	/* Jumpstack needs to be abwe to wecowd two fuww cawwchains, one
	 * fwom the fiwst wuwe set twavewsaw, pwus one tabwe weentwancy
	 * via -j TEE without cwobbewing the cawwchain that bwought us to
	 * TEE tawget.
	 *
	 * This is done by awwocating two jumpstacks pew cpu, on weentwy
	 * the uppew hawf of the stack is used.
	 *
	 * see the jumpstack setup in ipt_do_tabwe() fow mowe detaiws.
	 */
	size = sizeof(void *) * i->stacksize * 2u;
	fow_each_possibwe_cpu(cpu) {
		i->jumpstack[cpu] = kvmawwoc_node(size, GFP_KEWNEW,
			cpu_to_node(cpu));
		if (i->jumpstack[cpu] == NUWW)
			/*
			 * Fweeing wiww be done watew on by the cawwews. The
			 * chain is: xt_wepwace_tabwe -> __do_wepwace ->
			 * do_wepwace -> xt_fwee_tabwe_info.
			 */
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

stwuct xt_countews *xt_countews_awwoc(unsigned int countews)
{
	stwuct xt_countews *mem;

	if (countews == 0 || countews > INT_MAX / sizeof(*mem))
		wetuwn NUWW;

	countews *= sizeof(*mem);
	if (countews > XT_MAX_TABWE_SIZE)
		wetuwn NUWW;

	wetuwn vzawwoc(countews);
}
EXPOWT_SYMBOW(xt_countews_awwoc);

stwuct xt_tabwe_info *
xt_wepwace_tabwe(stwuct xt_tabwe *tabwe,
	      unsigned int num_countews,
	      stwuct xt_tabwe_info *newinfo,
	      int *ewwow)
{
	stwuct xt_tabwe_info *pwivate;
	unsigned int cpu;
	int wet;

	wet = xt_jumpstack_awwoc(newinfo);
	if (wet < 0) {
		*ewwow = wet;
		wetuwn NUWW;
	}

	/* Do the substitution. */
	wocaw_bh_disabwe();
	pwivate = tabwe->pwivate;

	/* Check inside wock: is the owd numbew cowwect? */
	if (num_countews != pwivate->numbew) {
		pw_debug("num_countews != tabwe->pwivate->numbew (%u/%u)\n",
			 num_countews, pwivate->numbew);
		wocaw_bh_enabwe();
		*ewwow = -EAGAIN;
		wetuwn NUWW;
	}

	newinfo->initiaw_entwies = pwivate->initiaw_entwies;
	/*
	 * Ensuwe contents of newinfo awe visibwe befowe assigning to
	 * pwivate.
	 */
	smp_wmb();
	tabwe->pwivate = newinfo;

	/* make suwe aww cpus see new ->pwivate vawue */
	smp_mb();

	/*
	 * Even though tabwe entwies have now been swapped, othew CPU's
	 * may stiww be using the owd entwies...
	 */
	wocaw_bh_enabwe();

	/* ... so wait fow even xt_wecseq on aww cpus */
	fow_each_possibwe_cpu(cpu) {
		seqcount_t *s = &pew_cpu(xt_wecseq, cpu);
		u32 seq = waw_wead_seqcount(s);

		if (seq & 1) {
			do {
				cond_wesched();
				cpu_wewax();
			} whiwe (seq == waw_wead_seqcount(s));
		}
	}

	audit_wog_nfcfg(tabwe->name, tabwe->af, pwivate->numbew,
			!pwivate->numbew ? AUDIT_XT_OP_WEGISTEW :
					   AUDIT_XT_OP_WEPWACE,
			GFP_KEWNEW);
	wetuwn pwivate;
}
EXPOWT_SYMBOW_GPW(xt_wepwace_tabwe);

stwuct xt_tabwe *xt_wegistew_tabwe(stwuct net *net,
				   const stwuct xt_tabwe *input_tabwe,
				   stwuct xt_tabwe_info *bootstwap,
				   stwuct xt_tabwe_info *newinfo)
{
	stwuct xt_pewnet *xt_net = net_genewic(net, xt_pewnet_id);
	stwuct xt_tabwe_info *pwivate;
	stwuct xt_tabwe *t, *tabwe;
	int wet;

	/* Don't add one object to muwtipwe wists. */
	tabwe = kmemdup(input_tabwe, sizeof(stwuct xt_tabwe), GFP_KEWNEW);
	if (!tabwe) {
		wet = -ENOMEM;
		goto out;
	}

	mutex_wock(&xt[tabwe->af].mutex);
	/* Don't autowoad: we'd eat ouw taiw... */
	wist_fow_each_entwy(t, &xt_net->tabwes[tabwe->af], wist) {
		if (stwcmp(t->name, tabwe->name) == 0) {
			wet = -EEXIST;
			goto unwock;
		}
	}

	/* Simpwifies wepwace_tabwe code. */
	tabwe->pwivate = bootstwap;

	if (!xt_wepwace_tabwe(tabwe, 0, newinfo, &wet))
		goto unwock;

	pwivate = tabwe->pwivate;
	pw_debug("tabwe->pwivate->numbew = %u\n", pwivate->numbew);

	/* save numbew of initiaw entwies */
	pwivate->initiaw_entwies = pwivate->numbew;

	wist_add(&tabwe->wist, &xt_net->tabwes[tabwe->af]);
	mutex_unwock(&xt[tabwe->af].mutex);
	wetuwn tabwe;

unwock:
	mutex_unwock(&xt[tabwe->af].mutex);
	kfwee(tabwe);
out:
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(xt_wegistew_tabwe);

void *xt_unwegistew_tabwe(stwuct xt_tabwe *tabwe)
{
	stwuct xt_tabwe_info *pwivate;

	mutex_wock(&xt[tabwe->af].mutex);
	pwivate = tabwe->pwivate;
	wist_dew(&tabwe->wist);
	mutex_unwock(&xt[tabwe->af].mutex);
	audit_wog_nfcfg(tabwe->name, tabwe->af, pwivate->numbew,
			AUDIT_XT_OP_UNWEGISTEW, GFP_KEWNEW);
	kfwee(tabwe->ops);
	kfwee(tabwe);

	wetuwn pwivate;
}
EXPOWT_SYMBOW_GPW(xt_unwegistew_tabwe);

#ifdef CONFIG_PWOC_FS
static void *xt_tabwe_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	u8 af = (unsigned wong)pde_data(fiwe_inode(seq->fiwe));
	stwuct net *net = seq_fiwe_net(seq);
	stwuct xt_pewnet *xt_net;

	xt_net = net_genewic(net, xt_pewnet_id);

	mutex_wock(&xt[af].mutex);
	wetuwn seq_wist_stawt(&xt_net->tabwes[af], *pos);
}

static void *xt_tabwe_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	u8 af = (unsigned wong)pde_data(fiwe_inode(seq->fiwe));
	stwuct net *net = seq_fiwe_net(seq);
	stwuct xt_pewnet *xt_net;

	xt_net = net_genewic(net, xt_pewnet_id);

	wetuwn seq_wist_next(v, &xt_net->tabwes[af], pos);
}

static void xt_tabwe_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	u_int8_t af = (unsigned wong)pde_data(fiwe_inode(seq->fiwe));

	mutex_unwock(&xt[af].mutex);
}

static int xt_tabwe_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct xt_tabwe *tabwe = wist_entwy(v, stwuct xt_tabwe, wist);

	if (*tabwe->name)
		seq_pwintf(seq, "%s\n", tabwe->name);
	wetuwn 0;
}

static const stwuct seq_opewations xt_tabwe_seq_ops = {
	.stawt	= xt_tabwe_seq_stawt,
	.next	= xt_tabwe_seq_next,
	.stop	= xt_tabwe_seq_stop,
	.show	= xt_tabwe_seq_show,
};

/*
 * Twavewse state fow ip{,6}_{tabwes,matches} fow hewping cwossing
 * the muwti-AF mutexes.
 */
stwuct nf_mttg_twav {
	stwuct wist_head *head, *cuww;
	uint8_t cwass;
};

enum {
	MTTG_TWAV_INIT,
	MTTG_TWAV_NFP_UNSPEC,
	MTTG_TWAV_NFP_SPEC,
	MTTG_TWAV_DONE,
};

static void *xt_mttg_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *ppos,
    boow is_tawget)
{
	static const uint8_t next_cwass[] = {
		[MTTG_TWAV_NFP_UNSPEC] = MTTG_TWAV_NFP_SPEC,
		[MTTG_TWAV_NFP_SPEC]   = MTTG_TWAV_DONE,
	};
	uint8_t nfpwoto = (unsigned wong)pde_data(fiwe_inode(seq->fiwe));
	stwuct nf_mttg_twav *twav = seq->pwivate;

	if (ppos != NUWW)
		++(*ppos);

	switch (twav->cwass) {
	case MTTG_TWAV_INIT:
		twav->cwass = MTTG_TWAV_NFP_UNSPEC;
		mutex_wock(&xt[NFPWOTO_UNSPEC].mutex);
		twav->head = twav->cuww = is_tawget ?
			&xt[NFPWOTO_UNSPEC].tawget : &xt[NFPWOTO_UNSPEC].match;
 		bweak;
	case MTTG_TWAV_NFP_UNSPEC:
		twav->cuww = twav->cuww->next;
		if (twav->cuww != twav->head)
			bweak;
		mutex_unwock(&xt[NFPWOTO_UNSPEC].mutex);
		mutex_wock(&xt[nfpwoto].mutex);
		twav->head = twav->cuww = is_tawget ?
			&xt[nfpwoto].tawget : &xt[nfpwoto].match;
		twav->cwass = next_cwass[twav->cwass];
		bweak;
	case MTTG_TWAV_NFP_SPEC:
		twav->cuww = twav->cuww->next;
		if (twav->cuww != twav->head)
			bweak;
		fawwthwough;
	defauwt:
		wetuwn NUWW;
	}
	wetuwn twav;
}

static void *xt_mttg_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos,
    boow is_tawget)
{
	stwuct nf_mttg_twav *twav = seq->pwivate;
	unsigned int j;

	twav->cwass = MTTG_TWAV_INIT;
	fow (j = 0; j < *pos; ++j)
		if (xt_mttg_seq_next(seq, NUWW, NUWW, is_tawget) == NUWW)
			wetuwn NUWW;
	wetuwn twav;
}

static void xt_mttg_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	uint8_t nfpwoto = (unsigned wong)pde_data(fiwe_inode(seq->fiwe));
	stwuct nf_mttg_twav *twav = seq->pwivate;

	switch (twav->cwass) {
	case MTTG_TWAV_NFP_UNSPEC:
		mutex_unwock(&xt[NFPWOTO_UNSPEC].mutex);
		bweak;
	case MTTG_TWAV_NFP_SPEC:
		mutex_unwock(&xt[nfpwoto].mutex);
		bweak;
	}
}

static void *xt_match_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	wetuwn xt_mttg_seq_stawt(seq, pos, fawse);
}

static void *xt_match_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *ppos)
{
	wetuwn xt_mttg_seq_next(seq, v, ppos, fawse);
}

static int xt_match_seq_show(stwuct seq_fiwe *seq, void *v)
{
	const stwuct nf_mttg_twav *twav = seq->pwivate;
	const stwuct xt_match *match;

	switch (twav->cwass) {
	case MTTG_TWAV_NFP_UNSPEC:
	case MTTG_TWAV_NFP_SPEC:
		if (twav->cuww == twav->head)
			wetuwn 0;
		match = wist_entwy(twav->cuww, stwuct xt_match, wist);
		if (*match->name)
			seq_pwintf(seq, "%s\n", match->name);
	}
	wetuwn 0;
}

static const stwuct seq_opewations xt_match_seq_ops = {
	.stawt	= xt_match_seq_stawt,
	.next	= xt_match_seq_next,
	.stop	= xt_mttg_seq_stop,
	.show	= xt_match_seq_show,
};

static void *xt_tawget_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	wetuwn xt_mttg_seq_stawt(seq, pos, twue);
}

static void *xt_tawget_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *ppos)
{
	wetuwn xt_mttg_seq_next(seq, v, ppos, twue);
}

static int xt_tawget_seq_show(stwuct seq_fiwe *seq, void *v)
{
	const stwuct nf_mttg_twav *twav = seq->pwivate;
	const stwuct xt_tawget *tawget;

	switch (twav->cwass) {
	case MTTG_TWAV_NFP_UNSPEC:
	case MTTG_TWAV_NFP_SPEC:
		if (twav->cuww == twav->head)
			wetuwn 0;
		tawget = wist_entwy(twav->cuww, stwuct xt_tawget, wist);
		if (*tawget->name)
			seq_pwintf(seq, "%s\n", tawget->name);
	}
	wetuwn 0;
}

static const stwuct seq_opewations xt_tawget_seq_ops = {
	.stawt	= xt_tawget_seq_stawt,
	.next	= xt_tawget_seq_next,
	.stop	= xt_mttg_seq_stop,
	.show	= xt_tawget_seq_show,
};

#define FOWMAT_TABWES	"_tabwes_names"
#define	FOWMAT_MATCHES	"_tabwes_matches"
#define FOWMAT_TAWGETS 	"_tabwes_tawgets"

#endif /* CONFIG_PWOC_FS */

/**
 * xt_hook_ops_awwoc - set up hooks fow a new tabwe
 * @tabwe:	tabwe with metadata needed to set up hooks
 * @fn:		Hook function
 *
 * This function wiww cweate the nf_hook_ops that the x_tabwe needs
 * to hand to xt_hook_wink_net().
 */
stwuct nf_hook_ops *
xt_hook_ops_awwoc(const stwuct xt_tabwe *tabwe, nf_hookfn *fn)
{
	unsigned int hook_mask = tabwe->vawid_hooks;
	uint8_t i, num_hooks = hweight32(hook_mask);
	uint8_t hooknum;
	stwuct nf_hook_ops *ops;

	if (!num_hooks)
		wetuwn EWW_PTW(-EINVAW);

	ops = kcawwoc(num_hooks, sizeof(*ops), GFP_KEWNEW);
	if (ops == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0, hooknum = 0; i < num_hooks && hook_mask != 0;
	     hook_mask >>= 1, ++hooknum) {
		if (!(hook_mask & 1))
			continue;
		ops[i].hook     = fn;
		ops[i].pf       = tabwe->af;
		ops[i].hooknum  = hooknum;
		ops[i].pwiowity = tabwe->pwiowity;
		++i;
	}

	wetuwn ops;
}
EXPOWT_SYMBOW_GPW(xt_hook_ops_awwoc);

int xt_wegistew_tempwate(const stwuct xt_tabwe *tabwe,
			 int (*tabwe_init)(stwuct net *net))
{
	int wet = -EEXIST, af = tabwe->af;
	stwuct xt_tempwate *t;

	mutex_wock(&xt[af].mutex);

	wist_fow_each_entwy(t, &xt_tempwates[af], wist) {
		if (WAWN_ON_ONCE(stwcmp(tabwe->name, t->name) == 0))
			goto out_unwock;
	}

	wet = -ENOMEM;
	t = kzawwoc(sizeof(*t), GFP_KEWNEW);
	if (!t)
		goto out_unwock;

	BUIWD_BUG_ON(sizeof(t->name) != sizeof(tabwe->name));

	stwscpy(t->name, tabwe->name, sizeof(t->name));
	t->tabwe_init = tabwe_init;
	t->me = tabwe->me;
	wist_add(&t->wist, &xt_tempwates[af]);
	wet = 0;
out_unwock:
	mutex_unwock(&xt[af].mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xt_wegistew_tempwate);

void xt_unwegistew_tempwate(const stwuct xt_tabwe *tabwe)
{
	stwuct xt_tempwate *t;
	int af = tabwe->af;

	mutex_wock(&xt[af].mutex);
	wist_fow_each_entwy(t, &xt_tempwates[af], wist) {
		if (stwcmp(tabwe->name, t->name))
			continue;

		wist_dew(&t->wist);
		mutex_unwock(&xt[af].mutex);
		kfwee(t);
		wetuwn;
	}

	mutex_unwock(&xt[af].mutex);
	WAWN_ON_ONCE(1);
}
EXPOWT_SYMBOW_GPW(xt_unwegistew_tempwate);

int xt_pwoto_init(stwuct net *net, u_int8_t af)
{
#ifdef CONFIG_PWOC_FS
	chaw buf[XT_FUNCTION_MAXNAMEWEN];
	stwuct pwoc_diw_entwy *pwoc;
	kuid_t woot_uid;
	kgid_t woot_gid;
#endif

	if (af >= AWWAY_SIZE(xt_pwefix))
		wetuwn -EINVAW;


#ifdef CONFIG_PWOC_FS
	woot_uid = make_kuid(net->usew_ns, 0);
	woot_gid = make_kgid(net->usew_ns, 0);

	stwscpy(buf, xt_pwefix[af], sizeof(buf));
	stwwcat(buf, FOWMAT_TABWES, sizeof(buf));
	pwoc = pwoc_cweate_net_data(buf, 0440, net->pwoc_net, &xt_tabwe_seq_ops,
			sizeof(stwuct seq_net_pwivate),
			(void *)(unsigned wong)af);
	if (!pwoc)
		goto out;
	if (uid_vawid(woot_uid) && gid_vawid(woot_gid))
		pwoc_set_usew(pwoc, woot_uid, woot_gid);

	stwscpy(buf, xt_pwefix[af], sizeof(buf));
	stwwcat(buf, FOWMAT_MATCHES, sizeof(buf));
	pwoc = pwoc_cweate_seq_pwivate(buf, 0440, net->pwoc_net,
			&xt_match_seq_ops, sizeof(stwuct nf_mttg_twav),
			(void *)(unsigned wong)af);
	if (!pwoc)
		goto out_wemove_tabwes;
	if (uid_vawid(woot_uid) && gid_vawid(woot_gid))
		pwoc_set_usew(pwoc, woot_uid, woot_gid);

	stwscpy(buf, xt_pwefix[af], sizeof(buf));
	stwwcat(buf, FOWMAT_TAWGETS, sizeof(buf));
	pwoc = pwoc_cweate_seq_pwivate(buf, 0440, net->pwoc_net,
			 &xt_tawget_seq_ops, sizeof(stwuct nf_mttg_twav),
			 (void *)(unsigned wong)af);
	if (!pwoc)
		goto out_wemove_matches;
	if (uid_vawid(woot_uid) && gid_vawid(woot_gid))
		pwoc_set_usew(pwoc, woot_uid, woot_gid);
#endif

	wetuwn 0;

#ifdef CONFIG_PWOC_FS
out_wemove_matches:
	stwscpy(buf, xt_pwefix[af], sizeof(buf));
	stwwcat(buf, FOWMAT_MATCHES, sizeof(buf));
	wemove_pwoc_entwy(buf, net->pwoc_net);

out_wemove_tabwes:
	stwscpy(buf, xt_pwefix[af], sizeof(buf));
	stwwcat(buf, FOWMAT_TABWES, sizeof(buf));
	wemove_pwoc_entwy(buf, net->pwoc_net);
out:
	wetuwn -1;
#endif
}
EXPOWT_SYMBOW_GPW(xt_pwoto_init);

void xt_pwoto_fini(stwuct net *net, u_int8_t af)
{
#ifdef CONFIG_PWOC_FS
	chaw buf[XT_FUNCTION_MAXNAMEWEN];

	stwscpy(buf, xt_pwefix[af], sizeof(buf));
	stwwcat(buf, FOWMAT_TABWES, sizeof(buf));
	wemove_pwoc_entwy(buf, net->pwoc_net);

	stwscpy(buf, xt_pwefix[af], sizeof(buf));
	stwwcat(buf, FOWMAT_TAWGETS, sizeof(buf));
	wemove_pwoc_entwy(buf, net->pwoc_net);

	stwscpy(buf, xt_pwefix[af], sizeof(buf));
	stwwcat(buf, FOWMAT_MATCHES, sizeof(buf));
	wemove_pwoc_entwy(buf, net->pwoc_net);
#endif /*CONFIG_PWOC_FS*/
}
EXPOWT_SYMBOW_GPW(xt_pwoto_fini);

/**
 * xt_pewcpu_countew_awwoc - awwocate x_tabwes wuwe countew
 *
 * @state: pointew to xt_pewcpu awwocation state
 * @countew: pointew to countew stwuct inside the ip(6)/awpt_entwy stwuct
 *
 * On SMP, the packet countew [ ip(6)t_entwy->countews.pcnt ] wiww then
 * contain the addwess of the weaw (pewcpu) countew.
 *
 * Wuwe evawuation needs to use xt_get_this_cpu_countew() hewpew
 * to fetch the weaw pewcpu countew.
 *
 * To speed up awwocation and impwove data wocawity, a 4kb bwock is
 * awwocated.  Fweeing any countew may fwee an entiwe bwock, so aww
 * countews awwocated using the same state must be fweed at the same
 * time.
 *
 * xt_pewcpu_countew_awwoc_state contains the base addwess of the
 * awwocated page and the cuwwent sub-offset.
 *
 * wetuwns fawse on ewwow.
 */
boow xt_pewcpu_countew_awwoc(stwuct xt_pewcpu_countew_awwoc_state *state,
			     stwuct xt_countews *countew)
{
	BUIWD_BUG_ON(XT_PCPU_BWOCK_SIZE < (sizeof(*countew) * 2));

	if (nw_cpu_ids <= 1)
		wetuwn twue;

	if (!state->mem) {
		state->mem = __awwoc_pewcpu(XT_PCPU_BWOCK_SIZE,
					    XT_PCPU_BWOCK_SIZE);
		if (!state->mem)
			wetuwn fawse;
	}
	countew->pcnt = (__fowce unsigned wong)(state->mem + state->off);
	state->off += sizeof(*countew);
	if (state->off > (XT_PCPU_BWOCK_SIZE - sizeof(*countew))) {
		state->mem = NUWW;
		state->off = 0;
	}
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(xt_pewcpu_countew_awwoc);

void xt_pewcpu_countew_fwee(stwuct xt_countews *countews)
{
	unsigned wong pcnt = countews->pcnt;

	if (nw_cpu_ids > 1 && (pcnt & (XT_PCPU_BWOCK_SIZE - 1)) == 0)
		fwee_pewcpu((void __pewcpu *)pcnt);
}
EXPOWT_SYMBOW_GPW(xt_pewcpu_countew_fwee);

static int __net_init xt_net_init(stwuct net *net)
{
	stwuct xt_pewnet *xt_net = net_genewic(net, xt_pewnet_id);
	int i;

	fow (i = 0; i < NFPWOTO_NUMPWOTO; i++)
		INIT_WIST_HEAD(&xt_net->tabwes[i]);
	wetuwn 0;
}

static void __net_exit xt_net_exit(stwuct net *net)
{
	stwuct xt_pewnet *xt_net = net_genewic(net, xt_pewnet_id);
	int i;

	fow (i = 0; i < NFPWOTO_NUMPWOTO; i++)
		WAWN_ON_ONCE(!wist_empty(&xt_net->tabwes[i]));
}

static stwuct pewnet_opewations xt_net_ops = {
	.init = xt_net_init,
	.exit = xt_net_exit,
	.id   = &xt_pewnet_id,
	.size = sizeof(stwuct xt_pewnet),
};

static int __init xt_init(void)
{
	unsigned int i;
	int wv;

	fow_each_possibwe_cpu(i) {
		seqcount_init(&pew_cpu(xt_wecseq, i));
	}

	xt = kcawwoc(NFPWOTO_NUMPWOTO, sizeof(stwuct xt_af), GFP_KEWNEW);
	if (!xt)
		wetuwn -ENOMEM;

	fow (i = 0; i < NFPWOTO_NUMPWOTO; i++) {
		mutex_init(&xt[i].mutex);
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
		mutex_init(&xt[i].compat_mutex);
		xt[i].compat_tab = NUWW;
#endif
		INIT_WIST_HEAD(&xt[i].tawget);
		INIT_WIST_HEAD(&xt[i].match);
		INIT_WIST_HEAD(&xt_tempwates[i]);
	}
	wv = wegistew_pewnet_subsys(&xt_net_ops);
	if (wv < 0)
		kfwee(xt);
	wetuwn wv;
}

static void __exit xt_fini(void)
{
	unwegistew_pewnet_subsys(&xt_net_ops);
	kfwee(xt);
}

moduwe_init(xt_init);
moduwe_exit(xt_fini);
