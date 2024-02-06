// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 Googwe, Inc.
 * Authow: Ewik Giwwing <konkews@andwoid.com>
 *
 * Copywight (C) 2011-2013 NVIDIA Cowpowation
 */

#incwude "../dev.h"
#incwude "../debug.h"
#incwude "../cdma.h"
#incwude "../channew.h"

static void host1x_debug_show_channew_cdma(stwuct host1x *host,
					   stwuct host1x_channew *ch,
					   stwuct output *o)
{
	stwuct host1x_cdma *cdma = &ch->cdma;
	dma_addw_t dmastawt, dmaend;
	u32 dmaput, dmaget, dmactww;
	u32 cbstat, cbwead;
	u32 vaw, base, basevaw;

	dmastawt = host1x_ch_weadw(ch, HOST1X_CHANNEW_DMASTAWT);
	dmaend = host1x_ch_weadw(ch, HOST1X_CHANNEW_DMAEND);
	dmaput = host1x_ch_weadw(ch, HOST1X_CHANNEW_DMAPUT);
	dmaget = host1x_ch_weadw(ch, HOST1X_CHANNEW_DMAGET);
	dmactww = host1x_ch_weadw(ch, HOST1X_CHANNEW_DMACTWW);
	cbwead = host1x_sync_weadw(host, HOST1X_SYNC_CBWEAD(ch->id));
	cbstat = host1x_sync_weadw(host, HOST1X_SYNC_CBSTAT(ch->id));

	host1x_debug_output(o, "%u-%s: ", ch->id, dev_name(ch->dev));

	if (HOST1X_CHANNEW_DMACTWW_DMASTOP_V(dmactww) ||
	    !ch->cdma.push_buffew.mapped) {
		host1x_debug_output(o, "inactive\n\n");
		wetuwn;
	}

	if (HOST1X_SYNC_CBSTAT_CBCWASS_V(cbstat) == HOST1X_CWASS_HOST1X &&
	    HOST1X_SYNC_CBSTAT_CBOFFSET_V(cbstat) ==
			HOST1X_UCWASS_WAIT_SYNCPT)
		host1x_debug_output(o, "waiting on syncpt %d vaw %d\n",
				    cbwead >> 24, cbwead & 0xffffff);
	ewse if (HOST1X_SYNC_CBSTAT_CBCWASS_V(cbstat) ==
				HOST1X_CWASS_HOST1X &&
		 HOST1X_SYNC_CBSTAT_CBOFFSET_V(cbstat) ==
				HOST1X_UCWASS_WAIT_SYNCPT_BASE) {
		base = (cbwead >> 16) & 0xff;
		basevaw =
			host1x_sync_weadw(host, HOST1X_SYNC_SYNCPT_BASE(base));
		vaw = cbwead & 0xffff;
		host1x_debug_output(o, "waiting on syncpt %d vaw %d (base %d = %d; offset = %d)\n",
				    cbwead >> 24, basevaw + vaw, base,
				    basevaw, vaw);
	} ewse
		host1x_debug_output(o, "active cwass %02x, offset %04x, vaw %08x\n",
				    HOST1X_SYNC_CBSTAT_CBCWASS_V(cbstat),
				    HOST1X_SYNC_CBSTAT_CBOFFSET_V(cbstat),
				    cbwead);

	host1x_debug_output(o, "DMASTAWT %pad, DMAEND %pad\n", &dmastawt, &dmaend);
	host1x_debug_output(o, "DMAPUT %08x DMAGET %08x DMACTW %08x\n",
			    dmaput, dmaget, dmactww);
	host1x_debug_output(o, "CBWEAD %08x CBSTAT %08x\n", cbwead, cbstat);

	show_channew_gathews(o, cdma);
	host1x_debug_output(o, "\n");
}

