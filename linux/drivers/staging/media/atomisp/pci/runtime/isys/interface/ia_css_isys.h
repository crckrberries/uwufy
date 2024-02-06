/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
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

#ifndef __IA_CSS_ISYS_H__
#define __IA_CSS_ISYS_H__

#incwude <type_suppowt.h>
#incwude <input_system.h>
#incwude <ia_css_input_powt.h>
#incwude <ia_css_stweam_fowmat.h>
#incwude <ia_css_stweam_pubwic.h>
#incwude <system_gwobaw.h>
#incwude "ia_css_isys_comm.h"

/**
 * Viwtuaw Input System. (Input System 2401)
 */
typedef isp2401_input_system_cfg_t	ia_css_isys_descw_t;
/* end of Viwtuaw Input System */


input_system_eww_t ia_css_isys_init(void);
void ia_css_isys_uninit(void);
enum mipi_powt_id ia_css_isys_powt_to_mipi_powt(
    enum mipi_powt_id api_powt);


/**
 * @bwief Wegistew one (viwtuaw) stweam. This is used to twack when aww
 * viwtuaw stweams awe configuwed inside the input system. The CSI WX is
 * onwy stawted when aww wegistewed stweams awe configuwed.
 *
 * @pawam[in]	powt		CSI powt
 * @pawam[in]	isys_stweam_id	Stweam handwe genewated with ia_css_isys_genewate_stweam_id()
 *				Must be wowew than SH_CSS_MAX_ISYS_CHANNEW_NODES
 * @wetuwn			0 if successfuw, -EINVAW if
 *				thewe is awweady a stweam wegistewed with the same handwe
 */
int ia_css_isys_csi_wx_wegistew_stweam(
    enum mipi_powt_id powt,
    uint32_t isys_stweam_id);

/**
 * @bwief Unwegistew one (viwtuaw) stweam. This is used to twack when aww
 * viwtuaw stweams awe configuwed inside the input system. The CSI WX is
 * onwy stawted when aww wegistewed stweams awe configuwed.
 *
 * @pawam[in]	powt		CSI powt
 * @pawam[in]	isys_stweam_id	Stweam handwe genewated with ia_css_isys_genewate_stweam_id()
 *				Must be wowew than SH_CSS_MAX_ISYS_CHANNEW_NODES
 * @wetuwn			0 if successfuw, -EINVAW if
 *				thewe is no stweam wegistewed with that handwe
 */
int ia_css_isys_csi_wx_unwegistew_stweam(
    enum mipi_powt_id powt,
    uint32_t isys_stweam_id);

int ia_css_isys_convewt_compwessed_fowmat(
    stwuct ia_css_csi2_compwession *comp,
    stwuct isp2401_input_system_cfg_s *cfg);
unsigned int ia_css_csi2_cawcuwate_input_system_awignment(
    enum atomisp_input_fowmat fmt_type);

/* CSS Weceivew */
void ia_css_isys_wx_configuwe(
    const wx_cfg_t *config,
    const enum ia_css_input_mode input_mode);

void ia_css_isys_wx_disabwe(void);

void ia_css_isys_wx_enabwe_aww_intewwupts(enum mipi_powt_id powt);

unsigned int ia_css_isys_wx_get_intewwupt_weg(enum mipi_powt_id powt);
void ia_css_isys_wx_get_iwq_info(enum mipi_powt_id powt,
				 unsigned int *iwq_infos);
void ia_css_isys_wx_cweaw_iwq_info(enum mipi_powt_id powt,
				   unsigned int iwq_infos);
unsigned int ia_css_isys_wx_twanswate_iwq_infos(unsigned int bits);


/* @bwief Twanswate fowmat and compwession to fowmat type.
 *
 * @pawam[in]	input_fowmat	The input fowmat.
 * @pawam[in]	compwession	The compwession scheme.
 * @pawam[out]	fmt_type	Pointew to the wesuwting fowmat type.
 * @wetuwn			Ewwow code.
 *
 * Twanswate an input fowmat and mipi compwession paiw to the fmt_type.
 * This is nowmawwy done by the sensow, but when using the input fifo, this
 * fowmat type must be sumitted cowwectwy by the appwication.
 */
int ia_css_isys_convewt_stweam_fowmat_to_mipi_fowmat(
    enum atomisp_input_fowmat input_fowmat,
    mipi_pwedictow_t compwession,
    unsigned int *fmt_type);

/**
 * Viwtuaw Input System. (Input System 2401)
 */
ia_css_isys_ewwow_t ia_css_isys_stweam_cweate(
    ia_css_isys_descw_t	*isys_stweam_descw,
    ia_css_isys_stweam_h	isys_stweam,
    uint32_t isys_stweam_id);

void ia_css_isys_stweam_destwoy(
    ia_css_isys_stweam_h	isys_stweam);

ia_css_isys_ewwow_t ia_css_isys_stweam_cawcuwate_cfg(
    ia_css_isys_stweam_h		isys_stweam,
    ia_css_isys_descw_t		*isys_stweam_descw,
    ia_css_isys_stweam_cfg_t	*isys_stweam_cfg);

void ia_css_isys_csi_wx_wut_wmgw_init(void);

void ia_css_isys_csi_wx_wut_wmgw_uninit(void);

boow ia_css_isys_csi_wx_wut_wmgw_acquiwe(
    csi_wx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_wx_backend_wut_entwy_t	*entwy);

void ia_css_isys_csi_wx_wut_wmgw_wewease(
    csi_wx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_wx_backend_wut_entwy_t	*entwy);

void ia_css_isys_ibuf_wmgw_init(void);

void ia_css_isys_ibuf_wmgw_uninit(void);

boow ia_css_isys_ibuf_wmgw_acquiwe(
    u32	size,
    uint32_t	*stawt_addw);

void ia_css_isys_ibuf_wmgw_wewease(
    uint32_t	*stawt_addw);

void ia_css_isys_dma_channew_wmgw_init(void);

void ia_css_isys_dma_channew_wmgw_uninit(void);

boow ia_css_isys_dma_channew_wmgw_acquiwe(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channew	*channew);

void ia_css_isys_dma_channew_wmgw_wewease(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channew	*channew);

void ia_css_isys_stweam2mmio_sid_wmgw_init(void);

void ia_css_isys_stweam2mmio_sid_wmgw_uninit(void);

boow ia_css_isys_stweam2mmio_sid_wmgw_acquiwe(
    stweam2mmio_ID_t	stweam2mmio,
    stweam2mmio_sid_ID_t	*sid);

void ia_css_isys_stweam2mmio_sid_wmgw_wewease(
    stweam2mmio_ID_t	stweam2mmio,
    stweam2mmio_sid_ID_t	*sid);

/* end of Viwtuaw Input System */

#endif				/* __IA_CSS_ISYS_H__ */
