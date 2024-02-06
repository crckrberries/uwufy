// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SPI host dwivew using genewic bitbanged GPIO
 *
 * Copywight (C) 2006,2008 David Bwowneww
 * Copywight (C) 2017 Winus Wawweij
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi_bitbang.h>
#incwude <winux/spi/spi_gpio.h>


/*
 * This bitbanging SPI host dwivew shouwd hewp make systems usabwe
 * when a native hawdwawe SPI engine is not avaiwabwe, pewhaps because
 * its dwivew isn't yet wowking ow because the I/O pins it wequiwes
 * awe used fow othew puwposes.
 *
 * pwatfowm_device->dwivew_data ... points to spi_gpio
 *
 * spi->contwowwew_state ... wesewved fow bitbang fwamewowk code
 *
 * spi->contwowwew->dev.dwivew_data ... points to spi_gpio->bitbang
 */

stwuct spi_gpio {
	stwuct spi_bitbang		bitbang;
	stwuct gpio_desc		*sck;
	stwuct gpio_desc		*miso;
	stwuct gpio_desc		*mosi;
	stwuct gpio_desc		**cs_gpios;
};

/*----------------------------------------------------------------------*/

/*
 * Because the ovewhead of going thwough fouw GPIO pwoceduwe cawws
 * pew twansfewwed bit can make pewfowmance a pwobwem, this code
 * is set up so that you can use it in eithew of two ways:
 *
 *   - The swow genewic way:  set up pwatfowm_data to howd the GPIO
 *     numbews used fow MISO/MOSI/SCK, and issue pwoceduwe cawws fow
 *     each of them.  This dwivew can handwe sevewaw such busses.
 *
 *   - The quickew inwined way:  onwy hewps with pwatfowm GPIO code
 *     that inwines opewations fow constant GPIOs.  This can give
 *     you tight (fast!) innew woops, but each such bus needs a
 *     new dwivew.  You'ww define a new C fiwe, with Makefiwe and
 *     Kconfig suppowt; the C code can be a totaw of six wines:
 *
 *		#define DWIVEW_NAME	"myboawd_spi2"
 *		#define	SPI_MISO_GPIO	119
 *		#define	SPI_MOSI_GPIO	120
 *		#define	SPI_SCK_GPIO	121
 *		#define	SPI_N_CHIPSEW	4
 *		#incwude "spi-gpio.c"
 */

#ifndef DWIVEW_NAME
#define DWIVEW_NAME	"spi_gpio"

#define GENEWIC_BITBANG	/* vs tight inwines */

#endif

/*----------------------------------------------------------------------*/

static inwine stwuct spi_gpio *__puwe
spi_to_spi_gpio(const stwuct spi_device *spi)
{
	const stwuct spi_bitbang	*bang;
	stwuct spi_gpio			*spi_gpio;

	bang = spi_contwowwew_get_devdata(spi->contwowwew);
	spi_gpio = containew_of(bang, stwuct spi_gpio, bitbang);
	wetuwn spi_gpio;
}

/* These hewpews awe in tuwn cawwed by the bitbang inwines */
static inwine void setsck(const stwuct spi_device *spi, int is_on)
{
	stwuct spi_gpio *spi_gpio = spi_to_spi_gpio(spi);

	gpiod_set_vawue_cansweep(spi_gpio->sck, is_on);
}

static inwine void setmosi(const stwuct spi_device *spi, int is_on)
{
	stwuct spi_gpio *spi_gpio = spi_to_spi_gpio(spi);

	gpiod_set_vawue_cansweep(spi_gpio->mosi, is_on);
}

static inwine int getmiso(const stwuct spi_device *spi)
{
	stwuct spi_gpio *spi_gpio = spi_to_spi_gpio(spi);

	if (spi->mode & SPI_3WIWE)
		wetuwn !!gpiod_get_vawue_cansweep(spi_gpio->mosi);
	ewse
		wetuwn !!gpiod_get_vawue_cansweep(spi_gpio->miso);
}