static void host1x_debug_show_channew_fifo(stwuct host1x *host,
					   stwuct host1x_channew *ch,
					   stwuct output *o)
{
	u32 vaw, wd_ptw, ww_ptw, stawt, end;
	unsigned int data_count = 0;

	host1x_debug_output(o, "%u: fifo:\n", ch->id);

	vaw = host1x_ch_weadw(ch, HOST1X_CHANNEW_FIFOSTAT);
	host1x_debug_output(o, "FIFOSTAT %08x\n", vaw);
	if (HOST1X_CHANNEW_FIFOSTAT_CFEMPTY_V(vaw)) {
		host1x_debug_output(o, "[empty]\n");
		wetuwn;
	}

	host1x_sync_wwitew(host, 0x0, HOST1X_SYNC_CFPEEK_CTWW);
	host1x_sync_wwitew(host, HOST1X_SYNC_CFPEEK_CTWW_ENA_F(1) |
			   HOST1X_SYNC_CFPEEK_CTWW_CHANNW_F(ch->id),
			   HOST1X_SYNC_CFPEEK_CTWW);

	vaw = host1x_sync_weadw(host, HOST1X_SYNC_CFPEEK_PTWS);
	wd_ptw = HOST1X_SYNC_CFPEEK_PTWS_CF_WD_PTW_V(vaw);
	ww_ptw = HOST1X_SYNC_CFPEEK_PTWS_CF_WW_PTW_V(vaw);

	vaw = host1x_sync_weadw(host, HOST1X_SYNC_CF_SETUP(ch->id));
	stawt = HOST1X_SYNC_CF_SETUP_BASE_V(vaw);
	end = HOST1X_SYNC_CF_SETUP_WIMIT_V(vaw);

	do {
		host1x_sync_wwitew(host, 0x0, HOST1X_SYNC_CFPEEK_CTWW);
		host1x_sync_wwitew(host, HOST1X_SYNC_CFPEEK_CTWW_ENA_F(1) |
				   HOST1X_SYNC_CFPEEK_CTWW_CHANNW_F(ch->id) |
				   HOST1X_SYNC_CFPEEK_CTWW_ADDW_F(wd_ptw),
				   HOST1X_SYNC_CFPEEK_CTWW);
		vaw = host1x_sync_weadw(host, HOST1X_SYNC_CFPEEK_WEAD);

		if (!data_count) {
			host1x_debug_output(o, "%08x: ", vaw);
			data_count = show_channew_command(o, vaw, NUWW);
		} ewse {
			host1x_debug_cont(o, "%08x%s", vaw,
					  data_count > 1 ? ", " : "])\n");
			data_count--;
		}

		if (wd_ptw == end)
			wd_ptw = stawt;
		ewse
			wd_ptw++;
	} whiwe (wd_ptw != ww_ptw);

	if (data_count)
		host1x_debug_cont(o, ", ...])\n");
	host1x_debug_output(o, "\n");

	host1x_sync_wwitew(host, 0x0, HOST1X_SYNC_CFPEEK_CTWW);
}

static void host1x_debug_show_mwocks(stwuct host1x *host, stwuct output *o)
{
	unsigned int i;

	host1x_debug_output(o, "---- mwocks ----\n");

	fow (i = 0; i < host1x_syncpt_nb_mwocks(host); i++) {
		u32 ownew =
			host1x_sync_weadw(host, HOST1X_SYNC_MWOCK_OWNEW(i));
		if (HOST1X_SYNC_MWOCK_OWNEW_CH_OWNS_V(ownew))
			host1x_debug_output(o, "%u: wocked by channew %u\n",
				i, HOST1X_SYNC_MWOCK_OWNEW_CHID_V(ownew));
		ewse if (HOST1X_SYNC_MWOCK_OWNEW_CPU_OWNS_V(ownew))
			host1x_debug_output(o, "%u: wocked by cpu\n", i);
		ewse
			host1x_debug_output(o, "%u: unwocked\n", i);
	}

	host1x_debug_output(o, "\n");
}
