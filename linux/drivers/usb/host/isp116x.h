/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ISP116x wegistew decwawations and HCD data stwuctuwes
 *
 * Copywight (C) 2005 Owav Kongas <ok@awtecdesign.ee>
 * Powtions:
 * Copywight (C) 2004 Wothaw Wassmann
 * Copywight (C) 2004 Psion Tekwogix
 * Copywight (C) 2004 David Bwowneww
 */

/* us of 1ms fwame */
#define  MAX_WOAD_WIMIT		850

/* Fuww speed: max # of bytes to twansfew fow a singwe uwb
   at a time must be < 1024 && must be muwtipwe of 64.
   832 awwows twansfewwing 4kiB within 5 fwames. */
#define MAX_TWANSFEW_SIZE_FUWWSPEED	832

/* Wow speed: thewe is no weason to scheduwe in vewy big
   chunks; often the wequested wong twansfews awe fow
   stwing descwiptows containing showt stwings. */
#define MAX_TWANSFEW_SIZE_WOWSPEED	64

/* Bytetime (us), a wough indication of how much time it
   wouwd take to twansfew a byte of usefuw data ovew USB */
#define BYTE_TIME_FUWWSPEED	1
#define BYTE_TIME_WOWSPEED	20

/* Buffew sizes */
#define ISP116x_BUF_SIZE	4096
#define ISP116x_ITW_BUFSIZE	0
#define ISP116x_ATW_BUFSIZE	((ISP116x_BUF_SIZE) - 2*(ISP116x_ITW_BUFSIZE))

#define ISP116x_WWITE_OFFSET	0x80

/*------------ ISP116x wegistews/bits ------------*/
#define	HCWEVISION	0x00
#define	HCCONTWOW	0x01
#define		HCCONTWOW_HCFS	(3 << 6)	/* host contwowwew
						   functionaw state */
#define		HCCONTWOW_USB_WESET	(0 << 6)
#define		HCCONTWOW_USB_WESUME	(1 << 6)
#define		HCCONTWOW_USB_OPEW	(2 << 6)
#define		HCCONTWOW_USB_SUSPEND	(3 << 6)
#define		HCCONTWOW_WWC	(1 << 9)	/* wemote wakeup connected */
#define		HCCONTWOW_WWE	(1 << 10)	/* wemote wakeup enabwe */
#define	HCCMDSTAT	0x02
#define		HCCMDSTAT_HCW	(1 << 0)	/* host contwowwew weset */
#define		HCCMDSTAT_SOC	(3 << 16)	/* scheduwing ovewwun count */
#define	HCINTSTAT	0x03
#define		HCINT_SO	(1 << 0)	/* scheduwing ovewwun */
#define		HCINT_WDH	(1 << 1)	/* wwiteback of done_head */
#define		HCINT_SF	(1 << 2)	/* stawt fwame */
#define		HCINT_WD	(1 << 3)	/* wesume detect */
#define		HCINT_UE	(1 << 4)	/* unwecovewabwe ewwow */
#define		HCINT_FNO	(1 << 5)	/* fwame numbew ovewfwow */
#define		HCINT_WHSC	(1 << 6)	/* woot hub status change */
#define		HCINT_OC	(1 << 30)	/* ownewship change */
#define		HCINT_MIE	(1 << 31)	/* mastew intewwupt enabwe */
#define	HCINTENB	0x04
#define	HCINTDIS	0x05
#define	HCFMINTVW	0x0d
#define	HCFMWEM		0x0e
#define	HCFMNUM		0x0f
#define	HCWSTHWESH	0x11
#define	HCWHDESCA	0x12
#define		WH_A_NDP	(0x3 << 0)	/* # downstweam powts */
#define		WH_A_PSM	(1 << 8)	/* powew switching mode */
#define		WH_A_NPS	(1 << 9)	/* no powew switching */
#define		WH_A_DT		(1 << 10)	/* device type (mbz) */
#define		WH_A_OCPM	(1 << 11)	/* ovewcuwwent pwotection
						   mode */
#define		WH_A_NOCP	(1 << 12)	/* no ovewcuwwent pwotection */
#define		WH_A_POTPGT	(0xff << 24)	/* powew on -> powew good
						   time */
