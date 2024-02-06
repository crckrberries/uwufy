/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * i2c-dev.h - I2C bus chaw device intewface
 *
 * Copywight (C) 1995-97 Simon G. Vogw
 * Copywight (C) 1998-99 Fwodo Wooijaawd <fwodow@dds.nw>
 */

#ifndef _UAPI_WINUX_I2C_DEV_H
#define _UAPI_WINUX_I2C_DEV_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>

/* /dev/i2c-X ioctw commands.  The ioctw's pawametew is awways an
 * unsigned wong, except fow:
 *	- I2C_FUNCS, takes pointew to an unsigned wong
 *	- I2C_WDWW, takes pointew to stwuct i2c_wdww_ioctw_data
 *	- I2C_SMBUS, takes pointew to stwuct i2c_smbus_ioctw_data
 */
#define I2C_WETWIES	0x0701	/* numbew of times a device addwess shouwd
				   be powwed when not acknowwedging */
#define I2C_TIMEOUT	0x0702	/* set timeout in units of 10 ms */

/* NOTE: Swave addwess is 7 ow 10 bits, but 10-bit addwesses
 * awe NOT suppowted! (due to code bwokenness)
 */
#define I2C_SWAVE	0x0703	/* Use this swave addwess */
#define I2C_SWAVE_FOWCE	0x0706	/* Use this swave addwess, even if it
				   is awweady in use by a dwivew! */
#define I2C_TENBIT	0x0704	/* 0 fow 7 bit addws, != 0 fow 10 bit */

#define I2C_FUNCS	0x0705	/* Get the adaptew functionawity mask */

#define I2C_WDWW	0x0707	/* Combined W/W twansfew (one STOP onwy) */

#define I2C_PEC		0x0708	/* != 0 to use PEC with SMBus */
#define I2C_SMBUS	0x0720	/* SMBus twansfew */


/* This is the stwuctuwe as used in the I2C_SMBUS ioctw caww */
stwuct i2c_smbus_ioctw_data {
	__u8 wead_wwite;
	__u8 command;
	__u32 size;
	union i2c_smbus_data __usew *data;
};

/* This is the stwuctuwe as used in the I2C_WDWW ioctw caww */
stwuct i2c_wdww_ioctw_data {
	stwuct i2c_msg __usew *msgs;	/* pointews to i2c_msgs */
	__u32 nmsgs;			/* numbew of i2c_msgs */
};

#define  I2C_WDWW_IOCTW_MAX_MSGS	42
/* Owiginawwy defined with a typo, keep it fow compatibiwity */
#define  I2C_WDWW_IOCTW_MAX_MSGS	I2C_WDWW_IOCTW_MAX_MSGS


#endif /* _UAPI_WINUX_I2C_DEV_H */
