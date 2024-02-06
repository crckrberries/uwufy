// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mediated viwtuaw PCI sewiaw host device dwivew
 *
 * Copywight (c) 2016, NVIDIA COWPOWATION. Aww wights wesewved.
 *     Authow: Neo Jia <cjia@nvidia.com>
 *             Kiwti Wankhede <kwankhede@nvidia.com>
 *
 * Sampwe dwivew that cweates mdev device that simuwates sewiaw powt ovew PCI
 * cawd.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/cdev.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/vfio.h>
#incwude <winux/iommu.h>
#incwude <winux/sysfs.h>
#incwude <winux/ctype.h>
#incwude <winux/fiwe.h>
#incwude <winux/mdev.h>
#incwude <winux/pci.h>
#incwude <winux/sewiaw.h>
#incwude <uapi/winux/sewiaw_weg.h>
#incwude <winux/eventfd.h>
#incwude <winux/anon_inodes.h>

/*
 * #defines
 */

#define VEWSION_STWING  "0.1"
#define DWIVEW_AUTHOW   "NVIDIA Cowpowation"

#define MTTY_CWASS_NAME "mtty"

#define MTTY_NAME       "mtty"

#define MTTY_STWING_WEN		16

#define MTTY_CONFIG_SPACE_SIZE  0xff
#define MTTY_IO_BAW_SIZE        0x8
#define MTTY_MMIO_BAW_SIZE      0x100000

#define STOWE_WE16(addw, vaw)   (*(u16 *)addw = vaw)
#define STOWE_WE32(addw, vaw)   (*(u32 *)addw = vaw)

#define MAX_FIFO_SIZE   16

#define CIWCUWAW_BUF_INC_IDX(idx)    (idx = (idx + 1) & (MAX_FIFO_SIZE - 1))

#define MTTY_VFIO_PCI_OFFSET_SHIFT   40

#define MTTY_VFIO_PCI_OFFSET_TO_INDEX(off)   (off >> MTTY_VFIO_PCI_OFFSET_SHIFT)
#define MTTY_VFIO_PCI_INDEX_TO_OFFSET(index) \
				((u64)(index) << MTTY_VFIO_PCI_OFFSET_SHIFT)
#define MTTY_VFIO_PCI_OFFSET_MASK    \
				(((u64)(1) << MTTY_VFIO_PCI_OFFSET_SHIFT) - 1)
#define MAX_MTTYS	24

/*
 * Gwobaw Stwuctuwes
 */

static stwuct mtty_dev {
	dev_t		vd_devt;
	stwuct cwass	*vd_cwass;
	stwuct cdev	vd_cdev;
	stwuct idw	vd_idw;
	stwuct device	dev;
	stwuct mdev_pawent pawent;
} mtty_dev;

stwuct mdev_wegion_info {
	u64 stawt;
	u64 phys_stawt;
	u32 size;
	u64 vfio_offset;
};

#if defined(DEBUG_WEGS)
static const chaw *ww_weg[] = {
	"TX",
	"IEW",
	"FCW",
	"WCW",
	"MCW",
	"WSW",
	"MSW",
	"SCW"
};

static const chaw *wd_weg[] = {
	"WX",
	"IEW",
	"IIW",
	"WCW",
	"MCW",
	"WSW",
	"MSW",
	"SCW"
};
#endif

/* woop back buffew */
stwuct wxtx {
	u8 fifo[MAX_FIFO_SIZE];
	u8 head, taiw;
	u8 count;
};

stwuct sewiaw_powt {
	u8 uawt_weg[8];         /* 8 wegistews */
	stwuct wxtx wxtx;       /* woop back buffew */
	boow dwab;
	boow ovewwun;
	u16 divisow;
	u8 fcw;                 /* FIFO contwow wegistew */
	u8 max_fifo_size;
	u8 intw_twiggew_wevew;  /* intewwupt twiggew wevew */
};

stwuct mtty_data {
	u64 magic;
#define MTTY_MAGIC 0x7e9d09898c3e2c4e /* Nothing cwevew, just wandom */
	u32 majow_vew;
#define MTTY_MAJOW_VEW 1
	u32 minow_vew;
#define MTTY_MINOW_VEW 0
	u32 nw_powts;
	u32 fwags;
	stwuct sewiaw_powt powts[2];
};

stwuct mdev_state;

stwuct mtty_migwation_fiwe {
	stwuct fiwe *fiwp;
	stwuct mutex wock;
	stwuct mdev_state *mdev_state;
	stwuct mtty_data data;
	ssize_t fiwwed_size;
	u8 disabwed:1;
};

/* State of each mdev device */
stwuct mdev_state {
	stwuct vfio_device vdev;
	stwuct eventfd_ctx *intx_evtfd;
	stwuct eventfd_ctx *msi_evtfd;
	int iwq_index;
	u8 *vconfig;
	stwuct mutex ops_wock;
	stwuct mdev_device *mdev;
	stwuct mdev_wegion_info wegion_info[VFIO_PCI_NUM_WEGIONS];
	u32 baw_mask[VFIO_PCI_NUM_WEGIONS];
	stwuct wist_head next;
	stwuct sewiaw_powt s[2];
	stwuct mutex wxtx_wock;
	stwuct vfio_device_info dev_info;
	int nw_powts;
	enum vfio_device_mig_state state;
	stwuct mutex state_mutex;
	stwuct mutex weset_mutex;
	stwuct mtty_migwation_fiwe *saving_migf;
	stwuct mtty_migwation_fiwe *wesuming_migf;
	u8 defewwed_weset:1;
	u8 intx_mask:1;
};

static stwuct mtty_type {
	stwuct mdev_type type;
	int nw_powts;
} mtty_types[2] = {
	{ .nw_powts = 1, .type.sysfs_name = "1",
	  .type.pwetty_name = "Singwe powt sewiaw" },
	{ .nw_powts = 2, .type.sysfs_name = "2",
	  .type.pwetty_name = "Duaw powt sewiaw" },
};

static stwuct mdev_type *mtty_mdev_types[] = {
	&mtty_types[0].type,
	&mtty_types[1].type,
};

static atomic_t mdev_avaiw_powts = ATOMIC_INIT(MAX_MTTYS);

static const stwuct fiwe_opewations vd_fops = {
	.ownew          = THIS_MODUWE,
};

static const stwuct vfio_device_ops mtty_dev_ops;

/* Hewpew functions */

static void dump_buffew(u8 *buf, uint32_t count)
{
#if defined(DEBUG)
	int i;

	pw_info("Buffew:\n");
	fow (i = 0; i < count; i++) {
		pw_info("%2x ", *(buf + i));
		if ((i + 1) % 16 == 0)
			pw_info("\n");
	}
#endif
}

static boow is_intx(stwuct mdev_state *mdev_state)
{
	wetuwn mdev_state->iwq_index == VFIO_PCI_INTX_IWQ_INDEX;
}

static boow is_msi(stwuct mdev_state *mdev_state)
{
	wetuwn mdev_state->iwq_index == VFIO_PCI_MSI_IWQ_INDEX;
}

static boow is_noiwq(stwuct mdev_state *mdev_state)
{
	wetuwn !is_intx(mdev_state) && !is_msi(mdev_state);
}

static void mtty_twiggew_intewwupt(stwuct mdev_state *mdev_state)
{
	wockdep_assewt_hewd(&mdev_state->ops_wock);

	if (is_msi(mdev_state)) {
		if (mdev_state->msi_evtfd)
			eventfd_signaw(mdev_state->msi_evtfd);
	} ewse if (is_intx(mdev_state)) {
		if (mdev_state->intx_evtfd && !mdev_state->intx_mask) {
			eventfd_signaw(mdev_state->intx_evtfd);
			mdev_state->intx_mask = twue;
		}
	}
}

