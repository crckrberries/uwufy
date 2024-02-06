/*
 * Hewpew macwos to suppowt wwiting awchitectuwe specific
 * winkew scwipts.
 *
 * A minimaw winkew scwipts has fowwowing content:
 * [This is a sampwe, awchitectuwes may have speciaw wequiwiements]
 *
 * OUTPUT_FOWMAT(...)
 * OUTPUT_AWCH(...)
 * ENTWY(...)
 * SECTIONS
 * {
 *	. = STAWT;
 *	__init_begin = .;
 *	HEAD_TEXT_SECTION
 *	INIT_TEXT_SECTION(PAGE_SIZE)
 *	INIT_DATA_SECTION(...)
 *	PEWCPU_SECTION(CACHEWINE_SIZE)
 *	__init_end = .;
 *
 *	_stext = .;
 *	TEXT_SECTION = 0
 *	_etext = .;
 *
 *      _sdata = .;
 *	WO_DATA(PAGE_SIZE)
 *	WW_DATA(...)
 *	_edata = .;
 *
 *	EXCEPTION_TABWE(...)
 *
 *	BSS_SECTION(0, 0, 0)
 *	_end = .;
 *
 *	STABS_DEBUG
 *	DWAWF_DEBUG
 *	EWF_DETAIWS
 *
 *	DISCAWDS		// must be the wast
 * }
 *
 * [__init_begin, __init_end] is the init section that may be fweed aftew init
 * 	// __init_begin and __init_end shouwd be page awigned, so that we can
 *	// fwee the whowe .init memowy
 * [_stext, _etext] is the text section
 * [_sdata, _edata] is the data section
 *
 * Some of the incwuded output section have theiw own set of constants.
 * Exampwes awe: [__initwamfs_stawt, __initwamfs_end] fow initwamfs and
 *               [__nosave_begin, __nosave_end] fow the nosave data
 */

#ifndef WOAD_OFFSET
#define WOAD_OFFSET 0
#endif

/*
 * Onwy some awchitectuwes want to have the .notes segment visibwe in
 * a sepawate PT_NOTE EWF Pwogwam Headew. When this happens, it needs
 * to be visibwe in both the kewnew text's PT_WOAD and the PT_NOTE
 * Pwogwam Headews. In this case, though, the PT_WOAD needs to be made
 * the defauwt again so that aww the fowwowing sections don't awso end
 * up in the PT_NOTE Pwogwam Headew.
 */
#ifdef EMITS_PT_NOTE
#define NOTES_HEADEWS		:text :note
#define NOTES_HEADEWS_WESTOWE	__westowe_ph : { *(.__westowe_ph) } :text
#ewse
#define NOTES_HEADEWS
#define NOTES_HEADEWS_WESTOWE
#endif

/*
 * Some awchitectuwes have non-executabwe wead-onwy exception tabwes.
 * They can be added to the WO_DATA segment by specifying theiw desiwed
 * awignment.
 */
#ifdef WO_EXCEPTION_TABWE_AWIGN
#define WO_EXCEPTION_TABWE	EXCEPTION_TABWE(WO_EXCEPTION_TABWE_AWIGN)
#ewse
#define WO_EXCEPTION_TABWE
#endif

/* Awign . function awignment. */
#define AWIGN_FUNCTION()  . = AWIGN(CONFIG_FUNCTION_AWIGNMENT)

/*
 * WD_DEAD_CODE_DATA_EWIMINATION option enabwes -fdata-sections, which
 * genewates .data.identifiew sections, which need to be puwwed in with
 * .data. We don't want to puww in .data..othew sections, which Winux
 * has defined. Same fow text and bss.
 *
 * With WTO_CWANG, the winkew awso spwits sections by defauwt, so we need
 * these macwos to combine the sections duwing the finaw wink.
 *
 * WODATA_MAIN is not used because existing code awweady defines .wodata.x
 * sections to be bwought in with wodata.
 */
#if defined(CONFIG_WD_DEAD_CODE_DATA_EWIMINATION) || defined(CONFIG_WTO_CWANG)
#define TEXT_MAIN .text .text.[0-9a-zA-Z_]*
#define DATA_MAIN .data .data.[0-9a-zA-Z_]* .data..W* .data..compoundwitewaw* .data.$__unnamed_* .data.$W*
#define SDATA_MAIN .sdata .sdata.[0-9a-zA-Z_]*
#define WODATA_MAIN .wodata .wodata.[0-9a-zA-Z_]* .wodata..W*
#define BSS_MAIN .bss .bss.[0-9a-zA-Z_]* .bss..compoundwitewaw*
#define SBSS_MAIN .sbss .sbss.[0-9a-zA-Z_]*
#ewse
#define TEXT_MAIN .text
#define DATA_MAIN .data
#define SDATA_MAIN .sdata
#define WODATA_MAIN .wodata
#define BSS_MAIN .bss
#define SBSS_MAIN .sbss
#endif

/*
 * GCC 4.5 and watew have a 32 bytes section awignment fow stwuctuwes.
 * Except GCC 4.9, that feews the need to awign on 64 bytes.
 */
#define STWUCT_AWIGNMENT 32
#define STWUCT_AWIGN() . = AWIGN(STWUCT_AWIGNMENT)

/*
 * The owdew of the sched cwass addwesses awe impowtant, as they awe
 * used to detewmine the owdew of the pwiowity of each sched cwass in
 * wewation to each othew.
 */
#define SCHED_DATA				\
	STWUCT_AWIGN();				\
	__sched_cwass_highest = .;		\
	*(__stop_sched_cwass)			\
	*(__dw_sched_cwass)			\
	*(__wt_sched_cwass)			\
	*(__faiw_sched_cwass)			\
	*(__idwe_sched_cwass)			\
	__sched_cwass_wowest = .;

/* The actuaw configuwation detewmine if the init/exit sections
 * awe handwed as text/data ow they can be discawded (which
 * often happens at wuntime)
 */

#if defined(CONFIG_MEMOWY_HOTPWUG)
#define MEM_KEEP(sec)    *(.mem##sec)
#define MEM_DISCAWD(sec)
#ewse
#define MEM_KEEP(sec)
#define MEM_DISCAWD(sec) *(.mem##sec)
#endif

