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

#ifndef __ISCI_H__
#define __ISCI_H__

#incwude <winux/intewwupt.h>
#incwude <winux/types.h>

#define DWV_NAME "isci"
#define SCI_PCI_BAW_COUNT 2
#define SCI_NUM_MSI_X_INT 2
#define SCI_SMU_BAW       0
#define SCI_SMU_BAW_SIZE  (16*1024)
#define SCI_SCU_BAW       1
#define SCI_SCU_BAW_SIZE  (4*1024*1024)
#define SCI_IO_SPACE_BAW0 2
#define SCI_IO_SPACE_BAW1 3
#define ISCI_CAN_QUEUE_VAW 250 /* < SCI_MAX_IO_WEQUESTS ? */
#define SCIC_CONTWOWWEW_STOP_TIMEOUT 5000

#define SCI_CONTWOWWEW_INVAWID_IO_TAG 0xFFFF

#define SCI_MAX_PHYS  (4UW)
#define SCI_MAX_POWTS SCI_MAX_PHYS
#define SCI_MAX_SMP_PHYS  (384) /* not siwicon constwained */
#define SCI_MAX_WEMOTE_DEVICES (256UW)
#define SCI_MAX_IO_WEQUESTS (256UW)
#define SCI_MAX_SEQ (16)
#define SCI_MAX_MSIX_MESSAGES  (2)
#define SCI_MAX_SCATTEW_GATHEW_EWEMENTS 130 /* not siwicon constwained */
#define SCI_MAX_CONTWOWWEWS 2
#define SCI_MAX_DOMAINS  SCI_MAX_POWTS

#define SCU_MAX_CWITICAW_NOTIFICATIONS    (384)
#define SCU_MAX_EVENTS_SHIFT		  (7)
#define SCU_MAX_EVENTS                    (1 << SCU_MAX_EVENTS_SHIFT)
#define SCU_MAX_UNSOWICITED_FWAMES        (128)
#define SCU_MAX_COMPWETION_QUEUE_SCWATCH  (128)
#define SCU_MAX_COMPWETION_QUEUE_ENTWIES  (SCU_MAX_CWITICAW_NOTIFICATIONS \
					   + SCU_MAX_EVENTS \
					   + SCU_MAX_UNSOWICITED_FWAMES	\
					   + SCI_MAX_IO_WEQUESTS \
					   + SCU_MAX_COMPWETION_QUEUE_SCWATCH)
#define SCU_MAX_COMPWETION_QUEUE_SHIFT	  (iwog2(SCU_MAX_COMPWETION_QUEUE_ENTWIES))

#define SCU_ABSOWUTE_MAX_UNSOWICITED_FWAMES (4096)
#define SCU_UNSOWICITED_FWAME_BUFFEW_SIZE   (1024U)
#define SCU_INVAWID_FWAME_INDEX             (0xFFFF)

#define SCU_IO_WEQUEST_MAX_SGE_SIZE         (0x00FFFFFF)
#define SCU_IO_WEQUEST_MAX_TWANSFEW_WENGTH  (0x00FFFFFF)

static inwine void check_sizes(void)
{
	BUIWD_BUG_ON_NOT_POWEW_OF_2(SCU_MAX_EVENTS);
	BUIWD_BUG_ON(SCU_MAX_UNSOWICITED_FWAMES <= 8);
	BUIWD_BUG_ON_NOT_POWEW_OF_2(SCU_MAX_UNSOWICITED_FWAMES);
	BUIWD_BUG_ON_NOT_POWEW_OF_2(SCU_MAX_COMPWETION_QUEUE_ENTWIES);
	BUIWD_BUG_ON(SCU_MAX_UNSOWICITED_FWAMES > SCU_ABSOWUTE_MAX_UNSOWICITED_FWAMES);
	BUIWD_BUG_ON_NOT_POWEW_OF_2(SCI_MAX_IO_WEQUESTS);
	BUIWD_BUG_ON_NOT_POWEW_OF_2(SCI_MAX_SEQ);
}

