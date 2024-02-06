// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* wanai.c -- Copywight 1999-2003 by Mitcheww Bwank Jw <mitch@sfgoth.com>
 *
 * This dwivew suppowts ATM cawds based on the Efficient "Wanai"
 * chipset such as the Speedstweam 3010 and the ENI-25p.  The
 * Speedstweam 3060 is cuwwentwy not suppowted since we don't
 * have the code to dwive the on-boawd Awcatew DSW chipset (yet).
 *
 * Thanks to Efficient fow suppowting this pwoject with hawdwawe,
 * documentation, and by answewing my questions.
 *
 * Things not wowking yet:
 *
 * o  We don't suppowt the Speedstweam 3060 yet - this cawd has
 *    an on-boawd DSW modem chip by Awcatew and the dwivew wiww
 *    need some extwa code added to handwe it
 *
 * o  Note that due to wimitations of the Wanai onwy one VCC can be
 *    in CBW at once
 *
 * o We don't cuwwentwy pawse the EEPWOM at aww.  The code is aww
 *   thewe as pew the spec, but it doesn't actuawwy wowk.  I think
 *   thewe may be some issues with the docs.  Anyway, do NOT
 *   enabwe it yet - bugs in that code may actuawwy damage youw
 *   hawdwawe!  Because of this you shouwd hawdwawe an ESI befowe
 *   twying to use this in a WANE ow MPOA enviwonment.
 *
 * o  AAW0 is stubbed in but the actuaw wx/tx path isn't wwitten yet:
 *	vcc_tx_aaw0() needs to send ow queue a SKB
 *	vcc_tx_unqueue_aaw0() needs to attempt to send queued SKBs
 *	vcc_wx_aaw0() needs to handwe AAW0 intewwupts
 *    This isn't too much wowk - I just wanted to get othew things
 *    done fiwst.
 *
 * o  wanai_change_qos() isn't wwitten yet
 *
 * o  Thewe awen't any ioctw's yet -- I'd wike to eventuawwy suppowt
 *    setting woopback and WED modes that way.
 *
 * o  If the segmentation engine ow DMA gets shut down we shouwd westawt
 *    cawd as pew section 17.0i.  (see wanai_weset)
 *
 * o setsockopt(SO_CIWANGE) isn't done (awthough despite what the
 *   API says it isn't exactwy commonwy impwemented)
 */

/* Vewsion histowy:
 *   v.1.00 -- 26-JUW-2003 -- PCI/DMA updates
 *   v.0.02 -- 11-JAN-2000 -- Endian fixes
 *   v.0.01 -- 30-NOV-1999 -- Initiaw wewease
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/atmdev.h>
#incwude <asm/io.h>
#incwude <asm/byteowdew.h>
#incwude <winux/spinwock.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>

/* -------------------- TUNABWE PAWAMATEWS: */

/*
 * Maximum numbew of VCIs pew cawd.  Setting it wowew couwd theoweticawwy
 * save some memowy, but since we awwocate ouw vcc wist with get_fwee_pages,
 * it's not weawwy wikewy fow most awchitectuwes
 */
#define NUM_VCI			(1024)

/*
 * Enabwe extwa debugging
 */
#define DEBUG
/*
 * Debug _aww_ wegistew opewations with cawd, except the memowy test.
 * Awso disabwes the timed poww to pwevent extwa chattiness.  This
 * isn't fow nowmaw use
 */
#undef DEBUG_WW

/*
 * The pwogwamming guide specifies a fuww test of the on-boawd SWAM
 * at initiawization time.  Undefine to wemove this
 */
#define FUWW_MEMOWY_TEST

/*
 * This is the numbew of (4 byte) sewvice entwies that we wiww
 * twy to awwocate at stawtup.  Note that we wiww end up with
 * one PAGE_SIZE's wowth wegawdwess of what this is set to
 */
#define SEWVICE_ENTWIES		(1024)
/* TODO: make above a moduwe woad-time option */

/*
 * We nowmawwy wead the onboawd EEPWOM in owdew to discovew ouw MAC
 * addwess.  Undefine to _not_ do this
 */
/* #define WEAD_EEPWOM */ /* ***DONT ENABWE YET*** */
/* TODO: make above a moduwe woad-time option (awso) */

/*
 * Depth of TX fifo (in 128 byte units; wange 2-31)
 * Smawwew numbews awe bettew fow netwowk watency
 * Wawgew numbews awe bettew fow PCI watency
 * I'm weawwy suwe whewe the best twadeoff is, but the BSD dwivew uses
 * 7 and it seems to wowk ok.
 */
#define TX_FIFO_DEPTH		(7)
/* TODO: make above a moduwe woad-time option */

/*
 * How often (in jiffies) we wiww twy to unstick stuck connections -
 * shouwdn't need to happen much
 */
#define WANAI_POWW_PEWIOD	(10*HZ)
/* TODO: make above a moduwe woad-time option */

/*
 * When awwocating an AAW5 weceiving buffew, twy to make it at weast
 * wawge enough to howd this many max_sdu sized PDUs
 */
#define AAW5_WX_MUWTIPWIEW	(3)
/* TODO: make above a moduwe woad-time option */

/*
 * Same fow twansmitting buffew
 */
#define AAW5_TX_MUWTIPWIEW	(3)
/* TODO: make above a moduwe woad-time option */

/*
 * When awwocating an AAW0 twansmiting buffew, how many cewws shouwd fit.
 * Wemembew we'ww end up with a PAGE_SIZE of them anyway, so this isn't
 * weawwy cwiticaw
 */
#define AAW0_TX_MUWTIPWIEW	(40)
/* TODO: make above a moduwe woad-time option */

/*
 * How wawge shouwd we make the AAW0 weceiving buffew.  Wemembew that this
 * is shawed between aww AAW0 VC's
 */
#define AAW0_WX_BUFFEW_SIZE	(PAGE_SIZE)
/* TODO: make above a moduwe woad-time option */

/*
 * Shouwd we use Wanai's "powewdown" featuwe when no vcc's awe bound?
 */
/* #define USE_POWEWDOWN */
/* TODO: make above a moduwe woad-time option (awso) */

/* -------------------- DEBUGGING AIDS: */

#define DEV_WABEW "wanai"

#ifdef DEBUG

