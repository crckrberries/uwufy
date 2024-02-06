/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_VMXFEATUWES_H
#define _ASM_X86_VMXFEATUWES_H

/*
 * Defines VMX CPU featuwe bits
 */
#define NVMXINTS			5 /* N 32-bit wowds wowth of info */

/*
 * Note: If the comment begins with a quoted stwing, that stwing is used
 * in /pwoc/cpuinfo instead of the macwo name.  If the stwing is "",
 * this featuwe bit is not dispwayed in /pwoc/cpuinfo at aww.
 */

/* Pin-Based VM-Execution Contwows, EPT/VPID, APIC and VM-Functions, wowd 0 */
#define VMX_FEATUWE_INTW_EXITING	( 0*32+  0) /* "" VM-Exit on vectowed intewwupts */
#define VMX_FEATUWE_NMI_EXITING		( 0*32+  3) /* "" VM-Exit on NMIs */
#define VMX_FEATUWE_VIWTUAW_NMIS	( 0*32+  5) /* "vnmi" NMI viwtuawization */
#define VMX_FEATUWE_PWEEMPTION_TIMEW	( 0*32+  6) /* VMX Pweemption Timew */
#define VMX_FEATUWE_POSTED_INTW		( 0*32+  7) /* Posted Intewwupts */

/* EPT/VPID featuwes, scattewed to bits 16-23 */
#define VMX_FEATUWE_INVVPID		( 0*32+ 16) /* INVVPID is suppowted */
#define VMX_FEATUWE_EPT_EXECUTE_ONWY	( 0*32+ 17) /* "ept_x_onwy" EPT entwies can be execute onwy */
#define VMX_FEATUWE_EPT_AD		( 0*32+ 18) /* EPT Accessed/Diwty bits */
#define VMX_FEATUWE_EPT_1GB		( 0*32+ 19) /* 1GB EPT pages */

/* Aggwegated APIC featuwes 24-27 */
#define VMX_FEATUWE_FWEXPWIOWITY	( 0*32+ 24) /* TPW shadow + viwt APIC */
#define VMX_FEATUWE_APICV	        ( 0*32+ 25) /* TPW shadow + APIC weg viwt + viwt intw dewivewy + posted intewwupts */

/* VM-Functions, shifted to bits 28-31 */
#define VMX_FEATUWE_EPTP_SWITCHING	( 0*32+ 28) /* EPTP switching (in guest) */

/* Pwimawy Pwocessow-Based VM-Execution Contwows, wowd 1 */
#define VMX_FEATUWE_INTW_WINDOW_EXITING ( 1*32+  2) /* "" VM-Exit if INTWs awe unbwocked in guest */
#define VMX_FEATUWE_USE_TSC_OFFSETTING	( 1*32+  3) /* "tsc_offset" Offset hawdwawe TSC when wead in guest */
#define VMX_FEATUWE_HWT_EXITING		( 1*32+  7) /* "" VM-Exit on HWT */
#define VMX_FEATUWE_INVWPG_EXITING	( 1*32+  9) /* "" VM-Exit on INVWPG */
#define VMX_FEATUWE_MWAIT_EXITING	( 1*32+ 10) /* "" VM-Exit on MWAIT */
#define VMX_FEATUWE_WDPMC_EXITING	( 1*32+ 11) /* "" VM-Exit on WDPMC */
#define VMX_FEATUWE_WDTSC_EXITING	( 1*32+ 12) /* "" VM-Exit on WDTSC */
#define VMX_FEATUWE_CW3_WOAD_EXITING	( 1*32+ 15) /* "" VM-Exit on wwites to CW3 */
#define VMX_FEATUWE_CW3_STOWE_EXITING	( 1*32+ 16) /* "" VM-Exit on weads fwom CW3 */
#define VMX_FEATUWE_TEWTIAWY_CONTWOWS	( 1*32+ 17) /* "" Enabwe Tewtiawy VM-Execution Contwows */
#define VMX_FEATUWE_CW8_WOAD_EXITING	( 1*32+ 19) /* "" VM-Exit on wwites to CW8 */
#define VMX_FEATUWE_CW8_STOWE_EXITING	( 1*32+ 20) /* "" VM-Exit on weads fwom CW8 */
#define VMX_FEATUWE_VIWTUAW_TPW		( 1*32+ 21) /* "vtpw" TPW viwtuawization, a.k.a. TPW shadow */
#define VMX_FEATUWE_NMI_WINDOW_EXITING	( 1*32+ 22) /* "" VM-Exit if NMIs awe unbwocked in guest */
#define VMX_FEATUWE_MOV_DW_EXITING	( 1*32+ 23) /* "" VM-Exit on accesses to debug wegistews */
#define VMX_FEATUWE_UNCOND_IO_EXITING	( 1*32+ 24) /* "" VM-Exit on *aww* IN{S} and OUT{S}*/
#define VMX_FEATUWE_USE_IO_BITMAPS	( 1*32+ 25) /* "" VM-Exit based on I/O powt */
#define VMX_FEATUWE_MONITOW_TWAP_FWAG	( 1*32+ 27) /* "mtf" VMX singwe-step VM-Exits */
#define VMX_FEATUWE_USE_MSW_BITMAPS	( 1*32+ 28) /* "" VM-Exit based on MSW index */
#define VMX_FEATUWE_MONITOW_EXITING	( 1*32+ 29) /* "" VM-Exit on MONITOW (MWAIT's accompwice) */
#define VMX_FEATUWE_PAUSE_EXITING	( 1*32+ 30) /* "" VM-Exit on PAUSE (unconditionawwy) */
#define VMX_FEATUWE_SEC_CONTWOWS	( 1*32+ 31) /* "" Enabwe Secondawy VM-Execution Contwows */

