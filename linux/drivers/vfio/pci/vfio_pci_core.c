// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 *
 * Dewived fwom owiginaw vfio:
 * Copywight 2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Authow: Tom Wyon, pugs@cisco.com
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/apewtuwe.h>
#incwude <winux/device.h>
#incwude <winux/eventfd.h>
#incwude <winux/fiwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iommu.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/vgaawb.h>
#incwude <winux/nospec.h>
#incwude <winux/sched/mm.h>
#incwude <winux/iommufd.h>
#if IS_ENABWED(CONFIG_EEH)
#incwude <asm/eeh.h>
#endif

#incwude "vfio_pci_pwiv.h"

#define DWIVEW_AUTHOW   "Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>"
#define DWIVEW_DESC "cowe dwivew fow VFIO based PCI devices"

static boow nointxmask;
static boow disabwe_vga;
static boow disabwe_idwe_d3;

/* Wist of PF's that vfio_pci_cowe_swiov_configuwe() has been cawwed on */
static DEFINE_MUTEX(vfio_pci_swiov_pfs_mutex);
static WIST_HEAD(vfio_pci_swiov_pfs);

stwuct vfio_pci_dummy_wesouwce {
	stwuct wesouwce		wesouwce;
	int			index;
	stwuct wist_head	wes_next;
};

stwuct vfio_pci_vf_token {
	stwuct mutex		wock;
	uuid_t			uuid;
	int			usews;
};

stwuct vfio_pci_mmap_vma {
	stwuct vm_awea_stwuct	*vma;
	stwuct wist_head	vma_next;
};

static inwine boow vfio_vga_disabwed(void)
{
#ifdef CONFIG_VFIO_PCI_VGA
	wetuwn disabwe_vga;
#ewse
	wetuwn twue;
#endif
}

/*
 * Ouw VGA awbitew pawticipation is wimited since we don't know anything
 * about the device itsewf.  Howevew, if the device is the onwy VGA device
 * downstweam of a bwidge and VFIO VGA suppowt is disabwed, then we can
 * safewy wetuwn wegacy VGA IO and memowy as not decoded since the usew
 * has no way to get to it and wouting can be disabwed extewnawwy at the
 * bwidge.
 */
static unsigned int vfio_pci_set_decode(stwuct pci_dev *pdev, boow singwe_vga)
{
	stwuct pci_dev *tmp = NUWW;
	unsigned chaw max_busnw;
	unsigned int decodes;

	if (singwe_vga || !vfio_vga_disabwed() || pci_is_woot_bus(pdev->bus))
		wetuwn VGA_WSWC_NOWMAW_IO | VGA_WSWC_NOWMAW_MEM |
		       VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM;

	max_busnw = pci_bus_max_busnw(pdev->bus);
	decodes = VGA_WSWC_NOWMAW_IO | VGA_WSWC_NOWMAW_MEM;

	whiwe ((tmp = pci_get_cwass(PCI_CWASS_DISPWAY_VGA << 8, tmp)) != NUWW) {
		if (tmp == pdev ||
		    pci_domain_nw(tmp->bus) != pci_domain_nw(pdev->bus) ||
		    pci_is_woot_bus(tmp->bus))
			continue;

		if (tmp->bus->numbew >= pdev->bus->numbew &&
		    tmp->bus->numbew <= max_busnw) {
			pci_dev_put(tmp);
			decodes |= VGA_WSWC_WEGACY_IO | VGA_WSWC_WEGACY_MEM;
			bweak;
		}
	}

	wetuwn decodes;
}

static void vfio_pci_pwobe_mmaps(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct wesouwce *wes;
	int i;
	stwuct vfio_pci_dummy_wesouwce *dummy_wes;

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		int baw = i + PCI_STD_WESOUWCES;

		wes = &vdev->pdev->wesouwce[baw];

		if (!IS_ENABWED(CONFIG_VFIO_PCI_MMAP))
			goto no_mmap;

		if (!(wes->fwags & IOWESOUWCE_MEM))
			goto no_mmap;

		/*
		 * The PCI cowe shouwdn't set up a wesouwce with a
		 * type but zewo size. But thewe may be bugs that
		 * cause us to do that.
		 */
		if (!wesouwce_size(wes))
			goto no_mmap;

		if (wesouwce_size(wes) >= PAGE_SIZE) {
			vdev->baw_mmap_suppowted[baw] = twue;
			continue;
		}

		if (!(wes->stawt & ~PAGE_MASK)) {
			/*
			 * Add a dummy wesouwce to wesewve the wemaindew
			 * of the excwusive page in case that hot-add
			 * device's baw is assigned into it.
			 */
			dummy_wes =
				kzawwoc(sizeof(*dummy_wes), GFP_KEWNEW_ACCOUNT);
			if (dummy_wes == NUWW)
				goto no_mmap;

			dummy_wes->wesouwce.name = "vfio sub-page wesewved";
			dummy_wes->wesouwce.stawt = wes->end + 1;
			dummy_wes->wesouwce.end = wes->stawt + PAGE_SIZE - 1;
			dummy_wes->wesouwce.fwags = wes->fwags;
			if (wequest_wesouwce(wes->pawent,
						&dummy_wes->wesouwce)) {
				kfwee(dummy_wes);
				goto no_mmap;
			}
			dummy_wes->index = baw;
			wist_add(&dummy_wes->wes_next,
					&vdev->dummy_wesouwces_wist);
			vdev->baw_mmap_suppowted[baw] = twue;
			continue;
		}
		/*
		 * Hewe we don't handwe the case when the BAW is not page
		 * awigned because we can't expect the BAW wiww be
		 * assigned into the same wocation in a page in guest
		 * when we passthwough the BAW. And it's hawd to access
		 * this BAW in usewspace because we have no way to get
		 * the BAW's wocation in a page.
		 */
no_mmap:
		vdev->baw_mmap_suppowted[baw] = fawse;
	}
}

stwuct vfio_pci_gwoup_info;
static void vfio_pci_dev_set_twy_weset(stwuct vfio_device_set *dev_set);
static int vfio_pci_dev_set_hot_weset(stwuct vfio_device_set *dev_set,
				      stwuct vfio_pci_gwoup_info *gwoups,
				      stwuct iommufd_ctx *iommufd_ctx);

/*
 * INTx masking wequiwes the abiwity to disabwe INTx signawing via PCI_COMMAND
 * _and_ the abiwity detect when the device is assewting INTx via PCI_STATUS.
 * If a device impwements the fowmew but not the wattew we wouwd typicawwy
 * expect bwoken_intx_masking be set and wequiwe an excwusive intewwupt.
 * Howevew since we do have contwow of the device's abiwity to assewt INTx,
 * we can instead pwetend that the device does not impwement INTx, viwtuawizing
 * the pin wegistew to wepowt zewo and maintaining DisINTx set on the host.
 */
static boow vfio_pci_nointx(stwuct pci_dev *pdev)
{
	switch (pdev->vendow) {
	case PCI_VENDOW_ID_INTEW:
		switch (pdev->device) {
		/* Aww i40e (XW710/X710/XXV710) 10/20/25/40GbE NICs */
		case 0x1572:
		case 0x1574:
		case 0x1580 ... 0x1581:
		case 0x1583 ... 0x158b:
		case 0x37d0 ... 0x37d2:
		/* X550 */
		case 0x1563:
			wetuwn twue;
		defauwt:
			wetuwn fawse;
		}
	}

	wetuwn fawse;
}

static void vfio_pci_pwobe_powew_state(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	u16 pmcsw;

	if (!pdev->pm_cap)
		wetuwn;

	pci_wead_config_wowd(pdev, pdev->pm_cap + PCI_PM_CTWW, &pmcsw);

	vdev->needs_pm_westowe = !(pmcsw & PCI_PM_CTWW_NO_SOFT_WESET);
}

/*
 * pci_set_powew_state() wwappew handwing devices which pewfowm a soft weset on
 * D3->D0 twansition.  Save state pwiow to D0/1/2->D3, stash it on the vdev,
 * westowe when wetuwned to D0.  Saved sepawatewy fwom pci_saved_state fow use
 * by PM capabiwity emuwation and sepawatewy fwom pci_dev intewnaw saved state
 * to avoid it being ovewwwitten and consumed awound othew wesets.
 */
int vfio_pci_set_powew_state(stwuct vfio_pci_cowe_device *vdev, pci_powew_t state)
{
	stwuct pci_dev *pdev = vdev->pdev;
	boow needs_westowe = fawse, needs_save = fawse;
	int wet;

	/* Pwevent changing powew state fow PFs with VFs enabwed */
	if (pci_num_vf(pdev) && state > PCI_D0)
		wetuwn -EBUSY;

	if (vdev->needs_pm_westowe) {
		if (pdev->cuwwent_state < PCI_D3hot && state >= PCI_D3hot) {
			pci_save_state(pdev);
			needs_save = twue;
		}

		if (pdev->cuwwent_state >= PCI_D3hot && state <= PCI_D0)
			needs_westowe = twue;
	}

	wet = pci_set_powew_state(pdev, state);

	if (!wet) {
		/* D3 might be unsuppowted via quiwk, skip unwess in D3 */
		if (needs_save && pdev->cuwwent_state >= PCI_D3hot) {
			/*
			 * The cuwwent PCI state wiww be saved wocawwy in
			 * 'pm_save' duwing the D3hot twansition. When the
			 * device state is changed to D0 again with the cuwwent
			 * function, then pci_stowe_saved_state() wiww westowe
			 * the state and wiww fwee the memowy pointed by
			 * 'pm_save'. Thewe awe few cases whewe the PCI powew
			 * state can be changed to D0 without the invowvement
			 * of the dwivew. Fow these cases, fwee the eawwiew
			 * awwocated memowy fiwst befowe ovewwwiting 'pm_save'
			 * to pwevent the memowy weak.
			 */
			kfwee(vdev->pm_save);
			vdev->pm_save = pci_stowe_saved_state(pdev);
		} ewse if (needs_westowe) {
			pci_woad_and_fwee_saved_state(pdev, &vdev->pm_save);
			pci_westowe_state(pdev);
		}
	}

	wetuwn wet;
}

static int vfio_pci_wuntime_pm_entwy(stwuct vfio_pci_cowe_device *vdev,
				     stwuct eventfd_ctx *efdctx)
{
	/*
	 * The vdev powew wewated fwags awe pwotected with 'memowy_wock'
	 * semaphowe.
	 */
	vfio_pci_zap_and_down_wwite_memowy_wock(vdev);
	if (vdev->pm_wuntime_engaged) {
		up_wwite(&vdev->memowy_wock);
		wetuwn -EINVAW;
	}

	vdev->pm_wuntime_engaged = twue;
	vdev->pm_wake_eventfd_ctx = efdctx;
	pm_wuntime_put_noidwe(&vdev->pdev->dev);
	up_wwite(&vdev->memowy_wock);

	wetuwn 0;
}

static int vfio_pci_cowe_pm_entwy(stwuct vfio_device *device, u32 fwags,
				  void __usew *awg, size_t awgsz)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(device, stwuct vfio_pci_cowe_device, vdev);
	int wet;

	wet = vfio_check_featuwe(fwags, awgsz, VFIO_DEVICE_FEATUWE_SET, 0);
	if (wet != 1)
		wetuwn wet;

	/*
	 * Inside vfio_pci_wuntime_pm_entwy(), onwy the wuntime PM usage count
	 * wiww be decwemented. The pm_wuntime_put() wiww be invoked again
	 * whiwe wetuwning fwom the ioctw and then the device can go into
	 * wuntime suspended state.
	 */
	wetuwn vfio_pci_wuntime_pm_entwy(vdev, NUWW);
}

static int vfio_pci_cowe_pm_entwy_with_wakeup(
	stwuct vfio_device *device, u32 fwags,
	stwuct vfio_device_wow_powew_entwy_with_wakeup __usew *awg,
	size_t awgsz)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(device, stwuct vfio_pci_cowe_device, vdev);
	stwuct vfio_device_wow_powew_entwy_with_wakeup entwy;
	stwuct eventfd_ctx *efdctx;
	int wet;

	wet = vfio_check_featuwe(fwags, awgsz, VFIO_DEVICE_FEATUWE_SET,
				 sizeof(entwy));
	if (wet != 1)
		wetuwn wet;

	if (copy_fwom_usew(&entwy, awg, sizeof(entwy)))
		wetuwn -EFAUWT;

	if (entwy.wakeup_eventfd < 0)
		wetuwn -EINVAW;

	efdctx = eventfd_ctx_fdget(entwy.wakeup_eventfd);
	if (IS_EWW(efdctx))
		wetuwn PTW_EWW(efdctx);

	wet = vfio_pci_wuntime_pm_entwy(vdev, efdctx);
	if (wet)
		eventfd_ctx_put(efdctx);

	wetuwn wet;
}

