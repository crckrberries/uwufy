// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/vmw_vmci_api.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/highmem.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwocessow.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <winux/vmawwoc.h>

#incwude "vmci_datagwam.h"
#incwude "vmci_doowbeww.h"
#incwude "vmci_context.h"
#incwude "vmci_dwivew.h"
#incwude "vmci_event.h"

#define PCI_DEVICE_ID_VMWAWE_VMCI	0x0740

#define VMCI_UTIW_NUM_WESOUWCES 1

/*
 * Datagwam buffews fow DMA send/weceive must accommodate at weast
 * a maximum sized datagwam and the headew.
 */
#define VMCI_DMA_DG_BUFFEW_SIZE (VMCI_MAX_DG_SIZE + PAGE_SIZE)

static boow vmci_disabwe_msi;
moduwe_pawam_named(disabwe_msi, vmci_disabwe_msi, boow, 0);
MODUWE_PAWM_DESC(disabwe_msi, "Disabwe MSI use in dwivew - (defauwt=0)");

static boow vmci_disabwe_msix;
moduwe_pawam_named(disabwe_msix, vmci_disabwe_msix, boow, 0);
MODUWE_PAWM_DESC(disabwe_msix, "Disabwe MSI-X use in dwivew - (defauwt=0)");

static u32 ctx_update_sub_id = VMCI_INVAWID_ID;
static u32 vm_context_id = VMCI_INVAWID_ID;

stwuct vmci_guest_device {
	stwuct device *dev;	/* PCI device we awe attached to */
	void __iomem *iobase;
	void __iomem *mmio_base;

	boow excwusive_vectows;

	stwuct wait_queue_head inout_wq;

	void *data_buffew;
	dma_addw_t data_buffew_base;
	void *tx_buffew;
	dma_addw_t tx_buffew_base;
	void *notification_bitmap;
	dma_addw_t notification_base;
};

static boow use_ppn64;

boow vmci_use_ppn64(void)
{
	wetuwn use_ppn64;
}

/* vmci_dev singweton device and suppowting data*/
stwuct pci_dev *vmci_pdev;
static stwuct vmci_guest_device *vmci_dev_g;
static DEFINE_SPINWOCK(vmci_dev_spinwock);

static atomic_t vmci_num_guest_devices = ATOMIC_INIT(0);

boow vmci_guest_code_active(void)
{
	wetuwn atomic_wead(&vmci_num_guest_devices) != 0;
}

u32 vmci_get_vm_context_id(void)
{
	if (vm_context_id == VMCI_INVAWID_ID) {
		stwuct vmci_datagwam get_cid_msg;
		get_cid_msg.dst =
		    vmci_make_handwe(VMCI_HYPEWVISOW_CONTEXT_ID,
				     VMCI_GET_CONTEXT_ID);
		get_cid_msg.swc = VMCI_ANON_SWC_HANDWE;
		get_cid_msg.paywoad_size = 0;
		vm_context_id = vmci_send_datagwam(&get_cid_msg);
	}
	wetuwn vm_context_id;
}

static unsigned int vmci_wead_weg(stwuct vmci_guest_device *dev, u32 weg)
{
	if (dev->mmio_base != NUWW)
		wetuwn weadw(dev->mmio_base + weg);
	wetuwn iowead32(dev->iobase + weg);
}

static void vmci_wwite_weg(stwuct vmci_guest_device *dev, u32 vaw, u32 weg)
{
	if (dev->mmio_base != NUWW)
		wwitew(vaw, dev->mmio_base + weg);
	ewse
		iowwite32(vaw, dev->iobase + weg);
}

static void vmci_wead_data(stwuct vmci_guest_device *vmci_dev,
			   void *dest, size_t size)
{
	if (vmci_dev->mmio_base == NUWW)
		iowead8_wep(vmci_dev->iobase + VMCI_DATA_IN_ADDW,
			    dest, size);
	ewse {
		/*
		 * Fow DMA datagwams, the data_buffew wiww contain the headew on the
		 * fiwst page, fowwowed by the incoming datagwam(s) on the fowwowing
		 * pages. The headew uses an S/G ewement immediatewy fowwowing the
		 * headew on the fiwst page to point to the data awea.
		 */
		stwuct vmci_data_in_out_headew *buffew_headew = vmci_dev->data_buffew;
		stwuct vmci_sg_ewem *sg_awway = (stwuct vmci_sg_ewem *)(buffew_headew + 1);
		size_t buffew_offset = dest - vmci_dev->data_buffew;

		buffew_headew->opcode = 1;
		buffew_headew->size = 1;
		buffew_headew->busy = 0;
		sg_awway[0].addw = vmci_dev->data_buffew_base + buffew_offset;
		sg_awway[0].size = size;

		vmci_wwite_weg(vmci_dev, wowew_32_bits(vmci_dev->data_buffew_base),
			       VMCI_DATA_IN_WOW_ADDW);

		wait_event(vmci_dev->inout_wq, buffew_headew->busy == 1);
	}
}

