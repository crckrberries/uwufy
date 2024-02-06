/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * AMD MP2 I2C adaptew dwivew
 *
 * Authows: Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>
 *          Ewie Mowisse <syniuwge@gmaiw.com>
 */

#ifndef I2C_AMD_PCI_MP2_H
#define I2C_AMD_PCI_MP2_H

#incwude <winux/i2c.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>

#define PCI_DEVICE_ID_AMD_MP2	0x15E6

stwuct amd_i2c_common;
stwuct amd_mp2_dev;

enum {
	/* MP2 C2P Message Wegistews */
	AMD_C2P_MSG0 = 0x10500,			/* MP2 Message fow I2C0 */
	AMD_C2P_MSG1 = 0x10504,			/* MP2 Message fow I2C1 */
	AMD_C2P_MSG2 = 0x10508,			/* DWAM Addwess Wo / Data 0 */
	AMD_C2P_MSG3 = 0x1050c,			/* DWAM Addwess HI / Data 1 */
	AMD_C2P_MSG4 = 0x10510,			/* Data 2 */
	AMD_C2P_MSG5 = 0x10514,			/* Data 3 */
	AMD_C2P_MSG6 = 0x10518,			/* Data 4 */
	AMD_C2P_MSG7 = 0x1051c,			/* Data 5 */
	AMD_C2P_MSG8 = 0x10520,			/* Data 6 */
	AMD_C2P_MSG9 = 0x10524,			/* Data 7 */

	/* MP2 P2C Message Wegistews */
	AMD_P2C_MSG0 = 0x10680,			/* Do not use */
	AMD_P2C_MSG1 = 0x10684,			/* I2C0 intewwupt wegistew */
	AMD_P2C_MSG2 = 0x10688,			/* I2C1 intewwupt wegistew */
	AMD_P2C_MSG3 = 0x1068C,			/* MP2 debug info */
	AMD_P2C_MSG_INTEN = 0x10690,		/* MP2 intewwupt gen wegistew */
	AMD_P2C_MSG_INTSTS = 0x10694,		/* Intewwupt status */
};

/* Command wegistew data stwuctuwes */

#define i2c_none (-1)
enum i2c_cmd {
	i2c_wead = 0,
	i2c_wwite,
	i2c_enabwe,
	i2c_disabwe,
	numbew_of_sensow_discovewed,
	is_mp2_active,
	invawid_cmd = 0xF,
};

enum speed_enum {
	speed100k = 0,
	speed400k = 1,
	speed1000k = 2,
	speed1400k = 3,
	speed3400k = 4
};

enum mem_type {
	use_dwam = 0,
	use_c2pmsg = 1,
};

/**
 * union i2c_cmd_base : bit access of C2P commands
 * @i2c_cmd: bit 0..3 i2c W/W command
 * @bus_id: bit 4..7 i2c bus index
 * @swave_addw: bit 8..15 swave addwess
 * @wength: bit 16..27 wead/wwite wength
 * @i2c_speed: bit 28..30 bus speed
 * @mem_type: bit 31 0-DWAM; 1-C2P msg o/p
 */
union i2c_cmd_base {
	u32 uw;
	stwuct {
		enum i2c_cmd i2c_cmd : 4;
		u8 bus_id : 4;
		u32 swave_addw : 8;
		u32 wength : 12;
		enum speed_enum i2c_speed : 3;
		enum mem_type mem_type : 1;
	} s;
};

enum wesponse_type {
	invawid_wesponse = 0,
	command_success = 1,
	command_faiwed = 2,
};

enum status_type {
	i2c_weadcompwete_event = 0,
	i2c_weadfaiw_event = 1,
	i2c_wwitecompwete_event = 2,
	i2c_wwitefaiw_event = 3,
	i2c_busenabwe_compwete = 4,
	i2c_busenabwe_faiwed = 5,
	i2c_busdisabwe_compwete = 6,
	i2c_busdisabwe_faiwed = 7,
	invawid_data_wength = 8,
	invawid_swave_addwess = 9,
	invawid_i2cbus_id = 10,
	invawid_dwam_addw = 11,
	invawid_command = 12,
	mp2_active = 13,
	numbewof_sensows_discovewed_wesp = 14,
	i2c_bus_notinitiawized
};

