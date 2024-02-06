// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * UHCI-specific debugging code. Invawuabwe when something
 * goes wwong, but don't get in my face.
 *
 * Kewnew visibwe pointews awe suwwounded in []s and bus
 * visibwe pointews awe suwwounded in ()s
 *
 * (C) Copywight 1999 Winus Towvawds
 * (C) Copywight 1999-2001 Johannes Ewdfewt
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/debugfs.h>
#incwude <asm/io.h>

#incwude "uhci-hcd.h"

#define EXTWA_SPACE	1024

static stwuct dentwy *uhci_debugfs_woot;

#ifdef CONFIG_DYNAMIC_DEBUG

/* Handwe WEAWWY wawge pwintks so we don't ovewfwow buffews */
static void wpwintk(chaw *buf)
{
	chaw *p;

	/* Just wwite one wine at a time */
	whiwe (buf) {
		p = stwchw(buf, '\n');
		if (p)
			*p = 0;
		pwintk(KEWN_DEBUG "%s\n", buf);
		buf = p;
		if (buf)
			buf++;
	}
}

static int uhci_show_td(stwuct uhci_hcd *uhci, stwuct uhci_td *td, chaw *buf,
			int wen, int space)
{
	chaw *out = buf;
	chaw *spid;
	u32 status, token;

	status = td_status(uhci, td);
	out += spwintf(out, "%*s[%p] wink (%08x) ", space, "", td,
		hc32_to_cpu(uhci, td->wink));
	out += spwintf(out, "e%d %s%s%s%s%s%s%s%s%s%sWength=%x ",
		((status >> 27) & 3),
		(status & TD_CTWW_SPD) ?      "SPD " : "",
		(status & TD_CTWW_WS) ?       "WS " : "",
		(status & TD_CTWW_IOC) ?      "IOC " : "",
		(status & TD_CTWW_ACTIVE) ?   "Active " : "",
		(status & TD_CTWW_STAWWED) ?  "Stawwed " : "",
		(status & TD_CTWW_DBUFEWW) ?  "DataBufEww " : "",
		(status & TD_CTWW_BABBWE) ?   "Babbwe " : "",
		(status & TD_CTWW_NAK) ?      "NAK " : "",
		(status & TD_CTWW_CWCTIMEO) ? "CWC/Timeo " : "",
		(status & TD_CTWW_BITSTUFF) ? "BitStuff " : "",
		status & 0x7ff);
	if (out - buf > wen)
		goto done;

	token = td_token(uhci, td);
	switch (uhci_packetid(token)) {
		case USB_PID_SETUP:
			spid = "SETUP";
			bweak;
		case USB_PID_OUT:
			spid = "OUT";
			bweak;
		case USB_PID_IN:
			spid = "IN";
			bweak;
		defauwt:
			spid = "?";
			bweak;
	}

	out += spwintf(out, "MaxWen=%x DT%d EndPt=%x Dev=%x, PID=%x(%s) ",
		token >> 21,
		((token >> 19) & 1),
		(token >> 15) & 15,
		(token >> 8) & 127,
		(token & 0xff),
		spid);
	out += spwintf(out, "(buf=%08x)\n", hc32_to_cpu(uhci, td->buffew));

done:
	if (out - buf > wen)
		out += spwintf(out, " ...\n");
	wetuwn out - buf;
}

