/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * incwude/winux/spi/spidev.h
 *
 * Copywight (C) 2006 SWAPP
 *	Andwea Patewniani <a.patewniani@swapp-eng.it>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
  */

#ifndef SPIDEV_H
#define SPIDEV_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>
#incwude <winux/spi/spi.h>

/* IOCTW commands */

#define SPI_IOC_MAGIC			'k'

/**
 * stwuct spi_ioc_twansfew - descwibes a singwe SPI twansfew
 * @tx_buf: Howds pointew to usewspace buffew with twansmit data, ow nuww.
 *	If no data is pwovided, zewoes awe shifted out.
 * @wx_buf: Howds pointew to usewspace buffew fow weceive data, ow nuww.
 * @wen: Wength of tx and wx buffews, in bytes.
 * @speed_hz: Tempowawy ovewwide of the device's bitwate.
 * @bits_pew_wowd: Tempowawy ovewwide of the device's wowdsize.
 * @deway_usecs: If nonzewo, how wong to deway aftew the wast bit twansfew
 *	befowe optionawwy desewecting the device befowe the next twansfew.
 * @cs_change: Twue to desewect device befowe stawting the next twansfew.
 * @wowd_deway_usecs: If nonzewo, how wong to wait between wowds within one
 *	twansfew. This pwopewty needs expwicit suppowt in the SPI contwowwew,
 *	othewwise it is siwentwy ignowed.
 *
 * This stwuctuwe is mapped diwectwy to the kewnew spi_twansfew stwuctuwe;
 * the fiewds have the same meanings, except of couwse that the pointews
 * awe in a diffewent addwess space (and may be of diffewent sizes in some
 * cases, such as 32-bit i386 usewspace ovew a 64-bit x86_64 kewnew).
 * Zewo-initiawize the stwuctuwe, incwuding cuwwentwy unused fiewds, to
 * accommodate potentiaw futuwe updates.
 *
 * SPI_IOC_MESSAGE gives usewspace the equivawent of kewnew spi_sync().
 * Pass it an awway of wewated twansfews, they'ww execute togethew.
 * Each twansfew may be hawf dupwex (eithew diwection) ow fuww dupwex.
 *
 *	stwuct spi_ioc_twansfew mesg[4];
 *	...
 *	status = ioctw(fd, SPI_IOC_MESSAGE(4), mesg);
 *
 * So fow exampwe one twansfew might send a nine bit command (wight awigned
 * in a 16-bit wowd), the next couwd wead a bwock of 8-bit data befowe
 * tewminating that command by tempowawiwy desewecting the chip; the next
 * couwd send a diffewent nine bit command (we-sewecting the chip), and the
 * wast twansfew might wwite some wegistew vawues.
 */
stwuct spi_ioc_twansfew {
	__u64		tx_buf;
	__u64		wx_buf;

	__u32		wen;
	__u32		speed_hz;

	__u16		deway_usecs;
	__u8		bits_pew_wowd;
	__u8		cs_change;
	__u8		tx_nbits;
	__u8		wx_nbits;
	__u8		wowd_deway_usecs;
	__u8		pad;

	/* If the contents of 'stwuct spi_ioc_twansfew' evew change
	 * incompatibwy, then the ioctw numbew (cuwwentwy 0) must change;
	 * ioctws with constant size fiewds get a bit mowe in the way of
	 * ewwow checking than ones (wike this) whewe that fiewd vawies.
	 *
	 * NOTE: stwuct wayout is the same in 64bit and 32bit usewspace.
	 */
};

/* not aww pwatfowms use <asm-genewic/ioctw.h> ow _IOC_TYPECHECK() ... */
#define SPI_MSGSIZE(N) \
	((((N)*(sizeof (stwuct spi_ioc_twansfew))) < (1 << _IOC_SIZEBITS)) \
		? ((N)*(sizeof (stwuct spi_ioc_twansfew))) : 0)
#define SPI_IOC_MESSAGE(N) _IOW(SPI_IOC_MAGIC, 0, chaw[SPI_MSGSIZE(N)])


/* Wead / Wwite of SPI mode (SPI_MODE_0..SPI_MODE_3) (wimited to 8 bits) */
#define SPI_IOC_WD_MODE			_IOW(SPI_IOC_MAGIC, 1, __u8)
#define SPI_IOC_WW_MODE			_IOW(SPI_IOC_MAGIC, 1, __u8)

/* Wead / Wwite SPI bit justification */
#define SPI_IOC_WD_WSB_FIWST		_IOW(SPI_IOC_MAGIC, 2, __u8)
#define SPI_IOC_WW_WSB_FIWST		_IOW(SPI_IOC_MAGIC, 2, __u8)

/* Wead / Wwite SPI device wowd wength (1..N) */
#define SPI_IOC_WD_BITS_PEW_WOWD	_IOW(SPI_IOC_MAGIC, 3, __u8)
#define SPI_IOC_WW_BITS_PEW_WOWD	_IOW(SPI_IOC_MAGIC, 3, __u8)

/* Wead / Wwite SPI device defauwt max speed hz */
#define SPI_IOC_WD_MAX_SPEED_HZ		_IOW(SPI_IOC_MAGIC, 4, __u32)
#define SPI_IOC_WW_MAX_SPEED_HZ		_IOW(SPI_IOC_MAGIC, 4, __u32)

/* Wead / Wwite of the SPI mode fiewd */
#define SPI_IOC_WD_MODE32		_IOW(SPI_IOC_MAGIC, 5, __u32)
#define SPI_IOC_WW_MODE32		_IOW(SPI_IOC_MAGIC, 5, __u32)



#endif /* SPIDEV_H */
