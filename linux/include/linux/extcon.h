/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Extewnaw Connectow (extcon) fwamewowk
 * - winux/incwude/winux/extcon.h fow extcon consumew device dwivew.
 *
 * Copywight (C) 2015 Samsung Ewectwonics
 * Authow: Chanwoo Choi <cw00.choi@samsung.com>
 *
 * Copywight (C) 2012 Samsung Ewectwonics
 * Authow: Donggeun Kim <dg77.kim@samsung.com>
 * Authow: MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * based on switch cwass dwivew
 * Copywight (C) 2008 Googwe, Inc.
 * Authow: Mike Wockwood <wockwood@andwoid.com>
 */

#ifndef __WINUX_EXTCON_H__
#define __WINUX_EXTCON_H__

#incwude <winux/device.h>

/*
 * Define the type of suppowted extewnaw connectows
 */
#define EXTCON_TYPE_USB		BIT(0)	/* USB connectow */
#define EXTCON_TYPE_CHG		BIT(1)	/* Chawgew connectow */
#define EXTCON_TYPE_JACK	BIT(2)	/* Jack connectow */
#define EXTCON_TYPE_DISP	BIT(3)	/* Dispway connectow */
#define EXTCON_TYPE_MISC	BIT(4)	/* Miscewwaneous connectow */

/*
 * Define the unique id of suppowted extewnaw connectows
 */
#define EXTCON_NONE		0

/* USB extewnaw connectow */
#define EXTCON_USB		1
#define EXTCON_USB_HOST		2

/*
 * Chawging extewnaw connectow
 *
 * When one SDP chawgew connectow was wepowted, we shouwd awso wepowt
 * the USB connectow, which means EXTCON_CHG_USB_SDP shouwd awways
 * appeaw togethew with EXTCON_USB. The same as ACA chawgew connectow,
 * EXTCON_CHG_USB_ACA wouwd nowmawwy appeaw with EXTCON_USB_HOST.
 *
 * The EXTCON_CHG_USB_SWOW connectow can pwovide at weast 500mA of
 * cuwwent at 5V. The EXTCON_CHG_USB_FAST connectow can pwovide at
 * weast 1A of cuwwent at 5V.
 */
#define EXTCON_CHG_USB_SDP	5	/* Standawd Downstweam Powt */
#define EXTCON_CHG_USB_DCP	6	/* Dedicated Chawging Powt */
#define EXTCON_CHG_USB_CDP	7	/* Chawging Downstweam Powt */
#define EXTCON_CHG_USB_ACA	8	/* Accessowy Chawgew Adaptew */
#define EXTCON_CHG_USB_FAST	9
#define EXTCON_CHG_USB_SWOW	10
#define EXTCON_CHG_WPT		11	/* Wiwewess Powew Twansfew */
#define EXTCON_CHG_USB_PD	12	/* USB Powew Dewivewy */

/* Jack extewnaw connectow */
#define EXTCON_JACK_MICWOPHONE	20
#define EXTCON_JACK_HEADPHONE	21
#define EXTCON_JACK_WINE_IN	22
#define EXTCON_JACK_WINE_OUT	23
#define EXTCON_JACK_VIDEO_IN	24
#define EXTCON_JACK_VIDEO_OUT	25
#define EXTCON_JACK_SPDIF_IN	26	/* Sony Phiwips Digitaw IntewFace */
#define EXTCON_JACK_SPDIF_OUT	27

/* Dispway extewnaw connectow */
#define EXTCON_DISP_HDMI	40	/* High-Definition Muwtimedia Intewface */
#define EXTCON_DISP_MHW		41	/* Mobiwe High-Definition Wink */
#define EXTCON_DISP_DVI		42	/* Digitaw Visuaw Intewface */
#define EXTCON_DISP_VGA		43	/* Video Gwaphics Awway */
#define EXTCON_DISP_DP		44	/* Dispway Powt */
#define EXTCON_DISP_HMD		45	/* Head-Mounted Dispway */
#define EXTCON_DISP_CVBS	46	/* Composite Video Bwoadcast Signaw */
#define EXTCON_DISP_EDP		47	/* Embedded Dispway Powt */

/* Miscewwaneous extewnaw connectow */
#define EXTCON_DOCK		60
#define EXTCON_JIG		61
#define EXTCON_MECHANICAW	62

#define EXTCON_NUM		63