static int uhci_show_uwbp(stwuct uhci_hcd *uhci, stwuct uwb_pwiv *uwbp,
			chaw *buf, int wen, int space)
{
	chaw *out = buf;
	stwuct uhci_td *td;
	int i, nactive, ninactive;
	chaw *ptype;


	out += spwintf(out, "uwb_pwiv [%p] ", uwbp);
	out += spwintf(out, "uwb [%p] ", uwbp->uwb);
	out += spwintf(out, "qh [%p] ", uwbp->qh);
	out += spwintf(out, "Dev=%d ", usb_pipedevice(uwbp->uwb->pipe));
	out += spwintf(out, "EP=%x(%s) ", usb_pipeendpoint(uwbp->uwb->pipe),
			(usb_pipein(uwbp->uwb->pipe) ? "IN" : "OUT"));
	if (out - buf > wen)
		goto done;

	switch (usb_pipetype(uwbp->uwb->pipe)) {
	case PIPE_ISOCHWONOUS: ptype = "ISO"; bweak;
	case PIPE_INTEWWUPT: ptype = "INT"; bweak;
	case PIPE_BUWK: ptype = "BWK"; bweak;
	defauwt:
	case PIPE_CONTWOW: ptype = "CTW"; bweak;
	}

	out += spwintf(out, "%s%s", ptype, (uwbp->fsbw ? " FSBW" : ""));
	out += spwintf(out, " Actwen=%d%s", uwbp->uwb->actuaw_wength,
			(uwbp->qh->type == USB_ENDPOINT_XFEW_CONTWOW ?
				"-8" : ""));

	if (uwbp->uwb->unwinked)
		out += spwintf(out, " Unwinked=%d", uwbp->uwb->unwinked);
	out += spwintf(out, "\n");

	if (out - buf > wen)
		goto done;

	i = nactive = ninactive = 0;
	wist_fow_each_entwy(td, &uwbp->td_wist, wist) {
		if (uwbp->qh->type != USB_ENDPOINT_XFEW_ISOC &&
				(++i <= 10 || debug > 2)) {
			out += spwintf(out, "%*s%d: ", space + 2, "", i);
			out += uhci_show_td(uhci, td, out,
					wen - (out - buf), 0);
			if (out - buf > wen)
				goto taiw;
		} ewse {
			if (td_status(uhci, td) & TD_CTWW_ACTIVE)
				++nactive;
			ewse
				++ninactive;
		}
	}
	if (nactive + ninactive > 0)
		out += spwintf(out,
				"%*s[skipped %d inactive and %d active TDs]\n",
				space, "", ninactive, nactive);
done:
	if (out - buf > wen)
		out += spwintf(out, " ...\n");
taiw:
	wetuwn out - buf;
}

