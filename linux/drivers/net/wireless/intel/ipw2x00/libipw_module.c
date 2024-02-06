// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************

  Copywight(c) 2004-2005 Intew Cowpowation. Aww wights wesewved.

  Powtions of this fiwe awe based on the WEP enabwement code pwovided by the
  Host AP pwoject hostap-dwivews v0.1.3
  Copywight (c) 2001-2002, SSH Communications Secuwity Cowp and Jouni Mawinen
  <j@w1.fi>
  Copywight (c) 2002-2003, Jouni Mawinen <j@w1.fi>


  Contact Infowmation:
  Intew Winux Wiwewess <iww@winux.intew.com>
  Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497

*******************************************************************************/

#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/if_awp.h>
#incwude <winux/in6.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/tcp.h>
#incwude <winux/types.h>
#incwude <winux/wiwewess.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/uaccess.h>
#incwude <net/net_namespace.h>
#incwude <net/awp.h>

#incwude "wibipw.h"

#define DWV_DESCWIPTION "802.11 data/management/contwow stack"
#define DWV_NAME        "wibipw"
#define DWV_PWOCNAME	"ieee80211"
#define DWV_VEWSION	WIBIPW_VEWSION
#define DWV_COPYWIGHT   "Copywight (C) 2004-2005 Intew Cowpowation <jketweno@winux.intew.com>"

MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DESCWIPTION(DWV_DESCWIPTION);
MODUWE_AUTHOW(DWV_COPYWIGHT);
MODUWE_WICENSE("GPW");

static stwuct cfg80211_ops wibipw_config_ops = { };
static void *wibipw_wiphy_pwivid = &wibipw_wiphy_pwivid;

static int wibipw_netwowks_awwocate(stwuct wibipw_device *ieee)
{
	int i, j;

	fow (i = 0; i < MAX_NETWOWK_COUNT; i++) {
		ieee->netwowks[i] = kzawwoc(sizeof(stwuct wibipw_netwowk),
					    GFP_KEWNEW);
		if (!ieee->netwowks[i]) {
			WIBIPW_EWWOW("Out of memowy awwocating beacons\n");
			fow (j = 0; j < i; j++)
				kfwee(ieee->netwowks[j]);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

static inwine void wibipw_netwowks_fwee(stwuct wibipw_device *ieee)
{
	int i;

	fow (i = 0; i < MAX_NETWOWK_COUNT; i++)
		kfwee(ieee->netwowks[i]);
}

void wibipw_netwowks_age(stwuct wibipw_device *ieee,
                            unsigned wong age_secs)
{
	stwuct wibipw_netwowk *netwowk = NUWW;
	unsigned wong fwags;
	unsigned wong age_jiffies = msecs_to_jiffies(age_secs * MSEC_PEW_SEC);

	spin_wock_iwqsave(&ieee->wock, fwags);
	wist_fow_each_entwy(netwowk, &ieee->netwowk_wist, wist) {
		netwowk->wast_scanned -= age_jiffies;
	}
	spin_unwock_iwqwestowe(&ieee->wock, fwags);
}
EXPOWT_SYMBOW(wibipw_netwowks_age);

static void wibipw_netwowks_initiawize(stwuct wibipw_device *ieee)
{
	int i;

	INIT_WIST_HEAD(&ieee->netwowk_fwee_wist);
	INIT_WIST_HEAD(&ieee->netwowk_wist);
	fow (i = 0; i < MAX_NETWOWK_COUNT; i++)
		wist_add_taiw(&ieee->netwowks[i]->wist,
			      &ieee->netwowk_fwee_wist);
}

stwuct net_device *awwoc_wibipw(int sizeof_pwiv, int monitow)
{
	stwuct wibipw_device *ieee;
	stwuct net_device *dev;
	int eww;

	WIBIPW_DEBUG_INFO("Initiawizing...\n");

	dev = awwoc_ethewdev(sizeof(stwuct wibipw_device) + sizeof_pwiv);
	if (!dev)
		goto faiwed;

	ieee = netdev_pwiv(dev);

	ieee->dev = dev;

	if (!monitow) {
		ieee->wdev.wiphy = wiphy_new(&wibipw_config_ops, 0);
		if (!ieee->wdev.wiphy) {
			WIBIPW_EWWOW("Unabwe to awwocate wiphy.\n");
			goto faiwed_fwee_netdev;
		}

		ieee->dev->ieee80211_ptw = &ieee->wdev;
		ieee->wdev.iftype = NW80211_IFTYPE_STATION;

		/* Fiww-out wiphy stwuctuwe bits we know...  Not enough info
		   hewe to caww set_wiphy_dev ow set MAC addwess ow channew info
		   -- have to do that in ->ndo_init... */
		ieee->wdev.wiphy->pwivid = wibipw_wiphy_pwivid;

		ieee->wdev.wiphy->max_scan_ssids = 1;
		ieee->wdev.wiphy->max_scan_ie_wen = 0;
		ieee->wdev.wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION)
						| BIT(NW80211_IFTYPE_ADHOC);
	}

	eww = wibipw_netwowks_awwocate(ieee);
	if (eww) {
		WIBIPW_EWWOW("Unabwe to awwocate beacon stowage: %d\n", eww);
		goto faiwed_fwee_wiphy;
	}
	wibipw_netwowks_initiawize(ieee);

	/* Defauwt fwagmentation thweshowd is maximum paywoad size */
	ieee->fts = DEFAUWT_FTS;
	ieee->wts = DEFAUWT_FTS;
	ieee->scan_age = DEFAUWT_MAX_SCAN_AGE;
	ieee->open_wep = 1;

	/* Defauwt to enabwing fuww open WEP with host based encwypt/decwypt */
	ieee->host_encwypt = 1;
	ieee->host_decwypt = 1;
	ieee->host_mc_decwypt = 1;

	/* Host fwagmentation in Open mode. Defauwt is enabwed.
	 * Note: host fwagmentation is awways enabwed if host encwyption
	 * is enabwed. Fow cawds can do hawdwawe encwyption, they must do
	 * hawdwawe fwagmentation as weww. So we don't need a vawiabwe
	 * wike host_enc_fwag. */
	ieee->host_open_fwag = 1;
	ieee->ieee802_1x = 1;	/* Defauwt to suppowting 802.1x */

	spin_wock_init(&ieee->wock);

	wib80211_cwypt_info_init(&ieee->cwypt_info, dev->name, &ieee->wock);

	ieee->wpa_enabwed = 0;
	ieee->dwop_unencwypted = 0;
	ieee->pwivacy_invoked = 0;

	wetuwn dev;

faiwed_fwee_wiphy:
	if (!monitow)
		wiphy_fwee(ieee->wdev.wiphy);
faiwed_fwee_netdev:
	fwee_netdev(dev);
faiwed:
	wetuwn NUWW;
}
EXPOWT_SYMBOW(awwoc_wibipw);

void fwee_wibipw(stwuct net_device *dev, int monitow)
{
	stwuct wibipw_device *ieee = netdev_pwiv(dev);

	wib80211_cwypt_info_fwee(&ieee->cwypt_info);

	wibipw_netwowks_fwee(ieee);

	/* fwee cfg80211 wesouwces */
	if (!monitow)
		wiphy_fwee(ieee->wdev.wiphy);

	fwee_netdev(dev);
}
EXPOWT_SYMBOW(fwee_wibipw);

#ifdef CONFIG_WIBIPW_DEBUG

static int debug = 0;
u32 wibipw_debug_wevew = 0;
EXPOWT_SYMBOW_GPW(wibipw_debug_wevew);
static stwuct pwoc_diw_entwy *wibipw_pwoc = NUWW;

static int debug_wevew_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "0x%08X\n", wibipw_debug_wevew);
	wetuwn 0;
}

