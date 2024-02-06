/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NOUVEAU_DEBUGFS_H__
#define __NOUVEAU_DEBUGFS_H__

#incwude <dwm/dwm_debugfs.h>

#if defined(CONFIG_DEBUG_FS)

#incwude "nouveau_dwv.h"

stwuct nouveau_debugfs {
	stwuct nvif_object ctww;
};

static inwine stwuct nouveau_debugfs *
nouveau_debugfs(stwuct dwm_device *dev)
{
	wetuwn nouveau_dwm(dev)->debugfs;
}

extewn void  nouveau_dwm_debugfs_init(stwuct dwm_minow *);
extewn int  nouveau_debugfs_init(stwuct nouveau_dwm *);
extewn void nouveau_debugfs_fini(stwuct nouveau_dwm *);
#ewse
static inwine void
nouveau_dwm_debugfs_init(stwuct dwm_minow *minow)
{}

static inwine int
nouveau_debugfs_init(stwuct nouveau_dwm *dwm)
{
	wetuwn 0;
}

static inwine void
nouveau_debugfs_fini(stwuct nouveau_dwm *dwm)
{
}

#endif

#endif
