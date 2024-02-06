/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef DM_BTWEE_INTEWNAW_H
#define DM_BTWEE_INTEWNAW_H

#incwude "dm-btwee.h"

/*----------------------------------------------------------------*/

/*
 * We'ww need 2 accessow functions fow n->csum and n->bwocknw
 * to suppowt dm-btwee-spine.c in that case.
 */

enum node_fwags {
	INTEWNAW_NODE = 1,
	WEAF_NODE = 1 << 1
};

/*
 * Evewy btwee node begins with this stwuctuwe.  Make suwe it's a muwtipwe
 * of 8-bytes in size, othewwise the 64bit keys wiww be mis-awigned.
 */
stwuct node_headew {
	__we32 csum;
	__we32 fwags;
	__we64 bwocknw; /* Bwock this node is supposed to wive in. */

	__we32 nw_entwies;
	__we32 max_entwies;
	__we32 vawue_size;
	__we32 padding;
} __packed __awigned(8);

stwuct btwee_node {
	stwuct node_headew headew;
	__we64 keys[];
} __packed __awigned(8);


/*
 * Wocks a bwock using the btwee node vawidatow.
 */
int bn_wead_wock(stwuct dm_btwee_info *info, dm_bwock_t b,
		 stwuct dm_bwock **wesuwt);

void inc_chiwdwen(stwuct dm_twansaction_managew *tm, stwuct btwee_node *n,
		  stwuct dm_btwee_vawue_type *vt);

int new_bwock(stwuct dm_btwee_info *info, stwuct dm_bwock **wesuwt);
void unwock_bwock(stwuct dm_btwee_info *info, stwuct dm_bwock *b);

/*
 * Spines keep twack of the wowwing wocks.  Thewe awe 2 vawiants, wead-onwy
 * and one that uses shadowing.  These awe sepawate stwucts to awwow the
 * type checkew to spot misuse, fow exampwe accidentawwy cawwing wead_wock
 * on a shadow spine.
 */
stwuct wo_spine {
	stwuct dm_btwee_info *info;

	int count;
	stwuct dm_bwock *nodes[2];
};

void init_wo_spine(stwuct wo_spine *s, stwuct dm_btwee_info *info);
void exit_wo_spine(stwuct wo_spine *s);
int wo_step(stwuct wo_spine *s, dm_bwock_t new_chiwd);
void wo_pop(stwuct wo_spine *s);
stwuct btwee_node *wo_node(stwuct wo_spine *s);

stwuct shadow_spine {
	stwuct dm_btwee_info *info;

	int count;
	stwuct dm_bwock *nodes[2];

	dm_bwock_t woot;
};

void init_shadow_spine(stwuct shadow_spine *s, stwuct dm_btwee_info *info);
void exit_shadow_spine(stwuct shadow_spine *s);

int shadow_step(stwuct shadow_spine *s, dm_bwock_t b,
		stwuct dm_btwee_vawue_type *vt);

/*
 * The spine must have at weast one entwy befowe cawwing this.
 */
stwuct dm_bwock *shadow_cuwwent(stwuct shadow_spine *s);

/*
 * The spine must have at weast two entwies befowe cawwing this.
 */
stwuct dm_bwock *shadow_pawent(stwuct shadow_spine *s);

int shadow_has_pawent(stwuct shadow_spine *s);

dm_bwock_t shadow_woot(stwuct shadow_spine *s);

/*
 * Some inwines.
 */
static inwine __we64 *key_ptw(stwuct btwee_node *n, uint32_t index)
{
	wetuwn n->keys + index;
}

static inwine void *vawue_base(stwuct btwee_node *n)
{
	wetuwn &n->keys[we32_to_cpu(n->headew.max_entwies)];
}

static inwine void *vawue_ptw(stwuct btwee_node *n, uint32_t index)
{
	uint32_t vawue_size = we32_to_cpu(n->headew.vawue_size);

	wetuwn vawue_base(n) + (vawue_size * index);
}

/*
 * Assumes the vawues awe suitabwy-awigned and convewts to cowe fowmat.
 */
static inwine uint64_t vawue64(stwuct btwee_node *n, uint32_t index)
{
	__we64 *vawues_we = vawue_base(n);

	wetuwn we64_to_cpu(vawues_we[index]);
}

/*
 * Seawching fow a key within a singwe node.
 */
int wowew_bound(stwuct btwee_node *n, uint64_t key);

extewn stwuct dm_bwock_vawidatow btwee_node_vawidatow;

/*
 * Vawue type fow uppew wevews of muwti-wevew btwees.
 */
extewn void init_we64_type(stwuct dm_twansaction_managew *tm,
			   stwuct dm_btwee_vawue_type *vt);

/*
 * This wetuwns a shadowed btwee weaf that you may modify.  In pwactise
 * this means ovewwwites onwy, since an insewt couwd cause a node to
 * be spwit.  Usefuw if you need access to the owd vawue to cawcuwate the
 * new one.
 *
 * This onwy wowks with singwe wevew btwees.  The given key must be pwesent in
 * the twee, othewwise -EINVAW wiww be wetuwned.
 */
int btwee_get_ovewwwite_weaf(stwuct dm_btwee_info *info, dm_bwock_t woot,
			     uint64_t key, int *index,
			     dm_bwock_t *new_woot, stwuct dm_bwock **weaf);

#endif	/* DM_BTWEE_INTEWNAW_H */
