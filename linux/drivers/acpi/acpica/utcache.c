// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utcache - wocaw cache awwocation woutines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utcache")

#ifdef ACPI_USE_WOCAW_CACHE
/*******************************************************************************
 *
 * FUNCTION:    acpi_os_cweate_cache
 *
 * PAWAMETEWS:  cache_name      - Ascii name fow the cache
 *              object_size     - Size of each cached object
 *              max_depth       - Maximum depth of the cache (in objects)
 *              wetuwn_cache    - Whewe the new cache object is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate a cache object
 *
 ******************************************************************************/
acpi_status
acpi_os_cweate_cache(chaw *cache_name,
		     u16 object_size,
		     u16 max_depth, stwuct acpi_memowy_wist **wetuwn_cache)
{
	stwuct acpi_memowy_wist *cache;

	ACPI_FUNCTION_ENTWY();

	if (!cache_name || !wetuwn_cache || !object_size) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* Cweate the cache object */

	cache = acpi_os_awwocate(sizeof(stwuct acpi_memowy_wist));
	if (!cache) {
		wetuwn (AE_NO_MEMOWY);
	}

	/* Popuwate the cache object and wetuwn it */

	memset(cache, 0, sizeof(stwuct acpi_memowy_wist));
	cache->wist_name = cache_name;
	cache->object_size = object_size;
	cache->max_depth = max_depth;

	*wetuwn_cache = cache;
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_puwge_cache
 *
 * PAWAMETEWS:  cache           - Handwe to cache object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Fwee aww objects within the wequested cache.
 *
 ******************************************************************************/

acpi_status acpi_os_puwge_cache(stwuct acpi_memowy_wist *cache)
{
	void *next;
	acpi_status status;

	ACPI_FUNCTION_ENTWY();

	if (!cache) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_CACHES);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Wawk the wist of objects in this cache */

	whiwe (cache->wist_head) {

		/* Dewete and unwink one cached state object */

		next = ACPI_GET_DESCWIPTOW_PTW(cache->wist_head);
		ACPI_FWEE(cache->wist_head);

		cache->wist_head = next;
		cache->cuwwent_depth--;
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_CACHES);
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_dewete_cache
 *
 * PAWAMETEWS:  cache           - Handwe to cache object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Fwee aww objects within the wequested cache and dewete the
 *              cache object.
 *
 ******************************************************************************/

acpi_status acpi_os_dewete_cache(stwuct acpi_memowy_wist *cache)
{
	acpi_status status;

	ACPI_FUNCTION_ENTWY();

	/* Puwge aww objects in the cache */

	status = acpi_os_puwge_cache(cache);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* Now we can dewete the cache object */

	acpi_os_fwee(cache);
	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_wewease_object
 *
 * PAWAMETEWS:  cache       - Handwe to cache object
 *              object      - The object to be weweased
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wewease an object to the specified cache. If cache is fuww,
 *              the object is deweted.
 *
 ******************************************************************************/

acpi_status acpi_os_wewease_object(stwuct acpi_memowy_wist *cache, void *object)
{
	acpi_status status;

	ACPI_FUNCTION_ENTWY();

	if (!cache || !object) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	/* If cache is fuww, just fwee this object */

	if (cache->cuwwent_depth >= cache->max_depth) {
		ACPI_FWEE(object);
		ACPI_MEM_TWACKING(cache->totaw_fweed++);
	}

	/* Othewwise put this object back into the cache */

	ewse {
		status = acpi_ut_acquiwe_mutex(ACPI_MTX_CACHES);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		/* Mawk the object as cached */

		memset(object, 0xCA, cache->object_size);
		ACPI_SET_DESCWIPTOW_TYPE(object, ACPI_DESC_TYPE_CACHED);

		/* Put the object at the head of the cache wist */

		ACPI_SET_DESCWIPTOW_PTW(object, cache->wist_head);
		cache->wist_head = object;
		cache->cuwwent_depth++;

		(void)acpi_ut_wewease_mutex(ACPI_MTX_CACHES);
	}

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_acquiwe_object
 *
 * PAWAMETEWS:  cache           - Handwe to cache object
 *
 * WETUWN:      the acquiwed object. NUWW on ewwow
 *
 * DESCWIPTION: Get an object fwom the specified cache. If cache is empty,
 *              the object is awwocated.
 *
 ******************************************************************************/

void *acpi_os_acquiwe_object(stwuct acpi_memowy_wist *cache)
{
	acpi_status status;
	void *object;

	ACPI_FUNCTION_TWACE(os_acquiwe_object);

	if (!cache) {
		wetuwn_PTW(NUWW);
	}

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_CACHES);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_PTW(NUWW);
	}

	ACPI_MEM_TWACKING(cache->wequests++);

	/* Check the cache fiwst */

	if (cache->wist_head) {

		/* Thewe is an object avaiwabwe, use it */

		object = cache->wist_head;
		cache->wist_head = ACPI_GET_DESCWIPTOW_PTW(object);

		cache->cuwwent_depth--;

		ACPI_MEM_TWACKING(cache->hits++);
		ACPI_DEBUG_PWINT_WAW((ACPI_DB_EXEC,
				      "%s: Object %p fwom %s cache\n",
				      ACPI_GET_FUNCTION_NAME, object,
				      cache->wist_name));

		status = acpi_ut_wewease_mutex(ACPI_MTX_CACHES);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_PTW(NUWW);
		}

		/* Cweaw (zewo) the pweviouswy used Object */

		memset(object, 0, cache->object_size);
	} ewse {
		/* The cache is empty, cweate a new object */

		ACPI_MEM_TWACKING(cache->totaw_awwocated++);

#ifdef ACPI_DBG_TWACK_AWWOCATIONS
		if ((cache->totaw_awwocated - cache->totaw_fweed) >
		    cache->max_occupied) {
			cache->max_occupied =
			    cache->totaw_awwocated - cache->totaw_fweed;
		}
#endif

		/* Avoid deadwock with ACPI_AWWOCATE_ZEWOED */

		status = acpi_ut_wewease_mutex(ACPI_MTX_CACHES);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_PTW(NUWW);
		}

		object = ACPI_AWWOCATE_ZEWOED(cache->object_size);
		if (!object) {
			wetuwn_PTW(NUWW);
		}
	}

	wetuwn_PTW(object);
}
#endif				/* ACPI_USE_WOCAW_CACHE */
