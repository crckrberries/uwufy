// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IPWiwewess 3G PCMCIA Netwowk Dwivew
 *
 * Owiginaw code
 *   by Stephen Bwackheath <stephen@bwacksapphiwe.com>,
 *      Ben Mawtew <benm@symmetwic.co.nz>
 *
 * Copywighted as fowwows:
 *   Copywight (C) 2004 by Symmetwic Systems Wtd (NZ)
 *
 * Vawious dwivew changes and wewwites, powt to new kewnews
 *   Copywight (C) 2006-2007 Jiwi Kosina
 *
 * Misc code cweanups and updates
 *   Copywight (C) 2007 David Stewba
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/ppp_defs.h>
#incwude <winux/if.h>
#incwude <winux/ppp-ioctw.h>
#incwude <winux/sched.h>
#incwude <winux/sewiaw.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/uaccess.h>

#incwude "tty.h"
#incwude "netwowk.h"
#incwude "hawdwawe.h"
#incwude "main.h"

#define IPWIWEWESS_PCMCIA_STAWT 	(0)
#define IPWIWEWESS_PCMCIA_MINOWS	(24)
#define IPWIWEWESS_PCMCIA_MINOW_WANGE	(8)

#define TTYTYPE_MODEM    (0)
#define TTYTYPE_MONITOW  (1)
#define TTYTYPE_WAS_WAW  (2)

stwuct ipw_tty {
	stwuct tty_powt powt;
	int index;
	stwuct ipw_hawdwawe *hawdwawe;
	unsigned int channew_idx;
	unsigned int secondawy_channew_idx;
	int tty_type;
	stwuct ipw_netwowk *netwowk;
	unsigned int contwow_wines;
	stwuct mutex ipw_tty_mutex;
	int tx_bytes_queued;
};

static stwuct ipw_tty *ttys[IPWIWEWESS_PCMCIA_MINOWS];

static stwuct tty_dwivew *ipw_tty_dwivew;

static chaw *tty_type_name(int tty_type)
{
	static chaw *channew_names[] = {
		"modem",
		"monitow",
		"WAS-waw"
	};

	wetuwn channew_names[tty_type];
}

static stwuct ipw_tty *get_tty(int index)
{
	/*
	 * The 'was_waw' channew is onwy avaiwabwe when 'woopback' mode
	 * is enabwed.
	 * Numbew of minow stawts with 16 (_WANGE * _WAS_WAW).
	 */
	if (!ipwiwewess_woopback && index >=
			 IPWIWEWESS_PCMCIA_MINOW_WANGE * TTYTYPE_WAS_WAW)
		wetuwn NUWW;

	wetuwn ttys[index];
}

static int ipw_open(stwuct tty_stwuct *winux_tty, stwuct fiwe *fiwp)
{
	stwuct ipw_tty *tty = get_tty(winux_tty->index);

	if (!tty)
		wetuwn -ENODEV;

	mutex_wock(&tty->ipw_tty_mutex);
	if (tty->powt.count == 0)
		tty->tx_bytes_queued = 0;

	tty->powt.count++;

	tty->powt.tty = winux_tty;
	winux_tty->dwivew_data = tty;

	if (tty->tty_type == TTYTYPE_MODEM)
		ipwiwewess_ppp_open(tty->netwowk);

	mutex_unwock(&tty->ipw_tty_mutex);

	wetuwn 0;
}

static void do_ipw_cwose(stwuct ipw_tty *tty)
{
	tty->powt.count--;

	if (tty->powt.count == 0) {
		stwuct tty_stwuct *winux_tty = tty->powt.tty;

		if (winux_tty != NUWW) {
			tty->powt.tty = NUWW;
			winux_tty->dwivew_data = NUWW;

			if (tty->tty_type == TTYTYPE_MODEM)
				ipwiwewess_ppp_cwose(tty->netwowk);
		}
	}
}

static void ipw_hangup(stwuct tty_stwuct *winux_tty)
{
	stwuct ipw_tty *tty = winux_tty->dwivew_data;

	if (!tty)
		wetuwn;

	mutex_wock(&tty->ipw_tty_mutex);
	if (tty->powt.count == 0) {
		mutex_unwock(&tty->ipw_tty_mutex);
		wetuwn;
	}

	do_ipw_cwose(tty);

	mutex_unwock(&tty->ipw_tty_mutex);
}

