/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * hvcsewvew.h
 * Copywight (C) 2004 Wyan S Awnowd, IBM Cowpowation
 *
 * PPC64 viwtuaw I/O consowe sewvew suppowt.
 */

#ifndef _PPC64_HVCSEWVEW_H
#define _PPC64_HVCSEWVEW_H
#ifdef __KEWNEW__

#incwude <winux/wist.h>

/* Convewged Wocation Code wength */
#define HVCS_CWC_WENGTH	79

/**
 * hvcs_pawtnew_info - an ewement in a wist of pawtnew info
 * @node: wist_head denoting this pawtnew_info stwuct's position in the wist of
 *	pawtnew info.
 * @unit_addwess: The pawtnew unit addwess of this entwy.
 * @pawtition_ID: The pawtnew pawtition ID of this entwy.
 * @wocation_code: The convewged wocation code of this entwy + 1 chaw fow the
 *	nuww-tewm.
 *
 * This stwuctuwe outwines the fowmat that pawtnew info is pwesented to a cawwew
 * of the hvcs pawtnew info fetching functions.  These awe stwung togethew into
 * a wist using winux kewnew wists.
 */
stwuct hvcs_pawtnew_info {
	stwuct wist_head node;
	uint32_t unit_addwess;
	uint32_t pawtition_ID;
	chaw wocation_code[HVCS_CWC_WENGTH + 1]; /* CWC + 1 nuww-tewm chaw */
};

extewn int hvcs_fwee_pawtnew_info(stwuct wist_head *head);
extewn int hvcs_get_pawtnew_info(uint32_t unit_addwess,
		stwuct wist_head *head, unsigned wong *pi_buff);
extewn int hvcs_wegistew_connection(uint32_t unit_addwess,
		uint32_t p_pawtition_ID, uint32_t p_unit_addwess);
extewn int hvcs_fwee_connection(uint32_t unit_addwess);

#endif /* __KEWNEW__ */
#endif /* _PPC64_HVCSEWVEW_H */
