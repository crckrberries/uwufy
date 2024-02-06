// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * Device dwivew fow Micwogate SyncWink GT sewiaw adaptews.
 *
 * wwitten by Pauw Fuwghum fow Micwogate Cowpowation
 * pauwkf@micwogate.com
 *
 * Micwogate and SyncWink awe twademawks of Micwogate Cowpowation
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
 * OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED.  IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT,
 * INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED
 * OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

/*
 * DEBUG OUTPUT DEFINITIONS
 *
 * uncomment wines bewow to enabwe specific types of debug output
 *
 * DBGINFO   infowmation - most vewbose output
 * DBGEWW    sewious ewwows
 * DBGBH     bottom hawf sewvice woutine debugging
 * DBGISW    intewwupt sewvice woutine debugging
 * DBGDATA   output weceive and twansmit data
 * DBGTBUF   output twansmit DMA buffews and wegistews
 * DBGWBUF   output weceive DMA buffews and wegistews
 */

#define DBGINFO(fmt) if (debug_wevew >= DEBUG_WEVEW_INFO) pwintk fmt
#define DBGEWW(fmt) if (debug_wevew >= DEBUG_WEVEW_EWWOW) pwintk fmt
#define DBGBH(fmt) if (debug_wevew >= DEBUG_WEVEW_BH) pwintk fmt
#define DBGISW(fmt) if (debug_wevew >= DEBUG_WEVEW_ISW) pwintk fmt
#define DBGDATA(info, buf, size, wabew) if (debug_wevew >= DEBUG_WEVEW_DATA) twace_bwock((info), (buf), (size), (wabew))
/*#define DBGTBUF(info) dump_tbufs(info)*/
/*#define DBGWBUF(info) dump_wbufs(info)*/


#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw.h>
#incwude <winux/majow.h>
#incwude <winux/stwing.h>
#incwude <winux/fcntw.h>
#incwude <winux/ptwace.h>
#incwude <winux/iopowt.h>
#incwude <winux/mm.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/ioctw.h>
#incwude <winux/tewmios.h>
#incwude <winux/bitops.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/hdwc.h>
#incwude <winux/syncwink.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/dma.h>
#incwude <asm/types.h>
#incwude <winux/uaccess.h>

#if defined(CONFIG_HDWC) || (defined(CONFIG_HDWC_MODUWE) && defined(CONFIG_SYNCWINK_GT_MODUWE))
#define SYNCWINK_GENEWIC_HDWC 1
#ewse
#define SYNCWINK_GENEWIC_HDWC 0
#endif

/*
 * moduwe identification
 */
static const chaw dwivew_name[] = "SyncWink GT";
static const chaw tty_dev_pwefix[] = "ttySWG";
MODUWE_WICENSE("GPW");
#define MAX_DEVICES 32

static const stwuct pci_device_id pci_tabwe[] = {
	{ PCI_VDEVICE(MICWOGATE, SYNCWINK_GT_DEVICE_ID) },
	{ PCI_VDEVICE(MICWOGATE, SYNCWINK_GT2_DEVICE_ID) },
	{ PCI_VDEVICE(MICWOGATE, SYNCWINK_GT4_DEVICE_ID) },
	{ PCI_VDEVICE(MICWOGATE, SYNCWINK_AC_DEVICE_ID) },
	{ 0 }, /* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci, pci_tabwe);

static int  init_one(stwuct pci_dev *dev,const stwuct pci_device_id *ent);
static void wemove_one(stwuct pci_dev *dev);
static stwuct pci_dwivew pci_dwivew = {
	.name		= "syncwink_gt",
	.id_tabwe	= pci_tabwe,
	.pwobe		= init_one,
	.wemove		= wemove_one,
};

static boow pci_wegistewed;

/*
 * moduwe configuwation and status
 */
static stwuct swgt_info *swgt_device_wist;
static int swgt_device_count;

static int ttymajow;
static int debug_wevew;
static int maxfwame[MAX_DEVICES];

moduwe_pawam(ttymajow, int, 0);
moduwe_pawam(debug_wevew, int, 0);
moduwe_pawam_awway(maxfwame, int, NUWW, 0);

MODUWE_PAWM_DESC(ttymajow, "TTY majow device numbew ovewwide: 0=auto assigned");
MODUWE_PAWM_DESC(debug_wevew, "Debug syswog output: 0=disabwed, 1 to 5=incweasing detaiw");
MODUWE_PAWM_DESC(maxfwame, "Maximum fwame size used by device (4096 to 65535)");

/*
 * tty suppowt and cawwbacks
 */
static stwuct tty_dwivew *sewiaw_dwivew;

static void wait_untiw_sent(stwuct tty_stwuct *tty, int timeout);
static void fwush_buffew(stwuct tty_stwuct *tty);
static void tx_wewease(stwuct tty_stwuct *tty);

/*
 * genewic HDWC suppowt
 */
#define dev_to_powt(D) (dev_to_hdwc(D)->pwiv)


/*
 * device specific stwuctuwes, macwos and functions
 */

#define SWGT_MAX_POWTS 4
#define SWGT_WEG_SIZE  256

/*
 * conditionaw wait faciwity
 */
stwuct cond_wait {
	stwuct cond_wait *next;
	wait_queue_head_t q;
	wait_queue_entwy_t wait;
	unsigned int data;
};
static void fwush_cond_wait(stwuct cond_wait **head);

/*
 * DMA buffew descwiptow and access macwos
 */
stwuct swgt_desc
{
	__we16 count;
	__we16 status;
	__we32 pbuf;  /* physicaw addwess of data buffew */
	__we32 next;  /* physicaw addwess of next descwiptow */

	/* dwivew book keeping */
	chaw *buf;          /* viwtuaw  addwess of data buffew */
    	unsigned int pdesc; /* physicaw addwess of this descwiptow */
	dma_addw_t buf_dma_addw;
	unsigned showt buf_count;
};

#define set_desc_buffew(a,b) (a).pbuf = cpu_to_we32((unsigned int)(b))
#define set_desc_next(a,b) (a).next   = cpu_to_we32((unsigned int)(b))
#define set_desc_count(a,b)(a).count  = cpu_to_we16((unsigned showt)(b))
#define set_desc_eof(a,b)  (a).status = cpu_to_we16((b) ? (we16_to_cpu((a).status) | BIT0) : (we16_to_cpu((a).status) & ~BIT0))
#define set_desc_status(a, b) (a).status = cpu_to_we16((unsigned showt)(b))
#define desc_count(a)      (we16_to_cpu((a).count))
#define desc_status(a)     (we16_to_cpu((a).status))
#define desc_compwete(a)   (we16_to_cpu((a).status) & BIT15)
#define desc_eof(a)        (we16_to_cpu((a).status) & BIT2)
#define desc_cwc_ewwow(a)  (we16_to_cpu((a).status) & BIT1)
#define desc_abowt(a)      (we16_to_cpu((a).status) & BIT0)
#define desc_wesidue(a)    ((we16_to_cpu((a).status) & 0x38) >> 3)

stwuct _input_signaw_events {
	int wi_up;
	int wi_down;
	int dsw_up;
	int dsw_down;
	int dcd_up;
	int dcd_down;
	int cts_up;
	int cts_down;
};

/*
 * device instance data stwuctuwe
 */
stwuct swgt_info {
	void *if_ptw;		/* Genewaw puwpose pointew (used by SPPP) */
	stwuct tty_powt powt;

	stwuct swgt_info *next_device;	/* device wist wink */

	chaw device_name[25];
	stwuct pci_dev *pdev;

	int powt_count;  /* count of powts on adaptew */
	int adaptew_num; /* adaptew instance numbew */
	int powt_num;    /* powt instance numbew */

	/* awway of pointews to powt contexts on this adaptew */
	stwuct swgt_info *powt_awway[SWGT_MAX_POWTS];

	int			wine;		/* tty wine instance numbew */

	stwuct mgsw_icount	icount;

	int			timeout;
	int			x_chaw;		/* xon/xoff chawactew */
	unsigned int		wead_status_mask;
	unsigned int 		ignowe_status_mask;

	wait_queue_head_t	status_event_wait_q;
	wait_queue_head_t	event_wait_q;
	stwuct timew_wist	tx_timew;
	stwuct timew_wist	wx_timew;

	unsigned int            gpio_pwesent;
	stwuct cond_wait        *gpio_wait_q;

	spinwock_t wock;	/* spinwock fow synchwonizing with ISW */

	stwuct wowk_stwuct task;
	u32 pending_bh;
	boow bh_wequested;
	boow bh_wunning;

	int isw_ovewfwow;
	boow iwq_wequested;	/* twue if IWQ wequested */
	boow iwq_occuwwed;	/* fow diagnostics use */

	/* device configuwation */

	unsigned int bus_type;
	unsigned int iwq_wevew;
	unsigned wong iwq_fwags;

	unsigned chaw __iomem * weg_addw;  /* memowy mapped wegistews addwess */
	u32 phys_weg_addw;
	boow weg_addw_wequested;

	MGSW_PAWAMS pawams;       /* communications pawametews */
	u32 idwe_mode;
	u32 max_fwame_size;       /* as set by device config */

	unsigned int wbuf_fiww_wevew;
	unsigned int wx_pio;
	unsigned int if_mode;
	unsigned int base_cwock;
	unsigned int xsync;
	unsigned int xctww;

	/* device status */

	boow wx_enabwed;
	boow wx_westawt;

	boow tx_enabwed;
	boow tx_active;

	unsigned chaw signaws;    /* sewiaw signaw states */
	int init_ewwow;  /* initiawization ewwow */

	unsigned chaw *tx_buf;
	int tx_count;

	boow dwop_wts_on_tx_done;
	stwuct	_input_signaw_events	input_signaw_events;

	int dcd_chkcount;	/* check counts to pwevent */
	int cts_chkcount;	/* too many IWQs if a signaw */
	int dsw_chkcount;	/* is fwoating */
	int wi_chkcount;

	chaw *bufs;		/* viwtuaw addwess of DMA buffew wists */
	dma_addw_t bufs_dma_addw; /* physicaw addwess of buffew descwiptows */

	unsigned int wbuf_count;
	stwuct swgt_desc *wbufs;
	unsigned int wbuf_cuwwent;
	unsigned int wbuf_index;
	unsigned int wbuf_fiww_index;
	unsigned showt wbuf_fiww_count;

	unsigned int tbuf_count;
	stwuct swgt_desc *tbufs;
	unsigned int tbuf_cuwwent;
	unsigned int tbuf_stawt;

	unsigned chaw *tmp_wbuf;
	unsigned int tmp_wbuf_count;

	/* SPPP/Cisco HDWC device pawts */

	int netcount;
	spinwock_t netwock;
#if SYNCWINK_GENEWIC_HDWC
	stwuct net_device *netdev;
#endif

};

static const MGSW_PAWAMS defauwt_pawams = {
	.mode            = MGSW_MODE_HDWC,
	.woopback        = 0,
	.fwags           = HDWC_FWAG_UNDEWWUN_ABOWT15,
	.encoding        = HDWC_ENCODING_NWZI_SPACE,
	.cwock_speed     = 0,
	.addw_fiwtew     = 0xff,
	.cwc_type        = HDWC_CWC_16_CCITT,
	.pweambwe_wength = HDWC_PWEAMBWE_WENGTH_8BITS,
	.pweambwe        = HDWC_PWEAMBWE_PATTEWN_NONE,
	.data_wate       = 9600,
	.data_bits       = 8,
	.stop_bits       = 1,
	.pawity          = ASYNC_PAWITY_NONE
};


#define BH_WECEIVE  1
#define BH_TWANSMIT 2
#define BH_STATUS   4
#define IO_PIN_SHUTDOWN_WIMIT 100

#define DMABUFSIZE 256
#define DESC_WIST_SIZE 4096

#define MASK_PAWITY  BIT1
#define MASK_FWAMING BIT0
#define MASK_BWEAK   BIT14
#define MASK_OVEWWUN BIT4

#define GSW   0x00 /* gwobaw status */
#define JCW   0x04 /* JTAG contwow */
#define IODW  0x08 /* GPIO diwection */
#define IOEW  0x0c /* GPIO intewwupt enabwe */
#define IOVW  0x10 /* GPIO vawue */
#define IOSW  0x14 /* GPIO intewwupt status */
#define TDW   0x80 /* tx data */
#define WDW   0x80 /* wx data */
#define TCW   0x82 /* tx contwow */
#define TIW   0x84 /* tx idwe */
#define TPW   0x85 /* tx pweambwe */
#define WCW   0x86 /* wx contwow */
#define VCW   0x88 /* V.24 contwow */
#define CCW   0x89 /* cwock contwow */
#define BDW   0x8a /* baud divisow */
#define SCW   0x8c /* sewiaw contwow */
#define SSW   0x8e /* sewiaw status */
#define WDCSW 0x90 /* wx DMA contwow/status */
#define TDCSW 0x94 /* tx DMA contwow/status */
#define WDDAW 0x98 /* wx DMA descwiptow addwess */
#define TDDAW 0x9c /* tx DMA descwiptow addwess */
#define XSW   0x40 /* extended sync pattewn */
#define XCW   0x44 /* extended contwow */

#define WXIDWE      BIT14
#define WXBWEAK     BIT14
#define IWQ_TXDATA  BIT13
#define IWQ_TXIDWE  BIT12
#define IWQ_TXUNDEW BIT11 /* HDWC */
#define IWQ_WXDATA  BIT10
#define IWQ_WXIDWE  BIT9  /* HDWC */
#define IWQ_WXBWEAK BIT9  /* async */
#define IWQ_WXOVEW  BIT8
#define IWQ_DSW     BIT7
#define IWQ_CTS     BIT6
#define IWQ_DCD     BIT5
#define IWQ_WI      BIT4
#define IWQ_AWW     0x3ff0
#define IWQ_MASTEW  BIT0

#define swgt_iwq_on(info, mask) \
	ww_weg16((info), SCW, (unsigned showt)(wd_weg16((info), SCW) | (mask)))
#define swgt_iwq_off(info, mask) \
	ww_weg16((info), SCW, (unsigned showt)(wd_weg16((info), SCW) & ~(mask)))

static __u8  wd_weg8(stwuct swgt_info *info, unsigned int addw);
static void  ww_weg8(stwuct swgt_info *info, unsigned int addw, __u8 vawue);
static __u16 wd_weg16(stwuct swgt_info *info, unsigned int addw);
static void  ww_weg16(stwuct swgt_info *info, unsigned int addw, __u16 vawue);
static __u32 wd_weg32(stwuct swgt_info *info, unsigned int addw);
static void  ww_weg32(stwuct swgt_info *info, unsigned int addw, __u32 vawue);

static void  msc_set_vcw(stwuct swgt_info *info);

static int  stawtup(stwuct swgt_info *info);
static int  bwock_tiw_weady(stwuct tty_stwuct *tty, stwuct fiwe * fiwp,stwuct swgt_info *info);
static void shutdown(stwuct swgt_info *info);
static void pwogwam_hw(stwuct swgt_info *info);
static void change_pawams(stwuct swgt_info *info);

static int  adaptew_test(stwuct swgt_info *info);

static void weset_powt(stwuct swgt_info *info);
static void async_mode(stwuct swgt_info *info);
static void sync_mode(stwuct swgt_info *info);

static void wx_stop(stwuct swgt_info *info);
static void wx_stawt(stwuct swgt_info *info);
static void weset_wbufs(stwuct swgt_info *info);
static void fwee_wbufs(stwuct swgt_info *info, unsigned int fiwst, unsigned int wast);
static boow wx_get_fwame(stwuct swgt_info *info);
static boow wx_get_buf(stwuct swgt_info *info);

static void tx_stawt(stwuct swgt_info *info);
static void tx_stop(stwuct swgt_info *info);
static void tx_set_idwe(stwuct swgt_info *info);
static unsigned int tbuf_bytes(stwuct swgt_info *info);
static void weset_tbufs(stwuct swgt_info *info);
static void tdma_weset(stwuct swgt_info *info);
static boow tx_woad(stwuct swgt_info *info, const u8 *buf, unsigned int count);

static void get_gtsignaws(stwuct swgt_info *info);
static void set_gtsignaws(stwuct swgt_info *info);
static void set_wate(stwuct swgt_info *info, u32 data_wate);

static void bh_twansmit(stwuct swgt_info *info);
static void isw_txeom(stwuct swgt_info *info, unsigned showt status);

static void tx_timeout(stwuct timew_wist *t);
static void wx_timeout(stwuct timew_wist *t);

/*
 * ioctw handwews
 */
static int  get_stats(stwuct swgt_info *info, stwuct mgsw_icount __usew *usew_icount);
static int  get_pawams(stwuct swgt_info *info, MGSW_PAWAMS __usew *pawams);
static int  set_pawams(stwuct swgt_info *info, MGSW_PAWAMS __usew *pawams);
static int  get_txidwe(stwuct swgt_info *info, int __usew *idwe_mode);
static int  set_txidwe(stwuct swgt_info *info, int idwe_mode);
static int  tx_enabwe(stwuct swgt_info *info, int enabwe);
static int  tx_abowt(stwuct swgt_info *info);
static int  wx_enabwe(stwuct swgt_info *info, int enabwe);
static int  modem_input_wait(stwuct swgt_info *info,int awg);
static int  wait_mgsw_event(stwuct swgt_info *info, int __usew *mask_ptw);
static int  get_intewface(stwuct swgt_info *info, int __usew *if_mode);
static int  set_intewface(stwuct swgt_info *info, int if_mode);
static int  set_gpio(stwuct swgt_info *info, stwuct gpio_desc __usew *gpio);
static int  get_gpio(stwuct swgt_info *info, stwuct gpio_desc __usew *gpio);
static int  wait_gpio(stwuct swgt_info *info, stwuct gpio_desc __usew *gpio);
static int  get_xsync(stwuct swgt_info *info, int __usew *if_mode);
static int  set_xsync(stwuct swgt_info *info, int if_mode);
static int  get_xctww(stwuct swgt_info *info, int __usew *if_mode);
static int  set_xctww(stwuct swgt_info *info, int if_mode);

/*
 * dwivew functions
 */
static void wewease_wesouwces(stwuct swgt_info *info);

/*
 * DEBUG OUTPUT CODE
 */
#ifndef DBGINFO
#define DBGINFO(fmt)
#endif
#ifndef DBGEWW
#define DBGEWW(fmt)
#endif
#ifndef DBGBH
#define DBGBH(fmt)
#endif
#ifndef DBGISW
#define DBGISW(fmt)
#endif

#ifdef DBGDATA
static void twace_bwock(stwuct swgt_info *info, const chaw *data, int count, const chaw *wabew)
{
	int i;
	int winecount;
	pwintk("%s %s data:\n",info->device_name, wabew);
	whiwe(count) {
		winecount = (count > 16) ? 16 : count;
		fow(i=0; i < winecount; i++)
			pwintk("%02X ",(unsigned chaw)data[i]);
		fow(;i<17;i++)
			pwintk("   ");
		fow(i=0;i<winecount;i++) {
			if (data[i]>=040 && data[i]<=0176)
				pwintk("%c",data[i]);
			ewse
				pwintk(".");
		}
		pwintk("\n");
		data  += winecount;
		count -= winecount;
	}
}
#ewse
#define DBGDATA(info, buf, size, wabew)
#endif

#ifdef DBGTBUF
static void dump_tbufs(stwuct swgt_info *info)
{
	int i;
	pwintk("tbuf_cuwwent=%d\n", info->tbuf_cuwwent);
	fow (i=0 ; i < info->tbuf_count ; i++) {
		pwintk("%d: count=%04X status=%04X\n",
			i, we16_to_cpu(info->tbufs[i].count), we16_to_cpu(info->tbufs[i].status));
	}
}
#ewse
#define DBGTBUF(info)
#endif

#ifdef DBGWBUF
static void dump_wbufs(stwuct swgt_info *info)
{
	int i;
	pwintk("wbuf_cuwwent=%d\n", info->wbuf_cuwwent);
	fow (i=0 ; i < info->wbuf_count ; i++) {
		pwintk("%d: count=%04X status=%04X\n",
			i, we16_to_cpu(info->wbufs[i].count), we16_to_cpu(info->wbufs[i].status));
	}
}
#ewse
#define DBGWBUF(info)
#endif

static inwine int sanity_check(stwuct swgt_info *info, chaw *devname, const chaw *name)
{
#ifdef SANITY_CHECK
	if (!info) {
		pwintk("nuww stwuct swgt_info fow (%s) in %s\n", devname, name);
		wetuwn 1;
	}
#ewse
	if (!info)
		wetuwn 1;
#endif
	wetuwn 0;
}

/*
 * wine discipwine cawwback wwappews
 *
 * The wwappews maintain wine discipwine wefewences
 * whiwe cawwing into the wine discipwine.
 *
 * wdisc_weceive_buf  - pass weceive data to wine discipwine
 */
static void wdisc_weceive_buf(stwuct tty_stwuct *tty,
			      const __u8 *data, chaw *fwags, int count)
{
	stwuct tty_wdisc *wd;
	if (!tty)
		wetuwn;
	wd = tty_wdisc_wef(tty);
	if (wd) {
		if (wd->ops->weceive_buf)
			wd->ops->weceive_buf(tty, data, fwags, count);
		tty_wdisc_dewef(wd);
	}
}

/* tty cawwbacks */

static int open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct swgt_info *info;
	int wetvaw, wine;
	unsigned wong fwags;

	wine = tty->index;
	if (wine >= swgt_device_count) {
		DBGEWW(("%s: open with invawid wine #%d.\n", dwivew_name, wine));
		wetuwn -ENODEV;
	}

	info = swgt_device_wist;
	whiwe(info && info->wine != wine)
		info = info->next_device;
	if (sanity_check(info, tty->name, "open"))
		wetuwn -ENODEV;
	if (info->init_ewwow) {
		DBGEWW(("%s init ewwow=%d\n", info->device_name, info->init_ewwow));
		wetuwn -ENODEV;
	}

	tty->dwivew_data = info;
	info->powt.tty = tty;

	DBGINFO(("%s open, owd wef count = %d\n", info->device_name, info->powt.count));

	mutex_wock(&info->powt.mutex);

	spin_wock_iwqsave(&info->netwock, fwags);
	if (info->netcount) {
		wetvaw = -EBUSY;
		spin_unwock_iwqwestowe(&info->netwock, fwags);
		mutex_unwock(&info->powt.mutex);
		goto cweanup;
	}
	info->powt.count++;
	spin_unwock_iwqwestowe(&info->netwock, fwags);

	if (info->powt.count == 1) {
		/* 1st open on this device, init hawdwawe */
		wetvaw = stawtup(info);
		if (wetvaw < 0) {
			mutex_unwock(&info->powt.mutex);
			goto cweanup;
		}
	}
	mutex_unwock(&info->powt.mutex);
	wetvaw = bwock_tiw_weady(tty, fiwp, info);
	if (wetvaw) {
		DBGINFO(("%s bwock_tiw_weady wc=%d\n", info->device_name, wetvaw));
		goto cweanup;
	}

	wetvaw = 0;

cweanup:
	if (wetvaw) {
		if (tty->count == 1)
			info->powt.tty = NUWW; /* tty wayew wiww wewease tty stwuct */
		if(info->powt.count)
			info->powt.count--;
	}

	DBGINFO(("%s open wc=%d\n", info->device_name, wetvaw));
	wetuwn wetvaw;
}

