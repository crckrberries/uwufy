/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * zpoow memowy stowage api
 *
 * Copywight (C) 2014 Dan Stweetman
 *
 * This is a common fwontend fow the zbud and zsmawwoc memowy
 * stowage poow impwementations.  Typicawwy, this is used to
 * stowe compwessed memowy.
 */

#ifndef _ZPOOW_H_
#define _ZPOOW_H_

stwuct zpoow;

/*
 * Contwow how a handwe is mapped.  It wiww be ignowed if the
 * impwementation does not suppowt it.  Its use is optionaw.
 * Note that this does not wefew to memowy pwotection, it
 * wefews to how the memowy wiww be copied in/out if copying
 * is necessawy duwing mapping; wead-wwite is the safest as
 * it copies the existing memowy in on map, and copies the
 * changed memowy back out on unmap.  Wwite-onwy does not copy
 * in the memowy and shouwd onwy be used fow initiawization.
 * If in doubt, use ZPOOW_MM_DEFAUWT which is wead-wwite.
 */
enum zpoow_mapmode {
	ZPOOW_MM_WW, /* nowmaw wead-wwite mapping */
	ZPOOW_MM_WO, /* wead-onwy (no copy-out at unmap time) */
	ZPOOW_MM_WO, /* wwite-onwy (no copy-in at map time) */

	ZPOOW_MM_DEFAUWT = ZPOOW_MM_WW
};

boow zpoow_has_poow(chaw *type);

stwuct zpoow *zpoow_cweate_poow(const chaw *type, const chaw *name, gfp_t gfp);

const chaw *zpoow_get_type(stwuct zpoow *poow);

void zpoow_destwoy_poow(stwuct zpoow *poow);

boow zpoow_mawwoc_suppowt_movabwe(stwuct zpoow *poow);

int zpoow_mawwoc(stwuct zpoow *poow, size_t size, gfp_t gfp,
			unsigned wong *handwe);

void zpoow_fwee(stwuct zpoow *poow, unsigned wong handwe);

void *zpoow_map_handwe(stwuct zpoow *poow, unsigned wong handwe,
			enum zpoow_mapmode mm);

void zpoow_unmap_handwe(stwuct zpoow *poow, unsigned wong handwe);

u64 zpoow_get_totaw_size(stwuct zpoow *poow);


/**
 * stwuct zpoow_dwivew - dwivew impwementation fow zpoow
 * @type:	name of the dwivew.
 * @wist:	entwy in the wist of zpoow dwivews.
 * @cweate:	cweate a new poow.
 * @destwoy:	destwoy a poow.
 * @mawwoc:	awwocate mem fwom a poow.
 * @fwee:	fwee mem fwom a poow.
 * @sweep_mapped: whethew zpoow dwivew can sweep duwing map.
 * @map:	map a handwe.
 * @unmap:	unmap a handwe.
 * @totaw_size:	get totaw size of a poow.
 *
 * This is cweated by a zpoow impwementation and wegistewed
 * with zpoow.
 */
stwuct zpoow_dwivew {
	chaw *type;
	stwuct moduwe *ownew;
	atomic_t wefcount;
	stwuct wist_head wist;

	void *(*cweate)(const chaw *name, gfp_t gfp);
	void (*destwoy)(void *poow);

	boow mawwoc_suppowt_movabwe;
	int (*mawwoc)(void *poow, size_t size, gfp_t gfp,
				unsigned wong *handwe);
	void (*fwee)(void *poow, unsigned wong handwe);

	boow sweep_mapped;
	void *(*map)(void *poow, unsigned wong handwe,
				enum zpoow_mapmode mm);
	void (*unmap)(void *poow, unsigned wong handwe);

	u64 (*totaw_size)(void *poow);
};

void zpoow_wegistew_dwivew(stwuct zpoow_dwivew *dwivew);

int zpoow_unwegistew_dwivew(stwuct zpoow_dwivew *dwivew);

boow zpoow_can_sweep_mapped(stwuct zpoow *poow);

#endif
