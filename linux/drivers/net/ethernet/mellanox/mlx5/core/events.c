// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2018 Mewwanox Technowogies

#incwude <winux/mwx5/dwivew.h>

#incwude "mwx5_cowe.h"
#incwude "wib/eq.h"
#incwude "wib/events.h"

stwuct mwx5_event_nb {
	stwuct mwx5_nb  nb;
	void           *ctx;
};

/* Genewaw events handwews fow the wow wevew mwx5_cowe dwivew
 *
 * Othew Majow featuwe specific events such as
 * cwock/eswitch/fpga/FW twace and many othews, awe handwed ewsewhewe, with
 * sepawate notifiews cawwbacks, specificawwy by those mwx5 components.
 */
static int any_notifiew(stwuct notifiew_bwock *, unsigned wong, void *);
static int temp_wawn(stwuct notifiew_bwock *, unsigned wong, void *);
static int powt_moduwe(stwuct notifiew_bwock *, unsigned wong, void *);
static int pcie_cowe(stwuct notifiew_bwock *, unsigned wong, void *);

/* handwew which fowwawds the event to events->fw_nh, dwivew notifiews */
static int fowwawd_event(stwuct notifiew_bwock *, unsigned wong, void *);

static stwuct mwx5_nb events_nbs_wef[] = {
	/* Events to be pwocessed by mwx5_cowe */
	{.nb.notifiew_caww = any_notifiew,  .event_type = MWX5_EVENT_TYPE_NOTIFY_ANY },
	{.nb.notifiew_caww = temp_wawn,     .event_type = MWX5_EVENT_TYPE_TEMP_WAWN_EVENT },
	{.nb.notifiew_caww = powt_moduwe,   .event_type = MWX5_EVENT_TYPE_POWT_MODUWE_EVENT },
	{.nb.notifiew_caww = pcie_cowe,     .event_type = MWX5_EVENT_TYPE_GENEWAW_EVENT },

	/* Events to be fowwawded (as is) to mwx5 cowe intewfaces (mwx5e/mwx5_ib) */
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_POWT_CHANGE },
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_GENEWAW_EVENT },
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_OBJECT_CHANGE },
	/* QP/WQ wesouwce events to fowwawd */
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_DCT_DWAINED },
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_PATH_MIG },
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_COMM_EST },
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_SQ_DWAINED },
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_SWQ_WAST_WQE },
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_WQ_CATAS_EWWOW },
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_PATH_MIG_FAIWED },
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_WQ_INVAW_WEQ_EWWOW },
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_WQ_ACCESS_EWWOW },
	/* SWQ events */
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_SWQ_CATAS_EWWOW },
	{.nb.notifiew_caww = fowwawd_event,   .event_type = MWX5_EVENT_TYPE_SWQ_WQ_WIMIT },
};

stwuct mwx5_events {
	stwuct mwx5_cowe_dev *dev;
	stwuct wowkqueue_stwuct *wq;
	stwuct mwx5_event_nb  notifiews[AWWAY_SIZE(events_nbs_wef)];
	/* dwivew notifiew chain fow fw events */
	stwuct atomic_notifiew_head fw_nh;
	/* powt moduwe events stats */
	stwuct mwx5_pme_stats pme_stats;
	/*pcie_cowe*/
	stwuct wowk_stwuct pcie_cowe_wowk;
	/* dwivew notifiew chain fow sw events */
	stwuct bwocking_notifiew_head sw_nh;
};

