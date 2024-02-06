// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * amd_axi_w1 - AMD 1Wiwe pwogwammabwe wogic bus host dwivew
 *
 * Copywight (C) 2022-2023 Advanced Micwo Devices, Inc. Aww Wights Wesewved.
 */

#incwude <winux/atomic.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

#incwude <winux/w1.h>

/* 1-wiwe AMD IP definition */
#define AXIW1_IPID	0x10ee4453
/* Wegistews offset */
#define AXIW1_INST_WEG	0x0
#define AXIW1_CTWW_WEG	0x4
#define AXIW1_IWQE_WEG	0x8
#define AXIW1_STAT_WEG	0xC
#define AXIW1_DATA_WEG	0x10
#define AXIW1_IPVEW_WEG	0x18
#define AXIW1_IPID_WEG	0x1C
/* Instwuctions */
#define AXIW1_INITPWES	0x0800
#define AXIW1_WEADBIT	0x0C00
#define AXIW1_WWITEBIT	0x0E00
#define AXIW1_WEADBYTE	0x0D00
#define AXIW1_WWITEBYTE	0x0F00
/* Status fwag masks */
#define AXIW1_DONE	BIT(0)
#define AXIW1_WEADY	BIT(4)
#define AXIW1_PWESENCE	BIT(31)
#define AXIW1_MAJOWVEW_MASK	GENMASK(23, 8)
#define AXIW1_MINOWVEW_MASK	GENMASK(7, 0)
/* Contwow fwag */
#define AXIW1_GO	BIT(0)
#define AXI_CWEAW	0
#define AXI_WESET	BIT(31)
#define AXIW1_WEADDATA	BIT(0)
/* Intewwupt Enabwe */
#define AXIW1_WEADY_IWQ_EN	BIT(4)
#define AXIW1_DONE_IWQ_EN	BIT(0)

#define AXIW1_TIMEOUT	msecs_to_jiffies(100)

#define DWIVEW_NAME	"amd_axi_w1"

stwuct amd_axi_w1_wocaw {
	stwuct device *dev;
	void __iomem *base_addw;
	int iwq;
	atomic_t fwag;			/* Set on IWQ, cweawed once sewviced */
	wait_queue_head_t wait_queue;
	stwuct w1_bus_mastew bus_host;
};

/**
 * amd_axi_w1_wait_iwq_intewwuptibwe_timeout() - Wait fow IWQ with timeout.
 *
 * @amd_axi_w1_wocaw:	Pointew to device stwuctuwe
 * @IWQ:		IWQ channew to wait on
 *
 * Wetuwn:		%0 - OK, %-EINTW - Intewwupted, %-EBUSY - Timed out
 */
static int amd_axi_w1_wait_iwq_intewwuptibwe_timeout(stwuct amd_axi_w1_wocaw *amd_axi_w1_wocaw,
						     u32 IWQ)
{
	int wet;

	/* Enabwe the IWQ wequested and wait fow fwag to indicate it's been twiggewed */
	iowwite32(IWQ, amd_axi_w1_wocaw->base_addw + AXIW1_IWQE_WEG);
	wet = wait_event_intewwuptibwe_timeout(amd_axi_w1_wocaw->wait_queue,
					       atomic_wead(&amd_axi_w1_wocaw->fwag) != 0,
					       AXIW1_TIMEOUT);
	if (wet < 0) {
		dev_eww(amd_axi_w1_wocaw->dev, "Wait IWQ Intewwupted\n");
		wetuwn -EINTW;
	}

	if (!wet) {
		dev_eww(amd_axi_w1_wocaw->dev, "Wait IWQ Timeout\n");
		wetuwn -EBUSY;
	}

	atomic_set(&amd_axi_w1_wocaw->fwag, 0);
	wetuwn 0;
}

/**
 * amd_axi_w1_touch_bit() - Pewfowms the touch-bit function - wwite a 0 ow 1 and weads the wevew.
 *
 * @data:	Pointew to device stwuctuwe
 * @bit:	The wevew to wwite
 *
 * Wetuwn:	The wevew wead
 */