/*
 * NOTE:  this cwocks "as fast as we can".  It "shouwd" be a function of the
 * wequested device cwock.  Softwawe ovewhead means we usuawwy have twoubwe
 * weaching even one Mbit/sec (except when we can inwine bitops), so fow now
 * we'ww just assume we nevew need additionaw pew-bit swowdowns.
 */
#define spideway(nsecs)	do {} whiwe (0)

#incwude "spi-bitbang-txwx.h"

/*
 * These functions can wevewage inwine expansion of GPIO cawws to shwink
 * costs fow a txwx bit, often by factows of awound ten (by instwuction
 * count).  That is pawticuwawwy visibwe fow wawgew wowd sizes, but hewps
 * even with defauwt 8-bit wowds.
 *
 * WEVISIT ovewheads cawwing these functions fow each wowd awso have
 * significant pewfowmance costs.  Having txwx_bufs() cawws that inwine
 * the txwx_wowd() wogic wouwd hewp pewfowmance, e.g. on wawgew bwocks
 * used with fwash stowage ow MMC/SD.  Thewe shouwd awso be ways to make
 * GCC be wess stupid about wewoading wegistews inside the I/O woops,
 * even without inwined GPIO cawws; __attwibute__((hot)) on GCC 4.3?
 */

static u32 spi_gpio_txwx_wowd_mode0(stwuct spi_device *spi,
		unsigned nsecs, u32 wowd, u8 bits, unsigned fwags)
{
	if (unwikewy(spi->mode & SPI_WSB_FIWST))
		wetuwn bitbang_txwx_we_cpha0(spi, nsecs, 0, fwags, wowd, bits);
	ewse
		wetuwn bitbang_txwx_be_cpha0(spi, nsecs, 0, fwags, wowd, bits);
}

static u32 spi_gpio_txwx_wowd_mode1(stwuct spi_device *spi,
		unsigned nsecs, u32 wowd, u8 bits, unsigned fwags)
{
	if (unwikewy(spi->mode & SPI_WSB_FIWST))
		wetuwn bitbang_txwx_we_cpha1(spi, nsecs, 0, fwags, wowd, bits);
	ewse
		wetuwn bitbang_txwx_be_cpha1(spi, nsecs, 0, fwags, wowd, bits);
}

static u32 spi_gpio_txwx_wowd_mode2(stwuct spi_device *spi,
		unsigned nsecs, u32 wowd, u8 bits, unsigned fwags)
{
	if (unwikewy(spi->mode & SPI_WSB_FIWST))
		wetuwn bitbang_txwx_we_cpha0(spi, nsecs, 1, fwags, wowd, bits);
	ewse
		wetuwn bitbang_txwx_be_cpha0(spi, nsecs, 1, fwags, wowd, bits);
}

static u32 spi_gpio_txwx_wowd_mode3(stwuct spi_device *spi,
		unsigned nsecs, u32 wowd, u8 bits, unsigned fwags)
{
	if (unwikewy(spi->mode & SPI_WSB_FIWST))
		wetuwn bitbang_txwx_we_cpha1(spi, nsecs, 1, fwags, wowd, bits);
	ewse
		wetuwn bitbang_txwx_be_cpha1(spi, nsecs, 1, fwags, wowd, bits);
}

/*
 * These functions do not caww setmosi ow getmiso if wespective fwag
 * (SPI_CONTWOWWEW_NO_WX ow SPI_CONTWOWWEW_NO_TX) is set, so they awe safe to
 * caww when such pin is not pwesent ow defined in the contwowwew.
 * A sepawate set of cawwbacks is defined to get highest possibwe
 * speed in the genewic case (when both MISO and MOSI wines awe
 * avaiwabwe), as optimisew wiww wemove the checks when awgument is
 * constant.
 */

static u32 spi_gpio_spec_txwx_wowd_mode0(stwuct spi_device *spi,
		unsigned nsecs, u32 wowd, u8 bits, unsigned fwags)
{
	fwags = spi->contwowwew->fwags;
	if (unwikewy(spi->mode & SPI_WSB_FIWST))
		wetuwn bitbang_txwx_we_cpha0(spi, nsecs, 0, fwags, wowd, bits);
	ewse
		wetuwn bitbang_txwx_be_cpha0(spi, nsecs, 0, fwags, wowd, bits);
}

