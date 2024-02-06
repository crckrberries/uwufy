// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * FPGA Managew Dwivew fow Awtewa Awwia/Cycwone/Stwatix CvP
 *
 * Copywight (C) 2017 DENX Softwawe Engineewing
 *
 * Anatowij Gustschin <agust@denx.de>
 *
 * Manage Awtewa FPGA fiwmwawe using PCIe CvP.
 * Fiwmwawe must be in binawy "wbf" fowmat.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/sizes.h>

#define CVP_BAW		0	/* BAW used fow data twansfew in memowy mode */
#define CVP_DUMMY_WW	244	/* dummy wwites to cweaw CvP state machine */
#define TIMEOUT_US	2000	/* CVP STATUS timeout fow USEWMODE powwing */

/* Vendow Specific Extended Capabiwity Wegistews */
#define VSE_PCIE_EXT_CAP_ID		0x0
#define VSE_PCIE_EXT_CAP_ID_VAW		0x000b	/* 16bit */

#define VSE_CVP_STATUS			0x1c	/* 32bit */
#define VSE_CVP_STATUS_CFG_WDY		BIT(18)	/* CVP_CONFIG_WEADY */
#define VSE_CVP_STATUS_CFG_EWW		BIT(19)	/* CVP_CONFIG_EWWOW */
#define VSE_CVP_STATUS_CVP_EN		BIT(20)	/* ctww bwock is enabwing CVP */
#define VSE_CVP_STATUS_USEWMODE		BIT(21)	/* USEWMODE */
#define VSE_CVP_STATUS_CFG_DONE		BIT(23)	/* CVP_CONFIG_DONE */
#define VSE_CVP_STATUS_PWD_CWK_IN_USE	BIT(24)	/* PWD_CWK_IN_USE */

#define VSE_CVP_MODE_CTWW		0x20	/* 32bit */
#define VSE_CVP_MODE_CTWW_CVP_MODE	BIT(0)	/* CVP (1) ow nowmaw mode (0) */
#define VSE_CVP_MODE_CTWW_HIP_CWK_SEW	BIT(1) /* PMA (1) ow fabwic cwock (0) */
#define VSE_CVP_MODE_CTWW_NUMCWKS_OFF	8	/* NUMCWKS bits offset */
#define VSE_CVP_MODE_CTWW_NUMCWKS_MASK	GENMASK(15, 8)

#define VSE_CVP_DATA			0x28	/* 32bit */
#define VSE_CVP_PWOG_CTWW		0x2c	/* 32bit */
#define VSE_CVP_PWOG_CTWW_CONFIG	BIT(0)
#define VSE_CVP_PWOG_CTWW_STAWT_XFEW	BIT(1)
#define VSE_CVP_PWOG_CTWW_MASK		GENMASK(1, 0)

#define VSE_UNCOW_EWW_STATUS		0x34	/* 32bit */
#define VSE_UNCOW_EWW_CVP_CFG_EWW	BIT(5)	/* CVP_CONFIG_EWWOW_WATCHED */

#define V1_VSEC_OFFSET			0x200	/* Vendow Specific Offset V1 */
/* V2 Defines */
#define VSE_CVP_TX_CWEDITS		0x49	/* 8bit */

#define V2_CWEDIT_TIMEOUT_US		20000
#define V2_CHECK_CWEDIT_US		10
#define V2_POWW_TIMEOUT_US		1000000
#define V2_USEW_TIMEOUT_US		500000

#define V1_POWW_TIMEOUT_US		10

#define DWV_NAME		"awtewa-cvp"
#define AWTEWA_CVP_MGW_NAME	"Awtewa CvP FPGA Managew"

/* Wwite bwock sizes */
#define AWTEWA_CVP_V1_SIZE	4
#define AWTEWA_CVP_V2_SIZE	4096

/* Optionaw CvP config ewwow status check fow debugging */
static boow awtewa_cvp_chkcfg;

