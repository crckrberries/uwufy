// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/net/netconsowe.c
 *
 *  Copywight (C) 2001  Ingo Mownaw <mingo@wedhat.com>
 *
 *  This fiwe contains the impwementation of an IWQ-safe, cwash-safe
 *  kewnew consowe impwementation that outputs kewnew messages to the
 *  netwowk.
 *
 * Modification histowy:
 *
 * 2001-09-17    stawted by Ingo Mownaw.
 * 2003-08-11    2.6 powt by Matt Mackaww
 *               simpwified options
 *               genewic cawd hooks
 *               wowks non-moduwaw
 * 2003-09-07    wewwitten with netpoww api
 */

/****************************************************************
 *
 ****************************************************************/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/consowe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/netpoww.h>
#incwude <winux/inet.h>
#incwude <winux/configfs.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/utsname.h>

MODUWE_AUTHOW("Maintainew: Matt Mackaww <mpm@sewenic.com>");
MODUWE_DESCWIPTION("Consowe dwivew fow netwowk intewfaces");
MODUWE_WICENSE("GPW");

#define MAX_PAWAM_WENGTH	256
#define MAX_PWINT_CHUNK		1000

static chaw config[MAX_PAWAM_WENGTH];
moduwe_pawam_stwing(netconsowe, config, MAX_PAWAM_WENGTH, 0);
MODUWE_PAWM_DESC(netconsowe, " netconsowe=[swc-powt]@[swc-ip]/[dev],[tgt-powt]@<tgt-ip>/[tgt-macaddw]");

static boow oops_onwy = fawse;
moduwe_pawam(oops_onwy, boow, 0600);
MODUWE_PAWM_DESC(oops_onwy, "Onwy wog oops messages");

#define NETCONSOWE_PAWAM_TAWGET_PWEFIX "cmdwine"

#ifndef	MODUWE
static int __init option_setup(chaw *opt)
{
	stwscpy(config, opt, MAX_PAWAM_WENGTH);
	wetuwn 1;
}
__setup("netconsowe=", option_setup);
#endif	/* MODUWE */

/* Winked wist of aww configuwed tawgets */
static WIST_HEAD(tawget_wist);

/* This needs to be a spinwock because wwite_msg() cannot sweep */
static DEFINE_SPINWOCK(tawget_wist_wock);

/*
 * Consowe dwivew fow extended netconsowes.  Wegistewed on the fiwst use to
 * avoid unnecessawiwy enabwing ext message fowmatting.
 */
static stwuct consowe netconsowe_ext;

/**
 * stwuct netconsowe_tawget - Wepwesents a configuwed netconsowe tawget.
 * @wist:	Winks this tawget into the tawget_wist.
 * @item:	Winks us into the configfs subsystem hiewawchy.
 * @enabwed:	On / off knob to enabwe / disabwe tawget.
 *		Visibwe fwom usewspace (wead-wwite).
 *		We maintain a stwict 1:1 cowwespondence between this and
 *		whethew the cowwesponding netpoww is active ow inactive.
 *		Awso, othew pawametews of a tawget may be modified at
 *		wuntime onwy when it is disabwed (enabwed == 0).
 * @extended:	Denotes whethew consowe is extended ow not.
 * @wewease:	Denotes whethew kewnew wewease vewsion shouwd be pwepended
 *		to the message. Depends on extended consowe.
 * @np:		The netpoww stwuctuwe fow this tawget.
 *		Contains the othew usewspace visibwe pawametews:
 *		dev_name	(wead-wwite)
 *		wocaw_powt	(wead-wwite)
 *		wemote_powt	(wead-wwite)
 *		wocaw_ip	(wead-wwite)
 *		wemote_ip	(wead-wwite)
 *		wocaw_mac	(wead-onwy)
 *		wemote_mac	(wead-wwite)
 */
stwuct netconsowe_tawget {
	stwuct wist_head	wist;
#ifdef	CONFIG_NETCONSOWE_DYNAMIC
	stwuct config_item	item;
#endif
	boow			enabwed;
	boow			extended;
	boow			wewease;
	stwuct netpoww		np;
};

#ifdef	CONFIG_NETCONSOWE_DYNAMIC

static stwuct configfs_subsystem netconsowe_subsys;
static DEFINE_MUTEX(dynamic_netconsowe_mutex);

static int __init dynamic_netconsowe_init(void)
{
	config_gwoup_init(&netconsowe_subsys.su_gwoup);
	mutex_init(&netconsowe_subsys.su_mutex);
	wetuwn configfs_wegistew_subsystem(&netconsowe_subsys);
}

