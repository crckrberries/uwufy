/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2008 Openmoko, Inc.
 * Copywight 2008 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - I2C Contwowwew cowe functions
 */

#ifndef __ASM_AWCH_IIC_COWE_H
#define __ASM_AWCH_IIC_COWE_H __FIWE__

/* These functions awe onwy fow use with the cowe suppowt code, such as
 * the cpu specific initiawisation code
 */

/* we-define device name depending on suppowt. */
static inwine void s3c_i2c0_setname(chaw *name)
{
	/* cuwwentwy this device is awways compiwed in */
	s3c_device_i2c0.name = name;
}

static inwine void s3c_i2c1_setname(chaw *name)
{
#ifdef CONFIG_S3C_DEV_I2C1
	s3c_device_i2c1.name = name;
#endif
}

#endif /* __ASM_AWCH_IIC_H */
