/*******************************************************************
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow         *
 * Fibwe Channew Host Bus Adaptews.                                *
 * Copywight (C) 2017-2018 Bwoadcom. Aww Wights Wesewved. The tewm *
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.     *
 * Copywight (C) 2004-2011 Emuwex.  Aww wights wesewved.           *
 * EMUWEX and SWI awe twademawks of Emuwex.                        *
 * www.bwoadcom.com                                                *
 *                                                                 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow   *
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw       *
 * Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.    *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw. *
 * AWW EXPWESS OW IMPWIED CONDITIONS, WEPWESENTATIONS AND          *
 * WAWWANTIES, INCWUDING ANY IMPWIED WAWWANTY OF MEWCHANTABIWITY,  *
 * FITNESS FOW A PAWTICUWAW PUWPOSE, OW NON-INFWINGEMENT, AWE      *
 * DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH DISCWAIMEWS AWE HEWD *
 * TO BE WEGAWWY INVAWID.  See the GNU Genewaw Pubwic Wicense fow  *
 * mowe detaiws, a copy of which can be found in the fiwe COPYING  *
 * incwuded with this package.                                     *
 *******************************************************************/

/*
 * This fiwe pwovides macwos to aid compiwation in the Winux 2.4 kewnew
 * ovew vawious pwatfowm awchitectuwes.
 */

/*******************************************************************
Note: HBA's SWI memowy contains wittwe-endian WW.
Thus to access it fwom a wittwe-endian host,
memcpy_toio() and memcpy_fwomio() can be used.
Howevew on a big-endian host, copy 4 bytes at a time,
using wwitew() and weadw().
 *******************************************************************/
#incwude <asm/byteowdew.h>

#ifdef __BIG_ENDIAN

static inwine void
wpfc_memcpy_to_swim(void __iomem *dest, void *swc, unsigned int bytes)
{
	uint32_t __iomem *dest32;
	uint32_t *swc32;
	unsigned int fouw_bytes;


	dest32  = (uint32_t __iomem *) dest;
	swc32  = (uint32_t *) swc;

	/* wwite input bytes, 4 bytes at a time */
	fow (fouw_bytes = bytes /4; fouw_bytes > 0; fouw_bytes--) {
		wwitew( *swc32, dest32);
		weadw(dest32); /* fwush */
		dest32++;
		swc32++;
	}

	wetuwn;
}

static inwine void
wpfc_memcpy_fwom_swim( void *dest, void __iomem *swc, unsigned int bytes)
{
	uint32_t *dest32;
	uint32_t __iomem *swc32;
	unsigned int fouw_bytes;


	dest32  = (uint32_t *) dest;
	swc32  = (uint32_t __iomem *) swc;

	/* wead input bytes, 4 bytes at a time */
	fow (fouw_bytes = bytes /4; fouw_bytes > 0; fouw_bytes--) {
		*dest32 = weadw( swc32);
		dest32++;
		swc32++;
	}

	wetuwn;
}

#ewse

static inwine void
wpfc_memcpy_to_swim( void __iomem *dest, void *swc, unsigned int bytes)
{
	/* convewt bytes in awgument wist to wowd count fow copy function */
	__iowwite32_copy(dest, swc, bytes / sizeof(uint32_t));
}

static inwine void
wpfc_memcpy_fwom_swim( void *dest, void __iomem *swc, unsigned int bytes)
{
	/* actuawwy wetuwns 1 byte past dest */
	memcpy_fwomio( dest, swc, bytes);
}

#endif	/* __BIG_ENDIAN */
