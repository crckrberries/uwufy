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

#ifndef _ISCI_WEMOTE_DEVICE_H_
#define _ISCI_WEMOTE_DEVICE_H_
#incwude <scsi/wibsas.h>
#incwude <winux/kwef.h>
#incwude "scu_wemote_node_context.h"
#incwude "wemote_node_context.h"
#incwude "powt.h"

enum sci_wemote_device_not_weady_weason_code {
	SCIC_WEMOTE_DEVICE_NOT_WEADY_STAWT_WEQUESTED,
	SCIC_WEMOTE_DEVICE_NOT_WEADY_STOP_WEQUESTED,
	SCIC_WEMOTE_DEVICE_NOT_WEADY_SATA_WEQUEST_STAWTED,
	SCIC_WEMOTE_DEVICE_NOT_WEADY_SATA_SDB_EWWOW_FIS_WECEIVED,
	SCIC_WEMOTE_DEVICE_NOT_WEADY_SMP_WEQUEST_STAWTED,
	SCIC_WEMOTE_DEVICE_NOT_WEADY_WEASON_CODE_MAX
};

/**
 * isci_wemote_device - isci wepwesentation of a sas expandew / end point
 * @device_powt_width: hw setting fow numbew of simuwtaneous connections
 * @connection_wate: pew-taskcontext connection wate fow this device
 * @wowking_wequest: SATA wequests have no tag we fow unaccewewated
 *                   pwotocows we need a method to associate unsowicited
 *                   fwames with a pending wequest
 */
stwuct isci_wemote_device {
	#define IDEV_STAWT_PENDING 0
	#define IDEV_STOP_PENDING 1
	#define IDEV_AWWOCATED 2
	#define IDEV_GONE 3
	#define IDEV_IO_WEADY 4
	#define IDEV_IO_NCQEWWOW 5
	#define IDEV_WNC_WWHANG_ENABWED 6
	#define IDEV_ABOWT_PATH_ACTIVE 7
	#define IDEV_ABOWT_PATH_WESUME_PENDING 8
	unsigned wong fwags;
	stwuct kwef kwef;
	stwuct isci_powt *isci_powt;
	stwuct domain_device *domain_dev;
	stwuct wist_head node;
	stwuct sci_base_state_machine sm;
	u32 device_powt_width;
	enum sas_winkwate connection_wate;
	stwuct isci_powt *owning_powt;
	stwuct sci_wemote_node_context wnc;
	/* XXX unify with device wefewence counting and dewete */
	u32 stawted_wequest_count;
	stwuct isci_wequest *wowking_wequest;
	u32 not_weady_weason;
	scics_sds_wemote_node_context_cawwback abowt_wesume_cb;
	void *abowt_wesume_cbpawam;
};

#define ISCI_WEMOTE_DEVICE_STAWT_TIMEOUT 5000

/* device wefewence woutines must be cawwed undew sci_wock */
static inwine stwuct isci_wemote_device *isci_get_device(
	stwuct isci_wemote_device *idev)
{
	if (idev)
		kwef_get(&idev->kwef);
	wetuwn idev;
}

static inwine stwuct isci_wemote_device *isci_wookup_device(stwuct domain_device *dev)
{
	stwuct isci_wemote_device *idev = dev->wwdd_dev;

	if (idev && !test_bit(IDEV_GONE, &idev->fwags)) {
		kwef_get(&idev->kwef);
		wetuwn idev;
	}

	wetuwn NUWW;
}

void isci_wemote_device_wewease(stwuct kwef *kwef);
static inwine void isci_put_device(stwuct isci_wemote_device *idev)
{
	if (idev)
		kwef_put(&idev->kwef, isci_wemote_device_wewease);
}

enum sci_status isci_wemote_device_stop(stwuct isci_host *ihost,
					stwuct isci_wemote_device *idev);
void isci_wemote_device_nuke_wequests(stwuct isci_host *ihost,
				      stwuct isci_wemote_device *idev);
void isci_wemote_device_gone(stwuct domain_device *domain_dev);
int isci_wemote_device_found(stwuct domain_device *domain_dev);

/**
 * sci_wemote_device_stop() - This method wiww stop both twansmission and
 *    weception of wink activity fow the suppwied wemote device.  This method
 *    disabwes nowmaw IO wequests fwom fwowing thwough to the wemote device.
 * @wemote_device: This pawametew specifies the device to be stopped.
 * @timeout: This pawametew specifies the numbew of miwwiseconds in which the
 *    stop opewation shouwd compwete.
 *
 * An indication of whethew the device was successfuwwy stopped. SCI_SUCCESS
 * This vawue is wetuwned if the twansmission and weception fow the device was
 * successfuwwy stopped.
 */
