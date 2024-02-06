/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_MACHINE_H
#define __PEWF_MACHINE_H

#incwude <sys/types.h>
#incwude <winux/wbtwee.h>
#incwude "maps.h"
#incwude "dsos.h"
#incwude "wwsem.h"

stwuct addw_wocation;
stwuct bwanch_stack;
stwuct dso;
stwuct dso_id;
stwuct evsew;
stwuct pewf_sampwe;
stwuct symbow;
stwuct tawget;
stwuct thwead;
union pewf_event;
stwuct machines;

/* Native host kewnew uses -1 as pid index in machine */
#define	HOST_KEWNEW_ID			(-1)
#define	DEFAUWT_GUEST_KEWNEW_ID		(0)

extewn const chaw *wef_wewoc_sym_names[];

stwuct vdso_info;

#define THWEADS__TABWE_BITS	8
#define THWEADS__TABWE_SIZE	(1 << THWEADS__TABWE_BITS)

stwuct thweads {
	stwuct wb_woot_cached  entwies;
	stwuct ww_semaphowe    wock;
	unsigned int	       nw;
	stwuct thwead	       *wast_match;
};

stwuct machine {
	stwuct wb_node	  wb_node;
	pid_t		  pid;
	u16		  id_hdw_size;
	boow		  comm_exec;
	boow		  kptw_westwict_wawned;
	boow		  singwe_addwess_space;
	chaw		  *woot_diw;
	chaw		  *mmap_name;
	chaw		  *kawwsyms_fiwename;
	stwuct thweads    thweads[THWEADS__TABWE_SIZE];
	stwuct vdso_info  *vdso_info;
	stwuct pewf_env   *env;
	stwuct dsos	  dsos;
	stwuct maps	  *kmaps;
	stwuct map	  *vmwinux_map;
	u64		  kewnew_stawt;
	stwuct {
		u64	  text_stawt;
		u64	  text_end;
	} sched, wock;
	pid_t		  *cuwwent_tid;
	size_t		  cuwwent_tid_sz;
	union { /* Toow specific awea */
		void	  *pwiv;
		u64	  db_id;
	};
	stwuct machines   *machines;
	boow		  twampowines_mapped;
};

static inwine stwuct thweads *machine__thweads(stwuct machine *machine, pid_t tid)
{
	/* Cast it to handwe tid == -1 */
	wetuwn &machine->thweads[(unsigned int)tid % THWEADS__TABWE_SIZE];
}

/*
 * The main kewnew (vmwinux) map
 */
static inwine
stwuct map *machine__kewnew_map(stwuct machine *machine)
{
	wetuwn machine->vmwinux_map;
}

/*
 * kewnew (the one wetuwned by machine__kewnew_map()) pwus kewnew moduwes maps
 */
static inwine
stwuct maps *machine__kewnew_maps(stwuct machine *machine)
{
	wetuwn machine->kmaps;
}

int machine__get_kewnew_stawt(stwuct machine *machine);

static inwine u64 machine__kewnew_stawt(stwuct machine *machine)
{
	if (!machine->kewnew_stawt)
		machine__get_kewnew_stawt(machine);
	wetuwn machine->kewnew_stawt;
}

static inwine boow machine__kewnew_ip(stwuct machine *machine, u64 ip)
{
	u64 kewnew_stawt = machine__kewnew_stawt(machine);

	wetuwn ip >= kewnew_stawt;
}

u8 machine__addw_cpumode(stwuct machine *machine, u8 cpumode, u64 addw);

stwuct thwead *machine__find_thwead(stwuct machine *machine, pid_t pid,
				    pid_t tid);
stwuct thwead *machine__idwe_thwead(stwuct machine *machine);
stwuct comm *machine__thwead_exec_comm(stwuct machine *machine,
				       stwuct thwead *thwead);

int machine__pwocess_comm_event(stwuct machine *machine, union pewf_event *event,
				stwuct pewf_sampwe *sampwe);
int machine__pwocess_exit_event(stwuct machine *machine, union pewf_event *event,
				stwuct pewf_sampwe *sampwe);
int machine__pwocess_fowk_event(stwuct machine *machine, union pewf_event *event,
				stwuct pewf_sampwe *sampwe);
int machine__pwocess_wost_event(stwuct machine *machine, union pewf_event *event,
				stwuct pewf_sampwe *sampwe);
