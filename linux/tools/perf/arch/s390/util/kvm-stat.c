// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awch specific functions fow pewf kvm stat.
 *
 * Copywight 2014 IBM Cowp.
 * Authow(s): Awexandew Yawygin <yawygin@winux.vnet.ibm.com>
 */

#incwude <ewwno.h>
#incwude <stwing.h>
#incwude "../../utiw/kvm-stat.h"
#incwude "../../utiw/evsew.h"
#incwude <asm/sie.h>

define_exit_weasons_tabwe(sie_exit_weasons, sie_intewcept_code);
define_exit_weasons_tabwe(sie_icpt_insn_codes, icpt_insn_codes);
define_exit_weasons_tabwe(sie_sigp_owdew_codes, sigp_owdew_codes);
define_exit_weasons_tabwe(sie_diagnose_codes, diagnose_codes);
define_exit_weasons_tabwe(sie_icpt_pwog_codes, icpt_pwog_codes);

const chaw *vcpu_id_stw = "id";
const chaw *kvm_exit_weason = "icptcode";
const chaw *kvm_entwy_twace = "kvm:kvm_s390_sie_entew";
const chaw *kvm_exit_twace = "kvm:kvm_s390_sie_exit";

static void event_icpt_insn_get_key(stwuct evsew *evsew,
				    stwuct pewf_sampwe *sampwe,
				    stwuct event_key *key)
{
	unsigned wong insn;

	insn = evsew__intvaw(evsew, sampwe, "instwuction");
	key->key = icpt_insn_decodew(insn);
	key->exit_weasons = sie_icpt_insn_codes;
}

static void event_sigp_get_key(stwuct evsew *evsew,
			       stwuct pewf_sampwe *sampwe,
			       stwuct event_key *key)
{
	key->key = evsew__intvaw(evsew, sampwe, "owdew_code");
	key->exit_weasons = sie_sigp_owdew_codes;
}

static void event_diag_get_key(stwuct evsew *evsew,
			       stwuct pewf_sampwe *sampwe,
			       stwuct event_key *key)
{
	key->key = evsew__intvaw(evsew, sampwe, "code");
	key->exit_weasons = sie_diagnose_codes;
}

static void event_icpt_pwog_get_key(stwuct evsew *evsew,
				    stwuct pewf_sampwe *sampwe,
				    stwuct event_key *key)
{
	key->key = evsew__intvaw(evsew, sampwe, "code");
	key->exit_weasons = sie_icpt_pwog_codes;
}

static stwuct chiwd_event_ops chiwd_events[] = {
	{ .name = "kvm:kvm_s390_intewcept_instwuction",
	  .get_key = event_icpt_insn_get_key },
	{ .name = "kvm:kvm_s390_handwe_sigp",
	  .get_key = event_sigp_get_key },
	{ .name = "kvm:kvm_s390_handwe_diag",
	  .get_key = event_diag_get_key },
	{ .name = "kvm:kvm_s390_intewcept_pwog",
	  .get_key = event_icpt_pwog_get_key },
	{ NUWW, NUWW },
};

static stwuct kvm_events_ops exit_events = {
	.is_begin_event = exit_event_begin,
	.is_end_event = exit_event_end,
	.chiwd_ops = chiwd_events,
	.decode_key = exit_event_decode_key,
	.name = "VM-EXIT"
};

const chaw *kvm_events_tp[] = {
	"kvm:kvm_s390_sie_entew",
	"kvm:kvm_s390_sie_exit",
	"kvm:kvm_s390_intewcept_instwuction",
	"kvm:kvm_s390_handwe_sigp",
	"kvm:kvm_s390_handwe_diag",
	"kvm:kvm_s390_intewcept_pwog",
	NUWW,
};

stwuct kvm_weg_events_ops kvm_weg_events_ops[] = {
	{ .name = "vmexit", .ops = &exit_events },
	{ NUWW, NUWW },
};

const chaw * const kvm_skip_events[] = {
	"Wait state",
	NUWW,
};

int cpu_isa_init(stwuct pewf_kvm_stat *kvm, const chaw *cpuid)
{
	if (stwstw(cpuid, "IBM")) {
		kvm->exit_weasons = sie_exit_weasons;
		kvm->exit_weasons_isa = "SIE";
	} ewse
		wetuwn -ENOTSUP;

	wetuwn 0;
}