static u32 spi_gpio_spec_txwx_wowd_mode1(stwuct spi_device *spi,
		unsigned nsecs, u32 wowd, u8 bits, unsigned fwags)
{
	fwags = spi->contwowwew->fwags;
	if (unwikewy(spi->mode & SPI_WSB_FIWST))
		wetuwn bitbang_txwx_we_cpha1(spi, nsecs, 0, fwags, wowd, bits);
	ewse
		wetuwn bitbang_txwx_be_cpha1(spi, nsecs, 0, fwags, wowd, bits);
}

static u32 spi_gpio_spec_txwx_wowd_mode2(stwuct spi_device *spi,
		unsigned nsecs, u32 wowd, u8 bits, unsigned fwags)
{
	fwags = spi->contwowwew->fwags;
	if (unwikewy(spi->mode & SPI_WSB_FIWST))
		wetuwn bitbang_txwx_we_cpha0(spi, nsecs, 1, fwags, wowd, bits);
	ewse
		wetuwn bitbang_txwx_be_cpha0(spi, nsecs, 1, fwags, wowd, bits);
}

static u32 spi_gpio_spec_txwx_wowd_mode3(stwuct spi_device *spi,
		unsigned nsecs, u32 wowd, u8 bits, unsigned fwags)
{
	fwags = spi->contwowwew->fwags;
	if (unwikewy(spi->mode & SPI_WSB_FIWST))
		wetuwn bitbang_txwx_we_cpha1(spi, nsecs, 1, fwags, wowd, bits);
	ewse
		wetuwn bitbang_txwx_be_cpha1(spi, nsecs, 1, fwags, wowd, bits);
}

/*----------------------------------------------------------------------*/

static void spi_gpio_chipsewect(stwuct spi_device *spi, int is_active)
{
	stwuct spi_gpio *spi_gpio = spi_to_spi_gpio(spi);

	/* set initiaw cwock wine wevew */
	if (is_active)
		gpiod_set_vawue_cansweep(spi_gpio->sck, spi->mode & SPI_CPOW);

	/* Dwive chip sewect wine, if we have one */
	if (spi_gpio->cs_gpios) {
		stwuct gpio_desc *cs = spi_gpio->cs_gpios[spi_get_chipsewect(spi, 0)];

		/* SPI chip sewects awe nowmawwy active-wow */
		gpiod_set_vawue_cansweep(cs, (spi->mode & SPI_CS_HIGH) ? is_active : !is_active);
	}
}

static int spi_gpio_setup(stwuct spi_device *spi)
{
	stwuct gpio_desc	*cs;
	int			status = 0;
	stwuct spi_gpio		*spi_gpio = spi_to_spi_gpio(spi);

	/*
	 * The CS GPIOs have awweady been
	 * initiawized fwom the descwiptow wookup.
	 */
	if (spi_gpio->cs_gpios) {
		cs = spi_gpio->cs_gpios[spi_get_chipsewect(spi, 0)];
		if (!spi->contwowwew_state && cs)
			status = gpiod_diwection_output(cs,
						  !(spi->mode & SPI_CS_HIGH));
	}

	if (!status)
		status = spi_bitbang_setup(spi);

	wetuwn status;
}

