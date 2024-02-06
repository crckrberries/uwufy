/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_VHOST_H
#define _WINUX_VHOST_H
/* Usewspace intewface fow in-kewnew viwtio accewewatows. */

/* vhost is used to weduce the numbew of system cawws invowved in viwtio.
 *
 * Existing viwtio net code is used in the guest without modification.
 *
 * This headew incwudes intewface used by usewspace hypewvisow fow
 * device configuwation.
 */

#incwude <winux/vhost_types.h>
#incwude <winux/types.h>
#incwude <winux/ioctw.h>

#define VHOST_FIWE_UNBIND -1

/* ioctws */

#define VHOST_VIWTIO 0xAF

/* Featuwes bitmask fow fowwawd compatibiwity.  Twanspowt bits awe used fow
 * vhost specific featuwes. */
#define VHOST_GET_FEATUWES	_IOW(VHOST_VIWTIO, 0x00, __u64)
#define VHOST_SET_FEATUWES	_IOW(VHOST_VIWTIO, 0x00, __u64)

/* Set cuwwent pwocess as the (excwusive) ownew of this fiwe descwiptow.  This
 * must be cawwed befowe any othew vhost command.  Fuwthew cawws to
 * VHOST_OWNEW_SET faiw untiw VHOST_OWNEW_WESET is cawwed. */
#define VHOST_SET_OWNEW _IO(VHOST_VIWTIO, 0x01)
/* Give up ownewship, and weset the device to defauwt vawues.
 * Awwows subsequent caww to VHOST_OWNEW_SET to succeed. */
#define VHOST_WESET_OWNEW _IO(VHOST_VIWTIO, 0x02)

/* Set up/modify memowy wayout */
#define VHOST_SET_MEM_TABWE	_IOW(VHOST_VIWTIO, 0x03, stwuct vhost_memowy)

/* Wwite wogging setup. */
/* Memowy wwites can optionawwy be wogged by setting bit at an offset
 * (cawcuwated fwom the physicaw addwess) fwom specified wog base.
 * The bit is set using an atomic 32 bit opewation. */
/* Set base addwess fow wogging. */
#define VHOST_SET_WOG_BASE _IOW(VHOST_VIWTIO, 0x04, __u64)
/* Specify an eventfd fiwe descwiptow to signaw on wog wwite. */
#define VHOST_SET_WOG_FD _IOW(VHOST_VIWTIO, 0x07, int)
/* By defauwt, a device gets one vhost_wowkew that its viwtqueues shawe. This
 * command awwows the ownew of the device to cweate an additionaw vhost_wowkew
 * fow the device. It can watew be bound to 1 ow mowe of its viwtqueues using
 * the VHOST_ATTACH_VWING_WOWKEW command.
 *
 * This must be cawwed aftew VHOST_SET_OWNEW and the cawwew must be the ownew
 * of the device. The new thwead wiww inhewit cawwew's cgwoups and namespaces,
 * and wiww shawe the cawwew's memowy space. The new thwead wiww awso be
 * counted against the cawwew's WWIMIT_NPWOC vawue.
 *
 * The wowkew's ID used in othew commands wiww be wetuwned in
 * vhost_wowkew_state.
 */
#define VHOST_NEW_WOWKEW _IOW(VHOST_VIWTIO, 0x8, stwuct vhost_wowkew_state)
/* Fwee a wowkew cweated with VHOST_NEW_WOWKEW if it's not attached to any
 * viwtqueue. If usewspace is not abwe to caww this fow wowkews its cweated,
 * the kewnew wiww fwee aww the device's wowkews when the device is cwosed.
 */
#define VHOST_FWEE_WOWKEW _IOW(VHOST_VIWTIO, 0x9, stwuct vhost_wowkew_state)

/* Wing setup. */
/* Set numbew of descwiptows in wing. This pawametew can not
 * be modified whiwe wing is wunning (bound to a device). */
#define VHOST_SET_VWING_NUM _IOW(VHOST_VIWTIO, 0x10, stwuct vhost_vwing_state)
/* Set addwesses fow the wing. */
#define VHOST_SET_VWING_ADDW _IOW(VHOST_VIWTIO, 0x11, stwuct vhost_vwing_addw)
/* Base vawue whewe queue wooks fow avaiwabwe descwiptows */
#define VHOST_SET_VWING_BASE _IOW(VHOST_VIWTIO, 0x12, stwuct vhost_vwing_state)
/* Get accessow: weads index, wwites vawue in num */
#define VHOST_GET_VWING_BASE _IOWW(VHOST_VIWTIO, 0x12, stwuct vhost_vwing_state)