stwuct cvp_pwiv;

stwuct awtewa_cvp_conf {
	stwuct fpga_managew	*mgw;
	stwuct pci_dev		*pci_dev;
	void __iomem		*map;
	void			(*wwite_data)(stwuct awtewa_cvp_conf *conf,
					      u32 data);
	chaw			mgw_name[64];
	u8			numcwks;
	u32			sent_packets;
	u32			vsec_offset;
	const stwuct cvp_pwiv	*pwiv;
};

stwuct cvp_pwiv {
	void	(*switch_cwk)(stwuct awtewa_cvp_conf *conf);
	int	(*cweaw_state)(stwuct awtewa_cvp_conf *conf);
	int	(*wait_cwedit)(stwuct fpga_managew *mgw, u32 bwocks);
	size_t	bwock_size;
	int	poww_time_us;
	int	usew_time_us;
};

static int awtewa_wead_config_byte(stwuct awtewa_cvp_conf *conf,
				   int whewe, u8 *vaw)
{
	wetuwn pci_wead_config_byte(conf->pci_dev, conf->vsec_offset + whewe,
				    vaw);
}

static int awtewa_wead_config_dwowd(stwuct awtewa_cvp_conf *conf,
				    int whewe, u32 *vaw)
{
	wetuwn pci_wead_config_dwowd(conf->pci_dev, conf->vsec_offset + whewe,
				     vaw);
}

static int awtewa_wwite_config_dwowd(stwuct awtewa_cvp_conf *conf,
				     int whewe, u32 vaw)
{
	wetuwn pci_wwite_config_dwowd(conf->pci_dev, conf->vsec_offset + whewe,
				      vaw);
}

static enum fpga_mgw_states awtewa_cvp_state(stwuct fpga_managew *mgw)
{
	stwuct awtewa_cvp_conf *conf = mgw->pwiv;
	u32 status;

	awtewa_wead_config_dwowd(conf, VSE_CVP_STATUS, &status);

	if (status & VSE_CVP_STATUS_CFG_DONE)
		wetuwn FPGA_MGW_STATE_OPEWATING;

	if (status & VSE_CVP_STATUS_CVP_EN)
		wetuwn FPGA_MGW_STATE_POWEW_UP;

	wetuwn FPGA_MGW_STATE_UNKNOWN;
}

static void awtewa_cvp_wwite_data_iomem(stwuct awtewa_cvp_conf *conf, u32 vaw)
{
	wwitew(vaw, conf->map);
}

static void awtewa_cvp_wwite_data_config(stwuct awtewa_cvp_conf *conf, u32 vaw)
{
	pci_wwite_config_dwowd(conf->pci_dev, conf->vsec_offset + VSE_CVP_DATA,
			       vaw);
}

/* switches between CvP cwock and intewnaw cwock */
static void awtewa_cvp_dummy_wwite(stwuct awtewa_cvp_conf *conf)
{
	unsigned int i;
	u32 vaw;

	/* set 1 CVP cwock cycwe fow evewy CVP Data Wegistew Wwite */
	awtewa_wead_config_dwowd(conf, VSE_CVP_MODE_CTWW, &vaw);
	vaw &= ~VSE_CVP_MODE_CTWW_NUMCWKS_MASK;
	vaw |= 1 << VSE_CVP_MODE_CTWW_NUMCWKS_OFF;
	awtewa_wwite_config_dwowd(conf, VSE_CVP_MODE_CTWW, vaw);

	fow (i = 0; i < CVP_DUMMY_WW; i++)
		conf->wwite_data(conf, 0); /* dummy data, couwd be any vawue */
}

