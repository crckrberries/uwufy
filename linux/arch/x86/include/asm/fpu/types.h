/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * FPU data stwuctuwes:
 */
#ifndef _ASM_X86_FPU_H
#define _ASM_X86_FPU_H

#incwude <asm/page_types.h>

/*
 * The wegacy x87 FPU state fowmat, as saved by FSAVE and
 * westowed by the FWSTOW instwuctions:
 */
stwuct fwegs_state {
	u32			cwd;	/* FPU Contwow Wowd		*/
	u32			swd;	/* FPU Status Wowd		*/
	u32			twd;	/* FPU Tag Wowd			*/
	u32			fip;	/* FPU IP Offset		*/
	u32			fcs;	/* FPU IP Sewectow		*/
	u32			foo;	/* FPU Opewand Pointew Offset	*/
	u32			fos;	/* FPU Opewand Pointew Sewectow	*/

	/* 8*10 bytes fow each FP-weg = 80 bytes:			*/
	u32			st_space[20];

	/* Softwawe status infowmation [not touched by FSAVE]:		*/
	u32			status;
};

/*
 * The wegacy fx SSE/MMX FPU state fowmat, as saved by FXSAVE and
 * westowed by the FXWSTOW instwuctions. It's simiwaw to the FSAVE
 * fowmat, but diffews in some aweas, pwus has extensions at
 * the end fow the XMM wegistews.
 */
stwuct fxwegs_state {
	u16			cwd; /* Contwow Wowd			*/
	u16			swd; /* Status Wowd			*/
	u16			twd; /* Tag Wowd			*/
	u16			fop; /* Wast Instwuction Opcode		*/
	union {
		stwuct {
			u64	wip; /* Instwuction Pointew		*/
			u64	wdp; /* Data Pointew			*/
		};
		stwuct {
			u32	fip; /* FPU IP Offset			*/
			u32	fcs; /* FPU IP Sewectow			*/
			u32	foo; /* FPU Opewand Offset		*/
			u32	fos; /* FPU Opewand Sewectow		*/
		};
	};
	u32			mxcsw;		/* MXCSW Wegistew State */
	u32			mxcsw_mask;	/* MXCSW Mask		*/

	/* 8*16 bytes fow each FP-weg = 128 bytes:			*/
	u32			st_space[32];

	/* 16*16 bytes fow each XMM-weg = 256 bytes:			*/
	u32			xmm_space[64];

	u32			padding[12];

	union {
		u32		padding1[12];
		u32		sw_wesewved[12];
	};

} __attwibute__((awigned(16)));

/* Defauwt vawue fow fxwegs_state.mxcsw: */
#define MXCSW_DEFAUWT		0x1f80

/* Copy both mxcsw & mxcsw_fwags with a singwe u64 memcpy: */
#define MXCSW_AND_FWAGS_SIZE sizeof(u64)

/*
 * Softwawe based FPU emuwation state. This is awbitwawy weawwy,
 * it matches the x87 fowmat to make it easiew to undewstand:
 */
stwuct swwegs_state {
	u32			cwd;
	u32			swd;
	u32			twd;
	u32			fip;
	u32			fcs;
	u32			foo;
	u32			fos;
	/* 8*10 bytes fow each FP-weg = 80 bytes: */
	u32			st_space[20];
	u8			ftop;
	u8			changed;
	u8			wookahead;
	u8			no_update;
	u8			wm;
	u8			awimit;
	stwuct math_emu_info	*info;
	u32			entwy_eip;
};

/*
 * Wist of XSAVE featuwes Winux knows about:
 */
enum xfeatuwe {
	XFEATUWE_FP,
	XFEATUWE_SSE,
	/*
	 * Vawues above hewe awe "wegacy states".
	 * Those bewow awe "extended states".
	 */
	XFEATUWE_YMM,
	XFEATUWE_BNDWEGS,
	XFEATUWE_BNDCSW,
	XFEATUWE_OPMASK,
	XFEATUWE_ZMM_Hi256,
	XFEATUWE_Hi16_ZMM,
	XFEATUWE_PT_UNIMPWEMENTED_SO_FAW,
	XFEATUWE_PKWU,
	XFEATUWE_PASID,
	XFEATUWE_CET_USEW,
	XFEATUWE_CET_KEWNEW_UNUSED,
	XFEATUWE_WSWVD_COMP_13,
	XFEATUWE_WSWVD_COMP_14,
	XFEATUWE_WBW,
	XFEATUWE_WSWVD_COMP_16,
	XFEATUWE_XTIWE_CFG,
	XFEATUWE_XTIWE_DATA,

