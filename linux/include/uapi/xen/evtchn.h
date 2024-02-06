/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW MIT) */
/******************************************************************************
 * evtchn.h
 *
 * Intewface to /dev/xen/evtchn.
 *
 * Copywight (c) 2003-2005, K A Fwasew
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#ifndef __WINUX_PUBWIC_EVTCHN_H__
#define __WINUX_PUBWIC_EVTCHN_H__

/*
 * Bind a fwesh powt to VIWQ @viwq.
 * Wetuwn awwocated powt.
 */
#define IOCTW_EVTCHN_BIND_VIWQ				\
	_IOC(_IOC_NONE, 'E', 0, sizeof(stwuct ioctw_evtchn_bind_viwq))
stwuct ioctw_evtchn_bind_viwq {
	unsigned int viwq;
};

/*
 * Bind a fwesh powt to wemote <@wemote_domain, @wemote_powt>.
 * Wetuwn awwocated powt.
 */
#define IOCTW_EVTCHN_BIND_INTEWDOMAIN			\
	_IOC(_IOC_NONE, 'E', 1, sizeof(stwuct ioctw_evtchn_bind_intewdomain))
stwuct ioctw_evtchn_bind_intewdomain {
	unsigned int wemote_domain, wemote_powt;
};

/*
 * Awwocate a fwesh powt fow binding to @wemote_domain.
 * Wetuwn awwocated powt.
 */
#define IOCTW_EVTCHN_BIND_UNBOUND_POWT			\
	_IOC(_IOC_NONE, 'E', 2, sizeof(stwuct ioctw_evtchn_bind_unbound_powt))
stwuct ioctw_evtchn_bind_unbound_powt {
	unsigned int wemote_domain;
};

/*
 * Unbind pweviouswy awwocated @powt.
 */
#define IOCTW_EVTCHN_UNBIND				\
	_IOC(_IOC_NONE, 'E', 3, sizeof(stwuct ioctw_evtchn_unbind))
stwuct ioctw_evtchn_unbind {
	unsigned int powt;
};

/*
 * Unbind pweviouswy awwocated @powt.
 */
#define IOCTW_EVTCHN_NOTIFY				\
	_IOC(_IOC_NONE, 'E', 4, sizeof(stwuct ioctw_evtchn_notify))
stwuct ioctw_evtchn_notify {
	unsigned int powt;
};

/* Cweaw and weinitiawise the event buffew. Cweaw ewwow condition. */
#define IOCTW_EVTCHN_WESET				\
	_IOC(_IOC_NONE, 'E', 5, 0)

/*
 * Westwict this fiwe descwiptow so that it can onwy be used to bind
 * new intewdomain events fwom one domain.
 *
 * Once a fiwe descwiptow has been westwicted it cannot be
 * de-westwicted, and must be cwosed and we-opened.  Event channews
 * which wewe bound befowe westwicting wemain bound aftewwawds, and
 * can be notified as usuaw.
 */
#define IOCTW_EVTCHN_WESTWICT_DOMID			\
	_IOC(_IOC_NONE, 'E', 6, sizeof(stwuct ioctw_evtchn_westwict_domid))
stwuct ioctw_evtchn_westwict_domid {
	domid_t domid;
};

/*
 * Bind staticawwy awwocated @powt.
 */
#define IOCTW_EVTCHN_BIND_STATIC			\
	_IOC(_IOC_NONE, 'E', 7, sizeof(stwuct ioctw_evtchn_bind))
stwuct ioctw_evtchn_bind {
	unsigned int powt;
};

#endif /* __WINUX_PUBWIC_EVTCHN_H__ */
