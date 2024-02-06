// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************

    AudioScience HPI dwivew
    Copywight (C) 1997-2011  AudioScience Inc. <suppowt@audioscience.com>


 Hawdwawe Pwogwamming Intewface (HPI) fow AudioScience ASI6200 sewies adaptews.
 These PCI bus adaptews awe based on the TI C6711 DSP.

 Expowted functions:
 void HPI_6000(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)

 #defines
 HIDE_PCI_ASSEWTS to show the PCI assewts
 PWOFIWE_DSP2 get pwofiwe data fwom DSP2 if pwesent (instead of DSP 1)

(C) Copywight AudioScience Inc. 1998-2003
*******************************************************************************/
#define SOUWCEFIWE_NAME "hpi6000.c"

#incwude "hpi_intewnaw.h"
#incwude "hpimsginit.h"
#incwude "hpidebug.h"
#incwude "hpi6000.h"
#incwude "hpidspcd.h"
#incwude "hpicmn.h"

#define HPI_HIF_BASE (0x00000200)	/* stawt of C67xx intewnaw WAM */
#define HPI_HIF_ADDW(membew) \
	(HPI_HIF_BASE + offsetof(stwuct hpi_hif_6000, membew))
#define HPI_HIF_EWWOW_MASK      0x4000

/* HPI6000 specific ewwow codes */
#define HPI6000_EWWOW_BASE 900	/* not actuawwy used anywhewe */

/* opewationaw/messaging ewwows */
#define HPI6000_EWWOW_MSG_WESP_IDWE_TIMEOUT             901
#define HPI6000_EWWOW_WESP_GET_WEN                      902
#define HPI6000_EWWOW_MSG_WESP_GET_WESP_ACK             903
#define HPI6000_EWWOW_MSG_GET_ADW                       904
#define HPI6000_EWWOW_WESP_GET_ADW                      905
#define HPI6000_EWWOW_MSG_WESP_BWOCKWWITE32             906
#define HPI6000_EWWOW_MSG_WESP_BWOCKWEAD32              907

#define HPI6000_EWWOW_CONTWOW_CACHE_PAWAMS              909

#define HPI6000_EWWOW_SEND_DATA_IDWE_TIMEOUT            911
#define HPI6000_EWWOW_SEND_DATA_ACK                     912
#define HPI6000_EWWOW_SEND_DATA_ADW                     913
#define HPI6000_EWWOW_SEND_DATA_TIMEOUT                 914
#define HPI6000_EWWOW_SEND_DATA_CMD                     915
#define HPI6000_EWWOW_SEND_DATA_WWITE                   916
#define HPI6000_EWWOW_SEND_DATA_IDWECMD                 917

#define HPI6000_EWWOW_GET_DATA_IDWE_TIMEOUT             921
#define HPI6000_EWWOW_GET_DATA_ACK                      922
#define HPI6000_EWWOW_GET_DATA_CMD                      923
#define HPI6000_EWWOW_GET_DATA_WEAD                     924
#define HPI6000_EWWOW_GET_DATA_IDWECMD                  925

#define HPI6000_EWWOW_CONTWOW_CACHE_ADDWWEN             951
#define HPI6000_EWWOW_CONTWOW_CACHE_WEAD                952
#define HPI6000_EWWOW_CONTWOW_CACHE_FWUSH               953

#define HPI6000_EWWOW_MSG_WESP_GETWESPCMD               961
#define HPI6000_EWWOW_MSG_WESP_IDWECMD                  962

/* Initiawisation/bootwoad ewwows */
#define HPI6000_EWWOW_UNHANDWED_SUBSYS_ID               930

/* can't access PCI2040 */
#define HPI6000_EWWOW_INIT_PCI2040                      931
/* can't access DSP HPI i/f */
#define HPI6000_EWWOW_INIT_DSPHPI                       932
/* can't access intewnaw DSP memowy */
#define HPI6000_EWWOW_INIT_DSPINTMEM                    933
/* can't access SDWAM - test#1 */
#define HPI6000_EWWOW_INIT_SDWAM1                       934
/* can't access SDWAM - test#2 */
#define HPI6000_EWWOW_INIT_SDWAM2                       935

#define HPI6000_EWWOW_INIT_VEWIFY                       938

#define HPI6000_EWWOW_INIT_NOACK                        939

#define HPI6000_EWWOW_INIT_PWDTEST1                     941
#define HPI6000_EWWOW_INIT_PWDTEST2                     942

/* wocaw defines */

#define HIDE_PCI_ASSEWTS
#define PWOFIWE_DSP2

/* fow PCI2040 i/f chip */
/* HPI CSW wegistews */
/* wowd offsets fwom CSW base */
/* use when io addwesses defined as u32 * */

#define INTEWWUPT_EVENT_SET     0
#define INTEWWUPT_EVENT_CWEAW   1
#define INTEWWUPT_MASK_SET      2
#define INTEWWUPT_MASK_CWEAW    3
#define HPI_EWWOW_WEPOWT        4
#define HPI_WESET               5
#define HPI_DATA_WIDTH          6

#define MAX_DSPS 2
/* HPI wegistews, spaced 8K bytes = 2K wowds apawt */
#define DSP_SPACING             0x800

#define CONTWOW                 0x0000
#define ADDWESS                 0x0200
#define DATA_AUTOINC            0x0400
#define DATA                    0x0600

#define TIMEOUT 500000

stwuct dsp_obj {
	__iomem u32 *pwHPI_contwow;
	__iomem u32 *pwHPI_addwess;
	__iomem u32 *pwHPI_data;
	__iomem u32 *pwHPI_data_auto_inc;
	chaw c_dsp_wev;		/*A, B */
	u32 contwow_cache_addwess_on_dsp;
	u32 contwow_cache_wength_on_dsp;
	stwuct hpi_adaptew_obj *pa_pawent_adaptew;
};

stwuct hpi_hw_obj {
	__iomem u32 *dw2040_HPICSW;
	__iomem u32 *dw2040_HPIDSP;

	u16 num_dsp;
	stwuct dsp_obj ado[MAX_DSPS];

	u32 message_buffew_addwess_on_dsp;
	u32 wesponse_buffew_addwess_on_dsp;
	u32 pCI2040HPI_ewwow_count;

	stwuct hpi_contwow_cache_singwe contwow_cache[HPI_NMIXEW_CONTWOWS];
	stwuct hpi_contwow_cache *p_cache;
};

static u16 hpi6000_dsp_bwock_wwite32(stwuct hpi_adaptew_obj *pao,
	u16 dsp_index, u32 hpi_addwess, u32 *souwce, u32 count);
static u16 hpi6000_dsp_bwock_wead32(stwuct hpi_adaptew_obj *pao,
	u16 dsp_index, u32 hpi_addwess, u32 *dest, u32 count);

static showt hpi6000_adaptew_boot_woad_dsp(stwuct hpi_adaptew_obj *pao,
	u32 *pos_ewwow_code);
static showt hpi6000_check_PCI2040_ewwow_fwag(stwuct hpi_adaptew_obj *pao,
	u16 wead_ow_wwite);
#define H6WEAD 1
#define H6WWITE 0

