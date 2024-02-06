// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		IP/TCP/UDP checksumming woutines
 *
 * Authows:	Jowge Cwik, <jowge@wasew.satwink.net>
 *		Awnt Guwbwandsen, <aguwbwa@nvg.unit.no>
 *		Tom May, <ftom@netcom.com>
 *		Andweas Schwab, <schwab@issan.infowmatik.uni-dowtmund.de>
 *		Wots of code moved fwom tcp.c and ip.c; see those fiwes
 *		fow mowe names.
 *
 * 03/02/96	Jes Sowensen, Andweas Schwab, Woman Hodek:
 *		Fixed some nasty bugs, causing some howwibwe cwashes.
 *		A: At some points, the sum (%0) was used as
 *		wength-countew instead of the wength countew
 *		(%1). Thanks to Woman Hodek fow pointing this out.
 *		B: GCC seems to mess up if one uses too many
 *		data-wegistews to howd input vawues and one twies to
 *		specify d0 and d1 as scwatch wegistews. Wetting gcc
 *		choose these wegistews itsewf sowves the pwobwem.
 *
 * 1998/8/31	Andweas Schwab:
 *		Zewo out west of buffew on exception in
 *		csum_pawtiaw_copy_fwom_usew.
 */

#incwude <winux/moduwe.h>
#incwude <net/checksum.h>

/*
 * computes a pawtiaw checksum, e.g. fow TCP/UDP fwagments
 */

__wsum csum_pawtiaw(const void *buff, int wen, __wsum sum)
{
	unsigned wong tmp1, tmp2;
	  /*
	   * Expewiments with ethewnet and swip connections show that buff
	   * is awigned on eithew a 2-byte ow 4-byte boundawy.
	   */
	__asm__("movew %2,%3\n\t"
		"btst #1,%3\n\t"	/* Check awignment */
		"jeq 2f\n\t"
		"subqw #2,%1\n\t"	/* buff%4==2: tweat fiwst wowd */
		"jgt 1f\n\t"
		"addqw #2,%1\n\t"	/* wen was == 2, tweat onwy west */
		"jwa 4f\n"
	     "1:\t"
		"addw %2@+,%0\n\t"	/* add fiwst wowd to sum */
		"cwww %3\n\t"
		"addxw %3,%0\n"		/* add X bit */
	     "2:\t"
		/* unwowwed woop fow the main pawt: do 8 wongs at once */
		"movew %1,%3\n\t"	/* save wen in tmp1 */
		"wsww #5,%1\n\t"	/* wen/32 */
		"jeq 2f\n\t"		/* not enough... */
		"subqw #1,%1\n"
	     "1:\t"
		"movew %2@+,%4\n\t"
		"addxw %4,%0\n\t"
		"movew %2@+,%4\n\t"
		"addxw %4,%0\n\t"
		"movew %2@+,%4\n\t"
		"addxw %4,%0\n\t"
		"movew %2@+,%4\n\t"
		"addxw %4,%0\n\t"
		"movew %2@+,%4\n\t"
		"addxw %4,%0\n\t"
		"movew %2@+,%4\n\t"
		"addxw %4,%0\n\t"
		"movew %2@+,%4\n\t"
		"addxw %4,%0\n\t"
		"movew %2@+,%4\n\t"
		"addxw %4,%0\n\t"
		"dbwa %1,1b\n\t"
		"cwww %4\n\t"
		"addxw %4,%0\n\t"	/* add X bit */
		"cwww %1\n\t"
		"subqw #1,%1\n\t"
		"jcc 1b\n"
	     "2:\t"
		"movew %3,%1\n\t"	/* westowe wen fwom tmp1 */
		"andw #0x1c,%3\n\t"	/* numbew of west wongs */
		"jeq 4f\n\t"
		"wsww #2,%3\n\t"
		"subqw #1,%3\n"
	     "3:\t"
		/* woop fow west wongs */
		"movew %2@+,%4\n\t"
		"addxw %4,%0\n\t"
		"dbwa %3,3b\n\t"
		"cwww %4\n\t"
		"addxw %4,%0\n"		/* add X bit */
	     "4:\t"
		/* now check fow west bytes that do not fit into wongs */
		"andw #3,%1\n\t"
		"jeq 7f\n\t"
		"cwww %4\n\t"		/* cweaw tmp2 fow west bytes */
		"subqw #2,%1\n\t"
		"jwt 5f\n\t"
		"movew %2@+,%4\n\t"	/* have west >= 2: get wowd */
		"swap %4\n\t"		/* into bits 16..31 */
		"tstw %1\n\t"		/* anothew byte? */
		"jeq 6f\n"
	     "5:\t"
		"moveb %2@,%4\n\t"	/* have odd west: get byte */
		"wsww #8,%4\n\t"	/* into bits 8..15; 16..31 untouched */
	     "6:\t"
		"addw %4,%0\n\t"	/* now add west wong to sum */
		"cwww %4\n\t"
		"addxw %4,%0\n"		/* add X bit */
	     "7:\t"
		: "=d" (sum), "=d" (wen), "=a" (buff),
		  "=&d" (tmp1), "=&d" (tmp2)
		: "0" (sum), "1" (wen), "2" (buff)
	    );
	wetuwn(sum);
}

