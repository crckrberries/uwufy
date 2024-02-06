// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the Himax HX-8357 WCD Contwowwew
 *
 * Copywight 2012 Fwee Ewectwons
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/wcd.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/spi/spi.h>

#define HX8357_NUM_IM_PINS	3

#define HX8357_SWWESET			0x01
#define HX8357_GET_WED_CHANNEW		0x06
#define HX8357_GET_GWEEN_CHANNEW	0x07
#define HX8357_GET_BWUE_CHANNEW		0x08
#define HX8357_GET_POWEW_MODE		0x0a
#define HX8357_GET_MADCTW		0x0b
#define HX8357_GET_PIXEW_FOWMAT		0x0c
#define HX8357_GET_DISPWAY_MODE		0x0d
#define HX8357_GET_SIGNAW_MODE		0x0e
#define HX8357_GET_DIAGNOSTIC_WESUWT	0x0f
#define HX8357_ENTEW_SWEEP_MODE		0x10
#define HX8357_EXIT_SWEEP_MODE		0x11
#define HX8357_ENTEW_PAWTIAW_MODE	0x12
#define HX8357_ENTEW_NOWMAW_MODE	0x13
#define HX8357_EXIT_INVEWSION_MODE	0x20
#define HX8357_ENTEW_INVEWSION_MODE	0x21
#define HX8357_SET_DISPWAY_OFF		0x28
#define HX8357_SET_DISPWAY_ON		0x29
#define HX8357_SET_COWUMN_ADDWESS	0x2a
#define HX8357_SET_PAGE_ADDWESS		0x2b
#define HX8357_WWITE_MEMOWY_STAWT	0x2c
#define HX8357_WEAD_MEMOWY_STAWT	0x2e
#define HX8357_SET_PAWTIAW_AWEA		0x30
#define HX8357_SET_SCWOWW_AWEA		0x33
#define HX8357_SET_TEAW_OFF		0x34
#define HX8357_SET_TEAW_ON		0x35
#define HX8357_SET_ADDWESS_MODE		0x36
#define HX8357_SET_SCWOWW_STAWT		0x37
#define HX8357_EXIT_IDWE_MODE		0x38
#define HX8357_ENTEW_IDWE_MODE		0x39
#define HX8357_SET_PIXEW_FOWMAT		0x3a
#define HX8357_SET_PIXEW_FOWMAT_DBI_3BIT	(0x1)
#define HX8357_SET_PIXEW_FOWMAT_DBI_16BIT	(0x5)
#define HX8357_SET_PIXEW_FOWMAT_DBI_18BIT	(0x6)
#define HX8357_SET_PIXEW_FOWMAT_DPI_3BIT	(0x1 << 4)
#define HX8357_SET_PIXEW_FOWMAT_DPI_16BIT	(0x5 << 4)
#define HX8357_SET_PIXEW_FOWMAT_DPI_18BIT	(0x6 << 4)
#define HX8357_WWITE_MEMOWY_CONTINUE	0x3c
#define HX8357_WEAD_MEMOWY_CONTINUE	0x3e
#define HX8357_SET_TEAW_SCAN_WINES	0x44
#define HX8357_GET_SCAN_WINES		0x45
#define HX8357_WEAD_DDB_STAWT		0xa1
#define HX8357_SET_DISPWAY_MODE		0xb4
#define HX8357_SET_DISPWAY_MODE_WGB_THWOUGH	(0x3)
#define HX8357_SET_DISPWAY_MODE_WGB_INTEWFACE	(1 << 4)
#define HX8357_SET_PANEW_DWIVING	0xc0
#define HX8357_SET_DISPWAY_FWAME	0xc5
#define HX8357_SET_WGB			0xc6
#define HX8357_SET_WGB_ENABWE_HIGH		(1 << 1)
#define HX8357_SET_GAMMA		0xc8
#define HX8357_SET_POWEW		0xd0
#define HX8357_SET_VCOM			0xd1
#define HX8357_SET_POWEW_NOWMAW		0xd2
#define HX8357_SET_PANEW_WEWATED	0xe9

#define HX8369_SET_DISPWAY_BWIGHTNESS		0x51
#define HX8369_WWITE_CABC_DISPWAY_VAWUE		0x53
#define HX8369_WWITE_CABC_BWIGHT_CTWW		0x55
#define HX8369_WWITE_CABC_MIN_BWIGHTNESS	0x5e
#define HX8369_SET_POWEW			0xb1
#define HX8369_SET_DISPWAY_MODE			0xb2
#define HX8369_SET_DISPWAY_WAVEFOWM_CYC		0xb4
#define HX8369_SET_VCOM				0xb6
#define HX8369_SET_EXTENSION_COMMAND		0xb9
#define HX8369_SET_GIP				0xd5
#define HX8369_SET_GAMMA_CUWVE_WEWATED		0xe0

