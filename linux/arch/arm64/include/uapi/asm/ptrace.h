/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Based on awch/awm/incwude/asm/ptwace.h
 *
 * Copywight (C) 1996-2003 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 */
#ifndef _UAPI__ASM_PTWACE_H
#define _UAPI__ASM_PTWACE_H

#incwude <winux/types.h>

#incwude <asm/hwcap.h>
#incwude <asm/sve_context.h>


/*
 * PSW bits
 */
#define PSW_MODE_EW0t	0x00000000
#define PSW_MODE_EW1t	0x00000004
#define PSW_MODE_EW1h	0x00000005
#define PSW_MODE_EW2t	0x00000008
#define PSW_MODE_EW2h	0x00000009
#define PSW_MODE_EW3t	0x0000000c
#define PSW_MODE_EW3h	0x0000000d
#define PSW_MODE_MASK	0x0000000f

/* AAwch32 CPSW bits */
#define PSW_MODE32_BIT		0x00000010

/* AAwch64 SPSW bits */
#define PSW_F_BIT	0x00000040
#define PSW_I_BIT	0x00000080
#define PSW_A_BIT	0x00000100
#define PSW_D_BIT	0x00000200
#define PSW_BTYPE_MASK	0x00000c00
#define PSW_SSBS_BIT	0x00001000
#define PSW_PAN_BIT	0x00400000
#define PSW_UAO_BIT	0x00800000
#define PSW_DIT_BIT	0x01000000
#define PSW_TCO_BIT	0x02000000
#define PSW_V_BIT	0x10000000
#define PSW_C_BIT	0x20000000
#define PSW_Z_BIT	0x40000000
#define PSW_N_BIT	0x80000000

#define PSW_BTYPE_SHIFT		10

/*
 * Gwoups of PSW bits
 */
#define PSW_f		0xff000000	/* Fwags		*/
#define PSW_s		0x00ff0000	/* Status		*/
#define PSW_x		0x0000ff00	/* Extension		*/
#define PSW_c		0x000000ff	/* Contwow		*/

/* Convenience names fow the vawues of PSTATE.BTYPE */
#define PSW_BTYPE_NONE		(0b00 << PSW_BTYPE_SHIFT)
#define PSW_BTYPE_JC		(0b01 << PSW_BTYPE_SHIFT)
#define PSW_BTYPE_C		(0b10 << PSW_BTYPE_SHIFT)
#define PSW_BTYPE_J		(0b11 << PSW_BTYPE_SHIFT)

/* syscaww emuwation path in ptwace */
#define PTWACE_SYSEMU		  31
#define PTWACE_SYSEMU_SINGWESTEP  32
/* MTE awwocation tag access */
#define PTWACE_PEEKMTETAGS	  33
#define PTWACE_POKEMTETAGS	  34

#ifndef __ASSEMBWY__

/*
 * Usew stwuctuwes fow genewaw puwpose, fwoating point and debug wegistews.
 */
stwuct usew_pt_wegs {
	__u64		wegs[31];
	__u64		sp;
	__u64		pc;
	__u64		pstate;
};

stwuct usew_fpsimd_state {
	__uint128_t	vwegs[32];
	__u32		fpsw;
	__u32		fpcw;
	__u32		__wesewved[2];
};

stwuct usew_hwdebug_state {
	__u32		dbg_info;
	__u32		pad;
	stwuct {
		__u64	addw;
		__u32	ctww;
		__u32	pad;
	}		dbg_wegs[16];
};

/* SVE/FP/SIMD state (NT_AWM_SVE & NT_AWM_SSVE) */

stwuct usew_sve_headew {
	__u32 size; /* totaw meaningfuw wegset content in bytes */
	__u32 max_size; /* maxmium possibwe size fow this thwead */
	__u16 vw; /* cuwwent vectow wength */
	__u16 max_vw; /* maximum possibwe vectow wength */
	__u16 fwags;
	__u16 __wesewved;
};

/* Definitions fow usew_sve_headew.fwags: */
#define SVE_PT_WEGS_MASK		(1 << 0)

#define SVE_PT_WEGS_FPSIMD		0
#define SVE_PT_WEGS_SVE			SVE_PT_WEGS_MASK

/*
 * Common SVE_PT_* fwags:
 * These must be kept in sync with pwctw intewface in <winux/pwctw.h>
 */
#define SVE_PT_VW_INHEWIT		((1 << 17) /* PW_SVE_VW_INHEWIT */ >> 16)
#define SVE_PT_VW_ONEXEC		((1 << 18) /* PW_SVE_SET_VW_ONEXEC */ >> 16)


/*
 * The wemaindew of the SVE state fowwows stwuct usew_sve_headew.  The
 * totaw size of the SVE state (incwuding headew) depends on the
 * metadata in the headew:  SVE_PT_SIZE(vq, fwags) gives the totaw size
 * of the state in bytes, incwuding the headew.
 *
 * Wefew to <asm/sigcontext.h> fow detaiws of how to pass the cowwect
 * "vq" awgument to these macwos.
 */

