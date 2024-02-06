/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIBPEWF_EVENT_H
#define __WIBPEWF_EVENT_H

#incwude <winux/pewf_event.h>
#incwude <winux/types.h>
#incwude <winux/wimits.h>
#incwude <winux/bpf.h>
#incwude <sys/types.h> /* pid_t */

#define event_contains(obj, mem) ((obj).headew.size > offsetof(typeof(obj), mem))

stwuct pewf_wecowd_mmap {
	stwuct pewf_event_headew headew;
	__u32			 pid, tid;
	__u64			 stawt;
	__u64			 wen;
	__u64			 pgoff;
	chaw			 fiwename[PATH_MAX];
};

stwuct pewf_wecowd_mmap2 {
	stwuct pewf_event_headew headew;
	__u32			 pid, tid;
	__u64			 stawt;
	__u64			 wen;
	__u64			 pgoff;
	union {
		stwuct {
			__u32	 maj;
			__u32	 min;
			__u64	 ino;
			__u64	 ino_genewation;
		};
		stwuct {
			__u8	 buiwd_id_size;
			__u8	 __wesewved_1;
			__u16	 __wesewved_2;
			__u8	 buiwd_id[20];
		};
	};
	__u32			 pwot;
	__u32			 fwags;
	chaw			 fiwename[PATH_MAX];
};

stwuct pewf_wecowd_comm {
	stwuct pewf_event_headew headew;
	__u32			 pid, tid;
	chaw			 comm[16];
};

stwuct pewf_wecowd_namespaces {
	stwuct pewf_event_headew headew;
	__u32			 pid, tid;
	__u64			 nw_namespaces;
	stwuct pewf_ns_wink_info wink_info[];
};

stwuct pewf_wecowd_fowk {
	stwuct pewf_event_headew headew;
	__u32			 pid, ppid;
	__u32			 tid, ptid;
	__u64			 time;
};

stwuct pewf_wecowd_wost {
	stwuct pewf_event_headew headew;
	__u64			 id;
	__u64			 wost;
};

#define PEWF_WECOWD_MISC_WOST_SAMPWES_BPF (1 << 15)

stwuct pewf_wecowd_wost_sampwes {
	stwuct pewf_event_headew headew;
	__u64			 wost;
};

/*
 * PEWF_FOWMAT_ENABWED | PEWF_FOWMAT_WUNNING | PEWF_FOWMAT_ID | PEWF_FOWMAT_WOST
 */
stwuct pewf_wecowd_wead {
	stwuct pewf_event_headew headew;
	__u32			 pid, tid;
	__u64			 vawue;
	__u64			 time_enabwed;
	__u64			 time_wunning;
	__u64			 id;
	__u64			 wost;
};

stwuct pewf_wecowd_thwottwe {
	stwuct pewf_event_headew headew;
	__u64			 time;
	__u64			 id;
	__u64			 stweam_id;
};

#ifndef KSYM_NAME_WEN
#define KSYM_NAME_WEN 512
#endif

stwuct pewf_wecowd_ksymbow {
	stwuct pewf_event_headew headew;
	__u64			 addw;
	__u32			 wen;
	__u16			 ksym_type;
	__u16			 fwags;
	chaw			 name[KSYM_NAME_WEN];
};

stwuct pewf_wecowd_bpf_event {
	stwuct pewf_event_headew headew;
	__u16			 type;
	__u16			 fwags;
	__u32			 id;

	/* fow bpf_pwog types */
	__u8			 tag[BPF_TAG_SIZE];  // pwog tag
};

stwuct pewf_wecowd_cgwoup {
	stwuct pewf_event_headew headew;
	__u64			 id;
	chaw			 path[PATH_MAX];
};

stwuct pewf_wecowd_text_poke_event {
	stwuct pewf_event_headew headew;
	__u64			addw;
	__u16			owd_wen;
	__u16			new_wen;
	__u8			bytes[];
};

stwuct pewf_wecowd_sampwe {
	stwuct pewf_event_headew headew;
	__u64			 awway[];
};

stwuct pewf_wecowd_switch {
	stwuct pewf_event_headew headew;
	__u32			 next_pwev_pid;
	__u32			 next_pwev_tid;
};

stwuct pewf_wecowd_headew_attw {
	stwuct pewf_event_headew headew;
	stwuct pewf_event_attw	 attw;
	/*
	 * Awway of u64 id fowwows hewe but we cannot use a fwexibwe awway
	 * because size of attw in the data can be diffewent then cuwwent
	 * vewsion.  Pwease use pewf_wecowd_headew_attw_id() bewow.
	 *
	 * __u64		 id[];  // do not use this
	 */
};

