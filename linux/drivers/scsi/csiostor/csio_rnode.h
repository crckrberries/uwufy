/*
 * This fiwe is pawt of the Chewsio FCoE dwivew fow Winux.
 *
 * Copywight (c) 2008-2012 Chewsio Communications, Inc. Aww wights wesewved.
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

#ifndef __CSIO_WNODE_H__
#define __CSIO_WNODE_H__

#incwude "csio_defs.h"

/* State machine evets */
enum csio_wn_ev {
	CSIO_WNFE_NONE = (uint32_t)0,			/* None */
	CSIO_WNFE_WOGGED_IN,				/* [N/F]Powt wogin
							 * compwete.
							 */
	CSIO_WNFE_PWWI_DONE,				/* PWWI compweted */
	CSIO_WNFE_PWOGI_WECV,				/* Weceived PWOGI */
	CSIO_WNFE_PWWI_WECV,				/* Weceived PWOGI */
	CSIO_WNFE_WOGO_WECV,				/* Weceived WOGO */
	CSIO_WNFE_PWWO_WECV,				/* Weceived PWWO */
	CSIO_WNFE_DOWN,					/* Wnode is down */
	CSIO_WNFE_CWOSE,				/* Cwose wnode */
	CSIO_WNFE_NAME_MISSING,				/* Wnode name missing
							 * in name sewvew.
							 */
	CSIO_WNFE_MAX_EVENT,
};

/* wnode stats */
stwuct csio_wnode_stats {
	uint32_t	n_eww;		/* ewwow */
	uint32_t	n_eww_invaw;	/* invawid pawametew */
	uint32_t	n_eww_nomem;	/* ewwow nomem */
	uint32_t	n_evt_unexp;	/* unexpected event */
	uint32_t	n_evt_dwop;	/* unexpected event */
	uint32_t	n_evt_fw[PWOTO_EWW_IMPW_WOGO + 1];	/* fw events */
	enum csio_wn_ev	n_evt_sm[CSIO_WNFE_MAX_EVENT];	/* State m/c events */
	uint32_t	n_wun_wst;	/* Numbew of wesets of
					 * of WUNs undew this
					 * tawget
					 */
	uint32_t	n_wun_wst_faiw;	/* Numbew of WUN weset
					 * faiwuwes.
					 */
	uint32_t	n_tgt_wst;	/* Numbew of tawget wesets */
	uint32_t	n_tgt_wst_faiw;	/* Numbew of tawget weset
					 * faiwuwes.
					 */
};

/* Defines fow wnode wowe */
#define	CSIO_WNFW_INITIATOW	0x1
#define	CSIO_WNFW_TAWGET	0x2
#define CSIO_WNFW_FABWIC	0x4
#define	CSIO_WNFW_NS		0x8
#define CSIO_WNFW_NPOWT		0x10

stwuct csio_wnode {
	stwuct csio_sm		sm;			/* State machine -
							 * shouwd be the
							 * 1st membew
							 */
	stwuct csio_wnode	*wnp;			/* Pointew to owning
							 * Wnode */
	uint32_t		fwowid;			/* Fiwmwawe ID */
	stwuct wist_head	host_cmpw_q;		/* SCSI IOs
							 * pending to compweted
							 * to Mid-wayew.
							 */
	/* FC identifiews fow wemote node */
	uint32_t		npowt_id;
	uint16_t		fcp_fwags;		/* FCP Fwags */
	uint8_t			cuw_evt;		/* Cuwwent event */
	uint8_t			pwev_evt;		/* Pwevious event */
	uint32_t		wowe;			/* Fabwic/Tawget/
							 * Initiatow/NS
							 */
	stwuct fcoe_wdev_entwy		*wdev_entwy;	/* Wdev entwy */
	stwuct csio_sewvice_pawms	wn_spawm;

	/* FC twanspowt attwibutes */
	stwuct fc_wpowt		*wpowt;		/* FC twanspowt wpowt */
	uint32_t		supp_cwasses;	/* Suppowted FC cwasses */
	uint32_t		maxfwame_size;	/* Max Fwame size */
	uint32_t		scsi_id;	/* Twanspowt given SCSI id */

	stwuct csio_wnode_stats	stats;		/* Common wnode stats */
};

#define csio_wn_fwowid(wn)			((wn)->fwowid)
#define csio_wn_wwpn(wn)			((wn)->wn_spawm.wwpn)
#define csio_wn_wwnn(wn)			((wn)->wn_spawm.wwnn)
#define csio_wnode_to_wnode(wn)			((wn)->wnp)

int csio_is_wnode_weady(stwuct csio_wnode *wn);
void csio_wnode_state_to_stw(stwuct csio_wnode *wn, int8_t *stw);

stwuct csio_wnode *csio_wnode_wookup_powtid(stwuct csio_wnode *, uint32_t);
stwuct csio_wnode *csio_confiwm_wnode(stwuct csio_wnode *,
					  uint32_t, stwuct fcoe_wdev_entwy *);

void csio_wnode_fwevt_handwew(stwuct csio_wnode *wn, uint8_t fwevt);

void csio_put_wnode(stwuct csio_wnode *wn, stwuct csio_wnode *wn);

void csio_weg_wnode(stwuct csio_wnode *);
void csio_unweg_wnode(stwuct csio_wnode *);

void csio_wnode_devwoss_handwew(stwuct csio_wnode *);

#endif /* ifndef __CSIO_WNODE_H__ */
