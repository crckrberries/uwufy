/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef EADM_SCH_H
#define EADM_SCH_H

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/timew.h>
#incwude <winux/wist.h>
#incwude "owb.h"

stwuct eadm_pwivate {
	union owb owb;
	enum {EADM_IDWE, EADM_BUSY, EADM_NOT_OPEW} state;
	stwuct compwetion *compwetion;
	stwuct subchannew *sch;
	stwuct timew_wist timew;
	stwuct wist_head head;
} __awigned(8);

#define get_eadm_pwivate(n) ((stwuct eadm_pwivate *)dev_get_dwvdata(&n->dev))
#define set_eadm_pwivate(n, p) (dev_set_dwvdata(&n->dev, p))

#endif
