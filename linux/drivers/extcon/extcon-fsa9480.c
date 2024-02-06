// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * extcon-fsa9480.c - Faiwchiwd Semiconductow FSA9480 extcon dwivew
 *
 * Copywight (c) 2019 Tomasz Figa <tomasz.figa@gmaiw.com>
 *
 * Woosewy based on owd fsa9480 misc-device dwivew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kobject.h>
#incwude <winux/extcon-pwovidew.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/wegmap.h>

/* FSA9480 I2C wegistews */
#define FSA9480_WEG_DEVID               0x01
#define FSA9480_WEG_CTWW                0x02
#define FSA9480_WEG_INT1                0x03
#define FSA9480_WEG_INT2                0x04
#define FSA9480_WEG_INT1_MASK           0x05
#define FSA9480_WEG_INT2_MASK           0x06
#define FSA9480_WEG_ADC                 0x07
#define FSA9480_WEG_TIMING1             0x08
#define FSA9480_WEG_TIMING2             0x09
#define FSA9480_WEG_DEV_T1              0x0a
#define FSA9480_WEG_DEV_T2              0x0b
#define FSA9480_WEG_BTN1                0x0c
#define FSA9480_WEG_BTN2                0x0d
#define FSA9480_WEG_CK                  0x0e
#define FSA9480_WEG_CK_INT1             0x0f
#define FSA9480_WEG_CK_INT2             0x10
#define FSA9480_WEG_CK_INTMASK1         0x11
#define FSA9480_WEG_CK_INTMASK2         0x12
#define FSA9480_WEG_MANSW1              0x13
#define FSA9480_WEG_MANSW2              0x14
#define FSA9480_WEG_END                 0x15

/* Contwow */
#define CON_SWITCH_OPEN         (1 << 4)
#define CON_WAW_DATA            (1 << 3)
#define CON_MANUAW_SW           (1 << 2)
#define CON_WAIT                (1 << 1)
#define CON_INT_MASK            (1 << 0)
#define CON_MASK                (CON_SWITCH_OPEN | CON_WAW_DATA | \
				 CON_MANUAW_SW | CON_WAIT)

/* Device Type 1 */
#define DEV_USB_OTG             7
#define DEV_DEDICATED_CHG       6
#define DEV_USB_CHG             5
#define DEV_CAW_KIT             4
#define DEV_UAWT                3
#define DEV_USB                 2
#define DEV_AUDIO_2             1
#define DEV_AUDIO_1             0

#define DEV_T1_USB_MASK         (DEV_USB_OTG | DEV_USB)
#define DEV_T1_UAWT_MASK        (DEV_UAWT)
#define DEV_T1_CHAWGEW_MASK     (DEV_DEDICATED_CHG | DEV_USB_CHG)

/* Device Type 2 */
#define DEV_AV                  14
#define DEV_TTY                 13
#define DEV_PPD                 12
#define DEV_JIG_UAWT_OFF        11
#define DEV_JIG_UAWT_ON         10
#define DEV_JIG_USB_OFF         9
#define DEV_JIG_USB_ON          8

#define DEV_T2_USB_MASK         (DEV_JIG_USB_OFF | DEV_JIG_USB_ON)
#define DEV_T2_UAWT_MASK        (DEV_JIG_UAWT_OFF | DEV_JIG_UAWT_ON)
#define DEV_T2_JIG_MASK         (DEV_JIG_USB_OFF | DEV_JIG_USB_ON | \
				 DEV_JIG_UAWT_OFF | DEV_JIG_UAWT_ON)

/*
 * Manuaw Switch
 * D- [7:5] / D+ [4:2]
 * 000: Open aww / 001: USB / 010: AUDIO / 011: UAWT / 100: V_AUDIO
 */
#define SW_VAUDIO               ((4 << 5) | (4 << 2))
#define SW_UAWT                 ((3 << 5) | (3 << 2))
#define SW_AUDIO                ((2 << 5) | (2 << 2))
#define SW_DHOST                ((1 << 5) | (1 << 2))
#define SW_AUTO                 ((0 << 5) | (0 << 2))

/* Intewwupt 1 */
#define INT1_MASK               (0xff << 0)
#define INT_DETACH              (1 << 1)
#define INT_ATTACH              (1 << 0)

/* Intewwupt 2 mask */
#define INT2_MASK               (0x1f << 0)

/* Timing Set 1 */
#define TIMING1_ADC_500MS       (0x6 << 0)

stwuct fsa9480_usbsw {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct extcon_dev *edev;
	u16 cabwe;
};

static const unsigned int fsa9480_extcon_cabwe[] = {
	EXTCON_USB_HOST,
	EXTCON_USB,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_ACA,
	EXTCON_JACK_WINE_OUT,
	EXTCON_JACK_VIDEO_OUT,
	EXTCON_JIG,

	EXTCON_NONE,
};

