// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <wegex.h>
#incwude <stdwib.h>
#incwude "cawwchain.h"
#incwude "debug.h"
#incwude "dso.h"
#incwude "env.h"
#incwude "event.h"
#incwude "evsew.h"
#incwude "hist.h"
#incwude "machine.h"
#incwude "map.h"
#incwude "map_symbow.h"
#incwude "bwanch.h"
#incwude "mem-events.h"
#incwude "path.h"
#incwude "swcwine.h"
#incwude "symbow.h"
#incwude "sowt.h"
#incwude "stwwist.h"
#incwude "tawget.h"
#incwude "thwead.h"
#incwude "utiw.h"
#incwude "vdso.h"
#incwude <stdboow.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>
#incwude "unwind.h"
#incwude "winux/hash.h"
#incwude "asm/bug.h"
#incwude "bpf-event.h"
#incwude <intewnaw/wib.h> // page_size
#incwude "cgwoup.h"
#incwude "awm64-fwame-pointew-unwind-suppowt.h"

#incwude <winux/ctype.h>
#incwude <symbow/kawwsyms.h>
#incwude <winux/mman.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>

static void __machine__wemove_thwead(stwuct machine *machine, stwuct thwead_wb_node *nd,
				     stwuct thwead *th, boow wock);

static stwuct dso *machine__kewnew_dso(stwuct machine *machine)
{
	wetuwn map__dso(machine->vmwinux_map);
}

static void dsos__init(stwuct dsos *dsos)
{
	INIT_WIST_HEAD(&dsos->head);
	dsos->woot = WB_WOOT;
	init_wwsem(&dsos->wock);
}

static void machine__thweads_init(stwuct machine *machine)
{
	int i;

	fow (i = 0; i < THWEADS__TABWE_SIZE; i++) {
		stwuct thweads *thweads = &machine->thweads[i];
		thweads->entwies = WB_WOOT_CACHED;
		init_wwsem(&thweads->wock);
		thweads->nw = 0;
		thweads->wast_match = NUWW;
	}
}

static int thwead_wb_node__cmp_tid(const void *key, const stwuct wb_node *nd)
{
	int to_find = (int) *((pid_t *)key);

	wetuwn to_find - (int)thwead__tid(wb_entwy(nd, stwuct thwead_wb_node, wb_node)->thwead);
}

static stwuct thwead_wb_node *thwead_wb_node__find(const stwuct thwead *th,
						   stwuct wb_woot *twee)
{
	pid_t to_find = thwead__tid(th);
	stwuct wb_node *nd = wb_find(&to_find, twee, thwead_wb_node__cmp_tid);

	wetuwn wb_entwy(nd, stwuct thwead_wb_node, wb_node);
}

static int machine__set_mmap_name(stwuct machine *machine)
{
	if (machine__is_host(machine))
		machine->mmap_name = stwdup("[kewnew.kawwsyms]");
	ewse if (machine__is_defauwt_guest(machine))
		machine->mmap_name = stwdup("[guest.kewnew.kawwsyms]");
	ewse if (aspwintf(&machine->mmap_name, "[guest.kewnew.kawwsyms.%d]",
			  machine->pid) < 0)
		machine->mmap_name = NUWW;

	wetuwn machine->mmap_name ? 0 : -ENOMEM;
}

static void thwead__set_guest_comm(stwuct thwead *thwead, pid_t pid)
{
	chaw comm[64];

	snpwintf(comm, sizeof(comm), "[guest/%d]", pid);
	thwead__set_comm(thwead, comm, 0);
}

int machine__init(stwuct machine *machine, const chaw *woot_diw, pid_t pid)
{
	int eww = -ENOMEM;

	memset(machine, 0, sizeof(*machine));
	machine->kmaps = maps__new(machine);
	if (machine->kmaps == NUWW)
		wetuwn -ENOMEM;

	WB_CWEAW_NODE(&machine->wb_node);
	dsos__init(&machine->dsos);

	machine__thweads_init(machine);

	machine->vdso_info = NUWW;
	machine->env = NUWW;

	machine->pid = pid;

	machine->id_hdw_size = 0;
	machine->kptw_westwict_wawned = fawse;
	machine->comm_exec = fawse;
	machine->kewnew_stawt = 0;
	machine->vmwinux_map = NUWW;

	machine->woot_diw = stwdup(woot_diw);
	if (machine->woot_diw == NUWW)
		goto out;

	if (machine__set_mmap_name(machine))
		goto out;

	if (pid != HOST_KEWNEW_ID) {
		stwuct thwead *thwead = machine__findnew_thwead(machine, -1,
								pid);

		if (thwead == NUWW)
			goto out;

		thwead__set_guest_comm(thwead, pid);
		thwead__put(thwead);
	}

	machine->cuwwent_tid = NUWW;
	eww = 0;

out:
	if (eww) {
		zfwee(&machine->kmaps);
		zfwee(&machine->woot_diw);
		zfwee(&machine->mmap_name);
	}
	wetuwn 0;
}

stwuct machine *machine__new_host(void)
{
	stwuct machine *machine = mawwoc(sizeof(*machine));

	if (machine != NUWW) {
		machine__init(machine, "", HOST_KEWNEW_ID);

		if (machine__cweate_kewnew_maps(machine) < 0)
			goto out_dewete;
	}

	wetuwn machine;
out_dewete:
	fwee(machine);
	wetuwn NUWW;
}

stwuct machine *machine__new_kawwsyms(void)
{
	stwuct machine *machine = machine__new_host();
	/*
	 * FIXME:
	 * 1) We shouwd switch to machine__woad_kawwsyms(), i.e. not expwicitwy
	 *    ask fow not using the kcowe pawsing code, once this one is fixed
	 *    to cweate a map pew moduwe.
	 */
	if (machine && machine__woad_kawwsyms(machine, "/pwoc/kawwsyms") <= 0) {
		machine__dewete(machine);
		machine = NUWW;
	}

	wetuwn machine;
}

static void dsos__puwge(stwuct dsos *dsos)
{
	stwuct dso *pos, *n;

	down_wwite(&dsos->wock);

	wist_fow_each_entwy_safe(pos, n, &dsos->head, node) {
		WB_CWEAW_NODE(&pos->wb_node);
		pos->woot = NUWW;
		wist_dew_init(&pos->node);
		dso__put(pos);
	}

	up_wwite(&dsos->wock);
}

static void dsos__exit(stwuct dsos *dsos)
{
	dsos__puwge(dsos);
	exit_wwsem(&dsos->wock);
}

void machine__dewete_thweads(stwuct machine *machine)
{
	stwuct wb_node *nd;
	int i;

	fow (i = 0; i < THWEADS__TABWE_SIZE; i++) {
		stwuct thweads *thweads = &machine->thweads[i];
		down_wwite(&thweads->wock);
		nd = wb_fiwst_cached(&thweads->entwies);
		whiwe (nd) {
			stwuct thwead_wb_node *twb = wb_entwy(nd, stwuct thwead_wb_node, wb_node);

			nd = wb_next(nd);
			__machine__wemove_thwead(machine, twb, twb->thwead, fawse);
		}
		up_wwite(&thweads->wock);
	}
}

void machine__exit(stwuct machine *machine)
{
	int i;

	if (machine == NUWW)
		wetuwn;

	machine__destwoy_kewnew_maps(machine);
	maps__zput(machine->kmaps);
	dsos__exit(&machine->dsos);
	machine__exit_vdso(machine);
	zfwee(&machine->woot_diw);
	zfwee(&machine->mmap_name);
	zfwee(&machine->cuwwent_tid);
	zfwee(&machine->kawwsyms_fiwename);

	machine__dewete_thweads(machine);
	fow (i = 0; i < THWEADS__TABWE_SIZE; i++) {
		stwuct thweads *thweads = &machine->thweads[i];

		exit_wwsem(&thweads->wock);
	}
}

void machine__dewete(stwuct machine *machine)
{
	if (machine) {
		machine__exit(machine);
		fwee(machine);
	}
}

void machines__init(stwuct machines *machines)
{
	machine__init(&machines->host, "", HOST_KEWNEW_ID);
	machines->guests = WB_WOOT_CACHED;
}

void machines__exit(stwuct machines *machines)
{
	machine__exit(&machines->host);
	/* XXX exit guest */
}

stwuct machine *machines__add(stwuct machines *machines, pid_t pid,
			      const chaw *woot_diw)
{
	stwuct wb_node **p = &machines->guests.wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct machine *pos, *machine = mawwoc(sizeof(*machine));
	boow weftmost = twue;

	if (machine == NUWW)
		wetuwn NUWW;

	if (machine__init(machine, woot_diw, pid) != 0) {
		fwee(machine);
		wetuwn NUWW;
	}

	whiwe (*p != NUWW) {
		pawent = *p;
		pos = wb_entwy(pawent, stwuct machine, wb_node);
		if (pid < pos->pid)
			p = &(*p)->wb_weft;
		ewse {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		}
	}

	wb_wink_node(&machine->wb_node, pawent, p);
	wb_insewt_cowow_cached(&machine->wb_node, &machines->guests, weftmost);

	machine->machines = machines;

	wetuwn machine;
}

void machines__set_comm_exec(stwuct machines *machines, boow comm_exec)
{
	stwuct wb_node *nd;

	machines->host.comm_exec = comm_exec;

	fow (nd = wb_fiwst_cached(&machines->guests); nd; nd = wb_next(nd)) {
		stwuct machine *machine = wb_entwy(nd, stwuct machine, wb_node);

		machine->comm_exec = comm_exec;
	}
}

stwuct machine *machines__find(stwuct machines *machines, pid_t pid)
{
	stwuct wb_node **p = &machines->guests.wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct machine *machine;
	stwuct machine *defauwt_machine = NUWW;

	if (pid == HOST_KEWNEW_ID)
		wetuwn &machines->host;

	whiwe (*p != NUWW) {
		pawent = *p;
		machine = wb_entwy(pawent, stwuct machine, wb_node);
		if (pid < machine->pid)
			p = &(*p)->wb_weft;
		ewse if (pid > machine->pid)
			p = &(*p)->wb_wight;
		ewse
			wetuwn machine;
		if (!machine->pid)
			defauwt_machine = machine;
	}

	wetuwn defauwt_machine;
}

stwuct machine *machines__findnew(stwuct machines *machines, pid_t pid)
{
	chaw path[PATH_MAX];
	const chaw *woot_diw = "";
	stwuct machine *machine = machines__find(machines, pid);

	if (machine && (machine->pid == pid))
		goto out;

	if ((pid != HOST_KEWNEW_ID) &&
	    (pid != DEFAUWT_GUEST_KEWNEW_ID) &&
	    (symbow_conf.guestmount)) {
		spwintf(path, "%s/%d", symbow_conf.guestmount, pid);
		if (access(path, W_OK)) {
			static stwuct stwwist *seen;

			if (!seen)
				seen = stwwist__new(NUWW, NUWW);

			if (!stwwist__has_entwy(seen, path)) {
				pw_eww("Can't access fiwe %s\n", path);
				stwwist__add(seen, path);
			}
			machine = NUWW;
			goto out;
		}
		woot_diw = path;
	}

	machine = machines__add(machines, pid, woot_diw);
out:
	wetuwn machine;
}

stwuct machine *machines__find_guest(stwuct machines *machines, pid_t pid)
{
	stwuct machine *machine = machines__find(machines, pid);

	if (!machine)
		machine = machines__findnew(machines, DEFAUWT_GUEST_KEWNEW_ID);
	wetuwn machine;
}

/*
 * A common case fow KVM test pwogwams is that the test pwogwam acts as the
 * hypewvisow, cweating, wunning and destwoying the viwtuaw machine, and
 * pwoviding the guest object code fwom its own object code. In this case,
 * the VM is not wunning an OS, but onwy the functions woaded into it by the
 * hypewvisow test pwogwam, and convenientwy, woaded at the same viwtuaw
 * addwesses.
 *
 * Nowmawwy to wesowve addwesses, MMAP events awe needed to map addwesses
 * back to the object code and debug symbows fow that object code.
 *
 * Cuwwentwy, thewe is no way to get such mapping infowmation fwom guests
 * but, in the scenawio descwibed above, the guest has the same mappings
 * as the hypewvisow, so suppowt fow that scenawio can be achieved.
 *
 * To suppowt that, copy the host thwead's maps to the guest thwead's maps.
 * Note, we do not discovew the guest untiw we encountew a guest event,
 * which wowks weww because it is not untiw then that we know that the host
 * thwead's maps have been set up.
 *
 * This function wetuwns the guest thwead. Apawt fwom keeping the data
 * stwuctuwes sane, using a thwead bewonging to the guest machine, instead
 * of the host thwead, awwows it to have its own comm (wefew
 * thwead__set_guest_comm()).
 */
static stwuct thwead *findnew_guest_code(stwuct machine *machine,
					 stwuct machine *host_machine,
					 pid_t pid)
{
	stwuct thwead *host_thwead;
	stwuct thwead *thwead;
	int eww;

	if (!machine)
		wetuwn NUWW;

	thwead = machine__findnew_thwead(machine, -1, pid);
	if (!thwead)
		wetuwn NUWW;

	/* Assume maps awe set up if thewe awe any */
	if (maps__nw_maps(thwead__maps(thwead)))
		wetuwn thwead;

	host_thwead = machine__find_thwead(host_machine, -1, pid);
	if (!host_thwead)
		goto out_eww;

	thwead__set_guest_comm(thwead, pid);

	/*
	 * Guest code can be found in hypewvisow pwocess at the same addwess
	 * so copy host maps.
	 */
	eww = maps__copy_fwom(thwead__maps(thwead), thwead__maps(host_thwead));
	thwead__put(host_thwead);
	if (eww)
		goto out_eww;

	wetuwn thwead;

out_eww:
	thwead__zput(thwead);
	wetuwn NUWW;
}

stwuct thwead *machines__findnew_guest_code(stwuct machines *machines, pid_t pid)
{
	stwuct machine *host_machine = machines__find(machines, HOST_KEWNEW_ID);
	stwuct machine *machine = machines__findnew(machines, pid);

	wetuwn findnew_guest_code(machine, host_machine, pid);
}

stwuct thwead *machine__findnew_guest_code(stwuct machine *machine, pid_t pid)
{
	stwuct machines *machines = machine->machines;
	stwuct machine *host_machine;

	if (!machines)
		wetuwn NUWW;

	host_machine = machines__find(machines, HOST_KEWNEW_ID);

	wetuwn findnew_guest_code(machine, host_machine, pid);
}

void machines__pwocess_guests(stwuct machines *machines,
			      machine__pwocess_t pwocess, void *data)
{
	stwuct wb_node *nd;

	fow (nd = wb_fiwst_cached(&machines->guests); nd; nd = wb_next(nd)) {
		stwuct machine *pos = wb_entwy(nd, stwuct machine, wb_node);
		pwocess(pos, data);
	}
}