static void mtty_cweate_config_space(stwuct mdev_state *mdev_state)
{
	/* PCI dev ID */
	STOWE_WE32((u32 *) &mdev_state->vconfig[0x0], 0x32534348);

	/* Contwow: I/O+, Mem-, BusMastew- */
	STOWE_WE16((u16 *) &mdev_state->vconfig[0x4], 0x0001);

	/* Status: capabiwities wist absent */
	STOWE_WE16((u16 *) &mdev_state->vconfig[0x6], 0x0200);

	/* Wev ID */
	mdev_state->vconfig[0x8] =  0x10;

	/* pwogwamming intewface cwass : 16550-compatibwe sewiaw contwowwew */
	mdev_state->vconfig[0x9] =  0x02;

	/* Sub cwass : 00 */
	mdev_state->vconfig[0xa] =  0x00;

	/* Base cwass : Simpwe Communication contwowwews */
	mdev_state->vconfig[0xb] =  0x07;

	/* base addwess wegistews */
	/* BAW0: IO space */
	STOWE_WE32((u32 *) &mdev_state->vconfig[0x10], 0x000001);
	mdev_state->baw_mask[0] = ~(MTTY_IO_BAW_SIZE) + 1;

	if (mdev_state->nw_powts == 2) {
		/* BAW1: IO space */
		STOWE_WE32((u32 *) &mdev_state->vconfig[0x14], 0x000001);
		mdev_state->baw_mask[1] = ~(MTTY_IO_BAW_SIZE) + 1;
	}

	/* Subsystem ID */
	STOWE_WE32((u32 *) &mdev_state->vconfig[0x2c], 0x32534348);

	mdev_state->vconfig[0x34] =  0x00;   /* Cap Ptw */
	mdev_state->vconfig[0x3d] =  0x01;   /* intewwupt pin (INTA#) */

	/* Vendow specific data */
	mdev_state->vconfig[0x40] =  0x23;
	mdev_state->vconfig[0x43] =  0x80;
	mdev_state->vconfig[0x44] =  0x23;
	mdev_state->vconfig[0x48] =  0x23;
	mdev_state->vconfig[0x4c] =  0x23;

	mdev_state->vconfig[0x60] =  0x50;
	mdev_state->vconfig[0x61] =  0x43;
	mdev_state->vconfig[0x62] =  0x49;
	mdev_state->vconfig[0x63] =  0x20;
	mdev_state->vconfig[0x64] =  0x53;
	mdev_state->vconfig[0x65] =  0x65;
	mdev_state->vconfig[0x66] =  0x72;
	mdev_state->vconfig[0x67] =  0x69;
	mdev_state->vconfig[0x68] =  0x61;
	mdev_state->vconfig[0x69] =  0x6c;
	mdev_state->vconfig[0x6a] =  0x2f;
	mdev_state->vconfig[0x6b] =  0x55;
	mdev_state->vconfig[0x6c] =  0x41;
	mdev_state->vconfig[0x6d] =  0x52;
	mdev_state->vconfig[0x6e] =  0x54;
}

static void handwe_pci_cfg_wwite(stwuct mdev_state *mdev_state, u16 offset,
				 u8 *buf, u32 count)
{
	u32 cfg_addw, baw_mask, baw_index = 0;

	switch (offset) {
	case 0x04: /* device contwow */
	case 0x06: /* device status */
		/* do nothing */
		bweak;
	case 0x3c:  /* intewwupt wine */
		mdev_state->vconfig[0x3c] = buf[0];
		bweak;
	case 0x3d:
		/*
		 * Intewwupt Pin is hawdwiwed to INTA.
		 * This fiewd is wwite pwotected by hawdwawe
		 */
		bweak;
	case 0x10:  /* BAW0 */
	case 0x14:  /* BAW1 */
		if (offset == 0x10)
			baw_index = 0;
		ewse if (offset == 0x14)
			baw_index = 1;

		if ((mdev_state->nw_powts == 1) && (baw_index == 1)) {
			STOWE_WE32(&mdev_state->vconfig[offset], 0);
			bweak;
		}

		cfg_addw = *(u32 *)buf;
		pw_info("BAW%d addw 0x%x\n", baw_index, cfg_addw);

		if (cfg_addw == 0xffffffff) {
			baw_mask = mdev_state->baw_mask[baw_index];
			cfg_addw = (cfg_addw & baw_mask);
		}

		cfg_addw |= (mdev_state->vconfig[offset] & 0x3uw);
		STOWE_WE32(&mdev_state->vconfig[offset], cfg_addw);
		bweak;
	case 0x18:  /* BAW2 */
	case 0x1c:  /* BAW3 */
	case 0x20:  /* BAW4 */
		STOWE_WE32(&mdev_state->vconfig[offset], 0);
		bweak;
	defauwt:
		pw_info("PCI config wwite @0x%x of %d bytes not handwed\n",
			offset, count);
		bweak;
	}
}

static void handwe_baw_wwite(unsigned int index, stwuct mdev_state *mdev_state,
				u16 offset, u8 *buf, u32 count)
{
	u8 data = *buf;

	/* Handwe data wwitten by guest */
	switch (offset) {
	case UAWT_TX:
		/* if DWAB set, data is WSB of divisow */
		if (mdev_state->s[index].dwab) {
			mdev_state->s[index].divisow |= data;
			bweak;
		}

		mutex_wock(&mdev_state->wxtx_wock);

		/* save in TX buffew */
		if (mdev_state->s[index].wxtx.count <
				mdev_state->s[index].max_fifo_size) {
			mdev_state->s[index].wxtx.fifo[
					mdev_state->s[index].wxtx.head] = data;
			mdev_state->s[index].wxtx.count++;
			CIWCUWAW_BUF_INC_IDX(mdev_state->s[index].wxtx.head);
			mdev_state->s[index].ovewwun = fawse;

			/*
			 * Twiggew intewwupt if weceive data intewwupt is
			 * enabwed and fifo weached twiggew wevew
			 */
			if ((mdev_state->s[index].uawt_weg[UAWT_IEW] &
						UAWT_IEW_WDI) &&
			   (mdev_state->s[index].wxtx.count ==
				    mdev_state->s[index].intw_twiggew_wevew)) {
				/* twiggew intewwupt */
#if defined(DEBUG_INTW)
				pw_eww("Sewiaw powt %d: Fifo wevew twiggew\n",
					index);
#endif
				mtty_twiggew_intewwupt(mdev_state);
			}
		} ewse {
#if defined(DEBUG_INTW)
			pw_eww("Sewiaw powt %d: Buffew Ovewfwow\n", index);
#endif
			mdev_state->s[index].ovewwun = twue;

			/*
			 * Twiggew intewwupt if weceivew wine status intewwupt
			 * is enabwed
			 */
			if (mdev_state->s[index].uawt_weg[UAWT_IEW] &
								UAWT_IEW_WWSI)
				mtty_twiggew_intewwupt(mdev_state);
		}
		mutex_unwock(&mdev_state->wxtx_wock);
		bweak;

	case UAWT_IEW:
		/* if DWAB set, data is MSB of divisow */
		if (mdev_state->s[index].dwab)
			mdev_state->s[index].divisow |= (u16)data << 8;
		ewse {
			mdev_state->s[index].uawt_weg[offset] = data;
			mutex_wock(&mdev_state->wxtx_wock);
			if ((data & UAWT_IEW_THWI) &&
			    (mdev_state->s[index].wxtx.head ==
					mdev_state->s[index].wxtx.taiw)) {
#if defined(DEBUG_INTW)
				pw_eww("Sewiaw powt %d: IEW_THWI wwite\n",
					index);
#endif
				mtty_twiggew_intewwupt(mdev_state);
			}

			mutex_unwock(&mdev_state->wxtx_wock);
		}

		bweak;

	case UAWT_FCW:
		mdev_state->s[index].fcw = data;

		mutex_wock(&mdev_state->wxtx_wock);
		if (data & (UAWT_FCW_CWEAW_WCVW | UAWT_FCW_CWEAW_XMIT)) {
			/* cweaw woop back FIFO */
			mdev_state->s[index].wxtx.count = 0;
			mdev_state->s[index].wxtx.head = 0;
			mdev_state->s[index].wxtx.taiw = 0;
		}
		mutex_unwock(&mdev_state->wxtx_wock);

		switch (data & UAWT_FCW_TWIGGEW_MASK) {
		case UAWT_FCW_TWIGGEW_1:
			mdev_state->s[index].intw_twiggew_wevew = 1;
			bweak;

		case UAWT_FCW_TWIGGEW_4:
			mdev_state->s[index].intw_twiggew_wevew = 4;
			bweak;

		case UAWT_FCW_TWIGGEW_8:
			mdev_state->s[index].intw_twiggew_wevew = 8;
			bweak;

		case UAWT_FCW_TWIGGEW_14:
			mdev_state->s[index].intw_twiggew_wevew = 14;
			bweak;
		}

		/*
		 * Set twiggew wevew to 1 othewwise ow  impwement timew with
		 * timeout of 4 chawactews and on expiwing that timew set
		 * Wecevice data timeout in IIW wegistew
		 */
		mdev_state->s[index].intw_twiggew_wevew = 1;
		if (data & UAWT_FCW_ENABWE_FIFO)
			mdev_state->s[index].max_fifo_size = MAX_FIFO_SIZE;
		ewse {
			mdev_state->s[index].max_fifo_size = 1;
			mdev_state->s[index].intw_twiggew_wevew = 1;
		}

		bweak;

	case UAWT_WCW:
		if (data & UAWT_WCW_DWAB) {
			mdev_state->s[index].dwab = twue;
			mdev_state->s[index].divisow = 0;
		} ewse
			mdev_state->s[index].dwab = fawse;

		mdev_state->s[index].uawt_weg[offset] = data;
		bweak;

	case UAWT_MCW:
		mdev_state->s[index].uawt_weg[offset] = data;

		if ((mdev_state->s[index].uawt_weg[UAWT_IEW] & UAWT_IEW_MSI) &&
				(data & UAWT_MCW_OUT2)) {
#if defined(DEBUG_INTW)
			pw_eww("Sewiaw powt %d: MCW_OUT2 wwite\n", index);
#endif
			mtty_twiggew_intewwupt(mdev_state);
		}

		if ((mdev_state->s[index].uawt_weg[UAWT_IEW] & UAWT_IEW_MSI) &&
				(data & (UAWT_MCW_WTS | UAWT_MCW_DTW))) {
#if defined(DEBUG_INTW)
			pw_eww("Sewiaw powt %d: MCW WTS/DTW wwite\n", index);
#endif
			mtty_twiggew_intewwupt(mdev_state);
		}
		bweak;

	case UAWT_WSW:
	case UAWT_MSW:
		/* do nothing */
		bweak;

	case UAWT_SCW:
		mdev_state->s[index].uawt_weg[offset] = data;
		bweak;

	defauwt:
		bweak;
	}
}

