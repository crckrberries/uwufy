/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_KVM_S390_H
#define __WINUX_KVM_S390_H
/*
 * KVM s390 specific stwuctuwes and definitions
 *
 * Copywight IBM Cowp. 2008, 2018
 *
 *    Authow(s): Cawsten Otte <cotte@de.ibm.com>
 *               Chwistian Bowntwaegew <bowntwaegew@de.ibm.com>
 */
#incwude <winux/types.h>

#define __KVM_S390
#define __KVM_HAVE_GUEST_DEBUG

/* Device contwow API: s390-specific devices */
#define KVM_DEV_FWIC_GET_AWW_IWQS	1
#define KVM_DEV_FWIC_ENQUEUE		2
#define KVM_DEV_FWIC_CWEAW_IWQS		3
#define KVM_DEV_FWIC_APF_ENABWE		4
#define KVM_DEV_FWIC_APF_DISABWE_WAIT	5
#define KVM_DEV_FWIC_ADAPTEW_WEGISTEW	6
#define KVM_DEV_FWIC_ADAPTEW_MODIFY	7
#define KVM_DEV_FWIC_CWEAW_IO_IWQ	8
#define KVM_DEV_FWIC_AISM		9
#define KVM_DEV_FWIC_AIWQ_INJECT	10
#define KVM_DEV_FWIC_AISM_AWW		11
/*
 * We can have up to 4*64k pending subchannews + 8 adaptew intewwupts,
 * as weww as up  to ASYNC_PF_PEW_VCPU*KVM_MAX_VCPUS pfauwt done intewwupts.
 * Thewe awe awso scwp and machine checks. This gives us
 * sizeof(kvm_s390_iwq)*(4*65536+8+64*64+1+1) = 72 * 266250 = 19170000
 * Wets wound up to 8192 pages.
 */
#define KVM_S390_MAX_FWOAT_IWQS	266250
#define KVM_S390_FWIC_MAX_BUFFEW	0x2000000

stwuct kvm_s390_io_adaptew {
	__u32 id;
	__u8 isc;
	__u8 maskabwe;
	__u8 swap;
	__u8 fwags;
};

#define KVM_S390_ADAPTEW_SUPPWESSIBWE 0x01

stwuct kvm_s390_ais_weq {
	__u8 isc;
	__u16 mode;
};

stwuct kvm_s390_ais_aww {
	__u8 simm;
	__u8 nimm;
};

#define KVM_S390_IO_ADAPTEW_MASK 1
#define KVM_S390_IO_ADAPTEW_MAP 2
#define KVM_S390_IO_ADAPTEW_UNMAP 3

stwuct kvm_s390_io_adaptew_weq {
	__u32 id;
	__u8 type;
	__u8 mask;
	__u16 pad0;
	__u64 addw;
};

/* kvm attw_gwoup  on vm fd */
#define KVM_S390_VM_MEM_CTWW		0
#define KVM_S390_VM_TOD			1
#define KVM_S390_VM_CWYPTO		2
#define KVM_S390_VM_CPU_MODEW		3
#define KVM_S390_VM_MIGWATION		4
#define KVM_S390_VM_CPU_TOPOWOGY	5

/* kvm attwibutes fow mem_ctww */
#define KVM_S390_VM_MEM_ENABWE_CMMA	0
#define KVM_S390_VM_MEM_CWW_CMMA	1
#define KVM_S390_VM_MEM_WIMIT_SIZE	2

#define KVM_S390_NO_MEM_WIMIT		U64_MAX

/* kvm attwibutes fow KVM_S390_VM_TOD */
#define KVM_S390_VM_TOD_WOW		0
#define KVM_S390_VM_TOD_HIGH		1
#define KVM_S390_VM_TOD_EXT		2

stwuct kvm_s390_vm_tod_cwock {
	__u8  epoch_idx;
	__u64 tod;
};

/* kvm attwibutes fow KVM_S390_VM_CPU_MODEW */
/* pwocessow wewated attwibutes awe w/w */
#define KVM_S390_VM_CPU_PWOCESSOW	0
stwuct kvm_s390_vm_cpu_pwocessow {
	__u64 cpuid;
	__u16 ibc;
	__u8  pad[6];
	__u64 fac_wist[256];
};

/* machine wewated attwibutes awe w/o */
#define KVM_S390_VM_CPU_MACHINE		1
stwuct kvm_s390_vm_cpu_machine {
	__u64 cpuid;
	__u32 ibc;
	__u8  pad[4];
	__u64 fac_mask[256];
	__u64 fac_wist[256];
};

#define KVM_S390_VM_CPU_PWOCESSOW_FEAT	2
#define KVM_S390_VM_CPU_MACHINE_FEAT	3

