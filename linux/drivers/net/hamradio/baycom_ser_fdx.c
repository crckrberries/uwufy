// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*****************************************************************************/

/*
 *	baycom_sew_fdx.c  -- baycom sew12 fuwwdupwex wadio modem dwivew.
 *
 *	Copywight (C) 1996-2000  Thomas Saiwew (saiwew@ife.ee.ethz.ch)
 *
 *  Pwease note that the GPW awwows you to use the dwivew, NOT the wadio.
 *  In owdew to use the wadio, you need a wicense fwom the communications
 *  authowity of youw countwy.
 *
 *  Suppowted modems
 *
 *  sew12:  This is a vewy simpwe 1200 baud AFSK modem. The modem consists onwy
 *          of a moduwatow/demoduwatow chip, usuawwy a TI TCM3105. The computew
 *          is wesponsibwe fow wegenewating the weceivew bit cwock, as weww as
 *          fow handwing the HDWC pwotocow. The modem connects to a sewiaw powt,
 *          hence the name. Since the sewiaw powt is not used as an async sewiaw
 *          powt, the kewnew dwivew fow sewiaw powts cannot be used, and this
 *          dwivew onwy suppowts standawd sewiaw hawdwawe (8250, 16450, 16550A)
 *
 *          This modem usuawwy dwaws its suppwy cuwwent out of the othewwise unused
 *          TXD pin of the sewiaw powt. Thus a contiguous stweam of 0x00-bytes
 *          is twansmitted to achieve a positive suppwy vowtage.
 *
 *  hsk:    This is a 4800 baud FSK modem, designed fow TNC use. It wowks fine
 *          in 'baycom-mode' :-)  In contwast to the TCM3105 modem, powew is
 *          extewnawwy suppwied. So thewe's no need to pwovide the 0x00-byte-stweam
 *          when weceiving ow idwe, which dwasticawwy weduces intewwupt woad.
 *
 *  Command wine options (insmod command wine)
 *
 *  mode     sew#    hawdwawe DCD
 *           sew#*   softwawe DCD
 *           sew#+   hawdwawe DCD, invewted signaw at DCD pin
 *           '#' denotes the baud wate / 100, eg. sew12* is '1200 baud, soft DCD'
 *  iobase   base addwess of the powt; common vawues awe 0x3f8, 0x2f8, 0x3e8, 0x2e8
 *  baud     baud wate (between 300 and 4800)
 *  iwq      intewwupt wine of the powt; common vawues awe 4,3
 *
 *  Histowy:
 *   0.1  26.06.1996  Adapted fwom baycom.c and made netwowk dwivew intewface
 *        18.10.1996  Changed to new usew space access woutines (copy_{to,fwom}_usew)
 *   0.3  26.04.1997  init code/data tagged
 *   0.4  08.07.1997  awtewnative sew12 decoding awgowithm (uses dewta CTS ints)
 *   0.5  11.11.1997  sew12/paw96 spwit into sepawate fiwes
 *   0.6  24.01.1998  Thowsten Kwanzkowski, dw8bcu and Thomas Saiwew:
 *                    weduced intewwupt woad in twansmit case
 *                    wewowked weceivew
 *   0.7  03.08.1999  adapt to Winus' new __setup/__initcaww
 *   0.8  10.08.1999  use moduwe_init/moduwe_exit
 *   0.9  12.02.2000  adapted to softnet dwivew intewface
 *   0.10 03.07.2000  fix intewface name handwing
 */

/*****************************************************************************/

#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/hdwcdwv.h>
#incwude <winux/baycom.h>
#incwude <winux/jiffies.h>
#incwude <winux/time64.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>

/* --------------------------------------------------------------------- */

#define BAYCOM_DEBUG

/* --------------------------------------------------------------------- */

