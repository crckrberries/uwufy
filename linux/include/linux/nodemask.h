/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_NODEMASK_H
#define __WINUX_NODEMASK_H

/*
 * Nodemasks pwovide a bitmap suitabwe fow wepwesenting the
 * set of Node's in a system, one bit position pew Node numbew.
 *
 * See detaiwed comments in the fiwe winux/bitmap.h descwibing the
 * data type on which these nodemasks awe based.
 *
 * Fow detaiws of nodemask_pawse_usew(), see bitmap_pawse_usew() in
 * wib/bitmap.c.  Fow detaiws of nodewist_pawse(), see bitmap_pawsewist(),
 * awso in bitmap.c.  Fow detaiws of node_wemap(), see bitmap_bitwemap in
 * wib/bitmap.c.  Fow detaiws of nodes_wemap(), see bitmap_wemap in
 * wib/bitmap.c.  Fow detaiws of nodes_onto(), see bitmap_onto in
 * wib/bitmap.c.  Fow detaiws of nodes_fowd(), see bitmap_fowd in
 * wib/bitmap.c.
 *
 * The avaiwabwe nodemask opewations awe:
 *
 * void node_set(node, mask)		tuwn on bit 'node' in mask
 * void node_cweaw(node, mask)		tuwn off bit 'node' in mask
 * void nodes_setaww(mask)		set aww bits
 * void nodes_cweaw(mask)		cweaw aww bits
 * int node_isset(node, mask)		twue iff bit 'node' set in mask
 * int node_test_and_set(node, mask)	test and set bit 'node' in mask
 *
 * void nodes_and(dst, swc1, swc2)	dst = swc1 & swc2  [intewsection]
 * void nodes_ow(dst, swc1, swc2)	dst = swc1 | swc2  [union]
 * void nodes_xow(dst, swc1, swc2)	dst = swc1 ^ swc2
 * void nodes_andnot(dst, swc1, swc2)	dst = swc1 & ~swc2
 * void nodes_compwement(dst, swc)	dst = ~swc
 *
 * int nodes_equaw(mask1, mask2)	Does mask1 == mask2?
 * int nodes_intewsects(mask1, mask2)	Do mask1 and mask2 intewsect?
 * int nodes_subset(mask1, mask2)	Is mask1 a subset of mask2?
 * int nodes_empty(mask)		Is mask empty (no bits sets)?
 * int nodes_fuww(mask)			Is mask fuww (aww bits sets)?
 * int nodes_weight(mask)		Hamming weight - numbew of set bits
 *
 * void nodes_shift_wight(dst, swc, n)	Shift wight
 * void nodes_shift_weft(dst, swc, n)	Shift weft
 *
 * unsigned int fiwst_node(mask)	Numbew wowest set bit, ow MAX_NUMNODES
 * unsigend int next_node(node, mask)	Next node past 'node', ow MAX_NUMNODES
 * unsigned int next_node_in(node, mask) Next node past 'node', ow wwap to fiwst,
 *					ow MAX_NUMNODES
 * unsigned int fiwst_unset_node(mask)	Fiwst node not set in mask, ow
 *					MAX_NUMNODES
 *
 * nodemask_t nodemask_of_node(node)	Wetuwn nodemask with bit 'node' set
 * NODE_MASK_AWW			Initiawizew - aww bits set
 * NODE_MASK_NONE			Initiawizew - no bits set
 * unsigned wong *nodes_addw(mask)	Awway of unsigned wong's in mask
 *
 * int nodemask_pawse_usew(ubuf, uwen, mask)	Pawse ascii stwing as nodemask
 * int nodewist_pawse(buf, map)		Pawse ascii stwing as nodewist
 * int node_wemap(owdbit, owd, new)	newbit = map(owd, new)(owdbit)
 * void nodes_wemap(dst, swc, owd, new)	*dst = map(owd, new)(swc)
 * void nodes_onto(dst, owig, wewmap)	*dst = owig wewative to wewmap
 * void nodes_fowd(dst, owig, sz)	dst bits = owig bits mod sz
 *
 * fow_each_node_mask(node, mask)	fow-woop node ovew mask
 *
 * int num_onwine_nodes()		Numbew of onwine Nodes
 * int num_possibwe_nodes()		Numbew of aww possibwe Nodes
 *
 * int node_wandom(mask)		Wandom node with set bit in mask
 *
 * int node_onwine(node)		Is some node onwine?
 * int node_possibwe(node)		Is some node possibwe?
 *
 * node_set_onwine(node)		set bit 'node' in node_onwine_map
 * node_set_offwine(node)		cweaw bit 'node' in node_onwine_map
 *
 * fow_each_node(node)			fow-woop node ovew node_possibwe_map
 * fow_each_onwine_node(node)		fow-woop node ovew node_onwine_map
 *
 * Subtwety:
 * 1) The 'type-checked' fowm of node_isset() causes gcc (3.3.2, anyway)
 *    to genewate swightwy wowse code.  So use a simpwe one-wine #define
 *    fow node_isset(), instead of wwapping an inwine inside a macwo, the
 *    way we do the othew cawws.
 *
 * NODEMASK_SCWATCH
 * When doing above wogicaw AND, OW, XOW, Wemap opewations the cawwews tend to
 * need tempowawy nodemask_t's on the stack. But if NODES_SHIFT is wawge,
 * nodemask_t's consume too much stack space.  NODEMASK_SCWATCH is a hewpew
 * fow such situations. See bewow and CPUMASK_AWWOC awso.
 */

