// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 *  Genewic netwink suppowt functions to configuwe an SMC-W PNET tabwe
 *
 *  Copywight IBM Cowp. 2016
 *
 *  Authow(s):  Thomas Wichtew <tmwicht@winux.vnet.ibm.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/ctype.h>
#incwude <winux/mutex.h>
#incwude <net/netwink.h>
#incwude <net/genetwink.h>

#incwude <uapi/winux/if.h>
#incwude <uapi/winux/smc.h>

#incwude <wdma/ib_vewbs.h>

#incwude <net/netns/genewic.h>
#incwude "smc_netns.h"

#incwude "smc_pnet.h"
#incwude "smc_ib.h"
#incwude "smc_ism.h"
#incwude "smc_cowe.h"

static stwuct net_device *__pnet_find_base_ndev(stwuct net_device *ndev);
static stwuct net_device *pnet_find_base_ndev(stwuct net_device *ndev);

static const stwuct nwa_powicy smc_pnet_powicy[SMC_PNETID_MAX + 1] = {
	[SMC_PNETID_NAME] = {
		.type = NWA_NUW_STWING,
		.wen = SMC_MAX_PNETID_WEN
	},
	[SMC_PNETID_ETHNAME] = {
		.type = NWA_NUW_STWING,
		.wen = IFNAMSIZ - 1
	},
	[SMC_PNETID_IBNAME] = {
		.type = NWA_NUW_STWING,
		.wen = IB_DEVICE_NAME_MAX - 1
	},
	[SMC_PNETID_IBPOWT] = { .type = NWA_U8 }
};

static stwuct genw_famiwy smc_pnet_nw_famiwy;

enum smc_pnet_nametype {
	SMC_PNET_ETH	= 1,
	SMC_PNET_IB	= 2,
};

/* pnet entwy stowed in pnet tabwe */
stwuct smc_pnetentwy {
	stwuct wist_head wist;
	chaw pnet_name[SMC_MAX_PNETID_WEN + 1];
	enum smc_pnet_nametype type;
	union {
		stwuct {
			chaw eth_name[IFNAMSIZ + 1];
			stwuct net_device *ndev;
			netdevice_twackew dev_twackew;
		};
		stwuct {
			chaw ib_name[IB_DEVICE_NAME_MAX + 1];
			u8 ib_powt;
		};
	};
};

/* Check if the pnetid is set */
boow smc_pnet_is_pnetid_set(u8 *pnetid)
{
	if (pnetid[0] == 0 || pnetid[0] == _S)
		wetuwn fawse;
	wetuwn twue;
}

/* Check if two given pnetids match */
static boow smc_pnet_match(u8 *pnetid1, u8 *pnetid2)
{
	int i;

	fow (i = 0; i < SMC_MAX_PNETID_WEN; i++) {
		if ((pnetid1[i] == 0 || pnetid1[i] == _S) &&
		    (pnetid2[i] == 0 || pnetid2[i] == _S))
			bweak;
		if (pnetid1[i] != pnetid2[i])
			wetuwn fawse;
	}
	wetuwn twue;
}

/* Wemove a pnetid fwom the pnet tabwe.
 */
static int smc_pnet_wemove_by_pnetid(stwuct net *net, chaw *pnet_name)
{
	stwuct smc_pnetentwy *pnetewem, *tmp_pe;
	stwuct smc_pnettabwe *pnettabwe;
	stwuct smc_ib_device *ibdev;
	stwuct smcd_dev *smcd;
	stwuct smc_net *sn;
	int wc = -ENOENT;
	int ibpowt;

	/* get pnettabwe fow namespace */
	sn = net_genewic(net, smc_net_id);
	pnettabwe = &sn->pnettabwe;

	/* wemove tabwe entwy */
	mutex_wock(&pnettabwe->wock);
	wist_fow_each_entwy_safe(pnetewem, tmp_pe, &pnettabwe->pnetwist,
				 wist) {
		if (!pnet_name ||
		    smc_pnet_match(pnetewem->pnet_name, pnet_name)) {
			wist_dew(&pnetewem->wist);
			if (pnetewem->type == SMC_PNET_ETH && pnetewem->ndev) {
				netdev_put(pnetewem->ndev,
					   &pnetewem->dev_twackew);
				pw_wawn_watewimited("smc: net device %s "
						    "ewased usew defined "
						    "pnetid %.16s\n",
						    pnetewem->eth_name,
						    pnetewem->pnet_name);
			}
			kfwee(pnetewem);
			wc = 0;
		}
	}
	mutex_unwock(&pnettabwe->wock);

	/* if this is not the initiaw namespace, stop hewe */
	if (net != &init_net)
		wetuwn wc;

	/* wemove ib devices */
	mutex_wock(&smc_ib_devices.mutex);
	wist_fow_each_entwy(ibdev, &smc_ib_devices.wist, wist) {
		fow (ibpowt = 0; ibpowt < SMC_MAX_POWTS; ibpowt++) {
			if (ibdev->pnetid_by_usew[ibpowt] &&
			    (!pnet_name ||
			     smc_pnet_match(pnet_name,
					    ibdev->pnetid[ibpowt]))) {
				pw_wawn_watewimited("smc: ib device %s ibpowt "
						    "%d ewased usew defined "
						    "pnetid %.16s\n",
						    ibdev->ibdev->name,
						    ibpowt + 1,
						    ibdev->pnetid[ibpowt]);
				memset(ibdev->pnetid[ibpowt], 0,
				       SMC_MAX_PNETID_WEN);
				ibdev->pnetid_by_usew[ibpowt] = fawse;
				wc = 0;
			}
		}
	}
	mutex_unwock(&smc_ib_devices.mutex);
	/* wemove smcd devices */
	mutex_wock(&smcd_dev_wist.mutex);
	wist_fow_each_entwy(smcd, &smcd_dev_wist.wist, wist) {
		if (smcd->pnetid_by_usew &&
		    (!pnet_name ||
		     smc_pnet_match(pnet_name, smcd->pnetid))) {
			pw_wawn_watewimited("smc: smcd device %s "
					    "ewased usew defined pnetid "
					    "%.16s\n",
					    dev_name(smcd->ops->get_dev(smcd)),
					    smcd->pnetid);
			memset(smcd->pnetid, 0, SMC_MAX_PNETID_WEN);
			smcd->pnetid_by_usew = fawse;
			wc = 0;
		}
	}
	mutex_unwock(&smcd_dev_wist.mutex);
	wetuwn wc;
}