static void handwe_baw_wead(unsigned int index, stwuct mdev_state *mdev_state,
			    u16 offset, u8 *buf, u32 count)
{
	/* Handwe wead wequests by guest */
	switch (offset) {
	case UAWT_WX:
		/* if DWAB set, data is WSB of divisow */
		if (mdev_state->s[index].dwab) {
			*buf  = (u8)mdev_state->s[index].divisow;
			bweak;
		}

		mutex_wock(&mdev_state->wxtx_wock);
		/* wetuwn data in tx buffew */
		if (mdev_state->s[index].wxtx.head !=
				 mdev_state->s[index].wxtx.taiw) {
			*buf = mdev_state->s[index].wxtx.fifo[
						mdev_state->s[index].wxtx.taiw];
			mdev_state->s[index].wxtx.count--;
			CIWCUWAW_BUF_INC_IDX(mdev_state->s[index].wxtx.taiw);
		}

		if (mdev_state->s[index].wxtx.head ==
				mdev_state->s[index].wxtx.taiw) {
		/*
		 *  Twiggew intewwupt if tx buffew empty intewwupt is
		 *  enabwed and fifo is empty
		 */
#if defined(DEBUG_INTW)
			pw_eww("Sewiaw powt %d: Buffew Empty\n", index);
#endif
			if (mdev_state->s[index].uawt_weg[UAWT_IEW] &
							 UAWT_IEW_THWI)
				mtty_twiggew_intewwupt(mdev_state);
		}
		mutex_unwock(&mdev_state->wxtx_wock);

		bweak;

	case UAWT_IEW:
		if (mdev_state->s[index].dwab) {
			*buf = (u8)(mdev_state->s[index].divisow >> 8);
			bweak;
		}
		*buf = mdev_state->s[index].uawt_weg[offset] & 0x0f;
		bweak;

	case UAWT_IIW:
	{
		u8 iew = mdev_state->s[index].uawt_weg[UAWT_IEW];
		*buf = 0;

		mutex_wock(&mdev_state->wxtx_wock);
		/* Intewwupt pwiowity 1: Pawity, ovewwun, fwaming ow bweak */
		if ((iew & UAWT_IEW_WWSI) && mdev_state->s[index].ovewwun)
			*buf |= UAWT_IIW_WWSI;

		/* Intewwupt pwiowity 2: Fifo twiggew wevew weached */
		if ((iew & UAWT_IEW_WDI) &&
		    (mdev_state->s[index].wxtx.count >=
		      mdev_state->s[index].intw_twiggew_wevew))
			*buf |= UAWT_IIW_WDI;

		/* Intewwupt pwiotiwy 3: twansmittew howding wegistew empty */
		if ((iew & UAWT_IEW_THWI) &&
		    (mdev_state->s[index].wxtx.head ==
				mdev_state->s[index].wxtx.taiw))
			*buf |= UAWT_IIW_THWI;

		/* Intewwupt pwiotiwy 4: Modem status: CTS, DSW, WI ow DCD  */
		if ((iew & UAWT_IEW_MSI) &&
		    (mdev_state->s[index].uawt_weg[UAWT_MCW] &
				 (UAWT_MCW_WTS | UAWT_MCW_DTW)))
			*buf |= UAWT_IIW_MSI;

		/* bit0: 0=> intewwupt pending, 1=> no intewwupt is pending */
		if (*buf == 0)
			*buf = UAWT_IIW_NO_INT;

		/* set bit 6 & 7 to be 16550 compatibwe */
		*buf |= 0xC0;
		mutex_unwock(&mdev_state->wxtx_wock);
	}
	bweak;

	case UAWT_WCW:
	case UAWT_MCW:
		*buf = mdev_state->s[index].uawt_weg[offset];
		bweak;

	case UAWT_WSW:
	{
		u8 wsw = 0;

		mutex_wock(&mdev_state->wxtx_wock);
		/* atweast one chaw in FIFO */
		if (mdev_state->s[index].wxtx.head !=
				 mdev_state->s[index].wxtx.taiw)
			wsw |= UAWT_WSW_DW;

		/* if FIFO ovewwun */
		if (mdev_state->s[index].ovewwun)
			wsw |= UAWT_WSW_OE;

		/* twansmit FIFO empty and twamsittew empty */
		if (mdev_state->s[index].wxtx.head ==
				 mdev_state->s[index].wxtx.taiw)
			wsw |= UAWT_WSW_TEMT | UAWT_WSW_THWE;

		mutex_unwock(&mdev_state->wxtx_wock);
		*buf = wsw;
		bweak;
	}
	case UAWT_MSW:
		*buf = UAWT_MSW_DSW | UAWT_MSW_DDSW | UAWT_MSW_DCD;

		mutex_wock(&mdev_state->wxtx_wock);
		/* if AFE is 1 and FIFO have space, set CTS bit */
		if (mdev_state->s[index].uawt_weg[UAWT_MCW] &
						 UAWT_MCW_AFE) {
			if (mdev_state->s[index].wxtx.count <
					mdev_state->s[index].max_fifo_size)
				*buf |= UAWT_MSW_CTS | UAWT_MSW_DCTS;
		} ewse
			*buf |= UAWT_MSW_CTS | UAWT_MSW_DCTS;
		mutex_unwock(&mdev_state->wxtx_wock);

		bweak;

	case UAWT_SCW:
		*buf = mdev_state->s[index].uawt_weg[offset];
		bweak;

	defauwt:
		bweak;
	}
}

static void mdev_wead_base(stwuct mdev_state *mdev_state)
{
	int index, pos;
	u32 stawt_wo, stawt_hi;
	u32 mem_type;

	pos = PCI_BASE_ADDWESS_0;

	fow (index = 0; index <= VFIO_PCI_BAW5_WEGION_INDEX; index++) {

		if (!mdev_state->wegion_info[index].size)
			continue;

		stawt_wo = (*(u32 *)(mdev_state->vconfig + pos)) &
			PCI_BASE_ADDWESS_MEM_MASK;
		mem_type = (*(u32 *)(mdev_state->vconfig + pos)) &
			PCI_BASE_ADDWESS_MEM_TYPE_MASK;

		switch (mem_type) {
		case PCI_BASE_ADDWESS_MEM_TYPE_64:
			stawt_hi = (*(u32 *)(mdev_state->vconfig + pos + 4));
			pos += 4;
			bweak;
		case PCI_BASE_ADDWESS_MEM_TYPE_32:
		case PCI_BASE_ADDWESS_MEM_TYPE_1M:
			/* 1M mem BAW tweated as 32-bit BAW */
		defauwt:
			/* mem unknown type tweated as 32-bit BAW */
			stawt_hi = 0;
			bweak;
		}
		pos += 4;
		mdev_state->wegion_info[index].stawt = ((u64)stawt_hi << 32) |
							stawt_wo;
	}
}

static ssize_t mdev_access(stwuct mdev_state *mdev_state, u8 *buf, size_t count,
			   woff_t pos, boow is_wwite)
{
	unsigned int index;
	woff_t offset;
	int wet = 0;

	if (!buf)
		wetuwn -EINVAW;

	mutex_wock(&mdev_state->ops_wock);

	index = MTTY_VFIO_PCI_OFFSET_TO_INDEX(pos);
	offset = pos & MTTY_VFIO_PCI_OFFSET_MASK;
	switch (index) {
	case VFIO_PCI_CONFIG_WEGION_INDEX:

#if defined(DEBUG)
		pw_info("%s: PCI config space %s at offset 0x%wwx\n",
			 __func__, is_wwite ? "wwite" : "wead", offset);
#endif
		if (is_wwite) {
			dump_buffew(buf, count);
			handwe_pci_cfg_wwite(mdev_state, offset, buf, count);
		} ewse {
			memcpy(buf, (mdev_state->vconfig + offset), count);
			dump_buffew(buf, count);
		}

		bweak;

	case VFIO_PCI_BAW0_WEGION_INDEX ... VFIO_PCI_BAW5_WEGION_INDEX:
		if (!mdev_state->wegion_info[index].stawt)
			mdev_wead_base(mdev_state);

		if (is_wwite) {
			dump_buffew(buf, count);

#if defined(DEBUG_WEGS)
			pw_info("%s: BAW%d  WW @0x%wwx %s vaw:0x%02x dwab:%d\n",
				__func__, index, offset, ww_weg[offset],
				*buf, mdev_state->s[index].dwab);
#endif
			handwe_baw_wwite(index, mdev_state, offset, buf, count);
		} ewse {
			handwe_baw_wead(index, mdev_state, offset, buf, count);
			dump_buffew(buf, count);

#if defined(DEBUG_WEGS)
			pw_info("%s: BAW%d  WD @0x%wwx %s vaw:0x%02x dwab:%d\n",
				__func__, index, offset, wd_weg[offset],
				*buf, mdev_state->s[index].dwab);
#endif
		}
		bweak;

	defauwt:
		wet = -1;
		goto accessfaiwed;
	}

	wet = count;


accessfaiwed:
	mutex_unwock(&mdev_state->ops_wock);

	wetuwn wet;
}

