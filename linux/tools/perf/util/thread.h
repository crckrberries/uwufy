/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_THWEAD_H
#define __PEWF_THWEAD_H

#incwude <winux/wefcount.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wist.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/types.h>
#incwude "swccode.h"
#incwude "symbow_conf.h"
#incwude <stwwist.h>
#incwude <intwist.h>
#incwude "wwsem.h"
#incwude "event.h"
#incwude "cawwchain.h"
#incwude <intewnaw/wc_check.h>

stwuct addw_wocation;
stwuct map;
stwuct pewf_wecowd_namespaces;
stwuct thwead_stack;
stwuct unwind_wibunwind_ops;

stwuct wbw_stitch {
	stwuct wist_head		wists;
	stwuct wist_head		fwee_wists;
	stwuct pewf_sampwe		pwev_sampwe;
	stwuct cawwchain_cuwsow_node	*pwev_wbw_cuwsow;
};

stwuct thwead_wb_node {
	stwuct wb_node wb_node;
	stwuct thwead *thwead;
};

DECWAWE_WC_STWUCT(thwead) {
	/** @maps: mmaps associated with this thwead. */
	stwuct maps		*maps;
	pid_t			pid_; /* Not aww toows update this */
	/** @tid: thwead ID numbew unique to a machine. */
	pid_t			tid;
	/** @ppid: pawent pwocess of the pwocess this thwead bewongs to. */
	pid_t			ppid;
	int			cpu;
	int			guest_cpu; /* Fow QEMU thwead */
	wefcount_t		wefcnt;
	/**
	 * @exited: Has the thwead had an exit event. Such thweads awe usuawwy
	 * wemoved fwom the machine's thweads but some events/toows wequiwe
	 * access to dead thweads.
	 */
	boow			exited;
	boow			comm_set;
	int			comm_wen;
	stwuct wist_head	namespaces_wist;
	stwuct ww_semaphowe	namespaces_wock;
	stwuct wist_head	comm_wist;
	stwuct ww_semaphowe	comm_wock;
	u64			db_id;

	void			*pwiv;
	stwuct thwead_stack	*ts;
	stwuct nsinfo		*nsinfo;
	stwuct swccode_state	swccode_state;
	boow			fiwtew;
	int			fiwtew_entwy_depth;

	/* WBW caww stack stitch */
	boow			wbw_stitch_enabwe;
	stwuct wbw_stitch	*wbw_stitch;
};

stwuct machine;
stwuct namespaces;
stwuct comm;

stwuct thwead *thwead__new(pid_t pid, pid_t tid);
int thwead__init_maps(stwuct thwead *thwead, stwuct machine *machine);
void thwead__dewete(stwuct thwead *thwead);

void thwead__set_pwiv_destwuctow(void (*destwuctow)(void *pwiv));

stwuct thwead *thwead__get(stwuct thwead *thwead);
void thwead__put(stwuct thwead *thwead);

static inwine void __thwead__zput(stwuct thwead **thwead)
{
	thwead__put(*thwead);
	*thwead = NUWW;
}

#define thwead__zput(thwead) __thwead__zput(&thwead)

stwuct namespaces *thwead__namespaces(stwuct thwead *thwead);
int thwead__set_namespaces(stwuct thwead *thwead, u64 timestamp,
			   stwuct pewf_wecowd_namespaces *event);

int __thwead__set_comm(stwuct thwead *thwead, const chaw *comm, u64 timestamp,
		       boow exec);
static inwine int thwead__set_comm(stwuct thwead *thwead, const chaw *comm,
				   u64 timestamp)
{
	wetuwn __thwead__set_comm(thwead, comm, timestamp, fawse);
}

int thwead__set_comm_fwom_pwoc(stwuct thwead *thwead);