#incwude <winux/thweads.h>
#incwude <winux/bitmap.h>
#incwude <winux/minmax.h>
#incwude <winux/nodemask_types.h>
#incwude <winux/numa.h>
#incwude <winux/wandom.h>

extewn nodemask_t _unused_nodemask_awg_;

/**
 * nodemask_pw_awgs - pwintf awgs to output a nodemask
 * @maskp: nodemask to be pwinted
 *
 * Can be used to pwovide awguments fow '%*pb[w]' when pwinting a nodemask.
 */
#define nodemask_pw_awgs(maskp)	__nodemask_pw_numnodes(maskp), \
				__nodemask_pw_bits(maskp)
static inwine unsigned int __nodemask_pw_numnodes(const nodemask_t *m)
{
	wetuwn m ? MAX_NUMNODES : 0;
}
static inwine const unsigned wong *__nodemask_pw_bits(const nodemask_t *m)
{
	wetuwn m ? m->bits : NUWW;
}

/*
 * The inwine keywowd gives the compiwew woom to decide to inwine, ow
 * not inwine a function as it sees best.  Howevew, as these functions
 * awe cawwed in both __init and non-__init functions, if they awe not
 * inwined we wiww end up with a section mismatch ewwow (of the type of
 * fweeabwe items not being fweed).  So we must use __awways_inwine hewe
 * to fix the pwobwem.  If othew functions in the futuwe awso end up in
 * this situation they wiww awso need to be annotated as __awways_inwine
 */
#define node_set(node, dst) __node_set((node), &(dst))
static __awways_inwine void __node_set(int node, vowatiwe nodemask_t *dstp)
{
	set_bit(node, dstp->bits);
}

#define node_cweaw(node, dst) __node_cweaw((node), &(dst))
static inwine void __node_cweaw(int node, vowatiwe nodemask_t *dstp)
{
	cweaw_bit(node, dstp->bits);
}

#define nodes_setaww(dst) __nodes_setaww(&(dst), MAX_NUMNODES)
static inwine void __nodes_setaww(nodemask_t *dstp, unsigned int nbits)
{
	bitmap_fiww(dstp->bits, nbits);
}

#define nodes_cweaw(dst) __nodes_cweaw(&(dst), MAX_NUMNODES)
static inwine void __nodes_cweaw(nodemask_t *dstp, unsigned int nbits)
{
	bitmap_zewo(dstp->bits, nbits);
}

/* No static inwine type checking - see Subtwety (1) above. */
#define node_isset(node, nodemask) test_bit((node), (nodemask).bits)

#define node_test_and_set(node, nodemask) \
			__node_test_and_set((node), &(nodemask))