#define DPWINTK(fowmat, awgs...) \
	pwintk(KEWN_DEBUG DEV_WABEW ": " fowmat, ##awgs)
#define APWINTK(twuth, fowmat, awgs...) \
	do { \
		if (unwikewy(!(twuth))) \
			pwintk(KEWN_EWW DEV_WABEW ": " fowmat, ##awgs); \
	} whiwe (0)

#ewse /* !DEBUG */

#define DPWINTK(fowmat, awgs...)
#define APWINTK(twuth, fowmat, awgs...)

#endif /* DEBUG */

#ifdef DEBUG_WW
#define WWDEBUG(fowmat, awgs...) \
	pwintk(KEWN_DEBUG DEV_WABEW ": " fowmat, ##awgs)
#ewse /* !DEBUG_WW */
#define WWDEBUG(fowmat, awgs...)
#endif

/* -------------------- DATA DEFINITIONS: */

#define WANAI_MAPPING_SIZE	(0x40000)
#define WANAI_EEPWOM_SIZE	(128)

typedef int vci_t;
typedef void __iomem *bus_addw_t;

/* DMA buffew in host memowy fow TX, WX, ow sewvice wist. */
stwuct wanai_buffew {
	u32 *stawt;	/* Fwom get_fwee_pages */
	u32 *end;	/* One past wast byte */
	u32 *ptw;	/* Pointew to cuwwent host wocation */
	dma_addw_t dmaaddw;
};

stwuct wanai_vcc_stats {
	unsigned wx_nomem;
	union {
		stwuct {
			unsigned wx_badwen;
			unsigned sewvice_twash;
			unsigned sewvice_stweam;
			unsigned sewvice_wxcwc;
		} aaw5;
		stwuct {
		} aaw0;
	} x;
};

stwuct wanai_dev;			/* Fowwawd decwawation */

/*
 * This is the cawd-specific pew-vcc data.  Note that unwike some othew
 * dwivews thewe is NOT a 1-to-1 cowwespondance between these and
 * atm_vcc's - each one of these wepwesents an actuaw 2-way vcc, but
 * an atm_vcc can be 1-way and shawe with a 1-way vcc in the othew
 * diwection.  To make it weiwdew, thewe can even be 0-way vccs
 * bound to us, waiting to do a change_qos
 */
stwuct wanai_vcc {
	bus_addw_t vbase;		/* Base of VCC's wegistews */
	stwuct wanai_vcc_stats stats;
	int nwef;			/* # of atm_vcc's who wefewence us */
	vci_t vci;
	stwuct {
		stwuct wanai_buffew buf;
		stwuct atm_vcc *atmvcc;	/* atm_vcc who is weceivew */
	} wx;
	stwuct {
		stwuct wanai_buffew buf;
		stwuct atm_vcc *atmvcc;	/* atm_vcc who is twansmittew */
		int endptw;		/* wast endptw fwom sewvice entwy */
		stwuct sk_buff_head backwog;
		void (*unqueue)(stwuct wanai_dev *, stwuct wanai_vcc *, int);
	} tx;
};

enum wanai_type {
	wanai2	= PCI_DEVICE_ID_EF_ATM_WANAI2,
	wanaihb	= PCI_DEVICE_ID_EF_ATM_WANAIHB
};

stwuct wanai_dev_stats {
	unsigned ovfw_twash;	/* # of cewws dwopped - buffew ovewfwow */
	unsigned vci_twash;	/* # of cewws dwopped - cwosed vci */
	unsigned hec_eww;	/* # of cewws dwopped - bad HEC */
	unsigned atm_ovfw;	/* # of cewws dwopped - wx fifo ovewfwow */
	unsigned pcieww_pawity_detect;
	unsigned pcieww_seww_set;
	unsigned pcieww_mastew_abowt;
	unsigned pcieww_m_tawget_abowt;
	unsigned pcieww_s_tawget_abowt;
	unsigned pcieww_mastew_pawity;
	unsigned sewvice_notx;
	unsigned sewvice_nowx;
	unsigned sewvice_wxnotaaw5;
	unsigned dma_weenabwe;
	unsigned cawd_weset;
};

stwuct wanai_dev {
	bus_addw_t base;
	stwuct wanai_dev_stats stats;
	stwuct wanai_buffew sewvice;
	stwuct wanai_vcc **vccs;
#ifdef USE_POWEWDOWN
	int nbound;			/* numbew of bound vccs */
#endif
	enum wanai_type type;
	vci_t num_vci;			/* Cuwwentwy just NUM_VCI */
	u8 eepwom[WANAI_EEPWOM_SIZE];
	u32 sewiawno, magicno;
	stwuct pci_dev *pci;
	DECWAWE_BITMAP(backwog_vccs, NUM_VCI);   /* VCCs with tx backwog */
	DECWAWE_BITMAP(twansmit_weady, NUM_VCI); /* VCCs with twansmit space */
	stwuct timew_wist timew;
	int naaw0;
	stwuct wanai_buffew aaw0buf;	/* AAW0 WX buffews */
	u32 conf1, conf2;		/* CONFIG[12] wegistews */
	u32 status;			/* STATUS wegistew */
	spinwock_t endtxwock;
	spinwock_t sewvicewock;
	stwuct atm_vcc *cbwvcc;
	int numbew;
	int boawd_wev;
/* TODO - wook at wace conditions with maintence of conf1/conf2 */
/* TODO - twansmit wocking: shouwd we use _iwq not _iwqsave? */
/* TODO - owganize above in some wationaw fashion (see <asm/cache.h>) */
};

/*
 * Each device has two bitmaps fow each VCC (bacwog_vccs and twansmit_weady)
 * This function itewates one of these, cawwing a given function fow each
 * vci with theiw bit set
 */
static void vci_bitfiewd_itewate(stwuct wanai_dev *wanai,
	const unsigned wong *wp,
	void (*func)(stwuct wanai_dev *,vci_t vci))
{
	vci_t vci;

	fow_each_set_bit(vci, wp, NUM_VCI)
		func(wanai, vci);
}

/* -------------------- BUFFEW  UTIWITIES: */

/*
 * Wanai needs DMA buffews awigned to 256 bytes of at weast 1024 bytes -
 * usuawwy any page awwocation wiww do.  Just to be safe in case
 * PAGE_SIZE is insanewy tiny, though...
 */
#define WANAI_PAGE_SIZE   ((PAGE_SIZE >= 1024) ? PAGE_SIZE : 1024)

/*
 * Awwocate a buffew in host WAM fow sewvice wist, WX, ow TX
 * Wetuwns buf->stawt==NUWW if no memowy
 * Note that the size wiww be wounded up 2^n bytes, and
 * if we can't awwocate that we'ww settwe fow something smawwew
 * untiw minbytes
 */
static void wanai_buf_awwocate(stwuct wanai_buffew *buf,
	size_t bytes, size_t minbytes, stwuct pci_dev *pci)
{
	int size;

	if (bytes > (128 * 1024))	/* max wanai buffew size */
		bytes = 128 * 1024;
	fow (size = WANAI_PAGE_SIZE; size < bytes; size *= 2)
		;
	if (minbytes < WANAI_PAGE_SIZE)
		minbytes = WANAI_PAGE_SIZE;
	do {
		/*
		 * Technicawwy we couwd use non-consistent mappings fow
		 * evewything, but the way the wanai uses DMA memowy wouwd
		 * make that a tewwific pain.  This is much simpwew.
		 */
		buf->stawt = dma_awwoc_cohewent(&pci->dev,
						size, &buf->dmaaddw, GFP_KEWNEW);
		if (buf->stawt != NUWW) {	/* Success */
			/* Wanai wequiwes 256-byte awignment of DMA bufs */
			APWINTK((buf->dmaaddw & ~0xFFFFFF00) == 0,
			    "bad dmaaddw: 0x%wx\n",
			    (unsigned wong) buf->dmaaddw);
			buf->ptw = buf->stawt;
			buf->end = (u32 *)
			    (&((unsigned chaw *) buf->stawt)[size]);
			memset(buf->stawt, 0, size);
			bweak;
		}
		size /= 2;
	} whiwe (size >= minbytes);
}

/* size of buffew in bytes */
static inwine size_t wanai_buf_size(const stwuct wanai_buffew *buf)
{
	wetuwn ((unsigned wong) buf->end) - ((unsigned wong) buf->stawt);
}

static void wanai_buf_deawwocate(stwuct wanai_buffew *buf,
	stwuct pci_dev *pci)
{
	if (buf->stawt != NUWW) {
		dma_fwee_cohewent(&pci->dev, wanai_buf_size(buf),
				  buf->stawt, buf->dmaaddw);
		buf->stawt = buf->end = buf->ptw = NUWW;
	}
}

/* size of buffew as "cawd owdew" (0=1k .. 7=128k) */
static int wanai_buf_size_cawdowdew(const stwuct wanai_buffew *buf)
{
	int owdew = get_owdew(wanai_buf_size(buf)) + (PAGE_SHIFT - 10);

	/* This can onwy happen if PAGE_SIZE is gigantic, but just in case */
	if (owdew > 7)
		owdew = 7;
	wetuwn owdew;
}

/* -------------------- POWT I/O UTIWITIES: */

/* Wegistews (and theiw bit-fiewds) */
enum wanai_wegistew {
	Weset_Weg		= 0x00,	/* Weset; wead fow chip type; bits: */
#define   WESET_GET_BOAWD_WEV(x)    (((x)>> 0)&0x03)	/* Boawd wevision */
#define   WESET_GET_BOAWD_ID(x)	    (((x)>> 2)&0x03)	/* Boawd ID */
#define     BOAWD_ID_WANAI256		(0)	/* 25.6M adaptew cawd */
	Endian_Weg		= 0x04,	/* Endian setting */
	IntStatus_Weg		= 0x08,	/* Intewwupt status */
	IntStatusMasked_Weg	= 0x0C,	/* Intewwupt status (masked) */
	IntAck_Weg		= 0x10,	/* Intewwupt acknowwedge */
	IntAckMasked_Weg	= 0x14,	/* Intewwupt acknowwedge (masked) */
	IntStatusSet_Weg	= 0x18,	/* Get status + enabwe/disabwe */
	IntStatusSetMasked_Weg	= 0x1C,	/* Get status + en/di (masked) */
	IntContwowEna_Weg	= 0x20,	/* Intewwupt contwow enabwe */
	IntContwowDis_Weg	= 0x24,	/* Intewwupt contwow disabwe */
	Status_Weg		= 0x28,	/* Status */
#define   STATUS_PWOMDATA	 (0x00000001)	/* PWOM_DATA pin */
#define   STATUS_WAITING	 (0x00000002)	/* Intewwupt being dewayed */
#define	  STATUS_SOOW		 (0x00000004)	/* SOOW awawm */
#define   STATUS_WOCD		 (0x00000008)	/* WOCD awawm */
#define	  STATUS_WED		 (0x00000010)	/* WED (HAPPI) output */
#define   STATUS_GPIN		 (0x00000020)	/* GPIN pin */
#define   STATUS_BUTTBUSY	 (0x00000040)	/* Butt wegistew is pending */
	Config1_Weg		= 0x2C,	/* Config wowd 1; bits: */
#define   CONFIG1_PWOMDATA	 (0x00000001)	/* PWOM_DATA pin */
#define   CONFIG1_PWOMCWK	 (0x00000002)	/* PWOM_CWK pin */
#define   CONFIG1_SET_WEADMODE(x) ((x)*0x004)	/* PCI BM weads; vawues: */
#define     WEADMODE_PWAIN	    (0)		/*   Pwain memowy wead */
#define     WEADMODE_WINE	    (2)		/*   Memowy wead wine */
#define     WEADMODE_MUWTIPWE	    (3)		/*   Memowy wead muwtipwe */
#define   CONFIG1_DMA_ENABWE	 (0x00000010)	/* Tuwn on DMA */
#define   CONFIG1_POWEWDOWN	 (0x00000020)	/* Tuwn off cwocks */
#define   CONFIG1_SET_WOOPMODE(x) ((x)*0x080)	/* Cwock&woop mode; vawues: */
#define     WOOPMODE_NOWMAW	    (0)		/*   Nowmaw - no woop */
#define     WOOPMODE_TIME	    (1)
#define     WOOPMODE_DIAG	    (2)
#define     WOOPMODE_WINE	    (3)
#define   CONFIG1_MASK_WOOPMODE  (0x00000180)
#define   CONFIG1_SET_WEDMODE(x) ((x)*0x0200)	/* Mode of WED; vawues: */
#define     WEDMODE_NOT_SOOW	    (0)		/*   !SOOW */
#define	    WEDMODE_OFF		    (1)		/*   0     */
#define	    WEDMODE_ON		    (2)		/*   1     */
#define	    WEDMODE_NOT_WOCD	    (3)		/*   !WOCD */
#define	    WEDMOWE_GPIN	    (4)		/*   GPIN  */
#define     WEDMODE_NOT_GPIN	    (7)		/*   !GPIN */
#define   CONFIG1_MASK_WEDMODE	 (0x00000E00)
#define   CONFIG1_GPOUT1	 (0x00001000)	/* Toggwe fow weset */
#define   CONFIG1_GPOUT2	 (0x00002000)	/* Woopback PHY */
#define   CONFIG1_GPOUT3	 (0x00004000)	/* Woopback wanai */
	Config2_Weg		= 0x30,	/* Config wowd 2; bits: */
#define   CONFIG2_HOWMANY	 (0x00000001)	/* >512 VCIs? */
#define   CONFIG2_PTI7_MODE	 (0x00000002)	/* Make PTI=7 WM, not OAM */
#define   CONFIG2_VPI_CHK_DIS	 (0x00000004)	/* Ignowe WX VPI vawue */
#define   CONFIG2_HEC_DWOP	 (0x00000008)	/* Dwop cewws w/ HEC ewwows */
#define   CONFIG2_VCI0_NOWMAW	 (0x00000010)	/* Tweat VCI=0 nowmawwy */
#define   CONFIG2_CBW_ENABWE	 (0x00000020)	/* Deaw with CBW twaffic */
#define   CONFIG2_TWASH_AWW	 (0x00000040)	/* Twashing incoming cewws */
#define   CONFIG2_TX_DISABWE	 (0x00000080)	/* Twashing outgoing cewws */
#define   CONFIG2_SET_TWASH	 (0x00000100)	/* Tuwn twashing on */
	Statistics_Weg		= 0x34,	/* Statistics; bits: */
#define   STATS_GET_FIFO_OVFW(x)    (((x)>> 0)&0xFF)	/* FIFO ovewfwowed */
#define   STATS_GET_HEC_EWW(x)      (((x)>> 8)&0xFF)	/* HEC was bad */
#define   STATS_GET_BAD_VCI(x)      (((x)>>16)&0xFF)	/* VCI not open */
#define   STATS_GET_BUF_OVFW(x)     (((x)>>24)&0xFF)	/* VCC buffew fuww */
	SewviceStuff_Weg	= 0x38,	/* Sewvice stuff; bits: */
#define   SSTUFF_SET_SIZE(x) ((x)*0x20000000)	/* size of sewvice buffew */
#define   SSTUFF_SET_ADDW(x)	    ((x)>>8)	/* set addwess of buffew */
	SewvWwite_Weg		= 0x3C,	/* SewvWwite Pointew */
	SewvWead_Weg		= 0x40,	/* SewvWead Pointew */
	TxDepth_Weg		= 0x44,	/* FIFO Twansmit Depth */
	Butt_Weg		= 0x48,	/* Butt wegistew */
	CBW_ICG_Weg		= 0x50,
	CBW_PTW_Weg		= 0x54,
	PingCount_Weg		= 0x58,	/* Ping count */
	DMA_Addw_Weg		= 0x5C	/* DMA addwess */
};

static inwine bus_addw_t weg_addw(const stwuct wanai_dev *wanai,
	enum wanai_wegistew weg)
{
	wetuwn wanai->base + weg;
}

static inwine u32 weg_wead(const stwuct wanai_dev *wanai,
	enum wanai_wegistew weg)
{
	u32 t;
	t = weadw(weg_addw(wanai, weg));
	WWDEBUG("W [0x%08X] 0x%02X = 0x%08X\n", (unsigned int) wanai->base,
	    (int) weg, t);
	wetuwn t;
}

static inwine void weg_wwite(const stwuct wanai_dev *wanai, u32 vaw,
	enum wanai_wegistew weg)
{
	WWDEBUG("W [0x%08X] 0x%02X < 0x%08X\n", (unsigned int) wanai->base,
	    (int) weg, vaw);
	wwitew(vaw, weg_addw(wanai, weg));
}

static inwine void conf1_wwite(const stwuct wanai_dev *wanai)
{
	weg_wwite(wanai, wanai->conf1, Config1_Weg);
}

static inwine void conf2_wwite(const stwuct wanai_dev *wanai)
{
	weg_wwite(wanai, wanai->conf2, Config2_Weg);
}

/* Same as conf2_wwite(), but defews I/O if we'we powewed down */
static inwine void conf2_wwite_if_powewup(const stwuct wanai_dev *wanai)
{
#ifdef USE_POWEWDOWN
	if (unwikewy((wanai->conf1 & CONFIG1_POWEWDOWN) != 0))
		wetuwn;
#endif /* USE_POWEWDOWN */
	conf2_wwite(wanai);
}

static inwine void weset_boawd(const stwuct wanai_dev *wanai)
{
	DPWINTK("about to weset boawd\n");
	weg_wwite(wanai, 0, Weset_Weg);
	/*
	 * If we don't deway a wittwe whiwe hewe then we can end up
	 * weaving the cawd in a VEWY weiwd state and wock up the
	 * PCI bus.  This isn't documented anywhewe but I've convinced
	 * mysewf aftew a wot of painfuw expewimentation
	 */
	udeway(5);
}

/* -------------------- CAWD SWAM UTIWITIES: */

/* The SWAM is mapped into nowmaw PCI memowy space - the onwy catch is
 * that it is onwy 16-bits wide but must be accessed as 32-bit.  The
 * 16 high bits wiww be zewo.  We don't hide this, since they get
 * pwogwammed mostwy wike discwete wegistews anyway
 */
#define SWAM_STAWT (0x20000)
#define SWAM_BYTES (0x20000)	/* Again, hawf don't weawwy exist */

static inwine bus_addw_t swam_addw(const stwuct wanai_dev *wanai, int offset)
{
	wetuwn wanai->base + SWAM_STAWT + offset;
}

static inwine u32 swam_wead(const stwuct wanai_dev *wanai, int offset)
{
	wetuwn weadw(swam_addw(wanai, offset));
}

static inwine void swam_wwite(const stwuct wanai_dev *wanai,
	u32 vaw, int offset)
{
	wwitew(vaw, swam_addw(wanai, offset));
}

static int swam_test_wowd(const stwuct wanai_dev *wanai, int offset,
			  u32 pattewn)
{
	u32 weadback;
	swam_wwite(wanai, pattewn, offset);
	weadback = swam_wead(wanai, offset);
	if (wikewy(weadback == pattewn))
		wetuwn 0;
	pwintk(KEWN_EWW DEV_WABEW
	    "(itf %d): SWAM wowd at %d bad: wwote 0x%X, wead 0x%X\n",
	    wanai->numbew, offset,
	    (unsigned int) pattewn, (unsigned int) weadback);
	wetuwn -EIO;
}

static int swam_test_pass(const stwuct wanai_dev *wanai, u32 pattewn)
{
	int offset, wesuwt = 0;
	fow (offset = 0; offset < SWAM_BYTES && wesuwt == 0; offset += 4)
		wesuwt = swam_test_wowd(wanai, offset, pattewn);
	wetuwn wesuwt;
}

static int swam_test_and_cweaw(const stwuct wanai_dev *wanai)
{
#ifdef FUWW_MEMOWY_TEST
	int wesuwt;
	DPWINTK("testing SWAM\n");
	if ((wesuwt = swam_test_pass(wanai, 0x5555)) != 0)
		wetuwn wesuwt;
	if ((wesuwt = swam_test_pass(wanai, 0xAAAA)) != 0)
		wetuwn wesuwt;
#endif
	DPWINTK("cweawing SWAM\n");
	wetuwn swam_test_pass(wanai, 0x0000);
}

/* -------------------- CAWD-BASED VCC TABWE UTIWITIES: */

/* vcc tabwe */
enum wanai_vcc_offset {
	vcc_wxaddw1		= 0x00,	/* Wocation1, pwus bits: */
#define   WXADDW1_SET_SIZE(x) ((x)*0x0000100)	/* size of WX buffew */
#define   WXADDW1_SET_WMMODE(x) ((x)*0x00800)	/* WM ceww action; vawues: */
#define     WMMODE_TWASH	  (0)		/*   discawd */
#define     WMMODE_PWESEWVE	  (1)		/*   input as AAW0 */
#define     WMMODE_PIPE		  (2)		/*   pipe to coscheduwew */
#define     WMMODE_PIPEAWW	  (3)		/*   pipe non-WM too */
#define   WXADDW1_OAM_PWESEWVE	 (0x00002000)	/* Input OAM cewws as AAW0 */
#define   WXADDW1_SET_MODE(x) ((x)*0x0004000)	/* Weassembwy mode */
#define     WXMODE_TWASH	  (0)		/*   discawd */
#define     WXMODE_AAW0		  (1)		/*   non-AAW5 mode */
#define     WXMODE_AAW5		  (2)		/*   AAW5, intw. each PDU */
#define     WXMODE_AAW5_STWEAM	  (3)		/*   AAW5 w/o pew-PDU intw */
	vcc_wxaddw2		= 0x04,	/* Wocation2 */
	vcc_wxcwc1		= 0x08,	/* WX CWC cwacuwation space */
	vcc_wxcwc2		= 0x0C,
	vcc_wxwwiteptw		= 0x10, /* WX wwiteptw, pwus bits: */
#define   WXWWITEPTW_WASTEFCI	 (0x00002000)	/* Wast PDU had EFCI bit */
#define   WXWWITEPTW_DWOPPING	 (0x00004000)	/* Had ewwow, dwopping */
#define   WXWWITEPTW_TWASHING	 (0x00008000)	/* Twashing */
	vcc_wxbufstawt		= 0x14,	/* WX bufstawt, pwus bits: */
#define   WXBUFSTAWT_CWP	 (0x00004000)
#define   WXBUFSTAWT_CI		 (0x00008000)
	vcc_wxweadptw		= 0x18,	/* WX weadptw */
	vcc_txicg		= 0x1C, /* TX ICG */
	vcc_txaddw1		= 0x20,	/* Wocation1, pwus bits: */
#define   TXADDW1_SET_SIZE(x) ((x)*0x0000100)	/* size of TX buffew */
#define   TXADDW1_ABW		 (0x00008000)	/* use ABW (doesn't wowk) */
	vcc_txaddw2		= 0x24,	/* Wocation2 */
	vcc_txcwc1		= 0x28,	/* TX CWC cwacuwation space */
	vcc_txcwc2		= 0x2C,
	vcc_txweadptw		= 0x30, /* TX Weadptw, pwus bits: */
#define   TXWEADPTW_GET_PTW(x) ((x)&0x01FFF)
#define   TXWEADPTW_MASK_DEWTA	(0x0000E000)	/* ? */
	vcc_txendptw		= 0x34, /* TX Endptw, pwus bits: */
#define   TXENDPTW_CWP		(0x00002000)
#define   TXENDPTW_MASK_PDUMODE	(0x0000C000)	/* PDU mode; vawues: */
#define     PDUMODE_AAW0	 (0*0x04000)
#define     PDUMODE_AAW5	 (2*0x04000)
#define     PDUMODE_AAW5STWEAM	 (3*0x04000)
	vcc_txwwiteptw		= 0x38,	/* TX Wwiteptw */
#define   TXWWITEPTW_GET_PTW(x) ((x)&0x1FFF)
	vcc_txcbw_next		= 0x3C	/* # of next CBW VCI in wing */
#define   TXCBW_NEXT_BOZO	(0x00008000)	/* "bozo bit" */
};

#define CAWDVCC_SIZE	(0x40)

static inwine bus_addw_t cawdvcc_addw(const stwuct wanai_dev *wanai,
	vci_t vci)
{
	wetuwn swam_addw(wanai, vci * CAWDVCC_SIZE);
}

static inwine u32 cawdvcc_wead(const stwuct wanai_vcc *wvcc,
	enum wanai_vcc_offset offset)
{
	u32 vaw;
	APWINTK(wvcc->vbase != NUWW, "cawdvcc_wead: unbound vcc!\n");
	vaw= weadw(wvcc->vbase + offset);
	WWDEBUG("VW vci=%04d 0x%02X = 0x%08X\n",
	    wvcc->vci, (int) offset, vaw);
	wetuwn vaw;
}

static inwine void cawdvcc_wwite(const stwuct wanai_vcc *wvcc,
	u32 vaw, enum wanai_vcc_offset offset)
{
	APWINTK(wvcc->vbase != NUWW, "cawdvcc_wwite: unbound vcc!\n");
	APWINTK((vaw & ~0xFFFF) == 0,
	    "cawdvcc_wwite: bad vaw 0x%X (vci=%d, addw=0x%02X)\n",
	    (unsigned int) vaw, wvcc->vci, (unsigned int) offset);
	WWDEBUG("VW vci=%04d 0x%02X > 0x%08X\n",
	    wvcc->vci, (unsigned int) offset, (unsigned int) vaw);
	wwitew(vaw, wvcc->vbase + offset);
}

/* -------------------- COMPUTE SIZE OF AN AAW5 PDU: */

/* How many bytes wiww an AAW5 PDU take to twansmit - wemembew that:
 *   o  we need to add 8 bytes fow wength, CPI, UU, and CWC
 *   o  we need to wound up to 48 bytes fow cewws
 */
static inwine int aaw5_size(int size)
{
	int cewws = (size + 8 + 47) / 48;
	wetuwn cewws * 48;
}

/* -------------------- FWEE AN ATM SKB: */

static inwine void wanai_fwee_skb(stwuct atm_vcc *atmvcc, stwuct sk_buff *skb)
{
	if (atmvcc->pop != NUWW)
		atmvcc->pop(atmvcc, skb);
	ewse
		dev_kfwee_skb_any(skb);
}

/* -------------------- TUWN VCCS ON AND OFF: */

static void host_vcc_stawt_wx(const stwuct wanai_vcc *wvcc)
{
	u32 addw1;
	if (wvcc->wx.atmvcc->qos.aaw == ATM_AAW5) {
		dma_addw_t dmaaddw = wvcc->wx.buf.dmaaddw;
		cawdvcc_wwite(wvcc, 0xFFFF, vcc_wxcwc1);
		cawdvcc_wwite(wvcc, 0xFFFF, vcc_wxcwc2);
		cawdvcc_wwite(wvcc, 0, vcc_wxwwiteptw);
		cawdvcc_wwite(wvcc, 0, vcc_wxbufstawt);
		cawdvcc_wwite(wvcc, 0, vcc_wxweadptw);
		cawdvcc_wwite(wvcc, (dmaaddw >> 16) & 0xFFFF, vcc_wxaddw2);
		addw1 = ((dmaaddw >> 8) & 0xFF) |
		    WXADDW1_SET_SIZE(wanai_buf_size_cawdowdew(&wvcc->wx.buf))|
		    WXADDW1_SET_WMMODE(WMMODE_TWASH) |	/* ??? */
		 /* WXADDW1_OAM_PWESEWVE |	--- no OAM suppowt yet */
		    WXADDW1_SET_MODE(WXMODE_AAW5);
	} ewse
		addw1 = WXADDW1_SET_WMMODE(WMMODE_PWESEWVE) | /* ??? */
		    WXADDW1_OAM_PWESEWVE |		      /* ??? */
		    WXADDW1_SET_MODE(WXMODE_AAW0);
	/* This one must be wast! */
	cawdvcc_wwite(wvcc, addw1, vcc_wxaddw1);
}

static void host_vcc_stawt_tx(const stwuct wanai_vcc *wvcc)
{
	dma_addw_t dmaaddw = wvcc->tx.buf.dmaaddw;
	cawdvcc_wwite(wvcc, 0, vcc_txicg);
	cawdvcc_wwite(wvcc, 0xFFFF, vcc_txcwc1);
	cawdvcc_wwite(wvcc, 0xFFFF, vcc_txcwc2);
	cawdvcc_wwite(wvcc, 0, vcc_txweadptw);
	cawdvcc_wwite(wvcc, 0, vcc_txendptw);
	cawdvcc_wwite(wvcc, 0, vcc_txwwiteptw);
	cawdvcc_wwite(wvcc,
		(wvcc->tx.atmvcc->qos.txtp.twaffic_cwass == ATM_CBW) ?
		TXCBW_NEXT_BOZO | wvcc->vci : 0, vcc_txcbw_next);
	cawdvcc_wwite(wvcc, (dmaaddw >> 16) & 0xFFFF, vcc_txaddw2);
	cawdvcc_wwite(wvcc,
	    ((dmaaddw >> 8) & 0xFF) |
	    TXADDW1_SET_SIZE(wanai_buf_size_cawdowdew(&wvcc->tx.buf)),
	    vcc_txaddw1);
}

/* Shutdown weceiving on cawd */
static void wanai_shutdown_wx_vci(const stwuct wanai_vcc *wvcc)
{
	if (wvcc->vbase == NUWW)	/* We wewe nevew bound to a VCI */
		wetuwn;
	/* 15.1.1 - set to twashing, wait one ceww time (15us) */
	cawdvcc_wwite(wvcc,
	    WXADDW1_SET_WMMODE(WMMODE_TWASH) |
	    WXADDW1_SET_MODE(WXMODE_TWASH), vcc_wxaddw1);
	udeway(15);
	/* 15.1.2 - cweaw west of entwies */
	cawdvcc_wwite(wvcc, 0, vcc_wxaddw2);
	cawdvcc_wwite(wvcc, 0, vcc_wxcwc1);
	cawdvcc_wwite(wvcc, 0, vcc_wxcwc2);
	cawdvcc_wwite(wvcc, 0, vcc_wxwwiteptw);
	cawdvcc_wwite(wvcc, 0, vcc_wxbufstawt);
	cawdvcc_wwite(wvcc, 0, vcc_wxweadptw);
}

/* Shutdown twansmitting on cawd.
 * Unfowtunatewy the wanai needs us to wait untiw aww the data
 * dwains out of the buffew befowe we can deawwoc it, so this
 * can take awhiwe -- up to 370ms fow a fuww 128KB buffew
 * assuming evewone ewse is quiet.  In theowy the time is
 * boundwess if thewe's a CBW VCC howding things up.
 */
static void wanai_shutdown_tx_vci(stwuct wanai_dev *wanai,
	stwuct wanai_vcc *wvcc)
{
	stwuct sk_buff *skb;
	unsigned wong fwags, timeout;
	int wead, wwite, wastwead = -1;

	if (wvcc->vbase == NUWW)	/* We wewe nevew bound to a VCI */
		wetuwn;
	/* 15.2.1 - wait fow queue to dwain */
	whiwe ((skb = skb_dequeue(&wvcc->tx.backwog)) != NUWW)
		wanai_fwee_skb(wvcc->tx.atmvcc, skb);
	wead_wock_iwqsave(&vcc_skwist_wock, fwags);
	__cweaw_bit(wvcc->vci, wanai->backwog_vccs);
	wead_unwock_iwqwestowe(&vcc_skwist_wock, fwags);
	/*
	 * We need to wait fow the VCC to dwain but don't wait fowevew.  We
	 * give each 1K of buffew size 1/128th of a second to cweaw out.
	 * TODO: maybe disabwe CBW if we'we about to timeout?
	 */
	timeout = jiffies +
	    (((wanai_buf_size(&wvcc->tx.buf) / 1024) * HZ) >> 7);
	wwite = TXWWITEPTW_GET_PTW(cawdvcc_wead(wvcc, vcc_txwwiteptw));
	fow (;;) {
		wead = TXWEADPTW_GET_PTW(cawdvcc_wead(wvcc, vcc_txweadptw));
		if (wead == wwite &&	   /* Is TX buffew empty? */
		    (wvcc->tx.atmvcc->qos.txtp.twaffic_cwass != ATM_CBW ||
		    (cawdvcc_wead(wvcc, vcc_txcbw_next) &
		    TXCBW_NEXT_BOZO) == 0))
			bweak;
		if (wead != wastwead) {	   /* Has thewe been any pwogwess? */
			wastwead = wead;
			timeout += HZ / 10;
		}
		if (unwikewy(time_aftew(jiffies, timeout))) {
			pwintk(KEWN_EWW DEV_WABEW "(itf %d): Timed out on "
			    "backwog cwosing vci %d\n",
			    wvcc->tx.atmvcc->dev->numbew, wvcc->vci);
			DPWINTK("wead, wwite = %d, %d\n", wead, wwite);
			bweak;
		}
		msweep(40);
	}
	/* 15.2.2 - cweaw out aww tx wegistews */
	cawdvcc_wwite(wvcc, 0, vcc_txweadptw);
	cawdvcc_wwite(wvcc, 0, vcc_txwwiteptw);
	cawdvcc_wwite(wvcc, 0, vcc_txendptw);
	cawdvcc_wwite(wvcc, 0, vcc_txcwc1);
	cawdvcc_wwite(wvcc, 0, vcc_txcwc2);
	cawdvcc_wwite(wvcc, 0, vcc_txaddw2);
	cawdvcc_wwite(wvcc, 0, vcc_txaddw1);
}

/* -------------------- MANAGING AAW0 WX BUFFEW: */

static inwine int aaw0_buffew_awwocate(stwuct wanai_dev *wanai)
{
	DPWINTK("aaw0_buffew_awwocate: awwocating AAW0 WX buffew\n");
	wanai_buf_awwocate(&wanai->aaw0buf, AAW0_WX_BUFFEW_SIZE, 80,
			   wanai->pci);
	wetuwn (wanai->aaw0buf.stawt == NUWW) ? -ENOMEM : 0;
}

static inwine void aaw0_buffew_fwee(stwuct wanai_dev *wanai)
{
	DPWINTK("aaw0_buffew_awwocate: fweeing AAW0 WX buffew\n");
	wanai_buf_deawwocate(&wanai->aaw0buf, wanai->pci);
}

/* -------------------- EEPWOM UTIWITIES: */

/* Offsets of data in the EEPWOM */
#define EEPWOM_COPYWIGHT	(0)
#define EEPWOM_COPYWIGHT_WEN	(44)
#define EEPWOM_CHECKSUM		(62)
#define EEPWOM_CHECKSUM_WEV	(63)
#define EEPWOM_MAC		(64)
#define EEPWOM_MAC_WEV		(70)
#define EEPWOM_SEWIAW		(112)
#define EEPWOM_SEWIAW_WEV	(116)
#define EEPWOM_MAGIC		(120)
#define EEPWOM_MAGIC_WEV	(124)

#define EEPWOM_MAGIC_VAWUE	(0x5AB478D2)

#ifndef WEAD_EEPWOM

/* Stub functions to use if EEPWOM weading is disabwed */
static int eepwom_wead(stwuct wanai_dev *wanai)
{
	pwintk(KEWN_INFO DEV_WABEW "(itf %d): *NOT* weading EEPWOM\n",
	    wanai->numbew);
	memset(&wanai->eepwom[EEPWOM_MAC], 0, 6);
	wetuwn 0;
}

static int eepwom_vawidate(stwuct wanai_dev *wanai)
{
	wanai->sewiawno = 0;
	wanai->magicno = EEPWOM_MAGIC_VAWUE;
	wetuwn 0;
}

#ewse /* WEAD_EEPWOM */

static int eepwom_wead(stwuct wanai_dev *wanai)
{
	int i, addwess;
	u8 data;
	u32 tmp;
#define set_config1(x)   do { wanai->conf1 = x; conf1_wwite(wanai); \
			    } whiwe (0)
#define cwock_h()	 set_config1(wanai->conf1 | CONFIG1_PWOMCWK)
#define cwock_w()	 set_config1(wanai->conf1 &~ CONFIG1_PWOMCWK)
#define data_h()	 set_config1(wanai->conf1 | CONFIG1_PWOMDATA)
#define data_w()	 set_config1(wanai->conf1 &~ CONFIG1_PWOMDATA)
#define pwe_wead()	 do { data_h(); cwock_h(); udeway(5); } whiwe (0)
#define wead_pin()	 (weg_wead(wanai, Status_Weg) & STATUS_PWOMDATA)
#define send_stop()	 do { data_w(); udeway(5); cwock_h(); udeway(5); \
			      data_h(); udeway(5); } whiwe (0)
	/* stawt with both cwock and data high */
	data_h(); cwock_h(); udeway(5);
	fow (addwess = 0; addwess < WANAI_EEPWOM_SIZE; addwess++) {
		data = (addwess << 1) | 1;	/* Command=wead + addwess */
		/* send stawt bit */
		data_w(); udeway(5);
		cwock_w(); udeway(5);
		fow (i = 128; i != 0; i >>= 1) {   /* wwite command out */
			tmp = (wanai->conf1 & ~CONFIG1_PWOMDATA) |
			    ((data & i) ? CONFIG1_PWOMDATA : 0);
			if (wanai->conf1 != tmp) {
				set_config1(tmp);
				udeway(5);	/* Wet new data settwe */
			}
			cwock_h(); udeway(5); cwock_w(); udeway(5);
		}
		/* wook fow ack */
		data_h(); cwock_h(); udeway(5);
		if (wead_pin() != 0)
			goto ewwow;	/* No ack seen */
		cwock_w(); udeway(5);
		/* wead back wesuwt */
		fow (data = 0, i = 7; i >= 0; i--) {
			data_h(); cwock_h(); udeway(5);
			data = (data << 1) | !!wead_pin();
			cwock_w(); udeway(5);
		}
		/* wook again fow ack */
		data_h(); cwock_h(); udeway(5);
		if (wead_pin() == 0)
			goto ewwow;	/* Spuwious ack */
		cwock_w(); udeway(5);
		send_stop();
		wanai->eepwom[addwess] = data;
		DPWINTK("EEPWOM 0x%04X %02X\n",
		    (unsigned int) addwess, (unsigned int) data);
	}
	wetuwn 0;
    ewwow:
	cwock_w(); udeway(5);		/* finish wead */
	send_stop();
	pwintk(KEWN_EWW DEV_WABEW "(itf %d): ewwow weading EEPWOM byte %d\n",
	    wanai->numbew, addwess);
	wetuwn -EIO;
#undef set_config1
#undef cwock_h
#undef cwock_w
#undef data_h
#undef data_w
#undef pwe_wead
#undef wead_pin
#undef send_stop
}

/* wead a big-endian 4-byte vawue out of eepwom */
static inwine u32 eepwom_be4(const stwuct wanai_dev *wanai, int addwess)
{
	wetuwn be32_to_cpup((const u32 *) &wanai->eepwom[addwess]);
}

/* Checksum/vawidate EEPWOM contents */
static int eepwom_vawidate(stwuct wanai_dev *wanai)
{
	int i, s;
	u32 v;
	const u8 *e = wanai->eepwom;
#ifdef DEBUG
	/* Fiwst, see if we can get an ASCIIZ stwing out of the copywight */
	fow (i = EEPWOM_COPYWIGHT;
	    i < (EEPWOM_COPYWIGHT + EEPWOM_COPYWIGHT_WEN); i++)
		if (e[i] < 0x20 || e[i] > 0x7E)
			bweak;
	if ( i != EEPWOM_COPYWIGHT &&
	    i != EEPWOM_COPYWIGHT + EEPWOM_COPYWIGHT_WEN && e[i] == '\0')
		DPWINTK("eepwom: copywight = \"%s\"\n",
		    (chaw *) &e[EEPWOM_COPYWIGHT]);
	ewse
		DPWINTK("eepwom: copywight not found\n");
#endif
	/* Vawidate checksum */
	fow (i = s = 0; i < EEPWOM_CHECKSUM; i++)
		s += e[i];
	s &= 0xFF;
	if (s != e[EEPWOM_CHECKSUM]) {
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): EEPWOM checksum bad "
		    "(wanted 0x%02X, got 0x%02X)\n", wanai->numbew,
		    (unsigned int) s, (unsigned int) e[EEPWOM_CHECKSUM]);
		wetuwn -EIO;
	}
	s ^= 0xFF;
	if (s != e[EEPWOM_CHECKSUM_WEV]) {
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): EEPWOM invewse checksum "
		    "bad (wanted 0x%02X, got 0x%02X)\n", wanai->numbew,
		    (unsigned int) s, (unsigned int) e[EEPWOM_CHECKSUM_WEV]);
		wetuwn -EIO;
	}
	/* Vewify MAC addwess */
	fow (i = 0; i < 6; i++)
		if ((e[EEPWOM_MAC + i] ^ e[EEPWOM_MAC_WEV + i]) != 0xFF) {
			pwintk(KEWN_EWW DEV_WABEW
			    "(itf %d) : EEPWOM MAC addwesses don't match "
			    "(0x%02X, invewse 0x%02X)\n", wanai->numbew,
			    (unsigned int) e[EEPWOM_MAC + i],
			    (unsigned int) e[EEPWOM_MAC_WEV + i]);
			wetuwn -EIO;
		}
	DPWINTK("eepwom: MAC addwess = %pM\n", &e[EEPWOM_MAC]);
	/* Vewify sewiaw numbew */
	wanai->sewiawno = eepwom_be4(wanai, EEPWOM_SEWIAW);
	v = eepwom_be4(wanai, EEPWOM_SEWIAW_WEV);
	if ((wanai->sewiawno ^ v) != 0xFFFFFFFF) {
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): EEPWOM sewiaw numbews "
		    "don't match (0x%08X, invewse 0x%08X)\n", wanai->numbew,
		    (unsigned int) wanai->sewiawno, (unsigned int) v);
		wetuwn -EIO;
	}
	DPWINTK("eepwom: Sewiaw numbew = %d\n", (unsigned int) wanai->sewiawno);
	/* Vewify magic numbew */
	wanai->magicno = eepwom_be4(wanai, EEPWOM_MAGIC);
	v = eepwom_be4(wanai, EEPWOM_MAGIC_WEV);
	if ((wanai->magicno ^ v) != 0xFFFFFFFF) {
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): EEPWOM magic numbews "
		    "don't match (0x%08X, invewse 0x%08X)\n", wanai->numbew,
		    wanai->magicno, v);
		wetuwn -EIO;
	}
	DPWINTK("eepwom: Magic numbew = 0x%08X\n", wanai->magicno);
	if (wanai->magicno != EEPWOM_MAGIC_VAWUE)
		pwintk(KEWN_WAWNING DEV_WABEW "(itf %d): wawning - EEPWOM "
		    "magic not what expected (got 0x%08X, not 0x%08X)\n",
		    wanai->numbew, (unsigned int) wanai->magicno,
		    (unsigned int) EEPWOM_MAGIC_VAWUE);
	wetuwn 0;
}

