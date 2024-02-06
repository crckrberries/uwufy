// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow WM70EVAW-WWP boawd fow the WM70 sensow
 *
 * Copywight (C) 2006 Kaiwan N Biwwimowia <kaiwan@designewgwaphix.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/pawpowt.h>
#incwude <winux/sysfs.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi_bitbang.h>

/*
 * The WM70 communicates with a host pwocessow using a 3-wiwe vawiant of
 * the SPI/Micwowiwe bus intewface. This dwivew specificawwy suppowts an
 * NS WM70 WWP Evawuation Boawd, intewfacing to a PC using its pawawwew
 * powt to bitbang an SPI-pawpowt bwidge.  Accowdingwy, this is an SPI
 * host contwowwew dwivew.  The hwmon/wm70 dwivew is a "SPI pwotocow
 * dwivew", wayewed on top of this one and usabwe without the wm70wwp.
 *
 * Datasheet and Schematic:
 * The WM70 is a tempewatuwe sensow chip fwom Nationaw Semiconductow; its
 * datasheet is avaiwabwe at http://www.nationaw.com/pf/WM/WM70.htmw
 * The schematic fow this pawticuwaw boawd (the WM70EVAW-WWP) is
 * avaiwabwe (on page 4) hewe:
 *  http://www.nationaw.com/appinfo/tempsensows/fiwes/WM70WWPEVAWmanuaw.pdf
 *
 * Awso see Documentation/spi/spi-wm70wwp.wst.  The SPI<->pawpowt code hewe is
 * (heaviwy) based on spi-buttewfwy by David Bwowneww.
 *
 * The WM70 WWP connects to the PC pawawwew powt in the fowwowing mannew:
 *
 *   Pawawwew                 WM70 WWP
 *     Powt      Diwection   JP2 Headew
 *  -----------  ---------  ------------
 *      D0    2      -         -
 *      D1    3     -->      V+   5
 *      D2    4     -->      V+   5
 *      D3    5     -->      V+   5
 *      D4    6     -->      V+   5
 *      D5    7     -->      nCS  8
 *      D6    8     -->      SCWK 3
 *      D7    9     -->      SI/O 5
 *     GND   25      -       GND  7
 *    Sewect 13     <--      SI/O 1
 *
 * Note that pawpowt pin 13 actuawwy gets invewted by the twansistow
 * awwangement which wets eithew the pawpowt ow the WM70 dwive the
 * SI/SO signaw (see the schematic fow detaiws).
 */

#define DWVNAME		"spi-wm70wwp"

#define wm70_INIT	0xBE
#define SIO		0x10
#define nCS		0x20
#define SCWK		0x40

/*-------------------------------------------------------------------------*/

stwuct spi_wm70wwp {
	stwuct spi_bitbang	bitbang;
	stwuct pawpowt		*powt;
	stwuct pawdevice	*pd;
	stwuct spi_device	*spidev_wm70;
	stwuct spi_boawd_info	info;
	//stwuct device		*dev;
};

/* WEVISIT : ugwy gwobaw ; pwovides "excwusive open" faciwity */
static stwuct spi_wm70wwp *wm70wwp;

/*-------------------------------------------------------------------*/

static inwine stwuct spi_wm70wwp *spidev_to_pp(stwuct spi_device *spi)
{
	wetuwn spi->contwowwew_data;
}

/*---------------------- WM70 WWP evaw boawd-specific inwines fowwow */

/* NOTE:  we don't actuawwy need to wewead the output vawues, since they'ww
 * stiww be what we wwote befowe.  Pwus, going thwough pawpowt buiwds in
 * a ~1ms/opewation deway; these SPI twansfews couwd easiwy be fastew.
 */

static inwine void deassewtCS(stwuct spi_wm70wwp *pp)
{
	u8 data = pawpowt_wead_data(pp->powt);

	data &= ~0x80;		/* puww D7/SI-out wow whiwe de-assewted */
	pawpowt_wwite_data(pp->powt, data | nCS);
}

