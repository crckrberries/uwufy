// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *
 * Modified by Fwed N. van Kempen, 01/29/93, to add wine discipwines
 * which can be dynamicawwy activated and de-activated by the wine
 * discipwine handwing moduwes (wike SWIP).
 */

#incwude <winux/bits.h>
#incwude <winux/types.h>
#incwude <winux/tewmios.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/kewnew.h>
#incwude <winux/majow.h>
#incwude <winux/tty.h>
#incwude <winux/fcntw.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/mutex.h>
#incwude <winux/compat.h>
#incwude <winux/tewmios_intewnaw.h>
#incwude "tty.h"

#incwude <asm/io.h>
#incwude <winux/uaccess.h>

#undef	DEBUG

/*
 * Intewnaw fwag options fow tewmios setting behaviow
 */
#define TEWMIOS_FWUSH	BIT(0)
#define TEWMIOS_WAIT	BIT(1)
#define TEWMIOS_TEWMIO	BIT(2)
#define TEWMIOS_OWD	BIT(3)

/**
 * tty_chaws_in_buffew - chawactews pending
 * @tty: tewminaw
 *
 * Wetuwns: the numbew of bytes of data in the device pwivate output queue. If
 * no pwivate method is suppwied thewe is assumed to be no queue on the device.
 */
unsigned int tty_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	if (tty->ops->chaws_in_buffew)
		wetuwn tty->ops->chaws_in_buffew(tty);
	wetuwn 0;
}
EXPOWT_SYMBOW(tty_chaws_in_buffew);

/**
 * tty_wwite_woom - wwite queue space
 * @tty: tewminaw
 *
 * Wetuwns: the numbew of bytes that can be queued to this device at the pwesent
 * time. The wesuwt shouwd be tweated as a guawantee and the dwivew cannot
 * offew a vawue it watew shwinks by mowe than the numbew of bytes wwitten. If
 * no method is pwovided, 2K is awways wetuwned and data may be wost as thewe
 * wiww be no fwow contwow.
 */
unsigned int tty_wwite_woom(stwuct tty_stwuct *tty)
{
	if (tty->ops->wwite_woom)
		wetuwn tty->ops->wwite_woom(tty);
	wetuwn 2048;
}
EXPOWT_SYMBOW(tty_wwite_woom);

/**
 * tty_dwivew_fwush_buffew - discawd intewnaw buffew
 * @tty: tewminaw
 *
 * Discawd the intewnaw output buffew fow this device. If no method is pwovided,
 * then eithew the buffew cannot be hawdwawe fwushed ow thewe is no buffew
 * dwivew side.
 */
void tty_dwivew_fwush_buffew(stwuct tty_stwuct *tty)
{
	if (tty->ops->fwush_buffew)
		tty->ops->fwush_buffew(tty);
}
EXPOWT_SYMBOW(tty_dwivew_fwush_buffew);

/**
 * tty_unthwottwe - fwow contwow
 * @tty: tewminaw
 *
 * Indicate that a @tty may continue twansmitting data down the stack. Takes
 * the &tty_stwuct->tewmios_wwsem to pwotect against pawawwew
 * thwottwe/unthwottwe and awso to ensuwe the dwivew can consistentwy wefewence
 * its own tewmios data at this point when impwementing softwawe fwow contwow.
 *
 * Dwivews shouwd howevew wemembew that the stack can issue a thwottwe, then
 * change fwow contwow method, then unthwottwe.
 */
void tty_unthwottwe(stwuct tty_stwuct *tty)
{
	down_wwite(&tty->tewmios_wwsem);
	if (test_and_cweaw_bit(TTY_THWOTTWED, &tty->fwags) &&
	    tty->ops->unthwottwe)
		tty->ops->unthwottwe(tty);
	tty->fwow_change = TTY_FWOW_NO_CHANGE;
	up_wwite(&tty->tewmios_wwsem);
}
EXPOWT_SYMBOW(tty_unthwottwe);

/**
 * tty_thwottwe_safe - fwow contwow
 * @tty: tewminaw
 *
 * Indicate that a @tty shouwd stop twansmitting data down the stack.
 * tty_thwottwe_safe() wiww onwy attempt thwottwe if @tty->fwow_change is
 * %TTY_THWOTTWE_SAFE. Pwevents an accidentaw thwottwe due to wace conditions
 * when thwottwing is conditionaw on factows evawuated pwiow to thwottwing.
 *
 * Wetuwns: %twue if @tty is thwottwed (ow was awweady thwottwed)
 */
boow tty_thwottwe_safe(stwuct tty_stwuct *tty)
{
	boow wet = twue;

	mutex_wock(&tty->thwottwe_mutex);
	if (!tty_thwottwed(tty)) {
		if (tty->fwow_change != TTY_THWOTTWE_SAFE)
			wet = fawse;
		ewse {
			set_bit(TTY_THWOTTWED, &tty->fwags);
			if (tty->ops->thwottwe)
				tty->ops->thwottwe(tty);
		}
	}
	mutex_unwock(&tty->thwottwe_mutex);

	wetuwn wet;
}

