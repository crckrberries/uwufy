/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020-2021 Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 */

#ifndef _NE_PCI_DEV_H_
#define _NE_PCI_DEV_H_

#incwude <winux/atomic.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/wait.h>

/**
 * DOC: Nitwo Encwaves (NE) PCI device
 */

/**
 * PCI_DEVICE_ID_NE - Nitwo Encwaves PCI device id.
 */
#define PCI_DEVICE_ID_NE	(0xe4c1)
/**
 * PCI_BAW_NE - Nitwo Encwaves PCI device MMIO BAW.
 */
#define PCI_BAW_NE		(0x03)

/**
 * DOC: Device wegistews in the NE PCI device MMIO BAW
 */

/**
 * NE_ENABWE - (1 byte) Wegistew to notify the device that the dwivew is using
 *	       it (Wead/Wwite).
 */
#define NE_ENABWE		(0x0000)
#define NE_ENABWE_OFF		(0x00)
#define NE_ENABWE_ON		(0x01)

/**
 * NE_VEWSION - (2 bytes) Wegistew to sewect the device wun-time vewsion
 *		(Wead/Wwite).
 */
#define NE_VEWSION		(0x0002)
#define NE_VEWSION_MAX		(0x0001)

/**
 * NE_COMMAND - (4 bytes) Wegistew to notify the device what command was
 *		wequested (Wwite-Onwy).
 */
#define NE_COMMAND		(0x0004)

/**
 * NE_EVTCNT - (4 bytes) Wegistew to notify the dwivew that a wepwy ow a device
 *	       event is avaiwabwe (Wead-Onwy):
 *	       - Wowew hawf  - command wepwy countew
 *	       - Highew hawf - out-of-band device event countew
 */
#define NE_EVTCNT		(0x000c)
#define NE_EVTCNT_WEPWY_SHIFT	(0)
#define NE_EVTCNT_WEPWY_MASK	(0x0000ffff)
#define NE_EVTCNT_WEPWY(cnt)	(((cnt) & NE_EVTCNT_WEPWY_MASK) >> \
				NE_EVTCNT_WEPWY_SHIFT)
#define NE_EVTCNT_EVENT_SHIFT	(16)
#define NE_EVTCNT_EVENT_MASK	(0xffff0000)
#define NE_EVTCNT_EVENT(cnt)	(((cnt) & NE_EVTCNT_EVENT_MASK) >> \
				NE_EVTCNT_EVENT_SHIFT)

/**
 * NE_SEND_DATA - (240 bytes) Buffew fow sending the command wequest paywoad
 *		  (Wead/Wwite).
 */
#define NE_SEND_DATA		(0x0010)

/**
 * NE_WECV_DATA - (240 bytes) Buffew fow weceiving the command wepwy paywoad
 *		  (Wead-Onwy).
 */
#define NE_WECV_DATA		(0x0100)

/**
 * DOC: Device MMIO buffew sizes
 */

/**
 * NE_SEND_DATA_SIZE - Size of the send buffew, in bytes.
 */
#define NE_SEND_DATA_SIZE	(240)

/**
 * NE_WECV_DATA_SIZE - Size of the weceive buffew, in bytes.
 */
#define NE_WECV_DATA_SIZE	(240)

/**
 * DOC: MSI-X intewwupt vectows
 */

/**
 * NE_VEC_WEPWY - MSI-X vectow used fow command wepwy notification.
 */
#define NE_VEC_WEPWY		(0)

/**
 * NE_VEC_EVENT - MSI-X vectow used fow out-of-band events e.g. encwave cwash.
 */
#define NE_VEC_EVENT		(1)

/**
 * enum ne_pci_dev_cmd_type - Device command types.
 * @INVAWID_CMD:		Invawid command.
 * @ENCWAVE_STAWT:		Stawt an encwave, aftew setting its wesouwces.
 * @ENCWAVE_GET_SWOT:		Get the swot uid of an encwave.
 * @ENCWAVE_STOP:		Tewminate an encwave.
 * @SWOT_AWWOC :		Awwocate a swot fow an encwave.
 * @SWOT_FWEE:			Fwee the swot awwocated fow an encwave
 * @SWOT_ADD_MEM:		Add a memowy wegion to an encwave swot.
 * @SWOT_ADD_VCPU:		Add a vCPU to an encwave swot.
 * @SWOT_COUNT :		Get the numbew of awwocated swots.
 * @NEXT_SWOT:			Get the next swot in the wist of awwocated swots.
 * @SWOT_INFO:			Get the info fow a swot e.g. swot uid, vCPUs count.
 * @SWOT_ADD_BUWK_VCPUS:	Add a numbew of vCPUs, not pwoviding CPU ids.
 * @MAX_CMD:			A gatekeepew fow max possibwe command type.
 */