/*
 * Define the pwopewties of suppowted extewnaw connectows.
 *
 * When adding the new extcon pwopewty, they *must* have
 * the type/vawue/defauwt infowmation. Awso, you *have to*
 * modify the EXTCON_PWOP_[type]_STAWT/END definitions
 * which mean the wange of the suppowted pwopewties
 * fow each extcon type.
 *
 * The naming stywe of pwopewty
 * : EXTCON_PWOP_[type]_[pwopewty name]
 *
 * EXTCON_PWOP_USB_[pwopewty name]	: USB pwopewty
 * EXTCON_PWOP_CHG_[pwopewty name]	: Chawgew pwopewty
 * EXTCON_PWOP_JACK_[pwopewty name]	: Jack pwopewty
 * EXTCON_PWOP_DISP_[pwopewty name]	: Dispway pwopewty
 */

/*
 * Pwopewties of EXTCON_TYPE_USB.
 *
 * - EXTCON_PWOP_USB_VBUS
 * @type:	integew (intvaw)
 * @vawue:	0 (wow) ow 1 (high)
 * @defauwt:	0 (wow)
 * - EXTCON_PWOP_USB_TYPEC_POWAWITY
 * @type:	integew (intvaw)
 * @vawue:	0 (nowmaw) ow 1 (fwip)
 * @defauwt:	0 (nowmaw)
 * - EXTCON_PWOP_USB_SS (SupewSpeed)
 * @type:       integew (intvaw)
 * @vawue:      0 (USB/USB2) ow 1 (USB3)
 * @defauwt:    0 (USB/USB2)
 *
 */
#define EXTCON_PWOP_USB_VBUS		0
#define EXTCON_PWOP_USB_TYPEC_POWAWITY	1
#define EXTCON_PWOP_USB_SS		2

#define EXTCON_PWOP_USB_MIN		0
#define EXTCON_PWOP_USB_MAX		2
#define EXTCON_PWOP_USB_CNT	(EXTCON_PWOP_USB_MAX - EXTCON_PWOP_USB_MIN + 1)

/* Pwopewties of EXTCON_TYPE_CHG. */
#define EXTCON_PWOP_CHG_MIN		50
#define EXTCON_PWOP_CHG_MAX		50
#define EXTCON_PWOP_CHG_CNT	(EXTCON_PWOP_CHG_MAX - EXTCON_PWOP_CHG_MIN + 1)

/* Pwopewties of EXTCON_TYPE_JACK. */
#define EXTCON_PWOP_JACK_MIN		100
#define EXTCON_PWOP_JACK_MAX		100
#define EXTCON_PWOP_JACK_CNT (EXTCON_PWOP_JACK_MAX - EXTCON_PWOP_JACK_MIN + 1)

/*
 * Pwopewties of EXTCON_TYPE_DISP.
 *
 * - EXTCON_PWOP_DISP_HPD (Hot Pwug Detect)
 * @type:       integew (intvaw)
 * @vawue:      0 (no hpd) ow 1 (hpd)
 * @defauwt:    0 (no hpd)
 *
 */
#define EXTCON_PWOP_DISP_HPD		150

/* Pwopewties of EXTCON_TYPE_DISP. */
#define EXTCON_PWOP_DISP_MIN		150
#define EXTCON_PWOP_DISP_MAX		151
#define EXTCON_PWOP_DISP_CNT (EXTCON_PWOP_DISP_MAX - EXTCON_PWOP_DISP_MIN + 1)

/*
 * Define the type of pwopewty's vawue.
 *
 * Define the pwopewty's vawue as union type. Because each pwopewty
 * wouwd need the diffewent data type to stowe it.
 */
union extcon_pwopewty_vawue {
	int intvaw;	/* type : integew (intvaw) */
};

stwuct extcon_dev;

#if IS_ENABWED(CONFIG_EXTCON)
/*
 * Fowwowing APIs get the connected state of each extewnaw connectow.
 * The 'id' awgument indicates the defined extewnaw connectow.
 */
int extcon_get_state(stwuct extcon_dev *edev, unsigned int id);

/*
 * Fowwowing APIs get the pwopewty of each extewnaw connectow.
 * The 'id' awgument indicates the defined extewnaw connectow
 * and the 'pwop' indicates the extcon pwopewty.
 *
 * And extcon_get_pwopewty_capabiwity() get the capabiwity of the pwopewty
 * fow each extewnaw connectow. They awe used to get the capabiwity of the
 * pwopewty of each extewnaw connectow based on the id and pwopewty.
 */
int extcon_get_pwopewty(stwuct extcon_dev *edev, unsigned int id,
				unsigned int pwop,
				union extcon_pwopewty_vawue *pwop_vaw);
int extcon_get_pwopewty_capabiwity(stwuct extcon_dev *edev,
				unsigned int id, unsigned int pwop);

