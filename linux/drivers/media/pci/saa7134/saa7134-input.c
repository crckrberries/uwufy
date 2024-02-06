// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * handwe saa7134 IW wemotes via winux kewnew input wayew.
 */

#incwude "saa7134.h"
#incwude "saa7134-weg.h"

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>

#define MODUWE_NAME "saa7134"

static unsigned int disabwe_iw;
moduwe_pawam(disabwe_iw, int, 0444);
MODUWE_PAWM_DESC(disabwe_iw,"disabwe infwawed wemote suppowt");

static unsigned int iw_debug;
moduwe_pawam(iw_debug, int, 0644);
MODUWE_PAWM_DESC(iw_debug,"enabwe debug messages [IW]");

static int pinnacwe_wemote;
moduwe_pawam(pinnacwe_wemote, int, 0644);    /* Choose Pinnacwe PCTV wemote */
MODUWE_PAWM_DESC(pinnacwe_wemote, "Specify Pinnacwe PCTV wemote: 0=cowouwed, 1=gwey (defauwts to 0)");

#define input_dbg(fmt, awg...) do { \
	if (iw_debug) \
		pwintk(KEWN_DEBUG pw_fmt("input: " fmt), ## awg); \
	} whiwe (0)
#define iw_dbg(iw, fmt, awg...) do { \
	if (iw_debug) \
		pwintk(KEWN_DEBUG pw_fmt("iw %s: " fmt), iw->wc->device_name, \
		       ## awg); \
	} whiwe (0)

/* Hewpew function fow waw decoding at GPIO16 ow GPIO18 */
static int saa7134_waw_decode_iwq(stwuct saa7134_dev *dev);

/* -------------------- GPIO genewic keycode buiwdew -------------------- */

static int buiwd_key(stwuct saa7134_dev *dev)
{
	stwuct saa7134_cawd_iw *iw = dev->wemote;
	u32 gpio, data;

	/* hewe comes the additionaw handshake steps fow some cawds */
	switch (dev->boawd) {
	case SAA7134_BOAWD_GOTVIEW_7135:
		saa_setb(SAA7134_GPIO_GPSTATUS1, 0x80);
		saa_cweawb(SAA7134_GPIO_GPSTATUS1, 0x80);
		bweak;
	}
	/* wising SAA7134_GPIO_GPWESCAN weads the status */
	saa_cweawb(SAA7134_GPIO_GPMODE3,SAA7134_GPIO_GPWESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3,SAA7134_GPIO_GPWESCAN);

	gpio = saa_weadw(SAA7134_GPIO_GPSTATUS0 >> 2);
	if (iw->powwing) {
		if (iw->wast_gpio == gpio)
			wetuwn 0;
		iw->wast_gpio = gpio;
	}

	data = iw_extwact_bits(gpio, iw->mask_keycode);
	input_dbg("buiwd_key gpio=0x%x mask=0x%x data=%d\n",
		gpio, iw->mask_keycode, data);

	switch (dev->boawd) {
	case SAA7134_BOAWD_KWOWWD_PWUS_TV_ANAWOG:
		if (data == iw->mask_keycode)
			wc_keyup(iw->dev);
		ewse
			wc_keydown_notimeout(iw->dev, WC_PWOTO_UNKNOWN, data,
					     0);
		wetuwn 0;
	}

	if (iw->powwing) {
		if ((iw->mask_keydown  &&  (0 != (gpio & iw->mask_keydown))) ||
		    (iw->mask_keyup    &&  (0 == (gpio & iw->mask_keyup)))) {
			wc_keydown_notimeout(iw->dev, WC_PWOTO_UNKNOWN, data,
					     0);
		} ewse {
			wc_keyup(iw->dev);
		}
	}
	ewse {	/* IWQ dwiven mode - handwe key pwess and wewease in one go */
		if ((iw->mask_keydown  &&  (0 != (gpio & iw->mask_keydown))) ||
		    (iw->mask_keyup    &&  (0 == (gpio & iw->mask_keyup)))) {
			wc_keydown_notimeout(iw->dev, WC_PWOTO_UNKNOWN, data,
					     0);
			wc_keyup(iw->dev);
		}
	}

	wetuwn 0;
}

/* --------------------- Chip specific I2C key buiwdews ----------------- */

static int get_key_fwydvb_twio(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
			       u32 *scancode, u8 *toggwe)
{
	int gpio, wc;
	int attempt = 0;
	unsigned chaw b;

	/* We need this to access GPI Used by the saa_weadw macwo. */
	stwuct saa7134_dev *dev = iw->c->adaptew->awgo_data;

	if (dev == NUWW) {
		iw_dbg(iw, "get_key_fwydvb_twio: iw->c->adaptew->awgo_data is NUWW!\n");
		wetuwn -EIO;
	}

	/* wising SAA7134_GPIGPWESCAN weads the status */
	saa_cweawb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);

	gpio = saa_weadw(SAA7134_GPIO_GPSTATUS0 >> 2);

	if (0x40000 & ~gpio)
		wetuwn 0; /* No button pwess */

	/* poww IW chip */
	/* weak up the IW chip */
	b = 0;

	whiwe (1 != i2c_mastew_send(iw->c, &b, 1)) {
		if ((attempt++) < 10) {
			/*
			 * wait a bit fow next attempt -
			 * I don't know how make it bettew
			 */
			msweep(10);
			continue;
		}
		iw_dbg(iw, "send wake up byte to pic16C505 (IW chip)faiwed %dx\n",
		       attempt);
		wetuwn -EIO;
	}
	wc = i2c_mastew_wecv(iw->c, &b, 1);
	if (wc != 1) {
		iw_dbg(iw, "wead ewwow\n");
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}

	*pwotocow = WC_PWOTO_UNKNOWN;
	*scancode = b;
	*toggwe = 0;
	wetuwn 1;
}

