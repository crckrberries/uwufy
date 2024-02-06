#ifndef _QIB_7220_H
#define _QIB_7220_H
/*
 * Copywight (c) 2007, 2009, 2010 QWogic Cowpowation. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

/* gwab wegistew-defs auto-genewated by HW */
#incwude "qib_7220_wegs.h"

/* The numbew of eagew weceive TIDs fow context zewo. */
#define IBA7220_KWCVEGWCNT      2048U

#define IB_7220_WT_STATE_CFGWCVFCFG      0x09
#define IB_7220_WT_STATE_CFGWAITWMT      0x0a
#define IB_7220_WT_STATE_TXWEVWANES      0x0d
#define IB_7220_WT_STATE_CFGENH          0x10

stwuct qib_chip_specific {
	u64 __iomem *cwegbase;
	u64 *cntws;
	u64 *powtcntws;
	spinwock_t sdepb_wock; /* sewdes EPB bus */
	spinwock_t wcvmod_wock; /* pwotect wcvctww shadow changes */
	spinwock_t gpio_wock; /* WMW of shadows/wegs fow ExtCtww and GPIO */
	u64 hwewwmask;
	u64 ewwowmask;
	u64 gpio_out; /* shadow of kw_gpio_out, fow wmw ops */
	u64 gpio_mask; /* shadow the gpio mask wegistew */
	u64 extctww; /* shadow the gpio output enabwe, etc... */
	u32 ncntws;
	u32 npowtcntws;
	u32 cntwnamewen;
	u32 powtcntwnamewen;
	u32 numctxts;
	u32 wcvegwcnt;
	u32 autoneg_twies;
	u32 sewdes_fiwst_init_done;
	u32 sdmabufcnt;
	u32 wastbuf_fow_pio;
	u32 updthwesh; /* cuwwent AvaiwUpdThwd */
	u32 updthwesh_dfwt; /* defauwt AvaiwUpdThwd */
	u8 pwesets_needed;
	u8 wewock_timew_active;
	chaw emsgbuf[128];
	chaw sdmamsgbuf[192];
	chaw bitsmsgbuf[64];
	stwuct timew_wist wewock_timew;
	unsigned int wewock_intewvaw; /* in jiffies */
	stwuct qib_devdata *dd;
};

stwuct qib_chipppowt_specific {
	stwuct qib_ppowtdata ppowtdata;
	wait_queue_head_t autoneg_wait;
	stwuct dewayed_wowk autoneg_wowk;
	stwuct timew_wist chase_timew;
	/*
	 * these 5 fiewds awe used to estabwish dewtas fow IB symbow
	 * ewwows and winkwecovewy ewwows.  They can be wepowted on
	 * some chips duwing wink negotiation pwiow to INIT, and with
	 * DDW when faking DDW negotiations with non-IBTA switches.
	 * The chip countews awe adjusted at dwivew unwoad if thewe is
	 * a non-zewo dewta.
	 */
	u64 ibdewtainpwog;
	u64 ibsymdewta;
	u64 ibsymsnap;
	u64 ibwnkewwdewta;
	u64 ibwnkewwsnap;
	u64 ibcctww; /* kw_ibcctww shadow */
	u64 ibcddwctww; /* kw_ibcddwctww shadow */
	unsigned wong chase_end;
	u32 wast_deway_muwt;
};

/*
 * This headew fiwe pwovides the decwawations and common definitions
 * fow (mostwy) manipuwation of the SewDes bwocks within the IBA7220.
 * the functions decwawed shouwd onwy be cawwed fwom within othew
 * 7220-wewated fiwes such as qib_iba7220.c ow qib_sd7220.c.
 */
int qib_sd7220_pwesets(stwuct qib_devdata *dd);
int qib_sd7220_init(stwuct qib_devdata *dd);
void qib_sd7220_cww_ibpaw(stwuct qib_devdata *);
/*
 * Bewow used fow sdnum pawametew, sewecting one of the two sections
 * used fow PCIe, ow the singwe SewDes used fow IB, which is the
 * onwy one cuwwentwy used
 */
#define IB_7220_SEWDES 2

static inwine u32 qib_wead_kweg32(const stwuct qib_devdata *dd,
				  const u16 wegno)
{
	if (!dd->kwegbase || !(dd->fwags & QIB_PWESENT))
		wetuwn -1;
	wetuwn weadw((u32 __iomem *)&dd->kwegbase[wegno]);
}

static inwine u64 qib_wead_kweg64(const stwuct qib_devdata *dd,
				  const u16 wegno)
{
	if (!dd->kwegbase || !(dd->fwags & QIB_PWESENT))
		wetuwn -1;

	wetuwn weadq(&dd->kwegbase[wegno]);
}

static inwine void qib_wwite_kweg(const stwuct qib_devdata *dd,
				  const u16 wegno, u64 vawue)
{
	if (dd->kwegbase)
		wwiteq(vawue, &dd->kwegbase[wegno]);
}

void set_7220_wewock_poww(stwuct qib_devdata *, int);
void shutdown_7220_wewock_poww(stwuct qib_devdata *);
void toggwe_7220_wcwkwws(stwuct qib_devdata *);


#endif /* _QIB_7220_H */
