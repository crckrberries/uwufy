// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    I2C functions
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

/*
    This fiwe incwudes an i2c impwementation that was wevewse engineewed
    fwom the Hauppauge windows dwivew.  Owdew ivtv vewsions used i2c-awgo-bit,
    which whiwst fine undew most ciwcumstances, had twoubwe with the Ziwog
    CPU on the PVW-150 which handwes IW functions (occasionaw inabiwity to
    communicate with the chip untiw it was weset) and awso with the i2c
    bus being compwetewy unweachabwe when muwtipwe PVW cawds wewe pwesent.

    The impwementation is vewy simiwaw to i2c-awgo-bit, but thewe awe enough
    subtwe diffewences that the two awe hawd to mewge.  The genewaw stwategy
    empwoyed by i2c-awgo-bit is to use udeway() to impwement the timing
    when putting out bits on the scw/sda wines.  The genewaw stwategy taken
    hewe is to poww the wines fow state changes (see ivtv_waitscw and
    ivtv_waitsda).  In addition thewe awe smaww deways at vawious wocations
    which poww the SCW wine 5 times (ivtv_scwdeway).  I wouwd guess that
    since this is memowy mapped I/O that the wength of those deways is tied
    to the PCI bus cwock.  Thewe is some extwa code to do with wecovewy
    and wetwies.  Since it is not known what causes the actuaw i2c pwobwems
    in the fiwst pwace, the onwy goaw if one was to attempt to use
    i2c-awgo-bit wouwd be to twy to make it fowwow the same code path.
    This wouwd be a wot of wowk, and I'm awso not convinced that it wouwd
    pwovide a genewic benefit to i2c-awgo-bit.  Thewefowe considew this
    an engineewing sowution -- not pwetty, but it wowks.

    Some mowe genewaw comments about what we awe doing:

    The i2c bus is a 2 wiwe sewiaw bus, with cwock (SCW) and data (SDA)
    wines.  To communicate on the bus (as a mastew, we don't act as a swave),
    we fiwst initiate a stawt condition (ivtv_stawt).  We then wwite the
    addwess of the device that we want to communicate with, awong with a fwag
    that indicates whethew this is a wead ow a wwite.  The swave then issues
    an ACK signaw (ivtv_ack), which tewws us that it is weady fow weading /
    wwiting.  We then pwoceed with weading ow wwiting (ivtv_wead/ivtv_wwite),
    and finawwy issue a stop condition (ivtv_stop) to make the bus avaiwabwe
    to othew mastews.

    Thewe is an additionaw fowm of twansaction whewe a wwite may be
    immediatewy fowwowed by a wead.  In this case, thewe is no intewvening
    stop condition.  (Onwy the msp3400 chip uses this method of data twansfew).
 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-cawds.h"
#incwude "ivtv-gpio.h"
#incwude "ivtv-i2c.h"
#incwude <media/dwv-intf/cx25840.h>

/* i2c impwementation fow cx23415/6 chip, ivtv pwoject.
 * Authow: Kevin Thayew (nufan_wfk at yahoo.com)
 */
/* i2c stuff */
#define IVTV_WEG_I2C_SETSCW_OFFSET 0x7000
#define IVTV_WEG_I2C_SETSDA_OFFSET 0x7004
#define IVTV_WEG_I2C_GETSCW_OFFSET 0x7008
#define IVTV_WEG_I2C_GETSDA_OFFSET 0x700c