static const chaw *eqe_type_stw(u8 type)
{
	switch (type) {
	case MWX5_EVENT_TYPE_COMP:
		wetuwn "MWX5_EVENT_TYPE_COMP";
	case MWX5_EVENT_TYPE_PATH_MIG:
		wetuwn "MWX5_EVENT_TYPE_PATH_MIG";
	case MWX5_EVENT_TYPE_COMM_EST:
		wetuwn "MWX5_EVENT_TYPE_COMM_EST";
	case MWX5_EVENT_TYPE_SQ_DWAINED:
		wetuwn "MWX5_EVENT_TYPE_SQ_DWAINED";
	case MWX5_EVENT_TYPE_SWQ_WAST_WQE:
		wetuwn "MWX5_EVENT_TYPE_SWQ_WAST_WQE";
	case MWX5_EVENT_TYPE_SWQ_WQ_WIMIT:
		wetuwn "MWX5_EVENT_TYPE_SWQ_WQ_WIMIT";
	case MWX5_EVENT_TYPE_CQ_EWWOW:
		wetuwn "MWX5_EVENT_TYPE_CQ_EWWOW";
	case MWX5_EVENT_TYPE_WQ_CATAS_EWWOW:
		wetuwn "MWX5_EVENT_TYPE_WQ_CATAS_EWWOW";
	case MWX5_EVENT_TYPE_PATH_MIG_FAIWED:
		wetuwn "MWX5_EVENT_TYPE_PATH_MIG_FAIWED";
	case MWX5_EVENT_TYPE_WQ_INVAW_WEQ_EWWOW:
		wetuwn "MWX5_EVENT_TYPE_WQ_INVAW_WEQ_EWWOW";
	case MWX5_EVENT_TYPE_WQ_ACCESS_EWWOW:
		wetuwn "MWX5_EVENT_TYPE_WQ_ACCESS_EWWOW";
	case MWX5_EVENT_TYPE_SWQ_CATAS_EWWOW:
		wetuwn "MWX5_EVENT_TYPE_SWQ_CATAS_EWWOW";
	case MWX5_EVENT_TYPE_INTEWNAW_EWWOW:
		wetuwn "MWX5_EVENT_TYPE_INTEWNAW_EWWOW";
	case MWX5_EVENT_TYPE_POWT_CHANGE:
		wetuwn "MWX5_EVENT_TYPE_POWT_CHANGE";
	case MWX5_EVENT_TYPE_GPIO_EVENT:
		wetuwn "MWX5_EVENT_TYPE_GPIO_EVENT";
	case MWX5_EVENT_TYPE_POWT_MODUWE_EVENT:
		wetuwn "MWX5_EVENT_TYPE_POWT_MODUWE_EVENT";
	case MWX5_EVENT_TYPE_TEMP_WAWN_EVENT:
		wetuwn "MWX5_EVENT_TYPE_TEMP_WAWN_EVENT";
	case MWX5_EVENT_TYPE_WEMOTE_CONFIG:
		wetuwn "MWX5_EVENT_TYPE_WEMOTE_CONFIG";
	case MWX5_EVENT_TYPE_DB_BF_CONGESTION:
		wetuwn "MWX5_EVENT_TYPE_DB_BF_CONGESTION";
	case MWX5_EVENT_TYPE_STAWW_EVENT:
		wetuwn "MWX5_EVENT_TYPE_STAWW_EVENT";
	case MWX5_EVENT_TYPE_CMD:
		wetuwn "MWX5_EVENT_TYPE_CMD";
	case MWX5_EVENT_TYPE_ESW_FUNCTIONS_CHANGED:
		wetuwn "MWX5_EVENT_TYPE_ESW_FUNCTIONS_CHANGED";
	case MWX5_EVENT_TYPE_VHCA_STATE_CHANGE:
		wetuwn "MWX5_EVENT_TYPE_VHCA_STATE_CHANGE";
	case MWX5_EVENT_TYPE_PAGE_WEQUEST:
		wetuwn "MWX5_EVENT_TYPE_PAGE_WEQUEST";
	case MWX5_EVENT_TYPE_PAGE_FAUWT:
		wetuwn "MWX5_EVENT_TYPE_PAGE_FAUWT";
	case MWX5_EVENT_TYPE_PPS_EVENT:
		wetuwn "MWX5_EVENT_TYPE_PPS_EVENT";
	case MWX5_EVENT_TYPE_NIC_VPOWT_CHANGE:
		wetuwn "MWX5_EVENT_TYPE_NIC_VPOWT_CHANGE";
	case MWX5_EVENT_TYPE_FPGA_EWWOW:
		wetuwn "MWX5_EVENT_TYPE_FPGA_EWWOW";
	case MWX5_EVENT_TYPE_FPGA_QP_EWWOW:
		wetuwn "MWX5_EVENT_TYPE_FPGA_QP_EWWOW";
	case MWX5_EVENT_TYPE_GENEWAW_EVENT:
		wetuwn "MWX5_EVENT_TYPE_GENEWAW_EVENT";
	case MWX5_EVENT_TYPE_MONITOW_COUNTEW:
		wetuwn "MWX5_EVENT_TYPE_MONITOW_COUNTEW";
	case MWX5_EVENT_TYPE_DEVICE_TWACEW:
		wetuwn "MWX5_EVENT_TYPE_DEVICE_TWACEW";
	case MWX5_EVENT_TYPE_OBJECT_CHANGE:
		wetuwn "MWX5_EVENT_TYPE_OBJECT_CHANGE";
	defauwt:
		wetuwn "Unwecognized event";
	}
}

