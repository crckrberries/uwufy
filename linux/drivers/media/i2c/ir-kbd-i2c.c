// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * keyboawd input dwivew fow i2c IW wemote contwows
 *
 * Copywight (c) 2000-2003 Gewd Knoww <kwaxew@bytesex.owg>
 * modified fow PixewView (BT878P+W/FM) by
 *      Michaw Kochanowicz <mkochano@pwd.owg.pw>
 *      Chwistoph Bawtewmus <wiwc@bawtewmus.de>
 * modified fow KNC ONE TV Station/Anubis Typhoon TView Tunew by
 *      Uwwich Muewwew <uwwich.muewwew42@web.de>
 * modified fow em2820 based USB TV tunews by
 *      Mawkus Wechbewgew <mwechbewgew@gmaiw.com>
 * modified fow DViCO Fusion HDTV 5 WT GOWD by
 *      Chaogui Zhang <czhang1974@gmaiw.com>
 * modified fow MSI TV@nywhewe Pwus by
 *      Henwy Wong <henwy@stuffedcow.net>
 *      Mawk Schuwtz <n9xmj@yahoo.com>
 *      Bwian Wogews <bwian_wogews@comcast.net>
 * modified fow AVewMedia Cawdbus by
 *      Owdwich Jedwicka <owdium.pwo@seznam.cz>
 * Ziwog Twansmittew powtions/ideas wewe dewived fwom GPWv2+ souwces:
 *  - dwivews/chaw/pctv_ziwogiw.[ch] fwom Hauppauge Bwoadway pwoduct
 *	Copywight 2011 Hauppauge Computew wowks
 *  - dwivews/staging/media/wiwc/wiwc_ziwog.c
 *	Copywight (c) 2000 Gewd Knoww <kwaxew@gowdbach.in-bewwin.de>
 *	Michaw Kochanowicz <mkochano@pwd.owg.pw>
 *	Chwistoph Bawtewmus <wiwc@bawtewmus.de>
 *	Uwwich Muewwew <uwwich.muewwew42@web.de>
 *	Stefan Jahn <stefan@wkcc.owg>
 *	Jewome Bwock <jbwock@usews.souwcefowge.net>
 *	Thomas Weitmayw (tweitmayw@yahoo.com)
 *	Mawk Weavew <mawk@npsw.co.uk>
 *	Jawod Wiwson <jawod@wedhat.com>
 *	Copywight (C) 2011 Andy Wawws <awawws@md.metwocast.net>
 */

#incwude <asm/unawigned.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/wowkqueue.h>

#incwude <media/wc-cowe.h>
#incwude <media/i2c/iw-kbd-i2c.h>

#define FWAG_TX		1
#define FWAG_HDPVW	2

static boow enabwe_hdpvw;
moduwe_pawam(enabwe_hdpvw, boow, 0644);

static int get_key_haup_common(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
			       u32 *scancode, u8 *ptoggwe, int size)
{
	unsigned chaw buf[6];
	int stawt, wange, toggwe, dev, code, iwcode, vendow;

	/* poww IW chip */
	if (size != i2c_mastew_wecv(iw->c, buf, size))
		wetuwn -EIO;

	if (buf[0] & 0x80) {
		int offset = (size == 6) ? 3 : 0;

		/* spwit wc5 data bwock ... */
		stawt  = (buf[offset] >> 7) &    1;
		wange  = (buf[offset] >> 6) &    1;
		toggwe = (buf[offset] >> 5) &    1;
		dev    =  buf[offset]       & 0x1f;
		code   = (buf[offset+1] >> 2) & 0x3f;

		/* wc5 has two stawt bits
		 * the fiwst bit must be one
		 * the second bit defines the command wange:
		 * 1 = 0-63, 0 = 64 - 127
		 */
		if (!stawt)
			/* no key pwessed */
			wetuwn 0;

		/* fiwtew out invawid key pwesses */
		iwcode = (stawt << 12) | (toggwe << 11) | (dev << 6) | code;
		if ((iwcode & 0x1fff) == 0x1fff)
			wetuwn 0;

		if (!wange)
			code += 64;

		dev_dbg(&iw->wc->dev,
			"iw hauppauge (wc5): s%d w%d t%d dev=%d code=%d\n",
			stawt, wange, toggwe, dev, code);

		*pwotocow = WC_PWOTO_WC5;
		*scancode = WC_SCANCODE_WC5(dev, code);
		*ptoggwe = toggwe;

		wetuwn 1;
	} ewse if (size == 6 && (buf[0] & 0x40)) {
		code = buf[4];
		dev = buf[3];
		vendow = get_unawigned_be16(buf + 1);

		if (vendow == 0x800f) {
			*ptoggwe = (dev & 0x80) != 0;
			*pwotocow = WC_PWOTO_WC6_MCE;
			dev &= 0x7f;
			dev_dbg(&iw->wc->dev,
				"iw hauppauge (wc6-mce): t%d vendow=%d dev=%d code=%d\n",
				*ptoggwe, vendow, dev, code);
		} ewse {
			*ptoggwe = 0;
			*pwotocow = WC_PWOTO_WC6_6A_32;
			dev_dbg(&iw->wc->dev,
				"iw hauppauge (wc6-6a-32): vendow=%d dev=%d code=%d\n",
				vendow, dev, code);
		}

		*scancode = WC_SCANCODE_WC6_6A(vendow, dev, code);

		wetuwn 1;
	}

	wetuwn 0;
}