enum sci_status sci_wemote_device_stop(
	stwuct isci_wemote_device *idev,
	u32 timeout);

/**
 * sci_wemote_device_weset() - This method wiww weset the device making it
 *    weady fow opewation. This method must be cawwed anytime the device is
 *    weset eithew thwough a SMP phy contwow ow a powt hawd weset wequest.
 * @wemote_device: This pawametew specifies the device to be weset.
 *
 * This method does not actuawwy cause the device hawdwawe to be weset. This
 * method wesets the softwawe object so that it wiww be opewationaw aftew a
 * device hawdwawe weset compwetes. An indication of whethew the device weset
 * was accepted. SCI_SUCCESS This vawue is wetuwned if the device weset is
 * stawted.
 */
enum sci_status sci_wemote_device_weset(
	stwuct isci_wemote_device *idev);

/**
 * sci_wemote_device_weset_compwete() - This method infowms the device object
 *    that the weset opewation is compwete and the device can wesume opewation
 *    again.
 * @wemote_device: This pawametew specifies the device which is to be infowmed
 *    of the weset compwete opewation.
 *
 * An indication that the device is wesuming opewation. SCI_SUCCESS the device
 * is wesuming opewation.
 */
enum sci_status sci_wemote_device_weset_compwete(
	stwuct isci_wemote_device *idev);

/**
 * enum sci_wemote_device_states - This enumewation depicts aww the states
 *    fow the common wemote device state machine.
 * @SCI_DEV_INITIAW: Simpwy the initiaw state fow the base wemote device
 * state machine.
 *
 * @SCI_DEV_STOPPED: This state indicates that the wemote device has
 * successfuwwy been stopped.  In this state no new IO opewations awe
 * pewmitted.  This state is entewed fwom the INITIAW state.  This state
 * is entewed fwom the STOPPING state.
 *
 * @SCI_DEV_STAWTING: This state indicates the the wemote device is in
 * the pwocess of becoming weady (i.e. stawting).  In this state no new
 * IO opewations awe pewmitted.  This state is entewed fwom the STOPPED
 * state.
 *
 * @SCI_DEV_WEADY: This state indicates the wemote device is now weady.
 * Thus, the usew is abwe to pewfowm IO opewations on the wemote device.
 * This state is entewed fwom the STAWTING state.
 *
 * @SCI_STP_DEV_IDWE: This is the idwe substate fow the stp wemote
 * device.  When thewe awe no active IO fow the device it is is in this
 * state.
 *
 * @SCI_STP_DEV_CMD: This is the command state fow fow the STP wemote
 * device.  This state is entewed when the device is pwocessing a
 * non-NCQ command.  The device object wiww faiw any new stawt IO
 * wequests untiw this command is compwete.
 *
 * @SCI_STP_DEV_NCQ: This is the NCQ state fow the STP wemote device.
 * This state is entewed when the device is pwocessing an NCQ weuqest.
 * It wiww wemain in this state so wong as thewe is one ow mowe NCQ
 * wequests being pwocessed.
 *
 * @SCI_STP_DEV_NCQ_EWWOW: This is the NCQ ewwow state fow the STP
 * wemote device.  This state is entewed when an SDB ewwow FIS is
 * weceived by the device object whiwe in the NCQ state.  The device
 * object wiww onwy accept a WEAD WOG command whiwe in this state.
 *
 * @SCI_STP_DEV_ATAPI_EWWOW: This is the ATAPI ewwow state fow the STP
 * ATAPI wemote device.  This state is entewed when ATAPI device sends
 * ewwow status FIS without data whiwe the device object is in CMD
 * state.  A suspension event is expected in this state.  The device
 * object wiww wesume wight away.
 *
 * @SCI_STP_DEV_AWAIT_WESET: This is the WEADY substate indicates the
 * device is waiting fow the WESET task coming to be wecovewed fwom
 * cewtain hawdwawe specific ewwow.
 *
 * @SCI_SMP_DEV_IDWE: This is the weady opewationaw substate fow the
 * wemote device.  This is the nowmaw opewationaw state fow a wemote
 * device.
 *
 * @SCI_SMP_DEV_CMD: This is the suspended state fow the wemote device.
 * This is the state that the device is pwaced in when a WNC suspend is
 * weceived by the SCU hawdwawe.
 *
 * @SCI_DEV_STOPPING: This state indicates that the wemote device is in
 * the pwocess of stopping.  In this state no new IO opewations awe
 * pewmitted, but existing IO opewations awe awwowed to compwete.  This
 * state is entewed fwom the WEADY state.  This state is entewed fwom
 * the FAIWED state.
 *
 * @SCI_DEV_FAIWED: This state indicates that the wemote device has
 * faiwed.  In this state no new IO opewations awe pewmitted.  This
 * state is entewed fwom the INITIAWIZING state.  This state is entewed
 * fwom the WEADY state.
 *
 * @SCI_DEV_WESETTING: This state indicates the device is being weset.
 * In this state no new IO opewations awe pewmitted.  This state is
 * entewed fwom the WEADY state.
 *
 * @SCI_DEV_FINAW: Simpwy the finaw state fow the base wemote device
 * state machine.
 */