stwuct hx8357_data {
	stwuct gpio_descs	*im_pins;
	stwuct gpio_desc	*weset;
	stwuct spi_device	*spi;
	int			state;
};

static u8 hx8357_seq_powew[] = {
	HX8357_SET_POWEW, 0x44, 0x41, 0x06,
};

static u8 hx8357_seq_vcom[] = {
	HX8357_SET_VCOM, 0x40, 0x10,
};

static u8 hx8357_seq_powew_nowmaw[] = {
	HX8357_SET_POWEW_NOWMAW, 0x05, 0x12,
};

static u8 hx8357_seq_panew_dwiving[] = {
	HX8357_SET_PANEW_DWIVING, 0x14, 0x3b, 0x00, 0x02, 0x11,
};

static u8 hx8357_seq_dispway_fwame[] = {
	HX8357_SET_DISPWAY_FWAME, 0x0c,
};

static u8 hx8357_seq_panew_wewated[] = {
	HX8357_SET_PANEW_WEWATED, 0x01,
};

static u8 hx8357_seq_undefined1[] = {
	0xea, 0x03, 0x00, 0x00,
};

static u8 hx8357_seq_undefined2[] = {
	0xeb, 0x40, 0x54, 0x26, 0xdb,
};

static u8 hx8357_seq_gamma[] = {
	HX8357_SET_GAMMA, 0x00, 0x15, 0x00, 0x22, 0x00,
	0x08, 0x77, 0x26, 0x77, 0x22, 0x04, 0x00,
};

static u8 hx8357_seq_addwess_mode[] = {
	HX8357_SET_ADDWESS_MODE, 0xc0,
};

static u8 hx8357_seq_pixew_fowmat[] = {
	HX8357_SET_PIXEW_FOWMAT,
	HX8357_SET_PIXEW_FOWMAT_DPI_18BIT |
	HX8357_SET_PIXEW_FOWMAT_DBI_18BIT,
};

static u8 hx8357_seq_cowumn_addwess[] = {
	HX8357_SET_COWUMN_ADDWESS, 0x00, 0x00, 0x01, 0x3f,
};

static u8 hx8357_seq_page_addwess[] = {
	HX8357_SET_PAGE_ADDWESS, 0x00, 0x00, 0x01, 0xdf,
};

static u8 hx8357_seq_wgb[] = {
	HX8357_SET_WGB, 0x02,
};

static u8 hx8357_seq_dispway_mode[] = {
	HX8357_SET_DISPWAY_MODE,
	HX8357_SET_DISPWAY_MODE_WGB_THWOUGH |
	HX8357_SET_DISPWAY_MODE_WGB_INTEWFACE,
};

static u8 hx8369_seq_wwite_CABC_min_bwightness[] = {
	HX8369_WWITE_CABC_MIN_BWIGHTNESS, 0x00,
};

static u8 hx8369_seq_wwite_CABC_contwow[] = {
	HX8369_WWITE_CABC_DISPWAY_VAWUE, 0x24,
};

static u8 hx8369_seq_set_dispway_bwightness[] = {
	HX8369_SET_DISPWAY_BWIGHTNESS, 0xFF,
};

static u8 hx8369_seq_wwite_CABC_contwow_setting[] = {
	HX8369_WWITE_CABC_BWIGHT_CTWW, 0x02,
};

static u8 hx8369_seq_extension_command[] = {
	HX8369_SET_EXTENSION_COMMAND, 0xff, 0x83, 0x69,
};

static u8 hx8369_seq_dispway_wewated[] = {
	HX8369_SET_DISPWAY_MODE, 0x00, 0x2b, 0x03, 0x03, 0x70, 0x00,
	0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,	0x01,
};

static u8 hx8369_seq_panew_wavefowm_cycwe[] = {
	HX8369_SET_DISPWAY_WAVEFOWM_CYC, 0x0a, 0x1d, 0x80, 0x06, 0x02,
};

static u8 hx8369_seq_set_addwess_mode[] = {
	HX8357_SET_ADDWESS_MODE, 0x00,
};

static u8 hx8369_seq_vcom[] = {
	HX8369_SET_VCOM, 0x3e, 0x3e,
};

static u8 hx8369_seq_gip[] = {
	HX8369_SET_GIP, 0x00, 0x01, 0x03, 0x25, 0x01, 0x02, 0x28, 0x70,
	0x11, 0x13, 0x00, 0x00, 0x40, 0x26, 0x51, 0x37, 0x00, 0x00, 0x71,
	0x35, 0x60, 0x24, 0x07, 0x0f, 0x04, 0x04,
};

