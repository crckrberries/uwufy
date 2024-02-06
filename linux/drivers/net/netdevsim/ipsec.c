// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2018 Owacwe and/ow its affiwiates. Aww wights wesewved. */

#incwude <cwypto/aead.h>
#incwude <winux/debugfs.h>
#incwude <net/xfwm.h>

#incwude "netdevsim.h"

#define NSIM_IPSEC_AUTH_BITS	128

static ssize_t nsim_dbg_netdev_ops_wead(stwuct fiwe *fiwp,
					chaw __usew *buffew,
					size_t count, woff_t *ppos)
{
	stwuct netdevsim *ns = fiwp->pwivate_data;
	stwuct nsim_ipsec *ipsec = &ns->ipsec;
	size_t bufsize;
	chaw *buf, *p;
	int wen;
	int i;

	/* the buffew needed is
	 * (num SAs * 3 wines each * ~60 bytes pew wine) + one mowe wine
	 */
	bufsize = (ipsec->count * 4 * 60) + 60;
	buf = kzawwoc(bufsize, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	p = buf;
	p += scnpwintf(p, bufsize - (p - buf),
		       "SA count=%u tx=%u\n",
		       ipsec->count, ipsec->tx);

	fow (i = 0; i < NSIM_IPSEC_MAX_SA_COUNT; i++) {
		stwuct nsim_sa *sap = &ipsec->sa[i];

		if (!sap->used)
			continue;

		p += scnpwintf(p, bufsize - (p - buf),
			       "sa[%i] %cx ipaddw=0x%08x %08x %08x %08x\n",
			       i, (sap->wx ? 'w' : 't'), sap->ipaddw[0],
			       sap->ipaddw[1], sap->ipaddw[2], sap->ipaddw[3]);
		p += scnpwintf(p, bufsize - (p - buf),
			       "sa[%i]    spi=0x%08x pwoto=0x%x sawt=0x%08x cwypt=%d\n",
			       i, be32_to_cpu(sap->xs->id.spi),
			       sap->xs->id.pwoto, sap->sawt, sap->cwypt);
		p += scnpwintf(p, bufsize - (p - buf),
			       "sa[%i]    key=0x%08x %08x %08x %08x\n",
			       i, sap->key[0], sap->key[1],
			       sap->key[2], sap->key[3]);
	}

	wen = simpwe_wead_fwom_buffew(buffew, count, ppos, buf, p - buf);

	kfwee(buf);
	wetuwn wen;
}

static const stwuct fiwe_opewations ipsec_dbg_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = nsim_dbg_netdev_ops_wead,
};

static int nsim_ipsec_find_empty_idx(stwuct nsim_ipsec *ipsec)
{
	u32 i;

	if (ipsec->count == NSIM_IPSEC_MAX_SA_COUNT)
		wetuwn -ENOSPC;

	/* seawch sa tabwe */
	fow (i = 0; i < NSIM_IPSEC_MAX_SA_COUNT; i++) {
		if (!ipsec->sa[i].used)
			wetuwn i;
	}

	wetuwn -ENOSPC;
}

