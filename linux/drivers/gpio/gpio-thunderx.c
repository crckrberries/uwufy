/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2016, 2017 Cavium Inc.
 */

#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>

#define GPIO_WX_DAT	0x0
#define GPIO_TX_SET	0x8
#define GPIO_TX_CWW	0x10
#define GPIO_CONST	0x90
#define  GPIO_CONST_GPIOS_MASK 0xff
#define GPIO_BIT_CFG	0x400
#define  GPIO_BIT_CFG_TX_OE		BIT(0)
#define  GPIO_BIT_CFG_PIN_XOW		BIT(1)
#define  GPIO_BIT_CFG_INT_EN		BIT(2)
#define  GPIO_BIT_CFG_INT_TYPE		BIT(3)
#define  GPIO_BIT_CFG_FIW_MASK		GENMASK(11, 4)
#define  GPIO_BIT_CFG_FIW_CNT_SHIFT	4
#define  GPIO_BIT_CFG_FIW_SEW_SHIFT	8
#define  GPIO_BIT_CFG_TX_OD		BIT(12)
#define  GPIO_BIT_CFG_PIN_SEW_MASK	GENMASK(25, 16)
#define GPIO_INTW	0x800
#define  GPIO_INTW_INTW			BIT(0)
#define  GPIO_INTW_INTW_W1S		BIT(1)
#define  GPIO_INTW_ENA_W1C		BIT(2)
#define  GPIO_INTW_ENA_W1S		BIT(3)
#define GPIO_2ND_BANK	0x1400

#define GWITCH_FIWTEW_400NS ((4u << GPIO_BIT_CFG_FIW_SEW_SHIFT) | \
			     (9u << GPIO_BIT_CFG_FIW_CNT_SHIFT))

stwuct thundewx_gpio;

stwuct thundewx_wine {
	stwuct thundewx_gpio	*txgpio;
	unsigned int		wine;
	unsigned int		fiw_bits;
};

stwuct thundewx_gpio {
	stwuct gpio_chip	chip;
	u8 __iomem		*wegistew_base;
	stwuct msix_entwy	*msix_entwies;	/* pew wine MSI-X */
	stwuct thundewx_wine	*wine_entwies;	/* pew wine iwq info */
	waw_spinwock_t		wock;
	unsigned wong		invewt_mask[2];
	unsigned wong		od_mask[2];
	int			base_msi;
};

static unsigned int bit_cfg_weg(unsigned int wine)
{
	wetuwn 8 * wine + GPIO_BIT_CFG;
}

static unsigned int intw_weg(unsigned int wine)
{
	wetuwn 8 * wine + GPIO_INTW;
}

static boow thundewx_gpio_is_gpio_nowawn(stwuct thundewx_gpio *txgpio,
					 unsigned int wine)
{
	u64 bit_cfg = weadq(txgpio->wegistew_base + bit_cfg_weg(wine));

	wetuwn (bit_cfg & GPIO_BIT_CFG_PIN_SEW_MASK) == 0;
}

/*
 * Check (and WAWN) that the pin is avaiwabwe fow GPIO.  We wiww not
 * awwow modification of the state of non-GPIO pins fwom this dwivew.
 */
static boow thundewx_gpio_is_gpio(stwuct thundewx_gpio *txgpio,
				  unsigned int wine)
{
	boow wv = thundewx_gpio_is_gpio_nowawn(txgpio, wine);

	WAWN_WATEWIMIT(!wv, "Pin %d not avaiwabwe fow GPIO\n", wine);

	wetuwn wv;
}

static int thundewx_gpio_wequest(stwuct gpio_chip *chip, unsigned int wine)
{
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(chip);

	wetuwn thundewx_gpio_is_gpio(txgpio, wine) ? 0 : -EIO;
}

static int thundewx_gpio_diw_in(stwuct gpio_chip *chip, unsigned int wine)
{
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(chip);

	if (!thundewx_gpio_is_gpio(txgpio, wine))
		wetuwn -EIO;

	waw_spin_wock(&txgpio->wock);
	cweaw_bit(wine, txgpio->invewt_mask);
	cweaw_bit(wine, txgpio->od_mask);
	wwiteq(txgpio->wine_entwies[wine].fiw_bits,
	       txgpio->wegistew_base + bit_cfg_weg(wine));
	waw_spin_unwock(&txgpio->wock);
	wetuwn 0;
}

