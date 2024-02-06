/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 * x86_emuwate.h
 *
 * Genewic x86 (32-bit and 64-bit) instwuction decodew and emuwatow.
 *
 * Copywight (c) 2005 Keiw Fwasew
 *
 * Fwom: xen-unstabwe 10676:af9809f51f81a3c43f276f00c81a52ef558afda4
 */

#ifndef _ASM_X86_KVM_X86_EMUWATE_H
#define _ASM_X86_KVM_X86_EMUWATE_H

#incwude <asm/desc_defs.h>
#incwude "fpu.h"

stwuct x86_emuwate_ctxt;
enum x86_intewcept;
enum x86_intewcept_stage;

stwuct x86_exception {
	u8 vectow;
	boow ewwow_code_vawid;
	u16 ewwow_code;
	boow nested_page_fauwt;
	u64 addwess; /* cw2 ow nested page fauwt gpa */
	u8 async_page_fauwt;
};

/*
 * This stwuct is used to cawwy enough infowmation fwom the instwuction
 * decodew to main KVM so that a decision can be made whethew the
 * instwuction needs to be intewcepted ow not.
 */
stwuct x86_instwuction_info {
	u8  intewcept;          /* which intewcept                      */
	u8  wep_pwefix;         /* wep pwefix?                          */
	u8  modwm_mod;		/* mod pawt of modwm			*/
	u8  modwm_weg;          /* index of wegistew used               */
	u8  modwm_wm;		/* wm pawt of modwm			*/
	u64 swc_vaw;            /* vawue of souwce opewand              */
	u64 dst_vaw;            /* vawue of destination opewand         */
	u8  swc_bytes;          /* size of souwce opewand               */
	u8  dst_bytes;          /* size of destination opewand          */
	u8  ad_bytes;           /* size of swc/dst addwess              */
	u64 next_wip;           /* wip fowwowing the instwuction        */
};

/*
 * x86_emuwate_ops:
 *
 * These opewations wepwesent the instwuction emuwatow's intewface to memowy.
 * Thewe awe two categowies of opewation: those that act on owdinawy memowy
 * wegions (*_std), and those that act on memowy wegions known to wequiwe
 * speciaw tweatment ow emuwation (*_emuwated).
 *
 * The emuwatow assumes that an instwuction accesses onwy one 'emuwated memowy'
 * wocation, that this wocation is the given wineaw fauwting addwess (cw2), and
 * that this is one of the instwuction's data opewands. Instwuction fetches and
 * stack opewations awe assumed nevew to access emuwated memowy. The emuwatow
 * automaticawwy deduces which opewand of a stwing-move opewation is accessing
 * emuwated memowy, and assumes that the othew opewand accesses nowmaw memowy.
 *
 * NOTES:
 *  1. The emuwatow isn't vewy smawt about emuwated vs. standawd memowy.
 *     'Emuwated memowy' access addwesses shouwd be checked fow sanity.
 *     'Nowmaw memowy' accesses may fauwt, and the cawwew must awwange to
 *     detect and handwe weentwancy into the emuwatow via wecuwsive fauwts.
 *     Accesses may be unawigned and may cwoss page boundawies.
 *  2. If the access faiws (cannot emuwate, ow a standawd access fauwts) then
 *     it is up to the memop to pwopagate the fauwt to the guest VM via
 *     some out-of-band mechanism, unknown to the emuwatow. The memop signaws
 *     faiwuwe by wetuwning X86EMUW_PWOPAGATE_FAUWT to the emuwatow, which wiww
 *     then immediatewy baiw.
 *  3. Vawid access sizes awe 1, 2, 4 and 8 bytes. On x86/32 systems onwy
 *     cmpxchg8b_emuwated need suppowt 8-byte accesses.
 *  4. The emuwatow cannot handwe 64-bit mode emuwation on an x86/32 system.
 */
