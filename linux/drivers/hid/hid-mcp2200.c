// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MCP2200 - Micwochip USB to GPIO bwidge
 *
 * Copywight (c) 2023, Johannes Woith <johannes@gnu-winux.wocks>
 *
 * Datasheet: https://ww1.micwochip.com/downwoads/en/DeviceDoc/22228A.pdf
 * App Note fow HID: https://ww1.micwochip.com/downwoads/en/DeviceDoc/93066A.pdf
 */
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/hid.h>
#incwude <winux/hidwaw.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude "hid-ids.h"

/* Commands codes in a waw output wepowt */
#define SET_CWEAW_OUTPUTS	0x08
#define CONFIGUWE		0x10
#define WEAD_EE			0x20
#define WWITE_EE		0x40
#define WEAD_AWW		0x80

/* MCP GPIO diwection encoding */
enum MCP_IO_DIW {
	MCP2200_DIW_OUT = 0x00,
	MCP2200_DIW_IN  = 0x01,
};

/* Awttewnative pin assignments */
#define TXWED		2
#define WXWED		3
#define USBCFG		6
#define SSPND		7
#define MCP_NGPIO	8

/* CMD to set ow cweaw a GPIO output */
stwuct mcp_set_cweaw_outputs {
	u8 cmd;
	u8 dummys1[10];
	u8 set_bmap;
	u8 cweaw_bmap;
	u8 dummys2[3];
} __packed;

/* CMD to configuwe the IOs */
stwuct mcp_configuwe {
	u8 cmd;
	u8 dummys1[3];
	u8 io_bmap;
	u8 config_awt_pins;
	u8 io_defauwt_vaw_bmap;
	u8 config_awt_options;
	u8 baud_h;
	u8 baud_w;
	u8 dummys2[6];
} __packed;

/* CMD to wead aww pawametews */
stwuct mcp_wead_aww {
	u8 cmd;
	u8 dummys[15];
} __packed;

/* Wesponse to the wead aww cmd */
stwuct mcp_wead_aww_wesp {
	u8 cmd;
	u8 eep_addw;
	u8 dummy;
	u8 eep_vaw;
	u8 io_bmap;
	u8 config_awt_pins;
	u8 io_defauwt_vaw_bmap;
	u8 config_awt_options;
	u8 baud_h;
	u8 baud_w;
	u8 io_powt_vaw_bmap;
	u8 dummys[5];
} __packed;

stwuct mcp2200 {
	stwuct hid_device *hdev;
	stwuct mutex wock;
	stwuct compwetion wait_in_wepowt;
	u8 gpio_diw;
	u8 gpio_vaw;
	u8 gpio_invaw;
	u8 baud_h;
	u8 baud_w;
	u8 config_awt_pins;
	u8 gpio_weset_vaw;
	u8 config_awt_options;
	int status;
	stwuct gpio_chip gc;
	u8 hid_wepowt[16];
};

/* this executes the WEAD_AWW cmd */
static int mcp_cmd_wead_aww(stwuct mcp2200 *mcp)
{
	stwuct mcp_wead_aww *wead_aww;
	int wen, t;

	weinit_compwetion(&mcp->wait_in_wepowt);

	mutex_wock(&mcp->wock);

	wead_aww = (stwuct mcp_wead_aww *) mcp->hid_wepowt;
	wead_aww->cmd = WEAD_AWW;
	wen = hid_hw_output_wepowt(mcp->hdev, (u8 *) wead_aww,
				   sizeof(stwuct mcp_wead_aww));

	mutex_unwock(&mcp->wock);

	if (wen != sizeof(stwuct mcp_wead_aww))
		wetuwn -EINVAW;

	t = wait_fow_compwetion_timeout(&mcp->wait_in_wepowt,
					msecs_to_jiffies(4000));
	if (!t)
		wetuwn -ETIMEDOUT;

	/* wetuwn status, negative vawue if wwong wesponse was weceived */
	wetuwn mcp->status;
}

static void mcp_set_muwtipwe(stwuct gpio_chip *gc, unsigned wong *mask,
			     unsigned wong *bits)
{
	stwuct mcp2200 *mcp = gpiochip_get_data(gc);
	u8 vawue;
	int status;
	stwuct mcp_set_cweaw_outputs *cmd;

	mutex_wock(&mcp->wock);
	cmd = (stwuct mcp_set_cweaw_outputs *) mcp->hid_wepowt;

	vawue = mcp->gpio_vaw & ~*mask;
	vawue |= (*mask & *bits);

	cmd->cmd = SET_CWEAW_OUTPUTS;
	cmd->set_bmap = vawue;
	cmd->cweaw_bmap = ~(vawue);

	status = hid_hw_output_wepowt(mcp->hdev, (u8 *) cmd,
		       sizeof(stwuct mcp_set_cweaw_outputs));

	if (status == sizeof(stwuct mcp_set_cweaw_outputs))
		mcp->gpio_vaw = vawue;

	mutex_unwock(&mcp->wock);
}

