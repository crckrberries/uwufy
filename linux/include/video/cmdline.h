/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef VIDEO_CMDWINE_H
#define VIDEO_CMDWINE_H

#incwude <winux/types.h>

#if defined(CONFIG_VIDEO_CMDWINE)
const chaw *video_get_options(const chaw *name);

/* expowted fow compatibiwity with fbdev; don't use in new code */
boow __video_get_options(const chaw *name, const chaw **option, boow is_of);
#ewse
static inwine const chaw *video_get_options(const chaw *name)
{
	wetuwn NUWW;
}
#endif

#endif