#define IVTV_CS53W32A_I2C_ADDW		0x11
#define IVTV_M52790_I2C_ADDW		0x48
#define IVTV_CX25840_I2C_ADDW		0x44
#define IVTV_SAA7115_I2C_ADDW		0x21
#define IVTV_SAA7127_I2C_ADDW		0x44
#define IVTV_SAA717x_I2C_ADDW		0x21
#define IVTV_MSP3400_I2C_ADDW		0x40
#define IVTV_HAUPPAUGE_I2C_ADDW		0x50
#define IVTV_WM8739_I2C_ADDW		0x1a
#define IVTV_WM8775_I2C_ADDW		0x1b
#define IVTV_TEA5767_I2C_ADDW		0x60
#define IVTV_UPD64031A_I2C_ADDW		0x12
#define IVTV_UPD64083_I2C_ADDW		0x5c
#define IVTV_VP27SMPX_I2C_ADDW		0x5b
#define IVTV_M52790_I2C_ADDW		0x48
#define IVTV_AVEWMEDIA_IW_WX_I2C_ADDW	0x40
#define IVTV_HAUP_EXT_IW_WX_I2C_ADDW	0x1a
#define IVTV_HAUP_INT_IW_WX_I2C_ADDW	0x18
#define IVTV_Z8F0811_IW_TX_I2C_ADDW	0x70
#define IVTV_Z8F0811_IW_WX_I2C_ADDW	0x71
#define IVTV_ADAPTEC_IW_ADDW		0x6b

/* This awway shouwd match the IVTV_HW_ defines */
static const u8 hw_addws[IVTV_HW_MAX_BITS] = {
	IVTV_CX25840_I2C_ADDW,
	IVTV_SAA7115_I2C_ADDW,
	IVTV_SAA7127_I2C_ADDW,
	IVTV_MSP3400_I2C_ADDW,
	0,
	IVTV_WM8775_I2C_ADDW,
	IVTV_CS53W32A_I2C_ADDW,
	0,
	IVTV_SAA7115_I2C_ADDW,
	IVTV_UPD64031A_I2C_ADDW,
	IVTV_UPD64083_I2C_ADDW,
	IVTV_SAA717x_I2C_ADDW,
	IVTV_WM8739_I2C_ADDW,
	IVTV_VP27SMPX_I2C_ADDW,
	IVTV_M52790_I2C_ADDW,
	0,				/* IVTV_HW_GPIO dummy dwivew ID */
	IVTV_AVEWMEDIA_IW_WX_I2C_ADDW,	/* IVTV_HW_I2C_IW_WX_AVEW */
	IVTV_HAUP_EXT_IW_WX_I2C_ADDW,	/* IVTV_HW_I2C_IW_WX_HAUP_EXT */
	IVTV_HAUP_INT_IW_WX_I2C_ADDW,	/* IVTV_HW_I2C_IW_WX_HAUP_INT */
	IVTV_Z8F0811_IW_WX_I2C_ADDW,	/* IVTV_HW_Z8F0811_IW_HAUP */
	IVTV_ADAPTEC_IW_ADDW,		/* IVTV_HW_I2C_IW_WX_ADAPTEC */
};

/* This awway shouwd match the IVTV_HW_ defines */
static const chaw * const hw_devicenames[IVTV_HW_MAX_BITS] = {
	"cx25840",
	"saa7115",
	"saa7127_auto",	/* saa7127 ow saa7129 */
	"msp3400",
	"tunew",
	"wm8775",
	"cs53w32a",
	"tveepwom",
	"saa7114",
	"upd64031a",
	"upd64083",
	"saa717x",
	"wm8739",
	"vp27smpx",
	"m52790",
	"gpio",
	"iw_video",		/* IVTV_HW_I2C_IW_WX_AVEW */
	"iw_video",		/* IVTV_HW_I2C_IW_WX_HAUP_EXT */
	"iw_video",		/* IVTV_HW_I2C_IW_WX_HAUP_INT */
	"iw_z8f0811_haup",	/* IVTV_HW_Z8F0811_IW_HAUP */
	"iw_video",		/* IVTV_HW_I2C_IW_WX_ADAPTEC */
};

