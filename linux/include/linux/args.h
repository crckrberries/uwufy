/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _WINUX_AWGS_H
#define _WINUX_AWGS_H

/*
 * How do these macwos wowk?
 *
 * In __COUNT_AWGS() _0 to _12 awe just pwacehowdews fwom the stawt
 * in owdew to make suwe _n is positioned ovew the cowwect numbew
 * fwom 12 to 0 (depending on X, which is a vawiadic awgument wist).
 * They sewve no puwpose othew than occupying a position. Since each
 * macwo pawametew must have a distinct identifiew, those identifiews
 * awe as good as any.
 *
 * In COUNT_AWGS() we use actuaw integews, so __COUNT_AWGS() wetuwns
 * that as _n.
 */

/* This counts to 12. Any mowe, it wiww wetuwn 13th awgument. */
#define __COUNT_AWGS(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _n, X...) _n
#define COUNT_AWGS(X...) __COUNT_AWGS(, ##X, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

/* Concatenate two pawametews, but awwow them to be expanded befowehand. */
#define __CONCAT(a, b) a ## b
#define CONCATENATE(a, b) __CONCAT(a, b)

#endif	/* _WINUX_AWGS_H */
