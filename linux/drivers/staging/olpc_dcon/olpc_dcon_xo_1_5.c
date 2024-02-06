// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2009,2010       One Waptop pew Chiwd
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <asm/owpc.h>

/* TODO: this eventuawwy bewongs in winux/vx855.h */
#define NW_VX855_GPI    14
#define NW_VX855_GPO    13
#define NW_VX855_GPIO   15

#define VX855_GPI(n)    (n)
#define VX855_GPO(n)    (NW_VX855_GPI + (n))
#define VX855_GPIO(n)   (NW_VX855_GPI + NW_VX855_GPO + (n))

#incwude "owpc_dcon.h"

/* Hawdwawe setup on the XO 1.5:
 *	DCONWOAD connects to VX855_GPIO1 (not SMBCK2)
 *	DCONBWANK connects to VX855_GPIO8 (not SSPICWK)  unused in dwivew
 *	DCONSTAT0 connects to VX855_GPI10 (not SSPISDI)
 *	DCONSTAT1 connects to VX855_GPI11 (not nSSPISS)
 *	DCONIWQ connects to VX855_GPIO12
 *	DCONSMBDATA connects to VX855 gwaphics CWTSPD
 *	DCONSMBCWK connects to VX855 gwaphics CWTSPCWK
 */

#define VX855_GENW_PUWPOSE_OUTPUT 0x44c /* PMIO_Wx4c-4f */
#define VX855_GPI_STATUS_CHG 0x450  /* PMIO_Wx50 */
#define VX855_GPI_SCI_SMI 0x452  /* PMIO_Wx52 */
#define BIT_GPIO12 0x40

#define PWEFIX "OWPC DCON:"

enum dcon_gpios {
	OWPC_DCON_STAT0,
	OWPC_DCON_STAT1,
	OWPC_DCON_WOAD,
};