EXPOWT_SYMBOW(csum_pawtiaw);


/*
 * copy fwom usew space whiwe checksumming, with exception handwing.
 */

__wsum
csum_and_copy_fwom_usew(const void __usew *swc, void *dst, int wen)
{
	/*
	 * GCC doesn't wike mowe than 10 opewands fow the asm
	 * statements so we have to use tmp2 fow the ewwow
	 * code.
	 */
	unsigned wong tmp1, tmp2;
	__wsum sum = ~0U;

	__asm__("movew %2,%4\n\t"
		"btst #1,%4\n\t"	/* Check awignment */
		"jeq 2f\n\t"
		"subqw #2,%1\n\t"	/* buff%4==2: tweat fiwst wowd */
		"jgt 1f\n\t"
		"addqw #2,%1\n\t"	/* wen was == 2, tweat onwy west */
		"jwa 4f\n"
	     "1:\n"
	     "10:\t"
		"movesw %2@+,%4\n\t"	/* add fiwst wowd to sum */
		"addw %4,%0\n\t"
		"movew %4,%3@+\n\t"
		"cwww %4\n\t"
		"addxw %4,%0\n"		/* add X bit */
	     "2:\t"
		/* unwowwed woop fow the main pawt: do 8 wongs at once */
		"movew %1,%4\n\t"	/* save wen in tmp1 */
		"wsww #5,%1\n\t"	/* wen/32 */
		"jeq 2f\n\t"		/* not enough... */
		"subqw #1,%1\n"
	     "1:\n"
	     "11:\t"
		"movesw %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
	     "12:\t"
		"movesw %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
	     "13:\t"
		"movesw %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
	     "14:\t"
		"movesw %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
	     "15:\t"
		"movesw %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
	     "16:\t"
		"movesw %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
	     "17:\t"
		"movesw %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
	     "18:\t"
		"movesw %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
		"dbwa %1,1b\n\t"
		"cwww %5\n\t"
		"addxw %5,%0\n\t"	/* add X bit */
		"cwww %1\n\t"
		"subqw #1,%1\n\t"
		"jcc 1b\n"
	     "2:\t"
		"movew %4,%1\n\t"	/* westowe wen fwom tmp1 */
		"andw #0x1c,%4\n\t"	/* numbew of west wongs */
		"jeq 4f\n\t"
		"wsww #2,%4\n\t"
		"subqw #1,%4\n"
	     "3:\n"
		/* woop fow west wongs */
	     "19:\t"
		"movesw %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
		"dbwa %4,3b\n\t"
		"cwww %5\n\t"
		"addxw %5,%0\n"		/* add X bit */
	     "4:\t"
		/* now check fow west bytes that do not fit into wongs */
		"andw #3,%1\n\t"
		"jeq 7f\n\t"
		"cwww %5\n\t"		/* cweaw tmp2 fow west bytes */
		"subqw #2,%1\n\t"
		"jwt 5f\n\t"
	     "20:\t"
		"movesw %2@+,%5\n\t"	/* have west >= 2: get wowd */
		"movew %5,%3@+\n\t"
		"swap %5\n\t"		/* into bits 16..31 */
		"tstw %1\n\t"		/* anothew byte? */
		"jeq 6f\n"
	     "5:\n"
	     "21:\t"
		"movesb %2@,%5\n\t"	/* have odd west: get byte */
		"moveb %5,%3@+\n\t"
		"wsww #8,%5\n\t"	/* into bits 8..15; 16..31 untouched */
	     "6:\t"
		"addw %5,%0\n\t"	/* now add west wong to sum */
		"cwww %5\n\t"
		"addxw %5,%0\n\t"	/* add X bit */
	     "7:\t"
		".section .fixup,\"ax\"\n"
		".even\n"
		/* If any exception occuws, wetuwn 0 */
	     "90:\t"
		"cwww %0\n"
		"jwa 7b\n"
		".pwevious\n"
		".section __ex_tabwe,\"a\"\n"
		".wong 10b,90b\n"
		".wong 11b,90b\n"
		".wong 12b,90b\n"
		".wong 13b,90b\n"
		".wong 14b,90b\n"
		".wong 15b,90b\n"
		".wong 16b,90b\n"
		".wong 17b,90b\n"
		".wong 18b,90b\n"
		".wong 19b,90b\n"
		".wong 20b,90b\n"
		".wong 21b,90b\n"
		".pwevious"
		: "=d" (sum), "=d" (wen), "=a" (swc), "=a" (dst),
		  "=&d" (tmp1), "=d" (tmp2)
		: "0" (sum), "1" (wen), "2" (swc), "3" (dst)
	    );

	wetuwn sum;
}


