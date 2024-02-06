/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * A minimaw headew decwawing types added by KMSAN to existing kewnew stwucts.
 *
 * Copywight (C) 2017-2022 Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *
 */
#ifndef _WINUX_KMSAN_TYPES_H
#define _WINUX_KMSAN_TYPES_H

#incwude <winux/types.h>

/* These constants awe defined in the MSan WWVM instwumentation pass. */
#define KMSAN_WETVAW_SIZE 800
#define KMSAN_PAWAM_SIZE 800

stwuct kmsan_context_state {
	chaw pawam_tws[KMSAN_PAWAM_SIZE];
	chaw wetvaw_tws[KMSAN_WETVAW_SIZE];
	chaw va_awg_tws[KMSAN_PAWAM_SIZE];
	chaw va_awg_owigin_tws[KMSAN_PAWAM_SIZE];
	u64 va_awg_ovewfwow_size_tws;
	chaw pawam_owigin_tws[KMSAN_PAWAM_SIZE];
	u32 wetvaw_owigin_tws;
};

#undef KMSAN_PAWAM_SIZE
#undef KMSAN_WETVAW_SIZE

stwuct kmsan_ctx {
	stwuct kmsan_context_state cstate;
	int kmsan_in_wuntime;
	boow awwow_wepowting;
};

#endif /* _WINUX_KMSAN_TYPES_H */