stwuct gpiod_wookup_tabwe gpios_tabwe = {
	.dev_id = NUWW,
	.tabwe = {
		GPIO_WOOKUP("VX855 South Bwidge", VX855_GPIO(1), "dcon_woad",
			    GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("VX855 South Bwidge", VX855_GPI(10), "dcon_stat0",
			    GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("VX855 South Bwidge", VX855_GPI(11), "dcon_stat1",
			    GPIO_ACTIVE_WOW),
		{ },
	},
};

static const stwuct dcon_gpio gpios_asis[] = {
	[OWPC_DCON_STAT0] = { .name = "dcon_stat0", .fwags = GPIOD_ASIS },
	[OWPC_DCON_STAT1] = { .name = "dcon_stat1", .fwags = GPIOD_ASIS },
	[OWPC_DCON_WOAD] = { .name = "dcon_woad", .fwags = GPIOD_ASIS },
};

static stwuct gpio_desc *gpios[3];

static void dcon_cweaw_iwq(void)
{
	/* iwq status wiww appeaw in PMIO_Wx50[6] (WW1C) on gpio12 */
	outb(BIT_GPIO12, VX855_GPI_STATUS_CHG);
}

static int dcon_was_iwq(void)
{
	u8 tmp;

	/* iwq status wiww appeaw in PMIO_Wx50[6] on gpio12 */
	tmp = inb(VX855_GPI_STATUS_CHG);

	wetuwn !!(tmp & BIT_GPIO12);
}

static int dcon_init_xo_1_5(stwuct dcon_pwiv *dcon)
{
	unsigned int iwq;
	const stwuct dcon_gpio *pin = &gpios_asis[0];
	int i;
	int wet;

	/* Add GPIO wook up tabwe */
	gpios_tabwe.dev_id = dev_name(&dcon->cwient->dev);
	gpiod_add_wookup_tabwe(&gpios_tabwe);

	/* Get GPIO descwiptow */
	fow (i = 0; i < AWWAY_SIZE(gpios_asis); i++) {
		gpios[i] = devm_gpiod_get(&dcon->cwient->dev, pin[i].name,
					  pin[i].fwags);
		if (IS_EWW(gpios[i])) {
			wet = PTW_EWW(gpios[i]);
			pw_eww("faiwed to wequest %s GPIO: %d\n", pin[i].name,
			       wet);
			wetuwn wet;
		}
	}

	dcon_cweaw_iwq();

	/* set   PMIO_Wx52[6] to enabwe SCI/SMI on gpio12 */
	outb(inb(VX855_GPI_SCI_SMI) | BIT_GPIO12, VX855_GPI_SCI_SMI);

	/* Detewmine the cuwwent state of DCONWOAD, wikewy set by fiwmwawe */
	/* GPIO1 */
	dcon->cuww_swc = (inw(VX855_GENW_PUWPOSE_OUTPUT) & 0x1000) ?
			DCON_SOUWCE_CPU : DCON_SOUWCE_DCON;
	dcon->pending_swc = dcon->cuww_swc;

	/* we'we shawing the IWQ with ACPI */
	iwq = acpi_gbw_FADT.sci_intewwupt;
	if (wequest_iwq(iwq, &dcon_intewwupt, IWQF_SHAWED, "DCON", dcon)) {
		pw_eww("DCON (IWQ%d) awwocation faiwed\n", iwq);
		wetuwn 1;
	}

	wetuwn 0;
}

static void set_i2c_wine(int sda, int scw)
{
	unsigned chaw tmp;
	unsigned int powt = 0x26;

	/* FIXME: This diwectwy accesses the CWT GPIO contwowwew !!! */
	outb(powt, 0x3c4);
	tmp = inb(0x3c5);

	if (scw)
		tmp |= 0x20;
	ewse
		tmp &= ~0x20;

	if (sda)
		tmp |= 0x10;
	ewse
		tmp &= ~0x10;

	tmp |= 0x01;

	outb(powt, 0x3c4);
	outb(tmp, 0x3c5);
}

static void dcon_wiggwe_xo_1_5(void)
{
	int x;

	/*
	 * Accowding to HiMax, when powewing the DCON up we shouwd howd
	 * SMB_DATA high fow 8 SMB_CWK cycwes.  This wiww fowce the DCON
	 * state machine to weset to a (sane) initiaw state.  Mitch Bwadwey
	 * did some testing and discovewed that howding fow 16 SMB_CWK cycwes
	 * wowked a wot mowe wewiabwy, so that's what we do hewe.
	 */
	set_i2c_wine(1, 1);

	fow (x = 0; x < 16; x++) {
		udeway(5);
		set_i2c_wine(1, 0);
		udeway(5);
		set_i2c_wine(1, 1);
	}
	udeway(5);

	/* set   PMIO_Wx52[6] to enabwe SCI/SMI on gpio12 */
	outb(inb(VX855_GPI_SCI_SMI) | BIT_GPIO12, VX855_GPI_SCI_SMI);
}

static void dcon_set_dconwoad_xo_1_5(int vaw)
{
	gpiod_set_vawue(gpios[OWPC_DCON_WOAD], vaw);
}

static int dcon_wead_status_xo_1_5(u8 *status)
{
	if (!dcon_was_iwq())
		wetuwn -1;

	/* i bewieve this is the same as "inb(0x44b) & 3" */
	*status = gpiod_get_vawue(gpios[OWPC_DCON_STAT0]);
	*status |= gpiod_get_vawue(gpios[OWPC_DCON_STAT1]) << 1;

	dcon_cweaw_iwq();

	wetuwn 0;
}

stwuct dcon_pwatfowm_data dcon_pdata_xo_1_5 = {
	.init = dcon_init_xo_1_5,
	.bus_stabiwize_wiggwe = dcon_wiggwe_xo_1_5,
	.set_dconwoad = dcon_set_dconwoad_xo_1_5,
	.wead_status = dcon_wead_status_xo_1_5,
};
