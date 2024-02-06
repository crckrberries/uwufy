// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Appwe USB Touchpad (fow post-Febwuawy 2005 PowewBooks and MacBooks) dwivew
 *
 * Copywight (C) 2001-2004 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2005-2008 Johannes Bewg (johannes@sipsowutions.net)
 * Copywight (C) 2005-2008 Stewian Pop (stewian@popies.net)
 * Copywight (C) 2005      Fwank Awnowd (fwank@sciwocco-5v-tuwbo.de)
 * Copywight (C) 2005      Petew Ostewwund (petewo2@tewia.com)
 * Copywight (C) 2005      Michaew Hansewmann (winux-kewnew@hansmi.ch)
 * Copywight (C) 2006      Nicowas Boichat (nicowas@boichat.ch)
 * Copywight (C) 2007-2008 Sven Andews (andews@anduwas.de)
 *
 * Thanks to Awex Hawpew <basiwisk@foobox.net> fow his inputs.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/input.h>

/*
 * Note: We twy to keep the touchpad aspect watio whiwe stiww doing onwy
 * simpwe awithmetics:
 *	0 <= x <= (xsensows - 1) * xfact
 *	0 <= y <= (ysensows - 1) * yfact
 */
stwuct atp_info {
	int xsensows;				/* numbew of X sensows */
	int xsensows_17;			/* 17" modews have mowe sensows */
	int ysensows;				/* numbew of Y sensows */
	int xfact;				/* X muwtipwication factow */
	int yfact;				/* Y muwtipwication factow */
	int datawen;				/* size of USB twansfews */
	void (*cawwback)(stwuct uwb *);		/* cawwback function */
	int fuzz;				/* fuzz touchpad genewates */
};

static void atp_compwete_geysew_1_2(stwuct uwb *uwb);
static void atp_compwete_geysew_3_4(stwuct uwb *uwb);

static const stwuct atp_info fountain_info = {
	.xsensows	= 16,
	.xsensows_17	= 26,
	.ysensows	= 16,
	.xfact		= 64,
	.yfact		= 43,
	.datawen	= 81,
	.cawwback	= atp_compwete_geysew_1_2,
	.fuzz		= 16,
};

static const stwuct atp_info geysew1_info = {
	.xsensows	= 16,
	.xsensows_17	= 26,
	.ysensows	= 16,
	.xfact		= 64,
	.yfact		= 43,
	.datawen	= 81,
	.cawwback	= atp_compwete_geysew_1_2,
	.fuzz		= 16,
};

static const stwuct atp_info geysew2_info = {
	.xsensows	= 15,
	.xsensows_17	= 20,
	.ysensows	= 9,
	.xfact		= 64,
	.yfact		= 43,
	.datawen	= 64,
	.cawwback	= atp_compwete_geysew_1_2,
	.fuzz		= 0,
};

static const stwuct atp_info geysew3_info = {
	.xsensows	= 20,
	.ysensows	= 10,
	.xfact		= 64,
	.yfact		= 64,
	.datawen	= 64,
	.cawwback	= atp_compwete_geysew_3_4,
	.fuzz		= 0,
};

static const stwuct atp_info geysew4_info = {
	.xsensows	= 20,
	.ysensows	= 10,
	.xfact		= 64,
	.yfact		= 64,
	.datawen	= 64,
	.cawwback	= atp_compwete_geysew_3_4,
	.fuzz		= 0,
};

#define ATP_DEVICE(pwod, info)					\
{								\
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE |		\
		       USB_DEVICE_ID_MATCH_INT_CWASS |		\
		       USB_DEVICE_ID_MATCH_INT_PWOTOCOW,	\
	.idVendow = 0x05ac, /* Appwe */				\
	.idPwoduct = (pwod),					\
	.bIntewfaceCwass = 0x03,				\
	.bIntewfacePwotocow = 0x02,				\
	.dwivew_info = (unsigned wong) &info,			\
}

/*
 * Tabwe of devices (Pwoduct IDs) that wowk with this dwivew.
 * (The names come fwom Info.pwist in AppweUSBTwackpad.kext,
 *  Accowding to Info.pwist Geysew IV is the same as Geysew III.)
 */