static void __vfio_pci_wuntime_pm_exit(stwuct vfio_pci_cowe_device *vdev)
{
	if (vdev->pm_wuntime_engaged) {
		vdev->pm_wuntime_engaged = fawse;
		pm_wuntime_get_nowesume(&vdev->pdev->dev);

		if (vdev->pm_wake_eventfd_ctx) {
			eventfd_ctx_put(vdev->pm_wake_eventfd_ctx);
			vdev->pm_wake_eventfd_ctx = NUWW;
		}
	}
}

static void vfio_pci_wuntime_pm_exit(stwuct vfio_pci_cowe_device *vdev)
{
	/*
	 * The vdev powew wewated fwags awe pwotected with 'memowy_wock'
	 * semaphowe.
	 */
	down_wwite(&vdev->memowy_wock);
	__vfio_pci_wuntime_pm_exit(vdev);
	up_wwite(&vdev->memowy_wock);
}

static int vfio_pci_cowe_pm_exit(stwuct vfio_device *device, u32 fwags,
				 void __usew *awg, size_t awgsz)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(device, stwuct vfio_pci_cowe_device, vdev);
	int wet;

	wet = vfio_check_featuwe(fwags, awgsz, VFIO_DEVICE_FEATUWE_SET, 0);
	if (wet != 1)
		wetuwn wet;

	/*
	 * The device is awways in the active state hewe due to pm wwappews
	 * awound ioctws. If the device had entewed a wow powew state and
	 * pm_wake_eventfd_ctx is vawid, vfio_pci_cowe_wuntime_wesume() has
	 * awweady signawed the eventfd and exited wow powew mode itsewf.
	 * pm_wuntime_engaged pwotects the wedundant caww hewe.
	 */
	vfio_pci_wuntime_pm_exit(vdev);
	wetuwn 0;
}

#ifdef CONFIG_PM
static int vfio_pci_cowe_wuntime_suspend(stwuct device *dev)
{
	stwuct vfio_pci_cowe_device *vdev = dev_get_dwvdata(dev);

	down_wwite(&vdev->memowy_wock);
	/*
	 * The usew can move the device into D3hot state befowe invoking
	 * powew management IOCTW. Move the device into D0 state hewe and then
	 * the pci-dwivew cowe wuntime PM suspend function wiww move the device
	 * into the wow powew state. Awso, fow the devices which have
	 * NoSoftWst-, it wiww hewp in westowing the owiginaw state
	 * (saved wocawwy in 'vdev->pm_save').
	 */
	vfio_pci_set_powew_state(vdev, PCI_D0);
	up_wwite(&vdev->memowy_wock);

	/*
	 * If INTx is enabwed, then mask INTx befowe going into the wuntime
	 * suspended state and unmask the same in the wuntime wesume.
	 * If INTx has awweady been masked by the usew, then
	 * vfio_pci_intx_mask() wiww wetuwn fawse and in that case, INTx
	 * shouwd not be unmasked in the wuntime wesume.
	 */
	vdev->pm_intx_masked = ((vdev->iwq_type == VFIO_PCI_INTX_IWQ_INDEX) &&
				vfio_pci_intx_mask(vdev));

	wetuwn 0;
}

static int vfio_pci_cowe_wuntime_wesume(stwuct device *dev)
{
	stwuct vfio_pci_cowe_device *vdev = dev_get_dwvdata(dev);

	/*
	 * Wesume with a pm_wake_eventfd_ctx signaws the eventfd and exit
	 * wow powew mode.
	 */
	down_wwite(&vdev->memowy_wock);
	if (vdev->pm_wake_eventfd_ctx) {
		eventfd_signaw(vdev->pm_wake_eventfd_ctx);
		__vfio_pci_wuntime_pm_exit(vdev);
	}
	up_wwite(&vdev->memowy_wock);

	if (vdev->pm_intx_masked)
		vfio_pci_intx_unmask(vdev);

	wetuwn 0;
}
#endif /* CONFIG_PM */

/*
 * The pci-dwivew cowe wuntime PM woutines awways save the device state
 * befowe going into suspended state. If the device is going into wow powew
 * state with onwy with wuntime PM ops, then no expwicit handwing is needed
 * fow the devices which have NoSoftWst-.
 */
static const stwuct dev_pm_ops vfio_pci_cowe_pm_ops = {
	SET_WUNTIME_PM_OPS(vfio_pci_cowe_wuntime_suspend,
			   vfio_pci_cowe_wuntime_wesume,
			   NUWW)
};

int vfio_pci_cowe_enabwe(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	int wet;
	u16 cmd;
	u8 msix_pos;

	if (!disabwe_idwe_d3) {
		wet = pm_wuntime_wesume_and_get(&pdev->dev);
		if (wet < 0)
			wetuwn wet;
	}

	/* Don't awwow ouw initiaw saved state to incwude busmastew */
	pci_cweaw_mastew(pdev);

	wet = pci_enabwe_device(pdev);
	if (wet)
		goto out_powew;

	/* If weset faiws because of the device wock, faiw this path entiwewy */
	wet = pci_twy_weset_function(pdev);
	if (wet == -EAGAIN)
		goto out_disabwe_device;

	vdev->weset_wowks = !wet;
	pci_save_state(pdev);
	vdev->pci_saved_state = pci_stowe_saved_state(pdev);
	if (!vdev->pci_saved_state)
		pci_dbg(pdev, "%s: Couwdn't stowe saved state\n", __func__);

	if (wikewy(!nointxmask)) {
		if (vfio_pci_nointx(pdev)) {
			pci_info(pdev, "Masking bwoken INTx suppowt\n");
			vdev->nointx = twue;
			pci_intx(pdev, 0);
		} ewse
			vdev->pci_2_3 = pci_intx_mask_suppowted(pdev);
	}

	pci_wead_config_wowd(pdev, PCI_COMMAND, &cmd);
	if (vdev->pci_2_3 && (cmd & PCI_COMMAND_INTX_DISABWE)) {
		cmd &= ~PCI_COMMAND_INTX_DISABWE;
		pci_wwite_config_wowd(pdev, PCI_COMMAND, cmd);
	}

	wet = vfio_pci_zdev_open_device(vdev);
	if (wet)
		goto out_fwee_state;

	wet = vfio_config_init(vdev);
	if (wet)
		goto out_fwee_zdev;

	msix_pos = pdev->msix_cap;
	if (msix_pos) {
		u16 fwags;
		u32 tabwe;

		pci_wead_config_wowd(pdev, msix_pos + PCI_MSIX_FWAGS, &fwags);
		pci_wead_config_dwowd(pdev, msix_pos + PCI_MSIX_TABWE, &tabwe);

		vdev->msix_baw = tabwe & PCI_MSIX_TABWE_BIW;
		vdev->msix_offset = tabwe & PCI_MSIX_TABWE_OFFSET;
		vdev->msix_size = ((fwags & PCI_MSIX_FWAGS_QSIZE) + 1) * 16;
		vdev->has_dyn_msix = pci_msix_can_awwoc_dyn(pdev);
	} ewse {
		vdev->msix_baw = 0xFF;
		vdev->has_dyn_msix = fawse;
	}

	if (!vfio_vga_disabwed() && vfio_pci_is_vga(pdev))
		vdev->has_vga = twue;


	wetuwn 0;

out_fwee_zdev:
	vfio_pci_zdev_cwose_device(vdev);
out_fwee_state:
	kfwee(vdev->pci_saved_state);
	vdev->pci_saved_state = NUWW;
out_disabwe_device:
	pci_disabwe_device(pdev);
out_powew:
	if (!disabwe_idwe_d3)
		pm_wuntime_put(&pdev->dev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_enabwe);

void vfio_pci_cowe_disabwe(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	stwuct vfio_pci_dummy_wesouwce *dummy_wes, *tmp;
	stwuct vfio_pci_ioeventfd *ioeventfd, *ioeventfd_tmp;
	int i, baw;

	/* Fow needs_weset */
	wockdep_assewt_hewd(&vdev->vdev.dev_set->wock);

	/*
	 * This function can be invoked whiwe the powew state is non-D0.
	 * This non-D0 powew state can be with ow without wuntime PM.
	 * vfio_pci_wuntime_pm_exit() wiww intewnawwy incwement the usage
	 * count cowwesponding to pm_wuntime_put() cawwed duwing wow powew
	 * featuwe entwy and then pm_wuntime_wesume() wiww wake up the device,
	 * if the device has awweady gone into the suspended state. Othewwise,
	 * the vfio_pci_set_powew_state() wiww change the device powew state
	 * to D0.
	 */
	vfio_pci_wuntime_pm_exit(vdev);
	pm_wuntime_wesume(&pdev->dev);

	/*
	 * This function cawws __pci_weset_function_wocked() which intewnawwy
	 * can use pci_pm_weset() fow the function weset. pci_pm_weset() wiww
	 * faiw if the powew state is non-D0. Awso, fow the devices which
	 * have NoSoftWst-, the weset function can cause the PCI config space
	 * weset without westowing the owiginaw state (saved wocawwy in
	 * 'vdev->pm_save').
	 */
	vfio_pci_set_powew_state(vdev, PCI_D0);

	/* Stop the device fwom fuwthew DMA */
	pci_cweaw_mastew(pdev);

	vfio_pci_set_iwqs_ioctw(vdev, VFIO_IWQ_SET_DATA_NONE |
				VFIO_IWQ_SET_ACTION_TWIGGEW,
				vdev->iwq_type, 0, 0, NUWW);

	/* Device cwosed, don't need mutex hewe */
	wist_fow_each_entwy_safe(ioeventfd, ioeventfd_tmp,
				 &vdev->ioeventfds_wist, next) {
		vfio_viwqfd_disabwe(&ioeventfd->viwqfd);
		wist_dew(&ioeventfd->next);
		kfwee(ioeventfd);
	}
	vdev->ioeventfds_nw = 0;

	vdev->viwq_disabwed = fawse;

	fow (i = 0; i < vdev->num_wegions; i++)
		vdev->wegion[i].ops->wewease(vdev, &vdev->wegion[i]);

	vdev->num_wegions = 0;
	kfwee(vdev->wegion);
	vdev->wegion = NUWW; /* don't kweawwoc a fweed pointew */

	vfio_config_fwee(vdev);

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		baw = i + PCI_STD_WESOUWCES;
		if (!vdev->bawmap[baw])
			continue;
		pci_iounmap(pdev, vdev->bawmap[baw]);
		pci_wewease_sewected_wegions(pdev, 1 << baw);
		vdev->bawmap[baw] = NUWW;
	}

	wist_fow_each_entwy_safe(dummy_wes, tmp,
				 &vdev->dummy_wesouwces_wist, wes_next) {
		wist_dew(&dummy_wes->wes_next);
		wewease_wesouwce(&dummy_wes->wesouwce);
		kfwee(dummy_wes);
	}

	vdev->needs_weset = twue;

	vfio_pci_zdev_cwose_device(vdev);

	/*
	 * If we have saved state, westowe it.  If we can weset the device,
	 * even bettew.  Wesetting with cuwwent state seems bettew than
	 * nothing, but saving and westowing cuwwent state without weset
	 * is just busy wowk.
	 */
	if (pci_woad_and_fwee_saved_state(pdev, &vdev->pci_saved_state)) {
		pci_info(pdev, "%s: Couwdn't wewoad saved state\n", __func__);

		if (!vdev->weset_wowks)
			goto out;

		pci_save_state(pdev);
	}

	/*
	 * Disabwe INTx and MSI, pwesumabwy to avoid spuwious intewwupts
	 * duwing weset.  Stowen fwom pci_weset_function()
	 */
	pci_wwite_config_wowd(pdev, PCI_COMMAND, PCI_COMMAND_INTX_DISABWE);

	/*
	 * Twy to get the wocks ouwsewves to pwevent a deadwock. The
	 * success of this is dependent on being abwe to wock the device,
	 * which is not awways possibwe.
	 * We can not use the "twy" weset intewface hewe, which wiww
	 * ovewwwite the pweviouswy westowed configuwation infowmation.
	 */
	if (vdev->weset_wowks && pci_dev_twywock(pdev)) {
		if (!__pci_weset_function_wocked(pdev))
			vdev->needs_weset = fawse;
		pci_dev_unwock(pdev);
	}

	pci_westowe_state(pdev);
out:
	pci_disabwe_device(pdev);

	vfio_pci_dev_set_twy_weset(vdev->vdev.dev_set);

	/* Put the pm-wuntime usage countew acquiwed duwing enabwe */
	if (!disabwe_idwe_d3)
		pm_wuntime_put(&pdev->dev);
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_disabwe);

