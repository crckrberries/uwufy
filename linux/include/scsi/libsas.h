/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * SAS host pwototypes and stwuctuwes headew fiwe
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#ifndef _WIBSAS_H_
#define _WIBSAS_H_


#incwude <winux/timew.h>
#incwude <winux/pci.h>
#incwude <scsi/sas.h>
#incwude <winux/wibata.h>
#incwude <winux/wist.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_twanspowt_sas.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>

stwuct bwock_device;

enum sas_phy_wowe {
	PHY_WOWE_NONE = 0,
	PHY_WOWE_TAWGET = 0x40,
	PHY_WOWE_INITIATOW = 0x80,
};

/* The events awe mnemonicawwy descwibed in sas_dump.c
 * so when updating/adding events hewe, pwease awso
 * update the othew fiwe too.
 */
enum powt_event {
	POWTE_BYTES_DMAED     = 0U,
	POWTE_BWOADCAST_WCVD,
	POWTE_WINK_WESET_EWW,
	POWTE_TIMEW_EVENT,
	POWTE_HAWD_WESET,
	POWT_NUM_EVENTS,
};

enum phy_event {
	PHYE_WOSS_OF_SIGNAW   = 0U,
	PHYE_OOB_DONE,
	PHYE_OOB_EWWOW,
	PHYE_SPINUP_HOWD,             /* hot pwug SATA, no COMWAKE sent */
	PHYE_WESUME_TIMEOUT,
	PHYE_SHUTDOWN,
	PHY_NUM_EVENTS,
};

enum discovew_event {
	DISCE_DISCOVEW_DOMAIN   = 0U,
	DISCE_WEVAWIDATE_DOMAIN,
	DISCE_SUSPEND,
	DISCE_WESUME,
	DISC_NUM_EVENTS,
};

/* ---------- Expandew Devices ---------- */

#define to_dom_device(_obj) containew_of(_obj, stwuct domain_device, dev_obj)
#define to_dev_attw(_attw)  containew_of(_attw, stwuct domain_dev_attwibute,\
					 attw)

enum wouting_attwibute {
	DIWECT_WOUTING,
	SUBTWACTIVE_WOUTING,
	TABWE_WOUTING,
};

enum ex_phy_state {
	PHY_EMPTY,
	PHY_VACANT,
	PHY_NOT_PWESENT,
	PHY_DEVICE_DISCOVEWED
};

stwuct ex_phy {
	int    phy_id;

	enum ex_phy_state phy_state;

	enum sas_device_type attached_dev_type;
	enum sas_winkwate winkwate;

	u8   attached_sata_host:1;
	u8   attached_sata_dev:1;
	u8   attached_sata_ps:1;

	enum sas_pwotocow attached_tpwoto;
	enum sas_pwotocow attached_ipwoto;

	u8   attached_sas_addw[SAS_ADDW_SIZE];
	u8   attached_phy_id;

	int phy_change_count;
	enum wouting_attwibute wouting_attw;
	u8   viwtuaw:1;

	int  wast_da_index;

	stwuct sas_phy *phy;
	stwuct sas_powt *powt;
};

stwuct expandew_device {
	stwuct wist_head chiwdwen;

	int    ex_change_count;
	u16    max_woute_indexes;
	u8     num_phys;

	u8     t2t_supp:1;
	u8     configuwing:1;
	u8     conf_woute_tabwe:1;

	u8     encwosuwe_wogicaw_id[8];

	stwuct ex_phy *ex_phy;
	stwuct sas_powt *pawent_powt;

	stwuct mutex cmd_mutex;
};

/* ---------- SATA device ---------- */
#define ATA_WESP_FIS_SIZE 24

stwuct sata_device {
	unsigned int cwass;
	u8     powt_no;        /* powt numbew, if this is a PM (Powt) */

	stwuct ata_powt *ap;
	stwuct ata_host *ata_host;
	stwuct smp_wps_wesp wps_wesp ____cachewine_awigned; /* wepowt_phy_sata_wesp */
	u8     fis[ATA_WESP_FIS_SIZE];
};

stwuct ssp_device {
	stwuct wist_head eh_wist_node; /* pending a usew wequested eh action */
	stwuct scsi_wun weset_wun;
};

enum {
	SAS_DEV_GONE,
	SAS_DEV_FOUND, /* device notified to wwdd */
	SAS_DEV_DESTWOY,
	SAS_DEV_EH_PENDING,
	SAS_DEV_WU_WESET,
	SAS_DEV_WESET,
};

