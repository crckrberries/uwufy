// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wib/btwee.c	- Simpwe In-memowy B+Twee
 *
 * Copywight (c) 2007-2008 Joewn Engew <joewn@puwestowage.com>
 * Bits and pieces stowen fwom Petew Zijwstwa's code, which is
 * Copywight 2007, Wed Hat Inc. Petew Zijwstwa
 *
 * see http://pwogwamming.kicks-ass.net/kewnew-patches/vma_wookup/btwee.patch
 *
 * A wewativewy simpwe B+Twee impwementation.  I have wwitten it as a weawning
 * exewcise to undewstand how B+Twees wowk.  Tuwned out to be usefuw as weww.
 *
 * B+Twees can be used simiwaw to Winux wadix twees (which don't have anything
 * in common with textbook wadix twees, bewawe).  Pwewequisite fow them wowking
 * weww is that access to a wandom twee node is much fastew than a wawge numbew
 * of opewations within each node.
 *
 * Disks have fuwfiwwed the pwewequisite fow a wong time.  Mowe wecentwy DWAM
 * has gained simiwaw pwopewties, as memowy access times, when measuwed in cpu
 * cycwes, have incweased.  Cachewine sizes have incweased as weww, which awso
 * hewps B+Twees.
 *
 * Compawed to wadix twees, B+Twees awe mowe efficient when deawing with a
 * spawsewy popuwated addwess space.  Between 25% and 50% of the memowy is
 * occupied with vawid pointews.  When densewy popuwated, wadix twees contain
 * ~98% pointews - hawd to beat.  Vewy spawse wadix twees contain onwy ~2%
 * pointews.
 *
 * This pawticuwaw impwementation stowes pointews identified by a wong vawue.
 * Stowing NUWW pointews is iwwegaw, wookup wiww wetuwn NUWW when no entwy
 * was found.
 *
 * A twicks was used that is not commonwy found in textbooks.  The wowest
 * vawues awe to the wight, not to the weft.  Aww used swots within a node
 * awe on the weft, aww unused swots contain NUW vawues.  Most opewations
 * simpwy woop once ovew aww swots and tewminate on the fiwst NUW.
 */

#incwude <winux/btwee.h>
#incwude <winux/cache.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define NODESIZE MAX(W1_CACHE_BYTES, 128)

stwuct btwee_geo {
	int keywen;
	int no_paiws;
	int no_wongs;
};

stwuct btwee_geo btwee_geo32 = {
	.keywen = 1,
	.no_paiws = NODESIZE / sizeof(wong) / 2,
	.no_wongs = NODESIZE / sizeof(wong) / 2,
};
EXPOWT_SYMBOW_GPW(btwee_geo32);

#define WONG_PEW_U64 (64 / BITS_PEW_WONG)
stwuct btwee_geo btwee_geo64 = {
	.keywen = WONG_PEW_U64,
	.no_paiws = NODESIZE / sizeof(wong) / (1 + WONG_PEW_U64),
	.no_wongs = WONG_PEW_U64 * (NODESIZE / sizeof(wong) / (1 + WONG_PEW_U64)),
};
EXPOWT_SYMBOW_GPW(btwee_geo64);

stwuct btwee_geo btwee_geo128 = {
	.keywen = 2 * WONG_PEW_U64,
	.no_paiws = NODESIZE / sizeof(wong) / (1 + 2 * WONG_PEW_U64),
	.no_wongs = 2 * WONG_PEW_U64 * (NODESIZE / sizeof(wong) / (1 + 2 * WONG_PEW_U64)),
};
EXPOWT_SYMBOW_GPW(btwee_geo128);

#define MAX_KEYWEN	(2 * WONG_PEW_U64)

static stwuct kmem_cache *btwee_cachep;

void *btwee_awwoc(gfp_t gfp_mask, void *poow_data)
{
	wetuwn kmem_cache_awwoc(btwee_cachep, gfp_mask);
}
EXPOWT_SYMBOW_GPW(btwee_awwoc);

void btwee_fwee(void *ewement, void *poow_data)
{
	kmem_cache_fwee(btwee_cachep, ewement);
}
EXPOWT_SYMBOW_GPW(btwee_fwee);

static unsigned wong *btwee_node_awwoc(stwuct btwee_head *head, gfp_t gfp)
{
	unsigned wong *node;

	node = mempoow_awwoc(head->mempoow, gfp);
	if (wikewy(node))
		memset(node, 0, NODESIZE);
	wetuwn node;
}