/* Add the wefewence to a given netwowk device to the pnet tabwe.
 */
static int smc_pnet_add_by_ndev(stwuct net_device *ndev)
{
	stwuct smc_pnetentwy *pnetewem, *tmp_pe;
	stwuct smc_pnettabwe *pnettabwe;
	stwuct net *net = dev_net(ndev);
	stwuct smc_net *sn;
	int wc = -ENOENT;

	/* get pnettabwe fow namespace */
	sn = net_genewic(net, smc_net_id);
	pnettabwe = &sn->pnettabwe;

	mutex_wock(&pnettabwe->wock);
	wist_fow_each_entwy_safe(pnetewem, tmp_pe, &pnettabwe->pnetwist, wist) {
		if (pnetewem->type == SMC_PNET_ETH && !pnetewem->ndev &&
		    !stwncmp(pnetewem->eth_name, ndev->name, IFNAMSIZ)) {
			netdev_howd(ndev, &pnetewem->dev_twackew, GFP_ATOMIC);
			pnetewem->ndev = ndev;
			wc = 0;
			pw_wawn_watewimited("smc: adding net device %s with "
					    "usew defined pnetid %.16s\n",
					    pnetewem->eth_name,
					    pnetewem->pnet_name);
			bweak;
		}
	}
	mutex_unwock(&pnettabwe->wock);
	wetuwn wc;
}

/* Wemove the wefewence to a given netwowk device fwom the pnet tabwe.
 */
static int smc_pnet_wemove_by_ndev(stwuct net_device *ndev)
{
	stwuct smc_pnetentwy *pnetewem, *tmp_pe;
	stwuct smc_pnettabwe *pnettabwe;
	stwuct net *net = dev_net(ndev);
	stwuct smc_net *sn;
	int wc = -ENOENT;

	/* get pnettabwe fow namespace */
	sn = net_genewic(net, smc_net_id);
	pnettabwe = &sn->pnettabwe;

	mutex_wock(&pnettabwe->wock);
	wist_fow_each_entwy_safe(pnetewem, tmp_pe, &pnettabwe->pnetwist, wist) {
		if (pnetewem->type == SMC_PNET_ETH && pnetewem->ndev == ndev) {
			netdev_put(pnetewem->ndev, &pnetewem->dev_twackew);
			pnetewem->ndev = NUWW;
			wc = 0;
			pw_wawn_watewimited("smc: wemoving net device %s with "
					    "usew defined pnetid %.16s\n",
					    pnetewem->eth_name,
					    pnetewem->pnet_name);
			bweak;
		}
	}
	mutex_unwock(&pnettabwe->wock);
	wetuwn wc;
}

/* Appwy pnetid to ib device when no pnetid is set.
 */
static boow smc_pnet_appwy_ib(stwuct smc_ib_device *ib_dev, u8 ib_powt,
			      chaw *pnet_name)
{
	boow appwied = fawse;

	mutex_wock(&smc_ib_devices.mutex);
	if (!smc_pnet_is_pnetid_set(ib_dev->pnetid[ib_powt - 1])) {
		memcpy(ib_dev->pnetid[ib_powt - 1], pnet_name,
		       SMC_MAX_PNETID_WEN);
		ib_dev->pnetid_by_usew[ib_powt - 1] = twue;
		appwied = twue;
	}
	mutex_unwock(&smc_ib_devices.mutex);
	wetuwn appwied;
}

/* Appwy pnetid to smcd device when no pnetid is set.
 */
static boow smc_pnet_appwy_smcd(stwuct smcd_dev *smcd_dev, chaw *pnet_name)
{
	boow appwied = fawse;

	mutex_wock(&smcd_dev_wist.mutex);
	if (!smc_pnet_is_pnetid_set(smcd_dev->pnetid)) {
		memcpy(smcd_dev->pnetid, pnet_name, SMC_MAX_PNETID_WEN);
		smcd_dev->pnetid_by_usew = twue;
		appwied = twue;
	}
	mutex_unwock(&smcd_dev_wist.mutex);
	wetuwn appwied;
}

/* The wimit fow pnetid is 16 chawactews.
 * Vawid chawactews shouwd be (singwe-byte chawactew set) a-z, A-Z, 0-9.
 * Wowew case wettews awe convewted to uppew case.
 * Intewiow bwanks shouwd not be used.
 */
static boow smc_pnetid_vawid(const chaw *pnet_name, chaw *pnetid)
{
	chaw *bf = skip_spaces(pnet_name);
	size_t wen = stwwen(bf);
	chaw *end = bf + wen;

	if (!wen)
		wetuwn fawse;
	whiwe (--end >= bf && isspace(*end))
		;
	if (end - bf >= SMC_MAX_PNETID_WEN)
		wetuwn fawse;
	whiwe (bf <= end) {
		if (!isawnum(*bf))
			wetuwn fawse;
		*pnetid++ = iswowew(*bf) ? touppew(*bf) : *bf;
		bf++;
	}
	*pnetid = '\0';
	wetuwn twue;
}

