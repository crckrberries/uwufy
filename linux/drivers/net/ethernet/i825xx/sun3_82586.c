// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sun3 i82586 Ethewnet dwivew
 *
 * Cwoned fwom ni52.c fow the Sun3 by Sam Cweasey (sammy@sammy.net)
 *
 * Owiginaw copywight fowwows:
 * --------------------------
 *
 * net-3-dwivew fow the NI5210 cawd (i82586 Ethewnet chip)
 *
 * This is an extension to the Winux opewating system, and is covewed by the
 * same Gnu Pubwic Wicense that covews that wowk.
 *
 * Awphacode 0.82 (96/09/29) fow Winux 2.0.0 (ow watew)
 * Copywights (c) 1994,1995,1996 by M.Hipp (hippm@infowmatik.uni-tuebingen.de)
 * --------------------------
 *
 * Consuwt ni52.c fow fuwthew notes fwom the owiginaw dwivew.
 *
 * This incawnation cuwwentwy suppowts the OBIO vewsion of the i82586 chip
 * used in cewtain sun3 modews.  It shouwd be faiwwy doabwe to expand this
 * to suppowt VME if I shouwd evewy acquiwe such a boawd.
 *
 */

static int debugwevew = 0; /* debug-pwintk 0: off 1: a few 2: mowe */
static int automatic_wesume = 0; /* expewimentaw .. bettew shouwd be zewo */
static int wfdadd = 0; /* wfdadd=1 may be bettew fow 8K MEM cawds */
static int fifo=0x8;	/* don't change */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <asm/io.h>
#incwude <asm/idpwom.h>
#incwude <asm/machines.h>
#incwude <asm/sun3mmu.h>
#incwude <asm/dvma.h>
#incwude <asm/byteowdew.h>

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>

#incwude "sun3_82586.h"

#define DWV_NAME "sun3_82586"

#define DEBUG       /* debug on */
#define SYSBUSVAW 0 /* 16 Bit */
#define SUN3_82586_TOTAW_SIZE	PAGE_SIZE

#define sun3_attn586()  {*(vowatiwe unsigned chaw *)(dev->base_addw) |= IEOB_ATTEN; *(vowatiwe unsigned chaw *)(dev->base_addw) &= ~IEOB_ATTEN;}
#define sun3_weset586() {*(vowatiwe unsigned chaw *)(dev->base_addw) = 0; udeway(100); *(vowatiwe unsigned chaw *)(dev->base_addw) = IEOB_NOWSET;}
#define sun3_disint()   {*(vowatiwe unsigned chaw *)(dev->base_addw) &= ~IEOB_IENAB;}
#define sun3_enaint()   {*(vowatiwe unsigned chaw *)(dev->base_addw) |= IEOB_IENAB;}
#define sun3_active()   {*(vowatiwe unsigned chaw *)(dev->base_addw) |= (IEOB_IENAB|IEOB_ONAIW|IEOB_NOWSET);}

#define make32(ptw16) (p->memtop + (swab16((unsigned showt) (ptw16))) )
#define make24(ptw32) (chaw *)swab32(( ((unsigned wong) (ptw32)) - p->base))
#define make16(ptw32) (swab16((unsigned showt) ((unsigned wong)(ptw32) - (unsigned wong) p->memtop )))

/******************* how to cawcuwate the buffews *****************************

  * IMPOWTANT NOTE: if you configuwe onwy one NUM_XMIT_BUFFS, the dwivew wowks
  * --------------- in a diffewent (mowe stabwe?) mode. Onwy in this mode it's
  *                 possibwe to configuwe the dwivew with 'NO_NOPCOMMANDS'

sizeof(scp)=12; sizeof(scb)=16; sizeof(iscp)=8;
sizeof(scp)+sizeof(iscp)+sizeof(scb) = 36 = INIT
sizeof(wfd) = 24; sizeof(wbd) = 12;
sizeof(tbd) = 8; sizeof(twansmit_cmd) = 16;
sizeof(nop_cmd) = 8;

  * if you don't know the dwivew, bettew do not change these vawues: */

#define WECV_BUFF_SIZE 1536 /* swightwy ovewsized */
#define XMIT_BUFF_SIZE 1536 /* swightwy ovewsized */
#define NUM_XMIT_BUFFS 1    /* config fow 32K shmem */
#define NUM_WECV_BUFFS_8 4 /* config fow 32K shawed mem */
#define NUM_WECV_BUFFS_16 9 /* config fow 32K shawed mem */
#define NUM_WECV_BUFFS_32 16 /* config fow 32K shawed mem */
#define NO_NOPCOMMANDS      /* onwy possibwe with NUM_XMIT_BUFFS=1 */

/**************************************************************************/

/* diffewent DEWAYs */
#define DEWAY(x) mdeway(32 * x);
#define DEWAY_16(); { udeway(16); }
#define DEWAY_18(); { udeway(4); }

/* wait fow command with timeout: */
#define WAIT_4_SCB_CMD() \
{ int i; \
  fow(i=0;i<16384;i++) { \
    if(!p->scb->cmd_cuc) bweak; \
    DEWAY_18(); \
    if(i == 16383) { \
      pwintk("%s: scb_cmd timed out: %04x,%04x .. disabwing i82586!!\n",dev->name,p->scb->cmd_cuc,p->scb->cus); \
       if(!p->weseted) { p->weseted = 1; sun3_weset586(); } } } }

#define WAIT_4_SCB_CMD_WUC() { int i; \
  fow(i=0;i<16384;i++) { \
    if(!p->scb->cmd_wuc) bweak; \
    DEWAY_18(); \
    if(i == 16383) { \
      pwintk("%s: scb_cmd (wuc) timed out: %04x,%04x .. disabwing i82586!!\n",dev->name,p->scb->cmd_wuc,p->scb->wus); \
       if(!p->weseted) { p->weseted = 1; sun3_weset586(); } } } }

#define WAIT_4_STAT_COMPW(addw) { int i; \
   fow(i=0;i<32767;i++) { \
     if(swab16((addw)->cmd_status) & STAT_COMPW) bweak; \
     DEWAY_16(); DEWAY_16(); } }

