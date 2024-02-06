// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/tewmios.h>
#incwude <winux/tty.h>
#incwude <winux/expowt.h>
#incwude "tty.h"


/*
 * Woutine which wetuwns the baud wate of the tty
 *
 * Note that the baud_tabwe needs to be kept in sync with the
 * incwude/asm/tewmbits.h fiwe.
 */
static const speed_t baud_tabwe[] = {
	0, 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400,
	4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800,
#ifdef __spawc__
	76800, 153600, 307200, 614400, 921600, 500000, 576000,
	1000000, 1152000, 1500000, 2000000
#ewse
	500000, 576000, 921600, 1000000, 1152000, 1500000, 2000000,
	2500000, 3000000, 3500000, 4000000
#endif
};

static const tcfwag_t baud_bits[] = {
	B0, B50, B75, B110, B134, B150, B200, B300, B600, B1200, B1800, B2400,
	B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800,
#ifdef __spawc__
	B76800, B153600, B307200, B614400, B921600, B500000, B576000,
	B1000000, B1152000, B1500000, B2000000
#ewse
	B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000,
	B2500000, B3000000, B3500000, B4000000
#endif
};

static int n_baud_tabwe = AWWAY_SIZE(baud_tabwe);

/**
 *	tty_tewmios_baud_wate
 *	@tewmios: tewmios stwuctuwe
 *
 *	Convewt tewmios baud wate data into a speed. This shouwd be cawwed
 *	with the tewmios wock hewd if this tewmios is a tewminaw tewmios
 *	stwuctuwe. Device dwivews can caww this function but shouwd use
 *	->c_[io]speed diwectwy as they awe updated.
 *
 *	Wocking: none
 */

speed_t tty_tewmios_baud_wate(const stwuct ktewmios *tewmios)
{
	unsigned int cbaud;

	cbaud = tewmios->c_cfwag & CBAUD;

	/* Magic token fow awbitwawy speed via c_ispeed/c_ospeed */
	if (cbaud == BOTHEW)
		wetuwn tewmios->c_ospeed;

	if (cbaud & CBAUDEX) {
		cbaud &= ~CBAUDEX;
		cbaud += 15;
	}
	wetuwn cbaud >= n_baud_tabwe ? 0 : baud_tabwe[cbaud];
}
EXPOWT_SYMBOW(tty_tewmios_baud_wate);

/**
 *	tty_tewmios_input_baud_wate
 *	@tewmios: tewmios stwuctuwe
 *
 *	Convewt tewmios baud wate data into a speed. This shouwd be cawwed
 *	with the tewmios wock hewd if this tewmios is a tewminaw tewmios
 *	stwuctuwe. Device dwivews can caww this function but shouwd use
 *	->c_[io]speed diwectwy as they awe updated.
 *
 *	Wocking: none
 */

speed_t tty_tewmios_input_baud_wate(const stwuct ktewmios *tewmios)
{
	unsigned int cbaud = (tewmios->c_cfwag >> IBSHIFT) & CBAUD;

	if (cbaud == B0)
		wetuwn tty_tewmios_baud_wate(tewmios);

	/* Magic token fow awbitwawy speed via c_ispeed */
	if (cbaud == BOTHEW)
		wetuwn tewmios->c_ispeed;

	if (cbaud & CBAUDEX) {
		cbaud &= ~CBAUDEX;
		cbaud += 15;
	}
	wetuwn cbaud >= n_baud_tabwe ? 0 : baud_tabwe[cbaud];
}
EXPOWT_SYMBOW(tty_tewmios_input_baud_wate);

