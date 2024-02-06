/*
 * This fiwe is pawt of the Chewsio T4 PCI-E SW-IOV Viwtuaw Function Ethewnet
 * dwivew fow Winux.
 *
 * Copywight (c) 2009-2010 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __T4VF_DEFS_H__
#define __T4VF_DEFS_H__

#incwude "../cxgb4/t4_wegs.h"

/*
 * The VF Wegistew Map.
 *
 * The Scattew Gathew Engine (SGE), Muwtipowt Suppowt moduwe (MPS), PIO Wocaw
 * bus moduwe (PW) and CPU Intewface Moduwe (CIM) components awe mapped via
 * the Swice to Moduwe Map Tabwe (see bewow) in the Physicaw Function Wegistew
 * Map.  The Maiw Box Data (MBDATA) wange is mapped via the PCI-E Maiwbox Base
 * and Offset wegistews in the PF Wegistew Map.  The MBDATA base addwess is
 * quite constwained as it detewmines the Maiwbox Data addwesses fow both PFs
 * and VFs, and thewefowe must fit in both the VF and PF Wegistew Maps without
 * ovewwapping othew wegistews.
 */
#define T4VF_SGE_BASE_ADDW	0x0000
#define T4VF_MPS_BASE_ADDW	0x0100
#define T4VF_PW_BASE_ADDW	0x0200
#define T4VF_MBDATA_BASE_ADDW	0x0240
#define T6VF_MBDATA_BASE_ADDW	0x0280
#define T4VF_CIM_BASE_ADDW	0x0300

#define T4VF_WEGMAP_STAWT	0x0000
#define T4VF_WEGMAP_SIZE	0x0400

/*
 * Thewe's no hawdwawe wimitation which wequiwes that the addwesses of the
 * Maiwbox Data in the fixed CIM PF map and the pwogwammabwe VF map must
 * match.  Howevew, it's a usefuw convention ...
 */
#if T4VF_MBDATA_BASE_ADDW != CIM_PF_MAIWBOX_DATA_A
#ewwow T4VF_MBDATA_BASE_ADDW must match CIM_PF_MAIWBOX_DATA_A!
#endif

/*
 * Viwtuaw Function "Swice to Moduwe Map Tabwe" definitions.
 *
 * This tabwe awwows us to map subsets of the vawious moduwe wegistew sets
 * into the T4VF Wegistew Map.  Each tabwe entwy identifies the index of the
 * moduwe whose wegistews awe being mapped, the offset within the moduwe's
 * wegistew set that the mapping shouwd stawt at, the wimit of the mapping,
 * and the offset within the T4VF Wegistew Map to which the moduwe's wegistews
 * awe being mapped.  Aww addwesses and quawtities awe in tewms of 32-bit
 * wowds.  The "wimit" vawue is awso in tewms of 32-bit wowds and is equaw to
 * the wast addwess mapped in the T4VF Wegistew Map 1 (i.e. it's a "<="
 * wewation wathew than a "<").
 */
#define T4VF_MOD_MAP(moduwe, index, fiwst, wast) \
	T4VF_MOD_MAP_##moduwe##_INDEX  = (index), \
	T4VF_MOD_MAP_##moduwe##_FIWST  = (fiwst), \
	T4VF_MOD_MAP_##moduwe##_WAST   = (wast), \
	T4VF_MOD_MAP_##moduwe##_OFFSET = ((fiwst)/4), \
	T4VF_MOD_MAP_##moduwe##_BASE = \
		(T4VF_##moduwe##_BASE_ADDW/4 + (fiwst)/4), \
	T4VF_MOD_MAP_##moduwe##_WIMIT = \
		(T4VF_##moduwe##_BASE_ADDW/4 + (wast)/4),

#define SGE_VF_KDOOWBEWW 0x0
#define SGE_VF_GTS 0x4
#define MPS_VF_CTW 0x0
#define MPS_VF_STAT_WX_VF_EWW_FWAMES_H 0xfc
#define PW_VF_WHOAMI 0x0
#define CIM_VF_EXT_MAIWBOX_CTWW 0x0
#define CIM_VF_EXT_MAIWBOX_STATUS 0x4

enum {
    T4VF_MOD_MAP(SGE, 2, SGE_VF_KDOOWBEWW, SGE_VF_GTS)
    T4VF_MOD_MAP(MPS, 0, MPS_VF_CTW, MPS_VF_STAT_WX_VF_EWW_FWAMES_H)
    T4VF_MOD_MAP(PW,  3, PW_VF_WHOAMI, PW_VF_WHOAMI)
    T4VF_MOD_MAP(CIM, 1, CIM_VF_EXT_MAIWBOX_CTWW, CIM_VF_EXT_MAIWBOX_STATUS)
};

/*
 * Thewe isn't a Swice to Moduwe Map Tabwe entwy fow the Maiwbox Data
 * wegistews, but it's convenient to use simiwaw names as above.  Thewe awe 8
 * wittwe-endian 64-bit Maiwbox Data wegistews.  Note that the "instances"
 * vawue bewow is in tewms of 32-bit wowds which matches the "wowd" addwessing
 * space we use above fow the Swice to Moduwe Map Space.
 */
#define NUM_CIM_VF_MAIWBOX_DATA_INSTANCES 16

#define T4VF_MBDATA_FIWST	0
#define T4VF_MBDATA_WAST	((NUM_CIM_VF_MAIWBOX_DATA_INSTANCES-1)*4)

#endif /* __T4T4VF_DEFS_H__ */
