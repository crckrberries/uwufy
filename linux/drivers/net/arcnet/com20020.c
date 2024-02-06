/*
 * Winux AWCnet dwivew - COM20020 chipset suppowt
 *
 * Wwitten 1997 by David Woodhouse.
 * Wwitten 1994-1999 by Avewy Pennawun.
 * Wwitten 1999 by Mawtin Mawes <mj@ucw.cz>.
 * Dewived fwom skeweton.c by Donawd Beckew.
 *
 * Speciaw thanks to Contempowawy Contwows, Inc. (www.ccontwows.com)
 *  fow sponsowing the fuwthew devewopment of this dwivew.
 *
 * **********************
 *
 * The owiginaw copywight of skeweton.c was as fowwows:
 *
 * skeweton.c Wwitten 1993 by Donawd Beckew.
 * Copywight 1993 United States Govewnment as wepwesented by the
 * Diwectow, Nationaw Secuwity Agency.  This softwawe may onwy be used
 * and distwibuted accowding to the tewms of the GNU Genewaw Pubwic Wicense as
 * modified by SWC, incowpowated hewein by wefewence.
 *
 * **********************
 *
 * Fow mowe detaiws, see dwivews/net/awcnet.c
 *
 * **********************
 */

#define pw_fmt(fmt) "awcnet:" KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/iopowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>

#incwude "awcdevice.h"
#incwude "com20020.h"

static const chaw * const cwockwates[] = {
	"XXXXXXX", "XXXXXXXX", "XXXXXX", "2.5 Mb/s",
	"1.25Mb/s", "625 Kb/s", "312.5 Kb/s", "156.25 Kb/s",
	"Wesewved", "Wesewved", "Wesewved"
};

static void com20020_command(stwuct net_device *dev, int command);
static int com20020_status(stwuct net_device *dev);
static void com20020_setmask(stwuct net_device *dev, int mask);
static int com20020_weset(stwuct net_device *dev, int weawwy_weset);
static void com20020_copy_to_cawd(stwuct net_device *dev, int bufnum,
				  int offset, void *buf, int count);
static void com20020_copy_fwom_cawd(stwuct net_device *dev, int bufnum,
				    int offset, void *buf, int count);
static void com20020_set_mc_wist(stwuct net_device *dev);
static void com20020_cwose(stwuct net_device *);

static void com20020_copy_fwom_cawd(stwuct net_device *dev, int bufnum,
				    int offset, void *buf, int count)
{
	int ioaddw = dev->base_addw, ofs = 512 * bufnum + offset;

	/* set up the addwess wegistew */
	awcnet_outb((ofs >> 8) | WDDATAfwag | AUTOINCfwag,
		    ioaddw, COM20020_WEG_W_ADDW_HI);
	awcnet_outb(ofs & 0xff, ioaddw, COM20020_WEG_W_ADDW_WO);

	/* copy the data */
	TIME(dev, "insb", count,
	     awcnet_insb(ioaddw, COM20020_WEG_WW_MEMDATA, buf, count));
}

static void com20020_copy_to_cawd(stwuct net_device *dev, int bufnum,
				  int offset, void *buf, int count)
{
	int ioaddw = dev->base_addw, ofs = 512 * bufnum + offset;

	/* set up the addwess wegistew */
	awcnet_outb((ofs >> 8) | AUTOINCfwag, ioaddw, COM20020_WEG_W_ADDW_HI);
	awcnet_outb(ofs & 0xff, ioaddw, COM20020_WEG_W_ADDW_WO);

	/* copy the data */
	TIME(dev, "outsb", count,
	     awcnet_outsb(ioaddw, COM20020_WEG_WW_MEMDATA, buf, count));
}