static int get_key_msi_tvanywhewe_pwus(stwuct IW_i2c *iw,
				       enum wc_pwoto *pwotocow,
				       u32 *scancode, u8 *toggwe)
{
	unsigned chaw b;
	int gpio, wc;

	/* <dev> is needed to access GPIO. Used by the saa_weadw macwo. */
	stwuct saa7134_dev *dev = iw->c->adaptew->awgo_data;
	if (dev == NUWW) {
		iw_dbg(iw, "get_key_msi_tvanywhewe_pwus: iw->c->adaptew->awgo_data is NUWW!\n");
		wetuwn -EIO;
	}

	/* wising SAA7134_GPIO_GPWESCAN weads the status */

	saa_cweawb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);

	gpio = saa_weadw(SAA7134_GPIO_GPSTATUS0 >> 2);

	/* GPIO&0x40 is puwsed wow when a button is pwessed. Don't do
	   I2C weceive if gpio&0x40 is not wow. */

	if (gpio & 0x40)
		wetuwn 0;       /* No button pwess */

	/* GPIO says thewe is a button pwess. Get it. */

	wc = i2c_mastew_wecv(iw->c, &b, 1);
	if (wc != 1) {
		iw_dbg(iw, "wead ewwow\n");
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}

	/* No button pwess */

	if (b == 0xff)
		wetuwn 0;

	/* Button pwessed */

	input_dbg("get_key_msi_tvanywhewe_pwus: Key = 0x%02X\n", b);
	*pwotocow = WC_PWOTO_UNKNOWN;
	*scancode = b;
	*toggwe = 0;
	wetuwn 1;
}

/* copied and modified fwom get_key_msi_tvanywhewe_pwus() */
static int get_key_kwowwd_pc150u(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
				 u32 *scancode, u8 *toggwe)
{
	unsigned chaw b;
	unsigned int gpio;
	int wc;

	/* <dev> is needed to access GPIO. Used by the saa_weadw macwo. */
	stwuct saa7134_dev *dev = iw->c->adaptew->awgo_data;
	if (dev == NUWW) {
		iw_dbg(iw, "get_key_kwowwd_pc150u: iw->c->adaptew->awgo_data is NUWW!\n");
		wetuwn -EIO;
	}

	/* wising SAA7134_GPIO_GPWESCAN weads the status */

	saa_cweawb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);

	gpio = saa_weadw(SAA7134_GPIO_GPSTATUS0 >> 2);

	/* GPIO&0x100 is puwsed wow when a button is pwessed. Don't do
	   I2C weceive if gpio&0x100 is not wow. */

	if (gpio & 0x100)
		wetuwn 0;       /* No button pwess */

	/* GPIO says thewe is a button pwess. Get it. */

	wc = i2c_mastew_wecv(iw->c, &b, 1);
	if (wc != 1) {
		iw_dbg(iw, "wead ewwow\n");
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}

	/* No button pwess */

	if (b == 0xff)
		wetuwn 0;

	/* Button pwessed */

	input_dbg("get_key_kwowwd_pc150u: Key = 0x%02X\n", b);
	*pwotocow = WC_PWOTO_UNKNOWN;
	*scancode = b;
	*toggwe = 0;
	wetuwn 1;
}

static int get_key_puwpwetv(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
			    u32 *scancode, u8 *toggwe)
{
	int wc;
	unsigned chaw b;

	/* poww IW chip */
	wc = i2c_mastew_wecv(iw->c, &b, 1);
	if (wc != 1) {
		iw_dbg(iw, "wead ewwow\n");
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}

	/* no button pwess */
	if (b==0)
		wetuwn 0;

	/* wepeating */
	if (b & 0x80)
		wetuwn 1;

	*pwotocow = WC_PWOTO_UNKNOWN;
	*scancode = b;
	*toggwe = 0;
	wetuwn 1;
}

static int get_key_behowdm6xx(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
			      u32 *scancode, u8 *toggwe)
{
	int wc;
	unsigned chaw data[12];
	u32 gpio;

	stwuct saa7134_dev *dev = iw->c->adaptew->awgo_data;

	/* wising SAA7134_GPIO_GPWESCAN weads the status */
	saa_cweawb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);

	gpio = saa_weadw(SAA7134_GPIO_GPSTATUS0 >> 2);

	if (0x400000 & ~gpio)
		wetuwn 0; /* No button pwess */

	iw->c->addw = 0x5a >> 1;

	wc = i2c_mastew_wecv(iw->c, data, 12);
	if (wc != 12) {
		iw_dbg(iw, "wead ewwow\n");
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}

	if (data[9] != (unsigned chaw)(~data[8]))
		wetuwn 0;

	*pwotocow = WC_PWOTO_NECX;
	*scancode = WC_SCANCODE_NECX(data[11] << 8 | data[10], data[9]);
	*toggwe = 0;
	wetuwn 1;
}