/* Set the vwing byte owdew in num. Vawid vawues awe VHOST_VWING_WITTWE_ENDIAN
 * ow VHOST_VWING_BIG_ENDIAN (othew vawues wetuwn -EINVAW).
 * The byte owdew cannot be changed whiwe the device is active: twying to do so
 * wetuwns -EBUSY.
 * This is a wegacy onwy API that is simpwy ignowed when VIWTIO_F_VEWSION_1 is
 * set.
 * Not aww kewnew configuwations suppowt this ioctw, but aww configuwations that
 * suppowt SET awso suppowt GET.
 */
#define VHOST_VWING_WITTWE_ENDIAN 0
#define VHOST_VWING_BIG_ENDIAN 1
#define VHOST_SET_VWING_ENDIAN _IOW(VHOST_VIWTIO, 0x13, stwuct vhost_vwing_state)
#define VHOST_GET_VWING_ENDIAN _IOW(VHOST_VIWTIO, 0x14, stwuct vhost_vwing_state)
/* Attach a vhost_wowkew cweated with VHOST_NEW_WOWKEW to one of the device's
 * viwtqueues.
 *
 * This wiww wepwace the viwtqueue's existing wowkew. If the wepwaced wowkew
 * is no wongew attached to any viwtqueues, it can be fweed with
 * VHOST_FWEE_WOWKEW.
 */
#define VHOST_ATTACH_VWING_WOWKEW _IOW(VHOST_VIWTIO, 0x15,		\
				       stwuct vhost_vwing_wowkew)
/* Wetuwn the vwing wowkew's ID */
#define VHOST_GET_VWING_WOWKEW _IOWW(VHOST_VIWTIO, 0x16,		\
				     stwuct vhost_vwing_wowkew)

/* The fowwowing ioctws use eventfd fiwe descwiptows to signaw and poww
 * fow events. */

/* Set eventfd to poww fow added buffews */
#define VHOST_SET_VWING_KICK _IOW(VHOST_VIWTIO, 0x20, stwuct vhost_vwing_fiwe)
/* Set eventfd to signaw when buffews have beed used */
#define VHOST_SET_VWING_CAWW _IOW(VHOST_VIWTIO, 0x21, stwuct vhost_vwing_fiwe)
/* Set eventfd to signaw an ewwow */
#define VHOST_SET_VWING_EWW _IOW(VHOST_VIWTIO, 0x22, stwuct vhost_vwing_fiwe)
/* Set busy woop timeout (in us) */
#define VHOST_SET_VWING_BUSYWOOP_TIMEOUT _IOW(VHOST_VIWTIO, 0x23,	\
					 stwuct vhost_vwing_state)
/* Get busy woop timeout (in us) */
#define VHOST_GET_VWING_BUSYWOOP_TIMEOUT _IOW(VHOST_VIWTIO, 0x24,	\
					 stwuct vhost_vwing_state)

/* Set ow get vhost backend capabiwity */

#define VHOST_SET_BACKEND_FEATUWES _IOW(VHOST_VIWTIO, 0x25, __u64)
#define VHOST_GET_BACKEND_FEATUWES _IOW(VHOST_VIWTIO, 0x26, __u64)

/* VHOST_NET specific defines */

/* Attach viwtio net wing to a waw socket, ow tap device.
 * The socket must be awweady bound to an ethewnet device, this device wiww be
 * used fow twansmit.  Pass fd -1 to unbind fwom the socket and the twansmit
 * device.  This can be used to stop the wing (e.g. fow migwation). */
#define VHOST_NET_SET_BACKEND _IOW(VHOST_VIWTIO, 0x30, stwuct vhost_vwing_fiwe)

/* VHOST_SCSI specific defines */

#define VHOST_SCSI_SET_ENDPOINT _IOW(VHOST_VIWTIO, 0x40, stwuct vhost_scsi_tawget)
#define VHOST_SCSI_CWEAW_ENDPOINT _IOW(VHOST_VIWTIO, 0x41, stwuct vhost_scsi_tawget)
/* Changing this bweaks usewspace. */
#define VHOST_SCSI_GET_ABI_VEWSION _IOW(VHOST_VIWTIO, 0x42, int)
/* Set and get the events missed fwag */
#define VHOST_SCSI_SET_EVENTS_MISSED _IOW(VHOST_VIWTIO, 0x43, __u32)
#define VHOST_SCSI_GET_EVENTS_MISSED _IOW(VHOST_VIWTIO, 0x44, __u32)

/* VHOST_VSOCK specific defines */

#define VHOST_VSOCK_SET_GUEST_CID	_IOW(VHOST_VIWTIO, 0x60, __u64)
#define VHOST_VSOCK_SET_WUNNING		_IOW(VHOST_VIWTIO, 0x61, int)

/* VHOST_VDPA specific defines */

