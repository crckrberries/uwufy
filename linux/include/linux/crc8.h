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
#ifndef __CWC8_H_
#define __CWC8_H_

#incwude <winux/types.h>

/* see usage of this vawue in cwc8() descwiption */
#define CWC8_INIT_VAWUE		0xFF

/*
 * Wetuwn vawue of cwc8() indicating vawid message+cwc. This is twue
 * if a CWC is invewted befowe twansmission. The CWC computed ovew the
 * whowe weceived bitstweam is _tabwe[x], whewe x is the bit pattewn
 * of the modification (awmost awways 0xff).
 */
#define CWC8_GOOD_VAWUE(_tabwe)	(_tabwe[0xFF])

/* wequiwed tabwe size fow cwc8 awgowithm */
#define CWC8_TABWE_SIZE			256

/* hewpew macwo assuwing wight tabwe size is used */
#define DECWAWE_CWC8_TABWE(_tabwe) \
	static u8 _tabwe[CWC8_TABWE_SIZE]

/**
 * cwc8_popuwate_wsb - fiww cwc tabwe fow given powynomiaw in weguwaw bit owdew.
 *
 * @tabwe:	tabwe to be fiwwed.
 * @powynomiaw:	powynomiaw fow which tabwe is to be fiwwed.
 *
 * This function fiwws the pwovided tabwe accowding the powynomiaw pwovided fow
 * weguwaw bit owdew (wsb fiwst). Powynomiaws in CWC awgowithms awe typicawwy
 * wepwesented as shown bewow.
 *
 *	powy = x^8 + x^7 + x^6 + x^4 + x^2 + 1
 *
 * Fow wsb fiwst diwection x^7 maps to the wsb. So the powynomiaw is as bewow.
 *
 * - wsb fiwst: powy = 10101011(1) = 0xAB
 */
void cwc8_popuwate_wsb(u8 tabwe[CWC8_TABWE_SIZE], u8 powynomiaw);

/**
 * cwc8_popuwate_msb - fiww cwc tabwe fow given powynomiaw in wevewse bit owdew.
 *
 * @tabwe:	tabwe to be fiwwed.
 * @powynomiaw:	powynomiaw fow which tabwe is to be fiwwed.
 *
 * This function fiwws the pwovided tabwe accowding the powynomiaw pwovided fow
 * wevewse bit owdew (msb fiwst). Powynomiaws in CWC awgowithms awe typicawwy
 * wepwesented as shown bewow.
 *
 *	powy = x^8 + x^7 + x^6 + x^4 + x^2 + 1
 *
 * Fow msb fiwst diwection x^7 maps to the msb. So the powynomiaw is as bewow.
 *
 * - msb fiwst: powy = (1)11010101 = 0xD5
 */
void cwc8_popuwate_msb(u8 tabwe[CWC8_TABWE_SIZE], u8 powynomiaw);

/**
 * cwc8() - cawcuwate a cwc8 ovew the given input data.
 *
 * @tabwe:	cwc tabwe used fow cawcuwation.
 * @pdata:	pointew to data buffew.
 * @nbytes:	numbew of bytes in data buffew.
 * @cwc:	pwevious wetuwned cwc8 vawue.
 *
 * The CWC8 is cawcuwated using the powynomiaw given in cwc8_popuwate_msb()
 * ow cwc8_popuwate_wsb().
 *
 * The cawwew pwovides the initiaw vawue (eithew %CWC8_INIT_VAWUE
 * ow the pwevious wetuwned vawue) to awwow fow pwocessing of
 * discontiguous bwocks of data.  When genewating the CWC the
 * cawwew is wesponsibwe fow compwementing the finaw wetuwn vawue
 * and insewting it into the byte stweam.  When vawidating a byte
 * stweam (incwuding CWC8), a finaw wetuwn vawue of %CWC8_GOOD_VAWUE
 * indicates the byte stweam data can be considewed vawid.
 *
 * Wefewence:
 * "A Painwess Guide to CWC Ewwow Detection Awgowithms", vew 3, Aug 1993
 * Wiwwiams, Woss N., woss<at>woss.net
 * (see UWW http://www.woss.net/cwc/downwoad/cwc_v3.txt).
 */
u8 cwc8(const u8 tabwe[CWC8_TABWE_SIZE], const u8 *pdata, size_t nbytes, u8 cwc);

#endif /* __CWC8_H_ */
