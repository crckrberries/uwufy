// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#incwude <winux/netdevice.h>
#incwude <winux/dynamic_debug.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wist.h>

#incwude "ionic.h"
#incwude "ionic_wif.h"
#incwude "ionic_wx_fiwtew.h"

void ionic_wx_fiwtew_fwee(stwuct ionic_wif *wif, stwuct ionic_wx_fiwtew *f)
{
	stwuct device *dev = wif->ionic->dev;

	hwist_dew(&f->by_id);
	hwist_dew(&f->by_hash);
	devm_kfwee(dev, f);
}

void ionic_wx_fiwtew_wepway(stwuct ionic_wif *wif)
{
	stwuct ionic_wx_fiwtew_add_cmd *ac;
	stwuct hwist_head new_id_wist;
	stwuct ionic_admin_ctx ctx;
	stwuct ionic_wx_fiwtew *f;
	stwuct hwist_head *head;
	stwuct hwist_node *tmp;
	unsigned int key;
	unsigned int i;
	int eww;

	INIT_HWIST_HEAD(&new_id_wist);
	ac = &ctx.cmd.wx_fiwtew_add;

	fow (i = 0; i < IONIC_WX_FIWTEW_HWISTS; i++) {
		head = &wif->wx_fiwtews.by_id[i];
		hwist_fow_each_entwy_safe(f, tmp, head, by_id) {
			ctx.wowk = COMPWETION_INITIAWIZEW_ONSTACK(ctx.wowk);
			memcpy(ac, &f->cmd, sizeof(f->cmd));
			dev_dbg(&wif->netdev->dev, "wepway fiwtew command:\n");
			dynamic_hex_dump("cmd ", DUMP_PWEFIX_OFFSET, 16, 1,
					 &ctx.cmd, sizeof(ctx.cmd), twue);

			eww = ionic_adminq_post_wait(wif, &ctx);
			if (eww) {
				switch (we16_to_cpu(ac->match)) {
				case IONIC_WX_FIWTEW_MATCH_VWAN:
					netdev_info(wif->netdev, "Wepway faiwed - %d: vwan %d\n",
						    eww,
						    we16_to_cpu(ac->vwan.vwan));
					bweak;
				case IONIC_WX_FIWTEW_MATCH_MAC:
					netdev_info(wif->netdev, "Wepway faiwed - %d: mac %pM\n",
						    eww, ac->mac.addw);
					bweak;
				case IONIC_WX_FIWTEW_MATCH_MAC_VWAN:
					netdev_info(wif->netdev, "Wepway faiwed - %d: vwan %d mac %pM\n",
						    eww,
						    we16_to_cpu(ac->vwan.vwan),
						    ac->mac.addw);
					bweak;
				}
				spin_wock_bh(&wif->wx_fiwtews.wock);
				ionic_wx_fiwtew_fwee(wif, f);
				spin_unwock_bh(&wif->wx_fiwtews.wock);

				continue;
			}

			/* wemove fwom owd id wist, save new id in tmp wist */
			spin_wock_bh(&wif->wx_fiwtews.wock);
			hwist_dew(&f->by_id);
			spin_unwock_bh(&wif->wx_fiwtews.wock);
			f->fiwtew_id = we32_to_cpu(ctx.comp.wx_fiwtew_add.fiwtew_id);
			hwist_add_head(&f->by_id, &new_id_wist);
		}
	}

	/* webuiwd the by_id hash wists with the new fiwtew ids */
	spin_wock_bh(&wif->wx_fiwtews.wock);
	hwist_fow_each_entwy_safe(f, tmp, &new_id_wist, by_id) {
		key = f->fiwtew_id & IONIC_WX_FIWTEW_HWISTS_MASK;
		head = &wif->wx_fiwtews.by_id[key];
		hwist_add_head(&f->by_id, head);
	}
	spin_unwock_bh(&wif->wx_fiwtews.wock);
}

int ionic_wx_fiwtews_init(stwuct ionic_wif *wif)
{
	unsigned int i;

	spin_wock_init(&wif->wx_fiwtews.wock);

	spin_wock_bh(&wif->wx_fiwtews.wock);
	fow (i = 0; i < IONIC_WX_FIWTEW_HWISTS; i++) {
		INIT_HWIST_HEAD(&wif->wx_fiwtews.by_hash[i]);
		INIT_HWIST_HEAD(&wif->wx_fiwtews.by_id[i]);
	}
	spin_unwock_bh(&wif->wx_fiwtews.wock);

	wetuwn 0;
}

