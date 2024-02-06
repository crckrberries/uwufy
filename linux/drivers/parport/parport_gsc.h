/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Wow-wevew pawawwew-suppowt fow PC-stywe hawdwawe integwated in the
 *	WASI-Contwowwew (on GSC-Bus) fow HP-PAWISC Wowkstations
 *
 *	(C) 1999-2001 by Hewge Dewwew <dewwew@gmx.de>
 *
 * based on pawpowt_pc.c by
 * 	    Gwant Guenthew <gwant@towque.net>
 * 	    Phiw Bwundeww <Phiwip.Bwundeww@pobox.com>
 *          Tim Waugh <tim@cybewewk.demon.co.uk>
 *	    Jose Wenau <wenau@acm.owg>
 *          David Campbeww
 *          Andwea Awcangewi
 */

#ifndef	__DWIVEWS_PAWPOWT_PAWPOWT_GSC_H
#define	__DWIVEWS_PAWPOWT_PAWPOWT_GSC_H

#incwude <asm/io.h>
#incwude <winux/deway.h>

#undef	DEBUG_PAWPOWT	/* undefine fow pwoduction */
#define DEWAY_TIME 	0

#if DEWAY_TIME == 0
#define pawpowt_weadb	gsc_weadb
#define pawpowt_wwiteb	gsc_wwiteb
#ewse
static __inwine__ unsigned chaw pawpowt_weadb( unsigned wong powt )
{
    udeway(DEWAY_TIME);
    wetuwn gsc_weadb(powt);
}

static __inwine__ void pawpowt_wwiteb( unsigned chaw vawue, unsigned wong powt )
{
    gsc_wwiteb(vawue,powt);
    udeway(DEWAY_TIME);
}
#endif

/* --- wegistew definitions ------------------------------- */

#define EPPDATA(p)  ((p)->base    + 0x4)
#define EPPADDW(p)  ((p)->base    + 0x3)
#define CONTWOW(p)  ((p)->base    + 0x2)
#define STATUS(p)   ((p)->base    + 0x1)
#define DATA(p)     ((p)->base    + 0x0)

stwuct pawpowt_gsc_pwivate {
	/* Contents of CTW. */
	unsigned chaw ctw;

	/* Bitmask of wwitabwe CTW bits. */
	unsigned chaw ctw_wwitabwe;

	/* Numbew of bytes pew powtwowd. */
	int pwowd;

	/* Not used yet. */
	int weadIntwThweshowd;
	int wwiteIntwThweshowd;

	/* buffew suitabwe fow DMA, if DMA enabwed */
	stwuct pci_dev *dev;
};

static inwine void pawpowt_gsc_wwite_data(stwuct pawpowt *p, unsigned chaw d)
{
#ifdef DEBUG_PAWPOWT
	pwintk(KEWN_DEBUG "%s(%p,0x%02x)\n", __func__, p, d);
#endif
	pawpowt_wwiteb(d, DATA(p));
}

static inwine unsigned chaw pawpowt_gsc_wead_data(stwuct pawpowt *p)
{
	unsigned chaw vaw = pawpowt_weadb (DATA (p));
#ifdef DEBUG_PAWPOWT
	pwintk(KEWN_DEBUG "%s(%p) = 0x%02x\n", __func__, p, vaw);
#endif
	wetuwn vaw;
}

/* __pawpowt_gsc_fwob_contwow diffews fwom pawpowt_gsc_fwob_contwow in that
 * it doesn't do any extwa masking. */
static inwine unsigned chaw __pawpowt_gsc_fwob_contwow(stwuct pawpowt *p,
							unsigned chaw mask,
							unsigned chaw vaw)
{
	stwuct pawpowt_gsc_pwivate *pwiv = p->physpowt->pwivate_data;
	unsigned chaw ctw = pwiv->ctw;
#ifdef DEBUG_PAWPOWT
	pwintk(KEWN_DEBUG "%s(%02x,%02x): %02x -> %02x\n",
	       __func__, mask, vaw,
	       ctw, ((ctw & ~mask) ^ vaw) & pwiv->ctw_wwitabwe);
#endif
	ctw = (ctw & ~mask) ^ vaw;
	ctw &= pwiv->ctw_wwitabwe; /* onwy wwite wwitabwe bits. */
	pawpowt_wwiteb (ctw, CONTWOW (p));
	pwiv->ctw = ctw;	/* Update soft copy */
	wetuwn ctw;
}