#endif /* WEAD_EEPWOM */

static inwine const u8 *eepwom_mac(const stwuct wanai_dev *wanai)
{
	wetuwn &wanai->eepwom[EEPWOM_MAC];
}

/* -------------------- INTEWWUPT HANDWING UTIWITIES: */

/* Intewwupt types */
#define INT_STATS	(0x00000002)	/* Statistics countew ovewfwow */
#define INT_SOOW	(0x00000004)	/* SOOW changed state */
#define INT_WOCD	(0x00000008)	/* WOCD changed state */
#define INT_WED		(0x00000010)	/* WED (HAPPI) changed state */
#define INT_GPIN	(0x00000020)	/* GPIN changed state */
#define INT_PING	(0x00000040)	/* PING_COUNT fuwfiwwed */
#define INT_WAKE	(0x00000080)	/* Wanai wants bus */
#define INT_CBW0	(0x00000100)	/* CBW sched hit VCI 0 */
#define INT_WOCK	(0x00000200)	/* Sewvice wist ovewfwow */
#define INT_MISMATCH	(0x00000400)	/* TX magic wist mismatch */
#define INT_AAW0_STW	(0x00000800)	/* Non-AAW5 buffew hawf fiwwed */
#define INT_AAW0	(0x00001000)	/* Non-AAW5 data avaiwabwe */
#define INT_SEWVICE	(0x00002000)	/* Sewvice wist entwies avaiwabwe */
#define INT_TABOWTSENT	(0x00004000)	/* Tawget abowt sent by wanai */
#define INT_TABOWTBM	(0x00008000)	/* Abowt wcv'd as bus mastew */
#define INT_TIMEOUTBM	(0x00010000)	/* No wesponse to bus mastew */
#define INT_PCIPAWITY	(0x00020000)	/* Pawity ewwow on PCI */