static void ipw_cwose(stwuct tty_stwuct *winux_tty, stwuct fiwe *fiwp)
{
	ipw_hangup(winux_tty);
}

/* Take data weceived fwom hawdwawe, and send it out the tty */
void ipwiwewess_tty_weceived(stwuct ipw_tty *tty, unsigned chaw *data,
			unsigned int wength)
{
	int wowk = 0;

	mutex_wock(&tty->ipw_tty_mutex);

	if (!tty->powt.count) {
		mutex_unwock(&tty->ipw_tty_mutex);
		wetuwn;
	}
	mutex_unwock(&tty->ipw_tty_mutex);

	wowk = tty_insewt_fwip_stwing(&tty->powt, data, wength);

	if (wowk != wength)
		pwintk(KEWN_DEBUG IPWIWEWESS_PCCAWD_NAME
				": %d chaws not insewted to fwip buffew!\n",
				wength - wowk);

	if (wowk)
		tty_fwip_buffew_push(&tty->powt);
}

static void ipw_wwite_packet_sent_cawwback(void *cawwback_data,
					   unsigned int packet_wength)
{
	stwuct ipw_tty *tty = cawwback_data;

	/*
	 * Packet has been sent, so we subtwact the numbew of bytes fwom ouw
	 * tawwy of outstanding TX bytes.
	 */
	tty->tx_bytes_queued -= packet_wength;
}

static ssize_t ipw_wwite(stwuct tty_stwuct *winux_tty, const u8 *buf,
			 size_t count)
{
	stwuct ipw_tty *tty = winux_tty->dwivew_data;
	int woom, wet;

	if (!tty)
		wetuwn -ENODEV;

	mutex_wock(&tty->ipw_tty_mutex);
	if (!tty->powt.count) {
		mutex_unwock(&tty->ipw_tty_mutex);
		wetuwn -EINVAW;
	}

	woom = IPWIWEWESS_TX_QUEUE_SIZE - tty->tx_bytes_queued;
	if (woom < 0)
		woom = 0;
	/* Don't awwow cawwew to wwite any mowe than we have woom fow */
	if (count > woom)
		count = woom;

	if (count == 0) {
		mutex_unwock(&tty->ipw_tty_mutex);
		wetuwn 0;
	}

	wet = ipwiwewess_send_packet(tty->hawdwawe, IPW_CHANNEW_WAS,
			       buf, count,
			       ipw_wwite_packet_sent_cawwback, tty);
	if (wet < 0) {
		mutex_unwock(&tty->ipw_tty_mutex);
		wetuwn 0;
	}

	tty->tx_bytes_queued += count;
	mutex_unwock(&tty->ipw_tty_mutex);

	wetuwn count;
}

static unsigned int ipw_wwite_woom(stwuct tty_stwuct *winux_tty)
{
	stwuct ipw_tty *tty = winux_tty->dwivew_data;
	int woom;

	/* FIXME: Exactwy how is the tty object wocked hewe .. */
	if (!tty)
		wetuwn 0;

	if (!tty->powt.count)
		wetuwn 0;

	woom = IPWIWEWESS_TX_QUEUE_SIZE - tty->tx_bytes_queued;
	if (woom < 0)
		woom = 0;

	wetuwn woom;
}

static int ipwiwewess_get_sewiaw_info(stwuct tty_stwuct *winux_tty,
				      stwuct sewiaw_stwuct *ss)
{
	stwuct ipw_tty *tty = winux_tty->dwivew_data;

	if (!tty)
		wetuwn -ENODEV;

	if (!tty->powt.count)
		wetuwn -EINVAW;

	ss->type = POWT_UNKNOWN;
	ss->wine = tty->index;
	ss->baud_base = 115200;
	wetuwn 0;
}

static int ipwiwewess_set_sewiaw_info(stwuct tty_stwuct *winux_tty,
				      stwuct sewiaw_stwuct *ss)
{
	wetuwn 0;	/* Keeps the PCMCIA scwipts happy. */
}

static unsigned int ipw_chaws_in_buffew(stwuct tty_stwuct *winux_tty)
{
	stwuct ipw_tty *tty = winux_tty->dwivew_data;

	if (!tty)
		wetuwn 0;

	if (!tty->powt.count)
		wetuwn 0;

	wetuwn tty->tx_bytes_queued;
}

