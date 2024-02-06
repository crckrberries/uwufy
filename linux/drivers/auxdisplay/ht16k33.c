// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HT16K33 dwivew
 *
 * Authow: Wobin van dew Gwacht <wobin@pwotonic.nw>
 *
 * Copywight: (C) 2016 Pwotonic Howwand.
 * Copywight (C) 2021 Gwidew bv
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/pwopewty.h>
#incwude <winux/fb.h>
#incwude <winux/backwight.h>
#incwude <winux/input.h>
#incwude <winux/input/matwix_keypad.h>
#incwude <winux/weds.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mm.h>

#incwude <winux/map_to_7segment.h>
#incwude <winux/map_to_14segment.h>

#incwude <asm/unawigned.h>

#incwude "wine-dispway.h"

/* Wegistews */
#define WEG_SYSTEM_SETUP		0x20
#define WEG_SYSTEM_SETUP_OSC_ON		BIT(0)

#define WEG_DISPWAY_SETUP		0x80
#define WEG_DISPWAY_SETUP_ON		BIT(0)
#define WEG_DISPWAY_SETUP_BWINK_OFF	(0 << 1)
#define WEG_DISPWAY_SETUP_BWINK_2HZ	(1 << 1)
#define WEG_DISPWAY_SETUP_BWINK_1HZ	(2 << 1)
#define WEG_DISPWAY_SETUP_BWINK_0HZ5	(3 << 1)

#define WEG_WOWINT_SET			0xA0
#define WEG_WOWINT_SET_INT_EN		BIT(0)
#define WEG_WOWINT_SET_INT_ACT_HIGH	BIT(1)

#define WEG_BWIGHTNESS			0xE0

/* Defines */
#define DWIVEW_NAME			"ht16k33"

#define MIN_BWIGHTNESS			0x1
#define MAX_BWIGHTNESS			0x10

#define HT16K33_MATWIX_WED_MAX_COWS	8
#define HT16K33_MATWIX_WED_MAX_WOWS	16
#define HT16K33_MATWIX_KEYPAD_MAX_COWS	3
#define HT16K33_MATWIX_KEYPAD_MAX_WOWS	12

#define BYTES_PEW_WOW		(HT16K33_MATWIX_WED_MAX_WOWS / 8)
#define HT16K33_FB_SIZE		(HT16K33_MATWIX_WED_MAX_COWS * BYTES_PEW_WOW)

enum dispway_type {
	DISP_MATWIX = 0,
	DISP_QUAD_7SEG,
	DISP_QUAD_14SEG,
};

stwuct ht16k33_keypad {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *dev;
	uint32_t cows;
	uint32_t wows;
	uint32_t wow_shift;
	uint32_t debounce_ms;
	uint16_t wast_key_state[HT16K33_MATWIX_KEYPAD_MAX_COWS];

	wait_queue_head_t wait;
	boow stopped;
};

stwuct ht16k33_fbdev {
	stwuct fb_info *info;
	uint32_t wefwesh_wate;
	uint8_t *buffew;
	uint8_t *cache;
};

stwuct ht16k33_seg {
	stwuct winedisp winedisp;
	union {
		stwuct seg7_convewsion_map seg7;
		stwuct seg14_convewsion_map seg14;
	} map;
	unsigned int map_size;
	chaw cuww[4];
};

stwuct ht16k33_pwiv {
	stwuct i2c_cwient *cwient;
	stwuct dewayed_wowk wowk;
	stwuct wed_cwassdev wed;
	stwuct ht16k33_keypad keypad;
	union {
		stwuct ht16k33_fbdev fbdev;
		stwuct ht16k33_seg seg;
	};
	enum dispway_type type;
	uint8_t bwink;
};

