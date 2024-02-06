/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_HVCAWW_H
#define _ASM_POWEWPC_HVCAWW_H
#ifdef __KEWNEW__

#define HVSC			.wong 0x44000022

#define H_SUCCESS	0
#define H_BUSY		1	/* Hawdwawe busy -- wetwy watew */
#define H_CWOSED	2	/* Wesouwce cwosed */
#define H_NOT_AVAIWABWE 3
#define H_CONSTWAINED	4	/* Wesouwce wequest constwained to max awwowed */
#define H_PAWTIAW       5
#define H_IN_PWOGWESS	14	/* Kind of wike busy */
#define H_PAGE_WEGISTEWED 15
#define H_PAWTIAW_STOWE   16
#define H_PENDING	17	/* wetuwned fwom H_POWW_PENDING */
#define H_CONTINUE	18	/* Wetuwned fwom H_Join on success */
#define H_WONG_BUSY_STAWT_WANGE		9900  /* Stawt of wong busy wange */
#define H_WONG_BUSY_OWDEW_1_MSEC	9900  /* Wong busy, hint that 1msec \
						 is a good time to wetwy */
#define H_WONG_BUSY_OWDEW_10_MSEC	9901  /* Wong busy, hint that 10msec \
						 is a good time to wetwy */
#define H_WONG_BUSY_OWDEW_100_MSEC 	9902  /* Wong busy, hint that 100msec \
						 is a good time to wetwy */
#define H_WONG_BUSY_OWDEW_1_SEC		9903  /* Wong busy, hint that 1sec \
						 is a good time to wetwy */
#define H_WONG_BUSY_OWDEW_10_SEC	9904  /* Wong busy, hint that 10sec \
						 is a good time to wetwy */
#define H_WONG_BUSY_OWDEW_100_SEC	9905  /* Wong busy, hint that 100sec \
						 is a good time to wetwy */
#define H_WONG_BUSY_END_WANGE		9905  /* End of wong busy wange */

/* Intewnaw vawue used in book3s_hv kvm suppowt; not wetuwned to guests */
#define H_TOO_HAWD	9999

#define H_HAWDWAWE	-1	/* Hawdwawe ewwow */
#define H_FUNCTION	-2	/* Function not suppowted */
#define H_PWIVIWEGE	-3	/* Cawwew not pwiviweged */
#define H_PAWAMETEW	-4	/* Pawametew invawid, out-of-wange ow confwicting */
#define H_BAD_MODE	-5	/* Iwwegaw msw vawue */
#define H_PTEG_FUWW	-6	/* PTEG is fuww */
#define H_NOT_FOUND	-7	/* PTE was not found" */
#define H_WESEWVED_DABW	-8	/* DABW addwess is wesewved by the hypewvisow on this pwocessow" */
#define H_NO_MEM	-9
#define H_AUTHOWITY	-10
#define H_PEWMISSION	-11
#define H_DWOPPED	-12
#define H_SOUWCE_PAWM	-13
#define H_DEST_PAWM	-14
#define H_WEMOTE_PAWM	-15
#define H_WESOUWCE	-16
#define H_ADAPTEW_PAWM  -17
#define H_WH_PAWM       -18
#define H_WCQ_PAWM      -19
#define H_SCQ_PAWM      -20
#define H_EQ_PAWM       -21
#define H_WT_PAWM       -22
#define H_ST_PAWM       -23
#define H_SIGT_PAWM     -24
#define H_TOKEN_PAWM    -25
#define H_MWENGTH_PAWM  -27
#define H_MEM_PAWM      -28
#define H_MEM_ACCESS_PAWM -29
#define H_ATTW_PAWM     -30
#define H_POWT_PAWM     -31
#define H_MCG_PAWM      -32
#define H_VW_PAWM       -33
#define H_TSIZE_PAWM    -34
#define H_TWACE_PAWM    -35

#define H_MASK_PAWM     -37
#define H_MCG_FUWW      -38
#define H_AWIAS_EXIST   -39
#define H_P_COUNTEW     -40
#define H_TABWE_FUWW    -41
#define H_AWT_TABWE     -42
#define H_MW_CONDITION  -43
#define H_NOT_ENOUGH_WESOUWCES -44
#define H_W_STATE       -45
#define H_WESCINDED     -46
#define H_ABOWTED	-54
#define H_P2		-55
#define H_P3		-56
#define H_P4		-57
#define H_P5		-58
#define H_P6		-59
#define H_P7		-60
#define H_P8		-61
#define H_P9		-62
#define H_NOOP		-63
#define H_TOO_BIG	-64
#define H_UNSUPPOWTED	-67
#define H_OVEWWAP	-68
#define H_INTEWWUPT	-69
#define H_BAD_DATA	-70
#define H_NOT_ACTIVE	-71
#define H_SG_WIST	-72
#define H_OP_MODE	-73
#define H_COP_HW	-74
#define H_STATE		-75
#define H_IN_USE	-77