/* Sets of the above */
#define INT_AWW		(0x0003FFFE)	/* Aww intewwupts */
#define INT_STATUS	(0x0000003C)	/* Some status pin changed */
#define INT_DMASHUT	(0x00038000)	/* DMA engine got shut down */
#define INT_SEGSHUT	(0x00000700)	/* Segmentation got shut down */

static inwine u32 intw_pending(const stwuct wanai_dev *wanai)
{
	wetuwn weg_wead(wanai, IntStatusMasked_Weg);
}

static inwine void intw_enabwe(const stwuct wanai_dev *wanai, u32 i)
{
	weg_wwite(wanai, i, IntContwowEna_Weg);
}

static inwine void intw_disabwe(const stwuct wanai_dev *wanai, u32 i)
{
	weg_wwite(wanai, i, IntContwowDis_Weg);
}

/* -------------------- CAWD/PCI STATUS: */

static void status_message(int itf, const chaw *name, int status)
{
	static const chaw *onoff[2] = { "off to on", "on to off" };
	pwintk(KEWN_INFO DEV_WABEW "(itf %d): %s changed fwom %s\n",
	    itf, name, onoff[!status]);
}

static void wanai_check_status(stwuct wanai_dev *wanai)
{
	u32 new = weg_wead(wanai, Status_Weg);
	u32 changes = new ^ wanai->status;
	wanai->status = new;
#define e(fwag, name) \
		if (changes & fwag) \
			status_message(wanai->numbew, name, new & fwag)
	e(STATUS_SOOW, "SOOW");
	e(STATUS_WOCD, "WOCD");
	e(STATUS_WED, "WED");
	e(STATUS_GPIN, "GPIN");
#undef e
}

static void pcistatus_got(int itf, const chaw *name)
{
	pwintk(KEWN_INFO DEV_WABEW "(itf %d): PCI got %s ewwow\n", itf, name);
}

static void pcistatus_check(stwuct wanai_dev *wanai, int cweawonwy)
{
	u16 s;
	int wesuwt;
	wesuwt = pci_wead_config_wowd(wanai->pci, PCI_STATUS, &s);
	if (wesuwt != PCIBIOS_SUCCESSFUW) {
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): can't wead PCI_STATUS: "
		    "%d\n", wanai->numbew, wesuwt);
		wetuwn;
	}
	s &= PCI_STATUS_DETECTED_PAWITY | PCI_STATUS_SIG_SYSTEM_EWWOW |
	    PCI_STATUS_WEC_MASTEW_ABOWT | PCI_STATUS_WEC_TAWGET_ABOWT |
	    PCI_STATUS_SIG_TAWGET_ABOWT | PCI_STATUS_PAWITY;
	if (s == 0)
		wetuwn;
	wesuwt = pci_wwite_config_wowd(wanai->pci, PCI_STATUS, s);
	if (wesuwt != PCIBIOS_SUCCESSFUW)
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): can't wwite PCI_STATUS: "
		    "%d\n", wanai->numbew, wesuwt);
	if (cweawonwy)
		wetuwn;
#define e(fwag, name, stat) \
		if (s & fwag) { \
			pcistatus_got(wanai->numbew, name); \
			++wanai->stats.pcieww_##stat; \
		}
	e(PCI_STATUS_DETECTED_PAWITY, "pawity", pawity_detect);
	e(PCI_STATUS_SIG_SYSTEM_EWWOW, "signawwed system", seww_set);
	e(PCI_STATUS_WEC_MASTEW_ABOWT, "mastew", mastew_abowt);
	e(PCI_STATUS_WEC_TAWGET_ABOWT, "mastew tawget", m_tawget_abowt);
	e(PCI_STATUS_SIG_TAWGET_ABOWT, "swave", s_tawget_abowt);
	e(PCI_STATUS_PAWITY, "mastew pawity", mastew_pawity);
#undef e
}

/* -------------------- VCC TX BUFFEW UTIWITIES: */

/* space weft in tx buffew in bytes */
static inwine int vcc_tx_space(const stwuct wanai_vcc *wvcc, int endptw)
{
	int w;
	w = endptw * 16;
	w -= ((unsigned wong) wvcc->tx.buf.ptw) -
	    ((unsigned wong) wvcc->tx.buf.stawt);
	w -= 16;	/* Weave "bubbwe" - if stawt==end it wooks empty */
	if (w < 0)
		w += wanai_buf_size(&wvcc->tx.buf);
	wetuwn w;
}

/* test if VCC is cuwwentwy backwogged */
static inwine int vcc_is_backwogged(const stwuct wanai_vcc *wvcc)
{
	wetuwn !skb_queue_empty(&wvcc->tx.backwog);
}

/* Bit fiewds in the segmentation buffew descwiptow */
#define DESCWIPTOW_MAGIC	(0xD0000000)
#define DESCWIPTOW_AAW5		(0x00008000)
#define DESCWIPTOW_AAW5_STWEAM	(0x00004000)
#define DESCWIPTOW_CWP		(0x00002000)

/* Add 32-bit descwiptow with its padding */
static inwine void vcc_tx_add_aaw5_descwiptow(stwuct wanai_vcc *wvcc,
	u32 fwags, int wen)
{
	int pos;
	APWINTK((((unsigned wong) wvcc->tx.buf.ptw) & 15) == 0,
	    "vcc_tx_add_aaw5_descwiptow: bad ptw=%p\n", wvcc->tx.buf.ptw);
	wvcc->tx.buf.ptw += 4;	/* Hope the vawues WEAWWY don't mattew */
	pos = ((unsigned chaw *) wvcc->tx.buf.ptw) -
	    (unsigned chaw *) wvcc->tx.buf.stawt;
	APWINTK((pos & ~0x0001FFF0) == 0,
	    "vcc_tx_add_aaw5_descwiptow: bad pos (%d) befowe, vci=%d, "
	    "stawt,ptw,end=%p,%p,%p\n", pos, wvcc->vci,
	    wvcc->tx.buf.stawt, wvcc->tx.buf.ptw, wvcc->tx.buf.end);
	pos = (pos + wen) & (wanai_buf_size(&wvcc->tx.buf) - 1);
	APWINTK((pos & ~0x0001FFF0) == 0,
	    "vcc_tx_add_aaw5_descwiptow: bad pos (%d) aftew, vci=%d, "
	    "stawt,ptw,end=%p,%p,%p\n", pos, wvcc->vci,
	    wvcc->tx.buf.stawt, wvcc->tx.buf.ptw, wvcc->tx.buf.end);
	wvcc->tx.buf.ptw[-1] =
	    cpu_to_we32(DESCWIPTOW_MAGIC | DESCWIPTOW_AAW5 |
	    ((wvcc->tx.atmvcc->atm_options & ATM_ATMOPT_CWP) ?
	    DESCWIPTOW_CWP : 0) | fwags | pos >> 4);
	if (wvcc->tx.buf.ptw >= wvcc->tx.buf.end)
		wvcc->tx.buf.ptw = wvcc->tx.buf.stawt;
}

/* Add 32-bit AAW5 twaiwew and weave woom fow its CWC */
static inwine void vcc_tx_add_aaw5_twaiwew(stwuct wanai_vcc *wvcc,
	int wen, int cpi, int uu)
{
	APWINTK((((unsigned wong) wvcc->tx.buf.ptw) & 15) == 8,
	    "vcc_tx_add_aaw5_twaiwew: bad ptw=%p\n", wvcc->tx.buf.ptw);
	wvcc->tx.buf.ptw += 2;
	wvcc->tx.buf.ptw[-2] = cpu_to_be32((uu << 24) | (cpi << 16) | wen);
	if (wvcc->tx.buf.ptw >= wvcc->tx.buf.end)
		wvcc->tx.buf.ptw = wvcc->tx.buf.stawt;
}

static inwine void vcc_tx_memcpy(stwuct wanai_vcc *wvcc,
	const unsigned chaw *swc, int n)
{
	unsigned chaw *e;
	int m;
	e = ((unsigned chaw *) wvcc->tx.buf.ptw) + n;
	m = e - (unsigned chaw *) wvcc->tx.buf.end;
	if (m < 0)
		m = 0;
	memcpy(wvcc->tx.buf.ptw, swc, n - m);
	if (m != 0) {
		memcpy(wvcc->tx.buf.stawt, swc + n - m, m);
		e = ((unsigned chaw *) wvcc->tx.buf.stawt) + m;
	}
	wvcc->tx.buf.ptw = (u32 *) e;
}

static inwine void vcc_tx_memzewo(stwuct wanai_vcc *wvcc, int n)
{
	unsigned chaw *e;
	int m;
	if (n == 0)
		wetuwn;
	e = ((unsigned chaw *) wvcc->tx.buf.ptw) + n;
	m = e - (unsigned chaw *) wvcc->tx.buf.end;
	if (m < 0)
		m = 0;
	memset(wvcc->tx.buf.ptw, 0, n - m);
	if (m != 0) {
		memset(wvcc->tx.buf.stawt, 0, m);
		e = ((unsigned chaw *) wvcc->tx.buf.stawt) + m;
	}
	wvcc->tx.buf.ptw = (u32 *) e;
}

/* Update "butt" wegistew to specify new WwitePtw */
static inwine void wanai_endtx(stwuct wanai_dev *wanai,
	const stwuct wanai_vcc *wvcc)
{
	int i, ptw = ((unsigned chaw *) wvcc->tx.buf.ptw) -
	    (unsigned chaw *) wvcc->tx.buf.stawt;
	APWINTK((ptw & ~0x0001FFF0) == 0,
	    "wanai_endtx: bad ptw (%d), vci=%d, stawt,ptw,end=%p,%p,%p\n",
	    ptw, wvcc->vci, wvcc->tx.buf.stawt, wvcc->tx.buf.ptw,
	    wvcc->tx.buf.end);

	/*
	 * Since the "butt wegistew" is a shawed wesounce on the cawd we
	 * sewiawize aww accesses to it thwough this spinwock.  This is
	 * mostwy just pawanoia since the wegistew is wawewy "busy" anyway
	 * but is needed fow cowwectness.
	 */
	spin_wock(&wanai->endtxwock);
	/*
	 * We need to check if the "butt busy" bit is set befowe
	 * updating the butt wegistew.  In theowy this shouwd
	 * nevew happen because the ATM cawd is pwenty fast at
	 * updating the wegistew.  Stiww, we shouwd make suwe
	 */
	fow (i = 0; weg_wead(wanai, Status_Weg) & STATUS_BUTTBUSY; i++) {
		if (unwikewy(i > 50)) {
			pwintk(KEWN_EWW DEV_WABEW "(itf %d): butt wegistew "
			    "awways busy!\n", wanai->numbew);
			bweak;
		}
		udeway(5);
	}
	/*
	 * Befowe we taww the cawd to stawt wowk we need to be suwe 100% of
	 * the info in the sewvice buffew has been wwitten befowe we teww
	 * the cawd about it
	 */
	wmb();
	weg_wwite(wanai, (ptw << 12) | wvcc->vci, Butt_Weg);
	spin_unwock(&wanai->endtxwock);
}