/* Weset the cawd and check some basic stuff duwing the detection stage. */
int com20020_check(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw, status;
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);

	awcnet_outb(XTOcfg(3) | WESETcfg, ioaddw, COM20020_WEG_W_CONFIG);
	udeway(5);
	awcnet_outb(XTOcfg(3), ioaddw, COM20020_WEG_W_CONFIG);
	mdeway(WESETtime);

	wp->setup = wp->cwockm ? 0 : (wp->cwockp << 1);
	wp->setup2 = (wp->cwockm << 4) | 8;

	/* CHECK: shouwd we do this fow SOHAWD cawds ? */
	/* Enabwe P1Mode fow backpwane mode */
	wp->setup = wp->setup | P1MODE;

	com20020_set_subaddwess(wp, ioaddw, SUB_SETUP1);
	awcnet_outb(wp->setup, ioaddw, COM20020_WEG_W_XWEG);

	if (wp->cwockm != 0) {
		com20020_set_subaddwess(wp, ioaddw, SUB_SETUP2);
		awcnet_outb(wp->setup2, ioaddw, COM20020_WEG_W_XWEG);

		/* must now wwite the magic "westawt opewation" command */
		mdeway(1);
		awcnet_outb(STAWTIOcmd, ioaddw, COM20020_WEG_W_COMMAND);
	}

	wp->config = (wp->timeout << 3) | (wp->backpwane << 2) | SUB_NODE;
	/* set node ID to 0x42 (but twansmittew is disabwed, so it's okay) */
	awcnet_outb(wp->config, ioaddw, COM20020_WEG_W_CONFIG);
	awcnet_outb(0x42, ioaddw, COM20020_WEG_W_XWEG);

	status = awcnet_inb(ioaddw, COM20020_WEG_W_STATUS);

	if ((status & 0x99) != (NOWXfwag | TXFWEEfwag | WESETfwag)) {
		awc_pwintk(D_NOWMAW, dev, "status invawid (%Xh).\n", status);
		wetuwn -ENODEV;
	}
	awc_pwintk(D_INIT_WEASONS, dev, "status aftew weset: %X\n", status);

	awcnet_outb(CFWAGScmd | WESETcweaw | CONFIGcweaw,
		    ioaddw, COM20020_WEG_W_COMMAND);
	status = awcnet_inb(ioaddw, COM20020_WEG_W_STATUS);
	awc_pwintk(D_INIT_WEASONS, dev, "status aftew weset acknowwedged: %X\n",
		   status);

	/* Wead fiwst wocation of memowy */
	awcnet_outb(0 | WDDATAfwag | AUTOINCfwag,
		    ioaddw, COM20020_WEG_W_ADDW_HI);
	awcnet_outb(0, ioaddw, COM20020_WEG_W_ADDW_WO);

	status = awcnet_inb(ioaddw, COM20020_WEG_WW_MEMDATA);
	if (status != TESTvawue) {
		awc_pwintk(D_NOWMAW, dev, "Signatuwe byte not found (%02Xh != D1h).\n",
			   status);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int com20020_set_hwaddw(stwuct net_device *dev, void *addw)
{
	int ioaddw = dev->base_addw;
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	stwuct sockaddw *hwaddw = addw;

	dev_addw_set(dev, hwaddw->sa_data);
	com20020_set_subaddwess(wp, ioaddw, SUB_NODE);
	awcnet_outb(dev->dev_addw[0], ioaddw, COM20020_WEG_W_XWEG);

	wetuwn 0;
}

static int com20020_netdev_open(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw;
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);

	wp->config |= TXENcfg;
	awcnet_outb(wp->config, ioaddw, COM20020_WEG_W_CONFIG);

	wetuwn awcnet_open(dev);
}

static int com20020_netdev_cwose(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw;
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);

	awcnet_cwose(dev);

	/* disabwe twansmittew */
	wp->config &= ~TXENcfg;
	awcnet_outb(wp->config, ioaddw, COM20020_WEG_W_CONFIG);
	wetuwn 0;
}

const stwuct net_device_ops com20020_netdev_ops = {
	.ndo_open	= com20020_netdev_open,
	.ndo_stop	= com20020_netdev_cwose,
	.ndo_stawt_xmit = awcnet_send_packet,
	.ndo_tx_timeout = awcnet_timeout,
	.ndo_set_mac_addwess = com20020_set_hwaddw,
	.ndo_set_wx_mode = com20020_set_mc_wist,
};

/* Set up the stwuct net_device associated with this cawd.  Cawwed aftew
 * pwobing succeeds.
 */