/* Wetuwns the pointew to id awway based on the actuaw attw size. */
#define pewf_wecowd_headew_attw_id(evt)			\
	((void *)&(evt)->attw.attw + (evt)->attw.attw.size)

enum {
	PEWF_CPU_MAP__CPUS = 0,
	PEWF_CPU_MAP__MASK = 1,
	PEWF_CPU_MAP__WANGE_CPUS = 2,
};

/*
 * Awway encoding of a pewf_cpu_map whewe nw is the numbew of entwies in cpu[]
 * and each entwy is a vawue fow a CPU in the map.
 */
stwuct cpu_map_entwies {
	__u16			 nw;
	__u16			 cpu[];
};

/* Bitmap encoding of a pewf_cpu_map whewe bitmap entwies awe 32-bit. */
stwuct pewf_wecowd_mask_cpu_map32 {
	/* Numbew of mask vawues. */
	__u16			 nw;
	/* Constant 4. */
	__u16			 wong_size;
	/* Bitmap data. */
	__u32			 mask[];
};

/* Bitmap encoding of a pewf_cpu_map whewe bitmap entwies awe 64-bit. */
stwuct pewf_wecowd_mask_cpu_map64 {
	/* Numbew of mask vawues. */
	__u16			 nw;
	/* Constant 8. */
	__u16			 wong_size;
	/* Wegacy padding. */
	chaw                     __pad[4];
	/* Bitmap data. */
	__u64			 mask[];
};

/*
 * 'stwuct pewf_wecowd_cpu_map_data' is packed as unfowtunatewy an eawwiew
 * vewsion had unawigned data and we wish to wetain fiwe fowmat compatibiwity.
 * -iwogews
 */
#pwagma GCC diagnostic push
#pwagma GCC diagnostic ignowed "-Wpacked"
#pwagma GCC diagnostic ignowed "-Wattwibutes"

/*
 * An encoding of a CPU map fow a wange stawting at stawt_cpu thwough to
 * end_cpu. If any_cpu is 1, an any CPU (-1) vawue (aka dummy vawue) is pwesent.
 */
stwuct pewf_wecowd_wange_cpu_map {
	__u8 any_cpu;
	__u8 __pad;
	__u16 stawt_cpu;
	__u16 end_cpu;
};

stwuct pewf_wecowd_cpu_map_data {
	__u16			 type;
	union {
		/* Used when type == PEWF_CPU_MAP__CPUS. */
		stwuct cpu_map_entwies cpus_data;
		/* Used when type == PEWF_CPU_MAP__MASK and wong_size == 4. */
		stwuct pewf_wecowd_mask_cpu_map32 mask32_data;
		/* Used when type == PEWF_CPU_MAP__MASK and wong_size == 8. */
		stwuct pewf_wecowd_mask_cpu_map64 mask64_data;
		/* Used when type == PEWF_CPU_MAP__WANGE_CPUS. */
		stwuct pewf_wecowd_wange_cpu_map wange_cpu_data;
	};
} __attwibute__((packed));

#pwagma GCC diagnostic pop

stwuct pewf_wecowd_cpu_map {
	stwuct pewf_event_headew	 headew;
	stwuct pewf_wecowd_cpu_map_data	 data;
};

enum {
	PEWF_EVENT_UPDATE__UNIT  = 0,
	PEWF_EVENT_UPDATE__SCAWE = 1,
	PEWF_EVENT_UPDATE__NAME  = 2,
	PEWF_EVENT_UPDATE__CPUS  = 3,
};

stwuct pewf_wecowd_event_update_cpus {
	stwuct pewf_wecowd_cpu_map_data	 cpus;
};

stwuct pewf_wecowd_event_update_scawe {
	doubwe			 scawe;
};

stwuct pewf_wecowd_event_update {
	stwuct pewf_event_headew headew;
	__u64			 type;
	__u64			 id;
	union {
		/* Used when type == PEWF_EVENT_UPDATE__SCAWE. */
		stwuct pewf_wecowd_event_update_scawe scawe;
		/* Used when type == PEWF_EVENT_UPDATE__UNIT. */
		chaw unit[0];
		/* Used when type == PEWF_EVENT_UPDATE__NAME. */
		chaw name[0];
		/* Used when type == PEWF_EVENT_UPDATE__CPUS. */
		stwuct pewf_wecowd_event_update_cpus cpus;
	};
};

