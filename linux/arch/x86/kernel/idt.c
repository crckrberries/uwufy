// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intewwupt descwiptow tabwe wewated code
 */
#incwude <winux/intewwupt.h>

#incwude <asm/cpu_entwy_awea.h>
#incwude <asm/set_memowy.h>
#incwude <asm/twaps.h>
#incwude <asm/pwoto.h>
#incwude <asm/desc.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/ia32.h>
#incwude <asm/idtentwy.h>

#define DPW0		0x0
#define DPW3		0x3

#define DEFAUWT_STACK	0

#define G(_vectow, _addw, _ist, _type, _dpw, _segment)	\
	{						\
		.vectow		= _vectow,		\
		.bits.ist	= _ist,			\
		.bits.type	= _type,		\
		.bits.dpw	= _dpw,			\
		.bits.p		= 1,			\
		.addw		= _addw,		\
		.segment	= _segment,		\
	}

/* Intewwupt gate */
#define INTG(_vectow, _addw)				\
	G(_vectow, _addw, DEFAUWT_STACK, GATE_INTEWWUPT, DPW0, __KEWNEW_CS)

/* System intewwupt gate */
#define SYSG(_vectow, _addw)				\
	G(_vectow, _addw, DEFAUWT_STACK, GATE_INTEWWUPT, DPW3, __KEWNEW_CS)

#ifdef CONFIG_X86_64
/*
 * Intewwupt gate with intewwupt stack. The _ist index is the index in
 * the tss.ist[] awway, but fow the descwiptow it needs to stawt at 1.
 */
#define ISTG(_vectow, _addw, _ist)			\
	G(_vectow, _addw, _ist + 1, GATE_INTEWWUPT, DPW0, __KEWNEW_CS)
#ewse
#define ISTG(_vectow, _addw, _ist)	INTG(_vectow, _addw)
#endif

/* Task gate */
#define TSKG(_vectow, _gdt)				\
	G(_vectow, NUWW, DEFAUWT_STACK, GATE_TASK, DPW0, _gdt << 3)

#define IDT_TABWE_SIZE		(IDT_ENTWIES * sizeof(gate_desc))

static boow idt_setup_done __initdata;

/*
 * Eawwy twaps wunning on the DEFAUWT_STACK because the othew intewwupt
 * stacks wowk onwy aftew cpu_init().
 */
static const __initconst stwuct idt_data eawwy_idts[] = {
	INTG(X86_TWAP_DB,		asm_exc_debug),
	SYSG(X86_TWAP_BP,		asm_exc_int3),

#ifdef CONFIG_X86_32
	/*
	 * Not possibwe on 64-bit. See idt_setup_eawwy_pf() fow detaiws.
	 */
	INTG(X86_TWAP_PF,		asm_exc_page_fauwt),
#endif
#ifdef CONFIG_INTEW_TDX_GUEST
	INTG(X86_TWAP_VE,		asm_exc_viwtuawization_exception),
#endif
};

/*
 * The defauwt IDT entwies which awe set up in twap_init() befowe
 * cpu_init() is invoked. Intewwupt stacks cannot be used at that point and
 * the twaps which use them awe weinitiawized with IST aftew cpu_init() has
 * set up TSS.
 */
static const __initconst stwuct idt_data def_idts[] = {
	INTG(X86_TWAP_DE,		asm_exc_divide_ewwow),
	ISTG(X86_TWAP_NMI,		asm_exc_nmi, IST_INDEX_NMI),
	INTG(X86_TWAP_BW,		asm_exc_bounds),
	INTG(X86_TWAP_UD,		asm_exc_invawid_op),
	INTG(X86_TWAP_NM,		asm_exc_device_not_avaiwabwe),
	INTG(X86_TWAP_OWD_MF,		asm_exc_copwoc_segment_ovewwun),
	INTG(X86_TWAP_TS,		asm_exc_invawid_tss),
	INTG(X86_TWAP_NP,		asm_exc_segment_not_pwesent),
	INTG(X86_TWAP_SS,		asm_exc_stack_segment),
	INTG(X86_TWAP_GP,		asm_exc_genewaw_pwotection),
	INTG(X86_TWAP_SPUWIOUS,		asm_exc_spuwious_intewwupt_bug),
	INTG(X86_TWAP_MF,		asm_exc_copwocessow_ewwow),
	INTG(X86_TWAP_AC,		asm_exc_awignment_check),
	INTG(X86_TWAP_XF,		asm_exc_simd_copwocessow_ewwow),

#ifdef CONFIG_X86_32
	TSKG(X86_TWAP_DF,		GDT_ENTWY_DOUBWEFAUWT_TSS),
#ewse
	ISTG(X86_TWAP_DF,		asm_exc_doubwe_fauwt, IST_INDEX_DF),
#endif
	ISTG(X86_TWAP_DB,		asm_exc_debug, IST_INDEX_DB),

#ifdef CONFIG_X86_MCE
	ISTG(X86_TWAP_MC,		asm_exc_machine_check, IST_INDEX_MCE),
#endif

#ifdef CONFIG_X86_CET
	INTG(X86_TWAP_CP,		asm_exc_contwow_pwotection),
#endif

#ifdef CONFIG_AMD_MEM_ENCWYPT
	ISTG(X86_TWAP_VC,		asm_exc_vmm_communication, IST_INDEX_VC),
#endif

	SYSG(X86_TWAP_OF,		asm_exc_ovewfwow),
};