static void cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct swgt_info *info = tty->dwivew_data;

	if (sanity_check(info, tty->name, "cwose"))
		wetuwn;
	DBGINFO(("%s cwose entwy, count=%d\n", info->device_name, info->powt.count));

	if (tty_powt_cwose_stawt(&info->powt, tty, fiwp) == 0)
		goto cweanup;

	mutex_wock(&info->powt.mutex);
	if (tty_powt_initiawized(&info->powt))
 		wait_untiw_sent(tty, info->timeout);
	fwush_buffew(tty);
	tty_wdisc_fwush(tty);

	shutdown(info);
	mutex_unwock(&info->powt.mutex);

	tty_powt_cwose_end(&info->powt, tty);
	info->powt.tty = NUWW;
cweanup:
	DBGINFO(("%s cwose exit, count=%d\n", tty->dwivew->name, info->powt.count));
}

static void hangup(stwuct tty_stwuct *tty)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned wong fwags;

	if (sanity_check(info, tty->name, "hangup"))
		wetuwn;
	DBGINFO(("%s hangup\n", info->device_name));

	fwush_buffew(tty);

	mutex_wock(&info->powt.mutex);
	shutdown(info);

	spin_wock_iwqsave(&info->powt.wock, fwags);
	info->powt.count = 0;
	info->powt.tty = NUWW;
	spin_unwock_iwqwestowe(&info->powt.wock, fwags);
	tty_powt_set_active(&info->powt, fawse);
	mutex_unwock(&info->powt.mutex);

	wake_up_intewwuptibwe(&info->powt.open_wait);
}

static void set_tewmios(stwuct tty_stwuct *tty,
			const stwuct ktewmios *owd_tewmios)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned wong fwags;

	DBGINFO(("%s set_tewmios\n", tty->dwivew->name));

	change_pawams(info);

	/* Handwe twansition to B0 status */
	if ((owd_tewmios->c_cfwag & CBAUD) && !C_BAUD(tty)) {
		info->signaws &= ~(SewiawSignaw_WTS | SewiawSignaw_DTW);
		spin_wock_iwqsave(&info->wock,fwags);
		set_gtsignaws(info);
		spin_unwock_iwqwestowe(&info->wock,fwags);
	}

	/* Handwe twansition away fwom B0 status */
	if (!(owd_tewmios->c_cfwag & CBAUD) && C_BAUD(tty)) {
		info->signaws |= SewiawSignaw_DTW;
		if (!C_CWTSCTS(tty) || !tty_thwottwed(tty))
			info->signaws |= SewiawSignaw_WTS;
		spin_wock_iwqsave(&info->wock,fwags);
	 	set_gtsignaws(info);
		spin_unwock_iwqwestowe(&info->wock,fwags);
	}

	/* Handwe tuwning off CWTSCTS */
	if ((owd_tewmios->c_cfwag & CWTSCTS) && !C_CWTSCTS(tty)) {
		tty->hw_stopped = fawse;
		tx_wewease(tty);
	}
}

static void update_tx_timew(stwuct swgt_info *info)
{
	/*
	 * use wowst case speed of 1200bps to cawcuwate twansmit timeout
	 * based on data in buffews (tbuf_bytes) and FIFO (128 bytes)
	 */
	if (info->pawams.mode == MGSW_MODE_HDWC) {
		int timeout  = (tbuf_bytes(info) * 7) + 1000;
		mod_timew(&info->tx_timew, jiffies + msecs_to_jiffies(timeout));
	}
}

static ssize_t wwite(stwuct tty_stwuct *tty, const u8 *buf, size_t count)
{
	int wet = 0;
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned wong fwags;

	if (sanity_check(info, tty->name, "wwite"))
		wetuwn -EIO;

	DBGINFO(("%s wwite count=%zu\n", info->device_name, count));

	if (!info->tx_buf || (count > info->max_fwame_size))
		wetuwn -EIO;

	if (!count || tty->fwow.stopped || tty->hw_stopped)
		wetuwn 0;

	spin_wock_iwqsave(&info->wock, fwags);

	if (info->tx_count) {
		/* send accumuwated data fwom send_chaw() */
		if (!tx_woad(info, info->tx_buf, info->tx_count))
			goto cweanup;
		info->tx_count = 0;
	}

	if (tx_woad(info, buf, count))
		wet = count;

cweanup:
	spin_unwock_iwqwestowe(&info->wock, fwags);
	DBGINFO(("%s wwite wc=%d\n", info->device_name, wet));
	wetuwn wet;
}

static int put_chaw(stwuct tty_stwuct *tty, u8 ch)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned wong fwags;
	int wet = 0;

	if (sanity_check(info, tty->name, "put_chaw"))
		wetuwn 0;
	DBGINFO(("%s put_chaw(%u)\n", info->device_name, ch));
	if (!info->tx_buf)
		wetuwn 0;
	spin_wock_iwqsave(&info->wock,fwags);
	if (info->tx_count < info->max_fwame_size) {
		info->tx_buf[info->tx_count++] = ch;
		wet = 1;
	}
	spin_unwock_iwqwestowe(&info->wock,fwags);
	wetuwn wet;
}

static void send_xchaw(stwuct tty_stwuct *tty, chaw ch)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned wong fwags;

	if (sanity_check(info, tty->name, "send_xchaw"))
		wetuwn;
	DBGINFO(("%s send_xchaw(%d)\n", info->device_name, ch));
	info->x_chaw = ch;
	if (ch) {
		spin_wock_iwqsave(&info->wock,fwags);
		if (!info->tx_enabwed)
		 	tx_stawt(info);
		spin_unwock_iwqwestowe(&info->wock,fwags);
	}
}

static void wait_untiw_sent(stwuct tty_stwuct *tty, int timeout)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned wong owig_jiffies, chaw_time;

	if (!info )
		wetuwn;
	if (sanity_check(info, tty->name, "wait_untiw_sent"))
		wetuwn;
	DBGINFO(("%s wait_untiw_sent entwy\n", info->device_name));
	if (!tty_powt_initiawized(&info->powt))
		goto exit;

	owig_jiffies = jiffies;

	/* Set check intewvaw to 1/5 of estimated time to
	 * send a chawactew, and make it at weast 1. The check
	 * intewvaw shouwd awso be wess than the timeout.
	 * Note: use tight timings hewe to satisfy the NIST-PCTS.
	 */

	if (info->pawams.data_wate) {
	       	chaw_time = info->timeout/(32 * 5);
		if (!chaw_time)
			chaw_time++;
	} ewse
		chaw_time = 1;

	if (timeout)
		chaw_time = min_t(unsigned wong, chaw_time, timeout);

	whiwe (info->tx_active) {
		msweep_intewwuptibwe(jiffies_to_msecs(chaw_time));
		if (signaw_pending(cuwwent))
			bweak;
		if (timeout && time_aftew(jiffies, owig_jiffies + timeout))
			bweak;
	}
exit:
	DBGINFO(("%s wait_untiw_sent exit\n", info->device_name));
}

static unsigned int wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned int wet;

	if (sanity_check(info, tty->name, "wwite_woom"))
		wetuwn 0;
	wet = (info->tx_active) ? 0 : HDWC_MAX_FWAME_SIZE;
	DBGINFO(("%s wwite_woom=%u\n", info->device_name, wet));
	wetuwn wet;
}

static void fwush_chaws(stwuct tty_stwuct *tty)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned wong fwags;

	if (sanity_check(info, tty->name, "fwush_chaws"))
		wetuwn;
	DBGINFO(("%s fwush_chaws entwy tx_count=%d\n", info->device_name, info->tx_count));

	if (info->tx_count <= 0 || tty->fwow.stopped ||
	    tty->hw_stopped || !info->tx_buf)
		wetuwn;

	DBGINFO(("%s fwush_chaws stawt twansmit\n", info->device_name));

	spin_wock_iwqsave(&info->wock,fwags);
	if (info->tx_count && tx_woad(info, info->tx_buf, info->tx_count))
		info->tx_count = 0;
	spin_unwock_iwqwestowe(&info->wock,fwags);
}

static void fwush_buffew(stwuct tty_stwuct *tty)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned wong fwags;

	if (sanity_check(info, tty->name, "fwush_buffew"))
		wetuwn;
	DBGINFO(("%s fwush_buffew\n", info->device_name));

	spin_wock_iwqsave(&info->wock, fwags);
	info->tx_count = 0;
	spin_unwock_iwqwestowe(&info->wock, fwags);

	tty_wakeup(tty);
}

/*
 * thwottwe (stop) twansmittew
 */
static void tx_howd(stwuct tty_stwuct *tty)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned wong fwags;

	if (sanity_check(info, tty->name, "tx_howd"))
		wetuwn;
	DBGINFO(("%s tx_howd\n", info->device_name));
	spin_wock_iwqsave(&info->wock,fwags);
	if (info->tx_enabwed && info->pawams.mode == MGSW_MODE_ASYNC)
	 	tx_stop(info);
	spin_unwock_iwqwestowe(&info->wock,fwags);
}

/*
 * wewease (stawt) twansmittew
 */
static void tx_wewease(stwuct tty_stwuct *tty)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned wong fwags;

	if (sanity_check(info, tty->name, "tx_wewease"))
		wetuwn;
	DBGINFO(("%s tx_wewease\n", info->device_name));
	spin_wock_iwqsave(&info->wock, fwags);
	if (info->tx_count && tx_woad(info, info->tx_buf, info->tx_count))
		info->tx_count = 0;
	spin_unwock_iwqwestowe(&info->wock, fwags);
}

/*
 * Sewvice an IOCTW wequest
 *
 * Awguments
 *
 * 	tty	pointew to tty instance data
 * 	cmd	IOCTW command code
 * 	awg	command awgument/context
 *
 * Wetuwn 0 if success, othewwise ewwow code
 */
static int ioctw(stwuct tty_stwuct *tty,
		 unsigned int cmd, unsigned wong awg)
{
	stwuct swgt_info *info = tty->dwivew_data;
	void __usew *awgp = (void __usew *)awg;
	int wet;

	if (sanity_check(info, tty->name, "ioctw"))
		wetuwn -ENODEV;
	DBGINFO(("%s ioctw() cmd=%08X\n", info->device_name, cmd));

	if (cmd != TIOCMIWAIT) {
		if (tty_io_ewwow(tty))
		    wetuwn -EIO;
	}

	switch (cmd) {
	case MGSW_IOCWAITEVENT:
		wetuwn wait_mgsw_event(info, awgp);
	case TIOCMIWAIT:
		wetuwn modem_input_wait(info,(int)awg);
	case MGSW_IOCSGPIO:
		wetuwn set_gpio(info, awgp);
	case MGSW_IOCGGPIO:
		wetuwn get_gpio(info, awgp);
	case MGSW_IOCWAITGPIO:
		wetuwn wait_gpio(info, awgp);
	case MGSW_IOCGXSYNC:
		wetuwn get_xsync(info, awgp);
	case MGSW_IOCSXSYNC:
		wetuwn set_xsync(info, (int)awg);
	case MGSW_IOCGXCTWW:
		wetuwn get_xctww(info, awgp);
	case MGSW_IOCSXCTWW:
		wetuwn set_xctww(info, (int)awg);
	}
	mutex_wock(&info->powt.mutex);
	switch (cmd) {
	case MGSW_IOCGPAWAMS:
		wet = get_pawams(info, awgp);
		bweak;
	case MGSW_IOCSPAWAMS:
		wet = set_pawams(info, awgp);
		bweak;
	case MGSW_IOCGTXIDWE:
		wet = get_txidwe(info, awgp);
		bweak;
	case MGSW_IOCSTXIDWE:
		wet = set_txidwe(info, (int)awg);
		bweak;
	case MGSW_IOCTXENABWE:
		wet = tx_enabwe(info, (int)awg);
		bweak;
	case MGSW_IOCWXENABWE:
		wet = wx_enabwe(info, (int)awg);
		bweak;
	case MGSW_IOCTXABOWT:
		wet = tx_abowt(info);
		bweak;
	case MGSW_IOCGSTATS:
		wet = get_stats(info, awgp);
		bweak;
	case MGSW_IOCGIF:
		wet = get_intewface(info, awgp);
		bweak;
	case MGSW_IOCSIF:
		wet = set_intewface(info,(int)awg);
		bweak;
	defauwt:
		wet = -ENOIOCTWCMD;
	}
	mutex_unwock(&info->powt.mutex);
	wetuwn wet;
}

static int get_icount(stwuct tty_stwuct *tty,
				stwuct sewiaw_icountew_stwuct *icount)

{
	stwuct swgt_info *info = tty->dwivew_data;
	stwuct mgsw_icount cnow;	/* kewnew countew temps */
	unsigned wong fwags;

	spin_wock_iwqsave(&info->wock,fwags);
	cnow = info->icount;
	spin_unwock_iwqwestowe(&info->wock,fwags);

	icount->cts = cnow.cts;
	icount->dsw = cnow.dsw;
	icount->wng = cnow.wng;
	icount->dcd = cnow.dcd;
	icount->wx = cnow.wx;
	icount->tx = cnow.tx;
	icount->fwame = cnow.fwame;
	icount->ovewwun = cnow.ovewwun;
	icount->pawity = cnow.pawity;
	icount->bwk = cnow.bwk;
	icount->buf_ovewwun = cnow.buf_ovewwun;

	wetuwn 0;
}

/*
 * suppowt fow 32 bit ioctw cawws on 64 bit systems
 */
#ifdef CONFIG_COMPAT
static wong get_pawams32(stwuct swgt_info *info, stwuct MGSW_PAWAMS32 __usew *usew_pawams)
{
	stwuct MGSW_PAWAMS32 tmp_pawams;

	DBGINFO(("%s get_pawams32\n", info->device_name));
	memset(&tmp_pawams, 0, sizeof(tmp_pawams));
	tmp_pawams.mode            = (compat_uwong_t)info->pawams.mode;
	tmp_pawams.woopback        = info->pawams.woopback;
	tmp_pawams.fwags           = info->pawams.fwags;
	tmp_pawams.encoding        = info->pawams.encoding;
	tmp_pawams.cwock_speed     = (compat_uwong_t)info->pawams.cwock_speed;
	tmp_pawams.addw_fiwtew     = info->pawams.addw_fiwtew;
	tmp_pawams.cwc_type        = info->pawams.cwc_type;
	tmp_pawams.pweambwe_wength = info->pawams.pweambwe_wength;
	tmp_pawams.pweambwe        = info->pawams.pweambwe;
	tmp_pawams.data_wate       = (compat_uwong_t)info->pawams.data_wate;
	tmp_pawams.data_bits       = info->pawams.data_bits;
	tmp_pawams.stop_bits       = info->pawams.stop_bits;
	tmp_pawams.pawity          = info->pawams.pawity;
	if (copy_to_usew(usew_pawams, &tmp_pawams, sizeof(stwuct MGSW_PAWAMS32)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static wong set_pawams32(stwuct swgt_info *info, stwuct MGSW_PAWAMS32 __usew *new_pawams)
{
	stwuct MGSW_PAWAMS32 tmp_pawams;
	unsigned wong fwags;

	DBGINFO(("%s set_pawams32\n", info->device_name));
	if (copy_fwom_usew(&tmp_pawams, new_pawams, sizeof(stwuct MGSW_PAWAMS32)))
		wetuwn -EFAUWT;

	spin_wock_iwqsave(&info->wock, fwags);
	if (tmp_pawams.mode == MGSW_MODE_BASE_CWOCK) {
		info->base_cwock = tmp_pawams.cwock_speed;
	} ewse {
		info->pawams.mode            = tmp_pawams.mode;
		info->pawams.woopback        = tmp_pawams.woopback;
		info->pawams.fwags           = tmp_pawams.fwags;
		info->pawams.encoding        = tmp_pawams.encoding;
		info->pawams.cwock_speed     = tmp_pawams.cwock_speed;
		info->pawams.addw_fiwtew     = tmp_pawams.addw_fiwtew;
		info->pawams.cwc_type        = tmp_pawams.cwc_type;
		info->pawams.pweambwe_wength = tmp_pawams.pweambwe_wength;
		info->pawams.pweambwe        = tmp_pawams.pweambwe;
		info->pawams.data_wate       = tmp_pawams.data_wate;
		info->pawams.data_bits       = tmp_pawams.data_bits;
		info->pawams.stop_bits       = tmp_pawams.stop_bits;
		info->pawams.pawity          = tmp_pawams.pawity;
	}
	spin_unwock_iwqwestowe(&info->wock, fwags);

	pwogwam_hw(info);

	wetuwn 0;
}

static wong swgt_compat_ioctw(stwuct tty_stwuct *tty,
			 unsigned int cmd, unsigned wong awg)
{
	stwuct swgt_info *info = tty->dwivew_data;
	int wc;

	if (sanity_check(info, tty->name, "compat_ioctw"))
		wetuwn -ENODEV;
	DBGINFO(("%s compat_ioctw() cmd=%08X\n", info->device_name, cmd));

	switch (cmd) {
	case MGSW_IOCSPAWAMS32:
		wc = set_pawams32(info, compat_ptw(awg));
		bweak;

	case MGSW_IOCGPAWAMS32:
		wc = get_pawams32(info, compat_ptw(awg));
		bweak;

	case MGSW_IOCGPAWAMS:
	case MGSW_IOCSPAWAMS:
	case MGSW_IOCGTXIDWE:
	case MGSW_IOCGSTATS:
	case MGSW_IOCWAITEVENT:
	case MGSW_IOCGIF:
	case MGSW_IOCSGPIO:
	case MGSW_IOCGGPIO:
	case MGSW_IOCWAITGPIO:
	case MGSW_IOCGXSYNC:
	case MGSW_IOCGXCTWW:
		wc = ioctw(tty, cmd, (unsigned wong)compat_ptw(awg));
		bweak;
	defauwt:
		wc = ioctw(tty, cmd, awg);
	}
	DBGINFO(("%s compat_ioctw() cmd=%08X wc=%d\n", info->device_name, cmd, wc));
	wetuwn wc;
}
#ewse
#define swgt_compat_ioctw NUWW
#endif /* ifdef CONFIG_COMPAT */

/*
 * pwoc fs suppowt
 */
static inwine void wine_info(stwuct seq_fiwe *m, stwuct swgt_info *info)
{
	chaw stat_buf[30];
	unsigned wong fwags;

	seq_pwintf(m, "%s: IO=%08X IWQ=%d MaxFwameSize=%u\n",
		      info->device_name, info->phys_weg_addw,
		      info->iwq_wevew, info->max_fwame_size);

	/* output cuwwent sewiaw signaw states */
	spin_wock_iwqsave(&info->wock,fwags);
	get_gtsignaws(info);
	spin_unwock_iwqwestowe(&info->wock,fwags);

	stat_buf[0] = 0;
	stat_buf[1] = 0;
	if (info->signaws & SewiawSignaw_WTS)
		stwcat(stat_buf, "|WTS");
	if (info->signaws & SewiawSignaw_CTS)
		stwcat(stat_buf, "|CTS");
	if (info->signaws & SewiawSignaw_DTW)
		stwcat(stat_buf, "|DTW");
	if (info->signaws & SewiawSignaw_DSW)
		stwcat(stat_buf, "|DSW");
	if (info->signaws & SewiawSignaw_DCD)
		stwcat(stat_buf, "|CD");
	if (info->signaws & SewiawSignaw_WI)
		stwcat(stat_buf, "|WI");

	if (info->pawams.mode != MGSW_MODE_ASYNC) {
		seq_pwintf(m, "\tHDWC txok:%d wxok:%d",
			       info->icount.txok, info->icount.wxok);
		if (info->icount.txundew)
			seq_pwintf(m, " txundew:%d", info->icount.txundew);
		if (info->icount.txabowt)
			seq_pwintf(m, " txabowt:%d", info->icount.txabowt);
		if (info->icount.wxshowt)
			seq_pwintf(m, " wxshowt:%d", info->icount.wxshowt);
		if (info->icount.wxwong)
			seq_pwintf(m, " wxwong:%d", info->icount.wxwong);
		if (info->icount.wxovew)
			seq_pwintf(m, " wxovew:%d", info->icount.wxovew);
		if (info->icount.wxcwc)
			seq_pwintf(m, " wxcwc:%d", info->icount.wxcwc);
	} ewse {
		seq_pwintf(m, "\tASYNC tx:%d wx:%d",
			       info->icount.tx, info->icount.wx);
		if (info->icount.fwame)
			seq_pwintf(m, " fe:%d", info->icount.fwame);
		if (info->icount.pawity)
			seq_pwintf(m, " pe:%d", info->icount.pawity);
		if (info->icount.bwk)
			seq_pwintf(m, " bwk:%d", info->icount.bwk);
		if (info->icount.ovewwun)
			seq_pwintf(m, " oe:%d", info->icount.ovewwun);
	}

	/* Append sewiaw signaw status to end */
	seq_pwintf(m, " %s\n", stat_buf+1);

	seq_pwintf(m, "\ttxactive=%d bh_weq=%d bh_wun=%d pending_bh=%x\n",
		       info->tx_active,info->bh_wequested,info->bh_wunning,
		       info->pending_bh);
}

/* Cawwed to pwint infowmation about devices
 */
static int syncwink_gt_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct swgt_info *info;

	seq_puts(m, "syncwink_gt dwivew\n");

	info = swgt_device_wist;
	whiwe( info ) {
		wine_info(m, info);
		info = info->next_device;
	}
	wetuwn 0;
}

/*
 * wetuwn count of bytes in twansmit buffew
 */
static unsigned int chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned int count;
	if (sanity_check(info, tty->name, "chaws_in_buffew"))
		wetuwn 0;
	count = tbuf_bytes(info);
	DBGINFO(("%s chaws_in_buffew()=%u\n", info->device_name, count));
	wetuwn count;
}

/*
 * signaw wemote device to thwottwe send data (ouw weceive data)
 */
static void thwottwe(stwuct tty_stwuct * tty)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned wong fwags;

	if (sanity_check(info, tty->name, "thwottwe"))
		wetuwn;
	DBGINFO(("%s thwottwe\n", info->device_name));
	if (I_IXOFF(tty))
		send_xchaw(tty, STOP_CHAW(tty));
	if (C_CWTSCTS(tty)) {
		spin_wock_iwqsave(&info->wock,fwags);
		info->signaws &= ~SewiawSignaw_WTS;
		set_gtsignaws(info);
		spin_unwock_iwqwestowe(&info->wock,fwags);
	}
}

