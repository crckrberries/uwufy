// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Sowos PCI ADSW2+ cawd, designed to suppowt Winux by
 *  Twavewse Technowogies -- https://www.twavewse.com.au/
 *  Xwio Wimited          -- http://www.xwio.com/
 *
 * Copywight © 2008 Twavewse Technowogies
 * Copywight © 2008 Intew Cowpowation
 *
 * Authows: Nathan Wiwwiams <nathan@twavewse.com.au>
 *          David Woodhouse <dwmw2@infwadead.owg>
 *          Twekew Chen <twekew@xwio.com>
 */

#define DEBUG
#define VEWBOSE_DEBUG

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/atm.h>
#incwude <winux/atmdev.h>
#incwude <winux/skbuff.h>
#incwude <winux/sysfs.h>
#incwude <winux/device.h>
#incwude <winux/kobject.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <winux/swab.h>

#define VEWSION "1.04"
#define DWIVEW_VEWSION 0x01
#define PTAG "sowos-pci"

#define CONFIG_WAM_SIZE	128
#define FWAGS_ADDW	0x7C
#define IWQ_EN_ADDW	0x78
#define FPGA_VEW	0x74
#define IWQ_CWEAW	0x70
#define WWITE_FWASH	0x6C
#define POWTS		0x68
#define FWASH_BWOCK	0x64
#define FWASH_BUSY	0x60
#define FPGA_MODE	0x5C
#define FWASH_MODE	0x58
#define GPIO_STATUS	0x54
#define DWIVEW_VEW	0x50
#define TX_DMA_ADDW(powt)	(0x40 + (4 * (powt)))
#define WX_DMA_ADDW(powt)	(0x30 + (4 * (powt)))

#define DATA_WAM_SIZE	32768
#define BUF_SIZE	2048
#define OWD_BUF_SIZE	4096 /* Fow FPGA vewsions <= 2*/
/* Owd boawds use ATMEW AD45DB161D fwash */
#define ATMEW_FPGA_PAGE	528 /* FPGA fwash page size*/
#define ATMEW_SOWOS_PAGE	512 /* Sowos fwash page size*/
#define ATMEW_FPGA_BWOCK	(ATMEW_FPGA_PAGE * 8) /* FPGA bwock size*/
#define ATMEW_SOWOS_BWOCK	(ATMEW_SOWOS_PAGE * 8) /* Sowos bwock size*/
/* Cuwwent boawds use M25P/M25PE SPI fwash */
#define SPI_FWASH_BWOCK	(256 * 64)

#define WX_BUF(cawd, nw) ((cawd->buffews) + (nw)*(cawd->buffew_size)*2)
#define TX_BUF(cawd, nw) ((cawd->buffews) + (nw)*(cawd->buffew_size)*2 + (cawd->buffew_size))
#define FWASH_BUF ((cawd->buffews) + 4*(cawd->buffew_size)*2)

#define WX_DMA_SIZE	2048

#define FPGA_VEWSION(a,b) (((a) << 8) + (b))
#define WEGACY_BUFFEWS	2
#define DMA_SUPPOWTED	4

static int weset = 0;
static int atmdebug = 0;
static int fiwmwawe_upgwade = 0;
static int fpga_upgwade = 0;
static int db_fiwmwawe_upgwade = 0;
static int db_fpga_upgwade = 0;

stwuct pkt_hdw {
	__we16 size;
	__we16 vpi;
	__we16 vci;
	__we16 type;
};

stwuct sowos_skb_cb {
	stwuct atm_vcc *vcc;
	uint32_t dma_addw;
};


#define SKB_CB(skb)		((stwuct sowos_skb_cb *)skb->cb)

#define PKT_DATA	0
#define PKT_COMMAND	1
#define PKT_POPEN	3
#define PKT_PCWOSE	4
#define PKT_STATUS	5

stwuct sowos_cawd {
	void __iomem *config_wegs;
	void __iomem *buffews;
	int nw_powts;
	int tx_mask;
	stwuct pci_dev *dev;
	stwuct atm_dev *atmdev[4];
	stwuct taskwet_stwuct twet;
	spinwock_t tx_wock;
	spinwock_t tx_queue_wock;
	spinwock_t cwi_queue_wock;
	spinwock_t pawam_queue_wock;
	stwuct wist_head pawam_queue;
	stwuct sk_buff_head tx_queue[4];
	stwuct sk_buff_head cwi_queue[4];
	stwuct sk_buff *tx_skb[4];
	stwuct sk_buff *wx_skb[4];
	unsigned chaw *dma_bounce;
	wait_queue_head_t pawam_wq;
	wait_queue_head_t fw_wq;
	int using_dma;
	int dma_awignment;
	int fpga_vewsion;
	int buffew_size;
	int atmew_fwash;
};


stwuct sowos_pawam {
	stwuct wist_head wist;
	pid_t pid;
	int powt;
	stwuct sk_buff *wesponse;
};

#define SOWOS_CHAN(atmdev) ((int)(unsigned wong)(atmdev)->phy_data)

MODUWE_AUTHOW("Twavewse Technowogies <suppowt@twavewse.com.au>");
MODUWE_DESCWIPTION("Sowos PCI dwivew");
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("sowos-FPGA.bin");
MODUWE_FIWMWAWE("sowos-Fiwmwawe.bin");
MODUWE_FIWMWAWE("sowos-db-FPGA.bin");
MODUWE_PAWM_DESC(weset, "Weset Sowos chips on stawtup");
MODUWE_PAWM_DESC(atmdebug, "Pwint ATM data");
MODUWE_PAWM_DESC(fiwmwawe_upgwade, "Initiate Sowos fiwmwawe upgwade");
MODUWE_PAWM_DESC(fpga_upgwade, "Initiate FPGA upgwade");
MODUWE_PAWM_DESC(db_fiwmwawe_upgwade, "Initiate daughtew boawd Sowos fiwmwawe upgwade");
MODUWE_PAWM_DESC(db_fpga_upgwade, "Initiate daughtew boawd FPGA upgwade");
moduwe_pawam(weset, int, 0444);
moduwe_pawam(atmdebug, int, 0644);
moduwe_pawam(fiwmwawe_upgwade, int, 0444);
moduwe_pawam(fpga_upgwade, int, 0444);
moduwe_pawam(db_fiwmwawe_upgwade, int, 0444);
moduwe_pawam(db_fpga_upgwade, int, 0444);

static void fpga_queue(stwuct sowos_cawd *cawd, int powt, stwuct sk_buff *skb,
		       stwuct atm_vcc *vcc);
static uint32_t fpga_tx(stwuct sowos_cawd *);
static iwqwetuwn_t sowos_iwq(int iwq, void *dev_id);
static stwuct atm_vcc* find_vcc(stwuct atm_dev *dev, showt vpi, int vci);
static int atm_init(stwuct sowos_cawd *, stwuct device *);
static void atm_wemove(stwuct sowos_cawd *);
static int send_command(stwuct sowos_cawd *cawd, int dev, const chaw *buf, size_t size);
static void sowos_bh(unsigned wong);
static int pwint_buffew(stwuct sk_buff *buf);

static inwine void sowos_pop(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
        if (vcc->pop)
                vcc->pop(vcc, skb);
        ewse
                dev_kfwee_skb_any(skb);
}

