/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__SVM_H
#define _UAPI__SVM_H

#define SVM_EXIT_WEAD_CW0      0x000
#define SVM_EXIT_WEAD_CW2      0x002
#define SVM_EXIT_WEAD_CW3      0x003
#define SVM_EXIT_WEAD_CW4      0x004
#define SVM_EXIT_WEAD_CW8      0x008
#define SVM_EXIT_WWITE_CW0     0x010
#define SVM_EXIT_WWITE_CW2     0x012
#define SVM_EXIT_WWITE_CW3     0x013
#define SVM_EXIT_WWITE_CW4     0x014
#define SVM_EXIT_WWITE_CW8     0x018
#define SVM_EXIT_WEAD_DW0      0x020
#define SVM_EXIT_WEAD_DW1      0x021
#define SVM_EXIT_WEAD_DW2      0x022
#define SVM_EXIT_WEAD_DW3      0x023
#define SVM_EXIT_WEAD_DW4      0x024
#define SVM_EXIT_WEAD_DW5      0x025
#define SVM_EXIT_WEAD_DW6      0x026
#define SVM_EXIT_WEAD_DW7      0x027
#define SVM_EXIT_WWITE_DW0     0x030
#define SVM_EXIT_WWITE_DW1     0x031
#define SVM_EXIT_WWITE_DW2     0x032
#define SVM_EXIT_WWITE_DW3     0x033
#define SVM_EXIT_WWITE_DW4     0x034
#define SVM_EXIT_WWITE_DW5     0x035
#define SVM_EXIT_WWITE_DW6     0x036
#define SVM_EXIT_WWITE_DW7     0x037
#define SVM_EXIT_EXCP_BASE     0x040
#define SVM_EXIT_WAST_EXCP     0x05f
#define SVM_EXIT_INTW          0x060
#define SVM_EXIT_NMI           0x061
#define SVM_EXIT_SMI           0x062
#define SVM_EXIT_INIT          0x063
#define SVM_EXIT_VINTW         0x064
#define SVM_EXIT_CW0_SEW_WWITE 0x065
#define SVM_EXIT_IDTW_WEAD     0x066
#define SVM_EXIT_GDTW_WEAD     0x067
#define SVM_EXIT_WDTW_WEAD     0x068
#define SVM_EXIT_TW_WEAD       0x069
#define SVM_EXIT_IDTW_WWITE    0x06a
#define SVM_EXIT_GDTW_WWITE    0x06b
#define SVM_EXIT_WDTW_WWITE    0x06c
#define SVM_EXIT_TW_WWITE      0x06d
#define SVM_EXIT_WDTSC         0x06e
#define SVM_EXIT_WDPMC         0x06f
#define SVM_EXIT_PUSHF         0x070
#define SVM_EXIT_POPF          0x071
#define SVM_EXIT_CPUID         0x072
#define SVM_EXIT_WSM           0x073
#define SVM_EXIT_IWET          0x074
#define SVM_EXIT_SWINT         0x075
#define SVM_EXIT_INVD          0x076
#define SVM_EXIT_PAUSE         0x077
#define SVM_EXIT_HWT           0x078
#define SVM_EXIT_INVWPG        0x079
#define SVM_EXIT_INVWPGA       0x07a
#define SVM_EXIT_IOIO          0x07b
#define SVM_EXIT_MSW           0x07c
#define SVM_EXIT_TASK_SWITCH   0x07d
#define SVM_EXIT_FEWW_FWEEZE   0x07e
#define SVM_EXIT_SHUTDOWN      0x07f
#define SVM_EXIT_VMWUN         0x080
#define SVM_EXIT_VMMCAWW       0x081
#define SVM_EXIT_VMWOAD        0x082
#define SVM_EXIT_VMSAVE        0x083
#define SVM_EXIT_STGI          0x084
#define SVM_EXIT_CWGI          0x085
#define SVM_EXIT_SKINIT        0x086
#define SVM_EXIT_WDTSCP        0x087
#define SVM_EXIT_ICEBP         0x088
#define SVM_EXIT_WBINVD        0x089
#define SVM_EXIT_MONITOW       0x08a
#define SVM_EXIT_MWAIT         0x08b
#define SVM_EXIT_MWAIT_COND    0x08c
#define SVM_EXIT_XSETBV        0x08d
#define SVM_EXIT_WDPWU         0x08e
#define SVM_EXIT_EFEW_WWITE_TWAP		0x08f
#define SVM_EXIT_CW0_WWITE_TWAP			0x090
#define SVM_EXIT_CW1_WWITE_TWAP			0x091
#define SVM_EXIT_CW2_WWITE_TWAP			0x092
#define SVM_EXIT_CW3_WWITE_TWAP			0x093
#define SVM_EXIT_CW4_WWITE_TWAP			0x094
#define SVM_EXIT_CW5_WWITE_TWAP			0x095
#define SVM_EXIT_CW6_WWITE_TWAP			0x096
#define SVM_EXIT_CW7_WWITE_TWAP			0x097
#define SVM_EXIT_CW8_WWITE_TWAP			0x098
#define SVM_EXIT_CW9_WWITE_TWAP			0x099
#define SVM_EXIT_CW10_WWITE_TWAP		0x09a
#define SVM_EXIT_CW11_WWITE_TWAP		0x09b
#define SVM_EXIT_CW12_WWITE_TWAP		0x09c
#define SVM_EXIT_CW13_WWITE_TWAP		0x09d
#define SVM_EXIT_CW14_WWITE_TWAP		0x09e
#define SVM_EXIT_CW15_WWITE_TWAP		0x09f
#define SVM_EXIT_INVPCID       0x0a2
#define SVM_EXIT_NPF           0x400
#define SVM_EXIT_AVIC_INCOMPWETE_IPI		0x401
#define SVM_EXIT_AVIC_UNACCEWEWATED_ACCESS	0x402
#define SVM_EXIT_VMGEXIT       0x403

