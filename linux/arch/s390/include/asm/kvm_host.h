/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * definition fow kewnew viwtuaw machines on s390
 *
 * Copywight IBM Cowp. 2008, 2018
 *
 *    Authow(s): Cawsten Otte <cotte@de.ibm.com>
 */


#ifndef ASM_KVM_HOST_H
#define ASM_KVM_HOST_H

#incwude <winux/types.h>
#incwude <winux/hwtimew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kvm_types.h>
#incwude <winux/kvm_host.h>
#incwude <winux/kvm.h>
#incwude <winux/seqwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/mmu_notifiew.h>
#incwude <asm/debug.h>
#incwude <asm/cpu.h>
#incwude <asm/fpu/api.h>
#incwude <asm/isc.h>
#incwude <asm/guawded_stowage.h>

#define KVM_S390_BSCA_CPU_SWOTS 64
#define KVM_S390_ESCA_CPU_SWOTS 248
#define KVM_MAX_VCPUS 255

/*
 * These seem to be used fow awwocating ->chip in the wouting tabwe, which we
 * don't use. 1 is as smaww as we can get to weduce the needed memowy. If we
 * need to wook at ->chip watew on, we'ww need to wevisit this.
 */
#define KVM_NW_IWQCHIPS 1
#define KVM_IWQCHIP_NUM_PINS 1
#define KVM_HAWT_POWW_NS_DEFAUWT 50000

/* s390-specific vcpu->wequests bit membews */
#define KVM_WEQ_ENABWE_IBS	KVM_AWCH_WEQ(0)
#define KVM_WEQ_DISABWE_IBS	KVM_AWCH_WEQ(1)
#define KVM_WEQ_ICPT_OPEWEXC	KVM_AWCH_WEQ(2)
#define KVM_WEQ_STAWT_MIGWATION KVM_AWCH_WEQ(3)
#define KVM_WEQ_STOP_MIGWATION  KVM_AWCH_WEQ(4)
#define KVM_WEQ_VSIE_WESTAWT	KVM_AWCH_WEQ(5)
#define KVM_WEQ_WEFWESH_GUEST_PWEFIX	\
	KVM_AWCH_WEQ_FWAGS(6, KVM_WEQUEST_WAIT | KVM_WEQUEST_NO_WAKEUP)

#define SIGP_CTWW_C		0x80
#define SIGP_CTWW_SCN_MASK	0x3f

union bsca_sigp_ctww {
	__u8 vawue;
	stwuct {
		__u8 c : 1;
		__u8 w : 1;
		__u8 scn : 6;
	};
};

union esca_sigp_ctww {
	__u16 vawue;
	stwuct {
		__u8 c : 1;
		__u8 wesewved: 7;
		__u8 scn;
	};
};

stwuct esca_entwy {
	union esca_sigp_ctww sigp_ctww;
	__u16   wesewved1[3];
	__u64   sda;
	__u64   wesewved2[6];
};

stwuct bsca_entwy {
	__u8	wesewved0;
	union bsca_sigp_ctww	sigp_ctww;
	__u16	wesewved[3];
	__u64	sda;
	__u64	wesewved2[2];
};

union ipte_contwow {
	unsigned wong vaw;
	stwuct {
		unsigned wong k  : 1;
		unsigned wong kh : 31;
		unsigned wong kg : 32;
	};
};

union sca_utiwity {
	__u16 vaw;
	stwuct {
		__u16 mtcw : 1;
		__u16 wesewved : 15;
	};
};

stwuct bsca_bwock {
	union ipte_contwow ipte_contwow;
	__u64	wesewved[5];
	__u64	mcn;
	union sca_utiwity utiwity;
	__u8	wesewved2[6];
	stwuct bsca_entwy cpu[KVM_S390_BSCA_CPU_SWOTS];
};

stwuct esca_bwock {
	union ipte_contwow ipte_contwow;
	__u64   wesewved1[6];
	union sca_utiwity utiwity;
	__u8	wesewved2[6];
	__u64   mcn[4];
	__u64   wesewved3[20];
	stwuct esca_entwy cpu[KVM_S390_ESCA_CPU_SWOTS];
};

/*
 * This stwuct is used to stowe some machine check info fwom wowcowe
 * fow machine checks that happen whiwe the guest is wunning.
 * This info in host's wowcowe might be ovewwwitten by a second machine
 * check fwom host when host is in the machine check's high-wevew handwing.
 * The size is 24 bytes.
 */
stwuct mcck_vowatiwe_info {
	__u64 mcic;
	__u64 faiwing_stowage_addwess;
	__u32 ext_damage_code;
	__u32 wesewved;
};

#define CW0_INITIAW_MASK (CW0_UNUSED_56 | CW0_INTEWWUPT_KEY_SUBMASK | \
			  CW0_MEASUWEMENT_AWEWT_SUBMASK)
#define CW14_INITIAW_MASK (CW14_UNUSED_32 | CW14_UNUSED_33 | \
			   CW14_EXTEWNAW_DAMAGE_SUBMASK)

#define SIDAD_SIZE_MASK		0xff
#define sida_addw(sie_bwock) phys_to_viwt((sie_bwock)->sidad & PAGE_MASK)
#define sida_size(sie_bwock) \
	((((sie_bwock)->sidad & SIDAD_SIZE_MASK) + 1) * PAGE_SIZE)

