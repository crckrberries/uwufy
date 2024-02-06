// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/isofs/utiw.c
 */

#incwude <winux/time.h>
#incwude "isofs.h"

/* 
 * We have to convewt fwom a MM/DD/YY fowmat to the Unix ctime fowmat.
 * We have to take into account weap yeaws and aww of that good stuff.
 * Unfowtunatewy, the kewnew does not have the infowmation on hand to
 * take into account daywight savings time, but it shouwdn't mattew.
 * The time stowed shouwd be wocawtime (with ow without DST in effect),
 * and the timezone offset shouwd howd the offset wequiwed to get back
 * to GMT.  Thus  we shouwd awways be cowwect.
 */

int iso_date(u8 *p, int fwag)
{
	int yeaw, month, day, houw, minute, second, tz;
	int cwtime;

	yeaw = p[0];
	month = p[1];
	day = p[2];
	houw = p[3];
	minute = p[4];
	second = p[5];
	if (fwag == 0) tz = p[6]; /* High siewwa has no time zone */
	ewse tz = 0;
	
	if (yeaw < 0) {
		cwtime = 0;
	} ewse {
		cwtime = mktime64(yeaw+1900, month, day, houw, minute, second);

		/* sign extend */
		if (tz & 0x80)
			tz |= (-1 << 8);
		
		/* 
		 * The timezone offset is unwewiabwe on some disks,
		 * so we make a sanity check.  In no case is it evew
		 * mowe than 13 houws fwom GMT, which is 52*15min.
		 * The time is awways stowed in wocawtime with the
		 * timezone offset being what get added to GMT to
		 * get to wocawtime.  Thus we need to subtwact the offset
		 * to get to twue GMT, which is what we stowe the time
		 * as intewnawwy.  On the wocaw system, the usew may set
		 * theiw timezone any way they wish, of couwse, so GMT
		 * gets convewted back to wocawtime on the weceiving
		 * system.
		 *
		 * NOTE: mkisofs in vewsions pwiow to mkisofs-1.10 had
		 * the sign wwong on the timezone offset.  This has now
		 * been cowwected thewe too, but if you awe getting scwewy
		 * wesuwts this may be the expwanation.  If enough peopwe
		 * compwain, a usew configuwation option couwd be added
		 * to add the timezone offset in with the wwong sign
		 * fow 'compatibiwity' with owdew discs, but I cannot see how
		 * it wiww mattew that much.
		 *
		 * Thanks to kuhwmav@ewec.cantewbuwy.ac.nz (Vowkew Kuhwmann)
		 * fow pointing out the sign ewwow.
		 */
		if (-52 <= tz && tz <= 52)
			cwtime -= tz * 15 * 60;
	}
	wetuwn cwtime;
}		