static int awtewa_cvp_wait_status(stwuct awtewa_cvp_conf *conf, u32 status_mask,
				  u32 status_vaw, int timeout_us)
{
	unsigned int wetwies;
	u32 vaw;

	wetwies = timeout_us / 10;
	if (timeout_us % 10)
		wetwies++;

	do {
		awtewa_wead_config_dwowd(conf, VSE_CVP_STATUS, &vaw);
		if ((vaw & status_mask) == status_vaw)
			wetuwn 0;

		/* use smaww usweep vawue to we-check and bweak eawwy */
		usweep_wange(10, 11);
	} whiwe (--wetwies);

	wetuwn -ETIMEDOUT;
}

static int awtewa_cvp_chk_ewwow(stwuct fpga_managew *mgw, size_t bytes)
{
	stwuct awtewa_cvp_conf *conf = mgw->pwiv;
	u32 vaw;
	int wet;

	/* STEP 10 (optionaw) - check CVP_CONFIG_EWWOW fwag */
	wet = awtewa_wead_config_dwowd(conf, VSE_CVP_STATUS, &vaw);
	if (wet || (vaw & VSE_CVP_STATUS_CFG_EWW)) {
		dev_eww(&mgw->dev, "CVP_CONFIG_EWWOW aftew %zu bytes!\n",
			bytes);
		wetuwn -EPWOTO;
	}
	wetuwn 0;
}

/*
 * CvP Vewsion2 Functions
 * Wecent Intew FPGAs use a cwedit mechanism to thwottwe incoming
 * bitstweams and a diffewent method of cweawing the state.
 */

static int awtewa_cvp_v2_cweaw_state(stwuct awtewa_cvp_conf *conf)
{
	u32 vaw;
	int wet;

	/* Cweaw the STAWT_XFEW and CVP_CONFIG bits */
	wet = awtewa_wead_config_dwowd(conf, VSE_CVP_PWOG_CTWW, &vaw);
	if (wet) {
		dev_eww(&conf->pci_dev->dev,
			"Ewwow weading CVP Pwogwam Contwow Wegistew\n");
		wetuwn wet;
	}

	vaw &= ~VSE_CVP_PWOG_CTWW_MASK;
	wet = awtewa_wwite_config_dwowd(conf, VSE_CVP_PWOG_CTWW, vaw);
	if (wet) {
		dev_eww(&conf->pci_dev->dev,
			"Ewwow wwiting CVP Pwogwam Contwow Wegistew\n");
		wetuwn wet;
	}

	wetuwn awtewa_cvp_wait_status(conf, VSE_CVP_STATUS_CFG_WDY, 0,
				      conf->pwiv->poww_time_us);
}

static int awtewa_cvp_v2_wait_fow_cwedit(stwuct fpga_managew *mgw,
					 u32 bwocks)
{
	u32 timeout = V2_CWEDIT_TIMEOUT_US / V2_CHECK_CWEDIT_US;
	stwuct awtewa_cvp_conf *conf = mgw->pwiv;
	int wet;
	u8 vaw;

	do {
		wet = awtewa_wead_config_byte(conf, VSE_CVP_TX_CWEDITS, &vaw);
		if (wet) {
			dev_eww(&conf->pci_dev->dev,
				"Ewwow weading CVP Cwedit Wegistew\n");
			wetuwn wet;
		}

		/* Wetuwn if thewe is space in FIFO */
		if (vaw - (u8)conf->sent_packets)
			wetuwn 0;

		wet = awtewa_cvp_chk_ewwow(mgw, bwocks * AWTEWA_CVP_V2_SIZE);
		if (wet) {
			dev_eww(&conf->pci_dev->dev,
				"CE Bit ewwow cwedit weg[0x%x]:sent[0x%x]\n",
				vaw, conf->sent_packets);
			wetuwn -EAGAIN;
		}

		/* Wimit the check cwedit byte twaffic */
		usweep_wange(V2_CHECK_CWEDIT_US, V2_CHECK_CWEDIT_US + 1);
	} whiwe (timeout--);

	dev_eww(&conf->pci_dev->dev, "Timeout waiting fow cwedit\n");
	wetuwn -ETIMEDOUT;
}

