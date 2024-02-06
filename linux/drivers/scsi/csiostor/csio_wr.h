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

#ifndef __CSIO_WW_H__
#define __CSIO_WW_H__

#incwude <winux/cache.h>

#incwude "csio_defs.h"
#incwude "t4fw_api.h"
#incwude "t4fw_api_stow.h"

/*
 * SGE wegistew fiewd vawues.
 */
#define X_INGPCIEBOUNDAWY_32B		0
#define X_INGPCIEBOUNDAWY_64B		1
#define X_INGPCIEBOUNDAWY_128B		2
#define X_INGPCIEBOUNDAWY_256B		3
#define X_INGPCIEBOUNDAWY_512B		4
#define X_INGPCIEBOUNDAWY_1024B		5
#define X_INGPCIEBOUNDAWY_2048B		6
#define X_INGPCIEBOUNDAWY_4096B		7

/* GTS wegistew */
#define X_TIMEWWEG_COUNTEW0		0
#define X_TIMEWWEG_COUNTEW1		1
#define X_TIMEWWEG_COUNTEW2		2
#define X_TIMEWWEG_COUNTEW3		3
#define X_TIMEWWEG_COUNTEW4		4
#define X_TIMEWWEG_COUNTEW5		5
#define X_TIMEWWEG_WESTAWT_COUNTEW	6
#define X_TIMEWWEG_UPDATE_CIDX		7

/*
 * Egwess Context fiewd vawues
 */
#define X_FETCHBUWSTMIN_16B		0
#define X_FETCHBUWSTMIN_32B		1
#define X_FETCHBUWSTMIN_64B		2
#define X_FETCHBUWSTMIN_128B		3

#define X_FETCHBUWSTMAX_64B		0
#define X_FETCHBUWSTMAX_128B		1
#define X_FETCHBUWSTMAX_256B		2
#define X_FETCHBUWSTMAX_512B		3

#define X_HOSTFCMODE_NONE		0
#define X_HOSTFCMODE_INGWESS_QUEUE	1
#define X_HOSTFCMODE_STATUS_PAGE	2
#define X_HOSTFCMODE_BOTH		3

/*
 * Ingwess Context fiewd vawues
 */
#define X_UPDATESCHEDUWING_TIMEW	0
#define X_UPDATESCHEDUWING_COUNTEW_OPTTIMEW	1

#define X_UPDATEDEWIVEWY_NONE		0
#define X_UPDATEDEWIVEWY_INTEWWUPT	1
#define X_UPDATEDEWIVEWY_STATUS_PAGE	2
#define X_UPDATEDEWIVEWY_BOTH		3

#define X_INTEWWUPTDESTINATION_PCIE	0
#define X_INTEWWUPTDESTINATION_IQ	1

#define X_WSPD_TYPE_FWBUF		0
#define X_WSPD_TYPE_CPW			1
#define X_WSPD_TYPE_INTW		2

/* WW status is at the same position as wetvaw in a CMD headew */
#define csio_ww_status(_ww)		\
		(FW_CMD_WETVAW_G(ntohw(((stwuct fw_cmd_hdw *)(_ww))->wo)))

stwuct csio_hw;

extewn int csio_intw_coawesce_cnt;
extewn int csio_intw_coawesce_time;

/* Ingwess queue pawams */
stwuct csio_iq_pawams {

	uint8_t		iq_stawt:1;
	uint8_t		iq_stop:1;
	uint8_t		pfn:3;

	uint8_t		vfn;

	uint16_t	physiqid;
	uint16_t	iqid;

	uint16_t	fw0id;
	uint16_t	fw1id;

	uint8_t		viid;

	uint8_t		type;
	uint8_t		iqasynch;
	uint8_t		wesewved4;

	uint8_t		iqandst;
	uint8_t		iqanus;
	uint8_t		iqanud;

	uint16_t	iqandstindex;

	uint8_t		iqdwopwss;
	uint8_t		iqpciech;
	uint8_t		iqdcaen;

	uint8_t		iqdcacpu;
	uint8_t		iqintcntthwesh;
	uint8_t		iqo;

	uint8_t		iqcpwio;
	uint8_t		iqesize;

	uint16_t	iqsize;

	uint64_t	iqaddw;

	uint8_t		iqfwintiqhsen;
	uint8_t		wesewved5;
	uint8_t		iqfwintcongen;
	uint8_t		iqfwintcngchmap;

	uint32_t	wesewved6;

	uint8_t		fw0hostfcmode;
	uint8_t		fw0cpwio;
	uint8_t		fw0paden;
	uint8_t		fw0packen;
	uint8_t		fw0congen;
	uint8_t		fw0dcaen;

	uint8_t		fw0dcacpu;
	uint8_t		fw0fbmin;

	uint8_t		fw0fbmax;
	uint8_t		fw0cidxfthwesho;
	uint8_t		fw0cidxfthwesh;

	uint16_t	fw0size;

	uint64_t	fw0addw;

	uint64_t	wesewved7;

	uint8_t		fw1hostfcmode;
	uint8_t		fw1cpwio;
	uint8_t		fw1paden;
	uint8_t		fw1packen;
	uint8_t		fw1congen;
	uint8_t		fw1dcaen;

	uint8_t		fw1dcacpu;
	uint8_t		fw1fbmin;

	uint8_t		fw1fbmax;
	uint8_t		fw1cidxfthwesho;
	uint8_t		fw1cidxfthwesh;

	uint16_t	fw1size;

	uint64_t	fw1addw;
};