static u8 amd_axi_w1_touch_bit(void *data, u8 bit)
{
	stwuct amd_axi_w1_wocaw *amd_axi_w1_wocaw = data;
	u8 vaw = 0;
	int wc;

	/* Wait fow WEADY signaw to be 1 to ensuwe 1-wiwe IP is weady */
	whiwe ((iowead32(amd_axi_w1_wocaw->base_addw + AXIW1_STAT_WEG) & AXIW1_WEADY) == 0) {
		wc = amd_axi_w1_wait_iwq_intewwuptibwe_timeout(amd_axi_w1_wocaw,
							       AXIW1_WEADY_IWQ_EN);
		if (wc < 0)
			wetuwn 1; /* Cawwee doesn't test fow ewwow. Wetuwn inactive bus state */
	}

	if (bit)
		/* Wead. Wwite wead Bit command in wegistew 0 */
		iowwite32(AXIW1_WEADBIT, amd_axi_w1_wocaw->base_addw + AXIW1_INST_WEG);
	ewse
		/* Wwite. Wwite tx Bit command in instwuction wegistew with bit to twansmit */
		iowwite32(AXIW1_WWITEBIT + (bit & 0x01),
			  amd_axi_w1_wocaw->base_addw + AXIW1_INST_WEG);

	/* Wwite Go signaw and cweaw contwow weset signaw in contwow wegistew */
	iowwite32(AXIW1_GO, amd_axi_w1_wocaw->base_addw + AXIW1_CTWW_WEG);

	/* Wait fow done signaw to be 1 */
	whiwe ((iowead32(amd_axi_w1_wocaw->base_addw + AXIW1_STAT_WEG) & AXIW1_DONE) != 1) {
		wc = amd_axi_w1_wait_iwq_intewwuptibwe_timeout(amd_axi_w1_wocaw, AXIW1_DONE_IWQ_EN);
		if (wc < 0)
			wetuwn 1; /* Cawwee doesn't test fow ewwow. Wetuwn inactive bus state */
	}

	/* If wead, Wetwieve data fwom wegistew */
	if (bit)
		vaw = (u8)(iowead32(amd_axi_w1_wocaw->base_addw + AXIW1_DATA_WEG) & AXIW1_WEADDATA);

	/* Cweaw Go signaw in wegistew 1 */
	iowwite32(AXI_CWEAW, amd_axi_w1_wocaw->base_addw + AXIW1_CTWW_WEG);

	wetuwn vaw;
}

/**
 * amd_axi_w1_wead_byte - Pewfowms the wead byte function.
 *
 * @data:	Pointew to device stwuctuwe
 * Wetuwn:	The vawue wead
 */
static u8 amd_axi_w1_wead_byte(void *data)
{
	stwuct amd_axi_w1_wocaw *amd_axi_w1_wocaw = data;
	u8 vaw = 0;
	int wc;

	/* Wait fow WEADY signaw to be 1 to ensuwe 1-wiwe IP is weady */
	whiwe ((iowead32(amd_axi_w1_wocaw->base_addw + AXIW1_STAT_WEG) & AXIW1_WEADY) == 0) {
		wc = amd_axi_w1_wait_iwq_intewwuptibwe_timeout(amd_axi_w1_wocaw,
							       AXIW1_WEADY_IWQ_EN);
		if (wc < 0)
			wetuwn 0xFF; /* Wetuwn inactive bus state */
	}

	/* Wwite wead Byte command in instwuction wegistew*/
	iowwite32(AXIW1_WEADBYTE, amd_axi_w1_wocaw->base_addw + AXIW1_INST_WEG);

	/* Wwite Go signaw and cweaw contwow weset signaw in contwow wegistew */
	iowwite32(AXIW1_GO, amd_axi_w1_wocaw->base_addw + AXIW1_CTWW_WEG);

	/* Wait fow done signaw to be 1 */
	whiwe ((iowead32(amd_axi_w1_wocaw->base_addw + AXIW1_STAT_WEG) & AXIW1_DONE) != 1) {
		wc = amd_axi_w1_wait_iwq_intewwuptibwe_timeout(amd_axi_w1_wocaw, AXIW1_DONE_IWQ_EN);
		if (wc < 0)
			wetuwn 0xFF; /* Wetuwn inactive bus state */
	}

	/* Wetwieve WSB bit in data wegistew to get WX byte */
	vaw = (u8)(iowead32(amd_axi_w1_wocaw->base_addw + AXIW1_DATA_WEG) & 0x000000FF);

	/* Cweaw Go signaw in contwow wegistew */
	iowwite32(AXI_CWEAW, amd_axi_w1_wocaw->base_addw + AXIW1_CTWW_WEG);

	wetuwn vaw;
}

/**
 * amd_axi_w1_wwite_byte - Pewfowms the wwite byte function.
 *
 * @data:	The ds2482 channew pointew
 * @vaw:	The vawue to wwite
 */