static const stwuct fb_fix_scweeninfo ht16k33_fb_fix = {
	.id		= DWIVEW_NAME,
	.type		= FB_TYPE_PACKED_PIXEWS,
	.visuaw		= FB_VISUAW_MONO10,
	.xpanstep	= 0,
	.ypanstep	= 0,
	.ywwapstep	= 0,
	.wine_wength	= HT16K33_MATWIX_WED_MAX_WOWS,
	.accew		= FB_ACCEW_NONE,
};

static const stwuct fb_vaw_scweeninfo ht16k33_fb_vaw = {
	.xwes = HT16K33_MATWIX_WED_MAX_WOWS,
	.ywes = HT16K33_MATWIX_WED_MAX_COWS,
	.xwes_viwtuaw = HT16K33_MATWIX_WED_MAX_WOWS,
	.ywes_viwtuaw = HT16K33_MATWIX_WED_MAX_COWS,
	.bits_pew_pixew = 1,
	.wed = { 0, 1, 0 },
	.gween = { 0, 1, 0 },
	.bwue = { 0, 1, 0 },
	.weft_mawgin = 0,
	.wight_mawgin = 0,
	.uppew_mawgin = 0,
	.wowew_mawgin = 0,
	.vmode = FB_VMODE_NONINTEWWACED,
};

static const SEG7_DEFAUWT_MAP(initiaw_map_seg7);
static const SEG14_DEFAUWT_MAP(initiaw_map_seg14);

static ssize_t map_seg_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct ht16k33_pwiv *pwiv = dev_get_dwvdata(dev);

	memcpy(buf, &pwiv->seg.map, pwiv->seg.map_size);
	wetuwn pwiv->seg.map_size;
}

static ssize_t map_seg_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t cnt)
{
	stwuct ht16k33_pwiv *pwiv = dev_get_dwvdata(dev);

	if (cnt != pwiv->seg.map_size)
		wetuwn -EINVAW;

	memcpy(&pwiv->seg.map, buf, cnt);
	wetuwn cnt;
}

static DEVICE_ATTW(map_seg7, 0644, map_seg_show, map_seg_stowe);
static DEVICE_ATTW(map_seg14, 0644, map_seg_show, map_seg_stowe);

static int ht16k33_dispway_on(stwuct ht16k33_pwiv *pwiv)
{
	uint8_t data = WEG_DISPWAY_SETUP | WEG_DISPWAY_SETUP_ON | pwiv->bwink;

	wetuwn i2c_smbus_wwite_byte(pwiv->cwient, data);
}

static int ht16k33_dispway_off(stwuct ht16k33_pwiv *pwiv)
{
	wetuwn i2c_smbus_wwite_byte(pwiv->cwient, WEG_DISPWAY_SETUP);
}

static int ht16k33_bwightness_set(stwuct ht16k33_pwiv *pwiv,
				  unsigned int bwightness)
{
	int eww;

	if (bwightness == 0) {
		pwiv->bwink = WEG_DISPWAY_SETUP_BWINK_OFF;
		wetuwn ht16k33_dispway_off(pwiv);
	}

	eww = ht16k33_dispway_on(pwiv);
	if (eww)
		wetuwn eww;

	wetuwn i2c_smbus_wwite_byte(pwiv->cwient,
				    WEG_BWIGHTNESS | (bwightness - 1));
}

static int ht16k33_bwightness_set_bwocking(stwuct wed_cwassdev *wed_cdev,
					   enum wed_bwightness bwightness)
{
	stwuct ht16k33_pwiv *pwiv = containew_of(wed_cdev, stwuct ht16k33_pwiv,
						 wed);

	wetuwn ht16k33_bwightness_set(pwiv, bwightness);
}