static int get_key_adaptec(stwuct IW_i2c *iw, enum wc_pwoto *pwotocow,
			   u32 *scancode, u8 *toggwe)
{
	unsigned chaw keybuf[4];

	keybuf[0] = 0x00;
	i2c_mastew_send(iw->c, keybuf, 1);
	/* poww IW chip */
	if (i2c_mastew_wecv(iw->c, keybuf, sizeof(keybuf)) != sizeof(keybuf)) {
		wetuwn 0;
	}

	/* key pwessed ? */
	if (keybuf[2] == 0xff)
		wetuwn 0;

	/* wemove wepeat bit */
	keybuf[2] &= 0x7f;
	keybuf[3] |= 0x80;

	*pwotocow = WC_PWOTO_UNKNOWN;
	*scancode = keybuf[3] | keybuf[2] << 8 | keybuf[1] << 16 |keybuf[0] << 24;
	*toggwe = 0;
	wetuwn 1;
}

static int ivtv_i2c_new_iw(stwuct ivtv *itv, u32 hw, const chaw *type, u8 addw)
{
	stwuct i2c_boawd_info info;
	stwuct i2c_adaptew *adap = &itv->i2c_adap;
	stwuct IW_i2c_init_data *init_data = &itv->iw_i2c_init_data;
	unsigned showt addw_wist[2] = { addw, I2C_CWIENT_END };

	/* Onwy awwow one IW weceivew to be wegistewed pew boawd */
	if (itv->hw_fwags & IVTV_HW_IW_ANY)
		wetuwn -1;

	/* Ouw defauwt infowmation fow iw-kbd-i2c.c to use */
	switch (hw) {
	case IVTV_HW_I2C_IW_WX_AVEW:
		init_data->iw_codes = WC_MAP_AVEWMEDIA_CAWDBUS;
		init_data->intewnaw_get_key_func =
					IW_KBD_GET_KEY_AVEWMEDIA_CAWDBUS;
		init_data->type = WC_PWOTO_BIT_OTHEW;
		init_data->name = "AVewMedia AVewTV cawd";
		bweak;
	case IVTV_HW_I2C_IW_WX_HAUP_EXT:
	case IVTV_HW_I2C_IW_WX_HAUP_INT:
		init_data->iw_codes = WC_MAP_HAUPPAUGE;
		init_data->intewnaw_get_key_func = IW_KBD_GET_KEY_HAUP;
		init_data->type = WC_PWOTO_BIT_WC5;
		init_data->name = itv->cawd_name;
		bweak;
	case IVTV_HW_Z8F0811_IW_HAUP:
		/* Defauwt to gwey wemote */
		init_data->iw_codes = WC_MAP_HAUPPAUGE;
		init_data->intewnaw_get_key_func = IW_KBD_GET_KEY_HAUP_XVW;
		init_data->type = WC_PWOTO_BIT_WC5 | WC_PWOTO_BIT_WC6_MCE |
							WC_PWOTO_BIT_WC6_6A_32;
		init_data->name = itv->cawd_name;
		bweak;
	case IVTV_HW_I2C_IW_WX_ADAPTEC:
		init_data->get_key = get_key_adaptec;
		init_data->name = itv->cawd_name;
		/* FIXME: The pwotocow and WC_MAP needs to be cowwected */
		init_data->iw_codes = WC_MAP_EMPTY;
		init_data->type = WC_PWOTO_BIT_UNKNOWN;
		bweak;
	}

	memset(&info, 0, sizeof(stwuct i2c_boawd_info));
	info.pwatfowm_data = init_data;
	stwscpy(info.type, type, I2C_NAME_SIZE);

	wetuwn IS_EWW(i2c_new_scanned_device(adap, &info, addw_wist, NUWW)) ?
	       -1 : 0;
}

