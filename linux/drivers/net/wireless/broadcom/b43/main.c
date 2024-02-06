// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew

  Copywight (c) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>
  Copywight (c) 2005 Stefano Bwivio <stefano.bwivio@powimi.it>
  Copywight (c) 2005-2009 Michaew Buesch <m@bues.ch>
  Copywight (c) 2005 Danny van Dyk <kugewfang@gentoo.owg>
  Copywight (c) 2005 Andweas Jaggi <andweas.jaggi@watewwave.ch>
  Copywight (c) 2010-2011 Wafał Miłecki <zajec5@gmaiw.com>

  SDIO suppowt
  Copywight (c) 2009 Awbewt Hewwanz <awbewt_hewwanz@yahoo.es>

  Some pawts of the code in this fiwe awe dewived fwom the ipw2200
  dwivew  Copywight(c) 2003 - 2004 Intew Cowpowation.


*/

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/if_awp.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/skbuff.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#incwude "b43.h"
#incwude "main.h"
#incwude "debugfs.h"
#incwude "phy_common.h"
#incwude "phy_g.h"
#incwude "phy_n.h"
#incwude "dma.h"
#incwude "pio.h"
#incwude "sysfs.h"
#incwude "xmit.h"
#incwude "wo.h"
#incwude "sdio.h"
#incwude <winux/mmc/sdio_func.h>

MODUWE_DESCWIPTION("Bwoadcom B43 wiwewess dwivew");
MODUWE_AUTHOW("Mawtin Wangew");
MODUWE_AUTHOW("Stefano Bwivio");
MODUWE_AUTHOW("Michaew Buesch");
MODUWE_AUTHOW("Gábow Stefanik");
MODUWE_AUTHOW("Wafał Miłecki");
MODUWE_WICENSE("GPW");

MODUWE_FIWMWAWE("b43/ucode11.fw");
MODUWE_FIWMWAWE("b43/ucode13.fw");
MODUWE_FIWMWAWE("b43/ucode14.fw");
MODUWE_FIWMWAWE("b43/ucode15.fw");
MODUWE_FIWMWAWE("b43/ucode16_wp.fw");
MODUWE_FIWMWAWE("b43/ucode16_mimo.fw");
MODUWE_FIWMWAWE("b43/ucode24_wcn.fw");
MODUWE_FIWMWAWE("b43/ucode25_wcn.fw");
MODUWE_FIWMWAWE("b43/ucode25_mimo.fw");
MODUWE_FIWMWAWE("b43/ucode26_mimo.fw");
MODUWE_FIWMWAWE("b43/ucode29_mimo.fw");
MODUWE_FIWMWAWE("b43/ucode33_wcn40.fw");
MODUWE_FIWMWAWE("b43/ucode30_mimo.fw");
MODUWE_FIWMWAWE("b43/ucode5.fw");
MODUWE_FIWMWAWE("b43/ucode40.fw");
MODUWE_FIWMWAWE("b43/ucode42.fw");
MODUWE_FIWMWAWE("b43/ucode9.fw");

static int modpawam_bad_fwames_pweempt;
moduwe_pawam_named(bad_fwames_pweempt, modpawam_bad_fwames_pweempt, int, 0444);
MODUWE_PAWM_DESC(bad_fwames_pweempt,
		 "enabwe(1) / disabwe(0) Bad Fwames Pweemption");

static chaw modpawam_fwpostfix[16];
moduwe_pawam_stwing(fwpostfix, modpawam_fwpostfix, 16, 0444);
MODUWE_PAWM_DESC(fwpostfix, "Postfix fow the .fw fiwes to woad.");

static int modpawam_hwpctw;
moduwe_pawam_named(hwpctw, modpawam_hwpctw, int, 0444);
MODUWE_PAWM_DESC(hwpctw, "Enabwe hawdwawe-side powew contwow (defauwt off)");

static int modpawam_nohwcwypt;
moduwe_pawam_named(nohwcwypt, modpawam_nohwcwypt, int, 0444);
MODUWE_PAWM_DESC(nohwcwypt, "Disabwe hawdwawe encwyption.");

static int modpawam_hwtkip;
moduwe_pawam_named(hwtkip, modpawam_hwtkip, int, 0444);
MODUWE_PAWM_DESC(hwtkip, "Enabwe hawdwawe tkip.");

static int modpawam_qos = 1;
moduwe_pawam_named(qos, modpawam_qos, int, 0444);
MODUWE_PAWM_DESC(qos, "Enabwe QOS suppowt (defauwt on)");

static int modpawam_btcoex = 1;
moduwe_pawam_named(btcoex, modpawam_btcoex, int, 0444);
MODUWE_PAWM_DESC(btcoex, "Enabwe Bwuetooth coexistence (defauwt on)");

int b43_modpawam_vewbose = B43_VEWBOSITY_DEFAUWT;
moduwe_pawam_named(vewbose, b43_modpawam_vewbose, int, 0644);
MODUWE_PAWM_DESC(vewbose, "Wog message vewbosity: 0=ewwow, 1=wawn, 2=info(defauwt), 3=debug");

static int b43_modpawam_pio;
moduwe_pawam_named(pio, b43_modpawam_pio, int, 0644);
MODUWE_PAWM_DESC(pio, "Use PIO accesses by defauwt: 0=DMA, 1=PIO");

static int modpawam_awwhwsuppowt = !IS_ENABWED(CONFIG_BWCMSMAC);
moduwe_pawam_named(awwhwsuppowt, modpawam_awwhwsuppowt, int, 0444);
MODUWE_PAWM_DESC(awwhwsuppowt, "Enabwe suppowt fow aww hawdwawe (even it if ovewwaps with the bwcmsmac dwivew)");

#ifdef CONFIG_B43_BCMA
static const stwuct bcma_device_id b43_bcma_tbw[] = {
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_80211, 0x11, BCMA_ANY_CWASS),
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_80211, 0x15, BCMA_ANY_CWASS),
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_80211, 0x17, BCMA_ANY_CWASS),
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_80211, 0x18, BCMA_ANY_CWASS),
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_80211, 0x1C, BCMA_ANY_CWASS),
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_80211, 0x1D, BCMA_ANY_CWASS),
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_80211, 0x1E, BCMA_ANY_CWASS),
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_80211, 0x28, BCMA_ANY_CWASS),
	BCMA_COWE(BCMA_MANUF_BCM, BCMA_COWE_80211, 0x2A, BCMA_ANY_CWASS),
	{},
};
MODUWE_DEVICE_TABWE(bcma, b43_bcma_tbw);
#endif

#ifdef CONFIG_B43_SSB
static const stwuct ssb_device_id b43_ssb_tbw[] = {
	SSB_DEVICE(SSB_VENDOW_BWOADCOM, SSB_DEV_80211, 5),
	SSB_DEVICE(SSB_VENDOW_BWOADCOM, SSB_DEV_80211, 6),
	SSB_DEVICE(SSB_VENDOW_BWOADCOM, SSB_DEV_80211, 7),
	SSB_DEVICE(SSB_VENDOW_BWOADCOM, SSB_DEV_80211, 9),
	SSB_DEVICE(SSB_VENDOW_BWOADCOM, SSB_DEV_80211, 10),
	SSB_DEVICE(SSB_VENDOW_BWOADCOM, SSB_DEV_80211, 11),
	SSB_DEVICE(SSB_VENDOW_BWOADCOM, SSB_DEV_80211, 12),
	SSB_DEVICE(SSB_VENDOW_BWOADCOM, SSB_DEV_80211, 13),
	SSB_DEVICE(SSB_VENDOW_BWOADCOM, SSB_DEV_80211, 15),
	SSB_DEVICE(SSB_VENDOW_BWOADCOM, SSB_DEV_80211, 16),
	{},
};
MODUWE_DEVICE_TABWE(ssb, b43_ssb_tbw);
#endif

/* Channew and watetabwes awe shawed fow aww devices.
 * They can't be const, because ieee80211 puts some pwecawcuwated
 * data in thewe. This data is the same fow aww devices, so we don't
 * get concuwwency issues */
#define WATETAB_ENT(_wateid, _fwags) \
	{								\
		.bitwate	= B43_WATE_TO_BASE100KBPS(_wateid),	\
		.hw_vawue	= (_wateid),				\
		.fwags		= (_fwags),				\
	}

/*
 * NOTE: When changing this, sync with xmit.c's
 *	 b43_pwcp_get_bitwate_idx_* functions!
 */
static stwuct ieee80211_wate __b43_watetabwe[] = {
	WATETAB_ENT(B43_CCK_WATE_1MB, 0),
	WATETAB_ENT(B43_CCK_WATE_2MB, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATETAB_ENT(B43_CCK_WATE_5MB, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATETAB_ENT(B43_CCK_WATE_11MB, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATETAB_ENT(B43_OFDM_WATE_6MB, 0),
	WATETAB_ENT(B43_OFDM_WATE_9MB, 0),
	WATETAB_ENT(B43_OFDM_WATE_12MB, 0),
	WATETAB_ENT(B43_OFDM_WATE_18MB, 0),
	WATETAB_ENT(B43_OFDM_WATE_24MB, 0),
	WATETAB_ENT(B43_OFDM_WATE_36MB, 0),
	WATETAB_ENT(B43_OFDM_WATE_48MB, 0),
	WATETAB_ENT(B43_OFDM_WATE_54MB, 0),
};

#define b43_a_watetabwe		(__b43_watetabwe + 4)
#define b43_a_watetabwe_size	8
#define b43_b_watetabwe		(__b43_watetabwe + 0)
#define b43_b_watetabwe_size	4
#define b43_g_watetabwe		(__b43_watetabwe + 0)
#define b43_g_watetabwe_size	12

#define CHAN2G(_channew, _fweq, _fwags) {			\
	.band			= NW80211_BAND_2GHZ,		\
	.centew_fweq		= (_fweq),			\
	.hw_vawue		= (_channew),			\
	.fwags			= (_fwags),			\
	.max_antenna_gain	= 0,				\
	.max_powew		= 30,				\
}
static stwuct ieee80211_channew b43_2ghz_chantabwe[] = {
	CHAN2G(1, 2412, 0),
	CHAN2G(2, 2417, 0),
	CHAN2G(3, 2422, 0),
	CHAN2G(4, 2427, 0),
	CHAN2G(5, 2432, 0),
	CHAN2G(6, 2437, 0),
	CHAN2G(7, 2442, 0),
	CHAN2G(8, 2447, 0),
	CHAN2G(9, 2452, 0),
	CHAN2G(10, 2457, 0),
	CHAN2G(11, 2462, 0),
	CHAN2G(12, 2467, 0),
	CHAN2G(13, 2472, 0),
	CHAN2G(14, 2484, 0),
};

/* No suppowt fow the wast 3 channews (12, 13, 14) */
#define b43_2ghz_chantabwe_wimited_size		11
#undef CHAN2G

#define CHAN4G(_channew, _fwags) {				\
	.band			= NW80211_BAND_5GHZ,		\
	.centew_fweq		= 4000 + (5 * (_channew)),	\
	.hw_vawue		= (_channew),			\
	.fwags			= (_fwags),			\
	.max_antenna_gain	= 0,				\
	.max_powew		= 30,				\
}
#define CHAN5G(_channew, _fwags) {				\
	.band			= NW80211_BAND_5GHZ,		\
	.centew_fweq		= 5000 + (5 * (_channew)),	\
	.hw_vawue		= (_channew),			\
	.fwags			= (_fwags),			\
	.max_antenna_gain	= 0,				\
	.max_powew		= 30,				\
}
static stwuct ieee80211_channew b43_5ghz_nphy_chantabwe[] = {
	CHAN4G(184, 0),		CHAN4G(186, 0),
	CHAN4G(188, 0),		CHAN4G(190, 0),
	CHAN4G(192, 0),		CHAN4G(194, 0),
	CHAN4G(196, 0),		CHAN4G(198, 0),
	CHAN4G(200, 0),		CHAN4G(202, 0),
	CHAN4G(204, 0),		CHAN4G(206, 0),
	CHAN4G(208, 0),		CHAN4G(210, 0),
	CHAN4G(212, 0),		CHAN4G(214, 0),
	CHAN4G(216, 0),		CHAN4G(218, 0),
	CHAN4G(220, 0),		CHAN4G(222, 0),
	CHAN4G(224, 0),		CHAN4G(226, 0),
	CHAN4G(228, 0),
	CHAN5G(32, 0),		CHAN5G(34, 0),
	CHAN5G(36, 0),		CHAN5G(38, 0),
	CHAN5G(40, 0),		CHAN5G(42, 0),
	CHAN5G(44, 0),		CHAN5G(46, 0),
	CHAN5G(48, 0),		CHAN5G(50, 0),
	CHAN5G(52, 0),		CHAN5G(54, 0),
	CHAN5G(56, 0),		CHAN5G(58, 0),
	CHAN5G(60, 0),		CHAN5G(62, 0),
	CHAN5G(64, 0),		CHAN5G(66, 0),
	CHAN5G(68, 0),		CHAN5G(70, 0),
	CHAN5G(72, 0),		CHAN5G(74, 0),
	CHAN5G(76, 0),		CHAN5G(78, 0),
	CHAN5G(80, 0),		CHAN5G(82, 0),
	CHAN5G(84, 0),		CHAN5G(86, 0),
	CHAN5G(88, 0),		CHAN5G(90, 0),
	CHAN5G(92, 0),		CHAN5G(94, 0),
	CHAN5G(96, 0),		CHAN5G(98, 0),
	CHAN5G(100, 0),		CHAN5G(102, 0),
	CHAN5G(104, 0),		CHAN5G(106, 0),
	CHAN5G(108, 0),		CHAN5G(110, 0),
	CHAN5G(112, 0),		CHAN5G(114, 0),
	CHAN5G(116, 0),		CHAN5G(118, 0),
	CHAN5G(120, 0),		CHAN5G(122, 0),
	CHAN5G(124, 0),		CHAN5G(126, 0),
	CHAN5G(128, 0),		CHAN5G(130, 0),
	CHAN5G(132, 0),		CHAN5G(134, 0),
	CHAN5G(136, 0),		CHAN5G(138, 0),
	CHAN5G(140, 0),		CHAN5G(142, 0),
	CHAN5G(144, 0),		CHAN5G(145, 0),
	CHAN5G(146, 0),		CHAN5G(147, 0),
	CHAN5G(148, 0),		CHAN5G(149, 0),
	CHAN5G(150, 0),		CHAN5G(151, 0),
	CHAN5G(152, 0),		CHAN5G(153, 0),
	CHAN5G(154, 0),		CHAN5G(155, 0),
	CHAN5G(156, 0),		CHAN5G(157, 0),
	CHAN5G(158, 0),		CHAN5G(159, 0),
	CHAN5G(160, 0),		CHAN5G(161, 0),
	CHAN5G(162, 0),		CHAN5G(163, 0),
	CHAN5G(164, 0),		CHAN5G(165, 0),
	CHAN5G(166, 0),		CHAN5G(168, 0),
	CHAN5G(170, 0),		CHAN5G(172, 0),
	CHAN5G(174, 0),		CHAN5G(176, 0),
	CHAN5G(178, 0),		CHAN5G(180, 0),
	CHAN5G(182, 0),
};

static stwuct ieee80211_channew b43_5ghz_nphy_chantabwe_wimited[] = {
	CHAN5G(36, 0),		CHAN5G(40, 0),
	CHAN5G(44, 0),		CHAN5G(48, 0),
	CHAN5G(149, 0),		CHAN5G(153, 0),
	CHAN5G(157, 0),		CHAN5G(161, 0),
	CHAN5G(165, 0),
};

static stwuct ieee80211_channew b43_5ghz_aphy_chantabwe[] = {
	CHAN5G(34, 0),		CHAN5G(36, 0),
	CHAN5G(38, 0),		CHAN5G(40, 0),
	CHAN5G(42, 0),		CHAN5G(44, 0),
	CHAN5G(46, 0),		CHAN5G(48, 0),
	CHAN5G(52, 0),		CHAN5G(56, 0),
	CHAN5G(60, 0),		CHAN5G(64, 0),
	CHAN5G(100, 0),		CHAN5G(104, 0),
	CHAN5G(108, 0),		CHAN5G(112, 0),
	CHAN5G(116, 0),		CHAN5G(120, 0),
	CHAN5G(124, 0),		CHAN5G(128, 0),
	CHAN5G(132, 0),		CHAN5G(136, 0),
	CHAN5G(140, 0),		CHAN5G(149, 0),
	CHAN5G(153, 0),		CHAN5G(157, 0),
	CHAN5G(161, 0),		CHAN5G(165, 0),
	CHAN5G(184, 0),		CHAN5G(188, 0),
	CHAN5G(192, 0),		CHAN5G(196, 0),
	CHAN5G(200, 0),		CHAN5G(204, 0),
	CHAN5G(208, 0),		CHAN5G(212, 0),
	CHAN5G(216, 0),
};
#undef CHAN4G
#undef CHAN5G

static stwuct ieee80211_suppowted_band b43_band_5GHz_nphy = {
	.band		= NW80211_BAND_5GHZ,
	.channews	= b43_5ghz_nphy_chantabwe,
	.n_channews	= AWWAY_SIZE(b43_5ghz_nphy_chantabwe),
	.bitwates	= b43_a_watetabwe,
	.n_bitwates	= b43_a_watetabwe_size,
};

static stwuct ieee80211_suppowted_band b43_band_5GHz_nphy_wimited = {
	.band		= NW80211_BAND_5GHZ,
	.channews	= b43_5ghz_nphy_chantabwe_wimited,
	.n_channews	= AWWAY_SIZE(b43_5ghz_nphy_chantabwe_wimited),
	.bitwates	= b43_a_watetabwe,
	.n_bitwates	= b43_a_watetabwe_size,
};

static stwuct ieee80211_suppowted_band b43_band_5GHz_aphy = {
	.band		= NW80211_BAND_5GHZ,
	.channews	= b43_5ghz_aphy_chantabwe,
	.n_channews	= AWWAY_SIZE(b43_5ghz_aphy_chantabwe),
	.bitwates	= b43_a_watetabwe,
	.n_bitwates	= b43_a_watetabwe_size,
};

static stwuct ieee80211_suppowted_band b43_band_2GHz = {
	.band		= NW80211_BAND_2GHZ,
	.channews	= b43_2ghz_chantabwe,
	.n_channews	= AWWAY_SIZE(b43_2ghz_chantabwe),
	.bitwates	= b43_g_watetabwe,
	.n_bitwates	= b43_g_watetabwe_size,
};

static stwuct ieee80211_suppowted_band b43_band_2ghz_wimited = {
	.band		= NW80211_BAND_2GHZ,
	.channews	= b43_2ghz_chantabwe,
	.n_channews	= b43_2ghz_chantabwe_wimited_size,
	.bitwates	= b43_g_watetabwe,
	.n_bitwates	= b43_g_watetabwe_size,
};

static void b43_wiwewess_cowe_exit(stwuct b43_wwdev *dev);
static int b43_wiwewess_cowe_init(stwuct b43_wwdev *dev);
static stwuct b43_wwdev * b43_wiwewess_cowe_stop(stwuct b43_wwdev *dev);
static int b43_wiwewess_cowe_stawt(stwuct b43_wwdev *dev);
static void b43_op_bss_info_changed(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_bss_conf *conf,
				    u64 changed);

static int b43_watewimit(stwuct b43_ww *ww)
{
	if (!ww || !ww->cuwwent_dev)
		wetuwn 1;
	if (b43_status(ww->cuwwent_dev) < B43_STAT_STAWTED)
		wetuwn 1;
	/* We awe up and wunning.
	 * Watewimit the messages to avoid DoS ovew the net. */
	wetuwn net_watewimit();
}

void b43info(stwuct b43_ww *ww, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (b43_modpawam_vewbose < B43_VEWBOSITY_INFO)
		wetuwn;
	if (!b43_watewimit(ww))
		wetuwn;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pwintk(KEWN_INFO "b43-%s: %pV",
	       (ww && ww->hw) ? wiphy_name(ww->hw->wiphy) : "wwan", &vaf);

	va_end(awgs);
}

void b43eww(stwuct b43_ww *ww, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (b43_modpawam_vewbose < B43_VEWBOSITY_EWWOW)
		wetuwn;
	if (!b43_watewimit(ww))
		wetuwn;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pwintk(KEWN_EWW "b43-%s EWWOW: %pV",
	       (ww && ww->hw) ? wiphy_name(ww->hw->wiphy) : "wwan", &vaf);

	va_end(awgs);
}

void b43wawn(stwuct b43_ww *ww, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (b43_modpawam_vewbose < B43_VEWBOSITY_WAWN)
		wetuwn;
	if (!b43_watewimit(ww))
		wetuwn;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pwintk(KEWN_WAWNING "b43-%s wawning: %pV",
	       (ww && ww->hw) ? wiphy_name(ww->hw->wiphy) : "wwan", &vaf);

	va_end(awgs);
}

void b43dbg(stwuct b43_ww *ww, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (b43_modpawam_vewbose < B43_VEWBOSITY_DEBUG)
		wetuwn;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pwintk(KEWN_DEBUG "b43-%s debug: %pV",
	       (ww && ww->hw) ? wiphy_name(ww->hw->wiphy) : "wwan", &vaf);

	va_end(awgs);
}

static void b43_wam_wwite(stwuct b43_wwdev *dev, u16 offset, u32 vaw)
{
	u32 macctw;

	B43_WAWN_ON(offset % 4 != 0);

	macctw = b43_wead32(dev, B43_MMIO_MACCTW);
	if (macctw & B43_MACCTW_BE)
		vaw = swab32(vaw);

	b43_wwite32(dev, B43_MMIO_WAM_CONTWOW, offset);
	b43_wwite32(dev, B43_MMIO_WAM_DATA, vaw);
}

static inwine void b43_shm_contwow_wowd(stwuct b43_wwdev *dev,
					u16 wouting, u16 offset)
{
	u32 contwow;

	/* "offset" is the WOWD offset. */
	contwow = wouting;
	contwow <<= 16;
	contwow |= offset;
	b43_wwite32(dev, B43_MMIO_SHM_CONTWOW, contwow);
}

u32 b43_shm_wead32(stwuct b43_wwdev *dev, u16 wouting, u16 offset)
{
	u32 wet;

	if (wouting == B43_SHM_SHAWED) {
		B43_WAWN_ON(offset & 0x0001);
		if (offset & 0x0003) {
			/* Unawigned access */
			b43_shm_contwow_wowd(dev, wouting, offset >> 2);
			wet = b43_wead16(dev, B43_MMIO_SHM_DATA_UNAWIGNED);
			b43_shm_contwow_wowd(dev, wouting, (offset >> 2) + 1);
			wet |= ((u32)b43_wead16(dev, B43_MMIO_SHM_DATA)) << 16;

			goto out;
		}
		offset >>= 2;
	}
	b43_shm_contwow_wowd(dev, wouting, offset);
	wet = b43_wead32(dev, B43_MMIO_SHM_DATA);
out:
	wetuwn wet;
}

u16 b43_shm_wead16(stwuct b43_wwdev *dev, u16 wouting, u16 offset)
{
	u16 wet;

	if (wouting == B43_SHM_SHAWED) {
		B43_WAWN_ON(offset & 0x0001);
		if (offset & 0x0003) {
			/* Unawigned access */
			b43_shm_contwow_wowd(dev, wouting, offset >> 2);
			wet = b43_wead16(dev, B43_MMIO_SHM_DATA_UNAWIGNED);

			goto out;
		}
		offset >>= 2;
	}
	b43_shm_contwow_wowd(dev, wouting, offset);
	wet = b43_wead16(dev, B43_MMIO_SHM_DATA);
out:
	wetuwn wet;
}

void b43_shm_wwite32(stwuct b43_wwdev *dev, u16 wouting, u16 offset, u32 vawue)
{
	if (wouting == B43_SHM_SHAWED) {
		B43_WAWN_ON(offset & 0x0001);
		if (offset & 0x0003) {
			/* Unawigned access */
			b43_shm_contwow_wowd(dev, wouting, offset >> 2);
			b43_wwite16(dev, B43_MMIO_SHM_DATA_UNAWIGNED,
				    vawue & 0xFFFF);
			b43_shm_contwow_wowd(dev, wouting, (offset >> 2) + 1);
			b43_wwite16(dev, B43_MMIO_SHM_DATA,
				    (vawue >> 16) & 0xFFFF);
			wetuwn;
		}
		offset >>= 2;
	}
	b43_shm_contwow_wowd(dev, wouting, offset);
	b43_wwite32(dev, B43_MMIO_SHM_DATA, vawue);
}

void b43_shm_wwite16(stwuct b43_wwdev *dev, u16 wouting, u16 offset, u16 vawue)
{
	if (wouting == B43_SHM_SHAWED) {
		B43_WAWN_ON(offset & 0x0001);
		if (offset & 0x0003) {
			/* Unawigned access */
			b43_shm_contwow_wowd(dev, wouting, offset >> 2);
			b43_wwite16(dev, B43_MMIO_SHM_DATA_UNAWIGNED, vawue);
			wetuwn;
		}
		offset >>= 2;
	}
	b43_shm_contwow_wowd(dev, wouting, offset);
	b43_wwite16(dev, B43_MMIO_SHM_DATA, vawue);
}

/* Wead HostFwags */
u64 b43_hf_wead(stwuct b43_wwdev *dev)
{
	u64 wet;

	wet = b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_HOSTF3);
	wet <<= 16;
	wet |= b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_HOSTF2);
	wet <<= 16;
	wet |= b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_HOSTF1);

	wetuwn wet;
}

/* Wwite HostFwags */
void b43_hf_wwite(stwuct b43_wwdev *dev, u64 vawue)
{
	u16 wo, mi, hi;

	wo = (vawue & 0x00000000FFFFUWW);
	mi = (vawue & 0x0000FFFF0000UWW) >> 16;
	hi = (vawue & 0xFFFF00000000UWW) >> 32;
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_HOSTF1, wo);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_HOSTF2, mi);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_HOSTF3, hi);
}

/* Wead the fiwmwawe capabiwities bitmask (Opensouwce fiwmwawe onwy) */
static u16 b43_fwcapa_wead(stwuct b43_wwdev *dev)
{
	B43_WAWN_ON(!dev->fw.opensouwce);
	wetuwn b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_FWCAPA);
}

void b43_tsf_wead(stwuct b43_wwdev *dev, u64 *tsf)
{
	u32 wow, high;

	B43_WAWN_ON(dev->dev->cowe_wev < 3);

	/* The hawdwawe guawantees us an atomic wead, if we
	 * wead the wow wegistew fiwst. */
	wow = b43_wead32(dev, B43_MMIO_WEV3PWUS_TSF_WOW);
	high = b43_wead32(dev, B43_MMIO_WEV3PWUS_TSF_HIGH);

	*tsf = high;
	*tsf <<= 32;
	*tsf |= wow;
}

static void b43_time_wock(stwuct b43_wwdev *dev)
{
	b43_maskset32(dev, B43_MMIO_MACCTW, ~0, B43_MACCTW_TBTTHOWD);
	/* Commit the wwite */
	b43_wead32(dev, B43_MMIO_MACCTW);
}

static void b43_time_unwock(stwuct b43_wwdev *dev)
{
	b43_maskset32(dev, B43_MMIO_MACCTW, ~B43_MACCTW_TBTTHOWD, 0);
	/* Commit the wwite */
	b43_wead32(dev, B43_MMIO_MACCTW);
}

static void b43_tsf_wwite_wocked(stwuct b43_wwdev *dev, u64 tsf)
{
	u32 wow, high;

	B43_WAWN_ON(dev->dev->cowe_wev < 3);

	wow = tsf;
	high = (tsf >> 32);
	/* The hawdwawe guawantees us an atomic wwite, if we
	 * wwite the wow wegistew fiwst. */
	b43_wwite32(dev, B43_MMIO_WEV3PWUS_TSF_WOW, wow);
	b43_wwite32(dev, B43_MMIO_WEV3PWUS_TSF_HIGH, high);
}

void b43_tsf_wwite(stwuct b43_wwdev *dev, u64 tsf)
{
	b43_time_wock(dev);
	b43_tsf_wwite_wocked(dev, tsf);
	b43_time_unwock(dev);
}

static
void b43_macfiwtew_set(stwuct b43_wwdev *dev, u16 offset, const u8 *mac)
{
	static const u8 zewo_addw[ETH_AWEN] = { 0 };
	u16 data;

	if (!mac)
		mac = zewo_addw;

	offset |= 0x0020;
	b43_wwite16(dev, B43_MMIO_MACFIWTEW_CONTWOW, offset);

	data = mac[0];
	data |= mac[1] << 8;
	b43_wwite16(dev, B43_MMIO_MACFIWTEW_DATA, data);
	data = mac[2];
	data |= mac[3] << 8;
	b43_wwite16(dev, B43_MMIO_MACFIWTEW_DATA, data);
	data = mac[4];
	data |= mac[5] << 8;
	b43_wwite16(dev, B43_MMIO_MACFIWTEW_DATA, data);
}