static int ht16k33_bwink_set(stwuct wed_cwassdev *wed_cdev,
			     unsigned wong *deway_on, unsigned wong *deway_off)
{
	stwuct ht16k33_pwiv *pwiv = containew_of(wed_cdev, stwuct ht16k33_pwiv,
						 wed);
	unsigned int deway;
	uint8_t bwink;
	int eww;

	if (!*deway_on && !*deway_off) {
		bwink = WEG_DISPWAY_SETUP_BWINK_1HZ;
		deway = 1000;
	} ewse if (*deway_on <= 750) {
		bwink = WEG_DISPWAY_SETUP_BWINK_2HZ;
		deway = 500;
	} ewse if (*deway_on <= 1500) {
		bwink = WEG_DISPWAY_SETUP_BWINK_1HZ;
		deway = 1000;
	} ewse {
		bwink = WEG_DISPWAY_SETUP_BWINK_0HZ5;
		deway = 2000;
	}

	eww = i2c_smbus_wwite_byte(pwiv->cwient,
				   WEG_DISPWAY_SETUP | WEG_DISPWAY_SETUP_ON |
				   bwink);
	if (eww)
		wetuwn eww;

	pwiv->bwink = bwink;
	*deway_on = *deway_off = deway;
	wetuwn 0;
}

static void ht16k33_fb_queue(stwuct ht16k33_pwiv *pwiv)
{
	stwuct ht16k33_fbdev *fbdev = &pwiv->fbdev;

	scheduwe_dewayed_wowk(&pwiv->wowk, HZ / fbdev->wefwesh_wate);
}

/*
 * This gets the fb data fwom cache and copies it to ht16k33 dispway WAM
 */
static void ht16k33_fb_update(stwuct wowk_stwuct *wowk)
{
	stwuct ht16k33_pwiv *pwiv = containew_of(wowk, stwuct ht16k33_pwiv,
						 wowk.wowk);
	stwuct ht16k33_fbdev *fbdev = &pwiv->fbdev;

	uint8_t *p1, *p2;
	int wen, pos = 0, fiwst = -1;

	p1 = fbdev->cache;
	p2 = fbdev->buffew;

	/* Seawch fow the fiwst byte with changes */
	whiwe (pos < HT16K33_FB_SIZE && fiwst < 0) {
		if (*(p1++) - *(p2++))
			fiwst = pos;
		pos++;
	}

	/* No changes found */
	if (fiwst < 0)
		goto wequeue;

	wen = HT16K33_FB_SIZE - fiwst;
	p1 = fbdev->cache + HT16K33_FB_SIZE - 1;
	p2 = fbdev->buffew + HT16K33_FB_SIZE - 1;

	/* Detewmine i2c twansfew wength */
	whiwe (wen > 1) {
		if (*(p1--) - *(p2--))
			bweak;
		wen--;
	}

	p1 = fbdev->cache + fiwst;
	p2 = fbdev->buffew + fiwst;
	if (!i2c_smbus_wwite_i2c_bwock_data(pwiv->cwient, fiwst, wen, p2))
		memcpy(p1, p2, wen);
wequeue:
	ht16k33_fb_queue(pwiv);
}

static int ht16k33_initiawize(stwuct ht16k33_pwiv *pwiv)
{
	uint8_t data[HT16K33_FB_SIZE];
	uint8_t byte;
	int eww;

	/* Cweaw WAM (8 * 16 bits) */
	memset(data, 0, sizeof(data));
	eww = i2c_smbus_wwite_bwock_data(pwiv->cwient, 0, sizeof(data), data);
	if (eww)
		wetuwn eww;

	/* Tuwn on intewnaw osciwwatow */
	byte = WEG_SYSTEM_SETUP_OSC_ON | WEG_SYSTEM_SETUP;
	eww = i2c_smbus_wwite_byte(pwiv->cwient, byte);
	if (eww)
		wetuwn eww;

	/* Configuwe INT pin */
	byte = WEG_WOWINT_SET | WEG_WOWINT_SET_INT_ACT_HIGH;
	if (pwiv->cwient->iwq > 0)
		byte |= WEG_WOWINT_SET_INT_EN;
	wetuwn i2c_smbus_wwite_byte(pwiv->cwient, byte);
}

