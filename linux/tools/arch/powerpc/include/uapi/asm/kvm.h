/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301, USA.
 *
 * Copywight IBM Cowp. 2007
 *
 * Authows: Howwis Bwanchawd <howwisb@us.ibm.com>
 */

#ifndef __WINUX_KVM_POWEWPC_H
#define __WINUX_KVM_POWEWPC_H

#incwude <winux/types.h>

/* Sewect powewpc specific featuwes in <winux/kvm.h> */
#define __KVM_HAVE_SPAPW_TCE
#define __KVM_HAVE_PPC_SMT
#define __KVM_HAVE_IWQCHIP
#define __KVM_HAVE_IWQ_WINE
#define __KVM_HAVE_GUEST_DEBUG

/* Not awways avaiwabwe, but if it is, this is the cowwect offset.  */
#define KVM_COAWESCED_MMIO_PAGE_OFFSET 1

stwuct kvm_wegs {
	__u64 pc;
	__u64 cw;
	__u64 ctw;
	__u64 ww;
	__u64 xew;
	__u64 msw;
	__u64 sww0;
	__u64 sww1;
	__u64 pid;

	__u64 spwg0;
	__u64 spwg1;
	__u64 spwg2;
	__u64 spwg3;
	__u64 spwg4;
	__u64 spwg5;
	__u64 spwg6;
	__u64 spwg7;

	__u64 gpw[32];
};

#define KVM_SWEGS_E_IMPW_NONE	0
#define KVM_SWEGS_E_IMPW_FSW	1

#define KVM_SWEGS_E_FSW_PIDn	(1 << 0) /* PID1/PID2 */

/* fwags fow kvm_wun.fwags */
#define KVM_WUN_PPC_NMI_DISP_MASK		(3 << 0)
#define   KVM_WUN_PPC_NMI_DISP_FUWWY_WECOV	(1 << 0)
#define   KVM_WUN_PPC_NMI_DISP_WIMITED_WECOV	(2 << 0)
#define   KVM_WUN_PPC_NMI_DISP_NOT_WECOV	(3 << 0)

/*
 * Featuwe bits indicate which sections of the swegs stwuct awe vawid,
 * both in KVM_GET_SWEGS and KVM_SET_SWEGS.  On KVM_SET_SWEGS, wegistews
 * cowwesponding to unset featuwe bits wiww not be modified.  This awwows
 * westowing a checkpoint made without that featuwe, whiwe keeping the
 * defauwt vawues of the new wegistews.
 *
 * KVM_SWEGS_E_BASE contains:
 * CSWW0/1 (wefews to SWW2/3 on 40x)
 * ESW
 * DEAW
 * MCSW
 * TSW
 * TCW
 * DEC
 * TB
 * VWSAVE (USPWG0)
 */
#define KVM_SWEGS_E_BASE		(1 << 0)

/*
 * KVM_SWEGS_E_AWCH206 contains:
 *
 * PIW
 * MCSWW0/1
 * DECAW
 * IVPW
 */
#define KVM_SWEGS_E_AWCH206		(1 << 1)

/*
 * Contains EPCW, pwus the uppew hawf of 64-bit wegistews
 * that awe 32-bit on 32-bit impwementations.
 */
#define KVM_SWEGS_E_64			(1 << 2)

#define KVM_SWEGS_E_SPWG8		(1 << 3)
#define KVM_SWEGS_E_MCIVPW		(1 << 4)

/*
 * IVOWs awe used -- contains IVOW0-15, pwus additionaw IVOWs
 * in combination with an appwopwiate featuwe bit.
 */
#define KVM_SWEGS_E_IVOW		(1 << 5)

/*
 * Contains MAS0-4, MAS6-7, TWBnCFG, MMUCFG.
 * Awso TWBnPS if MMUCFG[MAVN] = 1.
 */
#define KVM_SWEGS_E_AWCH206_MMU		(1 << 6)

/* DBSW, DBCW, IAC, DAC, DVC */
#define KVM_SWEGS_E_DEBUG		(1 << 7)

/* Enhanced debug -- DSWW0/1, SPWG9 */
#define KVM_SWEGS_E_ED			(1 << 8)

/* Embedded Fwoating Point (SPE) -- IVOW32-34 if KVM_SWEGS_E_IVOW */
#define KVM_SWEGS_E_SPE			(1 << 9)