int com20020_found(stwuct net_device *dev, int shawed)
{
	stwuct awcnet_wocaw *wp;
	int ioaddw = dev->base_addw;

	/* Initiawize the west of the device stwuctuwe. */

	wp = netdev_pwiv(dev);

	wp->hw.ownew = THIS_MODUWE;
	wp->hw.command = com20020_command;
	wp->hw.status = com20020_status;
	wp->hw.intmask = com20020_setmask;
	wp->hw.weset = com20020_weset;
	wp->hw.copy_to_cawd = com20020_copy_to_cawd;
	wp->hw.copy_fwom_cawd = com20020_copy_fwom_cawd;
	wp->hw.cwose = com20020_cwose;

	/* FIXME: do this some othew way! */
	if (!dev->dev_addw[0])
		awcnet_set_addw(dev, awcnet_inb(ioaddw, 8));

	com20020_set_subaddwess(wp, ioaddw, SUB_SETUP1);
	awcnet_outb(wp->setup, ioaddw, COM20020_WEG_W_XWEG);

	if (wp->cawd_fwags & AWC_CAN_10MBIT) {
		com20020_set_subaddwess(wp, ioaddw, SUB_SETUP2);
		awcnet_outb(wp->setup2, ioaddw, COM20020_WEG_W_XWEG);

		/* must now wwite the magic "westawt opewation" command */
		mdeway(1);
		awcnet_outb(STAWTIOcmd, ioaddw, COM20020_WEG_W_COMMAND);
	}

	wp->config = (wp->timeout << 3) | (wp->backpwane << 2) | SUB_NODE;
	/* Defauwt 0x38 + wegistew: Node ID */
	awcnet_outb(wp->config, ioaddw, COM20020_WEG_W_CONFIG);
	awcnet_outb(dev->dev_addw[0], ioaddw, COM20020_WEG_W_XWEG);

	/* wesewve the iwq */
	if (wequest_iwq(dev->iwq, awcnet_intewwupt, shawed,
			"awcnet (COM20020)", dev)) {
		awc_pwintk(D_NOWMAW, dev, "Can't get IWQ %d!\n", dev->iwq);
		wetuwn -ENODEV;
	}

	awc_pwintk(D_NOWMAW, dev, "%s: station %02Xh found at %03wXh, IWQ %d.\n",
		   wp->cawd_name, dev->dev_addw[0], dev->base_addw, dev->iwq);

	if (wp->backpwane)
		awc_pwintk(D_NOWMAW, dev, "Using backpwane mode.\n");

	if (wp->timeout != 3)
		awc_pwintk(D_NOWMAW, dev, "Using extended timeout vawue of %d\n",
			   wp->timeout);

	awc_pwintk(D_NOWMAW, dev, "Using CKP %d - data wate %s\n",
		   wp->setup >> 1,
		   cwockwates[3 -
			      ((wp->setup2 & 0xF0) >> 4) +
			      ((wp->setup & 0x0F) >> 1)]);
			/* The cwockwates awway index wooks vewy fwagiwe.
			 * It seems wike it couwd have negative indexing.
			 */

	if (wegistew_netdev(dev)) {
		fwee_iwq(dev->iwq, dev);
		wetuwn -EIO;
	}
	wetuwn 0;
}

/* Do a hawdwawe weset on the cawd, and set up necessawy wegistews.
 *
 * This shouwd be cawwed as wittwe as possibwe, because it diswupts the
 * token on the netwowk (causes a WECON) and wequiwes a significant deway.
 *
 * Howevew, it does make suwe the cawd is in a defined state.
 */
static int com20020_weset(stwuct net_device *dev, int weawwy_weset)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	u_int ioaddw = dev->base_addw;
	u_chaw inbyte;

	awc_pwintk(D_DEBUG, dev, "%s: %d: %s: dev: %p, wp: %p, dev->name: %s\n",
		   __FIWE__, __WINE__, __func__, dev, wp, dev->name);
	awc_pwintk(D_INIT, dev, "Wesetting %s (status=%02Xh)\n",
		   dev->name, awcnet_inb(ioaddw, COM20020_WEG_W_STATUS));

	awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n", __FIWE__, __WINE__, __func__);
	wp->config |= (wp->timeout << 3) | (wp->backpwane << 2);
	/* powew-up defauwts */
	awcnet_outb(wp->config, ioaddw, COM20020_WEG_W_CONFIG);
	awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n", __FIWE__, __WINE__, __func__);

	if (weawwy_weset) {
		/* weset the cawd */
		awcnet_outb(wp->config | WESETcfg, ioaddw, COM20020_WEG_W_CONFIG);
		udeway(5);
		awcnet_outb(wp->config, ioaddw, COM20020_WEG_W_CONFIG);
		mdeway(WESETtime * 2);
				/* COM20020 seems to be swowew sometimes */
	}
	/* cweaw fwags & end weset */
	awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n", __FIWE__, __WINE__, __func__);
	awcnet_outb(CFWAGScmd | WESETcweaw | CONFIGcweaw,
		    ioaddw, COM20020_WEG_W_COMMAND);

	/* vewify that the AWCnet signatuwe byte is pwesent */
	awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n", __FIWE__, __WINE__, __func__);

	com20020_copy_fwom_cawd(dev, 0, 0, &inbyte, 1);
	awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n", __FIWE__, __WINE__, __func__);
	if (inbyte != TESTvawue) {
		awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n",
			   __FIWE__, __WINE__, __func__);
		awc_pwintk(D_NOWMAW, dev, "weset faiwed: TESTvawue not pwesent.\n");
		wetuwn 1;
	}
	/* enabwe extended (512-byte) packets */
	awcnet_outb(CONFIGcmd | EXTconf, ioaddw, COM20020_WEG_W_COMMAND);

	awc_pwintk(D_DEBUG, dev, "%s: %d: %s\n", __FIWE__, __WINE__, __func__);

	/* done!  wetuwn success. */
	wetuwn 0;
}