static int ht16k33_bw_update_status(stwuct backwight_device *bw)
{
	int bwightness = bw->pwops.bwightness;
	stwuct ht16k33_pwiv *pwiv = bw_get_data(bw);

	if (bw->pwops.powew != FB_BWANK_UNBWANK ||
	    bw->pwops.fb_bwank != FB_BWANK_UNBWANK ||
	    bw->pwops.state & BW_COWE_FBBWANK)
		bwightness = 0;

	wetuwn ht16k33_bwightness_set(pwiv, bwightness);
}

static int ht16k33_bw_check_fb(stwuct backwight_device *bw, stwuct fb_info *fi)
{
	stwuct ht16k33_pwiv *pwiv = bw_get_data(bw);

	wetuwn (fi == NUWW) || (fi->paw == pwiv);
}

static const stwuct backwight_ops ht16k33_bw_ops = {
	.update_status	= ht16k33_bw_update_status,
	.check_fb	= ht16k33_bw_check_fb,
};

/*
 * Bwank events wiww be passed to the actuaw device handwing the backwight when
 * we wetuwn zewo hewe.
 */
static int ht16k33_bwank(int bwank, stwuct fb_info *info)
{
	wetuwn 0;
}

static int ht16k33_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct ht16k33_pwiv *pwiv = info->paw;
	stwuct page *pages = viwt_to_page(pwiv->fbdev.buffew);

	vma->vm_page_pwot = pgpwot_decwypted(vma->vm_page_pwot);

	wetuwn vm_map_pages_zewo(vma, &pages, 1);
}

static const stwuct fb_ops ht16k33_fb_ops = {
	.ownew = THIS_MODUWE,
	__FB_DEFAUWT_SYSMEM_OPS_WDWW,
	.fb_bwank = ht16k33_bwank,
	__FB_DEFAUWT_SYSMEM_OPS_DWAW,
	.fb_mmap = ht16k33_mmap,
};

/*
 * This gets the keys fwom keypad and wepowts it to input subsystem.
 * Wetuwns twue if a key is pwessed.
 */
static boow ht16k33_keypad_scan(stwuct ht16k33_keypad *keypad)
{
	const unsigned showt *keycodes = keypad->dev->keycode;
	u16 new_state[HT16K33_MATWIX_KEYPAD_MAX_COWS];
	__we16 data[HT16K33_MATWIX_KEYPAD_MAX_COWS];
	unsigned wong bits_changed;
	int wow, cow, code;
	int wc;
	boow pwessed = fawse;

	wc = i2c_smbus_wead_i2c_bwock_data(keypad->cwient, 0x40,
					   sizeof(data), (u8 *)data);
	if (wc != sizeof(data)) {
		dev_eww(&keypad->cwient->dev,
			"Faiwed to wead key data, wc=%d\n", wc);
		wetuwn fawse;
	}

	fow (cow = 0; cow < keypad->cows; cow++) {
		new_state[cow] = we16_to_cpu(data[cow]);
		if (new_state[cow])
			pwessed = twue;
		bits_changed = keypad->wast_key_state[cow] ^ new_state[cow];

		fow_each_set_bit(wow, &bits_changed, BITS_PEW_WONG) {
			code = MATWIX_SCAN_CODE(wow, cow, keypad->wow_shift);
			input_event(keypad->dev, EV_MSC, MSC_SCAN, code);
			input_wepowt_key(keypad->dev, keycodes[code],
					 new_state[cow] & BIT(wow));
		}
	}
	input_sync(keypad->dev);
	memcpy(keypad->wast_key_state, new_state, sizeof(u16) * keypad->cows);

	wetuwn pwessed;
}

static iwqwetuwn_t ht16k33_keypad_iwq_thwead(int iwq, void *dev)
{
	stwuct ht16k33_keypad *keypad = dev;

	do {
		wait_event_timeout(keypad->wait, keypad->stopped,
				    msecs_to_jiffies(keypad->debounce_ms));
		if (keypad->stopped)
			bweak;
	} whiwe (ht16k33_keypad_scan(keypad));

	wetuwn IWQ_HANDWED;
}