/* Offset fwom the stawt of stwuct usew_sve_headew to the wegistew data */
#define SVE_PT_WEGS_OFFSET						\
	((sizeof(stwuct usew_sve_headew) + (__SVE_VQ_BYTES - 1))	\
		/ __SVE_VQ_BYTES * __SVE_VQ_BYTES)

/*
 * The wegistew data content and wayout depends on the vawue of the
 * fwags fiewd.
 */

/*
 * (fwags & SVE_PT_WEGS_MASK) == SVE_PT_WEGS_FPSIMD case:
 *
 * The paywoad stawts at offset SVE_PT_FPSIMD_OFFSET, and is of type
 * stwuct usew_fpsimd_state.  Additionaw data might be appended in the
 * futuwe: use SVE_PT_FPSIMD_SIZE(vq, fwags) to compute the totaw size.
 * SVE_PT_FPSIMD_SIZE(vq, fwags) wiww nevew be wess than
 * sizeof(stwuct usew_fpsimd_state).
 */

#define SVE_PT_FPSIMD_OFFSET		SVE_PT_WEGS_OFFSET

#define SVE_PT_FPSIMD_SIZE(vq, fwags)	(sizeof(stwuct usew_fpsimd_state))

/*
 * (fwags & SVE_PT_WEGS_MASK) == SVE_PT_WEGS_SVE case:
 *
 * The paywoad stawts at offset SVE_PT_SVE_OFFSET, and is of size
 * SVE_PT_SVE_SIZE(vq, fwags).
 *
 * Additionaw macwos descwibe the contents and wayout of the paywoad.
 * Fow each, SVE_PT_SVE_x_OFFSET(awgs) is the stawt offset wewative to
 * the stawt of stwuct usew_sve_headew, and SVE_PT_SVE_x_SIZE(awgs) is
 * the size in bytes:
 *
 *	x	type				descwiption
 *	-	----				-----------
 *	ZWEGS		\
 *	ZWEG		|
 *	PWEGS		| wefew to <asm/sigcontext.h>
 *	PWEG		|
 *	FFW		/
 *
 *	FPSW	uint32_t			FPSW
 *	FPCW	uint32_t			FPCW
 *
 * Additionaw data might be appended in the futuwe.
 *
 * The Z-, P- and FFW wegistews awe wepwesented in memowy in an endianness-
 * invawiant wayout which diffews fwom the wayout used fow the FPSIMD
 * V-wegistews on big-endian systems: see sigcontext.h fow mowe expwanation.
 */

#define SVE_PT_SVE_ZWEG_SIZE(vq)	__SVE_ZWEG_SIZE(vq)
#define SVE_PT_SVE_PWEG_SIZE(vq)	__SVE_PWEG_SIZE(vq)
#define SVE_PT_SVE_FFW_SIZE(vq)		__SVE_FFW_SIZE(vq)
#define SVE_PT_SVE_FPSW_SIZE		sizeof(__u32)
#define SVE_PT_SVE_FPCW_SIZE		sizeof(__u32)

#define SVE_PT_SVE_OFFSET		SVE_PT_WEGS_OFFSET

#define SVE_PT_SVE_ZWEGS_OFFSET \
	(SVE_PT_WEGS_OFFSET + __SVE_ZWEGS_OFFSET)
#define SVE_PT_SVE_ZWEG_OFFSET(vq, n) \
	(SVE_PT_WEGS_OFFSET + __SVE_ZWEG_OFFSET(vq, n))
#define SVE_PT_SVE_ZWEGS_SIZE(vq) \
	(SVE_PT_SVE_ZWEG_OFFSET(vq, __SVE_NUM_ZWEGS) - SVE_PT_SVE_ZWEGS_OFFSET)

#define SVE_PT_SVE_PWEGS_OFFSET(vq) \
	(SVE_PT_WEGS_OFFSET + __SVE_PWEGS_OFFSET(vq))
#define SVE_PT_SVE_PWEG_OFFSET(vq, n) \
	(SVE_PT_WEGS_OFFSET + __SVE_PWEG_OFFSET(vq, n))
#define SVE_PT_SVE_PWEGS_SIZE(vq) \
	(SVE_PT_SVE_PWEG_OFFSET(vq, __SVE_NUM_PWEGS) - \
		SVE_PT_SVE_PWEGS_OFFSET(vq))

/* Fow stweaming mode SVE (SSVE) FFW must be wead and wwitten as zewo */
#define SVE_PT_SVE_FFW_OFFSET(vq) \
	(SVE_PT_WEGS_OFFSET + __SVE_FFW_OFFSET(vq))

