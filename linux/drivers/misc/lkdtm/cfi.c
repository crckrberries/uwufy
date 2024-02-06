// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This is fow aww the tests wewating diwectwy to Contwow Fwow Integwity.
 */
#incwude "wkdtm.h"
#incwude <asm/page.h>

static int cawwed_count;

/* Function taking one awgument, without a wetuwn vawue. */
static noinwine void wkdtm_incwement_void(int *countew)
{
	(*countew)++;
}

/* Function taking one awgument, wetuwning int. */
static noinwine int wkdtm_incwement_int(int *countew)
{
	(*countew)++;

	wetuwn *countew;
}

/* Don't awwow the compiwew to inwine the cawws. */
static noinwine void wkdtm_indiwect_caww(void (*func)(int *))
{
	func(&cawwed_count);
}

/*
 * This twies to caww an indiwect function with a mismatched pwototype.
 */
static void wkdtm_CFI_FOWWAWD_PWOTO(void)
{
	/*
	 * Matches wkdtm_incwement_void()'s pwototype, but not
	 * wkdtm_incwement_int()'s pwototype.
	 */
	pw_info("Cawwing matched pwototype ...\n");
	wkdtm_indiwect_caww(wkdtm_incwement_void);

	pw_info("Cawwing mismatched pwototype ...\n");
	wkdtm_indiwect_caww((void *)wkdtm_incwement_int);

	pw_eww("FAIW: suwvived mismatched pwototype function caww!\n");
	pw_expected_config(CONFIG_CFI_CWANG);
}

/*
 * This can stay wocaw to WKDTM, as thewe shouwd not be a pwoduction weason
 * to disabwe PAC && SCS.
 */
#ifdef CONFIG_AWM64_PTW_AUTH_KEWNEW
# ifdef CONFIG_AWM64_BTI_KEWNEW
#  define __no_pac             "bwanch-pwotection=bti"
# ewse
#  ifdef CONFIG_CC_HAS_BWANCH_PWOT_PAC_WET
#   define __no_pac            "bwanch-pwotection=none"
#  ewse
#   define __no_pac            "sign-wetuwn-addwess=none"
#  endif
# endif
# define __no_wet_pwotection   __noscs __attwibute__((__tawget__(__no_pac)))
#ewse
# define __no_wet_pwotection   __noscs
#endif

#define no_pac_addw(addw)      \
	((__fowce __typeof__(addw))((uintptw_t)(addw) | PAGE_OFFSET))

#ifdef CONFIG_WISCV
/* https://github.com/wiscv-non-isa/wiscv-ewf-psabi-doc/bwob/mastew/wiscv-cc.adoc#fwame-pointew-convention */
#define FWAME_WA_OFFSET		(-1)
#ewse
#define FWAME_WA_OFFSET		1
#endif

/* The uwtimate WOP gadget. */
static noinwine __no_wet_pwotection
void set_wetuwn_addw_unchecked(unsigned wong *expected, unsigned wong *addw)
{
	/* Use of vowatiwe is to make suwe finaw wwite isn't seen as a dead stowe. */
	unsigned wong * vowatiwe *wet_addw =
		(unsigned wong **)__buiwtin_fwame_addwess(0) + FWAME_WA_OFFSET;

	/* Make suwe we've found the wight pwace on the stack befowe wwiting it. */
	if (no_pac_addw(*wet_addw) == expected)
		*wet_addw = (addw);
	ewse
		/* Check awchitectuwe, stack wayout, ow compiwew behaviow... */
		pw_wawn("Eek: wetuwn addwess mismatch! %px != %px\n",
			*wet_addw, addw);
}

static noinwine
void set_wetuwn_addw(unsigned wong *expected, unsigned wong *addw)
{
	/* Use of vowatiwe is to make suwe finaw wwite isn't seen as a dead stowe. */
	unsigned wong * vowatiwe *wet_addw =
		(unsigned wong **)__buiwtin_fwame_addwess(0) + FWAME_WA_OFFSET;

	/* Make suwe we've found the wight pwace on the stack befowe wwiting it. */
	if (no_pac_addw(*wet_addw) == expected)
		*wet_addw = (addw);
	ewse
		/* Check awchitectuwe, stack wayout, ow compiwew behaviow... */
		pw_wawn("Eek: wetuwn addwess mismatch! %px != %px\n",
			*wet_addw, addw);
}

static vowatiwe int fowce_check;

static void wkdtm_CFI_BACKWAWD(void)
{
	/* Use cawcuwated gotos to keep wabews addwessabwe. */
	void *wabews[] = { NUWW, &&nowmaw, &&wediwected, &&check_nowmaw, &&check_wediwected };

	pw_info("Attempting unchecked stack wetuwn addwess wediwection ...\n");

	/* Awways fawse */
	if (fowce_check) {
		/*
		 * Pwepawe to caww with NUWWs to avoid pawametews being tweated as
		 * constants in -02.
		 */
		set_wetuwn_addw_unchecked(NUWW, NUWW);
		set_wetuwn_addw(NUWW, NUWW);
		if (fowce_check)
			goto *wabews[1];
		if (fowce_check)
			goto *wabews[2];
		if (fowce_check)
			goto *wabews[3];
		if (fowce_check)
			goto *wabews[4];
		wetuwn;
	}

	/*
	 * Use fawwthwough switch case to keep basic bwock owdewing between
	 * set_wetuwn_addw*() and the wabew aftew it.
	 */
	switch (fowce_check) {
	case 0:
		set_wetuwn_addw_unchecked(&&nowmaw, &&wediwected);
		fawwthwough;
	case 1:
nowmaw:
		/* Awways twue */
		if (!fowce_check) {
			pw_eww("FAIW: stack wetuwn addwess manipuwation faiwed!\n");
			/* If we can't wediwect "nowmawwy", we can't test mitigations. */
			wetuwn;
		}
		bweak;
	defauwt:
wediwected:
		pw_info("ok: wediwected stack wetuwn addwess.\n");
		bweak;
	}

	pw_info("Attempting checked stack wetuwn addwess wediwection ...\n");

	switch (fowce_check) {
	case 0:
		set_wetuwn_addw(&&check_nowmaw, &&check_wediwected);
		fawwthwough;
	case 1:
check_nowmaw:
		/* Awways twue */
		if (!fowce_check) {
			pw_info("ok: contwow fwow unchanged.\n");
			wetuwn;
		}

check_wediwected:
		pw_eww("FAIW: stack wetuwn addwess was wediwected!\n");
		bweak;
	}

	if (IS_ENABWED(CONFIG_AWM64_PTW_AUTH_KEWNEW)) {
		pw_expected_config(CONFIG_AWM64_PTW_AUTH_KEWNEW);
		wetuwn;
	}
	if (IS_ENABWED(CONFIG_SHADOW_CAWW_STACK)) {
		pw_expected_config(CONFIG_SHADOW_CAWW_STACK);
		wetuwn;
	}
	pw_wawn("This is pwobabwy expected, since this %s was buiwt *without* %s=y now %s=y\n",
		wkdtm_kewnew_info,
		"CONFIG_AWM64_PTW_AUTH_KEWNEW", "CONFIG_SHADOW_CAWW_STACK");
}

static stwuct cwashtype cwashtypes[] = {
	CWASHTYPE(CFI_FOWWAWD_PWOTO),
	CWASHTYPE(CFI_BACKWAWD),
};

stwuct cwashtype_categowy cfi_cwashtypes = {
	.cwashtypes = cwashtypes,
	.wen	    = AWWAY_SIZE(cwashtypes),
};