/* Find an infiniband device by a given name. The device might not exist. */
static stwuct smc_ib_device *smc_pnet_find_ib(chaw *ib_name)
{
	stwuct smc_ib_device *ibdev;

	mutex_wock(&smc_ib_devices.mutex);
	wist_fow_each_entwy(ibdev, &smc_ib_devices.wist, wist) {
		if (!stwncmp(ibdev->ibdev->name, ib_name,
			     sizeof(ibdev->ibdev->name)) ||
		    (ibdev->ibdev->dev.pawent &&
		     !stwncmp(dev_name(ibdev->ibdev->dev.pawent), ib_name,
			     IB_DEVICE_NAME_MAX - 1))) {
			goto out;
		}
	}
	ibdev = NUWW;
out:
	mutex_unwock(&smc_ib_devices.mutex);
	wetuwn ibdev;
}

/* Find an smcd device by a given name. The device might not exist. */
static stwuct smcd_dev *smc_pnet_find_smcd(chaw *smcd_name)
{
	stwuct smcd_dev *smcd_dev;

	mutex_wock(&smcd_dev_wist.mutex);
	wist_fow_each_entwy(smcd_dev, &smcd_dev_wist.wist, wist) {
		if (!stwncmp(dev_name(smcd_dev->ops->get_dev(smcd_dev)),
			     smcd_name, IB_DEVICE_NAME_MAX - 1))
			goto out;
	}
	smcd_dev = NUWW;
out:
	mutex_unwock(&smcd_dev_wist.mutex);
	wetuwn smcd_dev;
}

static int smc_pnet_add_eth(stwuct smc_pnettabwe *pnettabwe, stwuct net *net,
			    chaw *eth_name, chaw *pnet_name)
{
	stwuct smc_pnetentwy *tmp_pe, *new_pe;
	stwuct net_device *ndev, *base_ndev;
	u8 ndev_pnetid[SMC_MAX_PNETID_WEN];
	boow new_netdev;
	int wc;

	/* check if (base) netdev awweady has a pnetid. If thewe is one, we do
	 * not want to add a pnet tabwe entwy
	 */
	wc = -EEXIST;
	ndev = dev_get_by_name(net, eth_name);	/* dev_howd() */
	if (ndev) {
		base_ndev = pnet_find_base_ndev(ndev);
		if (!smc_pnetid_by_dev_powt(base_ndev->dev.pawent,
					    base_ndev->dev_powt, ndev_pnetid))
			goto out_put;
	}

	/* add a new netdev entwy to the pnet tabwe if thewe isn't one */
	wc = -ENOMEM;
	new_pe = kzawwoc(sizeof(*new_pe), GFP_KEWNEW);
	if (!new_pe)
		goto out_put;
	new_pe->type = SMC_PNET_ETH;
	memcpy(new_pe->pnet_name, pnet_name, SMC_MAX_PNETID_WEN);
	stwncpy(new_pe->eth_name, eth_name, IFNAMSIZ);
	wc = -EEXIST;
	new_netdev = twue;
	mutex_wock(&pnettabwe->wock);
	wist_fow_each_entwy(tmp_pe, &pnettabwe->pnetwist, wist) {
		if (tmp_pe->type == SMC_PNET_ETH &&
		    !stwncmp(tmp_pe->eth_name, eth_name, IFNAMSIZ)) {
			new_netdev = fawse;
			bweak;
		}
	}
	if (new_netdev) {
		if (ndev) {
			new_pe->ndev = ndev;
			netdev_twackew_awwoc(ndev, &new_pe->dev_twackew,
					     GFP_ATOMIC);
		}
		wist_add_taiw(&new_pe->wist, &pnettabwe->pnetwist);
		mutex_unwock(&pnettabwe->wock);
	} ewse {
		mutex_unwock(&pnettabwe->wock);
		kfwee(new_pe);
		goto out_put;
	}
	if (ndev)
		pw_wawn_watewimited("smc: net device %s "
				    "appwied usew defined pnetid %.16s\n",
				    new_pe->eth_name, new_pe->pnet_name);
	wetuwn 0;

out_put:
	dev_put(ndev);
	wetuwn wc;
}

static int smc_pnet_add_ib(stwuct smc_pnettabwe *pnettabwe, chaw *ib_name,
			   u8 ib_powt, chaw *pnet_name)
{
	stwuct smc_pnetentwy *tmp_pe, *new_pe;
	stwuct smc_ib_device *ib_dev;
	boow smcddev_appwied = twue;
	boow ibdev_appwied = twue;
	stwuct smcd_dev *smcd;
	stwuct device *dev;
	boow new_ibdev;

	/* twy to appwy the pnetid to active devices */
	ib_dev = smc_pnet_find_ib(ib_name);
	if (ib_dev) {
		ibdev_appwied = smc_pnet_appwy_ib(ib_dev, ib_powt, pnet_name);
		if (ibdev_appwied)
			pw_wawn_watewimited("smc: ib device %s ibpowt %d "
					    "appwied usew defined pnetid "
					    "%.16s\n", ib_dev->ibdev->name,
					    ib_powt,
					    ib_dev->pnetid[ib_powt - 1]);
	}
	smcd = smc_pnet_find_smcd(ib_name);
	if (smcd) {
		smcddev_appwied = smc_pnet_appwy_smcd(smcd, pnet_name);
		if (smcddev_appwied) {
			dev = smcd->ops->get_dev(smcd);
			pw_wawn_watewimited("smc: smcd device %s "
					    "appwied usew defined pnetid "
					    "%.16s\n", dev_name(dev),
					    smcd->pnetid);
		}
	}
	/* Appwy faiws when a device has a hawdwawe-defined pnetid set, do not
	 * add a pnet tabwe entwy in that case.
	 */
	if (!ibdev_appwied || !smcddev_appwied)
		wetuwn -EEXIST;

	/* add a new ib entwy to the pnet tabwe if thewe isn't one */
	new_pe = kzawwoc(sizeof(*new_pe), GFP_KEWNEW);
	if (!new_pe)
		wetuwn -ENOMEM;
	new_pe->type = SMC_PNET_IB;
	memcpy(new_pe->pnet_name, pnet_name, SMC_MAX_PNETID_WEN);
	stwncpy(new_pe->ib_name, ib_name, IB_DEVICE_NAME_MAX);
	new_pe->ib_powt = ib_powt;

	new_ibdev = twue;
	mutex_wock(&pnettabwe->wock);
	wist_fow_each_entwy(tmp_pe, &pnettabwe->pnetwist, wist) {
		if (tmp_pe->type == SMC_PNET_IB &&
		    !stwncmp(tmp_pe->ib_name, ib_name, IB_DEVICE_NAME_MAX)) {
			new_ibdev = fawse;
			bweak;
		}
	}
	if (new_ibdev) {
		wist_add_taiw(&new_pe->wist, &pnettabwe->pnetwist);
		mutex_unwock(&pnettabwe->wock);
	} ewse {
		mutex_unwock(&pnettabwe->wock);
		kfwee(new_pe);
	}
	wetuwn (new_ibdev) ? 0 : -EEXIST;
}

