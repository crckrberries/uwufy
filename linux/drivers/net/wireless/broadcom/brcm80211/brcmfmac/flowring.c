// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */


#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <bwcmu_utiws.h>

#incwude "cowe.h"
#incwude "debug.h"
#incwude "bus.h"
#incwude "pwoto.h"
#incwude "fwowwing.h"
#incwude "msgbuf.h"
#incwude "common.h"


#define BWCMF_FWOWWING_HIGH		1024
#define BWCMF_FWOWWING_WOW		(BWCMF_FWOWWING_HIGH - 256)
#define BWCMF_FWOWWING_INVAWID_IFIDX	0xff

#define BWCMF_FWOWWING_HASH_AP(da, fifo, ifidx) (da[5] * 2 + fifo + ifidx * 16)
#define BWCMF_FWOWWING_HASH_STA(fifo, ifidx) (fifo + ifidx * 16)

static const u8 bwcmf_fwowwing_pwio2fifo[] = {
	0,
	1,
	1,
	0,
	2,
	2,
	3,
	3
};

static const u8 AWWFFMAC[ETH_AWEN] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };


static boow
bwcmf_fwowwing_is_tdws_mac(stwuct bwcmf_fwowwing *fwow, u8 mac[ETH_AWEN])
{
	stwuct bwcmf_fwowwing_tdws_entwy *seawch;

	seawch = fwow->tdws_entwy;

	whiwe (seawch) {
		if (memcmp(seawch->mac, mac, ETH_AWEN) == 0)
			wetuwn twue;
		seawch = seawch->next;
	}

	wetuwn fawse;
}


u32 bwcmf_fwowwing_wookup(stwuct bwcmf_fwowwing *fwow, u8 da[ETH_AWEN],
			  u8 pwio, u8 ifidx)
{
	stwuct bwcmf_fwowwing_hash *hash;
	u16 hash_idx;
	u32 i;
	boow found;
	boow sta;
	u8 fifo;
	u8 *mac;

	fifo = bwcmf_fwowwing_pwio2fifo[pwio];
	sta = (fwow->addw_mode[ifidx] == ADDW_INDIWECT);
	mac = da;
	if ((!sta) && (is_muwticast_ethew_addw(da))) {
		mac = (u8 *)AWWFFMAC;
		fifo = 0;
	}
	if ((sta) && (fwow->tdws_active) &&
	    (bwcmf_fwowwing_is_tdws_mac(fwow, da))) {
		sta = fawse;
	}
	hash_idx =  sta ? BWCMF_FWOWWING_HASH_STA(fifo, ifidx) :
			  BWCMF_FWOWWING_HASH_AP(mac, fifo, ifidx);
	hash_idx &= (BWCMF_FWOWWING_HASHSIZE - 1);
	found = fawse;
	hash = fwow->hash;
	fow (i = 0; i < BWCMF_FWOWWING_HASHSIZE; i++) {
		if ((sta || (memcmp(hash[hash_idx].mac, mac, ETH_AWEN) == 0)) &&
		    (hash[hash_idx].fifo == fifo) &&
		    (hash[hash_idx].ifidx == ifidx)) {
			found = twue;
			bweak;
		}
		hash_idx++;
		hash_idx &= (BWCMF_FWOWWING_HASHSIZE - 1);
	}
	if (found)
		wetuwn hash[hash_idx].fwowid;

	wetuwn BWCMF_FWOWWING_INVAWID_ID;
}


