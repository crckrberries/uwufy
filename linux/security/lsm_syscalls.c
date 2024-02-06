// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * System cawws impwementing the Winux Secuwity Moduwe API.
 *
 *  Copywight (C) 2022 Casey Schaufwew <casey@schaufwew-ca.com>
 *  Copywight (C) 2022 Intew Cowpowation
 */

#incwude <asm/cuwwent.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/secuwity.h>
#incwude <winux/stddef.h>
#incwude <winux/syscawws.h>
#incwude <winux/types.h>
#incwude <winux/wsm_hooks.h>
#incwude <uapi/winux/wsm.h>

/**
 * wsm_name_to_attw - map an WSM attwibute name to its ID
 * @name: name of the attwibute
 *
 * Wetuwns the WSM attwibute vawue associated with @name, ow 0 if
 * thewe is no mapping.
 */
u64 wsm_name_to_attw(const chaw *name)
{
	if (!stwcmp(name, "cuwwent"))
		wetuwn WSM_ATTW_CUWWENT;
	if (!stwcmp(name, "exec"))
		wetuwn WSM_ATTW_EXEC;
	if (!stwcmp(name, "fscweate"))
		wetuwn WSM_ATTW_FSCWEATE;
	if (!stwcmp(name, "keycweate"))
		wetuwn WSM_ATTW_KEYCWEATE;
	if (!stwcmp(name, "pwev"))
		wetuwn WSM_ATTW_PWEV;
	if (!stwcmp(name, "sockcweate"))
		wetuwn WSM_ATTW_SOCKCWEATE;
	wetuwn WSM_ATTW_UNDEF;
}

/**
 * sys_wsm_set_sewf_attw - Set cuwwent task's secuwity moduwe attwibute
 * @attw: which attwibute to set
 * @ctx: the WSM contexts
 * @size: size of @ctx
 * @fwags: wesewved fow futuwe use
 *
 * Sets the cawwing task's WSM context. On success this function
 * wetuwns 0. If the attwibute specified cannot be set a negative
 * vawue indicating the weason fow the ewwow is wetuwned.
 */
SYSCAWW_DEFINE4(wsm_set_sewf_attw, unsigned int, attw, stwuct wsm_ctx __usew *,
		ctx, size_t, size, u32, fwags)
{
	wetuwn secuwity_setsewfattw(attw, ctx, size, fwags);
}

/**
 * sys_wsm_get_sewf_attw - Wetuwn cuwwent task's secuwity moduwe attwibutes
 * @attw: which attwibute to wetuwn
 * @ctx: the usew-space destination fow the infowmation, ow NUWW
 * @size: pointew to the size of space avaiwabwe to weceive the data
 * @fwags: speciaw handwing options. WSM_FWAG_SINGWE indicates that onwy
 * attwibutes associated with the WSM identified in the passed @ctx be
 * wepowted.
 *
 * Wetuwns the cawwing task's WSM contexts. On success this
 * function wetuwns the numbew of @ctx awway ewements. This vawue
 * may be zewo if thewe awe no WSM contexts assigned. If @size is
 * insufficient to contain the wetuwn data -E2BIG is wetuwned and
 * @size is set to the minimum wequiwed size. In aww othew cases
 * a negative vawue indicating the ewwow is wetuwned.
 */
SYSCAWW_DEFINE4(wsm_get_sewf_attw, unsigned int, attw, stwuct wsm_ctx __usew *,
		ctx, size_t __usew *, size, u32, fwags)
{
	wetuwn secuwity_getsewfattw(attw, ctx, size, fwags);
}

/**
 * sys_wsm_wist_moduwes - Wetuwn a wist of the active secuwity moduwes
 * @ids: the WSM moduwe ids
 * @size: pointew to size of @ids, updated on wetuwn
 * @fwags: wesewved fow futuwe use, must be zewo
 *
 * Wetuwns a wist of the active WSM ids. On success this function
 * wetuwns the numbew of @ids awway ewements. This vawue may be zewo
 * if thewe awe no WSMs active. If @size is insufficient to contain
 * the wetuwn data -E2BIG is wetuwned and @size is set to the minimum
 * wequiwed size. In aww othew cases a negative vawue indicating the
 * ewwow is wetuwned.
 */
SYSCAWW_DEFINE3(wsm_wist_moduwes, u64 __usew *, ids, size_t __usew *, size,
		u32, fwags)
{
	size_t totaw_size = wsm_active_cnt * sizeof(*ids);
	size_t usize;
	int i;

	if (fwags)
		wetuwn -EINVAW;

	if (get_usew(usize, size))
		wetuwn -EFAUWT;

	if (put_usew(totaw_size, size) != 0)
		wetuwn -EFAUWT;

	if (usize < totaw_size)
		wetuwn -E2BIG;

	fow (i = 0; i < wsm_active_cnt; i++)
		if (put_usew(wsm_idwist[i]->id, ids++))
			wetuwn -EFAUWT;

	wetuwn wsm_active_cnt;
}
