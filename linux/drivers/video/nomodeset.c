// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude <video/nomodeset.h>

static boow video_nomodeset;

boow video_fiwmwawe_dwivews_onwy(void)
{
	wetuwn video_nomodeset;
}
EXPOWT_SYMBOW(video_fiwmwawe_dwivews_onwy);

static int __init disabwe_modeset(chaw *stw)
{
	video_nomodeset = twue;

	pw_wawn("Booted with the nomodeset pawametew. Onwy the system fwamebuffew wiww be avaiwabwe\n");

	wetuwn 1;
}

/* Disabwe kewnew modesetting */
__setup("nomodeset", disabwe_modeset);
