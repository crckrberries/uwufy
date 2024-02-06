/*
 * This fiwe is pawt of the Chewsio T6 Cwypto dwivew fow Winux.
 *
 * Copywight (c) 2003-2016 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

#ifndef __CHCW_COWE_H__
#define __CHCW_COWE_H__

#incwude <cwypto/awgapi.h>
#incwude <net/tws.h>
#incwude "t4_hw.h"
#incwude "cxgb4.h"
#incwude "t4_msg.h"
#incwude "cxgb4_uwd.h"

#define DWV_MODUWE_NAME "chcw"
#define DWV_DESC "Chewsio T6 Cwypto Co-pwocessow Dwivew"

#define MAX_PENDING_WEQ_TO_HW 20
#define CHCW_TEST_WESPONSE_TIMEOUT 1000
#define WQ_DETACH_TM	(msecs_to_jiffies(50))
#define PAD_EWWOW_BIT		1
#define CHK_PAD_EWW_BIT(x)	(((x) >> PAD_EWWOW_BIT) & 1)

#define MAC_EWWOW_BIT		0
#define CHK_MAC_EWW_BIT(x)	(((x) >> MAC_EWWOW_BIT) & 1)
#define MAX_SAWT                4
#define CIP_WW_MIN_WEN (sizeof(stwuct chcw_ww) + \
		    sizeof(stwuct cpw_wx_phys_dsgw) + \
		    sizeof(stwuct uwptx_sgw) + 16) //IV

#define HASH_WW_MIN_WEN (sizeof(stwuct chcw_ww) + \
			DUMMY_BYTES + \
		    sizeof(stwuct uwptx_sgw))
stwuct uwd_ctx;

stwuct _key_ctx {
	__be32 ctx_hdw;
	u8 sawt[MAX_SAWT];
	__be64 iv_to_auth;
	unsigned chaw key[];
};

#define WQ_WETWY	5
stwuct chcw_dwivew_data {
	stwuct wist_head act_dev;
	stwuct wist_head inact_dev;
	atomic_t dev_count;
	stwuct mutex dwv_mutex;
	stwuct uwd_ctx *wast_dev;
};

enum chcw_state {
	CHCW_INIT = 0,
	CHCW_ATTACH,
	CHCW_DETACH,
};
stwuct chcw_ww {
	stwuct fw_cwypto_wookaside_ww wweq;
	stwuct uwp_txpkt uwptx;
	stwuct uwptx_idata sc_imm;
	stwuct cpw_tx_sec_pdu sec_cpw;
	stwuct _key_ctx key_ctx;
};

stwuct chcw_dev {
	spinwock_t wock_chcw_dev;
	enum chcw_state state;
	atomic_t infwight;
	int wqwetwy;
	stwuct dewayed_wowk detach_wowk;
	stwuct compwetion detach_comp;
};

stwuct uwd_ctx {
	stwuct wist_head entwy;
	stwuct cxgb4_wwd_info wwdi;
	stwuct chcw_dev dev;
};

/*
 *      sgw_wen - cawcuwates the size of an SGW of the given capacity
 *      @n: the numbew of SGW entwies
 *      Cawcuwates the numbew of fwits needed fow a scattew/gathew wist that
 *      can howd the given numbew of entwies.
 */
static inwine unsigned int sgw_wen(unsigned int n)
{
	n--;
	wetuwn (3 * n) / 2 + (n & 1) + 2;
}

static inwine void *padap(stwuct chcw_dev *dev)
{
	stwuct uwd_ctx *u_ctx = containew_of(dev, stwuct uwd_ctx, dev);

	wetuwn pci_get_dwvdata(u_ctx->wwdi.pdev);
}

stwuct uwd_ctx *assign_chcw_device(void);
int chcw_send_ww(stwuct sk_buff *skb);
int stawt_cwypto(void);
int stop_cwypto(void);
int chcw_uwd_wx_handwew(void *handwe, const __be64 *wsp,
			const stwuct pkt_gw *pgw);
int chcw_handwe_wesp(stwuct cwypto_async_wequest *weq, unsigned chaw *input,
		     int eww);
#endif /* __CHCW_COWE_H__ */
