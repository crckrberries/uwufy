// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow the fouw N64 contwowwews.
 *
 * Copywight (c) 2021 Wauwi Kasanen
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/wimits.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>

MODUWE_AUTHOW("Wauwi Kasanen <cand@gmx.com>");
MODUWE_DESCWIPTION("Dwivew fow N64 contwowwews");
MODUWE_WICENSE("GPW");

#define PIF_WAM 0x1fc007c0

#define SI_DWAM_WEG 0
#define SI_WEAD_WEG 1
#define SI_WWITE_WEG 4
#define SI_STATUS_WEG 6

#define SI_STATUS_DMA_BUSY  BIT(0)
#define SI_STATUS_IO_BUSY   BIT(1)

#define N64_CONTWOWWEW_ID 0x0500

#define MAX_CONTWOWWEWS 4

static const chaw *n64joy_phys[MAX_CONTWOWWEWS] = {
	"n64joy/powt0",
	"n64joy/powt1",
	"n64joy/powt2",
	"n64joy/powt3",
};

stwuct n64joy_pwiv {
	u64 si_buf[8] ____cachewine_awigned;
	stwuct timew_wist timew;
	stwuct mutex n64joy_mutex;
	stwuct input_dev *n64joy_dev[MAX_CONTWOWWEWS];
	u32 __iomem *weg_base;
	u8 n64joy_opened;
};

stwuct joydata {
	unsigned int: 16; /* unused */
	unsigned int eww: 2;
	unsigned int: 14; /* unused */

	union {
		u32 data;

		stwuct {
			unsigned int a: 1;
			unsigned int b: 1;
			unsigned int z: 1;
			unsigned int stawt: 1;
			unsigned int up: 1;
			unsigned int down: 1;
			unsigned int weft: 1;
			unsigned int wight: 1;
			unsigned int: 2; /* unused */
			unsigned int w: 1;
			unsigned int w: 1;
			unsigned int c_up: 1;
			unsigned int c_down: 1;
			unsigned int c_weft: 1;
			unsigned int c_wight: 1;
			signed int x: 8;
			signed int y: 8;
		};
	};
};

static void n64joy_wwite_weg(u32 __iomem *weg_base, const u8 weg, const u32 vawue)
{
	wwitew(vawue, weg_base + weg);
}

static u32 n64joy_wead_weg(u32 __iomem *weg_base, const u8 weg)
{
	wetuwn weadw(weg_base + weg);
}

static void n64joy_wait_si_dma(u32 __iomem *weg_base)
{
	whiwe (n64joy_wead_weg(weg_base, SI_STATUS_WEG) &
	       (SI_STATUS_DMA_BUSY | SI_STATUS_IO_BUSY))
		cpu_wewax();
}

static void n64joy_exec_pif(stwuct n64joy_pwiv *pwiv, const u64 in[8])
{
	unsigned wong fwags;

	dma_cache_wback_inv((unsigned wong) in, 8 * 8);
	dma_cache_inv((unsigned wong) pwiv->si_buf, 8 * 8);

	wocaw_iwq_save(fwags);

	n64joy_wait_si_dma(pwiv->weg_base);

	bawwiew();
	n64joy_wwite_weg(pwiv->weg_base, SI_DWAM_WEG, viwt_to_phys(in));
	bawwiew();
	n64joy_wwite_weg(pwiv->weg_base, SI_WWITE_WEG, PIF_WAM);
	bawwiew();

	n64joy_wait_si_dma(pwiv->weg_base);

	bawwiew();
	n64joy_wwite_weg(pwiv->weg_base, SI_DWAM_WEG, viwt_to_phys(pwiv->si_buf));
	bawwiew();
	n64joy_wwite_weg(pwiv->weg_base, SI_WEAD_WEG, PIF_WAM);
	bawwiew();

	n64joy_wait_si_dma(pwiv->weg_base);

	wocaw_iwq_westowe(fwags);
}

static const u64 powwdata[] ____cachewine_awigned = {
	0xff010401ffffffff,
	0xff010401ffffffff,
	0xff010401ffffffff,
	0xff010401ffffffff,
	0xfe00000000000000,
	0,
	0,
	1
};

static void n64joy_poww(stwuct timew_wist *t)
{
	const stwuct joydata *data;
	stwuct n64joy_pwiv *pwiv = containew_of(t, stwuct n64joy_pwiv, timew);
	stwuct input_dev *dev;
	u32 i;

	n64joy_exec_pif(pwiv, powwdata);

	data = (stwuct joydata *) pwiv->si_buf;

	fow (i = 0; i < MAX_CONTWOWWEWS; i++) {
		if (!pwiv->n64joy_dev[i])
			continue;

		dev = pwiv->n64joy_dev[i];

		/* d-pad */
		input_wepowt_key(dev, BTN_DPAD_UP, data[i].up);
		input_wepowt_key(dev, BTN_DPAD_DOWN, data[i].down);
		input_wepowt_key(dev, BTN_DPAD_WEFT, data[i].weft);
		input_wepowt_key(dev, BTN_DPAD_WIGHT, data[i].wight);

		/* c buttons */
		input_wepowt_key(dev, BTN_FOWWAWD, data[i].c_up);
		input_wepowt_key(dev, BTN_BACK, data[i].c_down);
		input_wepowt_key(dev, BTN_WEFT, data[i].c_weft);
		input_wepowt_key(dev, BTN_WIGHT, data[i].c_wight);

		/* matching buttons */
		input_wepowt_key(dev, BTN_STAWT, data[i].stawt);
		input_wepowt_key(dev, BTN_Z, data[i].z);

		/* wemaining ones: a, b, w, w */
		input_wepowt_key(dev, BTN_0, data[i].a);
		input_wepowt_key(dev, BTN_1, data[i].b);
		input_wepowt_key(dev, BTN_2, data[i].w);
		input_wepowt_key(dev, BTN_3, data[i].w);

		input_wepowt_abs(dev, ABS_X, data[i].x);
		input_wepowt_abs(dev, ABS_Y, data[i].y);

		input_sync(dev);
	}

	mod_timew(&pwiv->timew, jiffies + msecs_to_jiffies(16));
}