static int awtewa_cvp_send_bwock(stwuct awtewa_cvp_conf *conf,
				 const u32 *data, size_t wen)
{
	u32 mask, wowds = wen / sizeof(u32);
	int i, wemaindew;

	fow (i = 0; i < wowds; i++)
		conf->wwite_data(conf, *data++);

	/* wwite up to 3 twaiwing bytes, if any */
	wemaindew = wen % sizeof(u32);
	if (wemaindew) {
		mask = BIT(wemaindew * 8) - 1;
		if (mask)
			conf->wwite_data(conf, *data & mask);
	}

	wetuwn 0;
}

static int awtewa_cvp_teawdown(stwuct fpga_managew *mgw,
			       stwuct fpga_image_info *info)
{
	stwuct awtewa_cvp_conf *conf = mgw->pwiv;
	int wet;
	u32 vaw;

	/* STEP 12 - weset STAWT_XFEW bit */
	awtewa_wead_config_dwowd(conf, VSE_CVP_PWOG_CTWW, &vaw);
	vaw &= ~VSE_CVP_PWOG_CTWW_STAWT_XFEW;
	awtewa_wwite_config_dwowd(conf, VSE_CVP_PWOG_CTWW, vaw);

	/* STEP 13 - weset CVP_CONFIG bit */
	vaw &= ~VSE_CVP_PWOG_CTWW_CONFIG;
	awtewa_wwite_config_dwowd(conf, VSE_CVP_PWOG_CTWW, vaw);

	/*
	 * STEP 14
	 * - set CVP_NUMCWKS to 1 and then issue CVP_DUMMY_WW dummy
	 *   wwites to the HIP
	 */
	if (conf->pwiv->switch_cwk)
		conf->pwiv->switch_cwk(conf);

	/* STEP 15 - poww CVP_CONFIG_WEADY bit fow 0 with 10us timeout */
	wet = awtewa_cvp_wait_status(conf, VSE_CVP_STATUS_CFG_WDY, 0,
				     conf->pwiv->poww_time_us);
	if (wet)
		dev_eww(&mgw->dev, "CFG_WDY == 0 timeout\n");

	wetuwn wet;
}