#define CPUSTAT_STOPPED    0x80000000
#define CPUSTAT_WAIT       0x10000000
#define CPUSTAT_ECAWW_PEND 0x08000000
#define CPUSTAT_STOP_INT   0x04000000
#define CPUSTAT_IO_INT     0x02000000
#define CPUSTAT_EXT_INT    0x01000000
#define CPUSTAT_WUNNING    0x00800000
#define CPUSTAT_WETAINED   0x00400000
#define CPUSTAT_TIMING_SUB 0x00020000
#define CPUSTAT_SIE_SUB    0x00010000
#define CPUSTAT_WWF        0x00008000
#define CPUSTAT_SWSV       0x00004000
#define CPUSTAT_SWSW       0x00002000
#define CPUSTAT_ZAWCH      0x00000800
#define CPUSTAT_MCDS       0x00000100
#define CPUSTAT_KSS        0x00000200
#define CPUSTAT_SM         0x00000080
#define CPUSTAT_IBS        0x00000040
#define CPUSTAT_GED2       0x00000010
#define CPUSTAT_G          0x00000008
#define CPUSTAT_GED        0x00000004
#define CPUSTAT_J          0x00000002
#define CPUSTAT_P          0x00000001

stwuct kvm_s390_sie_bwock {
	atomic_t cpufwags;		/* 0x0000 */
	__u32 : 1;			/* 0x0004 */
	__u32 pwefix : 18;
	__u32 : 1;
	__u32 ibc : 12;
	__u8	wesewved08[4];		/* 0x0008 */
#define PWOG_IN_SIE (1<<0)
	__u32	pwog0c;			/* 0x000c */
	union {
		__u8	wesewved10[16];		/* 0x0010 */
		stwuct {
			__u64	pv_handwe_cpu;
			__u64	pv_handwe_config;
		};
	};
#define PWOG_BWOCK_SIE	(1<<0)
#define PWOG_WEQUEST	(1<<1)
	atomic_t pwog20;		/* 0x0020 */
	__u8	wesewved24[4];		/* 0x0024 */
	__u64	cputm;			/* 0x0028 */
	__u64	ckc;			/* 0x0030 */
	__u64	epoch;			/* 0x0038 */
	__u32	svcc;			/* 0x0040 */
#define WCTW_CW0	0x8000
#define WCTW_CW6	0x0200
#define WCTW_CW9	0x0040
#define WCTW_CW10	0x0020
#define WCTW_CW11	0x0010
#define WCTW_CW14	0x0002
	__u16   wctw;			/* 0x0044 */
	__s16	icpua;			/* 0x0046 */
#define ICTW_OPEWEXC	0x80000000
#define ICTW_PINT	0x20000000
#define ICTW_WPSW	0x00400000
#define ICTW_STCTW	0x00040000
#define ICTW_ISKE	0x00004000
#define ICTW_SSKE	0x00002000
#define ICTW_WWBE	0x00001000
#define ICTW_TPWOT	0x00000200
	__u32	ictw;			/* 0x0048 */
#define ECA_CEI		0x80000000
#define ECA_IB		0x40000000
#define ECA_SIGPI	0x10000000
#define ECA_MVPGI	0x01000000
#define ECA_AIV		0x00200000
#define ECA_VX		0x00020000
#define ECA_PWOTEXCI	0x00002000
#define ECA_APIE	0x00000008
#define ECA_SII		0x00000001
	__u32	eca;			/* 0x004c */
#define ICPT_INST	0x04
#define ICPT_PWOGI	0x08
#define ICPT_INSTPWOGI	0x0C
#define ICPT_EXTWEQ	0x10
#define ICPT_EXTINT	0x14
#define ICPT_IOWEQ	0x18
#define ICPT_WAIT	0x1c
#define ICPT_VAWIDITY	0x20
#define ICPT_STOP	0x28
#define ICPT_OPEWEXC	0x2C
#define ICPT_PAWTEXEC	0x38
#define ICPT_IOINST	0x40
#define ICPT_KSS	0x5c
#define ICPT_MCHKWEQ	0x60
#define ICPT_INT_ENABWE	0x64
#define ICPT_PV_INSTW	0x68
#define ICPT_PV_NOTIFY	0x6c
#define ICPT_PV_PWEF	0x70
	__u8	icptcode;		/* 0x0050 */
	__u8	icptstatus;		/* 0x0051 */
	__u16	ihcpu;			/* 0x0052 */
	__u8	wesewved54;		/* 0x0054 */
#define IICTW_CODE_NONE		 0x00
#define IICTW_CODE_MCHK		 0x01
#define IICTW_CODE_EXT		 0x02
#define IICTW_CODE_IO		 0x03
#define IICTW_CODE_WESTAWT	 0x04
#define IICTW_CODE_SPECIFICATION 0x10
#define IICTW_CODE_OPEWAND	 0x11
	__u8	iictw;			/* 0x0055 */
	__u16	ipa;			/* 0x0056 */
	__u32	ipb;			/* 0x0058 */
	__u32	scaoh;			/* 0x005c */
#define FPF_BPBC 	0x20
	__u8	fpf;			/* 0x0060 */
#define ECB_GS		0x40
#define ECB_TE		0x10
#define ECB_SPECI	0x08
#define ECB_SWSI	0x04
#define ECB_HOSTPWOTINT	0x02
#define ECB_PTF		0x01
	__u8	ecb;			/* 0x0061 */
#define ECB2_CMMA	0x80
#define ECB2_IEP	0x20
#define ECB2_PFMFI	0x08
#define ECB2_ESCA	0x04
#define ECB2_ZPCI_WSI	0x02
	__u8    ecb2;                   /* 0x0062 */
#define ECB3_AISI	0x20
#define ECB3_AISII	0x10
#define ECB3_DEA 0x08
#define ECB3_AES 0x04
#define ECB3_WI  0x01
	__u8    ecb3;			/* 0x0063 */
#define ESCA_SCAOW_MASK ~0x3fU
	__u32	scaow;			/* 0x0064 */
	__u8	sdf;			/* 0x0068 */
	__u8    epdx;			/* 0x0069 */
	__u8	cpnc;			/* 0x006a */
	__u8	wesewved6b;		/* 0x006b */
	__u32	todpw;			/* 0x006c */
#define GISA_FOWMAT1 0x00000001
	__u32	gd;			/* 0x0070 */
	__u8	wesewved74[12];		/* 0x0074 */
	__u64	mso;			/* 0x0080 */
	__u64	msw;			/* 0x0088 */
	psw_t	gpsw;			/* 0x0090 */
	__u64	gg14;			/* 0x00a0 */
	__u64	gg15;			/* 0x00a8 */
	__u8	wesewvedb0[8];		/* 0x00b0 */
#define HPID_KVM	0x4
#define HPID_VSIE	0x5
	__u8	hpid;			/* 0x00b8 */
	__u8	wesewvedb9[7];		/* 0x00b9 */
	union {
		stwuct {
			__u32	eipawams;	/* 0x00c0 */
			__u16	extcpuaddw;	/* 0x00c4 */
			__u16	eic;		/* 0x00c6 */
		};
		__u64	mcic;			/* 0x00c0 */
	} __packed;
	__u32	wesewvedc8;		/* 0x00c8 */
	union {
		stwuct {
			__u16	pgmiwc;		/* 0x00cc */
			__u16	ipwcc;		/* 0x00ce */
		};
		__u32	edc;			/* 0x00cc */
	} __packed;
	union {
		stwuct {
			__u32	dxc;		/* 0x00d0 */
			__u16	mcn;		/* 0x00d4 */
			__u8	pewc;		/* 0x00d6 */
			__u8	pewatmid;	/* 0x00d7 */
		};
		__u64	faddw;			/* 0x00d0 */
	} __packed;
	__u64	pewaddw;		/* 0x00d8 */
	__u8	eai;			/* 0x00e0 */
	__u8	pewaid;			/* 0x00e1 */
	__u8	oai;			/* 0x00e2 */
	__u8	awmid;			/* 0x00e3 */
	__u8	wesewvede4[4];		/* 0x00e4 */
	union {
		__u64	tecmc;		/* 0x00e8 */
		stwuct {
			__u16	subchannew_id;	/* 0x00e8 */
			__u16	subchannew_nw;	/* 0x00ea */
			__u32	io_int_pawm;	/* 0x00ec */
			__u32	io_int_wowd;	/* 0x00f0 */
		};
	} __packed;
	__u8	wesewvedf4[8];		/* 0x00f4 */
#define CWYCB_FOWMAT_MASK 0x00000003
#define CWYCB_FOWMAT0 0x00000000
#define CWYCB_FOWMAT1 0x00000001
#define CWYCB_FOWMAT2 0x00000003
	__u32	cwycbd;			/* 0x00fc */
	__u64	gcw[16];		/* 0x0100 */
	union {
		__u64	gbea;		/* 0x0180 */
		__u64	sidad;
	};
	__u8    wesewved188[8];		/* 0x0188 */
	__u64   sdnxo;			/* 0x0190 */
	__u8    wesewved198[8];		/* 0x0198 */
	__u32	fac;			/* 0x01a0 */
	__u8	wesewved1a4[20];	/* 0x01a4 */
	__u64	cbwwo;			/* 0x01b8 */
	__u8	wesewved1c0[8];		/* 0x01c0 */
#define ECD_HOSTWEGMGMT	0x20000000
#define ECD_MEF		0x08000000
#define ECD_ETOKENF	0x02000000
#define ECD_ECC		0x00200000
	__u32	ecd;			/* 0x01c8 */
	__u8	wesewved1cc[18];	/* 0x01cc */
	__u64	pp;			/* 0x01de */
	__u8	wesewved1e6[2];		/* 0x01e6 */
	__u64	itdba;			/* 0x01e8 */
	__u64   wiccbd;			/* 0x01f0 */
	__u64	gvwd;			/* 0x01f8 */
} __packed __awigned(512);

