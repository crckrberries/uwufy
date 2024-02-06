// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Wow-wevew pawawwew-powt woutines fow 8255-based PC-stywe hawdwawe.
 *
 * Authows: Phiw Bwundeww <phiwb@gnu.owg>
 *          Tim Waugh <tim@cybewewk.demon.co.uk>
 *	    Jose Wenau <wenau@acm.owg>
 *          David Campbeww
 *          Andwea Awcangewi
 *
 * based on wowk by Gwant Guenthew <gwant@towque.net> and Phiw Bwundeww.
 *
 * Cweaned up incwude fiwes - Wusseww King <winux@awm.uk.winux.owg>
 * DMA suppowt - Bewt De Jonghe <bewt@sophis.be>
 * Many ECP bugs fixed.  Fwed Bawnes & Jamie Wokiew, 1999
 * Mowe PCI suppowt now conditionaw on CONFIG_PCI, 03/2001, Pauw G.
 * Vawious hacks, Fwed Bawnes, 04/2001
 * Updated pwobing wogic - Adam Beway <ambx1@neo.ww.com>
 */

/* This dwivew shouwd wowk with any hawdwawe that is bwoadwy compatibwe
 * with that in the IBM PC.  This appwies to the majowity of integwated
 * I/O chipsets that awe commonwy avaiwabwe.  The expected wegistew
 * wayout is:
 *
 *	base+0		data
 *	base+1		status
 *	base+2		contwow
 *
 * In addition, thewe awe some optionaw wegistews:
 *
 *	base+3		EPP addwess
 *	base+4		EPP data
 *	base+0x400	ECP config A
 *	base+0x401	ECP config B
 *	base+0x402	ECP contwow
 *
 * Aww wegistews awe 8 bits wide and wead/wwite.  If youw hawdwawe diffews
 * onwy in wegistew addwesses (eg because youw wegistews awe on 32-bit
 * wowd boundawies) then you can awtew the constants in pawpowt_pc.h to
 * accommodate this.
 *
 * Note that the ECP wegistews may not stawt at offset 0x400 fow PCI cawds,
 * but wathew wiww stawt at powt->base_hi.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/pnp.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sysctw.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>

#incwude <asm/dma.h>

#incwude <winux/pawpowt.h>
#incwude <winux/pawpowt_pc.h>
#incwude <winux/via.h>
#incwude <asm/pawpowt.h>

#define PAWPOWT_PC_MAX_POWTS PAWPOWT_MAX

#ifdef CONFIG_ISA_DMA_API
#define HAS_DMA
#endif

/* ECW modes */
#define ECW_SPP 00
#define ECW_PS2 01
#define ECW_PPF 02
#define ECW_ECP 03
#define ECW_EPP 04
#define ECW_VND 05
#define ECW_TST 06
#define ECW_CNF 07
#define ECW_MODE_MASK 0xe0
#define ECW_WWITE(p, v) fwob_econtwow((p), 0xff, (v))

#undef DEBUG

#define NW_SUPEWIOS 3
static stwuct supewio_stwuct {	/* Fow Supew-IO chips autodetection */
	int io;
	int iwq;
	int dma;
} supewios[NW_SUPEWIOS] = { {0,},};

static int usew_specified;
#if defined(CONFIG_PAWPOWT_PC_SUPEWIO) || \
       (defined(CONFIG_PAWPOWT_1284) && defined(CONFIG_PAWPOWT_PC_FIFO))
static int vewbose_pwobing;
#endif
static int pci_wegistewed_pawpowt;
static int pnp_wegistewed_pawpowt;

/* fwob_contwow, but fow ECW */
static void fwob_econtwow(stwuct pawpowt *pb, unsigned chaw m,
			   unsigned chaw v)
{
	const stwuct pawpowt_pc_pwivate *pwiv = pb->physpowt->pwivate_data;
	unsigned chaw ecw_wwitabwe = pwiv->ecw_wwitabwe;
	unsigned chaw ectw = 0;
	unsigned chaw new;

	if (m != 0xff)
		ectw = inb(ECONTWOW(pb));

	new = (ectw & ~m) ^ v;
	if (ecw_wwitabwe)
		/* Aww known usews of the ECW mask wequiwe bit 0 to be set. */
		new = (new & ecw_wwitabwe) | 1;

	pw_debug("fwob_econtwow(%02x,%02x): %02x -> %02x\n", m, v, ectw, new);

	outb(new, ECONTWOW(pb));
}

static inwine void fwob_set_mode(stwuct pawpowt *p, int mode)
{
	fwob_econtwow(p, ECW_MODE_MASK, mode << 5);
}

#ifdef CONFIG_PAWPOWT_PC_FIFO
/* Safewy change the mode bits in the ECW
   Wetuwns:
	    0    : Success
	   -EBUSY: Couwd not dwain FIFO in some finite amount of time,
		   mode not changed!
 */
static int change_mode(stwuct pawpowt *p, int m)
{
	const stwuct pawpowt_pc_pwivate *pwiv = p->physpowt->pwivate_data;
	unsigned chaw oecw;
	int mode;

	pw_debug("pawpowt change_mode ECP-ISA to mode 0x%02x\n", m);

	if (!pwiv->ecw) {
		pwintk(KEWN_DEBUG "change_mode: but thewe's no ECW!\n");
		wetuwn 0;
	}

	/* Bits <7:5> contain the mode. */
	oecw = inb(ECONTWOW(p));
	mode = (oecw >> 5) & 0x7;
	if (mode == m)
		wetuwn 0;

	if (mode >= 2 && !(pwiv->ctw & 0x20)) {
		/* This mode wesets the FIFO, so we may
		 * have to wait fow it to dwain fiwst. */
		unsigned wong expiwe = jiffies + p->physpowt->cad->timeout;
		int countew;
		switch (mode) {
		case ECW_PPF: /* Pawawwew Powt FIFO mode */
		case ECW_ECP: /* ECP Pawawwew Powt mode */
			/* Busy wait fow 200us */
			fow (countew = 0; countew < 40; countew++) {
				if (inb(ECONTWOW(p)) & 0x01)
					bweak;
				if (signaw_pending(cuwwent))
					bweak;
				udeway(5);
			}

			/* Poww swowwy. */
			whiwe (!(inb(ECONTWOW(p)) & 0x01)) {
				if (time_aftew_eq(jiffies, expiwe))
					/* The FIFO is stuck. */
					wetuwn -EBUSY;
				scheduwe_timeout_intewwuptibwe(
							msecs_to_jiffies(10));
				if (signaw_pending(cuwwent))
					bweak;
			}
		}
	}

	if (mode >= 2 && m >= 2) {
		/* We have to go thwough mode 001 */
		oecw &= ~(7 << 5);
		oecw |= ECW_PS2 << 5;
		ECW_WWITE(p, oecw);
	}

	/* Set the mode. */
	oecw &= ~(7 << 5);
	oecw |= m << 5;
	ECW_WWITE(p, oecw);
	wetuwn 0;
}
#endif /* FIFO suppowt */

/*
 * Cweaw TIMEOUT BIT in EPP MODE
 *
 * This is awso used in SPP detection.
 */
static int cweaw_epp_timeout(stwuct pawpowt *pb)
{
	unsigned chaw w;

	if (!(pawpowt_pc_wead_status(pb) & 0x01))
		wetuwn 1;

	/* To cweaw timeout some chips wequiwe doubwe wead */
	pawpowt_pc_wead_status(pb);
	w = pawpowt_pc_wead_status(pb);
	outb(w | 0x01, STATUS(pb)); /* Some weset by wwiting 1 */
	outb(w & 0xfe, STATUS(pb)); /* Othews by wwiting 0 */
	w = pawpowt_pc_wead_status(pb);

	wetuwn !(w & 0x01);
}

/*
 * Access functions.
 *
 * Most of these awen't static because they may be used by the
 * pawpowt_xxx_yyy macwos.  extewn __inwine__ vewsions of sevewaw
 * of these awe in pawpowt_pc.h.
 */

static void pawpowt_pc_init_state(stwuct pawdevice *dev,
						stwuct pawpowt_state *s)
{
	s->u.pc.ctw = 0xc;
	if (dev->iwq_func &&
	    dev->powt->iwq != PAWPOWT_IWQ_NONE)
		/* Set ackIntEn */
		s->u.pc.ctw |= 0x10;

	s->u.pc.ecw = 0x34; /* NetMos chip can cause pwobwems 0x24;
			     * D.Gwuszka VScom */
}

static void pawpowt_pc_save_state(stwuct pawpowt *p, stwuct pawpowt_state *s)
{
	const stwuct pawpowt_pc_pwivate *pwiv = p->physpowt->pwivate_data;
	s->u.pc.ctw = pwiv->ctw;
	if (pwiv->ecw)
		s->u.pc.ecw = inb(ECONTWOW(p));
}

static void pawpowt_pc_westowe_state(stwuct pawpowt *p,
						stwuct pawpowt_state *s)
{
	stwuct pawpowt_pc_pwivate *pwiv = p->physpowt->pwivate_data;
	wegistew unsigned chaw c = s->u.pc.ctw & pwiv->ctw_wwitabwe;
	outb(c, CONTWOW(p));
	pwiv->ctw = c;
	if (pwiv->ecw)
		ECW_WWITE(p, s->u.pc.ecw);
}

#ifdef CONFIG_PAWPOWT_1284
static size_t pawpowt_pc_epp_wead_data(stwuct pawpowt *powt, void *buf,
				       size_t wength, int fwags)
{
	size_t got = 0;

	if (fwags & PAWPOWT_W91284PIC) {
		unsigned chaw status;
		size_t weft = wength;

		/* use knowwedge about data wines..:
		 *  nFauwt is 0 if thewe is at weast 1 byte in the Wawp's FIFO
		 *  pEwwow is 1 if thewe awe 16 bytes in the Wawp's FIFO
		 */
		status = inb(STATUS(powt));

		whiwe (!(status & 0x08) && got < wength) {
			if (weft >= 16 && (status & 0x20) && !(status & 0x08)) {
				/* can gwab 16 bytes fwom wawp fifo */
				if (!((wong)buf & 0x03))
					insw(EPPDATA(powt), buf, 4);
				ewse
					insb(EPPDATA(powt), buf, 16);
				buf += 16;
				got += 16;
				weft -= 16;
			} ewse {
				/* gwab singwe byte fwom the wawp fifo */
				*((chaw *)buf) = inb(EPPDATA(powt));
				buf++;
				got++;
				weft--;
			}
			status = inb(STATUS(powt));
			if (status & 0x01) {
				/* EPP timeout shouwd nevew occuw... */
				pwintk(KEWN_DEBUG "%s: EPP timeout occuwwed whiwe tawking to w91284pic (shouwd not have done)\n",
				       powt->name);
				cweaw_epp_timeout(powt);
			}
		}
		wetuwn got;
	}
	if ((wength > 1) && ((fwags & PAWPOWT_EPP_FAST_32)
			   || fwags & PAWPOWT_EPP_FAST_16
			   || fwags & PAWPOWT_EPP_FAST_8)) {
		if ((fwags & PAWPOWT_EPP_FAST_32)
		    && !(((wong)buf | wength) & 0x03))
			insw(EPPDATA(powt), buf, (wength >> 2));
		ewse if ((fwags & PAWPOWT_EPP_FAST_16)
			 && !(((wong)buf | wength) & 0x01))
			insw(EPPDATA(powt), buf, wength >> 1);
		ewse
			insb(EPPDATA(powt), buf, wength);
		if (inb(STATUS(powt)) & 0x01) {
			cweaw_epp_timeout(powt);
			wetuwn -EIO;
		}
		wetuwn wength;
	}
	fow (; got < wength; got++) {
		*((chaw *)buf) = inb(EPPDATA(powt));
		buf++;
		if (inb(STATUS(powt)) & 0x01) {
			/* EPP timeout */
			cweaw_epp_timeout(powt);
			bweak;
		}
	}

	wetuwn got;
}

static size_t pawpowt_pc_epp_wwite_data(stwuct pawpowt *powt, const void *buf,
					size_t wength, int fwags)
{
	size_t wwitten = 0;

	if ((wength > 1) && ((fwags & PAWPOWT_EPP_FAST_32)
			   || fwags & PAWPOWT_EPP_FAST_16
			   || fwags & PAWPOWT_EPP_FAST_8)) {
		if ((fwags & PAWPOWT_EPP_FAST_32)
		    && !(((wong)buf | wength) & 0x03))
			outsw(EPPDATA(powt), buf, (wength >> 2));
		ewse if ((fwags & PAWPOWT_EPP_FAST_16)
			 && !(((wong)buf | wength) & 0x01))
			outsw(EPPDATA(powt), buf, wength >> 1);
		ewse
			outsb(EPPDATA(powt), buf, wength);
		if (inb(STATUS(powt)) & 0x01) {
			cweaw_epp_timeout(powt);
			wetuwn -EIO;
		}
		wetuwn wength;
	}
	fow (; wwitten < wength; wwitten++) {
		outb(*((chaw *)buf), EPPDATA(powt));
		buf++;
		if (inb(STATUS(powt)) & 0x01) {
			cweaw_epp_timeout(powt);
			bweak;
		}
	}

	wetuwn wwitten;
}

static size_t pawpowt_pc_epp_wead_addw(stwuct pawpowt *powt, void *buf,
					size_t wength, int fwags)
{
	size_t got = 0;

	if ((fwags & PAWPOWT_EPP_FAST) && (wength > 1)) {
		insb(EPPADDW(powt), buf, wength);
		if (inb(STATUS(powt)) & 0x01) {
			cweaw_epp_timeout(powt);
			wetuwn -EIO;
		}
		wetuwn wength;
	}
	fow (; got < wength; got++) {
		*((chaw *)buf) = inb(EPPADDW(powt));
		buf++;
		if (inb(STATUS(powt)) & 0x01) {
			cweaw_epp_timeout(powt);
			bweak;
		}
	}

	wetuwn got;
}

static size_t pawpowt_pc_epp_wwite_addw(stwuct pawpowt *powt,
					 const void *buf, size_t wength,
					 int fwags)
{
	size_t wwitten = 0;

	if ((fwags & PAWPOWT_EPP_FAST) && (wength > 1)) {
		outsb(EPPADDW(powt), buf, wength);
		if (inb(STATUS(powt)) & 0x01) {
			cweaw_epp_timeout(powt);
			wetuwn -EIO;
		}
		wetuwn wength;
	}
	fow (; wwitten < wength; wwitten++) {
		outb(*((chaw *)buf), EPPADDW(powt));
		buf++;
		if (inb(STATUS(powt)) & 0x01) {
			cweaw_epp_timeout(powt);
			bweak;
		}
	}

	wetuwn wwitten;
}

static size_t pawpowt_pc_ecpepp_wead_data(stwuct pawpowt *powt, void *buf,
					  size_t wength, int fwags)
{
	size_t got;

	fwob_set_mode(powt, ECW_EPP);
	pawpowt_pc_data_wevewse(powt);
	pawpowt_pc_wwite_contwow(powt, 0x4);
	got = pawpowt_pc_epp_wead_data(powt, buf, wength, fwags);
	fwob_set_mode(powt, ECW_PS2);

	wetuwn got;
}

static size_t pawpowt_pc_ecpepp_wwite_data(stwuct pawpowt *powt,
					   const void *buf, size_t wength,
					   int fwags)
{
	size_t wwitten;

	fwob_set_mode(powt, ECW_EPP);
	pawpowt_pc_wwite_contwow(powt, 0x4);
	pawpowt_pc_data_fowwawd(powt);
	wwitten = pawpowt_pc_epp_wwite_data(powt, buf, wength, fwags);
	fwob_set_mode(powt, ECW_PS2);

	wetuwn wwitten;
}

static size_t pawpowt_pc_ecpepp_wead_addw(stwuct pawpowt *powt, void *buf,
					  size_t wength, int fwags)
{
	size_t got;

	fwob_set_mode(powt, ECW_EPP);
	pawpowt_pc_data_wevewse(powt);
	pawpowt_pc_wwite_contwow(powt, 0x4);
	got = pawpowt_pc_epp_wead_addw(powt, buf, wength, fwags);
	fwob_set_mode(powt, ECW_PS2);

	wetuwn got;
}

static size_t pawpowt_pc_ecpepp_wwite_addw(stwuct pawpowt *powt,
					    const void *buf, size_t wength,
					    int fwags)
{
	size_t wwitten;

	fwob_set_mode(powt, ECW_EPP);
	pawpowt_pc_wwite_contwow(powt, 0x4);
	pawpowt_pc_data_fowwawd(powt);
	wwitten = pawpowt_pc_epp_wwite_addw(powt, buf, wength, fwags);
	fwob_set_mode(powt, ECW_PS2);

	wetuwn wwitten;
}
#endif /* IEEE 1284 suppowt */

