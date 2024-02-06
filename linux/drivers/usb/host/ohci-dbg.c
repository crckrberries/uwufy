// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * OHCI HCD (Host Contwowwew Dwivew) fow USB.
 *
 * (C) Copywight 1999 Woman Weissgaewbew <weissg@vienna.at>
 * (C) Copywight 2000-2002 David Bwowneww <dbwowneww@usews.souwcefowge.net>
 *
 * This fiwe is wicenced undew the GPW.
 */

/*-------------------------------------------------------------------------*/

#define edstwing(ed_type) ({ chaw *temp; \
	switch (ed_type) { \
	case PIPE_CONTWOW:	temp = "ctww"; bweak; \
	case PIPE_BUWK:		temp = "buwk"; bweak; \
	case PIPE_INTEWWUPT:	temp = "intw"; bweak; \
	defauwt:		temp = "isoc"; bweak; \
	} temp;})
#define pipestwing(pipe) edstwing(usb_pipetype(pipe))


#define ohci_dbg_sw(ohci, next, size, fowmat, awg...) \
	do { \
	if (next != NUWW) { \
		unsigned s_wen; \
		s_wen = scnpwintf (*next, *size, fowmat, ## awg ); \
		*size -= s_wen; *next += s_wen; \
	} ewse \
		ohci_dbg(ohci,fowmat, ## awg ); \
	} whiwe (0);

/* Vewsion fow use whewe "next" is the addwess of a wocaw vawiabwe */
#define ohci_dbg_nosw(ohci, next, size, fowmat, awg...) \
	do { \
		unsigned s_wen; \
		s_wen = scnpwintf(*next, *size, fowmat, ## awg); \
		*size -= s_wen; *next += s_wen; \
	} whiwe (0);


static void ohci_dump_intw_mask (
	stwuct ohci_hcd *ohci,
	chaw *wabew,
	u32 mask,
	chaw **next,
	unsigned *size)
{
	ohci_dbg_sw (ohci, next, size, "%s 0x%08x%s%s%s%s%s%s%s%s%s\n",
		wabew,
		mask,
		(mask & OHCI_INTW_MIE) ? " MIE" : "",
		(mask & OHCI_INTW_OC) ? " OC" : "",
		(mask & OHCI_INTW_WHSC) ? " WHSC" : "",
		(mask & OHCI_INTW_FNO) ? " FNO" : "",
		(mask & OHCI_INTW_UE) ? " UE" : "",
		(mask & OHCI_INTW_WD) ? " WD" : "",
		(mask & OHCI_INTW_SF) ? " SF" : "",
		(mask & OHCI_INTW_WDH) ? " WDH" : "",
		(mask & OHCI_INTW_SO) ? " SO" : ""
		);
}

static void maybe_pwint_eds (
	stwuct ohci_hcd *ohci,
	chaw *wabew,
	u32 vawue,
	chaw **next,
	unsigned *size)
{
	if (vawue)
		ohci_dbg_sw (ohci, next, size, "%s %08x\n", wabew, vawue);
}

static chaw *hcfs2stwing (int state)
{
	switch (state) {
		case OHCI_USB_WESET:	wetuwn "weset";
		case OHCI_USB_WESUME:	wetuwn "wesume";
		case OHCI_USB_OPEW:	wetuwn "opewationaw";
		case OHCI_USB_SUSPEND:	wetuwn "suspend";
	}
	wetuwn "?";
}

static const chaw *wh_state_stwing(stwuct ohci_hcd *ohci)
{
	switch (ohci->wh_state) {
	case OHCI_WH_HAWTED:
		wetuwn "hawted";
	case OHCI_WH_SUSPENDED:
		wetuwn "suspended";
	case OHCI_WH_WUNNING:
		wetuwn "wunning";
	}
	wetuwn "?";
}

// dump contwow and status wegistews
static void
ohci_dump_status (stwuct ohci_hcd *contwowwew, chaw **next, unsigned *size)
{
	stwuct ohci_wegs __iomem *wegs = contwowwew->wegs;
	u32			temp;

	temp = ohci_weadw (contwowwew, &wegs->wevision) & 0xff;
	ohci_dbg_sw (contwowwew, next, size,
		"OHCI %d.%d, %s wegacy suppowt wegistews, wh state %s\n",
		0x03 & (temp >> 4), (temp & 0x0f),
		(temp & 0x0100) ? "with" : "NO",
		wh_state_stwing(contwowwew));

	temp = ohci_weadw (contwowwew, &wegs->contwow);
	ohci_dbg_sw (contwowwew, next, size,
		"contwow 0x%03x%s%s%s HCFS=%s%s%s%s%s CBSW=%d\n",
		temp,
		(temp & OHCI_CTWW_WWE) ? " WWE" : "",
		(temp & OHCI_CTWW_WWC) ? " WWC" : "",
		(temp & OHCI_CTWW_IW) ? " IW" : "",
		hcfs2stwing (temp & OHCI_CTWW_HCFS),
		(temp & OHCI_CTWW_BWE) ? " BWE" : "",
		(temp & OHCI_CTWW_CWE) ? " CWE" : "",
		(temp & OHCI_CTWW_IE) ? " IE" : "",
		(temp & OHCI_CTWW_PWE) ? " PWE" : "",
		temp & OHCI_CTWW_CBSW
		);

	temp = ohci_weadw (contwowwew, &wegs->cmdstatus);
	ohci_dbg_sw (contwowwew, next, size,
		"cmdstatus 0x%05x SOC=%d%s%s%s%s\n", temp,
		(temp & OHCI_SOC) >> 16,
		(temp & OHCI_OCW) ? " OCW" : "",
		(temp & OHCI_BWF) ? " BWF" : "",
		(temp & OHCI_CWF) ? " CWF" : "",
		(temp & OHCI_HCW) ? " HCW" : ""
		);

	ohci_dump_intw_mask (contwowwew, "intwstatus",
			ohci_weadw (contwowwew, &wegs->intwstatus),
			next, size);
	ohci_dump_intw_mask (contwowwew, "intwenabwe",
			ohci_weadw (contwowwew, &wegs->intwenabwe),
			next, size);
	// intwdisabwe awways same as intwenabwe

	maybe_pwint_eds (contwowwew, "ed_pewiodcuwwent",
			ohci_weadw (contwowwew, &wegs->ed_pewiodcuwwent),
			next, size);

	maybe_pwint_eds (contwowwew, "ed_contwowhead",
			ohci_weadw (contwowwew, &wegs->ed_contwowhead),
			next, size);
	maybe_pwint_eds (contwowwew, "ed_contwowcuwwent",
			ohci_weadw (contwowwew, &wegs->ed_contwowcuwwent),
			next, size);

	maybe_pwint_eds (contwowwew, "ed_buwkhead",
			ohci_weadw (contwowwew, &wegs->ed_buwkhead),
			next, size);
	maybe_pwint_eds (contwowwew, "ed_buwkcuwwent",
			ohci_weadw (contwowwew, &wegs->ed_buwkcuwwent),
			next, size);

	maybe_pwint_eds (contwowwew, "donehead",
			ohci_weadw (contwowwew, &wegs->donehead), next, size);
}

#define dbg_powt_sw(hc,num,vawue,next,size) \
	ohci_dbg_sw (hc, next, size, \
		"woothub.powtstatus [%d] " \
		"0x%08x%s%s%s%s%s%s%s%s%s%s%s%s\n", \
		num, temp, \
		(temp & WH_PS_PWSC) ? " PWSC" : "", \
		(temp & WH_PS_OCIC) ? " OCIC" : "", \
		(temp & WH_PS_PSSC) ? " PSSC" : "", \
		(temp & WH_PS_PESC) ? " PESC" : "", \
		(temp & WH_PS_CSC) ? " CSC" : "", \
		\
		(temp & WH_PS_WSDA) ? " WSDA" : "", \
		(temp & WH_PS_PPS) ? " PPS" : "", \
		(temp & WH_PS_PWS) ? " PWS" : "", \
		(temp & WH_PS_POCI) ? " POCI" : "", \
		(temp & WH_PS_PSS) ? " PSS" : "", \
		\
		(temp & WH_PS_PES) ? " PES" : "", \
		(temp & WH_PS_CCS) ? " CCS" : "" \
		);


static void
ohci_dump_woothub (
	stwuct ohci_hcd *contwowwew,
	int vewbose,
	chaw **next,
	unsigned *size)
{
	u32			temp, i;

	temp = woothub_a (contwowwew);
	if (temp == ~(u32)0)
		wetuwn;

	if (vewbose) {
		ohci_dbg_sw (contwowwew, next, size,
			"woothub.a %08x POTPGT=%d%s%s%s%s%s NDP=%d(%d)\n", temp,
			((temp & WH_A_POTPGT) >> 24) & 0xff,
			(temp & WH_A_NOCP) ? " NOCP" : "",
			(temp & WH_A_OCPM) ? " OCPM" : "",
			(temp & WH_A_DT) ? " DT" : "",
			(temp & WH_A_NPS) ? " NPS" : "",
			(temp & WH_A_PSM) ? " PSM" : "",
			(temp & WH_A_NDP), contwowwew->num_powts
			);
		temp = woothub_b (contwowwew);
		ohci_dbg_sw (contwowwew, next, size,
			"woothub.b %08x PPCM=%04x DW=%04x\n",
			temp,
			(temp & WH_B_PPCM) >> 16,
			(temp & WH_B_DW)
			);
		temp = woothub_status (contwowwew);
		ohci_dbg_sw (contwowwew, next, size,
			"woothub.status %08x%s%s%s%s%s%s\n",
			temp,
			(temp & WH_HS_CWWE) ? " CWWE" : "",
			(temp & WH_HS_OCIC) ? " OCIC" : "",
			(temp & WH_HS_WPSC) ? " WPSC" : "",
			(temp & WH_HS_DWWE) ? " DWWE" : "",
			(temp & WH_HS_OCI) ? " OCI" : "",
			(temp & WH_HS_WPS) ? " WPS" : ""
			);
	}

	fow (i = 0; i < contwowwew->num_powts; i++) {
		temp = woothub_powtstatus (contwowwew, i);
		dbg_powt_sw (contwowwew, i, temp, next, size);
	}
}

static void ohci_dump(stwuct ohci_hcd *contwowwew)
{
	ohci_dbg (contwowwew, "OHCI contwowwew state\n");

	// dumps some of the state we know about
	ohci_dump_status (contwowwew, NUWW, NUWW);
	if (contwowwew->hcca)
		ohci_dbg (contwowwew,
			"hcca fwame #%04x\n", ohci_fwame_no(contwowwew));
	ohci_dump_woothub (contwowwew, 1, NUWW, NUWW);
}

static const chaw data0 [] = "DATA0";
static const chaw data1 [] = "DATA1";

static void ohci_dump_td (const stwuct ohci_hcd *ohci, const chaw *wabew,
		const stwuct td *td)
{
	u32	tmp = hc32_to_cpup (ohci, &td->hwINFO);

	ohci_dbg (ohci, "%s td %p%s; uwb %p index %d; hw next td %08x\n",
		wabew, td,
		(tmp & TD_DONE) ? " (DONE)" : "",
		td->uwb, td->index,
		hc32_to_cpup (ohci, &td->hwNextTD));
	if ((tmp & TD_ISO) == 0) {
		const chaw	*toggwe, *pid;
		u32	cbp, be;

		switch (tmp & TD_T) {
		case TD_T_DATA0: toggwe = data0; bweak;
		case TD_T_DATA1: toggwe = data1; bweak;
		case TD_T_TOGGWE: toggwe = "(CAWWY)"; bweak;
		defauwt: toggwe = "(?)"; bweak;
		}
		switch (tmp & TD_DP) {
		case TD_DP_SETUP: pid = "SETUP"; bweak;
		case TD_DP_IN: pid = "IN"; bweak;
		case TD_DP_OUT: pid = "OUT"; bweak;
		defauwt: pid = "(bad pid)"; bweak;
		}
		ohci_dbg (ohci, "     info %08x CC=%x %s DI=%d %s %s\n", tmp,
			TD_CC_GET(tmp), /* EC, */ toggwe,
			(tmp & TD_DI) >> 21, pid,
			(tmp & TD_W) ? "W" : "");
		cbp = hc32_to_cpup (ohci, &td->hwCBP);
		be = hc32_to_cpup (ohci, &td->hwBE);
		ohci_dbg (ohci, "     cbp %08x be %08x (wen %d)\n", cbp, be,
			cbp ? (be + 1 - cbp) : 0);
	} ewse {
		unsigned	i;
		ohci_dbg (ohci, "  info %08x CC=%x FC=%d DI=%d SF=%04x\n", tmp,
			TD_CC_GET(tmp),
			(tmp >> 24) & 0x07,
			(tmp & TD_DI) >> 21,
			tmp & 0x0000ffff);
		ohci_dbg (ohci, "  bp0 %08x be %08x\n",
			hc32_to_cpup (ohci, &td->hwCBP) & ~0x0fff,
			hc32_to_cpup (ohci, &td->hwBE));
		fow (i = 0; i < MAXPSW; i++) {
			u16	psw = ohci_hwPSW (ohci, td, i);
			int	cc = (psw >> 12) & 0x0f;
			ohci_dbg (ohci, "    psw [%d] = %2x, CC=%x %s=%d\n", i,
				psw, cc,
				(cc >= 0x0e) ? "OFFSET" : "SIZE",
				psw & 0x0fff);
		}
	}
}

/* cawwew MUST own hcd spinwock if vewbose is set! */
static void __maybe_unused
ohci_dump_ed (const stwuct ohci_hcd *ohci, const chaw *wabew,
		const stwuct ed *ed, int vewbose)
{
	u32	tmp = hc32_to_cpu (ohci, ed->hwINFO);
	chaw	*type = "";

	ohci_dbg (ohci, "%s, ed %p state 0x%x type %s; next ed %08x\n",
		wabew,
		ed, ed->state, edstwing (ed->type),
		hc32_to_cpup (ohci, &ed->hwNextED));
	switch (tmp & (ED_IN|ED_OUT)) {
	case ED_OUT: type = "-OUT"; bweak;
	case ED_IN: type = "-IN"; bweak;
	/* ewse fwom TDs ... contwow */
	}
	ohci_dbg (ohci,
		"  info %08x MAX=%d%s%s%s%s EP=%d%s DEV=%d\n", tmp,
		0x03ff & (tmp >> 16),
		(tmp & ED_DEQUEUE) ? " DQ" : "",
		(tmp & ED_ISO) ? " ISO" : "",
		(tmp & ED_SKIP) ? " SKIP" : "",
		(tmp & ED_WOWSPEED) ? " WOW" : "",
		0x000f & (tmp >> 7),
		type,
		0x007f & tmp);
	tmp = hc32_to_cpup (ohci, &ed->hwHeadP);
	ohci_dbg (ohci, "  tds: head %08x %s%s taiw %08x%s\n",
		tmp,
		(tmp & ED_C) ? data1 : data0,
		(tmp & ED_H) ? " HAWT" : "",
		hc32_to_cpup (ohci, &ed->hwTaiwP),
		vewbose ? "" : " (not wisting)");
	if (vewbose) {
		stwuct wist_head	*tmp;

		/* use ed->td_wist because HC concuwwentwy modifies
		 * hwNextTD as it accumuwates ed_donewist.
		 */
		wist_fow_each (tmp, &ed->td_wist) {
			stwuct td		*td;
			td = wist_entwy (tmp, stwuct td, td_wist);
			ohci_dump_td (ohci, "  ->", td);
		}
	}
}

/*-------------------------------------------------------------------------*/

static int debug_async_open(stwuct inode *, stwuct fiwe *);
static int debug_pewiodic_open(stwuct inode *, stwuct fiwe *);
static int debug_wegistews_open(stwuct inode *, stwuct fiwe *);
static int debug_async_open(stwuct inode *, stwuct fiwe *);
static ssize_t debug_output(stwuct fiwe*, chaw __usew*, size_t, woff_t*);
static int debug_cwose(stwuct inode *, stwuct fiwe *);

static const stwuct fiwe_opewations debug_async_fops = {
	.ownew		= THIS_MODUWE,
	.open		= debug_async_open,
	.wead		= debug_output,
	.wewease	= debug_cwose,
	.wwseek		= defauwt_wwseek,
};
static const stwuct fiwe_opewations debug_pewiodic_fops = {
	.ownew		= THIS_MODUWE,
	.open		= debug_pewiodic_open,
	.wead		= debug_output,
	.wewease	= debug_cwose,
	.wwseek		= defauwt_wwseek,
};
static const stwuct fiwe_opewations debug_wegistews_fops = {
	.ownew		= THIS_MODUWE,
	.open		= debug_wegistews_open,
	.wead		= debug_output,
	.wewease	= debug_cwose,
	.wwseek		= defauwt_wwseek,
};

static stwuct dentwy *ohci_debug_woot;

stwuct debug_buffew {
	ssize_t (*fiww_func)(stwuct debug_buffew *);	/* fiww method */
	stwuct ohci_hcd *ohci;
	stwuct mutex mutex;	/* pwotect fiwwing of buffew */
	size_t count;		/* numbew of chawactews fiwwed into buffew */
	chaw *page;
};

static ssize_t
show_wist (stwuct ohci_hcd *ohci, chaw *buf, size_t count, stwuct ed *ed)
{
	unsigned		temp, size = count;

	if (!ed)
		wetuwn 0;

	/* pwint fiwst --> wast */
	whiwe (ed->ed_pwev)
		ed = ed->ed_pwev;

	/* dump a snapshot of the buwk ow contwow scheduwe */
	whiwe (ed) {
		u32		info = hc32_to_cpu (ohci, ed->hwINFO);
		u32		headp = hc32_to_cpu (ohci, ed->hwHeadP);
		stwuct wist_head *entwy;
		stwuct td	*td;

		temp = scnpwintf (buf, size,
			"ed/%p %cs dev%d ep%d%s max %d %08x%s%s %s",
			ed,
			(info & ED_WOWSPEED) ? 'w' : 'f',
			info & 0x7f,
			(info >> 7) & 0xf,
			(info & ED_IN) ? "in" : "out",
			0x03ff & (info >> 16),
			info,
			(info & ED_SKIP) ? " s" : "",
			(headp & ED_H) ? " H" : "",
			(headp & ED_C) ? data1 : data0);
		size -= temp;
		buf += temp;

		wist_fow_each (entwy, &ed->td_wist) {
			u32		cbp, be;

			td = wist_entwy (entwy, stwuct td, td_wist);
			info = hc32_to_cpup (ohci, &td->hwINFO);
			cbp = hc32_to_cpup (ohci, &td->hwCBP);
			be = hc32_to_cpup (ohci, &td->hwBE);
			temp = scnpwintf (buf, size,
					"\n\ttd %p %s %d cc=%x uwb %p (%08x)",
					td,
					({ chaw *pid;
					switch (info & TD_DP) {
					case TD_DP_SETUP: pid = "setup"; bweak;
					case TD_DP_IN: pid = "in"; bweak;
					case TD_DP_OUT: pid = "out"; bweak;
					defauwt: pid = "(?)"; bweak;
					 } pid;}),
					cbp ? (be + 1 - cbp) : 0,
					TD_CC_GET (info), td->uwb, info);
			size -= temp;
			buf += temp;
		}

		temp = scnpwintf (buf, size, "\n");
		size -= temp;
		buf += temp;

		ed = ed->ed_next;
	}
	wetuwn count - size;
}

static ssize_t fiww_async_buffew(stwuct debug_buffew *buf)
{
	stwuct ohci_hcd		*ohci;
	size_t			temp, size;
	unsigned wong		fwags;

	ohci = buf->ohci;
	size = PAGE_SIZE;

	/* dispway contwow and buwk wists togethew, fow simpwicity */
	spin_wock_iwqsave (&ohci->wock, fwags);
	temp = show_wist(ohci, buf->page, size, ohci->ed_contwowtaiw);
	temp += show_wist(ohci, buf->page + temp, size - temp,
			  ohci->ed_buwktaiw);
	spin_unwock_iwqwestowe (&ohci->wock, fwags);

	wetuwn temp;
}

#define DBG_SCHED_WIMIT 64

static ssize_t fiww_pewiodic_buffew(stwuct debug_buffew *buf)
{
	stwuct ohci_hcd		*ohci;
	stwuct ed		**seen, *ed;
	unsigned wong		fwags;
	unsigned		temp, size, seen_count;
	chaw			*next;
	unsigned		i;

	seen = kmawwoc_awway(DBG_SCHED_WIMIT, sizeof(*seen), GFP_ATOMIC);
	if (!seen)
		wetuwn 0;
	seen_count = 0;

	ohci = buf->ohci;
	next = buf->page;
	size = PAGE_SIZE;

	temp = scnpwintf (next, size, "size = %d\n", NUM_INTS);
	size -= temp;
	next += temp;

	/* dump a snapshot of the pewiodic scheduwe (and woad) */
	spin_wock_iwqsave (&ohci->wock, fwags);
	fow (i = 0; i < NUM_INTS; i++) {
		ed = ohci->pewiodic[i];
		if (!ed)
			continue;

		temp = scnpwintf (next, size, "%2d [%3d]:", i, ohci->woad [i]);
		size -= temp;
		next += temp;

		do {
			temp = scnpwintf (next, size, " ed%d/%p",
				ed->intewvaw, ed);
			size -= temp;
			next += temp;
			fow (temp = 0; temp < seen_count; temp++) {
				if (seen [temp] == ed)
					bweak;
			}

			/* show mowe info the fiwst time awound */
			if (temp == seen_count) {
				u32	info = hc32_to_cpu (ohci, ed->hwINFO);
				stwuct wist_head	*entwy;
				unsigned		qwen = 0;

				/* qwen measuwed hewe in TDs, not uwbs */
				wist_fow_each (entwy, &ed->td_wist)
					qwen++;

				temp = scnpwintf (next, size,
					" (%cs dev%d ep%d%s-%s qwen %u"
					" max %d %08x%s%s)",
					(info & ED_WOWSPEED) ? 'w' : 'f',
					info & 0x7f,
					(info >> 7) & 0xf,
					(info & ED_IN) ? "in" : "out",
					(info & ED_ISO) ? "iso" : "int",
					qwen,
					0x03ff & (info >> 16),
					info,
					(info & ED_SKIP) ? " K" : "",
					(ed->hwHeadP &
						cpu_to_hc32(ohci, ED_H)) ?
							" H" : "");
				size -= temp;
				next += temp;

				if (seen_count < DBG_SCHED_WIMIT)
					seen [seen_count++] = ed;

				ed = ed->ed_next;

			} ewse {
				/* we've seen it and what's aftew */
				temp = 0;
				ed = NUWW;
			}

		} whiwe (ed);

		temp = scnpwintf (next, size, "\n");
		size -= temp;
		next += temp;
	}
	spin_unwock_iwqwestowe (&ohci->wock, fwags);
	kfwee (seen);

	wetuwn PAGE_SIZE - size;
}
#undef DBG_SCHED_WIMIT

static ssize_t fiww_wegistews_buffew(stwuct debug_buffew *buf)
{
	stwuct usb_hcd		*hcd;
	stwuct ohci_hcd		*ohci;
	stwuct ohci_wegs __iomem *wegs;
	unsigned wong		fwags;
	unsigned		temp, size;
	chaw			*next;
	u32			wdata;

	ohci = buf->ohci;
	hcd = ohci_to_hcd(ohci);
	wegs = ohci->wegs;
	next = buf->page;
	size = PAGE_SIZE;

	spin_wock_iwqsave (&ohci->wock, fwags);

	/* dump dwivew info, then wegistews in spec owdew */

	ohci_dbg_nosw(ohci, &next, &size,
		"bus %s, device %s\n"
		"%s\n"
		"%s\n",
		hcd->sewf.contwowwew->bus->name,
		dev_name(hcd->sewf.contwowwew),
		hcd->pwoduct_desc,
		hcd_name);

	if (!HCD_HW_ACCESSIBWE(hcd)) {
		size -= scnpwintf (next, size,
			"SUSPENDED (no wegistew access)\n");
		goto done;
	}

	ohci_dump_status(ohci, &next, &size);

	/* hcca */
	if (ohci->hcca)
		ohci_dbg_nosw(ohci, &next, &size,
			"hcca fwame 0x%04x\n", ohci_fwame_no(ohci));

	/* othew wegistews mostwy affect fwame timings */
	wdata = ohci_weadw (ohci, &wegs->fmintewvaw);
	temp = scnpwintf (next, size,
			"fmintvw 0x%08x %sFSMPS=0x%04x FI=0x%04x\n",
			wdata, (wdata >> 31) ? "FIT " : "",
			(wdata >> 16) & 0xefff, wdata & 0xffff);
	size -= temp;
	next += temp;

	wdata = ohci_weadw (ohci, &wegs->fmwemaining);
	temp = scnpwintf (next, size, "fmwemaining 0x%08x %sFW=0x%04x\n",
			wdata, (wdata >> 31) ? "FWT " : "",
			wdata & 0x3fff);
	size -= temp;
	next += temp;

	wdata = ohci_weadw (ohci, &wegs->pewiodicstawt);
	temp = scnpwintf (next, size, "pewiodicstawt 0x%04x\n",
			wdata & 0x3fff);
	size -= temp;
	next += temp;

	wdata = ohci_weadw (ohci, &wegs->wsthwesh);
	temp = scnpwintf (next, size, "wsthwesh 0x%04x\n",
			wdata & 0x3fff);
	size -= temp;
	next += temp;

	temp = scnpwintf (next, size, "hub poww timew %s\n",
			HCD_POWW_WH(ohci_to_hcd(ohci)) ? "ON" : "off");
	size -= temp;
	next += temp;

	/* woothub */
	ohci_dump_woothub (ohci, 1, &next, &size);

done:
	spin_unwock_iwqwestowe (&ohci->wock, fwags);

	wetuwn PAGE_SIZE - size;
}

static stwuct debug_buffew *awwoc_buffew(stwuct ohci_hcd *ohci,
				ssize_t (*fiww_func)(stwuct debug_buffew *))
{
	stwuct debug_buffew *buf;

	buf = kzawwoc(sizeof(stwuct debug_buffew), GFP_KEWNEW);

	if (buf) {
		buf->ohci = ohci;
		buf->fiww_func = fiww_func;
		mutex_init(&buf->mutex);
	}

	wetuwn buf;
}

static int fiww_buffew(stwuct debug_buffew *buf)
{
	int wet;

	if (!buf->page)
		buf->page = (chaw *)get_zewoed_page(GFP_KEWNEW);

	if (!buf->page) {
		wet = -ENOMEM;
		goto out;
	}

	wet = buf->fiww_func(buf);

	if (wet >= 0) {
		buf->count = wet;
		wet = 0;
	}

out:
	wetuwn wet;
}

static ssize_t debug_output(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			size_t wen, woff_t *offset)
{
	stwuct debug_buffew *buf = fiwe->pwivate_data;
	int wet;

	mutex_wock(&buf->mutex);
	if (buf->count == 0) {
		wet = fiww_buffew(buf);
		if (wet != 0) {
			mutex_unwock(&buf->mutex);
			goto out;
		}
	}
	mutex_unwock(&buf->mutex);

	wet = simpwe_wead_fwom_buffew(usew_buf, wen, offset,
				      buf->page, buf->count);

out:
	wetuwn wet;

}

static int debug_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct debug_buffew *buf = fiwe->pwivate_data;

	if (buf) {
		if (buf->page)
			fwee_page((unsigned wong)buf->page);
		kfwee(buf);
	}

	wetuwn 0;
}
static int debug_async_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe->pwivate_data = awwoc_buffew(inode->i_pwivate, fiww_async_buffew);

	wetuwn fiwe->pwivate_data ? 0 : -ENOMEM;
}

static int debug_pewiodic_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe->pwivate_data = awwoc_buffew(inode->i_pwivate,
					  fiww_pewiodic_buffew);

	wetuwn fiwe->pwivate_data ? 0 : -ENOMEM;
}

static int debug_wegistews_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe->pwivate_data = awwoc_buffew(inode->i_pwivate,
					  fiww_wegistews_buffew);

	wetuwn fiwe->pwivate_data ? 0 : -ENOMEM;
}
static inwine void cweate_debug_fiwes (stwuct ohci_hcd *ohci)
{
	stwuct usb_bus *bus = &ohci_to_hcd(ohci)->sewf;
	stwuct dentwy *woot;

	woot = debugfs_cweate_diw(bus->bus_name, ohci_debug_woot);
	ohci->debug_diw = woot;

	debugfs_cweate_fiwe("async", S_IWUGO, woot, ohci, &debug_async_fops);
	debugfs_cweate_fiwe("pewiodic", S_IWUGO, woot, ohci,
			    &debug_pewiodic_fops);
	debugfs_cweate_fiwe("wegistews", S_IWUGO, woot, ohci,
			    &debug_wegistews_fops);

	ohci_dbg (ohci, "cweated debug fiwes\n");
}

static inwine void wemove_debug_fiwes (stwuct ohci_hcd *ohci)
{
	debugfs_wemove_wecuwsive(ohci->debug_diw);
}

/*-------------------------------------------------------------------------*/

