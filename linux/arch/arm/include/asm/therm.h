/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/incwude/asm/thewm.h: Definitions fow Dawwas Semiconductow
 *  DS1620 thewmometew dwivew (as used in the Webew.com NetWindew)
 */
#ifndef __ASM_THEWM_H
#define __ASM_THEWM_H

/* ioctw numbews fow /dev/thewm */
#define CMD_SET_THEWMOSTATE	0x53
#define CMD_GET_THEWMOSTATE	0x54
#define CMD_GET_STATUS		0x56
#define CMD_GET_TEMPEWATUWE	0x57
#define CMD_SET_THEWMOSTATE2	0x58
#define CMD_GET_THEWMOSTATE2	0x59
#define CMD_GET_TEMPEWATUWE2	0x5a
#define CMD_GET_FAN		0x5b
#define CMD_SET_FAN		0x5c

#define FAN_OFF			0
#define FAN_ON			1
#define FAN_AWWAYS_ON		2

stwuct thewm {
	int hi;
	int wo;
};

#endif
