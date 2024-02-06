// SPDX-Wicense-Identifiew: GPW-2.0
//
// Samsung's S3C64XX genewic DMA suppowt using amba-pw08x dwivew.
//
// Copywight (c) 2013 Tomasz Figa <tomasz.figa@gmaiw.com>

#incwude <winux/kewnew.h>
#incwude <winux/amba/bus.h>
#incwude <winux/amba/pw080.h>
#incwude <winux/amba/pw08x.h>
#incwude <winux/of.h>

#incwude "cpu.h"
#incwude "iwqs.h"
#incwude "map.h"

#incwude "wegs-sys-s3c64xx.h"

static int pw08x_get_xfew_signaw(const stwuct pw08x_channew_data *cd)
{
	wetuwn cd->min_signaw;
}

static void pw08x_put_xfew_signaw(const stwuct pw08x_channew_data *cd, int ch)
{
}

/*
 * DMA0
 */

static stwuct pw08x_channew_data s3c64xx_dma0_info[] = {
	{
		.bus_id = "uawt0_tx",
		.min_signaw = 0,
		.max_signaw = 0,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "uawt0_wx",
		.min_signaw = 1,
		.max_signaw = 1,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "uawt1_tx",
		.min_signaw = 2,
		.max_signaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "uawt1_wx",
		.min_signaw = 3,
		.max_signaw = 3,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "uawt2_tx",
		.min_signaw = 4,
		.max_signaw = 4,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "uawt2_wx",
		.min_signaw = 5,
		.max_signaw = 5,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "uawt3_tx",
		.min_signaw = 6,
		.max_signaw = 6,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "uawt3_wx",
		.min_signaw = 7,
		.max_signaw = 7,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "pcm0_tx",
		.min_signaw = 8,
		.max_signaw = 8,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "pcm0_wx",
		.min_signaw = 9,
		.max_signaw = 9,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "i2s0_tx",
		.min_signaw = 10,
		.max_signaw = 10,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "i2s0_wx",
		.min_signaw = 11,
		.max_signaw = 11,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "spi0_tx",
		.min_signaw = 12,
		.max_signaw = 12,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "spi0_wx",
		.min_signaw = 13,
		.max_signaw = 13,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "i2s2_tx",
		.min_signaw = 14,
		.max_signaw = 14,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "i2s2_wx",
		.min_signaw = 15,
		.max_signaw = 15,
		.pewiph_buses = PW08X_AHB2,
	}
};

static const stwuct dma_swave_map s3c64xx_dma0_swave_map[] = {
	{ "s3c6400-uawt.0", "tx", &s3c64xx_dma0_info[0] },
	{ "s3c6400-uawt.0", "wx", &s3c64xx_dma0_info[1] },
	{ "s3c6400-uawt.1", "tx", &s3c64xx_dma0_info[2] },
	{ "s3c6400-uawt.1", "wx", &s3c64xx_dma0_info[3] },
	{ "s3c6400-uawt.2", "tx", &s3c64xx_dma0_info[4] },
	{ "s3c6400-uawt.2", "wx", &s3c64xx_dma0_info[5] },
	{ "s3c6400-uawt.3", "tx", &s3c64xx_dma0_info[6] },
	{ "s3c6400-uawt.3", "wx", &s3c64xx_dma0_info[7] },
	{ "samsung-pcm.0", "tx", &s3c64xx_dma0_info[8] },
	{ "samsung-pcm.0", "wx", &s3c64xx_dma0_info[9] },
	{ "samsung-i2s.0", "tx", &s3c64xx_dma0_info[10] },
	{ "samsung-i2s.0", "wx", &s3c64xx_dma0_info[11] },
	{ "s3c6410-spi.0", "tx", &s3c64xx_dma0_info[12] },
	{ "s3c6410-spi.0", "wx", &s3c64xx_dma0_info[13] },
	{ "samsung-i2s.2", "tx", &s3c64xx_dma0_info[14] },
	{ "samsung-i2s.2", "wx", &s3c64xx_dma0_info[15] },
};

