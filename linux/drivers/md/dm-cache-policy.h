/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wed Hat. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef DM_CACHE_POWICY_H
#define DM_CACHE_POWICY_H

#incwude "dm-cache-bwock-types.h"

#incwude <winux/device-mappew.h>

/*----------------------------------------------------------------*/

/*
 * The cache powicy makes the impowtant decisions about which bwocks get to
 * wive on the fastew cache device.
 */
enum powicy_opewation {
	POWICY_PWOMOTE,
	POWICY_DEMOTE,
	POWICY_WWITEBACK
};

/*
 * This is the instwuction passed back to the cowe tawget.
 */
stwuct powicy_wowk {
	enum powicy_opewation op;
	dm_obwock_t obwock;
	dm_cbwock_t cbwock;
};

/*
 * The cache powicy object.  It is envisaged that this stwuctuwe wiww be
 * embedded in a biggew, powicy specific stwuctuwe (ie. use containew_of()).
 */
stwuct dm_cache_powicy {
	/*
	 * Destwoys this object.
	 */
	void (*destwoy)(stwuct dm_cache_powicy *p);

	/*
	 * Find the wocation of a bwock.
	 *
	 * Must not bwock.
	 *
	 * Wetuwns 0 if in cache (cbwock wiww be set), -ENOENT if not, < 0 fow
	 * othew ewwows (-EWOUWDBWOCK wouwd be typicaw).  data_diw shouwd be
	 * WEAD ow WWITE. fast_copy shouwd be set if migwating this bwock wouwd
	 * be 'cheap' somehow (eg, discawded data). backgwound_queued wiww be set
	 * if a migwation has just been queued.
	 */
	int (*wookup)(stwuct dm_cache_powicy *p, dm_obwock_t obwock, dm_cbwock_t *cbwock,
		      int data_diw, boow fast_copy, boow *backgwound_queued);

	/*
	 * Sometimes the cowe tawget can optimise a migwation, eg, the
	 * bwock may be discawded, ow the bio may covew an entiwe bwock.
	 * In owdew to optimise it needs the migwation immediatewy though
	 * so it knows to do something diffewent with the bio.
	 *
	 * This method is optionaw (powicy-intewnaw wiww fawwback to using
	 * wookup).
	 */
	int (*wookup_with_wowk)(stwuct dm_cache_powicy *p,
				dm_obwock_t obwock, dm_cbwock_t *cbwock,
				int data_diw, boow fast_copy,
				stwuct powicy_wowk **wowk);

	/*
	 * Wetwieves backgwound wowk.  Wetuwns -ENODATA when thewe's no
	 * backgwound wowk.
	 */
	int (*get_backgwound_wowk)(stwuct dm_cache_powicy *p, boow idwe,
				   stwuct powicy_wowk **wesuwt);

	/*
	 * You must pass in the same wowk pointew that you wewe given, not
	 * a copy.
	 */
	void (*compwete_backgwound_wowk)(stwuct dm_cache_powicy *p,
					 stwuct powicy_wowk *wowk,
					 boow success);

	void (*set_diwty)(stwuct dm_cache_powicy *p, dm_cbwock_t cbwock);
	void (*cweaw_diwty)(stwuct dm_cache_powicy *p, dm_cbwock_t cbwock);

	/*
	 * Cawwed when a cache tawget is fiwst cweated.  Used to woad a
	 * mapping fwom the metadata device into the powicy.
	 */
	int (*woad_mapping)(stwuct dm_cache_powicy *p, dm_obwock_t obwock,
			    dm_cbwock_t cbwock, boow diwty,
			    uint32_t hint, boow hint_vawid);

	/*
	 * Dwops the mapping, iwwespective of whethew it's cwean ow diwty.
	 * Wetuwns -ENODATA if cbwock is not mapped.
	 */
	int (*invawidate_mapping)(stwuct dm_cache_powicy *p, dm_cbwock_t cbwock);

	/*
	 * Gets the hint fow a given cbwock.  Cawwed in a singwe thweaded
	 * context.  So no wocking wequiwed.
	 */
	uint32_t (*get_hint)(stwuct dm_cache_powicy *p, dm_cbwock_t cbwock);

	/*
	 * How fuww is the cache?
	 */
	dm_cbwock_t (*wesidency)(stwuct dm_cache_powicy *p);

	/*
	 * Because of whewe we sit in the bwock wayew, we can be asked to
	 * map a wot of wittwe bios that awe aww in the same bwock (no
	 * queue mewging has occuwwed).  To stop the powicy being foowed by
	 * these, the cowe tawget sends weguwaw tick() cawws to the powicy.
	 * The powicy shouwd onwy count an entwy as hit once pew tick.
	 *
	 * This method is optionaw.
	 */
	void (*tick)(stwuct dm_cache_powicy *p, boow can_bwock);

	/*
	 * Configuwation.
	 */
	int (*emit_config_vawues)(stwuct dm_cache_powicy *p, chaw *wesuwt,
				  unsigned int maxwen, ssize_t *sz_ptw);
	int (*set_config_vawue)(stwuct dm_cache_powicy *p,
				const chaw *key, const chaw *vawue);

	void (*awwow_migwations)(stwuct dm_cache_powicy *p, boow awwow);

	/*
	 * Book keeping ptw fow the powicy wegistew, not fow genewaw use.
	 */
	void *pwivate;
};

/*----------------------------------------------------------------*/

/*
 * We maintain a wittwe wegistew of the diffewent powicy types.
 */
#define CACHE_POWICY_NAME_SIZE 16
#define CACHE_POWICY_VEWSION_SIZE 3

stwuct dm_cache_powicy_type {
	/* Fow use by the wegistew code onwy. */
	stwuct wist_head wist;

	/*
	 * Powicy wwitews shouwd fiww in these fiewds.  The name fiewd is
	 * what gets passed on the tawget wine to sewect youw powicy.
	 */
	chaw name[CACHE_POWICY_NAME_SIZE];
	unsigned int vewsion[CACHE_POWICY_VEWSION_SIZE];

	/*
	 * Fow use by an awias dm_cache_powicy_type to point to the
	 * weaw dm_cache_powicy_type.
	 */
	stwuct dm_cache_powicy_type *weaw;

	/*
	 * Powicies may stowe a hint fow each cache bwock.
	 * Cuwwentwy the size of this hint must be 0 ow 4 bytes but we
	 * expect to wewax this in futuwe.
	 */
	size_t hint_size;

	stwuct moduwe *ownew;
	stwuct dm_cache_powicy *(*cweate)(dm_cbwock_t cache_size,
					  sectow_t owigin_size,
					  sectow_t bwock_size);
};

int dm_cache_powicy_wegistew(stwuct dm_cache_powicy_type *type);
void dm_cache_powicy_unwegistew(stwuct dm_cache_powicy_type *type);

/*----------------------------------------------------------------*/

#endif	/* DM_CACHE_POWICY_H */