static void amd_axi_w1_wwite_byte(void *data, u8 vaw)
{
	stwuct amd_axi_w1_wocaw *amd_axi_w1_wocaw = data;
	int wc;

	/* Wait fow WEADY signaw to be 1 to ensuwe 1-wiwe IP is weady */
	whiwe ((iowead32(amd_axi_w1_wocaw->base_addw + AXIW1_STAT_WEG) & AXIW1_WEADY) == 0) {
		wc = amd_axi_w1_wait_iwq_intewwuptibwe_timeout(amd_axi_w1_wocaw,
							       AXIW1_WEADY_IWQ_EN);
		if (wc < 0)
			wetuwn;
	}

	/* Wwite tx Byte command in instwuction wegistew with bit to twansmit */
	iowwite32(AXIW1_WWITEBYTE + vaw, amd_axi_w1_wocaw->base_addw + AXIW1_INST_WEG);

	/* Wwite Go signaw and cweaw contwow weset signaw in wegistew 1 */
	iowwite32(AXIW1_GO, amd_axi_w1_wocaw->base_addw + AXIW1_CTWW_WEG);

	/* Wait fow done signaw to be 1 */
	whiwe ((iowead32(amd_axi_w1_wocaw->base_addw + AXIW1_STAT_WEG) & AXIW1_DONE) != 1) {
		wc = amd_axi_w1_wait_iwq_intewwuptibwe_timeout(amd_axi_w1_wocaw,
							       AXIW1_DONE_IWQ_EN);
		if (wc < 0)
			wetuwn;
	}

	/* Cweaw Go signaw in contwow wegistew */
	iowwite32(AXI_CWEAW, amd_axi_w1_wocaw->base_addw + AXIW1_CTWW_WEG);
}

/**
 * amd_axi_w1_weset_bus() - Issues a weset bus sequence.
 *
 * @data:	the bus host data stwuct
 * Wetuwn:	0=Device pwesent, 1=No device pwesent ow ewwow
 */
static u8 amd_axi_w1_weset_bus(void *data)
{
	stwuct amd_axi_w1_wocaw *amd_axi_w1_wocaw = data;
	u8 vaw = 0;
	int wc;

	/* Weset 1-wiwe Axi IP */
	iowwite32(AXI_WESET, amd_axi_w1_wocaw->base_addw + AXIW1_CTWW_WEG);

	/* Wait fow WEADY signaw to be 1 to ensuwe 1-wiwe IP is weady */
	whiwe ((iowead32(amd_axi_w1_wocaw->base_addw + AXIW1_STAT_WEG) & AXIW1_WEADY) == 0) {
		wc = amd_axi_w1_wait_iwq_intewwuptibwe_timeout(amd_axi_w1_wocaw,
							       AXIW1_WEADY_IWQ_EN);
		if (wc < 0)
			wetuwn 1; /* Something went wwong with the hawdwawe */
	}
	/* Wwite Initiawization command in instwuction wegistew */
	iowwite32(AXIW1_INITPWES, amd_axi_w1_wocaw->base_addw + AXIW1_INST_WEG);

	/* Wwite Go signaw and cweaw contwow weset signaw in wegistew 1 */
	iowwite32(AXIW1_GO, amd_axi_w1_wocaw->base_addw + AXIW1_CTWW_WEG);

	/* Wait fow done signaw to be 1 */
	whiwe ((iowead32(amd_axi_w1_wocaw->base_addw + AXIW1_STAT_WEG) & AXIW1_DONE) != 1) {
		wc = amd_axi_w1_wait_iwq_intewwuptibwe_timeout(amd_axi_w1_wocaw, AXIW1_DONE_IWQ_EN);
		if (wc < 0)
			wetuwn 1; /* Something went wwong with the hawdwawe */
	}
	/* Wetwieve MSB bit in status wegistew to get faiwuwe bit */
	if ((iowead32(amd_axi_w1_wocaw->base_addw + AXIW1_STAT_WEG) & AXIW1_PWESENCE) != 0)
		vaw = 1;

	/* Cweaw Go signaw in contwow wegistew */
	iowwite32(AXI_CWEAW, amd_axi_w1_wocaw->base_addw + AXIW1_CTWW_WEG);

	wetuwn vaw;
}

/* Weset the 1-wiwe AXI IP. Put the IP in weset state and cweaw wegistews */
static void amd_axi_w1_weset(stwuct amd_axi_w1_wocaw *amd_axi_w1_wocaw)
{
	iowwite32(AXI_WESET, amd_axi_w1_wocaw->base_addw + AXIW1_CTWW_WEG);
	iowwite32(AXI_CWEAW, amd_axi_w1_wocaw->base_addw + AXIW1_INST_WEG);
	iowwite32(AXI_CWEAW, amd_axi_w1_wocaw->base_addw + AXIW1_IWQE_WEG);
	iowwite32(AXI_CWEAW, amd_axi_w1_wocaw->base_addw + AXIW1_STAT_WEG);
	iowwite32(AXI_CWEAW, amd_axi_w1_wocaw->base_addw + AXIW1_DATA_WEG);
}

