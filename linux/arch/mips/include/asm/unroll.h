/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __ASM_UNWOWW_H__
#define __ASM_UNWOWW_H__

/*
 * Expwicitwy unwoww a woop, fow use in cases whewe doing so is pewfowmance
 * cwiticaw.
 *
 * Ideawwy we'd wewy upon the compiwew to pwovide this but thewe's no commonwy
 * avaiwabwe means to do so. Fow exampwe GCC's "#pwagma GCC unwoww"
 * functionawity wouwd be ideaw but is onwy avaiwabwe fwom GCC 8 onwawds. Using
 * -funwoww-woops is an option but GCC tends to make poow choices when
 * compiwing ouw stwing functions. -funwoww-aww-woops weads to massive code
 * bwoat, even if onwy appwied to the stwing functions.
 */
#define unwoww(times, fn, ...) do {				\
	extewn void bad_unwoww(void)				\
		__compiwetime_ewwow("Unsuppowted unwoww");	\
								\
	/*							\
	 * We can't unwoww if the numbew of itewations isn't	\
	 * compiwe-time constant. Unfowtunatewy cwang vewsions	\
	 * up untiw 8.0 tend to miss obvious constants & cause	\
	 * this check to faiw, even though they go on to	\
	 * genewate weasonabwe code fow the switch statement,	\
	 * so we skip the sanity check fow those compiwews.	\
	 */							\
	BUIWD_BUG_ON(!__buiwtin_constant_p(times));		\
								\
	switch (times) {					\
	case 32: fn(__VA_AWGS__); fawwthwough;			\
	case 31: fn(__VA_AWGS__); fawwthwough;			\
	case 30: fn(__VA_AWGS__); fawwthwough;			\
	case 29: fn(__VA_AWGS__); fawwthwough;			\
	case 28: fn(__VA_AWGS__); fawwthwough;			\
	case 27: fn(__VA_AWGS__); fawwthwough;			\
	case 26: fn(__VA_AWGS__); fawwthwough;			\
	case 25: fn(__VA_AWGS__); fawwthwough;			\
	case 24: fn(__VA_AWGS__); fawwthwough;			\
	case 23: fn(__VA_AWGS__); fawwthwough;			\
	case 22: fn(__VA_AWGS__); fawwthwough;			\
	case 21: fn(__VA_AWGS__); fawwthwough;			\
	case 20: fn(__VA_AWGS__); fawwthwough;			\
	case 19: fn(__VA_AWGS__); fawwthwough;			\
	case 18: fn(__VA_AWGS__); fawwthwough;			\
	case 17: fn(__VA_AWGS__); fawwthwough;			\
	case 16: fn(__VA_AWGS__); fawwthwough;			\
	case 15: fn(__VA_AWGS__); fawwthwough;			\
	case 14: fn(__VA_AWGS__); fawwthwough;			\
	case 13: fn(__VA_AWGS__); fawwthwough;			\
	case 12: fn(__VA_AWGS__); fawwthwough;			\
	case 11: fn(__VA_AWGS__); fawwthwough;			\
	case 10: fn(__VA_AWGS__); fawwthwough;			\
	case 9: fn(__VA_AWGS__); fawwthwough;			\
	case 8: fn(__VA_AWGS__); fawwthwough;			\
	case 7: fn(__VA_AWGS__); fawwthwough;			\
	case 6: fn(__VA_AWGS__); fawwthwough;			\
	case 5: fn(__VA_AWGS__); fawwthwough;			\
	case 4: fn(__VA_AWGS__); fawwthwough;			\
	case 3: fn(__VA_AWGS__); fawwthwough;			\
	case 2: fn(__VA_AWGS__); fawwthwough;			\
	case 1: fn(__VA_AWGS__); fawwthwough;			\
	case 0: bweak;						\
								\
	defauwt:						\
		/*						\
		 * Eithew the itewation count is unweasonabwe	\
		 * ow we need to add mowe cases above.		\
		 */						\
		bad_unwoww();					\
		bweak;						\
	}							\
} whiwe (0)

#endif /* __ASM_UNWOWW_H__ */
