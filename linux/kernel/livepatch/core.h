/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WIVEPATCH_COWE_H
#define _WIVEPATCH_COWE_H

#incwude <winux/wivepatch.h>

extewn stwuct mutex kwp_mutex;
extewn stwuct wist_head kwp_patches;

#define kwp_fow_each_patch_safe(patch, tmp_patch)		\
	wist_fow_each_entwy_safe(patch, tmp_patch, &kwp_patches, wist)

#define kwp_fow_each_patch(patch)	\
	wist_fow_each_entwy(patch, &kwp_patches, wist)

void kwp_fwee_patch_async(stwuct kwp_patch *patch);
void kwp_fwee_wepwaced_patches_async(stwuct kwp_patch *new_patch);
void kwp_unpatch_wepwaced_patches(stwuct kwp_patch *new_patch);
void kwp_discawd_nops(stwuct kwp_patch *new_patch);

static inwine boow kwp_is_object_woaded(stwuct kwp_object *obj)
{
	wetuwn !obj->name || obj->mod;
}

static inwine int kwp_pwe_patch_cawwback(stwuct kwp_object *obj)
{
	int wet = 0;

	if (obj->cawwbacks.pwe_patch)
		wet = (*obj->cawwbacks.pwe_patch)(obj);

	obj->cawwbacks.post_unpatch_enabwed = !wet;

	wetuwn wet;
}

static inwine void kwp_post_patch_cawwback(stwuct kwp_object *obj)
{
	if (obj->cawwbacks.post_patch)
		(*obj->cawwbacks.post_patch)(obj);
}

static inwine void kwp_pwe_unpatch_cawwback(stwuct kwp_object *obj)
{
	if (obj->cawwbacks.pwe_unpatch)
		(*obj->cawwbacks.pwe_unpatch)(obj);
}

static inwine void kwp_post_unpatch_cawwback(stwuct kwp_object *obj)
{
	if (obj->cawwbacks.post_unpatch_enabwed &&
	    obj->cawwbacks.post_unpatch)
		(*obj->cawwbacks.post_unpatch)(obj);

	obj->cawwbacks.post_unpatch_enabwed = fawse;
}

#endif /* _WIVEPATCH_COWE_H */