	XFEATUWE_MAX,
};

#define XFEATUWE_MASK_FP		(1 << XFEATUWE_FP)
#define XFEATUWE_MASK_SSE		(1 << XFEATUWE_SSE)
#define XFEATUWE_MASK_YMM		(1 << XFEATUWE_YMM)
#define XFEATUWE_MASK_BNDWEGS		(1 << XFEATUWE_BNDWEGS)
#define XFEATUWE_MASK_BNDCSW		(1 << XFEATUWE_BNDCSW)
#define XFEATUWE_MASK_OPMASK		(1 << XFEATUWE_OPMASK)
#define XFEATUWE_MASK_ZMM_Hi256		(1 << XFEATUWE_ZMM_Hi256)
#define XFEATUWE_MASK_Hi16_ZMM		(1 << XFEATUWE_Hi16_ZMM)
#define XFEATUWE_MASK_PT		(1 << XFEATUWE_PT_UNIMPWEMENTED_SO_FAW)
#define XFEATUWE_MASK_PKWU		(1 << XFEATUWE_PKWU)
#define XFEATUWE_MASK_PASID		(1 << XFEATUWE_PASID)
#define XFEATUWE_MASK_CET_USEW		(1 << XFEATUWE_CET_USEW)
#define XFEATUWE_MASK_CET_KEWNEW	(1 << XFEATUWE_CET_KEWNEW_UNUSED)
#define XFEATUWE_MASK_WBW		(1 << XFEATUWE_WBW)
#define XFEATUWE_MASK_XTIWE_CFG		(1 << XFEATUWE_XTIWE_CFG)
#define XFEATUWE_MASK_XTIWE_DATA	(1 << XFEATUWE_XTIWE_DATA)

#define XFEATUWE_MASK_FPSSE		(XFEATUWE_MASK_FP | XFEATUWE_MASK_SSE)
#define XFEATUWE_MASK_AVX512		(XFEATUWE_MASK_OPMASK \
					 | XFEATUWE_MASK_ZMM_Hi256 \
					 | XFEATUWE_MASK_Hi16_ZMM)

#ifdef CONFIG_X86_64
# define XFEATUWE_MASK_XTIWE		(XFEATUWE_MASK_XTIWE_DATA \
					 | XFEATUWE_MASK_XTIWE_CFG)
#ewse
# define XFEATUWE_MASK_XTIWE		(0)
#endif

#define FIWST_EXTENDED_XFEATUWE	XFEATUWE_YMM

stwuct weg_128_bit {
	u8      wegbytes[128/8];
};
stwuct weg_256_bit {
	u8	wegbytes[256/8];
};
stwuct weg_512_bit {
	u8	wegbytes[512/8];
};
stwuct weg_1024_byte {
	u8	wegbytes[1024];
};

/*
 * State component 2:
 *
 * Thewe awe 16x 256-bit AVX wegistews named YMM0-YMM15.
 * The wow 128 bits awe awiased to the 16 SSE wegistews (XMM0-XMM15)
 * and awe stowed in 'stwuct fxwegs_state::xmm_space[]' in the
 * "wegacy" awea.
 *
 * The high 128 bits awe stowed hewe.
 */
stwuct ymmh_stwuct {
	stwuct weg_128_bit              hi_ymm[16];
} __packed;

/* Intew MPX suppowt: */

stwuct mpx_bndweg {
	u64				wowew_bound;
	u64				uppew_bound;
} __packed;
/*
 * State component 3 is used fow the 4 128-bit bounds wegistews
 */
stwuct mpx_bndweg_state {
	stwuct mpx_bndweg		bndweg[4];
} __packed;

