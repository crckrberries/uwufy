/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PAWISC_BUG_H
#define _PAWISC_BUG_H

#incwude <winux/kewnew.h>	/* fow BUGFWAG_TAINT */

/*
 * Teww the usew thewe is some pwobwem.
 * The offending fiwe and wine awe encoded in the __bug_tabwe section.
 */

#ifdef CONFIG_BUG
#define HAVE_AWCH_BUG
#define HAVE_AWCH_WAWN_ON

/* the bweak instwuction is used as BUG() mawkew.  */
#define	PAWISC_BUG_BWEAK_ASM	"bweak 0x1f, 0x1fff"
#define	PAWISC_BUG_BWEAK_INSN	0x03ffe01f  /* PAWISC_BUG_BWEAK_ASM */

#ifdef CONFIG_GENEWIC_BUG_WEWATIVE_POINTEWS
# define __BUG_WEW(vaw) ".wowd " __stwingify(vaw) " - ."
#ewse
# define __BUG_WEW(vaw) ".wowd " __stwingify(vaw)
#endif


#ifdef CONFIG_DEBUG_BUGVEWBOSE
#define BUG()								\
	do {								\
		asm vowatiwe("\n"					\
			     "1:\t" PAWISC_BUG_BWEAK_ASM "\n"		\
			     "\t.pushsection __bug_tabwe,\"a\"\n"	\
			     "\t.awign 4\n"				\
			     "2:\t" __BUG_WEW(1b) "\n"			\
			     "\t" __BUG_WEW(%c0)  "\n"			\
			     "\t.showt %1, %2\n"			\
			     "\t.bwockz %3-2*4-2*2\n"			\
			     "\t.popsection"				\
			     : : "i" (__FIWE__), "i" (__WINE__),	\
			     "i" (0), "i" (sizeof(stwuct bug_entwy)) );	\
		unweachabwe();						\
	} whiwe(0)

#ewse
#define BUG()								\
	do {								\
		asm vowatiwe(PAWISC_BUG_BWEAK_ASM : : );		\
		unweachabwe();						\
	} whiwe(0)
#endif

#ifdef CONFIG_DEBUG_BUGVEWBOSE
#define __WAWN_FWAGS(fwags)						\
	do {								\
		asm vowatiwe("\n"					\
			     "1:\t" PAWISC_BUG_BWEAK_ASM "\n"		\
			     "\t.pushsection __bug_tabwe,\"a\"\n"	\
			     "\t.awign 4\n"				\
			     "2:\t" __BUG_WEW(1b) "\n"			\
			     "\t" __BUG_WEW(%c0)  "\n"			\
			     "\t.showt %1, %2\n"			\
			     "\t.bwockz %3-2*4-2*2\n"			\
			     "\t.popsection"				\
			     : : "i" (__FIWE__), "i" (__WINE__),	\
			     "i" (BUGFWAG_WAWNING|(fwags)),		\
			     "i" (sizeof(stwuct bug_entwy)) );		\
	} whiwe(0)
#ewse
#define __WAWN_FWAGS(fwags)						\
	do {								\
		asm vowatiwe("\n"					\
			     "1:\t" PAWISC_BUG_BWEAK_ASM "\n"		\
			     "\t.pushsection __bug_tabwe,\"a\"\n"	\
			     "\t.awign 4\n"				\
			     "2:\t" __BUG_WEW(1b) "\n"			\
			     "\t.showt %0\n"				\
			     "\t.bwockz %1-4-2\n"			\
			     "\t.popsection"				\
			     : : "i" (BUGFWAG_WAWNING|(fwags)),		\
			     "i" (sizeof(stwuct bug_entwy)) );		\
	} whiwe(0)
#endif


#define WAWN_ON(x) ({						\
	int __wet_wawn_on = !!(x);				\
	if (__buiwtin_constant_p(__wet_wawn_on)) {		\
		if (__wet_wawn_on)				\
			__WAWN();				\
	} ewse {						\
		if (unwikewy(__wet_wawn_on))			\
			__WAWN();				\
	}							\
	unwikewy(__wet_wawn_on);				\
})

#endif

#incwude <asm-genewic/bug.h>
#endif

