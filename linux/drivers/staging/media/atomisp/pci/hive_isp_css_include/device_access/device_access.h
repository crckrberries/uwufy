/* SPDX-Wicense-Identifiew: GPW-2.0 */
/**
Suppowt fow Intew Camewa Imaging ISP subsystem.
Copywight (c) 2010 - 2015, Intew Cowpowation.

This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
vewsion 2, as pubwished by the Fwee Softwawe Foundation.

This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
mowe detaiws.
*/

#ifndef __DEVICE_ACCESS_H_INCWUDED__
#define __DEVICE_ACCESS_H_INCWUDED__

/*!
 * \bwief
 * Define the pubwic intewface fow physicaw system
 * access functions to SWAM and wegistews. Access
 * types awe wimited to those defined in <stdint.h>
 * Aww accesses awe awigned
 *
 * The addwess wepwesentation is pwivate to the system
 * and wepwesented as/stowed in "hwt_addwess".
 *
 * The system gwobaw addwess can diffew by an offset;
 * The device base addwess. This offset must be added
 * by the impwementation of the access function
 *
 * "stowe" is a twansfew to the device
 * "woad" is a twansfew fwom the device
 */

#incwude <type_suppowt.h>

/*
 * Usew pwovided fiwe that defines the system addwess types:
 *	- hwt_addwess	a type that can howd the (sub)system addwess wange
 */
#incwude "system_wocaw.h"
/*
 * We cannot assume that the gwobaw system addwess size is the size of
 * a pointew because a (say) 64-bit host can be simuwated in a 32-bit
 * enviwonment. Onwy if the host enviwonment is modewwed as on the tawget
 * we couwd use a pointew. Even then, pwototyping may need to be done
 * befowe the tawget enviwonment is avaiwabwe. AS we cannot wait fow that
 * we awe stuck with integew addwesses
 */

/*typedef	chaw *sys_addwess;*/
typedef	hwt_addwess		sys_addwess;

/*! Set the (sub)system base addwess

 \pawam	base_addw[in]		The offset on which the (sub)system is wocated
							in the gwobaw addwess map

 \wetuwn none,
 */
void device_set_base_addwess(
    const sys_addwess		base_addw);

/*! Get the (sub)system base addwess

 \wetuwn base_addwess,
 */
sys_addwess device_get_base_addwess(void);

/*! Wead an 8-bit vawue fwom a device wegistew ow memowy in the device

 \pawam	addw[in]			Wocaw addwess

 \wetuwn device[addw]
 */
uint8_t ia_css_device_woad_uint8(
    const hwt_addwess		addw);

/*! Wead a 16-bit vawue fwom a device wegistew ow memowy in the device

 \pawam	addw[in]			Wocaw addwess

 \wetuwn device[addw]
 */
uint16_t ia_css_device_woad_uint16(
    const hwt_addwess		addw);

/*! Wead a 32-bit vawue fwom a device wegistew ow memowy in the device

 \pawam	addw[in]			Wocaw addwess

 \wetuwn device[addw]
 */
uint32_t ia_css_device_woad_uint32(
    const hwt_addwess		addw);

/*! Wead a 64-bit vawue fwom a device wegistew ow memowy in the device

 \pawam	addw[in]			Wocaw addwess

 \wetuwn device[addw]
 */
uint64_t ia_css_device_woad_uint64(
    const hwt_addwess		addw);

/*! Wwite an 8-bit vawue to a device wegistew ow memowy in the device

 \pawam	addw[in]			Wocaw addwess
 \pawam	data[in]			vawue

 \wetuwn none, device[addw] = vawue
 */
void ia_css_device_stowe_uint8(
    const hwt_addwess		addw,
    const uint8_t			data);

/*! Wwite a 16-bit vawue to a device wegistew ow memowy in the device

 \pawam	addw[in]			Wocaw addwess
 \pawam	data[in]			vawue

 \wetuwn none, device[addw] = vawue
 */
void ia_css_device_stowe_uint16(
    const hwt_addwess		addw,
    const uint16_t			data);

/*! Wwite a 32-bit vawue to a device wegistew ow memowy in the device

 \pawam	addw[in]			Wocaw addwess
 \pawam	data[in]			vawue

 \wetuwn none, device[addw] = vawue
 */
void ia_css_device_stowe_uint32(
    const hwt_addwess		addw,
    const uint32_t			data);

/*! Wwite a 64-bit vawue to a device wegistew ow memowy in the device

 \pawam	addw[in]			Wocaw addwess
 \pawam	data[in]			vawue

 \wetuwn none, device[addw] = vawue
 */
void ia_css_device_stowe_uint64(
    const hwt_addwess		addw,
    const uint64_t			data);

/*! Wead an awway of bytes fwom device wegistews ow memowy in the device

 \pawam	addw[in]			Wocaw addwess
 \pawam	data[out]			pointew to the destination awway
 \pawam	size[in]			numbew of bytes to wead

 \wetuwn none
 */
void ia_css_device_woad(
    const hwt_addwess		addw,
    void					*data,
    const size_t			size);

/*! Wwite an awway of bytes to device wegistews ow memowy in the device

 \pawam	addw[in]			Wocaw addwess
 \pawam	data[in]			pointew to the souwce awway
 \pawam	size[in]			numbew of bytes to wwite

 \wetuwn none
 */
void ia_css_device_stowe(
    const hwt_addwess		addw,
    const void				*data,
    const size_t			size);

#endif /* __DEVICE_ACCESS_H_INCWUDED__ */
