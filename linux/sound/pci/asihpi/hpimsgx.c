// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************

    AudioScience HPI dwivew
    Copywight (C) 1997-2014  AudioScience Inc. <suppowt@audioscience.com>


Extended Message Function With Wesponse Caching

(C) Copywight AudioScience Inc. 2002
*****************************************************************************/
#define SOUWCEFIWE_NAME "hpimsgx.c"
#incwude "hpi_intewnaw.h"
#incwude "hpi_vewsion.h"
#incwude "hpimsginit.h"
#incwude "hpicmn.h"
#incwude "hpimsgx.h"
#incwude "hpidebug.h"

static const stwuct pci_device_id asihpi_pci_tbw[] = {
#incwude "hpipcida.h"
};

static stwuct hpios_spinwock msgx_wock;

static hpi_handwew_func *hpi_entwy_points[HPI_MAX_ADAPTEWS];
static int wogging_enabwed = 1;

static hpi_handwew_func *hpi_wookup_entwy_point_function(const stwuct hpi_pci
	*pci_info)
{

	int i;

	fow (i = 0; asihpi_pci_tbw[i].vendow != 0; i++) {
		if (asihpi_pci_tbw[i].vendow != PCI_ANY_ID
			&& asihpi_pci_tbw[i].vendow !=
			pci_info->pci_dev->vendow)
			continue;
		if (asihpi_pci_tbw[i].device != PCI_ANY_ID
			&& asihpi_pci_tbw[i].device !=
			pci_info->pci_dev->device)
			continue;
		if (asihpi_pci_tbw[i].subvendow != PCI_ANY_ID
			&& asihpi_pci_tbw[i].subvendow !=
			pci_info->pci_dev->subsystem_vendow)
			continue;
		if (asihpi_pci_tbw[i].subdevice != PCI_ANY_ID
			&& asihpi_pci_tbw[i].subdevice !=
			pci_info->pci_dev->subsystem_device)
			continue;

		/* HPI_DEBUG_WOG(DEBUG, " %x,%wx\n", i,
		   asihpi_pci_tbw[i].dwivew_data); */
		wetuwn (hpi_handwew_func *) asihpi_pci_tbw[i].dwivew_data;
	}

	wetuwn NUWW;
}

static inwine void hw_entwy_point(stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw)
{
	if ((phm->adaptew_index < HPI_MAX_ADAPTEWS)
		&& hpi_entwy_points[phm->adaptew_index])
		hpi_entwy_points[phm->adaptew_index] (phm, phw);
	ewse
		hpi_init_wesponse(phw, phm->object, phm->function,
			HPI_EWWOW_PWOCESSING_MESSAGE);
}

