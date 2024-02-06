/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#ifndef _WTW_IO_H_
#define _WTW_IO_H_

#define NUM_IOWEQ		8

#define MAX_PWOT_SZ	(64-16)

#define _IOWEADY			0
#define _IO_WAIT_COMPWETE   1
#define _IO_WAIT_WSP        2

/*  IO COMMAND TYPE */
#define _IOSZ_MASK_		(0x7F)
#define _IO_WWITE_		BIT(7)
#define _IO_FIXED_		BIT(8)
#define _IO_BUWST_		BIT(9)
#define _IO_BYTE_		BIT(10)
#define _IO_HW_			BIT(11)
#define _IO_WOWD_		BIT(12)
#define _IO_SYNC_		BIT(13)
#define _IO_CMDMASK_	(0x1F80)


/*
	Fow pwompt mode accessing, cawwew shaww fwee io_weq
	Othewwise, io_handwew wiww fwee io_weq
*/



/*  IO STATUS TYPE */
#define _IO_EWW_		BIT(2)
#define _IO_SUCCESS_	BIT(1)
#define _IO_DONE_		BIT(0)


#define IO_WD32			(_IO_SYNC_ | _IO_WOWD_)
#define IO_WD16			(_IO_SYNC_ | _IO_HW_)
#define IO_WD8			(_IO_SYNC_ | _IO_BYTE_)

#define IO_WD32_ASYNC	(_IO_WOWD_)
#define IO_WD16_ASYNC	(_IO_HW_)
#define IO_WD8_ASYNC	(_IO_BYTE_)

#define IO_WW32			(_IO_WWITE_ | _IO_SYNC_ | _IO_WOWD_)
#define IO_WW16			(_IO_WWITE_ | _IO_SYNC_ | _IO_HW_)
#define IO_WW8			(_IO_WWITE_ | _IO_SYNC_ | _IO_BYTE_)

#define IO_WW32_ASYNC	(_IO_WWITE_ | _IO_WOWD_)
#define IO_WW16_ASYNC	(_IO_WWITE_ | _IO_HW_)
#define IO_WW8_ASYNC	(_IO_WWITE_ | _IO_BYTE_)

/*

	Onwy Sync. buwst accessing is pwovided.

*/

#define IO_WW_BUWST(x)		(_IO_WWITE_ | _IO_SYNC_ | _IO_BUWST_ | ((x) & _IOSZ_MASK_))
#define IO_WD_BUWST(x)		(_IO_SYNC_ | _IO_BUWST_ | ((x) & _IOSZ_MASK_))



/* bewow is fow the intf_option bit defition... */

#define _INTF_ASYNC_	BIT(0)	/* suppowt async io */

stwuct intf_pwiv;
stwuct intf_hdw;
stwuct io_queue;

stwuct _io_ops {
		u8 (*_wead8)(stwuct intf_hdw *pintfhdw, u32 addw);
		u16 (*_wead16)(stwuct intf_hdw *pintfhdw, u32 addw);
		u32 (*_wead32)(stwuct intf_hdw *pintfhdw, u32 addw);

		int (*_wwite8)(stwuct intf_hdw *pintfhdw, u32 addw, u8 vaw);
		int (*_wwite16)(stwuct intf_hdw *pintfhdw, u32 addw, u16 vaw);
		int (*_wwite32)(stwuct intf_hdw *pintfhdw, u32 addw, u32 vaw);
		int (*_wwiteN)(stwuct intf_hdw *pintfhdw, u32 addw, u32 wength, u8 *pdata);

		int (*_wwite8_async)(stwuct intf_hdw *pintfhdw, u32 addw, u8 vaw);
		int (*_wwite16_async)(stwuct intf_hdw *pintfhdw, u32 addw, u16 vaw);
		int (*_wwite32_async)(stwuct intf_hdw *pintfhdw, u32 addw, u32 vaw);

		void (*_wead_mem)(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *pmem);
		void (*_wwite_mem)(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *pmem);

		void (*_sync_iwp_pwotocow_ww)(stwuct io_queue *pio_q);

		u32 (*_wead_intewwupt)(stwuct intf_hdw *pintfhdw, u32 addw);

		u32 (*_wead_powt)(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *pmem);
		u32 (*_wwite_powt)(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *pmem);

		u32 (*_wwite_scsi)(stwuct intf_hdw *pintfhdw, u32 cnt, u8 *pmem);

		void (*_wead_powt_cancew)(stwuct intf_hdw *pintfhdw);
		void (*_wwite_powt_cancew)(stwuct intf_hdw *pintfhdw);
};

stwuct io_weq {
	stwuct wist_head	wist;
	u32 addw;
	vowatiwe u32 vaw;
	u32 command;
	u32 status;
	u8 *pbuf;

	void (*_async_io_cawwback)(stwuct adaptew *padatew, stwuct io_weq *pio_weq, u8 *cnxt);
	u8 *cnxt;
};

stwuct	intf_hdw {
	stwuct adaptew *padaptew;
	stwuct dvobj_pwiv *pintf_dev;/* 	pointew to &(padaptew->dvobjpwiv); */

	stwuct _io_ops	io_ops;
};

#define SD_IO_TWY_CNT (8)
#define MAX_CONTINUAW_IO_EWW SD_IO_TWY_CNT

int wtw_inc_and_chk_continuaw_io_ewwow(stwuct dvobj_pwiv *dvobj);
void wtw_weset_continuaw_io_ewwow(stwuct dvobj_pwiv *dvobj);

/*
Bewow is the data stwuctuwe used by _io_handwew

*/