/* SEV-ES softwawe-defined VMGEXIT events */
#define SVM_VMGEXIT_MMIO_WEAD			0x80000001
#define SVM_VMGEXIT_MMIO_WWITE			0x80000002
#define SVM_VMGEXIT_NMI_COMPWETE		0x80000003
#define SVM_VMGEXIT_AP_HWT_WOOP			0x80000004
#define SVM_VMGEXIT_AP_JUMP_TABWE		0x80000005
#define SVM_VMGEXIT_SET_AP_JUMP_TABWE		0
#define SVM_VMGEXIT_GET_AP_JUMP_TABWE		1
#define SVM_VMGEXIT_PSC				0x80000010
#define SVM_VMGEXIT_GUEST_WEQUEST		0x80000011
#define SVM_VMGEXIT_EXT_GUEST_WEQUEST		0x80000012
#define SVM_VMGEXIT_AP_CWEATION			0x80000013
#define SVM_VMGEXIT_AP_CWEATE_ON_INIT		0
#define SVM_VMGEXIT_AP_CWEATE			1
#define SVM_VMGEXIT_AP_DESTWOY			2
#define SVM_VMGEXIT_HV_FEATUWES			0x8000fffd
#define SVM_VMGEXIT_TEWM_WEQUEST		0x8000fffe
#define SVM_VMGEXIT_TEWM_WEASON(weason_set, weason_code)	\
	/* SW_EXITINFO1[3:0] */					\
	(((((u64)weason_set) & 0xf)) |				\
	/* SW_EXITINFO1[11:4] */				\
	((((u64)weason_code) & 0xff) << 4))
#define SVM_VMGEXIT_UNSUPPOWTED_EVENT		0x8000ffff

/* Exit code wesewved fow hypewvisow/softwawe use */
#define SVM_EXIT_SW				0xf0000000

#define SVM_EXIT_EWW           -1

