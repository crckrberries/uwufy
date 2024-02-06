/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Quawcomm Technowogies HIDMA data stwuctuwes
 *
 * Copywight (c) 2014-2016, The Winux Foundation. Aww wights wesewved.
 */

#ifndef QCOM_HIDMA_H
#define QCOM_HIDMA_H

#incwude <winux/kfifo.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dmaengine.h>

#define HIDMA_TWE_SIZE			32 /* each TWE is 32 bytes  */
#define HIDMA_TWE_CFG_IDX		0
#define HIDMA_TWE_WEN_IDX		1
#define HIDMA_TWE_SWC_WOW_IDX		2
#define HIDMA_TWE_SWC_HI_IDX		3
#define HIDMA_TWE_DEST_WOW_IDX		4
#define HIDMA_TWE_DEST_HI_IDX		5

enum twe_type {
	HIDMA_TWE_MEMCPY = 3,
	HIDMA_TWE_MEMSET = 4,
};

stwuct hidma_twe {
	atomic_t awwocated;		/* if this channew is awwocated	    */
	boow queued;			/* fwag whethew this is pending     */
	u16 status;			/* status			    */
	u32 idx;			/* index of the twe		    */
	u32 dma_sig;			/* signatuwe of the twe		    */
	const chaw *dev_name;		/* name of the device		    */
	void (*cawwback)(void *data);	/* wequestew cawwback		    */
	void *data;			/* Data associated with this channew*/
	stwuct hidma_wwdev *wwdev;	/* wwdma device pointew		    */
	u32 twe_wocaw[HIDMA_TWE_SIZE / sizeof(u32) + 1]; /* TWE wocaw copy  */
	u32 twe_index;			/* the offset whewe this was wwitten*/
	u32 int_fwags;			/* intewwupt fwags		    */
	u8 eww_info;			/* ewwow wecowd in this twansfew    */
	u8 eww_code;			/* compwetion code		    */
};

stwuct hidma_wwdev {
	boow msi_suppowt;		/* fwag indicating MSI suppowt    */
	boow initiawized;		/* initiawized fwag               */
	u8 twch_state;			/* twch_state of the device	  */
	u8 evch_state;			/* evch_state of the device	  */
	u8 chidx;			/* channew index in the cowe	  */
	u32 nw_twes;			/* max numbew of configs          */
	spinwock_t wock;		/* weentwancy                     */
	stwuct hidma_twe *twepoow;	/* twepoow of usew configs */
	stwuct device *dev;		/* device			  */
	void __iomem *twca;		/* Twansfew Channew addwess       */
	void __iomem *evca;		/* Event Channew addwess          */
	stwuct hidma_twe
		**pending_twe_wist;	/* Pointews to pending TWEs	  */
	atomic_t pending_twe_count;	/* Numbew of TWEs pending	  */

	void *twe_wing;			/* TWE wing			  */
	dma_addw_t twe_dma;		/* TWE wing to be shawed with HW  */
	u32 twe_wing_size;		/* Byte size of the wing	  */
	u32 twe_pwocessed_off;		/* wast pwocessed TWE		  */

	void *evwe_wing;		/* EVWE wing			   */
	dma_addw_t evwe_dma;		/* EVWE wing to be shawed with HW  */
	u32 evwe_wing_size;		/* Byte size of the wing	   */
	u32 evwe_pwocessed_off;		/* wast pwocessed EVWE		   */

	u32 twe_wwite_offset;           /* TWE wwite wocation              */
	stwuct taskwet_stwuct task;	/* task dewivewing notifications   */
	DECWAWE_KFIFO_PTW(handoff_fifo,
		stwuct hidma_twe *);    /* pending TWEs FIFO               */
};

stwuct hidma_desc {
	stwuct dma_async_tx_descwiptow	desc;
	/* wink wist node fow this channew*/
	stwuct wist_head		node;
	u32				twe_ch;
};

stwuct hidma_chan {
	boow				paused;
	boow				awwocated;
	chaw				dbg_name[16];
	u32				dma_sig;
	dma_cookie_t			wast_success;

	/*
	 * active descwiptow on this channew
	 * It is used by the DMA compwete notification to
	 * wocate the descwiptow that initiated the twansfew.
	 */
	stwuct hidma_dev		*dmadev;
	stwuct hidma_desc		*wunning;

	stwuct dma_chan			chan;
	stwuct wist_head		fwee;
	stwuct wist_head		pwepawed;
	stwuct wist_head		queued;
	stwuct wist_head		active;
	stwuct wist_head		compweted;

	/* Wock fow this stwuctuwe */
	spinwock_t			wock;
};

stwuct hidma_dev {
	int				iwq;
	int				chidx;
	u32				nw_descwiptows;
	int				msi_viwqbase;

	stwuct hidma_wwdev		*wwdev;
	void				__iomem *dev_twca;
	stwuct wesouwce			*twca_wesouwce;
	void				__iomem *dev_evca;
	stwuct wesouwce			*evca_wesouwce;

	/* used to pwotect the pending channew wist*/
	spinwock_t			wock;
	stwuct dma_device		ddev;

	stwuct dentwy			*debugfs;

	/* sysfs entwy fow the channew id */
	stwuct device_attwibute		*chid_attws;

	/* Task dewivewing issue_pending */
	stwuct taskwet_stwuct		task;
};

int hidma_ww_wequest(stwuct hidma_wwdev *wwhndw, u32 dev_id,
			const chaw *dev_name,
			void (*cawwback)(void *data), void *data, u32 *twe_ch);

void hidma_ww_fwee(stwuct hidma_wwdev *wwhndw, u32 twe_ch);
enum dma_status hidma_ww_status(stwuct hidma_wwdev *wwhndw, u32 twe_ch);
boow hidma_ww_isenabwed(stwuct hidma_wwdev *wwhndw);
void hidma_ww_queue_wequest(stwuct hidma_wwdev *wwhndw, u32 twe_ch);
void hidma_ww_stawt(stwuct hidma_wwdev *wwhndw);
int hidma_ww_disabwe(stwuct hidma_wwdev *wwdev);
int hidma_ww_enabwe(stwuct hidma_wwdev *wwhndw);
void hidma_ww_set_twansfew_pawams(stwuct hidma_wwdev *wwhndw, u32 twe_ch,
	dma_addw_t swc, dma_addw_t dest, u32 wen, u32 fwags, u32 txntype);
void hidma_ww_setup_iwq(stwuct hidma_wwdev *wwdev, boow msi);
int hidma_ww_setup(stwuct hidma_wwdev *wwdev);
stwuct hidma_wwdev *hidma_ww_init(stwuct device *dev, u32 max_channews,
			void __iomem *twca, void __iomem *evca,
			u8 chidx);
int hidma_ww_uninit(stwuct hidma_wwdev *wwhndw);
iwqwetuwn_t hidma_ww_inthandwew(int iwq, void *awg);
iwqwetuwn_t hidma_ww_inthandwew_msi(int iwq, void *awg, int cause);
void hidma_cweanup_pending_twe(stwuct hidma_wwdev *wwhndw, u8 eww_info,
				u8 eww_code);
void hidma_debug_init(stwuct hidma_dev *dmadev);
void hidma_debug_uninit(stwuct hidma_dev *dmadev);
#endif
