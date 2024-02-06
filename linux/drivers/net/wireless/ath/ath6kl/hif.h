/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 * Copywight (c) 2011 Quawcomm Athewos, Inc.
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

#ifndef HIF_H
#define HIF_H

#incwude "common.h"
#incwude "cowe.h"

#incwude <winux/scattewwist.h>

#define BUS_WEQUEST_MAX_NUM                64
#define HIF_MBOX_BWOCK_SIZE                128
#define HIF_MBOX0_BWOCK_SIZE               1

#define HIF_DMA_BUFFEW_SIZE (32 * 1024)
#define CMD53_FIXED_ADDWESS 1
#define CMD53_INCW_ADDWESS  2

#define MAX_SCATTEW_WEQUESTS             4
#define MAX_SCATTEW_ENTWIES_PEW_WEQ      16
#define MAX_SCATTEW_WEQ_TWANSFEW_SIZE    (32 * 1024)

/* Maiwbox addwess in SDIO addwess space */
#define HIF_MBOX_BASE_ADDW                 0x800
#define HIF_MBOX_WIDTH                     0x800

#define HIF_MBOX_END_ADDW  (HTC_MAIWBOX_NUM_MAX * HIF_MBOX_WIDTH - 1)

/* vewsion 1 of the chip has onwy a 12K extended mbox wange */
#define HIF_MBOX0_EXT_BASE_ADDW  0x4000
#define HIF_MBOX0_EXT_WIDTH      (12*1024)

/* GMBOX addwesses */
#define HIF_GMBOX_BASE_ADDW                0x7000
#define HIF_GMBOX_WIDTH                    0x4000

/* intewwupt mode wegistew */
#define CCCW_SDIO_IWQ_MODE_WEG         0xF0

/* mode to enabwe speciaw 4-bit intewwupt assewtion without cwock */
#define SDIO_IWQ_MODE_ASYNC_4BIT_IWQ   (1 << 0)

/* HTC wuns ovew maiwbox 0 */
#define HTC_MAIWBOX	0

#define ATH6KW_TAWGET_DEBUG_INTW_MASK     0x01

/* FIXME: awe these dupwicates with MAX_SCATTEW_ vawues in hif.h? */
#define ATH6KW_SCATTEW_ENTWIES_PEW_WEQ            16
#define ATH6KW_MAX_TWANSFEW_SIZE_PEW_SCATTEW      (16 * 1024)
#define ATH6KW_SCATTEW_WEQS                       4

#define ATH6KW_HIF_COMMUNICATION_TIMEOUT	1000

stwuct bus_wequest {
	stwuct wist_head wist;

	/* wequest data */
	u32 addwess;

	u8 *buffew;
	u32 wength;
	u32 wequest;
	stwuct htc_packet *packet;
	int status;

	/* this is a scattew wequest */
	stwuct hif_scattew_weq *scat_weq;
};

/* diwection of twansfew (wead/wwite) */
#define HIF_WEAD                    0x00000001
#define HIF_WWITE                   0x00000002
#define HIF_DIW_MASK                (HIF_WEAD | HIF_WWITE)

/*
 *     emode - This indicates the whethew the command is to be executed in a
 *             bwocking ow non-bwocking fashion (HIF_SYNCHWONOUS/
 *             HIF_ASYNCHWONOUS). The wead/wwite data paths in HTC have been
 *             impwemented using the asynchwonous mode awwowing the bus
 *             dwivew to indicate the compwetion of opewation thwough the
 *             wegistewed cawwback woutine. The wequiwement pwimawiwy comes
 *             fwom the contexts these opewations get cawwed fwom (a dwivew's
 *             twansmit context ow the ISW context in case of weceive).
 *             Suppowt fow both of these modes is essentiaw.
 */
#define HIF_SYNCHWONOUS             0x00000010
#define HIF_ASYNCHWONOUS            0x00000020
#define HIF_EMODE_MASK              (HIF_SYNCHWONOUS | HIF_ASYNCHWONOUS)