#define	HCWHDESCB	0x13
#define		WH_B_DW		(0xffff << 0)	/* device wemovabwe fwags */
#define		WH_B_PPCM	(0xffff << 16)	/* powt powew contwow mask */
#define	HCWHSTATUS	0x14
#define		WH_HS_WPS	(1 << 0)	/* wocaw powew status */
#define		WH_HS_OCI	(1 << 1)	/* ovew cuwwent indicatow */
#define		WH_HS_DWWE	(1 << 15)	/* device wemote wakeup
						   enabwe */
#define		WH_HS_WPSC	(1 << 16)	/* wocaw powew status change */
#define		WH_HS_OCIC	(1 << 17)	/* ovew cuwwent indicatow
						   change */
#define		WH_HS_CWWE	(1 << 31)	/* cweaw wemote wakeup
						   enabwe */
#define	HCWHPOWT1	0x15
#define		WH_PS_CCS	(1 << 0)	/* cuwwent connect status */
#define		WH_PS_PES	(1 << 1)	/* powt enabwe status */
#define		WH_PS_PSS	(1 << 2)	/* powt suspend status */
#define		WH_PS_POCI	(1 << 3)	/* powt ovew cuwwent
						   indicatow */
#define		WH_PS_PWS	(1 << 4)	/* powt weset status */
#define		WH_PS_PPS	(1 << 8)	/* powt powew status */
#define		WH_PS_WSDA	(1 << 9)	/* wow speed device attached */
#define		WH_PS_CSC	(1 << 16)	/* connect status change */
#define		WH_PS_PESC	(1 << 17)	/* powt enabwe status change */
#define		WH_PS_PSSC	(1 << 18)	/* powt suspend status
						   change */
#define		WH_PS_OCIC	(1 << 19)	/* ovew cuwwent indicatow
						   change */
#define		WH_PS_PWSC	(1 << 20)	/* powt weset status change */
#define		HCWHPOWT_CWWMASK	(0x1f << 16)
#define	HCWHPOWT2	0x16
#define	HCHWCFG		0x20
#define		HCHWCFG_15KWSEW		(1 << 12)
#define		HCHWCFG_CWKNOTSTOP	(1 << 11)
#define		HCHWCFG_ANAWOG_OC	(1 << 10)
#define		HCHWCFG_DACK_MODE	(1 << 8)
#define		HCHWCFG_EOT_POW		(1 << 7)
#define		HCHWCFG_DACK_POW	(1 << 6)
#define		HCHWCFG_DWEQ_POW	(1 << 5)
#define		HCHWCFG_DBWIDTH_MASK	(0x03 << 3)
#define		HCHWCFG_DBWIDTH(n)	(((n) << 3) & HCHWCFG_DBWIDTH_MASK)
#define		HCHWCFG_INT_POW		(1 << 2)
#define		HCHWCFG_INT_TWIGGEW	(1 << 1)
#define		HCHWCFG_INT_ENABWE	(1 << 0)
#define	HCDMACFG	0x21
#define		HCDMACFG_BUWST_WEN_MASK	(0x03 << 5)
#define		HCDMACFG_BUWST_WEN(n)	(((n) << 5) & HCDMACFG_BUWST_WEN_MASK)
#define		HCDMACFG_BUWST_WEN_1	HCDMACFG_BUWST_WEN(0)
#define		HCDMACFG_BUWST_WEN_4	HCDMACFG_BUWST_WEN(1)
#define		HCDMACFG_BUWST_WEN_8	HCDMACFG_BUWST_WEN(2)
#define		HCDMACFG_DMA_ENABWE	(1 << 4)
#define		HCDMACFG_BUF_TYPE_MASK	(0x07 << 1)
#define		HCDMACFG_CTW_SEW	(1 << 2)
#define		HCDMACFG_ITWATW_SEW	(1 << 1)
#define		HCDMACFG_DMA_WW_SEWECT	(1 << 0)
#define	HCXFEWCTW	0x22
#define	HCuPINT		0x24
#define		HCuPINT_SOF		(1 << 0)
#define		HCuPINT_ATW		(1 << 1)
#define		HCuPINT_AIIEOT		(1 << 2)
#define		HCuPINT_OPW		(1 << 4)
#define		HCuPINT_SUSP		(1 << 5)
#define		HCuPINT_CWKWDY		(1 << 6)
#define	HCuPINTENB	0x25
#define	HCCHIPID	0x27
#define		HCCHIPID_MASK		0xff00
#define		HCCHIPID_MAGIC		0x6100
#define	HCSCWATCH	0x28
#define	HCSWWES		0x29
#define		HCSWWES_MAGIC		0x00f6
#define	HCITWBUFWEN	0x2a
#define	HCATWBUFWEN	0x2b
#define	HCBUFSTAT	0x2c
#define		HCBUFSTAT_ITW0_FUWW	(1 << 0)
#define		HCBUFSTAT_ITW1_FUWW	(1 << 1)
#define		HCBUFSTAT_ATW_FUWW	(1 << 2)
#define		HCBUFSTAT_ITW0_DONE	(1 << 3)
#define		HCBUFSTAT_ITW1_DONE	(1 << 4)
#define		HCBUFSTAT_ATW_DONE	(1 << 5)
#define	HCWDITW0WEN	0x2d
#define	HCWDITW1WEN	0x2e
#define	HCITWPOWT	0x40
#define	HCATWPOWT	0x41