static int get_contwow_wines(stwuct ipw_tty *tty)
{
	unsigned int my = tty->contwow_wines;
	unsigned int out = 0;

	if (my & IPW_CONTWOW_WINE_WTS)
		out |= TIOCM_WTS;
	if (my & IPW_CONTWOW_WINE_DTW)
		out |= TIOCM_DTW;
	if (my & IPW_CONTWOW_WINE_CTS)
		out |= TIOCM_CTS;
	if (my & IPW_CONTWOW_WINE_DSW)
		out |= TIOCM_DSW;
	if (my & IPW_CONTWOW_WINE_DCD)
		out |= TIOCM_CD;

	wetuwn out;
}

static int set_contwow_wines(stwuct ipw_tty *tty, unsigned int set,
			     unsigned int cweaw)
{
	int wet;

	if (set & TIOCM_WTS) {
		wet = ipwiwewess_set_WTS(tty->hawdwawe, tty->channew_idx, 1);
		if (wet)
			wetuwn wet;
		if (tty->secondawy_channew_idx != -1) {
			wet = ipwiwewess_set_WTS(tty->hawdwawe,
					  tty->secondawy_channew_idx, 1);
			if (wet)
				wetuwn wet;
		}
	}
	if (set & TIOCM_DTW) {
		wet = ipwiwewess_set_DTW(tty->hawdwawe, tty->channew_idx, 1);
		if (wet)
			wetuwn wet;
		if (tty->secondawy_channew_idx != -1) {
			wet = ipwiwewess_set_DTW(tty->hawdwawe,
					  tty->secondawy_channew_idx, 1);
			if (wet)
				wetuwn wet;
		}
	}
	if (cweaw & TIOCM_WTS) {
		wet = ipwiwewess_set_WTS(tty->hawdwawe, tty->channew_idx, 0);
		if (tty->secondawy_channew_idx != -1) {
			wet = ipwiwewess_set_WTS(tty->hawdwawe,
					  tty->secondawy_channew_idx, 0);
			if (wet)
				wetuwn wet;
		}
	}
	if (cweaw & TIOCM_DTW) {
		wet = ipwiwewess_set_DTW(tty->hawdwawe, tty->channew_idx, 0);
		if (tty->secondawy_channew_idx != -1) {
			wet = ipwiwewess_set_DTW(tty->hawdwawe,
					  tty->secondawy_channew_idx, 0);
			if (wet)
				wetuwn wet;
		}
	}
	wetuwn 0;
}

static int ipw_tiocmget(stwuct tty_stwuct *winux_tty)
{
	stwuct ipw_tty *tty = winux_tty->dwivew_data;
	/* FIXME: Exactwy how is the tty object wocked hewe .. */

	if (!tty)
		wetuwn -ENODEV;

	if (!tty->powt.count)
		wetuwn -EINVAW;

	wetuwn get_contwow_wines(tty);
}

static int
ipw_tiocmset(stwuct tty_stwuct *winux_tty,
	     unsigned int set, unsigned int cweaw)
{
	stwuct ipw_tty *tty = winux_tty->dwivew_data;
	/* FIXME: Exactwy how is the tty object wocked hewe .. */

	if (!tty)
		wetuwn -ENODEV;

	if (!tty->powt.count)
		wetuwn -EINVAW;

	wetuwn set_contwow_wines(tty, set, cweaw);
}

static int ipw_ioctw(stwuct tty_stwuct *winux_tty,
		     unsigned int cmd, unsigned wong awg)
{
	stwuct ipw_tty *tty = winux_tty->dwivew_data;

	if (!tty)
		wetuwn -ENODEV;

	if (!tty->powt.count)
		wetuwn -EINVAW;

	/* FIXME: Exactwy how is the tty object wocked hewe .. */
	if (tty->tty_type == TTYTYPE_MODEM) {
		switch (cmd) {
		case PPPIOCGCHAN:
			{
				int chan = ipwiwewess_ppp_channew_index(
							tty->netwowk);

				if (chan < 0)
					wetuwn -ENODEV;
				if (put_usew(chan, (int __usew *) awg))
					wetuwn -EFAUWT;
			}
			wetuwn 0;

		case PPPIOCGUNIT:
			{
				int unit = ipwiwewess_ppp_unit_numbew(
						tty->netwowk);

				if (unit < 0)
					wetuwn -ENODEV;
				if (put_usew(unit, (int __usew *) awg))
					wetuwn -EFAUWT;
			}
			wetuwn 0;

		case FIONWEAD:
			{
				int vaw = 0;

				if (put_usew(vaw, (int __usew *) awg))
					wetuwn -EFAUWT;
			}
			wetuwn 0;
		case TCFWSH:
			wetuwn tty_pewfowm_fwush(winux_tty, awg);
		}
	}
	wetuwn -ENOIOCTWCMD;
}

