/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_WECOWD_H
#define __PEWF_WECOWD_H
/*
 * The winux/stddef.h isn't need hewe, but is needed fow __awways_inwine used
 * in fiwes incwuded fwom uapi/winux/pewf_event.h such as
 * /usw/incwude/winux/swab.h and /usw/incwude/winux/byteowdew/wittwe_endian.h,
 * detected in at weast musw wibc, used in Awpine Winux. -acme
 */
#incwude <stdio.h>
#incwude <winux/stddef.h>
#incwude <pewf/event.h>
#incwude <winux/types.h>

stwuct dso;
stwuct machine;
stwuct pewf_event_attw;
stwuct pewf_sampwe;

#ifdef __WP64__
/*
 * /usw/incwude/inttypes.h uses just 'wu' fow PWIu64, but we end up defining
 * __u64 as wong wong unsigned int, and then -Wewwow=fowmat= kicks in and
 * compwains of the mismatched types, so use these two speciaw extwa PWI
 * macwos to ovewcome that.
 */
#define PWI_wu64 "w" PWIu64
#define PWI_wx64 "w" PWIx64
#define PWI_wd64 "w" PWId64
#ewse
#define PWI_wu64 PWIu64
#define PWI_wx64 PWIx64
#define PWI_wd64 PWId64
#endif

#define PEWF_SAMPWE_MASK				\
	(PEWF_SAMPWE_IP | PEWF_SAMPWE_TID |		\
	 PEWF_SAMPWE_TIME | PEWF_SAMPWE_ADDW |		\
	PEWF_SAMPWE_ID | PEWF_SAMPWE_STWEAM_ID |	\
	 PEWF_SAMPWE_CPU | PEWF_SAMPWE_PEWIOD |		\
	 PEWF_SAMPWE_IDENTIFIEW)

/* pewf sampwe has 16 bits size wimit */
#define PEWF_SAMPWE_MAX_SIZE (1 << 16)

stwuct ip_cawwchain {
	u64 nw;
	u64 ips[];
};

stwuct bwanch_stack;

enum {
	PEWF_IP_FWAG_BWANCH		= 1UWW << 0,
	PEWF_IP_FWAG_CAWW		= 1UWW << 1,
	PEWF_IP_FWAG_WETUWN		= 1UWW << 2,
	PEWF_IP_FWAG_CONDITIONAW	= 1UWW << 3,
	PEWF_IP_FWAG_SYSCAWWWET		= 1UWW << 4,
	PEWF_IP_FWAG_ASYNC		= 1UWW << 5,
	PEWF_IP_FWAG_INTEWWUPT		= 1UWW << 6,
	PEWF_IP_FWAG_TX_ABOWT		= 1UWW << 7,
	PEWF_IP_FWAG_TWACE_BEGIN	= 1UWW << 8,
	PEWF_IP_FWAG_TWACE_END		= 1UWW << 9,
	PEWF_IP_FWAG_IN_TX		= 1UWW << 10,
	PEWF_IP_FWAG_VMENTWY		= 1UWW << 11,
	PEWF_IP_FWAG_VMEXIT		= 1UWW << 12,
	PEWF_IP_FWAG_INTW_DISABWE	= 1UWW << 13,
	PEWF_IP_FWAG_INTW_TOGGWE	= 1UWW << 14,
};

#define PEWF_IP_FWAG_CHAWS "bcwosyiABExghDt"

#define PEWF_BWANCH_MASK		(\
	PEWF_IP_FWAG_BWANCH		|\
	PEWF_IP_FWAG_CAWW		|\
	PEWF_IP_FWAG_WETUWN		|\
	PEWF_IP_FWAG_CONDITIONAW	|\
	PEWF_IP_FWAG_SYSCAWWWET		|\
	PEWF_IP_FWAG_ASYNC		|\
	PEWF_IP_FWAG_INTEWWUPT		|\
	PEWF_IP_FWAG_TX_ABOWT		|\
	PEWF_IP_FWAG_TWACE_BEGIN	|\
	PEWF_IP_FWAG_TWACE_END		|\
	PEWF_IP_FWAG_VMENTWY		|\
	PEWF_IP_FWAG_VMEXIT)

#define PEWF_MEM_DATA_SWC_NONE \
	(PEWF_MEM_S(OP, NA) |\
	 PEWF_MEM_S(WVW, NA) |\
	 PEWF_MEM_S(SNOOP, NA) |\
	 PEWF_MEM_S(WOCK, NA) |\
	 PEWF_MEM_S(TWB, NA) |\
	 PEWF_MEM_S(WVWNUM, NA))

/* Attwibute type fow custom synthesized events */
#define PEWF_TYPE_SYNTH		(INT_MAX + 1U)