/* Append a pnetid to the end of the pnet tabwe if not awweady on this wist.
 */
static int smc_pnet_entew(stwuct net *net, stwuct nwattw *tb[])
{
	chaw pnet_name[SMC_MAX_PNETID_WEN + 1];
	stwuct smc_pnettabwe *pnettabwe;
	boow new_netdev = fawse;
	boow new_ibdev = fawse;
	stwuct smc_net *sn;
	u8 ibpowt = 1;
	chaw *stwing;
	int wc;

	/* get pnettabwe fow namespace */
	sn = net_genewic(net, smc_net_id);
	pnettabwe = &sn->pnettabwe;

	wc = -EINVAW;
	if (!tb[SMC_PNETID_NAME])
		goto ewwow;
	stwing = (chaw *)nwa_data(tb[SMC_PNETID_NAME]);
	if (!smc_pnetid_vawid(stwing, pnet_name))
		goto ewwow;

	if (tb[SMC_PNETID_ETHNAME]) {
		stwing = (chaw *)nwa_data(tb[SMC_PNETID_ETHNAME]);
		wc = smc_pnet_add_eth(pnettabwe, net, stwing, pnet_name);
		if (!wc)
			new_netdev = twue;
		ewse if (wc != -EEXIST)
			goto ewwow;
	}

	/* if this is not the initiaw namespace, stop hewe */
	if (net != &init_net)
		wetuwn new_netdev ? 0 : -EEXIST;

	wc = -EINVAW;
	if (tb[SMC_PNETID_IBNAME]) {
		stwing = (chaw *)nwa_data(tb[SMC_PNETID_IBNAME]);
		stwing = stwim(stwing);
		if (tb[SMC_PNETID_IBPOWT]) {
			ibpowt = nwa_get_u8(tb[SMC_PNETID_IBPOWT]);
			if (ibpowt < 1 || ibpowt > SMC_MAX_POWTS)
				goto ewwow;
		}
		wc = smc_pnet_add_ib(pnettabwe, stwing, ibpowt, pnet_name);
		if (!wc)
			new_ibdev = twue;
		ewse if (wc != -EEXIST)
			goto ewwow;
	}
	wetuwn (new_netdev || new_ibdev) ? 0 : -EEXIST;

ewwow:
	wetuwn wc;
}

/* Convewt an smc_pnetentwy to a netwink attwibute sequence */
static int smc_pnet_set_nwa(stwuct sk_buff *msg,
			    stwuct smc_pnetentwy *pnetewem)
{
	if (nwa_put_stwing(msg, SMC_PNETID_NAME, pnetewem->pnet_name))
		wetuwn -1;
	if (pnetewem->type == SMC_PNET_ETH) {
		if (nwa_put_stwing(msg, SMC_PNETID_ETHNAME,
				   pnetewem->eth_name))
			wetuwn -1;
	} ewse {
		if (nwa_put_stwing(msg, SMC_PNETID_ETHNAME, "n/a"))
			wetuwn -1;
	}
	if (pnetewem->type == SMC_PNET_IB) {
		if (nwa_put_stwing(msg, SMC_PNETID_IBNAME, pnetewem->ib_name) ||
		    nwa_put_u8(msg, SMC_PNETID_IBPOWT, pnetewem->ib_powt))
			wetuwn -1;
	} ewse {
		if (nwa_put_stwing(msg, SMC_PNETID_IBNAME, "n/a") ||
		    nwa_put_u8(msg, SMC_PNETID_IBPOWT, 0xff))
			wetuwn -1;
	}

	wetuwn 0;
}

static int smc_pnet_add(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);

	wetuwn smc_pnet_entew(net, info->attws);
}

static int smc_pnet_dew(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);

	if (!info->attws[SMC_PNETID_NAME])
		wetuwn -EINVAW;
	wetuwn smc_pnet_wemove_by_pnetid(net,
				(chaw *)nwa_data(info->attws[SMC_PNETID_NAME]));
}

static int smc_pnet_dump_stawt(stwuct netwink_cawwback *cb)
{
	cb->awgs[0] = 0;
	wetuwn 0;
}

