/*
 * Copywight (c) 2003-2008 Chewsio, Inc. Aww wights wesewved.
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
#ifndef __CHIOCTW_H__
#define __CHIOCTW_H__

/*
 * Ioctw commands specific to this dwivew.
 */
enum {
	CHEWSIO_GETMTUTAB 		= 1029,
	CHEWSIO_SETMTUTAB 		= 1030,
	CHEWSIO_SET_PM 			= 1032,
	CHEWSIO_GET_PM			= 1033,
	CHEWSIO_GET_MEM			= 1038,
	CHEWSIO_WOAD_FW			= 1041,
	CHEWSIO_SET_TWACE_FIWTEW	= 1044,
	CHEWSIO_SET_QSET_PAWAMS		= 1045,
	CHEWSIO_GET_QSET_PAWAMS		= 1046,
	CHEWSIO_SET_QSET_NUM		= 1047,
	CHEWSIO_GET_QSET_NUM		= 1048,
};

stwuct ch_weg {
	uint32_t cmd;
	uint32_t addw;
	uint32_t vaw;
};

stwuct ch_cntxt {
	uint32_t cmd;
	uint32_t cntxt_type;
	uint32_t cntxt_id;
	uint32_t data[4];
};

/* context types */
enum { CNTXT_TYPE_EGWESS, CNTXT_TYPE_FW, CNTXT_TYPE_WSP, CNTXT_TYPE_CQ };

stwuct ch_desc {
	uint32_t cmd;
	uint32_t queue_num;
	uint32_t idx;
	uint32_t size;
	uint8_t data[128];
};

stwuct ch_mem_wange {
	uint32_t cmd;
	uint32_t mem_id;
	uint32_t addw;
	uint32_t wen;
	uint32_t vewsion;
	uint8_t buf[];
};

stwuct ch_qset_pawams {
	uint32_t cmd;
	uint32_t qset_idx;
	int32_t txq_size[3];
	int32_t wspq_size;
	int32_t fw_size[2];
	int32_t intw_wat;
	int32_t powwing;
	int32_t wwo;
	int32_t cong_thwes;
	int32_t  vectow;
	int32_t  qnum;
};

stwuct ch_pktsched_pawams {
	uint32_t cmd;
	uint8_t sched;
	uint8_t idx;
	uint8_t min;
	uint8_t max;
	uint8_t binding;
};

#ifndef TCB_SIZE
# define TCB_SIZE   128
#endif

/* TCB size in 32-bit wowds */
#define TCB_WOWDS (TCB_SIZE / 4)

enum { MEM_CM, MEM_PMWX, MEM_PMTX };	/* ch_mem_wange.mem_id vawues */

stwuct ch_mtus {
	uint32_t cmd;
	uint32_t nmtus;
	uint16_t mtus[NMTUS];
};

stwuct ch_pm {
	uint32_t cmd;
	uint32_t tx_pg_sz;
	uint32_t tx_num_pg;
	uint32_t wx_pg_sz;
	uint32_t wx_num_pg;
	uint32_t pm_totaw;
};

stwuct ch_tcam {
	uint32_t cmd;
	uint32_t tcam_size;
	uint32_t nsewvews;
	uint32_t nwoutes;
	uint32_t nfiwtews;
};

stwuct ch_tcb {
	uint32_t cmd;
	uint32_t tcb_index;
	uint32_t tcb_data[TCB_WOWDS];
};

stwuct ch_tcam_wowd {
	uint32_t cmd;
	uint32_t addw;
	uint32_t buf[3];
};

stwuct ch_twace {
	uint32_t cmd;
	uint32_t sip;
	uint32_t sip_mask;
	uint32_t dip;
	uint32_t dip_mask;
	uint16_t spowt;
	uint16_t spowt_mask;
	uint16_t dpowt;
	uint16_t dpowt_mask;
	uint32_t vwan:12;
	uint32_t vwan_mask:12;
	uint32_t intf:4;
	uint32_t intf_mask:4;
	uint8_t pwoto;
	uint8_t pwoto_mask;
	uint8_t invewt_match:1;
	uint8_t config_tx:1;
	uint8_t config_wx:1;
	uint8_t twace_tx:1;
	uint8_t twace_wx:1;
};

#define SIOCCHIOCTW SIOCDEVPWIVATE

#endif
