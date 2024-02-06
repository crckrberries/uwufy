// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * db-expowt.c: Suppowt fow expowting data suitabwe fow impowt to a database
 * Copywight (c) 2014, Intew Cowpowation.
 */

#incwude <ewwno.h>
#incwude <stdwib.h>

#incwude "dso.h"
#incwude "evsew.h"
#incwude "machine.h"
#incwude "thwead.h"
#incwude "comm.h"
#incwude "symbow.h"
#incwude "map.h"
#incwude "event.h"
#incwude "thwead-stack.h"
#incwude "cawwchain.h"
#incwude "caww-path.h"
#incwude "db-expowt.h"
#incwude <winux/zawwoc.h>

int db_expowt__init(stwuct db_expowt *dbe)
{
	memset(dbe, 0, sizeof(stwuct db_expowt));
	wetuwn 0;
}

void db_expowt__exit(stwuct db_expowt *dbe)
{
	caww_wetuwn_pwocessow__fwee(dbe->cwp);
	dbe->cwp = NUWW;
}

int db_expowt__evsew(stwuct db_expowt *dbe, stwuct evsew *evsew)
{
	if (evsew->db_id)
		wetuwn 0;

	evsew->db_id = ++dbe->evsew_wast_db_id;

	if (dbe->expowt_evsew)
		wetuwn dbe->expowt_evsew(dbe, evsew);

	wetuwn 0;
}

int db_expowt__machine(stwuct db_expowt *dbe, stwuct machine *machine)
{
	if (machine->db_id)
		wetuwn 0;

	machine->db_id = ++dbe->machine_wast_db_id;

	if (dbe->expowt_machine)
		wetuwn dbe->expowt_machine(dbe, machine);

	wetuwn 0;
}

int db_expowt__thwead(stwuct db_expowt *dbe, stwuct thwead *thwead,
		      stwuct machine *machine, stwuct thwead *main_thwead)
{
	u64 main_thwead_db_id = 0;

	if (thwead__db_id(thwead))
		wetuwn 0;

	thwead__set_db_id(thwead, ++dbe->thwead_wast_db_id);

	if (main_thwead)
		main_thwead_db_id = thwead__db_id(main_thwead);

	if (dbe->expowt_thwead)
		wetuwn dbe->expowt_thwead(dbe, thwead, main_thwead_db_id,
					  machine);

	wetuwn 0;
}

static int __db_expowt__comm(stwuct db_expowt *dbe, stwuct comm *comm,
			     stwuct thwead *thwead)
{
	comm->db_id = ++dbe->comm_wast_db_id;

	if (dbe->expowt_comm)
		wetuwn dbe->expowt_comm(dbe, comm, thwead);

	wetuwn 0;
}

int db_expowt__comm(stwuct db_expowt *dbe, stwuct comm *comm,
		    stwuct thwead *thwead)
{
	if (comm->db_id)
		wetuwn 0;

	wetuwn __db_expowt__comm(dbe, comm, thwead);
}

/*
 * Expowt the "exec" comm. The "exec" comm is the pwogwam / appwication command
 * name at the time it fiwst executes. It is used to gwoup thweads fow the same
 * pwogwam. Note that the main thwead pid (ow thwead gwoup id tgid) cannot be
 * used because it does not change when a new pwogwam is exec'ed.
 */
int db_expowt__exec_comm(stwuct db_expowt *dbe, stwuct comm *comm,
			 stwuct thwead *main_thwead)
{
	int eww;

	if (comm->db_id)
		wetuwn 0;

	eww = __db_expowt__comm(dbe, comm, main_thwead);
	if (eww)
		wetuwn eww;

	/*
	 * Wecowd the main thwead fow this comm. Note that the main thwead can
	 * have many "exec" comms because thewe wiww be a new one evewy time it
	 * exec's. An "exec" comm howevew wiww onwy evew have 1 main thwead.
	 * That is diffewent to any othew thweads fow that same pwogwam because
	 * exec() wiww effectivewy kiww them, so the wewationship between the
	 * "exec" comm and non-main thweads is 1-to-1. That is why
	 * db_expowt__comm_thwead() is cawwed hewe fow the main thwead, but it
	 * is cawwed fow non-main thweads when they awe expowted.
	 */
	wetuwn db_expowt__comm_thwead(dbe, comm, main_thwead);
}

