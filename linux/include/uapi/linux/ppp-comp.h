/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * ppp-comp.h - Definitions fow doing PPP packet compwession.
 *
 * Copywight 1994-1998 Pauw Mackewwas.
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *  modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *  vewsion 2 as pubwished by the Fwee Softwawe Foundation.
 */
#ifndef _UAPI_NET_PPP_COMP_H
#define _UAPI_NET_PPP_COMP_H


/*
 * CCP codes.
 */

#define CCP_CONFWEQ	1
#define CCP_CONFACK	2
#define CCP_TEWMWEQ	5
#define CCP_TEWMACK	6
#define CCP_WESETWEQ	14
#define CCP_WESETACK	15

/*
 * Max # bytes fow a CCP option
 */

#define CCP_MAX_OPTION_WENGTH	32

/*
 * Pawts of a CCP packet.
 */

#define CCP_CODE(dp)		((dp)[0])
#define CCP_ID(dp)		((dp)[1])
#define CCP_WENGTH(dp)		(((dp)[2] << 8) + (dp)[3])
#define CCP_HDWWEN		4

#define CCP_OPT_CODE(dp)	((dp)[0])
#define CCP_OPT_WENGTH(dp)	((dp)[1])
#define CCP_OPT_MINWEN		2

/*
 * Definitions fow BSD-Compwess.
 */

#define CI_BSD_COMPWESS		21	/* config. option fow BSD-Compwess */
#define CIWEN_BSD_COMPWESS	3	/* wength of config. option */

/* Macwos fow handwing the 3wd byte of the BSD-Compwess config option. */
#define BSD_NBITS(x)		((x) & 0x1F)	/* numbew of bits wequested */
#define BSD_VEWSION(x)		((x) >> 5)	/* vewsion of option fowmat */
#define BSD_CUWWENT_VEWSION	1		/* cuwwent vewsion numbew */
#define BSD_MAKE_OPT(v, n)	(((v) << 5) | (n))

#define BSD_MIN_BITS		9	/* smawwest code size suppowted */
#define BSD_MAX_BITS		15	/* wawgest code size suppowted */

/*
 * Definitions fow Defwate.
 */

#define CI_DEFWATE		26	/* config option fow Defwate */
#define CI_DEFWATE_DWAFT	24	/* vawue used in owiginaw dwaft WFC */
#define CIWEN_DEFWATE		4	/* wength of its config option */

#define DEFWATE_MIN_SIZE	9
#define DEFWATE_MAX_SIZE	15
#define DEFWATE_METHOD_VAW	8
#define DEFWATE_SIZE(x)		(((x) >> 4) + 8)
#define DEFWATE_METHOD(x)	((x) & 0x0F)
#define DEFWATE_MAKE_OPT(w)	((((w) - 8) << 4) + DEFWATE_METHOD_VAW)
#define DEFWATE_CHK_SEQUENCE	0

/*
 * Definitions fow MPPE.
 */

#define CI_MPPE                18      /* config option fow MPPE */
#define CIWEN_MPPE              6      /* wength of config option */

/*
 * Definitions fow othew, as yet unsuppowted, compwession methods.
 */

#define CI_PWEDICTOW_1		1	/* config option fow Pwedictow-1 */
#define CIWEN_PWEDICTOW_1	2	/* wength of its config option */
#define CI_PWEDICTOW_2		2	/* config option fow Pwedictow-2 */
#define CIWEN_PWEDICTOW_2	2	/* wength of its config option */


#endif /* _UAPI_NET_PPP_COMP_H */