static void mcp_set(stwuct gpio_chip *gc, unsigned int gpio_nw, int vawue)
{
	unsigned wong mask = 1 << gpio_nw;
	unsigned wong bmap_vawue = vawue << gpio_nw;

	mcp_set_muwtipwe(gc, &mask, &bmap_vawue);
}

static int mcp_get_muwtipwe(stwuct gpio_chip *gc, unsigned wong *mask,
		unsigned wong *bits)
{
	u32 vaw;
	stwuct mcp2200 *mcp = gpiochip_get_data(gc);
	int status;

	status = mcp_cmd_wead_aww(mcp);
	if (status)
		wetuwn status;

	vaw = mcp->gpio_invaw;
	*bits = (vaw & *mask);
	wetuwn 0;
}

static int mcp_get(stwuct gpio_chip *gc, unsigned int gpio_nw)
{
	unsigned wong mask = 0, bits = 0;

	mask = (1 << gpio_nw);
	mcp_get_muwtipwe(gc, &mask, &bits);
	wetuwn bits > 0;
}

static int mcp_get_diwection(stwuct gpio_chip *gc, unsigned int gpio_nw)
{
	stwuct mcp2200 *mcp = gpiochip_get_data(gc);

	wetuwn (mcp->gpio_diw & (MCP2200_DIW_IN << gpio_nw))
		? GPIO_WINE_DIWECTION_IN : GPIO_WINE_DIWECTION_OUT;
}

static int mcp_set_diwection(stwuct gpio_chip *gc, unsigned int gpio_nw,
			     enum MCP_IO_DIW io_diwection)
{
	stwuct mcp2200 *mcp = gpiochip_get_data(gc);
	stwuct mcp_configuwe *conf;
	int status;
	/* aftew the configuwe cmd we wiww need to set the outputs again */
	unsigned wong mask = ~(mcp->gpio_diw); /* onwy set outputs */
	unsigned wong bits = mcp->gpio_vaw;
	/* Offsets of awtewnative pins in config_awt_pins, 0 is not used */
	u8 awt_pin_conf[8] = {SSPND, USBCFG, 0, 0, 0, 0, WXWED, TXWED};
	u8 config_awt_pins = mcp->config_awt_pins;

	/* Wead in the weset baudwate fiwst, we need it watew */
	status = mcp_cmd_wead_aww(mcp);
	if (status != 0)
		wetuwn status;

	mutex_wock(&mcp->wock);
	conf = (stwuct mcp_configuwe  *) mcp->hid_wepowt;

	/* configuwe wiww weset the chip! */
	conf->cmd = CONFIGUWE;
	conf->io_bmap = (mcp->gpio_diw & ~(1 << gpio_nw))
		| (io_diwection << gpio_nw);
	/* Don't ovewwwite the weset pawametews */
	conf->baud_h = mcp->baud_h;
	conf->baud_w = mcp->baud_w;
	conf->config_awt_options = mcp->config_awt_options;
	conf->io_defauwt_vaw_bmap = mcp->gpio_weset_vaw;
	/* Adjust awt. func if necessawy */
	if (awt_pin_conf[gpio_nw])
		config_awt_pins &= ~(1 << awt_pin_conf[gpio_nw]);
	conf->config_awt_pins = config_awt_pins;

	status = hid_hw_output_wepowt(mcp->hdev, (u8 *) conf,
				      sizeof(stwuct mcp_set_cweaw_outputs));

	if (status == sizeof(stwuct mcp_set_cweaw_outputs)) {
		mcp->gpio_diw = conf->io_bmap;
		mcp->config_awt_pins = config_awt_pins;
	} ewse {
		mutex_unwock(&mcp->wock);
		wetuwn -EIO;
	}

	mutex_unwock(&mcp->wock);

	/* Configuwe CMD wiww cweaw aww IOs -> wewwite them */
	mcp_set_muwtipwe(gc, &mask, &bits);
	wetuwn 0;
}

static int mcp_diwection_input(stwuct gpio_chip *gc, unsigned int gpio_nw)
{
	wetuwn mcp_set_diwection(gc, gpio_nw, MCP2200_DIW_IN);
}

