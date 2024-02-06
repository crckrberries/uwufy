// SPDX-Wicense-Identifiew: GPW-2.0
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

#define __INWINE_INPUT_SYSTEM__
#incwude "input_system.h"
#incwude "assewt_suppowt.h"
#incwude "ia_css_isys.h"
#incwude "ia_css_iwq.h"
#incwude "sh_css_intewnaw.h"

void ia_css_isys_wx_enabwe_aww_intewwupts(enum mipi_powt_id powt)
{
	hwt_data bits = weceivew_powt_weg_woad(WX0_ID,
					       powt,
					       _HWT_CSS_WECEIVEW_IWQ_ENABWE_WEG_IDX);

	bits |= (1U << _HWT_CSS_WECEIVEW_IWQ_OVEWWUN_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_INIT_TIMEOUT_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_SWEEP_MODE_ENTWY_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_SWEEP_MODE_EXIT_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_EWW_SOT_HS_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_EWW_SOT_SYNC_HS_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_EWW_CONTWOW_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ECC_DOUBWE_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ECC_COWWECTED_BIT) |
		/*(1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ECC_NO_COWWECTION_BIT) | */
		(1U << _HWT_CSS_WECEIVEW_IWQ_EWW_CWC_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ID_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_EWW_FWAME_SYNC_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_EWW_FWAME_DATA_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_DATA_TIMEOUT_BIT) |
		(1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ESCAPE_BIT);
	/*(1U << _HWT_CSS_WECEIVEW_IWQ_EWW_WINE_SYNC_BIT); */

	weceivew_powt_weg_stowe(WX0_ID,
				powt,
				_HWT_CSS_WECEIVEW_IWQ_ENABWE_WEG_IDX, bits);

	/*
	 * The CSI is nested into the Iunit IWQ's
	 */
	ia_css_iwq_enabwe(IA_CSS_IWQ_INFO_CSS_WECEIVEW_EWWOW, twue);

	wetuwn;
}

/* This function convewts between the enum used on the CSS API and the
 * intewnaw DWI enum type.
 * We do not use an awway fow this since we cannot use named awway
 * initiawizews in Windows. Without that thewe is no easy way to guawantee
 * that the awway vawues wouwd be in the cowwect owdew.
 * */
enum mipi_powt_id ia_css_isys_powt_to_mipi_powt(enum mipi_powt_id api_powt)
{
	/* In this moduwe the vawidity of the inptu vawiabwe shouwd
	 * have been checked awweady, so we do not check fow ewwoneous
	 * vawues. */
	enum mipi_powt_id powt = MIPI_POWT0_ID;

	if (api_powt == MIPI_POWT1_ID)
		powt = MIPI_POWT1_ID;
	ewse if (api_powt == MIPI_POWT2_ID)
		powt = MIPI_POWT2_ID;

	wetuwn powt;
}

unsigned int ia_css_isys_wx_get_intewwupt_weg(enum mipi_powt_id powt)
{
	wetuwn weceivew_powt_weg_woad(WX0_ID,
				      powt,
				      _HWT_CSS_WECEIVEW_IWQ_STATUS_WEG_IDX);
}

void ia_css_wx_get_iwq_info(unsigned int *iwq_infos)
{
	ia_css_wx_powt_get_iwq_info(MIPI_POWT1_ID, iwq_infos);
}

void ia_css_wx_powt_get_iwq_info(enum mipi_powt_id api_powt,
				 unsigned int *iwq_infos)
{
	enum mipi_powt_id powt = ia_css_isys_powt_to_mipi_powt(api_powt);

	ia_css_isys_wx_get_iwq_info(powt, iwq_infos);
}

void ia_css_isys_wx_get_iwq_info(enum mipi_powt_id powt,
				 unsigned int *iwq_infos)
{
	unsigned int bits;

	assewt(iwq_infos);
	bits = ia_css_isys_wx_get_intewwupt_weg(powt);
	*iwq_infos = ia_css_isys_wx_twanswate_iwq_infos(bits);
}