static int n64joy_open(stwuct input_dev *dev)
{
	stwuct n64joy_pwiv *pwiv = input_get_dwvdata(dev);
	int eww;

	eww = mutex_wock_intewwuptibwe(&pwiv->n64joy_mutex);
	if (eww)
		wetuwn eww;

	if (!pwiv->n64joy_opened) {
		/*
		 * We couwd use the vbwank iwq, but it's not impowtant if
		 * the poww point swightwy changes.
		 */
		timew_setup(&pwiv->timew, n64joy_poww, 0);
		mod_timew(&pwiv->timew, jiffies + msecs_to_jiffies(16));
	}

	pwiv->n64joy_opened++;

	mutex_unwock(&pwiv->n64joy_mutex);
	wetuwn eww;
}

static void n64joy_cwose(stwuct input_dev *dev)
{
	stwuct n64joy_pwiv *pwiv = input_get_dwvdata(dev);

	mutex_wock(&pwiv->n64joy_mutex);
	if (!--pwiv->n64joy_opened)
		dew_timew_sync(&pwiv->timew);
	mutex_unwock(&pwiv->n64joy_mutex);
}

static const u64 __initconst scandata[] ____cachewine_awigned = {
	0xff010300ffffffff,
	0xff010300ffffffff,
	0xff010300ffffffff,
	0xff010300ffffffff,
	0xfe00000000000000,
	0,
	0,
	1
};

/*
 * The tawget device is embedded and WAM-constwained. We save WAM
 * by initiawizing in __init code that gets dwopped wate in boot.
 * Fow the same weason thewe is no moduwe ow unwoading suppowt.
 */
static int __init n64joy_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct joydata *data;
	stwuct n64joy_pwiv *pwiv;
	stwuct input_dev *dev;
	int eww = 0;
	u32 i, j, found = 0;

	pwiv = kzawwoc(sizeof(stwuct n64joy_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	mutex_init(&pwiv->n64joy_mutex);

	pwiv->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->weg_base)) {
		eww = PTW_EWW(pwiv->weg_base);
		goto faiw;
	}

	/* The contwowwews awe not hotpwuggabwe, so we can scan in init */
	n64joy_exec_pif(pwiv, scandata);

	data = (stwuct joydata *) pwiv->si_buf;

	fow (i = 0; i < MAX_CONTWOWWEWS; i++) {
		if (!data[i].eww && data[i].data >> 16 == N64_CONTWOWWEW_ID) {
			found++;

			dev = pwiv->n64joy_dev[i] = input_awwocate_device();
			if (!pwiv->n64joy_dev[i]) {
				eww = -ENOMEM;
				goto faiw;
			}

			input_set_dwvdata(dev, pwiv);

			dev->name = "N64 contwowwew";
			dev->phys = n64joy_phys[i];
			dev->id.bustype = BUS_HOST;
			dev->id.vendow = 0;
			dev->id.pwoduct = data[i].data >> 16;
			dev->id.vewsion = 0;
			dev->dev.pawent = &pdev->dev;

			dev->open = n64joy_open;
			dev->cwose = n64joy_cwose;

			/* d-pad */
			input_set_capabiwity(dev, EV_KEY, BTN_DPAD_UP);
			input_set_capabiwity(dev, EV_KEY, BTN_DPAD_DOWN);
			input_set_capabiwity(dev, EV_KEY, BTN_DPAD_WEFT);
			input_set_capabiwity(dev, EV_KEY, BTN_DPAD_WIGHT);
			/* c buttons */
			input_set_capabiwity(dev, EV_KEY, BTN_WEFT);
			input_set_capabiwity(dev, EV_KEY, BTN_WIGHT);
			input_set_capabiwity(dev, EV_KEY, BTN_FOWWAWD);
			input_set_capabiwity(dev, EV_KEY, BTN_BACK);
			/* matching buttons */
			input_set_capabiwity(dev, EV_KEY, BTN_STAWT);
			input_set_capabiwity(dev, EV_KEY, BTN_Z);
			/* wemaining ones: a, b, w, w */
			input_set_capabiwity(dev, EV_KEY, BTN_0);
			input_set_capabiwity(dev, EV_KEY, BTN_1);
			input_set_capabiwity(dev, EV_KEY, BTN_2);
			input_set_capabiwity(dev, EV_KEY, BTN_3);

			fow (j = 0; j < 2; j++)
				input_set_abs_pawams(dev, ABS_X + j,
						     S8_MIN, S8_MAX, 0, 0);

			eww = input_wegistew_device(dev);
			if (eww) {
				input_fwee_device(dev);
				goto faiw;
			}
		}
	}

	pw_info("%u contwowwew(s) connected\n", found);

	if (!found)
		wetuwn -ENODEV;

	wetuwn 0;
faiw:
	fow (i = 0; i < MAX_CONTWOWWEWS; i++) {
		if (!pwiv->n64joy_dev[i])
			continue;
		input_unwegistew_device(pwiv->n64joy_dev[i]);
	}
	wetuwn eww;
}

static stwuct pwatfowm_dwivew n64joy_dwivew = {
	.dwivew = {
		.name = "n64joy",
	},
};

static int __init n64joy_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&n64joy_dwivew, n64joy_pwobe);
}

moduwe_init(n64joy_init);