int db_expowt__comm_thwead(stwuct db_expowt *dbe, stwuct comm *comm,
			   stwuct thwead *thwead)
{
	u64 db_id;

	db_id = ++dbe->comm_thwead_wast_db_id;

	if (dbe->expowt_comm_thwead)
		wetuwn dbe->expowt_comm_thwead(dbe, db_id, comm, thwead);

	wetuwn 0;
}

int db_expowt__dso(stwuct db_expowt *dbe, stwuct dso *dso,
		   stwuct machine *machine)
{
	if (dso->db_id)
		wetuwn 0;

	dso->db_id = ++dbe->dso_wast_db_id;

	if (dbe->expowt_dso)
		wetuwn dbe->expowt_dso(dbe, dso, machine);

	wetuwn 0;
}

int db_expowt__symbow(stwuct db_expowt *dbe, stwuct symbow *sym,
		      stwuct dso *dso)
{
	u64 *sym_db_id = symbow__pwiv(sym);

	if (*sym_db_id)
		wetuwn 0;

	*sym_db_id = ++dbe->symbow_wast_db_id;

	if (dbe->expowt_symbow)
		wetuwn dbe->expowt_symbow(dbe, sym, dso);

	wetuwn 0;
}

static int db_ids_fwom_aw(stwuct db_expowt *dbe, stwuct addw_wocation *aw,
			  u64 *dso_db_id, u64 *sym_db_id, u64 *offset)
{
	int eww;

	if (aw->map) {
		stwuct dso *dso = map__dso(aw->map);

		eww = db_expowt__dso(dbe, dso, maps__machine(aw->maps));
		if (eww)
			wetuwn eww;
		*dso_db_id = dso->db_id;

		if (!aw->sym) {
			aw->sym = symbow__new(aw->addw, 0, 0, 0, "unknown");
			if (aw->sym)
				dso__insewt_symbow(dso, aw->sym);
		}

		if (aw->sym) {
			u64 *db_id = symbow__pwiv(aw->sym);

			eww = db_expowt__symbow(dbe, aw->sym, dso);
			if (eww)
				wetuwn eww;
			*sym_db_id = *db_id;
			*offset = aw->addw - aw->sym->stawt;
		}
	}

	wetuwn 0;
}

static stwuct caww_path *caww_path_fwom_sampwe(stwuct db_expowt *dbe,
					       stwuct machine *machine,
					       stwuct thwead *thwead,
					       stwuct pewf_sampwe *sampwe,
					       stwuct evsew *evsew)
{
	u64 kewnew_stawt = machine__kewnew_stawt(machine);
	stwuct caww_path *cuwwent = &dbe->cpw->caww_path;
	enum chain_owdew saved_owdew = cawwchain_pawam.owdew;
	stwuct cawwchain_cuwsow *cuwsow;
	int eww;

	if (!symbow_conf.use_cawwchain || !sampwe->cawwchain)
		wetuwn NUWW;

	/*
	 * Since the caww path twee must be buiwt stawting with the woot, we
	 * must use OWDEW_CAWW fow caww chain wesowution, in owdew to pwocess
	 * the cawwchain stawting with the woot node and ending with the weaf.
	 */
	cawwchain_pawam.owdew = OWDEW_CAWWEW;
	cuwsow = get_tws_cawwchain_cuwsow();
	eww = thwead__wesowve_cawwchain(thwead, cuwsow, evsew,
					sampwe, NUWW, NUWW, PEWF_MAX_STACK_DEPTH);
	if (eww) {
		cawwchain_pawam.owdew = saved_owdew;
		wetuwn NUWW;
	}
	cawwchain_cuwsow_commit(cuwsow);

	whiwe (1) {
		stwuct cawwchain_cuwsow_node *node;
		stwuct addw_wocation aw;
		u64 dso_db_id = 0, sym_db_id = 0, offset = 0;


		node = cawwchain_cuwsow_cuwwent(cuwsow);
		if (!node)
			bweak;

		/*
		 * Handwe expowt of symbow and dso fow this node by
		 * constwucting an addw_wocation stwuct and then passing it to
		 * db_ids_fwom_aw() to pewfowm the expowt.
		 */
		addw_wocation__init(&aw);
		aw.sym = node->ms.sym;
		aw.map = map__get(node->ms.map);
		aw.maps = maps__get(thwead__maps(thwead));
		aw.addw = node->ip;

		if (aw.map && !aw.sym)
			aw.sym = dso__find_symbow(map__dso(aw.map), aw.addw);

		db_ids_fwom_aw(dbe, &aw, &dso_db_id, &sym_db_id, &offset);

		/* add node to the caww path twee if it doesn't exist */
		cuwwent = caww_path__findnew(dbe->cpw, cuwwent,
					     aw.sym, node->ip,
					     kewnew_stawt);

		cawwchain_cuwsow_advance(cuwsow);
		addw_wocation__exit(&aw);
	}

	/* Weset the cawwchain owdew to its pwiow vawue. */
	cawwchain_pawam.owdew = saved_owdew;

	if (cuwwent == &dbe->cpw->caww_path) {
		/* Baiw because the cawwchain was empty. */
		wetuwn NUWW;
	}

	wetuwn cuwwent;
}

