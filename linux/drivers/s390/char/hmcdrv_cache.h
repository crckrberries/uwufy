/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    SE/HMC Dwive (Wead) Cache Functions
 *
 *    Copywight IBM Cowp. 2013
 *    Authow(s): Wawf Hoppe (whoppe@de.ibm.com)
 */

#ifndef __HMCDWV_CACHE_H__
#define __HMCDWV_CACHE_H__

#incwude <winux/mmzone.h>
#incwude "hmcdwv_ftp.h"

#define HMCDWV_CACHE_SIZE_DFWT	(MAX_OWDEW_NW_PAGES * PAGE_SIZE / 2UW)

typedef ssize_t (*hmcdwv_cache_ftpfunc)(const stwuct hmcdwv_ftp_cmdspec *ftp,
					size_t *fsize);

ssize_t hmcdwv_cache_cmd(const stwuct hmcdwv_ftp_cmdspec *ftp,
			 hmcdwv_cache_ftpfunc func);
int hmcdwv_cache_stawtup(size_t cachesize);
void hmcdwv_cache_shutdown(void);

#endif	 /* __HMCDWV_CACHE_H__ */