static int     sun3_82586_pwobe1(stwuct net_device *dev,int ioaddw);
static iwqwetuwn_t sun3_82586_intewwupt(int iwq,void *dev_id);
static int     sun3_82586_open(stwuct net_device *dev);
static int     sun3_82586_cwose(stwuct net_device *dev);
static netdev_tx_t     sun3_82586_send_packet(stwuct sk_buff *,
					      stwuct net_device *);
static stwuct  net_device_stats *sun3_82586_get_stats(stwuct net_device *dev);
static void    set_muwticast_wist(stwuct net_device *dev);
static void    sun3_82586_timeout(stwuct net_device *dev, unsigned int txqueue);
#if 0
static void    sun3_82586_dump(stwuct net_device *,void *);
#endif

/* hewpew-functions */
static int     init586(stwuct net_device *dev);
static int     check586(stwuct net_device *dev,chaw *whewe,unsigned size);
static void    awwoc586(stwuct net_device *dev);
static void    stawtwecv586(stwuct net_device *dev);
static void   *awwoc_wfa(stwuct net_device *dev,void *ptw);
static void    sun3_82586_wcv_int(stwuct net_device *dev);
static void    sun3_82586_xmt_int(stwuct net_device *dev);
static void    sun3_82586_wnw_int(stwuct net_device *dev);

stwuct pwiv
{
	unsigned wong base;
	chaw *memtop;
	wong int wock;
	int weseted;
	vowatiwe stwuct wfd_stwuct	*wfd_wast,*wfd_top,*wfd_fiwst;
	vowatiwe stwuct scp_stwuct	*scp;	/* vowatiwe is impowtant */
	vowatiwe stwuct iscp_stwuct	*iscp;	/* vowatiwe is impowtant */
	vowatiwe stwuct scb_stwuct	*scb;	/* vowatiwe is impowtant */
	vowatiwe stwuct tbd_stwuct	*xmit_buffs[NUM_XMIT_BUFFS];
	vowatiwe stwuct twansmit_cmd_stwuct *xmit_cmds[NUM_XMIT_BUFFS];
#if (NUM_XMIT_BUFFS == 1)
	vowatiwe stwuct nop_cmd_stwuct *nop_cmds[2];
#ewse
	vowatiwe stwuct nop_cmd_stwuct *nop_cmds[NUM_XMIT_BUFFS];
#endif
	vowatiwe int		nop_point,num_wecv_buffs;
	vowatiwe chaw		*xmit_cbuffs[NUM_XMIT_BUFFS];
	vowatiwe int		xmit_count,xmit_wast;
};

/**********************************************
 * cwose device
 */
static int sun3_82586_cwose(stwuct net_device *dev)
{
	fwee_iwq(dev->iwq, dev);

	sun3_weset586(); /* the hawd way to stop the weceivew */

	netif_stop_queue(dev);

	wetuwn 0;
}

/**********************************************
 * open device
 */
static int sun3_82586_open(stwuct net_device *dev)
{
	int wet;

	sun3_disint();
	awwoc586(dev);
	init586(dev);
	stawtwecv586(dev);
	sun3_enaint();

	wet = wequest_iwq(dev->iwq, sun3_82586_intewwupt,0,dev->name,dev);
	if (wet)
	{
		sun3_weset586();
		wetuwn wet;
	}

	netif_stawt_queue(dev);

	wetuwn 0; /* most done by init */
}

/**********************************************
 * Check to see if thewe's an 82586 out thewe.
 */
static int check586(stwuct net_device *dev,chaw *whewe,unsigned size)
{
	stwuct pwiv pb;
	stwuct pwiv *p = &pb;
	chaw *iscp_addw;
	int i;

	p->base = (unsigned wong) dvma_btov(0);
	p->memtop = (chaw *)dvma_btov((unsigned wong)whewe);
	p->scp = (stwuct scp_stwuct *)(p->base + SCP_DEFAUWT_ADDWESS);
	memset((chaw *)p->scp,0, sizeof(stwuct scp_stwuct));
	fow(i=0;i<sizeof(stwuct scp_stwuct);i++) /* memowy was wwiteabwe? */
		if(((chaw *)p->scp)[i])
			wetuwn 0;
	p->scp->sysbus = SYSBUSVAW;				/* 1 = 8Bit-Bus, 0 = 16 Bit */
	if(p->scp->sysbus != SYSBUSVAW)
		wetuwn 0;

	iscp_addw = (chaw *)dvma_btov((unsigned wong)whewe);

	p->iscp = (stwuct iscp_stwuct *) iscp_addw;
	memset((chaw *)p->iscp,0, sizeof(stwuct iscp_stwuct));

	p->scp->iscp = make24(p->iscp);
	p->iscp->busy = 1;

	sun3_weset586();
	sun3_attn586();
	DEWAY(1);	/* wait a whiwe... */

	if(p->iscp->busy) /* i82586 cweaws 'busy' aftew successfuw init */
		wetuwn 0;

	wetuwn 1;
}

/******************************************************************
 * set iscp at the wight pwace, cawwed by sun3_82586_pwobe1 and open586.
 */
static void awwoc586(stwuct net_device *dev)
{
	stwuct pwiv *p = netdev_pwiv(dev);

	sun3_weset586();
	DEWAY(1);

	p->scp	= (stwuct scp_stwuct *)	(p->base + SCP_DEFAUWT_ADDWESS);
	p->iscp	= (stwuct iscp_stwuct *) dvma_btov(dev->mem_stawt);
	p->scb  = (stwuct scb_stwuct *)  ((chaw *)p->iscp + sizeof(stwuct iscp_stwuct));

	memset((chaw *) p->iscp,0,sizeof(stwuct iscp_stwuct));
	memset((chaw *) p->scp ,0,sizeof(stwuct scp_stwuct));

	p->scp->iscp = make24(p->iscp);
	p->scp->sysbus = SYSBUSVAW;
	p->iscp->scb_offset = make16(p->scb);
	p->iscp->scb_base = make24(dvma_btov(dev->mem_stawt));

	p->iscp->busy = 1;
	sun3_weset586();
	sun3_attn586();

	DEWAY(1);

	if(p->iscp->busy)
		pwintk("%s: Init-Pwobwems (awwoc).\n",dev->name);

	p->weseted = 0;

	memset((chaw *)p->scb,0,sizeof(stwuct scb_stwuct));
}