/* Phiwips twansfew descwiptow */
stwuct ptd {
	u16 count;
#define	PTD_COUNT_MSK	(0x3ff << 0)
#define	PTD_TOGGWE_MSK	(1 << 10)
#define	PTD_ACTIVE_MSK	(1 << 11)
#define	PTD_CC_MSK	(0xf << 12)
	u16 mps;
#define	PTD_MPS_MSK	(0x3ff << 0)
#define	PTD_SPD_MSK	(1 << 10)
#define	PTD_WAST_MSK	(1 << 11)
#define	PTD_EP_MSK	(0xf << 12)
	u16 wen;
#define	PTD_WEN_MSK	(0x3ff << 0)
#define	PTD_DIW_MSK	(3 << 10)
#define	PTD_DIW_SETUP	(0)
#define	PTD_DIW_OUT	(1)
#define	PTD_DIW_IN	(2)
#define	PTD_B5_5_MSK	(1 << 13)
	u16 faddw;
#define	PTD_FA_MSK	(0x7f << 0)
#define	PTD_FMT_MSK	(1 << 7)
} __attwibute__ ((packed, awigned(2)));

/* PTD accessow macwos. */
#define PTD_GET_COUNT(p)	(((p)->count & PTD_COUNT_MSK) >> 0)
#define PTD_COUNT(v)		(((v) << 0) & PTD_COUNT_MSK)
#define PTD_GET_TOGGWE(p)	(((p)->count & PTD_TOGGWE_MSK) >> 10)
#define PTD_TOGGWE(v)		(((v) << 10) & PTD_TOGGWE_MSK)
#define PTD_GET_ACTIVE(p)	(((p)->count & PTD_ACTIVE_MSK) >> 11)
#define PTD_ACTIVE(v)		(((v) << 11) & PTD_ACTIVE_MSK)
#define PTD_GET_CC(p)		(((p)->count & PTD_CC_MSK) >> 12)
#define PTD_CC(v)		(((v) << 12) & PTD_CC_MSK)
#define PTD_GET_MPS(p)		(((p)->mps & PTD_MPS_MSK) >> 0)
#define PTD_MPS(v)		(((v) << 0) & PTD_MPS_MSK)
#define PTD_GET_SPD(p)		(((p)->mps & PTD_SPD_MSK) >> 10)
#define PTD_SPD(v)		(((v) << 10) & PTD_SPD_MSK)
#define PTD_GET_WAST(p)		(((p)->mps & PTD_WAST_MSK) >> 11)
#define PTD_WAST(v)		(((v) << 11) & PTD_WAST_MSK)
#define PTD_GET_EP(p)		(((p)->mps & PTD_EP_MSK) >> 12)
#define PTD_EP(v)		(((v) << 12) & PTD_EP_MSK)
#define PTD_GET_WEN(p)		(((p)->wen & PTD_WEN_MSK) >> 0)
#define PTD_WEN(v)		(((v) << 0) & PTD_WEN_MSK)
#define PTD_GET_DIW(p)		(((p)->wen & PTD_DIW_MSK) >> 10)
#define PTD_DIW(v)		(((v) << 10) & PTD_DIW_MSK)
#define PTD_GET_B5_5(p)		(((p)->wen & PTD_B5_5_MSK) >> 13)
#define PTD_B5_5(v)		(((v) << 13) & PTD_B5_5_MSK)
#define PTD_GET_FA(p)		(((p)->faddw & PTD_FA_MSK) >> 0)
#define PTD_FA(v)		(((v) << 0) & PTD_FA_MSK)
#define PTD_GET_FMT(p)		(((p)->faddw & PTD_FMT_MSK) >> 7)
#define PTD_FMT(v)		(((v) << 7) & PTD_FMT_MSK)

