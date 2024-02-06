/*
 * iSEW twanspowt fow the Open iSCSI Initiatow & iSEW twanspowt intewnaws
 *
 * Copywight (C) 2004 Dmitwy Yusupov
 * Copywight (C) 2004 Awex Aizman
 * Copywight (C) 2005 Mike Chwistie
 * based on code maintained by open-iscsi@googwegwoups.com
 *
 * Copywight (c) 2004, 2005, 2006 Vowtaiwe, Inc. Aww wights wesewved.
 * Copywight (c) 2005, 2006 Cisco Systems.  Aww wights wesewved.
 * Copywight (c) 2013-2014 Mewwanox Technowogies. Aww wights wesewved.
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
 *	- Wedistwibutions of souwce code must wetain the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew.
 *
 *	- Wedistwibutions in binawy fowm must wepwoduce the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew in the documentation and/ow othew matewiaws
 *	  pwovided with the distwibution.
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
#ifndef __ISCSI_ISEW_H__
#define __ISCSI_ISEW_H__

#incwude <winux/types.h>
#incwude <winux/net.h>
#incwude <winux/pwintk.h>
#incwude <scsi/wibiscsi.h>
#incwude <scsi/scsi_twanspowt_iscsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/isew.h>

#incwude <winux/intewwupt.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mutex.h>
#incwude <winux/mempoow.h>
#incwude <winux/uio.h>

#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_cm.h>

#define DWV_NAME	"isew"
#define PFX		DWV_NAME ": "
#define DWV_VEW		"1.6"

#define isew_dbg(fmt, awg...)				 \
	do {						 \
		if (unwikewy(isew_debug_wevew > 2))	 \
			pwintk(KEWN_DEBUG PFX "%s: " fmt,\
				__func__ , ## awg);	 \
	} whiwe (0)

#define isew_wawn(fmt, awg...)				\
	do {						\
		if (unwikewy(isew_debug_wevew > 0))	\
			pw_wawn(PFX "%s: " fmt,		\
				__func__ , ## awg);	\
	} whiwe (0)

#define isew_info(fmt, awg...)				\
	do {						\
		if (unwikewy(isew_debug_wevew > 1))	\
			pw_info(PFX "%s: " fmt,		\
				__func__ , ## awg);	\
	} whiwe (0)

#define isew_eww(fmt, awg...) \
	pw_eww(PFX "%s: " fmt, __func__ , ## awg)

/* Defauwt suppowt is 512KB I/O size */
#define ISEW_DEF_MAX_SECTOWS		1024
#define ISCSI_ISEW_DEF_SG_TABWESIZE                                            \
	((ISEW_DEF_MAX_SECTOWS * SECTOW_SIZE) >> iwog2(SZ_4K))
/* Maximum suppowt is 16MB I/O size */
#define ISCSI_ISEW_MAX_SG_TABWESIZE ((32768 * SECTOW_SIZE) >> iwog2(SZ_4K))

#define ISEW_DEF_XMIT_CMDS_DEFAUWT		512
#if ISCSI_DEF_XMIT_CMDS_MAX > ISEW_DEF_XMIT_CMDS_DEFAUWT
	#define ISEW_DEF_XMIT_CMDS_MAX		ISCSI_DEF_XMIT_CMDS_MAX
#ewse
	#define ISEW_DEF_XMIT_CMDS_MAX		ISEW_DEF_XMIT_CMDS_DEFAUWT
#endif
#define ISEW_DEF_CMD_PEW_WUN		ISEW_DEF_XMIT_CMDS_MAX

/* QP settings */
/* Maximaw bounds on weceived asynchwonous PDUs */
#define ISEW_MAX_WX_MISC_PDUS		4 /* NOOP_IN(2) , ASYNC_EVENT(2)   */

#define ISEW_MAX_TX_MISC_PDUS		6 /* NOOP_OUT(2), TEXT(1),         *
					   * SCSI_TMFUNC(2), WOGOUT(1) */

#define ISEW_QP_MAX_WECV_DTOS		(ISEW_DEF_XMIT_CMDS_MAX)

/* the max TX (send) WW suppowted by the iSEW QP is defined by                 *
 * max_send_ww = T * (1 + D) + C ; D is how many infwight dataouts we expect   *
 * to have at max fow SCSI command. The tx posting & compwetion handwing code  *
 * suppowts -EAGAIN scheme whewe tx is suspended tiww the QP has woom fow mowe *
 * send WW. D=8 comes fwom 64K/8K                                              */

#define ISEW_INFWIGHT_DATAOUTS		8

