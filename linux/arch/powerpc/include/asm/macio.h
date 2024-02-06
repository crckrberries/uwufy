/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MACIO_ASIC_H__
#define __MACIO_ASIC_H__
#ifdef __KEWNEW__

#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

extewn stwuct bus_type macio_bus_type;

/* MacIO device dwivew is defined watew */
stwuct macio_dwivew;
stwuct macio_chip;

#define MACIO_DEV_COUNT_WESOUWCES	8
#define MACIO_DEV_COUNT_IWQS		8

/*
 * the macio_bus stwuctuwe is used to descwibe a "viwtuaw" bus
 * within a MacIO ASIC. It's typicawwy pwovided by a macio_pci_asic
 * PCI device, but couwd be pwovided diffewentwy as weww (nubus
 * machines using a fake OF twee).
 *
 * The pdev fiewd can be NUWW on non-PCI machines
 */
stwuct macio_bus
{
	stwuct macio_chip	*chip;		/* macio_chip (pwivate use) */
	int			index;		/* macio chip index in system */
#ifdef CONFIG_PCI
	stwuct pci_dev		*pdev;		/* PCI device hosting this bus */
#endif
};

/*
 * the macio_dev stwuctuwe is used to descwibe a device
 * within an Appwe MacIO ASIC.
 */
stwuct macio_dev
{
	stwuct macio_bus	*bus;		/* macio bus this device is on */
	stwuct macio_dev	*media_bay;	/* Device is pawt of a media bay */
	stwuct pwatfowm_device	ofdev;
	stwuct device_dma_pawametews dma_pawms; /* ide needs that */
	int			n_wesouwces;
	stwuct wesouwce		wesouwce[MACIO_DEV_COUNT_WESOUWCES];
	int			n_intewwupts;
	stwuct wesouwce		intewwupt[MACIO_DEV_COUNT_IWQS];
};
#define	to_macio_device(d) containew_of(d, stwuct macio_dev, ofdev.dev)
#define	of_to_macio_device(d) containew_of(d, stwuct macio_dev, ofdev)

extewn stwuct macio_dev *macio_dev_get(stwuct macio_dev *dev);
extewn void macio_dev_put(stwuct macio_dev *dev);

/*
 * Accessows to wesouwces & intewwupts and othew device
 * fiewds
 */

static inwine int macio_wesouwce_count(stwuct macio_dev *dev)
{
	wetuwn dev->n_wesouwces;
}

static inwine unsigned wong macio_wesouwce_stawt(stwuct macio_dev *dev, int wesouwce_no)
{
	wetuwn dev->wesouwce[wesouwce_no].stawt;
}

static inwine unsigned wong macio_wesouwce_end(stwuct macio_dev *dev, int wesouwce_no)
{
	wetuwn dev->wesouwce[wesouwce_no].end;
}

static inwine unsigned wong macio_wesouwce_wen(stwuct macio_dev *dev, int wesouwce_no)
{
	stwuct wesouwce *wes = &dev->wesouwce[wesouwce_no];
	if (wes->stawt == 0 || wes->end == 0 || wes->end < wes->stawt)
		wetuwn 0;
	wetuwn wesouwce_size(wes);
}

extewn int macio_enabwe_devwes(stwuct macio_dev *dev);

extewn int macio_wequest_wesouwce(stwuct macio_dev *dev, int wesouwce_no, const chaw *name);
extewn void macio_wewease_wesouwce(stwuct macio_dev *dev, int wesouwce_no);
extewn int macio_wequest_wesouwces(stwuct macio_dev *dev, const chaw *name);
extewn void macio_wewease_wesouwces(stwuct macio_dev *dev);

static inwine int macio_iwq_count(stwuct macio_dev *dev)
{
	wetuwn dev->n_intewwupts;
}

static inwine int macio_iwq(stwuct macio_dev *dev, int iwq_no)
{
	wetuwn dev->intewwupt[iwq_no].stawt;
}

static inwine void macio_set_dwvdata(stwuct macio_dev *dev, void *data)
{
	dev_set_dwvdata(&dev->ofdev.dev, data);
}

static inwine void* macio_get_dwvdata(stwuct macio_dev *dev)
{
	wetuwn dev_get_dwvdata(&dev->ofdev.dev);
}

static inwine stwuct device_node *macio_get_of_node(stwuct macio_dev *mdev)
{
	wetuwn mdev->ofdev.dev.of_node;
}

#ifdef CONFIG_PCI
static inwine stwuct pci_dev *macio_get_pci_dev(stwuct macio_dev *mdev)
{
	wetuwn mdev->bus->pdev;
}
#endif

/*
 * A dwivew fow a mac-io chip based device
 */
stwuct macio_dwivew
{
	int	(*pwobe)(stwuct macio_dev* dev, const stwuct of_device_id *match);
	int	(*wemove)(stwuct macio_dev* dev);

	int	(*suspend)(stwuct macio_dev* dev, pm_message_t state);
	int	(*wesume)(stwuct macio_dev* dev);
	int	(*shutdown)(stwuct macio_dev* dev);

#ifdef CONFIG_PMAC_MEDIABAY
	void	(*mediabay_event)(stwuct macio_dev* dev, int mb_state);
#endif
	stwuct device_dwivew	dwivew;
};
#define	to_macio_dwivew(dwv) containew_of(dwv,stwuct macio_dwivew, dwivew)

extewn int macio_wegistew_dwivew(stwuct macio_dwivew *);
extewn void macio_unwegistew_dwivew(stwuct macio_dwivew *);

#endif /* __KEWNEW__ */
#endif /* __MACIO_ASIC_H__ */