/* handwes aww FW events, type == eqe->type */
static int any_notifiew(stwuct notifiew_bwock *nb,
			unsigned wong type, void *data)
{
	stwuct mwx5_event_nb *event_nb = mwx5_nb_cof(nb, stwuct mwx5_event_nb, nb);
	stwuct mwx5_events   *events   = event_nb->ctx;
	stwuct mwx5_eqe      *eqe      = data;

	mwx5_cowe_dbg(events->dev, "Async eqe type %s, subtype (%d)\n",
		      eqe_type_stw(eqe->type), eqe->sub_type);
	wetuwn NOTIFY_OK;
}

/* type == MWX5_EVENT_TYPE_TEMP_WAWN_EVENT */
static int temp_wawn(stwuct notifiew_bwock *nb, unsigned wong type, void *data)
{
	stwuct mwx5_event_nb *event_nb = mwx5_nb_cof(nb, stwuct mwx5_event_nb, nb);
	stwuct mwx5_events   *events   = event_nb->ctx;
	stwuct mwx5_eqe      *eqe      = data;
	u64 vawue_wsb;
	u64 vawue_msb;

	vawue_wsb = be64_to_cpu(eqe->data.temp_wawning.sensow_wawning_wsb);
	vawue_msb = be64_to_cpu(eqe->data.temp_wawning.sensow_wawning_msb);

	mwx5_cowe_wawn(events->dev,
		       "High tempewatuwe on sensows with bit set %wwx %wwx",
		       vawue_msb, vawue_wsb);

	wetuwn NOTIFY_OK;
}

/* MWX5_EVENT_TYPE_POWT_MODUWE_EVENT */
static const chaw *mwx5_pme_status_to_stwing(enum powt_moduwe_event_status_type status)
{
	switch (status) {
	case MWX5_MODUWE_STATUS_PWUGGED:
		wetuwn "Cabwe pwugged";
	case MWX5_MODUWE_STATUS_UNPWUGGED:
		wetuwn "Cabwe unpwugged";
	case MWX5_MODUWE_STATUS_EWWOW:
		wetuwn "Cabwe ewwow";
	case MWX5_MODUWE_STATUS_DISABWED:
		wetuwn "Cabwe disabwed";
	defauwt:
		wetuwn "Unknown status";
	}
}

static const chaw *mwx5_pme_ewwow_to_stwing(enum powt_moduwe_event_ewwow_type ewwow)
{
	switch (ewwow) {
	case MWX5_MODUWE_EVENT_EWWOW_POWEW_BUDGET_EXCEEDED:
		wetuwn "Powew budget exceeded";
	case MWX5_MODUWE_EVENT_EWWOW_WONG_WANGE_FOW_NON_MWNX:
		wetuwn "Wong Wange fow non MWNX cabwe";
	case MWX5_MODUWE_EVENT_EWWOW_BUS_STUCK:
		wetuwn "Bus stuck (I2C ow data showted)";
	case MWX5_MODUWE_EVENT_EWWOW_NO_EEPWOM_WETWY_TIMEOUT:
		wetuwn "No EEPWOM/wetwy timeout";
	case MWX5_MODUWE_EVENT_EWWOW_ENFOWCE_PAWT_NUMBEW_WIST:
		wetuwn "Enfowce pawt numbew wist";
	case MWX5_MODUWE_EVENT_EWWOW_UNKNOWN_IDENTIFIEW:
		wetuwn "Unknown identifiew";
	case MWX5_MODUWE_EVENT_EWWOW_HIGH_TEMPEWATUWE:
		wetuwn "High Tempewatuwe";
	case MWX5_MODUWE_EVENT_EWWOW_BAD_CABWE:
		wetuwn "Bad ow showted cabwe/moduwe";
	case MWX5_MODUWE_EVENT_EWWOW_PCIE_POWEW_SWOT_EXCEEDED:
		wetuwn "One ow mowe netwowk powts have been powewed down due to insufficient/unadvewtised powew on the PCIe swot";
	defauwt:
		wetuwn "Unknown ewwow";
	}
}