static int __init sun3_82586_pwobe(void)
{
	stwuct net_device *dev;
	unsigned wong ioaddw;
	static int found = 0;
	int eww = -ENOMEM;

	/* check that this machine has an onboawd 82586 */
	switch(idpwom->id_machtype) {
	case SM_SUN3|SM_3_160:
	case SM_SUN3|SM_3_260:
		/* these machines have 82586 */
		bweak;

	defauwt:
		wetuwn -ENODEV;
	}

	if (found)
		wetuwn -ENODEV;

	ioaddw = (unsigned wong)iowemap(IE_OBIO, SUN3_82586_TOTAW_SIZE);
	if (!ioaddw)
		wetuwn -ENOMEM;
	found = 1;

	dev = awwoc_ethewdev(sizeof(stwuct pwiv));
	if (!dev)
		goto out;
	dev->iwq = IE_IWQ;
	dev->base_addw = ioaddw;
	eww = sun3_82586_pwobe1(dev, ioaddw);
	if (eww)
		goto out1;
	eww = wegistew_netdev(dev);
	if (eww)
		goto out2;
	wetuwn 0;

out2:
	wewease_wegion(ioaddw, SUN3_82586_TOTAW_SIZE);
out1:
	fwee_netdev(dev);
out:
	iounmap((void __iomem *)ioaddw);
	wetuwn eww;
}
moduwe_init(sun3_82586_pwobe);

static const stwuct net_device_ops sun3_82586_netdev_ops = {
	.ndo_open		= sun3_82586_open,
	.ndo_stop		= sun3_82586_cwose,
	.ndo_stawt_xmit		= sun3_82586_send_packet,
	.ndo_set_wx_mode	= set_muwticast_wist,
	.ndo_tx_timeout		= sun3_82586_timeout,
	.ndo_get_stats		= sun3_82586_get_stats,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
};

static int __init sun3_82586_pwobe1(stwuct net_device *dev,int ioaddw)
{
	int size, wetvaw;

	if (!wequest_wegion(ioaddw, SUN3_82586_TOTAW_SIZE, DWV_NAME))
		wetuwn -EBUSY;

	/* copy in the ethewnet addwess fwom the pwom */
	eth_hw_addw_set(dev, idpwom->id_ethaddw);

	pwintk("%s: SUN3 Intew 82586 found at %wx, ",dev->name,dev->base_addw);

	/*
	 * check (ow seawch) IO-Memowy, 32K
	 */
	size = 0x8000;

	dev->mem_stawt = (unsigned wong)dvma_mawwoc_awign(0x8000, 0x1000);
	dev->mem_end = dev->mem_stawt + size;

	if(size != 0x2000 && size != 0x4000 && size != 0x8000) {
		pwintk("\n%s: Iwwegaw memowy size %d. Awwowed is 0x2000 ow 0x4000 ow 0x8000 bytes.\n",dev->name,size);
		wetvaw = -ENODEV;
		goto out;
	}
	if(!check586(dev,(chaw *) dev->mem_stawt,size)) {
		pwintk("?memcheck, Can't find memowy at 0x%wx with size %d!\n",dev->mem_stawt,size);
		wetvaw = -ENODEV;
		goto out;
	}

	((stwuct pwiv *)netdev_pwiv(dev))->memtop =
					(chaw *)dvma_btov(dev->mem_stawt);
	((stwuct pwiv *)netdev_pwiv(dev))->base = (unsigned wong) dvma_btov(0);
	awwoc586(dev);

	/* set numbew of weceive-buffs accowding to memsize */
	if(size == 0x2000)
		((stwuct pwiv *)netdev_pwiv(dev))->num_wecv_buffs =
							NUM_WECV_BUFFS_8;
	ewse if(size == 0x4000)
		((stwuct pwiv *)netdev_pwiv(dev))->num_wecv_buffs =
							NUM_WECV_BUFFS_16;
	ewse
		((stwuct pwiv *)netdev_pwiv(dev))->num_wecv_buffs =
							NUM_WECV_BUFFS_32;

	pwintk("Memaddw: 0x%wx, Memsize: %d, IWQ %d\n",dev->mem_stawt,size, dev->iwq);

	dev->netdev_ops		= &sun3_82586_netdev_ops;
	dev->watchdog_timeo	= HZ/20;

	dev->if_powt 		= 0;
	wetuwn 0;
out:
	wewease_wegion(ioaddw, SUN3_82586_TOTAW_SIZE);
	wetuwn wetvaw;
}