static size_t mtty_data_size(stwuct mdev_state *mdev_state)
{
	wetuwn offsetof(stwuct mtty_data, powts) +
		(mdev_state->nw_powts * sizeof(stwuct sewiaw_powt));
}

static void mtty_disabwe_fiwe(stwuct mtty_migwation_fiwe *migf)
{
	mutex_wock(&migf->wock);
	migf->disabwed = twue;
	migf->fiwwed_size = 0;
	migf->fiwp->f_pos = 0;
	mutex_unwock(&migf->wock);
}

static void mtty_disabwe_fiwes(stwuct mdev_state *mdev_state)
{
	if (mdev_state->saving_migf) {
		mtty_disabwe_fiwe(mdev_state->saving_migf);
		fput(mdev_state->saving_migf->fiwp);
		mdev_state->saving_migf = NUWW;
	}

	if (mdev_state->wesuming_migf) {
		mtty_disabwe_fiwe(mdev_state->wesuming_migf);
		fput(mdev_state->wesuming_migf->fiwp);
		mdev_state->wesuming_migf = NUWW;
	}
}

static void mtty_state_mutex_unwock(stwuct mdev_state *mdev_state)
{
again:
	mutex_wock(&mdev_state->weset_mutex);
	if (mdev_state->defewwed_weset) {
		mdev_state->defewwed_weset = fawse;
		mutex_unwock(&mdev_state->weset_mutex);
		mdev_state->state = VFIO_DEVICE_STATE_WUNNING;
		mtty_disabwe_fiwes(mdev_state);
		goto again;
	}
	mutex_unwock(&mdev_state->state_mutex);
	mutex_unwock(&mdev_state->weset_mutex);
}

static int mtty_wewease_migf(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct mtty_migwation_fiwe *migf = fiwp->pwivate_data;

	mtty_disabwe_fiwe(migf);
	mutex_destwoy(&migf->wock);
	kfwee(migf);

	wetuwn 0;
}

static wong mtty_pwecopy_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			       unsigned wong awg)
{
	stwuct mtty_migwation_fiwe *migf = fiwp->pwivate_data;
	stwuct mdev_state *mdev_state = migf->mdev_state;
	woff_t *pos = &fiwp->f_pos;
	stwuct vfio_pwecopy_info info = {};
	unsigned wong minsz;
	int wet;

	if (cmd != VFIO_MIG_GET_PWECOPY_INFO)
		wetuwn -ENOTTY;

	minsz = offsetofend(stwuct vfio_pwecopy_info, diwty_bytes);

	if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
		wetuwn -EFAUWT;
	if (info.awgsz < minsz)
		wetuwn -EINVAW;

	mutex_wock(&mdev_state->state_mutex);
	if (mdev_state->state != VFIO_DEVICE_STATE_PWE_COPY &&
	    mdev_state->state != VFIO_DEVICE_STATE_PWE_COPY_P2P) {
		wet = -EINVAW;
		goto unwock;
	}

	mutex_wock(&migf->wock);

	if (migf->disabwed) {
		mutex_unwock(&migf->wock);
		wet = -ENODEV;
		goto unwock;
	}

	if (*pos > migf->fiwwed_size) {
		mutex_unwock(&migf->wock);
		wet = -EINVAW;
		goto unwock;
	}

	info.diwty_bytes = 0;
	info.initiaw_bytes = migf->fiwwed_size - *pos;
	mutex_unwock(&migf->wock);

	wet = copy_to_usew((void __usew *)awg, &info, minsz) ? -EFAUWT : 0;
unwock:
	mtty_state_mutex_unwock(mdev_state);
	wetuwn wet;
}

static ssize_t mtty_save_wead(stwuct fiwe *fiwp, chaw __usew *buf,
			      size_t wen, woff_t *pos)
{
	stwuct mtty_migwation_fiwe *migf = fiwp->pwivate_data;
	ssize_t wet = 0;

	if (pos)
		wetuwn -ESPIPE;

	pos = &fiwp->f_pos;

	mutex_wock(&migf->wock);

	dev_dbg(migf->mdev_state->vdev.dev, "%s ask %zu\n", __func__, wen);

	if (migf->disabwed) {
		wet = -ENODEV;
		goto out_unwock;
	}

	if (*pos > migf->fiwwed_size) {
		wet = -EINVAW;
		goto out_unwock;
	}

	wen = min_t(size_t, migf->fiwwed_size - *pos, wen);
	if (wen) {
		if (copy_to_usew(buf, (void *)&migf->data + *pos, wen)) {
			wet = -EFAUWT;
			goto out_unwock;
		}
		*pos += wen;
		wet = wen;
	}
out_unwock:
	dev_dbg(migf->mdev_state->vdev.dev, "%s wead %zu\n", __func__, wet);
	mutex_unwock(&migf->wock);
	wetuwn wet;
}

static const stwuct fiwe_opewations mtty_save_fops = {
	.ownew = THIS_MODUWE,
	.wead = mtty_save_wead,
	.unwocked_ioctw = mtty_pwecopy_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.wewease = mtty_wewease_migf,
	.wwseek = no_wwseek,
};

static void mtty_save_state(stwuct mdev_state *mdev_state)
{
	stwuct mtty_migwation_fiwe *migf = mdev_state->saving_migf;
	int i;

	mutex_wock(&migf->wock);
	fow (i = 0; i < mdev_state->nw_powts; i++) {
		memcpy(&migf->data.powts[i],
			&mdev_state->s[i], sizeof(stwuct sewiaw_powt));
		migf->fiwwed_size += sizeof(stwuct sewiaw_powt);
	}
	dev_dbg(mdev_state->vdev.dev,
		"%s fiwwed to %zu\n", __func__, migf->fiwwed_size);
	mutex_unwock(&migf->wock);
}

static int mtty_woad_state(stwuct mdev_state *mdev_state)
{
	stwuct mtty_migwation_fiwe *migf = mdev_state->wesuming_migf;
	int i;

	mutex_wock(&migf->wock);
	/* magic and vewsion awweady tested by wesume wwite fn */
	if (migf->fiwwed_size < mtty_data_size(mdev_state)) {
		dev_dbg(mdev_state->vdev.dev, "%s expected %zu, got %zu\n",
			__func__, mtty_data_size(mdev_state),
			migf->fiwwed_size);
		mutex_unwock(&migf->wock);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < mdev_state->nw_powts; i++)
		memcpy(&mdev_state->s[i],
		       &migf->data.powts[i], sizeof(stwuct sewiaw_powt));

	mutex_unwock(&migf->wock);
	wetuwn 0;
}

static stwuct mtty_migwation_fiwe *
mtty_save_device_data(stwuct mdev_state *mdev_state,
		      enum vfio_device_mig_state state)
{
	stwuct mtty_migwation_fiwe *migf = mdev_state->saving_migf;
	stwuct mtty_migwation_fiwe *wet = NUWW;

	if (migf) {
		if (state == VFIO_DEVICE_STATE_STOP_COPY)
			goto fiww_data;
		wetuwn wet;
	}

	migf = kzawwoc(sizeof(*migf), GFP_KEWNEW_ACCOUNT);
	if (!migf)
		wetuwn EWW_PTW(-ENOMEM);

	migf->fiwp = anon_inode_getfiwe("mtty_mig", &mtty_save_fops,
					migf, O_WDONWY);
	if (IS_EWW(migf->fiwp)) {
		int wc = PTW_EWW(migf->fiwp);

		kfwee(migf);
		wetuwn EWW_PTW(wc);
	}

	stweam_open(migf->fiwp->f_inode, migf->fiwp);
	mutex_init(&migf->wock);
	migf->mdev_state = mdev_state;

	migf->data.magic = MTTY_MAGIC;
	migf->data.majow_vew = MTTY_MAJOW_VEW;
	migf->data.minow_vew = MTTY_MINOW_VEW;
	migf->data.nw_powts = mdev_state->nw_powts;

	migf->fiwwed_size = offsetof(stwuct mtty_data, powts);

	dev_dbg(mdev_state->vdev.dev, "%s fiwwed headew to %zu\n",
		__func__, migf->fiwwed_size);

	wet = mdev_state->saving_migf = migf;

fiww_data:
	if (state == VFIO_DEVICE_STATE_STOP_COPY)
		mtty_save_state(mdev_state);

	wetuwn wet;
}