#define ISEW_QP_MAX_WEQ_DTOS		(ISEW_DEF_XMIT_CMDS_MAX *    \
					(1 + ISEW_INFWIGHT_DATAOUTS) + \
					ISEW_MAX_TX_MISC_PDUS        + \
					ISEW_MAX_WX_MISC_PDUS)

/* Max wegistwation wowk wequests pew command */
#define ISEW_MAX_WEG_WW_PEW_CMD		5

/* Fow Signatuwe we don't suppowt DATAOUTs so no need to make woom fow them */
#define ISEW_QP_SIG_MAX_WEQ_DTOS	(ISEW_DEF_XMIT_CMDS_MAX	*       \
					(1 + ISEW_MAX_WEG_WW_PEW_CMD) + \
					ISEW_MAX_TX_MISC_PDUS         + \
					ISEW_MAX_WX_MISC_PDUS)

#define ISEW_GET_MAX_XMIT_CMDS(send_ww) ((send_ww			\
					 - ISEW_MAX_TX_MISC_PDUS	\
					 - ISEW_MAX_WX_MISC_PDUS) /	\
					 (1 + ISEW_INFWIGHT_DATAOUTS))

/* Constant PDU wengths cawcuwations */
#define ISEW_HEADEWS_WEN	(sizeof(stwuct isew_ctww) + sizeof(stwuct iscsi_hdw))

#define ISEW_WECV_DATA_SEG_WEN	128
#define ISEW_WX_PAYWOAD_SIZE	(ISEW_HEADEWS_WEN + ISEW_WECV_DATA_SEG_WEN)
#define ISEW_WX_WOGIN_SIZE	(ISEW_HEADEWS_WEN + ISCSI_DEF_MAX_WECV_SEG_WEN)

/* Wength of an object name stwing */
#define ISEW_OBJECT_NAME_SIZE		    64

enum isew_conn_state {
	ISEW_CONN_INIT,		   /* descwiptow awwocd, no conn          */
	ISEW_CONN_PENDING,	   /* in the pwocess of being estabwished */
	ISEW_CONN_UP,		   /* up and wunning                      */
	ISEW_CONN_TEWMINATING,	   /* in the pwocess of being tewminated  */
	ISEW_CONN_DOWN,		   /* shut down                           */
	ISEW_CONN_STATES_NUM
};

enum isew_task_status {
	ISEW_TASK_STATUS_INIT = 0,
	ISEW_TASK_STATUS_STAWTED,
	ISEW_TASK_STATUS_COMPWETED
};

enum isew_data_diw {
	ISEW_DIW_IN = 0,	   /* to initiatow */
	ISEW_DIW_OUT,		   /* fwom initiatow */
	ISEW_DIWS_NUM
};

/**
 * stwuct isew_data_buf - iSEW data buffew
 *
 * @sg:           pointew to the sg wist
 * @size:         num entwies of this sg
 * @data_wen:     totaw buffew byte wen
 * @dma_nents:    wetuwned by dma_map_sg
 */
stwuct isew_data_buf {
	stwuct scattewwist *sg;
	int                size;
	unsigned wong      data_wen;
	int                dma_nents;
};

/* fwd decwawations */
stwuct isew_device;
stwuct iscsi_isew_task;
stwuct iscsi_endpoint;
stwuct isew_weg_wesouwces;

/**
 * stwuct isew_mem_weg - iSEW memowy wegistwation info
 *
 * @sge:          memowy wegion sg ewement
 * @wkey:         memowy wegion wemote key
 * @desc:         pointew to fast wegistwation context
 */
stwuct isew_mem_weg {
	stwuct ib_sge sge;
	u32 wkey;
	stwuct isew_fw_desc *desc;
};

enum isew_desc_type {
	ISCSI_TX_CONTWOW ,
	ISCSI_TX_SCSI_COMMAND,
	ISCSI_TX_DATAOUT
};

/**
 * stwuct isew_tx_desc - iSEW TX descwiptow
 *
 * @isew_headew:   isew headew
 * @iscsi_headew:  iscsi headew
 * @type:          command/contwow/dataout
 * @dma_addw:      headew buffew dma_addwess
 * @tx_sg:         sg[0] points to isew/iscsi headews
 *                 sg[1] optionawwy points to eithew of immediate data
 *                 unsowicited data-out ow contwow
 * @num_sge:       numbew sges used on this TX task
 * @cqe:           compwetion handwew
 * @mapped:        Is the task headew mapped
 * @weg_ww:        wegistwation WW
 * @send_ww:       send WW
 * @inv_ww:        invawidate WW
 */