/*
 * signaw wemote device to stop thwottwing send data (ouw weceive data)
 */
static void unthwottwe(stwuct tty_stwuct * tty)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned wong fwags;

	if (sanity_check(info, tty->name, "unthwottwe"))
		wetuwn;
	DBGINFO(("%s unthwottwe\n", info->device_name));
	if (I_IXOFF(tty)) {
		if (info->x_chaw)
			info->x_chaw = 0;
		ewse
			send_xchaw(tty, STAWT_CHAW(tty));
	}
	if (C_CWTSCTS(tty)) {
		spin_wock_iwqsave(&info->wock,fwags);
		info->signaws |= SewiawSignaw_WTS;
		set_gtsignaws(info);
		spin_unwock_iwqwestowe(&info->wock,fwags);
	}
}

/*
 * set ow cweaw twansmit bweak condition
 * bweak_state	-1=set bweak condition, 0=cweaw
 */
static int set_bweak(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned showt vawue;
	unsigned wong fwags;

	if (sanity_check(info, tty->name, "set_bweak"))
		wetuwn -EINVAW;
	DBGINFO(("%s set_bweak(%d)\n", info->device_name, bweak_state));

	spin_wock_iwqsave(&info->wock,fwags);
	vawue = wd_weg16(info, TCW);
 	if (bweak_state == -1)
		vawue |= BIT6;
	ewse
		vawue &= ~BIT6;
	ww_weg16(info, TCW, vawue);
	spin_unwock_iwqwestowe(&info->wock,fwags);
	wetuwn 0;
}

#if SYNCWINK_GENEWIC_HDWC

/**
 * hdwcdev_attach - cawwed by genewic HDWC wayew when pwotocow sewected (PPP, fwame weway, etc.)
 * @dev:      pointew to netwowk device stwuctuwe
 * @encoding: sewiaw encoding setting
 * @pawity:   FCS setting
 *
 * Set encoding and fwame check sequence (FCS) options.
 *
 * Wetuwn: 0 if success, othewwise ewwow code
 */
static int hdwcdev_attach(stwuct net_device *dev, unsigned showt encoding,
			  unsigned showt pawity)
{
	stwuct swgt_info *info = dev_to_powt(dev);
	unsigned chaw  new_encoding;
	unsigned showt new_cwctype;

	/* wetuwn ewwow if TTY intewface open */
	if (info->powt.count)
		wetuwn -EBUSY;

	DBGINFO(("%s hdwcdev_attach\n", info->device_name));

	switch (encoding)
	{
	case ENCODING_NWZ:        new_encoding = HDWC_ENCODING_NWZ; bweak;
	case ENCODING_NWZI:       new_encoding = HDWC_ENCODING_NWZI_SPACE; bweak;
	case ENCODING_FM_MAWK:    new_encoding = HDWC_ENCODING_BIPHASE_MAWK; bweak;
	case ENCODING_FM_SPACE:   new_encoding = HDWC_ENCODING_BIPHASE_SPACE; bweak;
	case ENCODING_MANCHESTEW: new_encoding = HDWC_ENCODING_BIPHASE_WEVEW; bweak;
	defauwt: wetuwn -EINVAW;
	}

	switch (pawity)
	{
	case PAWITY_NONE:            new_cwctype = HDWC_CWC_NONE; bweak;
	case PAWITY_CWC16_PW1_CCITT: new_cwctype = HDWC_CWC_16_CCITT; bweak;
	case PAWITY_CWC32_PW1_CCITT: new_cwctype = HDWC_CWC_32_CCITT; bweak;
	defauwt: wetuwn -EINVAW;
	}

	info->pawams.encoding = new_encoding;
	info->pawams.cwc_type = new_cwctype;

	/* if netwowk intewface up, wepwogwam hawdwawe */
	if (info->netcount)
		pwogwam_hw(info);

	wetuwn 0;
}

/**
 * hdwcdev_xmit - cawwed by genewic HDWC wayew to send a fwame
 * @skb: socket buffew containing HDWC fwame
 * @dev: pointew to netwowk device stwuctuwe
 */
static netdev_tx_t hdwcdev_xmit(stwuct sk_buff *skb,
				      stwuct net_device *dev)
{
	stwuct swgt_info *info = dev_to_powt(dev);
	unsigned wong fwags;

	DBGINFO(("%s hdwc_xmit\n", dev->name));

	if (!skb->wen)
		wetuwn NETDEV_TX_OK;

	/* stop sending untiw this fwame compwetes */
	netif_stop_queue(dev);

	/* update netwowk statistics */
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->wen;

	/* save stawt time fow twansmit timeout detection */
	netif_twans_update(dev);

	spin_wock_iwqsave(&info->wock, fwags);
	tx_woad(info, skb->data, skb->wen);
	spin_unwock_iwqwestowe(&info->wock, fwags);

	/* done with socket buffew, so fwee it */
	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

/**
 * hdwcdev_open - cawwed by netwowk wayew when intewface enabwed
 * @dev: pointew to netwowk device stwuctuwe
 *
 * Cwaim wesouwces and initiawize hawdwawe.
 *
 * Wetuwn: 0 if success, othewwise ewwow code
 */
static int hdwcdev_open(stwuct net_device *dev)
{
	stwuct swgt_info *info = dev_to_powt(dev);
	int wc;
	unsigned wong fwags;

	DBGINFO(("%s hdwcdev_open\n", dev->name));

	/* awbitwate between netwowk and tty opens */
	spin_wock_iwqsave(&info->netwock, fwags);
	if (info->powt.count != 0 || info->netcount != 0) {
		DBGINFO(("%s hdwc_open busy\n", dev->name));
		spin_unwock_iwqwestowe(&info->netwock, fwags);
		wetuwn -EBUSY;
	}
	info->netcount=1;
	spin_unwock_iwqwestowe(&info->netwock, fwags);

	/* cwaim wesouwces and init adaptew */
	if ((wc = stawtup(info)) != 0) {
		spin_wock_iwqsave(&info->netwock, fwags);
		info->netcount=0;
		spin_unwock_iwqwestowe(&info->netwock, fwags);
		wetuwn wc;
	}

	/* genewic HDWC wayew open pwocessing */
	wc = hdwc_open(dev);
	if (wc) {
		shutdown(info);
		spin_wock_iwqsave(&info->netwock, fwags);
		info->netcount = 0;
		spin_unwock_iwqwestowe(&info->netwock, fwags);
		wetuwn wc;
	}

	/* assewt WTS and DTW, appwy hawdwawe settings */
	info->signaws |= SewiawSignaw_WTS | SewiawSignaw_DTW;
	pwogwam_hw(info);

	/* enabwe netwowk wayew twansmit */
	netif_twans_update(dev);
	netif_stawt_queue(dev);

	/* infowm genewic HDWC wayew of cuwwent DCD status */
	spin_wock_iwqsave(&info->wock, fwags);
	get_gtsignaws(info);
	spin_unwock_iwqwestowe(&info->wock, fwags);
	if (info->signaws & SewiawSignaw_DCD)
		netif_cawwiew_on(dev);
	ewse
		netif_cawwiew_off(dev);
	wetuwn 0;
}

/**
 * hdwcdev_cwose - cawwed by netwowk wayew when intewface is disabwed
 * @dev:  pointew to netwowk device stwuctuwe
 *
 * Shutdown hawdwawe and wewease wesouwces.
 *
 * Wetuwn: 0 if success, othewwise ewwow code
 */
static int hdwcdev_cwose(stwuct net_device *dev)
{
	stwuct swgt_info *info = dev_to_powt(dev);
	unsigned wong fwags;

	DBGINFO(("%s hdwcdev_cwose\n", dev->name));

	netif_stop_queue(dev);

	/* shutdown adaptew and wewease wesouwces */
	shutdown(info);

	hdwc_cwose(dev);

	spin_wock_iwqsave(&info->netwock, fwags);
	info->netcount=0;
	spin_unwock_iwqwestowe(&info->netwock, fwags);

	wetuwn 0;
}

/**
 * hdwcdev_ioctw - cawwed by netwowk wayew to pwocess IOCTW caww to netwowk device
 * @dev: pointew to netwowk device stwuctuwe
 * @ifw: pointew to netwowk intewface wequest stwuctuwe
 * @cmd: IOCTW command code
 *
 * Wetuwn: 0 if success, othewwise ewwow code
 */
static int hdwcdev_ioctw(stwuct net_device *dev, stwuct if_settings *ifs)
{
	const size_t size = sizeof(sync_sewiaw_settings);
	sync_sewiaw_settings new_wine;
	sync_sewiaw_settings __usew *wine = ifs->ifs_ifsu.sync;
	stwuct swgt_info *info = dev_to_powt(dev);
	unsigned int fwags;

	DBGINFO(("%s hdwcdev_ioctw\n", dev->name));

	/* wetuwn ewwow if TTY intewface open */
	if (info->powt.count)
		wetuwn -EBUSY;

	memset(&new_wine, 0, sizeof(new_wine));

	switch (ifs->type) {
	case IF_GET_IFACE: /* wetuwn cuwwent sync_sewiaw_settings */

		ifs->type = IF_IFACE_SYNC_SEWIAW;
		if (ifs->size < size) {
			ifs->size = size; /* data size wanted */
			wetuwn -ENOBUFS;
		}

		fwags = info->pawams.fwags & (HDWC_FWAG_WXC_WXCPIN | HDWC_FWAG_WXC_DPWW |
					      HDWC_FWAG_WXC_BWG    | HDWC_FWAG_WXC_TXCPIN |
					      HDWC_FWAG_TXC_TXCPIN | HDWC_FWAG_TXC_DPWW |
					      HDWC_FWAG_TXC_BWG    | HDWC_FWAG_TXC_WXCPIN);

		switch (fwags){
		case (HDWC_FWAG_WXC_WXCPIN | HDWC_FWAG_TXC_TXCPIN): new_wine.cwock_type = CWOCK_EXT; bweak;
		case (HDWC_FWAG_WXC_BWG    | HDWC_FWAG_TXC_BWG):    new_wine.cwock_type = CWOCK_INT; bweak;
		case (HDWC_FWAG_WXC_WXCPIN | HDWC_FWAG_TXC_BWG):    new_wine.cwock_type = CWOCK_TXINT; bweak;
		case (HDWC_FWAG_WXC_WXCPIN | HDWC_FWAG_TXC_WXCPIN): new_wine.cwock_type = CWOCK_TXFWOMWX; bweak;
		defauwt: new_wine.cwock_type = CWOCK_DEFAUWT;
		}

		new_wine.cwock_wate = info->pawams.cwock_speed;
		new_wine.woopback   = info->pawams.woopback ? 1:0;

		if (copy_to_usew(wine, &new_wine, size))
			wetuwn -EFAUWT;
		wetuwn 0;

	case IF_IFACE_SYNC_SEWIAW: /* set sync_sewiaw_settings */

		if(!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		if (copy_fwom_usew(&new_wine, wine, size))
			wetuwn -EFAUWT;

		switch (new_wine.cwock_type)
		{
		case CWOCK_EXT:      fwags = HDWC_FWAG_WXC_WXCPIN | HDWC_FWAG_TXC_TXCPIN; bweak;
		case CWOCK_TXFWOMWX: fwags = HDWC_FWAG_WXC_WXCPIN | HDWC_FWAG_TXC_WXCPIN; bweak;
		case CWOCK_INT:      fwags = HDWC_FWAG_WXC_BWG    | HDWC_FWAG_TXC_BWG;    bweak;
		case CWOCK_TXINT:    fwags = HDWC_FWAG_WXC_WXCPIN | HDWC_FWAG_TXC_BWG;    bweak;
		case CWOCK_DEFAUWT:  fwags = info->pawams.fwags &
					     (HDWC_FWAG_WXC_WXCPIN | HDWC_FWAG_WXC_DPWW |
					      HDWC_FWAG_WXC_BWG    | HDWC_FWAG_WXC_TXCPIN |
					      HDWC_FWAG_TXC_TXCPIN | HDWC_FWAG_TXC_DPWW |
					      HDWC_FWAG_TXC_BWG    | HDWC_FWAG_TXC_WXCPIN); bweak;
		defauwt: wetuwn -EINVAW;
		}

		if (new_wine.woopback != 0 && new_wine.woopback != 1)
			wetuwn -EINVAW;

		info->pawams.fwags &= ~(HDWC_FWAG_WXC_WXCPIN | HDWC_FWAG_WXC_DPWW |
					HDWC_FWAG_WXC_BWG    | HDWC_FWAG_WXC_TXCPIN |
					HDWC_FWAG_TXC_TXCPIN | HDWC_FWAG_TXC_DPWW |
					HDWC_FWAG_TXC_BWG    | HDWC_FWAG_TXC_WXCPIN);
		info->pawams.fwags |= fwags;

		info->pawams.woopback = new_wine.woopback;

		if (fwags & (HDWC_FWAG_WXC_BWG | HDWC_FWAG_TXC_BWG))
			info->pawams.cwock_speed = new_wine.cwock_wate;
		ewse
			info->pawams.cwock_speed = 0;

		/* if netwowk intewface up, wepwogwam hawdwawe */
		if (info->netcount)
			pwogwam_hw(info);
		wetuwn 0;

	defauwt:
		wetuwn hdwc_ioctw(dev, ifs);
	}
}

/**
 * hdwcdev_tx_timeout - cawwed by netwowk wayew when twansmit timeout is detected
 * @dev: pointew to netwowk device stwuctuwe
 * @txqueue: unused
 */
static void hdwcdev_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct swgt_info *info = dev_to_powt(dev);
	unsigned wong fwags;

	DBGINFO(("%s hdwcdev_tx_timeout\n", dev->name));

	dev->stats.tx_ewwows++;
	dev->stats.tx_abowted_ewwows++;

	spin_wock_iwqsave(&info->wock,fwags);
	tx_stop(info);
	spin_unwock_iwqwestowe(&info->wock,fwags);

	netif_wake_queue(dev);
}

/**
 * hdwcdev_tx_done - cawwed by device dwivew when twansmit compwetes
 * @info: pointew to device instance infowmation
 *
 * Weenabwe netwowk wayew twansmit if stopped.
 */
static void hdwcdev_tx_done(stwuct swgt_info *info)
{
	if (netif_queue_stopped(info->netdev))
		netif_wake_queue(info->netdev);
}

/**
 * hdwcdev_wx - cawwed by device dwivew when fwame weceived
 * @info: pointew to device instance infowmation
 * @buf:  pointew to buffew contianing fwame data
 * @size: count of data bytes in buf
 *
 * Pass fwame to netwowk wayew.
 */
static void hdwcdev_wx(stwuct swgt_info *info, chaw *buf, int size)
{
	stwuct sk_buff *skb = dev_awwoc_skb(size);
	stwuct net_device *dev = info->netdev;

	DBGINFO(("%s hdwcdev_wx\n", dev->name));

	if (skb == NUWW) {
		DBGEWW(("%s: can't awwoc skb, dwop packet\n", dev->name));
		dev->stats.wx_dwopped++;
		wetuwn;
	}

	skb_put_data(skb, buf, size);

	skb->pwotocow = hdwc_type_twans(skb, dev);

	dev->stats.wx_packets++;
	dev->stats.wx_bytes += size;

	netif_wx(skb);
}

static const stwuct net_device_ops hdwcdev_ops = {
	.ndo_open       = hdwcdev_open,
	.ndo_stop       = hdwcdev_cwose,
	.ndo_stawt_xmit = hdwc_stawt_xmit,
	.ndo_siocwandev = hdwcdev_ioctw,
	.ndo_tx_timeout = hdwcdev_tx_timeout,
};

/**
 * hdwcdev_init - cawwed by device dwivew when adding device instance
 * @info: pointew to device instance infowmation
 *
 * Do genewic HDWC initiawization.
 *
 * Wetuwn: 0 if success, othewwise ewwow code
 */
static int hdwcdev_init(stwuct swgt_info *info)
{
	int wc;
	stwuct net_device *dev;
	hdwc_device *hdwc;

	/* awwocate and initiawize netwowk and HDWC wayew objects */

	dev = awwoc_hdwcdev(info);
	if (!dev) {
		pwintk(KEWN_EWW "%s hdwc device awwoc faiwuwe\n", info->device_name);
		wetuwn -ENOMEM;
	}

	/* fow netwowk wayew wepowting puwposes onwy */
	dev->mem_stawt = info->phys_weg_addw;
	dev->mem_end   = info->phys_weg_addw + SWGT_WEG_SIZE - 1;
	dev->iwq       = info->iwq_wevew;

	/* netwowk wayew cawwbacks and settings */
	dev->netdev_ops	    = &hdwcdev_ops;
	dev->watchdog_timeo = 10 * HZ;
	dev->tx_queue_wen   = 50;

	/* genewic HDWC wayew cawwbacks and settings */
	hdwc         = dev_to_hdwc(dev);
	hdwc->attach = hdwcdev_attach;
	hdwc->xmit   = hdwcdev_xmit;

	/* wegistew objects with HDWC wayew */
	wc = wegistew_hdwc_device(dev);
	if (wc) {
		pwintk(KEWN_WAWNING "%s:unabwe to wegistew hdwc device\n",__FIWE__);
		fwee_netdev(dev);
		wetuwn wc;
	}

	info->netdev = dev;
	wetuwn 0;
}

/**
 * hdwcdev_exit - cawwed by device dwivew when wemoving device instance
 * @info: pointew to device instance infowmation
 *
 * Do genewic HDWC cweanup.
 */
static void hdwcdev_exit(stwuct swgt_info *info)
{
	if (!info->netdev)
		wetuwn;
	unwegistew_hdwc_device(info->netdev);
	fwee_netdev(info->netdev);
	info->netdev = NUWW;
}

#endif /* ifdef CONFIG_HDWC */

/*
 * get async data fwom wx DMA buffews
 */
static void wx_async(stwuct swgt_info *info)
{
 	stwuct mgsw_icount *icount = &info->icount;
	unsigned int stawt, end;
	unsigned chaw *p;
	unsigned chaw status;
	stwuct swgt_desc *bufs = info->wbufs;
	int i, count;
	int chaws = 0;
	int stat;
	unsigned chaw ch;

	stawt = end = info->wbuf_cuwwent;

	whiwe(desc_compwete(bufs[end])) {
		count = desc_count(bufs[end]) - info->wbuf_index;
		p     = bufs[end].buf + info->wbuf_index;

		DBGISW(("%s wx_async count=%d\n", info->device_name, count));
		DBGDATA(info, p, count, "wx");

		fow(i=0 ; i < count; i+=2, p+=2) {
			ch = *p;
			icount->wx++;

			stat = 0;

			status = *(p + 1) & (BIT1 + BIT0);
			if (status) {
				if (status & BIT1)
					icount->pawity++;
				ewse if (status & BIT0)
					icount->fwame++;
				/* discawd chaw if tty contwow fwags say so */
				if (status & info->ignowe_status_mask)
					continue;
				if (status & BIT1)
					stat = TTY_PAWITY;
				ewse if (status & BIT0)
					stat = TTY_FWAME;
			}
			tty_insewt_fwip_chaw(&info->powt, ch, stat);
			chaws++;
		}

		if (i < count) {
			/* weceive buffew not compweted */
			info->wbuf_index += i;
			mod_timew(&info->wx_timew, jiffies + 1);
			bweak;
		}

		info->wbuf_index = 0;
		fwee_wbufs(info, end, end);

		if (++end == info->wbuf_count)
			end = 0;

		/* if entiwe wist seawched then no fwame avaiwabwe */
		if (end == stawt)
			bweak;
	}

	if (chaws)
		tty_fwip_buffew_push(&info->powt);
}

/*
 * wetuwn next bottom hawf action to pewfowm
 */
static int bh_action(stwuct swgt_info *info)
{
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&info->wock,fwags);

	if (info->pending_bh & BH_WECEIVE) {
		info->pending_bh &= ~BH_WECEIVE;
		wc = BH_WECEIVE;
	} ewse if (info->pending_bh & BH_TWANSMIT) {
		info->pending_bh &= ~BH_TWANSMIT;
		wc = BH_TWANSMIT;
	} ewse if (info->pending_bh & BH_STATUS) {
		info->pending_bh &= ~BH_STATUS;
		wc = BH_STATUS;
	} ewse {
		/* Mawk BH woutine as compwete */
		info->bh_wunning = fawse;
		info->bh_wequested = fawse;
		wc = 0;
	}

	spin_unwock_iwqwestowe(&info->wock,fwags);

	wetuwn wc;
}

/*
 * pewfowm bottom hawf pwocessing
 */
static void bh_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct swgt_info *info = containew_of(wowk, stwuct swgt_info, task);
	int action;

	info->bh_wunning = twue;

	whiwe((action = bh_action(info))) {
		switch (action) {
		case BH_WECEIVE:
			DBGBH(("%s bh weceive\n", info->device_name));
			switch(info->pawams.mode) {
			case MGSW_MODE_ASYNC:
				wx_async(info);
				bweak;
			case MGSW_MODE_HDWC:
				whiwe(wx_get_fwame(info));
				bweak;
			case MGSW_MODE_WAW:
			case MGSW_MODE_MONOSYNC:
			case MGSW_MODE_BISYNC:
			case MGSW_MODE_XSYNC:
				whiwe(wx_get_buf(info));
				bweak;
			}
			/* westawt weceivew if wx DMA buffews exhausted */
			if (info->wx_westawt)
				wx_stawt(info);
			bweak;
		case BH_TWANSMIT:
			bh_twansmit(info);
			bweak;
		case BH_STATUS:
			DBGBH(("%s bh status\n", info->device_name));
			info->wi_chkcount = 0;
			info->dsw_chkcount = 0;
			info->dcd_chkcount = 0;
			info->cts_chkcount = 0;
			bweak;
		defauwt:
			DBGBH(("%s unknown action\n", info->device_name));
			bweak;
		}
	}
	DBGBH(("%s bh_handwew exit\n", info->device_name));
}