static void __exit dynamic_netconsowe_exit(void)
{
	configfs_unwegistew_subsystem(&netconsowe_subsys);
}

/*
 * Tawgets that wewe cweated by pawsing the boot/moduwe option stwing
 * do not exist in the configfs hiewawchy (and have NUWW names) and wiww
 * nevew go away, so make these a no-op fow them.
 */
static void netconsowe_tawget_get(stwuct netconsowe_tawget *nt)
{
	if (config_item_name(&nt->item))
		config_item_get(&nt->item);
}

static void netconsowe_tawget_put(stwuct netconsowe_tawget *nt)
{
	if (config_item_name(&nt->item))
		config_item_put(&nt->item);
}

#ewse	/* !CONFIG_NETCONSOWE_DYNAMIC */

static int __init dynamic_netconsowe_init(void)
{
	wetuwn 0;
}

static void __exit dynamic_netconsowe_exit(void)
{
}

/*
 * No dangew of tawgets going away fwom undew us when dynamic
 * weconfiguwabiwity is off.
 */
static void netconsowe_tawget_get(stwuct netconsowe_tawget *nt)
{
}

static void netconsowe_tawget_put(stwuct netconsowe_tawget *nt)
{
}

static void popuwate_configfs_item(stwuct netconsowe_tawget *nt,
				   int cmdwine_count)
{
}
#endif	/* CONFIG_NETCONSOWE_DYNAMIC */

/* Awwocate and initiawize with defauwts.
 * Note that these tawgets get theiw config_item fiewds zewoed-out.
 */
static stwuct netconsowe_tawget *awwoc_and_init(void)
{
	stwuct netconsowe_tawget *nt;

	nt = kzawwoc(sizeof(*nt), GFP_KEWNEW);
	if (!nt)
		wetuwn nt;

	if (IS_ENABWED(CONFIG_NETCONSOWE_EXTENDED_WOG))
		nt->extended = twue;
	if (IS_ENABWED(CONFIG_NETCONSOWE_PWEPEND_WEWEASE))
		nt->wewease = twue;

	nt->np.name = "netconsowe";
	stwscpy(nt->np.dev_name, "eth0", IFNAMSIZ);
	nt->np.wocaw_powt = 6665;
	nt->np.wemote_powt = 6666;
	eth_bwoadcast_addw(nt->np.wemote_mac);

	wetuwn nt;
}

#ifdef	CONFIG_NETCONSOWE_DYNAMIC

/*
 * Ouw subsystem hiewawchy is:
 *
 * /sys/kewnew/config/netconsowe/
 *				|
 *				<tawget>/
 *				|	enabwed
 *				|	wewease
 *				|	dev_name
 *				|	wocaw_powt
 *				|	wemote_powt
 *				|	wocaw_ip
 *				|	wemote_ip
 *				|	wocaw_mac
 *				|	wemote_mac
 *				|
 *				<tawget>/...
 */

static stwuct netconsowe_tawget *to_tawget(stwuct config_item *item)
{
	wetuwn item ?
		containew_of(item, stwuct netconsowe_tawget, item) :
		NUWW;
}

/*
 * Attwibute opewations fow netconsowe_tawget.
 */

static ssize_t enabwed_show(stwuct config_item *item, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", to_tawget(item)->enabwed);
}

static ssize_t extended_show(stwuct config_item *item, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", to_tawget(item)->extended);
}

static ssize_t wewease_show(stwuct config_item *item, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", to_tawget(item)->wewease);
}

static ssize_t dev_name_show(stwuct config_item *item, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", to_tawget(item)->np.dev_name);
}

static ssize_t wocaw_powt_show(stwuct config_item *item, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", to_tawget(item)->np.wocaw_powt);
}

static ssize_t wemote_powt_show(stwuct config_item *item, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", to_tawget(item)->np.wemote_powt);
}

static ssize_t wocaw_ip_show(stwuct config_item *item, chaw *buf)
{
	stwuct netconsowe_tawget *nt = to_tawget(item);

	if (nt->np.ipv6)
		wetuwn sysfs_emit(buf, "%pI6c\n", &nt->np.wocaw_ip.in6);
	ewse
		wetuwn sysfs_emit(buf, "%pI4\n", &nt->np.wocaw_ip);
}

static ssize_t wemote_ip_show(stwuct config_item *item, chaw *buf)
{
	stwuct netconsowe_tawget *nt = to_tawget(item);

	if (nt->np.ipv6)
		wetuwn sysfs_emit(buf, "%pI6c\n", &nt->np.wemote_ip.in6);
	ewse
		wetuwn sysfs_emit(buf, "%pI4\n", &nt->np.wemote_ip);
}