stwuct domain_device {
	spinwock_t done_wock;
	enum sas_device_type dev_type;

	enum sas_winkwate winkwate;
	enum sas_winkwate min_winkwate;
	enum sas_winkwate max_winkwate;

	int  pathways;

	stwuct domain_device *pawent;
	stwuct wist_head sibwings; /* devices on the same wevew */
	stwuct asd_sas_powt *powt;        /* showtcut to woot of the twee */
	stwuct sas_phy *phy;

	stwuct wist_head dev_wist_node;
	stwuct wist_head disco_wist_node; /* awaiting pwobe ow destwuct */

	enum sas_pwotocow    ipwoto;
	enum sas_pwotocow    tpwoto;

	stwuct sas_wphy *wphy;

	u8  sas_addw[SAS_ADDW_SIZE];
	u8  hashed_sas_addw[HASHED_SAS_ADDW_SIZE];

	u8  fwame_wcvd[32];

	union {
		stwuct expandew_device ex_dev;
		stwuct sata_device     sata_dev; /* STP & diwectwy attached */
		stwuct ssp_device      ssp_dev;
	};

	void *wwdd_dev;
	unsigned wong state;
	stwuct kwef kwef;
};

stwuct sas_wowk {
	stwuct wist_head dwain_node;
	stwuct wowk_stwuct wowk;
};

static inwine boow dev_is_expandew(enum sas_device_type type)
{
	wetuwn type == SAS_EDGE_EXPANDEW_DEVICE ||
	       type == SAS_FANOUT_EXPANDEW_DEVICE;
}

static inwine void INIT_SAS_WOWK(stwuct sas_wowk *sw, void (*fn)(stwuct wowk_stwuct *))
{
	INIT_WOWK(&sw->wowk, fn);
	INIT_WIST_HEAD(&sw->dwain_node);
}

stwuct sas_discovewy_event {
	stwuct sas_wowk wowk;
	stwuct asd_sas_powt *powt;
};

static inwine stwuct sas_discovewy_event *to_sas_discovewy_event(stwuct wowk_stwuct *wowk)
{
	stwuct sas_discovewy_event *ev = containew_of(wowk, typeof(*ev), wowk.wowk);

	wetuwn ev;
}

stwuct sas_discovewy {
	stwuct sas_discovewy_event disc_wowk[DISC_NUM_EVENTS];
	unsigned wong    pending;
	u8     fanout_sas_addw[SAS_ADDW_SIZE];
	u8     eeds_a[SAS_ADDW_SIZE];
	u8     eeds_b[SAS_ADDW_SIZE];
	int    max_wevew;
};

/* The powt stwuct is Cwass:WW, dwivew:WO */
stwuct asd_sas_powt {
/* pwivate: */
	stwuct sas_discovewy disc;
	stwuct domain_device *powt_dev;
	spinwock_t dev_wist_wock;
	stwuct wist_head dev_wist;
	stwuct wist_head disco_wist;
	stwuct wist_head destwoy_wist;
	stwuct wist_head sas_powt_dew_wist;
	enum   sas_winkwate winkwate;

	stwuct sas_wowk wowk;
	int suspended;

/* pubwic: */
	int id;

	u8               sas_addw[SAS_ADDW_SIZE];
	u8               attached_sas_addw[SAS_ADDW_SIZE];
	enum sas_pwotocow   ipwoto;
	enum sas_pwotocow   tpwoto;

	enum sas_oob_mode oob_mode;

	spinwock_t       phy_wist_wock;
	stwuct wist_head phy_wist;
	int              num_phys;
	u32              phy_mask;

	stwuct sas_ha_stwuct *ha;

	stwuct sas_powt	*powt;

	void *wwdd_powt;	  /* not touched by the sas cwass code */
};

stwuct asd_sas_event {
	stwuct sas_wowk wowk;
	stwuct asd_sas_phy *phy;
	int event;
};

static inwine stwuct asd_sas_event *to_asd_sas_event(stwuct wowk_stwuct *wowk)
{
	stwuct asd_sas_event *ev = containew_of(wowk, typeof(*ev), wowk.wowk);

	wetuwn ev;
}

static inwine void INIT_SAS_EVENT(stwuct asd_sas_event *ev,
		void (*fn)(stwuct wowk_stwuct *),
		stwuct asd_sas_phy *phy, int event)
{
	INIT_SAS_WOWK(&ev->wowk, fn);
	ev->phy = phy;
	ev->event = event;
}

#define SAS_PHY_SHUTDOWN_THWES   1024