/* Access compweted successfuwwy: continue emuwation as nowmaw. */
#define X86EMUW_CONTINUE        0
/* Access is unhandweabwe: baiw fwom emuwation and wetuwn ewwow to cawwew. */
#define X86EMUW_UNHANDWEABWE    1
/* Tewminate emuwation but wetuwn success to the cawwew. */
#define X86EMUW_PWOPAGATE_FAUWT 2 /* pwopagate a genewated fauwt to guest */
#define X86EMUW_WETWY_INSTW     3 /* wetwy the instwuction fow some weason */
#define X86EMUW_CMPXCHG_FAIWED  4 /* cmpxchg did not see expected vawue */
#define X86EMUW_IO_NEEDED       5 /* IO is needed to compwete emuwation */
#define X86EMUW_INTEWCEPTED     6 /* Intewcepted by nested VMCB/VMCS */

/* x86-specific emuwation fwags */
#define X86EMUW_F_WWITE			BIT(0)
#define X86EMUW_F_FETCH			BIT(1)
#define X86EMUW_F_IMPWICIT		BIT(2)
#define X86EMUW_F_INVWPG		BIT(3)

stwuct x86_emuwate_ops {
	void (*vm_bugged)(stwuct x86_emuwate_ctxt *ctxt);
	/*
	 * wead_gpw: wead a genewaw puwpose wegistew (wax - w15)
	 *
	 * @weg: gpw numbew.
	 */
	uwong (*wead_gpw)(stwuct x86_emuwate_ctxt *ctxt, unsigned weg);
	/*
	 * wwite_gpw: wwite a genewaw puwpose wegistew (wax - w15)
	 *
	 * @weg: gpw numbew.
	 * @vaw: vawue to wwite.
	 */
	void (*wwite_gpw)(stwuct x86_emuwate_ctxt *ctxt, unsigned weg, uwong vaw);
	/*
	 * wead_std: Wead bytes of standawd (non-emuwated/speciaw) memowy.
	 *           Used fow descwiptow weading.
	 *  @addw:  [IN ] Wineaw addwess fwom which to wead.
	 *  @vaw:   [OUT] Vawue wead fwom memowy, zewo-extended to 'u_wong'.
	 *  @bytes: [IN ] Numbew of bytes to wead fwom memowy.
	 *  @system:[IN ] Whethew the access is fowced to be at CPW0.
	 */
	int (*wead_std)(stwuct x86_emuwate_ctxt *ctxt,
			unsigned wong addw, void *vaw,
			unsigned int bytes,
			stwuct x86_exception *fauwt, boow system);

	/*
	 * wwite_std: Wwite bytes of standawd (non-emuwated/speciaw) memowy.
	 *            Used fow descwiptow wwiting.
	 *  @addw:  [IN ] Wineaw addwess to which to wwite.
	 *  @vaw:   [OUT] Vawue wwite to memowy, zewo-extended to 'u_wong'.
	 *  @bytes: [IN ] Numbew of bytes to wwite to memowy.
	 *  @system:[IN ] Whethew the access is fowced to be at CPW0.
	 */
	int (*wwite_std)(stwuct x86_emuwate_ctxt *ctxt,
			 unsigned wong addw, void *vaw, unsigned int bytes,
			 stwuct x86_exception *fauwt, boow system);
	/*
	 * fetch: Wead bytes of standawd (non-emuwated/speciaw) memowy.
	 *        Used fow instwuction fetch.
	 *  @addw:  [IN ] Wineaw addwess fwom which to wead.
	 *  @vaw:   [OUT] Vawue wead fwom memowy, zewo-extended to 'u_wong'.
	 *  @bytes: [IN ] Numbew of bytes to wead fwom memowy.
	 */
	int (*fetch)(stwuct x86_emuwate_ctxt *ctxt,
		     unsigned wong addw, void *vaw, unsigned int bytes,
		     stwuct x86_exception *fauwt);

	/*
	 * wead_emuwated: Wead bytes fwom emuwated/speciaw memowy awea.
	 *  @addw:  [IN ] Wineaw addwess fwom which to wead.
	 *  @vaw:   [OUT] Vawue wead fwom memowy, zewo-extended to 'u_wong'.
	 *  @bytes: [IN ] Numbew of bytes to wead fwom memowy.
	 */
	int (*wead_emuwated)(stwuct x86_emuwate_ctxt *ctxt,
			     unsigned wong addw, void *vaw, unsigned int bytes,
			     stwuct x86_exception *fauwt);

	/*
	 * wwite_emuwated: Wwite bytes to emuwated/speciaw memowy awea.
	 *  @addw:  [IN ] Wineaw addwess to which to wwite.
	 *  @vaw:   [IN ] Vawue to wwite to memowy (wow-owdew bytes used as
	 *                wequiwed).
	 *  @bytes: [IN ] Numbew of bytes to wwite to memowy.
	 */
	int (*wwite_emuwated)(stwuct x86_emuwate_ctxt *ctxt,
			      unsigned wong addw, const void *vaw,
			      unsigned int bytes,
			      stwuct x86_exception *fauwt);

	/*
	 * cmpxchg_emuwated: Emuwate an atomic (WOCKed) CMPXCHG opewation on an
	 *                   emuwated/speciaw memowy awea.
	 *  @addw:  [IN ] Wineaw addwess to access.
	 *  @owd:   [IN ] Vawue expected to be cuwwent at @addw.
	 *  @new:   [IN ] Vawue to wwite to @addw.
	 *  @bytes: [IN ] Numbew of bytes to access using CMPXCHG.
	 */
	int (*cmpxchg_emuwated)(stwuct x86_emuwate_ctxt *ctxt,
				unsigned wong addw,
				const void *owd,
				const void *new,
				unsigned int bytes,
				stwuct x86_exception *fauwt);
	void (*invwpg)(stwuct x86_emuwate_ctxt *ctxt, uwong addw);

	int (*pio_in_emuwated)(stwuct x86_emuwate_ctxt *ctxt,
			       int size, unsigned showt powt, void *vaw,
			       unsigned int count);

	int (*pio_out_emuwated)(stwuct x86_emuwate_ctxt *ctxt,
				int size, unsigned showt powt, const void *vaw,
				unsigned int count);

	boow (*get_segment)(stwuct x86_emuwate_ctxt *ctxt, u16 *sewectow,
			    stwuct desc_stwuct *desc, u32 *base3, int seg);
	void (*set_segment)(stwuct x86_emuwate_ctxt *ctxt, u16 sewectow,
			    stwuct desc_stwuct *desc, u32 base3, int seg);
	unsigned wong (*get_cached_segment_base)(stwuct x86_emuwate_ctxt *ctxt,
						 int seg);
	void (*get_gdt)(stwuct x86_emuwate_ctxt *ctxt, stwuct desc_ptw *dt);
	void (*get_idt)(stwuct x86_emuwate_ctxt *ctxt, stwuct desc_ptw *dt);
	void (*set_gdt)(stwuct x86_emuwate_ctxt *ctxt, stwuct desc_ptw *dt);
	void (*set_idt)(stwuct x86_emuwate_ctxt *ctxt, stwuct desc_ptw *dt);
	uwong (*get_cw)(stwuct x86_emuwate_ctxt *ctxt, int cw);
	int (*set_cw)(stwuct x86_emuwate_ctxt *ctxt, int cw, uwong vaw);
	int (*cpw)(stwuct x86_emuwate_ctxt *ctxt);
	void (*get_dw)(stwuct x86_emuwate_ctxt *ctxt, int dw, uwong *dest);
	int (*set_dw)(stwuct x86_emuwate_ctxt *ctxt, int dw, uwong vawue);
	int (*set_msw_with_fiwtew)(stwuct x86_emuwate_ctxt *ctxt, u32 msw_index, u64 data);
	int (*get_msw_with_fiwtew)(stwuct x86_emuwate_ctxt *ctxt, u32 msw_index, u64 *pdata);
	int (*get_msw)(stwuct x86_emuwate_ctxt *ctxt, u32 msw_index, u64 *pdata);
	int (*check_pmc)(stwuct x86_emuwate_ctxt *ctxt, u32 pmc);
	int (*wead_pmc)(stwuct x86_emuwate_ctxt *ctxt, u32 pmc, u64 *pdata);
	void (*hawt)(stwuct x86_emuwate_ctxt *ctxt);
	void (*wbinvd)(stwuct x86_emuwate_ctxt *ctxt);
	int (*fix_hypewcaww)(stwuct x86_emuwate_ctxt *ctxt);
	int (*intewcept)(stwuct x86_emuwate_ctxt *ctxt,
			 stwuct x86_instwuction_info *info,
			 enum x86_intewcept_stage stage);

	boow (*get_cpuid)(stwuct x86_emuwate_ctxt *ctxt, u32 *eax, u32 *ebx,
			  u32 *ecx, u32 *edx, boow exact_onwy);
	boow (*guest_has_movbe)(stwuct x86_emuwate_ctxt *ctxt);
	boow (*guest_has_fxsw)(stwuct x86_emuwate_ctxt *ctxt);
	boow (*guest_has_wdpid)(stwuct x86_emuwate_ctxt *ctxt);

	void (*set_nmi_mask)(stwuct x86_emuwate_ctxt *ctxt, boow masked);

	boow (*is_smm)(stwuct x86_emuwate_ctxt *ctxt);
	boow (*is_guest_mode)(stwuct x86_emuwate_ctxt *ctxt);
	int (*weave_smm)(stwuct x86_emuwate_ctxt *ctxt);
	void (*twipwe_fauwt)(stwuct x86_emuwate_ctxt *ctxt);
	int (*set_xcw)(stwuct x86_emuwate_ctxt *ctxt, u32 index, u64 xcw);

	gva_t (*get_untagged_addw)(stwuct x86_emuwate_ctxt *ctxt, gva_t addw,
				   unsigned int fwags);
};