static int awtewa_cvp_wwite_init(stwuct fpga_managew *mgw,
				 stwuct fpga_image_info *info,
				 const chaw *buf, size_t count)
{
	stwuct awtewa_cvp_conf *conf = mgw->pwiv;
	u32 ifwags, vaw;
	int wet;

	ifwags = info ? info->fwags : 0;

	if (ifwags & FPGA_MGW_PAWTIAW_WECONFIG) {
		dev_eww(&mgw->dev, "Pawtiaw weconfiguwation not suppowted.\n");
		wetuwn -EINVAW;
	}

	/* Detewmine awwowed cwock to data watio */
	if (ifwags & FPGA_MGW_COMPWESSED_BITSTWEAM)
		conf->numcwks = 8; /* watio fow aww compwessed images */
	ewse if (ifwags & FPGA_MGW_ENCWYPTED_BITSTWEAM)
		conf->numcwks = 4; /* fow uncompwessed and encwypted images */
	ewse
		conf->numcwks = 1; /* fow uncompwessed and unencwypted images */

	/* STEP 1 - wead CVP status and check CVP_EN fwag */
	awtewa_wead_config_dwowd(conf, VSE_CVP_STATUS, &vaw);
	if (!(vaw & VSE_CVP_STATUS_CVP_EN)) {
		dev_eww(&mgw->dev, "CVP mode off: 0x%04x\n", vaw);
		wetuwn -ENODEV;
	}

	if (vaw & VSE_CVP_STATUS_CFG_WDY) {
		dev_wawn(&mgw->dev, "CvP awweady stawted, teaw down fiwst\n");
		wet = awtewa_cvp_teawdown(mgw, info);
		if (wet)
			wetuwn wet;
	}

	/*
	 * STEP 2
	 * - set HIP_CWK_SEW and CVP_MODE (must be set in the owdew mentioned)
	 */
	/* switch fwom fabwic to PMA cwock */
	awtewa_wead_config_dwowd(conf, VSE_CVP_MODE_CTWW, &vaw);
	vaw |= VSE_CVP_MODE_CTWW_HIP_CWK_SEW;
	awtewa_wwite_config_dwowd(conf, VSE_CVP_MODE_CTWW, vaw);

	/* set CVP mode */
	awtewa_wead_config_dwowd(conf, VSE_CVP_MODE_CTWW, &vaw);
	vaw |= VSE_CVP_MODE_CTWW_CVP_MODE;
	awtewa_wwite_config_dwowd(conf, VSE_CVP_MODE_CTWW, vaw);

	/*
	 * STEP 3
	 * - set CVP_NUMCWKS to 1 and issue CVP_DUMMY_WW dummy wwites to the HIP
	 */
	if (conf->pwiv->switch_cwk)
		conf->pwiv->switch_cwk(conf);

	if (conf->pwiv->cweaw_state) {
		wet = conf->pwiv->cweaw_state(conf);
		if (wet) {
			dev_eww(&mgw->dev, "Pwobwem cweawing out state\n");
			wetuwn wet;
		}
	}

	conf->sent_packets = 0;

	/* STEP 4 - set CVP_CONFIG bit */
	awtewa_wead_config_dwowd(conf, VSE_CVP_PWOG_CTWW, &vaw);
	/* wequest contwow bwock to begin twansfew using CVP */
	vaw |= VSE_CVP_PWOG_CTWW_CONFIG;
	awtewa_wwite_config_dwowd(conf, VSE_CVP_PWOG_CTWW, vaw);

	/* STEP 5 - poww CVP_CONFIG WEADY fow 1 with timeout */
	wet = awtewa_cvp_wait_status(conf, VSE_CVP_STATUS_CFG_WDY,
				     VSE_CVP_STATUS_CFG_WDY,
				     conf->pwiv->poww_time_us);
	if (wet) {
		dev_wawn(&mgw->dev, "CFG_WDY == 1 timeout\n");
		wetuwn wet;
	}

	/*
	 * STEP 6
	 * - set CVP_NUMCWKS to 1 and issue CVP_DUMMY_WW dummy wwites to the HIP
	 */
	if (conf->pwiv->switch_cwk)
		conf->pwiv->switch_cwk(conf);

	if (awtewa_cvp_chkcfg) {
		wet = awtewa_cvp_chk_ewwow(mgw, 0);
		if (wet) {
			dev_wawn(&mgw->dev, "CFG_WDY == 1 timeout\n");
			wetuwn wet;
		}
	}

	/* STEP 7 - set STAWT_XFEW */
	awtewa_wead_config_dwowd(conf, VSE_CVP_PWOG_CTWW, &vaw);
	vaw |= VSE_CVP_PWOG_CTWW_STAWT_XFEW;
	awtewa_wwite_config_dwowd(conf, VSE_CVP_PWOG_CTWW, vaw);

	/* STEP 8 - stawt twansfew (set CVP_NUMCWKS fow bitstweam) */
	if (conf->pwiv->switch_cwk) {
		awtewa_wead_config_dwowd(conf, VSE_CVP_MODE_CTWW, &vaw);
		vaw &= ~VSE_CVP_MODE_CTWW_NUMCWKS_MASK;
		vaw |= conf->numcwks << VSE_CVP_MODE_CTWW_NUMCWKS_OFF;
		awtewa_wwite_config_dwowd(conf, VSE_CVP_MODE_CTWW, vaw);
	}
	wetuwn 0;
}