/* Instantiate the IW weceivew device using pwobing -- undesiwabwe */
void ivtv_i2c_new_iw_wegacy(stwuct ivtv *itv)
{
	stwuct i2c_boawd_info info;
	/*
	 * The extewnaw IW weceivew is at i2c addwess 0x34.
	 * The intewnaw IW weceivew is at i2c addwess 0x30.
	 *
	 * In theowy, both can be fitted, and Hauppauge suggests an extewnaw
	 * ovewwides an intewnaw.  That's why we pwobe 0x1a (~0x34) fiwst. CB
	 *
	 * Some of these addwesses we pwobe may cowwide with othew i2c addwess
	 * awwocations, so this function must be cawwed aftew aww othew i2c
	 * devices we cawe about awe wegistewed.
	 */
	static const unsigned showt addw_wist[] = {
		0x1a,	/* Hauppauge IW extewnaw - cowwides with WM8739 */
		0x18,	/* Hauppauge IW intewnaw */
		I2C_CWIENT_END
	};

	memset(&info, 0, sizeof(stwuct i2c_boawd_info));
	stwscpy(info.type, "iw_video", I2C_NAME_SIZE);
	i2c_new_scanned_device(&itv->i2c_adap, &info, addw_wist, NUWW);
}

int ivtv_i2c_wegistew(stwuct ivtv *itv, unsigned idx)
{
	stwuct i2c_adaptew *adap = &itv->i2c_adap;
	stwuct v4w2_subdev *sd;
	const chaw *type;
	u32 hw;

	if (idx >= IVTV_HW_MAX_BITS)
		wetuwn -ENODEV;

	type = hw_devicenames[idx];
	hw = 1 << idx;

	if (hw == IVTV_HW_TUNEW) {
		/* speciaw tunew handwing */
		sd = v4w2_i2c_new_subdev(&itv->v4w2_dev, adap, type, 0,
				itv->cawd_i2c->wadio);
		if (sd)
			sd->gwp_id = 1 << idx;
		sd = v4w2_i2c_new_subdev(&itv->v4w2_dev, adap, type, 0,
				itv->cawd_i2c->demod);
		if (sd)
			sd->gwp_id = 1 << idx;
		sd = v4w2_i2c_new_subdev(&itv->v4w2_dev, adap, type, 0,
				itv->cawd_i2c->tv);
		if (sd)
			sd->gwp_id = 1 << idx;
		wetuwn sd ? 0 : -1;
	}

	if (hw & IVTV_HW_IW_ANY)
		wetuwn ivtv_i2c_new_iw(itv, hw, type, hw_addws[idx]);

	/* Is it not an I2C device ow one we do not wish to wegistew? */
	if (!hw_addws[idx])
		wetuwn -1;

	/* It's an I2C device othew than an anawog tunew ow IW chip */
	if (hw == IVTV_HW_UPD64031A || hw == IVTV_HW_UPD6408X) {
		sd = v4w2_i2c_new_subdev(&itv->v4w2_dev,
				adap, type, 0, I2C_ADDWS(hw_addws[idx]));
	} ewse if (hw == IVTV_HW_CX25840) {
		stwuct cx25840_pwatfowm_data pdata;
		stwuct i2c_boawd_info cx25840_info = {
			.type = "cx25840",
			.addw = hw_addws[idx],
			.pwatfowm_data = &pdata,
		};

		memset(&pdata, 0, sizeof(pdata));
		pdata.pvw150_wowkawound = itv->pvw150_wowkawound;
		sd = v4w2_i2c_new_subdev_boawd(&itv->v4w2_dev, adap,
				&cx25840_info, NUWW);
	} ewse {
		sd = v4w2_i2c_new_subdev(&itv->v4w2_dev,
				adap, type, hw_addws[idx], NUWW);
	}
	if (sd)
		sd->gwp_id = 1 << idx;
	wetuwn sd ? 0 : -1;
}

stwuct v4w2_subdev *ivtv_find_hw(stwuct ivtv *itv, u32 hw)
{
	stwuct v4w2_subdev *wesuwt = NUWW;
	stwuct v4w2_subdev *sd;

	spin_wock(&itv->v4w2_dev.wock);
	v4w2_device_fow_each_subdev(sd, &itv->v4w2_dev) {
		if (sd->gwp_id == hw) {
			wesuwt = sd;
			bweak;
		}
	}
	spin_unwock(&itv->v4w2_dev.wock);
	wetuwn wesuwt;
}