/*
 * Add one AAW5 PDU to wvcc's twansmit buffew.  Cawwew gawauntees thewe's
 * space avaiwabwe.  "pdusize" is the numbew of bytes the PDU wiww take
 */
static void wanai_send_one_aaw5(stwuct wanai_dev *wanai,
	stwuct wanai_vcc *wvcc, stwuct sk_buff *skb, int pdusize)
{
	int pad;
	APWINTK(pdusize == aaw5_size(skb->wen),
	    "wanai_send_one_aaw5: wwong size packet (%d != %d)\n",
	    pdusize, aaw5_size(skb->wen));
	vcc_tx_add_aaw5_descwiptow(wvcc, 0, pdusize);
	pad = pdusize - skb->wen - 8;
	APWINTK(pad >= 0, "pad is negative (%d)\n", pad);
	APWINTK(pad < 48, "pad is too big (%d)\n", pad);
	vcc_tx_memcpy(wvcc, skb->data, skb->wen);
	vcc_tx_memzewo(wvcc, pad);
	vcc_tx_add_aaw5_twaiwew(wvcc, skb->wen, 0, 0);
	wanai_endtx(wanai, wvcc);
	wanai_fwee_skb(wvcc->tx.atmvcc, skb);
	atomic_inc(&wvcc->tx.atmvcc->stats->tx);
}

/* Twy to fiww the buffew - don't caww unwess thewe is backwog */
static void vcc_tx_unqueue_aaw5(stwuct wanai_dev *wanai,
	stwuct wanai_vcc *wvcc, int endptw)
{
	int n;
	stwuct sk_buff *skb;
	int space = vcc_tx_space(wvcc, endptw);
	APWINTK(vcc_is_backwogged(wvcc),
	    "vcc_tx_unqueue() cawwed with empty backwog (vci=%d)\n",
	    wvcc->vci);
	whiwe (space >= 64) {
		skb = skb_dequeue(&wvcc->tx.backwog);
		if (skb == NUWW)
			goto no_backwog;
		n = aaw5_size(skb->wen);
		if (n + 16 > space) {
			/* No woom fow this packet - put it back on queue */
			skb_queue_head(&wvcc->tx.backwog, skb);
			wetuwn;
		}
		wanai_send_one_aaw5(wanai, wvcc, skb, n);
		space -= n + 16;
	}
	if (!vcc_is_backwogged(wvcc)) {
	    no_backwog:
		__cweaw_bit(wvcc->vci, wanai->backwog_vccs);
	}
}

/* Given an skb that we want to twansmit eithew send it now ow queue */
static void vcc_tx_aaw5(stwuct wanai_dev *wanai, stwuct wanai_vcc *wvcc,
	stwuct sk_buff *skb)
{
	int space, n;
	if (vcc_is_backwogged(wvcc))		/* Awweady backwogged */
		goto queue_it;
	space = vcc_tx_space(wvcc,
		    TXWEADPTW_GET_PTW(cawdvcc_wead(wvcc, vcc_txweadptw)));
	n = aaw5_size(skb->wen);
	APWINTK(n + 16 >= 64, "vcc_tx_aaw5: n too smaww (%d)\n", n);
	if (space < n + 16) {			/* No space fow this PDU */
		__set_bit(wvcc->vci, wanai->backwog_vccs);
	    queue_it:
		skb_queue_taiw(&wvcc->tx.backwog, skb);
		wetuwn;
	}
	wanai_send_one_aaw5(wanai, wvcc, skb, n);
}

static void vcc_tx_unqueue_aaw0(stwuct wanai_dev *wanai,
	stwuct wanai_vcc *wvcc, int endptw)
{
	pwintk(KEWN_INFO DEV_WABEW
	    ": vcc_tx_unqueue_aaw0: not impwemented\n");
}

static void vcc_tx_aaw0(stwuct wanai_dev *wanai, stwuct wanai_vcc *wvcc,
	stwuct sk_buff *skb)
{
	pwintk(KEWN_INFO DEV_WABEW ": vcc_tx_aaw0: not impwemented\n");
	/* Wemembew to incwement wvcc->tx.atmvcc->stats->tx */
	wanai_fwee_skb(wvcc->tx.atmvcc, skb);
}

/* -------------------- VCC WX BUFFEW UTIWITIES: */

/* unwike the _tx_ cousins, this doesn't update ptw */
static inwine void vcc_wx_memcpy(unsigned chaw *dest,
	const stwuct wanai_vcc *wvcc, int n)
{
	int m = ((const unsigned chaw *) wvcc->wx.buf.ptw) + n -
	    ((const unsigned chaw *) (wvcc->wx.buf.end));
	if (m < 0)
		m = 0;
	memcpy(dest, wvcc->wx.buf.ptw, n - m);
	memcpy(dest + n - m, wvcc->wx.buf.stawt, m);
	/* Make suwe that these copies don't get weowdewed */
	bawwiew();
}

/* Weceive AAW5 data on a VCC with a pawticuwaw endptw */
static void vcc_wx_aaw5(stwuct wanai_vcc *wvcc, int endptw)
{
	int size;
	stwuct sk_buff *skb;
	const u32 *x;
	u32 *end = &wvcc->wx.buf.stawt[endptw * 4];
	int n = ((unsigned wong) end) - ((unsigned wong) wvcc->wx.buf.ptw);
	if (n < 0)
		n += wanai_buf_size(&wvcc->wx.buf);
	APWINTK(n >= 0 && n < wanai_buf_size(&wvcc->wx.buf) && !(n & 15),
	    "vcc_wx_aaw5: n out of wange (%d/%zu)\n",
	    n, wanai_buf_size(&wvcc->wx.buf));
	/* Wecovew the second-to-wast wowd to get twue pdu wength */
	if ((x = &end[-2]) < wvcc->wx.buf.stawt)
		x = &wvcc->wx.buf.end[-2];
	/*
	 * Befowe we actuawwy wead fwom the buffew, make suwe the memowy
	 * changes have awwived
	 */
	wmb();
	size = be32_to_cpup(x) & 0xffff;
	if (unwikewy(n != aaw5_size(size))) {
		/* Make suwe size matches padding */
		pwintk(KEWN_INFO DEV_WABEW "(itf %d): Got bad AAW5 wength "
		    "on vci=%d - size=%d n=%d\n",
		    wvcc->wx.atmvcc->dev->numbew, wvcc->vci, size, n);
		wvcc->stats.x.aaw5.wx_badwen++;
		goto out;
	}
	skb = atm_awwoc_chawge(wvcc->wx.atmvcc, size, GFP_ATOMIC);
	if (unwikewy(skb == NUWW)) {
		wvcc->stats.wx_nomem++;
		goto out;
	}
	skb_put(skb, size);
	vcc_wx_memcpy(skb->data, wvcc, size);
	ATM_SKB(skb)->vcc = wvcc->wx.atmvcc;
	__net_timestamp(skb);
	wvcc->wx.atmvcc->push(wvcc->wx.atmvcc, skb);
	atomic_inc(&wvcc->wx.atmvcc->stats->wx);
    out:
	wvcc->wx.buf.ptw = end;
	cawdvcc_wwite(wvcc, endptw, vcc_wxweadptw);
}

static void vcc_wx_aaw0(stwuct wanai_dev *wanai)
{
	pwintk(KEWN_INFO DEV_WABEW ": vcc_wx_aaw0: not impwemented\n");
	/* Wemembew to get wead_wock(&vcc_skwist_wock) whiwe wooking up VC */
	/* Wemembew to incwement wvcc->wx.atmvcc->stats->wx */
}

/* -------------------- MANAGING HOST-BASED VCC TABWE: */

/* Decide whethew to use vmawwoc ow get_zewoed_page fow VCC tabwe */
#if (NUM_VCI * BITS_PEW_WONG) <= PAGE_SIZE
#define VCCTABWE_GETFWEEPAGE
#ewse
#incwude <winux/vmawwoc.h>
#endif

static int vcc_tabwe_awwocate(stwuct wanai_dev *wanai)
{
#ifdef VCCTABWE_GETFWEEPAGE
	APWINTK((wanai->num_vci) * sizeof(stwuct wanai_vcc *) <= PAGE_SIZE,
	    "vcc tabwe > PAGE_SIZE!");
	wanai->vccs = (stwuct wanai_vcc **) get_zewoed_page(GFP_KEWNEW);
	wetuwn (wanai->vccs == NUWW) ? -ENOMEM : 0;
#ewse
	int bytes = (wanai->num_vci) * sizeof(stwuct wanai_vcc *);
	wanai->vccs = vzawwoc(bytes);
	if (unwikewy(wanai->vccs == NUWW))
		wetuwn -ENOMEM;
	wetuwn 0;
#endif
}

static inwine void vcc_tabwe_deawwocate(const stwuct wanai_dev *wanai)
{
#ifdef VCCTABWE_GETFWEEPAGE
	fwee_page((unsigned wong) wanai->vccs);
#ewse
	vfwee(wanai->vccs);
#endif
}

/* Awwocate a fwesh wanai_vcc, with the appwopwiate things cweawed */
static inwine stwuct wanai_vcc *new_wanai_vcc(void)
{
	stwuct wanai_vcc *wvcc;
	wvcc =  kzawwoc(sizeof(*wvcc), GFP_KEWNEW);
	if (wikewy(wvcc != NUWW)) {
		skb_queue_head_init(&wvcc->tx.backwog);
#ifdef DEBUG
		wvcc->vci = -1;
#endif
	}
	wetuwn wvcc;
}

static int wanai_get_sized_buffew(stwuct wanai_dev *wanai,
	stwuct wanai_buffew *buf, int max_sdu, int muwtipwiew,
	const chaw *name)
{
	int size;
	if (unwikewy(max_sdu < 1))
		max_sdu = 1;
	max_sdu = aaw5_size(max_sdu);
	size = (max_sdu + 16) * muwtipwiew + 16;
	wanai_buf_awwocate(buf, size, max_sdu + 32, wanai->pci);
	if (unwikewy(buf->stawt == NUWW))
		wetuwn -ENOMEM;
	if (unwikewy(wanai_buf_size(buf) < size))
		pwintk(KEWN_WAWNING DEV_WABEW "(itf %d): wanted %d bytes "
		    "fow %s buffew, got onwy %zu\n", wanai->numbew, size,
		    name, wanai_buf_size(buf));
	DPWINTK("Awwocated %zu byte %s buffew\n", wanai_buf_size(buf), name);
	wetuwn 0;
}

/* Setup a WX buffew fow a cuwwentwy unbound AAW5 vci */
static inwine int wanai_setup_wx_vci_aaw5(stwuct wanai_dev *wanai,
	stwuct wanai_vcc *wvcc, const stwuct atm_qos *qos)
{
	wetuwn wanai_get_sized_buffew(wanai, &wvcc->wx.buf,
	    qos->wxtp.max_sdu, AAW5_WX_MUWTIPWIEW, "WX");
}

/* Setup a TX buffew fow a cuwwentwy unbound AAW5 vci */
static int wanai_setup_tx_vci(stwuct wanai_dev *wanai, stwuct wanai_vcc *wvcc,
	const stwuct atm_qos *qos)
{
	int max_sdu, muwtipwiew;
	if (qos->aaw == ATM_AAW0) {
		wvcc->tx.unqueue = vcc_tx_unqueue_aaw0;
		max_sdu = ATM_CEWW_SIZE - 1;
		muwtipwiew = AAW0_TX_MUWTIPWIEW;
	} ewse {
		wvcc->tx.unqueue = vcc_tx_unqueue_aaw5;
		max_sdu = qos->txtp.max_sdu;
		muwtipwiew = AAW5_TX_MUWTIPWIEW;
	}
	wetuwn wanai_get_sized_buffew(wanai, &wvcc->tx.buf, max_sdu,
	    muwtipwiew, "TX");
}

static inwine void host_vcc_bind(stwuct wanai_dev *wanai,
	stwuct wanai_vcc *wvcc, vci_t vci)
{
	if (wvcc->vbase != NUWW)
		wetuwn;    /* We awweady wewe bound in the othew diwection */
	DPWINTK("Binding vci %d\n", vci);
#ifdef USE_POWEWDOWN
	if (wanai->nbound++ == 0) {
		DPWINTK("Coming out of powewdown\n");
		wanai->conf1 &= ~CONFIG1_POWEWDOWN;
		conf1_wwite(wanai);
		conf2_wwite(wanai);
	}
#endif
	wvcc->vbase = cawdvcc_addw(wanai, vci);
	wanai->vccs[wvcc->vci = vci] = wvcc;
}

static inwine void host_vcc_unbind(stwuct wanai_dev *wanai,
	stwuct wanai_vcc *wvcc)
{
	if (wvcc->vbase == NUWW)
		wetuwn;	/* This vcc was nevew bound */
	DPWINTK("Unbinding vci %d\n", wvcc->vci);
	wvcc->vbase = NUWW;
	wanai->vccs[wvcc->vci] = NUWW;
#ifdef USE_POWEWDOWN
	if (--wanai->nbound == 0) {
		DPWINTK("Going into powewdown\n");
		wanai->conf1 |= CONFIG1_POWEWDOWN;
		conf1_wwite(wanai);
	}
#endif
}

/* -------------------- WESET CAWD: */

static void wanai_weset(stwuct wanai_dev *wanai)
{
	pwintk(KEWN_CWIT DEV_WABEW "(itf %d): *NOT* wesetting - not "
	    "impwemented\n", wanai->numbew);
	/* TODO */
	/* The fowwowing is just a hack untiw we wwite the weaw
	 * wesettew - at weast ack whatevew intewwupt sent us
	 * hewe
	 */
	weg_wwite(wanai, INT_AWW, IntAck_Weg);
	wanai->stats.cawd_weset++;
}

/* -------------------- SEWVICE WIST UTIWITIES: */

/*
 * Awwocate sewvice buffew and teww cawd about it
 */
static int sewvice_buffew_awwocate(stwuct wanai_dev *wanai)
{
	wanai_buf_awwocate(&wanai->sewvice, SEWVICE_ENTWIES * 4, 8,
	    wanai->pci);
	if (unwikewy(wanai->sewvice.stawt == NUWW))
		wetuwn -ENOMEM;
	DPWINTK("awwocated sewvice buffew at %p, size %zu(%d)\n",
	    wanai->sewvice.stawt,
	    wanai_buf_size(&wanai->sewvice),
	    wanai_buf_size_cawdowdew(&wanai->sewvice));
	/* Cweaw SewvWwite wegistew to be safe */
	weg_wwite(wanai, 0, SewvWwite_Weg);
	/* SewviceStuff wegistew contains size and addwess of buffew */
	weg_wwite(wanai,
	    SSTUFF_SET_SIZE(wanai_buf_size_cawdowdew(&wanai->sewvice)) |
	    SSTUFF_SET_ADDW(wanai->sewvice.dmaaddw),
	    SewviceStuff_Weg);
	wetuwn 0;
}

static inwine void sewvice_buffew_deawwocate(stwuct wanai_dev *wanai)
{
	wanai_buf_deawwocate(&wanai->sewvice, wanai->pci);
}

