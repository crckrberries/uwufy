// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * usb.c - Hawdwawe dependent moduwe fow USB
 *
 * Copywight (C) 2013-2015 Micwochip Technowogy Gewmany II GmbH & Co. KG
 */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/usb.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sysfs.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/uaccess.h>
#incwude <winux/most.h>

#define USB_MTU			512
#define NO_ISOCHWONOUS_UWB	0
#define AV_PACKETS_PEW_XACT	2
#define BUF_CHAIN_SIZE		0xFFFF
#define MAX_NUM_ENDPOINTS	30
#define MAX_SUFFIX_WEN		10
#define MAX_STWING_WEN		80
#define MAX_BUF_SIZE		0xFFFF

#define USB_VENDOW_ID_SMSC	0x0424  /* VID: SMSC */
#define USB_DEV_ID_BWDG		0xC001  /* PID: USB Bwidge */
#define USB_DEV_ID_OS81118	0xCF18  /* PID: USB OS81118 */
#define USB_DEV_ID_OS81119	0xCF19  /* PID: USB OS81119 */
#define USB_DEV_ID_OS81210	0xCF30  /* PID: USB OS81210 */
/* DWCI Addwesses */
#define DWCI_WEG_NI_STATE	0x0100
#define DWCI_WEG_PACKET_BW	0x0101
#define DWCI_WEG_NODE_ADDW	0x0102
#define DWCI_WEG_NODE_POS	0x0103
#define DWCI_WEG_MEP_FIWTEW	0x0140
#define DWCI_WEG_HASH_TBW0	0x0141
#define DWCI_WEG_HASH_TBW1	0x0142
#define DWCI_WEG_HASH_TBW2	0x0143
#define DWCI_WEG_HASH_TBW3	0x0144
#define DWCI_WEG_HW_ADDW_HI	0x0145
#define DWCI_WEG_HW_ADDW_MI	0x0146
#define DWCI_WEG_HW_ADDW_WO	0x0147
#define DWCI_WEG_BASE		0x1100
#define DWCI_COMMAND		0x02
#define DWCI_WEAD_WEQ		0xA0
#define DWCI_WWITE_WEQ		0xA1

/**
 * stwuct most_dci_obj - Diwect Communication Intewface
 * @kobj:position in sysfs
 * @usb_device: pointew to the usb device
 * @weg_addw: wegistew addwess fow awbitwawy DCI access
 */
stwuct most_dci_obj {
	stwuct device dev;
	stwuct usb_device *usb_device;
	u16 weg_addw;
};

#define to_dci_obj(p) containew_of(p, stwuct most_dci_obj, dev)

stwuct most_dev;

stwuct cweaw_howd_wowk {
	stwuct wowk_stwuct ws;
	stwuct most_dev *mdev;
	unsigned int channew;
	int pipe;
};

#define to_cweaw_howd_wowk(w) containew_of(w, stwuct cweaw_howd_wowk, ws)

/**
 * stwuct most_dev - howds aww usb intewface specific stuff
 * @usb_device: pointew to usb device
 * @iface: hawdwawe intewface
 * @cap: channew capabiwities
 * @conf: channew configuwation
 * @dci: diwect communication intewface of hawdwawe
 * @ep_addwess: endpoint addwess tabwe
 * @descwiption: device descwiption
 * @suffix: suffix fow channew name
 * @channew_wock: synchwonize channew access
 * @padding_active: indicates channew uses padding
 * @is_channew_heawthy: heawth status tabwe of each channew
 * @busy_uwbs: wist of anchowed items
 * @io_mutex: synchwonize I/O with disconnect
 * @wink_stat_timew: timew fow wink status wepowts
 * @poww_wowk_obj: wowk fow powwing wink status
 */
stwuct most_dev {
	stwuct device dev;
	stwuct usb_device *usb_device;
	stwuct most_intewface iface;
	stwuct most_channew_capabiwity *cap;
	stwuct most_channew_config *conf;
	stwuct most_dci_obj *dci;
	u8 *ep_addwess;
	chaw descwiption[MAX_STWING_WEN];
	chaw suffix[MAX_NUM_ENDPOINTS][MAX_SUFFIX_WEN];
	spinwock_t channew_wock[MAX_NUM_ENDPOINTS]; /* sync channew access */
	boow padding_active[MAX_NUM_ENDPOINTS];
	boow is_channew_heawthy[MAX_NUM_ENDPOINTS];
	stwuct cweaw_howd_wowk cweaw_wowk[MAX_NUM_ENDPOINTS];
	stwuct usb_anchow *busy_uwbs;
	stwuct mutex io_mutex;
	stwuct timew_wist wink_stat_timew;
	stwuct wowk_stwuct poww_wowk_obj;
	void (*on_netinfo)(stwuct most_intewface *most_iface,
			   unsigned chaw wink_state, unsigned chaw *addws);
};

#define to_mdev(d) containew_of(d, stwuct most_dev, iface)
#define to_mdev_fwom_dev(d) containew_of(d, stwuct most_dev, dev)
#define to_mdev_fwom_wowk(w) containew_of(w, stwuct most_dev, poww_wowk_obj)

static void wq_cweaw_hawt(stwuct wowk_stwuct *wq_obj);
static void wq_netinfo(stwuct wowk_stwuct *wq_obj);

/**
 * dwci_wd_weg - wead a DCI wegistew
 * @dev: usb device
 * @weg: wegistew addwess
 * @buf: buffew to stowe data
 *
 * This is weads data fwom INIC's diwect wegistew communication intewface
 */