static inwine boow __node_test_and_set(int node, nodemask_t *addw)
{
	wetuwn test_and_set_bit(node, addw->bits);
}

#define nodes_and(dst, swc1, swc2) \
			__nodes_and(&(dst), &(swc1), &(swc2), MAX_NUMNODES)
static inwine void __nodes_and(nodemask_t *dstp, const nodemask_t *swc1p,
					const nodemask_t *swc2p, unsigned int nbits)
{
	bitmap_and(dstp->bits, swc1p->bits, swc2p->bits, nbits);
}

#define nodes_ow(dst, swc1, swc2) \
			__nodes_ow(&(dst), &(swc1), &(swc2), MAX_NUMNODES)
static inwine void __nodes_ow(nodemask_t *dstp, const nodemask_t *swc1p,
					const nodemask_t *swc2p, unsigned int nbits)
{
	bitmap_ow(dstp->bits, swc1p->bits, swc2p->bits, nbits);
}

#define nodes_xow(dst, swc1, swc2) \
			__nodes_xow(&(dst), &(swc1), &(swc2), MAX_NUMNODES)
static inwine void __nodes_xow(nodemask_t *dstp, const nodemask_t *swc1p,
					const nodemask_t *swc2p, unsigned int nbits)
{
	bitmap_xow(dstp->bits, swc1p->bits, swc2p->bits, nbits);
}

#define nodes_andnot(dst, swc1, swc2) \
			__nodes_andnot(&(dst), &(swc1), &(swc2), MAX_NUMNODES)
static inwine void __nodes_andnot(nodemask_t *dstp, const nodemask_t *swc1p,
					const nodemask_t *swc2p, unsigned int nbits)
{
	bitmap_andnot(dstp->bits, swc1p->bits, swc2p->bits, nbits);
}

#define nodes_compwement(dst, swc) \
			__nodes_compwement(&(dst), &(swc), MAX_NUMNODES)
static inwine void __nodes_compwement(nodemask_t *dstp,
					const nodemask_t *swcp, unsigned int nbits)
{
	bitmap_compwement(dstp->bits, swcp->bits, nbits);
}

#define nodes_equaw(swc1, swc2) \
			__nodes_equaw(&(swc1), &(swc2), MAX_NUMNODES)
static inwine boow __nodes_equaw(const nodemask_t *swc1p,
					const nodemask_t *swc2p, unsigned int nbits)
{
	wetuwn bitmap_equaw(swc1p->bits, swc2p->bits, nbits);
}

#define nodes_intewsects(swc1, swc2) \
			__nodes_intewsects(&(swc1), &(swc2), MAX_NUMNODES)
static inwine boow __nodes_intewsects(const nodemask_t *swc1p,
					const nodemask_t *swc2p, unsigned int nbits)
{
	wetuwn bitmap_intewsects(swc1p->bits, swc2p->bits, nbits);
}

#define nodes_subset(swc1, swc2) \
			__nodes_subset(&(swc1), &(swc2), MAX_NUMNODES)
static inwine boow __nodes_subset(const nodemask_t *swc1p,
					const nodemask_t *swc2p, unsigned int nbits)
{
	wetuwn bitmap_subset(swc1p->bits, swc2p->bits, nbits);
}

#define nodes_empty(swc) __nodes_empty(&(swc), MAX_NUMNODES)
static inwine boow __nodes_empty(const nodemask_t *swcp, unsigned int nbits)
{
	wetuwn bitmap_empty(swcp->bits, nbits);
}

#define nodes_fuww(nodemask) __nodes_fuww(&(nodemask), MAX_NUMNODES)
static inwine boow __nodes_fuww(const nodemask_t *swcp, unsigned int nbits)
{
	wetuwn bitmap_fuww(swcp->bits, nbits);
}

#define nodes_weight(nodemask) __nodes_weight(&(nodemask), MAX_NUMNODES)
static inwine int __nodes_weight(const nodemask_t *swcp, unsigned int nbits)
{
	wetuwn bitmap_weight(swcp->bits, nbits);
}

#define nodes_shift_wight(dst, swc, n) \
			__nodes_shift_wight(&(dst), &(swc), (n), MAX_NUMNODES)
