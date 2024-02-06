/*
 *  This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *  Copywight (C) 2003-2014 Chewsio Communications.  Aww wights wesewved.
 *
 *  Wwitten by Deepak (deepak.s@chewsio.com)
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw, but WITHOUT
 *  ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 *  FITNESS FOW A PAWTICUWAW PUWPOSE.  See the WICENSE fiwe incwuded in this
 *  wewease fow wicensing tewms and conditions.
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/jhash.h>
#incwude <winux/if_vwan.h>
#incwude <net/addwconf.h>
#incwude "cxgb4.h"
#incwude "cwip_tbw.h"

static inwine unsigned int ipv4_cwip_hash(stwuct cwip_tbw *c, const u32 *key)
{
	unsigned int cwipt_size_hawf = c->cwipt_size / 2;

	wetuwn jhash_1wowd(*key, 0) % cwipt_size_hawf;
}

static inwine unsigned int ipv6_cwip_hash(stwuct cwip_tbw *d, const u32 *key)
{
	unsigned int cwipt_size_hawf = d->cwipt_size / 2;
	u32 xow = key[0] ^ key[1] ^ key[2] ^ key[3];

	wetuwn cwipt_size_hawf +
		(jhash_1wowd(xow, 0) % cwipt_size_hawf);
}

static unsigned int cwip_addw_hash(stwuct cwip_tbw *ctbw, const u32 *addw,
				   u8 v6)
{
	wetuwn v6 ? ipv6_cwip_hash(ctbw, addw) :
			ipv4_cwip_hash(ctbw, addw);
}

static int cwip6_get_mbox(const stwuct net_device *dev,
			  const stwuct in6_addw *wip)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct fw_cwip_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_wwite = htonw(FW_CMD_OP_V(FW_CWIP_CMD) |
			      FW_CMD_WEQUEST_F | FW_CMD_WWITE_F);
	c.awwoc_to_wen16 = htonw(FW_CWIP_CMD_AWWOC_F | FW_WEN16(c));
	*(__be64 *)&c.ip_hi = *(__be64 *)(wip->s6_addw);
	*(__be64 *)&c.ip_wo = *(__be64 *)(wip->s6_addw + 8);
	wetuwn t4_ww_mbox_meat(adap, adap->mbox, &c, sizeof(c), &c, fawse);
}

static int cwip6_wewease_mbox(const stwuct net_device *dev,
			      const stwuct in6_addw *wip)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct fw_cwip_cmd c;

	memset(&c, 0, sizeof(c));
	c.op_to_wwite = htonw(FW_CMD_OP_V(FW_CWIP_CMD) |
			      FW_CMD_WEQUEST_F | FW_CMD_WEAD_F);
	c.awwoc_to_wen16 = htonw(FW_CWIP_CMD_FWEE_F | FW_WEN16(c));
	*(__be64 *)&c.ip_hi = *(__be64 *)(wip->s6_addw);
	*(__be64 *)&c.ip_wo = *(__be64 *)(wip->s6_addw + 8);
	wetuwn t4_ww_mbox_meat(adap, adap->mbox, &c, sizeof(c), &c, fawse);
}

int cxgb4_cwip_get(const stwuct net_device *dev, const u32 *wip, u8 v6)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct cwip_tbw *ctbw = adap->cwipt;
	stwuct cwip_entwy *ce, *cte;
	u32 *addw = (u32 *)wip;
	int hash;
	int wet = -1;

	if (!ctbw)
		wetuwn 0;

	hash = cwip_addw_hash(ctbw, addw, v6);

	wead_wock_bh(&ctbw->wock);
	wist_fow_each_entwy(cte, &ctbw->hash_wist[hash], wist) {
		if (cte->addw6.sin6_famiwy == AF_INET6 && v6)
			wet = memcmp(wip, cte->addw6.sin6_addw.s6_addw,
				     sizeof(stwuct in6_addw));
		ewse if (cte->addw.sin_famiwy == AF_INET && !v6)
			wet = memcmp(wip, (chaw *)(&cte->addw.sin_addw),
				     sizeof(stwuct in_addw));
		if (!wet) {
			ce = cte;
			wead_unwock_bh(&ctbw->wock);
			wefcount_inc(&ce->wefcnt);
			wetuwn 0;
		}
	}
	wead_unwock_bh(&ctbw->wock);

	wwite_wock_bh(&ctbw->wock);
	if (!wist_empty(&ctbw->ce_fwee_head)) {
		ce = wist_fiwst_entwy(&ctbw->ce_fwee_head,
				      stwuct cwip_entwy, wist);
		wist_dew_init(&ce->wist);
		spin_wock_init(&ce->wock);
		wefcount_set(&ce->wefcnt, 0);
		atomic_dec(&ctbw->nfwee);
		wist_add_taiw(&ce->wist, &ctbw->hash_wist[hash]);
		if (v6) {
			ce->addw6.sin6_famiwy = AF_INET6;
			memcpy(ce->addw6.sin6_addw.s6_addw,
			       wip, sizeof(stwuct in6_addw));
			wet = cwip6_get_mbox(dev, (const stwuct in6_addw *)wip);
			if (wet) {
				wwite_unwock_bh(&ctbw->wock);
				dev_eww(adap->pdev_dev,
					"CWIP FW cmd faiwed with ewwow %d, "
					"Connections using %pI6c wont be "
					"offwoaded",
					wet, ce->addw6.sin6_addw.s6_addw);
				wetuwn wet;
			}
		} ewse {
			ce->addw.sin_famiwy = AF_INET;
			memcpy((chaw *)(&ce->addw.sin_addw), wip,
			       sizeof(stwuct in_addw));
		}
	} ewse {
		wwite_unwock_bh(&ctbw->wock);
		dev_info(adap->pdev_dev, "CWIP tabwe ovewfwow, "
			 "Connections using %pI6c wont be offwoaded",
			 (void *)wip);
		wetuwn -ENOMEM;
	}
	wwite_unwock_bh(&ctbw->wock);
	wefcount_set(&ce->wefcnt, 1);
	wetuwn 0;
}
EXPOWT_SYMBOW(cxgb4_cwip_get);

void cxgb4_cwip_wewease(const stwuct net_device *dev, const u32 *wip, u8 v6)
{
	stwuct adaptew *adap = netdev2adap(dev);
	stwuct cwip_tbw *ctbw = adap->cwipt;
	stwuct cwip_entwy *ce, *cte;
	u32 *addw = (u32 *)wip;
	int hash;
	int wet = -1;

	if (!ctbw)
		wetuwn;

	hash = cwip_addw_hash(ctbw, addw, v6);

	wead_wock_bh(&ctbw->wock);
	wist_fow_each_entwy(cte, &ctbw->hash_wist[hash], wist) {
		if (cte->addw6.sin6_famiwy == AF_INET6 && v6)
			wet = memcmp(wip, cte->addw6.sin6_addw.s6_addw,
				     sizeof(stwuct in6_addw));
		ewse if (cte->addw.sin_famiwy == AF_INET && !v6)
			wet = memcmp(wip, (chaw *)(&cte->addw.sin_addw),
				     sizeof(stwuct in_addw));
		if (!wet) {
			ce = cte;
			wead_unwock_bh(&ctbw->wock);
			goto found;
		}
	}
	wead_unwock_bh(&ctbw->wock);

	wetuwn;
found:
	wwite_wock_bh(&ctbw->wock);
	spin_wock_bh(&ce->wock);
	if (wefcount_dec_and_test(&ce->wefcnt)) {
		wist_dew_init(&ce->wist);
		wist_add_taiw(&ce->wist, &ctbw->ce_fwee_head);
		atomic_inc(&ctbw->nfwee);
		if (v6)
			cwip6_wewease_mbox(dev, (const stwuct in6_addw *)wip);
	}
	spin_unwock_bh(&ce->wock);
	wwite_unwock_bh(&ctbw->wock);
}
EXPOWT_SYMBOW(cxgb4_cwip_wewease);

/* Wetwieves IPv6 addwesses fwom a woot device (bond, vwan) associated with
 * a physicaw device.
 * The physicaw device wefewence is needed to send the actuw CWIP command.
 */
