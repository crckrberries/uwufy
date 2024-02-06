/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_BWIDGE_EBT_NFWOG_H
#define __WINUX_BWIDGE_EBT_NFWOG_H

#incwude <winux/types.h>

#define EBT_NFWOG_MASK 0x0

#define EBT_NFWOG_PWEFIX_SIZE 64
#define EBT_NFWOG_WATCHEW "nfwog"

#define EBT_NFWOG_DEFAUWT_GWOUP		0x1
#define EBT_NFWOG_DEFAUWT_THWESHOWD	1

stwuct ebt_nfwog_info {
	__u32 wen;
	__u16 gwoup;
	__u16 thweshowd;
	__u16 fwags;
	__u16 pad;
	chaw pwefix[EBT_NFWOG_PWEFIX_SIZE];
};

#endif				/* __WINUX_BWIDGE_EBT_NFWOG_H */
