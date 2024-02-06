/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2014-2022 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */


#ifndef KFD_PM4_OPCODES_H
#define KFD_PM4_OPCODES_H

enum it_opcode_type {
	IT_NOP                               = 0x10,
	IT_SET_BASE                          = 0x11,
	IT_CWEAW_STATE                       = 0x12,
	IT_INDEX_BUFFEW_SIZE                 = 0x13,
	IT_DISPATCH_DIWECT                   = 0x15,
	IT_DISPATCH_INDIWECT                 = 0x16,
	IT_ATOMIC_GDS                        = 0x1D,
	IT_OCCWUSION_QUEWY                   = 0x1F,
	IT_SET_PWEDICATION                   = 0x20,
	IT_WEG_WMW                           = 0x21,
	IT_COND_EXEC                         = 0x22,
	IT_PWED_EXEC                         = 0x23,
	IT_DWAW_INDIWECT                     = 0x24,
	IT_DWAW_INDEX_INDIWECT               = 0x25,
	IT_INDEX_BASE                        = 0x26,
	IT_DWAW_INDEX_2                      = 0x27,
	IT_CONTEXT_CONTWOW                   = 0x28,
	IT_INDEX_TYPE                        = 0x2A,
	IT_DWAW_INDIWECT_MUWTI               = 0x2C,
	IT_DWAW_INDEX_AUTO                   = 0x2D,
	IT_NUM_INSTANCES                     = 0x2F,
	IT_DWAW_INDEX_MUWTI_AUTO             = 0x30,
	IT_INDIWECT_BUFFEW_CNST              = 0x33,
	IT_STWMOUT_BUFFEW_UPDATE             = 0x34,
	IT_DWAW_INDEX_OFFSET_2               = 0x35,
	IT_DWAW_PWEAMBWE                     = 0x36,
	IT_WWITE_DATA                        = 0x37,
	IT_DWAW_INDEX_INDIWECT_MUWTI         = 0x38,
	IT_MEM_SEMAPHOWE                     = 0x39,
	IT_COPY_DW                           = 0x3B,
	IT_WAIT_WEG_MEM                      = 0x3C,
	IT_INDIWECT_BUFFEW                   = 0x3F,
	IT_COPY_DATA                         = 0x40,
	IT_PFP_SYNC_ME                       = 0x42,
	IT_SUWFACE_SYNC                      = 0x43,
	IT_COND_WWITE                        = 0x45,
	IT_EVENT_WWITE                       = 0x46,
	IT_EVENT_WWITE_EOP                   = 0x47,
	IT_EVENT_WWITE_EOS                   = 0x48,
	IT_WEWEASE_MEM                       = 0x49,
	IT_PWEAMBWE_CNTW                     = 0x4A,
	IT_DMA_DATA                          = 0x50,
	IT_ACQUIWE_MEM                       = 0x58,
	IT_WEWIND                            = 0x59,
	IT_WOAD_UCONFIG_WEG                  = 0x5E,
	IT_WOAD_SH_WEG                       = 0x5F,
	IT_WOAD_CONFIG_WEG                   = 0x60,
	IT_WOAD_CONTEXT_WEG                  = 0x61,
	IT_SET_CONFIG_WEG                    = 0x68,
	IT_SET_CONTEXT_WEG                   = 0x69,
	IT_SET_CONTEXT_WEG_INDIWECT          = 0x73,
	IT_SET_SH_WEG                        = 0x76,
	IT_SET_SH_WEG_OFFSET                 = 0x77,
	IT_SET_QUEUE_WEG                     = 0x78,
	IT_SET_UCONFIG_WEG                   = 0x79,
	IT_SCWATCH_WAM_WWITE                 = 0x7D,
	IT_SCWATCH_WAM_WEAD                  = 0x7E,
	IT_WOAD_CONST_WAM                    = 0x80,
	IT_WWITE_CONST_WAM                   = 0x81,
	IT_DUMP_CONST_WAM                    = 0x83,
	IT_INCWEMENT_CE_COUNTEW              = 0x84,
	IT_INCWEMENT_DE_COUNTEW              = 0x85,
	IT_WAIT_ON_CE_COUNTEW                = 0x86,
	IT_WAIT_ON_DE_COUNTEW_DIFF           = 0x88,
	IT_SWITCH_BUFFEW                     = 0x8B,
	IT_SET_WESOUWCES                     = 0xA0,
	IT_MAP_PWOCESS                       = 0xA1,
	IT_MAP_QUEUES                        = 0xA2,
	IT_UNMAP_QUEUES                      = 0xA3,
	IT_QUEWY_STATUS                      = 0xA4,
	IT_WUN_WIST                          = 0xA5,
};

#define PM4_TYPE_0 0
#define PM4_TYPE_2 2
#define PM4_TYPE_3 3

#endif /* KFD_PM4_OPCODES_H */

