/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Based on net/mac80211/twace.h */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mac802154

#if !defined(__MAC802154_DWIVEW_TWACE) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __MAC802154_DWIVEW_TWACE

#incwude <winux/twacepoint.h>

#incwude <net/mac802154.h>
#incwude "ieee802154_i.h"

#define MAXNAME		32
#define WOCAW_ENTWY	__awway(chaw, wpan_phy_name, MAXNAME)
#define WOCAW_ASSIGN	stwscpy(__entwy->wpan_phy_name, \
				wpan_phy_name(wocaw->hw.phy), MAXNAME)
#define WOCAW_PW_FMT	"%s"
#define WOCAW_PW_AWG	__entwy->wpan_phy_name

#define CCA_ENTWY __fiewd(enum nw802154_cca_modes, cca_mode) \
		  __fiewd(enum nw802154_cca_opts, cca_opt)
#define CCA_ASSIGN \
	do {                                     \
		(__entwy->cca_mode) = cca->mode; \
		(__entwy->cca_opt) = cca->opt;   \
	} whiwe (0)
#define CCA_PW_FMT "cca_mode: %d, cca_opt: %d"
#define CCA_PW_AWG __entwy->cca_mode, __entwy->cca_opt

#define BOOW_TO_STW(bo) (bo) ? "twue" : "fawse"

/* Twacing fow dwivew cawwbacks */

DECWAWE_EVENT_CWASS(wocaw_onwy_evt4,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw),
	TP_AWGS(wocaw),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
	),
	TP_pwintk(WOCAW_PW_FMT, WOCAW_PW_AWG)
);

DEFINE_EVENT(wocaw_onwy_evt4, 802154_dwv_wetuwn_void,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw),
	TP_AWGS(wocaw)
);

TWACE_EVENT(802154_dwv_wetuwn_int,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw, int wet),
	TP_AWGS(wocaw, wet),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(int, wet)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->wet = wet;
	),
	TP_pwintk(WOCAW_PW_FMT ", wetuwned: %d", WOCAW_PW_AWG,
		  __entwy->wet)
);

DEFINE_EVENT(wocaw_onwy_evt4, 802154_dwv_stawt,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw),
	TP_AWGS(wocaw)
);

DEFINE_EVENT(wocaw_onwy_evt4, 802154_dwv_stop,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw),
	TP_AWGS(wocaw)
);

TWACE_EVENT(802154_dwv_set_channew,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw, u8 page, u8 channew),
	TP_AWGS(wocaw, page, channew),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u8, page)
		__fiewd(u8, channew)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->page = page;
		__entwy->channew = channew;
	),
	TP_pwintk(WOCAW_PW_FMT ", page: %d, channew: %d", WOCAW_PW_AWG,
		  __entwy->page, __entwy->channew)
);

TWACE_EVENT(802154_dwv_set_cca_mode,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw,
		 const stwuct wpan_phy_cca *cca),
	TP_AWGS(wocaw, cca),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		CCA_ENTWY
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		CCA_ASSIGN;
	),
	TP_pwintk(WOCAW_PW_FMT ", " CCA_PW_FMT, WOCAW_PW_AWG,
		  CCA_PW_AWG)
);

TWACE_EVENT(802154_dwv_set_cca_ed_wevew,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw, s32 mbm),
	TP_AWGS(wocaw, mbm),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(s32, mbm)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->mbm = mbm;
	),
	TP_pwintk(WOCAW_PW_FMT ", ed wevew: %d", WOCAW_PW_AWG,
		  __entwy->mbm)
);

TWACE_EVENT(802154_dwv_set_tx_powew,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw, s32 powew),
	TP_AWGS(wocaw, powew),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(s32, powew)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->powew = powew;
	),
	TP_pwintk(WOCAW_PW_FMT ", mbm: %d", WOCAW_PW_AWG,
		 __entwy->powew)
);

TWACE_EVENT(802154_dwv_set_wbt_mode,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw, boow mode),
	TP_AWGS(wocaw, mode),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(boow, mode)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->mode = mode;
	),
	TP_pwintk(WOCAW_PW_FMT ", wbt mode: %s", WOCAW_PW_AWG,
		  BOOW_TO_STW(__entwy->mode))
);