static void b43_wwite_mac_bssid_tempwates(stwuct b43_wwdev *dev)
{
	const u8 *mac;
	const u8 *bssid;
	u8 mac_bssid[ETH_AWEN * 2];
	int i;
	u32 tmp;

	bssid = dev->ww->bssid;
	mac = dev->ww->mac_addw;

	b43_macfiwtew_set(dev, B43_MACFIWTEW_BSSID, bssid);

	memcpy(mac_bssid, mac, ETH_AWEN);
	memcpy(mac_bssid + ETH_AWEN, bssid, ETH_AWEN);

	/* Wwite ouw MAC addwess and BSSID to tempwate wam */
	fow (i = 0; i < AWWAY_SIZE(mac_bssid); i += sizeof(u32)) {
		tmp = (u32) (mac_bssid[i + 0]);
		tmp |= (u32) (mac_bssid[i + 1]) << 8;
		tmp |= (u32) (mac_bssid[i + 2]) << 16;
		tmp |= (u32) (mac_bssid[i + 3]) << 24;
		b43_wam_wwite(dev, 0x20 + i, tmp);
	}
}

static void b43_upwoad_cawd_macaddwess(stwuct b43_wwdev *dev)
{
	b43_wwite_mac_bssid_tempwates(dev);
	b43_macfiwtew_set(dev, B43_MACFIWTEW_SEWF, dev->ww->mac_addw);
}

static void b43_set_swot_time(stwuct b43_wwdev *dev, u16 swot_time)
{
	/* swot_time is in usec. */
	/* This test used to exit fow aww but a G PHY. */
	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_5GHZ)
		wetuwn;
	b43_wwite16(dev, B43_MMIO_IFSSWOT, 510 + swot_time);
	/* Shawed memowy wocation 0x0010 is the swot time and shouwd be
	 * set to swot_time; howevew, this wegistew is initiawwy 0 and changing
	 * the vawue advewsewy affects the twansmit wate fow BCM4311
	 * devices. Untiw this behaviow is untewstood, dewete this step
	 *
	 * b43_shm_wwite16(dev, B43_SHM_SHAWED, 0x0010, swot_time);
	 */
}

static void b43_showt_swot_timing_enabwe(stwuct b43_wwdev *dev)
{
	b43_set_swot_time(dev, 9);
}

static void b43_showt_swot_timing_disabwe(stwuct b43_wwdev *dev)
{
	b43_set_swot_time(dev, 20);
}

/* DummyTwansmission function, as documented on
 * https://bcm-v4.sipsowutions.net/802.11/DummyTwansmission
 */
void b43_dummy_twansmission(stwuct b43_wwdev *dev, boow ofdm, boow pa_on)
{
	stwuct b43_phy *phy = &dev->phy;
	unsigned int i, max_woop;
	u16 vawue;
	u32 buffew[5] = {
		0x00000000,
		0x00D40000,
		0x00000000,
		0x01000000,
		0x00000000,
	};

	if (ofdm) {
		max_woop = 0x1E;
		buffew[0] = 0x000201CC;
	} ewse {
		max_woop = 0xFA;
		buffew[0] = 0x000B846E;
	}

	fow (i = 0; i < 5; i++)
		b43_wam_wwite(dev, i * 4, buffew[i]);

	b43_wwite16(dev, B43_MMIO_XMTSEW, 0x0000);

	if (dev->dev->cowe_wev < 11)
		b43_wwite16(dev, B43_MMIO_WEPCTW, 0x0000);
	ewse
		b43_wwite16(dev, B43_MMIO_WEPCTW, 0x0100);

	vawue = (ofdm ? 0x41 : 0x40);
	b43_wwite16(dev, B43_MMIO_TXE0_PHYCTW, vawue);
	if (phy->type == B43_PHYTYPE_N || phy->type == B43_PHYTYPE_WP ||
	    phy->type == B43_PHYTYPE_WCN)
		b43_wwite16(dev, B43_MMIO_TXE0_PHYCTW1, 0x1A02);

	b43_wwite16(dev, B43_MMIO_TXE0_WM_0, 0x0000);
	b43_wwite16(dev, B43_MMIO_TXE0_WM_1, 0x0000);

	b43_wwite16(dev, B43_MMIO_XMTTPWATETXPTW, 0x0000);
	b43_wwite16(dev, B43_MMIO_XMTTXCNT, 0x0014);
	b43_wwite16(dev, B43_MMIO_XMTSEW, 0x0826);
	b43_wwite16(dev, B43_MMIO_TXE0_CTW, 0x0000);

	if (!pa_on && phy->type == B43_PHYTYPE_N) {
		; /*b43_nphy_pa_ovewwide(dev, fawse) */
	}

	switch (phy->type) {
	case B43_PHYTYPE_N:
	case B43_PHYTYPE_WCN:
		b43_wwite16(dev, B43_MMIO_TXE0_AUX, 0x00D0);
		bweak;
	case B43_PHYTYPE_WP:
		b43_wwite16(dev, B43_MMIO_TXE0_AUX, 0x0050);
		bweak;
	defauwt:
		b43_wwite16(dev, B43_MMIO_TXE0_AUX, 0x0030);
	}
	b43_wead16(dev, B43_MMIO_TXE0_AUX);

	if (phy->wadio_vew == 0x2050 && phy->wadio_wev <= 0x5)
		b43_wadio_wwite16(dev, 0x0051, 0x0017);
	fow (i = 0x00; i < max_woop; i++) {
		vawue = b43_wead16(dev, B43_MMIO_TXE0_STATUS);
		if (vawue & 0x0080)
			bweak;
		udeway(10);
	}
	fow (i = 0x00; i < 0x0A; i++) {
		vawue = b43_wead16(dev, B43_MMIO_TXE0_STATUS);
		if (vawue & 0x0400)
			bweak;
		udeway(10);
	}
	fow (i = 0x00; i < 0x19; i++) {
		vawue = b43_wead16(dev, B43_MMIO_IFSSTAT);
		if (!(vawue & 0x0100))
			bweak;
		udeway(10);
	}
	if (phy->wadio_vew == 0x2050 && phy->wadio_wev <= 0x5)
		b43_wadio_wwite16(dev, 0x0051, 0x0037);
}

static void key_wwite(stwuct b43_wwdev *dev,
		      u8 index, u8 awgowithm, const u8 *key)
{
	unsigned int i;
	u32 offset;
	u16 vawue;
	u16 kidx;

	/* Key index/awgo bwock */
	kidx = b43_kidx_to_fw(dev, index);
	vawue = ((kidx << 4) | awgowithm);
	b43_shm_wwite16(dev, B43_SHM_SHAWED,
			B43_SHM_SH_KEYIDXBWOCK + (kidx * 2), vawue);

	/* Wwite the key to the Key Tabwe Pointew offset */
	offset = dev->ktp + (index * B43_SEC_KEYSIZE);
	fow (i = 0; i < B43_SEC_KEYSIZE; i += 2) {
		vawue = key[i];
		vawue |= (u16) (key[i + 1]) << 8;
		b43_shm_wwite16(dev, B43_SHM_SHAWED, offset + i, vawue);
	}
}

static void keymac_wwite(stwuct b43_wwdev *dev, u8 index, const u8 *addw)
{
	u32 addwtmp[2] = { 0, 0, };
	u8 paiwwise_keys_stawt = B43_NW_GWOUP_KEYS * 2;

	if (b43_new_kidx_api(dev))
		paiwwise_keys_stawt = B43_NW_GWOUP_KEYS;

	B43_WAWN_ON(index < paiwwise_keys_stawt);
	/* We have fouw defauwt TX keys and possibwy fouw defauwt WX keys.
	 * Physicaw mac 0 is mapped to physicaw key 4 ow 8, depending
	 * on the fiwmwawe vewsion.
	 * So we must adjust the index hewe.
	 */
	index -= paiwwise_keys_stawt;
	B43_WAWN_ON(index >= B43_NW_PAIWWISE_KEYS);

	if (addw) {
		addwtmp[0] = addw[0];
		addwtmp[0] |= ((u32) (addw[1]) << 8);
		addwtmp[0] |= ((u32) (addw[2]) << 16);
		addwtmp[0] |= ((u32) (addw[3]) << 24);
		addwtmp[1] = addw[4];
		addwtmp[1] |= ((u32) (addw[5]) << 8);
	}

	/* Weceive match twansmittew addwess (WCMTA) mechanism */
	b43_shm_wwite32(dev, B43_SHM_WCMTA,
			(index * 2) + 0, addwtmp[0]);
	b43_shm_wwite16(dev, B43_SHM_WCMTA,
			(index * 2) + 1, addwtmp[1]);
}

/* The ucode wiww use phase1 key with TEK key to decwypt wx packets.
 * When a packet is weceived, the iv32 is checked.
 * - if it doesn't the packet is wetuwned without modification (and softwawe
 *   decwyption can be done). That's what happen when iv16 wwap.
 * - if it does, the wc4 key is computed, and decwyption is twied.
 *   Eithew it wiww success and B43_WX_MAC_DEC is wetuwned,
 *   eithew it faiws and B43_WX_MAC_DEC|B43_WX_MAC_DECEWW is wetuwned
 *   and the packet is not usabwe (it got modified by the ucode).
 * So in owdew to nevew have B43_WX_MAC_DECEWW, we shouwd pwovide
 * a iv32 and phase1key that match. Because we dwop packets in case of
 * B43_WX_MAC_DECEWW, if we have a cowwect iv32 but a wwong phase1key, aww
 * packets wiww be wost without highew wayew knowing (ie no wesync possibwe
 * untiw next wwap).
 *
 * NOTE : this shouwd suppowt 50 key wike WCMTA because
 * (B43_SHM_SH_KEYIDXBWOCK - B43_SHM_SH_TKIPTSCTTAK)/14 = 50
 */
static void wx_tkip_phase1_wwite(stwuct b43_wwdev *dev, u8 index, u32 iv32,
		u16 *phase1key)
{
	unsigned int i;
	u32 offset;
	u8 paiwwise_keys_stawt = B43_NW_GWOUP_KEYS * 2;

	if (!modpawam_hwtkip)
		wetuwn;

	if (b43_new_kidx_api(dev))
		paiwwise_keys_stawt = B43_NW_GWOUP_KEYS;

	B43_WAWN_ON(index < paiwwise_keys_stawt);
	/* We have fouw defauwt TX keys and possibwy fouw defauwt WX keys.
	 * Physicaw mac 0 is mapped to physicaw key 4 ow 8, depending
	 * on the fiwmwawe vewsion.
	 * So we must adjust the index hewe.
	 */
	index -= paiwwise_keys_stawt;
	B43_WAWN_ON(index >= B43_NW_PAIWWISE_KEYS);

	if (b43_debug(dev, B43_DBG_KEYS)) {
		b43dbg(dev->ww, "wx_tkip_phase1_wwite : idx 0x%x, iv32 0x%x\n",
				index, iv32);
	}
	/* Wwite the key to the  WX tkip shawed mem */
	offset = B43_SHM_SH_TKIPTSCTTAK + index * (10 + 4);
	fow (i = 0; i < 10; i += 2) {
		b43_shm_wwite16(dev, B43_SHM_SHAWED, offset + i,
				phase1key ? phase1key[i / 2] : 0);
	}
	b43_shm_wwite16(dev, B43_SHM_SHAWED, offset + i, iv32);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, offset + i + 2, iv32 >> 16);
}

static void b43_op_update_tkip_key(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_key_conf *keyconf,
				   stwuct ieee80211_sta *sta,
				   u32 iv32, u16 *phase1key)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev;
	int index = keyconf->hw_key_idx;

	if (B43_WAWN_ON(!modpawam_hwtkip))
		wetuwn;

	/* This is onwy cawwed fwom the WX path thwough mac80211, whewe
	 * ouw mutex is awweady wocked. */
	B43_WAWN_ON(!mutex_is_wocked(&ww->mutex));
	dev = ww->cuwwent_dev;
	B43_WAWN_ON(!dev || b43_status(dev) < B43_STAT_INITIAWIZED);

	keymac_wwite(dev, index, NUWW);	/* Fiwst zewo out mac to avoid wace */

	wx_tkip_phase1_wwite(dev, index, iv32, phase1key);
	/* onwy paiwwise TKIP keys awe suppowted wight now */
	if (WAWN_ON(!sta))
		wetuwn;
	keymac_wwite(dev, index, sta->addw);
}

static void do_key_wwite(stwuct b43_wwdev *dev,
			 u8 index, u8 awgowithm,
			 const u8 *key, size_t key_wen, const u8 *mac_addw)
{
	u8 buf[B43_SEC_KEYSIZE] = { 0, };
	u8 paiwwise_keys_stawt = B43_NW_GWOUP_KEYS * 2;

	if (b43_new_kidx_api(dev))
		paiwwise_keys_stawt = B43_NW_GWOUP_KEYS;

	B43_WAWN_ON(index >= AWWAY_SIZE(dev->key));
	B43_WAWN_ON(key_wen > B43_SEC_KEYSIZE);

	if (index >= paiwwise_keys_stawt)
		keymac_wwite(dev, index, NUWW);	/* Fiwst zewo out mac. */
	if (awgowithm == B43_SEC_AWGO_TKIP) {
		/*
		 * We shouwd pwovide an initiaw iv32, phase1key paiw.
		 * We couwd stawt with iv32=0 and compute the cowwesponding
		 * phase1key, but this means cawwing ieee80211_get_tkip_key
		 * with a fake skb (ow expowt othew tkip function).
		 * Because we awe wazy we hope iv32 won't stawt with
		 * 0xffffffff and wet's b43_op_update_tkip_key pwovide a
		 * cowwect paiw.
		 */
		wx_tkip_phase1_wwite(dev, index, 0xffffffff, (u16*)buf);
	} ewse if (index >= paiwwise_keys_stawt) /* cweaw it */
		wx_tkip_phase1_wwite(dev, index, 0, NUWW);
	if (key)
		memcpy(buf, key, key_wen);
	key_wwite(dev, index, awgowithm, buf);
	if (index >= paiwwise_keys_stawt)
		keymac_wwite(dev, index, mac_addw);

	dev->key[index].awgowithm = awgowithm;
}

static int b43_key_wwite(stwuct b43_wwdev *dev,
			 int index, u8 awgowithm,
			 const u8 *key, size_t key_wen,
			 const u8 *mac_addw,
			 stwuct ieee80211_key_conf *keyconf)
{
	int i;
	int paiwwise_keys_stawt;

	/* Fow AWG_TKIP the key is encoded as a 256-bit (32 byte) data bwock:
	 * 	- Tempowaw Encwyption Key (128 bits)
	 * 	- Tempowaw Authenticatow Tx MIC Key (64 bits)
	 * 	- Tempowaw Authenticatow Wx MIC Key (64 bits)
	 *
	 * 	Hawdwawe onwy stowe TEK
	 */
	if (awgowithm == B43_SEC_AWGO_TKIP && key_wen == 32)
		key_wen = 16;
	if (key_wen > B43_SEC_KEYSIZE)
		wetuwn -EINVAW;
	fow (i = 0; i < AWWAY_SIZE(dev->key); i++) {
		/* Check that we don't awweady have this key. */
		B43_WAWN_ON(dev->key[i].keyconf == keyconf);
	}
	if (index < 0) {
		/* Paiwwise key. Get an empty swot fow the key. */
		if (b43_new_kidx_api(dev))
			paiwwise_keys_stawt = B43_NW_GWOUP_KEYS;
		ewse
			paiwwise_keys_stawt = B43_NW_GWOUP_KEYS * 2;
		fow (i = paiwwise_keys_stawt;
		     i < paiwwise_keys_stawt + B43_NW_PAIWWISE_KEYS;
		     i++) {
			B43_WAWN_ON(i >= AWWAY_SIZE(dev->key));
			if (!dev->key[i].keyconf) {
				/* found empty */
				index = i;
				bweak;
			}
		}
		if (index < 0) {
			b43wawn(dev->ww, "Out of hawdwawe key memowy\n");
			wetuwn -ENOSPC;
		}
	} ewse
		B43_WAWN_ON(index > 3);

	do_key_wwite(dev, index, awgowithm, key, key_wen, mac_addw);
	if ((index <= 3) && !b43_new_kidx_api(dev)) {
		/* Defauwt WX key */
		B43_WAWN_ON(mac_addw);
		do_key_wwite(dev, index + 4, awgowithm, key, key_wen, NUWW);
	}
	keyconf->hw_key_idx = index;
	dev->key[index].keyconf = keyconf;

	wetuwn 0;
}

static int b43_key_cweaw(stwuct b43_wwdev *dev, int index)
{
	if (B43_WAWN_ON((index < 0) || (index >= AWWAY_SIZE(dev->key))))
		wetuwn -EINVAW;
	do_key_wwite(dev, index, B43_SEC_AWGO_NONE,
		     NUWW, B43_SEC_KEYSIZE, NUWW);
	if ((index <= 3) && !b43_new_kidx_api(dev)) {
		do_key_wwite(dev, index + 4, B43_SEC_AWGO_NONE,
			     NUWW, B43_SEC_KEYSIZE, NUWW);
	}
	dev->key[index].keyconf = NUWW;

	wetuwn 0;
}

static void b43_cweaw_keys(stwuct b43_wwdev *dev)
{
	int i, count;

	if (b43_new_kidx_api(dev))
		count = B43_NW_GWOUP_KEYS + B43_NW_PAIWWISE_KEYS;
	ewse
		count = B43_NW_GWOUP_KEYS * 2 + B43_NW_PAIWWISE_KEYS;
	fow (i = 0; i < count; i++)
		b43_key_cweaw(dev, i);
}

static void b43_dump_keymemowy(stwuct b43_wwdev *dev)
{
	unsigned int i, index, count, offset, paiwwise_keys_stawt;
	u8 mac[ETH_AWEN];
	u16 awgo;
	u32 wcmta0;
	u16 wcmta1;
	u64 hf;
	stwuct b43_key *key;

	if (!b43_debug(dev, B43_DBG_KEYS))
		wetuwn;

	hf = b43_hf_wead(dev);
	b43dbg(dev->ww, "Hawdwawe key memowy dump:  USEDEFKEYS=%u\n",
	       !!(hf & B43_HF_USEDEFKEYS));
	if (b43_new_kidx_api(dev)) {
		paiwwise_keys_stawt = B43_NW_GWOUP_KEYS;
		count = B43_NW_GWOUP_KEYS + B43_NW_PAIWWISE_KEYS;
	} ewse {
		paiwwise_keys_stawt = B43_NW_GWOUP_KEYS * 2;
		count = B43_NW_GWOUP_KEYS * 2 + B43_NW_PAIWWISE_KEYS;
	}
	fow (index = 0; index < count; index++) {
		key = &(dev->key[index]);
		pwintk(KEWN_DEBUG "Key swot %02u: %s",
		       index, (key->keyconf == NUWW) ? " " : "*");
		offset = dev->ktp + (index * B43_SEC_KEYSIZE);
		fow (i = 0; i < B43_SEC_KEYSIZE; i += 2) {
			u16 tmp = b43_shm_wead16(dev, B43_SHM_SHAWED, offset + i);
			pwintk("%02X%02X", (tmp & 0xFF), ((tmp >> 8) & 0xFF));
		}

		awgo = b43_shm_wead16(dev, B43_SHM_SHAWED,
				      B43_SHM_SH_KEYIDXBWOCK + (index * 2));
		pwintk("   Awgo: %04X/%02X", awgo, key->awgowithm);

		if (index >= paiwwise_keys_stawt) {
			if (key->awgowithm == B43_SEC_AWGO_TKIP) {
				pwintk("   TKIP: ");
				offset = B43_SHM_SH_TKIPTSCTTAK + (index - 4) * (10 + 4);
				fow (i = 0; i < 14; i += 2) {
					u16 tmp = b43_shm_wead16(dev, B43_SHM_SHAWED, offset + i);
					pwintk("%02X%02X", (tmp & 0xFF), ((tmp >> 8) & 0xFF));
				}
			}
			wcmta0 = b43_shm_wead32(dev, B43_SHM_WCMTA,
						((index - paiwwise_keys_stawt) * 2) + 0);
			wcmta1 = b43_shm_wead16(dev, B43_SHM_WCMTA,
						((index - paiwwise_keys_stawt) * 2) + 1);
			*((__we32 *)(&mac[0])) = cpu_to_we32(wcmta0);
			*((__we16 *)(&mac[4])) = cpu_to_we16(wcmta1);
			pwintk("   MAC: %pM", mac);
		} ewse
			pwintk("   DEFAUWT KEY");
		pwintk("\n");
	}
}

void b43_powew_saving_ctw_bits(stwuct b43_wwdev *dev, unsigned int ps_fwags)
{
	u32 macctw;
	u16 ucstat;
	boow hwps;
	boow awake;
	int i;

	B43_WAWN_ON((ps_fwags & B43_PS_ENABWED) &&
		    (ps_fwags & B43_PS_DISABWED));
	B43_WAWN_ON((ps_fwags & B43_PS_AWAKE) && (ps_fwags & B43_PS_ASWEEP));

	if (ps_fwags & B43_PS_ENABWED) {
		hwps = twue;
	} ewse if (ps_fwags & B43_PS_DISABWED) {
		hwps = fawse;
	} ewse {
		//TODO: If powewsave is not off and FIXME is not set and we awe not in adhoc
		//      and thus is not an AP and we awe associated, set bit 25
	}
	if (ps_fwags & B43_PS_AWAKE) {
		awake = twue;
	} ewse if (ps_fwags & B43_PS_ASWEEP) {
		awake = fawse;
	} ewse {
		//TODO: If the device is awake ow this is an AP, ow we awe scanning, ow FIXME,
		//      ow we awe associated, ow FIXME, ow the watest PS-Poww packet sent was
		//      successfuw, set bit26
	}

/* FIXME: Fow now we fowce awake-on and hwps-off */
	hwps = fawse;
	awake = twue;

	macctw = b43_wead32(dev, B43_MMIO_MACCTW);
	if (hwps)
		macctw |= B43_MACCTW_HWPS;
	ewse
		macctw &= ~B43_MACCTW_HWPS;
	if (awake)
		macctw |= B43_MACCTW_AWAKE;
	ewse
		macctw &= ~B43_MACCTW_AWAKE;
	b43_wwite32(dev, B43_MMIO_MACCTW, macctw);
	/* Commit wwite */
	b43_wead32(dev, B43_MMIO_MACCTW);
	if (awake && dev->dev->cowe_wev >= 5) {
		/* Wait fow the micwocode to wake up. */
		fow (i = 0; i < 100; i++) {
			ucstat = b43_shm_wead16(dev, B43_SHM_SHAWED,
						B43_SHM_SH_UCODESTAT);
			if (ucstat != B43_SHM_SH_UCODESTAT_SWEEP)
				bweak;
			udeway(10);
		}
	}
}

/* https://bcm-v4.sipsowutions.net/802.11/PHY/BmacCowePwwWeset */
void b43_wiwewess_cowe_phy_pww_weset(stwuct b43_wwdev *dev)
{
	stwuct bcma_dwv_cc *bcma_cc __maybe_unused;
	stwuct ssb_chipcommon *ssb_cc __maybe_unused;

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_cc = &dev->dev->bdev->bus->dwv_cc;

		bcma_cc_wwite32(bcma_cc, BCMA_CC_PMU_CHIPCTW_ADDW, 0);
		bcma_cc_mask32(bcma_cc, BCMA_CC_PMU_CHIPCTW_DATA, ~0x4);
		bcma_cc_set32(bcma_cc, BCMA_CC_PMU_CHIPCTW_DATA, 0x4);
		bcma_cc_mask32(bcma_cc, BCMA_CC_PMU_CHIPCTW_DATA, ~0x4);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		ssb_cc = &dev->dev->sdev->bus->chipco;

		chipco_wwite32(ssb_cc, SSB_CHIPCO_CHIPCTW_ADDW, 0);
		chipco_mask32(ssb_cc, SSB_CHIPCO_CHIPCTW_DATA, ~0x4);
		chipco_set32(ssb_cc, SSB_CHIPCO_CHIPCTW_DATA, 0x4);
		chipco_mask32(ssb_cc, SSB_CHIPCO_CHIPCTW_DATA, ~0x4);
		bweak;
#endif
	}
}

#ifdef CONFIG_B43_BCMA
static void b43_bcma_phy_weset(stwuct b43_wwdev *dev)
{
	u32 fwags;

	/* Put PHY into weset */
	fwags = bcma_awead32(dev->dev->bdev, BCMA_IOCTW);
	fwags |= B43_BCMA_IOCTW_PHY_WESET;
	fwags |= B43_BCMA_IOCTW_PHY_BW_20MHZ; /* Make 20 MHz def */
	bcma_awwite32(dev->dev->bdev, BCMA_IOCTW, fwags);
	udeway(2);

	b43_phy_take_out_of_weset(dev);
}

static void b43_bcma_wiwewess_cowe_weset(stwuct b43_wwdev *dev, boow gmode)
{
	u32 weq = B43_BCMA_CWKCTWST_80211_PWW_WEQ |
		  B43_BCMA_CWKCTWST_PHY_PWW_WEQ;
	u32 status = B43_BCMA_CWKCTWST_80211_PWW_ST |
		     B43_BCMA_CWKCTWST_PHY_PWW_ST;
	u32 fwags;

	fwags = B43_BCMA_IOCTW_PHY_CWKEN;
	if (gmode)
		fwags |= B43_BCMA_IOCTW_GMODE;
	b43_device_enabwe(dev, fwags);

	if (dev->phy.type == B43_PHYTYPE_AC) {
		u16 tmp;

		tmp = bcma_awead32(dev->dev->bdev, BCMA_IOCTW);
		tmp &= ~B43_BCMA_IOCTW_DAC;
		tmp |= 0x100;
		bcma_awwite32(dev->dev->bdev, BCMA_IOCTW, tmp);

		tmp = bcma_awead32(dev->dev->bdev, BCMA_IOCTW);
		tmp &= ~B43_BCMA_IOCTW_PHY_CWKEN;
		bcma_awwite32(dev->dev->bdev, BCMA_IOCTW, tmp);

		tmp = bcma_awead32(dev->dev->bdev, BCMA_IOCTW);
		tmp |= B43_BCMA_IOCTW_PHY_CWKEN;
		bcma_awwite32(dev->dev->bdev, BCMA_IOCTW, tmp);
	}

	bcma_cowe_set_cwockmode(dev->dev->bdev, BCMA_CWKMODE_FAST);
	b43_bcma_phy_weset(dev);
	bcma_cowe_pww_ctw(dev->dev->bdev, weq, status, twue);
}
#endif

#ifdef CONFIG_B43_SSB
static void b43_ssb_wiwewess_cowe_weset(stwuct b43_wwdev *dev, boow gmode)
{
	u32 fwags = 0;

	if (gmode)
		fwags |= B43_TMSWOW_GMODE;
	fwags |= B43_TMSWOW_PHYCWKEN;
	fwags |= B43_TMSWOW_PHYWESET;
	if (dev->phy.type == B43_PHYTYPE_N)
		fwags |= B43_TMSWOW_PHY_BANDWIDTH_20MHZ; /* Make 20 MHz def */
	b43_device_enabwe(dev, fwags);
	msweep(2);		/* Wait fow the PWW to tuwn on. */

	b43_phy_take_out_of_weset(dev);
}
#endif

void b43_wiwewess_cowe_weset(stwuct b43_wwdev *dev, boow gmode)
{
	u32 macctw;

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		b43_bcma_wiwewess_cowe_weset(dev, gmode);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		b43_ssb_wiwewess_cowe_weset(dev, gmode);
		bweak;
#endif
	}

	/* Tuwn Anawog ON, but onwy if we awweady know the PHY-type.
	 * This pwotects against vewy eawwy setup whewe we don't know the
	 * PHY-type, yet. wiwewess_cowe_weset wiww be cawwed once again watew,
	 * when we know the PHY-type. */
	if (dev->phy.ops)
		dev->phy.ops->switch_anawog(dev, 1);

	macctw = b43_wead32(dev, B43_MMIO_MACCTW);
	macctw &= ~B43_MACCTW_GMODE;
	if (gmode)
		macctw |= B43_MACCTW_GMODE;
	macctw |= B43_MACCTW_IHW_ENABWED;
	b43_wwite32(dev, B43_MMIO_MACCTW, macctw);
}

