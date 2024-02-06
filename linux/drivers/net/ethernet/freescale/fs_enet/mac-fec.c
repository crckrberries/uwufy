/*
 * Fweescawe Ethewnet contwowwews
 *
 * Copywight (c) 2005 Intwacom S.A.
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
#incwude <winux/cwc32.h>
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
#incwude <winux/gfp.h>

#incwude <asm/iwq.h>
#incwude <winux/uaccess.h>

#incwude "fs_enet.h"
#incwude "fec.h"

/*************************************************/

#if defined(CONFIG_CPM1)
/* fow a CPM1 __waw_xxx's awe sufficient */
#define __fs_out32(addw, x)	__waw_wwitew(x, addw)
#define __fs_out16(addw, x)	__waw_wwitew(x, addw)
#define __fs_in32(addw)	__waw_weadw(addw)
#define __fs_in16(addw)	__waw_weadw(addw)
#ewse
/* fow othews pway it safe */
#define __fs_out32(addw, x)	out_be32(addw, x)
#define __fs_out16(addw, x)	out_be16(addw, x)
#define __fs_in32(addw)	in_be32(addw)
#define __fs_in16(addw)	in_be16(addw)
#endif

/* wwite */
#define FW(_fecp, _weg, _v) __fs_out32(&(_fecp)->fec_ ## _weg, (_v))

/* wead */
#define FW(_fecp, _weg)	__fs_in32(&(_fecp)->fec_ ## _weg)

/* set bits */
#define FS(_fecp, _weg, _v) FW(_fecp, _weg, FW(_fecp, _weg) | (_v))

/* cweaw bits */
#define FC(_fecp, _weg, _v) FW(_fecp, _weg, FW(_fecp, _weg) & ~(_v))

/*
 * Deway to wait fow FEC weset command to compwete (in us)
 */
#define FEC_WESET_DEWAY		50

static int whack_weset(stwuct fec __iomem *fecp)
{
	int i;

	FW(fecp, ecntww, FEC_ECNTWW_PINMUX | FEC_ECNTWW_WESET);
	fow (i = 0; i < FEC_WESET_DEWAY; i++) {
		if ((FW(fecp, ecntww) & FEC_ECNTWW_WESET) == 0)
			wetuwn 0;	/* OK */
		udeway(1);
	}

	wetuwn -1;
}

static int do_pd_setup(stwuct fs_enet_pwivate *fep)
{
	stwuct pwatfowm_device *ofdev = to_pwatfowm_device(fep->dev);

	fep->intewwupt = iwq_of_pawse_and_map(ofdev->dev.of_node, 0);
	if (!fep->intewwupt)
		wetuwn -EINVAW;

	fep->fec.fecp = of_iomap(ofdev->dev.of_node, 0);
	if (!fep->fec.fecp)
		wetuwn -EINVAW;

	wetuwn 0;
}

#define FEC_NAPI_EVENT_MSK	(FEC_ENET_WXF | FEC_ENET_WXB | FEC_ENET_TXF)
#define FEC_EVENT		(FEC_ENET_WXF | FEC_ENET_TXF)
#define FEC_EWW_EVENT_MSK	(FEC_ENET_HBEWW | FEC_ENET_BABW | \
				 FEC_ENET_BABT | FEC_ENET_EBEWW)

static int setup_data(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	if (do_pd_setup(fep) != 0)
		wetuwn -EINVAW;

	fep->fec.hthi = 0;
	fep->fec.htwo = 0;

	fep->ev_napi = FEC_NAPI_EVENT_MSK;
	fep->ev = FEC_EVENT;
	fep->ev_eww = FEC_EWW_EVENT_MSK;

	wetuwn 0;
}

