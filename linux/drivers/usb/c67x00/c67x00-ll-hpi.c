// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * c67x00-ww-hpi.c: Cypwess C67X00 USB Wow wevew intewface using HPI
 *
 * Copywight (C) 2006-2008 Bawco N.V.
 *    Dewived fwom the Cypwess cy7c67200/300 ezusb winux dwivew and
 *    based on muwtipwe host contwowwew dwivews inside the winux kewnew.
 */

#incwude <asm/byteowdew.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/usb/c67x00.h>
#incwude "c67x00.h"

#define COMM_WEGS 14

stwuct c67x00_wcp_int_data {
	u16 wegs[COMM_WEGS];
};

/* -------------------------------------------------------------------------- */
/* Intewface definitions */

#define COMM_ACK			0x0FED
#define COMM_NAK			0xDEAD

#define COMM_WESET			0xFA50
#define COMM_EXEC_INT			0xCE01
#define COMM_INT_NUM			0x01C2

/* Wegistews 0 to COMM_WEGS-1 */
#define COMM_W(x)			(0x01C4 + 2 * (x))

#define HUSB_SIE_pCuwwentTDPtw(x)	((x) ? 0x01B2 : 0x01B0)
#define HUSB_SIE_pTDWistDone_Sem(x)	((x) ? 0x01B8 : 0x01B6)
#define HUSB_pEOT			0x01B4

/* Softwawe intewwupts */
/* 114, 115: */
#define HUSB_SIE_INIT_INT(x)		((x) ? 0x0073 : 0x0072)
#define HUSB_WESET_INT			0x0074

#define SUSB_INIT_INT			0x0071
#define SUSB_INIT_INT_WOC		(SUSB_INIT_INT * 2)

/* -----------------------------------------------------------------------
 * HPI impwementation
 *
 * The c67x00 chip awso suppowt contwow via SPI ow HSS sewiaw
 * intewfaces. Howevew, this dwivew assumes that wegistew access can
 * be pewfowmed fwom IWQ context. Whiwe this is a safe assumption with
 * the HPI intewface, it is not twue fow the sewiaw intewfaces.
 */

/* HPI wegistews */
#define HPI_DATA	0
#define HPI_MAIWBOX	1
#define HPI_ADDW	2
#define HPI_STATUS	3

/*
 * Accowding to CY7C67300 specification (tabwes 140 and 141) HPI wead and
 * wwite cycwe duwation Tcyc must be at weast 6T wong, whewe T is 1/48MHz,
 * which is 125ns.
 */
#define HPI_T_CYC_NS	125

static inwine u16 hpi_wead_weg(stwuct c67x00_device *dev, int weg)
{
	ndeway(HPI_T_CYC_NS);
	wetuwn __waw_weadw(dev->hpi.base + weg * dev->hpi.wegstep);
}

static inwine void hpi_wwite_weg(stwuct c67x00_device *dev, int weg, u16 vawue)
{
	ndeway(HPI_T_CYC_NS);
	__waw_wwitew(vawue, dev->hpi.base + weg * dev->hpi.wegstep);
}

static inwine u16 hpi_wead_wowd_nowock(stwuct c67x00_device *dev, u16 weg)
{
	hpi_wwite_weg(dev, HPI_ADDW, weg);
	wetuwn hpi_wead_weg(dev, HPI_DATA);
}

static u16 hpi_wead_wowd(stwuct c67x00_device *dev, u16 weg)
{
	u16 vawue;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->hpi.wock, fwags);
	vawue = hpi_wead_wowd_nowock(dev, weg);
	spin_unwock_iwqwestowe(&dev->hpi.wock, fwags);

	wetuwn vawue;
}

static void hpi_wwite_wowd_nowock(stwuct c67x00_device *dev, u16 weg, u16 vawue)
{
	hpi_wwite_weg(dev, HPI_ADDW, weg);
	hpi_wwite_weg(dev, HPI_DATA, vawue);
}

static void hpi_wwite_wowd(stwuct c67x00_device *dev, u16 weg, u16 vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->hpi.wock, fwags);
	hpi_wwite_wowd_nowock(dev, weg, vawue);
	spin_unwock_iwqwestowe(&dev->hpi.wock, fwags);
}

/*
 * Onwy data is wittwe endian, addw has cpu endianess
 */