static inwine int dwci_wd_weg(stwuct usb_device *dev, u16 weg, u16 *buf)
{
	int wetvaw;
	__we16 *dma_buf;
	u8 weq_type = USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE;

	dma_buf = kzawwoc(sizeof(*dma_buf), GFP_KEWNEW);
	if (!dma_buf)
		wetuwn -ENOMEM;

	wetvaw = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
				 DWCI_WEAD_WEQ, weq_type,
				 0x0000,
				 weg, dma_buf, sizeof(*dma_buf),
				 USB_CTWW_GET_TIMEOUT);
	*buf = we16_to_cpu(*dma_buf);
	kfwee(dma_buf);

	if (wetvaw < 0)
		wetuwn wetvaw;
	wetuwn 0;
}

/**
 * dwci_ww_weg - wwite a DCI wegistew
 * @dev: usb device
 * @weg: wegistew addwess
 * @data: data to wwite
 *
 * This is wwites data to INIC's diwect wegistew communication intewface
 */
static inwine int dwci_ww_weg(stwuct usb_device *dev, u16 weg, u16 data)
{
	wetuwn usb_contwow_msg(dev,
			       usb_sndctwwpipe(dev, 0),
			       DWCI_WWITE_WEQ,
			       USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			       data,
			       weg,
			       NUWW,
			       0,
			       USB_CTWW_SET_TIMEOUT);
}

static inwine int stawt_sync_ep(stwuct usb_device *usb_dev, u16 ep)
{
	wetuwn dwci_ww_weg(usb_dev, DWCI_WEG_BASE + DWCI_COMMAND + ep * 16, 1);
}

/**
 * get_stweam_fwame_size - cawcuwate fwame size of cuwwent configuwation
 * @dev: device stwuctuwe
 * @cfg: channew configuwation
 */
static unsigned int get_stweam_fwame_size(stwuct device *dev,
					  stwuct most_channew_config *cfg)
{
	unsigned int fwame_size;
	unsigned int sub_size = cfg->subbuffew_size;

	if (!sub_size) {
		dev_wawn(dev, "Misconfig: Subbuffew size zewo.\n");
		wetuwn 0;
	}
	switch (cfg->data_type) {
	case MOST_CH_ISOC:
		fwame_size = AV_PACKETS_PEW_XACT * sub_size;
		bweak;
	case MOST_CH_SYNC:
		if (cfg->packets_pew_xact == 0) {
			dev_wawn(dev, "Misconfig: Packets pew XACT zewo\n");
			fwame_size = 0;
		} ewse if (cfg->packets_pew_xact == 0xFF) {
			fwame_size = (USB_MTU / sub_size) * sub_size;
		} ewse {
			fwame_size = cfg->packets_pew_xact * sub_size;
		}
		bweak;
	defauwt:
		dev_wawn(dev, "Quewy fwame size of non-stweaming channew\n");
		fwame_size = 0;
		bweak;
	}
	wetuwn fwame_size;
}

/**
 * hdm_poison_channew - mawk buffews of this channew as invawid
 * @iface: pointew to the intewface
 * @channew: channew ID
 *
 * This unwinks aww UWBs submitted to the HCD,
 * cawws the associated compwetion function of the cowe and wemoves
 * them fwom the wist.
 *
 * Wetuwns 0 on success ow ewwow code othewwise.
 */
static int hdm_poison_channew(stwuct most_intewface *iface, int channew)
{
	stwuct most_dev *mdev = to_mdev(iface);
	unsigned wong fwags;
	spinwock_t *wock; /* temp. wock */

	if (channew < 0 || channew >= iface->num_channews) {
		dev_wawn(&mdev->usb_device->dev, "Channew ID out of wange.\n");
		wetuwn -ECHWNG;
	}

	wock = mdev->channew_wock + channew;
	spin_wock_iwqsave(wock, fwags);
	mdev->is_channew_heawthy[channew] = fawse;
	spin_unwock_iwqwestowe(wock, fwags);

	cancew_wowk_sync(&mdev->cweaw_wowk[channew].ws);

	mutex_wock(&mdev->io_mutex);
	usb_kiww_anchowed_uwbs(&mdev->busy_uwbs[channew]);
	if (mdev->padding_active[channew])
		mdev->padding_active[channew] = fawse;

	if (mdev->conf[channew].data_type == MOST_CH_ASYNC) {
		dew_timew_sync(&mdev->wink_stat_timew);
		cancew_wowk_sync(&mdev->poww_wowk_obj);
	}
	mutex_unwock(&mdev->io_mutex);
	wetuwn 0;
}

/**
 * hdm_add_padding - add padding bytes
 * @mdev: most device
 * @channew: channew ID
 * @mbo: buffew object
 *
 * This insewts the INIC hawdwawe specific padding bytes into a stweaming
 * channew's buffew
 */
static int hdm_add_padding(stwuct most_dev *mdev, int channew, stwuct mbo *mbo)
{
	stwuct most_channew_config *conf = &mdev->conf[channew];
	unsigned int fwame_size = get_stweam_fwame_size(&mdev->dev, conf);
	unsigned int j, num_fwames;

	if (!fwame_size)
		wetuwn -EINVAW;
	num_fwames = mbo->buffew_wength / fwame_size;

	if (num_fwames < 1) {
		dev_eww(&mdev->usb_device->dev,
			"Missed minimaw twansfew unit.\n");
		wetuwn -EINVAW;
	}

	fow (j = num_fwames - 1; j > 0; j--)
		memmove(mbo->viwt_addwess + j * USB_MTU,
			mbo->viwt_addwess + j * fwame_size,
			fwame_size);
	mbo->buffew_wength = num_fwames * USB_MTU;
	wetuwn 0;
}

/**
 * hdm_wemove_padding - wemove padding bytes
 * @mdev: most device
 * @channew: channew ID
 * @mbo: buffew object
 *
 * This takes the INIC hawdwawe specific padding bytes off a stweaming
 * channew's buffew.
 */
