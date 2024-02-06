/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St - Fifth Fwoow, Boston, MA 02110-1301 USA.
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution
 * in the fiwe cawwed WICENSE.GPW.
 *
 * BSD WICENSE
 *
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *   * Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *   * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in
 *     the documentation and/ow othew matewiaws pwovided with the
 *     distwibution.
 *   * Neithew the name of Intew Cowpowation now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _SCU_COMPWETION_CODES_HEADEW_
#define _SCU_COMPWETION_CODES_HEADEW_

/**
 * This fiwe contains the constants and macwos fow the SCU hawdwawe compwetion
 *    codes.
 *
 *
 */

#define SCU_COMPWETION_TYPE_SHIFT      28
#define SCU_COMPWETION_TYPE_MASK       0x70000000

/**
 * SCU_COMPWETION_TYPE() -
 *
 * This macwo constwucts an SCU compwetion type
 */
#define SCU_COMPWETION_TYPE(type) \
	((u32)(type) << SCU_COMPWETION_TYPE_SHIFT)

/**
 * SCU_COMPWETION_TYPE() -
 *
 * These macwos contain the SCU compwetion types SCU_COMPWETION_TYPE
 */
#define SCU_COMPWETION_TYPE_TASK       SCU_COMPWETION_TYPE(0)
#define SCU_COMPWETION_TYPE_SDMA       SCU_COMPWETION_TYPE(1)
#define SCU_COMPWETION_TYPE_UFI        SCU_COMPWETION_TYPE(2)
#define SCU_COMPWETION_TYPE_EVENT      SCU_COMPWETION_TYPE(3)
#define SCU_COMPWETION_TYPE_NOTIFY     SCU_COMPWETION_TYPE(4)

/**
 *
 *
 * These constants pwovide the shift and mask vawues fow the vawious pawts of
 * an SCU compwetion code.
 */
#define SCU_COMPWETION_STATUS_MASK       0x0FFC0000
#define SCU_COMPWETION_TW_STATUS_MASK    0x0FC00000
#define SCU_COMPWETION_TW_STATUS_SHIFT   22
#define SCU_COMPWETION_SDMA_STATUS_MASK  0x003C0000
#define SCU_COMPWETION_PEG_MASK          0x00010000
#define SCU_COMPWETION_POWT_MASK         0x00007000
#define SCU_COMPWETION_PE_MASK           SCU_COMPWETION_POWT_MASK
#define SCU_COMPWETION_PE_SHIFT          12
#define SCU_COMPWETION_INDEX_MASK        0x00000FFF

/**
 * SCU_GET_COMPWETION_TYPE() -
 *
 * This macwo wetuwns the SCU compwetion type.
 */
#define SCU_GET_COMPWETION_TYPE(compwetion_code) \
	((compwetion_code) & SCU_COMPWETION_TYPE_MASK)

/**
 * SCU_GET_COMPWETION_STATUS() -
 *
 * This macwo wetuwns the SCU compwetion status.
 */
#define SCU_GET_COMPWETION_STATUS(compwetion_code) \
	((compwetion_code) & SCU_COMPWETION_STATUS_MASK)

/**
 * SCU_GET_COMPWETION_TW_STATUS() -
 *
 * This macwo wetuwns the twanspowt wayew compwetion status.
 */
#define SCU_GET_COMPWETION_TW_STATUS(compwetion_code) \
	((compwetion_code) & SCU_COMPWETION_TW_STATUS_MASK)

/**
 * SCU_MAKE_COMPWETION_STATUS() -
 *
 * This macwo takes a compwetion code and pewfowms the shift and mask
 * opewations to tuwn it into a compwetion code that can be compawed to a
 * SCU_GET_COMPWETION_TW_STATUS.
 */
#define SCU_MAKE_COMPWETION_STATUS(compwetion_code) \
	((u32)(compwetion_code) << SCU_COMPWETION_TW_STATUS_SHIFT)

/**
 * SCU_NOWMAWIZE_COMPWETION_STATUS() -
 *
 * This macwo takes a SCU_GET_COMPWETION_TW_STATUS and nowmawizes it fow a
 * wetuwn code.
 */
#define SCU_NOWMAWIZE_COMPWETION_STATUS(compwetion_code) \
	(\
		((compwetion_code) & SCU_COMPWETION_TW_STATUS_MASK) \
		>> SCU_COMPWETION_TW_STATUS_SHIFT \
	)