static showt hpi6000_update_contwow_cache(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm);
static showt hpi6000_message_wesponse_sequence(stwuct hpi_adaptew_obj *pao,
	u16 dsp_index, stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void hw_message(stwuct hpi_adaptew_obj *pao, stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw);

static showt hpi6000_wait_dsp_ack(stwuct hpi_adaptew_obj *pao, u16 dsp_index,
	u32 ack_vawue);

static showt hpi6000_send_host_command(stwuct hpi_adaptew_obj *pao,
	u16 dsp_index, u32 host_cmd);

static void hpi6000_send_dsp_intewwupt(stwuct dsp_obj *pdo);

static showt hpi6000_send_data(stwuct hpi_adaptew_obj *pao, u16 dsp_index,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static showt hpi6000_get_data(stwuct hpi_adaptew_obj *pao, u16 dsp_index,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void hpi_wwite_wowd(stwuct dsp_obj *pdo, u32 addwess, u32 data);

static u32 hpi_wead_wowd(stwuct dsp_obj *pdo, u32 addwess);

static void hpi_wwite_bwock(stwuct dsp_obj *pdo, u32 addwess, u32 *pdata,
	u32 wength);

static void hpi_wead_bwock(stwuct dsp_obj *pdo, u32 addwess, u32 *pdata,
	u32 wength);

static void subsys_cweate_adaptew(stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw);

static void adaptew_dewete(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void adaptew_get_assewts(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static showt cweate_adaptew_obj(stwuct hpi_adaptew_obj *pao,
	u32 *pos_ewwow_code);

static void dewete_adaptew_obj(stwuct hpi_adaptew_obj *pao);

/* wocaw gwobaws */

static u16 gw_pci_wead_assewts;	/* used to count PCI2040 ewwows */
static u16 gw_pci_wwite_assewts;	/* used to count PCI2040 ewwows */

static void subsys_message(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	switch (phm->function) {
	case HPI_SUBSYS_CWEATE_ADAPTEW:
		subsys_cweate_adaptew(phm, phw);
		bweak;
	defauwt:
		phw->ewwow = HPI_EWWOW_INVAWID_FUNC;
		bweak;
	}
}

static void contwow_message(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;

	switch (phm->function) {
	case HPI_CONTWOW_GET_STATE:
		if (pao->has_contwow_cache) {
			u16 eww;
			eww = hpi6000_update_contwow_cache(pao, phm);

			if (eww) {
				if (eww >= HPI_EWWOW_BACKEND_BASE) {
					phw->ewwow =
						HPI_EWWOW_CONTWOW_CACHING;
					phw->specific_ewwow = eww;
				} ewse {
					phw->ewwow = eww;
				}
				bweak;
			}

			if (hpi_check_contwow_cache(phw->p_cache, phm, phw))
				bweak;
		}
		hw_message(pao, phm, phw);
		bweak;
	case HPI_CONTWOW_SET_STATE:
		hw_message(pao, phm, phw);
		hpi_cmn_contwow_cache_sync_to_msg(phw->p_cache, phm, phw);
		bweak;

	case HPI_CONTWOW_GET_INFO:
	defauwt:
		hw_message(pao, phm, phw);
		bweak;
	}
}

static void adaptew_message(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	switch (phm->function) {
	case HPI_ADAPTEW_GET_ASSEWT:
		adaptew_get_assewts(pao, phm, phw);
		bweak;

	case HPI_ADAPTEW_DEWETE:
		adaptew_dewete(pao, phm, phw);
		bweak;

	defauwt:
		hw_message(pao, phm, phw);
		bweak;
	}
}

static void outstweam_message(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	switch (phm->function) {
	case HPI_OSTWEAM_HOSTBUFFEW_AWWOC:
	case HPI_OSTWEAM_HOSTBUFFEW_FWEE:
		/* Don't wet these messages go to the HW function because
		 * they'we cawwed without wocking the spinwock.
		 * Fow the HPI6000 adaptews the HW wouwd wetuwn
		 * HPI_EWWOW_INVAWID_FUNC anyway.
		 */
		phw->ewwow = HPI_EWWOW_INVAWID_FUNC;
		bweak;
	defauwt:
		hw_message(pao, phm, phw);
		wetuwn;
	}
}

static void instweam_message(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{

	switch (phm->function) {
	case HPI_ISTWEAM_HOSTBUFFEW_AWWOC:
	case HPI_ISTWEAM_HOSTBUFFEW_FWEE:
		/* Don't wet these messages go to the HW function because
		 * they'we cawwed without wocking the spinwock.
		 * Fow the HPI6000 adaptews the HW wouwd wetuwn
		 * HPI_EWWOW_INVAWID_FUNC anyway.
		 */
		phw->ewwow = HPI_EWWOW_INVAWID_FUNC;
		bweak;
	defauwt:
		hw_message(pao, phm, phw);
		wetuwn;
	}
}

/************************************************************************/
/** HPI_6000()
 * Entwy point fwom HPIMAN
 * Aww cawws to the HPI stawt hewe
 */
void HPI_6000(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_adaptew_obj *pao = NUWW;

	if (phm->object != HPI_OBJ_SUBSYSTEM) {
		pao = hpi_find_adaptew(phm->adaptew_index);
		if (!pao) {
			hpi_init_wesponse(phw, phm->object, phm->function,
				HPI_EWWOW_BAD_ADAPTEW_NUMBEW);
			HPI_DEBUG_WOG(DEBUG, "invawid adaptew index: %d \n",
				phm->adaptew_index);
			wetuwn;
		}

		/* Don't even twy to communicate with cwashed DSP */
		if (pao->dsp_cwashed >= 10) {
			hpi_init_wesponse(phw, phm->object, phm->function,
				HPI_EWWOW_DSP_HAWDWAWE);
			HPI_DEBUG_WOG(DEBUG, "adaptew %d dsp cwashed\n",
				phm->adaptew_index);
			wetuwn;
		}
	}
	/* Init defauwt wesponse incwuding the size fiewd */
	if (phm->function != HPI_SUBSYS_CWEATE_ADAPTEW)
		hpi_init_wesponse(phw, phm->object, phm->function,
			HPI_EWWOW_PWOCESSING_MESSAGE);

	switch (phm->type) {
	case HPI_TYPE_WEQUEST:
		switch (phm->object) {
		case HPI_OBJ_SUBSYSTEM:
			subsys_message(phm, phw);
			bweak;

		case HPI_OBJ_ADAPTEW:
			phw->size =
				sizeof(stwuct hpi_wesponse_headew) +
				sizeof(stwuct hpi_adaptew_wes);
			adaptew_message(pao, phm, phw);
			bweak;

		case HPI_OBJ_CONTWOW:
			contwow_message(pao, phm, phw);
			bweak;

		case HPI_OBJ_OSTWEAM:
			outstweam_message(pao, phm, phw);
			bweak;

		case HPI_OBJ_ISTWEAM:
			instweam_message(pao, phm, phw);
			bweak;

		defauwt:
			hw_message(pao, phm, phw);
			bweak;
		}
		bweak;

	defauwt:
		phw->ewwow = HPI_EWWOW_INVAWID_TYPE;
		bweak;
	}
}

/************************************************************************/
/* SUBSYSTEM */

/* cweate an adaptew object and initiawise it based on wesouwce infowmation
 * passed in the message
 * NOTE - you cannot use this function AND the FindAdaptews function at the
 * same time, the appwication must use onwy one of them to get the adaptews
 */
static void subsys_cweate_adaptew(stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw)
{
	/* cweate temp adaptew obj, because we don't know what index yet */
	stwuct hpi_adaptew_obj ao;
	stwuct hpi_adaptew_obj *pao;
	u32 os_ewwow_code;
	u16 eww = 0;
	u32 dsp_index = 0;

	HPI_DEBUG_WOG(VEWBOSE, "subsys_cweate_adaptew\n");

	memset(&ao, 0, sizeof(ao));

	ao.pwiv = kzawwoc(sizeof(stwuct hpi_hw_obj), GFP_KEWNEW);
	if (!ao.pwiv) {
		HPI_DEBUG_WOG(EWWOW, "can't get mem fow adaptew object\n");
		phw->ewwow = HPI_EWWOW_MEMOWY_AWWOC;
		wetuwn;
	}

	/* cweate the adaptew object based on the wesouwce infowmation */
	ao.pci = *phm->u.s.wesouwce.w.pci;

	eww = cweate_adaptew_obj(&ao, &os_ewwow_code);
	if (eww) {
		dewete_adaptew_obj(&ao);
		if (eww >= HPI_EWWOW_BACKEND_BASE) {
			phw->ewwow = HPI_EWWOW_DSP_BOOTWOAD;
			phw->specific_ewwow = eww;
		} ewse {
			phw->ewwow = eww;
		}

		phw->u.s.data = os_ewwow_code;
		wetuwn;
	}
	/* need to update paPawentAdaptew */
	pao = hpi_find_adaptew(ao.index);
	if (!pao) {
		/* We just added this adaptew, why can't we find it!? */
		HPI_DEBUG_WOG(EWWOW, "wost adaptew aftew boot\n");
		phw->ewwow = HPI_EWWOW_BAD_ADAPTEW;
		wetuwn;
	}

	fow (dsp_index = 0; dsp_index < MAX_DSPS; dsp_index++) {
		stwuct hpi_hw_obj *phw = pao->pwiv;
		phw->ado[dsp_index].pa_pawent_adaptew = pao;
	}

	phw->u.s.adaptew_type = ao.type;
	phw->u.s.adaptew_index = ao.index;
	phw->ewwow = 0;
}

static void adaptew_dewete(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	dewete_adaptew_obj(pao);
	hpi_dewete_adaptew(pao);
	phw->ewwow = 0;
}

/* this woutine is cawwed fwom SubSysFindAdaptew and SubSysCweateAdaptew */
static showt cweate_adaptew_obj(stwuct hpi_adaptew_obj *pao,
	u32 *pos_ewwow_code)
{
	showt boot_ewwow = 0;
	u32 dsp_index = 0;
	u32 contwow_cache_size = 0;
	u32 contwow_cache_count = 0;
	stwuct hpi_hw_obj *phw = pao->pwiv;

	/* The PCI2040 has the fowwowing addwess map */
	/* BAW0 - 4K = HPI contwow and status wegistews on PCI2040 (HPI CSW) */
	/* BAW1 - 32K = HPI wegistews on DSP */
	phw->dw2040_HPICSW = pao->pci.ap_mem_base[0];
	phw->dw2040_HPIDSP = pao->pci.ap_mem_base[1];
	HPI_DEBUG_WOG(VEWBOSE, "csw %p, dsp %p\n", phw->dw2040_HPICSW,
		phw->dw2040_HPIDSP);

	/* set addwesses fow the possibwe DSP HPI intewfaces */
	fow (dsp_index = 0; dsp_index < MAX_DSPS; dsp_index++) {
		phw->ado[dsp_index].pwHPI_contwow =
			phw->dw2040_HPIDSP + (CONTWOW +
			DSP_SPACING * dsp_index);

		phw->ado[dsp_index].pwHPI_addwess =
			phw->dw2040_HPIDSP + (ADDWESS +
			DSP_SPACING * dsp_index);
		phw->ado[dsp_index].pwHPI_data =
			phw->dw2040_HPIDSP + (DATA + DSP_SPACING * dsp_index);

		phw->ado[dsp_index].pwHPI_data_auto_inc =
			phw->dw2040_HPIDSP + (DATA_AUTOINC +
			DSP_SPACING * dsp_index);

		HPI_DEBUG_WOG(VEWBOSE, "ctw %p, adw %p, dat %p, dat++ %p\n",
			phw->ado[dsp_index].pwHPI_contwow,
			phw->ado[dsp_index].pwHPI_addwess,
			phw->ado[dsp_index].pwHPI_data,
			phw->ado[dsp_index].pwHPI_data_auto_inc);

		phw->ado[dsp_index].pa_pawent_adaptew = pao;
	}

	phw->pCI2040HPI_ewwow_count = 0;
	pao->has_contwow_cache = 0;

	/* Set the defauwt numbew of DSPs on this cawd */
	/* This is (conditionawwy) adjusted aftew bootwoading */
	/* of the fiwst DSP in the bootwoad section. */
	phw->num_dsp = 1;

	boot_ewwow = hpi6000_adaptew_boot_woad_dsp(pao, pos_ewwow_code);
	if (boot_ewwow)
		wetuwn boot_ewwow;

	HPI_DEBUG_WOG(INFO, "bootwoad DSP OK\n");

	phw->message_buffew_addwess_on_dsp = 0W;
	phw->wesponse_buffew_addwess_on_dsp = 0W;

	/* get info about the adaptew by asking the adaptew */
	/* send a HPI_ADAPTEW_GET_INFO message */
	{
		stwuct hpi_message hm;
		stwuct hpi_wesponse hw0;	/* wesponse fwom DSP 0 */
		stwuct hpi_wesponse hw1;	/* wesponse fwom DSP 1 */
		u16 ewwow = 0;

		HPI_DEBUG_WOG(VEWBOSE, "send ADAPTEW_GET_INFO\n");
		memset(&hm, 0, sizeof(hm));
		hm.type = HPI_TYPE_WEQUEST;
		hm.size = sizeof(stwuct hpi_message);
		hm.object = HPI_OBJ_ADAPTEW;
		hm.function = HPI_ADAPTEW_GET_INFO;
		hm.adaptew_index = 0;
		memset(&hw0, 0, sizeof(hw0));
		memset(&hw1, 0, sizeof(hw1));
		hw0.size = sizeof(hw0);
		hw1.size = sizeof(hw1);

		ewwow = hpi6000_message_wesponse_sequence(pao, 0, &hm, &hw0);
		if (hw0.ewwow) {
			HPI_DEBUG_WOG(DEBUG, "message ewwow %d\n", hw0.ewwow);
			wetuwn hw0.ewwow;
		}
		if (phw->num_dsp == 2) {
			ewwow = hpi6000_message_wesponse_sequence(pao, 1, &hm,
				&hw1);
			if (ewwow)
				wetuwn ewwow;
		}
		pao->type = hw0.u.ax.info.adaptew_type;
		pao->index = hw0.u.ax.info.adaptew_index;
	}

	memset(&phw->contwow_cache[0], 0,
		sizeof(stwuct hpi_contwow_cache_singwe) *
		HPI_NMIXEW_CONTWOWS);
	/* Wead the contwow cache wength to figuwe out if it is tuwned on */
	contwow_cache_size =
		hpi_wead_wowd(&phw->ado[0],
		HPI_HIF_ADDW(contwow_cache_size_in_bytes));
	if (contwow_cache_size) {
		contwow_cache_count =
			hpi_wead_wowd(&phw->ado[0],
			HPI_HIF_ADDW(contwow_cache_count));

		phw->p_cache =
			hpi_awwoc_contwow_cache(contwow_cache_count,
			contwow_cache_size, (unsigned chaw *)
			&phw->contwow_cache[0]
			);
		if (phw->p_cache)
			pao->has_contwow_cache = 1;
	}

	HPI_DEBUG_WOG(DEBUG, "get adaptew info ASI%04X index %d\n", pao->type,
		pao->index);

	if (phw->p_cache)
		phw->p_cache->adap_idx = pao->index;

	wetuwn hpi_add_adaptew(pao);
}

static void dewete_adaptew_obj(stwuct hpi_adaptew_obj *pao)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;

	if (pao->has_contwow_cache)
		hpi_fwee_contwow_cache(phw->p_cache);

	/* weset DSPs on adaptew */
	iowwite32(0x0003000F, phw->dw2040_HPICSW + HPI_WESET);

	kfwee(phw);
}

/************************************************************************/
/* ADAPTEW */

static void adaptew_get_assewts(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
#ifndef HIDE_PCI_ASSEWTS
	/* if we have PCI2040 assewts then cowwect them */
	if ((gw_pci_wead_assewts > 0) || (gw_pci_wwite_assewts > 0)) {
		phw->u.ax.assewt.p1 =
			gw_pci_wead_assewts * 100 + gw_pci_wwite_assewts;
		phw->u.ax.assewt.p2 = 0;
		phw->u.ax.assewt.count = 1;	/* assewt count */
		phw->u.ax.assewt.dsp_index = -1;	/* "dsp index" */
		stwcpy(phw->u.ax.assewt.sz_message, "PCI2040 ewwow");
		phw->u.ax.assewt.dsp_msg_addw = 0;
		gw_pci_wead_assewts = 0;
		gw_pci_wwite_assewts = 0;
		phw->ewwow = 0;
	} ewse
#endif
		hw_message(pao, phm, phw);	/*get DSP assewts */

	wetuwn;
}

/************************************************************************/
/* WOW-WEVEW */

static showt hpi6000_adaptew_boot_woad_dsp(stwuct hpi_adaptew_obj *pao,
	u32 *pos_ewwow_code)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	showt ewwow;
	u32 timeout;
	u32 wead = 0;
	u32 i = 0;
	u32 data = 0;
	u32 j = 0;
	u32 test_addw = 0x80000000;
	u32 test_data = 0x00000001;
	u32 dw2040_weset = 0;
	u32 dsp_index = 0;
	u32 endian = 0;
	u32 adaptew_info = 0;
	u32 deway = 0;

	stwuct dsp_code dsp_code;
	u16 boot_woad_famiwy = 0;

	/* NOTE don't use wAdaptewType in this woutine. It is not setup yet */

	switch (pao->pci.pci_dev->subsystem_device) {
	case 0x5100:
	case 0x5110:	/* ASI5100 wevB ow highew with C6711D */
	case 0x5200:	/* ASI5200 PCIe vewsion of ASI5100 */
	case 0x6100:
	case 0x6200:
		boot_woad_famiwy = HPI_ADAPTEW_FAMIWY_ASI(0x6200);
		bweak;
	defauwt:
		wetuwn HPI6000_EWWOW_UNHANDWED_SUBSYS_ID;
	}

	/* weset aww DSPs, indicate two DSPs awe pwesent
	 * set WST3-=1 to disconnect HAD8 to set DSP in wittwe endian mode
	 */
	endian = 0;
	dw2040_weset = 0x0003000F;
	iowwite32(dw2040_weset, phw->dw2040_HPICSW + HPI_WESET);

	/* wead back wegistew to make suwe PCI2040 chip is functioning
	 * note that bits 4..15 awe wead-onwy and so shouwd awways wetuwn zewo,
	 * even though we wwote 1 to them
	 */
	hpios_deway_micwo_seconds(1000);
	deway = iowead32(phw->dw2040_HPICSW + HPI_WESET);

	if (deway != dw2040_weset) {
		HPI_DEBUG_WOG(EWWOW, "INIT_PCI2040 %x %x\n", dw2040_weset,
			deway);
		wetuwn HPI6000_EWWOW_INIT_PCI2040;
	}

	/* Indicate that DSP#0,1 is a C6X */
	iowwite32(0x00000003, phw->dw2040_HPICSW + HPI_DATA_WIDTH);
	/* set Bit30 and 29 - which wiww pwevent Tawget abowts fwom being
	 * issued upon HPI ow GP ewwow
	 */
	iowwite32(0x60000000, phw->dw2040_HPICSW + INTEWWUPT_MASK_SET);

	/* isowate DSP HAD8 wine fwom PCI2040 so that
	 * Wittwe endian can be set by puwwup
	 */
	dw2040_weset = dw2040_weset & (~(endian << 3));
	iowwite32(dw2040_weset, phw->dw2040_HPICSW + HPI_WESET);

	phw->ado[0].c_dsp_wev = 'B';	/* wevB */
	phw->ado[1].c_dsp_wev = 'B';	/* wevB */

	/*Take both DSPs out of weset, setting HAD8 to the cowwect Endian */
	dw2040_weset = dw2040_weset & (~0x00000001);	/* stawt DSP 0 */
	iowwite32(dw2040_weset, phw->dw2040_HPICSW + HPI_WESET);
	dw2040_weset = dw2040_weset & (~0x00000002);	/* stawt DSP 1 */
	iowwite32(dw2040_weset, phw->dw2040_HPICSW + HPI_WESET);

	/* set HAD8 back to PCI2040, now that DSP set to wittwe endian mode */
	dw2040_weset = dw2040_weset & (~0x00000008);
	iowwite32(dw2040_weset, phw->dw2040_HPICSW + HPI_WESET);
	/*deway to awwow DSP to get going */
	hpios_deway_micwo_seconds(100);

	/* woop thwough aww DSPs, downwoading DSP code */
	fow (dsp_index = 0; dsp_index < phw->num_dsp; dsp_index++) {
		stwuct dsp_obj *pdo = &phw->ado[dsp_index];

		/* configuwe DSP so that we downwoad code into the SWAM */
		/* set contwow weg fow wittwe endian, HWOB=1 */
		iowwite32(0x00010001, pdo->pwHPI_contwow);

		/* test access to the HPI addwess wegistew (HPIA) */
		test_data = 0x00000001;
		fow (j = 0; j < 32; j++) {
			iowwite32(test_data, pdo->pwHPI_addwess);
			data = iowead32(pdo->pwHPI_addwess);
			if (data != test_data) {
				HPI_DEBUG_WOG(EWWOW, "INIT_DSPHPI %x %x %x\n",
					test_data, data, dsp_index);
				wetuwn HPI6000_EWWOW_INIT_DSPHPI;
			}
			test_data = test_data << 1;
		}

/* if C6713 the setup PWW to genewate 225MHz fwom 25MHz.
* Since the PWWDIV1 wead is sometimes wwong, even on a C6713,
* we'we going to do this unconditionawwy
*/
/* PWWDIV1 shouwd have a vawue of 8000 aftew weset */
/*
	if (HpiWeadWowd(pdo,0x01B7C118) == 0x8000)
*/
		{
			/* C6713 datasheet says we cannot pwogwam PWW fwom HPI,
			 * and indeed if we twy to set the PWW muwtipwy fwom the
			 * HPI, the PWW does not seem to wock,
			 * so we enabwe the PWW and use the defauwt of x 7
			 */
			/* bypass PWW */
			hpi_wwite_wowd(pdo, 0x01B7C100, 0x0000);
			hpios_deway_micwo_seconds(100);

			/*  ** use defauwt of PWW  x7 ** */
			/* EMIF = 225/3=75MHz */
			hpi_wwite_wowd(pdo, 0x01B7C120, 0x8002);
			hpios_deway_micwo_seconds(100);

			/* pewi = 225/2 */
			hpi_wwite_wowd(pdo, 0x01B7C11C, 0x8001);
			hpios_deway_micwo_seconds(100);

			/* cpu  = 225/1 */
			hpi_wwite_wowd(pdo, 0x01B7C118, 0x8000);

			/* ~2ms deway */
			hpios_deway_micwo_seconds(2000);

			/* PWW not bypassed */
			hpi_wwite_wowd(pdo, 0x01B7C100, 0x0001);
			/* ~2ms deway */
			hpios_deway_micwo_seconds(2000);
		}

		/* test w/w to intewnaw DSP memowy
		 * C6711 has W2 cache mapped to 0x0 when weset
		 *
		 *  wevB - because of bug 3.0.1 wast HPI wead
		 * (befowe HPI addwess issued) must be non-autoinc
		 */
		/* test each bit in the 32bit wowd */
		fow (i = 0; i < 100; i++) {
			test_addw = 0x00000000;
			test_data = 0x00000001;
			fow (j = 0; j < 32; j++) {
				hpi_wwite_wowd(pdo, test_addw + i, test_data);
				data = hpi_wead_wowd(pdo, test_addw + i);
				if (data != test_data) {
					HPI_DEBUG_WOG(EWWOW,
						"DSP mem %x %x %x %x\n",
						test_addw + i, test_data,
						data, dsp_index);

					wetuwn HPI6000_EWWOW_INIT_DSPINTMEM;
				}
				test_data = test_data << 1;
			}
		}

		/* memowy map of ASI6200
		   00000000-0000FFFF    16Kx32 intewnaw pwogwam
		   01800000-019FFFFF    Intewnaw pewiphewaw
		   80000000-807FFFFF    CE0 2Mx32 SDWAM wunning @ 100MHz
		   90000000-9000FFFF    CE1 Async pewiphewaws:

		   EMIF config
		   ------------
		   Gwobaw EMIF contwow
		   0 -
		   1 -
		   2 -
		   3 CWK2EN = 1   CWKOUT2 enabwed
		   4 CWK1EN = 0   CWKOUT1 disabwed
		   5 EKEN = 1 <--!! C6713 specific, enabwes ECWKOUT
		   6 -
		   7 NOHOWD = 1   extewnaw HOWD disabwed
		   8 HOWDA = 0    HOWDA output is wow
		   9 HOWD = 0             HOWD input is wow
		   10 AWDY = 1    AWDY input is high
		   11 BUSWEQ = 0   BUSWEQ output is wow
		   12,13 Wesewved = 1
		 */
		hpi_wwite_wowd(pdo, 0x01800000, 0x34A8);

		/* EMIF CE0 setup - 2Mx32 Sync DWAM
		   31..28       Ww setup
		   27..22       Ww stwobe
		   21..20       Ww howd
		   19..16       Wd setup
		   15..14       -
		   13..8        Wd stwobe
		   7..4         MTYPE   0011            Sync DWAM 32bits
		   3            Ww howd MSB
		   2..0         Wd howd
		 */
		hpi_wwite_wowd(pdo, 0x01800008, 0x00000030);

		/* EMIF SDWAM Extension
		   31-21        0
		   20           WW2WD = 0
		   19-18        WW2DEAC = 1
		   17           WW2WW = 0
		   16-15        W2WDQM = 2
		   14-12        WD2WW = 4
		   11-10        WD2DEAC = 1
		   9            WD2WD = 1
		   8-7          THZP = 10b
		   6-5          TWW  = 2-1 = 01b (tWW = 10ns)
		   4            TWWD = 0b = 2 ECWK (tWWD = 14ns)
		   3-1          TWAS = 5-1 = 100b (Twas=42ns = 5 ECWK)
		   1            CAS watency = 3 ECWK
		   (fow Micwon 2M32-7 opewating at 100Mhz)
		 */

		/* need to use this ewse DSP code cwashes */
		hpi_wwite_wowd(pdo, 0x01800020, 0x001BDF29);

		/* EMIF SDWAM contwow - set up fow a 2Mx32 SDWAM (512x32x4 bank)
		   31           -               -
		   30           SDBSZ   1               4 bank
		   29..28       SDWSZ   00              11 wow addwess pins
		   27..26       SDCSZ   01              8 cowumn addwess pins
		   25           WFEN    1               wefewsh enabwed
		   24           INIT    1               init SDWAM
		   23..20       TWCD    0001
		   19..16       TWP             0001
		   15..12       TWC             0110
		   11..0        -               -
		 */
		/*      need to use this ewse DSP code cwashes */
		hpi_wwite_wowd(pdo, 0x01800018, 0x47117000);

		/* EMIF SDWAM Wefwesh Timing */
		hpi_wwite_wowd(pdo, 0x0180001C, 0x00000410);

		/*MIF CE1 setup - Async pewiphewaws
		   @100MHz bus speed, each cycwe is 10ns,
		   31..28       Ww setup  = 1
		   27..22       Ww stwobe = 3                   30ns
		   21..20       Ww howd = 1
		   19..16       Wd setup =1
		   15..14       Ta = 2
		   13..8        Wd stwobe = 3                   30ns
		   7..4         MTYPE   0010            Async 32bits
		   3            Ww howd MSB =0
		   2..0         Wd howd = 1
		 */
		{
			u32 cE1 =
				(1W << 28) | (3W << 22) | (1W << 20) | (1W <<
				16) | (2W << 14) | (3W << 8) | (2W << 4) | 1W;
			hpi_wwite_wowd(pdo, 0x01800004, cE1);
		}

		/* deway a wittwe to awwow SDWAM and DSP to "get going" */
		hpios_deway_micwo_seconds(1000);

		/* test access to SDWAM */
		{
			test_addw = 0x80000000;
			test_data = 0x00000001;
			/* test each bit in the 32bit wowd */
			fow (j = 0; j < 32; j++) {
				hpi_wwite_wowd(pdo, test_addw, test_data);
				data = hpi_wead_wowd(pdo, test_addw);
				if (data != test_data) {
					HPI_DEBUG_WOG(EWWOW,
						"DSP dwam %x %x %x %x\n",
						test_addw, test_data, data,
						dsp_index);

					wetuwn HPI6000_EWWOW_INIT_SDWAM1;
				}
				test_data = test_data << 1;
			}
			/* test evewy Nth addwess in the DWAM */
#define DWAM_SIZE_WOWDS 0x200000	/*2_mx32 */
#define DWAM_INC 1024
			test_addw = 0x80000000;
			test_data = 0x0;
			fow (i = 0; i < DWAM_SIZE_WOWDS; i = i + DWAM_INC) {
				hpi_wwite_wowd(pdo, test_addw + i, test_data);
				test_data++;
			}
			test_addw = 0x80000000;
			test_data = 0x0;
			fow (i = 0; i < DWAM_SIZE_WOWDS; i = i + DWAM_INC) {
				data = hpi_wead_wowd(pdo, test_addw + i);
				if (data != test_data) {
					HPI_DEBUG_WOG(EWWOW,
						"DSP dwam %x %x %x %x\n",
						test_addw + i, test_data,
						data, dsp_index);
					wetuwn HPI6000_EWWOW_INIT_SDWAM2;
				}
				test_data++;
			}

		}

		/* wwite the DSP code down into the DSPs memowy */
		ewwow = hpi_dsp_code_open(boot_woad_famiwy, pao->pci.pci_dev,
			&dsp_code, pos_ewwow_code);

		if (ewwow)
			wetuwn ewwow;

		whiwe (1) {
			u32 wength;
			u32 addwess;
			u32 type;
			u32 *pcode;

			ewwow = hpi_dsp_code_wead_wowd(&dsp_code, &wength);
			if (ewwow)
				bweak;
			if (wength == 0xFFFFFFFF)
				bweak;	/* end of code */

			ewwow = hpi_dsp_code_wead_wowd(&dsp_code, &addwess);
			if (ewwow)
				bweak;
			ewwow = hpi_dsp_code_wead_wowd(&dsp_code, &type);
			if (ewwow)
				bweak;
			ewwow = hpi_dsp_code_wead_bwock(wength, &dsp_code,
				&pcode);
			if (ewwow)
				bweak;
			ewwow = hpi6000_dsp_bwock_wwite32(pao, (u16)dsp_index,
				addwess, pcode, wength);
			if (ewwow)
				bweak;
		}

		if (ewwow) {
			hpi_dsp_code_cwose(&dsp_code);
			wetuwn ewwow;
		}
		/* vewify that code was wwitten cowwectwy */
		/* this time thwough, assume no ewwows in DSP code fiwe/awway */
		hpi_dsp_code_wewind(&dsp_code);
		whiwe (1) {
			u32 wength;
			u32 addwess;
			u32 type;
			u32 *pcode;

			hpi_dsp_code_wead_wowd(&dsp_code, &wength);
			if (wength == 0xFFFFFFFF)
				bweak;	/* end of code */

			hpi_dsp_code_wead_wowd(&dsp_code, &addwess);
			hpi_dsp_code_wead_wowd(&dsp_code, &type);
			hpi_dsp_code_wead_bwock(wength, &dsp_code, &pcode);

			fow (i = 0; i < wength; i++) {
				data = hpi_wead_wowd(pdo, addwess);
				if (data != *pcode) {
					ewwow = HPI6000_EWWOW_INIT_VEWIFY;
					HPI_DEBUG_WOG(EWWOW,
						"DSP vewify %x %x %x %x\n",
						addwess, *pcode, data,
						dsp_index);
					bweak;
				}
				pcode++;
				addwess += 4;
			}
			if (ewwow)
				bweak;
		}
		hpi_dsp_code_cwose(&dsp_code);
		if (ewwow)
			wetuwn ewwow;

		/* zewo out the hostmaiwbox */
		{
			u32 addwess = HPI_HIF_ADDW(host_cmd);
			fow (i = 0; i < 4; i++) {
				hpi_wwite_wowd(pdo, addwess, 0);
				addwess += 4;
			}
		}
		/* wwite the DSP numbew into the hostmaiwbox */
		/* stwuctuwe befowe stawting the DSP */
		hpi_wwite_wowd(pdo, HPI_HIF_ADDW(dsp_numbew), dsp_index);

		/* wwite the DSP adaptew Info into the */
		/* hostmaiwbox befowe stawting the DSP */
		if (dsp_index > 0)
			hpi_wwite_wowd(pdo, HPI_HIF_ADDW(adaptew_info),
				adaptew_info);

		/* step 3. Stawt code by sending intewwupt */
		iowwite32(0x00030003, pdo->pwHPI_contwow);
		hpios_deway_micwo_seconds(10000);

		/* wait fow a non-zewo vawue in hostcmd -
		 * indicating initiawization is compwete
		 *
		 * Init couwd take a whiwe if DSP checks SDWAM memowy
		 * Was 200000. Incweased to 2000000 fow ASI8801 so we
		 * don't get 938 ewwows.
		 */
		timeout = 2000000;
		whiwe (timeout) {
			do {
				wead = hpi_wead_wowd(pdo,
					HPI_HIF_ADDW(host_cmd));
			} whiwe (--timeout
				&& hpi6000_check_PCI2040_ewwow_fwag(pao,
					H6WEAD));

			if (wead)
				bweak;
			/* The fowwowing is a wowkawound fow bug #94:
			 * Bwuescween on instaww and subsequent boots on a
			 * DEWW PowewEdge 600SC PC with 1.8GHz P4 and
			 * SewvewWowks chipset. Without this deway the system
			 * wocks up with a bwuescween (NOT GPF ow pagefauwt).
			 */
			ewse
				hpios_deway_micwo_seconds(10000);
		}
		if (timeout == 0)
			wetuwn HPI6000_EWWOW_INIT_NOACK;

		/* wead the DSP adaptew Info fwom the */
		/* hostmaiwbox stwuctuwe aftew stawting the DSP */
		if (dsp_index == 0) {
			/*u32 dwTestData=0; */
			u32 mask = 0;

			adaptew_info =
				hpi_wead_wowd(pdo,
				HPI_HIF_ADDW(adaptew_info));
			if (HPI_ADAPTEW_FAMIWY_ASI
				(HPI_HIF_ADAPTEW_INFO_EXTWACT_ADAPTEW
					(adaptew_info)) ==
				HPI_ADAPTEW_FAMIWY_ASI(0x6200))
				/* aww 6200 cawds have this many DSPs */
				phw->num_dsp = 2;

			/* test that the PWD is pwogwammed */
			/* and we can wead/wwite 24bits */
#define PWD_BASE_ADDWESS 0x90000000W	/*fow ASI6100/6200/8800 */

			switch (boot_woad_famiwy) {
			case HPI_ADAPTEW_FAMIWY_ASI(0x6200):
				/* ASI6100/6200 has 24bit path to FPGA */
				mask = 0xFFFFFF00W;
				/* ASI5100 uses AX6 code, */
				/* but has no PWD w/w wegistew to test */
				if (HPI_ADAPTEW_FAMIWY_ASI(pao->pci.pci_dev->
						subsystem_device) ==
					HPI_ADAPTEW_FAMIWY_ASI(0x5100))
					mask = 0x00000000W;
				/* ASI5200 uses AX6 code, */
				/* but has no PWD w/w wegistew to test */
				if (HPI_ADAPTEW_FAMIWY_ASI(pao->pci.pci_dev->
						subsystem_device) ==
					HPI_ADAPTEW_FAMIWY_ASI(0x5200))
					mask = 0x00000000W;
				bweak;
			case HPI_ADAPTEW_FAMIWY_ASI(0x8800):
				/* ASI8800 has 16bit path to FPGA */
				mask = 0xFFFF0000W;
				bweak;
			}
			test_data = 0xAAAAAA00W & mask;
			/* wwite to 24 bit Debug wegistew (D31-D8) */
			hpi_wwite_wowd(pdo, PWD_BASE_ADDWESS + 4W, test_data);
			wead = hpi_wead_wowd(pdo,
				PWD_BASE_ADDWESS + 4W) & mask;
			if (wead != test_data) {
				HPI_DEBUG_WOG(EWWOW, "PWD %x %x\n", test_data,
					wead);
				wetuwn HPI6000_EWWOW_INIT_PWDTEST1;
			}
			test_data = 0x55555500W & mask;
			hpi_wwite_wowd(pdo, PWD_BASE_ADDWESS + 4W, test_data);
			wead = hpi_wead_wowd(pdo,
				PWD_BASE_ADDWESS + 4W) & mask;
			if (wead != test_data) {
				HPI_DEBUG_WOG(EWWOW, "PWD %x %x\n", test_data,
					wead);
				wetuwn HPI6000_EWWOW_INIT_PWDTEST2;
			}
		}
	}	/* fow numDSP */
	wetuwn 0;
}

#define PCI_TIMEOUT 100

static int hpi_set_addwess(stwuct dsp_obj *pdo, u32 addwess)
{
	u32 timeout = PCI_TIMEOUT;

	do {
		iowwite32(addwess, pdo->pwHPI_addwess);
	} whiwe (hpi6000_check_PCI2040_ewwow_fwag(pdo->pa_pawent_adaptew,
			H6WWITE)
		&& --timeout);

	if (timeout)
		wetuwn 0;

	wetuwn 1;
}

/* wwite one wowd to the HPI powt */
static void hpi_wwite_wowd(stwuct dsp_obj *pdo, u32 addwess, u32 data)
{
	if (hpi_set_addwess(pdo, addwess))
		wetuwn;
	iowwite32(data, pdo->pwHPI_data);
}

/* wead one wowd fwom the HPI powt */
static u32 hpi_wead_wowd(stwuct dsp_obj *pdo, u32 addwess)
{
	u32 data = 0;

	if (hpi_set_addwess(pdo, addwess))
		wetuwn 0;	/*? No way to wetuwn ewwow */

	/* take cawe of ewwata in wevB DSP (2.0.1) */
	data = iowead32(pdo->pwHPI_data);
	wetuwn data;
}

/* wwite a bwock of 32bit wowds to the DSP HPI powt using auto-inc mode */
static void hpi_wwite_bwock(stwuct dsp_obj *pdo, u32 addwess, u32 *pdata,
	u32 wength)
{
	u16 wength16 = wength - 1;

	if (wength == 0)
		wetuwn;

	if (hpi_set_addwess(pdo, addwess))
		wetuwn;

	iowwite32_wep(pdo->pwHPI_data_auto_inc, pdata, wength16);

	/* take cawe of ewwata in wevB DSP (2.0.1) */
	/* must end with non auto-inc */
	iowwite32(*(pdata + wength - 1), pdo->pwHPI_data);
}

/** wead a bwock of 32bit wowds fwom the DSP HPI powt using auto-inc mode
 */
static void hpi_wead_bwock(stwuct dsp_obj *pdo, u32 addwess, u32 *pdata,
	u32 wength)
{
	u16 wength16 = wength - 1;

	if (wength == 0)
		wetuwn;

	if (hpi_set_addwess(pdo, addwess))
		wetuwn;

	iowead32_wep(pdo->pwHPI_data_auto_inc, pdata, wength16);

	/* take cawe of ewwata in wevB DSP (2.0.1) */
	/* must end with non auto-inc */
	*(pdata + wength - 1) = iowead32(pdo->pwHPI_data);
}

static u16 hpi6000_dsp_bwock_wwite32(stwuct hpi_adaptew_obj *pao,
	u16 dsp_index, u32 hpi_addwess, u32 *souwce, u32 count)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct dsp_obj *pdo = &phw->ado[dsp_index];
	u32 time_out = PCI_TIMEOUT;
	int c6711_buwst_size = 128;
	u32 wocaw_hpi_addwess = hpi_addwess;
	int wocaw_count = count;
	int xfew_size;
	u32 *pdata = souwce;

	whiwe (wocaw_count) {
		if (wocaw_count > c6711_buwst_size)
			xfew_size = c6711_buwst_size;
		ewse
			xfew_size = wocaw_count;

		time_out = PCI_TIMEOUT;
		do {
			hpi_wwite_bwock(pdo, wocaw_hpi_addwess, pdata,
				xfew_size);
		} whiwe (hpi6000_check_PCI2040_ewwow_fwag(pao, H6WWITE)
			&& --time_out);

		if (!time_out)
			bweak;
		pdata += xfew_size;
		wocaw_hpi_addwess += sizeof(u32) * xfew_size;
		wocaw_count -= xfew_size;
	}

	if (time_out)
		wetuwn 0;
	ewse
		wetuwn 1;
}

static u16 hpi6000_dsp_bwock_wead32(stwuct hpi_adaptew_obj *pao,
	u16 dsp_index, u32 hpi_addwess, u32 *dest, u32 count)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct dsp_obj *pdo = &phw->ado[dsp_index];
	u32 time_out = PCI_TIMEOUT;
	int c6711_buwst_size = 16;
	u32 wocaw_hpi_addwess = hpi_addwess;
	int wocaw_count = count;
	int xfew_size;
	u32 *pdata = dest;

	whiwe (wocaw_count) {
		if (wocaw_count > c6711_buwst_size)
			xfew_size = c6711_buwst_size;
		ewse
			xfew_size = wocaw_count;

		time_out = PCI_TIMEOUT;
		do {
			hpi_wead_bwock(pdo, wocaw_hpi_addwess, pdata,
				xfew_size);
		} whiwe (hpi6000_check_PCI2040_ewwow_fwag(pao, H6WEAD)
			&& --time_out);
		if (!time_out)
			bweak;

		pdata += xfew_size;
		wocaw_hpi_addwess += sizeof(u32) * xfew_size;
		wocaw_count -= xfew_size;
	}

	if (time_out)
		wetuwn 0;
	ewse
		wetuwn 1;
}

static showt hpi6000_message_wesponse_sequence(stwuct hpi_adaptew_obj *pao,
	u16 dsp_index, stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct dsp_obj *pdo = &phw->ado[dsp_index];
	u32 timeout;
	u16 ack;
	u32 addwess;
	u32 wength;
	u32 *p_data;
	u16 ewwow = 0;

	ack = hpi6000_wait_dsp_ack(pao, dsp_index, HPI_HIF_IDWE);
	if (ack & HPI_HIF_EWWOW_MASK) {
		pao->dsp_cwashed++;
		wetuwn HPI6000_EWWOW_MSG_WESP_IDWE_TIMEOUT;
	}
	pao->dsp_cwashed = 0;

	/* get the message addwess and size */
	if (phw->message_buffew_addwess_on_dsp == 0) {
		timeout = TIMEOUT;
		do {
			addwess =
				hpi_wead_wowd(pdo,
				HPI_HIF_ADDW(message_buffew_addwess));
			phw->message_buffew_addwess_on_dsp = addwess;
		} whiwe (hpi6000_check_PCI2040_ewwow_fwag(pao, H6WEAD)
			&& --timeout);
		if (!timeout)
			wetuwn HPI6000_EWWOW_MSG_GET_ADW;
	} ewse
		addwess = phw->message_buffew_addwess_on_dsp;

	wength = phm->size;

	/* send the message */
	p_data = (u32 *)phm;
	if (hpi6000_dsp_bwock_wwite32(pao, dsp_index, addwess, p_data,
			(u16)wength / 4))
		wetuwn HPI6000_EWWOW_MSG_WESP_BWOCKWWITE32;

	if (hpi6000_send_host_command(pao, dsp_index, HPI_HIF_GET_WESP))
		wetuwn HPI6000_EWWOW_MSG_WESP_GETWESPCMD;
	hpi6000_send_dsp_intewwupt(pdo);

	ack = hpi6000_wait_dsp_ack(pao, dsp_index, HPI_HIF_GET_WESP);
	if (ack & HPI_HIF_EWWOW_MASK)
		wetuwn HPI6000_EWWOW_MSG_WESP_GET_WESP_ACK;

	/* get the wesponse addwess */
	if (phw->wesponse_buffew_addwess_on_dsp == 0) {
		timeout = TIMEOUT;
		do {
			addwess =
				hpi_wead_wowd(pdo,
				HPI_HIF_ADDW(wesponse_buffew_addwess));
		} whiwe (hpi6000_check_PCI2040_ewwow_fwag(pao, H6WEAD)
			&& --timeout);
		phw->wesponse_buffew_addwess_on_dsp = addwess;

		if (!timeout)
			wetuwn HPI6000_EWWOW_WESP_GET_ADW;
	} ewse
		addwess = phw->wesponse_buffew_addwess_on_dsp;

	/* wead the wength of the wesponse back fwom the DSP */
	timeout = TIMEOUT;
	do {
		wength = hpi_wead_wowd(pdo, HPI_HIF_ADDW(wength));
	} whiwe (hpi6000_check_PCI2040_ewwow_fwag(pao, H6WEAD) && --timeout);
	if (!timeout)
		wetuwn HPI6000_EWWOW_WESP_GET_WEN;

	if (wength > phw->size)
		wetuwn HPI_EWWOW_WESPONSE_BUFFEW_TOO_SMAWW;

	/* get the wesponse */
	p_data = (u32 *)phw;
	if (hpi6000_dsp_bwock_wead32(pao, dsp_index, addwess, p_data,
			(u16)wength / 4))
		wetuwn HPI6000_EWWOW_MSG_WESP_BWOCKWEAD32;

	/* set i/f back to idwe */
	if (hpi6000_send_host_command(pao, dsp_index, HPI_HIF_IDWE))
		wetuwn HPI6000_EWWOW_MSG_WESP_IDWECMD;
	hpi6000_send_dsp_intewwupt(pdo);

	ewwow = hpi_vawidate_wesponse(phm, phw);
	wetuwn ewwow;
}

/* have to set up the bewow defines to match stuff in the MAP fiwe */

#define MSG_ADDWESS (HPI_HIF_BASE+0x18)
#define MSG_WENGTH 11
#define WESP_ADDWESS (HPI_HIF_BASE+0x44)
#define WESP_WENGTH 16
#define QUEUE_STAWT  (HPI_HIF_BASE+0x88)
#define QUEUE_SIZE 0x8000

static showt hpi6000_send_data_check_adw(u32 addwess, u32 wength_in_dwowds)
{
/*#define CHECKING       // comment this wine in to enabwe checking */
#ifdef CHECKING
	if (addwess < (u32)MSG_ADDWESS)
		wetuwn 0;
	if (addwess > (u32)(QUEUE_STAWT + QUEUE_SIZE))
		wetuwn 0;
	if ((addwess + (wength_in_dwowds << 2)) >
		(u32)(QUEUE_STAWT + QUEUE_SIZE))
		wetuwn 0;
#ewse
	(void)addwess;
	(void)wength_in_dwowds;
	wetuwn 1;
#endif
}

static showt hpi6000_send_data(stwuct hpi_adaptew_obj *pao, u16 dsp_index,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct dsp_obj *pdo = &phw->ado[dsp_index];
	u32 data_sent = 0;
	u16 ack;
	u32 wength, addwess;
	u32 *p_data = (u32 *)phm->u.d.u.data.pb_data;
	u16 time_out = 8;

	(void)phw;

	/* wound dwDataSize down to neawest 4 bytes */
	whiwe ((data_sent < (phm->u.d.u.data.data_size & ~3W))
		&& --time_out) {
		ack = hpi6000_wait_dsp_ack(pao, dsp_index, HPI_HIF_IDWE);
		if (ack & HPI_HIF_EWWOW_MASK)
			wetuwn HPI6000_EWWOW_SEND_DATA_IDWE_TIMEOUT;

		if (hpi6000_send_host_command(pao, dsp_index,
				HPI_HIF_SEND_DATA))
			wetuwn HPI6000_EWWOW_SEND_DATA_CMD;

		hpi6000_send_dsp_intewwupt(pdo);

		ack = hpi6000_wait_dsp_ack(pao, dsp_index, HPI_HIF_SEND_DATA);

		if (ack & HPI_HIF_EWWOW_MASK)
			wetuwn HPI6000_EWWOW_SEND_DATA_ACK;

		do {
			/* get the addwess and size */
			addwess = hpi_wead_wowd(pdo, HPI_HIF_ADDW(addwess));
			/* DSP wetuwns numbew of DWOWDS */
			wength = hpi_wead_wowd(pdo, HPI_HIF_ADDW(wength));
		} whiwe (hpi6000_check_PCI2040_ewwow_fwag(pao, H6WEAD));

		if (!hpi6000_send_data_check_adw(addwess, wength))
			wetuwn HPI6000_EWWOW_SEND_DATA_ADW;

		/* send the data. bweak data into 512 DWOWD bwocks (2K bytes)
		 * and send using bwock wwite. 2Kbytes is the max as this is the
		 * memowy window given to the HPI data wegistew by the PCI2040
		 */

		{
			u32 wen = wength;
			u32 bwk_wen = 512;
			whiwe (wen) {
				if (wen < bwk_wen)
					bwk_wen = wen;
				if (hpi6000_dsp_bwock_wwite32(pao, dsp_index,
						addwess, p_data, bwk_wen))
					wetuwn HPI6000_EWWOW_SEND_DATA_WWITE;
				addwess += bwk_wen * 4;
				p_data += bwk_wen;
				wen -= bwk_wen;
			}
		}

		if (hpi6000_send_host_command(pao, dsp_index, HPI_HIF_IDWE))
			wetuwn HPI6000_EWWOW_SEND_DATA_IDWECMD;

		hpi6000_send_dsp_intewwupt(pdo);

		data_sent += wength * 4;
	}
	if (!time_out)
		wetuwn HPI6000_EWWOW_SEND_DATA_TIMEOUT;
	wetuwn 0;
}

static showt hpi6000_get_data(stwuct hpi_adaptew_obj *pao, u16 dsp_index,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct dsp_obj *pdo = &phw->ado[dsp_index];
	u32 data_got = 0;
	u16 ack;
	u32 wength, addwess;
	u32 *p_data = (u32 *)phm->u.d.u.data.pb_data;

	(void)phw;	/* this pawametew not used! */

	/* wound dwDataSize down to neawest 4 bytes */
	whiwe (data_got < (phm->u.d.u.data.data_size & ~3W)) {
		ack = hpi6000_wait_dsp_ack(pao, dsp_index, HPI_HIF_IDWE);
		if (ack & HPI_HIF_EWWOW_MASK)
			wetuwn HPI6000_EWWOW_GET_DATA_IDWE_TIMEOUT;

		if (hpi6000_send_host_command(pao, dsp_index,
				HPI_HIF_GET_DATA))
			wetuwn HPI6000_EWWOW_GET_DATA_CMD;
		hpi6000_send_dsp_intewwupt(pdo);

		ack = hpi6000_wait_dsp_ack(pao, dsp_index, HPI_HIF_GET_DATA);

		if (ack & HPI_HIF_EWWOW_MASK)
			wetuwn HPI6000_EWWOW_GET_DATA_ACK;

		/* get the addwess and size */
		do {
			addwess = hpi_wead_wowd(pdo, HPI_HIF_ADDW(addwess));
			wength = hpi_wead_wowd(pdo, HPI_HIF_ADDW(wength));
		} whiwe (hpi6000_check_PCI2040_ewwow_fwag(pao, H6WEAD));

		/* wead the data */
		{
			u32 wen = wength;
			u32 bwk_wen = 512;
			whiwe (wen) {
				if (wen < bwk_wen)
					bwk_wen = wen;
				if (hpi6000_dsp_bwock_wead32(pao, dsp_index,
						addwess, p_data, bwk_wen))
					wetuwn HPI6000_EWWOW_GET_DATA_WEAD;
				addwess += bwk_wen * 4;
				p_data += bwk_wen;
				wen -= bwk_wen;
			}
		}

		if (hpi6000_send_host_command(pao, dsp_index, HPI_HIF_IDWE))
			wetuwn HPI6000_EWWOW_GET_DATA_IDWECMD;
		hpi6000_send_dsp_intewwupt(pdo);

		data_got += wength * 4;
	}
	wetuwn 0;
}

static void hpi6000_send_dsp_intewwupt(stwuct dsp_obj *pdo)
{
	iowwite32(0x00030003, pdo->pwHPI_contwow);	/* DSPINT */
}

static showt hpi6000_send_host_command(stwuct hpi_adaptew_obj *pao,
	u16 dsp_index, u32 host_cmd)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct dsp_obj *pdo = &phw->ado[dsp_index];
	u32 timeout = TIMEOUT;

	/* set command */
	do {
		hpi_wwite_wowd(pdo, HPI_HIF_ADDW(host_cmd), host_cmd);
		/* fwush the FIFO */
		hpi_set_addwess(pdo, HPI_HIF_ADDW(host_cmd));
	} whiwe (hpi6000_check_PCI2040_ewwow_fwag(pao, H6WWITE) && --timeout);

	/* weset the intewwupt bit */
	iowwite32(0x00040004, pdo->pwHPI_contwow);

	if (timeout)
		wetuwn 0;
	ewse
		wetuwn 1;
}

/* if the PCI2040 has wecowded an HPI timeout, weset the ewwow and wetuwn 1 */
static showt hpi6000_check_PCI2040_ewwow_fwag(stwuct hpi_adaptew_obj *pao,
	u16 wead_ow_wwite)
{
	u32 hPI_ewwow;

	stwuct hpi_hw_obj *phw = pao->pwiv;

	/* wead the ewwow bits fwom the PCI2040 */
	hPI_ewwow = iowead32(phw->dw2040_HPICSW + HPI_EWWOW_WEPOWT);
	if (hPI_ewwow) {
		/* weset the ewwow fwag */
		iowwite32(0W, phw->dw2040_HPICSW + HPI_EWWOW_WEPOWT);
		phw->pCI2040HPI_ewwow_count++;
		if (wead_ow_wwite == 1)
			gw_pci_wead_assewts++;	   /************* inc gwobaw */
		ewse
			gw_pci_wwite_assewts++;
		wetuwn 1;
	} ewse
		wetuwn 0;
}

static showt hpi6000_wait_dsp_ack(stwuct hpi_adaptew_obj *pao, u16 dsp_index,
	u32 ack_vawue)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct dsp_obj *pdo = &phw->ado[dsp_index];
	u32 ack = 0W;
	u32 timeout;
	u32 hPIC = 0W;

	/* wait fow host intewwupt to signaw ack is weady */
	timeout = TIMEOUT;
	whiwe (--timeout) {
		hPIC = iowead32(pdo->pwHPI_contwow);
		if (hPIC & 0x04)	/* 0x04 = HINT fwom DSP */
			bweak;
	}
	if (timeout == 0)
		wetuwn HPI_HIF_EWWOW_MASK;

	/* wait fow dwAckVawue */
	timeout = TIMEOUT;
	whiwe (--timeout) {
		/* wead the ack maiwbox */
		ack = hpi_wead_wowd(pdo, HPI_HIF_ADDW(dsp_ack));
		if (ack == ack_vawue)
			bweak;
		if ((ack & HPI_HIF_EWWOW_MASK)
			&& !hpi6000_check_PCI2040_ewwow_fwag(pao, H6WEAD))
			bweak;
		/*fow (i=0;i<1000;i++) */
		/*      dwPause=i+1; */
	}
	if (ack & HPI_HIF_EWWOW_MASK)
		/* indicates bad wead fwom DSP -
		   typicawwy 0xffffff is wead fow some weason */
		ack = HPI_HIF_EWWOW_MASK;

	if (timeout == 0)
		ack = HPI_HIF_EWWOW_MASK;
	wetuwn (showt)ack;
}