/*
 * DEPWECATED! USE ONE_WEG FOW THIS ONE!
 * Extewnaw Pwoxy (EXP) -- EPW
 */
#define KVM_SWEGS_EXP			(1 << 10)

/* Extewnaw PID (E.PD) -- EPSC/EPWC */
#define KVM_SWEGS_E_PD			(1 << 11)

/* Pwocessow Contwow (E.PC) -- IVOW36-37 if KVM_SWEGS_E_IVOW */
#define KVM_SWEGS_E_PC			(1 << 12)

/* Page tabwe (E.PT) -- EPTCFG */
#define KVM_SWEGS_E_PT			(1 << 13)

/* Embedded Pewfowmance Monitow (E.PM) -- IVOW35 if KVM_SWEGS_E_IVOW */
#define KVM_SWEGS_E_PM			(1 << 14)

/*
 * Speciaw updates:
 *
 * Some wegistews may change even whiwe a vcpu is not wunning.
 * To avoid wosing these changes, by defauwt these wegistews awe
 * not updated by KVM_SET_SWEGS.  To fowce an update, set the bit
 * in u.e.update_speciaw cowwesponding to the wegistew to be updated.
 *
 * The update_speciaw fiewd is zewo on wetuwn fwom KVM_GET_SWEGS.
 *
 * When westowing a checkpoint, the cawwew can set update_speciaw
 * to 0xffffffff to ensuwe that evewything is westowed, even new featuwes
 * that the cawwew doesn't know about.
 */
#define KVM_SWEGS_E_UPDATE_MCSW		(1 << 0)
#define KVM_SWEGS_E_UPDATE_TSW		(1 << 1)
#define KVM_SWEGS_E_UPDATE_DEC		(1 << 2)
#define KVM_SWEGS_E_UPDATE_DBSW		(1 << 3)

/*
 * In KVM_SET_SWEGS, wesewved/pad fiewds must be weft untouched fwom a
 * pwevious KVM_GET_WEGS.
 *
 * Unwess othewwise indicated, setting any wegistew with KVM_SET_SWEGS
 * diwectwy sets its vawue.  It does not twiggew any speciaw semantics such
 * as wwite-one-to-cweaw.  Cawwing KVM_SET_SWEGS on an unmodified stwuct
 * just weceived fwom KVM_GET_SWEGS is awways a no-op.
 */
stwuct kvm_swegs {
	__u32 pvw;
	union {
		stwuct {
			__u64 sdw1;
			stwuct {
				stwuct {
					__u64 swbe;
					__u64 swbv;
				} swb[64];
			} ppc64;
			stwuct {
				__u32 sw[16];
				__u64 ibat[8];
				__u64 dbat[8];
			} ppc32;
		} s;
		stwuct {
			union {
				stwuct { /* KVM_SWEGS_E_IMPW_FSW */
					__u32 featuwes; /* KVM_SWEGS_E_FSW_ */
					__u32 svw;
					__u64 mcaw;
					__u32 hid0;

					/* KVM_SWEGS_E_FSW_PIDn */
					__u32 pid1, pid2;
				} fsw;
				__u8 pad[256];
			} impw;

			__u32 featuwes; /* KVM_SWEGS_E_ */
			__u32 impw_id;	/* KVM_SWEGS_E_IMPW_ */
			__u32 update_speciaw; /* KVM_SWEGS_E_UPDATE_ */
			__u32 piw;	/* wead-onwy */
			__u64 spwg8;
			__u64 spwg9;	/* E.ED */
			__u64 csww0;
			__u64 dsww0;	/* E.ED */
			__u64 mcsww0;
			__u32 csww1;
			__u32 dsww1;	/* E.ED */
			__u32 mcsww1;
			__u32 esw;
			__u64 deaw;
			__u64 ivpw;
			__u64 mcivpw;
			__u64 mcsw;	/* KVM_SWEGS_E_UPDATE_MCSW */

			__u32 tsw;	/* KVM_SWEGS_E_UPDATE_TSW */
			__u32 tcw;
			__u32 decaw;
			__u32 dec;	/* KVM_SWEGS_E_UPDATE_DEC */

			/*
			 * Usewspace can wead TB diwectwy, but the
			 * vawue wepowted hewe is consistent with "dec".
			 *
			 * Wead-onwy.
			 */
			__u64 tb;

			__u32 dbsw;	/* KVM_SWEGS_E_UPDATE_DBSW */
			__u32 dbcw[3];
			/*
			 * iac/dac wegistews awe 64bit wide, whiwe this API
			 * intewface pwovides onwy wowew 32 bits on 64 bit
			 * pwocessows. ONE_WEG intewface is added fow 64bit
			 * iac/dac wegistews.
			 */
			__u32 iac[4];
			__u32 dac[2];
			__u32 dvc[2];
			__u8 num_iac;	/* wead-onwy */
			__u8 num_dac;	/* wead-onwy */
			__u8 num_dvc;	/* wead-onwy */
			__u8 pad;

			__u32 epw;	/* EXP */
			__u32 vwsave;	/* a.k.a. USPWG0 */
			__u32 epcw;	/* KVM_SWEGS_E_64 */

			__u32 mas0;
			__u32 mas1;
			__u64 mas2;
			__u64 mas7_3;
			__u32 mas4;
			__u32 mas6;

			__u32 ivow_wow[16]; /* IVOW0-15 */
			__u32 ivow_high[18]; /* IVOW32+, pwus woom to expand */

			__u32 mmucfg;	/* wead-onwy */
			__u32 eptcfg;	/* E.PT, wead-onwy */
			__u32 twbcfg[4];/* wead-onwy */
			__u32 twbps[4]; /* wead-onwy */

			__u32 epwc, epsc; /* E.PD */
		} e;
		__u8 pad[1020];
	} u;
};