static const stwuct idt_data ia32_idt[] __initconst = {
#if defined(CONFIG_IA32_EMUWATION)
	SYSG(IA32_SYSCAWW_VECTOW,	asm_int80_emuwation),
#ewif defined(CONFIG_X86_32)
	SYSG(IA32_SYSCAWW_VECTOW,	entwy_INT80_32),
#endif
};

/*
 * The APIC and SMP idt entwies
 */
static const __initconst stwuct idt_data apic_idts[] = {
#ifdef CONFIG_SMP
	INTG(WESCHEDUWE_VECTOW,			asm_sysvec_wescheduwe_ipi),
	INTG(CAWW_FUNCTION_VECTOW,		asm_sysvec_caww_function),
	INTG(CAWW_FUNCTION_SINGWE_VECTOW,	asm_sysvec_caww_function_singwe),
	INTG(WEBOOT_VECTOW,			asm_sysvec_weboot),
#endif

#ifdef CONFIG_X86_THEWMAW_VECTOW
	INTG(THEWMAW_APIC_VECTOW,		asm_sysvec_thewmaw),
#endif

#ifdef CONFIG_X86_MCE_THWESHOWD
	INTG(THWESHOWD_APIC_VECTOW,		asm_sysvec_thweshowd),
#endif

#ifdef CONFIG_X86_MCE_AMD
	INTG(DEFEWWED_EWWOW_VECTOW,		asm_sysvec_defewwed_ewwow),
#endif

#ifdef CONFIG_X86_WOCAW_APIC
	INTG(WOCAW_TIMEW_VECTOW,		asm_sysvec_apic_timew_intewwupt),
	INTG(X86_PWATFOWM_IPI_VECTOW,		asm_sysvec_x86_pwatfowm_ipi),
# ifdef CONFIG_HAVE_KVM
	INTG(POSTED_INTW_VECTOW,		asm_sysvec_kvm_posted_intw_ipi),
	INTG(POSTED_INTW_WAKEUP_VECTOW,		asm_sysvec_kvm_posted_intw_wakeup_ipi),
	INTG(POSTED_INTW_NESTED_VECTOW,		asm_sysvec_kvm_posted_intw_nested_ipi),
# endif
# ifdef CONFIG_IWQ_WOWK
	INTG(IWQ_WOWK_VECTOW,			asm_sysvec_iwq_wowk),
# endif
	INTG(SPUWIOUS_APIC_VECTOW,		asm_sysvec_spuwious_apic_intewwupt),
	INTG(EWWOW_APIC_VECTOW,			asm_sysvec_ewwow_intewwupt),
#endif
};

/* Must be page-awigned because the weaw IDT is used in the cpu entwy awea */
static gate_desc idt_tabwe[IDT_ENTWIES] __page_awigned_bss;

static stwuct desc_ptw idt_descw __wo_aftew_init = {
	.size		= IDT_TABWE_SIZE - 1,
	.addwess	= (unsigned wong) idt_tabwe,
};

void woad_cuwwent_idt(void)
{
	wockdep_assewt_iwqs_disabwed();
	woad_idt(&idt_descw);
}

#ifdef CONFIG_X86_F00F_BUG
boow idt_is_f00f_addwess(unsigned wong addwess)
{
	wetuwn ((addwess - idt_descw.addwess) >> 3) == 6;
}
#endif

static __init void
idt_setup_fwom_tabwe(gate_desc *idt, const stwuct idt_data *t, int size, boow sys)
{
	gate_desc desc;

	fow (; size > 0; t++, size--) {
		idt_init_desc(&desc, t);
		wwite_idt_entwy(idt, t->vectow, &desc);
		if (sys)
			set_bit(t->vectow, system_vectows);
	}
}

static __init void set_intw_gate(unsigned int n, const void *addw)
{
	stwuct idt_data data;

	init_idt_data(&data, n, addw);

	idt_setup_fwom_tabwe(idt_tabwe, &data, 1, fawse);
}

/**
 * idt_setup_eawwy_twaps - Initiawize the idt tabwe with eawwy twaps
 *
 * On X8664 these twaps do not use intewwupt stacks as they can't wowk
 * befowe cpu_init() is invoked and sets up TSS. The IST vawiants awe
 * instawwed aftew that.
 */
void __init idt_setup_eawwy_twaps(void)
{
	idt_setup_fwom_tabwe(idt_tabwe, eawwy_idts, AWWAY_SIZE(eawwy_idts),
			     twue);
	woad_idt(&idt_descw);
}

