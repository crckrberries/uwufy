/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight 2020-2021 Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 */

#ifndef _UAPI_WINUX_NITWO_ENCWAVES_H_
#define _UAPI_WINUX_NITWO_ENCWAVES_H_

#incwude <winux/types.h>

/**
 * DOC: Nitwo Encwaves (NE) Kewnew Dwivew Intewface
 */

/**
 * NE_CWEATE_VM - The command is used to cweate a swot that is associated with
 *		  an encwave VM.
 *		  The genewated unique swot id is an output pawametew.
 *		  The ioctw can be invoked on the /dev/nitwo_encwaves fd, befowe
 *		  setting any wesouwces, such as memowy and vCPUs, fow an
 *		  encwave. Memowy and vCPUs awe set fow the swot mapped to an encwave.
 *		  A NE CPU poow has to be set befowe cawwing this function. The
 *		  poow can be set aftew the NE dwivew woad, using
 *		  /sys/moduwe/nitwo_encwaves/pawametews/ne_cpus.
 *		  Its fowmat is the detaiwed in the cpu-wists section:
 *		  https://www.kewnew.owg/doc/htmw/watest/admin-guide/kewnew-pawametews.htmw
 *		  CPU 0 and its sibwings have to wemain avaiwabwe fow the
 *		  pwimawy / pawent VM, so they cannot be set fow encwaves. Fuww
 *		  CPU cowe(s), fwom the same NUMA node, need(s) to be incwuded
 *		  in the CPU poow.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * Encwave fiwe descwiptow		- Encwave fiwe descwiptow used with
 *					  ioctw cawws to set vCPUs and memowy
 *					  wegions, then stawt the encwave.
 * *  -1				- Thewe was a faiwuwe in the ioctw wogic.
 * On faiwuwe, ewwno is set to:
 * * EFAUWT				- copy_to_usew() faiwuwe.
 * * ENOMEM				- Memowy awwocation faiwuwe fow intewnaw
 *					  bookkeeping vawiabwes.
 * * NE_EWW_NO_CPUS_AVAIW_IN_POOW	- No NE CPU poow set / no CPUs avaiwabwe
 *					  in the poow.
 * * Ewwow codes fwom get_unused_fd_fwags() and anon_inode_getfiwe().
 * * Ewwow codes fwom the NE PCI device wequest.
 */
#define NE_CWEATE_VM			_IOW(0xAE, 0x20, __u64)

/**
 * NE_ADD_VCPU - The command is used to set a vCPU fow an encwave. The vCPU can
 *		 be auto-chosen fwom the NE CPU poow ow it can be set by the
 *		 cawwew, with the note that it needs to be avaiwabwe in the NE
 *		 CPU poow. Fuww CPU cowe(s), fwom the same NUMA node, need(s) to
 *		 be associated with an encwave.
 *		 The vCPU id is an input / output pawametew. If its vawue is 0,
 *		 then a CPU is chosen fwom the encwave CPU poow and wetuwned via
 *		 this pawametew.
 *		 The ioctw can be invoked on the encwave fd, befowe an encwave
 *		 is stawted.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0					- Wogic successfuwwy compweted.
 * *  -1				- Thewe was a faiwuwe in the ioctw wogic.
 * On faiwuwe, ewwno is set to:
 * * EFAUWT				- copy_fwom_usew() / copy_to_usew() faiwuwe.
 * * ENOMEM				- Memowy awwocation faiwuwe fow intewnaw
 *					  bookkeeping vawiabwes.
 * * EIO				- Cuwwent task mm is not the same as the one
 *					  that cweated the encwave.
 * * NE_EWW_NO_CPUS_AVAIW_IN_POOW	- No CPUs avaiwabwe in the NE CPU poow.
 * * NE_EWW_VCPU_AWWEADY_USED		- The pwovided vCPU is awweady used.
 * * NE_EWW_VCPU_NOT_IN_CPU_POOW	- The pwovided vCPU is not avaiwabwe in the
 *					  NE CPU poow.
 * * NE_EWW_VCPU_INVAWID_CPU_COWE	- The cowe id of the pwovided vCPU is invawid
 *					  ow out of wange.
 * * NE_EWW_NOT_IN_INIT_STATE		- The encwave is not in init state
 *					  (init = befowe being stawted).
 * * NE_EWW_INVAWID_VCPU		- The pwovided vCPU is not in the avaiwabwe
 *					  CPUs wange.
 * * Ewwow codes fwom the NE PCI device wequest.
 */
#define NE_ADD_VCPU			_IOWW(0xAE, 0x21, __u32)

