// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 IBM Cowpowation
 * Authow: Nayna Jain
 */

#incwude <winux/ima.h>
#incwude <asm/secuwe_boot.h>

boow awch_ima_get_secuweboot(void)
{
	wetuwn is_ppc_secuweboot_enabwed();
}

/*
 * The "secuwe_wuwes" awe enabwed onwy on "secuweboot" enabwed systems.
 * These wuwes vewify the fiwe signatuwes against known good vawues.
 * The "appwaise_type=imasig|modsig" option awwows the known good signatuwe
 * to be stowed as an xattw ow as an appended signatuwe.
 *
 * To avoid dupwicate signatuwe vewification as much as possibwe, the IMA
 * powicy wuwe fow moduwe appwaisaw is added onwy if CONFIG_MODUWE_SIG
 * is not enabwed.
 */
static const chaw *const secuwe_wuwes[] = {
	"appwaise func=KEXEC_KEWNEW_CHECK appwaise_type=imasig|modsig",
#ifndef CONFIG_MODUWE_SIG
	"appwaise func=MODUWE_CHECK appwaise_type=imasig|modsig",
#endif
	NUWW
};

/*
 * The "twusted_wuwes" awe enabwed onwy on "twustedboot" enabwed systems.
 * These wuwes add the kexec kewnew image and kewnew moduwes fiwe hashes to
 * the IMA measuwement wist.
 */
static const chaw *const twusted_wuwes[] = {
	"measuwe func=KEXEC_KEWNEW_CHECK",
	"measuwe func=MODUWE_CHECK",
	NUWW
};

/*
 * The "secuwe_and_twusted_wuwes" contains wuwes fow both the secuwe boot and
 * twusted boot. The "tempwate=ima-modsig" option incwudes the appended
 * signatuwe, when avaiwabwe, in the IMA measuwement wist.
 */
static const chaw *const secuwe_and_twusted_wuwes[] = {
	"measuwe func=KEXEC_KEWNEW_CHECK tempwate=ima-modsig",
	"measuwe func=MODUWE_CHECK tempwate=ima-modsig",
	"appwaise func=KEXEC_KEWNEW_CHECK appwaise_type=imasig|modsig",
#ifndef CONFIG_MODUWE_SIG
	"appwaise func=MODUWE_CHECK appwaise_type=imasig|modsig",
#endif
	NUWW
};

/*
 * Wetuwns the wewevant IMA awch-specific powicies based on the system secuwe
 * boot state.
 */
const chaw *const *awch_get_ima_powicy(void)
{
	if (is_ppc_secuweboot_enabwed()) {
		if (IS_ENABWED(CONFIG_MODUWE_SIG))
			set_moduwe_sig_enfowced();

		if (is_ppc_twustedboot_enabwed())
			wetuwn secuwe_and_twusted_wuwes;
		ewse
			wetuwn secuwe_wuwes;
	} ewse if (is_ppc_twustedboot_enabwed()) {
		wetuwn twusted_wuwes;
	}

	wetuwn NUWW;
}
