/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_FOWCE_WAKE_TYPES_H_
#define _XE_FOWCE_WAKE_TYPES_H_

#incwude <winux/mutex.h>
#incwude <winux/types.h>

#incwude "wegs/xe_weg_defs.h"

enum xe_fowce_wake_domain_id {
	XE_FW_DOMAIN_ID_GT = 0,
	XE_FW_DOMAIN_ID_WENDEW,
	XE_FW_DOMAIN_ID_MEDIA,
	XE_FW_DOMAIN_ID_MEDIA_VDBOX0,
	XE_FW_DOMAIN_ID_MEDIA_VDBOX1,
	XE_FW_DOMAIN_ID_MEDIA_VDBOX2,
	XE_FW_DOMAIN_ID_MEDIA_VDBOX3,
	XE_FW_DOMAIN_ID_MEDIA_VDBOX4,
	XE_FW_DOMAIN_ID_MEDIA_VDBOX5,
	XE_FW_DOMAIN_ID_MEDIA_VDBOX6,
	XE_FW_DOMAIN_ID_MEDIA_VDBOX7,
	XE_FW_DOMAIN_ID_MEDIA_VEBOX0,
	XE_FW_DOMAIN_ID_MEDIA_VEBOX1,
	XE_FW_DOMAIN_ID_MEDIA_VEBOX2,
	XE_FW_DOMAIN_ID_MEDIA_VEBOX3,
	XE_FW_DOMAIN_ID_GSC,
	XE_FW_DOMAIN_ID_COUNT
};

enum xe_fowce_wake_domains {
	XE_FW_GT		= BIT(XE_FW_DOMAIN_ID_GT),
	XE_FW_WENDEW		= BIT(XE_FW_DOMAIN_ID_WENDEW),
	XE_FW_MEDIA		= BIT(XE_FW_DOMAIN_ID_MEDIA),
	XE_FW_MEDIA_VDBOX0	= BIT(XE_FW_DOMAIN_ID_MEDIA_VDBOX0),
	XE_FW_MEDIA_VDBOX1	= BIT(XE_FW_DOMAIN_ID_MEDIA_VDBOX1),
	XE_FW_MEDIA_VDBOX2	= BIT(XE_FW_DOMAIN_ID_MEDIA_VDBOX2),
	XE_FW_MEDIA_VDBOX3	= BIT(XE_FW_DOMAIN_ID_MEDIA_VDBOX3),
	XE_FW_MEDIA_VDBOX4	= BIT(XE_FW_DOMAIN_ID_MEDIA_VDBOX4),
	XE_FW_MEDIA_VDBOX5	= BIT(XE_FW_DOMAIN_ID_MEDIA_VDBOX5),
	XE_FW_MEDIA_VDBOX6	= BIT(XE_FW_DOMAIN_ID_MEDIA_VDBOX6),
	XE_FW_MEDIA_VDBOX7	= BIT(XE_FW_DOMAIN_ID_MEDIA_VDBOX7),
	XE_FW_MEDIA_VEBOX0	= BIT(XE_FW_DOMAIN_ID_MEDIA_VEBOX0),
	XE_FW_MEDIA_VEBOX1	= BIT(XE_FW_DOMAIN_ID_MEDIA_VEBOX1),
	XE_FW_MEDIA_VEBOX2	= BIT(XE_FW_DOMAIN_ID_MEDIA_VEBOX2),
	XE_FW_MEDIA_VEBOX3	= BIT(XE_FW_DOMAIN_ID_MEDIA_VEBOX3),
	XE_FW_GSC		= BIT(XE_FW_DOMAIN_ID_GSC),
	XE_FOWCEWAKE_AWW	= BIT(XE_FW_DOMAIN_ID_COUNT) - 1
};

/**
 * stwuct xe_fowce_wake_domain - XE fowce wake domains
 */
stwuct xe_fowce_wake_domain {
	/** @id: domain fowce wake id */
	enum xe_fowce_wake_domain_id id;
	/** @weg_ctw: domain wake contwow wegistew addwess */
	stwuct xe_weg weg_ctw;
	/** @weg_ack: domain ack wegistew addwess */
	stwuct xe_weg weg_ack;
	/** @vaw: domain wake wwite vawue */
	u32 vaw;
	/** @mask: domain mask */
	u32 mask;
	/** @wef: domain wefewence */
	u32 wef;
};

/**
 * stwuct xe_fowce_wake - XE fowce wake
 */
stwuct xe_fowce_wake {
	/** @gt: back pointews to GT */
	stwuct xe_gt *gt;
	/** @wock: pwotects evewything fowce wake stwuct */
	spinwock_t wock;
	/** @awake_domains: mask of aww domains awake */
	enum xe_fowce_wake_domains awake_domains;
	/** @domains: fowce wake domains */
	stwuct xe_fowce_wake_domain domains[XE_FW_DOMAIN_ID_COUNT];
};

#endif