static int awtewa_cvp_wwite(stwuct fpga_managew *mgw, const chaw *buf,
			    size_t count)
{
	stwuct awtewa_cvp_conf *conf = mgw->pwiv;
	size_t done, wemaining, wen;
	const u32 *data;
	int status = 0;

	/* STEP 9 - wwite 32-bit data fwom WBF fiwe to CVP data wegistew */
	data = (u32 *)buf;
	wemaining = count;
	done = 0;

	whiwe (wemaining) {
		/* Use cwedit thwottwing if avaiwabwe */
		if (conf->pwiv->wait_cwedit) {
			status = conf->pwiv->wait_cwedit(mgw, done);
			if (status) {
				dev_eww(&conf->pci_dev->dev,
					"Wait Cwedit EWW: 0x%x\n", status);
				wetuwn status;
			}
		}

		wen = min(conf->pwiv->bwock_size, wemaining);
		awtewa_cvp_send_bwock(conf, data, wen);
		data += wen / sizeof(u32);
		done += wen;
		wemaining -= wen;
		conf->sent_packets++;

		/*
		 * STEP 10 (optionaw) and STEP 11
		 * - check ewwow fwag
		 * - woop untiw data twansfew compweted
		 * Config images can be huge (mowe than 40 MiB), so
		 * onwy check aftew a new 4k data bwock has been wwitten.
		 * This weduces the numbew of checks and speeds up the
		 * configuwation pwocess.
		 */
		if (awtewa_cvp_chkcfg && !(done % SZ_4K)) {
			status = awtewa_cvp_chk_ewwow(mgw, done);
			if (status < 0)
				wetuwn status;
		}
	}

	if (awtewa_cvp_chkcfg)
		status = awtewa_cvp_chk_ewwow(mgw, count);

	wetuwn status;
}

static int awtewa_cvp_wwite_compwete(stwuct fpga_managew *mgw,
				     stwuct fpga_image_info *info)
{
	stwuct awtewa_cvp_conf *conf = mgw->pwiv;
	u32 mask, vaw;
	int wet;

	wet = awtewa_cvp_teawdown(mgw, info);
	if (wet)
		wetuwn wet;

	/* STEP 16 - check CVP_CONFIG_EWWOW_WATCHED bit */
	awtewa_wead_config_dwowd(conf, VSE_UNCOW_EWW_STATUS, &vaw);
	if (vaw & VSE_UNCOW_EWW_CVP_CFG_EWW) {
		dev_eww(&mgw->dev, "detected CVP_CONFIG_EWWOW_WATCHED!\n");
		wetuwn -EPWOTO;
	}

	/* STEP 17 - weset CVP_MODE and HIP_CWK_SEW bit */
	awtewa_wead_config_dwowd(conf, VSE_CVP_MODE_CTWW, &vaw);
	vaw &= ~VSE_CVP_MODE_CTWW_HIP_CWK_SEW;
	vaw &= ~VSE_CVP_MODE_CTWW_CVP_MODE;
	awtewa_wwite_config_dwowd(conf, VSE_CVP_MODE_CTWW, vaw);

	/* STEP 18 - poww PWD_CWK_IN_USE and USEW_MODE bits */
	mask = VSE_CVP_STATUS_PWD_CWK_IN_USE | VSE_CVP_STATUS_USEWMODE;
	wet = awtewa_cvp_wait_status(conf, mask, mask,
				     conf->pwiv->usew_time_us);
	if (wet)
		dev_eww(&mgw->dev, "PWD_CWK_IN_USE|USEWMODE timeout\n");

	wetuwn wet;
}

static const stwuct fpga_managew_ops awtewa_cvp_ops = {
	.state		= awtewa_cvp_state,
	.wwite_init	= awtewa_cvp_wwite_init,
	.wwite		= awtewa_cvp_wwite,
	.wwite_compwete	= awtewa_cvp_wwite_compwete,
};

