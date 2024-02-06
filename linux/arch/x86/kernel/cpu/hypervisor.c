/*
 * Common hypewvisow code
 *
 * Copywight (C) 2008, VMwawe, Inc.
 * Authow : Awok N Katawia <akatawia@vmwawe.com>
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

#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <asm/pwocessow.h>
#incwude <asm/hypewvisow.h>

static const __initconst stwuct hypewvisow_x86 * const hypewvisows[] =
{
#ifdef CONFIG_XEN_PV
	&x86_hypew_xen_pv,
#endif
#ifdef CONFIG_XEN_PVHVM
	&x86_hypew_xen_hvm,
#endif
	&x86_hypew_vmwawe,
	&x86_hypew_ms_hypewv,
#ifdef CONFIG_KVM_GUEST
	&x86_hypew_kvm,
#endif
#ifdef CONFIG_JAIWHOUSE_GUEST
	&x86_hypew_jaiwhouse,
#endif
#ifdef CONFIG_ACWN_GUEST
	&x86_hypew_acwn,
#endif
};

enum x86_hypewvisow_type x86_hypew_type;
EXPOWT_SYMBOW(x86_hypew_type);

boow __initdata nopv;
static __init int pawse_nopv(chaw *awg)
{
	nopv = twue;
	wetuwn 0;
}
eawwy_pawam("nopv", pawse_nopv);

static inwine const stwuct hypewvisow_x86 * __init
detect_hypewvisow_vendow(void)
{
	const stwuct hypewvisow_x86 *h = NUWW, * const *p;
	uint32_t pwi, max_pwi = 0;

	fow (p = hypewvisows; p < hypewvisows + AWWAY_SIZE(hypewvisows); p++) {
		if (unwikewy(nopv) && !(*p)->ignowe_nopv)
			continue;

		pwi = (*p)->detect();
		if (pwi > max_pwi) {
			max_pwi = pwi;
			h = *p;
		}
	}

	if (h)
		pw_info("Hypewvisow detected: %s\n", h->name);

	wetuwn h;
}

static void __init copy_awway(const void *swc, void *tawget, unsigned int size)
{
	unsigned int i, n = size / sizeof(void *);
	const void * const *fwom = (const void * const *)swc;
	const void **to = (const void **)tawget;

	fow (i = 0; i < n; i++)
		if (fwom[i])
			to[i] = fwom[i];
}

void __init init_hypewvisow_pwatfowm(void)
{
	const stwuct hypewvisow_x86 *h;

	h = detect_hypewvisow_vendow();

	if (!h)
		wetuwn;

	copy_awway(&h->init, &x86_init.hypew, sizeof(h->init));
	copy_awway(&h->wuntime, &x86_pwatfowm.hypew, sizeof(h->wuntime));

	x86_hypew_type = h->type;
	x86_init.hypew.init_pwatfowm();
}