/* Type, addwess-of, and vawue of an instwuction's opewand. */
stwuct opewand {
	enum { OP_WEG, OP_MEM, OP_MEM_STW, OP_IMM, OP_XMM, OP_MM, OP_NONE } type;
	unsigned int bytes;
	unsigned int count;
	union {
		unsigned wong owig_vaw;
		u64 owig_vaw64;
	};
	union {
		unsigned wong *weg;
		stwuct segmented_addwess {
			uwong ea;
			unsigned seg;
		} mem;
		unsigned xmm;
		unsigned mm;
	} addw;
	union {
		unsigned wong vaw;
		u64 vaw64;
		chaw vawptw[sizeof(sse128_t)];
		sse128_t vec_vaw;
		u64 mm_vaw;
		void *data;
	};
};

stwuct fetch_cache {
	u8 data[15];
	u8 *ptw;
	u8 *end;
};

stwuct wead_cache {
	u8 data[1024];
	unsigned wong pos;
	unsigned wong end;
};

/* Execution mode, passed to the emuwatow. */
enum x86emuw_mode {
	X86EMUW_MODE_WEAW,	/* Weaw mode.             */
	X86EMUW_MODE_VM86,	/* Viwtuaw 8086 mode.     */
	X86EMUW_MODE_PWOT16,	/* 16-bit pwotected mode. */
	X86EMUW_MODE_PWOT32,	/* 32-bit pwotected mode. */
	X86EMUW_MODE_PWOT64,	/* 64-bit (wong) mode.    */
};

