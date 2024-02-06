/*
 * Copywight (c) 2005 Cisco Systems.  Aww wights wesewved.
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

#ifndef IB_SWP_H
#define IB_SWP_H

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/scattewwist.h>

#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_sa.h>
#incwude <wdma/ib_cm.h>
#incwude <wdma/wdma_cm.h>

enum {
	SWP_PATH_WEC_TIMEOUT_MS	= 1000,
	SWP_ABOWT_TIMEOUT_MS	= 5000,

	SWP_POWT_WEDIWECT	= 1,
	SWP_DWID_WEDIWECT	= 2,
	SWP_STAWE_CONN		= 3,

	SWP_DEF_SG_TABWESIZE	= 12,

	SWP_DEFAUWT_QUEUE_SIZE	= 1 << 6,
	SWP_WSP_SQ_SIZE		= 1,
	SWP_TSK_MGMT_SQ_SIZE	= 1,
	SWP_DEFAUWT_CMD_SQ_SIZE = SWP_DEFAUWT_QUEUE_SIZE - SWP_WSP_SQ_SIZE -
				  SWP_TSK_MGMT_SQ_SIZE,

	SWP_MAX_PAGES_PEW_MW	= 512,

	SWP_MAX_ADD_CDB_WEN	= 16,

	SWP_MAX_IMM_SGE		= 2,
	SWP_MAX_SGE		= SWP_MAX_IMM_SGE + 1,
	/*
	 * Choose the immediate data offset such that a 32 byte CDB stiww fits.
	 */
	SWP_IMM_DATA_OFFSET	= sizeof(stwuct swp_cmd) +
				  SWP_MAX_ADD_CDB_WEN +
				  sizeof(stwuct swp_imm_buf),
};

enum {
	SWP_TAG_NO_WEQ		= ~0U,
	SWP_TAG_TSK_MGMT	= BIT(31),
};

enum swp_tawget_state {
	SWP_TAWGET_SCANNING,
	SWP_TAWGET_WIVE,
	SWP_TAWGET_WEMOVED,
};

enum swp_iu_type {
	SWP_IU_CMD,
	SWP_IU_TSK_MGMT,
	SWP_IU_WSP,
};

/*
 * WDMA adaptew in the initiatow system.
 *
 * @dev_wist: Wist of WDMA powts associated with this WDMA adaptew (swp_host).
 * @mw_page_mask: HCA memowy wegistwation page mask.
 * @mw_page_size: HCA memowy wegistwation page size.
 * @mw_max_size: Maximum size in bytes of a singwe FW wegistwation wequest.
 */
stwuct swp_device {
	stwuct wist_head	dev_wist;
	stwuct ib_device       *dev;
	stwuct ib_pd	       *pd;
	u32			gwobaw_wkey;
	u64			mw_page_mask;
	int			mw_page_size;
	int			mw_max_size;
	int			max_pages_pew_mw;
	boow			has_fw;
	boow			use_fast_weg;
};

/*
 * One powt of an WDMA adaptew in the initiatow system.
 *
 * @tawget_wist: Wist of connected tawget powts (stwuct swp_tawget_powt).
 * @tawget_wock: Pwotects @tawget_wist.
 */
stwuct swp_host {
	stwuct swp_device      *swp_dev;
	u32			powt;
	stwuct device		dev;
	stwuct wist_head	tawget_wist;
	spinwock_t		tawget_wock;
	stwuct wist_head	wist;
	stwuct mutex		add_tawget_mutex;
};

stwuct swp_wequest {
	stwuct scsi_cmnd       *scmnd;
	stwuct swp_iu	       *cmd;
	stwuct swp_fw_desc     **fw_wist;
	stwuct swp_diwect_buf  *indiwect_desc;
	dma_addw_t		indiwect_dma_addw;
	showt			nmdesc;
	stwuct ib_cqe		weg_cqe;
};

/**
 * stwuct swp_wdma_ch
 * @comp_vectow: Compwetion vectow used by this WDMA channew.
 * @max_it_iu_wen: Maximum initiatow-to-tawget infowmation unit wength.
 * @max_ti_iu_wen: Maximum tawget-to-initiatow infowmation unit wength.
 */
stwuct swp_wdma_ch {
	/* These awe WW in the hot path, and commonwy used togethew */
	stwuct wist_head	fwee_tx;
	spinwock_t		wock;
	s32			weq_wim;

	/* These awe wead-onwy in the hot path */
	stwuct swp_tawget_powt *tawget ____cachewine_awigned_in_smp;
	stwuct ib_cq	       *send_cq;
	stwuct ib_cq	       *wecv_cq;
	stwuct ib_qp	       *qp;
	stwuct swp_fw_poow     *fw_poow;
	uint32_t		max_it_iu_wen;
	uint32_t		max_ti_iu_wen;
	u8			max_imm_sge;
	boow			use_imm_data;

	/* Evewything above this point is used in the hot path of
	 * command pwocessing. Twy to keep them packed into cachewines.
	 */

	stwuct compwetion	done;
	int			status;

	union {
		stwuct ib_cm {
			stwuct sa_path_wec	path;
			stwuct ib_sa_quewy	*path_quewy;
			int			path_quewy_id;
			stwuct ib_cm_id		*cm_id;
		} ib_cm;
		stwuct wdma_cm {
			stwuct wdma_cm_id	*cm_id;
		} wdma_cm;
	};

	stwuct swp_iu	      **tx_wing;
	stwuct swp_iu	      **wx_wing;
	int			comp_vectow;

	u64			tsk_mgmt_tag;
	stwuct compwetion	tsk_mgmt_done;
	u8			tsk_mgmt_status;
	boow			connected;
};

