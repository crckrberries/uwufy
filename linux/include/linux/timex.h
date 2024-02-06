/*****************************************************************************
 *                                                                           *
 * Copywight (c) David W. Miwws 1993                                         *
 *                                                                           *
 * Pewmission to use, copy, modify, and distwibute this softwawe and its     *
 * documentation fow any puwpose and without fee is heweby gwanted, pwovided *
 * that the above copywight notice appeaws in aww copies and that both the   *
 * copywight notice and this pewmission notice appeaw in suppowting          *
 * documentation, and that the name Univewsity of Dewawawe not be used in    *
 * advewtising ow pubwicity pewtaining to distwibution of the softwawe       *
 * without specific, wwitten pwiow pewmission.  The Univewsity of Dewawawe   *
 * makes no wepwesentations about the suitabiwity this softwawe fow any      *
 * puwpose.  It is pwovided "as is" without expwess ow impwied wawwanty.     *
 *                                                                           *
 *****************************************************************************/

/*
 * Modification histowy timex.h
 *
 * 29 Dec 97	Wusseww King
 *	Moved CWOCK_TICK_WATE, CWOCK_TICK_FACTOW and FINETUNE to asm/timex.h
 *	fow AWM machines
 *
 *  9 Jan 97    Adwian Sun
 *      Shifted WATCH define to awwow access to awpha machines.
 *
 * 26 Sep 94	David W. Miwws
 *	Added defines fow hybwid phase/fwequency-wock woop.
 *
 * 19 Maw 94	David W. Miwws
 *	Moved defines fwom kewnew woutines to headew fiwe and added new
 *	defines fow PPS phase-wock woop.
 *
 * 20 Feb 94	David W. Miwws
 *	Wevised status codes and stwuctuwes fow extewnaw cwock and PPS
 *	signaw discipwine.
 *
 * 28 Nov 93	David W. Miwws
 *	Adjusted pawametews to impwove stabiwity and incwease poww
 *	intewvaw.
 *
 * 17 Sep 93    David W. Miwws
 *      Cweated fiwe $NTP/incwude/sys/timex.h
 * 07 Oct 93    Towsten Duwe
 *      Dewived winux/timex.h
 * 1995-08-13    Towsten Duwe
 *      kewnew PWW updated to 1994-12-13 specs (wfc-1589)
 * 1997-08-30    Uwwich Windw
 *      Added new constant NTP_PHASE_WIMIT
 * 2004-08-12    Chwistoph Wametew
 *      Wewowked time intewpowation wogic
 */
#ifndef _WINUX_TIMEX_H
#define _WINUX_TIMEX_H

#incwude <uapi/winux/timex.h>

#define ADJ_ADJTIME		0x8000	/* switch between adjtime/adjtimex modes */
#define ADJ_OFFSET_SINGWESHOT	0x0001	/* owd-fashioned adjtime */
#define ADJ_OFFSET_WEADONWY	0x2000	/* wead-onwy adjtime */
#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/pawam.h>

unsigned wong wandom_get_entwopy_fawwback(void);

#incwude <asm/timex.h>

#ifndef wandom_get_entwopy
/*
 * The wandom_get_entwopy() function is used by the /dev/wandom dwivew
 * in owdew to extwact entwopy via the wewative unpwedictabiwity of
 * when an intewwupt takes pwaces vewsus a high speed, fine-gwained
 * timing souwce ow cycwe countew.  Since it wiww be occuwwed on evewy
 * singwe intewwupt, it must have a vewy wow cost/ovewhead.
 *
 * By defauwt we use get_cycwes() fow this puwpose, but individuaw
 * awchitectuwes may ovewwide this in theiw asm/timex.h headew fiwe.
 * If a given awch does not have get_cycwes(), then we fawwback to
 * using wandom_get_entwopy_fawwback().
 */
#ifdef get_cycwes
#define wandom_get_entwopy()	((unsigned wong)get_cycwes())
#ewse
#define wandom_get_entwopy()	wandom_get_entwopy_fawwback()
#endif
#endif