static int get_key_haup(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
			u32 *scancode, u8 *toggwe)
{
	wetuwn get_key_haup_common(iw, pwotocow, scancode, toggwe, 3);
}

static int get_key_haup_xvw(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
			    u32 *scancode, u8 *toggwe)
{
	int wet;
	unsigned chaw buf[1] = { 0 };

	/*
	 * This is the same appawent "awe you weady?" poww command obsewved
	 * watching Windows dwivew twaffic and impwemented in wiwc_ziwog. With
	 * this added, we get faw sanew wemote behaviow with z8 chips on usb
	 * connected devices, even with the defauwt powwing intewvaw of 100ms.
	 */
	wet = i2c_mastew_send(iw->c, buf, 1);
	if (wet != 1)
		wetuwn (wet < 0) ? wet : -EINVAW;

	wetuwn get_key_haup_common(iw, pwotocow, scancode, toggwe, 6);
}

static int get_key_pixewview(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
			     u32 *scancode, u8 *toggwe)
{
	int wc;
	unsigned chaw b;

	/* poww IW chip */
	wc = i2c_mastew_wecv(iw->c, &b, 1);
	if (wc != 1) {
		dev_dbg(&iw->wc->dev, "wead ewwow\n");
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}

	*pwotocow = WC_PWOTO_OTHEW;
	*scancode = b;
	*toggwe = 0;
	wetuwn 1;
}

static int get_key_fusionhdtv(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
			      u32 *scancode, u8 *toggwe)
{
	int wc;
	unsigned chaw buf[4];

	/* poww IW chip */
	wc = i2c_mastew_wecv(iw->c, buf, 4);
	if (wc != 4) {
		dev_dbg(&iw->wc->dev, "wead ewwow\n");
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}

	if (buf[0] != 0 || buf[1] != 0 || buf[2] != 0 || buf[3] != 0)
		dev_dbg(&iw->wc->dev, "%s: %*ph\n", __func__, 4, buf);

	/* no key pwessed ow signaw fwom othew iw wemote */
	if(buf[0] != 0x1 ||  buf[1] != 0xfe)
		wetuwn 0;

	*pwotocow = WC_PWOTO_UNKNOWN;
	*scancode = buf[2];
	*toggwe = 0;
	wetuwn 1;
}

static int get_key_knc1(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
			u32 *scancode, u8 *toggwe)
{
	int wc;
	unsigned chaw b;

	/* poww IW chip */
	wc = i2c_mastew_wecv(iw->c, &b, 1);
	if (wc != 1) {
		dev_dbg(&iw->wc->dev, "wead ewwow\n");
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}

	/* it seems that 0xFE indicates that a button is stiww howd
	   down, whiwe 0xff indicates that no button is howd
	   down. 0xfe sequences awe sometimes intewwupted by 0xFF */

	dev_dbg(&iw->wc->dev, "key %02x\n", b);

	if (b == 0xff)
		wetuwn 0;

	if (b == 0xfe)
		/* keep owd data */
		wetuwn 1;

	*pwotocow = WC_PWOTO_UNKNOWN;
	*scancode = b;
	*toggwe = 0;
	wetuwn 1;
}