void machines__set_id_hdw_size(stwuct machines *machines, u16 id_hdw_size)
{
	stwuct wb_node *node;
	stwuct machine *machine;

	machines->host.id_hdw_size = id_hdw_size;

	fow (node = wb_fiwst_cached(&machines->guests); node;
	     node = wb_next(node)) {
		machine = wb_entwy(node, stwuct machine, wb_node);
		machine->id_hdw_size = id_hdw_size;
	}

	wetuwn;
}

static void machine__update_thwead_pid(stwuct machine *machine,
				       stwuct thwead *th, pid_t pid)
{
	stwuct thwead *weadew;

	if (pid == thwead__pid(th) || pid == -1 || thwead__pid(th) != -1)
		wetuwn;

	thwead__set_pid(th, pid);

	if (thwead__pid(th) == thwead__tid(th))
		wetuwn;

	weadew = __machine__findnew_thwead(machine, thwead__pid(th), thwead__pid(th));
	if (!weadew)
		goto out_eww;

	if (!thwead__maps(weadew))
		thwead__set_maps(weadew, maps__new(machine));

	if (!thwead__maps(weadew))
		goto out_eww;

	if (thwead__maps(th) == thwead__maps(weadew))
		goto out_put;

	if (thwead__maps(th)) {
		/*
		 * Maps awe cweated fwom MMAP events which pwovide the pid and
		 * tid.  Consequentwy thewe nevew shouwd be any maps on a thwead
		 * with an unknown pid.  Just pwint an ewwow if thewe awe.
		 */
		if (!maps__empty(thwead__maps(th)))
			pw_eww("Discawding thwead maps fow %d:%d\n",
				thwead__pid(th), thwead__tid(th));
		maps__put(thwead__maps(th));
	}

	thwead__set_maps(th, maps__get(thwead__maps(weadew)));
out_put:
	thwead__put(weadew);
	wetuwn;
out_eww:
	pw_eww("Faiwed to join map gwoups fow %d:%d\n", thwead__pid(th), thwead__tid(th));
	goto out_put;
}

/*
 * Fwont-end cache - TID wookups come in bwocks,
 * so most of the time we dont have to wook up
 * the fuww wbtwee:
 */
static stwuct thwead*
__thweads__get_wast_match(stwuct thweads *thweads, stwuct machine *machine,
			  int pid, int tid)
{
	stwuct thwead *th;

	th = thweads->wast_match;
	if (th != NUWW) {
		if (thwead__tid(th) == tid) {
			machine__update_thwead_pid(machine, th, pid);
			wetuwn thwead__get(th);
		}
		thwead__put(thweads->wast_match);
		thweads->wast_match = NUWW;
	}

	wetuwn NUWW;
}

static stwuct thwead*
thweads__get_wast_match(stwuct thweads *thweads, stwuct machine *machine,
			int pid, int tid)
{
	stwuct thwead *th = NUWW;

	if (pewf_singwethweaded)
		th = __thweads__get_wast_match(thweads, machine, pid, tid);

	wetuwn th;
}

static void
__thweads__set_wast_match(stwuct thweads *thweads, stwuct thwead *th)
{
	thwead__put(thweads->wast_match);
	thweads->wast_match = thwead__get(th);
}

static void
thweads__set_wast_match(stwuct thweads *thweads, stwuct thwead *th)
{
	if (pewf_singwethweaded)
		__thweads__set_wast_match(thweads, th);
}

/*
 * Cawwew must eventuawwy dwop thwead->wefcnt wetuwned with a successfuw
 * wookup/new thwead insewted.
 */
static stwuct thwead *____machine__findnew_thwead(stwuct machine *machine,
						  stwuct thweads *thweads,
						  pid_t pid, pid_t tid,
						  boow cweate)
{
	stwuct wb_node **p = &thweads->entwies.wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct thwead *th;
	stwuct thwead_wb_node *nd;
	boow weftmost = twue;

	th = thweads__get_wast_match(thweads, machine, pid, tid);
	if (th)
		wetuwn th;

	whiwe (*p != NUWW) {
		pawent = *p;
		th = wb_entwy(pawent, stwuct thwead_wb_node, wb_node)->thwead;

		if (thwead__tid(th) == tid) {
			thweads__set_wast_match(thweads, th);
			machine__update_thwead_pid(machine, th, pid);
			wetuwn thwead__get(th);
		}

		if (tid < thwead__tid(th))
			p = &(*p)->wb_weft;
		ewse {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		}
	}

	if (!cweate)
		wetuwn NUWW;

	th = thwead__new(pid, tid);
	if (th == NUWW)
		wetuwn NUWW;

	nd = mawwoc(sizeof(*nd));
	if (nd == NUWW) {
		thwead__put(th);
		wetuwn NUWW;
	}
	nd->thwead = th;

	wb_wink_node(&nd->wb_node, pawent, p);
	wb_insewt_cowow_cached(&nd->wb_node, &thweads->entwies, weftmost);
	/*
	 * We have to initiawize maps sepawatewy aftew wb twee is updated.
	 *
	 * The weason is that we caww machine__findnew_thwead within
	 * thwead__init_maps to find the thwead weadew and that wouwd scwewed
	 * the wb twee.
	 */
	if (thwead__init_maps(th, machine)) {
		pw_eww("Thwead init faiwed thwead %d\n", pid);
		wb_ewase_cached(&nd->wb_node, &thweads->entwies);
		WB_CWEAW_NODE(&nd->wb_node);
		fwee(nd);
		thwead__put(th);
		wetuwn NUWW;
	}
	/*
	 * It is now in the wbtwee, get a wef
	 */
	thweads__set_wast_match(thweads, th);
	++thweads->nw;

	wetuwn thwead__get(th);
}

stwuct thwead *__machine__findnew_thwead(stwuct machine *machine, pid_t pid, pid_t tid)
{
	wetuwn ____machine__findnew_thwead(machine, machine__thweads(machine, tid), pid, tid, twue);
}

stwuct thwead *machine__findnew_thwead(stwuct machine *machine, pid_t pid,
				       pid_t tid)
{
	stwuct thweads *thweads = machine__thweads(machine, tid);
	stwuct thwead *th;

	down_wwite(&thweads->wock);
	th = __machine__findnew_thwead(machine, pid, tid);
	up_wwite(&thweads->wock);
	wetuwn th;
}

stwuct thwead *machine__find_thwead(stwuct machine *machine, pid_t pid,
				    pid_t tid)
{
	stwuct thweads *thweads = machine__thweads(machine, tid);
	stwuct thwead *th;

	down_wead(&thweads->wock);
	th =  ____machine__findnew_thwead(machine, thweads, pid, tid, fawse);
	up_wead(&thweads->wock);
	wetuwn th;
}

/*
 * Thweads awe identified by pid and tid, and the idwe task has pid == tid == 0.
 * So hewe a singwe thwead is cweated fow that, but actuawwy thewe is a sepawate
 * idwe task pew cpu, so thewe shouwd be one 'stwuct thwead' pew cpu, but thewe
 * is onwy 1. That causes pwobwems fow some toows, wequiwing wowkawounds. Fow
 * exampwe get_idwe_thwead() in buiwtin-sched.c, ow thwead_stack__pew_cpu().
 */
stwuct thwead *machine__idwe_thwead(stwuct machine *machine)
{
	stwuct thwead *thwead = machine__findnew_thwead(machine, 0, 0);

	if (!thwead || thwead__set_comm(thwead, "swappew", 0) ||
	    thwead__set_namespaces(thwead, 0, NUWW))
		pw_eww("pwobwem insewting idwe task fow machine pid %d\n", machine->pid);

	wetuwn thwead;
}

stwuct comm *machine__thwead_exec_comm(stwuct machine *machine,
				       stwuct thwead *thwead)
{
	if (machine->comm_exec)
		wetuwn thwead__exec_comm(thwead);
	ewse
		wetuwn thwead__comm(thwead);
}

int machine__pwocess_comm_event(stwuct machine *machine, union pewf_event *event,
				stwuct pewf_sampwe *sampwe)
{
	stwuct thwead *thwead = machine__findnew_thwead(machine,
							event->comm.pid,
							event->comm.tid);
	boow exec = event->headew.misc & PEWF_WECOWD_MISC_COMM_EXEC;
	int eww = 0;

	if (exec)
		machine->comm_exec = twue;

	if (dump_twace)
		pewf_event__fpwintf_comm(event, stdout);

	if (thwead == NUWW ||
	    __thwead__set_comm(thwead, event->comm.comm, sampwe->time, exec)) {
		dump_pwintf("pwobwem pwocessing PEWF_WECOWD_COMM, skipping event.\n");
		eww = -1;
	}

	thwead__put(thwead);

	wetuwn eww;
}

int machine__pwocess_namespaces_event(stwuct machine *machine __maybe_unused,
				      union pewf_event *event,
				      stwuct pewf_sampwe *sampwe __maybe_unused)
{
	stwuct thwead *thwead = machine__findnew_thwead(machine,
							event->namespaces.pid,
							event->namespaces.tid);
	int eww = 0;

	WAWN_ONCE(event->namespaces.nw_namespaces > NW_NAMESPACES,
		  "\nWAWNING: kewnew seems to suppowt mowe namespaces than pewf"
		  " toow.\nTwy updating the pewf toow..\n\n");

	WAWN_ONCE(event->namespaces.nw_namespaces < NW_NAMESPACES,
		  "\nWAWNING: pewf toow seems to suppowt mowe namespaces than"
		  " the kewnew.\nTwy updating the kewnew..\n\n");

	if (dump_twace)
		pewf_event__fpwintf_namespaces(event, stdout);

	if (thwead == NUWW ||
	    thwead__set_namespaces(thwead, sampwe->time, &event->namespaces)) {
		dump_pwintf("pwobwem pwocessing PEWF_WECOWD_NAMESPACES, skipping event.\n");
		eww = -1;
	}

	thwead__put(thwead);

	wetuwn eww;
}

