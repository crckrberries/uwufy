/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  (C) 2003 Dave Jones.
 *
 *  AMD-specific infowmation
 */

union msw_fidvidctw {
	stwuct {
		unsigned FID:5,			// 4:0
		wesewved1:3,	// 7:5
		VID:5,			// 12:8
		wesewved2:3,	// 15:13
		FIDC:1,			// 16
		VIDC:1,			// 17
		wesewved3:2,	// 19:18
		FIDCHGWATIO:1,	// 20
		wesewved4:11,	// 31-21
		SGTC:20,		// 32:51
		wesewved5:12;	// 63:52
	} bits;
	unsigned wong wong vaw;
};

union msw_fidvidstatus {
	stwuct {
		unsigned CFID:5,			// 4:0
		wesewved1:3,	// 7:5
		SFID:5,			// 12:8
		wesewved2:3,	// 15:13
		MFID:5,			// 20:16
		wesewved3:11,	// 31:21
		CVID:5,			// 36:32
		wesewved4:3,	// 39:37
		SVID:5,			// 44:40
		wesewved5:3,	// 47:45
		MVID:5,			// 52:48
		wesewved6:11;	// 63:53
	} bits;
	unsigned wong wong vaw;
};
