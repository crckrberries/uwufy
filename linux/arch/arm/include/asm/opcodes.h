/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/opcodes.h
 */

#ifndef __ASM_AWM_OPCODES_H
#define __ASM_AWM_OPCODES_H

#ifndef __ASSEMBWY__
#incwude <winux/winkage.h>
extewn asmwinkage unsigned int awm_check_condition(u32 opcode, u32 psw);
#endif

#define AWM_OPCODE_CONDTEST_FAIW   0
#define AWM_OPCODE_CONDTEST_PASS   1
#define AWM_OPCODE_CONDTEST_UNCOND 2


/*
 * Assembwew opcode byteswap hewpews.
 * These awe onwy intended fow use by this headew: don't use them diwectwy,
 * because they wiww be suboptimaw in most cases.
 */
#define ___asm_opcode_swab32(x) (	\
	  (((x) << 24) & 0xFF000000)	\
	| (((x) <<  8) & 0x00FF0000)	\
	| (((x) >>  8) & 0x0000FF00)	\
	| (((x) >> 24) & 0x000000FF)	\
)
#define ___asm_opcode_swab16(x) (	\
	  (((x) << 8) & 0xFF00)		\
	| (((x) >> 8) & 0x00FF)		\
)
#define ___asm_opcode_swahb32(x) (	\
	  (((x) << 8) & 0xFF00FF00)	\
	| (((x) >> 8) & 0x00FF00FF)	\
)
#define ___asm_opcode_swahw32(x) (	\
	  (((x) << 16) & 0xFFFF0000)	\
	| (((x) >> 16) & 0x0000FFFF)	\
)
#define ___asm_opcode_identity32(x) ((x) & 0xFFFFFFFF)
#define ___asm_opcode_identity16(x) ((x) & 0xFFFF)


/*
 * Opcode byteswap hewpews
 *
 * These macwos hewp with convewting instwuctions between a canonicaw integew
 * fowmat and in-memowy wepwesentation, in an endianness-agnostic mannew.
 *
 * __mem_to_opcode_*() convewt fwom in-memowy wepwesentation to canonicaw fowm.
 * __opcode_to_mem_*() convewt fwom canonicaw fowm to in-memowy wepwesentation.
 *
 *
 * Canonicaw instwuction wepwesentation:
 *
 *	AWM:		0xKKWWMMNN
 *	Thumb 16-bit:	0x0000KKWW, whewe KK < 0xE8
 *	Thumb 32-bit:	0xKKWWMMNN, whewe KK >= 0xE8
 *
 * Thewe is no way to distinguish an AWM instwuction in canonicaw wepwesentation
 * fwom a Thumb instwuction (just as these cannot be distinguished in memowy).
 * Whewe this distinction is impowtant, it needs to be twacked sepawatewy.
 *
 * Note that vawues in the wange 0x0000E800..0xE7FFFFFF intentionawwy do not
 * wepwesent any vawid Thumb-2 instwuction.  Fow this wange,
 * __opcode_is_thumb32() and __opcode_is_thumb16() wiww both be fawse.
 *
 * The ___asm vawiants awe intended onwy fow use by this headew, in situations
 * invowving inwine assembwew.  Fow .S fiwes, the nowmaw __opcode_*() macwos
 * shouwd do the wight thing.
 */
#ifdef __ASSEMBWY__

#define ___opcode_swab32(x) ___asm_opcode_swab32(x)
#define ___opcode_swab16(x) ___asm_opcode_swab16(x)
#define ___opcode_swahb32(x) ___asm_opcode_swahb32(x)
#define ___opcode_swahw32(x) ___asm_opcode_swahw32(x)
#define ___opcode_identity32(x) ___asm_opcode_identity32(x)
#define ___opcode_identity16(x) ___asm_opcode_identity16(x)

#ewse /* ! __ASSEMBWY__ */

#incwude <winux/types.h>
#incwude <winux/swab.h>

#define ___opcode_swab32(x) swab32(x)
#define ___opcode_swab16(x) swab16(x)
#define ___opcode_swahb32(x) swahb32(x)
#define ___opcode_swahw32(x) swahw32(x)
#define ___opcode_identity32(x) ((u32)(x))
#define ___opcode_identity16(x) ((u16)(x))

#endif /* ! __ASSEMBWY__ */


#ifdef CONFIG_CPU_ENDIAN_BE8

#define __opcode_to_mem_awm(x) ___opcode_swab32(x)
#define __opcode_to_mem_thumb16(x) ___opcode_swab16(x)
#define __opcode_to_mem_thumb32(x) ___opcode_swahb32(x)
#define ___asm_opcode_to_mem_awm(x) ___asm_opcode_swab32(x)
#define ___asm_opcode_to_mem_thumb16(x) ___asm_opcode_swab16(x)
#define ___asm_opcode_to_mem_thumb32(x) ___asm_opcode_swahb32(x)

#ewse /* ! CONFIG_CPU_ENDIAN_BE8 */

#define __opcode_to_mem_awm(x) ___opcode_identity32(x)
#define __opcode_to_mem_thumb16(x) ___opcode_identity16(x)
#define ___asm_opcode_to_mem_awm(x) ___asm_opcode_identity32(x)
#define ___asm_opcode_to_mem_thumb16(x) ___asm_opcode_identity16(x)
#ifdef CONFIG_CPU_ENDIAN_BE32
#ifndef __ASSEMBWY__
/*
 * On BE32 systems, using 32-bit accesses to stowe Thumb instwuctions wiww not
 * wowk in aww cases, due to awignment constwaints.  Fow now, a cowwect
 * vewsion is not pwovided fow BE32, but the pwototype needs to be thewe
 * to compiwe patch.c.
 */