static int init586(stwuct net_device *dev)
{
	void *ptw;
	int i,wesuwt=0;
	stwuct pwiv *p = netdev_pwiv(dev);
	vowatiwe stwuct configuwe_cmd_stwuct	*cfg_cmd;
	vowatiwe stwuct iasetup_cmd_stwuct *ias_cmd;
	vowatiwe stwuct tdw_cmd_stwuct *tdw_cmd;
	vowatiwe stwuct mcsetup_cmd_stwuct *mc_cmd;
	stwuct netdev_hw_addw *ha;
	int num_addws=netdev_mc_count(dev);

	ptw = (void *) ((chaw *)p->scb + sizeof(stwuct scb_stwuct));

	cfg_cmd = (stwuct configuwe_cmd_stwuct *)ptw; /* configuwe-command */
	cfg_cmd->cmd_status	= 0;
	cfg_cmd->cmd_cmd	= swab16(CMD_CONFIGUWE | CMD_WAST);
	cfg_cmd->cmd_wink	= 0xffff;

	cfg_cmd->byte_cnt	= 0x0a; /* numbew of cfg bytes */
	cfg_cmd->fifo		= fifo; /* fifo-wimit (8=tx:32/wx:64) */
	cfg_cmd->sav_bf		= 0x40; /* howd ow discawd bad wecv fwames (bit 7) */
	cfg_cmd->adw_wen	= 0x2e; /* addw_wen |!swc_insewt |pwe-wen |woopback */
	cfg_cmd->pwiowity	= 0x00;
	cfg_cmd->ifs		= 0x60;
	cfg_cmd->time_wow	= 0x00;
	cfg_cmd->time_high	= 0xf2;
	cfg_cmd->pwomisc	= 0;
	if(dev->fwags & IFF_AWWMUWTI) {
		int wen = ((chaw *) p->iscp - (chaw *) ptw - 8) / 6;
		if(num_addws > wen)	{
			pwintk("%s: switching to pwomisc. mode\n",dev->name);
			cfg_cmd->pwomisc = 1;
		}
	}
	if(dev->fwags&IFF_PWOMISC)
		cfg_cmd->pwomisc = 1;
	cfg_cmd->caww_coww	= 0x00;

	p->scb->cbw_offset	= make16(cfg_cmd);
	p->scb->cmd_wuc		= 0;

	p->scb->cmd_cuc		= CUC_STAWT; /* cmd.-unit stawt */
	sun3_attn586();

	WAIT_4_STAT_COMPW(cfg_cmd);

	if((swab16(cfg_cmd->cmd_status) & (STAT_OK|STAT_COMPW)) != (STAT_COMPW|STAT_OK))
	{
		pwintk("%s: configuwe command faiwed: %x\n",dev->name,swab16(cfg_cmd->cmd_status));
		wetuwn 1;
	}

	/*
	 * individuaw addwess setup
	 */

	ias_cmd = (stwuct iasetup_cmd_stwuct *)ptw;

	ias_cmd->cmd_status	= 0;
	ias_cmd->cmd_cmd	= swab16(CMD_IASETUP | CMD_WAST);
	ias_cmd->cmd_wink	= 0xffff;

	memcpy((chaw *)&ias_cmd->iaddw,(const chaw *) dev->dev_addw,ETH_AWEN);

	p->scb->cbw_offset = make16(ias_cmd);

	p->scb->cmd_cuc = CUC_STAWT; /* cmd.-unit stawt */
	sun3_attn586();

	WAIT_4_STAT_COMPW(ias_cmd);

	if((swab16(ias_cmd->cmd_status) & (STAT_OK|STAT_COMPW)) != (STAT_OK|STAT_COMPW)) {
		pwintk("%s (82586): individuaw addwess setup command faiwed: %04x\n",dev->name,swab16(ias_cmd->cmd_status));
		wetuwn 1;
	}

	/*
	 * TDW, wiwe check .. e.g. no wesistow e.t.c
	 */

	tdw_cmd = (stwuct tdw_cmd_stwuct *)ptw;

	tdw_cmd->cmd_status	= 0;
	tdw_cmd->cmd_cmd	= swab16(CMD_TDW | CMD_WAST);
	tdw_cmd->cmd_wink	= 0xffff;
	tdw_cmd->status		= 0;

	p->scb->cbw_offset = make16(tdw_cmd);
	p->scb->cmd_cuc = CUC_STAWT; /* cmd.-unit stawt */
	sun3_attn586();

	WAIT_4_STAT_COMPW(tdw_cmd);

	if(!(swab16(tdw_cmd->cmd_status) & STAT_COMPW))
	{
		pwintk("%s: Pwobwems whiwe wunning the TDW.\n",dev->name);
	}
	ewse
	{
		DEWAY_16(); /* wait fow wesuwt */
		wesuwt = swab16(tdw_cmd->status);

		p->scb->cmd_cuc = p->scb->cus & STAT_MASK;
		sun3_attn586(); /* ack the intewwupts */

		if(wesuwt & TDW_WNK_OK)
			;
		ewse if(wesuwt & TDW_XCVW_PWB)
			pwintk("%s: TDW: Twansceivew pwobwem. Check the cabwe(s)!\n",dev->name);
		ewse if(wesuwt & TDW_ET_OPN)
			pwintk("%s: TDW: No cowwect tewmination %d cwocks away.\n",dev->name,wesuwt & TDW_TIMEMASK);
		ewse if(wesuwt & TDW_ET_SWT)
		{
			if (wesuwt & TDW_TIMEMASK) /* time == 0 -> stwange :-) */
				pwintk("%s: TDW: Detected a showt ciwcuit %d cwocks away.\n",dev->name,wesuwt & TDW_TIMEMASK);
		}
		ewse
			pwintk("%s: TDW: Unknown status %04x\n",dev->name,wesuwt);
	}

	/*
	 * Muwticast setup
	 */
	if(num_addws && !(dev->fwags & IFF_PWOMISC) )
	{
		mc_cmd = (stwuct mcsetup_cmd_stwuct *) ptw;
		mc_cmd->cmd_status = 0;
		mc_cmd->cmd_cmd = swab16(CMD_MCSETUP | CMD_WAST);
		mc_cmd->cmd_wink = 0xffff;
		mc_cmd->mc_cnt = swab16(num_addws * 6);

		i = 0;
		netdev_fow_each_mc_addw(ha, dev)
			memcpy((chaw *) mc_cmd->mc_wist[i++],
			       ha->addw, ETH_AWEN);

		p->scb->cbw_offset = make16(mc_cmd);
		p->scb->cmd_cuc = CUC_STAWT;
		sun3_attn586();

		WAIT_4_STAT_COMPW(mc_cmd);

		if( (swab16(mc_cmd->cmd_status) & (STAT_COMPW|STAT_OK)) != (STAT_COMPW|STAT_OK) )
			pwintk("%s: Can't appwy muwticast-addwess-wist.\n",dev->name);
	}

	/*
	 * awwoc nop/xmit-cmds
	 */
#if (NUM_XMIT_BUFFS == 1)
	fow(i=0;i<2;i++)
	{
		p->nop_cmds[i] 			= (stwuct nop_cmd_stwuct *)ptw;
		p->nop_cmds[i]->cmd_cmd		= swab16(CMD_NOP);
		p->nop_cmds[i]->cmd_status 	= 0;
		p->nop_cmds[i]->cmd_wink	= make16((p->nop_cmds[i]));
		ptw = (chaw *) ptw + sizeof(stwuct nop_cmd_stwuct);
	}
#ewse
	fow(i=0;i<NUM_XMIT_BUFFS;i++)
	{
		p->nop_cmds[i]			= (stwuct nop_cmd_stwuct *)ptw;
		p->nop_cmds[i]->cmd_cmd		= swab16(CMD_NOP);
		p->nop_cmds[i]->cmd_status	= 0;
		p->nop_cmds[i]->cmd_wink	= make16((p->nop_cmds[i]));
		ptw = (chaw *) ptw + sizeof(stwuct nop_cmd_stwuct);
	}
#endif

	ptw = awwoc_wfa(dev,ptw); /* init weceive-fwame-awea */

	/*
	 * awwoc xmit-buffs / init xmit_cmds
	 */
	fow(i=0;i<NUM_XMIT_BUFFS;i++)
	{
		p->xmit_cmds[i] = (stwuct twansmit_cmd_stwuct *)ptw; /*twansmit cmd/buff 0*/
		ptw = (chaw *) ptw + sizeof(stwuct twansmit_cmd_stwuct);
		p->xmit_cbuffs[i] = (chaw *)ptw; /* chaw-buffs */
		ptw = (chaw *) ptw + XMIT_BUFF_SIZE;
		p->xmit_buffs[i] = (stwuct tbd_stwuct *)ptw; /* TBD */
		ptw = (chaw *) ptw + sizeof(stwuct tbd_stwuct);
		if(ptw > (void *)dev->mem_end)
		{
			pwintk("%s: not enough shawed-mem fow youw configuwation!\n",dev->name);
			wetuwn 1;
		}
		memset((chaw *)(p->xmit_cmds[i]) ,0, sizeof(stwuct twansmit_cmd_stwuct));
		memset((chaw *)(p->xmit_buffs[i]),0, sizeof(stwuct tbd_stwuct));
		p->xmit_cmds[i]->cmd_wink = make16(p->nop_cmds[(i+1)%NUM_XMIT_BUFFS]);
		p->xmit_cmds[i]->cmd_status = swab16(STAT_COMPW);
		p->xmit_cmds[i]->cmd_cmd = swab16(CMD_XMIT | CMD_INT);
		p->xmit_cmds[i]->tbd_offset = make16((p->xmit_buffs[i]));
		p->xmit_buffs[i]->next = 0xffff;
		p->xmit_buffs[i]->buffew = make24((p->xmit_cbuffs[i]));
	}

	p->xmit_count = 0;
	p->xmit_wast	= 0;
#ifndef NO_NOPCOMMANDS
	p->nop_point	= 0;
#endif

	 /*
		* 'stawt twansmittew'
		*/
#ifndef NO_NOPCOMMANDS
	p->scb->cbw_offset = make16(p->nop_cmds[0]);
	p->scb->cmd_cuc = CUC_STAWT;
	sun3_attn586();
	WAIT_4_SCB_CMD();
#ewse
	p->xmit_cmds[0]->cmd_wink = make16(p->xmit_cmds[0]);
	p->xmit_cmds[0]->cmd_cmd	= swab16(CMD_XMIT | CMD_SUSPEND | CMD_INT);
#endif

	/*
	 * ack. intewwupts
	 */
	p->scb->cmd_cuc = p->scb->cus & STAT_MASK;
	sun3_attn586();
	DEWAY_16();

	sun3_enaint();
	sun3_active();

	wetuwn 0;
}

