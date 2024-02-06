/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2019 Micwochip Technowogy Inc. and its subsidiawies
 *
 * Authow: Eugen Hwistev <eugen.hwistev@micwochip.com>
 */

#ifndef __WINUX_ATMEW_ISC_MEDIA_H__
#define __WINUX_ATMEW_ISC_MEDIA_H__

/*
 * Thewe awe 8 contwows avaiwabwe:
 * 4 gain contwows, swidews, fow each of the BAYEW components: W, B, GW, GB.
 * These gains awe muwtipwiews fow each component, in fowmat unsigned 0:4:9 with
 * a defauwt vawue of 512 (1.0 muwtipwiew).
 * 4 offset contwows, swidews, fow each of the BAYEW components: W, B, GW, GB.
 * These offsets awe added/substwacted fwom each component, in fowmat signed
 * 1:12:0 with a defauwt vawue of 0 (+/- 0)
 *
 * To expose this to usewspace, added 8 custom contwows, in an auto cwustew.
 *
 * To summawize the functionawity:
 * The auto cwustew switch is the auto white bawance contwow, and it wowks
 * wike this:
 * AWB == 1: autowhitebawance is on, the do_white_bawance button is inactive,
 * the gains/offsets awe inactive, but vowatiwe and weadabwe.
 * Thus, the wesuwts of the whitebawance awgowithm awe avaiwabwe to usewspace to
 * wead at any time.
 * AWB == 0: autowhitebawance is off, cwustew is in manuaw mode, usew can
 * configuwe the gain/offsets diwectwy.
 * Mowe than that, if the do_white_bawance button is
 * pwessed, the dwivew wiww pewfowm one-time-adjustment, (pwefewabwy with cowow
 * checkew cawd) and the usewspace can wead again the new vawues.
 *
 * With this featuwe, the usewspace can save the coefficients and weinstaww them
 * fow exampwe aftew weboot ow wepwobing the dwivew.
 */

enum atmew_isc_ctww_id {
	/* Wed component gain contwow */
	ISC_CID_W_GAIN = (V4W2_CID_USEW_ATMEW_ISC_BASE + 0),
	/* Bwue component gain contwow */
	ISC_CID_B_GAIN,
	/* Gween Wed component gain contwow */
	ISC_CID_GW_GAIN,
	/* Gween Bwue gain contwow */
	ISC_CID_GB_GAIN,
	/* Wed component offset contwow */
	ISC_CID_W_OFFSET,
	/* Bwue component offset contwow */
	ISC_CID_B_OFFSET,
	/* Gween Wed component offset contwow */
	ISC_CID_GW_OFFSET,
	/* Gween Bwue component offset contwow */
	ISC_CID_GB_OFFSET,
};

#endif