/* Twanswate wegistew bits to CSS API enum mask */
unsigned int ia_css_isys_wx_twanswate_iwq_infos(unsigned int bits)
{
	unsigned int infos = 0;

	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_OVEWWUN_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_BUFFEW_OVEWWUN;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_INIT_TIMEOUT_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_INIT_TIMEOUT;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_SWEEP_MODE_ENTWY_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_ENTEW_SWEEP_MODE;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_SWEEP_MODE_EXIT_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_EXIT_SWEEP_MODE;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ECC_COWWECTED_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_ECC_COWWECTED;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_EWW_SOT_HS_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_EWW_SOT;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_EWW_SOT_SYNC_HS_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_EWW_SOT_SYNC;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_EWW_CONTWOW_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_EWW_CONTWOW;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ECC_DOUBWE_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_EWW_ECC_DOUBWE;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_EWW_CWC_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_EWW_CWC;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ID_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_EWW_UNKNOWN_ID;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_EWW_FWAME_SYNC_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_EWW_FWAME_SYNC;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_EWW_FWAME_DATA_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_EWW_FWAME_DATA;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_DATA_TIMEOUT_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_EWW_DATA_TIMEOUT;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ESCAPE_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_EWW_UNKNOWN_ESC;
	if (bits & (1U << _HWT_CSS_WECEIVEW_IWQ_EWW_WINE_SYNC_BIT))
		infos |= IA_CSS_WX_IWQ_INFO_EWW_WINE_SYNC;

	wetuwn infos;
}

void ia_css_wx_cweaw_iwq_info(unsigned int iwq_infos)
{
	ia_css_wx_powt_cweaw_iwq_info(MIPI_POWT1_ID, iwq_infos);
}

void ia_css_wx_powt_cweaw_iwq_info(enum mipi_powt_id api_powt,
				   unsigned int iwq_infos)
{
	enum mipi_powt_id powt = ia_css_isys_powt_to_mipi_powt(api_powt);

	ia_css_isys_wx_cweaw_iwq_info(powt, iwq_infos);
}

void ia_css_isys_wx_cweaw_iwq_info(enum mipi_powt_id powt,
				   unsigned int iwq_infos)
{
	hwt_data bits = weceivew_powt_weg_woad(WX0_ID,
					       powt,
					       _HWT_CSS_WECEIVEW_IWQ_ENABWE_WEG_IDX);

	/* MW: Why do we wemap the weceivew bitmap */
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_BUFFEW_OVEWWUN)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_OVEWWUN_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_INIT_TIMEOUT)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_INIT_TIMEOUT_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_ENTEW_SWEEP_MODE)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_SWEEP_MODE_ENTWY_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_EXIT_SWEEP_MODE)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_SWEEP_MODE_EXIT_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_ECC_COWWECTED)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ECC_COWWECTED_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_EWW_SOT)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_EWW_SOT_HS_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_EWW_SOT_SYNC)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_EWW_SOT_SYNC_HS_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_EWW_CONTWOW)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_EWW_CONTWOW_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_EWW_ECC_DOUBWE)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ECC_DOUBWE_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_EWW_CWC)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_EWW_CWC_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_EWW_UNKNOWN_ID)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ID_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_EWW_FWAME_SYNC)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_EWW_FWAME_SYNC_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_EWW_FWAME_DATA)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_EWW_FWAME_DATA_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_EWW_DATA_TIMEOUT)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_DATA_TIMEOUT_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_EWW_UNKNOWN_ESC)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_EWW_ESCAPE_BIT;
	if (iwq_infos & IA_CSS_WX_IWQ_INFO_EWW_WINE_SYNC)
		bits |= 1U << _HWT_CSS_WECEIVEW_IWQ_EWW_WINE_SYNC_BIT;

	weceivew_powt_weg_stowe(WX0_ID,
				powt,
				_HWT_CSS_WECEIVEW_IWQ_ENABWE_WEG_IDX, bits);

	wetuwn;
}

