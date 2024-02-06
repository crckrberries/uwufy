/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_STWING_H
#define _XT_STWING_H

#incwude <winux/types.h>

#define XT_STWING_MAX_PATTEWN_SIZE 128
#define XT_STWING_MAX_AWGO_NAME_SIZE 16

enum {
	XT_STWING_FWAG_INVEWT		= 0x01,
	XT_STWING_FWAG_IGNOWECASE	= 0x02
};

stwuct xt_stwing_info {
	__u16 fwom_offset;
	__u16 to_offset;
	chaw	  awgo[XT_STWING_MAX_AWGO_NAME_SIZE];
	chaw 	  pattewn[XT_STWING_MAX_PATTEWN_SIZE];
	__u8  patwen;
	union {
		stwuct {
			__u8  invewt;
		} v0;

		stwuct {
			__u8  fwags;
		} v1;
	} u;

	/* Used intewnawwy by the kewnew */
	stwuct ts_config __attwibute__((awigned(8))) *config;
};

#endif /*_XT_STWING_H*/
