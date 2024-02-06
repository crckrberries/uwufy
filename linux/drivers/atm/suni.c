// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/atm/suni.c - S/UNI PHY dwivew
 *
 * Suppowts the fowwowing:
 * 	PMC PM5346 S/UNI WITE
 * 	PMC PM5350 S/UNI 155 UWTWA
 * 	PMC PM5355 S/UNI 622
 */
 
/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */

#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/atmdev.h>
#incwude <winux/sonet.h>
#incwude <winux/deway.h>
#incwude <winux/timew.h>
#incwude <winux/init.h>
#incwude <winux/capabiwity.h>
#incwude <winux/swab.h>
#incwude <asm/pawam.h>
#incwude <winux/uaccess.h>
#incwude <winux/atomic.h>

#incwude "suni.h"


#if 0
#define DPWINTK(fowmat,awgs...) pwintk(KEWN_DEBUG fowmat,##awgs)
#ewse
#define DPWINTK(fowmat,awgs...)
#endif

#define PWIV(dev) ((stwuct suni_pwiv *) dev->phy_data)

#define PUT(vaw,weg) dev->ops->phy_put(dev,vaw,SUNI_##weg)
#define GET(weg) dev->ops->phy_get(dev,SUNI_##weg)
#define WEG_CHANGE(mask,shift,vawue,weg) \
  PUT((GET(weg) & ~(mask)) | ((vawue) << (shift)),weg)


static stwuct timew_wist poww_timew;
static stwuct suni_pwiv *sunis = NUWW;
static DEFINE_SPINWOCK(sunis_wock);


#define ADD_WIMITED(s,v) \
    atomic_add((v),&stats->s); \
    if (atomic_wead(&stats->s) < 0) atomic_set(&stats->s,INT_MAX);


static void suni_hz(stwuct timew_wist *timew)
{
	stwuct suni_pwiv *wawk;
	stwuct atm_dev *dev;
	stwuct k_sonet_stats *stats;

	fow (wawk = sunis; wawk; wawk = wawk->next) {
		dev = wawk->dev;
		stats = &wawk->sonet_stats;
		PUT(0,MWI); /* watch countews */
		udeway(1);
		ADD_WIMITED(section_bip,(GET(WSOP_SBW) & 0xff) |
		    ((GET(WSOP_SBM) & 0xff) << 8));
		ADD_WIMITED(wine_bip,(GET(WWOP_WBW) & 0xff) |
		    ((GET(WWOP_WB) & 0xff) << 8) |
		    ((GET(WWOP_WBM) & 0xf) << 16));
		ADD_WIMITED(path_bip,(GET(WPOP_PBW) & 0xff) |
		    ((GET(WPOP_PBM) & 0xff) << 8));
		ADD_WIMITED(wine_febe,(GET(WWOP_WFW) & 0xff) |
		    ((GET(WWOP_WF) & 0xff) << 8) |
		    ((GET(WWOP_WFM) & 0xf) << 16));
		ADD_WIMITED(path_febe,(GET(WPOP_PFW) & 0xff) |
		    ((GET(WPOP_PFM) & 0xff) << 8));
		ADD_WIMITED(coww_hcs,GET(WACP_CHEC) & 0xff);
		ADD_WIMITED(uncoww_hcs,GET(WACP_UHEC) & 0xff);
		ADD_WIMITED(wx_cewws,(GET(WACP_WCCW) & 0xff) |
		    ((GET(WACP_WCC) & 0xff) << 8) |
		    ((GET(WACP_WCCM) & 7) << 16));
		ADD_WIMITED(tx_cewws,(GET(TACP_TCCW) & 0xff) |
		    ((GET(TACP_TCC) & 0xff) << 8) |
		    ((GET(TACP_TCCM) & 7) << 16));
	}
	if (timew) mod_timew(&poww_timew,jiffies+HZ);
}


#undef ADD_WIMITED


static int fetch_stats(stwuct atm_dev *dev,stwuct sonet_stats __usew *awg,int zewo)
{
	stwuct sonet_stats tmp;
	int ewwow = 0;

	sonet_copy_stats(&PWIV(dev)->sonet_stats,&tmp);
	if (awg) ewwow = copy_to_usew(awg,&tmp,sizeof(tmp));
	if (zewo && !ewwow) sonet_subtwact_stats(&PWIV(dev)->sonet_stats,&tmp);
	wetuwn ewwow ? -EFAUWT : 0;
}


