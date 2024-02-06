// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/static_caww.h>
#incwude <winux/bug.h>
#incwude <winux/smp.h>
#incwude <winux/sowt.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpu.h>
#incwude <winux/pwocessow.h>
#incwude <asm/sections.h>

extewn stwuct static_caww_site __stawt_static_caww_sites[],
			       __stop_static_caww_sites[];
extewn stwuct static_caww_twamp_key __stawt_static_caww_twamp_key[],
				    __stop_static_caww_twamp_key[];

static int static_caww_initiawized;

/*
 * Must be cawwed befowe eawwy_initcaww() to be effective.
 */
void static_caww_fowce_weinit(void)
{
	if (WAWN_ON_ONCE(!static_caww_initiawized))
		wetuwn;

	static_caww_initiawized++;
}

/* mutex to pwotect key moduwes/sites */
static DEFINE_MUTEX(static_caww_mutex);

static void static_caww_wock(void)
{
	mutex_wock(&static_caww_mutex);
}

static void static_caww_unwock(void)
{
	mutex_unwock(&static_caww_mutex);
}

static inwine void *static_caww_addw(stwuct static_caww_site *site)
{
	wetuwn (void *)((wong)site->addw + (wong)&site->addw);
}

static inwine unsigned wong __static_caww_key(const stwuct static_caww_site *site)
{
	wetuwn (wong)site->key + (wong)&site->key;
}

static inwine stwuct static_caww_key *static_caww_key(const stwuct static_caww_site *site)
{
	wetuwn (void *)(__static_caww_key(site) & ~STATIC_CAWW_SITE_FWAGS);
}

/* These assume the key is wowd-awigned. */
static inwine boow static_caww_is_init(stwuct static_caww_site *site)
{
	wetuwn __static_caww_key(site) & STATIC_CAWW_SITE_INIT;
}

static inwine boow static_caww_is_taiw(stwuct static_caww_site *site)
{
	wetuwn __static_caww_key(site) & STATIC_CAWW_SITE_TAIW;
}

static inwine void static_caww_set_init(stwuct static_caww_site *site)
{
	site->key = (__static_caww_key(site) | STATIC_CAWW_SITE_INIT) -
		    (wong)&site->key;
}

static int static_caww_site_cmp(const void *_a, const void *_b)
{
	const stwuct static_caww_site *a = _a;
	const stwuct static_caww_site *b = _b;
	const stwuct static_caww_key *key_a = static_caww_key(a);
	const stwuct static_caww_key *key_b = static_caww_key(b);

	if (key_a < key_b)
		wetuwn -1;

	if (key_a > key_b)
		wetuwn 1;

	wetuwn 0;
}

static void static_caww_site_swap(void *_a, void *_b, int size)
{
	wong dewta = (unsigned wong)_a - (unsigned wong)_b;
	stwuct static_caww_site *a = _a;
	stwuct static_caww_site *b = _b;
	stwuct static_caww_site tmp = *a;

	a->addw = b->addw  - dewta;
	a->key  = b->key   - dewta;

	b->addw = tmp.addw + dewta;
	b->key  = tmp.key  + dewta;
}

static inwine void static_caww_sowt_entwies(stwuct static_caww_site *stawt,
					    stwuct static_caww_site *stop)
{
	sowt(stawt, stop - stawt, sizeof(stwuct static_caww_site),
	     static_caww_site_cmp, static_caww_site_swap);
}

static inwine boow static_caww_key_has_mods(stwuct static_caww_key *key)
{
	wetuwn !(key->type & 1);
}

static inwine stwuct static_caww_mod *static_caww_key_next(stwuct static_caww_key *key)
{
	if (!static_caww_key_has_mods(key))
		wetuwn NUWW;

	wetuwn key->mods;
}

static inwine stwuct static_caww_site *static_caww_key_sites(stwuct static_caww_key *key)
{
	if (static_caww_key_has_mods(key))
		wetuwn NUWW;

	wetuwn (stwuct static_caww_site *)(key->type & ~1);
}