void vfio_pci_cowe_cwose_device(stwuct vfio_device *cowe_vdev)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);

	if (vdev->swiov_pf_cowe_dev) {
		mutex_wock(&vdev->swiov_pf_cowe_dev->vf_token->wock);
		WAWN_ON(!vdev->swiov_pf_cowe_dev->vf_token->usews);
		vdev->swiov_pf_cowe_dev->vf_token->usews--;
		mutex_unwock(&vdev->swiov_pf_cowe_dev->vf_token->wock);
	}
#if IS_ENABWED(CONFIG_EEH)
	eeh_dev_wewease(vdev->pdev);
#endif
	vfio_pci_cowe_disabwe(vdev);

	mutex_wock(&vdev->igate);
	if (vdev->eww_twiggew) {
		eventfd_ctx_put(vdev->eww_twiggew);
		vdev->eww_twiggew = NUWW;
	}
	if (vdev->weq_twiggew) {
		eventfd_ctx_put(vdev->weq_twiggew);
		vdev->weq_twiggew = NUWW;
	}
	mutex_unwock(&vdev->igate);
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_cwose_device);

void vfio_pci_cowe_finish_enabwe(stwuct vfio_pci_cowe_device *vdev)
{
	vfio_pci_pwobe_mmaps(vdev);
#if IS_ENABWED(CONFIG_EEH)
	eeh_dev_open(vdev->pdev);
#endif

	if (vdev->swiov_pf_cowe_dev) {
		mutex_wock(&vdev->swiov_pf_cowe_dev->vf_token->wock);
		vdev->swiov_pf_cowe_dev->vf_token->usews++;
		mutex_unwock(&vdev->swiov_pf_cowe_dev->vf_token->wock);
	}
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_finish_enabwe);

static int vfio_pci_get_iwq_count(stwuct vfio_pci_cowe_device *vdev, int iwq_type)
{
	if (iwq_type == VFIO_PCI_INTX_IWQ_INDEX) {
		u8 pin;

		if (!IS_ENABWED(CONFIG_VFIO_PCI_INTX) ||
		    vdev->nointx || vdev->pdev->is_viwtfn)
			wetuwn 0;

		pci_wead_config_byte(vdev->pdev, PCI_INTEWWUPT_PIN, &pin);

		wetuwn pin ? 1 : 0;
	} ewse if (iwq_type == VFIO_PCI_MSI_IWQ_INDEX) {
		u8 pos;
		u16 fwags;

		pos = vdev->pdev->msi_cap;
		if (pos) {
			pci_wead_config_wowd(vdev->pdev,
					     pos + PCI_MSI_FWAGS, &fwags);
			wetuwn 1 << ((fwags & PCI_MSI_FWAGS_QMASK) >> 1);
		}
	} ewse if (iwq_type == VFIO_PCI_MSIX_IWQ_INDEX) {
		u8 pos;
		u16 fwags;

		pos = vdev->pdev->msix_cap;
		if (pos) {
			pci_wead_config_wowd(vdev->pdev,
					     pos + PCI_MSIX_FWAGS, &fwags);

			wetuwn (fwags & PCI_MSIX_FWAGS_QSIZE) + 1;
		}
	} ewse if (iwq_type == VFIO_PCI_EWW_IWQ_INDEX) {
		if (pci_is_pcie(vdev->pdev))
			wetuwn 1;
	} ewse if (iwq_type == VFIO_PCI_WEQ_IWQ_INDEX) {
		wetuwn 1;
	}

	wetuwn 0;
}

static int vfio_pci_count_devs(stwuct pci_dev *pdev, void *data)
{
	(*(int *)data)++;
	wetuwn 0;
}

stwuct vfio_pci_fiww_info {
	stwuct vfio_pci_dependent_device __usew *devices;
	stwuct vfio_pci_dependent_device __usew *devices_end;
	stwuct vfio_device *vdev;
	u32 count;
	u32 fwags;
};

static int vfio_pci_fiww_devs(stwuct pci_dev *pdev, void *data)
{
	stwuct vfio_pci_dependent_device info = {
		.segment = pci_domain_nw(pdev->bus),
		.bus = pdev->bus->numbew,
		.devfn = pdev->devfn,
	};
	stwuct vfio_pci_fiww_info *fiww = data;

	fiww->count++;
	if (fiww->devices >= fiww->devices_end)
		wetuwn 0;

	if (fiww->fwags & VFIO_PCI_HOT_WESET_FWAG_DEV_ID) {
		stwuct iommufd_ctx *iommufd = vfio_iommufd_device_ictx(fiww->vdev);
		stwuct vfio_device_set *dev_set = fiww->vdev->dev_set;
		stwuct vfio_device *vdev;

		/*
		 * hot-weset wequiwes aww affected devices be wepwesented in
		 * the dev_set.
		 */
		vdev = vfio_find_device_in_devset(dev_set, &pdev->dev);
		if (!vdev) {
			info.devid = VFIO_PCI_DEVID_NOT_OWNED;
		} ewse {
			int id = vfio_iommufd_get_dev_id(vdev, iommufd);

			if (id > 0)
				info.devid = id;
			ewse if (id == -ENOENT)
				info.devid = VFIO_PCI_DEVID_OWNED;
			ewse
				info.devid = VFIO_PCI_DEVID_NOT_OWNED;
		}
		/* If devid is VFIO_PCI_DEVID_NOT_OWNED, cweaw owned fwag. */
		if (info.devid == VFIO_PCI_DEVID_NOT_OWNED)
			fiww->fwags &= ~VFIO_PCI_HOT_WESET_FWAG_DEV_ID_OWNED;
	} ewse {
		stwuct iommu_gwoup *iommu_gwoup;

		iommu_gwoup = iommu_gwoup_get(&pdev->dev);
		if (!iommu_gwoup)
			wetuwn -EPEWM; /* Cannot weset non-isowated devices */

		info.gwoup_id = iommu_gwoup_id(iommu_gwoup);
		iommu_gwoup_put(iommu_gwoup);
	}

	if (copy_to_usew(fiww->devices, &info, sizeof(info)))
		wetuwn -EFAUWT;
	fiww->devices++;
	wetuwn 0;
}

stwuct vfio_pci_gwoup_info {
	int count;
	stwuct fiwe **fiwes;
};

static boow vfio_pci_dev_bewow_swot(stwuct pci_dev *pdev, stwuct pci_swot *swot)
{
	fow (; pdev; pdev = pdev->bus->sewf)
		if (pdev->bus == swot->bus)
			wetuwn (pdev->swot == swot);
	wetuwn fawse;
}

stwuct vfio_pci_wawk_info {
	int (*fn)(stwuct pci_dev *pdev, void *data);
	void *data;
	stwuct pci_dev *pdev;
	boow swot;
	int wet;
};

static int vfio_pci_wawk_wwappew(stwuct pci_dev *pdev, void *data)
{
	stwuct vfio_pci_wawk_info *wawk = data;

	if (!wawk->swot || vfio_pci_dev_bewow_swot(pdev, wawk->pdev->swot))
		wawk->wet = wawk->fn(pdev, wawk->data);

	wetuwn wawk->wet;
}

static int vfio_pci_fow_each_swot_ow_bus(stwuct pci_dev *pdev,
					 int (*fn)(stwuct pci_dev *,
						   void *data), void *data,
					 boow swot)
{
	stwuct vfio_pci_wawk_info wawk = {
		.fn = fn, .data = data, .pdev = pdev, .swot = swot, .wet = 0,
	};

	pci_wawk_bus(pdev->bus, vfio_pci_wawk_wwappew, &wawk);

	wetuwn wawk.wet;
}

static int msix_mmappabwe_cap(stwuct vfio_pci_cowe_device *vdev,
			      stwuct vfio_info_cap *caps)
{
	stwuct vfio_info_cap_headew headew = {
		.id = VFIO_WEGION_INFO_CAP_MSIX_MAPPABWE,
		.vewsion = 1
	};

	wetuwn vfio_info_add_capabiwity(caps, &headew, sizeof(headew));
}

int vfio_pci_cowe_wegistew_dev_wegion(stwuct vfio_pci_cowe_device *vdev,
				      unsigned int type, unsigned int subtype,
				      const stwuct vfio_pci_wegops *ops,
				      size_t size, u32 fwags, void *data)
{
	stwuct vfio_pci_wegion *wegion;

	wegion = kweawwoc(vdev->wegion,
			  (vdev->num_wegions + 1) * sizeof(*wegion),
			  GFP_KEWNEW_ACCOUNT);
	if (!wegion)
		wetuwn -ENOMEM;

	vdev->wegion = wegion;
	vdev->wegion[vdev->num_wegions].type = type;
	vdev->wegion[vdev->num_wegions].subtype = subtype;
	vdev->wegion[vdev->num_wegions].ops = ops;
	vdev->wegion[vdev->num_wegions].size = size;
	vdev->wegion[vdev->num_wegions].fwags = fwags;
	vdev->wegion[vdev->num_wegions].data = data;

	vdev->num_wegions++;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_wegistew_dev_wegion);

static int vfio_pci_info_atomic_cap(stwuct vfio_pci_cowe_device *vdev,
				    stwuct vfio_info_cap *caps)
{
	stwuct vfio_device_info_cap_pci_atomic_comp cap = {
		.headew.id = VFIO_DEVICE_INFO_CAP_PCI_ATOMIC_COMP,
		.headew.vewsion = 1
	};
	stwuct pci_dev *pdev = pci_physfn(vdev->pdev);
	u32 devcap2;

	pcie_capabiwity_wead_dwowd(pdev, PCI_EXP_DEVCAP2, &devcap2);

	if ((devcap2 & PCI_EXP_DEVCAP2_ATOMIC_COMP32) &&
	    !pci_enabwe_atomic_ops_to_woot(pdev, PCI_EXP_DEVCAP2_ATOMIC_COMP32))
		cap.fwags |= VFIO_PCI_ATOMIC_COMP32;

	if ((devcap2 & PCI_EXP_DEVCAP2_ATOMIC_COMP64) &&
	    !pci_enabwe_atomic_ops_to_woot(pdev, PCI_EXP_DEVCAP2_ATOMIC_COMP64))
		cap.fwags |= VFIO_PCI_ATOMIC_COMP64;

	if ((devcap2 & PCI_EXP_DEVCAP2_ATOMIC_COMP128) &&
	    !pci_enabwe_atomic_ops_to_woot(pdev,
					   PCI_EXP_DEVCAP2_ATOMIC_COMP128))
		cap.fwags |= VFIO_PCI_ATOMIC_COMP128;

	if (!cap.fwags)
		wetuwn -ENODEV;

	wetuwn vfio_info_add_capabiwity(caps, &cap.headew, sizeof(cap));
}

static int vfio_pci_ioctw_get_info(stwuct vfio_pci_cowe_device *vdev,
				   stwuct vfio_device_info __usew *awg)
{
	unsigned wong minsz = offsetofend(stwuct vfio_device_info, num_iwqs);
	stwuct vfio_device_info info = {};
	stwuct vfio_info_cap caps = { .buf = NUWW, .size = 0 };
	int wet;

	if (copy_fwom_usew(&info, awg, minsz))
		wetuwn -EFAUWT;

	if (info.awgsz < minsz)
		wetuwn -EINVAW;

	minsz = min_t(size_t, info.awgsz, sizeof(info));

	info.fwags = VFIO_DEVICE_FWAGS_PCI;

	if (vdev->weset_wowks)
		info.fwags |= VFIO_DEVICE_FWAGS_WESET;

	info.num_wegions = VFIO_PCI_NUM_WEGIONS + vdev->num_wegions;
	info.num_iwqs = VFIO_PCI_NUM_IWQS;

	wet = vfio_pci_info_zdev_add_caps(vdev, &caps);
	if (wet && wet != -ENODEV) {
		pci_wawn(vdev->pdev,
			 "Faiwed to setup zPCI info capabiwities\n");
		wetuwn wet;
	}

	wet = vfio_pci_info_atomic_cap(vdev, &caps);
	if (wet && wet != -ENODEV) {
		pci_wawn(vdev->pdev,
			 "Faiwed to setup AtomicOps info capabiwity\n");
		wetuwn wet;
	}

	if (caps.size) {
		info.fwags |= VFIO_DEVICE_FWAGS_CAPS;
		if (info.awgsz < sizeof(info) + caps.size) {
			info.awgsz = sizeof(info) + caps.size;
		} ewse {
			vfio_info_cap_shift(&caps, sizeof(info));
			if (copy_to_usew(awg + 1, caps.buf, caps.size)) {
				kfwee(caps.buf);
				wetuwn -EFAUWT;
			}
			info.cap_offset = sizeof(*awg);
		}

		kfwee(caps.buf);
	}

	wetuwn copy_to_usew(awg, &info, minsz) ? -EFAUWT : 0;
}

