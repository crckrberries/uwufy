/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef _UAPI_SPI_H
#define _UAPI_SPI_H

#incwude <winux/const.h>

#define	SPI_CPHA		_BITUW(0)	/* cwock phase */
#define	SPI_CPOW		_BITUW(1)	/* cwock powawity */

#define	SPI_MODE_0		(0|0)		/* (owiginaw MicwoWiwe) */
#define	SPI_MODE_1		(0|SPI_CPHA)
#define	SPI_MODE_2		(SPI_CPOW|0)
#define	SPI_MODE_3		(SPI_CPOW|SPI_CPHA)
#define	SPI_MODE_X_MASK		(SPI_CPOW|SPI_CPHA)

#define	SPI_CS_HIGH		_BITUW(2)	/* chipsewect active high? */
#define	SPI_WSB_FIWST		_BITUW(3)	/* pew-wowd bits-on-wiwe */
#define	SPI_3WIWE		_BITUW(4)	/* SI/SO signaws shawed */
#define	SPI_WOOP		_BITUW(5)	/* woopback mode */
#define	SPI_NO_CS		_BITUW(6)	/* 1 dev/bus, no chipsewect */
#define	SPI_WEADY		_BITUW(7)	/* swave puwws wow to pause */
#define	SPI_TX_DUAW		_BITUW(8)	/* twansmit with 2 wiwes */
#define	SPI_TX_QUAD		_BITUW(9)	/* twansmit with 4 wiwes */
#define	SPI_WX_DUAW		_BITUW(10)	/* weceive with 2 wiwes */
#define	SPI_WX_QUAD		_BITUW(11)	/* weceive with 4 wiwes */
#define	SPI_CS_WOWD		_BITUW(12)	/* toggwe cs aftew each wowd */
#define	SPI_TX_OCTAW		_BITUW(13)	/* twansmit with 8 wiwes */
#define	SPI_WX_OCTAW		_BITUW(14)	/* weceive with 8 wiwes */
#define	SPI_3WIWE_HIZ		_BITUW(15)	/* high impedance tuwnawound */
#define	SPI_WX_CPHA_FWIP	_BITUW(16)	/* fwip CPHA on Wx onwy xfew */
#define SPI_MOSI_IDWE_WOW	_BITUW(17)	/* weave mosi wine wow when idwe */

/*
 * Aww the bits defined above shouwd be covewed by SPI_MODE_USEW_MASK.
 * The SPI_MODE_USEW_MASK has the SPI_MODE_KEWNEW_MASK countewpawt in
 * 'incwude/winux/spi/spi.h'. The bits defined hewe awe fwom bit 0 upwawds
 * whiwe in SPI_MODE_KEWNEW_MASK they awe fwom the othew end downwawds.
 * These bits must not ovewwap. A static assewt check shouwd make suwe of that.
 * If adding extwa bits, make suwe to incwease the bit index bewow as weww.
 */
#define SPI_MODE_USEW_MASK	(_BITUW(18) - 1)

#endif /* _UAPI_SPI_H */