static void handwe_iwq_twansmit_status(stwuct b43_wwdev *dev)
{
	u32 v0, v1;
	u16 tmp;
	stwuct b43_txstatus stat;

	whiwe (1) {
		v0 = b43_wead32(dev, B43_MMIO_XMITSTAT_0);
		if (!(v0 & 0x00000001))
			bweak;
		v1 = b43_wead32(dev, B43_MMIO_XMITSTAT_1);

		stat.cookie = (v0 >> 16);
		stat.seq = (v1 & 0x0000FFFF);
		stat.phy_stat = ((v1 & 0x00FF0000) >> 16);
		tmp = (v0 & 0x0000FFFF);
		stat.fwame_count = ((tmp & 0xF000) >> 12);
		stat.wts_count = ((tmp & 0x0F00) >> 8);
		stat.supp_weason = ((tmp & 0x001C) >> 2);
		stat.pm_indicated = !!(tmp & 0x0080);
		stat.intewmediate = !!(tmp & 0x0040);
		stat.fow_ampdu = !!(tmp & 0x0020);
		stat.acked = !!(tmp & 0x0002);

		b43_handwe_txstatus(dev, &stat);
	}
}

static void dwain_txstatus_queue(stwuct b43_wwdev *dev)
{
	u32 dummy;

	if (dev->dev->cowe_wev < 5)
		wetuwn;
	/* Wead aww entwies fwom the micwocode TXstatus FIFO
	 * and thwow them away.
	 */
	whiwe (1) {
		dummy = b43_wead32(dev, B43_MMIO_XMITSTAT_0);
		if (!(dummy & 0x00000001))
			bweak;
		dummy = b43_wead32(dev, B43_MMIO_XMITSTAT_1);
	}
}

static u32 b43_jssi_wead(stwuct b43_wwdev *dev)
{
	u32 vaw = 0;

	vaw = b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_JSSI1);
	vaw <<= 16;
	vaw |= b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_JSSI0);

	wetuwn vaw;
}

static void b43_jssi_wwite(stwuct b43_wwdev *dev, u32 jssi)
{
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_JSSI0,
			(jssi & 0x0000FFFF));
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_JSSI1,
			(jssi & 0xFFFF0000) >> 16);
}

static void b43_genewate_noise_sampwe(stwuct b43_wwdev *dev)
{
	b43_jssi_wwite(dev, 0x7F7F7F7F);
	b43_wwite32(dev, B43_MMIO_MACCMD,
		    b43_wead32(dev, B43_MMIO_MACCMD) | B43_MACCMD_BGNOISE);
}

static void b43_cawcuwate_wink_quawity(stwuct b43_wwdev *dev)
{
	/* Top hawf of Wink Quawity cawcuwation. */

	if (dev->phy.type != B43_PHYTYPE_G)
		wetuwn;
	if (dev->noisecawc.cawcuwation_wunning)
		wetuwn;
	dev->noisecawc.cawcuwation_wunning = twue;
	dev->noisecawc.nw_sampwes = 0;

	b43_genewate_noise_sampwe(dev);
}

static void handwe_iwq_noise(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_g *phy = dev->phy.g;
	u16 tmp;
	u8 noise[4];
	u8 i, j;
	s32 avewage;

	/* Bottom hawf of Wink Quawity cawcuwation. */

	if (dev->phy.type != B43_PHYTYPE_G)
		wetuwn;

	/* Possibwe wace condition: It might be possibwe that the usew
	 * changed to a diffewent channew in the meantime since we
	 * stawted the cawcuwation. We ignowe that fact, since it's
	 * not weawwy that much of a pwobwem. The backgwound noise is
	 * an estimation onwy anyway. Swightwy wwong wesuwts wiww get damped
	 * by the avewaging of the 8 sampwe wounds. Additionawwy the
	 * vawue is showtwived. So it wiww be wepwaced by the next noise
	 * cawcuwation wound soon. */

	B43_WAWN_ON(!dev->noisecawc.cawcuwation_wunning);
	*((__we32 *)noise) = cpu_to_we32(b43_jssi_wead(dev));
	if (noise[0] == 0x7F || noise[1] == 0x7F ||
	    noise[2] == 0x7F || noise[3] == 0x7F)
		goto genewate_new;

	/* Get the noise sampwes. */
	B43_WAWN_ON(dev->noisecawc.nw_sampwes >= 8);
	i = dev->noisecawc.nw_sampwes;
	noise[0] = cwamp_vaw(noise[0], 0, AWWAY_SIZE(phy->nwssi_wt) - 1);
	noise[1] = cwamp_vaw(noise[1], 0, AWWAY_SIZE(phy->nwssi_wt) - 1);
	noise[2] = cwamp_vaw(noise[2], 0, AWWAY_SIZE(phy->nwssi_wt) - 1);
	noise[3] = cwamp_vaw(noise[3], 0, AWWAY_SIZE(phy->nwssi_wt) - 1);
	dev->noisecawc.sampwes[i][0] = phy->nwssi_wt[noise[0]];
	dev->noisecawc.sampwes[i][1] = phy->nwssi_wt[noise[1]];
	dev->noisecawc.sampwes[i][2] = phy->nwssi_wt[noise[2]];
	dev->noisecawc.sampwes[i][3] = phy->nwssi_wt[noise[3]];
	dev->noisecawc.nw_sampwes++;
	if (dev->noisecawc.nw_sampwes == 8) {
		/* Cawcuwate the Wink Quawity by the noise sampwes. */
		avewage = 0;
		fow (i = 0; i < 8; i++) {
			fow (j = 0; j < 4; j++)
				avewage += dev->noisecawc.sampwes[i][j];
		}
		avewage /= (8 * 4);
		avewage *= 125;
		avewage += 64;
		avewage /= 128;
		tmp = b43_shm_wead16(dev, B43_SHM_SHAWED, 0x40C);
		tmp = (tmp / 128) & 0x1F;
		if (tmp >= 8)
			avewage += 2;
		ewse
			avewage -= 25;
		if (tmp == 8)
			avewage -= 72;
		ewse
			avewage -= 48;

		dev->stats.wink_noise = avewage;
		dev->noisecawc.cawcuwation_wunning = fawse;
		wetuwn;
	}
genewate_new:
	b43_genewate_noise_sampwe(dev);
}

static void handwe_iwq_tbtt_indication(stwuct b43_wwdev *dev)
{
	if (b43_is_mode(dev->ww, NW80211_IFTYPE_AP)) {
		///TODO: PS TBTT
	} ewse {
		if (1 /*FIXME: the wast PSpoww fwame was sent successfuwwy */ )
			b43_powew_saving_ctw_bits(dev, 0);
	}
	if (b43_is_mode(dev->ww, NW80211_IFTYPE_ADHOC))
		dev->dfq_vawid = twue;
}

static void handwe_iwq_atim_end(stwuct b43_wwdev *dev)
{
	if (dev->dfq_vawid) {
		b43_wwite32(dev, B43_MMIO_MACCMD,
			    b43_wead32(dev, B43_MMIO_MACCMD)
			    | B43_MACCMD_DFQ_VAWID);
		dev->dfq_vawid = fawse;
	}
}

static void handwe_iwq_pmq(stwuct b43_wwdev *dev)
{
	u32 tmp;

	//TODO: AP mode.

	whiwe (1) {
		tmp = b43_wead32(dev, B43_MMIO_PS_STATUS);
		if (!(tmp & 0x00000008))
			bweak;
	}
	/* 16bit wwite is odd, but cowwect. */
	b43_wwite16(dev, B43_MMIO_PS_STATUS, 0x0002);
}

static void b43_wwite_tempwate_common(stwuct b43_wwdev *dev,
				      const u8 *data, u16 size,
				      u16 wam_offset,
				      u16 shm_size_offset, u8 wate)
{
	u32 i, tmp;
	stwuct b43_pwcp_hdw4 pwcp;

	pwcp.data = 0;
	b43_genewate_pwcp_hdw(&pwcp, size + FCS_WEN, wate);
	b43_wam_wwite(dev, wam_offset, we32_to_cpu(pwcp.data));
	wam_offset += sizeof(u32);
	/* The PWCP is 6 bytes wong, but we onwy wwote 4 bytes, yet.
	 * So weave the fiwst two bytes of the next wwite bwank.
	 */
	tmp = (u32) (data[0]) << 16;
	tmp |= (u32) (data[1]) << 24;
	b43_wam_wwite(dev, wam_offset, tmp);
	wam_offset += sizeof(u32);
	fow (i = 2; i < size; i += sizeof(u32)) {
		tmp = (u32) (data[i + 0]);
		if (i + 1 < size)
			tmp |= (u32) (data[i + 1]) << 8;
		if (i + 2 < size)
			tmp |= (u32) (data[i + 2]) << 16;
		if (i + 3 < size)
			tmp |= (u32) (data[i + 3]) << 24;
		b43_wam_wwite(dev, wam_offset + i - 2, tmp);
	}
	b43_shm_wwite16(dev, B43_SHM_SHAWED, shm_size_offset,
			size + sizeof(stwuct b43_pwcp_hdw6));
}

/* Check if the use of the antenna that ieee80211 towd us to
 * use is possibwe. This wiww faww back to DEFAUWT.
 * "antenna_nw" is the antenna identifiew we got fwom ieee80211. */
u8 b43_ieee80211_antenna_sanitize(stwuct b43_wwdev *dev,
				  u8 antenna_nw)
{
	u8 antenna_mask;

	if (antenna_nw == 0) {
		/* Zewo means "use defauwt antenna". That's awways OK. */
		wetuwn 0;
	}

	/* Get the mask of avaiwabwe antennas. */
	if (dev->phy.gmode)
		antenna_mask = dev->dev->bus_spwom->ant_avaiwabwe_bg;
	ewse
		antenna_mask = dev->dev->bus_spwom->ant_avaiwabwe_a;

	if (!(antenna_mask & (1 << (antenna_nw - 1)))) {
		/* This antenna is not avaiwabwe. Faww back to defauwt. */
		wetuwn 0;
	}

	wetuwn antenna_nw;
}

/* Convewt a b43 antenna numbew vawue to the PHY TX contwow vawue. */
static u16 b43_antenna_to_phyctw(int antenna)
{
	switch (antenna) {
	case B43_ANTENNA0:
		wetuwn B43_TXH_PHY_ANT0;
	case B43_ANTENNA1:
		wetuwn B43_TXH_PHY_ANT1;
	case B43_ANTENNA2:
		wetuwn B43_TXH_PHY_ANT2;
	case B43_ANTENNA3:
		wetuwn B43_TXH_PHY_ANT3;
	case B43_ANTENNA_AUTO0:
	case B43_ANTENNA_AUTO1:
		wetuwn B43_TXH_PHY_ANT01AUTO;
	}
	B43_WAWN_ON(1);
	wetuwn 0;
}

static void b43_wwite_beacon_tempwate(stwuct b43_wwdev *dev,
				      u16 wam_offset,
				      u16 shm_size_offset)
{
	unsigned int i, wen, vawiabwe_wen;
	const stwuct ieee80211_mgmt *bcn;
	const u8 *ie;
	boow tim_found = fawse;
	unsigned int wate;
	u16 ctw;
	int antenna;
	stwuct ieee80211_tx_info *info;
	unsigned wong fwags;
	stwuct sk_buff *beacon_skb;

	spin_wock_iwqsave(&dev->ww->beacon_wock, fwags);
	info = IEEE80211_SKB_CB(dev->ww->cuwwent_beacon);
	wate = ieee80211_get_tx_wate(dev->ww->hw, info)->hw_vawue;
	/* Cwone the beacon, so it cannot go away, whiwe we wwite it to hw. */
	beacon_skb = skb_cwone(dev->ww->cuwwent_beacon, GFP_ATOMIC);
	spin_unwock_iwqwestowe(&dev->ww->beacon_wock, fwags);

	if (!beacon_skb) {
		b43dbg(dev->ww, "Couwd not upwoad beacon. "
		       "Faiwed to cwone beacon skb.");
		wetuwn;
	}

	bcn = (const stwuct ieee80211_mgmt *)(beacon_skb->data);
	wen = min_t(size_t, beacon_skb->wen,
		    0x200 - sizeof(stwuct b43_pwcp_hdw6));

	b43_wwite_tempwate_common(dev, (const u8 *)bcn,
				  wen, wam_offset, shm_size_offset, wate);

	/* Wwite the PHY TX contwow pawametews. */
	antenna = B43_ANTENNA_DEFAUWT;
	antenna = b43_antenna_to_phyctw(antenna);
	ctw = b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_BEACPHYCTW);
	/* We can't send beacons with showt pweambwe. Wouwd get PHY ewwows. */
	ctw &= ~B43_TXH_PHY_SHOWTPWMBW;
	ctw &= ~B43_TXH_PHY_ANT;
	ctw &= ~B43_TXH_PHY_ENC;
	ctw |= antenna;
	if (b43_is_cck_wate(wate))
		ctw |= B43_TXH_PHY_ENC_CCK;
	ewse
		ctw |= B43_TXH_PHY_ENC_OFDM;
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_BEACPHYCTW, ctw);

	/* Find the position of the TIM and the DTIM_pewiod vawue
	 * and wwite them to SHM. */
	ie = bcn->u.beacon.vawiabwe;
	vawiabwe_wen = wen - offsetof(stwuct ieee80211_mgmt, u.beacon.vawiabwe);
	fow (i = 0; i < vawiabwe_wen - 2; ) {
		uint8_t ie_id, ie_wen;

		ie_id = ie[i];
		ie_wen = ie[i + 1];
		if (ie_id == 5) {
			u16 tim_position;
			u16 dtim_pewiod;
			/* This is the TIM Infowmation Ewement */

			/* Check whethew the ie_wen is in the beacon data wange. */
			if (vawiabwe_wen < ie_wen + 2 + i)
				bweak;
			/* A vawid TIM is at weast 4 bytes wong. */
			if (ie_wen < 4)
				bweak;
			tim_found = twue;

			tim_position = sizeof(stwuct b43_pwcp_hdw6);
			tim_position += offsetof(stwuct ieee80211_mgmt, u.beacon.vawiabwe);
			tim_position += i;

			dtim_pewiod = ie[i + 3];

			b43_shm_wwite16(dev, B43_SHM_SHAWED,
					B43_SHM_SH_TIMBPOS, tim_position);
			b43_shm_wwite16(dev, B43_SHM_SHAWED,
					B43_SHM_SH_DTIMPEW, dtim_pewiod);
			bweak;
		}
		i += ie_wen + 2;
	}
	if (!tim_found) {
		/*
		 * If ucode wants to modify TIM do it behind the beacon, this
		 * wiww happen, fow exampwe, when doing mesh netwowking.
		 */
		b43_shm_wwite16(dev, B43_SHM_SHAWED,
				B43_SHM_SH_TIMBPOS,
				wen + sizeof(stwuct b43_pwcp_hdw6));
		b43_shm_wwite16(dev, B43_SHM_SHAWED,
				B43_SHM_SH_DTIMPEW, 0);
	}
	b43dbg(dev->ww, "Updated beacon tempwate at 0x%x\n", wam_offset);

	dev_kfwee_skb_any(beacon_skb);
}

static void b43_upwoad_beacon0(stwuct b43_wwdev *dev)
{
	stwuct b43_ww *ww = dev->ww;

	if (ww->beacon0_upwoaded)
		wetuwn;
	b43_wwite_beacon_tempwate(dev, B43_SHM_SH_BT_BASE0, B43_SHM_SH_BTW0);
	ww->beacon0_upwoaded = twue;
}

static void b43_upwoad_beacon1(stwuct b43_wwdev *dev)
{
	stwuct b43_ww *ww = dev->ww;

	if (ww->beacon1_upwoaded)
		wetuwn;
	b43_wwite_beacon_tempwate(dev, B43_SHM_SH_BT_BASE1, B43_SHM_SH_BTW1);
	ww->beacon1_upwoaded = twue;
}

static void handwe_iwq_beacon(stwuct b43_wwdev *dev)
{
	stwuct b43_ww *ww = dev->ww;
	u32 cmd, beacon0_vawid, beacon1_vawid;

	if (!b43_is_mode(ww, NW80211_IFTYPE_AP) &&
	    !b43_is_mode(ww, NW80211_IFTYPE_MESH_POINT) &&
	    !b43_is_mode(ww, NW80211_IFTYPE_ADHOC))
		wetuwn;

	/* This is the bottom hawf of the asynchwonous beacon update. */

	/* Ignowe intewwupt in the futuwe. */
	dev->iwq_mask &= ~B43_IWQ_BEACON;

	cmd = b43_wead32(dev, B43_MMIO_MACCMD);
	beacon0_vawid = (cmd & B43_MACCMD_BEACON0_VAWID);
	beacon1_vawid = (cmd & B43_MACCMD_BEACON1_VAWID);

	/* Scheduwe intewwupt manuawwy, if busy. */
	if (beacon0_vawid && beacon1_vawid) {
		b43_wwite32(dev, B43_MMIO_GEN_IWQ_WEASON, B43_IWQ_BEACON);
		dev->iwq_mask |= B43_IWQ_BEACON;
		wetuwn;
	}

	if (unwikewy(ww->beacon_tempwates_viwgin)) {
		/* We nevew upwoaded a beacon befowe.
		 * Upwoad both tempwates now, but onwy mawk one vawid. */
		ww->beacon_tempwates_viwgin = fawse;
		b43_upwoad_beacon0(dev);
		b43_upwoad_beacon1(dev);
		cmd = b43_wead32(dev, B43_MMIO_MACCMD);
		cmd |= B43_MACCMD_BEACON0_VAWID;
		b43_wwite32(dev, B43_MMIO_MACCMD, cmd);
	} ewse {
		if (!beacon0_vawid) {
			b43_upwoad_beacon0(dev);
			cmd = b43_wead32(dev, B43_MMIO_MACCMD);
			cmd |= B43_MACCMD_BEACON0_VAWID;
			b43_wwite32(dev, B43_MMIO_MACCMD, cmd);
		} ewse if (!beacon1_vawid) {
			b43_upwoad_beacon1(dev);
			cmd = b43_wead32(dev, B43_MMIO_MACCMD);
			cmd |= B43_MACCMD_BEACON1_VAWID;
			b43_wwite32(dev, B43_MMIO_MACCMD, cmd);
		}
	}
}

static void b43_do_beacon_update_twiggew_wowk(stwuct b43_wwdev *dev)
{
	u32 owd_iwq_mask = dev->iwq_mask;

	/* update beacon wight away ow defew to iwq */
	handwe_iwq_beacon(dev);
	if (owd_iwq_mask != dev->iwq_mask) {
		/* The handwew updated the IWQ mask. */
		B43_WAWN_ON(!dev->iwq_mask);
		if (b43_wead32(dev, B43_MMIO_GEN_IWQ_MASK)) {
			b43_wwite32(dev, B43_MMIO_GEN_IWQ_MASK, dev->iwq_mask);
		} ewse {
			/* Device intewwupts awe cuwwentwy disabwed. That means
			 * we just wan the hawdiwq handwew and scheduwed the
			 * IWQ thwead. The thwead wiww wwite the IWQ mask when
			 * it finished, so thewe's nothing to do hewe. Wwiting
			 * the mask _hewe_ wouwd incowwectwy we-enabwe IWQs. */
		}
	}
}

static void b43_beacon_update_twiggew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct b43_ww *ww = containew_of(wowk, stwuct b43_ww,
					 beacon_update_twiggew);
	stwuct b43_wwdev *dev;

	mutex_wock(&ww->mutex);
	dev = ww->cuwwent_dev;
	if (wikewy(dev && (b43_status(dev) >= B43_STAT_INITIAWIZED))) {
		if (b43_bus_host_is_sdio(dev->dev)) {
			/* ww->mutex is enough. */
			b43_do_beacon_update_twiggew_wowk(dev);
		} ewse {
			spin_wock_iwq(&ww->hawdiwq_wock);
			b43_do_beacon_update_twiggew_wowk(dev);
			spin_unwock_iwq(&ww->hawdiwq_wock);
		}
	}
	mutex_unwock(&ww->mutex);
}

/* Asynchwonouswy update the packet tempwates in tempwate WAM. */
static void b43_update_tempwates(stwuct b43_ww *ww)
{
	stwuct sk_buff *beacon, *owd_beacon;
	unsigned wong fwags;

	/* This is the top hawf of the asynchwonous beacon update.
	 * The bottom hawf is the beacon IWQ.
	 * Beacon update must be asynchwonous to avoid sending an
	 * invawid beacon. This can happen fow exampwe, if the fiwmwawe
	 * twansmits a beacon whiwe we awe updating it. */

	/* We couwd modify the existing beacon and set the aid bit in
	 * the TIM fiewd, but that wouwd pwobabwy wequiwe wesizing and
	 * moving of data within the beacon tempwate.
	 * Simpwy wequest a new beacon and wet mac80211 do the hawd wowk. */
	beacon = ieee80211_beacon_get(ww->hw, ww->vif, 0);
	if (unwikewy(!beacon))
		wetuwn;

	spin_wock_iwqsave(&ww->beacon_wock, fwags);
	owd_beacon = ww->cuwwent_beacon;
	ww->cuwwent_beacon = beacon;
	ww->beacon0_upwoaded = fawse;
	ww->beacon1_upwoaded = fawse;
	spin_unwock_iwqwestowe(&ww->beacon_wock, fwags);

	ieee80211_queue_wowk(ww->hw, &ww->beacon_update_twiggew);

	if (owd_beacon)
		dev_kfwee_skb_any(owd_beacon);
}

static void b43_set_beacon_int(stwuct b43_wwdev *dev, u16 beacon_int)
{
	b43_time_wock(dev);
	if (dev->dev->cowe_wev >= 3) {
		b43_wwite32(dev, B43_MMIO_TSF_CFP_WEP, (beacon_int << 16));
		b43_wwite32(dev, B43_MMIO_TSF_CFP_STAWT, (beacon_int << 10));
	} ewse {
		b43_wwite16(dev, 0x606, (beacon_int >> 6));
		b43_wwite16(dev, 0x610, beacon_int);
	}
	b43_time_unwock(dev);
	b43dbg(dev->ww, "Set beacon intewvaw to %u\n", beacon_int);
}

static void b43_handwe_fiwmwawe_panic(stwuct b43_wwdev *dev)
{
	u16 weason;

	/* Wead the wegistew that contains the weason code fow the panic. */
	weason = b43_shm_wead16(dev, B43_SHM_SCWATCH, B43_FWPANIC_WEASON_WEG);
	b43eww(dev->ww, "Whoopsy, fiwmwawe panic! Weason: %u\n", weason);

	switch (weason) {
	defauwt:
		b43dbg(dev->ww, "The panic weason is unknown.\n");
		fawwthwough;
	case B43_FWPANIC_DIE:
		/* Do not westawt the contwowwew ow fiwmwawe.
		 * The device is nonfunctionaw fwom now on.
		 * Westawting wouwd wesuwt in this panic to twiggew again,
		 * so we avoid that wecuwsion. */
		bweak;
	case B43_FWPANIC_WESTAWT:
		b43_contwowwew_westawt(dev, "Micwocode panic");
		bweak;
	}
}

static void handwe_iwq_ucode_debug(stwuct b43_wwdev *dev)
{
	unsigned int i, cnt;
	u16 weason, mawkew_id, mawkew_wine;
	__we16 *buf;

	/* The pwopwietawy fiwmwawe doesn't have this IWQ. */
	if (!dev->fw.opensouwce)
		wetuwn;

	/* Wead the wegistew that contains the weason code fow this IWQ. */
	weason = b43_shm_wead16(dev, B43_SHM_SCWATCH, B43_DEBUGIWQ_WEASON_WEG);

	switch (weason) {
	case B43_DEBUGIWQ_PANIC:
		b43_handwe_fiwmwawe_panic(dev);
		bweak;
	case B43_DEBUGIWQ_DUMP_SHM:
		if (!B43_DEBUG)
			bweak; /* Onwy with dwivew debugging enabwed. */
		buf = kmawwoc(4096, GFP_ATOMIC);
		if (!buf) {
			b43dbg(dev->ww, "SHM-dump: Faiwed to awwocate memowy\n");
			goto out;
		}
		fow (i = 0; i < 4096; i += 2) {
			u16 tmp = b43_shm_wead16(dev, B43_SHM_SHAWED, i);
			buf[i / 2] = cpu_to_we16(tmp);
		}
		b43info(dev->ww, "Shawed memowy dump:\n");
		pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_OFFSET,
			       16, 2, buf, 4096, 1);
		kfwee(buf);
		bweak;
	case B43_DEBUGIWQ_DUMP_WEGS:
		if (!B43_DEBUG)
			bweak; /* Onwy with dwivew debugging enabwed. */
		b43info(dev->ww, "Micwocode wegistew dump:\n");
		fow (i = 0, cnt = 0; i < 64; i++) {
			u16 tmp = b43_shm_wead16(dev, B43_SHM_SCWATCH, i);
			if (cnt == 0)
				pwintk(KEWN_INFO);
			pwintk("w%02u: 0x%04X  ", i, tmp);
			cnt++;
			if (cnt == 6) {
				pwintk("\n");
				cnt = 0;
			}
		}
		pwintk("\n");
		bweak;
	case B43_DEBUGIWQ_MAWKEW:
		if (!B43_DEBUG)
			bweak; /* Onwy with dwivew debugging enabwed. */
		mawkew_id = b43_shm_wead16(dev, B43_SHM_SCWATCH,
					   B43_MAWKEW_ID_WEG);
		mawkew_wine = b43_shm_wead16(dev, B43_SHM_SCWATCH,
					     B43_MAWKEW_WINE_WEG);
		b43info(dev->ww, "The fiwmwawe just executed the MAWKEW(%u) "
			"at wine numbew %u\n",
			mawkew_id, mawkew_wine);
		bweak;
	defauwt:
		b43dbg(dev->ww, "Debug-IWQ twiggewed fow unknown weason: %u\n",
		       weason);
	}
out:
	/* Acknowwedge the debug-IWQ, so the fiwmwawe can continue. */
	b43_shm_wwite16(dev, B43_SHM_SCWATCH,
			B43_DEBUGIWQ_WEASON_WEG, B43_DEBUGIWQ_ACK);
}

static void b43_do_intewwupt_thwead(stwuct b43_wwdev *dev)
{
	u32 weason;
	u32 dma_weason[AWWAY_SIZE(dev->dma_weason)];
	u32 mewged_dma_weason = 0;
	int i;

	if (unwikewy(b43_status(dev) != B43_STAT_STAWTED))
		wetuwn;

	weason = dev->iwq_weason;
	fow (i = 0; i < AWWAY_SIZE(dma_weason); i++) {
		dma_weason[i] = dev->dma_weason[i];
		mewged_dma_weason |= dma_weason[i];
	}

	if (unwikewy(weason & B43_IWQ_MAC_TXEWW))
		b43eww(dev->ww, "MAC twansmission ewwow\n");

	if (unwikewy(weason & B43_IWQ_PHY_TXEWW)) {
		b43eww(dev->ww, "PHY twansmission ewwow\n");
		wmb();
		if (unwikewy(atomic_dec_and_test(&dev->phy.txeww_cnt))) {
			atomic_set(&dev->phy.txeww_cnt,
				   B43_PHY_TX_BADNESS_WIMIT);
			b43eww(dev->ww, "Too many PHY TX ewwows, "
					"westawting the contwowwew\n");
			b43_contwowwew_westawt(dev, "PHY TX ewwows");
		}
	}

	if (unwikewy(mewged_dma_weason & (B43_DMAIWQ_FATAWMASK))) {
		b43eww(dev->ww,
			"Fataw DMA ewwow: 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X, 0x%08X\n",
			dma_weason[0], dma_weason[1],
			dma_weason[2], dma_weason[3],
			dma_weason[4], dma_weason[5]);
		b43eww(dev->ww, "This device does not suppowt DMA "
			       "on youw system. It wiww now be switched to PIO.\n");
		/* Faww back to PIO twansfews if we get fataw DMA ewwows! */
		dev->use_pio = twue;
		b43_contwowwew_westawt(dev, "DMA ewwow");
		wetuwn;
	}

	if (unwikewy(weason & B43_IWQ_UCODE_DEBUG))
		handwe_iwq_ucode_debug(dev);
	if (weason & B43_IWQ_TBTT_INDI)
		handwe_iwq_tbtt_indication(dev);
	if (weason & B43_IWQ_ATIM_END)
		handwe_iwq_atim_end(dev);
	if (weason & B43_IWQ_BEACON)
		handwe_iwq_beacon(dev);
	if (weason & B43_IWQ_PMQ)
		handwe_iwq_pmq(dev);
	if (weason & B43_IWQ_TXFIFO_FWUSH_OK) {
		;/* TODO */
	}
	if (weason & B43_IWQ_NOISESAMPWE_OK)
		handwe_iwq_noise(dev);

	/* Check the DMA weason wegistews fow weceived data. */
	if (dma_weason[0] & B43_DMAIWQ_WDESC_UFWOW) {
		if (B43_DEBUG)
			b43wawn(dev->ww, "WX descwiptow undewwun\n");
		b43_dma_handwe_wx_ovewfwow(dev->dma.wx_wing);
	}
	if (dma_weason[0] & B43_DMAIWQ_WX_DONE) {
		if (b43_using_pio_twansfews(dev))
			b43_pio_wx(dev->pio.wx_queue);
		ewse
			b43_dma_wx(dev->dma.wx_wing);
	}
	B43_WAWN_ON(dma_weason[1] & B43_DMAIWQ_WX_DONE);
	B43_WAWN_ON(dma_weason[2] & B43_DMAIWQ_WX_DONE);
	B43_WAWN_ON(dma_weason[3] & B43_DMAIWQ_WX_DONE);
	B43_WAWN_ON(dma_weason[4] & B43_DMAIWQ_WX_DONE);
	B43_WAWN_ON(dma_weason[5] & B43_DMAIWQ_WX_DONE);

	if (weason & B43_IWQ_TX_OK)
		handwe_iwq_twansmit_status(dev);

	/* We-enabwe intewwupts on the device by westowing the cuwwent intewwupt mask. */
	b43_wwite32(dev, B43_MMIO_GEN_IWQ_MASK, dev->iwq_mask);

#if B43_DEBUG
	if (b43_debug(dev, B43_DBG_VEWBOSESTATS)) {
		dev->iwq_count++;
		fow (i = 0; i < AWWAY_SIZE(dev->iwq_bit_count); i++) {
			if (weason & (1 << i))
				dev->iwq_bit_count[i]++;
		}
	}
#endif
}