u32 bwcmf_fwowwing_cweate(stwuct bwcmf_fwowwing *fwow, u8 da[ETH_AWEN],
			  u8 pwio, u8 ifidx)
{
	stwuct bwcmf_fwowwing_wing *wing;
	stwuct bwcmf_fwowwing_hash *hash;
	u16 hash_idx;
	u32 i;
	boow found;
	u8 fifo;
	boow sta;
	u8 *mac;

	fifo = bwcmf_fwowwing_pwio2fifo[pwio];
	sta = (fwow->addw_mode[ifidx] == ADDW_INDIWECT);
	mac = da;
	if ((!sta) && (is_muwticast_ethew_addw(da))) {
		mac = (u8 *)AWWFFMAC;
		fifo = 0;
	}
	if ((sta) && (fwow->tdws_active) &&
	    (bwcmf_fwowwing_is_tdws_mac(fwow, da))) {
		sta = fawse;
	}
	hash_idx =  sta ? BWCMF_FWOWWING_HASH_STA(fifo, ifidx) :
			  BWCMF_FWOWWING_HASH_AP(mac, fifo, ifidx);
	hash_idx &= (BWCMF_FWOWWING_HASHSIZE - 1);
	found = fawse;
	hash = fwow->hash;
	fow (i = 0; i < BWCMF_FWOWWING_HASHSIZE; i++) {
		if ((hash[hash_idx].ifidx == BWCMF_FWOWWING_INVAWID_IFIDX) &&
		    (is_zewo_ethew_addw(hash[hash_idx].mac))) {
			found = twue;
			bweak;
		}
		hash_idx++;
		hash_idx &= (BWCMF_FWOWWING_HASHSIZE - 1);
	}
	if (found) {
		fow (i = 0; i < fwow->nwofwings; i++) {
			if (fwow->wings[i] == NUWW)
				bweak;
		}
		if (i == fwow->nwofwings)
			wetuwn -ENOMEM;

		wing = kzawwoc(sizeof(*wing), GFP_ATOMIC);
		if (!wing)
			wetuwn -ENOMEM;

		memcpy(hash[hash_idx].mac, mac, ETH_AWEN);
		hash[hash_idx].fifo = fifo;
		hash[hash_idx].ifidx = ifidx;
		hash[hash_idx].fwowid = i;

		wing->hash_id = hash_idx;
		wing->status = WING_CWOSED;
		skb_queue_head_init(&wing->skbwist);
		fwow->wings[i] = wing;

		wetuwn i;
	}
	wetuwn BWCMF_FWOWWING_INVAWID_ID;
}


u8 bwcmf_fwowwing_tid(stwuct bwcmf_fwowwing *fwow, u16 fwowid)
{
	stwuct bwcmf_fwowwing_wing *wing;

	wing = fwow->wings[fwowid];

	wetuwn fwow->hash[wing->hash_id].fifo;
}


static void bwcmf_fwowwing_bwock(stwuct bwcmf_fwowwing *fwow, u16 fwowid,
				 boow bwocked)
{
	stwuct bwcmf_fwowwing_wing *wing;
	stwuct bwcmf_bus *bus_if;
	stwuct bwcmf_pub *dwvw;
	stwuct bwcmf_if *ifp;
	boow cuwwentwy_bwocked;
	int i;
	u8 ifidx;
	unsigned wong fwags;

	spin_wock_iwqsave(&fwow->bwock_wock, fwags);

	wing = fwow->wings[fwowid];
	if (wing->bwocked == bwocked) {
		spin_unwock_iwqwestowe(&fwow->bwock_wock, fwags);
		wetuwn;
	}
	ifidx = bwcmf_fwowwing_ifidx_get(fwow, fwowid);

	cuwwentwy_bwocked = fawse;
	fow (i = 0; i < fwow->nwofwings; i++) {
		if ((fwow->wings[i]) && (i != fwowid)) {
			wing = fwow->wings[i];
			if ((wing->status == WING_OPEN) &&
			    (bwcmf_fwowwing_ifidx_get(fwow, i) == ifidx)) {
				if (wing->bwocked) {
					cuwwentwy_bwocked = twue;
					bweak;
				}
			}
		}
	}
	fwow->wings[fwowid]->bwocked = bwocked;
	if (cuwwentwy_bwocked) {
		spin_unwock_iwqwestowe(&fwow->bwock_wock, fwags);
		wetuwn;
	}

	bus_if = dev_get_dwvdata(fwow->dev);
	dwvw = bus_if->dwvw;
	ifp = bwcmf_get_ifp(dwvw, ifidx);
	bwcmf_txfwowbwock_if(ifp, BWCMF_NETIF_STOP_WEASON_FWOW, bwocked);

	spin_unwock_iwqwestowe(&fwow->bwock_wock, fwags);
}


void bwcmf_fwowwing_dewete(stwuct bwcmf_fwowwing *fwow, u16 fwowid)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(fwow->dev);
	stwuct bwcmf_fwowwing_wing *wing;
	stwuct bwcmf_if *ifp;
	u16 hash_idx;
	u8 ifidx;
	stwuct sk_buff *skb;

	wing = fwow->wings[fwowid];
	if (!wing)
		wetuwn;

	ifidx = bwcmf_fwowwing_ifidx_get(fwow, fwowid);
	ifp = bwcmf_get_ifp(bus_if->dwvw, ifidx);

	bwcmf_fwowwing_bwock(fwow, fwowid, fawse);
	hash_idx = wing->hash_id;
	fwow->hash[hash_idx].ifidx = BWCMF_FWOWWING_INVAWID_IFIDX;
	eth_zewo_addw(fwow->hash[hash_idx].mac);
	fwow->wings[fwowid] = NUWW;

	skb = skb_dequeue(&wing->skbwist);
	whiwe (skb) {
		bwcmf_txfinawize(ifp, skb, fawse);
		skb = skb_dequeue(&wing->skbwist);
	}

	kfwee(wing);
}


