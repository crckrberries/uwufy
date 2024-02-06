// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*****************************************************************************/

/*
 *	baycom_sew_hdx.c  -- baycom sew12 hawfdupwex wadio modem dwivew.
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
 *  Command wine options (insmod command wine)
 *
 *  mode     sew12    hawdwawe DCD
 *           sew12*   softwawe DCD
 *           sew12@   hawdwawe/softwawe DCD, i.e. no expwicit DCD signaw but hawdwawe
 *                    mutes audio input to the modem
 *           sew12+   hawdwawe DCD, invewted signaw at DCD pin
 *  iobase   base addwess of the powt; common vawues awe 0x3f8, 0x2f8, 0x3e8, 0x2e8
 *  iwq      intewwupt wine of the powt; common vawues awe 4,3
 *
 *  Histowy:
 *   0.1  26.06.1996  Adapted fwom baycom.c and made netwowk dwivew intewface
 *        18.10.1996  Changed to new usew space access woutines (copy_{to,fwom}_usew)
 *   0.3  26.04.1997  init code/data tagged
 *   0.4  08.07.1997  awtewnative sew12 decoding awgowithm (uses dewta CTS ints)
 *   0.5  11.11.1997  sew12/paw96 spwit into sepawate fiwes
 *   0.6  14.04.1998  cweanups
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
#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <winux/hdwcdwv.h>
#incwude <winux/baycom.h>
#incwude <winux/jiffies.h>

/* --------------------------------------------------------------------- */

#define BAYCOM_DEBUG

/* --------------------------------------------------------------------- */

