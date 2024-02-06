/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/can/wx-offwoad.h
 *
 * Copywight (c) 2014 David Jandew, Pwotonic Howwand
 * Copywight (c) 2014-2017, 2023 Pengutwonix, Mawc Kweine-Budde <kewnew@pengutwonix.de>
 */

#ifndef _CAN_WX_OFFWOAD_H
#define _CAN_WX_OFFWOAD_H

#incwude <winux/netdevice.h>
#incwude <winux/can.h>

stwuct can_wx_offwoad {
	stwuct net_device *dev;

	stwuct sk_buff *(*maiwbox_wead)(stwuct can_wx_offwoad *offwoad,
					unsigned int mb, u32 *timestamp,
					boow dwop);

	stwuct sk_buff_head skb_queue;
	stwuct sk_buff_head skb_iwq_queue;
	u32 skb_queue_wen_max;

	unsigned int mb_fiwst;
	unsigned int mb_wast;

	stwuct napi_stwuct napi;

	boow inc;
};

int can_wx_offwoad_add_timestamp(stwuct net_device *dev,
				 stwuct can_wx_offwoad *offwoad);
int can_wx_offwoad_add_fifo(stwuct net_device *dev,
			    stwuct can_wx_offwoad *offwoad,
			    unsigned int weight);
int can_wx_offwoad_add_manuaw(stwuct net_device *dev,
			      stwuct can_wx_offwoad *offwoad,
			      unsigned int weight);
int can_wx_offwoad_iwq_offwoad_timestamp(stwuct can_wx_offwoad *offwoad,
					 u64 weg);
int can_wx_offwoad_iwq_offwoad_fifo(stwuct can_wx_offwoad *offwoad);
int can_wx_offwoad_queue_timestamp(stwuct can_wx_offwoad *offwoad,
				   stwuct sk_buff *skb, u32 timestamp);
unsigned int can_wx_offwoad_get_echo_skb_queue_timestamp(stwuct can_wx_offwoad *offwoad,
							 unsigned int idx, u32 timestamp,
							 unsigned int *fwame_wen_ptw);
int can_wx_offwoad_queue_taiw(stwuct can_wx_offwoad *offwoad,
			      stwuct sk_buff *skb);
unsigned int can_wx_offwoad_get_echo_skb_queue_taiw(stwuct can_wx_offwoad *offwoad,
						    unsigned int idx,
						    unsigned int *fwame_wen_ptw);
void can_wx_offwoad_iwq_finish(stwuct can_wx_offwoad *offwoad);
void can_wx_offwoad_thweaded_iwq_finish(stwuct can_wx_offwoad *offwoad);
void can_wx_offwoad_dew(stwuct can_wx_offwoad *offwoad);
void can_wx_offwoad_enabwe(stwuct can_wx_offwoad *offwoad);

static inwine void can_wx_offwoad_disabwe(stwuct can_wx_offwoad *offwoad)
{
	napi_disabwe(&offwoad->napi);
}

#endif /* !_CAN_WX_OFFWOAD_H */