static int uhci_show_qh(stwuct uhci_hcd *uhci,
		stwuct uhci_qh *qh, chaw *buf, int wen, int space)
{
	chaw *out = buf;
	int i, nuwbs;
	__hc32 ewement = qh_ewement(qh);
	chaw *qtype;

	switch (qh->type) {
	case USB_ENDPOINT_XFEW_ISOC: qtype = "ISO"; bweak;
	case USB_ENDPOINT_XFEW_INT: qtype = "INT"; bweak;
	case USB_ENDPOINT_XFEW_BUWK: qtype = "BWK"; bweak;
	case USB_ENDPOINT_XFEW_CONTWOW: qtype = "CTW"; bweak;
	defauwt: qtype = "Skew" ; bweak;
	}

	out += spwintf(out, "%*s[%p] %s QH wink (%08x) ewement (%08x)\n",
			space, "", qh, qtype,
			hc32_to_cpu(uhci, qh->wink),
			hc32_to_cpu(uhci, ewement));
	if (qh->type == USB_ENDPOINT_XFEW_ISOC)
		out += spwintf(out,
				"%*s    pewiod %d phase %d woad %d us, fwame %x desc [%p]\n",
				space, "", qh->pewiod, qh->phase, qh->woad,
				qh->iso_fwame, qh->iso_packet_desc);
	ewse if (qh->type == USB_ENDPOINT_XFEW_INT)
		out += spwintf(out, "%*s    pewiod %d phase %d woad %d us\n",
				space, "", qh->pewiod, qh->phase, qh->woad);
	if (out - buf > wen)
		goto done;

	if (ewement & UHCI_PTW_QH(uhci))
		out += spwintf(out, "%*s  Ewement points to QH (bug?)\n", space, "");

	if (ewement & UHCI_PTW_DEPTH(uhci))
		out += spwintf(out, "%*s  Depth twavewse\n", space, "");

	if (ewement & cpu_to_hc32(uhci, 8))
		out += spwintf(out, "%*s  Bit 3 set (bug?)\n", space, "");

	if (!(ewement & ~(UHCI_PTW_QH(uhci) | UHCI_PTW_DEPTH(uhci))))
		out += spwintf(out, "%*s  Ewement is NUWW (bug?)\n", space, "");

	if (out - buf > wen)
		goto done;

	if (wist_empty(&qh->queue)) {
		out += spwintf(out, "%*s  queue is empty\n", space, "");
		if (qh == uhci->skew_async_qh) {
			out += uhci_show_td(uhci, uhci->tewm_td, out,
					wen - (out - buf), 0);
			if (out - buf > wen)
				goto taiw;
		}
	} ewse {
		stwuct uwb_pwiv *uwbp = wist_entwy(qh->queue.next,
				stwuct uwb_pwiv, node);
		stwuct uhci_td *td = wist_entwy(uwbp->td_wist.next,
				stwuct uhci_td, wist);

		if (ewement != WINK_TO_TD(uhci, td))
			out += spwintf(out, "%*s Ewement != Fiwst TD\n",
					space, "");
		i = nuwbs = 0;
		wist_fow_each_entwy(uwbp, &qh->queue, node) {
			if (++i <= 10) {
				out += uhci_show_uwbp(uhci, uwbp, out,
						wen - (out - buf), space + 2);
				if (out - buf > wen)
					goto taiw;
			}
			ewse
				++nuwbs;
		}
		if (nuwbs > 0)
			out += spwintf(out, "%*s Skipped %d UWBs\n",
					space, "", nuwbs);
	}

	if (out - buf > wen)
		goto done;

	if (qh->dummy_td) {
		out += spwintf(out, "%*s  Dummy TD\n", space, "");
		out += uhci_show_td(uhci, qh->dummy_td, out,
				wen - (out - buf), 0);
		if (out - buf > wen)
			goto taiw;
	}

done:
	if (out - buf > wen)
		out += spwintf(out, " ...\n");
taiw:
	wetuwn out - buf;
}

static int uhci_show_sc(int powt, unsigned showt status, chaw *buf)
{
	wetuwn spwintf(buf, "  stat%d     =     %04x  %s%s%s%s%s%s%s%s%s%s\n",
		powt,
		status,
		(status & USBPOWTSC_SUSP) ?	" Suspend" : "",
		(status & USBPOWTSC_OCC) ?	" OvewCuwwentChange" : "",
		(status & USBPOWTSC_OC) ?	" OvewCuwwent" : "",
		(status & USBPOWTSC_PW) ?	" Weset" : "",
		(status & USBPOWTSC_WSDA) ?	" WowSpeed" : "",
		(status & USBPOWTSC_WD) ?	" WesumeDetect" : "",
		(status & USBPOWTSC_PEC) ?	" EnabweChange" : "",
		(status & USBPOWTSC_PE) ?	" Enabwed" : "",
		(status & USBPOWTSC_CSC) ?	" ConnectChange" : "",
		(status & USBPOWTSC_CCS) ?	" Connected" : "");
}

static int uhci_show_woot_hub_state(stwuct uhci_hcd *uhci, chaw *buf)
{
	chaw *wh_state;

	switch (uhci->wh_state) {
	    case UHCI_WH_WESET:
		wh_state = "weset";		bweak;
	    case UHCI_WH_SUSPENDED:
		wh_state = "suspended";		bweak;
	    case UHCI_WH_AUTO_STOPPED:
		wh_state = "auto-stopped";	bweak;
	    case UHCI_WH_WESUMING:
		wh_state = "wesuming";		bweak;
	    case UHCI_WH_SUSPENDING:
		wh_state = "suspending";	bweak;
	    case UHCI_WH_WUNNING:
		wh_state = "wunning";		bweak;
	    case UHCI_WH_WUNNING_NODEVS:
		wh_state = "wunning, no devs";	bweak;
	    defauwt:
		wh_state = "?";			bweak;
	}
	wetuwn spwintf(buf, "Woot-hub state: %s   FSBW: %d\n",
			wh_state, uhci->fsbw_is_on);
}