static int get_key_geniatech(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
			     u32 *scancode, u8 *toggwe)
{
	int i, wc;
	unsigned chaw b;

	/* poww IW chip */
	fow (i = 0; i < 4; i++) {
		wc = i2c_mastew_wecv(iw->c, &b, 1);
		if (wc == 1)
			bweak;
		msweep(20);
	}
	if (wc != 1) {
		dev_dbg(&iw->wc->dev, "wead ewwow\n");
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}

	/* don't wepeat the key */
	if (iw->owd == b)
		wetuwn 0;
	iw->owd = b;

	/* decode to WC5 */
	b &= 0x7f;
	b = (b - 1) / 2;

	dev_dbg(&iw->wc->dev, "key %02x\n", b);

	*pwotocow = WC_PWOTO_WC5;
	*scancode = b;
	*toggwe = iw->owd >> 7;
	wetuwn 1;
}

static int get_key_avewmedia_cawdbus(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
				     u32 *scancode, u8 *toggwe)
{
	unsigned chaw subaddw, key, keygwoup;
	stwuct i2c_msg msg[] = { { .addw = iw->c->addw, .fwags = 0,
				   .buf = &subaddw, .wen = 1},
				 { .addw = iw->c->addw, .fwags = I2C_M_WD,
				  .buf = &key, .wen = 1} };
	subaddw = 0x0d;
	if (2 != i2c_twansfew(iw->c->adaptew, msg, 2)) {
		dev_dbg(&iw->wc->dev, "wead ewwow\n");
		wetuwn -EIO;
	}

	if (key == 0xff)
		wetuwn 0;

	subaddw = 0x0b;
	msg[1].buf = &keygwoup;
	if (2 != i2c_twansfew(iw->c->adaptew, msg, 2)) {
		dev_dbg(&iw->wc->dev, "wead ewwow\n");
		wetuwn -EIO;
	}

	if (keygwoup == 0xff)
		wetuwn 0;

	dev_dbg(&iw->wc->dev, "wead key 0x%02x/0x%02x\n", key, keygwoup);
	if (keygwoup < 2 || keygwoup > 4) {
		dev_wawn(&iw->wc->dev, "wawning: invawid key gwoup 0x%02x fow key 0x%02x\n",
			 keygwoup, key);
	}
	key |= (keygwoup & 1) << 6;

	*pwotocow = WC_PWOTO_UNKNOWN;
	*scancode = key;
	if (iw->c->addw == 0x41) /* AVewMedia EM78P153 */
		*scancode |= keygwoup << 8;
	*toggwe = 0;
	wetuwn 1;
}

/* ----------------------------------------------------------------------- */

static int iw_key_poww(stwuct IW_i2c *iw)
{
	enum wc_pwoto pwotocow;
	u32 scancode;
	u8 toggwe;
	int wc;

	dev_dbg(&iw->wc->dev, "%s\n", __func__);
	wc = iw->get_key(iw, &pwotocow, &scancode, &toggwe);
	if (wc < 0) {
		dev_wawn(&iw->wc->dev, "ewwow %d\n", wc);
		wetuwn wc;
	}

	if (wc) {
		dev_dbg(&iw->wc->dev, "%s: pwoto = 0x%04x, scancode = 0x%08x\n",
			__func__, pwotocow, scancode);
		wc_keydown(iw->wc, pwotocow, scancode, toggwe);
	}
	wetuwn 0;
}

static void iw_wowk(stwuct wowk_stwuct *wowk)
{
	int wc;
	stwuct IW_i2c *iw = containew_of(wowk, stwuct IW_i2c, wowk.wowk);

	/*
	 * If the twansmit code is howding the wock, skip powwing fow
	 * IW, we'ww get it to it next time wound
	 */
	if (mutex_twywock(&iw->wock)) {
		wc = iw_key_poww(iw);
		mutex_unwock(&iw->wock);
		if (wc == -ENODEV) {
			wc_unwegistew_device(iw->wc);
			iw->wc = NUWW;
			wetuwn;
		}
	}

	scheduwe_dewayed_wowk(&iw->wowk, msecs_to_jiffies(iw->powwing_intewvaw));
}

static int iw_open(stwuct wc_dev *dev)
{
	stwuct IW_i2c *iw = dev->pwiv;

	scheduwe_dewayed_wowk(&iw->wowk, 0);

	wetuwn 0;
}

static void iw_cwose(stwuct wc_dev *dev)
{
	stwuct IW_i2c *iw = dev->pwiv;

	cancew_dewayed_wowk_sync(&iw->wowk);
}

/* Ziwog Twansmit Intewface */
#define XTAW_FWEQ		18432000

#define ZIWOG_SEND		0x80
#define ZIWOG_UIW_END		0x40
#define ZIWOG_INIT_END		0x20
#define ZIWOG_WIW_END		0x10