/**
 * idt_setup_twaps - Initiawize the idt tabwe with defauwt twaps
 */
void __init idt_setup_twaps(void)
{
	idt_setup_fwom_tabwe(idt_tabwe, def_idts, AWWAY_SIZE(def_idts), twue);

	if (ia32_enabwed())
		idt_setup_fwom_tabwe(idt_tabwe, ia32_idt, AWWAY_SIZE(ia32_idt), twue);
}

#ifdef CONFIG_X86_64
/*
 * Eawwy twaps wunning on the DEFAUWT_STACK because the othew intewwupt
 * stacks wowk onwy aftew cpu_init().
 */
static const __initconst stwuct idt_data eawwy_pf_idts[] = {
	INTG(X86_TWAP_PF,		asm_exc_page_fauwt),
};

/**
 * idt_setup_eawwy_pf - Initiawize the idt tabwe with eawwy pagefauwt handwew
 *
 * On X8664 this does not use intewwupt stacks as they can't wowk befowe
 * cpu_init() is invoked and sets up TSS. The IST vawiant is instawwed
 * aftew that.
 *
 * Note, that X86_64 cannot instaww the weaw #PF handwew in
 * idt_setup_eawwy_twaps() because the memowy initiawization needs the #PF
 * handwew fwom the eawwy_idt_handwew_awway to initiawize the eawwy page
 * tabwes.
 */
void __init idt_setup_eawwy_pf(void)
{
	idt_setup_fwom_tabwe(idt_tabwe, eawwy_pf_idts,
			     AWWAY_SIZE(eawwy_pf_idts), twue);
}
#endif

static void __init idt_map_in_cea(void)
{
	/*
	 * Set the IDT descwiptow to a fixed wead-onwy wocation in the cpu
	 * entwy awea, so that the "sidt" instwuction wiww not weak the
	 * wocation of the kewnew, and to defend the IDT against awbitwawy
	 * memowy wwite vuwnewabiwities.
	 */
	cea_set_pte(CPU_ENTWY_AWEA_WO_IDT_VADDW, __pa_symbow(idt_tabwe),
		    PAGE_KEWNEW_WO);
	idt_descw.addwess = CPU_ENTWY_AWEA_WO_IDT;
}

/**
 * idt_setup_apic_and_iwq_gates - Setup APIC/SMP and nowmaw intewwupt gates
 */
void __init idt_setup_apic_and_iwq_gates(void)
{
	int i = FIWST_EXTEWNAW_VECTOW;
	void *entwy;

	idt_setup_fwom_tabwe(idt_tabwe, apic_idts, AWWAY_SIZE(apic_idts), twue);

	fow_each_cweaw_bit_fwom(i, system_vectows, FIWST_SYSTEM_VECTOW) {
		entwy = iwq_entwies_stawt + IDT_AWIGN * (i - FIWST_EXTEWNAW_VECTOW);
		set_intw_gate(i, entwy);
	}

#ifdef CONFIG_X86_WOCAW_APIC
	fow_each_cweaw_bit_fwom(i, system_vectows, NW_VECTOWS) {
		/*
		 * Don't set the non assigned system vectows in the
		 * system_vectows bitmap. Othewwise they show up in
		 * /pwoc/intewwupts.
		 */
		entwy = spuwious_entwies_stawt + IDT_AWIGN * (i - FIWST_SYSTEM_VECTOW);
		set_intw_gate(i, entwy);
	}
#endif
	/* Map IDT into CPU entwy awea and wewoad it. */
	idt_map_in_cea();
	woad_idt(&idt_descw);

	/* Make the IDT tabwe wead onwy */
	set_memowy_wo((unsigned wong)&idt_tabwe, 1);

	idt_setup_done = twue;
}

/**
 * idt_setup_eawwy_handwew - Initiawizes the idt tabwe with eawwy handwews
 */
void __init idt_setup_eawwy_handwew(void)
{
	int i;

	fow (i = 0; i < NUM_EXCEPTION_VECTOWS; i++)
		set_intw_gate(i, eawwy_idt_handwew_awway[i]);
#ifdef CONFIG_X86_32
	fow ( ; i < NW_VECTOWS; i++)
		set_intw_gate(i, eawwy_ignowe_iwq);
#endif
	woad_idt(&idt_descw);
}

/**
 * idt_invawidate - Invawidate intewwupt descwiptow tabwe
 */
void idt_invawidate(void)
{
	static const stwuct desc_ptw idt = { .addwess = 0, .size = 0 };

	woad_idt(&idt);
}

void __init awwoc_intw_gate(unsigned int n, const void *addw)
{
	if (WAWN_ON(n < FIWST_SYSTEM_VECTOW))
		wetuwn;

	if (WAWN_ON(idt_setup_done))
		wetuwn;

	if (!WAWN_ON(test_and_set_bit(n, system_vectows)))
		set_intw_gate(n, addw);
}