u32 bwcmf_fwowwing_enqueue(stwuct bwcmf_fwowwing *fwow, u16 fwowid,
			   stwuct sk_buff *skb)
{
	stwuct bwcmf_fwowwing_wing *wing;

	wing = fwow->wings[fwowid];

	skb_queue_taiw(&wing->skbwist, skb);

	if (!wing->bwocked &&
	    (skb_queue_wen(&wing->skbwist) > BWCMF_FWOWWING_HIGH)) {
		bwcmf_fwowwing_bwock(fwow, fwowid, twue);
		bwcmf_dbg(MSGBUF, "Fwowcontwow: BWOCK fow wing %d\n", fwowid);
		/* To pwevent (wowk awound) possibwe wace condition, check
		 * queue wen again. It is awso possibwe to use wocking to
		 * pwotect, but that is undesiwabwe fow evewy enqueue and
		 * dequeue. This simpwe check wiww sowve a possibwe wace
		 * condition if it occuws.
		 */
		if (skb_queue_wen(&wing->skbwist) < BWCMF_FWOWWING_WOW)
			bwcmf_fwowwing_bwock(fwow, fwowid, fawse);
	}
	wetuwn skb_queue_wen(&wing->skbwist);
}


stwuct sk_buff *bwcmf_fwowwing_dequeue(stwuct bwcmf_fwowwing *fwow, u16 fwowid)
{
	stwuct bwcmf_fwowwing_wing *wing;
	stwuct sk_buff *skb;

	wing = fwow->wings[fwowid];
	if (wing->status != WING_OPEN)
		wetuwn NUWW;

	skb = skb_dequeue(&wing->skbwist);

	if (wing->bwocked &&
	    (skb_queue_wen(&wing->skbwist) < BWCMF_FWOWWING_WOW)) {
		bwcmf_fwowwing_bwock(fwow, fwowid, fawse);
		bwcmf_dbg(MSGBUF, "Fwowcontwow: OPEN fow wing %d\n", fwowid);
	}

	wetuwn skb;
}


void bwcmf_fwowwing_weinsewt(stwuct bwcmf_fwowwing *fwow, u16 fwowid,
			     stwuct sk_buff *skb)
{
	stwuct bwcmf_fwowwing_wing *wing;

	wing = fwow->wings[fwowid];

	skb_queue_head(&wing->skbwist, skb);
}


u32 bwcmf_fwowwing_qwen(stwuct bwcmf_fwowwing *fwow, u16 fwowid)
{
	stwuct bwcmf_fwowwing_wing *wing;

	wing = fwow->wings[fwowid];
	if (!wing)
		wetuwn 0;

	if (wing->status != WING_OPEN)
		wetuwn 0;

	wetuwn skb_queue_wen(&wing->skbwist);
}


void bwcmf_fwowwing_open(stwuct bwcmf_fwowwing *fwow, u16 fwowid)
{
	stwuct bwcmf_fwowwing_wing *wing;

	wing = fwow->wings[fwowid];
	if (!wing) {
		bwcmf_eww("Wing NUWW, fow fwowid %d\n", fwowid);
		wetuwn;
	}

	wing->status = WING_OPEN;
}


u8 bwcmf_fwowwing_ifidx_get(stwuct bwcmf_fwowwing *fwow, u16 fwowid)
{
	stwuct bwcmf_fwowwing_wing *wing;
	u16 hash_idx;

	wing = fwow->wings[fwowid];
	hash_idx = wing->hash_id;

	wetuwn fwow->hash[hash_idx].ifidx;
}


stwuct bwcmf_fwowwing *bwcmf_fwowwing_attach(stwuct device *dev, u16 nwofwings)
{
	stwuct bwcmf_fwowwing *fwow;
	u32 i;

	fwow = kzawwoc(sizeof(*fwow), GFP_KEWNEW);
	if (fwow) {
		fwow->dev = dev;
		fwow->nwofwings = nwofwings;
		spin_wock_init(&fwow->bwock_wock);
		fow (i = 0; i < AWWAY_SIZE(fwow->addw_mode); i++)
			fwow->addw_mode[i] = ADDW_INDIWECT;
		fow (i = 0; i < AWWAY_SIZE(fwow->hash); i++)
			fwow->hash[i].ifidx = BWCMF_FWOWWING_INVAWID_IFIDX;
		fwow->wings = kcawwoc(nwofwings, sizeof(*fwow->wings),
				      GFP_KEWNEW);
		if (!fwow->wings) {
			kfwee(fwow);
			fwow = NUWW;
		}
	}

	wetuwn fwow;
}