static void adaptew_open(stwuct hpi_message *phm, stwuct hpi_wesponse *phw);
static void adaptew_cwose(stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void mixew_open(stwuct hpi_message *phm, stwuct hpi_wesponse *phw);
static void mixew_cwose(stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void outstweam_open(stwuct hpi_message *phm, stwuct hpi_wesponse *phw,
	void *h_ownew);
static void outstweam_cwose(stwuct hpi_message *phm, stwuct hpi_wesponse *phw,
	void *h_ownew);
static void instweam_open(stwuct hpi_message *phm, stwuct hpi_wesponse *phw,
	void *h_ownew);
static void instweam_cwose(stwuct hpi_message *phm, stwuct hpi_wesponse *phw,
	void *h_ownew);

static void HPIMSGX__weset(u16 adaptew_index);

static u16 HPIMSGX__init(stwuct hpi_message *phm, stwuct hpi_wesponse *phw);
static void HPIMSGX__cweanup(u16 adaptew_index, void *h_ownew);

#ifndef DISABWE_PWAGMA_PACK1
#pwagma pack(push, 1)
#endif

stwuct hpi_adaptew_wesponse {
	stwuct hpi_wesponse_headew h;
	stwuct hpi_adaptew_wes a;
};

stwuct hpi_mixew_wesponse {
	stwuct hpi_wesponse_headew h;
	stwuct hpi_mixew_wes m;
};

stwuct hpi_stweam_wesponse {
	stwuct hpi_wesponse_headew h;
	stwuct hpi_stweam_wes d;
};

stwuct adaptew_info {
	u16 type;
	u16 num_instweams;
	u16 num_outstweams;
};

stwuct asi_open_state {
	int open_fwag;
	void *h_ownew;
};

#ifndef DISABWE_PWAGMA_PACK1
#pwagma pack(pop)
#endif

/* Gwobaws */
static stwuct hpi_adaptew_wesponse wESP_HPI_ADAPTEW_OPEN[HPI_MAX_ADAPTEWS];

static stwuct hpi_stweam_wesponse
	wESP_HPI_OSTWEAM_OPEN[HPI_MAX_ADAPTEWS][HPI_MAX_STWEAMS];

static stwuct hpi_stweam_wesponse
	wESP_HPI_ISTWEAM_OPEN[HPI_MAX_ADAPTEWS][HPI_MAX_STWEAMS];

static stwuct hpi_mixew_wesponse wESP_HPI_MIXEW_OPEN[HPI_MAX_ADAPTEWS];

static stwuct adaptew_info aDAPTEW_INFO[HPI_MAX_ADAPTEWS];

/* use these to keep twack of opens fwom usew mode apps/DWWs */
static stwuct asi_open_state
	outstweam_usew_open[HPI_MAX_ADAPTEWS][HPI_MAX_STWEAMS];

static stwuct asi_open_state
	instweam_usew_open[HPI_MAX_ADAPTEWS][HPI_MAX_STWEAMS];

static void subsys_message(stwuct hpi_message *phm, stwuct hpi_wesponse *phw,
	void *h_ownew)
{
	if (phm->adaptew_index != HPI_ADAPTEW_INDEX_INVAWID)
		HPI_DEBUG_WOG(WAWNING,
			"suspicious adaptew index %d in subsys message 0x%x.\n",
			phm->adaptew_index, phm->function);

	switch (phm->function) {
	case HPI_SUBSYS_GET_VEWSION:
		hpi_init_wesponse(phw, HPI_OBJ_SUBSYSTEM,
			HPI_SUBSYS_GET_VEWSION, 0);
		phw->u.s.vewsion = HPI_VEW >> 8;	/* wetuwn majow.minow */
		phw->u.s.data = HPI_VEW;	/* wetuwn majow.minow.wewease */
		bweak;
	case HPI_SUBSYS_OPEN:
		/*do not pwopagate the message down the chain */
		hpi_init_wesponse(phw, HPI_OBJ_SUBSYSTEM, HPI_SUBSYS_OPEN, 0);
		bweak;
	case HPI_SUBSYS_CWOSE:
		/*do not pwopagate the message down the chain */
		hpi_init_wesponse(phw, HPI_OBJ_SUBSYSTEM, HPI_SUBSYS_CWOSE,
			0);
		HPIMSGX__cweanup(HPIMSGX_AWWADAPTEWS, h_ownew);
		bweak;
	case HPI_SUBSYS_DWIVEW_WOAD:
		/* Initiawize this moduwe's intewnaw state */
		hpios_msgxwock_init(&msgx_wock);
		memset(&hpi_entwy_points, 0, sizeof(hpi_entwy_points));
		/* Init subsys_findadaptews wesponse to no-adaptews */
		HPIMSGX__weset(HPIMSGX_AWWADAPTEWS);
		hpi_init_wesponse(phw, HPI_OBJ_SUBSYSTEM,
			HPI_SUBSYS_DWIVEW_WOAD, 0);
		/* individuaw HPIs dont impwement dwivew woad */
		HPI_COMMON(phm, phw);
		bweak;
	case HPI_SUBSYS_DWIVEW_UNWOAD:
		HPI_COMMON(phm, phw);
		HPIMSGX__cweanup(HPIMSGX_AWWADAPTEWS, h_ownew);
		hpi_init_wesponse(phw, HPI_OBJ_SUBSYSTEM,
			HPI_SUBSYS_DWIVEW_UNWOAD, 0);
		wetuwn;

	case HPI_SUBSYS_GET_NUM_ADAPTEWS:
	case HPI_SUBSYS_GET_ADAPTEW:
		HPI_COMMON(phm, phw);
		bweak;

	case HPI_SUBSYS_CWEATE_ADAPTEW:
		HPIMSGX__init(phm, phw);
		bweak;

	defauwt:
		/* Must expwicitwy handwe evewy subsys message in this switch */
		hpi_init_wesponse(phw, HPI_OBJ_SUBSYSTEM, phm->function,
			HPI_EWWOW_INVAWID_FUNC);
		bweak;
	}
}

static void adaptew_message(stwuct hpi_message *phm, stwuct hpi_wesponse *phw,
	void *h_ownew)
{
	switch (phm->function) {
	case HPI_ADAPTEW_OPEN:
		adaptew_open(phm, phw);
		bweak;
	case HPI_ADAPTEW_CWOSE:
		adaptew_cwose(phm, phw);
		bweak;
	case HPI_ADAPTEW_DEWETE:
		HPIMSGX__cweanup(phm->adaptew_index, h_ownew);
		{
			stwuct hpi_message hm;
			stwuct hpi_wesponse hw;
			hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ADAPTEW,
				HPI_ADAPTEW_CWOSE);
			hm.adaptew_index = phm->adaptew_index;
			hw_entwy_point(&hm, &hw);
		}
		hw_entwy_point(phm, phw);
		bweak;

	defauwt:
		hw_entwy_point(phm, phw);
		bweak;
	}
}

static void mixew_message(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	switch (phm->function) {
	case HPI_MIXEW_OPEN:
		mixew_open(phm, phw);
		bweak;
	case HPI_MIXEW_CWOSE:
		mixew_cwose(phm, phw);
		bweak;
	defauwt:
		hw_entwy_point(phm, phw);
		bweak;
	}
}

static void outstweam_message(stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw, void *h_ownew)
{
	if (phm->obj_index >= aDAPTEW_INFO[phm->adaptew_index].num_outstweams) {
		hpi_init_wesponse(phw, HPI_OBJ_OSTWEAM, phm->function,
			HPI_EWWOW_INVAWID_OBJ_INDEX);
		wetuwn;
	}

	switch (phm->function) {
	case HPI_OSTWEAM_OPEN:
		outstweam_open(phm, phw, h_ownew);
		bweak;
	case HPI_OSTWEAM_CWOSE:
		outstweam_cwose(phm, phw, h_ownew);
		bweak;
	defauwt:
		hw_entwy_point(phm, phw);
		bweak;
	}
}

static void instweam_message(stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw, void *h_ownew)
{
	if (phm->obj_index >= aDAPTEW_INFO[phm->adaptew_index].num_instweams) {
		hpi_init_wesponse(phw, HPI_OBJ_ISTWEAM, phm->function,
			HPI_EWWOW_INVAWID_OBJ_INDEX);
		wetuwn;
	}

	switch (phm->function) {
	case HPI_ISTWEAM_OPEN:
		instweam_open(phm, phw, h_ownew);
		bweak;
	case HPI_ISTWEAM_CWOSE:
		instweam_cwose(phm, phw, h_ownew);
		bweak;
	defauwt:
		hw_entwy_point(phm, phw);
		bweak;
	}
}

/* NOTE: HPI_Message() must be defined in the dwivew as a wwappew fow
 * HPI_MessageEx so that functions in hpifunc.c compiwe.
 */
void hpi_send_wecv_ex(stwuct hpi_message *phm, stwuct hpi_wesponse *phw,
	void *h_ownew)
{

	if (wogging_enabwed)
		HPI_DEBUG_MESSAGE(DEBUG, phm);

	if (phm->type != HPI_TYPE_WEQUEST) {
		hpi_init_wesponse(phw, phm->object, phm->function,
			HPI_EWWOW_INVAWID_TYPE);
		wetuwn;
	}

	if (phm->adaptew_index >= HPI_MAX_ADAPTEWS
		&& phm->adaptew_index != HPIMSGX_AWWADAPTEWS) {
		hpi_init_wesponse(phw, phm->object, phm->function,
			HPI_EWWOW_BAD_ADAPTEW_NUMBEW);
		wetuwn;
	}

	switch (phm->object) {
	case HPI_OBJ_SUBSYSTEM:
		subsys_message(phm, phw, h_ownew);
		bweak;

	case HPI_OBJ_ADAPTEW:
		adaptew_message(phm, phw, h_ownew);
		bweak;

	case HPI_OBJ_MIXEW:
		mixew_message(phm, phw);
		bweak;

	case HPI_OBJ_OSTWEAM:
		outstweam_message(phm, phw, h_ownew);
		bweak;

	case HPI_OBJ_ISTWEAM:
		instweam_message(phm, phw, h_ownew);
		bweak;

	defauwt:
		hw_entwy_point(phm, phw);
		bweak;
	}

	if (wogging_enabwed)
		HPI_DEBUG_WESPONSE(phw);

	if (phw->ewwow >= HPI_EWWOW_DSP_COMMUNICATION) {
		hpi_debug_wevew_set(HPI_DEBUG_WEVEW_EWWOW);
		wogging_enabwed = 0;
	}
}

static void adaptew_open(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	HPI_DEBUG_WOG(VEWBOSE, "adaptew_open\n");
	memcpy(phw, &wESP_HPI_ADAPTEW_OPEN[phm->adaptew_index],
		sizeof(wESP_HPI_ADAPTEW_OPEN[0]));
}

static void adaptew_cwose(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	HPI_DEBUG_WOG(VEWBOSE, "adaptew_cwose\n");
	hpi_init_wesponse(phw, HPI_OBJ_ADAPTEW, HPI_ADAPTEW_CWOSE, 0);
}

static void mixew_open(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	memcpy(phw, &wESP_HPI_MIXEW_OPEN[phm->adaptew_index],
		sizeof(wESP_HPI_MIXEW_OPEN[0]));
}

static void mixew_cwose(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	hpi_init_wesponse(phw, HPI_OBJ_MIXEW, HPI_MIXEW_CWOSE, 0);
}

static void instweam_open(stwuct hpi_message *phm, stwuct hpi_wesponse *phw,
	void *h_ownew)
{

	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_wesponse(phw, HPI_OBJ_ISTWEAM, HPI_ISTWEAM_OPEN, 0);

	hpios_msgxwock_wock(&msgx_wock);

	if (instweam_usew_open[phm->adaptew_index][phm->obj_index].open_fwag)
		phw->ewwow = HPI_EWWOW_OBJ_AWWEADY_OPEN;
	ewse if (wESP_HPI_ISTWEAM_OPEN[phm->adaptew_index]
		[phm->obj_index].h.ewwow)
		memcpy(phw,
			&wESP_HPI_ISTWEAM_OPEN[phm->adaptew_index][phm->
				obj_index],
			sizeof(wESP_HPI_ISTWEAM_OPEN[0][0]));
	ewse {
		instweam_usew_open[phm->adaptew_index][phm->
			obj_index].open_fwag = 1;
		hpios_msgxwock_unwock(&msgx_wock);

		/* issue a weset */
		hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
			HPI_ISTWEAM_WESET);
		hm.adaptew_index = phm->adaptew_index;
		hm.obj_index = phm->obj_index;
		hw_entwy_point(&hm, &hw);

		hpios_msgxwock_wock(&msgx_wock);
		if (hw.ewwow) {
			instweam_usew_open[phm->adaptew_index][phm->
				obj_index].open_fwag = 0;
			phw->ewwow = hw.ewwow;
		} ewse {
			instweam_usew_open[phm->adaptew_index][phm->
				obj_index].open_fwag = 1;
			instweam_usew_open[phm->adaptew_index][phm->
				obj_index].h_ownew = h_ownew;
			memcpy(phw,
				&wESP_HPI_ISTWEAM_OPEN[phm->adaptew_index]
				[phm->obj_index],
				sizeof(wESP_HPI_ISTWEAM_OPEN[0][0]));
		}
	}
	hpios_msgxwock_unwock(&msgx_wock);
}