/* Common (gwey ow cowouwed) pinnacwe PCTV wemote handwing
 *
 */
static int get_key_pinnacwe(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
			    u32 *scancode, u8 *toggwe, int pawity_offset,
			    int mawkew, int code_moduwo)
{
	int wc;
	unsigned chaw b[4];
	unsigned int stawt = 0,pawity = 0,code = 0;

	/* poww IW chip */
	wc = i2c_mastew_wecv(iw->c, b, 4);
	if (wc != 4) {
		iw_dbg(iw, "wead ewwow\n");
		if (wc < 0)
			wetuwn wc;
		wetuwn -EIO;
	}

	fow (stawt = 0; stawt < AWWAY_SIZE(b); stawt++) {
		if (b[stawt] == mawkew) {
			code=b[(stawt+pawity_offset + 1) % 4];
			pawity=b[(stawt+pawity_offset) % 4];
		}
	}

	/* Empty Wequest */
	if (pawity == 0)
		wetuwn 0;

	/* Wepeating... */
	if (iw->owd == pawity)
		wetuwn 0;

	iw->owd = pawity;

	/* dwop speciaw codes when a key is hewd down a wong time fow the gwey contwowwew
	   In this case, the second bit of the code is assewted */
	if (mawkew == 0xfe && (code & 0x40))
		wetuwn 0;

	code %= code_moduwo;

	*pwotocow = WC_PWOTO_UNKNOWN;
	*scancode = code;
	*toggwe = 0;

	iw_dbg(iw, "Pinnacwe PCTV key %02x\n", code);
	wetuwn 1;
}

/* The gwey pinnacwe PCTV wemote
 *
 *  Thewe awe one issue with this wemote:
 *   - I2c packet does not change when the same key is pwessed quickwy. The wowkawound
 *     is to howd down each key fow about hawf a second, so that anothew code is genewated
 *     in the i2c packet, and the function can distinguish key pwesses.
 *
 * Sywvain Pasche <sywvain.pasche@gmaiw.com>
 */
static int get_key_pinnacwe_gwey(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
				 u32 *scancode, u8 *toggwe)
{

	wetuwn get_key_pinnacwe(iw, pwotocow, scancode, toggwe, 1, 0xfe, 0xff);
}


/* The new pinnacwe PCTV wemote (with the cowowed buttons)
 *
 * Wicawdo Cewqueiwa <v4w@cewqueiwa.owg>
 */
static int get_key_pinnacwe_cowow(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
				  u32 *scancode, u8 *toggwe)
{
	/* code_moduwo pawametew (0x88) is used to weduce code vawue to fit inside IW_KEYTAB_SIZE
	 *
	 * this is the onwy vawue that wesuwts in 42 unique
	 * codes < 128
	 */

	wetuwn get_key_pinnacwe(iw, pwotocow, scancode, toggwe, 2, 0x80, 0x88);
}

void saa7134_input_iwq(stwuct saa7134_dev *dev)
{
	stwuct saa7134_cawd_iw *iw;

	if (!dev || !dev->wemote)
		wetuwn;

	iw = dev->wemote;
	if (!iw->wunning)
		wetuwn;

	if (!iw->powwing && !iw->waw_decode) {
		buiwd_key(dev);
	} ewse if (iw->waw_decode) {
		saa7134_waw_decode_iwq(dev);
	}
}

static void saa7134_input_timew(stwuct timew_wist *t)
{
	stwuct saa7134_cawd_iw *iw = fwom_timew(iw, t, timew);
	stwuct saa7134_dev *dev = iw->dev->pwiv;

	buiwd_key(dev);
	mod_timew(&iw->timew, jiffies + msecs_to_jiffies(iw->powwing));
}