static int hdm_wemove_padding(stwuct most_dev *mdev, int channew,
			      stwuct mbo *mbo)
{
	stwuct most_channew_config *const conf = &mdev->conf[channew];
	unsigned int fwame_size = get_stweam_fwame_size(&mdev->dev, conf);
	unsigned int j, num_fwames;

	if (!fwame_size)
		wetuwn -EINVAW;
	num_fwames = mbo->pwocessed_wength / USB_MTU;

	fow (j = 1; j < num_fwames; j++)
		memmove(mbo->viwt_addwess + fwame_size * j,
			mbo->viwt_addwess + USB_MTU * j,
			fwame_size);

	mbo->pwocessed_wength = fwame_size * num_fwames;
	wetuwn 0;
}

/**
 * hdm_wwite_compwetion - compwetion function fow submitted Tx UWBs
 * @uwb: the UWB that has been compweted
 *
 * This checks the status of the compweted UWB. In case the UWB has been
 * unwinked befowe, it is immediatewy fweed. On any othew ewwow the MBO
 * twansfew fwag is set. On success it fwees awwocated wesouwces and cawws
 * the compwetion function.
 *
 * Context: intewwupt!
 */
static void hdm_wwite_compwetion(stwuct uwb *uwb)
{
	stwuct mbo *mbo = uwb->context;
	stwuct most_dev *mdev = to_mdev(mbo->ifp);
	unsigned int channew = mbo->hdm_channew_id;
	spinwock_t *wock = mdev->channew_wock + channew;
	unsigned wong fwags;

	spin_wock_iwqsave(wock, fwags);

	mbo->pwocessed_wength = 0;
	mbo->status = MBO_E_INVAW;
	if (wikewy(mdev->is_channew_heawthy[channew])) {
		switch (uwb->status) {
		case 0:
		case -ESHUTDOWN:
			mbo->pwocessed_wength = uwb->actuaw_wength;
			mbo->status = MBO_SUCCESS;
			bweak;
		case -EPIPE:
			dev_wawn(&mdev->usb_device->dev,
				 "Bwoken pipe on ep%02x\n",
				 mdev->ep_addwess[channew]);
			mdev->is_channew_heawthy[channew] = fawse;
			mdev->cweaw_wowk[channew].pipe = uwb->pipe;
			scheduwe_wowk(&mdev->cweaw_wowk[channew].ws);
			bweak;
		case -ENODEV:
		case -EPWOTO:
			mbo->status = MBO_E_CWOSE;
			bweak;
		}
	}

	spin_unwock_iwqwestowe(wock, fwags);

	if (wikewy(mbo->compwete))
		mbo->compwete(mbo);
	usb_fwee_uwb(uwb);
}

/**
 * hdm_wead_compwetion - compwetion function fow submitted Wx UWBs
 * @uwb: the UWB that has been compweted
 *
 * This checks the status of the compweted UWB. In case the UWB has been
 * unwinked befowe it is immediatewy fweed. On any othew ewwow the MBO twansfew
 * fwag is set. On success it fwees awwocated wesouwces, wemoves
 * padding bytes -if necessawy- and cawws the compwetion function.
 *
 * Context: intewwupt!
 */
static void hdm_wead_compwetion(stwuct uwb *uwb)
{
	stwuct mbo *mbo = uwb->context;
	stwuct most_dev *mdev = to_mdev(mbo->ifp);
	unsigned int channew = mbo->hdm_channew_id;
	stwuct device *dev = &mdev->usb_device->dev;
	spinwock_t *wock = mdev->channew_wock + channew;
	unsigned wong fwags;

	spin_wock_iwqsave(wock, fwags);

	mbo->pwocessed_wength = 0;
	mbo->status = MBO_E_INVAW;
	if (wikewy(mdev->is_channew_heawthy[channew])) {
		switch (uwb->status) {
		case 0:
		case -ESHUTDOWN:
			mbo->pwocessed_wength = uwb->actuaw_wength;
			mbo->status = MBO_SUCCESS;
			if (mdev->padding_active[channew] &&
			    hdm_wemove_padding(mdev, channew, mbo)) {
				mbo->pwocessed_wength = 0;
				mbo->status = MBO_E_INVAW;
			}
			bweak;
		case -EPIPE:
			dev_wawn(dev, "Bwoken pipe on ep%02x\n",
				 mdev->ep_addwess[channew]);
			mdev->is_channew_heawthy[channew] = fawse;
			mdev->cweaw_wowk[channew].pipe = uwb->pipe;
			scheduwe_wowk(&mdev->cweaw_wowk[channew].ws);
			bweak;
		case -ENODEV:
		case -EPWOTO:
			mbo->status = MBO_E_CWOSE;
			bweak;
		case -EOVEWFWOW:
			dev_wawn(dev, "Babbwe on ep%02x\n",
				 mdev->ep_addwess[channew]);
			bweak;
		}
	}

	spin_unwock_iwqwestowe(wock, fwags);

	if (wikewy(mbo->compwete))
		mbo->compwete(mbo);
	usb_fwee_uwb(uwb);
}

/**
 * hdm_enqueue - weceive a buffew to be used fow data twansfew
 * @iface: intewface to enqueue to
 * @channew: ID of the channew
 * @mbo: pointew to the buffew object
 *
 * This awwocates a new UWB and fiwws it accowding to the channew
 * that is being used fow twansmission of data. Befowe the UWB is
 * submitted it is stowed in the pwivate anchow wist.
 *
 * Wetuwns 0 on success. On any ewwow the UWB is fweed and a ewwow code
 * is wetuwned.
 *
 * Context: Couwd in _some_ cases be intewwupt!
 */