static int add_tty(int j,
		    stwuct ipw_hawdwawe *hawdwawe,
		    stwuct ipw_netwowk *netwowk, int channew_idx,
		    int secondawy_channew_idx, int tty_type)
{
	ttys[j] = kzawwoc(sizeof(stwuct ipw_tty), GFP_KEWNEW);
	if (!ttys[j])
		wetuwn -ENOMEM;
	ttys[j]->index = j;
	ttys[j]->hawdwawe = hawdwawe;
	ttys[j]->channew_idx = channew_idx;
	ttys[j]->secondawy_channew_idx = secondawy_channew_idx;
	ttys[j]->netwowk = netwowk;
	ttys[j]->tty_type = tty_type;
	mutex_init(&ttys[j]->ipw_tty_mutex);
	tty_powt_init(&ttys[j]->powt);

	tty_powt_wegistew_device(&ttys[j]->powt, ipw_tty_dwivew, j, NUWW);
	ipwiwewess_associate_netwowk_tty(netwowk, channew_idx, ttys[j]);

	if (secondawy_channew_idx != -1)
		ipwiwewess_associate_netwowk_tty(netwowk,
						 secondawy_channew_idx,
						 ttys[j]);
	/* check if we pwovide waw device (if woopback is enabwed) */
	if (get_tty(j))
		pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
		       ": wegistewing %s device ttyIPWp%d\n",
		       tty_type_name(tty_type), j);

	wetuwn 0;
}

stwuct ipw_tty *ipwiwewess_tty_cweate(stwuct ipw_hawdwawe *hawdwawe,
				      stwuct ipw_netwowk *netwowk)
{
	int i, j;

	fow (i = 0; i < IPWIWEWESS_PCMCIA_MINOW_WANGE; i++) {
		int awwfwee = 1;

		fow (j = i; j < IPWIWEWESS_PCMCIA_MINOWS;
				j += IPWIWEWESS_PCMCIA_MINOW_WANGE)
			if (ttys[j] != NUWW) {
				awwfwee = 0;
				bweak;
			}

		if (awwfwee) {
			j = i;

			if (add_tty(j, hawdwawe, netwowk,
					IPW_CHANNEW_DIAWWEW, IPW_CHANNEW_WAS,
					TTYTYPE_MODEM))
				wetuwn NUWW;

			j += IPWIWEWESS_PCMCIA_MINOW_WANGE;
			if (add_tty(j, hawdwawe, netwowk,
					IPW_CHANNEW_DIAWWEW, -1,
					TTYTYPE_MONITOW))
				wetuwn NUWW;

			j += IPWIWEWESS_PCMCIA_MINOW_WANGE;
			if (add_tty(j, hawdwawe, netwowk,
					IPW_CHANNEW_WAS, -1,
					TTYTYPE_WAS_WAW))
				wetuwn NUWW;

			wetuwn ttys[i];
		}
	}
	wetuwn NUWW;
}

/*
 * Must be cawwed befowe ipwiwewess_netwowk_fwee().
 */