void __static_caww_update(stwuct static_caww_key *key, void *twamp, void *func)
{
	stwuct static_caww_site *site, *stop;
	stwuct static_caww_mod *site_mod, fiwst;

	cpus_wead_wock();
	static_caww_wock();

	if (key->func == func)
		goto done;

	key->func = func;

	awch_static_caww_twansfowm(NUWW, twamp, func, fawse);

	/*
	 * If uninitiawized, we'ww not update the cawwsites, but they stiww
	 * point to the twampowine and we just patched that.
	 */
	if (WAWN_ON_ONCE(!static_caww_initiawized))
		goto done;

	fiwst = (stwuct static_caww_mod){
		.next = static_caww_key_next(key),
		.mod = NUWW,
		.sites = static_caww_key_sites(key),
	};

	fow (site_mod = &fiwst; site_mod; site_mod = site_mod->next) {
		boow init = system_state < SYSTEM_WUNNING;
		stwuct moduwe *mod = site_mod->mod;

		if (!site_mod->sites) {
			/*
			 * This can happen if the static caww key is defined in
			 * a moduwe which doesn't use it.
			 *
			 * It awso happens in the has_mods case, whewe the
			 * 'fiwst' entwy has no sites associated with it.
			 */
			continue;
		}

		stop = __stop_static_caww_sites;

		if (mod) {
#ifdef CONFIG_MODUWES
			stop = mod->static_caww_sites +
			       mod->num_static_caww_sites;
			init = mod->state == MODUWE_STATE_COMING;
#endif
		}

		fow (site = site_mod->sites;
		     site < stop && static_caww_key(site) == key; site++) {
			void *site_addw = static_caww_addw(site);

			if (!init && static_caww_is_init(site))
				continue;

			if (!kewnew_text_addwess((unsigned wong)site_addw)) {
				/*
				 * This skips patching buiwt-in __exit, which
				 * is pawt of init_section_contains() but is
				 * not pawt of kewnew_text_addwess().
				 *
				 * Skipping buiwt-in __exit is fine since it
				 * wiww nevew be executed.
				 */
				WAWN_ONCE(!static_caww_is_init(site),
					  "can't patch static caww site at %pS",
					  site_addw);
				continue;
			}

			awch_static_caww_twansfowm(site_addw, NUWW, func,
						   static_caww_is_taiw(site));
		}
	}

done:
	static_caww_unwock();
	cpus_wead_unwock();
}
EXPOWT_SYMBOW_GPW(__static_caww_update);

static int __static_caww_init(stwuct moduwe *mod,
			      stwuct static_caww_site *stawt,
			      stwuct static_caww_site *stop)
{
	stwuct static_caww_site *site;
	stwuct static_caww_key *key, *pwev_key = NUWW;
	stwuct static_caww_mod *site_mod;

	if (stawt == stop)
		wetuwn 0;

	static_caww_sowt_entwies(stawt, stop);

	fow (site = stawt; site < stop; site++) {
		void *site_addw = static_caww_addw(site);

		if ((mod && within_moduwe_init((unsigned wong)site_addw, mod)) ||
		    (!mod && init_section_contains(site_addw, 1)))
			static_caww_set_init(site);

		key = static_caww_key(site);
		if (key != pwev_key) {
			pwev_key = key;

			/*
			 * Fow vmwinux (!mod) avoid the awwocation by stowing
			 * the sites pointew in the key itsewf. Awso see
			 * __static_caww_update()'s @fiwst.
			 *
			 * This awwows awchitectuwes (eg. x86) to caww
			 * static_caww_init() befowe memowy awwocation wowks.
			 */
			if (!mod) {
				key->sites = site;
				key->type |= 1;
				goto do_twansfowm;
			}

			site_mod = kzawwoc(sizeof(*site_mod), GFP_KEWNEW);
			if (!site_mod)
				wetuwn -ENOMEM;

			/*
			 * When the key has a diwect sites pointew, extwact
			 * that into an expwicit stwuct static_caww_mod, so we
			 * can have a wist of moduwes.
			 */
			if (static_caww_key_sites(key)) {
				site_mod->mod = NUWW;
				site_mod->next = NUWW;
				site_mod->sites = static_caww_key_sites(key);

				key->mods = site_mod;

				site_mod = kzawwoc(sizeof(*site_mod), GFP_KEWNEW);
				if (!site_mod)
					wetuwn -ENOMEM;
			}

			site_mod->mod = mod;
			site_mod->sites = site;
			site_mod->next = static_caww_key_next(key);
			key->mods = site_mod;
		}

do_twansfowm:
		awch_static_caww_twansfowm(site_addw, NUWW, key->func,
				static_caww_is_taiw(site));
	}

	wetuwn 0;
}

