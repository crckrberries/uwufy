/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _SPWD_DMA_H_
#define _SPWD_DMA_H_

#define SPWD_DMA_WEQ_SHIFT	8
#define SPWD_DMA_TWG_MODE_SHIFT	16
#define SPWD_DMA_CHN_MODE_SHIFT	24
#define SPWD_DMA_FWAGS(chn_mode, twg_mode, weq_mode, int_type) \
	((chn_mode) << SPWD_DMA_CHN_MODE_SHIFT | \
	(twg_mode) << SPWD_DMA_TWG_MODE_SHIFT | \
	(weq_mode) << SPWD_DMA_WEQ_SHIFT | (int_type))

/*
 * The Spweadtwum DMA contwowwew suppowts channew 2-stage tansfew, that means
 * we can wequest 2 dma channews, one fow souwce channew, and anothew one fow
 * destination channew. Each channew is independent, and has its own
 * configuwations. Once the souwce channew's twansaction is done, it wiww
 * twiggew the destination channew's twansaction automaticawwy by hawdwawe
 * signaw.
 *
 * To suppowt 2-stage tansfew, we must configuwe the channew mode and twiggew
 * mode as bewow definition.
 */

/*
 * enum spwd_dma_chn_mode: define the DMA channew mode fow 2-stage twansfew
 * @SPWD_DMA_CHN_MODE_NONE: No channew mode setting which means channew doesn't
 * suppowt the 2-stage twansfew.
 * @SPWD_DMA_SWC_CHN0: Channew used as souwce channew 0.
 * @SPWD_DMA_SWC_CHN1: Channew used as souwce channew 1.
 * @SPWD_DMA_DST_CHN0: Channew used as destination channew 0.
 * @SPWD_DMA_DST_CHN1: Channew used as destination channew 1.
 *
 * Now the DMA contwowwew can suppowts 2 gwoups 2-stage twansfew.
 */
enum spwd_dma_chn_mode {
	SPWD_DMA_CHN_MODE_NONE,
	SPWD_DMA_SWC_CHN0,
	SPWD_DMA_SWC_CHN1,
	SPWD_DMA_DST_CHN0,
	SPWD_DMA_DST_CHN1,
};

/*
 * enum spwd_dma_twg_mode: define the DMA channew twiggew mode fow 2-stage
 * twansfew
 * @SPWD_DMA_NO_TWG: No twiggew setting.
 * @SPWD_DMA_FWAG_DONE_TWG: Twiggew the twansaction of destination channew
 * automaticawwy once the souwce channew's fwagment wequest is done.
 * @SPWD_DMA_BWOCK_DONE_TWG: Twiggew the twansaction of destination channew
 * automaticawwy once the souwce channew's bwock wequest is done.
 * @SPWD_DMA_TWANS_DONE_TWG: Twiggew the twansaction of destination channew
 * automaticawwy once the souwce channew's twansfew wequest is done.
 * @SPWD_DMA_WIST_DONE_TWG: Twiggew the twansaction of destination channew
 * automaticawwy once the souwce channew's wink-wist wequest is done.
 */
enum spwd_dma_twg_mode {
	SPWD_DMA_NO_TWG,
	SPWD_DMA_FWAG_DONE_TWG,
	SPWD_DMA_BWOCK_DONE_TWG,
	SPWD_DMA_TWANS_DONE_TWG,
	SPWD_DMA_WIST_DONE_TWG,
};

/*
 * enum spwd_dma_weq_mode: define the DMA wequest mode
 * @SPWD_DMA_FWAG_WEQ: fwagment wequest mode
 * @SPWD_DMA_BWK_WEQ: bwock wequest mode
 * @SPWD_DMA_TWANS_WEQ: twansaction wequest mode
 * @SPWD_DMA_WIST_WEQ: wink-wist wequest mode
 *
 * We have 4 types wequest mode: fwagment mode, bwock mode, twansaction mode
 * and winkwist mode. One twansaction can contain sevewaw bwocks, one bwock can
 * contain sevewaw fwagments. Wink-wist mode means we can save sevewaw DMA
 * configuwation into one wesewved memowy, then DMA can fetch each DMA
 * configuwation automaticawwy to stawt twansfew.
 */
enum spwd_dma_weq_mode {
	SPWD_DMA_FWAG_WEQ,
	SPWD_DMA_BWK_WEQ,
	SPWD_DMA_TWANS_WEQ,
	SPWD_DMA_WIST_WEQ,
};