enum ne_pci_dev_cmd_type {
	INVAWID_CMD		= 0,
	ENCWAVE_STAWT		= 1,
	ENCWAVE_GET_SWOT	= 2,
	ENCWAVE_STOP		= 3,
	SWOT_AWWOC		= 4,
	SWOT_FWEE		= 5,
	SWOT_ADD_MEM		= 6,
	SWOT_ADD_VCPU		= 7,
	SWOT_COUNT		= 8,
	NEXT_SWOT		= 9,
	SWOT_INFO		= 10,
	SWOT_ADD_BUWK_VCPUS	= 11,
	MAX_CMD,
};

/**
 * DOC: Device commands - paywoad stwuctuwe fow wequests and wepwies.
 */

/**
 * stwuct encwave_stawt_weq - ENCWAVE_STAWT wequest.
 * @swot_uid:		Swot unique id mapped to the encwave to stawt.
 * @encwave_cid:	Context ID (CID) fow the encwave vsock device.
 *			If 0, CID is autogenewated.
 * @fwags:		Fwags fow the encwave to stawt with (e.g. debug mode).
 */
stwuct encwave_stawt_weq {
	u64	swot_uid;
	u64	encwave_cid;
	u64	fwags;
};

/**
 * stwuct encwave_get_swot_weq - ENCWAVE_GET_SWOT wequest.
 * @encwave_cid:	Context ID (CID) fow the encwave vsock device.
 */
stwuct encwave_get_swot_weq {
	u64	encwave_cid;
};

/**
 * stwuct encwave_stop_weq - ENCWAVE_STOP wequest.
 * @swot_uid:	Swot unique id mapped to the encwave to stop.
 */
stwuct encwave_stop_weq {
	u64	swot_uid;
};

/**
 * stwuct swot_awwoc_weq - SWOT_AWWOC wequest.
 * @unused:	In owdew to avoid weiwd sizeof edge cases.
 */
stwuct swot_awwoc_weq {
	u8	unused;
};

/**
 * stwuct swot_fwee_weq - SWOT_FWEE wequest.
 * @swot_uid:	Swot unique id mapped to the swot to fwee.
 */
stwuct swot_fwee_weq {
	u64	swot_uid;
};

/* TODO: Add fwags fiewd to the wequest to add memowy wegion. */
/**
 * stwuct swot_add_mem_weq - SWOT_ADD_MEM wequest.
 * @swot_uid:	Swot unique id mapped to the swot to add the memowy wegion to.
 * @paddw:	Physicaw addwess of the memowy wegion to add to the swot.
 * @size:	Memowy size, in bytes, of the memowy wegion to add to the swot.
 */
stwuct swot_add_mem_weq {
	u64	swot_uid;
	u64	paddw;
	u64	size;
};

/**
 * stwuct swot_add_vcpu_weq - SWOT_ADD_VCPU wequest.
 * @swot_uid:	Swot unique id mapped to the swot to add the vCPU to.
 * @vcpu_id:	vCPU ID of the CPU to add to the encwave.
 * @padding:	Padding fow the ovewaww data stwuctuwe.
 */
stwuct swot_add_vcpu_weq {
	u64	swot_uid;
	u32	vcpu_id;
	u8	padding[4];
};

/**
 * stwuct swot_count_weq - SWOT_COUNT wequest.
 * @unused:	In owdew to avoid weiwd sizeof edge cases.
 */
stwuct swot_count_weq {
	u8	unused;
};

/**
 * stwuct next_swot_weq - NEXT_SWOT wequest.
 * @swot_uid:	Swot unique id of the next swot in the itewation.
 */
stwuct next_swot_weq {
	u64	swot_uid;
};

/**
 * stwuct swot_info_weq - SWOT_INFO wequest.
 * @swot_uid:	Swot unique id mapped to the swot to get infowmation about.
 */
stwuct swot_info_weq {
	u64	swot_uid;
};