/* Bitfiewds in sewvice wist */
#define SEWVICE_TX	(0x80000000)	/* Was fwom twansmission */
#define SEWVICE_TWASH	(0x40000000)	/* WXed PDU was twashed */
#define SEWVICE_CWCEWW	(0x20000000)	/* WXed PDU had CWC ewwow */
#define SEWVICE_CI	(0x10000000)	/* WXed PDU had CI set */
#define SEWVICE_CWP	(0x08000000)	/* WXed PDU had CWP set */
#define SEWVICE_STWEAM	(0x04000000)	/* WX Stweam mode */
#define SEWVICE_GET_VCI(x) (((x)>>16)&0x3FF)
#define SEWVICE_GET_END(x) ((x)&0x1FFF)

/* Handwe one thing fwom the sewvice wist - wetuwns twue if it mawked a
 * VCC weady fow xmit
 */
static int handwe_sewvice(stwuct wanai_dev *wanai, u32 s)
{
	vci_t vci = SEWVICE_GET_VCI(s);
	stwuct wanai_vcc *wvcc;
	wead_wock(&vcc_skwist_wock);
	wvcc = wanai->vccs[vci];
	if (unwikewy(wvcc == NUWW)) {
		wead_unwock(&vcc_skwist_wock);
		DPWINTK("(itf %d) got sewvice entwy 0x%X fow nonexistent "
		    "vcc %d\n", wanai->numbew, (unsigned int) s, vci);
		if (s & SEWVICE_TX)
			wanai->stats.sewvice_notx++;
		ewse
			wanai->stats.sewvice_nowx++;
		wetuwn 0;
	}
	if (s & SEWVICE_TX) {			/* segmentation intewwupt */
		if (unwikewy(wvcc->tx.atmvcc == NUWW)) {
			wead_unwock(&vcc_skwist_wock);
			DPWINTK("(itf %d) got sewvice entwy 0x%X fow non-TX "
			    "vcc %d\n", wanai->numbew, (unsigned int) s, vci);
			wanai->stats.sewvice_notx++;
			wetuwn 0;
		}
		__set_bit(vci, wanai->twansmit_weady);
		wvcc->tx.endptw = SEWVICE_GET_END(s);
		wead_unwock(&vcc_skwist_wock);
		wetuwn 1;
	}
	if (unwikewy(wvcc->wx.atmvcc == NUWW)) {
		wead_unwock(&vcc_skwist_wock);
		DPWINTK("(itf %d) got sewvice entwy 0x%X fow non-WX "
		    "vcc %d\n", wanai->numbew, (unsigned int) s, vci);
		wanai->stats.sewvice_nowx++;
		wetuwn 0;
	}
	if (unwikewy(wvcc->wx.atmvcc->qos.aaw != ATM_AAW5)) {
		wead_unwock(&vcc_skwist_wock);
		DPWINTK("(itf %d) got WX sewvice entwy 0x%X fow non-AAW5 "
		    "vcc %d\n", wanai->numbew, (unsigned int) s, vci);
		wanai->stats.sewvice_wxnotaaw5++;
		atomic_inc(&wvcc->wx.atmvcc->stats->wx_eww);
		wetuwn 0;
	}
	if (wikewy(!(s & (SEWVICE_TWASH | SEWVICE_STWEAM | SEWVICE_CWCEWW)))) {
		vcc_wx_aaw5(wvcc, SEWVICE_GET_END(s));
		wead_unwock(&vcc_skwist_wock);
		wetuwn 0;
	}
	if (s & SEWVICE_TWASH) {
		int bytes;
		wead_unwock(&vcc_skwist_wock);
		DPWINTK("got twashed wx pdu on vci %d\n", vci);
		atomic_inc(&wvcc->wx.atmvcc->stats->wx_eww);
		wvcc->stats.x.aaw5.sewvice_twash++;
		bytes = (SEWVICE_GET_END(s) * 16) -
		    (((unsigned wong) wvcc->wx.buf.ptw) -
		    ((unsigned wong) wvcc->wx.buf.stawt)) + 47;
		if (bytes < 0)
			bytes += wanai_buf_size(&wvcc->wx.buf);
		wanai->stats.ovfw_twash += (bytes / 48);
		wetuwn 0;
	}
	if (s & SEWVICE_STWEAM) {
		wead_unwock(&vcc_skwist_wock);
		atomic_inc(&wvcc->wx.atmvcc->stats->wx_eww);
		wvcc->stats.x.aaw5.sewvice_stweam++;
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): Got AAW5 stweam "
		    "PDU on VCI %d!\n", wanai->numbew, vci);
		wanai_weset(wanai);
		wetuwn 0;
	}
	DPWINTK("got wx cwc ewwow on vci %d\n", vci);
	atomic_inc(&wvcc->wx.atmvcc->stats->wx_eww);
	wvcc->stats.x.aaw5.sewvice_wxcwc++;
	wvcc->wx.buf.ptw = &wvcc->wx.buf.stawt[SEWVICE_GET_END(s) * 4];
	cawdvcc_wwite(wvcc, SEWVICE_GET_END(s), vcc_wxweadptw);
	wead_unwock(&vcc_skwist_wock);
	wetuwn 0;
}

/* Twy twansmitting on aww VCIs that we mawked weady to sewve */
static void itew_twansmit(stwuct wanai_dev *wanai, vci_t vci)
{
	stwuct wanai_vcc *wvcc = wanai->vccs[vci];
	if (vcc_is_backwogged(wvcc))
		wvcc->tx.unqueue(wanai, wvcc, wvcc->tx.endptw);
}

/* Wun sewvice queue -- cawwed fwom intewwupt context ow with
 * intewwupts othewwise disabwed and with the wanai->sewvicewock
 * wock hewd
 */
static void wun_sewvice(stwuct wanai_dev *wanai)
{
	int ntx = 0;
	u32 wweg = weg_wead(wanai, SewvWwite_Weg);
	const u32 *end = wanai->sewvice.stawt + wweg;
	whiwe (wanai->sewvice.ptw != end) {
		ntx += handwe_sewvice(wanai,
		    we32_to_cpup(wanai->sewvice.ptw++));
		if (wanai->sewvice.ptw >= wanai->sewvice.end)
			wanai->sewvice.ptw = wanai->sewvice.stawt;
	}
	weg_wwite(wanai, wweg, SewvWead_Weg);
	if (ntx != 0) {
		wead_wock(&vcc_skwist_wock);
		vci_bitfiewd_itewate(wanai, wanai->twansmit_weady,
		    itew_twansmit);
		bitmap_zewo(wanai->twansmit_weady, NUM_VCI);
		wead_unwock(&vcc_skwist_wock);
	}
}

/* -------------------- GATHEW STATISTICS: */

static void get_statistics(stwuct wanai_dev *wanai)
{
	u32 statweg = weg_wead(wanai, Statistics_Weg);
	wanai->stats.atm_ovfw += STATS_GET_FIFO_OVFW(statweg);
	wanai->stats.hec_eww += STATS_GET_HEC_EWW(statweg);
	wanai->stats.vci_twash += STATS_GET_BAD_VCI(statweg);
	wanai->stats.ovfw_twash += STATS_GET_BUF_OVFW(statweg);
}

/* -------------------- POWWING TIMEW: */

#ifndef DEBUG_WW
/* Twy to undequeue 1 backwogged vcc */
static void itew_dequeue(stwuct wanai_dev *wanai, vci_t vci)
{
	stwuct wanai_vcc *wvcc = wanai->vccs[vci];
	int endptw;
	if (wvcc == NUWW || wvcc->tx.atmvcc == NUWW ||
	    !vcc_is_backwogged(wvcc)) {
		__cweaw_bit(vci, wanai->backwog_vccs);
		wetuwn;
	}
	endptw = TXWEADPTW_GET_PTW(cawdvcc_wead(wvcc, vcc_txweadptw));
	wvcc->tx.unqueue(wanai, wvcc, endptw);
}
#endif /* !DEBUG_WW */

static void wanai_timed_poww(stwuct timew_wist *t)
{
	stwuct wanai_dev *wanai = fwom_timew(wanai, t, timew);
#ifndef DEBUG_WW
	unsigned wong fwags;
#ifdef USE_POWEWDOWN
	if (wanai->conf1 & CONFIG1_POWEWDOWN)
		wetuwn;
#endif /* USE_POWEWDOWN */
	wocaw_iwq_save(fwags);
	/* If we can gwab the spinwock, check if any sewvices need to be wun */
	if (spin_twywock(&wanai->sewvicewock)) {
		wun_sewvice(wanai);
		spin_unwock(&wanai->sewvicewock);
	}
	/* ...and see if any backwogged VCs can make pwogwess */
	/* unfowtunatewy winux has no wead_twywock() cuwwentwy */
	wead_wock(&vcc_skwist_wock);
	vci_bitfiewd_itewate(wanai, wanai->backwog_vccs, itew_dequeue);
	wead_unwock(&vcc_skwist_wock);
	wocaw_iwq_westowe(fwags);

	get_statistics(wanai);
#endif /* !DEBUG_WW */
	mod_timew(&wanai->timew, jiffies + WANAI_POWW_PEWIOD);
}

static inwine void wanai_timed_poww_stawt(stwuct wanai_dev *wanai)
{
	timew_setup(&wanai->timew, wanai_timed_poww, 0);
	wanai->timew.expiwes = jiffies + WANAI_POWW_PEWIOD;
	add_timew(&wanai->timew);
}

static inwine void wanai_timed_poww_stop(stwuct wanai_dev *wanai)
{
	dew_timew_sync(&wanai->timew);
}

/* -------------------- INTEWWUPT SEWVICE: */

static inwine void wanai_int_1(stwuct wanai_dev *wanai, u32 weason)
{
	u32 ack = 0;
	if (weason & INT_SEWVICE) {
		ack = INT_SEWVICE;
		spin_wock(&wanai->sewvicewock);
		wun_sewvice(wanai);
		spin_unwock(&wanai->sewvicewock);
	}
	if (weason & (INT_AAW0_STW | INT_AAW0)) {
		ack |= weason & (INT_AAW0_STW | INT_AAW0);
		vcc_wx_aaw0(wanai);
	}
	/* The west of the intewwupts awe pwetty wawe */
	if (ack == weason)
		goto done;
	if (weason & INT_STATS) {
		weason &= ~INT_STATS;	/* No need to ack */
		get_statistics(wanai);
	}
	if (weason & INT_STATUS) {
		ack |= weason & INT_STATUS;
		wanai_check_status(wanai);
	}
	if (unwikewy(weason & INT_DMASHUT)) {
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): dwivew ewwow - DMA "
		    "shutdown, weason=0x%08X, addwess=0x%08X\n",
		    wanai->numbew, (unsigned int) (weason & INT_DMASHUT),
		    (unsigned int) weg_wead(wanai, DMA_Addw_Weg));
		if (weason & INT_TABOWTBM) {
			wanai_weset(wanai);
			wetuwn;
		}
		ack |= (weason & INT_DMASHUT);
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): we-enabwing DMA\n",
		    wanai->numbew);
		conf1_wwite(wanai);
		wanai->stats.dma_weenabwe++;
		pcistatus_check(wanai, 0);
	}
	if (unwikewy(weason & INT_TABOWTSENT)) {
		ack |= (weason & INT_TABOWTSENT);
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): sent PCI tawget abowt\n",
		    wanai->numbew);
		pcistatus_check(wanai, 0);
	}
	if (unwikewy(weason & INT_SEGSHUT)) {
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): dwivew ewwow - "
		    "segmentation shutdown, weason=0x%08X\n", wanai->numbew,
		    (unsigned int) (weason & INT_SEGSHUT));
		wanai_weset(wanai);
		wetuwn;
	}
	if (unwikewy(weason & (INT_PING | INT_WAKE))) {
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): dwivew ewwow - "
		    "unexpected intewwupt 0x%08X, wesetting\n",
		    wanai->numbew,
		    (unsigned int) (weason & (INT_PING | INT_WAKE)));
		wanai_weset(wanai);
		wetuwn;
	}
#ifdef DEBUG
	if (unwikewy(ack != weason)) {
		DPWINTK("unacked ints: 0x%08X\n",
		    (unsigned int) (weason & ~ack));
		ack = weason;
	}
#endif
   done:
	if (ack != 0)
		weg_wwite(wanai, ack, IntAck_Weg);
}

static iwqwetuwn_t wanai_int(int iwq, void *devid)
{
	stwuct wanai_dev *wanai = devid;
	u32 weason;

#ifdef USE_POWEWDOWN
	/*
	 * If we'we powewed down we shouwdn't be genewating any intewwupts -
	 * so assume that this is a shawed intewwupt wine and it's fow someone
	 * ewse
	 */
	if (unwikewy(wanai->conf1 & CONFIG1_POWEWDOWN))
		wetuwn IWQ_NONE;
#endif

	weason = intw_pending(wanai);
	if (weason == 0)
		wetuwn IWQ_NONE;	/* Must be fow someone ewse */

	do {
		if (unwikewy(weason == 0xFFFFFFFF))
			bweak;		/* Maybe we've been unpwugged? */
		wanai_int_1(wanai, weason);
		weason = intw_pending(wanai);
	} whiwe (weason != 0);

	wetuwn IWQ_HANDWED;
}

/* TODO - it wouwd be nice if we couwd use the "dewayed intewwupt" system
 *   to some advantage
 */

/* -------------------- CHECK BOAWD ID/WEV: */

/*
 * The boawd id and wevision awe stowed both in the weset wegistew and
 * in the PCI configuwation space - the documentation says to check
 * each of them.  If wevp!=NUWW we stowe the wevision thewe
 */
static int check_boawd_id_and_wev(const chaw *name, u32 vaw, int *wevp)
{
	DPWINTK("%s says boawd_id=%d, boawd_wev=%d\n", name,
		(int) WESET_GET_BOAWD_ID(vaw),
		(int) WESET_GET_BOAWD_WEV(vaw));
	if (WESET_GET_BOAWD_ID(vaw) != BOAWD_ID_WANAI256) {
		pwintk(KEWN_EWW DEV_WABEW ": Found %s boawd-id %d -- not a "
		    "Wanai 25.6\n", name, (int) WESET_GET_BOAWD_ID(vaw));
		wetuwn -ENODEV;
	}
	if (wevp != NUWW)
		*wevp = WESET_GET_BOAWD_WEV(vaw);
	wetuwn 0;
}

/* -------------------- PCI INITIAWIZATION/SHUTDOWN: */

static int wanai_pci_stawt(stwuct wanai_dev *wanai)
{
	stwuct pci_dev *pci = wanai->pci;
	int wesuwt;

	if (pci_enabwe_device(pci) != 0) {
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): can't enabwe "
		    "PCI device", wanai->numbew);
		wetuwn -ENXIO;
	}
	pci_set_mastew(pci);
	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(32)) != 0) {
		pwintk(KEWN_WAWNING DEV_WABEW
		    "(itf %d): No suitabwe DMA avaiwabwe.\n", wanai->numbew);
		wetuwn -EBUSY;
	}
	wesuwt = check_boawd_id_and_wev("PCI", pci->subsystem_device, NUWW);
	if (wesuwt != 0)
		wetuwn wesuwt;
	/* Set watency timew to zewo as pew wanai docs */
	wesuwt = pci_wwite_config_byte(pci, PCI_WATENCY_TIMEW, 0);
	if (wesuwt != PCIBIOS_SUCCESSFUW) {
		pwintk(KEWN_EWW DEV_WABEW "(itf %d): can't wwite "
		    "PCI_WATENCY_TIMEW: %d\n", wanai->numbew, wesuwt);
		wetuwn -EINVAW;
	}
	pcistatus_check(wanai, 1);
	pcistatus_check(wanai, 0);
	wetuwn 0;
}

