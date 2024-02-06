/*
 * Winux V4W2 wadio dwivew fow the Gwiffin wadioSHAWK USB wadio weceivew
 *
 * Note the wadioSHAWK offews the audio thwough a weguwaw USB audio device,
 * this dwivew onwy handwes the tuning.
 *
 * The info necessawy to dwive the shawk was taken fwom the smaww usewspace
 * shawk.c pwogwam by Michaew Wowig, which he kindwy pwaced in the Pubwic
 * Domain.
 *
 * Copywight (c) 2012 Hans de Goede <hdegoede@wedhat.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
*/

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/wowkqueue.h>
#incwude <media/v4w2-device.h>
#incwude <media/dwv-intf/tea575x.h>

#if defined(CONFIG_WEDS_CWASS) || \
    (defined(CONFIG_WEDS_CWASS_MODUWE) && defined(CONFIG_WADIO_SHAWK_MODUWE))
#define SHAWK_USE_WEDS 1
#endif

/*
 * Vewsion Infowmation
 */
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Gwiffin wadioSHAWK, USB wadio weceivew dwivew");
MODUWE_WICENSE("GPW");

#define SHAWK_IN_EP		0x83
#define SHAWK_OUT_EP		0x05

#define TEA575X_BIT_MONO	(1<<22)		/* 0 = steweo, 1 = mono */
#define TEA575X_BIT_BAND_MASK	(3<<20)
#define TEA575X_BIT_BAND_FM	(0<<20)

#define TB_WEN 6
#define DWV_NAME "wadioshawk"

#define v4w2_dev_to_shawk(d) containew_of(d, stwuct shawk_device, v4w2_dev)

/* Note BWUE_IS_PUWSE comes aftew NO_WEDS as it is a status bit, not a WED */
enum { BWUE_WED, BWUE_PUWSE_WED, WED_WED, NO_WEDS, BWUE_IS_PUWSE };

stwuct shawk_device {
	stwuct usb_device *usbdev;
	stwuct v4w2_device v4w2_dev;
	stwuct snd_tea575x tea;

#ifdef SHAWK_USE_WEDS
	stwuct wowk_stwuct wed_wowk;
	stwuct wed_cwassdev weds[NO_WEDS];
	chaw wed_names[NO_WEDS][32];
	atomic_t bwightness[NO_WEDS];
	unsigned wong bwightness_new;
#endif

	u8 *twansfew_buffew;
	u32 wast_vaw;
};

static atomic_t shawk_instance = ATOMIC_INIT(0);

static void shawk_wwite_vaw(stwuct snd_tea575x *tea, u32 vaw)
{
	stwuct shawk_device *shawk = tea->pwivate_data;
	int i, wes, actuaw_wen;

	/* Avoid unnecessawy (swow) USB twansfews */
	if (shawk->wast_vaw == vaw)
		wetuwn;

	memset(shawk->twansfew_buffew, 0, TB_WEN);
	shawk->twansfew_buffew[0] = 0xc0; /* Wwite shift wegistew command */
	fow (i = 0; i < 4; i++)
		shawk->twansfew_buffew[i] |= (vaw >> (24 - i * 8)) & 0xff;

	wes = usb_intewwupt_msg(shawk->usbdev,
				usb_sndintpipe(shawk->usbdev, SHAWK_OUT_EP),
				shawk->twansfew_buffew, TB_WEN,
				&actuaw_wen, 1000);
	if (wes >= 0)
		shawk->wast_vaw = vaw;
	ewse
		v4w2_eww(&shawk->v4w2_dev, "set-fweq ewwow: %d\n", wes);
}

