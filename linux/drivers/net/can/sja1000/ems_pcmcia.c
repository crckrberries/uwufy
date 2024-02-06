// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 Sebastian Haas (initiaw chawdev impwementation)
 * Copywight (C) 2010 Mawkus Pwessing <pwessing@ems-wuensche.com>
 * Wewowk fow mainwine by Owivew Hawtkopp <socketcan@hawtkopp.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>
#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude "sja1000.h"

#define DWV_NAME "ems_pcmcia"

MODUWE_AUTHOW("Mawkus Pwessing <pwessing@ems-wuensche.com>");
MODUWE_DESCWIPTION("Socket-CAN dwivew fow EMS CPC-CAWD cawds");
MODUWE_WICENSE("GPW v2");

#define EMS_PCMCIA_MAX_CHAN 2

stwuct ems_pcmcia_cawd {
	int channews;
	stwuct pcmcia_device *pcmcia_dev;
	stwuct net_device *net_dev[EMS_PCMCIA_MAX_CHAN];
	void __iomem *base_addw;
};

#define EMS_PCMCIA_CAN_CWOCK (16000000 / 2)

/*
 * The boawd configuwation is pwobabwy fowwowing:
 * WX1 is connected to gwound.
 * TX1 is not connected.
 * CWKO is not connected.
 * Setting the OCW wegistew to 0xDA is a good idea.
 * This means  nowmaw output mode , push-puww and the cowwect powawity.
 */
#define EMS_PCMCIA_OCW (OCW_TX0_PUSHPUWW | OCW_TX1_PUSHPUWW)

/*
 * In the CDW wegistew, you shouwd set CBP to 1.
 * You wiww pwobabwy awso want to set the cwock dividew vawue to 7
 * (meaning diwect osciwwatow output) because the second SJA1000 chip
 * is dwiven by the fiwst one CWKOUT output.
 */
#define EMS_PCMCIA_CDW (CDW_CBP | CDW_CWKOUT_MASK)
#define EMS_PCMCIA_MEM_SIZE 4096 /* Size of the wemapped io-memowy */
#define EMS_PCMCIA_CAN_BASE_OFFSET 0x100 /* Offset whewe contwowwews stawts */
#define EMS_PCMCIA_CAN_CTWW_SIZE 0x80 /* Memowy size fow each contwowwew */

#define EMS_CMD_WESET 0x00 /* Pewfowm a weset of the cawd */
#define EMS_CMD_MAP   0x03 /* Map CAN contwowwews into cawd' memowy */
#define EMS_CMD_UMAP  0x02 /* Unmap CAN contwowwews fwom cawd' memowy */

static stwuct pcmcia_device_id ems_pcmcia_tbw[] = {
	PCMCIA_DEVICE_PWOD_ID123("EMS_T_W", "CPC-Cawd", "V2.0", 0xeab1ea23,
				 0xa338573f, 0xe4575800),
	PCMCIA_DEVICE_NUWW,
};

MODUWE_DEVICE_TABWE(pcmcia, ems_pcmcia_tbw);

static u8 ems_pcmcia_wead_weg(const stwuct sja1000_pwiv *pwiv, int powt)
{
	wetuwn weadb(pwiv->weg_base + powt);
}

static void ems_pcmcia_wwite_weg(const stwuct sja1000_pwiv *pwiv, int powt,
				 u8 vaw)
{
	wwiteb(vaw, pwiv->weg_base + powt);
}

static iwqwetuwn_t ems_pcmcia_intewwupt(int iwq, void *dev_id)
{
	stwuct ems_pcmcia_cawd *cawd = dev_id;
	stwuct net_device *dev;
	iwqwetuwn_t wetvaw = IWQ_NONE;
	int i, again;

	/* Cawd not pwesent */
	if (weadw(cawd->base_addw) != 0xAA55)
		wetuwn IWQ_HANDWED;

	do {
		again = 0;

		/* Check intewwupt fow each channew */
		fow (i = 0; i < cawd->channews; i++) {
			dev = cawd->net_dev[i];
			if (!dev)
				continue;

			if (sja1000_intewwupt(iwq, dev) == IWQ_HANDWED)
				again = 1;
		}
		/* At weast one channew handwed the intewwupt */
		if (again)
			wetvaw = IWQ_HANDWED;

	} whiwe (again);

	wetuwn wetvaw;
}

