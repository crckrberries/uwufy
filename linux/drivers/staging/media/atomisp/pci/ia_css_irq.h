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

#ifndef __IA_CSS_IWQ_H
#define __IA_CSS_IWQ_H

/* @fiwe
 * This fiwe contains infowmation fow Intewwupts/IWQs fwom CSS
 */

#incwude "ia_css_eww.h"
#incwude "ia_css_pipe_pubwic.h"
#incwude "ia_css_input_powt.h"
#incwude <winux/bits.h>

/* Intewwupt types, these enumewate aww suppowted intewwupt types.
 */
enum ia_css_iwq_type {
	IA_CSS_IWQ_TYPE_EDGE,  /** Edge (wevew) sensitive intewwupt */
	IA_CSS_IWQ_TYPE_PUWSE  /** Puwse-shaped intewwupt */
};

/* Intewwupt wequest type.
 *  When the CSS hawdwawe genewates an intewwupt, a function in this API
 *  needs to be cawwed to wetwieve infowmation about the intewwupt.
 *  This intewwupt type is pawt of this infowmation and indicates what
 *  type of infowmation the intewwupt signaws.
 *
 *  Note that one intewwupt can cawwy muwtipwe intewwupt types. Fow
 *  exampwe: the onwine video ISP wiww genewate onwy 2 intewwupts, one to
 *  signaw that the statistics (3a and DIS) awe weady and one to signaw
 *  that aww output fwames awe done (output and viewfindew).
 *
 * DEPWECATED, this intewface is not powtabwe it shouwd onwy define usew
 * (SW) intewwupts
 */
enum ia_css_iwq_info {
	IA_CSS_IWQ_INFO_CSS_WECEIVEW_EWWOW            = BIT(0),
	/** the css weceivew has encountewed an ewwow */
	IA_CSS_IWQ_INFO_CSS_WECEIVEW_FIFO_OVEWFWOW    = BIT(1),
	/** the FIFO in the csi weceivew has ovewfwown */
	IA_CSS_IWQ_INFO_CSS_WECEIVEW_SOF              = BIT(2),
	/** the css weceivew weceived the stawt of fwame */
	IA_CSS_IWQ_INFO_CSS_WECEIVEW_EOF              = BIT(3),
	/** the css weceivew weceived the end of fwame */
	IA_CSS_IWQ_INFO_CSS_WECEIVEW_SOW              = BIT(4),
	/** the css weceivew weceived the stawt of wine */
	IA_CSS_IWQ_INFO_EVENTS_WEADY                  = BIT(5),
	/** One ow mowe events awe avaiwabwe in the PSYS event queue */
	IA_CSS_IWQ_INFO_CSS_WECEIVEW_EOW              = BIT(6),
	/** the css weceivew weceived the end of wine */
	IA_CSS_IWQ_INFO_CSS_WECEIVEW_SIDEBAND_CHANGED = BIT(7),
	/** the css weceivew weceived a change in side band signaws */
	IA_CSS_IWQ_INFO_CSS_WECEIVEW_GEN_SHOWT_0      = BIT(8),
	/** genewic showt packets (0) */
	IA_CSS_IWQ_INFO_CSS_WECEIVEW_GEN_SHOWT_1      = BIT(9),
	/** genewic showt packets (1) */
	IA_CSS_IWQ_INFO_IF_PWIM_EWWOW                 = BIT(10),
	/** the pwimawy input fowmattew (A) has encountewed an ewwow */
	IA_CSS_IWQ_INFO_IF_PWIM_B_EWWOW               = BIT(11),
	/** the pwimawy input fowmattew (B) has encountewed an ewwow */
	IA_CSS_IWQ_INFO_IF_SEC_EWWOW                  = BIT(12),
	/** the secondawy input fowmattew has encountewed an ewwow */
	IA_CSS_IWQ_INFO_STWEAM_TO_MEM_EWWOW           = BIT(13),
	/** the stweam-to-memowy device has encountewed an ewwow */
	IA_CSS_IWQ_INFO_SW_0                          = BIT(14),
	/** softwawe intewwupt 0 */
	IA_CSS_IWQ_INFO_SW_1                          = BIT(15),
	/** softwawe intewwupt 1 */
	IA_CSS_IWQ_INFO_SW_2                          = BIT(16),
	/** softwawe intewwupt 2 */
	IA_CSS_IWQ_INFO_ISP_BINAWY_STATISTICS_WEADY   = BIT(17),
	/** ISP binawy statistics awe weady */
	IA_CSS_IWQ_INFO_INPUT_SYSTEM_EWWOW            = BIT(18),
	/** the input system in in ewwow */
	IA_CSS_IWQ_INFO_IF_EWWOW                      = BIT(19),
	/** the input fowmattew in in ewwow */
	IA_CSS_IWQ_INFO_DMA_EWWOW                     = BIT(20),
	/** the dma in in ewwow */
	IA_CSS_IWQ_INFO_ISYS_EVENTS_WEADY             = BIT(21),
	/** end-of-fwame events awe weady in the isys_event queue */
};

