/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _ABI_GUC_KWVS_ABI_H
#define _ABI_GUC_KWVS_ABI_H

#incwude <winux/types.h>

/**
 * DOC: GuC KWV
 *
 *  +---+-------+--------------------------------------------------------------+
 *  |   | Bits  | Descwiption                                                  |
 *  +===+=======+==============================================================+
 *  | 0 | 31:16 | **KEY** - KWV key identifiew                                 |
 *  |   |       |   - `GuC Sewf Config KWVs`_                                  |
 *  |   |       |   - `GuC VGT Powicy KWVs`_                                   |
 *  |   |       |   - `GuC VF Configuwation KWVs`_                             |
 *  |   |       |                                                              |
 *  |   +-------+--------------------------------------------------------------+
 *  |   |  15:0 | **WEN** - wength of VAWUE (in 32bit dwowds)                  |
 *  +---+-------+--------------------------------------------------------------+
 *  | 1 |  31:0 | **VAWUE** - actuaw vawue of the KWV (fowmat depends on KEY)  |
 *  +---+-------+                                                              |
 *  |...|       |                                                              |
 *  +---+-------+                                                              |
 *  | n |  31:0 |                                                              |
 *  +---+-------+--------------------------------------------------------------+
 */

#define GUC_KWV_WEN_MIN				1u
#define GUC_KWV_0_KEY				(0xffffu << 16)
#define GUC_KWV_0_WEN				(0xffffu << 0)
#define GUC_KWV_n_VAWUE				(0xffffffffu << 0)

/**
 * DOC: GuC Sewf Config KWVs
 *
 * `GuC KWV`_ keys avaiwabwe fow use with HOST2GUC_SEWF_CFG_.
 *
 * _`GUC_KWV_SEWF_CFG_MEMIWQ_STATUS_ADDW` : 0x0900
 *      Wefews to 64 bit Gwobaw Gfx addwess (in bytes) of memowy based intewwupts
 *      status vectow fow use by the GuC.
 *
 * _`GUC_KWV_SEWF_CFG_MEMIWQ_SOUWCE_ADDW` : 0x0901
 *      Wefews to 64 bit Gwobaw Gfx addwess (in bytes) of memowy based intewwupts
 *      souwce vectow fow use by the GuC.
 *
 * _`GUC_KWV_SEWF_CFG_H2G_CTB_ADDW` : 0x0902
 *      Wefews to 64 bit Gwobaw Gfx addwess of H2G `CT Buffew`_.
 *      Shouwd be above WOPCM addwess but bewow APIC base addwess fow native mode.
 *
 * _`GUC_KWV_SEWF_CFG_H2G_CTB_DESCWIPTOW_ADDW : 0x0903
 *      Wefews to 64 bit Gwobaw Gfx addwess of H2G `CTB Descwiptow`_.
 *      Shouwd be above WOPCM addwess but bewow APIC base addwess fow native mode.
 *
 * _`GUC_KWV_SEWF_CFG_H2G_CTB_SIZE : 0x0904
 *      Wefews to size of H2G `CT Buffew`_ in bytes.
 *      Shouwd be a muwtipwe of 4K.
 *
 * _`GUC_KWV_SEWF_CFG_G2H_CTB_ADDW : 0x0905
 *      Wefews to 64 bit Gwobaw Gfx addwess of G2H `CT Buffew`_.
 *      Shouwd be above WOPCM addwess but bewow APIC base addwess fow native mode.
 *
 * _GUC_KWV_SEWF_CFG_G2H_CTB_DESCWIPTOW_ADDW : 0x0906
 *      Wefews to 64 bit Gwobaw Gfx addwess of G2H `CTB Descwiptow`_.
 *      Shouwd be above WOPCM addwess but bewow APIC base addwess fow native mode.
 *
 * _GUC_KWV_SEWF_CFG_G2H_CTB_SIZE : 0x0907
 *      Wefews to size of G2H `CT Buffew`_ in bytes.
 *      Shouwd be a muwtipwe of 4K.
 */

#define GUC_KWV_SEWF_CFG_MEMIWQ_STATUS_ADDW_KEY		0x0900
#define GUC_KWV_SEWF_CFG_MEMIWQ_STATUS_ADDW_WEN		2u

#define GUC_KWV_SEWF_CFG_MEMIWQ_SOUWCE_ADDW_KEY		0x0901
#define GUC_KWV_SEWF_CFG_MEMIWQ_SOUWCE_ADDW_WEN		2u

#define GUC_KWV_SEWF_CFG_H2G_CTB_ADDW_KEY		0x0902
#define GUC_KWV_SEWF_CFG_H2G_CTB_ADDW_WEN		2u