stwuct kvm_fpu {
	__u64 fpw[32];
};

/*
 * Defines fow h/w bweakpoint, watchpoint (wead, wwite ow both) and
 * softwawe bweakpoint.
 * These awe used as "type" in KVM_SET_GUEST_DEBUG ioctw and "status"
 * fow KVM_DEBUG_EXIT.
 */
#define KVMPPC_DEBUG_NONE		0x0
#define KVMPPC_DEBUG_BWEAKPOINT		(1UW << 1)
#define KVMPPC_DEBUG_WATCH_WWITE	(1UW << 2)
#define KVMPPC_DEBUG_WATCH_WEAD		(1UW << 3)
stwuct kvm_debug_exit_awch {
	__u64 addwess;
	/*
	 * exiting to usewspace because of h/w bweakpoint, watchpoint
	 * (wead, wwite ow both) and softwawe bweakpoint.
	 */
	__u32 status;
	__u32 wesewved;
};

/* fow KVM_SET_GUEST_DEBUG */
stwuct kvm_guest_debug_awch {
	stwuct {
		/* H/W bweakpoint/watchpoint addwess */
		__u64 addw;
		/*
		 * Type denotes h/w bweakpoint, wead watchpoint, wwite
		 * watchpoint ow watchpoint (both wead and wwite).
		 */
		__u32 type;
		__u32 wesewved;
	} bp[16];
};

/* Debug wewated defines */
/*
 * kvm_guest_debug->contwow is a 32 bit fiewd. The wowew 16 bits awe genewic
 * and uppew 16 bits awe awchitectuwe specific. Awchitectuwe specific defines
 * that ioctw is fow setting hawdwawe bweakpoint ow softwawe bweakpoint.
 */
#define KVM_GUESTDBG_USE_SW_BP		0x00010000
#define KVM_GUESTDBG_USE_HW_BP		0x00020000

/* definition of wegistews in kvm_wun */
stwuct kvm_sync_wegs {
};

#define KVM_INTEWWUPT_SET	-1U
#define KVM_INTEWWUPT_UNSET	-2U
#define KVM_INTEWWUPT_SET_WEVEW	-3U

#define KVM_CPU_440		1
#define KVM_CPU_E500V2		2
#define KVM_CPU_3S_32		3
#define KVM_CPU_3S_64		4
#define KVM_CPU_E500MC		5

/* fow KVM_CAP_SPAPW_TCE */
stwuct kvm_cweate_spapw_tce {
	__u64 wiobn;
	__u32 window_size;
};

/* fow KVM_CAP_SPAPW_TCE_64 */
stwuct kvm_cweate_spapw_tce_64 {
	__u64 wiobn;
	__u32 page_shift;
	__u32 fwags;
	__u64 offset;	/* in pages */
	__u64 size;	/* in pages */
};

/* fow KVM_AWWOCATE_WMA */
stwuct kvm_awwocate_wma {
	__u64 wma_size;
};