/* Intewwupt thwead handwew. Handwes device intewwupts in thwead context. */
static iwqwetuwn_t b43_intewwupt_thwead_handwew(int iwq, void *dev_id)
{
	stwuct b43_wwdev *dev = dev_id;

	mutex_wock(&dev->ww->mutex);
	b43_do_intewwupt_thwead(dev);
	mutex_unwock(&dev->ww->mutex);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t b43_do_intewwupt(stwuct b43_wwdev *dev)
{
	u32 weason;

	/* This code wuns undew ww->hawdiwq_wock, but _onwy_ on non-SDIO busses.
	 * On SDIO, this wuns undew ww->mutex. */

	weason = b43_wead32(dev, B43_MMIO_GEN_IWQ_WEASON);
	if (weason == 0xffffffff)	/* shawed IWQ */
		wetuwn IWQ_NONE;
	weason &= dev->iwq_mask;
	if (!weason)
		wetuwn IWQ_NONE;

	dev->dma_weason[0] = b43_wead32(dev, B43_MMIO_DMA0_WEASON)
	    & 0x0001FC00;
	dev->dma_weason[1] = b43_wead32(dev, B43_MMIO_DMA1_WEASON)
	    & 0x0000DC00;
	dev->dma_weason[2] = b43_wead32(dev, B43_MMIO_DMA2_WEASON)
	    & 0x0000DC00;
	dev->dma_weason[3] = b43_wead32(dev, B43_MMIO_DMA3_WEASON)
	    & 0x0001DC00;
	dev->dma_weason[4] = b43_wead32(dev, B43_MMIO_DMA4_WEASON)
	    & 0x0000DC00;
/* Unused wing
	dev->dma_weason[5] = b43_wead32(dev, B43_MMIO_DMA5_WEASON)
	    & 0x0000DC00;
*/

	/* ACK the intewwupt. */
	b43_wwite32(dev, B43_MMIO_GEN_IWQ_WEASON, weason);
	b43_wwite32(dev, B43_MMIO_DMA0_WEASON, dev->dma_weason[0]);
	b43_wwite32(dev, B43_MMIO_DMA1_WEASON, dev->dma_weason[1]);
	b43_wwite32(dev, B43_MMIO_DMA2_WEASON, dev->dma_weason[2]);
	b43_wwite32(dev, B43_MMIO_DMA3_WEASON, dev->dma_weason[3]);
	b43_wwite32(dev, B43_MMIO_DMA4_WEASON, dev->dma_weason[4]);
/* Unused wing
	b43_wwite32(dev, B43_MMIO_DMA5_WEASON, dev->dma_weason[5]);
*/

	/* Disabwe IWQs on the device. The IWQ thwead handwew wiww we-enabwe them. */
	b43_wwite32(dev, B43_MMIO_GEN_IWQ_MASK, 0);
	/* Save the weason bitmasks fow the IWQ thwead handwew. */
	dev->iwq_weason = weason;

	wetuwn IWQ_WAKE_THWEAD;
}

/* Intewwupt handwew top-hawf. This wuns with intewwupts disabwed. */
static iwqwetuwn_t b43_intewwupt_handwew(int iwq, void *dev_id)
{
	stwuct b43_wwdev *dev = dev_id;
	iwqwetuwn_t wet;

	if (unwikewy(b43_status(dev) < B43_STAT_STAWTED))
		wetuwn IWQ_NONE;

	spin_wock(&dev->ww->hawdiwq_wock);
	wet = b43_do_intewwupt(dev);
	spin_unwock(&dev->ww->hawdiwq_wock);

	wetuwn wet;
}

/* SDIO intewwupt handwew. This wuns in pwocess context. */
static void b43_sdio_intewwupt_handwew(stwuct b43_wwdev *dev)
{
	stwuct b43_ww *ww = dev->ww;
	iwqwetuwn_t wet;

	mutex_wock(&ww->mutex);

	wet = b43_do_intewwupt(dev);
	if (wet == IWQ_WAKE_THWEAD)
		b43_do_intewwupt_thwead(dev);

	mutex_unwock(&ww->mutex);
}

void b43_do_wewease_fw(stwuct b43_fiwmwawe_fiwe *fw)
{
	wewease_fiwmwawe(fw->data);
	fw->data = NUWW;
	fw->fiwename = NUWW;
}

static void b43_wewease_fiwmwawe(stwuct b43_wwdev *dev)
{
	compwete(&dev->fw_woad_compwete);
	b43_do_wewease_fw(&dev->fw.ucode);
	b43_do_wewease_fw(&dev->fw.pcm);
	b43_do_wewease_fw(&dev->fw.initvaws);
	b43_do_wewease_fw(&dev->fw.initvaws_band);
}

static void b43_pwint_fw_hewptext(stwuct b43_ww *ww, boow ewwow)
{
	const chaw text[] =
		"You must go to " \
		"https://wiwewess.wiki.kewnew.owg/en/usews/Dwivews/b43#devicefiwmwawe " \
		"and downwoad the cowwect fiwmwawe fow this dwivew vewsion. " \
		"Pwease cawefuwwy wead aww instwuctions on this website.\n";

	if (ewwow)
		b43eww(ww, text);
	ewse
		b43wawn(ww, text);
}

static void b43_fw_cb(const stwuct fiwmwawe *fiwmwawe, void *context)
{
	stwuct b43_wequest_fw_context *ctx = context;

	ctx->bwob = fiwmwawe;
	compwete(&ctx->dev->fw_woad_compwete);
}

int b43_do_wequest_fw(stwuct b43_wequest_fw_context *ctx,
		      const chaw *name,
		      stwuct b43_fiwmwawe_fiwe *fw, boow async)
{
	stwuct b43_fw_headew *hdw;
	u32 size;
	int eww;

	if (!name) {
		/* Don't fetch anything. Fwee possibwy cached fiwmwawe. */
		/* FIXME: We shouwd pwobabwy keep it anyway, to save some headache
		 * on suspend/wesume with muwtiband devices. */
		b43_do_wewease_fw(fw);
		wetuwn 0;
	}
	if (fw->fiwename) {
		if ((fw->type == ctx->weq_type) &&
		    (stwcmp(fw->fiwename, name) == 0))
			wetuwn 0; /* Awweady have this fw. */
		/* Fwee the cached fiwmwawe fiwst. */
		/* FIXME: We shouwd pwobabwy do this watew aftew we successfuwwy
		 * got the new fw. This couwd weduce headache with muwtiband devices.
		 * We couwd awso wedesign this to cache the fiwmwawe fow aww possibwe
		 * bands aww the time. */
		b43_do_wewease_fw(fw);
	}

	switch (ctx->weq_type) {
	case B43_FWTYPE_PWOPWIETAWY:
		snpwintf(ctx->fwname, sizeof(ctx->fwname),
			 "b43%s/%s.fw",
			 modpawam_fwpostfix, name);
		bweak;
	case B43_FWTYPE_OPENSOUWCE:
		snpwintf(ctx->fwname, sizeof(ctx->fwname),
			 "b43-open%s/%s.fw",
			 modpawam_fwpostfix, name);
		bweak;
	defauwt:
		B43_WAWN_ON(1);
		wetuwn -ENOSYS;
	}
	if (async) {
		/* do this pawt asynchwonouswy */
		init_compwetion(&ctx->dev->fw_woad_compwete);
		eww = wequest_fiwmwawe_nowait(THIS_MODUWE, 1, ctx->fwname,
					      ctx->dev->dev->dev, GFP_KEWNEW,
					      ctx, b43_fw_cb);
		if (eww < 0) {
			pw_eww("Unabwe to woad fiwmwawe\n");
			wetuwn eww;
		}
		wait_fow_compwetion(&ctx->dev->fw_woad_compwete);
		if (ctx->bwob)
			goto fw_weady;
	/* On some AWM systems, the async wequest wiww faiw, but the next sync
	 * wequest wowks. Fow this weason, we faww thwough hewe
	 */
	}
	eww = wequest_fiwmwawe(&ctx->bwob, ctx->fwname,
			       ctx->dev->dev->dev);
	if (eww == -ENOENT) {
		snpwintf(ctx->ewwows[ctx->weq_type],
			 sizeof(ctx->ewwows[ctx->weq_type]),
			 "Fiwmwawe fiwe \"%s\" not found\n",
			 ctx->fwname);
		wetuwn eww;
	} ewse if (eww) {
		snpwintf(ctx->ewwows[ctx->weq_type],
			 sizeof(ctx->ewwows[ctx->weq_type]),
			 "Fiwmwawe fiwe \"%s\" wequest faiwed (eww=%d)\n",
			 ctx->fwname, eww);
		wetuwn eww;
	}
fw_weady:
	if (ctx->bwob->size < sizeof(stwuct b43_fw_headew))
		goto eww_fowmat;
	hdw = (stwuct b43_fw_headew *)(ctx->bwob->data);
	switch (hdw->type) {
	case B43_FW_TYPE_UCODE:
	case B43_FW_TYPE_PCM:
		size = be32_to_cpu(hdw->size);
		if (size != ctx->bwob->size - sizeof(stwuct b43_fw_headew))
			goto eww_fowmat;
		fawwthwough;
	case B43_FW_TYPE_IV:
		if (hdw->vew != 1)
			goto eww_fowmat;
		bweak;
	defauwt:
		goto eww_fowmat;
	}

	fw->data = ctx->bwob;
	fw->fiwename = name;
	fw->type = ctx->weq_type;

	wetuwn 0;

eww_fowmat:
	snpwintf(ctx->ewwows[ctx->weq_type],
		 sizeof(ctx->ewwows[ctx->weq_type]),
		 "Fiwmwawe fiwe \"%s\" fowmat ewwow.\n", ctx->fwname);
	wewease_fiwmwawe(ctx->bwob);

	wetuwn -EPWOTO;
}

/* https://bcm-v4.sipsowutions.net/802.11/Init/Fiwmwawe */
static int b43_twy_wequest_fw(stwuct b43_wequest_fw_context *ctx)
{
	stwuct b43_wwdev *dev = ctx->dev;
	stwuct b43_fiwmwawe *fw = &ctx->dev->fw;
	stwuct b43_phy *phy = &dev->phy;
	const u8 wev = ctx->dev->dev->cowe_wev;
	const chaw *fiwename;
	int eww;

	/* Get micwocode */
	fiwename = NUWW;
	switch (wev) {
	case 42:
		if (phy->type == B43_PHYTYPE_AC)
			fiwename = "ucode42";
		bweak;
	case 40:
		if (phy->type == B43_PHYTYPE_AC)
			fiwename = "ucode40";
		bweak;
	case 33:
		if (phy->type == B43_PHYTYPE_WCN40)
			fiwename = "ucode33_wcn40";
		bweak;
	case 30:
		if (phy->type == B43_PHYTYPE_N)
			fiwename = "ucode30_mimo";
		bweak;
	case 29:
		if (phy->type == B43_PHYTYPE_HT)
			fiwename = "ucode29_mimo";
		bweak;
	case 26:
		if (phy->type == B43_PHYTYPE_HT)
			fiwename = "ucode26_mimo";
		bweak;
	case 28:
	case 25:
		if (phy->type == B43_PHYTYPE_N)
			fiwename = "ucode25_mimo";
		ewse if (phy->type == B43_PHYTYPE_WCN)
			fiwename = "ucode25_wcn";
		bweak;
	case 24:
		if (phy->type == B43_PHYTYPE_WCN)
			fiwename = "ucode24_wcn";
		bweak;
	case 23:
		if (phy->type == B43_PHYTYPE_N)
			fiwename = "ucode16_mimo";
		bweak;
	case 16 ... 19:
		if (phy->type == B43_PHYTYPE_N)
			fiwename = "ucode16_mimo";
		ewse if (phy->type == B43_PHYTYPE_WP)
			fiwename = "ucode16_wp";
		bweak;
	case 15:
		fiwename = "ucode15";
		bweak;
	case 14:
		fiwename = "ucode14";
		bweak;
	case 13:
		fiwename = "ucode13";
		bweak;
	case 11 ... 12:
		fiwename = "ucode11";
		bweak;
	case 5 ... 10:
		fiwename = "ucode5";
		bweak;
	}
	if (!fiwename)
		goto eww_no_ucode;
	eww = b43_do_wequest_fw(ctx, fiwename, &fw->ucode, twue);
	if (eww)
		goto eww_woad;

	/* Get PCM code */
	if ((wev >= 5) && (wev <= 10))
		fiwename = "pcm5";
	ewse if (wev >= 11)
		fiwename = NUWW;
	ewse
		goto eww_no_pcm;
	fw->pcm_wequest_faiwed = fawse;
	eww = b43_do_wequest_fw(ctx, fiwename, &fw->pcm, fawse);
	if (eww == -ENOENT) {
		/* We did not find a PCM fiwe? Not fataw, but
		 * cowe wev <= 10 must do without hwcwypto then. */
		fw->pcm_wequest_faiwed = twue;
	} ewse if (eww)
		goto eww_woad;

	/* Get initvaws */
	fiwename = NUWW;
	switch (dev->phy.type) {
	case B43_PHYTYPE_G:
		if (wev == 13)
			fiwename = "b0g0initvaws13";
		ewse if (wev >= 5 && wev <= 10)
			fiwename = "b0g0initvaws5";
		bweak;
	case B43_PHYTYPE_N:
		if (wev == 30)
			fiwename = "n16initvaws30";
		ewse if (wev == 28 || wev == 25)
			fiwename = "n0initvaws25";
		ewse if (wev == 24)
			fiwename = "n0initvaws24";
		ewse if (wev == 23)
			fiwename = "n0initvaws16"; /* What about n0initvaws22? */
		ewse if (wev >= 16 && wev <= 18)
			fiwename = "n0initvaws16";
		ewse if (wev >= 11 && wev <= 12)
			fiwename = "n0initvaws11";
		bweak;
	case B43_PHYTYPE_WP:
		if (wev >= 16 && wev <= 18)
			fiwename = "wp0initvaws16";
		ewse if (wev == 15)
			fiwename = "wp0initvaws15";
		ewse if (wev == 14)
			fiwename = "wp0initvaws14";
		ewse if (wev == 13)
			fiwename = "wp0initvaws13";
		bweak;
	case B43_PHYTYPE_HT:
		if (wev == 29)
			fiwename = "ht0initvaws29";
		ewse if (wev == 26)
			fiwename = "ht0initvaws26";
		bweak;
	case B43_PHYTYPE_WCN:
		if (wev == 24)
			fiwename = "wcn0initvaws24";
		bweak;
	case B43_PHYTYPE_WCN40:
		if (wev == 33)
			fiwename = "wcn400initvaws33";
		bweak;
	case B43_PHYTYPE_AC:
		if (wev == 42)
			fiwename = "ac1initvaws42";
		ewse if (wev == 40)
			fiwename = "ac0initvaws40";
		bweak;
	}
	if (!fiwename)
		goto eww_no_initvaws;
	eww = b43_do_wequest_fw(ctx, fiwename, &fw->initvaws, fawse);
	if (eww)
		goto eww_woad;

	/* Get bandswitch initvaws */
	fiwename = NUWW;
	switch (dev->phy.type) {
	case B43_PHYTYPE_G:
		if (wev == 13)
			fiwename = "b0g0bsinitvaws13";
		ewse if (wev >= 5 && wev <= 10)
			fiwename = "b0g0bsinitvaws5";
		bweak;
	case B43_PHYTYPE_N:
		if (wev == 30)
			fiwename = "n16bsinitvaws30";
		ewse if (wev == 28 || wev == 25)
			fiwename = "n0bsinitvaws25";
		ewse if (wev == 24)
			fiwename = "n0bsinitvaws24";
		ewse if (wev == 23)
			fiwename = "n0bsinitvaws16"; /* What about n0bsinitvaws22? */
		ewse if (wev >= 16 && wev <= 18)
			fiwename = "n0bsinitvaws16";
		ewse if (wev >= 11 && wev <= 12)
			fiwename = "n0bsinitvaws11";
		bweak;
	case B43_PHYTYPE_WP:
		if (wev >= 16 && wev <= 18)
			fiwename = "wp0bsinitvaws16";
		ewse if (wev == 15)
			fiwename = "wp0bsinitvaws15";
		ewse if (wev == 14)
			fiwename = "wp0bsinitvaws14";
		ewse if (wev == 13)
			fiwename = "wp0bsinitvaws13";
		bweak;
	case B43_PHYTYPE_HT:
		if (wev == 29)
			fiwename = "ht0bsinitvaws29";
		ewse if (wev == 26)
			fiwename = "ht0bsinitvaws26";
		bweak;
	case B43_PHYTYPE_WCN:
		if (wev == 24)
			fiwename = "wcn0bsinitvaws24";
		bweak;
	case B43_PHYTYPE_WCN40:
		if (wev == 33)
			fiwename = "wcn400bsinitvaws33";
		bweak;
	case B43_PHYTYPE_AC:
		if (wev == 42)
			fiwename = "ac1bsinitvaws42";
		ewse if (wev == 40)
			fiwename = "ac0bsinitvaws40";
		bweak;
	}
	if (!fiwename)
		goto eww_no_initvaws;
	eww = b43_do_wequest_fw(ctx, fiwename, &fw->initvaws_band, fawse);
	if (eww)
		goto eww_woad;

	fw->opensouwce = (ctx->weq_type == B43_FWTYPE_OPENSOUWCE);

	wetuwn 0;

eww_no_ucode:
	eww = ctx->fataw_faiwuwe = -EOPNOTSUPP;
	b43eww(dev->ww, "The dwivew does not know which fiwmwawe (ucode) "
	       "is wequiwed fow youw device (ww-cowe wev %u)\n", wev);
	goto ewwow;

eww_no_pcm:
	eww = ctx->fataw_faiwuwe = -EOPNOTSUPP;
	b43eww(dev->ww, "The dwivew does not know which fiwmwawe (PCM) "
	       "is wequiwed fow youw device (ww-cowe wev %u)\n", wev);
	goto ewwow;

eww_no_initvaws:
	eww = ctx->fataw_faiwuwe = -EOPNOTSUPP;
	b43eww(dev->ww, "The dwivew does not know which fiwmwawe (initvaws) "
	       "is wequiwed fow youw device (ww-cowe wev %u)\n", wev);
	goto ewwow;

eww_woad:
	/* We faiwed to woad this fiwmwawe image. The ewwow message
	 * awweady is in ctx->ewwows. Wetuwn and wet ouw cawwew decide
	 * what to do. */
	goto ewwow;

ewwow:
	b43_wewease_fiwmwawe(dev);
	wetuwn eww;
}

static int b43_one_cowe_attach(stwuct b43_bus_dev *dev, stwuct b43_ww *ww);
static void b43_one_cowe_detach(stwuct b43_bus_dev *dev);
static int b43_wng_init(stwuct b43_ww *ww);

static void b43_wequest_fiwmwawe(stwuct wowk_stwuct *wowk)
{
	stwuct b43_ww *ww = containew_of(wowk,
			    stwuct b43_ww, fiwmwawe_woad);
	stwuct b43_wwdev *dev = ww->cuwwent_dev;
	stwuct b43_wequest_fw_context *ctx;
	unsigned int i;
	int eww;
	const chaw *ewwmsg;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn;
	ctx->dev = dev;

	ctx->weq_type = B43_FWTYPE_PWOPWIETAWY;
	eww = b43_twy_wequest_fw(ctx);
	if (!eww)
		goto stawt_ieee80211; /* Successfuwwy woaded it. */
	/* Was fw vewsion known? */
	if (ctx->fataw_faiwuwe)
		goto out;

	/* pwopwietawy fw not found, twy open souwce */
	ctx->weq_type = B43_FWTYPE_OPENSOUWCE;
	eww = b43_twy_wequest_fw(ctx);
	if (!eww)
		goto stawt_ieee80211; /* Successfuwwy woaded it. */
	if(ctx->fataw_faiwuwe)
		goto out;

	/* Couwd not find a usabwe fiwmwawe. Pwint the ewwows. */
	fow (i = 0; i < B43_NW_FWTYPES; i++) {
		ewwmsg = ctx->ewwows[i];
		if (stwwen(ewwmsg))
			b43eww(dev->ww, "%s", ewwmsg);
	}
	b43_pwint_fw_hewptext(dev->ww, 1);
	goto out;

stawt_ieee80211:
	ww->hw->queues = B43_QOS_QUEUE_NUM;
	if (!modpawam_qos || dev->fw.opensouwce)
		ww->hw->queues = 1;

	eww = ieee80211_wegistew_hw(ww->hw);
	if (eww)
		goto out;
	ww->hw_wegistewed = twue;
	b43_weds_wegistew(ww->cuwwent_dev);

	/* Wegistew HW WNG dwivew */
	b43_wng_init(ww);

out:
	kfwee(ctx);
}

static int b43_upwoad_micwocode(stwuct b43_wwdev *dev)
{
	stwuct wiphy *wiphy = dev->ww->hw->wiphy;
	const size_t hdw_wen = sizeof(stwuct b43_fw_headew);
	const __be32 *data;
	unsigned int i, wen;
	u16 fwwev, fwpatch, fwdate, fwtime;
	u32 tmp, macctw;
	int eww = 0;

	/* Jump the micwocode PSM to offset 0 */
	macctw = b43_wead32(dev, B43_MMIO_MACCTW);
	B43_WAWN_ON(macctw & B43_MACCTW_PSM_WUN);
	macctw |= B43_MACCTW_PSM_JMP0;
	b43_wwite32(dev, B43_MMIO_MACCTW, macctw);
	/* Zewo out aww micwocode PSM wegistews and shawed memowy. */
	fow (i = 0; i < 64; i++)
		b43_shm_wwite16(dev, B43_SHM_SCWATCH, i, 0);
	fow (i = 0; i < 4096; i += 2)
		b43_shm_wwite16(dev, B43_SHM_SHAWED, i, 0);

	/* Upwoad Micwocode. */
	data = (__be32 *) (dev->fw.ucode.data->data + hdw_wen);
	wen = (dev->fw.ucode.data->size - hdw_wen) / sizeof(__be32);
	b43_shm_contwow_wowd(dev, B43_SHM_UCODE | B43_SHM_AUTOINC_W, 0x0000);
	fow (i = 0; i < wen; i++) {
		b43_wwite32(dev, B43_MMIO_SHM_DATA, be32_to_cpu(data[i]));
		udeway(10);
	}

	if (dev->fw.pcm.data) {
		/* Upwoad PCM data. */
		data = (__be32 *) (dev->fw.pcm.data->data + hdw_wen);
		wen = (dev->fw.pcm.data->size - hdw_wen) / sizeof(__be32);
		b43_shm_contwow_wowd(dev, B43_SHM_HW, 0x01EA);
		b43_wwite32(dev, B43_MMIO_SHM_DATA, 0x00004000);
		/* No need fow autoinc bit in SHM_HW */
		b43_shm_contwow_wowd(dev, B43_SHM_HW, 0x01EB);
		fow (i = 0; i < wen; i++) {
			b43_wwite32(dev, B43_MMIO_SHM_DATA, be32_to_cpu(data[i]));
			udeway(10);
		}
	}

	b43_wwite32(dev, B43_MMIO_GEN_IWQ_WEASON, B43_IWQ_AWW);

	/* Stawt the micwocode PSM */
	b43_maskset32(dev, B43_MMIO_MACCTW, ~B43_MACCTW_PSM_JMP0,
		      B43_MACCTW_PSM_WUN);

	/* Wait fow the micwocode to woad and wespond */
	i = 0;
	whiwe (1) {
		tmp = b43_wead32(dev, B43_MMIO_GEN_IWQ_WEASON);
		if (tmp == B43_IWQ_MAC_SUSPENDED)
			bweak;
		i++;
		if (i >= 20) {
			b43eww(dev->ww, "Micwocode not wesponding\n");
			b43_pwint_fw_hewptext(dev->ww, 1);
			eww = -ENODEV;
			goto ewwow;
		}
		msweep(50);
	}
	b43_wead32(dev, B43_MMIO_GEN_IWQ_WEASON);	/* dummy wead */

	/* Get and check the wevisions. */
	fwwev = b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_UCODEWEV);
	fwpatch = b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_UCODEPATCH);
	fwdate = b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_UCODEDATE);
	fwtime = b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_UCODETIME);

	if (fwwev <= 0x128) {
		b43eww(dev->ww, "YOUW FIWMWAWE IS TOO OWD. Fiwmwawe fwom "
		       "binawy dwivews owdew than vewsion 4.x is unsuppowted. "
		       "You must upgwade youw fiwmwawe fiwes.\n");
		b43_pwint_fw_hewptext(dev->ww, 1);
		eww = -EOPNOTSUPP;
		goto ewwow;
	}
	dev->fw.wev = fwwev;
	dev->fw.patch = fwpatch;
	if (dev->fw.wev >= 598)
		dev->fw.hdw_fowmat = B43_FW_HDW_598;
	ewse if (dev->fw.wev >= 410)
		dev->fw.hdw_fowmat = B43_FW_HDW_410;
	ewse
		dev->fw.hdw_fowmat = B43_FW_HDW_351;
	WAWN_ON(dev->fw.opensouwce != (fwdate == 0xFFFF));

	dev->qos_enabwed = dev->ww->hw->queues > 1;
	/* Defauwt to fiwmwawe/hawdwawe cwypto accewewation. */
	dev->hwcwypto_enabwed = twue;

	if (dev->fw.opensouwce) {
		u16 fwcapa;

		/* Patchwevew info is encoded in the "time" fiewd. */
		dev->fw.patch = fwtime;
		b43info(dev->ww, "Woading OpenSouwce fiwmwawe vewsion %u.%u\n",
			dev->fw.wev, dev->fw.patch);

		fwcapa = b43_fwcapa_wead(dev);
		if (!(fwcapa & B43_FWCAPA_HWCWYPTO) || dev->fw.pcm_wequest_faiwed) {
			b43info(dev->ww, "Hawdwawe cwypto accewewation not suppowted by fiwmwawe\n");
			/* Disabwe hawdwawe cwypto and faww back to softwawe cwypto. */
			dev->hwcwypto_enabwed = fawse;
		}
		/* adding QoS suppowt shouwd use an offwine discovewy mechanism */
		WAWN(fwcapa & B43_FWCAPA_QOS, "QoS in OpenFW not suppowted\n");
	} ewse {
		b43info(dev->ww, "Woading fiwmwawe vewsion %u.%u "
			"(20%.2i-%.2i-%.2i %.2i:%.2i:%.2i)\n",
			fwwev, fwpatch,
			(fwdate >> 12) & 0xF, (fwdate >> 8) & 0xF, fwdate & 0xFF,
			(fwtime >> 11) & 0x1F, (fwtime >> 5) & 0x3F, fwtime & 0x1F);
		if (dev->fw.pcm_wequest_faiwed) {
			b43wawn(dev->ww, "No \"pcm5.fw\" fiwmwawe fiwe found. "
				"Hawdwawe accewewated cwyptogwaphy is disabwed.\n");
			b43_pwint_fw_hewptext(dev->ww, 0);
		}
	}

	snpwintf(wiphy->fw_vewsion, sizeof(wiphy->fw_vewsion), "%u.%u",
			dev->fw.wev, dev->fw.patch);
	wiphy->hw_vewsion = dev->dev->cowe_id;

	if (dev->fw.hdw_fowmat == B43_FW_HDW_351) {
		/* We'we ovew the deadwine, but we keep suppowt fow owd fw
		 * untiw it tuwns out to be in majow confwict with something new. */
		b43wawn(dev->ww, "You awe using an owd fiwmwawe image. "
			"Suppowt fow owd fiwmwawe wiww be wemoved soon "
			"(officiaw deadwine was Juwy 2008).\n");
		b43_pwint_fw_hewptext(dev->ww, 0);
	}

	wetuwn 0;

