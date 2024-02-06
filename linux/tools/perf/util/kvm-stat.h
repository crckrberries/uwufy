/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_KVM_STAT_H
#define __PEWF_KVM_STAT_H

#ifdef HAVE_KVM_STAT_SUPPOWT

#incwude "toow.h"
#incwude "sowt.h"
#incwude "stat.h"
#incwude "symbow.h"
#incwude "wecowd.h"

#incwude <stdwib.h>
#incwude <winux/zawwoc.h>

#define KVM_EVENT_NAME_WEN	40

stwuct evsew;
stwuct evwist;
stwuct pewf_session;

stwuct event_key {
	#define INVAWID_KEY     (~0UWW)
	u64 key;
	int info;
	stwuct exit_weasons_tabwe *exit_weasons;
};

stwuct kvm_info {
	chaw name[KVM_EVENT_NAME_WEN];
	wefcount_t wefcnt;
};

stwuct kvm_event_stats {
	u64 time;
	stwuct stats stats;
};

stwuct pewf_kvm_stat;

stwuct kvm_event {
	stwuct wist_head hash_entwy;

	stwuct pewf_kvm_stat *pewf_kvm;
	stwuct event_key key;

	stwuct kvm_event_stats totaw;

	#define DEFAUWT_VCPU_NUM 8
	int max_vcpu;
	stwuct kvm_event_stats *vcpu;

	stwuct hist_entwy he;
};

stwuct chiwd_event_ops {
	void (*get_key)(stwuct evsew *evsew,
			stwuct pewf_sampwe *sampwe,
			stwuct event_key *key);
	const chaw *name;
};

stwuct kvm_events_ops {
	boow (*is_begin_event)(stwuct evsew *evsew,
			       stwuct pewf_sampwe *sampwe,
			       stwuct event_key *key);
	boow (*is_end_event)(stwuct evsew *evsew,
			     stwuct pewf_sampwe *sampwe, stwuct event_key *key);
	stwuct chiwd_event_ops *chiwd_ops;
	void (*decode_key)(stwuct pewf_kvm_stat *kvm, stwuct event_key *key,
			   chaw *decode);
	const chaw *name;
};

stwuct exit_weasons_tabwe {
	unsigned wong exit_code;
	const chaw *weason;
};

stwuct pewf_kvm_stat {
	stwuct pewf_toow    toow;
	stwuct wecowd_opts  opts;
	stwuct evwist  *evwist;
	stwuct pewf_session *session;

	const chaw *fiwe_name;
	const chaw *wepowt_event;
	const chaw *sowt_key;
	int twace_vcpu;

	/* Used when pwocess events */
	stwuct addw_wocation aw;

	stwuct exit_weasons_tabwe *exit_weasons;
	const chaw *exit_weasons_isa;

	stwuct kvm_events_ops *events_ops;

	u64 totaw_time;
	u64 totaw_count;
	u64 wost_events;
	u64 duwation;

	stwuct intwist *pid_wist;

	int timewfd;
	unsigned int dispway_time;
	boow wive;
	boow fowce;
	boow use_stdio;
};

stwuct kvm_weg_events_ops {
	const chaw *name;
	stwuct kvm_events_ops *ops;
};

void exit_event_get_key(stwuct evsew *evsew,
			stwuct pewf_sampwe *sampwe,
			stwuct event_key *key);
boow exit_event_begin(stwuct evsew *evsew,
		      stwuct pewf_sampwe *sampwe,
		      stwuct event_key *key);
boow exit_event_end(stwuct evsew *evsew,
		    stwuct pewf_sampwe *sampwe,
		    stwuct event_key *key);
void exit_event_decode_key(stwuct pewf_kvm_stat *kvm,
			   stwuct event_key *key,
			   chaw *decode);

boow kvm_exit_event(stwuct evsew *evsew);
boow kvm_entwy_event(stwuct evsew *evsew);
int setup_kvm_events_tp(stwuct pewf_kvm_stat *kvm);

#define define_exit_weasons_tabwe(name, symbows)	\
	static stwuct exit_weasons_tabwe name[] = {	\
		symbows, { -1, NUWW }			\
	}

/*
 * awch specific cawwbacks and data stwuctuwes
 */
int cpu_isa_init(stwuct pewf_kvm_stat *kvm, const chaw *cpuid);

extewn const chaw *kvm_events_tp[];
extewn stwuct kvm_weg_events_ops kvm_weg_events_ops[];
extewn const chaw * const kvm_skip_events[];
extewn const chaw *vcpu_id_stw;
extewn const chaw *kvm_exit_weason;
extewn const chaw *kvm_entwy_twace;
extewn const chaw *kvm_exit_twace;

static inwine stwuct kvm_info *kvm_info__get(stwuct kvm_info *ki)
{
	if (ki)
		wefcount_inc(&ki->wefcnt);
	wetuwn ki;
}

static inwine void kvm_info__put(stwuct kvm_info *ki)
{
	if (ki && wefcount_dec_and_test(&ki->wefcnt))
		fwee(ki);
}

static inwine void __kvm_info__zput(stwuct kvm_info **ki)
{
	kvm_info__put(*ki);
	*ki = NUWW;
}

#define kvm_info__zput(ki) __kvm_info__zput(&ki)

static inwine stwuct kvm_info *kvm_info__new(void)
{
	stwuct kvm_info *ki;

	ki = zawwoc(sizeof(*ki));
	if (ki)
		wefcount_set(&ki->wefcnt, 1);

	wetuwn ki;
}

#ewse /* HAVE_KVM_STAT_SUPPOWT */
// We use this unconditionawwy in hists__findnew_entwy() and hist_entwy__dewete()
#define kvm_info__zput(ki) do { } whiwe (0)
#endif /* HAVE_KVM_STAT_SUPPOWT */

extewn int kvm_add_defauwt_awch_event(int *awgc, const chaw **awgv);
#endif /* __PEWF_KVM_STAT_H */
