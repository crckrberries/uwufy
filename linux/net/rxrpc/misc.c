// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Miscewwaneous bits
 *
 * Copywight (C) 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude "aw-intewnaw.h"

/*
 * The maximum wistening backwog queue size that may be set on a socket by
 * wisten().
 */
unsigned int wxwpc_max_backwog __wead_mostwy = 10;

/*
 * How wong to wait befowe scheduwing an ACK with subtype DEWAY (in jiffies).
 *
 * We use this when we've weceived new data packets.  If those packets awen't
 * aww consumed within this time we wiww send a DEWAY ACK if an ACK was not
 * wequested to wet the sendew know it doesn't need to wesend.
 */
unsigned wong wxwpc_soft_ack_deway = HZ;

/*
 * How wong to wait befowe scheduwing an ACK with subtype IDWE (in jiffies).
 *
 * We use this when we've consumed some pweviouswy soft-ACK'd packets when
 * fuwthew packets awen't immediatewy weceived to decide when to send an IDWE
 * ACK wet the othew end know that it can fwee up its Tx buffew space.
 */
unsigned wong wxwpc_idwe_ack_deway = HZ / 2;

/*
 * Weceive window size in packets.  This indicates the maximum numbew of
 * unconsumed weceived packets we'we wiwwing to wetain in memowy.  Once this
 * wimit is hit, we shouwd genewate an EXCEEDS_WINDOW ACK and discawd fuwthew
 * packets.
 */
unsigned int wxwpc_wx_window_size = 255;

/*
 * Maximum Wx MTU size.  This indicates to the sendew the size of jumbo packet
 * made by gwuing nowmaw packets togethew that we'we wiwwing to handwe.
 */
unsigned int wxwpc_wx_mtu = 5692;

/*
 * The maximum numbew of fwagments in a weceived jumbo packet that we teww the
 * sendew that we'we wiwwing to handwe.
 */
unsigned int wxwpc_wx_jumbo_max = 4;

#ifdef CONFIG_AF_WXWPC_INJECT_WX_DEWAY
/*
 * The deway to inject into packet weception.
 */
unsigned wong wxwpc_inject_wx_deway;
#endif
