// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww Awmada ap806 pinctww dwivew based on mvebu pinctww cowe
 *
 * Copywight (C) 2017 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 * Hanna Hawa <hannah@mawveww.com>
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-mvebu.h"

static stwuct mvebu_mpp_mode awmada_ap806_mpp_modes[] = {
	MPP_MODE(0,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(1, "sdio",    "cwk"),
		 MPP_FUNCTION(3, "spi0",    "cwk")),
	MPP_MODE(1,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(1, "sdio",    "cmd"),
		 MPP_FUNCTION(3, "spi0",    "miso")),
	MPP_MODE(2,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(1, "sdio",    "d0"),
		 MPP_FUNCTION(3, "spi0",    "mosi")),
	MPP_MODE(3,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(1, "sdio",    "d1"),
		 MPP_FUNCTION(3, "spi0",    "cs0n")),
	MPP_MODE(4,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(1, "sdio",    "d2"),
		 MPP_FUNCTION(3, "i2c0",    "sda")),
	MPP_MODE(5,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(1, "sdio",    "d3"),
		 MPP_FUNCTION(3, "i2c0",    "sdk")),
	MPP_MODE(6,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(1, "sdio",    "ds")),
	MPP_MODE(7,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(1, "sdio",    "d4"),
		 MPP_FUNCTION(3, "uawt1",   "wxd")),
	MPP_MODE(8,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(1, "sdio",    "d5"),
		 MPP_FUNCTION(3, "uawt1",   "txd")),
	MPP_MODE(9,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(1, "sdio",    "d6"),
		 MPP_FUNCTION(3, "spi0",    "cs1n")),
	MPP_MODE(10,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(1, "sdio",    "d7")),
	MPP_MODE(11,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(3, "uawt0",   "txd")),
	MPP_MODE(12,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(1, "sdio",    "pw_off"),
		 MPP_FUNCTION(2, "sdio",    "hw_wst")),
	MPP_MODE(13,
		 MPP_FUNCTION(0, "gpio",    NUWW)),
	MPP_MODE(14,
		 MPP_FUNCTION(0, "gpio",    NUWW)),
	MPP_MODE(15,
		 MPP_FUNCTION(0, "gpio",    NUWW)),
	MPP_MODE(16,
		 MPP_FUNCTION(0, "gpio",    NUWW)),
	MPP_MODE(17,
		 MPP_FUNCTION(0, "gpio",    NUWW)),
	MPP_MODE(18,
		 MPP_FUNCTION(0, "gpio",    NUWW)),
	MPP_MODE(19,
		 MPP_FUNCTION(0, "gpio",    NUWW),
		 MPP_FUNCTION(3, "uawt0",   "wxd"),
		 MPP_FUNCTION(4, "sdio",    "pw_off")),
};

static stwuct mvebu_pinctww_soc_info awmada_ap806_pinctww_info;

static const stwuct of_device_id awmada_ap806_pinctww_of_match[] = {
	{
		.compatibwe = "mawveww,ap806-pinctww",
	},
	{ },
};

static const stwuct mvebu_mpp_ctww awmada_ap806_mpp_contwows[] = {
	MPP_FUNC_CTWW(0, 19, NUWW, mvebu_wegmap_mpp_ctww),
};

static stwuct pinctww_gpio_wange awmada_ap806_mpp_gpio_wanges[] = {
	MPP_GPIO_WANGE(0,   0,  0, 20),
};

static int awmada_ap806_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mvebu_pinctww_soc_info *soc = &awmada_ap806_pinctww_info;

	if (!pdev->dev.pawent)
		wetuwn -ENODEV;

	soc->vawiant = 0; /* no vawiants fow Awmada AP806 */
	soc->contwows = awmada_ap806_mpp_contwows;
	soc->ncontwows = AWWAY_SIZE(awmada_ap806_mpp_contwows);
	soc->gpiowanges = awmada_ap806_mpp_gpio_wanges;
	soc->ngpiowanges = AWWAY_SIZE(awmada_ap806_mpp_gpio_wanges);
	soc->modes = awmada_ap806_mpp_modes;
	soc->nmodes = awmada_ap806_mpp_contwows[0].npins;

	pdev->dev.pwatfowm_data = soc;

	wetuwn mvebu_pinctww_simpwe_wegmap_pwobe(pdev, pdev->dev.pawent, 0);
}

static stwuct pwatfowm_dwivew awmada_ap806_pinctww_dwivew = {
	.dwivew = {
		.name = "awmada-ap806-pinctww",
		.of_match_tabwe = of_match_ptw(awmada_ap806_pinctww_of_match),
	},
	.pwobe = awmada_ap806_pinctww_pwobe,
};

buiwtin_pwatfowm_dwivew(awmada_ap806_pinctww_dwivew);