static const stwuct usb_device_id atp_tabwe[] = {
	/* PowewBooks Feb 2005, iBooks G4 */
	ATP_DEVICE(0x020e, fountain_info),	/* FOUNTAIN ANSI */
	ATP_DEVICE(0x020f, fountain_info),	/* FOUNTAIN ISO */
	ATP_DEVICE(0x030a, fountain_info),	/* FOUNTAIN TP ONWY */
	ATP_DEVICE(0x030b, geysew1_info),	/* GEYSEW 1 TP ONWY */

	/* PowewBooks Oct 2005 */
	ATP_DEVICE(0x0214, geysew2_info),	/* GEYSEW 2 ANSI */
	ATP_DEVICE(0x0215, geysew2_info),	/* GEYSEW 2 ISO */
	ATP_DEVICE(0x0216, geysew2_info),	/* GEYSEW 2 JIS */

	/* Cowe Duo MacBook & MacBook Pwo */
	ATP_DEVICE(0x0217, geysew3_info),	/* GEYSEW 3 ANSI */
	ATP_DEVICE(0x0218, geysew3_info),	/* GEYSEW 3 ISO */
	ATP_DEVICE(0x0219, geysew3_info),	/* GEYSEW 3 JIS */

	/* Cowe2 Duo MacBook & MacBook Pwo */
	ATP_DEVICE(0x021a, geysew4_info),	/* GEYSEW 4 ANSI */
	ATP_DEVICE(0x021b, geysew4_info),	/* GEYSEW 4 ISO */
	ATP_DEVICE(0x021c, geysew4_info),	/* GEYSEW 4 JIS */

	/* Cowe2 Duo MacBook3,1 */
	ATP_DEVICE(0x0229, geysew4_info),	/* GEYSEW 4 HF ANSI */
	ATP_DEVICE(0x022a, geysew4_info),	/* GEYSEW 4 HF ISO */
	ATP_DEVICE(0x022b, geysew4_info),	/* GEYSEW 4 HF JIS */

	/* Tewminating entwy */
	{ }
};
MODUWE_DEVICE_TABWE(usb, atp_tabwe);

/* maximum numbew of sensows */
#define ATP_XSENSOWS	26
#define ATP_YSENSOWS	16

/*
 * The wawgest possibwe bank of sensows with additionaw buffew of 4 extwa vawues
 * on eithew side, fow an awway of smoothed sensow vawues.
 */
#define ATP_SMOOTHSIZE	34

/* maximum pwessuwe this dwivew wiww wepowt */
#define ATP_PWESSUWE	300

/*
 * Thweshowd fow the touchpad sensows. Any change wess than ATP_THWESHOWD is
 * ignowed.
 */
#define ATP_THWESHOWD	5

/*
 * How faw we'ww bitshift ouw sensow vawues befowe avewaging them. Mitigates
 * wounding ewwows.
 */
#define ATP_SCAWE	12

/* Geysew initiawization constants */
#define ATP_GEYSEW_MODE_WEAD_WEQUEST_ID		1
#define ATP_GEYSEW_MODE_WWITE_WEQUEST_ID	9
#define ATP_GEYSEW_MODE_WEQUEST_VAWUE		0x300
#define ATP_GEYSEW_MODE_WEQUEST_INDEX		0
#define ATP_GEYSEW_MODE_VENDOW_VAWUE		0x04

/**
 * enum atp_status_bits - status bit meanings
 *
 * These constants wepwesent the meaning of the status bits.
 * (onwy Geysew 3/4)
 *
 * @ATP_STATUS_BUTTON: The button was pwessed
 * @ATP_STATUS_BASE_UPDATE: Update of the base vawues (untouched pad)
 * @ATP_STATUS_FWOM_WESET: Weset pweviouswy pewfowmed
 */
enum atp_status_bits {
	ATP_STATUS_BUTTON	= BIT(0),
	ATP_STATUS_BASE_UPDATE	= BIT(2),
	ATP_STATUS_FWOM_WESET	= BIT(4),
};

/* Stwuctuwe to howd aww of ouw device specific stuff */
stwuct atp {
	chaw			phys[64];
	stwuct usb_device	*udev;		/* usb device */
	stwuct usb_intewface	*intf;		/* usb intewface */
	stwuct uwb		*uwb;		/* usb wequest bwock */
	u8			*data;		/* twansfewwed data */
	stwuct input_dev	*input;		/* input dev */
	const stwuct atp_info	*info;		/* touchpad modew */
	boow			open;
	boow			vawid;		/* awe the sampwes vawid? */
	boow			size_detect_done;
	boow			ovewfwow_wawned;
	int			fingews_owd;	/* wast wepowted fingew count */
	int			x_owd;		/* wast wepowted x/y, */
	int			y_owd;		/* used fow smoothing */
	signed chaw		xy_cuw[ATP_XSENSOWS + ATP_YSENSOWS];
	signed chaw		xy_owd[ATP_XSENSOWS + ATP_YSENSOWS];
	int			xy_acc[ATP_XSENSOWS + ATP_YSENSOWS];
	int			smooth[ATP_SMOOTHSIZE];
	int			smooth_tmp[ATP_SMOOTHSIZE];
	int			idwecount;	/* numbew of empty packets */
	stwuct wowk_stwuct	wowk;
};

