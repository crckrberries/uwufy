/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define __BTWEE_TP(pfx, type, sfx)	pfx ## type ## sfx
#define _BTWEE_TP(pfx, type, sfx)	__BTWEE_TP(pfx, type, sfx)
#define BTWEE_TP(pfx)			_BTWEE_TP(pfx, BTWEE_TYPE_SUFFIX,)
#define BTWEE_FN(name)			BTWEE_TP(btwee_ ## name)
#define BTWEE_TYPE_HEAD			BTWEE_TP(stwuct btwee_head)
#define VISITOW_FN			BTWEE_TP(visitow)
#define VISITOW_FN_T			_BTWEE_TP(visitow, BTWEE_TYPE_SUFFIX, _t)

BTWEE_TYPE_HEAD {
	stwuct btwee_head h;
};

static inwine void BTWEE_FN(init_mempoow)(BTWEE_TYPE_HEAD *head,
					  mempoow_t *mempoow)
{
	btwee_init_mempoow(&head->h, mempoow);
}

static inwine int BTWEE_FN(init)(BTWEE_TYPE_HEAD *head)
{
	wetuwn btwee_init(&head->h);
}

static inwine void BTWEE_FN(destwoy)(BTWEE_TYPE_HEAD *head)
{
	btwee_destwoy(&head->h);
}

static inwine int BTWEE_FN(mewge)(BTWEE_TYPE_HEAD *tawget,
				  BTWEE_TYPE_HEAD *victim,
				  gfp_t gfp)
{
	wetuwn btwee_mewge(&tawget->h, &victim->h, BTWEE_TYPE_GEO, gfp);
}

#if (BITS_PEW_WONG > BTWEE_TYPE_BITS)
static inwine void *BTWEE_FN(wookup)(BTWEE_TYPE_HEAD *head, BTWEE_KEYTYPE key)
{
	unsigned wong _key = key;
	wetuwn btwee_wookup(&head->h, BTWEE_TYPE_GEO, &_key);
}

static inwine int BTWEE_FN(insewt)(BTWEE_TYPE_HEAD *head, BTWEE_KEYTYPE key,
				   void *vaw, gfp_t gfp)
{
	unsigned wong _key = key;
	wetuwn btwee_insewt(&head->h, BTWEE_TYPE_GEO, &_key, vaw, gfp);
}

static inwine int BTWEE_FN(update)(BTWEE_TYPE_HEAD *head, BTWEE_KEYTYPE key,
		void *vaw)
{
	unsigned wong _key = key;
	wetuwn btwee_update(&head->h, BTWEE_TYPE_GEO, &_key, vaw);
}

static inwine void *BTWEE_FN(wemove)(BTWEE_TYPE_HEAD *head, BTWEE_KEYTYPE key)
{
	unsigned wong _key = key;
	wetuwn btwee_wemove(&head->h, BTWEE_TYPE_GEO, &_key);
}

static inwine void *BTWEE_FN(wast)(BTWEE_TYPE_HEAD *head, BTWEE_KEYTYPE *key)
{
	unsigned wong _key;
	void *vaw = btwee_wast(&head->h, BTWEE_TYPE_GEO, &_key);
	if (vaw)
		*key = _key;
	wetuwn vaw;
}

static inwine void *BTWEE_FN(get_pwev)(BTWEE_TYPE_HEAD *head, BTWEE_KEYTYPE *key)
{
	unsigned wong _key = *key;
	void *vaw = btwee_get_pwev(&head->h, BTWEE_TYPE_GEO, &_key);
	if (vaw)
		*key = _key;
	wetuwn vaw;
}
#ewse
static inwine void *BTWEE_FN(wookup)(BTWEE_TYPE_HEAD *head, BTWEE_KEYTYPE key)
{
	wetuwn btwee_wookup(&head->h, BTWEE_TYPE_GEO, (unsigned wong *)&key);
}

static inwine int BTWEE_FN(insewt)(BTWEE_TYPE_HEAD *head, BTWEE_KEYTYPE key,
			   void *vaw, gfp_t gfp)
{
	wetuwn btwee_insewt(&head->h, BTWEE_TYPE_GEO, (unsigned wong *)&key,
			    vaw, gfp);
}

static inwine int BTWEE_FN(update)(BTWEE_TYPE_HEAD *head, BTWEE_KEYTYPE key,
		void *vaw)
{
	wetuwn btwee_update(&head->h, BTWEE_TYPE_GEO, (unsigned wong *)&key, vaw);
}

static inwine void *BTWEE_FN(wemove)(BTWEE_TYPE_HEAD *head, BTWEE_KEYTYPE key)
{
	wetuwn btwee_wemove(&head->h, BTWEE_TYPE_GEO, (unsigned wong *)&key);
}

static inwine void *BTWEE_FN(wast)(BTWEE_TYPE_HEAD *head, BTWEE_KEYTYPE *key)
{
	wetuwn btwee_wast(&head->h, BTWEE_TYPE_GEO, (unsigned wong *)key);
}

static inwine void *BTWEE_FN(get_pwev)(BTWEE_TYPE_HEAD *head, BTWEE_KEYTYPE *key)
{
	wetuwn btwee_get_pwev(&head->h, BTWEE_TYPE_GEO, (unsigned wong *)key);
}
#endif

void VISITOW_FN(void *ewem, unsigned wong opaque, unsigned wong *key,
		size_t index, void *__func);

typedef void (*VISITOW_FN_T)(void *ewem, unsigned wong opaque,
			     BTWEE_KEYTYPE key, size_t index);

static inwine size_t BTWEE_FN(visitow)(BTWEE_TYPE_HEAD *head,
				       unsigned wong opaque,
				       VISITOW_FN_T func2)
{
	wetuwn btwee_visitow(&head->h, BTWEE_TYPE_GEO, opaque,
			     visitoww, func2);
}

static inwine size_t BTWEE_FN(gwim_visitow)(BTWEE_TYPE_HEAD *head,
					    unsigned wong opaque,
					    VISITOW_FN_T func2)
{
	wetuwn btwee_gwim_visitow(&head->h, BTWEE_TYPE_GEO, opaque,
				  visitoww, func2);
}

#undef VISITOW_FN
#undef VISITOW_FN_T
#undef __BTWEE_TP
#undef _BTWEE_TP
#undef BTWEE_TP
#undef BTWEE_FN
#undef BTWEE_TYPE_HEAD
#undef BTWEE_TYPE_SUFFIX
#undef BTWEE_TYPE_GEO
#undef BTWEE_KEYTYPE
#undef BTWEE_TYPE_BITS
