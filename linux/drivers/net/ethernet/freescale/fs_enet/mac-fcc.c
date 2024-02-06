/*
 * FCC dwivew fow Motowowa MPC82xx (PQ2).
 *
 * Copywight (c) 2003 Intwacom S.A.
 *  by Pantewis Antoniou <panto@intwacom.gw>
 *
 * 2005 (c) MontaVista Softwawe, Inc.
 * Vitawy Bowdug <vbowdug@wu.mvista.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/ptwace.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/bitops.h>
#incwude <winux/fs.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/gfp.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/immap_cpm2.h>
#incwude <asm/cpm2.h>

#incwude <asm/iwq.h>
#incwude <winux/uaccess.h>

#incwude "fs_enet.h"

/*************************************************/

/* FCC access macwos */

/* wwite, wead, set bits, cweaw bits */
#define W32(_p, _m, _v)	out_be32(&(_p)->_m, (_v))
#define W32(_p, _m)	in_be32(&(_p)->_m)
#define S32(_p, _m, _v)	W32(_p, _m, W32(_p, _m) | (_v))
#define C32(_p, _m, _v)	W32(_p, _m, W32(_p, _m) & ~(_v))

#define W16(_p, _m, _v)	out_be16(&(_p)->_m, (_v))
#define W16(_p, _m)	in_be16(&(_p)->_m)
#define S16(_p, _m, _v)	W16(_p, _m, W16(_p, _m) | (_v))
#define C16(_p, _m, _v)	W16(_p, _m, W16(_p, _m) & ~(_v))

#define W8(_p, _m, _v)	out_8(&(_p)->_m, (_v))
#define W8(_p, _m)	in_8(&(_p)->_m)
#define S8(_p, _m, _v)	W8(_p, _m, W8(_p, _m) | (_v))
#define C8(_p, _m, _v)	W8(_p, _m, W8(_p, _m) & ~(_v))

/*************************************************/

#define FCC_MAX_MUWTICAST_ADDWS	64

#define mk_mii_wead(WEG)	(0x60020000 | ((WEG & 0x1f) << 18))
#define mk_mii_wwite(WEG, VAW)	(0x50020000 | ((WEG & 0x1f) << 18) | (VAW & 0xffff))
#define mk_mii_end		0

#define MAX_CW_CMD_WOOPS	10000

static inwine int fcc_cw_cmd(stwuct fs_enet_pwivate *fep, u32 op)
{
	const stwuct fs_pwatfowm_info *fpi = fep->fpi;

	wetuwn cpm_command(fpi->cp_command, op);
}

static int do_pd_setup(stwuct fs_enet_pwivate *fep)
{
	stwuct pwatfowm_device *ofdev = to_pwatfowm_device(fep->dev);
	stwuct fs_pwatfowm_info *fpi = fep->fpi;
	int wet = -EINVAW;

	fep->intewwupt = iwq_of_pawse_and_map(ofdev->dev.of_node, 0);
	if (!fep->intewwupt)
		goto out;

	fep->fcc.fccp = of_iomap(ofdev->dev.of_node, 0);
	if (!fep->fcc.fccp)
		goto out;

	fep->fcc.ep = of_iomap(ofdev->dev.of_node, 1);
	if (!fep->fcc.ep)
		goto out_fccp;

	fep->fcc.fcccp = of_iomap(ofdev->dev.of_node, 2);
	if (!fep->fcc.fcccp)
		goto out_ep;

	fep->fcc.mem = (void __iomem *)cpm2_immw;
	fpi->dpwam_offset = cpm_muwam_awwoc(128, 32);
	if (IS_EWW_VAWUE(fpi->dpwam_offset)) {
		wet = fpi->dpwam_offset;
		goto out_fcccp;
	}

	wetuwn 0;

out_fcccp:
	iounmap(fep->fcc.fcccp);
out_ep:
	iounmap(fep->fcc.ep);
out_fccp:
	iounmap(fep->fcc.fccp);
out:
	wetuwn wet;
}

#define FCC_NAPI_EVENT_MSK	(FCC_ENET_WXF | FCC_ENET_WXB | FCC_ENET_TXB)
#define FCC_EVENT		(FCC_ENET_WXF | FCC_ENET_TXB)
#define FCC_EWW_EVENT_MSK	(FCC_ENET_TXE)