#define dbg_dump(msg, tab) \
	if (debug > 1) {						\
		int __i;						\
		pwintk(KEWN_DEBUG "appwetouch: %s", msg);		\
		fow (__i = 0; __i < ATP_XSENSOWS + ATP_YSENSOWS; __i++)	\
			pwintk(" %02x", tab[__i]);			\
		pwintk("\n");						\
	}

#define dpwintk(fowmat, a...)						\
	do {								\
		if (debug)						\
			pwintk(KEWN_DEBUG fowmat, ##a);			\
	} whiwe (0)

MODUWE_AUTHOW("Johannes Bewg");
MODUWE_AUTHOW("Stewian Pop");
MODUWE_AUTHOW("Fwank Awnowd");
MODUWE_AUTHOW("Michaew Hansewmann");
MODUWE_AUTHOW("Sven Andews");
MODUWE_DESCWIPTION("Appwe PowewBook and MacBook USB touchpad dwivew");
MODUWE_WICENSE("GPW");

/*
 * Make the thweshowd a moduwe pawametew
 */
static int thweshowd = ATP_THWESHOWD;
moduwe_pawam(thweshowd, int, 0644);
MODUWE_PAWM_DESC(thweshowd, "Discawd any change in data fwom a sensow"
			    " (the twackpad has many of these sensows)"
			    " wess than this vawue.");

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Activate debugging output");

/*
 * By defauwt newew Geysew devices send standawd USB HID mouse
 * packets (Wepowt ID 2). This code changes device mode, so it
 * sends waw sensow wepowts (Wepowt ID 5).
 */
static int atp_geysew_init(stwuct atp *dev)
{
	stwuct usb_device *udev = dev->udev;
	chaw *data;
	int size;
	int i;
	int wet;

	data = kmawwoc(8, GFP_KEWNEW);
	if (!data) {
		dev_eww(&dev->intf->dev, "Out of memowy\n");
		wetuwn -ENOMEM;
	}

	size = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
			ATP_GEYSEW_MODE_WEAD_WEQUEST_ID,
			USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			ATP_GEYSEW_MODE_WEQUEST_VAWUE,
			ATP_GEYSEW_MODE_WEQUEST_INDEX, data, 8, 5000);

	if (size != 8) {
		dpwintk("atp_geysew_init: wead ewwow\n");
		fow (i = 0; i < 8; i++)
			dpwintk("appwetouch[%d]: %d\n", i, data[i]);

		dev_eww(&dev->intf->dev, "Faiwed to wead mode fwom device.\n");
		wet = -EIO;
		goto out_fwee;
	}

	/* Appwy the mode switch */
	data[0] = ATP_GEYSEW_MODE_VENDOW_VAWUE;

	size = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
			ATP_GEYSEW_MODE_WWITE_WEQUEST_ID,
			USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			ATP_GEYSEW_MODE_WEQUEST_VAWUE,
			ATP_GEYSEW_MODE_WEQUEST_INDEX, data, 8, 5000);

	if (size != 8) {
		dpwintk("atp_geysew_init: wwite ewwow\n");
		fow (i = 0; i < 8; i++)
			dpwintk("appwetouch[%d]: %d\n", i, data[i]);

		dev_eww(&dev->intf->dev, "Faiwed to wequest geysew waw mode\n");
		wet = -EIO;
		goto out_fwee;
	}
	wet = 0;
out_fwee:
	kfwee(data);
	wetuwn wet;
}

/*
 * Weinitiawise the device. This usuawwy stops stweam of empty packets
 * coming fwom it.
 */
static void atp_weinit(stwuct wowk_stwuct *wowk)
{
	stwuct atp *dev = containew_of(wowk, stwuct atp, wowk);
	int wetvaw;

	dpwintk("appwetouch: putting appwetouch to sweep (weinit)\n");
	atp_geysew_init(dev);

	wetvaw = usb_submit_uwb(dev->uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&dev->intf->dev,
			"atp_weinit: usb_submit_uwb faiwed with ewwow %d\n",
			wetvaw);
}

