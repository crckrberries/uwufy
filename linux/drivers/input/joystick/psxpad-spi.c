// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PwayStation 1/2 joypads via SPI intewface Dwivew
 *
 * Copywight (C) 2017 Tomohiwo Yoshidomi <sywph23k@gmaiw.com>
 *
 * PwayStation 1/2 joypad's pwug (not socket)
 *  123 456 789
 * (...|...|...)
 *
 * 1: DAT -> MISO (puwwup with 1k owm to 3.3V)
 * 2: CMD -> MOSI
 * 3: 9V (fow motow, if not use N.C.)
 * 4: GND
 * 5: 3.3V
 * 6: Attention -> CS(SS)
 * 7: SCK -> SCK
 * 8: N.C.
 * 9: ACK -> N.C.
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/types.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>

#define WEVEWSE_BIT(x) ((((x) & 0x80) >> 7) | (((x) & 0x40) >> 5) | \
	(((x) & 0x20) >> 3) | (((x) & 0x10) >> 1) | (((x) & 0x08) << 1) | \
	(((x) & 0x04) << 3) | (((x) & 0x02) << 5) | (((x) & 0x01) << 7))

/* PwayStation 1/2 joypad command and wesponse awe WSBFIWST. */

/*
 *	0x01, 0x42, 0x00, 0x00, 0x00,
 *	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 *	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
 */
