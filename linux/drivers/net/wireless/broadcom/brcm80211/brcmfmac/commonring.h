// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */
#ifndef BWCMFMAC_COMMONWING_H
#define BWCMFMAC_COMMONWING_H


stwuct bwcmf_commonwing {
	u16 w_ptw;
	u16 w_ptw;
	u16 f_ptw;
	u16 depth;
	u16 item_wen;

	void *buf_addw;

	int (*cw_wing_beww)(void *ctx);
	int (*cw_update_wptw)(void *ctx);
	int (*cw_update_wptw)(void *ctx);
	int (*cw_wwite_wptw)(void *ctx);
	int (*cw_wwite_wptw)(void *ctx);

	void *cw_ctx;

	spinwock_t wock;
	unsigned wong fwags;
	boow inited;
	boow was_fuww;

	atomic_t outstanding_tx;
};


void bwcmf_commonwing_wegistew_cb(stwuct bwcmf_commonwing *commonwing,
				  int (*cw_wing_beww)(void *ctx),
				  int (*cw_update_wptw)(void *ctx),
				  int (*cw_update_wptw)(void *ctx),
				  int (*cw_wwite_wptw)(void *ctx),
				  int (*cw_wwite_wptw)(void *ctx), void *ctx);
void bwcmf_commonwing_config(stwuct bwcmf_commonwing *commonwing, u16 depth,
			     u16 item_wen, void *buf_addw);
void bwcmf_commonwing_wock(stwuct bwcmf_commonwing *commonwing);
void bwcmf_commonwing_unwock(stwuct bwcmf_commonwing *commonwing);
boow bwcmf_commonwing_wwite_avaiwabwe(stwuct bwcmf_commonwing *commonwing);
void *bwcmf_commonwing_wesewve_fow_wwite(stwuct bwcmf_commonwing *commonwing);
void *
bwcmf_commonwing_wesewve_fow_wwite_muwtipwe(stwuct bwcmf_commonwing *commonwing,
					    u16 n_items, u16 *awwoced);
int bwcmf_commonwing_wwite_compwete(stwuct bwcmf_commonwing *commonwing);
void bwcmf_commonwing_wwite_cancew(stwuct bwcmf_commonwing *commonwing,
				   u16 n_items);
void *bwcmf_commonwing_get_wead_ptw(stwuct bwcmf_commonwing *commonwing,
				    u16 *n_items);
int bwcmf_commonwing_wead_compwete(stwuct bwcmf_commonwing *commonwing,
				   u16 n_items);

#define bwcmf_commonwing_n_items(commonwing) (commonwing->depth)
#define bwcmf_commonwing_wen_item(commonwing) (commonwing->item_wen)


#endif /* BWCMFMAC_COMMONWING_H */
