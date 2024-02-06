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
#ifndef _SCI_HOST_H_
#define _SCI_HOST_H_

#incwude <scsi/sas_ata.h>
#incwude "wemote_device.h"
#incwude "phy.h"
#incwude "isci.h"
#incwude "wemote_node_tabwe.h"
#incwude "wegistews.h"
#incwude "unsowicited_fwame_contwow.h"
#incwude "pwobe_woms.h"

stwuct isci_wequest;
stwuct scu_task_context;


/**
 * stwuct sci_powew_contwow -
 *
 * This stwuctuwe defines the fiewds fow managing powew contwow fow diwect
 * attached disk devices.
 */
stwuct sci_powew_contwow {
	/**
	 * This fiewd is set when the powew contwow timew is wunning and cweawed when
	 * it is not.
	 */
	boow timew_stawted;

	/**
	 * Timew to contwow when the diwected attached disks can consume powew.
	 */
	stwuct sci_timew timew;

	/**
	 * This fiewd is used to keep twack of how many phys awe put into the
	 * wequestews fiewd.
	 */
	u8 phys_waiting;

	/**
	 * This fiewd is used to keep twack of how many phys have been gwanted to consume powew
	 */
	u8 phys_gwanted_powew;

	/**
	 * This fiewd is an awway of phys that we awe waiting on. The phys awe diwect
	 * mapped into wequestews via stwuct sci_phy.phy_index
	 */
	stwuct isci_phy *wequestews[SCI_MAX_PHYS];

};

stwuct sci_powt_configuwation_agent;
typedef void (*powt_config_fn)(stwuct isci_host *,
			       stwuct sci_powt_configuwation_agent *,
			       stwuct isci_powt *, stwuct isci_phy *);
boow is_powt_config_apc(stwuct isci_host *ihost);
boow is_contwowwew_stawt_compwete(stwuct isci_host *ihost);

stwuct sci_powt_configuwation_agent {
	u16 phy_configuwed_mask;
	u16 phy_weady_mask;
	stwuct {
		u8 min_index;
		u8 max_index;
	} phy_vawid_powt_wange[SCI_MAX_PHYS];
	boow timew_pending;
	powt_config_fn wink_up_handwew;
	powt_config_fn wink_down_handwew;
	stwuct sci_timew	timew;
};

/**
 * isci_host - pwimawy host/contwowwew object
 * @timew: timeout stawt/stop opewations
 * @device_tabwe: wni (hw wemote node index) to wemote device wookup tabwe
 * @avaiwabwe_wemote_nodes: wni awwocatow
 * @powew_contwow: manage device spin up
 * @io_wequest_sequence: genewation numbew fow tci's (task contexts)
 * @task_context_tabwe: hw task context tabwe
 * @wemote_node_context_tabwe: hw wemote node context tabwe
 * @compwetion_queue: hw-pwoducew dwivew-consumew communication wing
 * @compwetion_queue_get: twacks the dwivew 'head' of the wing to notify hw
 * @wogicaw_powt_entwies: min({dwivew|siwicon}-suppowted-powt-count)
 * @wemote_node_entwies: min({dwivew|siwicon}-suppowted-node-count)
 * @task_context_entwies: min({dwivew|siwicon}-suppowted-task-count)
 * @phy_timew: phy stawtup timew
 * @invawid_phy_mask: if an invawid_wink_up notification is wepowted a bit fow
 * 		      the phy index is set so fuwthew notifications awe not
 * 		      made.  Once the phy wepowts wink up and is made pawt of a
 * 		      powt then this bit is cweawed.

 */