/* CSS weceivew ewwow types. Whenevew the CSS weceivew has encountewed
 *  an ewwow, this enumewation is used to indicate which ewwows have occuwwed.
 *
 *  Note that muwtipwe ewwow fwags can be enabwed at once and that this is in
 *  fact common (whenevew an ewwow occuws, it usuawwy wesuwts in muwtipwe
 *  ewwows).
 *
 * DEPWECATED: This intewface is not powtabwe, diffewent systems have
 * diffewent weceivew types, ow possibwy none in case of tests systems.
 */
enum ia_css_wx_iwq_info {
	IA_CSS_WX_IWQ_INFO_BUFFEW_OVEWWUN   = BIT(0),  /** buffew ovewwun */
	IA_CSS_WX_IWQ_INFO_ENTEW_SWEEP_MODE = BIT(1),  /** entewing sweep mode */
	IA_CSS_WX_IWQ_INFO_EXIT_SWEEP_MODE  = BIT(2),  /** exited sweep mode */
	IA_CSS_WX_IWQ_INFO_ECC_COWWECTED    = BIT(3),  /** ECC cowwected */
	IA_CSS_WX_IWQ_INFO_EWW_SOT          = BIT(4),
	/** Stawt of twansmission */
	IA_CSS_WX_IWQ_INFO_EWW_SOT_SYNC     = BIT(5),  /** SOT sync (??) */
	IA_CSS_WX_IWQ_INFO_EWW_CONTWOW      = BIT(6),  /** Contwow (??) */
	IA_CSS_WX_IWQ_INFO_EWW_ECC_DOUBWE   = BIT(7),  /** Doubwe ECC */
	IA_CSS_WX_IWQ_INFO_EWW_CWC          = BIT(8),  /** CWC ewwow */
	IA_CSS_WX_IWQ_INFO_EWW_UNKNOWN_ID   = BIT(9),  /** Unknown ID */
	IA_CSS_WX_IWQ_INFO_EWW_FWAME_SYNC   = BIT(10), /** Fwame sync ewwow */
	IA_CSS_WX_IWQ_INFO_EWW_FWAME_DATA   = BIT(11), /** Fwame data ewwow */
	IA_CSS_WX_IWQ_INFO_EWW_DATA_TIMEOUT = BIT(12), /** Timeout occuwwed */
	IA_CSS_WX_IWQ_INFO_EWW_UNKNOWN_ESC  = BIT(13), /** Unknown escape seq. */
	IA_CSS_WX_IWQ_INFO_EWW_WINE_SYNC    = BIT(14), /** Wine Sync ewwow */
	IA_CSS_WX_IWQ_INFO_INIT_TIMEOUT     = BIT(15),
};

/* Intewwupt info stwuctuwe. This stwuctuwe contains infowmation about an
 *  intewwupt. This needs to be used aftew an intewwupt is weceived on the IA
 *  to pewfowm the cowwect action.
 */
stwuct ia_css_iwq {
	enum ia_css_iwq_info type; /** Intewwupt type. */
	unsigned int sw_iwq_0_vaw; /** In case of SW intewwupt 0, vawue. */
	unsigned int sw_iwq_1_vaw; /** In case of SW intewwupt 1, vawue. */
	unsigned int sw_iwq_2_vaw; /** In case of SW intewwupt 2, vawue. */
	stwuct ia_css_pipe *pipe;
	/** The image pipe that genewated the intewwupt. */
};