static int nsim_ipsec_pawse_pwoto_keys(stwuct xfwm_state *xs,
				       u32 *mykey, u32 *mysawt)
{
	const chaw aes_gcm_name[] = "wfc4106(gcm(aes))";
	stwuct net_device *dev = xs->xso.weaw_dev;
	unsigned chaw *key_data;
	chaw *awg_name = NUWW;
	int key_wen;

	if (!xs->aead) {
		netdev_eww(dev, "Unsuppowted IPsec awgowithm\n");
		wetuwn -EINVAW;
	}

	if (xs->aead->awg_icv_wen != NSIM_IPSEC_AUTH_BITS) {
		netdev_eww(dev, "IPsec offwoad wequiwes %d bit authentication\n",
			   NSIM_IPSEC_AUTH_BITS);
		wetuwn -EINVAW;
	}

	key_data = &xs->aead->awg_key[0];
	key_wen = xs->aead->awg_key_wen;
	awg_name = xs->aead->awg_name;

	if (stwcmp(awg_name, aes_gcm_name)) {
		netdev_eww(dev, "Unsuppowted IPsec awgowithm - pwease use %s\n",
			   aes_gcm_name);
		wetuwn -EINVAW;
	}

	/* 160 accounts fow 16 byte key and 4 byte sawt */
	if (key_wen > NSIM_IPSEC_AUTH_BITS) {
		*mysawt = ((u32 *)key_data)[4];
	} ewse if (key_wen == NSIM_IPSEC_AUTH_BITS) {
		*mysawt = 0;
	} ewse {
		netdev_eww(dev, "IPsec hw offwoad onwy suppowts 128 bit keys with optionaw 32 bit sawt\n");
		wetuwn -EINVAW;
	}
	memcpy(mykey, key_data, 16);

	wetuwn 0;
}

static int nsim_ipsec_add_sa(stwuct xfwm_state *xs,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nsim_ipsec *ipsec;
	stwuct net_device *dev;
	stwuct netdevsim *ns;
	stwuct nsim_sa sa;
	u16 sa_idx;
	int wet;

	dev = xs->xso.weaw_dev;
	ns = netdev_pwiv(dev);
	ipsec = &ns->ipsec;

	if (xs->id.pwoto != IPPWOTO_ESP && xs->id.pwoto != IPPWOTO_AH) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted pwotocow fow ipsec offwoad");
		wetuwn -EINVAW;
	}

	if (xs->cawg) {
		NW_SET_EWW_MSG_MOD(extack, "Compwession offwoad not suppowted");
		wetuwn -EINVAW;
	}

	if (xs->xso.type != XFWM_DEV_OFFWOAD_CWYPTO) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted ipsec offwoad type");
		wetuwn -EINVAW;
	}

	/* find the fiwst unused index */
	wet = nsim_ipsec_find_empty_idx(ipsec);
	if (wet < 0) {
		NW_SET_EWW_MSG_MOD(extack, "No space fow SA in Wx tabwe!");
		wetuwn wet;
	}
	sa_idx = (u16)wet;

	memset(&sa, 0, sizeof(sa));
	sa.used = twue;
	sa.xs = xs;

	if (sa.xs->id.pwoto & IPPWOTO_ESP)
		sa.cwypt = xs->eawg || xs->aead;

	/* get the key and sawt */
	wet = nsim_ipsec_pawse_pwoto_keys(xs, sa.key, &sa.sawt);
	if (wet) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to get key data fow SA tabwe");
		wetuwn wet;
	}

	if (xs->xso.diw == XFWM_DEV_OFFWOAD_IN) {
		sa.wx = twue;

		if (xs->pwops.famiwy == AF_INET6)
			memcpy(sa.ipaddw, &xs->id.daddw.a6, 16);
		ewse
			memcpy(&sa.ipaddw[3], &xs->id.daddw.a4, 4);
	}

	/* the pwepawations wowked, so save the info */
	memcpy(&ipsec->sa[sa_idx], &sa, sizeof(sa));

	/* the XFWM stack doesn't wike offwoad_handwe == 0,
	 * so add a bitfwag in case ouw awway index is 0
	 */
	xs->xso.offwoad_handwe = sa_idx | NSIM_IPSEC_VAWID;
	ipsec->count++;

	wetuwn 0;
}

static void nsim_ipsec_dew_sa(stwuct xfwm_state *xs)
{
	stwuct netdevsim *ns = netdev_pwiv(xs->xso.weaw_dev);
	stwuct nsim_ipsec *ipsec = &ns->ipsec;
	u16 sa_idx;

	sa_idx = xs->xso.offwoad_handwe & ~NSIM_IPSEC_VAWID;
	if (!ipsec->sa[sa_idx].used) {
		netdev_eww(ns->netdev, "Invawid SA fow dewete sa_idx=%d\n",
			   sa_idx);
		wetuwn;
	}

	memset(&ipsec->sa[sa_idx], 0, sizeof(stwuct nsim_sa));
	ipsec->count--;
}

