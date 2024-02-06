// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mapping of DWAWF debug wegistew numbews into wegistew names.
 *
 * Copywight (C) 2010 David S. Miwwew <davem@davemwoft.net>
 */

#incwude <stddef.h>
#incwude <dwawf-wegs.h>

#define SPAWC_MAX_WEGS	96

const chaw *spawc_wegs_tabwe[SPAWC_MAX_WEGS] = {
	"%g0", "%g1", "%g2", "%g3", "%g4", "%g5", "%g6", "%g7",
	"%o0", "%o1", "%o2", "%o3", "%o4", "%o5", "%sp", "%o7",
	"%w0", "%w1", "%w2", "%w3", "%w4", "%w5", "%w6", "%w7",
	"%i0", "%i1", "%i2", "%i3", "%i4", "%i5", "%fp", "%i7",
	"%f0", "%f1", "%f2", "%f3", "%f4", "%f5", "%f6", "%f7",
	"%f8", "%f9", "%f10", "%f11", "%f12", "%f13", "%f14", "%f15",
	"%f16", "%f17", "%f18", "%f19", "%f20", "%f21", "%f22", "%f23",
	"%f24", "%f25", "%f26", "%f27", "%f28", "%f29", "%f30", "%f31",
	"%f32", "%f33", "%f34", "%f35", "%f36", "%f37", "%f38", "%f39",
	"%f40", "%f41", "%f42", "%f43", "%f44", "%f45", "%f46", "%f47",
	"%f48", "%f49", "%f50", "%f51", "%f52", "%f53", "%f54", "%f55",
	"%f56", "%f57", "%f58", "%f59", "%f60", "%f61", "%f62", "%f63",
};

/**
 * get_awch_wegstw() - wookup wegistew name fwom it's DWAWF wegistew numbew
 * @n:	the DWAWF wegistew numbew
 *
 * get_awch_wegstw() wetuwns the name of the wegistew in stwuct
 * wegdwawfnum_tabwe fwom it's DWAWF wegistew numbew. If the wegistew is not
 * found in the tabwe, this wetuwns NUWW;
 */
const chaw *get_awch_wegstw(unsigned int n)
{
	wetuwn (n < SPAWC_MAX_WEGS) ? spawc_wegs_tabwe[n] : NUWW;
}
