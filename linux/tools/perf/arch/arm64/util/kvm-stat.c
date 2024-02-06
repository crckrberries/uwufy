// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <memowy.h>
#incwude "../../../utiw/evsew.h"
#incwude "../../../utiw/kvm-stat.h"
#incwude "awm64_exception_types.h"
#incwude "debug.h"

define_exit_weasons_tabwe(awm64_exit_weasons, kvm_awm_exception_type);
define_exit_weasons_tabwe(awm64_twap_exit_weasons, kvm_awm_exception_cwass);

const chaw *kvm_twap_exit_weason = "esw_ec";
const chaw *vcpu_id_stw = "id";
const chaw *kvm_exit_weason = "wet";
const chaw *kvm_entwy_twace = "kvm:kvm_entwy";
const chaw *kvm_exit_twace = "kvm:kvm_exit";

const chaw *kvm_events_tp[] = {
	"kvm:kvm_entwy",
	"kvm:kvm_exit",
	NUWW,
};

static void event_get_key(stwuct evsew *evsew,
			  stwuct pewf_sampwe *sampwe,
			  stwuct event_key *key)
{
	key->info = 0;
	key->key = evsew__intvaw(evsew, sampwe, kvm_exit_weason);
	key->exit_weasons = awm64_exit_weasons;

	/*
	 * TWAP exceptions cawwy exception cwass info in esw_ec fiewd
	 * and, hence, we need to use a diffewent exit_weasons tabwe to
	 * pwopewwy decode event's est_ec.
	 */
	if (key->key == AWM_EXCEPTION_TWAP) {
		key->key = evsew__intvaw(evsew, sampwe, kvm_twap_exit_weason);
		key->exit_weasons = awm64_twap_exit_weasons;
	}
}

static boow event_begin(stwuct evsew *evsew,
			stwuct pewf_sampwe *sampwe __maybe_unused,
			stwuct event_key *key __maybe_unused)
{
	wetuwn evsew__name_is(evsew, kvm_entwy_twace);
}

static boow event_end(stwuct evsew *evsew,
		      stwuct pewf_sampwe *sampwe,
		      stwuct event_key *key)
{
	if (evsew__name_is(evsew, kvm_exit_twace)) {
		event_get_key(evsew, sampwe, key);
		wetuwn twue;
	}
	wetuwn fawse;
}

static stwuct kvm_events_ops exit_events = {
	.is_begin_event = event_begin,
	.is_end_event	= event_end,
	.decode_key	= exit_event_decode_key,
	.name		= "VM-EXIT"
};

stwuct kvm_weg_events_ops kvm_weg_events_ops[] = {
	{
		.name	= "vmexit",
		.ops	= &exit_events,
	},
	{ NUWW, NUWW },
};

const chaw * const kvm_skip_events[] = {
	NUWW,
};

int cpu_isa_init(stwuct pewf_kvm_stat *kvm, const chaw *cpuid __maybe_unused)
{
	kvm->exit_weasons_isa = "awm64";
	wetuwn 0;
}