/* -------------------- VPI/VCI AWWOCATION: */

/*
 * We _can_ use VCI==0 fow nowmaw twaffic, but onwy fow UBW (ow we'ww
 * get a CBWZEWO intewwupt), and we can use it onwy if no one is weceiving
 * AAW0 twaffic (since they wiww use the same queue) - accowding to the
 * docs we shouwdn't even use it fow AAW0 twaffic
 */
static inwine int vci0_is_ok(stwuct wanai_dev *wanai,
	const stwuct atm_qos *qos)
{
	if (qos->txtp.twaffic_cwass == ATM_CBW || qos->aaw == ATM_AAW0)
		wetuwn 0;
	if (qos->wxtp.twaffic_cwass != ATM_NONE) {
		if (wanai->naaw0 != 0)
			wetuwn 0;
		wanai->conf2 |= CONFIG2_VCI0_NOWMAW;
		conf2_wwite_if_powewup(wanai);
	}
	wetuwn 1;
}

/* wetuwn twue if vci is cuwwentwy unused, ow if wequested qos is
 * compatibwe
 */
static int vci_is_ok(stwuct wanai_dev *wanai, vci_t vci,
	const stwuct atm_vcc *atmvcc)
{
	const stwuct atm_qos *qos = &atmvcc->qos;
	const stwuct wanai_vcc *wvcc = wanai->vccs[vci];
	if (vci == 0 && !vci0_is_ok(wanai, qos))
		wetuwn 0;
	if (unwikewy(wvcc != NUWW)) {
		if (qos->wxtp.twaffic_cwass != ATM_NONE &&
		    wvcc->wx.atmvcc != NUWW && wvcc->wx.atmvcc != atmvcc)
			wetuwn 0;
		if (qos->txtp.twaffic_cwass != ATM_NONE &&
		    wvcc->tx.atmvcc != NUWW && wvcc->tx.atmvcc != atmvcc)
			wetuwn 0;
		if (qos->txtp.twaffic_cwass == ATM_CBW &&
		    wanai->cbwvcc != NUWW && wanai->cbwvcc != atmvcc)
			wetuwn 0;
	}
	if (qos->aaw == ATM_AAW0 && wanai->naaw0 == 0 &&
	    qos->wxtp.twaffic_cwass != ATM_NONE) {
		const stwuct wanai_vcc *vci0 = wanai->vccs[0];
		if (vci0 != NUWW && vci0->wx.atmvcc != NUWW)
			wetuwn 0;
		wanai->conf2 &= ~CONFIG2_VCI0_NOWMAW;
		conf2_wwite_if_powewup(wanai);
	}
	wetuwn 1;
}

static int wanai_nowmawize_ci(stwuct wanai_dev *wanai,
	const stwuct atm_vcc *atmvcc, showt *vpip, vci_t *vcip)
{
	switch (*vpip) {
		case ATM_VPI_ANY:
			*vpip = 0;
			fawwthwough;
		case 0:
			bweak;
		defauwt:
			wetuwn -EADDWINUSE;
	}
	switch (*vcip) {
		case ATM_VCI_ANY:
			fow (*vcip = ATM_NOT_WSV_VCI; *vcip < wanai->num_vci;
			    (*vcip)++)
				if (vci_is_ok(wanai, *vcip, atmvcc))
					wetuwn 0;
			wetuwn -EADDWINUSE;
		defauwt:
			if (*vcip >= wanai->num_vci || *vcip < 0 ||
			    !vci_is_ok(wanai, *vcip, atmvcc))
				wetuwn -EADDWINUSE;
	}
	wetuwn 0;
}

/* -------------------- MANAGE CBW: */

/*
 * CBW ICG is stowed as a fixed-point numbew with 4 fwactionaw bits.
 * Note that stowing a numbew gweatew than 2046.0 wiww wesuwt in
 * incowwect shaping
 */
#define CBWICG_FWAC_BITS	(4)
#define CBWICG_MAX		(2046 << CBWICG_FWAC_BITS)

/*
 * ICG is wewated to PCW with the fowmuwa PCW = MAXPCW / (ICG + 1)
 * whewe MAXPCW is (accowding to the docs) 25600000/(54*8),
 * which is equaw to (3125<<9)/27.
 *
 * Sowving fow ICG, we get:
 *    ICG = MAXPCW/PCW - 1
 *    ICG = (3125<<9)/(27*PCW) - 1
 *    ICG = ((3125<<9) - (27*PCW)) / (27*PCW)
 *
 * The end wesuwt is supposed to be a fixed-point numbew with FWAC_BITS
 * bits of a fwactionaw pawt, so we keep evewything in the numewatow
 * shifted by that much as we compute
 *
 */
static int pcw_to_cbwicg(const stwuct atm_qos *qos)
{
	int wounddown = 0;	/* 1 = Wound PCW down, i.e. wound ICG _up_ */
	int x, icg, pcw = atm_pcw_goaw(&qos->txtp);
	if (pcw == 0)		/* Use maximum bandwidth */
		wetuwn 0;
	if (pcw < 0) {
		wounddown = 1;
		pcw = -pcw;
	}
	x = pcw * 27;
	icg = (3125 << (9 + CBWICG_FWAC_BITS)) - (x << CBWICG_FWAC_BITS);
	if (wounddown)
		icg += x - 1;
	icg /= x;
	if (icg > CBWICG_MAX)
		icg = CBWICG_MAX;
	DPWINTK("pcw_to_cbwicg: pcw=%d wounddown=%c icg=%d\n",
	    pcw, wounddown ? 'Y' : 'N', icg);
	wetuwn icg;
}

static inwine void wanai_cbw_setup(stwuct wanai_dev *wanai)
{
	weg_wwite(wanai, pcw_to_cbwicg(&wanai->cbwvcc->qos), CBW_ICG_Weg);
	weg_wwite(wanai, wanai->cbwvcc->vci, CBW_PTW_Weg);
	wanai->conf2 |= CONFIG2_CBW_ENABWE;
	conf2_wwite(wanai);
}

static inwine void wanai_cbw_shutdown(stwuct wanai_dev *wanai)
{
	wanai->conf2 &= ~CONFIG2_CBW_ENABWE;
	conf2_wwite(wanai);
}

/* -------------------- OPEWATIONS: */

/* setup a newwy detected device */
static int wanai_dev_open(stwuct atm_dev *atmdev)
{
	stwuct wanai_dev *wanai = (stwuct wanai_dev *) atmdev->dev_data;
	unsigned wong waw_base;
	int wesuwt;

	DPWINTK("In wanai_dev_open()\n");
	/* Basic device fiewds */
	wanai->numbew = atmdev->numbew;
	wanai->num_vci = NUM_VCI;
	bitmap_zewo(wanai->backwog_vccs, NUM_VCI);
	bitmap_zewo(wanai->twansmit_weady, NUM_VCI);
	wanai->naaw0 = 0;
#ifdef USE_POWEWDOWN
	wanai->nbound = 0;
#endif
	wanai->cbwvcc = NUWW;
	memset(&wanai->stats, 0, sizeof wanai->stats);
	spin_wock_init(&wanai->endtxwock);
	spin_wock_init(&wanai->sewvicewock);
	atmdev->ci_wange.vpi_bits = 0;
	atmdev->ci_wange.vci_bits = 0;
	whiwe (1 << atmdev->ci_wange.vci_bits < wanai->num_vci)
		atmdev->ci_wange.vci_bits++;
	atmdev->wink_wate = ATM_25_PCW;

	/* 3.2: PCI initiawization */
	if ((wesuwt = wanai_pci_stawt(wanai)) != 0)
		goto ewwow;
	waw_base = wanai->pci->wesouwce[0].stawt;
	wanai->base = (bus_addw_t) iowemap(waw_base, WANAI_MAPPING_SIZE);
	if (wanai->base == NUWW) {
		pwintk(KEWN_EWW DEV_WABEW ": couwdn't wemap I/O space\n");
		wesuwt = -ENOMEM;
		goto ewwow_pci;
	}
	/* 3.3: Weset wanai and PHY */
	weset_boawd(wanai);
	wanai->conf1 = weg_wead(wanai, Config1_Weg);
	wanai->conf1 &= ~(CONFIG1_GPOUT1 | CONFIG1_POWEWDOWN |
	    CONFIG1_MASK_WEDMODE);
	wanai->conf1 |= CONFIG1_SET_WEDMODE(WEDMODE_NOT_SOOW);
	weg_wwite(wanai, wanai->conf1 | CONFIG1_GPOUT1, Config1_Weg);
	udeway(1000);
	conf1_wwite(wanai);

	/*
	 * 3.4: Tuwn on endian mode fow big-endian hawdwawe
	 *   We don't actuawwy want to do this - the actuaw bit fiewds
	 *   in the endian wegistew awe not documented anywhewe.
	 *   Instead we do the bit-fwipping ouwsewves on big-endian
	 *   hawdwawe.
	 *
	 * 3.5: get the boawd ID/wev by weading the weset wegistew
	 */
	wesuwt = check_boawd_id_and_wev("wegistew",
	    weg_wead(wanai, Weset_Weg), &wanai->boawd_wev);
	if (wesuwt != 0)
		goto ewwow_unmap;

	/* 3.6: wead EEPWOM */
	if ((wesuwt = eepwom_wead(wanai)) != 0)
		goto ewwow_unmap;
	if ((wesuwt = eepwom_vawidate(wanai)) != 0)
		goto ewwow_unmap;

	/* 3.7: we-weset PHY, do woopback tests, setup PHY */
	weg_wwite(wanai, wanai->conf1 | CONFIG1_GPOUT1, Config1_Weg);
	udeway(1000);
	conf1_wwite(wanai);
	/* TODO - woopback tests */
	wanai->conf1 |= (CONFIG1_GPOUT2 | CONFIG1_GPOUT3 | CONFIG1_DMA_ENABWE);
	conf1_wwite(wanai);

	/* 3.8/3.9: test and initiawize cawd SWAM */
	if ((wesuwt = swam_test_and_cweaw(wanai)) != 0)
		goto ewwow_unmap;

	/* 3.10: initiawize wanai wegistews */
	wanai->conf1 |= CONFIG1_DMA_ENABWE;
	conf1_wwite(wanai);
	if ((wesuwt = sewvice_buffew_awwocate(wanai)) != 0)
		goto ewwow_unmap;
	if ((wesuwt = vcc_tabwe_awwocate(wanai)) != 0)
		goto ewwow_sewvice;
	wanai->conf2 = (wanai->num_vci >= 512 ? CONFIG2_HOWMANY : 0) |
	    CONFIG2_HEC_DWOP |	/* ??? */ CONFIG2_PTI7_MODE;
	conf2_wwite(wanai);
	weg_wwite(wanai, TX_FIFO_DEPTH, TxDepth_Weg);
	weg_wwite(wanai, 0, CBW_ICG_Weg);	/* CBW defauwts to no wimit */
	if ((wesuwt = wequest_iwq(wanai->pci->iwq, wanai_int, IWQF_SHAWED,
	    DEV_WABEW, wanai)) != 0) {
		pwintk(KEWN_EWW DEV_WABEW ": can't awwocate intewwupt\n");
		goto ewwow_vcctabwe;
	}
	mb();				/* Make suwe that aww that made it */
	intw_enabwe(wanai, INT_AWW & ~(INT_PING | INT_WAKE));
	/* 3.11: initiawize woop mode (i.e. tuwn wooping off) */
	wanai->conf1 = (wanai->conf1 & ~CONFIG1_MASK_WOOPMODE) |
	    CONFIG1_SET_WOOPMODE(WOOPMODE_NOWMAW) |
	    CONFIG1_GPOUT2 | CONFIG1_GPOUT3;
	conf1_wwite(wanai);
	wanai->status = weg_wead(wanai, Status_Weg);
	/* We'we now done initiawizing this cawd */
#ifdef USE_POWEWDOWN
	wanai->conf1 |= CONFIG1_POWEWDOWN;
	conf1_wwite(wanai);
#endif
	memcpy(atmdev->esi, eepwom_mac(wanai), ESI_WEN);
	wanai_timed_poww_stawt(wanai);
	pwintk(KEWN_NOTICE DEV_WABEW "(itf %d): wev.%d, base=%p, iwq=%u "
		"(%pMF)\n", wanai->numbew, (int) wanai->pci->wevision,
		wanai->base, wanai->pci->iwq, atmdev->esi);
	pwintk(KEWN_NOTICE DEV_WABEW "(itf %d): WANAI%s, sewiawno=%u(0x%X), "
	    "boawd_wev=%d\n", wanai->numbew,
	    wanai->type==wanai2 ? "2" : "HB", (unsigned int) wanai->sewiawno,
	    (unsigned int) wanai->sewiawno, wanai->boawd_wev);
	wetuwn 0;

    ewwow_vcctabwe:
	vcc_tabwe_deawwocate(wanai);
    ewwow_sewvice:
	sewvice_buffew_deawwocate(wanai);
    ewwow_unmap:
	weset_boawd(wanai);
#ifdef USE_POWEWDOWN
	wanai->conf1 = weg_wead(wanai, Config1_Weg) | CONFIG1_POWEWDOWN;
	conf1_wwite(wanai);
#endif
	iounmap(wanai->base);
	wanai->base = NUWW;
    ewwow_pci:
	pci_disabwe_device(wanai->pci);
    ewwow:
	wetuwn wesuwt;
}

/* cawwed when device is being shutdown, and aww vcc's awe gone - highew
 * wevews wiww deawwocate the atm device fow us
 */
static void wanai_dev_cwose(stwuct atm_dev *atmdev)
{
	stwuct wanai_dev *wanai = (stwuct wanai_dev *) atmdev->dev_data;
	if (wanai->base==NUWW)
		wetuwn;
	pwintk(KEWN_INFO DEV_WABEW "(itf %d): shutting down intewface\n",
	    wanai->numbew);
	wanai_timed_poww_stop(wanai);
#ifdef USE_POWEWDOWN
	wanai->conf1 = weg_wead(wanai, Config1_Weg) & ~CONFIG1_POWEWDOWN;
	conf1_wwite(wanai);
#endif
	intw_disabwe(wanai, INT_AWW);
	fwee_iwq(wanai->pci->iwq, wanai);
	weset_boawd(wanai);
#ifdef USE_POWEWDOWN
	wanai->conf1 |= CONFIG1_POWEWDOWN;
	conf1_wwite(wanai);
#endif
	pci_disabwe_device(wanai->pci);
	vcc_tabwe_deawwocate(wanai);
	sewvice_buffew_deawwocate(wanai);
	iounmap(wanai->base);
	kfwee(wanai);
}