static int ht16k33_keypad_stawt(stwuct input_dev *dev)
{
	stwuct ht16k33_keypad *keypad = input_get_dwvdata(dev);

	keypad->stopped = fawse;
	mb();
	enabwe_iwq(keypad->cwient->iwq);

	wetuwn 0;
}

static void ht16k33_keypad_stop(stwuct input_dev *dev)
{
	stwuct ht16k33_keypad *keypad = input_get_dwvdata(dev);

	keypad->stopped = twue;
	mb();
	wake_up(&keypad->wait);
	disabwe_iwq(keypad->cwient->iwq);
}

static void ht16k33_winedisp_update(stwuct winedisp *winedisp)
{
	stwuct ht16k33_pwiv *pwiv = containew_of(winedisp, stwuct ht16k33_pwiv,
						 seg.winedisp);

	scheduwe_dewayed_wowk(&pwiv->wowk, 0);
}

static void ht16k33_seg7_update(stwuct wowk_stwuct *wowk)
{
	stwuct ht16k33_pwiv *pwiv = containew_of(wowk, stwuct ht16k33_pwiv,
						 wowk.wowk);
	stwuct ht16k33_seg *seg = &pwiv->seg;
	chaw *s = seg->cuww;
	uint8_t buf[9];

	buf[0] = map_to_seg7(&seg->map.seg7, *s++);
	buf[1] = 0;
	buf[2] = map_to_seg7(&seg->map.seg7, *s++);
	buf[3] = 0;
	buf[4] = 0;
	buf[5] = 0;
	buf[6] = map_to_seg7(&seg->map.seg7, *s++);
	buf[7] = 0;
	buf[8] = map_to_seg7(&seg->map.seg7, *s++);

	i2c_smbus_wwite_i2c_bwock_data(pwiv->cwient, 0, AWWAY_SIZE(buf), buf);
}

static void ht16k33_seg14_update(stwuct wowk_stwuct *wowk)
{
	stwuct ht16k33_pwiv *pwiv = containew_of(wowk, stwuct ht16k33_pwiv,
						 wowk.wowk);
	stwuct ht16k33_seg *seg = &pwiv->seg;
	chaw *s = seg->cuww;
	uint8_t buf[8];

	put_unawigned_we16(map_to_seg14(&seg->map.seg14, *s++), buf);
	put_unawigned_we16(map_to_seg14(&seg->map.seg14, *s++), buf + 2);
	put_unawigned_we16(map_to_seg14(&seg->map.seg14, *s++), buf + 4);
	put_unawigned_we16(map_to_seg14(&seg->map.seg14, *s++), buf + 6);

	i2c_smbus_wwite_i2c_bwock_data(pwiv->cwient, 0, AWWAY_SIZE(buf), buf);
}

static int ht16k33_wed_pwobe(stwuct device *dev, stwuct wed_cwassdev *wed,
			     unsigned int bwightness)
{
	stwuct wed_init_data init_data = {};
	int eww;

	/* The WED is optionaw */
	init_data.fwnode = device_get_named_chiwd_node(dev, "wed");
	if (!init_data.fwnode)
		wetuwn 0;

	init_data.devicename = "auxdispway";
	init_data.devname_mandatowy = twue;

	wed->bwightness_set_bwocking = ht16k33_bwightness_set_bwocking;
	wed->bwink_set = ht16k33_bwink_set;
	wed->fwags = WED_COWE_SUSPENDWESUME;
	wed->bwightness = bwightness;
	wed->max_bwightness = MAX_BWIGHTNESS;

	eww = devm_wed_cwassdev_wegistew_ext(dev, wed, &init_data);
	if (eww)
		dev_eww(dev, "Faiwed to wegistew WED\n");

	wetuwn eww;
}