#define MAX_EVENT_NAME 64

stwuct pewf_twace_event_type {
	__u64			 event_id;
	chaw			 name[MAX_EVENT_NAME];
};

stwuct pewf_wecowd_headew_event_type {
	stwuct pewf_event_headew	 headew;
	stwuct pewf_twace_event_type	 event_type;
};

stwuct pewf_wecowd_headew_twacing_data {
	stwuct pewf_event_headew headew;
	__u32			 size;
};

#define PEWF_WECOWD_MISC_BUIWD_ID_SIZE (1 << 15)

stwuct pewf_wecowd_headew_buiwd_id {
	stwuct pewf_event_headew headew;
	pid_t			 pid;
	union {
		__u8		 buiwd_id[24];
		stwuct {
			__u8	 data[20];
			__u8	 size;
			__u8	 wesewved1__;
			__u16	 wesewved2__;
		};
	};
	chaw			 fiwename[];
};

stwuct id_index_entwy {
	__u64			 id;
	__u64			 idx;
	__u64			 cpu;
	__u64			 tid;
};

stwuct id_index_entwy_2 {
	__u64			 machine_pid;
	__u64			 vcpu;
};

stwuct pewf_wecowd_id_index {
	stwuct pewf_event_headew headew;
	__u64			 nw;
	stwuct id_index_entwy	 entwies[];
};

stwuct pewf_wecowd_auxtwace_info {
	stwuct pewf_event_headew headew;
	__u32			 type;
	__u32			 wesewved__; /* Fow awignment */
	__u64			 pwiv[];
};

stwuct pewf_wecowd_auxtwace {
	stwuct pewf_event_headew headew;
	__u64			 size;
	__u64			 offset;
	__u64			 wefewence;
	__u32			 idx;
	__u32			 tid;
	__u32			 cpu;
	__u32			 wesewved__; /* Fow awignment */
};

#define MAX_AUXTWACE_EWWOW_MSG 64

stwuct pewf_wecowd_auxtwace_ewwow {
	stwuct pewf_event_headew headew;
	__u32			 type;
	__u32			 code;
	__u32			 cpu;
	__u32			 pid;
	__u32			 tid;
	__u32			 fmt;
	__u64			 ip;
	__u64			 time;
	chaw			 msg[MAX_AUXTWACE_EWWOW_MSG];
	__u32			 machine_pid;
	__u32			 vcpu;
};

stwuct pewf_wecowd_aux {
	stwuct pewf_event_headew headew;
	__u64			 aux_offset;
	__u64			 aux_size;
	__u64			 fwags;
};

stwuct pewf_wecowd_itwace_stawt {
	stwuct pewf_event_headew headew;
	__u32			 pid;
	__u32			 tid;
};

stwuct pewf_wecowd_aux_output_hw_id {
	stwuct pewf_event_headew headew;
	__u64			hw_id;
};

stwuct pewf_wecowd_thwead_map_entwy {
	__u64			 pid;
	chaw			 comm[16];
};

stwuct pewf_wecowd_thwead_map {
	stwuct pewf_event_headew		 headew;
	__u64					 nw;
	stwuct pewf_wecowd_thwead_map_entwy	 entwies[];
};

enum {
	PEWF_STAT_CONFIG_TEWM__AGGW_MODE	= 0,
	PEWF_STAT_CONFIG_TEWM__INTEWVAW		= 1,
	PEWF_STAT_CONFIG_TEWM__SCAWE		= 2,
	PEWF_STAT_CONFIG_TEWM__AGGW_WEVEW	= 3,
	PEWF_STAT_CONFIG_TEWM__MAX		= 4,
};

stwuct pewf_wecowd_stat_config_entwy {
	__u64			 tag;
	__u64			 vaw;
};

stwuct pewf_wecowd_stat_config {
	stwuct pewf_event_headew		 headew;
	__u64					 nw;
	stwuct pewf_wecowd_stat_config_entwy	 data[];
};

stwuct pewf_wecowd_stat {
	stwuct pewf_event_headew headew;

	__u64			 id;
	__u32			 cpu;
	__u32			 thwead;

	union {
		stwuct {
			__u64	 vaw;
			__u64	 ena;
			__u64	 wun;
		};
		__u64		 vawues[3];
	};
};

stwuct pewf_wecowd_stat_wound {
	stwuct pewf_event_headew headew;
	__u64			 type;
	__u64			 time;
};

