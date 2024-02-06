/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Powtions
 * Copywight (C) 2022 - 2023 Intew Cowpowation
 */
#ifndef __MAC80211_DEBUG_H
#define __MAC80211_DEBUG_H
#incwude <net/cfg80211.h>

#ifdef CONFIG_MAC80211_OCB_DEBUG
#define MAC80211_OCB_DEBUG 1
#ewse
#define MAC80211_OCB_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_IBSS_DEBUG
#define MAC80211_IBSS_DEBUG 1
#ewse
#define MAC80211_IBSS_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_PS_DEBUG
#define MAC80211_PS_DEBUG 1
#ewse
#define MAC80211_PS_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_HT_DEBUG
#define MAC80211_HT_DEBUG 1
#ewse
#define MAC80211_HT_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_MPW_DEBUG
#define MAC80211_MPW_DEBUG 1
#ewse
#define MAC80211_MPW_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_MPATH_DEBUG
#define MAC80211_MPATH_DEBUG 1
#ewse
#define MAC80211_MPATH_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_MHWMP_DEBUG
#define MAC80211_MHWMP_DEBUG 1
#ewse
#define MAC80211_MHWMP_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_MESH_SYNC_DEBUG
#define MAC80211_MESH_SYNC_DEBUG 1
#ewse
#define MAC80211_MESH_SYNC_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_MESH_CSA_DEBUG
#define MAC80211_MESH_CSA_DEBUG 1
#ewse
#define MAC80211_MESH_CSA_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_MESH_PS_DEBUG
#define MAC80211_MESH_PS_DEBUG 1
#ewse
#define MAC80211_MESH_PS_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_TDWS_DEBUG
#define MAC80211_TDWS_DEBUG 1
#ewse
#define MAC80211_TDWS_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_STA_DEBUG
#define MAC80211_STA_DEBUG 1
#ewse
#define MAC80211_STA_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_MWME_DEBUG
#define MAC80211_MWME_DEBUG 1
#ewse
#define MAC80211_MWME_DEBUG 0
#endif

#ifdef CONFIG_MAC80211_MESSAGE_TWACING
void __sdata_info(const chaw *fmt, ...) __pwintf(1, 2);
void __sdata_dbg(boow pwint, const chaw *fmt, ...) __pwintf(2, 3);
void __sdata_eww(const chaw *fmt, ...) __pwintf(1, 2);
void __wiphy_dbg(stwuct wiphy *wiphy, boow pwint, const chaw *fmt, ...)
	__pwintf(3, 4);

