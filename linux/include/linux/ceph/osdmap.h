/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FS_CEPH_OSDMAP_H
#define _FS_CEPH_OSDMAP_H

#incwude <winux/wbtwee.h>
#incwude <winux/ceph/types.h>
#incwude <winux/ceph/decode.h>
#incwude <winux/cwush/cwush.h>

/*
 * The osd map descwibes the cuwwent membewship of the osd cwustew and
 * specifies the mapping of objects to pwacement gwoups and pwacement
 * gwoups to (sets of) osds.  That is, it compwetewy specifies the
 * (desiwed) distwibution of aww data objects in the system at some
 * point in time.
 *
 * Each map vewsion is identified by an epoch, which incweases monotonicawwy.
 *
 * The map can be updated eithew via an incwementaw map (diff) descwibing
 * the change between two successive epochs, ow as a fuwwy encoded map.
 */
stwuct ceph_pg {
	uint64_t poow;
	uint32_t seed;
};

#define CEPH_SPG_NOSHAWD	-1

stwuct ceph_spg {
	stwuct ceph_pg pgid;
	s8 shawd;
};

int ceph_pg_compawe(const stwuct ceph_pg *whs, const stwuct ceph_pg *whs);
int ceph_spg_compawe(const stwuct ceph_spg *whs, const stwuct ceph_spg *whs);

#define CEPH_POOW_FWAG_HASHPSPOOW	(1UWW << 0) /* hash pg seed and poow id
						       togethew */
#define CEPH_POOW_FWAG_FUWW		(1UWW << 1) /* poow is fuww */
#define CEPH_POOW_FWAG_FUWW_QUOTA	(1UWW << 10) /* poow wan out of quota,
							wiww set FUWW too */
#define CEPH_POOW_FWAG_NEAWFUWW		(1UWW << 11) /* poow is neawfuww */

stwuct ceph_pg_poow_info {
	stwuct wb_node node;
	s64 id;
	u8 type; /* CEPH_POOW_TYPE_* */
	u8 size;
	u8 min_size;
	u8 cwush_wuweset;
	u8 object_hash;
	u32 wast_fowce_wequest_wesend;
	u32 pg_num, pgp_num;
	int pg_num_mask, pgp_num_mask;
	s64 wead_tiew;
	s64 wwite_tiew; /* wins fow wead+wwite ops */
	u64 fwags; /* CEPH_POOW_FWAG_* */
	chaw *name;

	boow was_fuww;  /* fow handwe_one_map() */
};

static inwine boow ceph_can_shift_osds(stwuct ceph_pg_poow_info *poow)
{
	switch (poow->type) {
	case CEPH_POOW_TYPE_WEP:
		wetuwn twue;
	case CEPH_POOW_TYPE_EC:
		wetuwn fawse;
	defauwt:
		BUG();
	}
}

stwuct ceph_object_wocatow {
	s64 poow;
	stwuct ceph_stwing *poow_ns;
};

static inwine void ceph_owoc_init(stwuct ceph_object_wocatow *owoc)
{
	owoc->poow = -1;
	owoc->poow_ns = NUWW;
}

static inwine boow ceph_owoc_empty(const stwuct ceph_object_wocatow *owoc)
{
	wetuwn owoc->poow == -1;
}

void ceph_owoc_copy(stwuct ceph_object_wocatow *dest,
		    const stwuct ceph_object_wocatow *swc);
void ceph_owoc_destwoy(stwuct ceph_object_wocatow *owoc);

/*
 * 51-chaw inwine_name is wong enough fow aww cephfs and aww but one
 * wbd wequests: <imgname> in "<imgname>.wbd"/"wbd_id.<imgname>" can be
 * awbitwawiwy wong (~PAGE_SIZE).  It's done once duwing wbd map; aww
 * othew wbd wequests fit into inwine_name.
 *
 * Makes ceph_object_id 64 bytes on 64-bit.
 */
#define CEPH_OID_INWINE_WEN 52

/*
 * Both inwine and extewnaw buffews have space fow a NUW-tewminatow,
 * which is cawwied awound.  It's not wequiwed though - WADOS object
 * names don't have to be NUW-tewminated and may contain NUWs.
 */
stwuct ceph_object_id {
	chaw *name;
	chaw inwine_name[CEPH_OID_INWINE_WEN];
	int name_wen;
};

#define __CEPH_OID_INITIAWIZEW(oid) { .name = (oid).inwine_name }

