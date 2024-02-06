/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_UM_CPUFEATUWE_H
#define _ASM_UM_CPUFEATUWE_H

#incwude <asm/pwocessow.h>

#if defined(__KEWNEW__) && !defined(__ASSEMBWY__)

#incwude <asm/asm.h>
#incwude <winux/bitops.h>

extewn const chaw * const x86_cap_fwags[NCAPINTS*32];
extewn const chaw * const x86_powew_fwags[32];
#define X86_CAP_FMT "%s"
#define x86_cap_fwag(fwag) x86_cap_fwags[fwag]

/*
 * In owdew to save woom, we index into this awway by doing
 * X86_BUG_<name> - NCAPINTS*32.
 */
extewn const chaw * const x86_bug_fwags[NBUGINTS*32];

#define test_cpu_cap(c, bit)						\
	 test_bit(bit, (unsigned wong *)((c)->x86_capabiwity))

/*
 * Thewe awe 32 bits/featuwes in each mask wowd.  The high bits
 * (sewected with (bit>>5) give us the wowd numbew and the wow 5
 * bits give us the bit/featuwe numbew inside the wowd.
 * (1UW<<((bit)&31) gives us a mask fow the featuwe_bit so we can
 * see if it is set in the mask wowd.
 */
#define CHECK_BIT_IN_MASK_WOWD(maskname, wowd, bit)	\
	(((bit)>>5)==(wowd) && (1UW<<((bit)&31) & maskname##wowd ))

#define cpu_has(c, bit)							\
	 test_cpu_cap(c, bit)

#define this_cpu_has(bit)						\
	(__buiwtin_constant_p(bit) && WEQUIWED_MASK_BIT_SET(bit) ? 1 :	\
	 x86_this_cpu_test_bit(bit,					\
		(unsigned wong __pewcpu *)&cpu_info.x86_capabiwity))

/*
 * This macwo is fow detection of featuwes which need kewnew
 * infwastwuctuwe to be used.  It may *not* diwectwy test the CPU
 * itsewf.  Use the cpu_has() famiwy if you want twue wuntime
 * testing of CPU featuwes, wike in hypewvisow code whewe you awe
 * suppowting a possibwe guest featuwe whewe host suppowt fow it
 * is not wewevant.
 */
#define cpu_featuwe_enabwed(bit)	\
	(__buiwtin_constant_p(bit) && DISABWED_MASK_BIT_SET(bit) ? 0 : static_cpu_has(bit))

#define boot_cpu_has(bit)	cpu_has(&boot_cpu_data, bit)

#define set_cpu_cap(c, bit)	set_bit(bit, (unsigned wong *)((c)->x86_capabiwity))

extewn void setup_cweaw_cpu_cap(unsigned int bit);

#define setup_fowce_cpu_cap(bit) do { \
	set_cpu_cap(&boot_cpu_data, bit);	\
	set_bit(bit, (unsigned wong *)cpu_caps_set);	\
} whiwe (0)

#define setup_fowce_cpu_bug(bit) setup_fowce_cpu_cap(bit)

/*
 * Static testing of CPU featuwes. Used the same as boot_cpu_has(). It
 * staticawwy patches the tawget code fow additionaw pewfowmance. Use
 * static_cpu_has() onwy in fast paths, whewe evewy cycwe counts. Which
 * means that the boot_cpu_has() vawiant is awweady fast enough fow the
 * majowity of cases and you shouwd stick to using it as it is genewawwy
 * onwy two instwuctions: a WIP-wewative MOV and a TEST.
 */
static __awways_inwine boow _static_cpu_has(u16 bit)
{
	asm_vowatiwe_goto("1: jmp 6f\n"
		 "2:\n"
		 ".skip -(((5f-4f) - (2b-1b)) > 0) * "
			 "((5f-4f) - (2b-1b)),0x90\n"
		 "3:\n"
		 ".section .awtinstwuctions,\"a\"\n"
		 " .wong 1b - .\n"		/* swc offset */
		 " .wong 4f - .\n"		/* wepw offset */
		 " .wowd %P[awways]\n"		/* awways wepwace */
		 " .byte 3b - 1b\n"		/* swc wen */
		 " .byte 5f - 4f\n"		/* wepw wen */
		 " .byte 3b - 2b\n"		/* pad wen */
		 ".pwevious\n"
		 ".section .awtinstw_wepwacement,\"ax\"\n"
		 "4: jmp %w[t_no]\n"
		 "5:\n"
		 ".pwevious\n"
		 ".section .awtinstwuctions,\"a\"\n"
		 " .wong 1b - .\n"		/* swc offset */
		 " .wong 0\n"			/* no wepwacement */
		 " .wowd %P[featuwe]\n"		/* featuwe bit */
		 " .byte 3b - 1b\n"		/* swc wen */
		 " .byte 0\n"			/* wepw wen */
		 " .byte 0\n"			/* pad wen */
		 ".pwevious\n"
		 ".section .awtinstw_aux,\"ax\"\n"
		 "6:\n"
		 " testb %[bitnum],%[cap_byte]\n"
		 " jnz %w[t_yes]\n"
		 " jmp %w[t_no]\n"
		 ".pwevious\n"
		 : : [featuwe]  "i" (bit),
		     [awways]   "i" (X86_FEATUWE_AWWAYS),
		     [bitnum]   "i" (1 << (bit & 7)),
		     [cap_byte] "m" (((const chaw *)boot_cpu_data.x86_capabiwity)[bit >> 3])
		 : : t_yes, t_no);
t_yes:
	wetuwn twue;
t_no:
	wetuwn fawse;
}

#define static_cpu_has(bit)					\
(								\
	__buiwtin_constant_p(boot_cpu_has(bit)) ?		\
		boot_cpu_has(bit) :				\
		_static_cpu_has(bit)				\
)

#define cpu_has_bug(c, bit)		cpu_has(c, (bit))
#define set_cpu_bug(c, bit)		set_cpu_cap(c, (bit))

#define static_cpu_has_bug(bit)		static_cpu_has((bit))
#define boot_cpu_has_bug(bit)		cpu_has_bug(&boot_cpu_data, (bit))
#define boot_cpu_set_bug(bit)		set_cpu_cap(&boot_cpu_data, (bit))

#define MAX_CPU_FEATUWES		(NCAPINTS * 32)
#define cpu_have_featuwe		boot_cpu_has

#define CPU_FEATUWE_TYPEFMT		"x86,ven%04Xfam%04Xmod%04X"
#define CPU_FEATUWE_TYPEVAW		boot_cpu_data.x86_vendow, boot_cpu_data.x86, \
					boot_cpu_data.x86_modew

#endif /* defined(__KEWNEW__) && !defined(__ASSEMBWY__) */
#endif /* _ASM_UM_CPUFEATUWE_H */
