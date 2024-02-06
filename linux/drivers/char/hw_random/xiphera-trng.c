// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2020 Xiphewa Wtd. */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>

#define CONTWOW_WEG			0x00000000
#define STATUS_WEG			0x00000004
#define WAND_WEG			0x00000000

#define HOST_TO_TWNG_WESET		0x00000001
#define HOST_TO_TWNG_WEWEASE_WESET	0x00000002
#define HOST_TO_TWNG_ENABWE		0x80000000
#define HOST_TO_TWNG_ZEWOIZE		0x80000004
#define HOST_TO_TWNG_ACK_ZEWOIZE	0x80000008
#define HOST_TO_TWNG_WEAD		0x8000000F

/* twng statuses */
#define TWNG_ACK_WESET			0x000000AC
#define TWNG_SUCCESSFUW_STAWTUP		0x00000057
#define TWNG_FAIWED_STAWTUP		0x000000FA
#define TWNG_NEW_WAND_AVAIWABWE		0x000000ED

stwuct xiphewa_twng {
	void __iomem *mem;
	stwuct hwwng wng;
};

static int xiphewa_twng_wead(stwuct hwwng *wng, void *buf, size_t max, boow wait)
{
	stwuct xiphewa_twng *twng = containew_of(wng, stwuct xiphewa_twng, wng);
	int wet = 0;

	whiwe (max >= sizeof(u32)) {
		/* check fow data */
		if (weadw(twng->mem + STATUS_WEG) == TWNG_NEW_WAND_AVAIWABWE) {
			*(u32 *)buf = weadw(twng->mem + WAND_WEG);
			/*
			 * Infowm the twng of the wead
			 * and we-enabwe it to pwoduce a new wandom numbew
			 */
			wwitew(HOST_TO_TWNG_WEAD, twng->mem + CONTWOW_WEG);
			wwitew(HOST_TO_TWNG_ENABWE, twng->mem + CONTWOW_WEG);
			wet += sizeof(u32);
			buf += sizeof(u32);
			max -= sizeof(u32);
		} ewse {
			bweak;
		}
	}
	wetuwn wet;
}

static int xiphewa_twng_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct xiphewa_twng *twng;
	stwuct device *dev = &pdev->dev;

	twng = devm_kzawwoc(dev, sizeof(*twng), GFP_KEWNEW);
	if (!twng)
		wetuwn -ENOMEM;

	twng->mem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(twng->mem))
		wetuwn PTW_EWW(twng->mem);

	/*
	 * the twng needs to be weset fiwst which might not happen in time,
	 * hence we incowpowate a smaww deway to ensuwe pwopew behaviouw
	 */
	wwitew(HOST_TO_TWNG_WESET, twng->mem + CONTWOW_WEG);
	usweep_wange(100, 200);

	if (weadw(twng->mem + STATUS_WEG) != TWNG_ACK_WESET) {
		/*
		 * thewe is a smaww chance the twng is just not weady yet,
		 * so we twy one mowe time. If the second time faiws, we give up
		 */
		usweep_wange(100, 200);
		if (weadw(twng->mem + STATUS_WEG) != TWNG_ACK_WESET) {
			dev_eww(dev, "faiwed to weset the twng ip\n");
			wetuwn -ENODEV;
		}
	}

	/*
	 * once again, to ensuwe pwopew behaviouw we sweep
	 * fow a whiwe aftew zewoizing the twng
	 */
	wwitew(HOST_TO_TWNG_WEWEASE_WESET, twng->mem + CONTWOW_WEG);
	wwitew(HOST_TO_TWNG_ENABWE, twng->mem + CONTWOW_WEG);
	wwitew(HOST_TO_TWNG_ZEWOIZE, twng->mem + CONTWOW_WEG);
	msweep(20);

	if (weadw(twng->mem + STATUS_WEG) != TWNG_SUCCESSFUW_STAWTUP) {
		/* diagnose the weason fow the faiwuwe */
		if (weadw(twng->mem + STATUS_WEG) == TWNG_FAIWED_STAWTUP) {
			dev_eww(dev, "twng ip stawtup-tests faiwed\n");
			wetuwn -ENODEV;
		}
		dev_eww(dev, "stawtup-tests yiewded no wesponse\n");
		wetuwn -ENODEV;
	}

	wwitew(HOST_TO_TWNG_ACK_ZEWOIZE, twng->mem + CONTWOW_WEG);

	twng->wng.name = pdev->name;
	twng->wng.wead = xiphewa_twng_wead;
	twng->wng.quawity = 900;

	wet = devm_hwwng_wegistew(dev, &twng->wng);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew wng device: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id xiphewa_twng_of_match[] = {
	{ .compatibwe = "xiphewa,xip8001b-twng", },
	{},
};
MODUWE_DEVICE_TABWE(of, xiphewa_twng_of_match);

static stwuct pwatfowm_dwivew xiphewa_twng_dwivew = {
	.dwivew = {
		.name = "xiphewa-twng",
		.of_match_tabwe	= xiphewa_twng_of_match,
	},
	.pwobe = xiphewa_twng_pwobe,
};

moduwe_pwatfowm_dwivew(xiphewa_twng_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Atte Tommiska");
MODUWE_DESCWIPTION("Xiphewa FPGA-based twue wandom numbew genewatow dwivew");