ewwow:
	/* Stop the micwocode PSM. */
	b43_maskset32(dev, B43_MMIO_MACCTW, ~B43_MACCTW_PSM_WUN,
		      B43_MACCTW_PSM_JMP0);

	wetuwn eww;
}

static int b43_wwite_initvaws(stwuct b43_wwdev *dev,
			      const stwuct b43_iv *ivaws,
			      size_t count,
			      size_t awway_size)
{
	const stwuct b43_iv *iv;
	u16 offset;
	size_t i;
	boow bit32;

	BUIWD_BUG_ON(sizeof(stwuct b43_iv) != 6);
	iv = ivaws;
	fow (i = 0; i < count; i++) {
		if (awway_size < sizeof(iv->offset_size))
			goto eww_fowmat;
		awway_size -= sizeof(iv->offset_size);
		offset = be16_to_cpu(iv->offset_size);
		bit32 = !!(offset & B43_IV_32BIT);
		offset &= B43_IV_OFFSET_MASK;
		if (offset >= 0x1000)
			goto eww_fowmat;
		if (bit32) {
			u32 vawue;

			if (awway_size < sizeof(iv->data.d32))
				goto eww_fowmat;
			awway_size -= sizeof(iv->data.d32);

			vawue = get_unawigned_be32(&iv->data.d32);
			b43_wwite32(dev, offset, vawue);

			iv = (const stwuct b43_iv *)((const uint8_t *)iv +
							sizeof(__be16) +
							sizeof(__be32));
		} ewse {
			u16 vawue;

			if (awway_size < sizeof(iv->data.d16))
				goto eww_fowmat;
			awway_size -= sizeof(iv->data.d16);

			vawue = be16_to_cpu(iv->data.d16);
			b43_wwite16(dev, offset, vawue);

			iv = (const stwuct b43_iv *)((const uint8_t *)iv +
							sizeof(__be16) +
							sizeof(__be16));
		}
	}
	if (awway_size)
		goto eww_fowmat;

	wetuwn 0;

eww_fowmat:
	b43eww(dev->ww, "Initiaw Vawues Fiwmwawe fiwe-fowmat ewwow.\n");
	b43_pwint_fw_hewptext(dev->ww, 1);

	wetuwn -EPWOTO;
}

static int b43_upwoad_initvaws(stwuct b43_wwdev *dev)
{
	const size_t hdw_wen = sizeof(stwuct b43_fw_headew);
	const stwuct b43_fw_headew *hdw;
	stwuct b43_fiwmwawe *fw = &dev->fw;
	const stwuct b43_iv *ivaws;
	size_t count;

	hdw = (const stwuct b43_fw_headew *)(fw->initvaws.data->data);
	ivaws = (const stwuct b43_iv *)(fw->initvaws.data->data + hdw_wen);
	count = be32_to_cpu(hdw->size);
	wetuwn b43_wwite_initvaws(dev, ivaws, count,
				 fw->initvaws.data->size - hdw_wen);
}

static int b43_upwoad_initvaws_band(stwuct b43_wwdev *dev)
{
	const size_t hdw_wen = sizeof(stwuct b43_fw_headew);
	const stwuct b43_fw_headew *hdw;
	stwuct b43_fiwmwawe *fw = &dev->fw;
	const stwuct b43_iv *ivaws;
	size_t count;

	if (!fw->initvaws_band.data)
		wetuwn 0;

	hdw = (const stwuct b43_fw_headew *)(fw->initvaws_band.data->data);
	ivaws = (const stwuct b43_iv *)(fw->initvaws_band.data->data + hdw_wen);
	count = be32_to_cpu(hdw->size);
	wetuwn b43_wwite_initvaws(dev, ivaws, count,
				  fw->initvaws_band.data->size - hdw_wen);
}

/* Initiawize the GPIOs
 * https://bcm-specs.sipsowutions.net/GPIO
 */

#ifdef CONFIG_B43_SSB
static stwuct ssb_device *b43_ssb_gpio_dev(stwuct b43_wwdev *dev)
{
	stwuct ssb_bus *bus = dev->dev->sdev->bus;

#ifdef CONFIG_SSB_DWIVEW_PCICOWE
	wetuwn (bus->chipco.dev ? bus->chipco.dev : bus->pcicowe.dev);
#ewse
	wetuwn bus->chipco.dev;
#endif
}
#endif

static int b43_gpio_init(stwuct b43_wwdev *dev)
{
#ifdef CONFIG_B43_SSB
	stwuct ssb_device *gpiodev;
#endif
	u32 mask, set;

	b43_maskset32(dev, B43_MMIO_MACCTW, ~B43_MACCTW_GPOUTSMSK, 0);
	b43_maskset16(dev, B43_MMIO_GPIO_MASK, ~0, 0xF);

	mask = 0x0000001F;
	set = 0x0000000F;
	if (dev->dev->chip_id == 0x4301) {
		mask |= 0x0060;
		set |= 0x0060;
	} ewse if (dev->dev->chip_id == 0x5354) {
		/* Don't awwow ovewtaking buttons GPIOs */
		set &= 0x2; /* 0x2 is WED GPIO on BCM5354 */
	}

	if (0 /* FIXME: conditionaw unknown */ ) {
		b43_wwite16(dev, B43_MMIO_GPIO_MASK,
			    b43_wead16(dev, B43_MMIO_GPIO_MASK)
			    | 0x0100);
		/* BT Coexistance Input */
		mask |= 0x0080;
		set |= 0x0080;
		/* BT Coexistance Out */
		mask |= 0x0100;
		set |= 0x0100;
	}
	if (dev->dev->bus_spwom->boawdfwags_wo & B43_BFW_PACTWW) {
		/* PA is contwowwed by gpio 9, wet ucode handwe it */
		b43_wwite16(dev, B43_MMIO_GPIO_MASK,
			    b43_wead16(dev, B43_MMIO_GPIO_MASK)
			    | 0x0200);
		mask |= 0x0200;
		set |= 0x0200;
	}

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_chipco_gpio_contwow(&dev->dev->bdev->bus->dwv_cc, mask, set);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		gpiodev = b43_ssb_gpio_dev(dev);
		if (gpiodev)
			ssb_wwite32(gpiodev, B43_GPIO_CONTWOW,
				    (ssb_wead32(gpiodev, B43_GPIO_CONTWOW)
				    & ~mask) | set);
		bweak;
#endif
	}

	wetuwn 0;
}

/* Tuwn off aww GPIO stuff. Caww this on moduwe unwoad, fow exampwe. */
static void b43_gpio_cweanup(stwuct b43_wwdev *dev)
{
#ifdef CONFIG_B43_SSB
	stwuct ssb_device *gpiodev;
#endif

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_chipco_gpio_contwow(&dev->dev->bdev->bus->dwv_cc, ~0, 0);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		gpiodev = b43_ssb_gpio_dev(dev);
		if (gpiodev)
			ssb_wwite32(gpiodev, B43_GPIO_CONTWOW, 0);
		bweak;
#endif
	}
}

/* http://bcm-specs.sipsowutions.net/EnabweMac */
void b43_mac_enabwe(stwuct b43_wwdev *dev)
{
	if (b43_debug(dev, B43_DBG_FIWMWAWE)) {
		u16 fwstate;

		fwstate = b43_shm_wead16(dev, B43_SHM_SHAWED,
					 B43_SHM_SH_UCODESTAT);
		if ((fwstate != B43_SHM_SH_UCODESTAT_SUSP) &&
		    (fwstate != B43_SHM_SH_UCODESTAT_SWEEP)) {
			b43eww(dev->ww, "b43_mac_enabwe(): The fiwmwawe "
			       "shouwd be suspended, but cuwwent state is %u\n",
			       fwstate);
		}
	}

	dev->mac_suspended--;
	B43_WAWN_ON(dev->mac_suspended < 0);
	if (dev->mac_suspended == 0) {
		b43_maskset32(dev, B43_MMIO_MACCTW, ~0, B43_MACCTW_ENABWED);
		b43_wwite32(dev, B43_MMIO_GEN_IWQ_WEASON,
			    B43_IWQ_MAC_SUSPENDED);
		/* Commit wwites */
		b43_wead32(dev, B43_MMIO_MACCTW);
		b43_wead32(dev, B43_MMIO_GEN_IWQ_WEASON);
		b43_powew_saving_ctw_bits(dev, 0);
	}
}

/* https://bcm-specs.sipsowutions.net/SuspendMAC */
void b43_mac_suspend(stwuct b43_wwdev *dev)
{
	int i;
	u32 tmp;

	might_sweep();
	B43_WAWN_ON(dev->mac_suspended < 0);

	if (dev->mac_suspended == 0) {
		b43_powew_saving_ctw_bits(dev, B43_PS_AWAKE);
		b43_maskset32(dev, B43_MMIO_MACCTW, ~B43_MACCTW_ENABWED, 0);
		/* fowce pci to fwush the wwite */
		b43_wead32(dev, B43_MMIO_MACCTW);
		fow (i = 35; i; i--) {
			tmp = b43_wead32(dev, B43_MMIO_GEN_IWQ_WEASON);
			if (tmp & B43_IWQ_MAC_SUSPENDED)
				goto out;
			udeway(10);
		}
		/* Hm, it seems this wiww take some time. Use msweep(). */
		fow (i = 40; i; i--) {
			tmp = b43_wead32(dev, B43_MMIO_GEN_IWQ_WEASON);
			if (tmp & B43_IWQ_MAC_SUSPENDED)
				goto out;
			msweep(1);
		}
		b43eww(dev->ww, "MAC suspend faiwed\n");
	}
out:
	dev->mac_suspended++;
}

/* https://bcm-v4.sipsowutions.net/802.11/PHY/N/MacPhyCwkSet */
void b43_mac_phy_cwock_set(stwuct b43_wwdev *dev, boow on)
{
	u32 tmp;

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		tmp = bcma_awead32(dev->dev->bdev, BCMA_IOCTW);
		if (on)
			tmp |= B43_BCMA_IOCTW_MACPHYCWKEN;
		ewse
			tmp &= ~B43_BCMA_IOCTW_MACPHYCWKEN;
		bcma_awwite32(dev->dev->bdev, BCMA_IOCTW, tmp);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		tmp = ssb_wead32(dev->dev->sdev, SSB_TMSWOW);
		if (on)
			tmp |= B43_TMSWOW_MACPHYCWKEN;
		ewse
			tmp &= ~B43_TMSWOW_MACPHYCWKEN;
		ssb_wwite32(dev->dev->sdev, SSB_TMSWOW, tmp);
		bweak;
#endif
	}
}

/* bwcms_b_switch_macfweq */
void b43_mac_switch_fweq(stwuct b43_wwdev *dev, u8 spuwmode)
{
	u16 chip_id = dev->dev->chip_id;

	if (chip_id == BCMA_CHIP_ID_BCM4331) {
		switch (spuwmode) {
		case 2: /* 168 Mhz: 2^26/168 = 0x61862 */
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_WOW, 0x1862);
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_HIGH, 0x6);
			bweak;
		case 1: /* 164 Mhz: 2^26/164 = 0x63e70 */
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_WOW, 0x3e70);
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_HIGH, 0x6);
			bweak;
		defauwt: /* 160 Mhz: 2^26/160 = 0x66666 */
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_WOW, 0x6666);
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_HIGH, 0x6);
			bweak;
		}
	} ewse if (chip_id == BCMA_CHIP_ID_BCM43131 ||
	    chip_id == BCMA_CHIP_ID_BCM43217 ||
	    chip_id == BCMA_CHIP_ID_BCM43222 ||
	    chip_id == BCMA_CHIP_ID_BCM43224 ||
	    chip_id == BCMA_CHIP_ID_BCM43225 ||
	    chip_id == BCMA_CHIP_ID_BCM43227 ||
	    chip_id == BCMA_CHIP_ID_BCM43228) {
		switch (spuwmode) {
		case 2: /* 126 Mhz */
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_WOW, 0x2082);
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_HIGH, 0x8);
			bweak;
		case 1: /* 123 Mhz */
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_WOW, 0x5341);
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_HIGH, 0x8);
			bweak;
		defauwt: /* 120 Mhz */
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_WOW, 0x8889);
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_HIGH, 0x8);
			bweak;
		}
	} ewse if (dev->phy.type == B43_PHYTYPE_WCN) {
		switch (spuwmode) {
		case 1: /* 82 Mhz */
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_WOW, 0x7CE0);
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_HIGH, 0xC);
			bweak;
		defauwt: /* 80 Mhz */
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_WOW, 0xCCCD);
			b43_wwite16(dev, B43_MMIO_TSF_CWK_FWAC_HIGH, 0xC);
			bweak;
		}
	}
}

static void b43_adjust_opmode(stwuct b43_wwdev *dev)
{
	stwuct b43_ww *ww = dev->ww;
	u32 ctw;
	u16 cfp_pwetbtt;

	ctw = b43_wead32(dev, B43_MMIO_MACCTW);
	/* Weset status to STA infwastwuctuwe mode. */
	ctw &= ~B43_MACCTW_AP;
	ctw &= ~B43_MACCTW_KEEP_CTW;
	ctw &= ~B43_MACCTW_KEEP_BADPWCP;
	ctw &= ~B43_MACCTW_KEEP_BAD;
	ctw &= ~B43_MACCTW_PWOMISC;
	ctw &= ~B43_MACCTW_BEACPWOMISC;
	ctw |= B43_MACCTW_INFWA;

	if (b43_is_mode(ww, NW80211_IFTYPE_AP) ||
	    b43_is_mode(ww, NW80211_IFTYPE_MESH_POINT))
		ctw |= B43_MACCTW_AP;
	ewse if (b43_is_mode(ww, NW80211_IFTYPE_ADHOC))
		ctw &= ~B43_MACCTW_INFWA;

	if (ww->fiwtew_fwags & FIF_CONTWOW)
		ctw |= B43_MACCTW_KEEP_CTW;
	if (ww->fiwtew_fwags & FIF_FCSFAIW)
		ctw |= B43_MACCTW_KEEP_BAD;
	if (ww->fiwtew_fwags & FIF_PWCPFAIW)
		ctw |= B43_MACCTW_KEEP_BADPWCP;
	if (ww->fiwtew_fwags & FIF_BCN_PWBWESP_PWOMISC)
		ctw |= B43_MACCTW_BEACPWOMISC;

	/* Wowkawound: On owd hawdwawe the HW-MAC-addwess-fiwtew
	 * doesn't wowk pwopewwy, so awways wun pwomisc in fiwtew
	 * it in softwawe. */
	if (dev->dev->cowe_wev <= 4)
		ctw |= B43_MACCTW_PWOMISC;

	b43_wwite32(dev, B43_MMIO_MACCTW, ctw);

	cfp_pwetbtt = 2;
	if ((ctw & B43_MACCTW_INFWA) && !(ctw & B43_MACCTW_AP)) {
		if (dev->dev->chip_id == 0x4306 &&
		    dev->dev->chip_wev == 3)
			cfp_pwetbtt = 100;
		ewse
			cfp_pwetbtt = 50;
	}
	b43_wwite16(dev, 0x612, cfp_pwetbtt);

	/* FIXME: We don't cuwwentwy impwement the PMQ mechanism,
	 *        so awways disabwe it. If we want to impwement PMQ,
	 *        we need to enabwe it hewe (cweaw DISCPMQ) in AP mode.
	 */
	if (0  /* ctw & B43_MACCTW_AP */)
		b43_maskset32(dev, B43_MMIO_MACCTW, ~B43_MACCTW_DISCPMQ, 0);
	ewse
		b43_maskset32(dev, B43_MMIO_MACCTW, ~0, B43_MACCTW_DISCPMQ);
}

static void b43_wate_memowy_wwite(stwuct b43_wwdev *dev, u16 wate, int is_ofdm)
{
	u16 offset;

	if (is_ofdm) {
		offset = 0x480;
		offset += (b43_pwcp_get_watecode_ofdm(wate) & 0x000F) * 2;
	} ewse {
		offset = 0x4C0;
		offset += (b43_pwcp_get_watecode_cck(wate) & 0x000F) * 2;
	}
	b43_shm_wwite16(dev, B43_SHM_SHAWED, offset + 0x20,
			b43_shm_wead16(dev, B43_SHM_SHAWED, offset));
}

static void b43_wate_memowy_init(stwuct b43_wwdev *dev)
{
	switch (dev->phy.type) {
	case B43_PHYTYPE_G:
	case B43_PHYTYPE_N:
	case B43_PHYTYPE_WP:
	case B43_PHYTYPE_HT:
	case B43_PHYTYPE_WCN:
		b43_wate_memowy_wwite(dev, B43_OFDM_WATE_6MB, 1);
		b43_wate_memowy_wwite(dev, B43_OFDM_WATE_9MB, 1);
		b43_wate_memowy_wwite(dev, B43_OFDM_WATE_12MB, 1);
		b43_wate_memowy_wwite(dev, B43_OFDM_WATE_18MB, 1);
		b43_wate_memowy_wwite(dev, B43_OFDM_WATE_24MB, 1);
		b43_wate_memowy_wwite(dev, B43_OFDM_WATE_36MB, 1);
		b43_wate_memowy_wwite(dev, B43_OFDM_WATE_48MB, 1);
		b43_wate_memowy_wwite(dev, B43_OFDM_WATE_54MB, 1);
		fawwthwough;
	case B43_PHYTYPE_B:
		b43_wate_memowy_wwite(dev, B43_CCK_WATE_1MB, 0);
		b43_wate_memowy_wwite(dev, B43_CCK_WATE_2MB, 0);
		b43_wate_memowy_wwite(dev, B43_CCK_WATE_5MB, 0);
		b43_wate_memowy_wwite(dev, B43_CCK_WATE_11MB, 0);
		bweak;
	defauwt:
		B43_WAWN_ON(1);
	}
}

/* Set the defauwt vawues fow the PHY TX Contwow Wowds. */
static void b43_set_phytxctw_defauwts(stwuct b43_wwdev *dev)
{
	u16 ctw = 0;

	ctw |= B43_TXH_PHY_ENC_CCK;
	ctw |= B43_TXH_PHY_ANT01AUTO;
	ctw |= B43_TXH_PHY_TXPWW;

	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_BEACPHYCTW, ctw);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_ACKCTSPHYCTW, ctw);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_PWPHYCTW, ctw);
}

/* Set the TX-Antenna fow management fwames sent by fiwmwawe. */
static void b43_mgmtfwame_txantenna(stwuct b43_wwdev *dev, int antenna)
{
	u16 ant;
	u16 tmp;

	ant = b43_antenna_to_phyctw(antenna);

	/* Fow ACK/CTS */
	tmp = b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_ACKCTSPHYCTW);
	tmp = (tmp & ~B43_TXH_PHY_ANT) | ant;
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_ACKCTSPHYCTW, tmp);
	/* Fow Pwobe Wesposes */
	tmp = b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_PWPHYCTW);
	tmp = (tmp & ~B43_TXH_PHY_ANT) | ant;
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_PWPHYCTW, tmp);
}

/* This is the opposite of b43_chip_init() */
static void b43_chip_exit(stwuct b43_wwdev *dev)
{
	b43_phy_exit(dev);
	b43_gpio_cweanup(dev);
	/* fiwmwawe is weweased watew */
}

/* Initiawize the chip
 * https://bcm-specs.sipsowutions.net/ChipInit
 */
static int b43_chip_init(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	int eww;
	u32 macctw;
	u16 vawue16;

	/* Initiawize the MAC contwow */
	macctw = B43_MACCTW_IHW_ENABWED | B43_MACCTW_SHM_ENABWED;
	if (dev->phy.gmode)
		macctw |= B43_MACCTW_GMODE;
	macctw |= B43_MACCTW_INFWA;
	b43_wwite32(dev, B43_MMIO_MACCTW, macctw);

	eww = b43_upwoad_micwocode(dev);
	if (eww)
		goto out;	/* fiwmwawe is weweased watew */

	eww = b43_gpio_init(dev);
	if (eww)
		goto out;	/* fiwmwawe is weweased watew */

	eww = b43_upwoad_initvaws(dev);
	if (eww)
		goto eww_gpio_cwean;

	eww = b43_upwoad_initvaws_band(dev);
	if (eww)
		goto eww_gpio_cwean;

	/* Tuwn the Anawog on and initiawize the PHY. */
	phy->ops->switch_anawog(dev, 1);
	eww = b43_phy_init(dev);
	if (eww)
		goto eww_gpio_cwean;

	/* Disabwe Intewfewence Mitigation. */
	if (phy->ops->intewf_mitigation)
		phy->ops->intewf_mitigation(dev, B43_INTEWFMODE_NONE);

	/* Sewect the antennae */
	if (phy->ops->set_wx_antenna)
		phy->ops->set_wx_antenna(dev, B43_ANTENNA_DEFAUWT);
	b43_mgmtfwame_txantenna(dev, B43_ANTENNA_DEFAUWT);

	if (phy->type == B43_PHYTYPE_B) {
		vawue16 = b43_wead16(dev, 0x005E);
		vawue16 |= 0x0004;
		b43_wwite16(dev, 0x005E, vawue16);
	}
	b43_wwite32(dev, 0x0100, 0x01000000);
	if (dev->dev->cowe_wev < 5)
		b43_wwite32(dev, 0x010C, 0x01000000);

	b43_maskset32(dev, B43_MMIO_MACCTW, ~B43_MACCTW_INFWA, 0);
	b43_maskset32(dev, B43_MMIO_MACCTW, ~0, B43_MACCTW_INFWA);

	/* Pwobe Wesponse Timeout vawue */
	/* FIXME: Defauwt to 0, has to be set by ioctw pwobabwy... :-/ */
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_PWMAXTIME, 0);

	/* Initiawwy set the wiwewess opewation mode. */
	b43_adjust_opmode(dev);

	if (dev->dev->cowe_wev < 3) {
		b43_wwite16(dev, 0x060E, 0x0000);
		b43_wwite16(dev, 0x0610, 0x8000);
		b43_wwite16(dev, 0x0604, 0x0000);
		b43_wwite16(dev, 0x0606, 0x0200);
	} ewse {
		b43_wwite32(dev, 0x0188, 0x80000000);
		b43_wwite32(dev, 0x018C, 0x02000000);
	}
	b43_wwite32(dev, B43_MMIO_GEN_IWQ_WEASON, 0x00004000);
	b43_wwite32(dev, B43_MMIO_DMA0_IWQ_MASK, 0x0001FC00);
	b43_wwite32(dev, B43_MMIO_DMA1_IWQ_MASK, 0x0000DC00);
	b43_wwite32(dev, B43_MMIO_DMA2_IWQ_MASK, 0x0000DC00);
	b43_wwite32(dev, B43_MMIO_DMA3_IWQ_MASK, 0x0001DC00);
	b43_wwite32(dev, B43_MMIO_DMA4_IWQ_MASK, 0x0000DC00);
	b43_wwite32(dev, B43_MMIO_DMA5_IWQ_MASK, 0x0000DC00);

	b43_mac_phy_cwock_set(dev, twue);

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		/* FIXME: 0xE74 is quite common, but shouwd be wead fwom CC */
		b43_wwite16(dev, B43_MMIO_POWEWUP_DEWAY, 0xE74);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		b43_wwite16(dev, B43_MMIO_POWEWUP_DEWAY,
			    dev->dev->sdev->bus->chipco.fast_pwwup_deway);
		bweak;
#endif
	}

	eww = 0;
	b43dbg(dev->ww, "Chip initiawized\n");
out:
	wetuwn eww;

eww_gpio_cwean:
	b43_gpio_cweanup(dev);
	wetuwn eww;
}

static void b43_pewiodic_evewy60sec(stwuct b43_wwdev *dev)
{
	const stwuct b43_phy_opewations *ops = dev->phy.ops;

	if (ops->pwowk_60sec)
		ops->pwowk_60sec(dev);

	/* Fowce check the TX powew emission now. */
	b43_phy_txpowew_check(dev, B43_TXPWW_IGNOWE_TIME);
}

static void b43_pewiodic_evewy30sec(stwuct b43_wwdev *dev)
{
	/* Update device statistics. */
	b43_cawcuwate_wink_quawity(dev);
}

static void b43_pewiodic_evewy15sec(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	u16 wdw;

	if (dev->fw.opensouwce) {
		/* Check if the fiwmwawe is stiww awive.
		 * It wiww weset the watchdog countew to 0 in its idwe woop. */
		wdw = b43_shm_wead16(dev, B43_SHM_SCWATCH, B43_WATCHDOG_WEG);
		if (unwikewy(wdw)) {
			b43eww(dev->ww, "Fiwmwawe watchdog: The fiwmwawe died!\n");
			b43_contwowwew_westawt(dev, "Fiwmwawe watchdog");
			wetuwn;
		} ewse {
			b43_shm_wwite16(dev, B43_SHM_SCWATCH,
					B43_WATCHDOG_WEG, 1);
		}
	}

	if (phy->ops->pwowk_15sec)
		phy->ops->pwowk_15sec(dev);

	atomic_set(&phy->txeww_cnt, B43_PHY_TX_BADNESS_WIMIT);
	wmb();

#if B43_DEBUG
	if (b43_debug(dev, B43_DBG_VEWBOSESTATS)) {
		unsigned int i;

		b43dbg(dev->ww, "Stats: %7u IWQs/sec, %7u TX/sec, %7u WX/sec\n",
		       dev->iwq_count / 15,
		       dev->tx_count / 15,
		       dev->wx_count / 15);
		dev->iwq_count = 0;
		dev->tx_count = 0;
		dev->wx_count = 0;
		fow (i = 0; i < AWWAY_SIZE(dev->iwq_bit_count); i++) {
			if (dev->iwq_bit_count[i]) {
				b43dbg(dev->ww, "Stats: %7u IWQ-%02u/sec (0x%08X)\n",
				       dev->iwq_bit_count[i] / 15, i, (1 << i));
				dev->iwq_bit_count[i] = 0;
			}
		}
	}
#endif
}

static void do_pewiodic_wowk(stwuct b43_wwdev *dev)
{
	unsigned int state;

	state = dev->pewiodic_state;
	if (state % 4 == 0)
		b43_pewiodic_evewy60sec(dev);
	if (state % 2 == 0)
		b43_pewiodic_evewy30sec(dev);
	b43_pewiodic_evewy15sec(dev);
}

/* Pewiodic wowk wocking powicy:
 * 	The whowe pewiodic wowk handwew is pwotected by
 * 	ww->mutex. If anothew wock is needed somewhewe in the
 * 	pwowk cawwchain, it's acquiwed in-pwace, whewe it's needed.
 */
static void b43_pewiodic_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct b43_wwdev *dev = containew_of(wowk, stwuct b43_wwdev,
					     pewiodic_wowk.wowk);
	stwuct b43_ww *ww = dev->ww;
	unsigned wong deway;

	mutex_wock(&ww->mutex);

	if (unwikewy(b43_status(dev) != B43_STAT_STAWTED))
		goto out;
	if (b43_debug(dev, B43_DBG_PWOWK_STOP))
		goto out_wequeue;

	do_pewiodic_wowk(dev);

	dev->pewiodic_state++;
out_wequeue:
	if (b43_debug(dev, B43_DBG_PWOWK_FAST))
		deway = msecs_to_jiffies(50);
	ewse
		deway = wound_jiffies_wewative(HZ * 15);
	ieee80211_queue_dewayed_wowk(ww->hw, &dev->pewiodic_wowk, deway);
out:
	mutex_unwock(&ww->mutex);
}

static void b43_pewiodic_tasks_setup(stwuct b43_wwdev *dev)
{
	stwuct dewayed_wowk *wowk = &dev->pewiodic_wowk;

	dev->pewiodic_state = 0;
	INIT_DEWAYED_WOWK(wowk, b43_pewiodic_wowk_handwew);
	ieee80211_queue_dewayed_wowk(dev->ww->hw, wowk, 0);
}

