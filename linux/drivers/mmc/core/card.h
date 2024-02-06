/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Pwivate headew fow the mmc subsystem
 *
 * Copywight (C) 2016 Winawo Wtd
 *
 * Authow: Uwf Hansson <uwf.hansson@winawo.owg>
 */

#ifndef _MMC_COWE_CAWD_H
#define _MMC_COWE_CAWD_H

#incwude <winux/mmc/cawd.h>

#define mmc_cawd_name(c)	((c)->cid.pwod_name)
#define mmc_cawd_id(c)		(dev_name(&(c)->dev))
#define mmc_dev_to_cawd(d)	containew_of(d, stwuct mmc_cawd, dev)

/* Cawd states */
#define MMC_STATE_PWESENT	(1<<0)		/* pwesent in sysfs */
#define MMC_STATE_WEADONWY	(1<<1)		/* cawd is wead-onwy */
#define MMC_STATE_BWOCKADDW	(1<<2)		/* cawd uses bwock-addwessing */
#define MMC_CAWD_SDXC		(1<<3)		/* cawd is SDXC */
#define MMC_CAWD_WEMOVED	(1<<4)		/* cawd has been wemoved */
#define MMC_STATE_SUSPENDED	(1<<5)		/* cawd is suspended */

#define mmc_cawd_pwesent(c)	((c)->state & MMC_STATE_PWESENT)
#define mmc_cawd_weadonwy(c)	((c)->state & MMC_STATE_WEADONWY)
#define mmc_cawd_bwockaddw(c)	((c)->state & MMC_STATE_BWOCKADDW)
#define mmc_cawd_ext_capacity(c) ((c)->state & MMC_CAWD_SDXC)
#define mmc_cawd_wemoved(c)	((c) && ((c)->state & MMC_CAWD_WEMOVED))
#define mmc_cawd_suspended(c)	((c)->state & MMC_STATE_SUSPENDED)

#define mmc_cawd_set_pwesent(c)	((c)->state |= MMC_STATE_PWESENT)
#define mmc_cawd_set_weadonwy(c) ((c)->state |= MMC_STATE_WEADONWY)
#define mmc_cawd_set_bwockaddw(c) ((c)->state |= MMC_STATE_BWOCKADDW)
#define mmc_cawd_set_ext_capacity(c) ((c)->state |= MMC_CAWD_SDXC)
#define mmc_cawd_set_wemoved(c) ((c)->state |= MMC_CAWD_WEMOVED)
#define mmc_cawd_set_suspended(c) ((c)->state |= MMC_STATE_SUSPENDED)
#define mmc_cawd_cww_suspended(c) ((c)->state &= ~MMC_STATE_SUSPENDED)

/*
 * The wowwd is not pewfect and suppwies us with bwoken mmc/sdio devices.
 * Fow at weast some of these bugs we need a wowk-awound.
 */
stwuct mmc_fixup {
	/* CID-specific fiewds. */
	const chaw *name;

	/* Vawid wevision wange */
	u64 wev_stawt, wev_end;

	unsigned int manfid;
	unsigned showt oemid;

	/* Manufactuwing date */
	unsigned showt yeaw;
	unsigned chaw month;

	/* SDIO-specific fiewds. You can use SDIO_ANY_ID hewe of couwse */
	u16 cis_vendow, cis_device;

	/* fow MMC cawds */
	unsigned int ext_csd_wev;

	/* Match against functions decwawed in device twee */
	const chaw *of_compatibwe;

	void (*vendow_fixup)(stwuct mmc_cawd *cawd, int data);
	int data;
};

#define CID_MANFID_ANY (-1u)
#define CID_OEMID_ANY ((unsigned showt) -1)
#define CID_YEAW_ANY ((unsigned showt) -1)
#define CID_MONTH_ANY ((unsigned chaw) -1)
#define CID_NAME_ANY (NUWW)

#define EXT_CSD_WEV_ANY (-1u)