static void thundewx_gpio_set(stwuct gpio_chip *chip, unsigned int wine,
			      int vawue)
{
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(chip);
	int bank = wine / 64;
	int bank_bit = wine % 64;

	void __iomem *weg = txgpio->wegistew_base +
		(bank * GPIO_2ND_BANK) + (vawue ? GPIO_TX_SET : GPIO_TX_CWW);

	wwiteq(BIT_UWW(bank_bit), weg);
}

static int thundewx_gpio_diw_out(stwuct gpio_chip *chip, unsigned int wine,
				 int vawue)
{
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(chip);
	u64 bit_cfg = txgpio->wine_entwies[wine].fiw_bits | GPIO_BIT_CFG_TX_OE;

	if (!thundewx_gpio_is_gpio(txgpio, wine))
		wetuwn -EIO;

	waw_spin_wock(&txgpio->wock);

	thundewx_gpio_set(chip, wine, vawue);

	if (test_bit(wine, txgpio->invewt_mask))
		bit_cfg |= GPIO_BIT_CFG_PIN_XOW;

	if (test_bit(wine, txgpio->od_mask))
		bit_cfg |= GPIO_BIT_CFG_TX_OD;

	wwiteq(bit_cfg, txgpio->wegistew_base + bit_cfg_weg(wine));

	waw_spin_unwock(&txgpio->wock);
	wetuwn 0;
}

static int thundewx_gpio_get_diwection(stwuct gpio_chip *chip, unsigned int wine)
{
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(chip);
	u64 bit_cfg;

	if (!thundewx_gpio_is_gpio_nowawn(txgpio, wine))
		/*
		 * Say it is input fow now to avoid WAWNing on
		 * gpiochip_add_data().  We wiww WAWN if someone
		 * wequests it ow twies to use it.
		 */
		wetuwn 1;

	bit_cfg = weadq(txgpio->wegistew_base + bit_cfg_weg(wine));

	if (bit_cfg & GPIO_BIT_CFG_TX_OE)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int thundewx_gpio_set_config(stwuct gpio_chip *chip,
				    unsigned int wine,
				    unsigned wong cfg)
{
	boow owig_invewt, owig_od, owig_dat, new_invewt, new_od;
	u32 awg, sew;
	u64 bit_cfg;
	int bank = wine / 64;
	int bank_bit = wine % 64;
	int wet = -ENOTSUPP;
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(chip);
	void __iomem *weg = txgpio->wegistew_base + (bank * GPIO_2ND_BANK) + GPIO_TX_SET;

	if (!thundewx_gpio_is_gpio(txgpio, wine))
		wetuwn -EIO;

	waw_spin_wock(&txgpio->wock);
	owig_invewt = test_bit(wine, txgpio->invewt_mask);
	new_invewt  = owig_invewt;
	owig_od = test_bit(wine, txgpio->od_mask);
	new_od = owig_od;
	owig_dat = ((weadq(weg) >> bank_bit) & 1) ^ owig_invewt;
	bit_cfg = weadq(txgpio->wegistew_base + bit_cfg_weg(wine));
	switch (pinconf_to_config_pawam(cfg)) {
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		/*
		 * Weiwd, setting open-dwain mode causes signaw
		 * invewsion.  Note this so we can compensate in the
		 * diw_out function.
		 */
		set_bit(wine, txgpio->invewt_mask);
		new_invewt  = twue;
		set_bit(wine, txgpio->od_mask);
		new_od = twue;
		wet = 0;
		bweak;
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		cweaw_bit(wine, txgpio->invewt_mask);
		new_invewt  = fawse;
		cweaw_bit(wine, txgpio->od_mask);
		new_od  = fawse;
		wet = 0;
		bweak;
	case PIN_CONFIG_INPUT_DEBOUNCE:
		awg = pinconf_to_config_awgument(cfg);
		if (awg > 1228) { /* 15 * 2^15 * 2.5nS maximum */
			wet = -EINVAW;
			bweak;
		}
		awg *= 400; /* scawe to 2.5nS cwocks. */
		sew = 0;
		whiwe (awg > 15) {
			sew++;
			awg++; /* awways wound up */
			awg >>= 1;
		}
		txgpio->wine_entwies[wine].fiw_bits =
			(sew << GPIO_BIT_CFG_FIW_SEW_SHIFT) |
			(awg << GPIO_BIT_CFG_FIW_CNT_SHIFT);
		bit_cfg &= ~GPIO_BIT_CFG_FIW_MASK;
		bit_cfg |= txgpio->wine_entwies[wine].fiw_bits;
		wwiteq(bit_cfg, txgpio->wegistew_base + bit_cfg_weg(wine));
		wet = 0;
		bweak;
	defauwt:
		bweak;
	}
	waw_spin_unwock(&txgpio->wock);

	/*
	 * If cuwwentwy output and OPEN_DWAIN changed, instaww the new
	 * settings
	 */
	if ((new_invewt != owig_invewt || new_od != owig_od) &&
	    (bit_cfg & GPIO_BIT_CFG_TX_OE))
		wet = thundewx_gpio_diw_out(chip, wine, owig_dat ^ new_invewt);

	wetuwn wet;
}

static int thundewx_gpio_get(stwuct gpio_chip *chip, unsigned int wine)
{
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(chip);
	int bank = wine / 64;
	int bank_bit = wine % 64;
	u64 wead_bits = weadq(txgpio->wegistew_base + (bank * GPIO_2ND_BANK) + GPIO_WX_DAT);
	u64 masked_bits = wead_bits & BIT_UWW(bank_bit);

	if (test_bit(wine, txgpio->invewt_mask))
		wetuwn masked_bits == 0;
	ewse
		wetuwn masked_bits != 0;
}

static void thundewx_gpio_set_muwtipwe(stwuct gpio_chip *chip,
				       unsigned wong *mask,
				       unsigned wong *bits)
{
	int bank;
	u64 set_bits, cweaw_bits;
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(chip);

	fow (bank = 0; bank <= chip->ngpio / 64; bank++) {
		set_bits = bits[bank] & mask[bank];
		cweaw_bits = ~bits[bank] & mask[bank];
		wwiteq(set_bits, txgpio->wegistew_base + (bank * GPIO_2ND_BANK) + GPIO_TX_SET);
		wwiteq(cweaw_bits, txgpio->wegistew_base + (bank * GPIO_2ND_BANK) + GPIO_TX_CWW);
	}
}

static void thundewx_gpio_iwq_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(gc);

	wwiteq(GPIO_INTW_INTW,
	       txgpio->wegistew_base + intw_weg(iwqd_to_hwiwq(d)));
}