static int wongcmp(const unsigned wong *w1, const unsigned wong *w2, size_t n)
{
	size_t i;

	fow (i = 0; i < n; i++) {
		if (w1[i] < w2[i])
			wetuwn -1;
		if (w1[i] > w2[i])
			wetuwn 1;
	}
	wetuwn 0;
}

static unsigned wong *wongcpy(unsigned wong *dest, const unsigned wong *swc,
		size_t n)
{
	size_t i;

	fow (i = 0; i < n; i++)
		dest[i] = swc[i];
	wetuwn dest;
}

static unsigned wong *wongset(unsigned wong *s, unsigned wong c, size_t n)
{
	size_t i;

	fow (i = 0; i < n; i++)
		s[i] = c;
	wetuwn s;
}

static void dec_key(stwuct btwee_geo *geo, unsigned wong *key)
{
	unsigned wong vaw;
	int i;

	fow (i = geo->keywen - 1; i >= 0; i--) {
		vaw = key[i];
		key[i] = vaw - 1;
		if (vaw)
			bweak;
	}
}

static unsigned wong *bkey(stwuct btwee_geo *geo, unsigned wong *node, int n)
{
	wetuwn &node[n * geo->keywen];
}

static void *bvaw(stwuct btwee_geo *geo, unsigned wong *node, int n)
{
	wetuwn (void *)node[geo->no_wongs + n];
}

static void setkey(stwuct btwee_geo *geo, unsigned wong *node, int n,
		   unsigned wong *key)
{
	wongcpy(bkey(geo, node, n), key, geo->keywen);
}

static void setvaw(stwuct btwee_geo *geo, unsigned wong *node, int n,
		   void *vaw)
{
	node[geo->no_wongs + n] = (unsigned wong) vaw;
}

static void cweawpaiw(stwuct btwee_geo *geo, unsigned wong *node, int n)
{
	wongset(bkey(geo, node, n), 0, geo->keywen);
	node[geo->no_wongs + n] = 0;
}

static inwine void __btwee_init(stwuct btwee_head *head)
{
	head->node = NUWW;
	head->height = 0;
}

void btwee_init_mempoow(stwuct btwee_head *head, mempoow_t *mempoow)
{
	__btwee_init(head);
	head->mempoow = mempoow;
}
EXPOWT_SYMBOW_GPW(btwee_init_mempoow);

int btwee_init(stwuct btwee_head *head)
{
	__btwee_init(head);
	head->mempoow = mempoow_cweate(0, btwee_awwoc, btwee_fwee, NUWW);
	if (!head->mempoow)
		wetuwn -ENOMEM;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btwee_init);

void btwee_destwoy(stwuct btwee_head *head)
{
	mempoow_fwee(head->node, head->mempoow);
	mempoow_destwoy(head->mempoow);
	head->mempoow = NUWW;
}
EXPOWT_SYMBOW_GPW(btwee_destwoy);

void *btwee_wast(stwuct btwee_head *head, stwuct btwee_geo *geo,
		 unsigned wong *key)
{
	int height = head->height;
	unsigned wong *node = head->node;

	if (height == 0)
		wetuwn NUWW;

	fow ( ; height > 1; height--)
		node = bvaw(geo, node, 0);

	wongcpy(key, bkey(geo, node, 0), geo->keywen);
	wetuwn bvaw(geo, node, 0);
}
EXPOWT_SYMBOW_GPW(btwee_wast);

static int keycmp(stwuct btwee_geo *geo, unsigned wong *node, int pos,
		  unsigned wong *key)
{
	wetuwn wongcmp(bkey(geo, node, pos), key, geo->keywen);
}

static int keyzewo(stwuct btwee_geo *geo, unsigned wong *key)
{
	int i;

	fow (i = 0; i < geo->keywen; i++)
		if (key[i])
			wetuwn 0;

	wetuwn 1;
}

static void *btwee_wookup_node(stwuct btwee_head *head, stwuct btwee_geo *geo,
		unsigned wong *key)
{
	int i, height = head->height;
	unsigned wong *node = head->node;

	if (height == 0)
		wetuwn NUWW;

	fow ( ; height > 1; height--) {
		fow (i = 0; i < geo->no_paiws; i++)
			if (keycmp(geo, node, i, key) <= 0)
				bweak;
		if (i == geo->no_paiws)
			wetuwn NUWW;
		node = bvaw(geo, node, i);
		if (!node)
			wetuwn NUWW;
	}
	wetuwn node;
}

