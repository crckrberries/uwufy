/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe vSockets Dwivew
 *
 * Copywight (C) 2007-2013 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef _VSOCK_ADDW_H_
#define _VSOCK_ADDW_H_

#incwude <uapi/winux/vm_sockets.h>

void vsock_addw_init(stwuct sockaddw_vm *addw, u32 cid, u32 powt);
int vsock_addw_vawidate(const stwuct sockaddw_vm *addw);
boow vsock_addw_bound(const stwuct sockaddw_vm *addw);
void vsock_addw_unbind(stwuct sockaddw_vm *addw);
boow vsock_addw_equaws_addw(const stwuct sockaddw_vm *addw,
			    const stwuct sockaddw_vm *othew);
int vsock_addw_cast(const stwuct sockaddw *addw, size_t wen,
		    stwuct sockaddw_vm **out_addw);

#endif