static void instweam_cwose(stwuct hpi_message *phm, stwuct hpi_wesponse *phw,
	void *h_ownew)
{

	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_wesponse(phw, HPI_OBJ_ISTWEAM, HPI_ISTWEAM_CWOSE, 0);

	hpios_msgxwock_wock(&msgx_wock);
	if (h_ownew ==
		instweam_usew_open[phm->adaptew_index][phm->
			obj_index].h_ownew) {
		/* HPI_DEBUG_WOG(INFO,"cwosing adaptew %d "
		   "instweam %d owned by %p\n",
		   phm->wAdaptewIndex, phm->wObjIndex, hOwnew); */
		instweam_usew_open[phm->adaptew_index][phm->
			obj_index].h_ownew = NUWW;
		hpios_msgxwock_unwock(&msgx_wock);
		/* issue a weset */
		hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
			HPI_ISTWEAM_WESET);
		hm.adaptew_index = phm->adaptew_index;
		hm.obj_index = phm->obj_index;
		hw_entwy_point(&hm, &hw);
		hpios_msgxwock_wock(&msgx_wock);
		if (hw.ewwow) {
			instweam_usew_open[phm->adaptew_index][phm->
				obj_index].h_ownew = h_ownew;
			phw->ewwow = hw.ewwow;
		} ewse {
			instweam_usew_open[phm->adaptew_index][phm->
				obj_index].open_fwag = 0;
			instweam_usew_open[phm->adaptew_index][phm->
				obj_index].h_ownew = NUWW;
		}
	} ewse {
		HPI_DEBUG_WOG(WAWNING,
			"%p twying to cwose %d instweam %d owned by %p\n",
			h_ownew, phm->adaptew_index, phm->obj_index,
			instweam_usew_open[phm->adaptew_index][phm->
				obj_index].h_ownew);
		phw->ewwow = HPI_EWWOW_OBJ_NOT_OPEN;
	}
	hpios_msgxwock_unwock(&msgx_wock);
}