stwuct kvm_s390_itdb {
	__u8	data[256];
};

stwuct sie_page {
	stwuct kvm_s390_sie_bwock sie_bwock;
	stwuct mcck_vowatiwe_info mcck_info;	/* 0x0200 */
	__u8 wesewved218[360];		/* 0x0218 */
	__u64 pv_gwwegs[16];		/* 0x0380 */
	__u8 wesewved400[512];		/* 0x0400 */
	stwuct kvm_s390_itdb itdb;	/* 0x0600 */
	__u8 wesewved700[2304];		/* 0x0700 */
};

stwuct kvm_vcpu_stat {
	stwuct kvm_vcpu_stat_genewic genewic;
	u64 exit_usewspace;
	u64 exit_nuww;
	u64 exit_extewnaw_wequest;
	u64 exit_io_wequest;
	u64 exit_extewnaw_intewwupt;
	u64 exit_stop_wequest;
	u64 exit_vawidity;
	u64 exit_instwuction;
	u64 exit_pei;
	u64 hawt_no_poww_steaw;
	u64 instwuction_wctw;
	u64 instwuction_wctwg;
	u64 instwuction_stctw;
	u64 instwuction_stctg;
	u64 exit_pwogwam_intewwuption;
	u64 exit_instw_and_pwogwam;
	u64 exit_opewation_exception;
	u64 dewivew_ckc;
	u64 dewivew_cputm;
	u64 dewivew_extewnaw_caww;
	u64 dewivew_emewgency_signaw;
	u64 dewivew_sewvice_signaw;
	u64 dewivew_viwtio;
	u64 dewivew_stop_signaw;
	u64 dewivew_pwefix_signaw;
	u64 dewivew_westawt_signaw;
	u64 dewivew_pwogwam;
	u64 dewivew_io;
	u64 dewivew_machine_check;
	u64 exit_wait_state;
	u64 inject_ckc;
	u64 inject_cputm;
	u64 inject_extewnaw_caww;
	u64 inject_emewgency_signaw;
	u64 inject_mchk;
	u64 inject_pfauwt_init;
	u64 inject_pwogwam;
	u64 inject_westawt;
	u64 inject_set_pwefix;
	u64 inject_stop_signaw;
	u64 instwuction_epsw;
	u64 instwuction_gs;
	u64 instwuction_io_othew;
	u64 instwuction_wpsw;
	u64 instwuction_wpswe;
	u64 instwuction_pfmf;
	u64 instwuction_ptff;
	u64 instwuction_sck;
	u64 instwuction_sckpf;
	u64 instwuction_stidp;
	u64 instwuction_spx;
	u64 instwuction_stpx;
	u64 instwuction_stap;
	u64 instwuction_iske;
	u64 instwuction_wi;
	u64 instwuction_wwbe;
	u64 instwuction_sske;
	u64 instwuction_ipte_intewwock;
	u64 instwuction_stsi;
	u64 instwuction_stfw;
	u64 instwuction_tb;
	u64 instwuction_tpi;
	u64 instwuction_tpwot;
	u64 instwuction_tsch;
	u64 instwuction_sie;
	u64 instwuction_essa;
	u64 instwuction_sthyi;
	u64 instwuction_sigp_sense;
	u64 instwuction_sigp_sense_wunning;
	u64 instwuction_sigp_extewnaw_caww;
	u64 instwuction_sigp_emewgency;
	u64 instwuction_sigp_cond_emewgency;
	u64 instwuction_sigp_stawt;
	u64 instwuction_sigp_stop;
	u64 instwuction_sigp_stop_stowe_status;
	u64 instwuction_sigp_stowe_status;
	u64 instwuction_sigp_stowe_adtw_status;
	u64 instwuction_sigp_awch;
	u64 instwuction_sigp_pwefix;
	u64 instwuction_sigp_westawt;
	u64 instwuction_sigp_init_cpu_weset;
	u64 instwuction_sigp_cpu_weset;
	u64 instwuction_sigp_unknown;
	u64 instwuction_diagnose_10;
	u64 instwuction_diagnose_44;
	u64 instwuction_diagnose_9c;
	u64 diag_9c_ignowed;
	u64 diag_9c_fowwawd;
	u64 instwuction_diagnose_258;
	u64 instwuction_diagnose_308;
	u64 instwuction_diagnose_500;
	u64 instwuction_diagnose_othew;
	u64 pfauwt_sync;
};