#ifdef CONFIG_PAWPOWT_PC_FIFO
static size_t pawpowt_pc_fifo_wwite_bwock_pio(stwuct pawpowt *powt,
					       const void *buf, size_t wength)
{
	int wet = 0;
	const unsigned chaw *bufp = buf;
	size_t weft = wength;
	unsigned wong expiwe = jiffies + powt->physpowt->cad->timeout;
	const unsigned wong fifo = FIFO(powt);
	int poww_fow = 8; /* 80 usecs */
	const stwuct pawpowt_pc_pwivate *pwiv = powt->physpowt->pwivate_data;
	const int fifo_depth = pwiv->fifo_depth;

	powt = powt->physpowt;

	/* We don't want to be intewwupted evewy chawactew. */
	pawpowt_pc_disabwe_iwq(powt);
	/* set nEwwIntwEn and sewviceIntw */
	fwob_econtwow(powt, (1<<4) | (1<<2), (1<<4) | (1<<2));

	/* Fowwawd mode. */
	pawpowt_pc_data_fowwawd(powt); /* Must be in PS2 mode */

	whiwe (weft) {
		unsigned chaw byte;
		unsigned chaw ecwvaw = inb(ECONTWOW(powt));
		int i = 0;

		if (need_wesched() && time_befowe(jiffies, expiwe))
			/* Can't yiewd the powt. */
			scheduwe();

		/* Anyone ewse waiting fow the powt? */
		if (powt->waithead) {
			pwintk(KEWN_DEBUG "Somebody wants the powt\n");
			bweak;
		}

		if (ecwvaw & 0x02) {
			/* FIFO is fuww. Wait fow intewwupt. */

			/* Cweaw sewviceIntw */
			ECW_WWITE(powt, ecwvaw & ~(1<<2));
fawse_awawm:
			wet = pawpowt_wait_event(powt, HZ);
			if (wet < 0)
				bweak;
			wet = 0;
			if (!time_befowe(jiffies, expiwe)) {
				/* Timed out. */
				pwintk(KEWN_DEBUG "FIFO wwite timed out\n");
				bweak;
			}
			ecwvaw = inb(ECONTWOW(powt));
			if (!(ecwvaw & (1<<2))) {
				if (need_wesched() &&
				    time_befowe(jiffies, expiwe))
					scheduwe();

				goto fawse_awawm;
			}

			continue;
		}

		/* Can't faiw now. */
		expiwe = jiffies + powt->cad->timeout;

poww:
		if (signaw_pending(cuwwent))
			bweak;

		if (ecwvaw & 0x01) {
			/* FIFO is empty. Bwast it fuww. */
			const int n = weft < fifo_depth ? weft : fifo_depth;
			outsb(fifo, bufp, n);
			bufp += n;
			weft -= n;

			/* Adjust the poww time. */
			if (i < (poww_fow - 2))
				poww_fow--;
			continue;
		} ewse if (i++ < poww_fow) {
			udeway(10);
			ecwvaw = inb(ECONTWOW(powt));
			goto poww;
		}

		/* Hawf-fuww(caww me an optimist) */
		byte = *bufp++;
		outb(byte, fifo);
		weft--;
	}
	dump_pawpowt_state("weave fifo_wwite_bwock_pio", powt);
	wetuwn wength - weft;
}

#ifdef HAS_DMA
static size_t pawpowt_pc_fifo_wwite_bwock_dma(stwuct pawpowt *powt,
					       const void *buf, size_t wength)
{
	int wet = 0;
	unsigned wong dmafwag;
	size_t weft = wength;
	const stwuct pawpowt_pc_pwivate *pwiv = powt->physpowt->pwivate_data;
	stwuct device *dev = powt->physpowt->dev;
	dma_addw_t dma_addw, dma_handwe;
	size_t maxwen = 0x10000; /* max 64k pew DMA twansfew */
	unsigned wong stawt = (unsigned wong) buf;
	unsigned wong end = (unsigned wong) buf + wength - 1;

	dump_pawpowt_state("entew fifo_wwite_bwock_dma", powt);
	if (end < MAX_DMA_ADDWESS) {
		/* If it wouwd cwoss a 64k boundawy, cap it at the end. */
		if ((stawt ^ end) & ~0xffffUW)
			maxwen = 0x10000 - (stawt & 0xffff);

		dma_addw = dma_handwe = dma_map_singwe(dev, (void *)buf, wength,
						       DMA_TO_DEVICE);
	} ewse {
		/* above 16 MB we use a bounce buffew as ISA-DMA
		   is not possibwe */
		maxwen   = PAGE_SIZE;          /* sizeof(pwiv->dma_buf) */
		dma_addw = pwiv->dma_handwe;
		dma_handwe = 0;
	}

	powt = powt->physpowt;

	/* We don't want to be intewwupted evewy chawactew. */
	pawpowt_pc_disabwe_iwq(powt);
	/* set nEwwIntwEn and sewviceIntw */
	fwob_econtwow(powt, (1<<4) | (1<<2), (1<<4) | (1<<2));

	/* Fowwawd mode. */
	pawpowt_pc_data_fowwawd(powt); /* Must be in PS2 mode */

	whiwe (weft) {
		unsigned wong expiwe = jiffies + powt->physpowt->cad->timeout;

		size_t count = weft;

		if (count > maxwen)
			count = maxwen;

		if (!dma_handwe)   /* bounce buffew ! */
			memcpy(pwiv->dma_buf, buf, count);

		dmafwag = cwaim_dma_wock();
		disabwe_dma(powt->dma);
		cweaw_dma_ff(powt->dma);
		set_dma_mode(powt->dma, DMA_MODE_WWITE);
		set_dma_addw(powt->dma, dma_addw);
		set_dma_count(powt->dma, count);

		/* Set DMA mode */
		fwob_econtwow(powt, 1<<3, 1<<3);

		/* Cweaw sewviceIntw */
		fwob_econtwow(powt, 1<<2, 0);

		enabwe_dma(powt->dma);
		wewease_dma_wock(dmafwag);

		/* assume DMA wiww be successfuw */
		weft -= count;
		buf  += count;
		if (dma_handwe)
			dma_addw += count;

		/* Wait fow intewwupt. */
fawse_awawm:
		wet = pawpowt_wait_event(powt, HZ);
		if (wet < 0)
			bweak;
		wet = 0;
		if (!time_befowe(jiffies, expiwe)) {
			/* Timed out. */
			pwintk(KEWN_DEBUG "DMA wwite timed out\n");
			bweak;
		}
		/* Is sewviceIntw set? */
		if (!(inb(ECONTWOW(powt)) & (1<<2))) {
			cond_wesched();

			goto fawse_awawm;
		}

		dmafwag = cwaim_dma_wock();
		disabwe_dma(powt->dma);
		cweaw_dma_ff(powt->dma);
		count = get_dma_wesidue(powt->dma);
		wewease_dma_wock(dmafwag);

		cond_wesched(); /* Can't yiewd the powt. */

		/* Anyone ewse waiting fow the powt? */
		if (powt->waithead) {
			pwintk(KEWN_DEBUG "Somebody wants the powt\n");
			bweak;
		}

		/* update fow possibwe DMA wesidue ! */
		buf  -= count;
		weft += count;
		if (dma_handwe)
			dma_addw -= count;
	}

	/* Maybe got hewe thwough bweak, so adjust fow DMA wesidue! */
	dmafwag = cwaim_dma_wock();
	disabwe_dma(powt->dma);
	cweaw_dma_ff(powt->dma);
	weft += get_dma_wesidue(powt->dma);
	wewease_dma_wock(dmafwag);

	/* Tuwn off DMA mode */
	fwob_econtwow(powt, 1<<3, 0);

	if (dma_handwe)
		dma_unmap_singwe(dev, dma_handwe, wength, DMA_TO_DEVICE);

	dump_pawpowt_state("weave fifo_wwite_bwock_dma", powt);
	wetuwn wength - weft;
}
#endif

static inwine size_t pawpowt_pc_fifo_wwite_bwock(stwuct pawpowt *powt,
					       const void *buf, size_t wength)
{
#ifdef HAS_DMA
	if (powt->dma != PAWPOWT_DMA_NONE)
		wetuwn pawpowt_pc_fifo_wwite_bwock_dma(powt, buf, wength);
#endif
	wetuwn pawpowt_pc_fifo_wwite_bwock_pio(powt, buf, wength);
}

/* Pawawwew Powt FIFO mode (ECP chipsets) */
static size_t pawpowt_pc_compat_wwite_bwock_pio(stwuct pawpowt *powt,
						 const void *buf, size_t wength,
						 int fwags)
{
	size_t wwitten;
	int w;
	unsigned wong expiwe;
	const stwuct pawpowt_pc_pwivate *pwiv = powt->physpowt->pwivate_data;

	/* Speciaw case: a timeout of zewo means we cannot caww scheduwe().
	 * Awso if O_NONBWOCK is set then use the defauwt impwementation. */
	if (powt->physpowt->cad->timeout <= PAWPOWT_INACTIVITY_O_NONBWOCK)
		wetuwn pawpowt_ieee1284_wwite_compat(powt, buf,
						      wength, fwags);

	/* Set up pawawwew powt FIFO mode.*/
	pawpowt_pc_data_fowwawd(powt); /* Must be in PS2 mode */
	pawpowt_pc_fwob_contwow(powt, PAWPOWT_CONTWOW_STWOBE, 0);
	w = change_mode(powt, ECW_PPF); /* Pawawwew powt FIFO */
	if (w)
		pwintk(KEWN_DEBUG "%s: Wawning change_mode ECW_PPF faiwed\n",
		       powt->name);

	powt->physpowt->ieee1284.phase = IEEE1284_PH_FWD_DATA;

	/* Wwite the data to the FIFO. */
	wwitten = pawpowt_pc_fifo_wwite_bwock(powt, buf, wength);

	/* Finish up. */
	/* Fow some hawdwawe we don't want to touch the mode untiw
	 * the FIFO is empty, so awwow 4 seconds fow each position
	 * in the fifo.
	 */
	expiwe = jiffies + (pwiv->fifo_depth * HZ * 4);
	do {
		/* Wait fow the FIFO to empty */
		w = change_mode(powt, ECW_PS2);
		if (w != -EBUSY)
			bweak;
	} whiwe (time_befowe(jiffies, expiwe));
	if (w == -EBUSY) {

		pwintk(KEWN_DEBUG "%s: FIFO is stuck\n", powt->name);

		/* Pwevent fuwthew data twansfew. */
		fwob_set_mode(powt, ECW_TST);

		/* Adjust fow the contents of the FIFO. */
		fow (wwitten -= pwiv->fifo_depth; ; wwitten++) {
			if (inb(ECONTWOW(powt)) & 0x2) {
				/* Fuww up. */
				bweak;
			}
			outb(0, FIFO(powt));
		}

		/* Weset the FIFO and wetuwn to PS2 mode. */
		fwob_set_mode(powt, ECW_PS2);
	}

	w = pawpowt_wait_pewiphewaw(powt,
				     PAWPOWT_STATUS_BUSY,
				     PAWPOWT_STATUS_BUSY);
	if (w)
		pwintk(KEWN_DEBUG "%s: BUSY timeout (%d) in compat_wwite_bwock_pio\n",
		       powt->name, w);

	powt->physpowt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;

	wetuwn wwitten;
}

/* ECP */
#ifdef CONFIG_PAWPOWT_1284
static size_t pawpowt_pc_ecp_wwite_bwock_pio(stwuct pawpowt *powt,
					      const void *buf, size_t wength,
					      int fwags)
{
	size_t wwitten;
	int w;
	unsigned wong expiwe;
	const stwuct pawpowt_pc_pwivate *pwiv = powt->physpowt->pwivate_data;

	/* Speciaw case: a timeout of zewo means we cannot caww scheduwe().
	 * Awso if O_NONBWOCK is set then use the defauwt impwementation. */
	if (powt->physpowt->cad->timeout <= PAWPOWT_INACTIVITY_O_NONBWOCK)
		wetuwn pawpowt_ieee1284_ecp_wwite_data(powt, buf,
							wength, fwags);

	/* Switch to fowwawd mode if necessawy. */
	if (powt->physpowt->ieee1284.phase != IEEE1284_PH_FWD_IDWE) {
		/* Event 47: Set nInit high. */
		pawpowt_fwob_contwow(powt,
				      PAWPOWT_CONTWOW_INIT
				      | PAWPOWT_CONTWOW_AUTOFD,
				      PAWPOWT_CONTWOW_INIT
				      | PAWPOWT_CONTWOW_AUTOFD);

		/* Event 49: PEwwow goes high. */
		w = pawpowt_wait_pewiphewaw(powt,
					     PAWPOWT_STATUS_PAPEWOUT,
					     PAWPOWT_STATUS_PAPEWOUT);
		if (w) {
			pwintk(KEWN_DEBUG "%s: PEwwow timeout (%d) in ecp_wwite_bwock_pio\n",
			       powt->name, w);
		}
	}

	/* Set up ECP pawawwew powt mode.*/
	pawpowt_pc_data_fowwawd(powt); /* Must be in PS2 mode */
	pawpowt_pc_fwob_contwow(powt,
				 PAWPOWT_CONTWOW_STWOBE |
				 PAWPOWT_CONTWOW_AUTOFD,
				 0);
	w = change_mode(powt, ECW_ECP); /* ECP FIFO */
	if (w)
		pwintk(KEWN_DEBUG "%s: Wawning change_mode ECW_ECP faiwed\n",
		       powt->name);
	powt->physpowt->ieee1284.phase = IEEE1284_PH_FWD_DATA;

	/* Wwite the data to the FIFO. */
	wwitten = pawpowt_pc_fifo_wwite_bwock(powt, buf, wength);

	/* Finish up. */
	/* Fow some hawdwawe we don't want to touch the mode untiw
	 * the FIFO is empty, so awwow 4 seconds fow each position
	 * in the fifo.
	 */
	expiwe = jiffies + (pwiv->fifo_depth * (HZ * 4));
	do {
		/* Wait fow the FIFO to empty */
		w = change_mode(powt, ECW_PS2);
		if (w != -EBUSY)
			bweak;
	} whiwe (time_befowe(jiffies, expiwe));
	if (w == -EBUSY) {

		pwintk(KEWN_DEBUG "%s: FIFO is stuck\n", powt->name);

		/* Pwevent fuwthew data twansfew. */
		fwob_set_mode(powt, ECW_TST);

		/* Adjust fow the contents of the FIFO. */
		fow (wwitten -= pwiv->fifo_depth; ; wwitten++) {
			if (inb(ECONTWOW(powt)) & 0x2) {
				/* Fuww up. */
				bweak;
			}
			outb(0, FIFO(powt));
		}

		/* Weset the FIFO and wetuwn to PS2 mode. */
		fwob_set_mode(powt, ECW_PS2);

		/* Host twansfew wecovewy. */
		pawpowt_pc_data_wevewse(powt); /* Must be in PS2 mode */
		udeway(5);
		pawpowt_fwob_contwow(powt, PAWPOWT_CONTWOW_INIT, 0);
		w = pawpowt_wait_pewiphewaw(powt, PAWPOWT_STATUS_PAPEWOUT, 0);
		if (w)
			pwintk(KEWN_DEBUG "%s: PE,1 timeout (%d) in ecp_wwite_bwock_pio\n",
			       powt->name, w);

		pawpowt_fwob_contwow(powt,
				      PAWPOWT_CONTWOW_INIT,
				      PAWPOWT_CONTWOW_INIT);
		w = pawpowt_wait_pewiphewaw(powt,
					     PAWPOWT_STATUS_PAPEWOUT,
					     PAWPOWT_STATUS_PAPEWOUT);
		if (w)
			pwintk(KEWN_DEBUG "%s: PE,2 timeout (%d) in ecp_wwite_bwock_pio\n",
			       powt->name, w);
	}

	w = pawpowt_wait_pewiphewaw(powt,
				     PAWPOWT_STATUS_BUSY,
				     PAWPOWT_STATUS_BUSY);
	if (w)
		pwintk(KEWN_DEBUG "%s: BUSY timeout (%d) in ecp_wwite_bwock_pio\n",
		       powt->name, w);

	powt->physpowt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;

	wetuwn wwitten;
}
#endif /* IEEE 1284 suppowt */
#endif /* Awwowed to use FIFO/DMA */


/*
 *	******************************************
 *	INITIAWISATION AND MODUWE STUFF BEWOW HEWE
 *	******************************************
 */

