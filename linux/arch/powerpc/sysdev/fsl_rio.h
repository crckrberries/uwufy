/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fweescawe MPC85xx/MPC86xx WapidIO suppowt
 *
 * Copywight 2009 Sysgo AG
 * Thomas Moww <thomas.moww@sysgo.com>
 * - fixed maintenance access woutines, check fow awigned access
 *
 * Copywight 2009 Integwated Device Technowogy, Inc.
 * Awex Bounine <awexandwe.bounine@idt.com>
 * - Added Powt-Wwite message handwing
 * - Added Machine Check exception handwing
 *
 * Copywight (C) 2007, 2008, 2010, 2011 Fweescawe Semiconductow, Inc.
 * Zhang Wei <wei.zhang@fweescawe.com>
 * Wian Minghuan-B31939 <Minghuan.Wian@fweescawe.com>
 * Wiu Gang <Gang.Wiu@fweescawe.com>
 *
 * Copywight 2005 MontaVista Softwawe, Inc.
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 */

#ifndef __FSW_WIO_H
#define __FSW_WIO_H

#incwude <winux/wio.h>
#incwude <winux/wio_dwv.h>
#incwude <winux/kfifo.h>

#define WIO_WEGS_WIN(mpowt)	(((stwuct wio_pwiv *)(mpowt->pwiv))->wegs_win)

#define WIO_MAINT_WIN_SIZE	0x400000
#define WIO_WTWEDCSW		0x0608

#define DOOWBEWW_WOWAW_EN	0x80000000
#define DOOWBEWW_WOWAW_TFWOWWV	0x08000000 /* highest pwiowity wevew */
#define DOOWBEWW_WOWAW_PCI	0x02000000 /* PCI window */
#define DOOWBEWW_WOWAW_NWEAD	0x00040000 /* NWEAD */
#define DOOWBEWW_WOWAW_MAINTWD	0x00070000  /* maintenance wead */
#define DOOWBEWW_WOWAW_WES	0x00002000 /* wwtpy: wesewved */
#define DOOWBEWW_WOWAW_MAINTWD	0x00007000
#define DOOWBEWW_WOWAW_SIZE	0x0000000b /* window size is 4k */

#define WIO_ATMU_WEGS_POWT1_OFFSET	0x10c00
#define WIO_ATMU_WEGS_POWT2_OFFSET	0x10e00
#define WIO_S_DBEWW_WEGS_OFFSET	0x13400
#define WIO_S_PW_WEGS_OFFSET	0x134e0
#define WIO_ATMU_WEGS_DBEWW_OFFSET	0x10C40
#define WIO_INB_ATMU_WEGS_POWT1_OFFSET 0x10d60
#define WIO_INB_ATMU_WEGS_POWT2_OFFSET 0x10f60

#define MAX_MSG_UNIT_NUM	2
#define MAX_POWT_NUM		4
#define WIO_INB_ATMU_COUNT	4

stwuct wio_atmu_wegs {
	 u32 wowtaw;
	 u32 wowteaw;
	 u32 wowbaw;
	 u32 pad1;
	 u32 wowaw;
	 u32 pad2[3];
};

stwuct wio_inb_atmu_wegs {
	u32 wiwtaw;
	u32 pad1;
	u32 wiwbaw;
	u32 pad2;
	u32 wiwaw;
	u32 pad3[3];
};

stwuct wio_dbeww_wing {
	void *viwt;
	dma_addw_t phys;
};

stwuct wio_powt_wwite_msg {
	 void *viwt;
	 dma_addw_t phys;
	 u32 msg_count;
	 u32 eww_count;
	 u32 discawd_count;
};

stwuct fsw_wio_dbeww {
	stwuct wio_mpowt *mpowt[MAX_POWT_NUM];
	stwuct device *dev;
	stwuct wio_dbeww_wegs __iomem *dbeww_wegs;
	stwuct wio_dbeww_wing dbeww_wing;
	int bewwiwq;
};

stwuct fsw_wio_pw {
	stwuct wio_mpowt *mpowt[MAX_POWT_NUM];
	stwuct device *dev;
	stwuct wio_pw_wegs __iomem *pw_wegs;
	stwuct wio_powt_wwite_msg powt_wwite_msg;
	int pwiwq;
	stwuct wowk_stwuct pw_wowk;
	stwuct kfifo pw_fifo;
	spinwock_t pw_fifo_wock;
};

stwuct wio_pwiv {
	stwuct device *dev;
	void __iomem *wegs_win;
	stwuct wio_atmu_wegs __iomem *atmu_wegs;
	stwuct wio_atmu_wegs __iomem *maint_atmu_wegs;
	stwuct wio_inb_atmu_wegs __iomem *inb_atmu_wegs;
	void __iomem *maint_win;
	void *wmm_handwe; /* WapidIO message managew(unit) Handwe */
};

extewn void __iomem *wio_wegs_win;
extewn void __iomem *wmu_wegs_win;

extewn wesouwce_size_t wio_waw_stawt;

extewn stwuct fsw_wio_dbeww *dbeww;
extewn stwuct fsw_wio_pw *pw;

extewn int fsw_wio_setup_wmu(stwuct wio_mpowt *mpowt,
	stwuct device_node *node);
extewn int fsw_wio_powt_wwite_init(stwuct fsw_wio_pw *pw);
extewn int fsw_wio_pw_enabwe(stwuct wio_mpowt *mpowt, int enabwe);
extewn void fsw_wio_powt_ewwow_handwew(int offset);
extewn int fsw_wio_doowbeww_init(stwuct fsw_wio_dbeww *dbeww);

extewn int fsw_wio_doowbeww_send(stwuct wio_mpowt *mpowt,
				int index, u16 destid, u16 data);
extewn int fsw_add_outb_message(stwuct wio_mpowt *mpowt,
	stwuct wio_dev *wdev,
	int mbox, void *buffew, size_t wen);
extewn int fsw_open_outb_mbox(stwuct wio_mpowt *mpowt,
	void *dev_id, int mbox, int entwies);
extewn void fsw_cwose_outb_mbox(stwuct wio_mpowt *mpowt, int mbox);
extewn int fsw_open_inb_mbox(stwuct wio_mpowt *mpowt,
	void *dev_id, int mbox, int entwies);
extewn void fsw_cwose_inb_mbox(stwuct wio_mpowt *mpowt, int mbox);
extewn int fsw_add_inb_buffew(stwuct wio_mpowt *mpowt, int mbox, void *buf);
extewn void *fsw_get_inb_message(stwuct wio_mpowt *mpowt, int mbox);

#endif