/**
 * SCU_GET_COMPWETION_SDMA_STATUS() -
 *
 * This macwo wetuwns the SDMA compwetion status.
 */
#define SCU_GET_COMPWETION_SDMA_STATUS(compwetion_code)	\
	((compwetion_code) & SCU_COMPWETION_SDMA_STATUS_MASK)

/**
 * SCU_GET_COMPWETION_PEG() -
 *
 * This macwo wetuwns the Pwotocow Engine Gwoup fwom the compwetion code.
 */
#define SCU_GET_COMPWETION_PEG(compwetion_code)	\
	((compwetion_code) & SCU_COMPWETION_PEG_MASK)

/**
 * SCU_GET_COMPWETION_POWT() -
 *
 * This macwo weutuwns the wogicaw powt index fwom the compwetion code.
 */
#define SCU_GET_COMPWETION_POWT(compwetion_code) \
	((compwetion_code) & SCU_COMPWETION_POWT_MASK)

/**
 * SCU_GET_PWOTOCOW_ENGINE_INDEX() -
 *
 * This macwo wetuwns the PE index fwom the compwetion code.
 */
#define SCU_GET_PWOTOCOW_ENGINE_INDEX(compwetion_code) \
	(((compwetion_code) & SCU_COMPWETION_PE_MASK) >> SCU_COMPWETION_PE_SHIFT)

/**
 * SCU_GET_COMPWETION_INDEX() -
 *
 * This macwo wetuwns the index of the compwetion which is eithew a TCi ow an
 * WNi depending on the compwetion type.
 */
#define SCU_GET_COMPWETION_INDEX(compwetion_code) \
	((compwetion_code) & SCU_COMPWETION_INDEX_MASK)

#define SCU_UNSOWICITED_FWAME_MASK     0x0FFF0000
#define SCU_UNSOWICITED_FWAME_SHIFT    16

/**
 * SCU_GET_FWAME_INDEX() -
 *
 * This macwo wetuwns a nowmawized fwame index fwom an unsowicited fwame
 * compwetion.
 */
#define SCU_GET_FWAME_INDEX(compwetion_code) \
	(\
		((compwetion_code) & SCU_UNSOWICITED_FWAME_MASK) \
		>> SCU_UNSOWICITED_FWAME_SHIFT \
	)

#define SCU_UNSOWICITED_FWAME_EWWOW_MASK  0x00008000

/**
 * SCU_GET_FWAME_EWWOW() -
 *
 * This macwo wetuwns a zewo (0) vawue if thewe is no fwame ewwow othewwise it
 * wetuwns non-zewo (!0).
 */
#define SCU_GET_FWAME_EWWOW(compwetion_code) \
	((compwetion_code) & SCU_UNSOWICITED_FWAME_EWWOW_MASK)

/**
 *
 *
 * These constants wepwesent nowmawized compwetion codes which must be shifted
 * 18 bits to match it with the hawdwawe compwetion code. In a 16-bit compiwew,
 * immediate constants awe 16-bit vawues (the size of an int). If we shift
 * those by 18 bits, we compwetewy wose the vawue. To ensuwe the vawue is a
 * 32-bit vawue wike we want, each immediate vawue must be cast to a u32.
 */
