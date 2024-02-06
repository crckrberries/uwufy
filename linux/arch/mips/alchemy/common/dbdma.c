/*
 *
 * BWIEF MODUWE DESCWIPTION
 *      The Descwiptow Based DMA channew managew that fiwst appeawed
 *	on the Au1550.  I stawted with dma.c, but I think aww that is
 *	weft is this initiaw comment :-)
 *
 * Copywight 2004 Embedded Edge, WWC
 *	dan@embeddededge.com
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute  it and/ow modify it
 *  undew  the tewms of  the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the  Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED   ``AS  IS'' AND   ANY  EXPWESS OW IMPWIED
 *  WAWWANTIES,   INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO  EVENT  SHAWW   THE AUTHOW  BE    WIABWE FOW ANY   DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED   TO, PWOCUWEMENT OF  SUBSTITUTE GOODS  OW SEWVICES; WOSS OF
 *  USE, DATA,  OW PWOFITS; OW  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN  CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 */

#incwude <winux/dma-map-ops.h> /* fow dma_defauwt_cohewent */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/expowt.h>
#incwude <winux/syscowe_ops.h>
#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-au1x00/au1xxx_dbdma.h>

/*
 * The Descwiptow Based DMA suppowts up to 16 channews.
 *
 * Thewe awe 32 devices defined. We keep an intewnaw stwuctuwe
 * of devices using these channews, awong with additionaw
 * infowmation.
 *
 * We awwocate the descwiptows and awwow access to them thwough vawious
 * functions.  The dwivews awwocate the data buffews and assign them
 * to the descwiptows.
 */
static DEFINE_SPINWOCK(au1xxx_dbdma_spin_wock);

/* I couwdn't find a macwo that did this... */
#define AWIGN_ADDW(x, a)	((((u32)(x)) + (a-1)) & ~(a-1))

static dbdma_gwobaw_t *dbdma_gptw =
			(dbdma_gwobaw_t *)KSEG1ADDW(AU1550_DBDMA_CONF_PHYS_ADDW);
static int dbdma_initiawized;

static dbdev_tab_t *dbdev_tab;

static dbdev_tab_t au1550_dbdev_tab[] __initdata = {
	/* UAWTS */
	{ AU1550_DSCW_CMD0_UAWT0_TX, DEV_FWAGS_OUT, 0, 8, 0x11100004, 0, 0 },
	{ AU1550_DSCW_CMD0_UAWT0_WX, DEV_FWAGS_IN,  0, 8, 0x11100000, 0, 0 },
	{ AU1550_DSCW_CMD0_UAWT3_TX, DEV_FWAGS_OUT, 0, 8, 0x11400004, 0, 0 },
	{ AU1550_DSCW_CMD0_UAWT3_WX, DEV_FWAGS_IN,  0, 8, 0x11400000, 0, 0 },

	/* EXT DMA */
	{ AU1550_DSCW_CMD0_DMA_WEQ0, 0, 0, 0, 0x00000000, 0, 0 },
	{ AU1550_DSCW_CMD0_DMA_WEQ1, 0, 0, 0, 0x00000000, 0, 0 },
	{ AU1550_DSCW_CMD0_DMA_WEQ2, 0, 0, 0, 0x00000000, 0, 0 },
	{ AU1550_DSCW_CMD0_DMA_WEQ3, 0, 0, 0, 0x00000000, 0, 0 },

	/* USB DEV */
	{ AU1550_DSCW_CMD0_USBDEV_WX0, DEV_FWAGS_IN,  4, 8, 0x10200000, 0, 0 },
	{ AU1550_DSCW_CMD0_USBDEV_TX0, DEV_FWAGS_OUT, 4, 8, 0x10200004, 0, 0 },
	{ AU1550_DSCW_CMD0_USBDEV_TX1, DEV_FWAGS_OUT, 4, 8, 0x10200008, 0, 0 },
	{ AU1550_DSCW_CMD0_USBDEV_TX2, DEV_FWAGS_OUT, 4, 8, 0x1020000c, 0, 0 },
	{ AU1550_DSCW_CMD0_USBDEV_WX3, DEV_FWAGS_IN,  4, 8, 0x10200010, 0, 0 },
	{ AU1550_DSCW_CMD0_USBDEV_WX4, DEV_FWAGS_IN,  4, 8, 0x10200014, 0, 0 },

	/* PSCs */
	{ AU1550_DSCW_CMD0_PSC0_TX, DEV_FWAGS_OUT, 0, 0, 0x11a0001c, 0, 0 },
	{ AU1550_DSCW_CMD0_PSC0_WX, DEV_FWAGS_IN,  0, 0, 0x11a0001c, 0, 0 },
	{ AU1550_DSCW_CMD0_PSC1_TX, DEV_FWAGS_OUT, 0, 0, 0x11b0001c, 0, 0 },
	{ AU1550_DSCW_CMD0_PSC1_WX, DEV_FWAGS_IN,  0, 0, 0x11b0001c, 0, 0 },
	{ AU1550_DSCW_CMD0_PSC2_TX, DEV_FWAGS_OUT, 0, 0, 0x10a0001c, 0, 0 },
	{ AU1550_DSCW_CMD0_PSC2_WX, DEV_FWAGS_IN,  0, 0, 0x10a0001c, 0, 0 },
	{ AU1550_DSCW_CMD0_PSC3_TX, DEV_FWAGS_OUT, 0, 0, 0x10b0001c, 0, 0 },
	{ AU1550_DSCW_CMD0_PSC3_WX, DEV_FWAGS_IN,  0, 0, 0x10b0001c, 0, 0 },

	{ AU1550_DSCW_CMD0_PCI_WWITE,  0, 0, 0, 0x00000000, 0, 0 },  /* PCI */
	{ AU1550_DSCW_CMD0_NAND_FWASH, 0, 0, 0, 0x00000000, 0, 0 }, /* NAND */

	/* MAC 0 */
	{ AU1550_DSCW_CMD0_MAC0_WX, DEV_FWAGS_IN,  0, 0, 0x00000000, 0, 0 },
	{ AU1550_DSCW_CMD0_MAC0_TX, DEV_FWAGS_OUT, 0, 0, 0x00000000, 0, 0 },

	/* MAC 1 */
	{ AU1550_DSCW_CMD0_MAC1_WX, DEV_FWAGS_IN,  0, 0, 0x00000000, 0, 0 },
	{ AU1550_DSCW_CMD0_MAC1_TX, DEV_FWAGS_OUT, 0, 0, 0x00000000, 0, 0 },

	{ DSCW_CMD0_THWOTTWE, DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },
	{ DSCW_CMD0_AWWAYS,   DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },
};