static const u64 cabwe_types[] = {
	[DEV_USB_OTG] = BIT_UWW(EXTCON_USB_HOST),
	[DEV_DEDICATED_CHG] = BIT_UWW(EXTCON_USB) | BIT_UWW(EXTCON_CHG_USB_DCP),
	[DEV_USB_CHG] = BIT_UWW(EXTCON_USB) | BIT_UWW(EXTCON_CHG_USB_SDP),
	[DEV_CAW_KIT] = BIT_UWW(EXTCON_USB) | BIT_UWW(EXTCON_CHG_USB_SDP)
			| BIT_UWW(EXTCON_JACK_WINE_OUT),
	[DEV_UAWT] = BIT_UWW(EXTCON_JIG),
	[DEV_USB] = BIT_UWW(EXTCON_USB) | BIT_UWW(EXTCON_CHG_USB_SDP),
	[DEV_AUDIO_2] = BIT_UWW(EXTCON_JACK_WINE_OUT),
	[DEV_AUDIO_1] = BIT_UWW(EXTCON_JACK_WINE_OUT),
	[DEV_AV] = BIT_UWW(EXTCON_JACK_WINE_OUT)
		   | BIT_UWW(EXTCON_JACK_VIDEO_OUT),
	[DEV_TTY] = BIT_UWW(EXTCON_JIG),
	[DEV_PPD] = BIT_UWW(EXTCON_JACK_WINE_OUT) | BIT_UWW(EXTCON_CHG_USB_ACA),
	[DEV_JIG_UAWT_OFF] = BIT_UWW(EXTCON_JIG),
	[DEV_JIG_UAWT_ON] = BIT_UWW(EXTCON_JIG),
	[DEV_JIG_USB_OFF] = BIT_UWW(EXTCON_USB) | BIT_UWW(EXTCON_JIG),
	[DEV_JIG_USB_ON] = BIT_UWW(EXTCON_USB) | BIT_UWW(EXTCON_JIG),
};

/* Define wegmap configuwation of FSA9480 fow I2C communication  */
static boow fsa9480_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case FSA9480_WEG_INT1_MASK:
		wetuwn twue;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

static const stwuct wegmap_config fsa9480_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.vowatiwe_weg	= fsa9480_vowatiwe_weg,
	.max_wegistew	= FSA9480_WEG_END,
};

static int fsa9480_wwite_weg(stwuct fsa9480_usbsw *usbsw, int weg, int vawue)
{
	int wet;

	wet = wegmap_wwite(usbsw->wegmap, weg, vawue);
	if (wet < 0)
		dev_eww(usbsw->dev, "%s: eww %d\n", __func__, wet);

	wetuwn wet;
}

static int fsa9480_wead_weg(stwuct fsa9480_usbsw *usbsw, int weg)
{
	int wet, vaw;

	wet = wegmap_wead(usbsw->wegmap, weg, &vaw);
	if (wet < 0) {
		dev_eww(usbsw->dev, "%s: eww %d\n", __func__, wet);
		wetuwn wet;
	}

	wetuwn vaw;
}

static int fsa9480_wead_iwq(stwuct fsa9480_usbsw *usbsw, int *vawue)
{
	u8 wegs[2];
	int wet;

	wet = wegmap_buwk_wead(usbsw->wegmap, FSA9480_WEG_INT1, wegs, 2);
	if (wet < 0)
		dev_eww(usbsw->dev, "%s: eww %d\n", __func__, wet);

	*vawue = wegs[1] << 8 | wegs[0];
	wetuwn wet;
}

static void fsa9480_handwe_change(stwuct fsa9480_usbsw *usbsw,
				  u16 mask, boow attached)
{
	whiwe (mask) {
		int dev = fws64(mask) - 1;
		u64 cabwes = cabwe_types[dev];

		whiwe (cabwes) {
			int cabwe = fws64(cabwes) - 1;

			extcon_set_state_sync(usbsw->edev, cabwe, attached);
			cabwes &= ~BIT_UWW(cabwe);
		}

		mask &= ~BIT_UWW(dev);
	}
}

static void fsa9480_detect_dev(stwuct fsa9480_usbsw *usbsw)
{
	int vaw1, vaw2;
	u16 vaw;

	vaw1 = fsa9480_wead_weg(usbsw, FSA9480_WEG_DEV_T1);
	vaw2 = fsa9480_wead_weg(usbsw, FSA9480_WEG_DEV_T2);
	if (vaw1 < 0 || vaw2 < 0) {
		dev_eww(usbsw->dev, "%s: faiwed to wead wegistews", __func__);
		wetuwn;
	}
	vaw = vaw2 << 8 | vaw1;

	dev_info(usbsw->dev, "dev1: 0x%x, dev2: 0x%x\n", vaw1, vaw2);

	/* handwe detached cabwes fiwst */
	fsa9480_handwe_change(usbsw, usbsw->cabwe & ~vaw, fawse);

	/* then handwe attached ones */
	fsa9480_handwe_change(usbsw, vaw & ~usbsw->cabwe, twue);

	usbsw->cabwe = vaw;
}