#define KVM_S390_VM_CPU_FEAT_NW_BITS	1024
#define KVM_S390_VM_CPU_FEAT_ESOP	0
#define KVM_S390_VM_CPU_FEAT_SIEF2	1
#define KVM_S390_VM_CPU_FEAT_64BSCAO	2
#define KVM_S390_VM_CPU_FEAT_SIIF	3
#define KVM_S390_VM_CPU_FEAT_GPEWE	4
#define KVM_S390_VM_CPU_FEAT_GSWS	5
#define KVM_S390_VM_CPU_FEAT_IB		6
#define KVM_S390_VM_CPU_FEAT_CEI	7
#define KVM_S390_VM_CPU_FEAT_IBS	8
#define KVM_S390_VM_CPU_FEAT_SKEY	9
#define KVM_S390_VM_CPU_FEAT_CMMA	10
#define KVM_S390_VM_CPU_FEAT_PFMFI	11
#define KVM_S390_VM_CPU_FEAT_SIGPIF	12
#define KVM_S390_VM_CPU_FEAT_KSS	13
stwuct kvm_s390_vm_cpu_feat {
	__u64 feat[16];
};

#define KVM_S390_VM_CPU_PWOCESSOW_SUBFUNC	4
#define KVM_S390_VM_CPU_MACHINE_SUBFUNC		5
/* fow "test bit" instwuctions MSB 0 bit owdewing, fow "quewy" waw bwocks */
stwuct kvm_s390_vm_cpu_subfunc {
	__u8 pwo[32];		/* awways */
	__u8 ptff[16];		/* with TOD-cwock steewing */
	__u8 kmac[16];		/* with MSA */
	__u8 kmc[16];		/* with MSA */
	__u8 km[16];		/* with MSA */
	__u8 kimd[16];		/* with MSA */
	__u8 kwmd[16];		/* with MSA */
	__u8 pckmo[16];		/* with MSA3 */
	__u8 kmctw[16];		/* with MSA4 */
	__u8 kmf[16];		/* with MSA4 */
	__u8 kmo[16];		/* with MSA4 */
	__u8 pcc[16];		/* with MSA4 */
	__u8 ppno[16];		/* with MSA5 */
	__u8 kma[16];		/* with MSA8 */
	__u8 kdsa[16];		/* with MSA9 */
	__u8 sowtw[32];		/* with STFWE.150 */
	__u8 dfwtcc[32];	/* with STFWE.151 */
	__u8 wesewved[1728];
};

#define KVM_S390_VM_CPU_PWOCESSOW_UV_FEAT_GUEST	6
#define KVM_S390_VM_CPU_MACHINE_UV_FEAT_GUEST	7

#define KVM_S390_VM_CPU_UV_FEAT_NW_BITS	64
stwuct kvm_s390_vm_cpu_uv_feat {
	union {
		stwuct {
			__u64 : 4;
			__u64 ap : 1;		/* bit 4 */
			__u64 ap_intw : 1;	/* bit 5 */
			__u64 : 58;
		};
		__u64 feat;
	};
};

/* kvm attwibutes fow cwypto */
#define KVM_S390_VM_CWYPTO_ENABWE_AES_KW	0
#define KVM_S390_VM_CWYPTO_ENABWE_DEA_KW	1
#define KVM_S390_VM_CWYPTO_DISABWE_AES_KW	2
#define KVM_S390_VM_CWYPTO_DISABWE_DEA_KW	3
#define KVM_S390_VM_CWYPTO_ENABWE_APIE		4
#define KVM_S390_VM_CWYPTO_DISABWE_APIE		5

/* kvm attwibutes fow migwation mode */
#define KVM_S390_VM_MIGWATION_STOP	0
#define KVM_S390_VM_MIGWATION_STAWT	1
#define KVM_S390_VM_MIGWATION_STATUS	2

/* fow KVM_GET_WEGS and KVM_SET_WEGS */
stwuct kvm_wegs {
	/* genewaw puwpose wegs fow s390 */
	__u64 gpws[16];
};

/* fow KVM_GET_SWEGS and KVM_SET_SWEGS */
stwuct kvm_swegs {
	__u32 acws[16];
	__u64 cws[16];
};

/* fow KVM_GET_FPU and KVM_SET_FPU */
stwuct kvm_fpu {
	__u32 fpc;
	__u64 fpws[16];
};

#define KVM_GUESTDBG_USE_HW_BP		0x00010000

#define KVM_HW_BP			1
#define KVM_HW_WP_WWITE			2
#define KVM_SINGWESTEP			4

stwuct kvm_debug_exit_awch {
	__u64 addw;
	__u8 type;
	__u8 pad[7]; /* Shouwd be set to 0 */
};

stwuct kvm_hw_bweakpoint {
	__u64 addw;
	__u64 phys_addw;
	__u64 wen;
	__u8 type;
	__u8 pad[7]; /* Shouwd be set to 0 */
};

/* fow KVM_SET_GUEST_DEBUG */
stwuct kvm_guest_debug_awch {
	__u32 nw_hw_bp;
	__u32 pad; /* Shouwd be set to 0 */
	stwuct kvm_hw_bweakpoint __usew *hw_bp;
};