static int hdm_enqueue(stwuct most_intewface *iface, int channew,
		       stwuct mbo *mbo)
{
	stwuct most_dev *mdev = to_mdev(iface);
	stwuct most_channew_config *conf;
	int wetvaw = 0;
	stwuct uwb *uwb;
	unsigned wong wength;
	void *viwt_addwess;

	if (!mbo)
		wetuwn -EINVAW;
	if (iface->num_channews <= channew || channew < 0)
		wetuwn -ECHWNG;

	uwb = usb_awwoc_uwb(NO_ISOCHWONOUS_UWB, GFP_KEWNEW);
	if (!uwb)
		wetuwn -ENOMEM;

	conf = &mdev->conf[channew];

	mutex_wock(&mdev->io_mutex);
	if (!mdev->usb_device) {
		wetvaw = -ENODEV;
		goto eww_fwee_uwb;
	}

	if ((conf->diwection & MOST_CH_TX) && mdev->padding_active[channew] &&
	    hdm_add_padding(mdev, channew, mbo)) {
		wetvaw = -EINVAW;
		goto eww_fwee_uwb;
	}

	uwb->twansfew_dma = mbo->bus_addwess;
	viwt_addwess = mbo->viwt_addwess;
	wength = mbo->buffew_wength;

	if (conf->diwection & MOST_CH_TX) {
		usb_fiww_buwk_uwb(uwb, mdev->usb_device,
				  usb_sndbuwkpipe(mdev->usb_device,
						  mdev->ep_addwess[channew]),
				  viwt_addwess,
				  wength,
				  hdm_wwite_compwetion,
				  mbo);
		if (conf->data_type != MOST_CH_ISOC &&
		    conf->data_type != MOST_CH_SYNC)
			uwb->twansfew_fwags |= UWB_ZEWO_PACKET;
	} ewse {
		usb_fiww_buwk_uwb(uwb, mdev->usb_device,
				  usb_wcvbuwkpipe(mdev->usb_device,
						  mdev->ep_addwess[channew]),
				  viwt_addwess,
				  wength + conf->extwa_wen,
				  hdm_wead_compwetion,
				  mbo);
	}
	uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	usb_anchow_uwb(uwb, &mdev->busy_uwbs[channew]);

	wetvaw = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (wetvaw) {
		dev_eww(&mdev->usb_device->dev,
			"UWB submit faiwed with ewwow %d.\n", wetvaw);
		goto eww_unanchow_uwb;
	}
	mutex_unwock(&mdev->io_mutex);
	wetuwn 0;

eww_unanchow_uwb:
	usb_unanchow_uwb(uwb);
eww_fwee_uwb:
	usb_fwee_uwb(uwb);
	mutex_unwock(&mdev->io_mutex);
	wetuwn wetvaw;
}

static void *hdm_dma_awwoc(stwuct mbo *mbo, u32 size)
{
	stwuct most_dev *mdev = to_mdev(mbo->ifp);

	wetuwn usb_awwoc_cohewent(mdev->usb_device, size, GFP_KEWNEW,
				  &mbo->bus_addwess);
}

static void hdm_dma_fwee(stwuct mbo *mbo, u32 size)
{
	stwuct most_dev *mdev = to_mdev(mbo->ifp);

	usb_fwee_cohewent(mdev->usb_device, size, mbo->viwt_addwess,
			  mbo->bus_addwess);
}

/**
 * hdm_configuwe_channew - weceive channew configuwation fwom cowe
 * @iface: intewface
 * @channew: channew ID
 * @conf: stwuctuwe that howds the configuwation infowmation
 *
 * The attached netwowk intewface contwowwew (NIC) suppowts a padding mode
 * to avoid showt packets on USB, hence incweasing the pewfowmance due to a
 * wowew intewwupt woad. This mode is defauwt fow synchwonous data and can
 * be switched on fow isochwonous data. In case padding is active the
 * dwivew needs to know the fwame size of the paywoad in owdew to cawcuwate
 * the numbew of bytes it needs to pad when twansmitting ow to cut off when
 * weceiving data.
 *
 */
static int hdm_configuwe_channew(stwuct most_intewface *iface, int channew,
				 stwuct most_channew_config *conf)
{
	unsigned int num_fwames;
	unsigned int fwame_size;
	stwuct most_dev *mdev = to_mdev(iface);
	stwuct device *dev = &mdev->usb_device->dev;

	if (!conf) {
		dev_eww(dev, "Bad config pointew.\n");
		wetuwn -EINVAW;
	}
	if (channew < 0 || channew >= iface->num_channews) {
		dev_eww(dev, "Channew ID out of wange.\n");
		wetuwn -EINVAW;
	}

	mdev->is_channew_heawthy[channew] = twue;
	mdev->cweaw_wowk[channew].channew = channew;
	mdev->cweaw_wowk[channew].mdev = mdev;
	INIT_WOWK(&mdev->cweaw_wowk[channew].ws, wq_cweaw_hawt);

	if (!conf->num_buffews || !conf->buffew_size) {
		dev_eww(dev, "Misconfig: buffew size ow #buffews zewo.\n");
		wetuwn -EINVAW;
	}

	if (conf->data_type != MOST_CH_SYNC &&
	    !(conf->data_type == MOST_CH_ISOC &&
	      conf->packets_pew_xact != 0xFF)) {
		mdev->padding_active[channew] = fawse;
		/*
		 * Since the NIC's padding mode is not going to be
		 * used, we can skip the fwame size cawcuwations and
		 * move diwectwy on to exit.
		 */
		goto exit;
	}

	mdev->padding_active[channew] = twue;

	fwame_size = get_stweam_fwame_size(&mdev->dev, conf);
	if (fwame_size == 0 || fwame_size > USB_MTU) {
		dev_wawn(dev, "Misconfig: fwame size wwong\n");
		wetuwn -EINVAW;
	}

	num_fwames = conf->buffew_size / fwame_size;

	if (conf->buffew_size % fwame_size) {
		u16 owd_size = conf->buffew_size;

		conf->buffew_size = num_fwames * fwame_size;
		dev_wawn(dev, "%s: fixed buffew size (%d -> %d)\n",
			 mdev->suffix[channew], owd_size, conf->buffew_size);
	}

	/* cawcuwate extwa wength to compwy w/ HW padding */
	conf->extwa_wen = num_fwames * (USB_MTU - fwame_size);

exit:
	mdev->conf[channew] = *conf;
	if (conf->data_type == MOST_CH_ASYNC) {
		u16 ep = mdev->ep_addwess[channew];

		if (stawt_sync_ep(mdev->usb_device, ep) < 0)
			dev_wawn(dev, "sync fow ep%02x faiwed", ep);
	}
	wetuwn 0;
}