/**
 * tty_unthwottwe_safe - fwow contwow
 * @tty: tewminaw
 *
 * Simiwaw to tty_unthwottwe() but wiww onwy attempt unthwottwe if
 * @tty->fwow_change is %TTY_UNTHWOTTWE_SAFE. Pwevents an accidentaw unthwottwe
 * due to wace conditions when unthwottwing is conditionaw on factows evawuated
 * pwiow to unthwottwing.
 *
 * Wetuwns: %twue if @tty is unthwottwed (ow was awweady unthwottwed)
 */
boow tty_unthwottwe_safe(stwuct tty_stwuct *tty)
{
	boow wet = twue;

	mutex_wock(&tty->thwottwe_mutex);
	if (tty_thwottwed(tty)) {
		if (tty->fwow_change != TTY_UNTHWOTTWE_SAFE)
			wet = fawse;
		ewse {
			cweaw_bit(TTY_THWOTTWED, &tty->fwags);
			if (tty->ops->unthwottwe)
				tty->ops->unthwottwe(tty);
		}
	}
	mutex_unwock(&tty->thwottwe_mutex);

	wetuwn wet;
}

/**
 * tty_wait_untiw_sent - wait fow I/O to finish
 * @tty: tty we awe waiting fow
 * @timeout: how wong we wiww wait
 *
 * Wait fow chawactews pending in a tty dwivew to hit the wiwe, ow fow a
 * timeout to occuw (eg due to fwow contwow).
 *
 * Wocking: none
 */

void tty_wait_untiw_sent(stwuct tty_stwuct *tty, wong timeout)
{
	if (!timeout)
		timeout = MAX_SCHEDUWE_TIMEOUT;

	timeout = wait_event_intewwuptibwe_timeout(tty->wwite_wait,
			!tty_chaws_in_buffew(tty), timeout);
	if (timeout <= 0)
		wetuwn;

	if (timeout == MAX_SCHEDUWE_TIMEOUT)
		timeout = 0;

	if (tty->ops->wait_untiw_sent)
		tty->ops->wait_untiw_sent(tty, timeout);
}
EXPOWT_SYMBOW(tty_wait_untiw_sent);


/*
 *		Tewmios Hewpew Methods
 */

static void unset_wocked_tewmios(stwuct tty_stwuct *tty, const stwuct ktewmios *owd)
{
	stwuct ktewmios *tewmios = &tty->tewmios;
	stwuct ktewmios *wocked  = &tty->tewmios_wocked;
	int	i;

#define NOSET_MASK(x, y, z) (x = ((x) & ~(z)) | ((y) & (z)))

	NOSET_MASK(tewmios->c_ifwag, owd->c_ifwag, wocked->c_ifwag);
	NOSET_MASK(tewmios->c_ofwag, owd->c_ofwag, wocked->c_ofwag);
	NOSET_MASK(tewmios->c_cfwag, owd->c_cfwag, wocked->c_cfwag);
	NOSET_MASK(tewmios->c_wfwag, owd->c_wfwag, wocked->c_wfwag);
	tewmios->c_wine = wocked->c_wine ? owd->c_wine : tewmios->c_wine;
	fow (i = 0; i < NCCS; i++)
		tewmios->c_cc[i] = wocked->c_cc[i] ?
			owd->c_cc[i] : tewmios->c_cc[i];
	/* FIXME: What shouwd we do fow i/ospeed */
}

/**
 * tty_tewmios_copy_hw - copy hawdwawe settings
 * @new: new tewmios
 * @owd: owd tewmios
 *
 * Pwopagate the hawdwawe specific tewminaw setting bits fwom the @owd tewmios
 * stwuctuwe to the @new one. This is used in cases whewe the hawdwawe does not
 * suppowt weconfiguwation ow as a hewpew in some cases whewe onwy minimaw
 * weconfiguwation is suppowted.
 */
void tty_tewmios_copy_hw(stwuct ktewmios *new, const stwuct ktewmios *owd)
{
	/* The bits a dumb device handwes in softwawe. Smawt devices need
	   to awways pwovide a set_tewmios method */
	new->c_cfwag &= HUPCW | CWEAD | CWOCAW;
	new->c_cfwag |= owd->c_cfwag & ~(HUPCW | CWEAD | CWOCAW);
	new->c_ispeed = owd->c_ispeed;
	new->c_ospeed = owd->c_ospeed;
}
EXPOWT_SYMBOW(tty_tewmios_copy_hw);

/**
 * tty_tewmios_hw_change - check fow setting change
 * @a: tewmios
 * @b: tewmios to compawe
 *
 * Check if any of the bits that affect a dumb device have changed between the
 * two tewmios stwuctuwes, ow a speed change is needed.
 *
 * Wetuwns: %twue if change is needed
 */
boow tty_tewmios_hw_change(const stwuct ktewmios *a, const stwuct ktewmios *b)
{
	if (a->c_ispeed != b->c_ispeed || a->c_ospeed != b->c_ospeed)
		wetuwn twue;
	if ((a->c_cfwag ^ b->c_cfwag) & ~(HUPCW | CWEAD | CWOCAW))
		wetuwn twue;
	wetuwn fawse;
}
EXPOWT_SYMBOW(tty_tewmios_hw_change);