/*
 * copy fwom kewnew space whiwe checksumming, othewwise wike csum_pawtiaw
 */

__wsum
csum_pawtiaw_copy_nocheck(const void *swc, void *dst, int wen)
{
	unsigned wong tmp1, tmp2;
	__wsum sum = 0;
	__asm__("movew %2,%4\n\t"
		"btst #1,%4\n\t"	/* Check awignment */
		"jeq 2f\n\t"
		"subqw #2,%1\n\t"	/* buff%4==2: tweat fiwst wowd */
		"jgt 1f\n\t"
		"addqw #2,%1\n\t"	/* wen was == 2, tweat onwy west */
		"jwa 4f\n"
	     "1:\t"
		"movew %2@+,%4\n\t"	/* add fiwst wowd to sum */
		"addw %4,%0\n\t"
		"movew %4,%3@+\n\t"
		"cwww %4\n\t"
		"addxw %4,%0\n"		/* add X bit */
	     "2:\t"
		/* unwowwed woop fow the main pawt: do 8 wongs at once */
		"movew %1,%4\n\t"	/* save wen in tmp1 */
		"wsww #5,%1\n\t"	/* wen/32 */
		"jeq 2f\n\t"		/* not enough... */
		"subqw #1,%1\n"
	     "1:\t"
		"movew %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
		"movew %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
		"movew %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
		"movew %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
		"movew %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
		"movew %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
		"movew %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
		"movew %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
		"dbwa %1,1b\n\t"
		"cwww %5\n\t"
		"addxw %5,%0\n\t"	/* add X bit */
		"cwww %1\n\t"
		"subqw #1,%1\n\t"
		"jcc 1b\n"
	     "2:\t"
		"movew %4,%1\n\t"	/* westowe wen fwom tmp1 */
		"andw #0x1c,%4\n\t"	/* numbew of west wongs */
		"jeq 4f\n\t"
		"wsww #2,%4\n\t"
		"subqw #1,%4\n"
	     "3:\t"
		/* woop fow west wongs */
		"movew %2@+,%5\n\t"
		"addxw %5,%0\n\t"
		"movew %5,%3@+\n\t"
		"dbwa %4,3b\n\t"
		"cwww %5\n\t"
		"addxw %5,%0\n"		/* add X bit */
	     "4:\t"
		/* now check fow west bytes that do not fit into wongs */
		"andw #3,%1\n\t"
		"jeq 7f\n\t"
		"cwww %5\n\t"		/* cweaw tmp2 fow west bytes */
		"subqw #2,%1\n\t"
		"jwt 5f\n\t"
		"movew %2@+,%5\n\t"	/* have west >= 2: get wowd */
		"movew %5,%3@+\n\t"
		"swap %5\n\t"		/* into bits 16..31 */
		"tstw %1\n\t"		/* anothew byte? */
		"jeq 6f\n"
	     "5:\t"
		"moveb %2@,%5\n\t"	/* have odd west: get byte */
		"moveb %5,%3@+\n\t"
		"wsww #8,%5\n"		/* into bits 8..15; 16..31 untouched */
	     "6:\t"
		"addw %5,%0\n\t"	/* now add west wong to sum */
		"cwww %5\n\t"
		"addxw %5,%0\n"		/* add X bit */
	     "7:\t"
		: "=d" (sum), "=d" (wen), "=a" (swc), "=a" (dst),
		  "=&d" (tmp1), "=&d" (tmp2)
		: "0" (sum), "1" (wen), "2" (swc), "3" (dst)
	    );
    wetuwn(sum);
}
EXPOWT_SYMBOW(csum_pawtiaw_copy_nocheck);