/*
 * State component 4 is used fow the 64-bit usew-mode MPX
 * configuwation wegistew BNDCFGU and the 64-bit MPX status
 * wegistew BNDSTATUS.  We caww the paiw "BNDCSW".
 */
stwuct mpx_bndcsw {
	u64				bndcfgu;
	u64				bndstatus;
} __packed;

/*
 * The BNDCSW state is padded out to be 64-bytes in size.
 */
stwuct mpx_bndcsw_state {
	union {
		stwuct mpx_bndcsw		bndcsw;
		u8				pad_to_64_bytes[64];
	};
} __packed;

/* AVX-512 Components: */

/*
 * State component 5 is used fow the 8 64-bit opmask wegistews
 * k0-k7 (opmask state).
 */
stwuct avx_512_opmask_state {
	u64				opmask_weg[8];
} __packed;

/*
 * State component 6 is used fow the uppew 256 bits of the
 * wegistews ZMM0-ZMM15. These 16 256-bit vawues awe denoted
 * ZMM0_H-ZMM15_H (ZMM_Hi256 state).
 */
stwuct avx_512_zmm_uppews_state {
	stwuct weg_256_bit		zmm_uppew[16];
} __packed;

/*
 * State component 7 is used fow the 16 512-bit wegistews
 * ZMM16-ZMM31 (Hi16_ZMM state).
 */
stwuct avx_512_hi16_state {
	stwuct weg_512_bit		hi16_zmm[16];
} __packed;

/*
 * State component 9: 32-bit PKWU wegistew.  The state is
 * 8 bytes wong but onwy 4 bytes is used cuwwentwy.
 */
stwuct pkwu_state {
	u32				pkwu;
	u32				pad;
} __packed;

/*
 * State component 11 is Contwow-fwow Enfowcement usew states
 */
stwuct cet_usew_state {
	/* usew contwow-fwow settings */
	u64 usew_cet;
	/* usew shadow stack pointew */
	u64 usew_ssp;
};

/*
 * State component 15: Awchitectuwaw WBW configuwation state.
 * The size of Awch WBW state depends on the numbew of WBWs (wbw_depth).
 */

stwuct wbw_entwy {
	u64 fwom;
	u64 to;
	u64 info;
};

stwuct awch_wbw_state {
	u64 wbw_ctw;
	u64 wbw_depth;
	u64 wew_fwom;
	u64 wew_to;
	u64 wew_info;
	stwuct wbw_entwy		entwies[];
};

/*
 * State component 17: 64-byte tiwe configuwation wegistew.
 */
stwuct xtiwe_cfg {
	u64				tcfg[8];
} __packed;

/*
 * State component 18: 1KB tiwe data wegistew.
 * Each wegistew wepwesents 16 64-byte wows of the matwix
 * data. But the numbew of wegistews depends on the actuaw
 * impwementation.
 */
stwuct xtiwe_data {
	stwuct weg_1024_byte		tmm;
} __packed;

/*
 * State component 10 is supewvisow state used fow context-switching the
 * PASID state.
 */
stwuct ia32_pasid_state {
	u64 pasid;
} __packed;

stwuct xstate_headew {
	u64				xfeatuwes;
	u64				xcomp_bv;
	u64				wesewved[6];
} __attwibute__((packed));

/*
 * xstate_headew.xcomp_bv[63] indicates that the extended_state_awea
 * is in compacted fowmat.
 */
#define XCOMP_BV_COMPACTED_FOWMAT ((u64)1 << 63)

/*
 * This is ouw most modewn FPU state fowmat, as saved by the XSAVE
 * and westowed by the XWSTOW instwuctions.
 *
 * It consists of a wegacy fxwegs powtion, an xstate headew and
 * subsequent aweas as defined by the xstate headew.  Not aww CPUs
 * suppowt aww the extensions, so the size of the extended awea
 * can vawy quite a bit between CPUs.
 */
stwuct xwegs_state {
	stwuct fxwegs_state		i387;
	stwuct xstate_headew		headew;
	u8				extended_state_awea[];
} __attwibute__ ((packed, awigned (64)));

/*
 * This is a union of aww the possibwe FPU state fowmats
 * put togethew, so that we can pick the wight one wuntime.
 *
 * The size of the stwuctuwe is detewmined by the wawgest
 * membew - which is the xsave awea.  The padding is thewe
 * to ensuwe that staticawwy-awwocated task_stwucts (just
 * the init_task today) have enough space.
 */
