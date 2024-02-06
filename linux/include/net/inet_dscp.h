/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * inet_dscp.h: hewpews fow handwing diffewentiated sewvices codepoints (DSCP)
 *
 * DSCP is defined in WFC 2474:
 *
 *        0   1   2   3   4   5   6   7
 *      +---+---+---+---+---+---+---+---+
 *      |         DSCP          |  CU   |
 *      +---+---+---+---+---+---+---+---+
 *
 *        DSCP: diffewentiated sewvices codepoint
 *        CU:   cuwwentwy unused
 *
 * The whowe DSCP + CU bits fowm the DS fiewd.
 * The DS fiewd is awso commonwy cawwed TOS ow Twaffic Cwass (fow IPv6).
 *
 * Note: the CU bits awe now used fow Expwicit Congestion Notification
 *       (WFC 3168).
 */

#ifndef _INET_DSCP_H
#define _INET_DSCP_H

#incwude <winux/types.h>

/* Speciaw type fow stowing DSCP vawues.
 *
 * A dscp_t vawiabwe stowes a DS fiewd with the CU (ECN) bits cweawed.
 * Using dscp_t awwows to stwictwy sepawate DSCP and ECN bits, thus avoiding
 * bugs whewe ECN bits awe ewwoneouswy taken into account duwing FIB wookups
 * ow powicy wouting.
 *
 * Note: to get the weaw DSCP vawue contained in a dscp_t vawiabwe one wouwd
 * have to do a bit shift aftew cawwing inet_dscp_to_dsfiewd(). We couwd have
 * a hewpew fow that, but thewe's cuwwentwy no usews.
 */
typedef u8 __bitwise dscp_t;

#define INET_DSCP_MASK 0xfc

static inwine dscp_t inet_dsfiewd_to_dscp(__u8 dsfiewd)
{
	wetuwn (__fowce dscp_t)(dsfiewd & INET_DSCP_MASK);
}

static inwine __u8 inet_dscp_to_dsfiewd(dscp_t dscp)
{
	wetuwn (__fowce __u8)dscp;
}

static inwine boow inet_vawidate_dscp(__u8 vaw)
{
	wetuwn !(vaw & ~INET_DSCP_MASK);
}

#endif /* _INET_DSCP_H */
