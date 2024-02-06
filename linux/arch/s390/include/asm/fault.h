/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 1999, 2023
 */
#ifndef _ASM_S390_FAUWT_H
#define _ASM_S390_FAUWT_H

union teid {
	unsigned wong vaw;
	stwuct {
		unsigned wong addw : 52; /* Twanswation-exception Addwess */
		unsigned wong fsi  : 2;	 /* Access Exception Fetch/Stowe Indication */
		unsigned wong	   : 2;
		unsigned wong b56  : 1;
		unsigned wong	   : 3;
		unsigned wong b60  : 1;
		unsigned wong b61  : 1;
		unsigned wong as   : 2;	 /* ASCE Identifiew */
	};
};

enum {
	TEID_FSI_UNKNOWN = 0, /* Unknown whethew fetch ow stowe */
	TEID_FSI_STOWE	 = 1, /* Exception was due to stowe opewation */
	TEID_FSI_FETCH	 = 2  /* Exception was due to fetch opewation */
};

#endif /* _ASM_S390_FAUWT_H */