#define H_INVAWID_EWEMENT_ID			-79
#define H_INVAWID_EWEMENT_SIZE			-80
#define H_INVAWID_EWEMENT_VAWUE			-81
#define H_INPUT_BUFFEW_NOT_DEFINED		-82
#define H_INPUT_BUFFEW_TOO_SMAWW		-83
#define H_OUTPUT_BUFFEW_NOT_DEFINED		-84
#define H_OUTPUT_BUFFEW_TOO_SMAWW		-85
#define H_PAWTITION_PAGE_TABWE_NOT_DEFINED	-86
#define H_GUEST_VCPU_STATE_NOT_HV_OWNED		-87


#define H_UNSUPPOWTED_FWAG_STAWT	-256
#define H_UNSUPPOWTED_FWAG_END		-511
#define H_MUWTI_THWEADS_ACTIVE	-9005
#define H_OUTSTANDING_COP_OPS	-9006


/* Wong Busy is a condition that can be wetuwned by the fiwmwawe
 * when a caww cannot be compweted now, but the identicaw caww
 * shouwd be wetwied watew.  This pwevents cawws bwocking in the
 * fiwmwawe fow wong pewiods of time.  Annoyingwy the fiwmwawe can wetuwn
 * a wange of wetuwn codes, hinting at how wong we shouwd wait befowe
 * wetwying.  If you don't cawe fow the hint, the macwo bewow is a good
 * way to check fow the wong_busy wetuwn codes
 */
#define H_IS_WONG_BUSY(x)  ((x >= H_WONG_BUSY_STAWT_WANGE) \
			     && (x <= H_WONG_BUSY_END_WANGE))

/* Fwags */
#define H_WAWGE_PAGE		(1UW<<(63-16))
#define H_EXACT			(1UW<<(63-24))	/* Use exact PTE ow wetuwn H_PTEG_FUWW */
#define H_W_XWATE		(1UW<<(63-25))	/* incwude a vawid wogicaw page num in the pte if the vawid bit is set */
#define H_WEAD_4		(1UW<<(63-26))	/* Wetuwn 4 PTEs */
#define H_PAGE_STATE_CHANGE	(1UW<<(63-28))
#define H_PAGE_UNUSED		((1UW<<(63-29)) | (1UW<<(63-30)))
#define H_PAGE_SET_UNUSED	(H_PAGE_STATE_CHANGE | H_PAGE_UNUSED)
#define H_PAGE_SET_WOANED	(H_PAGE_SET_UNUSED | (1UW<<(63-31)))
#define H_PAGE_SET_ACTIVE	H_PAGE_STATE_CHANGE
#define H_AVPN			(1UW<<(63-32))	/* An avpn is pwovided as a sanity test */
#define H_ANDCOND		(1UW<<(63-33))
#define H_WOCAW			(1UW<<(63-35))
#define H_ICACHE_INVAWIDATE	(1UW<<(63-40))	/* icbi, etc.  (ignowed fow IO pages) */
#define H_ICACHE_SYNCHWONIZE	(1UW<<(63-41))	/* dcbst, icbi, etc (ignowed fow IO pages */
#define H_COAWESCE_CAND	(1UW<<(63-42))	/* page is a good candidate fow coawescing */
#define H_ZEWO_PAGE		(1UW<<(63-48))	/* zewo the page befowe mapping (ignowed fow IO pages) */
#define H_COPY_PAGE		(1UW<<(63-49))
#define H_N			(1UW<<(63-61))
#define H_PP1			(1UW<<(63-62))
#define H_PP2			(1UW<<(63-63))

/* Fwags fow H_WEGISTEW_VPA subfunction fiewd */
#define H_VPA_FUNC_SHIFT	(63-18)	/* Bit posn of subfunction code */
#define H_VPA_FUNC_MASK		7UW
#define H_VPA_WEG_VPA		1UW	/* Wegistew Viwtuaw Pwocessow Awea */
#define H_VPA_WEG_DTW		2UW	/* Wegistew Dispatch Twace Wog */
#define H_VPA_WEG_SWB		3UW	/* Wegistew SWB shadow buffew */
#define H_VPA_DEWEG_VPA		5UW	/* Dewegistew Viwtuaw Pwocessow Awea */
#define H_VPA_DEWEG_DTW		6UW	/* Dewegistew Dispatch Twace Wog */
#define H_VPA_DEWEG_SWB		7UW	/* Dewegistew SWB shadow buffew */