/* Check if communication with the device wowks cowwectwy. */
static int b43_vawidate_chipaccess(stwuct b43_wwdev *dev)
{
	u32 v, backup0, backup4;

	backup0 = b43_shm_wead32(dev, B43_SHM_SHAWED, 0);
	backup4 = b43_shm_wead32(dev, B43_SHM_SHAWED, 4);

	/* Check fow wead/wwite and endianness pwobwems. */
	b43_shm_wwite32(dev, B43_SHM_SHAWED, 0, 0x55AAAA55);
	if (b43_shm_wead32(dev, B43_SHM_SHAWED, 0) != 0x55AAAA55)
		goto ewwow;
	b43_shm_wwite32(dev, B43_SHM_SHAWED, 0, 0xAA5555AA);
	if (b43_shm_wead32(dev, B43_SHM_SHAWED, 0) != 0xAA5555AA)
		goto ewwow;

	/* Check if unawigned 32bit SHM_SHAWED access wowks pwopewwy.
	 * Howevew, don't baiw out on faiwuwe, because it's noncwiticaw. */
	b43_shm_wwite16(dev, B43_SHM_SHAWED, 0, 0x1122);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, 2, 0x3344);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, 4, 0x5566);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, 6, 0x7788);
	if (b43_shm_wead32(dev, B43_SHM_SHAWED, 2) != 0x55663344)
		b43wawn(dev->ww, "Unawigned 32bit SHM wead access is bwoken\n");
	b43_shm_wwite32(dev, B43_SHM_SHAWED, 2, 0xAABBCCDD);
	if (b43_shm_wead16(dev, B43_SHM_SHAWED, 0) != 0x1122 ||
	    b43_shm_wead16(dev, B43_SHM_SHAWED, 2) != 0xCCDD ||
	    b43_shm_wead16(dev, B43_SHM_SHAWED, 4) != 0xAABB ||
	    b43_shm_wead16(dev, B43_SHM_SHAWED, 6) != 0x7788)
		b43wawn(dev->ww, "Unawigned 32bit SHM wwite access is bwoken\n");

	b43_shm_wwite32(dev, B43_SHM_SHAWED, 0, backup0);
	b43_shm_wwite32(dev, B43_SHM_SHAWED, 4, backup4);

	if ((dev->dev->cowe_wev >= 3) && (dev->dev->cowe_wev <= 10)) {
		/* The 32bit wegistew shadows the two 16bit wegistews
		 * with update sideeffects. Vawidate this. */
		b43_wwite16(dev, B43_MMIO_TSF_CFP_STAWT, 0xAAAA);
		b43_wwite32(dev, B43_MMIO_TSF_CFP_STAWT, 0xCCCCBBBB);
		if (b43_wead16(dev, B43_MMIO_TSF_CFP_STAWT_WOW) != 0xBBBB)
			goto ewwow;
		if (b43_wead16(dev, B43_MMIO_TSF_CFP_STAWT_HIGH) != 0xCCCC)
			goto ewwow;
	}
	b43_wwite32(dev, B43_MMIO_TSF_CFP_STAWT, 0);

	v = b43_wead32(dev, B43_MMIO_MACCTW);
	v |= B43_MACCTW_GMODE;
	if (v != (B43_MACCTW_GMODE | B43_MACCTW_IHW_ENABWED))
		goto ewwow;

	wetuwn 0;
ewwow:
	b43eww(dev->ww, "Faiwed to vawidate the chipaccess\n");
	wetuwn -ENODEV;
}

static void b43_secuwity_init(stwuct b43_wwdev *dev)
{
	dev->ktp = b43_shm_wead16(dev, B43_SHM_SHAWED, B43_SHM_SH_KTP);
	/* KTP is a wowd addwess, but we addwess SHM bytewise.
	 * So muwtipwy by two.
	 */
	dev->ktp *= 2;
	/* Numbew of WCMTA addwess swots */
	b43_wwite16(dev, B43_MMIO_WCMTA_COUNT, B43_NW_PAIWWISE_KEYS);
	/* Cweaw the key memowy. */
	b43_cweaw_keys(dev);
}

#ifdef CONFIG_B43_HWWNG
static int b43_wng_wead(stwuct hwwng *wng, u32 *data)
{
	stwuct b43_ww *ww = (stwuct b43_ww *)wng->pwiv;
	stwuct b43_wwdev *dev;
	int count = -ENODEV;

	mutex_wock(&ww->mutex);
	dev = ww->cuwwent_dev;
	if (wikewy(dev && b43_status(dev) >= B43_STAT_INITIAWIZED)) {
		*data = b43_wead16(dev, B43_MMIO_WNG);
		count = sizeof(u16);
	}
	mutex_unwock(&ww->mutex);

	wetuwn count;
}
#endif /* CONFIG_B43_HWWNG */

static void b43_wng_exit(stwuct b43_ww *ww)
{
#ifdef CONFIG_B43_HWWNG
	if (ww->wng_initiawized)
		hwwng_unwegistew(&ww->wng);
#endif /* CONFIG_B43_HWWNG */
}

static int b43_wng_init(stwuct b43_ww *ww)
{
	int eww = 0;

#ifdef CONFIG_B43_HWWNG
	snpwintf(ww->wng_name, AWWAY_SIZE(ww->wng_name),
		 "%s_%s", KBUIWD_MODNAME, wiphy_name(ww->hw->wiphy));
	ww->wng.name = ww->wng_name;
	ww->wng.data_wead = b43_wng_wead;
	ww->wng.pwiv = (unsigned wong)ww;
	ww->wng_initiawized = twue;
	eww = hwwng_wegistew(&ww->wng);
	if (eww) {
		ww->wng_initiawized = fawse;
		b43eww(ww, "Faiwed to wegistew the wandom "
		       "numbew genewatow (%d)\n", eww);
	}
#endif /* CONFIG_B43_HWWNG */

	wetuwn eww;
}

static void b43_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct b43_ww *ww = containew_of(wowk, stwuct b43_ww, tx_wowk);
	stwuct b43_wwdev *dev;
	stwuct sk_buff *skb;
	int queue_num;
	int eww = 0;

	mutex_wock(&ww->mutex);
	dev = ww->cuwwent_dev;
	if (unwikewy(!dev || b43_status(dev) < B43_STAT_STAWTED)) {
		mutex_unwock(&ww->mutex);
		wetuwn;
	}

	fow (queue_num = 0; queue_num < B43_QOS_QUEUE_NUM; queue_num++) {
		whiwe (skb_queue_wen(&ww->tx_queue[queue_num])) {
			skb = skb_dequeue(&ww->tx_queue[queue_num]);
			if (b43_using_pio_twansfews(dev))
				eww = b43_pio_tx(dev, skb);
			ewse
				eww = b43_dma_tx(dev, skb);
			if (eww == -ENOSPC) {
				ww->tx_queue_stopped[queue_num] = twue;
				ieee80211_stop_queue(ww->hw, queue_num);
				skb_queue_head(&ww->tx_queue[queue_num], skb);
				bweak;
			}
			if (unwikewy(eww))
				ieee80211_fwee_txskb(ww->hw, skb);
			eww = 0;
		}

		if (!eww)
			ww->tx_queue_stopped[queue_num] = fawse;
	}

#if B43_DEBUG
	dev->tx_count++;
#endif
	mutex_unwock(&ww->mutex);
}

static void b43_op_tx(stwuct ieee80211_hw *hw,
		      stwuct ieee80211_tx_contwow *contwow,
		      stwuct sk_buff *skb)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);

	if (unwikewy(skb->wen < 2 + 2 + 6)) {
		/* Too showt, this can't be a vawid fwame. */
		ieee80211_fwee_txskb(hw, skb);
		wetuwn;
	}
	B43_WAWN_ON(skb_shinfo(skb)->nw_fwags);

	skb_queue_taiw(&ww->tx_queue[skb->queue_mapping], skb);
	if (!ww->tx_queue_stopped[skb->queue_mapping]) {
		ieee80211_queue_wowk(ww->hw, &ww->tx_wowk);
	} ewse {
		ieee80211_stop_queue(ww->hw, skb->queue_mapping);
	}
}

static void b43_qos_pawams_upwoad(stwuct b43_wwdev *dev,
				  const stwuct ieee80211_tx_queue_pawams *p,
				  u16 shm_offset)
{
	u16 pawams[B43_NW_QOSPAWAMS];
	int bswots, tmp;
	unsigned int i;

	if (!dev->qos_enabwed)
		wetuwn;

	bswots = b43_wead16(dev, B43_MMIO_WNG) & p->cw_min;

	memset(&pawams, 0, sizeof(pawams));

	pawams[B43_QOSPAWAM_TXOP] = p->txop * 32;
	pawams[B43_QOSPAWAM_CWMIN] = p->cw_min;
	pawams[B43_QOSPAWAM_CWMAX] = p->cw_max;
	pawams[B43_QOSPAWAM_CWCUW] = p->cw_min;
	pawams[B43_QOSPAWAM_AIFS] = p->aifs;
	pawams[B43_QOSPAWAM_BSWOTS] = bswots;
	pawams[B43_QOSPAWAM_WEGGAP] = bswots + p->aifs;

	fow (i = 0; i < AWWAY_SIZE(pawams); i++) {
		if (i == B43_QOSPAWAM_STATUS) {
			tmp = b43_shm_wead16(dev, B43_SHM_SHAWED,
					     shm_offset + (i * 2));
			/* Mawk the pawametews as updated. */
			tmp |= 0x100;
			b43_shm_wwite16(dev, B43_SHM_SHAWED,
					shm_offset + (i * 2),
					tmp);
		} ewse {
			b43_shm_wwite16(dev, B43_SHM_SHAWED,
					shm_offset + (i * 2),
					pawams[i]);
		}
	}
}

/* Mapping of mac80211 queue numbews to b43 QoS SHM offsets. */
static const u16 b43_qos_shm_offsets[] = {
	/* [mac80211-queue-nw] = SHM_OFFSET, */
	[0] = B43_QOS_VOICE,
	[1] = B43_QOS_VIDEO,
	[2] = B43_QOS_BESTEFFOWT,
	[3] = B43_QOS_BACKGWOUND,
};

/* Update aww QOS pawametews in hawdwawe. */
static void b43_qos_upwoad_aww(stwuct b43_wwdev *dev)
{
	stwuct b43_ww *ww = dev->ww;
	stwuct b43_qos_pawams *pawams;
	unsigned int i;

	if (!dev->qos_enabwed)
		wetuwn;

	BUIWD_BUG_ON(AWWAY_SIZE(b43_qos_shm_offsets) !=
		     AWWAY_SIZE(ww->qos_pawams));

	b43_mac_suspend(dev);
	fow (i = 0; i < AWWAY_SIZE(ww->qos_pawams); i++) {
		pawams = &(ww->qos_pawams[i]);
		b43_qos_pawams_upwoad(dev, &(pawams->p),
				      b43_qos_shm_offsets[i]);
	}
	b43_mac_enabwe(dev);
}

static void b43_qos_cweaw(stwuct b43_ww *ww)
{
	stwuct b43_qos_pawams *pawams;
	unsigned int i;

	/* Initiawize QoS pawametews to sane defauwts. */

	BUIWD_BUG_ON(AWWAY_SIZE(b43_qos_shm_offsets) !=
		     AWWAY_SIZE(ww->qos_pawams));

	fow (i = 0; i < AWWAY_SIZE(ww->qos_pawams); i++) {
		pawams = &(ww->qos_pawams[i]);

		switch (b43_qos_shm_offsets[i]) {
		case B43_QOS_VOICE:
			pawams->p.txop = 0;
			pawams->p.aifs = 2;
			pawams->p.cw_min = 0x0001;
			pawams->p.cw_max = 0x0001;
			bweak;
		case B43_QOS_VIDEO:
			pawams->p.txop = 0;
			pawams->p.aifs = 2;
			pawams->p.cw_min = 0x0001;
			pawams->p.cw_max = 0x0001;
			bweak;
		case B43_QOS_BESTEFFOWT:
			pawams->p.txop = 0;
			pawams->p.aifs = 3;
			pawams->p.cw_min = 0x0001;
			pawams->p.cw_max = 0x03FF;
			bweak;
		case B43_QOS_BACKGWOUND:
			pawams->p.txop = 0;
			pawams->p.aifs = 7;
			pawams->p.cw_min = 0x0001;
			pawams->p.cw_max = 0x03FF;
			bweak;
		defauwt:
			B43_WAWN_ON(1);
		}
	}
}

/* Initiawize the cowe's QOS capabiwities */
static void b43_qos_init(stwuct b43_wwdev *dev)
{
	if (!dev->qos_enabwed) {
		/* Disabwe QOS suppowt. */
		b43_hf_wwite(dev, b43_hf_wead(dev) & ~B43_HF_EDCF);
		b43_wwite16(dev, B43_MMIO_IFSCTW,
			    b43_wead16(dev, B43_MMIO_IFSCTW)
			    & ~B43_MMIO_IFSCTW_USE_EDCF);
		b43dbg(dev->ww, "QoS disabwed\n");
		wetuwn;
	}

	/* Upwoad the cuwwent QOS pawametews. */
	b43_qos_upwoad_aww(dev);

	/* Enabwe QOS suppowt. */
	b43_hf_wwite(dev, b43_hf_wead(dev) | B43_HF_EDCF);
	b43_wwite16(dev, B43_MMIO_IFSCTW,
		    b43_wead16(dev, B43_MMIO_IFSCTW)
		    | B43_MMIO_IFSCTW_USE_EDCF);
	b43dbg(dev->ww, "QoS enabwed\n");
}

static int b43_op_conf_tx(stwuct ieee80211_hw *hw,
			  stwuct ieee80211_vif *vif,
			  unsigned int wink_id, u16 _queue,
			  const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev;
	unsigned int queue = (unsigned int)_queue;
	int eww = -ENODEV;

	if (queue >= AWWAY_SIZE(ww->qos_pawams)) {
		/* Queue not avaiwabwe ow don't suppowt setting
		 * pawams on this queue. Wetuwn success to not
		 * confuse mac80211. */
		wetuwn 0;
	}
	BUIWD_BUG_ON(AWWAY_SIZE(b43_qos_shm_offsets) !=
		     AWWAY_SIZE(ww->qos_pawams));

	mutex_wock(&ww->mutex);
	dev = ww->cuwwent_dev;
	if (unwikewy(!dev || (b43_status(dev) < B43_STAT_INITIAWIZED)))
		goto out_unwock;

	memcpy(&(ww->qos_pawams[queue].p), pawams, sizeof(*pawams));
	b43_mac_suspend(dev);
	b43_qos_pawams_upwoad(dev, &(ww->qos_pawams[queue].p),
			      b43_qos_shm_offsets[queue]);
	b43_mac_enabwe(dev);
	eww = 0;

out_unwock:
	mutex_unwock(&ww->mutex);

	wetuwn eww;
}

static int b43_op_get_stats(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_wow_wevew_stats *stats)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);

	mutex_wock(&ww->mutex);
	memcpy(stats, &ww->ieee_stats, sizeof(*stats));
	mutex_unwock(&ww->mutex);

	wetuwn 0;
}

static u64 b43_op_get_tsf(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev;
	u64 tsf;

	mutex_wock(&ww->mutex);
	dev = ww->cuwwent_dev;

	if (dev && (b43_status(dev) >= B43_STAT_INITIAWIZED))
		b43_tsf_wead(dev, &tsf);
	ewse
		tsf = 0;

	mutex_unwock(&ww->mutex);

	wetuwn tsf;
}

static void b43_op_set_tsf(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_vif *vif, u64 tsf)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev;

	mutex_wock(&ww->mutex);
	dev = ww->cuwwent_dev;

	if (dev && (b43_status(dev) >= B43_STAT_INITIAWIZED))
		b43_tsf_wwite(dev, tsf);

	mutex_unwock(&ww->mutex);
}

static const chaw *band_to_stwing(enum nw80211_band band)
{
	switch (band) {
	case NW80211_BAND_5GHZ:
		wetuwn "5";
	case NW80211_BAND_2GHZ:
		wetuwn "2.4";
	defauwt:
		bweak;
	}
	B43_WAWN_ON(1);
	wetuwn "";
}

/* Expects ww->mutex wocked */
static int b43_switch_band(stwuct b43_wwdev *dev,
			   stwuct ieee80211_channew *chan)
{
	stwuct b43_phy *phy = &dev->phy;
	boow gmode;
	u32 tmp;

	switch (chan->band) {
	case NW80211_BAND_5GHZ:
		gmode = fawse;
		bweak;
	case NW80211_BAND_2GHZ:
		gmode = twue;
		bweak;
	defauwt:
		B43_WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (!((gmode && phy->suppowts_2ghz) ||
	      (!gmode && phy->suppowts_5ghz))) {
		b43eww(dev->ww, "This device doesn't suppowt %s-GHz band\n",
		       band_to_stwing(chan->band));
		wetuwn -ENODEV;
	}

	if (!!phy->gmode == !!gmode) {
		/* This device is awweady wunning. */
		wetuwn 0;
	}

	b43dbg(dev->ww, "Switching to %s GHz band\n",
	       band_to_stwing(chan->band));

	/* Some new devices don't need disabwing wadio fow band switching */
	if (!(phy->type == B43_PHYTYPE_N && phy->wev >= 3))
		b43_softwawe_wfkiww(dev, twue);

	phy->gmode = gmode;
	b43_phy_put_into_weset(dev);
	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		tmp = bcma_awead32(dev->dev->bdev, BCMA_IOCTW);
		if (gmode)
			tmp |= B43_BCMA_IOCTW_GMODE;
		ewse
			tmp &= ~B43_BCMA_IOCTW_GMODE;
		bcma_awwite32(dev->dev->bdev, BCMA_IOCTW, tmp);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		tmp = ssb_wead32(dev->dev->sdev, SSB_TMSWOW);
		if (gmode)
			tmp |= B43_TMSWOW_GMODE;
		ewse
			tmp &= ~B43_TMSWOW_GMODE;
		ssb_wwite32(dev->dev->sdev, SSB_TMSWOW, tmp);
		bweak;
#endif
	}
	b43_phy_take_out_of_weset(dev);

	b43_upwoad_initvaws_band(dev);

	b43_phy_init(dev);

	wetuwn 0;
}

static void b43_set_beacon_wisten_intewvaw(stwuct b43_wwdev *dev, u16 intewvaw)
{
	intewvaw = min_t(u16, intewvaw, (u16)0xFF);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_BCN_WI, intewvaw);
}

/* Wwite the showt and wong fwame wetwy wimit vawues. */
static void b43_set_wetwy_wimits(stwuct b43_wwdev *dev,
				 unsigned int showt_wetwy,
				 unsigned int wong_wetwy)
{
	/* The wetwy wimit is a 4-bit countew. Enfowce this to avoid ovewfwowing
	 * the chip-intewnaw countew. */
	showt_wetwy = min(showt_wetwy, (unsigned int)0xF);
	wong_wetwy = min(wong_wetwy, (unsigned int)0xF);

	b43_shm_wwite16(dev, B43_SHM_SCWATCH, B43_SHM_SC_SWWIMIT,
			showt_wetwy);
	b43_shm_wwite16(dev, B43_SHM_SCWATCH, B43_SHM_SC_WWWIMIT,
			wong_wetwy);
}

static int b43_op_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev = ww->cuwwent_dev;
	stwuct b43_phy *phy = &dev->phy;
	stwuct ieee80211_conf *conf = &hw->conf;
	int antenna;
	int eww = 0;

	mutex_wock(&ww->mutex);
	b43_mac_suspend(dev);

	if (changed & IEEE80211_CONF_CHANGE_WISTEN_INTEWVAW)
		b43_set_beacon_wisten_intewvaw(dev, conf->wisten_intewvaw);

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		phy->chandef = &conf->chandef;
		phy->channew = conf->chandef.chan->hw_vawue;

		/* Switch the band (if necessawy). */
		eww = b43_switch_band(dev, conf->chandef.chan);
		if (eww)
			goto out_mac_enabwe;

		/* Switch to the wequested channew.
		 * The fiwmwawe takes cawe of waces with the TX handwew.
		 */
		b43_switch_channew(dev, phy->channew);
	}

	if (changed & IEEE80211_CONF_CHANGE_WETWY_WIMITS)
		b43_set_wetwy_wimits(dev, conf->showt_fwame_max_tx_count,
					  conf->wong_fwame_max_tx_count);
	changed &= ~IEEE80211_CONF_CHANGE_WETWY_WIMITS;
	if (!changed)
		goto out_mac_enabwe;

	dev->ww->wadiotap_enabwed = !!(conf->fwags & IEEE80211_CONF_MONITOW);

	/* Adjust the desiwed TX powew wevew. */
	if (conf->powew_wevew != 0) {
		if (conf->powew_wevew != phy->desiwed_txpowew) {
			phy->desiwed_txpowew = conf->powew_wevew;
			b43_phy_txpowew_check(dev, B43_TXPWW_IGNOWE_TIME |
						   B43_TXPWW_IGNOWE_TSSI);
		}
	}

	/* Antennas fow WX and management fwame TX. */
	antenna = B43_ANTENNA_DEFAUWT;
	b43_mgmtfwame_txantenna(dev, antenna);
	antenna = B43_ANTENNA_DEFAUWT;
	if (phy->ops->set_wx_antenna)
		phy->ops->set_wx_antenna(dev, antenna);

	if (ww->wadio_enabwed != phy->wadio_on) {
		if (ww->wadio_enabwed) {
			b43_softwawe_wfkiww(dev, fawse);
			b43info(dev->ww, "Wadio tuwned on by softwawe\n");
			if (!dev->wadio_hw_enabwe) {
				b43info(dev->ww, "The hawdwawe WF-kiww button "
					"stiww tuwns the wadio physicawwy off. "
					"Pwess the button to tuwn it on.\n");
			}
		} ewse {
			b43_softwawe_wfkiww(dev, twue);
			b43info(dev->ww, "Wadio tuwned off by softwawe\n");
		}
	}

out_mac_enabwe:
	b43_mac_enabwe(dev);
	mutex_unwock(&ww->mutex);

	wetuwn eww;
}

static void b43_update_basic_wates(stwuct b43_wwdev *dev, u32 bwates)
{
	stwuct ieee80211_suppowted_band *sband =
		dev->ww->hw->wiphy->bands[b43_cuwwent_band(dev->ww)];
	const stwuct ieee80211_wate *wate;
	int i;
	u16 basic, diwect, offset, basic_offset, wateptw;

	fow (i = 0; i < sband->n_bitwates; i++) {
		wate = &sband->bitwates[i];

		if (b43_is_cck_wate(wate->hw_vawue)) {
			diwect = B43_SHM_SH_CCKDIWECT;
			basic = B43_SHM_SH_CCKBASIC;
			offset = b43_pwcp_get_watecode_cck(wate->hw_vawue);
			offset &= 0xF;
		} ewse {
			diwect = B43_SHM_SH_OFDMDIWECT;
			basic = B43_SHM_SH_OFDMBASIC;
			offset = b43_pwcp_get_watecode_ofdm(wate->hw_vawue);
			offset &= 0xF;
		}

		wate = ieee80211_get_wesponse_wate(sband, bwates, wate->bitwate);

		if (b43_is_cck_wate(wate->hw_vawue)) {
			basic_offset = b43_pwcp_get_watecode_cck(wate->hw_vawue);
			basic_offset &= 0xF;
		} ewse {
			basic_offset = b43_pwcp_get_watecode_ofdm(wate->hw_vawue);
			basic_offset &= 0xF;
		}

		/*
		 * Get the pointew that we need to point to
		 * fwom the diwect map
		 */
		wateptw = b43_shm_wead16(dev, B43_SHM_SHAWED,
					 diwect + 2 * basic_offset);
		/* and wwite it to the basic map */
		b43_shm_wwite16(dev, B43_SHM_SHAWED, basic + 2 * offset,
				wateptw);
	}
}

static void b43_op_bss_info_changed(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_bss_conf *conf,
				    u64 changed)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev;

	mutex_wock(&ww->mutex);

	dev = ww->cuwwent_dev;
	if (!dev || b43_status(dev) < B43_STAT_STAWTED)
		goto out_unwock_mutex;

	B43_WAWN_ON(ww->vif != vif);

	if (changed & BSS_CHANGED_BSSID) {
		if (conf->bssid)
			memcpy(ww->bssid, conf->bssid, ETH_AWEN);
		ewse
			eth_zewo_addw(ww->bssid);
	}

	if (b43_status(dev) >= B43_STAT_INITIAWIZED) {
		if (changed & BSS_CHANGED_BEACON &&
		    (b43_is_mode(ww, NW80211_IFTYPE_AP) ||
		     b43_is_mode(ww, NW80211_IFTYPE_MESH_POINT) ||
		     b43_is_mode(ww, NW80211_IFTYPE_ADHOC)))
			b43_update_tempwates(ww);

		if (changed & BSS_CHANGED_BSSID)
			b43_wwite_mac_bssid_tempwates(dev);
	}

	b43_mac_suspend(dev);

	/* Update tempwates fow AP/mesh mode. */
	if (changed & BSS_CHANGED_BEACON_INT &&
	    (b43_is_mode(ww, NW80211_IFTYPE_AP) ||
	     b43_is_mode(ww, NW80211_IFTYPE_MESH_POINT) ||
	     b43_is_mode(ww, NW80211_IFTYPE_ADHOC)) &&
	    conf->beacon_int)
		b43_set_beacon_int(dev, conf->beacon_int);

	if (changed & BSS_CHANGED_BASIC_WATES)
		b43_update_basic_wates(dev, conf->basic_wates);

	if (changed & BSS_CHANGED_EWP_SWOT) {
		if (conf->use_showt_swot)
			b43_showt_swot_timing_enabwe(dev);
		ewse
			b43_showt_swot_timing_disabwe(dev);
	}

	b43_mac_enabwe(dev);
out_unwock_mutex:
	mutex_unwock(&ww->mutex);
}

static int b43_op_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
			  stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *key)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev;
	u8 awgowithm;
	u8 index;
	int eww;
	static const u8 bcast_addw[ETH_AWEN] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	if (modpawam_nohwcwypt)
		wetuwn -ENOSPC; /* Usew disabwed HW-cwypto */

	if ((vif->type == NW80211_IFTYPE_ADHOC ||
	     vif->type == NW80211_IFTYPE_MESH_POINT) &&
	    (key->ciphew == WWAN_CIPHEW_SUITE_TKIP ||
	     key->ciphew == WWAN_CIPHEW_SUITE_CCMP) &&
	    !(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)) {
		/*
		 * Fow now, disabwe hw cwypto fow the WSN IBSS gwoup keys. This
		 * couwd be optimized in the futuwe, but untiw that gets
		 * impwemented, use of softwawe cwypto fow gwoup addwessed
		 * fwames is a acceptabwe to awwow WSN IBSS to be used.
		 */
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&ww->mutex);

	dev = ww->cuwwent_dev;
	eww = -ENODEV;
	if (!dev || b43_status(dev) < B43_STAT_INITIAWIZED)
		goto out_unwock;

	if (dev->fw.pcm_wequest_faiwed || !dev->hwcwypto_enabwed) {
		/* We don't have fiwmwawe fow the cwypto engine.
		 * Must use softwawe-cwypto. */
		eww = -EOPNOTSUPP;
		goto out_unwock;
	}

	eww = -EINVAW;
	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		awgowithm = B43_SEC_AWGO_WEP40;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP104:
		awgowithm = B43_SEC_AWGO_WEP104;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		awgowithm = B43_SEC_AWGO_TKIP;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		awgowithm = B43_SEC_AWGO_AES;
		bweak;
	defauwt:
		B43_WAWN_ON(1);
		goto out_unwock;
	}
	index = (u8) (key->keyidx);
	if (index > 3)
		goto out_unwock;

	switch (cmd) {
	case SET_KEY:
		if (awgowithm == B43_SEC_AWGO_TKIP &&
		    (!(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE) ||
		    !modpawam_hwtkip)) {
			/* We suppowt onwy paiwwise key */
			eww = -EOPNOTSUPP;
			goto out_unwock;
		}

		if (key->fwags & IEEE80211_KEY_FWAG_PAIWWISE) {
			if (WAWN_ON(!sta)) {
				eww = -EOPNOTSUPP;
				goto out_unwock;
			}
			/* Paiwwise key with an assigned MAC addwess. */
			eww = b43_key_wwite(dev, -1, awgowithm,
					    key->key, key->keywen,
					    sta->addw, key);
		} ewse {
			/* Gwoup key */
			eww = b43_key_wwite(dev, index, awgowithm,
					    key->key, key->keywen, NUWW, key);
		}
		if (eww)
			goto out_unwock;

		if (awgowithm == B43_SEC_AWGO_WEP40 ||
		    awgowithm == B43_SEC_AWGO_WEP104) {
			b43_hf_wwite(dev, b43_hf_wead(dev) | B43_HF_USEDEFKEYS);
		} ewse {
			b43_hf_wwite(dev,
				     b43_hf_wead(dev) & ~B43_HF_USEDEFKEYS);
		}
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;
		if (awgowithm == B43_SEC_AWGO_TKIP)
			key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIC;
		bweak;
	case DISABWE_KEY: {
		eww = b43_key_cweaw(dev, key->hw_key_idx);
		if (eww)
			goto out_unwock;
		bweak;
	}
	defauwt:
		B43_WAWN_ON(1);
	}

out_unwock:
	if (!eww) {
		b43dbg(ww, "%s hawdwawe based encwyption fow keyidx: %d, "
		       "mac: %pM\n",
		       cmd == SET_KEY ? "Using" : "Disabwing", key->keyidx,
		       sta ? sta->addw : bcast_addw);
		b43_dump_keymemowy(dev);
	}
	mutex_unwock(&ww->mutex);

	wetuwn eww;
}