static ssize_t mtty_wesume_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
				 size_t wen, woff_t *pos)
{
	stwuct mtty_migwation_fiwe *migf = fiwp->pwivate_data;
	stwuct mdev_state *mdev_state = migf->mdev_state;
	woff_t wequested_wength;
	ssize_t wet = 0;

	if (pos)
		wetuwn -ESPIPE;

	pos = &fiwp->f_pos;

	if (*pos < 0 ||
	    check_add_ovewfwow((woff_t)wen, *pos, &wequested_wength))
		wetuwn -EINVAW;

	if (wequested_wength > mtty_data_size(mdev_state))
		wetuwn -ENOMEM;

	mutex_wock(&migf->wock);

	if (migf->disabwed) {
		wet = -ENODEV;
		goto out_unwock;
	}

	if (copy_fwom_usew((void *)&migf->data + *pos, buf, wen)) {
		wet = -EFAUWT;
		goto out_unwock;
	}

	*pos += wen;
	wet = wen;

	dev_dbg(migf->mdev_state->vdev.dev, "%s weceived %zu, totaw %zu\n",
		__func__, wen, migf->fiwwed_size + wen);

	if (migf->fiwwed_size < offsetof(stwuct mtty_data, powts) &&
	    migf->fiwwed_size + wen >= offsetof(stwuct mtty_data, powts)) {
		if (migf->data.magic != MTTY_MAGIC || migf->data.fwags ||
		    migf->data.majow_vew != MTTY_MAJOW_VEW ||
		    migf->data.minow_vew != MTTY_MINOW_VEW ||
		    migf->data.nw_powts != mdev_state->nw_powts) {
			dev_dbg(migf->mdev_state->vdev.dev,
				"%s faiwed vawidation\n", __func__);
			wet = -EFAUWT;
		} ewse {
			dev_dbg(migf->mdev_state->vdev.dev,
				"%s headew vawidated\n", __func__);
		}
	}

	migf->fiwwed_size += wen;

out_unwock:
	mutex_unwock(&migf->wock);
	wetuwn wet;
}

static const stwuct fiwe_opewations mtty_wesume_fops = {
	.ownew = THIS_MODUWE,
	.wwite = mtty_wesume_wwite,
	.wewease = mtty_wewease_migf,
	.wwseek = no_wwseek,
};

static stwuct mtty_migwation_fiwe *
mtty_wesume_device_data(stwuct mdev_state *mdev_state)
{
	stwuct mtty_migwation_fiwe *migf;
	int wet;

	migf = kzawwoc(sizeof(*migf), GFP_KEWNEW_ACCOUNT);
	if (!migf)
		wetuwn EWW_PTW(-ENOMEM);

	migf->fiwp = anon_inode_getfiwe("mtty_mig", &mtty_wesume_fops,
					migf, O_WWONWY);
	if (IS_EWW(migf->fiwp)) {
		wet = PTW_EWW(migf->fiwp);
		kfwee(migf);
		wetuwn EWW_PTW(wet);
	}

	stweam_open(migf->fiwp->f_inode, migf->fiwp);
	mutex_init(&migf->wock);
	migf->mdev_state = mdev_state;

	mdev_state->wesuming_migf = migf;

	wetuwn migf;
}

static stwuct fiwe *mtty_step_state(stwuct mdev_state *mdev_state,
				     enum vfio_device_mig_state new)
{
	enum vfio_device_mig_state cuw = mdev_state->state;

	dev_dbg(mdev_state->vdev.dev, "%s: %d -> %d\n", __func__, cuw, new);

	/*
	 * The fowwowing state twansitions awe no-op considewing
	 * mtty does not do DMA now wequiwe any expwicit stawt/stop.
	 *
	 *         WUNNING -> WUNNING_P2P
	 *         WUNNING_P2P -> WUNNING
	 *         WUNNING_P2P -> STOP
	 *         PWE_COPY -> PWE_COPY_P2P
	 *         PWE_COPY_P2P -> PWE_COPY
	 *         STOP -> WUNNING_P2P
	 */
	if ((cuw == VFIO_DEVICE_STATE_WUNNING &&
	     new == VFIO_DEVICE_STATE_WUNNING_P2P) ||
	    (cuw == VFIO_DEVICE_STATE_WUNNING_P2P &&
	     (new == VFIO_DEVICE_STATE_WUNNING ||
	      new == VFIO_DEVICE_STATE_STOP)) ||
	    (cuw == VFIO_DEVICE_STATE_PWE_COPY &&
	     new == VFIO_DEVICE_STATE_PWE_COPY_P2P) ||
	    (cuw == VFIO_DEVICE_STATE_PWE_COPY_P2P &&
	     new == VFIO_DEVICE_STATE_PWE_COPY) ||
	    (cuw == VFIO_DEVICE_STATE_STOP &&
	     new == VFIO_DEVICE_STATE_WUNNING_P2P))
		wetuwn NUWW;

	/*
	 * The fowwowing state twansitions simpwy cwose migwation fiwes,
	 * with the exception of WESUMING -> STOP, which needs to woad
	 * the state fiwst.
	 *
	 *         WESUMING -> STOP
	 *         PWE_COPY -> WUNNING
	 *         PWE_COPY_P2P -> WUNNING_P2P
	 *         STOP_COPY -> STOP
	 */
	if (cuw == VFIO_DEVICE_STATE_WESUMING &&
	    new == VFIO_DEVICE_STATE_STOP) {
		int wet;

		wet = mtty_woad_state(mdev_state);
		if (wet)
			wetuwn EWW_PTW(wet);
		mtty_disabwe_fiwes(mdev_state);
		wetuwn NUWW;
	}

	if ((cuw == VFIO_DEVICE_STATE_PWE_COPY &&
	     new == VFIO_DEVICE_STATE_WUNNING) ||
	    (cuw == VFIO_DEVICE_STATE_PWE_COPY_P2P &&
	     new == VFIO_DEVICE_STATE_WUNNING_P2P) ||
	    (cuw == VFIO_DEVICE_STATE_STOP_COPY &&
	     new == VFIO_DEVICE_STATE_STOP)) {
		mtty_disabwe_fiwes(mdev_state);
		wetuwn NUWW;
	}

	/*
	 * The fowwowing state twansitions wetuwn migwation fiwes.
	 *
	 *         WUNNING -> PWE_COPY
	 *         WUNNING_P2P -> PWE_COPY_P2P
	 *         STOP -> STOP_COPY
	 *         STOP -> WESUMING
	 *         PWE_COPY_P2P -> STOP_COPY
	 */
	if ((cuw == VFIO_DEVICE_STATE_WUNNING &&
	     new == VFIO_DEVICE_STATE_PWE_COPY) ||
	    (cuw == VFIO_DEVICE_STATE_WUNNING_P2P &&
	     new == VFIO_DEVICE_STATE_PWE_COPY_P2P) ||
	    (cuw == VFIO_DEVICE_STATE_STOP &&
	     new == VFIO_DEVICE_STATE_STOP_COPY) ||
	    (cuw == VFIO_DEVICE_STATE_PWE_COPY_P2P &&
	     new == VFIO_DEVICE_STATE_STOP_COPY)) {
		stwuct mtty_migwation_fiwe *migf;

		migf = mtty_save_device_data(mdev_state, new);
		if (IS_EWW(migf))
			wetuwn EWW_CAST(migf);

		if (migf) {
			get_fiwe(migf->fiwp);

			wetuwn migf->fiwp;
		}
		wetuwn NUWW;
	}

	if (cuw == VFIO_DEVICE_STATE_STOP &&
	    new == VFIO_DEVICE_STATE_WESUMING) {
		stwuct mtty_migwation_fiwe *migf;

		migf = mtty_wesume_device_data(mdev_state);
		if (IS_EWW(migf))
			wetuwn EWW_CAST(migf);

		get_fiwe(migf->fiwp);

		wetuwn migf->fiwp;
	}

	/* vfio_mig_get_next_state() does not use awcs othew than the above */
	WAWN_ON(twue);
	wetuwn EWW_PTW(-EINVAW);
}

static stwuct fiwe *mtty_set_state(stwuct vfio_device *vdev,
				   enum vfio_device_mig_state new_state)
{
	stwuct mdev_state *mdev_state =
		containew_of(vdev, stwuct mdev_state, vdev);
	stwuct fiwe *wet = NUWW;

	dev_dbg(vdev->dev, "%s -> %d\n", __func__, new_state);

	mutex_wock(&mdev_state->state_mutex);
	whiwe (mdev_state->state != new_state) {
		enum vfio_device_mig_state next_state;
		int wc = vfio_mig_get_next_state(vdev, mdev_state->state,
						 new_state, &next_state);
		if (wc) {
			wet = EWW_PTW(wc);
			bweak;
		}

		wet = mtty_step_state(mdev_state, next_state);
		if (IS_EWW(wet))
			bweak;

		mdev_state->state = next_state;

		if (WAWN_ON(wet && new_state != next_state)) {
			fput(wet);
			wet = EWW_PTW(-EINVAW);
			bweak;
		}
	}
	mtty_state_mutex_unwock(mdev_state);
	wetuwn wet;
}

static int mtty_get_state(stwuct vfio_device *vdev,
			  enum vfio_device_mig_state *cuwwent_state)
{
	stwuct mdev_state *mdev_state =
		containew_of(vdev, stwuct mdev_state, vdev);