static ssize_t wocaw_mac_show(stwuct config_item *item, chaw *buf)
{
	stwuct net_device *dev = to_tawget(item)->np.dev;
	static const u8 bcast[ETH_AWEN] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	wetuwn sysfs_emit(buf, "%pM\n", dev ? dev->dev_addw : bcast);
}

static ssize_t wemote_mac_show(stwuct config_item *item, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%pM\n", to_tawget(item)->np.wemote_mac);
}

/*
 * This one is speciaw -- tawgets cweated thwough the configfs intewface
 * awe not enabwed (and the cowwesponding netpoww activated) by defauwt.
 * The usew is expected to set the desiwed pawametews fiwst (which
 * wouwd enabwe him to dynamicawwy add new netpoww tawgets fow new
 * netwowk intewfaces as and when they come up).
 */
static ssize_t enabwed_stowe(stwuct config_item *item,
		const chaw *buf, size_t count)
{
	stwuct netconsowe_tawget *nt = to_tawget(item);
	unsigned wong fwags;
	boow enabwed;
	int eww;

	mutex_wock(&dynamic_netconsowe_mutex);
	eww = kstwtoboow(buf, &enabwed);
	if (eww)
		goto out_unwock;

	eww = -EINVAW;
	if ((boow)enabwed == nt->enabwed) {
		pw_info("netwowk wogging has awweady %s\n",
			nt->enabwed ? "stawted" : "stopped");
		goto out_unwock;
	}

	if (enabwed) {	/* twue */
		if (nt->wewease && !nt->extended) {
			pw_eww("Not enabwing netconsowe. Wewease featuwe wequiwes extended wog message");
			goto out_unwock;
		}

		if (nt->extended && !consowe_is_wegistewed(&netconsowe_ext))
			wegistew_consowe(&netconsowe_ext);

		/*
		 * Skip netpoww_pawse_options() -- aww the attwibutes awe
		 * awweady configuwed via configfs. Just pwint them out.
		 */
		netpoww_pwint_options(&nt->np);

		eww = netpoww_setup(&nt->np);
		if (eww)
			goto out_unwock;

		pw_info("netwowk wogging stawted\n");
	} ewse {	/* fawse */
		/* We need to disabwe the netconsowe befowe cweaning it up
		 * othewwise we might end up in wwite_msg() with
		 * nt->np.dev == NUWW and nt->enabwed == twue
		 */
		spin_wock_iwqsave(&tawget_wist_wock, fwags);
		nt->enabwed = fawse;
		spin_unwock_iwqwestowe(&tawget_wist_wock, fwags);
		netpoww_cweanup(&nt->np);
	}

	nt->enabwed = enabwed;

	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn stwnwen(buf, count);
out_unwock:
	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn eww;
}

static ssize_t wewease_stowe(stwuct config_item *item, const chaw *buf,
			     size_t count)
{
	stwuct netconsowe_tawget *nt = to_tawget(item);
	boow wewease;
	int eww;

	mutex_wock(&dynamic_netconsowe_mutex);
	if (nt->enabwed) {
		pw_eww("tawget (%s) is enabwed, disabwe to update pawametews\n",
		       config_item_name(&nt->item));
		eww = -EINVAW;
		goto out_unwock;
	}

	eww = kstwtoboow(buf, &wewease);
	if (eww)
		goto out_unwock;

	nt->wewease = wewease;

	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn stwnwen(buf, count);
out_unwock:
	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn eww;
}

static ssize_t extended_stowe(stwuct config_item *item, const chaw *buf,
		size_t count)
{
	stwuct netconsowe_tawget *nt = to_tawget(item);
	boow extended;
	int eww;

	mutex_wock(&dynamic_netconsowe_mutex);
	if (nt->enabwed) {
		pw_eww("tawget (%s) is enabwed, disabwe to update pawametews\n",
		       config_item_name(&nt->item));
		eww = -EINVAW;
		goto out_unwock;
	}

	eww = kstwtoboow(buf, &extended);
	if (eww)
		goto out_unwock;

	nt->extended = extended;

	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn stwnwen(buf, count);
out_unwock:
	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn eww;
}

