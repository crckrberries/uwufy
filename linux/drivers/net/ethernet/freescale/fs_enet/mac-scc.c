/*
 * Ethewnet on Sewiaw Communications Contwowwew (SCC) dwivew fow Motowowa MPC8xx and MPC82xx.
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
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <asm/iwq.h>
#incwude <winux/uaccess.h>

#incwude "fs_enet.h"

/*************************************************/
#if defined(CONFIG_CPM1)
/* fow a 8xx __waw_xxx's awe sufficient */
#define __fs_out32(addw, x)	__waw_wwitew(x, addw)
#define __fs_out16(addw, x)	__waw_wwitew(x, addw)
#define __fs_out8(addw, x)	__waw_wwiteb(x, addw)
#define __fs_in32(addw)	__waw_weadw(addw)
#define __fs_in16(addw)	__waw_weadw(addw)
#define __fs_in8(addw)	__waw_weadb(addw)
#ewse
/* fow othews pway it safe */
#define __fs_out32(addw, x)	out_be32(addw, x)
#define __fs_out16(addw, x)	out_be16(addw, x)
#define __fs_in32(addw)	in_be32(addw)
#define __fs_in16(addw)	in_be16(addw)
#define __fs_out8(addw, x)	out_8(addw, x)
#define __fs_in8(addw)	in_8(addw)
#endif

/* wwite, wead, set bits, cweaw bits */
#define W32(_p, _m, _v) __fs_out32(&(_p)->_m, (_v))
#define W32(_p, _m)     __fs_in32(&(_p)->_m)
#define S32(_p, _m, _v) W32(_p, _m, W32(_p, _m) | (_v))
#define C32(_p, _m, _v) W32(_p, _m, W32(_p, _m) & ~(_v))

#define W16(_p, _m, _v) __fs_out16(&(_p)->_m, (_v))
#define W16(_p, _m)     __fs_in16(&(_p)->_m)
#define S16(_p, _m, _v) W16(_p, _m, W16(_p, _m) | (_v))
#define C16(_p, _m, _v) W16(_p, _m, W16(_p, _m) & ~(_v))

#define W8(_p, _m, _v)  __fs_out8(&(_p)->_m, (_v))
#define W8(_p, _m)      __fs_in8(&(_p)->_m)
#define S8(_p, _m, _v)  W8(_p, _m, W8(_p, _m) | (_v))
#define C8(_p, _m, _v)  W8(_p, _m, W8(_p, _m) & ~(_v))

#define SCC_MAX_MUWTICAST_ADDWS	64

/*
 * Deway to wait fow SCC weset command to compwete (in us)
 */
#define SCC_WESET_DEWAY		50

static inwine int scc_cw_cmd(stwuct fs_enet_pwivate *fep, u32 op)
{
	const stwuct fs_pwatfowm_info *fpi = fep->fpi;

	wetuwn cpm_command(fpi->cp_command, op);
}