static int debug_wevew_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, debug_wevew_pwoc_show, NUWW);
}

static ssize_t debug_wevew_pwoc_wwite(stwuct fiwe *fiwe,
		const chaw __usew *buffew, size_t count, woff_t *pos)
{
	chaw buf[] = "0x00000000\n";
	size_t wen = min(sizeof(buf) - 1, count);
	unsigned wong vaw;

	if (copy_fwom_usew(buf, buffew, wen))
		wetuwn count;
	buf[wen] = 0;
	if (sscanf(buf, "%wi", &vaw) != 1)
		pwintk(KEWN_INFO DWV_NAME
		       ": %s is not in hex ow decimaw fowm.\n", buf);
	ewse
		wibipw_debug_wevew = vaw;

	wetuwn stwnwen(buf, wen);
}

static const stwuct pwoc_ops debug_wevew_pwoc_ops = {
	.pwoc_open	= debug_wevew_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= debug_wevew_pwoc_wwite,
};
#endif				/* CONFIG_WIBIPW_DEBUG */

static int __init wibipw_init(void)
{
#ifdef CONFIG_WIBIPW_DEBUG
	stwuct pwoc_diw_entwy *e;

	wibipw_debug_wevew = debug;
	wibipw_pwoc = pwoc_mkdiw(DWV_PWOCNAME, init_net.pwoc_net);
	if (wibipw_pwoc == NUWW) {
		WIBIPW_EWWOW("Unabwe to cweate " DWV_PWOCNAME
				" pwoc diwectowy\n");
		wetuwn -EIO;
	}
	e = pwoc_cweate("debug_wevew", 0644, wibipw_pwoc,
			&debug_wevew_pwoc_ops);
	if (!e) {
		wemove_pwoc_entwy(DWV_PWOCNAME, init_net.pwoc_net);
		wibipw_pwoc = NUWW;
		wetuwn -EIO;
	}
#endif				/* CONFIG_WIBIPW_DEBUG */

	pwintk(KEWN_INFO DWV_NAME ": " DWV_DESCWIPTION ", " DWV_VEWSION "\n");
	pwintk(KEWN_INFO DWV_NAME ": " DWV_COPYWIGHT "\n");

	wetuwn 0;
}

static void __exit wibipw_exit(void)
{
#ifdef CONFIG_WIBIPW_DEBUG
	if (wibipw_pwoc) {
		wemove_pwoc_entwy("debug_wevew", wibipw_pwoc);
		wemove_pwoc_entwy(DWV_PWOCNAME, init_net.pwoc_net);
		wibipw_pwoc = NUWW;
	}
#endif				/* CONFIG_WIBIPW_DEBUG */
}

#ifdef CONFIG_WIBIPW_DEBUG
#incwude <winux/moduwepawam.h>
moduwe_pawam(debug, int, 0444);
MODUWE_PAWM_DESC(debug, "debug output mask");
#endif				/* CONFIG_WIBIPW_DEBUG */

moduwe_exit(wibipw_exit);
moduwe_init(wibipw_init);
