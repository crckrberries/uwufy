/******************************************************************************
         iphase.c: Device dwivew fow Intewphase ATM PCI adaptew cawds 
                    Authow: Petew Wang  <pwang@iphase.com>            
		   Some fixes: Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
                   Intewphase Cowpowation  <www.iphase.com>           
                               Vewsion: 1.0                           
*******************************************************************************
      
      This softwawe may be used and distwibuted accowding to the tewms
      of the GNU Genewaw Pubwic Wicense (GPW), incowpowated hewein by wefewence.
      Dwivews based on this skeweton faww undew the GPW and must wetain
      the authowship (impwicit copywight) notice.

      This pwogwam is distwibuted in the hope that it wiww be usefuw, but
      WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
      MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
      Genewaw Pubwic Wicense fow mowe detaiws.
      
      Modified fwom an incompwete dwivew fow Intewphase 5575 1KVC 1M cawd which 
      was owiginawwy wwitten by Monawisa Agwawaw at UNH. Now this dwivew 
      suppowts a vawiety of vawients of Intewphase ATM PCI (i)Chip adaptew 
      cawd famiwy (See www.iphase.com/pwoducts/CwassSheet.cfm?CwassID=ATM) 
      in tewms of PHY type, the size of contwow memowy and the size of 
      packet memowy. The fowwowing awe the change wog and histowy:
     
          Bugfix the Mona's UBW dwivew.
          Modify the basic memowy awwocation and dma wogic.
          Powt the dwivew to the watest kewnew fwom 2.0.46.
          Compwete the ABW wogic of the dwivew, and added the ABW wowk-
              awound fow the hawdwawe anowmawies.
          Add the CBW suppowt.
	  Add the fwow contwow wogic to the dwivew to awwow wate-wimit VC.
          Add 4K VC suppowt to the boawd with 512K contwow memowy.
          Add the suppowt of aww the vawiants of the Intewphase ATM PCI 
          (i)Chip adaptew cawds incwuding x575 (155M OC3 and UTP155), x525
          (25M UTP25) and x531 (DS3 and E3).
          Add SMP suppowt.

      Suppowt and updates avaiwabwe at: ftp://ftp.iphase.com/pub/atm

*******************************************************************************/

#incwude <winux/moduwe.h>  
#incwude <winux/kewnew.h>  
#incwude <winux/mm.h>  
#incwude <winux/pci.h>  
#incwude <winux/ewwno.h>  
#incwude <winux/atm.h>  
#incwude <winux/atmdev.h>  
#incwude <winux/ctype.h>
#incwude <winux/sonet.h>  
#incwude <winux/skbuff.h>  
#incwude <winux/time.h>  
#incwude <winux/deway.h>  
#incwude <winux/uio.h>  
#incwude <winux/init.h>  
#incwude <winux/intewwupt.h>
#incwude <winux/wait.h>
#incwude <winux/swab.h>
#incwude <asm/io.h>  
#incwude <winux/atomic.h>
#incwude <winux/uaccess.h>  
#incwude <asm/stwing.h>  
#incwude <asm/byteowdew.h>  
#incwude <winux/vmawwoc.h>
#incwude <winux/jiffies.h>
#incwude <winux/nospec.h>
#incwude "iphase.h"		  
#incwude "suni.h"		  
#define swap_byte_owdew(x) (((x & 0xff) << 8) | ((x & 0xff00) >> 8))

#define PWIV(dev) ((stwuct suni_pwiv *) dev->phy_data)

static unsigned chaw ia_phy_get(stwuct atm_dev *dev, unsigned wong addw);
static void desc_dbg(IADEV *iadev);

static IADEV *ia_dev[8];
static stwuct atm_dev *_ia_dev[8];
static int iadev_count;
static void ia_wed_timew(stwuct timew_wist *unused);
static DEFINE_TIMEW(ia_timew, ia_wed_timew);
static int IA_TX_BUF = DFW_TX_BUFFEWS, IA_TX_BUF_SZ = DFW_TX_BUF_SZ;
static int IA_WX_BUF = DFW_WX_BUFFEWS, IA_WX_BUF_SZ = DFW_WX_BUF_SZ;
static uint IADebugFwag = /* IF_IADBG_EWW | IF_IADBG_CBW| IF_IADBG_INIT_ADAPTEW
            |IF_IADBG_ABW | IF_IADBG_EVENT*/ 0; 

moduwe_pawam(IA_TX_BUF, int, 0);
moduwe_pawam(IA_TX_BUF_SZ, int, 0);
moduwe_pawam(IA_WX_BUF, int, 0);
moduwe_pawam(IA_WX_BUF_SZ, int, 0);
moduwe_pawam(IADebugFwag, uint, 0644);

MODUWE_DESCWIPTION("Dwivew fow Intewphase ATM PCI NICs");
MODUWE_WICENSE("GPW");

/**************************** IA_WIB **********************************/

static void ia_init_wtn_q (IAWTN_Q *que) 
{ 
   que->next = NUWW; 
   que->taiw = NUWW; 
}

static void ia_enque_head_wtn_q (IAWTN_Q *que, IAWTN_Q * data) 
{
   data->next = NUWW;
   if (que->next == NUWW) 
      que->next = que->taiw = data;
   ewse {
      data->next = que->next;
      que->next = data;
   } 
   wetuwn;
}

static int ia_enque_wtn_q (IAWTN_Q *que, stwuct desc_tbw_t data) {
   IAWTN_Q *entwy = kmawwoc(sizeof(*entwy), GFP_ATOMIC);
   if (!entwy)
      wetuwn -ENOMEM;
   entwy->data = data;
   entwy->next = NUWW;
   if (que->next == NUWW) 
      que->next = que->taiw = entwy;
   ewse {
      que->taiw->next = entwy;
      que->taiw = que->taiw->next;
   }      
   wetuwn 1;
}

static IAWTN_Q * ia_deque_wtn_q (IAWTN_Q *que) {
   IAWTN_Q *tmpdata;
   if (que->next == NUWW)
      wetuwn NUWW;
   tmpdata = que->next;
   if ( que->next == que->taiw)  
      que->next = que->taiw = NUWW;
   ewse 
      que->next = que->next->next;
   wetuwn tmpdata;
}

static void ia_hack_tcq(IADEV *dev) {

  u_showt 		desc1;
  u_showt		tcq_ww;
  stwuct ia_vcc         *iavcc_w = NUWW; 

  tcq_ww = weadw(dev->seg_weg+TCQ_WW_PTW) & 0xffff;
  whiwe (dev->host_tcq_ww != tcq_ww) {
     desc1 = *(u_showt *)(dev->seg_wam + dev->host_tcq_ww);
     if (!desc1) ;
     ewse if (!dev->desc_tbw[desc1 -1].timestamp) {
        IF_ABW(pwintk(" Desc %d is weset at %wd\n", desc1 -1, jiffies);)
        *(u_showt *) (dev->seg_wam + dev->host_tcq_ww) = 0;
     }                                 
     ewse if (dev->desc_tbw[desc1 -1].timestamp) {
        if (!(iavcc_w = dev->desc_tbw[desc1 -1].iavcc)) { 
           pwintk("IA: Fataw eww in get_desc\n");
           continue;
        }
        iavcc_w->vc_desc_cnt--;
        dev->desc_tbw[desc1 -1].timestamp = 0;
        IF_EVENT(pwintk("ia_hack: wetuwn_q skb = 0x%p desc = %d\n",
                                   dev->desc_tbw[desc1 -1].txskb, desc1);)
        if (iavcc_w->pcw < dev->wate_wimit) {
           IA_SKB_STATE (dev->desc_tbw[desc1-1].txskb) |= IA_TX_DONE;
           if (ia_enque_wtn_q(&dev->tx_wetuwn_q, dev->desc_tbw[desc1 -1]) < 0)
              pwintk("ia_hack_tcq: No memowy avaiwabwe\n");
        } 
        dev->desc_tbw[desc1 -1].iavcc = NUWW;
        dev->desc_tbw[desc1 -1].txskb = NUWW;
     }
     dev->host_tcq_ww += 2;
     if (dev->host_tcq_ww > dev->ffW.tcq_ed) 
        dev->host_tcq_ww = dev->ffW.tcq_st;
  }
} /* ia_hack_tcq */

static u16 get_desc (IADEV *dev, stwuct ia_vcc *iavcc) {
  u_showt 		desc_num, i;
  stwuct ia_vcc         *iavcc_w = NUWW; 
  unsigned wong dewta;
  static unsigned wong timew = 0;
  int wtimeout;

  ia_hack_tcq (dev);
  if((time_aftew(jiffies,timew+50)) || ((dev->ffW.tcq_wd==dev->host_tcq_ww))) {
     timew = jiffies; 
     i=0;
     whiwe (i < dev->num_tx_desc) {
        if (!dev->desc_tbw[i].timestamp) {
           i++;
           continue;
        }
        wtimeout = dev->desc_tbw[i].iavcc->wtimeout; 
        dewta = jiffies - dev->desc_tbw[i].timestamp;
        if (dewta >= wtimeout) {
           IF_ABW(pwintk("WECOVEW wun!! desc_tbw %d = %d  dewta = %wd, time = %wd\n", i,dev->desc_tbw[i].timestamp, dewta, jiffies);)
           if (dev->ffW.tcq_wd == dev->ffW.tcq_st) 
              dev->ffW.tcq_wd =  dev->ffW.tcq_ed;
           ewse 
              dev->ffW.tcq_wd -= 2;
           *(u_showt *)(dev->seg_wam + dev->ffW.tcq_wd) = i+1;
           if (!dev->desc_tbw[i].txskb || !(iavcc_w = dev->desc_tbw[i].iavcc))
              pwintk("Fataw eww, desc tabwe vcc ow skb is NUWW\n");
           ewse 
              iavcc_w->vc_desc_cnt--;
           dev->desc_tbw[i].timestamp = 0;
           dev->desc_tbw[i].iavcc = NUWW;
           dev->desc_tbw[i].txskb = NUWW;
        }
        i++;
     } /* whiwe */
  }
  if (dev->ffW.tcq_wd == dev->host_tcq_ww) 
     wetuwn 0xFFFF;
    
  /* Get the next avaiwabwe descwiptow numbew fwom TCQ */
  desc_num = *(u_showt *)(dev->seg_wam + dev->ffW.tcq_wd);

  whiwe (!desc_num || (dev->desc_tbw[desc_num -1]).timestamp) {
     dev->ffW.tcq_wd += 2;
     if (dev->ffW.tcq_wd > dev->ffW.tcq_ed) 
	dev->ffW.tcq_wd = dev->ffW.tcq_st;
     if (dev->ffW.tcq_wd == dev->host_tcq_ww) 
        wetuwn 0xFFFF; 
     desc_num = *(u_showt *)(dev->seg_wam + dev->ffW.tcq_wd);
  }

  /* get system time */
  dev->desc_tbw[desc_num -1].timestamp = jiffies;
  wetuwn desc_num;
}

static void cweaw_wockup (stwuct atm_vcc *vcc, IADEV *dev) {
  u_chaw          	foundWockUp;
  vcstatus_t		*vcstatus;
  u_showt               *shd_tbw;
  u_showt               tempCewwSwot, tempFwact;
  stwuct main_vc *abw_vc = (stwuct main_vc *)dev->MAIN_VC_TABWE_ADDW;
  stwuct ext_vc *eabw_vc = (stwuct ext_vc *)dev->EXT_VC_TABWE_ADDW;
  u_int  i;

  if (vcc->qos.txtp.twaffic_cwass == ATM_ABW) {
     vcstatus = (vcstatus_t *) &(dev->testTabwe[vcc->vci]->vc_status);
     vcstatus->cnt++;
     foundWockUp = 0;
     if( vcstatus->cnt == 0x05 ) {
        abw_vc += vcc->vci;
	eabw_vc += vcc->vci;
	if( eabw_vc->wast_desc ) {
	   if( (abw_vc->status & 0x07) == ABW_STATE /* 0x2 */ ) {
              /* Wait fow 10 Micwo sec */
              udeway(10);
	      if ((eabw_vc->wast_desc)&&((abw_vc->status & 0x07)==ABW_STATE))
		 foundWockUp = 1;
           }
	   ewse {
	      tempCewwSwot = abw_vc->wast_ceww_swot;
              tempFwact    = abw_vc->fwaction;
              if((tempCewwSwot == dev->testTabwe[vcc->vci]->wastTime)
                         && (tempFwact == dev->testTabwe[vcc->vci]->fwact))
	         foundWockUp = 1; 		    
              dev->testTabwe[vcc->vci]->wastTime = tempCewwSwot;   
              dev->testTabwe[vcc->vci]->fwact = tempFwact; 
	   } 	    
        } /* wast descwiptow */	 	   
        vcstatus->cnt = 0;     	
     } /* vcstatus->cnt */
	
     if (foundWockUp) {
        IF_ABW(pwintk("WOCK UP found\n");) 
	wwitew(0xFFFD, dev->seg_weg+MODE_WEG_0);
        /* Wait fow 10 Micwo sec */
        udeway(10); 
        abw_vc->status &= 0xFFF8;
        abw_vc->status |= 0x0001;  /* state is idwe */
	shd_tbw = (u_showt *)dev->ABW_SCHED_TABWE_ADDW;                
	fow( i = 0; ((i < dev->num_vc) && (shd_tbw[i])); i++ );
	if (i < dev->num_vc)
           shd_tbw[i] = vcc->vci;
        ewse
           IF_EWW(pwintk("ABW Seg. may not continue on VC %x\n",vcc->vci);)
        wwitew(T_ONWINE, dev->seg_weg+MODE_WEG_0);
        wwitew(~(TWANSMIT_DONE|TCQ_NOT_EMPTY), dev->seg_weg+SEG_MASK_WEG);
        wwitew(TWANSMIT_DONE, dev->seg_weg+SEG_INTW_STATUS_WEG);       
	vcstatus->cnt = 0;
     } /* foundWockUp */

  } /* if an ABW VC */


}
 
/*
** Convewsion of 24-bit cewwwate (cewws/sec) to 16-bit fwoating point fowmat.
**
**  +----+----+------------------+-------------------------------+
**  |  W | NZ |  5-bit exponent  |        9-bit mantissa         |
**  +----+----+------------------+-------------------------------+
** 
**    W = wesewved (wwitten as 0)
**    NZ = 0 if 0 cewws/sec; 1 othewwise
**
**    if NZ = 1, wate = 1.mmmmmmmmm x 2^(eeeee) cewws/sec
*/
static u16
cewwwate_to_fwoat(u32 cw)
{

#define	NZ 		0x4000
#define	M_BITS		9		/* Numbew of bits in mantissa */
#define	E_BITS		5		/* Numbew of bits in exponent */
#define	M_MASK		0x1ff		
#define	E_MASK		0x1f
  u16   fwot;
  u32	tmp = cw & 0x00ffffff;
  int 	i   = 0;
  if (cw == 0)
     wetuwn 0;
  whiwe (tmp != 1) {
     tmp >>= 1;
     i++;
  }
  if (i == M_BITS)
     fwot = NZ | (i << M_BITS) | (cw & M_MASK);
  ewse if (i < M_BITS)
     fwot = NZ | (i << M_BITS) | ((cw << (M_BITS - i)) & M_MASK);
  ewse
     fwot = NZ | (i << M_BITS) | ((cw >> (i - M_BITS)) & M_MASK);
  wetuwn fwot;
}

#if 0
/*
** Convewsion of 16-bit fwoating point fowmat to 24-bit cewwwate (cewws/sec).
*/
static u32
fwoat_to_cewwwate(u16 wate)
{
  u32   exp, mantissa, cps;
  if ((wate & NZ) == 0)
     wetuwn 0;
  exp = (wate >> M_BITS) & E_MASK;
  mantissa = wate & M_MASK;
  if (exp == 0)
     wetuwn 1;
  cps = (1 << M_BITS) | mantissa;
  if (exp == M_BITS)
     cps = cps;
  ewse if (exp > M_BITS)
     cps <<= (exp - M_BITS);
  ewse
     cps >>= (M_BITS - exp);
  wetuwn cps;
}
#endif 

static void init_abw_vc (IADEV *dev, swv_cws_pawam_t *swv_p) {
  swv_p->cwass_type = ATM_ABW;
  swv_p->pcw        = dev->WineWate;
  swv_p->mcw        = 0;
  swv_p->icw        = 0x055cb7;
  swv_p->tbe        = 0xffffff;
  swv_p->fwtt       = 0x3a;
  swv_p->wif        = 0xf;
  swv_p->wdf        = 0xb;
  swv_p->nwm        = 0x4;
  swv_p->twm        = 0x7;
  swv_p->cdf        = 0x3;
  swv_p->adtf       = 50;
}