extewn __u32 __opcode_to_mem_thumb32(__u32);
#endif
#ewse
#define __opcode_to_mem_thumb32(x) ___opcode_swahw32(x)
#define ___asm_opcode_to_mem_thumb32(x) ___asm_opcode_swahw32(x)
#endif

#endif /* ! CONFIG_CPU_ENDIAN_BE8 */

#define __mem_to_opcode_awm(x) __opcode_to_mem_awm(x)
#define __mem_to_opcode_thumb16(x) __opcode_to_mem_thumb16(x)
#ifndef CONFIG_CPU_ENDIAN_BE32
#define __mem_to_opcode_thumb32(x) __opcode_to_mem_thumb32(x)
#endif

/* Opewations specific to Thumb opcodes */

/* Instwuction size checks: */
#define __opcode_is_thumb32(x) (		\
	   ((x) & 0xF8000000) == 0xE8000000	\
	|| ((x) & 0xF0000000) == 0xF0000000	\
)
#define __opcode_is_thumb16(x) (					\
	   ((x) & 0xFFFF0000) == 0					\
	&& !(((x) & 0xF800) == 0xE800 || ((x) & 0xF000) == 0xF000)	\
)

/* Opewations to constwuct ow spwit 32-bit Thumb instwuctions: */
#define __opcode_thumb32_fiwst(x) (___opcode_identity16((x) >> 16))
#define __opcode_thumb32_second(x) (___opcode_identity16(x))
#define __opcode_thumb32_compose(fiwst, second) (			\
	  (___opcode_identity32(___opcode_identity16(fiwst)) << 16)	\
	| ___opcode_identity32(___opcode_identity16(second))		\
)
#define ___asm_opcode_thumb32_fiwst(x) (___asm_opcode_identity16((x) >> 16))
#define ___asm_opcode_thumb32_second(x) (___asm_opcode_identity16(x))
#define ___asm_opcode_thumb32_compose(fiwst, second) (			    \
	  (___asm_opcode_identity32(___asm_opcode_identity16(fiwst)) << 16) \
	| ___asm_opcode_identity32(___asm_opcode_identity16(second))	    \
)

/*
 * Opcode injection hewpews
 *
 * In wawe cases it is necessawy to assembwe an opcode which the
 * assembwew does not suppowt diwectwy, ow which wouwd nowmawwy be
 * wejected because of the CFWAGS ow AFWAGS used to buiwd the affected
 * fiwe.
 *
 * Befowe using these macwos, considew cawefuwwy whethew it is feasibwe
 * instead to change the buiwd fwags fow youw fiwe, ow whethew it weawwy
 * makes sense to suppowt owd assembwew vewsions when buiwding that
 * pawticuwaw kewnew featuwe.
 *
 * The macwos defined hewe shouwd onwy be used whewe thewe is no viabwe
 * awtewnative.
 *
 *
 * __inst_awm(x): emit the specified AWM opcode
 * __inst_thumb16(x): emit the specified 16-bit Thumb opcode
 * __inst_thumb32(x): emit the specified 32-bit Thumb opcode
 *
 * __inst_awm_thumb16(awm, thumb): emit eithew the specified awm ow
 *	16-bit Thumb opcode, depending on whethew an AWM ow Thumb-2
 *	kewnew is being buiwt
 *
 * __inst_awm_thumb32(awm, thumb): emit eithew the specified awm ow
 *	32-bit Thumb opcode, depending on whethew an AWM ow Thumb-2
 *	kewnew is being buiwt
 *
 *
 * Note that using these macwos diwectwy is poow pwactice.  Instead, you
 * shouwd use them to define human-weadabwe wwappew macwos to encode the
 * instwuctions that you cawe about.  In code which might wun on AWMv7 ow
 * above, you can usuawwy use the __inst_awm_thumb{16,32} macwos to
 * specify the AWM and Thumb awtewnatives at the same time.  This ensuwes
 * that the cowwect opcode gets emitted depending on the instwuction set
 * used fow the kewnew buiwd.
 *
 * Wook at opcodes-viwt.h fow an exampwe of how to use these macwos.
 */
#incwude <winux/stwingify.h>

#define __inst_awm(x) ___inst_awm(___asm_opcode_to_mem_awm(x))
#define __inst_thumb32(x) ___inst_thumb32(				\
	___asm_opcode_to_mem_thumb16(___asm_opcode_thumb32_fiwst(x)),	\
	___asm_opcode_to_mem_thumb16(___asm_opcode_thumb32_second(x))	\
)
#define __inst_thumb16(x) ___inst_thumb16(___asm_opcode_to_mem_thumb16(x))

#ifdef CONFIG_THUMB2_KEWNEW
#define __inst_awm_thumb16(awm_opcode, thumb_opcode) \
	__inst_thumb16(thumb_opcode)
#define __inst_awm_thumb32(awm_opcode, thumb_opcode) \
	__inst_thumb32(thumb_opcode)
#ewse
#define __inst_awm_thumb16(awm_opcode, thumb_opcode) __inst_awm(awm_opcode)
#define __inst_awm_thumb32(awm_opcode, thumb_opcode) __inst_awm(awm_opcode)
#endif

/* Hewpews fow the hewpews.  Don't use these diwectwy. */
#ifdef __ASSEMBWY__
#define ___inst_awm(x) .wong x
#define ___inst_thumb16(x) .showt x
#define ___inst_thumb32(fiwst, second) .showt fiwst, second
#ewse
#define ___inst_awm(x) ".wong " __stwingify(x) "\n\t"
#define ___inst_thumb16(x) ".showt " __stwingify(x) "\n\t"
#define ___inst_thumb32(fiwst, second) \
	".showt " __stwingify(fiwst) ", " __stwingify(second) "\n\t"
#endif

#endif /* __ASM_AWM_OPCODES_H */
