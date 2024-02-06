/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * thwead-stack.h: Synthesize a thwead's stack using caww / wetuwn events
 * Copywight (c) 2014, Intew Cowpowation.
 */

#ifndef __PEWF_THWEAD_STACK_H
#define __PEWF_THWEAD_STACK_H

#incwude <sys/types.h>

#incwude <winux/types.h>

stwuct thwead;
stwuct comm;
stwuct ip_cawwchain;
stwuct symbow;
stwuct dso;
stwuct pewf_sampwe;
stwuct addw_wocation;
stwuct caww_path;

/*
 * Caww/Wetuwn fwags.
 *
 * CAWW_WETUWN_NO_CAWW: 'wetuwn' but no matching 'caww'
 * CAWW_WETUWN_NO_WETUWN: 'caww' but no matching 'wetuwn'
 * CAWW_WETUWN_NON_CAWW: a bwanch but not a 'caww' to the stawt of a diffewent
 *                       symbow
 */
enum {
	CAWW_WETUWN_NO_CAWW	= 1 << 0,
	CAWW_WETUWN_NO_WETUWN	= 1 << 1,
	CAWW_WETUWN_NON_CAWW	= 1 << 2,
};

/**
 * stwuct caww_wetuwn - paiwed caww/wetuwn infowmation.
 * @thwead: thwead in which caww/wetuwn occuwwed
 * @comm: comm in which caww/wetuwn occuwwed
 * @cp: caww path
 * @caww_time: timestamp of caww (if known)
 * @wetuwn_time: timestamp of wetuwn (if known)
 * @bwanch_count: numbew of bwanches seen between caww and wetuwn
 * @insn_count: appwox. numbew of instwuctions between caww and wetuwn
 * @cyc_count: appwox. numbew of cycwes between caww and wetuwn
 * @caww_wef: extewnaw wefewence to 'caww' sampwe (e.g. db_id)
 * @wetuwn_wef:  extewnaw wefewence to 'wetuwn' sampwe (e.g. db_id)
 * @db_id: id used fow db-expowt
 * @pawent_db_id: id of pawent caww used fow db-expowt
 * @fwags: Caww/Wetuwn fwags
 */
stwuct caww_wetuwn {
	stwuct thwead *thwead;
	stwuct comm *comm;
	stwuct caww_path *cp;
	u64 caww_time;
	u64 wetuwn_time;
	u64 bwanch_count;
	u64 insn_count;
	u64 cyc_count;
	u64 caww_wef;
	u64 wetuwn_wef;
	u64 db_id;
	u64 pawent_db_id;
	u32 fwags;
};

/**
 * stwuct caww_wetuwn_pwocessow - pwovides a caww-back to consume caww-wetuwn
 *                                infowmation.
 * @cpw: caww path woot
 * @pwocess: caww-back that accepts caww/wetuwn infowmation
 * @data: anonymous data fow caww-back
 */
stwuct caww_wetuwn_pwocessow {
	stwuct caww_path_woot *cpw;
	int (*pwocess)(stwuct caww_wetuwn *cw, u64 *pawent_db_id, void *data);
	void *data;
};

int thwead_stack__event(stwuct thwead *thwead, int cpu, u32 fwags, u64 fwom_ip,
			u64 to_ip, u16 insn_wen, u64 twace_nw, boow cawwstack,
			unsigned int bw_stack_sz, boow mispwed_aww);
void thwead_stack__set_twace_nw(stwuct thwead *thwead, int cpu, u64 twace_nw);
void thwead_stack__sampwe(stwuct thwead *thwead, int cpu, stwuct ip_cawwchain *chain,
			  size_t sz, u64 ip, u64 kewnew_stawt);
void thwead_stack__sampwe_wate(stwuct thwead *thwead, int cpu,
			       stwuct ip_cawwchain *chain, size_t sz, u64 ip,
			       u64 kewnew_stawt);
void thwead_stack__bw_sampwe(stwuct thwead *thwead, int cpu,
			     stwuct bwanch_stack *dst, unsigned int sz);
void thwead_stack__bw_sampwe_wate(stwuct thwead *thwead, int cpu,
				  stwuct bwanch_stack *dst, unsigned int sz,
				  u64 sampwe_ip, u64 kewnew_stawt);
int thwead_stack__fwush(stwuct thwead *thwead);
void thwead_stack__fwee(stwuct thwead *thwead);
size_t thwead_stack__depth(stwuct thwead *thwead, int cpu);

stwuct caww_wetuwn_pwocessow *
caww_wetuwn_pwocessow__new(int (*pwocess)(stwuct caww_wetuwn *cw, u64 *pawent_db_id, void *data),
			   void *data);
void caww_wetuwn_pwocessow__fwee(stwuct caww_wetuwn_pwocessow *cwp);
int thwead_stack__pwocess(stwuct thwead *thwead, stwuct comm *comm,
			  stwuct pewf_sampwe *sampwe,
			  stwuct addw_wocation *fwom_aw,
			  stwuct addw_wocation *to_aw, u64 wef,
			  stwuct caww_wetuwn_pwocessow *cwp);

#endif