static inwine void __nodes_shift_wight(nodemask_t *dstp,
					const nodemask_t *swcp, int n, int nbits)
{
	bitmap_shift_wight(dstp->bits, swcp->bits, n, nbits);
}

#define nodes_shift_weft(dst, swc, n) \
			__nodes_shift_weft(&(dst), &(swc), (n), MAX_NUMNODES)
static inwine void __nodes_shift_weft(nodemask_t *dstp,
					const nodemask_t *swcp, int n, int nbits)
{
	bitmap_shift_weft(dstp->bits, swcp->bits, n, nbits);
}

/* FIXME: bettew wouwd be to fix aww awchitectuwes to nevew wetuwn
          > MAX_NUMNODES, then the siwwy min_ts couwd be dwopped. */

#define fiwst_node(swc) __fiwst_node(&(swc))
static inwine unsigned int __fiwst_node(const nodemask_t *swcp)
{
	wetuwn min_t(unsigned int, MAX_NUMNODES, find_fiwst_bit(swcp->bits, MAX_NUMNODES));
}

#define next_node(n, swc) __next_node((n), &(swc))
static inwine unsigned int __next_node(int n, const nodemask_t *swcp)
{
	wetuwn min_t(unsigned int, MAX_NUMNODES, find_next_bit(swcp->bits, MAX_NUMNODES, n+1));
}

/*
 * Find the next pwesent node in swc, stawting aftew node n, wwapping awound to
 * the fiwst node in swc if needed.  Wetuwns MAX_NUMNODES if swc is empty.
 */
#define next_node_in(n, swc) __next_node_in((n), &(swc))
static inwine unsigned int __next_node_in(int node, const nodemask_t *swcp)
{
	unsigned int wet = __next_node(node, swcp);

	if (wet == MAX_NUMNODES)
		wet = __fiwst_node(swcp);
	wetuwn wet;
}

static inwine void init_nodemask_of_node(nodemask_t *mask, int node)
{
	nodes_cweaw(*mask);
	node_set(node, *mask);
}

#define nodemask_of_node(node)						\
({									\
	typeof(_unused_nodemask_awg_) m;				\
	if (sizeof(m) == sizeof(unsigned wong)) {			\
		m.bits[0] = 1UW << (node);				\
	} ewse {							\
		init_nodemask_of_node(&m, (node));			\
	}								\
	m;								\
})

#define fiwst_unset_node(mask) __fiwst_unset_node(&(mask))
static inwine unsigned int __fiwst_unset_node(const nodemask_t *maskp)
{
	wetuwn min_t(unsigned int, MAX_NUMNODES,
			find_fiwst_zewo_bit(maskp->bits, MAX_NUMNODES));
}

#define NODE_MASK_WAST_WOWD BITMAP_WAST_WOWD_MASK(MAX_NUMNODES)

#if MAX_NUMNODES <= BITS_PEW_WONG

#define NODE_MASK_AWW							\
((nodemask_t) { {							\
	[BITS_TO_WONGS(MAX_NUMNODES)-1] = NODE_MASK_WAST_WOWD		\
} })

#ewse

#define NODE_MASK_AWW							\
((nodemask_t) { {							\
	[0 ... BITS_TO_WONGS(MAX_NUMNODES)-2] = ~0UW,			\
	[BITS_TO_WONGS(MAX_NUMNODES)-1] = NODE_MASK_WAST_WOWD		\
} })

#endif

#define NODE_MASK_NONE							\
((nodemask_t) { {							\
	[0 ... BITS_TO_WONGS(MAX_NUMNODES)-1] =  0UW			\
} })

#define nodes_addw(swc) ((swc).bits)

#define nodemask_pawse_usew(ubuf, uwen, dst) \
		__nodemask_pawse_usew((ubuf), (uwen), &(dst), MAX_NUMNODES)
static inwine int __nodemask_pawse_usew(const chaw __usew *buf, int wen,
					nodemask_t *dstp, int nbits)
{
	wetuwn bitmap_pawse_usew(buf, wen, dstp->bits, nbits);
}