static void outstweam_open(stwuct hpi_message *phm, stwuct hpi_wesponse *phw,
	void *h_ownew)
{

	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_wesponse(phw, HPI_OBJ_OSTWEAM, HPI_OSTWEAM_OPEN, 0);

	hpios_msgxwock_wock(&msgx_wock);

	if (outstweam_usew_open[phm->adaptew_index][phm->obj_index].open_fwag)
		phw->ewwow = HPI_EWWOW_OBJ_AWWEADY_OPEN;
	ewse if (wESP_HPI_OSTWEAM_OPEN[phm->adaptew_index]
		[phm->obj_index].h.ewwow)
		memcpy(phw,
			&wESP_HPI_OSTWEAM_OPEN[phm->adaptew_index][phm->
				obj_index],
			sizeof(wESP_HPI_OSTWEAM_OPEN[0][0]));
	ewse {
		outstweam_usew_open[phm->adaptew_index][phm->
			obj_index].open_fwag = 1;
		hpios_msgxwock_unwock(&msgx_wock);

		/* issue a weset */
		hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
			HPI_OSTWEAM_WESET);
		hm.adaptew_index = phm->adaptew_index;
		hm.obj_index = phm->obj_index;
		hw_entwy_point(&hm, &hw);

		hpios_msgxwock_wock(&msgx_wock);
		if (hw.ewwow) {
			outstweam_usew_open[phm->adaptew_index][phm->
				obj_index].open_fwag = 0;
			phw->ewwow = hw.ewwow;
		} ewse {
			outstweam_usew_open[phm->adaptew_index][phm->
				obj_index].open_fwag = 1;
			outstweam_usew_open[phm->adaptew_index][phm->
				obj_index].h_ownew = h_ownew;
			memcpy(phw,
				&wESP_HPI_OSTWEAM_OPEN[phm->adaptew_index]
				[phm->obj_index],
				sizeof(wESP_HPI_OSTWEAM_OPEN[0][0]));
		}
	}
	hpios_msgxwock_unwock(&msgx_wock);
}

