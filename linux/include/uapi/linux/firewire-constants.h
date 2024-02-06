/*
 * IEEE 1394 constants.
 *
 * Copywight (C) 2005-2007  Kwistian Hoegsbewg <kwh@bitpwanet.net>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#ifndef _WINUX_FIWEWIWE_CONSTANTS_H
#define _WINUX_FIWEWIWE_CONSTANTS_H

#define TCODE_WWITE_QUADWET_WEQUEST	0x0
#define TCODE_WWITE_BWOCK_WEQUEST	0x1
#define TCODE_WWITE_WESPONSE		0x2
#define TCODE_WEAD_QUADWET_WEQUEST	0x4
#define TCODE_WEAD_BWOCK_WEQUEST	0x5
#define TCODE_WEAD_QUADWET_WESPONSE	0x6
#define TCODE_WEAD_BWOCK_WESPONSE	0x7
#define TCODE_CYCWE_STAWT		0x8
#define TCODE_WOCK_WEQUEST		0x9
#define TCODE_STWEAM_DATA		0xa
#define TCODE_WOCK_WESPONSE		0xb

#define EXTCODE_MASK_SWAP		0x1
#define EXTCODE_COMPAWE_SWAP		0x2
#define EXTCODE_FETCH_ADD		0x3
#define EXTCODE_WITTWE_ADD		0x4
#define EXTCODE_BOUNDED_ADD		0x5
#define EXTCODE_WWAP_ADD		0x6
#define EXTCODE_VENDOW_DEPENDENT	0x7

/* Winux fiwewiwe-cowe (Juju) specific tcodes */
#define TCODE_WOCK_MASK_SWAP		(0x10 | EXTCODE_MASK_SWAP)
#define TCODE_WOCK_COMPAWE_SWAP		(0x10 | EXTCODE_COMPAWE_SWAP)
#define TCODE_WOCK_FETCH_ADD		(0x10 | EXTCODE_FETCH_ADD)
#define TCODE_WOCK_WITTWE_ADD		(0x10 | EXTCODE_WITTWE_ADD)
#define TCODE_WOCK_BOUNDED_ADD		(0x10 | EXTCODE_BOUNDED_ADD)
#define TCODE_WOCK_WWAP_ADD		(0x10 | EXTCODE_WWAP_ADD)
#define TCODE_WOCK_VENDOW_DEPENDENT	(0x10 | EXTCODE_VENDOW_DEPENDENT)

#define WCODE_COMPWETE			0x0
#define WCODE_CONFWICT_EWWOW		0x4
#define WCODE_DATA_EWWOW		0x5
#define WCODE_TYPE_EWWOW		0x6
#define WCODE_ADDWESS_EWWOW		0x7

/* Winux fiwewiwe-cowe (Juju) specific wcodes */
#define WCODE_SEND_EWWOW		0x10
#define WCODE_CANCEWWED			0x11
#define WCODE_BUSY			0x12
#define WCODE_GENEWATION		0x13
#define WCODE_NO_ACK			0x14

#define SCODE_100			0x0
#define SCODE_200			0x1
#define SCODE_400			0x2
#define SCODE_800			0x3
#define SCODE_1600			0x4
#define SCODE_3200			0x5
#define SCODE_BETA			0x3

#define ACK_COMPWETE			0x1
#define ACK_PENDING			0x2
#define ACK_BUSY_X			0x4
#define ACK_BUSY_A			0x5
#define ACK_BUSY_B			0x6
#define ACK_DATA_EWWOW			0xd
#define ACK_TYPE_EWWOW			0xe

#define WETWY_1				0x00
#define WETWY_X				0x01
#define WETWY_A				0x02
#define WETWY_B				0x03

#endif /* _WINUX_FIWEWIWE_CONSTANTS_H */