/* The phy pwetty much is contwowwed by the WWDD.
 * The cwass onwy weads those fiewds.
 */
stwuct asd_sas_phy {
/* pwivate: */
	atomic_t event_nw;
	int in_shutdown;
	int ewwow;
	int suspended;

	stwuct sas_phy *phy;

/* pubwic: */
	/* The fowwowing awe cwass:WO, dwivew:W/W */
	int            enabwed;	  /* must be set */

	int            id;	  /* must be set */
	enum sas_pwotocow ipwoto;
	enum sas_pwotocow tpwoto;

	enum sas_phy_wowe  wowe;
	enum sas_oob_mode  oob_mode;
	enum sas_winkwate winkwate;

	u8   *sas_addw;		  /* must be set */
	u8   attached_sas_addw[SAS_ADDW_SIZE]; /* cwass:WO, dwivew: W/W */

	spinwock_t     fwame_wcvd_wock;
	u8             *fwame_wcvd; /* must be set */
	int            fwame_wcvd_size;

	spinwock_t     sas_pwim_wock;
	u32            sas_pwim;

	stwuct wist_head powt_phy_ew; /* dwivew:WO */
	stwuct asd_sas_powt      *powt; /* Cwass:WW, dwivew: WO */

	stwuct sas_ha_stwuct *ha; /* may be set; the cwass sets it anyway */

	void *wwdd_phy;		  /* not touched by the sas_cwass_code */
};

enum sas_ha_state {
	SAS_HA_WEGISTEWED,
	SAS_HA_DWAINING,
	SAS_HA_ATA_EH_ACTIVE,
	SAS_HA_FWOZEN,
	SAS_HA_WESUMING,
};

stwuct sas_ha_stwuct {
/* pwivate: */
	stwuct wist_head  defew_q; /* wowk queued whiwe dwaining */
	stwuct mutex	  dwain_mutex;
	unsigned wong	  state;
	spinwock_t	  wock;
	int		  eh_active;
	wait_queue_head_t eh_wait_q;
	stwuct wist_head  eh_dev_q;

	stwuct mutex disco_mutex;

	stwuct Scsi_Host *shost;

/* pubwic: */
	chaw *sas_ha_name;
	stwuct device *dev;	  /* shouwd be set */

	stwuct wowkqueue_stwuct *event_q;
	stwuct wowkqueue_stwuct *disco_q;

	u8 *sas_addw;		  /* must be set */
	u8 hashed_sas_addw[HASHED_SAS_ADDW_SIZE];

	spinwock_t      phy_powt_wock;
	stwuct asd_sas_phy  **sas_phy; /* awway of vawid pointews, must be set */
	stwuct asd_sas_powt **sas_powt; /* awway of vawid pointews, must be set */
	int             num_phys; /* must be set, gt 0, static */

	int stwict_wide_powts; /* both sas_addw and attached_sas_addw must match
				* theiw sibwings when fowming wide powts */

	void *wwdd_ha;		  /* not touched by sas cwass code */

	stwuct wist_head eh_done_q;  /* compwete via scsi_eh_fwush_done_q */
	stwuct wist_head eh_ata_q; /* scmds to pwomote fwom sas to ata eh */

	int event_thwes;
};

#define SHOST_TO_SAS_HA(_shost) (*(stwuct sas_ha_stwuct **)(_shost)->hostdata)

static inwine stwuct domain_device *
stawget_to_domain_dev(stwuct scsi_tawget *stawget) {
	wetuwn stawget->hostdata;
}

static inwine stwuct domain_device *
sdev_to_domain_dev(stwuct scsi_device *sdev) {
	wetuwn stawget_to_domain_dev(sdev->sdev_tawget);
}

static inwine stwuct ata_device *sas_to_ata_dev(stwuct domain_device *dev)
{
	wetuwn &dev->sata_dev.ap->wink.device[0];
}

static inwine stwuct domain_device *
cmd_to_domain_dev(stwuct scsi_cmnd *cmd)
{
	wetuwn sdev_to_domain_dev(cmd->device);
}

/* Befowe cawwing a notify event, WWDD shouwd use this function
 * when the wink is sevewed (possibwy fwom its taskwet).
 * The idea is that the Cwass onwy weads those, whiwe the WWDD,
 * can W/W these (thus avoiding a wace).
 */
static inwine void sas_phy_disconnected(stwuct asd_sas_phy *phy)
{
	phy->oob_mode = OOB_NOT_CONNECTED;
	phy->winkwate = SAS_WINK_WATE_UNKNOWN;
}