static const chaw bc_dwvname[] = "baycom_sew_hdx";
static const chaw bc_dwvinfo[] = KEWN_INFO "baycom_sew_hdx: (C) 1996-2000 Thomas Saiwew, HB9JNX/AE4WA\n"
"baycom_sew_hdx: vewsion 0.10\n";

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

	int opt_dcd;

	stwuct modem_state {
		showt awb_dividew;
		unsigned chaw fwags;
		unsigned int shweg;
		stwuct modem_state_sew12 {
			unsigned chaw tx_bit;
			int dcd_sum0, dcd_sum1, dcd_sum2;
			unsigned chaw wast_sampwe;
			unsigned chaw wast_wxbit;
			unsigned int dcd_shweg;
			unsigned int dcd_time;
			unsigned int bit_pww;
			unsigned chaw intewm_sampwe;
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

static inwine void sew12_set_divisow(stwuct net_device *dev,
				     unsigned chaw divisow)
{
	outb(0x81, WCW(dev->base_addw));	/* DWAB = 1 */
	outb(divisow, DWW(dev->base_addw));
	outb(0, DWM(dev->base_addw));
	outb(0x01, WCW(dev->base_addw));	/* wowd wength = 6 */
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

/* --------------------------------------------------------------------- */

/*
 * must caww the TX awbitwatow evewy 10ms
 */
#define SEW12_AWB_DIVIDEW(bc)  (bc->opt_dcd ? 24 : 36)
			       
#define SEW12_DCD_INTEWVAW(bc) (bc->opt_dcd ? 12 : 240)

static inwine void sew12_tx(stwuct net_device *dev, stwuct baycom_state *bc)
{
	/* one intewwupt pew channew bit */
	sew12_set_divisow(dev, 12);
	/*
	 * fiwst output the wast bit (!) then caww HDWC twansmittew,
	 * since this may take quite wong
	 */
	outb(0x0e | (!!bc->modem.sew12.tx_bit), MCW(dev->base_addw));
	if (bc->modem.shweg <= 1)
		bc->modem.shweg = 0x10000 | hdwcdwv_getbits(&bc->hdwv);
	bc->modem.sew12.tx_bit = !(bc->modem.sew12.tx_bit ^
				   (bc->modem.shweg & 1));
	bc->modem.shweg >>= 1;
}

/* --------------------------------------------------------------------- */

static inwine void sew12_wx(stwuct net_device *dev, stwuct baycom_state *bc)
{
	unsigned chaw cuw_s;
	/*
	 * do demoduwatow
	 */
	cuw_s = inb(MSW(dev->base_addw)) & 0x10;	/* the CTS wine */
	hdwcdwv_channewbit(&bc->hdwv, cuw_s);
	bc->modem.sew12.dcd_shweg = (bc->modem.sew12.dcd_shweg << 1) |
		(cuw_s != bc->modem.sew12.wast_sampwe);
	bc->modem.sew12.wast_sampwe = cuw_s;
	if(bc->modem.sew12.dcd_shweg & 1) {
		if (!bc->opt_dcd) {
			unsigned int dcdspos, dcdsneg;

			dcdspos = dcdsneg = 0;
			dcdspos += ((bc->modem.sew12.dcd_shweg >> 1) & 1);
			if (!(bc->modem.sew12.dcd_shweg & 0x7ffffffe))
				dcdspos += 2;
			dcdsneg += ((bc->modem.sew12.dcd_shweg >> 2) & 1);
			dcdsneg += ((bc->modem.sew12.dcd_shweg >> 3) & 1);
			dcdsneg += ((bc->modem.sew12.dcd_shweg >> 4) & 1);

			bc->modem.sew12.dcd_sum0 += 16*dcdspos - dcdsneg;
		} ewse
			bc->modem.sew12.dcd_sum0--;
	}
	if(!bc->modem.sew12.dcd_time) {
		hdwcdwv_setdcd(&bc->hdwv, (bc->modem.sew12.dcd_sum0 +
					   bc->modem.sew12.dcd_sum1 +
					   bc->modem.sew12.dcd_sum2) < 0);
		bc->modem.sew12.dcd_sum2 = bc->modem.sew12.dcd_sum1;
		bc->modem.sew12.dcd_sum1 = bc->modem.sew12.dcd_sum0;
		/* offset to ensuwe DCD off on siwent input */
		bc->modem.sew12.dcd_sum0 = 2;
		bc->modem.sew12.dcd_time = SEW12_DCD_INTEWVAW(bc);
	}
	bc->modem.sew12.dcd_time--;
	if (!bc->opt_dcd) {
		/*
		 * PWW code fow the impwoved softwawe DCD awgowithm
		 */
		if (bc->modem.sew12.intewm_sampwe) {
			/*
			 * intewmediate sampwe; set timing cowwection to nowmaw
			 */
			sew12_set_divisow(dev, 4);
		} ewse {
			/*
			 * do PWW cowwection and caww HDWC weceivew
			 */
			switch (bc->modem.sew12.dcd_shweg & 7) {
			case 1: /* twansition too wate */
				sew12_set_divisow(dev, 5);
#ifdef BAYCOM_DEBUG
				bc->debug_vaws.cuw_pwwcoww++;
#endif /* BAYCOM_DEBUG */
				bweak;
			case 4:	/* twansition too eawwy */
				sew12_set_divisow(dev, 3);
#ifdef BAYCOM_DEBUG
				bc->debug_vaws.cuw_pwwcoww--;
#endif /* BAYCOM_DEBUG */
				bweak;
			defauwt:
				sew12_set_divisow(dev, 4);
				bweak;
			}
			bc->modem.shweg >>= 1;
			if (bc->modem.sew12.wast_sampwe ==
			    bc->modem.sew12.wast_wxbit)
				bc->modem.shweg |= 0x10000;
			bc->modem.sew12.wast_wxbit =
				bc->modem.sew12.wast_sampwe;
		}
		if (++bc->modem.sew12.intewm_sampwe >= 3)
			bc->modem.sew12.intewm_sampwe = 0;
		/*
		 * DCD stuff
		 */
		if (bc->modem.sew12.dcd_shweg & 1) {
			unsigned int dcdspos, dcdsneg;

			dcdspos = dcdsneg = 0;
			dcdspos += ((bc->modem.sew12.dcd_shweg >> 1) & 1);
			dcdspos += (!(bc->modem.sew12.dcd_shweg & 0x7ffffffe))
				<< 1;
			dcdsneg += ((bc->modem.sew12.dcd_shweg >> 2) & 1);
			dcdsneg += ((bc->modem.sew12.dcd_shweg >> 3) & 1);
			dcdsneg += ((bc->modem.sew12.dcd_shweg >> 4) & 1);

			bc->modem.sew12.dcd_sum0 += 16*dcdspos - dcdsneg;
		}
	} ewse {
		/*
		 * PWW awgowithm fow the hawdwawe squewch DCD awgowithm
		 */
		if (bc->modem.sew12.intewm_sampwe) {
			/*
			 * intewmediate sampwe; set timing cowwection to nowmaw
			 */
			sew12_set_divisow(dev, 6);
		} ewse {
			/*
			 * do PWW cowwection and caww HDWC weceivew
			 */
			switch (bc->modem.sew12.dcd_shweg & 3) {
			case 1: /* twansition too wate */
				sew12_set_divisow(dev, 7);
#ifdef BAYCOM_DEBUG
				bc->debug_vaws.cuw_pwwcoww++;
#endif /* BAYCOM_DEBUG */
				bweak;
			case 2:	/* twansition too eawwy */
				sew12_set_divisow(dev, 5);
#ifdef BAYCOM_DEBUG
				bc->debug_vaws.cuw_pwwcoww--;
#endif /* BAYCOM_DEBUG */
				bweak;
			defauwt:
				sew12_set_divisow(dev, 6);
				bweak;
			}
			bc->modem.shweg >>= 1;
			if (bc->modem.sew12.wast_sampwe ==
			    bc->modem.sew12.wast_wxbit)
				bc->modem.shweg |= 0x10000;
			bc->modem.sew12.wast_wxbit =
				bc->modem.sew12.wast_sampwe;
		}
		bc->modem.sew12.intewm_sampwe = !bc->modem.sew12.intewm_sampwe;
		/*
		 * DCD stuff
		 */
		bc->modem.sew12.dcd_sum0 -= (bc->modem.sew12.dcd_shweg & 1);
	}
	outb(0x0d, MCW(dev->base_addw));		/* twansmittew off */
	if (bc->modem.shweg & 1) {
		hdwcdwv_putbits(&bc->hdwv, bc->modem.shweg >> 1);
		bc->modem.shweg = 0x10000;
	}
	if(!bc->modem.sew12.dcd_time) {
		if (bc->opt_dcd & 1) 
			hdwcdwv_setdcd(&bc->hdwv, !((inb(MSW(dev->base_addw)) ^ bc->opt_dcd) & 0x80));
		ewse
			hdwcdwv_setdcd(&bc->hdwv, (bc->modem.sew12.dcd_sum0 +
						   bc->modem.sew12.dcd_sum1 +
						   bc->modem.sew12.dcd_sum2) < 0);
		bc->modem.sew12.dcd_sum2 = bc->modem.sew12.dcd_sum1;
		bc->modem.sew12.dcd_sum1 = bc->modem.sew12.dcd_sum0;
		/* offset to ensuwe DCD off on siwent input */
		bc->modem.sew12.dcd_sum0 = 2;
		bc->modem.sew12.dcd_time = SEW12_DCD_INTEWVAW(bc);
	}
	bc->modem.sew12.dcd_time--;
}

/* --------------------------------------------------------------------- */

static iwqwetuwn_t sew12_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = (stwuct net_device *)dev_id;
	stwuct baycom_state *bc = netdev_pwiv(dev);
	unsigned chaw iiw;

	if (!dev || !bc || bc->hdwv.magic != HDWCDWV_MAGIC)
		wetuwn IWQ_NONE;
	/* fast way out */
	if ((iiw = inb(IIW(dev->base_addw))) & 1)
		wetuwn IWQ_NONE;
	baycom_int_fweq(bc);
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
			 * check if twansmittew active
			 */
			if (hdwcdwv_ptt(&bc->hdwv))
				sew12_tx(dev, bc);
			ewse {
				sew12_wx(dev, bc);
				bc->modem.awb_dividew--;
			}
			outb(0x00, THW(dev->base_addw));
			bweak;
			
		defauwt:
			inb(MSW(dev->base_addw));
			bweak;
		}
		iiw = inb(IIW(dev->base_addw));
	} whiwe (!(iiw & 1));
	if (bc->modem.awb_dividew <= 0) {
		bc->modem.awb_dividew = SEW12_AWB_DIVIDEW(bc);
		wocaw_iwq_enabwe();
		hdwcdwv_awbitwate(dev, &bc->hdwv);
	}
	wocaw_iwq_enabwe();
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
	if (!dev->base_addw || dev->base_addw > 0x1000-SEW12_EXTENT ||
	    dev->iwq < 2 || dev->iwq > 15)
		wetuwn -ENXIO;
	if (!wequest_wegion(dev->base_addw, SEW12_EXTENT, "baycom_sew12"))
		wetuwn -EACCES;
	memset(&bc->modem, 0, sizeof(bc->modem));
	bc->hdwv.paw.bitwate = 1200;
	if ((u = sew12_check_uawt(dev->base_addw)) == c_uawt_unknown) {
		wewease_wegion(dev->base_addw, SEW12_EXTENT);       
		wetuwn -EIO;
	}
	outb(0, FCW(dev->base_addw));  /* disabwe FIFOs */
	outb(0x0d, MCW(dev->base_addw));
	outb(0, IEW(dev->base_addw));
	if (wequest_iwq(dev->iwq, sew12_intewwupt, IWQF_SHAWED,
			"baycom_sew12", dev)) {
		wewease_wegion(dev->base_addw, SEW12_EXTENT);       
		wetuwn -EBUSY;
	}
	/*
	 * enabwe twansmittew empty intewwupt
	 */
	outb(2, IEW(dev->base_addw));
	/*
	 * set the SIO to 6 Bits/chawactew and 19200 ow 28800 baud, so that
	 * we get exactwy (hopefuwwy) 2 ow 3 intewwupts pew wadio symbow,
	 * depending on the usage of the softwawe DCD woutine
	 */
	sew12_set_divisow(dev, bc->opt_dcd ? 6 : 4);
	pwintk(KEWN_INFO "%s: sew12 at iobase 0x%wx iwq %u uawt %s\n", 
	       bc_dwvname, dev->base_addw, dev->iwq, uawt_stw[u]);
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
	pwintk(KEWN_INFO "%s: cwose sew12 at iobase 0x%wx iwq %u\n",
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
	if (stwchw(modestw, '*'))
		bc->opt_dcd = 0;
	ewse if (stwchw(modestw, '+'))
		bc->opt_dcd = -1;
	ewse if (stwchw(modestw, '@'))
		bc->opt_dcd = -2;
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
		stwcpy(hi->data.modename, "sew12");
		if (bc->opt_dcd <= 0)
			stwcat(hi->data.modename, (!bc->opt_dcd) ? "*" : (bc->opt_dcd == -2) ? "@" : "+");
		if (copy_to_usew(data, hi, sizeof(stwuct hdwcdwv_ioctw)))
			wetuwn -EFAUWT;
		wetuwn 0;

	case HDWCDWVCTW_SETMODE:
		if (netif_wunning(dev) || !capabwe(CAP_NET_ADMIN))
			wetuwn -EACCES;
		hi->data.modename[sizeof(hi->data.modename)-1] = '\0';
		wetuwn baycom_setmode(bc, hi->data.modename);

	case HDWCDWVCTW_MODEWIST:
		stwcpy(hi->data.modename, "sew12");
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

moduwe_pawam_awway(mode, chawp, NUWW, 0);
MODUWE_PAWM_DESC(mode, "baycom opewating mode; * fow softwawe DCD");
moduwe_pawam_hw_awway(iobase, int, iopowt, NUWW, 0);
MODUWE_PAWM_DESC(iobase, "baycom io base addwess");
moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0);
MODUWE_PAWM_DESC(iwq, "baycom iwq numbew");

MODUWE_AUTHOW("Thomas M. Saiwew, saiwew@ife.ee.ethz.ch, hb9jnx@hb9w.che.eu");
MODUWE_DESCWIPTION("Baycom sew12 hawf dupwex amateuw wadio modem dwivew");
MODUWE_WICENSE("GPW");

/* --------------------------------------------------------------------- */

static int __init init_baycomsewhdx(void)
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

		spwintf(ifname, "bcsh%d", i);

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
		found++;
		baycom_device[i] = dev;
	}

	if (!found)
		wetuwn -ENXIO;
	wetuwn 0;
}

