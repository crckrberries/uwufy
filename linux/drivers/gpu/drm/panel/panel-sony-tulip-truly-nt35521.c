// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, Winawo Wimited
 *
 * Genewated with winux-mdss-dsi-panew-dwivew-genewatow fwom vendow device twee:
 *   Copywight (c) 2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct twuwy_nt35521 {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	stwuct weguwatow_buwk_data suppwies[2];
	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *bwen_gpio;
};

static inwine
stwuct twuwy_nt35521 *to_twuwy_nt35521(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct twuwy_nt35521, panew);
}

static void twuwy_nt35521_weset(stwuct twuwy_nt35521 *ctx)
{
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	usweep_wange(1000, 2000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	usweep_wange(10000, 11000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	msweep(150);
}

static int twuwy_nt35521_on(stwuct twuwy_nt35521 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	mipi_dsi_genewic_wwite_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xff, 0xaa, 0x55, 0xa5, 0x80);
	mipi_dsi_genewic_wwite_seq(dsi, 0x6f, 0x11, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf7, 0x20, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0x6f, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb1, 0x21);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbd, 0x01, 0xa0, 0x10, 0x08, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb8, 0x01, 0x02, 0x0c, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbb, 0x11, 0x11);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbc, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb6, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb0, 0x09, 0x09);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb1, 0x09, 0x09);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbc, 0x8c, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbd, 0x8c, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xca, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc0, 0x04);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbe, 0xb5);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb3, 0x35, 0x35);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb4, 0x25, 0x25);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb9, 0x43, 0x43);
	mipi_dsi_genewic_wwite_seq(dsi, 0xba, 0x24, 0x24);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xee, 0x03);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb0,
				   0x00, 0xb2, 0x00, 0xb3, 0x00, 0xb6, 0x00, 0xc3,
				   0x00, 0xce, 0x00, 0xe1, 0x00, 0xf3, 0x01, 0x11);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb1,
				   0x01, 0x2e, 0x01, 0x5c, 0x01, 0x82, 0x01, 0xc3,
				   0x01, 0xfe, 0x02, 0x00, 0x02, 0x37, 0x02, 0x77);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb2,
				   0x02, 0xa1, 0x02, 0xd7, 0x02, 0xfe, 0x03, 0x2c,
				   0x03, 0x4b, 0x03, 0x63, 0x03, 0x8f, 0x03, 0x90);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb3, 0x03, 0x96, 0x03, 0x98);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb4,
				   0x00, 0x81, 0x00, 0x8b, 0x00, 0x9c, 0x00, 0xa9,
				   0x00, 0xb5, 0x00, 0xcb, 0x00, 0xdf, 0x01, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb5,
				   0x01, 0x1f, 0x01, 0x51, 0x01, 0x7a, 0x01, 0xbf,
				   0x01, 0xfa, 0x01, 0xfc, 0x02, 0x34, 0x02, 0x76);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb6,
				   0x02, 0x9f, 0x02, 0xd7, 0x02, 0xfc, 0x03, 0x2c,
				   0x03, 0x4a, 0x03, 0x63, 0x03, 0x8f, 0x03, 0xa2);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb7, 0x03, 0xb8, 0x03, 0xba);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb8,
				   0x00, 0x01, 0x00, 0x02, 0x00, 0x0e, 0x00, 0x2a,
				   0x00, 0x41, 0x00, 0x67, 0x00, 0x87, 0x00, 0xb9);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb9,
				   0x00, 0xe2, 0x01, 0x22, 0x01, 0x54, 0x01, 0xa3,
				   0x01, 0xe6, 0x01, 0xe7, 0x02, 0x24, 0x02, 0x67);
	mipi_dsi_genewic_wwite_seq(dsi, 0xba,
				   0x02, 0x93, 0x02, 0xcd, 0x02, 0xf6, 0x03, 0x31,
				   0x03, 0x6c, 0x03, 0xe9, 0x03, 0xef, 0x03, 0xf4);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbb, 0x03, 0xf6, 0x03, 0xf7);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x03);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb0, 0x22, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb1, 0x22, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb2, 0x05, 0x00, 0x60, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb3, 0x05, 0x00, 0x60, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb4, 0x05, 0x00, 0x60, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb5, 0x05, 0x00, 0x60, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xba, 0x53, 0x00, 0x60, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbb, 0x53, 0x00, 0x60, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbc, 0x53, 0x00, 0x60, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbd, 0x53, 0x00, 0x60, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc0, 0x00, 0x34, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc1, 0x00, 0x00, 0x34, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc2, 0x00, 0x00, 0x34, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc3, 0x00, 0x00, 0x34, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc4, 0x60);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc5, 0xc0);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc6, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc7, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x05);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb0, 0x17, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb1, 0x17, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb2, 0x17, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb3, 0x17, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb4, 0x17, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb5, 0x17, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb6, 0x17, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb7, 0x17, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb8, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb9, 0x00, 0x03);
	mipi_dsi_genewic_wwite_seq(dsi, 0xba, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbb, 0x02, 0x03);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbc, 0x02, 0x03);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbd, 0x03, 0x03, 0x00, 0x03, 0x03);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc0, 0x0b);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc1, 0x09);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc2, 0xa6);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc3, 0x05);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc4, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc5, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc6, 0x22);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc7, 0x03);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc8, 0x07, 0x20);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc9, 0x03, 0x20);
	mipi_dsi_genewic_wwite_seq(dsi, 0xca, 0x01, 0x60);
	mipi_dsi_genewic_wwite_seq(dsi, 0xcb, 0x01, 0x60);
	mipi_dsi_genewic_wwite_seq(dsi, 0xcc, 0x00, 0x00, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xcd, 0x00, 0x00, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xce, 0x00, 0x00, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xcf, 0x00, 0x00, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd1, 0x00, 0x05, 0x01, 0x07, 0x10);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd2, 0x10, 0x05, 0x05, 0x03, 0x10);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd3, 0x20, 0x00, 0x43, 0x07, 0x10);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd4, 0x30, 0x00, 0x43, 0x07, 0x10);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd0,
				   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd5,
				   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				   0x00, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd6,
				   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				   0x00, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd7,
				   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				   0x00, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xe5, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xe6, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xe7, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xe8, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xe9, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xea, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xeb, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xec, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xed, 0x30);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb0, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb1, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb2, 0x2d, 0x2e);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb3, 0x31, 0x34);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb4, 0x29, 0x2a);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb5, 0x12, 0x10);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb6, 0x18, 0x16);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb7, 0x00, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb8, 0x08, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb9, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xba, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbb, 0x31, 0x08);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbc, 0x03, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbd, 0x17, 0x19);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbe, 0x11, 0x13);
	mipi_dsi_genewic_wwite_seq(dsi, 0xbf, 0x2a, 0x29);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc0, 0x34, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc1, 0x2e, 0x2d);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc2, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc3, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc4, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc5, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc6, 0x2e, 0x2d);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc7, 0x31, 0x34);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc8, 0x29, 0x2a);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc9, 0x17, 0x19);
	mipi_dsi_genewic_wwite_seq(dsi, 0xca, 0x11, 0x13);
	mipi_dsi_genewic_wwite_seq(dsi, 0xcb, 0x03, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xcc, 0x08, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xcd, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xce, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xcf, 0x31, 0x08);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd0, 0x00, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd1, 0x12, 0x10);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd2, 0x18, 0x16);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd3, 0x2a, 0x29);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd4, 0x34, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd5, 0x2d, 0x2e);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd6, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd7, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xe5, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xe6, 0x31, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd9, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xe7, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0x6f, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf7, 0x47);
	mipi_dsi_genewic_wwite_seq(dsi, 0x6f, 0x0a);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf7, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0x6f, 0x17);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf4, 0x60);
	mipi_dsi_genewic_wwite_seq(dsi, 0x6f, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf9, 0x46);
	mipi_dsi_genewic_wwite_seq(dsi, 0x6f, 0x11);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf3, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0x35, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd9, 0x02, 0x03, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb1, 0x6c, 0x21);
	mipi_dsi_genewic_wwite_seq(dsi, 0xf0, 0x55, 0xaa, 0x52, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0x35, 0x00);

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to exit sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(120);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway on: %d\n", wet);
		wetuwn wet;
	}
	usweep_wange(1000, 2000);

	mipi_dsi_genewic_wwite_seq(dsi, 0x53, 0x24);

	wetuwn 0;
}