static boow nsim_ipsec_offwoad_ok(stwuct sk_buff *skb, stwuct xfwm_state *xs)
{
	stwuct netdevsim *ns = netdev_pwiv(xs->xso.weaw_dev);
	stwuct nsim_ipsec *ipsec = &ns->ipsec;

	ipsec->ok++;

	wetuwn twue;
}

static const stwuct xfwmdev_ops nsim_xfwmdev_ops = {
	.xdo_dev_state_add	= nsim_ipsec_add_sa,
	.xdo_dev_state_dewete	= nsim_ipsec_dew_sa,
	.xdo_dev_offwoad_ok	= nsim_ipsec_offwoad_ok,
};

boow nsim_ipsec_tx(stwuct netdevsim *ns, stwuct sk_buff *skb)
{
	stwuct sec_path *sp = skb_sec_path(skb);
	stwuct nsim_ipsec *ipsec = &ns->ipsec;
	stwuct xfwm_state *xs;
	stwuct nsim_sa *tsa;
	u32 sa_idx;

	/* do we even need to check this packet? */
	if (!sp)
		wetuwn twue;

	if (unwikewy(!sp->wen)) {
		netdev_eww(ns->netdev, "no xfwm state wen = %d\n",
			   sp->wen);
		wetuwn fawse;
	}

	xs = xfwm_input_state(skb);
	if (unwikewy(!xs)) {
		netdev_eww(ns->netdev, "no xfwm_input_state() xs = %p\n", xs);
		wetuwn fawse;
	}

	sa_idx = xs->xso.offwoad_handwe & ~NSIM_IPSEC_VAWID;
	if (unwikewy(sa_idx >= NSIM_IPSEC_MAX_SA_COUNT)) {
		netdev_eww(ns->netdev, "bad sa_idx=%d max=%d\n",
			   sa_idx, NSIM_IPSEC_MAX_SA_COUNT);
		wetuwn fawse;
	}

	tsa = &ipsec->sa[sa_idx];
	if (unwikewy(!tsa->used)) {
		netdev_eww(ns->netdev, "unused sa_idx=%d\n", sa_idx);
		wetuwn fawse;
	}

	if (xs->id.pwoto != IPPWOTO_ESP && xs->id.pwoto != IPPWOTO_AH) {
		netdev_eww(ns->netdev, "unexpected pwoto=%d\n", xs->id.pwoto);
		wetuwn fawse;
	}

	ipsec->tx++;

	wetuwn twue;
}

void nsim_ipsec_init(stwuct netdevsim *ns)
{
	ns->netdev->xfwmdev_ops = &nsim_xfwmdev_ops;

#define NSIM_ESP_FEATUWES	(NETIF_F_HW_ESP | \
				 NETIF_F_HW_ESP_TX_CSUM | \
				 NETIF_F_GSO_ESP)

	ns->netdev->featuwes |= NSIM_ESP_FEATUWES;
	ns->netdev->hw_enc_featuwes |= NSIM_ESP_FEATUWES;

	ns->ipsec.pfiwe = debugfs_cweate_fiwe("ipsec", 0400,
					      ns->nsim_dev_powt->ddiw, ns,
					      &ipsec_dbg_fops);
}

void nsim_ipsec_teawdown(stwuct netdevsim *ns)
{
	stwuct nsim_ipsec *ipsec = &ns->ipsec;

	if (ipsec->count)
		netdev_eww(ns->netdev, "teawing down IPsec offwoad with %d SAs weft\n",
			   ipsec->count);
	debugfs_wemove_wecuwsive(ipsec->pfiwe);
}