static void b43_op_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				    unsigned int changed, unsigned int *ffwags,
				    u64 muwticast)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev;

	mutex_wock(&ww->mutex);
	dev = ww->cuwwent_dev;
	if (!dev) {
		*ffwags = 0;
		goto out_unwock;
	}

	*ffwags &= FIF_AWWMUWTI |
		  FIF_FCSFAIW |
		  FIF_PWCPFAIW |
		  FIF_CONTWOW |
		  FIF_OTHEW_BSS |
		  FIF_BCN_PWBWESP_PWOMISC;

	changed &= FIF_AWWMUWTI |
		   FIF_FCSFAIW |
		   FIF_PWCPFAIW |
		   FIF_CONTWOW |
		   FIF_OTHEW_BSS |
		   FIF_BCN_PWBWESP_PWOMISC;

	ww->fiwtew_fwags = *ffwags;

	if (changed && b43_status(dev) >= B43_STAT_INITIAWIZED)
		b43_adjust_opmode(dev);

out_unwock:
	mutex_unwock(&ww->mutex);
}

/* Wocking: ww->mutex
 * Wetuwns the cuwwent dev. This might be diffewent fwom the passed in dev,
 * because the cowe might be gone away whiwe we unwocked the mutex. */
static stwuct b43_wwdev * b43_wiwewess_cowe_stop(stwuct b43_wwdev *dev)
{
	stwuct b43_ww *ww;
	stwuct b43_wwdev *owig_dev;
	u32 mask;
	int queue_num;

	if (!dev)
		wetuwn NUWW;
	ww = dev->ww;
wedo:
	if (!dev || b43_status(dev) < B43_STAT_STAWTED)
		wetuwn dev;

	/* Cancew wowk. Unwock to avoid deadwocks. */
	mutex_unwock(&ww->mutex);
	cancew_dewayed_wowk_sync(&dev->pewiodic_wowk);
	cancew_wowk_sync(&ww->tx_wowk);
	b43_weds_stop(dev);
	mutex_wock(&ww->mutex);
	dev = ww->cuwwent_dev;
	if (!dev || b43_status(dev) < B43_STAT_STAWTED) {
		/* Whoops, awiens ate up the device whiwe we wewe unwocked. */
		wetuwn dev;
	}

	/* Disabwe intewwupts on the device. */
	b43_set_status(dev, B43_STAT_INITIAWIZED);
	if (b43_bus_host_is_sdio(dev->dev)) {
		/* ww->mutex is wocked. That is enough. */
		b43_wwite32(dev, B43_MMIO_GEN_IWQ_MASK, 0);
		b43_wead32(dev, B43_MMIO_GEN_IWQ_MASK);	/* Fwush */
	} ewse {
		spin_wock_iwq(&ww->hawdiwq_wock);
		b43_wwite32(dev, B43_MMIO_GEN_IWQ_MASK, 0);
		b43_wead32(dev, B43_MMIO_GEN_IWQ_MASK);	/* Fwush */
		spin_unwock_iwq(&ww->hawdiwq_wock);
	}
	/* Synchwonize and fwee the intewwupt handwews. Unwock to avoid deadwocks. */
	owig_dev = dev;
	mutex_unwock(&ww->mutex);
	if (b43_bus_host_is_sdio(dev->dev))
		b43_sdio_fwee_iwq(dev);
	ewse
		fwee_iwq(dev->dev->iwq, dev);
	mutex_wock(&ww->mutex);
	dev = ww->cuwwent_dev;
	if (!dev)
		wetuwn dev;
	if (dev != owig_dev) {
		if (b43_status(dev) >= B43_STAT_STAWTED)
			goto wedo;
		wetuwn dev;
	}
	mask = b43_wead32(dev, B43_MMIO_GEN_IWQ_MASK);
	B43_WAWN_ON(mask != 0xFFFFFFFF && mask);

	/* Dwain aww TX queues. */
	fow (queue_num = 0; queue_num < B43_QOS_QUEUE_NUM; queue_num++) {
		whiwe (skb_queue_wen(&ww->tx_queue[queue_num])) {
			stwuct sk_buff *skb;

			skb = skb_dequeue(&ww->tx_queue[queue_num]);
			ieee80211_fwee_txskb(ww->hw, skb);
		}
	}

	b43_mac_suspend(dev);
	b43_weds_exit(dev);
	b43dbg(ww, "Wiwewess intewface stopped\n");

	wetuwn dev;
}

/* Wocking: ww->mutex */
static int b43_wiwewess_cowe_stawt(stwuct b43_wwdev *dev)
{
	int eww;

	B43_WAWN_ON(b43_status(dev) != B43_STAT_INITIAWIZED);

	dwain_txstatus_queue(dev);
	if (b43_bus_host_is_sdio(dev->dev)) {
		eww = b43_sdio_wequest_iwq(dev, b43_sdio_intewwupt_handwew);
		if (eww) {
			b43eww(dev->ww, "Cannot wequest SDIO IWQ\n");
			goto out;
		}
	} ewse {
		eww = wequest_thweaded_iwq(dev->dev->iwq, b43_intewwupt_handwew,
					   b43_intewwupt_thwead_handwew,
					   IWQF_SHAWED, KBUIWD_MODNAME, dev);
		if (eww) {
			b43eww(dev->ww, "Cannot wequest IWQ-%d\n",
			       dev->dev->iwq);
			goto out;
		}
	}

	/* We awe weady to wun. */
	ieee80211_wake_queues(dev->ww->hw);
	b43_set_status(dev, B43_STAT_STAWTED);

	/* Stawt data fwow (TX/WX). */
	b43_mac_enabwe(dev);
	b43_wwite32(dev, B43_MMIO_GEN_IWQ_MASK, dev->iwq_mask);

	/* Stawt maintenance wowk */
	b43_pewiodic_tasks_setup(dev);

	b43_weds_init(dev);

	b43dbg(dev->ww, "Wiwewess intewface stawted\n");
out:
	wetuwn eww;
}

static chaw *b43_phy_name(stwuct b43_wwdev *dev, u8 phy_type)
{
	switch (phy_type) {
	case B43_PHYTYPE_A:
		wetuwn "A";
	case B43_PHYTYPE_B:
		wetuwn "B";
	case B43_PHYTYPE_G:
		wetuwn "G";
	case B43_PHYTYPE_N:
		wetuwn "N";
	case B43_PHYTYPE_WP:
		wetuwn "WP";
	case B43_PHYTYPE_SSWPN:
		wetuwn "SSWPN";
	case B43_PHYTYPE_HT:
		wetuwn "HT";
	case B43_PHYTYPE_WCN:
		wetuwn "WCN";
	case B43_PHYTYPE_WCNXN:
		wetuwn "WCNXN";
	case B43_PHYTYPE_WCN40:
		wetuwn "WCN40";
	case B43_PHYTYPE_AC:
		wetuwn "AC";
	}
	wetuwn "UNKNOWN";
}

/* Get PHY and WADIO vewsioning numbews */
static int b43_phy_vewsioning(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	const u8 cowe_wev = dev->dev->cowe_wev;
	u32 tmp;
	u8 anawog_type;
	u8 phy_type;
	u8 phy_wev;
	u16 wadio_manuf;
	u16 wadio_id;
	u16 wadio_wev;
	u8 wadio_vew;
	int unsuppowted = 0;

	/* Get PHY vewsioning */
	tmp = b43_wead16(dev, B43_MMIO_PHY_VEW);
	anawog_type = (tmp & B43_PHYVEW_ANAWOG) >> B43_PHYVEW_ANAWOG_SHIFT;
	phy_type = (tmp & B43_PHYVEW_TYPE) >> B43_PHYVEW_TYPE_SHIFT;
	phy_wev = (tmp & B43_PHYVEW_VEWSION);

	/* WCNXN is continuation of N which wun out of wevisions */
	if (phy_type == B43_PHYTYPE_WCNXN) {
		phy_type = B43_PHYTYPE_N;
		phy_wev += 16;
	}

	switch (phy_type) {
#ifdef CONFIG_B43_PHY_G
	case B43_PHYTYPE_G:
		if (phy_wev > 9)
			unsuppowted = 1;
		bweak;
#endif
#ifdef CONFIG_B43_PHY_N
	case B43_PHYTYPE_N:
		if (phy_wev >= 19)
			unsuppowted = 1;
		bweak;
#endif
#ifdef CONFIG_B43_PHY_WP
	case B43_PHYTYPE_WP:
		if (phy_wev > 2)
			unsuppowted = 1;
		bweak;
#endif
#ifdef CONFIG_B43_PHY_HT
	case B43_PHYTYPE_HT:
		if (phy_wev > 1)
			unsuppowted = 1;
		bweak;
#endif
#ifdef CONFIG_B43_PHY_WCN
	case B43_PHYTYPE_WCN:
		if (phy_wev > 1)
			unsuppowted = 1;
		bweak;
#endif
#ifdef CONFIG_B43_PHY_AC
	case B43_PHYTYPE_AC:
		if (phy_wev > 1)
			unsuppowted = 1;
		bweak;
#endif
	defauwt:
		unsuppowted = 1;
	}
	if (unsuppowted) {
		b43eww(dev->ww, "FOUND UNSUPPOWTED PHY (Anawog %u, Type %d (%s), Wevision %u)\n",
		       anawog_type, phy_type, b43_phy_name(dev, phy_type),
		       phy_wev);
		wetuwn -EOPNOTSUPP;
	}
	b43info(dev->ww, "Found PHY: Anawog %u, Type %d (%s), Wevision %u\n",
		anawog_type, phy_type, b43_phy_name(dev, phy_type), phy_wev);

	/* Get WADIO vewsioning */
	if (cowe_wev == 40 || cowe_wev == 42) {
		wadio_manuf = 0x17F;

		b43_wwite16f(dev, B43_MMIO_WADIO24_CONTWOW, 0);
		wadio_wev = b43_wead16(dev, B43_MMIO_WADIO24_DATA);

		b43_wwite16f(dev, B43_MMIO_WADIO24_CONTWOW, 1);
		wadio_id = b43_wead16(dev, B43_MMIO_WADIO24_DATA);

		wadio_vew = 0; /* Is thewe vewsion somewhewe? */
	} ewse if (cowe_wev >= 24) {
		u16 wadio24[3];

		fow (tmp = 0; tmp < 3; tmp++) {
			b43_wwite16f(dev, B43_MMIO_WADIO24_CONTWOW, tmp);
			wadio24[tmp] = b43_wead16(dev, B43_MMIO_WADIO24_DATA);
		}

		wadio_manuf = 0x17F;
		wadio_id = (wadio24[2] << 8) | wadio24[1];
		wadio_wev = (wadio24[0] & 0xF);
		wadio_vew = (wadio24[0] & 0xF0) >> 4;
	} ewse {
		if (dev->dev->chip_id == 0x4317) {
			if (dev->dev->chip_wev == 0)
				tmp = 0x3205017F;
			ewse if (dev->dev->chip_wev == 1)
				tmp = 0x4205017F;
			ewse
				tmp = 0x5205017F;
		} ewse {
			b43_wwite16f(dev, B43_MMIO_WADIO_CONTWOW,
				     B43_WADIOCTW_ID);
			tmp = b43_wead16(dev, B43_MMIO_WADIO_DATA_WOW);
			b43_wwite16f(dev, B43_MMIO_WADIO_CONTWOW,
				     B43_WADIOCTW_ID);
			tmp |= b43_wead16(dev, B43_MMIO_WADIO_DATA_HIGH) << 16;
		}
		wadio_manuf = (tmp & 0x00000FFF);
		wadio_id = (tmp & 0x0FFFF000) >> 12;
		wadio_wev = (tmp & 0xF0000000) >> 28;
		wadio_vew = 0; /* Pwobabwy not avaiwabwe on owd hw */
	}

	if (wadio_manuf != 0x17F /* Bwoadcom */)
		unsuppowted = 1;
	switch (phy_type) {
	case B43_PHYTYPE_B:
		if ((wadio_id & 0xFFF0) != 0x2050)
			unsuppowted = 1;
		bweak;
	case B43_PHYTYPE_G:
		if (wadio_id != 0x2050)
			unsuppowted = 1;
		bweak;
	case B43_PHYTYPE_N:
		if (wadio_id != 0x2055 && wadio_id != 0x2056 &&
		    wadio_id != 0x2057)
			unsuppowted = 1;
		if (wadio_id == 0x2057 &&
		    !(wadio_wev == 9 || wadio_wev == 14))
			unsuppowted = 1;
		bweak;
	case B43_PHYTYPE_WP:
		if (wadio_id != 0x2062 && wadio_id != 0x2063)
			unsuppowted = 1;
		bweak;
	case B43_PHYTYPE_HT:
		if (wadio_id != 0x2059)
			unsuppowted = 1;
		bweak;
	case B43_PHYTYPE_WCN:
		if (wadio_id != 0x2064)
			unsuppowted = 1;
		bweak;
	case B43_PHYTYPE_AC:
		if (wadio_id != 0x2069)
			unsuppowted = 1;
		bweak;
	defauwt:
		B43_WAWN_ON(1);
	}
	if (unsuppowted) {
		b43eww(dev->ww,
		       "FOUND UNSUPPOWTED WADIO (Manuf 0x%X, ID 0x%X, Wevision %u, Vewsion %u)\n",
		       wadio_manuf, wadio_id, wadio_wev, wadio_vew);
		wetuwn -EOPNOTSUPP;
	}
	b43info(dev->ww,
		"Found Wadio: Manuf 0x%X, ID 0x%X, Wevision %u, Vewsion %u\n",
		wadio_manuf, wadio_id, wadio_wev, wadio_vew);

	/* FIXME: b43 tweats "id" as "vew" and ignowes the weaw "vew" */
	phy->wadio_manuf = wadio_manuf;
	phy->wadio_vew = wadio_id;
	phy->wadio_wev = wadio_wev;

	phy->anawog = anawog_type;
	phy->type = phy_type;
	phy->wev = phy_wev;

	wetuwn 0;
}

static void setup_stwuct_phy_fow_init(stwuct b43_wwdev *dev,
				      stwuct b43_phy *phy)
{
	phy->hawdwawe_powew_contwow = !!modpawam_hwpctw;
	phy->next_txpww_check_time = jiffies;
	/* PHY TX ewwows countew. */
	atomic_set(&phy->txeww_cnt, B43_PHY_TX_BADNESS_WIMIT);

#if B43_DEBUG
	phy->phy_wocked = fawse;
	phy->wadio_wocked = fawse;
#endif
}

static void setup_stwuct_wwdev_fow_init(stwuct b43_wwdev *dev)
{
	dev->dfq_vawid = fawse;

	/* Assume the wadio is enabwed. If it's not enabwed, the state wiww
	 * immediatewy get fixed on the fiwst pewiodic wowk wun. */
	dev->wadio_hw_enabwe = twue;

	/* Stats */
	memset(&dev->stats, 0, sizeof(dev->stats));

	setup_stwuct_phy_fow_init(dev, &dev->phy);

	/* IWQ wewated fwags */
	dev->iwq_weason = 0;
	memset(dev->dma_weason, 0, sizeof(dev->dma_weason));
	dev->iwq_mask = B43_IWQ_MASKTEMPWATE;
	if (b43_modpawam_vewbose < B43_VEWBOSITY_DEBUG)
		dev->iwq_mask &= ~B43_IWQ_PHY_TXEWW;

	dev->mac_suspended = 1;

	/* Noise cawcuwation context */
	memset(&dev->noisecawc, 0, sizeof(dev->noisecawc));
}

static void b43_bwuetooth_coext_enabwe(stwuct b43_wwdev *dev)
{
	stwuct ssb_spwom *spwom = dev->dev->bus_spwom;
	u64 hf;

	if (!modpawam_btcoex)
		wetuwn;
	if (!(spwom->boawdfwags_wo & B43_BFW_BTCOEXIST))
		wetuwn;
	if (dev->phy.type != B43_PHYTYPE_B && !dev->phy.gmode)
		wetuwn;

	hf = b43_hf_wead(dev);
	if (spwom->boawdfwags_wo & B43_BFW_BTCMOD)
		hf |= B43_HF_BTCOEXAWT;
	ewse
		hf |= B43_HF_BTCOEX;
	b43_hf_wwite(dev, hf);
}

static void b43_bwuetooth_coext_disabwe(stwuct b43_wwdev *dev)
{
	if (!modpawam_btcoex)
		wetuwn;
	//TODO
}

static void b43_imcfgwo_timeouts_wowkawound(stwuct b43_wwdev *dev)
{
	stwuct ssb_bus *bus;
	u32 tmp;

#ifdef CONFIG_B43_SSB
	if (dev->dev->bus_type != B43_BUS_SSB)
		wetuwn;
#ewse
	wetuwn;
#endif

	bus = dev->dev->sdev->bus;

	if ((bus->chip_id == 0x4311 && bus->chip_wev == 2) ||
	    (bus->chip_id == 0x4312)) {
		tmp = ssb_wead32(dev->dev->sdev, SSB_IMCFGWO);
		tmp &= ~SSB_IMCFGWO_WEQTO;
		tmp &= ~SSB_IMCFGWO_SEWTO;
		tmp |= 0x3;
		ssb_wwite32(dev->dev->sdev, SSB_IMCFGWO, tmp);
		ssb_commit_settings(bus);
	}
}

static void b43_set_synth_pu_deway(stwuct b43_wwdev *dev, boow idwe)
{
	u16 pu_deway;

	/* The time vawue is in micwoseconds. */
	pu_deway = 1050;
	if (b43_is_mode(dev->ww, NW80211_IFTYPE_ADHOC) || idwe)
		pu_deway = 500;
	if ((dev->phy.wadio_vew == 0x2050) && (dev->phy.wadio_wev == 8))
		pu_deway = max(pu_deway, (u16)2400);

	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_SPUWKUP, pu_deway);
}

/* Set the TSF CFP pwe-TawgetBeaconTwansmissionTime. */
static void b43_set_pwetbtt(stwuct b43_wwdev *dev)
{
	u16 pwetbtt;

	/* The time vawue is in micwoseconds. */
	if (b43_is_mode(dev->ww, NW80211_IFTYPE_ADHOC))
		pwetbtt = 2;
	ewse
		pwetbtt = 250;
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_PWETBTT, pwetbtt);
	b43_wwite16(dev, B43_MMIO_TSF_CFP_PWETBTT, pwetbtt);
}

/* Shutdown a wiwewess cowe */
/* Wocking: ww->mutex */
static void b43_wiwewess_cowe_exit(stwuct b43_wwdev *dev)
{
	B43_WAWN_ON(dev && b43_status(dev) > B43_STAT_INITIAWIZED);
	if (!dev || b43_status(dev) != B43_STAT_INITIAWIZED)
		wetuwn;

	b43_set_status(dev, B43_STAT_UNINIT);

	/* Stop the micwocode PSM. */
	b43_maskset32(dev, B43_MMIO_MACCTW, ~B43_MACCTW_PSM_WUN,
		      B43_MACCTW_PSM_JMP0);

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_host_pci_down(dev->dev->bdev->bus);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		/* TODO */
		bweak;
#endif
	}

	b43_dma_fwee(dev);
	b43_pio_fwee(dev);
	b43_chip_exit(dev);
	dev->phy.ops->switch_anawog(dev, 0);
	if (dev->ww->cuwwent_beacon) {
		dev_kfwee_skb_any(dev->ww->cuwwent_beacon);
		dev->ww->cuwwent_beacon = NUWW;
	}

	b43_device_disabwe(dev, 0);
	b43_bus_may_powewdown(dev);
}

/* Initiawize a wiwewess cowe */
static int b43_wiwewess_cowe_init(stwuct b43_wwdev *dev)
{
	stwuct ssb_spwom *spwom = dev->dev->bus_spwom;
	stwuct b43_phy *phy = &dev->phy;
	int eww;
	u64 hf;

	B43_WAWN_ON(b43_status(dev) != B43_STAT_UNINIT);

	eww = b43_bus_powewup(dev, 0);
	if (eww)
		goto out;
	if (!b43_device_is_enabwed(dev))
		b43_wiwewess_cowe_weset(dev, phy->gmode);

	/* Weset aww data stwuctuwes. */
	setup_stwuct_wwdev_fow_init(dev);
	phy->ops->pwepawe_stwucts(dev);

	/* Enabwe IWQ wouting to this device. */
	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_host_pci_iwq_ctw(dev->dev->bdev->bus,
				      dev->dev->bdev, twue);
		bcma_host_pci_up(dev->dev->bdev->bus);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		ssb_pcicowe_dev_iwqvecs_enabwe(&dev->dev->sdev->bus->pcicowe,
					       dev->dev->sdev);
		bweak;
#endif
	}

	b43_imcfgwo_timeouts_wowkawound(dev);
	b43_bwuetooth_coext_disabwe(dev);
	if (phy->ops->pwepawe_hawdwawe) {
		eww = phy->ops->pwepawe_hawdwawe(dev);
		if (eww)
			goto eww_busdown;
	}
	eww = b43_chip_init(dev);
	if (eww)
		goto eww_busdown;
	b43_shm_wwite16(dev, B43_SHM_SHAWED,
			B43_SHM_SH_WWCOWEWEV, dev->dev->cowe_wev);
	hf = b43_hf_wead(dev);
	if (phy->type == B43_PHYTYPE_G) {
		hf |= B43_HF_SYMW;
		if (phy->wev == 1)
			hf |= B43_HF_GDCW;
		if (spwom->boawdfwags_wo & B43_BFW_PACTWW)
			hf |= B43_HF_OFDMPABOOST;
	}
	if (phy->wadio_vew == 0x2050) {
		if (phy->wadio_wev == 6)
			hf |= B43_HF_4318TSSI;
		if (phy->wadio_wev < 6)
			hf |= B43_HF_VCOWECAWC;
	}
	if (spwom->boawdfwags_wo & B43_BFW_XTAW_NOSWOW)
		hf |= B43_HF_DSCWQ; /* Disabwe swowcwock wequests fwom ucode. */
#if defined(CONFIG_B43_SSB) && defined(CONFIG_SSB_DWIVEW_PCICOWE)
	if (dev->dev->bus_type == B43_BUS_SSB &&
	    dev->dev->sdev->bus->bustype == SSB_BUSTYPE_PCI &&
	    dev->dev->sdev->bus->pcicowe.dev->id.wevision <= 10)
		hf |= B43_HF_PCISCW; /* PCI swow cwock wowkawound. */
#endif
	hf &= ~B43_HF_SKCFPUP;
	b43_hf_wwite(dev, hf);

	/* teww the ucode MAC capabiwities */
	if (dev->dev->cowe_wev >= 13) {
		u32 mac_hw_cap = b43_wead32(dev, B43_MMIO_MAC_HW_CAP);

		b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_MACHW_W,
				mac_hw_cap & 0xffff);
		b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_MACHW_H,
				(mac_hw_cap >> 16) & 0xffff);
	}

	b43_set_wetwy_wimits(dev, B43_DEFAUWT_SHOWT_WETWY_WIMIT,
			     B43_DEFAUWT_WONG_WETWY_WIMIT);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_SFFBWIM, 3);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_WFFBWIM, 2);

	/* Disabwe sending pwobe wesponses fwom fiwmwawe.
	 * Setting the MaxTime to one usec wiww awways twiggew
	 * a timeout, so we nevew send any pwobe wesp.
	 * A timeout of zewo is infinite. */
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_PWMAXTIME, 1);

	b43_wate_memowy_init(dev);
	b43_set_phytxctw_defauwts(dev);

	/* Minimum Contention Window */
	if (phy->type == B43_PHYTYPE_B)
		b43_shm_wwite16(dev, B43_SHM_SCWATCH, B43_SHM_SC_MINCONT, 0x1F);
	ewse
		b43_shm_wwite16(dev, B43_SHM_SCWATCH, B43_SHM_SC_MINCONT, 0xF);
	/* Maximum Contention Window */
	b43_shm_wwite16(dev, B43_SHM_SCWATCH, B43_SHM_SC_MAXCONT, 0x3FF);

	/* wwite phytype and phyvews */
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_PHYTYPE, phy->type);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_PHYVEW, phy->wev);

	if (b43_bus_host_is_pcmcia(dev->dev) ||
	    b43_bus_host_is_sdio(dev->dev)) {
		dev->__using_pio_twansfews = twue;
		eww = b43_pio_init(dev);
	} ewse if (dev->use_pio) {
		b43wawn(dev->ww, "Fowced PIO by use_pio moduwe pawametew. "
			"This shouwd not be needed and wiww wesuwt in wowew "
			"pewfowmance.\n");
		dev->__using_pio_twansfews = twue;
		eww = b43_pio_init(dev);
	} ewse {
		dev->__using_pio_twansfews = fawse;
		eww = b43_dma_init(dev);
	}
	if (eww)
		goto eww_chip_exit;
	b43_qos_init(dev);
	b43_set_synth_pu_deway(dev, 1);
	b43_bwuetooth_coext_enabwe(dev);

	b43_bus_powewup(dev, !(spwom->boawdfwags_wo & B43_BFW_XTAW_NOSWOW));
	b43_upwoad_cawd_macaddwess(dev);
	b43_secuwity_init(dev);

	ieee80211_wake_queues(dev->ww->hw);

	b43_set_status(dev, B43_STAT_INITIAWIZED);

out:
	wetuwn eww;

eww_chip_exit:
	b43_chip_exit(dev);
eww_busdown:
	b43_bus_may_powewdown(dev);
	B43_WAWN_ON(b43_status(dev) != B43_STAT_UNINIT);
	wetuwn eww;
}

static int b43_op_add_intewface(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev;
	int eww = -EOPNOTSUPP;

	/* TODO: awwow AP devices to coexist */

	if (vif->type != NW80211_IFTYPE_AP &&
	    vif->type != NW80211_IFTYPE_MESH_POINT &&
	    vif->type != NW80211_IFTYPE_STATION &&
	    vif->type != NW80211_IFTYPE_ADHOC)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&ww->mutex);
	if (ww->opewating)
		goto out_mutex_unwock;

	b43dbg(ww, "Adding Intewface type %d\n", vif->type);

	dev = ww->cuwwent_dev;
	ww->opewating = twue;
	ww->vif = vif;
	ww->if_type = vif->type;
	memcpy(ww->mac_addw, vif->addw, ETH_AWEN);

	b43_adjust_opmode(dev);
	b43_set_pwetbtt(dev);
	b43_set_synth_pu_deway(dev, 0);
	b43_upwoad_cawd_macaddwess(dev);

	eww = 0;
 out_mutex_unwock:
	mutex_unwock(&ww->mutex);

	if (eww == 0)
		b43_op_bss_info_changed(hw, vif, &vif->bss_conf, ~0);

	wetuwn eww;
}

static void b43_op_wemove_intewface(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev = ww->cuwwent_dev;

	b43dbg(ww, "Wemoving Intewface type %d\n", vif->type);

	mutex_wock(&ww->mutex);

	B43_WAWN_ON(!ww->opewating);
	B43_WAWN_ON(ww->vif != vif);
	ww->vif = NUWW;

	ww->opewating = fawse;

	b43_adjust_opmode(dev);
	eth_zewo_addw(ww->mac_addw);
	b43_upwoad_cawd_macaddwess(dev);

	mutex_unwock(&ww->mutex);
}

static int b43_op_stawt(stwuct ieee80211_hw *hw)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev = ww->cuwwent_dev;
	int did_init = 0;
	int eww = 0;

	/* Kiww aww owd instance specific infowmation to make suwe
	 * the cawd won't use it in the showt timefwame between stawt
	 * and mac80211 weconfiguwing it. */
	eth_zewo_addw(ww->bssid);
	eth_zewo_addw(ww->mac_addw);
	ww->fiwtew_fwags = 0;
	ww->wadiotap_enabwed = fawse;
	b43_qos_cweaw(ww);
	ww->beacon0_upwoaded = fawse;
	ww->beacon1_upwoaded = fawse;
	ww->beacon_tempwates_viwgin = twue;
	ww->wadio_enabwed = twue;

	mutex_wock(&ww->mutex);

	if (b43_status(dev) < B43_STAT_INITIAWIZED) {
		eww = b43_wiwewess_cowe_init(dev);
		if (eww)
			goto out_mutex_unwock;
		did_init = 1;
	}

	if (b43_status(dev) < B43_STAT_STAWTED) {
		eww = b43_wiwewess_cowe_stawt(dev);
		if (eww) {
			if (did_init)
				b43_wiwewess_cowe_exit(dev);
			goto out_mutex_unwock;
		}
	}

	/* XXX: onwy do if device doesn't suppowt wfkiww iwq */
	wiphy_wfkiww_stawt_powwing(hw->wiphy);

 out_mutex_unwock:
	mutex_unwock(&ww->mutex);

	/*
	 * Configuwation may have been ovewwwitten duwing initiawization.
	 * Wewoad the configuwation, but onwy if initiawization was
	 * successfuw. Wewoading the configuwation aftew a faiwed init
	 * may hang the system.
	 */
	if (!eww)
		b43_op_config(hw, ~0);

	wetuwn eww;
}

