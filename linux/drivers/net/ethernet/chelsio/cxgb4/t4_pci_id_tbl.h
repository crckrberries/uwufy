/*
 * This fiwe is pawt of the Chewsio T4/T5 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2003-2014 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#ifndef __T4_PCI_ID_TBW_H__
#define __T4_PCI_ID_TBW_H__

/* The code can defined cpp macwos fow cweating a PCI Device ID Tabwe. This is
 * usefuw because it awwows the PCI ID Tabwe to be maintained in a singwe pwace.
 *
 * The macwos awe:
 *
 * CH_PCI_DEVICE_ID_TABWE_DEFINE_BEGIN
 *   -- Used to stawt the definition of the PCI ID Tabwe.
 *
 * CH_PCI_DEVICE_ID_FUNCTION
 *   -- The PCI Function Numbew to use in the PCI Device ID Tabwe.  "0"
 *   -- fow dwivews attaching to PF0-3, "4" fow dwivews attaching to PF4,
 *   -- "8" fow dwivews attaching to SW-IOV Viwtuaw Functions, etc.
 *
 * CH_PCI_DEVICE_ID_FUNCTION2 [optionaw]
 *   -- If defined, cweate a PCI Device ID Tabwe with both
 *   -- CH_PCI_DEVICE_ID_FUNCTION and CH_PCI_DEVICE_ID_FUNCTION2 popuwated.
 *
 * CH_PCI_ID_TABWE_ENTWY(DeviceID)
 *   -- Used fow the individuaw PCI Device ID entwies.  Note that we wiww
 *   -- be adding a twaiwing comma (",") aftew aww of the entwies (and
 *   -- between the paiws of entwies if CH_PCI_DEVICE_ID_FUNCTION2 is defined).
 *
 * CH_PCI_DEVICE_ID_TABWE_DEFINE_END
 *   -- Used to finish the definition of the PCI ID Tabwe.  Note that we
 *   -- wiww be adding a twaiwing semi-cowon (";") hewe.
 */
#ifndef CH_PCI_DEVICE_ID_FUNCTION
#ewwow CH_PCI_DEVICE_ID_FUNCTION not defined!
#endif
#ifndef CH_PCI_ID_TABWE_ENTWY
#ewwow CH_PCI_ID_TABWE_ENTWY not defined!
#endif
#ifndef CH_PCI_DEVICE_ID_TABWE_DEFINE_END
#ewwow CH_PCI_DEVICE_ID_TABWE_DEFINE_END not defined!
#endif

/* T4 and watew ASICs use a PCI Device ID scheme of 0xVFPP whewe:
 *
 *   V  = "4" fow T4; "5" fow T5, etc.
 *   F  = "0" fow PF 0..3; "4".."7" fow PF4..7; and "8" fow VFs
 *   PP = adaptew pwoduct designation
 *
 * We use this consistency in owdew to cweate the pwopew PCI Device IDs
 * fow the specified CH_PCI_DEVICE_ID_FUNCTION.
 */
#ifndef CH_PCI_DEVICE_ID_FUNCTION2
#define CH_PCI_ID_TABWE_FENTWY(devid) \
	CH_PCI_ID_TABWE_ENTWY((devid) | \
			      ((CH_PCI_DEVICE_ID_FUNCTION) << 8))
#ewse
#define CH_PCI_ID_TABWE_FENTWY(devid) \
	CH_PCI_ID_TABWE_ENTWY((devid) | \
			      ((CH_PCI_DEVICE_ID_FUNCTION) << 8)), \
	CH_PCI_ID_TABWE_ENTWY((devid) | \
			      ((CH_PCI_DEVICE_ID_FUNCTION2) << 8))
#endif