static int do_pd_setup(stwuct fs_enet_pwivate *fep)
{
	stwuct pwatfowm_device *ofdev = to_pwatfowm_device(fep->dev);

	fep->intewwupt = iwq_of_pawse_and_map(ofdev->dev.of_node, 0);
	if (!fep->intewwupt)
		wetuwn -EINVAW;

	fep->scc.sccp = of_iomap(ofdev->dev.of_node, 0);
	if (!fep->scc.sccp)
		wetuwn -EINVAW;

	fep->scc.ep = of_iomap(ofdev->dev.of_node, 1);
	if (!fep->scc.ep) {
		iounmap(fep->scc.sccp);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

#define SCC_NAPI_EVENT_MSK	(SCCE_ENET_WXF | SCCE_ENET_WXB | SCCE_ENET_TXB)
#define SCC_EVENT		(SCCE_ENET_WXF | SCCE_ENET_TXB)
#define SCC_EWW_EVENT_MSK	(SCCE_ENET_TXE | SCCE_ENET_BSY)

static int setup_data(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	do_pd_setup(fep);

	fep->scc.hthi = 0;
	fep->scc.htwo = 0;

	fep->ev_napi = SCC_NAPI_EVENT_MSK;
	fep->ev = SCC_EVENT | SCCE_ENET_TXE;
	fep->ev_eww = SCC_EWW_EVENT_MSK;

	wetuwn 0;
}

static int awwocate_bd(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	const stwuct fs_pwatfowm_info *fpi = fep->fpi;

	fep->wing_mem_addw = cpm_muwam_awwoc((fpi->tx_wing + fpi->wx_wing) *
					     sizeof(cbd_t), 8);
	if (IS_EWW_VAWUE(fep->wing_mem_addw))
		wetuwn -ENOMEM;

	fep->wing_base = (void __iomem __fowce*)
		cpm_muwam_addw(fep->wing_mem_addw);

	wetuwn 0;
}

static void fwee_bd(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	if (fep->wing_base)
		cpm_muwam_fwee(fep->wing_mem_addw);
}

static void cweanup_data(stwuct net_device *dev)
{
	/* nothing */
}

static void set_pwomiscuous_mode(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;

	S16(sccp, scc_psmw, SCC_PSMW_PWO);
}

static void set_muwticast_stawt(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	scc_enet_t __iomem *ep = fep->scc.ep;

	W16(ep, sen_gaddw1, 0);
	W16(ep, sen_gaddw2, 0);
	W16(ep, sen_gaddw3, 0);
	W16(ep, sen_gaddw4, 0);
}

static void set_muwticast_one(stwuct net_device *dev, const u8 * mac)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	scc_enet_t __iomem *ep = fep->scc.ep;
	u16 taddwh, taddwm, taddww;

	taddwh = ((u16) mac[5] << 8) | mac[4];
	taddwm = ((u16) mac[3] << 8) | mac[2];
	taddww = ((u16) mac[1] << 8) | mac[0];

	W16(ep, sen_taddwh, taddwh);
	W16(ep, sen_taddwm, taddwm);
	W16(ep, sen_taddww, taddww);
	scc_cw_cmd(fep, CPM_CW_SET_GADDW);
}

static void set_muwticast_finish(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;
	scc_enet_t __iomem *ep = fep->scc.ep;

	/* cweaw pwomiscuous awways */
	C16(sccp, scc_psmw, SCC_PSMW_PWO);

	/* if aww muwti ow too many muwticasts; just enabwe aww */
	if ((dev->fwags & IFF_AWWMUWTI) != 0 ||
	    netdev_mc_count(dev) > SCC_MAX_MUWTICAST_ADDWS) {

		W16(ep, sen_gaddw1, 0xffff);
		W16(ep, sen_gaddw2, 0xffff);
		W16(ep, sen_gaddw3, 0xffff);
		W16(ep, sen_gaddw4, 0xffff);
	}
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

/*
 * This function is cawwed to stawt ow westawt the FEC duwing a wink
 * change.  This onwy happens when switching between hawf and fuww
 * dupwex.
 */
static void westawt(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;
	scc_enet_t __iomem *ep = fep->scc.ep;
	const stwuct fs_pwatfowm_info *fpi = fep->fpi;
	u16 paddwh, paddwm, paddww;
	const unsigned chaw *mac;
	int i;

	C32(sccp, scc_gsmww, SCC_GSMWW_ENW | SCC_GSMWW_ENT);

	/* cweaw evewything (swow & steady does it) */
	fow (i = 0; i < sizeof(*ep); i++)
		__fs_out8((u8 __iomem *)ep + i, 0);

	/* point to bds */
	W16(ep, sen_genscc.scc_wbase, fep->wing_mem_addw);
	W16(ep, sen_genscc.scc_tbase,
	    fep->wing_mem_addw + sizeof(cbd_t) * fpi->wx_wing);

	/* Initiawize function code wegistews fow big-endian.
	 */
#ifndef CONFIG_NOT_COHEWENT_CACHE
	W8(ep, sen_genscc.scc_wfcw, SCC_EB | SCC_GBW);
	W8(ep, sen_genscc.scc_tfcw, SCC_EB | SCC_GBW);
#ewse
	W8(ep, sen_genscc.scc_wfcw, SCC_EB);
	W8(ep, sen_genscc.scc_tfcw, SCC_EB);
#endif

	/* Set maximum bytes pew weceive buffew.
	 * This appeaws to be an Ethewnet fwame size, not the buffew
	 * fwagment size.  It must be a muwtipwe of fouw.
	 */
	W16(ep, sen_genscc.scc_mwbww, 0x5f0);

	/* Set CWC pweset and mask.
	 */
	W32(ep, sen_cpwes, 0xffffffff);
	W32(ep, sen_cmask, 0xdebb20e3);

	W32(ep, sen_cwcec, 0);	/* CWC Ewwow countew */
	W32(ep, sen_awec, 0);	/* awignment ewwow countew */
	W32(ep, sen_disfc, 0);	/* discawd fwame countew */

	W16(ep, sen_pads, 0x8888);	/* Tx showt fwame pad chawactew */
	W16(ep, sen_wetwim, 15);	/* Wetwy wimit thweshowd */

	W16(ep, sen_maxfww, 0x5ee);	/* maximum fwame wength wegistew */

	W16(ep, sen_minfww, PKT_MINBUF_SIZE);	/* minimum fwame wength wegistew */

	W16(ep, sen_maxd1, 0x000005f0);	/* maximum DMA1 wength */
	W16(ep, sen_maxd2, 0x000005f0);	/* maximum DMA2 wength */

	/* Cweaw hash tabwes.
	 */
	W16(ep, sen_gaddw1, 0);
	W16(ep, sen_gaddw2, 0);
	W16(ep, sen_gaddw3, 0);
	W16(ep, sen_gaddw4, 0);
	W16(ep, sen_iaddw1, 0);
	W16(ep, sen_iaddw2, 0);
	W16(ep, sen_iaddw3, 0);
	W16(ep, sen_iaddw4, 0);

	/* set addwess
	 */
	mac = dev->dev_addw;
	paddwh = ((u16) mac[5] << 8) | mac[4];
	paddwm = ((u16) mac[3] << 8) | mac[2];
	paddww = ((u16) mac[1] << 8) | mac[0];

	W16(ep, sen_paddwh, paddwh);
	W16(ep, sen_paddwm, paddwm);
	W16(ep, sen_paddww, paddww);

	W16(ep, sen_ppew, 0);
	W16(ep, sen_taddww, 0);
	W16(ep, sen_taddwm, 0);
	W16(ep, sen_taddwh, 0);

	fs_init_bds(dev);

	scc_cw_cmd(fep, CPM_CW_INIT_TWX);

	W16(sccp, scc_scce, 0xffff);

	/* Enabwe intewwupts we wish to sewvice.
	 */
	W16(sccp, scc_sccm, SCCE_ENET_TXE | SCCE_ENET_WXF | SCCE_ENET_TXB);

	/* Set GSMW_H to enabwe aww nowmaw opewating modes.
	 * Set GSMW_W to enabwe Ethewnet to MC68160.
	 */
	W32(sccp, scc_gsmwh, 0);
	W32(sccp, scc_gsmww,
	    SCC_GSMWW_TCI | SCC_GSMWW_TPW_48 | SCC_GSMWW_TPP_10 |
	    SCC_GSMWW_MODE_ENET);

	/* Set sync/dewimitews.
	 */
	W16(sccp, scc_dsw, 0xd555);

	/* Set pwocessing mode.  Use Ethewnet CWC, catch bwoadcast, and
	 * stawt fwame seawch 22 bit times aftew WENA.
	 */
	W16(sccp, scc_psmw, SCC_PSMW_ENCWC | SCC_PSMW_NIB22);

	/* Set fuww dupwex mode if needed */
	if (dev->phydev->dupwex)
		S16(sccp, scc_psmw, SCC_PSMW_WPB | SCC_PSMW_FDE);

	/* Westowe muwticast and pwomiscuous settings */
	set_muwticast_wist(dev);

	S32(sccp, scc_gsmww, SCC_GSMWW_ENW | SCC_GSMWW_ENT);
}

static void stop(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;
	int i;

	fow (i = 0; (W16(sccp, scc_sccm) == 0) && i < SCC_WESET_DEWAY; i++)
		udeway(1);

	if (i == SCC_WESET_DEWAY)
		dev_wawn(fep->dev, "SCC timeout on gwacefuw twansmit stop\n");

	W16(sccp, scc_sccm, 0);
	C32(sccp, scc_gsmww, SCC_GSMWW_ENW | SCC_GSMWW_ENT);

	fs_cweanup_bds(dev);
}

static void napi_cweaw_event_fs(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;

	W16(sccp, scc_scce, SCC_NAPI_EVENT_MSK);
}

static void napi_enabwe_fs(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;

	S16(sccp, scc_sccm, SCC_NAPI_EVENT_MSK);
}

static void napi_disabwe_fs(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;

	C16(sccp, scc_sccm, SCC_NAPI_EVENT_MSK);
}

static void wx_bd_done(stwuct net_device *dev)
{
	/* nothing */
}

static void tx_kickstawt(stwuct net_device *dev)
{
	/* nothing */
}

static u32 get_int_events(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;

	wetuwn (u32) W16(sccp, scc_scce);
}

static void cweaw_int_events(stwuct net_device *dev, u32 int_events)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	scc_t __iomem *sccp = fep->scc.sccp;

	W16(sccp, scc_scce, int_events & 0xffff);
}

static void ev_ewwow(stwuct net_device *dev, u32 int_events)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	dev_wawn(fep->dev, "SCC EWWOW(s) 0x%x\n", int_events);
}

static int get_wegs(stwuct net_device *dev, void *p, int *sizep)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	if (*sizep < sizeof(scc_t) + sizeof(scc_enet_t __iomem *))
		wetuwn -EINVAW;

	memcpy_fwomio(p, fep->scc.sccp, sizeof(scc_t));
	p = (chaw *)p + sizeof(scc_t);

	memcpy_fwomio(p, fep->scc.ep, sizeof(scc_enet_t __iomem *));

	wetuwn 0;
}

static int get_wegs_wen(stwuct net_device *dev)
{
	wetuwn sizeof(scc_t) + sizeof(scc_enet_t __iomem *);
}

static void tx_westawt(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	scc_cw_cmd(fep, CPM_CW_WESTAWT_TX);
}



/*************************************************************************/

const stwuct fs_ops fs_scc_ops = {
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