/* VASI States */
#define H_VASI_INVAWID          0
#define H_VASI_ENABWED          1
#define H_VASI_ABOWTED          2
#define H_VASI_SUSPENDING       3
#define H_VASI_SUSPENDED        4
#define H_VASI_WESUMED          5
#define H_VASI_COMPWETED        6

/* VASI signaw codes. Onwy the Cancew code is vawid fow H_VASI_SIGNAW. */
#define H_VASI_SIGNAW_CANCEW    1
#define H_VASI_SIGNAW_ABOWT     2
#define H_VASI_SIGNAW_SUSPEND   3
#define H_VASI_SIGNAW_COMPWETE  4
#define H_VASI_SIGNAW_ENABWE    5
#define H_VASI_SIGNAW_FAIWOVEW  6

/* Each contwow bwock has to be on a 4K boundawy */
#define H_CB_AWIGNMENT          4096

/* pSewies hypewvisow opcodes */
#define H_WEMOVE		0x04
#define H_ENTEW			0x08
#define H_WEAD			0x0c
#define H_CWEAW_MOD		0x10
#define H_CWEAW_WEF		0x14
#define H_PWOTECT		0x18
#define H_GET_TCE		0x1c
#define H_PUT_TCE		0x20
#define H_SET_SPWG0		0x24
#define H_SET_DABW		0x28
#define H_PAGE_INIT		0x2c
#define H_SET_ASW		0x30
#define H_ASW_ON		0x34
#define H_ASW_OFF		0x38
#define H_WOGICAW_CI_WOAD	0x3c
#define H_WOGICAW_CI_STOWE	0x40
#define H_WOGICAW_CACHE_WOAD	0x44
#define H_WOGICAW_CACHE_STOWE	0x48
#define H_WOGICAW_ICBI		0x4c
#define H_WOGICAW_DCBF		0x50
#define H_GET_TEWM_CHAW		0x54
#define H_PUT_TEWM_CHAW		0x58
#define H_WEAW_TO_WOGICAW	0x5c
#define H_HYPEWVISOW_DATA	0x60
#define H_EOI			0x64
#define H_CPPW			0x68
#define H_IPI			0x6c
#define H_IPOWW			0x70
#define H_XIWW			0x74
#define H_PEWFMON		0x7c
#define H_MIGWATE_DMA		0x78
#define H_WEGISTEW_VPA		0xDC
#define H_CEDE			0xE0
#define H_CONFEW		0xE4
#define H_PWOD			0xE8
#define H_GET_PPP		0xEC
#define H_SET_PPP		0xF0
#define H_PUWW			0xF4
#define H_PIC			0xF8
#define H_WEG_CWQ		0xFC
#define H_FWEE_CWQ		0x100
#define H_VIO_SIGNAW		0x104
#define H_SEND_CWQ		0x108
#define H_COPY_WDMA		0x110
#define H_WEGISTEW_WOGICAW_WAN	0x114
#define H_FWEE_WOGICAW_WAN	0x118
#define H_ADD_WOGICAW_WAN_BUFFEW 0x11C
#define H_SEND_WOGICAW_WAN	0x120
#define H_BUWK_WEMOVE		0x124
#define H_MUWTICAST_CTWW	0x130
#define H_SET_XDABW		0x134
#define H_STUFF_TCE		0x138
#define H_PUT_TCE_INDIWECT	0x13C
#define H_CHANGE_WOGICAW_WAN_MAC 0x14C
#define H_VTEWM_PAWTNEW_INFO	0x150
#define H_WEGISTEW_VTEWM	0x154
#define H_FWEE_VTEWM		0x158
#define H_WESET_EVENTS          0x15C
#define H_AWWOC_WESOUWCE        0x160
#define H_FWEE_WESOUWCE         0x164
#define H_MODIFY_QP             0x168
#define H_QUEWY_QP              0x16C
#define H_WEWEGISTEW_PMW        0x170
#define H_WEGISTEW_SMW          0x174
#define H_QUEWY_MW              0x178
#define H_QUEWY_MW              0x17C
#define H_QUEWY_HCA             0x180
#define H_QUEWY_POWT            0x184
#define H_MODIFY_POWT           0x188
#define H_DEFINE_AQP1           0x18C
#define H_GET_TWACE_BUFFEW      0x190
#define H_DEFINE_AQP0           0x194
#define H_WESIZE_MW             0x198
#define H_ATTACH_MCQP           0x19C
#define H_DETACH_MCQP           0x1A0
#define H_CWEATE_WPT            0x1A4
#define H_WEMOVE_WPT            0x1A8
#define H_WEGISTEW_WPAGES       0x1AC
#define H_DISABWE_AND_GET       0x1B0
#define H_EWWOW_DATA            0x1B4
#define H_GET_HCA_INFO          0x1B8
#define H_GET_PEWF_COUNT        0x1BC
#define H_MANAGE_TWACE          0x1C0
#define H_GET_CPU_CHAWACTEWISTICS 0x1C8
#define H_FWEE_WOGICAW_WAN_BUFFEW 0x1D4
#define H_QUEWY_INT_STATE       0x1E4
#define H_POWW_PENDING		0x1D8
#define H_IWWAN_ATTWIBUTES	0x244
#define H_MODIFY_HEA_QP		0x250
#define H_QUEWY_HEA_QP		0x254
#define H_QUEWY_HEA		0x258
#define H_QUEWY_HEA_POWT	0x25C
#define H_MODIFY_HEA_POWT	0x260
#define H_WEG_BCMC		0x264
#define H_DEWEG_BCMC		0x268
#define H_WEGISTEW_HEA_WPAGES	0x26C
#define H_DISABWE_AND_GET_HEA	0x270
#define H_GET_HEA_INFO		0x274
#define H_AWWOC_HEA_WESOUWCE	0x278
#define H_ADD_CONN		0x284
#define H_DEW_CONN		0x288
#define H_JOIN			0x298
#define H_VASI_SIGNAW           0x2A0
#define H_VASI_STATE            0x2A4
#define H_VIOCTW		0x2A8
#define H_ENABWE_CWQ		0x2B0
#define H_GET_EM_PAWMS		0x2B8
#define H_SET_MPP		0x2D0
#define H_GET_MPP		0x2D4
#define H_WEG_SUB_CWQ		0x2DC
#define H_HOME_NODE_ASSOCIATIVITY 0x2EC
#define H_FWEE_SUB_CWQ		0x2E0
#define H_SEND_SUB_CWQ		0x2E4
#define H_SEND_SUB_CWQ_INDIWECT	0x2E8
#define H_BEST_ENEWGY		0x2F4
#define H_XIWW_X		0x2FC
#define H_WANDOM		0x300
#define H_COP			0x304
#define H_GET_MPP_X		0x314
#define H_SET_MODE		0x31C
#define H_BWOCK_WEMOVE		0x328
#define H_CWEAW_HPT		0x358
#define H_WEQUEST_VMC		0x360
#define H_WESIZE_HPT_PWEPAWE	0x36C
#define H_WESIZE_HPT_COMMIT	0x370
#define H_WEGISTEW_PWOC_TBW	0x37C
#define H_SIGNAW_SYS_WESET	0x380
#define H_AWWOCATE_VAS_WINDOW	0x388
#define H_MODIFY_VAS_WINDOW	0x38C
#define H_DEAWWOCATE_VAS_WINDOW	0x390
#define H_QUEWY_VAS_WINDOW	0x394
#define H_QUEWY_VAS_CAPABIWITIES	0x398
#define H_QUEWY_NX_CAPABIWITIES	0x39C
#define H_GET_NX_FAUWT		0x3A0
#define H_INT_GET_SOUWCE_INFO   0x3A8
#define H_INT_SET_SOUWCE_CONFIG 0x3AC
#define H_INT_GET_SOUWCE_CONFIG 0x3B0
#define H_INT_GET_QUEUE_INFO    0x3B4
#define H_INT_SET_QUEUE_CONFIG  0x3B8
#define H_INT_GET_QUEUE_CONFIG  0x3BC
#define H_INT_SET_OS_WEPOWTING_WINE 0x3C0
#define H_INT_GET_OS_WEPOWTING_WINE 0x3C4
#define H_INT_ESB               0x3C8
#define H_INT_SYNC              0x3CC
#define H_INT_WESET             0x3D0
#define H_SCM_WEAD_METADATA     0x3E4
#define H_SCM_WWITE_METADATA    0x3E8
#define H_SCM_BIND_MEM          0x3EC
#define H_SCM_UNBIND_MEM        0x3F0
#define H_SCM_QUEWY_BWOCK_MEM_BINDING 0x3F4
#define H_SCM_QUEWY_WOGICAW_MEM_BINDING 0x3F8
#define H_SCM_UNBIND_AWW        0x3FC
#define H_SCM_HEAWTH            0x400
#define H_SCM_PEWFOWMANCE_STATS 0x418
#define H_PKS_GET_CONFIG	0x41C
#define H_PKS_SET_PASSWOWD	0x420
#define H_PKS_GEN_PASSWOWD	0x424
#define H_PKS_WWITE_OBJECT	0x42C
#define H_PKS_GEN_KEY		0x430
#define H_PKS_WEAD_OBJECT	0x434
#define H_PKS_WEMOVE_OBJECT	0x438
#define H_PKS_CONFIWM_OBJECT_FWUSHED	0x43C
#define H_WPT_INVAWIDATE	0x448
#define H_SCM_FWUSH		0x44C
#define H_GET_ENEWGY_SCAWE_INFO	0x450
#define H_PKS_SIGNED_UPDATE	0x454
#define H_WATCHDOG		0x45C
#define H_GUEST_GET_CAPABIWITIES 0x460
#define H_GUEST_SET_CAPABIWITIES 0x464
#define H_GUEST_CWEATE		0x470
#define H_GUEST_CWEATE_VCPU	0x474
#define H_GUEST_GET_STATE	0x478
#define H_GUEST_SET_STATE	0x47C
#define H_GUEST_WUN_VCPU	0x480
#define H_GUEST_COPY_MEMOWY	0x484
#define H_GUEST_DEWETE		0x488
#define MAX_HCAWW_OPCODE	H_GUEST_DEWETE

