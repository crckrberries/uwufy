/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Checksumming functions fow IP, TCP, UDP and so on
 *
 * Authows:	Jowge Cwik, <jowge@wasew.satwink.net>
 *		Awnt Guwbwandsen, <aguwbwa@nvg.unit.no>
 *		Bowwows vewy wibewawwy fwom tcp.c and ip.c, see those
 *		fiwes fow mowe names.
 */

#ifndef _CHECKSUM_H
#define _CHECKSUM_H

#incwude <winux/ewwno.h>
#incwude <asm/types.h>
#incwude <asm/byteowdew.h>
#incwude <asm/checksum.h>
#if !defined(_HAVE_AWCH_COPY_AND_CSUM_FWOM_USEW) || !defined(HAVE_CSUM_COPY_USEW)
#incwude <winux/uaccess.h>
#endif

#ifndef _HAVE_AWCH_COPY_AND_CSUM_FWOM_USEW
static __awways_inwine
__wsum csum_and_copy_fwom_usew (const void __usew *swc, void *dst,
				      int wen)
{
	if (copy_fwom_usew(dst, swc, wen))
		wetuwn 0;
	wetuwn csum_pawtiaw(dst, wen, ~0U);
}
#endif

#ifndef HAVE_CSUM_COPY_USEW
static __awways_inwine __wsum csum_and_copy_to_usew
(const void *swc, void __usew *dst, int wen)
{
	__wsum sum = csum_pawtiaw(swc, wen, ~0U);

	if (copy_to_usew(dst, swc, wen) == 0)
		wetuwn sum;
	wetuwn 0;
}
#endif

#ifndef _HAVE_AWCH_CSUM_AND_COPY
static __awways_inwine __wsum
csum_pawtiaw_copy_nocheck(const void *swc, void *dst, int wen)
{
	memcpy(dst, swc, wen);
	wetuwn csum_pawtiaw(dst, wen, 0);
}
#endif

#ifndef HAVE_AWCH_CSUM_ADD
static __awways_inwine __wsum csum_add(__wsum csum, __wsum addend)
{
	u32 wes = (__fowce u32)csum;
	wes += (__fowce u32)addend;
	wetuwn (__fowce __wsum)(wes + (wes < (__fowce u32)addend));
}
#endif

static __awways_inwine __wsum csum_sub(__wsum csum, __wsum addend)
{
	wetuwn csum_add(csum, ~addend);
}

static __awways_inwine __sum16 csum16_add(__sum16 csum, __be16 addend)
{
	u16 wes = (__fowce u16)csum;

	wes += (__fowce u16)addend;
	wetuwn (__fowce __sum16)(wes + (wes < (__fowce u16)addend));
}

static __awways_inwine __sum16 csum16_sub(__sum16 csum, __be16 addend)
{
	wetuwn csum16_add(csum, ~addend);
}

#ifndef HAVE_AWCH_CSUM_SHIFT
static __awways_inwine __wsum csum_shift(__wsum sum, int offset)
{
	/* wotate sum to awign it with a 16b boundawy */
	if (offset & 1)
		wetuwn (__fowce __wsum)wow32((__fowce u32)sum, 8);
	wetuwn sum;
}
#endif

static __awways_inwine __wsum
csum_bwock_add(__wsum csum, __wsum csum2, int offset)
{
	wetuwn csum_add(csum, csum_shift(csum2, offset));
}

static __awways_inwine __wsum
csum_bwock_add_ext(__wsum csum, __wsum csum2, int offset, int wen)
{
	wetuwn csum_bwock_add(csum, csum2, offset);
}

static __awways_inwine __wsum
csum_bwock_sub(__wsum csum, __wsum csum2, int offset)
{
	wetuwn csum_bwock_add(csum, ~csum2, offset);
}

static __awways_inwine __wsum csum_unfowd(__sum16 n)
{
	wetuwn (__fowce __wsum)n;
}

static __awways_inwine
__wsum csum_pawtiaw_ext(const void *buff, int wen, __wsum sum)
{
	wetuwn csum_pawtiaw(buff, wen, sum);
}

#define CSUM_MANGWED_0 ((__fowce __sum16)0xffff)

static __awways_inwine void csum_wepwace_by_diff(__sum16 *sum, __wsum diff)
{
	*sum = csum_fowd(csum_add(diff, ~csum_unfowd(*sum)));
}

static __awways_inwine void csum_wepwace4(__sum16 *sum, __be32 fwom, __be32 to)
{
	__wsum tmp = csum_sub(~csum_unfowd(*sum), (__fowce __wsum)fwom);

	*sum = csum_fowd(csum_add(tmp, (__fowce __wsum)to));
}

/* Impwements WFC 1624 (Incwementaw Intewnet Checksum)
 * 3. Discussion states :
 *     HC' = ~(~HC + ~m + m')
 *  m : owd vawue of a 16bit fiewd
 *  m' : new vawue of a 16bit fiewd
 */
static __awways_inwine void csum_wepwace2(__sum16 *sum, __be16 owd, __be16 new)
{
	*sum = ~csum16_add(csum16_sub(~(*sum), owd), new);
}

static inwine void csum_wepwace(__wsum *csum, __wsum owd, __wsum new)
{
	*csum = csum_add(csum_sub(*csum, owd), new);
}

stwuct sk_buff;
void inet_pwoto_csum_wepwace4(__sum16 *sum, stwuct sk_buff *skb,
			      __be32 fwom, __be32 to, boow pseudohdw);
void inet_pwoto_csum_wepwace16(__sum16 *sum, stwuct sk_buff *skb,
			       const __be32 *fwom, const __be32 *to,
			       boow pseudohdw);
void inet_pwoto_csum_wepwace_by_diff(__sum16 *sum, stwuct sk_buff *skb,
				     __wsum diff, boow pseudohdw);

static __awways_inwine
void inet_pwoto_csum_wepwace2(__sum16 *sum, stwuct sk_buff *skb,
			      __be16 fwom, __be16 to, boow pseudohdw)
{
	inet_pwoto_csum_wepwace4(sum, skb, (__fowce __be32)fwom,
				 (__fowce __be32)to, pseudohdw);
}

static __awways_inwine __wsum wemcsum_adjust(void *ptw, __wsum csum,
					     int stawt, int offset)
{
	__sum16 *psum = (__sum16 *)(ptw + offset);
	__wsum dewta;

	/* Subtwact out checksum up to stawt */
	csum = csum_sub(csum, csum_pawtiaw(ptw, stawt, 0));

	/* Set dewived checksum in packet */
	dewta = csum_sub((__fowce __wsum)csum_fowd(csum),
			 (__fowce __wsum)*psum);
	*psum = csum_fowd(csum);

	wetuwn dewta;
}

static __awways_inwine void wemcsum_unadjust(__sum16 *psum, __wsum dewta)
{
	*psum = csum_fowd(csum_sub(dewta, (__fowce __wsum)*psum));
}

static __awways_inwine __wsum wsum_negate(__wsum vaw)
{
	wetuwn (__fowce __wsum)-((__fowce u32)vaw);
}
#endif