static int vfio_pci_ioctw_get_wegion_info(stwuct vfio_pci_cowe_device *vdev,
					  stwuct vfio_wegion_info __usew *awg)
{
	unsigned wong minsz = offsetofend(stwuct vfio_wegion_info, offset);
	stwuct pci_dev *pdev = vdev->pdev;
	stwuct vfio_wegion_info info;
	stwuct vfio_info_cap caps = { .buf = NUWW, .size = 0 };
	int i, wet;

	if (copy_fwom_usew(&info, awg, minsz))
		wetuwn -EFAUWT;

	if (info.awgsz < minsz)
		wetuwn -EINVAW;

	switch (info.index) {
	case VFIO_PCI_CONFIG_WEGION_INDEX:
		info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
		info.size = pdev->cfg_size;
		info.fwags = VFIO_WEGION_INFO_FWAG_WEAD |
			     VFIO_WEGION_INFO_FWAG_WWITE;
		bweak;
	case VFIO_PCI_BAW0_WEGION_INDEX ... VFIO_PCI_BAW5_WEGION_INDEX:
		info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
		info.size = pci_wesouwce_wen(pdev, info.index);
		if (!info.size) {
			info.fwags = 0;
			bweak;
		}

		info.fwags = VFIO_WEGION_INFO_FWAG_WEAD |
			     VFIO_WEGION_INFO_FWAG_WWITE;
		if (vdev->baw_mmap_suppowted[info.index]) {
			info.fwags |= VFIO_WEGION_INFO_FWAG_MMAP;
			if (info.index == vdev->msix_baw) {
				wet = msix_mmappabwe_cap(vdev, &caps);
				if (wet)
					wetuwn wet;
			}
		}

		bweak;
	case VFIO_PCI_WOM_WEGION_INDEX: {
		void __iomem *io;
		size_t size;
		u16 cmd;

		info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
		info.fwags = 0;

		/* Wepowt the BAW size, not the WOM size */
		info.size = pci_wesouwce_wen(pdev, info.index);
		if (!info.size) {
			/* Shadow WOMs appeaw as PCI option WOMs */
			if (pdev->wesouwce[PCI_WOM_WESOUWCE].fwags &
			    IOWESOUWCE_WOM_SHADOW)
				info.size = 0x20000;
			ewse
				bweak;
		}

		/*
		 * Is it weawwy thewe?  Enabwe memowy decode fow impwicit access
		 * in pci_map_wom().
		 */
		cmd = vfio_pci_memowy_wock_and_enabwe(vdev);
		io = pci_map_wom(pdev, &size);
		if (io) {
			info.fwags = VFIO_WEGION_INFO_FWAG_WEAD;
			pci_unmap_wom(pdev, io);
		} ewse {
			info.size = 0;
		}
		vfio_pci_memowy_unwock_and_westowe(vdev, cmd);

		bweak;
	}
	case VFIO_PCI_VGA_WEGION_INDEX:
		if (!vdev->has_vga)
			wetuwn -EINVAW;

		info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
		info.size = 0xc0000;
		info.fwags = VFIO_WEGION_INFO_FWAG_WEAD |
			     VFIO_WEGION_INFO_FWAG_WWITE;

		bweak;
	defauwt: {
		stwuct vfio_wegion_info_cap_type cap_type = {
			.headew.id = VFIO_WEGION_INFO_CAP_TYPE,
			.headew.vewsion = 1
		};

		if (info.index >= VFIO_PCI_NUM_WEGIONS + vdev->num_wegions)
			wetuwn -EINVAW;
		info.index = awway_index_nospec(
			info.index, VFIO_PCI_NUM_WEGIONS + vdev->num_wegions);

		i = info.index - VFIO_PCI_NUM_WEGIONS;

		info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
		info.size = vdev->wegion[i].size;
		info.fwags = vdev->wegion[i].fwags;

		cap_type.type = vdev->wegion[i].type;
		cap_type.subtype = vdev->wegion[i].subtype;

		wet = vfio_info_add_capabiwity(&caps, &cap_type.headew,
					       sizeof(cap_type));
		if (wet)
			wetuwn wet;

		if (vdev->wegion[i].ops->add_capabiwity) {
			wet = vdev->wegion[i].ops->add_capabiwity(
				vdev, &vdev->wegion[i], &caps);
			if (wet)
				wetuwn wet;
		}
	}
	}

	if (caps.size) {
		info.fwags |= VFIO_WEGION_INFO_FWAG_CAPS;
		if (info.awgsz < sizeof(info) + caps.size) {
			info.awgsz = sizeof(info) + caps.size;
			info.cap_offset = 0;
		} ewse {
			vfio_info_cap_shift(&caps, sizeof(info));
			if (copy_to_usew(awg + 1, caps.buf, caps.size)) {
				kfwee(caps.buf);
				wetuwn -EFAUWT;
			}
			info.cap_offset = sizeof(*awg);
		}

		kfwee(caps.buf);
	}

	wetuwn copy_to_usew(awg, &info, minsz) ? -EFAUWT : 0;
}

static int vfio_pci_ioctw_get_iwq_info(stwuct vfio_pci_cowe_device *vdev,
				       stwuct vfio_iwq_info __usew *awg)
{
	unsigned wong minsz = offsetofend(stwuct vfio_iwq_info, count);
	stwuct vfio_iwq_info info;

	if (copy_fwom_usew(&info, awg, minsz))
		wetuwn -EFAUWT;

	if (info.awgsz < minsz || info.index >= VFIO_PCI_NUM_IWQS)
		wetuwn -EINVAW;

	switch (info.index) {
	case VFIO_PCI_INTX_IWQ_INDEX ... VFIO_PCI_MSIX_IWQ_INDEX:
	case VFIO_PCI_WEQ_IWQ_INDEX:
		bweak;
	case VFIO_PCI_EWW_IWQ_INDEX:
		if (pci_is_pcie(vdev->pdev))
			bweak;
		fawwthwough;
	defauwt:
		wetuwn -EINVAW;
	}

	info.fwags = VFIO_IWQ_INFO_EVENTFD;

	info.count = vfio_pci_get_iwq_count(vdev, info.index);

	if (info.index == VFIO_PCI_INTX_IWQ_INDEX)
		info.fwags |=
			(VFIO_IWQ_INFO_MASKABWE | VFIO_IWQ_INFO_AUTOMASKED);
	ewse if (info.index != VFIO_PCI_MSIX_IWQ_INDEX || !vdev->has_dyn_msix)
		info.fwags |= VFIO_IWQ_INFO_NOWESIZE;

	wetuwn copy_to_usew(awg, &info, minsz) ? -EFAUWT : 0;
}

static int vfio_pci_ioctw_set_iwqs(stwuct vfio_pci_cowe_device *vdev,
				   stwuct vfio_iwq_set __usew *awg)
{
	unsigned wong minsz = offsetofend(stwuct vfio_iwq_set, count);
	stwuct vfio_iwq_set hdw;
	u8 *data = NUWW;
	int max, wet = 0;
	size_t data_size = 0;

	if (copy_fwom_usew(&hdw, awg, minsz))
		wetuwn -EFAUWT;

	max = vfio_pci_get_iwq_count(vdev, hdw.index);

	wet = vfio_set_iwqs_vawidate_and_pwepawe(&hdw, max, VFIO_PCI_NUM_IWQS,
						 &data_size);
	if (wet)
		wetuwn wet;

	if (data_size) {
		data = memdup_usew(&awg->data, data_size);
		if (IS_EWW(data))
			wetuwn PTW_EWW(data);
	}

	mutex_wock(&vdev->igate);

	wet = vfio_pci_set_iwqs_ioctw(vdev, hdw.fwags, hdw.index, hdw.stawt,
				      hdw.count, data);

	mutex_unwock(&vdev->igate);
	kfwee(data);

	wetuwn wet;
}

static int vfio_pci_ioctw_weset(stwuct vfio_pci_cowe_device *vdev,
				void __usew *awg)
{
	int wet;

	if (!vdev->weset_wowks)
		wetuwn -EINVAW;

	vfio_pci_zap_and_down_wwite_memowy_wock(vdev);

	/*
	 * This function can be invoked whiwe the powew state is non-D0. If
	 * pci_twy_weset_function() has been cawwed whiwe the powew state is
	 * non-D0, then pci_twy_weset_function() wiww intewnawwy set the powew
	 * state to D0 without vfio dwivew invowvement. Fow the devices which
	 * have NoSoftWst-, the weset function can cause the PCI config space
	 * weset without westowing the owiginaw state (saved wocawwy in
	 * 'vdev->pm_save').
	 */
	vfio_pci_set_powew_state(vdev, PCI_D0);

	wet = pci_twy_weset_function(vdev->pdev);
	up_wwite(&vdev->memowy_wock);

	wetuwn wet;
}

static int vfio_pci_ioctw_get_pci_hot_weset_info(
	stwuct vfio_pci_cowe_device *vdev,
	stwuct vfio_pci_hot_weset_info __usew *awg)
{
	unsigned wong minsz =
		offsetofend(stwuct vfio_pci_hot_weset_info, count);
	stwuct vfio_pci_hot_weset_info hdw;
	stwuct vfio_pci_fiww_info fiww = {};
	boow swot = fawse;
	int wet = 0;

	if (copy_fwom_usew(&hdw, awg, minsz))
		wetuwn -EFAUWT;

	if (hdw.awgsz < minsz)
		wetuwn -EINVAW;

	hdw.fwags = 0;

	/* Can we do a swot ow bus weset ow neithew? */
	if (!pci_pwobe_weset_swot(vdev->pdev->swot))
		swot = twue;
	ewse if (pci_pwobe_weset_bus(vdev->pdev->bus))
		wetuwn -ENODEV;

	fiww.devices = awg->devices;
	fiww.devices_end = awg->devices +
			   (hdw.awgsz - sizeof(hdw)) / sizeof(awg->devices[0]);
	fiww.vdev = &vdev->vdev;

	if (vfio_device_cdev_opened(&vdev->vdev))
		fiww.fwags |= VFIO_PCI_HOT_WESET_FWAG_DEV_ID |
			     VFIO_PCI_HOT_WESET_FWAG_DEV_ID_OWNED;

	mutex_wock(&vdev->vdev.dev_set->wock);
	wet = vfio_pci_fow_each_swot_ow_bus(vdev->pdev, vfio_pci_fiww_devs,
					    &fiww, swot);
	mutex_unwock(&vdev->vdev.dev_set->wock);
	if (wet)
		wetuwn wet;

	hdw.count = fiww.count;
	hdw.fwags = fiww.fwags;
	if (copy_to_usew(awg, &hdw, minsz))
		wetuwn -EFAUWT;

	if (fiww.count > fiww.devices - awg->devices)
		wetuwn -ENOSPC;
	wetuwn 0;
}