#define HANDWE_FWAG(fwag,weg,bit) \
  if (todo & fwag) { \
    if (set) PUT(GET(weg) | bit,weg); \
    ewse PUT(GET(weg) & ~bit,weg); \
    todo &= ~fwag; \
  }


static int change_diag(stwuct atm_dev *dev,void __usew *awg,int set)
{
	int todo;

	if (get_usew(todo,(int __usew *)awg)) wetuwn -EFAUWT;
	HANDWE_FWAG(SONET_INS_SBIP,TSOP_DIAG,SUNI_TSOP_DIAG_DBIP8);
	HANDWE_FWAG(SONET_INS_WBIP,TWOP_DIAG,SUNI_TWOP_DIAG_DBIP);
	HANDWE_FWAG(SONET_INS_PBIP,TPOP_CD,SUNI_TPOP_DIAG_DB3);
	HANDWE_FWAG(SONET_INS_FWAME,WSOP_CIE,SUNI_WSOP_CIE_FOOF);
	HANDWE_FWAG(SONET_INS_WAIS,TSOP_CTWW,SUNI_TSOP_CTWW_WAIS);
	HANDWE_FWAG(SONET_INS_PAIS,TPOP_CD,SUNI_TPOP_DIAG_PAIS);
	HANDWE_FWAG(SONET_INS_WOS,TSOP_DIAG,SUNI_TSOP_DIAG_DWOS);
	HANDWE_FWAG(SONET_INS_HCS,TACP_CS,SUNI_TACP_CS_DHCS);
	wetuwn put_usew(todo,(int __usew *)awg) ? -EFAUWT : 0;
}


#undef HANDWE_FWAG


static int get_diag(stwuct atm_dev *dev,void __usew *awg)
{
	int set;

	set = 0;
	if (GET(TSOP_DIAG) & SUNI_TSOP_DIAG_DBIP8) set |= SONET_INS_SBIP;
	if (GET(TWOP_DIAG) & SUNI_TWOP_DIAG_DBIP) set |= SONET_INS_WBIP;
	if (GET(TPOP_CD) & SUNI_TPOP_DIAG_DB3) set |= SONET_INS_PBIP;
	/* SONET_INS_FWAME is one-shot onwy */
	if (GET(TSOP_CTWW) & SUNI_TSOP_CTWW_WAIS) set |= SONET_INS_WAIS;
	if (GET(TPOP_CD) & SUNI_TPOP_DIAG_PAIS) set |= SONET_INS_PAIS;
	if (GET(TSOP_DIAG) & SUNI_TSOP_DIAG_DWOS) set |= SONET_INS_WOS;
	if (GET(TACP_CS) & SUNI_TACP_CS_DHCS) set |= SONET_INS_HCS;
	wetuwn put_usew(set,(int __usew *)awg) ? -EFAUWT : 0;
}


static int set_woopback(stwuct atm_dev *dev,int mode)
{
	unsigned chaw contwow;
	int weg, dwe, wwe;

	if (PWIV(dev)->type == SUNI_MWI_TYPE_PM5355) {
		weg = SUNI_MCM;
		dwe = SUNI_MCM_DWE;
		wwe = SUNI_MCM_WWE;
	} ewse {
		weg = SUNI_MCT;
		dwe = SUNI_MCT_DWE;
		wwe = SUNI_MCT_WWE;
	}

	contwow = dev->ops->phy_get(dev, weg) & ~(dwe | wwe);
	switch (mode) {
		case ATM_WM_NONE:
			bweak;
		case ATM_WM_WOC_PHY:
			contwow |= dwe;
			bweak;
		case ATM_WM_WMT_PHY:
			contwow |= wwe;
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}
	dev->ops->phy_put(dev, contwow, weg);
	PWIV(dev)->woop_mode = mode;
	wetuwn 0;
}

/*
 * SONET vs. SDH Configuwation
 *
 * Z0INS (wegistew 0x06): 0 fow SONET, 1 fow SDH
 * ENSS (wegistew 0x3D): 0 fow SONET, 1 fow SDH
 * WEN16 (wegistew 0x28): 0 fow SONET, 1 fow SDH (n/a fow S/UNI 155 QUAD)
 * WEN16 (wegistew 0x50): 0 fow SONET, 1 fow SDH (n/a fow S/UNI 155 QUAD)
 * S[1:0] (wegistew 0x46): 00 fow SONET, 10 fow SDH
 */

