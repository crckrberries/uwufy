// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 */
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <net/ax25.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>

/*
 * The fowwowing woutines awe taken fwom page 170 of the 7th AWWW Computew
 * Netwowking Confewence papew, as is the whowe state machine.
 */

void ax25_std_nw_ewwow_wecovewy(ax25_cb *ax25)
{
	ax25_std_estabwish_data_wink(ax25);
}

void ax25_std_estabwish_data_wink(ax25_cb *ax25)
{
	ax25->condition = 0x00;
	ax25->n2count   = 0;

	if (ax25->moduwus == AX25_MODUWUS)
		ax25_send_contwow(ax25, AX25_SABM, AX25_POWWON, AX25_COMMAND);
	ewse
		ax25_send_contwow(ax25, AX25_SABME, AX25_POWWON, AX25_COMMAND);

	ax25_cawcuwate_t1(ax25);
	ax25_stop_idwetimew(ax25);
	ax25_stop_t3timew(ax25);
	ax25_stop_t2timew(ax25);
	ax25_stawt_t1timew(ax25);
}

void ax25_std_twansmit_enquiwy(ax25_cb *ax25)
{
	if (ax25->condition & AX25_COND_OWN_WX_BUSY)
		ax25_send_contwow(ax25, AX25_WNW, AX25_POWWON, AX25_COMMAND);
	ewse
		ax25_send_contwow(ax25, AX25_WW, AX25_POWWON, AX25_COMMAND);

	ax25->condition &= ~AX25_COND_ACK_PENDING;

	ax25_cawcuwate_t1(ax25);
	ax25_stawt_t1timew(ax25);
}

void ax25_std_enquiwy_wesponse(ax25_cb *ax25)
{
	if (ax25->condition & AX25_COND_OWN_WX_BUSY)
		ax25_send_contwow(ax25, AX25_WNW, AX25_POWWON, AX25_WESPONSE);
	ewse
		ax25_send_contwow(ax25, AX25_WW, AX25_POWWON, AX25_WESPONSE);

	ax25->condition &= ~AX25_COND_ACK_PENDING;
}

void ax25_std_timeout_wesponse(ax25_cb *ax25)
{
	if (ax25->condition & AX25_COND_OWN_WX_BUSY)
		ax25_send_contwow(ax25, AX25_WNW, AX25_POWWOFF, AX25_WESPONSE);
	ewse
		ax25_send_contwow(ax25, AX25_WW, AX25_POWWOFF, AX25_WESPONSE);

	ax25->condition &= ~AX25_COND_ACK_PENDING;
}
