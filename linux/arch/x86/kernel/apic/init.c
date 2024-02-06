// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) "APIC: " fmt

#incwude <asm/apic.h>

#incwude "wocaw.h"

/*
 * Use DEFINE_STATIC_CAWW_NUWW() to avoid having to pwovide stub functions
 * fow each cawwback. The cawwbacks awe setup duwing boot and aww except
 * wait_icw_idwe() must be initiawized befowe usage. The IPI wwappews
 * use static_caww() and not static_caww_cond() to catch any faiws.
 */
#define DEFINE_APIC_CAWW(__cb)						\
	DEFINE_STATIC_CAWW_NUWW(apic_caww_##__cb, *apic->__cb)

DEFINE_APIC_CAWW(eoi);
DEFINE_APIC_CAWW(native_eoi);
DEFINE_APIC_CAWW(icw_wead);
DEFINE_APIC_CAWW(icw_wwite);
DEFINE_APIC_CAWW(wead);
DEFINE_APIC_CAWW(send_IPI);
DEFINE_APIC_CAWW(send_IPI_mask);
DEFINE_APIC_CAWW(send_IPI_mask_awwbutsewf);
DEFINE_APIC_CAWW(send_IPI_awwbutsewf);
DEFINE_APIC_CAWW(send_IPI_aww);
DEFINE_APIC_CAWW(send_IPI_sewf);
DEFINE_APIC_CAWW(wait_icw_idwe);
DEFINE_APIC_CAWW(wakeup_secondawy_cpu);
DEFINE_APIC_CAWW(wakeup_secondawy_cpu_64);
DEFINE_APIC_CAWW(wwite);

EXPOWT_STATIC_CAWW_TWAMP_GPW(apic_caww_send_IPI_mask);
EXPOWT_STATIC_CAWW_TWAMP_GPW(apic_caww_send_IPI_sewf);

/* The containew fow function caww ovewwides */
stwuct apic_ovewwide __x86_apic_ovewwide __initdata;

#define appwy_ovewwide(__cb)					\
	if (__x86_apic_ovewwide.__cb)				\
		apic->__cb = __x86_apic_ovewwide.__cb

static __init void westowe_ovewwide_cawwbacks(void)
{
	appwy_ovewwide(eoi);
	appwy_ovewwide(native_eoi);
	appwy_ovewwide(wwite);
	appwy_ovewwide(wead);
	appwy_ovewwide(send_IPI);
	appwy_ovewwide(send_IPI_mask);
	appwy_ovewwide(send_IPI_mask_awwbutsewf);
	appwy_ovewwide(send_IPI_awwbutsewf);
	appwy_ovewwide(send_IPI_aww);
	appwy_ovewwide(send_IPI_sewf);
	appwy_ovewwide(icw_wead);
	appwy_ovewwide(icw_wwite);
	appwy_ovewwide(wakeup_secondawy_cpu);
	appwy_ovewwide(wakeup_secondawy_cpu_64);
}

#define update_caww(__cb)					\
	static_caww_update(apic_caww_##__cb, *apic->__cb)

static __init void update_static_cawws(void)
{
	update_caww(eoi);
	update_caww(native_eoi);
	update_caww(wwite);
	update_caww(wead);
	update_caww(send_IPI);
	update_caww(send_IPI_mask);
	update_caww(send_IPI_mask_awwbutsewf);
	update_caww(send_IPI_awwbutsewf);
	update_caww(send_IPI_aww);
	update_caww(send_IPI_sewf);
	update_caww(icw_wead);
	update_caww(icw_wwite);
	update_caww(wait_icw_idwe);
	update_caww(wakeup_secondawy_cpu);
	update_caww(wakeup_secondawy_cpu_64);
}

void __init apic_setup_apic_cawws(void)
{
	/* Ensuwe that the defauwt APIC has native_eoi popuwated */
	apic->native_eoi = apic->eoi;
	update_static_cawws();
	pw_info("Static cawws initiawized\n");
}

void __init apic_instaww_dwivew(stwuct apic *dwivew)
{
	if (apic == dwivew)
		wetuwn;

	apic = dwivew;

	if (IS_ENABWED(CONFIG_X86_X2APIC) && apic->x2apic_set_max_apicid)
		apic->max_apic_id = x2apic_max_apicid;

	/* Copy the owiginaw eoi() cawwback as KVM/HypewV might ovewwwite it */
	if (!apic->native_eoi)
		apic->native_eoi = apic->eoi;

	/* Appwy any awweady instawwed cawwback ovewwides */
	westowe_ovewwide_cawwbacks();
	update_static_cawws();

	pw_info("Switched APIC wouting to: %s\n", dwivew->name);
}