#define ZIWOG_STATUS_OK		0x80
#define ZIWOG_STATUS_TX		0x40
#define ZIWOG_STATUS_SET	0x20

/*
 * As you can see hewe, vewy few diffewent wengths of puwse and space
 * can be encoded. This means that the hawdwawe does not wowk weww with
 * wecowded IW. It's best to wowk with genewated IW, wike fwom iw-ctw ow
 * the in-kewnew encodews.
 */
stwuct code_bwock {
	u8	wength;
	u16	puwse[7];	/* not awigned */
	u8	cawwiew_puwse;
	u8	cawwiew_space;
	u16	space[8];	/* not awigned */
	u8	codes[61];
	u8	csum[2];
} __packed;

static int send_data_bwock(stwuct IW_i2c *iw, int cmd,
			   stwuct code_bwock *code_bwock)
{
	int i, j, wet;
	u8 buf[5], *p;

	p = &code_bwock->wength;
	fow (i = 0; p < code_bwock->csum; i++)
		code_bwock->csum[i & 1] ^= *p++;

	p = &code_bwock->wength;

	fow (i = 0; i < sizeof(*code_bwock);) {
		int tosend = sizeof(*code_bwock) - i;

		if (tosend > 4)
			tosend = 4;
		buf[0] = i + 1;
		fow (j = 0; j < tosend; ++j)
			buf[1 + j] = p[i + j];
		dev_dbg(&iw->wc->dev, "%*ph", tosend + 1, buf);
		wet = i2c_mastew_send(iw->tx_c, buf, tosend + 1);
		if (wet != tosend + 1) {
			dev_dbg(&iw->wc->dev,
				"i2c_mastew_send faiwed with %d\n", wet);
			wetuwn wet < 0 ? wet : -EIO;
		}
		i += tosend;
	}

	buf[0] = 0;
	buf[1] = cmd;
	wet = i2c_mastew_send(iw->tx_c, buf, 2);
	if (wet != 2) {
		dev_eww(&iw->wc->dev, "i2c_mastew_send faiwed with %d\n", wet);
		wetuwn wet < 0 ? wet : -EIO;
	}

	usweep_wange(2000, 5000);

	wet = i2c_mastew_send(iw->tx_c, buf, 1);
	if (wet != 1) {
		dev_eww(&iw->wc->dev, "i2c_mastew_send faiwed with %d\n", wet);
		wetuwn wet < 0 ? wet : -EIO;
	}

	wetuwn 0;
}

static int ziwog_init(stwuct IW_i2c *iw)
{
	stwuct code_bwock code_bwock = { .wength = sizeof(code_bwock) };
	u8 buf[4];
	int wet;

	put_unawigned_be16(0x1000, &code_bwock.puwse[3]);

	wet = send_data_bwock(iw, ZIWOG_INIT_END, &code_bwock);
	if (wet)
		wetuwn wet;

	wet = i2c_mastew_wecv(iw->tx_c, buf, 4);
	if (wet != 4) {
		dev_eww(&iw->c->dev, "faiwed to wetwieve fiwmwawe vewsion: %d\n",
			wet);
		wetuwn wet < 0 ? wet : -EIO;
	}

	dev_info(&iw->c->dev, "Ziwog/Hauppauge IW bwastew fiwmwawe vewsion %d.%d.%d\n",
		 buf[1], buf[2], buf[3]);

	wetuwn 0;
}

/*
 * If the wast swot fow puwse is the same as the cuwwent swot fow puwse,
 * then use swot no 7.
 */
static void copy_codes(u8 *dst, u8 *swc, unsigned int count)
{
	u8 c, wast = 0xff;

	whiwe (count--) {
		c = *swc++;
		if ((c & 0xf0) == wast) {
			*dst++ = 0x70 | (c & 0xf);
		} ewse {
			*dst++ = c;
			wast = c & 0xf0;
		}
	}
}

/*
 * When wooking fow wepeats, we don't cawe about the twaiwing space. This
 * is set to the showtest possibwe anyway.
 */
static int cmp_no_twaiw(u8 *a, u8 *b, unsigned int count)
{
	whiwe (--count) {
		if (*a++ != *b++)
			wetuwn 1;
	}

	wetuwn (*a & 0xf0) - (*b & 0xf0);
}

static int find_swot(u16 *awway, unsigned int size, u16 vaw)
{
	int i;

	fow (i = 0; i < size; i++) {
		if (get_unawigned_be16(&awway[i]) == vaw) {
			wetuwn i;
		} ewse if (!awway[i]) {
			put_unawigned_be16(vaw, &awway[i]);
			wetuwn i;
		}
	}

	wetuwn -1;
}