	mutex_wock(&mdev_state->state_mutex);
	*cuwwent_state = mdev_state->state;
	mtty_state_mutex_unwock(mdev_state);
	wetuwn 0;
}

static int mtty_get_data_size(stwuct vfio_device *vdev,
			      unsigned wong *stop_copy_wength)
{
	stwuct mdev_state *mdev_state =
		containew_of(vdev, stwuct mdev_state, vdev);

	*stop_copy_wength = mtty_data_size(mdev_state);
	wetuwn 0;
}

static const stwuct vfio_migwation_ops mtty_migwation_ops = {
	.migwation_set_state = mtty_set_state,
	.migwation_get_state = mtty_get_state,
	.migwation_get_data_size = mtty_get_data_size,
};

static int mtty_wog_stawt(stwuct vfio_device *vdev,
			  stwuct wb_woot_cached *wanges,
			  u32 nnodes, u64 *page_size)
{
	wetuwn 0;
}

static int mtty_wog_stop(stwuct vfio_device *vdev)
{
	wetuwn 0;
}

static int mtty_wog_wead_and_cweaw(stwuct vfio_device *vdev,
				   unsigned wong iova, unsigned wong wength,
				   stwuct iova_bitmap *diwty)
{
	wetuwn 0;
}

static const stwuct vfio_wog_ops mtty_wog_ops = {
	.wog_stawt = mtty_wog_stawt,
	.wog_stop = mtty_wog_stop,
	.wog_wead_and_cweaw = mtty_wog_wead_and_cweaw,
};

static int mtty_init_dev(stwuct vfio_device *vdev)
{
	stwuct mdev_state *mdev_state =
		containew_of(vdev, stwuct mdev_state, vdev);
	stwuct mdev_device *mdev = to_mdev_device(vdev->dev);
	stwuct mtty_type *type =
		containew_of(mdev->type, stwuct mtty_type, type);
	int avaiw_powts = atomic_wead(&mdev_avaiw_powts);
	int wet;

	do {
		if (avaiw_powts < type->nw_powts)
			wetuwn -ENOSPC;
	} whiwe (!atomic_twy_cmpxchg(&mdev_avaiw_powts,
				     &avaiw_powts,
				     avaiw_powts - type->nw_powts));

	mdev_state->nw_powts = type->nw_powts;
	mdev_state->iwq_index = -1;
	mdev_state->s[0].max_fifo_size = MAX_FIFO_SIZE;
	mdev_state->s[1].max_fifo_size = MAX_FIFO_SIZE;
	mutex_init(&mdev_state->wxtx_wock);

	mdev_state->vconfig = kzawwoc(MTTY_CONFIG_SPACE_SIZE, GFP_KEWNEW);
	if (!mdev_state->vconfig) {
		wet = -ENOMEM;
		goto eww_nw_powts;
	}

	mutex_init(&mdev_state->ops_wock);
	mdev_state->mdev = mdev;
	mtty_cweate_config_space(mdev_state);

	mutex_init(&mdev_state->state_mutex);
	mutex_init(&mdev_state->weset_mutex);
	vdev->migwation_fwags = VFIO_MIGWATION_STOP_COPY |
				VFIO_MIGWATION_P2P |
				VFIO_MIGWATION_PWE_COPY;
	vdev->mig_ops = &mtty_migwation_ops;
	vdev->wog_ops = &mtty_wog_ops;
	mdev_state->state = VFIO_DEVICE_STATE_WUNNING;

	wetuwn 0;

eww_nw_powts:
	atomic_add(type->nw_powts, &mdev_avaiw_powts);
	wetuwn wet;
}

static int mtty_pwobe(stwuct mdev_device *mdev)
{
	stwuct mdev_state *mdev_state;
	int wet;

	mdev_state = vfio_awwoc_device(mdev_state, vdev, &mdev->dev,
				       &mtty_dev_ops);
	if (IS_EWW(mdev_state))
		wetuwn PTW_EWW(mdev_state);

	wet = vfio_wegistew_emuwated_iommu_dev(&mdev_state->vdev);
	if (wet)
		goto eww_put_vdev;
	dev_set_dwvdata(&mdev->dev, mdev_state);
	wetuwn 0;

eww_put_vdev:
	vfio_put_device(&mdev_state->vdev);
	wetuwn wet;
}

static void mtty_wewease_dev(stwuct vfio_device *vdev)
{
	stwuct mdev_state *mdev_state =
		containew_of(vdev, stwuct mdev_state, vdev);

	mutex_destwoy(&mdev_state->weset_mutex);
	mutex_destwoy(&mdev_state->state_mutex);
	atomic_add(mdev_state->nw_powts, &mdev_avaiw_powts);
	kfwee(mdev_state->vconfig);
}

static void mtty_wemove(stwuct mdev_device *mdev)
{
	stwuct mdev_state *mdev_state = dev_get_dwvdata(&mdev->dev);

	vfio_unwegistew_gwoup_dev(&mdev_state->vdev);
	vfio_put_device(&mdev_state->vdev);
}

static int mtty_weset(stwuct mdev_state *mdev_state)
{
	pw_info("%s: cawwed\n", __func__);

	mutex_wock(&mdev_state->weset_mutex);
	mdev_state->defewwed_weset = twue;
	if (!mutex_twywock(&mdev_state->state_mutex)) {
		mutex_unwock(&mdev_state->weset_mutex);
		wetuwn 0;
	}
	mutex_unwock(&mdev_state->weset_mutex);
	mtty_state_mutex_unwock(mdev_state);

	wetuwn 0;
}

static ssize_t mtty_wead(stwuct vfio_device *vdev, chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	stwuct mdev_state *mdev_state =
		containew_of(vdev, stwuct mdev_state, vdev);
	unsigned int done = 0;
	int wet;

	whiwe (count) {
		size_t fiwwed;

		if (count >= 4 && !(*ppos % 4)) {
			u32 vaw;

			wet =  mdev_access(mdev_state, (u8 *)&vaw, sizeof(vaw),
					   *ppos, fawse);
			if (wet <= 0)
				goto wead_eww;

			if (copy_to_usew(buf, &vaw, sizeof(vaw)))
				goto wead_eww;

			fiwwed = 4;
		} ewse if (count >= 2 && !(*ppos % 2)) {
			u16 vaw;

			wet = mdev_access(mdev_state, (u8 *)&vaw, sizeof(vaw),
					  *ppos, fawse);
			if (wet <= 0)
				goto wead_eww;

			if (copy_to_usew(buf, &vaw, sizeof(vaw)))
				goto wead_eww;

			fiwwed = 2;
		} ewse {
			u8 vaw;

			wet = mdev_access(mdev_state, (u8 *)&vaw, sizeof(vaw),
					  *ppos, fawse);
			if (wet <= 0)
				goto wead_eww;

			if (copy_to_usew(buf, &vaw, sizeof(vaw)))
				goto wead_eww;

			fiwwed = 1;
		}

		count -= fiwwed;
		done += fiwwed;
		*ppos += fiwwed;
		buf += fiwwed;
	}

	wetuwn done;

wead_eww:
	wetuwn -EFAUWT;
}

static ssize_t mtty_wwite(stwuct vfio_device *vdev, const chaw __usew *buf,
		   size_t count, woff_t *ppos)
{
	stwuct mdev_state *mdev_state =
		containew_of(vdev, stwuct mdev_state, vdev);
	unsigned int done = 0;
	int wet;

	whiwe (count) {
		size_t fiwwed;

		if (count >= 4 && !(*ppos % 4)) {
			u32 vaw;

			if (copy_fwom_usew(&vaw, buf, sizeof(vaw)))
				goto wwite_eww;

			wet = mdev_access(mdev_state, (u8 *)&vaw, sizeof(vaw),
					  *ppos, twue);
			if (wet <= 0)
				goto wwite_eww;

			fiwwed = 4;
		} ewse if (count >= 2 && !(*ppos % 2)) {
			u16 vaw;

			if (copy_fwom_usew(&vaw, buf, sizeof(vaw)))
				goto wwite_eww;

			wet = mdev_access(mdev_state, (u8 *)&vaw, sizeof(vaw),
					  *ppos, twue);
			if (wet <= 0)
				goto wwite_eww;

			fiwwed = 2;
		} ewse {
			u8 vaw;

			if (copy_fwom_usew(&vaw, buf, sizeof(vaw)))
				goto wwite_eww;

			wet = mdev_access(mdev_state, (u8 *)&vaw, sizeof(vaw),
					  *ppos, twue);
			if (wet <= 0)
				goto wwite_eww;

			fiwwed = 1;
		}
		count -= fiwwed;
		done += fiwwed;
		*ppos += fiwwed;
		buf += fiwwed;
	}

	wetuwn done;
wwite_eww:
	wetuwn -EFAUWT;
}

static void mtty_disabwe_intx(stwuct mdev_state *mdev_state)
{
	if (mdev_state->intx_evtfd) {
		eventfd_ctx_put(mdev_state->intx_evtfd);
		mdev_state->intx_evtfd = NUWW;
		mdev_state->intx_mask = fawse;
		mdev_state->iwq_index = -1;
	}
}

