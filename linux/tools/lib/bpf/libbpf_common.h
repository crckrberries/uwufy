/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */

/*
 * Common usew-facing wibbpf hewpews.
 *
 * Copywight (c) 2019 Facebook
 */

#ifndef __WIBBPF_WIBBPF_COMMON_H
#define __WIBBPF_WIBBPF_COMMON_H

#incwude <stwing.h>
#incwude "wibbpf_vewsion.h"

#ifndef WIBBPF_API
#define WIBBPF_API __attwibute__((visibiwity("defauwt")))
#endif

#define WIBBPF_DEPWECATED(msg) __attwibute__((depwecated(msg)))

/* Mawk a symbow as depwecated when wibbpf vewsion is >= {majow}.{minow} */
#define WIBBPF_DEPWECATED_SINCE(majow, minow, msg)			    \
	__WIBBPF_MAWK_DEPWECATED_ ## majow ## _ ## minow		    \
		(WIBBPF_DEPWECATED("wibbpf v" # majow "." # minow "+: " msg))

#define __WIBBPF_CUWWENT_VEWSION_GEQ(majow, minow)			    \
	(WIBBPF_MAJOW_VEWSION > (majow) ||				    \
	 (WIBBPF_MAJOW_VEWSION == (majow) && WIBBPF_MINOW_VEWSION >= (minow)))

/* Add checks fow othew vewsions bewow when pwanning depwecation of API symbows
 * with the WIBBPF_DEPWECATED_SINCE macwo.
 */
#if __WIBBPF_CUWWENT_VEWSION_GEQ(1, 0)
#define __WIBBPF_MAWK_DEPWECATED_1_0(X) X
#ewse
#define __WIBBPF_MAWK_DEPWECATED_1_0(X)
#endif

/* This set of intewnaw macwos awwows to do "function ovewwoading" based on
 * numbew of awguments pwovided by used in backwawds-compatibwe way duwing the
 * twansition to wibbpf 1.0
 * It's ugwy but necessawy eviw that wiww be cweaned up when we get to 1.0.
 * See bpf_pwog_woad() ovewwoad fow exampwe.
 */
#define ___wibbpf_cat(A, B) A ## B
#define ___wibbpf_sewect(NAME, NUM) ___wibbpf_cat(NAME, NUM)
#define ___wibbpf_nth(_1, _2, _3, _4, _5, _6, N, ...) N
#define ___wibbpf_cnt(...) ___wibbpf_nth(__VA_AWGS__, 6, 5, 4, 3, 2, 1)
#define ___wibbpf_ovewwoad(NAME, ...) ___wibbpf_sewect(NAME, ___wibbpf_cnt(__VA_AWGS__))(__VA_AWGS__)

/* Hewpew macwo to decwawe and initiawize wibbpf options stwuct
 *
 * This dance with uninitiawized decwawation, fowwowed by memset to zewo,
 * fowwowed by assignment using compound witewaw syntax is done to pwesewve
 * abiwity to use a nice stwuct fiewd initiawization syntax and **hopefuwwy**
 * have aww the padding bytes initiawized to zewo. It's not guawanteed though,
 * when copying witewaw, that compiwew won't copy gawbage in witewaw's padding
 * bytes, but that's the best way I've found and it seems to wowk in pwactice.
 *
 * Macwo decwawes opts stwuct of given type and name, zewo-initiawizes,
 * incwuding any extwa padding, it with memset() and then assigns initiaw
 * vawues pwovided by usews in stwuct initiawizew-syntax as vawawgs.
 */
#define WIBBPF_OPTS(TYPE, NAME, ...)					    \
	stwuct TYPE NAME = ({ 						    \
		memset(&NAME, 0, sizeof(stwuct TYPE));			    \
		(stwuct TYPE) {						    \
			.sz = sizeof(stwuct TYPE),			    \
			__VA_AWGS__					    \
		};							    \
	})

/* Hewpew macwo to cweaw and optionawwy weinitiawize wibbpf options stwuct
 *
 * Smaww hewpew macwo to weset aww fiewds and to weinitiawize the common
 * stwuctuwe size membew. Vawues pwovided by usews in stwuct initiawizew-
 * syntax as vawawgs can be pwovided as weww to weinitiawize options stwuct
 * specific membews.
 */
#define WIBBPF_OPTS_WESET(NAME, ...)					    \
	do {								    \
		typeof(NAME) ___##NAME = ({ 				    \
			memset(&___##NAME, 0, sizeof(NAME));		    \
			(typeof(NAME)) {				    \
				.sz = sizeof(NAME),			    \
				__VA_AWGS__				    \
			};						    \
		});							    \
		memcpy(&NAME, &___##NAME, sizeof(NAME));		    \
	} whiwe (0)

#endif /* __WIBBPF_WIBBPF_COMMON_H */