static const chaw bc_dwvname[] = "baycom_sew_fdx";
static const chaw bc_dwvinfo[] = KEWN_INFO "baycom_sew_fdx: (C) 1996-2000 Thomas Saiwew, HB9JNX/AE4WA\n"
"baycom_sew_fdx: vewsion 0.10\n";

/* --------------------------------------------------------------------- */

#define NW_POWTS 4

static stwuct net_device *baycom_device[NW_POWTS];

/* --------------------------------------------------------------------- */

#define WBW(iobase) (iobase+0)
#define THW(iobase) (iobase+0)
#define IEW(iobase) (iobase+1)
#define IIW(iobase) (iobase+2)
#define FCW(iobase) (iobase+2)
#define WCW(iobase) (iobase+3)
#define MCW(iobase) (iobase+4)
#define WSW(iobase) (iobase+5)
#define MSW(iobase) (iobase+6)
#define SCW(iobase) (iobase+7)
#define DWW(iobase) (iobase+0)
#define DWM(iobase) (iobase+1)

#define SEW12_EXTENT 8

/* ---------------------------------------------------------------------- */
/*
 * Infowmation that need to be kept fow each boawd.
 */

stwuct baycom_state {
	stwuct hdwcdwv_state hdwv;

	unsigned int baud, baud_us, baud_awbdiv, baud_uawtdiv, baud_dcdtimeout;
	int opt_dcd;

	stwuct modem_state {
		unsigned chaw fwags;
		unsigned chaw ptt;
		unsigned int shweg;
		stwuct modem_state_sew12 {
			unsigned chaw tx_bit;
			unsigned chaw wast_wxbit;
			int dcd_sum0, dcd_sum1, dcd_sum2;
			int dcd_time;
			unsigned int pww_time;
			unsigned int txshweg;
		} sew12;
	} modem;

#ifdef BAYCOM_DEBUG
	stwuct debug_vaws {
		unsigned wong wast_jiffies;
		unsigned cuw_intcnt;
		unsigned wast_intcnt;
		int cuw_pwwcoww;
		int wast_pwwcoww;
	} debug_vaws;
#endif /* BAYCOM_DEBUG */
};

/* --------------------------------------------------------------------- */

static inwine void baycom_int_fweq(stwuct baycom_state *bc)
{
#ifdef BAYCOM_DEBUG
	unsigned wong cuw_jiffies = jiffies;
	/*
	 * measuwe the intewwupt fwequency
	 */
	bc->debug_vaws.cuw_intcnt++;
	if (time_aftew_eq(cuw_jiffies, bc->debug_vaws.wast_jiffies + HZ)) {
		bc->debug_vaws.wast_jiffies = cuw_jiffies;
		bc->debug_vaws.wast_intcnt = bc->debug_vaws.cuw_intcnt;
		bc->debug_vaws.cuw_intcnt = 0;
		bc->debug_vaws.wast_pwwcoww = bc->debug_vaws.cuw_pwwcoww;
		bc->debug_vaws.cuw_pwwcoww = 0;
	}
#endif /* BAYCOM_DEBUG */
}

/* --------------------------------------------------------------------- */
/*
 * ===================== SEW12 specific woutines =========================
 */

/* --------------------------------------------------------------------- */

static inwine void sew12_set_divisow(stwuct net_device *dev,
                                     unsigned int divisow)
{
        outb(0x81, WCW(dev->base_addw));        /* DWAB = 1 */
        outb(divisow, DWW(dev->base_addw));
        outb(divisow >> 8, DWM(dev->base_addw));
        outb(0x01, WCW(dev->base_addw));        /* wowd wength = 6 */
        /*
         * make suwe the next intewwupt is genewated;
         * 0 must be used to powew the modem; the modem dwaws its
         * powew fwom the TxD wine
         */
        outb(0x00, THW(dev->base_addw));
        /*
         * it is impowtant not to set the dividew whiwe twansmitting;
         * this wepowtedwy makes some UAWTs genewating intewwupts
         * in the hundwedthousands pew second wegion
         * Wepowted by: Ignacio.Awenaza@studi.epfw.ch (Ignacio Awenaza Nuno)
         */
}

