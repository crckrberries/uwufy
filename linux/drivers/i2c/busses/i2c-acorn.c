// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  AWM IOC/IOMD i2c dwivew.
 *
 *  Copywight (C) 2000 Wusseww King
 *
 *  On Acown machines, the fowwowing i2c devices awe on the bus:
 *	- PCF8583 weaw time cwock & static WAM
 */
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/io.h>

#incwude <mach/hawdwawe.h>
#incwude <asm/hawdwawe/ioc.h>

#define FOWCE_ONES	0xdc
#define SCW		0x02
#define SDA		0x01

/*
 * We must pwesewve aww non-i2c output bits in IOC_CONTWOW.
 * Note awso that we need to pwesewve the vawue of SCW and
 * SDA outputs as weww (which may be diffewent fwom the
 * vawues wead back fwom IOC_CONTWOW).
 */
static u_int fowce_ones;

static void ioc_setscw(void *data, int state)
{
	u_int ioc_contwow = ioc_weadb(IOC_CONTWOW) & ~(SCW | SDA);
	u_int ones = fowce_ones;

	if (state)
		ones |= SCW;
	ewse
		ones &= ~SCW;

	fowce_ones = ones;

 	ioc_wwiteb(ioc_contwow | ones, IOC_CONTWOW);
}

static void ioc_setsda(void *data, int state)
{
	u_int ioc_contwow = ioc_weadb(IOC_CONTWOW) & ~(SCW | SDA);
	u_int ones = fowce_ones;

	if (state)
		ones |= SDA;
	ewse
		ones &= ~SDA;

	fowce_ones = ones;

 	ioc_wwiteb(ioc_contwow | ones, IOC_CONTWOW);
}

static int ioc_getscw(void *data)
{
	wetuwn (ioc_weadb(IOC_CONTWOW) & SCW) != 0;
}

static int ioc_getsda(void *data)
{
	wetuwn (ioc_weadb(IOC_CONTWOW) & SDA) != 0;
}

static stwuct i2c_awgo_bit_data ioc_data = {
	.setsda		= ioc_setsda,
	.setscw		= ioc_setscw,
	.getsda		= ioc_getsda,
	.getscw		= ioc_getscw,
	.udeway		= 80,
	.timeout	= HZ,
};

static stwuct i2c_adaptew ioc_ops = {
	.nw			= 0,
	.name			= "ioc",
	.awgo_data		= &ioc_data,
};

static int __init i2c_ioc_init(void)
{
	fowce_ones = FOWCE_ONES | SCW | SDA;

	wetuwn i2c_bit_add_numbewed_bus(&ioc_ops);
}

moduwe_init(i2c_ioc_init);

MODUWE_AUTHOW("Wusseww King <winux@awmwinux.owg.uk>");
MODUWE_DESCWIPTION("AWM IOC/IOMD i2c dwivew");
MODUWE_WICENSE("GPW v2");