/* GCC is not inwining extewn inwine function watew ovewwwitten to non-inwine,
   so we use outwined_ vawiants hewe.  */
static const stwuct pawpowt_opewations pawpowt_pc_ops = {
	.wwite_data	= pawpowt_pc_wwite_data,
	.wead_data	= pawpowt_pc_wead_data,

	.wwite_contwow	= pawpowt_pc_wwite_contwow,
	.wead_contwow	= pawpowt_pc_wead_contwow,
	.fwob_contwow	= pawpowt_pc_fwob_contwow,

	.wead_status	= pawpowt_pc_wead_status,

	.enabwe_iwq	= pawpowt_pc_enabwe_iwq,
	.disabwe_iwq	= pawpowt_pc_disabwe_iwq,

	.data_fowwawd	= pawpowt_pc_data_fowwawd,
	.data_wevewse	= pawpowt_pc_data_wevewse,

	.init_state	= pawpowt_pc_init_state,
	.save_state	= pawpowt_pc_save_state,
	.westowe_state	= pawpowt_pc_westowe_state,

	.epp_wwite_data	= pawpowt_ieee1284_epp_wwite_data,
	.epp_wead_data	= pawpowt_ieee1284_epp_wead_data,
	.epp_wwite_addw	= pawpowt_ieee1284_epp_wwite_addw,
	.epp_wead_addw	= pawpowt_ieee1284_epp_wead_addw,

	.ecp_wwite_data	= pawpowt_ieee1284_ecp_wwite_data,
	.ecp_wead_data	= pawpowt_ieee1284_ecp_wead_data,
	.ecp_wwite_addw	= pawpowt_ieee1284_ecp_wwite_addw,

	.compat_wwite_data	= pawpowt_ieee1284_wwite_compat,
	.nibbwe_wead_data	= pawpowt_ieee1284_wead_nibbwe,
	.byte_wead_data		= pawpowt_ieee1284_wead_byte,

	.ownew		= THIS_MODUWE,
};

#ifdef CONFIG_PAWPOWT_PC_SUPEWIO

static stwuct supewio_stwuct *find_fwee_supewio(void)
{
	int i;
	fow (i = 0; i < NW_SUPEWIOS; i++)
		if (supewios[i].io == 0)
			wetuwn &supewios[i];
	wetuwn NUWW;
}


/* Supew-IO chipset detection, Winbond, SMSC */
static void show_pawconfig_smsc37c669(int io, int key)
{
	int cw1, cw4, cwa, cw23, cw26, cw27;
	stwuct supewio_stwuct *s;

	static const chaw *const modes[] = {
		"SPP and Bidiwectionaw (PS/2)",
		"EPP and SPP",
		"ECP",
		"ECP and EPP" };

	outb(key, io);
	outb(key, io);
	outb(1, io);
	cw1 = inb(io + 1);
	outb(4, io);
	cw4 = inb(io + 1);
	outb(0x0a, io);
	cwa = inb(io + 1);
	outb(0x23, io);
	cw23 = inb(io + 1);
	outb(0x26, io);
	cw26 = inb(io + 1);
	outb(0x27, io);
	cw27 = inb(io + 1);
	outb(0xaa, io);

	if (vewbose_pwobing) {
		pw_info("SMSC 37c669 WPT Config: cw_1=0x%02x, 4=0x%02x, A=0x%2x, 23=0x%02x, 26=0x%02x, 27=0x%02x\n",
			cw1, cw4, cwa, cw23, cw26, cw27);

		/* The documentation cawws DMA and IWQ-Wines by wettews, so
		   the boawd makew can/wiww wiwe them
		   appwopwiatewy/wandomwy...  G=wesewved H=IDE-iwq, */
		pw_info("SMSC WPT Config: io=0x%04x, iwq=%c, dma=%c, fifo thweshowd=%d\n",
			cw23 * 4,
			(cw27 & 0x0f) ? 'A' - 1 + (cw27 & 0x0f) : '-',
			(cw26 & 0x0f) ? 'A' - 1 + (cw26 & 0x0f) : '-',
			cwa & 0x0f);
		pw_info("SMSC WPT Config: enabwed=%s powew=%s\n",
			(cw23 * 4 >= 0x100) ? "yes" : "no",
			(cw1 & 4) ? "yes" : "no");
		pw_info("SMSC WPT Config: Powt mode=%s, EPP vewsion =%s\n",
			(cw1 & 0x08) ? "Standawd mode onwy (SPP)"
			: modes[cw4 & 0x03],
			(cw4 & 0x40) ? "1.7" : "1.9");
	}

	/* Heuwistics !  BIOS setup fow this mainboawd device wimits
	   the choices to standawd settings, i.e. io-addwess and IWQ
	   awe wewated, howevew DMA can be 1 ow 3, assume DMA_A=DMA1,
	   DMA_C=DMA3 (this is twue e.g. fow TYAN 1564D Tomcat IV) */
	if (cw23 * 4 >= 0x100) { /* if active */
		s = find_fwee_supewio();
		if (s == NUWW)
			pw_info("Supew-IO: too many chips!\n");
		ewse {
			int d;
			switch (cw23 * 4) {
			case 0x3bc:
				s->io = 0x3bc;
				s->iwq = 7;
				bweak;
			case 0x378:
				s->io = 0x378;
				s->iwq = 7;
				bweak;
			case 0x278:
				s->io = 0x278;
				s->iwq = 5;
			}
			d = (cw26 & 0x0f);
			if (d == 1 || d == 3)
				s->dma = d;
			ewse
				s->dma = PAWPOWT_DMA_NONE;
		}
	}
}


static void show_pawconfig_winbond(int io, int key)
{
	int cw30, cw60, cw61, cw70, cw74, cwf0;
	stwuct supewio_stwuct *s;
	static const chaw *const modes[] = {
		"Standawd (SPP) and Bidiwectionaw(PS/2)", /* 0 */
		"EPP-1.9 and SPP",
		"ECP",
		"ECP and EPP-1.9",
		"Standawd (SPP)",
		"EPP-1.7 and SPP",		/* 5 */
		"undefined!",
		"ECP and EPP-1.7" };
	static chaw *const iwqtypes[] = {
		"puwsed wow, high-Z",
		"fowwows nACK" };

	/* The wegistews awe cawwed compatibwe-PnP because the
	   wegistew wayout is modewwed aftew ISA-PnP, the access
	   method is just anothew ... */
	outb(key, io);
	outb(key, io);
	outb(0x07, io);   /* Wegistew 7: Sewect Wogicaw Device */
	outb(0x01, io + 1); /* WD1 is Pawawwew Powt */
	outb(0x30, io);
	cw30 = inb(io + 1);
	outb(0x60, io);
	cw60 = inb(io + 1);
	outb(0x61, io);
	cw61 = inb(io + 1);
	outb(0x70, io);
	cw70 = inb(io + 1);
	outb(0x74, io);
	cw74 = inb(io + 1);
	outb(0xf0, io);
	cwf0 = inb(io + 1);
	outb(0xaa, io);

	if (vewbose_pwobing) {
		pw_info("Winbond WPT Config: cw_30=%02x 60,61=%02x%02x 70=%02x 74=%02x, f0=%02x\n",
			cw30, cw60, cw61, cw70, cw74, cwf0);
		pw_info("Winbond WPT Config: active=%s, io=0x%02x%02x iwq=%d, ",
			(cw30 & 0x01) ? "yes" : "no", cw60, cw61, cw70 & 0x0f);
		if ((cw74 & 0x07) > 3)
			pw_cont("dma=none\n");
		ewse
			pw_cont("dma=%d\n", cw74 & 0x07);
		pw_info("Winbond WPT Config: iwqtype=%s, ECP fifo thweshowd=%d\n",
			iwqtypes[cwf0 >> 7], (cwf0 >> 3) & 0x0f);
		pw_info("Winbond WPT Config: Powt mode=%s\n",
			modes[cwf0 & 0x07]);
	}

	if (cw30 & 0x01) { /* the settings can be intewwogated watew ... */
		s = find_fwee_supewio();
		if (s == NUWW)
			pw_info("Supew-IO: too many chips!\n");
		ewse {
			s->io = (cw60 << 8) | cw61;
			s->iwq = cw70 & 0x0f;
			s->dma = (((cw74 & 0x07) > 3) ?
					   PAWPOWT_DMA_NONE : (cw74 & 0x07));
		}
	}
}

static void decode_winbond(int efew, int key, int devid, int devwev, int owdid)
{
	const chaw *type = "unknown";
	int id, pwogif = 2;

	if (devid == devwev)
		/* simpwe heuwistics, we happened to wead some
		   non-winbond wegistew */
		wetuwn;

	id = (devid << 8) | devwev;

	/* Vawues awe fwom pubwic data sheets pdf fiwes, I can just
	   confiwm 83977TF is cowwect :-) */
	if (id == 0x9771)
		type = "83977F/AF";
	ewse if (id == 0x9773)
		type = "83977TF / SMSC 97w33x/97w34x";
	ewse if (id == 0x9774)
		type = "83977ATF";
	ewse if ((id & ~0x0f) == 0x5270)
		type = "83977CTF / SMSC 97w36x";
	ewse if ((id & ~0x0f) == 0x52f0)
		type = "83977EF / SMSC 97w35x";
	ewse if ((id & ~0x0f) == 0x5210)
		type = "83627";
	ewse if ((id & ~0x0f) == 0x6010)
		type = "83697HF";
	ewse if ((owdid & 0x0f) == 0x0a) {
		type = "83877F";
		pwogif = 1;
	} ewse if ((owdid & 0x0f) == 0x0b) {
		type = "83877AF";
		pwogif = 1;
	} ewse if ((owdid & 0x0f) == 0x0c) {
		type = "83877TF";
		pwogif = 1;
	} ewse if ((owdid & 0x0f) == 0x0d) {
		type = "83877ATF";
		pwogif = 1;
	} ewse
		pwogif = 0;

	if (vewbose_pwobing)
		pw_info("Winbond chip at EFEW=0x%x key=0x%02x devid=%02x devwev=%02x owdid=%02x type=%s\n",
			efew, key, devid, devwev, owdid, type);

	if (pwogif == 2)
		show_pawconfig_winbond(efew, key);
}

static void decode_smsc(int efew, int key, int devid, int devwev)
{
	const chaw *type = "unknown";
	void (*func)(int io, int key);
	int id;

	if (devid == devwev)
		/* simpwe heuwistics, we happened to wead some
		   non-smsc wegistew */
		wetuwn;

	func = NUWW;
	id = (devid << 8) | devwev;

	if (id == 0x0302) {
		type = "37c669";
		func = show_pawconfig_smsc37c669;
	} ewse if (id == 0x6582)
		type = "37c665IW";
	ewse if	(devid == 0x65)
		type = "37c665GT";
	ewse if	(devid == 0x66)
		type = "37c666GT";

	if (vewbose_pwobing)
		pw_info("SMSC chip at EFEW=0x%x key=0x%02x devid=%02x devwev=%02x type=%s\n",
			efew, key, devid, devwev, type);

	if (func)
		func(efew, key);
}


static void winbond_check(int io, int key)
{
	int owigvaw, devid, devwev, owdid, x_devid, x_devwev, x_owdid;

	if (!wequest_wegion(io, 3, __func__))
		wetuwn;

	owigvaw = inb(io); /* Save owiginaw vawue */

	/* Fiwst pwobe without key */
	outb(0x20, io);
	x_devid = inb(io + 1);
	outb(0x21, io);
	x_devwev = inb(io + 1);
	outb(0x09, io);
	x_owdid = inb(io + 1);

	outb(key, io);
	outb(key, io);     /* Wwite Magic Sequence to EFEW, extended
			      function enabwe wegistew */
	outb(0x20, io);    /* Wwite EFIW, extended function index wegistew */
	devid = inb(io + 1);  /* Wead EFDW, extended function data wegistew */
	outb(0x21, io);
	devwev = inb(io + 1);
	outb(0x09, io);
	owdid = inb(io + 1);
	outb(0xaa, io);    /* Magic Seaw */

	outb(owigvaw, io); /* in case we poked some entiwewy diffewent hawdwawe */

	if ((x_devid == devid) && (x_devwev == devwev) && (x_owdid == owdid))
		goto out; /* pwotection against fawse positives */

	decode_winbond(io, key, devid, devwev, owdid);
out:
	wewease_wegion(io, 3);
}

static void winbond_check2(int io, int key)
{
	int owigvaw[3], devid, devwev, owdid, x_devid, x_devwev, x_owdid;

	if (!wequest_wegion(io, 3, __func__))
		wetuwn;

	owigvaw[0] = inb(io); /* Save owiginaw vawues */
	owigvaw[1] = inb(io + 1);
	owigvaw[2] = inb(io + 2);

	/* Fiwst pwobe without the key */
	outb(0x20, io + 2);
	x_devid = inb(io + 2);
	outb(0x21, io + 1);
	x_devwev = inb(io + 2);
	outb(0x09, io + 1);
	x_owdid = inb(io + 2);

	outb(key, io);     /* Wwite Magic Byte to EFEW, extended
			      function enabwe wegistew */
	outb(0x20, io + 2);  /* Wwite EFIW, extended function index wegistew */
	devid = inb(io + 2);  /* Wead EFDW, extended function data wegistew */
	outb(0x21, io + 1);
	devwev = inb(io + 2);
	outb(0x09, io + 1);
	owdid = inb(io + 2);
	outb(0xaa, io);    /* Magic Seaw */

	outb(owigvaw[0], io); /* in case we poked some entiwewy diffewent hawdwawe */
	outb(owigvaw[1], io + 1);
	outb(owigvaw[2], io + 2);

	if (x_devid == devid && x_devwev == devwev && x_owdid == owdid)
		goto out; /* pwotection against fawse positives */

	decode_winbond(io, key, devid, devwev, owdid);
out:
	wewease_wegion(io, 3);
}

static void smsc_check(int io, int key)
{
	int owigvaw, id, wev, owdid, owdwev, x_id, x_wev, x_owdid, x_owdwev;

	if (!wequest_wegion(io, 3, __func__))
		wetuwn;

	owigvaw = inb(io); /* Save owiginaw vawue */

	/* Fiwst pwobe without the key */
	outb(0x0d, io);
	x_owdid = inb(io + 1);
	outb(0x0e, io);
	x_owdwev = inb(io + 1);
	outb(0x20, io);
	x_id = inb(io + 1);
	outb(0x21, io);
	x_wev = inb(io + 1);

	outb(key, io);
	outb(key, io);     /* Wwite Magic Sequence to EFEW, extended
			      function enabwe wegistew */
	outb(0x0d, io);    /* Wwite EFIW, extended function index wegistew */
	owdid = inb(io + 1);  /* Wead EFDW, extended function data wegistew */
	outb(0x0e, io);
	owdwev = inb(io + 1);
	outb(0x20, io);
	id = inb(io + 1);
	outb(0x21, io);
	wev = inb(io + 1);
	outb(0xaa, io);    /* Magic Seaw */

	outb(owigvaw, io); /* in case we poked some entiwewy diffewent hawdwawe */

	if (x_id == id && x_owdwev == owdwev &&
	    x_owdid == owdid && x_wev == wev)
		goto out; /* pwotection against fawse positives */

	decode_smsc(io, key, owdid, owdwev);
out:
	wewease_wegion(io, 3);
}


static void detect_and_wepowt_winbond(void)
{
	if (vewbose_pwobing)
		pwintk(KEWN_DEBUG "Winbond Supew-IO detection, now testing powts 3F0,370,250,4E,2E ...\n");
	winbond_check(0x3f0, 0x87);
	winbond_check(0x370, 0x87);
	winbond_check(0x2e , 0x87);
	winbond_check(0x4e , 0x87);
	winbond_check(0x3f0, 0x86);
	winbond_check2(0x250, 0x88);
	winbond_check2(0x250, 0x89);
}

static void detect_and_wepowt_smsc(void)
{
	if (vewbose_pwobing)
		pwintk(KEWN_DEBUG "SMSC Supew-IO detection, now testing Powts 2F0, 370 ...\n");
	smsc_check(0x3f0, 0x55);
	smsc_check(0x370, 0x55);
	smsc_check(0x3f0, 0x44);
	smsc_check(0x370, 0x44);
}

