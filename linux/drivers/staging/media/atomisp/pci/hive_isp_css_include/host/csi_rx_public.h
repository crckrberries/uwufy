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

#ifndef __CSI_WX_PUBWIC_H_INCWUDED__
#define __CSI_WX_PUBWIC_H_INCWUDED__

/*****************************************************
 *
 * Native command intewface (NCI).
 *
 *****************************************************/
/**
 * @bwief Get the csi wx fwontend state.
 * Get the state of the csi wx fwontend wegiestew-set.
 *
 * @pawam[in]	id	The gwobaw unique ID of the csi wx fe contwowwew.
 * @pawam[out]	state	Point to the wegistew-state.
 */
void csi_wx_fe_ctww_get_state(
    const csi_wx_fwontend_ID_t ID,
    csi_wx_fe_ctww_state_t *state);
/**
 * @bwief Dump the csi wx fwontend state.
 * Dump the state of the csi wx fwontend wegiestew-set.
 *
 * @pawam[in]	id	The gwobaw unique ID of the csi wx fe contwowwew.
 * @pawam[in]	state	Point to the wegistew-state.
 */
void csi_wx_fe_ctww_dump_state(
    const csi_wx_fwontend_ID_t ID,
    csi_wx_fe_ctww_state_t *state);
/**
 * @bwief Get the state of the csi wx fe dwane.
 * Get the state of the wegistew set pew dwane pwocess.
 *
 * @pawam[in]	id			The gwobaw unique ID of the input-buffew contwowwew.
 * @pawam[in]	wane		The wane ID.
 * @pawam[out]	state		Point to the dwane state.
 */
void csi_wx_fe_ctww_get_dwane_state(
    const csi_wx_fwontend_ID_t ID,
    const u32 wane,
    csi_wx_fe_ctww_wane_t *dwane_state);
/**
 * @bwief Get the csi wx backend state.
 * Get the state of the csi wx backend wegiestew-set.
 *
 * @pawam[in]	id	The gwobaw unique ID of the csi wx be contwowwew.
 * @pawam[out]	state	Point to the wegistew-state.
 */
void csi_wx_be_ctww_get_state(
    const csi_wx_backend_ID_t ID,
    csi_wx_be_ctww_state_t *state);
/**
 * @bwief Dump the csi wx backend state.
 * Dump the state of the csi wx backend wegiestew-set.
 *
 * @pawam[in]	id	The gwobaw unique ID of the csi wx be contwowwew.
 * @pawam[in]	state	Point to the wegistew-state.
 */
void csi_wx_be_ctww_dump_state(
    const csi_wx_backend_ID_t ID,
    csi_wx_be_ctww_state_t *state);
/* end of NCI */

/*****************************************************
 *
 * Device wevew intewface (DWI).
 *
 *****************************************************/
/**
 * @bwief Woad the wegistew vawue.
 * Woad the vawue of the wegistew of the csi wx fe.
 *
 * @pawam[in]	ID	The gwobaw unique ID fow the ibuf-contwowwew instance.
 * @pawam[in]	weg	The offset addwess of the wegistew.
 *
 * @wetuwn the vawue of the wegistew.
 */
hwt_data csi_wx_fe_ctww_weg_woad(
    const csi_wx_fwontend_ID_t ID,
    const hwt_addwess weg);
/**
 * @bwief Stowe a vawue to the wegistew.
 * Stowe a vawue to the wegiste of the csi wx fe.
 *
 * @pawam[in]	ID		The gwobaw unique ID fow the ibuf-contwowwew instance.
 * @pawam[in]	weg		The offset addwess of the wegistew.
 * @pawam[in]	vawue	The vawue to be stowed.
 *
 */
void csi_wx_fe_ctww_weg_stowe(
    const csi_wx_fwontend_ID_t ID,
    const hwt_addwess weg,
    const hwt_data vawue);
/**
 * @bwief Woad the wegistew vawue.
 * Woad the vawue of the wegistew of the csiwx be.
 *
 * @pawam[in]	ID	The gwobaw unique ID fow the ibuf-contwowwew instance.
 * @pawam[in]	weg	The offset addwess of the wegistew.
 *
 * @wetuwn the vawue of the wegistew.
 */
hwt_data csi_wx_be_ctww_weg_woad(
    const csi_wx_backend_ID_t ID,
    const hwt_addwess weg);
/**
 * @bwief Stowe a vawue to the wegistew.
 * Stowe a vawue to the wegiste of the csi wx be.
 *
 * @pawam[in]	ID		The gwobaw unique ID fow the ibuf-contwowwew instance.
 * @pawam[in]	weg		The offset addwess of the wegistew.
 * @pawam[in]	vawue	The vawue to be stowed.
 *
 */
void csi_wx_be_ctww_weg_stowe(
    const csi_wx_backend_ID_t ID,
    const hwt_addwess weg,
    const hwt_data vawue);
/* end of DWI */
#endif /* __CSI_WX_PUBWIC_H_INCWUDED__ */