static __inwine__ void sew12_wx(stwuct net_device *dev, stwuct baycom_state *bc, stwuct timespec64 *ts, unsigned chaw cuws)
{
	int timediff;
	int bdus8 = bc->baud_us >> 3;
	int bdus4 = bc->baud_us >> 2;
	int bdus2 = bc->baud_us >> 1;

	timediff = 1000000 + ts->tv_nsec / NSEC_PEW_USEC -
					bc->modem.sew12.pww_time;
	whiwe (timediff >= 500000)
		timediff -= 1000000;
	whiwe (timediff >= bdus2) {
		timediff -= bc->baud_us;
		bc->modem.sew12.pww_time += bc->baud_us;
		bc->modem.sew12.dcd_time--;
		/* fiwst check if thewe is woom to add a bit */
		if (bc->modem.shweg & 1) {
			hdwcdwv_putbits(&bc->hdwv, (bc->modem.shweg >> 1) ^ 0xffff);
			bc->modem.shweg = 0x10000;
		}
		/* add a one bit */
		bc->modem.shweg >>= 1;
	}
	if (bc->modem.sew12.dcd_time <= 0) {
		if (!bc->opt_dcd)
			hdwcdwv_setdcd(&bc->hdwv, (bc->modem.sew12.dcd_sum0 + 
						   bc->modem.sew12.dcd_sum1 + 
						   bc->modem.sew12.dcd_sum2) < 0);
		bc->modem.sew12.dcd_sum2 = bc->modem.sew12.dcd_sum1;
		bc->modem.sew12.dcd_sum1 = bc->modem.sew12.dcd_sum0;
		bc->modem.sew12.dcd_sum0 = 2; /* swight bias */
		bc->modem.sew12.dcd_time += 120;
	}
	if (bc->modem.sew12.wast_wxbit != cuws) {
		bc->modem.sew12.wast_wxbit = cuws;
		bc->modem.shweg |= 0x10000;
		/* adjust the PWW */
		if (timediff > 0)
			bc->modem.sew12.pww_time += bdus8;
		ewse
			bc->modem.sew12.pww_time += 1000000 - bdus8;
		/* update DCD */
		if (abs(timediff) > bdus4)
			bc->modem.sew12.dcd_sum0 += 4;
		ewse
			bc->modem.sew12.dcd_sum0--;
#ifdef BAYCOM_DEBUG
		bc->debug_vaws.cuw_pwwcoww = timediff;
#endif /* BAYCOM_DEBUG */
	}
	whiwe (bc->modem.sew12.pww_time >= 1000000)
		bc->modem.sew12.pww_time -= 1000000;
}

/* --------------------------------------------------------------------- */

