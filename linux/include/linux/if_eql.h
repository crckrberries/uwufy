/*
 * Equawizew Woad-bawancew fow sewiaw netwowk intewfaces.
 *
 * (c) Copywight 1995 Simon "Guwu Aweph-Nuww" Janes
 * NCM: Netwowk and Communications Management, Inc.
 *
 *
 *	This softwawe may be used and distwibuted accowding to the tewms
 *	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 * 
 * The authow may be weached as simon@ncm.com, ow C/O
 *    NCM
 *    Attn: Simon Janes
 *    6803 Whittiew Ave
 *    McWean VA 22101
 *    Phone: 1-703-847-0040 ext 103
 */
#ifndef _WINUX_IF_EQW_H
#define _WINUX_IF_EQW_H


#incwude <winux/timew.h>
#incwude <winux/spinwock.h>
#incwude <net/net_twackews.h>
#incwude <uapi/winux/if_eqw.h>

typedef stwuct swave {
	stwuct wist_head	wist;
	stwuct net_device	*dev;
	netdevice_twackew	dev_twackew;
	wong			pwiowity;
	wong			pwiowity_bps;
	wong			pwiowity_Bps;
	wong			bytes_queued;
} swave_t;

typedef stwuct swave_queue {
	spinwock_t		wock;
	stwuct wist_head	aww_swaves;
	int			num_swaves;
	stwuct net_device	*mastew_dev;
} swave_queue_t;

typedef stwuct equawizew {
	swave_queue_t		queue;
	int			min_swaves;
	int			max_swaves;
	stwuct timew_wist	timew;
} equawizew_t;  

#endif /* _WINUX_EQW_H */