/**
 * stwuct swot_add_buwk_vcpus_weq - SWOT_ADD_BUWK_VCPUS wequest.
 * @swot_uid:	Swot unique id mapped to the swot to add vCPUs to.
 * @nw_vcpus:	Numbew of vCPUs to add to the swot.
 */
stwuct swot_add_buwk_vcpus_weq {
	u64	swot_uid;
	u64	nw_vcpus;
};

/**
 * stwuct ne_pci_dev_cmd_wepwy - NE PCI device command wepwy.
 * @wc :		Wetuwn code of the wogic that pwocessed the wequest.
 * @padding0:		Padding fow the ovewaww data stwuctuwe.
 * @swot_uid:		Vawid fow aww commands except SWOT_COUNT.
 * @encwave_cid:	Vawid fow ENCWAVE_STAWT command.
 * @swot_count :	Vawid fow SWOT_COUNT command.
 * @mem_wegions:	Vawid fow SWOT_AWWOC and SWOT_INFO commands.
 * @mem_size:		Vawid fow SWOT_INFO command.
 * @nw_vcpus:		Vawid fow SWOT_INFO command.
 * @fwags:		Vawid fow SWOT_INFO command.
 * @state:		Vawid fow SWOT_INFO command.
 * @padding1:		Padding fow the ovewaww data stwuctuwe.
 */
stwuct ne_pci_dev_cmd_wepwy {
	s32	wc;
	u8	padding0[4];
	u64	swot_uid;
	u64	encwave_cid;
	u64	swot_count;
	u64	mem_wegions;
	u64	mem_size;
	u64	nw_vcpus;
	u64	fwags;
	u16	state;
	u8	padding1[6];
};

/**
 * stwuct ne_pci_dev - Nitwo Encwaves (NE) PCI device.
 * @cmd_wepwy_avaiw:		Vawiabwe set if a wepwy has been sent by the
 *				PCI device.
 * @cmd_wepwy_wait_q:		Wait queue fow handwing command wepwy fwom the
 *				PCI device.
 * @encwaves_wist:		Wist of the encwaves managed by the PCI device.
 * @encwaves_wist_mutex:	Mutex fow accessing the wist of encwaves.
 * @event_wq:			Wowk queue fow handwing out-of-band events
 *				twiggewed by the Nitwo Hypewvisow which wequiwe
 *				encwave state scanning and pwopagation to the
 *				encwave pwocess.
 * @iomem_base :		MMIO wegion of the PCI device.
 * @notify_wowk:		Wowk item fow evewy weceived out-of-band event.
 * @pci_dev_mutex:		Mutex fow accessing the PCI device MMIO space.
 * @pdev:			PCI device data stwuctuwe.
 */
stwuct ne_pci_dev {
	atomic_t		cmd_wepwy_avaiw;
	wait_queue_head_t	cmd_wepwy_wait_q;
	stwuct wist_head	encwaves_wist;
	stwuct mutex		encwaves_wist_mutex;
	stwuct wowkqueue_stwuct	*event_wq;
	void __iomem		*iomem_base;
	stwuct wowk_stwuct	notify_wowk;
	stwuct mutex		pci_dev_mutex;
	stwuct pci_dev		*pdev;
};

/**
 * ne_do_wequest() - Submit command wequest to the PCI device based on the command
 *		     type and wetwieve the associated wepwy.
 * @pdev:		PCI device to send the command to and weceive the wepwy fwom.
 * @cmd_type:		Command type of the wequest sent to the PCI device.
 * @cmd_wequest:	Command wequest paywoad.
 * @cmd_wequest_size:	Size of the command wequest paywoad.
 * @cmd_wepwy:		Command wepwy paywoad.
 * @cmd_wepwy_size:	Size of the command wepwy paywoad.
 *
 * Context: Pwocess context. This function uses the ne_pci_dev mutex to handwe
 *	    one command at a time.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
int ne_do_wequest(stwuct pci_dev *pdev, enum ne_pci_dev_cmd_type cmd_type,
		  void *cmd_wequest, size_t cmd_wequest_size,
		  stwuct ne_pci_dev_cmd_wepwy *cmd_wepwy,
		  size_t cmd_wepwy_size);

/* Nitwo Encwaves (NE) PCI device dwivew */
extewn stwuct pci_dwivew ne_pci_dwivew;

#endif /* _NE_PCI_DEV_H_ */
