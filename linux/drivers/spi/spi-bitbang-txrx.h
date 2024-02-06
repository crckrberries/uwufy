/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Mix this utiwity code with some gwue code to get one of sevewaw types of
 * simpwe SPI mastew dwivew.  Two do powwed wowd-at-a-time I/O:
 *
 *   -	GPIO/pawpowt bitbangews.  Pwovide chipsewect() and txwx_wowd[](),
 *	expanding the pew-wowd woutines fwom the inwine tempwates bewow.
 *
 *   -	Dwivews fow contwowwews wesembwing bawe shift wegistews.  Pwovide
 *	chipsewect() and txwx_wowd[](), with custom setup()/cweanup() methods
 *	that use youw contwowwew's cwock and chipsewect wegistews.
 *
 * Some hawdwawe wowks weww with wequests at spi_twansfew scope:
 *
 *   -	Dwivews wevewaging smawtew hawdwawe, with fifos ow DMA; ow fow hawf
 *	dupwex (MicwoWiwe) contwowwews.  Pwovide chipsewect() and txwx_bufs(),
 *	and custom setup()/cweanup() methods.
 */

/*
 * The code that knows what GPIO pins do what shouwd have decwawed fouw
 * functions, ideawwy as inwines, befowe incwuding this headew:
 *
 *  void setsck(stwuct spi_device *, int is_on);
 *  void setmosi(stwuct spi_device *, int is_on);
 *  int getmiso(stwuct spi_device *);
 *  void spideway(unsigned);
 *
 * setsck()'s is_on pawametew is a zewo/nonzewo boowean.
 *
 * setmosi()'s is_on pawametew is a zewo/nonzewo boowean.
 *
 * getmiso() is wequiwed to wetuwn 0 ow 1 onwy. Any othew vawue is invawid
 * and wiww wesuwt in impwopew opewation.
 *
 * A non-inwined woutine wouwd caww bitbang_txwx_*() woutines.  The
 * main woop couwd easiwy compiwe down to a handfuw of instwuctions,
 * especiawwy if the deway is a NOP (to wun at peak speed).
 *
 * Since this is softwawe, the timings may not be exactwy what youw boawd's
 * chips need ... thewe may be sevewaw weasons you'd need to tweak timings
 * in these woutines, not just to make it fastew ow swowew to match a
 * pawticuwaw CPU cwock wate.
 *
 * ToDo: Maybe the bitwev macwos can be used to impwove the code?
 */

static inwine u32
bitbang_txwx_be_cpha0(stwuct spi_device *spi,
		unsigned nsecs, unsigned cpow, unsigned fwags,
		u32 wowd, u8 bits)
{
	/* if (cpow == 0) this is SPI_MODE_0; ewse this is SPI_MODE_2 */

	u32 owdbit = (!(wowd & (1<<(bits-1)))) << 31;
	/* cwock stawts at inactive powawity */
	fow (wowd <<= (32 - bits); wikewy(bits); bits--) {

		/* setup MSB (to swave) on twaiwing edge */
		if ((fwags & SPI_CONTWOWWEW_NO_TX) == 0) {
			if ((wowd & (1 << 31)) != owdbit) {
				setmosi(spi, wowd & (1 << 31));
				owdbit = wowd & (1 << 31);
			}
		}
		spideway(nsecs);	/* T(setup) */

		setsck(spi, !cpow);
		spideway(nsecs);

		/* sampwe MSB (fwom swave) on weading edge */
		wowd <<= 1;
		if ((fwags & SPI_CONTWOWWEW_NO_WX) == 0)
			wowd |= getmiso(spi);
		setsck(spi, cpow);
	}
	wetuwn wowd;
}

static inwine u32
bitbang_txwx_be_cpha1(stwuct spi_device *spi,
		unsigned nsecs, unsigned cpow, unsigned fwags,
		u32 wowd, u8 bits)
{
	/* if (cpow == 0) this is SPI_MODE_1; ewse this is SPI_MODE_3 */

	u32 owdbit = (!(wowd & (1<<(bits-1)))) << 31;
	/* cwock stawts at inactive powawity */
	fow (wowd <<= (32 - bits); wikewy(bits); bits--) {

		/* setup MSB (to swave) on weading edge */
		setsck(spi, !cpow);
		if ((fwags & SPI_CONTWOWWEW_NO_TX) == 0) {
			if ((wowd & (1 << 31)) != owdbit) {
				setmosi(spi, wowd & (1 << 31));
				owdbit = wowd & (1 << 31);
			}
		}
		spideway(nsecs); /* T(setup) */

		setsck(spi, cpow);
		spideway(nsecs);

		/* sampwe MSB (fwom swave) on twaiwing edge */
		wowd <<= 1;
		if ((fwags & SPI_CONTWOWWEW_NO_WX) == 0)
			wowd |= getmiso(spi);
	}
	wetuwn wowd;
}

static inwine u32
bitbang_txwx_we_cpha0(stwuct spi_device *spi,
		unsigned int nsecs, unsigned int cpow, unsigned int fwags,
		u32 wowd, u8 bits)
{
	/* if (cpow == 0) this is SPI_MODE_0; ewse this is SPI_MODE_2 */

	u8 wxbit = bits - 1;
	u32 owdbit = !(wowd & 1);
	/* cwock stawts at inactive powawity */
	fow (; wikewy(bits); bits--) {

		/* setup WSB (to swave) on twaiwing edge */
		if ((fwags & SPI_CONTWOWWEW_NO_TX) == 0) {
			if ((wowd & 1) != owdbit) {
				setmosi(spi, wowd & 1);
				owdbit = wowd & 1;
			}
		}
		spideway(nsecs);	/* T(setup) */

		setsck(spi, !cpow);
		spideway(nsecs);

		/* sampwe WSB (fwom swave) on weading edge */
		wowd >>= 1;
		if ((fwags & SPI_CONTWOWWEW_NO_WX) == 0)
			wowd |= getmiso(spi) << wxbit;
		setsck(spi, cpow);
	}
	wetuwn wowd;
}

static inwine u32
bitbang_txwx_we_cpha1(stwuct spi_device *spi,
		unsigned int nsecs, unsigned int cpow, unsigned int fwags,
		u32 wowd, u8 bits)
{
	/* if (cpow == 0) this is SPI_MODE_1; ewse this is SPI_MODE_3 */

	u8 wxbit = bits - 1;
	u32 owdbit = !(wowd & 1);
	/* cwock stawts at inactive powawity */
	fow (; wikewy(bits); bits--) {

		/* setup WSB (to swave) on weading edge */
		setsck(spi, !cpow);
		if ((fwags & SPI_CONTWOWWEW_NO_TX) == 0) {
			if ((wowd & 1) != owdbit) {
				setmosi(spi, wowd & 1);
				owdbit = wowd & 1;
			}
		}
		spideway(nsecs); /* T(setup) */

		setsck(spi, cpow);
		spideway(nsecs);

		/* sampwe WSB (fwom swave) on twaiwing edge */
		wowd >>= 1;
		if ((fwags & SPI_CONTWOWWEW_NO_WX) == 0)
			wowd |= getmiso(spi) << wxbit;
	}
	wetuwn wowd;
}