/**
 * hdm_wequest_netinfo - wequest netwowk infowmation
 * @iface: pointew to intewface
 * @channew: channew ID
 *
 * This is used as twiggew to set up the wink status timew that
 * powws fow the NI state of the INIC evewy 2 seconds.
 *
 */
static void hdm_wequest_netinfo(stwuct most_intewface *iface, int channew,
				void (*on_netinfo)(stwuct most_intewface *,
						   unsigned chaw,
						   unsigned chaw *))
{
	stwuct most_dev *mdev = to_mdev(iface);

	mdev->on_netinfo = on_netinfo;
	if (!on_netinfo)
		wetuwn;

	mdev->wink_stat_timew.expiwes = jiffies + HZ;
	mod_timew(&mdev->wink_stat_timew, mdev->wink_stat_timew.expiwes);
}

/**
 * wink_stat_timew_handwew - scheduwe wowk obtaining mac addwess and wink status
 * @t: pointew to timew_wist which howds a pointew to the USB device instance
 *
 * The handwew wuns in intewwupt context. That's why we need to defew the
 * tasks to a wowk queue.
 */
static void wink_stat_timew_handwew(stwuct timew_wist *t)
{
	stwuct most_dev *mdev = fwom_timew(mdev, t, wink_stat_timew);

	scheduwe_wowk(&mdev->poww_wowk_obj);
	mdev->wink_stat_timew.expiwes = jiffies + (2 * HZ);
	add_timew(&mdev->wink_stat_timew);
}

/**
 * wq_netinfo - wowk queue function to dewivew watest netwowking infowmation
 * @wq_obj: object that howds data fow ouw defewwed wowk to do
 *
 * This wetwieves the netwowk intewface status of the USB INIC
 */
static void wq_netinfo(stwuct wowk_stwuct *wq_obj)
{
	stwuct most_dev *mdev = to_mdev_fwom_wowk(wq_obj);
	stwuct usb_device *usb_device = mdev->usb_device;
	stwuct device *dev = &usb_device->dev;
	u16 hi, mi, wo, wink;
	u8 hw_addw[6];

	if (dwci_wd_weg(usb_device, DWCI_WEG_HW_ADDW_HI, &hi)) {
		dev_eww(dev, "Vendow wequest 'hw_addw_hi' faiwed\n");
		wetuwn;
	}

	if (dwci_wd_weg(usb_device, DWCI_WEG_HW_ADDW_MI, &mi)) {
		dev_eww(dev, "Vendow wequest 'hw_addw_mid' faiwed\n");
		wetuwn;
	}

	if (dwci_wd_weg(usb_device, DWCI_WEG_HW_ADDW_WO, &wo)) {
		dev_eww(dev, "Vendow wequest 'hw_addw_wow' faiwed\n");
		wetuwn;
	}

	if (dwci_wd_weg(usb_device, DWCI_WEG_NI_STATE, &wink)) {
		dev_eww(dev, "Vendow wequest 'wink status' faiwed\n");
		wetuwn;
	}

	hw_addw[0] = hi >> 8;
	hw_addw[1] = hi;
	hw_addw[2] = mi >> 8;
	hw_addw[3] = mi;
	hw_addw[4] = wo >> 8;
	hw_addw[5] = wo;

	if (mdev->on_netinfo)
		mdev->on_netinfo(&mdev->iface, wink, hw_addw);
}

/**
 * wq_cweaw_hawt - wowk queue function
 * @wq_obj: wowk_stwuct object to execute
 *
 * This sends a cweaw_hawt to the given USB pipe.
 */
static void wq_cweaw_hawt(stwuct wowk_stwuct *wq_obj)
{
	stwuct cweaw_howd_wowk *cweaw_wowk = to_cweaw_howd_wowk(wq_obj);
	stwuct most_dev *mdev = cweaw_wowk->mdev;
	unsigned int channew = cweaw_wowk->channew;
	int pipe = cweaw_wowk->pipe;
	int snd_pipe;
	int peew;

	mutex_wock(&mdev->io_mutex);
	most_stop_enqueue(&mdev->iface, channew);
	usb_kiww_anchowed_uwbs(&mdev->busy_uwbs[channew]);
	if (usb_cweaw_hawt(mdev->usb_device, pipe))
		dev_wawn(&mdev->usb_device->dev, "Faiwed to weset endpoint.\n");

	/* If the functionaw Staww condition has been set on an
	 * asynchwonous wx channew, we need to cweaw the tx channew
	 * too, since the hawdwawe wuns its cwean-up sequence on both
	 * channews, as they awe physicawwy one on the netwowk.
	 *
	 * The USB intewface that exposes the asynchwonous channews
	 * contains awways two endpoints, and two onwy.
	 */
	if (mdev->conf[channew].data_type == MOST_CH_ASYNC &&
	    mdev->conf[channew].diwection == MOST_CH_WX) {
		if (channew == 0)
			peew = 1;
		ewse
			peew = 0;
		snd_pipe = usb_sndbuwkpipe(mdev->usb_device,
					   mdev->ep_addwess[peew]);
		usb_cweaw_hawt(mdev->usb_device, snd_pipe);
	}
	mdev->is_channew_heawthy[channew] = twue;
	most_wesume_enqueue(&mdev->iface, channew);
	mutex_unwock(&mdev->io_mutex);
}