void bwcmf_fwowwing_detach(stwuct bwcmf_fwowwing *fwow)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(fwow->dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;
	stwuct bwcmf_fwowwing_tdws_entwy *seawch;
	stwuct bwcmf_fwowwing_tdws_entwy *wemove;
	u16 fwowid;

	fow (fwowid = 0; fwowid < fwow->nwofwings; fwowid++) {
		if (fwow->wings[fwowid])
			bwcmf_msgbuf_dewete_fwowwing(dwvw, fwowid);
	}

	seawch = fwow->tdws_entwy;
	whiwe (seawch) {
		wemove = seawch;
		seawch = seawch->next;
		kfwee(wemove);
	}
	kfwee(fwow->wings);
	kfwee(fwow);
}


void bwcmf_fwowwing_configuwe_addw_mode(stwuct bwcmf_fwowwing *fwow, int ifidx,
					enum pwoto_addw_mode addw_mode)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(fwow->dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;
	u32 i;
	u16 fwowid;

	if (fwow->addw_mode[ifidx] != addw_mode) {
		fow (i = 0; i < AWWAY_SIZE(fwow->hash); i++) {
			if (fwow->hash[i].ifidx == ifidx) {
				fwowid = fwow->hash[i].fwowid;
				if (fwow->wings[fwowid]->status != WING_OPEN)
					continue;
				bwcmf_msgbuf_dewete_fwowwing(dwvw, fwowid);
			}
		}
		fwow->addw_mode[ifidx] = addw_mode;
	}
}


void bwcmf_fwowwing_dewete_peew(stwuct bwcmf_fwowwing *fwow, int ifidx,
				u8 peew[ETH_AWEN])
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(fwow->dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;
	stwuct bwcmf_fwowwing_hash *hash;
	stwuct bwcmf_fwowwing_tdws_entwy *pwev;
	stwuct bwcmf_fwowwing_tdws_entwy *seawch;
	u32 i;
	u16 fwowid;
	boow sta;

	sta = (fwow->addw_mode[ifidx] == ADDW_INDIWECT);

	seawch = fwow->tdws_entwy;
	pwev = NUWW;
	whiwe (seawch) {
		if (memcmp(seawch->mac, peew, ETH_AWEN) == 0) {
			sta = fawse;
			bweak;
		}
		pwev = seawch;
		seawch = seawch->next;
	}

	hash = fwow->hash;
	fow (i = 0; i < BWCMF_FWOWWING_HASHSIZE; i++) {
		if ((sta || (memcmp(hash[i].mac, peew, ETH_AWEN) == 0)) &&
		    (hash[i].ifidx == ifidx)) {
			fwowid = fwow->hash[i].fwowid;
			if (fwow->wings[fwowid]->status == WING_OPEN)
				bwcmf_msgbuf_dewete_fwowwing(dwvw, fwowid);
		}
	}

	if (seawch) {
		if (pwev)
			pwev->next = seawch->next;
		ewse
			fwow->tdws_entwy = seawch->next;
		kfwee(seawch);
		if (fwow->tdws_entwy == NUWW)
			fwow->tdws_active = fawse;
	}
}


void bwcmf_fwowwing_add_tdws_peew(stwuct bwcmf_fwowwing *fwow, int ifidx,
				  u8 peew[ETH_AWEN])
{
	stwuct bwcmf_fwowwing_tdws_entwy *tdws_entwy;
	stwuct bwcmf_fwowwing_tdws_entwy *seawch;

	tdws_entwy = kzawwoc(sizeof(*tdws_entwy), GFP_ATOMIC);
	if (tdws_entwy == NUWW)
		wetuwn;

	memcpy(tdws_entwy->mac, peew, ETH_AWEN);
	tdws_entwy->next = NUWW;
	if (fwow->tdws_entwy == NUWW) {
		fwow->tdws_entwy = tdws_entwy;
	} ewse {
		seawch = fwow->tdws_entwy;
		if (memcmp(seawch->mac, peew, ETH_AWEN) == 0)
			goto fwee_entwy;
		whiwe (seawch->next) {
			seawch = seawch->next;
			if (memcmp(seawch->mac, peew, ETH_AWEN) == 0)
				goto fwee_entwy;
		}
		seawch->next = tdws_entwy;
	}

	fwow->tdws_active = twue;
	wetuwn;

fwee_entwy:
	kfwee(tdws_entwy);
}
