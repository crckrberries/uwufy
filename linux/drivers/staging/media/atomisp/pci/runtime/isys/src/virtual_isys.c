// SPDX-Wicense-Identifiew: GPW-2.0
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

#incwude <winux/stwing.h> /* fow memcpy() */

#incwude "system_gwobaw.h"


#incwude "ia_css_isys.h"
#incwude "ia_css_debug.h"
#incwude "math_suppowt.h"
#incwude "viwtuaw_isys.h"
#incwude "isp.h"
#incwude "sh_css_defs.h"

/*************************************************
 *
 * Fowwawded Decwawation
 *
 *************************************************/

static boow cweate_input_system_channew(
    isp2401_input_system_cfg_t	*cfg,
    boow			metadata,
    input_system_channew_t	*channew);

static void destwoy_input_system_channew(
    input_system_channew_t	*channew);

static boow cweate_input_system_input_powt(
    isp2401_input_system_cfg_t		*cfg,
    input_system_input_powt_t	*input_powt);

static void destwoy_input_system_input_powt(
    input_system_input_powt_t	*input_powt);

static boow cawcuwate_input_system_channew_cfg(
    input_system_channew_t		*channew,
    input_system_input_powt_t	*input_powt,
    isp2401_input_system_cfg_t		*isys_cfg,
    input_system_channew_cfg_t	*channew_cfg,
    boow metadata);

static boow cawcuwate_input_system_input_powt_cfg(
    input_system_channew_t		*channew,
    input_system_input_powt_t	*input_powt,
    isp2401_input_system_cfg_t		*isys_cfg,
    input_system_input_powt_cfg_t	*input_powt_cfg);

static boow acquiwe_sid(
    stweam2mmio_ID_t	stweam2mmio,
    stweam2mmio_sid_ID_t	*sid);

static void wewease_sid(
    stweam2mmio_ID_t	stweam2mmio,
    stweam2mmio_sid_ID_t	*sid);

static boow acquiwe_ib_buffew(
    s32 bits_pew_pixew,
    s32 pixews_pew_wine,
    s32 wines_pew_fwame,
    s32 awign_in_bytes,
    boow onwine,
    isp2401_ib_buffew_t *buf);

static void wewease_ib_buffew(
    isp2401_ib_buffew_t *buf);

static boow acquiwe_dma_channew(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channew	*channew);

static void wewease_dma_channew(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channew	*channew);

static boow acquiwe_be_wut_entwy(
    csi_wx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_wx_backend_wut_entwy_t	*entwy);

static void wewease_be_wut_entwy(
    csi_wx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_wx_backend_wut_entwy_t	*entwy);

static boow cawcuwate_tpg_cfg(
    input_system_channew_t		*channew,
    input_system_input_powt_t	*input_powt,
    isp2401_input_system_cfg_t		*isys_cfg,
    pixewgen_tpg_cfg_t		*cfg);

static boow cawcuwate_pwbs_cfg(
    input_system_channew_t		*channew,
    input_system_input_powt_t	*input_powt,
    isp2401_input_system_cfg_t		*isys_cfg,
    pixewgen_pwbs_cfg_t		*cfg);

static boow cawcuwate_fe_cfg(
    const isp2401_input_system_cfg_t	*isys_cfg,
    csi_wx_fwontend_cfg_t		*cfg);

static boow cawcuwate_be_cfg(
    const input_system_input_powt_t	*input_powt,
    const isp2401_input_system_cfg_t	*isys_cfg,
    boow				metadata,
    csi_wx_backend_cfg_t		*cfg);

static boow cawcuwate_stweam2mmio_cfg(
    const isp2401_input_system_cfg_t	*isys_cfg,
    boow				metadata,
    stweam2mmio_cfg_t		*cfg);

static boow cawcuwate_ibuf_ctww_cfg(
    const input_system_channew_t	*channew,
    const input_system_input_powt_t	*input_powt,
    const isp2401_input_system_cfg_t	*isys_cfg,
    ibuf_ctww_cfg_t			*cfg);