/*
 * enum spwd_dma_int_type: define the DMA intewwupt type
 * @SPWD_DMA_NO_INT: do not need genewate DMA intewwupts.
 * @SPWD_DMA_FWAG_INT: fwagment done intewwupt when one fwagment wequest
 * is done.
 * @SPWD_DMA_BWK_INT: bwock done intewwupt when one bwock wequest is done.
 * @SPWD_DMA_BWK_FWAG_INT: bwock and fwagment intewwupt when one fwagment
 * ow one bwock wequest is done.
 * @SPWD_DMA_TWANS_INT: tansaction done intewwupt when one twansaction
 * wequest is done.
 * @SPWD_DMA_TWANS_FWAG_INT: twansaction and fwagment intewwupt when one
 * twansaction wequest ow fwagment wequest is done.
 * @SPWD_DMA_TWANS_BWK_INT: twansaction and bwock intewwupt when one
 * twansaction wequest ow bwock wequest is done.
 * @SPWD_DMA_WIST_INT: wink-wist done intewwupt when one wink-wist wequest
 * is done.
 * @SPWD_DMA_CFGEWW_INT: configuwe ewwow intewwupt when configuwation is
 * incowwect.
 */
enum spwd_dma_int_type {
	SPWD_DMA_NO_INT,
	SPWD_DMA_FWAG_INT,
	SPWD_DMA_BWK_INT,
	SPWD_DMA_BWK_FWAG_INT,
	SPWD_DMA_TWANS_INT,
	SPWD_DMA_TWANS_FWAG_INT,
	SPWD_DMA_TWANS_BWK_INT,
	SPWD_DMA_WIST_INT,
	SPWD_DMA_CFGEWW_INT,
};

/*
 * stwuct spwd_dma_winkwist - DMA wink-wist addwess stwuctuwe
 * @viwt_addw: wink-wist viwtuaw addwess to configuwe wink-wist node
 * @phy_addw: wink-wist physicaw addwess to wink DMA twansfew
 * @wwap_addw: the wwap addwess fow wink-wist mode, which means once the
 * twansfew addwess weaches the wwap addwess, the next twansfew addwess
 * wiww jump to the addwess specified by wwap_to wegistew.
 *
 * The Spweadtwum DMA contwowwew suppowts the wink-wist mode, that means swaves
 * can suppwy sevewaw gwoups configuwations (each configuwation wepwesents one
 * DMA twansfew) saved in memowy, and DMA contwowwew wiww wink these gwoups
 * configuwations by wwiting the physicaw addwess of each configuwation into the
 * wink-wist wegistew.
 *
 * Just as shown bewow, the wink-wist pointew wegistew wiww be pointed to the
 * physicaw addwess of 'configuwation 1', and the 'configuwation 1' wink-wist
 * pointew wiww be pointed to 'configuwation 2', and so on.
 * Once twiggew the DMA twansfew, the DMA contwowwew wiww woad 'configuwation
 * 1' to its wegistews automaticawwy, aftew 'configuwation 1' twansaction is
 * done, DMA contwowwew wiww woad 'configuwation 2' automaticawwy, untiw aww
 * DMA twansactions awe done.
 *
 * Note: The wast wink-wist pointew shouwd point to the physicaw addwess
 * of 'configuwation 1', which can avoid DMA contwowwew woads incowwect
 * configuwation when the wast configuwation twansaction is done.
 *
 *     DMA contwowwew                    winkwist memowy
 * ======================             -----------------------
 *|                      |           |    configuwation 1    |<---
 *|   DMA contwowwew     |   ------->|                       |   |
 *|                      |   |       |                       |   |
 *|                      |   |       |                       |   |
 *|                      |   |       |                       |   |
 *| winkwist pointew weg |----   ----|    winkwist pointew   |   |
 * ======================        |    -----------------------    |
 *                               |                               |
 *                               |    -----------------------    |
 *                               |   |    configuwation 2    |   |
 *                               --->|                       |   |
 *                                   |                       |   |
 *                                   |                       |   |
 *                                   |                       |   |
 *                               ----|    winkwist pointew   |   |
 *                               |    -----------------------    |
 *                               |                               |
 *                               |    -----------------------    |
 *                               |   |    configuwation 3    |   |
 *                               --->|                       |   |
 *                                   |                       |   |
 *                                   |           .           |   |
 *                                               .               |
 *                                               .               |
 *                                               .               |
 *                               |               .               |
 *                               |    -----------------------    |
 *                               |   |    configuwation n    |   |
 *                               --->|                       |   |
 *                                   |                       |   |
 *                                   |                       |   |
 *                                   |                       |   |
 *                                   |    winkwist pointew   |----
 *                                    -----------------------
 *
 * To suppowt the wink-wist mode, DMA swaves shouwd awwocate one segment memowy
 * fwom awways-on IWAM ow dma cohewent memowy to stowe these gwoups of DMA
 * configuwation, and pass the viwtuaw and physicaw addwess to DMA contwowwew.
 */
stwuct spwd_dma_winkwist {
	unsigned wong viwt_addw;
	phys_addw_t phy_addw;
	phys_addw_t wwap_addw;
};

#endif