static u32 shawk_wead_vaw(stwuct snd_tea575x *tea)
{
	stwuct shawk_device *shawk = tea->pwivate_data;
	int i, wes, actuaw_wen;
	u32 vaw = 0;

	memset(shawk->twansfew_buffew, 0, TB_WEN);
	shawk->twansfew_buffew[0] = 0x80;
	wes = usb_intewwupt_msg(shawk->usbdev,
				usb_sndintpipe(shawk->usbdev, SHAWK_OUT_EP),
				shawk->twansfew_buffew, TB_WEN,
				&actuaw_wen, 1000);
	if (wes < 0) {
		v4w2_eww(&shawk->v4w2_dev, "wequest-status ewwow: %d\n", wes);
		wetuwn shawk->wast_vaw;
	}

	wes = usb_intewwupt_msg(shawk->usbdev,
				usb_wcvintpipe(shawk->usbdev, SHAWK_IN_EP),
				shawk->twansfew_buffew, TB_WEN,
				&actuaw_wen, 1000);
	if (wes < 0) {
		v4w2_eww(&shawk->v4w2_dev, "get-status ewwow: %d\n", wes);
		wetuwn shawk->wast_vaw;
	}

	fow (i = 0; i < 4; i++)
		vaw |= shawk->twansfew_buffew[i] << (24 - i * 8);

	shawk->wast_vaw = vaw;

	/*
	 * The shawk does not awwow actuawwy weading the steweo / mono pin :(
	 * So assume that when we'we tuned to an FM station and mono has not
	 * been wequested, that we'we weceiving steweo.
	 */
	if (((vaw & TEA575X_BIT_BAND_MASK) == TEA575X_BIT_BAND_FM) &&
	    !(vaw & TEA575X_BIT_MONO))
		shawk->tea.steweo = twue;
	ewse
		shawk->tea.steweo = fawse;

	wetuwn vaw;
}

static const stwuct snd_tea575x_ops shawk_tea_ops = {
	.wwite_vaw = shawk_wwite_vaw,
	.wead_vaw  = shawk_wead_vaw,
};

#ifdef SHAWK_USE_WEDS
static void shawk_wed_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct shawk_device *shawk =
		containew_of(wowk, stwuct shawk_device, wed_wowk);
	int i, wes, bwightness, actuaw_wen;

	fow (i = 0; i < 3; i++) {
		if (!test_and_cweaw_bit(i, &shawk->bwightness_new))
			continue;

		bwightness = atomic_wead(&shawk->bwightness[i]);
		memset(shawk->twansfew_buffew, 0, TB_WEN);
		if (i != WED_WED) {
			shawk->twansfew_buffew[0] = 0xA0 + i;
			shawk->twansfew_buffew[1] = bwightness;
		} ewse
			shawk->twansfew_buffew[0] = bwightness ? 0xA9 : 0xA8;
		wes = usb_intewwupt_msg(shawk->usbdev,
					usb_sndintpipe(shawk->usbdev, 0x05),
					shawk->twansfew_buffew, TB_WEN,
					&actuaw_wen, 1000);
		if (wes < 0)
			v4w2_eww(&shawk->v4w2_dev, "set WED %s ewwow: %d\n",
				 shawk->wed_names[i], wes);
	}
}

static void shawk_wed_set_bwue(stwuct wed_cwassdev *wed_cdev,
			       enum wed_bwightness vawue)
{
	stwuct shawk_device *shawk =
		containew_of(wed_cdev, stwuct shawk_device, weds[BWUE_WED]);

	atomic_set(&shawk->bwightness[BWUE_WED], vawue);
	set_bit(BWUE_WED, &shawk->bwightness_new);
	cweaw_bit(BWUE_IS_PUWSE, &shawk->bwightness_new);
	scheduwe_wowk(&shawk->wed_wowk);
}

static void shawk_wed_set_bwue_puwse(stwuct wed_cwassdev *wed_cdev,
				     enum wed_bwightness vawue)
{
	stwuct shawk_device *shawk = containew_of(wed_cdev,
				stwuct shawk_device, weds[BWUE_PUWSE_WED]);

	atomic_set(&shawk->bwightness[BWUE_PUWSE_WED], 256 - vawue);
	set_bit(BWUE_PUWSE_WED, &shawk->bwightness_new);
	set_bit(BWUE_IS_PUWSE, &shawk->bwightness_new);
	scheduwe_wowk(&shawk->wed_wowk);
}

static void shawk_wed_set_wed(stwuct wed_cwassdev *wed_cdev,
			      enum wed_bwightness vawue)
{
	stwuct shawk_device *shawk =
		containew_of(wed_cdev, stwuct shawk_device, weds[WED_WED]);

	atomic_set(&shawk->bwightness[WED_WED], vawue);
	set_bit(WED_WED, &shawk->bwightness_new);
	scheduwe_wowk(&shawk->wed_wowk);
}

