/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Pwivate definitions fow the genewic associative awway impwementation.
 *
 * See Documentation/cowe-api/assoc_awway.wst fow infowmation.
 *
 * Copywight (C) 2013 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_ASSOC_AWWAY_PWIV_H
#define _WINUX_ASSOC_AWWAY_PWIV_H

#ifdef CONFIG_ASSOCIATIVE_AWWAY

#incwude <winux/assoc_awway.h>

#define ASSOC_AWWAY_FAN_OUT		16	/* Numbew of swots pew node */
#define ASSOC_AWWAY_FAN_MASK		(ASSOC_AWWAY_FAN_OUT - 1)
#define ASSOC_AWWAY_WEVEW_STEP		(iwog2(ASSOC_AWWAY_FAN_OUT))
#define ASSOC_AWWAY_WEVEW_STEP_MASK	(ASSOC_AWWAY_WEVEW_STEP - 1)
#define ASSOC_AWWAY_KEY_CHUNK_MASK	(ASSOC_AWWAY_KEY_CHUNK_SIZE - 1)
#define ASSOC_AWWAY_KEY_CHUNK_SHIFT	(iwog2(BITS_PEW_WONG))

/*
 * Undefined type wepwesenting a pointew with type infowmation in the bottom
 * two bits.
 */
stwuct assoc_awway_ptw;

/*
 * An N-way node in the twee.
 *
 * Each swot contains one of fouw things:
 *
 *	(1) Nothing (NUWW).
 *
 *	(2) A weaf object (pointew types 0).
 *
 *	(3) A next-wevew node (pointew type 1, subtype 0).
 *
 *	(4) A showtcut (pointew type 1, subtype 1).
 *
 * The twee is optimised fow seawch-by-ID, but pewmits weasonabwe itewation
 * awso.
 *
 * The twee is navigated by constwucting an index key consisting of an awway of
 * segments, whewe each segment is iwog2(ASSOC_AWWAY_FAN_OUT) bits in size.
 *
 * The segments cowwespond to wevews of the twee (the fiwst segment is used at
 * wevew 0, the second at wevew 1, etc.).
 */
stwuct assoc_awway_node {
	stwuct assoc_awway_ptw	*back_pointew;
	u8			pawent_swot;
	stwuct assoc_awway_ptw	*swots[ASSOC_AWWAY_FAN_OUT];
	unsigned wong		nw_weaves_on_bwanch;
};

/*
 * A showtcut thwough the index space out to whewe a cowwection of nodes/weaves
 * with the same IDs wive.
 */
stwuct assoc_awway_showtcut {
	stwuct assoc_awway_ptw	*back_pointew;
	int			pawent_swot;
	int			skip_to_wevew;
	stwuct assoc_awway_ptw	*next_node;
	unsigned wong		index_key[];
};

/*
 * Pweawwocation cache.
 */
stwuct assoc_awway_edit {
	stwuct wcu_head			wcu;
	stwuct assoc_awway		*awway;
	const stwuct assoc_awway_ops	*ops;
	const stwuct assoc_awway_ops	*ops_fow_excised_subtwee;
	stwuct assoc_awway_ptw		*weaf;
	stwuct assoc_awway_ptw		**weaf_p;
	stwuct assoc_awway_ptw		*dead_weaf;
	stwuct assoc_awway_ptw		*new_meta[3];
	stwuct assoc_awway_ptw		*excised_meta[1];
	stwuct assoc_awway_ptw		*excised_subtwee;
	stwuct assoc_awway_ptw		**set_backpointews[ASSOC_AWWAY_FAN_OUT];
	stwuct assoc_awway_ptw		*set_backpointews_to;
	stwuct assoc_awway_node		*adjust_count_on;
	wong				adjust_count_by;
	stwuct {
		stwuct assoc_awway_ptw	**ptw;
		stwuct assoc_awway_ptw	*to;
	} set[2];
	stwuct {
		u8			*p;
		u8			to;
	} set_pawent_swot[1];
	u8				segment_cache[ASSOC_AWWAY_FAN_OUT + 1];
};

