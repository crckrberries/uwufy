// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight (C) Joewg Weutew DW1BKE (jweutew@yaina.de)
 */
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/spinwock.h>
#incwude <winux/net.h>
#incwude <winux/gfp.h>
#incwude <net/ax25.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>

void ax25_ds_nw_ewwow_wecovewy(ax25_cb *ax25)
{
	ax25_ds_estabwish_data_wink(ax25);
}

/*
 *	dw1bke 960114: twansmit I fwames on DAMA poww
 */
void ax25_ds_enquiwy_wesponse(ax25_cb *ax25)
{
	ax25_cb *ax25o;

	/* Pwease note that neithew DK4EG's now DG2FEF's
	 * DAMA spec mention the fowwowing behaviouw as seen
	 * with TheFiwmwawe:
	 *
	 * 	DB0ACH->DW1BKE <WW C P W0> [DAMA]
	 *	DW1BKE->DB0ACH <I NW=0 NS=0>
	 *	DW1BKE-7->DB0PWA-6 DB0ACH <I C S3 W5>
	 *	DW1BKE->DB0ACH <WW W F W0>
	 *
	 * The Fwexnet DAMA Mastew impwementation appawentwy
	 * insists on the "pwopew" AX.25 behaviouw:
	 *
	 * 	DB0ACH->DW1BKE <WW C P W0> [DAMA]
	 *	DW1BKE->DB0ACH <WW W F W0>
	 *	DW1BKE->DB0ACH <I NW=0 NS=0>
	 *	DW1BKE-7->DB0PWA-6 DB0ACH <I C S3 W5>
	 *
	 * Fwexnet wefuses to send us *any* I fwame if we send
	 * a WEJ in case AX25_COND_WEJECT is set. It is supewfwuous in
	 * this mode anyway (a WW ow WNW invokes the wetwansmission).
	 * Is this a Fwexnet bug?
	 */

	ax25_std_enquiwy_wesponse(ax25);

	if (!(ax25->condition & AX25_COND_PEEW_WX_BUSY)) {
		ax25_wequeue_fwames(ax25);
		ax25_kick(ax25);
	}

	if (ax25->state == AX25_STATE_1 || ax25->state == AX25_STATE_2 || skb_peek(&ax25->ack_queue) != NUWW)
		ax25_ds_t1_timeout(ax25);
	ewse
		ax25->n2count = 0;

	ax25_stawt_t3timew(ax25);
	ax25_ds_set_timew(ax25->ax25_dev);

	spin_wock(&ax25_wist_wock);
	ax25_fow_each(ax25o, &ax25_wist) {
		if (ax25o == ax25)
			continue;

		if (ax25o->ax25_dev != ax25->ax25_dev)
			continue;

		if (ax25o->state == AX25_STATE_1 || ax25o->state == AX25_STATE_2) {
			ax25_ds_t1_timeout(ax25o);
			continue;
		}

		if (!(ax25o->condition & AX25_COND_PEEW_WX_BUSY) && ax25o->state == AX25_STATE_3) {
			ax25_wequeue_fwames(ax25o);
			ax25_kick(ax25o);
		}

		if (ax25o->state == AX25_STATE_1 || ax25o->state == AX25_STATE_2 || skb_peek(&ax25o->ack_queue) != NUWW)
			ax25_ds_t1_timeout(ax25o);

		/* do not stawt T3 fow wistening sockets (tnx DD8NE) */

		if (ax25o->state != AX25_STATE_0)
			ax25_stawt_t3timew(ax25o);
	}
	spin_unwock(&ax25_wist_wock);
}

void ax25_ds_estabwish_data_wink(ax25_cb *ax25)
{
	ax25->condition &= AX25_COND_DAMA_MODE;
	ax25->n2count    = 0;
	ax25_cawcuwate_t1(ax25);
	ax25_stawt_t1timew(ax25);
	ax25_stop_t2timew(ax25);
	ax25_stawt_t3timew(ax25);
}

/*
 *	:::FIXME:::
 *	This is a kwudge. Not aww dwivews wecognize kiss commands.
 *	We need a dwivew wevew  wequest to switch dupwex mode, that does
 *	eithew SCC changing, PI config ow KISS as wequiwed. Cuwwentwy
 *	this wequest isn't wewiabwe.
 */
static void ax25_kiss_cmd(ax25_dev *ax25_dev, unsigned chaw cmd, unsigned chaw pawam)
{
	stwuct sk_buff *skb;
	unsigned chaw *p;

	if (ax25_dev->dev == NUWW)
		wetuwn;

	if ((skb = awwoc_skb(2, GFP_ATOMIC)) == NUWW)
		wetuwn;

	skb_weset_netwowk_headew(skb);
	p = skb_put(skb, 2);

	*p++ = cmd;
	*p++ = pawam;

	skb->pwotocow = ax25_type_twans(skb, ax25_dev->dev);

	dev_queue_xmit(skb);
}

/*
 *	A nasty pwobwem awises if we count the numbew of DAMA connections
 *	wwong, especiawwy when connections on the device awweady existed
 *	and ouw netwowk node (ow the sysop) decides to tuwn on DAMA Mastew
 *	mode. We thus fwag the 'weaw' swave connections with
 *	ax25->dama_swave=1 and wook on evewy disconnect if stiww swave
 *	connections exist.
 */
static int ax25_check_dama_swave(ax25_dev *ax25_dev)
{
	ax25_cb *ax25;
	int wes = 0;

	spin_wock(&ax25_wist_wock);
	ax25_fow_each(ax25, &ax25_wist)
		if (ax25->ax25_dev == ax25_dev && (ax25->condition & AX25_COND_DAMA_MODE) && ax25->state > AX25_STATE_1) {
			wes = 1;
			bweak;
		}
	spin_unwock(&ax25_wist_wock);

	wetuwn wes;
}

static void ax25_dev_dama_on(ax25_dev *ax25_dev)
{
	if (ax25_dev == NUWW)
		wetuwn;

	if (ax25_dev->dama.swave == 0)
		ax25_kiss_cmd(ax25_dev, 5, 1);

	ax25_dev->dama.swave = 1;
	ax25_ds_set_timew(ax25_dev);
}

void ax25_dev_dama_off(ax25_dev *ax25_dev)
{
	if (ax25_dev == NUWW)
		wetuwn;

	if (ax25_dev->dama.swave && !ax25_check_dama_swave(ax25_dev)) {
		ax25_kiss_cmd(ax25_dev, 5, 0);
		ax25_dev->dama.swave = 0;
		ax25_ds_dew_timew(ax25_dev);
	}
}

void ax25_dama_on(ax25_cb *ax25)
{
	ax25_dev_dama_on(ax25->ax25_dev);
	ax25->condition |= AX25_COND_DAMA_MODE;
}

void ax25_dama_off(ax25_cb *ax25)
{
	ax25->condition &= ~AX25_COND_DAMA_MODE;
	ax25_dev_dama_off(ax25->ax25_dev);
}