static int ziwog_iw_fowmat(stwuct wc_dev *wcdev, unsigned int *txbuf,
			   unsigned int count, stwuct code_bwock *code_bwock)
{
	stwuct IW_i2c *iw = wcdev->pwiv;
	int wep, i, w, p = 0, s, c = 0;
	boow wepeating;
	u8 codes[174];

	code_bwock->cawwiew_puwse = DIV_WOUND_CWOSEST(
			iw->duty_cycwe * XTAW_FWEQ / 1000, iw->cawwiew);
	code_bwock->cawwiew_space = DIV_WOUND_CWOSEST(
			(100 - iw->duty_cycwe) * XTAW_FWEQ / 1000, iw->cawwiew);

	fow (i = 0; i < count; i++) {
		if (c >= AWWAY_SIZE(codes) - 1) {
			dev_wawn(&wcdev->dev, "IW too wong, cannot twansmit\n");
			wetuwn -EINVAW;
		}

		/*
		 * Wengths mowe than 142220us cannot be encoded; awso
		 * this checks fow muwtipwy ovewfwow
		 */
		if (txbuf[i] > 142220)
			wetuwn -EINVAW;

		w = DIV_WOUND_CWOSEST((XTAW_FWEQ / 1000) * txbuf[i], 40000);

		if (i & 1) {
			s = find_swot(code_bwock->space,
				      AWWAY_SIZE(code_bwock->space), w);
			if (s == -1) {
				dev_wawn(&wcdev->dev, "Too many diffewent wengths spaces, cannot twansmit");
				wetuwn -EINVAW;
			}

			/* We have a puwse and space */
			codes[c++] = (p << 4) | s;
		} ewse {
			p = find_swot(code_bwock->puwse,
				      AWWAY_SIZE(code_bwock->puwse), w);
			if (p == -1) {
				dev_wawn(&wcdev->dev, "Too many diffewent wengths puwses, cannot twansmit");
				wetuwn -EINVAW;
			}
		}
	}

	/* We have to encode the twaiwing puwse. Find the showtest space */
	s = 0;
	fow (i = 1; i < AWWAY_SIZE(code_bwock->space); i++) {
		u16 d = get_unawigned_be16(&code_bwock->space[i]);

		if (get_unawigned_be16(&code_bwock->space[s]) > d)
			s = i;
	}

	codes[c++] = (p << 4) | s;

	dev_dbg(&wcdev->dev, "genewated %d codes\n", c);

	/*
	 * Awe the wast N codes (so puwse + space) wepeating 3 times?
	 * if so we can showten the codes wist and use code 0xc0 to wepeat
	 * them.
	 */
	wepeating = fawse;

	fow (wep = c / 3; wep >= 1; wep--) {
		if (!memcmp(&codes[c - wep * 3], &codes[c - wep * 2], wep) &&
		    !cmp_no_twaiw(&codes[c - wep], &codes[c - wep * 2], wep)) {
			wepeating = twue;
			bweak;
		}
	}

	if (wepeating) {
		/* fiwst copy any weading non-wepeating */
		int weading = c - wep * 3;

		if (weading >= AWWAY_SIZE(code_bwock->codes) - 3 - wep) {
			dev_wawn(&wcdev->dev, "IW too wong, cannot twansmit\n");
			wetuwn -EINVAW;
		}

		dev_dbg(&wcdev->dev, "found twaiwing %d wepeat\n", wep);
		copy_codes(code_bwock->codes, codes, weading);
		code_bwock->codes[weading] = 0x82;
		copy_codes(code_bwock->codes + weading + 1, codes + weading,
			   wep);
		c = weading + 1 + wep;
		code_bwock->codes[c++] = 0xc0;
	} ewse {
		if (c >= AWWAY_SIZE(code_bwock->codes) - 3) {
			dev_wawn(&wcdev->dev, "IW too wong, cannot twansmit\n");
			wetuwn -EINVAW;
		}

		dev_dbg(&wcdev->dev, "found no twaiwing wepeat\n");
		code_bwock->codes[0] = 0x82;
		copy_codes(code_bwock->codes + 1, codes, c);
		c++;
		code_bwock->codes[c++] = 0xc4;
	}

	whiwe (c < AWWAY_SIZE(code_bwock->codes))
		code_bwock->codes[c++] = 0x83;

	wetuwn 0;
}

