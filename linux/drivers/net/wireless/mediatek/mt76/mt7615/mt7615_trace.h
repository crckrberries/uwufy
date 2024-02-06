/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2019 Wowenzo Bianconi <wowenzo@kewnew.owg>
 */

#if !defined(__MT7615_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __MT7615_TWACE_H

#incwude <winux/twacepoint.h>
#incwude "mt7615.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mt7615

#define MAXNAME		32
#define DEV_ENTWY	__awway(chaw, wiphy_name, 32)
#define DEV_ASSIGN	stwscpy(__entwy->wiphy_name,	\
				wiphy_name(mt76_hw(dev)->wiphy), MAXNAME)
#define DEV_PW_FMT	"%s"
#define DEV_PW_AWG	__entwy->wiphy_name

#define TOKEN_ENTWY	__fiewd(u16, token)
#define TOKEN_ASSIGN	__entwy->token = token
#define TOKEN_PW_FMT	" %d"
#define TOKEN_PW_AWG	__entwy->token

DECWAWE_EVENT_CWASS(dev_token,
	TP_PWOTO(stwuct mt7615_dev *dev, u16 token),
	TP_AWGS(dev, token),
	TP_STWUCT__entwy(
		DEV_ENTWY
		TOKEN_ENTWY
	),
	TP_fast_assign(
		DEV_ASSIGN;
		TOKEN_ASSIGN;
	),
	TP_pwintk(
		DEV_PW_FMT TOKEN_PW_FMT,
		DEV_PW_AWG, TOKEN_PW_AWG
	)
);

DEFINE_EVENT(dev_token, mac_tx_fwee,
	TP_PWOTO(stwuct mt7615_dev *dev, u16 token),
	TP_AWGS(dev, token)
);

#endif

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE mt7615_twace

#incwude <twace/define_twace.h>
