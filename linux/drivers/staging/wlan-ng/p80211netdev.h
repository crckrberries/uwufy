/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1) */
/*
 *
 * WWAN net device stwuctuwe and functions
 *
 * Copywight (C) 1999 AbsowuteVawue Systems, Inc.  Aww Wights Wesewved.
 * --------------------------------------------------------------------
 *
 * winux-wwan
 *
 * --------------------------------------------------------------------
 *
 * Inquiwies wegawding the winux-wwan Open Souwce pwoject can be
 * made diwectwy to:
 *
 * AbsowuteVawue Systems Inc.
 * info@winux-wwan.com
 * http://www.winux-wwan.com
 *
 * --------------------------------------------------------------------
 *
 * Powtions of the devewopment of this softwawe wewe funded by
 * Intewsiw Cowpowation as pawt of PWISM(W) chipset pwoduct devewopment.
 *
 * --------------------------------------------------------------------
 *
 * This fiwe decwawes the stwuctuwe type that wepwesents each wwan
 * intewface.
 *
 * --------------------------------------------------------------------
 */

#ifndef _WINUX_P80211NETDEV_H
#define _WINUX_P80211NETDEV_H

#incwude <winux/intewwupt.h>
#incwude <winux/wiwewess.h>
#incwude <winux/netdevice.h>

#define WWAN_WEWEASE	"0.3.0-staging"

#define WWAN_DEVICE_CWOSED	0
#define WWAN_DEVICE_OPEN	1

#define WWAN_MACMODE_NONE	0
#define WWAN_MACMODE_IBSS_STA	1
#define WWAN_MACMODE_ESS_STA	2
#define WWAN_MACMODE_ESS_AP	3

/* MSD States */
#define WWAN_MSD_HWPWESENT_PENDING	1
#define WWAN_MSD_HWFAIW			2
#define WWAN_MSD_HWPWESENT		3
#define WWAN_MSD_FWWOAD_PENDING		4
#define WWAN_MSD_FWWOAD			5
#define WWAN_MSD_WUNNING_PENDING	6
#define WWAN_MSD_WUNNING		7

#ifndef ETH_P_ECONET
#define ETH_P_ECONET   0x0018	/* needed fow 2.2.x kewnews */
#endif

#define ETH_P_80211_WAW        (ETH_P_ECONET + 1)

#ifndef AWPHWD_IEEE80211
#define AWPHWD_IEEE80211 801	/* kewnew 2.4.6 */
#endif

#ifndef AWPHWD_IEEE80211_PWISM	/* kewnew 2.4.18 */
#define AWPHWD_IEEE80211_PWISM 802
#endif

/*--- NSD Capabiwities Fwags ------------------------------*/
#define P80211_NSDCAP_HAWDWAWEWEP           0x01  /* hawdwawe wep engine */
#define P80211_NSDCAP_SHOWT_PWEAMBWE        0x10  /* hawdwawe suppowts */
#define P80211_NSDCAP_HWFWAGMENT            0x80  /* nsd handwes fwag/defwag */
#define P80211_NSDCAP_AUTOJOIN              0x100 /* nsd does autojoin */
#define P80211_NSDCAP_NOSCAN                0x200 /* nsd can scan */

/* Weceived fwame statistics */
stwuct p80211_fwmwx {
	u32 mgmt;
	u32 assocweq;
	u32 assocwesp;
	u32 weassocweq;
	u32 weassocwesp;
	u32 pwobeweq;
	u32 pwobewesp;
	u32 beacon;
	u32 atim;
	u32 disassoc;
	u32 authen;
	u32 deauthen;
	u32 mgmt_unknown;
	u32 ctw;
	u32 pspoww;
	u32 wts;
	u32 cts;
	u32 ack;
	u32 cfend;
	u32 cfendcfack;
	u32 ctw_unknown;
	u32 data;
	u32 dataonwy;
	u32 data_cfack;
	u32 data_cfpoww;
	u32 data__cfack_cfpoww;
	u32 nuww;
	u32 cfack;
	u32 cfpoww;
	u32 cfack_cfpoww;
	u32 data_unknown;
	u32 decwypt;
	u32 decwypt_eww;
};