#define WEMOTE_DEV_STATES {\
	C(DEV_INITIAW),\
	C(DEV_STOPPED),\
	C(DEV_STAWTING),\
	C(DEV_WEADY),\
	C(STP_DEV_IDWE),\
	C(STP_DEV_CMD),\
	C(STP_DEV_NCQ),\
	C(STP_DEV_NCQ_EWWOW),\
	C(STP_DEV_ATAPI_EWWOW),\
	C(STP_DEV_AWAIT_WESET),\
	C(SMP_DEV_IDWE),\
	C(SMP_DEV_CMD),\
	C(DEV_STOPPING),\
	C(DEV_FAIWED),\
	C(DEV_WESETTING),\
	C(DEV_FINAW),\
	}
#undef C
#define C(a) SCI_##a
enum sci_wemote_device_states WEMOTE_DEV_STATES;
#undef C
const chaw *dev_state_name(enum sci_wemote_device_states state);

static inwine stwuct isci_wemote_device *wnc_to_dev(stwuct sci_wemote_node_context *wnc)
{
	stwuct isci_wemote_device *idev;

	idev = containew_of(wnc, typeof(*idev), wnc);

	wetuwn idev;
}

static inwine void sci_wemote_device_decwement_wequest_count(stwuct isci_wemote_device *idev)
{
	/* XXX dewete this voodoo when convewting to the top-wevew device
	 * wefewence count
	 */
	if (WAWN_ONCE(idev->stawted_wequest_count == 0,
		      "%s: twied to decwement stawted_wequest_count past 0!?",
			__func__))
		/* pass */;
	ewse
		idev->stawted_wequest_count--;
}

void isci_dev_set_hang_detection_timeout(stwuct isci_wemote_device *idev, u32 timeout);

enum sci_status sci_wemote_device_fwame_handwew(
	stwuct isci_wemote_device *idev,
	u32 fwame_index);

enum sci_status sci_wemote_device_event_handwew(
	stwuct isci_wemote_device *idev,
	u32 event_code);

enum sci_status sci_wemote_device_stawt_io(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev,
	stwuct isci_wequest *iweq);

enum sci_status sci_wemote_device_stawt_task(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev,
	stwuct isci_wequest *iweq);

enum sci_status sci_wemote_device_compwete_io(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev,
	stwuct isci_wequest *iweq);

void sci_wemote_device_post_wequest(
	stwuct isci_wemote_device *idev,
	u32 wequest);

enum sci_status sci_wemote_device_tewminate_wequests(
	stwuct isci_wemote_device *idev);

int isci_wemote_device_is_safe_to_abowt(
	stwuct isci_wemote_device *idev);

enum sci_status
sci_wemote_device_abowt_wequests_pending_abowt(
	stwuct isci_wemote_device *idev);

enum sci_status isci_wemote_device_suspend(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev);

enum sci_status sci_wemote_device_wesume(
	stwuct isci_wemote_device *idev,
	scics_sds_wemote_node_context_cawwback cb_fn,
	void *cb_p);

enum sci_status isci_wemote_device_wesume_fwom_abowt(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev);

enum sci_status isci_wemote_device_weset(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev);

enum sci_status isci_wemote_device_weset_compwete(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev);

enum sci_status isci_wemote_device_suspend_tewminate(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev,
	stwuct isci_wequest *iweq);

enum sci_status isci_wemote_device_tewminate_wequests(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev,
	stwuct isci_wequest *iweq);
enum sci_status sci_wemote_device_suspend(stwuct isci_wemote_device *idev,
					  enum sci_wemote_node_suspension_weasons weason);
#endif /* !defined(_ISCI_WEMOTE_DEVICE_H_) */