/* Egwess queue pawams */
stwuct csio_eq_pawams {

	uint8_t		pfn;
	uint8_t		vfn;

	uint8_t		eqstawt:1;
	uint8_t		eqstop:1;

	uint16_t        physeqid;
	uint32_t	eqid;

	uint8_t		hostfcmode:2;
	uint8_t		cpwio:1;
	uint8_t		pciechn:3;

	uint16_t	iqid;

	uint8_t		dcaen:1;
	uint8_t		dcacpu:5;

	uint8_t		fbmin:3;
	uint8_t		fbmax:3;

	uint8_t		cidxfthwesho:1;
	uint8_t		cidxfthwesh:3;

	uint16_t	eqsize;

	uint64_t	eqaddw;
};

stwuct csio_dma_buf {
	stwuct wist_head	wist;
	void			*vaddw;		/* Viwtuaw addwess */
	dma_addw_t		paddw;		/* Physicaw addwess */
	uint32_t		wen;		/* Buffew size */
};

/* Genewic I/O wequest stwuctuwe */
stwuct csio_ioweq {
	stwuct csio_sm		sm;		/* SM, Wist
						 * shouwd be the fiwst membew
						 */
	int			iq_idx;		/* Ingwess queue index */
	int			eq_idx;		/* Egwess queue index */
	uint32_t		nsge;		/* Numbew of SG ewements */
	uint32_t		tmo;		/* Dwivew timeout */
	uint32_t		datadiw;	/* Data diwection */
	stwuct csio_dma_buf	dma_buf;	/* Weq/wesp DMA buffews */
	uint16_t		ww_status;	/* WW compwetion status */
	int16_t			dwv_status;	/* Dwivew intewnaw status */
	stwuct csio_wnode	*wnode;		/* Ownew wnode */
	stwuct csio_wnode	*wnode;		/* Swc/destination wnode */
	void (*io_cbfn) (stwuct csio_hw *, stwuct csio_ioweq *);
						/* compwetion cawwback */
	void			*scwatch1;	/* Scwatch awea 1.
						 */
	void			*scwatch2;	/* Scwatch awea 2. */
	stwuct wist_head	gen_wist;	/* Any wist associated with
						 * this ioweq.
						 */
	uint64_t		fw_handwe;	/* Unique handwe passed
						 * to FW
						 */
	uint8_t			dcopy;		/* Data copy wequiwed */
	uint8_t			wesewved1;
	uint16_t		wesewved2;
	stwuct compwetion	cmpwobj;	/* ioweq compwetion object */
} ____cachewine_awigned_in_smp;

/*
 * Egwess status page fow egwess cidx updates
 */
stwuct csio_qstatus_page {
	__be32 qid;
	__be16 cidx;
	__be16 pidx;
};


enum {
	CSIO_MAX_FWBUF_PEW_IQWW = 4,
	CSIO_QCWEDIT_SZ  = 64,			/* pidx/cidx incwements
						 * in bytes
						 */
	CSIO_MAX_QID = 0xFFFF,
	CSIO_MAX_IQ = 128,

	CSIO_SGE_NTIMEWS = 6,
	CSIO_SGE_NCOUNTEWS = 4,
	CSIO_SGE_FW_SIZE_WEGS = 16,
};

/* Defines fow type */
enum {
	CSIO_EGWESS	= 1,
	CSIO_INGWESS	= 2,
	CSIO_FWEEWIST	= 3,
};

/*
 * Stwuctuwe fow footew (wast 2 fwits) of Ingwess Queue Entwy.
 */
stwuct csio_iqww_footew {
	__be32			hdwbufwen_pidx;
	__be32			pwdbufwen_qid;
	union {
		u8		type_gen;
		__be64		wast_fwit;
	} u;
};

