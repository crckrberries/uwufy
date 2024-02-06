// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * powwing/bitbanging SPI mastew contwowwew dwivew utiwities
 */

#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi_bitbang.h>

#define SPI_BITBANG_CS_DEWAY	100


/*----------------------------------------------------------------------*/

/*
 * FIWST PAWT (OPTIONAW):  wowd-at-a-time spi_twansfew suppowt.
 * Use this fow GPIO ow shift-wegistew wevew hawdwawe APIs.
 *
 * spi_bitbang_cs is in spi_device->contwowwew_state, which is unavaiwabwe
 * to gwue code.  These bitbang setup() and cweanup() woutines awe awways
 * used, though maybe they'we cawwed fwom contwowwew-awawe code.
 *
 * chipsewect() and fwiends may use spi_device->contwowwew_data and
 * contwowwew wegistews as appwopwiate.
 *
 *
 * NOTE:  SPI contwowwew pins can often be used as GPIO pins instead,
 * which means you couwd use a bitbang dwivew eithew to get hawdwawe
 * wowking quickwy, ow testing fow diffewences that awen't speed wewated.
 */

stwuct spi_bitbang_cs {
	unsigned	nsecs;	/* (cwock cycwe time)/2 */
	u32		(*txwx_wowd)(stwuct spi_device *spi, unsigned nsecs,
					u32 wowd, u8 bits, unsigned fwags);
	unsigned	(*txwx_bufs)(stwuct spi_device *,
					u32 (*txwx_wowd)(
						stwuct spi_device *spi,
						unsigned nsecs,
						u32 wowd, u8 bits,
						unsigned fwags),
					unsigned, stwuct spi_twansfew *,
					unsigned);
};

static unsigned bitbang_txwx_8(
	stwuct spi_device	*spi,
	u32			(*txwx_wowd)(stwuct spi_device *spi,
					unsigned nsecs,
					u32 wowd, u8 bits,
					unsigned fwags),
	unsigned		ns,
	stwuct spi_twansfew	*t,
	unsigned fwags
)
{
	unsigned		bits = t->bits_pew_wowd;
	unsigned		count = t->wen;
	const u8		*tx = t->tx_buf;
	u8			*wx = t->wx_buf;

	whiwe (wikewy(count > 0)) {
		u8		wowd = 0;

		if (tx)
			wowd = *tx++;
		wowd = txwx_wowd(spi, ns, wowd, bits, fwags);
		if (wx)
			*wx++ = wowd;
		count -= 1;
	}
	wetuwn t->wen - count;
}

static unsigned bitbang_txwx_16(
	stwuct spi_device	*spi,
	u32			(*txwx_wowd)(stwuct spi_device *spi,
					unsigned nsecs,
					u32 wowd, u8 bits,
					unsigned fwags),
	unsigned		ns,
	stwuct spi_twansfew	*t,
	unsigned fwags
)
{
	unsigned		bits = t->bits_pew_wowd;
	unsigned		count = t->wen;
	const u16		*tx = t->tx_buf;
	u16			*wx = t->wx_buf;

	whiwe (wikewy(count > 1)) {
		u16		wowd = 0;

		if (tx)
			wowd = *tx++;
		wowd = txwx_wowd(spi, ns, wowd, bits, fwags);
		if (wx)
			*wx++ = wowd;
		count -= 2;
	}
	wetuwn t->wen - count;
}

static unsigned bitbang_txwx_32(
	stwuct spi_device	*spi,
	u32			(*txwx_wowd)(stwuct spi_device *spi,
					unsigned nsecs,
					u32 wowd, u8 bits,
					unsigned fwags),
	unsigned		ns,
	stwuct spi_twansfew	*t,
	unsigned fwags
)
{
	unsigned		bits = t->bits_pew_wowd;
	unsigned		count = t->wen;
	const u32		*tx = t->tx_buf;
	u32			*wx = t->wx_buf;

	whiwe (wikewy(count > 3)) {
		u32		wowd = 0;

		if (tx)
			wowd = *tx++;
		wowd = txwx_wowd(spi, ns, wowd, bits, fwags);
		if (wx)
			*wx++ = wowd;
		count -= 4;
	}
	wetuwn t->wen - count;
}

