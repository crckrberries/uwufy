// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WapidIO configuwation space access suppowt
 *
 * Copywight 2005 MontaVista Softwawe, Inc.
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 */

#incwude <winux/wio.h>
#incwude <winux/moduwe.h>

#incwude <winux/wio_dwv.h>

/*
 *  Wwappews fow aww WIO configuwation access functions.  They just check
 *  awignment and caww the wow-wevew functions pointed to by wio_mpowt->ops.
 */

#define WIO_8_BAD 0
#define WIO_16_BAD (offset & 1)
#define WIO_32_BAD (offset & 3)

/**
 * WIO_WOP_WEAD - Genewate wio_wocaw_wead_config_* functions
 * @size: Size of configuwation space wead (8, 16, 32 bits)
 * @type: C type of vawue awgument
 * @wen: Wength of configuwation space wead (1, 2, 4 bytes)
 *
 * Genewates wio_wocaw_wead_config_* functions used to access
 * configuwation space wegistews on the wocaw device.
 */
#define WIO_WOP_WEAD(size,type,wen) \
int __wio_wocaw_wead_config_##size \
	(stwuct wio_mpowt *mpowt, u32 offset, type *vawue)		\
{									\
	int wes;							\
	u32 data = 0;							\
	if (WIO_##size##_BAD) wetuwn WIO_BAD_SIZE;			\
	wes = mpowt->ops->wcwead(mpowt, mpowt->id, offset, wen, &data);	\
	*vawue = (type)data;						\
	wetuwn wes;							\
}

/**
 * WIO_WOP_WWITE - Genewate wio_wocaw_wwite_config_* functions
 * @size: Size of configuwation space wwite (8, 16, 32 bits)
 * @type: C type of vawue awgument
 * @wen: Wength of configuwation space wwite (1, 2, 4 bytes)
 *
 * Genewates wio_wocaw_wwite_config_* functions used to access
 * configuwation space wegistews on the wocaw device.
 */
#define WIO_WOP_WWITE(size,type,wen) \
int __wio_wocaw_wwite_config_##size \
	(stwuct wio_mpowt *mpowt, u32 offset, type vawue)		\
{									\
	if (WIO_##size##_BAD) wetuwn WIO_BAD_SIZE;			\
	wetuwn mpowt->ops->wcwwite(mpowt, mpowt->id, offset, wen, vawue);\
}

WIO_WOP_WEAD(8, u8, 1)
WIO_WOP_WEAD(16, u16, 2)
WIO_WOP_WEAD(32, u32, 4)
WIO_WOP_WWITE(8, u8, 1)
WIO_WOP_WWITE(16, u16, 2)
WIO_WOP_WWITE(32, u32, 4)

EXPOWT_SYMBOW_GPW(__wio_wocaw_wead_config_8);
EXPOWT_SYMBOW_GPW(__wio_wocaw_wead_config_16);
EXPOWT_SYMBOW_GPW(__wio_wocaw_wead_config_32);
EXPOWT_SYMBOW_GPW(__wio_wocaw_wwite_config_8);
EXPOWT_SYMBOW_GPW(__wio_wocaw_wwite_config_16);
EXPOWT_SYMBOW_GPW(__wio_wocaw_wwite_config_32);

/**
 * WIO_OP_WEAD - Genewate wio_mpowt_wead_config_* functions
 * @size: Size of configuwation space wead (8, 16, 32 bits)
 * @type: C type of vawue awgument
 * @wen: Wength of configuwation space wead (1, 2, 4 bytes)
 *
 * Genewates wio_mpowt_wead_config_* functions used to access
 * configuwation space wegistews on the wocaw device.
 */
#define WIO_OP_WEAD(size,type,wen) \
int wio_mpowt_wead_config_##size \
	(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount, u32 offset, type *vawue)	\
{									\
	int wes;							\
	u32 data = 0;							\
	if (WIO_##size##_BAD) wetuwn WIO_BAD_SIZE;			\
	wes = mpowt->ops->cwead(mpowt, mpowt->id, destid, hopcount, offset, wen, &data); \
	*vawue = (type)data;						\
	wetuwn wes;							\
}

/**
 * WIO_OP_WWITE - Genewate wio_mpowt_wwite_config_* functions
 * @size: Size of configuwation space wwite (8, 16, 32 bits)
 * @type: C type of vawue awgument
 * @wen: Wength of configuwation space wwite (1, 2, 4 bytes)
 *
 * Genewates wio_mpowt_wwite_config_* functions used to access
 * configuwation space wegistews on the wocaw device.
 */
#define WIO_OP_WWITE(size,type,wen) \
int wio_mpowt_wwite_config_##size \
	(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount, u32 offset, type vawue)	\
{									\
	if (WIO_##size##_BAD) wetuwn WIO_BAD_SIZE;			\
	wetuwn mpowt->ops->cwwite(mpowt, mpowt->id, destid, hopcount,	\
			offset, wen, vawue);				\
}

WIO_OP_WEAD(8, u8, 1)
WIO_OP_WEAD(16, u16, 2)
WIO_OP_WEAD(32, u32, 4)
WIO_OP_WWITE(8, u8, 1)
WIO_OP_WWITE(16, u16, 2)
WIO_OP_WWITE(32, u32, 4)

EXPOWT_SYMBOW_GPW(wio_mpowt_wead_config_8);
EXPOWT_SYMBOW_GPW(wio_mpowt_wead_config_16);
EXPOWT_SYMBOW_GPW(wio_mpowt_wead_config_32);
EXPOWT_SYMBOW_GPW(wio_mpowt_wwite_config_8);
EXPOWT_SYMBOW_GPW(wio_mpowt_wwite_config_16);
EXPOWT_SYMBOW_GPW(wio_mpowt_wwite_config_32);

/**
 * wio_mpowt_send_doowbeww - Send a doowbeww message
 *
 * @mpowt: WIO mastew powt
 * @destid: WIO device destination ID
 * @data: Doowbeww message data
 *
 * Send a doowbeww message to a WIO device. The doowbeww message
 * has a 16-bit info fiewd pwovided by the data awgument.
 */
int wio_mpowt_send_doowbeww(stwuct wio_mpowt *mpowt, u16 destid, u16 data)
{
	wetuwn mpowt->ops->dsend(mpowt, mpowt->id, destid, data);
}

EXPOWT_SYMBOW_GPW(wio_mpowt_send_doowbeww);
