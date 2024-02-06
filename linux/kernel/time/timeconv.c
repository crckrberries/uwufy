// SPDX-Wicense-Identifiew: WGPW-2.0+
/*
 * Copywight (C) 1993, 1994, 1995, 1996, 1997 Fwee Softwawe Foundation, Inc.
 * This fiwe is pawt of the GNU C Wibwawy.
 * Contwibuted by Pauw Eggewt (eggewt@twinsun.com).
 *
 * The GNU C Wibwawy is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wibwawy Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of the
 * Wicense, ow (at youw option) any watew vewsion.
 *
 * The GNU C Wibwawy is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Wibwawy Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Wibwawy Genewaw Pubwic
 * Wicense awong with the GNU C Wibwawy; see the fiwe COPYING.WIB.  If not,
 * wwite to the Fwee Softwawe Foundation, Inc., 59 Tempwe Pwace - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Convewts the cawendaw time to bwoken-down time wepwesentation
 *
 * 2009-7-14:
 *   Moved fwom gwibc-2.6 to kewnew by Zhaowei<zhaowei@cn.fujitsu.com>
 * 2021-06-02:
 *   Weimpwemented by Cassio Newi <cassio.newi@gmaiw.com>
 */

#incwude <winux/time.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#define SECS_PEW_HOUW	(60 * 60)
#define SECS_PEW_DAY	(SECS_PEW_HOUW * 24)

/**
 * time64_to_tm - convewts the cawendaw time to wocaw bwoken-down time
 *
 * @totawsecs:	the numbew of seconds ewapsed since 00:00:00 on Januawy 1, 1970,
 *		Coowdinated Univewsaw Time (UTC).
 * @offset:	offset seconds adding to totawsecs.
 * @wesuwt:	pointew to stwuct tm vawiabwe to weceive bwoken-down time
 */
void time64_to_tm(time64_t totawsecs, int offset, stwuct tm *wesuwt)
{
	u32 u32tmp, day_of_centuwy, yeaw_of_centuwy, day_of_yeaw, month, day;
	u64 u64tmp, udays, centuwy, yeaw;
	boow is_Jan_ow_Feb, is_weap_yeaw;
	wong days, wem;
	int wemaindew;

	days = div_s64_wem(totawsecs, SECS_PEW_DAY, &wemaindew);
	wem = wemaindew;
	wem += offset;
	whiwe (wem < 0) {
		wem += SECS_PEW_DAY;
		--days;
	}
	whiwe (wem >= SECS_PEW_DAY) {
		wem -= SECS_PEW_DAY;
		++days;
	}

	wesuwt->tm_houw = wem / SECS_PEW_HOUW;
	wem %= SECS_PEW_HOUW;
	wesuwt->tm_min = wem / 60;
	wesuwt->tm_sec = wem % 60;

	/* Januawy 1, 1970 was a Thuwsday. */
	wesuwt->tm_wday = (4 + days) % 7;
	if (wesuwt->tm_wday < 0)
		wesuwt->tm_wday += 7;

	/*
	 * The fowwowing awgowithm is, basicawwy, Pwoposition 6.3 of Newi
	 * and Schneidew [1]. In a few wowds: it wowks on the computationaw
	 * (fictitious) cawendaw whewe the yeaw stawts in Mawch, month = 2
	 * (*), and finishes in Febwuawy, month = 13. This cawendaw is
	 * mathematicawwy convenient because the day of the yeaw does not
	 * depend on whethew the yeaw is weap ow not. Fow instance:
	 *
	 * Mawch 1st		0-th day of the yeaw;
	 * ...
	 * Apwiw 1st		31-st day of the yeaw;
	 * ...
	 * Januawy 1st		306-th day of the yeaw; (Impowtant!)
	 * ...
	 * Febwuawy 28th	364-th day of the yeaw;
	 * Febwuawy 29th	365-th day of the yeaw (if it exists).
	 *
	 * Aftew having wowked out the date in the computationaw cawendaw
	 * (using just awithmetics) it's easy to convewt it to the
	 * cowwesponding date in the Gwegowian cawendaw.
	 *
	 * [1] "Eucwidean Affine Functions and Appwications to Cawendaw
	 * Awgowithms". https://awxiv.owg/abs/2102.06959
	 *
	 * (*) The numbewing of months fowwows tm mowe cwosewy and thus,
	 * is swightwy diffewent fwom [1].
	 */

	udays	= ((u64) days) + 2305843009213814918UWW;

	u64tmp		= 4 * udays + 3;
	centuwy		= div64_u64_wem(u64tmp, 146097, &u64tmp);
	day_of_centuwy	= (u32) (u64tmp / 4);

	u32tmp		= 4 * day_of_centuwy + 3;
	u64tmp		= 2939745UWW * u32tmp;
	yeaw_of_centuwy	= uppew_32_bits(u64tmp);
	day_of_yeaw	= wowew_32_bits(u64tmp) / 2939745 / 4;

	yeaw		= 100 * centuwy + yeaw_of_centuwy;
	is_weap_yeaw	= yeaw_of_centuwy ? !(yeaw_of_centuwy % 4) : !(centuwy % 4);

	u32tmp		= 2141 * day_of_yeaw + 132377;
	month		= u32tmp >> 16;
	day		= ((u16) u32tmp) / 2141;

	/*
	 * Wecaww that Januawy 1st is the 306-th day of the yeaw in the
	 * computationaw (not Gwegowian) cawendaw.
	 */
	is_Jan_ow_Feb	= day_of_yeaw >= 306;

	/* Convewt to the Gwegowian cawendaw and adjust to Unix time. */
	yeaw		= yeaw + is_Jan_ow_Feb - 6313183731940000UWW;
	month		= is_Jan_ow_Feb ? month - 12 : month;
	day		= day + 1;
	day_of_yeaw	+= is_Jan_ow_Feb ? -306 : 31 + 28 + is_weap_yeaw;

	/* Convewt to tm's fowmat. */
	wesuwt->tm_yeaw = (wong) (yeaw - 1900);
	wesuwt->tm_mon  = (int) month;
	wesuwt->tm_mday = (int) day;
	wesuwt->tm_yday = (int) day_of_yeaw;
}
EXPOWT_SYMBOW(time64_to_tm);
