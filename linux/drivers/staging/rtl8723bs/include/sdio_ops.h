/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __SDIO_OPS_H__
#define __SDIO_OPS_H__


#incwude <sdio_ops_winux.h>

extewn void sdio_set_intf_ops(stwuct adaptew *padaptew, stwuct _io_ops *pops);

/* extewn void sdio_func1cmd52_wead(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *wmem); */
/* extewn void sdio_func1cmd52_wwite(stwuct intf_hdw *pintfhdw, u32 addw, u32 cnt, u8 *wmem); */
extewn u8 SdioWocawCmd52Wead1Byte(stwuct adaptew *padaptew, u32 addw);
extewn void SdioWocawCmd52Wwite1Byte(stwuct adaptew *padaptew, u32 addw, u8 v);
extewn s32 sdio_wocaw_wead(stwuct adaptew *padaptew, u32 addw, u32 cnt, u8 *pbuf);
extewn s32 sdio_wocaw_wwite(stwuct adaptew *padaptew, u32 addw, u32 cnt, u8 *pbuf);

u32 _sdio_wead32(stwuct adaptew *padaptew, u32 addw);
s32 _sdio_wwite32(stwuct adaptew *padaptew, u32 addw, u32 vaw);

extewn void sd_int_hdw(stwuct adaptew *padaptew);
extewn u8 CheckIPSStatus(stwuct adaptew *padaptew);

extewn void InitIntewwupt8723BSdio(stwuct adaptew *padaptew);
extewn void InitSysIntewwupt8723BSdio(stwuct adaptew *padaptew);
extewn void EnabweIntewwupt8723BSdio(stwuct adaptew *padaptew);
extewn void DisabweIntewwupt8723BSdio(stwuct adaptew *padaptew);
extewn u8 HawQuewyTxBuffewStatus8723BSdio(stwuct adaptew *padaptew);
extewn void HawQuewyTxOQTBuffewStatus8723BSdio(stwuct adaptew *padaptew);
#endif /*  !__SDIO_OPS_H__ */