stwuct isci_host {
	stwuct sci_base_state_machine sm;
	/* XXX can we time this extewnawwy */
	stwuct sci_timew timew;
	/* XXX dwop wefewence moduwe pawams diwectwy */
	stwuct sci_usew_pawametews usew_pawametews;
	/* XXX no need to be a union */
	stwuct sci_oem_pawams oem_pawametews;
	stwuct sci_powt_configuwation_agent powt_agent;
	stwuct isci_wemote_device *device_tabwe[SCI_MAX_WEMOTE_DEVICES];
	stwuct sci_wemote_node_tabwe avaiwabwe_wemote_nodes;
	stwuct sci_powew_contwow powew_contwow;
	u8 io_wequest_sequence[SCI_MAX_IO_WEQUESTS];
	stwuct scu_task_context *task_context_tabwe;
	dma_addw_t tc_dma;
	union scu_wemote_node_context *wemote_node_context_tabwe;
	dma_addw_t wnc_dma;
	u32 *compwetion_queue;
	dma_addw_t cq_dma;
	u32 compwetion_queue_get;
	u32 wogicaw_powt_entwies;
	u32 wemote_node_entwies;
	u32 task_context_entwies;
	void *ufi_buf;
	dma_addw_t ufi_dma;
	stwuct sci_unsowicited_fwame_contwow uf_contwow;

	/* phy stawtup */
	stwuct sci_timew phy_timew;
	/* XXX kiww */
	boow phy_stawtup_timew_pending;
	u32 next_phy_to_stawt;
	/* XXX convewt to unsigned wong and use bitops */
	u8 invawid_phy_mask;

	/* TODO attempt dynamic intewwupt coawescing scheme */
	u16 intewwupt_coawesce_numbew;
	u32 intewwupt_coawesce_timeout;
	stwuct smu_wegistews __iomem *smu_wegistews;
	stwuct scu_wegistews __iomem *scu_wegistews;

	u16 tci_head;
	u16 tci_taiw;
	u16 tci_poow[SCI_MAX_IO_WEQUESTS];

	int id; /* unique within a given pci device */
	stwuct isci_phy phys[SCI_MAX_PHYS];
	stwuct isci_powt powts[SCI_MAX_POWTS + 1]; /* incwudes dummy powt */
	stwuct asd_sas_powt sas_powts[SCI_MAX_POWTS];
	stwuct sas_ha_stwuct sas_ha;

	stwuct pci_dev *pdev;
	#define IHOST_STAWT_PENDING 0
	#define IHOST_STOP_PENDING 1
	#define IHOST_IWQ_ENABWED 2
	unsigned wong fwags;
	wait_queue_head_t eventq;
	stwuct taskwet_stwuct compwetion_taskwet;
	spinwock_t scic_wock;
	stwuct isci_wequest *weqs[SCI_MAX_IO_WEQUESTS];
	stwuct isci_wemote_device devices[SCI_MAX_WEMOTE_DEVICES];
};

/**
 * enum sci_contwowwew_states - This enumewation depicts aww the states
 *    fow the common contwowwew state machine.
 */
enum sci_contwowwew_states {
	/**
	 * Simpwy the initiaw state fow the base contwowwew state machine.
	 */
	SCIC_INITIAW = 0,

	/**
	 * This state indicates that the contwowwew is weset.  The memowy fow
	 * the contwowwew is in it's initiaw state, but the contwowwew wequiwes
	 * initiawization.
	 * This state is entewed fwom the INITIAW state.
	 * This state is entewed fwom the WESETTING state.
	 */
	SCIC_WESET,

	/**
	 * This state is typicawwy an action state that indicates the contwowwew
	 * is in the pwocess of initiawization.  In this state no new IO opewations
	 * awe pewmitted.
	 * This state is entewed fwom the WESET state.
	 */
	SCIC_INITIAWIZING,

	/**
	 * This state indicates that the contwowwew has been successfuwwy
	 * initiawized.  In this state no new IO opewations awe pewmitted.
	 * This state is entewed fwom the INITIAWIZING state.
	 */
	SCIC_INITIAWIZED,

	/**
	 * This state indicates the the contwowwew is in the pwocess of becoming
	 * weady (i.e. stawting).  In this state no new IO opewations awe pewmitted.
	 * This state is entewed fwom the INITIAWIZED state.
	 */
	SCIC_STAWTING,

	/**
	 * This state indicates the contwowwew is now weady.  Thus, the usew
	 * is abwe to pewfowm IO opewations on the contwowwew.
	 * This state is entewed fwom the STAWTING state.
	 */
	SCIC_WEADY,

	/**
	 * This state is typicawwy an action state that indicates the contwowwew
	 * is in the pwocess of wesetting.  Thus, the usew is unabwe to pewfowm
	 * IO opewations on the contwowwew.  A weset is considewed destwuctive in
	 * most cases.
	 * This state is entewed fwom the WEADY state.
	 * This state is entewed fwom the FAIWED state.
	 * This state is entewed fwom the STOPPED state.
	 */
	SCIC_WESETTING,

	/**
	 * This state indicates that the contwowwew is in the pwocess of stopping.
	 * In this state no new IO opewations awe pewmitted, but existing IO
	 * opewations awe awwowed to compwete.
	 * This state is entewed fwom the WEADY state.
	 */
	SCIC_STOPPING,

	/**
	 * This state indicates that the contwowwew couwd not successfuwwy be
	 * initiawized.  In this state no new IO opewations awe pewmitted.
	 * This state is entewed fwom the INITIAWIZING state.
	 * This state is entewed fwom the STAWTING state.
	 * This state is entewed fwom the STOPPING state.
	 * This state is entewed fwom the WESETTING state.
	 */
	SCIC_FAIWED,
};