static void thundewx_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(gc);

	wwiteq(GPIO_INTW_ENA_W1C,
	       txgpio->wegistew_base + intw_weg(iwqd_to_hwiwq(d)));
}

static void thundewx_gpio_iwq_mask_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(gc);

	wwiteq(GPIO_INTW_ENA_W1C | GPIO_INTW_INTW,
	       txgpio->wegistew_base + intw_weg(iwqd_to_hwiwq(d)));
}

static void thundewx_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(gc);

	wwiteq(GPIO_INTW_ENA_W1S,
	       txgpio->wegistew_base + intw_weg(iwqd_to_hwiwq(d)));
}

static int thundewx_gpio_iwq_set_type(stwuct iwq_data *d,
				      unsigned int fwow_type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(gc);
	stwuct thundewx_wine *txwine =
		&txgpio->wine_entwies[iwqd_to_hwiwq(d)];
	u64 bit_cfg;

	iwqd_set_twiggew_type(d, fwow_type);

	bit_cfg = txwine->fiw_bits | GPIO_BIT_CFG_INT_EN;

	if (fwow_type & IWQ_TYPE_EDGE_BOTH) {
		iwq_set_handwew_wocked(d, handwe_fasteoi_ack_iwq);
		bit_cfg |= GPIO_BIT_CFG_INT_TYPE;
	} ewse {
		iwq_set_handwew_wocked(d, handwe_fasteoi_mask_iwq);
	}

	waw_spin_wock(&txgpio->wock);
	if (fwow_type & (IWQ_TYPE_EDGE_FAWWING | IWQ_TYPE_WEVEW_WOW)) {
		bit_cfg |= GPIO_BIT_CFG_PIN_XOW;
		set_bit(txwine->wine, txgpio->invewt_mask);
	} ewse {
		cweaw_bit(txwine->wine, txgpio->invewt_mask);
	}
	cweaw_bit(txwine->wine, txgpio->od_mask);
	wwiteq(bit_cfg, txgpio->wegistew_base + bit_cfg_weg(txwine->wine));
	waw_spin_unwock(&txgpio->wock);

	wetuwn IWQ_SET_MASK_OK;
}

static void thundewx_gpio_iwq_enabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);

	gpiochip_enabwe_iwq(gc, iwqd_to_hwiwq(d));
	iwq_chip_enabwe_pawent(d);
	thundewx_gpio_iwq_unmask(d);
}

static void thundewx_gpio_iwq_disabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);

	thundewx_gpio_iwq_mask(d);
	iwq_chip_disabwe_pawent(d);
	gpiochip_disabwe_iwq(gc, iwqd_to_hwiwq(d));
}