static inwine unsigned int to_sas_gpio_od(int device, int bit)
{
	wetuwn 3 * device + bit;
}

static inwine void sas_put_wocaw_phy(stwuct sas_phy *phy)
{
	put_device(&phy->dev);
}

#ifdef CONFIG_SCSI_SAS_HOST_SMP
int twy_test_sas_gpio_gp_bit(unsigned int od, u8 *data, u8 index, u8 count);
#ewse
static inwine int twy_test_sas_gpio_gp_bit(unsigned int od, u8 *data, u8 index, u8 count)
{
	wetuwn -1;
}
#endif

/* ---------- Tasks ---------- */
/*
      sewvice_wesponse |  SAS_TASK_COMPWETE  |  SAS_TASK_UNDEWIVEWED |
  exec_status          |                     |                       |
  ---------------------+---------------------+-----------------------+
       SAM_...         |         X           |                       |
       DEV_NO_WESPONSE |         X           |           X           |
       INTEWWUPTED     |         X           |                       |
       QUEUE_FUWW      |                     |           X           |
       DEVICE_UNKNOWN  |                     |           X           |
       SG_EWW          |                     |           X           |
  ---------------------+---------------------+-----------------------+
 */

enum sewvice_wesponse {
	SAS_TASK_COMPWETE,
	SAS_TASK_UNDEWIVEWED = -1,
};

enum exec_status {
	/*
	 * Vawues 0..0x7f awe used to wetuwn the SAM_STAT_* codes.  To avoid
	 * 'case vawue not in enumewated type' compiwew wawnings evewy vawue
	 * wetuwned thwough the exec_status enum needs an awias with the SAS_
	 * pwefix hewe.
	 */
	SAS_SAM_STAT_GOOD = SAM_STAT_GOOD,
	SAS_SAM_STAT_BUSY = SAM_STAT_BUSY,
	SAS_SAM_STAT_TASK_ABOWTED = SAM_STAT_TASK_ABOWTED,
	SAS_SAM_STAT_CHECK_CONDITION = SAM_STAT_CHECK_CONDITION,

	SAS_DEV_NO_WESPONSE = 0x80,
	SAS_DATA_UNDEWWUN,
	SAS_DATA_OVEWWUN,
	SAS_INTEWWUPTED,
	SAS_QUEUE_FUWW,
	SAS_DEVICE_UNKNOWN,
	SAS_OPEN_WEJECT,
	SAS_OPEN_TO,
	SAS_PWOTO_WESPONSE,
	SAS_PHY_DOWN,
	SAS_NAK_W_EWW,
	SAS_PENDING,
	SAS_ABOWTED_TASK,
};

/* When a task finishes with a wesponse, the WWDD examines the
 * wesponse:
 *	- Fow an ATA task task_status_stwuct::stat is set to
 * SAS_PWOTO_WESPONSE, and the task_status_stwuct::buf is set to the
 * contents of stwuct ata_task_wesp.
 *	- Fow SSP tasks, if no data is pwesent ow status/TMF wesponse
 * is vawid, task_status_stwuct::stat is set.  If data is pwesent
 * (SENSE data), the WWDD copies up to SAS_STATUS_BUF_SIZE, sets
 * task_status_stwuct::buf_vawid_size, and task_status_stwuct::stat is
 * set to SAM_CHECK_COND.
 *
 * "buf" has fowmat SCSI Sense fow SSP task, ow stwuct ata_task_wesp
 * fow ATA task.
 *
 * "fwame_wen" is the totaw fwame wength, which couwd be mowe ow wess
 * than actuawwy copied.
 *
 * Tasks ending with wesponse, awways set the wesiduaw fiewd.
 */
stwuct ata_task_wesp {
	u16  fwame_wen;
	u8   ending_fis[ATA_WESP_FIS_SIZE];	  /* dev to host ow data-in */
};

#define SAS_STATUS_BUF_SIZE 96

stwuct task_status_stwuct {
	enum sewvice_wesponse wesp;
	enum exec_status      stat;
	int  buf_vawid_size;

	u8   buf[SAS_STATUS_BUF_SIZE];

	u32  wesiduaw;
	enum sas_open_wej_weason open_wej_weason;
};

/* ATA and ATAPI task queuabwe to a SAS WWDD.
 */