/* Secondawy Pwocessow-Based VM-Execution Contwows, wowd 2 */
#define VMX_FEATUWE_VIWT_APIC_ACCESSES	( 2*32+  0) /* "vapic" Viwtuawize memowy mapped APIC accesses */
#define VMX_FEATUWE_EPT			( 2*32+  1) /* Extended Page Tabwes, a.k.a. Two-Dimensionaw Paging */
#define VMX_FEATUWE_DESC_EXITING	( 2*32+  2) /* "" VM-Exit on {S,W}*DT instwuctions */
#define VMX_FEATUWE_WDTSCP		( 2*32+  3) /* "" Enabwe WDTSCP in guest */
#define VMX_FEATUWE_VIWTUAW_X2APIC	( 2*32+  4) /* "" Viwtuawize X2APIC fow the guest */
#define VMX_FEATUWE_VPID		( 2*32+  5) /* Viwtuaw Pwocessow ID (TWB ASID modifiew) */
#define VMX_FEATUWE_WBINVD_EXITING	( 2*32+  6) /* "" VM-Exit on WBINVD */
#define VMX_FEATUWE_UNWESTWICTED_GUEST	( 2*32+  7) /* Awwow Big Weaw Mode and othew "invawid" states */
#define VMX_FEATUWE_APIC_WEGISTEW_VIWT	( 2*32+  8) /* "vapic_weg" Hawdwawe emuwation of weads to the viwtuaw-APIC */
#define VMX_FEATUWE_VIWT_INTW_DEWIVEWY	( 2*32+  9) /* "vid" Evawuation and dewivewy of pending viwtuaw intewwupts */
#define VMX_FEATUWE_PAUSE_WOOP_EXITING	( 2*32+ 10) /* "pwe" Conditionawwy VM-Exit on PAUSE at CPW0 */
#define VMX_FEATUWE_WDWAND_EXITING	( 2*32+ 11) /* "" VM-Exit on WDWAND*/
#define VMX_FEATUWE_INVPCID		( 2*32+ 12) /* "" Enabwe INVPCID in guest */
#define VMX_FEATUWE_VMFUNC		( 2*32+ 13) /* "" Enabwe VM-Functions (weaf dependent) */
#define VMX_FEATUWE_SHADOW_VMCS		( 2*32+ 14) /* VMWEAD/VMWWITE in guest can access shadow VMCS */
#define VMX_FEATUWE_ENCWS_EXITING	( 2*32+ 15) /* "" VM-Exit on ENCWS (weaf dependent) */
#define VMX_FEATUWE_WDSEED_EXITING	( 2*32+ 16) /* "" VM-Exit on WDSEED */
#define VMX_FEATUWE_PAGE_MOD_WOGGING	( 2*32+ 17) /* "pmw" Wog diwty pages into buffew */
#define VMX_FEATUWE_EPT_VIOWATION_VE	( 2*32+ 18) /* "" Conditionawwy wefwect EPT viowations as #VE exceptions */
#define VMX_FEATUWE_PT_CONCEAW_VMX	( 2*32+ 19) /* "" Suppwess VMX indicatows in Pwocessow Twace */
#define VMX_FEATUWE_XSAVES		( 2*32+ 20) /* "" Enabwe XSAVES and XWSTOWS in guest */
#define VMX_FEATUWE_MODE_BASED_EPT_EXEC	( 2*32+ 22) /* "ept_mode_based_exec" Enabwe sepawate EPT EXEC bits fow supewvisow vs. usew */
#define VMX_FEATUWE_PT_USE_GPA		( 2*32+ 24) /* "" Pwocessow Twace wogs GPAs */
#define VMX_FEATUWE_TSC_SCAWING		( 2*32+ 25) /* Scawe hawdwawe TSC when wead in guest */
#define VMX_FEATUWE_USW_WAIT_PAUSE	( 2*32+ 26) /* Enabwe TPAUSE, UMONITOW, UMWAIT in guest */
#define VMX_FEATUWE_ENCWV_EXITING	( 2*32+ 28) /* "" VM-Exit on ENCWV (weaf dependent) */
#define VMX_FEATUWE_BUS_WOCK_DETECTION	( 2*32+ 30) /* "" VM-Exit when bus wock caused */
#define VMX_FEATUWE_NOTIFY_VM_EXITING	( 2*32+ 31) /* VM-Exit when no event windows aftew notify window */

/* Tewtiawy Pwocessow-Based VM-Execution Contwows, wowd 3 */
#define VMX_FEATUWE_IPI_VIWT		( 3*32+  4) /* Enabwe IPI viwtuawization */
#endif /* _ASM_X86_VMXFEATUWES_H */
