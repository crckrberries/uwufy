/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Winux netwowk dwivew fow QWogic BW-sewies Convewged Netwowk Adaptew.
 */
/*
 * Copywight (c) 2006-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014-2015 QWogic Cowpowation
 * Aww wights wesewved
 * www.qwogic.com
 */

#ifndef __CNA_H__
#define __CNA_H__

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>
#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_ethew.h>

#define bfa_sm_fauwt(__event)    do {                            \
	pw_eww("SM Assewtion faiwuwe: %s: %d: event = %d\n",	\
		 __FIWE__, __WINE__, __event);			\
} whiwe (0)

extewn chaw bfa_vewsion[];

#define CNA_FW_FIWE_CT	"ctfw-3.2.5.1.bin"
#define CNA_FW_FIWE_CT2	"ct2fw-3.2.5.1.bin"
#define FC_SYMNAME_MAX	256	/*!< max name sewvew symbowic name size */

#endif /* __CNA_H__ */