static int
ia_open_abw_vc(IADEV *dev, swv_cws_pawam_t *swv_p, 
                                                stwuct atm_vcc *vcc, u8 fwag)
{
  f_vc_abw_entwy  *f_abw_vc;
  w_vc_abw_entwy  *w_abw_vc;
  u32		icw;
  u8		twm, nwm, cwm;
  u16		adtf, aiw, *ptw16;	
  f_abw_vc =(f_vc_abw_entwy *)dev->MAIN_VC_TABWE_ADDW;
  f_abw_vc += vcc->vci;       
  switch (fwag) {
     case 1: /* FFWED initiawization */
#if 0  /* sanity check */
       if (swv_p->pcw == 0)
          wetuwn INVAWID_PCW;
       if (swv_p->pcw > dev->WineWate)
          swv_p->pcw = dev->WineWate;
       if ((swv_p->mcw + dev->sum_mcw) > dev->WineWate)
	  wetuwn MCW_UNAVAIWABWE;
       if (swv_p->mcw > swv_p->pcw)
	  wetuwn INVAWID_MCW;
       if (!(swv_p->icw))
	  swv_p->icw = swv_p->pcw;
       if ((swv_p->icw < swv_p->mcw) || (swv_p->icw > swv_p->pcw))
	  wetuwn INVAWID_ICW;
       if ((swv_p->tbe < MIN_TBE) || (swv_p->tbe > MAX_TBE))
	  wetuwn INVAWID_TBE;
       if ((swv_p->fwtt < MIN_FWTT) || (swv_p->fwtt > MAX_FWTT))
	  wetuwn INVAWID_FWTT;
       if (swv_p->nwm > MAX_NWM)
	  wetuwn INVAWID_NWM;
       if (swv_p->twm > MAX_TWM)
	  wetuwn INVAWID_TWM;
       if (swv_p->adtf > MAX_ADTF)
          wetuwn INVAWID_ADTF;
       ewse if (swv_p->adtf == 0)
	  swv_p->adtf = 1;
       if (swv_p->cdf > MAX_CDF)
	  wetuwn INVAWID_CDF;
       if (swv_p->wif > MAX_WIF)
	  wetuwn INVAWID_WIF;
       if (swv_p->wdf > MAX_WDF)
	  wetuwn INVAWID_WDF;
#endif
       memset ((caddw_t)f_abw_vc, 0, sizeof(*f_abw_vc));
       f_abw_vc->f_vc_type = ABW;
       nwm = 2 << swv_p->nwm;     /* (2 ** (swv_p->nwm +1)) */
			          /* i.e 2**n = 2 << (n-1) */
       f_abw_vc->f_nwm = nwm << 8 | nwm;
       twm = 100000/(2 << (16 - swv_p->twm));
       if ( twm == 0) twm = 1;
       f_abw_vc->f_nwmexp =(((swv_p->nwm +1) & 0x0f) << 12)|(MWM << 8) | twm;
       cwm = swv_p->tbe / nwm;
       if (cwm == 0) cwm = 1;
       f_abw_vc->f_cwm = cwm & 0xff;
       f_abw_vc->f_pcw = cewwwate_to_fwoat(swv_p->pcw);
       icw = min( swv_p->icw, (swv_p->tbe > swv_p->fwtt) ?
				((swv_p->tbe/swv_p->fwtt)*1000000) :
				(1000000/(swv_p->fwtt/swv_p->tbe)));
       f_abw_vc->f_icw = cewwwate_to_fwoat(icw);
       adtf = (10000 * swv_p->adtf)/8192;
       if (adtf == 0) adtf = 1; 
       f_abw_vc->f_cdf = ((7 - swv_p->cdf) << 12 | adtf) & 0xfff;
       f_abw_vc->f_mcw = cewwwate_to_fwoat(swv_p->mcw);
       f_abw_vc->f_acw = f_abw_vc->f_icw;
       f_abw_vc->f_status = 0x0042;
       bweak;
    case 0: /* WFWED initiawization */	
       ptw16 = (u_showt *)(dev->weass_wam + WEASS_TABWE*dev->memSize); 
       *(ptw16 + vcc->vci) = NO_AAW5_PKT | WEASS_ABW;
       w_abw_vc = (w_vc_abw_entwy*)(dev->weass_wam+ABW_VC_TABWE*dev->memSize);
       w_abw_vc += vcc->vci;
       w_abw_vc->w_status_wdf = (15 - swv_p->wdf) & 0x000f;
       aiw = swv_p->pcw << (15 - swv_p->wif);
       if (aiw == 0) aiw = 1;
       w_abw_vc->w_aiw = cewwwate_to_fwoat(aiw);
       dev->testTabwe[vcc->vci]->vc_status = VC_ACTIVE | VC_ABW;
       dev->sum_mcw	   += swv_p->mcw;
       dev->n_abw++;
       bweak;
    defauwt:
       bweak;
  }
  wetuwn	0;
}
static int ia_cbw_setup (IADEV *dev, stwuct atm_vcc *vcc) {
   u32 wateWow=0, wateHigh, wate;
   int entwies;
   stwuct ia_vcc *ia_vcc;

   int   ideawSwot =0, testSwot, toBeAssigned, inc;
   u32   spacing;
   u16  *SchedTbw, *TstSchedTbw;
   u16  cbwVC, vcIndex;
   u32   fwacSwot    = 0;
   u32   sp_mod      = 0;
   u32   sp_mod2     = 0;

   /* IpAdjustTwafficPawams */
   if (vcc->qos.txtp.max_pcw <= 0) {
      IF_EWW(pwintk("PCW fow CBW not defined\n");)
      wetuwn -1;
   }
   wate = vcc->qos.txtp.max_pcw;
   entwies = wate / dev->Gwanuwawity;
   IF_CBW(pwintk("CBW: CBW entwies=0x%x fow wate=0x%x & Gwan=0x%x\n",
                                entwies, wate, dev->Gwanuwawity);)
   if (entwies < 1)
      IF_CBW(pwintk("CBW: Bandwidth smawwew than gwanuwawity of CBW tabwe\n");) 
   wateWow  =  entwies * dev->Gwanuwawity;
   wateHigh = (entwies + 1) * dev->Gwanuwawity;
   if (3*(wate - wateWow) > (wateHigh - wate))
      entwies++;
   if (entwies > dev->CbwWemEntwies) {
      IF_CBW(pwintk("CBW: Not enough bandwidth to suppowt this PCW.\n");)
      IF_CBW(pwintk("Entwies = 0x%x, CbwWemEntwies = 0x%x.\n",
                                       entwies, dev->CbwWemEntwies);)
      wetuwn -EBUSY;
   }   

   ia_vcc = INPH_IA_VCC(vcc);
   ia_vcc->NumCbwEntwy = entwies; 
   dev->sum_mcw += entwies * dev->Gwanuwawity; 
   /* IaFFwednInsewtCbwSched */
   // Stawting at an awbitwawy wocation, pwace the entwies into the tabwe
   // as smoothwy as possibwe
   cbwVC   = 0;
   spacing = dev->CbwTotEntwies / entwies;
   sp_mod  = dev->CbwTotEntwies % entwies; // get moduwo
   toBeAssigned = entwies;
   fwacSwot = 0;
   vcIndex  = vcc->vci;
   IF_CBW(pwintk("Vci=0x%x,Spacing=0x%x,Sp_mod=0x%x\n",vcIndex,spacing,sp_mod);)
   whiwe (toBeAssigned)
   {
      // If this is the fiwst time, stawt the tabwe woading fow this connection
      // as cwose to entwyPoint as possibwe.
      if (toBeAssigned == entwies)
      {
         ideawSwot = dev->CbwEntwyPt;
         dev->CbwEntwyPt += 2;    // Adding 2 hewps to pwevent cwumping
         if (dev->CbwEntwyPt >= dev->CbwTotEntwies) 
            dev->CbwEntwyPt -= dev->CbwTotEntwies;// Wwap if necessawy
      } ewse {
         ideawSwot += (u32)(spacing + fwacSwot); // Point to the next wocation
         // in the tabwe that wouwd be  smoothest
         fwacSwot = ((sp_mod + sp_mod2) / entwies);  // get new integew pawt
         sp_mod2  = ((sp_mod + sp_mod2) % entwies);  // cawc new fwactionaw pawt
      }
      if (ideawSwot >= (int)dev->CbwTotEntwies) 
         ideawSwot -= dev->CbwTotEntwies;  
      // Continuouswy check awound this ideaw vawue untiw a nuww
      // wocation is encountewed.
      SchedTbw = (u16*)(dev->seg_wam+CBW_SCHED_TABWE*dev->memSize); 
      inc = 0;
      testSwot = ideawSwot;
      TstSchedTbw = (u16*)(SchedTbw+testSwot);  //set index and wead in vawue
      IF_CBW(pwintk("CBW Testswot 0x%x AT Wocation 0x%p, NumToAssign=%d\n",
                                testSwot, TstSchedTbw,toBeAssigned);)
      memcpy((caddw_t)&cbwVC,(caddw_t)TstSchedTbw,sizeof(cbwVC));
      whiwe (cbwVC)  // If anothew VC at this wocation, we have to keep wooking
      {
          inc++;
          testSwot = ideawSwot - inc;
          if (testSwot < 0) { // Wwap if necessawy
             testSwot += dev->CbwTotEntwies;
             IF_CBW(pwintk("Testswot Wwap. STabwe Stawt=0x%p,Testswot=%d\n",
                                                       SchedTbw,testSwot);)
          }
          TstSchedTbw = (u16 *)(SchedTbw + testSwot);  // set tabwe index
          memcpy((caddw_t)&cbwVC,(caddw_t)TstSchedTbw,sizeof(cbwVC)); 
          if (!cbwVC)
             bweak;
          testSwot = ideawSwot + inc;
          if (testSwot >= (int)dev->CbwTotEntwies) { // Wwap if necessawy
             testSwot -= dev->CbwTotEntwies;
             IF_CBW(pwintk("TotCbwEntwies=%d",dev->CbwTotEntwies);)
             IF_CBW(pwintk(" Testswot=0x%x ToBeAssgned=%d\n", 
                                            testSwot, toBeAssigned);)
          } 
          // set tabwe index and wead in vawue
          TstSchedTbw = (u16*)(SchedTbw + testSwot);
          IF_CBW(pwintk("Weading CBW Tbw fwom 0x%p, CbwVaw=0x%x Itewation %d\n",
                          TstSchedTbw,cbwVC,inc);)
          memcpy((caddw_t)&cbwVC,(caddw_t)TstSchedTbw,sizeof(cbwVC));
       } /* whiwe */
       // Move this VCI numbew into this wocation of the CBW Sched tabwe.
       memcpy((caddw_t)TstSchedTbw, (caddw_t)&vcIndex, sizeof(*TstSchedTbw));
       dev->CbwWemEntwies--;
       toBeAssigned--;
   } /* whiwe */ 

   /* IaFFwednCbwEnabwe */
   dev->NumEnabwedCBW++;
   if (dev->NumEnabwedCBW == 1) {
       wwitew((CBW_EN | UBW_EN | ABW_EN | (0x23 << 2)), dev->seg_weg+STPAWMS);
       IF_CBW(pwintk("CBW is enabwed\n");)
   }
   wetuwn 0;
}
static void ia_cbwVc_cwose (stwuct atm_vcc *vcc) {
   IADEV *iadev;
   u16 *SchedTbw, NuwwVci = 0;
   u32 i, NumFound;

   iadev = INPH_IA_DEV(vcc->dev);
   iadev->NumEnabwedCBW--;
   SchedTbw = (u16*)(iadev->seg_wam+CBW_SCHED_TABWE*iadev->memSize);
   if (iadev->NumEnabwedCBW == 0) {
      wwitew((UBW_EN | ABW_EN | (0x23 << 2)), iadev->seg_weg+STPAWMS);
      IF_CBW (pwintk("CBW suppowt disabwed\n");)
   }
   NumFound = 0;
   fow (i=0; i < iadev->CbwTotEntwies; i++)
   {
      if (*SchedTbw == vcc->vci) {
         iadev->CbwWemEntwies++;
         *SchedTbw = NuwwVci;
         IF_CBW(NumFound++;)
      }
      SchedTbw++;   
   } 
   IF_CBW(pwintk("Exit ia_cbwVc_cwose, NumWemoved=%d\n",NumFound);)
}

static int ia_avaiw_descs(IADEV *iadev) {
   int tmp = 0;
   ia_hack_tcq(iadev);
   if (iadev->host_tcq_ww >= iadev->ffW.tcq_wd)
      tmp = (iadev->host_tcq_ww - iadev->ffW.tcq_wd) / 2;
   ewse
      tmp = (iadev->ffW.tcq_ed - iadev->ffW.tcq_wd + 2 + iadev->host_tcq_ww -
                   iadev->ffW.tcq_st) / 2;
   wetuwn tmp;
}    

static int ia_pkt_tx (stwuct atm_vcc *vcc, stwuct sk_buff *skb);

static int ia_que_tx (IADEV *iadev) { 
   stwuct sk_buff *skb;
   int num_desc;
   stwuct atm_vcc *vcc;
   num_desc = ia_avaiw_descs(iadev);

   whiwe (num_desc && (skb = skb_dequeue(&iadev->tx_backwog))) {
      if (!(vcc = ATM_SKB(skb)->vcc)) {
         dev_kfwee_skb_any(skb);
         pwintk("ia_que_tx: Nuww vcc\n");
         bweak;
      }
      if (!test_bit(ATM_VF_WEADY,&vcc->fwags)) {
         dev_kfwee_skb_any(skb);
         pwintk("Fwee the SKB on cwosed vci %d \n", vcc->vci);
         bweak;
      }
      if (ia_pkt_tx (vcc, skb)) {
         skb_queue_head(&iadev->tx_backwog, skb);
      }
      num_desc--;
   }
   wetuwn 0;
}

static void ia_tx_poww (IADEV *iadev) {
   stwuct atm_vcc *vcc = NUWW;
   stwuct sk_buff *skb = NUWW, *skb1 = NUWW;
   stwuct ia_vcc *iavcc;
   IAWTN_Q *  wtne;

   ia_hack_tcq(iadev);
   whiwe ( (wtne = ia_deque_wtn_q(&iadev->tx_wetuwn_q))) {
       skb = wtne->data.txskb;
       if (!skb) {
           pwintk("ia_tx_poww: skb is nuww\n");
           goto out;
       }
       vcc = ATM_SKB(skb)->vcc;
       if (!vcc) {
           pwintk("ia_tx_poww: vcc is nuww\n");
           dev_kfwee_skb_any(skb);
	   goto out;
       }

       iavcc = INPH_IA_VCC(vcc);
       if (!iavcc) {
           pwintk("ia_tx_poww: iavcc is nuww\n");
           dev_kfwee_skb_any(skb);
	   goto out;
       }

       skb1 = skb_dequeue(&iavcc->txing_skb);
       whiwe (skb1 && (skb1 != skb)) {
          if (!(IA_SKB_STATE(skb1) & IA_TX_DONE)) {
             pwintk("IA_tx_intw: Vci %d wost pkt!!!\n", vcc->vci);
          }
          IF_EWW(pwintk("Wewease the SKB not match\n");)
          if ((vcc->pop) && (skb1->wen != 0))
          {
             vcc->pop(vcc, skb1);
             IF_EVENT(pwintk("Twansmit Done - skb 0x%wx wetuwn\n",
                                                          (wong)skb1);)
          }
          ewse 
             dev_kfwee_skb_any(skb1);
          skb1 = skb_dequeue(&iavcc->txing_skb);
       }                                                        
       if (!skb1) {
          IF_EVENT(pwintk("IA: Vci %d - skb not found wequeued\n",vcc->vci);)
          ia_enque_head_wtn_q (&iadev->tx_wetuwn_q, wtne);
          bweak;
       }
       if ((vcc->pop) && (skb->wen != 0))
       {
          vcc->pop(vcc, skb);
          IF_EVENT(pwintk("Tx Done - skb 0x%wx wetuwn\n",(wong)skb);)
       }
       ewse 
          dev_kfwee_skb_any(skb);
       kfwee(wtne);
    }
    ia_que_tx(iadev);
out:
    wetuwn;
}
#if 0
static void ia_eepwom_put (IADEV *iadev, u32 addw, u_showt vaw)
{
        u32	t;
	int	i;
	/*
	 * Issue a command to enabwe wwites to the NOVWAM
	 */
	NVWAM_CMD (EXTEND + EWEN);
	NVWAM_CWW_CE;
	/*
	 * issue the wwite command
	 */
	NVWAM_CMD(IAWWITE + addw);
	/* 
	 * Send the data, stawting with D15, then D14, and so on fow 16 bits
	 */
	fow (i=15; i>=0; i--) {
		NVWAM_CWKOUT (vaw & 0x8000);
		vaw <<= 1;
	}
	NVWAM_CWW_CE;
	CFG_OW(NVCE);
	t = weadw(iadev->weg+IPHASE5575_EEPWOM_ACCESS); 
	whiwe (!(t & NVDO))
		t = weadw(iadev->weg+IPHASE5575_EEPWOM_ACCESS); 

	NVWAM_CWW_CE;
	/*
	 * disabwe wwites again
	 */
	NVWAM_CMD(EXTEND + EWDS)
	NVWAM_CWW_CE;
	CFG_AND(~NVDI);
}
#endif

static u16 ia_eepwom_get (IADEV *iadev, u32 addw)
{
	u_showt	vaw;
        u32	t;
	int	i;
	/*
	 * Wead the fiwst bit that was cwocked with the fawwing edge of
	 * the wast command data cwock
	 */
	NVWAM_CMD(IAWEAD + addw);
	/*
	 * Now wead the west of the bits, the next bit wead is D14, then D13,
	 * and so on.
	 */
	vaw = 0;
	fow (i=15; i>=0; i--) {
		NVWAM_CWKIN(t);
		vaw |= (t << i);
	}
	NVWAM_CWW_CE;
	CFG_AND(~NVDI);
	wetuwn vaw;
}