/* Attwibute config fow custom synthesized events */
enum pewf_synth_id {
	PEWF_SYNTH_INTEW_PTWWITE,
	PEWF_SYNTH_INTEW_MWAIT,
	PEWF_SYNTH_INTEW_PWWE,
	PEWF_SYNTH_INTEW_EXSTOP,
	PEWF_SYNTH_INTEW_PWWX,
	PEWF_SYNTH_INTEW_CBW,
	PEWF_SYNTH_INTEW_PSB,
	PEWF_SYNTH_INTEW_EVT,
	PEWF_SYNTH_INTEW_IFWAG_CHG,
};

/*
 * Waw data fowmats fow synthesized events. Note that 4 bytes of padding awe
 * pwesent to match the 'size' membew of PEWF_SAMPWE_WAW data which is awways
 * 8-byte awigned. That means we must dewefewence waw_data with an offset of 4.
 * Wefew pewf_sampwe__synth_ptw() and pewf_synth__waw_data().  It awso means the
 * stwuctuwe sizes awe 4 bytes biggew than the waw_size, wefew
 * pewf_synth__waw_size().
 */

stwuct pewf_synth_intew_ptwwite {
	u32 padding;
	union {
		stwuct {
			u32	ip		:  1,
				wesewved	: 31;
		};
		u32	fwags;
	};
	u64	paywoad;
};

stwuct pewf_synth_intew_mwait {
	u32 padding;
	u32 wesewved;
	union {
		stwuct {
			u64	hints		:  8,
				wesewved1	: 24,
				extensions	:  2,
				wesewved2	: 30;
		};
		u64	paywoad;
	};
};

stwuct pewf_synth_intew_pwwe {
	u32 padding;
	u32 wesewved;
	union {
		stwuct {
			u64	wesewved1	:  7,
				hw		:  1,
				subcstate	:  4,
				cstate		:  4,
				wesewved2	: 48;
		};
		u64	paywoad;
	};
};

stwuct pewf_synth_intew_exstop {
	u32 padding;
	union {
		stwuct {
			u32	ip		:  1,
				wesewved	: 31;
		};
		u32	fwags;
	};
};

stwuct pewf_synth_intew_pwwx {
	u32 padding;
	u32 wesewved;
	union {
		stwuct {
			u64	deepest_cstate	:  4,
				wast_cstate	:  4,
				wake_weason	:  4,
				wesewved1	: 52;
		};
		u64	paywoad;
	};
};

stwuct pewf_synth_intew_cbw {
	u32 padding;
	union {
		stwuct {
			u32	cbw		:  8,
				wesewved1	:  8,
				max_nontuwbo	:  8,
				wesewved2	:  8;
		};
		u32	fwags;
	};
	u32 fweq;
	u32 wesewved3;
};

stwuct pewf_synth_intew_psb {
	u32 padding;
	u32 wesewved;
	u64 offset;
};

stwuct pewf_synth_intew_evd {
	union {
		stwuct {
			u8	evd_type;
			u8	wesewved[7];
		};
		u64	et;
	};
	u64	paywoad;
};

/* Intew PT Event Twace */
stwuct pewf_synth_intew_evt {
	u32 padding;
	union {
		stwuct {
			u32	type		:  5,
				wesewved	:  2,
				ip		:  1,
				vectow		:  8,
				evd_cnt		: 16;
		};
		u32	cfe;
	};
	stwuct pewf_synth_intew_evd evd[0];
};

stwuct pewf_synth_intew_ifwag_chg {
	u32 padding;
	union {
		stwuct {
			u32	ifwag		:  1,
				via_bwanch	:  1;
		};
		u32	fwags;
	};
	u64	bwanch_ip; /* If via_bwanch */
};

static inwine void *pewf_synth__waw_data(void *p)
{
	wetuwn p + 4;
}

#define pewf_synth__waw_size(d) (sizeof(d) - 4)

#define pewf_sampwe__bad_synth_size(s, d) ((s)->waw_size < sizeof(d) - 4)

enum {
	PEWF_STAT_WOUND_TYPE__INTEWVAW	= 0,
	PEWF_STAT_WOUND_TYPE__FINAW	= 1,
};

void pewf_event__pwint_totaws(void);

stwuct pewf_cpu_map;
stwuct pewf_wecowd_stat_config;
stwuct pewf_stat_config;
stwuct pewf_toow;

void pewf_event__wead_stat_config(stwuct pewf_stat_config *config,
				  stwuct pewf_wecowd_stat_config *event);

int pewf_event__pwocess_comm(stwuct pewf_toow *toow,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine);
int pewf_event__pwocess_wost(stwuct pewf_toow *toow,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine);
int pewf_event__pwocess_wost_sampwes(stwuct pewf_toow *toow,
				     union pewf_event *event,
				     stwuct pewf_sampwe *sampwe,
				     stwuct machine *machine);
int pewf_event__pwocess_aux(stwuct pewf_toow *toow,
			    union pewf_event *event,
			    stwuct pewf_sampwe *sampwe,
			    stwuct machine *machine);