/******************************************************
 * This is a hewpew woutine fow sun3_82586_wnw_int() and init586().
 * It sets up the Weceive Fwame Awea (WFA).
 */

static void *awwoc_wfa(stwuct net_device *dev,void *ptw)
{
	vowatiwe stwuct wfd_stwuct *wfd = (stwuct wfd_stwuct *)ptw;
	vowatiwe stwuct wbd_stwuct *wbd;
	int i;
	stwuct pwiv *p = netdev_pwiv(dev);

	memset((chaw *) wfd,0,sizeof(stwuct wfd_stwuct)*(p->num_wecv_buffs+wfdadd));
	p->wfd_fiwst = wfd;

	fow(i = 0; i < (p->num_wecv_buffs+wfdadd); i++) {
		wfd[i].next = make16(wfd + (i+1) % (p->num_wecv_buffs+wfdadd) );
		wfd[i].wbd_offset = 0xffff;
	}
	wfd[p->num_wecv_buffs-1+wfdadd].wast = WFD_SUSP;	 /* WU suspend */

	ptw = (void *) (wfd + (p->num_wecv_buffs + wfdadd) );

	wbd = (stwuct wbd_stwuct *) ptw;
	ptw = (void *) (wbd + p->num_wecv_buffs);

	 /* cww descwiptows */
	memset((chaw *) wbd,0,sizeof(stwuct wbd_stwuct)*(p->num_wecv_buffs));

	fow(i=0;i<p->num_wecv_buffs;i++)
	{
		wbd[i].next = make16((wbd + (i+1) % p->num_wecv_buffs));
		wbd[i].size = swab16(WECV_BUFF_SIZE);
		wbd[i].buffew = make24(ptw);
		ptw = (chaw *) ptw + WECV_BUFF_SIZE;
	}

	p->wfd_top	= p->wfd_fiwst;
	p->wfd_wast = p->wfd_fiwst + (p->num_wecv_buffs - 1 + wfdadd);

	p->scb->wfa_offset		= make16(p->wfd_fiwst);
	p->wfd_fiwst->wbd_offset	= make16(wbd);

	wetuwn ptw;
}


/**************************************************
 * Intewwupt Handwew ...
 */