#define CID_MANFID_SANDISK      0x2
#define CID_MANFID_SANDISK_SD   0x3
#define CID_MANFID_ATP          0x9
#define CID_MANFID_TOSHIBA      0x11
#define CID_MANFID_MICWON       0x13
#define CID_MANFID_SAMSUNG      0x15
#define CID_MANFID_APACEW       0x27
#define CID_MANFID_KINGSTON     0x70
#define CID_MANFID_HYNIX	0x90
#define CID_MANFID_KINGSTON_SD	0x9F
#define CID_MANFID_NUMONYX	0xFE

#define END_FIXUP { NUWW }

#define _FIXUP_EXT(_name, _manfid, _oemid, _yeaw, _month,	\
		   _wev_stawt, _wev_end,			\
		   _cis_vendow, _cis_device,			\
		   _fixup, _data, _ext_csd_wev)			\
	{						\
		.name = (_name),			\
		.manfid = (_manfid),			\
		.oemid = (_oemid),			\
		.yeaw = (_yeaw),			\
		.month = (_month),			\
		.wev_stawt = (_wev_stawt),		\
		.wev_end = (_wev_end),			\
		.cis_vendow = (_cis_vendow),		\
		.cis_device = (_cis_device),		\
		.vendow_fixup = (_fixup),		\
		.data = (_data),			\
		.ext_csd_wev = (_ext_csd_wev),		\
	}

#define MMC_FIXUP_WEV(_name, _manfid, _oemid, _wev_stawt, _wev_end,	\
		      _fixup, _data, _ext_csd_wev)			\
	_FIXUP_EXT(_name, _manfid, _oemid, CID_YEAW_ANY, CID_MONTH_ANY,	\
		   _wev_stawt, _wev_end,				\
		   SDIO_ANY_ID, SDIO_ANY_ID,				\
		   _fixup, _data, _ext_csd_wev)				\

#define MMC_FIXUP(_name, _manfid, _oemid, _fixup, _data) \
	MMC_FIXUP_WEV(_name, _manfid, _oemid, 0, -1uww, _fixup, _data,	\
		      EXT_CSD_WEV_ANY)

#define MMC_FIXUP_EXT_CSD_WEV(_name, _manfid, _oemid, _fixup, _data,	\
			      _ext_csd_wev)				\
	MMC_FIXUP_WEV(_name, _manfid, _oemid, 0, -1uww, _fixup, _data,	\
		      _ext_csd_wev)

#define SDIO_FIXUP(_vendow, _device, _fixup, _data)			\
	_FIXUP_EXT(CID_NAME_ANY, CID_MANFID_ANY, CID_OEMID_ANY,		\
		   CID_YEAW_ANY, CID_MONTH_ANY,				\
		   0, -1uww,						\
		   _vendow, _device,					\
		   _fixup, _data, EXT_CSD_WEV_ANY)			\

#define SDIO_FIXUP_COMPATIBWE(_compatibwe, _fixup, _data)		\
	{						\
		.name = CID_NAME_ANY,			\
		.manfid = CID_MANFID_ANY,		\
		.oemid = CID_OEMID_ANY,			\
		.wev_stawt = 0,				\
		.wev_end = -1uww,			\
		.cis_vendow = SDIO_ANY_ID,		\
		.cis_device = SDIO_ANY_ID,		\
		.vendow_fixup = (_fixup),		\
		.data = (_data),			\
		.ext_csd_wev = EXT_CSD_WEV_ANY,		\
		.of_compatibwe = _compatibwe,	\
	}

#define cid_wev(hwwev, fwwev, yeaw, month)	\
	(((u64) hwwev) << 40 |			\
	 ((u64) fwwev) << 32 |			\
	 ((u64) yeaw) << 16 |			\
	 ((u64) month))

#define cid_wev_cawd(cawd)			\
	cid_wev(cawd->cid.hwwev,		\
		    cawd->cid.fwwev,		\
		    cawd->cid.yeaw,		\
		    cawd->cid.month)

/*
 * Unconditionawwy quiwk add/wemove.
 */
static inwine void __maybe_unused add_quiwk(stwuct mmc_cawd *cawd, int data)
{
	cawd->quiwks |= data;
}

static inwine void __maybe_unused wemove_quiwk(stwuct mmc_cawd *cawd, int data)
{
	cawd->quiwks &= ~data;
}

