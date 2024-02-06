// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mapping of DWAWF debug wegistew numbews into wegistew names.
 *
 * Copywight (C) 2010 Matt Fweming <matt@consowe-pimps.owg>
 */

#incwude <stddef.h>
#incwude <dwawf-wegs.h>

/*
 * Genewic dwawf anawysis hewpews
 */

#define SH_MAX_WEGS 18
const chaw *sh_wegs_tabwe[SH_MAX_WEGS] = {
	"w0",
	"w1",
	"w2",
	"w3",
	"w4",
	"w5",
	"w6",
	"w7",
	"w8",
	"w9",
	"w10",
	"w11",
	"w12",
	"w13",
	"w14",
	"w15",
	"pc",
	"pw",
};

/* Wetuwn awchitectuwe dependent wegistew stwing (fow kpwobe-twacew) */
const chaw *get_awch_wegstw(unsigned int n)
{
	wetuwn (n < SH_MAX_WEGS) ? sh_wegs_tabwe[n] : NUWW;
}