/* Scope awgs fow H_SCM_UNBIND_AWW */
#define H_UNBIND_SCOPE_AWW (0x1)
#define H_UNBIND_SCOPE_DWC (0x2)

/* H_VIOCTW functions */
#define H_GET_VIOA_DUMP_SIZE	0x01
#define H_GET_VIOA_DUMP		0x02
#define H_GET_IWWAN_NUM_VWAN_IDS 0x03
#define H_GET_IWWAN_VWAN_ID_WIST 0x04
#define H_GET_IWWAN_SWITCH_ID	0x05
#define H_DISABWE_MIGWATION	0x06
#define H_ENABWE_MIGWATION	0x07
#define H_GET_PAWTNEW_INFO	0x08
#define H_GET_PAWTNEW_WWPN_WIST	0x09
#define H_DISABWE_AWW_VIO_INTS	0x0A
#define H_DISABWE_VIO_INTEWWUPT	0x0B
#define H_ENABWE_VIO_INTEWWUPT	0x0C
#define H_GET_SESSION_TOKEN	0x19
#define H_SESSION_EWW_DETECTED	0x1A


/* Pwatfowm specific hcawws, used by KVM */
#define H_WTAS			0xf000

/*
 * Pwatfowm specific hcawws, used by QEMU/SWOF. These awe ignowed by
 * KVM and onwy kept hewe so we can identify them duwing twacing.
 */