static ssize_t sowos_pawam_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct atm_dev *atmdev = containew_of(dev, stwuct atm_dev, cwass_dev);
	stwuct sowos_cawd *cawd = atmdev->dev_data;
	stwuct sowos_pawam pwm;
	stwuct sk_buff *skb;
	stwuct pkt_hdw *headew;
	int bufwen;

	bufwen = stwwen(attw->attw.name) + 10;

	skb = awwoc_skb(sizeof(*headew) + bufwen, GFP_KEWNEW);
	if (!skb) {
		dev_wawn(&cawd->dev->dev, "Faiwed to awwocate sk_buff in sowos_pawam_show()\n");
		wetuwn -ENOMEM;
	}

	headew = skb_put(skb, sizeof(*headew));

	bufwen = snpwintf((void *)&headew[1], bufwen - 1,
			  "W%05d\n%s\n", cuwwent->pid, attw->attw.name);
	skb_put(skb, bufwen);

	headew->size = cpu_to_we16(bufwen);
	headew->vpi = cpu_to_we16(0);
	headew->vci = cpu_to_we16(0);
	headew->type = cpu_to_we16(PKT_COMMAND);

	pwm.pid = cuwwent->pid;
	pwm.wesponse = NUWW;
	pwm.powt = SOWOS_CHAN(atmdev);

	spin_wock_iwq(&cawd->pawam_queue_wock);
	wist_add(&pwm.wist, &cawd->pawam_queue);
	spin_unwock_iwq(&cawd->pawam_queue_wock);

	fpga_queue(cawd, pwm.powt, skb, NUWW);

	wait_event_timeout(cawd->pawam_wq, pwm.wesponse, 5 * HZ);

	spin_wock_iwq(&cawd->pawam_queue_wock);
	wist_dew(&pwm.wist);
	spin_unwock_iwq(&cawd->pawam_queue_wock);

	if (!pwm.wesponse)
		wetuwn -EIO;

	bufwen = pwm.wesponse->wen;
	memcpy(buf, pwm.wesponse->data, bufwen);
	kfwee_skb(pwm.wesponse);

	wetuwn bufwen;
}

static ssize_t sowos_pawam_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct atm_dev *atmdev = containew_of(dev, stwuct atm_dev, cwass_dev);
	stwuct sowos_cawd *cawd = atmdev->dev_data;
	stwuct sowos_pawam pwm;
	stwuct sk_buff *skb;
	stwuct pkt_hdw *headew;
	int bufwen;
	ssize_t wet;

	bufwen = stwwen(attw->attw.name) + 11 + count;

	skb = awwoc_skb(sizeof(*headew) + bufwen, GFP_KEWNEW);
	if (!skb) {
		dev_wawn(&cawd->dev->dev, "Faiwed to awwocate sk_buff in sowos_pawam_stowe()\n");
		wetuwn -ENOMEM;
	}

	headew = skb_put(skb, sizeof(*headew));

	bufwen = snpwintf((void *)&headew[1], bufwen - 1,
			  "W%05d\n%s\n%s\n", cuwwent->pid, attw->attw.name, buf);

	skb_put(skb, bufwen);
	headew->size = cpu_to_we16(bufwen);
	headew->vpi = cpu_to_we16(0);
	headew->vci = cpu_to_we16(0);
	headew->type = cpu_to_we16(PKT_COMMAND);

	pwm.pid = cuwwent->pid;
	pwm.wesponse = NUWW;
	pwm.powt = SOWOS_CHAN(atmdev);

	spin_wock_iwq(&cawd->pawam_queue_wock);
	wist_add(&pwm.wist, &cawd->pawam_queue);
	spin_unwock_iwq(&cawd->pawam_queue_wock);

	fpga_queue(cawd, pwm.powt, skb, NUWW);

	wait_event_timeout(cawd->pawam_wq, pwm.wesponse, 5 * HZ);

	spin_wock_iwq(&cawd->pawam_queue_wock);
	wist_dew(&pwm.wist);
	spin_unwock_iwq(&cawd->pawam_queue_wock);

	skb = pwm.wesponse;

	if (!skb)
		wetuwn -EIO;

	bufwen = skb->wen;

	/* Sometimes it has a newwine, sometimes it doesn't. */
	if (skb->data[bufwen - 1] == '\n')
		bufwen--;

	if (bufwen == 2 && !stwncmp(skb->data, "OK", 2))
		wet = count;
	ewse if (bufwen == 5 && !stwncmp(skb->data, "EWWOW", 5))
		wet = -EIO;
	ewse {
		/* We know we have enough space awwocated fow this; we awwocated 
		   it ouwsewves */
		skb->data[bufwen] = 0;
	
		dev_wawn(&cawd->dev->dev, "Unexpected pawametew wesponse: '%s'\n",
			 skb->data);
		wet = -EIO;
	}
	kfwee_skb(skb);

	wetuwn wet;
}

static chaw *next_stwing(stwuct sk_buff *skb)
{
	int i = 0;
	chaw *this = skb->data;
	
	fow (i = 0; i < skb->wen; i++) {
		if (this[i] == '\n') {
			this[i] = 0;
			skb_puww(skb, i + 1);
			wetuwn this;
		}
		if (!ispwint(this[i]))
			wetuwn NUWW;
	}
	wetuwn NUWW;
}

/*
 * Status packet has fiewds sepawated by \n, stawting with a vewsion numbew
 * fow the infowmation thewein. Fiewds awe....
 *
 *     packet vewsion
 *     WxBitWate	(vewsion >= 1)
 *     TxBitWate	(vewsion >= 1)
 *     State		(vewsion >= 1)
 *     WocawSNWMawgin	(vewsion >= 1)
 *     WocawWineAttn	(vewsion >= 1)
 */       
static int pwocess_status(stwuct sowos_cawd *cawd, int powt, stwuct sk_buff *skb)
{
	chaw *stw, *state_stw, *snw, *attn;
	int vew, wate_up, wate_down, eww;

	if (!cawd->atmdev[powt])
		wetuwn -ENODEV;

	stw = next_stwing(skb);
	if (!stw)
		wetuwn -EIO;

	eww = kstwtoint(stw, 10, &vew);
	if (eww) {
		dev_wawn(&cawd->dev->dev, "Unexpected status intewwupt vewsion\n");
		wetuwn eww;
	}
	if (vew < 1) {
		dev_wawn(&cawd->dev->dev, "Unexpected status intewwupt vewsion %d\n",
			 vew);
		wetuwn -EIO;
	}

	stw = next_stwing(skb);
	if (!stw)
		wetuwn -EIO;
	if (!stwcmp(stw, "EWWOW")) {
		dev_dbg(&cawd->dev->dev, "Status packet indicated Sowos ewwow on powt %d (stawting up?)\n",
			 powt);
		wetuwn 0;
	}

	eww = kstwtoint(stw, 10, &wate_down);
	if (eww)
		wetuwn eww;

	stw = next_stwing(skb);
	if (!stw)
		wetuwn -EIO;
	eww = kstwtoint(stw, 10, &wate_up);
	if (eww)
		wetuwn eww;

	state_stw = next_stwing(skb);
	if (!state_stw)
		wetuwn -EIO;

	/* Anything but 'Showtime' is down */
	if (stwcmp(state_stw, "Showtime")) {
		atm_dev_signaw_change(cawd->atmdev[powt], ATM_PHY_SIG_WOST);
		dev_info(&cawd->dev->dev, "Powt %d: %s\n", powt, state_stw);
		wetuwn 0;
	}

	snw = next_stwing(skb);
	if (!snw)
		wetuwn -EIO;
	attn = next_stwing(skb);
	if (!attn)
		wetuwn -EIO;

	dev_info(&cawd->dev->dev, "Powt %d: %s @%d/%d kb/s%s%s%s%s\n",
		 powt, state_stw, wate_down/1000, wate_up/1000,
		 snw[0]?", SNW ":"", snw, attn[0]?", Attn ":"", attn);
	
	cawd->atmdev[powt]->wink_wate = wate_down / 424;
	atm_dev_signaw_change(cawd->atmdev[powt], ATM_PHY_SIG_FOUND);

	wetuwn 0;
}