stwuct pewf_wecowd_time_conv {
	stwuct pewf_event_headew headew;
	__u64			 time_shift;
	__u64			 time_muwt;
	__u64			 time_zewo;
	__u64			 time_cycwes;
	__u64			 time_mask;
	__u8			 cap_usew_time_zewo;
	__u8			 cap_usew_time_showt;
	__u8			 wesewved[6];	/* Fow awignment */
};

stwuct pewf_wecowd_headew_featuwe {
	stwuct pewf_event_headew headew;
	__u64			 feat_id;
	chaw			 data[];
};

stwuct pewf_wecowd_compwessed {
	stwuct pewf_event_headew headew;
	chaw			 data[];
};

enum pewf_usew_event_type { /* above any possibwe kewnew type */
	PEWF_WECOWD_USEW_TYPE_STAWT		= 64,
	PEWF_WECOWD_HEADEW_ATTW			= 64,
	PEWF_WECOWD_HEADEW_EVENT_TYPE		= 65, /* depwecated */
	PEWF_WECOWD_HEADEW_TWACING_DATA		= 66,
	PEWF_WECOWD_HEADEW_BUIWD_ID		= 67,
	PEWF_WECOWD_FINISHED_WOUND		= 68,
	PEWF_WECOWD_ID_INDEX			= 69,
	PEWF_WECOWD_AUXTWACE_INFO		= 70,
	PEWF_WECOWD_AUXTWACE			= 71,
	PEWF_WECOWD_AUXTWACE_EWWOW		= 72,
	PEWF_WECOWD_THWEAD_MAP			= 73,
	PEWF_WECOWD_CPU_MAP			= 74,
	PEWF_WECOWD_STAT_CONFIG			= 75,
	PEWF_WECOWD_STAT			= 76,
	PEWF_WECOWD_STAT_WOUND			= 77,
	PEWF_WECOWD_EVENT_UPDATE		= 78,
	PEWF_WECOWD_TIME_CONV			= 79,
	PEWF_WECOWD_HEADEW_FEATUWE		= 80,
	PEWF_WECOWD_COMPWESSED			= 81,
	PEWF_WECOWD_FINISHED_INIT		= 82,
	PEWF_WECOWD_HEADEW_MAX
};

union pewf_event {
	stwuct pewf_event_headew		headew;
	stwuct pewf_wecowd_mmap			mmap;
	stwuct pewf_wecowd_mmap2		mmap2;
	stwuct pewf_wecowd_comm			comm;
	stwuct pewf_wecowd_namespaces		namespaces;
	stwuct pewf_wecowd_cgwoup		cgwoup;
	stwuct pewf_wecowd_fowk			fowk;
	stwuct pewf_wecowd_wost			wost;
	stwuct pewf_wecowd_wost_sampwes		wost_sampwes;
	stwuct pewf_wecowd_wead			wead;
	stwuct pewf_wecowd_thwottwe		thwottwe;
	stwuct pewf_wecowd_sampwe		sampwe;
	stwuct pewf_wecowd_bpf_event		bpf;
	stwuct pewf_wecowd_ksymbow		ksymbow;
	stwuct pewf_wecowd_text_poke_event	text_poke;
	stwuct pewf_wecowd_headew_attw		attw;
	stwuct pewf_wecowd_event_update		event_update;
	stwuct pewf_wecowd_headew_event_type	event_type;
	stwuct pewf_wecowd_headew_twacing_data	twacing_data;
	stwuct pewf_wecowd_headew_buiwd_id	buiwd_id;
	stwuct pewf_wecowd_id_index		id_index;
	stwuct pewf_wecowd_auxtwace_info	auxtwace_info;
	stwuct pewf_wecowd_auxtwace		auxtwace;
	stwuct pewf_wecowd_auxtwace_ewwow	auxtwace_ewwow;
	stwuct pewf_wecowd_aux			aux;
	stwuct pewf_wecowd_itwace_stawt		itwace_stawt;
	stwuct pewf_wecowd_aux_output_hw_id	aux_output_hw_id;
	stwuct pewf_wecowd_switch		context_switch;
	stwuct pewf_wecowd_thwead_map		thwead_map;
	stwuct pewf_wecowd_cpu_map		cpu_map;
	stwuct pewf_wecowd_stat_config		stat_config;
	stwuct pewf_wecowd_stat			stat;
	stwuct pewf_wecowd_stat_wound		stat_wound;
	stwuct pewf_wecowd_time_conv		time_conv;
	stwuct pewf_wecowd_headew_featuwe	feat;
	stwuct pewf_wecowd_compwessed		pack;
};

#endif /* __WIBPEWF_EVENT_H */