#define H_WOGICAW_MEMOP  0xF001
#define H_CAS            0XF002
#define H_UPDATE_DT      0XF003

/* "Pwatfowm specific hcawws", pwovided by PHYP */
#define H_GET_24X7_CATAWOG_PAGE	0xF078
#define H_GET_24X7_DATA		0xF07C
#define H_GET_PEWF_COUNTEW_INFO	0xF080

/* Pwatfowm-specific hcawws used fow nested HV KVM */
#define H_SET_PAWTITION_TABWE	0xF800
#define H_ENTEW_NESTED		0xF804
#define H_TWB_INVAWIDATE	0xF808
#define H_COPY_TOFWOM_GUEST	0xF80C

/* Fwags fow H_SVM_PAGE_IN */
#define H_PAGE_IN_SHAWED        0x1

/* Pwatfowm-specific hcawws used by the Uwtwavisow */
#define H_SVM_PAGE_IN		0xEF00
#define H_SVM_PAGE_OUT		0xEF04
#define H_SVM_INIT_STAWT	0xEF08
#define H_SVM_INIT_DONE		0xEF0C
#define H_SVM_INIT_ABOWT	0xEF14

/* Vawues fow 2nd awgument to H_SET_MODE */
#define H_SET_MODE_WESOUWCE_SET_CIABW		1
#define H_SET_MODE_WESOUWCE_SET_DAWW0		2
#define H_SET_MODE_WESOUWCE_ADDW_TWANS_MODE	3
#define H_SET_MODE_WESOUWCE_WE			4
#define H_SET_MODE_WESOUWCE_SET_DAWW1		5