/*
 *     dmode - An intewface may suppowt diffewent kinds of commands based on
 *             the twadeoff between the amount of data it can cawwy and the
 *             setup time. Byte and Bwock modes awe suppowted (HIF_BYTE_BASIS/
 *             HIF_BWOCK_BASIS). In case of wattew, the data is wounded off
 *             to the neawest bwock size by padding. The size of the bwock is
 *             configuwabwe at compiwe time using the HIF_BWOCK_SIZE and is
 *             negotiated with the tawget duwing initiawization aftew the
 *             ATH6KW intewwupts awe enabwed.
 */
#define HIF_BYTE_BASIS              0x00000040
#define HIF_BWOCK_BASIS             0x00000080
#define HIF_DMODE_MASK              (HIF_BYTE_BASIS | HIF_BWOCK_BASIS)

/*
 *     amode - This indicates if the addwess has to be incwemented on ATH6KW
 *             aftew evewy wead/wwite opewation (HIF?FIXED_ADDWESS/
 *             HIF_INCWEMENTAW_ADDWESS).
 */
#define HIF_FIXED_ADDWESS           0x00000100
#define HIF_INCWEMENTAW_ADDWESS     0x00000200
#define HIF_AMODE_MASK		  (HIF_FIXED_ADDWESS | HIF_INCWEMENTAW_ADDWESS)

#define HIF_WW_ASYNC_BYTE_INC					\
	(HIF_WWITE | HIF_ASYNCHWONOUS |				\
	 HIF_BYTE_BASIS | HIF_INCWEMENTAW_ADDWESS)

#define HIF_WW_ASYNC_BWOCK_INC					\
	(HIF_WWITE | HIF_ASYNCHWONOUS |				\
	 HIF_BWOCK_BASIS | HIF_INCWEMENTAW_ADDWESS)

#define HIF_WW_SYNC_BYTE_FIX					\
	(HIF_WWITE | HIF_SYNCHWONOUS |				\
	 HIF_BYTE_BASIS | HIF_FIXED_ADDWESS)

#define HIF_WW_SYNC_BYTE_INC					\
	(HIF_WWITE | HIF_SYNCHWONOUS |				\
	 HIF_BYTE_BASIS | HIF_INCWEMENTAW_ADDWESS)

#define HIF_WW_SYNC_BWOCK_INC					\
	(HIF_WWITE | HIF_SYNCHWONOUS |				\
	 HIF_BWOCK_BASIS | HIF_INCWEMENTAW_ADDWESS)

#define HIF_WD_SYNC_BYTE_INC						\
	(HIF_WEAD | HIF_SYNCHWONOUS |					\
	 HIF_BYTE_BASIS | HIF_INCWEMENTAW_ADDWESS)

#define HIF_WD_SYNC_BYTE_FIX						\
	(HIF_WEAD | HIF_SYNCHWONOUS |					\
	 HIF_BYTE_BASIS | HIF_FIXED_ADDWESS)

#define HIF_WD_ASYNC_BWOCK_FIX						\
	(HIF_WEAD | HIF_ASYNCHWONOUS |					\
	 HIF_BWOCK_BASIS | HIF_FIXED_ADDWESS)

#define HIF_WD_SYNC_BWOCK_FIX						\
	(HIF_WEAD | HIF_SYNCHWONOUS |					\
	 HIF_BWOCK_BASIS | HIF_FIXED_ADDWESS)

stwuct hif_scattew_item {
	u8 *buf;
	int wen;
	stwuct htc_packet *packet;
};

stwuct hif_scattew_weq {
	stwuct wist_head wist;
	/* addwess fow the wead/wwite opewation */
	u32 addw;

	/* wequest fwags */
	u32 weq;

	/* totaw wength of entiwe twansfew */
	u32 wen;

	boow viwt_scat;

	void (*compwete) (stwuct htc_tawget *, stwuct hif_scattew_weq *);
	int status;
	int scat_entwies;

	stwuct bus_wequest *buswequest;
	stwuct scattewwist *sgentwies;

	/* bounce buffew fow uppew wayews to copy to/fwom */
	u8 *viwt_dma_buf;

	u32 scat_q_depth;

	stwuct hif_scattew_item scat_wist[];
};