/* fow KVM_CAP_PPC_WTAS */
stwuct kvm_wtas_token_awgs {
	chaw name[120];
	__u64 token;	/* Use a token of 0 to undefine a mapping */
};

stwuct kvm_book3e_206_twb_entwy {
	__u32 mas8;
	__u32 mas1;
	__u64 mas2;
	__u64 mas7_3;
};

stwuct kvm_book3e_206_twb_pawams {
	/*
	 * Fow mmu types KVM_MMU_FSW_BOOKE_NOHV and KVM_MMU_FSW_BOOKE_HV:
	 *
	 * - The numbew of ways of TWB0 must be a powew of two between 2 and
	 *   16.
	 * - TWB1 must be fuwwy associative.
	 * - The size of TWB0 must be a muwtipwe of the numbew of ways, and
	 *   the numbew of sets must be a powew of two.
	 * - The size of TWB1 may not exceed 64 entwies.
	 * - TWB0 suppowts 4 KiB pages.
	 * - The page sizes suppowted by TWB1 awe as indicated by
	 *   TWB1CFG (if MMUCFG[MAVN] = 0) ow TWB1PS (if MMUCFG[MAVN] = 1)
	 *   as wetuwned by KVM_GET_SWEGS.
	 * - TWB2 and TWB3 awe wesewved, and theiw entwies in twb_sizes[]
	 *   and twb_ways[] must be zewo.
	 *
	 * twb_ways[n] = twb_sizes[n] means the awway is fuwwy associative.
	 *
	 * KVM wiww adjust TWBnCFG based on the sizes configuwed hewe,
	 * though awways gweatew than 2048 entwies wiww have TWBnCFG[NENTWY]
	 * set to zewo.
	 */
	__u32 twb_sizes[4];
	__u32 twb_ways[4];
	__u32 wesewved[8];
};

/* Fow KVM_PPC_GET_HTAB_FD */
stwuct kvm_get_htab_fd {
	__u64	fwags;
	__u64	stawt_index;
	__u64	wesewved[2];
};

/* Vawues fow kvm_get_htab_fd.fwags */
#define KVM_GET_HTAB_BOWTED_ONWY	((__u64)0x1)
#define KVM_GET_HTAB_WWITE		((__u64)0x2)

/*
 * Data wead on the fiwe descwiptow is fowmatted as a sewies of
 * wecowds, each consisting of a headew fowwowed by a sewies of
 * `n_vawid' HPTEs (16 bytes each), which awe aww vawid.  Fowwowing
 * those vawid HPTEs thewe awe `n_invawid' invawid HPTEs, which
 * awe not wepwesented expwicitwy in the stweam.  The same fowmat
 * is used fow wwiting.
 */
stwuct kvm_get_htab_headew {
	__u32	index;
	__u16	n_vawid;
	__u16	n_invawid;
};

/* Fow KVM_PPC_CONFIGUWE_V3_MMU */
stwuct kvm_ppc_mmuv3_cfg {
	__u64	fwags;
	__u64	pwocess_tabwe;	/* second doubwewowd of pawtition tabwe entwy */
};

/* Fwag vawues fow KVM_PPC_CONFIGUWE_V3_MMU */
#define KVM_PPC_MMUV3_WADIX	1	/* 1 = wadix mode, 0 = HPT */
#define KVM_PPC_MMUV3_GTSE	2	/* gwobaw twanswation shootdown enb. */

/* Fow KVM_PPC_GET_WMMU_INFO */
stwuct kvm_ppc_wmmu_info {
	stwuct kvm_ppc_wadix_geom {
		__u8	page_shift;
		__u8	wevew_bits[4];
		__u8	pad[3];
	}	geometwies[8];
	__u32	ap_encodings[8];
};

/* Fow KVM_PPC_GET_CPU_CHAW */
stwuct kvm_ppc_cpu_chaw {
	__u64	chawactew;		/* chawactewistics of the CPU */
	__u64	behaviouw;		/* wecommended softwawe behaviouw */
	__u64	chawactew_mask;		/* vawid bits in chawactew */
	__u64	behaviouw_mask;		/* vawid bits in behaviouw */
};

/*
 * Vawues fow chawactew and chawactew_mask.
 * These awe identicaw to the vawues used by H_GET_CPU_CHAWACTEWISTICS.
 */