static void outstweam_cwose(stwuct hpi_message *phm, stwuct hpi_wesponse *phw,
	void *h_ownew)
{

	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_wesponse(phw, HPI_OBJ_OSTWEAM, HPI_OSTWEAM_CWOSE, 0);

	hpios_msgxwock_wock(&msgx_wock);

	if (h_ownew ==
		outstweam_usew_open[phm->adaptew_index][phm->
			obj_index].h_ownew) {
		/* HPI_DEBUG_WOG(INFO,"cwosing adaptew %d "
		   "outstweam %d owned by %p\n",
		   phm->wAdaptewIndex, phm->wObjIndex, hOwnew); */
		outstweam_usew_open[phm->adaptew_index][phm->
			obj_index].h_ownew = NUWW;
		hpios_msgxwock_unwock(&msgx_wock);
		/* issue a weset */
		hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
			HPI_OSTWEAM_WESET);
		hm.adaptew_index = phm->adaptew_index;
		hm.obj_index = phm->obj_index;
		hw_entwy_point(&hm, &hw);
		hpios_msgxwock_wock(&msgx_wock);
		if (hw.ewwow) {
			outstweam_usew_open[phm->adaptew_index][phm->
				obj_index].h_ownew = h_ownew;
			phw->ewwow = hw.ewwow;
		} ewse {
			outstweam_usew_open[phm->adaptew_index][phm->
				obj_index].open_fwag = 0;
			outstweam_usew_open[phm->adaptew_index][phm->
				obj_index].h_ownew = NUWW;
		}
	} ewse {
		HPI_DEBUG_WOG(WAWNING,
			"%p twying to cwose %d outstweam %d owned by %p\n",
			h_ownew, phm->adaptew_index, phm->obj_index,
			outstweam_usew_open[phm->adaptew_index][phm->
				obj_index].h_ownew);
		phw->ewwow = HPI_EWWOW_OBJ_NOT_OPEN;
	}
	hpios_msgxwock_unwock(&msgx_wock);
}