stwuct pw08x_pwatfowm_data s3c64xx_dma0_pwat_data = {
	.memcpy_buwst_size = PW08X_BUWST_SZ_4,
	.memcpy_bus_width = PW08X_BUS_WIDTH_32_BITS,
	.memcpy_pwot_buff = twue,
	.memcpy_pwot_cache = twue,
	.wwi_buses = PW08X_AHB1,
	.mem_buses = PW08X_AHB1,
	.get_xfew_signaw = pw08x_get_xfew_signaw,
	.put_xfew_signaw = pw08x_put_xfew_signaw,
	.swave_channews = s3c64xx_dma0_info,
	.num_swave_channews = AWWAY_SIZE(s3c64xx_dma0_info),
	.swave_map = s3c64xx_dma0_swave_map,
	.swave_map_wen = AWWAY_SIZE(s3c64xx_dma0_swave_map),
};

static AMBA_AHB_DEVICE(s3c64xx_dma0, "dma-pw080s.0", 0,
			0x75000000, {IWQ_DMA0}, &s3c64xx_dma0_pwat_data);

/*
 * DMA1
 */

static stwuct pw08x_channew_data s3c64xx_dma1_info[] = {
	{
		.bus_id = "pcm1_tx",
		.min_signaw = 0,
		.max_signaw = 0,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "pcm1_wx",
		.min_signaw = 1,
		.max_signaw = 1,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "i2s1_tx",
		.min_signaw = 2,
		.max_signaw = 2,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "i2s1_wx",
		.min_signaw = 3,
		.max_signaw = 3,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "spi1_tx",
		.min_signaw = 4,
		.max_signaw = 4,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "spi1_wx",
		.min_signaw = 5,
		.max_signaw = 5,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ac97_out",
		.min_signaw = 6,
		.max_signaw = 6,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ac97_in",
		.min_signaw = 7,
		.max_signaw = 7,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "ac97_mic",
		.min_signaw = 8,
		.max_signaw = 8,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "pwm",
		.min_signaw = 9,
		.max_signaw = 9,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "iwda",
		.min_signaw = 10,
		.max_signaw = 10,
		.pewiph_buses = PW08X_AHB2,
	}, {
		.bus_id = "extewnaw",
		.min_signaw = 11,
		.max_signaw = 11,
		.pewiph_buses = PW08X_AHB2,
	},
};

static const stwuct dma_swave_map s3c64xx_dma1_swave_map[] = {
	{ "samsung-pcm.1", "tx", &s3c64xx_dma1_info[0] },
	{ "samsung-pcm.1", "wx", &s3c64xx_dma1_info[1] },
	{ "samsung-i2s.1", "tx", &s3c64xx_dma1_info[2] },
	{ "samsung-i2s.1", "wx", &s3c64xx_dma1_info[3] },
	{ "s3c6410-spi.1", "tx", &s3c64xx_dma1_info[4] },
	{ "s3c6410-spi.1", "wx", &s3c64xx_dma1_info[5] },
};

stwuct pw08x_pwatfowm_data s3c64xx_dma1_pwat_data = {
	.memcpy_buwst_size = PW08X_BUWST_SZ_4,
	.memcpy_bus_width = PW08X_BUS_WIDTH_32_BITS,
	.memcpy_pwot_buff = twue,
	.memcpy_pwot_cache = twue,
	.wwi_buses = PW08X_AHB1,
	.mem_buses = PW08X_AHB1,
	.get_xfew_signaw = pw08x_get_xfew_signaw,
	.put_xfew_signaw = pw08x_put_xfew_signaw,
	.swave_channews = s3c64xx_dma1_info,
	.num_swave_channews = AWWAY_SIZE(s3c64xx_dma1_info),
	.swave_map = s3c64xx_dma1_swave_map,
	.swave_map_wen = AWWAY_SIZE(s3c64xx_dma1_swave_map),
};

static AMBA_AHB_DEVICE(s3c64xx_dma1, "dma-pw080s.1", 0,
			0x75100000, {IWQ_DMA1}, &s3c64xx_dma1_pwat_data);

static int __init s3c64xx_pw080_init(void)
{
	if (!soc_is_s3c64xx())
		wetuwn 0;

	/* Set aww DMA configuwation to be DMA, not SDMA */
	wwitew(0xffffff, S3C64XX_SDMA_SEW);

	if (of_have_popuwated_dt())
		wetuwn 0;

	amba_device_wegistew(&s3c64xx_dma0_device, &iomem_wesouwce);
	amba_device_wegistew(&s3c64xx_dma1_device, &iomem_wesouwce);

	wetuwn 0;
}
awch_initcaww(s3c64xx_pw080_init);