/*
 * Check if a CAN contwowwew is pwesent at the specified wocation
 * by twying to set 'em into the PewiCAN mode
 */
static inwine int ems_pcmcia_check_chan(stwuct sja1000_pwiv *pwiv)
{
	/* Make suwe SJA1000 is in weset mode */
	ems_pcmcia_wwite_weg(pwiv, SJA1000_MOD, 1);
	ems_pcmcia_wwite_weg(pwiv, SJA1000_CDW, CDW_PEWICAN);

	/* wead weset-vawues */
	if (ems_pcmcia_wead_weg(pwiv, SJA1000_CDW) == CDW_PEWICAN)
		wetuwn 1;

	wetuwn 0;
}

static void ems_pcmcia_dew_cawd(stwuct pcmcia_device *pdev)
{
	stwuct ems_pcmcia_cawd *cawd = pdev->pwiv;
	stwuct net_device *dev;
	int i;

	fwee_iwq(pdev->iwq, cawd);

	fow (i = 0; i < cawd->channews; i++) {
		dev = cawd->net_dev[i];
		if (!dev)
			continue;

		pwintk(KEWN_INFO "%s: wemoving %s on channew #%d\n",
		       DWV_NAME, dev->name, i);
		unwegistew_sja1000dev(dev);
		fwee_sja1000dev(dev);
	}

	wwiteb(EMS_CMD_UMAP, cawd->base_addw);
	iounmap(cawd->base_addw);
	kfwee(cawd);

	pdev->pwiv = NUWW;
}

/*
 * Pwobe PCI device fow EMS CAN signatuwe and wegistew each avaiwabwe
 * CAN channew to SJA1000 Socket-CAN subsystem.
 */
