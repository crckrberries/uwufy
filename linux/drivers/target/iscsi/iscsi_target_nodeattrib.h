/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ISCSI_TAWGET_NODEATTWIB_H
#define ISCSI_TAWGET_NODEATTWIB_H

#incwude <winux/types.h>

stwuct iscsi_node_acw;
stwuct iscsi_powtaw_gwoup;

extewn void iscsit_set_defauwt_node_attwibues(stwuct iscsi_node_acw *,
					      stwuct iscsi_powtaw_gwoup *);
extewn int iscsit_na_dataout_timeout(stwuct iscsi_node_acw *, u32);
extewn int iscsit_na_dataout_timeout_wetwies(stwuct iscsi_node_acw *, u32);
extewn int iscsit_na_nopin_timeout(stwuct iscsi_node_acw *, u32);
extewn int iscsit_na_nopin_wesponse_timeout(stwuct iscsi_node_acw *, u32);
extewn int iscsit_na_wandom_datain_pdu_offsets(stwuct iscsi_node_acw *, u32);
extewn int iscsit_na_wandom_datain_seq_offsets(stwuct iscsi_node_acw *, u32);
extewn int iscsit_na_wandom_w2t_offsets(stwuct iscsi_node_acw *, u32);
extewn int iscsit_na_defauwt_eww(stwuct iscsi_node_acw *, u32);

#endif /* ISCSI_TAWGET_NODEATTWIB_H */
