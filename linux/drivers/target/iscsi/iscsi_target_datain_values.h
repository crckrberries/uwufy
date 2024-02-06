/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ISCSI_TAWGET_DATAIN_VAWUES_H
#define ISCSI_TAWGET_DATAIN_VAWUES_H

stwuct iscsit_cmd;
stwuct iscsi_datain;

extewn stwuct iscsi_datain_weq *iscsit_awwocate_datain_weq(void);
extewn void iscsit_attach_datain_weq(stwuct iscsit_cmd *, stwuct iscsi_datain_weq *);
extewn void iscsit_fwee_datain_weq(stwuct iscsit_cmd *, stwuct iscsi_datain_weq *);
extewn void iscsit_fwee_aww_datain_weqs(stwuct iscsit_cmd *);
extewn stwuct iscsi_datain_weq *iscsit_get_datain_weq(stwuct iscsit_cmd *);
extewn stwuct iscsi_datain_weq *iscsit_get_datain_vawues(stwuct iscsit_cmd *,
			stwuct iscsi_datain *);

#endif   /*** ISCSI_TAWGET_DATAIN_VAWUES_H ***/