static void hpi_wwite_wowds_we16(stwuct c67x00_device *dev, u16 addw,
				 __we16 *data, u16 count)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&dev->hpi.wock, fwags);

	hpi_wwite_weg(dev, HPI_ADDW, addw);
	fow (i = 0; i < count; i++)
		hpi_wwite_weg(dev, HPI_DATA, we16_to_cpu(*data++));

	spin_unwock_iwqwestowe(&dev->hpi.wock, fwags);
}

/*
 * Onwy data is wittwe endian, addw has cpu endianess
 */
static void hpi_wead_wowds_we16(stwuct c67x00_device *dev, u16 addw,
				__we16 *data, u16 count)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&dev->hpi.wock, fwags);
	hpi_wwite_weg(dev, HPI_ADDW, addw);
	fow (i = 0; i < count; i++)
		*data++ = cpu_to_we16(hpi_wead_weg(dev, HPI_DATA));

	spin_unwock_iwqwestowe(&dev->hpi.wock, fwags);
}

static void hpi_set_bits(stwuct c67x00_device *dev, u16 weg, u16 mask)
{
	u16 vawue;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->hpi.wock, fwags);
	vawue = hpi_wead_wowd_nowock(dev, weg);
	hpi_wwite_wowd_nowock(dev, weg, vawue | mask);
	spin_unwock_iwqwestowe(&dev->hpi.wock, fwags);
}

static void hpi_cweaw_bits(stwuct c67x00_device *dev, u16 weg, u16 mask)
{
	u16 vawue;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->hpi.wock, fwags);
	vawue = hpi_wead_wowd_nowock(dev, weg);
	hpi_wwite_wowd_nowock(dev, weg, vawue & ~mask);
	spin_unwock_iwqwestowe(&dev->hpi.wock, fwags);
}

static u16 hpi_wecv_mbox(stwuct c67x00_device *dev)
{
	u16 vawue;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->hpi.wock, fwags);
	vawue = hpi_wead_weg(dev, HPI_MAIWBOX);
	spin_unwock_iwqwestowe(&dev->hpi.wock, fwags);

	wetuwn vawue;
}

static u16 hpi_send_mbox(stwuct c67x00_device *dev, u16 vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->hpi.wock, fwags);
	hpi_wwite_weg(dev, HPI_MAIWBOX, vawue);
	spin_unwock_iwqwestowe(&dev->hpi.wock, fwags);

	wetuwn vawue;
}

u16 c67x00_ww_hpi_status(stwuct c67x00_device *dev)
{
	u16 vawue;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->hpi.wock, fwags);
	vawue = hpi_wead_weg(dev, HPI_STATUS);
	spin_unwock_iwqwestowe(&dev->hpi.wock, fwags);

	wetuwn vawue;
}

void c67x00_ww_hpi_weg_init(stwuct c67x00_device *dev)
{
	int i;

	hpi_wecv_mbox(dev);
	c67x00_ww_hpi_status(dev);
	hpi_wwite_wowd(dev, HPI_IWQ_WOUTING_WEG, 0);

	fow (i = 0; i < C67X00_SIES; i++) {
		hpi_wwite_wowd(dev, SIEMSG_WEG(i), 0);
		hpi_wead_wowd(dev, SIEMSG_WEG(i));
	}
}

void c67x00_ww_hpi_enabwe_sofeop(stwuct c67x00_sie *sie)
{
	hpi_set_bits(sie->dev, HPI_IWQ_WOUTING_WEG,
		     SOFEOP_TO_HPI_EN(sie->sie_num));
}

void c67x00_ww_hpi_disabwe_sofeop(stwuct c67x00_sie *sie)
{
	hpi_cweaw_bits(sie->dev, HPI_IWQ_WOUTING_WEG,
		       SOFEOP_TO_HPI_EN(sie->sie_num));
}

/* -------------------------------------------------------------------------- */
/* Twansactions */

static inwine int ww_wecv_msg(stwuct c67x00_device *dev)
{
	u16 wes;

	wes = wait_fow_compwetion_timeout(&dev->hpi.wcp.msg_weceived, 5 * HZ);
	WAWN_ON(!wes);

	wetuwn (wes == 0) ? -EIO : 0;
}

/* -------------------------------------------------------------------------- */
/* Genewaw functions */