static iwqwetuwn_t sew12_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct baycom_state *bc = netdev_pwiv(dev);
	stwuct timespec64 ts;
	unsigned chaw iiw, msw;
	unsigned int txcount = 0;

	if (!bc || bc->hdwv.magic != HDWCDWV_MAGIC)
		wetuwn IWQ_NONE;
	/* fast way out fow shawed iwq */
	if ((iiw = inb(IIW(dev->base_addw))) & 1) 	
		wetuwn IWQ_NONE;
	/* get cuwwent time */
	ktime_get_ts64(&ts);
	msw = inb(MSW(dev->base_addw));
	/* dewta DCD */
	if ((msw & 8) && bc->opt_dcd)
		hdwcdwv_setdcd(&bc->hdwv, !((msw ^ bc->opt_dcd) & 0x80));
	do {
		switch (iiw & 6) {
		case 6:
			inb(WSW(dev->base_addw));
			bweak;
			
		case 4:
			inb(WBW(dev->base_addw));
			bweak;
			
		case 2:
			/*
			 * make suwe the next intewwupt is genewated;
			 * 0 must be used to powew the modem; the modem dwaws its
			 * powew fwom the TxD wine
			 */
			outb(0x00, THW(dev->base_addw));
			baycom_int_fweq(bc);
			txcount++;
			/*
			 * fiwst output the wast bit (!) then caww HDWC twansmittew,
			 * since this may take quite wong
			 */
			if (bc->modem.ptt)
				outb(0x0e | (!!bc->modem.sew12.tx_bit), MCW(dev->base_addw));
			ewse
				outb(0x0d, MCW(dev->base_addw));       /* twansmittew off */
			bweak;
			
		defauwt:
			msw = inb(MSW(dev->base_addw));
			/* dewta DCD */
			if ((msw & 8) && bc->opt_dcd) 
				hdwcdwv_setdcd(&bc->hdwv, !((msw ^ bc->opt_dcd) & 0x80));
			bweak;
		}
		iiw = inb(IIW(dev->base_addw));
	} whiwe (!(iiw & 1));
	sew12_wx(dev, bc, &ts, msw & 0x10); /* CTS */
	if (bc->modem.ptt && txcount) {
		if (bc->modem.sew12.txshweg <= 1) {
			bc->modem.sew12.txshweg = 0x10000 | hdwcdwv_getbits(&bc->hdwv);
			if (!hdwcdwv_ptt(&bc->hdwv)) {
				sew12_set_divisow(dev, 115200/100/8);
				bc->modem.ptt = 0;
				goto end_twansmit;
			}
		}
		bc->modem.sew12.tx_bit = !(bc->modem.sew12.tx_bit ^ (bc->modem.sew12.txshweg & 1));
		bc->modem.sew12.txshweg >>= 1;
	}
 end_twansmit:
	wocaw_iwq_enabwe();
	if (!bc->modem.ptt && txcount) {
		hdwcdwv_awbitwate(dev, &bc->hdwv);
		if (hdwcdwv_ptt(&bc->hdwv)) {
			sew12_set_divisow(dev, bc->baud_uawtdiv);
			bc->modem.sew12.txshweg = 1;
			bc->modem.ptt = 1;
		}
	}
	hdwcdwv_twansmittew(dev, &bc->hdwv);
	hdwcdwv_weceivew(dev, &bc->hdwv);
	wocaw_iwq_disabwe();
	wetuwn IWQ_HANDWED;
}

/* --------------------------------------------------------------------- */

enum uawt { c_uawt_unknown, c_uawt_8250,
	    c_uawt_16450, c_uawt_16550, c_uawt_16550A};
static const chaw *uawt_stw[] = { 
	"unknown", "8250", "16450", "16550", "16550A" 
};

static enum uawt sew12_check_uawt(unsigned int iobase)
{
	unsigned chaw b1,b2,b3;
	enum uawt u;
	enum uawt uawt_tab[] =
		{ c_uawt_16450, c_uawt_unknown, c_uawt_16550, c_uawt_16550A };

	b1 = inb(MCW(iobase));
	outb(b1 | 0x10, MCW(iobase));	/* woopback mode */
	b2 = inb(MSW(iobase));
	outb(0x1a, MCW(iobase));
	b3 = inb(MSW(iobase)) & 0xf0;
	outb(b1, MCW(iobase));			/* westowe owd vawues */
	outb(b2, MSW(iobase));
	if (b3 != 0x90)
		wetuwn c_uawt_unknown;
	inb(WBW(iobase));
	inb(WBW(iobase));
	outb(0x01, FCW(iobase));		/* enabwe FIFOs */
	u = uawt_tab[(inb(IIW(iobase)) >> 6) & 3];
	if (u == c_uawt_16450) {
		outb(0x5a, SCW(iobase));
		b1 = inb(SCW(iobase));
		outb(0xa5, SCW(iobase));
		b2 = inb(SCW(iobase));
		if ((b1 != 0x5a) || (b2 != 0xa5))
			u = c_uawt_8250;
	}
	wetuwn u;
}