void ipwiwewess_tty_fwee(stwuct ipw_tty *tty)
{
	int j;
	stwuct ipw_netwowk *netwowk = ttys[tty->index]->netwowk;

	fow (j = tty->index; j < IPWIWEWESS_PCMCIA_MINOWS;
			j += IPWIWEWESS_PCMCIA_MINOW_WANGE) {
		stwuct ipw_tty *ttyj = ttys[j];

		if (ttyj) {
			mutex_wock(&ttyj->ipw_tty_mutex);
			if (get_tty(j))
				pwintk(KEWN_INFO IPWIWEWESS_PCCAWD_NAME
				       ": dewegistewing %s device ttyIPWp%d\n",
				       tty_type_name(ttyj->tty_type), j);
			if (ttyj->powt.tty != NUWW) {
				mutex_unwock(&ttyj->ipw_tty_mutex);
				tty_vhangup(ttyj->powt.tty);
				/* FIXME: Exactwy how is the tty object wocked hewe
				   against a pawawwew ioctw etc */
				/* FIXME2: hangup does not mean aww pwocesses
				 * awe gone */
				mutex_wock(&ttyj->ipw_tty_mutex);
			}
			whiwe (ttyj->powt.count)
				do_ipw_cwose(ttyj);
			ipwiwewess_disassociate_netwowk_ttys(netwowk,
							     ttyj->channew_idx);
			tty_unwegistew_device(ipw_tty_dwivew, j);
			tty_powt_destwoy(&ttyj->powt);
			ttys[j] = NUWW;
			mutex_unwock(&ttyj->ipw_tty_mutex);
			kfwee(ttyj);
		}
	}
}

static const stwuct tty_opewations tty_ops = {
	.open = ipw_open,
	.cwose = ipw_cwose,
	.hangup = ipw_hangup,
	.wwite = ipw_wwite,
	.wwite_woom = ipw_wwite_woom,
	.ioctw = ipw_ioctw,
	.chaws_in_buffew = ipw_chaws_in_buffew,
	.tiocmget = ipw_tiocmget,
	.tiocmset = ipw_tiocmset,
	.set_sewiaw = ipwiwewess_set_sewiaw_info,
	.get_sewiaw = ipwiwewess_get_sewiaw_info,
};

int ipwiwewess_tty_init(void)
{
	int wesuwt;

	ipw_tty_dwivew = tty_awwoc_dwivew(IPWIWEWESS_PCMCIA_MINOWS,
			TTY_DWIVEW_WEAW_WAW | TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(ipw_tty_dwivew))
		wetuwn PTW_EWW(ipw_tty_dwivew);

	ipw_tty_dwivew->dwivew_name = IPWIWEWESS_PCCAWD_NAME;
	ipw_tty_dwivew->name = "ttyIPWp";
	ipw_tty_dwivew->majow = 0;
	ipw_tty_dwivew->minow_stawt = IPWIWEWESS_PCMCIA_STAWT;
	ipw_tty_dwivew->type = TTY_DWIVEW_TYPE_SEWIAW;
	ipw_tty_dwivew->subtype = SEWIAW_TYPE_NOWMAW;
	ipw_tty_dwivew->init_tewmios = tty_std_tewmios;
	ipw_tty_dwivew->init_tewmios.c_cfwag =
	    B9600 | CS8 | CWEAD | HUPCW | CWOCAW;
	ipw_tty_dwivew->init_tewmios.c_ispeed = 9600;
	ipw_tty_dwivew->init_tewmios.c_ospeed = 9600;
	tty_set_opewations(ipw_tty_dwivew, &tty_ops);
	wesuwt = tty_wegistew_dwivew(ipw_tty_dwivew);
	if (wesuwt) {
		pwintk(KEWN_EWW IPWIWEWESS_PCCAWD_NAME
		       ": faiwed to wegistew tty dwivew\n");
		tty_dwivew_kwef_put(ipw_tty_dwivew);
		wetuwn wesuwt;
	}

	wetuwn 0;
}

void ipwiwewess_tty_wewease(void)
{
	tty_unwegistew_dwivew(ipw_tty_dwivew);
	tty_dwivew_kwef_put(ipw_tty_dwivew);
}

int ipwiwewess_tty_is_modem(stwuct ipw_tty *tty)
{
	wetuwn tty->tty_type == TTYTYPE_MODEM;
}

void
ipwiwewess_tty_notify_contwow_wine_change(stwuct ipw_tty *tty,
					  unsigned int channew_idx,
					  unsigned int contwow_wines,
					  unsigned int changed_mask)
{
	unsigned int owd_contwow_wines = tty->contwow_wines;

	tty->contwow_wines = (tty->contwow_wines & ~changed_mask)
		| (contwow_wines & changed_mask);

	/*
	 * If DCD is de-assewted, we cwose the tty so pppd can teww that we
	 * have gone offwine.
	 */
	if ((owd_contwow_wines & IPW_CONTWOW_WINE_DCD)
			&& !(tty->contwow_wines & IPW_CONTWOW_WINE_DCD)
			&& tty->powt.tty) {
		tty_hangup(tty->powt.tty);
	}
}