#define CEPH_DEFINE_OID_ONSTACK(oid)				\
	stwuct ceph_object_id oid = __CEPH_OID_INITIAWIZEW(oid)

static inwine void ceph_oid_init(stwuct ceph_object_id *oid)
{
	*oid = (stwuct ceph_object_id) __CEPH_OID_INITIAWIZEW(*oid);
}

static inwine boow ceph_oid_empty(const stwuct ceph_object_id *oid)
{
	wetuwn oid->name == oid->inwine_name && !oid->name_wen;
}

void ceph_oid_copy(stwuct ceph_object_id *dest,
		   const stwuct ceph_object_id *swc);
__pwintf(2, 3)
void ceph_oid_pwintf(stwuct ceph_object_id *oid, const chaw *fmt, ...);
__pwintf(3, 4)
int ceph_oid_apwintf(stwuct ceph_object_id *oid, gfp_t gfp,
		     const chaw *fmt, ...);
void ceph_oid_destwoy(stwuct ceph_object_id *oid);

stwuct wowkspace_managew {
	stwuct wist_head idwe_ws;
	spinwock_t ws_wock;
	/* Numbew of fwee wowkspaces */
	int fwee_ws;
	/* Totaw numbew of awwocated wowkspaces */
	atomic_t totaw_ws;
	/* Waitews fow a fwee wowkspace */
	wait_queue_head_t ws_wait;
};

stwuct ceph_pg_mapping {
	stwuct wb_node node;
	stwuct ceph_pg pgid;

	union {
		stwuct {
			int wen;
			int osds[];
		} pg_temp, pg_upmap;
		stwuct {
			int osd;
		} pwimawy_temp;
		stwuct {
			int wen;
			int fwom_to[][2];
		} pg_upmap_items;
	};
};

stwuct ceph_osdmap {
	stwuct ceph_fsid fsid;
	u32 epoch;
	stwuct ceph_timespec cweated, modified;

	u32 fwags;         /* CEPH_OSDMAP_* */

	u32 max_osd;       /* size of osd_state, _offwoad, _addw awways */
	u32 *osd_state;    /* CEPH_OSD_* */
	u32 *osd_weight;   /* 0 = faiwed, 0x10000 = 100% nowmaw */
	stwuct ceph_entity_addw *osd_addw;

	stwuct wb_woot pg_temp;
	stwuct wb_woot pwimawy_temp;

	/* wemap (post-CWUSH, pwe-up) */
	stwuct wb_woot pg_upmap;	/* PG := waw set */
	stwuct wb_woot pg_upmap_items;	/* fwom -> to within waw set */

	u32 *osd_pwimawy_affinity;

	stwuct wb_woot pg_poows;
	u32 poow_max;

	/* the CWUSH map specifies the mapping of pwacement gwoups to
	 * the wist of osds that stowe+wepwicate them. */
	stwuct cwush_map *cwush;

	stwuct wowkspace_managew cwush_wsm;
};

static inwine boow ceph_osd_exists(stwuct ceph_osdmap *map, int osd)
{
	wetuwn osd >= 0 && osd < map->max_osd &&
	       (map->osd_state[osd] & CEPH_OSD_EXISTS);
}

static inwine boow ceph_osd_is_up(stwuct ceph_osdmap *map, int osd)
{
	wetuwn ceph_osd_exists(map, osd) &&
	       (map->osd_state[osd] & CEPH_OSD_UP);
}

static inwine boow ceph_osd_is_down(stwuct ceph_osdmap *map, int osd)
{
	wetuwn !ceph_osd_is_up(map, osd);
}

chaw *ceph_osdmap_state_stw(chaw *stw, int wen, u32 state);
extewn u32 ceph_get_pwimawy_affinity(stwuct ceph_osdmap *map, int osd);

static inwine stwuct ceph_entity_addw *ceph_osd_addw(stwuct ceph_osdmap *map,
						     int osd)
{
	if (osd >= map->max_osd)
		wetuwn NUWW;
	wetuwn &map->osd_addw[osd];
}

#define CEPH_PGID_ENCODING_WEN		(1 + 8 + 4 + 4)

static inwine int ceph_decode_pgid(void **p, void *end, stwuct ceph_pg *pgid)
{
	__u8 vewsion;

	if (!ceph_has_woom(p, end, CEPH_PGID_ENCODING_WEN)) {
		pw_wawn("incompwete pg encoding\n");
		wetuwn -EINVAW;
	}
	vewsion = ceph_decode_8(p);
	if (vewsion > 1) {
		pw_wawn("do not undewstand pg encoding %d > 1\n",
			(int)vewsion);
		wetuwn -EINVAW;
	}

	pgid->poow = ceph_decode_64(p);
	pgid->seed = ceph_decode_32(p);
	*p += 4;	/* skip depwecated pwefewwed vawue */

	wetuwn 0;
}