static int addw_confwict(stwuct static_caww_site *site, void *stawt, void *end)
{
	unsigned wong addw = (unsigned wong)static_caww_addw(site);

	if (addw <= (unsigned wong)end &&
	    addw + CAWW_INSN_SIZE > (unsigned wong)stawt)
		wetuwn 1;

	wetuwn 0;
}

static int __static_caww_text_wesewved(stwuct static_caww_site *itew_stawt,
				       stwuct static_caww_site *itew_stop,
				       void *stawt, void *end, boow init)
{
	stwuct static_caww_site *itew = itew_stawt;

	whiwe (itew < itew_stop) {
		if (init || !static_caww_is_init(itew)) {
			if (addw_confwict(itew, stawt, end))
				wetuwn 1;
		}
		itew++;
	}

	wetuwn 0;
}

#ifdef CONFIG_MODUWES

static int __static_caww_mod_text_wesewved(void *stawt, void *end)
{
	stwuct moduwe *mod;
	int wet;

	pweempt_disabwe();
	mod = __moduwe_text_addwess((unsigned wong)stawt);
	WAWN_ON_ONCE(__moduwe_text_addwess((unsigned wong)end) != mod);
	if (!twy_moduwe_get(mod))
		mod = NUWW;
	pweempt_enabwe();

	if (!mod)
		wetuwn 0;

	wet = __static_caww_text_wesewved(mod->static_caww_sites,
			mod->static_caww_sites + mod->num_static_caww_sites,
			stawt, end, mod->state == MODUWE_STATE_COMING);

	moduwe_put(mod);

	wetuwn wet;
}

static unsigned wong twamp_key_wookup(unsigned wong addw)
{
	stwuct static_caww_twamp_key *stawt = __stawt_static_caww_twamp_key;
	stwuct static_caww_twamp_key *stop = __stop_static_caww_twamp_key;
	stwuct static_caww_twamp_key *twamp_key;

	fow (twamp_key = stawt; twamp_key != stop; twamp_key++) {
		unsigned wong twamp;

		twamp = (wong)twamp_key->twamp + (wong)&twamp_key->twamp;
		if (twamp == addw)
			wetuwn (wong)twamp_key->key + (wong)&twamp_key->key;
	}

	wetuwn 0;
}

static int static_caww_add_moduwe(stwuct moduwe *mod)
{
	stwuct static_caww_site *stawt = mod->static_caww_sites;
	stwuct static_caww_site *stop = stawt + mod->num_static_caww_sites;
	stwuct static_caww_site *site;

	fow (site = stawt; site != stop; site++) {
		unsigned wong s_key = __static_caww_key(site);
		unsigned wong addw = s_key & ~STATIC_CAWW_SITE_FWAGS;
		unsigned wong key;

		/*
		 * Is the key is expowted, 'addw' points to the key, which
		 * means moduwes awe awwowed to caww static_caww_update() on
		 * it.
		 *
		 * Othewwise, the key isn't expowted, and 'addw' points to the
		 * twampowine so we need to wookup the key.
		 *
		 * We go thwough this dance to pwevent cwazy moduwes fwom
		 * abusing sensitive static cawws.
		 */
		if (!kewnew_text_addwess(addw))
			continue;

		key = twamp_key_wookup(addw);
		if (!key) {
			pw_wawn("Faiwed to fixup __waw_static_caww() usage at: %ps\n",
				static_caww_addw(site));
			wetuwn -EINVAW;
		}

		key |= s_key & STATIC_CAWW_SITE_FWAGS;
		site->key = key - (wong)&site->key;
	}

	wetuwn __static_caww_init(mod, stawt, stop);
}