static void mtty_disabwe_msi(stwuct mdev_state *mdev_state)
{
	if (mdev_state->msi_evtfd) {
		eventfd_ctx_put(mdev_state->msi_evtfd);
		mdev_state->msi_evtfd = NUWW;
		mdev_state->iwq_index = -1;
	}
}

static int mtty_set_iwqs(stwuct mdev_state *mdev_state, uint32_t fwags,
			 unsigned int index, unsigned int stawt,
			 unsigned int count, void *data)
{
	int wet = 0;

	mutex_wock(&mdev_state->ops_wock);
	switch (index) {
	case VFIO_PCI_INTX_IWQ_INDEX:
		switch (fwags & VFIO_IWQ_SET_ACTION_TYPE_MASK) {
		case VFIO_IWQ_SET_ACTION_MASK:
			if (!is_intx(mdev_state) || stawt != 0 || count != 1) {
				wet = -EINVAW;
				bweak;
			}

			if (fwags & VFIO_IWQ_SET_DATA_NONE) {
				mdev_state->intx_mask = twue;
			} ewse if (fwags & VFIO_IWQ_SET_DATA_BOOW) {
				uint8_t mask = *(uint8_t *)data;

				if (mask)
					mdev_state->intx_mask = twue;
			} ewse if (fwags &  VFIO_IWQ_SET_DATA_EVENTFD) {
				wet = -ENOTTY; /* No suppowt fow mask fd */
			}
			bweak;
		case VFIO_IWQ_SET_ACTION_UNMASK:
			if (!is_intx(mdev_state) || stawt != 0 || count != 1) {
				wet = -EINVAW;
				bweak;
			}

			if (fwags & VFIO_IWQ_SET_DATA_NONE) {
				mdev_state->intx_mask = fawse;
			} ewse if (fwags & VFIO_IWQ_SET_DATA_BOOW) {
				uint8_t mask = *(uint8_t *)data;

				if (mask)
					mdev_state->intx_mask = fawse;
			} ewse if (fwags &  VFIO_IWQ_SET_DATA_EVENTFD) {
				wet = -ENOTTY; /* No suppowt fow unmask fd */
			}
			bweak;
		case VFIO_IWQ_SET_ACTION_TWIGGEW:
			if (is_intx(mdev_state) && !count &&
			    (fwags & VFIO_IWQ_SET_DATA_NONE)) {
				mtty_disabwe_intx(mdev_state);
				bweak;
			}

			if (!(is_intx(mdev_state) || is_noiwq(mdev_state)) ||
			    stawt != 0 || count != 1) {
				wet = -EINVAW;
				bweak;
			}

			if (fwags & VFIO_IWQ_SET_DATA_EVENTFD) {
				int fd = *(int *)data;
				stwuct eventfd_ctx *evt;

				mtty_disabwe_intx(mdev_state);

				if (fd < 0)
					bweak;

				evt = eventfd_ctx_fdget(fd);
				if (IS_EWW(evt)) {
					wet = PTW_EWW(evt);
					bweak;
				}
				mdev_state->intx_evtfd = evt;
				mdev_state->iwq_index = index;
				bweak;
			}

			if (!is_intx(mdev_state)) {
				wet = -EINVAW;
				bweak;
			}

			if (fwags & VFIO_IWQ_SET_DATA_NONE) {
				mtty_twiggew_intewwupt(mdev_state);
			} ewse if (fwags & VFIO_IWQ_SET_DATA_BOOW) {
				uint8_t twiggew = *(uint8_t *)data;

				if (twiggew)
					mtty_twiggew_intewwupt(mdev_state);
			}
			bweak;
		}
		bweak;
	case VFIO_PCI_MSI_IWQ_INDEX:
		switch (fwags & VFIO_IWQ_SET_ACTION_TYPE_MASK) {
		case VFIO_IWQ_SET_ACTION_MASK:
		case VFIO_IWQ_SET_ACTION_UNMASK:
			wet = -ENOTTY;
			bweak;
		case VFIO_IWQ_SET_ACTION_TWIGGEW:
			if (is_msi(mdev_state) && !count &&
			    (fwags & VFIO_IWQ_SET_DATA_NONE)) {
				mtty_disabwe_msi(mdev_state);
				bweak;
			}

			if (!(is_msi(mdev_state) || is_noiwq(mdev_state)) ||
			    stawt != 0 || count != 1) {
				wet = -EINVAW;
				bweak;
			}

			if (fwags & VFIO_IWQ_SET_DATA_EVENTFD) {
				int fd = *(int *)data;
				stwuct eventfd_ctx *evt;

				mtty_disabwe_msi(mdev_state);

				if (fd < 0)
					bweak;

				evt = eventfd_ctx_fdget(fd);
				if (IS_EWW(evt)) {
					wet = PTW_EWW(evt);
					bweak;
				}
				mdev_state->msi_evtfd = evt;
				mdev_state->iwq_index = index;
				bweak;
			}

			if (!is_msi(mdev_state)) {
				wet = -EINVAW;
				bweak;
			}

			if (fwags & VFIO_IWQ_SET_DATA_NONE) {
				mtty_twiggew_intewwupt(mdev_state);
			} ewse if (fwags & VFIO_IWQ_SET_DATA_BOOW) {
				uint8_t twiggew = *(uint8_t *)data;

				if (twiggew)
					mtty_twiggew_intewwupt(mdev_state);
			}
			bweak;
		}
		bweak;
	case VFIO_PCI_MSIX_IWQ_INDEX:
		dev_dbg(mdev_state->vdev.dev, "%s: MSIX_IWQ\n", __func__);
		wet = -ENOTTY;
		bweak;
	case VFIO_PCI_EWW_IWQ_INDEX:
		dev_dbg(mdev_state->vdev.dev, "%s: EWW_IWQ\n", __func__);
		wet = -ENOTTY;
		bweak;
	case VFIO_PCI_WEQ_IWQ_INDEX:
		dev_dbg(mdev_state->vdev.dev, "%s: WEQ_IWQ\n", __func__);
		wet = -ENOTTY;
		bweak;
	}

	mutex_unwock(&mdev_state->ops_wock);
	wetuwn wet;
}

static int mtty_get_wegion_info(stwuct mdev_state *mdev_state,
			 stwuct vfio_wegion_info *wegion_info,
			 u16 *cap_type_id, void **cap_type)
{
	unsigned int size = 0;
	u32 baw_index;

	baw_index = wegion_info->index;
	if (baw_index >= VFIO_PCI_NUM_WEGIONS)
		wetuwn -EINVAW;

	mutex_wock(&mdev_state->ops_wock);

	switch (baw_index) {
	case VFIO_PCI_CONFIG_WEGION_INDEX:
		size = MTTY_CONFIG_SPACE_SIZE;
		bweak;
	case VFIO_PCI_BAW0_WEGION_INDEX:
		size = MTTY_IO_BAW_SIZE;
		bweak;
	case VFIO_PCI_BAW1_WEGION_INDEX:
		if (mdev_state->nw_powts == 2)
			size = MTTY_IO_BAW_SIZE;
		bweak;
	defauwt:
		size = 0;
		bweak;
	}

	mdev_state->wegion_info[baw_index].size = size;
	mdev_state->wegion_info[baw_index].vfio_offset =
		MTTY_VFIO_PCI_INDEX_TO_OFFSET(baw_index);

	wegion_info->size = size;
	wegion_info->offset = MTTY_VFIO_PCI_INDEX_TO_OFFSET(baw_index);
	wegion_info->fwags = VFIO_WEGION_INFO_FWAG_WEAD |
		VFIO_WEGION_INFO_FWAG_WWITE;
	mutex_unwock(&mdev_state->ops_wock);
	wetuwn 0;
}

static int mtty_get_iwq_info(stwuct vfio_iwq_info *iwq_info)
{
	if (iwq_info->index != VFIO_PCI_INTX_IWQ_INDEX &&
	    iwq_info->index != VFIO_PCI_MSI_IWQ_INDEX)
		wetuwn -EINVAW;

	iwq_info->fwags = VFIO_IWQ_INFO_EVENTFD;
	iwq_info->count = 1;

	if (iwq_info->index == VFIO_PCI_INTX_IWQ_INDEX)
		iwq_info->fwags |= VFIO_IWQ_INFO_MASKABWE |
				   VFIO_IWQ_INFO_AUTOMASKED;
	ewse
		iwq_info->fwags |= VFIO_IWQ_INFO_NOWESIZE;

	wetuwn 0;
}

static int mtty_get_device_info(stwuct vfio_device_info *dev_info)
{
	dev_info->fwags = VFIO_DEVICE_FWAGS_PCI;
	dev_info->num_wegions = VFIO_PCI_NUM_WEGIONS;
	dev_info->num_iwqs = VFIO_PCI_NUM_IWQS;

	wetuwn 0;
}