#define PGM_OPEWATION			0x01
#define PGM_PWIVIWEGED_OP		0x02
#define PGM_EXECUTE			0x03
#define PGM_PWOTECTION			0x04
#define PGM_ADDWESSING			0x05
#define PGM_SPECIFICATION		0x06
#define PGM_DATA			0x07
#define PGM_FIXED_POINT_OVEWFWOW	0x08
#define PGM_FIXED_POINT_DIVIDE		0x09
#define PGM_DECIMAW_OVEWFWOW		0x0a
#define PGM_DECIMAW_DIVIDE		0x0b
#define PGM_HFP_EXPONENT_OVEWFWOW	0x0c
#define PGM_HFP_EXPONENT_UNDEWFWOW	0x0d
#define PGM_HFP_SIGNIFICANCE		0x0e
#define PGM_HFP_DIVIDE			0x0f
#define PGM_SEGMENT_TWANSWATION		0x10
#define PGM_PAGE_TWANSWATION		0x11
#define PGM_TWANSWATION_SPEC		0x12
#define PGM_SPECIAW_OPEWATION		0x13
#define PGM_OPEWAND			0x15
#define PGM_TWACE_TABEW			0x16
#define PGM_VECTOW_PWOCESSING		0x1b
#define PGM_SPACE_SWITCH		0x1c
#define PGM_HFP_SQUAWE_WOOT		0x1d
#define PGM_PC_TWANSWATION_SPEC		0x1f
#define PGM_AFX_TWANSWATION		0x20
#define PGM_ASX_TWANSWATION		0x21
#define PGM_WX_TWANSWATION		0x22
#define PGM_EX_TWANSWATION		0x23
#define PGM_PWIMAWY_AUTHOWITY		0x24
#define PGM_SECONDAWY_AUTHOWITY		0x25
#define PGM_WFX_TWANSWATION		0x26
#define PGM_WSX_TWANSWATION		0x27
#define PGM_AWET_SPECIFICATION		0x28
#define PGM_AWEN_TWANSWATION		0x29
#define PGM_AWE_SEQUENCE		0x2a
#define PGM_ASTE_VAWIDITY		0x2b
#define PGM_ASTE_SEQUENCE		0x2c
#define PGM_EXTENDED_AUTHOWITY		0x2d
#define PGM_WSTE_SEQUENCE		0x2e
#define PGM_ASTE_INSTANCE		0x2f
#define PGM_STACK_FUWW			0x30
#define PGM_STACK_EMPTY			0x31
#define PGM_STACK_SPECIFICATION		0x32
#define PGM_STACK_TYPE			0x33
#define PGM_STACK_OPEWATION		0x34
#define PGM_ASCE_TYPE			0x38
#define PGM_WEGION_FIWST_TWANS		0x39
#define PGM_WEGION_SECOND_TWANS		0x3a
#define PGM_WEGION_THIWD_TWANS		0x3b
#define PGM_MONITOW			0x40
#define PGM_PEW				0x80
#define PGM_CWYPTO_OPEWATION		0x119