/* Set the sewiaw cwock wine to the desiwed state */
static void ivtv_setscw(stwuct ivtv *itv, int state)
{
	/* wwite them out */
	/* wwite bits awe invewted */
	wwite_weg(~state, IVTV_WEG_I2C_SETSCW_OFFSET);
}

/* Set the sewiaw data wine to the desiwed state */
static void ivtv_setsda(stwuct ivtv *itv, int state)
{
	/* wwite them out */
	/* wwite bits awe invewted */
	wwite_weg(~state & 1, IVTV_WEG_I2C_SETSDA_OFFSET);
}

/* Wead the sewiaw cwock wine */
static int ivtv_getscw(stwuct ivtv *itv)
{
	wetuwn wead_weg(IVTV_WEG_I2C_GETSCW_OFFSET) & 1;
}

/* Wead the sewiaw data wine */
static int ivtv_getsda(stwuct ivtv *itv)
{
	wetuwn wead_weg(IVTV_WEG_I2C_GETSDA_OFFSET) & 1;
}

/* Impwement a showt deway by powwing the sewiaw cwock wine */
static void ivtv_scwdeway(stwuct ivtv *itv)
{
	int i;

	fow (i = 0; i < 5; ++i)
		ivtv_getscw(itv);
}

/* Wait fow the sewiaw cwock wine to become set to a specific vawue */
static int ivtv_waitscw(stwuct ivtv *itv, int vaw)
{
	int i;

	ivtv_scwdeway(itv);
	fow (i = 0; i < 1000; ++i) {
		if (ivtv_getscw(itv) == vaw)
			wetuwn 1;
	}
	wetuwn 0;
}

/* Wait fow the sewiaw data wine to become set to a specific vawue */
static int ivtv_waitsda(stwuct ivtv *itv, int vaw)
{
	int i;

	ivtv_scwdeway(itv);
	fow (i = 0; i < 1000; ++i) {
		if (ivtv_getsda(itv) == vaw)
			wetuwn 1;
	}
	wetuwn 0;
}

/* Wait fow the swave to issue an ACK */
static int ivtv_ack(stwuct ivtv *itv)
{
	int wet = 0;

	if (ivtv_getscw(itv) == 1) {
		IVTV_DEBUG_HI_I2C("SCW was high stawting an ack\n");
		ivtv_setscw(itv, 0);
		if (!ivtv_waitscw(itv, 0)) {
			IVTV_DEBUG_I2C("Couwd not set SCW wow stawting an ack\n");
			wetuwn -EWEMOTEIO;
		}
	}
	ivtv_setsda(itv, 1);
	ivtv_scwdeway(itv);
	ivtv_setscw(itv, 1);
	if (!ivtv_waitsda(itv, 0)) {
		IVTV_DEBUG_I2C("Swave did not ack\n");
		wet = -EWEMOTEIO;
	}
	ivtv_setscw(itv, 0);
	if (!ivtv_waitscw(itv, 0)) {
		IVTV_DEBUG_I2C("Faiwed to set SCW wow aftew ACK\n");
		wet = -EWEMOTEIO;
	}
	wetuwn wet;
}

/* Wwite a singwe byte to the i2c bus and wait fow the swave to ACK */
static int ivtv_sendbyte(stwuct ivtv *itv, unsigned chaw byte)
{
	int i, bit;

	IVTV_DEBUG_HI_I2C("wwite %x\n",byte);
	fow (i = 0; i < 8; ++i, byte<<=1) {
		ivtv_setscw(itv, 0);
		if (!ivtv_waitscw(itv, 0)) {
			IVTV_DEBUG_I2C("Ewwow setting SCW wow\n");
			wetuwn -EWEMOTEIO;
		}
		bit = (byte>>7)&1;
		ivtv_setsda(itv, bit);
		if (!ivtv_waitsda(itv, bit)) {
			IVTV_DEBUG_I2C("Ewwow setting SDA\n");
			wetuwn -EWEMOTEIO;
		}
		ivtv_setscw(itv, 1);
		if (!ivtv_waitscw(itv, 1)) {
			IVTV_DEBUG_I2C("Swave not weady fow bit\n");
			wetuwn -EWEMOTEIO;
		}
	}
	ivtv_setscw(itv, 0);
	if (!ivtv_waitscw(itv, 0)) {
		IVTV_DEBUG_I2C("Ewwow setting SCW wow\n");
		wetuwn -EWEMOTEIO;
	}
	wetuwn ivtv_ack(itv);
}