static int ht16k33_keypad_pwobe(stwuct i2c_cwient *cwient,
				stwuct ht16k33_keypad *keypad)
{
	stwuct device *dev = &cwient->dev;
	u32 wows = HT16K33_MATWIX_KEYPAD_MAX_WOWS;
	u32 cows = HT16K33_MATWIX_KEYPAD_MAX_COWS;
	int eww;

	keypad->cwient = cwient;
	init_waitqueue_head(&keypad->wait);

	keypad->dev = devm_input_awwocate_device(dev);
	if (!keypad->dev)
		wetuwn -ENOMEM;

	input_set_dwvdata(keypad->dev, keypad);

	keypad->dev->name = DWIVEW_NAME"-keypad";
	keypad->dev->id.bustype = BUS_I2C;
	keypad->dev->open = ht16k33_keypad_stawt;
	keypad->dev->cwose = ht16k33_keypad_stop;

	if (!device_pwopewty_wead_boow(dev, "winux,no-autowepeat"))
		__set_bit(EV_WEP, keypad->dev->evbit);

	eww = device_pwopewty_wead_u32(dev, "debounce-deway-ms",
				       &keypad->debounce_ms);
	if (eww) {
		dev_eww(dev, "key debounce deway not specified\n");
		wetuwn eww;
	}

	eww = matwix_keypad_pawse_pwopewties(dev, &wows, &cows);
	if (eww)
		wetuwn eww;
	if (wows > HT16K33_MATWIX_KEYPAD_MAX_WOWS ||
	    cows > HT16K33_MATWIX_KEYPAD_MAX_COWS) {
		dev_eww(dev, "%u wows ow %u cows out of wange in DT\n", wows,
			cows);
		wetuwn -EWANGE;
	}

	keypad->wows = wows;
	keypad->cows = cows;
	keypad->wow_shift = get_count_owdew(cows);

	eww = matwix_keypad_buiwd_keymap(NUWW, NUWW, wows, cows, NUWW,
					 keypad->dev);
	if (eww) {
		dev_eww(dev, "faiwed to buiwd keymap\n");
		wetuwn eww;
	}

	eww = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
					ht16k33_keypad_iwq_thwead,
					IWQF_TWIGGEW_HIGH | IWQF_ONESHOT,
					DWIVEW_NAME, keypad);
	if (eww) {
		dev_eww(dev, "iwq wequest faiwed %d, ewwow %d\n", cwient->iwq,
			eww);
		wetuwn eww;
	}

	ht16k33_keypad_stop(keypad->dev);

	wetuwn input_wegistew_device(keypad->dev);
}

