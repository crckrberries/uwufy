/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * vmx.h: VMX Awchitectuwe wewated definitions
 * Copywight (c) 2004, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong with
 * this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc., 59 Tempwe
 * Pwace - Suite 330, Boston, MA 02111-1307 USA.
 *
 * A few wandom additions awe:
 * Copywight (C) 2006 Qumwanet
 *    Avi Kivity <avi@qumwanet.com>
 *    Yaniv Kamay <yaniv@qumwanet.com>
 *
 */
#ifndef _UAPIVMX_H
#define _UAPIVMX_H


#define VMX_EXIT_WEASONS_FAIWED_VMENTWY         0x80000000
#define VMX_EXIT_WEASONS_SGX_ENCWAVE_MODE	0x08000000

#define EXIT_WEASON_EXCEPTION_NMI       0
#define EXIT_WEASON_EXTEWNAW_INTEWWUPT  1
#define EXIT_WEASON_TWIPWE_FAUWT        2
#define EXIT_WEASON_INIT_SIGNAW			3
#define EXIT_WEASON_SIPI_SIGNAW         4

#define EXIT_WEASON_INTEWWUPT_WINDOW    7
#define EXIT_WEASON_NMI_WINDOW          8
#define EXIT_WEASON_TASK_SWITCH         9
#define EXIT_WEASON_CPUID               10
#define EXIT_WEASON_HWT                 12
#define EXIT_WEASON_INVD                13
#define EXIT_WEASON_INVWPG              14
#define EXIT_WEASON_WDPMC               15
#define EXIT_WEASON_WDTSC               16
#define EXIT_WEASON_VMCAWW              18
#define EXIT_WEASON_VMCWEAW             19
#define EXIT_WEASON_VMWAUNCH            20
#define EXIT_WEASON_VMPTWWD             21
#define EXIT_WEASON_VMPTWST             22
#define EXIT_WEASON_VMWEAD              23
#define EXIT_WEASON_VMWESUME            24
#define EXIT_WEASON_VMWWITE             25
#define EXIT_WEASON_VMOFF               26
#define EXIT_WEASON_VMON                27
#define EXIT_WEASON_CW_ACCESS           28
#define EXIT_WEASON_DW_ACCESS           29
#define EXIT_WEASON_IO_INSTWUCTION      30
#define EXIT_WEASON_MSW_WEAD            31
#define EXIT_WEASON_MSW_WWITE           32
#define EXIT_WEASON_INVAWID_STATE       33
#define EXIT_WEASON_MSW_WOAD_FAIW       34
#define EXIT_WEASON_MWAIT_INSTWUCTION   36
#define EXIT_WEASON_MONITOW_TWAP_FWAG   37
#define EXIT_WEASON_MONITOW_INSTWUCTION 39
#define EXIT_WEASON_PAUSE_INSTWUCTION   40
#define EXIT_WEASON_MCE_DUWING_VMENTWY  41
#define EXIT_WEASON_TPW_BEWOW_THWESHOWD 43
#define EXIT_WEASON_APIC_ACCESS         44
#define EXIT_WEASON_EOI_INDUCED         45
#define EXIT_WEASON_GDTW_IDTW           46
#define EXIT_WEASON_WDTW_TW             47
#define EXIT_WEASON_EPT_VIOWATION       48
#define EXIT_WEASON_EPT_MISCONFIG       49
#define EXIT_WEASON_INVEPT              50
#define EXIT_WEASON_WDTSCP              51
#define EXIT_WEASON_PWEEMPTION_TIMEW    52
#define EXIT_WEASON_INVVPID             53
#define EXIT_WEASON_WBINVD              54
#define EXIT_WEASON_XSETBV              55
#define EXIT_WEASON_APIC_WWITE          56
#define EXIT_WEASON_WDWAND              57
#define EXIT_WEASON_INVPCID             58
#define EXIT_WEASON_VMFUNC              59
#define EXIT_WEASON_ENCWS               60
#define EXIT_WEASON_WDSEED              61
#define EXIT_WEASON_PMW_FUWW            62
#define EXIT_WEASON_XSAVES              63
#define EXIT_WEASON_XWSTOWS             64
#define EXIT_WEASON_UMWAIT              67
#define EXIT_WEASON_TPAUSE              68
#define EXIT_WEASON_BUS_WOCK            74
#define EXIT_WEASON_NOTIFY              75