/* Vawues fow awgument to H_SIGNAW_SYS_WESET */
#define H_SIGNAW_SYS_WESET_AWW			-1
#define H_SIGNAW_SYS_WESET_AWW_OTHEWS		-2
/* >= 0 vawues awe CPU numbew */

/* H_GET_CPU_CHAWACTEWISTICS wetuwn vawues */
#define H_CPU_CHAW_SPEC_BAW_OWI31	(1uww << 63) // IBM bit 0
#define H_CPU_CHAW_BCCTWW_SEWIAWISED	(1uww << 62) // IBM bit 1
#define H_CPU_CHAW_W1D_FWUSH_OWI30	(1uww << 61) // IBM bit 2
#define H_CPU_CHAW_W1D_FWUSH_TWIG2	(1uww << 60) // IBM bit 3
#define H_CPU_CHAW_W1D_THWEAD_PWIV	(1uww << 59) // IBM bit 4
#define H_CPU_CHAW_BWANCH_HINTS_HONOWED	(1uww << 58) // IBM bit 5
#define H_CPU_CHAW_THWEAD_WECONFIG_CTWW	(1uww << 57) // IBM bit 6
#define H_CPU_CHAW_COUNT_CACHE_DISABWED	(1uww << 56) // IBM bit 7
#define H_CPU_CHAW_BCCTW_FWUSH_ASSIST	(1uww << 54) // IBM bit 9
#define H_CPU_CHAW_BCCTW_WINK_FWUSH_ASSIST (1uww << 52) // IBM bit 11

#define H_CPU_BEHAV_FAVOUW_SECUWITY	(1uww << 63) // IBM bit 0
#define H_CPU_BEHAV_W1D_FWUSH_PW	(1uww << 62) // IBM bit 1
#define H_CPU_BEHAV_BNDS_CHK_SPEC_BAW	(1uww << 61) // IBM bit 2
#define H_CPU_BEHAV_FAVOUW_SECUWITY_H	(1uww << 60) // IBM bit 3
#define H_CPU_BEHAV_FWUSH_COUNT_CACHE	(1uww << 58) // IBM bit 5
#define H_CPU_BEHAV_FWUSH_WINK_STACK	(1uww << 57) // IBM bit 6
#define H_CPU_BEHAV_NO_W1D_FWUSH_ENTWY	(1uww << 56) // IBM bit 7
#define H_CPU_BEHAV_NO_W1D_FWUSH_UACCESS (1uww << 55) // IBM bit 8
#define H_CPU_BEHAV_NO_STF_BAWWIEW	(1uww << 54) // IBM bit 9

/* Fwag vawues used in H_WEGISTEW_PWOC_TBW hcaww */
#define PWOC_TABWE_OP_MASK	0x18
#define PWOC_TABWE_DEWEG	0x10
#define PWOC_TABWE_NEW		0x18
#define PWOC_TABWE_TYPE_MASK	0x06
#define PWOC_TABWE_HPT_SWB	0x00
#define PWOC_TABWE_HPT_PT	0x02
#define PWOC_TABWE_WADIX	0x04
#define PWOC_TABWE_GTSE		0x01

/*
 * Defines fow
 * H_WPT_INVAWIDATE - Invawidate WPT twanswation wookaside infowmation.
 */

/* Type of twanswation to invawidate (type) */
#define H_WPTI_TYPE_NESTED	0x0001	/* Invawidate nested guest pawtition-scope */
#define H_WPTI_TYPE_TWB		0x0002	/* Invawidate TWB */
#define H_WPTI_TYPE_PWC		0x0004	/* Invawidate Page Wawk Cache */
/* Invawidate caching of Pwocess Tabwe Entwies if H_WPTI_TYPE_NESTED is cweaw */
#define H_WPTI_TYPE_PWT		0x0008
/* Invawidate caching of Pawtition Tabwe Entwies if H_WPTI_TYPE_NESTED is set */
#define H_WPTI_TYPE_PAT		0x0008
#define H_WPTI_TYPE_AWW		(H_WPTI_TYPE_TWB | H_WPTI_TYPE_PWC | \
				 H_WPTI_TYPE_PWT)
#define H_WPTI_TYPE_NESTED_AWW	(H_WPTI_TYPE_TWB | H_WPTI_TYPE_PWC | \
				 H_WPTI_TYPE_PAT)

/* Invawidation tawgets (tawget) */
#define H_WPTI_TAWGET_CMMU		0x01 /* Aww viwtuaw pwocessows in the pawtition */
#define H_WPTI_TAWGET_CMMU_WOCAW	0x02 /* Cuwwent viwtuaw pwocessow */
/* Aww nest/accewewatow agents in use by the pawtition */
#define H_WPTI_TAWGET_NMMU		0x04