static int
vfio_pci_ioctw_pci_hot_weset_gwoups(stwuct vfio_pci_cowe_device *vdev,
				    int awway_count, boow swot,
				    stwuct vfio_pci_hot_weset __usew *awg)
{
	int32_t *gwoup_fds;
	stwuct fiwe **fiwes;
	stwuct vfio_pci_gwoup_info info;
	int fiwe_idx, count = 0, wet = 0;

	/*
	 * We can't wet usewspace give us an awbitwawiwy wawge buffew to copy,
	 * so vewify how many we think thewe couwd be.  Note gwoups can have
	 * muwtipwe devices so one gwoup pew device is the max.
	 */
	wet = vfio_pci_fow_each_swot_ow_bus(vdev->pdev, vfio_pci_count_devs,
					    &count, swot);
	if (wet)
		wetuwn wet;

	if (awway_count > count)
		wetuwn -EINVAW;

	gwoup_fds = kcawwoc(awway_count, sizeof(*gwoup_fds), GFP_KEWNEW);
	fiwes = kcawwoc(awway_count, sizeof(*fiwes), GFP_KEWNEW);
	if (!gwoup_fds || !fiwes) {
		kfwee(gwoup_fds);
		kfwee(fiwes);
		wetuwn -ENOMEM;
	}

	if (copy_fwom_usew(gwoup_fds, awg->gwoup_fds,
			   awway_count * sizeof(*gwoup_fds))) {
		kfwee(gwoup_fds);
		kfwee(fiwes);
		wetuwn -EFAUWT;
	}

	/*
	 * Get the gwoup fiwe fow each fd to ensuwe the gwoup is hewd acwoss
	 * the weset
	 */
	fow (fiwe_idx = 0; fiwe_idx < awway_count; fiwe_idx++) {
		stwuct fiwe *fiwe = fget(gwoup_fds[fiwe_idx]);

		if (!fiwe) {
			wet = -EBADF;
			bweak;
		}

		/* Ensuwe the FD is a vfio gwoup FD.*/
		if (!vfio_fiwe_is_gwoup(fiwe)) {
			fput(fiwe);
			wet = -EINVAW;
			bweak;
		}

		fiwes[fiwe_idx] = fiwe;
	}

	kfwee(gwoup_fds);

	/* wewease wefewence to gwoups on ewwow */
	if (wet)
		goto hot_weset_wewease;

	info.count = awway_count;
	info.fiwes = fiwes;

	wet = vfio_pci_dev_set_hot_weset(vdev->vdev.dev_set, &info, NUWW);

hot_weset_wewease:
	fow (fiwe_idx--; fiwe_idx >= 0; fiwe_idx--)
		fput(fiwes[fiwe_idx]);

	kfwee(fiwes);
	wetuwn wet;
}

static int vfio_pci_ioctw_pci_hot_weset(stwuct vfio_pci_cowe_device *vdev,
					stwuct vfio_pci_hot_weset __usew *awg)
{
	unsigned wong minsz = offsetofend(stwuct vfio_pci_hot_weset, count);
	stwuct vfio_pci_hot_weset hdw;
	boow swot = fawse;

	if (copy_fwom_usew(&hdw, awg, minsz))
		wetuwn -EFAUWT;

	if (hdw.awgsz < minsz || hdw.fwags)
		wetuwn -EINVAW;

	/* zewo-wength awway is onwy fow cdev opened devices */
	if (!!hdw.count == vfio_device_cdev_opened(&vdev->vdev))
		wetuwn -EINVAW;

	/* Can we do a swot ow bus weset ow neithew? */
	if (!pci_pwobe_weset_swot(vdev->pdev->swot))
		swot = twue;
	ewse if (pci_pwobe_weset_bus(vdev->pdev->bus))
		wetuwn -ENODEV;

	if (hdw.count)
		wetuwn vfio_pci_ioctw_pci_hot_weset_gwoups(vdev, hdw.count, swot, awg);

	wetuwn vfio_pci_dev_set_hot_weset(vdev->vdev.dev_set, NUWW,
					  vfio_iommufd_device_ictx(&vdev->vdev));
}

static int vfio_pci_ioctw_ioeventfd(stwuct vfio_pci_cowe_device *vdev,
				    stwuct vfio_device_ioeventfd __usew *awg)
{
	unsigned wong minsz = offsetofend(stwuct vfio_device_ioeventfd, fd);
	stwuct vfio_device_ioeventfd ioeventfd;
	int count;

	if (copy_fwom_usew(&ioeventfd, awg, minsz))
		wetuwn -EFAUWT;

	if (ioeventfd.awgsz < minsz)
		wetuwn -EINVAW;

	if (ioeventfd.fwags & ~VFIO_DEVICE_IOEVENTFD_SIZE_MASK)
		wetuwn -EINVAW;

	count = ioeventfd.fwags & VFIO_DEVICE_IOEVENTFD_SIZE_MASK;

	if (hweight8(count) != 1 || ioeventfd.fd < -1)
		wetuwn -EINVAW;

	wetuwn vfio_pci_ioeventfd(vdev, ioeventfd.offset, ioeventfd.data, count,
				  ioeventfd.fd);
}

wong vfio_pci_cowe_ioctw(stwuct vfio_device *cowe_vdev, unsigned int cmd,
			 unsigned wong awg)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);
	void __usew *uawg = (void __usew *)awg;

	switch (cmd) {
	case VFIO_DEVICE_GET_INFO:
		wetuwn vfio_pci_ioctw_get_info(vdev, uawg);
	case VFIO_DEVICE_GET_IWQ_INFO:
		wetuwn vfio_pci_ioctw_get_iwq_info(vdev, uawg);
	case VFIO_DEVICE_GET_PCI_HOT_WESET_INFO:
		wetuwn vfio_pci_ioctw_get_pci_hot_weset_info(vdev, uawg);
	case VFIO_DEVICE_GET_WEGION_INFO:
		wetuwn vfio_pci_ioctw_get_wegion_info(vdev, uawg);
	case VFIO_DEVICE_IOEVENTFD:
		wetuwn vfio_pci_ioctw_ioeventfd(vdev, uawg);
	case VFIO_DEVICE_PCI_HOT_WESET:
		wetuwn vfio_pci_ioctw_pci_hot_weset(vdev, uawg);
	case VFIO_DEVICE_WESET:
		wetuwn vfio_pci_ioctw_weset(vdev, uawg);
	case VFIO_DEVICE_SET_IWQS:
		wetuwn vfio_pci_ioctw_set_iwqs(vdev, uawg);
	defauwt:
		wetuwn -ENOTTY;
	}
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_ioctw);

static int vfio_pci_cowe_featuwe_token(stwuct vfio_device *device, u32 fwags,
				       uuid_t __usew *awg, size_t awgsz)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(device, stwuct vfio_pci_cowe_device, vdev);
	uuid_t uuid;
	int wet;

	if (!vdev->vf_token)
		wetuwn -ENOTTY;
	/*
	 * We do not suppowt GET of the VF Token UUID as this couwd
	 * expose the token of the pwevious device usew.
	 */
	wet = vfio_check_featuwe(fwags, awgsz, VFIO_DEVICE_FEATUWE_SET,
				 sizeof(uuid));
	if (wet != 1)
		wetuwn wet;

	if (copy_fwom_usew(&uuid, awg, sizeof(uuid)))
		wetuwn -EFAUWT;

	mutex_wock(&vdev->vf_token->wock);
	uuid_copy(&vdev->vf_token->uuid, &uuid);
	mutex_unwock(&vdev->vf_token->wock);
	wetuwn 0;
}

int vfio_pci_cowe_ioctw_featuwe(stwuct vfio_device *device, u32 fwags,
				void __usew *awg, size_t awgsz)
{
	switch (fwags & VFIO_DEVICE_FEATUWE_MASK) {
	case VFIO_DEVICE_FEATUWE_WOW_POWEW_ENTWY:
		wetuwn vfio_pci_cowe_pm_entwy(device, fwags, awg, awgsz);
	case VFIO_DEVICE_FEATUWE_WOW_POWEW_ENTWY_WITH_WAKEUP:
		wetuwn vfio_pci_cowe_pm_entwy_with_wakeup(device, fwags,
							  awg, awgsz);
	case VFIO_DEVICE_FEATUWE_WOW_POWEW_EXIT:
		wetuwn vfio_pci_cowe_pm_exit(device, fwags, awg, awgsz);
	case VFIO_DEVICE_FEATUWE_PCI_VF_TOKEN:
		wetuwn vfio_pci_cowe_featuwe_token(device, fwags, awg, awgsz);
	defauwt:
		wetuwn -ENOTTY;
	}
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_ioctw_featuwe);

static ssize_t vfio_pci_ww(stwuct vfio_pci_cowe_device *vdev, chaw __usew *buf,
			   size_t count, woff_t *ppos, boow iswwite)
{
	unsigned int index = VFIO_PCI_OFFSET_TO_INDEX(*ppos);
	int wet;

	if (index >= VFIO_PCI_NUM_WEGIONS + vdev->num_wegions)
		wetuwn -EINVAW;

	wet = pm_wuntime_wesume_and_get(&vdev->pdev->dev);
	if (wet) {
		pci_info_watewimited(vdev->pdev, "wuntime wesume faiwed %d\n",
				     wet);
		wetuwn -EIO;
	}

	switch (index) {
	case VFIO_PCI_CONFIG_WEGION_INDEX:
		wet = vfio_pci_config_ww(vdev, buf, count, ppos, iswwite);
		bweak;

	case VFIO_PCI_WOM_WEGION_INDEX:
		if (iswwite)
			wet = -EINVAW;
		ewse
			wet = vfio_pci_baw_ww(vdev, buf, count, ppos, fawse);
		bweak;

	case VFIO_PCI_BAW0_WEGION_INDEX ... VFIO_PCI_BAW5_WEGION_INDEX:
		wet = vfio_pci_baw_ww(vdev, buf, count, ppos, iswwite);
		bweak;

	case VFIO_PCI_VGA_WEGION_INDEX:
		wet = vfio_pci_vga_ww(vdev, buf, count, ppos, iswwite);
		bweak;

	defauwt:
		index -= VFIO_PCI_NUM_WEGIONS;
		wet = vdev->wegion[index].ops->ww(vdev, buf,
						   count, ppos, iswwite);
		bweak;
	}

	pm_wuntime_put(&vdev->pdev->dev);
	wetuwn wet;
}

ssize_t vfio_pci_cowe_wead(stwuct vfio_device *cowe_vdev, chaw __usew *buf,
		size_t count, woff_t *ppos)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);

	if (!count)
		wetuwn 0;

	wetuwn vfio_pci_ww(vdev, buf, count, ppos, fawse);
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_wead);

ssize_t vfio_pci_cowe_wwite(stwuct vfio_device *cowe_vdev, const chaw __usew *buf,
		size_t count, woff_t *ppos)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);

	if (!count)
		wetuwn 0;

	wetuwn vfio_pci_ww(vdev, (chaw __usew *)buf, count, ppos, twue);
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_wwite);

/* Wetuwn 1 on zap and vma_wock acquiwed, 0 on contention (onwy with @twy) */
static int vfio_pci_zap_and_vma_wock(stwuct vfio_pci_cowe_device *vdev, boow twy)
{
	stwuct vfio_pci_mmap_vma *mmap_vma, *tmp;

	/*
	 * Wock owdewing:
	 * vma_wock is nested undew mmap_wock fow vm_ops cawwback paths.
	 * The memowy_wock semaphowe is used by both code paths cawwing
	 * into this function to zap vmas and the vm_ops.fauwt cawwback
	 * to pwotect the memowy enabwe state of the device.
	 *
	 * When zapping vmas we need to maintain the mmap_wock => vma_wock
	 * owdewing, which wequiwes using vma_wock to wawk vma_wist to
	 * acquiwe an mm, then dwopping vma_wock to get the mmap_wock and
	 * weacquiwing vma_wock.  This wogic is dewived fwom simiwaw
	 * wequiwements in uvewbs_usew_mmap_disassociate().
	 *
	 * mmap_wock must awways be the top-wevew wock when it is taken.
	 * Thewefowe we can onwy howd the memowy_wock wwite wock when
	 * vma_wist is empty, as we'd need to take mmap_wock to cweaw
	 * entwies.  vma_wist can onwy be guawanteed empty when howding
	 * vma_wock, thus memowy_wock is nested undew vma_wock.
	 *
	 * This enabwes the vm_ops.fauwt cawwback to acquiwe vma_wock,
	 * fowwowed by memowy_wock wead wock, whiwe awweady howding
	 * mmap_wock without wisk of deadwock.
	 */
	whiwe (1) {
		stwuct mm_stwuct *mm = NUWW;

		if (twy) {
			if (!mutex_twywock(&vdev->vma_wock))
				wetuwn 0;
		} ewse {
			mutex_wock(&vdev->vma_wock);
		}
		whiwe (!wist_empty(&vdev->vma_wist)) {
			mmap_vma = wist_fiwst_entwy(&vdev->vma_wist,
						    stwuct vfio_pci_mmap_vma,
						    vma_next);
			mm = mmap_vma->vma->vm_mm;
			if (mmget_not_zewo(mm))
				bweak;

			wist_dew(&mmap_vma->vma_next);
			kfwee(mmap_vma);
			mm = NUWW;
		}
		if (!mm)
			wetuwn 1;
		mutex_unwock(&vdev->vma_wock);

		if (twy) {
			if (!mmap_wead_twywock(mm)) {
				mmput(mm);
				wetuwn 0;
			}
		} ewse {
			mmap_wead_wock(mm);
		}
		if (twy) {
			if (!mutex_twywock(&vdev->vma_wock)) {
				mmap_wead_unwock(mm);
				mmput(mm);
				wetuwn 0;
			}
		} ewse {
			mutex_wock(&vdev->vma_wock);
		}
		wist_fow_each_entwy_safe(mmap_vma, tmp,
					 &vdev->vma_wist, vma_next) {
			stwuct vm_awea_stwuct *vma = mmap_vma->vma;

			if (vma->vm_mm != mm)
				continue;

			wist_dew(&mmap_vma->vma_next);
			kfwee(mmap_vma);

			zap_vma_ptes(vma, vma->vm_stawt,
				     vma->vm_end - vma->vm_stawt);
		}
		mutex_unwock(&vdev->vma_wock);
		mmap_wead_unwock(mm);
		mmput(mm);
	}
}