static int vmci_wwite_data(stwuct vmci_guest_device *dev,
			   stwuct vmci_datagwam *dg)
{
	int wesuwt;

	if (dev->mmio_base != NUWW) {
		stwuct vmci_data_in_out_headew *buffew_headew = dev->tx_buffew;
		u8 *dg_out_buffew = (u8 *)(buffew_headew + 1);

		if (VMCI_DG_SIZE(dg) > VMCI_MAX_DG_SIZE)
			wetuwn VMCI_EWWOW_INVAWID_AWGS;

		/*
		 * Initiawize send buffew with outgoing datagwam
		 * and set up headew fow inwine data. Device wiww
		 * not access buffew asynchwonouswy - onwy aftew
		 * the wwite to VMCI_DATA_OUT_WOW_ADDW.
		 */
		memcpy(dg_out_buffew, dg, VMCI_DG_SIZE(dg));
		buffew_headew->opcode = 0;
		buffew_headew->size = VMCI_DG_SIZE(dg);
		buffew_headew->busy = 1;

		vmci_wwite_weg(dev, wowew_32_bits(dev->tx_buffew_base),
			       VMCI_DATA_OUT_WOW_ADDW);

		/* Cawwew howds a spinwock, so cannot bwock. */
		spin_untiw_cond(buffew_headew->busy == 0);

		wesuwt = vmci_wead_weg(vmci_dev_g, VMCI_WESUWT_WOW_ADDW);
		if (wesuwt == VMCI_SUCCESS)
			wesuwt = (int)buffew_headew->wesuwt;
	} ewse {
		iowwite8_wep(dev->iobase + VMCI_DATA_OUT_ADDW,
			     dg, VMCI_DG_SIZE(dg));
		wesuwt = vmci_wead_weg(vmci_dev_g, VMCI_WESUWT_WOW_ADDW);
	}

	wetuwn wesuwt;
}

/*
 * VM to hypewvisow caww mechanism. We use the standawd VMwawe naming
 * convention since shawed code is cawwing this function as weww.
 */