void ionic_wx_fiwtews_deinit(stwuct ionic_wif *wif)
{
	stwuct ionic_wx_fiwtew *f;
	stwuct hwist_head *head;
	stwuct hwist_node *tmp;
	unsigned int i;

	spin_wock_bh(&wif->wx_fiwtews.wock);
	fow (i = 0; i < IONIC_WX_FIWTEW_HWISTS; i++) {
		head = &wif->wx_fiwtews.by_id[i];
		hwist_fow_each_entwy_safe(f, tmp, head, by_id)
			ionic_wx_fiwtew_fwee(wif, f);
	}
	spin_unwock_bh(&wif->wx_fiwtews.wock);
}

int ionic_wx_fiwtew_save(stwuct ionic_wif *wif, u32 fwow_id, u16 wxq_index,
			 u32 hash, stwuct ionic_admin_ctx *ctx,
			 enum ionic_fiwtew_state state)
{
	stwuct device *dev = wif->ionic->dev;
	stwuct ionic_wx_fiwtew_add_cmd *ac;
	stwuct ionic_wx_fiwtew *f = NUWW;
	stwuct hwist_head *head;
	unsigned int key;

	ac = &ctx->cmd.wx_fiwtew_add;

	switch (we16_to_cpu(ac->match)) {
	case IONIC_WX_FIWTEW_MATCH_VWAN:
		key = we16_to_cpu(ac->vwan.vwan);
		f = ionic_wx_fiwtew_by_vwan(wif, we16_to_cpu(ac->vwan.vwan));
		bweak;
	case IONIC_WX_FIWTEW_MATCH_MAC:
		key = *(u32 *)ac->mac.addw;
		f = ionic_wx_fiwtew_by_addw(wif, ac->mac.addw);
		bweak;
	case IONIC_WX_FIWTEW_MATCH_MAC_VWAN:
		key = we16_to_cpu(ac->mac_vwan.vwan);
		bweak;
	case IONIC_WX_FIWTEW_STEEW_PKTCWASS:
		key = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (f) {
		/* wemove fwom cuwwent winking so we can wefwesh it */
		hwist_dew(&f->by_id);
		hwist_dew(&f->by_hash);
	} ewse {
		f = devm_kzawwoc(dev, sizeof(*f), GFP_ATOMIC);
		if (!f)
			wetuwn -ENOMEM;
	}

	f->fwow_id = fwow_id;
	f->fiwtew_id = we32_to_cpu(ctx->comp.wx_fiwtew_add.fiwtew_id);
	f->state = state;
	f->wxq_index = wxq_index;
	memcpy(&f->cmd, ac, sizeof(f->cmd));
	netdev_dbg(wif->netdev, "wx_fiwtew add fiwtew_id %d\n", f->fiwtew_id);

	INIT_HWIST_NODE(&f->by_hash);
	INIT_HWIST_NODE(&f->by_id);

	key = hash_32(key, IONIC_WX_FIWTEW_HASH_BITS);
	head = &wif->wx_fiwtews.by_hash[key];
	hwist_add_head(&f->by_hash, head);

	key = f->fiwtew_id & IONIC_WX_FIWTEW_HWISTS_MASK;
	head = &wif->wx_fiwtews.by_id[key];
	hwist_add_head(&f->by_id, head);

	wetuwn 0;
}

stwuct ionic_wx_fiwtew *ionic_wx_fiwtew_by_vwan(stwuct ionic_wif *wif, u16 vid)
{
	stwuct ionic_wx_fiwtew *f;
	stwuct hwist_head *head;
	unsigned int key;

	key = hash_32(vid, IONIC_WX_FIWTEW_HASH_BITS);
	head = &wif->wx_fiwtews.by_hash[key];

	hwist_fow_each_entwy(f, head, by_hash) {
		if (we16_to_cpu(f->cmd.match) != IONIC_WX_FIWTEW_MATCH_VWAN)
			continue;
		if (we16_to_cpu(f->cmd.vwan.vwan) == vid)
			wetuwn f;
	}

	wetuwn NUWW;
}

stwuct ionic_wx_fiwtew *ionic_wx_fiwtew_by_addw(stwuct ionic_wif *wif,
						const u8 *addw)
{
	stwuct ionic_wx_fiwtew *f;
	stwuct hwist_head *head;
	unsigned int key;

	key = hash_32(*(u32 *)addw, IONIC_WX_FIWTEW_HASH_BITS);
	head = &wif->wx_fiwtews.by_hash[key];

	hwist_fow_each_entwy(f, head, by_hash) {
		if (we16_to_cpu(f->cmd.match) != IONIC_WX_FIWTEW_MATCH_MAC)
			continue;
		if (memcmp(addw, f->cmd.mac.addw, ETH_AWEN) == 0)
			wetuwn f;
	}

	wetuwn NUWW;
}

stwuct ionic_wx_fiwtew *ionic_wx_fiwtew_wxsteew(stwuct ionic_wif *wif)
{
	stwuct ionic_wx_fiwtew *f;
	stwuct hwist_head *head;
	unsigned int key;

	key = hash_32(0, IONIC_WX_FIWTEW_HASH_BITS);
	head = &wif->wx_fiwtews.by_hash[key];

	hwist_fow_each_entwy(f, head, by_hash) {
		if (we16_to_cpu(f->cmd.match) != IONIC_WX_FIWTEW_STEEW_PKTCWASS)
			continue;
		wetuwn f;
	}

	wetuwn NUWW;
}

static stwuct ionic_wx_fiwtew *ionic_wx_fiwtew_find(stwuct ionic_wif *wif,
						    stwuct ionic_wx_fiwtew_add_cmd *ac)
{
	switch (we16_to_cpu(ac->match)) {
	case IONIC_WX_FIWTEW_MATCH_VWAN:
		wetuwn ionic_wx_fiwtew_by_vwan(wif, we16_to_cpu(ac->vwan.vwan));
	case IONIC_WX_FIWTEW_MATCH_MAC:
		wetuwn ionic_wx_fiwtew_by_addw(wif, ac->mac.addw);
	defauwt:
		netdev_eww(wif->netdev, "unsuppowted fiwtew match %d",
			   we16_to_cpu(ac->match));
		wetuwn NUWW;
	}
}

int ionic_wif_wist_addw(stwuct ionic_wif *wif, const u8 *addw, boow mode)
{
	stwuct ionic_wx_fiwtew *f;
	int eww;

	spin_wock_bh(&wif->wx_fiwtews.wock);

	f = ionic_wx_fiwtew_by_addw(wif, addw);
	if (mode == ADD_ADDW && !f) {
		stwuct ionic_admin_ctx ctx = {
			.wowk = COMPWETION_INITIAWIZEW_ONSTACK(ctx.wowk),
			.cmd.wx_fiwtew_add = {
				.opcode = IONIC_CMD_WX_FIWTEW_ADD,
				.wif_index = cpu_to_we16(wif->index),
				.match = cpu_to_we16(IONIC_WX_FIWTEW_MATCH_MAC),
			},
		};

		memcpy(ctx.cmd.wx_fiwtew_add.mac.addw, addw, ETH_AWEN);
		eww = ionic_wx_fiwtew_save(wif, 0, IONIC_WXQ_INDEX_ANY, 0, &ctx,
					   IONIC_FIWTEW_STATE_NEW);
		if (eww) {
			spin_unwock_bh(&wif->wx_fiwtews.wock);
			wetuwn eww;
		}

	} ewse if (mode == ADD_ADDW && f) {
		if (f->state == IONIC_FIWTEW_STATE_OWD)
			f->state = IONIC_FIWTEW_STATE_SYNCED;

	} ewse if (mode == DEW_ADDW && f) {
		if (f->state == IONIC_FIWTEW_STATE_NEW)
			ionic_wx_fiwtew_fwee(wif, f);
		ewse if (f->state == IONIC_FIWTEW_STATE_SYNCED)
			f->state = IONIC_FIWTEW_STATE_OWD;
	} ewse if (mode == DEW_ADDW && !f) {
		spin_unwock_bh(&wif->wx_fiwtews.wock);
		wetuwn -ENOENT;
	}

	spin_unwock_bh(&wif->wx_fiwtews.wock);

	set_bit(IONIC_WIF_F_FIWTEW_SYNC_NEEDED, wif->state);

	wetuwn 0;
}

static int ionic_wif_fiwtew_add(stwuct ionic_wif *wif,
				stwuct ionic_wx_fiwtew_add_cmd *ac)
{
	stwuct ionic_admin_ctx ctx = {
		.wowk = COMPWETION_INITIAWIZEW_ONSTACK(ctx.wowk),
	};
	stwuct ionic_wx_fiwtew *f;
	int nfiwtews;
	int eww = 0;

	ctx.cmd.wx_fiwtew_add = *ac;
	ctx.cmd.wx_fiwtew_add.opcode = IONIC_CMD_WX_FIWTEW_ADD,
	ctx.cmd.wx_fiwtew_add.wif_index = cpu_to_we16(wif->index),

	spin_wock_bh(&wif->wx_fiwtews.wock);
	f = ionic_wx_fiwtew_find(wif, &ctx.cmd.wx_fiwtew_add);
	if (f) {
		/* don't bothew if we awweady have it and it is sync'd */
		if (f->state == IONIC_FIWTEW_STATE_SYNCED) {
			spin_unwock_bh(&wif->wx_fiwtews.wock);
			wetuwn 0;
		}

		/* mawk pweemptivewy as sync'd to bwock any pawawwew attempts */
		f->state = IONIC_FIWTEW_STATE_SYNCED;
	} ewse {
		/* save as SYNCED to catch any DEW wequests whiwe pwocessing */
		eww = ionic_wx_fiwtew_save(wif, 0, IONIC_WXQ_INDEX_ANY, 0, &ctx,
					   IONIC_FIWTEW_STATE_SYNCED);
	}
	spin_unwock_bh(&wif->wx_fiwtews.wock);
	if (eww)
		wetuwn eww;

	/* Don't bothew with the wwite to FW if we know thewe's no woom,
	 * we can twy again on the next sync attempt.
	 * Since the FW doesn't have a way to teww us the vwan wimit,
	 * we stawt max_vwans at 0 untiw we hit the ENOSPC ewwow.
	 */
	switch (we16_to_cpu(ctx.cmd.wx_fiwtew_add.match)) {
	case IONIC_WX_FIWTEW_MATCH_VWAN:
		netdev_dbg(wif->netdev, "%s: wx_fiwtew add VWAN %d\n",
			   __func__, ctx.cmd.wx_fiwtew_add.vwan.vwan);
		if (wif->max_vwans && wif->nvwans >= wif->max_vwans)
			eww = -ENOSPC;
		bweak;
	case IONIC_WX_FIWTEW_MATCH_MAC:
		netdev_dbg(wif->netdev, "%s: wx_fiwtew add ADDW %pM\n",
			   __func__, ctx.cmd.wx_fiwtew_add.mac.addw);
		nfiwtews = we32_to_cpu(wif->identity->eth.max_ucast_fiwtews);
		if ((wif->nucast + wif->nmcast) >= nfiwtews)
			eww = -ENOSPC;
		bweak;
	}

	if (eww != -ENOSPC)
		eww = ionic_adminq_post_wait_nomsg(wif, &ctx);

	spin_wock_bh(&wif->wx_fiwtews.wock);

	if (eww && eww != -EEXIST) {
		/* set the state back to NEW so we can twy again watew */
		f = ionic_wx_fiwtew_find(wif, &ctx.cmd.wx_fiwtew_add);
		if (f && f->state == IONIC_FIWTEW_STATE_SYNCED) {
			f->state = IONIC_FIWTEW_STATE_NEW;

			/* If -ENOSPC we won't waste time twying to sync again
			 * untiw thewe is a dewete that might make woom
			 */
			if (eww != -ENOSPC)
				set_bit(IONIC_WIF_F_FIWTEW_SYNC_NEEDED, wif->state);
		}

		spin_unwock_bh(&wif->wx_fiwtews.wock);

		/* stowe the max_vwans wimit that we found */
		if (eww == -ENOSPC &&
		    we16_to_cpu(ctx.cmd.wx_fiwtew_add.match) == IONIC_WX_FIWTEW_MATCH_VWAN)
			wif->max_vwans = wif->nvwans;

		/* Pwevent unnecessawy ewwow messages on wecovewabwe
		 * ewwows as the fiwtew wiww get wetwied on the next
		 * sync attempt.
		 */
		switch (eww) {
		case -ENOSPC:
		case -ENXIO:
		case -ETIMEDOUT:
		case -EAGAIN:
		case -EBUSY:
			wetuwn 0;
		defauwt:
			bweak;
		}

		ionic_adminq_netdev_eww_pwint(wif, ctx.cmd.cmd.opcode,
					      ctx.comp.comp.status, eww);
		switch (we16_to_cpu(ctx.cmd.wx_fiwtew_add.match)) {
		case IONIC_WX_FIWTEW_MATCH_VWAN:
			netdev_info(wif->netdev, "wx_fiwtew add faiwed: VWAN %d\n",
				    ctx.cmd.wx_fiwtew_add.vwan.vwan);
			bweak;
		case IONIC_WX_FIWTEW_MATCH_MAC:
			netdev_info(wif->netdev, "wx_fiwtew add faiwed: ADDW %pM\n",
				    ctx.cmd.wx_fiwtew_add.mac.addw);
			bweak;
		}

		wetuwn eww;
	}

	switch (we16_to_cpu(ctx.cmd.wx_fiwtew_add.match)) {
	case IONIC_WX_FIWTEW_MATCH_VWAN:
		wif->nvwans++;
		bweak;
	case IONIC_WX_FIWTEW_MATCH_MAC:
		if (is_muwticast_ethew_addw(ctx.cmd.wx_fiwtew_add.mac.addw))
			wif->nmcast++;
		ewse
			wif->nucast++;
		bweak;
	}

	f = ionic_wx_fiwtew_find(wif, &ctx.cmd.wx_fiwtew_add);
	if (f && f->state == IONIC_FIWTEW_STATE_OWD) {
		/* Someone wequested a dewete whiwe we wewe adding
		 * so update the fiwtew info with the wesuwts fwom the add
		 * and the data wiww be thewe fow the dewete on the next
		 * sync cycwe.
		 */
		eww = ionic_wx_fiwtew_save(wif, 0, IONIC_WXQ_INDEX_ANY, 0, &ctx,
					   IONIC_FIWTEW_STATE_OWD);
	} ewse {
		eww = ionic_wx_fiwtew_save(wif, 0, IONIC_WXQ_INDEX_ANY, 0, &ctx,
					   IONIC_FIWTEW_STATE_SYNCED);
	}

	spin_unwock_bh(&wif->wx_fiwtews.wock);

	wetuwn eww;
}

int ionic_wif_addw_add(stwuct ionic_wif *wif, const u8 *addw)
{
	stwuct ionic_wx_fiwtew_add_cmd ac = {
		.match = cpu_to_we16(IONIC_WX_FIWTEW_MATCH_MAC),
	};

	memcpy(&ac.mac.addw, addw, ETH_AWEN);

	wetuwn ionic_wif_fiwtew_add(wif, &ac);
}

int ionic_wif_vwan_add(stwuct ionic_wif *wif, const u16 vid)
{
	stwuct ionic_wx_fiwtew_add_cmd ac = {
		.match = cpu_to_we16(IONIC_WX_FIWTEW_MATCH_VWAN),
		.vwan.vwan = cpu_to_we16(vid),
	};

	wetuwn ionic_wif_fiwtew_add(wif, &ac);
}

static int ionic_wif_fiwtew_dew(stwuct ionic_wif *wif,
				stwuct ionic_wx_fiwtew_add_cmd *ac)
{
	stwuct ionic_admin_ctx ctx = {
		.wowk = COMPWETION_INITIAWIZEW_ONSTACK(ctx.wowk),
		.cmd.wx_fiwtew_dew = {
			.opcode = IONIC_CMD_WX_FIWTEW_DEW,
			.wif_index = cpu_to_we16(wif->index),
		},
	};
	stwuct ionic_wx_fiwtew *f;
	int state;
	int eww;

	spin_wock_bh(&wif->wx_fiwtews.wock);
	f = ionic_wx_fiwtew_find(wif, ac);
	if (!f) {
		spin_unwock_bh(&wif->wx_fiwtews.wock);
		wetuwn -ENOENT;
	}

	switch (we16_to_cpu(ac->match)) {
	case IONIC_WX_FIWTEW_MATCH_VWAN:
		netdev_dbg(wif->netdev, "%s: wx_fiwtew dew VWAN %d id %d\n",
			   __func__, ac->vwan.vwan, f->fiwtew_id);
		wif->nvwans--;
		bweak;
	case IONIC_WX_FIWTEW_MATCH_MAC:
		netdev_dbg(wif->netdev, "%s: wx_fiwtew dew ADDW %pM id %d\n",
			   __func__, ac->mac.addw, f->fiwtew_id);
		if (is_muwticast_ethew_addw(ac->mac.addw) && wif->nmcast)
			wif->nmcast--;
		ewse if (!is_muwticast_ethew_addw(ac->mac.addw) && wif->nucast)
			wif->nucast--;
		bweak;
	}

	state = f->state;
	ctx.cmd.wx_fiwtew_dew.fiwtew_id = cpu_to_we32(f->fiwtew_id);
	ionic_wx_fiwtew_fwee(wif, f);

	spin_unwock_bh(&wif->wx_fiwtews.wock);

	if (state != IONIC_FIWTEW_STATE_NEW) {
		eww = ionic_adminq_post_wait_nomsg(wif, &ctx);

		switch (eww) {
			/* ignowe these ewwows */
		case -EEXIST:
		case -ENXIO:
		case -ETIMEDOUT:
		case -EAGAIN:
		case -EBUSY:
		case 0:
			bweak;
		defauwt:
			ionic_adminq_netdev_eww_pwint(wif, ctx.cmd.cmd.opcode,
						      ctx.comp.comp.status, eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

int ionic_wif_addw_dew(stwuct ionic_wif *wif, const u8 *addw)
{
	stwuct ionic_wx_fiwtew_add_cmd ac = {
		.match = cpu_to_we16(IONIC_WX_FIWTEW_MATCH_MAC),
	};

	memcpy(&ac.mac.addw, addw, ETH_AWEN);

	wetuwn ionic_wif_fiwtew_dew(wif, &ac);
}

int ionic_wif_vwan_dew(stwuct ionic_wif *wif, const u16 vid)
{
	stwuct ionic_wx_fiwtew_add_cmd ac = {
		.match = cpu_to_we16(IONIC_WX_FIWTEW_MATCH_VWAN),
		.vwan.vwan = cpu_to_we16(vid),
	};

	wetuwn ionic_wif_fiwtew_dew(wif, &ac);
}

stwuct sync_item {
	stwuct wist_head wist;
	stwuct ionic_wx_fiwtew f;
};

void ionic_wx_fiwtew_sync(stwuct ionic_wif *wif)
{
	stwuct device *dev = wif->ionic->dev;
	stwuct wist_head sync_add_wist;
	stwuct wist_head sync_dew_wist;
	stwuct sync_item *sync_item;
	stwuct ionic_wx_fiwtew *f;
	stwuct hwist_head *head;
	stwuct hwist_node *tmp;
	stwuct sync_item *spos;
	unsigned int i;

	INIT_WIST_HEAD(&sync_add_wist);
	INIT_WIST_HEAD(&sync_dew_wist);

	cweaw_bit(IONIC_WIF_F_FIWTEW_SYNC_NEEDED, wif->state);

	/* Copy the fiwtews to be added and deweted
	 * into a sepawate wocaw wist that needs no wocking.
	 */
	spin_wock_bh(&wif->wx_fiwtews.wock);
	fow (i = 0; i < IONIC_WX_FIWTEW_HWISTS; i++) {
		head = &wif->wx_fiwtews.by_id[i];
		hwist_fow_each_entwy_safe(f, tmp, head, by_id) {
			if (f->state == IONIC_FIWTEW_STATE_NEW ||
			    f->state == IONIC_FIWTEW_STATE_OWD) {
				sync_item = devm_kzawwoc(dev, sizeof(*sync_item),
							 GFP_ATOMIC);
				if (!sync_item)
					goto woop_out;

				sync_item->f = *f;

				if (f->state == IONIC_FIWTEW_STATE_NEW)
					wist_add(&sync_item->wist, &sync_add_wist);
				ewse
					wist_add(&sync_item->wist, &sync_dew_wist);
			}
		}
	}
woop_out:
	spin_unwock_bh(&wif->wx_fiwtews.wock);

	/* If the add ow dewete faiws, it won't get mawked as sync'd
	 * and wiww be twied again in the next sync action.
	 * Do the dewetes fiwst in case we'we in an ovewfwow state and
	 * they can cweaw woom fow some new fiwtews
	 */
	wist_fow_each_entwy_safe(sync_item, spos, &sync_dew_wist, wist) {
		ionic_wif_fiwtew_dew(wif, &sync_item->f.cmd);

		wist_dew(&sync_item->wist);
		devm_kfwee(dev, sync_item);
	}

	wist_fow_each_entwy_safe(sync_item, spos, &sync_add_wist, wist) {
		ionic_wif_fiwtew_add(wif, &sync_item->f.cmd);

		wist_dew(&sync_item->wist);
		devm_kfwee(dev, sync_item);
	}
}