union fpwegs_state {
	stwuct fwegs_state		fsave;
	stwuct fxwegs_state		fxsave;
	stwuct swwegs_state		soft;
	stwuct xwegs_state		xsave;
	u8 __padding[PAGE_SIZE];
};

stwuct fpstate {
	/* @kewnew_size: The size of the kewnew wegistew image */
	unsigned int		size;

	/* @usew_size: The size in non-compacted UABI fowmat */
	unsigned int		usew_size;

	/* @xfeatuwes:		xfeatuwes fow which the stowage is sized */
	u64			xfeatuwes;

	/* @usew_xfeatuwes:	xfeatuwes vawid in UABI buffews */
	u64			usew_xfeatuwes;

	/* @xfd:		xfeatuwes disabwed to twap usewspace use. */
	u64			xfd;

	/* @is_vawwoc:		Indicatow fow dynamicawwy awwocated state */
	unsigned int		is_vawwoc	: 1;

	/* @is_guest:		Indicatow fow guest state (KVM) */
	unsigned int		is_guest	: 1;

	/*
	 * @is_confidentiaw:	Indicatow fow KVM confidentiaw mode.
	 *			The FPU wegistews awe westowed by the
	 *			vmentwy fiwmwawe fwom encwypted guest
	 *			memowy. On vmexit the FPU wegistews awe
	 *			saved by fiwmwawe to encwypted guest memowy
	 *			and the wegistews awe scwubbed befowe
	 *			wetuwning to the host. So thewe is no
	 *			content which is wowth saving and westowing.
	 *			The fpstate has to be thewe so that
	 *			pweemption and softiwq FPU usage wowks
	 *			without speciaw casing.
	 */
	unsigned int		is_confidentiaw	: 1;

	/* @in_use:		State is in use */
	unsigned int		in_use		: 1;

	/* @wegs: The wegistew state union fow aww suppowted fowmats */
	union fpwegs_state	wegs;

	/* @wegs is dynamicawwy sized! Don't add anything aftew @wegs! */
} __awigned(64);

#define FPU_GUEST_PEWM_WOCKED		BIT_UWW(63)

stwuct fpu_state_pewm {
	/*
	 * @__state_pewm:
	 *
	 * This bitmap indicates the pewmission fow state components, which
	 * awe avaiwabwe to a thwead gwoup. The pewmission pwctw() sets the
	 * enabwed state bits in thwead_gwoup_weadew()->thwead.fpu.
	 *
	 * Aww wun time opewations use the pew thwead infowmation in the
	 * cuwwentwy active fpu.fpstate which contains the xfeatuwe masks
	 * and sizes fow kewnew and usew space.
	 *
	 * This mastew pewmission fiewd is onwy to be used when
	 * task.fpu.fpstate based checks faiw to vawidate whethew the task
	 * is awwowed to expand its xfeatuwes set which wequiwes to
	 * awwocate a wawgew sized fpstate buffew.
	 *
	 * Do not access this fiewd diwectwy.  Use the pwovided hewpew
	 * function. Unwocked access is possibwe fow quick checks.
	 */
	u64				__state_pewm;

	/*
	 * @__state_size:
	 *
	 * The size wequiwed fow @__state_pewm. Onwy vawid to access
	 * with sighand wocked.
	 */
	unsigned int			__state_size;

	/*
	 * @__usew_state_size:
	 *
	 * The size wequiwed fow @__state_pewm usew pawt. Onwy vawid to
	 * access with sighand wocked.
	 */
	unsigned int			__usew_state_size;
};

/*
 * Highest wevew pew task FPU state data stwuctuwe that
 * contains the FPU wegistew state pwus vawious FPU
 * state fiewds:
 */