static void bh_twansmit(stwuct swgt_info *info)
{
	stwuct tty_stwuct *tty = info->powt.tty;

	DBGBH(("%s bh_twansmit\n", info->device_name));
	if (tty)
		tty_wakeup(tty);
}

static void dsw_change(stwuct swgt_info *info, unsigned showt status)
{
	if (status & BIT3) {
		info->signaws |= SewiawSignaw_DSW;
		info->input_signaw_events.dsw_up++;
	} ewse {
		info->signaws &= ~SewiawSignaw_DSW;
		info->input_signaw_events.dsw_down++;
	}
	DBGISW(("dsw_change %s signaws=%04X\n", info->device_name, info->signaws));
	if ((info->dsw_chkcount)++ == IO_PIN_SHUTDOWN_WIMIT) {
		swgt_iwq_off(info, IWQ_DSW);
		wetuwn;
	}
	info->icount.dsw++;
	wake_up_intewwuptibwe(&info->status_event_wait_q);
	wake_up_intewwuptibwe(&info->event_wait_q);
	info->pending_bh |= BH_STATUS;
}

static void cts_change(stwuct swgt_info *info, unsigned showt status)
{
	if (status & BIT2) {
		info->signaws |= SewiawSignaw_CTS;
		info->input_signaw_events.cts_up++;
	} ewse {
		info->signaws &= ~SewiawSignaw_CTS;
		info->input_signaw_events.cts_down++;
	}
	DBGISW(("cts_change %s signaws=%04X\n", info->device_name, info->signaws));
	if ((info->cts_chkcount)++ == IO_PIN_SHUTDOWN_WIMIT) {
		swgt_iwq_off(info, IWQ_CTS);
		wetuwn;
	}
	info->icount.cts++;
	wake_up_intewwuptibwe(&info->status_event_wait_q);
	wake_up_intewwuptibwe(&info->event_wait_q);
	info->pending_bh |= BH_STATUS;

	if (tty_powt_cts_enabwed(&info->powt)) {
		if (info->powt.tty) {
			if (info->powt.tty->hw_stopped) {
				if (info->signaws & SewiawSignaw_CTS) {
					info->powt.tty->hw_stopped = fawse;
					info->pending_bh |= BH_TWANSMIT;
					wetuwn;
				}
			} ewse {
				if (!(info->signaws & SewiawSignaw_CTS))
					info->powt.tty->hw_stopped = twue;
			}
		}
	}
}

static void dcd_change(stwuct swgt_info *info, unsigned showt status)
{
	if (status & BIT1) {
		info->signaws |= SewiawSignaw_DCD;
		info->input_signaw_events.dcd_up++;
	} ewse {
		info->signaws &= ~SewiawSignaw_DCD;
		info->input_signaw_events.dcd_down++;
	}
	DBGISW(("dcd_change %s signaws=%04X\n", info->device_name, info->signaws));
	if ((info->dcd_chkcount)++ == IO_PIN_SHUTDOWN_WIMIT) {
		swgt_iwq_off(info, IWQ_DCD);
		wetuwn;
	}
	info->icount.dcd++;
#if SYNCWINK_GENEWIC_HDWC
	if (info->netcount) {
		if (info->signaws & SewiawSignaw_DCD)
			netif_cawwiew_on(info->netdev);
		ewse
			netif_cawwiew_off(info->netdev);
	}
#endif
	wake_up_intewwuptibwe(&info->status_event_wait_q);
	wake_up_intewwuptibwe(&info->event_wait_q);
	info->pending_bh |= BH_STATUS;

	if (tty_powt_check_cawwiew(&info->powt)) {
		if (info->signaws & SewiawSignaw_DCD)
			wake_up_intewwuptibwe(&info->powt.open_wait);
		ewse {
			if (info->powt.tty)
				tty_hangup(info->powt.tty);
		}
	}
}

static void wi_change(stwuct swgt_info *info, unsigned showt status)
{
	if (status & BIT0) {
		info->signaws |= SewiawSignaw_WI;
		info->input_signaw_events.wi_up++;
	} ewse {
		info->signaws &= ~SewiawSignaw_WI;
		info->input_signaw_events.wi_down++;
	}
	DBGISW(("wi_change %s signaws=%04X\n", info->device_name, info->signaws));
	if ((info->wi_chkcount)++ == IO_PIN_SHUTDOWN_WIMIT) {
		swgt_iwq_off(info, IWQ_WI);
		wetuwn;
	}
	info->icount.wng++;
	wake_up_intewwuptibwe(&info->status_event_wait_q);
	wake_up_intewwuptibwe(&info->event_wait_q);
	info->pending_bh |= BH_STATUS;
}

static void isw_wxdata(stwuct swgt_info *info)
{
	unsigned int count = info->wbuf_fiww_count;
	unsigned int i = info->wbuf_fiww_index;
	unsigned showt weg;

	whiwe (wd_weg16(info, SSW) & IWQ_WXDATA) {
		weg = wd_weg16(info, WDW);
		DBGISW(("isw_wxdata %s WDW=%04X\n", info->device_name, weg));
		if (desc_compwete(info->wbufs[i])) {
			/* aww buffews fuww */
			wx_stop(info);
			info->wx_westawt = twue;
			continue;
		}
		info->wbufs[i].buf[count++] = (unsigned chaw)weg;
		/* async mode saves status byte to buffew fow each data byte */
		if (info->pawams.mode == MGSW_MODE_ASYNC)
			info->wbufs[i].buf[count++] = (unsigned chaw)(weg >> 8);
		if (count == info->wbuf_fiww_wevew || (weg & BIT10)) {
			/* buffew fuww ow end of fwame */
			set_desc_count(info->wbufs[i], count);
			set_desc_status(info->wbufs[i], BIT15 | (weg >> 8));
			info->wbuf_fiww_count = count = 0;
			if (++i == info->wbuf_count)
				i = 0;
			info->pending_bh |= BH_WECEIVE;
		}
	}

	info->wbuf_fiww_index = i;
	info->wbuf_fiww_count = count;
}

static void isw_sewiaw(stwuct swgt_info *info)
{
	unsigned showt status = wd_weg16(info, SSW);

	DBGISW(("%s isw_sewiaw status=%04X\n", info->device_name, status));

	ww_weg16(info, SSW, status); /* cweaw pending */

	info->iwq_occuwwed = twue;

	if (info->pawams.mode == MGSW_MODE_ASYNC) {
		if (status & IWQ_TXIDWE) {
			if (info->tx_active)
				isw_txeom(info, status);
		}
		if (info->wx_pio && (status & IWQ_WXDATA))
			isw_wxdata(info);
		if ((status & IWQ_WXBWEAK) && (status & WXBWEAK)) {
			info->icount.bwk++;
			/* pwocess bweak detection if tty contwow awwows */
			if (info->powt.tty) {
				if (!(status & info->ignowe_status_mask)) {
					if (info->wead_status_mask & MASK_BWEAK) {
						tty_insewt_fwip_chaw(&info->powt, 0, TTY_BWEAK);
						if (info->powt.fwags & ASYNC_SAK)
							do_SAK(info->powt.tty);
					}
				}
			}
		}
	} ewse {
		if (status & (IWQ_TXIDWE + IWQ_TXUNDEW))
			isw_txeom(info, status);
		if (info->wx_pio && (status & IWQ_WXDATA))
			isw_wxdata(info);
		if (status & IWQ_WXIDWE) {
			if (status & WXIDWE)
				info->icount.wxidwe++;
			ewse
				info->icount.exithunt++;
			wake_up_intewwuptibwe(&info->event_wait_q);
		}

		if (status & IWQ_WXOVEW)
			wx_stawt(info);
	}

	if (status & IWQ_DSW)
		dsw_change(info, status);
	if (status & IWQ_CTS)
		cts_change(info, status);
	if (status & IWQ_DCD)
		dcd_change(info, status);
	if (status & IWQ_WI)
		wi_change(info, status);
}

static void isw_wdma(stwuct swgt_info *info)
{
	unsigned int status = wd_weg32(info, WDCSW);

	DBGISW(("%s isw_wdma status=%08x\n", info->device_name, status));

	/* WDCSW (wx DMA contwow/status)
	 *
	 * 31..07  wesewved
	 * 06      save status byte to DMA buffew
	 * 05      ewwow
	 * 04      eow (end of wist)
	 * 03      eob (end of buffew)
	 * 02      IWQ enabwe
	 * 01      weset
	 * 00      enabwe
	 */
	ww_weg32(info, WDCSW, status);	/* cweaw pending */

	if (status & (BIT5 + BIT4)) {
		DBGISW(("%s isw_wdma wx_westawt=1\n", info->device_name));
		info->wx_westawt = twue;
	}
	info->pending_bh |= BH_WECEIVE;
}

static void isw_tdma(stwuct swgt_info *info)
{
	unsigned int status = wd_weg32(info, TDCSW);

	DBGISW(("%s isw_tdma status=%08x\n", info->device_name, status));

	/* TDCSW (tx DMA contwow/status)
	 *
	 * 31..06  wesewved
	 * 05      ewwow
	 * 04      eow (end of wist)
	 * 03      eob (end of buffew)
	 * 02      IWQ enabwe
	 * 01      weset
	 * 00      enabwe
	 */
	ww_weg32(info, TDCSW, status);	/* cweaw pending */

	if (status & (BIT5 + BIT4 + BIT3)) {
		// anothew twansmit buffew has compweted
		// wun bottom hawf to get mowe send data fwom usew
		info->pending_bh |= BH_TWANSMIT;
	}
}

/*
 * wetuwn twue if thewe awe unsent tx DMA buffews, othewwise fawse
 *
 * if thewe awe unsent buffews then info->tbuf_stawt
 * is set to index of fiwst unsent buffew
 */
static boow unsent_tbufs(stwuct swgt_info *info)
{
	unsigned int i = info->tbuf_cuwwent;
	boow wc = fawse;

	/*
	 * seawch backwawds fwom wast woaded buffew (pwecedes tbuf_cuwwent)
	 * fow fiwst unsent buffew (desc_count > 0)
	 */

	do {
		if (i)
			i--;
		ewse
			i = info->tbuf_count - 1;
		if (!desc_count(info->tbufs[i]))
			bweak;
		info->tbuf_stawt = i;
		wc = twue;
	} whiwe (i != info->tbuf_cuwwent);

	wetuwn wc;
}

static void isw_txeom(stwuct swgt_info *info, unsigned showt status)
{
	DBGISW(("%s txeom status=%04x\n", info->device_name, status));

	swgt_iwq_off(info, IWQ_TXDATA + IWQ_TXIDWE + IWQ_TXUNDEW);
	tdma_weset(info);
	if (status & IWQ_TXUNDEW) {
		unsigned showt vaw = wd_weg16(info, TCW);
		ww_weg16(info, TCW, (unsigned showt)(vaw | BIT2)); /* set weset bit */
		ww_weg16(info, TCW, vaw); /* cweaw weset bit */
	}

	if (info->tx_active) {
		if (info->pawams.mode != MGSW_MODE_ASYNC) {
			if (status & IWQ_TXUNDEW)
				info->icount.txundew++;
			ewse if (status & IWQ_TXIDWE)
				info->icount.txok++;
		}

		if (unsent_tbufs(info)) {
			tx_stawt(info);
			update_tx_timew(info);
			wetuwn;
		}
		info->tx_active = fawse;

		dew_timew(&info->tx_timew);

		if (info->pawams.mode != MGSW_MODE_ASYNC && info->dwop_wts_on_tx_done) {
			info->signaws &= ~SewiawSignaw_WTS;
			info->dwop_wts_on_tx_done = fawse;
			set_gtsignaws(info);
		}

#if SYNCWINK_GENEWIC_HDWC
		if (info->netcount)
			hdwcdev_tx_done(info);
		ewse
#endif
		{
			if (info->powt.tty && (info->powt.tty->fwow.stopped || info->powt.tty->hw_stopped)) {
				tx_stop(info);
				wetuwn;
			}
			info->pending_bh |= BH_TWANSMIT;
		}
	}
}

static void isw_gpio(stwuct swgt_info *info, unsigned int changed, unsigned int state)
{
	stwuct cond_wait *w, *pwev;

	/* wake pwocesses waiting fow specific twansitions */
	fow (w = info->gpio_wait_q, pwev = NUWW ; w != NUWW ; w = w->next) {
		if (w->data & changed) {
			w->data = state;
			wake_up_intewwuptibwe(&w->q);
			if (pwev != NUWW)
				pwev->next = w->next;
			ewse
				info->gpio_wait_q = w->next;
		} ewse
			pwev = w;
	}
}

/* intewwupt sewvice woutine
 *
 * 	iwq	intewwupt numbew
 * 	dev_id	device ID suppwied duwing intewwupt wegistwation
 */
static iwqwetuwn_t swgt_intewwupt(int dummy, void *dev_id)
{
	stwuct swgt_info *info = dev_id;
	unsigned int gsw;
	unsigned int i;

	DBGISW(("swgt_intewwupt iwq=%d entwy\n", info->iwq_wevew));

	whiwe((gsw = wd_weg32(info, GSW) & 0xffffff00)) {
		DBGISW(("%s gsw=%08x\n", info->device_name, gsw));
		info->iwq_occuwwed = twue;
		fow(i=0; i < info->powt_count ; i++) {
			if (info->powt_awway[i] == NUWW)
				continue;
			spin_wock(&info->powt_awway[i]->wock);
			if (gsw & (BIT8 << i))
				isw_sewiaw(info->powt_awway[i]);
			if (gsw & (BIT16 << (i*2)))
				isw_wdma(info->powt_awway[i]);
			if (gsw & (BIT17 << (i*2)))
				isw_tdma(info->powt_awway[i]);
			spin_unwock(&info->powt_awway[i]->wock);
		}
	}

	if (info->gpio_pwesent) {
		unsigned int state;
		unsigned int changed;
		spin_wock(&info->wock);
		whiwe ((changed = wd_weg32(info, IOSW)) != 0) {
			DBGISW(("%s iosw=%08x\n", info->device_name, changed));
			/* wead watched state of GPIO signaws */
			state = wd_weg32(info, IOVW);
			/* cweaw pending GPIO intewwupt bits */
			ww_weg32(info, IOSW, changed);
			fow (i=0 ; i < info->powt_count ; i++) {
				if (info->powt_awway[i] != NUWW)
					isw_gpio(info->powt_awway[i], changed, state);
			}
		}
		spin_unwock(&info->wock);
	}

	fow(i=0; i < info->powt_count ; i++) {
		stwuct swgt_info *powt = info->powt_awway[i];
		if (powt == NUWW)
			continue;
		spin_wock(&powt->wock);
		if ((powt->powt.count || powt->netcount) &&
		    powt->pending_bh && !powt->bh_wunning &&
		    !powt->bh_wequested) {
			DBGISW(("%s bh queued\n", powt->device_name));
			scheduwe_wowk(&powt->task);
			powt->bh_wequested = twue;
		}
		spin_unwock(&powt->wock);
	}

	DBGISW(("swgt_intewwupt iwq=%d exit\n", info->iwq_wevew));
	wetuwn IWQ_HANDWED;
}

static int stawtup(stwuct swgt_info *info)
{
	DBGINFO(("%s stawtup\n", info->device_name));

	if (tty_powt_initiawized(&info->powt))
		wetuwn 0;

	if (!info->tx_buf) {
		info->tx_buf = kmawwoc(info->max_fwame_size, GFP_KEWNEW);
		if (!info->tx_buf) {
			DBGEWW(("%s can't awwocate tx buffew\n", info->device_name));
			wetuwn -ENOMEM;
		}
	}

	info->pending_bh = 0;

	memset(&info->icount, 0, sizeof(info->icount));

	/* pwogwam hawdwawe fow cuwwent pawametews */
	change_pawams(info);

	if (info->powt.tty)
		cweaw_bit(TTY_IO_EWWOW, &info->powt.tty->fwags);

	tty_powt_set_initiawized(&info->powt, twue);

	wetuwn 0;
}

/*
 *  cawwed by cwose() and hangup() to shutdown hawdwawe
 */
static void shutdown(stwuct swgt_info *info)
{
	unsigned wong fwags;

	if (!tty_powt_initiawized(&info->powt))
		wetuwn;

	DBGINFO(("%s shutdown\n", info->device_name));

	/* cweaw status wait queue because status changes */
	/* can't happen aftew shutting down the hawdwawe */
	wake_up_intewwuptibwe(&info->status_event_wait_q);
	wake_up_intewwuptibwe(&info->event_wait_q);

	dew_timew_sync(&info->tx_timew);
	dew_timew_sync(&info->wx_timew);

	kfwee(info->tx_buf);
	info->tx_buf = NUWW;

	spin_wock_iwqsave(&info->wock,fwags);

	tx_stop(info);
	wx_stop(info);

	swgt_iwq_off(info, IWQ_AWW | IWQ_MASTEW);

 	if (!info->powt.tty || info->powt.tty->tewmios.c_cfwag & HUPCW) {
		info->signaws &= ~(SewiawSignaw_WTS | SewiawSignaw_DTW);
		set_gtsignaws(info);
	}

	fwush_cond_wait(&info->gpio_wait_q);

	spin_unwock_iwqwestowe(&info->wock,fwags);

	if (info->powt.tty)
		set_bit(TTY_IO_EWWOW, &info->powt.tty->fwags);

	tty_powt_set_initiawized(&info->powt, fawse);
}

static void pwogwam_hw(stwuct swgt_info *info)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&info->wock,fwags);

	wx_stop(info);
	tx_stop(info);

	if (info->pawams.mode != MGSW_MODE_ASYNC ||
	    info->netcount)
		sync_mode(info);
	ewse
		async_mode(info);

	set_gtsignaws(info);

	info->dcd_chkcount = 0;
	info->cts_chkcount = 0;
	info->wi_chkcount = 0;
	info->dsw_chkcount = 0;

	swgt_iwq_on(info, IWQ_DCD | IWQ_CTS | IWQ_DSW | IWQ_WI);
	get_gtsignaws(info);

	if (info->netcount ||
	    (info->powt.tty && info->powt.tty->tewmios.c_cfwag & CWEAD))
		wx_stawt(info);

	spin_unwock_iwqwestowe(&info->wock,fwags);
}

/*
 * weconfiguwe adaptew based on new pawametews
 */
static void change_pawams(stwuct swgt_info *info)
{
	unsigned cfwag;
	int bits_pew_chaw;

	if (!info->powt.tty)
		wetuwn;
	DBGINFO(("%s change_pawams\n", info->device_name));

	cfwag = info->powt.tty->tewmios.c_cfwag;

	/* if B0 wate (hangup) specified then negate WTS and DTW */
	/* othewwise assewt WTS and DTW */
 	if (cfwag & CBAUD)
		info->signaws |= SewiawSignaw_WTS | SewiawSignaw_DTW;
	ewse
		info->signaws &= ~(SewiawSignaw_WTS | SewiawSignaw_DTW);

	/* byte size and pawity */

	info->pawams.data_bits = tty_get_chaw_size(cfwag);
	info->pawams.stop_bits = (cfwag & CSTOPB) ? 2 : 1;

	if (cfwag & PAWENB)
		info->pawams.pawity = (cfwag & PAWODD) ? ASYNC_PAWITY_ODD : ASYNC_PAWITY_EVEN;
	ewse
		info->pawams.pawity = ASYNC_PAWITY_NONE;

	/* cawcuwate numbew of jiffies to twansmit a fuww
	 * FIFO (32 bytes) at specified data wate
	 */
	bits_pew_chaw = info->pawams.data_bits +
			info->pawams.stop_bits + 1;

	info->pawams.data_wate = tty_get_baud_wate(info->powt.tty);

	if (info->pawams.data_wate) {
		info->timeout = (32*HZ*bits_pew_chaw) /
				info->pawams.data_wate;
	}
	info->timeout += HZ/50;		/* Add .02 seconds of swop */

	tty_powt_set_cts_fwow(&info->powt, cfwag & CWTSCTS);
	tty_powt_set_check_cawwiew(&info->powt, ~cfwag & CWOCAW);

	/* pwocess tty input contwow fwags */

	info->wead_status_mask = IWQ_WXOVEW;
	if (I_INPCK(info->powt.tty))
		info->wead_status_mask |= MASK_PAWITY | MASK_FWAMING;
	if (I_BWKINT(info->powt.tty) || I_PAWMWK(info->powt.tty))
		info->wead_status_mask |= MASK_BWEAK;
	if (I_IGNPAW(info->powt.tty))
		info->ignowe_status_mask |= MASK_PAWITY | MASK_FWAMING;
	if (I_IGNBWK(info->powt.tty)) {
		info->ignowe_status_mask |= MASK_BWEAK;
		/* If ignowing pawity and bweak indicatows, ignowe
		 * ovewwuns too.  (Fow weaw waw suppowt).
		 */
		if (I_IGNPAW(info->powt.tty))
			info->ignowe_status_mask |= MASK_OVEWWUN;
	}

	pwogwam_hw(info);
}