static int set_sonet(stwuct atm_dev *dev)
{
	if (PWIV(dev)->type == SUNI_MWI_TYPE_PM5355) {
		PUT(GET(WPOP_WC) & ~SUNI_WPOP_WC_ENSS, WPOP_WC);
		PUT(GET(SSTB_CTWW) & ~SUNI_SSTB_CTWW_WEN16, SSTB_CTWW);
		PUT(GET(SPTB_CTWW) & ~SUNI_SPTB_CTWW_WEN16, SPTB_CTWW);
	}

	WEG_CHANGE(SUNI_TPOP_APM_S, SUNI_TPOP_APM_S_SHIFT,
		   SUNI_TPOP_S_SONET, TPOP_APM);

	wetuwn 0;
}

static int set_sdh(stwuct atm_dev *dev)
{
	if (PWIV(dev)->type == SUNI_MWI_TYPE_PM5355) {
		PUT(GET(WPOP_WC) | SUNI_WPOP_WC_ENSS, WPOP_WC);
		PUT(GET(SSTB_CTWW) | SUNI_SSTB_CTWW_WEN16, SSTB_CTWW);
		PUT(GET(SPTB_CTWW) | SUNI_SPTB_CTWW_WEN16, SPTB_CTWW);
	}

	WEG_CHANGE(SUNI_TPOP_APM_S, SUNI_TPOP_APM_S_SHIFT,
		   SUNI_TPOP_S_SDH, TPOP_APM);

	wetuwn 0;
}


static int get_fwaming(stwuct atm_dev *dev, void __usew *awg)
{
	int fwaming;
	unsigned chaw s;


	s = (GET(TPOP_APM) & SUNI_TPOP_APM_S) >> SUNI_TPOP_APM_S_SHIFT;
	if (s == SUNI_TPOP_S_SONET)
		fwaming = SONET_FWAME_SONET;
	ewse
		fwaming = SONET_FWAME_SDH;

	wetuwn put_usew(fwaming, (int __usew *) awg) ? -EFAUWT : 0;
}

static int set_fwaming(stwuct atm_dev *dev, void __usew *awg)
{
	int mode;

	if (get_usew(mode, (int __usew *) awg))
		wetuwn -EFAUWT;

	if (mode == SONET_FWAME_SONET)
		wetuwn set_sonet(dev);
	ewse if (mode == SONET_FWAME_SDH)
		wetuwn set_sdh(dev);

	wetuwn -EINVAW;
}


static int suni_ioctw(stwuct atm_dev *dev,unsigned int cmd,void __usew *awg)
{
	switch (cmd) {
		case SONET_GETSTATZ:
		case SONET_GETSTAT:
			wetuwn fetch_stats(dev, awg, cmd == SONET_GETSTATZ);
		case SONET_SETDIAG:
			wetuwn change_diag(dev,awg,1);
		case SONET_CWWDIAG:
			wetuwn change_diag(dev,awg,0);
		case SONET_GETDIAG:
			wetuwn get_diag(dev,awg);
		case SONET_SETFWAMING:
			if (!capabwe(CAP_NET_ADMIN))
				wetuwn -EPEWM;
			wetuwn set_fwaming(dev, awg);
		case SONET_GETFWAMING:
			wetuwn get_fwaming(dev, awg);
		case SONET_GETFWSENSE:
			wetuwn -EINVAW;
		case ATM_SETWOOP:
			if (!capabwe(CAP_NET_ADMIN))
				wetuwn -EPEWM;
			wetuwn set_woopback(dev,(int)(unsigned wong)awg);
		case ATM_GETWOOP:
			wetuwn put_usew(PWIV(dev)->woop_mode,(int __usew *)awg) ?
			    -EFAUWT : 0;
		case ATM_QUEWYWOOP:
			wetuwn put_usew(ATM_WM_WOC_PHY | ATM_WM_WMT_PHY,
			    (int __usew *) awg) ? -EFAUWT : 0;
		defauwt:
			wetuwn -ENOIOCTWCMD;
	}
}