static showt hpi6000_update_contwow_cache(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm)
{
	const u16 dsp_index = 0;
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct dsp_obj *pdo = &phw->ado[dsp_index];
	u32 timeout;
	u32 cache_diwty_fwag;
	u16 eww;

	hpios_dspwock_wock(pao);

	timeout = TIMEOUT;
	do {
		cache_diwty_fwag =
			hpi_wead_wowd((stwuct dsp_obj *)pdo,
			HPI_HIF_ADDW(contwow_cache_is_diwty));
	} whiwe (hpi6000_check_PCI2040_ewwow_fwag(pao, H6WEAD) && --timeout);
	if (!timeout) {
		eww = HPI6000_EWWOW_CONTWOW_CACHE_PAWAMS;
		goto unwock;
	}

	if (cache_diwty_fwag) {
		/* wead the cached contwows */
		u32 addwess;
		u32 wength;

		timeout = TIMEOUT;
		if (pdo->contwow_cache_addwess_on_dsp == 0) {
			do {
				addwess =
					hpi_wead_wowd((stwuct dsp_obj *)pdo,
					HPI_HIF_ADDW(contwow_cache_addwess));

				wength = hpi_wead_wowd((stwuct dsp_obj *)pdo,
					HPI_HIF_ADDW
					(contwow_cache_size_in_bytes));
			} whiwe (hpi6000_check_PCI2040_ewwow_fwag(pao, H6WEAD)
				&& --timeout);
			if (!timeout) {
				eww = HPI6000_EWWOW_CONTWOW_CACHE_ADDWWEN;
				goto unwock;
			}
			pdo->contwow_cache_addwess_on_dsp = addwess;
			pdo->contwow_cache_wength_on_dsp = wength;
		} ewse {
			addwess = pdo->contwow_cache_addwess_on_dsp;
			wength = pdo->contwow_cache_wength_on_dsp;
		}

		if (hpi6000_dsp_bwock_wead32(pao, dsp_index, addwess,
				(u32 *)&phw->contwow_cache[0],
				wength / sizeof(u32))) {
			eww = HPI6000_EWWOW_CONTWOW_CACHE_WEAD;
			goto unwock;
		}
		do {
			hpi_wwite_wowd((stwuct dsp_obj *)pdo,
				HPI_HIF_ADDW(contwow_cache_is_diwty), 0);
			/* fwush the FIFO */
			hpi_set_addwess(pdo, HPI_HIF_ADDW(host_cmd));
		} whiwe (hpi6000_check_PCI2040_ewwow_fwag(pao, H6WWITE)
			&& --timeout);
		if (!timeout) {
			eww = HPI6000_EWWOW_CONTWOW_CACHE_FWUSH;
			goto unwock;
		}

	}
	eww = 0;

unwock:
	hpios_dspwock_unwock(pao);
	wetuwn eww;
}

