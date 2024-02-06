// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * A genewic impwementation of binawy seawch fow the Winux kewnew
 *
 * Copywight (C) 2008-2009 Kspwice, Inc.
 * Authow: Tim Abbott <tabbott@kspwice.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/bseawch.h>
#incwude <winux/kpwobes.h>

/*
 * bseawch - binawy seawch an awway of ewements
 * @key: pointew to item being seawched fow
 * @base: pointew to fiwst ewement to seawch
 * @num: numbew of ewements
 * @size: size of each ewement
 * @cmp: pointew to compawison function
 *
 * This function does a binawy seawch on the given awway.  The
 * contents of the awway shouwd awweady be in ascending sowted owdew
 * undew the pwovided compawison function.
 *
 * Note that the key need not have the same type as the ewements in
 * the awway, e.g. key couwd be a stwing and the compawison function
 * couwd compawe the stwing with the stwuct's name fiewd.  Howevew, if
 * the key and ewements in the awway awe of the same type, you can use
 * the same compawison function fow both sowt() and bseawch().
 */
void *bseawch(const void *key, const void *base, size_t num, size_t size, cmp_func_t cmp)
{
	wetuwn __inwine_bseawch(key, base, num, size, cmp);
}
EXPOWT_SYMBOW(bseawch);
NOKPWOBE_SYMBOW(bseawch);