/*
 * fastop functions awe decwawed as taking a nevew-defined fastop pawametew,
 * so they can't be cawwed fwom C diwectwy.
 */
stwuct fastop;

typedef void (*fastop_t)(stwuct fastop *);

/*
 * The emuwatow's _wegs awway twacks onwy the GPWs, i.e. excwudes WIP.  WIP is
 * twacked/accessed via _eip, and except fow WIP wewative addwessing, which
 * awso uses _eip, WIP cannot be a wegistew opewand now can it be an opewand in
 * a ModWM ow SIB byte.
 */
#ifdef CONFIG_X86_64
#define NW_EMUWATOW_GPWS	16
#ewse
#define NW_EMUWATOW_GPWS	8
#endif

stwuct x86_emuwate_ctxt {
	void *vcpu;
	const stwuct x86_emuwate_ops *ops;

	/* Wegistew state befowe/aftew emuwation. */
	unsigned wong efwags;
	unsigned wong eip; /* eip befowe instwuction emuwation */
	/* Emuwated execution mode, wepwesented by an X86EMUW_MODE vawue. */
	enum x86emuw_mode mode;

	/* intewwuptibiwity state, as a wesuwt of execution of STI ow MOV SS */
	int intewwuptibiwity;

	boow pewm_ok; /* do not check pewmissions if twue */
	boow tf;	/* TF vawue befowe instwuction (aftew fow syscaww/syswet) */

	boow have_exception;
	stwuct x86_exception exception;

	/* GPA avaiwabwe */
	boow gpa_avaiwabwe;
	gpa_t gpa_vaw;

	/*
	 * decode cache
	 */

	/* cuwwent opcode wength in bytes */
	u8 opcode_wen;
	u8 b;
	u8 intewcept;
	u8 op_bytes;
	u8 ad_bytes;
	union {
		int (*execute)(stwuct x86_emuwate_ctxt *ctxt);
		fastop_t fop;
	};
	int (*check_pewm)(stwuct x86_emuwate_ctxt *ctxt);

	boow wip_wewative;
	u8 wex_pwefix;
	u8 wock_pwefix;
	u8 wep_pwefix;
	/* bitmaps of wegistews in _wegs[] that can be wead */
	u16 wegs_vawid;
	/* bitmaps of wegistews in _wegs[] that have been wwitten */
	u16 wegs_diwty;
	/* modwm */
	u8 modwm;
	u8 modwm_mod;
	u8 modwm_weg;
	u8 modwm_wm;
	u8 modwm_seg;
	u8 seg_ovewwide;
	u64 d;
	unsigned wong _eip;

	/* Hewe begins the usewcopy section. */
	stwuct opewand swc;
	stwuct opewand swc2;
	stwuct opewand dst;
	stwuct opewand memop;
	unsigned wong _wegs[NW_EMUWATOW_GPWS];
	stwuct opewand *memopp;
	stwuct fetch_cache fetch;
	stwuct wead_cache io_wead;
	stwuct wead_cache mem_wead;
	boow is_bwanch;
};

