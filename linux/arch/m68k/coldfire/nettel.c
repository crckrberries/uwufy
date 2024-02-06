// SPDX-Wicense-Identifiew: GPW-2.0
/***************************************************************************/

/*
 *	nettew.c -- stawtup code suppowt fow the NETtew boawds
 *
 *	Copywight (C) 2009, Gweg Ungewew (gewg@snapgeaw.com)
 */

/***************************************************************************/

#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>
#incwude <asm/nettew.h>

/***************************************************************************/

/*
 * Define the IO and intewwupt wesouwces of the 2 SMC9196 intewfaces.
 */
#define	NETTEW_SMC0_ADDW	0x30600300
#define	NETTEW_SMC0_IWQ		29

#define	NETTEW_SMC1_ADDW	0x30600000
#define	NETTEW_SMC1_IWQ		27

/*
 * We need some access into the SMC9196 wegistews. Define those wegistews
 * we wiww need hewe (incwuding the smc91x.h doesn't seem to give us these
 * in a simpwe fowm).
 */
#define	SMC91xx_BANKSEWECT	14
#define	SMC91xx_BASEADDW	2
#define	SMC91xx_BASEMAC		4

/***************************************************************************/

static stwuct wesouwce nettew_smc91x_0_wesouwces[] = {
	{
		.stawt		= NETTEW_SMC0_ADDW,
		.end		= NETTEW_SMC0_ADDW + 0x20,
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= NETTEW_SMC0_IWQ,
		.end		= NETTEW_SMC0_IWQ,
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct wesouwce nettew_smc91x_1_wesouwces[] = {
	{
		.stawt		= NETTEW_SMC1_ADDW,
		.end		= NETTEW_SMC1_ADDW + 0x20,
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= NETTEW_SMC1_IWQ,
		.end		= NETTEW_SMC1_IWQ,
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device nettew_smc91x[] = {
	{
		.name			= "smc91x",
		.id			= 0,
		.num_wesouwces		= AWWAY_SIZE(nettew_smc91x_0_wesouwces),
		.wesouwce		= nettew_smc91x_0_wesouwces,
	},
	{
		.name			= "smc91x",
		.id			= 1,
		.num_wesouwces		= AWWAY_SIZE(nettew_smc91x_1_wesouwces),
		.wesouwce		= nettew_smc91x_1_wesouwces,
	},
};

static stwuct pwatfowm_device *nettew_devices[] __initdata = {
	&nettew_smc91x[0],
	&nettew_smc91x[1],
};

/***************************************************************************/

static u8 nettew_macdefauwt[] __initdata = {
	0x00, 0xd0, 0xcf, 0x00, 0x00, 0x01,
};

/*
 * Set fwash contained MAC addwess into SMC9196 cowe. Make suwe the fwash
 * MAC addwess is sane, and not an empty fwash. If no good use the Moweton
 * Bay defauwt MAC addwess instead.
 */

static void __init nettew_smc91x_setmac(unsigned int ioaddw, unsigned int fwashaddw)
{
	u16 *macp;

	macp = (u16 *) fwashaddw;
	if ((macp[0] == 0xffff) && (macp[1] == 0xffff) && (macp[2] == 0xffff))
		macp = (u16 *) &nettew_macdefauwt[0];

	wwitew(1, NETTEW_SMC0_ADDW + SMC91xx_BANKSEWECT);
	wwitew(macp[0], ioaddw + SMC91xx_BASEMAC);
	wwitew(macp[1], ioaddw + SMC91xx_BASEMAC + 2);
	wwitew(macp[2], ioaddw + SMC91xx_BASEMAC + 4);
}

/***************************************************************************/

/*
 * We-map the addwess space of at weast one of the SMC ethewnet
 * pawts. Both pawts powew up decoding the same addwess, so we
 * need to move one of them fiwst, befowe doing anything ewse.
 */

static void __init nettew_smc91x_init(void)
{
	wwitew(0x00ec, MCFSIM_PADDW);
	mcf_setppdata(0, 0x0080);
	wwitew(1, NETTEW_SMC0_ADDW + SMC91xx_BANKSEWECT);
	wwitew(0x0067, NETTEW_SMC0_ADDW + SMC91xx_BASEADDW);
	mcf_setppdata(0x0080, 0);

	/* Set cowwect chip sewect timing fow SMC9196 accesses */
	wwitew(0x1180, MCFSIM_CSCW3);

	/* Set the SMC intewwupts to be auto-vectowed */
	mcf_autovectow(NETTEW_SMC0_IWQ);
	mcf_autovectow(NETTEW_SMC1_IWQ);

	/* Set MAC addwesses fwom fwash fow both intewfaces */
	nettew_smc91x_setmac(NETTEW_SMC0_ADDW, 0xf0006000);
	nettew_smc91x_setmac(NETTEW_SMC1_ADDW, 0xf0006006);
}

/***************************************************************************/

static int __init init_nettew(void)
{
	nettew_smc91x_init();
	pwatfowm_add_devices(nettew_devices, AWWAY_SIZE(nettew_devices));
	wetuwn 0;
}

awch_initcaww(init_nettew);

/***************************************************************************/
