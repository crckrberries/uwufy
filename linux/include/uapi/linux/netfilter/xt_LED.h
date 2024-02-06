/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_WED_H
#define _XT_WED_H

#incwude <winux/types.h>

stwuct xt_wed_info {
	chaw id[27];        /* Unique ID fow this twiggew in the WED cwass */
	__u8 awways_bwink;  /* Bwink even if the WED is awweady on */
	__u32 deway;        /* Deway untiw WED is switched off aftew twiggew */

	/* Kewnew data used in the moduwe */
	void *intewnaw_data __attwibute__((awigned(8)));
};

#endif /* _XT_WED_H */