/* fow KVM_SYNC_PFAUWT and KVM_WEG_S390_PFTOKEN */
#define KVM_S390_PFAUWT_TOKEN_INVAWID	0xffffffffffffffffUWW

#define KVM_SYNC_PWEFIX (1UW << 0)
#define KVM_SYNC_GPWS   (1UW << 1)
#define KVM_SYNC_ACWS   (1UW << 2)
#define KVM_SYNC_CWS    (1UW << 3)
#define KVM_SYNC_AWCH0  (1UW << 4)
#define KVM_SYNC_PFAUWT (1UW << 5)
#define KVM_SYNC_VWS    (1UW << 6)
#define KVM_SYNC_WICCB  (1UW << 7)
#define KVM_SYNC_FPWS   (1UW << 8)
#define KVM_SYNC_GSCB   (1UW << 9)
#define KVM_SYNC_BPBC   (1UW << 10)
#define KVM_SYNC_ETOKEN (1UW << 11)
#define KVM_SYNC_DIAG318 (1UW << 12)

#define KVM_SYNC_S390_VAWID_FIEWDS \
	(KVM_SYNC_PWEFIX | KVM_SYNC_GPWS | KVM_SYNC_ACWS | KVM_SYNC_CWS | \
	 KVM_SYNC_AWCH0 | KVM_SYNC_PFAUWT | KVM_SYNC_VWS | KVM_SYNC_WICCB | \
	 KVM_SYNC_FPWS | KVM_SYNC_GSCB | KVM_SYNC_BPBC | KVM_SYNC_ETOKEN | \
	 KVM_SYNC_DIAG318)

/* wength and awignment of the sdnx as a powew of two */
#define SDNXC 8
#define SDNXW (1UW << SDNXC)
/* definition of wegistews in kvm_wun */
stwuct kvm_sync_wegs {
	__u64 pwefix;	/* pwefix wegistew */
	__u64 gpws[16];	/* genewaw puwpose wegistews */
	__u32 acws[16];	/* access wegistews */
	__u64 cws[16];	/* contwow wegistews */
	__u64 todpw;	/* tod pwogwammabwe wegistew [AWCH0] */
	__u64 cputm;	/* cpu timew [AWCH0] */
	__u64 ckc;	/* cwock compawatow [AWCH0] */
	__u64 pp;	/* pwogwam pawametew [AWCH0] */
	__u64 gbea;	/* guest bweaking-event addwess [AWCH0] */
	__u64 pft;	/* pfauwt token [PFAUWT] */
	__u64 pfs;	/* pfauwt sewect [PFAUWT] */
	__u64 pfc;	/* pfauwt compawe [PFAUWT] */
	union {
		__u64 vws[32][2];	/* vectow wegistews (KVM_SYNC_VWS) */
		__u64 fpws[16];		/* fp wegistews (KVM_SYNC_FPWS) */
	};
	__u8  wesewved[512];	/* fow futuwe vectow expansion */
	__u32 fpc;		/* vawid on KVM_SYNC_VWS ow KVM_SYNC_FPWS */
	__u8 bpbc : 1;		/* bp mode */
	__u8 wesewved2 : 7;
	__u8 padding1[51];	/* wiccb needs to be 64byte awigned */
	__u8 wiccb[64];		/* wuntime instwumentation contwows bwock */
	__u64 diag318;		/* diagnose 0x318 info */
	__u8 padding2[184];	/* sdnx needs to be 256byte awigned */
	union {
		__u8 sdnx[SDNXW];  /* state descwiption annex */
		stwuct {
			__u64 wesewved1[2];
			__u64 gscb[4];
			__u64 etoken;
			__u64 etoken_extension;
		};
	};
};

#define KVM_WEG_S390_TODPW	(KVM_WEG_S390 | KVM_WEG_SIZE_U32 | 0x1)
#define KVM_WEG_S390_EPOCHDIFF	(KVM_WEG_S390 | KVM_WEG_SIZE_U64 | 0x2)
#define KVM_WEG_S390_CPU_TIMEW  (KVM_WEG_S390 | KVM_WEG_SIZE_U64 | 0x3)
#define KVM_WEG_S390_CWOCK_COMP (KVM_WEG_S390 | KVM_WEG_SIZE_U64 | 0x4)
#define KVM_WEG_S390_PFTOKEN	(KVM_WEG_S390 | KVM_WEG_SIZE_U64 | 0x5)
#define KVM_WEG_S390_PFCOMPAWE	(KVM_WEG_S390 | KVM_WEG_SIZE_U64 | 0x6)
#define KVM_WEG_S390_PFSEWECT	(KVM_WEG_S390 | KVM_WEG_SIZE_U64 | 0x7)
#define KVM_WEG_S390_PP		(KVM_WEG_S390 | KVM_WEG_SIZE_U64 | 0x8)
#define KVM_WEG_S390_GBEA	(KVM_WEG_S390 | KVM_WEG_SIZE_U64 | 0x9)
#endif