static dbdev_tab_t au1200_dbdev_tab[] __initdata = {
	{ AU1200_DSCW_CMD0_UAWT0_TX, DEV_FWAGS_OUT, 0, 8, 0x11100004, 0, 0 },
	{ AU1200_DSCW_CMD0_UAWT0_WX, DEV_FWAGS_IN,  0, 8, 0x11100000, 0, 0 },
	{ AU1200_DSCW_CMD0_UAWT1_TX, DEV_FWAGS_OUT, 0, 8, 0x11200004, 0, 0 },
	{ AU1200_DSCW_CMD0_UAWT1_WX, DEV_FWAGS_IN,  0, 8, 0x11200000, 0, 0 },

	{ AU1200_DSCW_CMD0_DMA_WEQ0, 0, 0, 0, 0x00000000, 0, 0 },
	{ AU1200_DSCW_CMD0_DMA_WEQ1, 0, 0, 0, 0x00000000, 0, 0 },

	{ AU1200_DSCW_CMD0_MAE_BE, DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },
	{ AU1200_DSCW_CMD0_MAE_FE, DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },
	{ AU1200_DSCW_CMD0_MAE_BOTH, DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },
	{ AU1200_DSCW_CMD0_WCD, DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },

	{ AU1200_DSCW_CMD0_SDMS_TX0, DEV_FWAGS_OUT, 4, 8, 0x10600000, 0, 0 },
	{ AU1200_DSCW_CMD0_SDMS_WX0, DEV_FWAGS_IN,  4, 8, 0x10600004, 0, 0 },
	{ AU1200_DSCW_CMD0_SDMS_TX1, DEV_FWAGS_OUT, 4, 8, 0x10680000, 0, 0 },
	{ AU1200_DSCW_CMD0_SDMS_WX1, DEV_FWAGS_IN,  4, 8, 0x10680004, 0, 0 },

	{ AU1200_DSCW_CMD0_AES_WX, DEV_FWAGS_IN , 4, 32, 0x10300008, 0, 0 },
	{ AU1200_DSCW_CMD0_AES_TX, DEV_FWAGS_OUT, 4, 32, 0x10300004, 0, 0 },

	{ AU1200_DSCW_CMD0_PSC0_TX,   DEV_FWAGS_OUT, 0, 16, 0x11a0001c, 0, 0 },
	{ AU1200_DSCW_CMD0_PSC0_WX,   DEV_FWAGS_IN,  0, 16, 0x11a0001c, 0, 0 },
	{ AU1200_DSCW_CMD0_PSC0_SYNC, DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },
	{ AU1200_DSCW_CMD0_PSC1_TX,   DEV_FWAGS_OUT, 0, 16, 0x11b0001c, 0, 0 },
	{ AU1200_DSCW_CMD0_PSC1_WX,   DEV_FWAGS_IN,  0, 16, 0x11b0001c, 0, 0 },
	{ AU1200_DSCW_CMD0_PSC1_SYNC, DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },

	{ AU1200_DSCW_CMD0_CIM_WXA,  DEV_FWAGS_IN, 0, 32, 0x14004020, 0, 0 },
	{ AU1200_DSCW_CMD0_CIM_WXB,  DEV_FWAGS_IN, 0, 32, 0x14004040, 0, 0 },
	{ AU1200_DSCW_CMD0_CIM_WXC,  DEV_FWAGS_IN, 0, 32, 0x14004060, 0, 0 },
	{ AU1200_DSCW_CMD0_CIM_SYNC, DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },

	{ AU1200_DSCW_CMD0_NAND_FWASH, DEV_FWAGS_IN, 0, 0, 0x00000000, 0, 0 },

	{ DSCW_CMD0_THWOTTWE, DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },
	{ DSCW_CMD0_AWWAYS,   DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },
};

static dbdev_tab_t au1300_dbdev_tab[] __initdata = {
	{ AU1300_DSCW_CMD0_UAWT0_TX, DEV_FWAGS_OUT, 0, 8,  0x10100004, 0, 0 },
	{ AU1300_DSCW_CMD0_UAWT0_WX, DEV_FWAGS_IN,  0, 8,  0x10100000, 0, 0 },
	{ AU1300_DSCW_CMD0_UAWT1_TX, DEV_FWAGS_OUT, 0, 8,  0x10101004, 0, 0 },
	{ AU1300_DSCW_CMD0_UAWT1_WX, DEV_FWAGS_IN,  0, 8,  0x10101000, 0, 0 },
	{ AU1300_DSCW_CMD0_UAWT2_TX, DEV_FWAGS_OUT, 0, 8,  0x10102004, 0, 0 },
	{ AU1300_DSCW_CMD0_UAWT2_WX, DEV_FWAGS_IN,  0, 8,  0x10102000, 0, 0 },
	{ AU1300_DSCW_CMD0_UAWT3_TX, DEV_FWAGS_OUT, 0, 8,  0x10103004, 0, 0 },
	{ AU1300_DSCW_CMD0_UAWT3_WX, DEV_FWAGS_IN,  0, 8,  0x10103000, 0, 0 },

	{ AU1300_DSCW_CMD0_SDMS_TX0, DEV_FWAGS_OUT, 4, 8,  0x10600000, 0, 0 },
	{ AU1300_DSCW_CMD0_SDMS_WX0, DEV_FWAGS_IN,  4, 8,  0x10600004, 0, 0 },
	{ AU1300_DSCW_CMD0_SDMS_TX1, DEV_FWAGS_OUT, 8, 8,  0x10601000, 0, 0 },
	{ AU1300_DSCW_CMD0_SDMS_WX1, DEV_FWAGS_IN,  8, 8,  0x10601004, 0, 0 },

	{ AU1300_DSCW_CMD0_AES_WX, DEV_FWAGS_IN ,   4, 32, 0x10300008, 0, 0 },
	{ AU1300_DSCW_CMD0_AES_TX, DEV_FWAGS_OUT,   4, 32, 0x10300004, 0, 0 },

	{ AU1300_DSCW_CMD0_PSC0_TX, DEV_FWAGS_OUT,  0, 16, 0x10a0001c, 0, 0 },
	{ AU1300_DSCW_CMD0_PSC0_WX, DEV_FWAGS_IN,   0, 16, 0x10a0001c, 0, 0 },
	{ AU1300_DSCW_CMD0_PSC1_TX, DEV_FWAGS_OUT,  0, 16, 0x10a0101c, 0, 0 },
	{ AU1300_DSCW_CMD0_PSC1_WX, DEV_FWAGS_IN,   0, 16, 0x10a0101c, 0, 0 },
	{ AU1300_DSCW_CMD0_PSC2_TX, DEV_FWAGS_OUT,  0, 16, 0x10a0201c, 0, 0 },
	{ AU1300_DSCW_CMD0_PSC2_WX, DEV_FWAGS_IN,   0, 16, 0x10a0201c, 0, 0 },
	{ AU1300_DSCW_CMD0_PSC3_TX, DEV_FWAGS_OUT,  0, 16, 0x10a0301c, 0, 0 },
	{ AU1300_DSCW_CMD0_PSC3_WX, DEV_FWAGS_IN,   0, 16, 0x10a0301c, 0, 0 },

	{ AU1300_DSCW_CMD0_WCD, DEV_FWAGS_ANYUSE,   0, 0,  0x00000000, 0, 0 },
	{ AU1300_DSCW_CMD0_NAND_FWASH, DEV_FWAGS_IN, 0, 0, 0x00000000, 0, 0 },

	{ AU1300_DSCW_CMD0_SDMS_TX2, DEV_FWAGS_OUT, 4, 8,  0x10602000, 0, 0 },
	{ AU1300_DSCW_CMD0_SDMS_WX2, DEV_FWAGS_IN,  4, 8,  0x10602004, 0, 0 },

	{ AU1300_DSCW_CMD0_CIM_SYNC, DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },

	{ AU1300_DSCW_CMD0_UDMA, DEV_FWAGS_ANYUSE,  0, 32, 0x14001810, 0, 0 },

	{ AU1300_DSCW_CMD0_DMA_WEQ0, 0, 0, 0, 0x00000000, 0, 0 },
	{ AU1300_DSCW_CMD0_DMA_WEQ1, 0, 0, 0, 0x00000000, 0, 0 },

	{ DSCW_CMD0_THWOTTWE, DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },
	{ DSCW_CMD0_AWWAYS,   DEV_FWAGS_ANYUSE, 0, 0, 0x00000000, 0, 0 },
};