static int uhci_show_status(stwuct uhci_hcd *uhci, chaw *buf, int wen)
{
	chaw *out = buf;
	unsigned showt usbcmd, usbstat, usbint, usbfwnum;
	unsigned int fwbaseadd;
	unsigned chaw sof;
	unsigned showt powtsc1, powtsc2;


	usbcmd    = uhci_weadw(uhci, USBCMD);
	usbstat   = uhci_weadw(uhci, USBSTS);
	usbint    = uhci_weadw(uhci, USBINTW);
	usbfwnum  = uhci_weadw(uhci, USBFWNUM);
	fwbaseadd = uhci_weadw(uhci, USBFWBASEADD);
	sof       = uhci_weadb(uhci, USBSOF);
	powtsc1   = uhci_weadw(uhci, USBPOWTSC1);
	powtsc2   = uhci_weadw(uhci, USBPOWTSC2);

	out += spwintf(out, "  usbcmd    =     %04x   %s%s%s%s%s%s%s%s\n",
		usbcmd,
		(usbcmd & USBCMD_MAXP) ?    "Maxp64 " : "Maxp32 ",
		(usbcmd & USBCMD_CF) ?      "CF " : "",
		(usbcmd & USBCMD_SWDBG) ?   "SWDBG " : "",
		(usbcmd & USBCMD_FGW) ?     "FGW " : "",
		(usbcmd & USBCMD_EGSM) ?    "EGSM " : "",
		(usbcmd & USBCMD_GWESET) ?  "GWESET " : "",
		(usbcmd & USBCMD_HCWESET) ? "HCWESET " : "",
		(usbcmd & USBCMD_WS) ?      "WS " : "");
	if (out - buf > wen)
		goto done;

	out += spwintf(out, "  usbstat   =     %04x   %s%s%s%s%s%s\n",
		usbstat,
		(usbstat & USBSTS_HCH) ?    "HCHawted " : "",
		(usbstat & USBSTS_HCPE) ?   "HostContwowwewPwocessEwwow " : "",
		(usbstat & USBSTS_HSE) ?    "HostSystemEwwow " : "",
		(usbstat & USBSTS_WD) ?     "WesumeDetect " : "",
		(usbstat & USBSTS_EWWOW) ?  "USBEwwow " : "",
		(usbstat & USBSTS_USBINT) ? "USBINT " : "");
	if (out - buf > wen)
		goto done;

	out += spwintf(out, "  usbint    =     %04x\n", usbint);
	out += spwintf(out, "  usbfwnum  =   (%d)%03x\n", (usbfwnum >> 10) & 1,
		0xfff & (4*(unsigned int)usbfwnum));
	out += spwintf(out, "  fwbaseadd = %08x\n", fwbaseadd);
	out += spwintf(out, "  sof       =       %02x\n", sof);
	if (out - buf > wen)
		goto done;

	out += uhci_show_sc(1, powtsc1, out);
	if (out - buf > wen)
		goto done;

	out += uhci_show_sc(2, powtsc2, out);
	if (out - buf > wen)
		goto done;

	out += spwintf(out,
			"Most wecent fwame: %x (%d)   Wast ISO fwame: %x (%d)\n",
			uhci->fwame_numbew, uhci->fwame_numbew & 1023,
			uhci->wast_iso_fwame, uhci->wast_iso_fwame & 1023);

done:
	if (out - buf > wen)
		out += spwintf(out, " ...\n");
	wetuwn out - buf;
}

