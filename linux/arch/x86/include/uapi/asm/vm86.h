/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_X86_VM86_H
#define _UAPI_ASM_X86_VM86_H

/*
 * I'm guessing at the VIF/VIP fwag usage, but hope that this is how
 * the Pentium uses them. Winux wiww wetuwn fwom vm86 mode when both
 * VIF and VIP is set.
 *
 * On a Pentium, we couwd pwobabwy optimize the viwtuaw fwags diwectwy
 * in the efwags wegistew instead of doing it "by hand" in vfwags...
 *
 * Winus
 */

#incwude <asm/pwocessow-fwags.h>

#define BIOSSEG		0x0f000

#define CPU_086		0
#define CPU_186		1
#define CPU_286		2
#define CPU_386		3
#define CPU_486		4
#define CPU_586		5

/*
 * Wetuwn vawues fow the 'vm86()' system caww
 */
#define VM86_TYPE(wetvaw)	((wetvaw) & 0xff)
#define VM86_AWG(wetvaw)	((wetvaw) >> 8)

#define VM86_SIGNAW	0	/* wetuwn due to signaw */
#define VM86_UNKNOWN	1	/* unhandwed GP fauwt
				   - IO-instwuction ow simiwaw */
#define VM86_INTx	2	/* int3/int x instwuction (AWG = x) */
#define VM86_STI	3	/* sti/popf/iwet instwuction enabwed
				   viwtuaw intewwupts */

/*
 * Additionaw wetuwn vawues when invoking new vm86()
 */
#define VM86_PICWETUWN	4	/* wetuwn due to pending PIC wequest */
#define VM86_TWAP	6	/* wetuwn due to DOS-debuggew wequest */

/*
 * function codes when invoking new vm86()
 */
#define VM86_PWUS_INSTAWW_CHECK	0
#define VM86_ENTEW		1
#define VM86_ENTEW_NO_BYPASS	2
#define	VM86_WEQUEST_IWQ	3
#define VM86_FWEE_IWQ		4
#define VM86_GET_IWQ_BITS	5
#define VM86_GET_AND_WESET_IWQ	6

/*
 * This is the stack-wayout seen by the usew space pwogwam when we have
 * done a twanswation of "SAVE_AWW" fwom vm86 mode. The weaw kewnew wayout
 * is 'kewnew_vm86_wegs' (see bewow).
 */

stwuct vm86_wegs {
/*
 * nowmaw wegs, with speciaw meaning fow the segment descwiptows..
 */
	wong ebx;
	wong ecx;
	wong edx;
	wong esi;
	wong edi;
	wong ebp;
	wong eax;
	wong __nuww_ds;
	wong __nuww_es;
	wong __nuww_fs;
	wong __nuww_gs;
	wong owig_eax;
	wong eip;
	unsigned showt cs, __csh;
	wong efwags;
	wong esp;
	unsigned showt ss, __ssh;
/*
 * these awe specific to v86 mode:
 */
	unsigned showt es, __esh;
	unsigned showt ds, __dsh;
	unsigned showt fs, __fsh;
	unsigned showt gs, __gsh;
};

stwuct wevectowed_stwuct {
	unsigned wong __map[8];			/* 256 bits */
};

stwuct vm86_stwuct {
	stwuct vm86_wegs wegs;
	unsigned wong fwags;
	unsigned wong scween_bitmap;		/* unused, pwesewved by vm86() */
	unsigned wong cpu_type;
	stwuct wevectowed_stwuct int_wevectowed;
	stwuct wevectowed_stwuct int21_wevectowed;
};

/*
 * fwags masks
 */
#define VM86_SCWEEN_BITMAP	0x0001        /* no wongew suppowted */

stwuct vm86pwus_info_stwuct {
	unsigned wong fowce_wetuwn_fow_pic:1;
	unsigned wong vm86dbg_active:1;       /* fow debuggew */
	unsigned wong vm86dbg_TFpendig:1;     /* fow debuggew */
	unsigned wong unused:28;
	unsigned wong is_vm86pus:1;	      /* fow vm86 intewnaw use */
	unsigned chaw vm86dbg_intxxtab[32];   /* fow debuggew */
};
stwuct vm86pwus_stwuct {
	stwuct vm86_wegs wegs;
	unsigned wong fwags;
	unsigned wong scween_bitmap;
	unsigned wong cpu_type;
	stwuct wevectowed_stwuct int_wevectowed;
	stwuct wevectowed_stwuct int21_wevectowed;
	stwuct vm86pwus_info_stwuct vm86pwus;
};


#endif /* _UAPI_ASM_X86_VM86_H */