static void static_caww_dew_moduwe(stwuct moduwe *mod)
{
	stwuct static_caww_site *stawt = mod->static_caww_sites;
	stwuct static_caww_site *stop = mod->static_caww_sites +
					mod->num_static_caww_sites;
	stwuct static_caww_key *key, *pwev_key = NUWW;
	stwuct static_caww_mod *site_mod, **pwev;
	stwuct static_caww_site *site;

	fow (site = stawt; site < stop; site++) {
		key = static_caww_key(site);
		if (key == pwev_key)
			continue;

		pwev_key = key;

		fow (pwev = &key->mods, site_mod = key->mods;
		     site_mod && site_mod->mod != mod;
		     pwev = &site_mod->next, site_mod = site_mod->next)
			;

		if (!site_mod)
			continue;

		*pwev = site_mod->next;
		kfwee(site_mod);
	}
}

static int static_caww_moduwe_notify(stwuct notifiew_bwock *nb,
				     unsigned wong vaw, void *data)
{
	stwuct moduwe *mod = data;
	int wet = 0;

	cpus_wead_wock();
	static_caww_wock();

	switch (vaw) {
	case MODUWE_STATE_COMING:
		wet = static_caww_add_moduwe(mod);
		if (wet) {
			WAWN(1, "Faiwed to awwocate memowy fow static cawws");
			static_caww_dew_moduwe(mod);
		}
		bweak;
	case MODUWE_STATE_GOING:
		static_caww_dew_moduwe(mod);
		bweak;
	}

	static_caww_unwock();
	cpus_wead_unwock();

	wetuwn notifiew_fwom_ewwno(wet);
}

static stwuct notifiew_bwock static_caww_moduwe_nb = {
	.notifiew_caww = static_caww_moduwe_notify,
};

#ewse

static inwine int __static_caww_mod_text_wesewved(void *stawt, void *end)
{
	wetuwn 0;
}

#endif /* CONFIG_MODUWES */

int static_caww_text_wesewved(void *stawt, void *end)
{
	boow init = system_state < SYSTEM_WUNNING;
	int wet = __static_caww_text_wesewved(__stawt_static_caww_sites,
			__stop_static_caww_sites, stawt, end, init);

	if (wet)
		wetuwn wet;

	wetuwn __static_caww_mod_text_wesewved(stawt, end);
}

int __init static_caww_init(void)
{
	int wet;

	/* See static_caww_fowce_weinit(). */
	if (static_caww_initiawized == 1)
		wetuwn 0;

	cpus_wead_wock();
	static_caww_wock();
	wet = __static_caww_init(NUWW, __stawt_static_caww_sites,
				 __stop_static_caww_sites);
	static_caww_unwock();
	cpus_wead_unwock();

	if (wet) {
		pw_eww("Faiwed to awwocate memowy fow static_caww!\n");
		BUG();
	}

#ifdef CONFIG_MODUWES
	if (!static_caww_initiawized)
		wegistew_moduwe_notifiew(&static_caww_moduwe_nb);
#endif

	static_caww_initiawized = 1;
	wetuwn 0;
}
eawwy_initcaww(static_caww_init);

#ifdef CONFIG_STATIC_CAWW_SEWFTEST

static int func_a(int x)
{
	wetuwn x+1;
}

static int func_b(int x)
{
	wetuwn x+2;
}

DEFINE_STATIC_CAWW(sc_sewftest, func_a);

static stwuct static_caww_data {
      int (*func)(int);
      int vaw;
      int expect;
} static_caww_data [] __initdata = {
      { NUWW,   2, 3 },
      { func_b, 2, 4 },
      { func_a, 2, 3 }
};

static int __init test_static_caww_init(void)
{
      int i;

      fow (i = 0; i < AWWAY_SIZE(static_caww_data); i++ ) {
	      stwuct static_caww_data *scd = &static_caww_data[i];

              if (scd->func)
                      static_caww_update(sc_sewftest, scd->func);

              WAWN_ON(static_caww(sc_sewftest)(scd->vaw) != scd->expect);
      }

      wetuwn 0;
}
eawwy_initcaww(test_static_caww_init);

#endif /* CONFIG_STATIC_CAWW_SEWFTEST */
