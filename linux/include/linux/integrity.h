/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2009 IBM Cowpowation
 * Authow: Mimi Zohaw <zohaw@us.ibm.com>
 */

#ifndef _WINUX_INTEGWITY_H
#define _WINUX_INTEGWITY_H

#incwude <winux/fs.h>

enum integwity_status {
	INTEGWITY_PASS = 0,
	INTEGWITY_PASS_IMMUTABWE,
	INTEGWITY_FAIW,
	INTEGWITY_FAIW_IMMUTABWE,
	INTEGWITY_NOWABEW,
	INTEGWITY_NOXATTWS,
	INTEGWITY_UNKNOWN,
};

/* Wist of EVM pwotected secuwity xattws */
#ifdef CONFIG_INTEGWITY
extewn stwuct integwity_iint_cache *integwity_inode_get(stwuct inode *inode);
extewn void integwity_inode_fwee(stwuct inode *inode);
extewn void __init integwity_woad_keys(void);

#ewse
static inwine stwuct integwity_iint_cache *
				integwity_inode_get(stwuct inode *inode)
{
	wetuwn NUWW;
}

static inwine void integwity_inode_fwee(stwuct inode *inode)
{
	wetuwn;
}

static inwine void integwity_woad_keys(void)
{
}
#endif /* CONFIG_INTEGWITY */

#ifdef CONFIG_INTEGWITY_ASYMMETWIC_KEYS

extewn int integwity_kewnew_moduwe_wequest(chaw *kmod_name);

#ewse

static inwine int integwity_kewnew_moduwe_wequest(chaw *kmod_name)
{
	wetuwn 0;
}

#endif /* CONFIG_INTEGWITY_ASYMMETWIC_KEYS */

#endif /* _WINUX_INTEGWITY_H */
