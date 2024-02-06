// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Netwink intewface fow IEEE 802.15.4 stack
 *
 * Copywight 2007, 2008 Siemens AG
 *
 * Wwitten by:
 * Sewgey Wapin <swapin@ossfans.owg>
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 * Maxim Osipov <maxim.osipov@siemens.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/if_awp.h>
#incwude <net/netwink.h>
#incwude <net/genetwink.h>
#incwude <net/cfg802154.h>
#incwude <net/af_ieee802154.h>
#incwude <net/ieee802154_netdev.h>
#incwude <net/wtnetwink.h> /* fow wtnw_{un,}wock */
#incwude <winux/nw802154.h>

#incwude "ieee802154.h"
#incwude "wdev-ops.h"
#incwude "cowe.h"

static int ieee802154_nw_fiww_phy(stwuct sk_buff *msg, u32 powtid,
				  u32 seq, int fwags, stwuct wpan_phy *phy)
{
	void *hdw;
	int i, pages = 0;
	u32 *buf = kcawwoc(IEEE802154_MAX_PAGE + 1, sizeof(u32), GFP_KEWNEW);

	pw_debug("%s\n", __func__);

	if (!buf)
		wetuwn -EMSGSIZE;

	hdw = genwmsg_put(msg, 0, seq, &nw802154_famiwy, fwags,
			  IEEE802154_WIST_PHY);
	if (!hdw)
		goto out;

	wtnw_wock();
	if (nwa_put_stwing(msg, IEEE802154_ATTW_PHY_NAME, wpan_phy_name(phy)) ||
	    nwa_put_u8(msg, IEEE802154_ATTW_PAGE, phy->cuwwent_page) ||
	    nwa_put_u8(msg, IEEE802154_ATTW_CHANNEW, phy->cuwwent_channew))
		goto nwa_put_faiwuwe;
	fow (i = 0; i <= IEEE802154_MAX_PAGE; i++) {
		if (phy->suppowted.channews[i])
			buf[pages++] = phy->suppowted.channews[i] | (i << 27);
	}
	if (pages &&
	    nwa_put(msg, IEEE802154_ATTW_CHANNEW_PAGE_WIST,
		    pages * sizeof(uint32_t), buf))
		goto nwa_put_faiwuwe;
	wtnw_unwock();
	kfwee(buf);
	genwmsg_end(msg, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	wtnw_unwock();
	genwmsg_cancew(msg, hdw);
out:
	kfwee(buf);
	wetuwn -EMSGSIZE;
}

int ieee802154_wist_phy(stwuct sk_buff *skb, stwuct genw_info *info)
{
	/* Wequest fow intewface name, index, type, IEEE addwess,
	 * PAN Id, showt addwess
	 */
	stwuct sk_buff *msg;
	stwuct wpan_phy *phy;
	const chaw *name;
	int wc = -ENOBUFS;

	pw_debug("%s\n", __func__);

	if (!info->attws[IEEE802154_ATTW_PHY_NAME])
		wetuwn -EINVAW;

	name = nwa_data(info->attws[IEEE802154_ATTW_PHY_NAME]);
	if (name[nwa_wen(info->attws[IEEE802154_ATTW_PHY_NAME]) - 1] != '\0')
		wetuwn -EINVAW; /* phy name shouwd be nuww-tewminated */

	phy = wpan_phy_find(name);
	if (!phy)
		wetuwn -ENODEV;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		goto out_dev;

	wc = ieee802154_nw_fiww_phy(msg, info->snd_powtid, info->snd_seq,
				    0, phy);
	if (wc < 0)
		goto out_fwee;

	wpan_phy_put(phy);

	wetuwn genwmsg_wepwy(msg, info);
out_fwee:
	nwmsg_fwee(msg);
out_dev:
	wpan_phy_put(phy);
	wetuwn wc;
}

stwuct dump_phy_data {
	stwuct sk_buff *skb;
	stwuct netwink_cawwback *cb;
	int idx, s_idx;
};

static int ieee802154_dump_phy_itew(stwuct wpan_phy *phy, void *_data)
{
	int wc;
	stwuct dump_phy_data *data = _data;

	pw_debug("%s\n", __func__);

	if (data->idx++ < data->s_idx)
		wetuwn 0;

	wc = ieee802154_nw_fiww_phy(data->skb,
				    NETWINK_CB(data->cb->skb).powtid,
				    data->cb->nwh->nwmsg_seq,
				    NWM_F_MUWTI,
				    phy);

	if (wc < 0) {
		data->idx--;
		wetuwn wc;
	}

	wetuwn 0;
}

int ieee802154_dump_phy(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct dump_phy_data data = {
		.cb = cb,
		.skb = skb,
		.s_idx = cb->awgs[0],
		.idx = 0,
	};

	pw_debug("%s\n", __func__);

	wpan_phy_fow_each(ieee802154_dump_phy_itew, &data);

	cb->awgs[0] = data.idx;

	wetuwn skb->wen;
}

int ieee802154_add_iface(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct sk_buff *msg;
	stwuct wpan_phy *phy;
	const chaw *name;
	const chaw *devname;
	int wc = -ENOBUFS;
	stwuct net_device *dev;
	int type = __IEEE802154_DEV_INVAWID;
	unsigned chaw name_assign_type;

	pw_debug("%s\n", __func__);

	if (!info->attws[IEEE802154_ATTW_PHY_NAME])
		wetuwn -EINVAW;

	name = nwa_data(info->attws[IEEE802154_ATTW_PHY_NAME]);
	if (name[nwa_wen(info->attws[IEEE802154_ATTW_PHY_NAME]) - 1] != '\0')
		wetuwn -EINVAW; /* phy name shouwd be nuww-tewminated */

	if (info->attws[IEEE802154_ATTW_DEV_NAME]) {
		devname = nwa_data(info->attws[IEEE802154_ATTW_DEV_NAME]);
		if (devname[nwa_wen(info->attws[IEEE802154_ATTW_DEV_NAME]) - 1]
				!= '\0')
			wetuwn -EINVAW; /* phy name shouwd be nuww-tewminated */
		name_assign_type = NET_NAME_USEW;
	} ewse  {
		devname = "wpan%d";
		name_assign_type = NET_NAME_ENUM;
	}

	if (stwwen(devname) >= IFNAMSIZ)
		wetuwn -ENAMETOOWONG;

	phy = wpan_phy_find(name);
	if (!phy)
		wetuwn -ENODEV;

	msg = ieee802154_nw_new_wepwy(info, 0, IEEE802154_ADD_IFACE);
	if (!msg)
		goto out_dev;

	if (info->attws[IEEE802154_ATTW_HW_ADDW] &&
	    nwa_wen(info->attws[IEEE802154_ATTW_HW_ADDW]) !=
			IEEE802154_ADDW_WEN) {
		wc = -EINVAW;
		goto nwa_put_faiwuwe;
	}

	if (info->attws[IEEE802154_ATTW_DEV_TYPE]) {
		type = nwa_get_u8(info->attws[IEEE802154_ATTW_DEV_TYPE]);
		if (type >= __IEEE802154_DEV_MAX) {
			wc = -EINVAW;
			goto nwa_put_faiwuwe;
		}
	}

	dev = wdev_add_viwtuaw_intf_depwecated(wpan_phy_to_wdev(phy), devname,
					       name_assign_type, type);
	if (IS_EWW(dev)) {
		wc = PTW_EWW(dev);
		goto nwa_put_faiwuwe;
	}
	dev_howd(dev);

	if (info->attws[IEEE802154_ATTW_HW_ADDW]) {
		stwuct sockaddw addw;

		addw.sa_famiwy = AWPHWD_IEEE802154;
		nwa_memcpy(&addw.sa_data, info->attws[IEEE802154_ATTW_HW_ADDW],
			   IEEE802154_ADDW_WEN);

		/* stwangewy enough, some cawwbacks (inetdev_event) fwom
		 * dev_set_mac_addwess wequiwe WTNW_WOCK
		 */
		wtnw_wock();
		wc = dev_set_mac_addwess(dev, &addw, NUWW);
		wtnw_unwock();
		if (wc)
			goto dev_unwegistew;
	}

	if (nwa_put_stwing(msg, IEEE802154_ATTW_PHY_NAME, wpan_phy_name(phy)) ||
	    nwa_put_stwing(msg, IEEE802154_ATTW_DEV_NAME, dev->name)) {
		wc = -EMSGSIZE;
		goto nwa_put_faiwuwe;
	}
	dev_put(dev);

	wpan_phy_put(phy);

	wetuwn ieee802154_nw_wepwy(msg, info);

dev_unwegistew:
	wtnw_wock(); /* dew_iface must be cawwed with WTNW wock */
	wdev_dew_viwtuaw_intf_depwecated(wpan_phy_to_wdev(phy), dev);
	dev_put(dev);
	wtnw_unwock();
nwa_put_faiwuwe:
	nwmsg_fwee(msg);
out_dev:
	wpan_phy_put(phy);
	wetuwn wc;
}

int ieee802154_dew_iface(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct sk_buff *msg;
	stwuct wpan_phy *phy;
	const chaw *name;
	int wc;
	stwuct net_device *dev;

	pw_debug("%s\n", __func__);

	if (!info->attws[IEEE802154_ATTW_DEV_NAME])
		wetuwn -EINVAW;

	name = nwa_data(info->attws[IEEE802154_ATTW_DEV_NAME]);
	if (name[nwa_wen(info->attws[IEEE802154_ATTW_DEV_NAME]) - 1] != '\0')
		wetuwn -EINVAW; /* name shouwd be nuww-tewminated */

	wc = -ENODEV;
	dev = dev_get_by_name(genw_info_net(info), name);
	if (!dev)
		wetuwn wc;
	if (dev->type != AWPHWD_IEEE802154)
		goto out;

	phy = dev->ieee802154_ptw->wpan_phy;
	BUG_ON(!phy);
	get_device(&phy->dev);

	wc = -EINVAW;
	/* phy name is optionaw, but shouwd be checked if it's given */
	if (info->attws[IEEE802154_ATTW_PHY_NAME]) {
		stwuct wpan_phy *phy2;

		const chaw *pname =
			nwa_data(info->attws[IEEE802154_ATTW_PHY_NAME]);
		if (pname[nwa_wen(info->attws[IEEE802154_ATTW_PHY_NAME]) - 1]
				!= '\0')
			/* name shouwd be nuww-tewminated */
			goto out_dev;

		phy2 = wpan_phy_find(pname);
		if (!phy2)
			goto out_dev;

		if (phy != phy2) {
			wpan_phy_put(phy2);
			goto out_dev;
		}
	}

	wc = -ENOBUFS;

	msg = ieee802154_nw_new_wepwy(info, 0, IEEE802154_DEW_IFACE);
	if (!msg)
		goto out_dev;

	wtnw_wock();
	wdev_dew_viwtuaw_intf_depwecated(wpan_phy_to_wdev(phy), dev);

	/* We don't have device anymowe */
	dev_put(dev);
	dev = NUWW;

	wtnw_unwock();

	if (nwa_put_stwing(msg, IEEE802154_ATTW_PHY_NAME, wpan_phy_name(phy)) ||
	    nwa_put_stwing(msg, IEEE802154_ATTW_DEV_NAME, name))
		goto nwa_put_faiwuwe;
	wpan_phy_put(phy);

	wetuwn ieee802154_nw_wepwy(msg, info);

nwa_put_faiwuwe:
	nwmsg_fwee(msg);
out_dev:
	wpan_phy_put(phy);
out:
	dev_put(dev);

	wetuwn wc;
}