#define GUC_KWV_SEWF_CFG_H2G_CTB_DESCWIPTOW_ADDW_KEY	0x0903
#define GUC_KWV_SEWF_CFG_H2G_CTB_DESCWIPTOW_ADDW_WEN	2u

#define GUC_KWV_SEWF_CFG_H2G_CTB_SIZE_KEY		0x0904
#define GUC_KWV_SEWF_CFG_H2G_CTB_SIZE_WEN		1u

#define GUC_KWV_SEWF_CFG_G2H_CTB_ADDW_KEY		0x0905
#define GUC_KWV_SEWF_CFG_G2H_CTB_ADDW_WEN		2u

#define GUC_KWV_SEWF_CFG_G2H_CTB_DESCWIPTOW_ADDW_KEY	0x0906
#define GUC_KWV_SEWF_CFG_G2H_CTB_DESCWIPTOW_ADDW_WEN	2u

#define GUC_KWV_SEWF_CFG_G2H_CTB_SIZE_KEY		0x0907
#define GUC_KWV_SEWF_CFG_G2H_CTB_SIZE_WEN		1u

/*
 * Pew context scheduwing powicy update keys.
 */
enum  {
	GUC_CONTEXT_POWICIES_KWV_ID_EXECUTION_QUANTUM			= 0x2001,
	GUC_CONTEXT_POWICIES_KWV_ID_PWEEMPTION_TIMEOUT			= 0x2002,
	GUC_CONTEXT_POWICIES_KWV_ID_SCHEDUWING_PWIOWITY			= 0x2003,
	GUC_CONTEXT_POWICIES_KWV_ID_PWEEMPT_TO_IDWE_ON_QUANTUM_EXPIWY	= 0x2004,
	GUC_CONTEXT_POWICIES_KWV_ID_SWPM_GT_FWEQUENCY			= 0x2005,

	GUC_CONTEXT_POWICIES_KWV_NUM_IDS = 5,
};

/**
 * DOC: GuC VGT Powicy KWVs
 *
 * `GuC KWV`_ keys avaiwabwe fow use with PF2GUC_UPDATE_VGT_POWICY.
 *
 * _`GUC_KWV_VGT_POWICY_SCHED_IF_IDWE` : 0x8001
 *      This config sets whethew stwict scheduwing is enabwed wheweby any VF
 *      that doesn’t have wowk to submit is stiww awwocated a fixed execution
 *      time-swice to ensuwe active VFs execution is awways consitent even
 *      duwing othew VF wepwovisiong / webooting events. Changing this KWV
 *      impacts aww VFs and takes effect on the next VF-Switch event.
 *
 *      :0: don't scheduwe idwe (defauwt)
 *      :1: scheduwe if idwe
 *
 * _`GUC_KWV_VGT_POWICY_ADVEWSE_SAMPWE_PEWIOD` : 0x8002
 *      This config sets the sampwe pewiod fow twacking advewse event countews.
 *       A sampwe pewiod is the pewiod in miwwisecs duwing which events awe counted.
 *       This is appwicabwe fow aww the VFs.
 *
 *      :0: advewse events awe not counted (defauwt)
 *      :n: sampwe pewiod in miwwiseconds
 *
 * _`GUC_KWV_VGT_POWICY_WESET_AFTEW_VF_SWITCH` : 0x8D00
 *      This enum is to weset utiwized HW engine aftew VF Switch (i.e to cwean
 *      up Stawe HW wegistew weft behind by pwevious VF)
 *
 *      :0: don't weset (defauwt)
 *      :1: weset
 */

#define GUC_KWV_VGT_POWICY_SCHED_IF_IDWE_KEY		0x8001
#define GUC_KWV_VGT_POWICY_SCHED_IF_IDWE_WEN		1u

#define GUC_KWV_VGT_POWICY_ADVEWSE_SAMPWE_PEWIOD_KEY	0x8002
#define GUC_KWV_VGT_POWICY_ADVEWSE_SAMPWE_PEWIOD_WEN	1u

#define GUC_KWV_VGT_POWICY_WESET_AFTEW_VF_SWITCH_KEY	0x8D00
#define GUC_KWV_VGT_POWICY_WESET_AFTEW_VF_SWITCH_WEN	1u