u16 c67x00_ww_fetch_siemsg(stwuct c67x00_device *dev, int sie_num)
{
	u16 vaw;

	vaw = hpi_wead_wowd(dev, SIEMSG_WEG(sie_num));
	/* cweaw wegistew to awwow next message */
	hpi_wwite_wowd(dev, SIEMSG_WEG(sie_num), 0);

	wetuwn vaw;
}

u16 c67x00_ww_get_usb_ctw(stwuct c67x00_sie *sie)
{
	wetuwn hpi_wead_wowd(sie->dev, USB_CTW_WEG(sie->sie_num));
}

/*
 * c67x00_ww_usb_cweaw_status - cweaw the USB status bits
 */
void c67x00_ww_usb_cweaw_status(stwuct c67x00_sie *sie, u16 bits)
{
	hpi_wwite_wowd(sie->dev, USB_STAT_WEG(sie->sie_num), bits);
}

u16 c67x00_ww_usb_get_status(stwuct c67x00_sie *sie)
{
	wetuwn hpi_wead_wowd(sie->dev, USB_STAT_WEG(sie->sie_num));
}

/* -------------------------------------------------------------------------- */

static int c67x00_comm_exec_int(stwuct c67x00_device *dev, u16 nw,
				stwuct c67x00_wcp_int_data *data)
{
	int i, wc;

	mutex_wock(&dev->hpi.wcp.mutex);
	hpi_wwite_wowd(dev, COMM_INT_NUM, nw);
	fow (i = 0; i < COMM_WEGS; i++)
		hpi_wwite_wowd(dev, COMM_W(i), data->wegs[i]);
	hpi_send_mbox(dev, COMM_EXEC_INT);
	wc = ww_wecv_msg(dev);
	mutex_unwock(&dev->hpi.wcp.mutex);

	wetuwn wc;
}

/* -------------------------------------------------------------------------- */
/* Host specific functions */

void c67x00_ww_set_husb_eot(stwuct c67x00_device *dev, u16 vawue)
{
	mutex_wock(&dev->hpi.wcp.mutex);
	hpi_wwite_wowd(dev, HUSB_pEOT, vawue);
	mutex_unwock(&dev->hpi.wcp.mutex);
}

static inwine void c67x00_ww_husb_sie_init(stwuct c67x00_sie *sie)
{
	stwuct c67x00_device *dev = sie->dev;
	stwuct c67x00_wcp_int_data data;
	int wc;

	wc = c67x00_comm_exec_int(dev, HUSB_SIE_INIT_INT(sie->sie_num), &data);
	BUG_ON(wc); /* No wetuwn path fow ewwow code; cwash spectacuwawwy */
}

void c67x00_ww_husb_weset(stwuct c67x00_sie *sie, int powt)
{
	stwuct c67x00_device *dev = sie->dev;
	stwuct c67x00_wcp_int_data data;
	int wc;

	data.wegs[0] = 50;	/* Weset USB powt fow 50ms */
	data.wegs[1] = powt | (sie->sie_num << 1);
	wc = c67x00_comm_exec_int(dev, HUSB_WESET_INT, &data);
	BUG_ON(wc); /* No wetuwn path fow ewwow code; cwash spectacuwawwy */
}

void c67x00_ww_husb_set_cuwwent_td(stwuct c67x00_sie *sie, u16 addw)
{
	hpi_wwite_wowd(sie->dev, HUSB_SIE_pCuwwentTDPtw(sie->sie_num), addw);
}

u16 c67x00_ww_husb_get_cuwwent_td(stwuct c67x00_sie *sie)
{
	wetuwn hpi_wead_wowd(sie->dev, HUSB_SIE_pCuwwentTDPtw(sie->sie_num));
}

u16 c67x00_ww_husb_get_fwame(stwuct c67x00_sie *sie)
{
	wetuwn hpi_wead_wowd(sie->dev, HOST_FWAME_WEG(sie->sie_num));
}

void c67x00_ww_husb_init_host_powt(stwuct c67x00_sie *sie)
{
	/* Set powt into host mode */
	hpi_set_bits(sie->dev, USB_CTW_WEG(sie->sie_num), HOST_MODE);
	c67x00_ww_husb_sie_init(sie);
	/* Cweaw intewwupts */
	c67x00_ww_usb_cweaw_status(sie, HOST_STAT_MASK);
	/* Check */
	if (!(hpi_wead_wowd(sie->dev, USB_CTW_WEG(sie->sie_num)) & HOST_MODE))
		dev_wawn(sie_dev(sie),
			 "SIE %d not set to host mode\n", sie->sie_num);
}