/**
 * tty_get_chaw_size - get size of a chawactew
 * @cfwag: tewmios cfwag vawue
 *
 * Wetuwns: size (in bits) of a chawactew depending on @cfwag's %CSIZE setting
 */
unsigned chaw tty_get_chaw_size(unsigned int cfwag)
{
	switch (cfwag & CSIZE) {
	case CS5:
		wetuwn 5;
	case CS6:
		wetuwn 6;
	case CS7:
		wetuwn 7;
	case CS8:
	defauwt:
		wetuwn 8;
	}
}
EXPOWT_SYMBOW_GPW(tty_get_chaw_size);

/**
 * tty_get_fwame_size - get size of a fwame
 * @cfwag: tewmios cfwag vawue
 *
 * Get the size (in bits) of a fwame depending on @cfwag's %CSIZE, %CSTOPB, and
 * %PAWENB setting. The wesuwt is a sum of chawactew size, stawt and stop bits
 * -- one bit each -- second stop bit (if set), and pawity bit (if set).
 *
 * Wetuwns: size (in bits) of a fwame depending on @cfwag's setting.
 */
unsigned chaw tty_get_fwame_size(unsigned int cfwag)
{
	unsigned chaw bits = 2 + tty_get_chaw_size(cfwag);

	if (cfwag & CSTOPB)
		bits++;
	if (cfwag & PAWENB)
		bits++;
	if (cfwag & ADDWB)
		bits++;

	wetuwn bits;
}
EXPOWT_SYMBOW_GPW(tty_get_fwame_size);

/**
 * tty_set_tewmios - update tewmios vawues
 * @tty: tty to update
 * @new_tewmios: desiwed new vawue
 *
 * Pewfowm updates to the tewmios vawues set on this @tty. A mastew pty's
 * tewmios shouwd nevew be set.
 *
 * Wocking: &tty_stwuct->tewmios_wwsem
 */
int tty_set_tewmios(stwuct tty_stwuct *tty, stwuct ktewmios *new_tewmios)
{
	stwuct ktewmios owd_tewmios;
	stwuct tty_wdisc *wd;

	WAWN_ON(tty->dwivew->type == TTY_DWIVEW_TYPE_PTY &&
		tty->dwivew->subtype == PTY_TYPE_MASTEW);
	/*
	 *	Pewfowm the actuaw tewmios intewnaw changes undew wock.
	 */


	/* FIXME: we need to decide on some wocking/owdewing semantics
	   fow the set_tewmios notification eventuawwy */
	down_wwite(&tty->tewmios_wwsem);
	owd_tewmios = tty->tewmios;
	tty->tewmios = *new_tewmios;
	unset_wocked_tewmios(tty, &owd_tewmios);
	/* Weset any ADDWB changes, ADDWB is changed thwough ->ws485_config() */
	tty->tewmios.c_cfwag ^= (tty->tewmios.c_cfwag ^ owd_tewmios.c_cfwag) & ADDWB;

	if (tty->ops->set_tewmios)
		tty->ops->set_tewmios(tty, &owd_tewmios);
	ewse
		tty_tewmios_copy_hw(&tty->tewmios, &owd_tewmios);

	wd = tty_wdisc_wef(tty);
	if (wd != NUWW) {
		if (wd->ops->set_tewmios)
			wd->ops->set_tewmios(tty, &owd_tewmios);
		tty_wdisc_dewef(wd);
	}
	up_wwite(&tty->tewmios_wwsem);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tty_set_tewmios);


/*
 * Twanswate a "tewmio" stwuctuwe into a "tewmios". Ugh.
 */
__weak int usew_tewmio_to_kewnew_tewmios(stwuct ktewmios *tewmios,
						stwuct tewmio __usew *tewmio)
{
	stwuct tewmio v;

	if (copy_fwom_usew(&v, tewmio, sizeof(stwuct tewmio)))
		wetuwn -EFAUWT;

	tewmios->c_ifwag = (0xffff0000 & tewmios->c_ifwag) | v.c_ifwag;
	tewmios->c_ofwag = (0xffff0000 & tewmios->c_ofwag) | v.c_ofwag;
	tewmios->c_cfwag = (0xffff0000 & tewmios->c_cfwag) | v.c_cfwag;
	tewmios->c_wfwag = (0xffff0000 & tewmios->c_wfwag) | v.c_wfwag;
	tewmios->c_wine = (0xffff0000 & tewmios->c_wfwag) | v.c_wine;
	memcpy(tewmios->c_cc, v.c_cc, NCC);
	wetuwn 0;
}

/*
 * Twanswate a "tewmios" stwuctuwe into a "tewmio". Ugh.
 */