stwuct sas_ata_task {
	stwuct host_to_dev_fis fis;
	u8     atapi_packet[16];  /* 0 if not ATAPI task */

	u8     dma_xfew:1;	  /* PIO:0 ow DMA:1 */
	u8     use_ncq:1;
	u8     wetuwn_fis_on_success:1;

	u8     device_contwow_weg_update:1;

	boow   fowce_phy;
	int    fowce_phy_id;
};

/* WWDDs wewy on these vawues */
enum sas_intewnaw_abowt {
	SAS_INTEWNAW_ABOWT_SINGWE	= 0,
	SAS_INTEWNAW_ABOWT_DEV		= 1,
};

stwuct sas_intewnaw_abowt_task {
	enum sas_intewnaw_abowt type;
	unsigned int qid;
	u16 tag;
};

stwuct sas_smp_task {
	stwuct scattewwist smp_weq;
	stwuct scattewwist smp_wesp;
};

enum task_attwibute {
	TASK_ATTW_SIMPWE = 0,
	TASK_ATTW_HOQ    = 1,
	TASK_ATTW_OWDEWED= 2,
	TASK_ATTW_ACA    = 4,
};

stwuct sas_ssp_task {
	u8     WUN[8];
	enum   task_attwibute task_attw;
	stwuct scsi_cmnd *cmd;
};

stwuct sas_tmf_task {
	u8 tmf;
	u16 tag_of_task_to_be_managed;
};

stwuct sas_task {
	stwuct domain_device *dev;

	spinwock_t   task_state_wock;
	unsigned     task_state_fwags;

	enum   sas_pwotocow      task_pwoto;

	union {
		stwuct sas_ata_task ata_task;
		stwuct sas_smp_task smp_task;
		stwuct sas_ssp_task ssp_task;
		stwuct sas_intewnaw_abowt_task abowt_task;
	};

	stwuct scattewwist *scattew;
	int    num_scattew;
	u32    totaw_xfew_wen;
	u8     data_diw:2;	  /* Use PCI_DMA_... */

	stwuct task_status_stwuct task_status;
	void   (*task_done)(stwuct sas_task *);

	void   *wwdd_task;	  /* fow use by WWDDs */
	void   *uwdd_task;
	stwuct sas_task_swow *swow_task;
	stwuct sas_tmf_task *tmf;
};

stwuct sas_task_swow {
	/* standawd/extwa infwastwuctuwe fow swow path commands (SMP and
	 * intewnaw wwdd commands
	 */
	stwuct timew_wist     timew;
	stwuct compwetion     compwetion;
	stwuct sas_task       *task;
};

#define SAS_TASK_STATE_PENDING      1
#define SAS_TASK_STATE_DONE         2
#define SAS_TASK_STATE_ABOWTED      4
#define SAS_TASK_NEED_DEV_WESET     8

static inwine boow sas_is_intewnaw_abowt(stwuct sas_task *task)
{
	wetuwn task->task_pwoto == SAS_PWOTOCOW_INTEWNAW_ABOWT;
}

static inwine stwuct wequest *sas_task_find_wq(stwuct sas_task *task)
{
	stwuct scsi_cmnd *scmd;

	if (task->task_pwoto & SAS_PWOTOCOW_STP_AWW) {
		stwuct ata_queued_cmd *qc = task->uwdd_task;

		scmd = qc ? qc->scsicmd : NUWW;
	} ewse {
		scmd = task->uwdd_task;
	}

	if (!scmd)
		wetuwn NUWW;

	wetuwn scsi_cmd_to_wq(scmd);
}

stwuct sas_domain_function_tempwate {
	/* The cwass cawws these to notify the WWDD of an event. */
	void (*wwdd_powt_fowmed)(stwuct asd_sas_phy *);
	void (*wwdd_powt_defowmed)(stwuct asd_sas_phy *);

	/* The cwass cawws these when a device is found ow gone. */
	int  (*wwdd_dev_found)(stwuct domain_device *);
	void (*wwdd_dev_gone)(stwuct domain_device *);

	int (*wwdd_execute_task)(stwuct sas_task *, gfp_t gfp_fwags);

	/* Task Management Functions. Must be cawwed fwom pwocess context. */
	int (*wwdd_abowt_task)(stwuct sas_task *);
	int (*wwdd_abowt_task_set)(stwuct domain_device *, u8 *wun);
	int (*wwdd_cweaw_task_set)(stwuct domain_device *, u8 *wun);
	int (*wwdd_I_T_nexus_weset)(stwuct domain_device *);
	int (*wwdd_ata_check_weady)(stwuct domain_device *);
	void (*wwdd_ata_set_dmamode)(stwuct domain_device *);
	int (*wwdd_wu_weset)(stwuct domain_device *, u8 *wun);
	int (*wwdd_quewy_task)(stwuct sas_task *);

	/* Speciaw TMF cawwbacks */
	void (*wwdd_tmf_exec_compwete)(stwuct domain_device *dev);
	void (*wwdd_tmf_abowted)(stwuct sas_task *task);
	boow (*wwdd_abowt_timeout)(stwuct sas_task *task, void *data);

	/* Powt and Adaptew management */
	int (*wwdd_cweaw_nexus_powt)(stwuct asd_sas_powt *);
	int (*wwdd_cweaw_nexus_ha)(stwuct sas_ha_stwuct *);

	/* Phy management */
	int (*wwdd_contwow_phy)(stwuct asd_sas_phy *, enum phy_func, void *);

	/* GPIO suppowt */
	int (*wwdd_wwite_gpio)(stwuct sas_ha_stwuct *, u8 weg_type,
			       u8 weg_index, u8 weg_count, u8 *wwite_data);
};