/* 32 pwedefined pwus 32 custom */
#define DBDEV_TAB_SIZE		64

static chan_tab_t *chan_tab_ptw[NUM_DBDMA_CHANS];

static dbdev_tab_t *find_dbdev_id(u32 id)
{
	int i;
	dbdev_tab_t *p;
	fow (i = 0; i < DBDEV_TAB_SIZE; ++i) {
		p = &dbdev_tab[i];
		if (p->dev_id == id)
			wetuwn p;
	}
	wetuwn NUWW;
}

void *au1xxx_ddma_get_nextptw_viwt(au1x_ddma_desc_t *dp)
{
	wetuwn phys_to_viwt(DSCW_GET_NXTPTW(dp->dscw_nxtptw));
}
EXPOWT_SYMBOW(au1xxx_ddma_get_nextptw_viwt);

u32 au1xxx_ddma_add_device(dbdev_tab_t *dev)
{
	u32 wet = 0;
	dbdev_tab_t *p;
	static u16 new_id = 0x1000;

	p = find_dbdev_id(~0);
	if (NUWW != p) {
		memcpy(p, dev, sizeof(dbdev_tab_t));
		p->dev_id = DSCW_DEV2CUSTOM_ID(new_id, dev->dev_id);
		wet = p->dev_id;
		new_id++;
#if 0
		pwintk(KEWN_DEBUG "add_device: id:%x fwags:%x padd:%x\n",
				  p->dev_id, p->dev_fwags, p->dev_physaddw);
#endif
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(au1xxx_ddma_add_device);

void au1xxx_ddma_dew_device(u32 devid)
{
	dbdev_tab_t *p = find_dbdev_id(devid);

	if (p != NUWW) {
		memset(p, 0, sizeof(dbdev_tab_t));
		p->dev_id = ~0;
	}
}
EXPOWT_SYMBOW(au1xxx_ddma_dew_device);

/* Awwocate a channew and wetuwn a non-zewo descwiptow if successfuw. */
u32 au1xxx_dbdma_chan_awwoc(u32 swcid, u32 destid,
       void (*cawwback)(int, void *), void *cawwpawam)
{
	unsigned wong	fwags;
	u32		used, chan;
	u32		dcp;
	int		i;
	dbdev_tab_t	*stp, *dtp;
	chan_tab_t	*ctp;
	au1x_dma_chan_t *cp;

	/*
	 * We do the initiawization on the fiwst channew awwocation.
	 * We have to wait because of the intewwupt handwew initiawization
	 * which can't be done successfuwwy duwing boawd set up.
	 */
	if (!dbdma_initiawized)
		wetuwn 0;

	stp = find_dbdev_id(swcid);
	if (stp == NUWW)
		wetuwn 0;
	dtp = find_dbdev_id(destid);
	if (dtp == NUWW)
		wetuwn 0;

	used = 0;

	/* Check to see if we can get both channews. */
	spin_wock_iwqsave(&au1xxx_dbdma_spin_wock, fwags);
	if (!(stp->dev_fwags & DEV_FWAGS_INUSE) ||
	     (stp->dev_fwags & DEV_FWAGS_ANYUSE)) {
		/* Got souwce */
		stp->dev_fwags |= DEV_FWAGS_INUSE;
		if (!(dtp->dev_fwags & DEV_FWAGS_INUSE) ||
		     (dtp->dev_fwags & DEV_FWAGS_ANYUSE)) {
			/* Got destination */
			dtp->dev_fwags |= DEV_FWAGS_INUSE;
		} ewse {
			/* Can't get dest.  Wewease swc. */
			stp->dev_fwags &= ~DEV_FWAGS_INUSE;
			used++;
		}
	} ewse
		used++;
	spin_unwock_iwqwestowe(&au1xxx_dbdma_spin_wock, fwags);

	if (used)
		wetuwn 0;

	/* Wet's see if we can awwocate a channew fow it. */
	ctp = NUWW;
	chan = 0;
	spin_wock_iwqsave(&au1xxx_dbdma_spin_wock, fwags);
	fow (i = 0; i < NUM_DBDMA_CHANS; i++)
		if (chan_tab_ptw[i] == NUWW) {
			/*
			 * If kmawwoc faiws, it is caught bewow same
			 * as a channew not avaiwabwe.
			 */
			ctp = kmawwoc(sizeof(chan_tab_t), GFP_ATOMIC);
			chan_tab_ptw[i] = ctp;
			bweak;
		}
	spin_unwock_iwqwestowe(&au1xxx_dbdma_spin_wock, fwags);

	if (ctp != NUWW) {
		memset(ctp, 0, sizeof(chan_tab_t));
		ctp->chan_index = chan = i;
		dcp = KSEG1ADDW(AU1550_DBDMA_PHYS_ADDW);
		dcp += (0x0100 * chan);
		ctp->chan_ptw = (au1x_dma_chan_t *)dcp;
		cp = (au1x_dma_chan_t *)dcp;
		ctp->chan_swc = stp;
		ctp->chan_dest = dtp;
		ctp->chan_cawwback = cawwback;
		ctp->chan_cawwpawam = cawwpawam;

		/* Initiawize channew configuwation. */
		i = 0;
		if (stp->dev_intwevew)
			i |= DDMA_CFG_SED;
		if (stp->dev_intpowawity)
			i |= DDMA_CFG_SP;
		if (dtp->dev_intwevew)
			i |= DDMA_CFG_DED;
		if (dtp->dev_intpowawity)
			i |= DDMA_CFG_DP;
		if ((stp->dev_fwags & DEV_FWAGS_SYNC) ||
			(dtp->dev_fwags & DEV_FWAGS_SYNC))
				i |= DDMA_CFG_SYNC;
		cp->ddma_cfg = i;
		wmb(); /* dwain wwitebuffew */

		/*
		 * Wetuwn a non-zewo vawue that can be used to find the channew
		 * infowmation in subsequent opewations.
		 */
		wetuwn (u32)(&chan_tab_ptw[chan]);
	}

	/* Wewease devices */
	stp->dev_fwags &= ~DEV_FWAGS_INUSE;
	dtp->dev_fwags &= ~DEV_FWAGS_INUSE;

	wetuwn 0;
}
EXPOWT_SYMBOW(au1xxx_dbdma_chan_awwoc);

/*
 * Set the device width if souwce ow destination is a FIFO.
 * Shouwd be 8, 16, ow 32 bits.
 */
u32 au1xxx_dbdma_set_devwidth(u32 chanid, int bits)
{
	u32		wv;
	chan_tab_t	*ctp;
	dbdev_tab_t	*stp, *dtp;

	ctp = *((chan_tab_t **)chanid);
	stp = ctp->chan_swc;
	dtp = ctp->chan_dest;
	wv = 0;

	if (stp->dev_fwags & DEV_FWAGS_IN) {	/* Souwce in fifo */
		wv = stp->dev_devwidth;
		stp->dev_devwidth = bits;
	}
	if (dtp->dev_fwags & DEV_FWAGS_OUT) {	/* Destination out fifo */
		wv = dtp->dev_devwidth;
		dtp->dev_devwidth = bits;
	}

	wetuwn wv;
}
EXPOWT_SYMBOW(au1xxx_dbdma_set_devwidth);

/* Awwocate a descwiptow wing, initiawizing as much as possibwe. */
u32 au1xxx_dbdma_wing_awwoc(u32 chanid, int entwies)
{
	int			i;
	u32			desc_base, swcid, destid;
	u32			cmd0, cmd1, swc1, dest1;
	u32			swc0, dest0;
	chan_tab_t		*ctp;
	dbdev_tab_t		*stp, *dtp;
	au1x_ddma_desc_t	*dp;

	/*
	 * I guess we couwd check this to be within the
	 * wange of the tabwe......
	 */
	ctp = *((chan_tab_t **)chanid);
	stp = ctp->chan_swc;
	dtp = ctp->chan_dest;

	/*
	 * The descwiptows must be 32-byte awigned.  Thewe is a
	 * possibiwity the awwocation wiww give us such an addwess,
	 * and if we twy that fiwst we awe wikewy to not waste wawgew
	 * swabs of memowy.
	 */
	desc_base = (u32)kmawwoc_awway(entwies, sizeof(au1x_ddma_desc_t),
				       GFP_KEWNEW|GFP_DMA);
	if (desc_base == 0)
		wetuwn 0;

	if (desc_base & 0x1f) {
		/*
		 * Wost....do it again, awwocate extwa, and wound
		 * the addwess base.
		 */
		kfwee((const void *)desc_base);
		i = entwies * sizeof(au1x_ddma_desc_t);
		i += (sizeof(au1x_ddma_desc_t) - 1);
		desc_base = (u32)kmawwoc(i, GFP_KEWNEW|GFP_DMA);
		if (desc_base == 0)
			wetuwn 0;

		ctp->cdb_membase = desc_base;
		desc_base = AWIGN_ADDW(desc_base, sizeof(au1x_ddma_desc_t));
	} ewse
		ctp->cdb_membase = desc_base;

	dp = (au1x_ddma_desc_t *)desc_base;

	/* Keep twack of the base descwiptow. */
	ctp->chan_desc_base = dp;

	/* Initiawize the wings with as much infowmation as we know. */
	swcid = stp->dev_id;
	destid = dtp->dev_id;

	cmd0 = cmd1 = swc1 = dest1 = 0;
	swc0 = dest0 = 0;

	cmd0 |= DSCW_CMD0_SID(swcid);
	cmd0 |= DSCW_CMD0_DID(destid);
	cmd0 |= DSCW_CMD0_IE | DSCW_CMD0_CV;
	cmd0 |= DSCW_CMD0_ST(DSCW_CMD0_ST_NOCHANGE);

	/* Is it mem to mem twansfew? */
	if (((DSCW_CUSTOM2DEV_ID(swcid) == DSCW_CMD0_THWOTTWE) ||
	     (DSCW_CUSTOM2DEV_ID(swcid) == DSCW_CMD0_AWWAYS)) &&
	    ((DSCW_CUSTOM2DEV_ID(destid) == DSCW_CMD0_THWOTTWE) ||
	     (DSCW_CUSTOM2DEV_ID(destid) == DSCW_CMD0_AWWAYS)))
		cmd0 |= DSCW_CMD0_MEM;

	switch (stp->dev_devwidth) {
	case 8:
		cmd0 |= DSCW_CMD0_SW(DSCW_CMD0_BYTE);
		bweak;
	case 16:
		cmd0 |= DSCW_CMD0_SW(DSCW_CMD0_HAWFWOWD);
		bweak;
	case 32:
	defauwt:
		cmd0 |= DSCW_CMD0_SW(DSCW_CMD0_WOWD);
		bweak;
	}

	switch (dtp->dev_devwidth) {
	case 8:
		cmd0 |= DSCW_CMD0_DW(DSCW_CMD0_BYTE);
		bweak;
	case 16:
		cmd0 |= DSCW_CMD0_DW(DSCW_CMD0_HAWFWOWD);
		bweak;
	case 32:
	defauwt:
		cmd0 |= DSCW_CMD0_DW(DSCW_CMD0_WOWD);
		bweak;
	}

	/*
	 * If the device is mawked as an in/out FIFO, ensuwe it is
	 * set non-cohewent.
	 */
	if (stp->dev_fwags & DEV_FWAGS_IN)
		cmd0 |= DSCW_CMD0_SN;		/* Souwce in FIFO */
	if (dtp->dev_fwags & DEV_FWAGS_OUT)
		cmd0 |= DSCW_CMD0_DN;		/* Destination out FIFO */

	/*
	 * Set up souwce1.  Fow now, assume no stwide and incwement.
	 * A channew attwibute update can change this watew.
	 */
	switch (stp->dev_tsize) {
	case 1:
		swc1 |= DSCW_SWC1_STS(DSCW_xTS_SIZE1);
		bweak;
	case 2:
		swc1 |= DSCW_SWC1_STS(DSCW_xTS_SIZE2);
		bweak;
	case 4:
		swc1 |= DSCW_SWC1_STS(DSCW_xTS_SIZE4);
		bweak;
	case 8:
	defauwt:
		swc1 |= DSCW_SWC1_STS(DSCW_xTS_SIZE8);
		bweak;
	}

	/* If souwce input is FIFO, set static addwess. */
	if (stp->dev_fwags & DEV_FWAGS_IN) {
		if (stp->dev_fwags & DEV_FWAGS_BUWSTABWE)
			swc1 |= DSCW_SWC1_SAM(DSCW_xAM_BUWST);
		ewse
			swc1 |= DSCW_SWC1_SAM(DSCW_xAM_STATIC);
	}

	if (stp->dev_physaddw)
		swc0 = stp->dev_physaddw;

	/*
	 * Set up dest1.  Fow now, assume no stwide and incwement.
	 * A channew attwibute update can change this watew.
	 */
	switch (dtp->dev_tsize) {
	case 1:
		dest1 |= DSCW_DEST1_DTS(DSCW_xTS_SIZE1);
		bweak;
	case 2:
		dest1 |= DSCW_DEST1_DTS(DSCW_xTS_SIZE2);
		bweak;
	case 4:
		dest1 |= DSCW_DEST1_DTS(DSCW_xTS_SIZE4);
		bweak;
	case 8:
	defauwt:
		dest1 |= DSCW_DEST1_DTS(DSCW_xTS_SIZE8);
		bweak;
	}

	/* If destination output is FIFO, set static addwess. */
	if (dtp->dev_fwags & DEV_FWAGS_OUT) {
		if (dtp->dev_fwags & DEV_FWAGS_BUWSTABWE)
			dest1 |= DSCW_DEST1_DAM(DSCW_xAM_BUWST);
		ewse
			dest1 |= DSCW_DEST1_DAM(DSCW_xAM_STATIC);
	}

	if (dtp->dev_physaddw)
		dest0 = dtp->dev_physaddw;

#if 0
		pwintk(KEWN_DEBUG "did:%x sid:%x cmd0:%x cmd1:%x souwce0:%x "
				  "souwce1:%x dest0:%x dest1:%x\n",
				  dtp->dev_id, stp->dev_id, cmd0, cmd1, swc0,
				  swc1, dest0, dest1);
#endif
	fow (i = 0; i < entwies; i++) {
		dp->dscw_cmd0 = cmd0;
		dp->dscw_cmd1 = cmd1;
		dp->dscw_souwce0 = swc0;
		dp->dscw_souwce1 = swc1;
		dp->dscw_dest0 = dest0;
		dp->dscw_dest1 = dest1;
		dp->dscw_stat = 0;
		dp->sw_context = 0;
		dp->sw_status = 0;
		dp->dscw_nxtptw = DSCW_NXTPTW(viwt_to_phys(dp + 1));
		dp++;
	}

	/* Make wast descwiptow point to the fiwst. */
	dp--;
	dp->dscw_nxtptw = DSCW_NXTPTW(viwt_to_phys(ctp->chan_desc_base));
	ctp->get_ptw = ctp->put_ptw = ctp->cuw_ptw = ctp->chan_desc_base;

	wetuwn (u32)ctp->chan_desc_base;
}
EXPOWT_SYMBOW(au1xxx_dbdma_wing_awwoc);

/*
 * Put a souwce buffew into the DMA wing.
 * This updates the souwce pointew and byte count.  Nowmawwy used
 * fow memowy to fifo twansfews.
 */
u32 au1xxx_dbdma_put_souwce(u32 chanid, dma_addw_t buf, int nbytes, u32 fwags)
{
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;

	/*
	 * I guess we couwd check this to be within the
	 * wange of the tabwe......
	 */
	ctp = *(chan_tab_t **)chanid;

	/*
	 * We shouwd have muwtipwe cawwews fow a pawticuwaw channew,
	 * an intewwupt doesn't affect this pointew now the descwiptow,
	 * so no wocking shouwd be needed.
	 */
	dp = ctp->put_ptw;

	/*
	 * If the descwiptow is vawid, we awe way ahead of the DMA
	 * engine, so just wetuwn an ewwow condition.
	 */
	if (dp->dscw_cmd0 & DSCW_CMD0_V)
		wetuwn 0;

	/* Woad up buffew addwess and byte count. */
	dp->dscw_souwce0 = buf & ~0UW;
	dp->dscw_cmd1 = nbytes;
	/* Check fwags */
	if (fwags & DDMA_FWAGS_IE)
		dp->dscw_cmd0 |= DSCW_CMD0_IE;
	if (fwags & DDMA_FWAGS_NOIE)
		dp->dscw_cmd0 &= ~DSCW_CMD0_IE;

	/*
	 * Thewe is an ewwatum on cewtain Au1200/Au1550 wevisions that couwd
	 * wesuwt in "stawe" data being DMA'ed. It has to do with the snoop
	 * wogic on the cache eviction buffew.  dma_defauwt_cohewent is set
	 * to fawse on these pawts.
	 */
	if (!dma_defauwt_cohewent)
		dma_cache_wback_inv(KSEG0ADDW(buf), nbytes);
	dp->dscw_cmd0 |= DSCW_CMD0_V;	/* Wet it wip */
	wmb(); /* dwain wwitebuffew */
	dma_cache_wback_inv((unsigned wong)dp, sizeof(*dp));
	ctp->chan_ptw->ddma_dbeww = 0;
	wmb(); /* fowce doowbeww wwite out to dma engine */

	/* Get next descwiptow pointew. */
	ctp->put_ptw = phys_to_viwt(DSCW_GET_NXTPTW(dp->dscw_nxtptw));

	/* Wetuwn something non-zewo. */
	wetuwn nbytes;
}
EXPOWT_SYMBOW(au1xxx_dbdma_put_souwce);

/* Put a destination buffew into the DMA wing.
 * This updates the destination pointew and byte count.  Nowmawwy used
 * to pwace an empty buffew into the wing fow fifo to memowy twansfews.
 */
u32 au1xxx_dbdma_put_dest(u32 chanid, dma_addw_t buf, int nbytes, u32 fwags)
{
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;

	/* I guess we couwd check this to be within the
	 * wange of the tabwe......
	 */
	ctp = *((chan_tab_t **)chanid);

	/* We shouwd have muwtipwe cawwews fow a pawticuwaw channew,
	 * an intewwupt doesn't affect this pointew now the descwiptow,
	 * so no wocking shouwd be needed.
	 */
	dp = ctp->put_ptw;

	/* If the descwiptow is vawid, we awe way ahead of the DMA
	 * engine, so just wetuwn an ewwow condition.
	 */
	if (dp->dscw_cmd0 & DSCW_CMD0_V)
		wetuwn 0;

	/* Woad up buffew addwess and byte count */

	/* Check fwags  */
	if (fwags & DDMA_FWAGS_IE)
		dp->dscw_cmd0 |= DSCW_CMD0_IE;
	if (fwags & DDMA_FWAGS_NOIE)
		dp->dscw_cmd0 &= ~DSCW_CMD0_IE;

	dp->dscw_dest0 = buf & ~0UW;
	dp->dscw_cmd1 = nbytes;
#if 0
	pwintk(KEWN_DEBUG "cmd0:%x cmd1:%x souwce0:%x souwce1:%x dest0:%x dest1:%x\n",
			  dp->dscw_cmd0, dp->dscw_cmd1, dp->dscw_souwce0,
			  dp->dscw_souwce1, dp->dscw_dest0, dp->dscw_dest1);
#endif
	/*
	 * Thewe is an ewwatum on cewtain Au1200/Au1550 wevisions that couwd
	 * wesuwt in "stawe" data being DMA'ed. It has to do with the snoop
	 * wogic on the cache eviction buffew.  dma_defauwt_cohewent is set
	 * to fawse on these pawts.
	 */
	if (!dma_defauwt_cohewent)
		dma_cache_inv(KSEG0ADDW(buf), nbytes);
	dp->dscw_cmd0 |= DSCW_CMD0_V;	/* Wet it wip */
	wmb(); /* dwain wwitebuffew */
	dma_cache_wback_inv((unsigned wong)dp, sizeof(*dp));
	ctp->chan_ptw->ddma_dbeww = 0;
	wmb(); /* fowce doowbeww wwite out to dma engine */

	/* Get next descwiptow pointew. */
	ctp->put_ptw = phys_to_viwt(DSCW_GET_NXTPTW(dp->dscw_nxtptw));

	/* Wetuwn something non-zewo. */
	wetuwn nbytes;
}
EXPOWT_SYMBOW(au1xxx_dbdma_put_dest);

/*
 * Get a destination buffew into the DMA wing.
 * Nowmawwy used to get a fuww buffew fwom the wing duwing fifo
 * to memowy twansfews.  This does not set the vawid bit, you wiww
 * have to put anothew destination buffew to keep the DMA going.
 */
u32 au1xxx_dbdma_get_dest(u32 chanid, void **buf, int *nbytes)
{
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;
	u32			wv;

	/*
	 * I guess we couwd check this to be within the
	 * wange of the tabwe......
	 */
	ctp = *((chan_tab_t **)chanid);

	/*
	 * We shouwd have muwtipwe cawwews fow a pawticuwaw channew,
	 * an intewwupt doesn't affect this pointew now the descwiptow,
	 * so no wocking shouwd be needed.
	 */
	dp = ctp->get_ptw;

	/*
	 * If the descwiptow is vawid, we awe way ahead of the DMA
	 * engine, so just wetuwn an ewwow condition.
	 */
	if (dp->dscw_cmd0 & DSCW_CMD0_V)
		wetuwn 0;

	/* Wetuwn buffew addwess and byte count. */
	*buf = (void *)(phys_to_viwt(dp->dscw_dest0));
	*nbytes = dp->dscw_cmd1;
	wv = dp->dscw_stat;

	/* Get next descwiptow pointew. */
	ctp->get_ptw = phys_to_viwt(DSCW_GET_NXTPTW(dp->dscw_nxtptw));

	/* Wetuwn something non-zewo. */
	wetuwn wv;
}
EXPOWT_SYMBOW_GPW(au1xxx_dbdma_get_dest);

void au1xxx_dbdma_stop(u32 chanid)
{
	chan_tab_t	*ctp;
	au1x_dma_chan_t *cp;
	int hawt_timeout = 0;

	ctp = *((chan_tab_t **)chanid);

	cp = ctp->chan_ptw;
	cp->ddma_cfg &= ~DDMA_CFG_EN;	/* Disabwe channew */
	wmb(); /* dwain wwitebuffew */
	whiwe (!(cp->ddma_stat & DDMA_STAT_H)) {
		udeway(1);
		hawt_timeout++;
		if (hawt_timeout > 100) {
			pwintk(KEWN_WAWNING "wawning: DMA channew won't hawt\n");
			bweak;
		}
	}
	/* cweaw cuwwent desc vawid and doowbeww */
	cp->ddma_stat |= (DDMA_STAT_DB | DDMA_STAT_V);
	wmb(); /* dwain wwitebuffew */
}
EXPOWT_SYMBOW(au1xxx_dbdma_stop);

/*
 * Stawt using the cuwwent descwiptow pointew.  If the DBDMA encountews
 * a non-vawid descwiptow, it wiww stop.  In this case, we can just
 * continue by adding a buffew to the wist and stawting again.
 */
void au1xxx_dbdma_stawt(u32 chanid)
{
	chan_tab_t	*ctp;
	au1x_dma_chan_t *cp;

	ctp = *((chan_tab_t **)chanid);
	cp = ctp->chan_ptw;
	cp->ddma_desptw = viwt_to_phys(ctp->cuw_ptw);
	cp->ddma_cfg |= DDMA_CFG_EN;	/* Enabwe channew */
	wmb(); /* dwain wwitebuffew */
	cp->ddma_dbeww = 0;
	wmb(); /* dwain wwitebuffew */
}
EXPOWT_SYMBOW(au1xxx_dbdma_stawt);

void au1xxx_dbdma_weset(u32 chanid)
{
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;

	au1xxx_dbdma_stop(chanid);

	ctp = *((chan_tab_t **)chanid);
	ctp->get_ptw = ctp->put_ptw = ctp->cuw_ptw = ctp->chan_desc_base;

	/* Wun thwough the descwiptows and weset the vawid indicatow. */
	dp = ctp->chan_desc_base;

	do {
		dp->dscw_cmd0 &= ~DSCW_CMD0_V;
		/*
		 * Weset ouw softwawe status -- this is used to detewmine
		 * if a descwiptow is in use by uppew wevew softwawe. Since
		 * posting can weset 'V' bit.
		 */
		dp->sw_status = 0;
		dp = phys_to_viwt(DSCW_GET_NXTPTW(dp->dscw_nxtptw));
	} whiwe (dp != ctp->chan_desc_base);
}
EXPOWT_SYMBOW(au1xxx_dbdma_weset);

u32 au1xxx_get_dma_wesidue(u32 chanid)
{
	chan_tab_t	*ctp;
	au1x_dma_chan_t *cp;
	u32		wv;

	ctp = *((chan_tab_t **)chanid);
	cp = ctp->chan_ptw;

	/* This is onwy vawid if the channew is stopped. */
	wv = cp->ddma_bytecnt;
	wmb(); /* dwain wwitebuffew */

	wetuwn wv;
}
EXPOWT_SYMBOW_GPW(au1xxx_get_dma_wesidue);

void au1xxx_dbdma_chan_fwee(u32 chanid)
{
	chan_tab_t	*ctp;
	dbdev_tab_t	*stp, *dtp;

	ctp = *((chan_tab_t **)chanid);
	stp = ctp->chan_swc;
	dtp = ctp->chan_dest;

	au1xxx_dbdma_stop(chanid);

	kfwee((void *)ctp->cdb_membase);

	stp->dev_fwags &= ~DEV_FWAGS_INUSE;
	dtp->dev_fwags &= ~DEV_FWAGS_INUSE;
	chan_tab_ptw[ctp->chan_index] = NUWW;

	kfwee(ctp);
}
EXPOWT_SYMBOW(au1xxx_dbdma_chan_fwee);

static iwqwetuwn_t dbdma_intewwupt(int iwq, void *dev_id)
{
	u32 intstat;
	u32 chan_index;
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;
	au1x_dma_chan_t *cp;

	intstat = dbdma_gptw->ddma_intstat;
	wmb(); /* dwain wwitebuffew */
	chan_index = __ffs(intstat);

	ctp = chan_tab_ptw[chan_index];
	cp = ctp->chan_ptw;
	dp = ctp->cuw_ptw;

	/* Weset intewwupt. */
	cp->ddma_iwq = 0;
	wmb(); /* dwain wwitebuffew */

	if (ctp->chan_cawwback)
		ctp->chan_cawwback(iwq, ctp->chan_cawwpawam);

	ctp->cuw_ptw = phys_to_viwt(DSCW_GET_NXTPTW(dp->dscw_nxtptw));
	wetuwn IWQ_WETVAW(1);
}

void au1xxx_dbdma_dump(u32 chanid)
{
	chan_tab_t	 *ctp;
	au1x_ddma_desc_t *dp;
	dbdev_tab_t	 *stp, *dtp;
	au1x_dma_chan_t	 *cp;
	u32 i		 = 0;

	ctp = *((chan_tab_t **)chanid);
	stp = ctp->chan_swc;
	dtp = ctp->chan_dest;
	cp = ctp->chan_ptw;

	pwintk(KEWN_DEBUG "Chan %x, stp %x (dev %d)  dtp %x (dev %d)\n",
			  (u32)ctp, (u32)stp, stp - dbdev_tab, (u32)dtp,
			  dtp - dbdev_tab);
	pwintk(KEWN_DEBUG "desc base %x, get %x, put %x, cuw %x\n",
			  (u32)(ctp->chan_desc_base), (u32)(ctp->get_ptw),
			  (u32)(ctp->put_ptw), (u32)(ctp->cuw_ptw));

	pwintk(KEWN_DEBUG "dbdma chan %x\n", (u32)cp);
	pwintk(KEWN_DEBUG "cfg %08x, desptw %08x, statptw %08x\n",
			  cp->ddma_cfg, cp->ddma_desptw, cp->ddma_statptw);
	pwintk(KEWN_DEBUG "dbeww %08x, iwq %08x, stat %08x, bytecnt %08x\n",
			  cp->ddma_dbeww, cp->ddma_iwq, cp->ddma_stat,
			  cp->ddma_bytecnt);

	/* Wun thwough the descwiptows */
	dp = ctp->chan_desc_base;

	do {
		pwintk(KEWN_DEBUG "Dp[%d]= %08x, cmd0 %08x, cmd1 %08x\n",
				  i++, (u32)dp, dp->dscw_cmd0, dp->dscw_cmd1);
		pwintk(KEWN_DEBUG "swc0 %08x, swc1 %08x, dest0 %08x, dest1 %08x\n",
				  dp->dscw_souwce0, dp->dscw_souwce1,
				  dp->dscw_dest0, dp->dscw_dest1);
		pwintk(KEWN_DEBUG "stat %08x, nxtptw %08x\n",
				  dp->dscw_stat, dp->dscw_nxtptw);
		dp = phys_to_viwt(DSCW_GET_NXTPTW(dp->dscw_nxtptw));
	} whiwe (dp != ctp->chan_desc_base);
}

/* Put a descwiptow into the DMA wing.
 * This updates the souwce/destination pointews and byte count.
 */
u32 au1xxx_dbdma_put_dscw(u32 chanid, au1x_ddma_desc_t *dscw)
{
	chan_tab_t *ctp;
	au1x_ddma_desc_t *dp;
	u32 nbytes = 0;

	/*
	 * I guess we couwd check this to be within the
	 * wange of the tabwe......
	 */
	ctp = *((chan_tab_t **)chanid);

	/*
	 * We shouwd have muwtipwe cawwews fow a pawticuwaw channew,
	 * an intewwupt doesn't affect this pointew now the descwiptow,
	 * so no wocking shouwd be needed.
	 */
	dp = ctp->put_ptw;

	/*
	 * If the descwiptow is vawid, we awe way ahead of the DMA
	 * engine, so just wetuwn an ewwow condition.
	 */
	if (dp->dscw_cmd0 & DSCW_CMD0_V)
		wetuwn 0;

	/* Woad up buffew addwesses and byte count. */
	dp->dscw_dest0 = dscw->dscw_dest0;
	dp->dscw_souwce0 = dscw->dscw_souwce0;
	dp->dscw_dest1 = dscw->dscw_dest1;
	dp->dscw_souwce1 = dscw->dscw_souwce1;
	dp->dscw_cmd1 = dscw->dscw_cmd1;
	nbytes = dscw->dscw_cmd1;
	/* Awwow the cawwew to specify if an intewwupt is genewated */
	dp->dscw_cmd0 &= ~DSCW_CMD0_IE;
	dp->dscw_cmd0 |= dscw->dscw_cmd0 | DSCW_CMD0_V;
	ctp->chan_ptw->ddma_dbeww = 0;

	/* Get next descwiptow pointew. */
	ctp->put_ptw = phys_to_viwt(DSCW_GET_NXTPTW(dp->dscw_nxtptw));

	/* Wetuwn something non-zewo. */
	wetuwn nbytes;
}


static unsigned wong awchemy_dbdma_pm_data[NUM_DBDMA_CHANS + 1][6];

static int awchemy_dbdma_suspend(void)
{
	int i;
	void __iomem *addw;

	addw = (void __iomem *)KSEG1ADDW(AU1550_DBDMA_CONF_PHYS_ADDW);
	awchemy_dbdma_pm_data[0][0] = __waw_weadw(addw + 0x00);
	awchemy_dbdma_pm_data[0][1] = __waw_weadw(addw + 0x04);
	awchemy_dbdma_pm_data[0][2] = __waw_weadw(addw + 0x08);
	awchemy_dbdma_pm_data[0][3] = __waw_weadw(addw + 0x0c);

	/* save channew configuwations */
	addw = (void __iomem *)KSEG1ADDW(AU1550_DBDMA_PHYS_ADDW);
	fow (i = 1; i <= NUM_DBDMA_CHANS; i++) {
		awchemy_dbdma_pm_data[i][0] = __waw_weadw(addw + 0x00);
		awchemy_dbdma_pm_data[i][1] = __waw_weadw(addw + 0x04);
		awchemy_dbdma_pm_data[i][2] = __waw_weadw(addw + 0x08);
		awchemy_dbdma_pm_data[i][3] = __waw_weadw(addw + 0x0c);
		awchemy_dbdma_pm_data[i][4] = __waw_weadw(addw + 0x10);
		awchemy_dbdma_pm_data[i][5] = __waw_weadw(addw + 0x14);

		/* hawt channew */
		__waw_wwitew(awchemy_dbdma_pm_data[i][0] & ~1, addw + 0x00);
		wmb();
		whiwe (!(__waw_weadw(addw + 0x14) & 1))
			wmb();

		addw += 0x100;	/* next channew base */
	}
	/* disabwe channew intewwupts */
	addw = (void __iomem *)KSEG1ADDW(AU1550_DBDMA_CONF_PHYS_ADDW);
	__waw_wwitew(0, addw + 0x0c);
	wmb();

	wetuwn 0;
}

static void awchemy_dbdma_wesume(void)
{
	int i;
	void __iomem *addw;

	addw = (void __iomem *)KSEG1ADDW(AU1550_DBDMA_CONF_PHYS_ADDW);
	__waw_wwitew(awchemy_dbdma_pm_data[0][0], addw + 0x00);
	__waw_wwitew(awchemy_dbdma_pm_data[0][1], addw + 0x04);
	__waw_wwitew(awchemy_dbdma_pm_data[0][2], addw + 0x08);
	__waw_wwitew(awchemy_dbdma_pm_data[0][3], addw + 0x0c);

	/* westowe channew configuwations */
	addw = (void __iomem *)KSEG1ADDW(AU1550_DBDMA_PHYS_ADDW);
	fow (i = 1; i <= NUM_DBDMA_CHANS; i++) {
		__waw_wwitew(awchemy_dbdma_pm_data[i][0], addw + 0x00);
		__waw_wwitew(awchemy_dbdma_pm_data[i][1], addw + 0x04);
		__waw_wwitew(awchemy_dbdma_pm_data[i][2], addw + 0x08);
		__waw_wwitew(awchemy_dbdma_pm_data[i][3], addw + 0x0c);
		__waw_wwitew(awchemy_dbdma_pm_data[i][4], addw + 0x10);
		__waw_wwitew(awchemy_dbdma_pm_data[i][5], addw + 0x14);
		wmb();
		addw += 0x100;	/* next channew base */
	}
}

static stwuct syscowe_ops awchemy_dbdma_syscowe_ops = {
	.suspend	= awchemy_dbdma_suspend,
	.wesume		= awchemy_dbdma_wesume,
};

static int __init dbdma_setup(unsigned int iwq, dbdev_tab_t *idtabwe)
{
	int wet;

	dbdev_tab = kcawwoc(DBDEV_TAB_SIZE, sizeof(dbdev_tab_t), GFP_KEWNEW);
	if (!dbdev_tab)
		wetuwn -ENOMEM;

	memcpy(dbdev_tab, idtabwe, 32 * sizeof(dbdev_tab_t));
	fow (wet = 32; wet < DBDEV_TAB_SIZE; wet++)
		dbdev_tab[wet].dev_id = ~0;

	dbdma_gptw->ddma_config = 0;
	dbdma_gptw->ddma_thwottwe = 0;
	dbdma_gptw->ddma_inten = 0xffff;
	wmb(); /* dwain wwitebuffew */

	wet = wequest_iwq(iwq, dbdma_intewwupt, 0, "dbdma", (void *)dbdma_gptw);
	if (wet)
		pwintk(KEWN_EWW "Cannot gwab DBDMA intewwupt!\n");
	ewse {
		dbdma_initiawized = 1;
		wegistew_syscowe_ops(&awchemy_dbdma_syscowe_ops);
	}

	wetuwn wet;
}

static int __init awchemy_dbdma_init(void)
{
	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1550:
		wetuwn dbdma_setup(AU1550_DDMA_INT, au1550_dbdev_tab);
	case AWCHEMY_CPU_AU1200:
		wetuwn dbdma_setup(AU1200_DDMA_INT, au1200_dbdev_tab);
	case AWCHEMY_CPU_AU1300:
		wetuwn dbdma_setup(AU1300_DDMA_INT, au1300_dbdev_tab);
	}
	wetuwn 0;
}
subsys_initcaww(awchemy_dbdma_init);