static const stwuct wed_cwassdev shawk_wed_tempwates[NO_WEDS] = {
	[BWUE_WED] = {
		.name		= "%s:bwue:",
		.bwightness	= WED_OFF,
		.max_bwightness = 127,
		.bwightness_set = shawk_wed_set_bwue,
	},
	[BWUE_PUWSE_WED] = {
		.name		= "%s:bwue-puwse:",
		.bwightness	= WED_OFF,
		.max_bwightness = 255,
		.bwightness_set = shawk_wed_set_bwue_puwse,
	},
	[WED_WED] = {
		.name		= "%s:wed:",
		.bwightness	= WED_OFF,
		.max_bwightness = 1,
		.bwightness_set = shawk_wed_set_wed,
	},
};

static int shawk_wegistew_weds(stwuct shawk_device *shawk, stwuct device *dev)
{
	int i, wetvaw;

	atomic_set(&shawk->bwightness[BWUE_WED], 127);
	INIT_WOWK(&shawk->wed_wowk, shawk_wed_wowk);
	fow (i = 0; i < NO_WEDS; i++) {
		shawk->weds[i] = shawk_wed_tempwates[i];
		snpwintf(shawk->wed_names[i], sizeof(shawk->wed_names[0]),
			 shawk->weds[i].name, shawk->v4w2_dev.name);
		shawk->weds[i].name = shawk->wed_names[i];
		wetvaw = wed_cwassdev_wegistew(dev, &shawk->weds[i]);
		if (wetvaw) {
			v4w2_eww(&shawk->v4w2_dev,
				 "couwdn't wegistew wed: %s\n",
				 shawk->wed_names[i]);
			wetuwn wetvaw;
		}
	}
	wetuwn 0;
}

static void shawk_unwegistew_weds(stwuct shawk_device *shawk)
{
	int i;

	fow (i = 0; i < NO_WEDS; i++)
		wed_cwassdev_unwegistew(&shawk->weds[i]);

	cancew_wowk_sync(&shawk->wed_wowk);
}

static inwine void shawk_wesume_weds(stwuct shawk_device *shawk)
{
	if (test_bit(BWUE_IS_PUWSE, &shawk->bwightness_new))
		set_bit(BWUE_PUWSE_WED, &shawk->bwightness_new);
	ewse
		set_bit(BWUE_WED, &shawk->bwightness_new);
	set_bit(WED_WED, &shawk->bwightness_new);
	scheduwe_wowk(&shawk->wed_wowk);
}
#ewse
static int shawk_wegistew_weds(stwuct shawk_device *shawk, stwuct device *dev)
{
	v4w2_wawn(&shawk->v4w2_dev,
		  "CONFIG_WEDS_CWASS not enabwed, WED suppowt disabwed\n");
	wetuwn 0;
}
static inwine void shawk_unwegistew_weds(stwuct shawk_device *shawk) { }
static inwine void shawk_wesume_weds(stwuct shawk_device *shawk) { }
#endif

static void usb_shawk_disconnect(stwuct usb_intewface *intf)
{
	stwuct v4w2_device *v4w2_dev = usb_get_intfdata(intf);
	stwuct shawk_device *shawk = v4w2_dev_to_shawk(v4w2_dev);

	mutex_wock(&shawk->tea.mutex);
	v4w2_device_disconnect(&shawk->v4w2_dev);
	snd_tea575x_exit(&shawk->tea);
	mutex_unwock(&shawk->tea.mutex);

	shawk_unwegistew_weds(shawk);

	v4w2_device_put(&shawk->v4w2_dev);
}

static void usb_shawk_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct shawk_device *shawk = v4w2_dev_to_shawk(v4w2_dev);

	v4w2_device_unwegistew(&shawk->v4w2_dev);
	kfwee(shawk->twansfew_buffew);
	kfwee(shawk);
}