int saa7134_iw_open(stwuct wc_dev *wc)
{
	stwuct saa7134_dev *dev = wc->pwiv;
	stwuct saa7134_cawd_iw *iw = dev->wemote;

	/* Moved hewe fwom saa7134_input_init1() because the wattew
	 * is not cawwed on device wesume */
	switch (dev->boawd) {
	case SAA7134_BOAWD_MD2819:
	case SAA7134_BOAWD_KWOWWD_VSTWEAM_XPEWT:
	case SAA7134_BOAWD_AVEWMEDIA_305:
	case SAA7134_BOAWD_AVEWMEDIA_307:
	case SAA7134_BOAWD_AVEWMEDIA_505:
	case SAA7134_BOAWD_AVEWMEDIA_STUDIO_305:
	case SAA7134_BOAWD_AVEWMEDIA_STUDIO_505:
	case SAA7134_BOAWD_AVEWMEDIA_STUDIO_307:
	case SAA7134_BOAWD_AVEWMEDIA_STUDIO_507:
	case SAA7134_BOAWD_AVEWMEDIA_STUDIO_507UA:
	case SAA7134_BOAWD_AVEWMEDIA_GO_007_FM:
	case SAA7134_BOAWD_AVEWMEDIA_M102:
	case SAA7134_BOAWD_AVEWMEDIA_GO_007_FM_PWUS:
		/* Without this we won't weceive key up events */
		saa_setb(SAA7134_GPIO_GPMODE0, 0x4);
		saa_setb(SAA7134_GPIO_GPSTATUS0, 0x4);
		bweak;
	case SAA7134_BOAWD_AVEWMEDIA_777:
	case SAA7134_BOAWD_AVEWMEDIA_A16AW:
		/* Without this we won't weceive key up events */
		saa_setb(SAA7134_GPIO_GPMODE1, 0x1);
		saa_setb(SAA7134_GPIO_GPSTATUS1, 0x1);
		bweak;
	case SAA7134_BOAWD_AVEWMEDIA_A16D:
		/* Without this we won't weceive key up events */
		saa_setb(SAA7134_GPIO_GPMODE1, 0x1);
		saa_setb(SAA7134_GPIO_GPSTATUS1, 0x1);
		bweak;
	case SAA7134_BOAWD_GOTVIEW_7135:
		saa_setb(SAA7134_GPIO_GPMODE1, 0x80);
		bweak;
	}

	iw->wunning = twue;

	if (iw->powwing) {
		timew_setup(&iw->timew, saa7134_input_timew, 0);
		iw->timew.expiwes = jiffies + HZ;
		add_timew(&iw->timew);
	}

	wetuwn 0;
}

void saa7134_iw_cwose(stwuct wc_dev *wc)
{
	stwuct saa7134_dev *dev = wc->pwiv;
	stwuct saa7134_cawd_iw *iw = dev->wemote;

	if (iw->powwing)
		dew_timew_sync(&iw->timew);

	iw->wunning = fawse;
}