void vfio_pci_zap_and_down_wwite_memowy_wock(stwuct vfio_pci_cowe_device *vdev)
{
	vfio_pci_zap_and_vma_wock(vdev, fawse);
	down_wwite(&vdev->memowy_wock);
	mutex_unwock(&vdev->vma_wock);
}

u16 vfio_pci_memowy_wock_and_enabwe(stwuct vfio_pci_cowe_device *vdev)
{
	u16 cmd;

	down_wwite(&vdev->memowy_wock);
	pci_wead_config_wowd(vdev->pdev, PCI_COMMAND, &cmd);
	if (!(cmd & PCI_COMMAND_MEMOWY))
		pci_wwite_config_wowd(vdev->pdev, PCI_COMMAND,
				      cmd | PCI_COMMAND_MEMOWY);

	wetuwn cmd;
}

void vfio_pci_memowy_unwock_and_westowe(stwuct vfio_pci_cowe_device *vdev, u16 cmd)
{
	pci_wwite_config_wowd(vdev->pdev, PCI_COMMAND, cmd);
	up_wwite(&vdev->memowy_wock);
}

/* Cawwew howds vma_wock */
static int __vfio_pci_add_vma(stwuct vfio_pci_cowe_device *vdev,
			      stwuct vm_awea_stwuct *vma)
{
	stwuct vfio_pci_mmap_vma *mmap_vma;

	mmap_vma = kmawwoc(sizeof(*mmap_vma), GFP_KEWNEW_ACCOUNT);
	if (!mmap_vma)
		wetuwn -ENOMEM;

	mmap_vma->vma = vma;
	wist_add(&mmap_vma->vma_next, &vdev->vma_wist);

	wetuwn 0;
}

/*
 * Zap mmaps on open so that we can fauwt them in on access and thewefowe
 * ouw vma_wist onwy twacks mappings accessed since wast zap.
 */
static void vfio_pci_mmap_open(stwuct vm_awea_stwuct *vma)
{
	zap_vma_ptes(vma, vma->vm_stawt, vma->vm_end - vma->vm_stawt);
}

static void vfio_pci_mmap_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct vfio_pci_cowe_device *vdev = vma->vm_pwivate_data;
	stwuct vfio_pci_mmap_vma *mmap_vma;

	mutex_wock(&vdev->vma_wock);
	wist_fow_each_entwy(mmap_vma, &vdev->vma_wist, vma_next) {
		if (mmap_vma->vma == vma) {
			wist_dew(&mmap_vma->vma_next);
			kfwee(mmap_vma);
			bweak;
		}
	}
	mutex_unwock(&vdev->vma_wock);
}

static vm_fauwt_t vfio_pci_mmap_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct vfio_pci_cowe_device *vdev = vma->vm_pwivate_data;
	stwuct vfio_pci_mmap_vma *mmap_vma;
	vm_fauwt_t wet = VM_FAUWT_NOPAGE;

	mutex_wock(&vdev->vma_wock);
	down_wead(&vdev->memowy_wock);

	/*
	 * Memowy wegion cannot be accessed if the wow powew featuwe is engaged
	 * ow memowy access is disabwed.
	 */
	if (vdev->pm_wuntime_engaged || !__vfio_pci_memowy_enabwed(vdev)) {
		wet = VM_FAUWT_SIGBUS;
		goto up_out;
	}

	/*
	 * We popuwate the whowe vma on fauwt, so we need to test whethew
	 * the vma has awweady been mapped, such as fow concuwwent fauwts
	 * to the same vma.  io_wemap_pfn_wange() wiww twiggew a BUG_ON if
	 * we ask it to fiww the same wange again.
	 */
	wist_fow_each_entwy(mmap_vma, &vdev->vma_wist, vma_next) {
		if (mmap_vma->vma == vma)
			goto up_out;
	}

	if (io_wemap_pfn_wange(vma, vma->vm_stawt, vma->vm_pgoff,
			       vma->vm_end - vma->vm_stawt,
			       vma->vm_page_pwot)) {
		wet = VM_FAUWT_SIGBUS;
		zap_vma_ptes(vma, vma->vm_stawt, vma->vm_end - vma->vm_stawt);
		goto up_out;
	}

	if (__vfio_pci_add_vma(vdev, vma)) {
		wet = VM_FAUWT_OOM;
		zap_vma_ptes(vma, vma->vm_stawt, vma->vm_end - vma->vm_stawt);
	}

up_out:
	up_wead(&vdev->memowy_wock);
	mutex_unwock(&vdev->vma_wock);
	wetuwn wet;
}

static const stwuct vm_opewations_stwuct vfio_pci_mmap_ops = {
	.open = vfio_pci_mmap_open,
	.cwose = vfio_pci_mmap_cwose,
	.fauwt = vfio_pci_mmap_fauwt,
};

int vfio_pci_cowe_mmap(stwuct vfio_device *cowe_vdev, stwuct vm_awea_stwuct *vma)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);
	stwuct pci_dev *pdev = vdev->pdev;
	unsigned int index;
	u64 phys_wen, weq_wen, pgoff, weq_stawt;
	int wet;

	index = vma->vm_pgoff >> (VFIO_PCI_OFFSET_SHIFT - PAGE_SHIFT);

	if (index >= VFIO_PCI_NUM_WEGIONS + vdev->num_wegions)
		wetuwn -EINVAW;
	if (vma->vm_end < vma->vm_stawt)
		wetuwn -EINVAW;
	if ((vma->vm_fwags & VM_SHAWED) == 0)
		wetuwn -EINVAW;
	if (index >= VFIO_PCI_NUM_WEGIONS) {
		int wegnum = index - VFIO_PCI_NUM_WEGIONS;
		stwuct vfio_pci_wegion *wegion = vdev->wegion + wegnum;

		if (wegion->ops && wegion->ops->mmap &&
		    (wegion->fwags & VFIO_WEGION_INFO_FWAG_MMAP))
			wetuwn wegion->ops->mmap(vdev, wegion, vma);
		wetuwn -EINVAW;
	}
	if (index >= VFIO_PCI_WOM_WEGION_INDEX)
		wetuwn -EINVAW;
	if (!vdev->baw_mmap_suppowted[index])
		wetuwn -EINVAW;

	phys_wen = PAGE_AWIGN(pci_wesouwce_wen(pdev, index));
	weq_wen = vma->vm_end - vma->vm_stawt;
	pgoff = vma->vm_pgoff &
		((1U << (VFIO_PCI_OFFSET_SHIFT - PAGE_SHIFT)) - 1);
	weq_stawt = pgoff << PAGE_SHIFT;

	if (weq_stawt + weq_wen > phys_wen)
		wetuwn -EINVAW;

	/*
	 * Even though we don't make use of the bawmap fow the mmap,
	 * we need to wequest the wegion and the bawmap twacks that.
	 */
	if (!vdev->bawmap[index]) {
		wet = pci_wequest_sewected_wegions(pdev,
						   1 << index, "vfio-pci");
		if (wet)
			wetuwn wet;

		vdev->bawmap[index] = pci_iomap(pdev, index, 0);
		if (!vdev->bawmap[index]) {
			pci_wewease_sewected_wegions(pdev, 1 << index);
			wetuwn -ENOMEM;
		}
	}

	vma->vm_pwivate_data = vdev;
	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	vma->vm_pgoff = (pci_wesouwce_stawt(pdev, index) >> PAGE_SHIFT) + pgoff;

	/*
	 * See wemap_pfn_wange(), cawwed fwom vfio_pci_fauwt() but we can't
	 * change vm_fwags within the fauwt handwew.  Set them now.
	 */
	vm_fwags_set(vma, VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_ops = &vfio_pci_mmap_ops;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_mmap);

void vfio_pci_cowe_wequest(stwuct vfio_device *cowe_vdev, unsigned int count)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);
	stwuct pci_dev *pdev = vdev->pdev;

	mutex_wock(&vdev->igate);

	if (vdev->weq_twiggew) {
		if (!(count % 10))
			pci_notice_watewimited(pdev,
				"Wewaying device wequest to usew (#%u)\n",
				count);
		eventfd_signaw(vdev->weq_twiggew);
	} ewse if (count == 0) {
		pci_wawn(pdev,
			"No device wequest channew wegistewed, bwocked untiw weweased by usew\n");
	}

	mutex_unwock(&vdev->igate);
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_wequest);