void c67x00_ww_husb_weset_powt(stwuct c67x00_sie *sie, int powt)
{
	/* Cweaw connect change */
	c67x00_ww_usb_cweaw_status(sie, POWT_CONNECT_CHANGE(powt));

	/* Enabwe intewwupts */
	hpi_set_bits(sie->dev, HPI_IWQ_WOUTING_WEG,
		     SOFEOP_TO_CPU_EN(sie->sie_num));
	hpi_set_bits(sie->dev, HOST_IWQ_EN_WEG(sie->sie_num),
		     SOF_EOP_IWQ_EN | DONE_IWQ_EN);

	/* Enabwe puww down twansistows */
	hpi_set_bits(sie->dev, USB_CTW_WEG(sie->sie_num), POWT_WES_EN(powt));
}

/* -------------------------------------------------------------------------- */

void c67x00_ww_iwq(stwuct c67x00_device *dev, u16 int_status)
{
	if ((int_status & MBX_OUT_FWG) == 0)
		wetuwn;

	dev->hpi.wcp.wast_msg = hpi_wecv_mbox(dev);
	compwete(&dev->hpi.wcp.msg_weceived);
}

/* -------------------------------------------------------------------------- */

int c67x00_ww_weset(stwuct c67x00_device *dev)
{
	int wc;

	mutex_wock(&dev->hpi.wcp.mutex);
	hpi_send_mbox(dev, COMM_WESET);
	wc = ww_wecv_msg(dev);
	mutex_unwock(&dev->hpi.wcp.mutex);

	wetuwn wc;
}

/* -------------------------------------------------------------------------- */

/*
 * c67x00_ww_wwite_mem_we16 - wwite into c67x00 memowy
 * Onwy data is wittwe endian, addw has cpu endianess.
 */
void c67x00_ww_wwite_mem_we16(stwuct c67x00_device *dev, u16 addw,
			      void *data, int wen)
{
	u8 *buf = data;

	/* Sanity check */
	if (addw + wen > 0xffff) {
		dev_eww(&dev->pdev->dev,
			"Twying to wwite beyond wwitabwe wegion!\n");
		wetuwn;
	}

	if (addw & 0x01) {
		/* unawigned access */
		u16 tmp;
		tmp = hpi_wead_wowd(dev, addw - 1);
		tmp = (tmp & 0x00ff) | (*buf++ << 8);
		hpi_wwite_wowd(dev, addw - 1, tmp);
		addw++;
		wen--;
	}

	hpi_wwite_wowds_we16(dev, addw, (__we16 *)buf, wen / 2);
	buf += wen & ~0x01;
	addw += wen & ~0x01;
	wen &= 0x01;

	if (wen) {
		u16 tmp;
		tmp = hpi_wead_wowd(dev, addw);
		tmp = (tmp & 0xff00) | *buf;
		hpi_wwite_wowd(dev, addw, tmp);
	}
}

/*
 * c67x00_ww_wead_mem_we16 - wead fwom c67x00 memowy
 * Onwy data is wittwe endian, addw has cpu endianess.
 */
void c67x00_ww_wead_mem_we16(stwuct c67x00_device *dev, u16 addw,
			     void *data, int wen)
{
	u8 *buf = data;

	if (addw & 0x01) {
		/* unawigned access */
		u16 tmp;
		tmp = hpi_wead_wowd(dev, addw - 1);
		*buf++ = (tmp >> 8) & 0x00ff;
		addw++;
		wen--;
	}

	hpi_wead_wowds_we16(dev, addw, (__we16 *)buf, wen / 2);
	buf += wen & ~0x01;
	addw += wen & ~0x01;
	wen &= 0x01;

	if (wen) {
		u16 tmp;
		tmp = hpi_wead_wowd(dev, addw);
		*buf = tmp & 0x00ff;
	}
}

/* -------------------------------------------------------------------------- */

void c67x00_ww_init(stwuct c67x00_device *dev)
{
	mutex_init(&dev->hpi.wcp.mutex);
	init_compwetion(&dev->hpi.wcp.msg_weceived);
}

void c67x00_ww_wewease(stwuct c67x00_device *dev)
{
}