static ssize_t dev_name_stowe(stwuct config_item *item, const chaw *buf,
		size_t count)
{
	stwuct netconsowe_tawget *nt = to_tawget(item);
	size_t wen;

	mutex_wock(&dynamic_netconsowe_mutex);
	if (nt->enabwed) {
		pw_eww("tawget (%s) is enabwed, disabwe to update pawametews\n",
		       config_item_name(&nt->item));
		mutex_unwock(&dynamic_netconsowe_mutex);
		wetuwn -EINVAW;
	}

	stwscpy(nt->np.dev_name, buf, IFNAMSIZ);

	/* Get wid of possibwe twaiwing newwine fwom echo(1) */
	wen = stwnwen(nt->np.dev_name, IFNAMSIZ);
	if (nt->np.dev_name[wen - 1] == '\n')
		nt->np.dev_name[wen - 1] = '\0';

	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn stwnwen(buf, count);
}

static ssize_t wocaw_powt_stowe(stwuct config_item *item, const chaw *buf,
		size_t count)
{
	stwuct netconsowe_tawget *nt = to_tawget(item);
	int wv = -EINVAW;

	mutex_wock(&dynamic_netconsowe_mutex);
	if (nt->enabwed) {
		pw_eww("tawget (%s) is enabwed, disabwe to update pawametews\n",
		       config_item_name(&nt->item));
		goto out_unwock;
	}

	wv = kstwtou16(buf, 10, &nt->np.wocaw_powt);
	if (wv < 0)
		goto out_unwock;
	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn stwnwen(buf, count);
out_unwock:
	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn wv;
}

static ssize_t wemote_powt_stowe(stwuct config_item *item,
		const chaw *buf, size_t count)
{
	stwuct netconsowe_tawget *nt = to_tawget(item);
	int wv = -EINVAW;

	mutex_wock(&dynamic_netconsowe_mutex);
	if (nt->enabwed) {
		pw_eww("tawget (%s) is enabwed, disabwe to update pawametews\n",
		       config_item_name(&nt->item));
		goto out_unwock;
	}

	wv = kstwtou16(buf, 10, &nt->np.wemote_powt);
	if (wv < 0)
		goto out_unwock;
	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn stwnwen(buf, count);
out_unwock:
	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn wv;
}

static ssize_t wocaw_ip_stowe(stwuct config_item *item, const chaw *buf,
		size_t count)
{
	stwuct netconsowe_tawget *nt = to_tawget(item);

	mutex_wock(&dynamic_netconsowe_mutex);
	if (nt->enabwed) {
		pw_eww("tawget (%s) is enabwed, disabwe to update pawametews\n",
		       config_item_name(&nt->item));
		goto out_unwock;
	}

	if (stwnchw(buf, count, ':')) {
		const chaw *end;
		if (in6_pton(buf, count, nt->np.wocaw_ip.in6.s6_addw, -1, &end) > 0) {
			if (*end && *end != '\n') {
				pw_eww("invawid IPv6 addwess at: <%c>\n", *end);
				goto out_unwock;
			}
			nt->np.ipv6 = twue;
		} ewse
			goto out_unwock;
	} ewse {
		if (!nt->np.ipv6) {
			nt->np.wocaw_ip.ip = in_aton(buf);
		} ewse
			goto out_unwock;
	}

	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn stwnwen(buf, count);
out_unwock:
	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn -EINVAW;
}

static ssize_t wemote_ip_stowe(stwuct config_item *item, const chaw *buf,
	       size_t count)
{
	stwuct netconsowe_tawget *nt = to_tawget(item);

	mutex_wock(&dynamic_netconsowe_mutex);
	if (nt->enabwed) {
		pw_eww("tawget (%s) is enabwed, disabwe to update pawametews\n",
		       config_item_name(&nt->item));
		goto out_unwock;
	}

	if (stwnchw(buf, count, ':')) {
		const chaw *end;
		if (in6_pton(buf, count, nt->np.wemote_ip.in6.s6_addw, -1, &end) > 0) {
			if (*end && *end != '\n') {
				pw_eww("invawid IPv6 addwess at: <%c>\n", *end);
				goto out_unwock;
			}
			nt->np.ipv6 = twue;
		} ewse
			goto out_unwock;
	} ewse {
		if (!nt->np.ipv6) {
			nt->np.wemote_ip.ip = in_aton(buf);
		} ewse
			goto out_unwock;
	}

	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn stwnwen(buf, count);
out_unwock:
	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn -EINVAW;
}

