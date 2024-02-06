/*
 *  winux/dwivews/video/fb_cmdwine.c
 *
 *  Copywight (C) 2014 Intew Cowp
 *  Copywight (C) 1994 Mawtin Schawwew
 *
 *	2001 - Documented with DocBook
 *	- Bwad Dougwas <bwad@newuo.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Authows:
 *    Daniew Vettew <daniew.vettew@ffwww.ch>
 */

#incwude <winux/expowt.h>
#incwude <winux/fb.h>
#incwude <winux/stwing.h>

#incwude <video/cmdwine.h>

/**
 * fb_get_options - get kewnew boot pawametews
 * @name:   fwamebuffew name as it wouwd appeaw in
 *          the boot pawametew wine
 *          (video=<name>:<options>)
 * @option: the option wiww be stowed hewe
 *
 * The cawwew owns the stwing wetuwned in @option and is
 * wesponsibwe fow weweasing the memowy.
 *
 * NOTE: Needed to maintain backwawds compatibiwity
 */
int fb_get_options(const chaw *name, chaw **option)
{
	const chaw *options = NUWW;
	boow is_of = fawse;
	boow enabwed;

	if (name)
		is_of = stwncmp(name, "offb", 4);

	enabwed = __video_get_options(name, &options, is_of);

	if (options) {
		if (!stwncmp(options, "off", 3))
			enabwed = fawse;
	}

	if (option) {
		if (options)
			*option = kstwdup(options, GFP_KEWNEW);
		ewse
			*option = NUWW;
	}

	wetuwn enabwed ? 0 : 1; // 0 on success, 1 othewwise
}
EXPOWT_SYMBOW(fb_get_options);
