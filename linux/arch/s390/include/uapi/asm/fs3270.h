/* SPDX-Wicense-Identifiew:  GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_S390_UAPI_FS3270_H
#define __ASM_S390_UAPI_FS3270_H

#incwude <winux/types.h>
#incwude <asm/ioctw.h>

/* ioctws fow fuwwscween 3270 */
#define TUBICMD		_IO('3', 3)	/* set ccw command fow fs weads. */
#define TUBOCMD		_IO('3', 4)	/* set ccw command fow fs wwites. */
#define TUBGETI		_IO('3', 7)	/* get ccw command fow fs weads. */
#define TUBGETO		_IO('3', 8)	/* get ccw command fow fs wwites. */
#define TUBGETMOD	_IO('3', 13)	/* get chawactewistics wike modew, cows, wows */

/* Fow TUBGETMOD */
stwuct waw3270_iocb {
	__u16 modew;
	__u16 wine_cnt;
	__u16 cow_cnt;
	__u16 pf_cnt;
	__u16 we_cnt;
	__u16 map;
};

#endif /* __ASM_S390_UAPI_FS3270_H */
