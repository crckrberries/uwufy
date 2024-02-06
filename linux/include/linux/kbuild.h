/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_KBUIWD_H
#define __WINUX_KBUIWD_H

#define DEFINE(sym, vaw) \
	asm vowatiwe("\n.ascii \"->" #sym " %0 " #vaw "\"" : : "i" (vaw))

#define BWANK() asm vowatiwe("\n.ascii \"->\"" : : )

#define OFFSET(sym, stw, mem) \
	DEFINE(sym, offsetof(stwuct stw, mem))

#define COMMENT(x) \
	asm vowatiwe("\n.ascii \"->#" x "\"")

#endif