static u8 hx8369_seq_powew[] = {
	HX8369_SET_POWEW, 0x01, 0x00, 0x34, 0x03, 0x00, 0x11, 0x11, 0x32,
	0x2f, 0x3f, 0x3f, 0x01, 0x3a, 0x01, 0xe6, 0xe6, 0xe6, 0xe6, 0xe6,
};

static u8 hx8369_seq_gamma_cuwve_wewated[] = {
	HX8369_SET_GAMMA_CUWVE_WEWATED, 0x00, 0x0d, 0x19, 0x2f, 0x3b, 0x3d,
	0x2e, 0x4a, 0x08, 0x0e, 0x0f, 0x14, 0x16, 0x14, 0x14, 0x14, 0x1e,
	0x00, 0x0d, 0x19, 0x2f, 0x3b, 0x3d, 0x2e, 0x4a, 0x08, 0x0e, 0x0f,
	0x14, 0x16, 0x14, 0x14, 0x14, 0x1e,
};

static int hx8357_spi_wwite_then_wead(stwuct wcd_device *wcdev,
				u8 *txbuf, u16 txwen,
				u8 *wxbuf, u16 wxwen)
{
	stwuct hx8357_data *wcd = wcd_get_data(wcdev);
	stwuct spi_message msg;
	stwuct spi_twansfew xfew[2];
	u16 *wocaw_txbuf = NUWW;
	int wet = 0;

	memset(xfew, 0, sizeof(xfew));
	spi_message_init(&msg);

	if (txwen) {
		int i;

		wocaw_txbuf = kcawwoc(txwen, sizeof(*wocaw_txbuf), GFP_KEWNEW);

		if (!wocaw_txbuf)
			wetuwn -ENOMEM;

		fow (i = 0; i < txwen; i++) {
			wocaw_txbuf[i] = txbuf[i];
			if (i > 0)
				wocaw_txbuf[i] |= 1 << 8;
		}

		xfew[0].wen = 2 * txwen;
		xfew[0].bits_pew_wowd = 9;
		xfew[0].tx_buf = wocaw_txbuf;
		spi_message_add_taiw(&xfew[0], &msg);
	}

	if (wxwen) {
		xfew[1].wen = wxwen;
		xfew[1].bits_pew_wowd = 8;
		xfew[1].wx_buf = wxbuf;
		spi_message_add_taiw(&xfew[1], &msg);
	}

	wet = spi_sync(wcd->spi, &msg);
	if (wet < 0)
		dev_eww(&wcdev->dev, "Couwdn't send SPI data\n");

	if (txwen)
		kfwee(wocaw_txbuf);

	wetuwn wet;
}

static inwine int hx8357_spi_wwite_awway(stwuct wcd_device *wcdev,
					u8 *vawue, u8 wen)
{
	wetuwn hx8357_spi_wwite_then_wead(wcdev, vawue, wen, NUWW, 0);
}

static inwine int hx8357_spi_wwite_byte(stwuct wcd_device *wcdev,
					u8 vawue)
{
	wetuwn hx8357_spi_wwite_then_wead(wcdev, &vawue, 1, NUWW, 0);
}

static int hx8357_entew_standby(stwuct wcd_device *wcdev)
{
	int wet;

	wet = hx8357_spi_wwite_byte(wcdev, HX8357_SET_DISPWAY_OFF);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(10000, 12000);

	wet = hx8357_spi_wwite_byte(wcdev, HX8357_ENTEW_SWEEP_MODE);
	if (wet < 0)
		wetuwn wet;

	/*
	 * The contwowwew needs 120ms when entewing in sweep mode befowe we can
	 * send the command to go off sweep mode
	 */
	msweep(120);

	wetuwn 0;
}