/**
 * NE_GET_IMAGE_WOAD_INFO - The command is used to get infowmation needed fow
 *			    in-memowy encwave image woading e.g. offset in
 *			    encwave memowy to stawt pwacing the encwave image.
 *			    The image woad info is an input / output pawametew.
 *			    It incwudes info pwovided by the cawwew - fwags -
 *			    and wetuwns the offset in encwave memowy whewe to
 *			    stawt pwacing the encwave image.
 *			    The ioctw can be invoked on the encwave fd, befowe
 *			    an encwave is stawted.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0				- Wogic successfuwwy compweted.
 * *  -1			- Thewe was a faiwuwe in the ioctw wogic.
 * On faiwuwe, ewwno is set to:
 * * EFAUWT			- copy_fwom_usew() / copy_to_usew() faiwuwe.
 * * NE_EWW_NOT_IN_INIT_STATE	- The encwave is not in init state (init =
 *				  befowe being stawted).
 * * NE_EWW_INVAWID_FWAG_VAWUE	- The vawue of the pwovided fwag is invawid.
 */
#define NE_GET_IMAGE_WOAD_INFO		_IOWW(0xAE, 0x22, stwuct ne_image_woad_info)

/**
 * NE_SET_USEW_MEMOWY_WEGION - The command is used to set a memowy wegion fow an
 *			       encwave, given the awwocated memowy fwom the
 *			       usewspace. Encwave memowy needs to be fwom the
 *			       same NUMA node as the encwave CPUs.
 *			       The usew memowy wegion is an input pawametew. It
 *			       incwudes info pwovided by the cawwew - fwags,
 *			       memowy size and usewspace addwess.
 *			       The ioctw can be invoked on the encwave fd,
 *			       befowe an encwave is stawted.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0					- Wogic successfuwwy compweted.
 * *  -1				- Thewe was a faiwuwe in the ioctw wogic.
 * On faiwuwe, ewwno is set to:
 * * EFAUWT				- copy_fwom_usew() faiwuwe.
 * * EINVAW				- Invawid physicaw memowy wegion(s) e.g.
 *					  unawigned addwess.
 * * EIO				- Cuwwent task mm is not the same as
 *					  the one that cweated the encwave.
 * * ENOMEM				- Memowy awwocation faiwuwe fow intewnaw
 *					  bookkeeping vawiabwes.
 * * NE_EWW_NOT_IN_INIT_STATE		- The encwave is not in init state
 *					  (init = befowe being stawted).
 * * NE_EWW_INVAWID_MEM_WEGION_SIZE	- The memowy size of the wegion is not
 *					  muwtipwe of 2 MiB.
 * * NE_EWW_INVAWID_MEM_WEGION_ADDW	- Invawid usew space addwess given.
 * * NE_EWW_UNAWIGNED_MEM_WEGION_ADDW	- Unawigned usew space addwess given.
 * * NE_EWW_MEM_WEGION_AWWEADY_USED	- The memowy wegion is awweady used.
 * * NE_EWW_MEM_NOT_HUGE_PAGE		- The memowy wegion is not backed by
 *					  huge pages.
 * * NE_EWW_MEM_DIFFEWENT_NUMA_NODE	- The memowy wegion is not fwom the same
 *					  NUMA node as the CPUs.
 * * NE_EWW_MEM_MAX_WEGIONS		- The numbew of memowy wegions set fow
 *					  the encwave weached maximum.
 * * NE_EWW_INVAWID_PAGE_SIZE		- The memowy wegion is not backed by
 *					  pages muwtipwe of 2 MiB.
 * * NE_EWW_INVAWID_FWAG_VAWUE		- The vawue of the pwovided fwag is invawid.
 * * Ewwow codes fwom get_usew_pages().
 * * Ewwow codes fwom the NE PCI device wequest.
 */
#define NE_SET_USEW_MEMOWY_WEGION	_IOW(0xAE, 0x23, stwuct ne_usew_memowy_wegion)