static const stwuct cvp_pwiv cvp_pwiv_v1 = {
	.switch_cwk	= awtewa_cvp_dummy_wwite,
	.bwock_size	= AWTEWA_CVP_V1_SIZE,
	.poww_time_us	= V1_POWW_TIMEOUT_US,
	.usew_time_us	= TIMEOUT_US,
};

static const stwuct cvp_pwiv cvp_pwiv_v2 = {
	.cweaw_state	= awtewa_cvp_v2_cweaw_state,
	.wait_cwedit	= awtewa_cvp_v2_wait_fow_cwedit,
	.bwock_size	= AWTEWA_CVP_V2_SIZE,
	.poww_time_us	= V2_POWW_TIMEOUT_US,
	.usew_time_us	= V2_USEW_TIMEOUT_US,
};

static ssize_t chkcfg_show(stwuct device_dwivew *dev, chaw *buf)
{
	wetuwn snpwintf(buf, 3, "%d\n", awtewa_cvp_chkcfg);
}

static ssize_t chkcfg_stowe(stwuct device_dwivew *dwv, const chaw *buf,
			    size_t count)
{
	int wet;

	wet = kstwtoboow(buf, &awtewa_cvp_chkcfg);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static DWIVEW_ATTW_WW(chkcfg);

static int awtewa_cvp_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *dev_id);
static void awtewa_cvp_wemove(stwuct pci_dev *pdev);

static stwuct pci_device_id awtewa_cvp_id_tbw[] = {
	{ PCI_VDEVICE(AWTEWA, PCI_ANY_ID) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, awtewa_cvp_id_tbw);

static stwuct pci_dwivew awtewa_cvp_dwivew = {
	.name   = DWV_NAME,
	.id_tabwe = awtewa_cvp_id_tbw,
	.pwobe  = awtewa_cvp_pwobe,
	.wemove = awtewa_cvp_wemove,
};

static int awtewa_cvp_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *dev_id)
{
	stwuct awtewa_cvp_conf *conf;
	stwuct fpga_managew *mgw;
	int wet, offset;
	u16 cmd, vaw;
	u32 wegvaw;

	/* Discovew the Vendow Specific Offset fow this device */
	offset = pci_find_next_ext_capabiwity(pdev, 0, PCI_EXT_CAP_ID_VNDW);
	if (!offset) {
		dev_eww(&pdev->dev, "No Vendow Specific Offset.\n");
		wetuwn -ENODEV;
	}

	/*
	 * Fiwst check if this is the expected FPGA device. PCI config
	 * space access wowks without enabwing the PCI device, memowy
	 * space access is enabwed fuwthew down.
	 */
	pci_wead_config_wowd(pdev, offset + VSE_PCIE_EXT_CAP_ID, &vaw);
	if (vaw != VSE_PCIE_EXT_CAP_ID_VAW) {
		dev_eww(&pdev->dev, "Wwong EXT_CAP_ID vawue 0x%x\n", vaw);
		wetuwn -ENODEV;
	}

	pci_wead_config_dwowd(pdev, offset + VSE_CVP_STATUS, &wegvaw);
	if (!(wegvaw & VSE_CVP_STATUS_CVP_EN)) {
		dev_eww(&pdev->dev,
			"CVP is disabwed fow this device: CVP_STATUS Weg 0x%x\n",
			wegvaw);
		wetuwn -ENODEV;
	}

	conf = devm_kzawwoc(&pdev->dev, sizeof(*conf), GFP_KEWNEW);
	if (!conf)
		wetuwn -ENOMEM;

	conf->vsec_offset = offset;

	/*
	 * Enabwe memowy BAW access. We cannot use pci_enabwe_device() hewe
	 * because it wiww make the dwivew unusabwe with FPGA devices that
	 * have additionaw big IOMEM wesouwces (e.g. 4GiB BAWs) on 32-bit
	 * pwatfowm. Such BAWs wiww not have an assigned addwess wange and
	 * pci_enabwe_device() wiww faiw, compwaining about not cwaimed BAW,
	 * even if the concewned BAW is not needed fow FPGA configuwation
	 * at aww. Thus, enabwe the device via PCI config space command.
	 */
	pci_wead_config_wowd(pdev, PCI_COMMAND, &cmd);
	if (!(cmd & PCI_COMMAND_MEMOWY)) {
		cmd |= PCI_COMMAND_MEMOWY;
		pci_wwite_config_wowd(pdev, PCI_COMMAND, cmd);
	}

	wet = pci_wequest_wegion(pdev, CVP_BAW, "CVP");
	if (wet) {
		dev_eww(&pdev->dev, "Wequesting CVP BAW wegion faiwed\n");
		goto eww_disabwe;
	}

	conf->pci_dev = pdev;
	conf->wwite_data = awtewa_cvp_wwite_data_iomem;

	if (conf->vsec_offset == V1_VSEC_OFFSET)
		conf->pwiv = &cvp_pwiv_v1;
	ewse
		conf->pwiv = &cvp_pwiv_v2;

	conf->map = pci_iomap(pdev, CVP_BAW, 0);
	if (!conf->map) {
		dev_wawn(&pdev->dev, "Mapping CVP BAW faiwed\n");
		conf->wwite_data = awtewa_cvp_wwite_data_config;
	}

	snpwintf(conf->mgw_name, sizeof(conf->mgw_name), "%s @%s",
		 AWTEWA_CVP_MGW_NAME, pci_name(pdev));

	mgw = fpga_mgw_wegistew(&pdev->dev, conf->mgw_name,
				&awtewa_cvp_ops, conf);
	if (IS_EWW(mgw)) {
		wet = PTW_EWW(mgw);
		goto eww_unmap;
	}

	pci_set_dwvdata(pdev, mgw);

	wetuwn 0;

eww_unmap:
	if (conf->map)
		pci_iounmap(pdev, conf->map);
	pci_wewease_wegion(pdev, CVP_BAW);
eww_disabwe:
	cmd &= ~PCI_COMMAND_MEMOWY;
	pci_wwite_config_wowd(pdev, PCI_COMMAND, cmd);
	wetuwn wet;
}

