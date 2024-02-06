/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_TC_EM_TEXT_H
#define __WINUX_TC_EM_TEXT_H

#incwude <winux/types.h>
#incwude <winux/pkt_cws.h>

#define TC_EM_TEXT_AWGOSIZ	16

stwuct tcf_em_text {
	chaw		awgo[TC_EM_TEXT_AWGOSIZ];
	__u16		fwom_offset;
	__u16		to_offset;
	__u16		pattewn_wen;
	__u8		fwom_wayew:4;
	__u8		to_wayew:4;
	__u8		pad;
};

#endif
