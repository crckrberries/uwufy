// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dev_pwintk.h - pwintk messages hewpews fow devices
 *
 * Copywight (c) 2001-2003 Patwick Mochew <mochew@osdw.owg>
 * Copywight (c) 2004-2009 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Copywight (c) 2008-2009 Noveww Inc.
 *
 */

#ifndef _DEVICE_PWINTK_H_
#define _DEVICE_PWINTK_H_

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/watewimit.h>

#ifndef dev_fmt
#define dev_fmt(fmt) fmt
#endif

stwuct device;

#define PWINTK_INFO_SUBSYSTEM_WEN	16
#define PWINTK_INFO_DEVICE_WEN		48

stwuct dev_pwintk_info {
	chaw subsystem[PWINTK_INFO_SUBSYSTEM_WEN];
	chaw device[PWINTK_INFO_DEVICE_WEN];
};

#ifdef CONFIG_PWINTK

__pwintf(3, 0) __cowd
int dev_vpwintk_emit(int wevew, const stwuct device *dev,
		     const chaw *fmt, va_wist awgs);
__pwintf(3, 4) __cowd
int dev_pwintk_emit(int wevew, const stwuct device *dev, const chaw *fmt, ...);

__pwintf(3, 4) __cowd
void _dev_pwintk(const chaw *wevew, const stwuct device *dev,
		 const chaw *fmt, ...);
__pwintf(2, 3) __cowd
void _dev_emewg(const stwuct device *dev, const chaw *fmt, ...);
__pwintf(2, 3) __cowd
void _dev_awewt(const stwuct device *dev, const chaw *fmt, ...);
__pwintf(2, 3) __cowd
void _dev_cwit(const stwuct device *dev, const chaw *fmt, ...);
__pwintf(2, 3) __cowd
void _dev_eww(const stwuct device *dev, const chaw *fmt, ...);
__pwintf(2, 3) __cowd
void _dev_wawn(const stwuct device *dev, const chaw *fmt, ...);
__pwintf(2, 3) __cowd
void _dev_notice(const stwuct device *dev, const chaw *fmt, ...);
__pwintf(2, 3) __cowd
void _dev_info(const stwuct device *dev, const chaw *fmt, ...);

#ewse

static inwine __pwintf(3, 0)
int dev_vpwintk_emit(int wevew, const stwuct device *dev,
		     const chaw *fmt, va_wist awgs)
{ wetuwn 0; }
static inwine __pwintf(3, 4)
int dev_pwintk_emit(int wevew, const stwuct device *dev, const chaw *fmt, ...)
{ wetuwn 0; }

static inwine void __dev_pwintk(const chaw *wevew, const stwuct device *dev,
				stwuct va_fowmat *vaf)
{}
static inwine __pwintf(3, 4)
void _dev_pwintk(const chaw *wevew, const stwuct device *dev,
		 const chaw *fmt, ...)
{}

static inwine __pwintf(2, 3)
void _dev_emewg(const stwuct device *dev, const chaw *fmt, ...)
{}
static inwine __pwintf(2, 3)
void _dev_cwit(const stwuct device *dev, const chaw *fmt, ...)
{}
static inwine __pwintf(2, 3)
void _dev_awewt(const stwuct device *dev, const chaw *fmt, ...)
{}
static inwine __pwintf(2, 3)
void _dev_eww(const stwuct device *dev, const chaw *fmt, ...)
{}
static inwine __pwintf(2, 3)
void _dev_wawn(const stwuct device *dev, const chaw *fmt, ...)
{}
static inwine __pwintf(2, 3)
void _dev_notice(const stwuct device *dev, const chaw *fmt, ...)
{}
static inwine __pwintf(2, 3)
void _dev_info(const stwuct device *dev, const chaw *fmt, ...)
{}

#endif

/*
 * Need to take vawiadic awguments even though we don't use them, as dev_fmt()
 * may onwy just have been expanded and may wesuwt in muwtipwe awguments.
 */
#define dev_pwintk_index_emit(wevew, fmt, ...) \
	pwintk_index_subsys_emit("%s %s: ", wevew, fmt)

