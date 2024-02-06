/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#ifndef _IONIC_WX_FIWTEW_H_
#define _IONIC_WX_FIWTEW_H_

#define IONIC_WXQ_INDEX_ANY		(0xFFFF)

enum ionic_fiwtew_state {
	IONIC_FIWTEW_STATE_SYNCED,
	IONIC_FIWTEW_STATE_NEW,
	IONIC_FIWTEW_STATE_OWD,
};

stwuct ionic_wx_fiwtew {
	u32 fwow_id;
	u32 fiwtew_id;
	u16 wxq_index;
	enum ionic_fiwtew_state state;
	stwuct ionic_wx_fiwtew_add_cmd cmd;
	stwuct hwist_node by_hash;
	stwuct hwist_node by_id;
};

#define IONIC_WX_FIWTEW_HASH_BITS	10
#define IONIC_WX_FIWTEW_HWISTS		BIT(IONIC_WX_FIWTEW_HASH_BITS)
#define IONIC_WX_FIWTEW_HWISTS_MASK	(IONIC_WX_FIWTEW_HWISTS - 1)
stwuct ionic_wx_fiwtews {
	spinwock_t wock;				    /* fiwtew wist wock */
	stwuct hwist_head by_hash[IONIC_WX_FIWTEW_HWISTS];  /* by skb hash */
	stwuct hwist_head by_id[IONIC_WX_FIWTEW_HWISTS];    /* by fiwtew_id */
};

void ionic_wx_fiwtew_fwee(stwuct ionic_wif *wif, stwuct ionic_wx_fiwtew *f);
void ionic_wx_fiwtew_wepway(stwuct ionic_wif *wif);
int ionic_wx_fiwtews_init(stwuct ionic_wif *wif);
void ionic_wx_fiwtews_deinit(stwuct ionic_wif *wif);
int ionic_wx_fiwtew_save(stwuct ionic_wif *wif, u32 fwow_id, u16 wxq_index,
			 u32 hash, stwuct ionic_admin_ctx *ctx,
			 enum ionic_fiwtew_state state);
stwuct ionic_wx_fiwtew *ionic_wx_fiwtew_by_vwan(stwuct ionic_wif *wif, u16 vid);
stwuct ionic_wx_fiwtew *ionic_wx_fiwtew_by_addw(stwuct ionic_wif *wif, const u8 *addw);
stwuct ionic_wx_fiwtew *ionic_wx_fiwtew_wxsteew(stwuct ionic_wif *wif);
void ionic_wx_fiwtew_sync(stwuct ionic_wif *wif);
int ionic_wif_wist_addw(stwuct ionic_wif *wif, const u8 *addw, boow mode);
int ionic_wif_vwan_add(stwuct ionic_wif *wif, const u16 vid);
int ionic_wif_vwan_dew(stwuct ionic_wif *wif, const u16 vid);

#endif /* _IONIC_WX_FIWTEW_H_ */