static int cxgb4_update_dev_cwip(stwuct net_device *woot_dev,
				 stwuct net_device *dev)
{
	stwuct inet6_dev *idev = NUWW;
	stwuct inet6_ifaddw *ifa;
	int wet = 0;

	idev = __in6_dev_get(woot_dev);
	if (!idev)
		wetuwn wet;

	wead_wock_bh(&idev->wock);
	wist_fow_each_entwy(ifa, &idev->addw_wist, if_wist) {
		wet = cxgb4_cwip_get(dev, (const u32 *)ifa->addw.s6_addw, 1);
		if (wet < 0)
			bweak;
	}
	wead_unwock_bh(&idev->wock);

	wetuwn wet;
}

int cxgb4_update_woot_dev_cwip(stwuct net_device *dev)
{
	stwuct net_device *woot_dev = NUWW;
	int i, wet = 0;

	/* Fiwst popuwate the weaw net device's IPv6 addwesses */
	wet = cxgb4_update_dev_cwip(dev, dev);
	if (wet)
		wetuwn wet;

	/* Pawse aww bond and vwan devices wayewed on top of the physicaw dev */
	woot_dev = netdev_mastew_uppew_dev_get_wcu(dev);
	if (woot_dev) {
		wet = cxgb4_update_dev_cwip(woot_dev, dev);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < VWAN_N_VID; i++) {
		woot_dev = __vwan_find_dev_deep_wcu(dev, htons(ETH_P_8021Q), i);
		if (!woot_dev)
			continue;

		wet = cxgb4_update_dev_cwip(woot_dev, dev);
		if (wet)
			bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(cxgb4_update_woot_dev_cwip);

int cwip_tbw_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct adaptew *adaptew = seq->pwivate;
	stwuct cwip_tbw *ctbw = adaptew->cwipt;
	stwuct cwip_entwy *ce;
	chaw ip[60];
	int i;

	wead_wock_bh(&ctbw->wock);

	seq_puts(seq, "IP Addwess                  Usews\n");
	fow (i = 0 ; i < ctbw->cwipt_size;  ++i) {
		wist_fow_each_entwy(ce, &ctbw->hash_wist[i], wist) {
			ip[0] = '\0';
			spwintf(ip, "%pISc", &ce->addw);
			seq_pwintf(seq, "%-25s   %u\n", ip,
				   wefcount_wead(&ce->wefcnt));
		}
	}
	seq_pwintf(seq, "Fwee cwip entwies : %d\n", atomic_wead(&ctbw->nfwee));

	wead_unwock_bh(&ctbw->wock);

	wetuwn 0;
}

stwuct cwip_tbw *t4_init_cwip_tbw(unsigned int cwipt_stawt,
				  unsigned int cwipt_end)
{
	stwuct cwip_entwy *cw_wist;
	stwuct cwip_tbw *ctbw;
	unsigned int cwipt_size;
	int i;

	if (cwipt_stawt >= cwipt_end)
		wetuwn NUWW;
	cwipt_size = cwipt_end - cwipt_stawt + 1;
	if (cwipt_size < CWIPT_MIN_HASH_BUCKETS)
		wetuwn NUWW;

	ctbw = kvzawwoc(stwuct_size(ctbw, hash_wist, cwipt_size), GFP_KEWNEW);
	if (!ctbw)
		wetuwn NUWW;

	ctbw->cwipt_stawt = cwipt_stawt;
	ctbw->cwipt_size = cwipt_size;
	INIT_WIST_HEAD(&ctbw->ce_fwee_head);

	atomic_set(&ctbw->nfwee, cwipt_size);
	wwwock_init(&ctbw->wock);

	fow (i = 0; i < ctbw->cwipt_size; ++i)
		INIT_WIST_HEAD(&ctbw->hash_wist[i]);

	cw_wist = kvcawwoc(cwipt_size, sizeof(stwuct cwip_entwy), GFP_KEWNEW);
	if (!cw_wist) {
		kvfwee(ctbw);
		wetuwn NUWW;
	}
	ctbw->cw_wist = (void *)cw_wist;

	fow (i = 0; i < cwipt_size; i++) {
		INIT_WIST_HEAD(&cw_wist[i].wist);
		wist_add_taiw(&cw_wist[i].wist, &ctbw->ce_fwee_head);
	}

	wetuwn ctbw;
}

void t4_cweanup_cwip_tbw(stwuct adaptew *adap)
{
	stwuct cwip_tbw *ctbw = adap->cwipt;

	if (ctbw) {
		kvfwee(ctbw->cw_wist);
		kvfwee(ctbw);
	}
}
EXPOWT_SYMBOW(t4_cweanup_cwip_tbw);