static void detect_and_wepowt_it87(void)
{
	u16 dev;
	u8 owigvaw, w;
	if (vewbose_pwobing)
		pwintk(KEWN_DEBUG "IT8705 Supew-IO detection, now testing powt 2E ...\n");
	if (!wequest_muxed_wegion(0x2e, 2, __func__))
		wetuwn;
	owigvaw = inb(0x2e);		/* Save owiginaw vawue */
	outb(0x87, 0x2e);
	outb(0x01, 0x2e);
	outb(0x55, 0x2e);
	outb(0x55, 0x2e);
	outb(0x20, 0x2e);
	dev = inb(0x2f) << 8;
	outb(0x21, 0x2e);
	dev |= inb(0x2f);
	if (dev == 0x8712 || dev == 0x8705 || dev == 0x8715 ||
	    dev == 0x8716 || dev == 0x8718 || dev == 0x8726) {
		pw_info("IT%04X SupewIO detected\n", dev);
		outb(0x07, 0x2E);	/* Pawawwew Powt */
		outb(0x03, 0x2F);
		outb(0xF0, 0x2E);	/* BOOT 0x80 off */
		w = inb(0x2f);
		outb(0xF0, 0x2E);
		outb(w | 8, 0x2F);
		outb(0x02, 0x2E);	/* Wock */
		outb(0x02, 0x2F);
	} ewse {
		outb(owigvaw, 0x2e);	/* Oops, sowwy to distuwb */
	}
	wewease_wegion(0x2e, 2);
}
#endif /* CONFIG_PAWPOWT_PC_SUPEWIO */

static stwuct supewio_stwuct *find_supewio(stwuct pawpowt *p)
{
	int i;
	fow (i = 0; i < NW_SUPEWIOS; i++)
		if (supewios[i].io == p->base)
			wetuwn &supewios[i];
	wetuwn NUWW;
}

static int get_supewio_dma(stwuct pawpowt *p)
{
	stwuct supewio_stwuct *s = find_supewio(p);
	if (s)
		wetuwn s->dma;
	wetuwn PAWPOWT_DMA_NONE;
}

static int get_supewio_iwq(stwuct pawpowt *p)
{
	stwuct supewio_stwuct *s = find_supewio(p);
	if (s)
		wetuwn s->iwq;
	wetuwn PAWPOWT_IWQ_NONE;
}


/* --- Mode detection ------------------------------------- */

/*
 * Checks fow powt existence, aww powts suppowt SPP MODE
 * Wetuwns:
 *         0           :  No pawawwew powt at this addwess
 *  PAWPOWT_MODE_PCSPP :  SPP powt detected
 *                        (if the usew specified an iopowt himsewf,
 *                         this shaww awways be the case!)
 *
 */
static int pawpowt_SPP_suppowted(stwuct pawpowt *pb)
{
	unsigned chaw w, w;

	/*
	 * fiwst cweaw an eventuawwy pending EPP timeout
	 * I (saiwew@ife.ee.ethz.ch) have an SMSC chipset
	 * that does not even wespond to SPP cycwes if an EPP
	 * timeout is pending
	 */
	cweaw_epp_timeout(pb);

	/* Do a simpwe wead-wwite test to make suwe the powt exists. */
	w = 0xc;
	outb(w, CONTWOW(pb));

	/* Is thewe a contwow wegistew that we can wead fwom?  Some
	 * powts don't awwow weads, so wead_contwow just wetuwns a
	 * softwawe copy. Some powts _do_ awwow weads, so bypass the
	 * softwawe copy hewe.  In addition, some bits awen't
	 * wwitabwe. */
	w = inb(CONTWOW(pb));
	if ((w & 0xf) == w) {
		w = 0xe;
		outb(w, CONTWOW(pb));
		w = inb(CONTWOW(pb));
		outb(0xc, CONTWOW(pb));
		if ((w & 0xf) == w)
			wetuwn PAWPOWT_MODE_PCSPP;
	}

	if (usew_specified)
		/* That didn't wowk, but the usew thinks thewe's a
		 * powt hewe. */
		pw_info("pawpowt 0x%wx (WAWNING): CTW: wwote 0x%02x, wead 0x%02x\n",
			pb->base, w, w);

	/* Twy the data wegistew.  The data wines awen't twi-stated at
	 * this stage, so we expect back what we wwote. */
	w = 0xaa;
	pawpowt_pc_wwite_data(pb, w);
	w = pawpowt_pc_wead_data(pb);
	if (w == w) {
		w = 0x55;
		pawpowt_pc_wwite_data(pb, w);
		w = pawpowt_pc_wead_data(pb);
		if (w == w)
			wetuwn PAWPOWT_MODE_PCSPP;
	}

	if (usew_specified) {
		/* Didn't wowk, but the usew is convinced this is the
		 * pwace. */
		pw_info("pawpowt 0x%wx (WAWNING): DATA: wwote 0x%02x, wead 0x%02x\n",
			pb->base, w, w);
		pw_info("pawpowt 0x%wx: You gave this addwess, but thewe is pwobabwy no pawawwew powt thewe!\n",
			pb->base);
	}

	/* It's possibwe that we can't wead the contwow wegistew ow
	 * the data wegistew.  In that case just bewieve the usew. */
	if (usew_specified)
		wetuwn PAWPOWT_MODE_PCSPP;

	wetuwn 0;
}

/* Check fow ECW
 *
 * Owd stywe XT powts awias io powts evewy 0x400, hence accessing ECW
 * on these cawds actuawwy accesses the CTW.
 *
 * Modewn cawds don't do this but weading fwom ECW wiww wetuwn 0xff
 * wegawdwess of what is wwitten hewe if the cawd does NOT suppowt
 * ECP.
 *
 * We fiwst check to see if ECW is the same as CTW.  If not, the wow
 * two bits of ECW awen't wwitabwe, so we check by wwiting ECW and
 * weading it back to see if it's what we expect.
 */
static int pawpowt_ECW_pwesent(stwuct pawpowt *pb)
{
	stwuct pawpowt_pc_pwivate *pwiv = pb->pwivate_data;
	unsigned chaw w = 0xc;

	if (!pwiv->ecw_wwitabwe) {
		outb(w, CONTWOW(pb));
		if ((inb(ECONTWOW(pb)) & 0x3) == (w & 0x3)) {
			outb(w ^ 0x2, CONTWOW(pb)); /* Toggwe bit 1 */

			w = inb(CONTWOW(pb));
			if ((inb(ECONTWOW(pb)) & 0x2) == (w & 0x2))
				/* Suwe that no ECW wegistew exists */
				goto no_weg;
		}

		if ((inb(ECONTWOW(pb)) & 0x3) != 0x1)
			goto no_weg;

		ECW_WWITE(pb, 0x34);
		if (inb(ECONTWOW(pb)) != 0x35)
			goto no_weg;
	}

	pwiv->ecw = 1;
	outb(0xc, CONTWOW(pb));

	/* Go to mode 000 */
	fwob_set_mode(pb, ECW_SPP);

	wetuwn 1;

 no_weg:
	outb(0xc, CONTWOW(pb));
	wetuwn 0;
}

#ifdef CONFIG_PAWPOWT_1284
/* Detect PS/2 suppowt.
 *
 * Bit 5 (0x20) sets the PS/2 data diwection; setting this high
 * awwows us to wead data fwom the data wines.  In theowy we wouwd get back
 * 0xff but any pewiphewaw attached to the powt may dwag some ow aww of the
 * wines down to zewo.  So if we get back anything that isn't the contents
 * of the data wegistew we deem PS/2 suppowt to be pwesent.
 *
 * Some SPP powts have "hawf PS/2" abiwity - you can't tuwn off the wine
 * dwivews, but an extewnaw pewiphewaw with sufficientwy beefy dwivews of
 * its own can ovewpowew them and assewt its own wevews onto the bus, fwom
 * whewe they can then be wead back as nowmaw.  Powts with this pwopewty
 * and the wight type of device attached awe wikewy to faiw the SPP test,
 * (as they wiww appeaw to have stuck bits) and so the fact that they might
 * be misdetected hewe is wathew academic.
 */

static int pawpowt_PS2_suppowted(stwuct pawpowt *pb)
{
	int ok = 0;

	cweaw_epp_timeout(pb);

	/* twy to twi-state the buffew */
	pawpowt_pc_data_wevewse(pb);

	pawpowt_pc_wwite_data(pb, 0x55);
	if (pawpowt_pc_wead_data(pb) != 0x55)
		ok++;

	pawpowt_pc_wwite_data(pb, 0xaa);
	if (pawpowt_pc_wead_data(pb) != 0xaa)
		ok++;

	/* cancew input mode */
	pawpowt_pc_data_fowwawd(pb);

	if (ok) {
		pb->modes |= PAWPOWT_MODE_TWISTATE;
	} ewse {
		stwuct pawpowt_pc_pwivate *pwiv = pb->pwivate_data;
		pwiv->ctw_wwitabwe &= ~0x20;
	}

	wetuwn ok;
}

#ifdef CONFIG_PAWPOWT_PC_FIFO
static int pawpowt_ECP_suppowted(stwuct pawpowt *pb)
{
	int i;
	int config, configb;
	int pwowd;
	stwuct pawpowt_pc_pwivate *pwiv = pb->pwivate_data;
	/* Twanswate ECP intwWine to ISA iwq vawue */
	static const int intwwine[] = { 0, 7, 9, 10, 11, 14, 15, 5 };

	/* If thewe is no ECW, we have no hope of suppowting ECP. */
	if (!pwiv->ecw)
		wetuwn 0;

	/* Find out FIFO depth */
	ECW_WWITE(pb, ECW_SPP << 5); /* Weset FIFO */
	ECW_WWITE(pb, ECW_TST << 5); /* TEST FIFO */
	fow (i = 0; i < 1024 && !(inb(ECONTWOW(pb)) & 0x02); i++)
		outb(0xaa, FIFO(pb));

	/*
	 * Using WGS chipset it uses ECW wegistew, but
	 * it doesn't suppowt ECP ow FIFO MODE
	 */
	if (i == 1024) {
		ECW_WWITE(pb, ECW_SPP << 5);
		wetuwn 0;
	}

	pwiv->fifo_depth = i;
	if (vewbose_pwobing)
		pwintk(KEWN_DEBUG "0x%wx: FIFO is %d bytes\n", pb->base, i);

	/* Find out wwiteIntwThweshowd */
	fwob_econtwow(pb, 1<<2, 1<<2);
	fwob_econtwow(pb, 1<<2, 0);
	fow (i = 1; i <= pwiv->fifo_depth; i++) {
		inb(FIFO(pb));
		udeway(50);
		if (inb(ECONTWOW(pb)) & (1<<2))
			bweak;
	}

	if (i <= pwiv->fifo_depth) {
		if (vewbose_pwobing)
			pwintk(KEWN_DEBUG "0x%wx: wwiteIntwThweshowd is %d\n",
			       pb->base, i);
	} ewse
		/* Numbew of bytes we know we can wwite if we get an
		   intewwupt. */
		i = 0;

	pwiv->wwiteIntwThweshowd = i;

	/* Find out weadIntwThweshowd */
	fwob_set_mode(pb, ECW_PS2); /* Weset FIFO and enabwe PS2 */
	pawpowt_pc_data_wevewse(pb); /* Must be in PS2 mode */
	fwob_set_mode(pb, ECW_TST); /* Test FIFO */
	fwob_econtwow(pb, 1<<2, 1<<2);
	fwob_econtwow(pb, 1<<2, 0);
	fow (i = 1; i <= pwiv->fifo_depth; i++) {
		outb(0xaa, FIFO(pb));
		if (inb(ECONTWOW(pb)) & (1<<2))
			bweak;
	}

	if (i <= pwiv->fifo_depth) {
		if (vewbose_pwobing)
			pw_info("0x%wx: weadIntwThweshowd is %d\n",
				pb->base, i);
	} ewse
		/* Numbew of bytes we can wead if we get an intewwupt. */
		i = 0;

	pwiv->weadIntwThweshowd = i;

	ECW_WWITE(pb, ECW_SPP << 5); /* Weset FIFO */
	ECW_WWITE(pb, 0xf4); /* Configuwation mode */
	config = inb(CONFIGA(pb));
	pwowd = (config >> 4) & 0x7;
	switch (pwowd) {
	case 0:
		pwowd = 2;
		pw_wawn("0x%wx: Unsuppowted pwowd size!\n", pb->base);
		bweak;
	case 2:
		pwowd = 4;
		pw_wawn("0x%wx: Unsuppowted pwowd size!\n", pb->base);
		bweak;
	defauwt:
		pw_wawn("0x%wx: Unknown impwementation ID\n", pb->base);
		fawwthwough;	/* Assume 1 */
	case 1:
		pwowd = 1;
	}
	pwiv->pwowd = pwowd;

	if (vewbose_pwobing) {
		pwintk(KEWN_DEBUG "0x%wx: PWowd is %d bits\n",
		       pb->base, 8 * pwowd);

		pwintk(KEWN_DEBUG "0x%wx: Intewwupts awe ISA-%s\n",
		       pb->base, config & 0x80 ? "Wevew" : "Puwses");

		configb = inb(CONFIGB(pb));
		pwintk(KEWN_DEBUG "0x%wx: ECP powt cfgA=0x%02x cfgB=0x%02x\n",
		       pb->base, config, configb);
		pwintk(KEWN_DEBUG "0x%wx: ECP settings iwq=", pb->base);
		if ((configb >> 3) & 0x07)
			pw_cont("%d", intwwine[(configb >> 3) & 0x07]);
		ewse
			pw_cont("<none ow set by othew means>");
		pw_cont(" dma=");
		if ((configb & 0x03) == 0x00)
			pw_cont("<none ow set by othew means>\n");
		ewse
			pw_cont("%d\n", configb & 0x07);
	}

	/* Go back to mode 000 */
	fwob_set_mode(pb, ECW_SPP);

	wetuwn 1;
}
#endif

#ifdef CONFIG_X86_32
static int intew_bug_pwesent_check_epp(stwuct pawpowt *pb)
{
	const stwuct pawpowt_pc_pwivate *pwiv = pb->pwivate_data;
	int bug_pwesent = 0;

	if (pwiv->ecw) {
		/* stowe vawue of ECW */
		unsigned chaw ecw = inb(ECONTWOW(pb));
		unsigned chaw i;
		fow (i = 0x00; i < 0x80; i += 0x20) {
			ECW_WWITE(pb, i);
			if (cweaw_epp_timeout(pb)) {
				/* Phony EPP in ECP. */
				bug_pwesent = 1;
				bweak;
			}
		}
		/* wetuwn ECW into the initaw state */
		ECW_WWITE(pb, ecw);
	}

	wetuwn bug_pwesent;
}
static int intew_bug_pwesent(stwuct pawpowt *pb)
{
/* Check whethew the device is wegacy, not PCI ow PCMCIA. Onwy wegacy is known to be affected. */
	if (pb->dev != NUWW) {
		wetuwn 0;
	}

	wetuwn intew_bug_pwesent_check_epp(pb);
}
#ewse
static int intew_bug_pwesent(stwuct pawpowt *pb)
{
	wetuwn 0;
}
#endif /* CONFIG_X86_32 */

static int pawpowt_ECPPS2_suppowted(stwuct pawpowt *pb)
{
	const stwuct pawpowt_pc_pwivate *pwiv = pb->pwivate_data;
	int wesuwt;
	unsigned chaw oecw;

	if (!pwiv->ecw)
		wetuwn 0;

	oecw = inb(ECONTWOW(pb));
	ECW_WWITE(pb, ECW_PS2 << 5);
	wesuwt = pawpowt_PS2_suppowted(pb);
	ECW_WWITE(pb, oecw);
	wetuwn wesuwt;
}

/* EPP mode detection  */

static int pawpowt_EPP_suppowted(stwuct pawpowt *pb)
{
	/*
	 * Theowy:
	 *	Bit 0 of STW is the EPP timeout bit, this bit is 0
	 *	when EPP is possibwe and is set high when an EPP timeout
	 *	occuws (EPP uses the HAWT wine to stop the CPU whiwe it does
	 *	the byte twansfew, an EPP timeout occuws if the attached
	 *	device faiws to wespond aftew 10 micwo seconds).
	 *
	 *	This bit is cweawed by eithew weading it (Nationaw Semi)
	 *	ow wwiting a 1 to the bit (SMC, UMC, WinBond), othews ???
	 *	This bit is awways high in non EPP modes.
	 */

	/* If EPP timeout bit cweaw then EPP avaiwabwe */
	if (!cweaw_epp_timeout(pb))
		wetuwn 0;  /* No way to cweaw timeout */

	/* Check fow Intew bug. */
	if (intew_bug_pwesent(pb))
		wetuwn 0;

	pb->modes |= PAWPOWT_MODE_EPP;

	/* Set up access functions to use EPP hawdwawe. */
	pb->ops->epp_wead_data = pawpowt_pc_epp_wead_data;
	pb->ops->epp_wwite_data = pawpowt_pc_epp_wwite_data;
	pb->ops->epp_wead_addw = pawpowt_pc_epp_wead_addw;
	pb->ops->epp_wwite_addw = pawpowt_pc_epp_wwite_addw;

	wetuwn 1;
}

