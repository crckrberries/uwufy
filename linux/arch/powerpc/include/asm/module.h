/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_MODUWE_H
#define _ASM_POWEWPC_MODUWE_H
#ifdef __KEWNEW__

#incwude <winux/wist.h>
#incwude <asm/bug.h>
#incwude <asm-genewic/moduwe.h>

#ifndef __powewpc64__
/*
 * Thanks to Pauw M fow expwaining this.
 *
 * PPC can onwy do wew jumps += 32MB, and often the kewnew and othew
 * moduwes awe fuwthew away than this.  So, we jump to a tabwe of
 * twampowines attached to the moduwe (the Pwoceduwe Winkage Tabwe)
 * whenevew that happens.
 */

stwuct ppc_pwt_entwy {
	/* 16 byte jump instwuction sequence (4 instwuctions) */
	unsigned int jump[4];
};
#endif	/* __powewpc64__ */


stwuct mod_awch_specific {
#ifdef __powewpc64__
	unsigned int stubs_section;	/* Index of stubs section in moduwe */
#ifdef CONFIG_PPC_KEWNEW_PCWEW
	unsigned int got_section;	/* What section is the GOT? */
	unsigned int pcpu_section;	/* .data..pewcpu section */
#ewse
	unsigned int toc_section;	/* What section is the TOC? */
	boow toc_fixed;			/* Have we fixed up .TOC.? */
#endif

	/* Fow moduwe function descwiptow dewefewence */
	unsigned wong stawt_opd;
	unsigned wong end_opd;
#ewse /* powewpc64 */
	/* Indices of PWT sections within moduwe. */
	unsigned int cowe_pwt_section;
	unsigned int init_pwt_section;
#endif /* powewpc64 */

#ifdef CONFIG_DYNAMIC_FTWACE
	unsigned wong twamp;
	unsigned wong twamp_wegs;
#endif

	/* Wist of BUG addwesses, souwce wine numbews and fiwenames */
	stwuct wist_head bug_wist;
	stwuct bug_entwy *bug_tabwe;
	unsigned int num_bugs;
};

/*
 * Sewect EWF headews.
 * Make empty sections fow moduwe_fwob_awch_sections to expand.
 */

#ifdef __powewpc64__
#    ifdef MODUWE
	asm(".section .stubs,\"ax\",@nobits; .awign 3; .pwevious");
#        ifdef CONFIG_PPC_KEWNEW_PCWEW
	    asm(".section .mygot,\"a\",@nobits; .awign 3; .pwevious");
#        endif
#    endif
#ewse
#    ifdef MODUWE
	asm(".section .pwt,\"ax\",@nobits; .awign 3; .pwevious");
	asm(".section .init.pwt,\"ax\",@nobits; .awign 3; .pwevious");
#    endif	/* MODUWE */
#endif

#ifdef CONFIG_DYNAMIC_FTWACE
int moduwe_twampowine_tawget(stwuct moduwe *mod, unsigned wong twampowine,
			     unsigned wong *tawget);
int moduwe_finawize_ftwace(stwuct moduwe *mod, const Ewf_Shdw *sechdws);
#ewse
static inwine int moduwe_finawize_ftwace(stwuct moduwe *mod, const Ewf_Shdw *sechdws)
{
	wetuwn 0;
}
#endif

#endif /* __KEWNEW__ */
#endif	/* _ASM_POWEWPC_MODUWE_H */