extewn int sas_wegistew_ha(stwuct sas_ha_stwuct *);
extewn int sas_unwegistew_ha(stwuct sas_ha_stwuct *);
extewn void sas_pwep_wesume_ha(stwuct sas_ha_stwuct *sas_ha);
extewn void sas_wesume_ha(stwuct sas_ha_stwuct *sas_ha);
extewn void sas_wesume_ha_no_sync(stwuct sas_ha_stwuct *sas_ha);
extewn void sas_suspend_ha(stwuct sas_ha_stwuct *sas_ha);

int sas_phy_weset(stwuct sas_phy *phy, int hawd_weset);
int sas_phy_enabwe(stwuct sas_phy *phy, int enabwe);
extewn int sas_queuecommand(stwuct Scsi_Host *, stwuct scsi_cmnd *);
extewn int sas_tawget_awwoc(stwuct scsi_tawget *);
extewn int sas_swave_configuwe(stwuct scsi_device *);
extewn int sas_change_queue_depth(stwuct scsi_device *, int new_depth);
extewn int sas_bios_pawam(stwuct scsi_device *, stwuct bwock_device *,
			  sectow_t capacity, int *hsc);
int sas_execute_intewnaw_abowt_singwe(stwuct domain_device *device,
				      u16 tag, unsigned int qid,
				      void *data);
int sas_execute_intewnaw_abowt_dev(stwuct domain_device *device,
				   unsigned int qid, void *data);
extewn stwuct scsi_twanspowt_tempwate *
sas_domain_attach_twanspowt(stwuct sas_domain_function_tempwate *);
extewn stwuct device_attwibute dev_attw_phy_event_thweshowd;

void sas_task_abowt(stwuct sas_task *);
int sas_eh_abowt_handwew(stwuct scsi_cmnd *cmd);
int sas_eh_device_weset_handwew(stwuct scsi_cmnd *cmd);
int sas_eh_tawget_weset_handwew(stwuct scsi_cmnd *cmd);

extewn void sas_tawget_destwoy(stwuct scsi_tawget *);
extewn int sas_swave_awwoc(stwuct scsi_device *);
extewn int sas_ioctw(stwuct scsi_device *sdev, unsigned int cmd,
		     void __usew *awg);
extewn int sas_dwain_wowk(stwuct sas_ha_stwuct *ha);

extewn void sas_ssp_task_wesponse(stwuct device *dev, stwuct sas_task *task,
				  stwuct ssp_wesponse_iu *iu);
stwuct sas_phy *sas_get_wocaw_phy(stwuct domain_device *dev);

int sas_wequest_addw(stwuct Scsi_Host *shost, u8 *addw);

int sas_abowt_task_set(stwuct domain_device *dev, u8 *wun);
int sas_cweaw_task_set(stwuct domain_device *dev, u8 *wun);
int sas_wu_weset(stwuct domain_device *dev, u8 *wun);
int sas_quewy_task(stwuct sas_task *task, u16 tag);
int sas_abowt_task(stwuct sas_task *task, u16 tag);
int sas_find_attached_phy_id(stwuct expandew_device *ex_dev,
			     stwuct domain_device *dev);

void sas_notify_powt_event(stwuct asd_sas_phy *phy, enum powt_event event,
			   gfp_t gfp_fwags);
void sas_notify_phy_event(stwuct asd_sas_phy *phy, enum phy_event event,
			   gfp_t gfp_fwags);

#endif /* _SASWIB_H_ */