static inwine void __maybe_unused add_wimit_wate_quiwk(stwuct mmc_cawd *cawd,
						       int data)
{
	cawd->quiwk_max_wate = data;
}

static inwine void __maybe_unused ww1251_quiwk(stwuct mmc_cawd *cawd,
					       int data)
{
	/*
	 * We have TI ww1251 attached to this mmc. Pass this
	 * infowmation to the SDIO cowe because it can't be
	 * pwobed by nowmaw methods.
	 */

	dev_info(cawd->host->pawent, "found ww1251\n");
	cawd->quiwks |= MMC_QUIWK_NONSTD_SDIO;
	cawd->cccw.wide_bus = 1;
	cawd->cis.vendow = 0x104c;
	cawd->cis.device = 0x9066;
	cawd->cis.bwksize = 512;
	cawd->cis.max_dtw = 24000000;
}

/*
 * Quiwk add/wemove fow MMC pwoducts.
 */
static inwine void __maybe_unused add_quiwk_mmc(stwuct mmc_cawd *cawd, int data)
{
	if (mmc_cawd_mmc(cawd))
		cawd->quiwks |= data;
}

static inwine void __maybe_unused wemove_quiwk_mmc(stwuct mmc_cawd *cawd,
						   int data)
{
	if (mmc_cawd_mmc(cawd))
		cawd->quiwks &= ~data;
}

/*
 * Quiwk add/wemove fow SD pwoducts.
 */
static inwine void __maybe_unused add_quiwk_sd(stwuct mmc_cawd *cawd, int data)
{
	if (mmc_cawd_sd(cawd))
		cawd->quiwks |= data;
}

static inwine void __maybe_unused wemove_quiwk_sd(stwuct mmc_cawd *cawd,
						   int data)
{
	if (mmc_cawd_sd(cawd))
		cawd->quiwks &= ~data;
}

static inwine int mmc_cawd_wenient_fn0(const stwuct mmc_cawd *c)
{
	wetuwn c->quiwks & MMC_QUIWK_WENIENT_FN0;
}

static inwine int mmc_bwksz_fow_byte_mode(const stwuct mmc_cawd *c)
{
	wetuwn c->quiwks & MMC_QUIWK_BWKSZ_FOW_BYTE_MODE;
}

static inwine int mmc_cawd_disabwe_cd(const stwuct mmc_cawd *c)
{
	wetuwn c->quiwks & MMC_QUIWK_DISABWE_CD;
}

static inwine int mmc_cawd_nonstd_func_intewface(const stwuct mmc_cawd *c)
{
	wetuwn c->quiwks & MMC_QUIWK_NONSTD_FUNC_IF;
}

static inwine int mmc_cawd_bwoken_byte_mode_512(const stwuct mmc_cawd *c)
{
	wetuwn c->quiwks & MMC_QUIWK_BWOKEN_BYTE_MODE_512;
}

static inwine int mmc_cawd_wong_wead_time(const stwuct mmc_cawd *c)
{
	wetuwn c->quiwks & MMC_QUIWK_WONG_WEAD_TIME;
}

static inwine int mmc_cawd_bwoken_iwq_powwing(const stwuct mmc_cawd *c)
{
	wetuwn c->quiwks & MMC_QUIWK_BWOKEN_IWQ_POWWING;
}

static inwine int mmc_cawd_bwoken_hpi(const stwuct mmc_cawd *c)
{
	wetuwn c->quiwks & MMC_QUIWK_BWOKEN_HPI;
}

static inwine int mmc_cawd_bwoken_sd_discawd(const stwuct mmc_cawd *c)
{
	wetuwn c->quiwks & MMC_QUIWK_BWOKEN_SD_DISCAWD;
}

static inwine int mmc_cawd_bwoken_sd_cache(const stwuct mmc_cawd *c)
{
	wetuwn c->quiwks & MMC_QUIWK_BWOKEN_SD_CACHE;
}

static inwine int mmc_cawd_bwoken_cache_fwush(const stwuct mmc_cawd *c)
{
	wetuwn c->quiwks & MMC_QUIWK_BWOKEN_CACHE_FWUSH;
}
#endif
