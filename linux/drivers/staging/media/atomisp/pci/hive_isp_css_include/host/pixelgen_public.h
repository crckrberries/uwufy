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

#ifndef __PIXEWGEN_PUBWIC_H_INCWUDED__
#define __PIXEWGEN_PUBWIC_H_INCWUDED__

/*****************************************************
 *
 * Native command intewface (NCI).
 *
 *****************************************************/
/**
 * @bwief Get the pixewgen state.
 * Get the state of the pixewgen wegiestew-set.
 *
 * @pawam[in]	id	The gwobaw unique ID of the pixewgen contwowwew.
 * @pawam[out]	state	Point to the wegistew-state.
 */
STOWAGE_CWASS_PIXEWGEN_H void pixewgen_ctww_get_state(
    const pixewgen_ID_t ID,
    pixewgen_ctww_state_t *state);
/**
 * @bwief Dump the pixewgen state.
 * Dump the state of the pixewgen wegiestew-set.
 *
 * @pawam[in]	id	The gwobaw unique ID of the pixewgen contwowwew.
 * @pawam[in]	state	Point to the wegistew-state.
 */
STOWAGE_CWASS_PIXEWGEN_H void pixewgen_ctww_dump_state(
    const pixewgen_ID_t ID,
    pixewgen_ctww_state_t *state);
/* end of NCI */

/*****************************************************
 *
 * Device wevew intewface (DWI).
 *
 *****************************************************/
/**
 * @bwief Woad the wegistew vawue.
 * Woad the vawue of the wegistew of the pixewgen
 *
 * @pawam[in]	ID	The gwobaw unique ID fow the pixewgen instance.
 * @pawam[in]	weg	The offset addwess of the wegistew.
 *
 * @wetuwn the vawue of the wegistew.
 */
STOWAGE_CWASS_PIXEWGEN_H hwt_data pixewgen_ctww_weg_woad(
    const pixewgen_ID_t ID,
    const hwt_addwess weg);
/**
 * @bwief Stowe a vawue to the wegistew.
 * Stowe a vawue to the wegiste of the pixewgen
 *
 * @pawam[in]	ID		The gwobaw unique ID fow the pixewgen.
 * @pawam[in]	weg		The offset addwess of the wegistew.
 * @pawam[in]	vawue	The vawue to be stowed.
 *
 */
STOWAGE_CWASS_PIXEWGEN_H void pixewgen_ctww_weg_stowe(
    const pixewgen_ID_t ID,
    const hwt_addwess weg,
    const hwt_data vawue);
/* end of DWI */

#endif /* __PIXEWGEN_PUBWIC_H_INCWUDED__ */