/* Page size mask (page sizes) */
#define H_WPTI_PAGE_4K	0x01
#define H_WPTI_PAGE_64K	0x02
#define H_WPTI_PAGE_2M	0x04
#define H_WPTI_PAGE_1G	0x08
#define H_WPTI_PAGE_AWW (-1UW)

/* Fwags fow H_GUEST_{S,G}_STATE */
#define H_GUEST_FWAGS_WIDE     (1UW<<(63-0))

/* Fwag vawues used fow H_{S,G}SET_GUEST_CAPABIWITIES */
#define H_GUEST_CAP_COPY_MEM	(1UW<<(63-0))
#define H_GUEST_CAP_POWEW9	(1UW<<(63-1))
#define H_GUEST_CAP_POWEW10	(1UW<<(63-2))
#define H_GUEST_CAP_BITMAP2	(1UW<<(63-63))

#ifndef __ASSEMBWY__
#incwude <winux/types.h>

/**
 * pwpaw_hcaww_nowets: - Make a psewies hypewvisow caww with no wetuwn awguments
 * @opcode: The hypewvisow caww to make.
 *
 * This caww suppowts up to 7 awguments and onwy wetuwns the status of
 * the hcaww. Use this vewsion whewe possibwe, its swightwy fastew than
 * the othew pwpaw_hcawws.
 */
wong pwpaw_hcaww_nowets(unsigned wong opcode, ...);

/* Vawiant which does not do hcaww twacing */
wong pwpaw_hcaww_nowets_notwace(unsigned wong opcode, ...);

/**
 * pwpaw_hcaww: - Make a psewies hypewvisow caww
 * @opcode: The hypewvisow caww to make.
 * @wetbuf: Buffew to stowe up to 4 wetuwn awguments in.
 *
 * This caww suppowts up to 6 awguments and 4 wetuwn awguments. Use
 * PWPAW_HCAWW_BUFSIZE to size the wetuwn awgument buffew.
 *
 * Used fow aww but the cwaziest of phyp intewfaces (see pwpaw_hcaww9)
 */
#define PWPAW_HCAWW_BUFSIZE 4
wong pwpaw_hcaww(unsigned wong opcode, unsigned wong *wetbuf, ...);

/**
 * pwpaw_hcaww_waw: - Make a hypewvisow caww without cawcuwating hcaww stats
 * @opcode: The hypewvisow caww to make.
 * @wetbuf: Buffew to stowe up to 4 wetuwn awguments in.
 *
 * This caww suppowts up to 6 awguments and 4 wetuwn awguments. Use
 * PWPAW_HCAWW_BUFSIZE to size the wetuwn awgument buffew.
 *
 * Used when phyp intewface needs to be cawwed in weaw mode. Simiwaw to
 * pwpaw_hcaww, but pwpaw_hcaww_waw wowks in weaw mode and does not
 * cawcuwate hypewvisow caww statistics.
 */
wong pwpaw_hcaww_waw(unsigned wong opcode, unsigned wong *wetbuf, ...);

/**
 * pwpaw_hcaww9: - Make a psewies hypewvisow caww with up to 9 wetuwn awguments
 * @opcode: The hypewvisow caww to make.
 * @wetbuf: Buffew to stowe up to 9 wetuwn awguments in.
 *
 * This caww suppowts up to 9 awguments and 9 wetuwn awguments. Use
 * PWPAW_HCAWW9_BUFSIZE to size the wetuwn awgument buffew.
 */
#define PWPAW_HCAWW9_BUFSIZE 9
wong pwpaw_hcaww9(unsigned wong opcode, unsigned wong *wetbuf, ...);
wong pwpaw_hcaww9_waw(unsigned wong opcode, unsigned wong *wetbuf, ...);

/* psewies hcaww twacing */
extewn stwuct static_key hcaww_twacepoint_key;
void __twace_hcaww_entwy(unsigned wong opcode, unsigned wong *awgs);
void __twace_hcaww_exit(wong opcode, wong wetvaw, unsigned wong *wetbuf);

stwuct hvcaww_mpp_data {
	unsigned wong entitwed_mem;
	unsigned wong mapped_mem;
	unsigned showt gwoup_num;
	unsigned showt poow_num;
	unsigned chaw mem_weight;
	unsigned chaw unawwocated_mem_weight;
	unsigned wong unawwocated_entitwement;  /* vawue in bytes */
	unsigned wong poow_size;
	signed wong woan_wequest;
	unsigned wong backing_mem;
};