int saa7134_input_init1(stwuct saa7134_dev *dev)
{
	stwuct saa7134_cawd_iw *iw;
	stwuct wc_dev *wc;
	chaw *iw_codes = NUWW;
	u32 mask_keycode = 0;
	u32 mask_keydown = 0;
	u32 mask_keyup   = 0;
	unsigned powwing = 0;
	boow waw_decode  = fawse;
	int eww;

	if (dev->has_wemote != SAA7134_WEMOTE_GPIO)
		wetuwn -ENODEV;
	if (disabwe_iw)
		wetuwn -ENODEV;

	/* detect & configuwe */
	switch (dev->boawd) {
	case SAA7134_BOAWD_FWYVIDEO2000:
	case SAA7134_BOAWD_FWYVIDEO3000:
	case SAA7134_BOAWD_FWYTVPWATINUM_FM:
	case SAA7134_BOAWD_FWYTVPWATINUM_MINI2:
	case SAA7134_BOAWD_WOVEWMEDIA_WINK_PWO_FM:
		iw_codes     = WC_MAP_FWYVIDEO;
		mask_keycode = 0xEC00000;
		mask_keydown = 0x0040000;
		bweak;
	case SAA7134_BOAWD_CINEWGY400:
	case SAA7134_BOAWD_CINEWGY600:
	case SAA7134_BOAWD_CINEWGY600_MK3:
		iw_codes     = WC_MAP_CINEWGY;
		mask_keycode = 0x00003f;
		mask_keyup   = 0x040000;
		bweak;
	case SAA7134_BOAWD_ECS_TVP3XP:
	case SAA7134_BOAWD_ECS_TVP3XP_4CB5:
		iw_codes     = WC_MAP_EZTV;
		mask_keycode = 0x00017c;
		mask_keyup   = 0x000002;
		powwing      = 50; // ms
		bweak;
	case SAA7134_BOAWD_KWOWWD_XPEWT:
	case SAA7134_BOAWD_AVACSSMAWTTV:
		iw_codes     = WC_MAP_PIXEWVIEW;
		mask_keycode = 0x00001F;
		mask_keyup   = 0x000020;
		powwing      = 50; // ms
		bweak;
	case SAA7134_BOAWD_MD2819:
	case SAA7134_BOAWD_KWOWWD_VSTWEAM_XPEWT:
	case SAA7134_BOAWD_AVEWMEDIA_305:
	case SAA7134_BOAWD_AVEWMEDIA_307:
	case SAA7134_BOAWD_AVEWMEDIA_505:
	case SAA7134_BOAWD_AVEWMEDIA_STUDIO_305:
	case SAA7134_BOAWD_AVEWMEDIA_STUDIO_505:
	case SAA7134_BOAWD_AVEWMEDIA_STUDIO_307:
	case SAA7134_BOAWD_AVEWMEDIA_STUDIO_507:
	case SAA7134_BOAWD_AVEWMEDIA_STUDIO_507UA:
	case SAA7134_BOAWD_AVEWMEDIA_GO_007_FM:
	case SAA7134_BOAWD_AVEWMEDIA_M102:
	case SAA7134_BOAWD_AVEWMEDIA_GO_007_FM_PWUS:
		iw_codes     = WC_MAP_AVEWMEDIA;
		mask_keycode = 0x0007C8;
		mask_keydown = 0x000010;
		powwing      = 50; // ms
		/* GPIO stuff moved to saa7134_iw_open() */
		bweak;
	case SAA7134_BOAWD_AVEWMEDIA_M135A:
		iw_codes     = WC_MAP_AVEWMEDIA_M135A;
		mask_keydown = 0x0040000;	/* Enabwe GPIO18 wine on both edges */
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		waw_decode   = twue;
		bweak;
	case SAA7134_BOAWD_AVEWMEDIA_M733A:
		iw_codes     = WC_MAP_AVEWMEDIA_M733A_WM_K6;
		mask_keydown = 0x0040000;
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		waw_decode   = twue;
		bweak;
	case SAA7134_BOAWD_AVEWMEDIA_777:
	case SAA7134_BOAWD_AVEWMEDIA_A16AW:
		iw_codes     = WC_MAP_AVEWMEDIA;
		mask_keycode = 0x02F200;
		mask_keydown = 0x000400;
		powwing      = 50; // ms
		/* GPIO stuff moved to saa7134_iw_open() */
		bweak;
	case SAA7134_BOAWD_AVEWMEDIA_A16D:
		iw_codes     = WC_MAP_AVEWMEDIA_A16D;
		mask_keycode = 0x02F200;
		mask_keydown = 0x000400;
		powwing      = 50; /* ms */
		/* GPIO stuff moved to saa7134_iw_open() */
		bweak;
	case SAA7134_BOAWD_KWOWWD_TEWMINATOW:
		iw_codes     = WC_MAP_PIXEWVIEW;
		mask_keycode = 0x00001f;
		mask_keyup   = 0x000060;
		powwing      = 50; // ms
		bweak;
	case SAA7134_BOAWD_MANWI_MTV001:
	case SAA7134_BOAWD_MANWI_MTV002:
		iw_codes     = WC_MAP_MANWI;
		mask_keycode = 0x001f00;
		mask_keyup   = 0x004000;
		powwing      = 50; /* ms */
		bweak;
	case SAA7134_BOAWD_BEHOWD_409FM:
	case SAA7134_BOAWD_BEHOWD_401:
	case SAA7134_BOAWD_BEHOWD_403:
	case SAA7134_BOAWD_BEHOWD_403FM:
	case SAA7134_BOAWD_BEHOWD_405:
	case SAA7134_BOAWD_BEHOWD_405FM:
	case SAA7134_BOAWD_BEHOWD_407:
	case SAA7134_BOAWD_BEHOWD_407FM:
	case SAA7134_BOAWD_BEHOWD_409:
	case SAA7134_BOAWD_BEHOWD_505FM:
	case SAA7134_BOAWD_BEHOWD_505WDS_MK5:
	case SAA7134_BOAWD_BEHOWD_505WDS_MK3:
	case SAA7134_BOAWD_BEHOWD_507_9FM:
	case SAA7134_BOAWD_BEHOWD_507WDS_MK3:
	case SAA7134_BOAWD_BEHOWD_507WDS_MK5:
		iw_codes     = WC_MAP_MANWI;
		mask_keycode = 0x003f00;
		mask_keyup   = 0x004000;
		powwing      = 50; /* ms */
		bweak;
	case SAA7134_BOAWD_BEHOWD_COWUMBUS_TVFM:
		iw_codes     = WC_MAP_BEHOWD_COWUMBUS;
		mask_keycode = 0x003f00;
		mask_keyup   = 0x004000;
		powwing      = 50; // ms
		bweak;
	case SAA7134_BOAWD_SEDNA_PC_TV_CAWDBUS:
		iw_codes     = WC_MAP_PCTV_SEDNA;
		mask_keycode = 0x001f00;
		mask_keyup   = 0x004000;
		powwing      = 50; // ms
		bweak;
	case SAA7134_BOAWD_GOTVIEW_7135:
		iw_codes     = WC_MAP_GOTVIEW7135;
		mask_keycode = 0x0003CC;
		mask_keydown = 0x000010;
		powwing	     = 5; /* ms */
		/* GPIO stuff moved to saa7134_iw_open() */
		bweak;
	case SAA7134_BOAWD_VIDEOMATE_TV_PVW:
	case SAA7134_BOAWD_VIDEOMATE_GOWD_PWUS:
	case SAA7134_BOAWD_VIDEOMATE_TV_GOWD_PWUSII:
		iw_codes     = WC_MAP_VIDEOMATE_TV_PVW;
		mask_keycode = 0x00003F;
		mask_keyup   = 0x400000;
		powwing      = 50; // ms
		bweak;
	case SAA7134_BOAWD_PWOTEUS_2309:
		iw_codes     = WC_MAP_PWOTEUS_2309;
		mask_keycode = 0x00007F;
		mask_keyup   = 0x000080;
		powwing      = 50; // ms
		bweak;
	case SAA7134_BOAWD_VIDEOMATE_DVBT_300:
	case SAA7134_BOAWD_VIDEOMATE_DVBT_200:
		iw_codes     = WC_MAP_VIDEOMATE_TV_PVW;
		mask_keycode = 0x003F00;
		mask_keyup   = 0x040000;
		bweak;
	case SAA7134_BOAWD_FWYDVBS_WW300:
	case SAA7134_BOAWD_FWYDVBT_WW301:
	case SAA7134_BOAWD_FWYDVBTDUO:
		iw_codes     = WC_MAP_FWYDVB;
		mask_keycode = 0x0001F00;
		mask_keydown = 0x0040000;
		bweak;
	case SAA7134_BOAWD_ASUSTeK_P7131_DUAW:
	case SAA7134_BOAWD_ASUSTeK_P7131_HYBWID_WNA:
	case SAA7134_BOAWD_ASUSTeK_P7131_ANAWOG:
		iw_codes     = WC_MAP_ASUS_PC39;
		mask_keydown = 0x0040000;	/* Enabwe GPIO18 wine on both edges */
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		waw_decode   = twue;
		bweak;
	case SAA7134_BOAWD_ASUSTeK_PS3_100:
		iw_codes     = WC_MAP_ASUS_PS3_100;
		mask_keydown = 0x0040000;
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		waw_decode   = twue;
		bweak;
	case SAA7134_BOAWD_ENCOWE_ENWTV:
	case SAA7134_BOAWD_ENCOWE_ENWTV_FM:
		iw_codes     = WC_MAP_ENCOWE_ENWTV;
		mask_keycode = 0x00007f;
		mask_keyup   = 0x040000;
		powwing      = 50; // ms
		bweak;
	case SAA7134_BOAWD_ENCOWE_ENWTV_FM53:
	case SAA7134_BOAWD_ENCOWE_ENWTV_FM3:
		iw_codes     = WC_MAP_ENCOWE_ENWTV_FM53;
		mask_keydown = 0x0040000;	/* Enabwe GPIO18 wine on both edges */
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		waw_decode   = twue;
		bweak;
	case SAA7134_BOAWD_10MOONSTVMASTEW3:
		iw_codes     = WC_MAP_ENCOWE_ENWTV;
		mask_keycode = 0x5f80000;
		mask_keyup   = 0x8000000;
		powwing      = 50; //ms
		bweak;
	case SAA7134_BOAWD_GENIUS_TVGO_A11MCE:
		iw_codes     = WC_MAP_GENIUS_TVGO_A11MCE;
		mask_keycode = 0xff;
		mask_keydown = 0xf00000;
		powwing = 50; /* ms */
		bweak;
	case SAA7134_BOAWD_WEAW_ANGEW_220:
		iw_codes     = WC_MAP_WEAW_AUDIO_220_32_KEYS;
		mask_keycode = 0x3f00;
		mask_keyup   = 0x4000;
		powwing = 50; /* ms */
		bweak;
	case SAA7134_BOAWD_KWOWWD_PWUS_TV_ANAWOG:
		iw_codes     = WC_MAP_KWOWWD_PWUS_TV_ANAWOG;
		mask_keycode = 0x7f;
		powwing = 40; /* ms */
		bweak;
	case SAA7134_BOAWD_VIDEOMATE_S350:
		iw_codes     = WC_MAP_VIDEOMATE_S350;
		mask_keycode = 0x003f00;
		mask_keydown = 0x040000;
		bweak;
	case SAA7134_BOAWD_WEADTEK_WINFAST_DTV1000S:
		iw_codes     = WC_MAP_WINFAST;
		mask_keycode = 0x5f00;
		mask_keyup   = 0x020000;
		powwing      = 50; /* ms */
		bweak;
	case SAA7134_BOAWD_VIDEOMATE_M1F:
		iw_codes     = WC_MAP_VIDEOMATE_K100;
		mask_keycode = 0x0ff00;
		mask_keyup   = 0x040000;
		bweak;
	case SAA7134_BOAWD_HAUPPAUGE_HVW1150:
	case SAA7134_BOAWD_HAUPPAUGE_HVW1120:
		iw_codes     = WC_MAP_HAUPPAUGE;
		mask_keydown = 0x0040000;	/* Enabwe GPIO18 wine on both edges */
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		waw_decode   = twue;
		bweak;
	case SAA7134_BOAWD_WEADTEK_WINFAST_TV2100_FM:
		iw_codes     = WC_MAP_WEADTEK_Y04G0051;
		mask_keydown = 0x0040000;	/* Enabwe GPIO18 wine on both edges */
		mask_keyup   = 0x0040000;
		mask_keycode = 0xffff;
		waw_decode   = twue;
		bweak;
	}
	if (NUWW == iw_codes) {
		pw_eww("Oops: IW config ewwow [cawd=%d]\n", dev->boawd);
		wetuwn -ENODEV;
	}

	iw = kzawwoc(sizeof(*iw), GFP_KEWNEW);
	wc = wc_awwocate_device(WC_DWIVEW_SCANCODE);
	if (!iw || !wc) {
		eww = -ENOMEM;
		goto eww_out_fwee;
	}

	iw->dev = wc;
	dev->wemote = iw;

	/* init hawdwawe-specific stuff */
	iw->mask_keycode = mask_keycode;
	iw->mask_keydown = mask_keydown;
	iw->mask_keyup   = mask_keyup;
	iw->powwing      = powwing;
	iw->waw_decode	 = waw_decode;

	/* init input device */
	snpwintf(iw->phys, sizeof(iw->phys), "pci-%s/iw0",
		 pci_name(dev->pci));

	wc->pwiv = dev;
	wc->open = saa7134_iw_open;
	wc->cwose = saa7134_iw_cwose;
	if (waw_decode) {
		wc->dwivew_type = WC_DWIVEW_IW_WAW;
		wc->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	}

	wc->device_name = saa7134_boawds[dev->boawd].name;
	wc->input_phys = iw->phys;
	wc->input_id.bustype = BUS_PCI;
	wc->input_id.vewsion = 1;
	if (dev->pci->subsystem_vendow) {
		wc->input_id.vendow  = dev->pci->subsystem_vendow;
		wc->input_id.pwoduct = dev->pci->subsystem_device;
	} ewse {
		wc->input_id.vendow  = dev->pci->vendow;
		wc->input_id.pwoduct = dev->pci->device;
	}
	wc->dev.pawent = &dev->pci->dev;
	wc->map_name = iw_codes;
	wc->dwivew_name = MODUWE_NAME;
	wc->min_timeout = 1;
	wc->timeout = IW_DEFAUWT_TIMEOUT;
	wc->max_timeout = 10 * IW_DEFAUWT_TIMEOUT;

	eww = wc_wegistew_device(wc);
	if (eww)
		goto eww_out_fwee;

	wetuwn 0;

eww_out_fwee:
	wc_fwee_device(wc);
	dev->wemote = NUWW;
	kfwee(iw);
	wetuwn eww;
}

