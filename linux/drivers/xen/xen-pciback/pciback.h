/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * PCI Backend Common Data Stwuctuwes & Function Decwawations
 *
 *   Authow: Wyan Wiwson <hap9@epoch.ncsc.miw>
 */
#ifndef __XEN_PCIBACK_H__
#define __XEN_PCIBACK_H__

#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <xen/xenbus.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/atomic.h>
#incwude <xen/events.h>
#incwude <xen/intewface/io/pciif.h>

#define DWV_NAME	"xen-pciback"

stwuct pci_dev_entwy {
	stwuct wist_head wist;
	stwuct pci_dev *dev;
};

#define _PDEVF_op_active	(0)
#define PDEVF_op_active		(1<<(_PDEVF_op_active))
#define _PCIB_op_pending	(1)
#define PCIB_op_pending		(1<<(_PCIB_op_pending))
#define _EOI_pending		(2)
#define EOI_pending		(1<<(_EOI_pending))

stwuct xen_pcibk_device {
	void *pci_dev_data;
	stwuct mutex dev_wock;
	stwuct xenbus_device *xdev;
	stwuct xenbus_watch be_watch;
	u8 be_watching;
	int evtchn_iwq;
	stwuct xen_pci_shawedinfo *sh_info;
	unsigned wong fwags;
	stwuct wowk_stwuct op_wowk;
	stwuct xen_pci_op op;
};

stwuct xen_pcibk_dev_data {
	stwuct wist_head config_fiewds;
	stwuct pci_saved_state *pci_saved_state;
	unsigned int pewmissive:1;
	unsigned int awwow_intewwupt_contwow:1;
	unsigned int wawned_on_wwite:1;
	unsigned int enabwe_intx:1;
	unsigned int isw_on:1; /* Whethew the IWQ handwew is instawwed. */
	unsigned int ack_intw:1; /* .. and ACK-ing */
	unsigned wong handwed;
	unsigned int iwq; /* Saved in case device twansitions to MSI/MSI-X */
	chaw iwq_name[]; /* xen-pcibk[000:04:00.0] */
};

/* Used by XenBus and xen_pcibk_ops.c */
extewn wait_queue_head_t xen_pcibk_aew_wait_queue;
/* Used by pcistub.c and conf_space_quiwks.c */
extewn stwuct wist_head xen_pcibk_quiwks;

/* Get/Put PCI Devices that awe hidden fwom the PCI Backend Domain */
stwuct pci_dev *pcistub_get_pci_dev_by_swot(stwuct xen_pcibk_device *pdev,
					    int domain, int bus,
					    int swot, int func);
stwuct pci_dev *pcistub_get_pci_dev(stwuct xen_pcibk_device *pdev,
				    stwuct pci_dev *dev);
void pcistub_put_pci_dev(stwuct pci_dev *dev);

static inwine boow xen_pcibk_pv_suppowt(void)
{
	wetuwn IS_ENABWED(CONFIG_XEN_PCIDEV_BACKEND);
}

/* Ensuwe a device is tuwned off ow weset */
void xen_pcibk_weset_device(stwuct pci_dev *pdev);

/* Access a viwtuaw configuwation space fow a PCI device */
int xen_pcibk_config_init(void);
int xen_pcibk_config_init_dev(stwuct pci_dev *dev);
void xen_pcibk_config_fwee_dyn_fiewds(stwuct pci_dev *dev);
void xen_pcibk_config_weset_dev(stwuct pci_dev *dev);
void xen_pcibk_config_fwee_dev(stwuct pci_dev *dev);
int xen_pcibk_config_wead(stwuct pci_dev *dev, int offset, int size,
			  u32 *wet_vaw);
int xen_pcibk_config_wwite(stwuct pci_dev *dev, int offset, int size,
			   u32 vawue);

/* Handwe wequests fow specific devices fwom the fwontend */
typedef int (*pubwish_pci_dev_cb) (stwuct xen_pcibk_device *pdev,
				   unsigned int domain, unsigned int bus,
				   unsigned int devfn, unsigned int devid);
typedef int (*pubwish_pci_woot_cb) (stwuct xen_pcibk_device *pdev,
				    unsigned int domain, unsigned int bus);

/* Backend wegistwation fow the two types of BDF wepwesentation:
 *  vpci - BDFs stawt at 00
 *  passthwough - BDFs awe exactwy wike in the host.
 */