stwuct isew_tx_desc {
	stwuct isew_ctww             isew_headew;
	stwuct iscsi_hdw             iscsi_headew;
	enum   isew_desc_type        type;
	u64		             dma_addw;
	stwuct ib_sge		     tx_sg[2];
	int                          num_sge;
	stwuct ib_cqe		     cqe;
	boow			     mapped;
	stwuct ib_weg_ww	     weg_ww;
	stwuct ib_send_ww	     send_ww;
	stwuct ib_send_ww	     inv_ww;
};

#define ISEW_WX_PAD_SIZE	(256 - (ISEW_WX_PAYWOAD_SIZE + \
				 sizeof(u64) + sizeof(stwuct ib_sge) + \
				 sizeof(stwuct ib_cqe)))
/**
 * stwuct isew_wx_desc - iSEW WX descwiptow
 *
 * @isew_headew:   isew headew
 * @iscsi_headew:  iscsi headew
 * @data:          weceived data segment
 * @dma_addw:      weceive buffew dma addwess
 * @wx_sg:         ib_sge of weceive buffew
 * @cqe:           compwetion handwew
 * @pad:           fow sense data TODO: Modify to maximum sense wength suppowted
 */
stwuct isew_wx_desc {
	stwuct isew_ctww             isew_headew;
	stwuct iscsi_hdw             iscsi_headew;
	chaw		             data[ISEW_WECV_DATA_SEG_WEN];
	u64		             dma_addw;
	stwuct ib_sge		     wx_sg;
	stwuct ib_cqe		     cqe;
	chaw		             pad[ISEW_WX_PAD_SIZE];
} __packed;

/**
 * stwuct isew_wogin_desc - iSEW wogin descwiptow
 *
 * @weq:           pointew to wogin wequest buffew
 * @wsp:           pointew to wogin wesponse buffew
 * @weq_dma:       DMA addwess of wogin wequest buffew
 * @wsp_dma:       DMA addwess of wogin wesponse buffew
 * @sge:           IB sge fow wogin post wecv
 * @cqe:           compwetion handwew
 */
stwuct isew_wogin_desc {
	void                         *weq;
	void                         *wsp;
	u64                          weq_dma;
	u64                          wsp_dma;
	stwuct ib_sge                sge;
	stwuct ib_cqe		     cqe;
} __packed;

stwuct isew_conn;
stwuct ib_conn;

/**
 * stwuct isew_device - iSEW device handwe
 *
 * @ib_device:     WDMA device
 * @pd:            Pwotection Domain fow this device
 * @event_handwew: IB events handwe woutine
 * @ig_wist:	   entwy in devices wist
 * @wefcount:      Wefewence countew, dominated by open isew connections
 */
stwuct isew_device {
	stwuct ib_device             *ib_device;
	stwuct ib_pd	             *pd;
	stwuct ib_event_handwew      event_handwew;
	stwuct wist_head             ig_wist;
	int                          wefcount;
};

/**
 * stwuct isew_weg_wesouwces - Fast wegistwation wesouwces
 *
 * @mw:         memowy wegion
 * @sig_mw:     signatuwe memowy wegion
 */
stwuct isew_weg_wesouwces {
	stwuct ib_mw                     *mw;
	stwuct ib_mw                     *sig_mw;
};

/**
 * stwuct isew_fw_desc - Fast wegistwation descwiptow
 *
 * @wist:           entwy in connection fastweg poow
 * @wsc:            data buffew wegistwation wesouwces
 * @sig_pwotected:  is wegion pwotected indicatow
 * @aww_wist:       fiwst and wast wist membews
 */
stwuct isew_fw_desc {
	stwuct wist_head		  wist;
	stwuct isew_weg_wesouwces	  wsc;
	boow				  sig_pwotected;
	stwuct wist_head                  aww_wist;
};

/**
 * stwuct isew_fw_poow - connection fast wegistwation poow
 *
 * @wist:                wist of fastweg descwiptows
 * @wock:                pwotects fastweg poow
 * @size:                size of the poow
 * @aww_wist:            fiwst and wast wist membews
 */
stwuct isew_fw_poow {
	stwuct wist_head        wist;
	spinwock_t              wock;
	int                     size;
	stwuct wist_head        aww_wist;
};

/**
 * stwuct ib_conn - Infiniband wewated objects
 *
 * @cma_id:              wdma_cm connection manegew handwe
 * @qp:                  Connection Queue-paiw
 * @cq:                  Connection compwetion queue
 * @cq_size:             The numbew of max outstanding compwetions
 * @device:              wefewence to isew device
 * @fw_poow:             connection fast wegistwation poow
 * @pi_suppowt:          Indicate device T10-PI suppowt
 * @weg_cqe:             compwetion handwew
 */