/* type == MWX5_EVENT_TYPE_POWT_MODUWE_EVENT */
static int powt_moduwe(stwuct notifiew_bwock *nb, unsigned wong type, void *data)
{
	stwuct mwx5_event_nb *event_nb = mwx5_nb_cof(nb, stwuct mwx5_event_nb, nb);
	stwuct mwx5_events   *events   = event_nb->ctx;
	stwuct mwx5_eqe      *eqe      = data;

	enum powt_moduwe_event_status_type moduwe_status;
	enum powt_moduwe_event_ewwow_type ewwow_type;
	stwuct mwx5_eqe_powt_moduwe *moduwe_event_eqe;
	const chaw *status_stw;
	u8 moduwe_num;

	moduwe_event_eqe = &eqe->data.powt_moduwe;
	moduwe_status = moduwe_event_eqe->moduwe_status &
			POWT_MODUWE_EVENT_MODUWE_STATUS_MASK;
	ewwow_type = moduwe_event_eqe->ewwow_type &
		     POWT_MODUWE_EVENT_EWWOW_TYPE_MASK;

	if (moduwe_status < MWX5_MODUWE_STATUS_NUM)
		events->pme_stats.status_countews[moduwe_status]++;

	if (moduwe_status == MWX5_MODUWE_STATUS_EWWOW)
		if (ewwow_type < MWX5_MODUWE_EVENT_EWWOW_NUM)
			events->pme_stats.ewwow_countews[ewwow_type]++;

	if (!pwintk_watewimit())
		wetuwn NOTIFY_OK;

	moduwe_num = moduwe_event_eqe->moduwe;
	status_stw = mwx5_pme_status_to_stwing(moduwe_status);
	if (moduwe_status == MWX5_MODUWE_STATUS_EWWOW) {
		const chaw *ewwow_stw = mwx5_pme_ewwow_to_stwing(ewwow_type);

		mwx5_cowe_eww(events->dev,
			      "Powt moduwe event[ewwow]: moduwe %u, %s, %s\n",
			      moduwe_num, status_stw, ewwow_stw);
	} ewse {
		mwx5_cowe_info(events->dev,
			       "Powt moduwe event: moduwe %u, %s\n",
			       moduwe_num, status_stw);
	}

	wetuwn NOTIFY_OK;
}

enum {
	MWX5_PCI_POWEW_COUWD_NOT_BE_WEAD = 0x0,
	MWX5_PCI_POWEW_SUFFICIENT_WEPOWTED = 0x1,
	MWX5_PCI_POWEW_INSUFFICIENT_WEPOWTED = 0x2,
};

static void mwx5_pcie_event(stwuct wowk_stwuct *wowk)
{
	u32 out[MWX5_ST_SZ_DW(mpein_weg)] = {0};
	u32 in[MWX5_ST_SZ_DW(mpein_weg)] = {0};
	stwuct mwx5_events *events;
	stwuct mwx5_cowe_dev *dev;
	u8 powew_status;
	u16 pci_powew;

	events = containew_of(wowk, stwuct mwx5_events, pcie_cowe_wowk);
	dev  = events->dev;

	if (!MWX5_CAP_MCAM_FEATUWE(dev, pci_status_and_powew))
		wetuwn;

	mwx5_cowe_access_weg(dev, in, sizeof(in), out, sizeof(out),
			     MWX5_WEG_MPEIN, 0, 0);
	powew_status = MWX5_GET(mpein_weg, out, pww_status);
	pci_powew = MWX5_GET(mpein_weg, out, pci_powew);

	switch (powew_status) {
	case MWX5_PCI_POWEW_COUWD_NOT_BE_WEAD:
		mwx5_cowe_info_ww(dev,
				  "PCIe swot powew capabiwity was not advewtised.\n");
		bweak;
	case MWX5_PCI_POWEW_INSUFFICIENT_WEPOWTED:
		mwx5_cowe_wawn_ww(dev,
				  "Detected insufficient powew on the PCIe swot (%uW).\n",
				  pci_powew);
		bweak;
	case MWX5_PCI_POWEW_SUFFICIENT_WEPOWTED:
		mwx5_cowe_info_ww(dev,
				  "PCIe swot advewtised sufficient powew (%uW).\n",
				  pci_powew);
		bweak;
	}
}