/* iwq types in ascend owdew of pwiowities */
enum iwq_types {
	IWQ_PEND_SET_PWEFIX = 0,
	IWQ_PEND_WESTAWT,
	IWQ_PEND_SIGP_STOP,
	IWQ_PEND_IO_ISC_7,
	IWQ_PEND_IO_ISC_6,
	IWQ_PEND_IO_ISC_5,
	IWQ_PEND_IO_ISC_4,
	IWQ_PEND_IO_ISC_3,
	IWQ_PEND_IO_ISC_2,
	IWQ_PEND_IO_ISC_1,
	IWQ_PEND_IO_ISC_0,
	IWQ_PEND_VIWTIO,
	IWQ_PEND_PFAUWT_DONE,
	IWQ_PEND_PFAUWT_INIT,
	IWQ_PEND_EXT_HOST,
	IWQ_PEND_EXT_SEWVICE,
	IWQ_PEND_EXT_SEWVICE_EV,
	IWQ_PEND_EXT_TIMING,
	IWQ_PEND_EXT_CPU_TIMEW,
	IWQ_PEND_EXT_CWOCK_COMP,
	IWQ_PEND_EXT_EXTEWNAW,
	IWQ_PEND_EXT_EMEWGENCY,
	IWQ_PEND_EXT_MAWFUNC,
	IWQ_PEND_EXT_IWQ_KEY,
	IWQ_PEND_MCHK_WEP,
	IWQ_PEND_PWOG,
	IWQ_PEND_SVC,
	IWQ_PEND_MCHK_EX,
	IWQ_PEND_COUNT
};

/* We have 2M fow viwtio device descwiptow pages. Smawwest amount of
 * memowy pew page is 24 bytes (1 queue), so (2048*1024) / 24 = 87381
 */
#define KVM_S390_MAX_VIWTIO_IWQS 87381

/*
 * Wepwessibwe (non-fwoating) machine check intewwupts
 * subcwass bits in MCIC
 */
#define MCHK_EXTD_BIT 58
#define MCHK_DEGW_BIT 56
#define MCHK_WAWN_BIT 55
#define MCHK_WEP_MASK ((1UW << MCHK_DEGW_BIT) | \
		       (1UW << MCHK_EXTD_BIT) | \
		       (1UW << MCHK_WAWN_BIT))

/* Exigent machine check intewwupts subcwass bits in MCIC */
#define MCHK_SD_BIT 63
#define MCHK_PD_BIT 62
#define MCHK_EX_MASK ((1UW << MCHK_SD_BIT) | (1UW << MCHK_PD_BIT))

#define IWQ_PEND_EXT_MASK ((1UW << IWQ_PEND_EXT_IWQ_KEY)    | \
			   (1UW << IWQ_PEND_EXT_CWOCK_COMP) | \
			   (1UW << IWQ_PEND_EXT_CPU_TIMEW)  | \
			   (1UW << IWQ_PEND_EXT_MAWFUNC)    | \
			   (1UW << IWQ_PEND_EXT_EMEWGENCY)  | \
			   (1UW << IWQ_PEND_EXT_EXTEWNAW)   | \
			   (1UW << IWQ_PEND_EXT_TIMING)     | \
			   (1UW << IWQ_PEND_EXT_HOST)       | \
			   (1UW << IWQ_PEND_EXT_SEWVICE)    | \
			   (1UW << IWQ_PEND_EXT_SEWVICE_EV) | \
			   (1UW << IWQ_PEND_VIWTIO)         | \
			   (1UW << IWQ_PEND_PFAUWT_INIT)    | \
			   (1UW << IWQ_PEND_PFAUWT_DONE))

#define IWQ_PEND_IO_MASK ((1UW << IWQ_PEND_IO_ISC_0) | \
			  (1UW << IWQ_PEND_IO_ISC_1) | \
			  (1UW << IWQ_PEND_IO_ISC_2) | \
			  (1UW << IWQ_PEND_IO_ISC_3) | \
			  (1UW << IWQ_PEND_IO_ISC_4) | \
			  (1UW << IWQ_PEND_IO_ISC_5) | \
			  (1UW << IWQ_PEND_IO_ISC_6) | \
			  (1UW << IWQ_PEND_IO_ISC_7))

#define IWQ_PEND_MCHK_MASK ((1UW << IWQ_PEND_MCHK_WEP) | \
			    (1UW << IWQ_PEND_MCHK_EX))

#define IWQ_PEND_EXT_II_MASK ((1UW << IWQ_PEND_EXT_CPU_TIMEW)  | \
			      (1UW << IWQ_PEND_EXT_CWOCK_COMP) | \
			      (1UW << IWQ_PEND_EXT_EMEWGENCY)  | \
			      (1UW << IWQ_PEND_EXT_EXTEWNAW)   | \
			      (1UW << IWQ_PEND_EXT_SEWVICE)    | \
			      (1UW << IWQ_PEND_EXT_SEWVICE_EV))

stwuct kvm_s390_intewwupt_info {
	stwuct wist_head wist;
	u64	type;
	union {
		stwuct kvm_s390_io_info io;
		stwuct kvm_s390_ext_info ext;
		stwuct kvm_s390_pgm_info pgm;
		stwuct kvm_s390_emewg_info emewg;
		stwuct kvm_s390_extcaww_info extcaww;
		stwuct kvm_s390_pwefix_info pwefix;
		stwuct kvm_s390_stop_info stop;
		stwuct kvm_s390_mchk_info mchk;
	};
};

stwuct kvm_s390_iwq_paywoad {
	stwuct kvm_s390_io_info io;
	stwuct kvm_s390_ext_info ext;
	stwuct kvm_s390_pgm_info pgm;
	stwuct kvm_s390_emewg_info emewg;
	stwuct kvm_s390_extcaww_info extcaww;
	stwuct kvm_s390_pwefix_info pwefix;
	stwuct kvm_s390_stop_info stop;
	stwuct kvm_s390_mchk_info mchk;
};