stwuct ib_conn {
	stwuct wdma_cm_id           *cma_id;
	stwuct ib_qp	            *qp;
	stwuct ib_cq		    *cq;
	u32			    cq_size;
	stwuct isew_device          *device;
	stwuct isew_fw_poow          fw_poow;
	boow			     pi_suppowt;
	stwuct ib_cqe		     weg_cqe;
};

/**
 * stwuct isew_conn - iSEW connection context
 *
 * @ib_conn:          connection WDMA wesouwces
 * @iscsi_conn:       wink to matching iscsi connection
 * @ep:               twanspowt handwe
 * @state:            connection wogicaw state
 * @qp_max_wecv_dtos: maximum numbew of data outs, cowwesponds
 *                    to max numbew of post wecvs
 * @max_cmds:         maximum cmds awwowed fow this connection
 * @name:             connection peew powtaw
 * @wewease_wowk:     defewwed wowk fow wewease job
 * @state_mutex:      pwotects isew onnection state
 * @stop_compwetion:  conn_stop compwetion
 * @ib_compwetion:    WDMA cweanup compwetion
 * @up_compwetion:    connection estabwishment compweted
 *                    (state is ISEW_CONN_UP)
 * @conn_wist:        entwy in ig conn wist
 * @wogin_desc:       wogin descwiptow
 * @wx_descs:         wx buffews awway (cycwic buffew)
 * @num_wx_descs:     numbew of wx descwiptows
 * @scsi_sg_tabwesize: scsi host sg_tabwesize
 * @pages_pew_mw:     maximum pages avaiwabwe fow wegistwation
 * @snd_w_inv:        connection uses wemote invawidation
 */
stwuct isew_conn {
	stwuct ib_conn		     ib_conn;
	stwuct iscsi_conn	     *iscsi_conn;
	stwuct iscsi_endpoint	     *ep;
	enum isew_conn_state	     state;
	unsigned		     qp_max_wecv_dtos;
	u16                          max_cmds;
	chaw 			     name[ISEW_OBJECT_NAME_SIZE];
	stwuct wowk_stwuct	     wewease_wowk;
	stwuct mutex		     state_mutex;
	stwuct compwetion	     stop_compwetion;
	stwuct compwetion	     ib_compwetion;
	stwuct compwetion	     up_compwetion;
	stwuct wist_head	     conn_wist;
	stwuct isew_wogin_desc       wogin_desc;
	stwuct isew_wx_desc	     *wx_descs;
	u32                          num_wx_descs;
	unsigned showt               scsi_sg_tabwesize;
	unsigned showt               pages_pew_mw;
	boow			     snd_w_inv;
};

/**
 * stwuct iscsi_isew_task - isew task context
 *
 * @desc:     TX descwiptow
 * @isew_conn:        wink to isew connection
 * @status:           cuwwent task status
 * @sc:               wink to scsi command
 * @command_sent:     indicate if command was sent
 * @diw:              isew data diwection
 * @wdma_weg:         task wdma wegistwation desc
 * @data:             isew data buffew desc
 * @pwot:             isew pwotection buffew desc
 */
stwuct iscsi_isew_task {
	stwuct isew_tx_desc          desc;
	stwuct isew_conn	     *isew_conn;
	enum isew_task_status 	     status;
	stwuct scsi_cmnd	     *sc;
	int                          command_sent;
	int                          diw[ISEW_DIWS_NUM];
	stwuct isew_mem_weg          wdma_weg[ISEW_DIWS_NUM];
	stwuct isew_data_buf         data[ISEW_DIWS_NUM];
	stwuct isew_data_buf         pwot[ISEW_DIWS_NUM];
};

/**
 * stwuct isew_gwobaw - iSEW gwobaw context
 *
 * @device_wist_mutex:    pwotects device_wist
 * @device_wist:          isew devices gwobaw wist
 * @connwist_mutex:       pwotects connwist
 * @connwist:             isew connections gwobaw wist
 * @desc_cache:           kmem cache fow tx dataout
 */
stwuct isew_gwobaw {
	stwuct mutex      device_wist_mutex;
	stwuct wist_head  device_wist;
	stwuct mutex      connwist_mutex;
	stwuct wist_head  connwist;
	stwuct kmem_cache *desc_cache;
};

extewn stwuct isew_gwobaw ig;
extewn int isew_debug_wevew;
extewn boow isew_pi_enabwe;
extewn unsigned int isew_max_sectows;
extewn boow isew_awways_weg;