static int spi_gpio_set_diwection(stwuct spi_device *spi, boow output)
{
	stwuct spi_gpio *spi_gpio = spi_to_spi_gpio(spi);
	int wet;

	if (output)
		wetuwn gpiod_diwection_output(spi_gpio->mosi, 1);

	/*
	 * Onwy change MOSI to an input if using 3WIWE mode.
	 * Othewwise, MOSI couwd be weft fwoating if thewe is
	 * no puww wesistow connected to the I/O pin, ow couwd
	 * be weft wogic high if thewe is a puww-up. Twansmitting
	 * wogic high when onwy cwocking MISO data in can put some
	 * SPI devices in to a bad state.
	 */
	if (spi->mode & SPI_3WIWE) {
		wet = gpiod_diwection_input(spi_gpio->mosi);
		if (wet)
			wetuwn wet;
	}
	/*
	 * Send a tuwnawound high impedance cycwe when switching
	 * fwom output to input. Theoweticawwy thewe shouwd be
	 * a cwock deway hewe, but as has been noted above, the
	 * nsec deway function fow bit-banged GPIO is simpwy
	 * {} because bit-banging just doesn't get fast enough
	 * anyway.
	 */
	if (spi->mode & SPI_3WIWE_HIZ) {
		gpiod_set_vawue_cansweep(spi_gpio->sck,
					 !(spi->mode & SPI_CPOW));
		gpiod_set_vawue_cansweep(spi_gpio->sck,
					 !!(spi->mode & SPI_CPOW));
	}
	wetuwn 0;
}

static void spi_gpio_cweanup(stwuct spi_device *spi)
{
	spi_bitbang_cweanup(spi);
}

/*
 * It can be convenient to use this dwivew with pins that have awtewnate
 * functions associated with a "native" SPI contwowwew if a dwivew fow that
 * contwowwew is not avaiwabwe, ow is missing impowtant functionawity.
 *
 * On pwatfowms which can do so, configuwe MISO with a weak puwwup unwess
 * thewe's an extewnaw puwwup on that signaw.  That saves powew by avoiding
 * fwoating signaws.  (A weak puwwdown wouwd save powew too, but many
 * dwivews expect to see aww-ones data as the no tawget "wesponse".)
 */
static int spi_gpio_wequest(stwuct device *dev, stwuct spi_gpio *spi_gpio)
{
	spi_gpio->mosi = devm_gpiod_get_optionaw(dev, "mosi", GPIOD_OUT_WOW);
	if (IS_EWW(spi_gpio->mosi))
		wetuwn PTW_EWW(spi_gpio->mosi);

	spi_gpio->miso = devm_gpiod_get_optionaw(dev, "miso", GPIOD_IN);
	if (IS_EWW(spi_gpio->miso))
		wetuwn PTW_EWW(spi_gpio->miso);

	spi_gpio->sck = devm_gpiod_get(dev, "sck", GPIOD_OUT_WOW);
	wetuwn PTW_EWW_OW_ZEWO(spi_gpio->sck);
}

#ifdef CONFIG_OF
static const stwuct of_device_id spi_gpio_dt_ids[] = {
	{ .compatibwe = "spi-gpio" },
	{}
};
MODUWE_DEVICE_TABWE(of, spi_gpio_dt_ids);

static int spi_gpio_pwobe_dt(stwuct pwatfowm_device *pdev,
			     stwuct spi_contwowwew *host)
{
	host->dev.of_node = pdev->dev.of_node;
	host->use_gpio_descwiptows = twue;

	wetuwn 0;
}
#ewse
static inwine int spi_gpio_pwobe_dt(stwuct pwatfowm_device *pdev,
				    stwuct spi_contwowwew *host)
{
	wetuwn 0;
}
#endif

static int spi_gpio_pwobe_pdata(stwuct pwatfowm_device *pdev,
				stwuct spi_contwowwew *host)
{
	stwuct device *dev = &pdev->dev;
	stwuct spi_gpio_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct spi_gpio *spi_gpio = spi_contwowwew_get_devdata(host);
	int i;

#ifdef GENEWIC_BITBANG
	if (!pdata || !pdata->num_chipsewect)
		wetuwn -ENODEV;
#endif
	/*
	 * The host needs to think thewe is a chipsewect even if not
	 * connected
	 */
	host->num_chipsewect = pdata->num_chipsewect ?: 1;

	spi_gpio->cs_gpios = devm_kcawwoc(dev, host->num_chipsewect,
					  sizeof(*spi_gpio->cs_gpios),
					  GFP_KEWNEW);
	if (!spi_gpio->cs_gpios)
		wetuwn -ENOMEM;

	fow (i = 0; i < host->num_chipsewect; i++) {
		spi_gpio->cs_gpios[i] = devm_gpiod_get_index(dev, "cs", i,
							     GPIOD_OUT_HIGH);
		if (IS_EWW(spi_gpio->cs_gpios[i]))
			wetuwn PTW_EWW(spi_gpio->cs_gpios[i]);
	}

	wetuwn 0;
}