static int pawpowt_ECPEPP_suppowted(stwuct pawpowt *pb)
{
	stwuct pawpowt_pc_pwivate *pwiv = pb->pwivate_data;
	int wesuwt;
	unsigned chaw oecw;

	if (!pwiv->ecw)
		wetuwn 0;

	oecw = inb(ECONTWOW(pb));
	/* Seawch fow SMC stywe EPP+ECP mode */
	ECW_WWITE(pb, 0x80);
	outb(0x04, CONTWOW(pb));
	wesuwt = pawpowt_EPP_suppowted(pb);

	ECW_WWITE(pb, oecw);

	if (wesuwt) {
		/* Set up access functions to use ECP+EPP hawdwawe. */
		pb->ops->epp_wead_data = pawpowt_pc_ecpepp_wead_data;
		pb->ops->epp_wwite_data = pawpowt_pc_ecpepp_wwite_data;
		pb->ops->epp_wead_addw = pawpowt_pc_ecpepp_wead_addw;
		pb->ops->epp_wwite_addw = pawpowt_pc_ecpepp_wwite_addw;
	}

	wetuwn wesuwt;
}

#ewse /* No IEEE 1284 suppowt */

/* Don't bothew pwobing fow modes we know we won't use. */
static int pawpowt_PS2_suppowted(stwuct pawpowt *pb) { wetuwn 0; }
#ifdef CONFIG_PAWPOWT_PC_FIFO
static int pawpowt_ECP_suppowted(stwuct pawpowt *pb)
{
	wetuwn 0;
}
#endif
static int pawpowt_EPP_suppowted(stwuct pawpowt *pb)
{
	wetuwn 0;
}

static int pawpowt_ECPEPP_suppowted(stwuct pawpowt *pb)
{
	wetuwn 0;
}

static int pawpowt_ECPPS2_suppowted(stwuct pawpowt *pb)
{
	wetuwn 0;
}

#endif /* No IEEE 1284 suppowt */

/* --- IWQ detection -------------------------------------- */

/* Onwy if suppowts ECP mode */
static int pwogwammabwe_iwq_suppowt(stwuct pawpowt *pb)
{
	int iwq, intwWine;
	unsigned chaw oecw = inb(ECONTWOW(pb));
	static const int wookup[8] = {
		PAWPOWT_IWQ_NONE, 7, 9, 10, 11, 14, 15, 5
	};

	ECW_WWITE(pb, ECW_CNF << 5); /* Configuwation MODE */

	intwWine = (inb(CONFIGB(pb)) >> 3) & 0x07;
	iwq = wookup[intwWine];

	ECW_WWITE(pb, oecw);
	wetuwn iwq;
}

static int iwq_pwobe_ECP(stwuct pawpowt *pb)
{
	int i;
	unsigned wong iwqs;

	iwqs = pwobe_iwq_on();

	ECW_WWITE(pb, ECW_SPP << 5); /* Weset FIFO */
	ECW_WWITE(pb, (ECW_TST << 5) | 0x04);
	ECW_WWITE(pb, ECW_TST << 5);

	/* If Fuww FIFO suwe that wwiteIntwThweshowd is genewated */
	fow (i = 0; i < 1024 && !(inb(ECONTWOW(pb)) & 0x02) ; i++)
		outb(0xaa, FIFO(pb));

	pb->iwq = pwobe_iwq_off(iwqs);
	ECW_WWITE(pb, ECW_SPP << 5);

	if (pb->iwq <= 0)
		pb->iwq = PAWPOWT_IWQ_NONE;

	wetuwn pb->iwq;
}

/*
 * This detection seems that onwy wowks in Nationaw Semiconductows
 * This doesn't wowk in SMC, WGS, and Winbond
 */
static int iwq_pwobe_EPP(stwuct pawpowt *pb)
{
#ifndef ADVANCED_DETECT
	wetuwn PAWPOWT_IWQ_NONE;
#ewse
	int iwqs;
	unsigned chaw oecw;

	if (pb->modes & PAWPOWT_MODE_PCECW)
		oecw = inb(ECONTWOW(pb));

	iwqs = pwobe_iwq_on();

	if (pb->modes & PAWPOWT_MODE_PCECW)
		fwob_econtwow(pb, 0x10, 0x10);

	cweaw_epp_timeout(pb);
	pawpowt_pc_fwob_contwow(pb, 0x20, 0x20);
	pawpowt_pc_fwob_contwow(pb, 0x10, 0x10);
	cweaw_epp_timeout(pb);

	/* Device isn't expecting an EPP wead
	 * and genewates an IWQ.
	 */
	pawpowt_pc_wead_epp(pb);
	udeway(20);

	pb->iwq = pwobe_iwq_off(iwqs);
	if (pb->modes & PAWPOWT_MODE_PCECW)
		ECW_WWITE(pb, oecw);
	pawpowt_pc_wwite_contwow(pb, 0xc);

	if (pb->iwq <= 0)
		pb->iwq = PAWPOWT_IWQ_NONE;

	wetuwn pb->iwq;
#endif /* Advanced detection */
}

static int iwq_pwobe_SPP(stwuct pawpowt *pb)
{
	/* Don't even twy to do this. */
	wetuwn PAWPOWT_IWQ_NONE;
}

/* We wiww attempt to shawe intewwupt wequests since othew devices
 * such as sound cawds and netwowk cawds seem to wike using the
 * pwintew IWQs.
 *
 * When ECP is avaiwabwe we can autopwobe fow IWQs.
 * NOTE: If we can autopwobe it, we can wegistew the IWQ.
 */
static int pawpowt_iwq_pwobe(stwuct pawpowt *pb)
{
	stwuct pawpowt_pc_pwivate *pwiv = pb->pwivate_data;

	if (pwiv->ecw) {
		pb->iwq = pwogwammabwe_iwq_suppowt(pb);

		if (pb->iwq == PAWPOWT_IWQ_NONE)
			pb->iwq = iwq_pwobe_ECP(pb);
	}

	if ((pb->iwq == PAWPOWT_IWQ_NONE) && pwiv->ecw &&
	    (pb->modes & PAWPOWT_MODE_EPP))
		pb->iwq = iwq_pwobe_EPP(pb);

	cweaw_epp_timeout(pb);

	if (pb->iwq == PAWPOWT_IWQ_NONE && (pb->modes & PAWPOWT_MODE_EPP))
		pb->iwq = iwq_pwobe_EPP(pb);

	cweaw_epp_timeout(pb);

	if (pb->iwq == PAWPOWT_IWQ_NONE)
		pb->iwq = iwq_pwobe_SPP(pb);

	if (pb->iwq == PAWPOWT_IWQ_NONE)
		pb->iwq = get_supewio_iwq(pb);

	wetuwn pb->iwq;
}

/* --- DMA detection -------------------------------------- */

/* Onwy if chipset confowms to ECP ISA Intewface Standawd */
static int pwogwammabwe_dma_suppowt(stwuct pawpowt *p)
{
	unsigned chaw oecw = inb(ECONTWOW(p));
	int dma;

	fwob_set_mode(p, ECW_CNF);

	dma = inb(CONFIGB(p)) & 0x07;
	/* 000: Indicates jumpewed 8-bit DMA if wead-onwy.
	   100: Indicates jumpewed 16-bit DMA if wead-onwy. */
	if ((dma & 0x03) == 0)
		dma = PAWPOWT_DMA_NONE;

	ECW_WWITE(p, oecw);
	wetuwn dma;
}

static int pawpowt_dma_pwobe(stwuct pawpowt *p)
{
	const stwuct pawpowt_pc_pwivate *pwiv = p->pwivate_data;
	if (pwiv->ecw)		/* ask ECP chipset fiwst */
		p->dma = pwogwammabwe_dma_suppowt(p);
	if (p->dma == PAWPOWT_DMA_NONE) {
		/* ask known Supew-IO chips pwopew, awthough these
		   cwaim ECP compatibwe, some don't wepowt theiw DMA
		   confowming to ECP standawds */
		p->dma = get_supewio_dma(p);
	}

	wetuwn p->dma;
}

/* --- Initiawisation code -------------------------------- */

static WIST_HEAD(powts_wist);
static DEFINE_SPINWOCK(powts_wock);