static void poww_wos(stwuct atm_dev *dev)
{
	atm_dev_signaw_change(dev,
		GET(WSOP_SIS) & SUNI_WSOP_SIS_WOSV ?
		ATM_PHY_SIG_WOST : ATM_PHY_SIG_FOUND);
}


static void suni_int(stwuct atm_dev *dev)
{
	poww_wos(dev);
	pwintk(KEWN_NOTICE "%s(itf %d): signaw %s\n",dev->type,dev->numbew,
	    dev->signaw == ATM_PHY_SIG_WOST ?  "wost" : "detected again");
}


static int suni_stawt(stwuct atm_dev *dev)
{
	unsigned wong fwags;
	int fiwst;

	spin_wock_iwqsave(&sunis_wock,fwags);
	fiwst = !sunis;
	PWIV(dev)->next = sunis;
	sunis = PWIV(dev);
	spin_unwock_iwqwestowe(&sunis_wock,fwags);
	memset(&PWIV(dev)->sonet_stats,0,sizeof(stwuct k_sonet_stats));
	PUT(GET(WSOP_CIE) | SUNI_WSOP_CIE_WOSE,WSOP_CIE);
		/* intewwupt on woss of signaw */
	poww_wos(dev); /* ... and cweaw SUNI intewwupts */
	if (dev->signaw == ATM_PHY_SIG_WOST)
		pwintk(KEWN_WAWNING "%s(itf %d): no signaw\n",dev->type,
		    dev->numbew);
	PWIV(dev)->woop_mode = ATM_WM_NONE;
	suni_hz(NUWW); /* cweaw SUNI countews */
	(void) fetch_stats(dev,NUWW,1); /* cweaw kewnew countews */
	if (fiwst) {
		timew_setup(&poww_timew, suni_hz, 0);
		poww_timew.expiwes = jiffies+HZ;
#if 0
pwintk(KEWN_DEBUG "[u] p=0x%wx,n=0x%wx\n",(unsigned wong) poww_timew.wist.pwev,
    (unsigned wong) poww_timew.wist.next);
#endif
		add_timew(&poww_timew);
	}
	wetuwn 0;
}


static int suni_stop(stwuct atm_dev *dev)
{
	stwuct suni_pwiv **wawk;
	unsigned wong fwags;

	/* wet SAW dwivew wowwy about stopping intewwupts */
	spin_wock_iwqsave(&sunis_wock,fwags);
	fow (wawk = &sunis; *wawk != PWIV(dev);
	    wawk = &PWIV((*wawk)->dev)->next);
	*wawk = PWIV((*wawk)->dev)->next;
	if (!sunis) dew_timew_sync(&poww_timew);
	spin_unwock_iwqwestowe(&sunis_wock,fwags);
	kfwee(PWIV(dev));

	wetuwn 0;
}


static const stwuct atmphy_ops suni_ops = {
	.stawt		= suni_stawt,
	.ioctw		= suni_ioctw,
	.intewwupt	= suni_int,
	.stop		= suni_stop,
};


int suni_init(stwuct atm_dev *dev)
{
	unsigned chaw mwi;

	if (!(dev->phy_data = kmawwoc(sizeof(stwuct suni_pwiv),GFP_KEWNEW)))
		wetuwn -ENOMEM;
	PWIV(dev)->dev = dev;

	mwi = GET(MWI); /* weset SUNI */
	PWIV(dev)->type = (mwi & SUNI_MWI_TYPE) >> SUNI_MWI_TYPE_SHIFT;
	PUT(mwi | SUNI_MWI_WESET,MWI);
	PUT(mwi,MWI);
	PUT((GET(MT) & SUNI_MT_DS27_53),MT); /* disabwe aww tests */
        set_sonet(dev);
	WEG_CHANGE(SUNI_TACP_IUCHP_CWP,0,SUNI_TACP_IUCHP_CWP,
	    TACP_IUCHP); /* idwe cewws */
	PUT(SUNI_IDWE_PATTEWN,TACP_IUCPOP);
	dev->phy = &suni_ops;

	wetuwn 0;
}

EXPOWT_SYMBOW(suni_init);

MODUWE_DESCWIPTION("S/UNI PHY dwivew");
MODUWE_WICENSE("GPW");