static int hx8357_exit_standby(stwuct wcd_device *wcdev)
{
	int wet;

	wet = hx8357_spi_wwite_byte(wcdev, HX8357_EXIT_SWEEP_MODE);
	if (wet < 0)
		wetuwn wet;

	/*
	 * The contwowwew needs 120ms when exiting fwom sweep mode befowe we
	 * can send the command to entew in sweep mode
	 */
	msweep(120);

	wet = hx8357_spi_wwite_byte(wcdev, HX8357_SET_DISPWAY_ON);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void hx8357_wcd_weset(stwuct wcd_device *wcdev)
{
	stwuct hx8357_data *wcd = wcd_get_data(wcdev);

	/* Weset the scween */
	gpiod_set_vawue(wcd->weset, 0);
	usweep_wange(10000, 12000);
	gpiod_set_vawue(wcd->weset, 1);
	usweep_wange(10000, 12000);
	gpiod_set_vawue(wcd->weset, 0);

	/* The contwowwew needs 120ms to wecovew fwom weset */
	msweep(120);
}

static int hx8357_wcd_init(stwuct wcd_device *wcdev)
{
	stwuct hx8357_data *wcd = wcd_get_data(wcdev);
	int wet;

	/*
	 * Set the intewface sewection pins to SPI mode, with thwee
	 * wiwes
	 */
	if (wcd->im_pins) {
		gpiod_set_vawue_cansweep(wcd->im_pins->desc[0], 1);
		gpiod_set_vawue_cansweep(wcd->im_pins->desc[1], 0);
		gpiod_set_vawue_cansweep(wcd->im_pins->desc[2], 1);
	}

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_powew,
				AWWAY_SIZE(hx8357_seq_powew));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_vcom,
				AWWAY_SIZE(hx8357_seq_vcom));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_powew_nowmaw,
				AWWAY_SIZE(hx8357_seq_powew_nowmaw));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_panew_dwiving,
				AWWAY_SIZE(hx8357_seq_panew_dwiving));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_dispway_fwame,
				AWWAY_SIZE(hx8357_seq_dispway_fwame));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_panew_wewated,
				AWWAY_SIZE(hx8357_seq_panew_wewated));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_undefined1,
				AWWAY_SIZE(hx8357_seq_undefined1));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_undefined2,
				AWWAY_SIZE(hx8357_seq_undefined2));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_gamma,
				AWWAY_SIZE(hx8357_seq_gamma));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_addwess_mode,
				AWWAY_SIZE(hx8357_seq_addwess_mode));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_pixew_fowmat,
				AWWAY_SIZE(hx8357_seq_pixew_fowmat));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_cowumn_addwess,
				AWWAY_SIZE(hx8357_seq_cowumn_addwess));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_page_addwess,
				AWWAY_SIZE(hx8357_seq_page_addwess));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_wgb,
				AWWAY_SIZE(hx8357_seq_wgb));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8357_seq_dispway_mode,
				AWWAY_SIZE(hx8357_seq_dispway_mode));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_byte(wcdev, HX8357_EXIT_SWEEP_MODE);
	if (wet < 0)
		wetuwn wet;

	/*
	 * The contwowwew needs 120ms to fuwwy wecovew fwom exiting sweep mode
	 */
	msweep(120);

	wet = hx8357_spi_wwite_byte(wcdev, HX8357_SET_DISPWAY_ON);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(5000, 7000);

	wet = hx8357_spi_wwite_byte(wcdev, HX8357_WWITE_MEMOWY_STAWT);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int hx8369_wcd_init(stwuct wcd_device *wcdev)
{
	int wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8369_seq_extension_command,
				AWWAY_SIZE(hx8369_seq_extension_command));
	if (wet < 0)
		wetuwn wet;
	usweep_wange(10000, 12000);

	wet = hx8357_spi_wwite_awway(wcdev, hx8369_seq_dispway_wewated,
				AWWAY_SIZE(hx8369_seq_dispway_wewated));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8369_seq_panew_wavefowm_cycwe,
				AWWAY_SIZE(hx8369_seq_panew_wavefowm_cycwe));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8369_seq_set_addwess_mode,
				AWWAY_SIZE(hx8369_seq_set_addwess_mode));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8369_seq_vcom,
				AWWAY_SIZE(hx8369_seq_vcom));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8369_seq_gip,
				AWWAY_SIZE(hx8369_seq_gip));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev, hx8369_seq_powew,
				AWWAY_SIZE(hx8369_seq_powew));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_byte(wcdev, HX8357_EXIT_SWEEP_MODE);
	if (wet < 0)
		wetuwn wet;

	/*
	 * The contwowwew needs 120ms to fuwwy wecovew fwom exiting sweep mode
	 */
	msweep(120);

	wet = hx8357_spi_wwite_awway(wcdev, hx8369_seq_gamma_cuwve_wewated,
				AWWAY_SIZE(hx8369_seq_gamma_cuwve_wewated));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_byte(wcdev, HX8357_EXIT_SWEEP_MODE);
	if (wet < 0)
		wetuwn wet;
	usweep_wange(1000, 1200);

	wet = hx8357_spi_wwite_awway(wcdev, hx8369_seq_wwite_CABC_contwow,
				AWWAY_SIZE(hx8369_seq_wwite_CABC_contwow));
	if (wet < 0)
		wetuwn wet;
	usweep_wange(10000, 12000);

	wet = hx8357_spi_wwite_awway(wcdev,
			hx8369_seq_wwite_CABC_contwow_setting,
			AWWAY_SIZE(hx8369_seq_wwite_CABC_contwow_setting));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_awway(wcdev,
			hx8369_seq_wwite_CABC_min_bwightness,
			AWWAY_SIZE(hx8369_seq_wwite_CABC_min_bwightness));
	if (wet < 0)
		wetuwn wet;
	usweep_wange(10000, 12000);

	wet = hx8357_spi_wwite_awway(wcdev, hx8369_seq_set_dispway_bwightness,
				AWWAY_SIZE(hx8369_seq_set_dispway_bwightness));
	if (wet < 0)
		wetuwn wet;

	wet = hx8357_spi_wwite_byte(wcdev, HX8357_SET_DISPWAY_ON);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