static int twuwy_nt35521_off(stwuct twuwy_nt35521 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway off: %d\n", wet);
		wetuwn wet;
	}
	msweep(50);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(150);

	wetuwn 0;
}

static int twuwy_nt35521_pwepawe(stwuct dwm_panew *panew)
{
	stwuct twuwy_nt35521 *ctx = to_twuwy_nt35521(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	twuwy_nt35521_weset(ctx);

	wet = twuwy_nt35521_on(ctx);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize panew: %d\n", wet);
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		wetuwn wet;
	}

	wetuwn 0;
}

static int twuwy_nt35521_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct twuwy_nt35521 *ctx = to_twuwy_nt35521(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = twuwy_nt35521_off(ctx);
	if (wet < 0)
		dev_eww(dev, "Faiwed to un-initiawize panew: %d\n", wet);

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies),
			       ctx->suppwies);

	wetuwn 0;
}

static int twuwy_nt35521_enabwe(stwuct dwm_panew *panew)
{
	stwuct twuwy_nt35521 *ctx = to_twuwy_nt35521(panew);

	gpiod_set_vawue_cansweep(ctx->bwen_gpio, 1);

	wetuwn 0;
}

static int twuwy_nt35521_disabwe(stwuct dwm_panew *panew)
{
	stwuct twuwy_nt35521 *ctx = to_twuwy_nt35521(panew);

	gpiod_set_vawue_cansweep(ctx->bwen_gpio, 0);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode twuwy_nt35521_mode = {
	.cwock = (720 + 232 + 20 + 112) * (1280 + 18 + 1 + 18) * 60 / 1000,
	.hdispway = 720,
	.hsync_stawt = 720 + 232,
	.hsync_end = 720 + 232 + 20,
	.htotaw = 720 + 232 + 20 + 112,
	.vdispway = 1280,
	.vsync_stawt = 1280 + 18,
	.vsync_end = 1280 + 18 + 1,
	.vtotaw = 1280 + 18 + 1 + 18,
	.width_mm = 65,
	.height_mm = 116,
};

static int twuwy_nt35521_get_modes(stwuct dwm_panew *panew,
				   stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &twuwy_nt35521_mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs twuwy_nt35521_panew_funcs = {
	.pwepawe = twuwy_nt35521_pwepawe,
	.unpwepawe = twuwy_nt35521_unpwepawe,
	.enabwe = twuwy_nt35521_enabwe,
	.disabwe = twuwy_nt35521_disabwe,
	.get_modes = twuwy_nt35521_get_modes,
};

static int twuwy_nt35521_bw_update_status(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	u16 bwightness = backwight_get_bwightness(bw);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_bwightness(dsi, bwightness);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int twuwy_nt35521_bw_get_bwightness(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	u16 bwightness;
	int wet;

	wet = mipi_dsi_dcs_get_dispway_bwightness(dsi, &bwightness);
	if (wet < 0)
		wetuwn wet;

	wetuwn bwightness & 0xff;
}

static const stwuct backwight_ops twuwy_nt35521_bw_ops = {
	.update_status = twuwy_nt35521_bw_update_status,
	.get_bwightness = twuwy_nt35521_bw_get_bwightness,
};

static stwuct backwight_device *
twuwy_nt35521_cweate_backwight(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	const stwuct backwight_pwopewties pwops = {
		.type = BACKWIGHT_WAW,
		.bwightness = 255,
		.max_bwightness = 255,
	};

	wetuwn devm_backwight_device_wegistew(dev, dev_name(dev), dev, dsi,
					      &twuwy_nt35521_bw_ops, &pwops);
}

static int twuwy_nt35521_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct twuwy_nt35521 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->suppwies[0].suppwy = "positive5";
	ctx->suppwies[1].suppwy = "negative5";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(ctx->suppwies),
				      ctx->suppwies);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to get weguwatows: %d\n", wet);
		wetuwn wet;
	}

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ctx->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->weset_gpio),
				     "Faiwed to get weset-gpios\n");

	ctx->bwen_gpio = devm_gpiod_get(dev, "backwight", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->bwen_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->bwen_gpio),
				     "Faiwed to get backwight-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_dwvdata(dsi, ctx);

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
			  MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CWOCK_NON_CONTINUOUS;

	dwm_panew_init(&ctx->panew, dev, &twuwy_nt35521_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	ctx->panew.backwight = twuwy_nt35521_cweate_backwight(dsi);
	if (IS_EWW(ctx->panew.backwight))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->panew.backwight),
				     "Faiwed to cweate backwight\n");

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to attach to DSI host: %d\n", wet);
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void twuwy_nt35521_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct twuwy_nt35521 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id twuwy_nt35521_of_match[] = {
	{ .compatibwe = "sony,tuwip-twuwy-nt35521" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, twuwy_nt35521_of_match);

static stwuct mipi_dsi_dwivew twuwy_nt35521_dwivew = {
	.pwobe = twuwy_nt35521_pwobe,
	.wemove = twuwy_nt35521_wemove,
	.dwivew = {
		.name = "panew-twuwy-nt35521",
		.of_match_tabwe = twuwy_nt35521_of_match,
	},
};
moduwe_mipi_dsi_dwivew(twuwy_nt35521_dwivew);

MODUWE_AUTHOW("Shawn Guo <shawn.guo@winawo.owg>");
MODUWE_DESCWIPTION("DWM dwivew fow Sony Tuwip Twuwy NT35521 panew");
MODUWE_WICENSE("GPW v2");
