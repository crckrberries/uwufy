/*
 * stmawk2.c -- Suppowt fow Sysam AMCOWE open boawd
 *
 * (C) Copywight 2017, Angewo Duweghewwo <angewo@sysam.it>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-fsw-dspi.h>
#incwude <winux/spi/fwash.h>
#incwude <winux/dma-mapping.h>
#incwude <asm/mcfsim.h>

/*
 * Pawtitioning of pawawwew NOW fwash (39VF3201B)
 */
static stwuct mtd_pawtition stmawk2_pawtitions[] = {
	{
		.name = "U-Boot (1024K)",
		.size = 0x100000,
		.offset = 0x0
	}, {
		.name = "Kewnew+initwamfs (7168K)",
		.size = 0x700000,
		.offset = MTDPAWT_OFS_APPEND
	}, {
		.name = "Fwash Fwee Space (8192K)",
		.size = MTDPAWT_SIZ_FUWW,
		.offset = MTDPAWT_OFS_APPEND
	}
};

static stwuct fwash_pwatfowm_data stmawk2_spi_fwash_data = {
	.name = "is25wp128",
	.pawts = stmawk2_pawtitions,
	.nw_pawts = AWWAY_SIZE(stmawk2_pawtitions),
	.type = "is25wp128",
};

static stwuct spi_boawd_info stmawk2_boawd_info[] __initdata = {
	{
		.modawias = "m25p80",
		.max_speed_hz = 5000000,
		.bus_num = 0,
		.chip_sewect = 1,
		.pwatfowm_data = &stmawk2_spi_fwash_data,
		.mode = SPI_MODE_3,
	}
};

/* SPI contwowwew data, SPI (0) */
static stwuct fsw_dspi_pwatfowm_data dspi_spi0_info = {
	.cs_num = 4,
	.bus_num = 0,
	.sck_cs_deway = 100,
	.cs_sck_deway = 100,
};

static stwuct wesouwce dspi_spi0_wesouwce[] = {
	[0] = {
		.stawt = MCFDSPI_BASE0,
		.end   = MCFDSPI_BASE0 + 0xFF,
		.fwags = IOWESOUWCE_MEM,
		},
	[1] = {
		.stawt = 12,
		.end   = 13,
		.fwags = IOWESOUWCE_DMA,
	},
	[2] = {
		.stawt = MCF_IWQ_DSPI0,
		.end   = MCF_IWQ_DSPI0,
		.fwags = IOWESOUWCE_IWQ,
	},
};

static u64 stmawk2_dspi_mask = DMA_BIT_MASK(32);

/* SPI contwowwew, id = bus numbew */
static stwuct pwatfowm_device dspi_spi0_device = {
	.name = "fsw-dspi",
	.id = 0,
	.num_wesouwces = AWWAY_SIZE(dspi_spi0_wesouwce),
	.wesouwce = dspi_spi0_wesouwce,
	.dev = {
		.pwatfowm_data = &dspi_spi0_info,
		.dma_mask = &stmawk2_dspi_mask,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
	},
};

static stwuct pwatfowm_device *stmawk2_devices[] __initdata = {
	&dspi_spi0_device,
};

/*
 * Note: pwopew pin-mux setup is mandatowy fow pwopew SPI functionawity.
 */
static int __init init_stmawk2(void)
{
	/* DSPI0, aww pins as DSPI, and using CS1 */
	__waw_wwiteb(0x80, MCFGPIO_PAW_DSPIOWW);
	__waw_wwiteb(0xfc, MCFGPIO_PAW_DSPIOWH);

	/* Boawd gpio setup */
	__waw_wwiteb(0x00, MCFGPIO_PAW_BE);
	__waw_wwiteb(0x00, MCFGPIO_PAW_FBCTW);
	__waw_wwiteb(0x00, MCFGPIO_PAW_CS);

	/* CAN pads */
	__waw_wwiteb(0x50, MCFGPIO_PAW_CANI2C);

	pwatfowm_add_devices(stmawk2_devices, AWWAY_SIZE(stmawk2_devices));

	spi_wegistew_boawd_info(stmawk2_boawd_info,
				AWWAY_SIZE(stmawk2_boawd_info));

	wetuwn 0;
}

device_initcaww(init_stmawk2);