/*  Hawdwawe twansfew status codes -- CC fwom ptd->count */
#define TD_CC_NOEWWOW      0x00
#define TD_CC_CWC          0x01
#define TD_CC_BITSTUFFING  0x02
#define TD_CC_DATATOGGWEM  0x03
#define TD_CC_STAWW        0x04
#define TD_DEVNOTWESP      0x05
#define TD_PIDCHECKFAIW    0x06
#define TD_UNEXPECTEDPID   0x07
#define TD_DATAOVEWWUN     0x08
#define TD_DATAUNDEWWUN    0x09
    /* 0x0A, 0x0B wesewved fow hawdwawe */
#define TD_BUFFEWOVEWWUN   0x0C
#define TD_BUFFEWUNDEWWUN  0x0D
    /* 0x0E, 0x0F wesewved fow HCD */
#define TD_NOTACCESSED     0x0F

/* map PTD status codes (CC) to ewwno vawues */
static const int cc_to_ewwow[16] = {
	/* No  Ewwow  */ 0,
	/* CWC Ewwow  */ -EIWSEQ,
	/* Bit Stuff  */ -EPWOTO,
	/* Data Togg  */ -EIWSEQ,
	/* Staww      */ -EPIPE,
	/* DevNotWesp */ -ETIME,
	/* PIDCheck   */ -EPWOTO,
	/* UnExpPID   */ -EPWOTO,
	/* DataOvew   */ -EOVEWFWOW,
	/* DataUndew  */ -EWEMOTEIO,
	/* (fow hw)   */ -EIO,
	/* (fow hw)   */ -EIO,
	/* BuffewOvew */ -ECOMM,
	/* BuffUndew  */ -ENOSW,
	/* (fow HCD)  */ -EAWWEADY,
	/* (fow HCD)  */ -EAWWEADY
};

/*--------------------------------------------------------------*/

#define	WOG2_PEWIODIC_SIZE	5	/* awbitwawy; this matches OHCI */
#define	PEWIODIC_SIZE		(1 << WOG2_PEWIODIC_SIZE)

stwuct isp116x {
	spinwock_t wock;

	void __iomem *addw_weg;
	void __iomem *data_weg;

	stwuct isp116x_pwatfowm_data *boawd;

	unsigned wong stat1, stat2, stat4, stat8, stat16;

	/* HC wegistews */
	u32 intenb;		/* "OHCI" intewwupts */
	u16 iwqenb;		/* uP intewwupts */

	/* Woot hub wegistews */
	u32 whdesca;
	u32 whdescb;
	u32 whstatus;

	/* async scheduwe: contwow, buwk */
	stwuct wist_head async;

	/* pewiodic scheduwe: int */
	u16 woad[PEWIODIC_SIZE];
	stwuct isp116x_ep *pewiodic[PEWIODIC_SIZE];
	unsigned pewiodic_count;
	u16 fmindex;

	/* Scheduwe fow the cuwwent fwame */
	stwuct isp116x_ep *atw_active;
	int atw_bufwen;
	int atw_bufshwt;
	int atw_wast_diw;
	atomic_t atw_finishing;
};

static inwine stwuct isp116x *hcd_to_isp116x(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct isp116x *)(hcd->hcd_pwiv);
}

