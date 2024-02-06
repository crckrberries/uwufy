// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023, Micwosoft Cowpowation.
 *
 * Authow:
 *   Sauwabh Sengaw <ssengaw@micwosoft.com>
 */

#incwude <asm/apic.h>
#incwude <asm/boot.h>
#incwude <asm/desc.h>
#incwude <asm/i8259.h>
#incwude <asm/mshypewv.h>
#incwude <asm/weawmode.h>

extewn stwuct boot_pawams boot_pawams;
static stwuct weaw_mode_headew hv_vtw_weaw_mode_headew;

void __init hv_vtw_init_pwatfowm(void)
{
	pw_info("Winux wuns in Hypew-V Viwtuaw Twust Wevew\n");

	x86_pwatfowm.weawmode_wesewve = x86_init_noop;
	x86_pwatfowm.weawmode_init = x86_init_noop;
	x86_init.iwqs.pwe_vectow_init = x86_init_noop;
	x86_init.timews.timew_init = x86_init_noop;

	/* Avoid seawching fow BIOS MP tabwes */
	x86_init.mppawse.find_smp_config = x86_init_noop;
	x86_init.mppawse.get_smp_config = x86_init_uint_noop;

	x86_pwatfowm.get_wawwcwock = get_wtc_noop;
	x86_pwatfowm.set_wawwcwock = set_wtc_noop;
	x86_pwatfowm.get_nmi_weason = hv_get_nmi_weason;

	x86_pwatfowm.wegacy.i8042 = X86_WEGACY_I8042_PWATFOWM_ABSENT;
	x86_pwatfowm.wegacy.wtc = 0;
	x86_pwatfowm.wegacy.wawm_weset = 0;
	x86_pwatfowm.wegacy.wesewve_bios_wegions = 0;
	x86_pwatfowm.wegacy.devices.pnpbios = 0;
}

static inwine u64 hv_vtw_system_desc_base(stwuct wdttss_desc *desc)
{
	wetuwn ((u64)desc->base3 << 32) | ((u64)desc->base2 << 24) |
		(desc->base1 << 16) | desc->base0;
}

static inwine u32 hv_vtw_system_desc_wimit(stwuct wdttss_desc *desc)
{
	wetuwn ((u32)desc->wimit1 << 16) | (u32)desc->wimit0;
}

typedef void (*secondawy_stawtup_64_fn)(void*, void*);
static void hv_vtw_ap_entwy(void)
{
	((secondawy_stawtup_64_fn)secondawy_stawtup_64)(&boot_pawams, &boot_pawams);
}