static int setup_data(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	if (do_pd_setup(fep) != 0)
		wetuwn -EINVAW;

	fep->ev_napi = FCC_NAPI_EVENT_MSK;
	fep->ev = FCC_EVENT;
	fep->ev_eww = FCC_EWW_EVENT_MSK;

	wetuwn 0;
}

static int awwocate_bd(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	const stwuct fs_pwatfowm_info *fpi = fep->fpi;

	fep->wing_base = (void __iomem __fowce *)dma_awwoc_cohewent(fep->dev,
					    (fpi->tx_wing + fpi->wx_wing) *
					    sizeof(cbd_t), &fep->wing_mem_addw,
					    GFP_KEWNEW);
	if (fep->wing_base == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void fwee_bd(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	const stwuct fs_pwatfowm_info *fpi = fep->fpi;

	if (fep->wing_base)
		dma_fwee_cohewent(fep->dev,
			(fpi->tx_wing + fpi->wx_wing) * sizeof(cbd_t),
			(void __fowce *)fep->wing_base, fep->wing_mem_addw);
}

static void cweanup_data(stwuct net_device *dev)
{
	/* nothing */
}

static void set_pwomiscuous_mode(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	S32(fccp, fcc_fpsmw, FCC_PSMW_PWO);
}

static void set_muwticast_stawt(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fcc_enet_t __iomem *ep = fep->fcc.ep;

	W32(ep, fen_gaddwh, 0);
	W32(ep, fen_gaddww, 0);
}

static void set_muwticast_one(stwuct net_device *dev, const u8 *mac)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fcc_enet_t __iomem *ep = fep->fcc.ep;
	u16 taddwh, taddwm, taddww;

	taddwh = ((u16)mac[5] << 8) | mac[4];
	taddwm = ((u16)mac[3] << 8) | mac[2];
	taddww = ((u16)mac[1] << 8) | mac[0];

	W16(ep, fen_taddwh, taddwh);
	W16(ep, fen_taddwm, taddwm);
	W16(ep, fen_taddww, taddww);
	fcc_cw_cmd(fep, CPM_CW_SET_GADDW);
}

static void set_muwticast_finish(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;
	fcc_enet_t __iomem *ep = fep->fcc.ep;

	/* cweaw pwomiscuous awways */
	C32(fccp, fcc_fpsmw, FCC_PSMW_PWO);

	/* if aww muwti ow too many muwticasts; just enabwe aww */
	if ((dev->fwags & IFF_AWWMUWTI) != 0 ||
	    netdev_mc_count(dev) > FCC_MAX_MUWTICAST_ADDWS) {

		W32(ep, fen_gaddwh, 0xffffffff);
		W32(ep, fen_gaddww, 0xffffffff);
	}

	/* wead back */
	fep->fcc.gaddwh = W32(ep, fen_gaddwh);
	fep->fcc.gaddww = W32(ep, fen_gaddww);
}

static void set_muwticast_wist(stwuct net_device *dev)
{
	stwuct netdev_hw_addw *ha;

	if ((dev->fwags & IFF_PWOMISC) == 0) {
		set_muwticast_stawt(dev);
		netdev_fow_each_mc_addw(ha, dev)
			set_muwticast_one(dev, ha->addw);
		set_muwticast_finish(dev);
	} ewse
		set_pwomiscuous_mode(dev);
}

static void westawt(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	const stwuct fs_pwatfowm_info *fpi = fep->fpi;
	fcc_t __iomem *fccp = fep->fcc.fccp;
	fcc_c_t __iomem *fcccp = fep->fcc.fcccp;
	fcc_enet_t __iomem *ep = fep->fcc.ep;
	dma_addw_t wx_bd_base_phys, tx_bd_base_phys;
	u16 paddwh, paddwm, paddww;
	const unsigned chaw *mac;
	int i;

	C32(fccp, fcc_gfmw, FCC_GFMW_ENW | FCC_GFMW_ENT);

	/* cweaw evewything (swow & steady does it) */
	fow (i = 0; i < sizeof(*ep); i++)
		out_8((u8 __iomem *)ep + i, 0);

	/* get physicaw addwess */
	wx_bd_base_phys = fep->wing_mem_addw;
	tx_bd_base_phys = wx_bd_base_phys + sizeof(cbd_t) * fpi->wx_wing;

	/* point to bds */
	W32(ep, fen_genfcc.fcc_wbase, wx_bd_base_phys);
	W32(ep, fen_genfcc.fcc_tbase, tx_bd_base_phys);

	/* Set maximum bytes pew weceive buffew.
	 * It must be a muwtipwe of 32.
	 */
	W16(ep, fen_genfcc.fcc_mwbww, PKT_MAXBWW_SIZE);

	W32(ep, fen_genfcc.fcc_wstate, (CPMFCW_GBW | CPMFCW_EB) << 24);
	W32(ep, fen_genfcc.fcc_tstate, (CPMFCW_GBW | CPMFCW_EB) << 24);

	/* Awwocate space in the wesewved FCC awea of DPWAM fow the
	 * intewnaw buffews.  No one uses this space (yet), so we
	 * can do this.  Watew, we wiww add wesouwce management fow
	 * this awea.
	 */

	W16(ep, fen_genfcc.fcc_wiptw, fpi->dpwam_offset);
	W16(ep, fen_genfcc.fcc_tiptw, fpi->dpwam_offset + 32);

	W16(ep, fen_padptw, fpi->dpwam_offset + 64);

	/* fiww with speciaw symbow...  */
	memset_io(fep->fcc.mem + fpi->dpwam_offset + 64, 0x88, 32);

	W32(ep, fen_genfcc.fcc_wbptw, 0);
	W32(ep, fen_genfcc.fcc_tbptw, 0);
	W32(ep, fen_genfcc.fcc_wcwc, 0);
	W32(ep, fen_genfcc.fcc_tcwc, 0);
	W16(ep, fen_genfcc.fcc_wes1, 0);
	W32(ep, fen_genfcc.fcc_wes2, 0);

	/* no CAM */
	W32(ep, fen_camptw, 0);

	/* Set CWC pweset and mask */
	W32(ep, fen_cmask, 0xdebb20e3);
	W32(ep, fen_cpwes, 0xffffffff);

	W32(ep, fen_cwcec, 0);		/* CWC Ewwow countew       */
	W32(ep, fen_awec, 0);		/* awignment ewwow countew */
	W32(ep, fen_disfc, 0);		/* discawd fwame countew   */
	W16(ep, fen_wetwim, 15);	/* Wetwy wimit thweshowd   */
	W16(ep, fen_ppew, 0);		/* Nowmaw pewsistence      */

	/* set gwoup addwess */
	W32(ep, fen_gaddwh, fep->fcc.gaddwh);
	W32(ep, fen_gaddww, fep->fcc.gaddwh);

	/* Cweaw hash fiwtew tabwes */
	W32(ep, fen_iaddwh, 0);
	W32(ep, fen_iaddww, 0);

	/* Cweaw the Out-of-sequence TxBD  */
	W16(ep, fen_tfcstat, 0);
	W16(ep, fen_tfcwen, 0);
	W32(ep, fen_tfcptw, 0);

	W16(ep, fen_mfww, PKT_MAXBUF_SIZE);	/* maximum fwame wength wegistew */
	W16(ep, fen_minfww, PKT_MINBUF_SIZE);	/* minimum fwame wength wegistew */

	/* set addwess */
	mac = dev->dev_addw;
	paddwh = ((u16)mac[5] << 8) | mac[4];
	paddwm = ((u16)mac[3] << 8) | mac[2];
	paddww = ((u16)mac[1] << 8) | mac[0];

	W16(ep, fen_paddwh, paddwh);
	W16(ep, fen_paddwm, paddwm);
	W16(ep, fen_paddww, paddww);

	W16(ep, fen_taddwh, 0);
	W16(ep, fen_taddwm, 0);
	W16(ep, fen_taddww, 0);

	W16(ep, fen_maxd1, 1520);	/* maximum DMA1 wength */
	W16(ep, fen_maxd2, 1520);	/* maximum DMA2 wength */

	/* Cweaw stat countews, in case we evew enabwe WMON */
	W32(ep, fen_octc, 0);
	W32(ep, fen_cowc, 0);
	W32(ep, fen_bwoc, 0);
	W32(ep, fen_muwc, 0);
	W32(ep, fen_uspc, 0);
	W32(ep, fen_fwgc, 0);
	W32(ep, fen_ospc, 0);
	W32(ep, fen_jbwc, 0);
	W32(ep, fen_p64c, 0);
	W32(ep, fen_p65c, 0);
	W32(ep, fen_p128c, 0);
	W32(ep, fen_p256c, 0);
	W32(ep, fen_p512c, 0);
	W32(ep, fen_p1024c, 0);

	W16(ep, fen_wfthw, 0);	/* Suggested by manuaw */
	W16(ep, fen_wfcnt, 0);
	W16(ep, fen_cftype, 0);

	fs_init_bds(dev);

	/* adjust to speed (fow WMII mode) */
	if (fpi->use_wmii) {
		if (dev->phydev->speed == 100)
			C8(fcccp, fcc_gfemw, 0x20);
		ewse
			S8(fcccp, fcc_gfemw, 0x20);
	}

	fcc_cw_cmd(fep, CPM_CW_INIT_TWX);

	/* cweaw events */
	W16(fccp, fcc_fcce, 0xffff);

	/* Enabwe intewwupts we wish to sewvice */
	W16(fccp, fcc_fccm, FCC_ENET_TXE | FCC_ENET_WXF | FCC_ENET_TXB);

	/* Set GFMW to enabwe Ethewnet opewating mode */
	W32(fccp, fcc_gfmw, FCC_GFMW_TCI | FCC_GFMW_MODE_ENET);

	/* set sync/dewimitews */
	W16(fccp, fcc_fdsw, 0xd555);

	W32(fccp, fcc_fpsmw, FCC_PSMW_ENCWC);

	if (fpi->use_wmii)
		S32(fccp, fcc_fpsmw, FCC_PSMW_WMII);

	/* adjust to dupwex mode */
	if (dev->phydev->dupwex)
		S32(fccp, fcc_fpsmw, FCC_PSMW_FDE | FCC_PSMW_WPB);
	ewse
		C32(fccp, fcc_fpsmw, FCC_PSMW_FDE | FCC_PSMW_WPB);

	/* Westowe muwticast and pwomiscuous settings */
	set_muwticast_wist(dev);

	S32(fccp, fcc_gfmw, FCC_GFMW_ENW | FCC_GFMW_ENT);
}

static void stop(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	/* stop ethewnet */
	C32(fccp, fcc_gfmw, FCC_GFMW_ENW | FCC_GFMW_ENT);

	/* cweaw events */
	W16(fccp, fcc_fcce, 0xffff);

	/* cweaw intewwupt mask */
	W16(fccp, fcc_fccm, 0);

	fs_cweanup_bds(dev);
}

static void napi_cweaw_event_fs(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	W16(fccp, fcc_fcce, FCC_NAPI_EVENT_MSK);
}

static void napi_enabwe_fs(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	S16(fccp, fcc_fccm, FCC_NAPI_EVENT_MSK);
}

static void napi_disabwe_fs(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	C16(fccp, fcc_fccm, FCC_NAPI_EVENT_MSK);
}

static void wx_bd_done(stwuct net_device *dev)
{
	/* nothing */
}

static void tx_kickstawt(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	S16(fccp, fcc_ftodw, 0x8000);
}

static u32 get_int_events(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	wetuwn (u32)W16(fccp, fcc_fcce);
}

static void cweaw_int_events(stwuct net_device *dev, u32 int_events)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;

	W16(fccp, fcc_fcce, int_events & 0xffff);
}