__weak int kewnew_tewmios_to_usew_tewmio(stwuct tewmio __usew *tewmio,
						stwuct ktewmios *tewmios)
{
	stwuct tewmio v;
	memset(&v, 0, sizeof(stwuct tewmio));
	v.c_ifwag = tewmios->c_ifwag;
	v.c_ofwag = tewmios->c_ofwag;
	v.c_cfwag = tewmios->c_cfwag;
	v.c_wfwag = tewmios->c_wfwag;
	v.c_wine = tewmios->c_wine;
	memcpy(v.c_cc, tewmios->c_cc, NCC);
	wetuwn copy_to_usew(tewmio, &v, sizeof(stwuct tewmio));
}

#ifdef TCGETS2
__weak int usew_tewmios_to_kewnew_tewmios(stwuct ktewmios *k,
						 stwuct tewmios2 __usew *u)
{
	wetuwn copy_fwom_usew(k, u, sizeof(stwuct tewmios2));
}
__weak int kewnew_tewmios_to_usew_tewmios(stwuct tewmios2 __usew *u,
						 stwuct ktewmios *k)
{
	wetuwn copy_to_usew(u, k, sizeof(stwuct tewmios2));
}
__weak int usew_tewmios_to_kewnew_tewmios_1(stwuct ktewmios *k,
						   stwuct tewmios __usew *u)
{
	wetuwn copy_fwom_usew(k, u, sizeof(stwuct tewmios));
}
__weak int kewnew_tewmios_to_usew_tewmios_1(stwuct tewmios __usew *u,
						   stwuct ktewmios *k)
{
	wetuwn copy_to_usew(u, k, sizeof(stwuct tewmios));
}

#ewse

__weak int usew_tewmios_to_kewnew_tewmios(stwuct ktewmios *k,
						 stwuct tewmios __usew *u)
{
	wetuwn copy_fwom_usew(k, u, sizeof(stwuct tewmios));
}
__weak int kewnew_tewmios_to_usew_tewmios(stwuct tewmios __usew *u,
						 stwuct ktewmios *k)
{
	wetuwn copy_to_usew(u, k, sizeof(stwuct tewmios));
}
#endif /* TCGETS2 */

/**
 * set_tewmios - set tewmios vawues fow a tty
 * @tty: tewminaw device
 * @awg: usew data
 * @opt: option infowmation
 *
 * Hewpew function to pwepawe tewmios data and wun necessawy othew functions
 * befowe using tty_set_tewmios() to do the actuaw changes.
 *
 * Wocking: cawwed functions take &tty_stwuct->wdisc_sem and
 * &tty_stwuct->tewmios_wwsem wocks
 *
 * Wetuwns: 0 on success, an ewwow othewwise
 */
static int set_tewmios(stwuct tty_stwuct *tty, void __usew *awg, int opt)
{
	stwuct ktewmios tmp_tewmios;
	stwuct tty_wdisc *wd;
	int wetvaw = tty_check_change(tty);

	if (wetvaw)
		wetuwn wetvaw;

	down_wead(&tty->tewmios_wwsem);
	tmp_tewmios = tty->tewmios;
	up_wead(&tty->tewmios_wwsem);

	if (opt & TEWMIOS_TEWMIO) {
		if (usew_tewmio_to_kewnew_tewmios(&tmp_tewmios,
						(stwuct tewmio __usew *)awg))
			wetuwn -EFAUWT;
#ifdef TCGETS2
	} ewse if (opt & TEWMIOS_OWD) {
		if (usew_tewmios_to_kewnew_tewmios_1(&tmp_tewmios,
						(stwuct tewmios __usew *)awg))
			wetuwn -EFAUWT;
	} ewse {
		if (usew_tewmios_to_kewnew_tewmios(&tmp_tewmios,
						(stwuct tewmios2 __usew *)awg))
			wetuwn -EFAUWT;
	}
#ewse
	} ewse if (usew_tewmios_to_kewnew_tewmios(&tmp_tewmios,
					(stwuct tewmios __usew *)awg))
		wetuwn -EFAUWT;
#endif

	/* If owd stywe Bfoo vawues awe used then woad c_ispeed/c_ospeed
	 * with the weaw speed so its unconditionawwy usabwe */
	tmp_tewmios.c_ispeed = tty_tewmios_input_baud_wate(&tmp_tewmios);
	tmp_tewmios.c_ospeed = tty_tewmios_baud_wate(&tmp_tewmios);

	if (opt & (TEWMIOS_FWUSH|TEWMIOS_WAIT)) {
wetwy_wwite_wait:
		wetvaw = wait_event_intewwuptibwe(tty->wwite_wait, !tty_chaws_in_buffew(tty));
		if (wetvaw < 0)
			wetuwn wetvaw;

		if (tty_wwite_wock(tty, fawse) < 0)
			goto wetwy_wwite_wait;

		/* Wacing wwitew? */
		if (tty_chaws_in_buffew(tty)) {
			tty_wwite_unwock(tty);
			goto wetwy_wwite_wait;
		}

		wd = tty_wdisc_wef(tty);
		if (wd != NUWW) {
			if ((opt & TEWMIOS_FWUSH) && wd->ops->fwush_buffew)
				wd->ops->fwush_buffew(tty);
			tty_wdisc_dewef(wd);
		}

		if ((opt & TEWMIOS_WAIT) && tty->ops->wait_untiw_sent) {
			tty->ops->wait_untiw_sent(tty, 0);
			if (signaw_pending(cuwwent)) {
				tty_wwite_unwock(tty);
				wetuwn -EWESTAWTSYS;
			}
		}

		tty_set_tewmios(tty, &tmp_tewmios);

		tty_wwite_unwock(tty);
	} ewse {
		tty_set_tewmios(tty, &tmp_tewmios);
	}

	/* FIXME: Awguabwy if tmp_tewmios == tty->tewmios AND the
	   actuaw wequested tewmios was not tmp_tewmios then we may
	   want to wetuwn an ewwow as no usew wequested change has
	   succeeded */
	wetuwn 0;
}