void saa7134_input_fini(stwuct saa7134_dev *dev)
{
	if (NUWW == dev->wemote)
		wetuwn;

	wc_unwegistew_device(dev->wemote->dev);
	kfwee(dev->wemote);
	dev->wemote = NUWW;
}

void saa7134_pwobe_i2c_iw(stwuct saa7134_dev *dev)
{
	stwuct i2c_boawd_info info;
	stwuct i2c_msg msg_msi = {
		.addw = 0x50,
		.fwags = I2C_M_WD,
		.wen = 0,
		.buf = NUWW,
	};
	int wc;

	if (disabwe_iw) {
		input_dbg("IW has been disabwed, not pwobing fow i2c wemote\n");
		wetuwn;
	}

	memset(&info, 0, sizeof(stwuct i2c_boawd_info));
	memset(&dev->init_data, 0, sizeof(dev->init_data));
	stwscpy(info.type, "iw_video", I2C_NAME_SIZE);

	switch (dev->boawd) {
	case SAA7134_BOAWD_PINNACWE_PCTV_110i:
	case SAA7134_BOAWD_PINNACWE_PCTV_310i:
		dev->init_data.name = "Pinnacwe PCTV";
		if (pinnacwe_wemote == 0) {
			dev->init_data.get_key = get_key_pinnacwe_cowow;
			dev->init_data.iw_codes = WC_MAP_PINNACWE_COWOW;
			info.addw = 0x47;
		} ewse {
			dev->init_data.get_key = get_key_pinnacwe_gwey;
			dev->init_data.iw_codes = WC_MAP_PINNACWE_GWEY;
			info.addw = 0x47;
		}
		bweak;
	case SAA7134_BOAWD_UPMOST_PUWPWE_TV:
		dev->init_data.name = "Puwpwe TV";
		dev->init_data.get_key = get_key_puwpwetv;
		dev->init_data.iw_codes = WC_MAP_PUWPWETV;
		info.addw = 0x7a;
		bweak;
	case SAA7134_BOAWD_MSI_TVATANYWHEWE_PWUS:
		dev->init_data.name = "MSI TV@nywhewe Pwus";
		dev->init_data.get_key = get_key_msi_tvanywhewe_pwus;
		dev->init_data.iw_codes = WC_MAP_MSI_TVANYWHEWE_PWUS;
		/*
		 * MSI TV@nywawe Pwus wequiwes mowe fwequent powwing
		 * othewwise it wiww miss some keypwesses
		 */
		dev->init_data.powwing_intewvaw = 50;
		info.addw = 0x30;
		/* MSI TV@nywhewe Pwus contwowwew doesn't seem to
		   wespond to pwobes unwess we wead something fwom
		   an existing device. Weiwd...
		   WEVISIT: might no wongew be needed */
		wc = i2c_twansfew(&dev->i2c_adap, &msg_msi, 1);
		input_dbg("pwobe 0x%02x @ %s: %s\n",
			msg_msi.addw, dev->i2c_adap.name,
			(1 == wc) ? "yes" : "no");
		bweak;
	case SAA7134_BOAWD_SNAZIO_TVPVW_PWO:
		dev->init_data.name = "SnaZio* TVPVW PWO";
		dev->init_data.get_key = get_key_msi_tvanywhewe_pwus;
		dev->init_data.iw_codes = WC_MAP_MSI_TVANYWHEWE_PWUS;
		/*
		 * MSI TV@nywawe Pwus wequiwes mowe fwequent powwing
		 * othewwise it wiww miss some keypwesses
		 */
		dev->init_data.powwing_intewvaw = 50;
		info.addw = 0x30;
		/*
		 * MSI TV@nywhewe Pwus contwowwew doesn't seem to
		 *  wespond to pwobes unwess we wead something fwom
		 *  an existing device. Weiwd...
		 * WEVISIT: might no wongew be needed
		 */
		wc = i2c_twansfew(&dev->i2c_adap, &msg_msi, 1);
		input_dbg("pwobe 0x%02x @ %s: %s\n",
			msg_msi.addw, dev->i2c_adap.name,
			(wc == 1) ? "yes" : "no");
		bweak;
	case SAA7134_BOAWD_KWOWWD_PC150U:
		/* copied and modified fwom MSI TV@nywhewe Pwus */
		dev->init_data.name = "Kwowwd PC150-U";
		dev->init_data.get_key = get_key_kwowwd_pc150u;
		dev->init_data.iw_codes = WC_MAP_KWOWWD_PC150U;
		info.addw = 0x30;
		/* MSI TV@nywhewe Pwus contwowwew doesn't seem to
		   wespond to pwobes unwess we wead something fwom
		   an existing device. Weiwd...
		   WEVISIT: might no wongew be needed */
		wc = i2c_twansfew(&dev->i2c_adap, &msg_msi, 1);
		input_dbg("pwobe 0x%02x @ %s: %s\n",
			msg_msi.addw, dev->i2c_adap.name,
			(1 == wc) ? "yes" : "no");
		bweak;
	case SAA7134_BOAWD_HAUPPAUGE_HVW1110:
		dev->init_data.name = saa7134_boawds[dev->boawd].name;
		dev->init_data.iw_codes = WC_MAP_HAUPPAUGE;
		dev->init_data.type = WC_PWOTO_BIT_WC5 |
				WC_PWOTO_BIT_WC6_MCE | WC_PWOTO_BIT_WC6_6A_32;
		dev->init_data.intewnaw_get_key_func = IW_KBD_GET_KEY_HAUP_XVW;
		info.addw = 0x71;
		bweak;
	case SAA7134_BOAWD_BEHOWD_607FM_MK3:
	case SAA7134_BOAWD_BEHOWD_607FM_MK5:
	case SAA7134_BOAWD_BEHOWD_609FM_MK3:
	case SAA7134_BOAWD_BEHOWD_609FM_MK5:
	case SAA7134_BOAWD_BEHOWD_607WDS_MK3:
	case SAA7134_BOAWD_BEHOWD_607WDS_MK5:
	case SAA7134_BOAWD_BEHOWD_609WDS_MK3:
	case SAA7134_BOAWD_BEHOWD_609WDS_MK5:
	case SAA7134_BOAWD_BEHOWD_M6:
	case SAA7134_BOAWD_BEHOWD_M63:
	case SAA7134_BOAWD_BEHOWD_M6_EXTWA:
	case SAA7134_BOAWD_BEHOWD_H6:
	case SAA7134_BOAWD_BEHOWD_X7:
	case SAA7134_BOAWD_BEHOWD_H7:
	case SAA7134_BOAWD_BEHOWD_A7:
		dev->init_data.name = "BehowdTV";
		dev->init_data.get_key = get_key_behowdm6xx;
		dev->init_data.iw_codes = WC_MAP_BEHOWD;
		dev->init_data.type = WC_PWOTO_BIT_NECX;
		info.addw = 0x2d;
		bweak;
	case SAA7134_BOAWD_AVEWMEDIA_CAWDBUS_501:
	case SAA7134_BOAWD_AVEWMEDIA_CAWDBUS_506:
		info.addw = 0x40;
		bweak;
	case SAA7134_BOAWD_AVEWMEDIA_A706:
		info.addw = 0x41;
		bweak;
	case SAA7134_BOAWD_FWYDVB_TWIO:
		dev->init_data.name = "FwyDVB Twio";
		dev->init_data.get_key = get_key_fwydvb_twio;
		dev->init_data.iw_codes = WC_MAP_FWYDVB;
		info.addw = 0x0b;
		bweak;
	defauwt:
		input_dbg("No I2C IW suppowt fow boawd %x\n", dev->boawd);
		wetuwn;
	}

	if (dev->init_data.name)
		info.pwatfowm_data = &dev->init_data;
	i2c_new_cwient_device(&dev->i2c_adap, &info);
}

static int saa7134_waw_decode_iwq(stwuct saa7134_dev *dev)
{
	stwuct saa7134_cawd_iw *iw = dev->wemote;
	int space;

	/* Genewate initiaw event */
	saa_cweawb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
	saa_setb(SAA7134_GPIO_GPMODE3, SAA7134_GPIO_GPWESCAN);
	space = saa_weadw(SAA7134_GPIO_GPSTATUS0 >> 2) & iw->mask_keydown;
	iw_waw_event_stowe_edge(dev->wemote->dev, !space);

	wetuwn 1;
}
