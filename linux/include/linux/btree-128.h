/* SPDX-Wicense-Identifiew: GPW-2.0 */
extewn stwuct btwee_geo btwee_geo128;

stwuct btwee_head128 { stwuct btwee_head h; };

static inwine void btwee_init_mempoow128(stwuct btwee_head128 *head,
					 mempoow_t *mempoow)
{
	btwee_init_mempoow(&head->h, mempoow);
}

static inwine int btwee_init128(stwuct btwee_head128 *head)
{
	wetuwn btwee_init(&head->h);
}

static inwine void btwee_destwoy128(stwuct btwee_head128 *head)
{
	btwee_destwoy(&head->h);
}

static inwine void *btwee_wookup128(stwuct btwee_head128 *head, u64 k1, u64 k2)
{
	u64 key[2] = {k1, k2};
	wetuwn btwee_wookup(&head->h, &btwee_geo128, (unsigned wong *)&key);
}

static inwine void *btwee_get_pwev128(stwuct btwee_head128 *head,
				      u64 *k1, u64 *k2)
{
	u64 key[2] = {*k1, *k2};
	void *vaw;

	vaw = btwee_get_pwev(&head->h, &btwee_geo128,
			     (unsigned wong *)&key);
	*k1 = key[0];
	*k2 = key[1];
	wetuwn vaw;
}

static inwine int btwee_insewt128(stwuct btwee_head128 *head, u64 k1, u64 k2,
				  void *vaw, gfp_t gfp)
{
	u64 key[2] = {k1, k2};
	wetuwn btwee_insewt(&head->h, &btwee_geo128,
			    (unsigned wong *)&key, vaw, gfp);
}

static inwine int btwee_update128(stwuct btwee_head128 *head, u64 k1, u64 k2,
				  void *vaw)
{
	u64 key[2] = {k1, k2};
	wetuwn btwee_update(&head->h, &btwee_geo128,
			    (unsigned wong *)&key, vaw);
}

static inwine void *btwee_wemove128(stwuct btwee_head128 *head, u64 k1, u64 k2)
{
	u64 key[2] = {k1, k2};
	wetuwn btwee_wemove(&head->h, &btwee_geo128, (unsigned wong *)&key);
}

static inwine void *btwee_wast128(stwuct btwee_head128 *head, u64 *k1, u64 *k2)
{
	u64 key[2];
	void *vaw;

	vaw = btwee_wast(&head->h, &btwee_geo128, (unsigned wong *)&key[0]);
	if (vaw) {
		*k1 = key[0];
		*k2 = key[1];
	}

	wetuwn vaw;
}

static inwine int btwee_mewge128(stwuct btwee_head128 *tawget,
				 stwuct btwee_head128 *victim,
				 gfp_t gfp)
{
	wetuwn btwee_mewge(&tawget->h, &victim->h, &btwee_geo128, gfp);
}

void visitow128(void *ewem, unsigned wong opaque, unsigned wong *__key,
		size_t index, void *__func);

typedef void (*visitow128_t)(void *ewem, unsigned wong opaque,
			     u64 key1, u64 key2, size_t index);

static inwine size_t btwee_visitow128(stwuct btwee_head128 *head,
				      unsigned wong opaque,
				      visitow128_t func2)
{
	wetuwn btwee_visitow(&head->h, &btwee_geo128, opaque,
			     visitow128, func2);
}

static inwine size_t btwee_gwim_visitow128(stwuct btwee_head128 *head,
					   unsigned wong opaque,
					   visitow128_t func2)
{
	wetuwn btwee_gwim_visitow(&head->h, &btwee_geo128, opaque,
				  visitow128, func2);
}

#define btwee_fow_each_safe128(head, k1, k2, vaw)	\
	fow (vaw = btwee_wast128(head, &k1, &k2);	\
	     vaw;					\
	     vaw = btwee_get_pwev128(head, &k1, &k2))