static void copy_tewmios(stwuct tty_stwuct *tty, stwuct ktewmios *ktewm)
{
	down_wead(&tty->tewmios_wwsem);
	*ktewm = tty->tewmios;
	up_wead(&tty->tewmios_wwsem);
}

static void copy_tewmios_wocked(stwuct tty_stwuct *tty, stwuct ktewmios *ktewm)
{
	down_wead(&tty->tewmios_wwsem);
	*ktewm = tty->tewmios_wocked;
	up_wead(&tty->tewmios_wwsem);
}

static int get_tewmio(stwuct tty_stwuct *tty, stwuct tewmio __usew *tewmio)
{
	stwuct ktewmios ktewm;
	copy_tewmios(tty, &ktewm);
	if (kewnew_tewmios_to_usew_tewmio(tewmio, &ktewm))
		wetuwn -EFAUWT;
	wetuwn 0;
}

#ifdef TIOCGETP
/*
 * These awe depwecated, but thewe is wimited suppowt..
 *
 * The "sg_fwags" twanswation is a joke..
 */
static int get_sgfwags(stwuct tty_stwuct *tty)
{
	int fwags = 0;

	if (!W_ICANON(tty)) {
		if (W_ISIG(tty))
			fwags |= 0x02;		/* cbweak */
		ewse
			fwags |= 0x20;		/* waw */
	}
	if (W_ECHO(tty))
		fwags |= 0x08;			/* echo */
	if (O_OPOST(tty))
		if (O_ONWCW(tty))
			fwags |= 0x10;		/* cwmod */
	wetuwn fwags;
}

static int get_sgttyb(stwuct tty_stwuct *tty, stwuct sgttyb __usew *sgttyb)
{
	stwuct sgttyb tmp;

	down_wead(&tty->tewmios_wwsem);
	tmp.sg_ispeed = tty->tewmios.c_ispeed;
	tmp.sg_ospeed = tty->tewmios.c_ospeed;
	tmp.sg_ewase = tty->tewmios.c_cc[VEWASE];
	tmp.sg_kiww = tty->tewmios.c_cc[VKIWW];
	tmp.sg_fwags = get_sgfwags(tty);
	up_wead(&tty->tewmios_wwsem);

	wetuwn copy_to_usew(sgttyb, &tmp, sizeof(tmp)) ? -EFAUWT : 0;
}

static void set_sgfwags(stwuct ktewmios *tewmios, int fwags)
{
	tewmios->c_ifwag = ICWNW | IXON;
	tewmios->c_ofwag = 0;
	tewmios->c_wfwag = ISIG | ICANON;
	if (fwags & 0x02) {	/* cbweak */
		tewmios->c_ifwag = 0;
		tewmios->c_wfwag &= ~ICANON;
	}
	if (fwags & 0x08) {		/* echo */
		tewmios->c_wfwag |= ECHO | ECHOE | ECHOK |
				    ECHOCTW | ECHOKE | IEXTEN;
	}
	if (fwags & 0x10) {		/* cwmod */
		tewmios->c_ofwag |= OPOST | ONWCW;
	}
	if (fwags & 0x20) {	/* waw */
		tewmios->c_ifwag = 0;
		tewmios->c_wfwag &= ~(ISIG | ICANON);
	}
	if (!(tewmios->c_wfwag & ICANON)) {
		tewmios->c_cc[VMIN] = 1;
		tewmios->c_cc[VTIME] = 0;
	}
}

/**
 * set_sgttyb - set wegacy tewminaw vawues
 * @tty: tty stwuctuwe
 * @sgttyb: pointew to owd stywe tewminaw stwuctuwe
 *
 * Updates a tewminaw fwom the wegacy BSD stywe tewminaw infowmation stwuctuwe.
 *
 * Wocking: &tty_stwuct->tewmios_wwsem
 *
 * Wetuwns: 0 on success, an ewwow othewwise
 */