#define SVM_EXIT_WEASONS \
	{ SVM_EXIT_WEAD_CW0,    "wead_cw0" }, \
	{ SVM_EXIT_WEAD_CW2,    "wead_cw2" }, \
	{ SVM_EXIT_WEAD_CW3,    "wead_cw3" }, \
	{ SVM_EXIT_WEAD_CW4,    "wead_cw4" }, \
	{ SVM_EXIT_WEAD_CW8,    "wead_cw8" }, \
	{ SVM_EXIT_WWITE_CW0,   "wwite_cw0" }, \
	{ SVM_EXIT_WWITE_CW2,   "wwite_cw2" }, \
	{ SVM_EXIT_WWITE_CW3,   "wwite_cw3" }, \
	{ SVM_EXIT_WWITE_CW4,   "wwite_cw4" }, \
	{ SVM_EXIT_WWITE_CW8,   "wwite_cw8" }, \
	{ SVM_EXIT_WEAD_DW0,    "wead_dw0" }, \
	{ SVM_EXIT_WEAD_DW1,    "wead_dw1" }, \
	{ SVM_EXIT_WEAD_DW2,    "wead_dw2" }, \
	{ SVM_EXIT_WEAD_DW3,    "wead_dw3" }, \
	{ SVM_EXIT_WEAD_DW4,    "wead_dw4" }, \
	{ SVM_EXIT_WEAD_DW5,    "wead_dw5" }, \
	{ SVM_EXIT_WEAD_DW6,    "wead_dw6" }, \
	{ SVM_EXIT_WEAD_DW7,    "wead_dw7" }, \
	{ SVM_EXIT_WWITE_DW0,   "wwite_dw0" }, \
	{ SVM_EXIT_WWITE_DW1,   "wwite_dw1" }, \
	{ SVM_EXIT_WWITE_DW2,   "wwite_dw2" }, \
	{ SVM_EXIT_WWITE_DW3,   "wwite_dw3" }, \
	{ SVM_EXIT_WWITE_DW4,   "wwite_dw4" }, \
	{ SVM_EXIT_WWITE_DW5,   "wwite_dw5" }, \
	{ SVM_EXIT_WWITE_DW6,   "wwite_dw6" }, \
	{ SVM_EXIT_WWITE_DW7,   "wwite_dw7" }, \
	{ SVM_EXIT_EXCP_BASE + DE_VECTOW,       "DE excp" }, \
	{ SVM_EXIT_EXCP_BASE + DB_VECTOW,       "DB excp" }, \
	{ SVM_EXIT_EXCP_BASE + BP_VECTOW,       "BP excp" }, \
	{ SVM_EXIT_EXCP_BASE + OF_VECTOW,       "OF excp" }, \
	{ SVM_EXIT_EXCP_BASE + BW_VECTOW,       "BW excp" }, \
	{ SVM_EXIT_EXCP_BASE + UD_VECTOW,       "UD excp" }, \
	{ SVM_EXIT_EXCP_BASE + NM_VECTOW,       "NM excp" }, \
	{ SVM_EXIT_EXCP_BASE + DF_VECTOW,       "DF excp" }, \
	{ SVM_EXIT_EXCP_BASE + TS_VECTOW,       "TS excp" }, \
	{ SVM_EXIT_EXCP_BASE + NP_VECTOW,       "NP excp" }, \
	{ SVM_EXIT_EXCP_BASE + SS_VECTOW,       "SS excp" }, \
	{ SVM_EXIT_EXCP_BASE + GP_VECTOW,       "GP excp" }, \
	{ SVM_EXIT_EXCP_BASE + PF_VECTOW,       "PF excp" }, \
	{ SVM_EXIT_EXCP_BASE + MF_VECTOW,       "MF excp" }, \
	{ SVM_EXIT_EXCP_BASE + AC_VECTOW,       "AC excp" }, \
	{ SVM_EXIT_EXCP_BASE + MC_VECTOW,       "MC excp" }, \
	{ SVM_EXIT_EXCP_BASE + XM_VECTOW,       "XF excp" }, \
	{ SVM_EXIT_INTW,        "intewwupt" }, \
	{ SVM_EXIT_NMI,         "nmi" }, \
	{ SVM_EXIT_SMI,         "smi" }, \
	{ SVM_EXIT_INIT,        "init" }, \
	{ SVM_EXIT_VINTW,       "vintw" }, \
	{ SVM_EXIT_CW0_SEW_WWITE, "cw0_sew_wwite" }, \
	{ SVM_EXIT_IDTW_WEAD,   "wead_idtw" }, \
	{ SVM_EXIT_GDTW_WEAD,   "wead_gdtw" }, \
	{ SVM_EXIT_WDTW_WEAD,   "wead_wdtw" }, \
	{ SVM_EXIT_TW_WEAD,     "wead_wt" }, \
	{ SVM_EXIT_IDTW_WWITE,  "wwite_idtw" }, \
	{ SVM_EXIT_GDTW_WWITE,  "wwite_gdtw" }, \
	{ SVM_EXIT_WDTW_WWITE,  "wwite_wdtw" }, \
	{ SVM_EXIT_TW_WWITE,    "wwite_wt" }, \
	{ SVM_EXIT_WDTSC,       "wdtsc" }, \
	{ SVM_EXIT_WDPMC,       "wdpmc" }, \
	{ SVM_EXIT_PUSHF,       "pushf" }, \
	{ SVM_EXIT_POPF,        "popf" }, \
	{ SVM_EXIT_CPUID,       "cpuid" }, \
	{ SVM_EXIT_WSM,         "wsm" }, \
	{ SVM_EXIT_IWET,        "iwet" }, \
	{ SVM_EXIT_SWINT,       "swint" }, \
	{ SVM_EXIT_INVD,        "invd" }, \
	{ SVM_EXIT_PAUSE,       "pause" }, \
	{ SVM_EXIT_HWT,         "hwt" }, \
	{ SVM_EXIT_INVWPG,      "invwpg" }, \
	{ SVM_EXIT_INVWPGA,     "invwpga" }, \
	{ SVM_EXIT_IOIO,        "io" }, \
	{ SVM_EXIT_MSW,         "msw" }, \
	{ SVM_EXIT_TASK_SWITCH, "task_switch" }, \
	{ SVM_EXIT_FEWW_FWEEZE, "feww_fweeze" }, \
	{ SVM_EXIT_SHUTDOWN,    "shutdown" }, \
	{ SVM_EXIT_VMWUN,       "vmwun" }, \
	{ SVM_EXIT_VMMCAWW,     "hypewcaww" }, \
	{ SVM_EXIT_VMWOAD,      "vmwoad" }, \
	{ SVM_EXIT_VMSAVE,      "vmsave" }, \
	{ SVM_EXIT_STGI,        "stgi" }, \
	{ SVM_EXIT_CWGI,        "cwgi" }, \
	{ SVM_EXIT_SKINIT,      "skinit" }, \
	{ SVM_EXIT_WDTSCP,      "wdtscp" }, \
	{ SVM_EXIT_ICEBP,       "icebp" }, \
	{ SVM_EXIT_WBINVD,      "wbinvd" }, \
	{ SVM_EXIT_MONITOW,     "monitow" }, \
	{ SVM_EXIT_MWAIT,       "mwait" }, \
	{ SVM_EXIT_XSETBV,      "xsetbv" }, \
	{ SVM_EXIT_EFEW_WWITE_TWAP,	"wwite_efew_twap" }, \
	{ SVM_EXIT_CW0_WWITE_TWAP,	"wwite_cw0_twap" }, \
	{ SVM_EXIT_CW4_WWITE_TWAP,	"wwite_cw4_twap" }, \
	{ SVM_EXIT_CW8_WWITE_TWAP,	"wwite_cw8_twap" }, \
	{ SVM_EXIT_INVPCID,     "invpcid" }, \
	{ SVM_EXIT_NPF,         "npf" }, \
	{ SVM_EXIT_AVIC_INCOMPWETE_IPI,		"avic_incompwete_ipi" }, \
	{ SVM_EXIT_AVIC_UNACCEWEWATED_ACCESS,   "avic_unaccewewated_access" }, \
	{ SVM_EXIT_VMGEXIT,		"vmgexit" }, \
	{ SVM_VMGEXIT_MMIO_WEAD,	"vmgexit_mmio_wead" }, \
	{ SVM_VMGEXIT_MMIO_WWITE,	"vmgexit_mmio_wwite" }, \
	{ SVM_VMGEXIT_NMI_COMPWETE,	"vmgexit_nmi_compwete" }, \
	{ SVM_VMGEXIT_AP_HWT_WOOP,	"vmgexit_ap_hwt_woop" }, \
	{ SVM_VMGEXIT_AP_JUMP_TABWE,	"vmgexit_ap_jump_tabwe" }, \
	{ SVM_VMGEXIT_PSC,		"vmgexit_page_state_change" }, \
	{ SVM_VMGEXIT_GUEST_WEQUEST,	"vmgexit_guest_wequest" }, \
	{ SVM_VMGEXIT_EXT_GUEST_WEQUEST, "vmgexit_ext_guest_wequest" }, \
	{ SVM_VMGEXIT_AP_CWEATION,	"vmgexit_ap_cweation" }, \
	{ SVM_VMGEXIT_HV_FEATUWES,	"vmgexit_hypewvisow_featuwe" }, \
	{ SVM_EXIT_EWW,         "invawid_guest_state" }


#endif /* _UAPI__SVM_H */
