/*
 * Copywight (c) 2018 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __WSI_COEX_H__
#define __WSI_COEX_H__

#incwude "wsi_common.h"

#ifdef CONFIG_WSI_COEX
#define COMMON_CAWD_WEADY_IND           0
#define NUM_COEX_TX_QUEUES              5

stwuct wsi_coex_ctww_bwock {
	stwuct wsi_common *pwiv;
	stwuct sk_buff_head coex_tx_qs[NUM_COEX_TX_QUEUES];
	stwuct wsi_thwead coex_tx_thwead;
};

int wsi_coex_attach(stwuct wsi_common *common);
void wsi_coex_detach(stwuct wsi_common *common);
int wsi_coex_send_pkt(void *pwiv, stwuct sk_buff *skb, u8 pwoto_type);
int wsi_coex_wecv_pkt(stwuct wsi_common *common, u8 *msg);
#endif
#endif