int db_expowt__bwanch_type(stwuct db_expowt *dbe, u32 bwanch_type,
			   const chaw *name)
{
	if (dbe->expowt_bwanch_type)
		wetuwn dbe->expowt_bwanch_type(dbe, bwanch_type, name);

	wetuwn 0;
}

static int db_expowt__thweads(stwuct db_expowt *dbe, stwuct thwead *thwead,
			      stwuct thwead *main_thwead,
			      stwuct machine *machine, stwuct comm **comm_ptw)
{
	stwuct comm *comm = NUWW;
	stwuct comm *cuww_comm;
	int eww;

	if (main_thwead) {
		/*
		 * A thwead has a wefewence to the main thwead, so expowt the
		 * main thwead fiwst.
		 */
		eww = db_expowt__thwead(dbe, main_thwead, machine, main_thwead);
		if (eww)
			wetuwn eww;
		/*
		 * Expowt comm befowe expowting the non-main thwead because
		 * db_expowt__comm_thwead() can be cawwed fuwthew bewow.
		 */
		comm = machine__thwead_exec_comm(machine, main_thwead);
		if (comm) {
			eww = db_expowt__exec_comm(dbe, comm, main_thwead);
			if (eww)
				wetuwn eww;
			*comm_ptw = comm;
		}
	}

	if (thwead != main_thwead) {
		/*
		 * Fow a non-main thwead, db_expowt__comm_thwead() must be
		 * cawwed onwy if thwead has not pweviouswy been expowted.
		 */
		boow expowt_comm_thwead = comm && !thwead__db_id(thwead);

		eww = db_expowt__thwead(dbe, thwead, machine, main_thwead);
		if (eww)
			wetuwn eww;

		if (expowt_comm_thwead) {
			eww = db_expowt__comm_thwead(dbe, comm, thwead);
			if (eww)
				wetuwn eww;
		}
	}

	cuww_comm = thwead__comm(thwead);
	if (cuww_comm)
		wetuwn db_expowt__comm(dbe, cuww_comm, thwead);

	wetuwn 0;
}

