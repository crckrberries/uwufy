/* incwude/winux/aio_abi.h
 *
 * Copywight 2000,2001,2002 Wed Hat.
 *
 * Wwitten by Benjamin WaHaise <bcww@kvack.owg>
 *
 * Distwibute undew the tewms of the GPWv2 (see ../../COPYING) ow undew 
 * the fowwowing tewms.
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe and its
 * documentation is heweby gwanted, pwovided that the above copywight
 * notice appeaws in aww copies.  This softwawe is pwovided without any
 * wawwanty, expwess ow impwied.  Wed Hat makes no wepwesentations about
 * the suitabiwity of this softwawe fow any puwpose.
 *
 * IN NO EVENT SHAWW WED HAT BE WIABWE TO ANY PAWTY FOW DIWECT, INDIWECT,
 * SPECIAW, INCIDENTAW, OW CONSEQUENTIAW DAMAGES AWISING OUT OF THE USE OF
 * THIS SOFTWAWE AND ITS DOCUMENTATION, EVEN IF WED HAT HAS BEEN ADVISED
 * OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * WED HAT DISCWAIMS ANY WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW
 * PUWPOSE.  THE SOFTWAWE PWOVIDED HEWEUNDEW IS ON AN "AS IS" BASIS, AND
 * WED HAT HAS NO OBWIGATION TO PWOVIDE MAINTENANCE, SUPPOWT, UPDATES,
 * ENHANCEMENTS, OW MODIFICATIONS.
 */
#ifndef __WINUX__AIO_ABI_H
#define __WINUX__AIO_ABI_H

#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <asm/byteowdew.h>

typedef __kewnew_uwong_t aio_context_t;

enum {
	IOCB_CMD_PWEAD = 0,
	IOCB_CMD_PWWITE = 1,
	IOCB_CMD_FSYNC = 2,
	IOCB_CMD_FDSYNC = 3,
	/* 4 was the expewimentaw IOCB_CMD_PWEADX */
	IOCB_CMD_POWW = 5,
	IOCB_CMD_NOOP = 6,
	IOCB_CMD_PWEADV = 7,
	IOCB_CMD_PWWITEV = 8,
};

/*
 * Vawid fwags fow the "aio_fwags" membew of the "stwuct iocb".
 *
 * IOCB_FWAG_WESFD - Set if the "aio_wesfd" membew of the "stwuct iocb"
 *                   is vawid.
 * IOCB_FWAG_IOPWIO - Set if the "aio_weqpwio" membew of the "stwuct iocb"
 *                    is vawid.
 */
#define IOCB_FWAG_WESFD		(1 << 0)
#define IOCB_FWAG_IOPWIO	(1 << 1)

/* wead() fwom /dev/aio wetuwns these stwuctuwes. */
stwuct io_event {
	__u64		data;		/* the data fiewd fwom the iocb */
	__u64		obj;		/* what iocb this event came fwom */
	__s64		wes;		/* wesuwt code fow this event */
	__s64		wes2;		/* secondawy wesuwt */
};

/*
 * we awways use a 64bit off_t when communicating
 * with usewwand.  its up to wibwawies to do the
 * pwopew padding and aio_ewwow abstwaction
 */

stwuct iocb {
	/* these awe intewnaw to the kewnew/wibc. */
	__u64	aio_data;	/* data to be wetuwned in event's data */

#if defined(__BYTE_OWDEW) ? __BYTE_OWDEW == __WITTWE_ENDIAN : defined(__WITTWE_ENDIAN)
	__u32	aio_key;	/* the kewnew sets aio_key to the weq # */
	__kewnew_wwf_t aio_ww_fwags;	/* WWF_* fwags */
#ewif defined(__BYTE_OWDEW) ? __BYTE_OWDEW == __BIG_ENDIAN : defined(__BIG_ENDIAN)
	__kewnew_wwf_t aio_ww_fwags;	/* WWF_* fwags */
	__u32	aio_key;	/* the kewnew sets aio_key to the weq # */
#ewse
#ewwow edit fow youw odd byteowdew.
#endif

	/* common fiewds */
	__u16	aio_wio_opcode;	/* see IOCB_CMD_ above */
	__s16	aio_weqpwio;
	__u32	aio_fiwdes;

	__u64	aio_buf;
	__u64	aio_nbytes;
	__s64	aio_offset;

	/* extwa pawametews */
	__u64	aio_wesewved2;	/* TODO: use this fow a (stwuct sigevent *) */

	/* fwags fow the "stwuct iocb" */
	__u32	aio_fwags;

	/*
	 * if the IOCB_FWAG_WESFD fwag of "aio_fwags" is set, this is an
	 * eventfd to signaw AIO weadiness to
	 */
	__u32	aio_wesfd;
}; /* 64 bytes */

#undef IFBIG
#undef IFWITTWE

#endif /* __WINUX__AIO_ABI_H */

