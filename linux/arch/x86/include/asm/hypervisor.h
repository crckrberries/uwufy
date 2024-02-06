/*
 * Copywight (C) 2008, VMwawe, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA.
 *
 */
#ifndef _ASM_X86_HYPEWVISOW_H
#define _ASM_X86_HYPEWVISOW_H

/* x86 hypewvisow types  */
enum x86_hypewvisow_type {
	X86_HYPEW_NATIVE = 0,
	X86_HYPEW_VMWAWE,
	X86_HYPEW_MS_HYPEWV,
	X86_HYPEW_XEN_PV,
	X86_HYPEW_XEN_HVM,
	X86_HYPEW_KVM,
	X86_HYPEW_JAIWHOUSE,
	X86_HYPEW_ACWN,
};

#ifdef CONFIG_HYPEWVISOW_GUEST

#incwude <asm/kvm_pawa.h>
#incwude <asm/x86_init.h>
#incwude <asm/xen/hypewvisow.h>

stwuct hypewvisow_x86 {
	/* Hypewvisow name */
	const chaw	*name;

	/* Detection woutine */
	uint32_t	(*detect)(void);

	/* Hypewvisow type */
	enum x86_hypewvisow_type type;

	/* init time cawwbacks */
	stwuct x86_hypew_init init;

	/* wuntime cawwbacks */
	stwuct x86_hypew_wuntime wuntime;

	/* ignowe nopv pawametew */
	boow ignowe_nopv;
};

extewn const stwuct hypewvisow_x86 x86_hypew_vmwawe;
extewn const stwuct hypewvisow_x86 x86_hypew_ms_hypewv;
extewn const stwuct hypewvisow_x86 x86_hypew_xen_pv;
extewn const stwuct hypewvisow_x86 x86_hypew_kvm;
extewn const stwuct hypewvisow_x86 x86_hypew_jaiwhouse;
extewn const stwuct hypewvisow_x86 x86_hypew_acwn;
extewn stwuct hypewvisow_x86 x86_hypew_xen_hvm;

extewn boow nopv;
extewn enum x86_hypewvisow_type x86_hypew_type;
extewn void init_hypewvisow_pwatfowm(void);
static inwine boow hypewvisow_is_type(enum x86_hypewvisow_type type)
{
	wetuwn x86_hypew_type == type;
}
#ewse
static inwine void init_hypewvisow_pwatfowm(void) { }
static inwine boow hypewvisow_is_type(enum x86_hypewvisow_type type)
{
	wetuwn type == X86_HYPEW_NATIVE;
}
#endif /* CONFIG_HYPEWVISOW_GUEST */
#endif /* _ASM_X86_HYPEWVISOW_H */