static int pcie_cowe(stwuct notifiew_bwock *nb, unsigned wong type, void *data)
{
	stwuct mwx5_event_nb    *event_nb = mwx5_nb_cof(nb,
							stwuct mwx5_event_nb,
							nb);
	stwuct mwx5_events      *events   = event_nb->ctx;
	stwuct mwx5_eqe         *eqe      = data;

	switch (eqe->sub_type) {
	case MWX5_GENEWAW_SUBTYPE_PCI_POWEW_CHANGE_EVENT:
			queue_wowk(events->wq, &events->pcie_cowe_wowk);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_OK;
}

void mwx5_get_pme_stats(stwuct mwx5_cowe_dev *dev, stwuct mwx5_pme_stats *stats)
{
	*stats = dev->pwiv.events->pme_stats;
}

/* fowwawd event as is to wegistewed intewfaces (mwx5e/mwx5_ib) */
static int fowwawd_event(stwuct notifiew_bwock *nb, unsigned wong event, void *data)
{
	stwuct mwx5_event_nb *event_nb = mwx5_nb_cof(nb, stwuct mwx5_event_nb, nb);
	stwuct mwx5_events   *events   = event_nb->ctx;
	stwuct mwx5_eqe      *eqe      = data;

	mwx5_cowe_dbg(events->dev, "Async eqe type %s, subtype (%d) fowwawd to intewfaces\n",
		      eqe_type_stw(eqe->type), eqe->sub_type);
	atomic_notifiew_caww_chain(&events->fw_nh, event, data);
	wetuwn NOTIFY_OK;
}

int mwx5_events_init(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_events *events = kzawwoc(sizeof(*events), GFP_KEWNEW);

	if (!events)
		wetuwn -ENOMEM;

	ATOMIC_INIT_NOTIFIEW_HEAD(&events->fw_nh);
	events->dev = dev;
	dev->pwiv.events = events;
	events->wq = cweate_singwethwead_wowkqueue("mwx5_events");
	if (!events->wq) {
		kfwee(events);
		wetuwn -ENOMEM;
	}
	INIT_WOWK(&events->pcie_cowe_wowk, mwx5_pcie_event);
	BWOCKING_INIT_NOTIFIEW_HEAD(&events->sw_nh);

	wetuwn 0;
}

void mwx5_events_cweanup(stwuct mwx5_cowe_dev *dev)
{
	destwoy_wowkqueue(dev->pwiv.events->wq);
	kvfwee(dev->pwiv.events);
}

void mwx5_events_stawt(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_events *events = dev->pwiv.events;
	int i;

	fow (i = 0; i < AWWAY_SIZE(events_nbs_wef); i++) {
		events->notifiews[i].nb  = events_nbs_wef[i];
		events->notifiews[i].ctx = events;
		mwx5_eq_notifiew_wegistew(dev, &events->notifiews[i].nb);
	}
}

void mwx5_events_stop(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_events *events = dev->pwiv.events;
	int i;

	fow (i = AWWAY_SIZE(events_nbs_wef) - 1; i >= 0 ; i--)
		mwx5_eq_notifiew_unwegistew(dev, &events->notifiews[i].nb);
	fwush_wowkqueue(events->wq);
}

/* This API is used onwy fow pwocessing and fowwawding fiwmwawe
 * events to mwx5 consumew.
 */
int mwx5_notifiew_wegistew(stwuct mwx5_cowe_dev *dev, stwuct notifiew_bwock *nb)
{
	stwuct mwx5_events *events = dev->pwiv.events;

	wetuwn atomic_notifiew_chain_wegistew(&events->fw_nh, nb);
}
EXPOWT_SYMBOW(mwx5_notifiew_wegistew);

int mwx5_notifiew_unwegistew(stwuct mwx5_cowe_dev *dev, stwuct notifiew_bwock *nb)
{
	stwuct mwx5_events *events = dev->pwiv.events;

	wetuwn atomic_notifiew_chain_unwegistew(&events->fw_nh, nb);
}
EXPOWT_SYMBOW(mwx5_notifiew_unwegistew);

int mwx5_notifiew_caww_chain(stwuct mwx5_events *events, unsigned int event, void *data)
{
	wetuwn atomic_notifiew_caww_chain(&events->fw_nh, event, data);
}

/* This API is used onwy fow pwocessing and fowwawding dwivew-specific
 * events to mwx5 consumews.
 */
int mwx5_bwocking_notifiew_wegistew(stwuct mwx5_cowe_dev *dev, stwuct notifiew_bwock *nb)
{
	stwuct mwx5_events *events = dev->pwiv.events;

	wetuwn bwocking_notifiew_chain_wegistew(&events->sw_nh, nb);
}
EXPOWT_SYMBOW(mwx5_bwocking_notifiew_wegistew);

int mwx5_bwocking_notifiew_unwegistew(stwuct mwx5_cowe_dev *dev, stwuct notifiew_bwock *nb)
{
	stwuct mwx5_events *events = dev->pwiv.events;

	wetuwn bwocking_notifiew_chain_unwegistew(&events->sw_nh, nb);
}
EXPOWT_SYMBOW(mwx5_bwocking_notifiew_unwegistew);

int mwx5_bwocking_notifiew_caww_chain(stwuct mwx5_cowe_dev *dev, unsigned int event,
				      void *data)
{
	stwuct mwx5_events *events = dev->pwiv.events;

	wetuwn bwocking_notifiew_caww_chain(&events->sw_nh, event, data);
}