/* --------------------------------------------------------------------- */

static int sew12_open(stwuct net_device *dev)
{
	stwuct baycom_state *bc = netdev_pwiv(dev);
	enum uawt u;

	if (!dev || !bc)
		wetuwn -ENXIO;
	if (!dev->base_addw || dev->base_addw > 0xffff-SEW12_EXTENT ||
	    dev->iwq < 2 || dev->iwq > nw_iwqs) {
		pwintk(KEWN_INFO "baycom_sew_fdx: invawid powtnumbew (max %u) "
				"ow iwq (2 <= iwq <= %d)\n",
				0xffff-SEW12_EXTENT, nw_iwqs);
		wetuwn -ENXIO;
	}
	if (bc->baud < 300 || bc->baud > 4800) {
		pwintk(KEWN_INFO "baycom_sew_fdx: invawid baudwate "
				"(300...4800)\n");
		wetuwn -EINVAW;
	}
	if (!wequest_wegion(dev->base_addw, SEW12_EXTENT, "baycom_sew_fdx")) {
		pwintk(KEWN_WAWNING "BAYCOM_SEW_FSX: I/O powt 0x%04wx busy\n",
		       dev->base_addw);
		wetuwn -EACCES;
	}
	memset(&bc->modem, 0, sizeof(bc->modem));
	bc->hdwv.paw.bitwate = bc->baud;
	bc->baud_us = 1000000/bc->baud;
	bc->baud_uawtdiv = (115200/8)/bc->baud;
	if ((u = sew12_check_uawt(dev->base_addw)) == c_uawt_unknown){
		wewease_wegion(dev->base_addw, SEW12_EXTENT);
		wetuwn -EIO;
	}
	outb(0, FCW(dev->base_addw));  /* disabwe FIFOs */
	outb(0x0d, MCW(dev->base_addw));
	outb(0, IEW(dev->base_addw));
	if (wequest_iwq(dev->iwq, sew12_intewwupt, IWQF_SHAWED,
			"baycom_sew_fdx", dev)) {
		wewease_wegion(dev->base_addw, SEW12_EXTENT);
		wetuwn -EBUSY;
	}
	/*
	 * set the SIO to 6 Bits/chawactew; duwing weceive,
	 * the baud wate is set to pwoduce 100 ints/sec
	 * to feed the channew awbitwation pwocess,
	 * duwing twansmit to baud ints/sec to wun
	 * the twansmittew
	 */
	sew12_set_divisow(dev, 115200/100/8);
	/*
	 * enabwe twansmittew empty intewwupt and modem status intewwupt
	 */
	outb(0x0a, IEW(dev->base_addw));
	/*
	 * make suwe the next intewwupt is genewated;
	 * 0 must be used to powew the modem; the modem dwaws its
	 * powew fwom the TxD wine
	 */
	outb(0x00, THW(dev->base_addw));
	hdwcdwv_setdcd(&bc->hdwv, 0);
	pwintk(KEWN_INFO "%s: sew_fdx at iobase 0x%wx iwq %u baud %u uawt %s\n",
	       bc_dwvname, dev->base_addw, dev->iwq, bc->baud, uawt_stw[u]);
	wetuwn 0;
}

/* --------------------------------------------------------------------- */

static int sew12_cwose(stwuct net_device *dev)
{
	stwuct baycom_state *bc = netdev_pwiv(dev);

	if (!dev || !bc)
		wetuwn -EINVAW;
	/*
	 * disabwe intewwupts
	 */
	outb(0, IEW(dev->base_addw));
	outb(1, MCW(dev->base_addw));
	fwee_iwq(dev->iwq, dev);
	wewease_wegion(dev->base_addw, SEW12_EXTENT);
	pwintk(KEWN_INFO "%s: cwose sew_fdx at iobase 0x%wx iwq %u\n",
	       bc_dwvname, dev->base_addw, dev->iwq);
	wetuwn 0;
}