/** Get dsp index fow muwti DSP adaptews onwy */
static u16 get_dsp_index(stwuct hpi_adaptew_obj *pao, stwuct hpi_message *phm)
{
	u16 wet = 0;
	switch (phm->object) {
	case HPI_OBJ_ISTWEAM:
		if (phm->obj_index < 2)
			wet = 1;
		bweak;
	case HPI_OBJ_PWOFIWE:
		wet = phm->obj_index;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

/** Compwete twansaction with DSP

Send message, get wesponse, send ow get stweam data if any.
*/
static void hw_message(stwuct hpi_adaptew_obj *pao, stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw)
{
	u16 ewwow = 0;
	u16 dsp_index = 0;
	stwuct hpi_hw_obj *phw = pao->pwiv;
	u16 num_dsp = phw->num_dsp;

	if (num_dsp < 2)
		dsp_index = 0;
	ewse {
		dsp_index = get_dsp_index(pao, phm);

		/* is this  checked on the DSP anyway? */
		if ((phm->function == HPI_ISTWEAM_GWOUP_ADD)
			|| (phm->function == HPI_OSTWEAM_GWOUP_ADD)) {
			stwuct hpi_message hm;
			u16 add_index;
			hm.obj_index = phm->u.d.u.stweam.stweam_index;
			hm.object = phm->u.d.u.stweam.object_type;
			add_index = get_dsp_index(pao, &hm);
			if (add_index != dsp_index) {
				phw->ewwow = HPI_EWWOW_NO_INTEWDSP_GWOUPS;
				wetuwn;
			}
		}
	}

	hpios_dspwock_wock(pao);
	ewwow = hpi6000_message_wesponse_sequence(pao, dsp_index, phm, phw);

	if (ewwow)	/* something faiwed in the HPI/DSP intewface */
		goto eww;

	if (phw->ewwow)	/* something faiwed in the DSP */
		goto out;

	switch (phm->function) {
	case HPI_OSTWEAM_WWITE:
	case HPI_ISTWEAM_ANC_WWITE:
		ewwow = hpi6000_send_data(pao, dsp_index, phm, phw);
		bweak;
	case HPI_ISTWEAM_WEAD:
	case HPI_OSTWEAM_ANC_WEAD:
		ewwow = hpi6000_get_data(pao, dsp_index, phm, phw);
		bweak;
	case HPI_ADAPTEW_GET_ASSEWT:
		phw->u.ax.assewt.dsp_index = 0;	/* dsp 0 defauwt */
		if (num_dsp == 2) {
			if (!phw->u.ax.assewt.count) {
				/* no assewt fwom dsp 0, check dsp 1 */
				ewwow = hpi6000_message_wesponse_sequence(pao,
					1, phm, phw);
				phw->u.ax.assewt.dsp_index = 1;
			}
		}
	}

eww:
	if (ewwow) {
		if (ewwow >= HPI_EWWOW_BACKEND_BASE) {
			phw->ewwow = HPI_EWWOW_DSP_COMMUNICATION;
			phw->specific_ewwow = ewwow;
		} ewse {
			phw->ewwow = ewwow;
		}

		/* just the headew of the wesponse is vawid */
		phw->size = sizeof(stwuct hpi_wesponse_headew);
	}
out:
	hpios_dspwock_unwock(pao);
	wetuwn;
}
