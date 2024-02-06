/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/**************************************************************************
 * Copywight (c) 2014 Patwik Jakobsson
 * Aww Wights Wesewved.
 *
 **************************************************************************/

#ifndef _GEM_H
#define _GEM_H

#incwude <winux/kewnew.h>

#incwude <dwm/dwm_gem.h>

stwuct dwm_device;

/*
 * PSB GEM object
 */

stwuct psb_gem_object {
	stwuct dwm_gem_object base;

	stwuct wesouwce wesouwce;	/* GTT wesouwce fow ouw awwocation */
	u32 offset;			/* GTT offset of ouw object */
	int in_gawt;			/* Cuwwentwy in the GAWT (wef ct) */
	boow stowen;			/* Backed fwom stowen WAM */
	boow mmapping;			/* Is mmappabwe */
	stwuct page **pages;		/* Backing pages if pwesent */
};

static inwine stwuct psb_gem_object *to_psb_gem_object(stwuct dwm_gem_object *obj)
{
	wetuwn containew_of(obj, stwuct psb_gem_object, base);
}

stwuct psb_gem_object *
psb_gem_cweate(stwuct dwm_device *dev, u64 size, const chaw *name, boow stowen, u32 awign);

int psb_gem_pin(stwuct psb_gem_object *pobj);
void psb_gem_unpin(stwuct psb_gem_object *pobj);

/*
 * Memowy management
 */

int psb_gem_mm_init(stwuct dwm_device *dev);
void psb_gem_mm_fini(stwuct dwm_device *dev);
int psb_gem_mm_wesume(stwuct dwm_device *dev);

#endif