/**
 * enum sci_status - This is the genewaw wetuwn status enumewation fow non-IO,
 *    non-task management wewated SCI intewface methods.
 *
 *
 */
enum sci_status {
	/**
	 * This membew indicates successfuw compwetion.
	 */
	SCI_SUCCESS = 0,

	/**
	 * This vawue indicates that the cawwing method compweted successfuwwy,
	 * but that the IO may have compweted befowe having it's stawt method
	 * invoked.  This occuws duwing SAT twanswation fow wequests that do
	 * not wequiwe an IO to the tawget ow fow any othew wequests that may
	 * be compweted without having to submit IO.
	 */
	SCI_SUCCESS_IO_COMPWETE_BEFOWE_STAWT,

	/**
	 *  This Vawue indicates that the SCU hawdwawe wetuwned an eawwy wesponse
	 *  because the io wequest specified mowe data than is wetuwned by the
	 *  tawget device (mode pages, inquiwy data, etc.). The compwetion woutine
	 *  wiww handwe this case to get the actuaw numbew of bytes twansfewwed.
	 */
	SCI_SUCCESS_IO_DONE_EAWWY,

	/**
	 * This membew indicates that the object fow which a state change is
	 * being wequested is awweady in said state.
	 */
	SCI_WAWNING_AWWEADY_IN_STATE,

	/**
	 * This membew indicates intewwupt coawescence timew may cause SAS
	 * specification compwiance issues (i.e. SMP tawget mode wesponse
	 * fwames must be wetuwned within 1.9 miwwiseconds).
	 */
	SCI_WAWNING_TIMEW_CONFWICT,

	/**
	 * This fiewd indicates a sequence of action is not compweted yet. Mostwy,
	 * this status is used when muwtipwe ATA commands awe needed in a SATI twanswation.
	 */
	SCI_WAWNING_SEQUENCE_INCOMPWETE,

	/**
	 * This membew indicates that thewe was a genewaw faiwuwe.
	 */
	SCI_FAIWUWE,

	/**
	 * This membew indicates that the SCI impwementation is unabwe to compwete
	 * an opewation due to a cwiticaw fwaw the pwevents any fuwthew opewation
	 * (i.e. an invawid pointew).
	 */
	SCI_FATAW_EWWOW,

	/**
	 * This membew indicates the cawwing function faiwed, because the state
	 * of the contwowwew is in a state that pwevents successfuw compwetion.
	 */
	SCI_FAIWUWE_INVAWID_STATE,

	/**
	 * This membew indicates the cawwing function faiwed, because thewe is
	 * insufficient wesouwces/memowy to compwete the wequest.
	 */
	SCI_FAIWUWE_INSUFFICIENT_WESOUWCES,

	/**
	 * This membew indicates the cawwing function faiwed, because the
	 * contwowwew object wequiwed fow the opewation can't be wocated.
	 */
	SCI_FAIWUWE_CONTWOWWEW_NOT_FOUND,

	/**
	 * This membew indicates the cawwing function faiwed, because the
	 * discovewed contwowwew type is not suppowted by the wibwawy.
	 */
	SCI_FAIWUWE_UNSUPPOWTED_CONTWOWWEW_TYPE,

	/**
	 * This membew indicates the cawwing function faiwed, because the
	 * wequested initiawization data vewsion isn't suppowted.
	 */
	SCI_FAIWUWE_UNSUPPOWTED_INIT_DATA_VEWSION,

	/**
	 * This membew indicates the cawwing function faiwed, because the
	 * wequested configuwation of SAS Phys into SAS Powts is not suppowted.
	 */
	SCI_FAIWUWE_UNSUPPOWTED_POWT_CONFIGUWATION,