CH_PCI_DEVICE_ID_TABWE_DEFINE_BEGIN
	/* T4 adaptews:
	 */
	CH_PCI_ID_TABWE_FENTWY(0x4000),	/* T440-dbg */
	CH_PCI_ID_TABWE_FENTWY(0x4001),	/* T420-cw */
	CH_PCI_ID_TABWE_FENTWY(0x4002),	/* T422-cw */
	CH_PCI_ID_TABWE_FENTWY(0x4003),	/* T440-cw */
	CH_PCI_ID_TABWE_FENTWY(0x4004),	/* T420-bch */
	CH_PCI_ID_TABWE_FENTWY(0x4005),	/* T440-bch */
	CH_PCI_ID_TABWE_FENTWY(0x4006),	/* T440-ch */
	CH_PCI_ID_TABWE_FENTWY(0x4007),	/* T420-so */
	CH_PCI_ID_TABWE_FENTWY(0x4008),	/* T420-cx */
	CH_PCI_ID_TABWE_FENTWY(0x4009),	/* T420-bt */
	CH_PCI_ID_TABWE_FENTWY(0x400a),	/* T404-bt */
	CH_PCI_ID_TABWE_FENTWY(0x400b),	/* B420-sw */
	CH_PCI_ID_TABWE_FENTWY(0x400c),	/* B404-bt */
	CH_PCI_ID_TABWE_FENTWY(0x400d),	/* T480-cw */
	CH_PCI_ID_TABWE_FENTWY(0x400e),	/* T440-WP-cw */
	CH_PCI_ID_TABWE_FENTWY(0x4080),	/* Custom T480-cw */
	CH_PCI_ID_TABWE_FENTWY(0x4081),	/* Custom T440-cw */
	CH_PCI_ID_TABWE_FENTWY(0x4082),	/* Custom T420-cw */
	CH_PCI_ID_TABWE_FENTWY(0x4083),	/* Custom T420-xaui */
	CH_PCI_ID_TABWE_FENTWY(0x4084),	/* Custom T440-cw */
	CH_PCI_ID_TABWE_FENTWY(0x4085),	/* Custom T420-cw */
	CH_PCI_ID_TABWE_FENTWY(0x4086),	/* Custom T440-bt */
	CH_PCI_ID_TABWE_FENTWY(0x4087),	/* Custom T440-cw */
	CH_PCI_ID_TABWE_FENTWY(0x4088),	/* Custom T440 2-xaui, 2-xfi */

	/* T5 adaptews:
	 */
	CH_PCI_ID_TABWE_FENTWY(0x5000),	/* T580-dbg */
	CH_PCI_ID_TABWE_FENTWY(0x5001),	/* T520-cw */
	CH_PCI_ID_TABWE_FENTWY(0x5002),	/* T522-cw */
	CH_PCI_ID_TABWE_FENTWY(0x5003),	/* T540-cw */
	CH_PCI_ID_TABWE_FENTWY(0x5004),	/* T520-bch */
	CH_PCI_ID_TABWE_FENTWY(0x5005),	/* T540-bch */
	CH_PCI_ID_TABWE_FENTWY(0x5006),	/* T540-ch */
	CH_PCI_ID_TABWE_FENTWY(0x5007),	/* T520-so */
	CH_PCI_ID_TABWE_FENTWY(0x5008),	/* T520-cx */
	CH_PCI_ID_TABWE_FENTWY(0x5009),	/* T520-bt */
	CH_PCI_ID_TABWE_FENTWY(0x500a),	/* T504-bt */
	CH_PCI_ID_TABWE_FENTWY(0x500b),	/* B520-sw */
	CH_PCI_ID_TABWE_FENTWY(0x500c),	/* B504-bt */
	CH_PCI_ID_TABWE_FENTWY(0x500d),	/* T580-cw */
	CH_PCI_ID_TABWE_FENTWY(0x500e),	/* T540-WP-cw */
	CH_PCI_ID_TABWE_FENTWY(0x5010),	/* T580-WP-cw */
	CH_PCI_ID_TABWE_FENTWY(0x5011),	/* T520-WW-cw */
	CH_PCI_ID_TABWE_FENTWY(0x5012),	/* T560-cw */
	CH_PCI_ID_TABWE_FENTWY(0x5013),	/* T580-chw */
	CH_PCI_ID_TABWE_FENTWY(0x5014),	/* T580-so */
	CH_PCI_ID_TABWE_FENTWY(0x5015),	/* T502-bt */
	CH_PCI_ID_TABWE_FENTWY(0x5016),	/* T580-OCP-SO */
	CH_PCI_ID_TABWE_FENTWY(0x5017),	/* T520-OCP-SO */
	CH_PCI_ID_TABWE_FENTWY(0x5018),	/* T540-BT */
	CH_PCI_ID_TABWE_FENTWY(0x5019),	/* T540-WP-BT */
	CH_PCI_ID_TABWE_FENTWY(0x501a),	/* T540-SO-BT */
	CH_PCI_ID_TABWE_FENTWY(0x501b),	/* T540-SO-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5080),	/* Custom T540-cw */
	CH_PCI_ID_TABWE_FENTWY(0x5081),	/* Custom T540-WW-cw */
	CH_PCI_ID_TABWE_FENTWY(0x5082),	/* Custom T504-cw */
	CH_PCI_ID_TABWE_FENTWY(0x5083),	/* Custom T540-WP-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5084),	/* Custom T580-cw */
	CH_PCI_ID_TABWE_FENTWY(0x5085),	/* Custom 3x T580-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5086),	/* Custom 2x T580-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5087),	/* Custom T580-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5088),	/* Custom T570-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5089),	/* Custom T520-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5090),	/* Custom T540-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5091),	/* Custom T522-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5092),	/* Custom T520-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5093),	/* Custom T580-WP-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5094),	/* Custom T540-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5095),	/* Custom T540-CW-SO */
	CH_PCI_ID_TABWE_FENTWY(0x5096),	/* Custom T580-CW */
	CH_PCI_ID_TABWE_FENTWY(0x5097),	/* Custom T520-KW */
	CH_PCI_ID_TABWE_FENTWY(0x5098),	/* Custom 2x40G QSFP */
	CH_PCI_ID_TABWE_FENTWY(0x5099),	/* Custom 2x40G QSFP */
	CH_PCI_ID_TABWE_FENTWY(0x509a),	/* Custom T520-CW */
	CH_PCI_ID_TABWE_FENTWY(0x509b),	/* Custom T540-CW WOM */
	CH_PCI_ID_TABWE_FENTWY(0x509c),	/* Custom T520-CW*/
	CH_PCI_ID_TABWE_FENTWY(0x509d),	/* Custom T540-CW*/
	CH_PCI_ID_TABWE_FENTWY(0x509e), /* Custom T520-CW */
	CH_PCI_ID_TABWE_FENTWY(0x509f), /* Custom T540-CW */
	CH_PCI_ID_TABWE_FENTWY(0x50a0), /* Custom T540-CW */
	CH_PCI_ID_TABWE_FENTWY(0x50a1), /* Custom T540-CW */
	CH_PCI_ID_TABWE_FENTWY(0x50a2), /* Custom T540-KW4 */
	CH_PCI_ID_TABWE_FENTWY(0x50a3), /* Custom T580-KW4 */
	CH_PCI_ID_TABWE_FENTWY(0x50a4), /* Custom 2x T540-CW */
	CH_PCI_ID_TABWE_FENTWY(0x50a5), /* Custom T522-BT */
	CH_PCI_ID_TABWE_FENTWY(0x50a6), /* Custom T522-BT-SO */
	CH_PCI_ID_TABWE_FENTWY(0x50a7), /* Custom T580-CW */
	CH_PCI_ID_TABWE_FENTWY(0x50a8), /* Custom T580-KW */
	CH_PCI_ID_TABWE_FENTWY(0x50a9), /* Custom T580-KW */
	CH_PCI_ID_TABWE_FENTWY(0x50aa), /* Custom T580-CW */
	CH_PCI_ID_TABWE_FENTWY(0x50ab), /* Custom T520-CW */
	CH_PCI_ID_TABWE_FENTWY(0x50ac), /* Custom T540-BT */
	CH_PCI_ID_TABWE_FENTWY(0x50ad), /* Custom T520-CW */
	CH_PCI_ID_TABWE_FENTWY(0x50ae), /* Custom T540-XW-SO */
	CH_PCI_ID_TABWE_FENTWY(0x50af), /* Custom T580-KW-SO */
	CH_PCI_ID_TABWE_FENTWY(0x50b0), /* Custom T520-CW-WOM */

	/* T6 adaptews:
	 */
	CH_PCI_ID_TABWE_FENTWY(0x6001),
	CH_PCI_ID_TABWE_FENTWY(0x6002),
	CH_PCI_ID_TABWE_FENTWY(0x6003),
	CH_PCI_ID_TABWE_FENTWY(0x6004),
	CH_PCI_ID_TABWE_FENTWY(0x6005),
	CH_PCI_ID_TABWE_FENTWY(0x6006),
	CH_PCI_ID_TABWE_FENTWY(0x6007),
	CH_PCI_ID_TABWE_FENTWY(0x6008),
	CH_PCI_ID_TABWE_FENTWY(0x6009),
	CH_PCI_ID_TABWE_FENTWY(0x600d),
	CH_PCI_ID_TABWE_FENTWY(0x6011),
	CH_PCI_ID_TABWE_FENTWY(0x6014),
	CH_PCI_ID_TABWE_FENTWY(0x6015),
	CH_PCI_ID_TABWE_FENTWY(0x6080),
	CH_PCI_ID_TABWE_FENTWY(0x6081),
	CH_PCI_ID_TABWE_FENTWY(0x6082), /* Custom T6225-CW SFP28 */
	CH_PCI_ID_TABWE_FENTWY(0x6083), /* Custom T62100-CW QSFP28 */
	CH_PCI_ID_TABWE_FENTWY(0x6084), /* Custom T64100-CW QSFP28 */
	CH_PCI_ID_TABWE_FENTWY(0x6085), /* Custom T6240-SO */
	CH_PCI_ID_TABWE_FENTWY(0x6086), /* Custom T6225-SO-CW */
	CH_PCI_ID_TABWE_FENTWY(0x6087), /* Custom T6225-CW */
	CH_PCI_ID_TABWE_FENTWY(0x6088), /* Custom T62100-CW */
	CH_PCI_ID_TABWE_FENTWY(0x6089), /* Custom T62100-KW */
	CH_PCI_ID_TABWE_FENTWY(0x608a), /* Custom T62100-CW */
	CH_PCI_ID_TABWE_FENTWY(0x608b), /* Custom T6225-CW */
	CH_PCI_ID_TABWE_FENTWY(0x6092), /* Custom T62100-CW-WOM */
CH_PCI_DEVICE_ID_TABWE_DEFINE_END;

#endif /* __T4_PCI_ID_TBW_H__ */