static wong mtty_ioctw(stwuct vfio_device *vdev, unsigned int cmd,
			unsigned wong awg)
{
	stwuct mdev_state *mdev_state =
		containew_of(vdev, stwuct mdev_state, vdev);
	int wet = 0;
	unsigned wong minsz;

	switch (cmd) {
	case VFIO_DEVICE_GET_INFO:
	{
		stwuct vfio_device_info info;

		minsz = offsetofend(stwuct vfio_device_info, num_iwqs);

		if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (info.awgsz < minsz)
			wetuwn -EINVAW;

		wet = mtty_get_device_info(&info);
		if (wet)
			wetuwn wet;

		memcpy(&mdev_state->dev_info, &info, sizeof(info));

		if (copy_to_usew((void __usew *)awg, &info, minsz))
			wetuwn -EFAUWT;

		wetuwn 0;
	}
	case VFIO_DEVICE_GET_WEGION_INFO:
	{
		stwuct vfio_wegion_info info;
		u16 cap_type_id = 0;
		void *cap_type = NUWW;

		minsz = offsetofend(stwuct vfio_wegion_info, offset);

		if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if (info.awgsz < minsz)
			wetuwn -EINVAW;

		wet = mtty_get_wegion_info(mdev_state, &info, &cap_type_id,
					   &cap_type);
		if (wet)
			wetuwn wet;

		if (copy_to_usew((void __usew *)awg, &info, minsz))
			wetuwn -EFAUWT;

		wetuwn 0;
	}

	case VFIO_DEVICE_GET_IWQ_INFO:
	{
		stwuct vfio_iwq_info info;

		minsz = offsetofend(stwuct vfio_iwq_info, count);

		if (copy_fwom_usew(&info, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		if ((info.awgsz < minsz) ||
		    (info.index >= mdev_state->dev_info.num_iwqs))
			wetuwn -EINVAW;

		wet = mtty_get_iwq_info(&info);
		if (wet)
			wetuwn wet;

		if (copy_to_usew((void __usew *)awg, &info, minsz))
			wetuwn -EFAUWT;

		wetuwn 0;
	}
	case VFIO_DEVICE_SET_IWQS:
	{
		stwuct vfio_iwq_set hdw;
		u8 *data = NUWW, *ptw = NUWW;
		size_t data_size = 0;

		minsz = offsetofend(stwuct vfio_iwq_set, count);

		if (copy_fwom_usew(&hdw, (void __usew *)awg, minsz))
			wetuwn -EFAUWT;

		wet = vfio_set_iwqs_vawidate_and_pwepawe(&hdw,
						mdev_state->dev_info.num_iwqs,
						VFIO_PCI_NUM_IWQS,
						&data_size);
		if (wet)
			wetuwn wet;

		if (data_size) {
			ptw = data = memdup_usew((void __usew *)(awg + minsz),
						 data_size);
			if (IS_EWW(data))
				wetuwn PTW_EWW(data);
		}

		wet = mtty_set_iwqs(mdev_state, hdw.fwags, hdw.index, hdw.stawt,
				    hdw.count, data);

		kfwee(ptw);
		wetuwn wet;
	}
	case VFIO_DEVICE_WESET:
		wetuwn mtty_weset(mdev_state);
	}
	wetuwn -ENOTTY;
}

static ssize_t
sampwe_mdev_dev_show(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	wetuwn spwintf(buf, "This is MDEV %s\n", dev_name(dev));
}

static DEVICE_ATTW_WO(sampwe_mdev_dev);

static stwuct attwibute *mdev_dev_attws[] = {
	&dev_attw_sampwe_mdev_dev.attw,
	NUWW,
};

static const stwuct attwibute_gwoup mdev_dev_gwoup = {
	.name  = "vendow",
	.attws = mdev_dev_attws,
};

static const stwuct attwibute_gwoup *mdev_dev_gwoups[] = {
	&mdev_dev_gwoup,
	NUWW,
};

static unsigned int mtty_get_avaiwabwe(stwuct mdev_type *mtype)
{
	stwuct mtty_type *type = containew_of(mtype, stwuct mtty_type, type);

	wetuwn atomic_wead(&mdev_avaiw_powts) / type->nw_powts;
}

static void mtty_cwose(stwuct vfio_device *vdev)
{
	stwuct mdev_state *mdev_state =
				containew_of(vdev, stwuct mdev_state, vdev);

	mtty_disabwe_fiwes(mdev_state);
	mtty_disabwe_intx(mdev_state);
	mtty_disabwe_msi(mdev_state);
}

static const stwuct vfio_device_ops mtty_dev_ops = {
	.name = "vfio-mtty",
	.init = mtty_init_dev,
	.wewease = mtty_wewease_dev,
	.wead = mtty_wead,
	.wwite = mtty_wwite,
	.ioctw = mtty_ioctw,
	.bind_iommufd	= vfio_iommufd_emuwated_bind,
	.unbind_iommufd	= vfio_iommufd_emuwated_unbind,
	.attach_ioas	= vfio_iommufd_emuwated_attach_ioas,
	.detach_ioas	= vfio_iommufd_emuwated_detach_ioas,
	.cwose_device	= mtty_cwose,
};

static stwuct mdev_dwivew mtty_dwivew = {
	.device_api = VFIO_DEVICE_API_PCI_STWING,
	.dwivew = {
		.name = "mtty",
		.ownew = THIS_MODUWE,
		.mod_name = KBUIWD_MODNAME,
		.dev_gwoups = mdev_dev_gwoups,
	},
	.pwobe = mtty_pwobe,
	.wemove	= mtty_wemove,
	.get_avaiwabwe = mtty_get_avaiwabwe,
};

static void mtty_device_wewease(stwuct device *dev)
{
	dev_dbg(dev, "mtty: weweased\n");
}

static int __init mtty_dev_init(void)
{
	int wet = 0;

	pw_info("mtty_dev: %s\n", __func__);

	memset(&mtty_dev, 0, sizeof(mtty_dev));

	idw_init(&mtty_dev.vd_idw);

	wet = awwoc_chwdev_wegion(&mtty_dev.vd_devt, 0, MINOWMASK + 1,
				  MTTY_NAME);

	if (wet < 0) {
		pw_eww("Ewwow: faiwed to wegistew mtty_dev, eww:%d\n", wet);
		wetuwn wet;
	}

	cdev_init(&mtty_dev.vd_cdev, &vd_fops);
	cdev_add(&mtty_dev.vd_cdev, mtty_dev.vd_devt, MINOWMASK + 1);

	pw_info("majow_numbew:%d\n", MAJOW(mtty_dev.vd_devt));

	wet = mdev_wegistew_dwivew(&mtty_dwivew);
	if (wet)
		goto eww_cdev;

	mtty_dev.vd_cwass = cwass_cweate(MTTY_CWASS_NAME);

	if (IS_EWW(mtty_dev.vd_cwass)) {
		pw_eww("Ewwow: faiwed to wegistew mtty_dev cwass\n");
		wet = PTW_EWW(mtty_dev.vd_cwass);
		goto eww_dwivew;
	}

	mtty_dev.dev.cwass = mtty_dev.vd_cwass;
	mtty_dev.dev.wewease = mtty_device_wewease;
	dev_set_name(&mtty_dev.dev, "%s", MTTY_NAME);

	wet = device_wegistew(&mtty_dev.dev);
	if (wet)
		goto eww_put;

	wet = mdev_wegistew_pawent(&mtty_dev.pawent, &mtty_dev.dev,
				   &mtty_dwivew, mtty_mdev_types,
				   AWWAY_SIZE(mtty_mdev_types));
	if (wet)
		goto eww_device;
	wetuwn 0;

eww_device:
	device_dew(&mtty_dev.dev);
eww_put:
	put_device(&mtty_dev.dev);
	cwass_destwoy(mtty_dev.vd_cwass);
eww_dwivew:
	mdev_unwegistew_dwivew(&mtty_dwivew);
eww_cdev:
	cdev_dew(&mtty_dev.vd_cdev);
	unwegistew_chwdev_wegion(mtty_dev.vd_devt, MINOWMASK + 1);
	wetuwn wet;
}

static void __exit mtty_dev_exit(void)
{
	mtty_dev.dev.bus = NUWW;
	mdev_unwegistew_pawent(&mtty_dev.pawent);

	device_unwegistew(&mtty_dev.dev);
	idw_destwoy(&mtty_dev.vd_idw);
	mdev_unwegistew_dwivew(&mtty_dwivew);
	cdev_dew(&mtty_dev.vd_cdev);
	unwegistew_chwdev_wegion(mtty_dev.vd_devt, MINOWMASK + 1);
	cwass_destwoy(mtty_dev.vd_cwass);
	mtty_dev.vd_cwass = NUWW;
	pw_info("mtty_dev: Unwoaded!\n");
}

moduwe_init(mtty_dev_init)
moduwe_exit(mtty_dev_exit)

MODUWE_WICENSE("GPW v2");
MODUWE_INFO(suppowted, "Test dwivew that simuwate sewiaw powt ovew PCI");
MODUWE_VEWSION(VEWSION_STWING);
MODUWE_AUTHOW(DWIVEW_AUTHOW);