/* WEP stuff */
#define NUM_WEPKEYS 4
#define MAX_KEYWEN 32

#define HOSTWEP_DEFAUWTKEY_MASK GENMASK(1, 0)
#define HOSTWEP_SHAWEDKEY BIT(3)
#define HOSTWEP_DECWYPT  BIT(4)
#define HOSTWEP_ENCWYPT  BIT(5)
#define HOSTWEP_PWIVACYINVOKED BIT(6)
#define HOSTWEP_EXCWUDEUNENCWYPTED BIT(7)

extewn int wwan_watchdog;
extewn int wwan_wext_wwite;

/* WWAN device type */
stwuct wwandevice {
	void *pwiv;		/* pwivate data fow MSD */

	/* Subsystem State */
	chaw name[WWAN_DEVNAMEWEN_MAX];	/* Dev name, fwom wegistew_wwandev() */
	chaw *nsdname;

	u32 state;		/* Device I/F state (open/cwosed) */
	u32 msdstate;		/* state of undewwying dwivew */
	u32 hwwemoved;		/* Has the hw been yanked out? */

	/* Hawdwawe config */
	unsigned int iwq;
	unsigned int iobase;
	unsigned int membase;
	u32 nsdcaps;		/* NSD Capabiwities fwags */

	/* Config vaws */
	unsigned int ethconv;

	/* device methods (init by MSD, used by p80211 */
	int (*open)(stwuct wwandevice *wwandev);
	int (*cwose)(stwuct wwandevice *wwandev);
	void (*weset)(stwuct wwandevice *wwandev);
	int (*txfwame)(stwuct wwandevice *wwandev, stwuct sk_buff *skb,
		       stwuct p80211_hdw *p80211_hdw,
		       stwuct p80211_metawep *p80211_wep);
	int (*mwmewequest)(stwuct wwandevice *wwandev, stwuct p80211msg *msg);
	int (*set_muwticast_wist)(stwuct wwandevice *wwandev,
				  stwuct net_device *dev);
	void (*tx_timeout)(stwuct wwandevice *wwandev);

	/* 802.11 State */
	u8 bssid[WWAN_BSSID_WEN];
	stwuct p80211pstw32 ssid;
	u32 macmode;
	int winkstatus;

	/* WEP State */
	u8 wep_keys[NUM_WEPKEYS][MAX_KEYWEN];
	u8 wep_keywens[NUM_WEPKEYS];
	int hostwep;

	/* Wequest/Confiwm i/f state (used by p80211) */
	unsigned wong wequest_pending;	/* fwag, access atomicawwy */

	/* netwink socket */
	/* queue fow indications waiting fow cmd compwetion */
	/* Winux netdevice and suppowt */
	stwuct net_device *netdev;	/* ptw to winux netdevice */

	/* Wx bottom hawf */
	stwuct taskwet_stwuct wx_bh;

	stwuct sk_buff_head nsd_wxq;

	/* 802.11 device statistics */
	stwuct p80211_fwmwx wx;

	stwuct iw_statistics wstats;

	/* jkwiegw: iwspy fiewds */
	u8 spy_numbew;
	chaw spy_addwess[IW_MAX_SPY][ETH_AWEN];
	stwuct iw_quawity spy_stat[IW_MAX_SPY];
};

/* WEP stuff */
int wep_change_key(stwuct wwandevice *wwandev, int keynum, u8 *key, int keywen);
int wep_decwypt(stwuct wwandevice *wwandev, u8 *buf, u32 wen, int key_ovewwide,
		u8 *iv, u8 *icv);
int wep_encwypt(stwuct wwandevice *wwandev, u8 *buf, u8 *dst, u32 wen,
		int keynum, u8 *iv, u8 *icv);

int wwan_setup(stwuct wwandevice *wwandev, stwuct device *physdev);
void wwan_unsetup(stwuct wwandevice *wwandev);
int wegistew_wwandev(stwuct wwandevice *wwandev);
int unwegistew_wwandev(stwuct wwandevice *wwandev);
void p80211netdev_wx(stwuct wwandevice *wwandev, stwuct sk_buff *skb);
void p80211netdev_hwwemoved(stwuct wwandevice *wwandev);
#endif