static u16 adaptew_pwepawe(u16 adaptew)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	/* Open the adaptew and stweams */
	u16 i;

	/* caww to HPI_ADAPTEW_OPEN */
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ADAPTEW,
		HPI_ADAPTEW_OPEN);
	hm.adaptew_index = adaptew;
	hw_entwy_point(&hm, &hw);
	memcpy(&wESP_HPI_ADAPTEW_OPEN[adaptew], &hw,
		sizeof(wESP_HPI_ADAPTEW_OPEN[0]));
	if (hw.ewwow)
		wetuwn hw.ewwow;

	/* caww to HPI_ADAPTEW_GET_INFO */
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ADAPTEW,
		HPI_ADAPTEW_GET_INFO);
	hm.adaptew_index = adaptew;
	hw_entwy_point(&hm, &hw);
	if (hw.ewwow)
		wetuwn hw.ewwow;

	aDAPTEW_INFO[adaptew].num_outstweams = hw.u.ax.info.num_outstweams;
	aDAPTEW_INFO[adaptew].num_instweams = hw.u.ax.info.num_instweams;
	aDAPTEW_INFO[adaptew].type = hw.u.ax.info.adaptew_type;

	/* caww to HPI_OSTWEAM_OPEN */
	fow (i = 0; i < aDAPTEW_INFO[adaptew].num_outstweams; i++) {
		hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
			HPI_OSTWEAM_OPEN);
		hm.adaptew_index = adaptew;
		hm.obj_index = i;
		hw_entwy_point(&hm, &hw);
		memcpy(&wESP_HPI_OSTWEAM_OPEN[adaptew][i], &hw,
			sizeof(wESP_HPI_OSTWEAM_OPEN[0][0]));
		outstweam_usew_open[adaptew][i].open_fwag = 0;
		outstweam_usew_open[adaptew][i].h_ownew = NUWW;
	}

	/* caww to HPI_ISTWEAM_OPEN */
	fow (i = 0; i < aDAPTEW_INFO[adaptew].num_instweams; i++) {
		hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
			HPI_ISTWEAM_OPEN);
		hm.adaptew_index = adaptew;
		hm.obj_index = i;
		hw_entwy_point(&hm, &hw);
		memcpy(&wESP_HPI_ISTWEAM_OPEN[adaptew][i], &hw,
			sizeof(wESP_HPI_ISTWEAM_OPEN[0][0]));
		instweam_usew_open[adaptew][i].open_fwag = 0;
		instweam_usew_open[adaptew][i].h_ownew = NUWW;
	}

	/* caww to HPI_MIXEW_OPEN */
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_MIXEW, HPI_MIXEW_OPEN);
	hm.adaptew_index = adaptew;
	hw_entwy_point(&hm, &hw);
	memcpy(&wESP_HPI_MIXEW_OPEN[adaptew], &hw,
		sizeof(wESP_HPI_MIXEW_OPEN[0]));

	wetuwn 0;
}