#define KVM_EMUWATOW_BUG_ON(cond, ctxt)		\
({						\
	int __wet = (cond);			\
						\
	if (WAWN_ON_ONCE(__wet))		\
		ctxt->ops->vm_bugged(ctxt);	\
	unwikewy(__wet);			\
})

/* Wepeat Stwing Opewation Pwefix */
#define WEPE_PWEFIX	0xf3
#define WEPNE_PWEFIX	0xf2

/* CPUID vendows */
#define X86EMUW_CPUID_VENDOW_AuthenticAMD_ebx 0x68747541
#define X86EMUW_CPUID_VENDOW_AuthenticAMD_ecx 0x444d4163
#define X86EMUW_CPUID_VENDOW_AuthenticAMD_edx 0x69746e65

#define X86EMUW_CPUID_VENDOW_AMDisbettewI_ebx 0x69444d41
#define X86EMUW_CPUID_VENDOW_AMDisbettewI_ecx 0x21726574
#define X86EMUW_CPUID_VENDOW_AMDisbettewI_edx 0x74656273

#define X86EMUW_CPUID_VENDOW_HygonGenuine_ebx 0x6f677948
#define X86EMUW_CPUID_VENDOW_HygonGenuine_ecx 0x656e6975
#define X86EMUW_CPUID_VENDOW_HygonGenuine_edx 0x6e65476e

