/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ISCSI_TAWGET_DEVICE_H
#define ISCSI_TAWGET_DEVICE_H

stwuct iscsit_cmd;
stwuct iscsit_session;

extewn void iscsit_detewmine_maxcmdsn(stwuct iscsit_session *);
extewn void iscsit_incwement_maxcmdsn(stwuct iscsit_cmd *, stwuct iscsit_session *);

#endif /* ISCSI_TAWGET_DEVICE_H */