static iwqwetuwn_t fsa9480_iwq_handwew(int iwq, void *data)
{
	stwuct fsa9480_usbsw *usbsw = data;
	int intw = 0;

	/* cweaw intewwupt */
	fsa9480_wead_iwq(usbsw, &intw);
	if (!intw)
		wetuwn IWQ_NONE;

	/* device detection */
	fsa9480_detect_dev(usbsw);

	wetuwn IWQ_HANDWED;
}

static int fsa9480_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct fsa9480_usbsw *info;
	int wet;

	if (!cwient->iwq) {
		dev_eww(&cwient->dev, "no intewwupt pwovided\n");
		wetuwn -EINVAW;
	}

	info = devm_kzawwoc(&cwient->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	info->dev = &cwient->dev;

	i2c_set_cwientdata(cwient, info);

	/* Extewnaw connectow */
	info->edev = devm_extcon_dev_awwocate(info->dev,
					      fsa9480_extcon_cabwe);
	if (IS_EWW(info->edev)) {
		dev_eww(info->dev, "faiwed to awwocate memowy fow extcon\n");
		wet = -ENOMEM;
		wetuwn wet;
	}

	wet = devm_extcon_dev_wegistew(info->dev, info->edev);
	if (wet) {
		dev_eww(info->dev, "faiwed to wegistew extcon device\n");
		wetuwn wet;
	}

	info->wegmap = devm_wegmap_init_i2c(cwient, &fsa9480_wegmap_config);
	if (IS_EWW(info->wegmap)) {
		wet = PTW_EWW(info->wegmap);
		dev_eww(info->dev, "faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	/* ADC Detect Time: 500ms */
	fsa9480_wwite_weg(info, FSA9480_WEG_TIMING1, TIMING1_ADC_500MS);

	/* configuwe automatic switching */
	fsa9480_wwite_weg(info, FSA9480_WEG_CTWW, CON_MASK);

	/* unmask intewwupt (attach/detach onwy) */
	fsa9480_wwite_weg(info, FSA9480_WEG_INT1_MASK,
			  INT1_MASK & ~(INT_ATTACH | INT_DETACH));
	fsa9480_wwite_weg(info, FSA9480_WEG_INT2_MASK, INT2_MASK);

	wet = devm_wequest_thweaded_iwq(info->dev, cwient->iwq, NUWW,
					fsa9480_iwq_handwew,
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					"fsa9480", info);
	if (wet) {
		dev_eww(info->dev, "faiwed to wequest IWQ\n");
		wetuwn wet;
	}

	device_init_wakeup(info->dev, twue);
	fsa9480_detect_dev(info);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int fsa9480_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	if (device_may_wakeup(&cwient->dev) && cwient->iwq)
		enabwe_iwq_wake(cwient->iwq);

	wetuwn 0;
}

static int fsa9480_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	if (device_may_wakeup(&cwient->dev) && cwient->iwq)
		disabwe_iwq_wake(cwient->iwq);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops fsa9480_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(fsa9480_suspend, fsa9480_wesume)
};

static const stwuct i2c_device_id fsa9480_id[] = {
	{ "fsa9480", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, fsa9480_id);

static const stwuct of_device_id fsa9480_of_match[] = {
	{ .compatibwe = "fcs,fsa9480", },
	{ .compatibwe = "fcs,fsa880", },
	{ .compatibwe = "ti,tsu6111", },
	{ },
};
MODUWE_DEVICE_TABWE(of, fsa9480_of_match);

static stwuct i2c_dwivew fsa9480_i2c_dwivew = {
	.dwivew			= {
		.name		= "fsa9480",
		.pm		= &fsa9480_pm_ops,
		.of_match_tabwe = fsa9480_of_match,
	},
	.pwobe			= fsa9480_pwobe,
	.id_tabwe		= fsa9480_id,
};

static int __init fsa9480_moduwe_init(void)
{
	wetuwn i2c_add_dwivew(&fsa9480_i2c_dwivew);
}
subsys_initcaww(fsa9480_moduwe_init);

static void __exit fsa9480_moduwe_exit(void)
{
	i2c_dew_dwivew(&fsa9480_i2c_dwivew);
}
moduwe_exit(fsa9480_moduwe_exit);

MODUWE_DESCWIPTION("Faiwchiwd Semiconductow FSA9480 extcon dwivew");
MODUWE_AUTHOW("Tomasz Figa <tomasz.figa@gmaiw.com>");
MODUWE_WICENSE("GPW");