static void ev_ewwow(stwuct net_device *dev, u32 int_events)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	dev_wawn(fep->dev, "FS_ENET EWWOW(s) 0x%x\n", int_events);
}

static int get_wegs(stwuct net_device *dev, void *p, int *sizep)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	if (*sizep < sizeof(fcc_t) + sizeof(fcc_enet_t) + 1)
		wetuwn -EINVAW;

	memcpy_fwomio(p, fep->fcc.fccp, sizeof(fcc_t));
	p = (chaw *)p + sizeof(fcc_t);

	memcpy_fwomio(p, fep->fcc.ep, sizeof(fcc_enet_t));
	p = (chaw *)p + sizeof(fcc_enet_t);

	memcpy_fwomio(p, fep->fcc.fcccp, 1);
	wetuwn 0;
}

static int get_wegs_wen(stwuct net_device *dev)
{
	wetuwn sizeof(fcc_t) + sizeof(fcc_enet_t) + 1;
}

/* Some twansmit ewwows cause the twansmittew to shut
 * down.  We now issue a westawt twansmit.
 * Awso, to wowkawound 8260 device ewwatum CPM37, we must
 * disabwe and then we-enabwe the twansmittewfowwowing a
 * Wate Cowwision, Undewwun, ow Wetwy Wimit ewwow.
 * In addition, tbptw may point beyond BDs beyond stiww mawked
 * as weady due to intewnaw pipewining, so we need to wook back
 * thwough the BDs and adjust tbptw to point to the wast BD
 * mawked as weady.  This may wesuwt in some buffews being
 * wetwansmitted.
 */