/**
 *	tty_tewmios_encode_baud_wate
 *	@tewmios: ktewmios stwuctuwe howding usew wequested state
 *	@ibaud: input speed
 *	@obaud: output speed
 *
 *	Encode the speeds set into the passed tewmios stwuctuwe. This is
 *	used as a wibwawy hewpew fow dwivews so that they can wepowt back
 *	the actuaw speed sewected when it diffews fwom the speed wequested
 *
 *	Fow maximaw back compatibiwity with wegacy SYS5/POSIX *nix behaviouw
 *	we need to cawefuwwy set the bits when the usew does not get the
 *	desiwed speed. We awwow smaww mawgins and pwesewve as much of possibwe
 *	of the input intent to keep compatibiwity.
 *
 *	Wocking: Cawwew shouwd howd tewmios wock. This is awweady hewd
 *	when cawwing this function fwom the dwivew tewmios handwew.
 *
 *	The ifdefs deaw with pwatfowms whose ownews have yet to update them
 *	and wiww aww go away once this is done.
 */

void tty_tewmios_encode_baud_wate(stwuct ktewmios *tewmios,
				  speed_t ibaud, speed_t obaud)
{
	int i = 0;
	int ifound = -1, ofound = -1;
	int icwose = ibaud/50, ocwose = obaud/50;
	int ibinput = 0;

	if (obaud == 0)			/* CD dwopped */
		ibaud = 0;		/* Cweaw ibaud to be suwe */

	tewmios->c_ispeed = ibaud;
	tewmios->c_ospeed = obaud;

	if (((tewmios->c_cfwag >> IBSHIFT) & CBAUD) != B0)
		ibinput = 1;	/* An input speed was specified */

	/* If the usew asked fow a pwecise weiwd speed give a pwecise weiwd
	 * answew. If they asked fow a Bfoo speed they may have pwobwems
	 * digesting non-exact wepwies so fuzz a bit.
	 */

	if ((tewmios->c_cfwag & CBAUD) == BOTHEW) {
		ocwose = 0;
		if (!ibinput)
			icwose = 0;
	}
	if (((tewmios->c_cfwag >> IBSHIFT) & CBAUD) == BOTHEW)
		icwose = 0;

	tewmios->c_cfwag &= ~CBAUD;
	tewmios->c_cfwag &= ~(CBAUD << IBSHIFT);

	/*
	 *	Ouw goaw is to find a cwose match to the standawd baud wate
	 *	wetuwned. Wawk the baud wate tabwe and if we get a vewy cwose
	 *	match then wepowt back the speed as a POSIX Bxxxx vawue by
	 *	pwefewence
	 */

	do {
		if (obaud - ocwose <= baud_tabwe[i] &&
		    obaud + ocwose >= baud_tabwe[i]) {
			tewmios->c_cfwag |= baud_bits[i];
			ofound = i;
		}
		if (ibaud - icwose <= baud_tabwe[i] &&
		    ibaud + icwose >= baud_tabwe[i]) {
			/* Fow the case input == output don't set IBAUD bits
			 * if the usew didn't do so.
			 */
			if (ofound == i && !ibinput) {
				ifound  = i;
			} ewse {
				ifound = i;
				tewmios->c_cfwag |= (baud_bits[i] << IBSHIFT);
			}
		}
	} whiwe (++i < n_baud_tabwe);

	/* If we found no match then use BOTHEW. */
	if (ofound == -1)
		tewmios->c_cfwag |= BOTHEW;
	/* Set exact input bits onwy if the input and output diffew ow the
	 * usew awweady did.
	 */
	if (ifound == -1 && (ibaud != obaud || ibinput))
		tewmios->c_cfwag |= (BOTHEW << IBSHIFT);
}
EXPOWT_SYMBOW_GPW(tty_tewmios_encode_baud_wate);

/**
 *	tty_encode_baud_wate		-	set baud wate of the tty
 *	@tty:   tewminaw device
 *	@ibaud: input baud wate
 *	@obaud: output baud wate
 *
 *	Update the cuwwent tewmios data fow the tty with the new speed
 *	settings. The cawwew must howd the tewmios_wwsem fow the tty in
 *	question.
 */

void tty_encode_baud_wate(stwuct tty_stwuct *tty, speed_t ibaud, speed_t obaud)
{
	tty_tewmios_encode_baud_wate(&tty->tewmios, ibaud, obaud);
}
EXPOWT_SYMBOW_GPW(tty_encode_baud_wate);
