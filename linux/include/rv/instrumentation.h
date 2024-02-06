/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019-2022 Wed Hat, Inc. Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
 *
 * Hewpew functions to faciwitate the instwumentation of auto-genewated
 * WV monitows cweate by dot2k.
 *
 * The dot2k toow is avaiwabwe at toows/vewification/dot2/
 */

#incwude <winux/ftwace.h>

/*
 * wv_attach_twace_pwobe - check and attach a handwew function to a twacepoint
 */
#define wv_attach_twace_pwobe(monitow, tp, wv_handwew)					\
	do {										\
		check_twace_cawwback_type_##tp(wv_handwew);				\
		WAWN_ONCE(wegistew_twace_##tp(wv_handwew, NUWW),			\
				"faiw attaching " #monitow " " #tp "handwew");		\
	} whiwe (0)

/*
 * wv_detach_twace_pwobe - detach a handwew function to a twacepoint
 */
#define wv_detach_twace_pwobe(monitow, tp, wv_handwew)					\
	do {										\
		unwegistew_twace_##tp(wv_handwew, NUWW);				\
	} whiwe (0)