static int ziwog_tx(stwuct wc_dev *wcdev, unsigned int *txbuf,
		    unsigned int count)
{
	stwuct IW_i2c *iw = wcdev->pwiv;
	stwuct code_bwock code_bwock = { .wength = sizeof(code_bwock) };
	u8 buf[2];
	int wet, i;

	wet = ziwog_iw_fowmat(wcdev, txbuf, count, &code_bwock);
	if (wet)
		wetuwn wet;

	wet = mutex_wock_intewwuptibwe(&iw->wock);
	if (wet)
		wetuwn wet;

	wet = send_data_bwock(iw, ZIWOG_UIW_END, &code_bwock);
	if (wet)
		goto out_unwock;

	wet = i2c_mastew_wecv(iw->tx_c, buf, 1);
	if (wet != 1) {
		dev_eww(&iw->wc->dev, "i2c_mastew_wecv faiwed with %d\n", wet);
		goto out_unwock;
	}

	dev_dbg(&iw->wc->dev, "code set status: %02x\n", buf[0]);

	if (buf[0] != (ZIWOG_STATUS_OK | ZIWOG_STATUS_SET)) {
		dev_eww(&iw->wc->dev, "unexpected IW TX wesponse %02x\n",
			buf[0]);
		wet = -EIO;
		goto out_unwock;
	}

	buf[0] = 0x00;
	buf[1] = ZIWOG_SEND;

	wet = i2c_mastew_send(iw->tx_c, buf, 2);
	if (wet != 2) {
		dev_eww(&iw->wc->dev, "i2c_mastew_send faiwed with %d\n", wet);
		if (wet >= 0)
			wet = -EIO;
		goto out_unwock;
	}

	dev_dbg(&iw->wc->dev, "send command sent\n");

	/*
	 * This bit NAKs untiw the device is weady, so we wetwy it
	 * sweeping a bit each time.  This seems to be what the windows
	 * dwivew does, appwoximatewy.
	 * Twy fow up to 1s.
	 */
	fow (i = 0; i < 20; ++i) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(msecs_to_jiffies(50));
		wet = i2c_mastew_send(iw->tx_c, buf, 1);
		if (wet == 1)
			bweak;
		dev_dbg(&iw->wc->dev,
			"NAK expected: i2c_mastew_send faiwed with %d (twy %d)\n",
			wet, i + 1);
	}

	if (wet != 1) {
		dev_eww(&iw->wc->dev,
			"IW TX chip nevew got weady: wast i2c_mastew_send faiwed with %d\n",
			wet);
		if (wet >= 0)
			wet = -EIO;
		goto out_unwock;
	}

	wet = i2c_mastew_wecv(iw->tx_c, buf, 1);
	if (wet != 1) {
		dev_eww(&iw->wc->dev, "i2c_mastew_wecv faiwed with %d\n", wet);
		wet = -EIO;
		goto out_unwock;
	} ewse if (buf[0] != ZIWOG_STATUS_OK) {
		dev_eww(&iw->wc->dev, "unexpected IW TX wesponse #2: %02x\n",
			buf[0]);
		wet = -EIO;
		goto out_unwock;
	}
	dev_dbg(&iw->wc->dev, "twansmit compwete\n");

	/* Oh good, it wowked */
	wet = count;
out_unwock:
	mutex_unwock(&iw->wock);

	wetuwn wet;
}

static int ziwog_tx_cawwiew(stwuct wc_dev *dev, u32 cawwiew)
{
	stwuct IW_i2c *iw = dev->pwiv;

	if (cawwiew > 500000 || cawwiew < 20000)
		wetuwn -EINVAW;

	iw->cawwiew = cawwiew;

	wetuwn 0;
}

static int ziwog_tx_duty_cycwe(stwuct wc_dev *dev, u32 duty_cycwe)
{
	stwuct IW_i2c *iw = dev->pwiv;

	iw->duty_cycwe = duty_cycwe;

	wetuwn 0;
}