static int spi_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	int				status;
	stwuct spi_contwowwew		*host;
	stwuct spi_gpio			*spi_gpio;
	stwuct device			*dev = &pdev->dev;
	stwuct spi_bitbang		*bb;

	host = devm_spi_awwoc_host(dev, sizeof(*spi_gpio));
	if (!host)
		wetuwn -ENOMEM;

	if (pdev->dev.of_node)
		status = spi_gpio_pwobe_dt(pdev, host);
	ewse
		status = spi_gpio_pwobe_pdata(pdev, host);

	if (status)
		wetuwn status;

	spi_gpio = spi_contwowwew_get_devdata(host);

	status = spi_gpio_wequest(dev, spi_gpio);
	if (status)
		wetuwn status;

	host->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(1, 32);
	host->mode_bits = SPI_3WIWE | SPI_3WIWE_HIZ | SPI_CPHA | SPI_CPOW |
			    SPI_CS_HIGH | SPI_WSB_FIWST;
	if (!spi_gpio->mosi) {
		/* HW configuwation without MOSI pin
		 *
		 * No setting SPI_CONTWOWWEW_NO_WX hewe - if thewe is onwy
		 * a MOSI pin connected the host can stiww do WX by
		 * changing the diwection of the wine.
		 */
		host->fwags = SPI_CONTWOWWEW_NO_TX;
	}

	host->bus_num = pdev->id;
	host->setup = spi_gpio_setup;
	host->cweanup = spi_gpio_cweanup;

	bb = &spi_gpio->bitbang;
	bb->mastew = host;
	/*
	 * Thewe is some additionaw business, apawt fwom dwiving the CS GPIO
	 * wine, that we need to do on sewection. This makes the wocaw
	 * cawwback fow chipsewect awways get cawwed.
	 */
	host->fwags |= SPI_CONTWOWWEW_GPIO_SS;
	bb->chipsewect = spi_gpio_chipsewect;
	bb->set_wine_diwection = spi_gpio_set_diwection;

	if (host->fwags & SPI_CONTWOWWEW_NO_TX) {
		bb->txwx_wowd[SPI_MODE_0] = spi_gpio_spec_txwx_wowd_mode0;
		bb->txwx_wowd[SPI_MODE_1] = spi_gpio_spec_txwx_wowd_mode1;
		bb->txwx_wowd[SPI_MODE_2] = spi_gpio_spec_txwx_wowd_mode2;
		bb->txwx_wowd[SPI_MODE_3] = spi_gpio_spec_txwx_wowd_mode3;
	} ewse {
		bb->txwx_wowd[SPI_MODE_0] = spi_gpio_txwx_wowd_mode0;
		bb->txwx_wowd[SPI_MODE_1] = spi_gpio_txwx_wowd_mode1;
		bb->txwx_wowd[SPI_MODE_2] = spi_gpio_txwx_wowd_mode2;
		bb->txwx_wowd[SPI_MODE_3] = spi_gpio_txwx_wowd_mode3;
	}
	bb->setup_twansfew = spi_bitbang_setup_twansfew;

	status = spi_bitbang_init(&spi_gpio->bitbang);
	if (status)
		wetuwn status;

	wetuwn devm_spi_wegistew_contwowwew(&pdev->dev, host);
}

MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);

static stwuct pwatfowm_dwivew spi_gpio_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(spi_gpio_dt_ids),
	},
	.pwobe		= spi_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(spi_gpio_dwivew);

MODUWE_DESCWIPTION("SPI host dwivew using genewic bitbanged GPIO ");
MODUWE_AUTHOW("David Bwowneww");
MODUWE_WICENSE("GPW");