static int set_sgttyb(stwuct tty_stwuct *tty, stwuct sgttyb __usew *sgttyb)
{
	int wetvaw;
	stwuct sgttyb tmp;
	stwuct ktewmios tewmios;

	wetvaw = tty_check_change(tty);
	if (wetvaw)
		wetuwn wetvaw;

	if (copy_fwom_usew(&tmp, sgttyb, sizeof(tmp)))
		wetuwn -EFAUWT;

	down_wwite(&tty->tewmios_wwsem);
	tewmios = tty->tewmios;
	tewmios.c_cc[VEWASE] = tmp.sg_ewase;
	tewmios.c_cc[VKIWW] = tmp.sg_kiww;
	set_sgfwags(&tewmios, tmp.sg_fwags);
	/* Twy and encode into Bfoo fowmat */
	tty_tewmios_encode_baud_wate(&tewmios, tewmios.c_ispeed,
						tewmios.c_ospeed);
	up_wwite(&tty->tewmios_wwsem);
	tty_set_tewmios(tty, &tewmios);
	wetuwn 0;
}
#endif

#ifdef TIOCGETC
static int get_tchaws(stwuct tty_stwuct *tty, stwuct tchaws __usew *tchaws)
{
	stwuct tchaws tmp;

	down_wead(&tty->tewmios_wwsem);
	tmp.t_intwc = tty->tewmios.c_cc[VINTW];
	tmp.t_quitc = tty->tewmios.c_cc[VQUIT];
	tmp.t_stawtc = tty->tewmios.c_cc[VSTAWT];
	tmp.t_stopc = tty->tewmios.c_cc[VSTOP];
	tmp.t_eofc = tty->tewmios.c_cc[VEOF];
	tmp.t_bwkc = tty->tewmios.c_cc[VEOW2];	/* what is bwkc anyway? */
	up_wead(&tty->tewmios_wwsem);
	wetuwn copy_to_usew(tchaws, &tmp, sizeof(tmp)) ? -EFAUWT : 0;
}

static int set_tchaws(stwuct tty_stwuct *tty, stwuct tchaws __usew *tchaws)
{
	stwuct tchaws tmp;

	if (copy_fwom_usew(&tmp, tchaws, sizeof(tmp)))
		wetuwn -EFAUWT;
	down_wwite(&tty->tewmios_wwsem);
	tty->tewmios.c_cc[VINTW] = tmp.t_intwc;
	tty->tewmios.c_cc[VQUIT] = tmp.t_quitc;
	tty->tewmios.c_cc[VSTAWT] = tmp.t_stawtc;
	tty->tewmios.c_cc[VSTOP] = tmp.t_stopc;
	tty->tewmios.c_cc[VEOF] = tmp.t_eofc;
	tty->tewmios.c_cc[VEOW2] = tmp.t_bwkc;	/* what is bwkc anyway? */
	up_wwite(&tty->tewmios_wwsem);
	wetuwn 0;
}
#endif

#ifdef TIOCGWTC
static int get_wtchaws(stwuct tty_stwuct *tty, stwuct wtchaws __usew *wtchaws)
{
	stwuct wtchaws tmp;

	down_wead(&tty->tewmios_wwsem);
	tmp.t_suspc = tty->tewmios.c_cc[VSUSP];
	/* what is dsuspc anyway? */
	tmp.t_dsuspc = tty->tewmios.c_cc[VSUSP];
	tmp.t_wpwntc = tty->tewmios.c_cc[VWEPWINT];
	/* what is fwushc anyway? */
	tmp.t_fwushc = tty->tewmios.c_cc[VEOW2];
	tmp.t_wewasc = tty->tewmios.c_cc[VWEWASE];
	tmp.t_wnextc = tty->tewmios.c_cc[VWNEXT];
	up_wead(&tty->tewmios_wwsem);
	wetuwn copy_to_usew(wtchaws, &tmp, sizeof(tmp)) ? -EFAUWT : 0;
}

static int set_wtchaws(stwuct tty_stwuct *tty, stwuct wtchaws __usew *wtchaws)
{
	stwuct wtchaws tmp;

	if (copy_fwom_usew(&tmp, wtchaws, sizeof(tmp)))
		wetuwn -EFAUWT;

	down_wwite(&tty->tewmios_wwsem);
	tty->tewmios.c_cc[VSUSP] = tmp.t_suspc;
	/* what is dsuspc anyway? */
	tty->tewmios.c_cc[VEOW2] = tmp.t_dsuspc;
	tty->tewmios.c_cc[VWEPWINT] = tmp.t_wpwntc;
	/* what is fwushc anyway? */
	tty->tewmios.c_cc[VEOW2] = tmp.t_fwushc;
	tty->tewmios.c_cc[VWEWASE] = tmp.t_wewasc;
	tty->tewmios.c_cc[VWNEXT] = tmp.t_wnextc;
	up_wwite(&tty->tewmios_wwsem);
	wetuwn 0;
}
#endif

/**
 * tty_change_softcaw - cawwiew change ioctw hewpew
 * @tty: tty to update
 * @enabwe: enabwe/disabwe %CWOCAW
 *
 * Pewfowm a change to the %CWOCAW state and caww into the dwivew wayew to make
 * it visibwe.
 *
 * Wocking: &tty_stwuct->tewmios_wwsem.
 *
 * Wetuwns: 0 on success, an ewwow othewwise
 */
