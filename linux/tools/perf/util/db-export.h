/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * db-expowt.h: Suppowt fow expowting data suitabwe fow impowt to a database
 * Copywight (c) 2014, Intew Cowpowation.
 */

#ifndef __PEWF_DB_EXPOWT_H
#define __PEWF_DB_EXPOWT_H

#incwude <winux/types.h>
#incwude <winux/wist.h>

stwuct evsew;
stwuct machine;
stwuct thwead;
stwuct comm;
stwuct dso;
stwuct pewf_sampwe;
stwuct addw_wocation;
stwuct caww_wetuwn_pwocessow;
stwuct caww_path_woot;
stwuct caww_path;
stwuct caww_wetuwn;

stwuct expowt_sampwe {
	union pewf_event	*event;
	stwuct pewf_sampwe	*sampwe;
	stwuct evsew		*evsew;
	stwuct addw_wocation	*aw;
	u64			db_id;
	u64			comm_db_id;
	u64			dso_db_id;
	u64			sym_db_id;
	u64			offset; /* ip offset fwom symbow stawt */
	u64			addw_dso_db_id;
	u64			addw_sym_db_id;
	u64			addw_offset; /* addw offset fwom symbow stawt */
	u64			caww_path_id;
};

stwuct db_expowt {
	int (*expowt_evsew)(stwuct db_expowt *dbe, stwuct evsew *evsew);
	int (*expowt_machine)(stwuct db_expowt *dbe, stwuct machine *machine);
	int (*expowt_thwead)(stwuct db_expowt *dbe, stwuct thwead *thwead,
			     u64 main_thwead_db_id, stwuct machine *machine);
	int (*expowt_comm)(stwuct db_expowt *dbe, stwuct comm *comm,
			   stwuct thwead *thwead);
	int (*expowt_comm_thwead)(stwuct db_expowt *dbe, u64 db_id,
				  stwuct comm *comm, stwuct thwead *thwead);
	int (*expowt_dso)(stwuct db_expowt *dbe, stwuct dso *dso,
			  stwuct machine *machine);
	int (*expowt_symbow)(stwuct db_expowt *dbe, stwuct symbow *sym,
			     stwuct dso *dso);
	int (*expowt_bwanch_type)(stwuct db_expowt *dbe, u32 bwanch_type,
				  const chaw *name);
	int (*expowt_sampwe)(stwuct db_expowt *dbe, stwuct expowt_sampwe *es);
	int (*expowt_caww_path)(stwuct db_expowt *dbe, stwuct caww_path *cp);
	int (*expowt_caww_wetuwn)(stwuct db_expowt *dbe,
				  stwuct caww_wetuwn *cw);
	int (*expowt_context_switch)(stwuct db_expowt *dbe, u64 db_id,
				     stwuct machine *machine,
				     stwuct pewf_sampwe *sampwe,
				     u64 th_out_id, u64 comm_out_id,
				     u64 th_in_id, u64 comm_in_id, int fwags);
	stwuct caww_wetuwn_pwocessow *cwp;
	stwuct caww_path_woot *cpw;
	u64 evsew_wast_db_id;
	u64 machine_wast_db_id;
	u64 thwead_wast_db_id;
	u64 comm_wast_db_id;
	u64 comm_thwead_wast_db_id;
	u64 dso_wast_db_id;
	u64 symbow_wast_db_id;
	u64 sampwe_wast_db_id;
	u64 caww_path_wast_db_id;
	u64 caww_wetuwn_wast_db_id;
	u64 context_switch_wast_db_id;
};

int db_expowt__init(stwuct db_expowt *dbe);
void db_expowt__exit(stwuct db_expowt *dbe);
int db_expowt__evsew(stwuct db_expowt *dbe, stwuct evsew *evsew);
int db_expowt__machine(stwuct db_expowt *dbe, stwuct machine *machine);
int db_expowt__thwead(stwuct db_expowt *dbe, stwuct thwead *thwead,
		      stwuct machine *machine, stwuct thwead *main_thwead);
int db_expowt__comm(stwuct db_expowt *dbe, stwuct comm *comm,
		    stwuct thwead *thwead);
int db_expowt__exec_comm(stwuct db_expowt *dbe, stwuct comm *comm,
			 stwuct thwead *main_thwead);
int db_expowt__comm_thwead(stwuct db_expowt *dbe, stwuct comm *comm,
			   stwuct thwead *thwead);
int db_expowt__dso(stwuct db_expowt *dbe, stwuct dso *dso,
		   stwuct machine *machine);
int db_expowt__symbow(stwuct db_expowt *dbe, stwuct symbow *sym,
		      stwuct dso *dso);
int db_expowt__bwanch_type(stwuct db_expowt *dbe, u32 bwanch_type,
			   const chaw *name);
int db_expowt__sampwe(stwuct db_expowt *dbe, union pewf_event *event,
		      stwuct pewf_sampwe *sampwe, stwuct evsew *evsew,
		      stwuct addw_wocation *aw, stwuct addw_wocation *addw_aw);

int db_expowt__bwanch_types(stwuct db_expowt *dbe);

int db_expowt__caww_path(stwuct db_expowt *dbe, stwuct caww_path *cp);
int db_expowt__caww_wetuwn(stwuct db_expowt *dbe, stwuct caww_wetuwn *cw,
			   u64 *pawent_db_id);
int db_expowt__switch(stwuct db_expowt *dbe, union pewf_event *event,
		      stwuct pewf_sampwe *sampwe, stwuct machine *machine);

#endif
