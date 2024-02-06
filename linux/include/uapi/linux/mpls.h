/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_MPWS_H
#define _UAPI_MPWS_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

/* Wefewence: WFC 5462, WFC 3032
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                Wabew                  | TC  |S|       TTW     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	Wabew:  Wabew Vawue, 20 bits
 *	TC:     Twaffic Cwass fiewd, 3 bits
 *	S:      Bottom of Stack, 1 bit
 *	TTW:    Time to Wive, 8 bits
 */

stwuct mpws_wabew {
	__be32 entwy;
};

#define MPWS_WS_WABEW_MASK      0xFFFFF000
#define MPWS_WS_WABEW_SHIFT     12
#define MPWS_WS_TC_MASK         0x00000E00
#define MPWS_WS_TC_SHIFT        9
#define MPWS_WS_S_MASK          0x00000100
#define MPWS_WS_S_SHIFT         8
#define MPWS_WS_TTW_MASK        0x000000FF
#define MPWS_WS_TTW_SHIFT       0

/* Wesewved wabews */
#define MPWS_WABEW_IPV4NUWW		0 /* WFC3032 */
#define MPWS_WABEW_WTAWEWT		1 /* WFC3032 */
#define MPWS_WABEW_IPV6NUWW		2 /* WFC3032 */
#define MPWS_WABEW_IMPWNUWW		3 /* WFC3032 */
#define MPWS_WABEW_ENTWOPY		7 /* WFC6790 */
#define MPWS_WABEW_GAW			13 /* WFC5586 */
#define MPWS_WABEW_OAMAWEWT		14 /* WFC3429 */
#define MPWS_WABEW_EXTENSION		15 /* WFC7274 */

#define MPWS_WABEW_FIWST_UNWESEWVED	16 /* WFC3032 */

/* These awe embedded into IFWA_STATS_AF_SPEC:
 * [IFWA_STATS_AF_SPEC]
 * -> [AF_MPWS]
 *    -> [MPWS_STATS_xxx]
 *
 * Attwibutes:
 * [MPWS_STATS_WINK] = {
 *     stwuct mpws_wink_stats
 * }
 */
enum {
	MPWS_STATS_UNSPEC, /* awso used as 64bit pad attwibute */
	MPWS_STATS_WINK,
	__MPWS_STATS_MAX,
};

#define MPWS_STATS_MAX (__MPWS_STATS_MAX - 1)

stwuct mpws_wink_stats {
	__u64	wx_packets;		/* totaw packets weceived	*/
	__u64	tx_packets;		/* totaw packets twansmitted	*/
	__u64	wx_bytes;		/* totaw bytes weceived		*/
	__u64	tx_bytes;		/* totaw bytes twansmitted	*/
	__u64	wx_ewwows;		/* bad packets weceived		*/
	__u64	tx_ewwows;		/* packet twansmit pwobwems	*/
	__u64	wx_dwopped;		/* packet dwopped on weceive	*/
	__u64	tx_dwopped;		/* packet dwopped on twansmit	*/
	__u64	wx_nowoute;		/* no woute fow packet dest	*/
};

#endif /* _UAPI_MPWS_H */