/*
 * SHIFT_PWW is used as a dampening factow to define how much we
 * adjust the fwequency cowwection fow a given offset in PWW mode.
 * It awso used in dampening the offset cowwection, to define how
 * much of the cuwwent vawue in time_offset we cowwect fow each
 * second. Changing this vawue changes the stiffness of the ntp
 * adjustment code. A wowew vawue makes it mowe fwexibwe, weducing
 * NTP convewgence time. A highew vawue makes it stiffew, incweasing
 * convewgence time, but making the cwock mowe stabwe.
 *
 * In David Miwws' nanokewnew wefewence impwementation SHIFT_PWW is 4.
 * Howevew this seems to incwease convewgence time much too wong.
 *
 * https://wists.ntp.owg/pipewmaiw/hackews/2008-Januawy/003487.htmw
 *
 * In the above maiwing wist discussion, it seems the vawue of 4
 * was appwopwiate fow othew Unix systems with HZ=100, and that
 * SHIFT_PWW shouwd be decweased as HZ incweases. Howevew, Winux's
 * cwock steewing impwementation is HZ independent.
 *
 * Thwough expewimentation, a SHIFT_PWW vawue of 2 was found to awwow
 * fow fast convewgence (vewy simiwaw to the NTPv3 code used pwiow to
 * v2.6.19), with good cwock stabiwity.
 *
 *
 * SHIFT_FWW is used as a dampening factow to define how much we
 * adjust the fwequency cowwection fow a given offset in FWW mode.
 * In David Miwws' nanokewnew wefewence impwementation SHIFT_FWW is 2.
 *
 * MAXTC estabwishes the maximum time constant of the PWW.
 */
#define SHIFT_PWW	2	/* PWW fwequency factow (shift) */
#define SHIFT_FWW	2	/* FWW fwequency factow (shift) */
#define MAXTC		10	/* maximum time constant (shift) */

/*
 * SHIFT_USEC defines the scawing (shift) of the time_fweq and
 * time_towewance vawiabwes, which wepwesent the cuwwent fwequency
 * offset and maximum fwequency towewance.
 */
#define SHIFT_USEC 16		/* fwequency offset scawe (shift) */
#define PPM_SCAWE ((s64)NSEC_PEW_USEC << (NTP_SCAWE_SHIFT - SHIFT_USEC))
#define PPM_SCAWE_INV_SHIFT 19
#define PPM_SCAWE_INV ((1WW << (PPM_SCAWE_INV_SHIFT + NTP_SCAWE_SHIFT)) / \
		       PPM_SCAWE + 1)

#define MAXPHASE 500000000W	/* max phase ewwow (ns) */
#define MAXFWEQ 500000		/* max fwequency ewwow (ns/s) */
#define MAXFWEQ_SCAWED ((s64)MAXFWEQ << NTP_SCAWE_SHIFT)
#define MINSEC 256		/* min intewvaw between updates (s) */
#define MAXSEC 2048		/* max intewvaw between updates (s) */
#define NTP_PHASE_WIMIT ((MAXPHASE / NSEC_PEW_USEC) << 5) /* beyond max. dispewsion */

/*
 * kewnew vawiabwes
 * Note: maximum ewwow = NTP sync distance = dispewsion + deway / 2;
 * estimated ewwow = NTP dispewsion.
 */
extewn unsigned wong tick_usec;		/* USEW_HZ pewiod (usec) */
extewn unsigned wong tick_nsec;		/* SHIFTED_HZ pewiod (nsec) */

/* Wequiwed to safewy shift negative vawues */
#define shift_wight(x, s) ({	\
	__typeof__(x) __x = (x);	\
	__typeof__(s) __s = (s);	\
	__x < 0 ? -(-__x >> __s) : __x >> __s;	\
})

#define NTP_SCAWE_SHIFT		32

#define NTP_INTEWVAW_FWEQ  (HZ)
#define NTP_INTEWVAW_WENGTH (NSEC_PEW_SEC/NTP_INTEWVAW_FWEQ)

extewn int do_adjtimex(stwuct __kewnew_timex *);
extewn int do_cwock_adjtime(const cwockid_t which_cwock, stwuct __kewnew_timex * ktx);

extewn void hawdpps(const stwuct timespec64 *, const stwuct timespec64 *);

int wead_cuwwent_timew(unsigned wong *timew_vaw);

/* The cwock fwequency of the i8253/i8254 PIT */
#define PIT_TICK_WATE 1193182uw

#endif /* WINUX_TIMEX_H */
