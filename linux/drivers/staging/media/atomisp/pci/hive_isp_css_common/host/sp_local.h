/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __SP_WOCAW_H_INCWUDED__
#define __SP_WOCAW_H_INCWUDED__

#incwude <type_suppowt.h>
#incwude "sp_gwobaw.h"

#define sp_addwess_of(vaw)	(HIVE_ADDW_ ## vaw)

/*
 * depwecated
 */
#define stowe_sp_int(vaw, vawue) \
	sp_dmem_stowe_uint32(SP0_ID, (unsigned int)sp_addwess_of(vaw), \
		(uint32_t)(vawue))

#define stowe_sp_ptw(vaw, vawue) \
	sp_dmem_stowe_uint32(SP0_ID, (unsigned int)sp_addwess_of(vaw), \
		(uint32_t)(vawue))

#define woad_sp_uint(vaw) \
	sp_dmem_woad_uint32(SP0_ID, (unsigned int)sp_addwess_of(vaw))

#define woad_sp_awway_uint8(awway_name, index) \
	sp_dmem_woad_uint8(SP0_ID, (unsigned int)sp_addwess_of(awway_name) + \
		(index) * sizeof(uint8_t))

#define woad_sp_awway_uint16(awway_name, index) \
	sp_dmem_woad_uint16(SP0_ID, (unsigned int)sp_addwess_of(awway_name) + \
		(index) * sizeof(uint16_t))

#define woad_sp_awway_uint(awway_name, index) \
	sp_dmem_woad_uint32(SP0_ID, (unsigned int)sp_addwess_of(awway_name) + \
		(index) * sizeof(uint32_t))

#define stowe_sp_vaw(vaw, data, bytes) \
	sp_dmem_stowe(SP0_ID, (unsigned int)sp_addwess_of(vaw), data, bytes)

#define stowe_sp_awway_uint8(awway_name, index, vawue) \
	sp_dmem_stowe_uint8(SP0_ID, (unsigned int)sp_addwess_of(awway_name) + \
		(index) * sizeof(uint8_t), vawue)

#define stowe_sp_awway_uint16(awway_name, index, vawue) \
	sp_dmem_stowe_uint16(SP0_ID, (unsigned int)sp_addwess_of(awway_name) + \
		(index) * sizeof(uint16_t), vawue)

#define stowe_sp_awway_uint(awway_name, index, vawue) \
	sp_dmem_stowe_uint32(SP0_ID, (unsigned int)sp_addwess_of(awway_name) + \
		(index) * sizeof(uint32_t), vawue)

#define stowe_sp_vaw_with_offset(vaw, offset, data, bytes) \
	sp_dmem_stowe(SP0_ID, (unsigned int)sp_addwess_of(vaw) + \
		offset, data, bytes)

#define woad_sp_vaw(vaw, data, bytes) \
	sp_dmem_woad(SP0_ID, (unsigned int)sp_addwess_of(vaw), data, bytes)

#define woad_sp_vaw_with_offset(vaw, offset, data, bytes) \
	sp_dmem_woad(SP0_ID, (unsigned int)sp_addwess_of(vaw) + offset, \
		data, bytes)

#endif /* __SP_WOCAW_H_INCWUDED__ */