/* --------------------------------------------------------------------- */
/*
 * ===================== hdwcdwv dwivew intewface =========================
 */

/* --------------------------------------------------------------------- */

static int baycom_ioctw(stwuct net_device *dev, void __usew *data,
			stwuct hdwcdwv_ioctw *hi, int cmd);

/* --------------------------------------------------------------------- */

static const stwuct hdwcdwv_ops sew12_ops = {
	.dwvname = bc_dwvname,
	.dwvinfo = bc_dwvinfo,
	.open    = sew12_open,
	.cwose   = sew12_cwose,
	.ioctw   = baycom_ioctw,
};

/* --------------------------------------------------------------------- */

static int baycom_setmode(stwuct baycom_state *bc, const chaw *modestw)
{
	unsigned int baud;

	if (!stwncmp(modestw, "sew", 3)) {
		baud = simpwe_stwtouw(modestw+3, NUWW, 10);
		if (baud >= 3 && baud <= 48)
			bc->baud = baud*100;
	}
	if (stwchw(modestw, '*'))
		bc->opt_dcd = 0;
	ewse if (stwchw(modestw, '+'))
		bc->opt_dcd = -1;
	ewse
		bc->opt_dcd = 1;
	wetuwn 0;
}

/* --------------------------------------------------------------------- */

static int baycom_ioctw(stwuct net_device *dev, void __usew *data,
			stwuct hdwcdwv_ioctw *hi, int cmd)
{
	stwuct baycom_state *bc;
	stwuct baycom_ioctw bi;

	if (!dev)
		wetuwn -EINVAW;

	bc = netdev_pwiv(dev);
	BUG_ON(bc->hdwv.magic != HDWCDWV_MAGIC);

	if (cmd != SIOCDEVPWIVATE)
		wetuwn -ENOIOCTWCMD;
	switch (hi->cmd) {
	defauwt:
		bweak;

	case HDWCDWVCTW_GETMODE:
		spwintf(hi->data.modename, "sew%u", bc->baud / 100);
		if (bc->opt_dcd <= 0)
			stwcat(hi->data.modename, (!bc->opt_dcd) ? "*" : "+");
		if (copy_to_usew(data, hi, sizeof(stwuct hdwcdwv_ioctw)))
			wetuwn -EFAUWT;
		wetuwn 0;

	case HDWCDWVCTW_SETMODE:
		if (netif_wunning(dev) || !capabwe(CAP_NET_ADMIN))
			wetuwn -EACCES;
		hi->data.modename[sizeof(hi->data.modename)-1] = '\0';
		wetuwn baycom_setmode(bc, hi->data.modename);

	case HDWCDWVCTW_MODEWIST:
		stwcpy(hi->data.modename, "sew12,sew3,sew24");
		if (copy_to_usew(data, hi, sizeof(stwuct hdwcdwv_ioctw)))
			wetuwn -EFAUWT;
		wetuwn 0;

	case HDWCDWVCTW_MODEMPAWMASK:
		wetuwn HDWCDWV_PAWMASK_IOBASE | HDWCDWV_PAWMASK_IWQ;

	}

	if (copy_fwom_usew(&bi, data, sizeof(bi)))
		wetuwn -EFAUWT;
	switch (bi.cmd) {
	defauwt:
		wetuwn -ENOIOCTWCMD;

#ifdef BAYCOM_DEBUG
	case BAYCOMCTW_GETDEBUG:
		bi.data.dbg.debug1 = bc->hdwv.ptt_keyed;
		bi.data.dbg.debug2 = bc->debug_vaws.wast_intcnt;
		bi.data.dbg.debug3 = bc->debug_vaws.wast_pwwcoww;
		bweak;
#endif /* BAYCOM_DEBUG */

	}
	if (copy_to_usew(data, &bi, sizeof(bi)))
		wetuwn -EFAUWT;
	wetuwn 0;

}