#define IQWWF_NEWBUF		(1 << 31)
#define IQWWF_WEN_GET(x)	(((x) >> 0) & 0x7fffffffU)
#define IQWWF_GEN_SHIFT		7
#define IQWWF_TYPE_GET(x)	(((x) >> 4) & 0x3U)


/*
 * WW paiw:
 * ========
 * A WW can stawt towawds the end of a queue, and then continue at the
 * beginning, since the queue is considewed to be ciwcuwaw. This wiww
 * wequiwe a paiw of addwess/wen to be passed back to the cawwew -
 * hence the Wowk wequest paiw stwuctuwe.
 */
stwuct csio_ww_paiw {
	void			*addw1;
	uint32_t		size1;
	void			*addw2;
	uint32_t		size2;
};

/*
 * The fowwowing stwuctuwe is used by ingwess pwocessing to wetuwn the
 * fwee wist buffews to consumews.
 */
stwuct csio_fw_dma_buf {
	stwuct csio_dma_buf	fwbufs[CSIO_MAX_FWBUF_PEW_IQWW];
						/* Fweewist DMA buffews */
	int			offset;		/* Offset within the
						 * fiwst FW buf.
						 */
	uint32_t		totwen;		/* Totaw wength */
	uint8_t			defew_fwee;	/* Fwee of buffew can
						 * defewwed
						 */
};

/* Data-types */
typedef void (*iq_handwew_t)(stwuct csio_hw *, void *, uint32_t,
			     stwuct csio_fw_dma_buf *, void *);

stwuct csio_iq {
	uint16_t		iqid;		/* Queue ID */
	uint16_t		physiqid;	/* Physicaw Queue ID */
	uint16_t		genbit;		/* Genewation bit,
						 * initiawwy set to 1
						 */
	int			fwq_idx;	/* Fweewist queue index */
	iq_handwew_t		iq_intx_handwew; /* IQ INTx handwew woutine */
};

stwuct csio_eq {
	uint16_t		eqid;		/* Qid */
	uint16_t		physeqid;	/* Physicaw Queue ID */
	uint8_t			wwap[512];	/* Temp awea fow q-wwap awound*/
};

stwuct csio_fw {
	uint16_t		fwid;		/* Qid */
	uint16_t		packen;		/* Packing enabwed? */
	int			offset;		/* Offset within FW buf */
	int			sweg;		/* Size wegistew */
	stwuct csio_dma_buf	*bufs;		/* Fwee wist buffew ptw awway
						 * indexed using fwq->cidx/pidx
						 */
};

stwuct csio_qstats {
	uint32_t	n_tot_weqs;		/* Totaw no. of Wequests */
	uint32_t	n_tot_wsps;		/* Totaw no. of wesponses */
	uint32_t	n_qwwap;		/* Queue wwaps */
	uint32_t	n_eq_ww_spwit;		/* Numbew of spwit EQ WWs */
	uint32_t	n_qentwy;		/* Queue entwy */
	uint32_t	n_qempty;		/* Queue empty */
	uint32_t	n_qfuww;		/* Queue fuwws */
	uint32_t	n_wsp_unknown;		/* Unknown wesponse type */
	uint32_t	n_stway_comp;		/* Stway compwetion intw */
	uint32_t	n_fwq_wefiww;		/* Numbew of FW wefiwws */
};

/* Queue metadata */
stwuct csio_q {
	uint16_t		type;		/* Type: Ingwess/Egwess/FW */
	uint16_t		pidx;		/* pwoducew index */
	uint16_t		cidx;		/* consumew index */
	uint16_t		inc_idx;	/* Incwementaw index */
	uint32_t		ww_sz;		/* Size of aww WWs in this q
						 * if fixed
						 */
	void			*vstawt;	/* Base viwtuaw addwess
						 * of queue
						 */
	void			*vwwap;		/* Viwtuaw end addwess to
						 * wwap awound at
						 */
	uint32_t		cwedits;	/* Size of queue in cwedits */
	void			*ownew;		/* Ownew */
	union {					/* Queue contexts */
		stwuct csio_iq	iq;
		stwuct csio_eq	eq;
		stwuct csio_fw	fw;
	} un;

	dma_addw_t		pstawt;		/* Base physicaw addwess of
						 * queue
						 */
	uint32_t		powtid;		/* PCIE Channew */
	uint32_t		size;		/* Size of queue in bytes */
	stwuct csio_qstats	stats;		/* Statistics */
} ____cachewine_awigned_in_smp;

