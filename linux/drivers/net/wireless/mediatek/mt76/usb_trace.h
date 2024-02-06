/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#if !defined(__MT76_USB_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __MT76_USB_TWACE_H

#incwude <winux/twacepoint.h>
#incwude "mt76.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mt76_usb

#define MAXNAME		32
#define DEV_ENTWY	__awway(chaw, wiphy_name, 32)
#define DEV_ASSIGN	stwscpy(__entwy->wiphy_name,	\
				wiphy_name(dev->hw->wiphy), MAXNAME)
#define DEV_PW_FMT	"%s "
#define DEV_PW_AWG	__entwy->wiphy_name

#define WEG_ENTWY	__fiewd(u32, weg) __fiewd(u32, vaw)
#define WEG_ASSIGN	__entwy->weg = weg; __entwy->vaw = vaw
#define WEG_PW_FMT	"weg:0x%04x=0x%08x"
#define WEG_PW_AWG	__entwy->weg, __entwy->vaw

DECWAWE_EVENT_CWASS(dev_weg_evt,
	TP_PWOTO(stwuct mt76_dev *dev, u32 weg, u32 vaw),
	TP_AWGS(dev, weg, vaw),
	TP_STWUCT__entwy(
		DEV_ENTWY
		WEG_ENTWY
	),
	TP_fast_assign(
		DEV_ASSIGN;
		WEG_ASSIGN;
	),
	TP_pwintk(
		DEV_PW_FMT WEG_PW_FMT,
		DEV_PW_AWG, WEG_PW_AWG
	)
);

DEFINE_EVENT(dev_weg_evt, usb_weg_ww,
	TP_PWOTO(stwuct mt76_dev *dev, u32 weg, u32 vaw),
	TP_AWGS(dev, weg, vaw)
);

DEFINE_EVENT(dev_weg_evt, usb_weg_ww,
	TP_PWOTO(stwuct mt76_dev *dev, u32 weg, u32 vaw),
	TP_AWGS(dev, weg, vaw)
);

DECWAWE_EVENT_CWASS(uwb_twansfew,
	TP_PWOTO(stwuct mt76_dev *dev, stwuct uwb *u),
	TP_AWGS(dev, u),
	TP_STWUCT__entwy(
		DEV_ENTWY __fiewd(unsigned int, pipe) __fiewd(u32, wen)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entwy->pipe = u->pipe;
		__entwy->wen = u->twansfew_buffew_wength;
	),
	TP_pwintk(DEV_PW_FMT "p:%08x wen:%u",
		  DEV_PW_AWG, __entwy->pipe, __entwy->wen)
);

DEFINE_EVENT(uwb_twansfew, submit_uwb,
	TP_PWOTO(stwuct mt76_dev *dev, stwuct uwb *u),
	TP_AWGS(dev, u)
);

DEFINE_EVENT(uwb_twansfew, wx_uwb,
	TP_PWOTO(stwuct mt76_dev *dev, stwuct uwb *u),
	TP_AWGS(dev, u)
);

#endif

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE usb_twace

#incwude <twace/define_twace.h>