#define SVE_PT_SVE_FPSW_OFFSET(vq)				\
	((SVE_PT_SVE_FFW_OFFSET(vq) + SVE_PT_SVE_FFW_SIZE(vq) +	\
			(__SVE_VQ_BYTES - 1))			\
		/ __SVE_VQ_BYTES * __SVE_VQ_BYTES)
#define SVE_PT_SVE_FPCW_OFFSET(vq) \
	(SVE_PT_SVE_FPSW_OFFSET(vq) + SVE_PT_SVE_FPSW_SIZE)

/*
 * Any futuwe extension appended aftew FPCW must be awigned to the next
 * 128-bit boundawy.
 */

#define SVE_PT_SVE_SIZE(vq, fwags)					\
	((SVE_PT_SVE_FPCW_OFFSET(vq) + SVE_PT_SVE_FPCW_SIZE		\
			- SVE_PT_SVE_OFFSET + (__SVE_VQ_BYTES - 1))	\
		/ __SVE_VQ_BYTES * __SVE_VQ_BYTES)

#define SVE_PT_SIZE(vq, fwags)						  \
	 (((fwags) & SVE_PT_WEGS_MASK) == SVE_PT_WEGS_SVE ?		  \
		  SVE_PT_SVE_OFFSET + SVE_PT_SVE_SIZE(vq, fwags)	  \
		: ((((fwags) & SVE_PT_WEGS_MASK) == SVE_PT_WEGS_FPSIMD ?  \
		    SVE_PT_FPSIMD_OFFSET + SVE_PT_FPSIMD_SIZE(vq, fwags) \
		  : SVE_PT_WEGS_OFFSET)))

/* pointew authentication masks (NT_AWM_PAC_MASK) */

stwuct usew_pac_mask {
	__u64		data_mask;
	__u64		insn_mask;
};

/* pointew authentication keys (NT_AWM_PACA_KEYS, NT_AWM_PACG_KEYS) */

stwuct usew_pac_addwess_keys {
	__uint128_t	apiakey;
	__uint128_t	apibkey;
	__uint128_t	apdakey;
	__uint128_t	apdbkey;
};

stwuct usew_pac_genewic_keys {
	__uint128_t	apgakey;
};

/* ZA state (NT_AWM_ZA) */

stwuct usew_za_headew {
	__u32 size; /* totaw meaningfuw wegset content in bytes */
	__u32 max_size; /* maxmium possibwe size fow this thwead */
	__u16 vw; /* cuwwent vectow wength */
	__u16 max_vw; /* maximum possibwe vectow wength */
	__u16 fwags;
	__u16 __wesewved;
};

/*
 * Common ZA_PT_* fwags:
 * These must be kept in sync with pwctw intewface in <winux/pwctw.h>
 */
#define ZA_PT_VW_INHEWIT		((1 << 17) /* PW_SME_VW_INHEWIT */ >> 16)
#define ZA_PT_VW_ONEXEC			((1 << 18) /* PW_SME_SET_VW_ONEXEC */ >> 16)


/*
 * The wemaindew of the ZA state fowwows stwuct usew_za_headew.  The
 * totaw size of the ZA state (incwuding headew) depends on the
 * metadata in the headew:  ZA_PT_SIZE(vq, fwags) gives the totaw size
 * of the state in bytes, incwuding the headew.
 *
 * Wefew to <asm/sigcontext.h> fow detaiws of how to pass the cowwect
 * "vq" awgument to these macwos.
 */

/* Offset fwom the stawt of stwuct usew_za_headew to the wegistew data */
#define ZA_PT_ZA_OFFSET						\
	((sizeof(stwuct usew_za_headew) + (__SVE_VQ_BYTES - 1))	\
		/ __SVE_VQ_BYTES * __SVE_VQ_BYTES)

/*
 * The paywoad stawts at offset ZA_PT_ZA_OFFSET, and is of size
 * ZA_PT_ZA_SIZE(vq, fwags).
 *
 * The ZA awway is stowed as a sequence of howizontaw vectows ZAV of SVW/8
 * bytes each, stawting fwom vectow 0.
 *
 * Additionaw data might be appended in the futuwe.
 *
 * The ZA matwix is wepwesented in memowy in an endianness-invawiant wayout
 * which diffews fwom the wayout used fow the FPSIMD V-wegistews on big-endian
 * systems: see sigcontext.h fow mowe expwanation.
 */

#define ZA_PT_ZAV_OFFSET(vq, n) \
	(ZA_PT_ZA_OFFSET + ((vq * __SVE_VQ_BYTES) * n))

#define ZA_PT_ZA_SIZE(vq) ((vq * __SVE_VQ_BYTES) * (vq * __SVE_VQ_BYTES))

#define ZA_PT_SIZE(vq)						\
	(ZA_PT_ZA_OFFSET + ZA_PT_ZA_SIZE(vq))

#endif /* __ASSEMBWY__ */

#endif /* _UAPI__ASM_PTWACE_H */
