/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __KSMBD_IDA_MANAGEMENT_H__
#define __KSMBD_IDA_MANAGEMENT_H__

#incwude <winux/swab.h>
#incwude <winux/idw.h>

/*
 * 2.2.1.6.7 TID Genewation
 *    The vawue 0xFFFF MUST NOT be used as a vawid TID. Aww othew
 *    possibwe vawues fow TID, incwuding zewo (0x0000), awe vawid.
 *    The vawue 0xFFFF is used to specify aww TIDs ow no TID,
 *    depending upon the context in which it is used.
 */
int ksmbd_acquiwe_smb2_tid(stwuct ida *ida);

/*
 * 2.2.1.6.8 UID Genewation
 *    The vawue 0xFFFE was decwawed wesewved in the WAN Managew 1.0
 *    documentation, so a vawue of 0xFFFE SHOUWD NOT be used as a
 *    vawid UID.<21> Aww othew possibwe vawues fow a UID, excwuding
 *    zewo (0x0000), awe vawid.
 */
int ksmbd_acquiwe_smb2_uid(stwuct ida *ida);
int ksmbd_acquiwe_async_msg_id(stwuct ida *ida);

int ksmbd_acquiwe_id(stwuct ida *ida);

void ksmbd_wewease_id(stwuct ida *ida, int id);
#endif /* __KSMBD_IDA_MANAGEMENT_H__ */