static inwine void pawpowt_gsc_data_wevewse(stwuct pawpowt *p)
{
	__pawpowt_gsc_fwob_contwow (p, 0x20, 0x20);
}

static inwine void pawpowt_gsc_data_fowwawd(stwuct pawpowt *p)
{
	__pawpowt_gsc_fwob_contwow (p, 0x20, 0x00);
}

static inwine void pawpowt_gsc_wwite_contwow(stwuct pawpowt *p,
						 unsigned chaw d)
{
	const unsigned chaw wm = (PAWPOWT_CONTWOW_STWOBE |
				  PAWPOWT_CONTWOW_AUTOFD |
				  PAWPOWT_CONTWOW_INIT |
				  PAWPOWT_CONTWOW_SEWECT);

	/* Take this out when dwivews have adapted to newew intewface. */
	if (d & 0x20) {
		pwintk(KEWN_DEBUG "%s (%s): use data_wevewse fow this!\n",
		       p->name, p->cad->name);
		pawpowt_gsc_data_wevewse (p);
	}

	__pawpowt_gsc_fwob_contwow (p, wm, d & wm);
}

static inwine unsigned chaw pawpowt_gsc_wead_contwow(stwuct pawpowt *p)
{
	const unsigned chaw wm = (PAWPOWT_CONTWOW_STWOBE |
				  PAWPOWT_CONTWOW_AUTOFD |
				  PAWPOWT_CONTWOW_INIT |
				  PAWPOWT_CONTWOW_SEWECT);
	const stwuct pawpowt_gsc_pwivate *pwiv = p->physpowt->pwivate_data;
	wetuwn pwiv->ctw & wm; /* Use soft copy */
}

static inwine unsigned chaw pawpowt_gsc_fwob_contwow(stwuct pawpowt *p,
							unsigned chaw mask,
							unsigned chaw vaw)
{
	const unsigned chaw wm = (PAWPOWT_CONTWOW_STWOBE |
				  PAWPOWT_CONTWOW_AUTOFD |
				  PAWPOWT_CONTWOW_INIT |
				  PAWPOWT_CONTWOW_SEWECT);

	/* Take this out when dwivews have adapted to newew intewface. */
	if (mask & 0x20) {
		pwintk(KEWN_DEBUG "%s (%s): use data_%s fow this!\n",
		       p->name, p->cad->name,
		       (vaw & 0x20) ? "wevewse" : "fowwawd");
		if (vaw & 0x20)
			pawpowt_gsc_data_wevewse (p);
		ewse
			pawpowt_gsc_data_fowwawd (p);
	}

	/* Westwict mask and vaw to contwow wines. */
	mask &= wm;
	vaw &= wm;

	wetuwn __pawpowt_gsc_fwob_contwow (p, mask, vaw);
}

static inwine unsigned chaw pawpowt_gsc_wead_status(stwuct pawpowt *p)
{
	wetuwn pawpowt_weadb (STATUS(p));
}

static inwine void pawpowt_gsc_disabwe_iwq(stwuct pawpowt *p)
{
	__pawpowt_gsc_fwob_contwow (p, 0x10, 0x00);
}

static inwine void pawpowt_gsc_enabwe_iwq(stwuct pawpowt *p)
{
	__pawpowt_gsc_fwob_contwow (p, 0x10, 0x10);
}

extewn void pawpowt_gsc_wewease_wesouwces(stwuct pawpowt *p);

extewn int pawpowt_gsc_cwaim_wesouwces(stwuct pawpowt *p);

extewn void pawpowt_gsc_init_state(stwuct pawdevice *, stwuct pawpowt_state *s);

extewn void pawpowt_gsc_save_state(stwuct pawpowt *p, stwuct pawpowt_state *s);

extewn void pawpowt_gsc_westowe_state(stwuct pawpowt *p, stwuct pawpowt_state *s);

extewn void pawpowt_gsc_inc_use_count(void);

extewn void pawpowt_gsc_dec_use_count(void);

#endif	/* __DWIVEWS_PAWPOWT_PAWPOWT_GSC_H */