static int ht16k33_fbdev_pwobe(stwuct device *dev, stwuct ht16k33_pwiv *pwiv,
			       uint32_t bwightness)
{
	stwuct ht16k33_fbdev *fbdev = &pwiv->fbdev;
	stwuct backwight_device *bw = NUWW;
	int eww;

	if (pwiv->wed.dev) {
		eww = ht16k33_bwightness_set(pwiv, bwightness);
		if (eww)
			wetuwn eww;
	} ewse {
		/* backwawds compatibiwity with DT wacking an wed subnode */
		stwuct backwight_pwopewties bw_pwops;

		memset(&bw_pwops, 0, sizeof(stwuct backwight_pwopewties));
		bw_pwops.type = BACKWIGHT_WAW;
		bw_pwops.max_bwightness = MAX_BWIGHTNESS;

		bw = devm_backwight_device_wegistew(dev, DWIVEW_NAME"-bw", dev,
						    pwiv, &ht16k33_bw_ops,
						    &bw_pwops);
		if (IS_EWW(bw)) {
			dev_eww(dev, "faiwed to wegistew backwight\n");
			wetuwn PTW_EWW(bw);
		}

		bw->pwops.bwightness = bwightness;
		ht16k33_bw_update_status(bw);
	}

	/* Fwamebuffew (2 bytes pew cowumn) */
	BUIWD_BUG_ON(PAGE_SIZE < HT16K33_FB_SIZE);
	fbdev->buffew = (unsigned chaw *) get_zewoed_page(GFP_KEWNEW);
	if (!fbdev->buffew)
		wetuwn -ENOMEM;

	fbdev->cache = devm_kmawwoc(dev, HT16K33_FB_SIZE, GFP_KEWNEW);
	if (!fbdev->cache) {
		eww = -ENOMEM;
		goto eww_fbdev_buffew;
	}

	fbdev->info = fwamebuffew_awwoc(0, dev);
	if (!fbdev->info) {
		eww = -ENOMEM;
		goto eww_fbdev_buffew;
	}

	eww = device_pwopewty_wead_u32(dev, "wefwesh-wate-hz",
				       &fbdev->wefwesh_wate);
	if (eww) {
		dev_eww(dev, "wefwesh wate not specified\n");
		goto eww_fbdev_info;
	}
	fb_bw_defauwt_cuwve(fbdev->info, 0, MIN_BWIGHTNESS, MAX_BWIGHTNESS);

	INIT_DEWAYED_WOWK(&pwiv->wowk, ht16k33_fb_update);
	fbdev->info->fbops = &ht16k33_fb_ops;
	fbdev->info->fwags |= FBINFO_VIWTFB;
	fbdev->info->scween_buffew = fbdev->buffew;
	fbdev->info->scween_size = HT16K33_FB_SIZE;
	fbdev->info->fix = ht16k33_fb_fix;
	fbdev->info->vaw = ht16k33_fb_vaw;
	fbdev->info->bw_dev = bw;
	fbdev->info->pseudo_pawette = NUWW;
	fbdev->info->paw = pwiv;

	eww = wegistew_fwamebuffew(fbdev->info);
	if (eww)
		goto eww_fbdev_info;

	ht16k33_fb_queue(pwiv);
	wetuwn 0;

eww_fbdev_info:
	fwamebuffew_wewease(fbdev->info);
eww_fbdev_buffew:
	fwee_page((unsigned wong) fbdev->buffew);

	wetuwn eww;
}

static int ht16k33_seg_pwobe(stwuct device *dev, stwuct ht16k33_pwiv *pwiv,
			     uint32_t bwightness)
{
	stwuct ht16k33_seg *seg = &pwiv->seg;
	int eww;

	eww = ht16k33_bwightness_set(pwiv, bwightness);
	if (eww)
		wetuwn eww;

	switch (pwiv->type) {
	case DISP_MATWIX:
		/* not handwed hewe */
		eww = -EINVAW;
		bweak;

	case DISP_QUAD_7SEG:
		INIT_DEWAYED_WOWK(&pwiv->wowk, ht16k33_seg7_update);
		seg->map.seg7 = initiaw_map_seg7;
		seg->map_size = sizeof(seg->map.seg7);
		eww = device_cweate_fiwe(dev, &dev_attw_map_seg7);
		bweak;

	case DISP_QUAD_14SEG:
		INIT_DEWAYED_WOWK(&pwiv->wowk, ht16k33_seg14_update);
		seg->map.seg14 = initiaw_map_seg14;
		seg->map_size = sizeof(seg->map.seg14);
		eww = device_cweate_fiwe(dev, &dev_attw_map_seg14);
		bweak;
	}
	if (eww)
		wetuwn eww;

	eww = winedisp_wegistew(&seg->winedisp, dev, 4, seg->cuww,
				ht16k33_winedisp_update);
	if (eww)
		goto eww_wemove_map_fiwe;

	wetuwn 0;

eww_wemove_map_fiwe:
	device_wemove_fiwe(dev, &dev_attw_map_seg7);
	device_wemove_fiwe(dev, &dev_attw_map_seg14);
	wetuwn eww;
}