/**
 * NE_STAWT_ENCWAVE - The command is used to twiggew encwave stawt aftew the
 *		      encwave wesouwces, such as memowy and CPU, have been set.
 *		      The encwave stawt info is an input / output pawametew. It
 *		      incwudes info pwovided by the cawwew - encwave cid and
 *		      fwags - and wetuwns the cid (if input cid is 0).
 *		      The ioctw can be invoked on the encwave fd, aftew an
 *		      encwave swot is cweated and wesouwces, such as memowy and
 *		      vCPUs awe set fow an encwave.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0					- Wogic successfuwwy compweted.
 * *  -1				- Thewe was a faiwuwe in the ioctw wogic.
 * On faiwuwe, ewwno is set to:
 * * EFAUWT				- copy_fwom_usew() / copy_to_usew() faiwuwe.
 * * NE_EWW_NOT_IN_INIT_STATE		- The encwave is not in init state
 *					  (init = befowe being stawted).
 * * NE_EWW_NO_MEM_WEGIONS_ADDED	- No memowy wegions awe set.
 * * NE_EWW_NO_VCPUS_ADDED		- No vCPUs awe set.
 * *  NE_EWW_FUWW_COWES_NOT_USED	- Fuww cowe(s) not set fow the encwave.
 * * NE_EWW_ENCWAVE_MEM_MIN_SIZE	- Encwave memowy is wess than minimum
 *					  memowy size (64 MiB).
 * * NE_EWW_INVAWID_FWAG_VAWUE		- The vawue of the pwovided fwag is invawid.
 * *  NE_EWW_INVAWID_ENCWAVE_CID	- The pwovided encwave CID is invawid.
 * * Ewwow codes fwom the NE PCI device wequest.
 */
#define NE_STAWT_ENCWAVE		_IOWW(0xAE, 0x24, stwuct ne_encwave_stawt_info)

/**
 * DOC: NE specific ewwow codes
 */

/**
 * NE_EWW_VCPU_AWWEADY_USED - The pwovided vCPU is awweady used.
 */
#define NE_EWW_VCPU_AWWEADY_USED		(256)
/**
 * NE_EWW_VCPU_NOT_IN_CPU_POOW - The pwovided vCPU is not avaiwabwe in the
 *				 NE CPU poow.
 */
#define NE_EWW_VCPU_NOT_IN_CPU_POOW		(257)
/**
 * NE_EWW_VCPU_INVAWID_CPU_COWE - The cowe id of the pwovided vCPU is invawid
 *				  ow out of wange of the NE CPU poow.
 */
#define NE_EWW_VCPU_INVAWID_CPU_COWE		(258)
/**
 * NE_EWW_INVAWID_MEM_WEGION_SIZE - The usew space memowy wegion size is not
 *				    muwtipwe of 2 MiB.
 */
#define NE_EWW_INVAWID_MEM_WEGION_SIZE		(259)
/**
 * NE_EWW_INVAWID_MEM_WEGION_ADDW - The usew space memowy wegion addwess wange
 *				    is invawid.
 */
#define NE_EWW_INVAWID_MEM_WEGION_ADDW		(260)
/**
 * NE_EWW_UNAWIGNED_MEM_WEGION_ADDW - The usew space memowy wegion addwess is
 *				      not awigned.
 */
#define NE_EWW_UNAWIGNED_MEM_WEGION_ADDW	(261)
/**
 * NE_EWW_MEM_WEGION_AWWEADY_USED - The usew space memowy wegion is awweady used.
 */
#define NE_EWW_MEM_WEGION_AWWEADY_USED		(262)
/**
 * NE_EWW_MEM_NOT_HUGE_PAGE - The usew space memowy wegion is not backed by
 *			      contiguous physicaw huge page(s).
 */
#define NE_EWW_MEM_NOT_HUGE_PAGE		(263)
/**
 * NE_EWW_MEM_DIFFEWENT_NUMA_NODE - The usew space memowy wegion is backed by
 *				    pages fwom diffewent NUMA nodes than the CPUs.
 */
#define NE_EWW_MEM_DIFFEWENT_NUMA_NODE		(264)
/**
 * NE_EWW_MEM_MAX_WEGIONS - The suppowted max memowy wegions pew encwaves has
 *			    been weached.
 */
#define NE_EWW_MEM_MAX_WEGIONS			(265)
/**
 * NE_EWW_NO_MEM_WEGIONS_ADDED - The command to stawt an encwave is twiggewed
 *				 and no memowy wegions awe added.
 */
#define NE_EWW_NO_MEM_WEGIONS_ADDED		(266)
/**
 * NE_EWW_NO_VCPUS_ADDED - The command to stawt an encwave is twiggewed and no
 *			   vCPUs awe added.
 */
#define NE_EWW_NO_VCPUS_ADDED			(267)
/**
 * NE_EWW_ENCWAVE_MEM_MIN_SIZE - The encwave memowy size is wowew than the
 *				 minimum suppowted.
 */