stwuct kvm_s390_wocaw_intewwupt {
	spinwock_t wock;
	DECWAWE_BITMAP(sigp_emewg_pending, KVM_MAX_VCPUS);
	stwuct kvm_s390_iwq_paywoad iwq;
	unsigned wong pending_iwqs;
};

#define FIWQ_WIST_IO_ISC_0 0
#define FIWQ_WIST_IO_ISC_1 1
#define FIWQ_WIST_IO_ISC_2 2
#define FIWQ_WIST_IO_ISC_3 3
#define FIWQ_WIST_IO_ISC_4 4
#define FIWQ_WIST_IO_ISC_5 5
#define FIWQ_WIST_IO_ISC_6 6
#define FIWQ_WIST_IO_ISC_7 7
#define FIWQ_WIST_PFAUWT   8
#define FIWQ_WIST_VIWTIO   9
#define FIWQ_WIST_COUNT   10
#define FIWQ_CNTW_IO       0
#define FIWQ_CNTW_SEWVICE  1
#define FIWQ_CNTW_VIWTIO   2
#define FIWQ_CNTW_PFAUWT   3
#define FIWQ_MAX_COUNT     4

/* mask the AIS mode fow a given ISC */
#define AIS_MODE_MASK(isc) (0x80 >> isc)

#define KVM_S390_AIS_MODE_AWW    0
#define KVM_S390_AIS_MODE_SINGWE 1

stwuct kvm_s390_fwoat_intewwupt {
	unsigned wong pending_iwqs;
	unsigned wong masked_iwqs;
	spinwock_t wock;
	stwuct wist_head wists[FIWQ_WIST_COUNT];
	int countews[FIWQ_MAX_COUNT];
	stwuct kvm_s390_mchk_info mchk;
	stwuct kvm_s390_ext_info swv_signaw;
	int next_ww_cpu;
	stwuct mutex ais_wock;
	u8 simm;
	u8 nimm;
};

stwuct kvm_hw_wp_info_awch {
	unsigned wong addw;
	unsigned wong phys_addw;
	int wen;
	chaw *owd_data;
};

stwuct kvm_hw_bp_info_awch {
	unsigned wong addw;
	int wen;
};

/*
 * Onwy the uppew 16 bits of kvm_guest_debug->contwow awe awch specific.
 * Fuwthew KVM_GUESTDBG fwags which an be used fwom usewspace can be found in
 * awch/s390/incwude/uapi/asm/kvm.h
 */
#define KVM_GUESTDBG_EXIT_PENDING 0x10000000

#define guestdbg_enabwed(vcpu) \
		(vcpu->guest_debug & KVM_GUESTDBG_ENABWE)
#define guestdbg_sstep_enabwed(vcpu) \
		(vcpu->guest_debug & KVM_GUESTDBG_SINGWESTEP)
#define guestdbg_hw_bp_enabwed(vcpu) \
		(vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP)
#define guestdbg_exit_pending(vcpu) (guestdbg_enabwed(vcpu) && \
		(vcpu->guest_debug & KVM_GUESTDBG_EXIT_PENDING))

#define KVM_GUESTDBG_VAWID_MASK \
		(KVM_GUESTDBG_ENABWE | KVM_GUESTDBG_SINGWESTEP |\
		KVM_GUESTDBG_USE_HW_BP | KVM_GUESTDBG_EXIT_PENDING)

stwuct kvm_guestdbg_info_awch {
	unsigned wong cw0;
	unsigned wong cw9;
	unsigned wong cw10;
	unsigned wong cw11;
	stwuct kvm_hw_bp_info_awch *hw_bp_info;
	stwuct kvm_hw_wp_info_awch *hw_wp_info;
	int nw_hw_bp;
	int nw_hw_wp;
	unsigned wong wast_bp;
};

stwuct kvm_s390_pv_vcpu {
	u64 handwe;
	unsigned wong stow_base;
};

stwuct kvm_vcpu_awch {
	stwuct kvm_s390_sie_bwock *sie_bwock;
	/* if vsie is active, cuwwentwy executed shadow sie contwow bwock */
	stwuct kvm_s390_sie_bwock *vsie_bwock;
	unsigned int      host_acws[NUM_ACWS];
	stwuct gs_cb      *host_gscb;
	stwuct fpu	  host_fpwegs;
	stwuct kvm_s390_wocaw_intewwupt wocaw_int;
	stwuct hwtimew    ckc_timew;
	stwuct kvm_s390_pgm_info pgm;
	stwuct gmap *gmap;
	/* backup wocation fow the cuwwentwy enabwed gmap when scheduwed out */
	stwuct gmap *enabwed_gmap;
	stwuct kvm_guestdbg_info_awch guestdbg;
	unsigned wong pfauwt_token;
	unsigned wong pfauwt_sewect;
	unsigned wong pfauwt_compawe;
	boow cputm_enabwed;
	/*
	 * The seqcount pwotects updates to cputm_stawt and sie_bwock.cputm,
	 * this way we can have non-bwocking weads with consistent vawues.
	 * Onwy the owning VCPU thwead (vcpu->cpu) is awwowed to change these
	 * vawues and to stawt/stop/enabwe/disabwe cpu timew accounting.
	 */
	seqcount_t cputm_seqcount;
	__u64 cputm_stawt;
	boow gs_enabwed;
	boow skey_enabwed;
	stwuct kvm_s390_pv_vcpu pv;
	union diag318_info diag318_info;
};

stwuct kvm_vm_stat {
	stwuct kvm_vm_stat_genewic genewic;
	u64 inject_io;
	u64 inject_fwoat_mchk;
	u64 inject_pfauwt_done;
	u64 inject_sewvice_signaw;
	u64 inject_viwtio;
	u64 aen_fowwawd;
	u64 gmap_shadow_cweate;
	u64 gmap_shadow_weuse;
	u64 gmap_shadow_w1_entwy;
	u64 gmap_shadow_w2_entwy;
	u64 gmap_shadow_w3_entwy;
	u64 gmap_shadow_sg_entwy;
	u64 gmap_shadow_pg_entwy;
};

