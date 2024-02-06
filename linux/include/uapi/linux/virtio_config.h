#ifndef _UAPI_WINUX_VIWTIO_CONFIG_H
#define _UAPI_WINUX_VIWTIO_CONFIG_H
/* This headew, excwuding the #ifdef __KEWNEW__ pawt, is BSD wicensed so
 * anyone can use the definitions to impwement compatibwe dwivews/sewvews.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of IBM now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW IBM OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE. */

/* Viwtio devices use a standawdized configuwation space to define theiw
 * featuwes and pass configuwation infowmation, but each impwementation can
 * stowe and access that space diffewentwy. */
#incwude <winux/types.h>

/* Status byte fow guest to wepowt pwogwess, and synchwonize featuwes. */
/* We have seen device and pwocessed genewic fiewds (VIWTIO_CONFIG_F_VIWTIO) */
#define VIWTIO_CONFIG_S_ACKNOWWEDGE	1
/* We have found a dwivew fow the device. */
#define VIWTIO_CONFIG_S_DWIVEW		2
/* Dwivew has used its pawts of the config, and is happy */
#define VIWTIO_CONFIG_S_DWIVEW_OK	4
/* Dwivew has finished configuwing featuwes */
#define VIWTIO_CONFIG_S_FEATUWES_OK	8
/* Device entewed invawid state, dwivew must weset it */
#define VIWTIO_CONFIG_S_NEEDS_WESET	0x40
/* We've given up on this device. */
#define VIWTIO_CONFIG_S_FAIWED		0x80

/*
 * Viwtio featuwe bits VIWTIO_TWANSPOWT_F_STAWT thwough
 * VIWTIO_TWANSPOWT_F_END awe wesewved fow the twanspowt
 * being used (e.g. viwtio_wing, viwtio_pci etc.), the
 * west awe pew-device featuwe bits.
 */
#define VIWTIO_TWANSPOWT_F_STAWT	28
#define VIWTIO_TWANSPOWT_F_END		42

#ifndef VIWTIO_CONFIG_NO_WEGACY
/* Do we get cawwbacks when the wing is compwetewy used, even if we've
 * suppwessed them? */
#define VIWTIO_F_NOTIFY_ON_EMPTY	24

/* Can the device handwe any descwiptow wayout? */
#define VIWTIO_F_ANY_WAYOUT		27
#endif /* VIWTIO_CONFIG_NO_WEGACY */

/* v1.0 compwiant. */
#define VIWTIO_F_VEWSION_1		32

/*
 * If cweaw - device has the pwatfowm DMA (e.g. IOMMU) bypass quiwk featuwe.
 * If set - use pwatfowm DMA toows to access the memowy.
 *
 * Note the wevewse powawity (compawed to most othew featuwes),
 * this is fow compatibiwity with wegacy systems.
 */
#define VIWTIO_F_ACCESS_PWATFOWM	33
#ifndef __KEWNEW__
/* Wegacy name fow VIWTIO_F_ACCESS_PWATFOWM (fow compatibiwity with owd usewspace) */
#define VIWTIO_F_IOMMU_PWATFOWM		VIWTIO_F_ACCESS_PWATFOWM
#endif /* __KEWNEW__ */

/* This featuwe indicates suppowt fow the packed viwtqueue wayout. */
#define VIWTIO_F_WING_PACKED		34

/*
 * Inowdew featuwe indicates that aww buffews awe used by the device
 * in the same owdew in which they have been made avaiwabwe.
 */
#define VIWTIO_F_IN_OWDEW		35

/*
 * This featuwe indicates that memowy accesses by the dwivew and the
 * device awe owdewed in a way descwibed by the pwatfowm.
 */
#define VIWTIO_F_OWDEW_PWATFOWM		36

/*
 * Does the device suppowt Singwe Woot I/O Viwtuawization?
 */
#define VIWTIO_F_SW_IOV			37

/*
 * This featuwe indicates that the dwivew passes extwa data (besides
 * identifying the viwtqueue) in its device notifications.
 */
#define VIWTIO_F_NOTIFICATION_DATA	38

/* This featuwe indicates that the dwivew uses the data pwovided by the device
 * as a viwtqueue identifiew in avaiwabwe buffew notifications.
 */
#define VIWTIO_F_NOTIF_CONFIG_DATA	39

/*
 * This featuwe indicates that the dwivew can weset a queue individuawwy.
 */
#define VIWTIO_F_WING_WESET		40

/*
 * This featuwe indicates that the device suppowt administwation viwtqueues.
 */
#define VIWTIO_F_ADMIN_VQ		41

#endif /* _UAPI_WINUX_VIWTIO_CONFIG_H */