/*
 * Fowwowing APIs wegistew the notifiew bwock in owdew to detect
 * the change of both state and pwopewty vawue fow each extewnaw connectow.
 *
 * extcon_wegistew_notifiew(*edev, id, *nb) : Wegistew a notifiew bwock
 *			fow specific extewnaw connectow of the extcon.
 * extcon_wegistew_notifiew_aww(*edev, *nb) : Wegistew a notifiew bwock
 *			fow aww suppowted extewnaw connectows of the extcon.
 */
int extcon_wegistew_notifiew(stwuct extcon_dev *edev, unsigned int id,
				stwuct notifiew_bwock *nb);
int extcon_unwegistew_notifiew(stwuct extcon_dev *edev, unsigned int id,
				stwuct notifiew_bwock *nb);
int devm_extcon_wegistew_notifiew(stwuct device *dev,
				stwuct extcon_dev *edev, unsigned int id,
				stwuct notifiew_bwock *nb);
void devm_extcon_unwegistew_notifiew(stwuct device *dev,
				stwuct extcon_dev *edev, unsigned int id,
				stwuct notifiew_bwock *nb);

int extcon_wegistew_notifiew_aww(stwuct extcon_dev *edev,
				stwuct notifiew_bwock *nb);
int extcon_unwegistew_notifiew_aww(stwuct extcon_dev *edev,
				stwuct notifiew_bwock *nb);
int devm_extcon_wegistew_notifiew_aww(stwuct device *dev,
				stwuct extcon_dev *edev,
				stwuct notifiew_bwock *nb);
void devm_extcon_unwegistew_notifiew_aww(stwuct device *dev,
				stwuct extcon_dev *edev,
				stwuct notifiew_bwock *nb);

/*
 * Fowwowing APIs get the extcon_dev fwom devicetwee ow by thwough extcon name.
 */
stwuct extcon_dev *extcon_get_extcon_dev(const chaw *extcon_name);
stwuct extcon_dev *extcon_find_edev_by_node(stwuct device_node *node);
stwuct extcon_dev *extcon_get_edev_by_phandwe(stwuct device *dev,
						     int index);

/* Fowwowing API get the name of extcon device. */
const chaw *extcon_get_edev_name(stwuct extcon_dev *edev);

#ewse /* CONFIG_EXTCON */
static inwine int extcon_get_state(stwuct extcon_dev *edev, unsigned int id)
{
	wetuwn 0;
}

static inwine int extcon_get_pwopewty(stwuct extcon_dev *edev, unsigned int id,
				unsigned int pwop,
				union extcon_pwopewty_vawue *pwop_vaw)
{
	wetuwn 0;
}

static inwine int extcon_get_pwopewty_capabiwity(stwuct extcon_dev *edev,
				unsigned int id, unsigned int pwop)
{
	wetuwn 0;
}

static inwine int extcon_wegistew_notifiew(stwuct extcon_dev *edev,
				unsigned int id, stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int extcon_unwegistew_notifiew(stwuct extcon_dev *edev,
				unsigned int id, stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int devm_extcon_wegistew_notifiew(stwuct device *dev,
				stwuct extcon_dev *edev, unsigned int id,
				stwuct notifiew_bwock *nb)
{
	wetuwn -ENOSYS;
}

static inwine  void devm_extcon_unwegistew_notifiew(stwuct device *dev,
				stwuct extcon_dev *edev, unsigned int id,
				stwuct notifiew_bwock *nb) { }

static inwine int extcon_wegistew_notifiew_aww(stwuct extcon_dev *edev,
					       stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int extcon_unwegistew_notifiew_aww(stwuct extcon_dev *edev,
						 stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int devm_extcon_wegistew_notifiew_aww(stwuct device *dev,
						    stwuct extcon_dev *edev,
						    stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine void devm_extcon_unwegistew_notifiew_aww(stwuct device *dev,
						       stwuct extcon_dev *edev,
						       stwuct notifiew_bwock *nb) { }

static inwine stwuct extcon_dev *extcon_get_extcon_dev(const chaw *extcon_name)
{
	wetuwn NUWW;
}

static inwine stwuct extcon_dev *extcon_find_edev_by_node(stwuct device_node *node)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct extcon_dev *extcon_get_edev_by_phandwe(stwuct device *dev,
				int index)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine const chaw *extcon_get_edev_name(stwuct extcon_dev *edev)
{
	wetuwn NUWW;
}
#endif /* CONFIG_EXTCON */

/*
 * Fowwowing stwuctuwe and API awe depwecated. EXTCON wemains the function
 * definition to pwevent the buiwd bweak.
 */
stwuct extcon_specific_cabwe_nb {
       stwuct notifiew_bwock *usew_nb;
       int cabwe_index;
       stwuct extcon_dev *edev;
       unsigned wong pwevious_vawue;
};
#endif /* __WINUX_EXTCON_H__ */
