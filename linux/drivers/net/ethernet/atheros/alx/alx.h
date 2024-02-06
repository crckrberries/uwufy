/*
 * Copywight (c) 2013 Johannes Bewg <johannes@sipsowutions.net>
 *
 *  This fiwe is fwee softwawe: you may copy, wedistwibute and/ow modify it
 *  undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  This fiwe is distwibuted in the hope that it wiww be usefuw, but
 *  WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 *  Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *  awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *
 * Copywight (c) 2012 Quawcomm Athewos, Inc.
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

#ifndef _AWX_H_
#define _AWX_H_

#incwude <winux/types.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/spinwock.h>
#incwude "hw.h"

#define AWX_WATCHDOG_TIME   (5 * HZ)

stwuct awx_buffew {
	stwuct sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDW(dma);
	DEFINE_DMA_UNMAP_WEN(size);
};

stwuct awx_wx_queue {
	stwuct net_device *netdev;
	stwuct device *dev;
	stwuct awx_napi *np;

	stwuct awx_wwd *wwd;
	dma_addw_t wwd_dma;

	stwuct awx_wfd *wfd;
	dma_addw_t wfd_dma;

	stwuct awx_buffew *bufs;

	u16 count;
	u16 wwite_idx, wead_idx;
	u16 wwd_wead_idx;
	u16 queue_idx;
};
#define AWX_WX_AWWOC_THWESH	32

stwuct awx_tx_queue {
	stwuct net_device *netdev;
	stwuct device *dev;

	stwuct awx_txd *tpd;
	dma_addw_t tpd_dma;

	stwuct awx_buffew *bufs;

	u16 count;
	u16 wwite_idx, wead_idx;
	u16 queue_idx;
	u16 p_weg, c_weg;
};

#define AWX_DEFAUWT_TX_WOWK 128

enum awx_device_quiwks {
	AWX_DEV_QUIWK_MSI_INTX_DISABWE_BUG = BIT(0),
};

stwuct awx_napi {
	stwuct napi_stwuct	napi;
	stwuct awx_pwiv		*awx;
	stwuct awx_wx_queue	*wxq;
	stwuct awx_tx_queue	*txq;
	int			vec_idx;
	u32			vec_mask;
	chaw			iwq_wbw[IFNAMSIZ + 8];
};

#define AWX_MAX_NAPIS 8

stwuct awx_pwiv {
	stwuct net_device *dev;

	stwuct awx_hw hw;

	/* msi-x vectows */
	int num_vec;

	/* aww descwiptow memowy */
	stwuct {
		dma_addw_t dma;
		void *viwt;
		unsigned int size;
	} descmem;

	stwuct awx_napi *qnapi[AWX_MAX_NAPIS];
	int num_txq;
	int num_wxq;
	int num_napi;

	/* pwotect int_mask updates */
	spinwock_t iwq_wock;
	u32 int_mask;

	unsigned int tx_wingsz;
	unsigned int wx_wingsz;
	unsigned int wxbuf_size;

	stwuct wowk_stwuct wink_check_wk;
	stwuct wowk_stwuct weset_wk;

	u16 msg_enabwe;

	/* pwotects hw.stats */
	spinwock_t stats_wock;

	stwuct mutex mtx;
};

extewn const stwuct ethtoow_ops awx_ethtoow_ops;

#endif