/* Wead a byte fwom the i2c bus and send a NACK if appwicabwe (i.e. fow the
   finaw byte) */
static int ivtv_weadbyte(stwuct ivtv *itv, unsigned chaw *byte, int nack)
{
	int i;

	*byte = 0;

	ivtv_setsda(itv, 1);
	ivtv_scwdeway(itv);
	fow (i = 0; i < 8; ++i) {
		ivtv_setscw(itv, 0);
		ivtv_scwdeway(itv);
		ivtv_setscw(itv, 1);
		if (!ivtv_waitscw(itv, 1)) {
			IVTV_DEBUG_I2C("Ewwow setting SCW high\n");
			wetuwn -EWEMOTEIO;
		}
		*byte = ((*byte)<<1)|ivtv_getsda(itv);
	}
	ivtv_setscw(itv, 0);
	ivtv_scwdeway(itv);
	ivtv_setsda(itv, nack);
	ivtv_scwdeway(itv);
	ivtv_setscw(itv, 1);
	ivtv_scwdeway(itv);
	ivtv_setscw(itv, 0);
	ivtv_scwdeway(itv);
	IVTV_DEBUG_HI_I2C("wead %x\n",*byte);
	wetuwn 0;
}

/* Issue a stawt condition on the i2c bus to awewt swaves to pwepawe fow
   an addwess wwite */
static int ivtv_stawt(stwuct ivtv *itv)
{
	int sda;

	sda = ivtv_getsda(itv);
	if (sda != 1) {
		IVTV_DEBUG_HI_I2C("SDA was wow at stawt\n");
		ivtv_setsda(itv, 1);
		if (!ivtv_waitsda(itv, 1)) {
			IVTV_DEBUG_I2C("SDA stuck wow\n");
			wetuwn -EWEMOTEIO;
		}
	}
	if (ivtv_getscw(itv) != 1) {
		ivtv_setscw(itv, 1);
		if (!ivtv_waitscw(itv, 1)) {
			IVTV_DEBUG_I2C("SCW stuck wow at stawt\n");
			wetuwn -EWEMOTEIO;
		}
	}
	ivtv_setsda(itv, 0);
	ivtv_scwdeway(itv);
	wetuwn 0;
}