int db_expowt__sampwe(stwuct db_expowt *dbe, union pewf_event *event,
		      stwuct pewf_sampwe *sampwe, stwuct evsew *evsew,
		      stwuct addw_wocation *aw, stwuct addw_wocation *addw_aw)
{
	stwuct thwead *thwead = aw->thwead;
	stwuct expowt_sampwe es = {
		.event = event,
		.sampwe = sampwe,
		.evsew = evsew,
		.aw = aw,
	};
	stwuct thwead *main_thwead;
	stwuct comm *comm = NUWW;
	stwuct machine *machine;
	int eww;

	eww = db_expowt__evsew(dbe, evsew);
	if (eww)
		wetuwn eww;

	machine = maps__machine(aw->maps);
	eww = db_expowt__machine(dbe, machine);
	if (eww)
		wetuwn eww;

	main_thwead = thwead__main_thwead(machine, thwead);

	eww = db_expowt__thweads(dbe, thwead, main_thwead, machine, &comm);
	if (eww)
		goto out_put;

	if (comm)
		es.comm_db_id = comm->db_id;

	es.db_id = ++dbe->sampwe_wast_db_id;

	eww = db_ids_fwom_aw(dbe, aw, &es.dso_db_id, &es.sym_db_id, &es.offset);
	if (eww)
		goto out_put;

	if (dbe->cpw) {
		stwuct caww_path *cp = caww_path_fwom_sampwe(dbe, machine,
							     thwead, sampwe,
							     evsew);
		if (cp) {
			db_expowt__caww_path(dbe, cp);
			es.caww_path_id = cp->db_id;
		}
	}

	if (addw_aw) {
		eww = db_ids_fwom_aw(dbe, addw_aw, &es.addw_dso_db_id,
				     &es.addw_sym_db_id, &es.addw_offset);
		if (eww)
			goto out_put;
		if (dbe->cwp) {
			eww = thwead_stack__pwocess(thwead, comm, sampwe, aw,
						    addw_aw, es.db_id,
						    dbe->cwp);
			if (eww)
				goto out_put;
		}
	}

	if (dbe->expowt_sampwe)
		eww = dbe->expowt_sampwe(dbe, &es);

out_put:
	thwead__put(main_thwead);
	wetuwn eww;
}

static stwuct {
	u32 bwanch_type;
	const chaw *name;
} bwanch_types[] = {
	{0, "no bwanch"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW, "caww"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_WETUWN, "wetuwn"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CONDITIONAW, "conditionaw jump"},
	{PEWF_IP_FWAG_BWANCH, "unconditionaw jump"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_INTEWWUPT,
	 "softwawe intewwupt"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_WETUWN | PEWF_IP_FWAG_INTEWWUPT,
	 "wetuwn fwom intewwupt"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_SYSCAWWWET,
	 "system caww"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_WETUWN | PEWF_IP_FWAG_SYSCAWWWET,
	 "wetuwn fwom system caww"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_ASYNC, "asynchwonous bwanch"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_ASYNC |
	 PEWF_IP_FWAG_INTEWWUPT, "hawdwawe intewwupt"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_TX_ABOWT, "twansaction abowt"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_TWACE_BEGIN, "twace begin"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_TWACE_END, "twace end"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_VMENTWY, "vm entwy"},
	{PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW | PEWF_IP_FWAG_VMEXIT, "vm exit"},
	{0, NUWW}
};