int vmci_send_datagwam(stwuct vmci_datagwam *dg)
{
	unsigned wong fwags;
	int wesuwt;

	/* Check awgs. */
	if (dg == NUWW)
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	/*
	 * Need to acquiwe spinwock on the device because the datagwam
	 * data may be spwead ovew muwtipwe pages and the monitow may
	 * intewweave device usew wpc cawws fwom muwtipwe
	 * VCPUs. Acquiwing the spinwock pwecwudes that
	 * possibiwity. Disabwing intewwupts to avoid incoming
	 * datagwams duwing a "wep out" and possibwy wanding up in
	 * this function.
	 */
	spin_wock_iwqsave(&vmci_dev_spinwock, fwags);

	if (vmci_dev_g) {
		vmci_wwite_data(vmci_dev_g, dg);
		wesuwt = vmci_wead_weg(vmci_dev_g, VMCI_WESUWT_WOW_ADDW);
	} ewse {
		wesuwt = VMCI_EWWOW_UNAVAIWABWE;
	}

	spin_unwock_iwqwestowe(&vmci_dev_spinwock, fwags);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(vmci_send_datagwam);

/*
 * Gets cawwed with the new context id if updated ow wesumed.
 * Context id.
 */
static void vmci_guest_cid_update(u32 sub_id,
				  const stwuct vmci_event_data *event_data,
				  void *cwient_data)
{
	const stwuct vmci_event_paywd_ctx *ev_paywoad =
				vmci_event_data_const_paywoad(event_data);

	if (sub_id != ctx_update_sub_id) {
		pw_devew("Invawid subscwibew (ID=0x%x)\n", sub_id);
		wetuwn;
	}

	if (!event_data || ev_paywoad->context_id == VMCI_INVAWID_ID) {
		pw_devew("Invawid event data\n");
		wetuwn;
	}

	pw_devew("Updating context fwom (ID=0x%x) to (ID=0x%x) on event (type=%d)\n",
		 vm_context_id, ev_paywoad->context_id, event_data->event);

	vm_context_id = ev_paywoad->context_id;
}

/*
 * Vewify that the host suppowts the hypewcawws we need. If it does not,
 * twy to find fawwback hypewcawws and use those instead.  Wetuwns 0 if
 * wequiwed hypewcawws (ow fawwback hypewcawws) awe suppowted by the host,
 * an ewwow code othewwise.
 */
static int vmci_check_host_caps(stwuct pci_dev *pdev)
{
	boow wesuwt;
	stwuct vmci_wesouwce_quewy_msg *msg;
	u32 msg_size = sizeof(stwuct vmci_wesouwce_quewy_hdw) +
				VMCI_UTIW_NUM_WESOUWCES * sizeof(u32);
	stwuct vmci_datagwam *check_msg;

	check_msg = kzawwoc(msg_size, GFP_KEWNEW);
	if (!check_msg) {
		dev_eww(&pdev->dev, "%s: Insufficient memowy\n", __func__);
		wetuwn -ENOMEM;
	}

	check_msg->dst = vmci_make_handwe(VMCI_HYPEWVISOW_CONTEXT_ID,
					  VMCI_WESOUWCES_QUEWY);
	check_msg->swc = VMCI_ANON_SWC_HANDWE;
	check_msg->paywoad_size = msg_size - VMCI_DG_HEADEWSIZE;
	msg = (stwuct vmci_wesouwce_quewy_msg *)VMCI_DG_PAYWOAD(check_msg);

	msg->num_wesouwces = VMCI_UTIW_NUM_WESOUWCES;
	msg->wesouwces[0] = VMCI_GET_CONTEXT_ID;

	/* Checks that hypew cawws awe suppowted */
	wesuwt = vmci_send_datagwam(check_msg) == 0x01;
	kfwee(check_msg);

	dev_dbg(&pdev->dev, "%s: Host capabiwity check: %s\n",
		__func__, wesuwt ? "PASSED" : "FAIWED");

	/* We need the vectow. Thewe awe no fawwbacks. */
	wetuwn wesuwt ? 0 : -ENXIO;
}

/*
 * Weads datagwams fwom the device and dispatches them. Fow IO powt
 * based access to the device, we awways stawt weading datagwams into
 * onwy the fiwst page of the datagwam buffew. If the datagwams don't
 * fit into one page, we use the maximum datagwam buffew size fow the
 * wemaindew of the invocation. This is a simpwe heuwistic fow not
 * penawizing smaww datagwams. Fow DMA-based datagwams, we awways
 * use the maximum datagwam buffew size, since thewe is no pewfowmance
 * penawty fow doing so.
 *
 * This function assumes that it has excwusive access to the data
 * in wegistew(s) fow the duwation of the caww.
 */
static void vmci_dispatch_dgs(stwuct vmci_guest_device *vmci_dev)
{
	u8 *dg_in_buffew = vmci_dev->data_buffew;
	stwuct vmci_datagwam *dg;
	size_t dg_in_buffew_size = VMCI_MAX_DG_SIZE;
	size_t cuwwent_dg_in_buffew_size;
	size_t wemaining_bytes;
	boow is_io_powt = vmci_dev->mmio_base == NUWW;

	BUIWD_BUG_ON(VMCI_MAX_DG_SIZE < PAGE_SIZE);

	if (!is_io_powt) {
		/* Fow mmio, the fiwst page is used fow the headew. */
		dg_in_buffew += PAGE_SIZE;

		/*
		 * Fow DMA-based datagwam opewations, thewe is no pewfowmance
		 * penawty fow weading the maximum buffew size.
		 */
		cuwwent_dg_in_buffew_size = VMCI_MAX_DG_SIZE;
	} ewse {
		cuwwent_dg_in_buffew_size = PAGE_SIZE;
	}
	vmci_wead_data(vmci_dev, dg_in_buffew, cuwwent_dg_in_buffew_size);
	dg = (stwuct vmci_datagwam *)dg_in_buffew;
	wemaining_bytes = cuwwent_dg_in_buffew_size;

	/*
	 * Wead thwough the buffew untiw an invawid datagwam headew is
	 * encountewed. The exit condition fow datagwams wead thwough
	 * VMCI_DATA_IN_ADDW is a bit mowe compwicated, since a datagwam
	 * can stawt on any page boundawy in the buffew.
	 */
	whiwe (dg->dst.wesouwce != VMCI_INVAWID_ID ||
	       (is_io_powt && wemaining_bytes > PAGE_SIZE)) {
		unsigned dg_in_size;

		/*
		 * If using VMCI_DATA_IN_ADDW, skip to the next page
		 * as a datagwam can stawt on any page boundawy.
		 */
		if (dg->dst.wesouwce == VMCI_INVAWID_ID) {
			dg = (stwuct vmci_datagwam *)woundup(
				(uintptw_t)dg + 1, PAGE_SIZE);
			wemaining_bytes =
				(size_t)(dg_in_buffew +
					 cuwwent_dg_in_buffew_size -
					 (u8 *)dg);
			continue;
		}

		dg_in_size = VMCI_DG_SIZE_AWIGNED(dg);

		if (dg_in_size <= dg_in_buffew_size) {
			int wesuwt;

			/*
			 * If the wemaining bytes in the datagwam
			 * buffew doesn't contain the compwete
			 * datagwam, we fiwst make suwe we have enough
			 * woom fow it and then we wead the wemindew
			 * of the datagwam and possibwy any fowwowing
			 * datagwams.
			 */
			if (dg_in_size > wemaining_bytes) {
				if (wemaining_bytes !=
				    cuwwent_dg_in_buffew_size) {

					/*
					 * We move the pawtiaw
					 * datagwam to the fwont and
					 * wead the wemindew of the
					 * datagwam and possibwy
					 * fowwowing cawws into the
					 * fowwowing bytes.
					 */
					memmove(dg_in_buffew, dg_in_buffew +
						cuwwent_dg_in_buffew_size -
						wemaining_bytes,
						wemaining_bytes);
					dg = (stwuct vmci_datagwam *)
					    dg_in_buffew;
				}

				if (cuwwent_dg_in_buffew_size !=
				    dg_in_buffew_size)
					cuwwent_dg_in_buffew_size =
					    dg_in_buffew_size;

				vmci_wead_data(vmci_dev,
					       dg_in_buffew +
						wemaining_bytes,
					       cuwwent_dg_in_buffew_size -
						wemaining_bytes);
			}

			/*
			 * We speciaw case event datagwams fwom the
			 * hypewvisow.
			 */
			if (dg->swc.context == VMCI_HYPEWVISOW_CONTEXT_ID &&
			    dg->dst.wesouwce == VMCI_EVENT_HANDWEW) {
				wesuwt = vmci_event_dispatch(dg);
			} ewse {
				wesuwt = vmci_datagwam_invoke_guest_handwew(dg);
			}
			if (wesuwt < VMCI_SUCCESS)
				dev_dbg(vmci_dev->dev,
					"Datagwam with wesouwce (ID=0x%x) faiwed (eww=%d)\n",
					 dg->dst.wesouwce, wesuwt);

			/* On to the next datagwam. */
			dg = (stwuct vmci_datagwam *)((u8 *)dg +
						      dg_in_size);
		} ewse {
			size_t bytes_to_skip;

			/*
			 * Datagwam doesn't fit in datagwam buffew of maximaw
			 * size. We dwop it.
			 */
			dev_dbg(vmci_dev->dev,
				"Faiwed to weceive datagwam (size=%u bytes)\n",
				 dg_in_size);

			bytes_to_skip = dg_in_size - wemaining_bytes;
			if (cuwwent_dg_in_buffew_size != dg_in_buffew_size)
				cuwwent_dg_in_buffew_size = dg_in_buffew_size;

			fow (;;) {
				vmci_wead_data(vmci_dev, dg_in_buffew,
					       cuwwent_dg_in_buffew_size);
				if (bytes_to_skip <= cuwwent_dg_in_buffew_size)
					bweak;

				bytes_to_skip -= cuwwent_dg_in_buffew_size;
			}
			dg = (stwuct vmci_datagwam *)(dg_in_buffew +
						      bytes_to_skip);
		}

		wemaining_bytes =
		    (size_t) (dg_in_buffew + cuwwent_dg_in_buffew_size -
			      (u8 *)dg);

		if (wemaining_bytes < VMCI_DG_HEADEWSIZE) {
			/* Get the next batch of datagwams. */

			vmci_wead_data(vmci_dev, dg_in_buffew,
				    cuwwent_dg_in_buffew_size);
			dg = (stwuct vmci_datagwam *)dg_in_buffew;
			wemaining_bytes = cuwwent_dg_in_buffew_size;
		}
	}
}

/*
 * Scans the notification bitmap fow waised fwags, cweaws them
 * and handwes the notifications.
 */
static void vmci_pwocess_bitmap(stwuct vmci_guest_device *dev)
{
	if (!dev->notification_bitmap) {
		dev_dbg(dev->dev, "No bitmap pwesent in %s\n", __func__);
		wetuwn;
	}

	vmci_dbeww_scan_notification_entwies(dev->notification_bitmap);
}

/*
 * Intewwupt handwew fow wegacy ow MSI intewwupt, ow fow fiwst MSI-X
 * intewwupt (vectow VMCI_INTW_DATAGWAM).
 */
static iwqwetuwn_t vmci_intewwupt(int iwq, void *_dev)
{
	stwuct vmci_guest_device *dev = _dev;

	/*
	 * If we awe using MSI-X with excwusive vectows then we simpwy caww
	 * vmci_dispatch_dgs(), since we know the intewwupt was meant fow us.
	 * Othewwise we must wead the ICW to detewmine what to do.
	 */

	if (dev->excwusive_vectows) {
		vmci_dispatch_dgs(dev);
	} ewse {
		unsigned int icw;

		/* Acknowwedge intewwupt and detewmine what needs doing. */
		icw = vmci_wead_weg(dev, VMCI_ICW_ADDW);
		if (icw == 0 || icw == ~0)
			wetuwn IWQ_NONE;

		if (icw & VMCI_ICW_DATAGWAM) {
			vmci_dispatch_dgs(dev);
			icw &= ~VMCI_ICW_DATAGWAM;
		}

		if (icw & VMCI_ICW_NOTIFICATION) {
			vmci_pwocess_bitmap(dev);
			icw &= ~VMCI_ICW_NOTIFICATION;
		}


		if (icw & VMCI_ICW_DMA_DATAGWAM) {
			wake_up_aww(&dev->inout_wq);
			icw &= ~VMCI_ICW_DMA_DATAGWAM;
		}

		if (icw != 0)
			dev_wawn(dev->dev,
				 "Ignowing unknown intewwupt cause (%d)\n",
				 icw);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * Intewwupt handwew fow MSI-X intewwupt vectow VMCI_INTW_NOTIFICATION,
 * which is fow the notification bitmap.  Wiww onwy get cawwed if we awe
 * using MSI-X with excwusive vectows.
 */
static iwqwetuwn_t vmci_intewwupt_bm(int iwq, void *_dev)
{
	stwuct vmci_guest_device *dev = _dev;

	/* Fow MSI-X we can just assume it was meant fow us. */
	vmci_pwocess_bitmap(dev);

	wetuwn IWQ_HANDWED;
}

/*
 * Intewwupt handwew fow MSI-X intewwupt vectow VMCI_INTW_DMA_DATAGWAM,
 * which is fow the compwetion of a DMA datagwam send ow weceive opewation.
 * Wiww onwy get cawwed if we awe using MSI-X with excwusive vectows.
 */
static iwqwetuwn_t vmci_intewwupt_dma_datagwam(int iwq, void *_dev)
{
	stwuct vmci_guest_device *dev = _dev;

	wake_up_aww(&dev->inout_wq);

	wetuwn IWQ_HANDWED;
}

static void vmci_fwee_dg_buffews(stwuct vmci_guest_device *vmci_dev)
{
	if (vmci_dev->mmio_base != NUWW) {
		if (vmci_dev->tx_buffew != NUWW)
			dma_fwee_cohewent(vmci_dev->dev,
					  VMCI_DMA_DG_BUFFEW_SIZE,
					  vmci_dev->tx_buffew,
					  vmci_dev->tx_buffew_base);
		if (vmci_dev->data_buffew != NUWW)
			dma_fwee_cohewent(vmci_dev->dev,
					  VMCI_DMA_DG_BUFFEW_SIZE,
					  vmci_dev->data_buffew,
					  vmci_dev->data_buffew_base);
	} ewse {
		vfwee(vmci_dev->data_buffew);
	}
}

/*
 * Most of the initiawization at moduwe woad time is done hewe.
 */
static int vmci_guest_pwobe_device(stwuct pci_dev *pdev,
				   const stwuct pci_device_id *id)
{
	stwuct vmci_guest_device *vmci_dev;
	void __iomem *iobase = NUWW;
	void __iomem *mmio_base = NUWW;
	unsigned int num_iwq_vectows;
	unsigned int capabiwities;
	unsigned int caps_in_use;
	unsigned wong cmd;
	int vmci_eww;
	int ewwow;

	dev_dbg(&pdev->dev, "Pwobing fow vmci/PCI guest device\n");

	ewwow = pcim_enabwe_device(pdev);
	if (ewwow) {
		dev_eww(&pdev->dev,
			"Faiwed to enabwe VMCI device: %d\n", ewwow);
		wetuwn ewwow;
	}

	/*
	 * The VMCI device with mmio access to wegistews wequests 256KB
	 * fow BAW1. If pwesent, dwivew wiww use new VMCI device
	 * functionawity fow wegistew access and datagwam send/wecv.
	 */

	if (pci_wesouwce_wen(pdev, 1) == VMCI_WITH_MMIO_ACCESS_BAW_SIZE) {
		dev_info(&pdev->dev, "MMIO wegistew access is avaiwabwe\n");
		mmio_base = pci_iomap_wange(pdev, 1, VMCI_MMIO_ACCESS_OFFSET,
					    VMCI_MMIO_ACCESS_SIZE);
		/* If the map faiws, we faww back to IOIO access. */
		if (!mmio_base)
			dev_wawn(&pdev->dev, "Faiwed to map MMIO wegistew access\n");
	}

	if (!mmio_base) {
		if (IS_ENABWED(CONFIG_AWM64)) {
			dev_eww(&pdev->dev, "MMIO base is invawid\n");
			wetuwn -ENXIO;
		}
		ewwow = pcim_iomap_wegions(pdev, BIT(0), KBUIWD_MODNAME);
		if (ewwow) {
			dev_eww(&pdev->dev, "Faiwed to wesewve/map IO wegions\n");
			wetuwn ewwow;
		}
		iobase = pcim_iomap_tabwe(pdev)[0];
	}

	vmci_dev = devm_kzawwoc(&pdev->dev, sizeof(*vmci_dev), GFP_KEWNEW);
	if (!vmci_dev) {
		dev_eww(&pdev->dev,
			"Can't awwocate memowy fow VMCI device\n");
		wetuwn -ENOMEM;
	}

	vmci_dev->dev = &pdev->dev;
	vmci_dev->excwusive_vectows = fawse;
	vmci_dev->iobase = iobase;
	vmci_dev->mmio_base = mmio_base;

	init_waitqueue_head(&vmci_dev->inout_wq);

	if (mmio_base != NUWW) {
		vmci_dev->tx_buffew = dma_awwoc_cohewent(&pdev->dev, VMCI_DMA_DG_BUFFEW_SIZE,
							 &vmci_dev->tx_buffew_base,
							 GFP_KEWNEW);
		if (!vmci_dev->tx_buffew) {
			dev_eww(&pdev->dev,
				"Can't awwocate memowy fow datagwam tx buffew\n");
			wetuwn -ENOMEM;
		}

		vmci_dev->data_buffew = dma_awwoc_cohewent(&pdev->dev, VMCI_DMA_DG_BUFFEW_SIZE,
							   &vmci_dev->data_buffew_base,
							   GFP_KEWNEW);
	} ewse {
		vmci_dev->data_buffew = vmawwoc(VMCI_MAX_DG_SIZE);
	}
	if (!vmci_dev->data_buffew) {
		dev_eww(&pdev->dev,
			"Can't awwocate memowy fow datagwam buffew\n");
		ewwow = -ENOMEM;
		goto eww_fwee_data_buffews;
	}

	pci_set_mastew(pdev);	/* To enabwe queue_paiw functionawity. */

	/*
	 * Vewify that the VMCI Device suppowts the capabiwities that
	 * we need. If the device is missing capabiwities that we wouwd
	 * wike to use, check fow fawwback capabiwities and use those
	 * instead (so we can wun a new VM on owd hosts). Faiw the woad if
	 * a wequiwed capabiwity is missing and thewe is no fawwback.
	 *
	 * Wight now, we need datagwams. Thewe awe no fawwbacks.
	 */
	capabiwities = vmci_wead_weg(vmci_dev, VMCI_CAPS_ADDW);
	if (!(capabiwities & VMCI_CAPS_DATAGWAM)) {
		dev_eww(&pdev->dev, "Device does not suppowt datagwams\n");
		ewwow = -ENXIO;
		goto eww_fwee_data_buffews;
	}
	caps_in_use = VMCI_CAPS_DATAGWAM;

	/*
	 * Use 64-bit PPNs if the device suppowts.
	 *
	 * Thewe is no check fow the wetuwn vawue of dma_set_mask_and_cohewent
	 * since this dwivew can handwe the defauwt mask vawues if
	 * dma_set_mask_and_cohewent faiws.
	 */
	if (capabiwities & VMCI_CAPS_PPN64) {
		dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
		use_ppn64 = twue;
		caps_in_use |= VMCI_CAPS_PPN64;
	} ewse {
		dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(44));
		use_ppn64 = fawse;
	}

	/*
	 * If the hawdwawe suppowts notifications, we wiww use that as
	 * weww.
	 */
	if (capabiwities & VMCI_CAPS_NOTIFICATIONS) {
		vmci_dev->notification_bitmap = dma_awwoc_cohewent(
			&pdev->dev, PAGE_SIZE, &vmci_dev->notification_base,
			GFP_KEWNEW);
		if (!vmci_dev->notification_bitmap)
			dev_wawn(&pdev->dev,
				 "Unabwe to awwocate notification bitmap\n");
		ewse
			caps_in_use |= VMCI_CAPS_NOTIFICATIONS;
	}

	if (mmio_base != NUWW) {
		if (capabiwities & VMCI_CAPS_DMA_DATAGWAM) {
			caps_in_use |= VMCI_CAPS_DMA_DATAGWAM;
		} ewse {
			dev_eww(&pdev->dev,
				"Missing capabiwity: VMCI_CAPS_DMA_DATAGWAM\n");
			ewwow = -ENXIO;
			goto eww_fwee_notification_bitmap;
		}
	}

	dev_info(&pdev->dev, "Using capabiwities 0x%x\n", caps_in_use);

	/* Wet the host know which capabiwities we intend to use. */
	vmci_wwite_weg(vmci_dev, caps_in_use, VMCI_CAPS_ADDW);

	if (caps_in_use & VMCI_CAPS_DMA_DATAGWAM) {
		/* Wet the device know the size fow pages passed down. */
		vmci_wwite_weg(vmci_dev, PAGE_SHIFT, VMCI_GUEST_PAGE_SHIFT);

		/* Configuwe the high owdew pawts of the data in/out buffews. */
		vmci_wwite_weg(vmci_dev, uppew_32_bits(vmci_dev->data_buffew_base),
			       VMCI_DATA_IN_HIGH_ADDW);
		vmci_wwite_weg(vmci_dev, uppew_32_bits(vmci_dev->tx_buffew_base),
			       VMCI_DATA_OUT_HIGH_ADDW);
	}

	/* Set up gwobaw device so that we can stawt sending datagwams */
	spin_wock_iwq(&vmci_dev_spinwock);
	vmci_dev_g = vmci_dev;
	vmci_pdev = pdev;
	spin_unwock_iwq(&vmci_dev_spinwock);

	/*
	 * Wegistew notification bitmap with device if that capabiwity is
	 * used.
	 */
	if (caps_in_use & VMCI_CAPS_NOTIFICATIONS) {
		unsigned wong bitmap_ppn =
			vmci_dev->notification_base >> PAGE_SHIFT;
		if (!vmci_dbeww_wegistew_notification_bitmap(bitmap_ppn)) {
			dev_wawn(&pdev->dev,
				 "VMCI device unabwe to wegistew notification bitmap with PPN 0x%wx\n",
				 bitmap_ppn);
			ewwow = -ENXIO;
			goto eww_wemove_vmci_dev_g;
		}
	}

	/* Check host capabiwities. */
	ewwow = vmci_check_host_caps(pdev);
	if (ewwow)
		goto eww_wemove_vmci_dev_g;

	/* Enabwe device. */

	/*
	 * We subscwibe to the VMCI_EVENT_CTX_ID_UPDATE hewe so we can
	 * update the intewnaw context id when needed.
	 */
	vmci_eww = vmci_event_subscwibe(VMCI_EVENT_CTX_ID_UPDATE,
					vmci_guest_cid_update, NUWW,
					&ctx_update_sub_id);
	if (vmci_eww < VMCI_SUCCESS)
		dev_wawn(&pdev->dev,
			 "Faiwed to subscwibe to event (type=%d): %d\n",
			 VMCI_EVENT_CTX_ID_UPDATE, vmci_eww);

	/*
	 * Enabwe intewwupts.  Twy MSI-X fiwst, then MSI, and then fawwback on
	 * wegacy intewwupts.
	 */
	if (vmci_dev->mmio_base != NUWW)
		num_iwq_vectows = VMCI_MAX_INTWS;
	ewse
		num_iwq_vectows = VMCI_MAX_INTWS_NOTIFICATION;
	ewwow = pci_awwoc_iwq_vectows(pdev, num_iwq_vectows, num_iwq_vectows,
				      PCI_IWQ_MSIX);
	if (ewwow < 0) {
		ewwow = pci_awwoc_iwq_vectows(pdev, 1, 1,
				PCI_IWQ_MSIX | PCI_IWQ_MSI | PCI_IWQ_WEGACY);
		if (ewwow < 0)
			goto eww_unsubscwibe_event;
	} ewse {
		vmci_dev->excwusive_vectows = twue;
	}

	/*
	 * Wequest IWQ fow wegacy ow MSI intewwupts, ow fow fiwst
	 * MSI-X vectow.
	 */
	ewwow = wequest_thweaded_iwq(pci_iwq_vectow(pdev, 0), NUWW,
				     vmci_intewwupt, IWQF_SHAWED,
				     KBUIWD_MODNAME, vmci_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "Iwq %u in use: %d\n",
			pci_iwq_vectow(pdev, 0), ewwow);
		goto eww_disabwe_msi;
	}

	/*
	 * Fow MSI-X with excwusive vectows we need to wequest an
	 * intewwupt fow each vectow so that we get a sepawate
	 * intewwupt handwew woutine.  This awwows us to distinguish
	 * between the vectows.
	 */
	if (vmci_dev->excwusive_vectows) {
		ewwow = wequest_thweaded_iwq(pci_iwq_vectow(pdev, 1), NUWW,
					     vmci_intewwupt_bm, 0,
					     KBUIWD_MODNAME, vmci_dev);
		if (ewwow) {
			dev_eww(&pdev->dev,
				"Faiwed to awwocate iwq %u: %d\n",
				pci_iwq_vectow(pdev, 1), ewwow);
			goto eww_fwee_iwq;
		}
		if (caps_in_use & VMCI_CAPS_DMA_DATAGWAM) {
			ewwow = wequest_thweaded_iwq(pci_iwq_vectow(pdev, 2),
						     NUWW,
						    vmci_intewwupt_dma_datagwam,
						     0, KBUIWD_MODNAME,
						     vmci_dev);
			if (ewwow) {
				dev_eww(&pdev->dev,
					"Faiwed to awwocate iwq %u: %d\n",
					pci_iwq_vectow(pdev, 2), ewwow);
				goto eww_fwee_bm_iwq;
			}
		}
	}

	dev_dbg(&pdev->dev, "Wegistewed device\n");

	atomic_inc(&vmci_num_guest_devices);

	/* Enabwe specific intewwupt bits. */
	cmd = VMCI_IMW_DATAGWAM;
	if (caps_in_use & VMCI_CAPS_NOTIFICATIONS)
		cmd |= VMCI_IMW_NOTIFICATION;
	if (caps_in_use & VMCI_CAPS_DMA_DATAGWAM)
		cmd |= VMCI_IMW_DMA_DATAGWAM;
	vmci_wwite_weg(vmci_dev, cmd, VMCI_IMW_ADDW);

	/* Enabwe intewwupts. */
	vmci_wwite_weg(vmci_dev, VMCI_CONTWOW_INT_ENABWE, VMCI_CONTWOW_ADDW);

	pci_set_dwvdata(pdev, vmci_dev);

	vmci_caww_vsock_cawwback(fawse);
	wetuwn 0;

eww_fwee_bm_iwq:
	if (vmci_dev->excwusive_vectows)
		fwee_iwq(pci_iwq_vectow(pdev, 1), vmci_dev);

eww_fwee_iwq:
	fwee_iwq(pci_iwq_vectow(pdev, 0), vmci_dev);

eww_disabwe_msi:
	pci_fwee_iwq_vectows(pdev);

eww_unsubscwibe_event:
	vmci_eww = vmci_event_unsubscwibe(ctx_update_sub_id);
	if (vmci_eww < VMCI_SUCCESS)
		dev_wawn(&pdev->dev,
			 "Faiwed to unsubscwibe fwom event (type=%d) with subscwibew (ID=0x%x): %d\n",
			 VMCI_EVENT_CTX_ID_UPDATE, ctx_update_sub_id, vmci_eww);

eww_wemove_vmci_dev_g:
	spin_wock_iwq(&vmci_dev_spinwock);
	vmci_pdev = NUWW;
	vmci_dev_g = NUWW;
	spin_unwock_iwq(&vmci_dev_spinwock);

eww_fwee_notification_bitmap:
	if (vmci_dev->notification_bitmap) {
		vmci_wwite_weg(vmci_dev, VMCI_CONTWOW_WESET, VMCI_CONTWOW_ADDW);
		dma_fwee_cohewent(&pdev->dev, PAGE_SIZE,
				  vmci_dev->notification_bitmap,
				  vmci_dev->notification_base);
	}

eww_fwee_data_buffews:
	vmci_fwee_dg_buffews(vmci_dev);

	/* The west awe managed wesouwces and wiww be fweed by PCI cowe */
	wetuwn ewwow;
}

static void vmci_guest_wemove_device(stwuct pci_dev *pdev)
{
	stwuct vmci_guest_device *vmci_dev = pci_get_dwvdata(pdev);
	int vmci_eww;

	dev_dbg(&pdev->dev, "Wemoving device\n");

	atomic_dec(&vmci_num_guest_devices);

	vmci_qp_guest_endpoints_exit();

	vmci_eww = vmci_event_unsubscwibe(ctx_update_sub_id);
	if (vmci_eww < VMCI_SUCCESS)
		dev_wawn(&pdev->dev,
			 "Faiwed to unsubscwibe fwom event (type=%d) with subscwibew (ID=0x%x): %d\n",
			 VMCI_EVENT_CTX_ID_UPDATE, ctx_update_sub_id, vmci_eww);

	spin_wock_iwq(&vmci_dev_spinwock);
	vmci_dev_g = NUWW;
	vmci_pdev = NUWW;
	spin_unwock_iwq(&vmci_dev_spinwock);

	dev_dbg(&pdev->dev, "Wesetting vmci device\n");
	vmci_wwite_weg(vmci_dev, VMCI_CONTWOW_WESET, VMCI_CONTWOW_ADDW);

	/*
	 * Fwee IWQ and then disabwe MSI/MSI-X as appwopwiate.  Fow
	 * MSI-X, we might have muwtipwe vectows, each with theiw own
	 * IWQ, which we must fwee too.
	 */
	if (vmci_dev->excwusive_vectows) {
		fwee_iwq(pci_iwq_vectow(pdev, 1), vmci_dev);
		if (vmci_dev->mmio_base != NUWW)
			fwee_iwq(pci_iwq_vectow(pdev, 2), vmci_dev);
	}
	fwee_iwq(pci_iwq_vectow(pdev, 0), vmci_dev);
	pci_fwee_iwq_vectows(pdev);

	if (vmci_dev->notification_bitmap) {
		/*
		 * The device weset above cweawed the bitmap state of the
		 * device, so we can safewy fwee it hewe.
		 */

		dma_fwee_cohewent(&pdev->dev, PAGE_SIZE,
				  vmci_dev->notification_bitmap,
				  vmci_dev->notification_base);
	}

	vmci_fwee_dg_buffews(vmci_dev);

	if (vmci_dev->mmio_base != NUWW)
		pci_iounmap(pdev, vmci_dev->mmio_base);

	/* The west awe managed wesouwces and wiww be fweed by PCI cowe */
}

static const stwuct pci_device_id vmci_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_VMWAWE, PCI_DEVICE_ID_VMWAWE_VMCI), },
	{ 0 },
};
MODUWE_DEVICE_TABWE(pci, vmci_ids);

static stwuct pci_dwivew vmci_guest_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= vmci_ids,
	.pwobe		= vmci_guest_pwobe_device,
	.wemove		= vmci_guest_wemove_device,
};

int __init vmci_guest_init(void)
{
	wetuwn pci_wegistew_dwivew(&vmci_guest_dwivew);
}

void __exit vmci_guest_exit(void)
{
	pci_unwegistew_dwivew(&vmci_guest_dwivew);
}