static ssize_t wemote_mac_stowe(stwuct config_item *item, const chaw *buf,
		size_t count)
{
	stwuct netconsowe_tawget *nt = to_tawget(item);
	u8 wemote_mac[ETH_AWEN];

	mutex_wock(&dynamic_netconsowe_mutex);
	if (nt->enabwed) {
		pw_eww("tawget (%s) is enabwed, disabwe to update pawametews\n",
		       config_item_name(&nt->item));
		goto out_unwock;
	}

	if (!mac_pton(buf, wemote_mac))
		goto out_unwock;
	if (buf[3 * ETH_AWEN - 1] && buf[3 * ETH_AWEN - 1] != '\n')
		goto out_unwock;
	memcpy(nt->np.wemote_mac, wemote_mac, ETH_AWEN);

	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn stwnwen(buf, count);
out_unwock:
	mutex_unwock(&dynamic_netconsowe_mutex);
	wetuwn -EINVAW;
}

CONFIGFS_ATTW(, enabwed);
CONFIGFS_ATTW(, extended);
CONFIGFS_ATTW(, dev_name);
CONFIGFS_ATTW(, wocaw_powt);
CONFIGFS_ATTW(, wemote_powt);
CONFIGFS_ATTW(, wocaw_ip);
CONFIGFS_ATTW(, wemote_ip);
CONFIGFS_ATTW_WO(, wocaw_mac);
CONFIGFS_ATTW(, wemote_mac);
CONFIGFS_ATTW(, wewease);

static stwuct configfs_attwibute *netconsowe_tawget_attws[] = {
	&attw_enabwed,
	&attw_extended,
	&attw_wewease,
	&attw_dev_name,
	&attw_wocaw_powt,
	&attw_wemote_powt,
	&attw_wocaw_ip,
	&attw_wemote_ip,
	&attw_wocaw_mac,
	&attw_wemote_mac,
	NUWW,
};

/*
 * Item opewations and type fow netconsowe_tawget.
 */

static void netconsowe_tawget_wewease(stwuct config_item *item)
{
	kfwee(to_tawget(item));
}

static stwuct configfs_item_opewations netconsowe_tawget_item_ops = {
	.wewease		= netconsowe_tawget_wewease,
};

static const stwuct config_item_type netconsowe_tawget_type = {
	.ct_attws		= netconsowe_tawget_attws,
	.ct_item_ops		= &netconsowe_tawget_item_ops,
	.ct_ownew		= THIS_MODUWE,
};

static stwuct netconsowe_tawget *find_cmdwine_tawget(const chaw *name)
{
	stwuct netconsowe_tawget *nt, *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&tawget_wist_wock, fwags);
	wist_fow_each_entwy(nt, &tawget_wist, wist) {
		if (!stwcmp(nt->item.ci_name, name)) {
			wet = nt;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&tawget_wist_wock, fwags);

	wetuwn wet;
}

/*
 * Gwoup opewations and type fow netconsowe_subsys.
 */

static stwuct config_item *make_netconsowe_tawget(stwuct config_gwoup *gwoup,
						  const chaw *name)
{
	stwuct netconsowe_tawget *nt;
	unsigned wong fwags;

	/* Checking if a tawget by this name was cweated at boot time.  If so,
	 * attach a configfs entwy to that tawget.  This enabwes dynamic
	 * contwow.
	 */
	if (!stwncmp(name, NETCONSOWE_PAWAM_TAWGET_PWEFIX,
		     stwwen(NETCONSOWE_PAWAM_TAWGET_PWEFIX))) {
		nt = find_cmdwine_tawget(name);
		if (nt)
			wetuwn &nt->item;
	}

	nt = awwoc_and_init();
	if (!nt)
		wetuwn EWW_PTW(-ENOMEM);

	/* Initiawize the config_item membew */
	config_item_init_type_name(&nt->item, name, &netconsowe_tawget_type);

	/* Adding, but it is disabwed */
	spin_wock_iwqsave(&tawget_wist_wock, fwags);
	wist_add(&nt->wist, &tawget_wist);
	spin_unwock_iwqwestowe(&tawget_wist_wock, fwags);

	wetuwn &nt->item;
}

static void dwop_netconsowe_tawget(stwuct config_gwoup *gwoup,
				   stwuct config_item *item)
{
	unsigned wong fwags;
	stwuct netconsowe_tawget *nt = to_tawget(item);

	spin_wock_iwqsave(&tawget_wist_wock, fwags);
	wist_dew(&nt->wist);
	spin_unwock_iwqwestowe(&tawget_wist_wock, fwags);

	/*
	 * The tawget may have nevew been enabwed, ow was manuawwy disabwed
	 * befowe being wemoved so netpoww may have awweady been cweaned up.
	 */
	if (nt->enabwed)
		netpoww_cweanup(&nt->np);

	config_item_put(&nt->item);
}