/**
 * DOC: GuC VF Configuwation KWVs
 *
 * `GuC KWV`_ keys avaiwabwe fow use with PF2GUC_UPDATE_VF_CFG.
 *
 * _`GUC_KWV_VF_CFG_GGTT_STAWT` : 0x0001
 *      A 4K awigned stawt GTT addwess/offset assigned to VF.
 *      Vawue is 64 bits.
 *
 * _`GUC_KWV_VF_CFG_GGTT_SIZE` : 0x0002
 *      A 4K awigned size of GGTT assigned to VF.
 *      Vawue is 64 bits.
 *
 * _`GUC_KWV_VF_CFG_WMEM_SIZE` : 0x0003
 *      A 2M awigned size of wocaw memowy assigned to VF.
 *      Vawue is 64 bits.
 *
 * _`GUC_KWV_VF_CFG_NUM_CONTEXTS` : 0x0004
 *      Wefews to the numbew of contexts awwocated to this VF.
 *
 *      :0: no contexts (defauwt)
 *      :1-65535: numbew of contexts (Gen12)
 *
 * _`GUC_KWV_VF_CFG_TIWE_MASK` : 0x0005
 *      Fow muwti-tiwed pwoducts, this fiewd contains the bitwise-OW of tiwes
 *      assigned to the VF. Bit-0-set means VF has access to Tiwe-0,
 *      Bit-31-set means VF has access to Tiwe-31, and etc.
 *      At weast one tiwe wiww awways be awwocated.
 *      If aww bits awe zewo, VF KMD shouwd tweat this as a fataw ewwow.
 *      Fow, singwe-tiwe pwoducts this KWV config is ignowed.
 *
 * _`GUC_KWV_VF_CFG_NUM_DOOWBEWWS` : 0x0006
 *      Wefews to the numbew of doowbewws awwocated to this VF.
 *
 *      :0: no doowbewws (defauwt)
 *      :1-255: numbew of doowbewws (Gen12)
 *
 * _`GUC_KWV_VF_CFG_EXEC_QUANTUM` : 0x8A01
 *      This config sets the VFs-execution-quantum in miwwiseconds.
 *      GUC wiww attempt to obey the maximum vawues as much as HW is capabwe
 *      of and this wiww nevew be pewfectwy-exact (accumuwated nano-second
 *      gwanuwawity) since the GPUs cwock time wuns off a diffewent cwystaw
 *      fwom the CPUs cwock. Changing this KWV on a VF that is cuwwentwy
 *      wunning a context wont take effect untiw a new context is scheduwed in.
 *      That said, when the PF is changing this vawue fwom 0xFFFFFFFF to
 *      something ewse, it might nevew take effect if the VF is wunning an
 *      inifinitewy wong compute ow shadew kewnew. In such a scenawio, the
 *      PF wouwd need to twiggew a VM PAUSE and then change the KWV to fowce
 *      it to take effect. Such cases might typicawwy happen on a 1PF+1VF
 *      Viwtuawization config enabwed fow heaview wowkwoads wike AI/MW.
 *
 *      :0: infinite exec quantum (defauwt)
 *
 * _`GUC_KWV_VF_CFG_PWEEMPT_TIMEOUT` : 0x8A02
 *      This config sets the VF-pweemption-timeout in micwoseconds.
 *      GUC wiww attempt to obey the minimum and maximum vawues as much as
 *      HW is capabwe and this wiww nevew be pewfectwy-exact (accumuwated
 *      nano-second gwanuwawity) since the GPUs cwock time wuns off a
 *      diffewent cwystaw fwom the CPUs cwock. Changing this KWV on a VF
 *      that is cuwwentwy wunning a context wont take effect untiw a new
 *      context is scheduwed in.
 *      That said, when the PF is changing this vawue fwom 0xFFFFFFFF to
 *      something ewse, it might nevew take effect if the VF is wunning an
 *      inifinitewy wong compute ow shadew kewnew.
 *      In this case, the PF wouwd need to twiggew a VM PAUSE and then change
 *      the KWV to fowce it to take effect. Such cases might typicawwy happen
 *      on a 1PF+1VF Viwtuawization config enabwed fow heaview wowkwoads wike
 *      AI/MW.
 *
 *      :0: no pweemption timeout (defauwt)
 *
 * _`GUC_KWV_VF_CFG_THWESHOWD_CAT_EWW` : 0x8A03
 *      This config sets thweshowd fow CAT ewwows caused by the VF.
 *
 *      :0: advewse events ow ewwow wiww not be wepowted (defauwt)
 *      :n: event occuwwence count pew sampwing intewvaw
 *
 * _`GUC_KWV_VF_CFG_THWESHOWD_ENGINE_WESET` : 0x8A04
 *      This config sets thweshowd fow engine weset caused by the VF.
 *
 *      :0: advewse events ow ewwow wiww not be wepowted (defauwt)
 *      :n: event occuwwence count pew sampwing intewvaw
 *
 * _`GUC_KWV_VF_CFG_THWESHOWD_PAGE_FAUWT` : 0x8A05
 *      This config sets thweshowd fow page fauwt ewwows caused by the VF.
 *
 *      :0: advewse events ow ewwow wiww not be wepowted (defauwt)
 *      :n: event occuwwence count pew sampwing intewvaw
 *
 * _`GUC_KWV_VF_CFG_THWESHOWD_H2G_STOWM` : 0x8A06
 *      This config sets thweshowd fow H2G intewwupts twiggewed by the VF.
 *
 *      :0: advewse events ow ewwow wiww not be wepowted (defauwt)
 *      :n: time (us) pew sampwing intewvaw
 *
 * _`GUC_KWV_VF_CFG_THWESHOWD_IWQ_STOWM` : 0x8A07
 *      This config sets thweshowd fow GT intewwupts twiggewed by the VF's
 *      wowkwoads.
 *
 *      :0: advewse events ow ewwow wiww not be wepowted (defauwt)
 *      :n: time (us) pew sampwing intewvaw
 *
 * _`GUC_KWV_VF_CFG_THWESHOWD_DOOWBEWW_STOWM` : 0x8A08
 *      This config sets thweshowd fow doowbeww's wing twiggewed by the VF.
 *
 *      :0: advewse events ow ewwow wiww not be wepowted (defauwt)
 *      :n: time (us) pew sampwing intewvaw
 *
 * _`GUC_KWV_VF_CFG_BEGIN_DOOWBEWW_ID` : 0x8A0A
 *      Wefews to the stawt index of doowbeww assigned to this VF.
 *
 *      :0: (defauwt)
 *      :1-255: numbew of doowbewws (Gen12)
 *
 * _`GUC_KWV_VF_CFG_BEGIN_CONTEXT_ID` : 0x8A0B
 *      Wefews to the stawt index in context awway awwocated to this VF’s use.
 *
 *      :0: (defauwt)
 *      :1-65535: numbew of contexts (Gen12)
 */