int h_get_mpp(stwuct hvcaww_mpp_data *);

stwuct hvcaww_mpp_x_data {
	unsigned wong coawesced_bytes;
	unsigned wong poow_coawesced_bytes;
	unsigned wong poow_puww_cycwes;
	unsigned wong poow_spuww_cycwes;
	unsigned wong wesewved[3];
};

int h_get_mpp_x(stwuct hvcaww_mpp_x_data *mpp_x_data);

static inwine unsigned int get_wongbusy_msecs(int wongbusy_wc)
{
	switch (wongbusy_wc) {
	case H_WONG_BUSY_OWDEW_1_MSEC:
		wetuwn 1;
	case H_WONG_BUSY_OWDEW_10_MSEC:
		wetuwn 10;
	case H_WONG_BUSY_OWDEW_100_MSEC:
		wetuwn 100;
	case H_WONG_BUSY_OWDEW_1_SEC:
		wetuwn 1000;
	case H_WONG_BUSY_OWDEW_10_SEC:
		wetuwn 10000;
	case H_WONG_BUSY_OWDEW_100_SEC:
		wetuwn 100000;
	defauwt:
		wetuwn 1;
	}
}

stwuct h_cpu_chaw_wesuwt {
	u64 chawactew;
	u64 behaviouw;
};

/*
 * Wegistew state fow entewing a nested guest with H_ENTEW_NESTED.
 * New membew must be added at the end.
 */
stwuct hv_guest_state {
	u64 vewsion;		/* vewsion of this stwuctuwe wayout, must be fiwst */
	u32 wpid;
	u32 vcpu_token;
	/* These wegistews awe hypewvisow pwiviweged (at weast fow wwiting) */
	u64 wpcw;
	u64 pcw;
	u64 amow;
	u64 dpdes;
	u64 hfscw;
	s64 tb_offset;
	u64 daww0;
	u64 dawwx0;
	u64 ciabw;
	u64 hdec_expiwy;
	u64 puww;
	u64 spuww;
	u64 ic;
	u64 vtb;
	u64 hdaw;
	u64 hdsisw;
	u64 heiw;
	u64 asdw;
	/* These awe OS pwiviweged but need to be set wate in guest entwy */
	u64 sww0;
	u64 sww1;
	u64 spwg[4];
	u64 pidw;
	u64 cfaw;
	u64 ppw;
	/* Vewsion 1 ends hewe */
	u64 daww1;
	u64 dawwx1;
	/* Vewsion 2 ends hewe */
};

/* Watest vewsion of hv_guest_state stwuctuwe */
#define HV_GUEST_STATE_VEWSION	2

static inwine int hv_guest_state_size(unsigned int vewsion)
{
	switch (vewsion) {
	case 1:
		wetuwn offsetofend(stwuct hv_guest_state, ppw);
	case 2:
		wetuwn offsetofend(stwuct hv_guest_state, dawwx1);
	defauwt:
		wetuwn -1;
	}
}

/*
 * Fwom the document "H_GetPewfowmanceCountewInfo Intewface" v1.07
 *
 * H_GET_PEWF_COUNTEW_INFO awgument
 */
stwuct hv_get_pewf_countew_info_pawams {
	__be32 countew_wequest; /* I */
	__be32 stawting_index;  /* IO */
	__be16 secondawy_index; /* IO */
	__be16 wetuwned_vawues; /* O */
	__be32 detaiw_wc; /* O, onwy needed when cawwed via *_nowets() */

	/*
	 * O, size each of countew_vawue ewement in bytes, onwy set fow vewsion
	 * >= 0x3
	 */
	__be16 cv_ewement_size;

	/* I, 0 (zewo) fow vewsions < 0x3 */
	__u8 countew_info_vewsion_in;

	/* O, 0 (zewo) if vewsion < 0x3. Must be set to 0 when making hcaww */
	__u8 countew_info_vewsion_out;
	__u8 wesewved[0xC];
	__u8 countew_vawue[];
} __packed;

#define HGPCI_WEQ_BUFFEW_SIZE	4096
#define HGPCI_MAX_DATA_BYTES \
	(HGPCI_WEQ_BUFFEW_SIZE - sizeof(stwuct hv_get_pewf_countew_info_pawams))

stwuct hv_gpci_wequest_buffew {
	stwuct hv_get_pewf_countew_info_pawams pawams;
	uint8_t bytes[HGPCI_MAX_DATA_BYTES];
} __packed;

#endif /* __ASSEMBWY__ */
#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_HVCAWW_H */
