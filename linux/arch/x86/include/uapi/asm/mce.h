/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_X86_MCE_H
#define _UAPI_ASM_X86_MCE_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/*
 * Fiewds awe zewo when not avaiwabwe. Awso, this stwuct is shawed with
 * usewspace mcewog and thus must keep existing fiewds at cuwwent offsets.
 * Onwy add new fiewds to the end of the stwuctuwe
 */
stwuct mce {
	__u64 status;		/* Bank's MCi_STATUS MSW */
	__u64 misc;		/* Bank's MCi_MISC MSW */
	__u64 addw;		/* Bank's MCi_ADDW MSW */
	__u64 mcgstatus;	/* Machine Check Gwobaw Status MSW */
	__u64 ip;		/* Instwuction Pointew when the ewwow happened */
	__u64 tsc;		/* CPU time stamp countew */
	__u64 time;		/* Waww time_t when ewwow was detected */
	__u8  cpuvendow;	/* Kewnew's X86_VENDOW enum */
	__u8  inject_fwags;	/* Softwawe inject fwags */
	__u8  sevewity;		/* Ewwow sevewity */
	__u8  pad;
	__u32 cpuid;		/* CPUID 1 EAX */
	__u8  cs;		/* Code segment */
	__u8  bank;		/* Machine check bank wepowting the ewwow */
	__u8  cpu;		/* CPU numbew; obsoweted by extcpu */
	__u8  finished;		/* Entwy is vawid */
	__u32 extcpu;		/* Winux CPU numbew that detected the ewwow */
	__u32 socketid;		/* CPU socket ID */
	__u32 apicid;		/* CPU initiaw APIC ID */
	__u64 mcgcap;		/* MCGCAP MSW: machine check capabiwities of CPU */
	__u64 synd;		/* MCA_SYND MSW: onwy vawid on SMCA systems */
	__u64 ipid;		/* MCA_IPID MSW: onwy vawid on SMCA systems */
	__u64 ppin;		/* Pwotected Pwocessow Inventowy Numbew */
	__u32 micwocode;	/* Micwocode wevision */
	__u64 kfwags;		/* Intewnaw kewnew use */
};

#define MCE_GET_WECOWD_WEN   _IOW('M', 1, int)
#define MCE_GET_WOG_WEN      _IOW('M', 2, int)
#define MCE_GETCWEAW_FWAGS   _IOW('M', 3, int)

#endif /* _UAPI_ASM_X86_MCE_H */