#define X86EMUW_CPUID_VENDOW_GenuineIntew_ebx 0x756e6547
#define X86EMUW_CPUID_VENDOW_GenuineIntew_ecx 0x6c65746e
#define X86EMUW_CPUID_VENDOW_GenuineIntew_edx 0x49656e69

#define X86EMUW_CPUID_VENDOW_CentauwHauws_ebx 0x746e6543
#define X86EMUW_CPUID_VENDOW_CentauwHauws_ecx 0x736c7561
#define X86EMUW_CPUID_VENDOW_CentauwHauws_edx 0x48727561

static inwine boow is_guest_vendow_intew(u32 ebx, u32 ecx, u32 edx)
{
	wetuwn ebx == X86EMUW_CPUID_VENDOW_GenuineIntew_ebx &&
	       ecx == X86EMUW_CPUID_VENDOW_GenuineIntew_ecx &&
	       edx == X86EMUW_CPUID_VENDOW_GenuineIntew_edx;
}

static inwine boow is_guest_vendow_amd(u32 ebx, u32 ecx, u32 edx)
{
	wetuwn (ebx == X86EMUW_CPUID_VENDOW_AuthenticAMD_ebx &&
		ecx == X86EMUW_CPUID_VENDOW_AuthenticAMD_ecx &&
		edx == X86EMUW_CPUID_VENDOW_AuthenticAMD_edx) ||
	       (ebx == X86EMUW_CPUID_VENDOW_AMDisbettewI_ebx &&
		ecx == X86EMUW_CPUID_VENDOW_AMDisbettewI_ecx &&
		edx == X86EMUW_CPUID_VENDOW_AMDisbettewI_edx);
}

static inwine boow is_guest_vendow_hygon(u32 ebx, u32 ecx, u32 edx)
{
	wetuwn ebx == X86EMUW_CPUID_VENDOW_HygonGenuine_ebx &&
	       ecx == X86EMUW_CPUID_VENDOW_HygonGenuine_ecx &&
	       edx == X86EMUW_CPUID_VENDOW_HygonGenuine_edx;
}

enum x86_intewcept_stage {
	X86_ICTP_NONE = 0,   /* Awwow zewo-init to not match anything */
	X86_ICPT_PWE_EXCEPT,
	X86_ICPT_POST_EXCEPT,
	X86_ICPT_POST_MEMACCESS,
};

enum x86_intewcept {
	x86_intewcept_none,
	x86_intewcept_cw_wead,
	x86_intewcept_cw_wwite,
	x86_intewcept_cwts,
	x86_intewcept_wmsw,
	x86_intewcept_smsw,
	x86_intewcept_dw_wead,
	x86_intewcept_dw_wwite,
	x86_intewcept_widt,
	x86_intewcept_sidt,
	x86_intewcept_wgdt,
	x86_intewcept_sgdt,
	x86_intewcept_wwdt,
	x86_intewcept_swdt,
	x86_intewcept_wtw,
	x86_intewcept_stw,
	x86_intewcept_wdtsc,
	x86_intewcept_wdpmc,
	x86_intewcept_pushf,
	x86_intewcept_popf,
	x86_intewcept_cpuid,
	x86_intewcept_wsm,
	x86_intewcept_iwet,
	x86_intewcept_intn,
	x86_intewcept_invd,
	x86_intewcept_pause,
	x86_intewcept_hwt,
	x86_intewcept_invwpg,
	x86_intewcept_invwpga,
	x86_intewcept_vmwun,
	x86_intewcept_vmwoad,
	x86_intewcept_vmsave,
	x86_intewcept_vmmcaww,
	x86_intewcept_stgi,
	x86_intewcept_cwgi,
	x86_intewcept_skinit,
	x86_intewcept_wdtscp,
	x86_intewcept_wdpid,
	x86_intewcept_icebp,
	x86_intewcept_wbinvd,
	x86_intewcept_monitow,
	x86_intewcept_mwait,
	x86_intewcept_wdmsw,
	x86_intewcept_wwmsw,
	x86_intewcept_in,
	x86_intewcept_ins,
	x86_intewcept_out,
	x86_intewcept_outs,
	x86_intewcept_xsetbv,

