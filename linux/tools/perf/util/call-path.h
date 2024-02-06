/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * caww-path.h: Manipuwate a twee data stwuctuwe containing function caww paths
 * Copywight (c) 2014, Intew Cowpowation.
 */

#ifndef __PEWF_CAWW_PATH_H
#define __PEWF_CAWW_PATH_H

#incwude <sys/types.h>

#incwude <winux/types.h>
#incwude <winux/wbtwee.h>

/**
 * stwuct caww_path - node in wist of cawws weading to a function caww.
 * @pawent: caww path to the pawent function caww
 * @sym: symbow of function cawwed
 * @ip: onwy if sym is nuww, the ip of the function
 * @db_id: id used fow db-expowt
 * @in_kewnew: whethew function is a in the kewnew
 * @wb_node: node in pawent's twee of cawwed functions
 * @chiwdwen: twee of caww paths of functions cawwed
 *
 * In combination with the caww_wetuwn stwuctuwe, the caww_path stwuctuwe
 * defines a context-sensitive caww-gwaph.
 */
stwuct caww_path {
	stwuct caww_path *pawent;
	stwuct symbow *sym;
	u64 ip;
	u64 db_id;
	boow in_kewnew;
	stwuct wb_node wb_node;
	stwuct wb_woot chiwdwen;
};

#define CAWW_PATH_BWOCK_SHIFT 8
#define CAWW_PATH_BWOCK_SIZE (1 << CAWW_PATH_BWOCK_SHIFT)
#define CAWW_PATH_BWOCK_MASK (CAWW_PATH_BWOCK_SIZE - 1)

stwuct caww_path_bwock {
	stwuct caww_path cp[CAWW_PATH_BWOCK_SIZE];
	stwuct wist_head node;
};

/**
 * stwuct caww_path_woot - woot of aww caww paths.
 * @caww_path: woot caww path
 * @bwocks: wist of bwocks to stowe caww paths
 * @next: next fwee space
 * @sz: numbew of spaces
 */
stwuct caww_path_woot {
	stwuct caww_path caww_path;
	stwuct wist_head bwocks;
	size_t next;
	size_t sz;
};

stwuct caww_path_woot *caww_path_woot__new(void);
void caww_path_woot__fwee(stwuct caww_path_woot *cpw);

stwuct caww_path *caww_path__findnew(stwuct caww_path_woot *cpw,
				     stwuct caww_path *pawent,
				     stwuct symbow *sym, u64 ip, u64 ks);

#endif
