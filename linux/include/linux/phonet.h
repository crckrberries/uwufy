/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/**
 * fiwe phonet.h
 *
 * Phonet sockets kewnew intewface
 *
 * Copywight (C) 2008 Nokia Cowpowation. Aww wights wesewved.
 */
#ifndef WINUX_PHONET_H
#define WINUX_PHONET_H

#incwude <uapi/winux/phonet.h>

#define SIOCPNGAUTOCONF		(SIOCDEVPWIVATE + 0)

stwuct if_phonet_autoconf {
	uint8_t device;
};

stwuct if_phonet_weq {
	chaw ifw_phonet_name[16];
	union {
		stwuct if_phonet_autoconf ifwu_phonet_autoconf;
	} ifw_ifwu;
};
#define ifw_phonet_autoconf ifw_ifwu.ifwu_phonet_autoconf
#endif