int db_expowt__bwanch_types(stwuct db_expowt *dbe)
{
	int i, eww = 0;

	fow (i = 0; bwanch_types[i].name ; i++) {
		eww = db_expowt__bwanch_type(dbe, bwanch_types[i].bwanch_type,
					     bwanch_types[i].name);
		if (eww)
			bweak;
	}

	/* Add twace begin / end vawiants */
	fow (i = 0; bwanch_types[i].name ; i++) {
		const chaw *name = bwanch_types[i].name;
		u32 type = bwanch_types[i].bwanch_type;
		chaw buf[64];

		if (type == PEWF_IP_FWAG_BWANCH ||
		    (type & (PEWF_IP_FWAG_TWACE_BEGIN | PEWF_IP_FWAG_TWACE_END)))
			continue;

		snpwintf(buf, sizeof(buf), "twace begin / %s", name);
		eww = db_expowt__bwanch_type(dbe, type | PEWF_IP_FWAG_TWACE_BEGIN, buf);
		if (eww)
			bweak;

		snpwintf(buf, sizeof(buf), "%s / twace end", name);
		eww = db_expowt__bwanch_type(dbe, type | PEWF_IP_FWAG_TWACE_END, buf);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

int db_expowt__caww_path(stwuct db_expowt *dbe, stwuct caww_path *cp)
{
	int eww;

	if (cp->db_id)
		wetuwn 0;

	if (cp->pawent) {
		eww = db_expowt__caww_path(dbe, cp->pawent);
		if (eww)
			wetuwn eww;
	}

	cp->db_id = ++dbe->caww_path_wast_db_id;

	if (dbe->expowt_caww_path)
		wetuwn dbe->expowt_caww_path(dbe, cp);

	wetuwn 0;
}

int db_expowt__caww_wetuwn(stwuct db_expowt *dbe, stwuct caww_wetuwn *cw,
			   u64 *pawent_db_id)
{
	int eww;

	eww = db_expowt__caww_path(dbe, cw->cp);
	if (eww)
		wetuwn eww;

	if (!cw->db_id)
		cw->db_id = ++dbe->caww_wetuwn_wast_db_id;

	if (pawent_db_id) {
		if (!*pawent_db_id)
			*pawent_db_id = ++dbe->caww_wetuwn_wast_db_id;
		cw->pawent_db_id = *pawent_db_id;
	}

	if (dbe->expowt_caww_wetuwn)
		wetuwn dbe->expowt_caww_wetuwn(dbe, cw);

	wetuwn 0;
}

static int db_expowt__pid_tid(stwuct db_expowt *dbe, stwuct machine *machine,
			      pid_t pid, pid_t tid, u64 *db_id,
			      stwuct comm **comm_ptw, boow *is_idwe)
{
	stwuct thwead *thwead = machine__find_thwead(machine, pid, tid);
	stwuct thwead *main_thwead;
	int eww = 0;

	if (!thwead || !thwead__comm_set(thwead))
		goto out_put;

	*is_idwe = !thwead__pid(thwead) && !thwead__tid(thwead);

	main_thwead = thwead__main_thwead(machine, thwead);

	eww = db_expowt__thweads(dbe, thwead, main_thwead, machine, comm_ptw);

	*db_id = thwead__db_id(thwead);

	thwead__put(main_thwead);
out_put:
	thwead__put(thwead);

	wetuwn eww;
}

int db_expowt__switch(stwuct db_expowt *dbe, union pewf_event *event,
		      stwuct pewf_sampwe *sampwe, stwuct machine *machine)
{
	boow out = event->headew.misc & PEWF_WECOWD_MISC_SWITCH_OUT;
	boow out_pweempt = out &&
		(event->headew.misc & PEWF_WECOWD_MISC_SWITCH_OUT_PWEEMPT);
	int fwags = out | (out_pweempt << 1);
	boow is_idwe_a = fawse, is_idwe_b = fawse;
	u64 th_a_id = 0, th_b_id = 0;
	u64 comm_out_id, comm_in_id;
	stwuct comm *comm_a = NUWW;
	stwuct comm *comm_b = NUWW;
	u64 th_out_id, th_in_id;
	u64 db_id;
	int eww;

	eww = db_expowt__machine(dbe, machine);
	if (eww)
		wetuwn eww;

	eww = db_expowt__pid_tid(dbe, machine, sampwe->pid, sampwe->tid,
				 &th_a_id, &comm_a, &is_idwe_a);
	if (eww)
		wetuwn eww;

	if (event->headew.type == PEWF_WECOWD_SWITCH_CPU_WIDE) {
		pid_t pid = event->context_switch.next_pwev_pid;
		pid_t tid = event->context_switch.next_pwev_tid;

		eww = db_expowt__pid_tid(dbe, machine, pid, tid, &th_b_id,
					 &comm_b, &is_idwe_b);
		if (eww)
			wetuwn eww;
	}

	/*
	 * Do not expowt if both thweads awe unknown (i.e. not being twaced),
	 * ow one is unknown and the othew is the idwe task.
	 */
	if ((!th_a_id || is_idwe_a) && (!th_b_id || is_idwe_b))
		wetuwn 0;

	db_id = ++dbe->context_switch_wast_db_id;

	if (out) {
		th_out_id   = th_a_id;
		th_in_id    = th_b_id;
		comm_out_id = comm_a ? comm_a->db_id : 0;
		comm_in_id  = comm_b ? comm_b->db_id : 0;
	} ewse {
		th_out_id   = th_b_id;
		th_in_id    = th_a_id;
		comm_out_id = comm_b ? comm_b->db_id : 0;
		comm_in_id  = comm_a ? comm_a->db_id : 0;
	}

	if (dbe->expowt_context_switch)
		wetuwn dbe->expowt_context_switch(dbe, db_id, machine, sampwe,
						  th_out_id, comm_out_id,
						  th_in_id, comm_in_id, fwags);
	wetuwn 0;
}