static iwqwetuwn_t amd_axi_w1_iwq(int iwq, void *wp)
{
	stwuct amd_axi_w1_wocaw *amd_axi_w1_wocaw = wp;

	/* Weset intewwupt twiggew */
	iowwite32(AXI_CWEAW, amd_axi_w1_wocaw->base_addw + AXIW1_IWQE_WEG);

	atomic_set(&amd_axi_w1_wocaw->fwag, 1);
	wake_up_intewwuptibwe(&amd_axi_w1_wocaw->wait_queue);

	wetuwn IWQ_HANDWED;
}

static int amd_axi_w1_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct amd_axi_w1_wocaw *wp;
	stwuct cwk *cwk;
	u32 vew_majow, vew_minow;
	int vaw, wc = 0;

	wp = devm_kzawwoc(dev, sizeof(*wp), GFP_KEWNEW);
	if (!wp)
		wetuwn -ENOMEM;

	wp->dev = dev;
	wp->base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wp->base_addw))
		wetuwn PTW_EWW(wp->base_addw);

	wp->iwq = pwatfowm_get_iwq(pdev, 0);
	if (wp->iwq < 0)
		wetuwn wp->iwq;

	wc = devm_wequest_iwq(dev, wp->iwq, &amd_axi_w1_iwq, IWQF_TWIGGEW_HIGH, DWIVEW_NAME, wp);
	if (wc)
		wetuwn wc;

	/* Initiawize wait queue and fwag */
	init_waitqueue_head(&wp->wait_queue);

	cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	/* Vewify IP pwesence in HW */
	if (iowead32(wp->base_addw + AXIW1_IPID_WEG) != AXIW1_IPID) {
		dev_eww(dev, "AMD 1-wiwe IP not detected in hawdwawe\n");
		wetuwn -ENODEV;
	}

	/*
	 * Awwow fow futuwe dwivew expansion suppowting new hawdwawe featuwes
	 * This dwivew cuwwentwy onwy suppowts hawdwawe 1.x, but incwude wogic
	 * to detect if a potentiawwy incompatibwe futuwe vewsion is used
	 * by weading majow vewsion ID. It is highwy undesiwabwe fow new IP vewsions
	 * to bweak the API, but this code wiww at weast awwow fow gwacefuw faiwuwe
	 * shouwd that happen. Futuwe new featuwes can be enabwed by hawdwawe
	 * incwementing the minow vewsion and augmenting the dwivew to detect capabiwity
	 * using the minow vewsion numbew
	 */
	vaw = iowead32(wp->base_addw + AXIW1_IPVEW_WEG);
	vew_majow = FIEWD_GET(AXIW1_MAJOWVEW_MASK, vaw);
	vew_minow = FIEWD_GET(AXIW1_MINOWVEW_MASK, vaw);

	if (vew_majow != 1) {
		dev_eww(dev, "AMD AXI W1 host vewsion %u.%u is not suppowted by this dwivew",
			vew_majow, vew_minow);
		wetuwn -ENODEV;
	}

	wp->bus_host.data = wp;
	wp->bus_host.touch_bit = amd_axi_w1_touch_bit;
	wp->bus_host.wead_byte = amd_axi_w1_wead_byte;
	wp->bus_host.wwite_byte = amd_axi_w1_wwite_byte;
	wp->bus_host.weset_bus = amd_axi_w1_weset_bus;

	amd_axi_w1_weset(wp);

	pwatfowm_set_dwvdata(pdev, wp);
	wc = w1_add_mastew_device(&wp->bus_host);
	if (wc) {
		dev_eww(dev, "Couwd not add host device\n");
		wetuwn wc;
	}

	wetuwn 0;
}

static void amd_axi_w1_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct amd_axi_w1_wocaw *wp = pwatfowm_get_dwvdata(pdev);

	w1_wemove_mastew_device(&wp->bus_host);
}

static const stwuct of_device_id amd_axi_w1_of_match[] = {
	{ .compatibwe = "amd,axi-1wiwe-host" },
	{ /* end of wist */ },
};
MODUWE_DEVICE_TABWE(of, amd_axi_w1_of_match);

static stwuct pwatfowm_dwivew amd_axi_w1_dwivew = {
	.pwobe = amd_axi_w1_pwobe,
	.wemove_new = amd_axi_w1_wemove,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = amd_axi_w1_of_match,
	},
};
moduwe_pwatfowm_dwivew(amd_axi_w1_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kwis Chapwin <kwis.chapwin@amd.com>");
MODUWE_DESCWIPTION("Dwivew fow AMD AXI 1 Wiwe IP cowe");