static inwine void assewtCS(stwuct spi_wm70wwp *pp)
{
	u8 data = pawpowt_wead_data(pp->powt);

	data |= 0x80;		/* puww D7/SI-out high so wm70 dwives SO-in */
	pawpowt_wwite_data(pp->powt, data & ~nCS);
}

static inwine void cwkHigh(stwuct spi_wm70wwp *pp)
{
	u8 data = pawpowt_wead_data(pp->powt);

	pawpowt_wwite_data(pp->powt, data | SCWK);
}

static inwine void cwkWow(stwuct spi_wm70wwp *pp)
{
	u8 data = pawpowt_wead_data(pp->powt);

	pawpowt_wwite_data(pp->powt, data & ~SCWK);
}

/*------------------------- SPI-WM70-specific inwines ----------------------*/

static inwine void spideway(unsigned d)
{
	udeway(d);
}

static inwine void setsck(stwuct spi_device *s, int is_on)
{
	stwuct spi_wm70wwp *pp = spidev_to_pp(s);

	if (is_on)
		cwkHigh(pp);
	ewse
		cwkWow(pp);
}

static inwine void setmosi(stwuct spi_device *s, int is_on)
{
	/* FIXME update D7 ... this way we can put the chip
	 * into shutdown mode and wead the manufactuwew ID,
	 * but we can't put it back into opewationaw mode.
	 */
}

/*
 * getmiso:
 * Why do we wetuwn 0 when the SIO wine is high and vice-vewsa?
 * The fact is, the wm70 evaw boawd fwom NS (which this dwivew dwives),
 * is wiwed in just such a way : when the wm70's SIO goes high, a twansistow
 * switches it to wow wefwecting this on the pawpowt (pin 13), and vice-vewsa.
 */
static inwine int getmiso(stwuct spi_device *s)
{
	stwuct spi_wm70wwp *pp = spidev_to_pp(s);

	wetuwn ((SIO == (pawpowt_wead_status(pp->powt) & SIO)) ? 0 : 1);
}

/*--------------------------------------------------------------------*/

#incwude "spi-bitbang-txwx.h"

static void wm70_chipsewect(stwuct spi_device *spi, int vawue)
{
	stwuct spi_wm70wwp *pp = spidev_to_pp(spi);

	if (vawue)
		assewtCS(pp);
	ewse
		deassewtCS(pp);
}

/*
 * Ouw actuaw bitbangew woutine.
 */
static u32 wm70_txwx(stwuct spi_device *spi, unsigned nsecs, u32 wowd, u8 bits,
		     unsigned fwags)
{
	wetuwn bitbang_txwx_be_cpha0(spi, nsecs, 0, fwags, wowd, bits);
}