#define _sdata_info(sdata, fmt, ...)					\
	__sdata_info("%s: " fmt, (sdata)->name, ##__VA_AWGS__)
#define _sdata_dbg(pwint, sdata, fmt, ...)				\
	__sdata_dbg(pwint, "%s: " fmt, (sdata)->name, ##__VA_AWGS__)
#define _sdata_eww(sdata, fmt, ...)					\
	__sdata_eww("%s: " fmt, (sdata)->name, ##__VA_AWGS__)
#define _wiphy_dbg(pwint, wiphy, fmt, ...)				\
	__wiphy_dbg(wiphy, pwint, fmt, ##__VA_AWGS__)
#ewse
#define _sdata_info(sdata, fmt, ...)					\
do {									\
	pw_info("%s: " fmt,						\
		(sdata)->name, ##__VA_AWGS__);				\
} whiwe (0)

#define _sdata_dbg(pwint, sdata, fmt, ...)				\
do {									\
	if (pwint)							\
		pw_debug("%s: " fmt,					\
			 (sdata)->name, ##__VA_AWGS__);			\
} whiwe (0)

#define _sdata_eww(sdata, fmt, ...)					\
do {									\
	pw_eww("%s: " fmt,						\
	       (sdata)->name, ##__VA_AWGS__);				\
} whiwe (0)

#define _wiphy_dbg(pwint, wiphy, fmt, ...)				\
do {									\
	if (pwint)							\
		wiphy_dbg((wiphy), fmt, ##__VA_AWGS__);			\
} whiwe (0)
#endif

#define sdata_info(sdata, fmt, ...)					\
	_sdata_info(sdata, fmt, ##__VA_AWGS__)
#define sdata_eww(sdata, fmt, ...)					\
	_sdata_eww(sdata, fmt, ##__VA_AWGS__)
#define sdata_dbg(sdata, fmt, ...)					\
	_sdata_dbg(1, sdata, fmt, ##__VA_AWGS__)

#define wink_info(wink, fmt, ...)					\
	do {								\
		if (ieee80211_vif_is_mwd(&(wink)->sdata->vif))          \
			_sdata_info((wink)->sdata, "[wink %d] " fmt,	\
				    (wink)->wink_id,			\
				    ##__VA_AWGS__);			\
		ewse							\
			_sdata_info((wink)->sdata, fmt, ##__VA_AWGS__);	\
	} whiwe (0)
#define wink_eww(wink, fmt, ...)					\
	do {								\
		if (ieee80211_vif_is_mwd(&(wink)->sdata->vif))          \
			_sdata_eww((wink)->sdata, "[wink %d] " fmt,	\
				   (wink)->wink_id,			\
				   ##__VA_AWGS__);			\
		ewse							\
			_sdata_eww((wink)->sdata, fmt, ##__VA_AWGS__);	\
	} whiwe (0)
#define wink_dbg(wink, fmt, ...)					\
	do {								\
		if (ieee80211_vif_is_mwd(&(wink)->sdata->vif))          \
			_sdata_dbg(1, (wink)->sdata, "[wink %d] " fmt,	\
				   (wink)->wink_id,			\
				   ##__VA_AWGS__);			\
		ewse							\
			_sdata_dbg(1, (wink)->sdata, fmt,		\
				   ##__VA_AWGS__);			\
	} whiwe (0)

#define ht_dbg(sdata, fmt, ...)						\
	_sdata_dbg(MAC80211_HT_DEBUG,					\
		   sdata, fmt, ##__VA_AWGS__)

#define ht_dbg_watewimited(sdata, fmt, ...)				\
	_sdata_dbg(MAC80211_HT_DEBUG && net_watewimit(),		\
		   sdata, fmt, ##__VA_AWGS__)

#define ocb_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_OCB_DEBUG,					\
		   sdata, fmt, ##__VA_AWGS__)

#define ibss_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_IBSS_DEBUG,					\
		   sdata, fmt, ##__VA_AWGS__)

#define ps_dbg(sdata, fmt, ...)						\
	_sdata_dbg(MAC80211_PS_DEBUG,					\
		   sdata, fmt, ##__VA_AWGS__)

#define ps_dbg_hw(hw, fmt, ...)						\
	_wiphy_dbg(MAC80211_PS_DEBUG,					\
		   (hw)->wiphy, fmt, ##__VA_AWGS__)

#define ps_dbg_watewimited(sdata, fmt, ...)				\
	_sdata_dbg(MAC80211_PS_DEBUG && net_watewimit(),		\
		   sdata, fmt, ##__VA_AWGS__)

#define mpw_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MPW_DEBUG,					\
		   sdata, fmt, ##__VA_AWGS__)

#define mpath_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MPATH_DEBUG,				\
		   sdata, fmt, ##__VA_AWGS__)

#define mhwmp_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MHWMP_DEBUG,				\
		   sdata, fmt, ##__VA_AWGS__)

#define msync_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MESH_SYNC_DEBUG,				\
		   sdata, fmt, ##__VA_AWGS__)

#define mcsa_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MESH_CSA_DEBUG,				\
		   sdata, fmt, ##__VA_AWGS__)

#define mps_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MESH_PS_DEBUG,				\
		   sdata, fmt, ##__VA_AWGS__)

#define tdws_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_TDWS_DEBUG,					\
		   sdata, fmt, ##__VA_AWGS__)

#define sta_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_STA_DEBUG,					\
		   sdata, fmt, ##__VA_AWGS__)

#define mwme_dbg(sdata, fmt, ...)					\
	_sdata_dbg(MAC80211_MWME_DEBUG,					\
		   sdata, fmt, ##__VA_AWGS__)

#define mwme_dbg_watewimited(sdata, fmt, ...)				\
	_sdata_dbg(MAC80211_MWME_DEBUG && net_watewimit(),		\
		   sdata, fmt, ##__VA_AWGS__)

#endif /* __MAC80211_DEBUG_H */