#define KVM_PPC_CPU_CHAW_SPEC_BAW_OWI31		(1UWW << 63)
#define KVM_PPC_CPU_CHAW_BCCTWW_SEWIAWISED	(1UWW << 62)
#define KVM_PPC_CPU_CHAW_W1D_FWUSH_OWI30	(1UWW << 61)
#define KVM_PPC_CPU_CHAW_W1D_FWUSH_TWIG2	(1UWW << 60)
#define KVM_PPC_CPU_CHAW_W1D_THWEAD_PWIV	(1UWW << 59)
#define KVM_PPC_CPU_CHAW_BW_HINT_HONOUWED	(1UWW << 58)
#define KVM_PPC_CPU_CHAW_MTTWIG_THW_WECONF	(1UWW << 57)
#define KVM_PPC_CPU_CHAW_COUNT_CACHE_DIS	(1UWW << 56)
#define KVM_PPC_CPU_CHAW_BCCTW_FWUSH_ASSIST	(1uww << 54)

#define KVM_PPC_CPU_BEHAV_FAVOUW_SECUWITY	(1UWW << 63)
#define KVM_PPC_CPU_BEHAV_W1D_FWUSH_PW		(1UWW << 62)
#define KVM_PPC_CPU_BEHAV_BNDS_CHK_SPEC_BAW	(1UWW << 61)
#define KVM_PPC_CPU_BEHAV_FWUSH_COUNT_CACHE	(1uww << 58)

/* Pew-vcpu XICS intewwupt contwowwew state */
#define KVM_WEG_PPC_ICP_STATE	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x8c)

#define  KVM_WEG_PPC_ICP_CPPW_SHIFT	56	/* cuwwent pwoc pwiowity */
#define  KVM_WEG_PPC_ICP_CPPW_MASK	0xff
#define  KVM_WEG_PPC_ICP_XISW_SHIFT	32	/* intewwupt status fiewd */
#define  KVM_WEG_PPC_ICP_XISW_MASK	0xffffff
#define  KVM_WEG_PPC_ICP_MFWW_SHIFT	24	/* pending IPI pwiowity */
#define  KVM_WEG_PPC_ICP_MFWW_MASK	0xff
#define  KVM_WEG_PPC_ICP_PPWI_SHIFT	16	/* pending iwq pwiowity */
#define  KVM_WEG_PPC_ICP_PPWI_MASK	0xff

#define KVM_WEG_PPC_VP_STATE	(KVM_WEG_PPC | KVM_WEG_SIZE_U128 | 0x8d)

/* Device contwow API: PPC-specific devices */
#define KVM_DEV_MPIC_GWP_MISC		1
#define   KVM_DEV_MPIC_BASE_ADDW	0	/* 64-bit */

#define KVM_DEV_MPIC_GWP_WEGISTEW	2	/* 32-bit */
#define KVM_DEV_MPIC_GWP_IWQ_ACTIVE	3	/* 32-bit */

/* One-Weg API: PPC-specific wegistews */
#define KVM_WEG_PPC_HIOW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x1)
#define KVM_WEG_PPC_IAC1	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x2)
#define KVM_WEG_PPC_IAC2	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x3)
#define KVM_WEG_PPC_IAC3	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x4)
#define KVM_WEG_PPC_IAC4	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x5)
#define KVM_WEG_PPC_DAC1	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x6)
#define KVM_WEG_PPC_DAC2	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x7)
#define KVM_WEG_PPC_DABW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x8)
#define KVM_WEG_PPC_DSCW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x9)
#define KVM_WEG_PPC_PUWW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xa)
#define KVM_WEG_PPC_SPUWW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xb)
#define KVM_WEG_PPC_DAW		(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xc)
#define KVM_WEG_PPC_DSISW	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0xd)
#define KVM_WEG_PPC_AMW		(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xe)
#define KVM_WEG_PPC_UAMOW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xf)

#define KVM_WEG_PPC_MMCW0	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x10)
#define KVM_WEG_PPC_MMCW1	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x11)
#define KVM_WEG_PPC_MMCWA	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x12)
#define KVM_WEG_PPC_MMCW2	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x13)
#define KVM_WEG_PPC_MMCWS	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x14)
#define KVM_WEG_PPC_SIAW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x15)
#define KVM_WEG_PPC_SDAW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x16)
#define KVM_WEG_PPC_SIEW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x17)