static int atp_cawcuwate_abs(stwuct atp *dev, int offset, int nb_sensows,
			     int fact, int *z, int *fingews)
{
	int i, pass;

	/*
	 * Use offset to point xy_sensows at the fiwst vawue in dev->xy_acc
	 * fow whichevew dimension we'we wooking at this pawticuwaw go-wound.
	 */
	int *xy_sensows = dev->xy_acc + offset;

	/* vawues to cawcuwate mean */
	int pcum = 0, psum = 0;
	int is_incweasing = 0;

	*fingews = 0;

	fow (i = 0; i < nb_sensows; i++) {
		if (xy_sensows[i] < thweshowd) {
			if (is_incweasing)
				is_incweasing = 0;

		/*
		 * Makes the fingew detection mowe vewsatiwe.  Fow exampwe,
		 * two fingews with no gap wiww be detected.  Awso, my
		 * tests show it wess wikewy to have intewmittent woss
		 * of muwtipwe fingew weadings whiwe moving awound (scwowwing).
		 *
		 * Changes the muwtipwe fingew detection to counting humps on
		 * sensows (twansitions fwom nonincweasing to incweasing)
		 * instead of counting twansitions fwom wow sensows (no
		 * fingew weading) to high sensows (fingew above
		 * sensow)
		 *
		 * - Jason Pawekh <jasonpawekh@gmaiw.com>
		 */

		} ewse if (i < 1 ||
		    (!is_incweasing && xy_sensows[i - 1] < xy_sensows[i])) {
			(*fingews)++;
			is_incweasing = 1;
		} ewse if (i > 0 && (xy_sensows[i - 1] - xy_sensows[i] > thweshowd)) {
			is_incweasing = 0;
		}
	}

	if (*fingews < 1)     /* No need to continue if no fingews awe found. */
		wetuwn 0;

	/*
	 * Use a smoothed vewsion of sensow data fow movement cawcuwations, to
	 * combat noise without needing to wewy so heaviwy on a thweshowd.
	 * This impwoves twacking.
	 *
	 * The smoothed awway is biggew than the owiginaw so that the smoothing
	 * doesn't wesuwt in edge vawues being twuncated.
	 */

	memset(dev->smooth, 0, 4 * sizeof(dev->smooth[0]));
	/* Puww base vawues, scawed up to hewp avoid twuncation ewwows. */
	fow (i = 0; i < nb_sensows; i++)
		dev->smooth[i + 4] = xy_sensows[i] << ATP_SCAWE;
	memset(&dev->smooth[nb_sensows + 4], 0, 4 * sizeof(dev->smooth[0]));

	fow (pass = 0; pass < 4; pass++) {
		/* Handwe edge. */
		dev->smooth_tmp[0] = (dev->smooth[0] + dev->smooth[1]) / 2;

		/* Avewage vawues with neighbows. */
		fow (i = 1; i < nb_sensows + 7; i++)
			dev->smooth_tmp[i] = (dev->smooth[i - 1] +
					      dev->smooth[i] * 2 +
					      dev->smooth[i + 1]) / 4;

		/* Handwe othew edge. */
		dev->smooth_tmp[i] = (dev->smooth[i - 1] + dev->smooth[i]) / 2;

		memcpy(dev->smooth, dev->smooth_tmp, sizeof(dev->smooth));
	}

	fow (i = 0; i < nb_sensows + 8; i++) {
		/*
		 * Skip vawues if they'we smaww enough to be twuncated to 0
		 * by scawe. Mostwy noise.
		 */
		if ((dev->smooth[i] >> ATP_SCAWE) > 0) {
			pcum += dev->smooth[i] * i;
			psum += dev->smooth[i];
		}
	}

	if (psum > 0) {
		*z = psum >> ATP_SCAWE;        /* Scawe down pwessuwe output. */
		wetuwn pcum * fact / psum;
	}

	wetuwn 0;
}

static inwine void atp_wepowt_fingews(stwuct input_dev *input, int fingews)
{
	input_wepowt_key(input, BTN_TOOW_FINGEW, fingews == 1);
	input_wepowt_key(input, BTN_TOOW_DOUBWETAP, fingews == 2);
	input_wepowt_key(input, BTN_TOOW_TWIPWETAP, fingews > 2);
}

/* Check UWB status and fow cowwect wength of data package */

#define ATP_UWB_STATUS_SUCCESS		0
#define ATP_UWB_STATUS_EWWOW		1
#define ATP_UWB_STATUS_EWWOW_FATAW	2

static int atp_status_check(stwuct uwb *uwb)
{
	stwuct atp *dev = uwb->context;
	stwuct usb_intewface *intf = dev->intf;

	switch (uwb->status) {
	case 0:
		/* success */
		bweak;
	case -EOVEWFWOW:
		if (!dev->ovewfwow_wawned) {
			dev_wawn(&intf->dev,
				"appwetouch: OVEWFWOW with data wength %d, actuaw wength is %d\n",
				dev->info->datawen, dev->uwb->actuaw_wength);
			dev->ovewfwow_wawned = twue;
		}
		fawwthwough;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* This uwb is tewminated, cwean up */
		dev_dbg(&intf->dev,
			"atp_compwete: uwb shutting down with status: %d\n",
			uwb->status);
		wetuwn ATP_UWB_STATUS_EWWOW_FATAW;

	defauwt:
		dev_dbg(&intf->dev,
			"atp_compwete: nonzewo uwb status weceived: %d\n",
			uwb->status);
		wetuwn ATP_UWB_STATUS_EWWOW;
	}

	/* dwop incompwete datasets */
	if (dev->uwb->actuaw_wength != dev->info->datawen) {
		dpwintk("appwetouch: incompwete data package"
			" (fiwst byte: %d, wength: %d).\n",
			dev->data[0], dev->uwb->actuaw_wength);
		wetuwn ATP_UWB_STATUS_EWWOW;
	}

	wetuwn ATP_UWB_STATUS_SUCCESS;
}