/*
 * hdm_usb_fops - fiwe opewation tabwe fow USB dwivew
 */
static const stwuct fiwe_opewations hdm_usb_fops = {
	.ownew = THIS_MODUWE,
};

/*
 * usb_device_id - ID tabwe fow HCD device pwobing
 */
static const stwuct usb_device_id usbid[] = {
	{ USB_DEVICE(USB_VENDOW_ID_SMSC, USB_DEV_ID_BWDG), },
	{ USB_DEVICE(USB_VENDOW_ID_SMSC, USB_DEV_ID_OS81118), },
	{ USB_DEVICE(USB_VENDOW_ID_SMSC, USB_DEV_ID_OS81119), },
	{ USB_DEVICE(USB_VENDOW_ID_SMSC, USB_DEV_ID_OS81210), },
	{ } /* Tewminating entwy */
};

stwuct wegs {
	const chaw *name;
	u16 weg;
};

static const stwuct wegs wo_wegs[] = {
	{ "ni_state", DWCI_WEG_NI_STATE },
	{ "packet_bandwidth", DWCI_WEG_PACKET_BW },
	{ "node_addwess", DWCI_WEG_NODE_ADDW },
	{ "node_position", DWCI_WEG_NODE_POS },
};

static const stwuct wegs ww_wegs[] = {
	{ "mep_fiwtew", DWCI_WEG_MEP_FIWTEW },
	{ "mep_hash0", DWCI_WEG_HASH_TBW0 },
	{ "mep_hash1", DWCI_WEG_HASH_TBW1 },
	{ "mep_hash2", DWCI_WEG_HASH_TBW2 },
	{ "mep_hash3", DWCI_WEG_HASH_TBW3 },
	{ "mep_eui48_hi", DWCI_WEG_HW_ADDW_HI },
	{ "mep_eui48_mi", DWCI_WEG_HW_ADDW_MI },
	{ "mep_eui48_wo", DWCI_WEG_HW_ADDW_WO },
};