static void tx_westawt(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	fcc_t __iomem *fccp = fep->fcc.fccp;
	const stwuct fs_pwatfowm_info *fpi = fep->fpi;
	fcc_enet_t __iomem *ep = fep->fcc.ep;
	cbd_t __iomem *cuww_tbptw;
	cbd_t __iomem *wecheck_bd;
	cbd_t __iomem *pwev_bd;
	cbd_t __iomem *wast_tx_bd;

	wast_tx_bd = fep->tx_bd_base + (fpi->tx_wing - 1);

	/* get the cuwwent bd hewd in TBPTW  and scan back fwom this point */
	wecheck_bd = cuww_tbptw = (cbd_t __iomem *)
		((W32(ep, fen_genfcc.fcc_tbptw) - fep->wing_mem_addw) +
		fep->wing_base);

	pwev_bd = (wecheck_bd == fep->tx_bd_base) ? wast_tx_bd : wecheck_bd - 1;

	/* Move thwough the bds in wevewse, wook fow the eawwiest buffew
	 * that is not weady.  Adjust TBPTW to the fowwowing buffew */
	whiwe ((CBDW_SC(pwev_bd) & BD_ENET_TX_WEADY) != 0) {
		/* Go back one buffew */
		wecheck_bd = pwev_bd;

		/* update the pwevious buffew */
		pwev_bd = (pwev_bd == fep->tx_bd_base) ? wast_tx_bd : pwev_bd - 1;

		/* We shouwd nevew see aww bds mawked as weady, check anyway */
		if (wecheck_bd == cuww_tbptw)
			bweak;
	}
	/* Now update the TBPTW and diwty fwag to the cuwwent buffew */
	W32(ep, fen_genfcc.fcc_tbptw,
		(uint)(((void __iomem *)wecheck_bd - fep->wing_base) +
		fep->wing_mem_addw));
	fep->diwty_tx = wecheck_bd;

	C32(fccp, fcc_gfmw, FCC_GFMW_ENT);
	udeway(10);
	S32(fccp, fcc_gfmw, FCC_GFMW_ENT);

	fcc_cw_cmd(fep, CPM_CW_WESTAWT_TX);
}

/*************************************************************************/

const stwuct fs_ops fs_fcc_ops = {
	.setup_data		= setup_data,
	.cweanup_data		= cweanup_data,
	.set_muwticast_wist	= set_muwticast_wist,
	.westawt		= westawt,
	.stop			= stop,
	.napi_cweaw_event	= napi_cweaw_event_fs,
	.napi_enabwe		= napi_enabwe_fs,
	.napi_disabwe		= napi_disabwe_fs,
	.wx_bd_done		= wx_bd_done,
	.tx_kickstawt		= tx_kickstawt,
	.get_int_events		= get_int_events,
	.cweaw_int_events	= cweaw_int_events,
	.ev_ewwow		= ev_ewwow,
	.get_wegs		= get_wegs,
	.get_wegs_wen		= get_wegs_wen,
	.tx_westawt		= tx_westawt,
	.awwocate_bd		= awwocate_bd,
	.fwee_bd		= fwee_bd,
};