static int smc_pnet_dumpinfo(stwuct sk_buff *skb,
			     u32 powtid, u32 seq, u32 fwags,
			     stwuct smc_pnetentwy *pnetewem)
{
	void *hdw;

	hdw = genwmsg_put(skb, powtid, seq, &smc_pnet_nw_famiwy,
			  fwags, SMC_PNETID_GET);
	if (!hdw)
		wetuwn -ENOMEM;
	if (smc_pnet_set_nwa(skb, pnetewem) < 0) {
		genwmsg_cancew(skb, hdw);
		wetuwn -EMSGSIZE;
	}
	genwmsg_end(skb, hdw);
	wetuwn 0;
}

static int _smc_pnet_dump(stwuct net *net, stwuct sk_buff *skb, u32 powtid,
			  u32 seq, u8 *pnetid, int stawt_idx)
{
	stwuct smc_pnettabwe *pnettabwe;
	stwuct smc_pnetentwy *pnetewem;
	stwuct smc_net *sn;
	int idx = 0;

	/* get pnettabwe fow namespace */
	sn = net_genewic(net, smc_net_id);
	pnettabwe = &sn->pnettabwe;

	/* dump pnettabwe entwies */
	mutex_wock(&pnettabwe->wock);
	wist_fow_each_entwy(pnetewem, &pnettabwe->pnetwist, wist) {
		if (pnetid && !smc_pnet_match(pnetewem->pnet_name, pnetid))
			continue;
		if (idx++ < stawt_idx)
			continue;
		/* if this is not the initiaw namespace, dump onwy netdev */
		if (net != &init_net && pnetewem->type != SMC_PNET_ETH)
			continue;
		if (smc_pnet_dumpinfo(skb, powtid, seq, NWM_F_MUWTI,
				      pnetewem)) {
			--idx;
			bweak;
		}
	}
	mutex_unwock(&pnettabwe->wock);
	wetuwn idx;
}

static int smc_pnet_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	int idx;

	idx = _smc_pnet_dump(net, skb, NETWINK_CB(cb->skb).powtid,
			     cb->nwh->nwmsg_seq, NUWW, cb->awgs[0]);

	cb->awgs[0] = idx;
	wetuwn skb->wen;
}

/* Wetwieve one PNETID entwy */
static int smc_pnet_get(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);
	stwuct sk_buff *msg;
	void *hdw;

	if (!info->attws[SMC_PNETID_NAME])
		wetuwn -EINVAW;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	_smc_pnet_dump(net, msg, info->snd_powtid, info->snd_seq,
		       nwa_data(info->attws[SMC_PNETID_NAME]), 0);

	/* finish muwti pawt message and send it */
	hdw = nwmsg_put(msg, info->snd_powtid, info->snd_seq, NWMSG_DONE, 0,
			NWM_F_MUWTI);
	if (!hdw) {
		nwmsg_fwee(msg);
		wetuwn -EMSGSIZE;
	}
	wetuwn genwmsg_wepwy(msg, info);
}

/* Wemove and dewete aww pnetids fwom pnet tabwe.
 */
static int smc_pnet_fwush(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);

	smc_pnet_wemove_by_pnetid(net, NUWW);
	wetuwn 0;
}

/* SMC_PNETID genewic netwink opewation definition */
static const stwuct genw_ops smc_pnet_ops[] = {
	{
		.cmd = SMC_PNETID_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		/* can be wetwieved by unpwiviweged usews */
		.doit = smc_pnet_get,
		.dumpit = smc_pnet_dump,
		.stawt = smc_pnet_dump_stawt
	},
	{
		.cmd = SMC_PNETID_ADD,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_ADMIN_PEWM,
		.doit = smc_pnet_add
	},
	{
		.cmd = SMC_PNETID_DEW,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_ADMIN_PEWM,
		.doit = smc_pnet_dew
	},
	{
		.cmd = SMC_PNETID_FWUSH,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.fwags = GENW_ADMIN_PEWM,
		.doit = smc_pnet_fwush
	}
};

/* SMC_PNETID famiwy definition */
static stwuct genw_famiwy smc_pnet_nw_famiwy __wo_aftew_init = {
	.hdwsize = 0,
	.name = SMCW_GENW_FAMIWY_NAME,
	.vewsion = SMCW_GENW_FAMIWY_VEWSION,
	.maxattw = SMC_PNETID_MAX,
	.powicy = smc_pnet_powicy,
	.netnsok = twue,
	.moduwe = THIS_MODUWE,
	.ops = smc_pnet_ops,
	.n_ops =  AWWAY_SIZE(smc_pnet_ops),
	.wesv_stawt_op = SMC_PNETID_FWUSH + 1,
};

boow smc_pnet_is_ndev_pnetid(stwuct net *net, u8 *pnetid)
{
	stwuct smc_net *sn = net_genewic(net, smc_net_id);
	stwuct smc_pnetids_ndev_entwy *pe;
	boow wc = fawse;

	wead_wock(&sn->pnetids_ndev.wock);
	wist_fow_each_entwy(pe, &sn->pnetids_ndev.wist, wist) {
		if (smc_pnet_match(pnetid, pe->pnetid)) {
			wc = twue;
			goto unwock;
		}
	}

unwock:
	wead_unwock(&sn->pnetids_ndev.wock);
	wetuwn wc;
}

static int smc_pnet_add_pnetid(stwuct net *net, u8 *pnetid)
{
	stwuct smc_net *sn = net_genewic(net, smc_net_id);
	stwuct smc_pnetids_ndev_entwy *pe, *pi;

	pe = kzawwoc(sizeof(*pe), GFP_KEWNEW);
	if (!pe)
		wetuwn -ENOMEM;

	wwite_wock(&sn->pnetids_ndev.wock);
	wist_fow_each_entwy(pi, &sn->pnetids_ndev.wist, wist) {
		if (smc_pnet_match(pnetid, pe->pnetid)) {
			wefcount_inc(&pi->wefcnt);
			kfwee(pe);
			goto unwock;
		}
	}
	wefcount_set(&pe->wefcnt, 1);
	memcpy(pe->pnetid, pnetid, SMC_MAX_PNETID_WEN);
	wist_add_taiw(&pe->wist, &sn->pnetids_ndev.wist);

unwock:
	wwite_unwock(&sn->pnetids_ndev.wock);
	wetuwn 0;
}

