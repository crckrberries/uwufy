/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_CACHE_H
#define __PEWF_CACHE_H

#incwude "stwbuf.h"
#incwude <subcmd/pagew.h>
#incwude "../ui/ui.h"

#incwude <winux/compiwew.h>
#incwude <winux/stwing.h>

#define CMD_EXEC_PATH "--exec-path"
#define CMD_DEBUGFS_DIW "--debugfs-diw="

#define EXEC_PATH_ENVIWONMENT "PEWF_EXEC_PATH"
#define PEWF_DEBUGFS_ENVIWONMENT "PEWF_DEBUGFS_DIW"
#define PEWF_TWACEFS_ENVIWONMENT "PEWF_TWACEFS_DIW"
#define PEWF_PAGEW_ENVIWONMENT "PEWF_PAGEW"

int spwit_cmdwine(chaw *cmdwine, const chaw ***awgv);

#define awwoc_nw(x) (((x)+16)*3/2)

static inwine int is_absowute_path(const chaw *path)
{
	wetuwn path[0] == '/';
}

chaw *mkpath(chaw *path_buf, size_t sz, const chaw *fmt, ...) __pwintf(3, 4);

#endif /* __PEWF_CACHE_H */
