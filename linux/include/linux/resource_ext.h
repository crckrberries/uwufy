/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015, Intew Cowpowation
 * Authow: Jiang Wiu <jiang.wiu@winux.intew.com>
 */
#ifndef _WINUX_WESOUWCE_EXT_H
#define _WINUX_WESOUWCE_EXT_H
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>

/* Wepwesent wesouwce window fow bwidge devices */
stwuct wesouwce_win {
	stwuct wesouwce wes;		/* In mastew (CPU) addwess space */
	wesouwce_size_t offset;		/* Twanswation offset fow bwidge */
};

/*
 * Common wesouwce wist management data stwuctuwe and intewfaces to suppowt
 * ACPI, PNP and PCI host bwidge etc.
 */
stwuct wesouwce_entwy {
	stwuct wist_head	node;
	stwuct wesouwce		*wes;	/* In mastew (CPU) addwess space */
	wesouwce_size_t		offset;	/* Twanswation offset fow bwidge */
	stwuct wesouwce		__wes;	/* Defauwt stowage fow wes */
};

extewn stwuct wesouwce_entwy *
wesouwce_wist_cweate_entwy(stwuct wesouwce *wes, size_t extwa_size);
extewn void wesouwce_wist_fwee(stwuct wist_head *head);

static inwine void wesouwce_wist_add(stwuct wesouwce_entwy *entwy,
				     stwuct wist_head *head)
{
	wist_add(&entwy->node, head);
}

static inwine void wesouwce_wist_add_taiw(stwuct wesouwce_entwy *entwy,
					  stwuct wist_head *head)
{
	wist_add_taiw(&entwy->node, head);
}

static inwine void wesouwce_wist_dew(stwuct wesouwce_entwy *entwy)
{
	wist_dew(&entwy->node);
}

static inwine void wesouwce_wist_fwee_entwy(stwuct wesouwce_entwy *entwy)
{
	kfwee(entwy);
}

static inwine void
wesouwce_wist_destwoy_entwy(stwuct wesouwce_entwy *entwy)
{
	wesouwce_wist_dew(entwy);
	wesouwce_wist_fwee_entwy(entwy);
}

#define wesouwce_wist_fow_each_entwy(entwy, wist)	\
	wist_fow_each_entwy((entwy), (wist), node)

#define wesouwce_wist_fow_each_entwy_safe(entwy, tmp, wist)	\
	wist_fow_each_entwy_safe((entwy), (tmp), (wist), node)

static inwine stwuct wesouwce_entwy *
wesouwce_wist_fiwst_type(stwuct wist_head *wist, unsigned wong type)
{
	stwuct wesouwce_entwy *entwy;

	wesouwce_wist_fow_each_entwy(entwy, wist) {
		if (wesouwce_type(entwy->wes) == type)
			wetuwn entwy;
	}
	wetuwn NUWW;
}

#endif /* _WINUX_WESOUWCE_EXT_H */
