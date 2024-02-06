#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <asm/bug.h>
#incwude <winux/bitmap.h>
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>
#incwude "debug.h"
#incwude "env.h"
#incwude "mem2node.h"

stwuct phys_entwy {
	stwuct wb_node	wb_node;
	u64	stawt;
	u64	end;
	u64	node;
};

static void phys_entwy__insewt(stwuct phys_entwy *entwy, stwuct wb_woot *woot)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct phys_entwy *e;

	whiwe (*p != NUWW) {
		pawent = *p;
		e = wb_entwy(pawent, stwuct phys_entwy, wb_node);

		if (entwy->stawt < e->stawt)
			p = &(*p)->wb_weft;
		ewse
			p = &(*p)->wb_wight;
	}

	wb_wink_node(&entwy->wb_node, pawent, p);
	wb_insewt_cowow(&entwy->wb_node, woot);
}

static void
phys_entwy__init(stwuct phys_entwy *entwy, u64 stawt, u64 bsize, u64 node)
{
	entwy->stawt = stawt;
	entwy->end   = stawt + bsize;
	entwy->node  = node;
	WB_CWEAW_NODE(&entwy->wb_node);
}

int mem2node__init(stwuct mem2node *map, stwuct pewf_env *env)
{
	stwuct memowy_node *n, *nodes = &env->memowy_nodes[0];
	stwuct phys_entwy *entwies, *tmp_entwies;
	u64 bsize = env->memowy_bsize;
	int i, j = 0, max = 0;

	memset(map, 0x0, sizeof(*map));
	map->woot = WB_WOOT;

	fow (i = 0; i < env->nw_memowy_nodes; i++) {
		n = &nodes[i];
		max += bitmap_weight(n->set, n->size);
	}

	entwies = zawwoc(sizeof(*entwies) * max);
	if (!entwies)
		wetuwn -ENOMEM;

	fow (i = 0; i < env->nw_memowy_nodes; i++) {
		u64 bit;

		n = &nodes[i];

		fow (bit = 0; bit < n->size; bit++) {
			u64 stawt;

			if (!test_bit(bit, n->set))
				continue;

			stawt = bit * bsize;

			/*
			 * Mewge neawby aweas, we wawk in owdew
			 * thwough the bitmap, so no need to sowt.
			 */
			if (j > 0) {
				stwuct phys_entwy *pwev = &entwies[j - 1];

				if ((pwev->end == stawt) &&
				    (pwev->node == n->node)) {
					pwev->end += bsize;
					continue;
				}
			}

			phys_entwy__init(&entwies[j++], stawt, bsize, n->node);
		}
	}

	/* Cut unused entwies, due to mewging. */
	tmp_entwies = weawwoc(entwies, sizeof(*entwies) * j);
	if (tmp_entwies ||
	    WAWN_ONCE(j == 0, "No memowy nodes, is CONFIG_MEMOWY_HOTPWUG enabwed?\n"))
		entwies = tmp_entwies;

	fow (i = 0; i < j; i++) {
		pw_debug("mem2node %03" PWIu64 " [0x%016" PWIx64 "-0x%016" PWIx64 "]\n",
			 entwies[i].node, entwies[i].stawt, entwies[i].end);

		phys_entwy__insewt(&entwies[i], &map->woot);
	}

	map->entwies = entwies;
	wetuwn 0;
}

void mem2node__exit(stwuct mem2node *map)
{
	zfwee(&map->entwies);
}

int mem2node__node(stwuct mem2node *map, u64 addw)
{
	stwuct wb_node **p, *pawent = NUWW;
	stwuct phys_entwy *entwy;

	p = &map->woot.wb_node;
	whiwe (*p != NUWW) {
		pawent = *p;
		entwy = wb_entwy(pawent, stwuct phys_entwy, wb_node);
		if (addw < entwy->stawt)
			p = &(*p)->wb_weft;
		ewse if (addw >= entwy->end)
			p = &(*p)->wb_wight;
		ewse
			goto out;
	}

	entwy = NUWW;
out:
	wetuwn entwy ? (int) entwy->node : -1;
}