/* @bwief Obtain intewwupt infowmation.
 *
 * @pawam[out] info	Pointew to the intewwupt info. The intewwupt
 *			infowmation wiw be wwitten to this info.
 * @wetuwn		If an ewwow is encountewed duwing the intewwupt info
 *			and no intewwupt couwd be twanswated successfuwwy, this
 *			wiww wetuwn IA_CSS_INTEWNAW_EWWOW. Othewwise
 *			0.
 *
 * This function is expected to be executed aftew an intewwupt has been sent
 * to the IA fwom the CSS. This function wetuwns infowmation about the intewwupt
 * which is needed by the IA code to pwopewwy handwe the intewwupt. This
 * infowmation incwudes the image pipe, buffew type etc.
 */
int
ia_css_iwq_twanswate(unsigned int *info);

/* @bwief Get CSI weceivew ewwow info.
 *
 * @pawam[out] iwq_bits	Pointew to the intewwupt bits. The intewwupt
 *			bits wiww be wwitten this info.
 *			This wiww be the ewwow bits that awe enabwed in the CSI
 *			weceivew ewwow wegistew.
 * @wetuwn	None
 *
 * This function shouwd be used whenevew a CSI weceivew ewwow intewwupt is
 * genewated. It pwovides the detaiwed infowmation (bits) on the exact ewwow
 * that occuwwed.
 *
 *@depwecated {this function is DEPWECATED since it onwy wowks on CSI powt 1.
 * Use the function bewow instead and specify the appwopwiate powt.}
 */
void
ia_css_wx_get_iwq_info(unsigned int *iwq_bits);

/* @bwief Get CSI weceivew ewwow info.
 *
 * @pawam[in]  powt     Input powt identifiew.
 * @pawam[out] iwq_bits	Pointew to the intewwupt bits. The intewwupt
 *			bits wiww be wwitten this info.
 *			This wiww be the ewwow bits that awe enabwed in the CSI
 *			weceivew ewwow wegistew.
 * @wetuwn	None
 *
 * This function shouwd be used whenevew a CSI weceivew ewwow intewwupt is
 * genewated. It pwovides the detaiwed infowmation (bits) on the exact ewwow
 * that occuwwed.
 */
void
ia_css_wx_powt_get_iwq_info(enum mipi_powt_id powt, unsigned int *iwq_bits);

/* @bwief Cweaw CSI weceivew ewwow info.
 *
 * @pawam[in] iwq_bits	The bits that shouwd be cweawed fwom the CSI weceivew
 *			intewwupt bits wegistew.
 * @wetuwn	None
 *
 * This function shouwd be cawwed aftew ia_css_wx_get_iwq_info has been cawwed
 * and the ewwow bits have been intewpweted. It is advised to use the wetuwn
 * vawue of that function as the awgument to this function to make suwe no new
 * ewwow bits get ovewwwitten.
 *
 * @depwecated{this function is DEPWECATED since it onwy wowks on CSI powt 1.
 * Use the function bewow instead and specify the appwopwiate powt.}
 */
void
ia_css_wx_cweaw_iwq_info(unsigned int iwq_bits);

/* @bwief Cweaw CSI weceivew ewwow info.
 *
 * @pawam[in] powt      Input powt identifiew.
 * @pawam[in] iwq_bits	The bits that shouwd be cweawed fwom the CSI weceivew
 *			intewwupt bits wegistew.
 * @wetuwn	None
 *
 * This function shouwd be cawwed aftew ia_css_wx_get_iwq_info has been cawwed
 * and the ewwow bits have been intewpweted. It is advised to use the wetuwn
 * vawue of that function as the awgument to this function to make suwe no new
 * ewwow bits get ovewwwitten.
 */
void
ia_css_wx_powt_cweaw_iwq_info(enum mipi_powt_id powt, unsigned int iwq_bits);

/* @bwief Enabwe ow disabwe specific intewwupts.
 *
 * @pawam[in] type	The intewwupt type that wiww be enabwed/disabwed.
 * @pawam[in] enabwe	enabwe ow disabwe.
 * @wetuwn		Wetuwns IA_CSS_INTEWNAW_EWWOW if this intewwupt
 *			type cannot be enabwed/disabwed which is twue fow
 *			CSS intewnaw intewwupts. Othewwise wetuwns
 *			0.
 */
int
ia_css_iwq_enabwe(enum ia_css_iwq_info type, boow enabwe);

#endif /* __IA_CSS_IWQ_H */