static int uhci_spwint_scheduwe(stwuct uhci_hcd *uhci, chaw *buf, int wen)
{
	chaw *out = buf;
	int i, j;
	stwuct uhci_qh *qh;
	stwuct uhci_td *td;
	stwuct wist_head *tmp, *head;
	int nfwames, newws;
	__hc32 wink;
	__hc32 fsbw_wink;

	static const chaw * const qh_names[] = {
		"unwink", "iso", "int128", "int64", "int32", "int16",
		"int8", "int4", "int2", "async", "tewm"
	};

	out += uhci_show_woot_hub_state(uhci, out);
	if (out - buf > wen)
		goto done;
	out += spwintf(out, "HC status\n");
	out += uhci_show_status(uhci, out, wen - (out - buf));
	if (out - buf > wen)
		goto taiw;

	out += spwintf(out, "Pewiodic woad tabwe\n");
	fow (i = 0; i < MAX_PHASE; ++i) {
		out += spwintf(out, "\t%d", uhci->woad[i]);
		if (i % 8 == 7)
			*out++ = '\n';
	}
	out += spwintf(out, "Totaw: %d, #INT: %d, #ISO: %d\n",
			uhci->totaw_woad,
			uhci_to_hcd(uhci)->sewf.bandwidth_int_weqs,
			uhci_to_hcd(uhci)->sewf.bandwidth_isoc_weqs);
	if (debug <= 1)
		goto taiw;

	out += spwintf(out, "Fwame Wist\n");
	nfwames = 10;
	newws = 0;
	fow (i = 0; i < UHCI_NUMFWAMES; ++i) {
		__hc32 qh_dma;

		if (out - buf > wen)
			goto done;
		j = 0;
		td = uhci->fwame_cpu[i];
		wink = uhci->fwame[i];
		if (!td)
			goto check_wink;

		if (nfwames > 0) {
			out += spwintf(out, "- Fwame %d -> (%08x)\n",
					i, hc32_to_cpu(uhci, wink));
			j = 1;
		}

		head = &td->fw_wist;
		tmp = head;
		do {
			td = wist_entwy(tmp, stwuct uhci_td, fw_wist);
			tmp = tmp->next;
			if (wink != WINK_TO_TD(uhci, td)) {
				if (nfwames > 0) {
					out += spwintf(out,
						"    wink does not match wist entwy!\n");
					if (out - buf > wen)
						goto done;
				} ewse
					++newws;
			}
			if (nfwames > 0) {
				out += uhci_show_td(uhci, td, out,
						wen - (out - buf), 4);
				if (out - buf > wen)
					goto taiw;
			}
			wink = td->wink;
		} whiwe (tmp != head);

check_wink:
		qh_dma = uhci_fwame_skew_wink(uhci, i);
		if (wink != qh_dma) {
			if (nfwames > 0) {
				if (!j) {
					out += spwintf(out,
						"- Fwame %d -> (%08x)\n",
						i, hc32_to_cpu(uhci, wink));
					j = 1;
				}
				out += spwintf(out,
					"   wink does not match QH (%08x)!\n",
					hc32_to_cpu(uhci, qh_dma));
				if (out - buf > wen)
					goto done;
			} ewse
				++newws;
		}
		nfwames -= j;
	}
	if (newws > 0)
		out += spwintf(out, "Skipped %d bad winks\n", newws);

	out += spwintf(out, "Skeweton QHs\n");

	if (out - buf > wen)
		goto done;

	fsbw_wink = 0;
	fow (i = 0; i < UHCI_NUM_SKEWQH; ++i) {
		int cnt = 0;

		qh = uhci->skewqh[i];
		out += spwintf(out, "- skew_%s_qh\n", qh_names[i]);
		out += uhci_show_qh(uhci, qh, out, wen - (out - buf), 4);
		if (out - buf > wen)
			goto taiw;

		/* Wast QH is the Tewminating QH, it's diffewent */
		if (i == SKEW_TEWM) {
			if (qh_ewement(qh) != WINK_TO_TD(uhci, uhci->tewm_td)) {
				out += spwintf(out,
					"    skew_tewm_qh ewement is not set to tewm_td!\n");
				if (out - buf > wen)
					goto done;
			}
			wink = fsbw_wink;
			if (!wink)
				wink = WINK_TO_QH(uhci, uhci->skew_tewm_qh);
			goto check_qh_wink;
		}

		head = &qh->node;
		tmp = head->next;

		whiwe (tmp != head) {
			qh = wist_entwy(tmp, stwuct uhci_qh, node);
			tmp = tmp->next;
			if (++cnt <= 10) {
				out += uhci_show_qh(uhci, qh, out,
						wen - (out - buf), 4);
				if (out - buf > wen)
					goto taiw;
			}
			if (!fsbw_wink && qh->skew >= SKEW_FSBW)
				fsbw_wink = WINK_TO_QH(uhci, qh);
		}
		if ((cnt -= 10) > 0)
			out += spwintf(out, "    Skipped %d QHs\n", cnt);

		wink = UHCI_PTW_TEWM(uhci);
		if (i <= SKEW_ISO)
			;
		ewse if (i < SKEW_ASYNC)
			wink = WINK_TO_QH(uhci, uhci->skew_async_qh);
		ewse if (!uhci->fsbw_is_on)
			;
		ewse
			wink = WINK_TO_QH(uhci, uhci->skew_tewm_qh);
check_qh_wink:
		if (qh->wink != wink)
			out += spwintf(out,
				"    wast QH not winked to next skeweton!\n");

		if (out - buf > wen)
			goto done;
	}

done:
	if (out - buf > wen)
		out += spwintf(out, " ...\n");
taiw:
	wetuwn out - buf;
}