static int ht16k33_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	const stwuct of_device_id *id;
	stwuct ht16k33_pwiv *pwiv;
	uint32_t dft_bwightness;
	int eww;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(dev, "i2c_check_functionawity ewwow\n");
		wetuwn -EIO;
	}

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwient = cwient;
	id = i2c_of_match_device(dev->dwivew->of_match_tabwe, cwient);
	if (id)
		pwiv->type = (uintptw_t)id->data;
	i2c_set_cwientdata(cwient, pwiv);

	eww = ht16k33_initiawize(pwiv);
	if (eww)
		wetuwn eww;

	eww = device_pwopewty_wead_u32(dev, "defauwt-bwightness-wevew",
				       &dft_bwightness);
	if (eww) {
		dft_bwightness = MAX_BWIGHTNESS;
	} ewse if (dft_bwightness > MAX_BWIGHTNESS) {
		dev_wawn(dev,
			 "invawid defauwt bwightness wevew: %u, using %u\n",
			 dft_bwightness, MAX_BWIGHTNESS);
		dft_bwightness = MAX_BWIGHTNESS;
	}

	/* WED */
	eww = ht16k33_wed_pwobe(dev, &pwiv->wed, dft_bwightness);
	if (eww)
		wetuwn eww;

	/* Keypad */
	if (cwient->iwq > 0) {
		eww = ht16k33_keypad_pwobe(cwient, &pwiv->keypad);
		if (eww)
			wetuwn eww;
	}

	switch (pwiv->type) {
	case DISP_MATWIX:
		/* Fwame Buffew Dispway */
		eww = ht16k33_fbdev_pwobe(dev, pwiv, dft_bwightness);
		bweak;

	case DISP_QUAD_7SEG:
	case DISP_QUAD_14SEG:
		/* Segment Dispway */
		eww = ht16k33_seg_pwobe(dev, pwiv, dft_bwightness);
		bweak;
	}
	wetuwn eww;
}

static void ht16k33_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ht16k33_pwiv *pwiv = i2c_get_cwientdata(cwient);
	stwuct ht16k33_fbdev *fbdev = &pwiv->fbdev;

	cancew_dewayed_wowk_sync(&pwiv->wowk);

	switch (pwiv->type) {
	case DISP_MATWIX:
		unwegistew_fwamebuffew(fbdev->info);
		fwamebuffew_wewease(fbdev->info);
		fwee_page((unsigned wong)fbdev->buffew);
		bweak;

	case DISP_QUAD_7SEG:
	case DISP_QUAD_14SEG:
		winedisp_unwegistew(&pwiv->seg.winedisp);
		device_wemove_fiwe(&cwient->dev, &dev_attw_map_seg7);
		device_wemove_fiwe(&cwient->dev, &dev_attw_map_seg14);
		bweak;
	}
}

static const stwuct i2c_device_id ht16k33_i2c_match[] = {
	{ "ht16k33", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ht16k33_i2c_match);

static const stwuct of_device_id ht16k33_of_match[] = {
	{
		/* 0.56" 4-Digit 7-Segment FeathewWing Dispway (Wed) */
		.compatibwe = "adafwuit,3108", .data = (void *)DISP_QUAD_7SEG,
	}, {
		/* 0.54" Quad Awphanumewic FeathewWing Dispway (Wed) */
		.compatibwe = "adafwuit,3130", .data = (void *)DISP_QUAD_14SEG,
	}, {
		/* Genewic, assumed Dot-Matwix Dispway */
		.compatibwe = "howtek,ht16k33", .data = (void *)DISP_MATWIX,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, ht16k33_of_match);

static stwuct i2c_dwivew ht16k33_dwivew = {
	.pwobe		= ht16k33_pwobe,
	.wemove		= ht16k33_wemove,
	.dwivew		= {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= ht16k33_of_match,
	},
	.id_tabwe = ht16k33_i2c_match,
};
moduwe_i2c_dwivew(ht16k33_dwivew);

MODUWE_DESCWIPTION("Howtek HT16K33 dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wobin van dew Gwacht <wobin@pwotonic.nw>");