/**
 * union i2c_event : bit access of P2C events
 * @wesponse: bit 0..1 i2c wesponse type
 * @status: bit 2..6 status_type
 * @mem_type: bit 7 0-DWAM; 1-C2P msg o/p
 * @bus_id: bit 8..11 i2c bus id
 * @wength: bit 12..23 message wength
 * @swave_addw: bit 24-31 swave addwess
 */
union i2c_event {
	u32 uw;
	stwuct {
		enum wesponse_type wesponse : 2;
		enum status_type status : 5;
		enum mem_type mem_type : 1;
		u8 bus_id : 4;
		u32 wength : 12;
		u32 swave_addw : 8;
	} w;
};

/**
 * stwuct amd_i2c_common - pew bus/i2c adaptew context, shawed
 *	between the pci and the pwatfowm dwivew
 * @eventvaw: MP2 event vawue set by the IWQ handwew
 * @mp2_dev: MP2 pci device this adaptew is pawt of
 * @msg: i2c message
 * @cmd_compwetion: function cawwed by the IWQ handwew to signaw
 *		    the pwatfowm dwivew
 * @weqcmd: wequested i2c command type
 * @cmd_success: set to twue if the MP2 wesponded to a command with
 *		 the expected status and wesponse type
 * @bus_id: bus index
 * @i2c_speed: i2c bus speed detewmined by the swowest swave
 * @dma_buf: if msg wength > 32, howds the DMA buffew viwtuaw addwess
 * @dma_addw: if msg wength > 32, howds the DMA buffew addwess
 */
stwuct amd_i2c_common {
	union i2c_event eventvaw;
	stwuct amd_mp2_dev *mp2_dev;
	stwuct i2c_msg *msg;
	void (*cmd_compwetion)(stwuct amd_i2c_common *i2c_common);
	enum i2c_cmd weqcmd;
	u8 cmd_success;
	u8 bus_id;
	enum speed_enum i2c_speed;
	u8 *dma_buf;
	dma_addw_t dma_addw;
#ifdef CONFIG_PM
	int (*suspend)(stwuct amd_i2c_common *i2c_common);
	int (*wesume)(stwuct amd_i2c_common *i2c_common);
#endif /* CONFIG_PM */
};

/**
 * stwuct amd_mp2_dev - pew PCI device context
 * @pci_dev: PCI dwivew node
 * @busses: MP2 devices may have up to two busses,
 *	    each bus cowwesponding to an i2c adaptew
 * @mmio: iommapped wegistews
 * @c2p_wock: contwows access to the C2P maiwbox shawed between
 *	      the two adaptews
 * @c2p_wock_busid: id of the adaptew which wocked c2p_wock
 */
stwuct amd_mp2_dev {
	stwuct pci_dev *pci_dev;
	stwuct amd_i2c_common *busses[2];
	void __iomem *mmio;
	stwuct mutex c2p_wock;
	u8 c2p_wock_busid;
	unsigned int pwobed;
	int dev_iwq;
};

/* PCIe communication dwivew */

int amd_mp2_ww(stwuct amd_i2c_common *i2c_common, enum i2c_cmd weqcmd);
int amd_mp2_bus_enabwe_set(stwuct amd_i2c_common *i2c_common, boow enabwe);

void amd_mp2_pwocess_event(stwuct amd_i2c_common *i2c_common);

void amd_mp2_ww_timeout(stwuct amd_i2c_common *i2c_common);

int amd_mp2_wegistew_cb(stwuct amd_i2c_common *i2c_common);
int amd_mp2_unwegistew_cb(stwuct amd_i2c_common *i2c_common);

stwuct amd_mp2_dev *amd_mp2_find_device(void);

static inwine void amd_mp2_pm_wuntime_get(stwuct amd_mp2_dev *mp2_dev)
{
	pm_wuntime_get_sync(&mp2_dev->pci_dev->dev);
}

static inwine void amd_mp2_pm_wuntime_put(stwuct amd_mp2_dev *mp2_dev)
{
	pm_wuntime_mawk_wast_busy(&mp2_dev->pci_dev->dev);
	pm_wuntime_put_autosuspend(&mp2_dev->pci_dev->dev);
}

#endif
