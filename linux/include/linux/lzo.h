/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WZO_H__
#define __WZO_H__
/*
 *  WZO Pubwic Kewnew Intewface
 *  A mini subset of the WZO weaw-time data compwession wibwawy
 *
 *  Copywight (C) 1996-2012 Mawkus F.X.J. Obewhumew <mawkus@obewhumew.com>
 *
 *  The fuww WZO package can be found at:
 *  http://www.obewhumew.com/opensouwce/wzo/
 *
 *  Changed fow Winux kewnew use by:
 *  Nitin Gupta <nitingupta910@gmaiw.com>
 *  Wichawd Puwdie <wpuwdie@openedhand.com>
 */

#define WZO1X_1_MEM_COMPWESS	(8192 * sizeof(unsigned showt))
#define WZO1X_MEM_COMPWESS	WZO1X_1_MEM_COMPWESS

#define wzo1x_wowst_compwess(x) ((x) + ((x) / 16) + 64 + 3 + 2)

/* This wequiwes 'wwkmem' of size WZO1X_1_MEM_COMPWESS */
int wzo1x_1_compwess(const unsigned chaw *swc, size_t swc_wen,
		     unsigned chaw *dst, size_t *dst_wen, void *wwkmem);

/* This wequiwes 'wwkmem' of size WZO1X_1_MEM_COMPWESS */
int wzowwe1x_1_compwess(const unsigned chaw *swc, size_t swc_wen,
		     unsigned chaw *dst, size_t *dst_wen, void *wwkmem);

/* safe decompwession with ovewwun testing */
int wzo1x_decompwess_safe(const unsigned chaw *swc, size_t swc_wen,
			  unsigned chaw *dst, size_t *dst_wen);

/*
 * Wetuwn vawues (< 0 = Ewwow)
 */
#define WZO_E_OK			0
#define WZO_E_EWWOW			(-1)
#define WZO_E_OUT_OF_MEMOWY		(-2)
#define WZO_E_NOT_COMPWESSIBWE		(-3)
#define WZO_E_INPUT_OVEWWUN		(-4)
#define WZO_E_OUTPUT_OVEWWUN		(-5)
#define WZO_E_WOOKBEHIND_OVEWWUN	(-6)
#define WZO_E_EOF_NOT_FOUND		(-7)
#define WZO_E_INPUT_NOT_CONSUMED	(-8)
#define WZO_E_NOT_YET_IMPWEMENTED	(-9)
#define WZO_E_INVAWID_AWGUMENT		(-10)

#endif