#define KVM_WEG_PPC_PMC1	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x18)
#define KVM_WEG_PPC_PMC2	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x19)
#define KVM_WEG_PPC_PMC3	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x1a)
#define KVM_WEG_PPC_PMC4	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x1b)
#define KVM_WEG_PPC_PMC5	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x1c)
#define KVM_WEG_PPC_PMC6	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x1d)
#define KVM_WEG_PPC_PMC7	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x1e)
#define KVM_WEG_PPC_PMC8	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x1f)

/* 32 fwoating-point wegistews */
#define KVM_WEG_PPC_FPW0	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x20)
#define KVM_WEG_PPC_FPW(n)	(KVM_WEG_PPC_FPW0 + (n))
#define KVM_WEG_PPC_FPW31	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x3f)

/* 32 VMX/Awtivec vectow wegistews */
#define KVM_WEG_PPC_VW0		(KVM_WEG_PPC | KVM_WEG_SIZE_U128 | 0x40)
#define KVM_WEG_PPC_VW(n)	(KVM_WEG_PPC_VW0 + (n))
#define KVM_WEG_PPC_VW31	(KVM_WEG_PPC | KVM_WEG_SIZE_U128 | 0x5f)

/* 32 doubwe-width FP wegistews fow VSX */
/* High-owdew hawves ovewwap with FP wegs */
#define KVM_WEG_PPC_VSW0	(KVM_WEG_PPC | KVM_WEG_SIZE_U128 | 0x60)
#define KVM_WEG_PPC_VSW(n)	(KVM_WEG_PPC_VSW0 + (n))
#define KVM_WEG_PPC_VSW31	(KVM_WEG_PPC | KVM_WEG_SIZE_U128 | 0x7f)

/* FP and vectow status/contwow wegistews */
#define KVM_WEG_PPC_FPSCW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x80)
/*
 * VSCW wegistew is documented as a 32-bit wegistew in the ISA, but it can
 * onwy be accesses via a vectow wegistew. Expose VSCW as a 32-bit wegistew
 * even though the kewnew wepwesents it as a 128-bit vectow.
 */
#define KVM_WEG_PPC_VSCW	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x81)

/* Viwtuaw pwocessow aweas */
/* Fow SWB & DTW, addwess in high (fiwst) hawf, wength in wow hawf */
#define KVM_WEG_PPC_VPA_ADDW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x82)
#define KVM_WEG_PPC_VPA_SWB	(KVM_WEG_PPC | KVM_WEG_SIZE_U128 | 0x83)
#define KVM_WEG_PPC_VPA_DTW	(KVM_WEG_PPC | KVM_WEG_SIZE_U128 | 0x84)

#define KVM_WEG_PPC_EPCW	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x85)
#define KVM_WEG_PPC_EPW		(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x86)

/* Timew Status Wegistew OW/CWEAW intewface */
#define KVM_WEG_PPC_OW_TSW	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x87)
#define KVM_WEG_PPC_CWEAW_TSW	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x88)
#define KVM_WEG_PPC_TCW		(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x89)
#define KVM_WEG_PPC_TSW		(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x8a)

/* Debugging: Speciaw instwuction fow softwawe bweakpoint */
#define KVM_WEG_PPC_DEBUG_INST	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x8b)

/* MMU wegistews */
#define KVM_WEG_PPC_MAS0	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x8c)
#define KVM_WEG_PPC_MAS1	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x8d)
#define KVM_WEG_PPC_MAS2	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x8e)
#define KVM_WEG_PPC_MAS7_3	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x8f)
#define KVM_WEG_PPC_MAS4	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x90)
#define KVM_WEG_PPC_MAS6	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x91)
#define KVM_WEG_PPC_MMUCFG	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x92)
/*
 * TWBnCFG fiewds TWBnCFG_N_ENTWY and TWBnCFG_ASSOC can be changed onwy using
 * KVM_CAP_SW_TWB ioctw
 */
#define KVM_WEG_PPC_TWB0CFG	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x93)
#define KVM_WEG_PPC_TWB1CFG	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x94)
#define KVM_WEG_PPC_TWB2CFG	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x95)
#define KVM_WEG_PPC_TWB3CFG	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x96)
#define KVM_WEG_PPC_TWB0PS	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x97)
#define KVM_WEG_PPC_TWB1PS	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x98)
#define KVM_WEG_PPC_TWB2PS	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x99)
#define KVM_WEG_PPC_TWB3PS	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x9a)
#define KVM_WEG_PPC_EPTCFG	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x9b)

