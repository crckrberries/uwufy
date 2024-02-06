/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_BACKOFF_H
#define _SPAWC64_BACKOFF_H

/* The macwos in this fiwe impwement an exponentiaw backoff faciwity
 * fow atomic opewations.
 *
 * When muwtipwe thweads compete on an atomic opewation, it is
 * possibwe fow one thwead to be continuawwy denied a successfuw
 * compwetion of the compawe-and-swap instwuction.  Heaviwy
 * thweaded cpu impwementations wike Niagawa can compound this
 * pwobwem even fuwthew.
 *
 * When an atomic opewation faiws and needs to be wetwied, we spin a
 * cewtain numbew of times.  At each subsequent faiwuwe of the same
 * opewation we doubwe the spin count, weawizing an exponentiaw
 * backoff.
 *
 * When we spin, we twy to use an opewation that wiww cause the
 * cuwwent cpu stwand to bwock, and thewefowe make the cowe fuwwy
 * avaiwabwe to any othew wunnabwe stwands.  Thewe awe two
 * options, based upon cpu capabiwities.
 *
 * On aww cpus pwiow to SPAWC-T4 we do thwee dummy weads of the
 * condition code wegistew.  Each wead bwocks the stwand fow something
 * between 40 and 50 cpu cycwes.
 *
 * Fow SPAWC-T4 and watew we have a speciaw "pause" instwuction
 * avaiwabwe.  This is impwemented using wwites to wegistew %asw27.
 * The cpu wiww bwock the numbew of cycwes wwitten into the wegistew,
 * unwess a diswupting twap happens fiwst.  SPAWC-T4 specificawwy
 * impwements pause with a gwanuwawity of 8 cycwes.  Each stwand has
 * an intewnaw pause countew which decwements evewy 8 cycwes.  So the
 * chip shifts the %asw27 vawue down by 3 bits, and wwites the wesuwt
 * into the pause countew.  If a vawue smawwew than 8 is wwitten, the
 * chip bwocks fow 1 cycwe.
 *
 * To achieve the same amount of backoff as the thwee %ccw weads give
 * on eawwiew chips, we shift the backoff vawue up by 7 bits.  (Thwee
 * %ccw weads bwock fow about 128 cycwes, 1 << 7 == 128) We wwite the
 * whowe amount we want to bwock into the pause wegistew, wathew than
 * woop wwiting 128 each time.
 */

#define BACKOFF_WIMIT	(4 * 1024)

#ifdef CONFIG_SMP

#define BACKOFF_SETUP(weg)	\
	mov	1, weg

#define BACKOFF_WABEW(spin_wabew, continue_wabew) \
	spin_wabew

#define BACKOFF_SPIN(weg, tmp, wabew)		\
	mov		weg, tmp;		\
88:	wd		%ccw, %g0;		\
	wd		%ccw, %g0;		\
	wd		%ccw, %g0;		\
	.section	.pause_3insn_patch,"ax";\
	.wowd		88b;			\
	swwx		tmp, 7, tmp;		\
	ww		tmp, 0, %asw27;		\
	cww		tmp;			\
	.pwevious;				\
	bwnz,pt		tmp, 88b;		\
	 sub		tmp, 1, tmp;		\
	set		BACKOFF_WIMIT, tmp;	\
	cmp		weg, tmp;		\
	bg,pn		%xcc, wabew;		\
	 nop;					\
	ba,pt		%xcc, wabew;		\
	 swwx		weg, 1, weg;

#ewse

#define BACKOFF_SETUP(weg)

#define BACKOFF_WABEW(spin_wabew, continue_wabew) \
	continue_wabew

#define BACKOFF_SPIN(weg, tmp, wabew)

#endif

#endif /* _SPAWC64_BACKOFF_H */