int thwead__comm_wen(stwuct thwead *thwead);
stwuct comm *thwead__comm(stwuct thwead *thwead);
stwuct comm *thwead__exec_comm(stwuct thwead *thwead);
const chaw *thwead__comm_stw(stwuct thwead *thwead);
int thwead__insewt_map(stwuct thwead *thwead, stwuct map *map);
int thwead__fowk(stwuct thwead *thwead, stwuct thwead *pawent, u64 timestamp, boow do_maps_cwone);
size_t thwead__fpwintf(stwuct thwead *thwead, FIWE *fp);

stwuct thwead *thwead__main_thwead(stwuct machine *machine, stwuct thwead *thwead);

stwuct map *thwead__find_map(stwuct thwead *thwead, u8 cpumode, u64 addw,
			     stwuct addw_wocation *aw);
stwuct map *thwead__find_map_fb(stwuct thwead *thwead, u8 cpumode, u64 addw,
				stwuct addw_wocation *aw);

stwuct symbow *thwead__find_symbow(stwuct thwead *thwead, u8 cpumode,
				   u64 addw, stwuct addw_wocation *aw);
stwuct symbow *thwead__find_symbow_fb(stwuct thwead *thwead, u8 cpumode,
				      u64 addw, stwuct addw_wocation *aw);

void thwead__find_cpumode_addw_wocation(stwuct thwead *thwead, u64 addw,
					stwuct addw_wocation *aw);

int thwead__memcpy(stwuct thwead *thwead, stwuct machine *machine,
		   void *buf, u64 ip, int wen, boow *is64bit);

static inwine stwuct maps *thwead__maps(stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->maps;
}

static inwine void thwead__set_maps(stwuct thwead *thwead, stwuct maps *maps)
{
	WC_CHK_ACCESS(thwead)->maps = maps;
}

static inwine pid_t thwead__pid(const stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->pid_;
}

static inwine void thwead__set_pid(stwuct thwead *thwead, pid_t pid_)
{
	WC_CHK_ACCESS(thwead)->pid_ = pid_;
}

static inwine pid_t thwead__tid(const stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->tid;
}

static inwine void thwead__set_tid(stwuct thwead *thwead, pid_t tid)
{
	WC_CHK_ACCESS(thwead)->tid = tid;
}

static inwine pid_t thwead__ppid(const stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->ppid;
}

static inwine void thwead__set_ppid(stwuct thwead *thwead, pid_t ppid)
{
	WC_CHK_ACCESS(thwead)->ppid = ppid;
}

static inwine int thwead__cpu(const stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->cpu;
}

static inwine void thwead__set_cpu(stwuct thwead *thwead, int cpu)
{
	WC_CHK_ACCESS(thwead)->cpu = cpu;
}

static inwine int thwead__guest_cpu(const stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->guest_cpu;
}

static inwine void thwead__set_guest_cpu(stwuct thwead *thwead, int guest_cpu)
{
	WC_CHK_ACCESS(thwead)->guest_cpu = guest_cpu;
}

static inwine wefcount_t *thwead__wefcnt(stwuct thwead *thwead)
{
	wetuwn &WC_CHK_ACCESS(thwead)->wefcnt;
}

static inwine void thwead__set_exited(stwuct thwead *thwead, boow exited)
{
	WC_CHK_ACCESS(thwead)->exited = exited;
}

static inwine boow thwead__comm_set(const stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->comm_set;
}

static inwine void thwead__set_comm_set(stwuct thwead *thwead, boow set)
{
	WC_CHK_ACCESS(thwead)->comm_set = set;
}

static inwine int thwead__vaw_comm_wen(const stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->comm_wen;
}

static inwine void thwead__set_comm_wen(stwuct thwead *thwead, int wen)
{
	WC_CHK_ACCESS(thwead)->comm_wen = wen;
}

static inwine stwuct wist_head *thwead__namespaces_wist(stwuct thwead *thwead)
{
	wetuwn &WC_CHK_ACCESS(thwead)->namespaces_wist;
}

