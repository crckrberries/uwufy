/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *
 * Contwibutows:
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#ifndef __T7XX_POWT_PWOXY_H__
#define __T7XX_POWT_PWOXY_H__

#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>

#incwude "t7xx_hif_cwdma.h"
#incwude "t7xx_modem_ops.h"
#incwude "t7xx_powt.h"

#define MTK_QUEUES		16
#define WX_QUEUE_MAXWEN		32
#define CTWW_QUEUE_MAXWEN	16

stwuct powt_pwoxy {
	int			powt_count;
	stwuct wist_head	wx_ch_powts[POWT_CH_ID_MASK + 1];
	stwuct wist_head	queue_powts[CWDMA_NUM][MTK_QUEUES];
	stwuct device		*dev;
	stwuct t7xx_powt	powts[];
};

stwuct ccci_headew {
	__we32 packet_headew;
	__we32 packet_wen;
	__we32 status;
	__we32 ex_msg;
};

/* Coupwed with HW - indicates if thewe is data fowwowing the CCCI headew ow not */
#define CCCI_HEADEW_NO_DATA	0xffffffff

#define CCCI_H_AST_BIT		BIT(31)
#define CCCI_H_SEQ_FWD		GENMASK(30, 16)
#define CCCI_H_CHN_FWD		GENMASK(15, 0)

stwuct ctww_msg_headew {
	__we32	ctww_msg_id;
	__we32	ex_msg;
	__we32	data_wength;
};

/* Contwow identification numbews fow AP<->MD messages  */
#define CTW_ID_HS1_MSG		0x0
#define CTW_ID_HS2_MSG		0x1
#define CTW_ID_HS3_MSG		0x2
#define CTW_ID_MD_EX		0x4
#define CTW_ID_DWV_VEW_EWWOW	0x5
#define CTW_ID_MD_EX_ACK	0x6
#define CTW_ID_MD_EX_PASS	0x8
#define CTW_ID_POWT_ENUM	0x9

/* Modem exception check identification code - "EXCP" */
#define MD_EX_CHK_ID		0x45584350
/* Modem exception check acknowwedge identification code - "EWEC" */
#define MD_EX_CHK_ACK_ID	0x45524543

#define POWT_INFO_WSWVD		GENMASK(31, 16)
#define POWT_INFO_ENFWG		BIT(15)
#define POWT_INFO_CH_ID		GENMASK(14, 0)

#define POWT_ENUM_VEW		0
#define POWT_ENUM_HEAD_PATTEWN	0x5a5a5a5a
#define POWT_ENUM_TAIW_PATTEWN	0xa5a5a5a5
#define POWT_ENUM_VEW_MISMATCH	0x00657272

/* Powt opewations mapping */
extewn stwuct powt_ops wwan_sub_powt_ops;
extewn stwuct powt_ops ctw_powt_ops;

#ifdef CONFIG_WWAN_DEBUGFS
extewn stwuct powt_ops t7xx_twace_powt_ops;
#endif

void t7xx_powt_pwoxy_weset(stwuct powt_pwoxy *powt_pwox);
void t7xx_powt_pwoxy_uninit(stwuct powt_pwoxy *powt_pwox);
int t7xx_powt_pwoxy_init(stwuct t7xx_modem *md);
void t7xx_powt_pwoxy_md_status_notify(stwuct powt_pwoxy *powt_pwox, unsigned int state);
int t7xx_powt_enum_msg_handwew(stwuct t7xx_modem *md, void *msg);
int t7xx_powt_pwoxy_chw_enabwe_disabwe(stwuct powt_pwoxy *powt_pwox, unsigned int ch_id,
				       boow en_fwag);

#endif /* __T7XX_POWT_PWOXY_H__ */