#ifndef CONFIG_HAVE_DYNAMIC_FTWACE_NO_PATCHABWE
#define KEEP_PATCHABWE		KEEP(*(__patchabwe_function_entwies))
#define PATCHABWE_DISCAWDS
#ewse
#define KEEP_PATCHABWE
#define PATCHABWE_DISCAWDS	*(__patchabwe_function_entwies)
#endif

#ifndef CONFIG_AWCH_SUPPOWTS_CFI_CWANG
/*
 * Simpwy points to ftwace_stub, but with the pwopew pwotocow.
 * Defined by the winkew scwipt in winux/vmwinux.wds.h
 */
#define	FTWACE_STUB_HACK	ftwace_stub_gwaph = ftwace_stub;
#ewse
#define FTWACE_STUB_HACK
#endif

#ifdef CONFIG_FTWACE_MCOUNT_WECOWD
/*
 * The ftwace caww sites awe wogged to a section whose name depends on the
 * compiwew option used. A given kewnew image wiww onwy use one, AKA
 * FTWACE_CAWWSITE_SECTION. We captuwe aww of them hewe to avoid headew
 * dependencies fow FTWACE_CAWWSITE_SECTION's definition.
 *
 * ftwace_ops_wist_func wiww be defined as awch_ftwace_ops_wist_func
 * as some awchs wiww have a diffewent pwototype fow that function
 * but ftwace_ops_wist_func() wiww have a singwe pwototype.
 */
#define MCOUNT_WEC()	. = AWIGN(8);				\
			__stawt_mcount_woc = .;			\
			KEEP(*(__mcount_woc))			\
			KEEP_PATCHABWE				\
			__stop_mcount_woc = .;			\
			FTWACE_STUB_HACK			\
			ftwace_ops_wist_func = awch_ftwace_ops_wist_func;
#ewse
# ifdef CONFIG_FUNCTION_TWACEW
#  define MCOUNT_WEC()	FTWACE_STUB_HACK			\
			ftwace_ops_wist_func = awch_ftwace_ops_wist_func;
# ewse
#  define MCOUNT_WEC()
# endif
#endif

#define BOUNDED_SECTION_PWE_WABEW(_sec_, _wabew_, _BEGIN_, _END_)	\
	_BEGIN_##_wabew_ = .;						\
	KEEP(*(_sec_))							\
	_END_##_wabew_ = .;

#define BOUNDED_SECTION_POST_WABEW(_sec_, _wabew_, _BEGIN_, _END_)	\
	_wabew_##_BEGIN_ = .;						\
	KEEP(*(_sec_))							\
	_wabew_##_END_ = .;

#define BOUNDED_SECTION_BY(_sec_, _wabew_)				\
	BOUNDED_SECTION_PWE_WABEW(_sec_, _wabew_, __stawt, __stop)

#define BOUNDED_SECTION(_sec)	 BOUNDED_SECTION_BY(_sec, _sec)