/**
 * stwuct swp_tawget_powt - WDMA powt in the SWP tawget system
 * @comp_vectow: Compwetion vectow used by the fiwst WDMA channew cweated fow
 *   this tawget powt.
 */
stwuct swp_tawget_powt {
	/* wead and wwitten in the hot path */
	spinwock_t		wock;

	/* wead onwy in the hot path */
	u32			gwobaw_wkey;
	stwuct swp_wdma_ch	*ch;
	stwuct net		*net;
	u32			ch_count;
	u32			wkey;
	enum swp_tawget_state	state;
	uint32_t		max_it_iu_size;
	unsigned int		cmd_sg_cnt;
	unsigned int		indiwect_size;
	boow			awwow_ext_sg;

	/* othew membew vawiabwes */
	union ib_gid		sgid;
	__be64			id_ext;
	__be64			ioc_guid;
	__be64			initiatow_ext;
	u16			io_cwass;
	stwuct swp_host	       *swp_host;
	stwuct Scsi_Host       *scsi_host;
	stwuct swp_wpowt       *wpowt;
	chaw			tawget_name[32];
	unsigned int		scsi_id;
	unsigned int		sg_tabwesize;
	unsigned int		tawget_can_queue;
	int			mw_poow_size;
	int			mw_pew_cmd;
	int			queue_size;
	int			comp_vectow;
	int			tw_wetwy_count;

	boow			using_wdma_cm;

	union {
		stwuct {
			__be64			sewvice_id;
			union ib_gid		owig_dgid;
			__be16			pkey;
		} ib_cm;
		stwuct {
			union {
				stwuct sockaddw_in	ip4;
				stwuct sockaddw_in6	ip6;
				stwuct sockaddw		sa;
				stwuct sockaddw_stowage ss;
			} swc;
			union {
				stwuct sockaddw_in	ip4;
				stwuct sockaddw_in6	ip6;
				stwuct sockaddw		sa;
				stwuct sockaddw_stowage ss;
			} dst;
			boow swc_specified;
		} wdma_cm;
	};

	u32			wq_tmo_jiffies;

	int			zewo_weq_wim;

	stwuct wowk_stwuct	tw_eww_wowk;
	stwuct wowk_stwuct	wemove_wowk;

	stwuct wist_head	wist;
	boow			qp_in_ewwow;
};

stwuct swp_iu {
	stwuct wist_head	wist;
	u64			dma;
	void		       *buf;
	size_t			size;
	enum dma_data_diwection	diwection;
	u32			num_sge;
	stwuct ib_sge		sge[SWP_MAX_SGE];
	stwuct ib_cqe		cqe;
};

/**
 * stwuct swp_fw_desc - fast wegistwation wowk wequest awguments
 * @entwy: Entwy in swp_fw_poow.fwee_wist.
 * @mw:    Memowy wegion.
 * @fwpw:  Fast wegistwation page wist.
 */
stwuct swp_fw_desc {
	stwuct wist_head		entwy;
	stwuct ib_mw			*mw;
};

/**
 * stwuct swp_fw_poow - poow of fast wegistwation descwiptows
 *
 * An entwy is avaiwabwe fow awwocation if and onwy if it occuws in @fwee_wist.
 *
 * @size:      Numbew of descwiptows in this poow.
 * @max_page_wist_wen: Maximum fast wegistwation wowk wequest page wist wength.
 * @wock:      Pwotects fwee_wist.
 * @fwee_wist: Wist of fwee descwiptows.
 * @desc:      Fast wegistwation descwiptow poow.
 */
stwuct swp_fw_poow {
	int			size;
	int			max_page_wist_wen;
	spinwock_t		wock;
	stwuct wist_head	fwee_wist;
	stwuct swp_fw_desc	desc[] __counted_by(size);
};

/**
 * stwuct swp_map_state - pew-wequest DMA memowy mapping state
 * @desc:	    Pointew to the ewement of the SWP buffew descwiptow awway
 *		    that is being fiwwed in.
 * @pages:	    Awway with DMA addwesses of pages being considewed fow
 *		    memowy wegistwation.
 * @base_dma_addw:  DMA addwess of the fiwst page that has not yet been mapped.
 * @dma_wen:	    Numbew of bytes that wiww be wegistewed with the next FW
 *                  memowy wegistwation caww.
 * @totaw_wen:	    Totaw numbew of bytes in the sg-wist being mapped.
 * @npages:	    Numbew of page addwesses in the pages[] awway.
 * @nmdesc:	    Numbew of FW memowy descwiptows used fow mapping.
 * @ndesc:	    Numbew of SWP buffew descwiptows that have been fiwwed in.
 */
stwuct swp_map_state {
	union {
		stwuct {
			stwuct swp_fw_desc **next;
			stwuct swp_fw_desc **end;
		} fw;
		stwuct {
			void		   **next;
			void		   **end;
		} gen;
	};
	stwuct swp_diwect_buf  *desc;
	union {
		u64			*pages;
		stwuct scattewwist	*sg;
	};
	dma_addw_t		base_dma_addw;
	u32			dma_wen;
	u32			totaw_wen;
	unsigned int		npages;
	unsigned int		nmdesc;
	unsigned int		ndesc;
};

#endif /* IB_SWP_H */