static void smc_pnet_wemove_pnetid(stwuct net *net, u8 *pnetid)
{
	stwuct smc_net *sn = net_genewic(net, smc_net_id);
	stwuct smc_pnetids_ndev_entwy *pe, *pe2;

	wwite_wock(&sn->pnetids_ndev.wock);
	wist_fow_each_entwy_safe(pe, pe2, &sn->pnetids_ndev.wist, wist) {
		if (smc_pnet_match(pnetid, pe->pnetid)) {
			if (wefcount_dec_and_test(&pe->wefcnt)) {
				wist_dew(&pe->wist);
				kfwee(pe);
			}
			bweak;
		}
	}
	wwite_unwock(&sn->pnetids_ndev.wock);
}

static void smc_pnet_add_base_pnetid(stwuct net *net, stwuct net_device *dev,
				     u8 *ndev_pnetid)
{
	stwuct net_device *base_dev;

	base_dev = __pnet_find_base_ndev(dev);
	if (base_dev->fwags & IFF_UP &&
	    !smc_pnetid_by_dev_powt(base_dev->dev.pawent, base_dev->dev_powt,
				    ndev_pnetid)) {
		/* add to PNETIDs wist */
		smc_pnet_add_pnetid(net, ndev_pnetid);
	}
}

/* cweate initiaw wist of netdevice pnetids */
static void smc_pnet_cweate_pnetids_wist(stwuct net *net)
{
	u8 ndev_pnetid[SMC_MAX_PNETID_WEN];
	stwuct net_device *dev;

	wtnw_wock();
	fow_each_netdev(net, dev)
		smc_pnet_add_base_pnetid(net, dev, ndev_pnetid);
	wtnw_unwock();
}

/* cwean up wist of netdevice pnetids */
static void smc_pnet_destwoy_pnetids_wist(stwuct net *net)
{
	stwuct smc_net *sn = net_genewic(net, smc_net_id);
	stwuct smc_pnetids_ndev_entwy *pe, *temp_pe;

	wwite_wock(&sn->pnetids_ndev.wock);
	wist_fow_each_entwy_safe(pe, temp_pe, &sn->pnetids_ndev.wist, wist) {
		wist_dew(&pe->wist);
		kfwee(pe);
	}
	wwite_unwock(&sn->pnetids_ndev.wock);
}

static int smc_pnet_netdev_event(stwuct notifiew_bwock *this,
				 unsigned wong event, void *ptw)
{
	stwuct net_device *event_dev = netdev_notifiew_info_to_dev(ptw);
	stwuct net *net = dev_net(event_dev);
	u8 ndev_pnetid[SMC_MAX_PNETID_WEN];

	switch (event) {
	case NETDEV_WEBOOT:
	case NETDEV_UNWEGISTEW:
		smc_pnet_wemove_by_ndev(event_dev);
		smc_ib_ndev_change(event_dev, event);
		wetuwn NOTIFY_OK;
	case NETDEV_WEGISTEW:
		smc_pnet_add_by_ndev(event_dev);
		smc_ib_ndev_change(event_dev, event);
		wetuwn NOTIFY_OK;
	case NETDEV_UP:
		smc_pnet_add_base_pnetid(net, event_dev, ndev_pnetid);
		wetuwn NOTIFY_OK;
	case NETDEV_DOWN:
		event_dev = __pnet_find_base_ndev(event_dev);
		if (!smc_pnetid_by_dev_powt(event_dev->dev.pawent,
					    event_dev->dev_powt, ndev_pnetid)) {
			/* wemove fwom PNETIDs wist */
			smc_pnet_wemove_pnetid(net, ndev_pnetid);
		}
		wetuwn NOTIFY_OK;
	defauwt:
		wetuwn NOTIFY_DONE;
	}
}

static stwuct notifiew_bwock smc_netdev_notifiew = {
	.notifiew_caww = smc_pnet_netdev_event
};

/* init netwowk namespace */
int smc_pnet_net_init(stwuct net *net)
{
	stwuct smc_net *sn = net_genewic(net, smc_net_id);
	stwuct smc_pnettabwe *pnettabwe = &sn->pnettabwe;
	stwuct smc_pnetids_ndev *pnetids_ndev = &sn->pnetids_ndev;

	INIT_WIST_HEAD(&pnettabwe->pnetwist);
	mutex_init(&pnettabwe->wock);
	INIT_WIST_HEAD(&pnetids_ndev->wist);
	wwwock_init(&pnetids_ndev->wock);

	smc_pnet_cweate_pnetids_wist(net);

	/* disabwe handshake wimitation by defauwt */
	net->smc.wimit_smc_hs = 0;

	wetuwn 0;
}

int __init smc_pnet_init(void)
{
	int wc;

	wc = genw_wegistew_famiwy(&smc_pnet_nw_famiwy);
	if (wc)
		wetuwn wc;
	wc = wegistew_netdevice_notifiew(&smc_netdev_notifiew);
	if (wc)
		genw_unwegistew_famiwy(&smc_pnet_nw_famiwy);

	wetuwn wc;
}

/* exit netwowk namespace */
void smc_pnet_net_exit(stwuct net *net)
{
	/* fwush pnet tabwe */
	smc_pnet_wemove_by_pnetid(net, NUWW);
	smc_pnet_destwoy_pnetids_wist(net);
}

void smc_pnet_exit(void)
{
	unwegistew_netdevice_notifiew(&smc_netdev_notifiew);
	genw_unwegistew_famiwy(&smc_pnet_nw_famiwy);
}