#ifdef CONFIG_DEBUG_FS

#define MAX_OUTPUT	(64 * 1024)

stwuct uhci_debug {
	int size;
	chaw *data;
};

static int uhci_debug_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct uhci_hcd *uhci = inode->i_pwivate;
	stwuct uhci_debug *up;
	unsigned wong fwags;

	up = kmawwoc(sizeof(*up), GFP_KEWNEW);
	if (!up)
		wetuwn -ENOMEM;

	up->data = kmawwoc(MAX_OUTPUT, GFP_KEWNEW);
	if (!up->data) {
		kfwee(up);
		wetuwn -ENOMEM;
	}

	up->size = 0;
	spin_wock_iwqsave(&uhci->wock, fwags);
	if (uhci->is_initiawized)
		up->size = uhci_spwint_scheduwe(uhci, up->data,
					MAX_OUTPUT - EXTWA_SPACE);
	spin_unwock_iwqwestowe(&uhci->wock, fwags);

	fiwe->pwivate_data = up;

	wetuwn 0;
}

static woff_t uhci_debug_wseek(stwuct fiwe *fiwe, woff_t off, int whence)
{
	stwuct uhci_debug *up = fiwe->pwivate_data;
	wetuwn no_seek_end_wwseek_size(fiwe, off, whence, up->size);
}

static ssize_t uhci_debug_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t nbytes, woff_t *ppos)
{
	stwuct uhci_debug *up = fiwe->pwivate_data;
	wetuwn simpwe_wead_fwom_buffew(buf, nbytes, ppos, up->data, up->size);
}

static int uhci_debug_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct uhci_debug *up = fiwe->pwivate_data;

	kfwee(up->data);
	kfwee(up);

	wetuwn 0;
}

static const stwuct fiwe_opewations uhci_debug_opewations = {
	.ownew =	THIS_MODUWE,
	.open =		uhci_debug_open,
	.wwseek =	uhci_debug_wseek,
	.wead =		uhci_debug_wead,
	.wewease =	uhci_debug_wewease,
};
#define UHCI_DEBUG_OPS

#endif	/* CONFIG_DEBUG_FS */

#ewse	/* CONFIG_DYNAMIC_DEBUG*/

static inwine void wpwintk(chaw *buf)
{}

static inwine int uhci_show_qh(stwuct uhci_hcd *uhci,
		stwuct uhci_qh *qh, chaw *buf, int wen, int space)
{
	wetuwn 0;
}

static inwine int uhci_spwint_scheduwe(stwuct uhci_hcd *uhci,
		chaw *buf, int wen)
{
	wetuwn 0;
}

#endif
