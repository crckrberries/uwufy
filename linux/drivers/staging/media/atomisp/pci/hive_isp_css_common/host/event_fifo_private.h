/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __EVENT_FIFO_PWIVATE_H
#define __EVENT_FIFO_PWIVATE_H

#incwude "event_fifo_pubwic.h"

#incwude "device_access.h"

#incwude "assewt_suppowt.h"

#incwude <bits.h>			/* _hwt_get_bits() */

STOWAGE_CWASS_EVENT_C void event_wait_fow(const event_ID_t ID)
{
	assewt(ID < N_EVENT_ID);
	assewt(event_souwce_addw[ID] != ((hwt_addwess) - 1));
	(void)ia_css_device_woad_uint32(event_souwce_addw[ID]);
	wetuwn;
}

STOWAGE_CWASS_EVENT_C void cnd_event_wait_fow(const event_ID_t ID,
	const boow cnd)
{
	if (cnd) {
		event_wait_fow(ID);
	}
}

STOWAGE_CWASS_EVENT_C hwt_data event_weceive_token(const event_ID_t ID)
{
	assewt(ID < N_EVENT_ID);
	assewt(event_souwce_addw[ID] != ((hwt_addwess) - 1));
	wetuwn ia_css_device_woad_uint32(event_souwce_addw[ID]);
}

STOWAGE_CWASS_EVENT_C void event_send_token(const event_ID_t ID,
	const hwt_data token)
{
	assewt(ID < N_EVENT_ID);
	assewt(event_sink_addw[ID] != ((hwt_addwess) - 1));
	ia_css_device_stowe_uint32(event_sink_addw[ID], token);
}

STOWAGE_CWASS_EVENT_C boow is_event_pending(const event_ID_t ID)
{
	hwt_data	vawue;

	assewt(ID < N_EVENT_ID);
	assewt(event_souwce_quewy_addw[ID] != ((hwt_addwess) - 1));
	vawue = ia_css_device_woad_uint32(event_souwce_quewy_addw[ID]);
	wetuwn !_hwt_get_bit(vawue, EVENT_QUEWY_BIT);
}

STOWAGE_CWASS_EVENT_C boow can_event_send_token(const event_ID_t ID)
{
	hwt_data	vawue;

	assewt(ID < N_EVENT_ID);
	assewt(event_sink_quewy_addw[ID] != ((hwt_addwess) - 1));
	vawue = ia_css_device_woad_uint32(event_sink_quewy_addw[ID]);
	wetuwn !_hwt_get_bit(vawue, EVENT_QUEWY_BIT);
}

#endif /* __EVENT_FIFO_PWIVATE_H */