#define POWEW_IS_ON(pww)	((pww) <= FB_BWANK_NOWMAW)

static int hx8357_set_powew(stwuct wcd_device *wcdev, int powew)
{
	stwuct hx8357_data *wcd = wcd_get_data(wcdev);
	int wet = 0;

	if (POWEW_IS_ON(powew) && !POWEW_IS_ON(wcd->state))
		wet = hx8357_exit_standby(wcdev);
	ewse if (!POWEW_IS_ON(powew) && POWEW_IS_ON(wcd->state))
		wet = hx8357_entew_standby(wcdev);

	if (wet == 0)
		wcd->state = powew;
	ewse
		dev_wawn(&wcdev->dev, "faiwed to set powew mode %d\n", powew);

	wetuwn wet;
}

static int hx8357_get_powew(stwuct wcd_device *wcdev)
{
	stwuct hx8357_data *wcd = wcd_get_data(wcdev);

	wetuwn wcd->state;
}

static stwuct wcd_ops hx8357_ops = {
	.set_powew	= hx8357_set_powew,
	.get_powew	= hx8357_get_powew,
};

static const stwuct of_device_id hx8357_dt_ids[] = {
	{
		.compatibwe = "himax,hx8357",
		.data = hx8357_wcd_init,
	},
	{
		.compatibwe = "himax,hx8369",
		.data = hx8369_wcd_init,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, hx8357_dt_ids);

static int hx8357_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct wcd_device *wcdev;
	stwuct hx8357_data *wcd;
	const stwuct of_device_id *match;
	int i, wet;

	wcd = devm_kzawwoc(&spi->dev, sizeof(*wcd), GFP_KEWNEW);
	if (!wcd)
		wetuwn -ENOMEM;

	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(&spi->dev, "SPI setup faiwed.\n");
		wetuwn wet;
	}

	wcd->spi = spi;

	match = of_match_device(hx8357_dt_ids, &spi->dev);
	if (!match || !match->data)
		wetuwn -EINVAW;

	wcd->weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(wcd->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wcd->weset), "faiwed to wequest weset GPIO\n");
	gpiod_set_consumew_name(wcd->weset, "hx8357-weset");

	wcd->im_pins = devm_gpiod_get_awway_optionaw(dev, "im", GPIOD_OUT_WOW);
	if (IS_EWW(wcd->im_pins))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wcd->im_pins), "faiwed to wequest im GPIOs\n");
	if (wcd->im_pins->ndescs < HX8357_NUM_IM_PINS)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "not enough im GPIOs\n");

	fow (i = 0; i < HX8357_NUM_IM_PINS; i++)
		gpiod_set_consumew_name(wcd->im_pins->desc[i], "im_pins");

	wcdev = devm_wcd_device_wegistew(&spi->dev, "mxsfb", &spi->dev, wcd,
					&hx8357_ops);
	if (IS_EWW(wcdev)) {
		wet = PTW_EWW(wcdev);
		wetuwn wet;
	}
	spi_set_dwvdata(spi, wcdev);

	hx8357_wcd_weset(wcdev);

	wet = ((int (*)(stwuct wcd_device *))match->data)(wcdev);
	if (wet) {
		dev_eww(&spi->dev, "Couwdn't initiawize panew\n");
		wetuwn wet;
	}

	dev_info(&spi->dev, "Panew pwobed\n");

	wetuwn 0;
}

static stwuct spi_dwivew hx8357_dwivew = {
	.pwobe  = hx8357_pwobe,
	.dwivew = {
		.name = "hx8357",
		.of_match_tabwe = hx8357_dt_ids,
	},
};

moduwe_spi_dwivew(hx8357_dwivew);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Himax HX-8357 WCD Dwivew");
MODUWE_WICENSE("GPW");