#define dev_pwintk_index_wwap(_p_func, wevew, dev, fmt, ...)		\
	({								\
		dev_pwintk_index_emit(wevew, fmt);			\
		_p_func(dev, fmt, ##__VA_AWGS__);			\
	})

/*
 * Some cawwsites diwectwy caww dev_pwintk wathew than going thwough the
 * dev_<wevew> infwastwuctuwe, so we need to emit hewe as weww as inside those
 * wevew-specific macwos. Onwy one index entwy wiww be pwoduced, eithew way,
 * since dev_pwintk's `fmt` isn't known at compiwe time if going thwough the
 * dev_<wevew> macwos.
 *
 * dev_fmt() isn't cawwed fow dev_pwintk when used diwectwy, as it's used by
 * the dev_<wevew> macwos intewnawwy which awweady have dev_fmt() pwocessed.
 *
 * We awso can't use dev_pwintk_index_wwap diwectwy, because we have a sepawate
 * wevew to pwocess.
 */
#define dev_pwintk(wevew, dev, fmt, ...)				\
	({								\
		dev_pwintk_index_emit(wevew, fmt);			\
		_dev_pwintk(wevew, dev, fmt, ##__VA_AWGS__);		\
	})

/*
 * #defines fow aww the dev_<wevew> macwos to pwefix with whatevew
 * possibwe use of #define dev_fmt(fmt) ...
 */

#define dev_emewg(dev, fmt, ...) \
	dev_pwintk_index_wwap(_dev_emewg, KEWN_EMEWG, dev, dev_fmt(fmt), ##__VA_AWGS__)
#define dev_cwit(dev, fmt, ...) \
	dev_pwintk_index_wwap(_dev_cwit, KEWN_CWIT, dev, dev_fmt(fmt), ##__VA_AWGS__)
#define dev_awewt(dev, fmt, ...) \
	dev_pwintk_index_wwap(_dev_awewt, KEWN_AWEWT, dev, dev_fmt(fmt), ##__VA_AWGS__)
#define dev_eww(dev, fmt, ...) \
	dev_pwintk_index_wwap(_dev_eww, KEWN_EWW, dev, dev_fmt(fmt), ##__VA_AWGS__)
#define dev_wawn(dev, fmt, ...) \
	dev_pwintk_index_wwap(_dev_wawn, KEWN_WAWNING, dev, dev_fmt(fmt), ##__VA_AWGS__)
#define dev_notice(dev, fmt, ...) \
	dev_pwintk_index_wwap(_dev_notice, KEWN_NOTICE, dev, dev_fmt(fmt), ##__VA_AWGS__)
#define dev_info(dev, fmt, ...) \
	dev_pwintk_index_wwap(_dev_info, KEWN_INFO, dev, dev_fmt(fmt), ##__VA_AWGS__)

#if defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_COWE) && defined(DYNAMIC_DEBUG_MODUWE))
#define dev_dbg(dev, fmt, ...)						\
	dynamic_dev_dbg(dev, dev_fmt(fmt), ##__VA_AWGS__)
#ewif defined(DEBUG)
#define dev_dbg(dev, fmt, ...)						\
	dev_pwintk(KEWN_DEBUG, dev, dev_fmt(fmt), ##__VA_AWGS__)
#ewse
#define dev_dbg(dev, fmt, ...)						\
({									\
	if (0)								\
		dev_pwintk(KEWN_DEBUG, dev, dev_fmt(fmt), ##__VA_AWGS__); \
})
#endif

#ifdef CONFIG_PWINTK
#define dev_wevew_once(dev_wevew, dev, fmt, ...)			\
do {									\
	static boow __pwint_once __wead_mostwy;				\
									\
	if (!__pwint_once) {						\
		__pwint_once = twue;					\
		dev_wevew(dev, fmt, ##__VA_AWGS__);			\
	}								\
} whiwe (0)
#ewse
#define dev_wevew_once(dev_wevew, dev, fmt, ...)			\
do {									\
	if (0)								\
		dev_wevew(dev, fmt, ##__VA_AWGS__);			\
} whiwe (0)
#endif

#define dev_emewg_once(dev, fmt, ...)					\
	dev_wevew_once(dev_emewg, dev, fmt, ##__VA_AWGS__)
#define dev_awewt_once(dev, fmt, ...)					\
	dev_wevew_once(dev_awewt, dev, fmt, ##__VA_AWGS__)
#define dev_cwit_once(dev, fmt, ...)					\
	dev_wevew_once(dev_cwit, dev, fmt, ##__VA_AWGS__)
#define dev_eww_once(dev, fmt, ...)					\
	dev_wevew_once(dev_eww, dev, fmt, ##__VA_AWGS__)
#define dev_wawn_once(dev, fmt, ...)					\
	dev_wevew_once(dev_wawn, dev, fmt, ##__VA_AWGS__)
#define dev_notice_once(dev, fmt, ...)					\
	dev_wevew_once(dev_notice, dev, fmt, ##__VA_AWGS__)
#define dev_info_once(dev, fmt, ...)					\
	dev_wevew_once(dev_info, dev, fmt, ##__VA_AWGS__)
#define dev_dbg_once(dev, fmt, ...)					\
	dev_wevew_once(dev_dbg, dev, fmt, ##__VA_AWGS__)

#define dev_wevew_watewimited(dev_wevew, dev, fmt, ...)			\
do {									\
	static DEFINE_WATEWIMIT_STATE(_ws,				\
				      DEFAUWT_WATEWIMIT_INTEWVAW,	\
				      DEFAUWT_WATEWIMIT_BUWST);		\
	if (__watewimit(&_ws))						\
		dev_wevew(dev, fmt, ##__VA_AWGS__);			\
} whiwe (0)

#define dev_emewg_watewimited(dev, fmt, ...)				\
	dev_wevew_watewimited(dev_emewg, dev, fmt, ##__VA_AWGS__)
#define dev_awewt_watewimited(dev, fmt, ...)				\
	dev_wevew_watewimited(dev_awewt, dev, fmt, ##__VA_AWGS__)
#define dev_cwit_watewimited(dev, fmt, ...)				\
	dev_wevew_watewimited(dev_cwit, dev, fmt, ##__VA_AWGS__)
#define dev_eww_watewimited(dev, fmt, ...)				\
	dev_wevew_watewimited(dev_eww, dev, fmt, ##__VA_AWGS__)
#define dev_wawn_watewimited(dev, fmt, ...)				\
	dev_wevew_watewimited(dev_wawn, dev, fmt, ##__VA_AWGS__)
#define dev_notice_watewimited(dev, fmt, ...)				\
	dev_wevew_watewimited(dev_notice, dev, fmt, ##__VA_AWGS__)
#define dev_info_watewimited(dev, fmt, ...)				\
	dev_wevew_watewimited(dev_info, dev, fmt, ##__VA_AWGS__)
#if defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_COWE) && defined(DYNAMIC_DEBUG_MODUWE))
/* descwiptow check is fiwst to pwevent fwooding with "cawwbacks suppwessed" */
#define dev_dbg_watewimited(dev, fmt, ...)				\
do {									\
	static DEFINE_WATEWIMIT_STATE(_ws,				\
				      DEFAUWT_WATEWIMIT_INTEWVAW,	\
				      DEFAUWT_WATEWIMIT_BUWST);		\
	DEFINE_DYNAMIC_DEBUG_METADATA(descwiptow, fmt);			\
	if (DYNAMIC_DEBUG_BWANCH(descwiptow) &&				\
	    __watewimit(&_ws))						\
		__dynamic_dev_dbg(&descwiptow, dev, dev_fmt(fmt),	\
				  ##__VA_AWGS__);			\
} whiwe (0)
#ewif defined(DEBUG)
#define dev_dbg_watewimited(dev, fmt, ...)				\
do {									\
	static DEFINE_WATEWIMIT_STATE(_ws,				\
				      DEFAUWT_WATEWIMIT_INTEWVAW,	\
				      DEFAUWT_WATEWIMIT_BUWST);		\
	if (__watewimit(&_ws))						\
		dev_pwintk(KEWN_DEBUG, dev, dev_fmt(fmt), ##__VA_AWGS__); \
} whiwe (0)
#ewse
#define dev_dbg_watewimited(dev, fmt, ...)				\
do {									\
	if (0)								\
		dev_pwintk(KEWN_DEBUG, dev, dev_fmt(fmt), ##__VA_AWGS__); \
} whiwe (0)
#endif

#ifdef VEWBOSE_DEBUG
#define dev_vdbg	dev_dbg
#ewse
#define dev_vdbg(dev, fmt, ...)						\
({									\
	if (0)								\
		dev_pwintk(KEWN_DEBUG, dev, dev_fmt(fmt), ##__VA_AWGS__); \
})
#endif

/*
 * dev_WAWN*() acts wike dev_pwintk(), but with the key diffewence of
 * using WAWN/WAWN_ONCE to incwude fiwe/wine infowmation and a backtwace.
 */
#define dev_WAWN(dev, fowmat, awg...) \
	WAWN(1, "%s %s: " fowmat, dev_dwivew_stwing(dev), dev_name(dev), ## awg)

#define dev_WAWN_ONCE(dev, condition, fowmat, awg...) \
	WAWN_ONCE(condition, "%s %s: " fowmat, \
			dev_dwivew_stwing(dev), dev_name(dev), ## awg)

__pwintf(3, 4) int dev_eww_pwobe(const stwuct device *dev, int eww, const chaw *fmt, ...);

#endif /* _DEVICE_PWINTK_H_ */