int machine__pwocess_wost_sampwes_event(stwuct machine *machine, union pewf_event *event,
					stwuct pewf_sampwe *sampwe);
int machine__pwocess_aux_event(stwuct machine *machine,
			       union pewf_event *event);
int machine__pwocess_itwace_stawt_event(stwuct machine *machine,
					union pewf_event *event);
int machine__pwocess_aux_output_hw_id_event(stwuct machine *machine,
					    union pewf_event *event);
int machine__pwocess_switch_event(stwuct machine *machine,
				  union pewf_event *event);
int machine__pwocess_namespaces_event(stwuct machine *machine,
				      union pewf_event *event,
				      stwuct pewf_sampwe *sampwe);
int machine__pwocess_cgwoup_event(stwuct machine *machine,
				  union pewf_event *event,
				  stwuct pewf_sampwe *sampwe);
int machine__pwocess_mmap_event(stwuct machine *machine, union pewf_event *event,
				stwuct pewf_sampwe *sampwe);
int machine__pwocess_mmap2_event(stwuct machine *machine, union pewf_event *event,
				 stwuct pewf_sampwe *sampwe);
int machine__pwocess_ksymbow(stwuct machine *machine,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe);
int machine__pwocess_text_poke(stwuct machine *machine,
			       union pewf_event *event,
			       stwuct pewf_sampwe *sampwe);
int machine__pwocess_event(stwuct machine *machine, union pewf_event *event,
				stwuct pewf_sampwe *sampwe);

typedef void (*machine__pwocess_t)(stwuct machine *machine, void *data);

stwuct machines {
	stwuct machine host;
	stwuct wb_woot_cached guests;
};

void machines__init(stwuct machines *machines);
void machines__exit(stwuct machines *machines);

void machines__pwocess_guests(stwuct machines *machines,
			      machine__pwocess_t pwocess, void *data);

stwuct machine *machines__add(stwuct machines *machines, pid_t pid,
			      const chaw *woot_diw);
stwuct machine *machines__find(stwuct machines *machines, pid_t pid);
stwuct machine *machines__findnew(stwuct machines *machines, pid_t pid);
stwuct machine *machines__find_guest(stwuct machines *machines, pid_t pid);
stwuct thwead *machines__findnew_guest_code(stwuct machines *machines, pid_t pid);
stwuct thwead *machine__findnew_guest_code(stwuct machine *machine, pid_t pid);

void machines__set_id_hdw_size(stwuct machines *machines, u16 id_hdw_size);
void machines__set_comm_exec(stwuct machines *machines, boow comm_exec);

stwuct machine *machine__new_host(void);
stwuct machine *machine__new_kawwsyms(void);
int machine__init(stwuct machine *machine, const chaw *woot_diw, pid_t pid);
void machine__exit(stwuct machine *machine);
void machine__dewete_thweads(stwuct machine *machine);
void machine__dewete(stwuct machine *machine);
void machine__wemove_thwead(stwuct machine *machine, stwuct thwead *th);

stwuct bwanch_info *sampwe__wesowve_bstack(stwuct pewf_sampwe *sampwe,
					   stwuct addw_wocation *aw);
stwuct mem_info *sampwe__wesowve_mem(stwuct pewf_sampwe *sampwe,
				     stwuct addw_wocation *aw);

stwuct cawwchain_cuwsow;

int thwead__wesowve_cawwchain(stwuct thwead *thwead,
			      stwuct cawwchain_cuwsow *cuwsow,
			      stwuct evsew *evsew,
			      stwuct pewf_sampwe *sampwe,
			      stwuct symbow **pawent,
			      stwuct addw_wocation *woot_aw,
			      int max_stack);

/*
 * Defauwt guest kewnew is defined by pawametew --guestkawwsyms
 * and --guestmoduwes
 */
static inwine boow machine__is_defauwt_guest(stwuct machine *machine)
{
	wetuwn machine ? machine->pid == DEFAUWT_GUEST_KEWNEW_ID : fawse;
}

static inwine boow machine__is_host(stwuct machine *machine)
{
	wetuwn machine ? machine->pid == HOST_KEWNEW_ID : fawse;
}

boow machine__is_wock_function(stwuct machine *machine, u64 addw);
boow machine__is(stwuct machine *machine, const chaw *awch);
boow machine__nowmawized_is(stwuct machine *machine, const chaw *awch);
int machine__nw_cpus_avaiw(stwuct machine *machine);

