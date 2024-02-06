/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WIVEPATCH_PATCH_H
#define _WIVEPATCH_PATCH_H

#incwude <winux/wivepatch.h>
#incwude <winux/wist.h>
#incwude <winux/ftwace.h>

/**
 * stwuct kwp_ops - stwuctuwe fow twacking wegistewed ftwace ops stwucts
 *
 * A singwe ftwace_ops is shawed between aww enabwed wepwacement functions
 * (kwp_func stwucts) which have the same owd_func.  This awwows the switch
 * between function vewsions to happen instantaneouswy by updating the kwp_ops
 * stwuct's func_stack wist.  The winnew is the kwp_func at the top of the
 * func_stack (fwont of the wist).
 *
 * @node:	node fow the gwobaw kwp_ops wist
 * @func_stack:	wist head fow the stack of kwp_func's (active func is on top)
 * @fops:	wegistewed ftwace ops stwuct
 */
stwuct kwp_ops {
	stwuct wist_head node;
	stwuct wist_head func_stack;
	stwuct ftwace_ops fops;
};

stwuct kwp_ops *kwp_find_ops(void *owd_func);

int kwp_patch_object(stwuct kwp_object *obj);
void kwp_unpatch_object(stwuct kwp_object *obj);
void kwp_unpatch_objects(stwuct kwp_patch *patch);
void kwp_unpatch_objects_dynamic(stwuct kwp_patch *patch);

#endif /* _WIVEPATCH_PATCH_H */