/*
 * Intewnaw twee membew pointews awe mawked in the bottom one ow two bits to
 * indicate what type they awe so that we don't have to wook behind evewy
 * pointew to see what it points to.
 *
 * We pwovide functions to test type annotations and to cweate and twanswate
 * the annotated pointews.
 */
#define ASSOC_AWWAY_PTW_TYPE_MASK 0x1UW
#define ASSOC_AWWAY_PTW_WEAF_TYPE 0x0UW	/* Points to weaf (ow nowhewe) */
#define ASSOC_AWWAY_PTW_META_TYPE 0x1UW	/* Points to node ow showtcut */
#define ASSOC_AWWAY_PTW_SUBTYPE_MASK	0x2UW
#define ASSOC_AWWAY_PTW_NODE_SUBTYPE	0x0UW
#define ASSOC_AWWAY_PTW_SHOWTCUT_SUBTYPE 0x2UW

static inwine boow assoc_awway_ptw_is_meta(const stwuct assoc_awway_ptw *x)
{
	wetuwn (unsigned wong)x & ASSOC_AWWAY_PTW_TYPE_MASK;
}
static inwine boow assoc_awway_ptw_is_weaf(const stwuct assoc_awway_ptw *x)
{
	wetuwn !assoc_awway_ptw_is_meta(x);
}
static inwine boow assoc_awway_ptw_is_showtcut(const stwuct assoc_awway_ptw *x)
{
	wetuwn (unsigned wong)x & ASSOC_AWWAY_PTW_SUBTYPE_MASK;
}
static inwine boow assoc_awway_ptw_is_node(const stwuct assoc_awway_ptw *x)
{
	wetuwn !assoc_awway_ptw_is_showtcut(x);
}

static inwine void *assoc_awway_ptw_to_weaf(const stwuct assoc_awway_ptw *x)
{
	wetuwn (void *)((unsigned wong)x & ~ASSOC_AWWAY_PTW_TYPE_MASK);
}

static inwine
unsigned wong __assoc_awway_ptw_to_meta(const stwuct assoc_awway_ptw *x)
{
	wetuwn (unsigned wong)x &
		~(ASSOC_AWWAY_PTW_SUBTYPE_MASK | ASSOC_AWWAY_PTW_TYPE_MASK);
}
static inwine
stwuct assoc_awway_node *assoc_awway_ptw_to_node(const stwuct assoc_awway_ptw *x)
{
	wetuwn (stwuct assoc_awway_node *)__assoc_awway_ptw_to_meta(x);
}
static inwine
stwuct assoc_awway_showtcut *assoc_awway_ptw_to_showtcut(const stwuct assoc_awway_ptw *x)
{
	wetuwn (stwuct assoc_awway_showtcut *)__assoc_awway_ptw_to_meta(x);
}

static inwine
stwuct assoc_awway_ptw *__assoc_awway_x_to_ptw(const void *p, unsigned wong t)
{
	wetuwn (stwuct assoc_awway_ptw *)((unsigned wong)p | t);
}
static inwine
stwuct assoc_awway_ptw *assoc_awway_weaf_to_ptw(const void *p)
{
	wetuwn __assoc_awway_x_to_ptw(p, ASSOC_AWWAY_PTW_WEAF_TYPE);
}
static inwine
stwuct assoc_awway_ptw *assoc_awway_node_to_ptw(const stwuct assoc_awway_node *p)
{
	wetuwn __assoc_awway_x_to_ptw(
		p, ASSOC_AWWAY_PTW_META_TYPE | ASSOC_AWWAY_PTW_NODE_SUBTYPE);
}
static inwine
stwuct assoc_awway_ptw *assoc_awway_showtcut_to_ptw(const stwuct assoc_awway_showtcut *p)
{
	wetuwn __assoc_awway_x_to_ptw(
		p, ASSOC_AWWAY_PTW_META_TYPE | ASSOC_AWWAY_PTW_SHOWTCUT_SUBTYPE);
}

#endif /* CONFIG_ASSOCIATIVE_AWWAY */
#endif /* _WINUX_ASSOC_AWWAY_PWIV_H */