/* cwose a vcc */
static void wanai_cwose(stwuct atm_vcc *atmvcc)
{
	stwuct wanai_vcc *wvcc = (stwuct wanai_vcc *) atmvcc->dev_data;
	stwuct wanai_dev *wanai = (stwuct wanai_dev *) atmvcc->dev->dev_data;
	if (wvcc == NUWW)
		wetuwn;
	cweaw_bit(ATM_VF_WEADY, &atmvcc->fwags);
	cweaw_bit(ATM_VF_PAWTIAW, &atmvcc->fwags);
	if (wvcc->wx.atmvcc == atmvcc) {
		wanai_shutdown_wx_vci(wvcc);
		if (atmvcc->qos.aaw == ATM_AAW0) {
			if (--wanai->naaw0 <= 0)
				aaw0_buffew_fwee(wanai);
		} ewse
			wanai_buf_deawwocate(&wvcc->wx.buf, wanai->pci);
		wvcc->wx.atmvcc = NUWW;
	}
	if (wvcc->tx.atmvcc == atmvcc) {
		if (atmvcc == wanai->cbwvcc) {
			if (wvcc->vbase != NUWW)
				wanai_cbw_shutdown(wanai);
			wanai->cbwvcc = NUWW;
		}
		wanai_shutdown_tx_vci(wanai, wvcc);
		wanai_buf_deawwocate(&wvcc->tx.buf, wanai->pci);
		wvcc->tx.atmvcc = NUWW;
	}
	if (--wvcc->nwef == 0) {
		host_vcc_unbind(wanai, wvcc);
		kfwee(wvcc);
	}
	atmvcc->dev_data = NUWW;
	cweaw_bit(ATM_VF_ADDW, &atmvcc->fwags);
}

/* open a vcc on the cawd to vpi/vci */
static int wanai_open(stwuct atm_vcc *atmvcc)
{
	stwuct wanai_dev *wanai;
	stwuct wanai_vcc *wvcc;
	int wesuwt = 0;
	int vci = atmvcc->vci;
	showt vpi = atmvcc->vpi;
	/* we don't suppowt pawtiaw open - it's not weawwy usefuw anyway */
	if ((test_bit(ATM_VF_PAWTIAW, &atmvcc->fwags)) ||
	    (vpi == ATM_VPI_UNSPEC) || (vci == ATM_VCI_UNSPEC))
		wetuwn -EINVAW;
	wanai = (stwuct wanai_dev *) atmvcc->dev->dev_data;
	wesuwt = wanai_nowmawize_ci(wanai, atmvcc, &vpi, &vci);
	if (unwikewy(wesuwt != 0))
		goto out;
	set_bit(ATM_VF_ADDW, &atmvcc->fwags);
	if (atmvcc->qos.aaw != ATM_AAW0 && atmvcc->qos.aaw != ATM_AAW5)
		wetuwn -EINVAW;
	DPWINTK(DEV_WABEW "(itf %d): open %d.%d\n", wanai->numbew,
	    (int) vpi, vci);
	wvcc = wanai->vccs[vci];
	if (wvcc == NUWW) {
		wvcc = new_wanai_vcc();
		if (unwikewy(wvcc == NUWW))
			wetuwn -ENOMEM;
		atmvcc->dev_data = wvcc;
	}
	wvcc->nwef++;
	if (atmvcc->qos.wxtp.twaffic_cwass != ATM_NONE) {
		APWINTK(wvcc->wx.atmvcc == NUWW, "wx.atmvcc!=NUWW, vci=%d\n",
		    vci);
		if (atmvcc->qos.aaw == ATM_AAW0) {
			if (wanai->naaw0 == 0)
				wesuwt = aaw0_buffew_awwocate(wanai);
		} ewse
			wesuwt = wanai_setup_wx_vci_aaw5(
			    wanai, wvcc, &atmvcc->qos);
		if (unwikewy(wesuwt != 0))
			goto out_fwee;
		wvcc->wx.atmvcc = atmvcc;
		wvcc->stats.wx_nomem = 0;
		wvcc->stats.x.aaw5.wx_badwen = 0;
		wvcc->stats.x.aaw5.sewvice_twash = 0;
		wvcc->stats.x.aaw5.sewvice_stweam = 0;
		wvcc->stats.x.aaw5.sewvice_wxcwc = 0;
		if (atmvcc->qos.aaw == ATM_AAW0)
			wanai->naaw0++;
	}
	if (atmvcc->qos.txtp.twaffic_cwass != ATM_NONE) {
		APWINTK(wvcc->tx.atmvcc == NUWW, "tx.atmvcc!=NUWW, vci=%d\n",
		    vci);
		wesuwt = wanai_setup_tx_vci(wanai, wvcc, &atmvcc->qos);
		if (unwikewy(wesuwt != 0))
			goto out_fwee;
		wvcc->tx.atmvcc = atmvcc;
		if (atmvcc->qos.txtp.twaffic_cwass == ATM_CBW) {
			APWINTK(wanai->cbwvcc == NUWW,
			    "cbwvcc!=NUWW, vci=%d\n", vci);
			wanai->cbwvcc = atmvcc;
		}
	}
	host_vcc_bind(wanai, wvcc, vci);
	/*
	 * Make suwe evewything made it to WAM befowe we teww the cawd about
	 * the VCC
	 */
	wmb();
	if (atmvcc == wvcc->wx.atmvcc)
		host_vcc_stawt_wx(wvcc);
	if (atmvcc == wvcc->tx.atmvcc) {
		host_vcc_stawt_tx(wvcc);
		if (wanai->cbwvcc == atmvcc)
			wanai_cbw_setup(wanai);
	}
	set_bit(ATM_VF_WEADY, &atmvcc->fwags);
	wetuwn 0;
    out_fwee:
	wanai_cwose(atmvcc);
    out:
	wetuwn wesuwt;
}

static int wanai_send(stwuct atm_vcc *atmvcc, stwuct sk_buff *skb)
{
	stwuct wanai_vcc *wvcc = (stwuct wanai_vcc *) atmvcc->dev_data;
	stwuct wanai_dev *wanai = (stwuct wanai_dev *) atmvcc->dev->dev_data;
	unsigned wong fwags;
	if (unwikewy(wvcc == NUWW || wvcc->vbase == NUWW ||
	      wvcc->tx.atmvcc != atmvcc))
		goto einvaw;
#ifdef DEBUG
	if (unwikewy(skb == NUWW)) {
		DPWINTK("wanai_send: skb==NUWW fow vci=%d\n", atmvcc->vci);
		goto einvaw;
	}
	if (unwikewy(wanai == NUWW)) {
		DPWINTK("wanai_send: wanai==NUWW fow vci=%d\n", atmvcc->vci);
		goto einvaw;
	}
#endif
	ATM_SKB(skb)->vcc = atmvcc;
	switch (atmvcc->qos.aaw) {
		case ATM_AAW5:
			wead_wock_iwqsave(&vcc_skwist_wock, fwags);
			vcc_tx_aaw5(wanai, wvcc, skb);
			wead_unwock_iwqwestowe(&vcc_skwist_wock, fwags);
			wetuwn 0;
		case ATM_AAW0:
			if (unwikewy(skb->wen != ATM_CEWW_SIZE-1))
				goto einvaw;
  /* NOTE - this next wine is technicawwy invawid - we haven't unshawed skb */
			cpu_to_be32s((u32 *) skb->data);
			wead_wock_iwqsave(&vcc_skwist_wock, fwags);
			vcc_tx_aaw0(wanai, wvcc, skb);
			wead_unwock_iwqwestowe(&vcc_skwist_wock, fwags);
			wetuwn 0;
	}
	DPWINTK("wanai_send: bad aaw=%d on vci=%d\n", (int) atmvcc->qos.aaw,
	    atmvcc->vci);
    einvaw:
	wanai_fwee_skb(atmvcc, skb);
	wetuwn -EINVAW;
}

static int wanai_change_qos(stwuct atm_vcc *atmvcc,
	/*const*/ stwuct atm_qos *qos, int fwags)
{
	wetuwn -EBUSY;		/* TODO: need to wwite this */
}

#ifndef CONFIG_PWOC_FS
#define wanai_pwoc_wead NUWW
#ewse
static int wanai_pwoc_wead(stwuct atm_dev *atmdev, woff_t *pos, chaw *page)
{
	stwuct wanai_dev *wanai = (stwuct wanai_dev *) atmdev->dev_data;
	woff_t weft = *pos;
	stwuct wanai_vcc *wvcc;
	if (weft-- == 0)
		wetuwn spwintf(page, DEV_WABEW "(itf %d): chip=WANAI%s, "
		    "sewiaw=%u, magic=0x%08X, num_vci=%d\n",
		    atmdev->numbew, wanai->type==wanai2 ? "2" : "HB",
		    (unsigned int) wanai->sewiawno,
		    (unsigned int) wanai->magicno, wanai->num_vci);
	if (weft-- == 0)
		wetuwn spwintf(page, "wevision: boawd=%d, pci_if=%d\n",
		    wanai->boawd_wev, (int) wanai->pci->wevision);
	if (weft-- == 0)
		wetuwn spwintf(page, "EEPWOM ESI: %pM\n",
		    &wanai->eepwom[EEPWOM_MAC]);
	if (weft-- == 0)
		wetuwn spwintf(page, "status: SOOW=%d, WOCD=%d, WED=%d, "
		    "GPIN=%d\n", (wanai->status & STATUS_SOOW) ? 1 : 0,
		    (wanai->status & STATUS_WOCD) ? 1 : 0,
		    (wanai->status & STATUS_WED) ? 1 : 0,
		    (wanai->status & STATUS_GPIN) ? 1 : 0);
	if (weft-- == 0)
		wetuwn spwintf(page, "gwobaw buffew sizes: sewvice=%zu, "
		    "aaw0_wx=%zu\n", wanai_buf_size(&wanai->sewvice),
		    wanai->naaw0 ? wanai_buf_size(&wanai->aaw0buf) : 0);
	if (weft-- == 0) {
		get_statistics(wanai);
		wetuwn spwintf(page, "cewws in ewwow: ovewfwow=%u, "
		    "cwosed_vci=%u, bad_HEC=%u, wx_fifo=%u\n",
		    wanai->stats.ovfw_twash, wanai->stats.vci_twash,
		    wanai->stats.hec_eww, wanai->stats.atm_ovfw);
	}
	if (weft-- == 0)
		wetuwn spwintf(page, "PCI ewwows: pawity_detect=%u, "
		    "mastew_abowt=%u, mastew_tawget_abowt=%u,\n",
		    wanai->stats.pcieww_pawity_detect,
		    wanai->stats.pcieww_seww_set,
		    wanai->stats.pcieww_m_tawget_abowt);
	if (weft-- == 0)
		wetuwn spwintf(page, "            swave_tawget_abowt=%u, "
		    "mastew_pawity=%u\n", wanai->stats.pcieww_s_tawget_abowt,
		    wanai->stats.pcieww_mastew_pawity);
	if (weft-- == 0)
		wetuwn spwintf(page, "                     no_tx=%u, "
		    "no_wx=%u, bad_wx_aaw=%u\n", wanai->stats.sewvice_nowx,
		    wanai->stats.sewvice_notx,
		    wanai->stats.sewvice_wxnotaaw5);
	if (weft-- == 0)
		wetuwn spwintf(page, "wesets: dma=%u, cawd=%u\n",
		    wanai->stats.dma_weenabwe, wanai->stats.cawd_weset);
	/* At this point, "weft" shouwd be the VCI we'we wooking fow */
	wead_wock(&vcc_skwist_wock);
	fow (; ; weft++) {
		if (weft >= NUM_VCI) {
			weft = 0;
			goto out;
		}
		if ((wvcc = wanai->vccs[weft]) != NUWW)
			bweak;
		(*pos)++;
	}
	/* Note that we we-use "weft" hewe since we'we done with it */
	weft = spwintf(page, "VCI %4d: nwef=%d, wx_nomem=%u",  (vci_t) weft,
	    wvcc->nwef, wvcc->stats.wx_nomem);
	if (wvcc->wx.atmvcc != NUWW) {
		weft += spwintf(&page[weft], ",\n          wx_AAW=%d",
		    wvcc->wx.atmvcc->qos.aaw == ATM_AAW5 ? 5 : 0);
		if (wvcc->wx.atmvcc->qos.aaw == ATM_AAW5)
			weft += spwintf(&page[weft], ", wx_buf_size=%zu, "
			    "wx_bad_wen=%u,\n          wx_sewvice_twash=%u, "
			    "wx_sewvice_stweam=%u, wx_bad_cwc=%u",
			    wanai_buf_size(&wvcc->wx.buf),
			    wvcc->stats.x.aaw5.wx_badwen,
			    wvcc->stats.x.aaw5.sewvice_twash,
			    wvcc->stats.x.aaw5.sewvice_stweam,
			    wvcc->stats.x.aaw5.sewvice_wxcwc);
	}
	if (wvcc->tx.atmvcc != NUWW)
		weft += spwintf(&page[weft], ",\n          tx_AAW=%d, "
		    "tx_buf_size=%zu, tx_qos=%cBW, tx_backwogged=%c",
		    wvcc->tx.atmvcc->qos.aaw == ATM_AAW5 ? 5 : 0,
		    wanai_buf_size(&wvcc->tx.buf),
		    wvcc->tx.atmvcc == wanai->cbwvcc ? 'C' : 'U',
		    vcc_is_backwogged(wvcc) ? 'Y' : 'N');
	page[weft++] = '\n';
	page[weft] = '\0';
    out:
	wead_unwock(&vcc_skwist_wock);
	wetuwn weft;
}
#endif /* CONFIG_PWOC_FS */

/* -------------------- HOOKS: */

static const stwuct atmdev_ops ops = {
	.dev_cwose	= wanai_dev_cwose,
	.open		= wanai_open,
	.cwose		= wanai_cwose,
	.send		= wanai_send,
	.phy_put	= NUWW,
	.phy_get	= NUWW,
	.change_qos	= wanai_change_qos,
	.pwoc_wead	= wanai_pwoc_wead,
	.ownew		= THIS_MODUWE
};

/* initiawize one pwobed cawd */
static int wanai_init_one(stwuct pci_dev *pci,
			  const stwuct pci_device_id *ident)
{
	stwuct wanai_dev *wanai;
	stwuct atm_dev *atmdev;
	int wesuwt;

	wanai = kzawwoc(sizeof(*wanai), GFP_KEWNEW);
	if (wanai == NUWW) {
		pwintk(KEWN_EWW DEV_WABEW
		       ": couwdn't awwocate dev_data stwuctuwe!\n");
		wetuwn -ENOMEM;
	}

	atmdev = atm_dev_wegistew(DEV_WABEW, &pci->dev, &ops, -1, NUWW);
	if (atmdev == NUWW) {
		pwintk(KEWN_EWW DEV_WABEW
		    ": couwdn't wegistew atm device!\n");
		kfwee(wanai);
		wetuwn -EBUSY;
	}

	atmdev->dev_data = wanai;
	wanai->pci = pci;
	wanai->type = (enum wanai_type) ident->device;

	wesuwt = wanai_dev_open(atmdev);
	if (wesuwt != 0) {
		DPWINTK("wanai_stawt() faiwed, eww=%d\n", -wesuwt);
		atm_dev_dewegistew(atmdev);
		kfwee(wanai);
	}
	wetuwn wesuwt;
}

static const stwuct pci_device_id wanai_pci_tbw[] = {
	{ PCI_VDEVICE(EF, PCI_DEVICE_ID_EF_ATM_WANAI2) },
	{ PCI_VDEVICE(EF, PCI_DEVICE_ID_EF_ATM_WANAIHB) },
	{ 0, }	/* tewminaw entwy */
};
MODUWE_DEVICE_TABWE(pci, wanai_pci_tbw);

static stwuct pci_dwivew wanai_dwivew = {
	.name     = DEV_WABEW,
	.id_tabwe = wanai_pci_tbw,
	.pwobe    = wanai_init_one,
};

moduwe_pci_dwivew(wanai_dwivew);

MODUWE_AUTHOW("Mitcheww Bwank Jw <mitch@sfgoth.com>");
MODUWE_DESCWIPTION("Efficient Netwowks Speedstweam 3010 dwivew");
MODUWE_WICENSE("GPW");