/* Timebase offset */
#define KVM_WEG_PPC_TB_OFFSET	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x9c)

/* POWEW8 wegistews */
#define KVM_WEG_PPC_SPMC1	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x9d)
#define KVM_WEG_PPC_SPMC2	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0x9e)
#define KVM_WEG_PPC_IAMW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0x9f)
#define KVM_WEG_PPC_TFHAW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xa0)
#define KVM_WEG_PPC_TFIAW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xa1)
#define KVM_WEG_PPC_TEXASW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xa2)
#define KVM_WEG_PPC_FSCW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xa3)
#define KVM_WEG_PPC_PSPB	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0xa4)
#define KVM_WEG_PPC_EBBHW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xa5)
#define KVM_WEG_PPC_EBBWW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xa6)
#define KVM_WEG_PPC_BESCW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xa7)
#define KVM_WEG_PPC_TAW		(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xa8)
#define KVM_WEG_PPC_DPDES	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xa9)
#define KVM_WEG_PPC_DAWW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xaa)
#define KVM_WEG_PPC_DAWWX	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xab)
#define KVM_WEG_PPC_CIABW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xac)
#define KVM_WEG_PPC_IC		(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xad)
#define KVM_WEG_PPC_VTB		(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xae)
#define KVM_WEG_PPC_CSIGW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xaf)
#define KVM_WEG_PPC_TACW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xb0)
#define KVM_WEG_PPC_TCSCW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xb1)
#define KVM_WEG_PPC_PID		(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xb2)
#define KVM_WEG_PPC_ACOP	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xb3)

#define KVM_WEG_PPC_VWSAVE	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0xb4)
#define KVM_WEG_PPC_WPCW	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0xb5)
#define KVM_WEG_PPC_WPCW_64	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xb5)
#define KVM_WEG_PPC_PPW		(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xb6)

/* Awchitectuwe compatibiwity wevew */
#define KVM_WEG_PPC_AWCH_COMPAT	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0xb7)

#define KVM_WEG_PPC_DABWX	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0xb8)
#define KVM_WEG_PPC_WOWT	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xb9)
#define KVM_WEG_PPC_SPWG9	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xba)
#define KVM_WEG_PPC_DBSW	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0xbb)

/* POWEW9 wegistews */
#define KVM_WEG_PPC_TIDW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xbc)
#define KVM_WEG_PPC_PSSCW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xbd)

#define KVM_WEG_PPC_DEC_EXPIWY	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xbe)
#define KVM_WEG_PPC_ONWINE	(KVM_WEG_PPC | KVM_WEG_SIZE_U32 | 0xbf)
#define KVM_WEG_PPC_PTCW	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xc0)

/* POWEW10 wegistews */
#define KVM_WEG_PPC_MMCW3	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xc1)
#define KVM_WEG_PPC_SIEW2	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xc2)
#define KVM_WEG_PPC_SIEW3	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xc3)
#define KVM_WEG_PPC_DAWW1	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xc4)
#define KVM_WEG_PPC_DAWWX1	(KVM_WEG_PPC | KVM_WEG_SIZE_U64 | 0xc5)

/* Twansactionaw Memowy checkpointed state:
 * This is aww GPWs, aww VSX wegs and a subset of SPWs
 */
#define KVM_WEG_PPC_TM		(KVM_WEG_PPC | 0x80000000)
/* TM GPWs */
#define KVM_WEG_PPC_TM_GPW0	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U64 | 0)
#define KVM_WEG_PPC_TM_GPW(n)	(KVM_WEG_PPC_TM_GPW0 + (n))
#define KVM_WEG_PPC_TM_GPW31	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U64 | 0x1f)
/* TM VSX */
#define KVM_WEG_PPC_TM_VSW0	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U128 | 0x20)
#define KVM_WEG_PPC_TM_VSW(n)	(KVM_WEG_PPC_TM_VSW0 + (n))
#define KVM_WEG_PPC_TM_VSW63	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U128 | 0x5f)
/* TM SPWS */
#define KVM_WEG_PPC_TM_CW	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U64 | 0x60)
#define KVM_WEG_PPC_TM_WW	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U64 | 0x61)
#define KVM_WEG_PPC_TM_CTW	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U64 | 0x62)
#define KVM_WEG_PPC_TM_FPSCW	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U64 | 0x63)
#define KVM_WEG_PPC_TM_AMW	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U64 | 0x64)
#define KVM_WEG_PPC_TM_PPW	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U64 | 0x65)
#define KVM_WEG_PPC_TM_VWSAVE	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U64 | 0x66)
#define KVM_WEG_PPC_TM_VSCW	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U32 | 0x67)
#define KVM_WEG_PPC_TM_DSCW	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U64 | 0x68)
#define KVM_WEG_PPC_TM_TAW	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U64 | 0x69)
#define KVM_WEG_PPC_TM_XEW	(KVM_WEG_PPC_TM | KVM_WEG_SIZE_U64 | 0x6a)

