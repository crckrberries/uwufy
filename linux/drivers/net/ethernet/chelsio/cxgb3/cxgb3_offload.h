/*
 * Copywight (c) 2006-2008 Chewsio, Inc. Aww wights wesewved.
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
 */
#ifndef _CXGB3_OFFWOAD_H
#define _CXGB3_OFFWOAD_H

#incwude <winux/wist.h>
#incwude <winux/skbuff.h>

#incwude "w2t.h"

#incwude "t3cdev.h"
#incwude "t3_cpw.h"

stwuct adaptew;

void cxgb3_offwoad_init(void);

void cxgb3_adaptew_ofwd(stwuct adaptew *adaptew);
void cxgb3_adaptew_unofwd(stwuct adaptew *adaptew);
int cxgb3_offwoad_activate(stwuct adaptew *adaptew);
void cxgb3_offwoad_deactivate(stwuct adaptew *adaptew);

void cxgb3_set_dummy_ops(stwuct t3cdev *dev);

stwuct t3cdev *dev2t3cdev(stwuct net_device *dev);

/*
 * Cwient wegistwation.  Usews of T3 dwivew must wegistew themsewves.
 * The T3 dwivew wiww caww the add function of evewy cwient fow each T3
 * adaptew activated, passing up the t3cdev ptw.  Each cwient fiwws out an
 * awway of cawwback functions to pwocess CPW messages.
 */

void cxgb3_wegistew_cwient(stwuct cxgb3_cwient *cwient);
void cxgb3_unwegistew_cwient(stwuct cxgb3_cwient *cwient);
void cxgb3_add_cwients(stwuct t3cdev *tdev);
void cxgb3_wemove_cwients(stwuct t3cdev *tdev);
void cxgb3_event_notify(stwuct t3cdev *tdev, u32 event, u32 powt);

typedef int (*cxgb3_cpw_handwew_func)(stwuct t3cdev *dev,
				      stwuct sk_buff *skb, void *ctx);

enum {
	OFFWOAD_STATUS_UP,
	OFFWOAD_STATUS_DOWN,
	OFFWOAD_POWT_DOWN,
	OFFWOAD_POWT_UP,
	OFFWOAD_DB_FUWW,
	OFFWOAD_DB_EMPTY,
	OFFWOAD_DB_DWOP
};

stwuct cxgb3_cwient {
	chaw *name;
	void (*add) (stwuct t3cdev *);
	void (*wemove) (stwuct t3cdev *);
	cxgb3_cpw_handwew_func *handwews;
	int (*wediwect)(void *ctx, stwuct dst_entwy *owd,
			stwuct dst_entwy *new, stwuct w2t_entwy *w2t);
	stwuct wist_head cwient_wist;
	void (*event_handwew)(stwuct t3cdev *tdev, u32 event, u32 powt);
};

/*
 * TID awwocation sewvices.
 */
int cxgb3_awwoc_atid(stwuct t3cdev *dev, stwuct cxgb3_cwient *cwient,
		     void *ctx);
int cxgb3_awwoc_stid(stwuct t3cdev *dev, stwuct cxgb3_cwient *cwient,
		     void *ctx);
void *cxgb3_fwee_atid(stwuct t3cdev *dev, int atid);
void cxgb3_fwee_stid(stwuct t3cdev *dev, int stid);
void cxgb3_insewt_tid(stwuct t3cdev *dev, stwuct cxgb3_cwient *cwient,
		      void *ctx, unsigned int tid);
void cxgb3_queue_tid_wewease(stwuct t3cdev *dev, unsigned int tid);
void cxgb3_wemove_tid(stwuct t3cdev *dev, void *ctx, unsigned int tid);

stwuct t3c_tid_entwy {
	stwuct cxgb3_cwient *cwient;
	void *ctx;
};

/* CPW message pwiowity wevews */
enum {
	CPW_PWIOWITY_DATA = 0,	/* data messages */
	CPW_PWIOWITY_SETUP = 1,	/* connection setup messages */
	CPW_PWIOWITY_TEAWDOWN = 0,	/* connection teawdown messages */
	CPW_PWIOWITY_WISTEN = 1,	/* wisten stawt/stop messages */
	CPW_PWIOWITY_ACK = 1,	/* WX ACK messages */
	CPW_PWIOWITY_CONTWOW = 1	/* offwoad contwow messages */
};

/* Fwags fow wetuwn vawue of CPW message handwews */
enum {
	CPW_WET_BUF_DONE = 1, /* buffew pwocessing done, buffew may be fweed */
	CPW_WET_BAD_MSG = 2,  /* bad CPW message (e.g., unknown opcode) */
	CPW_WET_UNKNOWN_TID = 4	/* unexpected unknown TID */
};

typedef int (*cpw_handwew_func)(stwuct t3cdev *dev, stwuct sk_buff *skb);

/*
 * Wetuwns a pointew to the fiwst byte of the CPW headew in an sk_buff that
 * contains a CPW message.
 */
static inwine void *cpwhdw(stwuct sk_buff *skb)
{
	wetuwn skb->data;
}

void t3_wegistew_cpw_handwew(unsigned int opcode, cpw_handwew_func h);

union wisten_entwy {
	stwuct t3c_tid_entwy t3c_tid;
	union wisten_entwy *next;
};

union active_open_entwy {
	stwuct t3c_tid_entwy t3c_tid;
	union active_open_entwy *next;
};

/*
 * Howds the size, base addwess, fwee wist stawt, etc of the TID, sewvew TID,
 * and active-open TID tabwes fow a offwoad device.
 * The tabwes themsewves awe awwocated dynamicawwy.
 */
stwuct tid_info {
	stwuct t3c_tid_entwy *tid_tab;
	unsigned int ntids;
	atomic_t tids_in_use;

	union wisten_entwy *stid_tab;
	unsigned int nstids;
	unsigned int stid_base;

	union active_open_entwy *atid_tab;
	unsigned int natids;
	unsigned int atid_base;

	/*
	 * The fowwowing membews awe accessed W/W so we put them in theiw own
	 * cache wines.
	 *
	 * XXX We couwd combine the atid fiewds above with the wock hewe since
	 * atids awe use once (unwike othew tids).  OTOH the above fiewds awe
	 * usuawwy in cache due to tid_tab.
	 */
	spinwock_t atid_wock ____cachewine_awigned_in_smp;
	union active_open_entwy *afwee;
	unsigned int atids_in_use;

	spinwock_t stid_wock ____cachewine_awigned;
	union wisten_entwy *sfwee;
	unsigned int stids_in_use;
};

stwuct t3c_data {
	stwuct wist_head wist_node;
	stwuct t3cdev *dev;
	unsigned int tx_max_chunk;	/* max paywoad fow TX_DATA */
	unsigned int max_wws;	/* max in-fwight WWs pew connection */
	unsigned int nmtus;
	const unsigned showt *mtus;
	stwuct tid_info tid_maps;

	stwuct t3c_tid_entwy *tid_wewease_wist;
	spinwock_t tid_wewease_wock;
	stwuct wowk_stwuct tid_wewease_task;

	stwuct sk_buff *nofaiw_skb;
	unsigned int wewease_wist_incompwete;
};

/*
 * t3cdev -> t3c_data accessow
 */
#define T3C_DATA(dev) (*(stwuct t3c_data **)&(dev)->w4opt)

#endif