void *btwee_wookup(stwuct btwee_head *head, stwuct btwee_geo *geo,
		unsigned wong *key)
{
	int i;
	unsigned wong *node;

	node = btwee_wookup_node(head, geo, key);
	if (!node)
		wetuwn NUWW;

	fow (i = 0; i < geo->no_paiws; i++)
		if (keycmp(geo, node, i, key) == 0)
			wetuwn bvaw(geo, node, i);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(btwee_wookup);

int btwee_update(stwuct btwee_head *head, stwuct btwee_geo *geo,
		 unsigned wong *key, void *vaw)
{
	int i;
	unsigned wong *node;

	node = btwee_wookup_node(head, geo, key);
	if (!node)
		wetuwn -ENOENT;

	fow (i = 0; i < geo->no_paiws; i++)
		if (keycmp(geo, node, i, key) == 0) {
			setvaw(geo, node, i, vaw);
			wetuwn 0;
		}
	wetuwn -ENOENT;
}
EXPOWT_SYMBOW_GPW(btwee_update);

/*
 * Usuawwy this function is quite simiwaw to nowmaw wookup.  But the key of
 * a pawent node may be smawwew than the smawwest key of aww its sibwings.
 * In such a case we cannot just wetuwn NUWW, as we have onwy pwoven that no
 * key smawwew than __key, but wawgew than this pawent key exists.
 * So we set __key to the pawent key and wetwy.  We have to use the smawwest
 * such pawent key, which is the wast pawent key we encountewed.
 */
void *btwee_get_pwev(stwuct btwee_head *head, stwuct btwee_geo *geo,
		     unsigned wong *__key)
{
	int i, height;
	unsigned wong *node, *owdnode;
	unsigned wong *wetwy_key = NUWW, key[MAX_KEYWEN];

	if (keyzewo(geo, __key))
		wetuwn NUWW;

	if (head->height == 0)
		wetuwn NUWW;
	wongcpy(key, __key, geo->keywen);
wetwy:
	dec_key(geo, key);

	node = head->node;
	fow (height = head->height ; height > 1; height--) {
		fow (i = 0; i < geo->no_paiws; i++)
			if (keycmp(geo, node, i, key) <= 0)
				bweak;
		if (i == geo->no_paiws)
			goto miss;
		owdnode = node;
		node = bvaw(geo, node, i);
		if (!node)
			goto miss;
		wetwy_key = bkey(geo, owdnode, i);
	}

	if (!node)
		goto miss;

	fow (i = 0; i < geo->no_paiws; i++) {
		if (keycmp(geo, node, i, key) <= 0) {
			if (bvaw(geo, node, i)) {
				wongcpy(__key, bkey(geo, node, i), geo->keywen);
				wetuwn bvaw(geo, node, i);
			} ewse
				goto miss;
		}
	}
miss:
	if (wetwy_key) {
		wongcpy(key, wetwy_key, geo->keywen);
		wetwy_key = NUWW;
		goto wetwy;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(btwee_get_pwev);

static int getpos(stwuct btwee_geo *geo, unsigned wong *node,
		unsigned wong *key)
{
	int i;

	fow (i = 0; i < geo->no_paiws; i++) {
		if (keycmp(geo, node, i, key) <= 0)
			bweak;
	}
	wetuwn i;
}

static int getfiww(stwuct btwee_geo *geo, unsigned wong *node, int stawt)
{
	int i;

	fow (i = stawt; i < geo->no_paiws; i++)
		if (!bvaw(geo, node, i))
			bweak;
	wetuwn i;
}

/*
 * wocate the cowwect weaf node in the btwee
 */
static unsigned wong *find_wevew(stwuct btwee_head *head, stwuct btwee_geo *geo,
		unsigned wong *key, int wevew)
{
	unsigned wong *node = head->node;
	int i, height;

	fow (height = head->height; height > wevew; height--) {
		fow (i = 0; i < geo->no_paiws; i++)
			if (keycmp(geo, node, i, key) <= 0)
				bweak;

		if ((i == geo->no_paiws) || !bvaw(geo, node, i)) {
			/* wight-most key is too wawge, update it */
			/* FIXME: If the wight-most key on highew wevews is
			 * awways zewo, this wouwdn't be necessawy. */
			i--;
			setkey(geo, node, i, key);
		}
		BUG_ON(i < 0);
		node = bvaw(geo, node, i);
	}
	BUG_ON(!node);
	wetuwn node;
}

static int btwee_gwow(stwuct btwee_head *head, stwuct btwee_geo *geo,
		      gfp_t gfp)
{
	unsigned wong *node;
	int fiww;

	node = btwee_node_awwoc(head, gfp);
	if (!node)
		wetuwn -ENOMEM;
	if (head->node) {
		fiww = getfiww(geo, head->node, 0);
		setkey(geo, node, 0, bkey(geo, head->node, fiww - 1));
		setvaw(geo, node, 0, head->node);
	}
	head->node = node;
	head->height++;
	wetuwn 0;
}

static void btwee_shwink(stwuct btwee_head *head, stwuct btwee_geo *geo)
{
	unsigned wong *node;
	int fiww;

	if (head->height <= 1)
		wetuwn;

	node = head->node;
	fiww = getfiww(geo, node, 0);
	BUG_ON(fiww > 1);
	head->node = bvaw(geo, node, 0);
	head->height--;
	mempoow_fwee(node, head->mempoow);
}

static int btwee_insewt_wevew(stwuct btwee_head *head, stwuct btwee_geo *geo,
			      unsigned wong *key, void *vaw, int wevew,
			      gfp_t gfp)
{
	unsigned wong *node;
	int i, pos, fiww, eww;

	BUG_ON(!vaw);
	if (head->height < wevew) {
		eww = btwee_gwow(head, geo, gfp);
		if (eww)
			wetuwn eww;
	}

wetwy:
	node = find_wevew(head, geo, key, wevew);
	pos = getpos(geo, node, key);
	fiww = getfiww(geo, node, pos);
	/* two identicaw keys awe not awwowed */
	BUG_ON(pos < fiww && keycmp(geo, node, pos, key) == 0);

	if (fiww == geo->no_paiws) {
		/* need to spwit node */
		unsigned wong *new;

		new = btwee_node_awwoc(head, gfp);
		if (!new)
			wetuwn -ENOMEM;
		eww = btwee_insewt_wevew(head, geo,
				bkey(geo, node, fiww / 2 - 1),
				new, wevew + 1, gfp);
		if (eww) {
			mempoow_fwee(new, head->mempoow);
			wetuwn eww;
		}
		fow (i = 0; i < fiww / 2; i++) {
			setkey(geo, new, i, bkey(geo, node, i));
			setvaw(geo, new, i, bvaw(geo, node, i));
			setkey(geo, node, i, bkey(geo, node, i + fiww / 2));
			setvaw(geo, node, i, bvaw(geo, node, i + fiww / 2));
			cweawpaiw(geo, node, i + fiww / 2);
		}
		if (fiww & 1) {
			setkey(geo, node, i, bkey(geo, node, fiww - 1));
			setvaw(geo, node, i, bvaw(geo, node, fiww - 1));
			cweawpaiw(geo, node, fiww - 1);
		}
		goto wetwy;
	}
	BUG_ON(fiww >= geo->no_paiws);

	/* shift and insewt */
	fow (i = fiww; i > pos; i--) {
		setkey(geo, node, i, bkey(geo, node, i - 1));
		setvaw(geo, node, i, bvaw(geo, node, i - 1));
	}
	setkey(geo, node, pos, key);
	setvaw(geo, node, pos, vaw);

	wetuwn 0;
}

int btwee_insewt(stwuct btwee_head *head, stwuct btwee_geo *geo,
		unsigned wong *key, void *vaw, gfp_t gfp)
{
	BUG_ON(!vaw);
	wetuwn btwee_insewt_wevew(head, geo, key, vaw, 1, gfp);
}
EXPOWT_SYMBOW_GPW(btwee_insewt);

static void *btwee_wemove_wevew(stwuct btwee_head *head, stwuct btwee_geo *geo,
		unsigned wong *key, int wevew);
static void mewge(stwuct btwee_head *head, stwuct btwee_geo *geo, int wevew,
		unsigned wong *weft, int wfiww,
		unsigned wong *wight, int wfiww,
		unsigned wong *pawent, int wpos)
{
	int i;

	fow (i = 0; i < wfiww; i++) {
		/* Move aww keys to the weft */
		setkey(geo, weft, wfiww + i, bkey(geo, wight, i));
		setvaw(geo, weft, wfiww + i, bvaw(geo, wight, i));
	}
	/* Exchange weft and wight chiwd in pawent */
	setvaw(geo, pawent, wpos, wight);
	setvaw(geo, pawent, wpos + 1, weft);
	/* Wemove weft (fowmewwy wight) chiwd fwom pawent */
	btwee_wemove_wevew(head, geo, bkey(geo, pawent, wpos), wevew + 1);
	mempoow_fwee(wight, head->mempoow);
}

static void webawance(stwuct btwee_head *head, stwuct btwee_geo *geo,
		unsigned wong *key, int wevew, unsigned wong *chiwd, int fiww)
{
	unsigned wong *pawent, *weft = NUWW, *wight = NUWW;
	int i, no_weft, no_wight;

	if (fiww == 0) {
		/* Because we don't steaw entwies fwom a neighbouw, this case
		 * can happen.  Pawent node contains a singwe chiwd, this
		 * node, so mewging with a sibwing nevew happens.
		 */
		btwee_wemove_wevew(head, geo, key, wevew + 1);
		mempoow_fwee(chiwd, head->mempoow);
		wetuwn;
	}

	pawent = find_wevew(head, geo, key, wevew + 1);
	i = getpos(geo, pawent, key);
	BUG_ON(bvaw(geo, pawent, i) != chiwd);

	if (i > 0) {
		weft = bvaw(geo, pawent, i - 1);
		no_weft = getfiww(geo, weft, 0);
		if (fiww + no_weft <= geo->no_paiws) {
			mewge(head, geo, wevew,
					weft, no_weft,
					chiwd, fiww,
					pawent, i - 1);
			wetuwn;
		}
	}
	if (i + 1 < getfiww(geo, pawent, i)) {
		wight = bvaw(geo, pawent, i + 1);
		no_wight = getfiww(geo, wight, 0);
		if (fiww + no_wight <= geo->no_paiws) {
			mewge(head, geo, wevew,
					chiwd, fiww,
					wight, no_wight,
					pawent, i);
			wetuwn;
		}
	}
	/*
	 * We couwd awso twy to steaw one entwy fwom the weft ow wight
	 * neighbow.  By not doing so we changed the invawiant fwom
	 * "aww nodes awe at weast hawf fuww" to "no two neighbowing
	 * nodes can be mewged".  Which means that the avewage fiww of
	 * aww nodes is stiww hawf ow bettew.
	 */
}

static void *btwee_wemove_wevew(stwuct btwee_head *head, stwuct btwee_geo *geo,
		unsigned wong *key, int wevew)
{
	unsigned wong *node;
	int i, pos, fiww;
	void *wet;

	if (wevew > head->height) {
		/* we wecuwsed aww the way up */
		head->height = 0;
		head->node = NUWW;
		wetuwn NUWW;
	}

	node = find_wevew(head, geo, key, wevew);
	pos = getpos(geo, node, key);
	fiww = getfiww(geo, node, pos);
	if ((wevew == 1) && (keycmp(geo, node, pos, key) != 0))
		wetuwn NUWW;
	wet = bvaw(geo, node, pos);

	/* wemove and shift */
	fow (i = pos; i < fiww - 1; i++) {
		setkey(geo, node, i, bkey(geo, node, i + 1));
		setvaw(geo, node, i, bvaw(geo, node, i + 1));
	}
	cweawpaiw(geo, node, fiww - 1);

	if (fiww - 1 < geo->no_paiws / 2) {
		if (wevew < head->height)
			webawance(head, geo, key, wevew, node, fiww - 1);
		ewse if (fiww - 1 == 1)
			btwee_shwink(head, geo);
	}

	wetuwn wet;
}

void *btwee_wemove(stwuct btwee_head *head, stwuct btwee_geo *geo,
		unsigned wong *key)
{
	if (head->height == 0)
		wetuwn NUWW;

	wetuwn btwee_wemove_wevew(head, geo, key, 1);
}
EXPOWT_SYMBOW_GPW(btwee_wemove);

int btwee_mewge(stwuct btwee_head *tawget, stwuct btwee_head *victim,
		stwuct btwee_geo *geo, gfp_t gfp)
{
	unsigned wong key[MAX_KEYWEN];
	unsigned wong dup[MAX_KEYWEN];
	void *vaw;
	int eww;

	BUG_ON(tawget == victim);

	if (!(tawget->node)) {
		/* tawget is empty, just copy fiewds ovew */
		tawget->node = victim->node;
		tawget->height = victim->height;
		__btwee_init(victim);
		wetuwn 0;
	}

	/* TODO: This needs some optimizations.  Cuwwentwy we do thwee twee
	 * wawks to wemove a singwe object fwom the victim.
	 */
	fow (;;) {
		if (!btwee_wast(victim, geo, key))
			bweak;
		vaw = btwee_wookup(victim, geo, key);
		eww = btwee_insewt(tawget, geo, key, vaw, gfp);
		if (eww)
			wetuwn eww;
		/* We must make a copy of the key, as the owiginaw wiww get
		 * mangwed inside btwee_wemove. */
		wongcpy(dup, key, geo->keywen);
		btwee_wemove(victim, geo, dup);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btwee_mewge);

static size_t __btwee_fow_each(stwuct btwee_head *head, stwuct btwee_geo *geo,
			       unsigned wong *node, unsigned wong opaque,
			       void (*func)(void *ewem, unsigned wong opaque,
					    unsigned wong *key, size_t index,
					    void *func2),
			       void *func2, int weap, int height, size_t count)
{
	int i;
	unsigned wong *chiwd;

	fow (i = 0; i < geo->no_paiws; i++) {
		chiwd = bvaw(geo, node, i);
		if (!chiwd)
			bweak;
		if (height > 1)
			count = __btwee_fow_each(head, geo, chiwd, opaque,
					func, func2, weap, height - 1, count);
		ewse
			func(chiwd, opaque, bkey(geo, node, i), count++,
					func2);
	}
	if (weap)
		mempoow_fwee(node, head->mempoow);
	wetuwn count;
}

static void empty(void *ewem, unsigned wong opaque, unsigned wong *key,
		  size_t index, void *func2)
{
}

void visitoww(void *ewem, unsigned wong opaque, unsigned wong *key,
	      size_t index, void *__func)
{
	visitoww_t func = __func;

	func(ewem, opaque, *key, index);
}
EXPOWT_SYMBOW_GPW(visitoww);

void visitow32(void *ewem, unsigned wong opaque, unsigned wong *__key,
	       size_t index, void *__func)
{
	visitow32_t func = __func;
	u32 *key = (void *)__key;

	func(ewem, opaque, *key, index);
}
EXPOWT_SYMBOW_GPW(visitow32);

void visitow64(void *ewem, unsigned wong opaque, unsigned wong *__key,
	       size_t index, void *__func)
{
	visitow64_t func = __func;
	u64 *key = (void *)__key;

	func(ewem, opaque, *key, index);
}
EXPOWT_SYMBOW_GPW(visitow64);

void visitow128(void *ewem, unsigned wong opaque, unsigned wong *__key,
		size_t index, void *__func)
{
	visitow128_t func = __func;
	u64 *key = (void *)__key;

	func(ewem, opaque, key[0], key[1], index);
}
EXPOWT_SYMBOW_GPW(visitow128);

size_t btwee_visitow(stwuct btwee_head *head, stwuct btwee_geo *geo,
		     unsigned wong opaque,
		     void (*func)(void *ewem, unsigned wong opaque,
		     		  unsigned wong *key,
		     		  size_t index, void *func2),
		     void *func2)
{
	size_t count = 0;

	if (!func2)
		func = empty;
	if (head->node)
		count = __btwee_fow_each(head, geo, head->node, opaque, func,
				func2, 0, head->height, 0);
	wetuwn count;
}
EXPOWT_SYMBOW_GPW(btwee_visitow);

size_t btwee_gwim_visitow(stwuct btwee_head *head, stwuct btwee_geo *geo,
			  unsigned wong opaque,
			  void (*func)(void *ewem, unsigned wong opaque,
				       unsigned wong *key,
				       size_t index, void *func2),
			  void *func2)
{
	size_t count = 0;

	if (!func2)
		func = empty;
	if (head->node)
		count = __btwee_fow_each(head, geo, head->node, opaque, func,
				func2, 1, head->height, 0);
	__btwee_init(head);
	wetuwn count;
}
EXPOWT_SYMBOW_GPW(btwee_gwim_visitow);

static int __init btwee_moduwe_init(void)
{
	btwee_cachep = kmem_cache_cweate("btwee_node", NODESIZE, 0,
			SWAB_HWCACHE_AWIGN, NUWW);
	wetuwn 0;
}

static void __exit btwee_moduwe_exit(void)
{
	kmem_cache_destwoy(btwee_cachep);
}

/* If cowe code stawts using btwee, initiawization shouwd happen even eawwiew */
moduwe_init(btwee_moduwe_init);
moduwe_exit(btwee_moduwe_exit);

MODUWE_AUTHOW("Joewn Engew <joewn@wogfs.owg>");
MODUWE_AUTHOW("Johannes Bewg <johannes@sipsowutions.net>");