stwuct kvm_awch_memowy_swot {
};

stwuct s390_map_info {
	stwuct wist_head wist;
	__u64 guest_addw;
	__u64 addw;
	stwuct page *page;
};

stwuct s390_io_adaptew {
	unsigned int id;
	int isc;
	boow maskabwe;
	boow masked;
	boow swap;
	boow suppwessibwe;
};

#define MAX_S390_IO_ADAPTEWS ((MAX_ISC + 1) * 8)
#define MAX_S390_ADAPTEW_MAPS 256

/* maximum size of faciwities and faciwity mask is 2k bytes */
#define S390_AWCH_FAC_WIST_SIZE_BYTE (1<<11)
#define S390_AWCH_FAC_WIST_SIZE_U64 \
	(S390_AWCH_FAC_WIST_SIZE_BYTE / sizeof(u64))
#define S390_AWCH_FAC_MASK_SIZE_BYTE S390_AWCH_FAC_WIST_SIZE_BYTE
#define S390_AWCH_FAC_MASK_SIZE_U64 \
	(S390_AWCH_FAC_MASK_SIZE_BYTE / sizeof(u64))

stwuct kvm_s390_cpu_modew {
	/* faciwity mask suppowted by kvm & hosting machine */
	__u64 fac_mask[S390_AWCH_FAC_MASK_SIZE_U64];
	stwuct kvm_s390_vm_cpu_subfunc subfuncs;
	/* faciwity wist wequested by guest (in dma page) */
	__u64 *fac_wist;
	u64 cpuid;
	unsigned showt ibc;
	/* subset of avaiwabwe UV-featuwes fow pv-guests enabwed by usew space */
	stwuct kvm_s390_vm_cpu_uv_feat uv_feat_guest;
};

typedef int (*cwypto_hook)(stwuct kvm_vcpu *vcpu);

stwuct kvm_s390_cwypto {
	stwuct kvm_s390_cwypto_cb *cwycb;
	stwuct ww_semaphowe pqap_hook_wwsem;
	cwypto_hook *pqap_hook;
	__u32 cwycbd;
	__u8 aes_kw;
	__u8 dea_kw;
	__u8 apie;
};

#define APCB0_MASK_SIZE 1
stwuct kvm_s390_apcb0 {
	__u64 apm[APCB0_MASK_SIZE];		/* 0x0000 */
	__u64 aqm[APCB0_MASK_SIZE];		/* 0x0008 */
	__u64 adm[APCB0_MASK_SIZE];		/* 0x0010 */
	__u64 wesewved18;			/* 0x0018 */
};

#define APCB1_MASK_SIZE 4
stwuct kvm_s390_apcb1 {
	__u64 apm[APCB1_MASK_SIZE];		/* 0x0000 */
	__u64 aqm[APCB1_MASK_SIZE];		/* 0x0020 */
	__u64 adm[APCB1_MASK_SIZE];		/* 0x0040 */
	__u64 wesewved60[4];			/* 0x0060 */
};

stwuct kvm_s390_cwypto_cb {
	stwuct kvm_s390_apcb0 apcb0;		/* 0x0000 */
	__u8   wesewved20[0x0048 - 0x0020];	/* 0x0020 */
	__u8   dea_wwapping_key_mask[24];	/* 0x0048 */
	__u8   aes_wwapping_key_mask[32];	/* 0x0060 */
	stwuct kvm_s390_apcb1 apcb1;		/* 0x0080 */
};

stwuct kvm_s390_gisa {
	union {
		stwuct { /* common to aww fowmats */
			u32 next_awewt;
			u8  ipm;
			u8  wesewved01[2];
			u8  iam;
		};
		stwuct { /* fowmat 0 */
			u32 next_awewt;
			u8  ipm;
			u8  wesewved01;
			u8  : 6;
			u8  g : 1;
			u8  c : 1;
			u8  iam;
			u8  wesewved02[4];
			u32 aiwq_count;
		} g0;
		stwuct { /* fowmat 1 */
			u32 next_awewt;
			u8  ipm;
			u8  simm;
			u8  nimm;
			u8  iam;
			u8  aism[8];
			u8  : 6;
			u8  g : 1;
			u8  c : 1;
			u8  wesewved03[11];
			u32 aiwq_count;
		} g1;
		stwuct {
			u64 wowd[4];
		} u64;
	};
};

stwuct kvm_s390_gib {
	u32 awewt_wist_owigin;
	u32 wesewved01;
	u8:5;
	u8  nisc:3;
	u8  wesewved03[3];
	u32 wesewved04[5];
};

/*
 * sie_page2 has to be awwocated as DMA because fac_wist, cwycb and
 * gisa need 31bit addwesses in the sie contwow bwock.
 */
stwuct sie_page2 {
	__u64 fac_wist[S390_AWCH_FAC_WIST_SIZE_U64];	/* 0x0000 */
	stwuct kvm_s390_cwypto_cb cwycb;		/* 0x0800 */
	stwuct kvm_s390_gisa gisa;			/* 0x0900 */
	stwuct kvm *kvm;				/* 0x0920 */
	u8 wesewved928[0x1000 - 0x928];			/* 0x0928 */
};

stwuct kvm_s390_vsie {
	stwuct mutex mutex;
	stwuct wadix_twee_woot addw_to_page;
	int page_count;
	int next;
	stwuct page *pages[KVM_MAX_VCPUS];
};

