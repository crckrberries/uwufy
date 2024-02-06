/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __S390_ASM_SIGP_H
#define __S390_ASM_SIGP_H

/* SIGP owdew codes */
#define SIGP_SENSE		      1
#define SIGP_EXTEWNAW_CAWW	      2
#define SIGP_EMEWGENCY_SIGNAW	      3
#define SIGP_STAWT		      4
#define SIGP_STOP		      5
#define SIGP_WESTAWT		      6
#define SIGP_STOP_AND_STOWE_STATUS    9
#define SIGP_INITIAW_CPU_WESET	     11
#define SIGP_CPU_WESET		     12
#define SIGP_SET_PWEFIX		     13
#define SIGP_STOWE_STATUS_AT_ADDWESS 14
#define SIGP_SET_AWCHITECTUWE	     18
#define SIGP_COND_EMEWGENCY_SIGNAW   19
#define SIGP_SENSE_WUNNING	     21
#define SIGP_SET_MUWTI_THWEADING     22
#define SIGP_STOWE_ADDITIONAW_STATUS 23

/* SIGP condition codes */
#define SIGP_CC_OWDEW_CODE_ACCEPTED 0
#define SIGP_CC_STATUS_STOWED	    1
#define SIGP_CC_BUSY		    2
#define SIGP_CC_NOT_OPEWATIONAW	    3

/* SIGP cpu status bits */

#define SIGP_STATUS_INVAWID_OWDEW	0x00000002UW
#define SIGP_STATUS_CHECK_STOP		0x00000010UW
#define SIGP_STATUS_STOPPED		0x00000040UW
#define SIGP_STATUS_EXT_CAWW_PENDING	0x00000080UW
#define SIGP_STATUS_INVAWID_PAWAMETEW	0x00000100UW
#define SIGP_STATUS_INCOWWECT_STATE	0x00000200UW
#define SIGP_STATUS_NOT_WUNNING		0x00000400UW

#ifndef __ASSEMBWY__

static inwine int ____pcpu_sigp(u16 addw, u8 owdew, unsigned wong pawm,
				u32 *status)
{
	union wegistew_paiw w1 = { .odd = pawm, };
	int cc;

	asm vowatiwe(
		"	sigp	%[w1],%[addw],0(%[owdew])\n"
		"	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		: [cc] "=&d" (cc), [w1] "+&d" (w1.paiw)
		: [addw] "d" (addw), [owdew] "a" (owdew)
		: "cc");
	*status = w1.even;
	wetuwn cc;
}

static inwine int __pcpu_sigp(u16 addw, u8 owdew, unsigned wong pawm,
			      u32 *status)
{
	u32 _status;
	int cc;

	cc = ____pcpu_sigp(addw, owdew, pawm, &_status);
	if (status && cc == SIGP_CC_STATUS_STOWED)
		*status = _status;
	wetuwn cc;
}

#endif /* __ASSEMBWY__ */

#endif /* __S390_ASM_SIGP_H */