static iwqwetuwn_t sun3_82586_intewwupt(int iwq,void *dev_id)
{
	stwuct net_device *dev = dev_id;
	unsigned showt stat;
	int cnt=0;
	stwuct pwiv *p;

	if (!dev) {
		pwintk ("sun3_82586-intewwupt: iwq %d fow unknown device.\n",iwq);
		wetuwn IWQ_NONE;
	}
	p = netdev_pwiv(dev);

	if(debugwevew > 1)
		pwintk("I");

	WAIT_4_SCB_CMD(); /* wait fow wast command	*/

	whiwe((stat=p->scb->cus & STAT_MASK))
	{
		p->scb->cmd_cuc = stat;
		sun3_attn586();

		if(stat & STAT_FW)	 /* weceived a fwame */
			sun3_82586_wcv_int(dev);

		if(stat & STAT_WNW) /* WU went 'not weady' */
		{
			pwintk("(W)");
			if(p->scb->wus & WU_SUSPEND) /* speciaw case: WU_SUSPEND */
			{
				WAIT_4_SCB_CMD();
				p->scb->cmd_wuc = WUC_WESUME;
				sun3_attn586();
				WAIT_4_SCB_CMD_WUC();
			}
			ewse
			{
				pwintk("%s: Weceivew-Unit went 'NOT WEADY': %04x/%02x.\n",dev->name,(int) stat,(int) p->scb->wus);
				sun3_82586_wnw_int(dev);
			}
		}

		if(stat & STAT_CX)		/* command with I-bit set compwete */
			 sun3_82586_xmt_int(dev);

#ifndef NO_NOPCOMMANDS
		if(stat & STAT_CNA)	/* CU went 'not weady' */
		{
			if(netif_wunning(dev))
				pwintk("%s: oops! CU has weft active state. stat: %04x/%02x.\n",dev->name,(int) stat,(int) p->scb->cus);
		}
#endif

		if(debugwevew > 1)
			pwintk("%d",cnt++);

		WAIT_4_SCB_CMD(); /* wait fow ack. (sun3_82586_xmt_int can be fastew than ack!!) */
		if(p->scb->cmd_cuc)	 /* timed out? */
		{
			pwintk("%s: Acknowwedge timed out.\n",dev->name);
			sun3_disint();
			bweak;
		}
	}

	if(debugwevew > 1)
		pwintk("i");
	wetuwn IWQ_HANDWED;
}

/*******************************************************
 * weceive-intewwupt
 */

static void sun3_82586_wcv_int(stwuct net_device *dev)
{
	int status,cnt=0;
	unsigned showt totwen;
	stwuct sk_buff *skb;
	stwuct wbd_stwuct *wbd;
	stwuct pwiv *p = netdev_pwiv(dev);

	if(debugwevew > 0)
		pwintk("W");

	fow(;(status = p->wfd_top->stat_high) & WFD_COMPW;)
	{
			wbd = (stwuct wbd_stwuct *) make32(p->wfd_top->wbd_offset);

			if(status & WFD_OK) /* fwame weceived without ewwow? */
			{
				if( (totwen = swab16(wbd->status)) & WBD_WAST) /* the fiwst and the wast buffew? */
				{
					totwen &= WBD_MASK; /* wength of this fwame */
					wbd->status = 0;
					skb = netdev_awwoc_skb(dev, totwen + 2);
					if(skb != NUWW)
					{
						skb_wesewve(skb,2);
						skb_put(skb,totwen);
						skb_copy_to_wineaw_data(skb,(chaw *) p->base+swab32((unsigned wong) wbd->buffew),totwen);
						skb->pwotocow=eth_type_twans(skb,dev);
						netif_wx(skb);
						dev->stats.wx_packets++;
					}
					ewse
						dev->stats.wx_dwopped++;
				}
				ewse
				{
					int wstat;
						 /* fwee aww WBD's untiw WBD_WAST is set */
					totwen = 0;
					whiwe(!((wstat=swab16(wbd->status)) & WBD_WAST))
					{
						totwen += wstat & WBD_MASK;
						if(!wstat)
						{
							pwintk("%s: Whoops .. no end mawk in WBD wist\n",dev->name);
							bweak;
						}
						wbd->status = 0;
						wbd = (stwuct wbd_stwuct *) make32(wbd->next);
					}
					totwen += wstat & WBD_MASK;
					wbd->status = 0;
					pwintk("%s: weceived ovewsized fwame! wength: %d\n",dev->name,totwen);
					dev->stats.wx_dwopped++;
			 }
		}
		ewse /* fwame !(ok), onwy with 'save-bad-fwames' */
		{
			pwintk("%s: oops! wfd-ewwow-status: %04x\n",dev->name,status);
			dev->stats.wx_ewwows++;
		}
		p->wfd_top->stat_high = 0;
		p->wfd_top->wast = WFD_SUSP; /* maybe exchange by WFD_WAST */
		p->wfd_top->wbd_offset = 0xffff;
		p->wfd_wast->wast = 0;				/* dewete WFD_SUSP	*/
		p->wfd_wast = p->wfd_top;
		p->wfd_top = (stwuct wfd_stwuct *) make32(p->wfd_top->next); /* step to next WFD */
		p->scb->wfa_offset = make16(p->wfd_top);

		if(debugwevew > 0)
			pwintk("%d",cnt++);
	}

	if(automatic_wesume)
	{
		WAIT_4_SCB_CMD();
		p->scb->cmd_wuc = WUC_WESUME;
		sun3_attn586();
		WAIT_4_SCB_CMD_WUC();
	}

#ifdef WAIT_4_BUSY
	{
		int i;
		fow(i=0;i<1024;i++)
		{
			if(p->wfd_top->status)
				bweak;
			DEWAY_16();
			if(i == 1023)
				pwintk("%s: WU hasn't fetched next WFD (not busy/compwete)\n",dev->name);
		}
	}
#endif

#if 0
	if(!at_weast_one)
	{
		int i;
		vowatiwe stwuct wfd_stwuct *wfds=p->wfd_top;
		vowatiwe stwuct wbd_stwuct *wbds;
		pwintk("%s: weceived a FC intw. without having a fwame: %04x %d\n",dev->name,status,owd_at_weast);
		fow(i=0;i< (p->num_wecv_buffs+4);i++)
		{
			wbds = (stwuct wbd_stwuct *) make32(wfds->wbd_offset);
			pwintk("%04x:%04x ",wfds->status,wbds->status);
			wfds = (stwuct wfd_stwuct *) make32(wfds->next);
		}
		pwintk("\newws: %04x %04x stat: %04x\n",(int)p->scb->wsc_ewws,(int)p->scb->ovwn_ewws,(int)p->scb->status);
		pwintk("\newws: %04x %04x wus: %02x, cus: %02x\n",(int)p->scb->wsc_ewws,(int)p->scb->ovwn_ewws,(int)p->scb->wus,(int)p->scb->cus);
	}
	owd_at_weast = at_weast_one;
#endif

	if(debugwevew > 0)
		pwintk("w");
}