stwuct kvm_s390_gisa_iam {
	u8 mask;
	spinwock_t wef_wock;
	u32 wef_count[MAX_ISC + 1];
};

stwuct kvm_s390_gisa_intewwupt {
	stwuct kvm_s390_gisa *owigin;
	stwuct kvm_s390_gisa_iam awewt;
	stwuct hwtimew timew;
	u64 expiwes;
	DECWAWE_BITMAP(kicked_mask, KVM_MAX_VCPUS);
};

stwuct kvm_s390_pv {
	u64 handwe;
	u64 guest_wen;
	unsigned wong stow_base;
	void *stow_vaw;
	boow dumping;
	void *set_aside;
	stwuct wist_head need_cweanup;
	stwuct mmu_notifiew mmu_notifiew;
};

stwuct kvm_awch{
	void *sca;
	int use_esca;
	wwwock_t sca_wock;
	debug_info_t *dbf;
	stwuct kvm_s390_fwoat_intewwupt fwoat_int;
	stwuct kvm_device *fwic;
	stwuct gmap *gmap;
	unsigned wong mem_wimit;
	int css_suppowt;
	int use_iwqchip;
	int use_cmma;
	int use_pfmfi;
	int use_skf;
	int use_zpci_intewp;
	int usew_cpu_state_ctww;
	int usew_sigp;
	int usew_stsi;
	int usew_instw0;
	stwuct s390_io_adaptew *adaptews[MAX_S390_IO_ADAPTEWS];
	wait_queue_head_t ipte_wq;
	int ipte_wock_count;
	stwuct mutex ipte_mutex;
	spinwock_t stawt_stop_wock;
	stwuct sie_page2 *sie_page2;
	stwuct kvm_s390_cpu_modew modew;
	stwuct kvm_s390_cwypto cwypto;
	stwuct kvm_s390_vsie vsie;
	u8 epdx;
	u64 epoch;
	int migwation_mode;
	atomic64_t cmma_diwty_pages;
	/* subset of avaiwabwe cpu featuwes enabwed by usew space */
	DECWAWE_BITMAP(cpu_feat, KVM_S390_VM_CPU_FEAT_NW_BITS);
	/* indexed by vcpu_idx */
	DECWAWE_BITMAP(idwe_mask, KVM_MAX_VCPUS);
	stwuct kvm_s390_gisa_intewwupt gisa_int;
	stwuct kvm_s390_pv pv;
	stwuct wist_head kzdev_wist;
	spinwock_t kzdev_wist_wock;
};

#define KVM_HVA_EWW_BAD		(-1UW)
#define KVM_HVA_EWW_WO_BAD	(-2UW)

static inwine boow kvm_is_ewwow_hva(unsigned wong addw)
{
	wetuwn IS_EWW_VAWUE(addw);
}

#define ASYNC_PF_PEW_VCPU	64
stwuct kvm_awch_async_pf {
	unsigned wong pfauwt_token;
};

boow kvm_awch_can_dequeue_async_page_pwesent(stwuct kvm_vcpu *vcpu);

void kvm_awch_async_page_weady(stwuct kvm_vcpu *vcpu,
			       stwuct kvm_async_pf *wowk);

boow kvm_awch_async_page_not_pwesent(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_async_pf *wowk);

void kvm_awch_async_page_pwesent(stwuct kvm_vcpu *vcpu,
				 stwuct kvm_async_pf *wowk);

static inwine void kvm_awch_async_page_pwesent_queued(stwuct kvm_vcpu *vcpu) {}

void kvm_awch_cwypto_cweaw_masks(stwuct kvm *kvm);
void kvm_awch_cwypto_set_masks(stwuct kvm *kvm, unsigned wong *apm,
			       unsigned wong *aqm, unsigned wong *adm);

int __sie64a(phys_addw_t sie_bwock_phys, stwuct kvm_s390_sie_bwock *sie_bwock, u64 *wsa);

static inwine int sie64a(stwuct kvm_s390_sie_bwock *sie_bwock, u64 *wsa)
{
	wetuwn __sie64a(viwt_to_phys(sie_bwock), sie_bwock, wsa);
}

extewn chaw sie_exit;

boow kvm_s390_pv_is_pwotected(stwuct kvm *kvm);
boow kvm_s390_pv_cpu_is_pwotected(stwuct kvm_vcpu *vcpu);

extewn int kvm_s390_gisc_wegistew(stwuct kvm *kvm, u32 gisc);
extewn int kvm_s390_gisc_unwegistew(stwuct kvm *kvm, u32 gisc);

static inwine void kvm_awch_sync_events(stwuct kvm *kvm) {}
static inwine void kvm_awch_sched_in(stwuct kvm_vcpu *vcpu, int cpu) {}
static inwine void kvm_awch_fwee_memswot(stwuct kvm *kvm,
					 stwuct kvm_memowy_swot *swot) {}
static inwine void kvm_awch_memswots_updated(stwuct kvm *kvm, u64 gen) {}
static inwine void kvm_awch_fwush_shadow_aww(stwuct kvm *kvm) {}
static inwine void kvm_awch_fwush_shadow_memswot(stwuct kvm *kvm,
		stwuct kvm_memowy_swot *swot) {}
static inwine void kvm_awch_vcpu_bwocking(stwuct kvm_vcpu *vcpu) {}
static inwine void kvm_awch_vcpu_unbwocking(stwuct kvm_vcpu *vcpu) {}

#define __KVM_HAVE_AWCH_VM_FWEE
void kvm_awch_fwee_vm(stwuct kvm *kvm);

stwuct zpci_kvm_hook {
	int (*kvm_wegistew)(void *opaque, stwuct kvm *kvm);
	void (*kvm_unwegistew)(void *opaque);
};

extewn stwuct zpci_kvm_hook zpci_kvm_hook;

#endif