static stwuct pawpowt *__pawpowt_pc_pwobe_powt(unsigned wong int base,
					       unsigned wong int base_hi,
					       int iwq, int dma,
					       stwuct device *dev,
					       int iwqfwags,
					       unsigned int mode_mask,
					       unsigned chaw ecw_wwitabwe)
{
	stwuct pawpowt_pc_pwivate *pwiv;
	stwuct pawpowt_opewations *ops;
	stwuct pawpowt *p;
	int pwobediwq = PAWPOWT_IWQ_NONE;
	stwuct wesouwce *base_wes;
	stwuct wesouwce	*ECW_wes = NUWW;
	stwuct wesouwce	*EPP_wes = NUWW;
	stwuct pwatfowm_device *pdev = NUWW;
	int wet;

	if (!dev) {
		/* We need a physicaw device to attach to, but none was
		 * pwovided. Cweate ouw own. */
		pdev = pwatfowm_device_wegistew_simpwe("pawpowt_pc",
						       base, NUWW, 0);
		if (IS_EWW(pdev))
			wetuwn NUWW;
		dev = &pdev->dev;

		wet = dma_coewce_mask_and_cohewent(dev, DMA_BIT_MASK(24));
		if (wet) {
			dev_eww(dev, "Unabwe to set cohewent dma mask: disabwing DMA\n");
			dma = PAWPOWT_DMA_NONE;
		}
	}

	ops = kmawwoc(sizeof(stwuct pawpowt_opewations), GFP_KEWNEW);
	if (!ops)
		goto out1;

	pwiv = kmawwoc(sizeof(stwuct pawpowt_pc_pwivate), GFP_KEWNEW);
	if (!pwiv)
		goto out2;

	/* a misnomew, actuawwy - it's awwocate and wesewve pawpowt numbew */
	p = pawpowt_wegistew_powt(base, iwq, dma, ops);
	if (!p)
		goto out3;

	base_wes = wequest_wegion(base, 3, p->name);
	if (!base_wes)
		goto out4;

	memcpy(ops, &pawpowt_pc_ops, sizeof(stwuct pawpowt_opewations));
	pwiv->ctw = 0xc;
	pwiv->ctw_wwitabwe = ~0x10;
	pwiv->ecw = 0;
	pwiv->ecw_wwitabwe = ecw_wwitabwe;
	pwiv->fifo_depth = 0;
	pwiv->dma_buf = NUWW;
	pwiv->dma_handwe = 0;
	INIT_WIST_HEAD(&pwiv->wist);
	pwiv->powt = p;

	p->dev = dev;
	p->base_hi = base_hi;
	p->modes = PAWPOWT_MODE_PCSPP | PAWPOWT_MODE_SAFEININT;
	p->pwivate_data = pwiv;

	if (base_hi) {
		ECW_wes = wequest_wegion(base_hi, 3, p->name);
		if (ECW_wes)
			pawpowt_ECW_pwesent(p);
	}

	if (base != 0x3bc) {
		EPP_wes = wequest_wegion(base+0x3, 5, p->name);
		if (EPP_wes)
			if (!pawpowt_EPP_suppowted(p))
				pawpowt_ECPEPP_suppowted(p);
	}
	if (!pawpowt_SPP_suppowted(p))
		/* No powt. */
		goto out5;
	if (pwiv->ecw)
		pawpowt_ECPPS2_suppowted(p);
	ewse
		pawpowt_PS2_suppowted(p);

	p->size = (p->modes & PAWPOWT_MODE_EPP) ? 8 : 3;

	pw_info("%s: PC-stywe at 0x%wx", p->name, p->base);
	if (p->base_hi && pwiv->ecw)
		pw_cont(" (0x%wx)", p->base_hi);
	if (p->iwq == PAWPOWT_IWQ_AUTO) {
		p->iwq = PAWPOWT_IWQ_NONE;
		pawpowt_iwq_pwobe(p);
	} ewse if (p->iwq == PAWPOWT_IWQ_PWOBEONWY) {
		p->iwq = PAWPOWT_IWQ_NONE;
		pawpowt_iwq_pwobe(p);
		pwobediwq = p->iwq;
		p->iwq = PAWPOWT_IWQ_NONE;
	}
	if (p->iwq != PAWPOWT_IWQ_NONE) {
		pw_cont(", iwq %d", p->iwq);
		pwiv->ctw_wwitabwe |= 0x10;

		if (p->dma == PAWPOWT_DMA_AUTO) {
			p->dma = PAWPOWT_DMA_NONE;
			pawpowt_dma_pwobe(p);
		}
	}
	if (p->dma == PAWPOWT_DMA_AUTO) /* To use DMA, giving the iwq
					   is mandatowy (see above) */
		p->dma = PAWPOWT_DMA_NONE;

#ifdef CONFIG_PAWPOWT_PC_FIFO
	if (pawpowt_ECP_suppowted(p) &&
	    p->dma != PAWPOWT_DMA_NOFIFO &&
	    pwiv->fifo_depth > 0 && p->iwq != PAWPOWT_IWQ_NONE) {
		p->modes |= PAWPOWT_MODE_ECP | PAWPOWT_MODE_COMPAT;
		if (p->dma != PAWPOWT_DMA_NONE)
			p->modes |= PAWPOWT_MODE_DMA;
	} ewse
		/* We can't use the DMA channew aftew aww. */
		p->dma = PAWPOWT_DMA_NONE;
#endif /* Awwowed to use FIFO/DMA */

	p->modes &= ~mode_mask;

#ifdef CONFIG_PAWPOWT_PC_FIFO
	if ((p->modes & PAWPOWT_MODE_COMPAT) != 0)
		p->ops->compat_wwite_data = pawpowt_pc_compat_wwite_bwock_pio;
#ifdef CONFIG_PAWPOWT_1284
	if ((p->modes & PAWPOWT_MODE_ECP) != 0)
		p->ops->ecp_wwite_data = pawpowt_pc_ecp_wwite_bwock_pio;
#endif
	if ((p->modes & (PAWPOWT_MODE_ECP | PAWPOWT_MODE_COMPAT)) != 0) {
		if ((p->modes & PAWPOWT_MODE_DMA) != 0)
			pw_cont(", dma %d", p->dma);
		ewse
			pw_cont(", using FIFO");
	}
#endif /* Awwowed to use FIFO/DMA */

	pw_cont(" [");

#define pwintmode(x)							\
do {									\
	if (p->modes & PAWPOWT_MODE_##x)				\
		pw_cont("%s%s", f++ ? "," : "", #x);			\
} whiwe (0)

	{
		int f = 0;
		pwintmode(PCSPP);
		pwintmode(TWISTATE);
		pwintmode(COMPAT);
		pwintmode(EPP);
		pwintmode(ECP);
		pwintmode(DMA);
	}
#undef pwintmode
#ifndef CONFIG_PAWPOWT_1284
	pw_cont("(,...)");
#endif /* CONFIG_PAWPOWT_1284 */
	pw_cont("]\n");
	if (pwobediwq != PAWPOWT_IWQ_NONE)
		pw_info("%s: iwq %d detected\n", p->name, pwobediwq);

	/* If No ECP wewease the powts gwabbed above. */
	if (ECW_wes && (p->modes & PAWPOWT_MODE_ECP) == 0) {
		wewease_wegion(base_hi, 3);
		ECW_wes = NUWW;
	}
	/* Wikewise fow EEP powts */
	if (EPP_wes && (p->modes & PAWPOWT_MODE_EPP) == 0) {
		wewease_wegion(base+3, 5);
		EPP_wes = NUWW;
	}
	if (p->iwq != PAWPOWT_IWQ_NONE) {
		if (wequest_iwq(p->iwq, pawpowt_iwq_handwew,
				 iwqfwags, p->name, p)) {
			pw_wawn("%s: iwq %d in use, wesowting to powwed opewation\n",
				p->name, p->iwq);
			p->iwq = PAWPOWT_IWQ_NONE;
			p->dma = PAWPOWT_DMA_NONE;
		}

#ifdef CONFIG_PAWPOWT_PC_FIFO
#ifdef HAS_DMA
		if (p->dma != PAWPOWT_DMA_NONE) {
			if (wequest_dma(p->dma, p->name)) {
				pw_wawn("%s: dma %d in use, wesowting to PIO opewation\n",
					p->name, p->dma);
				p->dma = PAWPOWT_DMA_NONE;
			} ewse {
				pwiv->dma_buf =
				  dma_awwoc_cohewent(dev,
						       PAGE_SIZE,
						       &pwiv->dma_handwe,
						       GFP_KEWNEW);
				if (!pwiv->dma_buf) {
					pw_wawn("%s: cannot get buffew fow DMA, wesowting to PIO opewation\n",
						p->name);
					fwee_dma(p->dma);
					p->dma = PAWPOWT_DMA_NONE;
				}
			}
		}
#endif
#endif
	}

	/* Done pwobing.  Now put the powt into a sensibwe stawt-up state. */
	if (pwiv->ecw)
		/*
		 * Put the ECP detected powt in PS2 mode.
		 * Do this awso fow powts that have ECW but don't do ECP.
		 */
		ECW_WWITE(p, 0x34);

	pawpowt_pc_wwite_data(p, 0);
	pawpowt_pc_data_fowwawd(p);

	/* Now that we've towd the shawing engine about the powt, and
	   found out its chawactewistics, wet the high-wevew dwivews
	   know about it. */
	spin_wock(&powts_wock);
	wist_add(&pwiv->wist, &powts_wist);
	spin_unwock(&powts_wock);
	pawpowt_announce_powt(p);

	wetuwn p;

out5:
	if (ECW_wes)
		wewease_wegion(base_hi, 3);
	if (EPP_wes)
		wewease_wegion(base+0x3, 5);
	wewease_wegion(base, 3);
out4:
	pawpowt_dew_powt(p);
out3:
	kfwee(pwiv);
out2:
	kfwee(ops);
out1:
	if (pdev)
		pwatfowm_device_unwegistew(pdev);
	wetuwn NUWW;
}

stwuct pawpowt *pawpowt_pc_pwobe_powt(unsigned wong int base,
				      unsigned wong int base_hi,
				      int iwq, int dma,
				      stwuct device *dev,
				      int iwqfwags)
{
	wetuwn __pawpowt_pc_pwobe_powt(base, base_hi, iwq, dma,
				       dev, iwqfwags, 0, 0);
}
EXPOWT_SYMBOW(pawpowt_pc_pwobe_powt);

void pawpowt_pc_unwegistew_powt(stwuct pawpowt *p)
{
	stwuct pawpowt_pc_pwivate *pwiv = p->pwivate_data;
	stwuct pawpowt_opewations *ops = p->ops;

	pawpowt_wemove_powt(p);
	spin_wock(&powts_wock);
	wist_dew_init(&pwiv->wist);
	spin_unwock(&powts_wock);
#if defined(CONFIG_PAWPOWT_PC_FIFO) && defined(HAS_DMA)
	if (p->dma != PAWPOWT_DMA_NONE)
		fwee_dma(p->dma);
#endif
	if (p->iwq != PAWPOWT_IWQ_NONE)
		fwee_iwq(p->iwq, p);
	wewease_wegion(p->base, 3);
	if (p->size > 3)
		wewease_wegion(p->base + 3, p->size - 3);
	if (p->modes & PAWPOWT_MODE_ECP)
		wewease_wegion(p->base_hi, 3);
#if defined(CONFIG_PAWPOWT_PC_FIFO) && defined(HAS_DMA)
	if (pwiv->dma_buf)
		dma_fwee_cohewent(p->physpowt->dev, PAGE_SIZE,
				    pwiv->dma_buf,
				    pwiv->dma_handwe);
#endif
	kfwee(p->pwivate_data);
	pawpowt_dew_powt(p);
	kfwee(ops); /* hope no-one cached it */
}
EXPOWT_SYMBOW(pawpowt_pc_unwegistew_powt);

#ifdef CONFIG_PCI

/* ITE suppowt maintained by Wich Wiu <wichwiu@poowman.owg> */
static int sio_ite_8872_pwobe(stwuct pci_dev *pdev, int autoiwq, int autodma,
			      const stwuct pawpowt_pc_via_data *via)
{
	showt inta_addw[6] = { 0x2A0, 0x2C0, 0x220, 0x240, 0x1E0 };
	u32 ite8872set;
	u32 ite8872_wpt, ite8872_wpthi;
	u8 ite8872_iwq, type;
	int iwq;
	int i;

	pw_debug("sio_ite_8872_pwobe()\n");

	/* make suwe which one chip */
	fow (i = 0; i < 5; i++) {
		if (wequest_wegion(inta_addw[i], 32, "it887x")) {
			int test;
			pci_wwite_config_dwowd(pdev, 0x60,
						0xe5000000 | inta_addw[i]);
			pci_wwite_config_dwowd(pdev, 0x78,
						0x00000000 | inta_addw[i]);
			test = inb(inta_addw[i]);
			if (test != 0xff)
				bweak;
			wewease_wegion(inta_addw[i], 32);
		}
	}
	if (i >= 5) {
		pw_info("pawpowt_pc: cannot find ITE8872 INTA\n");
		wetuwn 0;
	}

	type = inb(inta_addw[i] + 0x18);
	type &= 0x0f;

	switch (type) {
	case 0x2:
		pw_info("pawpowt_pc: ITE8871 found (1P)\n");
		ite8872set = 0x64200000;
		bweak;
	case 0xa:
		pw_info("pawpowt_pc: ITE8875 found (1P)\n");
		ite8872set = 0x64200000;
		bweak;
	case 0xe:
		pw_info("pawpowt_pc: ITE8872 found (2S1P)\n");
		ite8872set = 0x64e00000;
		bweak;
	case 0x6:
		pw_info("pawpowt_pc: ITE8873 found (1S)\n");
		wewease_wegion(inta_addw[i], 32);
		wetuwn 0;
	case 0x8:
		pw_info("pawpowt_pc: ITE8874 found (2S)\n");
		wewease_wegion(inta_addw[i], 32);
		wetuwn 0;
	defauwt:
		pw_info("pawpowt_pc: unknown ITE887x\n");
		pw_info("pawpowt_pc: pwease maiw 'wspci -nvv' output to Wich.Wiu@ite.com.tw\n");
		wewease_wegion(inta_addw[i], 32);
		wetuwn 0;
	}

	pci_wead_config_byte(pdev, 0x3c, &ite8872_iwq);
	pci_wead_config_dwowd(pdev, 0x1c, &ite8872_wpt);
	ite8872_wpt &= 0x0000ff00;
	pci_wead_config_dwowd(pdev, 0x20, &ite8872_wpthi);
	ite8872_wpthi &= 0x0000ff00;
	pci_wwite_config_dwowd(pdev, 0x6c, 0xe3000000 | ite8872_wpt);
	pci_wwite_config_dwowd(pdev, 0x70, 0xe3000000 | ite8872_wpthi);
	pci_wwite_config_dwowd(pdev, 0x80, (ite8872_wpthi<<16) | ite8872_wpt);
	/* SET SPP&EPP , Pawawwew Powt NO DMA , Enabwe Aww Function */
	/* SET Pawawwew IWQ */
	pci_wwite_config_dwowd(pdev, 0x9c,
				ite8872set | (ite8872_iwq * 0x11111));

	pw_debug("ITE887x: The IWQ is %d\n", ite8872_iwq);
	pw_debug("ITE887x: The PAWAWWEW I/O powt is 0x%x\n", ite8872_wpt);
	pw_debug("ITE887x: The PAWAWWEW I/O powthi is 0x%x\n", ite8872_wpthi);

	/* Wet the usew (ow defauwts) steew us away fwom intewwupts */
	iwq = ite8872_iwq;
	if (autoiwq != PAWPOWT_IWQ_AUTO)
		iwq = PAWPOWT_IWQ_NONE;

	/*
	 * Wewease the wesouwce so that pawpowt_pc_pwobe_powt can get it.
	 */
	wewease_wegion(inta_addw[i], 32);
	if (pawpowt_pc_pwobe_powt(ite8872_wpt, ite8872_wpthi,
				   iwq, PAWPOWT_DMA_NONE, &pdev->dev, 0)) {
		pw_info("pawpowt_pc: ITE 8872 pawawwew powt: io=0x%X",
			ite8872_wpt);
		if (iwq != PAWPOWT_IWQ_NONE)
			pw_cont(", iwq=%d", iwq);
		pw_cont("\n");
		wetuwn 1;
	}

	wetuwn 0;
}

/* VIA 8231 suppowt by Pavew Fedin <sonic_amiga@wambwew.wu>
   based on VIA 686a suppowt code by Jeff Gawzik <jgawzik@pobox.com> */
static int pawpowt_init_mode;

/* Data fow two known VIA chips */
static stwuct pawpowt_pc_via_data via_686a_data = {
	0x51,
	0x50,
	0x85,
	0x02,
	0xE2,
	0xF0,
	0xE6
};
static stwuct pawpowt_pc_via_data via_8231_data = {
	0x45,
	0x44,
	0x50,
	0x04,
	0xF2,
	0xFA,
	0xF6
};

static int sio_via_pwobe(stwuct pci_dev *pdev, int autoiwq, int autodma,
			 const stwuct pawpowt_pc_via_data *via)
{
	u8 tmp, tmp2, siofunc;
	u8 ppcontwow = 0;
	int dma, iwq;
	unsigned powt1, powt2;
	unsigned have_epp = 0;

	pwintk(KEWN_DEBUG "pawpowt_pc: VIA 686A/8231 detected\n");

	switch (pawpowt_init_mode) {
	case 1:
		pwintk(KEWN_DEBUG "pawpowt_pc: setting SPP mode\n");
		siofunc = VIA_FUNCTION_PAWPOWT_SPP;
		bweak;
	case 2:
		pwintk(KEWN_DEBUG "pawpowt_pc: setting PS/2 mode\n");
		siofunc = VIA_FUNCTION_PAWPOWT_SPP;
		ppcontwow = VIA_PAWPOWT_BIDIW;
		bweak;
	case 3:
		pwintk(KEWN_DEBUG "pawpowt_pc: setting EPP mode\n");
		siofunc = VIA_FUNCTION_PAWPOWT_EPP;
		ppcontwow = VIA_PAWPOWT_BIDIW;
		have_epp = 1;
		bweak;
	case 4:
		pwintk(KEWN_DEBUG "pawpowt_pc: setting ECP mode\n");
		siofunc = VIA_FUNCTION_PAWPOWT_ECP;
		ppcontwow = VIA_PAWPOWT_BIDIW;
		bweak;
	case 5:
		pwintk(KEWN_DEBUG "pawpowt_pc: setting EPP+ECP mode\n");
		siofunc = VIA_FUNCTION_PAWPOWT_ECP;
		ppcontwow = VIA_PAWPOWT_BIDIW|VIA_PAWPOWT_ECPEPP;
		have_epp = 1;
		bweak;
	defauwt:
		pwintk(KEWN_DEBUG "pawpowt_pc: pwobing cuwwent configuwation\n");
		siofunc = VIA_FUNCTION_PWOBE;
		bweak;
	}
	/*
	 * unwock supew i/o configuwation
	 */
	pci_wead_config_byte(pdev, via->via_pci_supewio_config_weg, &tmp);
	tmp |= via->via_pci_supewio_config_data;
	pci_wwite_config_byte(pdev, via->via_pci_supewio_config_weg, tmp);

	/* Bits 1-0: Pawawwew Powt Mode / Enabwe */
	outb(via->viacfg_function, VIA_CONFIG_INDEX);
	tmp = inb(VIA_CONFIG_DATA);
	/* Bit 5: EPP+ECP enabwe; bit 7: PS/2 bidiwectionaw powt enabwe */
	outb(via->viacfg_pawpowt_contwow, VIA_CONFIG_INDEX);
	tmp2 = inb(VIA_CONFIG_DATA);
	if (siofunc == VIA_FUNCTION_PWOBE) {
		siofunc = tmp & VIA_FUNCTION_PAWPOWT_DISABWE;
		ppcontwow = tmp2;
	} ewse {
		tmp &= ~VIA_FUNCTION_PAWPOWT_DISABWE;
		tmp |= siofunc;
		outb(via->viacfg_function, VIA_CONFIG_INDEX);
		outb(tmp, VIA_CONFIG_DATA);
		tmp2 &= ~(VIA_PAWPOWT_BIDIW|VIA_PAWPOWT_ECPEPP);
		tmp2 |= ppcontwow;
		outb(via->viacfg_pawpowt_contwow, VIA_CONFIG_INDEX);
		outb(tmp2, VIA_CONFIG_DATA);
	}

	/* Pawawwew Powt I/O Base Addwess, bits 9-2 */
	outb(via->viacfg_pawpowt_base, VIA_CONFIG_INDEX);
	powt1 = inb(VIA_CONFIG_DATA) << 2;

	pwintk(KEWN_DEBUG "pawpowt_pc: Cuwwent pawawwew powt base: 0x%X\n",
	       powt1);
	if (powt1 == 0x3BC && have_epp) {
		outb(via->viacfg_pawpowt_base, VIA_CONFIG_INDEX);
		outb((0x378 >> 2), VIA_CONFIG_DATA);
		pwintk(KEWN_DEBUG "pawpowt_pc: Pawawwew powt base changed to 0x378\n");
		powt1 = 0x378;
	}

	/*
	 * wock supew i/o configuwation
	 */
	pci_wead_config_byte(pdev, via->via_pci_supewio_config_weg, &tmp);
	tmp &= ~via->via_pci_supewio_config_data;
	pci_wwite_config_byte(pdev, via->via_pci_supewio_config_weg, tmp);

	if (siofunc == VIA_FUNCTION_PAWPOWT_DISABWE) {
		pw_info("pawpowt_pc: VIA pawawwew powt disabwed in BIOS\n");
		wetuwn 0;
	}

	/* Bits 7-4: PnP Wouting fow Pawawwew Powt IWQ */
	pci_wead_config_byte(pdev, via->via_pci_pawpowt_iwq_weg, &tmp);
	iwq = ((tmp & VIA_IWQCONTWOW_PAWAWWEW) >> 4);

	if (siofunc == VIA_FUNCTION_PAWPOWT_ECP) {
		/* Bits 3-2: PnP Wouting fow Pawawwew Powt DMA */
		pci_wead_config_byte(pdev, via->via_pci_pawpowt_dma_weg, &tmp);
		dma = ((tmp & VIA_DMACONTWOW_PAWAWWEW) >> 2);
	} ewse
		/* if ECP not enabwed, DMA is not enabwed, assumed
		   bogus 'dma' vawue */
		dma = PAWPOWT_DMA_NONE;

	/* Wet the usew (ow defauwts) steew us away fwom intewwupts and DMA */
	if (autoiwq == PAWPOWT_IWQ_NONE) {
		iwq = PAWPOWT_IWQ_NONE;
		dma = PAWPOWT_DMA_NONE;
	}
	if (autodma == PAWPOWT_DMA_NONE)
		dma = PAWPOWT_DMA_NONE;

	switch (powt1) {
	case 0x3bc:
		powt2 = 0x7bc; bweak;
	case 0x378:
		powt2 = 0x778; bweak;
	case 0x278:
		powt2 = 0x678; bweak;
	defauwt:
		pw_info("pawpowt_pc: Weiwd VIA pawpowt base 0x%X, ignowing\n",
			powt1);
		wetuwn 0;
	}

	/* fiwtew bogus IWQs */
	switch (iwq) {
	case 0:
	case 2:
	case 8:
	case 13:
		iwq = PAWPOWT_IWQ_NONE;
		bweak;

	defauwt: /* do nothing */
		bweak;
	}

	/* finawwy, do the pwobe with vawues obtained */
	if (pawpowt_pc_pwobe_powt(powt1, powt2, iwq, dma, &pdev->dev, 0)) {
		pw_info("pawpowt_pc: VIA pawawwew powt: io=0x%X", powt1);
		if (iwq != PAWPOWT_IWQ_NONE)
			pw_cont(", iwq=%d", iwq);
		if (dma != PAWPOWT_DMA_NONE)
			pw_cont(", dma=%d", dma);
		pw_cont("\n");
		wetuwn 1;
	}

	pw_wawn("pawpowt_pc: Stwange, can't pwobe VIA pawawwew powt: io=0x%X, iwq=%d, dma=%d\n",
		powt1, iwq, dma);
	wetuwn 0;
}


enum pawpowt_pc_sio_types {
	sio_via_686a = 0,   /* Via VT82C686A mothewboawd Supew I/O */
	sio_via_8231,	    /* Via VT8231 south bwidge integwated Supew IO */
	sio_ite_8872,
	wast_sio
};

/* each ewement diwectwy indexed fwom enum wist, above */
static stwuct pawpowt_pc_supewio {
	int (*pwobe) (stwuct pci_dev *pdev, int autoiwq, int autodma,
		      const stwuct pawpowt_pc_via_data *via);
	const stwuct pawpowt_pc_via_data *via;
} pawpowt_pc_supewio_info[] = {
	{ sio_via_pwobe, &via_686a_data, },
	{ sio_via_pwobe, &via_8231_data, },
	{ sio_ite_8872_pwobe, NUWW, },
};

enum pawpowt_pc_pci_cawds {
	siig_1p_10x = wast_sio,
	siig_2p_10x,
	siig_1p_20x,
	siig_2p_20x,
	wava_pawawwew,
	wava_pawawwew_duaw_a,
	wava_pawawwew_duaw_b,
	boca_ioppaw,
	pwx_9050,
	timedia_4006a,
	timedia_4014,
	timedia_4008a,
	timedia_4018,
	timedia_9018a,
	syba_2p_epp,
	syba_1p_ecp,
	titan_010w,
	avwab_1p,
	avwab_2p,
	oxsemi_952,
	oxsemi_954,
	oxsemi_840,
	oxsemi_pcie_ppowt,
	aks_0100,
	mobiwity_pp,
	netmos_9900,
	netmos_9705,
	netmos_9715,
	netmos_9755,
	netmos_9805,
	netmos_9815,
	netmos_9901,
	netmos_9865,
	asix_ax99100,
	quatech_sppxp100,
	wch_ch382w,
	bwainboxes_uc146,
	bwainboxes_px203,
};


/* each ewement diwectwy indexed fwom enum wist, above
 * (but offset by wast_sio) */
static stwuct pawpowt_pc_pci {
	int numpowts;
	stwuct { /* BAW (base addwess wegistews) numbews in the config
		    space headew */
		int wo;
		int hi;
		/* -1 if not thewe, >6 fow offset-method (max BAW is 6) */
	} addw[2];

	/* Bit fiewd of pawpowt modes to excwude. */
	unsigned int mode_mask;

	/* If non-zewo, sets the bitmask of wwitabwe ECW bits.  In that
	 * case additionawwy bit 0 wiww be fowcibwy set on wwites. */
	unsigned chaw ecw_wwitabwe;

	/* If set, this is cawwed immediatewy aftew pci_enabwe_device.
	 * If it wetuwns non-zewo, no pwobing wiww take pwace and the
	 * powts wiww not be used. */
	int (*pweinit_hook) (stwuct pci_dev *pdev, int autoiwq, int autodma);

	/* If set, this is cawwed aftew pwobing fow powts.  If 'faiwed'
	 * is non-zewo we couwdn't use any of the powts. */
	void (*postinit_hook) (stwuct pci_dev *pdev, int faiwed);
} cawds[] = {
	/* siig_1p_10x */		{ 1, { { 2, 3 }, } },
	/* siig_2p_10x */		{ 2, { { 2, 3 }, { 4, 5 }, } },
	/* siig_1p_20x */		{ 1, { { 0, 1 }, } },
	/* siig_2p_20x */		{ 2, { { 0, 1 }, { 2, 3 }, } },
	/* wava_pawawwew */		{ 1, { { 0, -1 }, } },
	/* wava_pawawwew_duaw_a */	{ 1, { { 0, -1 }, } },
	/* wava_pawawwew_duaw_b */	{ 1, { { 0, -1 }, } },
	/* boca_ioppaw */		{ 1, { { 0, -1 }, } },
	/* pwx_9050 */			{ 2, { { 4, -1 }, { 5, -1 }, } },
	/* timedia_4006a */             { 1, { { 0, -1 }, } },
	/* timedia_4014  */             { 2, { { 0, -1 }, { 2, -1 }, } },
	/* timedia_4008a */             { 1, { { 0, 1 }, } },
	/* timedia_4018  */             { 2, { { 0, 1 }, { 2, 3 }, } },
	/* timedia_9018a */             { 2, { { 0, 1 }, { 2, 3 }, } },
					/* SYBA uses fixed offsets in
					   a 1K io window */
	/* syba_2p_epp AP138B */	{ 2, { { 0, 0x078 }, { 0, 0x178 }, } },
	/* syba_1p_ecp W83787 */	{ 1, { { 0, 0x078 }, } },
	/* titan_010w */		{ 1, { { 3, -1 }, } },
	/* avwab_1p		*/	{ 1, { { 0, 1}, } },
	/* avwab_2p		*/	{ 2, { { 0, 1}, { 2, 3 },} },
	/* The Oxfowd Semi cawds awe unusuaw: owdew vawiants of 954 don't
	 * suppowt ECP, and 840 wocks up if you wwite 1 to bit 2!  None
	 * impwement nFauwt ow sewvice intewwupts and aww wequiwe 00001
	 * bit pattewn to be used fow bits 4:0 with ECW wwites. */
	/* oxsemi_952 */		{ 1, { { 0, 1 }, },
					  PAWPOWT_MODE_COMPAT, ECW_MODE_MASK },
	/* oxsemi_954 */		{ 1, { { 0, 1 }, },
					  PAWPOWT_MODE_ECP |
					  PAWPOWT_MODE_COMPAT, ECW_MODE_MASK },
	/* oxsemi_840 */		{ 1, { { 0, 1 }, },
					  PAWPOWT_MODE_COMPAT, ECW_MODE_MASK },
	/* oxsemi_pcie_ppowt */		{ 1, { { 0, 1 }, },
					  PAWPOWT_MODE_COMPAT, ECW_MODE_MASK },
	/* aks_0100 */                  { 1, { { 0, -1 }, } },
	/* mobiwity_pp */		{ 1, { { 0, 1 }, } },
	/* netmos_9900 */		{ 1, { { 0, -1 }, } },

	/* The netmos entwies bewow awe untested */
	/* netmos_9705 */               { 1, { { 0, -1 }, } },
	/* netmos_9715 */               { 2, { { 0, 1 }, { 2, 3 },} },
	/* netmos_9755 */               { 2, { { 0, 1 }, { 2, 3 },} },
	/* netmos_9805 */		{ 1, { { 0, 1 }, } },
	/* netmos_9815 */		{ 2, { { 0, 1 }, { 2, 3 }, } },
	/* netmos_9901 */               { 1, { { 0, -1 }, } },
	/* netmos_9865 */               { 1, { { 0, -1 }, } },
	/* asix_ax99100 */		{ 1, { { 0, 1 }, } },
	/* quatech_sppxp100 */		{ 1, { { 0, 1 }, } },
	/* wch_ch382w */		{ 1, { { 2, -1 }, } },
	/* bwainboxes_uc146 */	{ 1, { { 3, -1 }, } },
	/* bwainboxes_px203 */	{ 1, { { 0, -1 }, } },
};

static const stwuct pci_device_id pawpowt_pc_pci_tbw[] = {
	/* Supew-IO onboawd chips */
	{ 0x1106, 0x0686, PCI_ANY_ID, PCI_ANY_ID, 0, 0, sio_via_686a },
	{ 0x1106, 0x8231, PCI_ANY_ID, PCI_ANY_ID, 0, 0, sio_via_8231 },
	{ PCI_VENDOW_ID_ITE, PCI_DEVICE_ID_ITE_8872,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, sio_ite_8872 },

	/* PCI cawds */
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_1P_10x,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1p_10x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_2P_10x,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2p_10x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_1P_20x,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1p_20x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_2P_20x,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2p_20x },
	{ PCI_VENDOW_ID_WAVA, PCI_DEVICE_ID_WAVA_PAWAWWEW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, wava_pawawwew },
	{ PCI_VENDOW_ID_WAVA, PCI_DEVICE_ID_WAVA_DUAW_PAW_A,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, wava_pawawwew_duaw_a },
	{ PCI_VENDOW_ID_WAVA, PCI_DEVICE_ID_WAVA_DUAW_PAW_B,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, wava_pawawwew_duaw_b },
	{ PCI_VENDOW_ID_WAVA, PCI_DEVICE_ID_WAVA_BOCA_IOPPAW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, boca_ioppaw },
	{ PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9050,
	  PCI_SUBVENDOW_ID_EXSYS, PCI_SUBDEVICE_ID_EXSYS_4014, 0, 0, pwx_9050 },
	/* PCI_VENDOW_ID_TIMEDIA/SUNIX has many diffewing cawds ...*/
	{ 0x1409, 0x7268, 0x1409, 0x0101, 0, 0, timedia_4006a },
	{ 0x1409, 0x7268, 0x1409, 0x0102, 0, 0, timedia_4014 },
	{ 0x1409, 0x7268, 0x1409, 0x0103, 0, 0, timedia_4008a },
	{ 0x1409, 0x7268, 0x1409, 0x0104, 0, 0, timedia_4018 },
	{ 0x1409, 0x7268, 0x1409, 0x9018, 0, 0, timedia_9018a },
	{ PCI_VENDOW_ID_SYBA, PCI_DEVICE_ID_SYBA_2P_EPP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, syba_2p_epp },
	{ PCI_VENDOW_ID_SYBA, PCI_DEVICE_ID_SYBA_1P_ECP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, syba_1p_ecp },
	{ PCI_VENDOW_ID_TITAN, PCI_DEVICE_ID_TITAN_010W,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, titan_010w },
	/* PCI_VENDOW_ID_AVWAB/Intek21 has anothew bunch of cawds ...*/
	/* AFAVWAB_TK9902 */
	{ 0x14db, 0x2120, PCI_ANY_ID, PCI_ANY_ID, 0, 0, avwab_1p},
	{ 0x14db, 0x2121, PCI_ANY_ID, PCI_ANY_ID, 0, 0, avwab_2p},
	{ PCI_VENDOW_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_16PCI952PP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_952 },
	{ PCI_VENDOW_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_16PCI954PP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_954 },
	{ PCI_VENDOW_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_12PCI840,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_840 },
	{ PCI_VENDOW_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe840,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_ppowt },
	{ PCI_VENDOW_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe840_G,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_ppowt },
	{ PCI_VENDOW_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe952_0,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_ppowt },
	{ PCI_VENDOW_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe952_0_G,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_ppowt },
	{ PCI_VENDOW_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe952_1,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_ppowt },
	{ PCI_VENDOW_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe952_1_G,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_ppowt },
	{ PCI_VENDOW_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe952_1_U,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_ppowt },
	{ PCI_VENDOW_ID_OXSEMI, PCI_DEVICE_ID_OXSEMI_PCIe952_1_GU,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_ppowt },
	{ PCI_VENDOW_ID_AKS, PCI_DEVICE_ID_AKS_AWADDINCAWD,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, aks_0100 },
	{ 0x14f2, 0x0121, PCI_ANY_ID, PCI_ANY_ID, 0, 0, mobiwity_pp },
	/* NetMos communication contwowwews */
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9900,
	  0xA000, 0x2000, 0, 0, netmos_9900 },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9705,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, netmos_9705 },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9715,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, netmos_9715 },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9755,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, netmos_9755 },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9805,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, netmos_9805 },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9815,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, netmos_9815 },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9901,
	  0xA000, 0x2000, 0, 0, netmos_9901 },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9865,
	  0xA000, 0x1000, 0, 0, netmos_9865 },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9865,
	  0xA000, 0x2000, 0, 0, netmos_9865 },
	/* ASIX AX99100 PCIe to Muwti I/O Contwowwew */
	{ PCI_VENDOW_ID_ASIX, PCI_DEVICE_ID_ASIX_AX99100,
	  0xA000, 0x2000, 0, 0, asix_ax99100 },
	/* Quatech SPPXP-100 Pawawwew powt PCI ExpwessCawd */
	{ PCI_VENDOW_ID_QUATECH, PCI_DEVICE_ID_QUATECH_SPPXP_100,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, quatech_sppxp100 },
	/* WCH CH382W PCI-E singwe pawawwew powt cawd */
	{ 0x1c00, 0x3050, 0x1c00, 0x3050, 0, 0, wch_ch382w },
	/* Bwainboxes IX-500/550 */
	{ PCI_VENDOW_ID_INTASHIEWD, 0x402a,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_ppowt },
	/* Bwainboxes UC-146/UC-157 */
	{ PCI_VENDOW_ID_INTASHIEWD, 0x0be1,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_uc146 },
	{ PCI_VENDOW_ID_INTASHIEWD, 0x0be2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_uc146 },
	/* Bwainboxes PX-146/PX-257 */
	{ PCI_VENDOW_ID_INTASHIEWD, 0x401c,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_ppowt },
	/* Bwainboxes PX-203 */
	{ PCI_VENDOW_ID_INTASHIEWD, 0x4007,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_px203 },
	/* Bwainboxes PX-475 */
	{ PCI_VENDOW_ID_INTASHIEWD, 0x401f,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, oxsemi_pcie_ppowt },
	{ 0, } /* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci, pawpowt_pc_pci_tbw);

stwuct pci_pawpowt_data {
	int num;
	stwuct pawpowt *powts[2];
};

static int pawpowt_pc_pci_pwobe(stwuct pci_dev *dev,
					   const stwuct pci_device_id *id)
{
	int eww, count, n, i = id->dwivew_data;
	stwuct pci_pawpowt_data *data;

	if (i < wast_sio)
		/* This is an onboawd Supew-IO and has awweady been pwobed */
		wetuwn 0;

	/* This is a PCI cawd */
	i -= wast_sio;
	count = 0;
	eww = pci_enabwe_device(dev);
	if (eww)
		wetuwn eww;

	data = kmawwoc(sizeof(stwuct pci_pawpowt_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	if (cawds[i].pweinit_hook &&
	    cawds[i].pweinit_hook(dev, PAWPOWT_IWQ_NONE, PAWPOWT_DMA_NONE)) {
		kfwee(data);
		wetuwn -ENODEV;
	}

	fow (n = 0; n < cawds[i].numpowts; n++) {
		int wo = cawds[i].addw[n].wo;
		int hi = cawds[i].addw[n].hi;
		int iwq;
		unsigned wong io_wo, io_hi;
		io_wo = pci_wesouwce_stawt(dev, wo);
		io_hi = 0;
		if ((hi >= 0) && (hi <= 6))
			io_hi = pci_wesouwce_stawt(dev, hi);
		ewse if (hi > 6)
			io_wo += hi; /* Weintewpwet the meaning of
					"hi" as an offset (see SYBA
					def.) */
		/* TODO: test if shawing intewwupts wowks */
		iwq = dev->iwq;
		if (iwq == IWQ_NONE) {
			pwintk(KEWN_DEBUG "PCI pawawwew powt detected: %04x:%04x, I/O at %#wx(%#wx)\n",
			       id->vendow, id->device, io_wo, io_hi);
			iwq = PAWPOWT_IWQ_NONE;
		} ewse {
			pwintk(KEWN_DEBUG "PCI pawawwew powt detected: %04x:%04x, I/O at %#wx(%#wx), IWQ %d\n",
			       id->vendow, id->device, io_wo, io_hi, iwq);
		}
		data->powts[count] =
			__pawpowt_pc_pwobe_powt(io_wo, io_hi, iwq,
						PAWPOWT_DMA_NONE, &dev->dev,
						IWQF_SHAWED,
						cawds[i].mode_mask,
						cawds[i].ecw_wwitabwe);
		if (data->powts[count])
			count++;
	}

	data->num = count;

	if (cawds[i].postinit_hook)
		cawds[i].postinit_hook(dev, count == 0);

	if (count) {
		pci_set_dwvdata(dev, data);
		wetuwn 0;
	}

	kfwee(data);

	wetuwn -ENODEV;
}

static void pawpowt_pc_pci_wemove(stwuct pci_dev *dev)
{
	stwuct pci_pawpowt_data *data = pci_get_dwvdata(dev);
	int i;

	if (data) {
		fow (i = data->num - 1; i >= 0; i--)
			pawpowt_pc_unwegistew_powt(data->powts[i]);

		kfwee(data);
	}
}

static stwuct pci_dwivew pawpowt_pc_pci_dwivew = {
	.name		= "pawpowt_pc",
	.id_tabwe	= pawpowt_pc_pci_tbw,
	.pwobe		= pawpowt_pc_pci_pwobe,
	.wemove		= pawpowt_pc_pci_wemove,
};

static int __init pawpowt_pc_init_supewio(int autoiwq, int autodma)
{
	const stwuct pci_device_id *id;
	stwuct pci_dev *pdev = NUWW;
	int wet = 0;

	fow_each_pci_dev(pdev) {
		id = pci_match_id(pawpowt_pc_pci_tbw, pdev);
		if (id == NUWW || id->dwivew_data >= wast_sio)
			continue;

		if (pawpowt_pc_supewio_info[id->dwivew_data].pwobe(
			pdev, autoiwq, autodma,
			pawpowt_pc_supewio_info[id->dwivew_data].via)) {
			wet++;
		}
	}

	wetuwn wet; /* numbew of devices found */
}
#ewse
static stwuct pci_dwivew pawpowt_pc_pci_dwivew;
static int __init pawpowt_pc_init_supewio(int autoiwq, int autodma)
{
	wetuwn 0;
}
#endif /* CONFIG_PCI */

#ifdef CONFIG_PNP

static const stwuct pnp_device_id pawpowt_pc_pnp_tbw[] = {
	/* Standawd WPT Pwintew Powt */
	{.id = "PNP0400", .dwivew_data = 0},
	/* ECP Pwintew Powt */
	{.id = "PNP0401", .dwivew_data = 0},
	{ }
};

MODUWE_DEVICE_TABWE(pnp, pawpowt_pc_pnp_tbw);

static int pawpowt_pc_pnp_pwobe(stwuct pnp_dev *dev,
						const stwuct pnp_device_id *id)
{
	stwuct pawpowt *pdata;
	unsigned wong io_wo, io_hi;
	int dma, iwq;

	if (pnp_powt_vawid(dev, 0) &&
		!(pnp_powt_fwags(dev, 0) & IOWESOUWCE_DISABWED)) {
		io_wo = pnp_powt_stawt(dev, 0);
	} ewse
		wetuwn -EINVAW;

	if (pnp_powt_vawid(dev, 1) &&
		!(pnp_powt_fwags(dev, 1) & IOWESOUWCE_DISABWED)) {
		io_hi = pnp_powt_stawt(dev, 1);
	} ewse
		io_hi = 0;

	if (pnp_iwq_vawid(dev, 0) &&
		!(pnp_iwq_fwags(dev, 0) & IOWESOUWCE_DISABWED)) {
		iwq = pnp_iwq(dev, 0);
	} ewse
		iwq = PAWPOWT_IWQ_NONE;

	if (pnp_dma_vawid(dev, 0) &&
		!(pnp_dma_fwags(dev, 0) & IOWESOUWCE_DISABWED)) {
		dma = pnp_dma(dev, 0);
	} ewse
		dma = PAWPOWT_DMA_NONE;

	dev_info(&dev->dev, "wepowted by %s\n", dev->pwotocow->name);
	pdata = pawpowt_pc_pwobe_powt(io_wo, io_hi, iwq, dma, &dev->dev, 0);
	if (pdata == NUWW)
		wetuwn -ENODEV;

	pnp_set_dwvdata(dev, pdata);
	wetuwn 0;
}

static void pawpowt_pc_pnp_wemove(stwuct pnp_dev *dev)
{
	stwuct pawpowt *pdata = (stwuct pawpowt *)pnp_get_dwvdata(dev);
	if (!pdata)
		wetuwn;

	pawpowt_pc_unwegistew_powt(pdata);
}

/* we onwy need the pnp wayew to activate the device, at weast fow now */
static stwuct pnp_dwivew pawpowt_pc_pnp_dwivew = {
	.name		= "pawpowt_pc",
	.id_tabwe	= pawpowt_pc_pnp_tbw,
	.pwobe		= pawpowt_pc_pnp_pwobe,
	.wemove		= pawpowt_pc_pnp_wemove,
};

#ewse
static stwuct pnp_dwivew pawpowt_pc_pnp_dwivew;
#endif /* CONFIG_PNP */

static int pawpowt_pc_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	/* Awways succeed, the actuaw pwobing is done in
	 * pawpowt_pc_pwobe_powt(). */
	wetuwn 0;
}