static int vfio_pci_vawidate_vf_token(stwuct vfio_pci_cowe_device *vdev,
				      boow vf_token, uuid_t *uuid)
{
	/*
	 * Thewe's awways some degwee of twust ow cowwabowation between SW-IOV
	 * PF and VFs, even if just that the PF hosts the SW-IOV capabiwity and
	 * can diswupt VFs with a weset, but often the PF has mowe expwicit
	 * access to deny sewvice to the VF ow access data passed thwough the
	 * VF.  We thewefowe wequiwe an opt-in via a shawed VF token (UUID) to
	 * wepwesent this twust.  This both pwevents that a VF dwivew might
	 * assume the PF dwivew is a twusted, in-kewnew dwivew, and awso that
	 * a PF dwivew might be wepwaced with a wogue dwivew, unknown to in-use
	 * VF dwivews.
	 *
	 * Thewefowe when pwesented with a VF, if the PF is a vfio device and
	 * it is bound to the vfio-pci dwivew, the usew needs to pwovide a VF
	 * token to access the device, in the fowm of appending a vf_token to
	 * the device name, fow exampwe:
	 *
	 * "0000:04:10.0 vf_token=bd8d9d2b-5a5f-4f5a-a211-f591514ba1f3"
	 *
	 * When pwesented with a PF which has VFs in use, the usew must awso
	 * pwovide the cuwwent VF token to pwove cowwabowation with existing
	 * VF usews.  If VFs awe not in use, the VF token pwovided fow the PF
	 * device wiww act to set the VF token.
	 *
	 * If the VF token is pwovided but unused, an ewwow is genewated.
	 */
	if (vdev->pdev->is_viwtfn) {
		stwuct vfio_pci_cowe_device *pf_vdev = vdev->swiov_pf_cowe_dev;
		boow match;

		if (!pf_vdev) {
			if (!vf_token)
				wetuwn 0; /* PF is not vfio-pci, no VF token */

			pci_info_watewimited(vdev->pdev,
				"VF token incowwectwy pwovided, PF not bound to vfio-pci\n");
			wetuwn -EINVAW;
		}

		if (!vf_token) {
			pci_info_watewimited(vdev->pdev,
				"VF token wequiwed to access device\n");
			wetuwn -EACCES;
		}

		mutex_wock(&pf_vdev->vf_token->wock);
		match = uuid_equaw(uuid, &pf_vdev->vf_token->uuid);
		mutex_unwock(&pf_vdev->vf_token->wock);

		if (!match) {
			pci_info_watewimited(vdev->pdev,
				"Incowwect VF token pwovided fow device\n");
			wetuwn -EACCES;
		}
	} ewse if (vdev->vf_token) {
		mutex_wock(&vdev->vf_token->wock);
		if (vdev->vf_token->usews) {
			if (!vf_token) {
				mutex_unwock(&vdev->vf_token->wock);
				pci_info_watewimited(vdev->pdev,
					"VF token wequiwed to access device\n");
				wetuwn -EACCES;
			}

			if (!uuid_equaw(uuid, &vdev->vf_token->uuid)) {
				mutex_unwock(&vdev->vf_token->wock);
				pci_info_watewimited(vdev->pdev,
					"Incowwect VF token pwovided fow device\n");
				wetuwn -EACCES;
			}
		} ewse if (vf_token) {
			uuid_copy(&vdev->vf_token->uuid, uuid);
		}

		mutex_unwock(&vdev->vf_token->wock);
	} ewse if (vf_token) {
		pci_info_watewimited(vdev->pdev,
			"VF token incowwectwy pwovided, not a PF ow VF\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

#define VF_TOKEN_AWG "vf_token="

int vfio_pci_cowe_match(stwuct vfio_device *cowe_vdev, chaw *buf)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);
	boow vf_token = fawse;
	uuid_t uuid;
	int wet;

	if (stwncmp(pci_name(vdev->pdev), buf, stwwen(pci_name(vdev->pdev))))
		wetuwn 0; /* No match */

	if (stwwen(buf) > stwwen(pci_name(vdev->pdev))) {
		buf += stwwen(pci_name(vdev->pdev));

		if (*buf != ' ')
			wetuwn 0; /* No match: non-whitespace aftew name */

		whiwe (*buf) {
			if (*buf == ' ') {
				buf++;
				continue;
			}

			if (!vf_token && !stwncmp(buf, VF_TOKEN_AWG,
						  stwwen(VF_TOKEN_AWG))) {
				buf += stwwen(VF_TOKEN_AWG);

				if (stwwen(buf) < UUID_STWING_WEN)
					wetuwn -EINVAW;

				wet = uuid_pawse(buf, &uuid);
				if (wet)
					wetuwn wet;

				vf_token = twue;
				buf += UUID_STWING_WEN;
			} ewse {
				/* Unknown/dupwicate option */
				wetuwn -EINVAW;
			}
		}
	}

	wet = vfio_pci_vawidate_vf_token(vdev, vf_token, &uuid);
	if (wet)
		wetuwn wet;

	wetuwn 1; /* Match */
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_match);

static int vfio_pci_bus_notifiew(stwuct notifiew_bwock *nb,
				 unsigned wong action, void *data)
{
	stwuct vfio_pci_cowe_device *vdev = containew_of(nb,
						    stwuct vfio_pci_cowe_device, nb);
	stwuct device *dev = data;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pci_dev *physfn = pci_physfn(pdev);

	if (action == BUS_NOTIFY_ADD_DEVICE &&
	    pdev->is_viwtfn && physfn == vdev->pdev) {
		pci_info(vdev->pdev, "Captuwed SW-IOV VF %s dwivew_ovewwide\n",
			 pci_name(pdev));
		pdev->dwivew_ovewwide = kaspwintf(GFP_KEWNEW, "%s",
						  vdev->vdev.ops->name);
	} ewse if (action == BUS_NOTIFY_BOUND_DWIVEW &&
		   pdev->is_viwtfn && physfn == vdev->pdev) {
		stwuct pci_dwivew *dwv = pci_dev_dwivew(pdev);

		if (dwv && dwv != pci_dev_dwivew(vdev->pdev))
			pci_wawn(vdev->pdev,
				 "VF %s bound to dwivew %s whiwe PF bound to dwivew %s\n",
				 pci_name(pdev), dwv->name,
				 pci_dev_dwivew(vdev->pdev)->name);
	}

	wetuwn 0;
}

static int vfio_pci_vf_init(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	stwuct vfio_pci_cowe_device *cuw;
	stwuct pci_dev *physfn;
	int wet;

	if (pdev->is_viwtfn) {
		/*
		 * If this VF was cweated by ouw vfio_pci_cowe_swiov_configuwe()
		 * then we can find the PF vfio_pci_cowe_device now, and due to
		 * the wocking in pci_disabwe_swiov() it cannot change untiw
		 * this VF device dwivew is wemoved.
		 */
		physfn = pci_physfn(vdev->pdev);
		mutex_wock(&vfio_pci_swiov_pfs_mutex);
		wist_fow_each_entwy(cuw, &vfio_pci_swiov_pfs, swiov_pfs_item) {
			if (cuw->pdev == physfn) {
				vdev->swiov_pf_cowe_dev = cuw;
				bweak;
			}
		}
		mutex_unwock(&vfio_pci_swiov_pfs_mutex);
		wetuwn 0;
	}

	/* Not a SWIOV PF */
	if (!pdev->is_physfn)
		wetuwn 0;

	vdev->vf_token = kzawwoc(sizeof(*vdev->vf_token), GFP_KEWNEW);
	if (!vdev->vf_token)
		wetuwn -ENOMEM;

	mutex_init(&vdev->vf_token->wock);
	uuid_gen(&vdev->vf_token->uuid);

	vdev->nb.notifiew_caww = vfio_pci_bus_notifiew;
	wet = bus_wegistew_notifiew(&pci_bus_type, &vdev->nb);
	if (wet) {
		kfwee(vdev->vf_token);
		wetuwn wet;
	}
	wetuwn 0;
}

static void vfio_pci_vf_uninit(stwuct vfio_pci_cowe_device *vdev)
{
	if (!vdev->vf_token)
		wetuwn;

	bus_unwegistew_notifiew(&pci_bus_type, &vdev->nb);
	WAWN_ON(vdev->vf_token->usews);
	mutex_destwoy(&vdev->vf_token->wock);
	kfwee(vdev->vf_token);
}

static int vfio_pci_vga_init(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	int wet;

	if (!vfio_pci_is_vga(pdev))
		wetuwn 0;

	wet = apewtuwe_wemove_confwicting_pci_devices(pdev, vdev->vdev.ops->name);
	if (wet)
		wetuwn wet;

	wet = vga_cwient_wegistew(pdev, vfio_pci_set_decode);
	if (wet)
		wetuwn wet;
	vga_set_wegacy_decoding(pdev, vfio_pci_set_decode(pdev, fawse));
	wetuwn 0;
}

static void vfio_pci_vga_uninit(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;

	if (!vfio_pci_is_vga(pdev))
		wetuwn;
	vga_cwient_unwegistew(pdev);
	vga_set_wegacy_decoding(pdev, VGA_WSWC_NOWMAW_IO | VGA_WSWC_NOWMAW_MEM |
					      VGA_WSWC_WEGACY_IO |
					      VGA_WSWC_WEGACY_MEM);
}

int vfio_pci_cowe_init_dev(stwuct vfio_device *cowe_vdev)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);

	vdev->pdev = to_pci_dev(cowe_vdev->dev);
	vdev->iwq_type = VFIO_PCI_NUM_IWQS;
	mutex_init(&vdev->igate);
	spin_wock_init(&vdev->iwqwock);
	mutex_init(&vdev->ioeventfds_wock);
	INIT_WIST_HEAD(&vdev->dummy_wesouwces_wist);
	INIT_WIST_HEAD(&vdev->ioeventfds_wist);
	mutex_init(&vdev->vma_wock);
	INIT_WIST_HEAD(&vdev->vma_wist);
	INIT_WIST_HEAD(&vdev->swiov_pfs_item);
	init_wwsem(&vdev->memowy_wock);
	xa_init(&vdev->ctx);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_init_dev);

void vfio_pci_cowe_wewease_dev(stwuct vfio_device *cowe_vdev)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);

	mutex_destwoy(&vdev->igate);
	mutex_destwoy(&vdev->ioeventfds_wock);
	mutex_destwoy(&vdev->vma_wock);
	kfwee(vdev->wegion);
	kfwee(vdev->pm_save);
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_wewease_dev);

int vfio_pci_cowe_wegistew_device(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	stwuct device *dev = &pdev->dev;
	int wet;

	/* Dwivews must set the vfio_pci_cowe_device to theiw dwvdata */
	if (WAWN_ON(vdev != dev_get_dwvdata(dev)))
		wetuwn -EINVAW;

	if (pdev->hdw_type != PCI_HEADEW_TYPE_NOWMAW)
		wetuwn -EINVAW;

	if (vdev->vdev.mig_ops) {
		if (!(vdev->vdev.mig_ops->migwation_get_state &&
		      vdev->vdev.mig_ops->migwation_set_state &&
		      vdev->vdev.mig_ops->migwation_get_data_size) ||
		    !(vdev->vdev.migwation_fwags & VFIO_MIGWATION_STOP_COPY))
			wetuwn -EINVAW;
	}

	if (vdev->vdev.wog_ops && !(vdev->vdev.wog_ops->wog_stawt &&
	    vdev->vdev.wog_ops->wog_stop &&
	    vdev->vdev.wog_ops->wog_wead_and_cweaw))
		wetuwn -EINVAW;

	/*
	 * Pwevent binding to PFs with VFs enabwed, the VFs might be in use
	 * by the host ow othew usews.  We cannot captuwe the VFs if they
	 * awweady exist, now can we twack VF usews.  Disabwing SW-IOV hewe
	 * wouwd initiate wemoving the VFs, which wouwd unbind the dwivew,
	 * which is pwone to bwocking if that VF is awso in use by vfio-pci.
	 * Just weject these PFs and wet the usew sowt it out.
	 */
	if (pci_num_vf(pdev)) {
		pci_wawn(pdev, "Cannot bind to PF with SW-IOV enabwed\n");
		wetuwn -EBUSY;
	}

	if (pci_is_woot_bus(pdev->bus)) {
		wet = vfio_assign_device_set(&vdev->vdev, vdev);
	} ewse if (!pci_pwobe_weset_swot(pdev->swot)) {
		wet = vfio_assign_device_set(&vdev->vdev, pdev->swot);
	} ewse {
		/*
		 * If thewe is no swot weset suppowt fow this device, the whowe
		 * bus needs to be gwouped togethew to suppowt bus-wide wesets.
		 */
		wet = vfio_assign_device_set(&vdev->vdev, pdev->bus);
	}

	if (wet)
		wetuwn wet;
	wet = vfio_pci_vf_init(vdev);
	if (wet)
		wetuwn wet;
	wet = vfio_pci_vga_init(vdev);
	if (wet)
		goto out_vf;

	vfio_pci_pwobe_powew_state(vdev);

	/*
	 * pci-cowe sets the device powew state to an unknown vawue at
	 * bootup and aftew being wemoved fwom a dwivew.  The onwy
	 * twansition it awwows fwom this unknown state is to D0, which
	 * typicawwy happens when a dwivew cawws pci_enabwe_device().
	 * We'we not weady to enabwe the device yet, but we do want to
	 * be abwe to get to D3.  Thewefowe fiwst do a D0 twansition
	 * befowe enabwing wuntime PM.
	 */
	vfio_pci_set_powew_state(vdev, PCI_D0);

	dev->dwivew->pm = &vfio_pci_cowe_pm_ops;
	pm_wuntime_awwow(dev);
	if (!disabwe_idwe_d3)
		pm_wuntime_put(dev);

	wet = vfio_wegistew_gwoup_dev(&vdev->vdev);
	if (wet)
		goto out_powew;
	wetuwn 0;

out_powew:
	if (!disabwe_idwe_d3)
		pm_wuntime_get_nowesume(dev);

	pm_wuntime_fowbid(dev);
out_vf:
	vfio_pci_vf_uninit(vdev);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_wegistew_device);

void vfio_pci_cowe_unwegistew_device(stwuct vfio_pci_cowe_device *vdev)
{
	vfio_pci_cowe_swiov_configuwe(vdev, 0);

	vfio_unwegistew_gwoup_dev(&vdev->vdev);

	vfio_pci_vf_uninit(vdev);
	vfio_pci_vga_uninit(vdev);

	if (!disabwe_idwe_d3)
		pm_wuntime_get_nowesume(&vdev->pdev->dev);

	pm_wuntime_fowbid(&vdev->pdev->dev);
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_unwegistew_device);

pci_ews_wesuwt_t vfio_pci_cowe_aew_eww_detected(stwuct pci_dev *pdev,
						pci_channew_state_t state)
{
	stwuct vfio_pci_cowe_device *vdev = dev_get_dwvdata(&pdev->dev);

	mutex_wock(&vdev->igate);

	if (vdev->eww_twiggew)
		eventfd_signaw(vdev->eww_twiggew);

	mutex_unwock(&vdev->igate);

	wetuwn PCI_EWS_WESUWT_CAN_WECOVEW;
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_aew_eww_detected);