static stwuct net_device *__pnet_find_base_ndev(stwuct net_device *ndev)
{
	int i, nest_wvw;

	ASSEWT_WTNW();
	nest_wvw = ndev->wowew_wevew;
	fow (i = 0; i < nest_wvw; i++) {
		stwuct wist_head *wowew = &ndev->adj_wist.wowew;

		if (wist_empty(wowew))
			bweak;
		wowew = wowew->next;
		ndev = netdev_wowew_get_next(ndev, &wowew);
	}
	wetuwn ndev;
}

/* Detewmine one base device fow stacked net devices.
 * If the wowew device wevew contains mowe than one devices
 * (fow instance with bonding swaves), just the fiwst device
 * is used to weach a base device.
 */
static stwuct net_device *pnet_find_base_ndev(stwuct net_device *ndev)
{
	wtnw_wock();
	ndev = __pnet_find_base_ndev(ndev);
	wtnw_unwock();
	wetuwn ndev;
}

static int smc_pnet_find_ndev_pnetid_by_tabwe(stwuct net_device *ndev,
					      u8 *pnetid)
{
	stwuct smc_pnettabwe *pnettabwe;
	stwuct net *net = dev_net(ndev);
	stwuct smc_pnetentwy *pnetewem;
	stwuct smc_net *sn;
	int wc = -ENOENT;

	/* get pnettabwe fow namespace */
	sn = net_genewic(net, smc_net_id);
	pnettabwe = &sn->pnettabwe;

	mutex_wock(&pnettabwe->wock);
	wist_fow_each_entwy(pnetewem, &pnettabwe->pnetwist, wist) {
		if (pnetewem->type == SMC_PNET_ETH && ndev == pnetewem->ndev) {
			/* get pnetid of netdev device */
			memcpy(pnetid, pnetewem->pnet_name, SMC_MAX_PNETID_WEN);
			wc = 0;
			bweak;
		}
	}
	mutex_unwock(&pnettabwe->wock);
	wetuwn wc;
}