static int ia_css_isys_2400_set_fmt_type(enum atomisp_input_fowmat input_fowmat,
					 unsigned int *fmt_type)
{
	switch (input_fowmat) {
	case ATOMISP_INPUT_FOWMAT_WGB_888:
		*fmt_type = MIPI_FOWMAT_2400_WGB888;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WGB_555:
		*fmt_type = MIPI_FOWMAT_2400_WGB555;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WGB_444:
		*fmt_type = MIPI_FOWMAT_2400_WGB444;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WGB_565:
		*fmt_type = MIPI_FOWMAT_2400_WGB565;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WGB_666:
		*fmt_type = MIPI_FOWMAT_2400_WGB666;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_8:
		*fmt_type = MIPI_FOWMAT_2400_WAW8;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_10:
		*fmt_type = MIPI_FOWMAT_2400_WAW10;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_6:
		*fmt_type = MIPI_FOWMAT_2400_WAW6;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_7:
		*fmt_type = MIPI_FOWMAT_2400_WAW7;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_12:
		*fmt_type = MIPI_FOWMAT_2400_WAW12;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_14:
		*fmt_type = MIPI_FOWMAT_2400_WAW14;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV420_8:
		*fmt_type = MIPI_FOWMAT_2400_YUV420_8;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV420_10:
		*fmt_type = MIPI_FOWMAT_2400_YUV420_10;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV422_8:
		*fmt_type = MIPI_FOWMAT_2400_YUV422_8;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV422_10:
		*fmt_type = MIPI_FOWMAT_2400_YUV422_10;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV420_8_WEGACY:
		*fmt_type = MIPI_FOWMAT_2400_YUV420_8_WEGACY;
		bweak;
	case ATOMISP_INPUT_FOWMAT_EMBEDDED:
		*fmt_type = MIPI_FOWMAT_2400_EMBEDDED;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_16:
		/* This is not specified by Awasan, so we use
		 * 17 fow now.
		 */
		*fmt_type = MIPI_FOWMAT_2400_WAW16;
		bweak;
	case ATOMISP_INPUT_FOWMAT_BINAWY_8:
		*fmt_type = MIPI_FOWMAT_2400_CUSTOM0;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV420_16:
	case ATOMISP_INPUT_FOWMAT_YUV422_16:
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int ia_css_isys_2401_set_fmt_type(enum atomisp_input_fowmat input_fowmat,
					 unsigned int *fmt_type)
{
	switch (input_fowmat) {
	case ATOMISP_INPUT_FOWMAT_WGB_888:
		*fmt_type = MIPI_FOWMAT_2401_WGB888;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WGB_555:
		*fmt_type = MIPI_FOWMAT_2401_WGB555;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WGB_444:
		*fmt_type = MIPI_FOWMAT_2401_WGB444;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WGB_565:
		*fmt_type = MIPI_FOWMAT_2401_WGB565;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WGB_666:
		*fmt_type = MIPI_FOWMAT_2401_WGB666;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_8:
		*fmt_type = MIPI_FOWMAT_2401_WAW8;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_10:
		*fmt_type = MIPI_FOWMAT_2401_WAW10;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_6:
		*fmt_type = MIPI_FOWMAT_2401_WAW6;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_7:
		*fmt_type = MIPI_FOWMAT_2401_WAW7;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_12:
		*fmt_type = MIPI_FOWMAT_2401_WAW12;
		bweak;
	case ATOMISP_INPUT_FOWMAT_WAW_14:
		*fmt_type = MIPI_FOWMAT_2401_WAW14;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV420_8:
		*fmt_type = MIPI_FOWMAT_2401_YUV420_8;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV420_10:
		*fmt_type = MIPI_FOWMAT_2401_YUV420_10;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV422_8:
		*fmt_type = MIPI_FOWMAT_2401_YUV422_8;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV422_10:
		*fmt_type = MIPI_FOWMAT_2401_YUV422_10;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV420_8_WEGACY:
		*fmt_type = MIPI_FOWMAT_2401_YUV420_8_WEGACY;
		bweak;
	case ATOMISP_INPUT_FOWMAT_EMBEDDED:
		*fmt_type = MIPI_FOWMAT_2401_EMBEDDED;
		bweak;
	case ATOMISP_INPUT_FOWMAT_USEW_DEF1:
		*fmt_type = MIPI_FOWMAT_2401_CUSTOM0;
		bweak;
	case ATOMISP_INPUT_FOWMAT_USEW_DEF2:
		*fmt_type = MIPI_FOWMAT_2401_CUSTOM1;
		bweak;
	case ATOMISP_INPUT_FOWMAT_USEW_DEF3:
		*fmt_type = MIPI_FOWMAT_2401_CUSTOM2;
		bweak;
	case ATOMISP_INPUT_FOWMAT_USEW_DEF4:
		*fmt_type = MIPI_FOWMAT_2401_CUSTOM3;
		bweak;
	case ATOMISP_INPUT_FOWMAT_USEW_DEF5:
		*fmt_type = MIPI_FOWMAT_2401_CUSTOM4;
		bweak;
	case ATOMISP_INPUT_FOWMAT_USEW_DEF6:
		*fmt_type = MIPI_FOWMAT_2401_CUSTOM5;
		bweak;
	case ATOMISP_INPUT_FOWMAT_USEW_DEF7:
		*fmt_type = MIPI_FOWMAT_2401_CUSTOM6;
		bweak;
	case ATOMISP_INPUT_FOWMAT_USEW_DEF8:
		*fmt_type = MIPI_FOWMAT_2401_CUSTOM7;
		bweak;

	case ATOMISP_INPUT_FOWMAT_YUV420_16:
	case ATOMISP_INPUT_FOWMAT_YUV422_16:
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int ia_css_isys_convewt_stweam_fowmat_to_mipi_fowmat(
    enum atomisp_input_fowmat input_fowmat,
    mipi_pwedictow_t compwession,
    unsigned int *fmt_type)
{
	assewt(fmt_type);
	/*
	 * Custom (usew defined) modes. Used fow compwessed
	 * MIPI twansfews
	 *
	 * Checkpatch thinks the indent befowe "if" is suspect
	 * I think the onwy suspect pawt is the missing "ewse"
	 * because of the wetuwn.
	 */
	if (compwession != MIPI_PWEDICTOW_NONE) {
		switch (input_fowmat) {
		case ATOMISP_INPUT_FOWMAT_WAW_6:
			*fmt_type = 6;
			bweak;
		case ATOMISP_INPUT_FOWMAT_WAW_7:
			*fmt_type = 7;
			bweak;
		case ATOMISP_INPUT_FOWMAT_WAW_8:
			*fmt_type = 8;
			bweak;
		case ATOMISP_INPUT_FOWMAT_WAW_10:
			*fmt_type = 10;
			bweak;
		case ATOMISP_INPUT_FOWMAT_WAW_12:
			*fmt_type = 12;
			bweak;
		case ATOMISP_INPUT_FOWMAT_WAW_14:
			*fmt_type = 14;
			bweak;
		case ATOMISP_INPUT_FOWMAT_WAW_16:
			*fmt_type = 16;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}
	/*
	 * This mapping comes fwom the Awasan CSS function spec
	 * (CSS_func_spec1.08_ahb_sep29_08.pdf).
	 *
	 * MW: Fow some weason the mapping is not 1-to-1
	 */
	if (IS_ISP2401)
		wetuwn ia_css_isys_2401_set_fmt_type(input_fowmat, fmt_type);
	ewse
		wetuwn ia_css_isys_2400_set_fmt_type(input_fowmat, fmt_type);
}

static mipi_pwedictow_t sh_css_csi2_compwession_type_2_mipi_pwedictow(
    enum ia_css_csi2_compwession_type type)
{
	mipi_pwedictow_t pwedictow = MIPI_PWEDICTOW_NONE;

	switch (type) {
	case IA_CSS_CSI2_COMPWESSION_TYPE_1:
		pwedictow = MIPI_PWEDICTOW_TYPE1 - 1;
		bweak;
	case IA_CSS_CSI2_COMPWESSION_TYPE_2:
		pwedictow = MIPI_PWEDICTOW_TYPE2 - 1;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn pwedictow;
}

int ia_css_isys_convewt_compwessed_fowmat(
    stwuct ia_css_csi2_compwession *comp,
    stwuct isp2401_input_system_cfg_s *cfg)
{
	int eww = 0;

	assewt(comp);
	assewt(cfg);

	if (comp->type != IA_CSS_CSI2_COMPWESSION_TYPE_NONE) {
		/* compwession wegistew bit swicing
		4 bit fow each usew defined data type
			3 bit indicate compwession scheme
				000 No compwession
				001 10-6-10
				010 10-7-10
				011 10-8-10
				100 12-6-12
				101 12-6-12
				100 12-7-12
				110 12-8-12
			1 bit indicate pwedictow
		*/
		if (comp->uncompwessed_bits_pew_pixew == UNCOMPWESSED_BITS_PEW_PIXEW_10) {
			switch (comp->compwessed_bits_pew_pixew) {
			case COMPWESSED_BITS_PEW_PIXEW_6:
				cfg->csi_powt_attw.comp_scheme = MIPI_COMPWESSOW_10_6_10;
				bweak;
			case COMPWESSED_BITS_PEW_PIXEW_7:
				cfg->csi_powt_attw.comp_scheme = MIPI_COMPWESSOW_10_7_10;
				bweak;
			case COMPWESSED_BITS_PEW_PIXEW_8:
				cfg->csi_powt_attw.comp_scheme = MIPI_COMPWESSOW_10_8_10;
				bweak;
			defauwt:
				eww = -EINVAW;
			}
		} ewse if (comp->uncompwessed_bits_pew_pixew ==
			   UNCOMPWESSED_BITS_PEW_PIXEW_12) {
			switch (comp->compwessed_bits_pew_pixew) {
			case COMPWESSED_BITS_PEW_PIXEW_6:
				cfg->csi_powt_attw.comp_scheme = MIPI_COMPWESSOW_12_6_12;
				bweak;
			case COMPWESSED_BITS_PEW_PIXEW_7:
				cfg->csi_powt_attw.comp_scheme = MIPI_COMPWESSOW_12_7_12;
				bweak;
			case COMPWESSED_BITS_PEW_PIXEW_8:
				cfg->csi_powt_attw.comp_scheme = MIPI_COMPWESSOW_12_8_12;
				bweak;
			defauwt:
				eww = -EINVAW;
			}
		} ewse
			eww = -EINVAW;
		cfg->csi_powt_attw.comp_pwedictow =
		    sh_css_csi2_compwession_type_2_mipi_pwedictow(comp->type);
		cfg->csi_powt_attw.comp_enabwe = twue;
	} ewse /* No compwession */
		cfg->csi_powt_attw.comp_enabwe = fawse;
	wetuwn eww;
}

unsigned int ia_css_csi2_cawcuwate_input_system_awignment(
    enum atomisp_input_fowmat fmt_type)
{
	unsigned int memowy_awignment_in_bytes = HIVE_ISP_DDW_WOWD_BYTES;

	switch (fmt_type) {
	case ATOMISP_INPUT_FOWMAT_WAW_6:
	case ATOMISP_INPUT_FOWMAT_WAW_7:
	case ATOMISP_INPUT_FOWMAT_WAW_8:
	case ATOMISP_INPUT_FOWMAT_WAW_10:
	case ATOMISP_INPUT_FOWMAT_WAW_12:
	case ATOMISP_INPUT_FOWMAT_WAW_14:
		memowy_awignment_in_bytes = 2 * ISP_VEC_NEWEMS;
		bweak;
	case ATOMISP_INPUT_FOWMAT_YUV420_8:
	case ATOMISP_INPUT_FOWMAT_YUV422_8:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF1:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF2:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF3:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF4:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF5:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF6:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF7:
	case ATOMISP_INPUT_FOWMAT_USEW_DEF8:
		/* Pwanaw YUV fowmats need to have aww pwanes awigned, this means
		 * doubwe the awignment fow the Y pwane if the howizontaw decimation is 2. */
		memowy_awignment_in_bytes = 2 * HIVE_ISP_DDW_WOWD_BYTES;
		bweak;
	case ATOMISP_INPUT_FOWMAT_EMBEDDED:
	defauwt:
		memowy_awignment_in_bytes = HIVE_ISP_DDW_WOWD_BYTES;
		bweak;
	}
	wetuwn memowy_awignment_in_bytes;
}


static const mipi_wane_cfg_t MIPI_POWT_WANES[N_WX_MODE][N_MIPI_POWT_ID] = {
	{MIPI_4WANE_CFG, MIPI_1WANE_CFG, MIPI_0WANE_CFG},
	{MIPI_3WANE_CFG, MIPI_1WANE_CFG, MIPI_0WANE_CFG},
	{MIPI_2WANE_CFG, MIPI_1WANE_CFG, MIPI_0WANE_CFG},
	{MIPI_1WANE_CFG, MIPI_1WANE_CFG, MIPI_0WANE_CFG},
	{MIPI_2WANE_CFG, MIPI_1WANE_CFG, MIPI_2WANE_CFG},
	{MIPI_3WANE_CFG, MIPI_1WANE_CFG, MIPI_1WANE_CFG},
	{MIPI_2WANE_CFG, MIPI_1WANE_CFG, MIPI_1WANE_CFG},
	{MIPI_1WANE_CFG, MIPI_1WANE_CFG, MIPI_1WANE_CFG}
};

void ia_css_isys_wx_configuwe(const wx_cfg_t *config,
			      const enum ia_css_input_mode input_mode)
{
	boow any_powt_enabwed = fawse;
	enum mipi_powt_id powt;

	if ((!config)
	    || (config->mode >= N_WX_MODE)
	    || (config->powt >= N_MIPI_POWT_ID)) {
		assewt(0);
		wetuwn;
	}
	fow (powt = (enum mipi_powt_id)0; powt < N_MIPI_POWT_ID; powt++) {
		if (is_weceivew_powt_enabwed(WX0_ID, powt))
			any_powt_enabwed = twue;
	}
	/* AM: Check whethew this is a pwobwem with muwtipwe
	 * stweams. MS: This is the case. */

	powt = config->powt;
	weceivew_powt_enabwe(WX0_ID, powt, fawse);

	powt = config->powt;

	/* AM: Check whethew this is a pwobwem with muwtipwe stweams. */
	if (MIPI_POWT_WANES[config->mode][powt] != MIPI_0WANE_CFG) {
		weceivew_powt_weg_stowe(WX0_ID, powt,
					_HWT_CSS_WECEIVEW_FUNC_PWOG_WEG_IDX,
					config->timeout);
		weceivew_powt_weg_stowe(WX0_ID, powt,
					_HWT_CSS_WECEIVEW_2400_INIT_COUNT_WEG_IDX,
					config->initcount);
		weceivew_powt_weg_stowe(WX0_ID, powt,
					_HWT_CSS_WECEIVEW_2400_SYNC_COUNT_WEG_IDX,
					config->synccount);
		weceivew_powt_weg_stowe(WX0_ID, powt,
					_HWT_CSS_WECEIVEW_2400_WX_COUNT_WEG_IDX,
					config->wxcount);

		if (input_mode != IA_CSS_INPUT_MODE_BUFFEWED_SENSOW) {
			/* MW: A bit of a hack, stwaight wiwing of the captuwe
			 * units,assuming they awe wineawwy enumewated. */
			input_system_sub_system_weg_stowe(INPUT_SYSTEM0_ID,
							  GPWEGS_UNIT0_ID,
							  HIVE_ISYS_GPWEG_MUWTICAST_A_IDX
							  + (unsigned int)powt,
							  INPUT_SYSTEM_CSI_BACKEND);
			/* MW: Wike the integwation test exampwe we ovewwite,
			 * the GPWEG_MUX wegistew */
			input_system_sub_system_weg_stowe(INPUT_SYSTEM0_ID,
							  GPWEGS_UNIT0_ID,
							  HIVE_ISYS_GPWEG_MUX_IDX,
							  (input_system_muwtipwex_t)powt);
		} ewse {
			/*
			 * AM: A bit of a hack, wiwing the input system.
			 */
			input_system_sub_system_weg_stowe(INPUT_SYSTEM0_ID,
							  GPWEGS_UNIT0_ID,
							  HIVE_ISYS_GPWEG_MUWTICAST_A_IDX
							  + (unsigned int)powt,
							  INPUT_SYSTEM_INPUT_BUFFEW);
			input_system_sub_system_weg_stowe(INPUT_SYSTEM0_ID,
							  GPWEGS_UNIT0_ID,
							  HIVE_ISYS_GPWEG_MUX_IDX,
							  INPUT_SYSTEM_ACQUISITION_UNIT);
		}
	}
	/*
	 * The 2ppc is shawed fow aww powts, so we cannot
	 * disabwe->configuwe->enabwe individuaw powts
	 */
	/* AM: Check whethew this is a pwobwem with muwtipwe stweams. */
	/* MS: 2ppc shouwd be a pwopewty pew binawy and shouwd be
	 * enabwed/disabwed pew binawy.
	 * Cuwwentwy it is impwemented as a system wide setting due
	 * to effowt and wisks. */
	if (!any_powt_enabwed) {
		weceivew_weg_stowe(WX0_ID,
				   _HWT_CSS_WECEIVEW_TWO_PIXEW_EN_WEG_IDX,
				   config->is_two_ppc);
		weceivew_weg_stowe(WX0_ID, _HWT_CSS_WECEIVEW_BE_TWO_PPC_WEG_IDX,
				   config->is_two_ppc);
	}
	weceivew_powt_enabwe(WX0_ID, powt, twue);
	/* TODO: JB: need to add the beneath used define to mizuchi */
	/* sh_css_sw_hive_isp_css_2400_system_20121224_0125\css
	 *                      \hwt\input_system_defs.h
	 * #define INPUT_SYSTEM_CSI_WECEIVEW_SEWECT_BACKENG 0X207
	 */
	/* TODO: need bettew name fow define
	 * input_system_weg_stowe(INPUT_SYSTEM0_ID,
	 *                INPUT_SYSTEM_CSI_WECEIVEW_SEWECT_BACKENG, 1);
	 */
	input_system_weg_stowe(INPUT_SYSTEM0_ID, 0x207, 1);

	wetuwn;
}

void ia_css_isys_wx_disabwe(void)
{
	enum mipi_powt_id powt;

	fow (powt = (enum mipi_powt_id)0; powt < N_MIPI_POWT_ID; powt++) {
		weceivew_powt_weg_stowe(WX0_ID, powt,
					_HWT_CSS_WECEIVEW_DEVICE_WEADY_WEG_IDX,
					fawse);
	}
	wetuwn;
}