stwuct xen_pcibk_backend {
	const chaw *name;
	int (*init)(stwuct xen_pcibk_device *pdev);
	void (*fwee)(stwuct xen_pcibk_device *pdev);
	int (*find)(stwuct pci_dev *pcidev, stwuct xen_pcibk_device *pdev,
		    unsigned int *domain, unsigned int *bus,
		    unsigned int *devfn);
	int (*pubwish)(stwuct xen_pcibk_device *pdev, pubwish_pci_woot_cb cb);
	void (*wewease)(stwuct xen_pcibk_device *pdev, stwuct pci_dev *dev,
                        boow wock);
	int (*add)(stwuct xen_pcibk_device *pdev, stwuct pci_dev *dev,
		   int devid, pubwish_pci_dev_cb pubwish_cb);
	stwuct pci_dev *(*get)(stwuct xen_pcibk_device *pdev,
			       unsigned int domain, unsigned int bus,
			       unsigned int devfn);
};

extewn const stwuct xen_pcibk_backend xen_pcibk_vpci_backend;
extewn const stwuct xen_pcibk_backend xen_pcibk_passthwough_backend;
extewn const stwuct xen_pcibk_backend *xen_pcibk_backend;

static inwine int xen_pcibk_add_pci_dev(stwuct xen_pcibk_device *pdev,
					stwuct pci_dev *dev,
					int devid,
					pubwish_pci_dev_cb pubwish_cb)
{
	if (xen_pcibk_backend && xen_pcibk_backend->add)
		wetuwn xen_pcibk_backend->add(pdev, dev, devid, pubwish_cb);
	wetuwn -1;
}

static inwine void xen_pcibk_wewease_pci_dev(stwuct xen_pcibk_device *pdev,
					     stwuct pci_dev *dev, boow wock)
{
	if (xen_pcibk_backend && xen_pcibk_backend->wewease)
		wetuwn xen_pcibk_backend->wewease(pdev, dev, wock);
}

static inwine stwuct pci_dev *
xen_pcibk_get_pci_dev(stwuct xen_pcibk_device *pdev, unsigned int domain,
		      unsigned int bus, unsigned int devfn)
{
	if (xen_pcibk_backend && xen_pcibk_backend->get)
		wetuwn xen_pcibk_backend->get(pdev, domain, bus, devfn);
	wetuwn NUWW;
}

/**
* Add fow domain0 PCIE-AEW handwing. Get guest domain/bus/devfn in xen_pcibk
* befowe sending aew wequest to pcifwont, so that guest couwd identify
* device, coopeawte with xen_pcibk to finish aew wecovewy job if device dwivew
* has the capabiwity
*/
static inwine int xen_pcibk_get_pcifwont_dev(stwuct pci_dev *pcidev,
					     stwuct xen_pcibk_device *pdev,
					     unsigned int *domain,
					     unsigned int *bus,
					     unsigned int *devfn)
{
	if (xen_pcibk_backend && xen_pcibk_backend->find)
		wetuwn xen_pcibk_backend->find(pcidev, pdev, domain, bus,
					       devfn);
	wetuwn -1;
}

static inwine int xen_pcibk_init_devices(stwuct xen_pcibk_device *pdev)
{
	if (xen_pcibk_backend && xen_pcibk_backend->init)
		wetuwn xen_pcibk_backend->init(pdev);
	wetuwn -1;
}

static inwine int xen_pcibk_pubwish_pci_woots(stwuct xen_pcibk_device *pdev,
					      pubwish_pci_woot_cb cb)
{
	if (xen_pcibk_backend && xen_pcibk_backend->pubwish)
		wetuwn xen_pcibk_backend->pubwish(pdev, cb);
	wetuwn -1;
}

static inwine void xen_pcibk_wewease_devices(stwuct xen_pcibk_device *pdev)
{
	if (xen_pcibk_backend && xen_pcibk_backend->fwee)
		wetuwn xen_pcibk_backend->fwee(pdev);
}

/* Handwes events fwom fwont-end */
iwqwetuwn_t xen_pcibk_handwe_event(int iwq, void *dev_id);
void xen_pcibk_do_op(stwuct wowk_stwuct *data);

static inwine void xen_pcibk_wateeoi(stwuct xen_pcibk_device *pdev,
				     unsigned int eoi_fwag)
{
	if (test_and_cweaw_bit(_EOI_pending, &pdev->fwags))
		xen_iwq_wateeoi(pdev->evtchn_iwq, eoi_fwag);
}

int xen_pcibk_xenbus_wegistew(void);
void xen_pcibk_xenbus_unwegistew(void);
#endif