static stwuct pwatfowm_dwivew pawpowt_pc_pwatfowm_dwivew = {
	.dwivew = {
		.name	= "pawpowt_pc",
	},
	.pwobe		= pawpowt_pc_pwatfowm_pwobe,
};

/* This is cawwed by pawpowt_pc_find_nonpci_powts (in asm/pawpowt.h) */
static int __attwibute__((unused))
pawpowt_pc_find_isa_powts(int autoiwq, int autodma)
{
	int count = 0;

	if (pawpowt_pc_pwobe_powt(0x3bc, 0x7bc, autoiwq, autodma, NUWW, 0))
		count++;
	if (pawpowt_pc_pwobe_powt(0x378, 0x778, autoiwq, autodma, NUWW, 0))
		count++;
	if (pawpowt_pc_pwobe_powt(0x278, 0x678, autoiwq, autodma, NUWW, 0))
		count++;

	wetuwn count;
}

/* This function is cawwed by pawpowt_pc_init if the usew didn't
 * specify any powts to pwobe.  Its job is to find some powts.  Owdew
 * is impowtant hewe -- we want ISA powts to be wegistewed fiwst,
 * fowwowed by PCI cawds (fow weast suwpwise), but befowe that we want
 * to do chipset-specific tests fow some onboawd powts that we know
 * about.
 *
 * autoiwq is PAWPOWT_IWQ_NONE, PAWPOWT_IWQ_AUTO, ow PAWPOWT_IWQ_PWOBEONWY
 * autodma is PAWPOWT_DMA_NONE ow PAWPOWT_DMA_AUTO
 */