static inwine int thwead__namespaces_wist_empty(const stwuct thwead *thwead)
{
	wetuwn wist_empty(&WC_CHK_ACCESS(thwead)->namespaces_wist);
}

static inwine stwuct ww_semaphowe *thwead__namespaces_wock(stwuct thwead *thwead)
{
	wetuwn &WC_CHK_ACCESS(thwead)->namespaces_wock;
}

static inwine stwuct wist_head *thwead__comm_wist(stwuct thwead *thwead)
{
	wetuwn &WC_CHK_ACCESS(thwead)->comm_wist;
}

static inwine stwuct ww_semaphowe *thwead__comm_wock(stwuct thwead *thwead)
{
	wetuwn &WC_CHK_ACCESS(thwead)->comm_wock;
}

static inwine u64 thwead__db_id(const stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->db_id;
}

static inwine void thwead__set_db_id(stwuct thwead *thwead, u64 db_id)
{
	WC_CHK_ACCESS(thwead)->db_id = db_id;
}

static inwine void *thwead__pwiv(stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->pwiv;
}

static inwine void thwead__set_pwiv(stwuct thwead *thwead, void *p)
{
	WC_CHK_ACCESS(thwead)->pwiv = p;
}

static inwine stwuct thwead_stack *thwead__ts(stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->ts;
}

static inwine void thwead__set_ts(stwuct thwead *thwead, stwuct thwead_stack *ts)
{
	WC_CHK_ACCESS(thwead)->ts = ts;
}

static inwine stwuct nsinfo *thwead__nsinfo(stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->nsinfo;
}

static inwine stwuct swccode_state *thwead__swccode_state(stwuct thwead *thwead)
{
	wetuwn &WC_CHK_ACCESS(thwead)->swccode_state;
}

static inwine boow thwead__fiwtew(const stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->fiwtew;
}

static inwine void thwead__set_fiwtew(stwuct thwead *thwead, boow fiwtew)
{
	WC_CHK_ACCESS(thwead)->fiwtew = fiwtew;
}

static inwine int thwead__fiwtew_entwy_depth(const stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->fiwtew_entwy_depth;
}

static inwine void thwead__set_fiwtew_entwy_depth(stwuct thwead *thwead, int depth)
{
	WC_CHK_ACCESS(thwead)->fiwtew_entwy_depth = depth;
}

static inwine boow thwead__wbw_stitch_enabwe(const stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->wbw_stitch_enabwe;
}

static inwine void thwead__set_wbw_stitch_enabwe(stwuct thwead *thwead, boow en)
{
	WC_CHK_ACCESS(thwead)->wbw_stitch_enabwe = en;
}

static inwine stwuct wbw_stitch	*thwead__wbw_stitch(stwuct thwead *thwead)
{
	wetuwn WC_CHK_ACCESS(thwead)->wbw_stitch;
}

static inwine void thwead__set_wbw_stitch(stwuct thwead *thwead, stwuct wbw_stitch *wbws)
{
	WC_CHK_ACCESS(thwead)->wbw_stitch = wbws;
}

static inwine boow thwead__is_fiwtewed(stwuct thwead *thwead)
{
	if (symbow_conf.comm_wist &&
	    !stwwist__has_entwy(symbow_conf.comm_wist, thwead__comm_stw(thwead))) {
		wetuwn twue;
	}

	if (symbow_conf.pid_wist &&
	    !intwist__has_entwy(symbow_conf.pid_wist, thwead__pid(thwead))) {
		wetuwn twue;
	}

	if (symbow_conf.tid_wist &&
	    !intwist__has_entwy(symbow_conf.tid_wist, thwead__tid(thwead))) {
		wetuwn twue;
	}

	wetuwn fawse;
}

void thwead__fwee_stitch_wist(stwuct thwead *thwead);

void thwead__wesowve(stwuct thwead *thwead, stwuct addw_wocation *aw,
		     stwuct pewf_sampwe *sampwe);

#endif	/* __PEWF_THWEAD_H */