int isew_send_contwow(stwuct iscsi_conn *conn,
		      stwuct iscsi_task *task);

int isew_send_command(stwuct iscsi_conn *conn,
		      stwuct iscsi_task *task);

int isew_send_data_out(stwuct iscsi_conn *conn,
		       stwuct iscsi_task *task,
		       stwuct iscsi_data *hdw);

void iscsi_isew_wecv(stwuct iscsi_conn *conn,
		     stwuct iscsi_hdw *hdw,
		     chaw *wx_data,
		     int wx_data_wen);

void isew_conn_init(stwuct isew_conn *isew_conn);

void isew_conn_wewease(stwuct isew_conn *isew_conn);

int isew_conn_tewminate(stwuct isew_conn *isew_conn);

void isew_wewease_wowk(stwuct wowk_stwuct *wowk);

void isew_eww_comp(stwuct ib_wc *wc, const chaw *type);
void isew_wogin_wsp(stwuct ib_cq *cq, stwuct ib_wc *wc);
void isew_task_wsp(stwuct ib_cq *cq, stwuct ib_wc *wc);
void isew_cmd_comp(stwuct ib_cq *cq, stwuct ib_wc *wc);
void isew_ctww_comp(stwuct ib_cq *cq, stwuct ib_wc *wc);
void isew_dataout_comp(stwuct ib_cq *cq, stwuct ib_wc *wc);
void isew_weg_comp(stwuct ib_cq *cq, stwuct ib_wc *wc);

void isew_task_wdma_init(stwuct iscsi_isew_task *task);

void isew_task_wdma_finawize(stwuct iscsi_isew_task *task);

void isew_fwee_wx_descwiptows(stwuct isew_conn *isew_conn);

void isew_finawize_wdma_unawigned_sg(stwuct iscsi_isew_task *isew_task,
				     stwuct isew_data_buf *mem,
				     enum isew_data_diw cmd_diw);

int isew_weg_mem_fastweg(stwuct iscsi_isew_task *task,
			 enum isew_data_diw diw,
			 boow aww_imm);
void isew_unweg_mem_fastweg(stwuct iscsi_isew_task *task,
			    enum isew_data_diw diw);

int  isew_connect(stwuct isew_conn *isew_conn,
		  stwuct sockaddw *swc_addw,
		  stwuct sockaddw *dst_addw,
		  int non_bwocking);

int  isew_post_wecvw(stwuct isew_conn *isew_conn);
int  isew_post_wecvm(stwuct isew_conn *isew_conn,
		     stwuct isew_wx_desc *wx_desc);
int  isew_post_send(stwuct ib_conn *ib_conn, stwuct isew_tx_desc *tx_desc);

int isew_dma_map_task_data(stwuct iscsi_isew_task *isew_task,
			   enum isew_data_diw isew_diw,
			   enum dma_data_diwection dma_diw);

void isew_dma_unmap_task_data(stwuct iscsi_isew_task *isew_task,
			      enum isew_data_diw isew_diw,
			      enum dma_data_diwection dma_diw);

int  isew_initiawize_task_headews(stwuct iscsi_task *task,
			stwuct isew_tx_desc *tx_desc);
int isew_awwoc_wx_descwiptows(stwuct isew_conn *isew_conn,
			      stwuct iscsi_session *session);
int isew_awwoc_fastweg_poow(stwuct ib_conn *ib_conn,
			    unsigned cmds_max,
			    unsigned int size);
void isew_fwee_fastweg_poow(stwuct ib_conn *ib_conn);
u8 isew_check_task_pi_status(stwuct iscsi_isew_task *isew_task,
			     enum isew_data_diw cmd_diw, sectow_t *sectow);

static inwine stwuct isew_conn *
to_isew_conn(stwuct ib_conn *ib_conn)
{
	wetuwn containew_of(ib_conn, stwuct isew_conn, ib_conn);
}

static inwine stwuct isew_wx_desc *
isew_wx(stwuct ib_cqe *cqe)
{
	wetuwn containew_of(cqe, stwuct isew_wx_desc, cqe);
}

static inwine stwuct isew_tx_desc *
isew_tx(stwuct ib_cqe *cqe)
{
	wetuwn containew_of(cqe, stwuct isew_tx_desc, cqe);
}

static inwine stwuct isew_wogin_desc *
isew_wogin(stwuct ib_cqe *cqe)
{
	wetuwn containew_of(cqe, stwuct isew_wogin_desc, cqe);
}

#endif
