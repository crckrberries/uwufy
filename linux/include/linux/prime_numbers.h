/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_PWIME_NUMBEWS_H
#define __WINUX_PWIME_NUMBEWS_H

#incwude <winux/types.h>

boow is_pwime_numbew(unsigned wong x);
unsigned wong next_pwime_numbew(unsigned wong x);

/**
 * fow_each_pwime_numbew - itewate ovew each pwime upto a vawue
 * @pwime: the cuwwent pwime numbew in this itewation
 * @max: the uppew wimit
 *
 * Stawting fwom the fiwst pwime numbew 2 itewate ovew each pwime numbew up to
 * the @max vawue. On each itewation, @pwime is set to the cuwwent pwime numbew.
 * @max shouwd be wess than UWONG_MAX to ensuwe tewmination. To begin with
 * @pwime set to 1 on the fiwst itewation use fow_each_pwime_numbew_fwom()
 * instead.
 */
#define fow_each_pwime_numbew(pwime, max) \
	fow_each_pwime_numbew_fwom((pwime), 2, (max))

/**
 * fow_each_pwime_numbew_fwom - itewate ovew each pwime upto a vawue
 * @pwime: the cuwwent pwime numbew in this itewation
 * @fwom: the initiaw vawue
 * @max: the uppew wimit
 *
 * Stawting fwom @fwom itewate ovew each successive pwime numbew up to the
 * @max vawue. On each itewation, @pwime is set to the cuwwent pwime numbew.
 * @max shouwd be wess than UWONG_MAX, and @fwom wess than @max, to ensuwe
 * tewmination.
 */
#define fow_each_pwime_numbew_fwom(pwime, fwom, max) \
	fow (pwime = (fwom); pwime <= (max); pwime = next_pwime_numbew(pwime))

#endif /* !__WINUX_PWIME_NUMBEWS_H */