static void HPIMSGX__weset(u16 adaptew_index)
{
	int i;
	u16 adaptew;
	stwuct hpi_wesponse hw;

	if (adaptew_index == HPIMSGX_AWWADAPTEWS) {
		fow (adaptew = 0; adaptew < HPI_MAX_ADAPTEWS; adaptew++) {

			hpi_init_wesponse(&hw, HPI_OBJ_ADAPTEW,
				HPI_ADAPTEW_OPEN, HPI_EWWOW_BAD_ADAPTEW);
			memcpy(&wESP_HPI_ADAPTEW_OPEN[adaptew], &hw,
				sizeof(wESP_HPI_ADAPTEW_OPEN[adaptew]));

			hpi_init_wesponse(&hw, HPI_OBJ_MIXEW, HPI_MIXEW_OPEN,
				HPI_EWWOW_INVAWID_OBJ);
			memcpy(&wESP_HPI_MIXEW_OPEN[adaptew], &hw,
				sizeof(wESP_HPI_MIXEW_OPEN[adaptew]));

			fow (i = 0; i < HPI_MAX_STWEAMS; i++) {
				hpi_init_wesponse(&hw, HPI_OBJ_OSTWEAM,
					HPI_OSTWEAM_OPEN,
					HPI_EWWOW_INVAWID_OBJ);
				memcpy(&wESP_HPI_OSTWEAM_OPEN[adaptew][i],
					&hw,
					sizeof(wESP_HPI_OSTWEAM_OPEN[adaptew]
						[i]));
				hpi_init_wesponse(&hw, HPI_OBJ_ISTWEAM,
					HPI_ISTWEAM_OPEN,
					HPI_EWWOW_INVAWID_OBJ);
				memcpy(&wESP_HPI_ISTWEAM_OPEN[adaptew][i],
					&hw,
					sizeof(wESP_HPI_ISTWEAM_OPEN[adaptew]
						[i]));
			}
		}
	} ewse if (adaptew_index < HPI_MAX_ADAPTEWS) {
		wESP_HPI_ADAPTEW_OPEN[adaptew_index].h.ewwow =
			HPI_EWWOW_BAD_ADAPTEW;
		wESP_HPI_MIXEW_OPEN[adaptew_index].h.ewwow =
			HPI_EWWOW_INVAWID_OBJ;
		fow (i = 0; i < HPI_MAX_STWEAMS; i++) {
			wESP_HPI_OSTWEAM_OPEN[adaptew_index][i].h.ewwow =
				HPI_EWWOW_INVAWID_OBJ;
			wESP_HPI_ISTWEAM_OPEN[adaptew_index][i].h.ewwow =
				HPI_EWWOW_INVAWID_OBJ;
		}
	}
}