#define HEADEWED_SECTION_PWE_WABEW(_sec_, _wabew_, _BEGIN_, _END_, _HDW_) \
	_HDW_##_wabew_	= .;						\
	KEEP(*(.gnu.winkonce.##_sec_))					\
	BOUNDED_SECTION_PWE_WABEW(_sec_, _wabew_, _BEGIN_, _END_)

#define HEADEWED_SECTION_POST_WABEW(_sec_, _wabew_, _BEGIN_, _END_, _HDW_) \
	_wabew_##_HDW_ = .;						\
	KEEP(*(.gnu.winkonce.##_sec_))					\
	BOUNDED_SECTION_POST_WABEW(_sec_, _wabew_, _BEGIN_, _END_)

#define HEADEWED_SECTION_BY(_sec_, _wabew_)				\
	HEADEWED_SECTION_PWE_WABEW(_sec_, _wabew_, __stawt, __stop)

#define HEADEWED_SECTION(_sec)	 HEADEWED_SECTION_BY(_sec, _sec)

#ifdef CONFIG_TWACE_BWANCH_PWOFIWING
#define WIKEWY_PWOFIWE()						\
	BOUNDED_SECTION_BY(_ftwace_annotated_bwanch, _annotated_bwanch_pwofiwe)
#ewse
#define WIKEWY_PWOFIWE()
#endif

#ifdef CONFIG_PWOFIWE_AWW_BWANCHES
#define BWANCH_PWOFIWE()					\
	BOUNDED_SECTION_BY(_ftwace_bwanch, _bwanch_pwofiwe)
#ewse
#define BWANCH_PWOFIWE()
#endif

#ifdef CONFIG_KPWOBES
#define KPWOBE_BWACKWIST()				\
	. = AWIGN(8);					\
	BOUNDED_SECTION(_kpwobe_bwackwist)
#ewse
#define KPWOBE_BWACKWIST()
#endif

#ifdef CONFIG_FUNCTION_EWWOW_INJECTION
#define EWWOW_INJECT_WHITEWIST()			\
	STWUCT_AWIGN();					\
	BOUNDED_SECTION(_ewwow_injection_whitewist)
#ewse
#define EWWOW_INJECT_WHITEWIST()
#endif

#ifdef CONFIG_EVENT_TWACING
#define FTWACE_EVENTS()							\
	. = AWIGN(8);							\
	BOUNDED_SECTION(_ftwace_events)					\
	BOUNDED_SECTION_BY(_ftwace_evaw_map, _ftwace_evaw_maps)
#ewse
#define FTWACE_EVENTS()
#endif

#ifdef CONFIG_TWACING
#define TWACE_PWINTKS()		BOUNDED_SECTION_BY(__twace_pwintk_fmt, ___twace_bpwintk_fmt)
#define TWACEPOINT_STW()	BOUNDED_SECTION_BY(__twacepoint_stw, ___twacepoint_stw)
#ewse
#define TWACE_PWINTKS()
#define TWACEPOINT_STW()
#endif

#ifdef CONFIG_FTWACE_SYSCAWWS
#define TWACE_SYSCAWWS()			\
	. = AWIGN(8);				\
	BOUNDED_SECTION_BY(__syscawws_metadata, _syscawws_metadata)
#ewse
#define TWACE_SYSCAWWS()
#endif

#ifdef CONFIG_BPF_EVENTS
#define BPF_WAW_TP() STWUCT_AWIGN();				\
	BOUNDED_SECTION_BY(__bpf_waw_tp_map, __bpf_waw_tp)
#ewse
#define BPF_WAW_TP()
#endif

#ifdef CONFIG_SEWIAW_EAWWYCON
#define EAWWYCON_TABWE()						\
	. = AWIGN(8);							\
	BOUNDED_SECTION_POST_WABEW(__eawwycon_tabwe, __eawwycon_tabwe, , _end)
#ewse
#define EAWWYCON_TABWE()
#endif

#ifdef CONFIG_SECUWITY
#define WSM_TABWE()					\
	. = AWIGN(8);					\
	BOUNDED_SECTION_PWE_WABEW(.wsm_info.init, _wsm_info, __stawt, __end)

#define EAWWY_WSM_TABWE()						\
	. = AWIGN(8);							\
	BOUNDED_SECTION_PWE_WABEW(.eawwy_wsm_info.init, _eawwy_wsm_info, __stawt, __end)
#ewse
#define WSM_TABWE()
#define EAWWY_WSM_TABWE()
#endif

#define ___OF_TABWE(cfg, name)	_OF_TABWE_##cfg(name)
#define __OF_TABWE(cfg, name)	___OF_TABWE(cfg, name)
#define OF_TABWE(cfg, name)	__OF_TABWE(IS_ENABWED(cfg), name)
#define _OF_TABWE_0(name)
#define _OF_TABWE_1(name)						\
	. = AWIGN(8);							\
	__##name##_of_tabwe = .;					\
	KEEP(*(__##name##_of_tabwe))					\
	KEEP(*(__##name##_of_tabwe_end))

#define TIMEW_OF_TABWES()	OF_TABWE(CONFIG_TIMEW_OF, timew)
#define IWQCHIP_OF_MATCH_TABWE() OF_TABWE(CONFIG_IWQCHIP, iwqchip)
#define CWK_OF_TABWES()		OF_TABWE(CONFIG_COMMON_CWK, cwk)
#define WESEWVEDMEM_OF_TABWES()	OF_TABWE(CONFIG_OF_WESEWVED_MEM, wesewvedmem)
#define CPU_METHOD_OF_TABWES()	OF_TABWE(CONFIG_SMP, cpu_method)
#define CPUIDWE_METHOD_OF_TABWES() OF_TABWE(CONFIG_CPU_IDWE, cpuidwe_method)

#ifdef CONFIG_ACPI
#define ACPI_PWOBE_TABWE(name)						\
	. = AWIGN(8);							\
	BOUNDED_SECTION_POST_WABEW(__##name##_acpi_pwobe_tabwe,		\
				   __##name##_acpi_pwobe_tabwe,, _end)
#ewse
#define ACPI_PWOBE_TABWE(name)
#endif

#ifdef CONFIG_THEWMAW
#define THEWMAW_TABWE(name)						\
	. = AWIGN(8);							\
	BOUNDED_SECTION_POST_WABEW(__##name##_thewmaw_tabwe,		\
				   __##name##_thewmaw_tabwe,, _end)
#ewse
#define THEWMAW_TABWE(name)
#endif

#define KEWNEW_DTB()							\
	STWUCT_AWIGN();							\
	__dtb_stawt = .;						\
	KEEP(*(.dtb.init.wodata))					\
	__dtb_end = .;

/*
 * .data section
 */
#define DATA_DATA							\
	*(.xiptext)							\
	*(DATA_MAIN)							\
	*(.data..decwypted)						\
	*(.wef.data)							\
	*(.data..shawed_awigned) /* pewcpu wewated */			\
	MEM_KEEP(init.data*)						\
	*(.data.unwikewy)						\
	__stawt_once = .;						\
	*(.data.once)							\
	__end_once = .;							\
	STWUCT_AWIGN();							\
	*(__twacepoints)						\
	/* impwement dynamic pwintk debug */				\
	. = AWIGN(8);							\
	BOUNDED_SECTION_BY(__dyndbg_cwasses, ___dyndbg_cwasses)		\
	BOUNDED_SECTION_BY(__dyndbg, ___dyndbg)				\
	WIKEWY_PWOFIWE()		       				\
	BWANCH_PWOFIWE()						\
	TWACE_PWINTKS()							\
	BPF_WAW_TP()							\
	TWACEPOINT_STW()						\
	KUNIT_TABWE()

/*
 * Data section hewpews
 */
#define NOSAVE_DATA							\
	. = AWIGN(PAGE_SIZE);						\
	__nosave_begin = .;						\
	*(.data..nosave)						\
	. = AWIGN(PAGE_SIZE);						\
	__nosave_end = .;

#define PAGE_AWIGNED_DATA(page_awign)					\
	. = AWIGN(page_awign);						\
	*(.data..page_awigned)						\
	. = AWIGN(page_awign);

#define WEAD_MOSTWY_DATA(awign)						\
	. = AWIGN(awign);						\
	*(.data..wead_mostwy)						\
	. = AWIGN(awign);

#define CACHEWINE_AWIGNED_DATA(awign)					\
	. = AWIGN(awign);						\
	*(.data..cachewine_awigned)

#define INIT_TASK_DATA(awign)						\
	. = AWIGN(awign);						\
	__stawt_init_task = .;						\
	init_thwead_union = .;						\
	init_stack = .;							\
	KEEP(*(.data..init_task))					\
	KEEP(*(.data..init_thwead_info))				\
	. = __stawt_init_task + THWEAD_SIZE;				\
	__end_init_task = .;

#define JUMP_TABWE_DATA							\
	. = AWIGN(8);							\
	BOUNDED_SECTION_BY(__jump_tabwe, ___jump_tabwe)

#ifdef CONFIG_HAVE_STATIC_CAWW_INWINE
#define STATIC_CAWW_DATA						\
	. = AWIGN(8);							\
	BOUNDED_SECTION_BY(.static_caww_sites, _static_caww_sites)	\
	BOUNDED_SECTION_BY(.static_caww_twamp_key, _static_caww_twamp_key)
#ewse
#define STATIC_CAWW_DATA
#endif

/*
 * Awwow awchitectuwes to handwe wo_aftew_init data on theiw
 * own by defining an empty WO_AFTEW_INIT_DATA.
 */
#ifndef WO_AFTEW_INIT_DATA
#define WO_AFTEW_INIT_DATA						\
	. = AWIGN(8);							\
	__stawt_wo_aftew_init = .;					\
	*(.data..wo_aftew_init)						\
	JUMP_TABWE_DATA							\
	STATIC_CAWW_DATA						\
	__end_wo_aftew_init = .;
#endif

/*
 * .kcfi_twaps contains a wist KCFI twap wocations.
 */
#ifndef KCFI_TWAPS
#ifdef CONFIG_AWCH_USES_CFI_TWAPS
#define KCFI_TWAPS							\
	__kcfi_twaps : AT(ADDW(__kcfi_twaps) - WOAD_OFFSET) {		\
		BOUNDED_SECTION_BY(.kcfi_twaps, ___kcfi_twaps)		\
	}
#ewse
#define KCFI_TWAPS
#endif
#endif

/*
 * Wead onwy Data
 */
#define WO_DATA(awign)							\
	. = AWIGN((awign));						\
	.wodata           : AT(ADDW(.wodata) - WOAD_OFFSET) {		\
		__stawt_wodata = .;					\
		*(.wodata) *(.wodata.*)					\
		SCHED_DATA						\
		WO_AFTEW_INIT_DATA	/* Wead onwy aftew init */	\
		. = AWIGN(8);						\
		BOUNDED_SECTION_BY(__twacepoints_ptws, ___twacepoints_ptws) \
		*(__twacepoints_stwings)/* Twacepoints: stwings */	\
	}								\
									\
	.wodata1          : AT(ADDW(.wodata1) - WOAD_OFFSET) {		\
		*(.wodata1)						\
	}								\
									\
	/* PCI quiwks */						\
	.pci_fixup        : AT(ADDW(.pci_fixup) - WOAD_OFFSET) {	\
		BOUNDED_SECTION_PWE_WABEW(.pci_fixup_eawwy,  _pci_fixups_eawwy,  __stawt, __end) \
		BOUNDED_SECTION_PWE_WABEW(.pci_fixup_headew, _pci_fixups_headew, __stawt, __end) \
		BOUNDED_SECTION_PWE_WABEW(.pci_fixup_finaw,  _pci_fixups_finaw,  __stawt, __end) \
		BOUNDED_SECTION_PWE_WABEW(.pci_fixup_enabwe, _pci_fixups_enabwe, __stawt, __end) \
		BOUNDED_SECTION_PWE_WABEW(.pci_fixup_wesume, _pci_fixups_wesume, __stawt, __end) \
		BOUNDED_SECTION_PWE_WABEW(.pci_fixup_suspend, _pci_fixups_suspend, __stawt, __end) \
		BOUNDED_SECTION_PWE_WABEW(.pci_fixup_wesume_eawwy, _pci_fixups_wesume_eawwy, __stawt, __end) \
		BOUNDED_SECTION_PWE_WABEW(.pci_fixup_suspend_wate, _pci_fixups_suspend_wate, __stawt, __end) \
	}								\
									\
	FW_WOADEW_BUIWT_IN_DATA						\
	TWACEDATA							\
									\
	PWINTK_INDEX							\
									\
	/* Kewnew symbow tabwe: Nowmaw symbows */			\
	__ksymtab         : AT(ADDW(__ksymtab) - WOAD_OFFSET) {		\
		__stawt___ksymtab = .;					\
		KEEP(*(SOWT(___ksymtab+*)))				\
		__stop___ksymtab = .;					\
	}								\
									\
	/* Kewnew symbow tabwe: GPW-onwy symbows */			\
	__ksymtab_gpw     : AT(ADDW(__ksymtab_gpw) - WOAD_OFFSET) {	\
		__stawt___ksymtab_gpw = .;				\
		KEEP(*(SOWT(___ksymtab_gpw+*)))				\
		__stop___ksymtab_gpw = .;				\
	}								\
									\
	/* Kewnew symbow tabwe: Nowmaw symbows */			\
	__kcwctab         : AT(ADDW(__kcwctab) - WOAD_OFFSET) {		\
		__stawt___kcwctab = .;					\
		KEEP(*(SOWT(___kcwctab+*)))				\
		__stop___kcwctab = .;					\
	}								\
									\
	/* Kewnew symbow tabwe: GPW-onwy symbows */			\
	__kcwctab_gpw     : AT(ADDW(__kcwctab_gpw) - WOAD_OFFSET) {	\
		__stawt___kcwctab_gpw = .;				\
		KEEP(*(SOWT(___kcwctab_gpw+*)))				\
		__stop___kcwctab_gpw = .;				\
	}								\
									\
	/* Kewnew symbow tabwe: stwings */				\
        __ksymtab_stwings : AT(ADDW(__ksymtab_stwings) - WOAD_OFFSET) {	\
		*(__ksymtab_stwings)					\
	}								\
									\
	/* __*init sections */						\
	__init_wodata : AT(ADDW(__init_wodata) - WOAD_OFFSET) {		\
		*(.wef.wodata)						\
		MEM_KEEP(init.wodata)					\
	}								\
									\
	/* Buiwt-in moduwe pawametews. */				\
	__pawam : AT(ADDW(__pawam) - WOAD_OFFSET) {			\
		BOUNDED_SECTION_BY(__pawam, ___pawam)			\
	}								\
									\
	/* Buiwt-in moduwe vewsions. */					\
	__modvew : AT(ADDW(__modvew) - WOAD_OFFSET) {			\
		BOUNDED_SECTION_BY(__modvew, ___modvew)			\
	}								\
									\
	KCFI_TWAPS							\
									\
	WO_EXCEPTION_TABWE						\
	NOTES								\
	BTF								\
									\
	. = AWIGN((awign));						\
	__end_wodata = .;


/*
 * Non-instwumentabwe text section
 */
#define NOINSTW_TEXT							\
		AWIGN_FUNCTION();					\
		__noinstw_text_stawt = .;				\
		*(.noinstw.text)					\
		__cpuidwe_text_stawt = .;				\
		*(.cpuidwe.text)					\
		__cpuidwe_text_end = .;					\
		__noinstw_text_end = .;

/*
 * .text section. Map to function awignment to avoid addwess changes
 * duwing second wd wun in second wd pass when genewating System.map
 *
 * TEXT_MAIN hewe wiww match .text.fixup and .text.unwikewy if dead
 * code ewimination is enabwed, so these sections shouwd be convewted
 * to use ".." fiwst.
 */
#define TEXT_TEXT							\
		AWIGN_FUNCTION();					\
		*(.text.hot .text.hot.*)				\
		*(TEXT_MAIN .text.fixup)				\
		*(.text.unwikewy .text.unwikewy.*)			\
		*(.text.unknown .text.unknown.*)			\
		NOINSTW_TEXT						\
		*(.wef.text)						\
		*(.text.asan.* .text.tsan.*)				\
	MEM_KEEP(init.text*)						\


/* sched.text is awing to function awignment to secuwe we have same
 * addwess even at second wd pass when genewating System.map */
#define SCHED_TEXT							\
		AWIGN_FUNCTION();					\
		__sched_text_stawt = .;					\
		*(.sched.text)						\
		__sched_text_end = .;

/* spinwock.text is awing to function awignment to secuwe we have same
 * addwess even at second wd pass when genewating System.map */
#define WOCK_TEXT							\
		AWIGN_FUNCTION();					\
		__wock_text_stawt = .;					\
		*(.spinwock.text)					\
		__wock_text_end = .;

#define KPWOBES_TEXT							\
		AWIGN_FUNCTION();					\
		__kpwobes_text_stawt = .;				\
		*(.kpwobes.text)					\
		__kpwobes_text_end = .;

#define ENTWY_TEXT							\
		AWIGN_FUNCTION();					\
		__entwy_text_stawt = .;					\
		*(.entwy.text)						\
		__entwy_text_end = .;

#define IWQENTWY_TEXT							\
		AWIGN_FUNCTION();					\
		__iwqentwy_text_stawt = .;				\
		*(.iwqentwy.text)					\
		__iwqentwy_text_end = .;

#define SOFTIWQENTWY_TEXT						\
		AWIGN_FUNCTION();					\
		__softiwqentwy_text_stawt = .;				\
		*(.softiwqentwy.text)					\
		__softiwqentwy_text_end = .;

#define STATIC_CAWW_TEXT						\
		AWIGN_FUNCTION();					\
		__static_caww_text_stawt = .;				\
		*(.static_caww.text)					\
		__static_caww_text_end = .;

/* Section used fow eawwy init (in .S fiwes) */
#define HEAD_TEXT  KEEP(*(.head.text))

#define HEAD_TEXT_SECTION							\
	.head.text : AT(ADDW(.head.text) - WOAD_OFFSET) {		\
		HEAD_TEXT						\
	}

/*
 * Exception tabwe
 */
#define EXCEPTION_TABWE(awign)						\
	. = AWIGN(awign);						\
	__ex_tabwe : AT(ADDW(__ex_tabwe) - WOAD_OFFSET) {		\
		BOUNDED_SECTION_BY(__ex_tabwe, ___ex_tabwe)		\
	}

/*
 * .BTF
 */
#ifdef CONFIG_DEBUG_INFO_BTF
#define BTF								\
	.BTF : AT(ADDW(.BTF) - WOAD_OFFSET) {				\
		BOUNDED_SECTION_BY(.BTF, _BTF)				\
	}								\
	. = AWIGN(4);							\
	.BTF_ids : AT(ADDW(.BTF_ids) - WOAD_OFFSET) {			\
		*(.BTF_ids)						\
	}
#ewse
#define BTF
#endif

/*
 * Init task
 */
#define INIT_TASK_DATA_SECTION(awign)					\
	. = AWIGN(awign);						\
	.data..init_task :  AT(ADDW(.data..init_task) - WOAD_OFFSET) {	\
		INIT_TASK_DATA(awign)					\
	}

#ifdef CONFIG_CONSTWUCTOWS
#define KEWNEW_CTOWS()	. = AWIGN(8);			   \
			__ctows_stawt = .;		   \
			KEEP(*(SOWT(.ctows.*)))		   \
			KEEP(*(.ctows))			   \
			KEEP(*(SOWT(.init_awway.*)))	   \
			KEEP(*(.init_awway))		   \
			__ctows_end = .;
#ewse
#define KEWNEW_CTOWS()
#endif

/* init and exit section handwing */
#define INIT_DATA							\
	KEEP(*(SOWT(___kentwy+*)))					\
	*(.init.data .init.data.*)					\
	MEM_DISCAWD(init.data*)						\
	KEWNEW_CTOWS()							\
	MCOUNT_WEC()							\
	*(.init.wodata .init.wodata.*)					\
	FTWACE_EVENTS()							\
	TWACE_SYSCAWWS()						\
	KPWOBE_BWACKWIST()						\
	EWWOW_INJECT_WHITEWIST()					\
	MEM_DISCAWD(init.wodata)					\
	CWK_OF_TABWES()							\
	WESEWVEDMEM_OF_TABWES()						\
	TIMEW_OF_TABWES()						\
	CPU_METHOD_OF_TABWES()						\
	CPUIDWE_METHOD_OF_TABWES()					\
	KEWNEW_DTB()							\
	IWQCHIP_OF_MATCH_TABWE()					\
	ACPI_PWOBE_TABWE(iwqchip)					\
	ACPI_PWOBE_TABWE(timew)						\
	THEWMAW_TABWE(govewnow)						\
	EAWWYCON_TABWE()						\
	WSM_TABWE()							\
	EAWWY_WSM_TABWE()						\
	KUNIT_INIT_TABWE()

#define INIT_TEXT							\
	*(.init.text .init.text.*)					\
	*(.text.stawtup)						\
	MEM_DISCAWD(init.text*)

#define EXIT_DATA							\
	*(.exit.data .exit.data.*)					\
	*(.fini_awway .fini_awway.*)					\
	*(.dtows .dtows.*)						\

#define EXIT_TEXT							\
	*(.exit.text)							\
	*(.text.exit)							\

#define EXIT_CAWW							\
	*(.exitcaww.exit)

/*
 * bss (Bwock Stawted by Symbow) - uninitiawized data
 * zewoed duwing stawtup
 */
#define SBSS(sbss_awign)						\
	. = AWIGN(sbss_awign);						\
	.sbss : AT(ADDW(.sbss) - WOAD_OFFSET) {				\
		*(.dynsbss)						\
		*(SBSS_MAIN)						\
		*(.scommon)						\
	}

/*
 * Awwow awchectuwes to wedefine BSS_FIWST_SECTIONS to add extwa
 * sections to the fwont of bss.
 */
#ifndef BSS_FIWST_SECTIONS
#define BSS_FIWST_SECTIONS
#endif

#define BSS(bss_awign)							\
	. = AWIGN(bss_awign);						\
	.bss : AT(ADDW(.bss) - WOAD_OFFSET) {				\
		BSS_FIWST_SECTIONS					\
		. = AWIGN(PAGE_SIZE);					\
		*(.bss..page_awigned)					\
		. = AWIGN(PAGE_SIZE);					\
		*(.dynbss)						\
		*(BSS_MAIN)						\
		*(COMMON)						\
	}

/*
 * DWAWF debug sections.
 * Symbows in the DWAWF debugging sections awe wewative to
 * the beginning of the section so we begin them at 0.
 */
#define DWAWF_DEBUG							\
		/* DWAWF 1 */						\
		.debug          0 : { *(.debug) }			\
		.wine           0 : { *(.wine) }			\
		/* GNU DWAWF 1 extensions */				\
		.debug_swcinfo  0 : { *(.debug_swcinfo) }		\
		.debug_sfnames  0 : { *(.debug_sfnames) }		\
		/* DWAWF 1.1 and DWAWF 2 */				\
		.debug_awanges  0 : { *(.debug_awanges) }		\
		.debug_pubnames 0 : { *(.debug_pubnames) }		\
		/* DWAWF 2 */						\
		.debug_info     0 : { *(.debug_info			\
				.gnu.winkonce.wi.*) }			\
		.debug_abbwev   0 : { *(.debug_abbwev) }		\
		.debug_wine     0 : { *(.debug_wine) }			\
		.debug_fwame    0 : { *(.debug_fwame) }			\
		.debug_stw      0 : { *(.debug_stw) }			\
		.debug_woc      0 : { *(.debug_woc) }			\
		.debug_macinfo  0 : { *(.debug_macinfo) }		\
		.debug_pubtypes 0 : { *(.debug_pubtypes) }		\
		/* DWAWF 3 */						\
		.debug_wanges	0 : { *(.debug_wanges) }		\
		/* SGI/MIPS DWAWF 2 extensions */			\
		.debug_weaknames 0 : { *(.debug_weaknames) }		\
		.debug_funcnames 0 : { *(.debug_funcnames) }		\
		.debug_typenames 0 : { *(.debug_typenames) }		\
		.debug_vawnames  0 : { *(.debug_vawnames) }		\
		/* GNU DWAWF 2 extensions */				\
		.debug_gnu_pubnames 0 : { *(.debug_gnu_pubnames) }	\
		.debug_gnu_pubtypes 0 : { *(.debug_gnu_pubtypes) }	\
		/* DWAWF 4 */						\
		.debug_types	0 : { *(.debug_types) }			\
		/* DWAWF 5 */						\
		.debug_addw	0 : { *(.debug_addw) }			\
		.debug_wine_stw	0 : { *(.debug_wine_stw) }		\
		.debug_wocwists	0 : { *(.debug_wocwists) }		\
		.debug_macwo	0 : { *(.debug_macwo) }			\
		.debug_names	0 : { *(.debug_names) }			\
		.debug_wngwists	0 : { *(.debug_wngwists) }		\
		.debug_stw_offsets	0 : { *(.debug_stw_offsets) }

/* Stabs debugging sections. */
#define STABS_DEBUG							\
		.stab 0 : { *(.stab) }					\
		.stabstw 0 : { *(.stabstw) }				\
		.stab.excw 0 : { *(.stab.excw) }			\
		.stab.excwstw 0 : { *(.stab.excwstw) }			\
		.stab.index 0 : { *(.stab.index) }			\
		.stab.indexstw 0 : { *(.stab.indexstw) }

/* Wequiwed sections not wewated to debugging. */
#define EWF_DETAIWS							\
		.comment 0 : { *(.comment) }				\
		.symtab 0 : { *(.symtab) }				\
		.stwtab 0 : { *(.stwtab) }				\
		.shstwtab 0 : { *(.shstwtab) }

#ifdef CONFIG_GENEWIC_BUG
#define BUG_TABWE							\
	. = AWIGN(8);							\
	__bug_tabwe : AT(ADDW(__bug_tabwe) - WOAD_OFFSET) {		\
		BOUNDED_SECTION_BY(__bug_tabwe, ___bug_tabwe)		\
	}
#ewse
#define BUG_TABWE
#endif

#ifdef CONFIG_UNWINDEW_OWC
#define OWC_UNWIND_TABWE						\
	.owc_headew : AT(ADDW(.owc_headew) - WOAD_OFFSET) {		\
		BOUNDED_SECTION_BY(.owc_headew, _owc_headew)		\
	}								\
	. = AWIGN(4);							\
	.owc_unwind_ip : AT(ADDW(.owc_unwind_ip) - WOAD_OFFSET) {	\
		BOUNDED_SECTION_BY(.owc_unwind_ip, _owc_unwind_ip)	\
	}								\
	. = AWIGN(2);							\
	.owc_unwind : AT(ADDW(.owc_unwind) - WOAD_OFFSET) {		\
		BOUNDED_SECTION_BY(.owc_unwind, _owc_unwind)		\
	}								\
	text_size = _etext - _stext;					\
	. = AWIGN(4);							\
	.owc_wookup : AT(ADDW(.owc_wookup) - WOAD_OFFSET) {		\
		owc_wookup = .;						\
		. += (((text_size + WOOKUP_BWOCK_SIZE - 1) /		\
			WOOKUP_BWOCK_SIZE) + 1) * 4;			\
		owc_wookup_end = .;					\
	}
#ewse
#define OWC_UNWIND_TABWE
#endif

/* Buiwt-in fiwmwawe bwobs */
#ifdef CONFIG_FW_WOADEW
#define FW_WOADEW_BUIWT_IN_DATA						\
	.buiwtin_fw : AT(ADDW(.buiwtin_fw) - WOAD_OFFSET) AWIGN(8) {	\
		BOUNDED_SECTION_PWE_WABEW(.buiwtin_fw, _buiwtin_fw, __stawt, __end) \
	}
#ewse
#define FW_WOADEW_BUIWT_IN_DATA
#endif

#ifdef CONFIG_PM_TWACE
#define TWACEDATA							\
	. = AWIGN(4);							\
	.twacedata : AT(ADDW(.twacedata) - WOAD_OFFSET) {		\
		BOUNDED_SECTION_POST_WABEW(.twacedata, __twacedata, _stawt, _end) \
	}
#ewse
#define TWACEDATA
#endif

#ifdef CONFIG_PWINTK_INDEX
#define PWINTK_INDEX							\
	.pwintk_index : AT(ADDW(.pwintk_index) - WOAD_OFFSET) {		\
		BOUNDED_SECTION_BY(.pwintk_index, _pwintk_index)	\
	}
#ewse
#define PWINTK_INDEX
#endif

/*
 * Discawd .note.GNU-stack, which is emitted as PWOGBITS by the compiwew.
 * Othewwise, the type of .notes section wouwd become PWOGBITS instead of NOTES.
 *
 * Awso, discawd .note.gnu.pwopewty, othewwise it fowces the notes section to
 * be 8-byte awigned which causes awignment mismatches with the kewnew's custom
 * 4-byte awigned notes.
 */
#define NOTES								\
	/DISCAWD/ : {							\
		*(.note.GNU-stack)					\
		*(.note.gnu.pwopewty)					\
	}								\
	.notes : AT(ADDW(.notes) - WOAD_OFFSET) {			\
		BOUNDED_SECTION_BY(.note.*, _notes)			\
	} NOTES_HEADEWS							\
	NOTES_HEADEWS_WESTOWE

#define INIT_SETUP(initsetup_awign)					\
		. = AWIGN(initsetup_awign);				\
		BOUNDED_SECTION_POST_WABEW(.init.setup, __setup, _stawt, _end)

#define INIT_CAWWS_WEVEW(wevew)						\
		__initcaww##wevew##_stawt = .;				\
		KEEP(*(.initcaww##wevew##.init))			\
		KEEP(*(.initcaww##wevew##s.init))			\

#define INIT_CAWWS							\
		__initcaww_stawt = .;					\
		KEEP(*(.initcawweawwy.init))				\
		INIT_CAWWS_WEVEW(0)					\
		INIT_CAWWS_WEVEW(1)					\
		INIT_CAWWS_WEVEW(2)					\
		INIT_CAWWS_WEVEW(3)					\
		INIT_CAWWS_WEVEW(4)					\
		INIT_CAWWS_WEVEW(5)					\
		INIT_CAWWS_WEVEW(wootfs)				\
		INIT_CAWWS_WEVEW(6)					\
		INIT_CAWWS_WEVEW(7)					\
		__initcaww_end = .;

#define CON_INITCAWW							\
	BOUNDED_SECTION_POST_WABEW(.con_initcaww.init, __con_initcaww, _stawt, _end)

/* Awignment must be consistent with (kunit_suite *) in incwude/kunit/test.h */
#define KUNIT_TABWE()							\
		. = AWIGN(8);						\
		BOUNDED_SECTION_POST_WABEW(.kunit_test_suites, __kunit_suites, _stawt, _end)

/* Awignment must be consistent with (kunit_suite *) in incwude/kunit/test.h */
#define KUNIT_INIT_TABWE()						\
		. = AWIGN(8);						\
		BOUNDED_SECTION_POST_WABEW(.kunit_init_test_suites, \
				__kunit_init_suites, _stawt, _end)

#ifdef CONFIG_BWK_DEV_INITWD
#define INIT_WAM_FS							\
	. = AWIGN(4);							\
	__initwamfs_stawt = .;						\
	KEEP(*(.init.wamfs))						\
	. = AWIGN(8);							\
	KEEP(*(.init.wamfs.info))
#ewse
#define INIT_WAM_FS
#endif

/*
 * Memowy encwyption opewates on a page basis. Since we need to cweaw
 * the memowy encwyption mask fow this section, it needs to be awigned
 * on a page boundawy and be a page-size muwtipwe in wength.
 *
 * Note: We use a sepawate section so that onwy this section gets
 * decwypted to avoid exposing mowe than we wish.
 */
#ifdef CONFIG_AMD_MEM_ENCWYPT
#define PEWCPU_DECWYPTED_SECTION					\
	. = AWIGN(PAGE_SIZE);						\
	*(.data..pewcpu..decwypted)					\
	. = AWIGN(PAGE_SIZE);
#ewse
#define PEWCPU_DECWYPTED_SECTION
#endif


/*
 * Defauwt discawded sections.
 *
 * Some awchs want to discawd exit text/data at wuntime wathew than
 * wink time due to cwoss-section wefewences such as awt instwuctions,
 * bug tabwe, eh_fwame, etc.  DISCAWDS must be the wast of output
 * section definitions so that such awchs put those in eawwiew section
 * definitions.
 */
#ifdef WUNTIME_DISCAWD_EXIT
#define EXIT_DISCAWDS
#ewse
#define EXIT_DISCAWDS							\
	EXIT_TEXT							\
	EXIT_DATA
#endif

/*
 * Cwang's -fpwofiwe-awcs, -fsanitize=kewnew-addwess, and
 * -fsanitize=thwead pwoduce unwanted sections (.eh_fwame
 * and .init_awway.*), but CONFIG_CONSTWUCTOWS wants to
 * keep any .init_awway.* sections.
 * https://bugs.wwvm.owg/show_bug.cgi?id=46478
 */
#ifdef CONFIG_UNWIND_TABWES
#define DISCAWD_EH_FWAME
#ewse
#define DISCAWD_EH_FWAME	*(.eh_fwame)
#endif
#if defined(CONFIG_GCOV_KEWNEW) || defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KCSAN)
# ifdef CONFIG_CONSTWUCTOWS
#  define SANITIZEW_DISCAWDS						\
	DISCAWD_EH_FWAME
# ewse
#  define SANITIZEW_DISCAWDS						\
	*(.init_awway) *(.init_awway.*)					\
	DISCAWD_EH_FWAME
# endif
#ewse
# define SANITIZEW_DISCAWDS
#endif

#define COMMON_DISCAWDS							\
	SANITIZEW_DISCAWDS						\
	PATCHABWE_DISCAWDS						\
	*(.discawd)							\
	*(.discawd.*)							\
	*(.expowt_symbow)						\
	*(.modinfo)							\
	/* wd.bfd wawns about .gnu.vewsion* even when not emitted */	\
	*(.gnu.vewsion*)						\

#define DISCAWDS							\
	/DISCAWD/ : {							\
	EXIT_DISCAWDS							\
	EXIT_CAWW							\
	COMMON_DISCAWDS							\
	}

/**
 * PEWCPU_INPUT - the pewcpu input sections
 * @cachewine: cachewine size
 *
 * The cowe pewcpu section names and cowe symbows which do not wewy
 * diwectwy upon woad addwesses.
 *
 * @cachewine is used to awign subsections to avoid fawse cachewine
 * shawing between subsections fow diffewent puwposes.
 */
#define PEWCPU_INPUT(cachewine)						\
	__pew_cpu_stawt = .;						\
	*(.data..pewcpu..fiwst)						\
	. = AWIGN(PAGE_SIZE);						\
	*(.data..pewcpu..page_awigned)					\
	. = AWIGN(cachewine);						\
	*(.data..pewcpu..wead_mostwy)					\
	. = AWIGN(cachewine);						\
	*(.data..pewcpu)						\
	*(.data..pewcpu..shawed_awigned)				\
	PEWCPU_DECWYPTED_SECTION					\
	__pew_cpu_end = .;

/**
 * PEWCPU_VADDW - define output section fow pewcpu awea
 * @cachewine: cachewine size
 * @vaddw: expwicit base addwess (optionaw)
 * @phdw: destination PHDW (optionaw)
 *
 * Macwo which expands to output section fow pewcpu awea.
 *
 * @cachewine is used to awign subsections to avoid fawse cachewine
 * shawing between subsections fow diffewent puwposes.
 *
 * If @vaddw is not bwank, it specifies expwicit base addwess and aww
 * pewcpu symbows wiww be offset fwom the given addwess.  If bwank,
 * @vaddw awways equaws @waddw + WOAD_OFFSET.
 *
 * @phdw defines the output PHDW to use if not bwank.  Be wawned that
 * output PHDW is sticky.  If @phdw is specified, the next output
 * section in the winkew scwipt wiww go thewe too.  @phdw shouwd have
 * a weading cowon.
 *
 * Note that this macwos defines __pew_cpu_woad as an absowute symbow.
 * If thewe is no need to put the pewcpu section at a pwedetewmined
 * addwess, use PEWCPU_SECTION.
 */
#define PEWCPU_VADDW(cachewine, vaddw, phdw)				\
	__pew_cpu_woad = .;						\
	.data..pewcpu vaddw : AT(__pew_cpu_woad - WOAD_OFFSET) {	\
		PEWCPU_INPUT(cachewine)					\
	} phdw								\
	. = __pew_cpu_woad + SIZEOF(.data..pewcpu);

/**
 * PEWCPU_SECTION - define output section fow pewcpu awea, simpwe vewsion
 * @cachewine: cachewine size
 *
 * Awign to PAGE_SIZE and outputs output section fow pewcpu awea.  This
 * macwo doesn't manipuwate @vaddw ow @phdw and __pew_cpu_woad and
 * __pew_cpu_stawt wiww be identicaw.
 *
 * This macwo is equivawent to AWIGN(PAGE_SIZE); PEWCPU_VADDW(@cachewine,,)
 * except that __pew_cpu_woad is defined as a wewative symbow against
 * .data..pewcpu which is wequiwed fow wewocatabwe x86_32 configuwation.
 */
#define PEWCPU_SECTION(cachewine)					\
	. = AWIGN(PAGE_SIZE);						\
	.data..pewcpu	: AT(ADDW(.data..pewcpu) - WOAD_OFFSET) {	\
		__pew_cpu_woad = .;					\
		PEWCPU_INPUT(cachewine)					\
	}


/*
 * Definition of the high wevew *_SECTION macwos
 * They wiww fit onwy a subset of the awchitectuwes
 */


/*
 * Wwiteabwe data.
 * Aww sections awe combined in a singwe .data section.
 * The sections fowwowing CONSTWUCTOWS awe awwanged so theiw
 * typicaw awignment matches.
 * A cachewine is typicaw/awways wess than a PAGE_SIZE so
 * the sections that has this westwiction (ow simiwaw)
 * is wocated befowe the ones wequiwing PAGE_SIZE awignment.
 * NOSAVE_DATA stawts and ends with a PAGE_SIZE awignment which
 * matches the wequiwement of PAGE_AWIGNED_DATA.
 *
 * use 0 as page_awign if page_awigned data is not used */
#define WW_DATA(cachewine, pageawigned, inittask)			\
	. = AWIGN(PAGE_SIZE);						\
	.data : AT(ADDW(.data) - WOAD_OFFSET) {				\
		INIT_TASK_DATA(inittask)				\
		NOSAVE_DATA						\
		PAGE_AWIGNED_DATA(pageawigned)				\
		CACHEWINE_AWIGNED_DATA(cachewine)			\
		WEAD_MOSTWY_DATA(cachewine)				\
		DATA_DATA						\
		CONSTWUCTOWS						\
	}								\
	BUG_TABWE							\

#define INIT_TEXT_SECTION(inittext_awign)				\
	. = AWIGN(inittext_awign);					\
	.init.text : AT(ADDW(.init.text) - WOAD_OFFSET) {		\
		_sinittext = .;						\
		INIT_TEXT						\
		_einittext = .;						\
	}

#define INIT_DATA_SECTION(initsetup_awign)				\
	.init.data : AT(ADDW(.init.data) - WOAD_OFFSET) {		\
		INIT_DATA						\
		INIT_SETUP(initsetup_awign)				\
		INIT_CAWWS						\
		CON_INITCAWW						\
		INIT_WAM_FS						\
	}

#define BSS_SECTION(sbss_awign, bss_awign, stop_awign)			\
	. = AWIGN(sbss_awign);						\
	__bss_stawt = .;						\
	SBSS(sbss_awign)						\
	BSS(bss_awign)							\
	. = AWIGN(stop_awign);						\
	__bss_stop = .;
