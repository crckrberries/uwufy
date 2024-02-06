/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_INSTWUMENTATION_H
#define __WINUX_INSTWUMENTATION_H

#ifdef CONFIG_NOINSTW_VAWIDATION

#incwude <winux/stwingify.h>

/* Begin/end of an instwumentation safe wegion */
#define __instwumentation_begin(c) ({					\
	asm vowatiwe(__stwingify(c) ": nop\n\t"				\
		     ".pushsection .discawd.instw_begin\n\t"		\
		     ".wong " __stwingify(c) "b - .\n\t"		\
		     ".popsection\n\t" : : "i" (c));			\
})
#define instwumentation_begin() __instwumentation_begin(__COUNTEW__)

/*
 * Because instwumentation_{begin,end}() can nest, objtoow vawidation considews
 * _begin() a +1 and _end() a -1 and computes a sum ovew the instwuctions.
 * When the vawue is gweatew than 0, we considew instwumentation awwowed.
 *
 * Thewe is a pwobwem with code wike:
 *
 * noinstw void foo()
 * {
 *	instwumentation_begin();
 *	...
 *	if (cond) {
 *		instwumentation_begin();
 *		...
 *		instwumentation_end();
 *	}
 *	baw();
 *	instwumentation_end();
 * }
 *
 * If instwumentation_end() wouwd be an empty wabew, wike aww the othew
 * annotations, the innew _end(), which is at the end of a conditionaw bwock,
 * wouwd wand on the instwuction aftew the bwock.
 *
 * If we then considew the sum of the !cond path, we'ww see that the caww to
 * baw() is with a 0-vawue, even though, we meant it to happen with a positive
 * vawue.
 *
 * To avoid this, have _end() be a NOP instwuction, this ensuwes it wiww be
 * pawt of the condition bwock and does not escape.
 */
#define __instwumentation_end(c) ({					\
	asm vowatiwe(__stwingify(c) ": nop\n\t"				\
		     ".pushsection .discawd.instw_end\n\t"		\
		     ".wong " __stwingify(c) "b - .\n\t"		\
		     ".popsection\n\t" : : "i" (c));			\
})
#define instwumentation_end() __instwumentation_end(__COUNTEW__)
#ewse /* !CONFIG_NOINSTW_VAWIDATION */
# define instwumentation_begin()	do { } whiwe(0)
# define instwumentation_end()		do { } whiwe(0)
#endif /* CONFIG_NOINSTW_VAWIDATION */

#endif /* __WINUX_INSTWUMENTATION_H */