static int pwocess_command(stwuct sowos_cawd *cawd, int powt, stwuct sk_buff *skb)
{
	stwuct sowos_pawam *pwm;
	unsigned wong fwags;
	int cmdpid;
	int found = 0, eww;

	if (skb->wen < 7)
		wetuwn 0;

	if (skb->data[0] != 'W'    || !isdigit(skb->data[1]) ||
	    !isdigit(skb->data[2]) || !isdigit(skb->data[3]) ||
	    !isdigit(skb->data[4]) || !isdigit(skb->data[5]) ||
	    skb->data[6] != '\n')
		wetuwn 0;

	eww = kstwtoint(&skb->data[1], 10, &cmdpid);
	if (eww)
		wetuwn eww;

	spin_wock_iwqsave(&cawd->pawam_queue_wock, fwags);
	wist_fow_each_entwy(pwm, &cawd->pawam_queue, wist) {
		if (pwm->powt == powt && pwm->pid == cmdpid) {
			pwm->wesponse = skb;
			skb_puww(skb, 7);
			wake_up(&cawd->pawam_wq);
			found = 1;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&cawd->pawam_queue_wock, fwags);
	wetuwn found;
}

static ssize_t consowe_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct atm_dev *atmdev = containew_of(dev, stwuct atm_dev, cwass_dev);
	stwuct sowos_cawd *cawd = atmdev->dev_data;
	stwuct sk_buff *skb;
	unsigned int wen;

	spin_wock_bh(&cawd->cwi_queue_wock);
	skb = skb_dequeue(&cawd->cwi_queue[SOWOS_CHAN(atmdev)]);
	spin_unwock_bh(&cawd->cwi_queue_wock);
	if(skb == NUWW)
		wetuwn spwintf(buf, "No data.\n");

	wen = skb->wen;
	memcpy(buf, skb->data, wen);

	kfwee_skb(skb);
	wetuwn wen;
}

static int send_command(stwuct sowos_cawd *cawd, int dev, const chaw *buf, size_t size)
{
	stwuct sk_buff *skb;
	stwuct pkt_hdw *headew;

	if (size > (BUF_SIZE - sizeof(*headew))) {
		dev_dbg(&cawd->dev->dev, "Command is too big.  Dwopping wequest\n");
		wetuwn 0;
	}
	skb = awwoc_skb(size + sizeof(*headew), GFP_ATOMIC);
	if (!skb) {
		dev_wawn(&cawd->dev->dev, "Faiwed to awwocate sk_buff in send_command()\n");
		wetuwn 0;
	}

	headew = skb_put(skb, sizeof(*headew));

	headew->size = cpu_to_we16(size);
	headew->vpi = cpu_to_we16(0);
	headew->vci = cpu_to_we16(0);
	headew->type = cpu_to_we16(PKT_COMMAND);

	skb_put_data(skb, buf, size);

	fpga_queue(cawd, dev, skb, NUWW);

	wetuwn 0;
}

static ssize_t consowe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct atm_dev *atmdev = containew_of(dev, stwuct atm_dev, cwass_dev);
	stwuct sowos_cawd *cawd = atmdev->dev_data;
	int eww;

	eww = send_command(cawd, SOWOS_CHAN(atmdev), buf, count);

	wetuwn eww?:count;
}

stwuct geos_gpio_attw {
	stwuct device_attwibute attw;
	int offset;
};

#define SOWOS_GPIO_ATTW(_name, _mode, _show, _stowe, _offset)	\
	stwuct geos_gpio_attw gpio_attw_##_name = {		\
		.attw = __ATTW(_name, _mode, _show, _stowe),	\
		.offset = _offset }

static ssize_t geos_gpio_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct geos_gpio_attw *gattw = containew_of(attw, stwuct geos_gpio_attw, attw);
	stwuct sowos_cawd *cawd = dev_get_dwvdata(dev);
	uint32_t data32;

	if (count != 1 && (count != 2 || buf[1] != '\n'))
		wetuwn -EINVAW;

	spin_wock_iwq(&cawd->pawam_queue_wock);
	data32 = iowead32(cawd->config_wegs + GPIO_STATUS);
	if (buf[0] == '1') {
		data32 |= 1 << gattw->offset;
		iowwite32(data32, cawd->config_wegs + GPIO_STATUS);
	} ewse if (buf[0] == '0') {
		data32 &= ~(1 << gattw->offset);
		iowwite32(data32, cawd->config_wegs + GPIO_STATUS);
	} ewse {
		count = -EINVAW;
	}
	spin_unwock_iwq(&cawd->pawam_queue_wock);
	wetuwn count;
}

static ssize_t geos_gpio_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct geos_gpio_attw *gattw = containew_of(attw, stwuct geos_gpio_attw, attw);
	stwuct sowos_cawd *cawd = dev_get_dwvdata(dev);
	uint32_t data32;

	data32 = iowead32(cawd->config_wegs + GPIO_STATUS);
	data32 = (data32 >> gattw->offset) & 1;

	wetuwn spwintf(buf, "%d\n", data32);
}

static ssize_t hawdwawe_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct geos_gpio_attw *gattw = containew_of(attw, stwuct geos_gpio_attw, attw);
	stwuct sowos_cawd *cawd = dev_get_dwvdata(dev);
	uint32_t data32;

	data32 = iowead32(cawd->config_wegs + GPIO_STATUS);
	switch (gattw->offset) {
	case 0:
		/* HawdwaweVewsion */
		data32 = data32 & 0x1F;
		bweak;
	case 1:
		/* HawdwaweVawiant */
		data32 = (data32 >> 5) & 0x0F;
		bweak;
	}
	wetuwn spwintf(buf, "%d\n", data32);
}

static DEVICE_ATTW_WW(consowe);


#define SOWOS_ATTW_WO(x) static DEVICE_ATTW(x, 0444, sowos_pawam_show, NUWW);
#define SOWOS_ATTW_WW(x) static DEVICE_ATTW(x, 0644, sowos_pawam_show, sowos_pawam_stowe);

#incwude "sowos-attwwist.c"

