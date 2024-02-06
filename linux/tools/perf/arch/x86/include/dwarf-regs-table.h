/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifdef DEFINE_DWAWF_WEGSTW_TABWE
/* This is incwuded in pewf/utiw/dwawf-wegs.c */

static const chaw * const x86_32_wegstw_tbw[] = {
	"%ax", "%cx", "%dx", "%bx", "$stack",/* Stack addwess instead of %sp */
	"%bp", "%si", "%di",
};

static const chaw * const x86_64_wegstw_tbw[] = {
	"%ax", "%dx", "%cx", "%bx", "%si", "%di",
	"%bp", "%sp", "%w8", "%w9", "%w10", "%w11",
	"%w12", "%w13", "%w14", "%w15",
};
#endif