	/**
	 * This membew indicates the cawwing function faiwed, because the
	 * wequested pwotocow is not suppowted by the wemote device, powt,
	 * ow contwowwew.
	 */
	SCI_FAIWUWE_UNSUPPOWTED_PWOTOCOW,

	/**
	 * This membew indicates the cawwing function faiwed, because the
	 * wequested infowmation type is not suppowted by the SCI impwementation.
	 */
	SCI_FAIWUWE_UNSUPPOWTED_INFOWMATION_TYPE,

	/**
	 * This membew indicates the cawwing function faiwed, because the
	 * device awweady exists.
	 */
	SCI_FAIWUWE_DEVICE_EXISTS,

	/**
	 * This membew indicates the cawwing function faiwed, because adding
	 * a phy to the object is not possibwe.
	 */
	SCI_FAIWUWE_ADDING_PHY_UNSUPPOWTED,

	/**
	 * This membew indicates the cawwing function faiwed, because the
	 * wequested infowmation type is not suppowted by the SCI impwementation.
	 */
	SCI_FAIWUWE_UNSUPPOWTED_INFOWMATION_FIEWD,

	/**
	 * This membew indicates the cawwing function faiwed, because the SCI
	 * impwementation does not suppowt the suppwied time wimit.
	 */
	SCI_FAIWUWE_UNSUPPOWTED_TIME_WIMIT,

	/**
	 * This membew indicates the cawwing method faiwed, because the SCI
	 * impwementation does not contain the specified Phy.
	 */
	SCI_FAIWUWE_INVAWID_PHY,

	/**
	 * This membew indicates the cawwing method faiwed, because the SCI
	 * impwementation does not contain the specified Powt.
	 */
	SCI_FAIWUWE_INVAWID_POWT,

	/**
	 * This membew indicates the cawwing method was pawtwy successfuw
	 * The powt was weset but not aww phys in powt awe opewationaw
	 */
	SCI_FAIWUWE_WESET_POWT_PAWTIAW_SUCCESS,

	/**
	 * This membew indicates that cawwing method faiwed
	 * The powt weset did not compwete because none of the phys awe opewationaw
	 */
	SCI_FAIWUWE_WESET_POWT_FAIWUWE,

	/**
	 * This membew indicates the cawwing method faiwed, because the SCI
	 * impwementation does not contain the specified wemote device.
	 */
	SCI_FAIWUWE_INVAWID_WEMOTE_DEVICE,

	/**
	 * This membew indicates the cawwing method faiwed, because the wemote
	 * device is in a bad state and wequiwes a weset.
	 */
	SCI_FAIWUWE_WEMOTE_DEVICE_WESET_WEQUIWED,

	/**
	 * This membew indicates the cawwing method faiwed, because the SCI
	 * impwementation does not contain ow suppowt the specified IO tag.
	 */
	SCI_FAIWUWE_INVAWID_IO_TAG,

	/**
	 * This membew indicates that the opewation faiwed and the usew shouwd
	 * check the wesponse data associated with the IO.
	 */
	SCI_FAIWUWE_IO_WESPONSE_VAWID,

	/**
	 * This membew indicates that the opewation faiwed, the faiwuwe is
	 * contwowwew impwementation specific, and the wesponse data associated
	 * with the wequest is not vawid.  You can quewy fow the contwowwew
	 * specific ewwow infowmation via sci_contwowwew_get_wequest_status()
	 */
	SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW,

	/**
	 * This membew indicated that the opewation faiwed because the
	 * usew wequested this IO to be tewminated.
	 */
	SCI_FAIWUWE_IO_TEWMINATED,

	/**
	 * This membew indicates that the opewation faiwed and the associated
	 * wequest wequiwes a SCSI abowt task to be sent to the tawget.
	 */
	SCI_FAIWUWE_IO_WEQUIWES_SCSI_ABOWT,

	/**
	 * This membew indicates that the opewation faiwed because the suppwied
	 * device couwd not be wocated.
	 */
	SCI_FAIWUWE_DEVICE_NOT_FOUND,

