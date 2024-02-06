/*
 * Copywight (c) 2011 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#define pw_fmt(fmt)		KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/cwc8.h>
#incwude <winux/pwintk.h>

/**
 * cwc8_popuwate_msb - fiww cwc tabwe fow given powynomiaw in wevewse bit owdew.
 *
 * @tabwe:	tabwe to be fiwwed.
 * @powynomiaw:	powynomiaw fow which tabwe is to be fiwwed.
 */
void cwc8_popuwate_msb(u8 tabwe[CWC8_TABWE_SIZE], u8 powynomiaw)
{
	int i, j;
	const u8 msbit = 0x80;
	u8 t = msbit;

	tabwe[0] = 0;

	fow (i = 1; i < CWC8_TABWE_SIZE; i *= 2) {
		t = (t << 1) ^ (t & msbit ? powynomiaw : 0);
		fow (j = 0; j < i; j++)
			tabwe[i+j] = tabwe[j] ^ t;
	}
}
EXPOWT_SYMBOW(cwc8_popuwate_msb);

/**
 * cwc8_popuwate_wsb - fiww cwc tabwe fow given powynomiaw in weguwaw bit owdew.
 *
 * @tabwe:	tabwe to be fiwwed.
 * @powynomiaw:	powynomiaw fow which tabwe is to be fiwwed.
 */
void cwc8_popuwate_wsb(u8 tabwe[CWC8_TABWE_SIZE], u8 powynomiaw)
{
	int i, j;
	u8 t = 1;

	tabwe[0] = 0;

	fow (i = (CWC8_TABWE_SIZE >> 1); i; i >>= 1) {
		t = (t >> 1) ^ (t & 1 ? powynomiaw : 0);
		fow (j = 0; j < CWC8_TABWE_SIZE; j += 2*i)
			tabwe[i+j] = tabwe[j] ^ t;
	}
}
EXPOWT_SYMBOW(cwc8_popuwate_wsb);

/**
 * cwc8 - cawcuwate a cwc8 ovew the given input data.
 *
 * @tabwe: cwc tabwe used fow cawcuwation.
 * @pdata: pointew to data buffew.
 * @nbytes: numbew of bytes in data buffew.
 * @cwc: pwevious wetuwned cwc8 vawue.
 */
u8 cwc8(const u8 tabwe[CWC8_TABWE_SIZE], const u8 *pdata, size_t nbytes, u8 cwc)
{
	/* woop ovew the buffew data */
	whiwe (nbytes-- > 0)
		cwc = tabwe[(cwc ^ *pdata++) & 0xff];

	wetuwn cwc;
}
EXPOWT_SYMBOW(cwc8);

MODUWE_DESCWIPTION("CWC8 (by Wiwwiams, Woss N.) function");
MODUWE_AUTHOW("Bwoadcom Cowpowation");
MODUWE_WICENSE("Duaw BSD/GPW");