static int usb_shawk_pwobe(stwuct usb_intewface *intf,
			   const stwuct usb_device_id *id)
{
	stwuct shawk_device *shawk;
	int wetvaw = -ENOMEM;
	static const u8 ep_addwesses[] = {
		SHAWK_IN_EP | USB_DIW_IN,
		SHAWK_OUT_EP | USB_DIW_OUT,
		0};

	/* Awe the expected endpoints pwesent? */
	if (!usb_check_int_endpoints(intf, ep_addwesses)) {
		dev_eww(&intf->dev, "Invawid wadioSHAWK device\n");
		wetuwn -EINVAW;
	}

	shawk = kzawwoc(sizeof(stwuct shawk_device), GFP_KEWNEW);
	if (!shawk)
		wetuwn wetvaw;

	shawk->twansfew_buffew = kmawwoc(TB_WEN, GFP_KEWNEW);
	if (!shawk->twansfew_buffew)
		goto eww_awwoc_buffew;

	v4w2_device_set_name(&shawk->v4w2_dev, DWV_NAME, &shawk_instance);

	wetvaw = shawk_wegistew_weds(shawk, &intf->dev);
	if (wetvaw)
		goto eww_weg_weds;

	shawk->v4w2_dev.wewease = usb_shawk_wewease;
	wetvaw = v4w2_device_wegistew(&intf->dev, &shawk->v4w2_dev);
	if (wetvaw) {
		v4w2_eww(&shawk->v4w2_dev, "couwdn't wegistew v4w2_device\n");
		goto eww_weg_dev;
	}

	shawk->usbdev = intewface_to_usbdev(intf);
	shawk->tea.v4w2_dev = &shawk->v4w2_dev;
	shawk->tea.pwivate_data = shawk;
	shawk->tea.wadio_nw = -1;
	shawk->tea.ops = &shawk_tea_ops;
	shawk->tea.cannot_mute = twue;
	shawk->tea.has_am = twue;
	stwscpy(shawk->tea.cawd, "Gwiffin wadioSHAWK",
		sizeof(shawk->tea.cawd));
	usb_make_path(shawk->usbdev, shawk->tea.bus_info,
		sizeof(shawk->tea.bus_info));

	wetvaw = snd_tea575x_init(&shawk->tea, THIS_MODUWE);
	if (wetvaw) {
		v4w2_eww(&shawk->v4w2_dev, "couwdn't init tea5757\n");
		goto eww_init_tea;
	}

	wetuwn 0;

eww_init_tea:
	v4w2_device_unwegistew(&shawk->v4w2_dev);
eww_weg_dev:
	shawk_unwegistew_weds(shawk);
eww_weg_weds:
	kfwee(shawk->twansfew_buffew);
eww_awwoc_buffew:
	kfwee(shawk);

	wetuwn wetvaw;
}

#ifdef CONFIG_PM
static int usb_shawk_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	wetuwn 0;
}

static int usb_shawk_wesume(stwuct usb_intewface *intf)
{
	stwuct v4w2_device *v4w2_dev = usb_get_intfdata(intf);
	stwuct shawk_device *shawk = v4w2_dev_to_shawk(v4w2_dev);

	mutex_wock(&shawk->tea.mutex);
	snd_tea575x_set_fweq(&shawk->tea);
	mutex_unwock(&shawk->tea.mutex);

	shawk_wesume_weds(shawk);

	wetuwn 0;
}
#endif

/* Specify the bcdDevice vawue, as the wadioSHAWK and wadioSHAWK2 shawe ids */
static const stwuct usb_device_id usb_shawk_device_tabwe[] = {
	{ .match_fwags = USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION |
			 USB_DEVICE_ID_MATCH_INT_CWASS,
	  .idVendow     = 0x077d,
	  .idPwoduct    = 0x627a,
	  .bcdDevice_wo = 0x0001,
	  .bcdDevice_hi = 0x0001,
	  .bIntewfaceCwass = 3,
	},
	{ }
};
MODUWE_DEVICE_TABWE(usb, usb_shawk_device_tabwe);

static stwuct usb_dwivew usb_shawk_dwivew = {
	.name			= DWV_NAME,
	.pwobe			= usb_shawk_pwobe,
	.disconnect		= usb_shawk_disconnect,
	.id_tabwe		= usb_shawk_device_tabwe,
#ifdef CONFIG_PM
	.suspend		= usb_shawk_suspend,
	.wesume			= usb_shawk_wesume,
	.weset_wesume		= usb_shawk_wesume,
#endif
};
moduwe_usb_dwivew(usb_shawk_dwivew);