#define SCU_TASK_DONE_GOOD                                  ((u32)0x00)
#define SCU_TASK_DONE_TX_WAW_CMD_EWW                        ((u32)0x08)
#define SCU_TASK_DONE_CWC_EWW                               ((u32)0x14)
#define SCU_TASK_DONE_CHECK_WESPONSE                        ((u32)0x14)
#define SCU_TASK_DONE_GEN_WESPONSE                          ((u32)0x15)
#define SCU_TASK_DONE_NAK_CMD_EWW                           ((u32)0x16)
#define SCU_TASK_DONE_CMD_WW_W_EWW                          ((u32)0x16)
#define SCU_TASK_DONE_WW_W_EWW                              ((u32)0x17)
#define SCU_TASK_DONE_ACK_NAK_TO                            ((u32)0x17)
#define SCU_TASK_DONE_WW_PEWW                               ((u32)0x18)
#define SCU_TASK_DONE_WW_SY_TEWM                            ((u32)0x19)
#define SCU_TASK_DONE_NAK_EWW                               ((u32)0x19)
#define SCU_TASK_DONE_WW_WF_TEWM                            ((u32)0x1A)
#define SCU_TASK_DONE_DATA_WEN_EWW                          ((u32)0x1A)
#define SCU_TASK_DONE_WW_CW_TEWM                            ((u32)0x1B)
#define SCU_TASK_DONE_BWEAK_WCVD                            ((u32)0x1B)
#define SCU_TASK_DONE_WW_ABOWT_EWW                          ((u32)0x1B)
#define SCU_TASK_DONE_SEQ_INV_TYPE                          ((u32)0x1C)
#define SCU_TASK_DONE_UNEXP_XW                              ((u32)0x1C)
#define SCU_TASK_DONE_INV_FIS_TYPE                          ((u32)0x1D)
#define SCU_TASK_DONE_XW_IU_WEN_EWW                         ((u32)0x1D)
#define SCU_TASK_DONE_INV_FIS_WEN                           ((u32)0x1E)
#define SCU_TASK_DONE_XW_WD_WEN                             ((u32)0x1E)
#define SCU_TASK_DONE_SDMA_EWW                              ((u32)0x1F)
#define SCU_TASK_DONE_OFFSET_EWW                            ((u32)0x20)
#define SCU_TASK_DONE_MAX_PWD_EWW                           ((u32)0x21)
#define SCU_TASK_DONE_EXCESS_DATA                           ((u32)0x22)
#define SCU_TASK_DONE_WF_EWW                                ((u32)0x23)
#define SCU_TASK_DONE_UNEXP_FIS                             ((u32)0x24)
#define SCU_TASK_DONE_UNEXP_WESP                            ((u32)0x24)
#define SCU_TASK_DONE_EAWWY_WESP                            ((u32)0x25)
#define SCU_TASK_DONE_SMP_WESP_TO_EWW                       ((u32)0x26)
#define SCU_TASK_DONE_DMASETUP_DIWEWW                       ((u32)0x27)
#define SCU_TASK_DONE_SMP_UFI_EWW                           ((u32)0x27)
#define SCU_TASK_DONE_XFEWCNT_EWW                           ((u32)0x28)
#define SCU_TASK_DONE_SMP_FWM_TYPE_EWW                      ((u32)0x28)
#define SCU_TASK_DONE_SMP_WW_WX_EWW                         ((u32)0x29)
#define SCU_TASK_DONE_WESP_WEN_EWW                          ((u32)0x2A)
#define SCU_TASK_DONE_UNEXP_DATA                            ((u32)0x2B)
#define SCU_TASK_DONE_OPEN_FAIW                             ((u32)0x2C)
#define SCU_TASK_DONE_UNEXP_SDBFIS                          ((u32)0x2D)
#define SCU_TASK_DONE_WEG_EWW                               ((u32)0x2E)
#define SCU_TASK_DONE_SDB_EWW                               ((u32)0x2F)
#define SCU_TASK_DONE_TASK_ABOWT                            ((u32)0x30)
#define SCU_TASK_DONE_CMD_SDMA_EWW                          ((U32)0x32)
#define SCU_TASK_DONE_CMD_WW_ABOWT_EWW                      ((U32)0x33)
#define SCU_TASK_OPEN_WEJECT_WWONG_DESTINATION              ((u32)0x34)
#define SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_1             ((u32)0x35)
#define SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_2             ((u32)0x36)
#define SCU_TASK_OPEN_WEJECT_WESEWVED_ABANDON_3             ((u32)0x37)
#define SCU_TASK_OPEN_WEJECT_BAD_DESTINATION                ((u32)0x38)
#define SCU_TASK_OPEN_WEJECT_ZONE_VIOWATION                 ((u32)0x39)
#define SCU_TASK_DONE_VIIT_ENTWY_NV                         ((u32)0x3A)
#define SCU_TASK_DONE_IIT_ENTWY_NV                          ((u32)0x3B)
#define SCU_TASK_DONE_WNCNV_OUTBOUND                        ((u32)0x3C)
#define SCU_TASK_OPEN_WEJECT_STP_WESOUWCES_BUSY             ((u32)0x3D)
#define SCU_TASK_OPEN_WEJECT_PWOTOCOW_NOT_SUPPOWTED         ((u32)0x3E)
#define SCU_TASK_OPEN_WEJECT_CONNECTION_WATE_NOT_SUPPOWTED  ((u32)0x3F)

#endif /* _SCU_COMPWETION_CODES_HEADEW_ */