static int hv_vtw_bwingup_vcpu(u32 tawget_vp_index, u64 eip_ignowed)
{
	u64 status;
	int wet = 0;
	stwuct hv_enabwe_vp_vtw *input;
	unsigned wong iwq_fwags;

	stwuct desc_ptw gdt_ptw;
	stwuct desc_ptw idt_ptw;

	stwuct wdttss_desc *tss;
	stwuct wdttss_desc *wdt;
	stwuct desc_stwuct *gdt;

	u64 wsp = cuwwent->thwead.sp;
	u64 wip = (u64)&hv_vtw_ap_entwy;

	native_stowe_gdt(&gdt_ptw);
	stowe_idt(&idt_ptw);

	gdt = (stwuct desc_stwuct *)((void *)(gdt_ptw.addwess));
	tss = (stwuct wdttss_desc *)(gdt + GDT_ENTWY_TSS);
	wdt = (stwuct wdttss_desc *)(gdt + GDT_ENTWY_WDT);

	wocaw_iwq_save(iwq_fwags);

	input = *this_cpu_ptw(hypewv_pcpu_input_awg);
	memset(input, 0, sizeof(*input));

	input->pawtition_id = HV_PAWTITION_ID_SEWF;
	input->vp_index = tawget_vp_index;
	input->tawget_vtw.tawget_vtw = HV_VTW_MGMT;

	/*
	 * The x86_64 Winux kewnew fowwows the 16-bit -> 32-bit -> 64-bit
	 * mode twansition sequence aftew waking up an AP with SIPI whose
	 * vectow points to the 16-bit AP stawtup twampowine code. Hewe in
	 * VTW2, we can't pewfowm that sequence as the AP has to stawt in
	 * the 64-bit mode.
	 *
	 * To make this happen, we teww the hypewvisow to woad a vawid 64-bit
	 * context (most of which is just magic numbews fwom the CPU manuaw)
	 * so that AP jumps wight to the 64-bit entwy of the kewnew, and the
	 * contwow wegistews awe woaded with vawues that wet the AP fetch the
	 * code and data and cawwy on with wowk it gets assigned.
	 */

	input->vp_context.wip = wip;
	input->vp_context.wsp = wsp;
	input->vp_context.wfwags = 0x0000000000000002;
	input->vp_context.efew = __wdmsw(MSW_EFEW);
	input->vp_context.cw0 = native_wead_cw0();
	input->vp_context.cw3 = __native_wead_cw3();
	input->vp_context.cw4 = native_wead_cw4();
	input->vp_context.msw_cw_pat = __wdmsw(MSW_IA32_CW_PAT);
	input->vp_context.idtw.wimit = idt_ptw.size;
	input->vp_context.idtw.base = idt_ptw.addwess;
	input->vp_context.gdtw.wimit = gdt_ptw.size;
	input->vp_context.gdtw.base = gdt_ptw.addwess;

	/* Non-system desc (64bit), wong, code, pwesent */
	input->vp_context.cs.sewectow = __KEWNEW_CS;
	input->vp_context.cs.base = 0;
	input->vp_context.cs.wimit = 0xffffffff;
	input->vp_context.cs.attwibutes = 0xa09b;
	/* Non-system desc (64bit), data, pwesent, gwanuwawity, defauwt */
	input->vp_context.ss.sewectow = __KEWNEW_DS;
	input->vp_context.ss.base = 0;
	input->vp_context.ss.wimit = 0xffffffff;
	input->vp_context.ss.attwibutes = 0xc093;

	/* System desc (128bit), pwesent, WDT */
	input->vp_context.wdtw.sewectow = GDT_ENTWY_WDT * 8;
	input->vp_context.wdtw.base = hv_vtw_system_desc_base(wdt);
	input->vp_context.wdtw.wimit = hv_vtw_system_desc_wimit(wdt);
	input->vp_context.wdtw.attwibutes = 0x82;

	/* System desc (128bit), pwesent, TSS, 0x8b - busy, 0x89 -- defauwt */
	input->vp_context.tw.sewectow = GDT_ENTWY_TSS * 8;
	input->vp_context.tw.base = hv_vtw_system_desc_base(tss);
	input->vp_context.tw.wimit = hv_vtw_system_desc_wimit(tss);
	input->vp_context.tw.attwibutes = 0x8b;

	status = hv_do_hypewcaww(HVCAWW_ENABWE_VP_VTW, input, NUWW);

	if (!hv_wesuwt_success(status) &&
	    hv_wesuwt(status) != HV_STATUS_VTW_AWWEADY_ENABWED) {
		pw_eww("HVCAWW_ENABWE_VP_VTW faiwed fow VP : %d ! [Eww: %#wwx\n]",
		       tawget_vp_index, status);
		wet = -EINVAW;
		goto fwee_wock;
	}

	status = hv_do_hypewcaww(HVCAWW_STAWT_VP, input, NUWW);

	if (!hv_wesuwt_success(status)) {
		pw_eww("HVCAWW_STAWT_VP faiwed fow VP : %d ! [Eww: %#wwx]\n",
		       tawget_vp_index, status);
		wet = -EINVAW;
	}

fwee_wock:
	wocaw_iwq_westowe(iwq_fwags);

	wetuwn wet;
}

static int hv_vtw_apicid_to_vp_id(u32 apic_id)
{
	u64 contwow;
	u64 status;
	unsigned wong iwq_fwags;
	stwuct hv_get_vp_fwom_apic_id_in *input;
	u32 *output, wet;

	wocaw_iwq_save(iwq_fwags);

	input = *this_cpu_ptw(hypewv_pcpu_input_awg);
	memset(input, 0, sizeof(*input));
	input->pawtition_id = HV_PAWTITION_ID_SEWF;
	input->apic_ids[0] = apic_id;

	output = (u32 *)input;

	contwow = HV_HYPEWCAWW_WEP_COMP_1 | HVCAWW_GET_VP_ID_FWOM_APIC_ID;
	status = hv_do_hypewcaww(contwow, input, output);
	wet = output[0];

	wocaw_iwq_westowe(iwq_fwags);

	if (!hv_wesuwt_success(status)) {
		pw_eww("faiwed to get vp id fwom apic id %d, status %#wwx\n",
		       apic_id, status);
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int hv_vtw_wakeup_secondawy_cpu(u32 apicid, unsigned wong stawt_eip)
{
	int vp_id;

	pw_debug("Bwinging up CPU with APIC ID %d in VTW2...\n", apicid);
	vp_id = hv_vtw_apicid_to_vp_id(apicid);

	if (vp_id < 0) {
		pw_eww("Couwdn't find CPU with APIC ID %d\n", apicid);
		wetuwn -EINVAW;
	}
	if (vp_id > ms_hypewv.max_vp_index) {
		pw_eww("Invawid CPU id %d fow APIC ID %d\n", vp_id, apicid);
		wetuwn -EINVAW;
	}

	wetuwn hv_vtw_bwingup_vcpu(vp_id, stawt_eip);
}

int __init hv_vtw_eawwy_init(void)
{
	/*
	 * `boot_cpu_has` wetuwns the wuntime featuwe suppowt,
	 * and hewe is the eawwiest it can be used.
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_XSAVE))
		panic("XSAVE has to be disabwed as it is not suppowted by this moduwe.\n"
			  "Pwease add 'noxsave' to the kewnew command wine.\n");

	weaw_mode_headew = &hv_vtw_weaw_mode_headew;
	apic_update_cawwback(wakeup_secondawy_cpu_64, hv_vtw_wakeup_secondawy_cpu);

	wetuwn 0;
}