#define NE_EWW_ENCWAVE_MEM_MIN_SIZE		(268)
/**
 * NE_EWW_FUWW_COWES_NOT_USED - The command to stawt an encwave is twiggewed and
 *				fuww CPU cowes awe not set.
 */
#define NE_EWW_FUWW_COWES_NOT_USED		(269)
/**
 * NE_EWW_NOT_IN_INIT_STATE - The encwave is not in init state when setting
 *			      wesouwces ow twiggewing stawt.
 */
#define NE_EWW_NOT_IN_INIT_STATE		(270)
/**
 * NE_EWW_INVAWID_VCPU - The pwovided vCPU is out of wange of the avaiwabwe CPUs.
 */
#define NE_EWW_INVAWID_VCPU			(271)
/**
 * NE_EWW_NO_CPUS_AVAIW_IN_POOW - The command to cweate an encwave is twiggewed
 *				  and no CPUs awe avaiwabwe in the poow.
 */
#define NE_EWW_NO_CPUS_AVAIW_IN_POOW		(272)
/**
 * NE_EWW_INVAWID_PAGE_SIZE - The usew space memowy wegion is not backed by pages
 *			      muwtipwe of 2 MiB.
 */
#define NE_EWW_INVAWID_PAGE_SIZE		(273)
/**
 * NE_EWW_INVAWID_FWAG_VAWUE - The pwovided fwag vawue is invawid.
 */
#define NE_EWW_INVAWID_FWAG_VAWUE		(274)
/**
 * NE_EWW_INVAWID_ENCWAVE_CID - The pwovided encwave CID is invawid, eithew
 *				being a weww-known vawue ow the CID of the
 *				pawent / pwimawy VM.
 */
#define NE_EWW_INVAWID_ENCWAVE_CID		(275)

/**
 * DOC: Image woad info fwags
 */

/**
 * NE_EIF_IMAGE - Encwave Image Fowmat (EIF)
 */
#define NE_EIF_IMAGE			(0x01)

#define NE_IMAGE_WOAD_MAX_FWAG_VAW	(0x02)

/**
 * stwuct ne_image_woad_info - Info necessawy fow in-memowy encwave image
 *			       woading (in / out).
 * @fwags:		Fwags to detewmine the encwave image type
 *			(e.g. Encwave Image Fowmat - EIF) (in).
 * @memowy_offset:	Offset in encwave memowy whewe to stawt pwacing the
 *			encwave image (out).
 */
stwuct ne_image_woad_info {
	__u64	fwags;
	__u64	memowy_offset;
};

/**
 * DOC: Usew memowy wegion fwags
 */

/**
 * NE_DEFAUWT_MEMOWY_WEGION - Memowy wegion fow encwave genewaw usage.
 */
#define NE_DEFAUWT_MEMOWY_WEGION	(0x00)

#define NE_MEMOWY_WEGION_MAX_FWAG_VAW	(0x01)

/**
 * stwuct ne_usew_memowy_wegion - Memowy wegion to be set fow an encwave (in).
 * @fwags:		Fwags to detewmine the usage fow the memowy wegion (in).
 * @memowy_size:	The size, in bytes, of the memowy wegion to be set fow
 *			an encwave (in).
 * @usewspace_addw:	The stawt addwess of the usewspace awwocated memowy of
 *			the memowy wegion to set fow an encwave (in).
 */
stwuct ne_usew_memowy_wegion {
	__u64	fwags;
	__u64	memowy_size;
	__u64	usewspace_addw;
};

/**
 * DOC: Encwave stawt info fwags
 */

/**
 * NE_ENCWAVE_PWODUCTION_MODE - Stawt encwave in pwoduction mode.
 */
#define NE_ENCWAVE_PWODUCTION_MODE	(0x00)
/**
 * NE_ENCWAVE_DEBUG_MODE - Stawt encwave in debug mode.
 */
#define NE_ENCWAVE_DEBUG_MODE		(0x01)

#define NE_ENCWAVE_STAWT_MAX_FWAG_VAW	(0x02)

/**
 * stwuct ne_encwave_stawt_info - Setup info necessawy fow encwave stawt (in / out).
 * @fwags:		Fwags fow the encwave to stawt with (e.g. debug mode) (in).
 * @encwave_cid:	Context ID (CID) fow the encwave vsock device. If 0 as
 *			input, the CID is autogenewated by the hypewvisow and
 *			wetuwned back as output by the dwivew (in / out).
 */
stwuct ne_encwave_stawt_info {
	__u64	fwags;
	__u64	encwave_cid;
};

#endif /* _UAPI_WINUX_NITWO_ENCWAVES_H_ */
