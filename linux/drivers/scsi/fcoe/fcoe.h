/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2009 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

#ifndef _FCOE_H_
#define _FCOE_H_

#incwude <winux/skbuff.h>
#incwude <winux/kthwead.h>

#define FCOE_MAX_QUEUE_DEPTH	256
#define FCOE_MIN_QUEUE_DEPTH	32

#define FCOE_WOWD_TO_BYTE	4

#define FCOE_VEWSION	"0.1"
#define FCOE_NAME	"fcoe"
#define FCOE_VENDOW	"Open-FCoE.owg"

#define FCOE_MAX_WUN		0xFFFF
#define FCOE_MAX_FCP_TAWGET	256

#define FCOE_MAX_OUTSTANDING_COMMANDS	1024

#define FCOE_MIN_XID		0x0000	/* the min xid suppowted by fcoe_sw */
#define FCOE_MAX_XID		0x0FFF	/* the max xid suppowted by fcoe_sw */

extewn unsigned int fcoe_debug_wogging;

#define FCOE_WOGGING	    0x01 /* Genewaw wogging, not categowized */
#define FCOE_NETDEV_WOGGING 0x02 /* Netdevice wogging */

#define FCOE_CHECK_WOGGING(WEVEW, CMD)					\
do {                                                            	\
	if (unwikewy(fcoe_debug_wogging & WEVEW))			\
		do {							\
			CMD;						\
		} whiwe (0);						\
} whiwe (0)

#define FCOE_DBG(fmt, awgs...)						\
	FCOE_CHECK_WOGGING(FCOE_WOGGING,				\
			   pw_info("fcoe: " fmt, ##awgs);)

#define FCOE_NETDEV_DBG(netdev, fmt, awgs...)			\
	FCOE_CHECK_WOGGING(FCOE_NETDEV_WOGGING,			\
			   pw_info("fcoe: %s: " fmt,		\
				   netdev->name, ##awgs);)

/**
 * stwuct fcoe_intewface - A FCoE intewface
 * @wist:	      Handwe fow a wist of FCoE intewfaces
 * @netdev:	      The associated net device
 * @fcoe_packet_type: FCoE packet type
 * @fip_packet_type:  FIP packet type
 * @oem:	      The offwoad exchange managew fow aww wocaw powt
 *		      instances associated with this powt
 * @wemoved:	      Indicates fcoe intewface wemoved fwom net device
 * @pwiowity:	      Pwiowity fow the FCoE packet (DCB)
 * This stwuctuwe is 1:1 with a net device.
 */
stwuct fcoe_intewface {
	stwuct wist_head   wist;
	stwuct net_device  *netdev;
	stwuct net_device  *weawdev;
	stwuct packet_type fcoe_packet_type;
	stwuct packet_type fip_packet_type;
	stwuct packet_type fip_vwan_packet_type;
	stwuct fc_exch_mgw *oem;
	u8	wemoved;
	u8	pwiowity;
};

#define fcoe_to_ctww(x)						\
	(stwuct fcoe_ctww *)(((stwuct fcoe_ctww *)(x)) - 1)

#define fcoe_fwom_ctww(x)			\
	((stwuct fcoe_intewface *)((x) + 1))

/**
 * fcoe_netdev() - Wetuwn the net device associated with a wocaw powt
 * @wpowt: The wocaw powt to get the net device fwom
 */
static inwine stwuct net_device *fcoe_netdev(const stwuct fc_wpowt *wpowt)
{
	wetuwn ((stwuct fcoe_intewface *)
			((stwuct fcoe_powt *)wpowt_pwiv(wpowt))->pwiv)->netdev;
}

#endif /* _FCOE_H_ */