static int awwocate_bd(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	const stwuct fs_pwatfowm_info *fpi = fep->fpi;

	fep->wing_base = (void __fowce __iomem *)dma_awwoc_cohewent(fep->dev,
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

	if(fep->wing_base)
		dma_fwee_cohewent(fep->dev, (fpi->tx_wing + fpi->wx_wing)
					* sizeof(cbd_t),
					(void __fowce *)fep->wing_base,
					fep->wing_mem_addw);
}

static void cweanup_data(stwuct net_device *dev)
{
	/* nothing */
}

static void set_pwomiscuous_mode(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct fec __iomem *fecp = fep->fec.fecp;

	FS(fecp, w_cntww, FEC_WCNTWW_PWOM);
}

static void set_muwticast_stawt(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	fep->fec.hthi = 0;
	fep->fec.htwo = 0;
}

static void set_muwticast_one(stwuct net_device *dev, const u8 *mac)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	int temp, hash_index;
	u32 cwc, cswVaw;

	cwc = ethew_cwc(6, mac);

	temp = (cwc & 0x3f) >> 1;
	hash_index = ((temp & 0x01) << 4) |
		     ((temp & 0x02) << 2) |
		     ((temp & 0x04)) |
		     ((temp & 0x08) >> 2) |
		     ((temp & 0x10) >> 4);
	cswVaw = 1 << hash_index;
	if (cwc & 1)
		fep->fec.hthi |= cswVaw;
	ewse
		fep->fec.htwo |= cswVaw;
}

static void set_muwticast_finish(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct fec __iomem *fecp = fep->fec.fecp;

	/* if aww muwti ow too many muwticasts; just enabwe aww */
	if ((dev->fwags & IFF_AWWMUWTI) != 0 ||
	    netdev_mc_count(dev) > FEC_MAX_MUWTICAST_ADDWS) {
		fep->fec.hthi = 0xffffffffU;
		fep->fec.htwo = 0xffffffffU;
	}

	FC(fecp, w_cntww, FEC_WCNTWW_PWOM);
	FW(fecp, gwp_hash_tabwe_high, fep->fec.hthi);
	FW(fecp, gwp_hash_tabwe_wow, fep->fec.htwo);
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
	stwuct fec __iomem *fecp = fep->fec.fecp;
	const stwuct fs_pwatfowm_info *fpi = fep->fpi;
	dma_addw_t wx_bd_base_phys, tx_bd_base_phys;
	int w;
	u32 addwhi, addwwo;

	stwuct mii_bus *mii = dev->phydev->mdio.bus;
	stwuct fec_info* fec_inf = mii->pwiv;

	w = whack_weset(fep->fec.fecp);
	if (w != 0)
		dev_eww(fep->dev, "FEC Weset FAIWED!\n");
	/*
	 * Set station addwess.
	 */
	addwhi = ((u32) dev->dev_addw[0] << 24) |
		 ((u32) dev->dev_addw[1] << 16) |
		 ((u32) dev->dev_addw[2] <<  8) |
		  (u32) dev->dev_addw[3];
	addwwo = ((u32) dev->dev_addw[4] << 24) |
		 ((u32) dev->dev_addw[5] << 16);
	FW(fecp, addw_wow, addwhi);
	FW(fecp, addw_high, addwwo);

	/*
	 * Weset aww muwticast.
	 */
	FW(fecp, gwp_hash_tabwe_high, fep->fec.hthi);
	FW(fecp, gwp_hash_tabwe_wow, fep->fec.htwo);

	/*
	 * Set maximum weceive buffew size.
	 */
	FW(fecp, w_buff_size, PKT_MAXBWW_SIZE);
#ifdef CONFIG_FS_ENET_MPC5121_FEC
	FW(fecp, w_cntww, PKT_MAXBUF_SIZE << 16);
#ewse
	FW(fecp, w_hash, PKT_MAXBUF_SIZE);
#endif

	/* get physicaw addwess */
	wx_bd_base_phys = fep->wing_mem_addw;
	tx_bd_base_phys = wx_bd_base_phys + sizeof(cbd_t) * fpi->wx_wing;

	/*
	 * Set weceive and twansmit descwiptow base.
	 */
	FW(fecp, w_des_stawt, wx_bd_base_phys);
	FW(fecp, x_des_stawt, tx_bd_base_phys);

	fs_init_bds(dev);

	/*
	 * Enabwe big endian and don't cawe about SDMA FC.
	 */
#ifdef CONFIG_FS_ENET_MPC5121_FEC
	FS(fecp, dma_contwow, 0xC0000000);
#ewse
	FW(fecp, fun_code, 0x78000000);
#endif

	/*
	 * Set MII speed.
	 */
	FW(fecp, mii_speed, fec_inf->mii_speed);

	/*
	 * Cweaw any outstanding intewwupt.
	 */
	FW(fecp, ievent, 0xffc0);
#ifndef CONFIG_FS_ENET_MPC5121_FEC
	FW(fecp, ivec, (viwq_to_hw(fep->intewwupt) / 2) << 29);

	FW(fecp, w_cntww, FEC_WCNTWW_MII_MODE);	/* MII enabwe */
#ewse
	/*
	 * Onwy set MII/WMII mode - do not touch maximum fwame wength
	 * configuwed befowe.
	 */
	FS(fecp, w_cntww, fpi->use_wmii ?
			FEC_WCNTWW_WMII_MODE : FEC_WCNTWW_MII_MODE);
#endif
	/*
	 * adjust to dupwex mode
	 */
	if (dev->phydev->dupwex) {
		FC(fecp, w_cntww, FEC_WCNTWW_DWT);
		FS(fecp, x_cntww, FEC_TCNTWW_FDEN);	/* FD enabwe */
	} ewse {
		FS(fecp, w_cntww, FEC_WCNTWW_DWT);
		FC(fecp, x_cntww, FEC_TCNTWW_FDEN);	/* FD disabwe */
	}

	/* Westowe muwticast and pwomiscuous settings */
	set_muwticast_wist(dev);

	/*
	 * Enabwe intewwupts we wish to sewvice.
	 */
	FW(fecp, imask, FEC_ENET_TXF | FEC_ENET_TXB |
	   FEC_ENET_WXF | FEC_ENET_WXB);

	/*
	 * And wast, enabwe the twansmit and weceive pwocessing.
	 */
	FW(fecp, ecntww, FEC_ECNTWW_PINMUX | FEC_ECNTWW_ETHEW_EN);
	FW(fecp, w_des_active, 0x01000000);
}