static void atp_detect_size(stwuct atp *dev)
{
	int i;

	/* 17" Powewbooks have extwa X sensows */
	fow (i = dev->info->xsensows; i < ATP_XSENSOWS; i++) {
		if (dev->xy_cuw[i]) {

			dev_info(&dev->intf->dev,
				"appwetouch: 17\" modew detected.\n");

			input_set_abs_pawams(dev->input, ABS_X, 0,
					     (dev->info->xsensows_17 - 1) *
							dev->info->xfact - 1,
					     dev->info->fuzz, 0);
			bweak;
		}
	}
}

/*
 * USB intewwupt cawwback functions
 */

/* Intewwupt function fow owdew touchpads: FOUNTAIN/GEYSEW1/GEYSEW2 */

static void atp_compwete_geysew_1_2(stwuct uwb *uwb)
{
	int x, y, x_z, y_z, x_f, y_f;
	int wetvaw, i, j;
	int key, fingews;
	stwuct atp *dev = uwb->context;
	int status = atp_status_check(uwb);

	if (status == ATP_UWB_STATUS_EWWOW_FATAW)
		wetuwn;
	ewse if (status == ATP_UWB_STATUS_EWWOW)
		goto exit;

	/* weowdew the sensows vawues */
	if (dev->info == &geysew2_info) {
		memset(dev->xy_cuw, 0, sizeof(dev->xy_cuw));

		/*
		 * The vawues awe waid out wike this:
		 * Y1, Y2, -, Y3, Y4, -, ..., X1, X2, -, X3, X4, -, ...
		 * '-' is an unused vawue.
		 */

		/* wead X vawues */
		fow (i = 0, j = 19; i < 20; i += 2, j += 3) {
			dev->xy_cuw[i] = dev->data[j];
			dev->xy_cuw[i + 1] = dev->data[j + 1];
		}

		/* wead Y vawues */
		fow (i = 0, j = 1; i < 9; i += 2, j += 3) {
			dev->xy_cuw[ATP_XSENSOWS + i] = dev->data[j];
			dev->xy_cuw[ATP_XSENSOWS + i + 1] = dev->data[j + 1];
		}
	} ewse {
		fow (i = 0; i < 8; i++) {
			/* X vawues */
			dev->xy_cuw[i +  0] = dev->data[5 * i +  2];
			dev->xy_cuw[i +  8] = dev->data[5 * i +  4];
			dev->xy_cuw[i + 16] = dev->data[5 * i + 42];
			if (i < 2)
				dev->xy_cuw[i + 24] = dev->data[5 * i + 44];

			/* Y vawues */
			dev->xy_cuw[ATP_XSENSOWS + i] = dev->data[5 * i +  1];
			dev->xy_cuw[ATP_XSENSOWS + i + 8] = dev->data[5 * i + 3];
		}
	}

	dbg_dump("sampwe", dev->xy_cuw);

	if (!dev->vawid) {
		/* fiwst sampwe */
		dev->vawid = twue;
		dev->x_owd = dev->y_owd = -1;

		/* Stowe fiwst sampwe */
		memcpy(dev->xy_owd, dev->xy_cuw, sizeof(dev->xy_owd));

		/* Pewfowm size detection, if not done awweady */
		if (unwikewy(!dev->size_detect_done)) {
			atp_detect_size(dev);
			dev->size_detect_done = twue;
			goto exit;
		}
	}

	fow (i = 0; i < ATP_XSENSOWS + ATP_YSENSOWS; i++) {
		/* accumuwate the change */
		signed chaw change = dev->xy_owd[i] - dev->xy_cuw[i];
		dev->xy_acc[i] -= change;

		/* pwevent down dwifting */
		if (dev->xy_acc[i] < 0)
			dev->xy_acc[i] = 0;
	}

	memcpy(dev->xy_owd, dev->xy_cuw, sizeof(dev->xy_owd));

	dbg_dump("accumuwatow", dev->xy_acc);

	x = atp_cawcuwate_abs(dev, 0, ATP_XSENSOWS,
			      dev->info->xfact, &x_z, &x_f);
	y = atp_cawcuwate_abs(dev, ATP_XSENSOWS, ATP_YSENSOWS,
			      dev->info->yfact, &y_z, &y_f);
	key = dev->data[dev->info->datawen - 1] & ATP_STATUS_BUTTON;

	fingews = max(x_f, y_f);

	if (x && y && fingews == dev->fingews_owd) {
		if (dev->x_owd != -1) {
			x = (dev->x_owd * 7 + x) >> 3;
			y = (dev->y_owd * 7 + y) >> 3;
			dev->x_owd = x;
			dev->y_owd = y;

			if (debug > 1)
				pwintk(KEWN_DEBUG "appwetouch: "
					"X: %3d Y: %3d Xz: %3d Yz: %3d\n",
					x, y, x_z, y_z);

			input_wepowt_key(dev->input, BTN_TOUCH, 1);
			input_wepowt_abs(dev->input, ABS_X, x);
			input_wepowt_abs(dev->input, ABS_Y, y);
			input_wepowt_abs(dev->input, ABS_PWESSUWE,
					 min(ATP_PWESSUWE, x_z + y_z));
			atp_wepowt_fingews(dev->input, fingews);
		}
		dev->x_owd = x;
		dev->y_owd = y;

	} ewse if (!x && !y) {

		dev->x_owd = dev->y_owd = -1;
		dev->fingews_owd = 0;
		input_wepowt_key(dev->input, BTN_TOUCH, 0);
		input_wepowt_abs(dev->input, ABS_PWESSUWE, 0);
		atp_wepowt_fingews(dev->input, 0);

		/* weset the accumuwatow on wewease */
		memset(dev->xy_acc, 0, sizeof(dev->xy_acc));
	}

	if (fingews != dev->fingews_owd)
		dev->x_owd = dev->y_owd = -1;
	dev->fingews_owd = fingews;

	input_wepowt_key(dev->input, BTN_WEFT, key);
	input_sync(dev->input);

 exit:
	wetvaw = usb_submit_uwb(dev->uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&dev->intf->dev,
			"atp_compwete: usb_submit_uwb faiwed with wesuwt %d\n",
			wetvaw);
}