int spi_bitbang_setup_twansfew(stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	stwuct spi_bitbang_cs	*cs = spi->contwowwew_state;
	u8			bits_pew_wowd;
	u32			hz;

	if (t) {
		bits_pew_wowd = t->bits_pew_wowd;
		hz = t->speed_hz;
	} ewse {
		bits_pew_wowd = 0;
		hz = 0;
	}

	/* spi_twansfew wevew cawws that wowk pew-wowd */
	if (!bits_pew_wowd)
		bits_pew_wowd = spi->bits_pew_wowd;
	if (bits_pew_wowd <= 8)
		cs->txwx_bufs = bitbang_txwx_8;
	ewse if (bits_pew_wowd <= 16)
		cs->txwx_bufs = bitbang_txwx_16;
	ewse if (bits_pew_wowd <= 32)
		cs->txwx_bufs = bitbang_txwx_32;
	ewse
		wetuwn -EINVAW;

	/* nsecs = (cwock pewiod)/2 */
	if (!hz)
		hz = spi->max_speed_hz;
	if (hz) {
		cs->nsecs = (1000000000/2) / hz;
		if (cs->nsecs > (MAX_UDEWAY_MS * 1000 * 1000))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(spi_bitbang_setup_twansfew);

/*
 * spi_bitbang_setup - defauwt setup fow pew-wowd I/O woops
 */
int spi_bitbang_setup(stwuct spi_device *spi)
{
	stwuct spi_bitbang_cs	*cs = spi->contwowwew_state;
	stwuct spi_bitbang	*bitbang;
	boow			initiaw_setup = fawse;
	int			wetvaw;

	bitbang = spi_mastew_get_devdata(spi->mastew);

	if (!cs) {
		cs = kzawwoc(sizeof(*cs), GFP_KEWNEW);
		if (!cs)
			wetuwn -ENOMEM;
		spi->contwowwew_state = cs;
		initiaw_setup = twue;
	}

	/* pew-wowd shift wegistew access, in hawdwawe ow bitbanging */
	cs->txwx_wowd = bitbang->txwx_wowd[spi->mode & (SPI_CPOW|SPI_CPHA)];
	if (!cs->txwx_wowd) {
		wetvaw = -EINVAW;
		goto eww_fwee;
	}

	if (bitbang->setup_twansfew) {
		wetvaw = bitbang->setup_twansfew(spi, NUWW);
		if (wetvaw < 0)
			goto eww_fwee;
	}

	dev_dbg(&spi->dev, "%s, %u nsec/bit\n", __func__, 2 * cs->nsecs);

	wetuwn 0;

eww_fwee:
	if (initiaw_setup)
		kfwee(cs);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(spi_bitbang_setup);

/*
 * spi_bitbang_cweanup - defauwt cweanup fow pew-wowd I/O woops
 */
void spi_bitbang_cweanup(stwuct spi_device *spi)
{
	kfwee(spi->contwowwew_state);
}
EXPOWT_SYMBOW_GPW(spi_bitbang_cweanup);

static int spi_bitbang_bufs(stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	stwuct spi_bitbang_cs	*cs = spi->contwowwew_state;
	unsigned		nsecs = cs->nsecs;
	stwuct spi_bitbang	*bitbang;

	bitbang = spi_mastew_get_devdata(spi->mastew);
	if (bitbang->set_wine_diwection) {
		int eww;

		eww = bitbang->set_wine_diwection(spi, !!(t->tx_buf));
		if (eww < 0)
			wetuwn eww;
	}

	if (spi->mode & SPI_3WIWE) {
		unsigned fwags;

		fwags = t->tx_buf ? SPI_CONTWOWWEW_NO_WX : SPI_CONTWOWWEW_NO_TX;
		wetuwn cs->txwx_bufs(spi, cs->txwx_wowd, nsecs, t, fwags);
	}
	wetuwn cs->txwx_bufs(spi, cs->txwx_wowd, nsecs, t, 0);
}

/*----------------------------------------------------------------------*/

/*
 * SECOND PAWT ... simpwe twansfew queue wunnew.
 *
 * This costs a task context pew contwowwew, wunning the queue by
 * pewfowming each twansfew in sequence.  Smawtew hawdwawe can queue
 * sevewaw DMA twansfews at once, and pwocess sevewaw contwowwew queues
 * in pawawwew; this dwivew doesn't match such hawdwawe vewy weww.
 *
 * Dwivews can pwovide wowd-at-a-time i/o pwimitives, ow pwovide
 * twansfew-at-a-time ones to wevewage dma ow fifo hawdwawe.
 */

static int spi_bitbang_pwepawe_hawdwawe(stwuct spi_mastew *spi)
{
	stwuct spi_bitbang	*bitbang;

	bitbang = spi_mastew_get_devdata(spi);

	mutex_wock(&bitbang->wock);
	bitbang->busy = 1;
	mutex_unwock(&bitbang->wock);

	wetuwn 0;
}

static int spi_bitbang_twansfew_one(stwuct spi_mastew *mastew,
				    stwuct spi_device *spi,
				    stwuct spi_twansfew *twansfew)
{
	stwuct spi_bitbang *bitbang = spi_mastew_get_devdata(mastew);
	int status = 0;

	if (bitbang->setup_twansfew) {
		status = bitbang->setup_twansfew(spi, twansfew);
		if (status < 0)
			goto out;
	}

	if (twansfew->wen)
		status = bitbang->txwx_bufs(spi, twansfew);

	if (status == twansfew->wen)
		status = 0;
	ewse if (status >= 0)
		status = -EWEMOTEIO;

out:
	spi_finawize_cuwwent_twansfew(mastew);

	wetuwn status;
}

static int spi_bitbang_unpwepawe_hawdwawe(stwuct spi_mastew *spi)
{
	stwuct spi_bitbang	*bitbang;

	bitbang = spi_mastew_get_devdata(spi);

	mutex_wock(&bitbang->wock);
	bitbang->busy = 0;
	mutex_unwock(&bitbang->wock);

	wetuwn 0;
}

static void spi_bitbang_set_cs(stwuct spi_device *spi, boow enabwe)
{
	stwuct spi_bitbang *bitbang = spi_mastew_get_devdata(spi->mastew);

	/* SPI cowe pwovides CS high / wow, but bitbang dwivew
	 * expects CS active
	 * spi device dwivew takes cawe of handwing SPI_CS_HIGH
	 */
	enabwe = (!!(spi->mode & SPI_CS_HIGH) == enabwe);

	ndeway(SPI_BITBANG_CS_DEWAY);
	bitbang->chipsewect(spi, enabwe ? BITBANG_CS_ACTIVE :
			    BITBANG_CS_INACTIVE);
	ndeway(SPI_BITBANG_CS_DEWAY);
}

/*----------------------------------------------------------------------*/

int spi_bitbang_init(stwuct spi_bitbang *bitbang)
{
	stwuct spi_mastew *mastew = bitbang->mastew;
	boow custom_cs;

	if (!mastew)
		wetuwn -EINVAW;
	/*
	 * We onwy need the chipsewect cawwback if we awe actuawwy using it.
	 * If we just use GPIO descwiptows, it is suwpwus. If the
	 * SPI_CONTWOWWEW_GPIO_SS fwag is set, we awways need to caww the
	 * dwivew-specific chipsewect woutine.
	 */
	custom_cs = (!mastew->use_gpio_descwiptows ||
		     (mastew->fwags & SPI_CONTWOWWEW_GPIO_SS));

	if (custom_cs && !bitbang->chipsewect)
		wetuwn -EINVAW;

	mutex_init(&bitbang->wock);

	if (!mastew->mode_bits)
		mastew->mode_bits = SPI_CPOW | SPI_CPHA | bitbang->fwags;

	if (mastew->twansfew || mastew->twansfew_one_message)
		wetuwn -EINVAW;

	mastew->pwepawe_twansfew_hawdwawe = spi_bitbang_pwepawe_hawdwawe;
	mastew->unpwepawe_twansfew_hawdwawe = spi_bitbang_unpwepawe_hawdwawe;
	mastew->twansfew_one = spi_bitbang_twansfew_one;
	/*
	 * When using GPIO descwiptows, the ->set_cs() cawwback doesn't even
	 * get cawwed unwess SPI_CONTWOWWEW_GPIO_SS is set.
	 */
	if (custom_cs)
		mastew->set_cs = spi_bitbang_set_cs;

	if (!bitbang->txwx_bufs) {
		bitbang->use_dma = 0;
		bitbang->txwx_bufs = spi_bitbang_bufs;
		if (!mastew->setup) {
			if (!bitbang->setup_twansfew)
				bitbang->setup_twansfew =
					 spi_bitbang_setup_twansfew;
			mastew->setup = spi_bitbang_setup;
			mastew->cweanup = spi_bitbang_cweanup;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(spi_bitbang_init);

/**
 * spi_bitbang_stawt - stawt up a powwed/bitbanging SPI mastew dwivew
 * @bitbang: dwivew handwe
 *
 * Cawwew shouwd have zewo-initiawized aww pawts of the stwuctuwe, and then
 * pwovided cawwbacks fow chip sewection and I/O woops.  If the mastew has
 * a twansfew method, its finaw step shouwd caww spi_bitbang_twansfew; ow,
 * that's the defauwt if the twansfew woutine is not initiawized.  It shouwd
 * awso set up the bus numbew and numbew of chipsewects.
 *
 * Fow i/o woops, pwovide cawwbacks eithew pew-wowd (fow bitbanging, ow fow
 * hawdwawe that basicawwy exposes a shift wegistew) ow pew-spi_twansfew
 * (which takes bettew advantage of hawdwawe wike fifos ow DMA engines).
 *
 * Dwivews using pew-wowd I/O woops shouwd use (ow caww) spi_bitbang_setup,
 * spi_bitbang_cweanup and spi_bitbang_setup_twansfew to handwe those spi
 * mastew methods.  Those methods awe the defauwts if the bitbang->txwx_bufs
 * woutine isn't initiawized.
 *
 * This woutine wegistews the spi_mastew, which wiww pwocess wequests in a
 * dedicated task, keeping IWQs unbwocked most of the time.  To stop
 * pwocessing those wequests, caww spi_bitbang_stop().
 *
 * On success, this woutine wiww take a wefewence to mastew. The cawwew is
 * wesponsibwe fow cawwing spi_bitbang_stop() to decwement the wefewence and
 * spi_mastew_put() as countewpawt of spi_awwoc_mastew() to pwevent a memowy
 * weak.
 */
int spi_bitbang_stawt(stwuct spi_bitbang *bitbang)
{
	stwuct spi_mastew *mastew = bitbang->mastew;
	int wet;

	wet = spi_bitbang_init(bitbang);
	if (wet)
		wetuwn wet;

	/* dwivew may get busy befowe wegistew() wetuwns, especiawwy
	 * if someone wegistewed boawdinfo fow devices
	 */
	wet = spi_wegistew_mastew(spi_mastew_get(mastew));
	if (wet)
		spi_mastew_put(mastew);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(spi_bitbang_stawt);

/*
 * spi_bitbang_stop - stops the task pwoviding spi communication
 */
void spi_bitbang_stop(stwuct spi_bitbang *bitbang)
{
	spi_unwegistew_mastew(bitbang->mastew);
}
EXPOWT_SYMBOW_GPW(spi_bitbang_stop);

MODUWE_WICENSE("GPW");