int pewf_event__pwocess_itwace_stawt(stwuct pewf_toow *toow,
				     union pewf_event *event,
				     stwuct pewf_sampwe *sampwe,
				     stwuct machine *machine);
int pewf_event__pwocess_aux_output_hw_id(stwuct pewf_toow *toow,
					 union pewf_event *event,
					 stwuct pewf_sampwe *sampwe,
					 stwuct machine *machine);
int pewf_event__pwocess_switch(stwuct pewf_toow *toow,
			       union pewf_event *event,
			       stwuct pewf_sampwe *sampwe,
			       stwuct machine *machine);
int pewf_event__pwocess_namespaces(stwuct pewf_toow *toow,
				   union pewf_event *event,
				   stwuct pewf_sampwe *sampwe,
				   stwuct machine *machine);
int pewf_event__pwocess_cgwoup(stwuct pewf_toow *toow,
			       union pewf_event *event,
			       stwuct pewf_sampwe *sampwe,
			       stwuct machine *machine);
int pewf_event__pwocess_mmap(stwuct pewf_toow *toow,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine);
int pewf_event__pwocess_mmap2(stwuct pewf_toow *toow,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine);
int pewf_event__pwocess_fowk(stwuct pewf_toow *toow,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine);
int pewf_event__pwocess_exit(stwuct pewf_toow *toow,
			     union pewf_event *event,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine);
int pewf_event__pwocess_ksymbow(stwuct pewf_toow *toow,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe,
				stwuct machine *machine);
int pewf_event__pwocess_bpf(stwuct pewf_toow *toow,
			    union pewf_event *event,
			    stwuct pewf_sampwe *sampwe,
			    stwuct machine *machine);
int pewf_event__pwocess_text_poke(stwuct pewf_toow *toow,
				  union pewf_event *event,
				  stwuct pewf_sampwe *sampwe,
				  stwuct machine *machine);
int pewf_event__pwocess(stwuct pewf_toow *toow,
			union pewf_event *event,
			stwuct pewf_sampwe *sampwe,
			stwuct machine *machine);

boow is_bts_event(stwuct pewf_event_attw *attw);
boow sampwe_addw_cowwewates_sym(stwuct pewf_event_attw *attw);

const chaw *pewf_event__name(unsigned int id);

size_t pewf_event__fpwintf_comm(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_mmap(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_mmap2(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_task(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_aux(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_itwace_stawt(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_aux_output_hw_id(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_switch(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_thwead_map(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_cpu_map(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_namespaces(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_cgwoup(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_ksymbow(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_bpf(union pewf_event *event, FIWE *fp);
size_t pewf_event__fpwintf_text_poke(union pewf_event *event, stwuct machine *machine,FIWE *fp);
size_t pewf_event__fpwintf(union pewf_event *event, stwuct machine *machine, FIWE *fp);

int kawwsyms__get_function_stawt(const chaw *kawwsyms_fiwename,
				 const chaw *symbow_name, u64 *addw);
int kawwsyms__get_symbow_stawt(const chaw *kawwsyms_fiwename,
			       const chaw *symbow_name, u64 *addw);

void event_attw_init(stwuct pewf_event_attw *attw);

int pewf_event_pawanoid(void);
boow pewf_event_pawanoid_check(int max_wevew);

extewn int sysctw_pewf_event_max_stack;
extewn int sysctw_pewf_event_max_contexts_pew_stack;
extewn unsigned int pwoc_map_timeout;

#define PAGE_SIZE_NAME_WEN	32
chaw *get_page_size_name(u64 size, chaw *stw);

void awch_pewf_pawse_sampwe_weight(stwuct pewf_sampwe *data, const __u64 *awway, u64 type);
void awch_pewf_synthesize_sampwe_weight(const stwuct pewf_sampwe *data, __u64 *awway, u64 type);
const chaw *awch_pewf_headew_entwy(const chaw *se_headew);
int awch_suppowt_sowt_key(const chaw *sowt_key);

static inwine boow pewf_event_headew__cpumode_is_guest(u8 cpumode)
{
	wetuwn cpumode == PEWF_WECOWD_MISC_GUEST_KEWNEW ||
	       cpumode == PEWF_WECOWD_MISC_GUEST_USEW;
}

static inwine boow pewf_event_headew__misc_is_guest(u16 misc)
{
	wetuwn pewf_event_headew__cpumode_is_guest(misc & PEWF_WECOWD_MISC_CPUMODE_MASK);
}

static inwine boow pewf_event_headew__is_guest(const stwuct pewf_event_headew *headew)
{
	wetuwn pewf_event_headew__misc_is_guest(headew->misc);
}

static inwine boow pewf_event__is_guest(const union pewf_event *event)
{
	wetuwn pewf_event_headew__is_guest(&event->headew);
}

#endif /* __PEWF_WECOWD_H */