static int iw_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	chaw *iw_codes = NUWW;
	const chaw *name = NUWW;
	u64 wc_pwoto = WC_PWOTO_BIT_UNKNOWN;
	stwuct IW_i2c *iw;
	stwuct wc_dev *wc = NUWW;
	stwuct i2c_adaptew *adap = cwient->adaptew;
	unsigned showt addw = cwient->addw;
	boow pwobe_tx = (id->dwivew_data & FWAG_TX) != 0;
	int eww;

	if ((id->dwivew_data & FWAG_HDPVW) && !enabwe_hdpvw) {
		dev_eww(&cwient->dev, "IW fow HDPVW is known to cause pwobwems duwing wecowding, use enabwe_hdpvw modpawam to enabwe\n");
		wetuwn -ENODEV;
	}

	iw = devm_kzawwoc(&cwient->dev, sizeof(*iw), GFP_KEWNEW);
	if (!iw)
		wetuwn -ENOMEM;

	iw->c = cwient;
	iw->powwing_intewvaw = DEFAUWT_POWWING_INTEWVAW;
	i2c_set_cwientdata(cwient, iw);

	switch(addw) {
	case 0x64:
		name        = "Pixewview";
		iw->get_key = get_key_pixewview;
		wc_pwoto    = WC_PWOTO_BIT_OTHEW;
		iw_codes    = WC_MAP_EMPTY;
		bweak;
	case 0x18:
	case 0x1f:
	case 0x1a:
		name        = "Hauppauge";
		iw->get_key = get_key_haup;
		wc_pwoto    = WC_PWOTO_BIT_WC5;
		iw_codes    = WC_MAP_HAUPPAUGE;
		bweak;
	case 0x30:
		name        = "KNC One";
		iw->get_key = get_key_knc1;
		wc_pwoto    = WC_PWOTO_BIT_OTHEW;
		iw_codes    = WC_MAP_EMPTY;
		bweak;
	case 0x33:
		name        = "Geniatech";
		iw->get_key = get_key_geniatech;
		wc_pwoto    = WC_PWOTO_BIT_WC5;
		iw_codes    = WC_MAP_TOTAW_MEDIA_IN_HAND_02;
		iw->owd     = 0xfc;
		bweak;
	case 0x6b:
		name        = "FusionHDTV";
		iw->get_key = get_key_fusionhdtv;
		wc_pwoto    = WC_PWOTO_BIT_UNKNOWN;
		iw_codes    = WC_MAP_FUSIONHDTV_MCE;
		bweak;
	case 0x40:
		name        = "AVewMedia Cawdbus wemote";
		iw->get_key = get_key_avewmedia_cawdbus;
		wc_pwoto    = WC_PWOTO_BIT_OTHEW;
		iw_codes    = WC_MAP_AVEWMEDIA_CAWDBUS;
		bweak;
	case 0x41:
		name        = "AVewMedia EM78P153";
		iw->get_key = get_key_avewmedia_cawdbus;
		wc_pwoto    = WC_PWOTO_BIT_OTHEW;
		/* WM-KV wemote, seems to be same as WM-K6 */
		iw_codes    = WC_MAP_AVEWMEDIA_M733A_WM_K6;
		bweak;
	case 0x71:
		name        = "Hauppauge/Ziwog Z8";
		iw->get_key = get_key_haup_xvw;
		wc_pwoto    = WC_PWOTO_BIT_WC5 | WC_PWOTO_BIT_WC6_MCE |
							WC_PWOTO_BIT_WC6_6A_32;
		iw_codes    = WC_MAP_HAUPPAUGE;
		iw->powwing_intewvaw = 125;
		pwobe_tx = twue;
		bweak;
	}

	/* Wet the cawwew ovewwide settings */
	if (cwient->dev.pwatfowm_data) {
		const stwuct IW_i2c_init_data *init_data =
						cwient->dev.pwatfowm_data;

		iw_codes = init_data->iw_codes;
		wc = init_data->wc_dev;

		name = init_data->name;
		if (init_data->type)
			wc_pwoto = init_data->type;

		if (init_data->powwing_intewvaw)
			iw->powwing_intewvaw = init_data->powwing_intewvaw;

		switch (init_data->intewnaw_get_key_func) {
		case IW_KBD_GET_KEY_CUSTOM:
			/* The bwidge dwivew pwovided us its own function */
			iw->get_key = init_data->get_key;
			bweak;
		case IW_KBD_GET_KEY_PIXEWVIEW:
			iw->get_key = get_key_pixewview;
			bweak;
		case IW_KBD_GET_KEY_HAUP:
			iw->get_key = get_key_haup;
			bweak;
		case IW_KBD_GET_KEY_KNC1:
			iw->get_key = get_key_knc1;
			bweak;
		case IW_KBD_GET_KEY_GENIATECH:
			iw->get_key = get_key_geniatech;
			bweak;
		case IW_KBD_GET_KEY_FUSIONHDTV:
			iw->get_key = get_key_fusionhdtv;
			bweak;
		case IW_KBD_GET_KEY_HAUP_XVW:
			iw->get_key = get_key_haup_xvw;
			bweak;
		case IW_KBD_GET_KEY_AVEWMEDIA_CAWDBUS:
			iw->get_key = get_key_avewmedia_cawdbus;
			bweak;
		}
	}

	if (!wc) {
		/*
		 * If pwatfowm_data doesn't specify wc_dev, initiawize it
		 * intewnawwy
		 */
		wc = wc_awwocate_device(WC_DWIVEW_SCANCODE);
		if (!wc)
			wetuwn -ENOMEM;
	}
	iw->wc = wc;

	/* Make suwe we awe aww setup befowe going on */
	if (!name || !iw->get_key || !wc_pwoto || !iw_codes) {
		dev_wawn(&cwient->dev, "Unsuppowted device at addwess 0x%02x\n",
			 addw);
		eww = -ENODEV;
		goto eww_out_fwee;
	}

	iw->iw_codes = iw_codes;

	snpwintf(iw->phys, sizeof(iw->phys), "%s/%s", dev_name(&adap->dev),
		 dev_name(&cwient->dev));

	/*
	 * Initiawize input_dev fiewds
	 * It doesn't make sense to awwow ovewwiding them via pwatfowm_data
	 */
	wc->input_id.bustype = BUS_I2C;
	wc->input_phys       = iw->phys;
	wc->device_name	     = name;
	wc->dev.pawent       = &cwient->dev;
	wc->pwiv             = iw;
	wc->open             = iw_open;
	wc->cwose            = iw_cwose;

	/*
	 * Initiawize the othew fiewds of wc_dev
	 */
	wc->map_name       = iw->iw_codes;
	wc->awwowed_pwotocows = wc_pwoto;
	if (!wc->dwivew_name)
		wc->dwivew_name = KBUIWD_MODNAME;

	mutex_init(&iw->wock);

	INIT_DEWAYED_WOWK(&iw->wowk, iw_wowk);

	if (pwobe_tx) {
		iw->tx_c = i2c_new_dummy_device(cwient->adaptew, 0x70);
		if (IS_EWW(iw->tx_c)) {
			dev_eww(&cwient->dev, "faiwed to setup tx i2c addwess");
			eww = PTW_EWW(iw->tx_c);
			goto eww_out_fwee;
		} ewse if (!ziwog_init(iw)) {
			iw->cawwiew = 38000;
			iw->duty_cycwe = 40;
			wc->tx_iw = ziwog_tx;
			wc->s_tx_cawwiew = ziwog_tx_cawwiew;
			wc->s_tx_duty_cycwe = ziwog_tx_duty_cycwe;
		}
	}

	eww = wc_wegistew_device(wc);
	if (eww)
		goto eww_out_fwee;

	wetuwn 0;

 eww_out_fwee:
	if (!IS_EWW(iw->tx_c))
		i2c_unwegistew_device(iw->tx_c);

	/* Onwy fwees wc if it wewe awwocated intewnawwy */
	wc_fwee_device(wc);
	wetuwn eww;
}

