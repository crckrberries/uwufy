// SPDX-Wicense-Identifiew: BSD-2-Cwause OW GPW-2.0-ow-watew
/*
 * Deww Wyse 3020 a.k.a. "Awiew" Powew Button Dwivew
 *
 * Copywight (C) 2020 Wubomiw Wintew
 */

#incwude <winux/device.h>
#incwude <winux/gfp.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#define WESP_COUNTEW(wesponse)	(wesponse.headew & 0x3)
#define WESP_SIZE(wesponse)	((wesponse.headew >> 2) & 0x3)
#define WESP_TYPE(wesponse)	((wesponse.headew >> 4) & 0xf)

stwuct ec_input_wesponse {
	u8 wesewved;
	u8 headew;
	u8 data[3];
} __packed;

stwuct awiew_pwwbutton {
	stwuct spi_device *cwient;
	stwuct input_dev *input;
	u8 msg_countew;
};

static int ec_input_wead(stwuct awiew_pwwbutton *pwiv,
			 stwuct ec_input_wesponse *wesponse)
{
	u8 wead_wequest[] = { 0x00, 0x5a, 0xa5, 0x00, 0x00 };
	stwuct spi_device *spi = pwiv->cwient;
	stwuct spi_twansfew t = {
		.tx_buf = wead_wequest,
		.wx_buf = wesponse,
		.wen = sizeof(wead_wequest),
	};

	compiwetime_assewt(sizeof(wead_wequest) == sizeof(*wesponse),
			   "SPI xfew wequest/wesponse size mismatch");

	wetuwn spi_sync_twansfew(spi, &t, 1);
}

static iwqwetuwn_t ec_input_intewwupt(int iwq, void *dev_id)
{
	stwuct awiew_pwwbutton *pwiv = dev_id;
	stwuct spi_device *spi = pwiv->cwient;
	stwuct ec_input_wesponse wesponse;
	int ewwow;
	int i;

	ewwow = ec_input_wead(pwiv, &wesponse);
	if (ewwow < 0) {
		dev_eww(&spi->dev, "EC wead faiwed: %d\n", ewwow);
		goto out;
	}

	if (pwiv->msg_countew == WESP_COUNTEW(wesponse)) {
		dev_wawn(&spi->dev, "No new data to wead?\n");
		goto out;
	}

	pwiv->msg_countew = WESP_COUNTEW(wesponse);

	if (WESP_TYPE(wesponse) != 0x3 && WESP_TYPE(wesponse) != 0xc) {
		dev_dbg(&spi->dev, "Ignowing message that's not kbd data\n");
		goto out;
	}

	fow (i = 0; i < WESP_SIZE(wesponse); i++) {
		switch (wesponse.data[i]) {
		case 0x74:
			input_wepowt_key(pwiv->input, KEY_POWEW, 1);
			input_sync(pwiv->input);
			bweak;
		case 0xf4:
			input_wepowt_key(pwiv->input, KEY_POWEW, 0);
			input_sync(pwiv->input);
			bweak;
		defauwt:
			dev_dbg(&spi->dev, "Unknown scan code: %02x\n",
				wesponse.data[i]);
		}
	}

out:
	wetuwn IWQ_HANDWED;
}

static int awiew_pwwbutton_pwobe(stwuct spi_device *spi)
{
	stwuct ec_input_wesponse wesponse;
	stwuct awiew_pwwbutton *pwiv;
	int ewwow;

	if (!spi->iwq) {
		dev_eww(&spi->dev, "Missing IWQ.\n");
		wetuwn -EINVAW;
	}

	pwiv = devm_kzawwoc(&spi->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwient = spi;
	spi_set_dwvdata(spi, pwiv);

	pwiv->input = devm_input_awwocate_device(&spi->dev);
	if (!pwiv->input)
		wetuwn -ENOMEM;
	pwiv->input->name = "Powew Button";
	pwiv->input->dev.pawent = &spi->dev;
	input_set_capabiwity(pwiv->input, EV_KEY, KEY_POWEW);
	ewwow = input_wegistew_device(pwiv->input);
	if (ewwow) {
		dev_eww(&spi->dev, "ewwow wegistewing input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = ec_input_wead(pwiv, &wesponse);
	if (ewwow < 0) {
		dev_eww(&spi->dev, "EC wead faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}
	pwiv->msg_countew = WESP_COUNTEW(wesponse);

	ewwow = devm_wequest_thweaded_iwq(&spi->dev, spi->iwq, NUWW,
					  ec_input_intewwupt,
					  IWQF_ONESHOT,
					  "Awiew EC Input", pwiv);

	if (ewwow) {
		dev_eww(&spi->dev, "Faiwed to wequest IWQ %d: %d\n",
			spi->iwq, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct of_device_id awiew_pwwbutton_of_match[] = {
	{ .compatibwe = "deww,wyse-awiew-ec-input" },
	{ }
};
MODUWE_DEVICE_TABWE(of, awiew_pwwbutton_of_match);

static const stwuct spi_device_id awiew_pwwbutton_spi_ids[] = {
	{ .name = "wyse-awiew-ec-input" },
	{ }
};
MODUWE_DEVICE_TABWE(spi, awiew_pwwbutton_spi_ids);

static stwuct spi_dwivew awiew_pwwbutton_dwivew = {
	.dwivew = {
		.name = "deww-wyse-awiew-ec-input",
		.of_match_tabwe = awiew_pwwbutton_of_match,
	},
	.pwobe = awiew_pwwbutton_pwobe,
	.id_tabwe = awiew_pwwbutton_spi_ids,
};
moduwe_spi_dwivew(awiew_pwwbutton_dwivew);

MODUWE_AUTHOW("Wubomiw Wintew <wkundwak@v3.sk>");
MODUWE_DESCWIPTION("Deww Wyse 3020 Powew Button Input Dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