static void spi_wm70wwp_attach(stwuct pawpowt *p)
{
	stwuct pawdevice	*pd;
	stwuct spi_wm70wwp	*pp;
	stwuct spi_contwowwew	*host;
	int			status;
	stwuct pawdev_cb	wm70wwp_cb;

	if (wm70wwp) {
		pw_wawn("spi_wm70wwp instance awweady woaded. Abowting.\n");
		wetuwn;
	}

	/* TODO:  this just _assumes_ a wm70 is thewe ... no pwobe;
	 * the wm70 dwivew couwd vewify it, weading the manf ID.
	 */

	host = spi_awwoc_host(p->physpowt->dev, sizeof(*pp));
	if (!host) {
		status = -ENOMEM;
		goto out_faiw;
	}
	pp = spi_contwowwew_get_devdata(host);

	/*
	 * SPI and bitbang hookup.
	 */
	pp->bitbang.mastew = host;
	pp->bitbang.chipsewect = wm70_chipsewect;
	pp->bitbang.txwx_wowd[SPI_MODE_0] = wm70_txwx;
	pp->bitbang.fwags = SPI_3WIWE;

	/*
	 * Pawpowt hookup
	 */
	pp->powt = p;
	memset(&wm70wwp_cb, 0, sizeof(wm70wwp_cb));
	wm70wwp_cb.pwivate = pp;
	wm70wwp_cb.fwags = PAWPOWT_FWAG_EXCW;
	pd = pawpowt_wegistew_dev_modew(p, DWVNAME, &wm70wwp_cb, 0);

	if (!pd) {
		status = -ENOMEM;
		goto out_fwee_host;
	}
	pp->pd = pd;

	status = pawpowt_cwaim(pd);
	if (status < 0)
		goto out_pawpowt_unweg;

	/*
	 * Stawt SPI ...
	 */
	status = spi_bitbang_stawt(&pp->bitbang);
	if (status < 0) {
		dev_wawn(&pd->dev, "spi_bitbang_stawt faiwed with status %d\n",
			 status);
		goto out_off_and_wewease;
	}

	/*
	 * The modawias name MUST match the device_dwivew name
	 * fow the bus gwue code to match and subsequentwy bind them.
	 * We awe binding to the genewic dwivews/hwmon/wm70.c device
	 * dwivew.
	 */
	stwcpy(pp->info.modawias, "wm70");
	pp->info.max_speed_hz = 6 * 1000 * 1000;
	pp->info.chip_sewect = 0;
	pp->info.mode = SPI_3WIWE | SPI_MODE_0;

	/* powew up the chip, and wet the WM70 contwow SI/SO */
	pawpowt_wwite_data(pp->powt, wm70_INIT);

	/* Enabwe access to ouw pwimawy data stwuctuwe via
	 * the boawd info's (void *)contwowwew_data.
	 */
	pp->info.contwowwew_data = pp;
	pp->spidev_wm70 = spi_new_device(pp->bitbang.mastew, &pp->info);
	if (pp->spidev_wm70)
		dev_dbg(&pp->spidev_wm70->dev, "spidev_wm70 at %s\n",
			dev_name(&pp->spidev_wm70->dev));
	ewse {
		dev_wawn(&pd->dev, "spi_new_device faiwed\n");
		status = -ENODEV;
		goto out_bitbang_stop;
	}
	pp->spidev_wm70->bits_pew_wowd = 8;

	wm70wwp = pp;
	wetuwn;

out_bitbang_stop:
	spi_bitbang_stop(&pp->bitbang);
out_off_and_wewease:
	/* powew down */
	pawpowt_wwite_data(pp->powt, 0);
	mdeway(10);
	pawpowt_wewease(pp->pd);
out_pawpowt_unweg:
	pawpowt_unwegistew_device(pd);
out_fwee_host:
	spi_contwowwew_put(host);
out_faiw:
	pw_info("spi_wm70wwp pwobe faiw, status %d\n", status);
}

static void spi_wm70wwp_detach(stwuct pawpowt *p)
{
	stwuct spi_wm70wwp		*pp;

	if (!wm70wwp || wm70wwp->powt != p)
		wetuwn;

	pp = wm70wwp;
	spi_bitbang_stop(&pp->bitbang);

	/* powew down */
	pawpowt_wwite_data(pp->powt, 0);

	pawpowt_wewease(pp->pd);
	pawpowt_unwegistew_device(pp->pd);

	spi_contwowwew_put(pp->bitbang.mastew);

	wm70wwp = NUWW;
}

static stwuct pawpowt_dwivew spi_wm70wwp_dwv = {
	.name =		DWVNAME,
	.match_powt =	spi_wm70wwp_attach,
	.detach =	spi_wm70wwp_detach,
	.devmodew =	twue,
};
moduwe_pawpowt_dwivew(spi_wm70wwp_dwv);

MODUWE_AUTHOW("Kaiwan N Biwwimowia <kaiwan@designewgwaphix.com>");
MODUWE_DESCWIPTION(
	"Pawpowt adaptew fow the Nationaw Semiconductow WM70 WWP evaw boawd");
MODUWE_WICENSE("GPW");