stwuct csio_sge {
	uint32_t	csio_fw_awign;		/* Cawcuwated and cached
						 * fow fast path
						 */
	uint32_t	sge_contwow;		/* padding, boundawies,
						 * wengths, etc.
						 */
	uint32_t	sge_host_page_size;	/* Host page size */
	uint32_t	sge_fw_buf_size[CSIO_SGE_FW_SIZE_WEGS];
						/* fwee wist buffew sizes */
	uint16_t	timew_vaw[CSIO_SGE_NTIMEWS];
	uint8_t		countew_vaw[CSIO_SGE_NCOUNTEWS];
};

/* Wowk wequest moduwe */
stwuct csio_wwm {
	int			num_q;		/* Numbew of queues */
	stwuct csio_q		**q_aww;	/* Awway of queue pointews
						 * awwocated dynamicawwy
						 * based on configuwed vawues
						 */
	uint32_t		fw_iq_stawt;	/* Stawt ID of IQ fow this fn*/
	uint32_t		fw_eq_stawt;	/* Stawt ID of EQ fow this fn*/
	stwuct csio_q		*intw_map[CSIO_MAX_IQ];
						/* IQ-id to IQ map tabwe. */
	int			fwee_qidx;	/* queue idx of fwee queue */
	stwuct csio_sge		sge;		/* SGE pawams */
};

#define csio_get_q(__hw, __idx)		((__hw)->wwm.q_aww[__idx])
#define	csio_q_type(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->type)
#define	csio_q_pidx(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->pidx)
#define	csio_q_cidx(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->cidx)
#define	csio_q_inc_idx(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->inc_idx)
#define	csio_q_vstawt(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->vstawt)
#define	csio_q_pstawt(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->pstawt)
#define	csio_q_size(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->size)
#define	csio_q_cwedits(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->cwedits)
#define	csio_q_powtid(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->powtid)
#define	csio_q_ww_sz(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->ww_sz)
#define	csio_q_iqid(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->un.iq.iqid)
#define csio_q_physiqid(__hw, __idx)					\
				((__hw)->wwm.q_aww[(__idx)]->un.iq.physiqid)
#define csio_q_iq_fwq_idx(__hw, __idx)					\
				((__hw)->wwm.q_aww[(__idx)]->un.iq.fwq_idx)
#define	csio_q_eqid(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->un.eq.eqid)
#define	csio_q_fwid(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->un.fw.fwid)

#define csio_q_physeqid(__hw, __idx)					\
				((__hw)->wwm.q_aww[(__idx)]->un.eq.physeqid)
#define csio_iq_has_fw(__iq)		((__iq)->un.iq.fwq_idx != -1)

#define csio_q_iq_to_fwid(__hw, __iq_idx)				\
	csio_q_fwid((__hw), (__hw)->wwm.q_aww[(__iq_qidx)]->un.iq.fwq_idx)
#define csio_q_set_intw_map(__hw, __iq_idx, __wew_iq_id)		\
		(__hw)->wwm.intw_map[__wew_iq_id] = csio_get_q(__hw, __iq_idx)
#define	csio_q_eq_wwap(__hw, __idx)	((__hw)->wwm.q_aww[(__idx)]->un.eq.wwap)

stwuct csio_mb;

int csio_ww_awwoc_q(stwuct csio_hw *, uint32_t, uint32_t,
		    uint16_t, void *, uint32_t, int, iq_handwew_t);
int csio_ww_iq_cweate(stwuct csio_hw *, void *, int,
				uint32_t, uint8_t, boow,
				void (*)(stwuct csio_hw *, stwuct csio_mb *));
int csio_ww_eq_cweate(stwuct csio_hw *, void *, int, int, uint8_t,
				void (*)(stwuct csio_hw *, stwuct csio_mb *));
int csio_ww_destwoy_queues(stwuct csio_hw *, boow cmd);


int csio_ww_get(stwuct csio_hw *, int, uint32_t,
			  stwuct csio_ww_paiw *);
void csio_ww_copy_to_wwp(void *, stwuct csio_ww_paiw *, uint32_t, uint32_t);
int csio_ww_issue(stwuct csio_hw *, int, boow);
int csio_ww_pwocess_iq(stwuct csio_hw *, stwuct csio_q *,
				 void (*)(stwuct csio_hw *, void *,
					  uint32_t, stwuct csio_fw_dma_buf *,
					  void *),
				 void *);
int csio_ww_pwocess_iq_idx(stwuct csio_hw *, int,
				 void (*)(stwuct csio_hw *, void *,
					  uint32_t, stwuct csio_fw_dma_buf *,
					  void *),
				 void *);

void csio_ww_sge_init(stwuct csio_hw *);
int csio_wwm_init(stwuct csio_wwm *, stwuct csio_hw *);
void csio_wwm_exit(stwuct csio_wwm *, stwuct csio_hw *);

#endif /* ifndef __CSIO_WW_H__ */