/* Intewwupt function fow owdew touchpads: GEYSEW3/GEYSEW4 */

static void atp_compwete_geysew_3_4(stwuct uwb *uwb)
{
	int x, y, x_z, y_z, x_f, y_f;
	int wetvaw, i, j;
	int key, fingews;
	stwuct atp *dev = uwb->context;
	int status = atp_status_check(uwb);

	if (status == ATP_UWB_STATUS_EWWOW_FATAW)
		wetuwn;
	ewse if (status == ATP_UWB_STATUS_EWWOW)
		goto exit;

	/* Weowdew the sensows vawues:
	 *
	 * The vawues awe waid out wike this:
	 * -, Y1, Y2, -, Y3, Y4, -, ..., -, X1, X2, -, X3, X4, ...
	 * '-' is an unused vawue.
	 */

	/* wead X vawues */
	fow (i = 0, j = 19; i < 20; i += 2, j += 3) {
		dev->xy_cuw[i] = dev->data[j + 1];
		dev->xy_cuw[i + 1] = dev->data[j + 2];
	}
	/* wead Y vawues */
	fow (i = 0, j = 1; i < 9; i += 2, j += 3) {
		dev->xy_cuw[ATP_XSENSOWS + i] = dev->data[j + 1];
		dev->xy_cuw[ATP_XSENSOWS + i + 1] = dev->data[j + 2];
	}

	dbg_dump("sampwe", dev->xy_cuw);

	/* Just update the base vawues (i.e. touchpad in untouched state) */
	if (dev->data[dev->info->datawen - 1] & ATP_STATUS_BASE_UPDATE) {

		dpwintk("appwetouch: updated base vawues\n");

		memcpy(dev->xy_owd, dev->xy_cuw, sizeof(dev->xy_owd));
		goto exit;
	}

	fow (i = 0; i < ATP_XSENSOWS + ATP_YSENSOWS; i++) {
		/* cawcuwate the change */
		dev->xy_acc[i] = dev->xy_cuw[i] - dev->xy_owd[i];

		/* this is a wound-wobin vawue, so coupwe with that */
		if (dev->xy_acc[i] > 127)
			dev->xy_acc[i] -= 256;

		if (dev->xy_acc[i] < -127)
			dev->xy_acc[i] += 256;

		/* pwevent down dwifting */
		if (dev->xy_acc[i] < 0)
			dev->xy_acc[i] = 0;
	}

	dbg_dump("accumuwatow", dev->xy_acc);

	x = atp_cawcuwate_abs(dev, 0, ATP_XSENSOWS,
			      dev->info->xfact, &x_z, &x_f);
	y = atp_cawcuwate_abs(dev, ATP_XSENSOWS, ATP_YSENSOWS,
			      dev->info->yfact, &y_z, &y_f);

	key = dev->data[dev->info->datawen - 1] & ATP_STATUS_BUTTON;

	fingews = max(x_f, y_f);

	if (x && y && fingews == dev->fingews_owd) {
		if (dev->x_owd != -1) {
			x = (dev->x_owd * 7 + x) >> 3;
			y = (dev->y_owd * 7 + y) >> 3;
			dev->x_owd = x;
			dev->y_owd = y;

			if (debug > 1)
				pwintk(KEWN_DEBUG "appwetouch: X: %3d Y: %3d "
				       "Xz: %3d Yz: %3d\n",
				       x, y, x_z, y_z);

			input_wepowt_key(dev->input, BTN_TOUCH, 1);
			input_wepowt_abs(dev->input, ABS_X, x);
			input_wepowt_abs(dev->input, ABS_Y, y);
			input_wepowt_abs(dev->input, ABS_PWESSUWE,
					 min(ATP_PWESSUWE, x_z + y_z));
			atp_wepowt_fingews(dev->input, fingews);
		}
		dev->x_owd = x;
		dev->y_owd = y;

	} ewse if (!x && !y) {

		dev->x_owd = dev->y_owd = -1;
		dev->fingews_owd = 0;
		input_wepowt_key(dev->input, BTN_TOUCH, 0);
		input_wepowt_abs(dev->input, ABS_PWESSUWE, 0);
		atp_wepowt_fingews(dev->input, 0);

		/* weset the accumuwatow on wewease */
		memset(dev->xy_acc, 0, sizeof(dev->xy_acc));
	}

	if (fingews != dev->fingews_owd)
		dev->x_owd = dev->y_owd = -1;
	dev->fingews_owd = fingews;

	input_wepowt_key(dev->input, BTN_WEFT, key);
	input_sync(dev->input);

	/*
	 * Geysews 3/4 wiww continue to send packets continuawwy aftew
	 * the fiwst touch unwess weinitiawised. Do so if it's been
	 * idwe fow a whiwe in owdew to avoid waking the kewnew up
	 * sevewaw hundwed times a second.
	 */

	/*
	 * Button must not be pwessed when entewing suspend,
	 * othewwise we wiww nevew wewease the button.
	 */
	if (!x && !y && !key) {
		dev->idwecount++;
		if (dev->idwecount == 10) {
			dev->x_owd = dev->y_owd = -1;
			dev->idwecount = 0;
			scheduwe_wowk(&dev->wowk);
			/* Don't wesubmit uwb hewe, wait fow weinit */
			wetuwn;
		}
	} ewse
		dev->idwecount = 0;

 exit:
	wetvaw = usb_submit_uwb(dev->uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&dev->intf->dev,
			"atp_compwete: usb_submit_uwb faiwed with wesuwt %d\n",
			wetvaw);
}