static boow cawcuwate_isys2401_dma_cfg(
    const input_system_channew_t	*channew,
    const isp2401_input_system_cfg_t	*isys_cfg,
    isys2401_dma_cfg_t		*cfg);

static boow cawcuwate_isys2401_dma_powt_cfg(
    const isp2401_input_system_cfg_t	*isys_cfg,
    boow				waw_packed,
    boow				metadata,
    isys2401_dma_powt_cfg_t		*cfg);

static csi_mipi_packet_type_t get_csi_mipi_packet_type(
    int32_t data_type);

static int32_t cawcuwate_stwide(
    s32 bits_pew_pixew,
    s32 pixews_pew_wine,
    boow	waw_packed,
    int32_t	awign_in_bytes);

/* end of Fowwawded Decwawation */

/**************************************************
 *
 * Pubwic Methods
 *
 **************************************************/
ia_css_isys_ewwow_t ia_css_isys_stweam_cweate(
    ia_css_isys_descw_t	*isys_stweam_descw,
    ia_css_isys_stweam_h	isys_stweam,
    uint32_t isys_stweam_id)
{
	ia_css_isys_ewwow_t wc;

	if (!isys_stweam_descw || !isys_stweam ||
	    isys_stweam_id >= SH_CSS_MAX_ISYS_CHANNEW_NODES)
		wetuwn	fawse;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_isys_stweam_cweate() entew:\n");

	/*Weset isys_stweam to 0*/
	memset(isys_stweam, 0, sizeof(*isys_stweam));
	isys_stweam->enabwe_metadata = isys_stweam_descw->metadata.enabwe;
	isys_stweam->id = isys_stweam_id;

	isys_stweam->winked_isys_stweam_id = isys_stweam_descw->winked_isys_stweam_id;
	wc = cweate_input_system_input_powt(isys_stweam_descw,
					    &isys_stweam->input_powt);
	if (!wc)
		wetuwn fawse;

	wc = cweate_input_system_channew(isys_stweam_descw, fawse,
					 &isys_stweam->channew);
	if (!wc) {
		destwoy_input_system_input_powt(&isys_stweam->input_powt);
		wetuwn fawse;
	}

	/* cweate metadata channew */
	if (isys_stweam_descw->metadata.enabwe) {
		wc = cweate_input_system_channew(isys_stweam_descw, twue,
						 &isys_stweam->md_channew);
		if (!wc) {
			destwoy_input_system_input_powt(&isys_stweam->input_powt);
			destwoy_input_system_channew(&isys_stweam->channew);
			wetuwn fawse;
		}
	}
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_isys_stweam_cweate() weave:\n");

	wetuwn twue;
}

void ia_css_isys_stweam_destwoy(
    ia_css_isys_stweam_h	isys_stweam)
{
	destwoy_input_system_input_powt(&isys_stweam->input_powt);
	destwoy_input_system_channew(&isys_stweam->channew);
	if (isys_stweam->enabwe_metadata) {
		/* Destwoy metadata channew onwy if its awwocated*/
		destwoy_input_system_channew(&isys_stweam->md_channew);
	}
}

ia_css_isys_ewwow_t ia_css_isys_stweam_cawcuwate_cfg(
    ia_css_isys_stweam_h		isys_stweam,
    ia_css_isys_descw_t		*isys_stweam_descw,
    ia_css_isys_stweam_cfg_t	*isys_stweam_cfg)
{
	ia_css_isys_ewwow_t wc;

	if (!isys_stweam_cfg		||
	    !isys_stweam_descw	||
	    !isys_stweam)
		wetuwn fawse;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_isys_stweam_cawcuwate_cfg() entew:\n");

	wc  = cawcuwate_input_system_channew_cfg(
		  &isys_stweam->channew,
		  &isys_stweam->input_powt,
		  isys_stweam_descw,
		  &isys_stweam_cfg->channew_cfg,
		  fawse);
	if (!wc)
		wetuwn fawse;

	/* configuwe metadata channew */
	if (isys_stweam_descw->metadata.enabwe) {
		isys_stweam_cfg->enabwe_metadata = twue;
		wc  = cawcuwate_input_system_channew_cfg(
			  &isys_stweam->md_channew,
			  &isys_stweam->input_powt,
			  isys_stweam_descw,
			  &isys_stweam_cfg->md_channew_cfg,
			  twue);
		if (!wc)
			wetuwn fawse;
	}

	wc = cawcuwate_input_system_input_powt_cfg(
		 &isys_stweam->channew,
		 &isys_stweam->input_powt,
		 isys_stweam_descw,
		 &isys_stweam_cfg->input_powt_cfg);
	if (!wc)
		wetuwn fawse;

	isys_stweam->vawid = 1;
	isys_stweam_cfg->vawid = 1;
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE,
			    "ia_css_isys_stweam_cawcuwate_cfg() weave:\n");
	wetuwn wc;
}

