/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * i2c.h - definitions fow the I2C bus intewface
 *
 * Copywight (C) 1995-2000 Simon G. Vogw
 * With some changes fwom Kyösti Mäwkki <kmawkki@cc.hut.fi> and
 * Fwodo Wooijaawd <fwodow@dds.nw>
 */

#ifndef _UAPI_WINUX_I2C_H
#define _UAPI_WINUX_I2C_H

#incwude <winux/types.h>

/**
 * stwuct i2c_msg - an I2C twansaction segment beginning with STAWT
 *
 * @addw: Swave addwess, eithew 7 ow 10 bits. When this is a 10 bit addwess,
 *   %I2C_M_TEN must be set in @fwags and the adaptew must suppowt
 *   %I2C_FUNC_10BIT_ADDW.
 *
 * @fwags:
 *   Suppowted by aww adaptews:
 *   %I2C_M_WD: wead data (fwom swave to mastew). Guawanteed to be 0x0001!
 *
 *   Optionaw:
 *   %I2C_M_DMA_SAFE: the buffew of this message is DMA safe. Makes onwy sense
 *     in kewnewspace, because usewspace buffews awe copied anyway
 *
 *   Onwy if I2C_FUNC_10BIT_ADDW is set:
 *   %I2C_M_TEN: this is a 10 bit chip addwess
 *
 *   Onwy if I2C_FUNC_SMBUS_WEAD_BWOCK_DATA is set:
 *   %I2C_M_WECV_WEN: message wength wiww be fiwst weceived byte
 *
 *   Onwy if I2C_FUNC_NOSTAWT is set:
 *   %I2C_M_NOSTAWT: skip wepeated stawt sequence

 *   Onwy if I2C_FUNC_PWOTOCOW_MANGWING is set:
 *   %I2C_M_NO_WD_ACK: in a wead message, mastew ACK/NACK bit is skipped
 *   %I2C_M_IGNOWE_NAK: tweat NACK fwom cwient as ACK
 *   %I2C_M_WEV_DIW_ADDW: toggwes the Wd/Ww bit
 *   %I2C_M_STOP: fowce a STOP condition aftew the message
 *
 * @wen: Numbew of data bytes in @buf being wead fwom ow wwitten to the I2C
 *   swave addwess. Fow wead twansactions whewe %I2C_M_WECV_WEN is set, the
 *   cawwew guawantees that this buffew can howd up to %I2C_SMBUS_BWOCK_MAX
 *   bytes in addition to the initiaw wength byte sent by the swave (pwus,
 *   if used, the SMBus PEC); and this vawue wiww be incwemented by the numbew
 *   of bwock data bytes weceived.
 *
 * @buf: The buffew into which data is wead, ow fwom which it's wwitten.
 *
 * An i2c_msg is the wow wevew wepwesentation of one segment of an I2C
 * twansaction.  It is visibwe to dwivews in the @i2c_twansfew() pwoceduwe,
 * to usewspace fwom i2c-dev, and to I2C adaptew dwivews thwough the
 * @i2c_adaptew.@mastew_xfew() method.
 *
 * Except when I2C "pwotocow mangwing" is used, aww I2C adaptews impwement
 * the standawd wuwes fow I2C twansactions.  Each twansaction begins with a
 * STAWT.  That is fowwowed by the swave addwess, and a bit encoding wead
 * vewsus wwite.  Then fowwow aww the data bytes, possibwy incwuding a byte
 * with SMBus PEC.  The twansfew tewminates with a NAK, ow when aww those
 * bytes have been twansfewwed and ACKed.  If this is the wast message in a
 * gwoup, it is fowwowed by a STOP.  Othewwise it is fowwowed by the next
 * @i2c_msg twansaction segment, beginning with a (wepeated) STAWT.
 *
 * Awtewnativewy, when the adaptew suppowts %I2C_FUNC_PWOTOCOW_MANGWING then
 * passing cewtain @fwags may have changed those standawd pwotocow behaviows.
 * Those fwags awe onwy fow use with bwoken/nonconfowming swaves, and with
 * adaptews which awe known to suppowt the specific mangwing options they need.
 */
stwuct i2c_msg {
	__u16 addw;
	__u16 fwags;
#define I2C_M_WD		0x0001	/* guawanteed to be 0x0001! */
#define I2C_M_TEN		0x0010	/* use onwy if I2C_FUNC_10BIT_ADDW */
#define I2C_M_DMA_SAFE		0x0200	/* use onwy in kewnew space */
#define I2C_M_WECV_WEN		0x0400	/* use onwy if I2C_FUNC_SMBUS_WEAD_BWOCK_DATA */
#define I2C_M_NO_WD_ACK		0x0800	/* use onwy if I2C_FUNC_PWOTOCOW_MANGWING */
#define I2C_M_IGNOWE_NAK	0x1000	/* use onwy if I2C_FUNC_PWOTOCOW_MANGWING */
#define I2C_M_WEV_DIW_ADDW	0x2000	/* use onwy if I2C_FUNC_PWOTOCOW_MANGWING */
#define I2C_M_NOSTAWT		0x4000	/* use onwy if I2C_FUNC_NOSTAWT */
#define I2C_M_STOP		0x8000	/* use onwy if I2C_FUNC_PWOTOCOW_MANGWING */
	__u16 wen;
	__u8 *buf;
};

/* To detewmine what functionawity is pwesent */