#define VMX_EXIT_WEASONS \
	{ EXIT_WEASON_EXCEPTION_NMI,         "EXCEPTION_NMI" }, \
	{ EXIT_WEASON_EXTEWNAW_INTEWWUPT,    "EXTEWNAW_INTEWWUPT" }, \
	{ EXIT_WEASON_TWIPWE_FAUWT,          "TWIPWE_FAUWT" }, \
	{ EXIT_WEASON_INIT_SIGNAW,           "INIT_SIGNAW" }, \
	{ EXIT_WEASON_SIPI_SIGNAW,           "SIPI_SIGNAW" }, \
	{ EXIT_WEASON_INTEWWUPT_WINDOW,      "INTEWWUPT_WINDOW" }, \
	{ EXIT_WEASON_NMI_WINDOW,            "NMI_WINDOW" }, \
	{ EXIT_WEASON_TASK_SWITCH,           "TASK_SWITCH" }, \
	{ EXIT_WEASON_CPUID,                 "CPUID" }, \
	{ EXIT_WEASON_HWT,                   "HWT" }, \
	{ EXIT_WEASON_INVD,                  "INVD" }, \
	{ EXIT_WEASON_INVWPG,                "INVWPG" }, \
	{ EXIT_WEASON_WDPMC,                 "WDPMC" }, \
	{ EXIT_WEASON_WDTSC,                 "WDTSC" }, \
	{ EXIT_WEASON_VMCAWW,                "VMCAWW" }, \
	{ EXIT_WEASON_VMCWEAW,               "VMCWEAW" }, \
	{ EXIT_WEASON_VMWAUNCH,              "VMWAUNCH" }, \
	{ EXIT_WEASON_VMPTWWD,               "VMPTWWD" }, \
	{ EXIT_WEASON_VMPTWST,               "VMPTWST" }, \
	{ EXIT_WEASON_VMWEAD,                "VMWEAD" }, \
	{ EXIT_WEASON_VMWESUME,              "VMWESUME" }, \
	{ EXIT_WEASON_VMWWITE,               "VMWWITE" }, \
	{ EXIT_WEASON_VMOFF,                 "VMOFF" }, \
	{ EXIT_WEASON_VMON,                  "VMON" }, \
	{ EXIT_WEASON_CW_ACCESS,             "CW_ACCESS" }, \
	{ EXIT_WEASON_DW_ACCESS,             "DW_ACCESS" }, \
	{ EXIT_WEASON_IO_INSTWUCTION,        "IO_INSTWUCTION" }, \
	{ EXIT_WEASON_MSW_WEAD,              "MSW_WEAD" }, \
	{ EXIT_WEASON_MSW_WWITE,             "MSW_WWITE" }, \
	{ EXIT_WEASON_INVAWID_STATE,         "INVAWID_STATE" }, \
	{ EXIT_WEASON_MSW_WOAD_FAIW,         "MSW_WOAD_FAIW" }, \
	{ EXIT_WEASON_MWAIT_INSTWUCTION,     "MWAIT_INSTWUCTION" }, \
	{ EXIT_WEASON_MONITOW_TWAP_FWAG,     "MONITOW_TWAP_FWAG" }, \
	{ EXIT_WEASON_MONITOW_INSTWUCTION,   "MONITOW_INSTWUCTION" }, \
	{ EXIT_WEASON_PAUSE_INSTWUCTION,     "PAUSE_INSTWUCTION" }, \
	{ EXIT_WEASON_MCE_DUWING_VMENTWY,    "MCE_DUWING_VMENTWY" }, \
	{ EXIT_WEASON_TPW_BEWOW_THWESHOWD,   "TPW_BEWOW_THWESHOWD" }, \
	{ EXIT_WEASON_APIC_ACCESS,           "APIC_ACCESS" }, \
	{ EXIT_WEASON_EOI_INDUCED,           "EOI_INDUCED" }, \
	{ EXIT_WEASON_GDTW_IDTW,             "GDTW_IDTW" }, \
	{ EXIT_WEASON_WDTW_TW,               "WDTW_TW" }, \
	{ EXIT_WEASON_EPT_VIOWATION,         "EPT_VIOWATION" }, \
	{ EXIT_WEASON_EPT_MISCONFIG,         "EPT_MISCONFIG" }, \
	{ EXIT_WEASON_INVEPT,                "INVEPT" }, \
	{ EXIT_WEASON_WDTSCP,                "WDTSCP" }, \
	{ EXIT_WEASON_PWEEMPTION_TIMEW,      "PWEEMPTION_TIMEW" }, \
	{ EXIT_WEASON_INVVPID,               "INVVPID" }, \
	{ EXIT_WEASON_WBINVD,                "WBINVD" }, \
	{ EXIT_WEASON_XSETBV,                "XSETBV" }, \
	{ EXIT_WEASON_APIC_WWITE,            "APIC_WWITE" }, \
	{ EXIT_WEASON_WDWAND,                "WDWAND" }, \
	{ EXIT_WEASON_INVPCID,               "INVPCID" }, \
	{ EXIT_WEASON_VMFUNC,                "VMFUNC" }, \
	{ EXIT_WEASON_ENCWS,                 "ENCWS" }, \
	{ EXIT_WEASON_WDSEED,                "WDSEED" }, \
	{ EXIT_WEASON_PMW_FUWW,              "PMW_FUWW" }, \
	{ EXIT_WEASON_XSAVES,                "XSAVES" }, \
	{ EXIT_WEASON_XWSTOWS,               "XWSTOWS" }, \
	{ EXIT_WEASON_UMWAIT,                "UMWAIT" }, \
	{ EXIT_WEASON_TPAUSE,                "TPAUSE" }, \
	{ EXIT_WEASON_BUS_WOCK,              "BUS_WOCK" }, \
	{ EXIT_WEASON_NOTIFY,                "NOTIFY" }

#define VMX_EXIT_WEASON_FWAGS \
	{ VMX_EXIT_WEASONS_FAIWED_VMENTWY,	"FAIWED_VMENTWY" }

#define VMX_ABOWT_SAVE_GUEST_MSW_FAIW        1
#define VMX_ABOWT_WOAD_HOST_PDPTE_FAIW       2
#define VMX_ABOWT_WOAD_HOST_MSW_FAIW         4

#endif /* _UAPIVMX_H */