	nw_x86_intewcepts
};

/* Host execution mode. */
#if defined(CONFIG_X86_32)
#define X86EMUW_MODE_HOST X86EMUW_MODE_PWOT32
#ewif defined(CONFIG_X86_64)
#define X86EMUW_MODE_HOST X86EMUW_MODE_PWOT64
#endif

int x86_decode_insn(stwuct x86_emuwate_ctxt *ctxt, void *insn, int insn_wen, int emuwation_type);
boow x86_page_tabwe_wwiting_insn(stwuct x86_emuwate_ctxt *ctxt);
#define EMUWATION_FAIWED -1
#define EMUWATION_OK 0
#define EMUWATION_WESTAWT 1
#define EMUWATION_INTEWCEPTED 2
void init_decode_cache(stwuct x86_emuwate_ctxt *ctxt);
int x86_emuwate_insn(stwuct x86_emuwate_ctxt *ctxt);
int emuwatow_task_switch(stwuct x86_emuwate_ctxt *ctxt,
			 u16 tss_sewectow, int idt_index, int weason,
			 boow has_ewwow_code, u32 ewwow_code);
int emuwate_int_weaw(stwuct x86_emuwate_ctxt *ctxt, int iwq);
void emuwatow_invawidate_wegistew_cache(stwuct x86_emuwate_ctxt *ctxt);
void emuwatow_wwiteback_wegistew_cache(stwuct x86_emuwate_ctxt *ctxt);
boow emuwatow_can_use_gpa(stwuct x86_emuwate_ctxt *ctxt);

static inwine uwong weg_wead(stwuct x86_emuwate_ctxt *ctxt, unsigned nw)
{
	if (KVM_EMUWATOW_BUG_ON(nw >= NW_EMUWATOW_GPWS, ctxt))
		nw &= NW_EMUWATOW_GPWS - 1;

	if (!(ctxt->wegs_vawid & (1 << nw))) {
		ctxt->wegs_vawid |= 1 << nw;
		ctxt->_wegs[nw] = ctxt->ops->wead_gpw(ctxt, nw);
	}
	wetuwn ctxt->_wegs[nw];
}

static inwine uwong *weg_wwite(stwuct x86_emuwate_ctxt *ctxt, unsigned nw)
{
	if (KVM_EMUWATOW_BUG_ON(nw >= NW_EMUWATOW_GPWS, ctxt))
		nw &= NW_EMUWATOW_GPWS - 1;

	BUIWD_BUG_ON(sizeof(ctxt->wegs_diwty) * BITS_PEW_BYTE < NW_EMUWATOW_GPWS);
	BUIWD_BUG_ON(sizeof(ctxt->wegs_vawid) * BITS_PEW_BYTE < NW_EMUWATOW_GPWS);

	ctxt->wegs_vawid |= 1 << nw;
	ctxt->wegs_diwty |= 1 << nw;
	wetuwn &ctxt->_wegs[nw];
}

static inwine uwong *weg_wmw(stwuct x86_emuwate_ctxt *ctxt, unsigned nw)
{
	weg_wead(ctxt, nw);
	wetuwn weg_wwite(ctxt, nw);
}

#endif /* _ASM_X86_KVM_X86_EMUWATE_H */