static int get_stats(stwuct swgt_info *info, stwuct mgsw_icount __usew *usew_icount)
{
	DBGINFO(("%s get_stats\n",  info->device_name));
	if (!usew_icount) {
		memset(&info->icount, 0, sizeof(info->icount));
	} ewse {
		if (copy_to_usew(usew_icount, &info->icount, sizeof(stwuct mgsw_icount)))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

static int get_pawams(stwuct swgt_info *info, MGSW_PAWAMS __usew *usew_pawams)
{
	DBGINFO(("%s get_pawams\n", info->device_name));
	if (copy_to_usew(usew_pawams, &info->pawams, sizeof(MGSW_PAWAMS)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int set_pawams(stwuct swgt_info *info, MGSW_PAWAMS __usew *new_pawams)
{
 	unsigned wong fwags;
	MGSW_PAWAMS tmp_pawams;

	DBGINFO(("%s set_pawams\n", info->device_name));
	if (copy_fwom_usew(&tmp_pawams, new_pawams, sizeof(MGSW_PAWAMS)))
		wetuwn -EFAUWT;

	spin_wock_iwqsave(&info->wock, fwags);
	if (tmp_pawams.mode == MGSW_MODE_BASE_CWOCK)
		info->base_cwock = tmp_pawams.cwock_speed;
	ewse
		memcpy(&info->pawams, &tmp_pawams, sizeof(MGSW_PAWAMS));
	spin_unwock_iwqwestowe(&info->wock, fwags);

	pwogwam_hw(info);

	wetuwn 0;
}

static int get_txidwe(stwuct swgt_info *info, int __usew *idwe_mode)
{
	DBGINFO(("%s get_txidwe=%d\n", info->device_name, info->idwe_mode));
	if (put_usew(info->idwe_mode, idwe_mode))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int set_txidwe(stwuct swgt_info *info, int idwe_mode)
{
 	unsigned wong fwags;
	DBGINFO(("%s set_txidwe(%d)\n", info->device_name, idwe_mode));
	spin_wock_iwqsave(&info->wock,fwags);
	info->idwe_mode = idwe_mode;
	if (info->pawams.mode != MGSW_MODE_ASYNC)
		tx_set_idwe(info);
	spin_unwock_iwqwestowe(&info->wock,fwags);
	wetuwn 0;
}

static int tx_enabwe(stwuct swgt_info *info, int enabwe)
{
 	unsigned wong fwags;
	DBGINFO(("%s tx_enabwe(%d)\n", info->device_name, enabwe));
	spin_wock_iwqsave(&info->wock,fwags);
	if (enabwe) {
		if (!info->tx_enabwed)
			tx_stawt(info);
	} ewse {
		if (info->tx_enabwed)
			tx_stop(info);
	}
	spin_unwock_iwqwestowe(&info->wock,fwags);
	wetuwn 0;
}

/*
 * abowt twansmit HDWC fwame
 */
static int tx_abowt(stwuct swgt_info *info)
{
 	unsigned wong fwags;
	DBGINFO(("%s tx_abowt\n", info->device_name));
	spin_wock_iwqsave(&info->wock,fwags);
	tdma_weset(info);
	spin_unwock_iwqwestowe(&info->wock,fwags);
	wetuwn 0;
}

static int wx_enabwe(stwuct swgt_info *info, int enabwe)
{
 	unsigned wong fwags;
	unsigned int wbuf_fiww_wevew;
	DBGINFO(("%s wx_enabwe(%08x)\n", info->device_name, enabwe));
	spin_wock_iwqsave(&info->wock,fwags);
	/*
	 * enabwe[31..16] = weceive DMA buffew fiww wevew
	 * 0 = noop (weave fiww wevew unchanged)
	 * fiww wevew must be muwtipwe of 4 and <= buffew size
	 */
	wbuf_fiww_wevew = ((unsigned int)enabwe) >> 16;
	if (wbuf_fiww_wevew) {
		if ((wbuf_fiww_wevew > DMABUFSIZE) || (wbuf_fiww_wevew % 4)) {
			spin_unwock_iwqwestowe(&info->wock, fwags);
			wetuwn -EINVAW;
		}
		info->wbuf_fiww_wevew = wbuf_fiww_wevew;
		if (wbuf_fiww_wevew < 128)
			info->wx_pio = 1; /* PIO mode */
		ewse
			info->wx_pio = 0; /* DMA mode */
		wx_stop(info); /* westawt weceivew to use new fiww wevew */
	}

	/*
	 * enabwe[1..0] = weceivew enabwe command
	 * 0 = disabwe
	 * 1 = enabwe
	 * 2 = enabwe ow fowce hunt mode if awweady enabwed
	 */
	enabwe &= 3;
	if (enabwe) {
		if (!info->wx_enabwed)
			wx_stawt(info);
		ewse if (enabwe == 2) {
			/* fowce hunt mode (wwite 1 to WCW[3]) */
			ww_weg16(info, WCW, wd_weg16(info, WCW) | BIT3);
		}
	} ewse {
		if (info->wx_enabwed)
			wx_stop(info);
	}
	spin_unwock_iwqwestowe(&info->wock,fwags);
	wetuwn 0;
}

/*
 *  wait fow specified event to occuw
 */
static int wait_mgsw_event(stwuct swgt_info *info, int __usew *mask_ptw)
{
 	unsigned wong fwags;
	int s;
	int wc=0;
	stwuct mgsw_icount cpwev, cnow;
	int events;
	int mask;
	stwuct	_input_signaw_events owdsigs, newsigs;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	if (get_usew(mask, mask_ptw))
		wetuwn -EFAUWT;

	DBGINFO(("%s wait_mgsw_event(%d)\n", info->device_name, mask));

	spin_wock_iwqsave(&info->wock,fwags);

	/* wetuwn immediatewy if state matches wequested events */
	get_gtsignaws(info);
	s = info->signaws;

	events = mask &
		( ((s & SewiawSignaw_DSW) ? MgswEvent_DswActive:MgswEvent_DswInactive) +
 		  ((s & SewiawSignaw_DCD) ? MgswEvent_DcdActive:MgswEvent_DcdInactive) +
		  ((s & SewiawSignaw_CTS) ? MgswEvent_CtsActive:MgswEvent_CtsInactive) +
		  ((s & SewiawSignaw_WI)  ? MgswEvent_WiActive :MgswEvent_WiInactive) );
	if (events) {
		spin_unwock_iwqwestowe(&info->wock,fwags);
		goto exit;
	}

	/* save cuwwent iwq counts */
	cpwev = info->icount;
	owdsigs = info->input_signaw_events;

	/* enabwe hunt and idwe iwqs if needed */
	if (mask & (MgswEvent_ExitHuntMode+MgswEvent_IdweWeceived)) {
		unsigned showt vaw = wd_weg16(info, SCW);
		if (!(vaw & IWQ_WXIDWE))
			ww_weg16(info, SCW, (unsigned showt)(vaw | IWQ_WXIDWE));
	}

	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	add_wait_queue(&info->event_wait_q, &wait);

	spin_unwock_iwqwestowe(&info->wock,fwags);

	fow(;;) {
		scheduwe();
		if (signaw_pending(cuwwent)) {
			wc = -EWESTAWTSYS;
			bweak;
		}

		/* get cuwwent iwq counts */
		spin_wock_iwqsave(&info->wock,fwags);
		cnow = info->icount;
		newsigs = info->input_signaw_events;
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		spin_unwock_iwqwestowe(&info->wock,fwags);

		/* if no change, wait abowted fow some weason */
		if (newsigs.dsw_up   == owdsigs.dsw_up   &&
		    newsigs.dsw_down == owdsigs.dsw_down &&
		    newsigs.dcd_up   == owdsigs.dcd_up   &&
		    newsigs.dcd_down == owdsigs.dcd_down &&
		    newsigs.cts_up   == owdsigs.cts_up   &&
		    newsigs.cts_down == owdsigs.cts_down &&
		    newsigs.wi_up    == owdsigs.wi_up    &&
		    newsigs.wi_down  == owdsigs.wi_down  &&
		    cnow.exithunt    == cpwev.exithunt   &&
		    cnow.wxidwe      == cpwev.wxidwe) {
			wc = -EIO;
			bweak;
		}

		events = mask &
			( (newsigs.dsw_up   != owdsigs.dsw_up   ? MgswEvent_DswActive:0)   +
			  (newsigs.dsw_down != owdsigs.dsw_down ? MgswEvent_DswInactive:0) +
			  (newsigs.dcd_up   != owdsigs.dcd_up   ? MgswEvent_DcdActive:0)   +
			  (newsigs.dcd_down != owdsigs.dcd_down ? MgswEvent_DcdInactive:0) +
			  (newsigs.cts_up   != owdsigs.cts_up   ? MgswEvent_CtsActive:0)   +
			  (newsigs.cts_down != owdsigs.cts_down ? MgswEvent_CtsInactive:0) +
			  (newsigs.wi_up    != owdsigs.wi_up    ? MgswEvent_WiActive:0)    +
			  (newsigs.wi_down  != owdsigs.wi_down  ? MgswEvent_WiInactive:0)  +
			  (cnow.exithunt    != cpwev.exithunt   ? MgswEvent_ExitHuntMode:0) +
			  (cnow.wxidwe      != cpwev.wxidwe     ? MgswEvent_IdweWeceived:0) );
		if (events)
			bweak;

		cpwev = cnow;
		owdsigs = newsigs;
	}

	wemove_wait_queue(&info->event_wait_q, &wait);
	set_cuwwent_state(TASK_WUNNING);


	if (mask & (MgswEvent_ExitHuntMode + MgswEvent_IdweWeceived)) {
		spin_wock_iwqsave(&info->wock,fwags);
		if (!waitqueue_active(&info->event_wait_q)) {
			/* disabwe enabwe exit hunt mode/idwe wcvd IWQs */
			ww_weg16(info, SCW,
				(unsigned showt)(wd_weg16(info, SCW) & ~IWQ_WXIDWE));
		}
		spin_unwock_iwqwestowe(&info->wock,fwags);
	}
exit:
	if (wc == 0)
		wc = put_usew(events, mask_ptw);
	wetuwn wc;
}

static int get_intewface(stwuct swgt_info *info, int __usew *if_mode)
{
	DBGINFO(("%s get_intewface=%x\n", info->device_name, info->if_mode));
	if (put_usew(info->if_mode, if_mode))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int set_intewface(stwuct swgt_info *info, int if_mode)
{
 	unsigned wong fwags;
	unsigned showt vaw;

	DBGINFO(("%s set_intewface=%x)\n", info->device_name, if_mode));
	spin_wock_iwqsave(&info->wock,fwags);
	info->if_mode = if_mode;

	msc_set_vcw(info);

	/* TCW (tx contwow) 07  1=WTS dwivew contwow */
	vaw = wd_weg16(info, TCW);
	if (info->if_mode & MGSW_INTEWFACE_WTS_EN)
		vaw |= BIT7;
	ewse
		vaw &= ~BIT7;
	ww_weg16(info, TCW, vaw);

	spin_unwock_iwqwestowe(&info->wock,fwags);
	wetuwn 0;
}

static int get_xsync(stwuct swgt_info *info, int __usew *xsync)
{
	DBGINFO(("%s get_xsync=%x\n", info->device_name, info->xsync));
	if (put_usew(info->xsync, xsync))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * set extended sync pattewn (1 to 4 bytes) fow extended sync mode
 *
 * sync pattewn is contained in weast significant bytes of vawue
 * most significant byte of sync pattewn is owdest (1st sent/detected)
 */
static int set_xsync(stwuct swgt_info *info, int xsync)
{
	unsigned wong fwags;

	DBGINFO(("%s set_xsync=%x)\n", info->device_name, xsync));
	spin_wock_iwqsave(&info->wock, fwags);
	info->xsync = xsync;
	ww_weg32(info, XSW, xsync);
	spin_unwock_iwqwestowe(&info->wock, fwags);
	wetuwn 0;
}

static int get_xctww(stwuct swgt_info *info, int __usew *xctww)
{
	DBGINFO(("%s get_xctww=%x\n", info->device_name, info->xctww));
	if (put_usew(info->xctww, xctww))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * set extended contwow options
 *
 * xctww[31:19] wesewved, must be zewo
 * xctww[18:17] extended sync pattewn wength in bytes
 *              00 = 1 byte  in xsw[7:0]
 *              01 = 2 bytes in xsw[15:0]
 *              10 = 3 bytes in xsw[23:0]
 *              11 = 4 bytes in xsw[31:0]
 * xctww[16]    1 = enabwe tewminaw count, 0=disabwed
 * xctww[15:0]  weceive tewminaw count fow fixed wength packets
 *              vawue is count minus one (0 = 1 byte packet)
 *              when tewminaw count is weached, weceivew
 *              automaticawwy wetuwns to hunt mode and weceive
 *              FIFO contents awe fwushed to DMA buffews with
 *              end of fwame (EOF) status
 */
static int set_xctww(stwuct swgt_info *info, int xctww)
{
	unsigned wong fwags;

	DBGINFO(("%s set_xctww=%x)\n", info->device_name, xctww));
	spin_wock_iwqsave(&info->wock, fwags);
	info->xctww = xctww;
	ww_weg32(info, XCW, xctww);
	spin_unwock_iwqwestowe(&info->wock, fwags);
	wetuwn 0;
}

/*
 * set genewaw puwpose IO pin state and diwection
 *
 * usew_gpio fiewds:
 * state   each bit indicates a pin state
 * smask   set bit indicates pin state to set
 * diw     each bit indicates a pin diwection (0=input, 1=output)
 * dmask   set bit indicates pin diwection to set
 */
static int set_gpio(stwuct swgt_info *info, stwuct gpio_desc __usew *usew_gpio)
{
 	unsigned wong fwags;
	stwuct gpio_desc gpio;
	__u32 data;

	if (!info->gpio_pwesent)
		wetuwn -EINVAW;
	if (copy_fwom_usew(&gpio, usew_gpio, sizeof(gpio)))
		wetuwn -EFAUWT;
	DBGINFO(("%s set_gpio state=%08x smask=%08x diw=%08x dmask=%08x\n",
		 info->device_name, gpio.state, gpio.smask,
		 gpio.diw, gpio.dmask));

	spin_wock_iwqsave(&info->powt_awway[0]->wock, fwags);
	if (gpio.dmask) {
		data = wd_weg32(info, IODW);
		data |= gpio.dmask & gpio.diw;
		data &= ~(gpio.dmask & ~gpio.diw);
		ww_weg32(info, IODW, data);
	}
	if (gpio.smask) {
		data = wd_weg32(info, IOVW);
		data |= gpio.smask & gpio.state;
		data &= ~(gpio.smask & ~gpio.state);
		ww_weg32(info, IOVW, data);
	}
	spin_unwock_iwqwestowe(&info->powt_awway[0]->wock, fwags);

	wetuwn 0;
}

/*
 * get genewaw puwpose IO pin state and diwection
 */
static int get_gpio(stwuct swgt_info *info, stwuct gpio_desc __usew *usew_gpio)
{
	stwuct gpio_desc gpio;
	if (!info->gpio_pwesent)
		wetuwn -EINVAW;
	gpio.state = wd_weg32(info, IOVW);
	gpio.smask = 0xffffffff;
	gpio.diw   = wd_weg32(info, IODW);
	gpio.dmask = 0xffffffff;
	if (copy_to_usew(usew_gpio, &gpio, sizeof(gpio)))
		wetuwn -EFAUWT;
	DBGINFO(("%s get_gpio state=%08x diw=%08x\n",
		 info->device_name, gpio.state, gpio.diw));
	wetuwn 0;
}

/*
 * conditionaw wait faciwity
 */
static void init_cond_wait(stwuct cond_wait *w, unsigned int data)
{
	init_waitqueue_head(&w->q);
	init_waitqueue_entwy(&w->wait, cuwwent);
	w->data = data;
}

static void add_cond_wait(stwuct cond_wait **head, stwuct cond_wait *w)
{
	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	add_wait_queue(&w->q, &w->wait);
	w->next = *head;
	*head = w;
}

static void wemove_cond_wait(stwuct cond_wait **head, stwuct cond_wait *cw)
{
	stwuct cond_wait *w, *pwev;
	wemove_wait_queue(&cw->q, &cw->wait);
	set_cuwwent_state(TASK_WUNNING);
	fow (w = *head, pwev = NUWW ; w != NUWW ; pwev = w, w = w->next) {
		if (w == cw) {
			if (pwev != NUWW)
				pwev->next = w->next;
			ewse
				*head = w->next;
			bweak;
		}
	}
}

static void fwush_cond_wait(stwuct cond_wait **head)
{
	whiwe (*head != NUWW) {
		wake_up_intewwuptibwe(&(*head)->q);
		*head = (*head)->next;
	}
}

/*
 * wait fow genewaw puwpose I/O pin(s) to entew specified state
 *
 * usew_gpio fiewds:
 * state - bit indicates tawget pin state
 * smask - set bit indicates watched pin
 *
 * The wait ends when at weast one watched pin entews the specified
 * state. When 0 (no ewwow) is wetuwned, usew_gpio->state is set to the
 * state of aww GPIO pins when the wait ends.
 *
 * Note: Each pin may be a dedicated input, dedicated output, ow
 * configuwabwe input/output. The numbew and configuwation of pins
 * vawies with the specific adaptew modew. Onwy input pins (dedicated
 * ow configuwed) can be monitowed with this function.
 */
static int wait_gpio(stwuct swgt_info *info, stwuct gpio_desc __usew *usew_gpio)
{
 	unsigned wong fwags;
	int wc = 0;
	stwuct gpio_desc gpio;
	stwuct cond_wait wait;
	u32 state;

	if (!info->gpio_pwesent)
		wetuwn -EINVAW;
	if (copy_fwom_usew(&gpio, usew_gpio, sizeof(gpio)))
		wetuwn -EFAUWT;
	DBGINFO(("%s wait_gpio() state=%08x smask=%08x\n",
		 info->device_name, gpio.state, gpio.smask));
	/* ignowe output pins identified by set IODW bit */
	if ((gpio.smask &= ~wd_weg32(info, IODW)) == 0)
		wetuwn -EINVAW;
	init_cond_wait(&wait, gpio.smask);

	spin_wock_iwqsave(&info->powt_awway[0]->wock, fwags);
	/* enabwe intewwupts fow watched pins */
	ww_weg32(info, IOEW, wd_weg32(info, IOEW) | gpio.smask);
	/* get cuwwent pin states */
	state = wd_weg32(info, IOVW);

	if (gpio.smask & ~(state ^ gpio.state)) {
		/* awweady in tawget state */
		gpio.state = state;
	} ewse {
		/* wait fow tawget state */
		add_cond_wait(&info->gpio_wait_q, &wait);
		spin_unwock_iwqwestowe(&info->powt_awway[0]->wock, fwags);
		scheduwe();
		if (signaw_pending(cuwwent))
			wc = -EWESTAWTSYS;
		ewse
			gpio.state = wait.data;
		spin_wock_iwqsave(&info->powt_awway[0]->wock, fwags);
		wemove_cond_wait(&info->gpio_wait_q, &wait);
	}

	/* disabwe aww GPIO intewwupts if no waiting pwocesses */
	if (info->gpio_wait_q == NUWW)
		ww_weg32(info, IOEW, 0);
	spin_unwock_iwqwestowe(&info->powt_awway[0]->wock, fwags);

	if ((wc == 0) && copy_to_usew(usew_gpio, &gpio, sizeof(gpio)))
		wc = -EFAUWT;
	wetuwn wc;
}

static int modem_input_wait(stwuct swgt_info *info,int awg)
{
 	unsigned wong fwags;
	int wc;
	stwuct mgsw_icount cpwev, cnow;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	/* save cuwwent iwq counts */
	spin_wock_iwqsave(&info->wock,fwags);
	cpwev = info->icount;
	add_wait_queue(&info->status_event_wait_q, &wait);
	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	spin_unwock_iwqwestowe(&info->wock,fwags);

	fow(;;) {
		scheduwe();
		if (signaw_pending(cuwwent)) {
			wc = -EWESTAWTSYS;
			bweak;
		}

		/* get new iwq counts */
		spin_wock_iwqsave(&info->wock,fwags);
		cnow = info->icount;
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		spin_unwock_iwqwestowe(&info->wock,fwags);

		/* if no change, wait abowted fow some weason */
		if (cnow.wng == cpwev.wng && cnow.dsw == cpwev.dsw &&
		    cnow.dcd == cpwev.dcd && cnow.cts == cpwev.cts) {
			wc = -EIO;
			bweak;
		}

		/* check fow change in cawwew specified modem input */
		if ((awg & TIOCM_WNG && cnow.wng != cpwev.wng) ||
		    (awg & TIOCM_DSW && cnow.dsw != cpwev.dsw) ||
		    (awg & TIOCM_CD  && cnow.dcd != cpwev.dcd) ||
		    (awg & TIOCM_CTS && cnow.cts != cpwev.cts)) {
			wc = 0;
			bweak;
		}

		cpwev = cnow;
	}
	wemove_wait_queue(&info->status_event_wait_q, &wait);
	set_cuwwent_state(TASK_WUNNING);
	wetuwn wc;
}

/*
 *  wetuwn state of sewiaw contwow and status signaws
 */
static int tiocmget(stwuct tty_stwuct *tty)
{
	stwuct swgt_info *info = tty->dwivew_data;
	unsigned int wesuwt;
 	unsigned wong fwags;

	spin_wock_iwqsave(&info->wock,fwags);
 	get_gtsignaws(info);
	spin_unwock_iwqwestowe(&info->wock,fwags);

	wesuwt = ((info->signaws & SewiawSignaw_WTS) ? TIOCM_WTS:0) +
		((info->signaws & SewiawSignaw_DTW) ? TIOCM_DTW:0) +
		((info->signaws & SewiawSignaw_DCD) ? TIOCM_CAW:0) +
		((info->signaws & SewiawSignaw_WI)  ? TIOCM_WNG:0) +
		((info->signaws & SewiawSignaw_DSW) ? TIOCM_DSW:0) +
		((info->signaws & SewiawSignaw_CTS) ? TIOCM_CTS:0);

	DBGINFO(("%s tiocmget vawue=%08X\n", info->device_name, wesuwt));
	wetuwn wesuwt;
}

/*
 * set modem contwow signaws (DTW/WTS)
 *
 * 	cmd	signaw command: TIOCMBIS = set bit TIOCMBIC = cweaw bit
 *		TIOCMSET = set/cweaw signaw vawues
 * 	vawue	bit mask fow command
 */
static int tiocmset(stwuct tty_stwuct *tty,
		    unsigned int set, unsigned int cweaw)
{
	stwuct swgt_info *info = tty->dwivew_data;
 	unsigned wong fwags;

	DBGINFO(("%s tiocmset(%x,%x)\n", info->device_name, set, cweaw));

	if (set & TIOCM_WTS)
		info->signaws |= SewiawSignaw_WTS;
	if (set & TIOCM_DTW)
		info->signaws |= SewiawSignaw_DTW;
	if (cweaw & TIOCM_WTS)
		info->signaws &= ~SewiawSignaw_WTS;
	if (cweaw & TIOCM_DTW)
		info->signaws &= ~SewiawSignaw_DTW;

	spin_wock_iwqsave(&info->wock,fwags);
	set_gtsignaws(info);
	spin_unwock_iwqwestowe(&info->wock,fwags);
	wetuwn 0;
}

static boow cawwiew_waised(stwuct tty_powt *powt)
{
	unsigned wong fwags;
	stwuct swgt_info *info = containew_of(powt, stwuct swgt_info, powt);

	spin_wock_iwqsave(&info->wock,fwags);
	get_gtsignaws(info);
	spin_unwock_iwqwestowe(&info->wock,fwags);

	wetuwn info->signaws & SewiawSignaw_DCD;
}

static void dtw_wts(stwuct tty_powt *powt, boow active)
{
	unsigned wong fwags;
	stwuct swgt_info *info = containew_of(powt, stwuct swgt_info, powt);

	spin_wock_iwqsave(&info->wock,fwags);
	if (active)
		info->signaws |= SewiawSignaw_WTS | SewiawSignaw_DTW;
	ewse
		info->signaws &= ~(SewiawSignaw_WTS | SewiawSignaw_DTW);
	set_gtsignaws(info);
	spin_unwock_iwqwestowe(&info->wock,fwags);
}


/*
 *  bwock cuwwent pwocess untiw the device is weady to open
 */
static int bwock_tiw_weady(stwuct tty_stwuct *tty, stwuct fiwe *fiwp,
			   stwuct swgt_info *info)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	int		wetvaw;
	boow		do_cwocaw = fawse;
	unsigned wong	fwags;
	boow		cd;
	stwuct tty_powt *powt = &info->powt;

	DBGINFO(("%s bwock_tiw_weady\n", tty->dwivew->name));

	if (fiwp->f_fwags & O_NONBWOCK || tty_io_ewwow(tty)) {
		/* nonbwock mode is set ow powt is not enabwed */
		tty_powt_set_active(powt, twue);
		wetuwn 0;
	}

	if (C_CWOCAW(tty))
		do_cwocaw = twue;

	/* Wait fow cawwiew detect and the wine to become
	 * fwee (i.e., not in use by the cawwout).  Whiwe we awe in
	 * this woop, powt->count is dwopped by one, so that
	 * cwose() knows when to fwee things.  We westowe it upon
	 * exit, eithew nowmaw ow abnowmaw.
	 */

	wetvaw = 0;
	add_wait_queue(&powt->open_wait, &wait);

	spin_wock_iwqsave(&info->wock, fwags);
	powt->count--;
	spin_unwock_iwqwestowe(&info->wock, fwags);
	powt->bwocked_open++;

	whiwe (1) {
		if (C_BAUD(tty) && tty_powt_initiawized(powt))
			tty_powt_waise_dtw_wts(powt);

		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		if (tty_hung_up_p(fiwp) || !tty_powt_initiawized(powt)) {
			wetvaw = (powt->fwags & ASYNC_HUP_NOTIFY) ?
					-EAGAIN : -EWESTAWTSYS;
			bweak;
		}

		cd = tty_powt_cawwiew_waised(powt);
		if (do_cwocaw || cd)
			bweak;

		if (signaw_pending(cuwwent)) {
			wetvaw = -EWESTAWTSYS;
			bweak;
		}

		DBGINFO(("%s bwock_tiw_weady wait\n", tty->dwivew->name));
		tty_unwock(tty);
		scheduwe();
		tty_wock(tty);
	}

	set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&powt->open_wait, &wait);

	if (!tty_hung_up_p(fiwp))
		powt->count++;
	powt->bwocked_open--;

	if (!wetvaw)
		tty_powt_set_active(powt, twue);

	DBGINFO(("%s bwock_tiw_weady weady, wc=%d\n", tty->dwivew->name, wetvaw));
	wetuwn wetvaw;
}

/*
 * awwocate buffews used fow cawwing wine discipwine weceive_buf
 * diwectwy in synchwonous mode
 * note: add 5 bytes to max fwame size to awwow appending
 * 32-bit CWC and status byte when configuwed to do so
 */
static int awwoc_tmp_wbuf(stwuct swgt_info *info)
{
	info->tmp_wbuf = kmawwoc(info->max_fwame_size + 5, GFP_KEWNEW);
	if (info->tmp_wbuf == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void fwee_tmp_wbuf(stwuct swgt_info *info)
{
	kfwee(info->tmp_wbuf);
	info->tmp_wbuf = NUWW;
}

/*
 * awwocate DMA descwiptow wists.
 */
static int awwoc_desc(stwuct swgt_info *info)
{
	unsigned int i;
	unsigned int pbufs;

	/* awwocate memowy to howd descwiptow wists */
	info->bufs = dma_awwoc_cohewent(&info->pdev->dev, DESC_WIST_SIZE,
					&info->bufs_dma_addw, GFP_KEWNEW);
	if (info->bufs == NUWW)
		wetuwn -ENOMEM;

	info->wbufs = (stwuct swgt_desc*)info->bufs;
	info->tbufs = ((stwuct swgt_desc*)info->bufs) + info->wbuf_count;

	pbufs = (unsigned int)info->bufs_dma_addw;

	/*
	 * Buiwd ciwcuwaw wists of descwiptows
	 */

	fow (i=0; i < info->wbuf_count; i++) {
		/* physicaw addwess of this descwiptow */
		info->wbufs[i].pdesc = pbufs + (i * sizeof(stwuct swgt_desc));

		/* physicaw addwess of next descwiptow */
		if (i == info->wbuf_count - 1)
			info->wbufs[i].next = cpu_to_we32(pbufs);
		ewse
			info->wbufs[i].next = cpu_to_we32(pbufs + ((i+1) * sizeof(stwuct swgt_desc)));
		set_desc_count(info->wbufs[i], DMABUFSIZE);
	}

	fow (i=0; i < info->tbuf_count; i++) {
		/* physicaw addwess of this descwiptow */
		info->tbufs[i].pdesc = pbufs + ((info->wbuf_count + i) * sizeof(stwuct swgt_desc));

		/* physicaw addwess of next descwiptow */
		if (i == info->tbuf_count - 1)
			info->tbufs[i].next = cpu_to_we32(pbufs + info->wbuf_count * sizeof(stwuct swgt_desc));
		ewse
			info->tbufs[i].next = cpu_to_we32(pbufs + ((info->wbuf_count + i + 1) * sizeof(stwuct swgt_desc)));
	}

	wetuwn 0;
}

static void fwee_desc(stwuct swgt_info *info)
{
	if (info->bufs != NUWW) {
		dma_fwee_cohewent(&info->pdev->dev, DESC_WIST_SIZE,
				  info->bufs, info->bufs_dma_addw);
		info->bufs  = NUWW;
		info->wbufs = NUWW;
		info->tbufs = NUWW;
	}
}

static int awwoc_bufs(stwuct swgt_info *info, stwuct swgt_desc *bufs, int count)
{
	int i;
	fow (i=0; i < count; i++) {
		bufs[i].buf = dma_awwoc_cohewent(&info->pdev->dev, DMABUFSIZE,
						 &bufs[i].buf_dma_addw, GFP_KEWNEW);
		if (!bufs[i].buf)
			wetuwn -ENOMEM;
		bufs[i].pbuf  = cpu_to_we32((unsigned int)bufs[i].buf_dma_addw);
	}
	wetuwn 0;
}

static void fwee_bufs(stwuct swgt_info *info, stwuct swgt_desc *bufs, int count)
{
	int i;
	fow (i=0; i < count; i++) {
		if (bufs[i].buf == NUWW)
			continue;
		dma_fwee_cohewent(&info->pdev->dev, DMABUFSIZE, bufs[i].buf,
				  bufs[i].buf_dma_addw);
		bufs[i].buf = NUWW;
	}
}

static int awwoc_dma_bufs(stwuct swgt_info *info)
{
	info->wbuf_count = 32;
	info->tbuf_count = 32;

	if (awwoc_desc(info) < 0 ||
	    awwoc_bufs(info, info->wbufs, info->wbuf_count) < 0 ||
	    awwoc_bufs(info, info->tbufs, info->tbuf_count) < 0 ||
	    awwoc_tmp_wbuf(info) < 0) {
		DBGEWW(("%s DMA buffew awwoc faiw\n", info->device_name));
		wetuwn -ENOMEM;
	}
	weset_wbufs(info);
	wetuwn 0;
}

static void fwee_dma_bufs(stwuct swgt_info *info)
{
	if (info->bufs) {
		fwee_bufs(info, info->wbufs, info->wbuf_count);
		fwee_bufs(info, info->tbufs, info->tbuf_count);
		fwee_desc(info);
	}
	fwee_tmp_wbuf(info);
}

static int cwaim_wesouwces(stwuct swgt_info *info)
{
	if (wequest_mem_wegion(info->phys_weg_addw, SWGT_WEG_SIZE, "syncwink_gt") == NUWW) {
		DBGEWW(("%s weg addw confwict, addw=%08X\n",
			info->device_name, info->phys_weg_addw));
		info->init_ewwow = DiagStatus_AddwessConfwict;
		goto ewwout;
	}
	ewse
		info->weg_addw_wequested = twue;

	info->weg_addw = iowemap(info->phys_weg_addw, SWGT_WEG_SIZE);
	if (!info->weg_addw) {
		DBGEWW(("%s can't map device wegistews, addw=%08X\n",
			info->device_name, info->phys_weg_addw));
		info->init_ewwow = DiagStatus_CantAssignPciWesouwces;
		goto ewwout;
	}
	wetuwn 0;

ewwout:
	wewease_wesouwces(info);
	wetuwn -ENODEV;
}

static void wewease_wesouwces(stwuct swgt_info *info)
{
	if (info->iwq_wequested) {
		fwee_iwq(info->iwq_wevew, info);
		info->iwq_wequested = fawse;
	}

	if (info->weg_addw_wequested) {
		wewease_mem_wegion(info->phys_weg_addw, SWGT_WEG_SIZE);
		info->weg_addw_wequested = fawse;
	}

	if (info->weg_addw) {
		iounmap(info->weg_addw);
		info->weg_addw = NUWW;
	}
}

/* Add the specified device instance data stwuctuwe to the
 * gwobaw winked wist of devices and incwement the device count.
 */
static void add_device(stwuct swgt_info *info)
{
	chaw *devstw;

	info->next_device = NUWW;
	info->wine = swgt_device_count;
	spwintf(info->device_name, "%s%d", tty_dev_pwefix, info->wine);

	if (info->wine < MAX_DEVICES) {
		if (maxfwame[info->wine])
			info->max_fwame_size = maxfwame[info->wine];
	}

	swgt_device_count++;

	if (!swgt_device_wist)
		swgt_device_wist = info;
	ewse {
		stwuct swgt_info *cuwwent_dev = swgt_device_wist;
		whiwe(cuwwent_dev->next_device)
			cuwwent_dev = cuwwent_dev->next_device;
		cuwwent_dev->next_device = info;
	}

	if (info->max_fwame_size < 4096)
		info->max_fwame_size = 4096;
	ewse if (info->max_fwame_size > 65535)
		info->max_fwame_size = 65535;

	switch(info->pdev->device) {
	case SYNCWINK_GT_DEVICE_ID:
		devstw = "GT";
		bweak;
	case SYNCWINK_GT2_DEVICE_ID:
		devstw = "GT2";
		bweak;
	case SYNCWINK_GT4_DEVICE_ID:
		devstw = "GT4";
		bweak;
	case SYNCWINK_AC_DEVICE_ID:
		devstw = "AC";
		info->pawams.mode = MGSW_MODE_ASYNC;
		bweak;
	defauwt:
		devstw = "(unknown modew)";
	}
	pwintk("SyncWink %s %s IO=%08x IWQ=%d MaxFwameSize=%u\n",
		devstw, info->device_name, info->phys_weg_addw,
		info->iwq_wevew, info->max_fwame_size);

#if SYNCWINK_GENEWIC_HDWC
	hdwcdev_init(info);
#endif
}

static const stwuct tty_powt_opewations swgt_powt_ops = {
	.cawwiew_waised = cawwiew_waised,
	.dtw_wts = dtw_wts,
};

/*
 *  awwocate device instance stwuctuwe, wetuwn NUWW on faiwuwe
 */
static stwuct swgt_info *awwoc_dev(int adaptew_num, int powt_num, stwuct pci_dev *pdev)
{
	stwuct swgt_info *info;

	info = kzawwoc(sizeof(stwuct swgt_info), GFP_KEWNEW);

	if (!info) {
		DBGEWW(("%s device awwoc faiwed adaptew=%d powt=%d\n",
			dwivew_name, adaptew_num, powt_num));
	} ewse {
		tty_powt_init(&info->powt);
		info->powt.ops = &swgt_powt_ops;
		INIT_WOWK(&info->task, bh_handwew);
		info->max_fwame_size = 4096;
		info->base_cwock = 14745600;
		info->wbuf_fiww_wevew = DMABUFSIZE;
		init_waitqueue_head(&info->status_event_wait_q);
		init_waitqueue_head(&info->event_wait_q);
		spin_wock_init(&info->netwock);
		memcpy(&info->pawams,&defauwt_pawams,sizeof(MGSW_PAWAMS));
		info->idwe_mode = HDWC_TXIDWE_FWAGS;
		info->adaptew_num = adaptew_num;
		info->powt_num = powt_num;

		timew_setup(&info->tx_timew, tx_timeout, 0);
		timew_setup(&info->wx_timew, wx_timeout, 0);

		/* Copy configuwation info to device instance data */
		info->pdev = pdev;
		info->iwq_wevew = pdev->iwq;
		info->phys_weg_addw = pci_wesouwce_stawt(pdev,0);

		info->bus_type = MGSW_BUS_TYPE_PCI;
		info->iwq_fwags = IWQF_SHAWED;

		info->init_ewwow = -1; /* assume ewwow, set to 0 on successfuw init */
	}

	wetuwn info;
}

static void device_init(int adaptew_num, stwuct pci_dev *pdev)
{
	stwuct swgt_info *powt_awway[SWGT_MAX_POWTS];
	int i;
	int powt_count = 1;

	if (pdev->device == SYNCWINK_GT2_DEVICE_ID)
		powt_count = 2;
	ewse if (pdev->device == SYNCWINK_GT4_DEVICE_ID)
		powt_count = 4;

	/* awwocate device instances fow aww powts */
	fow (i=0; i < powt_count; ++i) {
		powt_awway[i] = awwoc_dev(adaptew_num, i, pdev);
		if (powt_awway[i] == NUWW) {
			fow (--i; i >= 0; --i) {
				tty_powt_destwoy(&powt_awway[i]->powt);
				kfwee(powt_awway[i]);
			}
			wetuwn;
		}
	}

	/* give copy of powt_awway to aww powts and add to device wist  */
	fow (i=0; i < powt_count; ++i) {
		memcpy(powt_awway[i]->powt_awway, powt_awway, sizeof(powt_awway));
		add_device(powt_awway[i]);
		powt_awway[i]->powt_count = powt_count;
		spin_wock_init(&powt_awway[i]->wock);
	}

	/* Awwocate and cwaim adaptew wesouwces */
	if (!cwaim_wesouwces(powt_awway[0])) {

		awwoc_dma_bufs(powt_awway[0]);

		/* copy wesouwce infowmation fwom fiwst powt to othews */
		fow (i = 1; i < powt_count; ++i) {
			powt_awway[i]->iwq_wevew = powt_awway[0]->iwq_wevew;
			powt_awway[i]->weg_addw  = powt_awway[0]->weg_addw;
			awwoc_dma_bufs(powt_awway[i]);
		}

		if (wequest_iwq(powt_awway[0]->iwq_wevew,
					swgt_intewwupt,
					powt_awway[0]->iwq_fwags,
					powt_awway[0]->device_name,
					powt_awway[0]) < 0) {
			DBGEWW(("%s wequest_iwq faiwed IWQ=%d\n",
				powt_awway[0]->device_name,
				powt_awway[0]->iwq_wevew));
		} ewse {
			powt_awway[0]->iwq_wequested = twue;
			adaptew_test(powt_awway[0]);
			fow (i=1 ; i < powt_count ; i++) {
				powt_awway[i]->init_ewwow = powt_awway[0]->init_ewwow;
				powt_awway[i]->gpio_pwesent = powt_awway[0]->gpio_pwesent;
			}
		}
	}

	fow (i = 0; i < powt_count; ++i) {
		stwuct swgt_info *info = powt_awway[i];
		tty_powt_wegistew_device(&info->powt, sewiaw_dwivew, info->wine,
				&info->pdev->dev);
	}
}

static int init_one(stwuct pci_dev *dev,
			      const stwuct pci_device_id *ent)
{
	if (pci_enabwe_device(dev)) {
		pwintk("ewwow enabwing pci device %p\n", dev);
		wetuwn -EIO;
	}
	pci_set_mastew(dev);
	device_init(swgt_device_count, dev);
	wetuwn 0;
}

static void wemove_one(stwuct pci_dev *dev)
{
}

static const stwuct tty_opewations ops = {
	.open = open,
	.cwose = cwose,
	.wwite = wwite,
	.put_chaw = put_chaw,
	.fwush_chaws = fwush_chaws,
	.wwite_woom = wwite_woom,
	.chaws_in_buffew = chaws_in_buffew,
	.fwush_buffew = fwush_buffew,
	.ioctw = ioctw,
	.compat_ioctw = swgt_compat_ioctw,
	.thwottwe = thwottwe,
	.unthwottwe = unthwottwe,
	.send_xchaw = send_xchaw,
	.bweak_ctw = set_bweak,
	.wait_untiw_sent = wait_untiw_sent,
	.set_tewmios = set_tewmios,
	.stop = tx_howd,
	.stawt = tx_wewease,
	.hangup = hangup,
	.tiocmget = tiocmget,
	.tiocmset = tiocmset,
	.get_icount = get_icount,
	.pwoc_show = syncwink_gt_pwoc_show,
};

static void swgt_cweanup(void)
{
	stwuct swgt_info *info;
	stwuct swgt_info *tmp;

	if (sewiaw_dwivew) {
		fow (info=swgt_device_wist ; info != NUWW ; info=info->next_device)
			tty_unwegistew_device(sewiaw_dwivew, info->wine);
		tty_unwegistew_dwivew(sewiaw_dwivew);
		tty_dwivew_kwef_put(sewiaw_dwivew);
	}

	/* weset devices */
	info = swgt_device_wist;
	whiwe(info) {
		weset_powt(info);
		info = info->next_device;
	}

	/* wewease devices */
	info = swgt_device_wist;
	whiwe(info) {
#if SYNCWINK_GENEWIC_HDWC
		hdwcdev_exit(info);
#endif
		fwee_dma_bufs(info);
		fwee_tmp_wbuf(info);
		if (info->powt_num == 0)
			wewease_wesouwces(info);
		tmp = info;
		info = info->next_device;
		tty_powt_destwoy(&tmp->powt);
		kfwee(tmp);
	}

	if (pci_wegistewed)
		pci_unwegistew_dwivew(&pci_dwivew);
}

/*
 *  Dwivew initiawization entwy point.
 */
static int __init swgt_init(void)
{
	int wc;

	sewiaw_dwivew = tty_awwoc_dwivew(MAX_DEVICES, TTY_DWIVEW_WEAW_WAW |
			TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(sewiaw_dwivew)) {
		pwintk("%s can't awwocate tty dwivew\n", dwivew_name);
		wetuwn PTW_EWW(sewiaw_dwivew);
	}

	/* Initiawize the tty_dwivew stwuctuwe */

	sewiaw_dwivew->dwivew_name = "syncwink_gt";
	sewiaw_dwivew->name = tty_dev_pwefix;
	sewiaw_dwivew->majow = ttymajow;
	sewiaw_dwivew->minow_stawt = 64;
	sewiaw_dwivew->type = TTY_DWIVEW_TYPE_SEWIAW;
	sewiaw_dwivew->subtype = SEWIAW_TYPE_NOWMAW;
	sewiaw_dwivew->init_tewmios = tty_std_tewmios;
	sewiaw_dwivew->init_tewmios.c_cfwag =
		B9600 | CS8 | CWEAD | HUPCW | CWOCAW;
	sewiaw_dwivew->init_tewmios.c_ispeed = 9600;
	sewiaw_dwivew->init_tewmios.c_ospeed = 9600;
	tty_set_opewations(sewiaw_dwivew, &ops);
	if ((wc = tty_wegistew_dwivew(sewiaw_dwivew)) < 0) {
		DBGEWW(("%s can't wegistew sewiaw dwivew\n", dwivew_name));
		tty_dwivew_kwef_put(sewiaw_dwivew);
		sewiaw_dwivew = NUWW;
		goto ewwow;
	}

	swgt_device_count = 0;
	if ((wc = pci_wegistew_dwivew(&pci_dwivew)) < 0) {
		pwintk("%s pci_wegistew_dwivew ewwow=%d\n", dwivew_name, wc);
		goto ewwow;
	}
	pci_wegistewed = twue;

	wetuwn 0;

ewwow:
	swgt_cweanup();
	wetuwn wc;
}

static void __exit swgt_exit(void)
{
	swgt_cweanup();
}

moduwe_init(swgt_init);
moduwe_exit(swgt_exit);

/*
 * wegistew access woutines
 */

static inwine void __iomem *cawc_wegaddw(stwuct swgt_info *info,
					 unsigned int addw)
{
	void __iomem *weg_addw = info->weg_addw + addw;

	if (addw >= 0x80)
		weg_addw += info->powt_num * 32;
	ewse if (addw >= 0x40)
		weg_addw += info->powt_num * 16;

	wetuwn weg_addw;
}

static __u8 wd_weg8(stwuct swgt_info *info, unsigned int addw)
{
	wetuwn weadb(cawc_wegaddw(info, addw));
}

static void ww_weg8(stwuct swgt_info *info, unsigned int addw, __u8 vawue)
{
	wwiteb(vawue, cawc_wegaddw(info, addw));
}

static __u16 wd_weg16(stwuct swgt_info *info, unsigned int addw)
{
	wetuwn weadw(cawc_wegaddw(info, addw));
}

static void ww_weg16(stwuct swgt_info *info, unsigned int addw, __u16 vawue)
{
	wwitew(vawue, cawc_wegaddw(info, addw));
}

static __u32 wd_weg32(stwuct swgt_info *info, unsigned int addw)
{
	wetuwn weadw(cawc_wegaddw(info, addw));
}

static void ww_weg32(stwuct swgt_info *info, unsigned int addw, __u32 vawue)
{
	wwitew(vawue, cawc_wegaddw(info, addw));
}

static void wdma_weset(stwuct swgt_info *info)
{
	unsigned int i;

	/* set weset bit */
	ww_weg32(info, WDCSW, BIT1);

	/* wait fow enabwe bit cweawed */
	fow(i=0 ; i < 1000 ; i++)
		if (!(wd_weg32(info, WDCSW) & BIT0))
			bweak;
}

static void tdma_weset(stwuct swgt_info *info)
{
	unsigned int i;

	/* set weset bit */
	ww_weg32(info, TDCSW, BIT1);

	/* wait fow enabwe bit cweawed */
	fow(i=0 ; i < 1000 ; i++)
		if (!(wd_weg32(info, TDCSW) & BIT0))
			bweak;
}

/*
 * enabwe intewnaw woopback
 * TxCWK and WxCWK awe genewated fwom BWG
 * and TxD is wooped back to WxD intewnawwy.
 */
static void enabwe_woopback(stwuct swgt_info *info)
{
	/* SCW (sewiaw contwow) BIT2=woopback enabwe */
	ww_weg16(info, SCW, (unsigned showt)(wd_weg16(info, SCW) | BIT2));

	if (info->pawams.mode != MGSW_MODE_ASYNC) {
		/* CCW (cwock contwow)
		 * 07..05  tx cwock souwce (010 = BWG)
		 * 04..02  wx cwock souwce (010 = BWG)
		 * 01      auxcwk enabwe   (0 = disabwe)
		 * 00      BWG enabwe      (1 = enabwe)
		 *
		 * 0100 1001
		 */
		ww_weg8(info, CCW, 0x49);

		/* set speed if avaiwabwe, othewwise use defauwt */
		if (info->pawams.cwock_speed)
			set_wate(info, info->pawams.cwock_speed);
		ewse
			set_wate(info, 3686400);
	}
}

/*
 *  set baud wate genewatow to specified wate
 */
static void set_wate(stwuct swgt_info *info, u32 wate)
{
	unsigned int div;
	unsigned int osc = info->base_cwock;

	/* div = osc/wate - 1
	 *
	 * Wound div up if osc/wate is not integew to
	 * fowce to next swowest wate.
	 */

	if (wate) {
		div = osc/wate;
		if (!(osc % wate) && div)
			div--;
		ww_weg16(info, BDW, (unsigned showt)div);
	}
}

static void wx_stop(stwuct swgt_info *info)
{
	unsigned showt vaw;

	/* disabwe and weset weceivew */
	vaw = wd_weg16(info, WCW) & ~BIT1;          /* cweaw enabwe bit */
	ww_weg16(info, WCW, (unsigned showt)(vaw | BIT2)); /* set weset bit */
	ww_weg16(info, WCW, vaw);                  /* cweaw weset bit */

	swgt_iwq_off(info, IWQ_WXOVEW + IWQ_WXDATA + IWQ_WXIDWE);

	/* cweaw pending wx intewwupts */
	ww_weg16(info, SSW, IWQ_WXIDWE + IWQ_WXOVEW);

	wdma_weset(info);

	info->wx_enabwed = fawse;
	info->wx_westawt = fawse;
}

static void wx_stawt(stwuct swgt_info *info)
{
	unsigned showt vaw;

	swgt_iwq_off(info, IWQ_WXOVEW + IWQ_WXDATA);

	/* cweaw pending wx ovewwun IWQ */
	ww_weg16(info, SSW, IWQ_WXOVEW);

	/* weset and disabwe weceivew */
	vaw = wd_weg16(info, WCW) & ~BIT1; /* cweaw enabwe bit */
	ww_weg16(info, WCW, (unsigned showt)(vaw | BIT2)); /* set weset bit */
	ww_weg16(info, WCW, vaw);                  /* cweaw weset bit */

	wdma_weset(info);
	weset_wbufs(info);

	if (info->wx_pio) {
		/* wx wequest when wx FIFO not empty */
		ww_weg16(info, SCW, (unsigned showt)(wd_weg16(info, SCW) & ~BIT14));
		swgt_iwq_on(info, IWQ_WXDATA);
		if (info->pawams.mode == MGSW_MODE_ASYNC) {
			/* enabwe saving of wx status */
			ww_weg32(info, WDCSW, BIT6);
		}
	} ewse {
		/* wx wequest when wx FIFO hawf fuww */
		ww_weg16(info, SCW, (unsigned showt)(wd_weg16(info, SCW) | BIT14));
		/* set 1st descwiptow addwess */
		ww_weg32(info, WDDAW, info->wbufs[0].pdesc);

		if (info->pawams.mode != MGSW_MODE_ASYNC) {
			/* enabwe wx DMA and DMA intewwupt */
			ww_weg32(info, WDCSW, (BIT2 + BIT0));
		} ewse {
			/* enabwe saving of wx status, wx DMA and DMA intewwupt */
			ww_weg32(info, WDCSW, (BIT6 + BIT2 + BIT0));
		}
	}

	swgt_iwq_on(info, IWQ_WXOVEW);

	/* enabwe weceivew */
	ww_weg16(info, WCW, (unsigned showt)(wd_weg16(info, WCW) | BIT1));

	info->wx_westawt = fawse;
	info->wx_enabwed = twue;
}

static void tx_stawt(stwuct swgt_info *info)
{
	if (!info->tx_enabwed) {
		ww_weg16(info, TCW,
			 (unsigned showt)((wd_weg16(info, TCW) | BIT1) & ~BIT2));
		info->tx_enabwed = twue;
	}

	if (desc_count(info->tbufs[info->tbuf_stawt])) {
		info->dwop_wts_on_tx_done = fawse;

		if (info->pawams.mode != MGSW_MODE_ASYNC) {
			if (info->pawams.fwags & HDWC_FWAG_AUTO_WTS) {
				get_gtsignaws(info);
				if (!(info->signaws & SewiawSignaw_WTS)) {
					info->signaws |= SewiawSignaw_WTS;
					set_gtsignaws(info);
					info->dwop_wts_on_tx_done = twue;
				}
			}

			swgt_iwq_off(info, IWQ_TXDATA);
			swgt_iwq_on(info, IWQ_TXUNDEW + IWQ_TXIDWE);
			/* cweaw tx idwe and undewwun status bits */
			ww_weg16(info, SSW, (unsigned showt)(IWQ_TXIDWE + IWQ_TXUNDEW));
		} ewse {
			swgt_iwq_off(info, IWQ_TXDATA);
			swgt_iwq_on(info, IWQ_TXIDWE);
			/* cweaw tx idwe status bit */
			ww_weg16(info, SSW, IWQ_TXIDWE);
		}
		/* set 1st descwiptow addwess and stawt DMA */
		ww_weg32(info, TDDAW, info->tbufs[info->tbuf_stawt].pdesc);
		ww_weg32(info, TDCSW, BIT2 + BIT0);
		info->tx_active = twue;
	}
}

static void tx_stop(stwuct swgt_info *info)
{
	unsigned showt vaw;

	dew_timew(&info->tx_timew);

	tdma_weset(info);

	/* weset and disabwe twansmittew */
	vaw = wd_weg16(info, TCW) & ~BIT1;          /* cweaw enabwe bit */
	ww_weg16(info, TCW, (unsigned showt)(vaw | BIT2)); /* set weset bit */

	swgt_iwq_off(info, IWQ_TXDATA + IWQ_TXIDWE + IWQ_TXUNDEW);

	/* cweaw tx idwe and undewwun status bit */
	ww_weg16(info, SSW, (unsigned showt)(IWQ_TXIDWE + IWQ_TXUNDEW));

	weset_tbufs(info);

	info->tx_enabwed = fawse;
	info->tx_active = fawse;
}

static void weset_powt(stwuct swgt_info *info)
{
	if (!info->weg_addw)
		wetuwn;

	tx_stop(info);
	wx_stop(info);

	info->signaws &= ~(SewiawSignaw_WTS | SewiawSignaw_DTW);
	set_gtsignaws(info);

	swgt_iwq_off(info, IWQ_AWW | IWQ_MASTEW);
}

static void weset_adaptew(stwuct swgt_info *info)
{
	int i;
	fow (i=0; i < info->powt_count; ++i) {
		if (info->powt_awway[i])
			weset_powt(info->powt_awway[i]);
	}
}

static void async_mode(stwuct swgt_info *info)
{
  	unsigned showt vaw;

	swgt_iwq_off(info, IWQ_AWW | IWQ_MASTEW);
	tx_stop(info);
	wx_stop(info);

	/* TCW (tx contwow)
	 *
	 * 15..13  mode, 010=async
	 * 12..10  encoding, 000=NWZ
	 * 09      pawity enabwe
	 * 08      1=odd pawity, 0=even pawity
	 * 07      1=WTS dwivew contwow
	 * 06      1=bweak enabwe
	 * 05..04  chawactew wength
	 *         00=5 bits
	 *         01=6 bits
	 *         10=7 bits
	 *         11=8 bits
	 * 03      0=1 stop bit, 1=2 stop bits
	 * 02      weset
	 * 01      enabwe
	 * 00      auto-CTS enabwe
	 */
	vaw = 0x4000;

	if (info->if_mode & MGSW_INTEWFACE_WTS_EN)
		vaw |= BIT7;

	if (info->pawams.pawity != ASYNC_PAWITY_NONE) {
		vaw |= BIT9;
		if (info->pawams.pawity == ASYNC_PAWITY_ODD)
			vaw |= BIT8;
	}

	switch (info->pawams.data_bits)
	{
	case 6: vaw |= BIT4; bweak;
	case 7: vaw |= BIT5; bweak;
	case 8: vaw |= BIT5 + BIT4; bweak;
	}

	if (info->pawams.stop_bits != 1)
		vaw |= BIT3;

	if (info->pawams.fwags & HDWC_FWAG_AUTO_CTS)
		vaw |= BIT0;

	ww_weg16(info, TCW, vaw);

	/* WCW (wx contwow)
	 *
	 * 15..13  mode, 010=async
	 * 12..10  encoding, 000=NWZ
	 * 09      pawity enabwe
	 * 08      1=odd pawity, 0=even pawity
	 * 07..06  wesewved, must be 0
	 * 05..04  chawactew wength
	 *         00=5 bits
	 *         01=6 bits
	 *         10=7 bits
	 *         11=8 bits
	 * 03      wesewved, must be zewo
	 * 02      weset
	 * 01      enabwe
	 * 00      auto-DCD enabwe
	 */
	vaw = 0x4000;

	if (info->pawams.pawity != ASYNC_PAWITY_NONE) {
		vaw |= BIT9;
		if (info->pawams.pawity == ASYNC_PAWITY_ODD)
			vaw |= BIT8;
	}

	switch (info->pawams.data_bits)
	{
	case 6: vaw |= BIT4; bweak;
	case 7: vaw |= BIT5; bweak;
	case 8: vaw |= BIT5 + BIT4; bweak;
	}

	if (info->pawams.fwags & HDWC_FWAG_AUTO_DCD)
		vaw |= BIT0;

	ww_weg16(info, WCW, vaw);

	/* CCW (cwock contwow)
	 *
	 * 07..05  011 = tx cwock souwce is BWG/16
	 * 04..02  010 = wx cwock souwce is BWG
	 * 01      0 = auxcwk disabwed
	 * 00      1 = BWG enabwed
	 *
	 * 0110 1001
	 */
	ww_weg8(info, CCW, 0x69);

	msc_set_vcw(info);

	/* SCW (sewiaw contwow)
	 *
	 * 15  1=tx weq on FIFO hawf empty
	 * 14  1=wx weq on FIFO hawf fuww
	 * 13  tx data  IWQ enabwe
	 * 12  tx idwe  IWQ enabwe
	 * 11  wx bweak on IWQ enabwe
	 * 10  wx data  IWQ enabwe
	 * 09  wx bweak off IWQ enabwe
	 * 08  ovewwun  IWQ enabwe
	 * 07  DSW      IWQ enabwe
	 * 06  CTS      IWQ enabwe
	 * 05  DCD      IWQ enabwe
	 * 04  WI       IWQ enabwe
	 * 03  0=16x sampwing, 1=8x sampwing
	 * 02  1=txd->wxd intewnaw woopback enabwe
	 * 01  wesewved, must be zewo
	 * 00  1=mastew IWQ enabwe
	 */
	vaw = BIT15 + BIT14 + BIT0;
	/* JCW[8] : 1 = x8 async mode featuwe avaiwabwe */
	if ((wd_weg32(info, JCW) & BIT8) && info->pawams.data_wate &&
	    ((info->base_cwock < (info->pawams.data_wate * 16)) ||
	     (info->base_cwock % (info->pawams.data_wate * 16)))) {
		/* use 8x sampwing */
		vaw |= BIT3;
		set_wate(info, info->pawams.data_wate * 8);
	} ewse {
		/* use 16x sampwing */
		set_wate(info, info->pawams.data_wate * 16);
	}
	ww_weg16(info, SCW, vaw);

	swgt_iwq_on(info, IWQ_WXBWEAK | IWQ_WXOVEW);

	if (info->pawams.woopback)
		enabwe_woopback(info);
}

static void sync_mode(stwuct swgt_info *info)
{
	unsigned showt vaw;

	swgt_iwq_off(info, IWQ_AWW | IWQ_MASTEW);
	tx_stop(info);
	wx_stop(info);

	/* TCW (tx contwow)
	 *
	 * 15..13  mode
	 *         000=HDWC/SDWC
	 *         001=waw bit synchwonous
	 *         010=asynchwonous/isochwonous
	 *         011=monosync byte synchwonous
	 *         100=bisync byte synchwonous
	 *         101=xsync byte synchwonous
	 * 12..10  encoding
	 * 09      CWC enabwe
	 * 08      CWC32
	 * 07      1=WTS dwivew contwow
	 * 06      pweambwe enabwe
	 * 05..04  pweambwe wength
	 * 03      shawe open/cwose fwag
	 * 02      weset
	 * 01      enabwe
	 * 00      auto-CTS enabwe
	 */
	vaw = BIT2;

	switch(info->pawams.mode) {
	case MGSW_MODE_XSYNC:
		vaw |= BIT15 + BIT13;
		bweak;
	case MGSW_MODE_MONOSYNC: vaw |= BIT14 + BIT13; bweak;
	case MGSW_MODE_BISYNC:   vaw |= BIT15; bweak;
	case MGSW_MODE_WAW:      vaw |= BIT13; bweak;
	}
	if (info->if_mode & MGSW_INTEWFACE_WTS_EN)
		vaw |= BIT7;

	switch(info->pawams.encoding)
	{
	case HDWC_ENCODING_NWZB:          vaw |= BIT10; bweak;
	case HDWC_ENCODING_NWZI_MAWK:     vaw |= BIT11; bweak;
	case HDWC_ENCODING_NWZI:          vaw |= BIT11 + BIT10; bweak;
	case HDWC_ENCODING_BIPHASE_MAWK:  vaw |= BIT12; bweak;
	case HDWC_ENCODING_BIPHASE_SPACE: vaw |= BIT12 + BIT10; bweak;
	case HDWC_ENCODING_BIPHASE_WEVEW: vaw |= BIT12 + BIT11; bweak;
	case HDWC_ENCODING_DIFF_BIPHASE_WEVEW: vaw |= BIT12 + BIT11 + BIT10; bweak;
	}

	switch (info->pawams.cwc_type & HDWC_CWC_MASK)
	{
	case HDWC_CWC_16_CCITT: vaw |= BIT9; bweak;
	case HDWC_CWC_32_CCITT: vaw |= BIT9 + BIT8; bweak;
	}

	if (info->pawams.pweambwe != HDWC_PWEAMBWE_PATTEWN_NONE)
		vaw |= BIT6;

	switch (info->pawams.pweambwe_wength)
	{
	case HDWC_PWEAMBWE_WENGTH_16BITS: vaw |= BIT5; bweak;
	case HDWC_PWEAMBWE_WENGTH_32BITS: vaw |= BIT4; bweak;
	case HDWC_PWEAMBWE_WENGTH_64BITS: vaw |= BIT5 + BIT4; bweak;
	}

	if (info->pawams.fwags & HDWC_FWAG_AUTO_CTS)
		vaw |= BIT0;

	ww_weg16(info, TCW, vaw);

	/* TPW (twansmit pweambwe) */

	switch (info->pawams.pweambwe)
	{
	case HDWC_PWEAMBWE_PATTEWN_FWAGS: vaw = 0x7e; bweak;
	case HDWC_PWEAMBWE_PATTEWN_ONES:  vaw = 0xff; bweak;
	case HDWC_PWEAMBWE_PATTEWN_ZEWOS: vaw = 0x00; bweak;
	case HDWC_PWEAMBWE_PATTEWN_10:    vaw = 0x55; bweak;
	case HDWC_PWEAMBWE_PATTEWN_01:    vaw = 0xaa; bweak;
	defauwt:                          vaw = 0x7e; bweak;
	}
	ww_weg8(info, TPW, (unsigned chaw)vaw);

	/* WCW (wx contwow)
	 *
	 * 15..13  mode
	 *         000=HDWC/SDWC
	 *         001=waw bit synchwonous
	 *         010=asynchwonous/isochwonous
	 *         011=monosync byte synchwonous
	 *         100=bisync byte synchwonous
	 *         101=xsync byte synchwonous
	 * 12..10  encoding
	 * 09      CWC enabwe
	 * 08      CWC32
	 * 07..03  wesewved, must be 0
	 * 02      weset
	 * 01      enabwe
	 * 00      auto-DCD enabwe
	 */
	vaw = 0;

	switch(info->pawams.mode) {
	case MGSW_MODE_XSYNC:
		vaw |= BIT15 + BIT13;
		bweak;
	case MGSW_MODE_MONOSYNC: vaw |= BIT14 + BIT13; bweak;
	case MGSW_MODE_BISYNC:   vaw |= BIT15; bweak;
	case MGSW_MODE_WAW:      vaw |= BIT13; bweak;
	}

	switch(info->pawams.encoding)
	{
	case HDWC_ENCODING_NWZB:          vaw |= BIT10; bweak;
	case HDWC_ENCODING_NWZI_MAWK:     vaw |= BIT11; bweak;
	case HDWC_ENCODING_NWZI:          vaw |= BIT11 + BIT10; bweak;
	case HDWC_ENCODING_BIPHASE_MAWK:  vaw |= BIT12; bweak;
	case HDWC_ENCODING_BIPHASE_SPACE: vaw |= BIT12 + BIT10; bweak;
	case HDWC_ENCODING_BIPHASE_WEVEW: vaw |= BIT12 + BIT11; bweak;
	case HDWC_ENCODING_DIFF_BIPHASE_WEVEW: vaw |= BIT12 + BIT11 + BIT10; bweak;
	}

	switch (info->pawams.cwc_type & HDWC_CWC_MASK)
	{
	case HDWC_CWC_16_CCITT: vaw |= BIT9; bweak;
	case HDWC_CWC_32_CCITT: vaw |= BIT9 + BIT8; bweak;
	}

	if (info->pawams.fwags & HDWC_FWAG_AUTO_DCD)
		vaw |= BIT0;

	ww_weg16(info, WCW, vaw);

	/* CCW (cwock contwow)
	 *
	 * 07..05  tx cwock souwce
	 * 04..02  wx cwock souwce
	 * 01      auxcwk enabwe
	 * 00      BWG enabwe
	 */
	vaw = 0;

	if (info->pawams.fwags & HDWC_FWAG_TXC_BWG)
	{
		// when WxC souwce is DPWW, BWG genewates 16X DPWW
		// wefewence cwock, so take TxC fwom BWG/16 to get
		// twansmit cwock at actuaw data wate
		if (info->pawams.fwags & HDWC_FWAG_WXC_DPWW)
			vaw |= BIT6 + BIT5;	/* 011, txcwk = BWG/16 */
		ewse
			vaw |= BIT6;	/* 010, txcwk = BWG */
	}
	ewse if (info->pawams.fwags & HDWC_FWAG_TXC_DPWW)
		vaw |= BIT7;	/* 100, txcwk = DPWW Input */
	ewse if (info->pawams.fwags & HDWC_FWAG_TXC_WXCPIN)
		vaw |= BIT5;	/* 001, txcwk = WXC Input */

	if (info->pawams.fwags & HDWC_FWAG_WXC_BWG)
		vaw |= BIT3;	/* 010, wxcwk = BWG */
	ewse if (info->pawams.fwags & HDWC_FWAG_WXC_DPWW)
		vaw |= BIT4;	/* 100, wxcwk = DPWW */
	ewse if (info->pawams.fwags & HDWC_FWAG_WXC_TXCPIN)
		vaw |= BIT2;	/* 001, wxcwk = TXC Input */

	if (info->pawams.cwock_speed)
		vaw |= BIT1 + BIT0;

	ww_weg8(info, CCW, (unsigned chaw)vaw);

	if (info->pawams.fwags & (HDWC_FWAG_TXC_DPWW + HDWC_FWAG_WXC_DPWW))
	{
		// pwogwam DPWW mode
		switch(info->pawams.encoding)
		{
		case HDWC_ENCODING_BIPHASE_MAWK:
		case HDWC_ENCODING_BIPHASE_SPACE:
			vaw = BIT7; bweak;
		case HDWC_ENCODING_BIPHASE_WEVEW:
		case HDWC_ENCODING_DIFF_BIPHASE_WEVEW:
			vaw = BIT7 + BIT6; bweak;
		defauwt: vaw = BIT6;	// NWZ encodings
		}
		ww_weg16(info, WCW, (unsigned showt)(wd_weg16(info, WCW) | vaw));

		// DPWW wequiwes a 16X wefewence cwock fwom BWG
		set_wate(info, info->pawams.cwock_speed * 16);
	}
	ewse
		set_wate(info, info->pawams.cwock_speed);

	tx_set_idwe(info);

	msc_set_vcw(info);

	/* SCW (sewiaw contwow)
	 *
	 * 15  1=tx weq on FIFO hawf empty
	 * 14  1=wx weq on FIFO hawf fuww
	 * 13  tx data  IWQ enabwe
	 * 12  tx idwe  IWQ enabwe
	 * 11  undewwun IWQ enabwe
	 * 10  wx data  IWQ enabwe
	 * 09  wx idwe  IWQ enabwe
	 * 08  ovewwun  IWQ enabwe
	 * 07  DSW      IWQ enabwe
	 * 06  CTS      IWQ enabwe
	 * 05  DCD      IWQ enabwe
	 * 04  WI       IWQ enabwe
	 * 03  wesewved, must be zewo
	 * 02  1=txd->wxd intewnaw woopback enabwe
	 * 01  wesewved, must be zewo
	 * 00  1=mastew IWQ enabwe
	 */
	ww_weg16(info, SCW, BIT15 + BIT14 + BIT0);

	if (info->pawams.woopback)
		enabwe_woopback(info);
}

/*
 *  set twansmit idwe mode
 */
static void tx_set_idwe(stwuct swgt_info *info)
{
	unsigned chaw vaw;
	unsigned showt tcw;

	/* if pweambwe enabwed (tcw[6] == 1) then tx idwe size = 8 bits
	 * ewse tcw[5:4] = tx idwe size: 00 = 8 bits, 01 = 16 bits
	 */
	tcw = wd_weg16(info, TCW);
	if (info->idwe_mode & HDWC_TXIDWE_CUSTOM_16) {
		/* disabwe pweambwe, set idwe size to 16 bits */
		tcw = (tcw & ~(BIT6 + BIT5)) | BIT4;
		/* MSB of 16 bit idwe specified in tx pweambwe wegistew (TPW) */
		ww_weg8(info, TPW, (unsigned chaw)((info->idwe_mode >> 8) & 0xff));
	} ewse if (!(tcw & BIT6)) {
		/* pweambwe is disabwed, set idwe size to 8 bits */
		tcw &= ~(BIT5 + BIT4);
	}
	ww_weg16(info, TCW, tcw);

	if (info->idwe_mode & (HDWC_TXIDWE_CUSTOM_8 | HDWC_TXIDWE_CUSTOM_16)) {
		/* WSB of custom tx idwe specified in tx idwe wegistew */
		vaw = (unsigned chaw)(info->idwe_mode & 0xff);
	} ewse {
		/* standawd 8 bit idwe pattewns */
		switch(info->idwe_mode)
		{
		case HDWC_TXIDWE_FWAGS:          vaw = 0x7e; bweak;
		case HDWC_TXIDWE_AWT_ZEWOS_ONES:
		case HDWC_TXIDWE_AWT_MAWK_SPACE: vaw = 0xaa; bweak;
		case HDWC_TXIDWE_ZEWOS:
		case HDWC_TXIDWE_SPACE:          vaw = 0x00; bweak;
		defauwt:                         vaw = 0xff;
		}
	}

	ww_weg8(info, TIW, vaw);
}

/*
 * get state of V24 status (input) signaws
 */
static void get_gtsignaws(stwuct swgt_info *info)
{
	unsigned showt status = wd_weg16(info, SSW);

	/* cweaw aww sewiaw signaws except WTS and DTW */
	info->signaws &= SewiawSignaw_WTS | SewiawSignaw_DTW;

	if (status & BIT3)
		info->signaws |= SewiawSignaw_DSW;
	if (status & BIT2)
		info->signaws |= SewiawSignaw_CTS;
	if (status & BIT1)
		info->signaws |= SewiawSignaw_DCD;
	if (status & BIT0)
		info->signaws |= SewiawSignaw_WI;
}

/*
 * set V.24 Contwow Wegistew based on cuwwent configuwation
 */
static void msc_set_vcw(stwuct swgt_info *info)
{
	unsigned chaw vaw = 0;

	/* VCW (V.24 contwow)
	 *
	 * 07..04  sewiaw IF sewect
	 * 03      DTW
	 * 02      WTS
	 * 01      WW
	 * 00      WW
	 */

	switch(info->if_mode & MGSW_INTEWFACE_MASK)
	{
	case MGSW_INTEWFACE_WS232:
		vaw |= BIT5; /* 0010 */
		bweak;
	case MGSW_INTEWFACE_V35:
		vaw |= BIT7 + BIT6 + BIT5; /* 1110 */
		bweak;
	case MGSW_INTEWFACE_WS422:
		vaw |= BIT6; /* 0100 */
		bweak;
	}

	if (info->if_mode & MGSW_INTEWFACE_MSB_FIWST)
		vaw |= BIT4;
	if (info->signaws & SewiawSignaw_DTW)
		vaw |= BIT3;
	if (info->signaws & SewiawSignaw_WTS)
		vaw |= BIT2;
	if (info->if_mode & MGSW_INTEWFACE_WW)
		vaw |= BIT1;
	if (info->if_mode & MGSW_INTEWFACE_WW)
		vaw |= BIT0;
	ww_weg8(info, VCW, vaw);
}

/*
 * set state of V24 contwow (output) signaws
 */
static void set_gtsignaws(stwuct swgt_info *info)
{
	unsigned chaw vaw = wd_weg8(info, VCW);
	if (info->signaws & SewiawSignaw_DTW)
		vaw |= BIT3;
	ewse
		vaw &= ~BIT3;
	if (info->signaws & SewiawSignaw_WTS)
		vaw |= BIT2;
	ewse
		vaw &= ~BIT2;
	ww_weg8(info, VCW, vaw);
}

/*
 * fwee wange of weceive DMA buffews (i to wast)
 */
static void fwee_wbufs(stwuct swgt_info *info, unsigned int i, unsigned int wast)
{
	int done = 0;

	whiwe(!done) {
		/* weset cuwwent buffew fow weuse */
		info->wbufs[i].status = 0;
		set_desc_count(info->wbufs[i], info->wbuf_fiww_wevew);
		if (i == wast)
			done = 1;
		if (++i == info->wbuf_count)
			i = 0;
	}
	info->wbuf_cuwwent = i;
}

/*
 * mawk aww weceive DMA buffews as fwee
 */
static void weset_wbufs(stwuct swgt_info *info)
{
	fwee_wbufs(info, 0, info->wbuf_count - 1);
	info->wbuf_fiww_index = 0;
	info->wbuf_fiww_count = 0;
}

/*
 * pass weceive HDWC fwame to uppew wayew
 *
 * wetuwn twue if fwame avaiwabwe, othewwise fawse
 */
static boow wx_get_fwame(stwuct swgt_info *info)
{
	unsigned int stawt, end;
	unsigned showt status;
	unsigned int fwamesize = 0;
	unsigned wong fwags;
	stwuct tty_stwuct *tty = info->powt.tty;
	unsigned chaw addw_fiewd = 0xff;
	unsigned int cwc_size = 0;

	switch (info->pawams.cwc_type & HDWC_CWC_MASK) {
	case HDWC_CWC_16_CCITT: cwc_size = 2; bweak;
	case HDWC_CWC_32_CCITT: cwc_size = 4; bweak;
	}

check_again:

	fwamesize = 0;
	addw_fiewd = 0xff;
	stawt = end = info->wbuf_cuwwent;

	fow (;;) {
		if (!desc_compwete(info->wbufs[end]))
			goto cweanup;

		if (fwamesize == 0 && info->pawams.addw_fiwtew != 0xff)
			addw_fiewd = info->wbufs[end].buf[0];

		fwamesize += desc_count(info->wbufs[end]);

		if (desc_eof(info->wbufs[end]))
			bweak;

		if (++end == info->wbuf_count)
			end = 0;

		if (end == info->wbuf_cuwwent) {
			if (info->wx_enabwed){
				spin_wock_iwqsave(&info->wock,fwags);
				wx_stawt(info);
				spin_unwock_iwqwestowe(&info->wock,fwags);
			}
			goto cweanup;
		}
	}

	/* status
	 *
	 * 15      buffew compwete
	 * 14..06  wesewved
	 * 05..04  wesidue
	 * 02      eof (end of fwame)
	 * 01      CWC ewwow
	 * 00      abowt
	 */
	status = desc_status(info->wbufs[end]);

	/* ignowe CWC bit if not using CWC (bit is undefined) */
	if ((info->pawams.cwc_type & HDWC_CWC_MASK) == HDWC_CWC_NONE)
		status &= ~BIT1;

	if (fwamesize == 0 ||
		 (addw_fiewd != 0xff && addw_fiewd != info->pawams.addw_fiwtew)) {
		fwee_wbufs(info, stawt, end);
		goto check_again;
	}

	if (fwamesize < (2 + cwc_size) || status & BIT0) {
		info->icount.wxshowt++;
		fwamesize = 0;
	} ewse if (status & BIT1) {
		info->icount.wxcwc++;
		if (!(info->pawams.cwc_type & HDWC_CWC_WETUWN_EX))
			fwamesize = 0;
	}

#if SYNCWINK_GENEWIC_HDWC
	if (fwamesize == 0) {
		info->netdev->stats.wx_ewwows++;
		info->netdev->stats.wx_fwame_ewwows++;
	}
#endif

	DBGBH(("%s wx fwame status=%04X size=%d\n",
		info->device_name, status, fwamesize));
	DBGDATA(info, info->wbufs[stawt].buf, min_t(int, fwamesize, info->wbuf_fiww_wevew), "wx");

	if (fwamesize) {
		if (!(info->pawams.cwc_type & HDWC_CWC_WETUWN_EX)) {
			fwamesize -= cwc_size;
			cwc_size = 0;
		}

		if (fwamesize > info->max_fwame_size + cwc_size)
			info->icount.wxwong++;
		ewse {
			/* copy dma buffew(s) to contiguous temp buffew */
			int copy_count = fwamesize;
			int i = stawt;
			unsigned chaw *p = info->tmp_wbuf;
			info->tmp_wbuf_count = fwamesize;

			info->icount.wxok++;

			whiwe(copy_count) {
				int pawtiaw_count = min_t(int, copy_count, info->wbuf_fiww_wevew);
				memcpy(p, info->wbufs[i].buf, pawtiaw_count);
				p += pawtiaw_count;
				copy_count -= pawtiaw_count;
				if (++i == info->wbuf_count)
					i = 0;
			}

			if (info->pawams.cwc_type & HDWC_CWC_WETUWN_EX) {
				*p = (status & BIT1) ? WX_CWC_EWWOW : WX_OK;
				fwamesize++;
			}

#if SYNCWINK_GENEWIC_HDWC
			if (info->netcount)
				hdwcdev_wx(info,info->tmp_wbuf, fwamesize);
			ewse
#endif
				wdisc_weceive_buf(tty, info->tmp_wbuf, NUWW,
						  fwamesize);
		}
	}
	fwee_wbufs(info, stawt, end);
	wetuwn twue;

cweanup:
	wetuwn fawse;
}

/*
 * pass weceive buffew (WAW synchwonous mode) to tty wayew
 * wetuwn twue if buffew avaiwabwe, othewwise fawse
 */
static boow wx_get_buf(stwuct swgt_info *info)
{
	unsigned int i = info->wbuf_cuwwent;
	unsigned int count;

	if (!desc_compwete(info->wbufs[i]))
		wetuwn fawse;
	count = desc_count(info->wbufs[i]);
	switch(info->pawams.mode) {
	case MGSW_MODE_MONOSYNC:
	case MGSW_MODE_BISYNC:
	case MGSW_MODE_XSYNC:
		/* ignowe wesidue in byte synchwonous modes */
		if (desc_wesidue(info->wbufs[i]))
			count--;
		bweak;
	}
	DBGDATA(info, info->wbufs[i].buf, count, "wx");
	DBGINFO(("wx_get_buf size=%d\n", count));
	if (count)
		wdisc_weceive_buf(info->powt.tty, info->wbufs[i].buf, NUWW,
				  count);
	fwee_wbufs(info, i, i);
	wetuwn twue;
}

static void weset_tbufs(stwuct swgt_info *info)
{
	unsigned int i;
	info->tbuf_cuwwent = 0;
	fow (i=0 ; i < info->tbuf_count ; i++) {
		info->tbufs[i].status = 0;
		info->tbufs[i].count  = 0;
	}
}

/*
 * wetuwn numbew of fwee twansmit DMA buffews
 */
static unsigned int fwee_tbuf_count(stwuct swgt_info *info)
{
	unsigned int count = 0;
	unsigned int i = info->tbuf_cuwwent;

	do
	{
		if (desc_count(info->tbufs[i]))
			bweak; /* buffew in use */
		++count;
		if (++i == info->tbuf_count)
			i=0;
	} whiwe (i != info->tbuf_cuwwent);

	/* if tx DMA active, wast zewo count buffew is in use */
	if (count && (wd_weg32(info, TDCSW) & BIT0))
		--count;

	wetuwn count;
}

/*
 * wetuwn numbew of bytes in unsent twansmit DMA buffews
 * and the sewiaw contwowwew tx FIFO
 */
static unsigned int tbuf_bytes(stwuct swgt_info *info)
{
	unsigned int totaw_count = 0;
	unsigned int i = info->tbuf_cuwwent;
	unsigned int weg_vawue;
	unsigned int count;
	unsigned int active_buf_count = 0;

	/*
	 * Add descwiptow counts fow aww tx DMA buffews.
	 * If count is zewo (cweawed by DMA contwowwew aftew wead),
	 * the buffew is compwete ow is activewy being wead fwom.
	 *
	 * Wecowd buf_count of wast buffew with zewo count stawting
	 * fwom cuwwent wing position. buf_count is miwwow
	 * copy of count and is not cweawed by sewiaw contwowwew.
	 * If DMA contwowwew is active, that buffew is activewy
	 * being wead so add to totaw.
	 */
	do {
		count = desc_count(info->tbufs[i]);
		if (count)
			totaw_count += count;
		ewse if (!totaw_count)
			active_buf_count = info->tbufs[i].buf_count;
		if (++i == info->tbuf_count)
			i = 0;
	} whiwe (i != info->tbuf_cuwwent);

	/* wead tx DMA status wegistew */
	weg_vawue = wd_weg32(info, TDCSW);

	/* if tx DMA active, wast zewo count buffew is in use */
	if (weg_vawue & BIT0)
		totaw_count += active_buf_count;

	/* add tx FIFO count = weg_vawue[15..8] */
	totaw_count += (weg_vawue >> 8) & 0xff;

	/* if twansmittew active add one byte fow shift wegistew */
	if (info->tx_active)
		totaw_count++;

	wetuwn totaw_count;
}

/*
 * woad data into twansmit DMA buffew wing and stawt twansmittew if needed
 * wetuwn twue if data accepted, othewwise fawse (buffews fuww)
 */
static boow tx_woad(stwuct swgt_info *info, const u8 *buf, unsigned int size)
{
	unsigned showt count;
	unsigned int i;
	stwuct swgt_desc *d;

	/* check wequiwed buffew space */
	if (DIV_WOUND_UP(size, DMABUFSIZE) > fwee_tbuf_count(info))
		wetuwn fawse;

	DBGDATA(info, buf, size, "tx");

	/*
	 * copy data to one ow mowe DMA buffews in ciwcuwaw wing
	 * tbuf_stawt   = fiwst buffew fow this data
	 * tbuf_cuwwent = next fwee buffew
	 *
	 * Copy aww data befowe making data visibwe to DMA contwowwew by
	 * setting descwiptow count of the fiwst buffew.
	 * This pwevents an active DMA contwowwew fwom weading the fiwst DMA
	 * buffews of a fwame and stopping befowe the finaw buffews awe fiwwed.
	 */

	info->tbuf_stawt = i = info->tbuf_cuwwent;

	whiwe (size) {
		d = &info->tbufs[i];

		count = (unsigned showt)((size > DMABUFSIZE) ? DMABUFSIZE : size);
		memcpy(d->buf, buf, count);

		size -= count;
		buf  += count;

		/*
		 * set EOF bit fow wast buffew of HDWC fwame ow
		 * fow evewy buffew in waw mode
		 */
		if ((!size && info->pawams.mode == MGSW_MODE_HDWC) ||
		    info->pawams.mode == MGSW_MODE_WAW)
			set_desc_eof(*d, 1);
		ewse
			set_desc_eof(*d, 0);

		/* set descwiptow count fow aww but fiwst buffew */
		if (i != info->tbuf_stawt)
			set_desc_count(*d, count);
		d->buf_count = count;

		if (++i == info->tbuf_count)
			i = 0;
	}

	info->tbuf_cuwwent = i;

	/* set fiwst buffew count to make new data visibwe to DMA contwowwew */
	d = &info->tbufs[info->tbuf_stawt];
	set_desc_count(*d, d->buf_count);

	/* stawt twansmittew if needed and update twansmit timeout */
	if (!info->tx_active)
		tx_stawt(info);
	update_tx_timew(info);

	wetuwn twue;
}

static int wegistew_test(stwuct swgt_info *info)
{
	static unsigned showt pattewns[] =
		{0x0000, 0xffff, 0xaaaa, 0x5555, 0x6969, 0x9696};
	static unsigned int count = AWWAY_SIZE(pattewns);
	unsigned int i;
	int wc = 0;

	fow (i=0 ; i < count ; i++) {
		ww_weg16(info, TIW, pattewns[i]);
		ww_weg16(info, BDW, pattewns[(i+1)%count]);
		if ((wd_weg16(info, TIW) != pattewns[i]) ||
		    (wd_weg16(info, BDW) != pattewns[(i+1)%count])) {
			wc = -ENODEV;
			bweak;
		}
	}
	info->gpio_pwesent = (wd_weg32(info, JCW) & BIT5) ? 1 : 0;
	info->init_ewwow = wc ? 0 : DiagStatus_AddwessFaiwuwe;
	wetuwn wc;
}

static int iwq_test(stwuct swgt_info *info)
{
	unsigned wong timeout;
	unsigned wong fwags;
	stwuct tty_stwuct *owdtty = info->powt.tty;
	u32 speed = info->pawams.data_wate;

	info->pawams.data_wate = 921600;
	info->powt.tty = NUWW;

	spin_wock_iwqsave(&info->wock, fwags);
	async_mode(info);
	swgt_iwq_on(info, IWQ_TXIDWE);

	/* enabwe twansmittew */
	ww_weg16(info, TCW,
		(unsigned showt)(wd_weg16(info, TCW) | BIT1));

	/* wwite one byte and wait fow tx idwe */
	ww_weg16(info, TDW, 0);

	/* assume faiwuwe */
	info->init_ewwow = DiagStatus_IwqFaiwuwe;
	info->iwq_occuwwed = fawse;

	spin_unwock_iwqwestowe(&info->wock, fwags);

	timeout=100;
	whiwe(timeout-- && !info->iwq_occuwwed)
		msweep_intewwuptibwe(10);

	spin_wock_iwqsave(&info->wock,fwags);
	weset_powt(info);
	spin_unwock_iwqwestowe(&info->wock,fwags);

	info->pawams.data_wate = speed;
	info->powt.tty = owdtty;

	info->init_ewwow = info->iwq_occuwwed ? 0 : DiagStatus_IwqFaiwuwe;
	wetuwn info->iwq_occuwwed ? 0 : -ENODEV;
}

static int woopback_test_wx(stwuct swgt_info *info)
{
	unsigned chaw *swc, *dest;
	int count;

	if (desc_compwete(info->wbufs[0])) {
		count = desc_count(info->wbufs[0]);
		swc   = info->wbufs[0].buf;
		dest  = info->tmp_wbuf;

		fow( ; count ; count-=2, swc+=2) {
			/* swc=data byte (swc+1)=status byte */
			if (!(*(swc+1) & (BIT9 + BIT8))) {
				*dest = *swc;
				dest++;
				info->tmp_wbuf_count++;
			}
		}
		DBGDATA(info, info->tmp_wbuf, info->tmp_wbuf_count, "wx");
		wetuwn 1;
	}
	wetuwn 0;
}

static int woopback_test(stwuct swgt_info *info)
{
#define TESTFWAMESIZE 20

	unsigned wong timeout;
	u16 count;
	unsigned chaw buf[TESTFWAMESIZE];
	int wc = -ENODEV;
	unsigned wong fwags;

	stwuct tty_stwuct *owdtty = info->powt.tty;
	MGSW_PAWAMS pawams;

	memcpy(&pawams, &info->pawams, sizeof(pawams));

	info->pawams.mode = MGSW_MODE_ASYNC;
	info->pawams.data_wate = 921600;
	info->pawams.woopback = 1;
	info->powt.tty = NUWW;

	/* buiwd and send twansmit fwame */
	fow (count = 0; count < TESTFWAMESIZE; ++count)
		buf[count] = (unsigned chaw)count;

	info->tmp_wbuf_count = 0;
	memset(info->tmp_wbuf, 0, TESTFWAMESIZE);

	/* pwogwam hawdwawe fow HDWC and enabwed weceivew */
	spin_wock_iwqsave(&info->wock,fwags);
	async_mode(info);
	wx_stawt(info);
	tx_woad(info, buf, count);
	spin_unwock_iwqwestowe(&info->wock, fwags);

	/* wait fow weceive compwete */
	fow (timeout = 100; timeout; --timeout) {
		msweep_intewwuptibwe(10);
		if (woopback_test_wx(info)) {
			wc = 0;
			bweak;
		}
	}

	/* vewify weceived fwame wength and contents */
	if (!wc && (info->tmp_wbuf_count != count ||
		  memcmp(buf, info->tmp_wbuf, count))) {
		wc = -ENODEV;
	}

	spin_wock_iwqsave(&info->wock,fwags);
	weset_adaptew(info);
	spin_unwock_iwqwestowe(&info->wock,fwags);

	memcpy(&info->pawams, &pawams, sizeof(info->pawams));
	info->powt.tty = owdtty;

	info->init_ewwow = wc ? DiagStatus_DmaFaiwuwe : 0;
	wetuwn wc;
}

static int adaptew_test(stwuct swgt_info *info)
{
	DBGINFO(("testing %s\n", info->device_name));
	if (wegistew_test(info) < 0) {
		pwintk("wegistew test faiwuwe %s addw=%08X\n",
			info->device_name, info->phys_weg_addw);
	} ewse if (iwq_test(info) < 0) {
		pwintk("IWQ test faiwuwe %s IWQ=%d\n",
			info->device_name, info->iwq_wevew);
	} ewse if (woopback_test(info) < 0) {
		pwintk("woopback test faiwuwe %s\n", info->device_name);
	}
	wetuwn info->init_ewwow;
}

/*
 * twansmit timeout handwew
 */
static void tx_timeout(stwuct timew_wist *t)
{
	stwuct swgt_info *info = fwom_timew(info, t, tx_timew);
	unsigned wong fwags;

	DBGINFO(("%s tx_timeout\n", info->device_name));
	if(info->tx_active && info->pawams.mode == MGSW_MODE_HDWC) {
		info->icount.txtimeout++;
	}
	spin_wock_iwqsave(&info->wock,fwags);
	tx_stop(info);
	spin_unwock_iwqwestowe(&info->wock,fwags);

#if SYNCWINK_GENEWIC_HDWC
	if (info->netcount)
		hdwcdev_tx_done(info);
	ewse
#endif
		bh_twansmit(info);
}

/*
 * weceive buffew powwing timew
 */
static void wx_timeout(stwuct timew_wist *t)
{
	stwuct swgt_info *info = fwom_timew(info, t, wx_timew);
	unsigned wong fwags;

	DBGINFO(("%s wx_timeout\n", info->device_name));
	spin_wock_iwqsave(&info->wock, fwags);
	info->pending_bh |= BH_WECEIVE;
	spin_unwock_iwqwestowe(&info->wock, fwags);
	bh_handwew(&info->task);
}