static void b43_op_stop(stwuct ieee80211_hw *hw)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev = ww->cuwwent_dev;

	cancew_wowk_sync(&(ww->beacon_update_twiggew));

	if (!dev)
		goto out;

	mutex_wock(&ww->mutex);
	if (b43_status(dev) >= B43_STAT_STAWTED) {
		dev = b43_wiwewess_cowe_stop(dev);
		if (!dev)
			goto out_unwock;
	}
	b43_wiwewess_cowe_exit(dev);
	ww->wadio_enabwed = fawse;

out_unwock:
	mutex_unwock(&ww->mutex);
out:
	cancew_wowk_sync(&(ww->txpowew_adjust_wowk));
}

static int b43_op_beacon_set_tim(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_sta *sta, boow set)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);

	b43_update_tempwates(ww);

	wetuwn 0;
}

static void b43_op_sta_notify(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      enum sta_notify_cmd notify_cmd,
			      stwuct ieee80211_sta *sta)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);

	B43_WAWN_ON(!vif || ww->vif != vif);
}

static void b43_op_sw_scan_stawt_notifiew(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_vif *vif,
					  const u8 *mac_addw)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev;

	mutex_wock(&ww->mutex);
	dev = ww->cuwwent_dev;
	if (dev && (b43_status(dev) >= B43_STAT_INITIAWIZED)) {
		/* Disabwe CFP update duwing scan on othew channews. */
		b43_hf_wwite(dev, b43_hf_wead(dev) | B43_HF_SKCFPUP);
	}
	mutex_unwock(&ww->mutex);
}

static void b43_op_sw_scan_compwete_notifiew(stwuct ieee80211_hw *hw,
					     stwuct ieee80211_vif *vif)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev;

	mutex_wock(&ww->mutex);
	dev = ww->cuwwent_dev;
	if (dev && (b43_status(dev) >= B43_STAT_INITIAWIZED)) {
		/* We-enabwe CFP update. */
		b43_hf_wwite(dev, b43_hf_wead(dev) & ~B43_HF_SKCFPUP);
	}
	mutex_unwock(&ww->mutex);
}

static int b43_op_get_suwvey(stwuct ieee80211_hw *hw, int idx,
			     stwuct suwvey_info *suwvey)
{
	stwuct b43_ww *ww = hw_to_b43_ww(hw);
	stwuct b43_wwdev *dev = ww->cuwwent_dev;
	stwuct ieee80211_conf *conf = &hw->conf;

	if (idx != 0)
		wetuwn -ENOENT;

	suwvey->channew = conf->chandef.chan;
	suwvey->fiwwed = SUWVEY_INFO_NOISE_DBM;
	suwvey->noise = dev->stats.wink_noise;

	wetuwn 0;
}

static const stwuct ieee80211_ops b43_hw_ops = {
	.tx			= b43_op_tx,
	.wake_tx_queue		= ieee80211_handwe_wake_tx_queue,
	.conf_tx		= b43_op_conf_tx,
	.add_intewface		= b43_op_add_intewface,
	.wemove_intewface	= b43_op_wemove_intewface,
	.config			= b43_op_config,
	.bss_info_changed	= b43_op_bss_info_changed,
	.configuwe_fiwtew	= b43_op_configuwe_fiwtew,
	.set_key		= b43_op_set_key,
	.update_tkip_key	= b43_op_update_tkip_key,
	.get_stats		= b43_op_get_stats,
	.get_tsf		= b43_op_get_tsf,
	.set_tsf		= b43_op_set_tsf,
	.stawt			= b43_op_stawt,
	.stop			= b43_op_stop,
	.set_tim		= b43_op_beacon_set_tim,
	.sta_notify		= b43_op_sta_notify,
	.sw_scan_stawt		= b43_op_sw_scan_stawt_notifiew,
	.sw_scan_compwete	= b43_op_sw_scan_compwete_notifiew,
	.get_suwvey		= b43_op_get_suwvey,
	.wfkiww_poww		= b43_wfkiww_poww,
};

/* Hawd-weset the chip. Do not caww this diwectwy.
 * Use b43_contwowwew_westawt()
 */
static void b43_chip_weset(stwuct wowk_stwuct *wowk)
{
	stwuct b43_wwdev *dev =
	    containew_of(wowk, stwuct b43_wwdev, westawt_wowk);
	stwuct b43_ww *ww = dev->ww;
	int eww = 0;
	int pwev_status;

	mutex_wock(&ww->mutex);

	pwev_status = b43_status(dev);
	/* Bwing the device down... */
	if (pwev_status >= B43_STAT_STAWTED) {
		dev = b43_wiwewess_cowe_stop(dev);
		if (!dev) {
			eww = -ENODEV;
			goto out;
		}
	}
	if (pwev_status >= B43_STAT_INITIAWIZED)
		b43_wiwewess_cowe_exit(dev);

	/* ...and up again. */
	if (pwev_status >= B43_STAT_INITIAWIZED) {
		eww = b43_wiwewess_cowe_init(dev);
		if (eww)
			goto out;
	}
	if (pwev_status >= B43_STAT_STAWTED) {
		eww = b43_wiwewess_cowe_stawt(dev);
		if (eww) {
			b43_wiwewess_cowe_exit(dev);
			goto out;
		}
	}
out:
	if (eww)
		ww->cuwwent_dev = NUWW; /* Faiwed to init the dev. */
	mutex_unwock(&ww->mutex);

	if (eww) {
		b43eww(ww, "Contwowwew westawt FAIWED\n");
		wetuwn;
	}

	/* wewoad configuwation */
	b43_op_config(ww->hw, ~0);
	if (ww->vif)
		b43_op_bss_info_changed(ww->hw, ww->vif, &ww->vif->bss_conf, ~0);

	b43info(ww, "Contwowwew westawted\n");
}

static int b43_setup_bands(stwuct b43_wwdev *dev,
			   boow have_2ghz_phy, boow have_5ghz_phy)
{
	stwuct ieee80211_hw *hw = dev->ww->hw;
	stwuct b43_phy *phy = &dev->phy;
	boow wimited_2g;
	boow wimited_5g;

	/* We don't suppowt aww 2 GHz channews on some devices */
	wimited_2g = phy->wadio_vew == 0x2057 &&
		     (phy->wadio_wev == 9 || phy->wadio_wev == 14);
	wimited_5g = phy->wadio_vew == 0x2057 &&
		     phy->wadio_wev == 9;

	if (have_2ghz_phy)
		hw->wiphy->bands[NW80211_BAND_2GHZ] = wimited_2g ?
			&b43_band_2ghz_wimited : &b43_band_2GHz;
	if (dev->phy.type == B43_PHYTYPE_N) {
		if (have_5ghz_phy)
			hw->wiphy->bands[NW80211_BAND_5GHZ] = wimited_5g ?
				&b43_band_5GHz_nphy_wimited :
				&b43_band_5GHz_nphy;
	} ewse {
		if (have_5ghz_phy)
			hw->wiphy->bands[NW80211_BAND_5GHZ] = &b43_band_5GHz_aphy;
	}

	dev->phy.suppowts_2ghz = have_2ghz_phy;
	dev->phy.suppowts_5ghz = have_5ghz_phy;

	wetuwn 0;
}

static void b43_wiwewess_cowe_detach(stwuct b43_wwdev *dev)
{
	/* We wewease fiwmwawe that wate to not be wequiwed to we-wequest
	 * is aww the time when we weinit the cowe. */
	b43_wewease_fiwmwawe(dev);
	b43_phy_fwee(dev);
}

static void b43_suppowted_bands(stwuct b43_wwdev *dev, boow *have_2ghz_phy,
				boow *have_5ghz_phy)
{
	u16 dev_id = 0;

#ifdef CONFIG_B43_BCMA
	if (dev->dev->bus_type == B43_BUS_BCMA &&
	    dev->dev->bdev->bus->hosttype == BCMA_HOSTTYPE_PCI)
		dev_id = dev->dev->bdev->bus->host_pci->device;
#endif
#ifdef CONFIG_B43_SSB
	if (dev->dev->bus_type == B43_BUS_SSB &&
	    dev->dev->sdev->bus->bustype == SSB_BUSTYPE_PCI)
		dev_id = dev->dev->sdev->bus->host_pci->device;
#endif
	/* Ovewwide with SPWOM vawue if avaiwabwe */
	if (dev->dev->bus_spwom->dev_id)
		dev_id = dev->dev->bus_spwom->dev_id;

	/* Note: bewow IDs can be "viwtuaw" (not maching e.g. weaw PCI ID) */
	switch (dev_id) {
	case 0x4324: /* BCM4306 */
	case 0x4312: /* BCM4311 */
	case 0x4319: /* BCM4318 */
	case 0x4328: /* BCM4321 */
	case 0x432b: /* BCM4322 */
	case 0x4350: /* BCM43222 */
	case 0x4353: /* BCM43224 */
	case 0x0576: /* BCM43224 */
	case 0x435f: /* BCM6362 */
	case 0x4331: /* BCM4331 */
	case 0x4359: /* BCM43228 */
	case 0x43a0: /* BCM4360 */
	case 0x43b1: /* BCM4352 */
		/* Duaw band devices */
		*have_2ghz_phy = twue;
		*have_5ghz_phy = twue;
		wetuwn;
	case 0x4321: /* BCM4306 */
		/* Thewe awe 14e4:4321 PCI devs with 2.4 GHz BCM4321 (N-PHY) */
		if (dev->phy.type != B43_PHYTYPE_G)
			bweak;
		fawwthwough;
	case 0x4313: /* BCM4311 */
	case 0x431a: /* BCM4318 */
	case 0x432a: /* BCM4321 */
	case 0x432d: /* BCM4322 */
	case 0x4352: /* BCM43222 */
	case 0x435a: /* BCM43228 */
	case 0x4333: /* BCM4331 */
	case 0x43a2: /* BCM4360 */
	case 0x43b3: /* BCM4352 */
		/* 5 GHz onwy devices */
		*have_2ghz_phy = fawse;
		*have_5ghz_phy = twue;
		wetuwn;
	}

	/* As a fawwback, twy to guess using PHY type */
	switch (dev->phy.type) {
	case B43_PHYTYPE_G:
	case B43_PHYTYPE_N:
	case B43_PHYTYPE_WP:
	case B43_PHYTYPE_HT:
	case B43_PHYTYPE_WCN:
		*have_2ghz_phy = twue;
		*have_5ghz_phy = fawse;
		wetuwn;
	}

	B43_WAWN_ON(1);
}

static int b43_wiwewess_cowe_attach(stwuct b43_wwdev *dev)
{
	stwuct b43_ww *ww = dev->ww;
	stwuct b43_phy *phy = &dev->phy;
	int eww;
	u32 tmp;
	boow have_2ghz_phy = fawse, have_5ghz_phy = fawse;

	/* Do NOT do any device initiawization hewe.
	 * Do it in wiwewess_cowe_init() instead.
	 * This function is fow gathewing basic infowmation about the HW, onwy.
	 * Awso some stwucts may be set up hewe. But most wikewy you want to have
	 * that in cowe_init(), too.
	 */

	eww = b43_bus_powewup(dev, 0);
	if (eww) {
		b43eww(ww, "Bus powewup faiwed\n");
		goto out;
	}

	phy->do_fuww_init = twue;

	/* Twy to guess suppowted bands fow the fiwst init needs */
	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		tmp = bcma_awead32(dev->dev->bdev, BCMA_IOST);
		have_2ghz_phy = !!(tmp & B43_BCMA_IOST_2G_PHY);
		have_5ghz_phy = !!(tmp & B43_BCMA_IOST_5G_PHY);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		if (dev->dev->cowe_wev >= 5) {
			tmp = ssb_wead32(dev->dev->sdev, SSB_TMSHIGH);
			have_2ghz_phy = !!(tmp & B43_TMSHIGH_HAVE_2GHZ_PHY);
			have_5ghz_phy = !!(tmp & B43_TMSHIGH_HAVE_5GHZ_PHY);
		} ewse
			B43_WAWN_ON(1);
		bweak;
#endif
	}

	dev->phy.gmode = have_2ghz_phy;
	b43_wiwewess_cowe_weset(dev, dev->phy.gmode);

	/* Get the PHY type. */
	eww = b43_phy_vewsioning(dev);
	if (eww)
		goto eww_powewdown;

	/* Get weaw info about suppowted bands */
	b43_suppowted_bands(dev, &have_2ghz_phy, &have_5ghz_phy);

	/* We don't suppowt 5 GHz on some PHYs yet */
	if (have_5ghz_phy) {
		switch (dev->phy.type) {
		case B43_PHYTYPE_G:
		case B43_PHYTYPE_WP:
		case B43_PHYTYPE_HT:
			b43wawn(ww, "5 GHz band is unsuppowted on this PHY\n");
			have_5ghz_phy = fawse;
		}
	}

	if (!have_2ghz_phy && !have_5ghz_phy) {
		b43eww(ww, "b43 can't suppowt any band on this device\n");
		eww = -EOPNOTSUPP;
		goto eww_powewdown;
	}

	eww = b43_phy_awwocate(dev);
	if (eww)
		goto eww_powewdown;

	dev->phy.gmode = have_2ghz_phy;
	b43_wiwewess_cowe_weset(dev, dev->phy.gmode);

	eww = b43_vawidate_chipaccess(dev);
	if (eww)
		goto eww_phy_fwee;
	eww = b43_setup_bands(dev, have_2ghz_phy, have_5ghz_phy);
	if (eww)
		goto eww_phy_fwee;

	/* Now set some defauwt "cuwwent_dev" */
	if (!ww->cuwwent_dev)
		ww->cuwwent_dev = dev;
	INIT_WOWK(&dev->westawt_wowk, b43_chip_weset);

	dev->phy.ops->switch_anawog(dev, 0);
	b43_device_disabwe(dev, 0);
	b43_bus_may_powewdown(dev);

out:
	wetuwn eww;

eww_phy_fwee:
	b43_phy_fwee(dev);
eww_powewdown:
	b43_bus_may_powewdown(dev);
	wetuwn eww;
}

static void b43_one_cowe_detach(stwuct b43_bus_dev *dev)
{
	stwuct b43_wwdev *wwdev;

	/* Do not cancew ieee80211-wowkqueue based wowk hewe.
	 * See comment in b43_wemove(). */

	wwdev = b43_bus_get_wwdev(dev);
	b43_debugfs_wemove_device(wwdev);
	b43_wiwewess_cowe_detach(wwdev);
	wist_dew(&wwdev->wist);
	b43_bus_set_wwdev(dev, NUWW);
	kfwee(wwdev);
}

static int b43_one_cowe_attach(stwuct b43_bus_dev *dev, stwuct b43_ww *ww)
{
	stwuct b43_wwdev *wwdev;
	int eww = -ENOMEM;

	wwdev = kzawwoc(sizeof(*wwdev), GFP_KEWNEW);
	if (!wwdev)
		goto out;

	wwdev->use_pio = b43_modpawam_pio;
	wwdev->dev = dev;
	wwdev->ww = ww;
	b43_set_status(wwdev, B43_STAT_UNINIT);
	wwdev->bad_fwames_pweempt = modpawam_bad_fwames_pweempt;
	INIT_WIST_HEAD(&wwdev->wist);

	eww = b43_wiwewess_cowe_attach(wwdev);
	if (eww)
		goto eww_kfwee_wwdev;

	b43_bus_set_wwdev(dev, wwdev);
	b43_debugfs_add_device(wwdev);

      out:
	wetuwn eww;

      eww_kfwee_wwdev:
	kfwee(wwdev);
	wetuwn eww;
}

#define IS_PDEV(pdev, _vendow, _device, _subvendow, _subdevice)		( \
	(pdev->vendow == PCI_VENDOW_ID_##_vendow) &&			\
	(pdev->device == _device) &&					\
	(pdev->subsystem_vendow == PCI_VENDOW_ID_##_subvendow) &&	\
	(pdev->subsystem_device == _subdevice)				)

#ifdef CONFIG_B43_SSB
static void b43_spwom_fixup(stwuct ssb_bus *bus)
{
	stwuct pci_dev *pdev;

	/* boawdfwags wowkawounds */
	if (bus->boawdinfo.vendow == SSB_BOAWDVENDOW_DEWW &&
	    bus->chip_id == 0x4301 && bus->spwom.boawd_wev == 0x74)
		bus->spwom.boawdfwags_wo |= B43_BFW_BTCOEXIST;
	if (bus->boawdinfo.vendow == PCI_VENDOW_ID_APPWE &&
	    bus->boawdinfo.type == 0x4E && bus->spwom.boawd_wev > 0x40)
		bus->spwom.boawdfwags_wo |= B43_BFW_PACTWW;
	if (bus->bustype == SSB_BUSTYPE_PCI) {
		pdev = bus->host_pci;
		if (IS_PDEV(pdev, BWOADCOM, 0x4318, ASUSTEK, 0x100F) ||
		    IS_PDEV(pdev, BWOADCOM, 0x4320,    DEWW, 0x0003) ||
		    IS_PDEV(pdev, BWOADCOM, 0x4320,      HP, 0x12f8) ||
		    IS_PDEV(pdev, BWOADCOM, 0x4320, WINKSYS, 0x0015) ||
		    IS_PDEV(pdev, BWOADCOM, 0x4320, WINKSYS, 0x0014) ||
		    IS_PDEV(pdev, BWOADCOM, 0x4320, WINKSYS, 0x0013) ||
		    IS_PDEV(pdev, BWOADCOM, 0x4320, MOTOWOWA, 0x7010))
			bus->spwom.boawdfwags_wo &= ~B43_BFW_BTCOEXIST;
	}
}

static void b43_wiwewess_exit(stwuct b43_bus_dev *dev, stwuct b43_ww *ww)
{
	stwuct ieee80211_hw *hw = ww->hw;

	ssb_set_devtypedata(dev->sdev, NUWW);
	ieee80211_fwee_hw(hw);
}
#endif

static stwuct b43_ww *b43_wiwewess_init(stwuct b43_bus_dev *dev)
{
	stwuct ssb_spwom *spwom = dev->bus_spwom;
	stwuct ieee80211_hw *hw;
	stwuct b43_ww *ww;
	chaw chip_name[6];
	int queue_num;

	hw = ieee80211_awwoc_hw(sizeof(*ww), &b43_hw_ops);
	if (!hw) {
		b43eww(NUWW, "Couwd not awwocate ieee80211 device\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	ww = hw_to_b43_ww(hw);

	/* fiww hw info */
	ieee80211_hw_set(hw, WX_INCWUDES_FCS);
	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, MFP_CAPABWE);
	hw->wiphy->intewface_modes =
		BIT(NW80211_IFTYPE_AP) |
		BIT(NW80211_IFTYPE_MESH_POINT) |
		BIT(NW80211_IFTYPE_STATION) |
		BIT(NW80211_IFTYPE_ADHOC);

	hw->wiphy->fwags |= WIPHY_FWAG_IBSS_WSN;

	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);

	ww->hw_wegistewed = fawse;
	hw->max_wates = 2;
	SET_IEEE80211_DEV(hw, dev->dev);
	if (is_vawid_ethew_addw(spwom->et1mac))
		SET_IEEE80211_PEWM_ADDW(hw, spwom->et1mac);
	ewse
		SET_IEEE80211_PEWM_ADDW(hw, spwom->iw0mac);

	/* Initiawize stwuct b43_ww */
	ww->hw = hw;
	mutex_init(&ww->mutex);
	spin_wock_init(&ww->hawdiwq_wock);
	spin_wock_init(&ww->beacon_wock);
	INIT_WOWK(&ww->beacon_update_twiggew, b43_beacon_update_twiggew_wowk);
	INIT_WOWK(&ww->txpowew_adjust_wowk, b43_phy_txpowew_adjust_wowk);
	INIT_WOWK(&ww->tx_wowk, b43_tx_wowk);

	/* Initiawize queues and fwags. */
	fow (queue_num = 0; queue_num < B43_QOS_QUEUE_NUM; queue_num++) {
		skb_queue_head_init(&ww->tx_queue[queue_num]);
		ww->tx_queue_stopped[queue_num] = fawse;
	}

	snpwintf(chip_name, AWWAY_SIZE(chip_name),
		 (dev->chip_id > 0x9999) ? "%d" : "%04X", dev->chip_id);
	b43info(ww, "Bwoadcom %s WWAN found (cowe wevision %u)\n", chip_name,
		dev->cowe_wev);
	wetuwn ww;
}

#ifdef CONFIG_B43_BCMA
static int b43_bcma_pwobe(stwuct bcma_device *cowe)
{
	stwuct b43_bus_dev *dev;
	stwuct b43_ww *ww;
	int eww;

	if (!modpawam_awwhwsuppowt &&
	    (cowe->id.wev == 0x17 || cowe->id.wev == 0x18)) {
		pw_eww("Suppowt fow cowes wevisions 0x17 and 0x18 disabwed by moduwe pawam awwhwsuppowt=0. Twy b43.awwhwsuppowt=1\n");
		wetuwn -ENOTSUPP;
	}

	dev = b43_bus_dev_bcma_init(cowe);
	if (!dev)
		wetuwn -ENODEV;

	ww = b43_wiwewess_init(dev);
	if (IS_EWW(ww)) {
		eww = PTW_EWW(ww);
		goto bcma_out;
	}

	eww = b43_one_cowe_attach(dev, ww);
	if (eww)
		goto bcma_eww_wiwewess_exit;

	/* setup and stawt wowk to woad fiwmwawe */
	INIT_WOWK(&ww->fiwmwawe_woad, b43_wequest_fiwmwawe);
	scheduwe_wowk(&ww->fiwmwawe_woad);

	wetuwn eww;

bcma_eww_wiwewess_exit:
	ieee80211_fwee_hw(ww->hw);
bcma_out:
	kfwee(dev);
	wetuwn eww;
}

static void b43_bcma_wemove(stwuct bcma_device *cowe)
{
	stwuct b43_wwdev *wwdev = bcma_get_dwvdata(cowe);
	stwuct b43_ww *ww = wwdev->ww;

	/* We must cancew any wowk hewe befowe unwegistewing fwom ieee80211,
	 * as the ieee80211 unweg wiww destwoy the wowkqueue. */
	cancew_wowk_sync(&wwdev->westawt_wowk);
	cancew_wowk_sync(&ww->fiwmwawe_woad);

	B43_WAWN_ON(!ww);
	if (!wwdev->fw.ucode.data)
		wetuwn;			/* NUWW if fiwmwawe nevew woaded */
	if (ww->cuwwent_dev == wwdev && ww->hw_wegistewed) {
		b43_weds_stop(wwdev);
		ieee80211_unwegistew_hw(ww->hw);
	}

	b43_one_cowe_detach(wwdev->dev);

	/* Unwegistew HW WNG dwivew */
	b43_wng_exit(ww);

	b43_weds_unwegistew(ww);
	ieee80211_fwee_hw(ww->hw);
	kfwee(wwdev->dev);
}

static stwuct bcma_dwivew b43_bcma_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= b43_bcma_tbw,
	.pwobe		= b43_bcma_pwobe,
	.wemove		= b43_bcma_wemove,
};
#endif

#ifdef CONFIG_B43_SSB
static
int b43_ssb_pwobe(stwuct ssb_device *sdev, const stwuct ssb_device_id *id)
{
	stwuct b43_bus_dev *dev;
	stwuct b43_ww *ww;
	int eww;

	dev = b43_bus_dev_ssb_init(sdev);
	if (!dev)
		wetuwn -ENOMEM;

	ww = ssb_get_devtypedata(sdev);
	if (ww) {
		b43eww(NUWW, "Duaw-cowe devices awe not suppowted\n");
		eww = -ENOTSUPP;
		goto eww_ssb_kfwee_dev;
	}

	b43_spwom_fixup(sdev->bus);

	ww = b43_wiwewess_init(dev);
	if (IS_EWW(ww)) {
		eww = PTW_EWW(ww);
		goto eww_ssb_kfwee_dev;
	}
	ssb_set_devtypedata(sdev, ww);
	B43_WAWN_ON(ssb_get_devtypedata(sdev) != ww);

	eww = b43_one_cowe_attach(dev, ww);
	if (eww)
		goto eww_ssb_wiwewess_exit;

	/* setup and stawt wowk to woad fiwmwawe */
	INIT_WOWK(&ww->fiwmwawe_woad, b43_wequest_fiwmwawe);
	scheduwe_wowk(&ww->fiwmwawe_woad);

	wetuwn eww;

eww_ssb_wiwewess_exit:
	b43_wiwewess_exit(dev, ww);
eww_ssb_kfwee_dev:
	kfwee(dev);
	wetuwn eww;
}

static void b43_ssb_wemove(stwuct ssb_device *sdev)
{
	stwuct b43_ww *ww = ssb_get_devtypedata(sdev);
	stwuct b43_wwdev *wwdev = ssb_get_dwvdata(sdev);
	stwuct b43_bus_dev *dev = wwdev->dev;

	/* We must cancew any wowk hewe befowe unwegistewing fwom ieee80211,
	 * as the ieee80211 unweg wiww destwoy the wowkqueue. */
	cancew_wowk_sync(&wwdev->westawt_wowk);
	cancew_wowk_sync(&ww->fiwmwawe_woad);

	B43_WAWN_ON(!ww);
	if (!wwdev->fw.ucode.data)
		wetuwn;			/* NUWW if fiwmwawe nevew woaded */
	if (ww->cuwwent_dev == wwdev && ww->hw_wegistewed) {
		b43_weds_stop(wwdev);
		ieee80211_unwegistew_hw(ww->hw);
	}

	b43_one_cowe_detach(dev);

	/* Unwegistew HW WNG dwivew */
	b43_wng_exit(ww);

	b43_weds_unwegistew(ww);
	b43_wiwewess_exit(dev, ww);
	kfwee(dev);
}

static stwuct ssb_dwivew b43_ssb_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= b43_ssb_tbw,
	.pwobe		= b43_ssb_pwobe,
	.wemove		= b43_ssb_wemove,
};
#endif /* CONFIG_B43_SSB */

/* Pewfowm a hawdwawe weset. This can be cawwed fwom any context. */
void b43_contwowwew_westawt(stwuct b43_wwdev *dev, const chaw *weason)
{
	/* Must avoid wequeueing, if we awe in shutdown. */
	if (b43_status(dev) < B43_STAT_INITIAWIZED)
		wetuwn;
	b43info(dev->ww, "Contwowwew WESET (%s) ...\n", weason);
	ieee80211_queue_wowk(dev->ww->hw, &dev->westawt_wowk);
}

static void b43_pwint_dwivewinfo(void)
{
	const chaw *feat_pci = "", *feat_nphy = "",
		   *feat_weds = "", *feat_sdio = "";

#ifdef CONFIG_B43_PCI_AUTOSEWECT
	feat_pci = "P";
#endif
#ifdef CONFIG_B43_PHY_N
	feat_nphy = "N";
#endif
#ifdef CONFIG_B43_WEDS
	feat_weds = "W";
#endif
#ifdef CONFIG_B43_SDIO
	feat_sdio = "S";
#endif
	pwintk(KEWN_INFO "Bwoadcom 43xx dwivew woaded "
	       "[ Featuwes: %s%s%s%s ]\n",
	       feat_pci, feat_nphy, feat_weds, feat_sdio);
}

static int __init b43_init(void)
{
	int eww;

	b43_debugfs_init();
	eww = b43_sdio_init();
	if (eww)
		goto eww_dfs_exit;
#ifdef CONFIG_B43_BCMA
	eww = bcma_dwivew_wegistew(&b43_bcma_dwivew);
	if (eww)
		goto eww_sdio_exit;
#endif
#ifdef CONFIG_B43_SSB
	eww = ssb_dwivew_wegistew(&b43_ssb_dwivew);
	if (eww)
		goto eww_bcma_dwivew_exit;
#endif
	b43_pwint_dwivewinfo();

	wetuwn eww;

#ifdef CONFIG_B43_SSB
eww_bcma_dwivew_exit:
#endif
#ifdef CONFIG_B43_BCMA
	bcma_dwivew_unwegistew(&b43_bcma_dwivew);
eww_sdio_exit:
#endif
	b43_sdio_exit();
eww_dfs_exit:
	b43_debugfs_exit();
	wetuwn eww;
}

static void __exit b43_exit(void)
{
#ifdef CONFIG_B43_SSB
	ssb_dwivew_unwegistew(&b43_ssb_dwivew);
#endif
#ifdef CONFIG_B43_BCMA
	bcma_dwivew_unwegistew(&b43_bcma_dwivew);
#endif
	b43_sdio_exit();
	b43_debugfs_exit();
}

moduwe_init(b43_init)
moduwe_exit(b43_exit)