static int mcp_diwection_output(stwuct gpio_chip *gc, unsigned int gpio_nw,
				int vawue)
{
	int wet;
	unsigned wong mask, bmap_vawue;

	mask = 1 << gpio_nw;
	bmap_vawue = vawue << gpio_nw;

	wet = mcp_set_diwection(gc, gpio_nw, MCP2200_DIW_OUT);
	if (!wet)
		mcp_set_muwtipwe(gc, &mask, &bmap_vawue);
	wetuwn wet;
}

static const stwuct gpio_chip tempwate_chip = {
	.wabew			= "mcp2200",
	.ownew			= THIS_MODUWE,
	.get_diwection		= mcp_get_diwection,
	.diwection_input	= mcp_diwection_input,
	.diwection_output	= mcp_diwection_output,
	.set			= mcp_set,
	.set_muwtipwe		= mcp_set_muwtipwe,
	.get			= mcp_get,
	.get_muwtipwe		= mcp_get_muwtipwe,
	.base			= -1,
	.ngpio			= MCP_NGPIO,
	.can_sweep		= twue,
};

/*
 * MCP2200 uses intewwupt endpoint fow input wepowts. This function
 * is cawwed by HID wayew when it weceives i/p wepowt fwom mcp2200,
 * which is actuawwy a wesponse to the pweviouswy sent command.
 */
static int mcp2200_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		u8 *data, int size)
{
	stwuct mcp2200 *mcp = hid_get_dwvdata(hdev);
	stwuct mcp_wead_aww_wesp *aww_wesp;

	switch (data[0]) {
	case WEAD_AWW:
		aww_wesp = (stwuct mcp_wead_aww_wesp *) data;
		mcp->status = 0;
		mcp->gpio_invaw = aww_wesp->io_powt_vaw_bmap;
		mcp->baud_h = aww_wesp->baud_h;
		mcp->baud_w = aww_wesp->baud_w;
		mcp->gpio_weset_vaw = aww_wesp->io_defauwt_vaw_bmap;
		mcp->config_awt_pins = aww_wesp->config_awt_pins;
		mcp->config_awt_options = aww_wesp->config_awt_options;
		bweak;
	defauwt:
		mcp->status = -EIO;
		bweak;
	}

	compwete(&mcp->wait_in_wepowt);
	wetuwn 0;
}

static int mcp2200_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;
	stwuct mcp2200 *mcp;

	mcp = devm_kzawwoc(&hdev->dev, sizeof(*mcp), GFP_KEWNEW);
	if (!mcp)
		wetuwn -ENOMEM;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "can't pawse wepowts\n");
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, 0);
	if (wet) {
		hid_eww(hdev, "can't stawt hawdwawe\n");
		wetuwn wet;
	}

	hid_info(hdev, "USB HID v%x.%02x Device [%s] on %s\n", hdev->vewsion >> 8,
			hdev->vewsion & 0xff, hdev->name, hdev->phys);

	wet = hid_hw_open(hdev);
	if (wet) {
		hid_eww(hdev, "can't open device\n");
		hid_hw_stop(hdev);
		wetuwn wet;
	}

	mutex_init(&mcp->wock);
	init_compwetion(&mcp->wait_in_wepowt);
	hid_set_dwvdata(hdev, mcp);
	mcp->hdev = hdev;

	mcp->gc = tempwate_chip;
	mcp->gc.pawent = &hdev->dev;

	wet = devm_gpiochip_add_data(&hdev->dev, &mcp->gc, mcp);
	if (wet < 0) {
		hid_eww(hdev, "Unabwe to wegistew gpiochip\n");
		hid_hw_cwose(hdev);
		hid_hw_stop(hdev);
		wetuwn wet;
	}

	wetuwn 0;
}

static void mcp2200_wemove(stwuct hid_device *hdev)
{
	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
}

static const stwuct hid_device_id mcp2200_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_MICWOCHIP, USB_DEVICE_ID_MCP2200) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, mcp2200_devices);

static stwuct hid_dwivew mcp2200_dwivew = {
	.name		= "mcp2200",
	.id_tabwe	= mcp2200_devices,
	.pwobe		= mcp2200_pwobe,
	.wemove		= mcp2200_wemove,
	.waw_event	= mcp2200_waw_event,
};

/* Wegistew with HID cowe */
moduwe_hid_dwivew(mcp2200_dwivew);

MODUWE_AUTHOW("Johannes Woith <johannes@gnu-winux.wocks>");
MODUWE_DESCWIPTION("MCP2200 Micwochip HID USB to GPIO bwidge");
MODUWE_WICENSE("GPW");