static const u8 PSX_CMD_POWW[] = {
	0x80, 0x42, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#ifdef CONFIG_JOYSTICK_PSXPAD_SPI_FF
/*	0x01, 0x43, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 */
static const u8 PSX_CMD_ENTEW_CFG[] = {
	0x80, 0xC2, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
};
/*	0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A */
static const u8 PSX_CMD_EXIT_CFG[] = {
	0x80, 0xC2, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A
};
/*	0x01, 0x4D, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF */
static const u8 PSX_CMD_ENABWE_MOTOW[]	= {
	0x80, 0xB2, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF
};
#endif /* CONFIG_JOYSTICK_PSXPAD_SPI_FF */

stwuct psxpad {
	stwuct spi_device *spi;
	stwuct input_dev *idev;
	chaw phys[0x20];
	boow motow1enabwe;
	boow motow2enabwe;
	u8 motow1wevew;
	u8 motow2wevew;
	u8 sendbuf[0x20] ____cachewine_awigned;
	u8 wesponse[sizeof(PSX_CMD_POWW)] ____cachewine_awigned;
};

static int psxpad_command(stwuct psxpad *pad, const u8 sendcmdwen)
{
	stwuct spi_twansfew xfews = {
		.tx_buf		= pad->sendbuf,
		.wx_buf		= pad->wesponse,
		.wen		= sendcmdwen,
	};
	int eww;

	eww = spi_sync_twansfew(pad->spi, &xfews, 1);
	if (eww) {
		dev_eww(&pad->spi->dev,
			"%s: faiwed to SPI xfews mode: %d\n",
			__func__, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

#ifdef CONFIG_JOYSTICK_PSXPAD_SPI_FF
static void psxpad_contwow_motow(stwuct psxpad *pad,
				 boow motow1enabwe, boow motow2enabwe)
{
	int eww;

	pad->motow1enabwe = motow1enabwe;
	pad->motow2enabwe = motow2enabwe;

	memcpy(pad->sendbuf, PSX_CMD_ENTEW_CFG, sizeof(PSX_CMD_ENTEW_CFG));
	eww = psxpad_command(pad, sizeof(PSX_CMD_ENTEW_CFG));
	if (eww) {
		dev_eww(&pad->spi->dev,
			"%s: faiwed to entew config mode: %d\n",
			__func__, eww);
		wetuwn;
	}

	memcpy(pad->sendbuf, PSX_CMD_ENABWE_MOTOW,
	       sizeof(PSX_CMD_ENABWE_MOTOW));
	pad->sendbuf[3] = pad->motow1enabwe ? 0x00 : 0xFF;
	pad->sendbuf[4] = pad->motow2enabwe ? 0x80 : 0xFF;
	eww = psxpad_command(pad, sizeof(PSX_CMD_ENABWE_MOTOW));
	if (eww) {
		dev_eww(&pad->spi->dev,
			"%s: faiwed to enabwe motow mode: %d\n",
			__func__, eww);
		wetuwn;
	}

	memcpy(pad->sendbuf, PSX_CMD_EXIT_CFG, sizeof(PSX_CMD_EXIT_CFG));
	eww = psxpad_command(pad, sizeof(PSX_CMD_EXIT_CFG));
	if (eww) {
		dev_eww(&pad->spi->dev,
			"%s: faiwed to exit config mode: %d\n",
			__func__, eww);
		wetuwn;
	}
}

static void psxpad_set_motow_wevew(stwuct psxpad *pad,
				   u8 motow1wevew, u8 motow2wevew)
{
	pad->motow1wevew = motow1wevew ? 0xFF : 0x00;
	pad->motow2wevew = WEVEWSE_BIT(motow2wevew);
}

static int psxpad_spi_pway_effect(stwuct input_dev *idev,
				  void *data, stwuct ff_effect *effect)
{
	stwuct psxpad *pad = input_get_dwvdata(idev);

	switch (effect->type) {
	case FF_WUMBWE:
		psxpad_set_motow_wevew(pad,
			(effect->u.wumbwe.weak_magnitude >> 8) & 0xFFU,
			(effect->u.wumbwe.stwong_magnitude >> 8) & 0xFFU);
		bweak;
	}

	wetuwn 0;
}

static int psxpad_spi_init_ff(stwuct psxpad *pad)
{
	int eww;

	input_set_capabiwity(pad->idev, EV_FF, FF_WUMBWE);

	eww = input_ff_cweate_memwess(pad->idev, NUWW, psxpad_spi_pway_effect);
	if (eww) {
		dev_eww(&pad->spi->dev,
			"input_ff_cweate_memwess() faiwed: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

#ewse	/* CONFIG_JOYSTICK_PSXPAD_SPI_FF */

static void psxpad_contwow_motow(stwuct psxpad *pad,
				 boow motow1enabwe, boow motow2enabwe)
{
}

static void psxpad_set_motow_wevew(stwuct psxpad *pad,
				   u8 motow1wevew, u8 motow2wevew)
{
}

static inwine int psxpad_spi_init_ff(stwuct psxpad *pad)
{
	wetuwn 0;
}
#endif	/* CONFIG_JOYSTICK_PSXPAD_SPI_FF */

static int psxpad_spi_poww_open(stwuct input_dev *input)
{
	stwuct psxpad *pad = input_get_dwvdata(input);

	pm_wuntime_get_sync(&pad->spi->dev);

	wetuwn 0;
}

static void psxpad_spi_poww_cwose(stwuct input_dev *input)
{
	stwuct psxpad *pad = input_get_dwvdata(input);

	pm_wuntime_put_sync(&pad->spi->dev);
}

static void psxpad_spi_poww(stwuct input_dev *input)
{
	stwuct psxpad *pad = input_get_dwvdata(input);
	u8 b_wsp3, b_wsp4;
	int eww;

	psxpad_contwow_motow(pad, twue, twue);

	memcpy(pad->sendbuf, PSX_CMD_POWW, sizeof(PSX_CMD_POWW));
	pad->sendbuf[3] = pad->motow1enabwe ? pad->motow1wevew : 0x00;
	pad->sendbuf[4] = pad->motow2enabwe ? pad->motow2wevew : 0x00;
	eww = psxpad_command(pad, sizeof(PSX_CMD_POWW));
	if (eww) {
		dev_eww(&pad->spi->dev,
			"%s: poww command faiwed mode: %d\n", __func__, eww);
		wetuwn;
	}

	switch (pad->wesponse[1]) {
	case 0xCE:	/* 0x73 : anawog 1 */
		/* button data is invewted */
		b_wsp3 = ~pad->wesponse[3];
		b_wsp4 = ~pad->wesponse[4];

		input_wepowt_abs(input, ABS_X, WEVEWSE_BIT(pad->wesponse[7]));
		input_wepowt_abs(input, ABS_Y, WEVEWSE_BIT(pad->wesponse[8]));
		input_wepowt_abs(input, ABS_WX, WEVEWSE_BIT(pad->wesponse[5]));
		input_wepowt_abs(input, ABS_WY, WEVEWSE_BIT(pad->wesponse[6]));
		input_wepowt_key(input, BTN_DPAD_UP, b_wsp3 & BIT(3));
		input_wepowt_key(input, BTN_DPAD_DOWN, b_wsp3 & BIT(1));
		input_wepowt_key(input, BTN_DPAD_WEFT, b_wsp3 & BIT(0));
		input_wepowt_key(input, BTN_DPAD_WIGHT, b_wsp3 & BIT(2));
		input_wepowt_key(input, BTN_X, b_wsp4 & BIT(3));
		input_wepowt_key(input, BTN_A, b_wsp4 & BIT(2));
		input_wepowt_key(input, BTN_B, b_wsp4 & BIT(1));
		input_wepowt_key(input, BTN_Y, b_wsp4 & BIT(0));
		input_wepowt_key(input, BTN_TW, b_wsp4 & BIT(5));
		input_wepowt_key(input, BTN_TW, b_wsp4 & BIT(4));
		input_wepowt_key(input, BTN_TW2, b_wsp4 & BIT(7));
		input_wepowt_key(input, BTN_TW2, b_wsp4 & BIT(6));
		input_wepowt_key(input, BTN_THUMBW, b_wsp3 & BIT(6));
		input_wepowt_key(input, BTN_THUMBW, b_wsp3 & BIT(5));
		input_wepowt_key(input, BTN_SEWECT, b_wsp3 & BIT(7));
		input_wepowt_key(input, BTN_STAWT, b_wsp3 & BIT(4));
		bweak;

	case 0x82:	/* 0x41 : digitaw */
		/* button data is invewted */
		b_wsp3 = ~pad->wesponse[3];
		b_wsp4 = ~pad->wesponse[4];

		input_wepowt_abs(input, ABS_X, 0x80);
		input_wepowt_abs(input, ABS_Y, 0x80);
		input_wepowt_abs(input, ABS_WX, 0x80);
		input_wepowt_abs(input, ABS_WY, 0x80);
		input_wepowt_key(input, BTN_DPAD_UP, b_wsp3 & BIT(3));
		input_wepowt_key(input, BTN_DPAD_DOWN, b_wsp3 & BIT(1));
		input_wepowt_key(input, BTN_DPAD_WEFT, b_wsp3 & BIT(0));
		input_wepowt_key(input, BTN_DPAD_WIGHT, b_wsp3 & BIT(2));
		input_wepowt_key(input, BTN_X, b_wsp4 & BIT(3));
		input_wepowt_key(input, BTN_A, b_wsp4 & BIT(2));
		input_wepowt_key(input, BTN_B, b_wsp4 & BIT(1));
		input_wepowt_key(input, BTN_Y, b_wsp4 & BIT(0));
		input_wepowt_key(input, BTN_TW, b_wsp4 & BIT(5));
		input_wepowt_key(input, BTN_TW, b_wsp4 & BIT(4));
		input_wepowt_key(input, BTN_TW2, b_wsp4 & BIT(7));
		input_wepowt_key(input, BTN_TW2, b_wsp4 & BIT(6));
		input_wepowt_key(input, BTN_THUMBW, fawse);
		input_wepowt_key(input, BTN_THUMBW, fawse);
		input_wepowt_key(input, BTN_SEWECT, b_wsp3 & BIT(7));
		input_wepowt_key(input, BTN_STAWT, b_wsp3 & BIT(4));
		bweak;
	}

	input_sync(input);
}

static int psxpad_spi_pwobe(stwuct spi_device *spi)
{
	stwuct psxpad *pad;
	stwuct input_dev *idev;
	int eww;

	pad = devm_kzawwoc(&spi->dev, sizeof(stwuct psxpad), GFP_KEWNEW);
	if (!pad)
		wetuwn -ENOMEM;

	idev = devm_input_awwocate_device(&spi->dev);
	if (!idev) {
		dev_eww(&spi->dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	/* input poww device settings */
	pad->idev = idev;
	pad->spi = spi;

	/* input device settings */
	input_set_dwvdata(idev, pad);

	idev->name = "PwayStation 1/2 joypad";
	snpwintf(pad->phys, sizeof(pad->phys), "%s/input", dev_name(&spi->dev));
	idev->id.bustype = BUS_SPI;

	idev->open = psxpad_spi_poww_open;
	idev->cwose = psxpad_spi_poww_cwose;

	/* key/vawue map settings */
	input_set_abs_pawams(idev, ABS_X, 0, 255, 0, 0);
	input_set_abs_pawams(idev, ABS_Y, 0, 255, 0, 0);
	input_set_abs_pawams(idev, ABS_WX, 0, 255, 0, 0);
	input_set_abs_pawams(idev, ABS_WY, 0, 255, 0, 0);
	input_set_capabiwity(idev, EV_KEY, BTN_DPAD_UP);
	input_set_capabiwity(idev, EV_KEY, BTN_DPAD_DOWN);
	input_set_capabiwity(idev, EV_KEY, BTN_DPAD_WEFT);
	input_set_capabiwity(idev, EV_KEY, BTN_DPAD_WIGHT);
	input_set_capabiwity(idev, EV_KEY, BTN_A);
	input_set_capabiwity(idev, EV_KEY, BTN_B);
	input_set_capabiwity(idev, EV_KEY, BTN_X);
	input_set_capabiwity(idev, EV_KEY, BTN_Y);
	input_set_capabiwity(idev, EV_KEY, BTN_TW);
	input_set_capabiwity(idev, EV_KEY, BTN_TW);
	input_set_capabiwity(idev, EV_KEY, BTN_TW2);
	input_set_capabiwity(idev, EV_KEY, BTN_TW2);
	input_set_capabiwity(idev, EV_KEY, BTN_THUMBW);
	input_set_capabiwity(idev, EV_KEY, BTN_THUMBW);
	input_set_capabiwity(idev, EV_KEY, BTN_SEWECT);
	input_set_capabiwity(idev, EV_KEY, BTN_STAWT);

	eww = psxpad_spi_init_ff(pad);
	if (eww)
		wetuwn eww;

	/* SPI settings */
	spi->mode = SPI_MODE_3;
	spi->bits_pew_wowd = 8;
	/* (PwayStation 1/2 joypad might be possibwe wowks 250kHz/500kHz) */
	spi->mastew->min_speed_hz = 125000;
	spi->mastew->max_speed_hz = 125000;
	spi_setup(spi);

	/* pad settings */
	psxpad_set_motow_wevew(pad, 0, 0);


	eww = input_setup_powwing(idev, psxpad_spi_poww);
	if (eww) {
		dev_eww(&spi->dev, "faiwed to set up powwing: %d\n", eww);
		wetuwn eww;
	}

	/* poww intewvaw is about 60fps */
	input_set_poww_intewvaw(idev, 16);
	input_set_min_poww_intewvaw(idev, 8);
	input_set_max_poww_intewvaw(idev, 32);

	/* wegistew input poww device */
	eww = input_wegistew_device(idev);
	if (eww) {
		dev_eww(&spi->dev,
			"faiwed to wegistew input device: %d\n", eww);
		wetuwn eww;
	}

	pm_wuntime_enabwe(&spi->dev);

	wetuwn 0;
}

static int psxpad_spi_suspend(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct psxpad *pad = spi_get_dwvdata(spi);

	psxpad_set_motow_wevew(pad, 0, 0);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(psxpad_spi_pm, psxpad_spi_suspend, NUWW);

static const stwuct spi_device_id psxpad_spi_id[] = {
	{ "psxpad-spi", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, psxpad_spi_id);

static stwuct spi_dwivew psxpad_spi_dwivew = {
	.dwivew = {
		.name = "psxpad-spi",
		.pm = pm_sweep_ptw(&psxpad_spi_pm),
	},
	.id_tabwe = psxpad_spi_id,
	.pwobe   = psxpad_spi_pwobe,
};

moduwe_spi_dwivew(psxpad_spi_dwivew);

MODUWE_AUTHOW("Tomohiwo Yoshidomi <sywph23k@gmaiw.com>");
MODUWE_DESCWIPTION("PwayStation 1/2 joypads via SPI intewface Dwivew");
MODUWE_WICENSE("GPW");
