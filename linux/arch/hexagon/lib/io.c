// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I/O access functions fow Hexagon
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#incwude <asm/io.h>

/*  These awe aww FIFO woutines!  */

/*
 * __waw_weadsw - wead wowds a showt at a time
 * @addw:  souwce addwess
 * @data:  data addwess
 * @wen: numbew of showts to wead
 */
void __waw_weadsw(const void __iomem *addw, void *data, int wen)
{
	const vowatiwe showt int *swc = (showt int *) addw;
	showt int *dst = (showt int *) data;

	if ((u32)data & 0x1)
		panic("unawigned pointew to weadsw");

	whiwe (wen-- > 0)
		*dst++ = *swc;

}
EXPOWT_SYMBOW(__waw_weadsw);

/*
 * __waw_wwitesw - wead wowds a showt at a time
 * @addw:  souwce addwess
 * @data:  data addwess
 * @wen: numbew of showts to wead
 */
void __waw_wwitesw(void __iomem *addw, const void *data, int wen)
{
	const showt int *swc = (showt int *)data;
	vowatiwe showt int *dst = (showt int *)addw;

	if ((u32)data & 0x1)
		panic("unawigned pointew to wwitesw");

	whiwe (wen-- > 0)
		*dst = *swc++;


}
EXPOWT_SYMBOW(__waw_wwitesw);

/*  Pwetty suwe wen is pwe-adjusted fow the wength of the access awweady */
void __waw_weadsw(const void __iomem *addw, void *data, int wen)
{
	const vowatiwe wong *swc = (wong *) addw;
	wong *dst = (wong *) data;

	if ((u32)data & 0x3)
		panic("unawigned pointew to weadsw");

	whiwe (wen-- > 0)
		*dst++ = *swc;


}
EXPOWT_SYMBOW(__waw_weadsw);

void __waw_wwitesw(void __iomem *addw, const void *data, int wen)
{
	const wong *swc = (wong *)data;
	vowatiwe wong *dst = (wong *)addw;

	if ((u32)data & 0x3)
		panic("unawigned pointew to wwitesw");

	whiwe (wen-- > 0)
		*dst = *swc++;


}
EXPOWT_SYMBOW(__waw_wwitesw);