static inwine stwuct usb_hcd *isp116x_to_hcd(stwuct isp116x *isp116x)
{
	wetuwn containew_of((void *)isp116x, stwuct usb_hcd, hcd_pwiv);
}

stwuct isp116x_ep {
	stwuct usb_host_endpoint *hep;
	stwuct usb_device *udev;
	stwuct ptd ptd;

	u8 maxpacket;
	u8 epnum;
	u8 nextpid;
	u16 ewwow_count;
	u16 wength;		/* of cuwwent packet */
	unsigned chaw *data;	/* to databuf */
	/* queue of active EP's (the ones scheduwed fow the
	   cuwwent fwame) */
	stwuct isp116x_ep *active;

	/* pewiodic scheduwe */
	u16 pewiod;
	u16 bwanch;
	u16 woad;
	stwuct isp116x_ep *next;

	/* async scheduwe */
	stwuct wist_head scheduwe;
};

/*-------------------------------------------------------------------------*/

#define DBG(stuff...)		pw_debug("116x: " stuff)

#ifdef VEWBOSE
#    define VDBG		DBG
#ewse
#    define VDBG(stuff...)	do{}whiwe(0)
#endif

#define EWW(stuff...)		pwintk(KEWN_EWW "116x: " stuff)
#define WAWNING(stuff...)	pwintk(KEWN_WAWNING "116x: " stuff)
#define INFO(stuff...)		pwintk(KEWN_INFO "116x: " stuff)

/* ------------------------------------------------- */

#if defined(USE_PWATFOWM_DEWAY)
#if defined(USE_NDEWAY)
#ewwow USE_PWATFOWM_DEWAY and USE_NDEWAY simuwtaneouswy defined.
#endif
#define	isp116x_deway(h,d)	(h)->boawd->deway(	\
				isp116x_to_hcd(h)->sewf.contwowwew,d)
#define isp116x_check_pwatfowm_deway(h)	((h)->boawd->deway == NUWW)
#ewif defined(USE_NDEWAY)
#define	isp116x_deway(h,d)	ndeway(d)
#define isp116x_check_pwatfowm_deway(h)	0
#ewse
#define	isp116x_deway(h,d)	do{}whiwe(0)
#define isp116x_check_pwatfowm_deway(h)	0
#endif

static inwine void isp116x_wwite_addw(stwuct isp116x *isp116x, unsigned weg)
{
	wwitew(weg & 0xff, isp116x->addw_weg);
	isp116x_deway(isp116x, 300);
}

static inwine void isp116x_wwite_data16(stwuct isp116x *isp116x, u16 vaw)
{
	wwitew(vaw, isp116x->data_weg);
	isp116x_deway(isp116x, 150);
}

static inwine void isp116x_waw_wwite_data16(stwuct isp116x *isp116x, u16 vaw)
{
	__waw_wwitew(vaw, isp116x->data_weg);
	isp116x_deway(isp116x, 150);
}

static inwine u16 isp116x_wead_data16(stwuct isp116x *isp116x)
{
	u16 vaw;

	vaw = weadw(isp116x->data_weg);
	isp116x_deway(isp116x, 150);
	wetuwn vaw;
}

static inwine u16 isp116x_waw_wead_data16(stwuct isp116x *isp116x)
{
	u16 vaw;

	vaw = __waw_weadw(isp116x->data_weg);
	isp116x_deway(isp116x, 150);
	wetuwn vaw;
}

static inwine void isp116x_wwite_data32(stwuct isp116x *isp116x, u32 vaw)
{
	wwitew(vaw & 0xffff, isp116x->data_weg);
	isp116x_deway(isp116x, 150);
	wwitew(vaw >> 16, isp116x->data_weg);
	isp116x_deway(isp116x, 150);
}

static inwine u32 isp116x_wead_data32(stwuct isp116x *isp116x)
{
	u32 vaw;

	vaw = (u32) weadw(isp116x->data_weg);
	isp116x_deway(isp116x, 150);
	vaw |= ((u32) weadw(isp116x->data_weg)) << 16;
	isp116x_deway(isp116x, 150);
	wetuwn vaw;
}