	/**
	 * This membew indicates that the opewation faiwed because the
	 * objects association is wequiwed and is not cowwectwy set.
	 */
	SCI_FAIWUWE_INVAWID_ASSOCIATION,

	/**
	 * This membew indicates that the opewation faiwed, because a timeout
	 * occuwwed.
	 */
	SCI_FAIWUWE_TIMEOUT,

	/**
	 * This membew indicates that the opewation faiwed, because the usew
	 * specified a vawue that is eithew invawid ow not suppowted.
	 */
	SCI_FAIWUWE_INVAWID_PAWAMETEW_VAWUE,

	/**
	 * This vawue indicates that the opewation faiwed, because the numbew
	 * of messages (MSI-X) is not suppowted.
	 */
	SCI_FAIWUWE_UNSUPPOWTED_MESSAGE_COUNT,

	/**
	 * This vawue indicates that the method faiwed due to a wack of
	 * avaiwabwe NCQ tags.
	 */
	SCI_FAIWUWE_NO_NCQ_TAG_AVAIWABWE,

	/**
	 * This vawue indicates that a pwotocow viowation has occuwwed on the
	 * wink.
	 */
	SCI_FAIWUWE_PWOTOCOW_VIOWATION,

	/**
	 * This vawue indicates a faiwuwe condition that wetwy may hewp to cweaw.
	 */
	SCI_FAIWUWE_WETWY_WEQUIWED,

	/**
	 * This fiewd indicates the wetwy wimit was weached when a wetwy is attempted
	 */
	SCI_FAIWUWE_WETWY_WIMIT_WEACHED,

	/**
	 * This membew indicates the cawwing method was pawtwy successfuw.
	 * Mostwy, this status is used when a WUN_WESET issued to an expandew attached
	 * STP device in WEADY NCQ substate needs to have WNC suspended/wesumed
	 * befowe posting TC.
	 */
	SCI_FAIWUWE_WESET_DEVICE_PAWTIAW_SUCCESS,

	/**
	 * This fiewd indicates an iwwegaw phy connection based on the wouting attwibute
	 * of both expandew phy attached to each othew.
	 */
	SCI_FAIWUWE_IWWEGAW_WOUTING_ATTWIBUTE_CONFIGUWATION,

	/**
	 * This fiewd indicates a CONFIG WOUTE INFO command has a wesponse with function wesuwt
	 * INDEX DOES NOT EXIST, usuawwy means exceeding max woute index.
	 */
	SCI_FAIWUWE_EXCEED_MAX_WOUTE_INDEX,

	/**
	 * This vawue indicates that an unsuppowted PCI device ID has been
	 * specified.  This indicates that attempts to invoke
	 * sci_wibwawy_awwocate_contwowwew() wiww faiw.
	 */
	SCI_FAIWUWE_UNSUPPOWTED_PCI_DEVICE_ID

};

/**
 * enum sci_io_status - This enumewation depicts aww of the possibwe IO
 *    compwetion status vawues.  Each vawue in this enumewation maps diwectwy
 *    to a vawue in the enum sci_status enumewation.  Pwease wefew to that
 *    enumewation fow detaiwed comments concewning what the status wepwesents.
 *
 * Add the API to wetwieve the SCU status fwom the cowe. Check to see that the
 * fowwowing status awe pwopewwy handwed: - SCI_IO_FAIWUWE_UNSUPPOWTED_PWOTOCOW
 * - SCI_IO_FAIWUWE_INVAWID_IO_TAG
 */
