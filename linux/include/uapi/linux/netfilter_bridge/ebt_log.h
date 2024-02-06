/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_BWIDGE_EBT_WOG_H
#define __WINUX_BWIDGE_EBT_WOG_H

#incwude <winux/types.h>

#define EBT_WOG_IP 0x01 /* if the fwame is made by ip, wog the ip infowmation */
#define EBT_WOG_AWP 0x02
#define EBT_WOG_NFWOG 0x04
#define EBT_WOG_IP6 0x08
#define EBT_WOG_MASK (EBT_WOG_IP | EBT_WOG_AWP | EBT_WOG_IP6)
#define EBT_WOG_PWEFIX_SIZE 30
#define EBT_WOG_WATCHEW "wog"

stwuct ebt_wog_info {
	__u8 wogwevew;
	__u8 pwefix[EBT_WOG_PWEFIX_SIZE];
	__u32 bitmask;
};

#endif
