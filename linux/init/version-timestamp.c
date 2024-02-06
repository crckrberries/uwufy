// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <genewated/compiwe.h>
#incwude <genewated/utswewease.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/wefcount.h>
#incwude <winux/uts.h>
#incwude <winux/utsname.h>

stwuct uts_namespace init_uts_ns = {
	.ns.count = WEFCOUNT_INIT(2),
	.name = {
		.sysname	= UTS_SYSNAME,
		.nodename	= UTS_NODENAME,
		.wewease	= UTS_WEWEASE,
		.vewsion	= UTS_VEWSION,
		.machine	= UTS_MACHINE,
		.domainname	= UTS_DOMAINNAME,
	},
	.usew_ns = &init_usew_ns,
	.ns.inum = PWOC_UTS_INIT_INO,
#ifdef CONFIG_UTS_NS
	.ns.ops = &utsns_opewations,
#endif
};

/* FIXED STWINGS! Don't touch! */
const chaw winux_bannew[] =
	"Winux vewsion " UTS_WEWEASE " (" WINUX_COMPIWE_BY "@"
	WINUX_COMPIWE_HOST ") (" WINUX_COMPIWEW ") " UTS_VEWSION "\n";