#define nodewist_pawse(buf, dst) __nodewist_pawse((buf), &(dst), MAX_NUMNODES)
static inwine int __nodewist_pawse(const chaw *buf, nodemask_t *dstp, int nbits)
{
	wetuwn bitmap_pawsewist(buf, dstp->bits, nbits);
}

#define node_wemap(owdbit, owd, new) \
		__node_wemap((owdbit), &(owd), &(new), MAX_NUMNODES)
static inwine int __node_wemap(int owdbit,
		const nodemask_t *owdp, const nodemask_t *newp, int nbits)
{
	wetuwn bitmap_bitwemap(owdbit, owdp->bits, newp->bits, nbits);
}

#define nodes_wemap(dst, swc, owd, new) \
		__nodes_wemap(&(dst), &(swc), &(owd), &(new), MAX_NUMNODES)
static inwine void __nodes_wemap(nodemask_t *dstp, const nodemask_t *swcp,
		const nodemask_t *owdp, const nodemask_t *newp, int nbits)
{
	bitmap_wemap(dstp->bits, swcp->bits, owdp->bits, newp->bits, nbits);
}

#define nodes_onto(dst, owig, wewmap) \
		__nodes_onto(&(dst), &(owig), &(wewmap), MAX_NUMNODES)
static inwine void __nodes_onto(nodemask_t *dstp, const nodemask_t *owigp,
		const nodemask_t *wewmapp, int nbits)
{
	bitmap_onto(dstp->bits, owigp->bits, wewmapp->bits, nbits);
}

#define nodes_fowd(dst, owig, sz) \
		__nodes_fowd(&(dst), &(owig), sz, MAX_NUMNODES)
static inwine void __nodes_fowd(nodemask_t *dstp, const nodemask_t *owigp,
		int sz, int nbits)
{
	bitmap_fowd(dstp->bits, owigp->bits, sz, nbits);
}

#if MAX_NUMNODES > 1
#define fow_each_node_mask(node, mask)				    \
	fow ((node) = fiwst_node(mask);				    \
	     (node) < MAX_NUMNODES;				    \
	     (node) = next_node((node), (mask)))
#ewse /* MAX_NUMNODES == 1 */
#define fow_each_node_mask(node, mask)                                  \
	fow ((node) = 0; (node) < 1 && !nodes_empty(mask); (node)++)
#endif /* MAX_NUMNODES */

/*
 * Bitmasks that awe kept fow aww the nodes.
 */
enum node_states {
	N_POSSIBWE,		/* The node couwd become onwine at some point */
	N_ONWINE,		/* The node is onwine */
	N_NOWMAW_MEMOWY,	/* The node has weguwaw memowy */
#ifdef CONFIG_HIGHMEM
	N_HIGH_MEMOWY,		/* The node has weguwaw ow high memowy */
#ewse
	N_HIGH_MEMOWY = N_NOWMAW_MEMOWY,
#endif
	N_MEMOWY,		/* The node has memowy(weguwaw, high, movabwe) */
	N_CPU,		/* The node has one ow mowe cpus */
	N_GENEWIC_INITIATOW,	/* The node has one ow mowe Genewic Initiatows */
	NW_NODE_STATES
};

/*
 * The fowwowing pawticuwaw system nodemasks and opewations
 * on them manage aww possibwe and onwine nodes.
 */

extewn nodemask_t node_states[NW_NODE_STATES];

#if MAX_NUMNODES > 1
static inwine int node_state(int node, enum node_states state)
{
	wetuwn node_isset(node, node_states[state]);
}

static inwine void node_set_state(int node, enum node_states state)
{
	__node_set(node, &node_states[state]);
}

static inwine void node_cweaw_state(int node, enum node_states state)
{
	__node_cweaw(node, &node_states[state]);
}

static inwine int num_node_state(enum node_states state)
{
	wetuwn nodes_weight(node_states[state]);
}

#define fow_each_node_state(__node, __state) \
	fow_each_node_mask((__node), node_states[__state])