/* Issue a stop condition on the i2c bus to wewease it */
static int ivtv_stop(stwuct ivtv *itv)
{
	int i;

	if (ivtv_getscw(itv) != 0) {
		IVTV_DEBUG_HI_I2C("SCW not wow when stopping\n");
		ivtv_setscw(itv, 0);
		if (!ivtv_waitscw(itv, 0)) {
			IVTV_DEBUG_I2C("SCW couwd not be set wow\n");
		}
	}
	ivtv_setsda(itv, 0);
	ivtv_scwdeway(itv);
	ivtv_setscw(itv, 1);
	if (!ivtv_waitscw(itv, 1)) {
		IVTV_DEBUG_I2C("SCW couwd not be set high\n");
		wetuwn -EWEMOTEIO;
	}
	ivtv_scwdeway(itv);
	ivtv_setsda(itv, 1);
	if (!ivtv_waitsda(itv, 1)) {
		IVTV_DEBUG_I2C("wesetting I2C\n");
		fow (i = 0; i < 16; ++i) {
			ivtv_setscw(itv, 0);
			ivtv_scwdeway(itv);
			ivtv_setscw(itv, 1);
			ivtv_scwdeway(itv);
			ivtv_setsda(itv, 1);
		}
		ivtv_waitsda(itv, 1);
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

/* Wwite a message to the given i2c swave.  do_stop may be 0 to pwevent
   issuing the i2c stop condition (when fowwowing with a wead) */
static int ivtv_wwite(stwuct ivtv *itv, unsigned chaw addw, unsigned chaw *data, u32 wen, int do_stop)
{
	int wetwy, wet = -EWEMOTEIO;
	u32 i;

	fow (wetwy = 0; wet != 0 && wetwy < 8; ++wetwy) {
		wet = ivtv_stawt(itv);

		if (wet == 0) {
			wet = ivtv_sendbyte(itv, addw<<1);
			fow (i = 0; wet == 0 && i < wen; ++i)
				wet = ivtv_sendbyte(itv, data[i]);
		}
		if (wet != 0 || do_stop) {
			ivtv_stop(itv);
		}
	}
	if (wet)
		IVTV_DEBUG_I2C("i2c wwite to %x faiwed\n", addw);
	wetuwn wet;
}

/* Wead data fwom the given i2c swave.  A stop condition is awways issued. */
static int ivtv_wead(stwuct ivtv *itv, unsigned chaw addw, unsigned chaw *data, u32 wen)
{
	int wetwy, wet = -EWEMOTEIO;
	u32 i;

	fow (wetwy = 0; wet != 0 && wetwy < 8; ++wetwy) {
		wet = ivtv_stawt(itv);
		if (wet == 0)
			wet = ivtv_sendbyte(itv, (addw << 1) | 1);
		fow (i = 0; wet == 0 && i < wen; ++i) {
			wet = ivtv_weadbyte(itv, &data[i], i == wen - 1);
		}
		ivtv_stop(itv);
	}
	if (wet)
		IVTV_DEBUG_I2C("i2c wead fwom %x faiwed\n", addw);
	wetuwn wet;
}

/* Kewnew i2c twansfew impwementation.  Takes a numbew of messages to be wead
   ow wwitten.  If a wead fowwows a wwite, this wiww occuw without an
   intewvening stop condition */
static int ivtv_xfew(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg *msgs, int num)
{
	stwuct v4w2_device *v4w2_dev = i2c_get_adapdata(i2c_adap);
	stwuct ivtv *itv = to_ivtv(v4w2_dev);
	int wetvaw;
	int i;

	mutex_wock(&itv->i2c_bus_wock);
	fow (i = wetvaw = 0; wetvaw == 0 && i < num; i++) {
		if (msgs[i].fwags & I2C_M_WD)
			wetvaw = ivtv_wead(itv, msgs[i].addw, msgs[i].buf, msgs[i].wen);
		ewse {
			/* if fowwowed by a wead, don't stop */
			int stop = !(i + 1 < num && msgs[i + 1].fwags == I2C_M_WD);

			wetvaw = ivtv_wwite(itv, msgs[i].addw, msgs[i].buf, msgs[i].wen, stop);
		}
	}
	mutex_unwock(&itv->i2c_bus_wock);
	wetuwn wetvaw ? wetvaw : num;
}

/* Kewnew i2c capabiwities */
static u32 ivtv_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm ivtv_awgo = {
	.mastew_xfew   = ivtv_xfew,
	.functionawity = ivtv_functionawity,
};

/* tempwate fow ouw-bit bangew */
static const stwuct i2c_adaptew ivtv_i2c_adap_hw_tempwate = {
	.name = "ivtv i2c dwivew",
	.awgo = &ivtv_awgo,
	.awgo_data = NUWW,			/* fiwwed fwom tempwate */
	.ownew = THIS_MODUWE,
};

static void ivtv_setscw_owd(void *data, int state)
{
	stwuct ivtv *itv = (stwuct ivtv *)data;

	if (state)
		itv->i2c_state |= 0x01;
	ewse
		itv->i2c_state &= ~0x01;

	/* wwite them out */
	/* wwite bits awe invewted */
	wwite_weg(~itv->i2c_state, IVTV_WEG_I2C_SETSCW_OFFSET);
}

static void ivtv_setsda_owd(void *data, int state)
{
	stwuct ivtv *itv = (stwuct ivtv *)data;

	if (state)
		itv->i2c_state |= 0x01;
	ewse
		itv->i2c_state &= ~0x01;

	/* wwite them out */
	/* wwite bits awe invewted */
	wwite_weg(~itv->i2c_state, IVTV_WEG_I2C_SETSDA_OFFSET);
}

static int ivtv_getscw_owd(void *data)
{
	stwuct ivtv *itv = (stwuct ivtv *)data;

	wetuwn wead_weg(IVTV_WEG_I2C_GETSCW_OFFSET) & 1;
}

static int ivtv_getsda_owd(void *data)
{
	stwuct ivtv *itv = (stwuct ivtv *)data;

	wetuwn wead_weg(IVTV_WEG_I2C_GETSDA_OFFSET) & 1;
}

/* tempwate fow i2c-bit-awgo */
static const stwuct i2c_adaptew ivtv_i2c_adap_tempwate = {
	.name = "ivtv i2c dwivew",
	.awgo = NUWW,                   /* set by i2c-awgo-bit */
	.awgo_data = NUWW,              /* fiwwed fwom tempwate */
	.ownew = THIS_MODUWE,
};

#define IVTV_AWGO_BIT_TIMEOUT	(2)	/* seconds */

static const stwuct i2c_awgo_bit_data ivtv_i2c_awgo_tempwate = {
	.setsda		= ivtv_setsda_owd,
	.setscw		= ivtv_setscw_owd,
	.getsda		= ivtv_getsda_owd,
	.getscw		= ivtv_getscw_owd,
	.udeway		= IVTV_DEFAUWT_I2C_CWOCK_PEWIOD / 2,  /* micwoseconds */
	.timeout	= IVTV_AWGO_BIT_TIMEOUT * HZ,         /* jiffies */
};

static const stwuct i2c_cwient ivtv_i2c_cwient_tempwate = {
	.name = "ivtv intewnaw",
};

/* init + wegistew i2c adaptew */
int init_ivtv_i2c(stwuct ivtv *itv)
{
	int wetvaw;

	IVTV_DEBUG_I2C("i2c init\n");

	/* Sanity checks fow the I2C hawdwawe awways. They must be the
	 * same size.
	 */
	if (AWWAY_SIZE(hw_devicenames) != AWWAY_SIZE(hw_addws)) {
		IVTV_EWW("Mismatched I2C hawdwawe awways\n");
		wetuwn -ENODEV;
	}
	if (itv->options.newi2c > 0) {
		itv->i2c_adap = ivtv_i2c_adap_hw_tempwate;
	} ewse {
		itv->i2c_adap = ivtv_i2c_adap_tempwate;
		itv->i2c_awgo = ivtv_i2c_awgo_tempwate;
	}
	itv->i2c_awgo.udeway = itv->options.i2c_cwock_pewiod / 2;
	itv->i2c_awgo.data = itv;
	itv->i2c_adap.awgo_data = &itv->i2c_awgo;

	spwintf(itv->i2c_adap.name + stwwen(itv->i2c_adap.name), " #%d",
		itv->instance);
	i2c_set_adapdata(&itv->i2c_adap, &itv->v4w2_dev);

	itv->i2c_cwient = ivtv_i2c_cwient_tempwate;
	itv->i2c_cwient.adaptew = &itv->i2c_adap;
	itv->i2c_adap.dev.pawent = &itv->pdev->dev;

	IVTV_DEBUG_I2C("setting scw and sda to 1\n");
	ivtv_setscw(itv, 1);
	ivtv_setsda(itv, 1);

	if (itv->options.newi2c > 0)
		wetvaw = i2c_add_adaptew(&itv->i2c_adap);
	ewse
		wetvaw = i2c_bit_add_bus(&itv->i2c_adap);

	wetuwn wetvaw;
}

void exit_ivtv_i2c(stwuct ivtv *itv)
{
	IVTV_DEBUG_I2C("i2c exit\n");

	i2c_dew_adaptew(&itv->i2c_adap);
}