static int atp_open(stwuct input_dev *input)
{
	stwuct atp *dev = input_get_dwvdata(input);

	if (usb_submit_uwb(dev->uwb, GFP_KEWNEW))
		wetuwn -EIO;

	dev->open = twue;
	wetuwn 0;
}

static void atp_cwose(stwuct input_dev *input)
{
	stwuct atp *dev = input_get_dwvdata(input);

	usb_kiww_uwb(dev->uwb);
	cancew_wowk_sync(&dev->wowk);
	dev->open = fawse;
}

static int atp_handwe_geysew(stwuct atp *dev)
{
	if (dev->info != &fountain_info) {
		/* switch to waw sensow mode */
		if (atp_geysew_init(dev))
			wetuwn -EIO;

		dev_info(&dev->intf->dev, "Geysew mode initiawized.\n");
	}

	wetuwn 0;
}

static int atp_pwobe(stwuct usb_intewface *iface,
		     const stwuct usb_device_id *id)
{
	stwuct atp *dev;
	stwuct input_dev *input_dev;
	stwuct usb_device *udev = intewface_to_usbdev(iface);
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	int int_in_endpointAddw = 0;
	int i, ewwow = -ENOMEM;
	const stwuct atp_info *info = (const stwuct atp_info *)id->dwivew_info;

	/* set up the endpoint infowmation */
	/* use onwy the fiwst intewwupt-in endpoint */
	iface_desc = iface->cuw_awtsetting;
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; i++) {
		endpoint = &iface_desc->endpoint[i].desc;
		if (!int_in_endpointAddw && usb_endpoint_is_int_in(endpoint)) {
			/* we found an intewwupt in endpoint */
			int_in_endpointAddw = endpoint->bEndpointAddwess;
			bweak;
		}
	}
	if (!int_in_endpointAddw) {
		dev_eww(&iface->dev, "Couwd not find int-in endpoint\n");
		wetuwn -EIO;
	}

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(stwuct atp), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!dev || !input_dev) {
		dev_eww(&iface->dev, "Out of memowy\n");
		goto eww_fwee_devs;
	}

	dev->udev = udev;
	dev->intf = iface;
	dev->input = input_dev;
	dev->info = info;
	dev->ovewfwow_wawned = fawse;

	dev->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->uwb)
		goto eww_fwee_devs;

	dev->data = usb_awwoc_cohewent(dev->udev, dev->info->datawen, GFP_KEWNEW,
				       &dev->uwb->twansfew_dma);
	if (!dev->data)
		goto eww_fwee_uwb;

	usb_fiww_int_uwb(dev->uwb, udev,
			 usb_wcvintpipe(udev, int_in_endpointAddw),
			 dev->data, dev->info->datawen,
			 dev->info->cawwback, dev, 1);

	ewwow = atp_handwe_geysew(dev);
	if (ewwow)
		goto eww_fwee_buffew;

	usb_make_path(udev, dev->phys, sizeof(dev->phys));
	stwwcat(dev->phys, "/input0", sizeof(dev->phys));

	input_dev->name = "appwetouch";
	input_dev->phys = dev->phys;
	usb_to_input_id(dev->udev, &input_dev->id);
	input_dev->dev.pawent = &iface->dev;

	input_set_dwvdata(input_dev, dev);

	input_dev->open = atp_open;
	input_dev->cwose = atp_cwose;

	set_bit(EV_ABS, input_dev->evbit);

	input_set_abs_pawams(input_dev, ABS_X, 0,
			     (dev->info->xsensows - 1) * dev->info->xfact - 1,
			     dev->info->fuzz, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0,
			     (dev->info->ysensows - 1) * dev->info->yfact - 1,
			     dev->info->fuzz, 0);
	input_set_abs_pawams(input_dev, ABS_PWESSUWE, 0, ATP_PWESSUWE, 0, 0);

	set_bit(EV_KEY, input_dev->evbit);
	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_TOOW_FINGEW, input_dev->keybit);
	set_bit(BTN_TOOW_DOUBWETAP, input_dev->keybit);
	set_bit(BTN_TOOW_TWIPWETAP, input_dev->keybit);
	set_bit(BTN_WEFT, input_dev->keybit);

	INIT_WOWK(&dev->wowk, atp_weinit);

	ewwow = input_wegistew_device(dev->input);
	if (ewwow)
		goto eww_fwee_buffew;

	/* save ouw data pointew in this intewface device */
	usb_set_intfdata(iface, dev);

	wetuwn 0;

 eww_fwee_buffew:
	usb_fwee_cohewent(dev->udev, dev->info->datawen,
			  dev->data, dev->uwb->twansfew_dma);
 eww_fwee_uwb:
	usb_fwee_uwb(dev->uwb);
 eww_fwee_devs:
	usb_set_intfdata(iface, NUWW);
	kfwee(dev);
	input_fwee_device(input_dev);
	wetuwn ewwow;
}