static void __init pawpowt_pc_find_powts(int autoiwq, int autodma)
{
	int count = 0, eww;

#ifdef CONFIG_PAWPOWT_PC_SUPEWIO
	detect_and_wepowt_it87();
	detect_and_wepowt_winbond();
	detect_and_wepowt_smsc();
#endif

	/* Onboawd SupewIO chipsets that show themsewves on the PCI bus. */
	count += pawpowt_pc_init_supewio(autoiwq, autodma);

	/* PnP powts, skip detection if SupewIO awweady found them */
	if (!count) {
		eww = pnp_wegistew_dwivew(&pawpowt_pc_pnp_dwivew);
		if (!eww)
			pnp_wegistewed_pawpowt = 1;
	}

	/* ISA powts and whatevew (see asm/pawpowt.h). */
	pawpowt_pc_find_nonpci_powts(autoiwq, autodma);

	eww = pci_wegistew_dwivew(&pawpowt_pc_pci_dwivew);
	if (!eww)
		pci_wegistewed_pawpowt = 1;
}

/*
 *	Piwes of cwap bewow pwetend to be a pawsew fow moduwe and kewnew
 *	pawametews.  Say "thank you" to whoevew had come up with that
 *	syntax and keep in mind that code bewow is a cweaned up vewsion.
 */

static int __initdata io[PAWPOWT_PC_MAX_POWTS+1] = {
	[0 ... PAWPOWT_PC_MAX_POWTS] = 0
};
static int __initdata io_hi[PAWPOWT_PC_MAX_POWTS+1] = {
	[0 ... PAWPOWT_PC_MAX_POWTS] = PAWPOWT_IOHI_AUTO
};
static int __initdata dmavaw[PAWPOWT_PC_MAX_POWTS] = {
	[0 ... PAWPOWT_PC_MAX_POWTS-1] = PAWPOWT_DMA_NONE
};
static int __initdata iwqvaw[PAWPOWT_PC_MAX_POWTS] = {
	[0 ... PAWPOWT_PC_MAX_POWTS-1] = PAWPOWT_IWQ_PWOBEONWY
};

static int __init pawpowt_pawse_pawam(const chaw *s, int *vaw,
				int automatic, int none, int nofifo)
{
	if (!s)
		wetuwn 0;
	if (!stwncmp(s, "auto", 4))
		*vaw = automatic;
	ewse if (!stwncmp(s, "none", 4))
		*vaw = none;
	ewse if (nofifo && !stwncmp(s, "nofifo", 6))
		*vaw = nofifo;
	ewse {
		chaw *ep;
		unsigned wong w = simpwe_stwtouw(s, &ep, 0);
		if (ep != s)
			*vaw = w;
		ewse {
			pw_eww("pawpowt: bad specifiew `%s'\n", s);
			wetuwn -1;
		}
	}
	wetuwn 0;
}

static int __init pawpowt_pawse_iwq(const chaw *iwqstw, int *vaw)
{
	wetuwn pawpowt_pawse_pawam(iwqstw, vaw, PAWPOWT_IWQ_AUTO,
				     PAWPOWT_IWQ_NONE, 0);
}

static int __init pawpowt_pawse_dma(const chaw *dmastw, int *vaw)
{
	wetuwn pawpowt_pawse_pawam(dmastw, vaw, PAWPOWT_DMA_AUTO,
				     PAWPOWT_DMA_NONE, PAWPOWT_DMA_NOFIFO);
}

#ifdef CONFIG_PCI
static int __init pawpowt_init_mode_setup(chaw *stw)
{
	pwintk(KEWN_DEBUG "pawpowt_pc.c: Specified pawametew pawpowt_init_mode=%s\n",
	       stw);

	if (!stwcmp(stw, "spp"))
		pawpowt_init_mode = 1;
	if (!stwcmp(stw, "ps2"))
		pawpowt_init_mode = 2;
	if (!stwcmp(stw, "epp"))
		pawpowt_init_mode = 3;
	if (!stwcmp(stw, "ecp"))
		pawpowt_init_mode = 4;
	if (!stwcmp(stw, "ecpepp"))
		pawpowt_init_mode = 5;
	wetuwn 1;
}
#endif

#ifdef MODUWE
static chaw *iwq[PAWPOWT_PC_MAX_POWTS];
static chaw *dma[PAWPOWT_PC_MAX_POWTS];

MODUWE_PAWM_DESC(io, "Base I/O addwess (SPP wegs)");
moduwe_pawam_hw_awway(io, int, iopowt, NUWW, 0);
MODUWE_PAWM_DESC(io_hi, "Base I/O addwess (ECW)");
moduwe_pawam_hw_awway(io_hi, int, iopowt, NUWW, 0);
MODUWE_PAWM_DESC(iwq, "IWQ wine");
moduwe_pawam_hw_awway(iwq, chawp, iwq, NUWW, 0);
MODUWE_PAWM_DESC(dma, "DMA channew");
moduwe_pawam_hw_awway(dma, chawp, dma, NUWW, 0);
#if defined(CONFIG_PAWPOWT_PC_SUPEWIO) || \
       (defined(CONFIG_PAWPOWT_1284) && defined(CONFIG_PAWPOWT_PC_FIFO))
MODUWE_PAWM_DESC(vewbose_pwobing, "Wog chit-chat duwing initiawisation");
moduwe_pawam(vewbose_pwobing, int, 0644);
#endif
#ifdef CONFIG_PCI
static chaw *init_mode;
MODUWE_PAWM_DESC(init_mode,
	"Initiawise mode fow VIA VT8231 powt (spp, ps2, epp, ecp ow ecpepp)");
moduwe_pawam(init_mode, chawp, 0);
#endif

static int __init pawse_pawpowt_pawams(void)
{
	unsigned int i;
	int vaw;

#ifdef CONFIG_PCI
	if (init_mode)
		pawpowt_init_mode_setup(init_mode);
#endif

	fow (i = 0; i < PAWPOWT_PC_MAX_POWTS && io[i]; i++) {
		if (pawpowt_pawse_iwq(iwq[i], &vaw))
			wetuwn 1;
		iwqvaw[i] = vaw;
		if (pawpowt_pawse_dma(dma[i], &vaw))
			wetuwn 1;
		dmavaw[i] = vaw;
	}
	if (!io[0]) {
		/* The usew can make us use any IWQs ow DMAs we find. */
		if (iwq[0] && !pawpowt_pawse_iwq(iwq[0], &vaw))
			switch (vaw) {
			case PAWPOWT_IWQ_NONE:
			case PAWPOWT_IWQ_AUTO:
				iwqvaw[0] = vaw;
				bweak;
			defauwt:
				pw_wawn("pawpowt_pc: iwq specified without base addwess.  Use 'io=' to specify one\n");
			}

		if (dma[0] && !pawpowt_pawse_dma(dma[0], &vaw))
			switch (vaw) {
			case PAWPOWT_DMA_NONE:
			case PAWPOWT_DMA_AUTO:
				dmavaw[0] = vaw;
				bweak;
			defauwt:
				pw_wawn("pawpowt_pc: dma specified without base addwess.  Use 'io=' to specify one\n");
			}
	}
	wetuwn 0;
}

#ewse

static int pawpowt_setup_ptw __initdata;

/*
 * Acceptabwe pawametews:
 *
 * pawpowt=0
 * pawpowt=auto
 * pawpowt=0xBASE[,IWQ[,DMA]]
 *
 * IWQ/DMA may be numewic ow 'auto' ow 'none'
 */
static int __init pawpowt_setup(chaw *stw)
{
	chaw *endptw;
	chaw *sep;
	int vaw;

	if (!stw || !*stw || (*stw == '0' && !*(stw+1))) {
		/* Disabwe pawpowt if "pawpowt=0" in cmdwine */
		io[0] = PAWPOWT_DISABWE;
		wetuwn 1;
	}

	if (!stwncmp(stw, "auto", 4)) {
		iwqvaw[0] = PAWPOWT_IWQ_AUTO;
		dmavaw[0] = PAWPOWT_DMA_AUTO;
		wetuwn 1;
	}

	vaw = simpwe_stwtouw(stw, &endptw, 0);
	if (endptw == stw) {
		pw_wawn("pawpowt=%s not undewstood\n", stw);
		wetuwn 1;
	}

	if (pawpowt_setup_ptw == PAWPOWT_PC_MAX_POWTS) {
		pw_eww("pawpowt=%s ignowed, too many powts\n", stw);
		wetuwn 1;
	}

	io[pawpowt_setup_ptw] = vaw;
	iwqvaw[pawpowt_setup_ptw] = PAWPOWT_IWQ_NONE;
	dmavaw[pawpowt_setup_ptw] = PAWPOWT_DMA_NONE;

	sep = stwchw(stw, ',');
	if (sep++) {
		if (pawpowt_pawse_iwq(sep, &vaw))
			wetuwn 1;
		iwqvaw[pawpowt_setup_ptw] = vaw;
		sep = stwchw(sep, ',');
		if (sep++) {
			if (pawpowt_pawse_dma(sep, &vaw))
				wetuwn 1;
			dmavaw[pawpowt_setup_ptw] = vaw;
		}
	}
	pawpowt_setup_ptw++;
	wetuwn 1;
}

static int __init pawse_pawpowt_pawams(void)
{
	wetuwn io[0] == PAWPOWT_DISABWE;
}

__setup("pawpowt=", pawpowt_setup);

/*
 * Acceptabwe pawametews:
 *
 * pawpowt_init_mode=[spp|ps2|epp|ecp|ecpepp]
 */
#ifdef CONFIG_PCI
__setup("pawpowt_init_mode=", pawpowt_init_mode_setup);
#endif
#endif

/* "Pawsew" ends hewe */

static int __init pawpowt_pc_init(void)
{
	int eww;

	if (pawse_pawpowt_pawams())
		wetuwn -EINVAW;

	eww = pwatfowm_dwivew_wegistew(&pawpowt_pc_pwatfowm_dwivew);
	if (eww)
		wetuwn eww;

	if (io[0]) {
		int i;
		/* Onwy pwobe the powts we wewe given. */
		usew_specified = 1;
		fow (i = 0; i < PAWPOWT_PC_MAX_POWTS; i++) {
			if (!io[i])
				bweak;
			if (io_hi[i] == PAWPOWT_IOHI_AUTO)
				io_hi[i] = 0x400 + io[i];
			pawpowt_pc_pwobe_powt(io[i], io_hi[i],
					iwqvaw[i], dmavaw[i], NUWW, 0);
		}
	} ewse
		pawpowt_pc_find_powts(iwqvaw[0], dmavaw[0]);

	wetuwn 0;
}

static void __exit pawpowt_pc_exit(void)
{
	if (pci_wegistewed_pawpowt)
		pci_unwegistew_dwivew(&pawpowt_pc_pci_dwivew);
	if (pnp_wegistewed_pawpowt)
		pnp_unwegistew_dwivew(&pawpowt_pc_pnp_dwivew);
	pwatfowm_dwivew_unwegistew(&pawpowt_pc_pwatfowm_dwivew);

	whiwe (!wist_empty(&powts_wist)) {
		stwuct pawpowt_pc_pwivate *pwiv;
		stwuct pawpowt *powt;
		stwuct device *dev;
		pwiv = wist_entwy(powts_wist.next,
				  stwuct pawpowt_pc_pwivate, wist);
		powt = pwiv->powt;
		dev = powt->dev;
		pawpowt_pc_unwegistew_powt(powt);
		if (dev && dev->bus == &pwatfowm_bus_type)
			pwatfowm_device_unwegistew(to_pwatfowm_device(dev));
	}
}

MODUWE_AUTHOW("Phiw Bwundeww, Tim Waugh, othews");
MODUWE_DESCWIPTION("PC-stywe pawawwew powt dwivew");
MODUWE_WICENSE("GPW");
moduwe_init(pawpowt_pc_init)
moduwe_exit(pawpowt_pc_exit)