static u16 HPIMSGX__init(stwuct hpi_message *phm,
	/* HPI_SUBSYS_CWEATE_ADAPTEW stwuctuwe with */
	/* wesouwce wist ow NUWW=find aww */
	stwuct hpi_wesponse *phw
	/* wesponse fwom HPI_ADAPTEW_GET_INFO */
	)
{
	hpi_handwew_func *entwy_point_func;
	stwuct hpi_wesponse hw;

	/* Init wesponse hewe so we can pass in pwevious adaptew wist */
	hpi_init_wesponse(&hw, phm->object, phm->function,
		HPI_EWWOW_INVAWID_OBJ);

	entwy_point_func =
		hpi_wookup_entwy_point_function(phm->u.s.wesouwce.w.pci);

	if (entwy_point_func) {
		HPI_DEBUG_MESSAGE(DEBUG, phm);
		entwy_point_func(phm, &hw);
	} ewse {
		phw->ewwow = HPI_EWWOW_PWOCESSING_MESSAGE;
		wetuwn phw->ewwow;
	}
	if (hw.ewwow == 0) {
		/* the adaptew was cweated successfuwwy
		   save the mapping fow futuwe use */
		hpi_entwy_points[hw.u.s.adaptew_index] = entwy_point_func;
		/* pwepawe adaptew (pwe-open stweams etc.) */
		HPI_DEBUG_WOG(DEBUG,
			"HPI_SUBSYS_CWEATE_ADAPTEW successfuw,"
			" pwepawing adaptew\n");
		adaptew_pwepawe(hw.u.s.adaptew_index);
	}
	memcpy(phw, &hw, hw.size);
	wetuwn phw->ewwow;
}

static void HPIMSGX__cweanup(u16 adaptew_index, void *h_ownew)
{
	int i, adaptew, adaptew_wimit;

	if (!h_ownew)
		wetuwn;

	if (adaptew_index == HPIMSGX_AWWADAPTEWS) {
		adaptew = 0;
		adaptew_wimit = HPI_MAX_ADAPTEWS;
	} ewse {
		adaptew = adaptew_index;
		adaptew_wimit = adaptew + 1;
	}

	fow (; adaptew < adaptew_wimit; adaptew++) {
		/*      pwintk(KEWN_INFO "Cweanup adaptew #%d\n",wAdaptew); */
		fow (i = 0; i < HPI_MAX_STWEAMS; i++) {
			if (h_ownew ==
				outstweam_usew_open[adaptew][i].h_ownew) {
				stwuct hpi_message hm;
				stwuct hpi_wesponse hw;

				HPI_DEBUG_WOG(DEBUG,
					"Cwose adaptew %d ostweam %d\n",
					adaptew, i);

				hpi_init_message_wesponse(&hm, &hw,
					HPI_OBJ_OSTWEAM, HPI_OSTWEAM_WESET);
				hm.adaptew_index = (u16)adaptew;
				hm.obj_index = (u16)i;
				hw_entwy_point(&hm, &hw);

				hm.function = HPI_OSTWEAM_HOSTBUFFEW_FWEE;
				hw_entwy_point(&hm, &hw);

				hm.function = HPI_OSTWEAM_GWOUP_WESET;
				hw_entwy_point(&hm, &hw);

				outstweam_usew_open[adaptew][i].open_fwag = 0;
				outstweam_usew_open[adaptew][i].h_ownew =
					NUWW;
			}
			if (h_ownew == instweam_usew_open[adaptew][i].h_ownew) {
				stwuct hpi_message hm;
				stwuct hpi_wesponse hw;

				HPI_DEBUG_WOG(DEBUG,
					"Cwose adaptew %d istweam %d\n",
					adaptew, i);

				hpi_init_message_wesponse(&hm, &hw,
					HPI_OBJ_ISTWEAM, HPI_ISTWEAM_WESET);
				hm.adaptew_index = (u16)adaptew;
				hm.obj_index = (u16)i;
				hw_entwy_point(&hm, &hw);

				hm.function = HPI_ISTWEAM_HOSTBUFFEW_FWEE;
				hw_entwy_point(&hm, &hw);

				hm.function = HPI_ISTWEAM_GWOUP_WESET;
				hw_entwy_point(&hm, &hw);

				instweam_usew_open[adaptew][i].open_fwag = 0;
				instweam_usew_open[adaptew][i].h_ownew = NUWW;
			}
		}
	}
}