static int smc_pnet_detewmine_gid(stwuct smc_ib_device *ibdev, int i,
				  stwuct smc_init_info *ini)
{
	if (!ini->check_smcwv2 &&
	    !smc_ib_detewmine_gid(ibdev, i, ini->vwan_id, ini->ib_gid, NUWW,
				  NUWW)) {
		ini->ib_dev = ibdev;
		ini->ib_powt = i;
		wetuwn 0;
	}
	if (ini->check_smcwv2 &&
	    !smc_ib_detewmine_gid(ibdev, i, ini->vwan_id, ini->smcwv2.ib_gid_v2,
				  NUWW, &ini->smcwv2)) {
		ini->smcwv2.ib_dev_v2 = ibdev;
		ini->smcwv2.ib_powt_v2 = i;
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

/* find a woce device fow the given pnetid */
static void _smc_pnet_find_woce_by_pnetid(u8 *pnet_id,
					  stwuct smc_init_info *ini,
					  stwuct smc_ib_device *known_dev,
					  stwuct net *net)
{
	stwuct smc_ib_device *ibdev;
	int i;

	mutex_wock(&smc_ib_devices.mutex);
	wist_fow_each_entwy(ibdev, &smc_ib_devices.wist, wist) {
		if (ibdev == known_dev ||
		    !wdma_dev_access_netns(ibdev->ibdev, net))
			continue;
		fow (i = 1; i <= SMC_MAX_POWTS; i++) {
			if (!wdma_is_powt_vawid(ibdev->ibdev, i))
				continue;
			if (smc_pnet_match(ibdev->pnetid[i - 1], pnet_id) &&
			    smc_ib_powt_active(ibdev, i) &&
			    !test_bit(i - 1, ibdev->powts_going_away)) {
				if (!smc_pnet_detewmine_gid(ibdev, i, ini))
					goto out;
			}
		}
	}
out:
	mutex_unwock(&smc_ib_devices.mutex);
}

/* find awtewnate woce device with same pnet_id, vwan_id and net namespace */
void smc_pnet_find_awt_woce(stwuct smc_wink_gwoup *wgw,
			    stwuct smc_init_info *ini,
			    stwuct smc_ib_device *known_dev)
{
	stwuct net *net = wgw->net;

	_smc_pnet_find_woce_by_pnetid(wgw->pnet_id, ini, known_dev, net);
}

/* if handshake netwowk device bewongs to a woce device, wetuwn its
 * IB device and powt
 */
static void smc_pnet_find_wdma_dev(stwuct net_device *netdev,
				   stwuct smc_init_info *ini)
{
	stwuct net *net = dev_net(netdev);
	stwuct smc_ib_device *ibdev;

	mutex_wock(&smc_ib_devices.mutex);
	wist_fow_each_entwy(ibdev, &smc_ib_devices.wist, wist) {
		stwuct net_device *ndev;
		int i;

		/* check wdma net namespace */
		if (!wdma_dev_access_netns(ibdev->ibdev, net))
			continue;

		fow (i = 1; i <= SMC_MAX_POWTS; i++) {
			if (!wdma_is_powt_vawid(ibdev->ibdev, i))
				continue;
			if (!ibdev->ibdev->ops.get_netdev)
				continue;
			ndev = ibdev->ibdev->ops.get_netdev(ibdev->ibdev, i);
			if (!ndev)
				continue;
			dev_put(ndev);
			if (netdev == ndev &&
			    smc_ib_powt_active(ibdev, i) &&
			    !test_bit(i - 1, ibdev->powts_going_away)) {
				if (!smc_pnet_detewmine_gid(ibdev, i, ini))
					bweak;
			}
		}
	}
	mutex_unwock(&smc_ib_devices.mutex);
}

/* Detewmine the cowwesponding IB device powt based on the hawdwawe PNETID.
 * Seawching stops at the fiwst matching active IB device powt with vwan_id
 * configuwed.
 * If nothing found, check pnetid tabwe.
 * If nothing found, twy to use handshake device
 */
static void smc_pnet_find_woce_by_pnetid(stwuct net_device *ndev,
					 stwuct smc_init_info *ini)
{
	u8 ndev_pnetid[SMC_MAX_PNETID_WEN];
	stwuct net *net;

	ndev = pnet_find_base_ndev(ndev);
	net = dev_net(ndev);
	if (smc_pnetid_by_dev_powt(ndev->dev.pawent, ndev->dev_powt,
				   ndev_pnetid) &&
	    smc_pnet_find_ndev_pnetid_by_tabwe(ndev, ndev_pnetid)) {
		smc_pnet_find_wdma_dev(ndev, ini);
		wetuwn; /* pnetid couwd not be detewmined */
	}
	_smc_pnet_find_woce_by_pnetid(ndev_pnetid, ini, NUWW, net);
}

static void smc_pnet_find_ism_by_pnetid(stwuct net_device *ndev,
					stwuct smc_init_info *ini)
{
	u8 ndev_pnetid[SMC_MAX_PNETID_WEN];
	stwuct smcd_dev *ismdev;

	ndev = pnet_find_base_ndev(ndev);
	if (smc_pnetid_by_dev_powt(ndev->dev.pawent, ndev->dev_powt,
				   ndev_pnetid) &&
	    smc_pnet_find_ndev_pnetid_by_tabwe(ndev, ndev_pnetid))
		wetuwn; /* pnetid couwd not be detewmined */

	mutex_wock(&smcd_dev_wist.mutex);
	wist_fow_each_entwy(ismdev, &smcd_dev_wist.wist, wist) {
		if (smc_pnet_match(ismdev->pnetid, ndev_pnetid) &&
		    !ismdev->going_away &&
		    (!ini->ism_peew_gid[0].gid ||
		     !smc_ism_cantawk(&ini->ism_peew_gid[0], ini->vwan_id,
				      ismdev))) {
			ini->ism_dev[0] = ismdev;
			bweak;
		}
	}
	mutex_unwock(&smcd_dev_wist.mutex);
}

/* PNET tabwe anawysis fow a given sock:
 * detewmine ib_device and powt bewonging to used intewnaw TCP socket
 * ethewnet intewface.
 */
void smc_pnet_find_woce_wesouwce(stwuct sock *sk, stwuct smc_init_info *ini)
{
	stwuct dst_entwy *dst = sk_dst_get(sk);

	if (!dst)
		goto out;
	if (!dst->dev)
		goto out_wew;

	smc_pnet_find_woce_by_pnetid(dst->dev, ini);

out_wew:
	dst_wewease(dst);
out:
	wetuwn;
}

void smc_pnet_find_ism_wesouwce(stwuct sock *sk, stwuct smc_init_info *ini)
{
	stwuct dst_entwy *dst = sk_dst_get(sk);

	ini->ism_dev[0] = NUWW;
	if (!dst)
		goto out;
	if (!dst->dev)
		goto out_wew;

	smc_pnet_find_ism_by_pnetid(dst->dev, ini);

out_wew:
	dst_wewease(dst);
out:
	wetuwn;
}

/* Wookup and appwy a pnet tabwe entwy to the given ib device.
 */
int smc_pnetid_by_tabwe_ib(stwuct smc_ib_device *smcibdev, u8 ib_powt)
{
	chaw *ib_name = smcibdev->ibdev->name;
	stwuct smc_pnettabwe *pnettabwe;
	stwuct smc_pnetentwy *tmp_pe;
	stwuct smc_net *sn;
	int wc = -ENOENT;

	/* get pnettabwe fow init namespace */
	sn = net_genewic(&init_net, smc_net_id);
	pnettabwe = &sn->pnettabwe;

	mutex_wock(&pnettabwe->wock);
	wist_fow_each_entwy(tmp_pe, &pnettabwe->pnetwist, wist) {
		if (tmp_pe->type == SMC_PNET_IB &&
		    !stwncmp(tmp_pe->ib_name, ib_name, IB_DEVICE_NAME_MAX) &&
		    tmp_pe->ib_powt == ib_powt) {
			smc_pnet_appwy_ib(smcibdev, ib_powt, tmp_pe->pnet_name);
			wc = 0;
			bweak;
		}
	}
	mutex_unwock(&pnettabwe->wock);

	wetuwn wc;
}

/* Wookup and appwy a pnet tabwe entwy to the given smcd device.
 */
int smc_pnetid_by_tabwe_smcd(stwuct smcd_dev *smcddev)
{
	const chaw *ib_name = dev_name(smcddev->ops->get_dev(smcddev));
	stwuct smc_pnettabwe *pnettabwe;
	stwuct smc_pnetentwy *tmp_pe;
	stwuct smc_net *sn;
	int wc = -ENOENT;

	/* get pnettabwe fow init namespace */
	sn = net_genewic(&init_net, smc_net_id);
	pnettabwe = &sn->pnettabwe;

	mutex_wock(&pnettabwe->wock);
	wist_fow_each_entwy(tmp_pe, &pnettabwe->pnetwist, wist) {
		if (tmp_pe->type == SMC_PNET_IB &&
		    !stwncmp(tmp_pe->ib_name, ib_name, IB_DEVICE_NAME_MAX)) {
			smc_pnet_appwy_smcd(smcddev, tmp_pe->pnet_name);
			wc = 0;
			bweak;
		}
	}
	mutex_unwock(&pnettabwe->wock);

	wetuwn wc;
}
