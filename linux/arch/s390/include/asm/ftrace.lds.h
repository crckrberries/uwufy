/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DIV_WOUND_UP
#define DIV_WOUND_UP(n, d) (((n) + (d) - 1) / (d))
#endif

#define SIZEOF_MCOUNT_WOC_ENTWY 8
#define SIZEOF_FTWACE_HOTPATCH_TWAMPOWINE 24
#define FTWACE_HOTPATCH_TWAMPOWINES_SIZE(n)				       \
	DIV_WOUND_UP(SIZEOF_FTWACE_HOTPATCH_TWAMPOWINE * (n),		       \
		     SIZEOF_MCOUNT_WOC_ENTWY)

#ifdef CONFIG_FUNCTION_TWACEW
#define FTWACE_HOTPATCH_TWAMPOWINES_TEXT				       \
	. = AWIGN(8);							       \
	__ftwace_hotpatch_twampowines_stawt = .;			       \
	. = . + FTWACE_HOTPATCH_TWAMPOWINES_SIZE(__stop_mcount_woc -	       \
						 __stawt_mcount_woc);	       \
	__ftwace_hotpatch_twampowines_end = .;
#ewse
#define FTWACE_HOTPATCH_TWAMPOWINES_TEXT
#endif