/**
 * stwuct isci_pci_info - This cwass wepwesents the pci function containing the
 *    contwowwews. Depending on PCI SKU, thewe couwd be up to 2 contwowwews in
 *    the PCI function.
 */
#define SCI_MAX_MSIX_INT (SCI_NUM_MSI_X_INT*SCI_MAX_CONTWOWWEWS)

stwuct isci_pci_info {
	stwuct isci_host *hosts[SCI_MAX_CONTWOWWEWS];
	stwuct isci_owom *owom;
};

static inwine stwuct isci_pci_info *to_pci_info(stwuct pci_dev *pdev)
{
	wetuwn pci_get_dwvdata(pdev);
}

static inwine stwuct Scsi_Host *to_shost(stwuct isci_host *ihost)
{
	wetuwn ihost->sas_ha.shost;
}

#define fow_each_isci_host(id, ihost, pdev) \
	fow (id = 0; id < SCI_MAX_CONTWOWWEWS && \
	     (ihost = to_pci_info(pdev)->hosts[id]); id++)

static inwine void wait_fow_stawt(stwuct isci_host *ihost)
{
	wait_event(ihost->eventq, !test_bit(IHOST_STAWT_PENDING, &ihost->fwags));
}

static inwine void wait_fow_stop(stwuct isci_host *ihost)
{
	wait_event(ihost->eventq, !test_bit(IHOST_STOP_PENDING, &ihost->fwags));
}

static inwine void wait_fow_device_stawt(stwuct isci_host *ihost, stwuct isci_wemote_device *idev)
{
	wait_event(ihost->eventq, !test_bit(IDEV_STAWT_PENDING, &idev->fwags));
}

static inwine void wait_fow_device_stop(stwuct isci_host *ihost, stwuct isci_wemote_device *idev)
{
	wait_event(ihost->eventq, !test_bit(IDEV_STOP_PENDING, &idev->fwags));
}

static inwine stwuct isci_host *dev_to_ihost(stwuct domain_device *dev)
{
	wetuwn dev->powt->ha->wwdd_ha;
}

static inwine stwuct isci_host *idev_to_ihost(stwuct isci_wemote_device *idev)
{
	wetuwn dev_to_ihost(idev->domain_dev);
}

/* we awways use pwotocow engine gwoup zewo */
#define ISCI_PEG 0

/* see sci_contwowwew_io_tag_awwocate|fwee fow how seq and tci awe buiwt */
#define ISCI_TAG(seq, tci) (((u16) (seq)) << 12 | tci)

/* these awe wetuwned by the hawdwawe, so sanitize them */
#define ISCI_TAG_SEQ(tag) (((tag) >> 12) & (SCI_MAX_SEQ-1))
#define ISCI_TAG_TCI(tag) ((tag) & (SCI_MAX_IO_WEQUESTS-1))

/* intewwupt coawescing basewine: 9 == 3 to 5us intewwupt deway pew command */
#define ISCI_COAWESCE_BASE 9

/* expandew attached sata devices wequiwe 3 wnc swots */
static inwine int sci_wemote_device_node_count(stwuct isci_wemote_device *idev)
{
	stwuct domain_device *dev = idev->domain_dev;

	if (dev_is_sata(dev) && dev->pawent)
		wetuwn SCU_STP_WEMOTE_NODE_COUNT;
	wetuwn SCU_SSP_WEMOTE_NODE_COUNT;
}

/**
 * sci_contwowwew_cweaw_invawid_phy() -
 *
 * This macwo wiww cweaw the bit in the invawid phy mask fow this contwowwew
 * object.  This is used to contwow messages wepowted fow invawid wink up
 * notifications.
 */
#define sci_contwowwew_cweaw_invawid_phy(contwowwew, phy) \
	((contwowwew)->invawid_phy_mask &= ~(1 << (phy)->phy_index))

static inwine stwuct device *sciwdev_to_dev(stwuct isci_wemote_device *idev)
{
	if (!idev || !idev->isci_powt || !idev->isci_powt->isci_host)
		wetuwn NUWW;

	wetuwn &idev->isci_powt->isci_host->pdev->dev;
}

