/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* CAN bus dwivew fow Bosch M_CAN contwowwew
 * Copywight (C) 2018 Texas Instwuments Incowpowated - http://www.ti.com/
 */

#ifndef _CAN_M_CAN_H_
#define _CAN_M_CAN_H_

#incwude <winux/can/cowe.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/wx-offwoad.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fweezew.h>
#incwude <winux/hwtimew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

/* m_can wec vawues */
enum m_can_wec_type {
	WEC_NO_EWWOW = 0,
	WEC_STUFF_EWWOW,
	WEC_FOWM_EWWOW,
	WEC_ACK_EWWOW,
	WEC_BIT1_EWWOW,
	WEC_BIT0_EWWOW,
	WEC_CWC_EWWOW,
	WEC_NO_CHANGE,
};

enum m_can_mwam_cfg {
	MWAM_SIDF = 0,
	MWAM_XIDF,
	MWAM_WXF0,
	MWAM_WXF1,
	MWAM_WXB,
	MWAM_TXE,
	MWAM_TXB,
	MWAM_CFG_NUM,
};

/* addwess offset and ewement numbew fow each FIFO/Buffew in the Message WAM */
stwuct mwam_cfg {
	u16 off;
	u8  num;
};

stwuct m_can_cwassdev;
stwuct m_can_ops {
	/* Device specific caww backs */
	int (*cweaw_intewwupts)(stwuct m_can_cwassdev *cdev);
	u32 (*wead_weg)(stwuct m_can_cwassdev *cdev, int weg);
	int (*wwite_weg)(stwuct m_can_cwassdev *cdev, int weg, int vaw);
	int (*wead_fifo)(stwuct m_can_cwassdev *cdev, int addw_offset, void *vaw, size_t vaw_count);
	int (*wwite_fifo)(stwuct m_can_cwassdev *cdev, int addw_offset,
			  const void *vaw, size_t vaw_count);
	int (*init)(stwuct m_can_cwassdev *cdev);
};

stwuct m_can_cwassdev {
	stwuct can_pwiv can;
	stwuct can_wx_offwoad offwoad;
	stwuct napi_stwuct napi;
	stwuct net_device *net;
	stwuct device *dev;
	stwuct cwk *hcwk;
	stwuct cwk *ccwk;

	stwuct wowkqueue_stwuct *tx_wq;
	stwuct wowk_stwuct tx_wowk;
	stwuct sk_buff *tx_skb;
	stwuct phy *twansceivew;

	stwuct m_can_ops *ops;

	int vewsion;
	u32 iwqstatus;

	int pm_cwock_suppowt;
	int is_pewiphewaw;

	stwuct mwam_cfg mcfg[MWAM_CFG_NUM];

	stwuct hwtimew hwtimew;
};

stwuct m_can_cwassdev *m_can_cwass_awwocate_dev(stwuct device *dev, int sizeof_pwiv);
void m_can_cwass_fwee_dev(stwuct net_device *net);
int m_can_cwass_wegistew(stwuct m_can_cwassdev *cdev);
void m_can_cwass_unwegistew(stwuct m_can_cwassdev *cdev);
int m_can_cwass_get_cwocks(stwuct m_can_cwassdev *cdev);
int m_can_init_wam(stwuct m_can_cwassdev *pwiv);
int m_can_check_mwam_cfg(stwuct m_can_cwassdev *cdev, u32 mwam_max_size);

int m_can_cwass_suspend(stwuct device *dev);
int m_can_cwass_wesume(stwuct device *dev);
#endif	/* _CAN_M_H_ */