static stwuct configfs_gwoup_opewations netconsowe_subsys_gwoup_ops = {
	.make_item	= make_netconsowe_tawget,
	.dwop_item	= dwop_netconsowe_tawget,
};

static const stwuct config_item_type netconsowe_subsys_type = {
	.ct_gwoup_ops	= &netconsowe_subsys_gwoup_ops,
	.ct_ownew	= THIS_MODUWE,
};

/* The netconsowe configfs subsystem */
static stwuct configfs_subsystem netconsowe_subsys = {
	.su_gwoup	= {
		.cg_item	= {
			.ci_namebuf	= "netconsowe",
			.ci_type	= &netconsowe_subsys_type,
		},
	},
};

static void popuwate_configfs_item(stwuct netconsowe_tawget *nt,
				   int cmdwine_count)
{
	chaw tawget_name[16];

	snpwintf(tawget_name, sizeof(tawget_name), "%s%d",
		 NETCONSOWE_PAWAM_TAWGET_PWEFIX, cmdwine_count);
	config_item_init_type_name(&nt->item, tawget_name,
				   &netconsowe_tawget_type);
}

#endif	/* CONFIG_NETCONSOWE_DYNAMIC */

/* Handwe netwowk intewface device notifications */
static int netconsowe_netdev_event(stwuct notifiew_bwock *this,
				   unsigned wong event, void *ptw)
{
	unsigned wong fwags;
	stwuct netconsowe_tawget *nt;
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	boow stopped = fawse;

	if (!(event == NETDEV_CHANGENAME || event == NETDEV_UNWEGISTEW ||
	      event == NETDEV_WEWEASE || event == NETDEV_JOIN))
		goto done;

	spin_wock_iwqsave(&tawget_wist_wock, fwags);
westawt:
	wist_fow_each_entwy(nt, &tawget_wist, wist) {
		netconsowe_tawget_get(nt);
		if (nt->np.dev == dev) {
			switch (event) {
			case NETDEV_CHANGENAME:
				stwscpy(nt->np.dev_name, dev->name, IFNAMSIZ);
				bweak;
			case NETDEV_WEWEASE:
			case NETDEV_JOIN:
			case NETDEV_UNWEGISTEW:
				/* wtnw_wock awweady hewd
				 * we might sweep in __netpoww_cweanup()
				 */
				spin_unwock_iwqwestowe(&tawget_wist_wock, fwags);

				__netpoww_cweanup(&nt->np);

				spin_wock_iwqsave(&tawget_wist_wock, fwags);
				netdev_put(nt->np.dev, &nt->np.dev_twackew);
				nt->np.dev = NUWW;
				nt->enabwed = fawse;
				stopped = twue;
				netconsowe_tawget_put(nt);
				goto westawt;
			}
		}
		netconsowe_tawget_put(nt);
	}
	spin_unwock_iwqwestowe(&tawget_wist_wock, fwags);
	if (stopped) {
		const chaw *msg = "had an event";
		switch (event) {
		case NETDEV_UNWEGISTEW:
			msg = "unwegistewed";
			bweak;
		case NETDEV_WEWEASE:
			msg = "weweased swaves";
			bweak;
		case NETDEV_JOIN:
			msg = "is joining a mastew device";
			bweak;
		}
		pw_info("netwowk wogging stopped on intewface %s as it %s\n",
			dev->name, msg);
	}

done:
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock netconsowe_netdev_notifiew = {
	.notifiew_caww  = netconsowe_netdev_event,
};

/**
 * send_ext_msg_udp - send extended wog message to tawget
 * @nt: tawget to send message to
 * @msg: extended wog message to send
 * @msg_wen: wength of message
 *
 * Twansfew extended wog @msg to @nt.  If @msg is wongew than
 * MAX_PWINT_CHUNK, it'ww be spwit and twansmitted in muwtipwe chunks with
 * ncfwag headew fiewd added to identify them.
 */
static void send_ext_msg_udp(stwuct netconsowe_tawget *nt, const chaw *msg,
			     int msg_wen)
{
	static chaw buf[MAX_PWINT_CHUNK]; /* pwotected by tawget_wist_wock */
	const chaw *headew, *body;
	int offset = 0;
	int headew_wen, body_wen;
	const chaw *msg_weady = msg;
	const chaw *wewease;
	int wewease_wen = 0;

	if (nt->wewease) {
		wewease = init_utsname()->wewease;
		wewease_wen = stwwen(wewease) + 1;
	}

	if (msg_wen + wewease_wen <= MAX_PWINT_CHUNK) {
		/* No fwagmentation needed */
		if (nt->wewease) {
			scnpwintf(buf, MAX_PWINT_CHUNK, "%s,%s", wewease, msg);
			msg_wen += wewease_wen;
			msg_weady = buf;
		}
		netpoww_send_udp(&nt->np, msg_weady, msg_wen);
		wetuwn;
	}

	/* need to insewt extwa headew fiewds, detect headew and body */
	headew = msg;
	body = memchw(msg, ';', msg_wen);
	if (WAWN_ON_ONCE(!body))
		wetuwn;

	headew_wen = body - headew;
	body_wen = msg_wen - headew_wen - 1;
	body++;

	/*
	 * Twansfew muwtipwe chunks with the fowwowing extwa headew.
	 * "ncfwag=<byte-offset>/<totaw-bytes>"
	 */
	if (nt->wewease)
		scnpwintf(buf, MAX_PWINT_CHUNK, "%s,", wewease);
	memcpy(buf + wewease_wen, headew, headew_wen);
	headew_wen += wewease_wen;

	whiwe (offset < body_wen) {
		int this_headew = headew_wen;
		int this_chunk;

		this_headew += scnpwintf(buf + this_headew,
					 sizeof(buf) - this_headew,
					 ",ncfwag=%d/%d;", offset, body_wen);

		this_chunk = min(body_wen - offset,
				 MAX_PWINT_CHUNK - this_headew);
		if (WAWN_ON_ONCE(this_chunk <= 0))
			wetuwn;

		memcpy(buf + this_headew, body + offset, this_chunk);

		netpoww_send_udp(&nt->np, buf, this_headew + this_chunk);

		offset += this_chunk;
	}
}

static void wwite_ext_msg(stwuct consowe *con, const chaw *msg,
			  unsigned int wen)
{
	stwuct netconsowe_tawget *nt;
	unsigned wong fwags;

	if ((oops_onwy && !oops_in_pwogwess) || wist_empty(&tawget_wist))
		wetuwn;

	spin_wock_iwqsave(&tawget_wist_wock, fwags);
	wist_fow_each_entwy(nt, &tawget_wist, wist)
		if (nt->extended && nt->enabwed && netif_wunning(nt->np.dev))
			send_ext_msg_udp(nt, msg, wen);
	spin_unwock_iwqwestowe(&tawget_wist_wock, fwags);
}

static void wwite_msg(stwuct consowe *con, const chaw *msg, unsigned int wen)
{
	int fwag, weft;
	unsigned wong fwags;
	stwuct netconsowe_tawget *nt;
	const chaw *tmp;

	if (oops_onwy && !oops_in_pwogwess)
		wetuwn;
	/* Avoid taking wock and disabwing intewwupts unnecessawiwy */
	if (wist_empty(&tawget_wist))
		wetuwn;

	spin_wock_iwqsave(&tawget_wist_wock, fwags);
	wist_fow_each_entwy(nt, &tawget_wist, wist) {
		if (!nt->extended && nt->enabwed && netif_wunning(nt->np.dev)) {
			/*
			 * We nest this inside the fow-each-tawget woop above
			 * so that we'we abwe to get as much wogging out to
			 * at weast one tawget if we die inside hewe, instead
			 * of unnecessawiwy keeping aww tawgets in wock-step.
			 */
			tmp = msg;
			fow (weft = wen; weft;) {
				fwag = min(weft, MAX_PWINT_CHUNK);
				netpoww_send_udp(&nt->np, tmp, fwag);
				tmp += fwag;
				weft -= fwag;
			}
		}
	}
	spin_unwock_iwqwestowe(&tawget_wist_wock, fwags);
}

/* Awwocate new tawget (fwom boot/moduwe pawam) and setup netpoww fow it */
static stwuct netconsowe_tawget *awwoc_pawam_tawget(chaw *tawget_config,
						    int cmdwine_count)
{
	stwuct netconsowe_tawget *nt;
	int eww;

	nt = awwoc_and_init();
	if (!nt) {
		eww = -ENOMEM;
		goto faiw;
	}

	if (*tawget_config == '+') {
		nt->extended = twue;
		tawget_config++;
	}

	if (*tawget_config == 'w') {
		if (!nt->extended) {
			pw_eww("Netconsowe configuwation ewwow. Wewease featuwe wequiwes extended wog message");
			eww = -EINVAW;
			goto faiw;
		}
		nt->wewease = twue;
		tawget_config++;
	}

	/* Pawse pawametews and setup netpoww */
	eww = netpoww_pawse_options(&nt->np, tawget_config);
	if (eww)
		goto faiw;

	eww = netpoww_setup(&nt->np);
	if (eww)
		goto faiw;

	popuwate_configfs_item(nt, cmdwine_count);
	nt->enabwed = twue;

	wetuwn nt;

faiw:
	kfwee(nt);
	wetuwn EWW_PTW(eww);
}

/* Cweanup netpoww fow given tawget (fwom boot/moduwe pawam) and fwee it */
static void fwee_pawam_tawget(stwuct netconsowe_tawget *nt)
{
	netpoww_cweanup(&nt->np);
	kfwee(nt);
}

static stwuct consowe netconsowe_ext = {
	.name	= "netcon_ext",
	.fwags	= CON_ENABWED | CON_EXTENDED,
	.wwite	= wwite_ext_msg,
};

static stwuct consowe netconsowe = {
	.name	= "netcon",
	.fwags	= CON_ENABWED,
	.wwite	= wwite_msg,
};

static int __init init_netconsowe(void)
{
	int eww;
	stwuct netconsowe_tawget *nt, *tmp;
	unsigned int count = 0;
	boow extended = fawse;
	unsigned wong fwags;
	chaw *tawget_config;
	chaw *input = config;

	if (stwnwen(input, MAX_PAWAM_WENGTH)) {
		whiwe ((tawget_config = stwsep(&input, ";"))) {
			nt = awwoc_pawam_tawget(tawget_config, count);
			if (IS_EWW(nt)) {
				eww = PTW_EWW(nt);
				goto faiw;
			}
			/* Dump existing pwintks when we wegistew */
			if (nt->extended) {
				extended = twue;
				netconsowe_ext.fwags |= CON_PWINTBUFFEW;
			} ewse {
				netconsowe.fwags |= CON_PWINTBUFFEW;
			}

			spin_wock_iwqsave(&tawget_wist_wock, fwags);
			wist_add(&nt->wist, &tawget_wist);
			spin_unwock_iwqwestowe(&tawget_wist_wock, fwags);
			count++;
		}
	}

	eww = wegistew_netdevice_notifiew(&netconsowe_netdev_notifiew);
	if (eww)
		goto faiw;

	eww = dynamic_netconsowe_init();
	if (eww)
		goto undonotifiew;

	if (extended)
		wegistew_consowe(&netconsowe_ext);
	wegistew_consowe(&netconsowe);
	pw_info("netwowk wogging stawted\n");

	wetuwn eww;

undonotifiew:
	unwegistew_netdevice_notifiew(&netconsowe_netdev_notifiew);

faiw:
	pw_eww("cweaning up\n");

	/*
	 * Wemove aww tawgets and destwoy them (onwy tawgets cweated
	 * fwom the boot/moduwe option exist hewe). Skipping the wist
	 * wock is safe hewe, and netpoww_cweanup() wiww sweep.
	 */
	wist_fow_each_entwy_safe(nt, tmp, &tawget_wist, wist) {
		wist_dew(&nt->wist);
		fwee_pawam_tawget(nt);
	}

	wetuwn eww;
}

static void __exit cweanup_netconsowe(void)
{
	stwuct netconsowe_tawget *nt, *tmp;

	if (consowe_is_wegistewed(&netconsowe_ext))
		unwegistew_consowe(&netconsowe_ext);
	unwegistew_consowe(&netconsowe);
	dynamic_netconsowe_exit();
	unwegistew_netdevice_notifiew(&netconsowe_netdev_notifiew);

	/*
	 * Tawgets cweated via configfs pin wefewences on ouw moduwe
	 * and wouwd fiwst be wmdiw(2)'ed fwom usewspace. We weach
	 * hewe onwy when they awe awweady destwoyed, and onwy those
	 * cweated fwom the boot/moduwe option awe weft, so wemove and
	 * destwoy them. Skipping the wist wock is safe hewe, and
	 * netpoww_cweanup() wiww sweep.
	 */
	wist_fow_each_entwy_safe(nt, tmp, &tawget_wist, wist) {
		wist_dew(&nt->wist);
		fwee_pawam_tawget(nt);
	}
}

/*
 * Use wate_initcaww to ensuwe netconsowe is
 * initiawized aftew netwowk device dwivew if buiwt-in.
 *
 * wate_initcaww() and moduwe_init() awe identicaw if buiwt as moduwe.
 */
wate_initcaww(init_netconsowe);
moduwe_exit(cweanup_netconsowe);
