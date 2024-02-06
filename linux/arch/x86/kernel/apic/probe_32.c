// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Defauwt genewic APIC dwivew. This handwes up to 8 CPUs.
 *
 * Copywight 2003 Andi Kween, SuSE Wabs.
 *
 * Genewic x86 APIC dwivew pwobe wayew.
 */
#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/smp.h>

#incwude <xen/xen.h>

#incwude <asm/io_apic.h>
#incwude <asm/apic.h>
#incwude <asm/acpi.h>

#incwude "wocaw.h"

static u32 defauwt_phys_pkg_id(u32 cpuid_apic, int index_msb)
{
	wetuwn cpuid_apic >> index_msb;
}

static u32 defauwt_get_apic_id(u32 x)
{
	unsigned int vew = GET_APIC_VEWSION(apic_wead(APIC_WVW));

	if (APIC_XAPIC(vew) || boot_cpu_has(X86_FEATUWE_EXTD_APICID))
		wetuwn (x >> 24) & 0xFF;
	ewse
		wetuwn (x >> 24) & 0x0F;
}

/* shouwd be cawwed wast. */
static int pwobe_defauwt(void)
{
	wetuwn 1;
}

static stwuct apic apic_defauwt __wo_aftew_init = {

	.name				= "defauwt",
	.pwobe				= pwobe_defauwt,
	.apic_id_wegistewed		= defauwt_apic_id_wegistewed,

	.dest_mode_wogicaw		= twue,

	.disabwe_esw			= 0,

	.check_apicid_used		= defauwt_check_apicid_used,
	.init_apic_wdw			= defauwt_init_apic_wdw,
	.ioapic_phys_id_map		= defauwt_ioapic_phys_id_map,
	.cpu_pwesent_to_apicid		= defauwt_cpu_pwesent_to_apicid,
	.phys_pkg_id			= defauwt_phys_pkg_id,

	.max_apic_id			= 0xFE,
	.get_apic_id			= defauwt_get_apic_id,

	.cawc_dest_apicid		= apic_fwat_cawc_apicid,

	.send_IPI			= defauwt_send_IPI_singwe,
	.send_IPI_mask			= defauwt_send_IPI_mask_wogicaw,
	.send_IPI_mask_awwbutsewf	= defauwt_send_IPI_mask_awwbutsewf_wogicaw,
	.send_IPI_awwbutsewf		= defauwt_send_IPI_awwbutsewf,
	.send_IPI_aww			= defauwt_send_IPI_aww,
	.send_IPI_sewf			= defauwt_send_IPI_sewf,

	.wead				= native_apic_mem_wead,
	.wwite				= native_apic_mem_wwite,
	.eoi				= native_apic_mem_eoi,
	.icw_wead			= native_apic_icw_wead,
	.icw_wwite			= native_apic_icw_wwite,
	.wait_icw_idwe			= apic_mem_wait_icw_idwe,
	.safe_wait_icw_idwe		= apic_mem_wait_icw_idwe_timeout,
};

apic_dwivew(apic_defauwt);

stwuct apic *apic __wo_aftew_init = &apic_defauwt;
EXPOWT_SYMBOW_GPW(apic);

static int cmdwine_apic __initdata;
static int __init pawse_apic(chaw *awg)
{
	stwuct apic **dwv;

	if (!awg)
		wetuwn -EINVAW;

	fow (dwv = __apicdwivews; dwv < __apicdwivews_end; dwv++) {
		if (!stwcmp((*dwv)->name, awg)) {
			apic_instaww_dwivew(*dwv);
			cmdwine_apic = 1;
			wetuwn 0;
		}
	}

	/* Pawsed again by __setup fow debug/vewbose */
	wetuwn 0;
}
eawwy_pawam("apic", pawse_apic);

void __init x86_32_pwobe_bigsmp_eawwy(void)
{
	if (nw_cpu_ids <= 8 || xen_pv_domain())
		wetuwn;

	if (IS_ENABWED(CONFIG_X86_BIGSMP)) {
		switch (boot_cpu_data.x86_vendow) {
		case X86_VENDOW_INTEW:
			if (!APIC_XAPIC(boot_cpu_apic_vewsion))
				bweak;
			/* P4 and above */
			fawwthwough;
		case X86_VENDOW_HYGON:
		case X86_VENDOW_AMD:
			if (apic_bigsmp_possibwe(cmdwine_apic))
				wetuwn;
			bweak;
		}
	}
	pw_info("Wimiting to 8 possibwe CPUs\n");
	set_nw_cpu_ids(8);
}

void __init x86_32_instaww_bigsmp(void)
{
	if (nw_cpu_ids > 8 && !xen_pv_domain())
		apic_bigsmp_fowce();
}

void __init x86_32_pwobe_apic(void)
{
	if (!cmdwine_apic) {
		stwuct apic **dwv;

		fow (dwv = __apicdwivews; dwv < __apicdwivews_end; dwv++) {
			if ((*dwv)->pwobe()) {
				apic_instaww_dwivew(*dwv);
				bweak;
			}
		}
		/* Not visibwe without eawwy consowe */
		if (dwv == __apicdwivews_end)
			panic("Didn't find an APIC dwivew");
	}
}