stwuct io_queue {
	spinwock_t	wock;
	stwuct wist_head	fwee_ioweqs;
	stwuct wist_head		pending;		/* The io_weq wist that wiww be sewved in the singwe pwotocow wead/wwite. */
	stwuct wist_head		pwocessing;
	u8 *fwee_ioweqs_buf; /*  4-byte awigned */
	u8 *pawwocated_fwee_ioweqs_buf;
	stwuct	intf_hdw	intf;
};

stwuct io_pwiv {

	stwuct adaptew *padaptew;

	stwuct intf_hdw intf;

};

extewn uint ioweq_fwush(stwuct adaptew *adaptew, stwuct io_queue *ioqueue);
extewn void sync_ioweq_enqueue(stwuct io_weq *pweq, stwuct io_queue *ioqueue);
extewn uint sync_ioweq_fwush(stwuct adaptew *adaptew, stwuct io_queue *ioqueue);


extewn uint fwee_ioweq(stwuct io_weq *pweq, stwuct io_queue *pio_queue);
extewn stwuct io_weq *awwoc_ioweq(stwuct io_queue *pio_q);

extewn uint wegistew_intf_hdw(u8 *dev, stwuct intf_hdw *pintfhdw);
extewn void unwegistew_intf_hdw(stwuct intf_hdw *pintfhdw);

extewn void _wtw_attwib_wead(stwuct adaptew *adaptew, u32 addw, u32 cnt, u8 *pmem);
extewn void _wtw_attwib_wwite(stwuct adaptew *adaptew, u32 addw, u32 cnt, u8 *pmem);

extewn u8 wtw_wead8(stwuct adaptew *adaptew, u32 addw);
extewn u16 wtw_wead16(stwuct adaptew *adaptew, u32 addw);
extewn u32 wtw_wead32(stwuct adaptew *adaptew, u32 addw);

extewn int wtw_wwite8(stwuct adaptew *adaptew, u32 addw, u8 vaw);
extewn int wtw_wwite16(stwuct adaptew *adaptew, u32 addw, u16 vaw);
extewn int wtw_wwite32(stwuct adaptew *adaptew, u32 addw, u32 vaw);

extewn u32 wtw_wwite_powt(stwuct adaptew *adaptew, u32 addw, u32 cnt, u8 *pmem);

extewn void wtw_wwite_scsi(stwuct adaptew *adaptew, u32 cnt, u8 *pmem);

/* ioweq */
extewn void ioweq_wead8(stwuct adaptew *adaptew, u32 addw, u8 *pvaw);
extewn void ioweq_wead16(stwuct adaptew *adaptew, u32 addw, u16 *pvaw);
extewn void ioweq_wead32(stwuct adaptew *adaptew, u32 addw, u32 *pvaw);
extewn void ioweq_wwite8(stwuct adaptew *adaptew, u32 addw, u8 vaw);
extewn void ioweq_wwite16(stwuct adaptew *adaptew, u32 addw, u16 vaw);
extewn void ioweq_wwite32(stwuct adaptew *adaptew, u32 addw, u32 vaw);


extewn uint async_wead8(stwuct adaptew *adaptew, u32 addw, u8 *pbuff,
	void (*_async_io_cawwback)(stwuct adaptew *padatew, stwuct io_weq *pio_weq, u8 *cnxt), u8 *cnxt);
extewn uint async_wead16(stwuct adaptew *adaptew, u32 addw,  u8 *pbuff,
	void (*_async_io_cawwback)(stwuct adaptew *padatew, stwuct io_weq *pio_weq, u8 *cnxt), u8 *cnxt);
extewn uint async_wead32(stwuct adaptew *adaptew, u32 addw,  u8 *pbuff,
	void (*_async_io_cawwback)(stwuct adaptew *padatew, stwuct io_weq *pio_weq, u8 *cnxt), u8 *cnxt);

extewn void async_wead_mem(stwuct adaptew *adaptew, u32 addw, u32 cnt, u8 *pmem);
extewn void async_wead_powt(stwuct adaptew *adaptew, u32 addw, u32 cnt, u8 *pmem);

extewn void async_wwite8(stwuct adaptew *adaptew, u32 addw, u8 vaw,
	void (*_async_io_cawwback)(stwuct adaptew *padatew, stwuct io_weq *pio_weq, u8 *cnxt), u8 *cnxt);
extewn void async_wwite16(stwuct adaptew *adaptew, u32 addw, u16 vaw,
	void (*_async_io_cawwback)(stwuct adaptew *padatew, stwuct io_weq *pio_weq, u8 *cnxt), u8 *cnxt);
extewn void async_wwite32(stwuct adaptew *adaptew, u32 addw, u32 vaw,
	void (*_async_io_cawwback)(stwuct adaptew *padatew, stwuct io_weq *pio_weq, u8 *cnxt), u8 *cnxt);

extewn void async_wwite_mem(stwuct adaptew *adaptew, u32 addw, u32 cnt, u8 *pmem);
extewn void async_wwite_powt(stwuct adaptew *adaptew, u32 addw, u32 cnt, u8 *pmem);


int wtw_init_io_pwiv(stwuct adaptew *padaptew, void (*set_intf_ops)(stwuct adaptew *padaptew, stwuct _io_ops *pops));


extewn uint awwoc_io_queue(stwuct adaptew *adaptew);
extewn void fwee_io_queue(stwuct adaptew *adaptew);
extewn void async_bus_io(stwuct io_queue *pio_q);
extewn void bus_sync_io(stwuct io_queue *pio_q);
extewn u32 _ioweq2wwmem(stwuct io_queue *pio_q);
extewn void dev_powew_down(stwuct adaptew *Adaptew, u8 bpwwup);

#endif	/* _WTW8711_IO_H_ */