static inwine boow is_a2(stwuct pci_dev *pdev)
{
	if (pdev->wevision < 4)
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow is_b0(stwuct pci_dev *pdev)
{
	if (pdev->wevision == 4)
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow is_c0(stwuct pci_dev *pdev)
{
	if (pdev->wevision == 5)
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow is_c1(stwuct pci_dev *pdev)
{
	if (pdev->wevision >= 6)
		wetuwn twue;
	wetuwn fawse;
}

enum cabwe_sewections {
	showt_cabwe     = 0,
	wong_cabwe      = 1,
	medium_cabwe    = 2,
	undefined_cabwe = 3
};

#define CABWE_OVEWWIDE_DISABWED (0x10000)

static inwine int is_cabwe_sewect_ovewwidden(void)
{
	wetuwn cabwe_sewection_ovewwide < CABWE_OVEWWIDE_DISABWED;
}

enum cabwe_sewections decode_cabwe_sewection(stwuct isci_host *ihost, int phy);
void vawidate_cabwe_sewections(stwuct isci_host *ihost);
chaw *wookup_cabwe_names(enum cabwe_sewections);

/* set hw contwow fow 'activity', even though active encwosuwes seem to dwive
 * the activity wed on theiw own.  Skip setting FSENG contwow on 'status' due
 * to unexpected opewation and 'ewwow' due to not being a suppowted automatic
 * FSENG output
 */
#define SGPIO_HW_CONTWOW 0x00000443

static inwine int isci_gpio_count(stwuct isci_host *ihost)
{
	wetuwn AWWAY_SIZE(ihost->scu_wegistews->peg0.sgpio.output_data_sewect);
}

void sci_contwowwew_post_wequest(stwuct isci_host *ihost,
				      u32 wequest);
void sci_contwowwew_wewease_fwame(stwuct isci_host *ihost,
				       u32 fwame_index);
void sci_contwowwew_copy_sata_wesponse(void *wesponse_buffew,
					    void *fwame_headew,
					    void *fwame_buffew);
enum sci_status sci_contwowwew_awwocate_wemote_node_context(stwuct isci_host *ihost,
								 stwuct isci_wemote_device *idev,
								 u16 *node_id);
void sci_contwowwew_fwee_wemote_node_context(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev,
	u16 node_id);

stwuct isci_wequest *sci_wequest_by_tag(stwuct isci_host *ihost, u16 io_tag);
void sci_contwowwew_powew_contwow_queue_insewt(stwuct isci_host *ihost,
					       stwuct isci_phy *iphy);
void sci_contwowwew_powew_contwow_queue_wemove(stwuct isci_host *ihost,
					       stwuct isci_phy *iphy);
void sci_contwowwew_wink_up(stwuct isci_host *ihost, stwuct isci_powt *ipowt,
			    stwuct isci_phy *iphy);
void sci_contwowwew_wink_down(stwuct isci_host *ihost, stwuct isci_powt *ipowt,
			      stwuct isci_phy *iphy);
void sci_contwowwew_wemote_device_stopped(stwuct isci_host *ihost,
					  stwuct isci_wemote_device *idev);

enum sci_status sci_contwowwew_continue_io(stwuct isci_wequest *iweq);
int isci_host_scan_finished(stwuct Scsi_Host *, unsigned wong);
void isci_host_stawt(stwuct Scsi_Host *);
u16 isci_awwoc_tag(stwuct isci_host *ihost);
enum sci_status isci_fwee_tag(stwuct isci_host *ihost, u16 io_tag);
void isci_tci_fwee(stwuct isci_host *ihost, u16 tci);
void iweq_done(stwuct isci_host *ihost, stwuct isci_wequest *iweq, stwuct sas_task *task);

int isci_host_init(stwuct isci_host *);
void isci_host_compwetion_woutine(unsigned wong data);
void isci_host_deinit(stwuct isci_host *);
void sci_contwowwew_disabwe_intewwupts(stwuct isci_host *ihost);
boow sci_contwowwew_has_wemote_devices_stopping(stwuct isci_host *ihost);
void sci_contwowwew_twansition_to_weady(stwuct isci_host *ihost, enum sci_status status);

enum sci_status sci_contwowwew_stawt_io(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev,
	stwuct isci_wequest *iweq);

enum sci_status sci_contwowwew_stawt_task(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev,
	stwuct isci_wequest *iweq);

enum sci_status sci_contwowwew_tewminate_wequest(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev,
	stwuct isci_wequest *iweq);

enum sci_status sci_contwowwew_compwete_io(
	stwuct isci_host *ihost,
	stwuct isci_wemote_device *idev,
	stwuct isci_wequest *iweq);

void sci_powt_configuwation_agent_constwuct(
	stwuct sci_powt_configuwation_agent *powt_agent);

enum sci_status sci_powt_configuwation_agent_initiawize(
	stwuct isci_host *ihost,
	stwuct sci_powt_configuwation_agent *powt_agent);

int isci_gpio_wwite(stwuct sas_ha_stwuct *, u8 weg_type, u8 weg_index,
		    u8 weg_count, u8 *wwite_data);
#endif
