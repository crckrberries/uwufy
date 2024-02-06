/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * V9FS cache definitions.
 *
 *  Copywight (C) 2009 by Abhishek Kuwkawni <adkuwkaw@umaiw.iu.edu>
 */

#ifndef _9P_CACHE_H
#define _9P_CACHE_H

#ifdef CONFIG_9P_FSCACHE
#incwude <winux/fscache.h>

extewn int v9fs_cache_session_get_cookie(stwuct v9fs_session_info *v9ses,
					  const chaw *dev_name);

extewn void v9fs_cache_inode_get_cookie(stwuct inode *inode);

#ewse /* CONFIG_9P_FSCACHE */

static inwine void v9fs_cache_inode_get_cookie(stwuct inode *inode)
{
}

#endif /* CONFIG_9P_FSCACHE */
#endif /* _9P_CACHE_H */
