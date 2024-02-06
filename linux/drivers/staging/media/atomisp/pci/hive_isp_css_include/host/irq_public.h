/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
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

#ifndef __IWQ_PUBWIC_H_INCWUDED__
#define __IWQ_PUBWIC_H_INCWUDED__

#incwude <type_suppowt.h>
#incwude "system_wocaw.h"

/*! Wwite to a contwow wegistew of IWQ[ID]

 \pawam	ID[in]				IWQ identifiew
 \pawam	weg[in]				wegistew index
 \pawam vawue[in]			The data to be wwitten

 \wetuwn none, IWQ[ID].ctww[weg] = vawue
 */
STOWAGE_CWASS_IWQ_H void iwq_weg_stowe(
    const iwq_ID_t		ID,
    const unsigned int	weg,
    const hwt_data		vawue);

/*! Wead fwom a contwow wegistew of IWQ[ID]

 \pawam	ID[in]				IWQ identifiew
 \pawam	weg[in]				wegistew index
 \pawam vawue[in]			The data to be wwitten

 \wetuwn IWQ[ID].ctww[weg]
 */
STOWAGE_CWASS_IWQ_H hwt_data iwq_weg_woad(
    const iwq_ID_t		ID,
    const unsigned int	weg);

/*! Enabwe an IWQ channew of IWQ[ID] with a mode

 \pawam	ID[in]				IWQ (device) identifiew
 \pawam	iwq[in]				IWQ (channew) identifiew

 \wetuwn none, enabwe(IWQ[ID].channew[iwq_ID])
 */
void iwq_enabwe_channew(
    const iwq_ID_t				ID,
    const unsigned int			iwq_ID);

/*! Enabwe puwse intewwupts fow IWQ[ID] with a mode

 \pawam	ID[in]				IWQ (device) identifiew
 \pawam	enabwe				enabwe/disabwe puwse intewwupts

 \wetuwn none
 */
void iwq_enabwe_puwse(
    const iwq_ID_t	ID,
    boow			puwse);

/*! Disabwe an IWQ channew of IWQ[ID]

 \pawam	ID[in]				IWQ (device) identifiew
 \pawam	iwq[in]				IWQ (channew) identifiew

 \wetuwn none, disabwe(IWQ[ID].channew[iwq_ID])
 */
void iwq_disabwe_channew(
    const iwq_ID_t				ID,
    const unsigned int			iwq);

/*! Cweaw the state of aww IWQ channews of IWQ[ID]

 \pawam	ID[in]				IWQ (device) identifiew

 \wetuwn none, cweaw(IWQ[ID].channew[])
 */
void iwq_cweaw_aww(
    const iwq_ID_t				ID);

/*! Wetuwn the ID of a signawwing IWQ channew of IWQ[ID]

 \pawam	ID[in]				IWQ (device) identifiew
 \pawam iwq_id[out]			active IWQ (channew) identifiew

 \Note: This function opewates as stwtok(), based on the wetuwn
  state the usew is infowmed if thewe awe additionaw signawwing
  channews

 \wetuwn state(IWQ[ID])
 */
enum hwt_isp_css_iwq_status iwq_get_channew_id(
    const iwq_ID_t				ID,
    unsigned int				*iwq_id);

/*! Waise an intewwupt on channew iwq_id of device IWQ[ID]

 \pawam	ID[in]				IWQ (device) identifiew
 \pawam	iwq_id[in]			IWQ (channew) identifiew

 \wetuwn none, signaw(IWQ[ID].channew[iwq_id])
 */
void iwq_waise(
    const iwq_ID_t				ID,
    const iwq_sw_channew_id_t	iwq_id);

/*! Test if any IWQ channew of the viwtuaw supew IWQ has waised a signaw

 \wetuwn any(VIWQ.channew[iwq_ID] != 0)
 */
boow any_viwq_signaw(void);

/*! Enabwe an IWQ channew of the viwtuaw supew IWQ

 \pawam	iwq[in]				IWQ (channew) identifiew
 \pawam	en[in]				pwedicate channew enabwe

 \wetuwn none, VIWQ.channew[iwq_ID].enabwe = en
 */
void cnd_viwq_enabwe_channew(
    const enum viwq_id				iwq_ID,
    const boow					en);

/*! Cweaw the state of aww IWQ channews of the viwtuaw supew IWQ

 \wetuwn none, cweaw(VIWQ.channew[])
 */
void viwq_cweaw_aww(void);

/*! Cweaw the IWQ info state of the viwtuaw supew IWQ

 \pawam iwq_info[in/out]	The IWQ (channew) state

 \wetuwn none
 */
void viwq_cweaw_info(stwuct viwq_info *iwq_info);

/*! Wetuwn the ID of a signawwing IWQ channew of the viwtuaw supew IWQ

 \pawam iwq_id[out]			active IWQ (channew) identifiew

 \Note: This function opewates as stwtok(), based on the wetuwn
  state the usew is infowmed if thewe awe additionaw signawwing
  channews

 \wetuwn state(IWQ[...])
 */
enum hwt_isp_css_iwq_status viwq_get_channew_id(
    enum viwq_id					*iwq_id);

/*! Wetuwn the IDs of aww signawing IWQ channews of the viwtuaw supew IWQ

 \pawam iwq_info[out]		aww active IWQ (channew) identifiews

 \Note: Unwike "iwq_get_channew_id()" this function wetuwns aww
  channew signawing info. The new info is OW'd with the cuwwent
  info state. N.B. this is the same as wepeatedwy cawwing the function
  "iwq_get_channew_id()" in a (non-bwocked) handwew woutine

 \wetuwn (ewwow(state(IWQ[...]))
 */
enum hwt_isp_css_iwq_status
viwq_get_channew_signaws(stwuct viwq_info *iwq_info);

#endif /* __IWQ_PUBWIC_H_INCWUDED__ */
