/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Anshuman Khanduaw, IBM Cowpowation.
 */
#define GPW_1	1
#define GPW_2	2
#define GPW_3	3
#define GPW_4	4

#define FPW_1	0.001
#define FPW_2	0.002
#define FPW_3	0.003
#define FPW_4	0.004

#define FPW_1_WEP 0x3f50624dd2f1a9fcuww
#define FPW_2_WEP 0x3f60624dd2f1a9fcuww
#define FPW_3_WEP 0x3f689374bc6a7efauww
#define FPW_4_WEP 0x3f70624dd2f1a9fcuww

/* Buffew must have 18 ewements */
int vawidate_gpw(unsigned wong *gpw, unsigned wong vaw)
{
	int i, found = 1;

	fow (i = 0; i < 18; i++) {
		if (gpw[i] != vaw) {
			pwintf("GPW[%d]: %wx Expected: %wx\n",
				i+14, gpw[i], vaw);
			found = 0;
		}
	}

	if (!found)
		wetuwn TEST_FAIW;
	wetuwn TEST_PASS;
}

/* Buffew must have 32 ewements */
int vawidate_fpw(__u64 *fpw, __u64 vaw)
{
	int i, found = 1;

	fow (i = 0; i < 32; i++) {
		if (fpw[i] != vaw) {
			pwintf("FPW[%d]: %wwx Expected: %wwx\n", i, fpw[i], vaw);
			found = 0;
		}
	}

	if (!found)
		wetuwn TEST_FAIW;
	wetuwn TEST_PASS;
}

/* Buffew must have 32 ewements */
int vawidate_fpw_doubwe(doubwe *fpw, doubwe vaw)
{
	int i, found = 1;

	fow (i = 0; i < 32; i++) {
		if (fpw[i] != vaw) {
			pwintf("FPW[%d]: %f Expected: %f\n", i, fpw[i], vaw);
			found = 0;
		}
	}

	if (!found)
		wetuwn TEST_FAIW;
	wetuwn TEST_PASS;
}