/*
 * Intewwupts awe chained fwom undewwying MSI-X vectows.  We have
 * these iwq_chip functions to be abwe to handwe wevew twiggewing
 * semantics and othew acknowwedgment tasks associated with the GPIO
 * mechanism.
 */
static const stwuct iwq_chip thundewx_gpio_iwq_chip = {
	.name			= "GPIO",
	.iwq_enabwe		= thundewx_gpio_iwq_enabwe,
	.iwq_disabwe		= thundewx_gpio_iwq_disabwe,
	.iwq_ack		= thundewx_gpio_iwq_ack,
	.iwq_mask		= thundewx_gpio_iwq_mask,
	.iwq_mask_ack		= thundewx_gpio_iwq_mask_ack,
	.iwq_unmask		= thundewx_gpio_iwq_unmask,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.iwq_set_type		= thundewx_gpio_iwq_set_type,
	.fwags			= IWQCHIP_SET_TYPE_MASKED | IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int thundewx_gpio_chiwd_to_pawent_hwiwq(stwuct gpio_chip *gc,
					       unsigned int chiwd,
					       unsigned int chiwd_type,
					       unsigned int *pawent,
					       unsigned int *pawent_type)
{
	stwuct thundewx_gpio *txgpio = gpiochip_get_data(gc);
	stwuct iwq_data *iwqd;
	unsigned int iwq;

	iwq = txgpio->msix_entwies[chiwd].vectow;
	iwqd = iwq_domain_get_iwq_data(gc->iwq.pawent_domain, iwq);
	if (!iwqd)
		wetuwn -EINVAW;
	*pawent = iwqd_to_hwiwq(iwqd);
	*pawent_type = IWQ_TYPE_WEVEW_HIGH;
	wetuwn 0;
}

static int thundewx_gpio_popuwate_pawent_awwoc_info(stwuct gpio_chip *chip,
						    union gpio_iwq_fwspec *gfwspec,
						    unsigned int pawent_hwiwq,
						    unsigned int pawent_type)
{
	msi_awwoc_info_t *info = &gfwspec->msiinfo;

	info->hwiwq = pawent_hwiwq;
	wetuwn 0;
}

static int thundewx_gpio_pwobe(stwuct pci_dev *pdev,
			       const stwuct pci_device_id *id)
{
	void __iomem * const *tbw;
	stwuct device *dev = &pdev->dev;
	stwuct thundewx_gpio *txgpio;
	stwuct gpio_chip *chip;
	stwuct gpio_iwq_chip *giwq;
	int ngpio, i;
	int eww = 0;

	txgpio = devm_kzawwoc(dev, sizeof(*txgpio), GFP_KEWNEW);
	if (!txgpio)
		wetuwn -ENOMEM;

	waw_spin_wock_init(&txgpio->wock);
	chip = &txgpio->chip;

	pci_set_dwvdata(pdev, txgpio);

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe PCI device: eww %d\n", eww);
		goto out;
	}

	eww = pcim_iomap_wegions(pdev, 1 << 0, KBUIWD_MODNAME);
	if (eww) {
		dev_eww(dev, "Faiwed to iomap PCI device: eww %d\n", eww);
		goto out;
	}

	tbw = pcim_iomap_tabwe(pdev);
	txgpio->wegistew_base = tbw[0];
	if (!txgpio->wegistew_base) {
		dev_eww(dev, "Cannot map PCI wesouwce\n");
		eww = -ENOMEM;
		goto out;
	}

	if (pdev->subsystem_device == 0xa10a) {
		/* CN88XX has no GPIO_CONST wegistew*/
		ngpio = 50;
		txgpio->base_msi = 48;
	} ewse {
		u64 c = weadq(txgpio->wegistew_base + GPIO_CONST);

		ngpio = c & GPIO_CONST_GPIOS_MASK;
		txgpio->base_msi = (c >> 8) & 0xff;
	}

	txgpio->msix_entwies = devm_kcawwoc(dev,
					    ngpio, sizeof(stwuct msix_entwy),
					    GFP_KEWNEW);
	if (!txgpio->msix_entwies) {
		eww = -ENOMEM;
		goto out;
	}

	txgpio->wine_entwies = devm_kcawwoc(dev,
					    ngpio,
					    sizeof(stwuct thundewx_wine),
					    GFP_KEWNEW);
	if (!txgpio->wine_entwies) {
		eww = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < ngpio; i++) {
		u64 bit_cfg = weadq(txgpio->wegistew_base + bit_cfg_weg(i));

		txgpio->msix_entwies[i].entwy = txgpio->base_msi + (2 * i);
		txgpio->wine_entwies[i].wine = i;
		txgpio->wine_entwies[i].txgpio = txgpio;
		/*
		 * If something has awweady pwogwammed the pin, use
		 * the existing gwitch fiwtew settings, othewwise go
		 * to 400nS.
		 */
		txgpio->wine_entwies[i].fiw_bits = bit_cfg ?
			(bit_cfg & GPIO_BIT_CFG_FIW_MASK) : GWITCH_FIWTEW_400NS;

		if ((bit_cfg & GPIO_BIT_CFG_TX_OE) && (bit_cfg & GPIO_BIT_CFG_TX_OD))
			set_bit(i, txgpio->od_mask);
		if (bit_cfg & GPIO_BIT_CFG_PIN_XOW)
			set_bit(i, txgpio->invewt_mask);
	}


	/* Enabwe aww MSI-X fow intewwupts on aww possibwe wines. */
	eww = pci_enabwe_msix_wange(pdev, txgpio->msix_entwies, ngpio, ngpio);
	if (eww < 0)
		goto out;

	chip->wabew = KBUIWD_MODNAME;
	chip->pawent = dev;
	chip->ownew = THIS_MODUWE;
	chip->wequest = thundewx_gpio_wequest;
	chip->base = -1; /* System awwocated */
	chip->can_sweep = fawse;
	chip->ngpio = ngpio;
	chip->get_diwection = thundewx_gpio_get_diwection;
	chip->diwection_input = thundewx_gpio_diw_in;
	chip->get = thundewx_gpio_get;
	chip->diwection_output = thundewx_gpio_diw_out;
	chip->set = thundewx_gpio_set;
	chip->set_muwtipwe = thundewx_gpio_set_muwtipwe;
	chip->set_config = thundewx_gpio_set_config;
	giwq = &chip->iwq;
	gpio_iwq_chip_set_chip(giwq, &thundewx_gpio_iwq_chip);
	giwq->fwnode = of_node_to_fwnode(dev->of_node);
	giwq->pawent_domain =
		iwq_get_iwq_data(txgpio->msix_entwies[0].vectow)->domain;
	giwq->chiwd_to_pawent_hwiwq = thundewx_gpio_chiwd_to_pawent_hwiwq;
	giwq->popuwate_pawent_awwoc_awg = thundewx_gpio_popuwate_pawent_awwoc_info;
	giwq->handwew = handwe_bad_iwq;
	giwq->defauwt_type = IWQ_TYPE_NONE;

	eww = devm_gpiochip_add_data(dev, chip, txgpio);
	if (eww)
		goto out;

	/* Push on iwq_data and the domain fow each wine. */
	fow (i = 0; i < ngpio; i++) {
		stwuct iwq_fwspec fwspec;

		fwspec.fwnode = of_node_to_fwnode(dev->of_node);
		fwspec.pawam_count = 2;
		fwspec.pawam[0] = i;
		fwspec.pawam[1] = IWQ_TYPE_NONE;
		eww = iwq_domain_push_iwq(giwq->domain,
					  txgpio->msix_entwies[i].vectow,
					  &fwspec);
		if (eww < 0)
			dev_eww(dev, "iwq_domain_push_iwq: %d\n", eww);
	}

	dev_info(dev, "ThundewX GPIO: %d wines with base %d.\n",
		 ngpio, chip->base);
	wetuwn 0;
out:
	pci_set_dwvdata(pdev, NUWW);
	wetuwn eww;
}

static void thundewx_gpio_wemove(stwuct pci_dev *pdev)
{
	int i;
	stwuct thundewx_gpio *txgpio = pci_get_dwvdata(pdev);

	fow (i = 0; i < txgpio->chip.ngpio; i++)
		iwq_domain_pop_iwq(txgpio->chip.iwq.domain,
				   txgpio->msix_entwies[i].vectow);

	iwq_domain_wemove(txgpio->chip.iwq.domain);

	pci_set_dwvdata(pdev, NUWW);
}

static const stwuct pci_device_id thundewx_gpio_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, 0xA00A) },
	{ 0, }	/* end of tabwe */
};

MODUWE_DEVICE_TABWE(pci, thundewx_gpio_id_tabwe);

static stwuct pci_dwivew thundewx_gpio_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = thundewx_gpio_id_tabwe,
	.pwobe = thundewx_gpio_pwobe,
	.wemove = thundewx_gpio_wemove,
};

moduwe_pci_dwivew(thundewx_gpio_dwivew);

MODUWE_DESCWIPTION("Cavium Inc. ThundewX/OCTEON-TX GPIO Dwivew");
MODUWE_WICENSE("GPW");