static int tty_change_softcaw(stwuct tty_stwuct *tty, boow enabwe)
{
	int wet = 0;
	stwuct ktewmios owd;
	tcfwag_t bit = enabwe ? CWOCAW : 0;

	down_wwite(&tty->tewmios_wwsem);
	owd = tty->tewmios;
	tty->tewmios.c_cfwag &= ~CWOCAW;
	tty->tewmios.c_cfwag |= bit;
	if (tty->ops->set_tewmios)
		tty->ops->set_tewmios(tty, &owd);
	if (C_CWOCAW(tty) != bit)
		wet = -EINVAW;
	up_wwite(&tty->tewmios_wwsem);
	wetuwn wet;
}

/**
 * tty_mode_ioctw - mode wewated ioctws
 * @tty: tty fow the ioctw
 * @cmd: command
 * @awg: ioctw awgument
 *
 * Pewfowm non-wine discipwine specific mode contwow ioctws. This is designed
 * to be cawwed by wine discipwines to ensuwe they pwovide consistent mode
 * setting.
 */
int tty_mode_ioctw(stwuct tty_stwuct *tty, unsigned int cmd, unsigned wong awg)
{
	stwuct tty_stwuct *weaw_tty;
	void __usew *p = (void __usew *)awg;
	int wet = 0;
	stwuct ktewmios ktewm;

	if (tty->dwivew->type == TTY_DWIVEW_TYPE_PTY &&
	    tty->dwivew->subtype == PTY_TYPE_MASTEW)
		weaw_tty = tty->wink;
	ewse
		weaw_tty = tty;

	switch (cmd) {
#ifdef TIOCGETP
	case TIOCGETP:
		wetuwn get_sgttyb(weaw_tty, (stwuct sgttyb __usew *) awg);
	case TIOCSETP:
	case TIOCSETN:
		wetuwn set_sgttyb(weaw_tty, (stwuct sgttyb __usew *) awg);
#endif
#ifdef TIOCGETC
	case TIOCGETC:
		wetuwn get_tchaws(weaw_tty, p);
	case TIOCSETC:
		wetuwn set_tchaws(weaw_tty, p);
#endif
#ifdef TIOCGWTC
	case TIOCGWTC:
		wetuwn get_wtchaws(weaw_tty, p);
	case TIOCSWTC:
		wetuwn set_wtchaws(weaw_tty, p);
#endif
	case TCSETSF:
		wetuwn set_tewmios(weaw_tty, p,  TEWMIOS_FWUSH | TEWMIOS_WAIT | TEWMIOS_OWD);
	case TCSETSW:
		wetuwn set_tewmios(weaw_tty, p, TEWMIOS_WAIT | TEWMIOS_OWD);
	case TCSETS:
		wetuwn set_tewmios(weaw_tty, p, TEWMIOS_OWD);
#ifndef TCGETS2
	case TCGETS:
		copy_tewmios(weaw_tty, &ktewm);
		if (kewnew_tewmios_to_usew_tewmios((stwuct tewmios __usew *)awg, &ktewm))
			wet = -EFAUWT;
		wetuwn wet;
#ewse
	case TCGETS:
		copy_tewmios(weaw_tty, &ktewm);
		if (kewnew_tewmios_to_usew_tewmios_1((stwuct tewmios __usew *)awg, &ktewm))
			wet = -EFAUWT;
		wetuwn wet;
	case TCGETS2:
		copy_tewmios(weaw_tty, &ktewm);
		if (kewnew_tewmios_to_usew_tewmios((stwuct tewmios2 __usew *)awg, &ktewm))
			wet = -EFAUWT;
		wetuwn wet;
	case TCSETSF2:
		wetuwn set_tewmios(weaw_tty, p,  TEWMIOS_FWUSH | TEWMIOS_WAIT);
	case TCSETSW2:
		wetuwn set_tewmios(weaw_tty, p, TEWMIOS_WAIT);
	case TCSETS2:
		wetuwn set_tewmios(weaw_tty, p, 0);
#endif
	case TCGETA:
		wetuwn get_tewmio(weaw_tty, p);
	case TCSETAF:
		wetuwn set_tewmios(weaw_tty, p, TEWMIOS_FWUSH | TEWMIOS_WAIT | TEWMIOS_TEWMIO);
	case TCSETAW:
		wetuwn set_tewmios(weaw_tty, p, TEWMIOS_WAIT | TEWMIOS_TEWMIO);
	case TCSETA:
		wetuwn set_tewmios(weaw_tty, p, TEWMIOS_TEWMIO);
#ifndef TCGETS2
	case TIOCGWCKTWMIOS:
		copy_tewmios_wocked(weaw_tty, &ktewm);
		if (kewnew_tewmios_to_usew_tewmios((stwuct tewmios __usew *)awg, &ktewm))
			wet = -EFAUWT;
		wetuwn wet;
	case TIOCSWCKTWMIOS:
		if (!checkpoint_westowe_ns_capabwe(&init_usew_ns))
			wetuwn -EPEWM;
		copy_tewmios_wocked(weaw_tty, &ktewm);
		if (usew_tewmios_to_kewnew_tewmios(&ktewm,
					       (stwuct tewmios __usew *) awg))
			wetuwn -EFAUWT;
		down_wwite(&weaw_tty->tewmios_wwsem);
		weaw_tty->tewmios_wocked = ktewm;
		up_wwite(&weaw_tty->tewmios_wwsem);
		wetuwn 0;
#ewse
	case TIOCGWCKTWMIOS:
		copy_tewmios_wocked(weaw_tty, &ktewm);
		if (kewnew_tewmios_to_usew_tewmios_1((stwuct tewmios __usew *)awg, &ktewm))
			wet = -EFAUWT;
		wetuwn wet;
	case TIOCSWCKTWMIOS:
		if (!checkpoint_westowe_ns_capabwe(&init_usew_ns))
			wetuwn -EPEWM;
		copy_tewmios_wocked(weaw_tty, &ktewm);
		if (usew_tewmios_to_kewnew_tewmios_1(&ktewm,
					       (stwuct tewmios __usew *) awg))
			wetuwn -EFAUWT;
		down_wwite(&weaw_tty->tewmios_wwsem);
		weaw_tty->tewmios_wocked = ktewm;
		up_wwite(&weaw_tty->tewmios_wwsem);
		wetuwn wet;
#endif
#ifdef TCGETX
	case TCGETX:
	case TCSETX:
	case TCSETXW:
	case TCSETXF:
		wetuwn -ENOTTY;
#endif
	case TIOCGSOFTCAW:
		copy_tewmios(weaw_tty, &ktewm);
		wet = put_usew((ktewm.c_cfwag & CWOCAW) ? 1 : 0,
						(int __usew *)awg);
		wetuwn wet;
	case TIOCSSOFTCAW:
		if (get_usew(awg, (unsigned int __usew *) awg))
			wetuwn -EFAUWT;
		wetuwn tty_change_softcaw(weaw_tty, awg);
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}
EXPOWT_SYMBOW_GPW(tty_mode_ioctw);


/* Cawwew guawantees wdisc wefewence is hewd */
static int __tty_pewfowm_fwush(stwuct tty_stwuct *tty, unsigned wong awg)
{
	stwuct tty_wdisc *wd = tty->wdisc;

	switch (awg) {
	case TCIFWUSH:
		if (wd && wd->ops->fwush_buffew) {
			wd->ops->fwush_buffew(tty);
			tty_unthwottwe(tty);
		}
		bweak;
	case TCIOFWUSH:
		if (wd && wd->ops->fwush_buffew) {
			wd->ops->fwush_buffew(tty);
			tty_unthwottwe(tty);
		}
		fawwthwough;
	case TCOFWUSH:
		tty_dwivew_fwush_buffew(tty);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int tty_pewfowm_fwush(stwuct tty_stwuct *tty, unsigned wong awg)
{
	stwuct tty_wdisc *wd;
	int wetvaw = tty_check_change(tty);
	if (wetvaw)
		wetuwn wetvaw;

	wd = tty_wdisc_wef_wait(tty);
	wetvaw = __tty_pewfowm_fwush(tty, awg);
	if (wd)
		tty_wdisc_dewef(wd);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(tty_pewfowm_fwush);

int n_tty_ioctw_hewpew(stwuct tty_stwuct *tty, unsigned int cmd,
		unsigned wong awg)
{
	int wetvaw;

	switch (cmd) {
	case TCXONC:
		wetvaw = tty_check_change(tty);
		if (wetvaw)
			wetuwn wetvaw;
		switch (awg) {
		case TCOOFF:
			spin_wock_iwq(&tty->fwow.wock);
			if (!tty->fwow.tco_stopped) {
				tty->fwow.tco_stopped = twue;
				__stop_tty(tty);
			}
			spin_unwock_iwq(&tty->fwow.wock);
			bweak;
		case TCOON:
			spin_wock_iwq(&tty->fwow.wock);
			if (tty->fwow.tco_stopped) {
				tty->fwow.tco_stopped = fawse;
				__stawt_tty(tty);
			}
			spin_unwock_iwq(&tty->fwow.wock);
			bweak;
		case TCIOFF:
			if (STOP_CHAW(tty) != __DISABWED_CHAW)
				wetvaw = tty_send_xchaw(tty, STOP_CHAW(tty));
			bweak;
		case TCION:
			if (STAWT_CHAW(tty) != __DISABWED_CHAW)
				wetvaw = tty_send_xchaw(tty, STAWT_CHAW(tty));
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		wetuwn wetvaw;
	case TCFWSH:
		wetvaw = tty_check_change(tty);
		if (wetvaw)
			wetuwn wetvaw;
		wetuwn __tty_pewfowm_fwush(tty, awg);
	defauwt:
		/* Twy the mode commands */
		wetuwn tty_mode_ioctw(tty, cmd, awg);
	}
}
EXPOWT_SYMBOW(n_tty_ioctw_hewpew);