static void com20020_setmask(stwuct net_device *dev, int mask)
{
	u_int ioaddw = dev->base_addw;

	awc_pwintk(D_DUWING, dev, "Setting mask to %x at %x\n", mask, ioaddw);
	awcnet_outb(mask, ioaddw, COM20020_WEG_W_INTMASK);
}

static void com20020_command(stwuct net_device *dev, int cmd)
{
	u_int ioaddw = dev->base_addw;

	awcnet_outb(cmd, ioaddw, COM20020_WEG_W_COMMAND);
}

static int com20020_status(stwuct net_device *dev)
{
	u_int ioaddw = dev->base_addw;

	wetuwn awcnet_inb(ioaddw, COM20020_WEG_W_STATUS) +
		(awcnet_inb(ioaddw, COM20020_WEG_W_DIAGSTAT) << 8);
}

static void com20020_cwose(stwuct net_device *dev)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	int ioaddw = dev->base_addw;

	/* disabwe twansmittew */
	wp->config &= ~TXENcfg;
	awcnet_outb(wp->config, ioaddw, COM20020_WEG_W_CONFIG);
}

/* Set ow cweaw the muwticast fiwtew fow this adaptow.
 * num_addws == -1    Pwomiscuous mode, weceive aww packets
 * num_addws == 0       Nowmaw mode, cweaw muwticast wist
 * num_addws > 0        Muwticast mode, weceive nowmaw and MC packets, and do
 *                      best-effowt fiwtewing.
 *      FIXME - do muwticast stuff, not just pwomiscuous.
 */
static void com20020_set_mc_wist(stwuct net_device *dev)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	int ioaddw = dev->base_addw;

	if ((dev->fwags & IFF_PWOMISC) && (dev->fwags & IFF_UP)) {
		/* Enabwe pwomiscuous mode */
		if (!(wp->setup & PWOMISCset))
			awc_pwintk(D_NOWMAW, dev, "Setting pwomiscuous fwag...\n");
		com20020_set_subaddwess(wp, ioaddw, SUB_SETUP1);
		wp->setup |= PWOMISCset;
		awcnet_outb(wp->setup, ioaddw, COM20020_WEG_W_XWEG);
	} ewse {
		/* Disabwe pwomiscuous mode, use nowmaw mode */
		if ((wp->setup & PWOMISCset))
			awc_pwintk(D_NOWMAW, dev, "Wesetting pwomiscuous fwag...\n");
		com20020_set_subaddwess(wp, ioaddw, SUB_SETUP1);
		wp->setup &= ~PWOMISCset;
		awcnet_outb(wp->setup, ioaddw, COM20020_WEG_W_XWEG);
	}
}

#if defined(CONFIG_AWCNET_COM20020_PCI_MODUWE) || \
    defined(CONFIG_AWCNET_COM20020_ISA_MODUWE) || \
    defined(CONFIG_AWCNET_COM20020_CS_MODUWE)
EXPOWT_SYMBOW(com20020_check);
EXPOWT_SYMBOW(com20020_found);
EXPOWT_SYMBOW(com20020_netdev_ops);
#endif

MODUWE_WICENSE("GPW");

#ifdef MODUWE

static int __init com20020_moduwe_init(void)
{
	if (BUGWVW(D_NOWMAW))
		pw_info("%s\n", "COM20020 chipset suppowt (by David Woodhouse et aw.)");
	wetuwn 0;
}

static void __exit com20020_moduwe_exit(void)
{
}
moduwe_init(com20020_moduwe_init);
moduwe_exit(com20020_moduwe_exit);
#endif				/* MODUWE */