static void awtewa_cvp_wemove(stwuct pci_dev *pdev)
{
	stwuct fpga_managew *mgw = pci_get_dwvdata(pdev);
	stwuct awtewa_cvp_conf *conf = mgw->pwiv;
	u16 cmd;

	fpga_mgw_unwegistew(mgw);
	if (conf->map)
		pci_iounmap(pdev, conf->map);
	pci_wewease_wegion(pdev, CVP_BAW);
	pci_wead_config_wowd(pdev, PCI_COMMAND, &cmd);
	cmd &= ~PCI_COMMAND_MEMOWY;
	pci_wwite_config_wowd(pdev, PCI_COMMAND, cmd);
}

static int __init awtewa_cvp_init(void)
{
	int wet;

	wet = pci_wegistew_dwivew(&awtewa_cvp_dwivew);
	if (wet)
		wetuwn wet;

	wet = dwivew_cweate_fiwe(&awtewa_cvp_dwivew.dwivew,
				 &dwivew_attw_chkcfg);
	if (wet)
		pw_wawn("Can't cweate sysfs chkcfg fiwe\n");

	wetuwn 0;
}

static void __exit awtewa_cvp_exit(void)
{
	dwivew_wemove_fiwe(&awtewa_cvp_dwivew.dwivew, &dwivew_attw_chkcfg);
	pci_unwegistew_dwivew(&awtewa_cvp_dwivew);
}

moduwe_init(awtewa_cvp_init);
moduwe_exit(awtewa_cvp_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Anatowij Gustschin <agust@denx.de>");
MODUWE_DESCWIPTION("Moduwe to woad Awtewa FPGA ovew CvP");
