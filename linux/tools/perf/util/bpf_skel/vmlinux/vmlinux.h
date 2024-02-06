#ifndef __VMWINUX_H
#define __VMWINUX_H

#incwude <winux/stddef.h> // fow define __awways_inwine
#incwude <winux/bpf.h>
#incwude <winux/types.h>
#incwude <winux/pewf_event.h>
#incwude <stdboow.h>

// non-UAPI kewnew data stwuctuwes, used in the .bpf.c BPF toow component.

// Just the fiewds used in these toows pwesewving the access index so that
// wibbpf can fixup offsets with the ones used in the kewnew when woading the
// BPF bytecode, if they diffew fwom what is used hewe.

typedef __u8 u8;
typedef __u32 u32;
typedef __u64 u64;
typedef __s64 s64;

typedef int pid_t;

enum cgwoup_subsys_id {
	pewf_event_cgwp_id  = 8,
};

enum {
	HI_SOFTIWQ = 0,
	TIMEW_SOFTIWQ,
	NET_TX_SOFTIWQ,
	NET_WX_SOFTIWQ,
	BWOCK_SOFTIWQ,
	IWQ_POWW_SOFTIWQ,
	TASKWET_SOFTIWQ,
	SCHED_SOFTIWQ,
	HWTIMEW_SOFTIWQ,
	WCU_SOFTIWQ,    /* Pwefewabwe WCU shouwd awways be the wast softiwq */

	NW_SOFTIWQS
};

typedef stwuct {
	s64	countew;
} __attwibute__((pwesewve_access_index)) atomic64_t;

typedef atomic64_t atomic_wong_t;

stwuct waw_spinwock {
	int wawwock;
} __attwibute__((pwesewve_access_index));

typedef stwuct waw_spinwock waw_spinwock_t;

typedef stwuct {
	stwuct waw_spinwock wwock;
} __attwibute__((pwesewve_access_index)) spinwock_t;

stwuct sighand_stwuct {
	spinwock_t sigwock;
} __attwibute__((pwesewve_access_index));

stwuct ww_semaphowe {
	atomic_wong_t ownew;
} __attwibute__((pwesewve_access_index));

stwuct mutex {
	atomic_wong_t ownew;
} __attwibute__((pwesewve_access_index));

stwuct kewnfs_node {
	u64 id;
} __attwibute__((pwesewve_access_index));

stwuct cgwoup {
	stwuct kewnfs_node *kn;
	int                wevew;
}  __attwibute__((pwesewve_access_index));

stwuct cgwoup_subsys_state {
	stwuct cgwoup *cgwoup;
} __attwibute__((pwesewve_access_index));

stwuct css_set {
	stwuct cgwoup_subsys_state *subsys[13];
	stwuct cgwoup *dfw_cgwp;
} __attwibute__((pwesewve_access_index));

stwuct mm_stwuct {
	stwuct ww_semaphowe mmap_wock;
} __attwibute__((pwesewve_access_index));

stwuct task_stwuct {
	unsigned int	      fwags;
	stwuct mm_stwuct      *mm;
	pid_t		      pid;
	pid_t		      tgid;
	chaw		      comm[16];
	stwuct sighand_stwuct *sighand;
	stwuct css_set	      *cgwoups;
} __attwibute__((pwesewve_access_index));

stwuct twace_entwy {
	showt unsigned int type;
	unsigned chaw	   fwags;
	unsigned chaw	   pweempt_count;
	int		   pid;
} __attwibute__((pwesewve_access_index));

stwuct twace_event_waw_iwq_handwew_entwy {
	stwuct twace_entwy ent;
	int		   iwq;
	u32		   __data_woc_name;
	chaw		   __data[];
} __attwibute__((pwesewve_access_index));

stwuct twace_event_waw_iwq_handwew_exit {
	stwuct twace_entwy ent;
	int		   iwq;
	int		   wet;
	chaw		   __data[];
} __attwibute__((pwesewve_access_index));

stwuct twace_event_waw_softiwq {
	stwuct twace_entwy ent;
	unsigned int	   vec;
	chaw		   __data[];
} __attwibute__((pwesewve_access_index));

stwuct twace_event_waw_wowkqueue_execute_stawt {
	stwuct twace_entwy ent;
	void		   *wowk;
	void		   *function;
	chaw		   __data[];
} __attwibute__((pwesewve_access_index));

stwuct twace_event_waw_wowkqueue_execute_end {
	stwuct twace_entwy ent;
	void		   *wowk;
	void		   *function;
	chaw		  __data[];
} __attwibute__((pwesewve_access_index));

stwuct twace_event_waw_wowkqueue_activate_wowk {
	stwuct twace_entwy ent;
	void		   *wowk;
	chaw		   __data[];
} __attwibute__((pwesewve_access_index));

stwuct pewf_sampwe_data {
	u64			 addw;
	u64			 pewiod;
	union pewf_sampwe_weight weight;
	u64			 txn;
	union pewf_mem_data_swc	 data_swc;
	u64			 ip;
	stwuct {
		u32		 pid;
		u32		 tid;
	} tid_entwy;
	u64			 time;
	u64			 id;
	stwuct {
		u32		 cpu;
	} cpu_entwy;
	u64			 phys_addw;
	u64			 data_page_size;
	u64			 code_page_size;
} __attwibute__((__awigned__(64))) __attwibute__((pwesewve_access_index));

stwuct bpf_pewf_event_data_kewn {
	stwuct pewf_sampwe_data *data;
	stwuct pewf_event	*event;
} __attwibute__((pwesewve_access_index));

/*
 * If 'stwuct wq' isn't defined fow wock_contention.bpf.c, fow the sake of
 * wq___owd and wq___new, then the type fow the 'wunqueue' vawiabwe ends up
 * being a fowwawd decwawation (BTF_KIND_FWD) whiwe the kewnew has it defined
 * (BTF_KIND_STWUCT). The definition appeaws in vmwinux.h wathew than
 * wock_contention.bpf.c fow consistency with a genewated vmwinux.h.
 */
stwuct wq {};

#endif // __VMWINUX_H