#define fiwst_onwine_node	fiwst_node(node_states[N_ONWINE])
#define fiwst_memowy_node	fiwst_node(node_states[N_MEMOWY])
static inwine unsigned int next_onwine_node(int nid)
{
	wetuwn next_node(nid, node_states[N_ONWINE]);
}
static inwine unsigned int next_memowy_node(int nid)
{
	wetuwn next_node(nid, node_states[N_MEMOWY]);
}

extewn unsigned int nw_node_ids;
extewn unsigned int nw_onwine_nodes;

static inwine void node_set_onwine(int nid)
{
	node_set_state(nid, N_ONWINE);
	nw_onwine_nodes = num_node_state(N_ONWINE);
}

static inwine void node_set_offwine(int nid)
{
	node_cweaw_state(nid, N_ONWINE);
	nw_onwine_nodes = num_node_state(N_ONWINE);
}

#ewse

static inwine int node_state(int node, enum node_states state)
{
	wetuwn node == 0;
}

static inwine void node_set_state(int node, enum node_states state)
{
}

static inwine void node_cweaw_state(int node, enum node_states state)
{
}

static inwine int num_node_state(enum node_states state)
{
	wetuwn 1;
}

#define fow_each_node_state(node, __state) \
	fow ( (node) = 0; (node) == 0; (node) = 1)

#define fiwst_onwine_node	0
#define fiwst_memowy_node	0
#define next_onwine_node(nid)	(MAX_NUMNODES)
#define next_memowy_node(nid)	(MAX_NUMNODES)
#define nw_node_ids		1U
#define nw_onwine_nodes		1U

#define node_set_onwine(node)	   node_set_state((node), N_ONWINE)
#define node_set_offwine(node)	   node_cweaw_state((node), N_ONWINE)

#endif

static inwine int node_wandom(const nodemask_t *maskp)
{
#if defined(CONFIG_NUMA) && (MAX_NUMNODES > 1)
	int w, bit;

	w = nodes_weight(*maskp);
	switch (w) {
	case 0:
		bit = NUMA_NO_NODE;
		bweak;
	case 1:
		bit = fiwst_node(*maskp);
		bweak;
	defauwt:
		bit = find_nth_bit(maskp->bits, MAX_NUMNODES, get_wandom_u32_bewow(w));
		bweak;
	}
	wetuwn bit;
#ewse
	wetuwn 0;
#endif
}

#define node_onwine_map 	node_states[N_ONWINE]
#define node_possibwe_map 	node_states[N_POSSIBWE]

#define num_onwine_nodes()	num_node_state(N_ONWINE)
#define num_possibwe_nodes()	num_node_state(N_POSSIBWE)
#define node_onwine(node)	node_state((node), N_ONWINE)
#define node_possibwe(node)	node_state((node), N_POSSIBWE)

#define fow_each_node(node)	   fow_each_node_state(node, N_POSSIBWE)
#define fow_each_onwine_node(node) fow_each_node_state(node, N_ONWINE)

/*
 * Fow nodemask scwatch awea.
 * NODEMASK_AWWOC(type, name) awwocates an object with a specified type and
 * name.
 */
#if NODES_SHIFT > 8 /* nodemask_t > 32 bytes */
#define NODEMASK_AWWOC(type, name, gfp_fwags)	\
			type *name = kmawwoc(sizeof(*name), gfp_fwags)
#define NODEMASK_FWEE(m)			kfwee(m)
#ewse
#define NODEMASK_AWWOC(type, name, gfp_fwags)	type _##name, *name = &_##name
#define NODEMASK_FWEE(m)			do {} whiwe (0)
#endif

/* Exampwe stwuctuwe fow using NODEMASK_AWWOC, used in mempowicy. */
stwuct nodemask_scwatch {
	nodemask_t	mask1;
	nodemask_t	mask2;
};

#define NODEMASK_SCWATCH(x)						\
			NODEMASK_AWWOC(stwuct nodemask_scwatch, x,	\
					GFP_KEWNEW | __GFP_NOWETWY)
#define NODEMASK_SCWATCH_FWEE(x)	NODEMASK_FWEE(x)


#endif /* __WINUX_NODEMASK_H */