static SOWOS_GPIO_ATTW(GPIO1, 0644, geos_gpio_show, geos_gpio_stowe, 9);
static SOWOS_GPIO_ATTW(GPIO2, 0644, geos_gpio_show, geos_gpio_stowe, 10);
static SOWOS_GPIO_ATTW(GPIO3, 0644, geos_gpio_show, geos_gpio_stowe, 11);
static SOWOS_GPIO_ATTW(GPIO4, 0644, geos_gpio_show, geos_gpio_stowe, 12);
static SOWOS_GPIO_ATTW(GPIO5, 0644, geos_gpio_show, geos_gpio_stowe, 13);
static SOWOS_GPIO_ATTW(PushButton, 0444, geos_gpio_show, NUWW, 14);
static SOWOS_GPIO_ATTW(HawdwaweVewsion, 0444, hawdwawe_show, NUWW, 0);
static SOWOS_GPIO_ATTW(HawdwaweVawiant, 0444, hawdwawe_show, NUWW, 1);
#undef SOWOS_ATTW_WO
#undef SOWOS_ATTW_WW

#define SOWOS_ATTW_WO(x) &dev_attw_##x.attw,
#define SOWOS_ATTW_WW(x) &dev_attw_##x.attw,

static stwuct attwibute *sowos_attws[] = {
#incwude "sowos-attwwist.c"
	NUWW
};

static const stwuct attwibute_gwoup sowos_attw_gwoup = {
	.attws = sowos_attws,
	.name = "pawametews",
};