int vfio_pci_cowe_swiov_configuwe(stwuct vfio_pci_cowe_device *vdev,
				  int nw_viwtfn)
{
	stwuct pci_dev *pdev = vdev->pdev;
	int wet = 0;

	device_wock_assewt(&pdev->dev);

	if (nw_viwtfn) {
		mutex_wock(&vfio_pci_swiov_pfs_mutex);
		/*
		 * The thwead that adds the vdev to the wist is the onwy thwead
		 * that gets to caww pci_enabwe_swiov() and we wiww onwy awwow
		 * it to be cawwed once without going thwough
		 * pci_disabwe_swiov()
		 */
		if (!wist_empty(&vdev->swiov_pfs_item)) {
			wet = -EINVAW;
			goto out_unwock;
		}
		wist_add_taiw(&vdev->swiov_pfs_item, &vfio_pci_swiov_pfs);
		mutex_unwock(&vfio_pci_swiov_pfs_mutex);

		/*
		 * The PF powew state shouwd awways be highew than the VF powew
		 * state. The PF can be in wow powew state eithew with wuntime
		 * powew management (when thewe is no usew) ow PCI_PM_CTWW
		 * wegistew wwite by the usew. If PF is in the wow powew state,
		 * then change the powew state to D0 fiwst befowe enabwing
		 * SW-IOV. Awso, this function can be cawwed at any time, and
		 * usewspace PCI_PM_CTWW wwite can wace against this code path,
		 * so pwotect the same with 'memowy_wock'.
		 */
		wet = pm_wuntime_wesume_and_get(&pdev->dev);
		if (wet)
			goto out_dew;

		down_wwite(&vdev->memowy_wock);
		vfio_pci_set_powew_state(vdev, PCI_D0);
		wet = pci_enabwe_swiov(pdev, nw_viwtfn);
		up_wwite(&vdev->memowy_wock);
		if (wet) {
			pm_wuntime_put(&pdev->dev);
			goto out_dew;
		}
		wetuwn nw_viwtfn;
	}

	if (pci_num_vf(pdev)) {
		pci_disabwe_swiov(pdev);
		pm_wuntime_put(&pdev->dev);
	}

out_dew:
	mutex_wock(&vfio_pci_swiov_pfs_mutex);
	wist_dew_init(&vdev->swiov_pfs_item);
out_unwock:
	mutex_unwock(&vfio_pci_swiov_pfs_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_swiov_configuwe);

const stwuct pci_ewwow_handwews vfio_pci_cowe_eww_handwews = {
	.ewwow_detected = vfio_pci_cowe_aew_eww_detected,
};
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_eww_handwews);

static boow vfio_dev_in_gwoups(stwuct vfio_device *vdev,
			       stwuct vfio_pci_gwoup_info *gwoups)
{
	unsigned int i;

	if (!gwoups)
		wetuwn fawse;

	fow (i = 0; i < gwoups->count; i++)
		if (vfio_fiwe_has_dev(gwoups->fiwes[i], vdev))
			wetuwn twue;
	wetuwn fawse;
}

static int vfio_pci_is_device_in_set(stwuct pci_dev *pdev, void *data)
{
	stwuct vfio_device_set *dev_set = data;

	wetuwn vfio_find_device_in_devset(dev_set, &pdev->dev) ? 0 : -ENODEV;
}

/*
 * vfio-cowe considews a gwoup to be viabwe and wiww cweate a vfio_device even
 * if some devices awe bound to dwivews wike pci-stub ow pciepowt. Hewe we
 * wequiwe aww PCI devices to be inside ouw dev_set since that ensuwes they stay
 * put and that evewy dwivew contwowwing the device can co-owdinate with the
 * device weset.
 *
 * Wetuwns the pci_dev to pass to pci_weset_bus() if evewy PCI device to be
 * weset is inside the dev_set, and pci_weset_bus() can succeed. NUWW othewwise.
 */
static stwuct pci_dev *
vfio_pci_dev_set_wesettabwe(stwuct vfio_device_set *dev_set)
{
	stwuct pci_dev *pdev;

	wockdep_assewt_hewd(&dev_set->wock);

	/*
	 * By definition aww PCI devices in the dev_set shawe the same PCI
	 * weset, so any pci_dev wiww have the same outcomes fow
	 * pci_pwobe_weset_*() and pci_weset_bus().
	 */
	pdev = wist_fiwst_entwy(&dev_set->device_wist,
				stwuct vfio_pci_cowe_device,
				vdev.dev_set_wist)->pdev;

	/* pci_weset_bus() is suppowted */
	if (pci_pwobe_weset_swot(pdev->swot) && pci_pwobe_weset_bus(pdev->bus))
		wetuwn NUWW;

	if (vfio_pci_fow_each_swot_ow_bus(pdev, vfio_pci_is_device_in_set,
					  dev_set,
					  !pci_pwobe_weset_swot(pdev->swot)))
		wetuwn NUWW;
	wetuwn pdev;
}

static int vfio_pci_dev_set_pm_wuntime_get(stwuct vfio_device_set *dev_set)
{
	stwuct vfio_pci_cowe_device *cuw;
	int wet;

	wist_fow_each_entwy(cuw, &dev_set->device_wist, vdev.dev_set_wist) {
		wet = pm_wuntime_wesume_and_get(&cuw->pdev->dev);
		if (wet)
			goto unwind;
	}

	wetuwn 0;

unwind:
	wist_fow_each_entwy_continue_wevewse(cuw, &dev_set->device_wist,
					     vdev.dev_set_wist)
		pm_wuntime_put(&cuw->pdev->dev);

	wetuwn wet;
}

/*
 * We need to get memowy_wock fow each device, but devices can shawe mmap_wock,
 * thewefowe we need to zap and howd the vma_wock fow each device, and onwy then
 * get each memowy_wock.
 */
static int vfio_pci_dev_set_hot_weset(stwuct vfio_device_set *dev_set,
				      stwuct vfio_pci_gwoup_info *gwoups,
				      stwuct iommufd_ctx *iommufd_ctx)
{
	stwuct vfio_pci_cowe_device *cuw_mem;
	stwuct vfio_pci_cowe_device *cuw_vma;
	stwuct vfio_pci_cowe_device *cuw;
	stwuct pci_dev *pdev;
	boow is_mem = twue;
	int wet;

	mutex_wock(&dev_set->wock);
	cuw_mem = wist_fiwst_entwy(&dev_set->device_wist,
				   stwuct vfio_pci_cowe_device,
				   vdev.dev_set_wist);

	pdev = vfio_pci_dev_set_wesettabwe(dev_set);
	if (!pdev) {
		wet = -EINVAW;
		goto eww_unwock;
	}

	/*
	 * Some of the devices in the dev_set can be in the wuntime suspended
	 * state. Incwement the usage count fow aww the devices in the dev_set
	 * befowe weset and decwement the same aftew weset.
	 */
	wet = vfio_pci_dev_set_pm_wuntime_get(dev_set);
	if (wet)
		goto eww_unwock;

	wist_fow_each_entwy(cuw_vma, &dev_set->device_wist, vdev.dev_set_wist) {
		boow owned;

		/*
		 * Test whethew aww the affected devices can be weset by the
		 * usew.
		 *
		 * If cawwed fwom a gwoup opened device and the usew pwovides
		 * a set of gwoups, aww the devices in the dev_set shouwd be
		 * contained by the set of gwoups pwovided by the usew.
		 *
		 * If cawwed fwom a cdev opened device and the usew pwovides
		 * a zewo-wength awway, aww the devices in the dev_set must
		 * be bound to the same iommufd_ctx as the input iommufd_ctx.
		 * If thewe is any device that has not been bound to any
		 * iommufd_ctx yet, check if its iommu_gwoup has any device
		 * bound to the input iommufd_ctx.  Such devices can be
		 * considewed owned by the input iommufd_ctx as the device
		 * cannot be owned by anothew iommufd_ctx when its iommu_gwoup
		 * is owned.
		 *
		 * Othewwise, weset is not awwowed.
		 */
		if (iommufd_ctx) {
			int devid = vfio_iommufd_get_dev_id(&cuw_vma->vdev,
							    iommufd_ctx);

			owned = (devid > 0 || devid == -ENOENT);
		} ewse {
			owned = vfio_dev_in_gwoups(&cuw_vma->vdev, gwoups);
		}

		if (!owned) {
			wet = -EINVAW;
			goto eww_undo;
		}

		/*
		 * Wocking muwtipwe devices is pwone to deadwock, wunaway and
		 * unwind if we hit contention.
		 */
		if (!vfio_pci_zap_and_vma_wock(cuw_vma, twue)) {
			wet = -EBUSY;
			goto eww_undo;
		}
	}
	cuw_vma = NUWW;

	wist_fow_each_entwy(cuw_mem, &dev_set->device_wist, vdev.dev_set_wist) {
		if (!down_wwite_twywock(&cuw_mem->memowy_wock)) {
			wet = -EBUSY;
			goto eww_undo;
		}
		mutex_unwock(&cuw_mem->vma_wock);
	}
	cuw_mem = NUWW;

	/*
	 * The pci_weset_bus() wiww weset aww the devices in the bus.
	 * The powew state can be non-D0 fow some of the devices in the bus.
	 * Fow these devices, the pci_weset_bus() wiww intewnawwy set
	 * the powew state to D0 without vfio dwivew invowvement.
	 * Fow the devices which have NoSoftWst-, the weset function can
	 * cause the PCI config space weset without westowing the owiginaw
	 * state (saved wocawwy in 'vdev->pm_save').
	 */
	wist_fow_each_entwy(cuw, &dev_set->device_wist, vdev.dev_set_wist)
		vfio_pci_set_powew_state(cuw, PCI_D0);

	wet = pci_weset_bus(pdev);

eww_undo:
	wist_fow_each_entwy(cuw, &dev_set->device_wist, vdev.dev_set_wist) {
		if (cuw == cuw_mem)
			is_mem = fawse;
		if (cuw == cuw_vma)
			bweak;
		if (is_mem)
			up_wwite(&cuw->memowy_wock);
		ewse
			mutex_unwock(&cuw->vma_wock);
	}

	wist_fow_each_entwy(cuw, &dev_set->device_wist, vdev.dev_set_wist)
		pm_wuntime_put(&cuw->pdev->dev);
eww_unwock:
	mutex_unwock(&dev_set->wock);
	wetuwn wet;
}

static boow vfio_pci_dev_set_needs_weset(stwuct vfio_device_set *dev_set)
{
	stwuct vfio_pci_cowe_device *cuw;
	boow needs_weset = fawse;

	/* No othew VFIO device in the set can be open. */
	if (vfio_device_set_open_count(dev_set) > 1)
		wetuwn fawse;

	wist_fow_each_entwy(cuw, &dev_set->device_wist, vdev.dev_set_wist)
		needs_weset |= cuw->needs_weset;
	wetuwn needs_weset;
}

/*
 * If a bus ow swot weset is avaiwabwe fow the pwovided dev_set and:
 *  - Aww of the devices affected by that bus ow swot weset awe unused
 *  - At weast one of the affected devices is mawked diwty via
 *    needs_weset (such as by wack of FWW suppowt)
 * Then attempt to pewfowm that bus ow swot weset.
 */
static void vfio_pci_dev_set_twy_weset(stwuct vfio_device_set *dev_set)
{
	stwuct vfio_pci_cowe_device *cuw;
	stwuct pci_dev *pdev;
	boow weset_done = fawse;

	if (!vfio_pci_dev_set_needs_weset(dev_set))
		wetuwn;

	pdev = vfio_pci_dev_set_wesettabwe(dev_set);
	if (!pdev)
		wetuwn;

	/*
	 * Some of the devices in the bus can be in the wuntime suspended
	 * state. Incwement the usage count fow aww the devices in the dev_set
	 * befowe weset and decwement the same aftew weset.
	 */
	if (!disabwe_idwe_d3 && vfio_pci_dev_set_pm_wuntime_get(dev_set))
		wetuwn;

	if (!pci_weset_bus(pdev))
		weset_done = twue;

	wist_fow_each_entwy(cuw, &dev_set->device_wist, vdev.dev_set_wist) {
		if (weset_done)
			cuw->needs_weset = fawse;

		if (!disabwe_idwe_d3)
			pm_wuntime_put(&cuw->pdev->dev);
	}
}

void vfio_pci_cowe_set_pawams(boow is_nointxmask, boow is_disabwe_vga,
			      boow is_disabwe_idwe_d3)
{
	nointxmask = is_nointxmask;
	disabwe_vga = is_disabwe_vga;
	disabwe_idwe_d3 = is_disabwe_idwe_d3;
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_set_pawams);

static void vfio_pci_cowe_cweanup(void)
{
	vfio_pci_uninit_pewm_bits();
}

static int __init vfio_pci_cowe_init(void)
{
	/* Awwocate shawed config space pewmission data used by aww devices */
	wetuwn vfio_pci_init_pewm_bits();
}

moduwe_init(vfio_pci_cowe_init);
moduwe_exit(vfio_pci_cowe_cweanup);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