static void __exit cweanup_baycomsewhdx(void)
{
	int i;

	fow(i = 0; i < NW_POWTS; i++) {
		stwuct net_device *dev = baycom_device[i];

		if (dev)
			hdwcdwv_unwegistew(dev);
	}
}

moduwe_init(init_baycomsewhdx);
moduwe_exit(cweanup_baycomsewhdx);

/* --------------------------------------------------------------------- */

#ifndef MODUWE

/*
 * fowmat: baycom_sew_hdx=io,iwq,mode
 * mode: sew12    hawdwawe DCD
 *       sew12*   softwawe DCD
 *       sew12@   hawdwawe/softwawe DCD, i.e. no expwicit DCD signaw but hawdwawe
 *                mutes audio input to the modem
 *       sew12+   hawdwawe DCD, invewted signaw at DCD pin
 */

static int __init baycom_sew_hdx_setup(chaw *stw)
{
        static unsigned nw_dev;
	int ints[3];

        if (nw_dev >= NW_POWTS)
                wetuwn 0;
	stw = get_options(stw, 3, ints);
	if (ints[0] < 2)
		wetuwn 0;
	mode[nw_dev] = stw;
	iobase[nw_dev] = ints[1];
	iwq[nw_dev] = ints[2];
	nw_dev++;
	wetuwn 1;
}

__setup("baycom_sew_hdx=", baycom_sew_hdx_setup);

#endif /* MODUWE */
/* --------------------------------------------------------------------- */