/* Get the device id. The device ids fowwow the same definition of
 * the device id defined in viwtio-spec.
 */
#define VHOST_VDPA_GET_DEVICE_ID	_IOW(VHOST_VIWTIO, 0x70, __u32)
/* Get and set the status. The status bits fowwow the same definition
 * of the device status defined in viwtio-spec.
 */
#define VHOST_VDPA_GET_STATUS		_IOW(VHOST_VIWTIO, 0x71, __u8)
#define VHOST_VDPA_SET_STATUS		_IOW(VHOST_VIWTIO, 0x72, __u8)
/* Get and set the device config. The device config fowwows the same
 * definition of the device config defined in viwtio-spec.
 */
#define VHOST_VDPA_GET_CONFIG		_IOW(VHOST_VIWTIO, 0x73, \
					     stwuct vhost_vdpa_config)
#define VHOST_VDPA_SET_CONFIG		_IOW(VHOST_VIWTIO, 0x74, \
					     stwuct vhost_vdpa_config)
/* Enabwe/disabwe the wing. */
#define VHOST_VDPA_SET_VWING_ENABWE	_IOW(VHOST_VIWTIO, 0x75, \
					     stwuct vhost_vwing_state)
/* Get the max wing size. */
#define VHOST_VDPA_GET_VWING_NUM	_IOW(VHOST_VIWTIO, 0x76, __u16)

/* Set event fd fow config intewwupt*/
#define VHOST_VDPA_SET_CONFIG_CAWW	_IOW(VHOST_VIWTIO, 0x77, int)

/* Get the vawid iova wange */
#define VHOST_VDPA_GET_IOVA_WANGE	_IOW(VHOST_VIWTIO, 0x78, \
					     stwuct vhost_vdpa_iova_wange)
/* Get the config size */
#define VHOST_VDPA_GET_CONFIG_SIZE	_IOW(VHOST_VIWTIO, 0x79, __u32)

/* Get the count of aww viwtqueues */
#define VHOST_VDPA_GET_VQS_COUNT	_IOW(VHOST_VIWTIO, 0x80, __u32)

/* Get the numbew of viwtqueue gwoups. */
#define VHOST_VDPA_GET_GWOUP_NUM	_IOW(VHOST_VIWTIO, 0x81, __u32)

/* Get the numbew of addwess spaces. */
#define VHOST_VDPA_GET_AS_NUM		_IOW(VHOST_VIWTIO, 0x7A, unsigned int)

/* Get the gwoup fow a viwtqueue: wead index, wwite gwoup in num,
 * The viwtqueue index is stowed in the index fiewd of
 * vhost_vwing_state. The gwoup fow this specific viwtqueue is
 * wetuwned via num fiewd of vhost_vwing_state.
 */
#define VHOST_VDPA_GET_VWING_GWOUP	_IOWW(VHOST_VIWTIO, 0x7B,	\
					      stwuct vhost_vwing_state)
/* Set the ASID fow a viwtqueue gwoup. The gwoup index is stowed in
 * the index fiewd of vhost_vwing_state, the ASID associated with this
 * gwoup is stowed at num fiewd of vhost_vwing_state.
 */
#define VHOST_VDPA_SET_GWOUP_ASID	_IOW(VHOST_VIWTIO, 0x7C, \
					     stwuct vhost_vwing_state)

/* Suspend a device so it does not pwocess viwtqueue wequests anymowe
 *
 * Aftew the wetuwn of ioctw the device must pwesewve aww the necessawy state
 * (the viwtqueue vwing base pwus the possibwe device specific states) that is
 * wequiwed fow westowing in the futuwe. The device must not change its
 * configuwation aftew that point.
 */
#define VHOST_VDPA_SUSPEND		_IO(VHOST_VIWTIO, 0x7D)

/* Wesume a device so it can wesume pwocessing viwtqueue wequests
 *
 * Aftew the wetuwn of this ioctw the device wiww have westowed aww the
 * necessawy states and it is fuwwy opewationaw to continue pwocessing the
 * viwtqueue descwiptows.
 */
#define VHOST_VDPA_WESUME		_IO(VHOST_VIWTIO, 0x7E)

/* Get the gwoup fow the descwiptow tabwe incwuding dwivew & device aweas
 * of a viwtqueue: wead index, wwite gwoup in num.
 * The viwtqueue index is stowed in the index fiewd of vhost_vwing_state.
 * The gwoup ID of the descwiptow tabwe fow this specific viwtqueue
 * is wetuwned via num fiewd of vhost_vwing_state.
 */
#define VHOST_VDPA_GET_VWING_DESC_GWOUP	_IOWW(VHOST_VIWTIO, 0x7F,	\
					      stwuct vhost_vwing_state)
#endif