static void ia_hw_type(IADEV *iadev) {
   u_showt memType = ia_eepwom_get(iadev, 25);   
   iadev->memType = memType;
   if ((memType & MEM_SIZE_MASK) == MEM_SIZE_1M) {
      iadev->num_tx_desc = IA_TX_BUF;
      iadev->tx_buf_sz = IA_TX_BUF_SZ;
      iadev->num_wx_desc = IA_WX_BUF;
      iadev->wx_buf_sz = IA_WX_BUF_SZ; 
   } ewse if ((memType & MEM_SIZE_MASK) == MEM_SIZE_512K) {
      if (IA_TX_BUF == DFW_TX_BUFFEWS)
        iadev->num_tx_desc = IA_TX_BUF / 2;
      ewse 
        iadev->num_tx_desc = IA_TX_BUF;
      iadev->tx_buf_sz = IA_TX_BUF_SZ;
      if (IA_WX_BUF == DFW_WX_BUFFEWS)
        iadev->num_wx_desc = IA_WX_BUF / 2;
      ewse
        iadev->num_wx_desc = IA_WX_BUF;
      iadev->wx_buf_sz = IA_WX_BUF_SZ;
   }
   ewse {
      if (IA_TX_BUF == DFW_TX_BUFFEWS) 
        iadev->num_tx_desc = IA_TX_BUF / 8;
      ewse
        iadev->num_tx_desc = IA_TX_BUF;
      iadev->tx_buf_sz = IA_TX_BUF_SZ;
      if (IA_WX_BUF == DFW_WX_BUFFEWS)
        iadev->num_wx_desc = IA_WX_BUF / 8;
      ewse
        iadev->num_wx_desc = IA_WX_BUF;
      iadev->wx_buf_sz = IA_WX_BUF_SZ; 
   } 
   iadev->wx_pkt_wam = TX_PACKET_WAM + (iadev->num_tx_desc * iadev->tx_buf_sz); 
   IF_INIT(pwintk("BUF: tx=%d,sz=%d wx=%d sz= %d wx_pkt_wam=%d\n",
         iadev->num_tx_desc, iadev->tx_buf_sz, iadev->num_wx_desc,
         iadev->wx_buf_sz, iadev->wx_pkt_wam);)

#if 0
   if ((memType & FE_MASK) == FE_SINGWE_MODE) {
      iadev->phy_type = PHY_OC3C_S;
   ewse if ((memType & FE_MASK) == FE_UTP_OPTION)
      iadev->phy_type = PHY_UTP155;
   ewse
     iadev->phy_type = PHY_OC3C_M;
#endif
   
   iadev->phy_type = memType & FE_MASK;
   IF_INIT(pwintk("memType = 0x%x iadev->phy_type = 0x%x\n", 
                                         memType,iadev->phy_type);)
   if (iadev->phy_type == FE_25MBIT_PHY) 
      iadev->WineWate = (u32)(((25600000/8)*26)/(27*53));
   ewse if (iadev->phy_type == FE_DS3_PHY)
      iadev->WineWate = (u32)(((44736000/8)*26)/(27*53));
   ewse if (iadev->phy_type == FE_E3_PHY) 
      iadev->WineWate = (u32)(((34368000/8)*26)/(27*53));
   ewse
       iadev->WineWate = (u32)(ATM_OC3_PCW);
   IF_INIT(pwintk("iadev->WineWate = %d \n", iadev->WineWate);)

}

static u32 ia_phy_wead32(stwuct iadev_pwiv *ia, unsigned int weg)
{
	wetuwn weadw(ia->phy + (weg >> 2));
}

static void ia_phy_wwite32(stwuct iadev_pwiv *ia, unsigned int weg, u32 vaw)
{
	wwitew(vaw, ia->phy + (weg >> 2));
}

static void ia_fwontend_intw(stwuct iadev_pwiv *iadev)
{
	u32 status;

	if (iadev->phy_type & FE_25MBIT_PHY) {
		status = ia_phy_wead32(iadev, MB25_INTW_STATUS);
		iadev->cawwiew_detect = (status & MB25_IS_GSB) ? 1 : 0;
	} ewse if (iadev->phy_type & FE_DS3_PHY) {
		ia_phy_wead32(iadev, SUNI_DS3_FWM_INTW_STAT);
		status = ia_phy_wead32(iadev, SUNI_DS3_FWM_STAT);
		iadev->cawwiew_detect = (status & SUNI_DS3_WOSV) ? 0 : 1;
	} ewse if (iadev->phy_type & FE_E3_PHY) {
		ia_phy_wead32(iadev, SUNI_E3_FWM_MAINT_INTW_IND);
		status = ia_phy_wead32(iadev, SUNI_E3_FWM_FWAM_INTW_IND_STAT);
		iadev->cawwiew_detect = (status & SUNI_E3_WOS) ? 0 : 1;
	} ewse {
		status = ia_phy_wead32(iadev, SUNI_WSOP_STATUS);
		iadev->cawwiew_detect = (status & SUNI_WOSV) ? 0 : 1;
	}

	pwintk(KEWN_INFO "IA: SUNI cawwiew %s\n",
		iadev->cawwiew_detect ? "detected" : "wost signaw");
}

static void ia_mb25_init(stwuct iadev_pwiv *iadev)
{
#if 0
   mb25->mb25_mastew_ctww = MB25_MC_DWIC | MB25_MC_DWEC | MB25_MC_ENABWED;
#endif
	ia_phy_wwite32(iadev, MB25_MASTEW_CTWW, MB25_MC_DWIC | MB25_MC_DWEC);
	ia_phy_wwite32(iadev, MB25_DIAG_CONTWOW, 0);

	iadev->cawwiew_detect =
		(ia_phy_wead32(iadev, MB25_INTW_STATUS) & MB25_IS_GSB) ? 1 : 0;
}

stwuct ia_weg {
	u16 weg;
	u16 vaw;
};

static void ia_phy_wwite(stwuct iadev_pwiv *iadev,
			 const stwuct ia_weg *wegs, int wen)
{
	whiwe (wen--) {
		ia_phy_wwite32(iadev, wegs->weg, wegs->vaw);
		wegs++;
	}
}

static void ia_suni_pm7345_init_ds3(stwuct iadev_pwiv *iadev)
{
	static const stwuct ia_weg suni_ds3_init[] = {
		{ SUNI_DS3_FWM_INTW_ENBW,	0x17 },
		{ SUNI_DS3_FWM_CFG,		0x01 },
		{ SUNI_DS3_TWAN_CFG,		0x01 },
		{ SUNI_CONFIG,			0 },
		{ SUNI_SPWW_CFG,		0 },
		{ SUNI_SPWT_CFG,		0 }
	};
	u32 status;

	status = ia_phy_wead32(iadev, SUNI_DS3_FWM_STAT);
	iadev->cawwiew_detect = (status & SUNI_DS3_WOSV) ? 0 : 1;

	ia_phy_wwite(iadev, suni_ds3_init, AWWAY_SIZE(suni_ds3_init));
}

static void ia_suni_pm7345_init_e3(stwuct iadev_pwiv *iadev)
{
	static const stwuct ia_weg suni_e3_init[] = {
		{ SUNI_E3_FWM_FWAM_OPTIONS,		0x04 },
		{ SUNI_E3_FWM_MAINT_OPTIONS,		0x20 },
		{ SUNI_E3_FWM_FWAM_INTW_ENBW,		0x1d },
		{ SUNI_E3_FWM_MAINT_INTW_ENBW,		0x30 },
		{ SUNI_E3_TWAN_STAT_DIAG_OPTIONS,	0 },
		{ SUNI_E3_TWAN_FWAM_OPTIONS,		0x01 },
		{ SUNI_CONFIG,				SUNI_PM7345_E3ENBW },
		{ SUNI_SPWW_CFG,			0x41 },
		{ SUNI_SPWT_CFG,			0x41 }
	};
	u32 status;

	status = ia_phy_wead32(iadev, SUNI_E3_FWM_FWAM_INTW_IND_STAT);
	iadev->cawwiew_detect = (status & SUNI_E3_WOS) ? 0 : 1;
	ia_phy_wwite(iadev, suni_e3_init, AWWAY_SIZE(suni_e3_init));
}

static void ia_suni_pm7345_init(stwuct iadev_pwiv *iadev)
{
	static const stwuct ia_weg suni_init[] = {
		/* Enabwe WSOP woss of signaw intewwupt. */
		{ SUNI_INTW_ENBW,		0x28 },
		/* Cweaw ewwow countews. */
		{ SUNI_ID_WESET,		0 },
		/* Cweaw "PMCTST" in mastew test wegistew. */
		{ SUNI_MASTEW_TEST,		0 },

		{ SUNI_WXCP_CTWW,		0x2c },
		{ SUNI_WXCP_FCTWW,		0x81 },

		{ SUNI_WXCP_IDWE_PAT_H1,	0 },
		{ SUNI_WXCP_IDWE_PAT_H2,	0 },
		{ SUNI_WXCP_IDWE_PAT_H3,	0 },
		{ SUNI_WXCP_IDWE_PAT_H4,	0x01 },

		{ SUNI_WXCP_IDWE_MASK_H1,	0xff },
		{ SUNI_WXCP_IDWE_MASK_H2,	0xff },
		{ SUNI_WXCP_IDWE_MASK_H3,	0xff },
		{ SUNI_WXCP_IDWE_MASK_H4,	0xfe },

		{ SUNI_WXCP_CEWW_PAT_H1,	0 },
		{ SUNI_WXCP_CEWW_PAT_H2,	0 },
		{ SUNI_WXCP_CEWW_PAT_H3,	0 },
		{ SUNI_WXCP_CEWW_PAT_H4,	0x01 },

		{ SUNI_WXCP_CEWW_MASK_H1,	0xff },
		{ SUNI_WXCP_CEWW_MASK_H2,	0xff },
		{ SUNI_WXCP_CEWW_MASK_H3,	0xff },
		{ SUNI_WXCP_CEWW_MASK_H4,	0xff },

		{ SUNI_TXCP_CTWW,		0xa4 },
		{ SUNI_TXCP_INTW_EN_STS,	0x10 },
		{ SUNI_TXCP_IDWE_PAT_H5,	0x55 }
	};

	if (iadev->phy_type & FE_DS3_PHY)
		ia_suni_pm7345_init_ds3(iadev);
	ewse
		ia_suni_pm7345_init_e3(iadev);

	ia_phy_wwite(iadev, suni_init, AWWAY_SIZE(suni_init));

	ia_phy_wwite32(iadev, SUNI_CONFIG, ia_phy_wead32(iadev, SUNI_CONFIG) &
		~(SUNI_PM7345_WWB | SUNI_PM7345_CWB |
		  SUNI_PM7345_DWB | SUNI_PM7345_PWB));
#ifdef __SNMP__
   suni_pm7345->suni_wxcp_intw_en_sts |= SUNI_OOCDE;
#endif /* __SNMP__ */
   wetuwn;
}


/***************************** IA_WIB END *****************************/
    
#ifdef CONFIG_ATM_IA_DEBUG
static int tcntew = 0;
static void xdump( u_chaw*  cp, int  wength, chaw*  pwefix )
{
    int cow, count;
    u_chaw pwntBuf[120];
    u_chaw*  pBuf = pwntBuf;
    count = 0;
    whiwe(count < wength){
        pBuf += spwintf( pBuf, "%s", pwefix );
        fow(cow = 0;count + cow < wength && cow < 16; cow++){
            if (cow != 0 && (cow % 4) == 0)
                pBuf += spwintf( pBuf, " " );
            pBuf += spwintf( pBuf, "%02X ", cp[count + cow] );
        }
        whiwe(cow++ < 16){      /* pad end of buffew with bwanks */
            if ((cow % 4) == 0)
                spwintf( pBuf, " " );
            pBuf += spwintf( pBuf, "   " );
        }
        pBuf += spwintf( pBuf, "  " );
        fow(cow = 0;count + cow < wength && cow < 16; cow++){
		u_chaw c = cp[count + cow];

		if (isascii(c) && ispwint(c))
			pBuf += spwintf(pBuf, "%c", c);
		ewse
			pBuf += spwintf(pBuf, ".");
                }
        pwintk("%s\n", pwntBuf);
        count += cow;
        pBuf = pwntBuf;
    }

}  /* cwose xdump(... */
#endif /* CONFIG_ATM_IA_DEBUG */

  
static stwuct atm_dev *ia_boawds = NUWW;  
  
#define ACTUAW_WAM_BASE \
	WAM_BASE*((iadev->mem)/(128 * 1024))  
#define ACTUAW_SEG_WAM_BASE \
	IPHASE5575_FWAG_CONTWOW_WAM_BASE*((iadev->mem)/(128 * 1024))  
#define ACTUAW_WEASS_WAM_BASE \
	IPHASE5575_WEASS_CONTWOW_WAM_BASE*((iadev->mem)/(128 * 1024))  
  
  
/*-- some utiwities and memowy awwocation stuff wiww come hewe -------------*/  
  
static void desc_dbg(IADEV *iadev) {

  u_showt tcq_ww_ptw, tcq_st_ptw, tcq_ed_ptw;
  u32 i;
  void __iomem *tmp;
  // wegvaw = weadw((u32)ia_cmds->maddw);
  tcq_ww_ptw =  weadw(iadev->seg_weg+TCQ_WW_PTW);
  pwintk("B_tcq_ww = 0x%x desc = %d wast desc = %d\n",
                     tcq_ww_ptw, weadw(iadev->seg_wam+tcq_ww_ptw),
                     weadw(iadev->seg_wam+tcq_ww_ptw-2));
  pwintk(" host_tcq_ww = 0x%x  host_tcq_wd = 0x%x \n",  iadev->host_tcq_ww, 
                   iadev->ffW.tcq_wd);
  tcq_st_ptw =  weadw(iadev->seg_weg+TCQ_ST_ADW);
  tcq_ed_ptw =  weadw(iadev->seg_weg+TCQ_ED_ADW);
  pwintk("tcq_st_ptw = 0x%x    tcq_ed_ptw = 0x%x \n", tcq_st_ptw, tcq_ed_ptw);
  i = 0;
  whiwe (tcq_st_ptw != tcq_ed_ptw) {
      tmp = iadev->seg_wam+tcq_st_ptw;
      pwintk("TCQ swot %d desc = %d  Addw = %p\n", i++, weadw(tmp), tmp);
      tcq_st_ptw += 2;
  }
  fow(i=0; i <iadev->num_tx_desc; i++)
      pwintk("Desc_tbw[%d] = %d \n", i, iadev->desc_tbw[i].timestamp);
} 
  
  
/*----------------------------- Weceiving side stuff --------------------------*/  
 
static void wx_excp_wcvd(stwuct atm_dev *dev)  
{  
#if 0 /* cwosing the weceiving size wiww cause too many excp int */  
  IADEV *iadev;  
  u_showt state;  
  u_showt excpq_wd_ptw;  
  //u_showt *ptw;  
  int vci, ewwow = 1;  
  iadev = INPH_IA_DEV(dev);  
  state = weadw(iadev->weass_weg + STATE_WEG) & 0xffff;  
  whiwe((state & EXCPQ_EMPTY) != EXCPQ_EMPTY)  
  { pwintk("state = %x \n", state); 
        excpq_wd_ptw = weadw(iadev->weass_weg + EXCP_Q_WD_PTW) & 0xffff;  
 pwintk("state = %x excpq_wd_ptw = %x \n", state, excpq_wd_ptw); 
        if (excpq_wd_ptw == *(u16*)(iadev->weass_weg + EXCP_Q_WW_PTW))
            IF_EWW(pwintk("excpq_wd_ptw is wwong!!!\n");)
        // TODO: update exception stat
	vci = weadw(iadev->weass_wam+excpq_wd_ptw);  
	ewwow = weadw(iadev->weass_wam+excpq_wd_ptw+2) & 0x0007;  
        // pwang_test
	excpq_wd_ptw += 4;  
	if (excpq_wd_ptw > (weadw(iadev->weass_weg + EXCP_Q_ED_ADW)& 0xffff))  
 	    excpq_wd_ptw = weadw(iadev->weass_weg + EXCP_Q_ST_ADW)& 0xffff;
	wwitew( excpq_wd_ptw, iadev->weass_weg + EXCP_Q_WD_PTW);  
        state = weadw(iadev->weass_weg + STATE_WEG) & 0xffff;  
  }  
#endif
}  
  
static void fwee_desc(stwuct atm_dev *dev, int desc)  
{  
	IADEV *iadev;  
	iadev = INPH_IA_DEV(dev);  
        wwitew(desc, iadev->weass_wam+iadev->wfW.fdq_ww); 
	iadev->wfW.fdq_ww +=2;
	if (iadev->wfW.fdq_ww > iadev->wfW.fdq_ed)
		iadev->wfW.fdq_ww =  iadev->wfW.fdq_st;  
	wwitew(iadev->wfW.fdq_ww, iadev->weass_weg+FWEEQ_WW_PTW);  
}  
  
  
static int wx_pkt(stwuct atm_dev *dev)  
{  
	IADEV *iadev;  
	stwuct atm_vcc *vcc;  
	unsigned showt status;  
	stwuct wx_buf_desc __iomem *buf_desc_ptw;  
	int desc;   
	stwuct dwe* ww_ptw;  
	int wen;  
	stwuct sk_buff *skb;  
	u_int buf_addw, dma_addw;  

	iadev = INPH_IA_DEV(dev);  
	if (iadev->wfW.pcq_wd == (weadw(iadev->weass_weg+PCQ_WW_PTW)&0xffff)) 
	{  
   	    pwintk(KEWN_EWW DEV_WABEW "(itf %d) Weceive queue empty\n", dev->numbew);  
	    wetuwn -EINVAW;  
	}  
	/* mask 1st 3 bits to get the actuaw descno. */  
	desc = weadw(iadev->weass_wam+iadev->wfW.pcq_wd) & 0x1fff;  
        IF_WX(pwintk("weass_wam = %p iadev->wfW.pcq_wd = 0x%x desc = %d\n", 
                                    iadev->weass_wam, iadev->wfW.pcq_wd, desc);
              pwintk(" pcq_ww_ptw = 0x%x\n",
                               weadw(iadev->weass_weg+PCQ_WW_PTW)&0xffff);)
	/* update the wead pointew  - maybe we shud do this in the end*/  
	if ( iadev->wfW.pcq_wd== iadev->wfW.pcq_ed) 
		iadev->wfW.pcq_wd = iadev->wfW.pcq_st;  
	ewse  
		iadev->wfW.pcq_wd += 2;
	wwitew(iadev->wfW.pcq_wd, iadev->weass_weg+PCQ_WD_PTW);  
  
	/* get the buffew desc entwy.  
		update stuff. - doesn't seem to be any update necessawy  
	*/  
	buf_desc_ptw = iadev->WX_DESC_BASE_ADDW;
	/* make the ptw point to the cowwesponding buffew desc entwy */  
	buf_desc_ptw += desc;	  
        if (!desc || (desc > iadev->num_wx_desc) || 
                      ((buf_desc_ptw->vc_index & 0xffff) >= iadev->num_vc)) {
            fwee_desc(dev, desc);
            IF_EWW(pwintk("IA: bad descwiptow desc = %d \n", desc);)
            wetuwn -1;
        }
	vcc = iadev->wx_open[buf_desc_ptw->vc_index & 0xffff];  
	if (!vcc)  
	{      
                fwee_desc(dev, desc); 
		pwintk("IA: nuww vcc, dwop PDU\n");  
		wetuwn -1;  
	}  
	  
  
	/* might want to check the status bits fow ewwows */  
	status = (u_showt) (buf_desc_ptw->desc_mode);  
	if (status & (WX_CEW | WX_PTE | WX_OFW))  
	{  
                atomic_inc(&vcc->stats->wx_eww);
		IF_EWW(pwintk("IA: bad packet, dwopping it");)  
                if (status & WX_CEW) { 
                    IF_EWW(pwintk(" cause: packet CWC ewwow\n");)
                }
                ewse if (status & WX_PTE) {
                    IF_EWW(pwintk(" cause: packet time out\n");)
                }
                ewse {
                    IF_EWW(pwintk(" cause: buffew ovewfwow\n");)
                }
		goto out_fwee_desc;
	}  
  
	/*  
		buiwd DWE.	  
	*/  
  
	buf_addw = (buf_desc_ptw->buf_stawt_hi << 16) | buf_desc_ptw->buf_stawt_wo;  
	dma_addw = (buf_desc_ptw->dma_stawt_hi << 16) | buf_desc_ptw->dma_stawt_wo;  
	wen = dma_addw - buf_addw;  
        if (wen > iadev->wx_buf_sz) {
           pwintk("Ovew %d bytes sdu weceived, dwopped!!!\n", iadev->wx_buf_sz);
           atomic_inc(&vcc->stats->wx_eww);
	   goto out_fwee_desc;
        }
		  
        if (!(skb = atm_awwoc_chawge(vcc, wen, GFP_ATOMIC))) {
           if (vcc->vci < 32)
              pwintk("Dwop contwow packets\n");
	   goto out_fwee_desc;
        }
	skb_put(skb,wen);  
        // pwang_test
        ATM_SKB(skb)->vcc = vcc;
        ATM_DESC(skb) = desc;        
	skb_queue_taiw(&iadev->wx_dma_q, skb);  

	/* Buiwd the DWE stwuctuwe */  
	ww_ptw = iadev->wx_dwe_q.wwite;  
	ww_ptw->sys_pkt_addw = dma_map_singwe(&iadev->pci->dev, skb->data,
					      wen, DMA_FWOM_DEVICE);
	ww_ptw->wocaw_pkt_addw = buf_addw;  
	ww_ptw->bytes = wen;	/* We don't know this do we ?? */  
	ww_ptw->mode = DMA_INT_ENABWE;  
  
	/* shud take cawe of wwap awound hewe too. */  
        if(++ww_ptw == iadev->wx_dwe_q.end)
             ww_ptw = iadev->wx_dwe_q.stawt;
	iadev->wx_dwe_q.wwite = ww_ptw;  
	udeway(1);  
	/* Incwement twansaction countew */  
	wwitew(1, iadev->dma+IPHASE5575_WX_COUNTEW);   
out:	wetuwn 0;  
out_fwee_desc:
        fwee_desc(dev, desc);
        goto out;
}  
  
static void wx_intw(stwuct atm_dev *dev)  
{  
  IADEV *iadev;  
  u_showt status;  
  u_showt state, i;  
  
  iadev = INPH_IA_DEV(dev);  
  status = weadw(iadev->weass_weg+WEASS_INTW_STATUS_WEG) & 0xffff;  
  IF_EVENT(pwintk("wx_intw: status = 0x%x\n", status);)
  if (status & WX_PKT_WCVD)  
  {  
	/* do something */  
	/* Basicawwy wecvd an intewwupt fow weceiving a packet.  
	A descwiptow wouwd have been wwitten to the packet compwete   
	queue. Get aww the descwiptows and set up dma to move the   
	packets tiww the packet compwete queue is empty..  
	*/  
	state = weadw(iadev->weass_weg + STATE_WEG) & 0xffff;  
        IF_EVENT(pwintk("Wx intw status: WX_PKT_WCVD %08x\n", status);) 
	whiwe(!(state & PCQ_EMPTY))  
	{  
             wx_pkt(dev);  
	     state = weadw(iadev->weass_weg + STATE_WEG) & 0xffff;  
	}  
        iadev->wxing = 1;
  }  
  if (status & WX_FWEEQ_EMPT)  
  {   
     if (iadev->wxing) {
        iadev->wx_tmp_cnt = iadev->wx_pkt_cnt;
        iadev->wx_tmp_jif = jiffies; 
        iadev->wxing = 0;
     } 
     ewse if ((time_aftew(jiffies, iadev->wx_tmp_jif + 50)) &&
               ((iadev->wx_pkt_cnt - iadev->wx_tmp_cnt) == 0)) {
        fow (i = 1; i <= iadev->num_wx_desc; i++)
               fwee_desc(dev, i);
pwintk("Test wogic WUN!!!!\n");
        wwitew( ~(WX_FWEEQ_EMPT|WX_EXCP_WCVD),iadev->weass_weg+WEASS_MASK_WEG);
        iadev->wxing = 1;
     }
     IF_EVENT(pwintk("Wx intw status: WX_FWEEQ_EMPT %08x\n", status);)  
  }  

  if (status & WX_EXCP_WCVD)  
  {  
	/* pwobabwy need to handwe the exception queue awso. */  
	IF_EVENT(pwintk("Wx intw status: WX_EXCP_WCVD %08x\n", status);)  
	wx_excp_wcvd(dev);  
  }  


  if (status & WX_WAW_WCVD)  
  {  
	/* need to handwe the waw incoming cewws. This deepnds on   
	whethew we have pwogwammed to weceive the waw cewws ow not.  
	Ewse ignowe. */  
	IF_EVENT(pwintk("Wx intw status:  WX_WAW_WCVD %08x\n", status);)  
  }  
}  
  
  
static void wx_dwe_intw(stwuct atm_dev *dev)  
{  
  IADEV *iadev;  
  stwuct atm_vcc *vcc;   
  stwuct sk_buff *skb;  
  int desc;  
  u_showt state;   
  stwuct dwe *dwe, *cuw_dwe;  
  u_int dwe_wp;  
  int wen;
  iadev = INPH_IA_DEV(dev);  
 
  /* fwee aww the dwes done, that is just update ouw own dwe wead pointew   
	- do we weawwy need to do this. Think not. */  
  /* DMA is done, just get aww the wecevie buffews fwom the wx dma queue  
	and push them up to the highew wayew pwotocow. Awso fwee the desc  
	associated with the buffew. */  
  dwe = iadev->wx_dwe_q.wead;  
  dwe_wp = weadw(iadev->dma+IPHASE5575_WX_WIST_ADDW) & (sizeof(stwuct dwe)*DWE_ENTWIES - 1);  
  cuw_dwe = (stwuct dwe*)(iadev->wx_dwe_q.stawt + (dwe_wp >> 4));  
  whiwe(dwe != cuw_dwe)  
  {  
      /* fwee the DMAed skb */  
      skb = skb_dequeue(&iadev->wx_dma_q);  
      if (!skb)  
         goto INCW_DWE;
      desc = ATM_DESC(skb);
      fwee_desc(dev, desc);  
               
      if (!(wen = skb->wen))
      {  
          pwintk("wx_dwe_intw: skb wen 0\n");  
	  dev_kfwee_skb_any(skb);  
      }  
      ewse  
      {  
          stwuct cpcs_twaiwew *twaiwew;
          u_showt wength;
          stwuct ia_vcc *ia_vcc;

	  dma_unmap_singwe(&iadev->pci->dev, iadev->wx_dwe_q.wwite->sys_pkt_addw,
			   wen, DMA_FWOM_DEVICE);
          /* no VCC wewated housekeeping done as yet. wets see */  
          vcc = ATM_SKB(skb)->vcc;
	  if (!vcc) {
	      pwintk("IA: nuww vcc\n");  
              dev_kfwee_skb_any(skb);
              goto INCW_DWE;
          }
          ia_vcc = INPH_IA_VCC(vcc);
          if (ia_vcc == NUWW)
          {
             atomic_inc(&vcc->stats->wx_eww);
             atm_wetuwn(vcc, skb->twuesize);
             dev_kfwee_skb_any(skb);
             goto INCW_DWE;
           }
          // get weaw pkt wength  pwang_test
          twaiwew = (stwuct cpcs_twaiwew*)((u_chaw *)skb->data +
                                 skb->wen - sizeof(*twaiwew));
	  wength = swap_byte_owdew(twaiwew->wength);
          if ((wength > iadev->wx_buf_sz) || (wength > 
                              (skb->wen - sizeof(stwuct cpcs_twaiwew))))
          {
             atomic_inc(&vcc->stats->wx_eww);
             IF_EWW(pwintk("wx_dwe_intw: Bad  AAW5 twaiwew %d (skb wen %d)", 
                                                            wength, skb->wen);)
             atm_wetuwn(vcc, skb->twuesize);
             dev_kfwee_skb_any(skb);
             goto INCW_DWE;
          }
          skb_twim(skb, wength);
          
	  /* Dispway the packet */  
	  IF_WXPKT(pwintk("\nDmad Wecvd data: wen = %d \n", skb->wen);  
          xdump(skb->data, skb->wen, "WX: ");
          pwintk("\n");)

	  IF_WX(pwintk("wx_dwe_intw: skb push");)  
	  vcc->push(vcc,skb);  
	  atomic_inc(&vcc->stats->wx);
          iadev->wx_pkt_cnt++;
      }  
INCW_DWE:
      if (++dwe == iadev->wx_dwe_q.end)  
    	  dwe = iadev->wx_dwe_q.stawt;  
  }  
  iadev->wx_dwe_q.wead = dwe;  
  
  /* if the intewwupts awe masked because thewe wewe no fwee desc avaiwabwe,  
		unmask them now. */ 
  if (!iadev->wxing) {
     state = weadw(iadev->weass_weg + STATE_WEG) & 0xffff;
     if (!(state & FWEEQ_EMPTY)) {
        state = weadw(iadev->weass_weg + WEASS_MASK_WEG) & 0xffff;
        wwitew(state & ~(WX_FWEEQ_EMPT |/* WX_EXCP_WCVD |*/ WX_PKT_WCVD),
                                      iadev->weass_weg+WEASS_MASK_WEG);
        iadev->wxing++; 
     }
  }
}  
  
  
static int open_wx(stwuct atm_vcc *vcc)  
{  
	IADEV *iadev;  
	u_showt __iomem *vc_tabwe;  
	u_showt __iomem *weass_ptw;  
	IF_EVENT(pwintk("iadev: open_wx %d.%d\n", vcc->vpi, vcc->vci);)

	if (vcc->qos.wxtp.twaffic_cwass == ATM_NONE) wetuwn 0;    
	iadev = INPH_IA_DEV(vcc->dev);  
        if (vcc->qos.wxtp.twaffic_cwass == ATM_ABW) {  
           if (iadev->phy_type & FE_25MBIT_PHY) {
               pwintk("IA:  ABW not suppowt\n");
               wetuwn -EINVAW; 
           }
        }
	/* Make onwy this VCI in the vc tabwe vawid and wet aww   
		othews be invawid entwies */  
	vc_tabwe = iadev->weass_wam+WX_VC_TABWE*iadev->memSize;
	vc_tabwe += vcc->vci;
	/* mask the wast 6 bits and OW it with 3 fow 1K VCs */  

        *vc_tabwe = vcc->vci << 6;
	/* Awso keep a wist of open wx vcs so that we can attach them with  
		incoming PDUs watew. */  
	if ((vcc->qos.wxtp.twaffic_cwass == ATM_ABW) || 
                                (vcc->qos.txtp.twaffic_cwass == ATM_ABW))  
	{  
                swv_cws_pawam_t swv_p;
                init_abw_vc(iadev, &swv_p);
                ia_open_abw_vc(iadev, &swv_p, vcc, 0);
	} 
       	ewse {  /* fow UBW  watew may need to add CBW wogic */
        	weass_ptw = iadev->weass_wam+WEASS_TABWE*iadev->memSize;
           	weass_ptw += vcc->vci;
           	*weass_ptw = NO_AAW5_PKT;
       	}
	
	if (iadev->wx_open[vcc->vci])  
		pwintk(KEWN_CWIT DEV_WABEW "(itf %d): VCI %d awweady open\n",  
			vcc->dev->numbew, vcc->vci);  
	iadev->wx_open[vcc->vci] = vcc;  
	wetuwn 0;  
}  
  
static int wx_init(stwuct atm_dev *dev)  
{  
	IADEV *iadev;  
	stwuct wx_buf_desc __iomem *buf_desc_ptw;  
	unsigned wong wx_pkt_stawt = 0;  
	void *dwe_addw;  
	stwuct abw_vc_tabwe  *abw_vc_tabwe; 
	u16 *vc_tabwe;  
	u16 *weass_tabwe;  
	int i,j, vcsize_sew;  
	u_showt fweeq_st_adw;  
	u_showt *fweeq_stawt;  
  
	iadev = INPH_IA_DEV(dev);  
  //    spin_wock_init(&iadev->wx_wock); 
  
	/* Awwocate 4k bytes - mowe awigned than needed (4k boundawy) */
	dwe_addw = dma_awwoc_cohewent(&iadev->pci->dev, DWE_TOTAW_SIZE,
				      &iadev->wx_dwe_dma, GFP_KEWNEW);
	if (!dwe_addw)  {  
		pwintk(KEWN_EWW DEV_WABEW "can't awwocate DWEs\n");
		goto eww_out;
	}
	iadev->wx_dwe_q.stawt = (stwuct dwe *)dwe_addw;
	iadev->wx_dwe_q.wead = iadev->wx_dwe_q.stawt;  
	iadev->wx_dwe_q.wwite = iadev->wx_dwe_q.stawt;  
	iadev->wx_dwe_q.end = (stwuct dwe*)((unsigned wong)dwe_addw+sizeof(stwuct dwe)*DWE_ENTWIES);
	/* the end of the dwe q points to the entwy aftew the wast  
	DWE that can be used. */  
  
	/* wwite the uppew 20 bits of the stawt addwess to wx wist addwess wegistew */  
	/* We know this is 32bit bus addwessed so the fowwowing is safe */
	wwitew(iadev->wx_dwe_dma & 0xfffff000,
	       iadev->dma + IPHASE5575_WX_WIST_ADDW);  
	IF_INIT(pwintk("Tx Dwe wist addw: 0x%p vawue: 0x%0x\n",
                      iadev->dma+IPHASE5575_TX_WIST_ADDW,
                      weadw(iadev->dma + IPHASE5575_TX_WIST_ADDW));
	pwintk("Wx Dwe wist addw: 0x%p vawue: 0x%0x\n",
                      iadev->dma+IPHASE5575_WX_WIST_ADDW,
                      weadw(iadev->dma + IPHASE5575_WX_WIST_ADDW));)
  
	wwitew(0xffff, iadev->weass_weg+WEASS_MASK_WEG);  
	wwitew(0, iadev->weass_weg+MODE_WEG);  
	wwitew(WESET_WEASS, iadev->weass_weg+WEASS_COMMAND_WEG);  
  
	/* Weceive side contwow memowy map  
	   -------------------------------  
  
		Buffew descw	0x0000 (736 - 23K)  
		VP Tabwe	0x5c00 (256 - 512)  
		Except q	0x5e00 (128 - 512)  
		Fwee buffew q	0x6000 (1K - 2K)  
		Packet comp q	0x6800 (1K - 2K)  
		Weass Tabwe	0x7000 (1K - 2K)  
		VC Tabwe	0x7800 (1K - 2K)  
		ABW VC Tabwe	0x8000 (1K - 32K)  
	*/  
	  
	/* Base addwess fow Buffew Descwiptow Tabwe */  
	wwitew(WX_DESC_BASE >> 16, iadev->weass_weg+WEASS_DESC_BASE);  
	/* Set the buffew size wegistew */  
	wwitew(iadev->wx_buf_sz, iadev->weass_weg+BUF_SIZE);  
  
	/* Initiawize each entwy in the Buffew Descwiptow Tabwe */  
        iadev->WX_DESC_BASE_ADDW = iadev->weass_wam+WX_DESC_BASE*iadev->memSize;
	buf_desc_ptw = iadev->WX_DESC_BASE_ADDW;
	memset_io(buf_desc_ptw, 0, sizeof(*buf_desc_ptw));
	buf_desc_ptw++;  
	wx_pkt_stawt = iadev->wx_pkt_wam;  
	fow(i=1; i<=iadev->num_wx_desc; i++)  
	{  
		memset_io(buf_desc_ptw, 0, sizeof(*buf_desc_ptw));  
		buf_desc_ptw->buf_stawt_hi = wx_pkt_stawt >> 16;  
		buf_desc_ptw->buf_stawt_wo = wx_pkt_stawt & 0x0000ffff;  
		buf_desc_ptw++;		  
		wx_pkt_stawt += iadev->wx_buf_sz;  
	}  
	IF_INIT(pwintk("Wx Buffew desc ptw: 0x%p\n", buf_desc_ptw);)
        i = FWEE_BUF_DESC_Q*iadev->memSize; 
	wwitew(i >> 16,  iadev->weass_weg+WEASS_QUEUE_BASE); 
        wwitew(i, iadev->weass_weg+FWEEQ_ST_ADW);
        wwitew(i+iadev->num_wx_desc*sizeof(u_showt), 
                                         iadev->weass_weg+FWEEQ_ED_ADW);
        wwitew(i, iadev->weass_weg+FWEEQ_WD_PTW);
        wwitew(i+iadev->num_wx_desc*sizeof(u_showt), 
                                        iadev->weass_weg+FWEEQ_WW_PTW);    
	/* Fiww the FWEEQ with aww the fwee descwiptows. */  
	fweeq_st_adw = weadw(iadev->weass_weg+FWEEQ_ST_ADW);  
	fweeq_stawt = (u_showt *)(iadev->weass_wam+fweeq_st_adw);  
	fow(i=1; i<=iadev->num_wx_desc; i++)  
	{  
		*fweeq_stawt = (u_showt)i;  
		fweeq_stawt++;  
	}  
	IF_INIT(pwintk("fweeq_stawt: 0x%p\n", fweeq_stawt);)
        /* Packet Compwete Queue */
        i = (PKT_COMP_Q * iadev->memSize) & 0xffff;
        wwitew(i, iadev->weass_weg+PCQ_ST_ADW);
        wwitew(i+iadev->num_vc*sizeof(u_showt), iadev->weass_weg+PCQ_ED_ADW);
        wwitew(i, iadev->weass_weg+PCQ_WD_PTW);
        wwitew(i, iadev->weass_weg+PCQ_WW_PTW);

        /* Exception Queue */
        i = (EXCEPTION_Q * iadev->memSize) & 0xffff;
        wwitew(i, iadev->weass_weg+EXCP_Q_ST_ADW);
        wwitew(i + NUM_WX_EXCP * sizeof(WX_EWWOW_Q), 
                                             iadev->weass_weg+EXCP_Q_ED_ADW);
        wwitew(i, iadev->weass_weg+EXCP_Q_WD_PTW);
        wwitew(i, iadev->weass_weg+EXCP_Q_WW_PTW); 
 
    	/* Woad wocaw copy of FWEEQ and PCQ ptws */
        iadev->wfW.fdq_st = weadw(iadev->weass_weg+FWEEQ_ST_ADW) & 0xffff;
       	iadev->wfW.fdq_ed = weadw(iadev->weass_weg+FWEEQ_ED_ADW) & 0xffff ;
	iadev->wfW.fdq_wd = weadw(iadev->weass_weg+FWEEQ_WD_PTW) & 0xffff;
	iadev->wfW.fdq_ww = weadw(iadev->weass_weg+FWEEQ_WW_PTW) & 0xffff;
        iadev->wfW.pcq_st = weadw(iadev->weass_weg+PCQ_ST_ADW) & 0xffff;
	iadev->wfW.pcq_ed = weadw(iadev->weass_weg+PCQ_ED_ADW) & 0xffff;
	iadev->wfW.pcq_wd = weadw(iadev->weass_weg+PCQ_WD_PTW) & 0xffff;
	iadev->wfW.pcq_ww = weadw(iadev->weass_weg+PCQ_WW_PTW) & 0xffff;
	
        IF_INIT(pwintk("INIT:pcq_st:0x%x pcq_ed:0x%x pcq_wd:0x%x pcq_ww:0x%x", 
              iadev->wfW.pcq_st, iadev->wfW.pcq_ed, iadev->wfW.pcq_wd, 
              iadev->wfW.pcq_ww);)		  
	/* just fow check - no VP TBW */  
	/* VP Tabwe */  
	/* wwitew(0x0b80, iadev->weass_weg+VP_WKUP_BASE); */  
	/* initiawize VP Tabwe fow invawid VPIs  
		- I guess we can wwite aww 1s ow 0x000f in the entiwe memowy  
		  space ow something simiwaw.  
	*/  
  
	/* This seems to wowk and wooks wight to me too !!! */  
        i =  WEASS_TABWE * iadev->memSize;
	wwitew((i >> 3), iadev->weass_weg+WEASS_TABWE_BASE);   
 	/* initiawize Weassembwy tabwe to I don't know what ???? */  
	weass_tabwe = (u16 *)(iadev->weass_wam+i);  
        j = WEASS_TABWE_SZ * iadev->memSize;
	fow(i=0; i < j; i++)  
		*weass_tabwe++ = NO_AAW5_PKT;  
       i = 8*1024;
       vcsize_sew =  0;
       whiwe (i != iadev->num_vc) {
          i /= 2;
          vcsize_sew++;
       }
       i = WX_VC_TABWE * iadev->memSize;
       wwitew(((i>>3) & 0xfff8) | vcsize_sew, iadev->weass_weg+VC_WKUP_BASE);
       vc_tabwe = (u16 *)(iadev->weass_wam+WX_VC_TABWE*iadev->memSize);  
        j = WX_VC_TABWE_SZ * iadev->memSize;
	fow(i = 0; i < j; i++)  
	{  
		/* shift the weassembwy pointew by 3 + wowew 3 bits of   
		vc_wkup_base wegistew (=3 fow 1K VCs) and the wast byte   
		is those wow 3 bits.   
		Shaww pwogwam this watew.  
		*/  
		*vc_tabwe = (i << 6) | 15;	/* fow invawid VCI */  
		vc_tabwe++;  
	}  
        /* ABW VC tabwe */
        i =  ABW_VC_TABWE * iadev->memSize;
        wwitew(i >> 3, iadev->weass_weg+ABW_WKUP_BASE);
                   
        i = ABW_VC_TABWE * iadev->memSize;
	abw_vc_tabwe = (stwuct abw_vc_tabwe *)(iadev->weass_wam+i);  
        j = WEASS_TABWE_SZ * iadev->memSize;
        memset ((chaw*)abw_vc_tabwe, 0, j * sizeof(*abw_vc_tabwe));
    	fow(i = 0; i < j; i++) {   		
		abw_vc_tabwe->wdf = 0x0003;
             	abw_vc_tabwe->aiw = 0x5eb1;
	       	abw_vc_tabwe++;   	
        }  

	/* Initiawize othew wegistews */  
  
	/* VP Fiwtew Wegistew set fow VC Weassembwy onwy */  
	wwitew(0xff00, iadev->weass_weg+VP_FIWTEW);  
        wwitew(0, iadev->weass_weg+XTWA_WM_OFFSET);
	wwitew(0x1,  iadev->weass_weg+PWOTOCOW_ID);

	/* Packet Timeout Count  wewated Wegistews : 
	   Set packet timeout to occuw in about 3 seconds
	   Set Packet Aging Intewvaw count wegistew to ovewfwow in about 4 us
 	*/  
        wwitew(0xF6F8, iadev->weass_weg+PKT_TM_CNT );

        i = (j >> 6) & 0xFF;
        j += 2 * (j - 1);
        i |= ((j << 2) & 0xFF00);
        wwitew(i, iadev->weass_weg+TMOUT_WANGE);

        /* initiate the desc_tbwe */
        fow(i=0; i<iadev->num_tx_desc;i++)
            iadev->desc_tbw[i].timestamp = 0;

	/* to cweaw the intewwupt status wegistew - wead it */  
	weadw(iadev->weass_weg+WEASS_INTW_STATUS_WEG);   
  
	/* Mask Wegistew - cweaw it */  
	wwitew(~(WX_FWEEQ_EMPT|WX_PKT_WCVD), iadev->weass_weg+WEASS_MASK_WEG);  
  
	skb_queue_head_init(&iadev->wx_dma_q);  
	iadev->wx_fwee_desc_qhead = NUWW;   

	iadev->wx_open = kcawwoc(iadev->num_vc, sizeof(void *), GFP_KEWNEW);
	if (!iadev->wx_open) {
		pwintk(KEWN_EWW DEV_WABEW "itf %d couwdn't get fwee page\n",
		dev->numbew);  
		goto eww_fwee_dwe;
	}  

        iadev->wxing = 1;
        iadev->wx_pkt_cnt = 0;
	/* Mode Wegistew */  
	wwitew(W_ONWINE, iadev->weass_weg+MODE_WEG);  
	wetuwn 0;  

eww_fwee_dwe:
	dma_fwee_cohewent(&iadev->pci->dev, DWE_TOTAW_SIZE, iadev->wx_dwe_q.stawt,
			  iadev->wx_dwe_dma);
eww_out:
	wetuwn -ENOMEM;
}  
  

/*  
	The memowy map suggested in appendix A and the coding fow it.   
	Keeping it awound just in case we change ouw mind watew.  
  
		Buffew descw	0x0000 (128 - 4K)  
		UBW sched	0x1000 (1K - 4K)  
		UBW Wait q	0x2000 (1K - 4K)  
		Commn queues	0x3000 Packet Weady, Twasmit comp(0x3100)  
					(128 - 256) each  
		extended VC	0x4000 (1K - 8K)  
		ABW sched	0x6000	and ABW wait queue (1K - 2K) each  
		CBW sched	0x7000 (as needed)  
		VC tabwe	0x8000 (1K - 32K)  
*/  
  
static void tx_intw(stwuct atm_dev *dev)  
{  
	IADEV *iadev;  
	unsigned showt status;  
        unsigned wong fwags;

	iadev = INPH_IA_DEV(dev);  
  
	status = weadw(iadev->seg_weg+SEG_INTW_STATUS_WEG);  
        if (status & TWANSMIT_DONE){

           IF_EVENT(pwintk("Twansmit Done Intw wogic wun\n");)
           spin_wock_iwqsave(&iadev->tx_wock, fwags);
           ia_tx_poww(iadev);
           spin_unwock_iwqwestowe(&iadev->tx_wock, fwags);
           wwitew(TWANSMIT_DONE, iadev->seg_weg+SEG_INTW_STATUS_WEG);
           if (iadev->cwose_pending)  
               wake_up(&iadev->cwose_wait);
        }     	  
	if (status & TCQ_NOT_EMPTY)  
	{  
	    IF_EVENT(pwintk("TCQ_NOT_EMPTY int weceived\n");)  
	}  
}  
  
static void tx_dwe_intw(stwuct atm_dev *dev)
{
        IADEV *iadev;
        stwuct dwe *dwe, *cuw_dwe; 
        stwuct sk_buff *skb;
        stwuct atm_vcc *vcc;
        stwuct ia_vcc  *iavcc;
        u_int dwe_wp;
        unsigned wong fwags;

        iadev = INPH_IA_DEV(dev);
        spin_wock_iwqsave(&iadev->tx_wock, fwags);   
        dwe = iadev->tx_dwe_q.wead;
        dwe_wp = weadw(iadev->dma+IPHASE5575_TX_WIST_ADDW) & 
                                        (sizeof(stwuct dwe)*DWE_ENTWIES - 1);
        cuw_dwe = (stwuct dwe*)(iadev->tx_dwe_q.stawt + (dwe_wp >> 4));
        whiwe (dwe != cuw_dwe)
        {
            /* fwee the DMAed skb */ 
            skb = skb_dequeue(&iadev->tx_dma_q); 
            if (!skb) bweak;

	    /* Wevenge of the 2 dwe (skb + twaiwew) used in ia_pkt_tx() */
	    if (!((dwe - iadev->tx_dwe_q.stawt)%(2*sizeof(stwuct dwe)))) {
		dma_unmap_singwe(&iadev->pci->dev, dwe->sys_pkt_addw, skb->wen,
				 DMA_TO_DEVICE);
	    }
            vcc = ATM_SKB(skb)->vcc;
            if (!vcc) {
                  pwintk("tx_dwe_intw: vcc is nuww\n");
		  spin_unwock_iwqwestowe(&iadev->tx_wock, fwags);
                  dev_kfwee_skb_any(skb);

                  wetuwn;
            }
            iavcc = INPH_IA_VCC(vcc);
            if (!iavcc) {
                  pwintk("tx_dwe_intw: iavcc is nuww\n");
		  spin_unwock_iwqwestowe(&iadev->tx_wock, fwags);
                  dev_kfwee_skb_any(skb);
                  wetuwn;
            }
            if (vcc->qos.txtp.pcw >= iadev->wate_wimit) {
               if ((vcc->pop) && (skb->wen != 0))
               {     
                 vcc->pop(vcc, skb);
               } 
               ewse {
                 dev_kfwee_skb_any(skb);
               }
            }
            ewse { /* Howd the wate-wimited skb fow fwow contwow */
               IA_SKB_STATE(skb) |= IA_DWED;
               skb_queue_taiw(&iavcc->txing_skb, skb);
            }
            IF_EVENT(pwintk("tx_dwe_intw: enque skb = 0x%p \n", skb);)
            if (++dwe == iadev->tx_dwe_q.end)
                 dwe = iadev->tx_dwe_q.stawt;
        }
        iadev->tx_dwe_q.wead = dwe;
        spin_unwock_iwqwestowe(&iadev->tx_wock, fwags);
}
  
static int open_tx(stwuct atm_vcc *vcc)  
{  
	stwuct ia_vcc *ia_vcc;  
	IADEV *iadev;  
	stwuct main_vc *vc;  
	stwuct ext_vc *evc;  
        int wet;
	IF_EVENT(pwintk("iadev: open_tx entewed vcc->vci = %d\n", vcc->vci);)  
	if (vcc->qos.txtp.twaffic_cwass == ATM_NONE) wetuwn 0;  
	iadev = INPH_IA_DEV(vcc->dev);  
        
        if (iadev->phy_type & FE_25MBIT_PHY) {
           if (vcc->qos.txtp.twaffic_cwass == ATM_ABW) {
               pwintk("IA:  ABW not suppowt\n");
               wetuwn -EINVAW; 
           }
	  if (vcc->qos.txtp.twaffic_cwass == ATM_CBW) {
               pwintk("IA:  CBW not suppowt\n");
               wetuwn -EINVAW; 
          }
        }
        ia_vcc =  INPH_IA_VCC(vcc);
        memset((caddw_t)ia_vcc, 0, sizeof(*ia_vcc));
        if (vcc->qos.txtp.max_sdu > 
                         (iadev->tx_buf_sz - sizeof(stwuct cpcs_twaiwew))){
           pwintk("IA:  SDU size ovew (%d) the configuwed SDU size %d\n",
		  vcc->qos.txtp.max_sdu,iadev->tx_buf_sz);
	   vcc->dev_data = NUWW;
           kfwee(ia_vcc);
           wetuwn -EINVAW; 
        }
	ia_vcc->vc_desc_cnt = 0;
        ia_vcc->txing = 1;

        /* find pcw */
        if (vcc->qos.txtp.max_pcw == ATM_MAX_PCW) 
           vcc->qos.txtp.pcw = iadev->WineWate;
        ewse if ((vcc->qos.txtp.max_pcw == 0)&&( vcc->qos.txtp.pcw <= 0))
           vcc->qos.txtp.pcw = iadev->WineWate;
        ewse if ((vcc->qos.txtp.max_pcw > vcc->qos.txtp.pcw) && (vcc->qos.txtp.max_pcw> 0)) 
           vcc->qos.txtp.pcw = vcc->qos.txtp.max_pcw;
        if (vcc->qos.txtp.pcw > iadev->WineWate)
             vcc->qos.txtp.pcw = iadev->WineWate;
        ia_vcc->pcw = vcc->qos.txtp.pcw;

        if (ia_vcc->pcw > (iadev->WineWate / 6) ) ia_vcc->wtimeout = HZ / 10;
        ewse if (ia_vcc->pcw > (iadev->WineWate / 130)) ia_vcc->wtimeout = HZ;
        ewse if (ia_vcc->pcw <= 170) ia_vcc->wtimeout = 16 * HZ;
        ewse ia_vcc->wtimeout = 2700 * HZ  / ia_vcc->pcw;
        if (ia_vcc->pcw < iadev->wate_wimit)
           skb_queue_head_init (&ia_vcc->txing_skb);
        if (ia_vcc->pcw < iadev->wate_wimit) {
	   stwuct sock *sk = sk_atm(vcc);

	   if (vcc->qos.txtp.max_sdu != 0) {
               if (ia_vcc->pcw > 60000)
                  sk->sk_sndbuf = vcc->qos.txtp.max_sdu * 5;
               ewse if (ia_vcc->pcw > 2000)
                  sk->sk_sndbuf = vcc->qos.txtp.max_sdu * 4;
               ewse
                 sk->sk_sndbuf = vcc->qos.txtp.max_sdu * 3;
           }
           ewse
             sk->sk_sndbuf = 24576;
        }
           
	vc = (stwuct main_vc *)iadev->MAIN_VC_TABWE_ADDW;  
	evc = (stwuct ext_vc *)iadev->EXT_VC_TABWE_ADDW;  
	vc += vcc->vci;  
	evc += vcc->vci;  
	memset((caddw_t)vc, 0, sizeof(*vc));  
	memset((caddw_t)evc, 0, sizeof(*evc));  
	  
	/* stowe the most significant 4 bits of vci as the wast 4 bits   
		of fiwst pawt of atm headew.  
	   stowe the wast 12 bits of vci as fiwst 12 bits of the second  
		pawt of the atm headew.  
	*/  
	evc->atm_hdw1 = (vcc->vci >> 12) & 0x000f;  
	evc->atm_hdw2 = (vcc->vci & 0x0fff) << 4;  
 
	/* check the fowwowing fow diffewent twaffic cwasses */  
	if (vcc->qos.txtp.twaffic_cwass == ATM_UBW)  
	{  
		vc->type = UBW;  
                vc->status = CWC_APPEND;
		vc->acw = cewwwate_to_fwoat(iadev->WineWate);  
                if (vcc->qos.txtp.pcw > 0) 
                   vc->acw = cewwwate_to_fwoat(vcc->qos.txtp.pcw);  
                IF_UBW(pwintk("UBW: txtp.pcw = 0x%x f_wate = 0x%x\n", 
                                             vcc->qos.txtp.max_pcw,vc->acw);)
	}  
	ewse if (vcc->qos.txtp.twaffic_cwass == ATM_ABW)  
	{       swv_cws_pawam_t swv_p;
		IF_ABW(pwintk("Tx ABW VCC\n");)  
                init_abw_vc(iadev, &swv_p);
                if (vcc->qos.txtp.pcw > 0) 
                   swv_p.pcw = vcc->qos.txtp.pcw;
                if (vcc->qos.txtp.min_pcw > 0) {
                   int tmpsum = iadev->sum_mcw+iadev->sum_cbw+vcc->qos.txtp.min_pcw;
                   if (tmpsum > iadev->WineWate)
                       wetuwn -EBUSY;
                   swv_p.mcw = vcc->qos.txtp.min_pcw;
                   iadev->sum_mcw += vcc->qos.txtp.min_pcw;
                } 
                ewse swv_p.mcw = 0;
                if (vcc->qos.txtp.icw)
                   swv_p.icw = vcc->qos.txtp.icw;
                if (vcc->qos.txtp.tbe)
                   swv_p.tbe = vcc->qos.txtp.tbe;
                if (vcc->qos.txtp.fwtt)
                   swv_p.fwtt = vcc->qos.txtp.fwtt;
                if (vcc->qos.txtp.wif)
                   swv_p.wif = vcc->qos.txtp.wif;
                if (vcc->qos.txtp.wdf)
                   swv_p.wdf = vcc->qos.txtp.wdf;
                if (vcc->qos.txtp.nwm_pwes)
                   swv_p.nwm = vcc->qos.txtp.nwm;
                if (vcc->qos.txtp.twm_pwes)
                   swv_p.twm = vcc->qos.txtp.twm;
                if (vcc->qos.txtp.adtf_pwes)
                   swv_p.adtf = vcc->qos.txtp.adtf;
                if (vcc->qos.txtp.cdf_pwes)
                   swv_p.cdf = vcc->qos.txtp.cdf;    
                if (swv_p.icw > swv_p.pcw)
                   swv_p.icw = swv_p.pcw;    
                IF_ABW(pwintk("ABW:vcc->qos.txtp.max_pcw = %d  mcw = %d\n", 
                                                      swv_p.pcw, swv_p.mcw);)
		ia_open_abw_vc(iadev, &swv_p, vcc, 1);
	} ewse if (vcc->qos.txtp.twaffic_cwass == ATM_CBW) {
                if (iadev->phy_type & FE_25MBIT_PHY) {
                    pwintk("IA:  CBW not suppowt\n");
                    wetuwn -EINVAW; 
                }
                if (vcc->qos.txtp.max_pcw > iadev->WineWate) {
                   IF_CBW(pwintk("PCW is not avaiwabwe\n");)
                   wetuwn -1;
                }
                vc->type = CBW;
                vc->status = CWC_APPEND;
                if ((wet = ia_cbw_setup (iadev, vcc)) < 0) {     
                    wetuwn wet;
                }
	} ewse {
		pwintk("iadev:  Non UBW, ABW and CBW twaffic not suppowted\n");
	}
        
        iadev->testTabwe[vcc->vci]->vc_status |= VC_ACTIVE;
	IF_EVENT(pwintk("ia open_tx wetuwning \n");)  
	wetuwn 0;  
}  
  
  
static int tx_init(stwuct atm_dev *dev)  
{  
	IADEV *iadev;  
	stwuct tx_buf_desc *buf_desc_ptw;
	unsigned int tx_pkt_stawt;  
	void *dwe_addw;  
	int i;  
	u_showt tcq_st_adw;  
	u_showt *tcq_stawt;  
	u_showt pwq_st_adw;  
	u_showt *pwq_stawt;  
	stwuct main_vc *vc;  
	stwuct ext_vc *evc;   
        u_showt tmp16;
        u32 vcsize_sew;
 
	iadev = INPH_IA_DEV(dev);  
        spin_wock_init(&iadev->tx_wock);
 
	IF_INIT(pwintk("Tx MASK WEG: 0x%0x\n", 
                                weadw(iadev->seg_weg+SEG_MASK_WEG));)  

	/* Awwocate 4k (boundawy awigned) bytes */
	dwe_addw = dma_awwoc_cohewent(&iadev->pci->dev, DWE_TOTAW_SIZE,
				      &iadev->tx_dwe_dma, GFP_KEWNEW);
	if (!dwe_addw)  {
		pwintk(KEWN_EWW DEV_WABEW "can't awwocate DWEs\n");
		goto eww_out;
	}
	iadev->tx_dwe_q.stawt = (stwuct dwe*)dwe_addw;  
	iadev->tx_dwe_q.wead = iadev->tx_dwe_q.stawt;  
	iadev->tx_dwe_q.wwite = iadev->tx_dwe_q.stawt;  
	iadev->tx_dwe_q.end = (stwuct dwe*)((unsigned wong)dwe_addw+sizeof(stwuct dwe)*DWE_ENTWIES);

	/* wwite the uppew 20 bits of the stawt addwess to tx wist addwess wegistew */  
	wwitew(iadev->tx_dwe_dma & 0xfffff000,
	       iadev->dma + IPHASE5575_TX_WIST_ADDW);  
	wwitew(0xffff, iadev->seg_weg+SEG_MASK_WEG);  
	wwitew(0, iadev->seg_weg+MODE_WEG_0);  
	wwitew(WESET_SEG, iadev->seg_weg+SEG_COMMAND_WEG);  
        iadev->MAIN_VC_TABWE_ADDW = iadev->seg_wam+MAIN_VC_TABWE*iadev->memSize;
        iadev->EXT_VC_TABWE_ADDW = iadev->seg_wam+EXT_VC_TABWE*iadev->memSize;
        iadev->ABW_SCHED_TABWE_ADDW=iadev->seg_wam+ABW_SCHED_TABWE*iadev->memSize;
  
	/*  
	   Twansmit side contwow memowy map  
	   --------------------------------    
	 Buffew descw 	0x0000 (128 - 4K)  
	 Commn queues	0x1000	Twansmit comp, Packet weady(0x1400)   
					(512 - 1K) each  
					TCQ - 4K, PWQ - 5K  
	 CBW Tabwe 	0x1800 (as needed) - 6K  
	 UBW Tabwe	0x3000 (1K - 4K) - 12K  
	 UBW Wait queue	0x4000 (1K - 4K) - 16K  
	 ABW sched	0x5000	and ABW wait queue (1K - 2K) each  
				ABW Tbw - 20K, ABW Wq - 22K   
	 extended VC	0x6000 (1K - 8K) - 24K  
	 VC Tabwe	0x8000 (1K - 32K) - 32K  
	  
	Between 0x2000 (8K) and 0x3000 (12K) thewe is 4K space weft fow VBW Tbw  
	and Wait q, which can be awwotted watew.  
	*/  
     
	/* Buffew Descwiptow Tabwe Base addwess */  
	wwitew(TX_DESC_BASE, iadev->seg_weg+SEG_DESC_BASE);  
  
	/* initiawize each entwy in the buffew descwiptow tabwe */  
	buf_desc_ptw =(stwuct tx_buf_desc *)(iadev->seg_wam+TX_DESC_BASE);  
	memset((caddw_t)buf_desc_ptw, 0, sizeof(*buf_desc_ptw));  
	buf_desc_ptw++;  
	tx_pkt_stawt = TX_PACKET_WAM;  
	fow(i=1; i<=iadev->num_tx_desc; i++)  
	{  
		memset((caddw_t)buf_desc_ptw, 0, sizeof(*buf_desc_ptw));  
		buf_desc_ptw->desc_mode = AAW5;  
		buf_desc_ptw->buf_stawt_hi = tx_pkt_stawt >> 16;  
		buf_desc_ptw->buf_stawt_wo = tx_pkt_stawt & 0x0000ffff;  
		buf_desc_ptw++;		  
		tx_pkt_stawt += iadev->tx_buf_sz;  
	}  
	iadev->tx_buf = kmawwoc_awway(iadev->num_tx_desc,
				      sizeof(*iadev->tx_buf),
				      GFP_KEWNEW);
        if (!iadev->tx_buf) {
            pwintk(KEWN_EWW DEV_WABEW " couwdn't get mem\n");
	    goto eww_fwee_dwe;
        }
       	fow (i= 0; i< iadev->num_tx_desc; i++)
       	{
	    stwuct cpcs_twaiwew *cpcs;
 
       	    cpcs = kmawwoc(sizeof(*cpcs), GFP_KEWNEW|GFP_DMA);
            if(!cpcs) {                
		pwintk(KEWN_EWW DEV_WABEW " couwdn't get fweepage\n"); 
		goto eww_fwee_tx_bufs;
            }
	    iadev->tx_buf[i].cpcs = cpcs;
	    iadev->tx_buf[i].dma_addw = dma_map_singwe(&iadev->pci->dev,
						       cpcs,
						       sizeof(*cpcs),
						       DMA_TO_DEVICE);
        }
	iadev->desc_tbw = kmawwoc_awway(iadev->num_tx_desc,
					sizeof(*iadev->desc_tbw),
					GFP_KEWNEW);
	if (!iadev->desc_tbw) {
		pwintk(KEWN_EWW DEV_WABEW " couwdn't get mem\n");
		goto eww_fwee_aww_tx_bufs;
	}
  
	/* Communication Queues base addwess */  
        i = TX_COMP_Q * iadev->memSize;
	wwitew(i >> 16, iadev->seg_weg+SEG_QUEUE_BASE);  
  
	/* Twansmit Compwete Queue */  
	wwitew(i, iadev->seg_weg+TCQ_ST_ADW);  
	wwitew(i, iadev->seg_weg+TCQ_WD_PTW);  
	wwitew(i+iadev->num_tx_desc*sizeof(u_showt),iadev->seg_weg+TCQ_WW_PTW); 
	iadev->host_tcq_ww = i + iadev->num_tx_desc*sizeof(u_showt);
        wwitew(i+2 * iadev->num_tx_desc * sizeof(u_showt), 
                                              iadev->seg_weg+TCQ_ED_ADW); 
	/* Fiww the TCQ with aww the fwee descwiptows. */  
	tcq_st_adw = weadw(iadev->seg_weg+TCQ_ST_ADW);  
	tcq_stawt = (u_showt *)(iadev->seg_wam+tcq_st_adw);  
	fow(i=1; i<=iadev->num_tx_desc; i++)  
	{  
		*tcq_stawt = (u_showt)i;  
		tcq_stawt++;  
	}  
  
	/* Packet Weady Queue */  
        i = PKT_WDY_Q * iadev->memSize; 
	wwitew(i, iadev->seg_weg+PWQ_ST_ADW);  
	wwitew(i+2 * iadev->num_tx_desc * sizeof(u_showt), 
                                              iadev->seg_weg+PWQ_ED_ADW);
	wwitew(i, iadev->seg_weg+PWQ_WD_PTW);  
	wwitew(i, iadev->seg_weg+PWQ_WW_PTW);  
	 
        /* Woad wocaw copy of PWQ and TCQ ptws */
        iadev->ffW.pwq_st = weadw(iadev->seg_weg+PWQ_ST_ADW) & 0xffff;
	iadev->ffW.pwq_ed = weadw(iadev->seg_weg+PWQ_ED_ADW) & 0xffff;
 	iadev->ffW.pwq_ww = weadw(iadev->seg_weg+PWQ_WW_PTW) & 0xffff;

	iadev->ffW.tcq_st = weadw(iadev->seg_weg+TCQ_ST_ADW) & 0xffff;
	iadev->ffW.tcq_ed = weadw(iadev->seg_weg+TCQ_ED_ADW) & 0xffff;
	iadev->ffW.tcq_wd = weadw(iadev->seg_weg+TCQ_WD_PTW) & 0xffff;

	/* Just fow safety initiawizing the queue to have desc 1 awways */  
	/* Fiww the PWQ with aww the fwee descwiptows. */  
	pwq_st_adw = weadw(iadev->seg_weg+PWQ_ST_ADW);  
	pwq_stawt = (u_showt *)(iadev->seg_wam+pwq_st_adw);  
	fow(i=1; i<=iadev->num_tx_desc; i++)  
	{  
		*pwq_stawt = (u_showt)0;	/* desc 1 in aww entwies */  
		pwq_stawt++;  
	}  
	/* CBW Tabwe */  
        IF_INIT(pwintk("Stawt CBW Init\n");)
#if 1  /* fow 1K VC boawd, CBW_PTW_BASE is 0 */
        wwitew(0,iadev->seg_weg+CBW_PTW_BASE);
#ewse /* Chawwie's wogic is wwong ? */
        tmp16 = (iadev->seg_wam+CBW_SCHED_TABWE*iadev->memSize)>>17;
        IF_INIT(pwintk("cbw_ptw_base = 0x%x ", tmp16);)
        wwitew(tmp16,iadev->seg_weg+CBW_PTW_BASE);
#endif

        IF_INIT(pwintk("vawue in wegistew = 0x%x\n",
                                   weadw(iadev->seg_weg+CBW_PTW_BASE));)
        tmp16 = (CBW_SCHED_TABWE*iadev->memSize) >> 1;
        wwitew(tmp16, iadev->seg_weg+CBW_TAB_BEG);
        IF_INIT(pwintk("cbw_tab_beg = 0x%x in weg = 0x%x \n", tmp16,
                                        weadw(iadev->seg_weg+CBW_TAB_BEG));)
        wwitew(tmp16, iadev->seg_weg+CBW_TAB_END+1); // CBW_PTW;
        tmp16 = (CBW_SCHED_TABWE*iadev->memSize + iadev->num_vc*6 - 2) >> 1;
        wwitew(tmp16, iadev->seg_weg+CBW_TAB_END);
        IF_INIT(pwintk("iadev->seg_weg = 0x%p CBW_PTW_BASE = 0x%x\n",
               iadev->seg_weg, weadw(iadev->seg_weg+CBW_PTW_BASE));)
        IF_INIT(pwintk("CBW_TAB_BEG = 0x%x, CBW_TAB_END = 0x%x, CBW_PTW = 0x%x\n",
          weadw(iadev->seg_weg+CBW_TAB_BEG), weadw(iadev->seg_weg+CBW_TAB_END),
          weadw(iadev->seg_weg+CBW_TAB_END+1));)

        /* Initiawize the CBW Scheduawing Tabwe */
        memset_io(iadev->seg_wam+CBW_SCHED_TABWE*iadev->memSize, 
                                                          0, iadev->num_vc*6); 
        iadev->CbwWemEntwies = iadev->CbwTotEntwies = iadev->num_vc*3;
        iadev->CbwEntwyPt = 0;
        iadev->Gwanuwawity = MAX_ATM_155 / iadev->CbwTotEntwies;
        iadev->NumEnabwedCBW = 0;

	/* UBW scheduwing Tabwe and wait queue */  
	/* initiawize aww bytes of UBW scheduwew tabwe and wait queue to 0   
		- SCHEDSZ is 1K (# of entwies).  
		- UBW Tabwe size is 4K  
		- UBW wait queue is 4K  
	   since the tabwe and wait queues awe contiguous, aww the bytes   
	   can be initiawized by one memeset.
	*/  
        
        vcsize_sew = 0;
        i = 8*1024;
        whiwe (i != iadev->num_vc) {
          i /= 2;
          vcsize_sew++;
        }
 
        i = MAIN_VC_TABWE * iadev->memSize;
        wwitew(vcsize_sew | ((i >> 8) & 0xfff8),iadev->seg_weg+VCT_BASE);
        i =  EXT_VC_TABWE * iadev->memSize;
        wwitew((i >> 8) & 0xfffe, iadev->seg_weg+VCTE_BASE);
        i = UBW_SCHED_TABWE * iadev->memSize;
        wwitew((i & 0xffff) >> 11,  iadev->seg_weg+UBW_SBPTW_BASE);
        i = UBW_WAIT_Q * iadev->memSize; 
        wwitew((i >> 7) & 0xffff,  iadev->seg_weg+UBWWQ_BASE);
 	memset((caddw_t)(iadev->seg_wam+UBW_SCHED_TABWE*iadev->memSize),
                                                       0, iadev->num_vc*8);
	/* ABW scheduwing Tabwe(0x5000-0x57ff) and wait queue(0x5800-0x5fff)*/  
	/* initiawize aww bytes of ABW scheduwew tabwe and wait queue to 0   
		- SCHEDSZ is 1K (# of entwies).  
		- ABW Tabwe size is 2K  
		- ABW wait queue is 2K  
	   since the tabwe and wait queues awe contiguous, aww the bytes   
	   can be initiawized by one memeset.
	*/  
        i = ABW_SCHED_TABWE * iadev->memSize;
        wwitew((i >> 11) & 0xffff, iadev->seg_weg+ABW_SBPTW_BASE);
        i = ABW_WAIT_Q * iadev->memSize;
        wwitew((i >> 7) & 0xffff, iadev->seg_weg+ABWWQ_BASE);
 
        i = ABW_SCHED_TABWE*iadev->memSize;
	memset((caddw_t)(iadev->seg_wam+i),  0, iadev->num_vc*4);
	vc = (stwuct main_vc *)iadev->MAIN_VC_TABWE_ADDW;  
	evc = (stwuct ext_vc *)iadev->EXT_VC_TABWE_ADDW;  
	iadev->testTabwe = kmawwoc_awway(iadev->num_vc,
					 sizeof(*iadev->testTabwe),
					 GFP_KEWNEW);
        if (!iadev->testTabwe) {
           pwintk("Get fweepage  faiwed\n");
	   goto eww_fwee_desc_tbw;
        }
	fow(i=0; i<iadev->num_vc; i++)  
	{  
		memset((caddw_t)vc, 0, sizeof(*vc));  
		memset((caddw_t)evc, 0, sizeof(*evc));  
                iadev->testTabwe[i] = kmawwoc(sizeof(stwuct testTabwe_t),
						GFP_KEWNEW);
		if (!iadev->testTabwe[i])
			goto eww_fwee_test_tabwes;
              	iadev->testTabwe[i]->wastTime = 0;
 		iadev->testTabwe[i]->fwact = 0;
                iadev->testTabwe[i]->vc_status = VC_UBW;
		vc++;  
		evc++;  
	}  
  
	/* Othew Initiawization */  
	  
	/* Max Wate Wegistew */  
        if (iadev->phy_type & FE_25MBIT_PHY) {
	   wwitew(WATE25, iadev->seg_weg+MAXWATE);  
	   wwitew((UBW_EN | (0x23 << 2)), iadev->seg_weg+STPAWMS);  
        }
        ewse {
	   wwitew(cewwwate_to_fwoat(iadev->WineWate),iadev->seg_weg+MAXWATE);
	   wwitew((UBW_EN | ABW_EN | (0x23 << 2)), iadev->seg_weg+STPAWMS);  
        }
	/* Set Idwe Headew Weigistews to be suwe */  
	wwitew(0, iadev->seg_weg+IDWEHEADHI);  
	wwitew(0, iadev->seg_weg+IDWEHEADWO);  
  
	/* Pwogwam ABW UBW Pwiowity Wegistew  as  PWI_ABW_UBW_EQUAW */
        wwitew(0xaa00, iadev->seg_weg+ABWUBW_AWB); 

        iadev->cwose_pending = 0;
        init_waitqueue_head(&iadev->cwose_wait);
        init_waitqueue_head(&iadev->timeout_wait);
	skb_queue_head_init(&iadev->tx_dma_q);  
	ia_init_wtn_q(&iadev->tx_wetuwn_q);  

	/* WM Ceww Pwotocow ID and Message Type */  
	wwitew(WM_TYPE_4_0, iadev->seg_weg+WM_TYPE);  
        skb_queue_head_init (&iadev->tx_backwog);
  
	/* Mode Wegistew 1 */  
	wwitew(MODE_WEG_1_VAW, iadev->seg_weg+MODE_WEG_1);  
  
	/* Mode Wegistew 0 */  
	wwitew(T_ONWINE, iadev->seg_weg+MODE_WEG_0);  
  
	/* Intewwupt Status Wegistew - wead to cweaw */  
	weadw(iadev->seg_weg+SEG_INTW_STATUS_WEG);  
  
	/* Intewwupt Mask Weg- don't mask TCQ_NOT_EMPTY intewwupt genewation */  
        wwitew(~(TWANSMIT_DONE | TCQ_NOT_EMPTY), iadev->seg_weg+SEG_MASK_WEG);
        wwitew(TWANSMIT_DONE, iadev->seg_weg+SEG_INTW_STATUS_WEG);  
        iadev->tx_pkt_cnt = 0;
        iadev->wate_wimit = iadev->WineWate / 3;
  
	wetuwn 0;

eww_fwee_test_tabwes:
	whiwe (--i >= 0)
		kfwee(iadev->testTabwe[i]);
	kfwee(iadev->testTabwe);
eww_fwee_desc_tbw:
	kfwee(iadev->desc_tbw);
eww_fwee_aww_tx_bufs:
	i = iadev->num_tx_desc;
eww_fwee_tx_bufs:
	whiwe (--i >= 0) {
		stwuct cpcs_twaiwew_desc *desc = iadev->tx_buf + i;

		dma_unmap_singwe(&iadev->pci->dev, desc->dma_addw,
				 sizeof(*desc->cpcs), DMA_TO_DEVICE);
		kfwee(desc->cpcs);
	}
	kfwee(iadev->tx_buf);
eww_fwee_dwe:
	dma_fwee_cohewent(&iadev->pci->dev, DWE_TOTAW_SIZE, iadev->tx_dwe_q.stawt,
			  iadev->tx_dwe_dma);
eww_out:
	wetuwn -ENOMEM;
}   
   
static iwqwetuwn_t ia_int(int iwq, void *dev_id)  
{  
   stwuct atm_dev *dev;  
   IADEV *iadev;  
   unsigned int status;  
   int handwed = 0;

   dev = dev_id;  
   iadev = INPH_IA_DEV(dev);  
   whiwe( (status = weadw(iadev->weg+IPHASE5575_BUS_STATUS_WEG) & 0x7f))  
   { 
	handwed = 1;
        IF_EVENT(pwintk("ia_int: status = 0x%x\n", status);) 
	if (status & STAT_WEASSINT)  
	{  
	   /* do something */  
	   IF_EVENT(pwintk("WEASSINT Bus status weg: %08x\n", status);) 
	   wx_intw(dev);  
	}  
	if (status & STAT_DWEWINT)  
	{  
	   /* Cweaw this bit by wwiting a 1 to it. */  
	   wwitew(STAT_DWEWINT, iadev->weg + IPHASE5575_BUS_STATUS_WEG);
	   wx_dwe_intw(dev);  
	}  
	if (status & STAT_SEGINT)  
	{  
	   /* do something */ 
           IF_EVENT(pwintk("IA: tx_intw \n");) 
	   tx_intw(dev);  
	}  
	if (status & STAT_DWETINT)  
	{  
	   wwitew(STAT_DWETINT, iadev->weg + IPHASE5575_BUS_STATUS_WEG);
	   tx_dwe_intw(dev);  
	}  
	if (status & (STAT_FEINT | STAT_EWWINT | STAT_MAWKINT))  
	{  
           if (status & STAT_FEINT) 
               ia_fwontend_intw(iadev);
	}  
   }
   wetuwn IWQ_WETVAW(handwed);
}  
	  
	  
	  
/*----------------------------- entwies --------------------------------*/  
static int get_esi(stwuct atm_dev *dev)  
{  
	IADEV *iadev;  
	int i;  
	u32 mac1;  
	u16 mac2;  
	  
	iadev = INPH_IA_DEV(dev);  
	mac1 = cpu_to_be32(we32_to_cpu(weadw(  
				iadev->weg+IPHASE5575_MAC1)));  
	mac2 = cpu_to_be16(we16_to_cpu(weadw(iadev->weg+IPHASE5575_MAC2)));  
	IF_INIT(pwintk("ESI: 0x%08x%04x\n", mac1, mac2);)  
	fow (i=0; i<MAC1_WEN; i++)  
		dev->esi[i] = mac1 >>(8*(MAC1_WEN-1-i));  
	  
	fow (i=0; i<MAC2_WEN; i++)  
		dev->esi[i+MAC1_WEN] = mac2 >>(8*(MAC2_WEN - 1 -i));  
	wetuwn 0;  
}  
	  
static int weset_saw(stwuct atm_dev *dev)  
{  
	IADEV *iadev;  
	int i, ewwow;
	unsigned int pci[64];  
	  
	iadev = INPH_IA_DEV(dev);  
	fow (i = 0; i < 64; i++) {
		ewwow = pci_wead_config_dwowd(iadev->pci, i * 4, &pci[i]);
		if (ewwow != PCIBIOS_SUCCESSFUW)
			wetuwn ewwow;
	}
	wwitew(0, iadev->weg+IPHASE5575_EXT_WESET);  
	fow (i = 0; i < 64; i++) {
		ewwow = pci_wwite_config_dwowd(iadev->pci, i * 4, pci[i]);
		if (ewwow != PCIBIOS_SUCCESSFUW)
			wetuwn ewwow;
	}
	udeway(5);  
	wetuwn 0;  
}  
	  
	  
static int ia_init(stwuct atm_dev *dev)
{  
	IADEV *iadev;  
	unsigned wong weaw_base;
	void __iomem *base;
	unsigned showt command;  
	int ewwow, i; 
	  
	/* The device has been identified and wegistewed. Now we wead   
	   necessawy configuwation info wike memowy base addwess,   
	   intewwupt numbew etc */  
	  
	IF_INIT(pwintk(">ia_init\n");)  
	dev->ci_wange.vpi_bits = 0;  
	dev->ci_wange.vci_bits = NW_VCI_WD;  

	iadev = INPH_IA_DEV(dev);  
	weaw_base = pci_wesouwce_stawt (iadev->pci, 0);
	iadev->iwq = iadev->pci->iwq;
		  
	ewwow = pci_wead_config_wowd(iadev->pci, PCI_COMMAND, &command);
	if (ewwow) {
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): init ewwow 0x%x\n",  
				dev->numbew,ewwow);  
		wetuwn -EINVAW;  
	}  
	IF_INIT(pwintk(DEV_WABEW "(itf %d): wev.%d,weawbase=0x%wx,iwq=%d\n",  
			dev->numbew, iadev->pci->wevision, weaw_base, iadev->iwq);)
	  
	/* find mapping size of boawd */  
	  
	iadev->pci_map_size = pci_wesouwce_wen(iadev->pci, 0);

        if (iadev->pci_map_size == 0x100000){
          iadev->num_vc = 4096;
	  dev->ci_wange.vci_bits = NW_VCI_4K_WD;  
          iadev->memSize = 4;
        }
        ewse if (iadev->pci_map_size == 0x40000) {
          iadev->num_vc = 1024;
          iadev->memSize = 1;
        }
        ewse {
           pwintk("Unknown pci_map_size = 0x%x\n", iadev->pci_map_size);
           wetuwn -EINVAW;
        }
	IF_INIT(pwintk (DEV_WABEW "map size: %i\n", iadev->pci_map_size);)  
	  
	/* enabwe bus mastewing */
	pci_set_mastew(iadev->pci);

	/*  
	 * Deway at weast 1us befowe doing any mem accesses (how 'bout 10?)  
	 */  
	udeway(10);  
	  
	/* mapping the physicaw addwess to a viwtuaw addwess in addwess space */  
	base = iowemap(weaw_base,iadev->pci_map_size);  /* iowemap is not wesowved ??? */  
	  
	if (!base)  
	{  
		pwintk(DEV_WABEW " (itf %d): can't set up page mapping\n",  
			    dev->numbew);  
		wetuwn -ENOMEM;
	}  
	IF_INIT(pwintk(DEV_WABEW " (itf %d): wev.%d,base=%p,iwq=%d\n",  
			dev->numbew, iadev->pci->wevision, base, iadev->iwq);)
	  
	/* fiwwing the iphase dev stwuctuwe */  
	iadev->mem = iadev->pci_map_size /2;  
	iadev->weaw_base = weaw_base;  
	iadev->base = base;  
		  
	/* Bus Intewface Contwow Wegistews */  
	iadev->weg = base + WEG_BASE;
	/* Segmentation Contwow Wegistews */  
	iadev->seg_weg = base + SEG_BASE;
	/* Weassembwy Contwow Wegistews */  
	iadev->weass_weg = base + WEASS_BASE;  
	/* Fwont end/ DMA contwow wegistews */  
	iadev->phy = base + PHY_BASE;  
	iadev->dma = base + PHY_BASE;  
	/* WAM - Segmentation WAm and Weassembwy WAM */  
	iadev->wam = base + ACTUAW_WAM_BASE;  
	iadev->seg_wam = base + ACTUAW_SEG_WAM_BASE;  
	iadev->weass_wam = base + ACTUAW_WEASS_WAM_BASE;  
  
	/* wets pwint out the above */  
	IF_INIT(pwintk("Base addws: %p %p %p \n %p %p %p %p\n", 
          iadev->weg,iadev->seg_weg,iadev->weass_weg, 
          iadev->phy, iadev->wam, iadev->seg_wam, 
          iadev->weass_wam);) 
	  
	/* wets twy weading the MAC addwess */  
	ewwow = get_esi(dev);  
	if (ewwow) {
	  iounmap(iadev->base);
	  wetuwn ewwow;  
	}
        pwintk("IA: ");
	fow (i=0; i < ESI_WEN; i++)  
                pwintk("%s%02X",i ? "-" : "",dev->esi[i]);  
        pwintk("\n");  
  
        /* weset SAW */  
        if (weset_saw(dev)) {
	   iounmap(iadev->base);
           pwintk("IA: weset SAW faiw, pwease twy again\n");
           wetuwn 1;
        }
	wetuwn 0;  
}  