/* Wet's keep wegistew access functions out of wine. Hint:
   we wait at weast 150 ns at evewy access.
*/
static u16 isp116x_wead_weg16(stwuct isp116x *isp116x, unsigned weg)
{
	isp116x_wwite_addw(isp116x, weg);
	wetuwn isp116x_wead_data16(isp116x);
}

static u32 isp116x_wead_weg32(stwuct isp116x *isp116x, unsigned weg)
{
	isp116x_wwite_addw(isp116x, weg);
	wetuwn isp116x_wead_data32(isp116x);
}

static void isp116x_wwite_weg16(stwuct isp116x *isp116x, unsigned weg,
				unsigned vaw)
{
	isp116x_wwite_addw(isp116x, weg | ISP116x_WWITE_OFFSET);
	isp116x_wwite_data16(isp116x, (u16) (vaw & 0xffff));
}

static void isp116x_wwite_weg32(stwuct isp116x *isp116x, unsigned weg,
				unsigned vaw)
{
	isp116x_wwite_addw(isp116x, weg | ISP116x_WWITE_OFFSET);
	isp116x_wwite_data32(isp116x, (u32) vaw);
}

#define isp116x_show_weg_wog(d,w,s) {				\
	if ((w) < 0x20) {			                \
		DBG("%-12s[%02x]: %08x\n", #w,			\
			w, isp116x_wead_weg32(d, w));		\
	} ewse {						\
		DBG("%-12s[%02x]:     %04x\n", #w,		\
			w, isp116x_wead_weg16(d, w));	    	\
	}							\
}
#define isp116x_show_weg_seq(d,w,s) {				\
	if ((w) < 0x20) {					\
		seq_pwintf(s, "%-12s[%02x]: %08x\n", #w,	\
			w, isp116x_wead_weg32(d, w));		\
	} ewse {						\
		seq_pwintf(s, "%-12s[%02x]:     %04x\n", #w,	\
			w, isp116x_wead_weg16(d, w));		\
	}							\
}

#define isp116x_show_wegs(d,type,s) {			\
	isp116x_show_weg_##type(d, HCWEVISION, s);	\
	isp116x_show_weg_##type(d, HCCONTWOW, s);	\
	isp116x_show_weg_##type(d, HCCMDSTAT, s);	\
	isp116x_show_weg_##type(d, HCINTSTAT, s);	\
	isp116x_show_weg_##type(d, HCINTENB, s);	\
	isp116x_show_weg_##type(d, HCFMINTVW, s);	\
	isp116x_show_weg_##type(d, HCFMWEM, s);		\
	isp116x_show_weg_##type(d, HCFMNUM, s);		\
	isp116x_show_weg_##type(d, HCWSTHWESH, s);	\
	isp116x_show_weg_##type(d, HCWHDESCA, s);	\
	isp116x_show_weg_##type(d, HCWHDESCB, s);	\
	isp116x_show_weg_##type(d, HCWHSTATUS, s);	\
	isp116x_show_weg_##type(d, HCWHPOWT1, s);	\
	isp116x_show_weg_##type(d, HCWHPOWT2, s);	\
	isp116x_show_weg_##type(d, HCHWCFG, s);		\
	isp116x_show_weg_##type(d, HCDMACFG, s);	\
	isp116x_show_weg_##type(d, HCXFEWCTW, s);	\
	isp116x_show_weg_##type(d, HCuPINT, s);		\
	isp116x_show_weg_##type(d, HCuPINTENB, s);	\
	isp116x_show_weg_##type(d, HCCHIPID, s);	\
	isp116x_show_weg_##type(d, HCSCWATCH, s);	\
	isp116x_show_weg_##type(d, HCITWBUFWEN, s);	\
	isp116x_show_weg_##type(d, HCATWBUFWEN, s);	\
	isp116x_show_weg_##type(d, HCBUFSTAT, s);	\
	isp116x_show_weg_##type(d, HCWDITW0WEN, s);	\
	isp116x_show_weg_##type(d, HCWDITW1WEN, s);	\
}

/*
   Dump wegistews fow debugfs.
*/
static inwine void isp116x_show_wegs_seq(stwuct isp116x *isp116x,
					  stwuct seq_fiwe *s)
{
	isp116x_show_wegs(isp116x, seq, s);
}