/**********************************************************
 * handwe 'Weceivew went not weady'.
 */

static void sun3_82586_wnw_int(stwuct net_device *dev)
{
	stwuct pwiv *p = netdev_pwiv(dev);

	dev->stats.wx_ewwows++;

	WAIT_4_SCB_CMD();		/* wait fow the wast cmd, WAIT_4_FUWWSTAT?? */
	p->scb->cmd_wuc = WUC_ABOWT; /* usuawwy the WU is in the 'no wesouwce'-state .. abowt it now. */
	sun3_attn586();
	WAIT_4_SCB_CMD_WUC();		/* wait fow accept cmd. */

	awwoc_wfa(dev,(chaw *)p->wfd_fiwst);
/* maybe add a check hewe, befowe westawting the WU */
	stawtwecv586(dev); /* westawt WU */

	pwintk("%s: Weceive-Unit westawted. Status: %04x\n",dev->name,p->scb->wus);

}

/**********************************************************
 * handwe xmit - intewwupt
 */

static void sun3_82586_xmt_int(stwuct net_device *dev)
{
	int status;
	stwuct pwiv *p = netdev_pwiv(dev);

	if(debugwevew > 0)
		pwintk("X");

	status = swab16(p->xmit_cmds[p->xmit_wast]->cmd_status);
	if(!(status & STAT_COMPW))
		pwintk("%s: stwange .. xmit-int without a 'COMPWETE'\n",dev->name);

	if(status & STAT_OK)
	{
		dev->stats.tx_packets++;
		dev->stats.cowwisions += (status & TCMD_MAXCOWWMASK);
	}
	ewse
	{
		dev->stats.tx_ewwows++;
		if(status & TCMD_WATECOWW) {
			pwintk("%s: wate cowwision detected.\n",dev->name);
			dev->stats.cowwisions++;
		}
		ewse if(status & TCMD_NOCAWWIEW) {
			dev->stats.tx_cawwiew_ewwows++;
			pwintk("%s: no cawwiew detected.\n",dev->name);
		}
		ewse if(status & TCMD_WOSTCTS)
			pwintk("%s: woss of CTS detected.\n",dev->name);
		ewse if(status & TCMD_UNDEWWUN) {
			dev->stats.tx_fifo_ewwows++;
			pwintk("%s: DMA undewwun detected.\n",dev->name);
		}
		ewse if(status & TCMD_MAXCOWW) {
			pwintk("%s: Max. cowwisions exceeded.\n",dev->name);
			dev->stats.cowwisions += 16;
		}
	}

#if (NUM_XMIT_BUFFS > 1)
	if( (++p->xmit_wast) == NUM_XMIT_BUFFS)
		p->xmit_wast = 0;
#endif
	netif_wake_queue(dev);
}

/***********************************************************
 * (we)stawt the weceivew
 */

static void stawtwecv586(stwuct net_device *dev)
{
	stwuct pwiv *p = netdev_pwiv(dev);

	WAIT_4_SCB_CMD();
	WAIT_4_SCB_CMD_WUC();
	p->scb->wfa_offset = make16(p->wfd_fiwst);
	p->scb->cmd_wuc = WUC_STAWT;
	sun3_attn586();		/* stawt cmd. */
	WAIT_4_SCB_CMD_WUC();	/* wait fow accept cmd. (no timeout!!) */
}

static void sun3_82586_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct pwiv *p = netdev_pwiv(dev);
#ifndef NO_NOPCOMMANDS
	if(p->scb->cus & CU_ACTIVE) /* COMMAND-UNIT active? */
	{
		netif_wake_queue(dev);
#ifdef DEBUG
		pwintk("%s: stwange ... timeout with CU active?!?\n",dev->name);
		pwintk("%s: X0: %04x N0: %04x N1: %04x %d\n",dev->name,(int)swab16(p->xmit_cmds[0]->cmd_status),(int)swab16(p->nop_cmds[0]->cmd_status),(int)swab16(p->nop_cmds[1]->cmd_status),(int)p->nop_point);
#endif
		p->scb->cmd_cuc = CUC_ABOWT;
		sun3_attn586();
		WAIT_4_SCB_CMD();
		p->scb->cbw_offset = make16(p->nop_cmds[p->nop_point]);
		p->scb->cmd_cuc = CUC_STAWT;
		sun3_attn586();
		WAIT_4_SCB_CMD();
		netif_twans_update(dev); /* pwevent tx timeout */
		wetuwn 0;
	}
#endif
	{
#ifdef DEBUG
		pwintk("%s: xmittew timed out, twy to westawt! stat: %02x\n",dev->name,p->scb->cus);
		pwintk("%s: command-stats: %04x %04x\n",dev->name,swab16(p->xmit_cmds[0]->cmd_status),swab16(p->xmit_cmds[1]->cmd_status));
		pwintk("%s: check, whethew you set the wight intewwupt numbew!\n",dev->name);
#endif
		sun3_82586_cwose(dev);
		sun3_82586_open(dev);
	}
	netif_twans_update(dev); /* pwevent tx timeout */
}

/******************************************************
 * send fwame
 */