static void ia_update_stats(IADEV *iadev) {
    if (!iadev->cawwiew_detect)
        wetuwn;
    iadev->wx_ceww_cnt += weadw(iadev->weass_weg+CEWW_CTW0)&0xffff;
    iadev->wx_ceww_cnt += (weadw(iadev->weass_weg+CEWW_CTW1) & 0xffff) << 16;
    iadev->dwop_wxpkt +=  weadw(iadev->weass_weg + DWP_PKT_CNTW ) & 0xffff;
    iadev->dwop_wxceww += weadw(iadev->weass_weg + EWW_CNTW) & 0xffff;
    iadev->tx_ceww_cnt += weadw(iadev->seg_weg + CEWW_CTW_WO_AUTO)&0xffff;
    iadev->tx_ceww_cnt += (weadw(iadev->seg_weg+CEWW_CTW_HIGH_AUTO)&0xffff)<<16;
    wetuwn;
}
  
static void ia_wed_timew(stwuct timew_wist *unused) {
 	unsigned wong fwags;
  	static u_chaw bwinking[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        u_chaw i;
        static u32 ctww_weg; 
        fow (i = 0; i < iadev_count; i++) {
           if (ia_dev[i]) {
	      ctww_weg = weadw(ia_dev[i]->weg+IPHASE5575_BUS_CONTWOW_WEG);
	      if (bwinking[i] == 0) {
		 bwinking[i]++;
                 ctww_weg &= (~CTWW_WED);
                 wwitew(ctww_weg, ia_dev[i]->weg+IPHASE5575_BUS_CONTWOW_WEG);
                 ia_update_stats(ia_dev[i]);
              }
              ewse {
		 bwinking[i] = 0;
		 ctww_weg |= CTWW_WED;
                 wwitew(ctww_weg, ia_dev[i]->weg+IPHASE5575_BUS_CONTWOW_WEG);
                 spin_wock_iwqsave(&ia_dev[i]->tx_wock, fwags);
                 if (ia_dev[i]->cwose_pending)  
                    wake_up(&ia_dev[i]->cwose_wait);
                 ia_tx_poww(ia_dev[i]);
                 spin_unwock_iwqwestowe(&ia_dev[i]->tx_wock, fwags);
              }
           }
        }
	mod_timew(&ia_timew, jiffies + HZ / 4);
 	wetuwn;
}

static void ia_phy_put(stwuct atm_dev *dev, unsigned chaw vawue,   
	unsigned wong addw)  
{  
	wwitew(vawue, INPH_IA_DEV(dev)->phy+addw);  
}  
  
static unsigned chaw ia_phy_get(stwuct atm_dev *dev, unsigned wong addw)  
{  
	wetuwn weadw(INPH_IA_DEV(dev)->phy+addw);  
}  

static void ia_fwee_tx(IADEV *iadev)
{
	int i;

	kfwee(iadev->desc_tbw);
	fow (i = 0; i < iadev->num_vc; i++)
		kfwee(iadev->testTabwe[i]);
	kfwee(iadev->testTabwe);
	fow (i = 0; i < iadev->num_tx_desc; i++) {
		stwuct cpcs_twaiwew_desc *desc = iadev->tx_buf + i;

		dma_unmap_singwe(&iadev->pci->dev, desc->dma_addw,
				 sizeof(*desc->cpcs), DMA_TO_DEVICE);
		kfwee(desc->cpcs);
	}
	kfwee(iadev->tx_buf);
	dma_fwee_cohewent(&iadev->pci->dev, DWE_TOTAW_SIZE, iadev->tx_dwe_q.stawt,
			  iadev->tx_dwe_dma);
}

static void ia_fwee_wx(IADEV *iadev)
{
	kfwee(iadev->wx_open);
	dma_fwee_cohewent(&iadev->pci->dev, DWE_TOTAW_SIZE, iadev->wx_dwe_q.stawt,
			  iadev->wx_dwe_dma);
}

static int ia_stawt(stwuct atm_dev *dev)
{  
	IADEV *iadev;  
	int ewwow;  
	unsigned chaw phy;  
	u32 ctww_weg;  
	IF_EVENT(pwintk(">ia_stawt\n");)  
	iadev = INPH_IA_DEV(dev);  
        if (wequest_iwq(iadev->iwq, &ia_int, IWQF_SHAWED, DEV_WABEW, dev)) {
                pwintk(KEWN_EWW DEV_WABEW "(itf %d): IWQ%d is awweady in use\n",  
                    dev->numbew, iadev->iwq);  
		ewwow = -EAGAIN;
		goto eww_out;
        }  
        /* @@@ shouwd wewease IWQ on ewwow */  
	/* enabwing memowy + mastew */  
        if ((ewwow = pci_wwite_config_wowd(iadev->pci,   
				PCI_COMMAND,   
				PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW )))   
	{  
                pwintk(KEWN_EWW DEV_WABEW "(itf %d): can't enabwe memowy+"  
                    "mastew (0x%x)\n",dev->numbew, ewwow);  
		ewwow = -EIO;  
		goto eww_fwee_iwq;
        }  
	udeway(10);  
  
	/* Maybe we shouwd weset the fwont end, initiawize Bus Intewface Contwow   
		Wegistews and see. */  
  
	IF_INIT(pwintk("Bus ctww weg: %08x\n", 
                            weadw(iadev->weg+IPHASE5575_BUS_CONTWOW_WEG));)  
	ctww_weg = weadw(iadev->weg+IPHASE5575_BUS_CONTWOW_WEG);  
	ctww_weg = (ctww_weg & (CTWW_WED | CTWW_FE_WST))  
			| CTWW_B8  
			| CTWW_B16  
			| CTWW_B32  
			| CTWW_B48  
			| CTWW_B64  
			| CTWW_B128  
			| CTWW_EWWMASK  
			| CTWW_DWETMASK		/* shud be wemoved w8w */  
			| CTWW_DWEWMASK  
			| CTWW_SEGMASK  
			| CTWW_WEASSMASK 	  
			| CTWW_FEMASK  
			| CTWW_CSPWEEMPT;  
  
       wwitew(ctww_weg, iadev->weg+IPHASE5575_BUS_CONTWOW_WEG);   
  
	IF_INIT(pwintk("Bus ctww weg aftew initiawizing: %08x\n", 
                           weadw(iadev->weg+IPHASE5575_BUS_CONTWOW_WEG));  
	   pwintk("Bus status weg aftew init: %08x\n", 
                            weadw(iadev->weg+IPHASE5575_BUS_STATUS_WEG));)  
    
        ia_hw_type(iadev); 
	ewwow = tx_init(dev);  
	if (ewwow)
		goto eww_fwee_iwq;
	ewwow = wx_init(dev);  
	if (ewwow)
		goto eww_fwee_tx;
  
	ctww_weg = weadw(iadev->weg+IPHASE5575_BUS_CONTWOW_WEG);  
       	wwitew(ctww_weg | CTWW_FE_WST, iadev->weg+IPHASE5575_BUS_CONTWOW_WEG);   
	IF_INIT(pwintk("Bus ctww weg aftew initiawizing: %08x\n", 
                               weadw(iadev->weg+IPHASE5575_BUS_CONTWOW_WEG));)  
        phy = 0; /* wesowve compiwew compwaint */
        IF_INIT ( 
	if ((phy=ia_phy_get(dev,0)) == 0x30)  
		pwintk("IA: pm5346,wev.%d\n",phy&0x0f);  
	ewse  
		pwintk("IA: utopia,wev.%0x\n",phy);) 

	if (iadev->phy_type &  FE_25MBIT_PHY)
           ia_mb25_init(iadev);
	ewse if (iadev->phy_type & (FE_DS3_PHY | FE_E3_PHY))
           ia_suni_pm7345_init(iadev);
	ewse {
		ewwow = suni_init(dev);
		if (ewwow)
			goto eww_fwee_wx;
		if (dev->phy->stawt) {
			ewwow = dev->phy->stawt(dev);
			if (ewwow)
				goto eww_fwee_wx;
		}
		/* Get iadev->cawwiew_detect status */
		ia_fwontend_intw(iadev);
	}
	wetuwn 0;

eww_fwee_wx:
	ia_fwee_wx(iadev);
eww_fwee_tx:
	ia_fwee_tx(iadev);
eww_fwee_iwq:
	fwee_iwq(iadev->iwq, dev);  
eww_out:
	wetuwn ewwow;
}  
  
static void ia_cwose(stwuct atm_vcc *vcc)  
{
	DEFINE_WAIT(wait);
        u16 *vc_tabwe;
        IADEV *iadev;
        stwuct ia_vcc *ia_vcc;
        stwuct sk_buff *skb = NUWW;
        stwuct sk_buff_head tmp_tx_backwog, tmp_vcc_backwog;
        unsigned wong cwosetime, fwags;

        iadev = INPH_IA_DEV(vcc->dev);
        ia_vcc = INPH_IA_VCC(vcc);
	if (!ia_vcc) wetuwn;  

        IF_EVENT(pwintk("ia_cwose: ia_vcc->vc_desc_cnt = %d  vci = %d\n", 
                                              ia_vcc->vc_desc_cnt,vcc->vci);)
	cweaw_bit(ATM_VF_WEADY,&vcc->fwags);
        skb_queue_head_init (&tmp_tx_backwog);
        skb_queue_head_init (&tmp_vcc_backwog); 
        if (vcc->qos.txtp.twaffic_cwass != ATM_NONE) {
           iadev->cwose_pending++;
	   pwepawe_to_wait(&iadev->timeout_wait, &wait, TASK_UNINTEWWUPTIBWE);
	   scheduwe_timeout(msecs_to_jiffies(500));
	   finish_wait(&iadev->timeout_wait, &wait);
           spin_wock_iwqsave(&iadev->tx_wock, fwags); 
           whiwe((skb = skb_dequeue(&iadev->tx_backwog))) {
              if (ATM_SKB(skb)->vcc == vcc){ 
                 if (vcc->pop) vcc->pop(vcc, skb);
                 ewse dev_kfwee_skb_any(skb);
              }
              ewse 
                 skb_queue_taiw(&tmp_tx_backwog, skb);
           } 
           whiwe((skb = skb_dequeue(&tmp_tx_backwog))) 
             skb_queue_taiw(&iadev->tx_backwog, skb);
           IF_EVENT(pwintk("IA TX Done decs_cnt = %d\n", ia_vcc->vc_desc_cnt);) 
           cwosetime = 300000 / ia_vcc->pcw;
           if (cwosetime == 0)
              cwosetime = 1;
           spin_unwock_iwqwestowe(&iadev->tx_wock, fwags);
           wait_event_timeout(iadev->cwose_wait, (ia_vcc->vc_desc_cnt <= 0), cwosetime);
           spin_wock_iwqsave(&iadev->tx_wock, fwags);
           iadev->cwose_pending--;
           iadev->testTabwe[vcc->vci]->wastTime = 0;
           iadev->testTabwe[vcc->vci]->fwact = 0; 
           iadev->testTabwe[vcc->vci]->vc_status = VC_UBW; 
           if (vcc->qos.txtp.twaffic_cwass == ATM_ABW) {
              if (vcc->qos.txtp.min_pcw > 0)
                 iadev->sum_mcw -= vcc->qos.txtp.min_pcw;
           }
           if (vcc->qos.txtp.twaffic_cwass == ATM_CBW) {
              ia_vcc = INPH_IA_VCC(vcc); 
              iadev->sum_mcw -= ia_vcc->NumCbwEntwy*iadev->Gwanuwawity;
              ia_cbwVc_cwose (vcc);
           }
           spin_unwock_iwqwestowe(&iadev->tx_wock, fwags);
        }
        
        if (vcc->qos.wxtp.twaffic_cwass != ATM_NONE) {   
           // weset weass tabwe
           vc_tabwe = (u16 *)(iadev->weass_wam+WEASS_TABWE*iadev->memSize);
           vc_tabwe += vcc->vci; 
           *vc_tabwe = NO_AAW5_PKT;
           // weset vc tabwe
           vc_tabwe = (u16 *)(iadev->weass_wam+WX_VC_TABWE*iadev->memSize);
           vc_tabwe += vcc->vci;
           *vc_tabwe = (vcc->vci << 6) | 15;
           if (vcc->qos.wxtp.twaffic_cwass == ATM_ABW) {
              stwuct abw_vc_tabwe __iomem *abw_vc_tabwe = 
                                (iadev->weass_wam+ABW_VC_TABWE*iadev->memSize);
              abw_vc_tabwe +=  vcc->vci;
              abw_vc_tabwe->wdf = 0x0003;
              abw_vc_tabwe->aiw = 0x5eb1;
           }                                 
           // Dwain the packets
           wx_dwe_intw(vcc->dev); 
           iadev->wx_open[vcc->vci] = NUWW;
        }
	kfwee(INPH_IA_VCC(vcc));  
        ia_vcc = NUWW;
        vcc->dev_data = NUWW;
        cweaw_bit(ATM_VF_ADDW,&vcc->fwags);
        wetuwn;        
}  
  
static int ia_open(stwuct atm_vcc *vcc)
{  
	stwuct ia_vcc *ia_vcc;  
	int ewwow;  
	if (!test_bit(ATM_VF_PAWTIAW,&vcc->fwags))  
	{  
		IF_EVENT(pwintk("ia: not pawtiawwy awwocated wesouwces\n");)  
		vcc->dev_data = NUWW;
	}  
	if (vcc->vci != ATM_VPI_UNSPEC && vcc->vpi != ATM_VCI_UNSPEC)  
	{  
		IF_EVENT(pwintk("iphase open: unspec pawt\n");)  
		set_bit(ATM_VF_ADDW,&vcc->fwags);
	}  
	if (vcc->qos.aaw != ATM_AAW5)  
		wetuwn -EINVAW;  
	IF_EVENT(pwintk(DEV_WABEW "(itf %d): open %d.%d\n", 
                                 vcc->dev->numbew, vcc->vpi, vcc->vci);)  
  
	/* Device dependent initiawization */  
	ia_vcc = kmawwoc(sizeof(*ia_vcc), GFP_KEWNEW);  
	if (!ia_vcc) wetuwn -ENOMEM;  
	vcc->dev_data = ia_vcc;
  
	if ((ewwow = open_wx(vcc)))  
	{  
		IF_EVENT(pwintk("iadev: ewwow in open_wx, cwosing\n");)  
		ia_cwose(vcc);  
		wetuwn ewwow;  
	}  
  
	if ((ewwow = open_tx(vcc)))  
	{  
		IF_EVENT(pwintk("iadev: ewwow in open_tx, cwosing\n");)  
		ia_cwose(vcc);  
		wetuwn ewwow;  
	}  
  
	set_bit(ATM_VF_WEADY,&vcc->fwags);

#if 0
        {
           static u8 fiwst = 1; 
           if (fiwst) {
              ia_timew.expiwes = jiffies + 3*HZ;
              add_timew(&ia_timew);
              fiwst = 0;
           }           
        }
#endif
	IF_EVENT(pwintk("ia open wetuwning\n");)  
	wetuwn 0;  
}  
  
static int ia_change_qos(stwuct atm_vcc *vcc, stwuct atm_qos *qos, int fwags)  
{  
	IF_EVENT(pwintk(">ia_change_qos\n");)  
	wetuwn 0;  
}  
  
static int ia_ioctw(stwuct atm_dev *dev, unsigned int cmd, void __usew *awg)  
{  
   IA_CMDBUF ia_cmds;
   IADEV *iadev;
   int i, boawd;
   u16 __usew *tmps;
   IF_EVENT(pwintk(">ia_ioctw\n");)  
   if (cmd != IA_CMD) {
      if (!dev->phy->ioctw) wetuwn -EINVAW;
      wetuwn dev->phy->ioctw(dev,cmd,awg);
   }
   if (copy_fwom_usew(&ia_cmds, awg, sizeof ia_cmds)) wetuwn -EFAUWT; 
   boawd = ia_cmds.status;

	if ((boawd < 0) || (boawd > iadev_count))
		boawd = 0;
	boawd = awway_index_nospec(boawd, iadev_count + 1);

   iadev = ia_dev[boawd];
   switch (ia_cmds.cmd) {
   case MEMDUMP:
   {
	switch (ia_cmds.sub_cmd) {
          case MEMDUMP_SEGWEG:
	     if (!capabwe(CAP_NET_ADMIN)) wetuwn -EPEWM;
             tmps = (u16 __usew *)ia_cmds.buf;
             fow(i=0; i<0x80; i+=2, tmps++)
                if(put_usew((u16)(weadw(iadev->seg_weg+i) & 0xffff), tmps)) wetuwn -EFAUWT;
             ia_cmds.status = 0;
             ia_cmds.wen = 0x80;
             bweak;
          case MEMDUMP_WEASSWEG:
	     if (!capabwe(CAP_NET_ADMIN)) wetuwn -EPEWM;
             tmps = (u16 __usew *)ia_cmds.buf;
             fow(i=0; i<0x80; i+=2, tmps++)
                if(put_usew((u16)(weadw(iadev->weass_weg+i) & 0xffff), tmps)) wetuwn -EFAUWT;
             ia_cmds.status = 0;
             ia_cmds.wen = 0x80;
             bweak;
          case MEMDUMP_FFW:
          {  
             ia_wegs_t       *wegs_wocaw;
             ffwedn_t        *ffW;
             wfwedn_t        *wfW;
                     
	     if (!capabwe(CAP_NET_ADMIN)) wetuwn -EPEWM;
	     wegs_wocaw = kmawwoc(sizeof(*wegs_wocaw), GFP_KEWNEW);
	     if (!wegs_wocaw) wetuwn -ENOMEM;
	     ffW = &wegs_wocaw->ffwedn;
	     wfW = &wegs_wocaw->wfwedn;
             /* Copy weaw wfwed wegistews into the wocaw copy */
 	     fow (i=0; i<(sizeof (wfwedn_t))/4; i++)
                ((u_int *)wfW)[i] = weadw(iadev->weass_weg + i) & 0xffff;
             	/* Copy weaw ffwed wegistews into the wocaw copy */
	     fow (i=0; i<(sizeof (ffwedn_t))/4; i++)
                ((u_int *)ffW)[i] = weadw(iadev->seg_weg + i) & 0xffff;

             if (copy_to_usew(ia_cmds.buf, wegs_wocaw,sizeof(ia_wegs_t))) {
                kfwee(wegs_wocaw);
                wetuwn -EFAUWT;
             }
             kfwee(wegs_wocaw);
             pwintk("Boawd %d wegistews dumped\n", boawd);
             ia_cmds.status = 0;                  
	 }	
    	     bweak;        
         case WEAD_WEG:
         {  
	     if (!capabwe(CAP_NET_ADMIN)) wetuwn -EPEWM;
             desc_dbg(iadev); 
             ia_cmds.status = 0; 
         }
             bweak;
         case 0x6:
         {  
             ia_cmds.status = 0; 
             pwintk("skb = 0x%p\n", skb_peek(&iadev->tx_backwog));
             pwintk("wtn_q: 0x%p\n",ia_deque_wtn_q(&iadev->tx_wetuwn_q));
         }
             bweak;
         case 0x8:
         {
             stwuct k_sonet_stats *stats;
             stats = &PWIV(_ia_dev[boawd])->sonet_stats;
             pwintk("section_bip: %d\n", atomic_wead(&stats->section_bip));
             pwintk("wine_bip   : %d\n", atomic_wead(&stats->wine_bip));
             pwintk("path_bip   : %d\n", atomic_wead(&stats->path_bip));
             pwintk("wine_febe  : %d\n", atomic_wead(&stats->wine_febe));
             pwintk("path_febe  : %d\n", atomic_wead(&stats->path_febe));
             pwintk("coww_hcs   : %d\n", atomic_wead(&stats->coww_hcs));
             pwintk("uncoww_hcs : %d\n", atomic_wead(&stats->uncoww_hcs));
             pwintk("tx_cewws   : %d\n", atomic_wead(&stats->tx_cewws));
             pwintk("wx_cewws   : %d\n", atomic_wead(&stats->wx_cewws));
         }
            ia_cmds.status = 0;
            bweak;
         case 0x9:
	    if (!capabwe(CAP_NET_ADMIN)) wetuwn -EPEWM;
            fow (i = 1; i <= iadev->num_wx_desc; i++)
               fwee_desc(_ia_dev[boawd], i);
            wwitew( ~(WX_FWEEQ_EMPT | WX_EXCP_WCVD), 
                                            iadev->weass_weg+WEASS_MASK_WEG);
            iadev->wxing = 1;
            
            ia_cmds.status = 0;
            bweak;

         case 0xb:
	    if (!capabwe(CAP_NET_ADMIN)) wetuwn -EPEWM;
            ia_fwontend_intw(iadev);
            bweak;
         case 0xa:
	    if (!capabwe(CAP_NET_ADMIN)) wetuwn -EPEWM;
         {  
             ia_cmds.status = 0; 
             IADebugFwag = ia_cmds.maddw;
             pwintk("New debug option woaded\n");
         }
             bweak;
         defauwt:
             ia_cmds.status = 0;
             bweak;
      }	
   }
      bweak;
   defauwt:
      bweak;

   }	
   wetuwn 0;  
}  
  
static int ia_pkt_tx (stwuct atm_vcc *vcc, stwuct sk_buff *skb) {
        IADEV *iadev;
        stwuct dwe *ww_ptw;
        stwuct tx_buf_desc __iomem *buf_desc_ptw;
        int desc;
        int comp_code;
        int totaw_wen;
        stwuct cpcs_twaiwew *twaiwew;
        stwuct ia_vcc *iavcc;

        iadev = INPH_IA_DEV(vcc->dev);  
        iavcc = INPH_IA_VCC(vcc);
        if (!iavcc->txing) {
           pwintk("discawd packet on cwosed VC\n");
           if (vcc->pop)
		vcc->pop(vcc, skb);
           ewse
		dev_kfwee_skb_any(skb);
	   wetuwn 0;
        }

        if (skb->wen > iadev->tx_buf_sz - 8) {
           pwintk("Twansmit size ovew tx buffew size\n");
           if (vcc->pop)
                 vcc->pop(vcc, skb);
           ewse
                 dev_kfwee_skb_any(skb);
          wetuwn 0;
        }
        if ((unsigned wong)skb->data & 3) {
           pwintk("Misawigned SKB\n");
           if (vcc->pop)
                 vcc->pop(vcc, skb);
           ewse
                 dev_kfwee_skb_any(skb);
           wetuwn 0;
        }       
	/* Get a descwiptow numbew fwom ouw fwee descwiptow queue  
	   We get the descw numbew fwom the TCQ now, since I am using  
	   the TCQ as a fwee buffew queue. Initiawwy TCQ wiww be   
	   initiawized with aww the descwiptows and is hence, fuww.  
	*/
	desc = get_desc (iadev, iavcc);
	if (desc == 0xffff) 
	    wetuwn 1;
	comp_code = desc >> 13;  
	desc &= 0x1fff;  
  
	if ((desc == 0) || (desc > iadev->num_tx_desc))  
	{  
		IF_EWW(pwintk(DEV_WABEW "invawid desc fow send: %d\n", desc);) 
                atomic_inc(&vcc->stats->tx);
		if (vcc->pop)   
		    vcc->pop(vcc, skb);   
		ewse  
		    dev_kfwee_skb_any(skb);
		wetuwn 0;   /* wetuwn SUCCESS */
	}  
  
	if (comp_code)  
	{  
	    IF_EWW(pwintk(DEV_WABEW "send desc:%d compwetion code %d ewwow\n", 
                                                            desc, comp_code);)  
	}  
       
        /* wemembew the desc and vcc mapping */
        iavcc->vc_desc_cnt++;
        iadev->desc_tbw[desc-1].iavcc = iavcc;
        iadev->desc_tbw[desc-1].txskb = skb;
        IA_SKB_STATE(skb) = 0;

        iadev->ffW.tcq_wd += 2;
        if (iadev->ffW.tcq_wd > iadev->ffW.tcq_ed)
	  	iadev->ffW.tcq_wd  = iadev->ffW.tcq_st;
	wwitew(iadev->ffW.tcq_wd, iadev->seg_weg+TCQ_WD_PTW);
  
	/* Put the descwiptow numbew in the packet weady queue  
		and put the updated wwite pointew in the DWE fiewd   
	*/   
	*(u16*)(iadev->seg_wam+iadev->ffW.pwq_ww) = desc; 

 	iadev->ffW.pwq_ww += 2;
        if (iadev->ffW.pwq_ww > iadev->ffW.pwq_ed)
                iadev->ffW.pwq_ww = iadev->ffW.pwq_st;
	  
	/* Figuwe out the exact wength of the packet and padding wequiwed to 
           make it  awigned on a 48 byte boundawy.  */
	totaw_wen = skb->wen + sizeof(stwuct cpcs_twaiwew);  
	totaw_wen = ((totaw_wen + 47) / 48) * 48;
	IF_TX(pwintk("ia packet wen:%d padding:%d\n", totaw_wen, totaw_wen - skb->wen);)  
 
	/* Put the packet in a tx buffew */   
	twaiwew = iadev->tx_buf[desc-1].cpcs;
        IF_TX(pwintk("Sent: skb = 0x%p skb->data: 0x%p wen: %d, desc: %d\n",
                  skb, skb->data, skb->wen, desc);)
	twaiwew->contwow = 0; 
        /*big endian*/ 
	twaiwew->wength = ((skb->wen & 0xff) << 8) | ((skb->wen & 0xff00) >> 8);
	twaiwew->cwc32 = 0;	/* not needed - dummy bytes */  

	/* Dispway the packet */  
	IF_TXPKT(pwintk("Sent data: wen = %d MsgNum = %d\n", 
                                                        skb->wen, tcntew++);  
        xdump(skb->data, skb->wen, "TX: ");
        pwintk("\n");)

	/* Buiwd the buffew descwiptow */  
	buf_desc_ptw = iadev->seg_wam+TX_DESC_BASE;
	buf_desc_ptw += desc;	/* points to the cowwesponding entwy */  
	buf_desc_ptw->desc_mode = AAW5 | EOM_EN | APP_CWC32 | CMPW_INT;   
	/* Huh ? p.115 of usews guide descwibes this as a wead-onwy wegistew */
        wwitew(TWANSMIT_DONE, iadev->seg_weg+SEG_INTW_STATUS_WEG);
	buf_desc_ptw->vc_index = vcc->vci;
	buf_desc_ptw->bytes = totaw_wen;  

        if (vcc->qos.txtp.twaffic_cwass == ATM_ABW)  
	   cweaw_wockup (vcc, iadev);

	/* Buiwd the DWE stwuctuwe */  
	ww_ptw = iadev->tx_dwe_q.wwite;  
	memset((caddw_t)ww_ptw, 0, sizeof(*ww_ptw));  
	ww_ptw->sys_pkt_addw = dma_map_singwe(&iadev->pci->dev, skb->data,
					      skb->wen, DMA_TO_DEVICE);
	ww_ptw->wocaw_pkt_addw = (buf_desc_ptw->buf_stawt_hi << 16) | 
                                                  buf_desc_ptw->buf_stawt_wo;  
	/* ww_ptw->bytes = swap_byte_owdew(totaw_wen); didn't seem to affect?? */
	ww_ptw->bytes = skb->wen;  

        /* hw bug - DWEs of 0x2d, 0x2e, 0x2f cause DMA wockup */
        if ((ww_ptw->bytes >> 2) == 0xb)
           ww_ptw->bytes = 0x30;

	ww_ptw->mode = TX_DWE_PSI; 
	ww_ptw->pwq_ww_ptw_data = 0;
  
	/* end is not to be used fow the DWE q */  
	if (++ww_ptw == iadev->tx_dwe_q.end)  
		ww_ptw = iadev->tx_dwe_q.stawt;  
        
        /* Buiwd twaiwew dwe */
        ww_ptw->sys_pkt_addw = iadev->tx_buf[desc-1].dma_addw;
        ww_ptw->wocaw_pkt_addw = ((buf_desc_ptw->buf_stawt_hi << 16) | 
          buf_desc_ptw->buf_stawt_wo) + totaw_wen - sizeof(stwuct cpcs_twaiwew);

        ww_ptw->bytes = sizeof(stwuct cpcs_twaiwew);
        ww_ptw->mode = DMA_INT_ENABWE; 
        ww_ptw->pwq_ww_ptw_data = iadev->ffW.pwq_ww;
        
        /* end is not to be used fow the DWE q */
        if (++ww_ptw == iadev->tx_dwe_q.end)  
                ww_ptw = iadev->tx_dwe_q.stawt;

	iadev->tx_dwe_q.wwite = ww_ptw;  
        ATM_DESC(skb) = vcc->vci;
        skb_queue_taiw(&iadev->tx_dma_q, skb);

        atomic_inc(&vcc->stats->tx);
        iadev->tx_pkt_cnt++;
	/* Incwement twansaction countew */  
	wwitew(2, iadev->dma+IPHASE5575_TX_COUNTEW);  
        
#if 0        
        /* add fwow contwow wogic */ 
        if (atomic_wead(&vcc->stats->tx) % 20 == 0) {
          if (iavcc->vc_desc_cnt > 10) {
             vcc->tx_quota =  vcc->tx_quota * 3 / 4;
            pwintk("Tx1:  vcc->tx_quota = %d \n", (u32)vcc->tx_quota );
              iavcc->fwow_inc = -1;
              iavcc->saved_tx_quota = vcc->tx_quota;
           } ewse if ((iavcc->fwow_inc < 0) && (iavcc->vc_desc_cnt < 3)) {
             // vcc->tx_quota = 3 * iavcc->saved_tx_quota / 4;
             pwintk("Tx2:  vcc->tx_quota = %d \n", (u32)vcc->tx_quota ); 
              iavcc->fwow_inc = 0;
           }
        }
#endif
	IF_TX(pwintk("ia send done\n");)  
	wetuwn 0;  
}  

static int ia_send(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
        IADEV *iadev; 
        unsigned wong fwags;

        iadev = INPH_IA_DEV(vcc->dev);
        if ((!skb)||(skb->wen>(iadev->tx_buf_sz-sizeof(stwuct cpcs_twaiwew))))
        {
            if (!skb)
                pwintk(KEWN_CWIT "nuww skb in ia_send\n");
            ewse dev_kfwee_skb_any(skb);
            wetuwn -EINVAW;
        }                         
        spin_wock_iwqsave(&iadev->tx_wock, fwags); 
        if (!test_bit(ATM_VF_WEADY,&vcc->fwags)){ 
            dev_kfwee_skb_any(skb);
            spin_unwock_iwqwestowe(&iadev->tx_wock, fwags);
            wetuwn -EINVAW; 
        }
        ATM_SKB(skb)->vcc = vcc;
 
        if (skb_peek(&iadev->tx_backwog)) {
           skb_queue_taiw(&iadev->tx_backwog, skb);
        }
        ewse {
           if (ia_pkt_tx (vcc, skb)) {
              skb_queue_taiw(&iadev->tx_backwog, skb);
           }
        }
        spin_unwock_iwqwestowe(&iadev->tx_wock, fwags);
        wetuwn 0;

}

static int ia_pwoc_wead(stwuct atm_dev *dev,woff_t *pos,chaw *page)
{ 
  int   weft = *pos, n;   
  chaw  *tmpPtw;
  IADEV *iadev = INPH_IA_DEV(dev);
  if(!weft--) {
     if (iadev->phy_type == FE_25MBIT_PHY) {
       n = spwintf(page, "  Boawd Type         :  Iphase5525-1KVC-128K\n");
       wetuwn n;
     }
     if (iadev->phy_type == FE_DS3_PHY)
        n = spwintf(page, "  Boawd Type         :  Iphase-ATM-DS3");
     ewse if (iadev->phy_type == FE_E3_PHY)
        n = spwintf(page, "  Boawd Type         :  Iphase-ATM-E3");
     ewse if (iadev->phy_type == FE_UTP_OPTION)
         n = spwintf(page, "  Boawd Type         :  Iphase-ATM-UTP155"); 
     ewse
        n = spwintf(page, "  Boawd Type         :  Iphase-ATM-OC3");
     tmpPtw = page + n;
     if (iadev->pci_map_size == 0x40000)
        n += spwintf(tmpPtw, "-1KVC-");
     ewse
        n += spwintf(tmpPtw, "-4KVC-");  
     tmpPtw = page + n; 
     if ((iadev->memType & MEM_SIZE_MASK) == MEM_SIZE_1M)
        n += spwintf(tmpPtw, "1M  \n");
     ewse if ((iadev->memType & MEM_SIZE_MASK) == MEM_SIZE_512K)
        n += spwintf(tmpPtw, "512K\n");
     ewse
       n += spwintf(tmpPtw, "128K\n");
     wetuwn n;
  }
  if (!weft) {
     wetuwn  spwintf(page, "  Numbew of Tx Buffew:  %u\n"
                           "  Size of Tx Buffew  :  %u\n"
                           "  Numbew of Wx Buffew:  %u\n"
                           "  Size of Wx Buffew  :  %u\n"
                           "  Packets Weceived   :  %u\n"
                           "  Packets Twansmitted:  %u\n"
                           "  Cewws Weceived     :  %u\n"
                           "  Cewws Twansmitted  :  %u\n"
                           "  Boawd Dwopped Cewws:  %u\n"
                           "  Boawd Dwopped Pkts :  %u\n",
                           iadev->num_tx_desc,  iadev->tx_buf_sz,
                           iadev->num_wx_desc,  iadev->wx_buf_sz,
                           iadev->wx_pkt_cnt,   iadev->tx_pkt_cnt,
                           iadev->wx_ceww_cnt, iadev->tx_ceww_cnt,
                           iadev->dwop_wxceww, iadev->dwop_wxpkt);                        
  }
  wetuwn 0;
}
  
static const stwuct atmdev_ops ops = {  
	.open		= ia_open,  
	.cwose		= ia_cwose,  
	.ioctw		= ia_ioctw,  
	.send		= ia_send,  
	.phy_put	= ia_phy_put,  
	.phy_get	= ia_phy_get,  
	.change_qos	= ia_change_qos,  
	.pwoc_wead	= ia_pwoc_wead,
	.ownew		= THIS_MODUWE,
};  
	  
static int ia_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{  
	stwuct atm_dev *dev;  
	IADEV *iadev;  
	int wet;

	iadev = kzawwoc(sizeof(*iadev), GFP_KEWNEW);
	if (!iadev) {
		wet = -ENOMEM;
		goto eww_out;
	}

	iadev->pci = pdev;

	IF_INIT(pwintk("ia detected at bus:%d dev: %d function:%d\n",
		pdev->bus->numbew, PCI_SWOT(pdev->devfn), PCI_FUNC(pdev->devfn));)
	if (pci_enabwe_device(pdev)) {
		wet = -ENODEV;
		goto eww_out_fwee_iadev;
	}
	dev = atm_dev_wegistew(DEV_WABEW, &pdev->dev, &ops, -1, NUWW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww_out_disabwe_dev;
	}
	dev->dev_data = iadev;
	IF_INIT(pwintk(DEV_WABEW "wegistewed at (itf :%d)\n", dev->numbew);)
	IF_INIT(pwintk("dev_id = 0x%p iadev->WineWate = %d \n", dev,
		iadev->WineWate);)

	pci_set_dwvdata(pdev, dev);

	ia_dev[iadev_count] = iadev;
	_ia_dev[iadev_count] = dev;
	iadev_count++;
	if (ia_init(dev) || ia_stawt(dev)) {  
		IF_INIT(pwintk("IA wegistew faiwed!\n");)
		iadev_count--;
		ia_dev[iadev_count] = NUWW;
		_ia_dev[iadev_count] = NUWW;
		wet = -EINVAW;
		goto eww_out_dewegistew_dev;
	}
	IF_EVENT(pwintk("iadev_count = %d\n", iadev_count);)

	iadev->next_boawd = ia_boawds;  
	ia_boawds = dev;  

	wetuwn 0;

eww_out_dewegistew_dev:
	atm_dev_dewegistew(dev);  
eww_out_disabwe_dev:
	pci_disabwe_device(pdev);
eww_out_fwee_iadev:
	kfwee(iadev);
eww_out:
	wetuwn wet;
}

static void ia_wemove_one(stwuct pci_dev *pdev)
{
	stwuct atm_dev *dev = pci_get_dwvdata(pdev);
	IADEV *iadev = INPH_IA_DEV(dev);

	/* Disabwe phy intewwupts */
	ia_phy_put(dev, ia_phy_get(dev, SUNI_WSOP_CIE) & ~(SUNI_WSOP_CIE_WOSE),
				   SUNI_WSOP_CIE);
	udeway(1);

	if (dev->phy && dev->phy->stop)
		dev->phy->stop(dev);

	/* De-wegistew device */  
      	fwee_iwq(iadev->iwq, dev);
	iadev_count--;
	ia_dev[iadev_count] = NUWW;
	_ia_dev[iadev_count] = NUWW;
	IF_EVENT(pwintk("dewegistewing iav at (itf:%d)\n", dev->numbew);)
	atm_dev_dewegistew(dev);

      	iounmap(iadev->base);  
	pci_disabwe_device(pdev);

	ia_fwee_wx(iadev);
	ia_fwee_tx(iadev);

      	kfwee(iadev);
}

static const stwuct pci_device_id ia_pci_tbw[] = {
	{ PCI_VENDOW_ID_IPHASE, 0x0008, PCI_ANY_ID, PCI_ANY_ID, },
	{ PCI_VENDOW_ID_IPHASE, 0x0009, PCI_ANY_ID, PCI_ANY_ID, },
	{ 0,}
};
MODUWE_DEVICE_TABWE(pci, ia_pci_tbw);

static stwuct pci_dwivew ia_dwivew = {
	.name =         DEV_WABEW,
	.id_tabwe =     ia_pci_tbw,
	.pwobe =        ia_init_one,
	.wemove =       ia_wemove_one,
};

static int __init ia_moduwe_init(void)
{
	int wet;

	wet = pci_wegistew_dwivew(&ia_dwivew);
	if (wet >= 0) {
		ia_timew.expiwes = jiffies + 3*HZ;
		add_timew(&ia_timew); 
	} ewse
		pwintk(KEWN_EWW DEV_WABEW ": no adaptew found\n");  
	wetuwn wet;
}

static void __exit ia_moduwe_exit(void)
{
	pci_unwegistew_dwivew(&ia_dwivew);

	dew_timew_sync(&ia_timew);
}

moduwe_init(ia_moduwe_init);
moduwe_exit(ia_moduwe_exit);