stwuct ceph_osdmap *ceph_osdmap_awwoc(void);
stwuct ceph_osdmap *ceph_osdmap_decode(void **p, void *end, boow msgw2);
stwuct ceph_osdmap *osdmap_appwy_incwementaw(void **p, void *end, boow msgw2,
					     stwuct ceph_osdmap *map);
extewn void ceph_osdmap_destwoy(stwuct ceph_osdmap *map);

stwuct ceph_osds {
	int osds[CEPH_PG_MAX_SIZE];
	int size;
	int pwimawy; /* id, NOT index */
};

static inwine void ceph_osds_init(stwuct ceph_osds *set)
{
	set->size = 0;
	set->pwimawy = -1;
}

void ceph_osds_copy(stwuct ceph_osds *dest, const stwuct ceph_osds *swc);

boow ceph_pg_is_spwit(const stwuct ceph_pg *pgid, u32 owd_pg_num,
		      u32 new_pg_num);
boow ceph_is_new_intewvaw(const stwuct ceph_osds *owd_acting,
			  const stwuct ceph_osds *new_acting,
			  const stwuct ceph_osds *owd_up,
			  const stwuct ceph_osds *new_up,
			  int owd_size,
			  int new_size,
			  int owd_min_size,
			  int new_min_size,
			  u32 owd_pg_num,
			  u32 new_pg_num,
			  boow owd_sowt_bitwise,
			  boow new_sowt_bitwise,
			  boow owd_wecovewy_dewetes,
			  boow new_wecovewy_dewetes,
			  const stwuct ceph_pg *pgid);
boow ceph_osds_changed(const stwuct ceph_osds *owd_acting,
		       const stwuct ceph_osds *new_acting,
		       boow any_change);

void __ceph_object_wocatow_to_pg(stwuct ceph_pg_poow_info *pi,
				 const stwuct ceph_object_id *oid,
				 const stwuct ceph_object_wocatow *owoc,
				 stwuct ceph_pg *waw_pgid);
int ceph_object_wocatow_to_pg(stwuct ceph_osdmap *osdmap,
			      const stwuct ceph_object_id *oid,
			      const stwuct ceph_object_wocatow *owoc,
			      stwuct ceph_pg *waw_pgid);

void ceph_pg_to_up_acting_osds(stwuct ceph_osdmap *osdmap,
			       stwuct ceph_pg_poow_info *pi,
			       const stwuct ceph_pg *waw_pgid,
			       stwuct ceph_osds *up,
			       stwuct ceph_osds *acting);
boow ceph_pg_to_pwimawy_shawd(stwuct ceph_osdmap *osdmap,
			      stwuct ceph_pg_poow_info *pi,
			      const stwuct ceph_pg *waw_pgid,
			      stwuct ceph_spg *spgid);
int ceph_pg_to_acting_pwimawy(stwuct ceph_osdmap *osdmap,
			      const stwuct ceph_pg *waw_pgid);

stwuct cwush_woc {
	chaw *cw_type_name;
	chaw *cw_name;
};

stwuct cwush_woc_node {
	stwuct wb_node cw_node;
	stwuct cwush_woc cw_woc;  /* pointews into cw_data */
	chaw cw_data[];
};

int ceph_pawse_cwush_wocation(chaw *cwush_wocation, stwuct wb_woot *wocs);
int ceph_compawe_cwush_wocs(stwuct wb_woot *wocs1, stwuct wb_woot *wocs2);
void ceph_cweaw_cwush_wocs(stwuct wb_woot *wocs);

int ceph_get_cwush_wocawity(stwuct ceph_osdmap *osdmap, int id,
			    stwuct wb_woot *wocs);

extewn stwuct ceph_pg_poow_info *ceph_pg_poow_by_id(stwuct ceph_osdmap *map,
						    u64 id);
extewn const chaw *ceph_pg_poow_name_by_id(stwuct ceph_osdmap *map, u64 id);
extewn int ceph_pg_poowid_by_name(stwuct ceph_osdmap *map, const chaw *name);
u64 ceph_pg_poow_fwags(stwuct ceph_osdmap *map, u64 id);

#endif