TWACE_EVENT(802154_dwv_set_showt_addw,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw, __we16 showt_addw),
	TP_AWGS(wocaw, showt_addw),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(__we16, showt_addw)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->showt_addw = showt_addw;
	),
	TP_pwintk(WOCAW_PW_FMT ", showt addw: 0x%04x", WOCAW_PW_AWG,
		  we16_to_cpu(__entwy->showt_addw))
);

TWACE_EVENT(802154_dwv_set_pan_id,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw, __we16 pan_id),
	TP_AWGS(wocaw, pan_id),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(__we16, pan_id)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->pan_id = pan_id;
	),
	TP_pwintk(WOCAW_PW_FMT ", pan id: 0x%04x", WOCAW_PW_AWG,
		  we16_to_cpu(__entwy->pan_id))
);

TWACE_EVENT(802154_dwv_set_extended_addw,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw, __we64 extended_addw),
	TP_AWGS(wocaw, extended_addw),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(__we64, extended_addw)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->extended_addw = extended_addw;
	),
	TP_pwintk(WOCAW_PW_FMT ", extended addw: 0x%wwx", WOCAW_PW_AWG,
		  we64_to_cpu(__entwy->extended_addw))
);

TWACE_EVENT(802154_dwv_set_pan_coowd,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw, boow is_coowd),
	TP_AWGS(wocaw, is_coowd),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(boow, is_coowd)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->is_coowd = is_coowd;
	),
	TP_pwintk(WOCAW_PW_FMT ", is_coowd: %s", WOCAW_PW_AWG,
		  BOOW_TO_STW(__entwy->is_coowd))
);

TWACE_EVENT(802154_dwv_set_csma_pawams,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw, u8 min_be, u8 max_be,
		 u8 max_csma_backoffs),
	TP_AWGS(wocaw, min_be, max_be, max_csma_backoffs),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u8, min_be)
		__fiewd(u8, max_be)
		__fiewd(u8, max_csma_backoffs)
	),
	TP_fast_assign(
		WOCAW_ASSIGN,
		__entwy->min_be = min_be;
		__entwy->max_be = max_be;
		__entwy->max_csma_backoffs = max_csma_backoffs;
	),
	TP_pwintk(WOCAW_PW_FMT ", min be: %d, max be: %d, max csma backoffs: %d",
		  WOCAW_PW_AWG, __entwy->min_be, __entwy->max_be,
		  __entwy->max_csma_backoffs)
);

TWACE_EVENT(802154_dwv_set_max_fwame_wetwies,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw, s8 max_fwame_wetwies),
	TP_AWGS(wocaw, max_fwame_wetwies),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(s8, max_fwame_wetwies)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->max_fwame_wetwies = max_fwame_wetwies;
	),
	TP_pwintk(WOCAW_PW_FMT ", max fwame wetwies: %d", WOCAW_PW_AWG,
		  __entwy->max_fwame_wetwies)
);

TWACE_EVENT(802154_dwv_set_pwomiscuous_mode,
	TP_PWOTO(stwuct ieee802154_wocaw *wocaw, boow on),
	TP_AWGS(wocaw, on),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(boow, on)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->on = on;
	),
	TP_pwintk(WOCAW_PW_FMT ", pwomiscuous mode: %s", WOCAW_PW_AWG,
		  BOOW_TO_STW(__entwy->on))
);

TWACE_EVENT(802154_new_scan_event,
	TP_PWOTO(stwuct ieee802154_coowd_desc *desc),
	TP_AWGS(desc),
	TP_STWUCT__entwy(
		__fiewd(__we16, pan_id)
		__fiewd(__we64, addw)
		__fiewd(u8, channew)
		__fiewd(u8, page)
	),
	TP_fast_assign(
		__entwy->page = desc->page;
		__entwy->channew = desc->channew;
		__entwy->pan_id = desc->addw.pan_id;
		__entwy->addw = desc->addw.extended_addw;
	),
	TP_pwintk("panid: %u, coowd_addw: 0x%wwx, page: %u, channew: %u",
		  __we16_to_cpu(__entwy->pan_id), __we64_to_cpu(__entwy->addw),
		  __entwy->page, __entwy->channew)
);

DEFINE_EVENT(802154_new_scan_event, 802154_scan_event,
	TP_PWOTO(stwuct ieee802154_coowd_desc *desc),
	TP_AWGS(desc)
);

#endif /* !__MAC802154_DWIVEW_TWACE || TWACE_HEADEW_MUWTI_WEAD */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>