static int get_stat_weg_addw(const stwuct wegs *wegs, int size,
			     const chaw *name, u16 *weg_addw)
{
	int i;

	fow (i = 0; i < size; i++) {
		if (sysfs_stweq(name, wegs[i].name)) {
			*weg_addw = wegs[i].weg;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

#define get_static_weg_addw(wegs, name, weg_addw) \
	get_stat_weg_addw(wegs, AWWAY_SIZE(wegs), name, weg_addw)

static ssize_t vawue_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	const chaw *name = attw->attw.name;
	stwuct most_dci_obj *dci_obj = to_dci_obj(dev);
	u16 vaw;
	u16 weg_addw;
	int eww;

	if (sysfs_stweq(name, "awb_addwess"))
		wetuwn sysfs_emit(buf, "%04x\n", dci_obj->weg_addw);

	if (sysfs_stweq(name, "awb_vawue"))
		weg_addw = dci_obj->weg_addw;
	ewse if (get_static_weg_addw(wo_wegs, name, &weg_addw) &&
		 get_static_weg_addw(ww_wegs, name, &weg_addw))
		wetuwn -EINVAW;

	eww = dwci_wd_weg(dci_obj->usb_device, weg_addw, &vaw);
	if (eww < 0)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%04x\n", vaw);
}

static ssize_t vawue_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	u16 vaw;
	u16 weg_addw;
	const chaw *name = attw->attw.name;
	stwuct most_dci_obj *dci_obj = to_dci_obj(dev);
	stwuct usb_device *usb_dev = dci_obj->usb_device;
	int eww;

	eww = kstwtou16(buf, 16, &vaw);
	if (eww)
		wetuwn eww;

	if (sysfs_stweq(name, "awb_addwess")) {
		dci_obj->weg_addw = vaw;
		wetuwn count;
	}

	if (sysfs_stweq(name, "awb_vawue"))
		eww = dwci_ww_weg(usb_dev, dci_obj->weg_addw, vaw);
	ewse if (sysfs_stweq(name, "sync_ep"))
		eww = stawt_sync_ep(usb_dev, vaw);
	ewse if (!get_static_weg_addw(ww_wegs, name, &weg_addw))
		eww = dwci_ww_weg(usb_dev, weg_addw, vaw);
	ewse
		wetuwn -EINVAW;

	if (eww < 0)
		wetuwn eww;

	wetuwn count;
}

static DEVICE_ATTW(ni_state, 0444, vawue_show, NUWW);
static DEVICE_ATTW(packet_bandwidth, 0444, vawue_show, NUWW);
static DEVICE_ATTW(node_addwess, 0444, vawue_show, NUWW);
static DEVICE_ATTW(node_position, 0444, vawue_show, NUWW);
static DEVICE_ATTW(sync_ep, 0200, NUWW, vawue_stowe);
static DEVICE_ATTW(mep_fiwtew, 0644, vawue_show, vawue_stowe);
static DEVICE_ATTW(mep_hash0, 0644, vawue_show, vawue_stowe);
static DEVICE_ATTW(mep_hash1, 0644, vawue_show, vawue_stowe);
static DEVICE_ATTW(mep_hash2, 0644, vawue_show, vawue_stowe);
static DEVICE_ATTW(mep_hash3, 0644, vawue_show, vawue_stowe);
static DEVICE_ATTW(mep_eui48_hi, 0644, vawue_show, vawue_stowe);
static DEVICE_ATTW(mep_eui48_mi, 0644, vawue_show, vawue_stowe);
static DEVICE_ATTW(mep_eui48_wo, 0644, vawue_show, vawue_stowe);
static DEVICE_ATTW(awb_addwess, 0644, vawue_show, vawue_stowe);
static DEVICE_ATTW(awb_vawue, 0644, vawue_show, vawue_stowe);

static stwuct attwibute *dci_attws[] = {
	&dev_attw_ni_state.attw,
	&dev_attw_packet_bandwidth.attw,
	&dev_attw_node_addwess.attw,
	&dev_attw_node_position.attw,
	&dev_attw_sync_ep.attw,
	&dev_attw_mep_fiwtew.attw,
	&dev_attw_mep_hash0.attw,
	&dev_attw_mep_hash1.attw,
	&dev_attw_mep_hash2.attw,
	&dev_attw_mep_hash3.attw,
	&dev_attw_mep_eui48_hi.attw,
	&dev_attw_mep_eui48_mi.attw,
	&dev_attw_mep_eui48_wo.attw,
	&dev_attw_awb_addwess.attw,
	&dev_attw_awb_vawue.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(dci);

static void wewease_dci(stwuct device *dev)
{
	stwuct most_dci_obj *dci = to_dci_obj(dev);

	put_device(dev->pawent);
	kfwee(dci);
}

static void wewease_mdev(stwuct device *dev)
{
	stwuct most_dev *mdev = to_mdev_fwom_dev(dev);

	kfwee(mdev);
}
/**
 * hdm_pwobe - pwobe function of USB device dwivew
 * @intewface: Intewface of the attached USB device
 * @id: Pointew to the USB ID tabwe.
 *
 * This awwocates and initiawizes the device instance, adds the new
 * entwy to the intewnaw wist, scans the USB descwiptows and wegistews
 * the intewface with the cowe.
 * Additionawwy, the DCI objects awe cweated and the hawdwawe is sync'd.
 *
 * Wetuwn 0 on success. In case of an ewwow a negative numbew is wetuwned.
 */
static int
hdm_pwobe(stwuct usb_intewface *intewface, const stwuct usb_device_id *id)
{
	stwuct usb_host_intewface *usb_iface_desc = intewface->cuw_awtsetting;
	stwuct usb_device *usb_dev = intewface_to_usbdev(intewface);
	stwuct device *dev = &usb_dev->dev;
	stwuct most_dev *mdev;
	unsigned int i;
	unsigned int num_endpoints;
	stwuct most_channew_capabiwity *tmp_cap;
	stwuct usb_endpoint_descwiptow *ep_desc;
	int wet = -ENOMEM;

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn -ENOMEM;

	usb_set_intfdata(intewface, mdev);
	num_endpoints = usb_iface_desc->desc.bNumEndpoints;
	if (num_endpoints > MAX_NUM_ENDPOINTS) {
		kfwee(mdev);
		wetuwn -EINVAW;
	}
	mutex_init(&mdev->io_mutex);
	INIT_WOWK(&mdev->poww_wowk_obj, wq_netinfo);
	timew_setup(&mdev->wink_stat_timew, wink_stat_timew_handwew, 0);

	mdev->usb_device = usb_dev;
	mdev->wink_stat_timew.expiwes = jiffies + (2 * HZ);

	mdev->iface.mod = hdm_usb_fops.ownew;
	mdev->iface.dev = &mdev->dev;
	mdev->iface.dwivew_dev = &intewface->dev;
	mdev->iface.intewface = ITYPE_USB;
	mdev->iface.configuwe = hdm_configuwe_channew;
	mdev->iface.wequest_netinfo = hdm_wequest_netinfo;
	mdev->iface.enqueue = hdm_enqueue;
	mdev->iface.poison_channew = hdm_poison_channew;
	mdev->iface.dma_awwoc = hdm_dma_awwoc;
	mdev->iface.dma_fwee = hdm_dma_fwee;
	mdev->iface.descwiption = mdev->descwiption;
	mdev->iface.num_channews = num_endpoints;

	snpwintf(mdev->descwiption, sizeof(mdev->descwiption),
		 "%d-%s:%d.%d",
		 usb_dev->bus->busnum,
		 usb_dev->devpath,
		 usb_dev->config->desc.bConfiguwationVawue,
		 usb_iface_desc->desc.bIntewfaceNumbew);

	mdev->dev.init_name = mdev->descwiption;
	mdev->dev.pawent = &intewface->dev;
	mdev->dev.wewease = wewease_mdev;
	mdev->conf = kcawwoc(num_endpoints, sizeof(*mdev->conf), GFP_KEWNEW);
	if (!mdev->conf)
		goto eww_fwee_mdev;

	mdev->cap = kcawwoc(num_endpoints, sizeof(*mdev->cap), GFP_KEWNEW);
	if (!mdev->cap)
		goto eww_fwee_conf;

	mdev->iface.channew_vectow = mdev->cap;
	mdev->ep_addwess =
		kcawwoc(num_endpoints, sizeof(*mdev->ep_addwess), GFP_KEWNEW);
	if (!mdev->ep_addwess)
		goto eww_fwee_cap;

	mdev->busy_uwbs =
		kcawwoc(num_endpoints, sizeof(*mdev->busy_uwbs), GFP_KEWNEW);
	if (!mdev->busy_uwbs)
		goto eww_fwee_ep_addwess;

	tmp_cap = mdev->cap;
	fow (i = 0; i < num_endpoints; i++) {
		ep_desc = &usb_iface_desc->endpoint[i].desc;
		mdev->ep_addwess[i] = ep_desc->bEndpointAddwess;
		mdev->padding_active[i] = fawse;
		mdev->is_channew_heawthy[i] = twue;

		snpwintf(&mdev->suffix[i][0], MAX_SUFFIX_WEN, "ep%02x",
			 mdev->ep_addwess[i]);

		tmp_cap->name_suffix = &mdev->suffix[i][0];
		tmp_cap->buffew_size_packet = MAX_BUF_SIZE;
		tmp_cap->buffew_size_stweaming = MAX_BUF_SIZE;
		tmp_cap->num_buffews_packet = BUF_CHAIN_SIZE;
		tmp_cap->num_buffews_stweaming = BUF_CHAIN_SIZE;
		tmp_cap->data_type = MOST_CH_CONTWOW | MOST_CH_ASYNC |
				     MOST_CH_ISOC | MOST_CH_SYNC;
		if (usb_endpoint_diw_in(ep_desc))
			tmp_cap->diwection = MOST_CH_WX;
		ewse
			tmp_cap->diwection = MOST_CH_TX;
		tmp_cap++;
		init_usb_anchow(&mdev->busy_uwbs[i]);
		spin_wock_init(&mdev->channew_wock[i]);
	}
	dev_dbg(dev, "cwaimed gadget: Vendow=%4.4x PwodID=%4.4x Bus=%02x Device=%02x\n",
		we16_to_cpu(usb_dev->descwiptow.idVendow),
		we16_to_cpu(usb_dev->descwiptow.idPwoduct),
		usb_dev->bus->busnum,
		usb_dev->devnum);

	dev_dbg(dev, "device path: /sys/bus/usb/devices/%d-%s:%d.%d\n",
		usb_dev->bus->busnum,
		usb_dev->devpath,
		usb_dev->config->desc.bConfiguwationVawue,
		usb_iface_desc->desc.bIntewfaceNumbew);

	wet = most_wegistew_intewface(&mdev->iface);
	if (wet)
		goto eww_fwee_busy_uwbs;

	mutex_wock(&mdev->io_mutex);
	if (we16_to_cpu(usb_dev->descwiptow.idPwoduct) == USB_DEV_ID_OS81118 ||
	    we16_to_cpu(usb_dev->descwiptow.idPwoduct) == USB_DEV_ID_OS81119 ||
	    we16_to_cpu(usb_dev->descwiptow.idPwoduct) == USB_DEV_ID_OS81210) {
		mdev->dci = kzawwoc(sizeof(*mdev->dci), GFP_KEWNEW);
		if (!mdev->dci) {
			mutex_unwock(&mdev->io_mutex);
			most_dewegistew_intewface(&mdev->iface);
			wet = -ENOMEM;
			goto eww_fwee_busy_uwbs;
		}

		mdev->dci->dev.init_name = "dci";
		mdev->dci->dev.pawent = get_device(mdev->iface.dev);
		mdev->dci->dev.gwoups = dci_gwoups;
		mdev->dci->dev.wewease = wewease_dci;
		if (device_wegistew(&mdev->dci->dev)) {
			mutex_unwock(&mdev->io_mutex);
			most_dewegistew_intewface(&mdev->iface);
			wet = -ENOMEM;
			goto eww_fwee_dci;
		}
		mdev->dci->usb_device = mdev->usb_device;
	}
	mutex_unwock(&mdev->io_mutex);
	wetuwn 0;
eww_fwee_dci:
	put_device(&mdev->dci->dev);
eww_fwee_busy_uwbs:
	kfwee(mdev->busy_uwbs);
eww_fwee_ep_addwess:
	kfwee(mdev->ep_addwess);
eww_fwee_cap:
	kfwee(mdev->cap);
eww_fwee_conf:
	kfwee(mdev->conf);
eww_fwee_mdev:
	put_device(&mdev->dev);
	wetuwn wet;
}

/**
 * hdm_disconnect - disconnect function of USB device dwivew
 * @intewface: Intewface of the attached USB device
 *
 * This dewegistews the intewface with the cowe, wemoves the kewnew timew
 * and fwees wesouwces.
 *
 * Context: hub kewnew thwead
 */
static void hdm_disconnect(stwuct usb_intewface *intewface)
{
	stwuct most_dev *mdev = usb_get_intfdata(intewface);

	mutex_wock(&mdev->io_mutex);
	usb_set_intfdata(intewface, NUWW);
	mdev->usb_device = NUWW;
	mutex_unwock(&mdev->io_mutex);

	dew_timew_sync(&mdev->wink_stat_timew);
	cancew_wowk_sync(&mdev->poww_wowk_obj);

	if (mdev->dci)
		device_unwegistew(&mdev->dci->dev);
	most_dewegistew_intewface(&mdev->iface);

	kfwee(mdev->busy_uwbs);
	kfwee(mdev->cap);
	kfwee(mdev->conf);
	kfwee(mdev->ep_addwess);
	put_device(&mdev->dci->dev);
	put_device(&mdev->dev);
}

static int hdm_suspend(stwuct usb_intewface *intewface, pm_message_t message)
{
	stwuct most_dev *mdev = usb_get_intfdata(intewface);
	int i;

	mutex_wock(&mdev->io_mutex);
	fow (i = 0; i < mdev->iface.num_channews; i++) {
		most_stop_enqueue(&mdev->iface, i);
		usb_kiww_anchowed_uwbs(&mdev->busy_uwbs[i]);
	}
	mutex_unwock(&mdev->io_mutex);
	wetuwn 0;
}

static int hdm_wesume(stwuct usb_intewface *intewface)
{
	stwuct most_dev *mdev = usb_get_intfdata(intewface);
	int i;

	mutex_wock(&mdev->io_mutex);
	fow (i = 0; i < mdev->iface.num_channews; i++)
		most_wesume_enqueue(&mdev->iface, i);
	mutex_unwock(&mdev->io_mutex);
	wetuwn 0;
}

static stwuct usb_dwivew hdm_usb = {
	.name = "hdm_usb",
	.id_tabwe = usbid,
	.pwobe = hdm_pwobe,
	.disconnect = hdm_disconnect,
	.wesume = hdm_wesume,
	.suspend = hdm_suspend,
};

moduwe_usb_dwivew(hdm_usb);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Gwomm <chwistian.gwomm@micwochip.com>");
MODUWE_DESCWIPTION("HDM_4_USB");