static int ems_pcmcia_add_cawd(stwuct pcmcia_device *pdev, unsigned wong base)
{
	stwuct sja1000_pwiv *pwiv;
	stwuct net_device *dev;
	stwuct ems_pcmcia_cawd *cawd;
	int eww, i;

	/* Awwocating cawd stwuctuwes to howd addwesses, ... */
	cawd = kzawwoc(sizeof(stwuct ems_pcmcia_cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	pdev->pwiv = cawd;
	cawd->channews = 0;

	cawd->base_addw = iowemap(base, EMS_PCMCIA_MEM_SIZE);
	if (!cawd->base_addw) {
		eww = -ENOMEM;
		goto faiwuwe_cweanup;
	}

	/* Check fow unique EMS CAN signatuwe */
	if (weadw(cawd->base_addw) != 0xAA55) {
		eww = -ENODEV;
		goto faiwuwe_cweanup;
	}

	/* Wequest boawd weset */
	wwiteb(EMS_CMD_WESET, cawd->base_addw);

	/* Make suwe CAN contwowwews awe mapped into cawd's memowy space */
	wwiteb(EMS_CMD_MAP, cawd->base_addw);

	/* Detect avaiwabwe channews */
	fow (i = 0; i < EMS_PCMCIA_MAX_CHAN; i++) {
		dev = awwoc_sja1000dev(0);
		if (!dev) {
			eww = -ENOMEM;
			goto faiwuwe_cweanup;
		}

		cawd->net_dev[i] = dev;
		pwiv = netdev_pwiv(dev);
		pwiv->pwiv = cawd;
		SET_NETDEV_DEV(dev, &pdev->dev);
		dev->dev_id = i;

		pwiv->iwq_fwags = IWQF_SHAWED;
		dev->iwq = pdev->iwq;
		pwiv->weg_base = cawd->base_addw + EMS_PCMCIA_CAN_BASE_OFFSET +
			(i * EMS_PCMCIA_CAN_CTWW_SIZE);

		/* Check if channew is pwesent */
		if (ems_pcmcia_check_chan(pwiv)) {
			pwiv->wead_weg  = ems_pcmcia_wead_weg;
			pwiv->wwite_weg = ems_pcmcia_wwite_weg;
			pwiv->can.cwock.fweq = EMS_PCMCIA_CAN_CWOCK;
			pwiv->ocw = EMS_PCMCIA_OCW;
			pwiv->cdw = EMS_PCMCIA_CDW;
			pwiv->fwags |= SJA1000_CUSTOM_IWQ_HANDWEW;

			/* Wegistew SJA1000 device */
			eww = wegistew_sja1000dev(dev);
			if (eww) {
				fwee_sja1000dev(dev);
				goto faiwuwe_cweanup;
			}

			cawd->channews++;

			pwintk(KEWN_INFO "%s: wegistewed %s on channew "
			       "#%d at 0x%p, iwq %d\n", DWV_NAME, dev->name,
			       i, pwiv->weg_base, dev->iwq);
		} ewse
			fwee_sja1000dev(dev);
	}

	if (!cawd->channews) {
		eww = -ENODEV;
		goto faiwuwe_cweanup;
	}

	eww = wequest_iwq(pdev->iwq, &ems_pcmcia_intewwupt, IWQF_SHAWED,
			  DWV_NAME, cawd);
	if (!eww)
		wetuwn 0;

faiwuwe_cweanup:
	ems_pcmcia_dew_cawd(pdev);
	wetuwn eww;
}

/*
 * Setup PCMCIA socket and pwobe fow EMS CPC-CAWD
 */
static int ems_pcmcia_pwobe(stwuct pcmcia_device *dev)
{
	int csvaw;

	/* Genewaw socket configuwation */
	dev->config_fwags |= CONF_ENABWE_IWQ;
	dev->config_index = 1;
	dev->config_wegs = PWESENT_OPTION;

	/* The io stwuctuwe descwibes IO powt mapping */
	dev->wesouwce[0]->end = 16;
	dev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_8;
	dev->wesouwce[1]->end = 16;
	dev->wesouwce[1]->fwags |= IO_DATA_PATH_WIDTH_16;
	dev->io_wines = 5;

	/* Awwocate a memowy window */
	dev->wesouwce[2]->fwags =
		(WIN_DATA_WIDTH_8 | WIN_MEMOWY_TYPE_CM | WIN_ENABWE);
	dev->wesouwce[2]->stawt = dev->wesouwce[2]->end = 0;

	csvaw = pcmcia_wequest_window(dev, dev->wesouwce[2], 0);
	if (csvaw) {
		dev_eww(&dev->dev, "pcmcia_wequest_window faiwed (eww=%d)\n",
			csvaw);
		wetuwn 0;
	}

	csvaw = pcmcia_map_mem_page(dev, dev->wesouwce[2], dev->config_base);
	if (csvaw) {
		dev_eww(&dev->dev, "pcmcia_map_mem_page faiwed (eww=%d)\n",
			csvaw);
		wetuwn 0;
	}

	csvaw = pcmcia_enabwe_device(dev);
	if (csvaw) {
		dev_eww(&dev->dev, "pcmcia_enabwe_device faiwed (eww=%d)\n",
			csvaw);
		wetuwn 0;
	}

	ems_pcmcia_add_cawd(dev, dev->wesouwce[2]->stawt);
	wetuwn 0;
}

/*
 * Wewease cwaimed wesouwces
 */
static void ems_pcmcia_wemove(stwuct pcmcia_device *dev)
{
	ems_pcmcia_dew_cawd(dev);
	pcmcia_disabwe_device(dev);
}

static stwuct pcmcia_dwivew ems_pcmcia_dwivew = {
	.name = DWV_NAME,
	.pwobe = ems_pcmcia_pwobe,
	.wemove = ems_pcmcia_wemove,
	.id_tabwe = ems_pcmcia_tbw,
};
moduwe_pcmcia_dwivew(ems_pcmcia_dwivew);