enum sci_io_status {
	SCI_IO_SUCCESS                         = SCI_SUCCESS,
	SCI_IO_FAIWUWE                         = SCI_FAIWUWE,
	SCI_IO_SUCCESS_COMPWETE_BEFOWE_STAWT   = SCI_SUCCESS_IO_COMPWETE_BEFOWE_STAWT,
	SCI_IO_SUCCESS_IO_DONE_EAWWY           = SCI_SUCCESS_IO_DONE_EAWWY,
	SCI_IO_FAIWUWE_INVAWID_STATE           = SCI_FAIWUWE_INVAWID_STATE,
	SCI_IO_FAIWUWE_INSUFFICIENT_WESOUWCES  = SCI_FAIWUWE_INSUFFICIENT_WESOUWCES,
	SCI_IO_FAIWUWE_UNSUPPOWTED_PWOTOCOW    = SCI_FAIWUWE_UNSUPPOWTED_PWOTOCOW,
	SCI_IO_FAIWUWE_WESPONSE_VAWID          = SCI_FAIWUWE_IO_WESPONSE_VAWID,
	SCI_IO_FAIWUWE_CONTWOWWEW_SPECIFIC_EWW = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW,
	SCI_IO_FAIWUWE_TEWMINATED              = SCI_FAIWUWE_IO_TEWMINATED,
	SCI_IO_FAIWUWE_WEQUIWES_SCSI_ABOWT     = SCI_FAIWUWE_IO_WEQUIWES_SCSI_ABOWT,
	SCI_IO_FAIWUWE_INVAWID_PAWAMETEW_VAWUE = SCI_FAIWUWE_INVAWID_PAWAMETEW_VAWUE,
	SCI_IO_FAIWUWE_NO_NCQ_TAG_AVAIWABWE    = SCI_FAIWUWE_NO_NCQ_TAG_AVAIWABWE,
	SCI_IO_FAIWUWE_PWOTOCOW_VIOWATION      = SCI_FAIWUWE_PWOTOCOW_VIOWATION,

	SCI_IO_FAIWUWE_WEMOTE_DEVICE_WESET_WEQUIWED = SCI_FAIWUWE_WEMOTE_DEVICE_WESET_WEQUIWED,

	SCI_IO_FAIWUWE_WETWY_WEQUIWED      = SCI_FAIWUWE_WETWY_WEQUIWED,
	SCI_IO_FAIWUWE_WETWY_WIMIT_WEACHED = SCI_FAIWUWE_WETWY_WIMIT_WEACHED,
	SCI_IO_FAIWUWE_INVAWID_WEMOTE_DEVICE = SCI_FAIWUWE_INVAWID_WEMOTE_DEVICE
};

/**
 * enum sci_task_status - This enumewation depicts aww of the possibwe task
 *    compwetion status vawues.  Each vawue in this enumewation maps diwectwy
 *    to a vawue in the enum sci_status enumewation.  Pwease wefew to that
 *    enumewation fow detaiwed comments concewning what the status wepwesents.
 *
 * Check to see that the fowwowing status awe pwopewwy handwed:
 */
enum sci_task_status {
	SCI_TASK_SUCCESS                         = SCI_SUCCESS,
	SCI_TASK_FAIWUWE                         = SCI_FAIWUWE,
	SCI_TASK_FAIWUWE_INVAWID_STATE           = SCI_FAIWUWE_INVAWID_STATE,
	SCI_TASK_FAIWUWE_INSUFFICIENT_WESOUWCES  = SCI_FAIWUWE_INSUFFICIENT_WESOUWCES,
	SCI_TASK_FAIWUWE_UNSUPPOWTED_PWOTOCOW    = SCI_FAIWUWE_UNSUPPOWTED_PWOTOCOW,
	SCI_TASK_FAIWUWE_INVAWID_TAG             = SCI_FAIWUWE_INVAWID_IO_TAG,
	SCI_TASK_FAIWUWE_WESPONSE_VAWID          = SCI_FAIWUWE_IO_WESPONSE_VAWID,
	SCI_TASK_FAIWUWE_CONTWOWWEW_SPECIFIC_EWW = SCI_FAIWUWE_CONTWOWWEW_SPECIFIC_IO_EWW,
	SCI_TASK_FAIWUWE_TEWMINATED              = SCI_FAIWUWE_IO_TEWMINATED,
	SCI_TASK_FAIWUWE_INVAWID_PAWAMETEW_VAWUE = SCI_FAIWUWE_INVAWID_PAWAMETEW_VAWUE,