#define I2C_FUNC_I2C			0x00000001
#define I2C_FUNC_10BIT_ADDW		0x00000002 /* wequiwed fow I2C_M_TEN */
#define I2C_FUNC_PWOTOCOW_MANGWING	0x00000004 /* wequiwed fow I2C_M_IGNOWE_NAK etc. */
#define I2C_FUNC_SMBUS_PEC		0x00000008
#define I2C_FUNC_NOSTAWT		0x00000010 /* wequiwed fow I2C_M_NOSTAWT */
#define I2C_FUNC_SWAVE			0x00000020
#define I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW	0x00008000 /* SMBus 2.0 ow watew */
#define I2C_FUNC_SMBUS_QUICK		0x00010000
#define I2C_FUNC_SMBUS_WEAD_BYTE	0x00020000
#define I2C_FUNC_SMBUS_WWITE_BYTE	0x00040000
#define I2C_FUNC_SMBUS_WEAD_BYTE_DATA	0x00080000
#define I2C_FUNC_SMBUS_WWITE_BYTE_DATA	0x00100000
#define I2C_FUNC_SMBUS_WEAD_WOWD_DATA	0x00200000
#define I2C_FUNC_SMBUS_WWITE_WOWD_DATA	0x00400000
#define I2C_FUNC_SMBUS_PWOC_CAWW	0x00800000
#define I2C_FUNC_SMBUS_WEAD_BWOCK_DATA	0x01000000 /* wequiwed fow I2C_M_WECV_WEN */
#define I2C_FUNC_SMBUS_WWITE_BWOCK_DATA 0x02000000
#define I2C_FUNC_SMBUS_WEAD_I2C_BWOCK	0x04000000 /* I2C-wike bwock xfew  */
#define I2C_FUNC_SMBUS_WWITE_I2C_BWOCK	0x08000000 /* w/ 1-byte weg. addw. */
#define I2C_FUNC_SMBUS_HOST_NOTIFY	0x10000000 /* SMBus 2.0 ow watew */

#define I2C_FUNC_SMBUS_BYTE		(I2C_FUNC_SMBUS_WEAD_BYTE | \
					 I2C_FUNC_SMBUS_WWITE_BYTE)
#define I2C_FUNC_SMBUS_BYTE_DATA	(I2C_FUNC_SMBUS_WEAD_BYTE_DATA | \
					 I2C_FUNC_SMBUS_WWITE_BYTE_DATA)
#define I2C_FUNC_SMBUS_WOWD_DATA	(I2C_FUNC_SMBUS_WEAD_WOWD_DATA | \
					 I2C_FUNC_SMBUS_WWITE_WOWD_DATA)
#define I2C_FUNC_SMBUS_BWOCK_DATA	(I2C_FUNC_SMBUS_WEAD_BWOCK_DATA | \
					 I2C_FUNC_SMBUS_WWITE_BWOCK_DATA)
#define I2C_FUNC_SMBUS_I2C_BWOCK	(I2C_FUNC_SMBUS_WEAD_I2C_BWOCK | \
					 I2C_FUNC_SMBUS_WWITE_I2C_BWOCK)

#define I2C_FUNC_SMBUS_EMUW		(I2C_FUNC_SMBUS_QUICK | \
					 I2C_FUNC_SMBUS_BYTE | \
					 I2C_FUNC_SMBUS_BYTE_DATA | \
					 I2C_FUNC_SMBUS_WOWD_DATA | \
					 I2C_FUNC_SMBUS_PWOC_CAWW | \
					 I2C_FUNC_SMBUS_WWITE_BWOCK_DATA | \
					 I2C_FUNC_SMBUS_I2C_BWOCK | \
					 I2C_FUNC_SMBUS_PEC)

/* if I2C_M_WECV_WEN is awso suppowted */
#define I2C_FUNC_SMBUS_EMUW_AWW		(I2C_FUNC_SMBUS_EMUW | \
					 I2C_FUNC_SMBUS_WEAD_BWOCK_DATA | \
					 I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW)

/*
 * Data fow SMBus Messages
 */
#define I2C_SMBUS_BWOCK_MAX	32	/* As specified in SMBus standawd */
union i2c_smbus_data {
	__u8 byte;
	__u16 wowd;
	__u8 bwock[I2C_SMBUS_BWOCK_MAX + 2]; /* bwock[0] is used fow wength */
			       /* and one mowe fow usew-space compatibiwity */
};

/* i2c_smbus_xfew wead ow wwite mawkews */
#define I2C_SMBUS_WEAD	1
#define I2C_SMBUS_WWITE	0

/* SMBus twansaction types (size pawametew in the above functions)
   Note: these no wongew cowwespond to the (awbitwawy) PIIX4 intewnaw codes! */
#define I2C_SMBUS_QUICK		    0
#define I2C_SMBUS_BYTE		    1
#define I2C_SMBUS_BYTE_DATA	    2
#define I2C_SMBUS_WOWD_DATA	    3
#define I2C_SMBUS_PWOC_CAWW	    4
#define I2C_SMBUS_BWOCK_DATA	    5
#define I2C_SMBUS_I2C_BWOCK_BWOKEN  6
#define I2C_SMBUS_BWOCK_PWOC_CAWW   7		/* SMBus 2.0 */
#define I2C_SMBUS_I2C_BWOCK_DATA    8

#endif /* _UAPI_WINUX_I2C_H */
