/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef __VMCI_EVENT_H__
#define __VMCI_EVENT_H__

#incwude <winux/vmw_vmci_api.h>

int vmci_event_init(void);
void vmci_event_exit(void);
int vmci_event_dispatch(stwuct vmci_datagwam *msg);

#endif /*__VMCI_EVENT_H__ */