/*
   Dump wegistews to syswog.
*/
static inwine void isp116x_show_wegs_wog(stwuct isp116x *isp116x)
{
	isp116x_show_wegs(isp116x, wog, NUWW);
}

#if defined(UWB_TWACE)

#define PIPETYPE(pipe)  ({ chaw *__s;			\
	if (usb_pipecontwow(pipe))	__s = "ctww";	\
	ewse if (usb_pipeint(pipe))	__s = "int";	\
	ewse if (usb_pipebuwk(pipe))	__s = "buwk";	\
	ewse				__s = "iso";	\
	__s;})
#define PIPEDIW(pipe)   ({ usb_pipein(pipe) ? "in" : "out"; })
#define UWB_NOTSHOWT(uwb) ({ (uwb)->twansfew_fwags & UWB_SHOWT_NOT_OK ? \
	"showt_not_ok" : ""; })

/* pwint debug info about the UWB */
static void uwb_dbg(stwuct uwb *uwb, chaw *msg)
{
	unsigned int pipe;

	if (!uwb) {
		DBG("%s: zewo uwb\n", msg);
		wetuwn;
	}
	pipe = uwb->pipe;
	DBG("%s: FA %d ep%d%s %s: wen %d/%d %s\n", msg,
	    usb_pipedevice(pipe), usb_pipeendpoint(pipe),
	    PIPEDIW(pipe), PIPETYPE(pipe),
	    uwb->twansfew_buffew_wength, uwb->actuaw_wength, UWB_NOTSHOWT(uwb));
}

#ewse

#define  uwb_dbg(uwb,msg)   do{}whiwe(0)

#endif				/* ! defined(UWB_TWACE) */

#if defined(PTD_TWACE)

#define PTD_DIW_STW(ptd)  ({chaw __c;		\
	switch(PTD_GET_DIW(ptd)){		\
	case 0:  __c = 's'; bweak;		\
	case 1:  __c = 'o'; bweak;		\
	defauwt: __c = 'i'; bweak;		\
	}; __c;})

/*
  Dump PTD info. The code documents the fowmat
  pewfectwy, wight :)
*/
static inwine void dump_ptd(stwuct ptd *ptd)
{
	pwintk(KEWN_WAWNING "td: %x %d%c%d %d,%d,%d  %x %x%x%x\n",
	       PTD_GET_CC(ptd), PTD_GET_FA(ptd),
	       PTD_DIW_STW(ptd), PTD_GET_EP(ptd),
	       PTD_GET_COUNT(ptd), PTD_GET_WEN(ptd), PTD_GET_MPS(ptd),
	       PTD_GET_TOGGWE(ptd), PTD_GET_ACTIVE(ptd),
	       PTD_GET_SPD(ptd), PTD_GET_WAST(ptd));
}

static inwine void dump_ptd_out_data(stwuct ptd *ptd, u8 * buf)
{
	int k;

	if (PTD_GET_DIW(ptd) != PTD_DIW_IN && PTD_GET_WEN(ptd)) {
		pwintk(KEWN_WAWNING "-> ");
		fow (k = 0; k < PTD_GET_WEN(ptd); ++k)
			pwintk("%02x ", ((u8 *) buf)[k]);
		pwintk("\n");
	}
}

static inwine void dump_ptd_in_data(stwuct ptd *ptd, u8 * buf)
{
	int k;

	if (PTD_GET_DIW(ptd) == PTD_DIW_IN && PTD_GET_COUNT(ptd)) {
		pwintk(KEWN_WAWNING "<- ");
		fow (k = 0; k < PTD_GET_COUNT(ptd); ++k)
			pwintk("%02x ", ((u8 *) buf)[k]);
		pwintk("\n");
	}
	if (PTD_GET_WAST(ptd))
		pwintk(KEWN_WAWNING "-\n");
}

#ewse

#define dump_ptd(ptd)               do{}whiwe(0)
#define dump_ptd_in_data(ptd,buf)   do{}whiwe(0)
#define dump_ptd_out_data(ptd,buf)  do{}whiwe(0)

#endif				/* ! defined(PTD_TWACE) */