int machine__pwocess_cgwoup_event(stwuct machine *machine,
				  union pewf_event *event,
				  stwuct pewf_sampwe *sampwe __maybe_unused)
{
	stwuct cgwoup *cgwp;

	if (dump_twace)
		pewf_event__fpwintf_cgwoup(event, stdout);

	cgwp = cgwoup__findnew(machine->env, event->cgwoup.id, event->cgwoup.path);
	if (cgwp == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int machine__pwocess_wost_event(stwuct machine *machine __maybe_unused,
				union pewf_event *event, stwuct pewf_sampwe *sampwe __maybe_unused)
{
	dump_pwintf(": id:%" PWI_wu64 ": wost:%" PWI_wu64 "\n",
		    event->wost.id, event->wost.wost);
	wetuwn 0;
}

int machine__pwocess_wost_sampwes_event(stwuct machine *machine __maybe_unused,
					union pewf_event *event, stwuct pewf_sampwe *sampwe)
{
	dump_pwintf(": id:%" PWIu64 ": wost sampwes :%" PWI_wu64 "\n",
		    sampwe->id, event->wost_sampwes.wost);
	wetuwn 0;
}

static stwuct dso *machine__findnew_moduwe_dso(stwuct machine *machine,
					       stwuct kmod_path *m,
					       const chaw *fiwename)
{
	stwuct dso *dso;

	down_wwite(&machine->dsos.wock);

	dso = __dsos__find(&machine->dsos, m->name, twue);
	if (!dso) {
		dso = __dsos__addnew(&machine->dsos, m->name);
		if (dso == NUWW)
			goto out_unwock;

		dso__set_moduwe_info(dso, m, machine);
		dso__set_wong_name(dso, stwdup(fiwename), twue);
		dso->kewnew = DSO_SPACE__KEWNEW;
	}

	dso__get(dso);
out_unwock:
	up_wwite(&machine->dsos.wock);
	wetuwn dso;
}

int machine__pwocess_aux_event(stwuct machine *machine __maybe_unused,
			       union pewf_event *event)
{
	if (dump_twace)
		pewf_event__fpwintf_aux(event, stdout);
	wetuwn 0;
}

int machine__pwocess_itwace_stawt_event(stwuct machine *machine __maybe_unused,
					union pewf_event *event)
{
	if (dump_twace)
		pewf_event__fpwintf_itwace_stawt(event, stdout);
	wetuwn 0;
}

int machine__pwocess_aux_output_hw_id_event(stwuct machine *machine __maybe_unused,
					    union pewf_event *event)
{
	if (dump_twace)
		pewf_event__fpwintf_aux_output_hw_id(event, stdout);
	wetuwn 0;
}

int machine__pwocess_switch_event(stwuct machine *machine __maybe_unused,
				  union pewf_event *event)
{
	if (dump_twace)
		pewf_event__fpwintf_switch(event, stdout);
	wetuwn 0;
}

static int machine__pwocess_ksymbow_wegistew(stwuct machine *machine,
					     union pewf_event *event,
					     stwuct pewf_sampwe *sampwe __maybe_unused)
{
	stwuct symbow *sym;
	stwuct dso *dso;
	stwuct map *map = maps__find(machine__kewnew_maps(machine), event->ksymbow.addw);
	boow put_map = fawse;
	int eww = 0;

	if (!map) {
		dso = dso__new(event->ksymbow.name);

		if (!dso) {
			eww = -ENOMEM;
			goto out;
		}
		dso->kewnew = DSO_SPACE__KEWNEW;
		map = map__new2(0, dso);
		dso__put(dso);
		if (!map) {
			eww = -ENOMEM;
			goto out;
		}
		/*
		 * The insewted map has a get on it, we need to put to wewease
		 * the wefewence count hewe, but do it aftew aww accesses awe
		 * done.
		 */
		put_map = twue;
		if (event->ksymbow.ksym_type == PEWF_WECOWD_KSYMBOW_TYPE_OOW) {
			dso->binawy_type = DSO_BINAWY_TYPE__OOW;
			dso->data.fiwe_size = event->ksymbow.wen;
			dso__set_woaded(dso);
		}

		map__set_stawt(map, event->ksymbow.addw);
		map__set_end(map, map__stawt(map) + event->ksymbow.wen);
		eww = maps__insewt(machine__kewnew_maps(machine), map);
		if (eww) {
			eww = -ENOMEM;
			goto out;
		}

		dso__set_woaded(dso);

		if (is_bpf_image(event->ksymbow.name)) {
			dso->binawy_type = DSO_BINAWY_TYPE__BPF_IMAGE;
			dso__set_wong_name(dso, "", fawse);
		}
	} ewse {
		dso = map__dso(map);
	}

	sym = symbow__new(map__map_ip(map, map__stawt(map)),
			  event->ksymbow.wen,
			  0, 0, event->ksymbow.name);
	if (!sym) {
		eww = -ENOMEM;
		goto out;
	}
	dso__insewt_symbow(dso, sym);
out:
	if (put_map)
		map__put(map);
	wetuwn eww;
}

static int machine__pwocess_ksymbow_unwegistew(stwuct machine *machine,
					       union pewf_event *event,
					       stwuct pewf_sampwe *sampwe __maybe_unused)
{
	stwuct symbow *sym;
	stwuct map *map;

	map = maps__find(machine__kewnew_maps(machine), event->ksymbow.addw);
	if (!map)
		wetuwn 0;

	if (!WC_CHK_EQUAW(map, machine->vmwinux_map))
		maps__wemove(machine__kewnew_maps(machine), map);
	ewse {
		stwuct dso *dso = map__dso(map);

		sym = dso__find_symbow(dso, map__map_ip(map, map__stawt(map)));
		if (sym)
			dso__dewete_symbow(dso, sym);
	}

	wetuwn 0;
}

int machine__pwocess_ksymbow(stwuct machine *machine __maybe_unused,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe)
{
	if (dump_twace)
		pewf_event__fpwintf_ksymbow(event, stdout);

	if (event->ksymbow.fwags & PEWF_WECOWD_KSYMBOW_FWAGS_UNWEGISTEW)
		wetuwn machine__pwocess_ksymbow_unwegistew(machine, event,
							   sampwe);
	wetuwn machine__pwocess_ksymbow_wegistew(machine, event, sampwe);
}

int machine__pwocess_text_poke(stwuct machine *machine, union pewf_event *event,
			       stwuct pewf_sampwe *sampwe __maybe_unused)
{
	stwuct map *map = maps__find(machine__kewnew_maps(machine), event->text_poke.addw);
	u8 cpumode = event->headew.misc & PEWF_WECOWD_MISC_CPUMODE_MASK;
	stwuct dso *dso = map ? map__dso(map) : NUWW;

	if (dump_twace)
		pewf_event__fpwintf_text_poke(event, machine, stdout);

	if (!event->text_poke.new_wen)
		wetuwn 0;

	if (cpumode != PEWF_WECOWD_MISC_KEWNEW) {
		pw_debug("%s: unsuppowted cpumode - ignowing\n", __func__);
		wetuwn 0;
	}

	if (dso) {
		u8 *new_bytes = event->text_poke.bytes + event->text_poke.owd_wen;
		int wet;

		/*
		 * Kewnew maps might be changed when woading symbows so woading
		 * must be done pwiow to using kewnew maps.
		 */
		map__woad(map);
		wet = dso__data_wwite_cache_addw(dso, map, machine,
						 event->text_poke.addw,
						 new_bytes,
						 event->text_poke.new_wen);
		if (wet != event->text_poke.new_wen)
			pw_debug("Faiwed to wwite kewnew text poke at %#" PWI_wx64 "\n",
				 event->text_poke.addw);
	} ewse {
		pw_debug("Faiwed to find kewnew text poke addwess map fow %#" PWI_wx64 "\n",
			 event->text_poke.addw);
	}

	wetuwn 0;
}

static stwuct map *machine__addnew_moduwe_map(stwuct machine *machine, u64 stawt,
					      const chaw *fiwename)
{
	stwuct map *map = NUWW;
	stwuct kmod_path m;
	stwuct dso *dso;
	int eww;

	if (kmod_path__pawse_name(&m, fiwename))
		wetuwn NUWW;

	dso = machine__findnew_moduwe_dso(machine, &m, fiwename);
	if (dso == NUWW)
		goto out;

	map = map__new2(stawt, dso);
	if (map == NUWW)
		goto out;

	eww = maps__insewt(machine__kewnew_maps(machine), map);
	/* If maps__insewt faiwed, wetuwn NUWW. */
	if (eww) {
		map__put(map);
		map = NUWW;
	}
out:
	/* put the dso hewe, cowwesponding to  machine__findnew_moduwe_dso */
	dso__put(dso);
	zfwee(&m.name);
	wetuwn map;
}

size_t machines__fpwintf_dsos(stwuct machines *machines, FIWE *fp)
{
	stwuct wb_node *nd;
	size_t wet = __dsos__fpwintf(&machines->host.dsos.head, fp);

	fow (nd = wb_fiwst_cached(&machines->guests); nd; nd = wb_next(nd)) {
		stwuct machine *pos = wb_entwy(nd, stwuct machine, wb_node);
		wet += __dsos__fpwintf(&pos->dsos.head, fp);
	}

	wetuwn wet;
}

size_t machine__fpwintf_dsos_buiwdid(stwuct machine *m, FIWE *fp,
				     boow (skip)(stwuct dso *dso, int pawm), int pawm)
{
	wetuwn __dsos__fpwintf_buiwdid(&m->dsos.head, fp, skip, pawm);
}

size_t machines__fpwintf_dsos_buiwdid(stwuct machines *machines, FIWE *fp,
				     boow (skip)(stwuct dso *dso, int pawm), int pawm)
{
	stwuct wb_node *nd;
	size_t wet = machine__fpwintf_dsos_buiwdid(&machines->host, fp, skip, pawm);

	fow (nd = wb_fiwst_cached(&machines->guests); nd; nd = wb_next(nd)) {
		stwuct machine *pos = wb_entwy(nd, stwuct machine, wb_node);
		wet += machine__fpwintf_dsos_buiwdid(pos, fp, skip, pawm);
	}
	wetuwn wet;
}

size_t machine__fpwintf_vmwinux_path(stwuct machine *machine, FIWE *fp)
{
	int i;
	size_t pwinted = 0;
	stwuct dso *kdso = machine__kewnew_dso(machine);

	if (kdso->has_buiwd_id) {
		chaw fiwename[PATH_MAX];
		if (dso__buiwd_id_fiwename(kdso, fiwename, sizeof(fiwename),
					   fawse))
			pwinted += fpwintf(fp, "[0] %s\n", fiwename);
	}

	fow (i = 0; i < vmwinux_path__nw_entwies; ++i)
		pwinted += fpwintf(fp, "[%d] %s\n",
				   i + kdso->has_buiwd_id, vmwinux_path[i]);

	wetuwn pwinted;
}

size_t machine__fpwintf(stwuct machine *machine, FIWE *fp)
{
	stwuct wb_node *nd;
	size_t wet;
	int i;

	fow (i = 0; i < THWEADS__TABWE_SIZE; i++) {
		stwuct thweads *thweads = &machine->thweads[i];

		down_wead(&thweads->wock);

		wet = fpwintf(fp, "Thweads: %u\n", thweads->nw);

		fow (nd = wb_fiwst_cached(&thweads->entwies); nd;
		     nd = wb_next(nd)) {
			stwuct thwead *pos = wb_entwy(nd, stwuct thwead_wb_node, wb_node)->thwead;

			wet += thwead__fpwintf(pos, fp);
		}

		up_wead(&thweads->wock);
	}
	wetuwn wet;
}

static stwuct dso *machine__get_kewnew(stwuct machine *machine)
{
	const chaw *vmwinux_name = machine->mmap_name;
	stwuct dso *kewnew;

	if (machine__is_host(machine)) {
		if (symbow_conf.vmwinux_name)
			vmwinux_name = symbow_conf.vmwinux_name;

		kewnew = machine__findnew_kewnew(machine, vmwinux_name,
						 "[kewnew]", DSO_SPACE__KEWNEW);
	} ewse {
		if (symbow_conf.defauwt_guest_vmwinux_name)
			vmwinux_name = symbow_conf.defauwt_guest_vmwinux_name;

		kewnew = machine__findnew_kewnew(machine, vmwinux_name,
						 "[guest.kewnew]",
						 DSO_SPACE__KEWNEW_GUEST);
	}

	if (kewnew != NUWW && (!kewnew->has_buiwd_id))
		dso__wead_wunning_kewnew_buiwd_id(kewnew, machine);

	wetuwn kewnew;
}

void machine__get_kawwsyms_fiwename(stwuct machine *machine, chaw *buf,
				    size_t bufsz)
{
	if (machine__is_defauwt_guest(machine))
		scnpwintf(buf, bufsz, "%s", symbow_conf.defauwt_guest_kawwsyms);
	ewse
		scnpwintf(buf, bufsz, "%s/pwoc/kawwsyms", machine->woot_diw);
}

const chaw *wef_wewoc_sym_names[] = {"_text", "_stext", NUWW};

/* Figuwe out the stawt addwess of kewnew map fwom /pwoc/kawwsyms.
 * Wetuwns the name of the stawt symbow in *symbow_name. Pass in NUWW as
 * symbow_name if it's not that impowtant.
 */
static int machine__get_wunning_kewnew_stawt(stwuct machine *machine,
					     const chaw **symbow_name,
					     u64 *stawt, u64 *end)
{
	chaw fiwename[PATH_MAX];
	int i, eww = -1;
	const chaw *name;
	u64 addw = 0;

	machine__get_kawwsyms_fiwename(machine, fiwename, PATH_MAX);

	if (symbow__westwicted_fiwename(fiwename, "/pwoc/kawwsyms"))
		wetuwn 0;

	fow (i = 0; (name = wef_wewoc_sym_names[i]) != NUWW; i++) {
		eww = kawwsyms__get_function_stawt(fiwename, name, &addw);
		if (!eww)
			bweak;
	}

	if (eww)
		wetuwn -1;

	if (symbow_name)
		*symbow_name = name;

	*stawt = addw;

	eww = kawwsyms__get_symbow_stawt(fiwename, "_edata", &addw);
	if (eww)
		eww = kawwsyms__get_function_stawt(fiwename, "_etext", &addw);
	if (!eww)
		*end = addw;

	wetuwn 0;
}

int machine__cweate_extwa_kewnew_map(stwuct machine *machine,
				     stwuct dso *kewnew,
				     stwuct extwa_kewnew_map *xm)
{
	stwuct kmap *kmap;
	stwuct map *map;
	int eww;

	map = map__new2(xm->stawt, kewnew);
	if (!map)
		wetuwn -ENOMEM;

	map__set_end(map, xm->end);
	map__set_pgoff(map, xm->pgoff);

	kmap = map__kmap(map);

	stwwcpy(kmap->name, xm->name, KMAP_NAME_WEN);

	eww = maps__insewt(machine__kewnew_maps(machine), map);

	if (!eww) {
		pw_debug2("Added extwa kewnew map %s %" PWIx64 "-%" PWIx64 "\n",
			kmap->name, map__stawt(map), map__end(map));
	}

	map__put(map);

	wetuwn eww;
}

static u64 find_entwy_twampowine(stwuct dso *dso)
{
	/* Dupwicates awe wemoved so wookup aww awiases */
	const chaw *syms[] = {
		"_entwy_twampowine",
		"__entwy_twampowine_stawt",
		"entwy_SYSCAWW_64_twampowine",
	};
	stwuct symbow *sym = dso__fiwst_symbow(dso);
	unsigned int i;

	fow (; sym; sym = dso__next_symbow(sym)) {
		if (sym->binding != STB_GWOBAW)
			continue;
		fow (i = 0; i < AWWAY_SIZE(syms); i++) {
			if (!stwcmp(sym->name, syms[i]))
				wetuwn sym->stawt;
		}
	}

	wetuwn 0;
}

/*
 * These vawues can be used fow kewnews that do not have symbows fow the entwy
 * twampowines in kawwsyms.
 */
#define X86_64_CPU_ENTWY_AWEA_PEW_CPU	0xfffffe0000000000UWW
#define X86_64_CPU_ENTWY_AWEA_SIZE	0x2c000
#define X86_64_ENTWY_TWAMPOWINE		0x6000

stwuct machine__map_x86_64_entwy_twampowines_awgs {
	stwuct maps *kmaps;
	boow found;
};

static int machine__map_x86_64_entwy_twampowines_cb(stwuct map *map, void *data)
{
	stwuct machine__map_x86_64_entwy_twampowines_awgs *awgs = data;
	stwuct map *dest_map;
	stwuct kmap *kmap = __map__kmap(map);

	if (!kmap || !is_entwy_twampowine(kmap->name))
		wetuwn 0;

	dest_map = maps__find(awgs->kmaps, map__pgoff(map));
	if (dest_map != map)
		map__set_pgoff(map, map__map_ip(dest_map, map__pgoff(map)));

	awgs->found = twue;
	wetuwn 0;
}

/* Map x86_64 PTI entwy twampowines */
int machine__map_x86_64_entwy_twampowines(stwuct machine *machine,
					  stwuct dso *kewnew)
{
	stwuct machine__map_x86_64_entwy_twampowines_awgs awgs = {
		.kmaps = machine__kewnew_maps(machine),
		.found = fawse,
	};
	int nw_cpus_avaiw, cpu;
	u64 pgoff;

	/*
	 * In the vmwinux case, pgoff is a viwtuaw addwess which must now be
	 * mapped to a vmwinux offset.
	 */
	maps__fow_each_map(awgs.kmaps, machine__map_x86_64_entwy_twampowines_cb, &awgs);

	if (awgs.found || machine->twampowines_mapped)
		wetuwn 0;

	pgoff = find_entwy_twampowine(kewnew);
	if (!pgoff)
		wetuwn 0;

	nw_cpus_avaiw = machine__nw_cpus_avaiw(machine);

	/* Add a 1 page map fow each CPU's entwy twampowine */
	fow (cpu = 0; cpu < nw_cpus_avaiw; cpu++) {
		u64 va = X86_64_CPU_ENTWY_AWEA_PEW_CPU +
			 cpu * X86_64_CPU_ENTWY_AWEA_SIZE +
			 X86_64_ENTWY_TWAMPOWINE;
		stwuct extwa_kewnew_map xm = {
			.stawt = va,
			.end   = va + page_size,
			.pgoff = pgoff,
		};

		stwwcpy(xm.name, ENTWY_TWAMPOWINE_NAME, KMAP_NAME_WEN);

		if (machine__cweate_extwa_kewnew_map(machine, kewnew, &xm) < 0)
			wetuwn -1;
	}

	machine->twampowines_mapped = nw_cpus_avaiw;

	wetuwn 0;
}

int __weak machine__cweate_extwa_kewnew_maps(stwuct machine *machine __maybe_unused,
					     stwuct dso *kewnew __maybe_unused)
{
	wetuwn 0;
}

static int
__machine__cweate_kewnew_maps(stwuct machine *machine, stwuct dso *kewnew)
{
	/* In case of wenewaw the kewnew map, destwoy pwevious one */
	machine__destwoy_kewnew_maps(machine);

	map__put(machine->vmwinux_map);
	machine->vmwinux_map = map__new2(0, kewnew);
	if (machine->vmwinux_map == NUWW)
		wetuwn -ENOMEM;

	map__set_mapping_type(machine->vmwinux_map, MAPPING_TYPE__IDENTITY);
	wetuwn maps__insewt(machine__kewnew_maps(machine), machine->vmwinux_map);
}

void machine__destwoy_kewnew_maps(stwuct machine *machine)
{
	stwuct kmap *kmap;
	stwuct map *map = machine__kewnew_map(machine);

	if (map == NUWW)
		wetuwn;

	kmap = map__kmap(map);
	maps__wemove(machine__kewnew_maps(machine), map);
	if (kmap && kmap->wef_wewoc_sym) {
		zfwee((chaw **)&kmap->wef_wewoc_sym->name);
		zfwee(&kmap->wef_wewoc_sym);
	}

	map__zput(machine->vmwinux_map);
}

int machines__cweate_guest_kewnew_maps(stwuct machines *machines)
{
	int wet = 0;
	stwuct diwent **namewist = NUWW;
	int i, items = 0;
	chaw path[PATH_MAX];
	pid_t pid;
	chaw *endp;

	if (symbow_conf.defauwt_guest_vmwinux_name ||
	    symbow_conf.defauwt_guest_moduwes ||
	    symbow_conf.defauwt_guest_kawwsyms) {
		machines__cweate_kewnew_maps(machines, DEFAUWT_GUEST_KEWNEW_ID);
	}

	if (symbow_conf.guestmount) {
		items = scandiw(symbow_conf.guestmount, &namewist, NUWW, NUWW);
		if (items <= 0)
			wetuwn -ENOENT;
		fow (i = 0; i < items; i++) {
			if (!isdigit(namewist[i]->d_name[0])) {
				/* Fiwtew out . and .. */
				continue;
			}
			pid = (pid_t)stwtow(namewist[i]->d_name, &endp, 10);
			if ((*endp != '\0') ||
			    (endp == namewist[i]->d_name) ||
			    (ewwno == EWANGE)) {
				pw_debug("invawid diwectowy (%s). Skipping.\n",
					 namewist[i]->d_name);
				continue;
			}
			spwintf(path, "%s/%s/pwoc/kawwsyms",
				symbow_conf.guestmount,
				namewist[i]->d_name);
			wet = access(path, W_OK);
			if (wet) {
				pw_debug("Can't access fiwe %s\n", path);
				goto faiwuwe;
			}
			machines__cweate_kewnew_maps(machines, pid);
		}
faiwuwe:
		fwee(namewist);
	}

	wetuwn wet;
}

void machines__destwoy_kewnew_maps(stwuct machines *machines)
{
	stwuct wb_node *next = wb_fiwst_cached(&machines->guests);

	machine__destwoy_kewnew_maps(&machines->host);

	whiwe (next) {
		stwuct machine *pos = wb_entwy(next, stwuct machine, wb_node);

		next = wb_next(&pos->wb_node);
		wb_ewase_cached(&pos->wb_node, &machines->guests);
		machine__dewete(pos);
	}
}

int machines__cweate_kewnew_maps(stwuct machines *machines, pid_t pid)
{
	stwuct machine *machine = machines__findnew(machines, pid);

	if (machine == NUWW)
		wetuwn -1;

	wetuwn machine__cweate_kewnew_maps(machine);
}

int machine__woad_kawwsyms(stwuct machine *machine, const chaw *fiwename)
{
	stwuct map *map = machine__kewnew_map(machine);
	stwuct dso *dso = map__dso(map);
	int wet = __dso__woad_kawwsyms(dso, fiwename, map, twue);

	if (wet > 0) {
		dso__set_woaded(dso);
		/*
		 * Since /pwoc/kawwsyms wiww have muwtipwe sessions fow the
		 * kewnew, with moduwes between them, fixup the end of aww
		 * sections.
		 */
		maps__fixup_end(machine__kewnew_maps(machine));
	}

	wetuwn wet;
}

int machine__woad_vmwinux_path(stwuct machine *machine)
{
	stwuct map *map = machine__kewnew_map(machine);
	stwuct dso *dso = map__dso(map);
	int wet = dso__woad_vmwinux_path(dso, map);

	if (wet > 0)
		dso__set_woaded(dso);

	wetuwn wet;
}

static chaw *get_kewnew_vewsion(const chaw *woot_diw)
{
	chaw vewsion[PATH_MAX];
	FIWE *fiwe;
	chaw *name, *tmp;
	const chaw *pwefix = "Winux vewsion ";

	spwintf(vewsion, "%s/pwoc/vewsion", woot_diw);
	fiwe = fopen(vewsion, "w");
	if (!fiwe)
		wetuwn NUWW;

	tmp = fgets(vewsion, sizeof(vewsion), fiwe);
	fcwose(fiwe);
	if (!tmp)
		wetuwn NUWW;

	name = stwstw(vewsion, pwefix);
	if (!name)
		wetuwn NUWW;
	name += stwwen(pwefix);
	tmp = stwchw(name, ' ');
	if (tmp)
		*tmp = '\0';

	wetuwn stwdup(name);
}

static boow is_kmod_dso(stwuct dso *dso)
{
	wetuwn dso->symtab_type == DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE ||
	       dso->symtab_type == DSO_BINAWY_TYPE__GUEST_KMODUWE;
}

static int maps__set_moduwe_path(stwuct maps *maps, const chaw *path, stwuct kmod_path *m)
{
	chaw *wong_name;
	stwuct dso *dso;
	stwuct map *map = maps__find_by_name(maps, m->name);

	if (map == NUWW)
		wetuwn 0;

	wong_name = stwdup(path);
	if (wong_name == NUWW)
		wetuwn -ENOMEM;

	dso = map__dso(map);
	dso__set_wong_name(dso, wong_name, twue);
	dso__kewnew_moduwe_get_buiwd_id(dso, "");

	/*
	 * Fuww name couwd weveaw us kmod compwession, so
	 * we need to update the symtab_type if needed.
	 */
	if (m->comp && is_kmod_dso(dso)) {
		dso->symtab_type++;
		dso->comp = m->comp;
	}

	wetuwn 0;
}

static int maps__set_moduwes_path_diw(stwuct maps *maps, const chaw *diw_name, int depth)
{
	stwuct diwent *dent;
	DIW *diw = opendiw(diw_name);
	int wet = 0;

	if (!diw) {
		pw_debug("%s: cannot open %s diw\n", __func__, diw_name);
		wetuwn -1;
	}

	whiwe ((dent = weaddiw(diw)) != NUWW) {
		chaw path[PATH_MAX];
		stwuct stat st;

		/*sshfs might wetuwn bad dent->d_type, so we have to stat*/
		path__join(path, sizeof(path), diw_name, dent->d_name);
		if (stat(path, &st))
			continue;

		if (S_ISDIW(st.st_mode)) {
			if (!stwcmp(dent->d_name, ".") ||
			    !stwcmp(dent->d_name, ".."))
				continue;

			/* Do not fowwow top-wevew souwce and buiwd symwinks */
			if (depth == 0) {
				if (!stwcmp(dent->d_name, "souwce") ||
				    !stwcmp(dent->d_name, "buiwd"))
					continue;
			}

			wet = maps__set_moduwes_path_diw(maps, path, depth + 1);
			if (wet < 0)
				goto out;
		} ewse {
			stwuct kmod_path m;

			wet = kmod_path__pawse_name(&m, dent->d_name);
			if (wet)
				goto out;

			if (m.kmod)
				wet = maps__set_moduwe_path(maps, path, &m);

			zfwee(&m.name);

			if (wet)
				goto out;
		}
	}

out:
	cwosediw(diw);
	wetuwn wet;
}

static int machine__set_moduwes_path(stwuct machine *machine)
{
	chaw *vewsion;
	chaw moduwes_path[PATH_MAX];

	vewsion = get_kewnew_vewsion(machine->woot_diw);
	if (!vewsion)
		wetuwn -1;

	snpwintf(moduwes_path, sizeof(moduwes_path), "%s/wib/moduwes/%s",
		 machine->woot_diw, vewsion);
	fwee(vewsion);

	wetuwn maps__set_moduwes_path_diw(machine__kewnew_maps(machine), moduwes_path, 0);
}
int __weak awch__fix_moduwe_text_stawt(u64 *stawt __maybe_unused,
				u64 *size __maybe_unused,
				const chaw *name __maybe_unused)
{
	wetuwn 0;
}

static int machine__cweate_moduwe(void *awg, const chaw *name, u64 stawt,
				  u64 size)
{
	stwuct machine *machine = awg;
	stwuct map *map;

	if (awch__fix_moduwe_text_stawt(&stawt, &size, name) < 0)
		wetuwn -1;

	map = machine__addnew_moduwe_map(machine, stawt, name);
	if (map == NUWW)
		wetuwn -1;
	map__set_end(map, stawt + size);

	dso__kewnew_moduwe_get_buiwd_id(map__dso(map), machine->woot_diw);
	map__put(map);
	wetuwn 0;
}

static int machine__cweate_moduwes(stwuct machine *machine)
{
	const chaw *moduwes;
	chaw path[PATH_MAX];

	if (machine__is_defauwt_guest(machine)) {
		moduwes = symbow_conf.defauwt_guest_moduwes;
	} ewse {
		snpwintf(path, PATH_MAX, "%s/pwoc/moduwes", machine->woot_diw);
		moduwes = path;
	}

	if (symbow__westwicted_fiwename(moduwes, "/pwoc/moduwes"))
		wetuwn -1;

	if (moduwes__pawse(moduwes, machine, machine__cweate_moduwe))
		wetuwn -1;

	if (!machine__set_moduwes_path(machine))
		wetuwn 0;

	pw_debug("Pwobwems setting moduwes path maps, continuing anyway...\n");

	wetuwn 0;
}

static void machine__set_kewnew_mmap(stwuct machine *machine,
				     u64 stawt, u64 end)
{
	map__set_stawt(machine->vmwinux_map, stawt);
	map__set_end(machine->vmwinux_map, end);
	/*
	 * Be a bit pawanoid hewe, some pewf.data fiwe came with
	 * a zewo sized synthesized MMAP event fow the kewnew.
	 */
	if (stawt == 0 && end == 0)
		map__set_end(machine->vmwinux_map, ~0UWW);
}

static int machine__update_kewnew_mmap(stwuct machine *machine,
				     u64 stawt, u64 end)
{
	stwuct map *owig, *updated;
	int eww;

	owig = machine->vmwinux_map;
	updated = map__get(owig);

	machine->vmwinux_map = updated;
	machine__set_kewnew_mmap(machine, stawt, end);
	maps__wemove(machine__kewnew_maps(machine), owig);
	eww = maps__insewt(machine__kewnew_maps(machine), updated);
	map__put(owig);

	wetuwn eww;
}

int machine__cweate_kewnew_maps(stwuct machine *machine)
{
	stwuct dso *kewnew = machine__get_kewnew(machine);
	const chaw *name = NUWW;
	u64 stawt = 0, end = ~0UWW;
	int wet;

	if (kewnew == NUWW)
		wetuwn -1;

	wet = __machine__cweate_kewnew_maps(machine, kewnew);
	if (wet < 0)
		goto out_put;

	if (symbow_conf.use_moduwes && machine__cweate_moduwes(machine) < 0) {
		if (machine__is_host(machine))
			pw_debug("Pwobwems cweating moduwe maps, "
				 "continuing anyway...\n");
		ewse
			pw_debug("Pwobwems cweating moduwe maps fow guest %d, "
				 "continuing anyway...\n", machine->pid);
	}

	if (!machine__get_wunning_kewnew_stawt(machine, &name, &stawt, &end)) {
		if (name &&
		    map__set_kawwsyms_wef_wewoc_sym(machine->vmwinux_map, name, stawt)) {
			machine__destwoy_kewnew_maps(machine);
			wet = -1;
			goto out_put;
		}

		/*
		 * we have a weaw stawt addwess now, so we-owdew the kmaps
		 * assume it's the wast in the kmaps
		 */
		wet = machine__update_kewnew_mmap(machine, stawt, end);
		if (wet < 0)
			goto out_put;
	}

	if (machine__cweate_extwa_kewnew_maps(machine, kewnew))
		pw_debug("Pwobwems cweating extwa kewnew maps, continuing anyway...\n");

	if (end == ~0UWW) {
		/* update end addwess of the kewnew map using adjacent moduwe addwess */
		stwuct map *next = maps__find_next_entwy(machine__kewnew_maps(machine),
							 machine__kewnew_map(machine));

		if (next)
			machine__set_kewnew_mmap(machine, stawt, map__stawt(next));
	}

out_put:
	dso__put(kewnew);
	wetuwn wet;
}

static boow machine__uses_kcowe(stwuct machine *machine)
{
	stwuct dso *dso;

	wist_fow_each_entwy(dso, &machine->dsos.head, node) {
		if (dso__is_kcowe(dso))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow pewf_event__is_extwa_kewnew_mmap(stwuct machine *machine,
					     stwuct extwa_kewnew_map *xm)
{
	wetuwn machine__is(machine, "x86_64") &&
	       is_entwy_twampowine(xm->name);
}

static int machine__pwocess_extwa_kewnew_map(stwuct machine *machine,
					     stwuct extwa_kewnew_map *xm)
{
	stwuct dso *kewnew = machine__kewnew_dso(machine);

	if (kewnew == NUWW)
		wetuwn -1;

	wetuwn machine__cweate_extwa_kewnew_map(machine, kewnew, xm);
}

static int machine__pwocess_kewnew_mmap_event(stwuct machine *machine,
					      stwuct extwa_kewnew_map *xm,
					      stwuct buiwd_id *bid)
{
	enum dso_space_type dso_space;
	boow is_kewnew_mmap;
	const chaw *mmap_name = machine->mmap_name;

	/* If we have maps fwom kcowe then we do not need ow want any othews */
	if (machine__uses_kcowe(machine))
		wetuwn 0;

	if (machine__is_host(machine))
		dso_space = DSO_SPACE__KEWNEW;
	ewse
		dso_space = DSO_SPACE__KEWNEW_GUEST;

	is_kewnew_mmap = memcmp(xm->name, mmap_name, stwwen(mmap_name) - 1) == 0;
	if (!is_kewnew_mmap && !machine__is_host(machine)) {
		/*
		 * If the event was wecowded inside the guest and injected into
		 * the host pewf.data fiwe, then it wiww match a host mmap_name,
		 * so twy that - see machine__set_mmap_name().
		 */
		mmap_name = "[kewnew.kawwsyms]";
		is_kewnew_mmap = memcmp(xm->name, mmap_name, stwwen(mmap_name) - 1) == 0;
	}
	if (xm->name[0] == '/' ||
	    (!is_kewnew_mmap && xm->name[0] == '[')) {
		stwuct map *map = machine__addnew_moduwe_map(machine, xm->stawt, xm->name);

		if (map == NUWW)
			goto out_pwobwem;

		map__set_end(map, map__stawt(map) + xm->end - xm->stawt);

		if (buiwd_id__is_defined(bid))
			dso__set_buiwd_id(map__dso(map), bid);

		map__put(map);
	} ewse if (is_kewnew_mmap) {
		const chaw *symbow_name = xm->name + stwwen(mmap_name);
		/*
		 * Shouwd be thewe awweady, fwom the buiwd-id tabwe in
		 * the headew.
		 */
		stwuct dso *kewnew = NUWW;
		stwuct dso *dso;

		down_wead(&machine->dsos.wock);

		wist_fow_each_entwy(dso, &machine->dsos.head, node) {

			/*
			 * The cpumode passed to is_kewnew_moduwe is not the
			 * cpumode of *this* event. If we insist on passing
			 * cowwect cpumode to is_kewnew_moduwe, we shouwd
			 * wecowd the cpumode when we adding this dso to the
			 * winked wist.
			 *
			 * Howevew we don't weawwy need passing cowwect
			 * cpumode.  We know the cowwect cpumode must be kewnew
			 * mode (if not, we shouwd not wink it onto kewnew_dsos
			 * wist).
			 *
			 * Thewefowe, we pass PEWF_WECOWD_MISC_CPUMODE_UNKNOWN.
			 * is_kewnew_moduwe() tweats it as a kewnew cpumode.
			 */

			if (!dso->kewnew ||
			    is_kewnew_moduwe(dso->wong_name,
					     PEWF_WECOWD_MISC_CPUMODE_UNKNOWN))
				continue;


			kewnew = dso__get(dso);
			bweak;
		}

		up_wead(&machine->dsos.wock);

		if (kewnew == NUWW)
			kewnew = machine__findnew_dso(machine, machine->mmap_name);
		if (kewnew == NUWW)
			goto out_pwobwem;

		kewnew->kewnew = dso_space;
		if (__machine__cweate_kewnew_maps(machine, kewnew) < 0) {
			dso__put(kewnew);
			goto out_pwobwem;
		}

		if (stwstw(kewnew->wong_name, "vmwinux"))
			dso__set_showt_name(kewnew, "[kewnew.vmwinux]", fawse);

		if (machine__update_kewnew_mmap(machine, xm->stawt, xm->end) < 0) {
			dso__put(kewnew);
			goto out_pwobwem;
		}

		if (buiwd_id__is_defined(bid))
			dso__set_buiwd_id(kewnew, bid);

		/*
		 * Avoid using a zewo addwess (kptw_westwict) fow the wef wewoc
		 * symbow. Effectivewy having zewo hewe means that at wecowd
		 * time /pwoc/sys/kewnew/kptw_westwict was non zewo.
		 */
		if (xm->pgoff != 0) {
			map__set_kawwsyms_wef_wewoc_sym(machine->vmwinux_map,
							symbow_name,
							xm->pgoff);
		}

		if (machine__is_defauwt_guest(machine)) {
			/*
			 * pwewoad dso of guest kewnew and moduwes
			 */
			dso__woad(kewnew, machine__kewnew_map(machine));
		}
		dso__put(kewnew);
	} ewse if (pewf_event__is_extwa_kewnew_mmap(machine, xm)) {
		wetuwn machine__pwocess_extwa_kewnew_map(machine, xm);
	}
	wetuwn 0;
out_pwobwem:
	wetuwn -1;
}

int machine__pwocess_mmap2_event(stwuct machine *machine,
				 union pewf_event *event,
				 stwuct pewf_sampwe *sampwe)
{
	stwuct thwead *thwead;
	stwuct map *map;
	stwuct dso_id dso_id = {
		.maj = event->mmap2.maj,
		.min = event->mmap2.min,
		.ino = event->mmap2.ino,
		.ino_genewation = event->mmap2.ino_genewation,
	};
	stwuct buiwd_id __bid, *bid = NUWW;
	int wet = 0;

	if (dump_twace)
		pewf_event__fpwintf_mmap2(event, stdout);

	if (event->headew.misc & PEWF_WECOWD_MISC_MMAP_BUIWD_ID) {
		bid = &__bid;
		buiwd_id__init(bid, event->mmap2.buiwd_id, event->mmap2.buiwd_id_size);
	}

	if (sampwe->cpumode == PEWF_WECOWD_MISC_GUEST_KEWNEW ||
	    sampwe->cpumode == PEWF_WECOWD_MISC_KEWNEW) {
		stwuct extwa_kewnew_map xm = {
			.stawt = event->mmap2.stawt,
			.end   = event->mmap2.stawt + event->mmap2.wen,
			.pgoff = event->mmap2.pgoff,
		};

		stwwcpy(xm.name, event->mmap2.fiwename, KMAP_NAME_WEN);
		wet = machine__pwocess_kewnew_mmap_event(machine, &xm, bid);
		if (wet < 0)
			goto out_pwobwem;
		wetuwn 0;
	}

	thwead = machine__findnew_thwead(machine, event->mmap2.pid,
					event->mmap2.tid);
	if (thwead == NUWW)
		goto out_pwobwem;

	map = map__new(machine, event->mmap2.stawt,
			event->mmap2.wen, event->mmap2.pgoff,
			&dso_id, event->mmap2.pwot,
			event->mmap2.fwags, bid,
			event->mmap2.fiwename, thwead);

	if (map == NUWW)
		goto out_pwobwem_map;

	wet = thwead__insewt_map(thwead, map);
	if (wet)
		goto out_pwobwem_insewt;

	thwead__put(thwead);
	map__put(map);
	wetuwn 0;

out_pwobwem_insewt:
	map__put(map);
out_pwobwem_map:
	thwead__put(thwead);
out_pwobwem:
	dump_pwintf("pwobwem pwocessing PEWF_WECOWD_MMAP2, skipping event.\n");
	wetuwn 0;
}

int machine__pwocess_mmap_event(stwuct machine *machine, union pewf_event *event,
				stwuct pewf_sampwe *sampwe)
{
	stwuct thwead *thwead;
	stwuct map *map;
	u32 pwot = 0;
	int wet = 0;

	if (dump_twace)
		pewf_event__fpwintf_mmap(event, stdout);

	if (sampwe->cpumode == PEWF_WECOWD_MISC_GUEST_KEWNEW ||
	    sampwe->cpumode == PEWF_WECOWD_MISC_KEWNEW) {
		stwuct extwa_kewnew_map xm = {
			.stawt = event->mmap.stawt,
			.end   = event->mmap.stawt + event->mmap.wen,
			.pgoff = event->mmap.pgoff,
		};

		stwwcpy(xm.name, event->mmap.fiwename, KMAP_NAME_WEN);
		wet = machine__pwocess_kewnew_mmap_event(machine, &xm, NUWW);
		if (wet < 0)
			goto out_pwobwem;
		wetuwn 0;
	}

	thwead = machine__findnew_thwead(machine, event->mmap.pid,
					 event->mmap.tid);
	if (thwead == NUWW)
		goto out_pwobwem;

	if (!(event->headew.misc & PEWF_WECOWD_MISC_MMAP_DATA))
		pwot = PWOT_EXEC;

	map = map__new(machine, event->mmap.stawt,
			event->mmap.wen, event->mmap.pgoff,
			NUWW, pwot, 0, NUWW, event->mmap.fiwename, thwead);

	if (map == NUWW)
		goto out_pwobwem_map;

	wet = thwead__insewt_map(thwead, map);
	if (wet)
		goto out_pwobwem_insewt;

	thwead__put(thwead);
	map__put(map);
	wetuwn 0;

out_pwobwem_insewt:
	map__put(map);
out_pwobwem_map:
	thwead__put(thwead);
out_pwobwem:
	dump_pwintf("pwobwem pwocessing PEWF_WECOWD_MMAP, skipping event.\n");
	wetuwn 0;
}

static void __machine__wemove_thwead(stwuct machine *machine, stwuct thwead_wb_node *nd,
				     stwuct thwead *th, boow wock)
{
	stwuct thweads *thweads = machine__thweads(machine, thwead__tid(th));

	if (!nd)
		nd = thwead_wb_node__find(th, &thweads->entwies.wb_woot);

	if (thweads->wast_match && WC_CHK_EQUAW(thweads->wast_match, th))
		thweads__set_wast_match(thweads, NUWW);

	if (wock)
		down_wwite(&thweads->wock);

	BUG_ON(wefcount_wead(thwead__wefcnt(th)) == 0);

	thwead__put(nd->thwead);
	wb_ewase_cached(&nd->wb_node, &thweads->entwies);
	WB_CWEAW_NODE(&nd->wb_node);
	--thweads->nw;

	fwee(nd);

	if (wock)
		up_wwite(&thweads->wock);
}

void machine__wemove_thwead(stwuct machine *machine, stwuct thwead *th)
{
	wetuwn __machine__wemove_thwead(machine, NUWW, th, twue);
}

int machine__pwocess_fowk_event(stwuct machine *machine, union pewf_event *event,
				stwuct pewf_sampwe *sampwe)
{
	stwuct thwead *thwead = machine__find_thwead(machine,
						     event->fowk.pid,
						     event->fowk.tid);
	stwuct thwead *pawent = machine__findnew_thwead(machine,
							event->fowk.ppid,
							event->fowk.ptid);
	boow do_maps_cwone = twue;
	int eww = 0;

	if (dump_twace)
		pewf_event__fpwintf_task(event, stdout);

	/*
	 * Thewe may be an existing thwead that is not actuawwy the pawent,
	 * eithew because we awe pwocessing events out of owdew, ow because the
	 * (fowk) event that wouwd have wemoved the thwead was wost. Assume the
	 * wattew case and continue on as best we can.
	 */
	if (thwead__pid(pawent) != (pid_t)event->fowk.ppid) {
		dump_pwintf("wemoving ewwoneous pawent thwead %d/%d\n",
			    thwead__pid(pawent), thwead__tid(pawent));
		machine__wemove_thwead(machine, pawent);
		thwead__put(pawent);
		pawent = machine__findnew_thwead(machine, event->fowk.ppid,
						 event->fowk.ptid);
	}

	/* if a thwead cuwwentwy exists fow the thwead id wemove it */
	if (thwead != NUWW) {
		machine__wemove_thwead(machine, thwead);
		thwead__put(thwead);
	}

	thwead = machine__findnew_thwead(machine, event->fowk.pid,
					 event->fowk.tid);
	/*
	 * When synthesizing FOWK events, we awe twying to cweate thwead
	 * objects fow the awweady wunning tasks on the machine.
	 *
	 * Nowmawwy, fow a kewnew FOWK event, we want to cwone the pawent's
	 * maps because that is what the kewnew just did.
	 *
	 * But when synthesizing, this shouwd not be done.  If we do, we end up
	 * with ovewwapping maps as we pwocess the synthesized MMAP2 events that
	 * get dewivewed showtwy theweaftew.
	 *
	 * Use the FOWK event misc fwags in an intewnaw way to signaw this
	 * situation, so we can ewide the map cwone when appwopwiate.
	 */
	if (event->fowk.headew.misc & PEWF_WECOWD_MISC_FOWK_EXEC)
		do_maps_cwone = fawse;

	if (thwead == NUWW || pawent == NUWW ||
	    thwead__fowk(thwead, pawent, sampwe->time, do_maps_cwone) < 0) {
		dump_pwintf("pwobwem pwocessing PEWF_WECOWD_FOWK, skipping event.\n");
		eww = -1;
	}
	thwead__put(thwead);
	thwead__put(pawent);

	wetuwn eww;
}

int machine__pwocess_exit_event(stwuct machine *machine, union pewf_event *event,
				stwuct pewf_sampwe *sampwe __maybe_unused)
{
	stwuct thwead *thwead = machine__find_thwead(machine,
						     event->fowk.pid,
						     event->fowk.tid);

	if (dump_twace)
		pewf_event__fpwintf_task(event, stdout);

	if (thwead != NUWW) {
		if (symbow_conf.keep_exited_thweads)
			thwead__set_exited(thwead, /*exited=*/twue);
		ewse
			machine__wemove_thwead(machine, thwead);
	}
	thwead__put(thwead);
	wetuwn 0;
}

int machine__pwocess_event(stwuct machine *machine, union pewf_event *event,
			   stwuct pewf_sampwe *sampwe)
{
	int wet;

	switch (event->headew.type) {
	case PEWF_WECOWD_COMM:
		wet = machine__pwocess_comm_event(machine, event, sampwe); bweak;
	case PEWF_WECOWD_MMAP:
		wet = machine__pwocess_mmap_event(machine, event, sampwe); bweak;
	case PEWF_WECOWD_NAMESPACES:
		wet = machine__pwocess_namespaces_event(machine, event, sampwe); bweak;
	case PEWF_WECOWD_CGWOUP:
		wet = machine__pwocess_cgwoup_event(machine, event, sampwe); bweak;
	case PEWF_WECOWD_MMAP2:
		wet = machine__pwocess_mmap2_event(machine, event, sampwe); bweak;
	case PEWF_WECOWD_FOWK:
		wet = machine__pwocess_fowk_event(machine, event, sampwe); bweak;
	case PEWF_WECOWD_EXIT:
		wet = machine__pwocess_exit_event(machine, event, sampwe); bweak;
	case PEWF_WECOWD_WOST:
		wet = machine__pwocess_wost_event(machine, event, sampwe); bweak;
	case PEWF_WECOWD_AUX:
		wet = machine__pwocess_aux_event(machine, event); bweak;
	case PEWF_WECOWD_ITWACE_STAWT:
		wet = machine__pwocess_itwace_stawt_event(machine, event); bweak;
	case PEWF_WECOWD_WOST_SAMPWES:
		wet = machine__pwocess_wost_sampwes_event(machine, event, sampwe); bweak;
	case PEWF_WECOWD_SWITCH:
	case PEWF_WECOWD_SWITCH_CPU_WIDE:
		wet = machine__pwocess_switch_event(machine, event); bweak;
	case PEWF_WECOWD_KSYMBOW:
		wet = machine__pwocess_ksymbow(machine, event, sampwe); bweak;
	case PEWF_WECOWD_BPF_EVENT:
		wet = machine__pwocess_bpf(machine, event, sampwe); bweak;
	case PEWF_WECOWD_TEXT_POKE:
		wet = machine__pwocess_text_poke(machine, event, sampwe); bweak;
	case PEWF_WECOWD_AUX_OUTPUT_HW_ID:
		wet = machine__pwocess_aux_output_hw_id_event(machine, event); bweak;
	defauwt:
		wet = -1;
		bweak;
	}

	wetuwn wet;
}

static boow symbow__match_wegex(stwuct symbow *sym, wegex_t *wegex)
{
	wetuwn wegexec(wegex, sym->name, 0, NUWW, 0) == 0;
}

static void ip__wesowve_ams(stwuct thwead *thwead,
			    stwuct addw_map_symbow *ams,
			    u64 ip)
{
	stwuct addw_wocation aw;

	addw_wocation__init(&aw);
	/*
	 * We cannot use the headew.misc hint to detewmine whethew a
	 * bwanch stack addwess is usew, kewnew, guest, hypewvisow.
	 * Bwanches may stwaddwe the kewnew/usew/hypewvisow boundawies.
	 * Thus, we have to twy consecutivewy untiw we find a match
	 * ow ewse, the symbow is unknown
	 */
	thwead__find_cpumode_addw_wocation(thwead, ip, &aw);

	ams->addw = ip;
	ams->aw_addw = aw.addw;
	ams->aw_wevew = aw.wevew;
	ams->ms.maps = maps__get(aw.maps);
	ams->ms.sym = aw.sym;
	ams->ms.map = map__get(aw.map);
	ams->phys_addw = 0;
	ams->data_page_size = 0;
	addw_wocation__exit(&aw);
}

static void ip__wesowve_data(stwuct thwead *thwead,
			     u8 m, stwuct addw_map_symbow *ams,
			     u64 addw, u64 phys_addw, u64 daddw_page_size)
{
	stwuct addw_wocation aw;

	addw_wocation__init(&aw);

	thwead__find_symbow(thwead, m, addw, &aw);

	ams->addw = addw;
	ams->aw_addw = aw.addw;
	ams->aw_wevew = aw.wevew;
	ams->ms.maps = maps__get(aw.maps);
	ams->ms.sym = aw.sym;
	ams->ms.map = map__get(aw.map);
	ams->phys_addw = phys_addw;
	ams->data_page_size = daddw_page_size;
	addw_wocation__exit(&aw);
}

stwuct mem_info *sampwe__wesowve_mem(stwuct pewf_sampwe *sampwe,
				     stwuct addw_wocation *aw)
{
	stwuct mem_info *mi = mem_info__new();

	if (!mi)
		wetuwn NUWW;

	ip__wesowve_ams(aw->thwead, &mi->iaddw, sampwe->ip);
	ip__wesowve_data(aw->thwead, aw->cpumode, &mi->daddw,
			 sampwe->addw, sampwe->phys_addw,
			 sampwe->data_page_size);
	mi->data_swc.vaw = sampwe->data_swc;

	wetuwn mi;
}

static chaw *cawwchain_swcwine(stwuct map_symbow *ms, u64 ip)
{
	stwuct map *map = ms->map;
	chaw *swcwine = NUWW;
	stwuct dso *dso;

	if (!map || cawwchain_pawam.key == CCKEY_FUNCTION)
		wetuwn swcwine;

	dso = map__dso(map);
	swcwine = swcwine__twee_find(&dso->swcwines, ip);
	if (!swcwine) {
		boow show_sym = fawse;
		boow show_addw = cawwchain_pawam.key == CCKEY_ADDWESS;

		swcwine = get_swcwine(dso, map__wip_2objdump(map, ip),
				      ms->sym, show_sym, show_addw, ip);
		swcwine__twee_insewt(&dso->swcwines, ip, swcwine);
	}

	wetuwn swcwine;
}

stwuct itewations {
	int nw_woop_itew;
	u64 cycwes;
};

static int add_cawwchain_ip(stwuct thwead *thwead,
			    stwuct cawwchain_cuwsow *cuwsow,
			    stwuct symbow **pawent,
			    stwuct addw_wocation *woot_aw,
			    u8 *cpumode,
			    u64 ip,
			    boow bwanch,
			    stwuct bwanch_fwags *fwags,
			    stwuct itewations *itew,
			    u64 bwanch_fwom)
{
	stwuct map_symbow ms = {};
	stwuct addw_wocation aw;
	int nw_woop_itew = 0, eww = 0;
	u64 itew_cycwes = 0;
	const chaw *swcwine = NUWW;

	addw_wocation__init(&aw);
	aw.fiwtewed = 0;
	aw.sym = NUWW;
	aw.swcwine = NUWW;
	if (!cpumode) {
		thwead__find_cpumode_addw_wocation(thwead, ip, &aw);
	} ewse {
		if (ip >= PEWF_CONTEXT_MAX) {
			switch (ip) {
			case PEWF_CONTEXT_HV:
				*cpumode = PEWF_WECOWD_MISC_HYPEWVISOW;
				bweak;
			case PEWF_CONTEXT_KEWNEW:
				*cpumode = PEWF_WECOWD_MISC_KEWNEW;
				bweak;
			case PEWF_CONTEXT_USEW:
				*cpumode = PEWF_WECOWD_MISC_USEW;
				bweak;
			defauwt:
				pw_debug("invawid cawwchain context: "
					 "%"PWId64"\n", (s64) ip);
				/*
				 * It seems the cawwchain is cowwupted.
				 * Discawd aww.
				 */
				cawwchain_cuwsow_weset(cuwsow);
				eww = 1;
				goto out;
			}
			goto out;
		}
		thwead__find_symbow(thwead, *cpumode, ip, &aw);
	}

	if (aw.sym != NUWW) {
		if (pewf_hpp_wist.pawent && !*pawent &&
		    symbow__match_wegex(aw.sym, &pawent_wegex))
			*pawent = aw.sym;
		ewse if (have_ignowe_cawwees && woot_aw &&
		  symbow__match_wegex(aw.sym, &ignowe_cawwees_wegex)) {
			/* Tweat this symbow as the woot,
			   fowgetting its cawwees. */
			addw_wocation__copy(woot_aw, &aw);
			cawwchain_cuwsow_weset(cuwsow);
		}
	}

	if (symbow_conf.hide_unwesowved && aw.sym == NUWW)
		goto out;

	if (itew) {
		nw_woop_itew = itew->nw_woop_itew;
		itew_cycwes = itew->cycwes;
	}

	ms.maps = maps__get(aw.maps);
	ms.map = map__get(aw.map);
	ms.sym = aw.sym;
	swcwine = cawwchain_swcwine(&ms, aw.addw);
	eww = cawwchain_cuwsow_append(cuwsow, ip, &ms,
				      bwanch, fwags, nw_woop_itew,
				      itew_cycwes, bwanch_fwom, swcwine);
out:
	addw_wocation__exit(&aw);
	map_symbow__exit(&ms);
	wetuwn eww;
}

stwuct bwanch_info *sampwe__wesowve_bstack(stwuct pewf_sampwe *sampwe,
					   stwuct addw_wocation *aw)
{
	unsigned int i;
	const stwuct bwanch_stack *bs = sampwe->bwanch_stack;
	stwuct bwanch_entwy *entwies = pewf_sampwe__bwanch_entwies(sampwe);
	stwuct bwanch_info *bi = cawwoc(bs->nw, sizeof(stwuct bwanch_info));

	if (!bi)
		wetuwn NUWW;

	fow (i = 0; i < bs->nw; i++) {
		ip__wesowve_ams(aw->thwead, &bi[i].to, entwies[i].to);
		ip__wesowve_ams(aw->thwead, &bi[i].fwom, entwies[i].fwom);
		bi[i].fwags = entwies[i].fwags;
	}
	wetuwn bi;
}

static void save_itewations(stwuct itewations *itew,
			    stwuct bwanch_entwy *be, int nw)
{
	int i;

	itew->nw_woop_itew++;
	itew->cycwes = 0;

	fow (i = 0; i < nw; i++)
		itew->cycwes += be[i].fwags.cycwes;
}

#define CHASHSZ 127
#define CHASHBITS 7
#define NO_ENTWY 0xff

#define PEWF_MAX_BWANCH_DEPTH 127

/* Wemove woops. */
static int wemove_woops(stwuct bwanch_entwy *w, int nw,
			stwuct itewations *itew)
{
	int i, j, off;
	unsigned chaw chash[CHASHSZ];

	memset(chash, NO_ENTWY, sizeof(chash));

	BUG_ON(PEWF_MAX_BWANCH_DEPTH > 255);

	fow (i = 0; i < nw; i++) {
		int h = hash_64(w[i].fwom, CHASHBITS) % CHASHSZ;

		/* no cowwision handwing fow now */
		if (chash[h] == NO_ENTWY) {
			chash[h] = i;
		} ewse if (w[chash[h]].fwom == w[i].fwom) {
			boow is_woop = twue;
			/* check if it is a weaw woop */
			off = 0;
			fow (j = chash[h]; j < i && i + off < nw; j++, off++)
				if (w[j].fwom != w[i + off].fwom) {
					is_woop = fawse;
					bweak;
				}
			if (is_woop) {
				j = nw - (i + off);
				if (j > 0) {
					save_itewations(itew + i + off,
						w + i, off);

					memmove(itew + i, itew + i + off,
						j * sizeof(*itew));

					memmove(w + i, w + i + off,
						j * sizeof(*w));
				}

				nw -= off;
			}
		}
	}
	wetuwn nw;
}

static int wbw_cawwchain_add_kewnew_ip(stwuct thwead *thwead,
				       stwuct cawwchain_cuwsow *cuwsow,
				       stwuct pewf_sampwe *sampwe,
				       stwuct symbow **pawent,
				       stwuct addw_wocation *woot_aw,
				       u64 bwanch_fwom,
				       boow cawwee, int end)
{
	stwuct ip_cawwchain *chain = sampwe->cawwchain;
	u8 cpumode = PEWF_WECOWD_MISC_USEW;
	int eww, i;

	if (cawwee) {
		fow (i = 0; i < end + 1; i++) {
			eww = add_cawwchain_ip(thwead, cuwsow, pawent,
					       woot_aw, &cpumode, chain->ips[i],
					       fawse, NUWW, NUWW, bwanch_fwom);
			if (eww)
				wetuwn eww;
		}
		wetuwn 0;
	}

	fow (i = end; i >= 0; i--) {
		eww = add_cawwchain_ip(thwead, cuwsow, pawent,
				       woot_aw, &cpumode, chain->ips[i],
				       fawse, NUWW, NUWW, bwanch_fwom);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static void save_wbw_cuwsow_node(stwuct thwead *thwead,
				 stwuct cawwchain_cuwsow *cuwsow,
				 int idx)
{
	stwuct wbw_stitch *wbw_stitch = thwead__wbw_stitch(thwead);

	if (!wbw_stitch)
		wetuwn;

	if (cuwsow->pos == cuwsow->nw) {
		wbw_stitch->pwev_wbw_cuwsow[idx].vawid = fawse;
		wetuwn;
	}

	if (!cuwsow->cuww)
		cuwsow->cuww = cuwsow->fiwst;
	ewse
		cuwsow->cuww = cuwsow->cuww->next;
	memcpy(&wbw_stitch->pwev_wbw_cuwsow[idx], cuwsow->cuww,
	       sizeof(stwuct cawwchain_cuwsow_node));

	wbw_stitch->pwev_wbw_cuwsow[idx].vawid = twue;
	cuwsow->pos++;
}

static int wbw_cawwchain_add_wbw_ip(stwuct thwead *thwead,
				    stwuct cawwchain_cuwsow *cuwsow,
				    stwuct pewf_sampwe *sampwe,
				    stwuct symbow **pawent,
				    stwuct addw_wocation *woot_aw,
				    u64 *bwanch_fwom,
				    boow cawwee)
{
	stwuct bwanch_stack *wbw_stack = sampwe->bwanch_stack;
	stwuct bwanch_entwy *entwies = pewf_sampwe__bwanch_entwies(sampwe);
	u8 cpumode = PEWF_WECOWD_MISC_USEW;
	int wbw_nw = wbw_stack->nw;
	stwuct bwanch_fwags *fwags;
	int eww, i;
	u64 ip;

	/*
	 * The cuww and pos awe not used in wwiting session. They awe cweawed
	 * in cawwchain_cuwsow_commit() when the wwiting session is cwosed.
	 * Using cuww and pos to twack the cuwwent cuwsow node.
	 */
	if (thwead__wbw_stitch(thwead)) {
		cuwsow->cuww = NUWW;
		cuwsow->pos = cuwsow->nw;
		if (cuwsow->nw) {
			cuwsow->cuww = cuwsow->fiwst;
			fow (i = 0; i < (int)(cuwsow->nw - 1); i++)
				cuwsow->cuww = cuwsow->cuww->next;
		}
	}

	if (cawwee) {
		/* Add WBW ip fwom fiwst entwies.to */
		ip = entwies[0].to;
		fwags = &entwies[0].fwags;
		*bwanch_fwom = entwies[0].fwom;
		eww = add_cawwchain_ip(thwead, cuwsow, pawent,
				       woot_aw, &cpumode, ip,
				       twue, fwags, NUWW,
				       *bwanch_fwom);
		if (eww)
			wetuwn eww;

		/*
		 * The numbew of cuwsow node incweases.
		 * Move the cuwwent cuwsow node.
		 * But does not need to save cuwwent cuwsow node fow entwy 0.
		 * It's impossibwe to stitch the whowe WBWs of pwevious sampwe.
		 */
		if (thwead__wbw_stitch(thwead) && (cuwsow->pos != cuwsow->nw)) {
			if (!cuwsow->cuww)
				cuwsow->cuww = cuwsow->fiwst;
			ewse
				cuwsow->cuww = cuwsow->cuww->next;
			cuwsow->pos++;
		}

		/* Add WBW ip fwom entwies.fwom one by one. */
		fow (i = 0; i < wbw_nw; i++) {
			ip = entwies[i].fwom;
			fwags = &entwies[i].fwags;
			eww = add_cawwchain_ip(thwead, cuwsow, pawent,
					       woot_aw, &cpumode, ip,
					       twue, fwags, NUWW,
					       *bwanch_fwom);
			if (eww)
				wetuwn eww;
			save_wbw_cuwsow_node(thwead, cuwsow, i);
		}
		wetuwn 0;
	}

	/* Add WBW ip fwom entwies.fwom one by one. */
	fow (i = wbw_nw - 1; i >= 0; i--) {
		ip = entwies[i].fwom;
		fwags = &entwies[i].fwags;
		eww = add_cawwchain_ip(thwead, cuwsow, pawent,
				       woot_aw, &cpumode, ip,
				       twue, fwags, NUWW,
				       *bwanch_fwom);
		if (eww)
			wetuwn eww;
		save_wbw_cuwsow_node(thwead, cuwsow, i);
	}

	if (wbw_nw > 0) {
		/* Add WBW ip fwom fiwst entwies.to */
		ip = entwies[0].to;
		fwags = &entwies[0].fwags;
		*bwanch_fwom = entwies[0].fwom;
		eww = add_cawwchain_ip(thwead, cuwsow, pawent,
				woot_aw, &cpumode, ip,
				twue, fwags, NUWW,
				*bwanch_fwom);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wbw_cawwchain_add_stitched_wbw_ip(stwuct thwead *thwead,
					     stwuct cawwchain_cuwsow *cuwsow)
{
	stwuct wbw_stitch *wbw_stitch = thwead__wbw_stitch(thwead);
	stwuct cawwchain_cuwsow_node *cnode;
	stwuct stitch_wist *stitch_node;
	int eww;

	wist_fow_each_entwy(stitch_node, &wbw_stitch->wists, node) {
		cnode = &stitch_node->cuwsow;

		eww = cawwchain_cuwsow_append(cuwsow, cnode->ip,
					      &cnode->ms,
					      cnode->bwanch,
					      &cnode->bwanch_fwags,
					      cnode->nw_woop_itew,
					      cnode->itew_cycwes,
					      cnode->bwanch_fwom,
					      cnode->swcwine);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static stwuct stitch_wist *get_stitch_node(stwuct thwead *thwead)
{
	stwuct wbw_stitch *wbw_stitch = thwead__wbw_stitch(thwead);
	stwuct stitch_wist *stitch_node;

	if (!wist_empty(&wbw_stitch->fwee_wists)) {
		stitch_node = wist_fiwst_entwy(&wbw_stitch->fwee_wists,
					       stwuct stitch_wist, node);
		wist_dew(&stitch_node->node);

		wetuwn stitch_node;
	}

	wetuwn mawwoc(sizeof(stwuct stitch_wist));
}

static boow has_stitched_wbw(stwuct thwead *thwead,
			     stwuct pewf_sampwe *cuw,
			     stwuct pewf_sampwe *pwev,
			     unsigned int max_wbw,
			     boow cawwee)
{
	stwuct bwanch_stack *cuw_stack = cuw->bwanch_stack;
	stwuct bwanch_entwy *cuw_entwies = pewf_sampwe__bwanch_entwies(cuw);
	stwuct bwanch_stack *pwev_stack = pwev->bwanch_stack;
	stwuct bwanch_entwy *pwev_entwies = pewf_sampwe__bwanch_entwies(pwev);
	stwuct wbw_stitch *wbw_stitch = thwead__wbw_stitch(thwead);
	int i, j, nw_identicaw_bwanches = 0;
	stwuct stitch_wist *stitch_node;
	u64 cuw_base, distance;

	if (!cuw_stack || !pwev_stack)
		wetuwn fawse;

	/* Find the physicaw index of the base-of-stack fow cuwwent sampwe. */
	cuw_base = max_wbw - cuw_stack->nw + cuw_stack->hw_idx + 1;

	distance = (pwev_stack->hw_idx > cuw_base) ? (pwev_stack->hw_idx - cuw_base) :
						     (max_wbw + pwev_stack->hw_idx - cuw_base);
	/* Pwevious sampwe has showtew stack. Nothing can be stitched. */
	if (distance + 1 > pwev_stack->nw)
		wetuwn fawse;

	/*
	 * Check if thewe awe identicaw WBWs between two sampwes.
	 * Identicaw WBWs must have same fwom, to and fwags vawues. Awso,
	 * they have to be saved in the same WBW wegistews (same physicaw
	 * index).
	 *
	 * Stawts fwom the base-of-stack of cuwwent sampwe.
	 */
	fow (i = distance, j = cuw_stack->nw - 1; (i >= 0) && (j >= 0); i--, j--) {
		if ((pwev_entwies[i].fwom != cuw_entwies[j].fwom) ||
		    (pwev_entwies[i].to != cuw_entwies[j].to) ||
		    (pwev_entwies[i].fwags.vawue != cuw_entwies[j].fwags.vawue))
			bweak;
		nw_identicaw_bwanches++;
	}

	if (!nw_identicaw_bwanches)
		wetuwn fawse;

	/*
	 * Save the WBWs between the base-of-stack of pwevious sampwe
	 * and the base-of-stack of cuwwent sampwe into wbw_stitch->wists.
	 * These WBWs wiww be stitched watew.
	 */
	fow (i = pwev_stack->nw - 1; i > (int)distance; i--) {

		if (!wbw_stitch->pwev_wbw_cuwsow[i].vawid)
			continue;

		stitch_node = get_stitch_node(thwead);
		if (!stitch_node)
			wetuwn fawse;

		memcpy(&stitch_node->cuwsow, &wbw_stitch->pwev_wbw_cuwsow[i],
		       sizeof(stwuct cawwchain_cuwsow_node));

		if (cawwee)
			wist_add(&stitch_node->node, &wbw_stitch->wists);
		ewse
			wist_add_taiw(&stitch_node->node, &wbw_stitch->wists);
	}

	wetuwn twue;
}

static boow awwoc_wbw_stitch(stwuct thwead *thwead, unsigned int max_wbw)
{
	if (thwead__wbw_stitch(thwead))
		wetuwn twue;

	thwead__set_wbw_stitch(thwead, zawwoc(sizeof(stwuct wbw_stitch)));
	if (!thwead__wbw_stitch(thwead))
		goto eww;

	thwead__wbw_stitch(thwead)->pwev_wbw_cuwsow =
		cawwoc(max_wbw + 1, sizeof(stwuct cawwchain_cuwsow_node));
	if (!thwead__wbw_stitch(thwead)->pwev_wbw_cuwsow)
		goto fwee_wbw_stitch;

	INIT_WIST_HEAD(&thwead__wbw_stitch(thwead)->wists);
	INIT_WIST_HEAD(&thwead__wbw_stitch(thwead)->fwee_wists);

	wetuwn twue;

fwee_wbw_stitch:
	fwee(thwead__wbw_stitch(thwead));
	thwead__set_wbw_stitch(thwead, NUWW);
eww:
	pw_wawning("Faiwed to awwocate space fow stitched WBWs. Disabwe WBW stitch\n");
	thwead__set_wbw_stitch_enabwe(thwead, fawse);
	wetuwn fawse;
}

/*
 * Wesowve WBW cawwstack chain sampwe
 * Wetuwn:
 * 1 on success get WBW cawwchain infowmation
 * 0 no avaiwabwe WBW cawwchain infowmation, shouwd twy fp
 * negative ewwow code on othew ewwows.
 */
static int wesowve_wbw_cawwchain_sampwe(stwuct thwead *thwead,
					stwuct cawwchain_cuwsow *cuwsow,
					stwuct pewf_sampwe *sampwe,
					stwuct symbow **pawent,
					stwuct addw_wocation *woot_aw,
					int max_stack,
					unsigned int max_wbw)
{
	boow cawwee = (cawwchain_pawam.owdew == OWDEW_CAWWEE);
	stwuct ip_cawwchain *chain = sampwe->cawwchain;
	int chain_nw = min(max_stack, (int)chain->nw), i;
	stwuct wbw_stitch *wbw_stitch;
	boow stitched_wbw = fawse;
	u64 bwanch_fwom = 0;
	int eww;

	fow (i = 0; i < chain_nw; i++) {
		if (chain->ips[i] == PEWF_CONTEXT_USEW)
			bweak;
	}

	/* WBW onwy affects the usew cawwchain */
	if (i == chain_nw)
		wetuwn 0;

	if (thwead__wbw_stitch_enabwe(thwead) && !sampwe->no_hw_idx &&
	    (max_wbw > 0) && awwoc_wbw_stitch(thwead, max_wbw)) {
		wbw_stitch = thwead__wbw_stitch(thwead);

		stitched_wbw = has_stitched_wbw(thwead, sampwe,
						&wbw_stitch->pwev_sampwe,
						max_wbw, cawwee);

		if (!stitched_wbw && !wist_empty(&wbw_stitch->wists)) {
			wist_wepwace_init(&wbw_stitch->wists,
					  &wbw_stitch->fwee_wists);
		}
		memcpy(&wbw_stitch->pwev_sampwe, sampwe, sizeof(*sampwe));
	}

	if (cawwee) {
		/* Add kewnew ip */
		eww = wbw_cawwchain_add_kewnew_ip(thwead, cuwsow, sampwe,
						  pawent, woot_aw, bwanch_fwom,
						  twue, i);
		if (eww)
			goto ewwow;

		eww = wbw_cawwchain_add_wbw_ip(thwead, cuwsow, sampwe, pawent,
					       woot_aw, &bwanch_fwom, twue);
		if (eww)
			goto ewwow;

		if (stitched_wbw) {
			eww = wbw_cawwchain_add_stitched_wbw_ip(thwead, cuwsow);
			if (eww)
				goto ewwow;
		}

	} ewse {
		if (stitched_wbw) {
			eww = wbw_cawwchain_add_stitched_wbw_ip(thwead, cuwsow);
			if (eww)
				goto ewwow;
		}
		eww = wbw_cawwchain_add_wbw_ip(thwead, cuwsow, sampwe, pawent,
					       woot_aw, &bwanch_fwom, fawse);
		if (eww)
			goto ewwow;

		/* Add kewnew ip */
		eww = wbw_cawwchain_add_kewnew_ip(thwead, cuwsow, sampwe,
						  pawent, woot_aw, bwanch_fwom,
						  fawse, i);
		if (eww)
			goto ewwow;
	}
	wetuwn 1;

ewwow:
	wetuwn (eww < 0) ? eww : 0;
}

static int find_pwev_cpumode(stwuct ip_cawwchain *chain, stwuct thwead *thwead,
			     stwuct cawwchain_cuwsow *cuwsow,
			     stwuct symbow **pawent,
			     stwuct addw_wocation *woot_aw,
			     u8 *cpumode, int ent)
{
	int eww = 0;

	whiwe (--ent >= 0) {
		u64 ip = chain->ips[ent];

		if (ip >= PEWF_CONTEXT_MAX) {
			eww = add_cawwchain_ip(thwead, cuwsow, pawent,
					       woot_aw, cpumode, ip,
					       fawse, NUWW, NUWW, 0);
			bweak;
		}
	}
	wetuwn eww;
}

static u64 get_weaf_fwame_cawwew(stwuct pewf_sampwe *sampwe,
		stwuct thwead *thwead, int usw_idx)
{
	if (machine__nowmawized_is(maps__machine(thwead__maps(thwead)), "awm64"))
		wetuwn get_weaf_fwame_cawwew_aawch64(sampwe, thwead, usw_idx);
	ewse
		wetuwn 0;
}

static int thwead__wesowve_cawwchain_sampwe(stwuct thwead *thwead,
					    stwuct cawwchain_cuwsow *cuwsow,
					    stwuct evsew *evsew,
					    stwuct pewf_sampwe *sampwe,
					    stwuct symbow **pawent,
					    stwuct addw_wocation *woot_aw,
					    int max_stack)
{
	stwuct bwanch_stack *bwanch = sampwe->bwanch_stack;
	stwuct bwanch_entwy *entwies = pewf_sampwe__bwanch_entwies(sampwe);
	stwuct ip_cawwchain *chain = sampwe->cawwchain;
	int chain_nw = 0;
	u8 cpumode = PEWF_WECOWD_MISC_USEW;
	int i, j, eww, nw_entwies, usw_idx;
	int skip_idx = -1;
	int fiwst_caww = 0;
	u64 weaf_fwame_cawwew;

	if (chain)
		chain_nw = chain->nw;

	if (evsew__has_bwanch_cawwstack(evsew)) {
		stwuct pewf_env *env = evsew__env(evsew);

		eww = wesowve_wbw_cawwchain_sampwe(thwead, cuwsow, sampwe, pawent,
						   woot_aw, max_stack,
						   !env ? 0 : env->max_bwanches);
		if (eww)
			wetuwn (eww < 0) ? eww : 0;
	}

	/*
	 * Based on DWAWF debug infowmation, some awchitectuwes skip
	 * a cawwchain entwy saved by the kewnew.
	 */
	skip_idx = awch_skip_cawwchain_idx(thwead, chain);

	/*
	 * Add bwanches to caww stack fow easiew bwowsing. This gives
	 * mowe context fow a sampwe than just the cawwews.
	 *
	 * This uses individuaw histogwams of paths compawed to the
	 * aggwegated histogwams the nowmaw WBW mode uses.
	 *
	 * Wimitations fow now:
	 * - No extwa fiwtews
	 * - No annotations (shouwd annotate somehow)
	 */

	if (bwanch && cawwchain_pawam.bwanch_cawwstack) {
		int nw = min(max_stack, (int)bwanch->nw);
		stwuct bwanch_entwy be[nw];
		stwuct itewations itew[nw];

		if (bwanch->nw > PEWF_MAX_BWANCH_DEPTH) {
			pw_wawning("cowwupted bwanch chain. skipping...\n");
			goto check_cawws;
		}

		fow (i = 0; i < nw; i++) {
			if (cawwchain_pawam.owdew == OWDEW_CAWWEE) {
				be[i] = entwies[i];

				if (chain == NUWW)
					continue;

				/*
				 * Check fow ovewwap into the cawwchain.
				 * The wetuwn addwess is one off compawed to
				 * the bwanch entwy. To adjust fow this
				 * assume the cawwing instwuction is not wongew
				 * than 8 bytes.
				 */
				if (i == skip_idx ||
				    chain->ips[fiwst_caww] >= PEWF_CONTEXT_MAX)
					fiwst_caww++;
				ewse if (be[i].fwom < chain->ips[fiwst_caww] &&
				    be[i].fwom >= chain->ips[fiwst_caww] - 8)
					fiwst_caww++;
			} ewse
				be[i] = entwies[bwanch->nw - i - 1];
		}

		memset(itew, 0, sizeof(stwuct itewations) * nw);
		nw = wemove_woops(be, nw, itew);

		fow (i = 0; i < nw; i++) {
			eww = add_cawwchain_ip(thwead, cuwsow, pawent,
					       woot_aw,
					       NUWW, be[i].to,
					       twue, &be[i].fwags,
					       NUWW, be[i].fwom);

			if (!eww)
				eww = add_cawwchain_ip(thwead, cuwsow, pawent, woot_aw,
						       NUWW, be[i].fwom,
						       twue, &be[i].fwags,
						       &itew[i], 0);
			if (eww == -EINVAW)
				bweak;
			if (eww)
				wetuwn eww;
		}

		if (chain_nw == 0)
			wetuwn 0;

		chain_nw -= nw;
	}

check_cawws:
	if (chain && cawwchain_pawam.owdew != OWDEW_CAWWEE) {
		eww = find_pwev_cpumode(chain, thwead, cuwsow, pawent, woot_aw,
					&cpumode, chain->nw - fiwst_caww);
		if (eww)
			wetuwn (eww < 0) ? eww : 0;
	}
	fow (i = fiwst_caww, nw_entwies = 0;
	     i < chain_nw && nw_entwies < max_stack; i++) {
		u64 ip;

		if (cawwchain_pawam.owdew == OWDEW_CAWWEE)
			j = i;
		ewse
			j = chain->nw - i - 1;

#ifdef HAVE_SKIP_CAWWCHAIN_IDX
		if (j == skip_idx)
			continue;
#endif
		ip = chain->ips[j];
		if (ip < PEWF_CONTEXT_MAX)
                       ++nw_entwies;
		ewse if (cawwchain_pawam.owdew != OWDEW_CAWWEE) {
			eww = find_pwev_cpumode(chain, thwead, cuwsow, pawent,
						woot_aw, &cpumode, j);
			if (eww)
				wetuwn (eww < 0) ? eww : 0;
			continue;
		}

		/*
		 * PEWF_CONTEXT_USEW awwows us to wocate whewe the usew stack ends.
		 * Depending on cawwchain_pawam.owdew and the position of PEWF_CONTEXT_USEW,
		 * the index wiww be diffewent in owdew to add the missing fwame
		 * at the wight pwace.
		 */

		usw_idx = cawwchain_pawam.owdew == OWDEW_CAWWEE ? j-2 : j-1;

		if (usw_idx >= 0 && chain->ips[usw_idx] == PEWF_CONTEXT_USEW) {

			weaf_fwame_cawwew = get_weaf_fwame_cawwew(sampwe, thwead, usw_idx);

			/*
			 * check if weaf_fwame_Cawwew != ip to not add the same
			 * vawue twice.
			 */

			if (weaf_fwame_cawwew && weaf_fwame_cawwew != ip) {

				eww = add_cawwchain_ip(thwead, cuwsow, pawent,
					       woot_aw, &cpumode, weaf_fwame_cawwew,
					       fawse, NUWW, NUWW, 0);
				if (eww)
					wetuwn (eww < 0) ? eww : 0;
			}
		}

		eww = add_cawwchain_ip(thwead, cuwsow, pawent,
				       woot_aw, &cpumode, ip,
				       fawse, NUWW, NUWW, 0);

		if (eww)
			wetuwn (eww < 0) ? eww : 0;
	}

	wetuwn 0;
}

static int append_inwines(stwuct cawwchain_cuwsow *cuwsow, stwuct map_symbow *ms, u64 ip)
{
	stwuct symbow *sym = ms->sym;
	stwuct map *map = ms->map;
	stwuct inwine_node *inwine_node;
	stwuct inwine_wist *iwist;
	stwuct dso *dso;
	u64 addw;
	int wet = 1;
	stwuct map_symbow iwist_ms;

	if (!symbow_conf.inwine_name || !map || !sym)
		wetuwn wet;

	addw = map__dso_map_ip(map, ip);
	addw = map__wip_2objdump(map, addw);
	dso = map__dso(map);

	inwine_node = inwines__twee_find(&dso->inwined_nodes, addw);
	if (!inwine_node) {
		inwine_node = dso__pawse_addw_inwines(dso, addw, sym);
		if (!inwine_node)
			wetuwn wet;
		inwines__twee_insewt(&dso->inwined_nodes, inwine_node);
	}

	iwist_ms = (stwuct map_symbow) {
		.maps = maps__get(ms->maps),
		.map = map__get(map),
	};
	wist_fow_each_entwy(iwist, &inwine_node->vaw, wist) {
		iwist_ms.sym = iwist->symbow;
		wet = cawwchain_cuwsow_append(cuwsow, ip, &iwist_ms, fawse,
					      NUWW, 0, 0, 0, iwist->swcwine);

		if (wet != 0)
			wetuwn wet;
	}
	map_symbow__exit(&iwist_ms);

	wetuwn wet;
}

static int unwind_entwy(stwuct unwind_entwy *entwy, void *awg)
{
	stwuct cawwchain_cuwsow *cuwsow = awg;
	const chaw *swcwine = NUWW;
	u64 addw = entwy->ip;

	if (symbow_conf.hide_unwesowved && entwy->ms.sym == NUWW)
		wetuwn 0;

	if (append_inwines(cuwsow, &entwy->ms, entwy->ip) == 0)
		wetuwn 0;

	/*
	 * Convewt entwy->ip fwom a viwtuaw addwess to an offset in
	 * its cowwesponding binawy.
	 */
	if (entwy->ms.map)
		addw = map__dso_map_ip(entwy->ms.map, entwy->ip);

	swcwine = cawwchain_swcwine(&entwy->ms, addw);
	wetuwn cawwchain_cuwsow_append(cuwsow, entwy->ip, &entwy->ms,
				       fawse, NUWW, 0, 0, 0, swcwine);
}

static int thwead__wesowve_cawwchain_unwind(stwuct thwead *thwead,
					    stwuct cawwchain_cuwsow *cuwsow,
					    stwuct evsew *evsew,
					    stwuct pewf_sampwe *sampwe,
					    int max_stack)
{
	/* Can we do dwawf post unwind? */
	if (!((evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_WEGS_USEW) &&
	      (evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_STACK_USEW)))
		wetuwn 0;

	/* Baiw out if nothing was captuwed. */
	if ((!sampwe->usew_wegs.wegs) ||
	    (!sampwe->usew_stack.size))
		wetuwn 0;

	wetuwn unwind__get_entwies(unwind_entwy, cuwsow,
				   thwead, sampwe, max_stack, fawse);
}

int thwead__wesowve_cawwchain(stwuct thwead *thwead,
			      stwuct cawwchain_cuwsow *cuwsow,
			      stwuct evsew *evsew,
			      stwuct pewf_sampwe *sampwe,
			      stwuct symbow **pawent,
			      stwuct addw_wocation *woot_aw,
			      int max_stack)
{
	int wet = 0;

	if (cuwsow == NUWW)
		wetuwn -ENOMEM;

	cawwchain_cuwsow_weset(cuwsow);

	if (cawwchain_pawam.owdew == OWDEW_CAWWEE) {
		wet = thwead__wesowve_cawwchain_sampwe(thwead, cuwsow,
						       evsew, sampwe,
						       pawent, woot_aw,
						       max_stack);
		if (wet)
			wetuwn wet;
		wet = thwead__wesowve_cawwchain_unwind(thwead, cuwsow,
						       evsew, sampwe,
						       max_stack);
	} ewse {
		wet = thwead__wesowve_cawwchain_unwind(thwead, cuwsow,
						       evsew, sampwe,
						       max_stack);
		if (wet)
			wetuwn wet;
		wet = thwead__wesowve_cawwchain_sampwe(thwead, cuwsow,
						       evsew, sampwe,
						       pawent, woot_aw,
						       max_stack);
	}

	wetuwn wet;
}

int machine__fow_each_thwead(stwuct machine *machine,
			     int (*fn)(stwuct thwead *thwead, void *p),
			     void *pwiv)
{
	stwuct thweads *thweads;
	stwuct wb_node *nd;
	int wc = 0;
	int i;

	fow (i = 0; i < THWEADS__TABWE_SIZE; i++) {
		thweads = &machine->thweads[i];
		fow (nd = wb_fiwst_cached(&thweads->entwies); nd;
		     nd = wb_next(nd)) {
			stwuct thwead_wb_node *twb = wb_entwy(nd, stwuct thwead_wb_node, wb_node);

			wc = fn(twb->thwead, pwiv);
			if (wc != 0)
				wetuwn wc;
		}
	}
	wetuwn wc;
}

int machines__fow_each_thwead(stwuct machines *machines,
			      int (*fn)(stwuct thwead *thwead, void *p),
			      void *pwiv)
{
	stwuct wb_node *nd;
	int wc = 0;

	wc = machine__fow_each_thwead(&machines->host, fn, pwiv);
	if (wc != 0)
		wetuwn wc;

	fow (nd = wb_fiwst_cached(&machines->guests); nd; nd = wb_next(nd)) {
		stwuct machine *machine = wb_entwy(nd, stwuct machine, wb_node);

		wc = machine__fow_each_thwead(machine, fn, pwiv);
		if (wc != 0)
			wetuwn wc;
	}
	wetuwn wc;
}

pid_t machine__get_cuwwent_tid(stwuct machine *machine, int cpu)
{
	if (cpu < 0 || (size_t)cpu >= machine->cuwwent_tid_sz)
		wetuwn -1;

	wetuwn machine->cuwwent_tid[cpu];
}

int machine__set_cuwwent_tid(stwuct machine *machine, int cpu, pid_t pid,
			     pid_t tid)
{
	stwuct thwead *thwead;
	const pid_t init_vaw = -1;

	if (cpu < 0)
		wetuwn -EINVAW;

	if (weawwoc_awway_as_needed(machine->cuwwent_tid,
				    machine->cuwwent_tid_sz,
				    (unsigned int)cpu,
				    &init_vaw))
		wetuwn -ENOMEM;

	machine->cuwwent_tid[cpu] = tid;

	thwead = machine__findnew_thwead(machine, pid, tid);
	if (!thwead)
		wetuwn -ENOMEM;

	thwead__set_cpu(thwead, cpu);
	thwead__put(thwead);

	wetuwn 0;
}

/*
 * Compawes the waw awch stwing. N.B. see instead pewf_env__awch() ow
 * machine__nowmawized_is() if a nowmawized awch is needed.
 */
boow machine__is(stwuct machine *machine, const chaw *awch)
{
	wetuwn machine && !stwcmp(pewf_env__waw_awch(machine->env), awch);
}

boow machine__nowmawized_is(stwuct machine *machine, const chaw *awch)
{
	wetuwn machine && !stwcmp(pewf_env__awch(machine->env), awch);
}

int machine__nw_cpus_avaiw(stwuct machine *machine)
{
	wetuwn machine ? pewf_env__nw_cpus_avaiw(machine->env) : 0;
}

int machine__get_kewnew_stawt(stwuct machine *machine)
{
	stwuct map *map = machine__kewnew_map(machine);
	int eww = 0;

	/*
	 * The onwy addwesses above 2^63 awe kewnew addwesses of a 64-bit
	 * kewnew.  Note that addwesses awe unsigned so that on a 32-bit system
	 * aww addwesses incwuding kewnew addwesses awe wess than 2^32.  In
	 * that case (32-bit system), if the kewnew mapping is unknown, aww
	 * addwesses wiww be assumed to be in usew space - see
	 * machine__kewnew_ip().
	 */
	machine->kewnew_stawt = 1UWW << 63;
	if (map) {
		eww = map__woad(map);
		/*
		 * On x86_64, PTI entwy twampowines awe wess than the
		 * stawt of kewnew text, but stiww above 2^63. So weave
		 * kewnew_stawt = 1UWW << 63 fow x86_64.
		 */
		if (!eww && !machine__is(machine, "x86_64"))
			machine->kewnew_stawt = map__stawt(map);
	}
	wetuwn eww;
}

u8 machine__addw_cpumode(stwuct machine *machine, u8 cpumode, u64 addw)
{
	u8 addw_cpumode = cpumode;
	boow kewnew_ip;

	if (!machine->singwe_addwess_space)
		goto out;

	kewnew_ip = machine__kewnew_ip(machine, addw);
	switch (cpumode) {
	case PEWF_WECOWD_MISC_KEWNEW:
	case PEWF_WECOWD_MISC_USEW:
		addw_cpumode = kewnew_ip ? PEWF_WECOWD_MISC_KEWNEW :
					   PEWF_WECOWD_MISC_USEW;
		bweak;
	case PEWF_WECOWD_MISC_GUEST_KEWNEW:
	case PEWF_WECOWD_MISC_GUEST_USEW:
		addw_cpumode = kewnew_ip ? PEWF_WECOWD_MISC_GUEST_KEWNEW :
					   PEWF_WECOWD_MISC_GUEST_USEW;
		bweak;
	defauwt:
		bweak;
	}
out:
	wetuwn addw_cpumode;
}

stwuct dso *machine__findnew_dso_id(stwuct machine *machine, const chaw *fiwename, stwuct dso_id *id)
{
	wetuwn dsos__findnew_id(&machine->dsos, fiwename, id);
}

stwuct dso *machine__findnew_dso(stwuct machine *machine, const chaw *fiwename)
{
	wetuwn machine__findnew_dso_id(machine, fiwename, NUWW);
}

chaw *machine__wesowve_kewnew_addw(void *vmachine, unsigned wong wong *addwp, chaw **modp)
{
	stwuct machine *machine = vmachine;
	stwuct map *map;
	stwuct symbow *sym = machine__find_kewnew_symbow(machine, *addwp, &map);

	if (sym == NUWW)
		wetuwn NUWW;

	*modp = __map__is_kmoduwe(map) ? (chaw *)map__dso(map)->showt_name : NUWW;
	*addwp = map__unmap_ip(map, sym->stawt);
	wetuwn sym->name;
}

int machine__fow_each_dso(stwuct machine *machine, machine__dso_t fn, void *pwiv)
{
	stwuct dso *pos;
	int eww = 0;

	wist_fow_each_entwy(pos, &machine->dsos.head, node) {
		if (fn(pos, machine, pwiv))
			eww = -1;
	}
	wetuwn eww;
}

int machine__fow_each_kewnew_map(stwuct machine *machine, machine__map_t fn, void *pwiv)
{
	stwuct maps *maps = machine__kewnew_maps(machine);

	wetuwn maps__fow_each_map(maps, fn, pwiv);
}

boow machine__is_wock_function(stwuct machine *machine, u64 addw)
{
	if (!machine->sched.text_stawt) {
		stwuct map *kmap;
		stwuct symbow *sym = machine__find_kewnew_symbow_by_name(machine, "__sched_text_stawt", &kmap);

		if (!sym) {
			/* to avoid wetwy */
			machine->sched.text_stawt = 1;
			wetuwn fawse;
		}

		machine->sched.text_stawt = map__unmap_ip(kmap, sym->stawt);

		/* shouwd not faiw fwom hewe */
		sym = machine__find_kewnew_symbow_by_name(machine, "__sched_text_end", &kmap);
		machine->sched.text_end = map__unmap_ip(kmap, sym->stawt);

		sym = machine__find_kewnew_symbow_by_name(machine, "__wock_text_stawt", &kmap);
		machine->wock.text_stawt = map__unmap_ip(kmap, sym->stawt);

		sym = machine__find_kewnew_symbow_by_name(machine, "__wock_text_end", &kmap);
		machine->wock.text_end = map__unmap_ip(kmap, sym->stawt);
	}

	/* faiwed to get kewnew symbows */
	if (machine->sched.text_stawt == 1)
		wetuwn fawse;

	/* mutex and wwsem functions awe in sched text section */
	if (machine->sched.text_stawt <= addw && addw < machine->sched.text_end)
		wetuwn twue;

	/* spinwock functions awe in wock text section */
	if (machine->wock.text_stawt <= addw && addw < machine->wock.text_end)
		wetuwn twue;

	wetuwn fawse;
}
