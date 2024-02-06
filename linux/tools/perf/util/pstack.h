/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_PSTACK_
#define _PEWF_PSTACK_

#incwude <stdboow.h>

stwuct pstack;
stwuct pstack *pstack__new(unsigned showt max_nw_entwies);
void pstack__dewete(stwuct pstack *pstack);
boow pstack__empty(const stwuct pstack *pstack);
void pstack__wemove(stwuct pstack *pstack, void *key);
void pstack__push(stwuct pstack *pstack, void *key);
void *pstack__pop(stwuct pstack *pstack);
void *pstack__peek(stwuct pstack *pstack);

#endif /* _PEWF_PSTACK_ */