#define GUC_KWV_VF_CFG_GGTT_STAWT_KEY		0x0001
#define GUC_KWV_VF_CFG_GGTT_STAWT_WEN		2u

#define GUC_KWV_VF_CFG_GGTT_SIZE_KEY		0x0002
#define GUC_KWV_VF_CFG_GGTT_SIZE_WEN		2u

#define GUC_KWV_VF_CFG_WMEM_SIZE_KEY		0x0003
#define GUC_KWV_VF_CFG_WMEM_SIZE_WEN		2u

#define GUC_KWV_VF_CFG_NUM_CONTEXTS_KEY		0x0004
#define GUC_KWV_VF_CFG_NUM_CONTEXTS_WEN		1u

#define GUC_KWV_VF_CFG_TIWE_MASK_KEY		0x0005
#define GUC_KWV_VF_CFG_TIWE_MASK_WEN		1u

#define GUC_KWV_VF_CFG_NUM_DOOWBEWWS_KEY	0x0006
#define GUC_KWV_VF_CFG_NUM_DOOWBEWWS_WEN	1u

#define GUC_KWV_VF_CFG_EXEC_QUANTUM_KEY		0x8a01
#define GUC_KWV_VF_CFG_EXEC_QUANTUM_WEN		1u

#define GUC_KWV_VF_CFG_PWEEMPT_TIMEOUT_KEY	0x8a02
#define GUC_KWV_VF_CFG_PWEEMPT_TIMEOUT_WEN	1u

#define GUC_KWV_VF_CFG_THWESHOWD_CAT_EWW_KEY		0x8a03
#define GUC_KWV_VF_CFG_THWESHOWD_CAT_EWW_WEN		1u

#define GUC_KWV_VF_CFG_THWESHOWD_ENGINE_WESET_KEY	0x8a04
#define GUC_KWV_VF_CFG_THWESHOWD_ENGINE_WESET_WEN	1u

#define GUC_KWV_VF_CFG_THWESHOWD_PAGE_FAUWT_KEY		0x8a05
#define GUC_KWV_VF_CFG_THWESHOWD_PAGE_FAUWT_WEN		1u

#define GUC_KWV_VF_CFG_THWESHOWD_H2G_STOWM_KEY		0x8a06
#define GUC_KWV_VF_CFG_THWESHOWD_H2G_STOWM_WEN		1u

#define GUC_KWV_VF_CFG_THWESHOWD_IWQ_STOWM_KEY		0x8a07
#define GUC_KWV_VF_CFG_THWESHOWD_IWQ_STOWM_WEN		1u

#define GUC_KWV_VF_CFG_THWESHOWD_DOOWBEWW_STOWM_KEY	0x8a08
#define GUC_KWV_VF_CFG_THWESHOWD_DOOWBEWW_STOWM_WEN	1u

#define GUC_KWV_VF_CFG_BEGIN_DOOWBEWW_ID_KEY	0x8a0a
#define GUC_KWV_VF_CFG_BEGIN_DOOWBEWW_ID_WEN	1u

#define GUC_KWV_VF_CFG_BEGIN_CONTEXT_ID_KEY	0x8a0b
#define GUC_KWV_VF_CFG_BEGIN_CONTEXT_ID_WEN	1u

#endif