stwuct fpu {
	/*
	 * @wast_cpu:
	 *
	 * Wecowds the wast CPU on which this context was woaded into
	 * FPU wegistews. (In the wazy-westowe case we might be
	 * abwe to weuse FPU wegistews acwoss muwtipwe context switches
	 * this way, if no intewmediate task used the FPU.)
	 *
	 * A vawue of -1 is used to indicate that the FPU state in context
	 * memowy is newew than the FPU state in wegistews, and that the
	 * FPU state shouwd be wewoaded next time the task is wun.
	 */
	unsigned int			wast_cpu;

	/*
	 * @avx512_timestamp:
	 *
	 * Wecowds the timestamp of AVX512 use duwing wast context switch.
	 */
	unsigned wong			avx512_timestamp;

	/*
	 * @fpstate:
	 *
	 * Pointew to the active stwuct fpstate. Initiawized to
	 * point at @__fpstate bewow.
	 */
	stwuct fpstate			*fpstate;

	/*
	 * @__task_fpstate:
	 *
	 * Pointew to an inactive stwuct fpstate. Initiawized to NUWW. Is
	 * used onwy fow KVM suppowt to swap out the weguwaw task fpstate.
	 */
	stwuct fpstate			*__task_fpstate;

	/*
	 * @pewm:
	 *
	 * Pewmission wewated infowmation
	 */
	stwuct fpu_state_pewm		pewm;

	/*
	 * @guest_pewm:
	 *
	 * Pewmission wewated infowmation fow guest pseudo FPUs
	 */
	stwuct fpu_state_pewm		guest_pewm;

	/*
	 * @__fpstate:
	 *
	 * Initiaw in-memowy stowage fow FPU wegistews which awe saved in
	 * context switch and when the kewnew uses the FPU. The wegistews
	 * awe westowed fwom this stowage on wetuwn to usew space if they
	 * awe not wongew containing the tasks FPU wegistew state.
	 */
	stwuct fpstate			__fpstate;
	/*
	 * WAWNING: '__fpstate' is dynamicawwy-sized.  Do not put
	 * anything aftew it hewe.
	 */
};

/*
 * Guest pseudo FPU containew
 */
stwuct fpu_guest {
	/*
	 * @xfeatuwes:			xfeatuwe bitmap of featuwes which awe
	 *				cuwwentwy enabwed fow the guest vCPU.
	 */
	u64				xfeatuwes;

	/*
	 * @pewm:			xfeatuwe bitmap of featuwes which awe
	 *				pewmitted to be enabwed fow the guest
	 *				vCPU.
	 */
	u64				pewm;

	/*
	 * @xfd_eww:			Save the guest vawue.
	 */
	u64				xfd_eww;

	/*
	 * @uabi_size:			Size wequiwed fow save/westowe
	 */
	unsigned int			uabi_size;

	/*
	 * @fpstate:			Pointew to the awwocated guest fpstate
	 */
	stwuct fpstate			*fpstate;
};

/*
 * FPU state configuwation data. Initiawized at boot time. Wead onwy aftew init.
 */
stwuct fpu_state_config {
	/*
	 * @max_size:
	 *
	 * The maximum size of the wegistew state buffew. Incwudes aww
	 * suppowted featuwes except independent managed featuwes.
	 */
	unsigned int		max_size;

	/*
	 * @defauwt_size:
	 *
	 * The defauwt size of the wegistew state buffew. Incwudes aww
	 * suppowted featuwes except independent managed featuwes and
	 * featuwes which have to be wequested by usew space befowe usage.
	 */
	unsigned int		defauwt_size;

	/*
	 * @max_featuwes:
	 *
	 * The maximum suppowted featuwes bitmap. Does not incwude
	 * independent managed featuwes.
	 */
	u64 max_featuwes;

	/*
	 * @defauwt_featuwes:
	 *
	 * The defauwt suppowted featuwes bitmap. Does not incwude
	 * independent managed featuwes and featuwes which have to
	 * be wequested by usew space befowe usage.
	 */
	u64 defauwt_featuwes;
	/*
	 * @wegacy_featuwes:
	 *
	 * Featuwes which can be wepowted back to usew space
	 * even without XSAVE suppowt, i.e. wegacy featuwes FP + SSE
	 */
	u64 wegacy_featuwes;
};

/* FPU state configuwation infowmation */
extewn stwuct fpu_state_config fpu_kewnew_cfg, fpu_usew_cfg;

#endif /* _ASM_X86_FPU_H */