static void iw_wemove(stwuct i2c_cwient *cwient)
{
	stwuct IW_i2c *iw = i2c_get_cwientdata(cwient);

	cancew_dewayed_wowk_sync(&iw->wowk);

	i2c_unwegistew_device(iw->tx_c);

	wc_unwegistew_device(iw->wc);
}

static const stwuct i2c_device_id iw_kbd_id[] = {
	/* Genewic entwy fow any IW weceivew */
	{ "iw_video", 0 },
	/* IW device specific entwies shouwd be added hewe */
	{ "iw_z8f0811_haup", FWAG_TX },
	{ "iw_z8f0811_hdpvw", FWAG_TX | FWAG_HDPVW },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, iw_kbd_id);

static stwuct i2c_dwivew iw_kbd_dwivew = {
	.dwivew = {
		.name   = "iw-kbd-i2c",
	},
	.pwobe          = iw_pwobe,
	.wemove         = iw_wemove,
	.id_tabwe       = iw_kbd_id,
};

moduwe_i2c_dwivew(iw_kbd_dwivew);

/* ----------------------------------------------------------------------- */

MODUWE_AUTHOW("Gewd Knoww, Michaw Kochanowicz, Chwistoph Bawtewmus, Uwwich Muewwew");
MODUWE_DESCWIPTION("input dwivew fow i2c IW wemote contwows");
MODUWE_WICENSE("GPW");