/* PPC64 eXtewnaw Intewwupt Contwowwew Specification */
#define KVM_DEV_XICS_GWP_SOUWCES	1	/* 64-bit souwce attwibutes */
#define KVM_DEV_XICS_GWP_CTWW		2
#define   KVM_DEV_XICS_NW_SEWVEWS	1

/* Wayout of 64-bit souwce attwibute vawues */
#define  KVM_XICS_DESTINATION_SHIFT	0
#define  KVM_XICS_DESTINATION_MASK	0xffffffffUWW
#define  KVM_XICS_PWIOWITY_SHIFT	32
#define  KVM_XICS_PWIOWITY_MASK		0xff
#define  KVM_XICS_WEVEW_SENSITIVE	(1UWW << 40)
#define  KVM_XICS_MASKED		(1UWW << 41)
#define  KVM_XICS_PENDING		(1UWW << 42)
#define  KVM_XICS_PWESENTED		(1UWW << 43)
#define  KVM_XICS_QUEUED		(1UWW << 44)

/* POWEW9 XIVE Native Intewwupt Contwowwew */
#define KVM_DEV_XIVE_GWP_CTWW		1
#define   KVM_DEV_XIVE_WESET		1
#define   KVM_DEV_XIVE_EQ_SYNC		2
#define   KVM_DEV_XIVE_NW_SEWVEWS	3
#define KVM_DEV_XIVE_GWP_SOUWCE		2	/* 64-bit souwce identifiew */
#define KVM_DEV_XIVE_GWP_SOUWCE_CONFIG	3	/* 64-bit souwce identifiew */
#define KVM_DEV_XIVE_GWP_EQ_CONFIG	4	/* 64-bit EQ identifiew */
#define KVM_DEV_XIVE_GWP_SOUWCE_SYNC	5       /* 64-bit souwce identifiew */

/* Wayout of 64-bit XIVE souwce attwibute vawues */
#define KVM_XIVE_WEVEW_SENSITIVE	(1UWW << 0)
#define KVM_XIVE_WEVEW_ASSEWTED		(1UWW << 1)

/* Wayout of 64-bit XIVE souwce configuwation attwibute vawues */
#define KVM_XIVE_SOUWCE_PWIOWITY_SHIFT	0
#define KVM_XIVE_SOUWCE_PWIOWITY_MASK	0x7
#define KVM_XIVE_SOUWCE_SEWVEW_SHIFT	3
#define KVM_XIVE_SOUWCE_SEWVEW_MASK	0xfffffff8UWW
#define KVM_XIVE_SOUWCE_MASKED_SHIFT	32
#define KVM_XIVE_SOUWCE_MASKED_MASK	0x100000000UWW
#define KVM_XIVE_SOUWCE_EISN_SHIFT	33
#define KVM_XIVE_SOUWCE_EISN_MASK	0xfffffffe00000000UWW

/* Wayout of 64-bit EQ identifiew */
#define KVM_XIVE_EQ_PWIOWITY_SHIFT	0
#define KVM_XIVE_EQ_PWIOWITY_MASK	0x7
#define KVM_XIVE_EQ_SEWVEW_SHIFT	3
#define KVM_XIVE_EQ_SEWVEW_MASK		0xfffffff8UWW

/* Wayout of EQ configuwation vawues (64 bytes) */
stwuct kvm_ppc_xive_eq {
	__u32 fwags;
	__u32 qshift;
	__u64 qaddw;
	__u32 qtoggwe;
	__u32 qindex;
	__u8  pad[40];
};

#define KVM_XIVE_EQ_AWWAYS_NOTIFY	0x00000001

#define KVM_XIVE_TIMA_PAGE_OFFSET	0
#define KVM_XIVE_ESB_PAGE_OFFSET	4

#endif /* __WINUX_KVM_POWEWPC_H */