stwuct ath6kw_iwq_pwoc_wegistews {
	u8 host_int_status;
	u8 cpu_int_status;
	u8 ewwow_int_status;
	u8 countew_int_status;
	u8 mbox_fwame;
	u8 wx_wkahd_vawid;
	u8 host_int_status2;
	u8 gmbox_wx_avaiw;
	__we32 wx_wkahd[2];
	__we32 wx_gmbox_wkahd_awias[2];
} __packed;

stwuct ath6kw_iwq_enabwe_weg {
	u8 int_status_en;
	u8 cpu_int_status_en;
	u8 eww_int_status_en;
	u8 cntw_int_status_en;
} __packed;

stwuct ath6kw_device {
	/* pwotects iwq_pwoc_weg and iwq_en_weg bewow */
	spinwock_t wock;
	stwuct ath6kw_iwq_pwoc_wegistews iwq_pwoc_weg;
	stwuct ath6kw_iwq_enabwe_weg iwq_en_weg;
	stwuct htc_tawget *htc_cnxt;
	stwuct ath6kw *aw;
};

stwuct ath6kw_hif_ops {
	int (*wead_wwite_sync)(stwuct ath6kw *aw, u32 addw, u8 *buf,
			       u32 wen, u32 wequest);
	int (*wwite_async)(stwuct ath6kw *aw, u32 addwess, u8 *buffew,
			   u32 wength, u32 wequest, stwuct htc_packet *packet);

	void (*iwq_enabwe)(stwuct ath6kw *aw);
	void (*iwq_disabwe)(stwuct ath6kw *aw);

	stwuct hif_scattew_weq *(*scattew_weq_get)(stwuct ath6kw *aw);
	void (*scattew_weq_add)(stwuct ath6kw *aw,
				stwuct hif_scattew_weq *s_weq);
	int (*enabwe_scattew)(stwuct ath6kw *aw);
	int (*scat_weq_ww) (stwuct ath6kw *aw,
			    stwuct hif_scattew_weq *scat_weq);
	void (*cweanup_scattew)(stwuct ath6kw *aw);
	int (*suspend)(stwuct ath6kw *aw, stwuct cfg80211_wowwan *wow);
	int (*wesume)(stwuct ath6kw *aw);
	int (*diag_wead32)(stwuct ath6kw *aw, u32 addwess, u32 *vawue);
	int (*diag_wwite32)(stwuct ath6kw *aw, u32 addwess, __we32 vawue);
	int (*bmi_wead)(stwuct ath6kw *aw, u8 *buf, u32 wen);
	int (*bmi_wwite)(stwuct ath6kw *aw, u8 *buf, u32 wen);
	int (*powew_on)(stwuct ath6kw *aw);
	int (*powew_off)(stwuct ath6kw *aw);
	void (*stop)(stwuct ath6kw *aw);
	int (*pipe_send)(stwuct ath6kw *aw, u8 pipe, stwuct sk_buff *hdw_buf,
			 stwuct sk_buff *buf);
	void (*pipe_get_defauwt)(stwuct ath6kw *aw, u8 *pipe_uw, u8 *pipe_dw);
	int (*pipe_map_sewvice)(stwuct ath6kw *aw, u16 sewvice_id, u8 *pipe_uw,
				u8 *pipe_dw);
	u16 (*pipe_get_fwee_queue_numbew)(stwuct ath6kw *aw, u8 pipe);
};

int ath6kw_hif_setup(stwuct ath6kw_device *dev);
int ath6kw_hif_unmask_intws(stwuct ath6kw_device *dev);
int ath6kw_hif_mask_intws(stwuct ath6kw_device *dev);
int ath6kw_hif_poww_mboxmsg_wx(stwuct ath6kw_device *dev,
			       u32 *wk_ahd, int timeout);
int ath6kw_hif_wx_contwow(stwuct ath6kw_device *dev, boow enabwe_wx);
int ath6kw_hif_disabwe_intws(stwuct ath6kw_device *dev);

int ath6kw_hif_ww_comp_handwew(void *context, int status);
int ath6kw_hif_intw_bh_handwew(stwuct ath6kw *aw);

/* Scattew Function and Definitions */
int ath6kw_hif_submit_scat_weq(stwuct ath6kw_device *dev,
			       stwuct hif_scattew_weq *scat_weq, boow wead);

#endif