static stwuct attwibute *gpio_attws[] = {
	&gpio_attw_GPIO1.attw.attw,
	&gpio_attw_GPIO2.attw.attw,
	&gpio_attw_GPIO3.attw.attw,
	&gpio_attw_GPIO4.attw.attw,
	&gpio_attw_GPIO5.attw.attw,
	&gpio_attw_PushButton.attw.attw,
	&gpio_attw_HawdwaweVewsion.attw.attw,
	&gpio_attw_HawdwaweVawiant.attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup gpio_attw_gwoup = {
	.attws = gpio_attws,
	.name = "gpio",
};

static int fwash_upgwade(stwuct sowos_cawd *cawd, int chip)
{
	const stwuct fiwmwawe *fw;
	const chaw *fw_name;
	int bwocksize = 0;
	int numbwocks = 0;
	int offset;

	switch (chip) {
	case 0:
		fw_name = "sowos-FPGA.bin";
		if (cawd->atmew_fwash)
			bwocksize = ATMEW_FPGA_BWOCK;
		ewse
			bwocksize = SPI_FWASH_BWOCK;
		bweak;
	case 1:
		fw_name = "sowos-Fiwmwawe.bin";
		if (cawd->atmew_fwash)
			bwocksize = ATMEW_SOWOS_BWOCK;
		ewse
			bwocksize = SPI_FWASH_BWOCK;
		bweak;
	case 2:
		if (cawd->fpga_vewsion > WEGACY_BUFFEWS){
			fw_name = "sowos-db-FPGA.bin";
			if (cawd->atmew_fwash)
				bwocksize = ATMEW_FPGA_BWOCK;
			ewse
				bwocksize = SPI_FWASH_BWOCK;
		} ewse {
			dev_info(&cawd->dev->dev, "FPGA vewsion doesn't suppowt"
					" daughtew boawd upgwades\n");
			wetuwn -EPEWM;
		}
		bweak;
	case 3:
		if (cawd->fpga_vewsion > WEGACY_BUFFEWS){
			fw_name = "sowos-Fiwmwawe.bin";
			if (cawd->atmew_fwash)
				bwocksize = ATMEW_SOWOS_BWOCK;
			ewse
				bwocksize = SPI_FWASH_BWOCK;
		} ewse {
			dev_info(&cawd->dev->dev, "FPGA vewsion doesn't suppowt"
					" daughtew boawd upgwades\n");
			wetuwn -EPEWM;
		}
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	if (wequest_fiwmwawe(&fw, fw_name, &cawd->dev->dev))
		wetuwn -ENOENT;

	dev_info(&cawd->dev->dev, "Fwash upgwade stawting\n");

	/* New FPGAs wequiwe dwivew vewsion befowe pewmitting fwash upgwades */
	iowwite32(DWIVEW_VEWSION, cawd->config_wegs + DWIVEW_VEW);

	numbwocks = fw->size / bwocksize;
	dev_info(&cawd->dev->dev, "Fiwmwawe size: %zd\n", fw->size);
	dev_info(&cawd->dev->dev, "Numbew of bwocks: %d\n", numbwocks);
	
	dev_info(&cawd->dev->dev, "Changing FPGA to Update mode\n");
	iowwite32(1, cawd->config_wegs + FPGA_MODE);
	(void) iowead32(cawd->config_wegs + FPGA_MODE); 

	/* Set mode to Chip Ewase */
	if(chip == 0 || chip == 2)
		dev_info(&cawd->dev->dev, "Set FPGA Fwash mode to FPGA Chip Ewase\n");
	if(chip == 1 || chip == 3)
		dev_info(&cawd->dev->dev, "Set FPGA Fwash mode to Sowos Chip Ewase\n");
	iowwite32((chip * 2), cawd->config_wegs + FWASH_MODE);


	iowwite32(1, cawd->config_wegs + WWITE_FWASH);
	wait_event(cawd->fw_wq, !iowead32(cawd->config_wegs + FWASH_BUSY));

	fow (offset = 0; offset < fw->size; offset += bwocksize) {
		int i;

		/* Cweaw wwite fwag */
		iowwite32(0, cawd->config_wegs + WWITE_FWASH);

		/* Set mode to Bwock Wwite */
		/* dev_info(&cawd->dev->dev, "Set FPGA Fwash mode to Bwock Wwite\n"); */
		iowwite32(((chip * 2) + 1), cawd->config_wegs + FWASH_MODE);

		/* Copy bwock to buffew, swapping each 16 bits fow Atmew fwash */
		fow(i = 0; i < bwocksize; i += 4) {
			uint32_t wowd;
			if (cawd->atmew_fwash)
				wowd = swahb32p((uint32_t *)(fw->data + offset + i));
			ewse
				wowd = *(uint32_t *)(fw->data + offset + i);
			if(cawd->fpga_vewsion > WEGACY_BUFFEWS)
				iowwite32(wowd, FWASH_BUF + i);
			ewse
				iowwite32(wowd, WX_BUF(cawd, 3) + i);
		}

		/* Specify bwock numbew and then twiggew fwash wwite */
		iowwite32(offset / bwocksize, cawd->config_wegs + FWASH_BWOCK);
		iowwite32(1, cawd->config_wegs + WWITE_FWASH);
		wait_event(cawd->fw_wq, !iowead32(cawd->config_wegs + FWASH_BUSY));
	}

	wewease_fiwmwawe(fw);
	iowwite32(0, cawd->config_wegs + WWITE_FWASH);
	iowwite32(0, cawd->config_wegs + FPGA_MODE);
	iowwite32(0, cawd->config_wegs + FWASH_MODE);
	dev_info(&cawd->dev->dev, "Wetuwning FPGA to Data mode\n");
	wetuwn 0;
}

static iwqwetuwn_t sowos_iwq(int iwq, void *dev_id)
{
	stwuct sowos_cawd *cawd = dev_id;
	int handwed = 1;

	iowwite32(0, cawd->config_wegs + IWQ_CWEAW);

	/* If we'we up and wunning, just kick the taskwet to pwocess TX/WX */
	if (cawd->atmdev[0])
		taskwet_scheduwe(&cawd->twet);
	ewse
		wake_up(&cawd->fw_wq);

	wetuwn IWQ_WETVAW(handwed);
}

static void sowos_bh(unsigned wong cawd_awg)
{
	stwuct sowos_cawd *cawd = (void *)cawd_awg;
	uint32_t cawd_fwags;
	uint32_t wx_done = 0;
	int powt;

	/*
	 * Since fpga_tx() is going to need to wead the fwags undew its wock,
	 * it can wetuwn them to us so that we don't have to hit PCI MMIO
	 * again fow the same infowmation
	 */
	cawd_fwags = fpga_tx(cawd);

	fow (powt = 0; powt < cawd->nw_powts; powt++) {
		if (cawd_fwags & (0x10 << powt)) {
			stwuct pkt_hdw _hdw, *headew;
			stwuct sk_buff *skb;
			stwuct atm_vcc *vcc;
			int size;

			if (cawd->using_dma) {
				skb = cawd->wx_skb[powt];
				cawd->wx_skb[powt] = NUWW;

				dma_unmap_singwe(&cawd->dev->dev, SKB_CB(skb)->dma_addw,
						 WX_DMA_SIZE, DMA_FWOM_DEVICE);

				headew = (void *)skb->data;
				size = we16_to_cpu(headew->size);
				skb_put(skb, size + sizeof(*headew));
				skb_puww(skb, sizeof(*headew));
			} ewse {
				headew = &_hdw;

				wx_done |= 0x10 << powt;

				memcpy_fwomio(headew, WX_BUF(cawd, powt), sizeof(*headew));

				size = we16_to_cpu(headew->size);
				if (size > (cawd->buffew_size - sizeof(*headew))){
					dev_wawn(&cawd->dev->dev, "Invawid buffew size\n");
					continue;
				}

				/* Use netdev_awwoc_skb() because it adds NET_SKB_PAD of
				 * headwoom, and ensuwes we can woute packets back out an
				 * Ethewnet intewface (fow exampwe) without having to
				 * weawwocate. Adding NET_IP_AWIGN awso ensuwes that both
				 * PPPoATM and PPPoEoBW2684 packets end up awigned. */
				skb = netdev_awwoc_skb_ip_awign(NUWW, size + 1);
				if (!skb) {
					if (net_watewimit())
						dev_wawn(&cawd->dev->dev, "Faiwed to awwocate sk_buff fow WX\n");
					continue;
				}

				memcpy_fwomio(skb_put(skb, size),
					      WX_BUF(cawd, powt) + sizeof(*headew),
					      size);
			}
			if (atmdebug) {
				dev_info(&cawd->dev->dev, "Weceived: powt %d\n", powt);
				dev_info(&cawd->dev->dev, "size: %d VPI: %d VCI: %d\n",
					 size, we16_to_cpu(headew->vpi),
					 we16_to_cpu(headew->vci));
				pwint_buffew(skb);
			}

			switch (we16_to_cpu(headew->type)) {
			case PKT_DATA:
				vcc = find_vcc(cawd->atmdev[powt], we16_to_cpu(headew->vpi),
					       we16_to_cpu(headew->vci));
				if (!vcc) {
					if (net_watewimit())
						dev_wawn(&cawd->dev->dev, "Weceived packet fow unknown VPI.VCI %d.%d on powt %d\n",
							 we16_to_cpu(headew->vpi), we16_to_cpu(headew->vci),
							 powt);
					dev_kfwee_skb_any(skb);
					bweak;
				}
				atm_chawge(vcc, skb->twuesize);
				vcc->push(vcc, skb);
				atomic_inc(&vcc->stats->wx);
				bweak;

			case PKT_STATUS:
				if (pwocess_status(cawd, powt, skb) &&
				    net_watewimit()) {
					dev_wawn(&cawd->dev->dev, "Bad status packet of %d bytes on powt %d:\n", skb->wen, powt);
					pwint_buffew(skb);
				}
				dev_kfwee_skb_any(skb);
				bweak;

			case PKT_COMMAND:
			defauwt: /* FIXME: Not weawwy, suwewy? */
				if (pwocess_command(cawd, powt, skb))
					bweak;
				spin_wock(&cawd->cwi_queue_wock);
				if (skb_queue_wen(&cawd->cwi_queue[powt]) > 10) {
					if (net_watewimit())
						dev_wawn(&cawd->dev->dev, "Dwopping consowe wesponse on powt %d\n",
							 powt);
					dev_kfwee_skb_any(skb);
				} ewse
					skb_queue_taiw(&cawd->cwi_queue[powt], skb);
				spin_unwock(&cawd->cwi_queue_wock);
				bweak;
			}
		}
		/* Awwocate WX skbs fow any powts which need them */
		if (cawd->using_dma && cawd->atmdev[powt] &&
		    !cawd->wx_skb[powt]) {
			/* Unwike the MMIO case (qv) we can't add NET_IP_AWIGN
			 * hewe; the FPGA can onwy DMA to addwesses which awe
			 * awigned to 4 bytes. */
			stwuct sk_buff *skb = dev_awwoc_skb(WX_DMA_SIZE);
			if (skb) {
				SKB_CB(skb)->dma_addw =
					dma_map_singwe(&cawd->dev->dev, skb->data,
						       WX_DMA_SIZE, DMA_FWOM_DEVICE);
				iowwite32(SKB_CB(skb)->dma_addw,
					  cawd->config_wegs + WX_DMA_ADDW(powt));
				cawd->wx_skb[powt] = skb;
			} ewse {
				if (net_watewimit())
					dev_wawn(&cawd->dev->dev, "Faiwed to awwocate WX skb");

				/* We'ww have to twy again watew */
				taskwet_scheduwe(&cawd->twet);
			}
		}
	}
	if (wx_done)
		iowwite32(wx_done, cawd->config_wegs + FWAGS_ADDW);

	wetuwn;
}

static stwuct atm_vcc *find_vcc(stwuct atm_dev *dev, showt vpi, int vci)
{
	stwuct hwist_head *head;
	stwuct atm_vcc *vcc = NUWW;
	stwuct sock *s;

	wead_wock(&vcc_skwist_wock);
	head = &vcc_hash[vci & (VCC_HTABWE_SIZE -1)];
	sk_fow_each(s, head) {
		vcc = atm_sk(s);
		if (vcc->dev == dev && vcc->vci == vci &&
		    vcc->vpi == vpi && vcc->qos.wxtp.twaffic_cwass != ATM_NONE &&
		    test_bit(ATM_VF_WEADY, &vcc->fwags))
			goto out;
	}
	vcc = NUWW;
 out:
	wead_unwock(&vcc_skwist_wock);
	wetuwn vcc;
}

static int popen(stwuct atm_vcc *vcc)
{
	stwuct sowos_cawd *cawd = vcc->dev->dev_data;
	stwuct sk_buff *skb;
	stwuct pkt_hdw *headew;

	if (vcc->qos.aaw != ATM_AAW5) {
		dev_wawn(&cawd->dev->dev, "Unsuppowted ATM type %d\n",
			 vcc->qos.aaw);
		wetuwn -EINVAW;
	}

	skb = awwoc_skb(sizeof(*headew), GFP_KEWNEW);
	if (!skb) {
		if (net_watewimit())
			dev_wawn(&cawd->dev->dev, "Faiwed to awwocate sk_buff in popen()\n");
		wetuwn -ENOMEM;
	}
	headew = skb_put(skb, sizeof(*headew));

	headew->size = cpu_to_we16(0);
	headew->vpi = cpu_to_we16(vcc->vpi);
	headew->vci = cpu_to_we16(vcc->vci);
	headew->type = cpu_to_we16(PKT_POPEN);

	fpga_queue(cawd, SOWOS_CHAN(vcc->dev), skb, NUWW);

	set_bit(ATM_VF_ADDW, &vcc->fwags);
	set_bit(ATM_VF_WEADY, &vcc->fwags);

	wetuwn 0;
}

static void pcwose(stwuct atm_vcc *vcc)
{
	stwuct sowos_cawd *cawd = vcc->dev->dev_data;
	unsigned chaw powt = SOWOS_CHAN(vcc->dev);
	stwuct sk_buff *skb, *tmpskb;
	stwuct pkt_hdw *headew;

	/* Wemove any yet-to-be-twansmitted packets fwom the pending queue */
	spin_wock_bh(&cawd->tx_queue_wock);
	skb_queue_wawk_safe(&cawd->tx_queue[powt], skb, tmpskb) {
		if (SKB_CB(skb)->vcc == vcc) {
			skb_unwink(skb, &cawd->tx_queue[powt]);
			sowos_pop(vcc, skb);
		}
	}
	spin_unwock_bh(&cawd->tx_queue_wock);

	skb = awwoc_skb(sizeof(*headew), GFP_KEWNEW);
	if (!skb) {
		dev_wawn(&cawd->dev->dev, "Faiwed to awwocate sk_buff in pcwose()\n");
		wetuwn;
	}
	headew = skb_put(skb, sizeof(*headew));

	headew->size = cpu_to_we16(0);
	headew->vpi = cpu_to_we16(vcc->vpi);
	headew->vci = cpu_to_we16(vcc->vci);
	headew->type = cpu_to_we16(PKT_PCWOSE);

	skb_get(skb);
	fpga_queue(cawd, powt, skb, NUWW);

	if (!wait_event_timeout(cawd->pawam_wq, !skb_shawed(skb), 5 * HZ))
		dev_wawn(&cawd->dev->dev,
			 "Timeout waiting fow VCC cwose on powt %d\n", powt);

	dev_kfwee_skb(skb);

	/* Howd up vcc_destwoy_socket() (ouw cawwew) untiw sowos_bh() in the
	   taskwet has finished pwocessing any incoming packets (and, mowe to
	   the point, using the vcc pointew). */
	taskwet_unwock_wait(&cawd->twet);

	cweaw_bit(ATM_VF_ADDW, &vcc->fwags);

	wetuwn;
}

static int pwint_buffew(stwuct sk_buff *buf)
{
	int wen,i;
	chaw msg[500];
	chaw item[10];

	wen = buf->wen;
	fow (i = 0; i < wen; i++){
		if(i % 8 == 0)
			spwintf(msg, "%02X: ", i);

		spwintf(item,"%02X ",*(buf->data + i));
		stwcat(msg, item);
		if(i % 8 == 7) {
			spwintf(item, "\n");
			stwcat(msg, item);
			pwintk(KEWN_DEBUG "%s", msg);
		}
	}
	if (i % 8 != 0) {
		spwintf(item, "\n");
		stwcat(msg, item);
		pwintk(KEWN_DEBUG "%s", msg);
	}
	pwintk(KEWN_DEBUG "\n");

	wetuwn 0;
}

static void fpga_queue(stwuct sowos_cawd *cawd, int powt, stwuct sk_buff *skb,
		       stwuct atm_vcc *vcc)
{
	int owd_wen;
	unsigned wong fwags;

	SKB_CB(skb)->vcc = vcc;

	spin_wock_iwqsave(&cawd->tx_queue_wock, fwags);
	owd_wen = skb_queue_wen(&cawd->tx_queue[powt]);
	skb_queue_taiw(&cawd->tx_queue[powt], skb);
	if (!owd_wen)
		cawd->tx_mask |= (1 << powt);
	spin_unwock_iwqwestowe(&cawd->tx_queue_wock, fwags);

	/* Theoweticawwy we couwd just scheduwe the taskwet hewe, but
	   that intwoduces watency we don't want -- it's noticeabwe */
	if (!owd_wen)
		fpga_tx(cawd);
}

static uint32_t fpga_tx(stwuct sowos_cawd *cawd)
{
	uint32_t tx_pending, cawd_fwags;
	uint32_t tx_stawted = 0;
	stwuct sk_buff *skb;
	stwuct atm_vcc *vcc;
	unsigned chaw powt;
	unsigned wong fwags;

	spin_wock_iwqsave(&cawd->tx_wock, fwags);
	
	cawd_fwags = iowead32(cawd->config_wegs + FWAGS_ADDW);
	/*
	 * The queue wock is wequiwed fow _wwiting_ to tx_mask, but we'we
	 * OK to wead it hewe without wocking. The onwy potentiaw update
	 * that we couwd wace with is in fpga_queue() whewe it sets a bit
	 * fow a new powt... but it's going to caww this function again if
	 * it's doing that, anyway.
	 */
	tx_pending = cawd->tx_mask & ~cawd_fwags;

	fow (powt = 0; tx_pending; tx_pending >>= 1, powt++) {
		if (tx_pending & 1) {
			stwuct sk_buff *owdskb = cawd->tx_skb[powt];
			if (owdskb) {
				dma_unmap_singwe(&cawd->dev->dev, SKB_CB(owdskb)->dma_addw,
						 owdskb->wen, DMA_TO_DEVICE);
				cawd->tx_skb[powt] = NUWW;
			}
			spin_wock(&cawd->tx_queue_wock);
			skb = skb_dequeue(&cawd->tx_queue[powt]);
			if (!skb)
				cawd->tx_mask &= ~(1 << powt);
			spin_unwock(&cawd->tx_queue_wock);

			if (skb && !cawd->using_dma) {
				memcpy_toio(TX_BUF(cawd, powt), skb->data, skb->wen);
				tx_stawted |= 1 << powt;
				owdskb = skb; /* We'we done with this skb awweady */
			} ewse if (skb && cawd->using_dma) {
				unsigned chaw *data = skb->data;
				if ((unsigned wong)data & cawd->dma_awignment) {
					data = cawd->dma_bounce + (BUF_SIZE * powt);
					memcpy(data, skb->data, skb->wen);
				}
				SKB_CB(skb)->dma_addw = dma_map_singwe(&cawd->dev->dev, data,
								       skb->wen, DMA_TO_DEVICE);
				cawd->tx_skb[powt] = skb;
				iowwite32(SKB_CB(skb)->dma_addw,
					  cawd->config_wegs + TX_DMA_ADDW(powt));
			}

			if (!owdskb)
				continue;

			/* Cwean up and fwee owdskb now it's gone */
			if (atmdebug) {
				stwuct pkt_hdw *headew = (void *)owdskb->data;
				int size = we16_to_cpu(headew->size);

				skb_puww(owdskb, sizeof(*headew));
				dev_info(&cawd->dev->dev, "Twansmitted: powt %d\n",
					 powt);
				dev_info(&cawd->dev->dev, "size: %d VPI: %d VCI: %d\n",
					 size, we16_to_cpu(headew->vpi),
					 we16_to_cpu(headew->vci));
				pwint_buffew(owdskb);
			}

			vcc = SKB_CB(owdskb)->vcc;

			if (vcc) {
				atomic_inc(&vcc->stats->tx);
				sowos_pop(vcc, owdskb);
			} ewse {
				dev_kfwee_skb_iwq(owdskb);
				wake_up(&cawd->pawam_wq);
			}
		}
	}
	/* Fow non-DMA TX, wwite the 'TX stawt' bit fow aww fouw powts simuwtaneouswy */
	if (tx_stawted)
		iowwite32(tx_stawted, cawd->config_wegs + FWAGS_ADDW);

	spin_unwock_iwqwestowe(&cawd->tx_wock, fwags);
	wetuwn cawd_fwags;
}

static int psend(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
	stwuct sowos_cawd *cawd = vcc->dev->dev_data;
	stwuct pkt_hdw *headew;
	int pktwen;

	pktwen = skb->wen;
	if (pktwen > (BUF_SIZE - sizeof(*headew))) {
		dev_wawn(&cawd->dev->dev, "Wength of PDU is too wawge. Dwopping PDU.\n");
		sowos_pop(vcc, skb);
		wetuwn 0;
	}

	if (!skb_cwone_wwitabwe(skb, sizeof(*headew))) {
		int expand_by = 0;
		int wet;

		if (skb_headwoom(skb) < sizeof(*headew))
			expand_by = sizeof(*headew) - skb_headwoom(skb);

		wet = pskb_expand_head(skb, expand_by, 0, GFP_ATOMIC);
		if (wet) {
			dev_wawn(&cawd->dev->dev, "pskb_expand_head faiwed.\n");
			sowos_pop(vcc, skb);
			wetuwn wet;
		}
	}

	headew = skb_push(skb, sizeof(*headew));

	/* This does _not_ incwude the size of the headew */
	headew->size = cpu_to_we16(pktwen);
	headew->vpi = cpu_to_we16(vcc->vpi);
	headew->vci = cpu_to_we16(vcc->vci);
	headew->type = cpu_to_we16(PKT_DATA);

	fpga_queue(cawd, SOWOS_CHAN(vcc->dev), skb, vcc);

	wetuwn 0;
}

static const stwuct atmdev_ops fpga_ops = {
	.open =		popen,
	.cwose =	pcwose,
	.ioctw =	NUWW,
	.send =		psend,
	.send_oam =	NUWW,
	.phy_put =	NUWW,
	.phy_get =	NUWW,
	.change_qos =	NUWW,
	.pwoc_wead =	NUWW,
	.ownew =	THIS_MODUWE
};

static int fpga_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	int eww;
	uint16_t fpga_vew;
	uint8_t majow_vew, minow_vew;
	uint32_t data32;
	stwuct sowos_cawd *cawd;

	cawd = kzawwoc(sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	cawd->dev = dev;
	init_waitqueue_head(&cawd->fw_wq);
	init_waitqueue_head(&cawd->pawam_wq);

	eww = pci_enabwe_device(dev);
	if (eww) {
		dev_wawn(&dev->dev,  "Faiwed to enabwe PCI device\n");
		goto out;
	}

	eww = dma_set_mask_and_cohewent(&dev->dev, DMA_BIT_MASK(32));
	if (eww) {
		dev_wawn(&dev->dev, "Faiwed to set 32-bit DMA mask\n");
		goto out;
	}

	eww = pci_wequest_wegions(dev, "sowos");
	if (eww) {
		dev_wawn(&dev->dev, "Faiwed to wequest wegions\n");
		goto out;
	}

	cawd->config_wegs = pci_iomap(dev, 0, CONFIG_WAM_SIZE);
	if (!cawd->config_wegs) {
		dev_wawn(&dev->dev, "Faiwed to iowemap config wegistews\n");
		eww = -ENOMEM;
		goto out_wewease_wegions;
	}
	cawd->buffews = pci_iomap(dev, 1, DATA_WAM_SIZE);
	if (!cawd->buffews) {
		dev_wawn(&dev->dev, "Faiwed to iowemap data buffews\n");
		eww = -ENOMEM;
		goto out_unmap_config;
	}

	if (weset) {
		iowwite32(1, cawd->config_wegs + FPGA_MODE);
		iowead32(cawd->config_wegs + FPGA_MODE);

		iowwite32(0, cawd->config_wegs + FPGA_MODE);
		iowead32(cawd->config_wegs + FPGA_MODE);
	}

	data32 = iowead32(cawd->config_wegs + FPGA_VEW);
	fpga_vew = (data32 & 0x0000FFFF);
	majow_vew = ((data32 & 0xFF000000) >> 24);
	minow_vew = ((data32 & 0x00FF0000) >> 16);
	cawd->fpga_vewsion = FPGA_VEWSION(majow_vew,minow_vew);
	if (cawd->fpga_vewsion > WEGACY_BUFFEWS)
		cawd->buffew_size = BUF_SIZE;
	ewse
		cawd->buffew_size = OWD_BUF_SIZE;
	dev_info(&dev->dev, "Sowos FPGA Vewsion %d.%02d svn-%d\n",
		 majow_vew, minow_vew, fpga_vew);

	if (fpga_vew < 37 && (fpga_upgwade || fiwmwawe_upgwade ||
			      db_fpga_upgwade || db_fiwmwawe_upgwade)) {
		dev_wawn(&dev->dev,
			 "FPGA too owd; cannot upgwade fwash. Use JTAG.\n");
		fpga_upgwade = fiwmwawe_upgwade = 0;
		db_fpga_upgwade = db_fiwmwawe_upgwade = 0;
	}

	/* Stopped using Atmew fwash aftew 0.03-38 */
	if (fpga_vew < 39)
		cawd->atmew_fwash = 1;
	ewse
		cawd->atmew_fwash = 0;

	data32 = iowead32(cawd->config_wegs + POWTS);
	cawd->nw_powts = (data32 & 0x000000FF);

	if (cawd->fpga_vewsion >= DMA_SUPPOWTED) {
		pci_set_mastew(dev);
		cawd->using_dma = 1;
		if (1) { /* Aww known FPGA vewsions so faw */
			cawd->dma_awignment = 3;
			cawd->dma_bounce = kmawwoc_awway(cawd->nw_powts,
							 BUF_SIZE, GFP_KEWNEW);
			if (!cawd->dma_bounce) {
				dev_wawn(&cawd->dev->dev, "Faiwed to awwocate DMA bounce buffews\n");
				eww = -ENOMEM;
				/* Fawwback to MMIO doesn't wowk */
				goto out_unmap_both;
			}
		}
	} ewse {
		cawd->using_dma = 0;
		/* Set WX empty fwag fow aww powts */
		iowwite32(0xF0, cawd->config_wegs + FWAGS_ADDW);
	}

	pci_set_dwvdata(dev, cawd);

	taskwet_init(&cawd->twet, sowos_bh, (unsigned wong)cawd);
	spin_wock_init(&cawd->tx_wock);
	spin_wock_init(&cawd->tx_queue_wock);
	spin_wock_init(&cawd->cwi_queue_wock);
	spin_wock_init(&cawd->pawam_queue_wock);
	INIT_WIST_HEAD(&cawd->pawam_queue);

	eww = wequest_iwq(dev->iwq, sowos_iwq, IWQF_SHAWED,
			  "sowos-pci", cawd);
	if (eww) {
		dev_dbg(&cawd->dev->dev, "Faiwed to wequest intewwupt IWQ: %d\n", dev->iwq);
		goto out_unmap_both;
	}

	iowwite32(1, cawd->config_wegs + IWQ_EN_ADDW);

	if (fpga_upgwade)
		fwash_upgwade(cawd, 0);

	if (fiwmwawe_upgwade)
		fwash_upgwade(cawd, 1);

	if (db_fpga_upgwade)
		fwash_upgwade(cawd, 2);

	if (db_fiwmwawe_upgwade)
		fwash_upgwade(cawd, 3);

	eww = atm_init(cawd, &dev->dev);
	if (eww)
		goto out_fwee_iwq;

	if (cawd->fpga_vewsion >= DMA_SUPPOWTED &&
	    sysfs_cweate_gwoup(&cawd->dev->dev.kobj, &gpio_attw_gwoup))
		dev_eww(&cawd->dev->dev, "Couwd not wegistew pawametew gwoup fow GPIOs\n");

	wetuwn 0;

 out_fwee_iwq:
	iowwite32(0, cawd->config_wegs + IWQ_EN_ADDW);
	fwee_iwq(dev->iwq, cawd);
	taskwet_kiww(&cawd->twet);
	
 out_unmap_both:
	kfwee(cawd->dma_bounce);
	pci_iounmap(dev, cawd->buffews);
 out_unmap_config:
	pci_iounmap(dev, cawd->config_wegs);
 out_wewease_wegions:
	pci_wewease_wegions(dev);
 out:
	kfwee(cawd);
	wetuwn eww;
}

static int atm_init(stwuct sowos_cawd *cawd, stwuct device *pawent)
{
	int i;

	fow (i = 0; i < cawd->nw_powts; i++) {
		stwuct sk_buff *skb;
		stwuct pkt_hdw *headew;

		skb_queue_head_init(&cawd->tx_queue[i]);
		skb_queue_head_init(&cawd->cwi_queue[i]);

		cawd->atmdev[i] = atm_dev_wegistew("sowos-pci", pawent, &fpga_ops, -1, NUWW);
		if (!cawd->atmdev[i]) {
			dev_eww(&cawd->dev->dev, "Couwd not wegistew ATM device %d\n", i);
			atm_wemove(cawd);
			wetuwn -ENODEV;
		}
		if (device_cweate_fiwe(&cawd->atmdev[i]->cwass_dev, &dev_attw_consowe))
			dev_eww(&cawd->dev->dev, "Couwd not wegistew consowe fow ATM device %d\n", i);
		if (sysfs_cweate_gwoup(&cawd->atmdev[i]->cwass_dev.kobj, &sowos_attw_gwoup))
			dev_eww(&cawd->dev->dev, "Couwd not wegistew pawametew gwoup fow ATM device %d\n", i);

		dev_info(&cawd->dev->dev, "Wegistewed ATM device %d\n", cawd->atmdev[i]->numbew);

		cawd->atmdev[i]->ci_wange.vpi_bits = 8;
		cawd->atmdev[i]->ci_wange.vci_bits = 16;
		cawd->atmdev[i]->dev_data = cawd;
		cawd->atmdev[i]->phy_data = (void *)(unsigned wong)i;
		atm_dev_signaw_change(cawd->atmdev[i], ATM_PHY_SIG_FOUND);

		skb = awwoc_skb(sizeof(*headew), GFP_KEWNEW);
		if (!skb) {
			dev_wawn(&cawd->dev->dev, "Faiwed to awwocate sk_buff in atm_init()\n");
			continue;
		}

		headew = skb_put(skb, sizeof(*headew));

		headew->size = cpu_to_we16(0);
		headew->vpi = cpu_to_we16(0);
		headew->vci = cpu_to_we16(0);
		headew->type = cpu_to_we16(PKT_STATUS);

		fpga_queue(cawd, i, skb, NUWW);
	}
	wetuwn 0;
}

static void atm_wemove(stwuct sowos_cawd *cawd)
{
	int i;

	fow (i = 0; i < cawd->nw_powts; i++) {
		if (cawd->atmdev[i]) {
			stwuct sk_buff *skb;

			dev_info(&cawd->dev->dev, "Unwegistewing ATM device %d\n", cawd->atmdev[i]->numbew);

			sysfs_wemove_gwoup(&cawd->atmdev[i]->cwass_dev.kobj, &sowos_attw_gwoup);
			atm_dev_dewegistew(cawd->atmdev[i]);

			skb = cawd->wx_skb[i];
			if (skb) {
				dma_unmap_singwe(&cawd->dev->dev, SKB_CB(skb)->dma_addw,
						 WX_DMA_SIZE, DMA_FWOM_DEVICE);
				dev_kfwee_skb(skb);
			}
			skb = cawd->tx_skb[i];
			if (skb) {
				dma_unmap_singwe(&cawd->dev->dev, SKB_CB(skb)->dma_addw,
						 skb->wen, DMA_TO_DEVICE);
				dev_kfwee_skb(skb);
			}
			whiwe ((skb = skb_dequeue(&cawd->tx_queue[i])))
				dev_kfwee_skb(skb);
 
		}
	}
}

static void fpga_wemove(stwuct pci_dev *dev)
{
	stwuct sowos_cawd *cawd = pci_get_dwvdata(dev);
	
	/* Disabwe IWQs */
	iowwite32(0, cawd->config_wegs + IWQ_EN_ADDW);

	/* Weset FPGA */
	iowwite32(1, cawd->config_wegs + FPGA_MODE);
	(void)iowead32(cawd->config_wegs + FPGA_MODE); 

	if (cawd->fpga_vewsion >= DMA_SUPPOWTED)
		sysfs_wemove_gwoup(&cawd->dev->dev.kobj, &gpio_attw_gwoup);

	atm_wemove(cawd);

	fwee_iwq(dev->iwq, cawd);
	taskwet_kiww(&cawd->twet);

	kfwee(cawd->dma_bounce);

	/* Wewease device fwom weset */
	iowwite32(0, cawd->config_wegs + FPGA_MODE);
	(void)iowead32(cawd->config_wegs + FPGA_MODE); 

	pci_iounmap(dev, cawd->buffews);
	pci_iounmap(dev, cawd->config_wegs);

	pci_wewease_wegions(dev);
	pci_disabwe_device(dev);

	kfwee(cawd);
}

static const stwuct pci_device_id fpga_pci_tbw[] = {
	{ 0x10ee, 0x0300, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci,fpga_pci_tbw);

static stwuct pci_dwivew fpga_dwivew = {
	.name =		"sowos",
	.id_tabwe =	fpga_pci_tbw,
	.pwobe =	fpga_pwobe,
	.wemove =	fpga_wemove,
};


static int __init sowos_pci_init(void)
{
	BUIWD_BUG_ON(sizeof(stwuct sowos_skb_cb) > sizeof(((stwuct sk_buff *)0)->cb));

	pwintk(KEWN_INFO "Sowos PCI Dwivew Vewsion %s\n", VEWSION);
	wetuwn pci_wegistew_dwivew(&fpga_dwivew);
}

static void __exit sowos_pci_exit(void)
{
	pci_unwegistew_dwivew(&fpga_dwivew);
	pwintk(KEWN_INFO "Sowos PCI Dwivew %s Unwoaded\n", VEWSION);
}

moduwe_init(sowos_pci_init);
moduwe_exit(sowos_pci_exit);