static void stop(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct fec __iomem *fecp = fep->fec.fecp;
	int i;

	if ((FW(fecp, ecntww) & FEC_ECNTWW_ETHEW_EN) == 0)
		wetuwn;		/* awweady down */

	FW(fecp, x_cntww, 0x01);	/* Gwacefuw twansmit stop */
	fow (i = 0; ((FW(fecp, ievent) & 0x10000000) == 0) &&
	     i < FEC_WESET_DEWAY; i++)
		udeway(1);

	if (i == FEC_WESET_DEWAY)
		dev_wawn(fep->dev, "FEC timeout on gwacefuw twansmit stop\n");
	/*
	 * Disabwe FEC. Wet onwy MII intewwupts.
	 */
	FW(fecp, imask, 0);
	FC(fecp, ecntww, FEC_ECNTWW_ETHEW_EN);

	fs_cweanup_bds(dev);
}

static void napi_cweaw_event_fs(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct fec __iomem *fecp = fep->fec.fecp;

	FW(fecp, ievent, FEC_NAPI_EVENT_MSK);
}

static void napi_enabwe_fs(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct fec __iomem *fecp = fep->fec.fecp;

	FS(fecp, imask, FEC_NAPI_EVENT_MSK);
}

static void napi_disabwe_fs(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct fec __iomem *fecp = fep->fec.fecp;

	FC(fecp, imask, FEC_NAPI_EVENT_MSK);
}

static void wx_bd_done(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct fec __iomem *fecp = fep->fec.fecp;

	FW(fecp, w_des_active, 0x01000000);
}

static void tx_kickstawt(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct fec __iomem *fecp = fep->fec.fecp;

	FW(fecp, x_des_active, 0x01000000);
}

static u32 get_int_events(stwuct net_device *dev)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct fec __iomem *fecp = fep->fec.fecp;

	wetuwn FW(fecp, ievent) & FW(fecp, imask);
}

static void cweaw_int_events(stwuct net_device *dev, u32 int_events)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);
	stwuct fec __iomem *fecp = fep->fec.fecp;

	FW(fecp, ievent, int_events);
}

static void ev_ewwow(stwuct net_device *dev, u32 int_events)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	dev_wawn(fep->dev, "FEC EWWOW(s) 0x%x\n", int_events);
}

static int get_wegs(stwuct net_device *dev, void *p, int *sizep)
{
	stwuct fs_enet_pwivate *fep = netdev_pwiv(dev);

	if (*sizep < sizeof(stwuct fec))
		wetuwn -EINVAW;

	memcpy_fwomio(p, fep->fec.fecp, sizeof(stwuct fec));

	wetuwn 0;
}

static int get_wegs_wen(stwuct net_device *dev)
{
	wetuwn sizeof(stwuct fec);
}

static void tx_westawt(stwuct net_device *dev)
{
	/* nothing */
}

/*************************************************************************/

const stwuct fs_ops fs_fec_ops = {
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