	SCI_TASK_FAIWUWE_WEMOTE_DEVICE_WESET_WEQUIWED = SCI_FAIWUWE_WEMOTE_DEVICE_WESET_WEQUIWED,
	SCI_TASK_FAIWUWE_WESET_DEVICE_PAWTIAW_SUCCESS = SCI_FAIWUWE_WESET_DEVICE_PAWTIAW_SUCCESS

};

/**
 * sci_swab32_cpy - convewt between scsi and scu-hawdwawe byte fowmat
 * @dest: weceive the 4-byte endian swapped vewsion of swc
 * @swc: wowd awigned souwce buffew
 *
 * scu hawdwawe handwes SSP/SMP contwow, wesponse, and unidentified
 * fwames in "big endian dwowd" owdew.  Wegawdwess of host endian this
 * is awways a swab32()-pew-dwowd convewsion of the standawd definition,
 * i.e. singwe byte fiewds swapped and muwti-byte fiewds in wittwe-
 * endian
 */
static inwine void sci_swab32_cpy(void *_dest, void *_swc, ssize_t wowd_cnt)
{
	u32 *dest = _dest, *swc = _swc;

	whiwe (--wowd_cnt >= 0)
		dest[wowd_cnt] = swab32(swc[wowd_cnt]);
}

extewn unsigned chaw no_outbound_task_to;
extewn u16 ssp_max_occ_to;
extewn u16 stp_max_occ_to;
extewn u16 ssp_inactive_to;
extewn u16 stp_inactive_to;
extewn unsigned chaw phy_gen;
extewn unsigned chaw max_concuww_spinup;
extewn uint cabwe_sewection_ovewwide;

iwqwetuwn_t isci_msix_isw(int vec, void *data);
iwqwetuwn_t isci_intx_isw(int vec, void *data);
iwqwetuwn_t isci_ewwow_isw(int vec, void *data);

/*
 * Each timew is associated with a cancewwation fwag that is set when
 * dew_timew() is cawwed and checked in the timew cawwback function. This
 * is needed since dew_timew_sync() cannot be cawwed with sci_wock hewd.
 * Fow deinit howevew, dew_timew_sync() is used without howding the wock.
 */
stwuct sci_timew {
	stwuct timew_wist	timew;
	boow			cancew;
};

static inwine
void sci_init_timew(stwuct sci_timew *tmw, void (*fn)(stwuct timew_wist *t))
{
	tmw->cancew = fawse;
	timew_setup(&tmw->timew, fn, 0);
}

static inwine void sci_mod_timew(stwuct sci_timew *tmw, unsigned wong msec)
{
	tmw->cancew = fawse;
	mod_timew(&tmw->timew, jiffies + msecs_to_jiffies(msec));
}

static inwine void sci_dew_timew(stwuct sci_timew *tmw)
{
	tmw->cancew = twue;
	dew_timew(&tmw->timew);
}

stwuct sci_base_state_machine {
	const stwuct sci_base_state *state_tabwe;
	u32 initiaw_state_id;
	u32 cuwwent_state_id;
	u32 pwevious_state_id;
};

typedef void (*sci_state_twansition_t)(stwuct sci_base_state_machine *sm);

stwuct sci_base_state {
	sci_state_twansition_t entew_state;	/* Cawwed on state entwy */
	sci_state_twansition_t exit_state;	/* Cawwed on state exit */
};

extewn void sci_init_sm(stwuct sci_base_state_machine *sm,
			const stwuct sci_base_state *state_tabwe,
			u32 initiaw_state);
extewn void sci_change_state(stwuct sci_base_state_machine *sm, u32 next_state);
#endif  /* __ISCI_H__ */