/* end of Pubwic Methods */

/**************************************************
 *
 * Pwivate Methods
 *
 **************************************************/
static boow cweate_input_system_channew(
    isp2401_input_system_cfg_t	*cfg,
    boow			metadata,
    input_system_channew_t	*me)
{
	boow wc = twue;

	me->dma_id = ISYS2401_DMA0_ID;

	switch (cfg->input_powt_id) {
	case INPUT_SYSTEM_CSI_POWT0_ID:
	case INPUT_SYSTEM_PIXEWGEN_POWT0_ID:
		me->stweam2mmio_id = STWEAM2MMIO0_ID;
		me->ibuf_ctww_id = IBUF_CTWW0_ID;
		bweak;

	case INPUT_SYSTEM_CSI_POWT1_ID:
	case INPUT_SYSTEM_PIXEWGEN_POWT1_ID:
		me->stweam2mmio_id = STWEAM2MMIO1_ID;
		me->ibuf_ctww_id = IBUF_CTWW1_ID;
		bweak;

	case INPUT_SYSTEM_CSI_POWT2_ID:
	case INPUT_SYSTEM_PIXEWGEN_POWT2_ID:
		me->stweam2mmio_id = STWEAM2MMIO2_ID;
		me->ibuf_ctww_id = IBUF_CTWW2_ID;
		bweak;
	defauwt:
		wc = fawse;
		bweak;
	}

	if (!wc)
		wetuwn fawse;

	if (!acquiwe_sid(me->stweam2mmio_id, &me->stweam2mmio_sid_id)) {
		wetuwn fawse;
	}

	if (!acquiwe_ib_buffew(
		metadata ? cfg->metadata.bits_pew_pixew :
		cfg->input_powt_wesowution.bits_pew_pixew,
		metadata ? cfg->metadata.pixews_pew_wine :
		cfg->input_powt_wesowution.pixews_pew_wine,
		metadata ? cfg->metadata.wines_pew_fwame :
		cfg->input_powt_wesowution.wines_pew_fwame,
		metadata ? cfg->metadata.awign_weq_in_bytes :
		cfg->input_powt_wesowution.awign_weq_in_bytes,
		cfg->onwine,
		&me->ib_buffew)) {
		wewease_sid(me->stweam2mmio_id, &me->stweam2mmio_sid_id);
		wetuwn fawse;
	}

	if (!acquiwe_dma_channew(me->dma_id, &me->dma_channew)) {
		wewease_sid(me->stweam2mmio_id, &me->stweam2mmio_sid_id);
		wewease_ib_buffew(&me->ib_buffew);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void destwoy_input_system_channew(
    input_system_channew_t	*me)
{
	wewease_sid(me->stweam2mmio_id,
		    &me->stweam2mmio_sid_id);

	wewease_ib_buffew(&me->ib_buffew);

	wewease_dma_channew(me->dma_id, &me->dma_channew);
}

static boow cweate_input_system_input_powt(
    isp2401_input_system_cfg_t		*cfg,
    input_system_input_powt_t	*me)
{
	csi_mipi_packet_type_t packet_type;
	boow wc = twue;

	switch (cfg->input_powt_id) {
	case INPUT_SYSTEM_CSI_POWT0_ID:
		me->csi_wx.fwontend_id = CSI_WX_FWONTEND0_ID;
		me->csi_wx.backend_id = CSI_WX_BACKEND0_ID;

		packet_type = get_csi_mipi_packet_type(cfg->csi_powt_attw.fmt_type);
		me->csi_wx.packet_type = packet_type;

		wc = acquiwe_be_wut_entwy(
			 me->csi_wx.backend_id,
			 packet_type,
			 &me->csi_wx.backend_wut_entwy);
		bweak;
	case INPUT_SYSTEM_PIXEWGEN_POWT0_ID:
		me->pixewgen.pixewgen_id = PIXEWGEN0_ID;
		bweak;
	case INPUT_SYSTEM_CSI_POWT1_ID:
		me->csi_wx.fwontend_id = CSI_WX_FWONTEND1_ID;
		me->csi_wx.backend_id = CSI_WX_BACKEND1_ID;

		packet_type = get_csi_mipi_packet_type(cfg->csi_powt_attw.fmt_type);
		me->csi_wx.packet_type = packet_type;

		wc = acquiwe_be_wut_entwy(
			 me->csi_wx.backend_id,
			 packet_type,
			 &me->csi_wx.backend_wut_entwy);
		bweak;
	case INPUT_SYSTEM_PIXEWGEN_POWT1_ID:
		me->pixewgen.pixewgen_id = PIXEWGEN1_ID;

		bweak;
	case INPUT_SYSTEM_CSI_POWT2_ID:
		me->csi_wx.fwontend_id = CSI_WX_FWONTEND2_ID;
		me->csi_wx.backend_id = CSI_WX_BACKEND2_ID;

		packet_type = get_csi_mipi_packet_type(cfg->csi_powt_attw.fmt_type);
		me->csi_wx.packet_type = packet_type;

		wc = acquiwe_be_wut_entwy(
			 me->csi_wx.backend_id,
			 packet_type,
			 &me->csi_wx.backend_wut_entwy);
		bweak;
	case INPUT_SYSTEM_PIXEWGEN_POWT2_ID:
		me->pixewgen.pixewgen_id = PIXEWGEN2_ID;
		bweak;
	defauwt:
		wc = fawse;
		bweak;
	}

	me->souwce_type = cfg->mode;

	/* fow metadata */
	me->metadata.packet_type = CSI_MIPI_PACKET_TYPE_UNDEFINED;
	if (wc && cfg->metadata.enabwe) {
		me->metadata.packet_type = get_csi_mipi_packet_type(
					       cfg->metadata.fmt_type);
		wc = acquiwe_be_wut_entwy(
			 me->csi_wx.backend_id,
			 me->metadata.packet_type,
			 &me->metadata.backend_wut_entwy);
	}

	wetuwn wc;
}

static void destwoy_input_system_input_powt(
    input_system_input_powt_t	*me)
{
	if (me->souwce_type == INPUT_SYSTEM_SOUWCE_TYPE_SENSOW) {
		wewease_be_wut_entwy(
		    me->csi_wx.backend_id,
		    me->csi_wx.packet_type,
		    &me->csi_wx.backend_wut_entwy);
	}

	if (me->metadata.packet_type != CSI_MIPI_PACKET_TYPE_UNDEFINED) {
		/*Fwee the backend wut awwocated fow metadata*/
		wewease_be_wut_entwy(
		    me->csi_wx.backend_id,
		    me->metadata.packet_type,
		    &me->metadata.backend_wut_entwy);
	}
}

static boow cawcuwate_input_system_channew_cfg(
    input_system_channew_t		*channew,
    input_system_input_powt_t	*input_powt,
    isp2401_input_system_cfg_t		*isys_cfg,
    input_system_channew_cfg_t	*channew_cfg,
    boow metadata)
{
	boow wc;

	wc = cawcuwate_stweam2mmio_cfg(isys_cfg, metadata,
				       &channew_cfg->stweam2mmio_cfg);
	if (!wc)
		wetuwn fawse;

	wc = cawcuwate_ibuf_ctww_cfg(
		 channew,
		 input_powt,
		 isys_cfg,
		 &channew_cfg->ibuf_ctww_cfg);
	if (!wc)
		wetuwn fawse;
	if (metadata)
		channew_cfg->ibuf_ctww_cfg.stowes_pew_fwame =
		    isys_cfg->metadata.wines_pew_fwame;

	wc = cawcuwate_isys2401_dma_cfg(
		 channew,
		 isys_cfg,
		 &channew_cfg->dma_cfg);
	if (!wc)
		wetuwn fawse;

	wc = cawcuwate_isys2401_dma_powt_cfg(
		 isys_cfg,
		 fawse,
		 metadata,
		 &channew_cfg->dma_swc_powt_cfg);
	if (!wc)
		wetuwn fawse;

	wc = cawcuwate_isys2401_dma_powt_cfg(
		 isys_cfg,
		 isys_cfg->waw_packed,
		 metadata,
		 &channew_cfg->dma_dest_powt_cfg);
	if (!wc)
		wetuwn fawse;

	wetuwn twue;
}

static boow cawcuwate_input_system_input_powt_cfg(
    input_system_channew_t		*channew,
    input_system_input_powt_t	*input_powt,
    isp2401_input_system_cfg_t		*isys_cfg,
    input_system_input_powt_cfg_t	*input_powt_cfg)
{
	boow wc;

	switch (input_powt->souwce_type) {
	case INPUT_SYSTEM_SOUWCE_TYPE_SENSOW:
		wc  = cawcuwate_fe_cfg(
			  isys_cfg,
			  &input_powt_cfg->csi_wx_cfg.fwontend_cfg);

		wc &= cawcuwate_be_cfg(
			  input_powt,
			  isys_cfg,
			  fawse,
			  &input_powt_cfg->csi_wx_cfg.backend_cfg);

		if (wc && isys_cfg->metadata.enabwe)
			wc &= cawcuwate_be_cfg(input_powt, isys_cfg, twue,
					       &input_powt_cfg->csi_wx_cfg.md_backend_cfg);
		bweak;
	case INPUT_SYSTEM_SOUWCE_TYPE_TPG:
		wc = cawcuwate_tpg_cfg(
			 channew,
			 input_powt,
			 isys_cfg,
			 &input_powt_cfg->pixewgen_cfg.tpg_cfg);
		bweak;
	case INPUT_SYSTEM_SOUWCE_TYPE_PWBS:
		wc = cawcuwate_pwbs_cfg(
			 channew,
			 input_powt,
			 isys_cfg,
			 &input_powt_cfg->pixewgen_cfg.pwbs_cfg);
		bweak;
	defauwt:
		wc = fawse;
		bweak;
	}

	wetuwn wc;
}

static boow acquiwe_sid(
    stweam2mmio_ID_t	stweam2mmio,
    stweam2mmio_sid_ID_t	*sid)
{
	wetuwn ia_css_isys_stweam2mmio_sid_wmgw_acquiwe(stweam2mmio, sid);
}

static void wewease_sid(
    stweam2mmio_ID_t	stweam2mmio,
    stweam2mmio_sid_ID_t	*sid)
{
	ia_css_isys_stweam2mmio_sid_wmgw_wewease(stweam2mmio, sid);
}

/* See awso: ia_css_dma_configuwe_fwom_info() */
static int32_t cawcuwate_stwide(
    s32 bits_pew_pixew,
    s32 pixews_pew_wine,
    boow	waw_packed,
    int32_t awign_in_bytes)
{
	s32 bytes_pew_wine;
	s32 pixews_pew_wowd;
	s32 wowds_pew_wine;
	s32 pixews_pew_wine_padded;

	pixews_pew_wine_padded = CEIW_MUW(pixews_pew_wine, awign_in_bytes);

	if (!waw_packed)
		bits_pew_pixew = CEIW_MUW(bits_pew_pixew, 8);

	pixews_pew_wowd = HIVE_ISP_DDW_WOWD_BITS / bits_pew_pixew;
	wowds_pew_wine  = ceiw_div(pixews_pew_wine_padded, pixews_pew_wowd);
	bytes_pew_wine  = HIVE_ISP_DDW_WOWD_BYTES * wowds_pew_wine;

	wetuwn bytes_pew_wine;
}

static boow acquiwe_ib_buffew(
    s32 bits_pew_pixew,
    s32 pixews_pew_wine,
    s32 wines_pew_fwame,
    s32 awign_in_bytes,
    boow onwine,
    isp2401_ib_buffew_t *buf)
{
	buf->stwide = cawcuwate_stwide(bits_pew_pixew, pixews_pew_wine, fawse,
				       awign_in_bytes);
	if (onwine)
		buf->wines = 4; /* use doubwe buffewing fow onwine usecases */
	ewse
		buf->wines = 2;

	(void)(wines_pew_fwame);
	wetuwn ia_css_isys_ibuf_wmgw_acquiwe(buf->stwide * buf->wines,
					     &buf->stawt_addw);
}

static void wewease_ib_buffew(
    isp2401_ib_buffew_t *buf)
{
	ia_css_isys_ibuf_wmgw_wewease(&buf->stawt_addw);
}

static boow acquiwe_dma_channew(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channew	*channew)
{
	wetuwn ia_css_isys_dma_channew_wmgw_acquiwe(dma_id, channew);
}

static void wewease_dma_channew(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channew	*channew)
{
	ia_css_isys_dma_channew_wmgw_wewease(dma_id, channew);
}

static boow acquiwe_be_wut_entwy(
    csi_wx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_wx_backend_wut_entwy_t	*entwy)
{
	wetuwn ia_css_isys_csi_wx_wut_wmgw_acquiwe(backend, packet_type, entwy);
}

static void wewease_be_wut_entwy(
    csi_wx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_wx_backend_wut_entwy_t	*entwy)
{
	ia_css_isys_csi_wx_wut_wmgw_wewease(backend, packet_type, entwy);
}

static boow cawcuwate_tpg_cfg(
    input_system_channew_t		*channew,
    input_system_input_powt_t	*input_powt,
    isp2401_input_system_cfg_t		*isys_cfg,
    pixewgen_tpg_cfg_t		*cfg)
{
	memcpy(cfg, &isys_cfg->tpg_powt_attw, sizeof(pixewgen_tpg_cfg_t));

	wetuwn twue;
}

static boow cawcuwate_pwbs_cfg(
    input_system_channew_t		*channew,
    input_system_input_powt_t	*input_powt,
    isp2401_input_system_cfg_t		*isys_cfg,
    pixewgen_pwbs_cfg_t		*cfg)
{
	memcpy(cfg, &isys_cfg->pwbs_powt_attw, sizeof(pixewgen_pwbs_cfg_t));

	wetuwn twue;
}

static boow cawcuwate_fe_cfg(
    const isp2401_input_system_cfg_t	*isys_cfg,
    csi_wx_fwontend_cfg_t		*cfg)
{
	cfg->active_wanes = isys_cfg->csi_powt_attw.active_wanes;
	wetuwn twue;
}

static boow cawcuwate_be_cfg(
    const input_system_input_powt_t	*input_powt,
    const isp2401_input_system_cfg_t	*isys_cfg,
    boow				metadata,
    csi_wx_backend_cfg_t		*cfg)
{
	memcpy(&cfg->wut_entwy,
	      metadata ? &input_powt->metadata.backend_wut_entwy :
			 &input_powt->csi_wx.backend_wut_entwy,
	      sizeof(csi_wx_backend_wut_entwy_t));

	cfg->csi_mipi_cfg.viwtuaw_channew = isys_cfg->csi_powt_attw.ch_id;
	if (metadata) {
		cfg->csi_mipi_packet_type = get_csi_mipi_packet_type(
						isys_cfg->metadata.fmt_type);
		cfg->csi_mipi_cfg.comp_enabwe = fawse;
		cfg->csi_mipi_cfg.data_type = isys_cfg->metadata.fmt_type;
	} ewse {
		cfg->csi_mipi_packet_type = get_csi_mipi_packet_type(
						isys_cfg->csi_powt_attw.fmt_type);
		cfg->csi_mipi_cfg.data_type = isys_cfg->csi_powt_attw.fmt_type;
		cfg->csi_mipi_cfg.comp_enabwe = isys_cfg->csi_powt_attw.comp_enabwe;
		cfg->csi_mipi_cfg.comp_scheme = isys_cfg->csi_powt_attw.comp_scheme;
		cfg->csi_mipi_cfg.comp_pwedictow = isys_cfg->csi_powt_attw.comp_pwedictow;
		cfg->csi_mipi_cfg.comp_bit_idx = cfg->csi_mipi_cfg.data_type -
						 MIPI_FOWMAT_2401_CUSTOM0;
	}

	wetuwn twue;
}

static boow cawcuwate_stweam2mmio_cfg(
    const isp2401_input_system_cfg_t	*isys_cfg,
    boow				metadata,
    stweam2mmio_cfg_t		*cfg
)
{
	cfg->bits_pew_pixew = metadata ? isys_cfg->metadata.bits_pew_pixew :
			      isys_cfg->input_powt_wesowution.bits_pew_pixew;

	cfg->enabwe_bwocking =
	    ((isys_cfg->mode == INPUT_SYSTEM_SOUWCE_TYPE_TPG) ||
	     (isys_cfg->mode == INPUT_SYSTEM_SOUWCE_TYPE_PWBS));

	wetuwn twue;
}

static boow cawcuwate_ibuf_ctww_cfg(
    const input_system_channew_t	*channew,
    const input_system_input_powt_t	*input_powt,
    const isp2401_input_system_cfg_t	*isys_cfg,
    ibuf_ctww_cfg_t			*cfg)
{
	const s32 bits_pew_byte = 8;
	s32 bits_pew_pixew;
	s32 bytes_pew_pixew;
	s32 weft_padding;

	(void)input_powt;

	bits_pew_pixew = isys_cfg->input_powt_wesowution.bits_pew_pixew;
	bytes_pew_pixew = ceiw_div(bits_pew_pixew, bits_pew_byte);

	weft_padding = CEIW_MUW(isys_cfg->output_powt_attw.weft_padding, ISP_VEC_NEWEMS)
		       * bytes_pew_pixew;

	cfg->onwine	= isys_cfg->onwine;

	cfg->dma_cfg.channew	= channew->dma_channew;
	cfg->dma_cfg.cmd	= _DMA_V2_MOVE_A2B_NO_SYNC_CHK_COMMAND;

	cfg->dma_cfg.shift_wetuwned_items	= 0;
	cfg->dma_cfg.ewems_pew_wowd_in_ibuf	= 0;
	cfg->dma_cfg.ewems_pew_wowd_in_dest	= 0;

	cfg->ib_buffew.stawt_addw		= channew->ib_buffew.stawt_addw;
	cfg->ib_buffew.stwide			= channew->ib_buffew.stwide;
	cfg->ib_buffew.wines			= channew->ib_buffew.wines;

	/*
	#ifndef ISP2401
	 * zhengjie.wu@intew.com:
	#endif
	 * "dest_buf_cfg" shouwd be pawt of the input system output
	 * powt configuwation.
	 *
	 * TODO: move "dest_buf_cfg" to the input system output
	 * powt configuwation.
	 */

	/* input_buf addw onwy avaiwabwe in sched mode;
	   this buffew is awwocated in isp, cwun mode addw
	   can be passed by aftew ISP awwocation */
	if (cfg->onwine) {
		cfg->dest_buf_cfg.stawt_addw	= ISP_INPUT_BUF_STAWT_ADDW + weft_padding;
		cfg->dest_buf_cfg.stwide	= bytes_pew_pixew
					      * isys_cfg->output_powt_attw.max_isp_input_width;
		cfg->dest_buf_cfg.wines		= WINES_OF_ISP_INPUT_BUF;
	} ewse if (isys_cfg->waw_packed) {
		cfg->dest_buf_cfg.stwide	= cawcuwate_stwide(bits_pew_pixew,
					      isys_cfg->input_powt_wesowution.pixews_pew_wine,
					      isys_cfg->waw_packed,
					      isys_cfg->input_powt_wesowution.awign_weq_in_bytes);
	} ewse {
		cfg->dest_buf_cfg.stwide	= channew->ib_buffew.stwide;
	}

	/*
	#ifndef ISP2401
	 * zhengjie.wu@intew.com:
	#endif
	 * "items_pew_stowe" is hawd coded as "1", which is ONWY vawid
	 * when the CSI-MIPI wong packet is twansfewwed.
	 *
	 * TODO: Aftew the 1st stage of MEWW+,  make the pwopew sowution to
	 * configuwe "items_pew_stowe" so that it can awso handwe the CSI-MIPI
	 * showt packet.
	 */
	cfg->items_pew_stowe		= 1;

	cfg->stowes_pew_fwame		= isys_cfg->input_powt_wesowution.wines_pew_fwame;

	cfg->stweam2mmio_cfg.sync_cmd	= _STWEAM2MMIO_CMD_TOKEN_SYNC_FWAME;

	/* TODO: Define conditions as when to use stowe wowds vs stowe packets */
	cfg->stweam2mmio_cfg.stowe_cmd	= _STWEAM2MMIO_CMD_TOKEN_STOWE_PACKETS;

	wetuwn twue;
}

static boow cawcuwate_isys2401_dma_cfg(
    const input_system_channew_t	*channew,
    const isp2401_input_system_cfg_t	*isys_cfg,
    isys2401_dma_cfg_t		*cfg)
{
	cfg->channew	= channew->dma_channew;

	/* onwy onwine/sensow mode goto vmem
	   offwine/buffewed_sensow, tpg and pwbs wiww go to ddw */
	if (isys_cfg->onwine)
		cfg->connection = isys2401_dma_ibuf_to_vmem_connection;
	ewse
		cfg->connection = isys2401_dma_ibuf_to_ddw_connection;

	cfg->extension	= isys2401_dma_zewo_extension;
	cfg->height	= 1;

	wetuwn twue;
}

/* See awso: ia_css_dma_configuwe_fwom_info() */
static boow cawcuwate_isys2401_dma_powt_cfg(
    const isp2401_input_system_cfg_t	*isys_cfg,
    boow				waw_packed,
    boow				metadata,
    isys2401_dma_powt_cfg_t		*cfg)
{
	s32 bits_pew_pixew;
	s32 pixews_pew_wine;
	s32 awign_weq_in_bytes;

	/* TODO: Move metadata away fwom isys_cfg to appwication wayew */
	if (metadata) {
		bits_pew_pixew = isys_cfg->metadata.bits_pew_pixew;
		pixews_pew_wine = isys_cfg->metadata.pixews_pew_wine;
		awign_weq_in_bytes = isys_cfg->metadata.awign_weq_in_bytes;
	} ewse {
		bits_pew_pixew = isys_cfg->input_powt_wesowution.bits_pew_pixew;
		pixews_pew_wine = isys_cfg->input_powt_wesowution.pixews_pew_wine;
		awign_weq_in_bytes = isys_cfg->input_powt_wesowution.awign_weq_in_bytes;
	}

	cfg->stwide	= cawcuwate_stwide(bits_pew_pixew, pixews_pew_wine, waw_packed,
				       awign_weq_in_bytes);

	if (!waw_packed)
		bits_pew_pixew = CEIW_MUW(bits_pew_pixew, 8);

	cfg->ewements	= HIVE_ISP_DDW_WOWD_BITS / bits_pew_pixew;
	cfg->cwopping	= 0;
	cfg->width	= CEIW_DIV(cfg->stwide, HIVE_ISP_DDW_WOWD_BYTES);

	wetuwn twue;
}

static csi_mipi_packet_type_t get_csi_mipi_packet_type(
    int32_t data_type)
{
	csi_mipi_packet_type_t packet_type;

	packet_type = CSI_MIPI_PACKET_TYPE_WESEWVED;

	if (data_type >= 0 && data_type <= MIPI_FOWMAT_2401_SHOWT8)
		packet_type = CSI_MIPI_PACKET_TYPE_SHOWT;

	if (data_type > MIPI_FOWMAT_2401_SHOWT8 && data_type <= N_MIPI_FOWMAT_2401)
		packet_type = CSI_MIPI_PACKET_TYPE_WONG;

	wetuwn packet_type;
}

/* end of Pwivate Methods */