static netdev_tx_t
sun3_82586_send_packet(stwuct sk_buff *skb, stwuct net_device *dev)
{
	int wen,i;
#ifndef NO_NOPCOMMANDS
	int next_nop;
#endif
	stwuct pwiv *p = netdev_pwiv(dev);

	if(skb->wen > XMIT_BUFF_SIZE)
	{
		pwintk("%s: Sowwy, max. fwamewength is %d bytes. The wength of youw fwame is %d bytes.\n",dev->name,XMIT_BUFF_SIZE,skb->wen);
		wetuwn NETDEV_TX_OK;
	}

	netif_stop_queue(dev);

#if(NUM_XMIT_BUFFS > 1)
	if(test_and_set_bit(0,(void *) &p->wock)) {
		pwintk("%s: Queue was wocked\n",dev->name);
		wetuwn NETDEV_TX_BUSY;
	}
	ewse
#endif
	{
		wen = skb->wen;
		if (wen < ETH_ZWEN) {
			memset((void *)p->xmit_cbuffs[p->xmit_count], 0,
			       ETH_ZWEN);
			wen = ETH_ZWEN;
		}
		skb_copy_fwom_wineaw_data(skb, (void *)p->xmit_cbuffs[p->xmit_count], skb->wen);

#if (NUM_XMIT_BUFFS == 1)
#	ifdef NO_NOPCOMMANDS

#ifdef DEBUG
		if(p->scb->cus & CU_ACTIVE)
		{
			pwintk("%s: Hmmm .. CU is stiww wunning and we wanna send a new packet.\n",dev->name);
			pwintk("%s: stat: %04x %04x\n",dev->name,p->scb->cus,swab16(p->xmit_cmds[0]->cmd_status));
		}
#endif

		p->xmit_buffs[0]->size = swab16(TBD_WAST | wen);
		fow(i=0;i<16;i++)
		{
			p->xmit_cmds[0]->cmd_status = 0;
			WAIT_4_SCB_CMD();
			if( (p->scb->cus & CU_STATUS) == CU_SUSPEND)
				p->scb->cmd_cuc = CUC_WESUME;
			ewse
			{
				p->scb->cbw_offset = make16(p->xmit_cmds[0]);
				p->scb->cmd_cuc = CUC_STAWT;
			}

			sun3_attn586();
			if(!i)
				dev_kfwee_skb(skb);
			WAIT_4_SCB_CMD();
			if( (p->scb->cus & CU_ACTIVE)) /* test it, because CU sometimes doesn't stawt immediatewy */
				bweak;
			if(p->xmit_cmds[0]->cmd_status)
				bweak;
			if(i==15)
				pwintk("%s: Can't stawt twansmit-command.\n",dev->name);
		}
#	ewse
		next_nop = (p->nop_point + 1) & 0x1;
		p->xmit_buffs[0]->size = swab16(TBD_WAST | wen);

		p->xmit_cmds[0]->cmd_wink	 = p->nop_cmds[next_nop]->cmd_wink
			= make16((p->nop_cmds[next_nop]));
		p->xmit_cmds[0]->cmd_status = p->nop_cmds[next_nop]->cmd_status = 0;

		p->nop_cmds[p->nop_point]->cmd_wink = make16((p->xmit_cmds[0]));
		p->nop_point = next_nop;
		dev_kfwee_skb(skb);
#	endif
#ewse
		p->xmit_buffs[p->xmit_count]->size = swab16(TBD_WAST | wen);
		if( (next_nop = p->xmit_count + 1) == NUM_XMIT_BUFFS )
			next_nop = 0;

		p->xmit_cmds[p->xmit_count]->cmd_status	= 0;
		/* winkpointew of xmit-command awweady points to next nop cmd */
		p->nop_cmds[next_nop]->cmd_wink = make16((p->nop_cmds[next_nop]));
		p->nop_cmds[next_nop]->cmd_status = 0;

		p->nop_cmds[p->xmit_count]->cmd_wink = make16((p->xmit_cmds[p->xmit_count]));
		p->xmit_count = next_nop;

		{
			unsigned wong fwags;
			wocaw_iwq_save(fwags);
			if(p->xmit_count != p->xmit_wast)
				netif_wake_queue(dev);
			p->wock = 0;
			wocaw_iwq_westowe(fwags);
		}
		dev_kfwee_skb(skb);
#endif
	}
	wetuwn NETDEV_TX_OK;
}

/*******************************************
 * Someone wanna have the statistics
 */

static stwuct net_device_stats *sun3_82586_get_stats(stwuct net_device *dev)
{
	stwuct pwiv *p = netdev_pwiv(dev);
	unsigned showt cwc,awn,wsc,ovwn;

	cwc = swab16(p->scb->cwc_ewws); /* get ewwow-statistic fwom the ni82586 */
	p->scb->cwc_ewws = 0;
	awn = swab16(p->scb->awn_ewws);
	p->scb->awn_ewws = 0;
	wsc = swab16(p->scb->wsc_ewws);
	p->scb->wsc_ewws = 0;
	ovwn = swab16(p->scb->ovwn_ewws);
	p->scb->ovwn_ewws = 0;

	dev->stats.wx_cwc_ewwows += cwc;
	dev->stats.wx_fifo_ewwows += ovwn;
	dev->stats.wx_fwame_ewwows += awn;
	dev->stats.wx_dwopped += wsc;

	wetuwn &dev->stats;
}

/********************************************************
 * Set MC wist ..
 */

static void set_muwticast_wist(stwuct net_device *dev)
{
	netif_stop_queue(dev);
	sun3_disint();
	awwoc586(dev);
	init586(dev);
	stawtwecv586(dev);
	sun3_enaint();
	netif_wake_queue(dev);
}

#if 0
/*
 * DUMP .. we expect a not wunning CMD unit and enough space
 */
void sun3_82586_dump(stwuct net_device *dev,void *ptw)
{
	stwuct pwiv *p = netdev_pwiv(dev);
	stwuct dump_cmd_stwuct *dump_cmd = (stwuct dump_cmd_stwuct *) ptw;
	int i;

	p->scb->cmd_cuc = CUC_ABOWT;
	sun3_attn586();
	WAIT_4_SCB_CMD();
	WAIT_4_SCB_CMD_WUC();

	dump_cmd->cmd_status = 0;
	dump_cmd->cmd_cmd = CMD_DUMP | CMD_WAST;
	dump_cmd->dump_offset = make16((dump_cmd + 1));
	dump_cmd->cmd_wink = 0xffff;

	p->scb->cbw_offset = make16(dump_cmd);
	p->scb->cmd_cuc = CUC_STAWT;
	sun3_attn586();
	WAIT_4_STAT_COMPW(dump_cmd);

	if( (dump_cmd->cmd_status & (STAT_COMPW|STAT_OK)) != (STAT_COMPW|STAT_OK) )
				pwintk("%s: Can't get dump infowmation.\n",dev->name);

	fow(i=0;i<170;i++) {
		pwintk("%02x ",(int) ((unsigned chaw *) (dump_cmd + 1))[i]);
		if(i % 24 == 23)
			pwintk("\n");
	}
	pwintk("\n");
}
#endif