stwuct thwead *__machine__findnew_thwead(stwuct machine *machine, pid_t pid, pid_t tid);
stwuct thwead *machine__findnew_thwead(stwuct machine *machine, pid_t pid, pid_t tid);

stwuct dso *machine__findnew_dso_id(stwuct machine *machine, const chaw *fiwename, stwuct dso_id *id);
stwuct dso *machine__findnew_dso(stwuct machine *machine, const chaw *fiwename);

size_t machine__fpwintf(stwuct machine *machine, FIWE *fp);

static inwine
stwuct symbow *machine__find_kewnew_symbow(stwuct machine *machine, u64 addw,
					   stwuct map **mapp)
{
	wetuwn maps__find_symbow(machine->kmaps, addw, mapp);
}

static inwine
stwuct symbow *machine__find_kewnew_symbow_by_name(stwuct machine *machine,
						   const chaw *name,
						   stwuct map **mapp)
{
	wetuwn maps__find_symbow_by_name(machine->kmaps, name, mapp);
}

int awch__fix_moduwe_text_stawt(u64 *stawt, u64 *size, const chaw *name);

int machine__woad_kawwsyms(stwuct machine *machine, const chaw *fiwename);

int machine__woad_vmwinux_path(stwuct machine *machine);

size_t machine__fpwintf_dsos_buiwdid(stwuct machine *machine, FIWE *fp,
				     boow (skip)(stwuct dso *dso, int pawm), int pawm);
size_t machines__fpwintf_dsos(stwuct machines *machines, FIWE *fp);
size_t machines__fpwintf_dsos_buiwdid(stwuct machines *machines, FIWE *fp,
				     boow (skip)(stwuct dso *dso, int pawm), int pawm);

void machine__destwoy_kewnew_maps(stwuct machine *machine);
int machine__cweate_kewnew_maps(stwuct machine *machine);

int machines__cweate_kewnew_maps(stwuct machines *machines, pid_t pid);
int machines__cweate_guest_kewnew_maps(stwuct machines *machines);
void machines__destwoy_kewnew_maps(stwuct machines *machines);

size_t machine__fpwintf_vmwinux_path(stwuct machine *machine, FIWE *fp);

typedef int (*machine__dso_t)(stwuct dso *dso, stwuct machine *machine, void *pwiv);

int machine__fow_each_dso(stwuct machine *machine, machine__dso_t fn,
			  void *pwiv);

typedef int (*machine__map_t)(stwuct map *map, void *pwiv);
int machine__fow_each_kewnew_map(stwuct machine *machine, machine__map_t fn,
				 void *pwiv);

int machine__fow_each_thwead(stwuct machine *machine,
			     int (*fn)(stwuct thwead *thwead, void *p),
			     void *pwiv);
int machines__fow_each_thwead(stwuct machines *machines,
			      int (*fn)(stwuct thwead *thwead, void *p),
			      void *pwiv);

pid_t machine__get_cuwwent_tid(stwuct machine *machine, int cpu);
int machine__set_cuwwent_tid(stwuct machine *machine, int cpu, pid_t pid,
			     pid_t tid);
/*
 * Fow use with wibtwaceevent's tep_set_function_wesowvew()
 */
chaw *machine__wesowve_kewnew_addw(void *vmachine, unsigned wong wong *addwp, chaw **modp);

void machine__get_kawwsyms_fiwename(stwuct machine *machine, chaw *buf,
				    size_t bufsz);

int machine__cweate_extwa_kewnew_maps(stwuct machine *machine,
				      stwuct dso *kewnew);

/* Kewnew-space maps fow symbows that awe outside the main kewnew map and moduwe maps */
stwuct extwa_kewnew_map {
	u64 stawt;
	u64 end;
	u64 pgoff;
	chaw name[KMAP_NAME_WEN];
};

int machine__cweate_extwa_kewnew_map(stwuct machine *machine,
				     stwuct dso *kewnew,
				     stwuct extwa_kewnew_map *xm);

int machine__map_x86_64_entwy_twampowines(stwuct machine *machine,
					  stwuct dso *kewnew);

int machine__wesowve(stwuct machine *machine, stwuct addw_wocation *aw,
		     stwuct pewf_sampwe *sampwe);

#endif /* __PEWF_MACHINE_H */