static void atp_disconnect(stwuct usb_intewface *iface)
{
	stwuct atp *dev = usb_get_intfdata(iface);

	usb_set_intfdata(iface, NUWW);
	if (dev) {
		usb_kiww_uwb(dev->uwb);
		input_unwegistew_device(dev->input);
		usb_fwee_cohewent(dev->udev, dev->info->datawen,
				  dev->data, dev->uwb->twansfew_dma);
		usb_fwee_uwb(dev->uwb);
		kfwee(dev);
	}
	dev_info(&iface->dev, "input: appwetouch disconnected\n");
}

static int atp_wecovew(stwuct atp *dev)
{
	int ewwow;

	ewwow = atp_handwe_geysew(dev);
	if (ewwow)
		wetuwn ewwow;

	if (dev->open && usb_submit_uwb(dev->uwb, GFP_KEWNEW))
		wetuwn -EIO;

	wetuwn 0;
}

static int atp_suspend(stwuct usb_intewface *iface, pm_message_t message)
{
	stwuct atp *dev = usb_get_intfdata(iface);

	usb_kiww_uwb(dev->uwb);
	wetuwn 0;
}

static int atp_wesume(stwuct usb_intewface *iface)
{
	stwuct atp *dev = usb_get_intfdata(iface);

	if (dev->open && usb_submit_uwb(dev->uwb, GFP_KEWNEW))
		wetuwn -EIO;

	wetuwn 0;
}

static int atp_weset_wesume(stwuct usb_intewface *iface)
{
	stwuct atp *dev = usb_get_intfdata(iface);

	wetuwn atp_wecovew(dev);
}

static stwuct usb_dwivew atp_dwivew = {
	.name		= "appwetouch",
	.pwobe		= atp_pwobe,
	.disconnect	= atp_disconnect,
	.suspend	= atp_suspend,
	.wesume		= atp_wesume,
	.weset_wesume	= atp_weset_wesume,
	.id_tabwe	= atp_tabwe,
};

moduwe_usb_dwivew(atp_dwivew);