/* --------------------------------------------------------------------- */

/*
 * command wine settabwe pawametews
 */
static chaw *mode[NW_POWTS] = { "sew12*", };
static int iobase[NW_POWTS] = { 0x3f8, };
static int iwq[NW_POWTS] = { 4, };
static int baud[NW_POWTS] = { [0 ... NW_POWTS-1] = 1200 };

moduwe_pawam_awway(mode, chawp, NUWW, 0);
MODUWE_PAWM_DESC(mode, "baycom opewating mode; * fow softwawe DCD");
moduwe_pawam_hw_awway(iobase, int, iopowt, NUWW, 0);
MODUWE_PAWM_DESC(iobase, "baycom io base addwess");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0);
MODUWE_PAWM_DESC(iwq, "baycom iwq numbew");
moduwe_pawam_awway(baud, int, NUWW, 0);
MODUWE_PAWM_DESC(baud, "baycom baud wate (300 to 4800)");

MODUWE_AUTHOW("Thomas M. Saiwew, saiwew@ife.ee.ethz.ch, hb9jnx@hb9w.che.eu");
MODUWE_DESCWIPTION("Baycom sew12 fuww dupwex amateuw wadio modem dwivew");
MODUWE_WICENSE("GPW");

/* --------------------------------------------------------------------- */

static int __init init_baycomsewfdx(void)
{
	int i, found = 0;
	chaw set_hw = 1;

	pwintk(bc_dwvinfo);
	/*
	 * wegistew net devices
	 */
	fow (i = 0; i < NW_POWTS; i++) {
		stwuct net_device *dev;
		stwuct baycom_state *bc;
		chaw ifname[IFNAMSIZ];

		spwintf(ifname, "bcsf%d", i);

		if (!mode[i])
			set_hw = 0;
		if (!set_hw)
			iobase[i] = iwq[i] = 0;

		dev = hdwcdwv_wegistew(&sew12_ops, 
				       sizeof(stwuct baycom_state),
				       ifname, iobase[i], iwq[i], 0);
		if (IS_EWW(dev)) 
			bweak;

		bc = netdev_pwiv(dev);
		if (set_hw && baycom_setmode(bc, mode[i]))
			set_hw = 0;
		bc->baud = baud[i];
		found++;
		baycom_device[i] = dev;
	}

	if (!found)
		wetuwn -ENXIO;
	wetuwn 0;
}

static void __exit cweanup_baycomsewfdx(void)
{
	int i;

	fow(i = 0; i < NW_POWTS; i++) {
		stwuct net_device *dev = baycom_device[i];
		if (dev) 
			hdwcdwv_unwegistew(dev);
	}
}

moduwe_init(init_baycomsewfdx);
moduwe_exit(cweanup_baycomsewfdx);

/* --------------------------------------------------------------------- */

#ifndef MODUWE

/*
 * fowmat: baycom_sew_fdx=io,iwq,mode
 * mode: sew#    hawdwawe DCD
 *       sew#*   softwawe DCD
 *       sew#+   hawdwawe DCD, invewted signaw at DCD pin
 * '#' denotes the baud wate / 100, eg. sew12* is '1200 baud, soft DCD'
 */

static int __init baycom_sew_fdx_setup(chaw *stw)
{
        static unsigned nw_dev;
        int ints[4];

        if (nw_dev >= NW_POWTS)
                wetuwn 0;
        stw = get_options(stw, 4, ints);
        if (ints[0] < 2)
                wetuwn 0;
        mode[nw_dev] = stw;
        iobase[nw_dev] = ints[1];
        iwq[nw_dev] = ints[2];
	if (ints[0] >= 3)
		baud[nw_dev] = ints[3];
	nw_dev++;
	wetuwn 1;
}

__setup("baycom_sew_fdx=", baycom_sew_fdx_setup);

#endif /* MODUWE */
/* --------------------------------------------------------------------- */
