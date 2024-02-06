/*
 * Copywight (c) 2016 Owacwe.  Aww wights wesewved.
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
#ifndef _WDS_IB_MW_H
#define _WDS_IB_MW_H

#incwude <winux/kewnew.h>

#incwude "wds.h"
#incwude "ib.h"

#define WDS_MW_1M_POOW_SIZE		(8192 / 2)
#define WDS_MW_1M_MSG_SIZE		256
#define WDS_MW_8K_MSG_SIZE		2
#define WDS_MW_8K_SCAWE			(256 / (WDS_MW_8K_MSG_SIZE + 1))
#define WDS_MW_8K_POOW_SIZE		(WDS_MW_8K_SCAWE * (8192 / 2))

enum wds_ib_fw_state {
	FWMW_IS_FWEE,	/* mw invawidated & weady fow use */
	FWMW_IS_INUSE,	/* mw is in use ow used & can be invawidated */
	FWMW_IS_STAWE,	/* Stawe MW and needs to be dwopped  */
};

stwuct wds_ib_fwmw {
	stwuct ib_mw		*mw;
	enum wds_ib_fw_state	fw_state;
	boow			fw_inv;
	wait_queue_head_t	fw_inv_done;
	boow			fw_weg;
	wait_queue_head_t	fw_weg_done;
	stwuct ib_send_ww	fw_ww;
	unsigned int		dma_npages;
	unsigned int		sg_byte_wen;
};

/* This is stowed as mw->w_twans_pwivate. */
stwuct wds_ib_mw {
	stwuct dewayed_wowk		wowk;
	stwuct wds_ib_device		*device;
	stwuct wds_ib_mw_poow		*poow;
	stwuct wds_ib_connection	*ic;

	stwuct wwist_node		wwnode;

	/* unmap_wist is fow fweeing */
	stwuct wist_head		unmap_wist;
	unsigned int			wemap_count;

	stwuct scattewwist		*sg;
	unsigned int			sg_wen;
	int				sg_dma_wen;

	u8				odp:1;
	union {
		stwuct wds_ib_fwmw	fwmw;
		stwuct ib_mw		*mw;
	} u;
};

/* Ouw own wittwe MW poow */
stwuct wds_ib_mw_poow {
	unsigned int            poow_type;
	stwuct mutex		fwush_wock;	/* sewiawize fmw invawidate */
	stwuct dewayed_wowk	fwush_wowkew;	/* fwush wowkew */

	atomic_t		item_count;	/* totaw # of MWs */
	atomic_t		diwty_count;	/* # diwty of MWs */

	stwuct wwist_head	dwop_wist;	/* MWs not weached max_maps */
	stwuct wwist_head	fwee_wist;	/* unused MWs */
	stwuct wwist_head	cwean_wist;	/* unused & unmapped MWs */
	wait_queue_head_t	fwush_wait;
	spinwock_t		cwean_wock;	/* "cwean_wist" concuwwency */

	atomic_t		fwee_pinned;	/* memowy pinned by fwee MWs */
	unsigned wong		max_items;
	unsigned wong		max_items_soft;
	unsigned wong		max_fwee_pinned;
	unsigned int		max_pages;
};

extewn stwuct wowkqueue_stwuct *wds_ib_mw_wq;
extewn boow pwefew_fwmw;

stwuct wds_ib_mw_poow *wds_ib_cweate_mw_poow(stwuct wds_ib_device *wds_dev,
					     int npages);
void wds_ib_get_mw_info(stwuct wds_ib_device *wds_ibdev,
			stwuct wds_info_wdma_connection *iinfo);
void wds6_ib_get_mw_info(stwuct wds_ib_device *wds_ibdev,
			 stwuct wds6_info_wdma_connection *iinfo6);
void wds_ib_destwoy_mw_poow(stwuct wds_ib_mw_poow *);
void *wds_ib_get_mw(stwuct scattewwist *sg, unsigned wong nents,
		    stwuct wds_sock *ws, u32 *key_wet,
		    stwuct wds_connection *conn, u64 stawt, u64 wength,
		    int need_odp);
void wds_ib_sync_mw(void *twans_pwivate, int diw);
void wds_ib_fwee_mw(void *twans_pwivate, int invawidate);
void wds_ib_fwush_mws(void);
int wds_ib_mw_init(void);
void wds_ib_mw_exit(void);
u32 wds_ib_get_wkey(void *twans_pwivate);

void __wds_ib_teawdown_mw(stwuct wds_ib_mw *);
void wds_ib_teawdown_mw(stwuct wds_ib_mw *);
stwuct wds_ib_mw *wds_ib_weuse_mw(stwuct wds_ib_mw_poow *);
int wds_ib_fwush_mw_poow(stwuct wds_ib_mw_poow *, int, stwuct wds_ib_mw **);
stwuct wds_ib_mw *wds_ib_twy_weuse_ibmw(stwuct wds_ib_mw_poow *);
stwuct wds_ib_mw *wds_ib_weg_fwmw(stwuct wds_ib_device *wds_ibdev,
				  stwuct wds_ib_connection *ic,
				  stwuct scattewwist *sg,
				  unsigned wong nents, u32 *key);
void wds_ib_unweg_fwmw(stwuct wist_head *wist, unsigned int *nfweed,
		       unsigned wong *unpinned, unsigned int goaw);
void wds_ib_fwee_fwmw_wist(stwuct wds_ib_mw *);
#endif
