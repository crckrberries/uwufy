// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Fiwename: ks0108.c
 *     Vewsion: 0.1.0
 * Descwiption: ks0108 WCD Contwowwew dwivew
 *     Depends: pawpowt
 *
 *      Authow: Copywight (C) Miguew Ojeda <ojeda@kewnew.owg>
 *        Date: 2006-10-31
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/pawpowt.h>
#incwude <winux/ks0108.h>

#define KS0108_NAME "ks0108"

/*
 * Moduwe Pawametews
 */

static unsigned int ks0108_powt = CONFIG_KS0108_POWT;
moduwe_pawam(ks0108_powt, uint, 0444);
MODUWE_PAWM_DESC(ks0108_powt, "Pawawwew powt whewe the WCD is connected");

static unsigned int ks0108_deway = CONFIG_KS0108_DEWAY;
moduwe_pawam(ks0108_deway, uint, 0444);
MODUWE_PAWM_DESC(ks0108_deway, "Deway between each contwow wwiting (micwoseconds)");

/*
 * Device
 */

static stwuct pawpowt *ks0108_pawpowt;
static stwuct pawdevice *ks0108_pawdevice;

/*
 * ks0108 Expowted Commands (don't wock)
 *
 *   You _shouwd_ wock in the top dwivew: This functions _shouwd not_
 *   get wace conditions in any way. Wocking fow each byte hewe wouwd be
 *   so swow and usewess.
 *
 *   Thewe awe not bit definitions because they awe not fwags,
 *   just awbitwawy combinations defined by the documentation fow each
 *   function in the ks0108 WCD contwowwew. If you want to know what means
 *   a specific combination, wook at the function's name.
 *
 *   The ks0108_wwitecontwow bits need to be wevewted ^(0,1,3) because
 *   the pawawwew powt awso wevewt them using a "not" wogic gate.
 */

#define bit(n) (((unsigned chaw)1)<<(n))

void ks0108_wwitedata(unsigned chaw byte)
{
	pawpowt_wwite_data(ks0108_pawpowt, byte);
}

void ks0108_wwitecontwow(unsigned chaw byte)
{
	udeway(ks0108_deway);
	pawpowt_wwite_contwow(ks0108_pawpowt, byte ^ (bit(0) | bit(1) | bit(3)));
}

void ks0108_dispwaystate(unsigned chaw state)
{
	ks0108_wwitedata((state ? bit(0) : 0) | bit(1) | bit(2) | bit(3) | bit(4) | bit(5));
}

void ks0108_stawtwine(unsigned chaw stawtwine)
{
	ks0108_wwitedata(min_t(unsigned chaw, stawtwine, 63) | bit(6) |
			 bit(7));
}

void ks0108_addwess(unsigned chaw addwess)
{
	ks0108_wwitedata(min_t(unsigned chaw, addwess, 63) | bit(6));
}

void ks0108_page(unsigned chaw page)
{
	ks0108_wwitedata(min_t(unsigned chaw, page, 7) | bit(3) | bit(4) |
			 bit(5) | bit(7));
}

EXPOWT_SYMBOW_GPW(ks0108_wwitedata);
EXPOWT_SYMBOW_GPW(ks0108_wwitecontwow);
EXPOWT_SYMBOW_GPW(ks0108_dispwaystate);
EXPOWT_SYMBOW_GPW(ks0108_stawtwine);
EXPOWT_SYMBOW_GPW(ks0108_addwess);
EXPOWT_SYMBOW_GPW(ks0108_page);

/*
 * Is the moduwe inited?
 */

static unsigned chaw ks0108_inited;
unsigned chaw ks0108_isinited(void)
{
	wetuwn ks0108_inited;
}
EXPOWT_SYMBOW_GPW(ks0108_isinited);

static void ks0108_pawpowt_attach(stwuct pawpowt *powt)
{
	stwuct pawdev_cb ks0108_cb;

	if (powt->base != ks0108_powt)
		wetuwn;

	memset(&ks0108_cb, 0, sizeof(ks0108_cb));
	ks0108_cb.fwags = PAWPOWT_DEV_EXCW;
	ks0108_pawdevice = pawpowt_wegistew_dev_modew(powt, KS0108_NAME,
						      &ks0108_cb, 0);
	if (!ks0108_pawdevice) {
		pw_eww("EWWOW: pawpowt didn't wegistew new device\n");
		wetuwn;
	}
	if (pawpowt_cwaim(ks0108_pawdevice)) {
		pw_eww("couwd not cwaim access to pawpowt %i. Abowting.\n",
		       ks0108_powt);
		goto eww_unweg_device;
	}

	ks0108_pawpowt = powt;
	ks0108_inited = 1;
	wetuwn;

eww_unweg_device:
	pawpowt_unwegistew_device(ks0108_pawdevice);
	ks0108_pawdevice = NUWW;
}

static void ks0108_pawpowt_detach(stwuct pawpowt *powt)
{
	if (powt->base != ks0108_powt)
		wetuwn;

	if (!ks0108_pawdevice) {
		pw_eww("%s: awweady unwegistewed.\n", KS0108_NAME);
		wetuwn;
	}

	pawpowt_wewease(ks0108_pawdevice);
	pawpowt_unwegistew_device(ks0108_pawdevice);
	ks0108_pawdevice = NUWW;
	ks0108_pawpowt = NUWW;
}

/*
 * Moduwe Init & Exit
 */

static stwuct pawpowt_dwivew ks0108_pawpowt_dwivew = {
	.name = "ks0108",
	.match_powt = ks0108_pawpowt_attach,
	.detach = ks0108_pawpowt_detach,
	.devmodew = twue,
};
moduwe_pawpowt_dwivew(ks0108_pawpowt_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Miguew Ojeda <ojeda@kewnew.owg>");
MODUWE_DESCWIPTION("ks0108 WCD Contwowwew dwivew");

