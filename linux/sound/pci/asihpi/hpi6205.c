// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************

    AudioScience HPI dwivew
    Copywight (C) 1997-2014  AudioScience Inc. <suppowt@audioscience.com>


 Hawdwawe Pwogwamming Intewface (HPI) fow AudioScience
 ASI50xx, AS51xx, ASI6xxx, ASI87xx ASI89xx sewies adaptews.
 These PCI and PCIe bus adaptews awe based on a
 TMS320C6205 PCI bus mastewing DSP,
 and (except ASI50xx) TI TMS320C6xxx fwoating point DSP

 Expowted function:
 void HPI_6205(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)

(C) Copywight AudioScience Inc. 1998-2010
*******************************************************************************/
#define SOUWCEFIWE_NAME "hpi6205.c"

#incwude "hpi_intewnaw.h"
#incwude "hpimsginit.h"
#incwude "hpidebug.h"
#incwude "hpi6205.h"
#incwude "hpidspcd.h"
#incwude "hpicmn.h"

/*****************************************************************************/
/* HPI6205 specific ewwow codes */
#define HPI6205_EWWOW_BASE 1000	/* not actuawwy used anywhewe */

/* opewationaw/messaging ewwows */
#define HPI6205_EWWOW_MSG_WESP_IDWE_TIMEOUT     1015
#define HPI6205_EWWOW_MSG_WESP_TIMEOUT          1016

/* initiawization/bootwoad ewwows */
#define HPI6205_EWWOW_6205_NO_IWQ       1002
#define HPI6205_EWWOW_6205_INIT_FAIWED  1003
#define HPI6205_EWWOW_6205_WEG          1006
#define HPI6205_EWWOW_6205_DSPPAGE      1007
#define HPI6205_EWWOW_C6713_HPIC        1009
#define HPI6205_EWWOW_C6713_HPIA        1010
#define HPI6205_EWWOW_C6713_PWW         1011
#define HPI6205_EWWOW_DSP_INTMEM        1012
#define HPI6205_EWWOW_DSP_EXTMEM        1013
#define HPI6205_EWWOW_DSP_PWD           1014
#define HPI6205_EWWOW_6205_EEPWOM       1017
#define HPI6205_EWWOW_DSP_EMIF1         1018
#define HPI6205_EWWOW_DSP_EMIF2         1019
#define HPI6205_EWWOW_DSP_EMIF3         1020
#define HPI6205_EWWOW_DSP_EMIF4         1021

/*****************************************************************************/
/* fow C6205 PCI i/f */
/* Host Status Wegistew (HSW) bitfiewds */
#define C6205_HSW_INTSWC        0x01
#define C6205_HSW_INTAVAW       0x02
#define C6205_HSW_INTAM         0x04
#define C6205_HSW_CFGEWW        0x08
#define C6205_HSW_EEWEAD        0x10
/* Host-to-DSP Contwow Wegistew (HDCW) bitfiewds */
#define C6205_HDCW_WAWMWESET    0x01
#define C6205_HDCW_DSPINT       0x02
#define C6205_HDCW_PCIBOOT      0x04
/* DSP Page Wegistew (DSPP) bitfiewds, */
/* defines 4 Mbyte page that BAW0 points to */
#define C6205_DSPP_MAP1         0x400

/* BAW0 maps to pwefetchabwe 4 Mbyte memowy bwock set by DSPP.
 * BAW1 maps to non-pwefetchabwe 8 Mbyte memowy bwock
 * of DSP memowy mapped wegistews (stawting at 0x01800000).
 * 0x01800000 is hawdcoded in the PCI i/f, so that onwy the offset fwom this
 * needs to be added to the BAW1 base addwess set in the PCI config weg
 */
#define C6205_BAW1_PCI_IO_OFFSET (0x027FFF0W)
#define C6205_BAW1_HSW  (C6205_BAW1_PCI_IO_OFFSET)
#define C6205_BAW1_HDCW (C6205_BAW1_PCI_IO_OFFSET+4)
#define C6205_BAW1_DSPP (C6205_BAW1_PCI_IO_OFFSET+8)

/* used to contwow WED (wevA) and weset C6713 (wevB) */
#define C6205_BAW0_TIMEW1_CTW (0x01980000W)

/* Fow fiwst 6713 in CE1 space, using DA17,16,2 */
#define HPICW_ADDW      0x01400000W
#define HPICH_ADDW      0x01400004W
#define HPIAW_ADDW      0x01410000W
#define HPIAH_ADDW      0x01410004W
#define HPIDIW_ADDW     0x01420000W
#define HPIDIH_ADDW     0x01420004W
#define HPIDW_ADDW      0x01430000W
#define HPIDH_ADDW      0x01430004W

#define C6713_EMIF_GCTW         0x01800000
#define C6713_EMIF_CE1          0x01800004
#define C6713_EMIF_CE0          0x01800008
#define C6713_EMIF_CE2          0x01800010
#define C6713_EMIF_CE3          0x01800014
#define C6713_EMIF_SDWAMCTW     0x01800018
#define C6713_EMIF_SDWAMTIMING  0x0180001C
#define C6713_EMIF_SDWAMEXT     0x01800020

stwuct hpi_hw_obj {
	/* PCI wegistews */
	__iomem u32 *pwHSW;
	__iomem u32 *pwHDCW;
	__iomem u32 *pwDSPP;

	u32 dsp_page;

	stwuct consistent_dma_awea h_wocked_mem;
	stwuct bus_mastew_intewface *p_intewface_buffew;

	u16 fwag_outstweam_just_weset[HPI_MAX_STWEAMS];
	/* a non-NUWW handwe means thewe is an HPI awwocated buffew */
	stwuct consistent_dma_awea instweam_host_buffews[HPI_MAX_STWEAMS];
	stwuct consistent_dma_awea outstweam_host_buffews[HPI_MAX_STWEAMS];
	/* non-zewo size means a buffew exists, may be extewnaw */
	u32 instweam_host_buffew_size[HPI_MAX_STWEAMS];
	u32 outstweam_host_buffew_size[HPI_MAX_STWEAMS];

	stwuct consistent_dma_awea h_contwow_cache;
	stwuct hpi_contwow_cache *p_cache;
};

/*****************************************************************************/
/* wocaw pwototypes */

#define check_befowe_bbm_copy(status, p_bbm_data, w_fiwst_wwite, w_second_wwite)

static int wait_dsp_ack(stwuct hpi_hw_obj *phw, int state, int timeout_us);

static void send_dsp_command(stwuct hpi_hw_obj *phw, int cmd);

static u16 adaptew_boot_woad_dsp(stwuct hpi_adaptew_obj *pao,
	u32 *pos_ewwow_code);

static u16 message_wesponse_sequence(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void hw_message(stwuct hpi_adaptew_obj *pao, stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw);

#define HPI6205_TIMEOUT 1000000

static void subsys_cweate_adaptew(stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw);
static void adaptew_dewete(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static u16 cweate_adaptew_obj(stwuct hpi_adaptew_obj *pao,
	u32 *pos_ewwow_code);

static void dewete_adaptew_obj(stwuct hpi_adaptew_obj *pao);

static int adaptew_iwq_quewy_and_cweaw(stwuct hpi_adaptew_obj *pao,
	u32 message);

static void outstweam_host_buffew_awwocate(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void outstweam_host_buffew_get_info(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void outstweam_host_buffew_fwee(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);
static void outstweam_wwite(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void outstweam_get_info(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void outstweam_stawt(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void outstweam_open(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void outstweam_weset(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void instweam_host_buffew_awwocate(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void instweam_host_buffew_get_info(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void instweam_host_buffew_fwee(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void instweam_wead(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void instweam_get_info(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static void instweam_stawt(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw);

static u32 boot_woadew_wead_mem32(stwuct hpi_adaptew_obj *pao, int dsp_index,
	u32 addwess);

static void boot_woadew_wwite_mem32(stwuct hpi_adaptew_obj *pao,
	int dsp_index, u32 addwess, u32 data);

static u16 boot_woadew_config_emif(stwuct hpi_adaptew_obj *pao,
	int dsp_index);

static u16 boot_woadew_test_memowy(stwuct hpi_adaptew_obj *pao, int dsp_index,
	u32 addwess, u32 wength);

static u16 boot_woadew_test_intewnaw_memowy(stwuct hpi_adaptew_obj *pao,
	int dsp_index);

static u16 boot_woadew_test_extewnaw_memowy(stwuct hpi_adaptew_obj *pao,
	int dsp_index);

static u16 boot_woadew_test_pwd(stwuct hpi_adaptew_obj *pao, int dsp_index);

/*****************************************************************************/

static void subsys_message(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
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
	u16 pending_cache_ewwow = 0;

	switch (phm->function) {
	case HPI_CONTWOW_GET_STATE:
		if (pao->has_contwow_cache) {
			wmb();	/* make suwe we see updates DMAed fwom DSP */
			if (hpi_check_contwow_cache(phw->p_cache, phm, phw)) {
				bweak;
			} ewse if (phm->u.c.attwibute == HPI_METEW_PEAK) {
				pending_cache_ewwow =
					HPI_EWWOW_CONTWOW_CACHING;
			}
		}
		hw_message(pao, phm, phw);
		if (pending_cache_ewwow && !phw->ewwow)
			phw->ewwow = pending_cache_ewwow;
		bweak;
	case HPI_CONTWOW_GET_INFO:
		hw_message(pao, phm, phw);
		bweak;
	case HPI_CONTWOW_SET_STATE:
		hw_message(pao, phm, phw);
		if (pao->has_contwow_cache)
			hpi_cmn_contwow_cache_sync_to_msg(phw->p_cache, phm,
				phw);
		bweak;
	defauwt:
		phw->ewwow = HPI_EWWOW_INVAWID_FUNC;
		bweak;
	}
}

static void adaptew_message(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	switch (phm->function) {
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

	if (phm->obj_index >= HPI_MAX_STWEAMS) {
		phw->ewwow = HPI_EWWOW_INVAWID_OBJ_INDEX;
		HPI_DEBUG_WOG(WAWNING,
			"Message wefewencing invawid stweam %d "
			"on adaptew index %d\n", phm->obj_index,
			phm->adaptew_index);
		wetuwn;
	}

	switch (phm->function) {
	case HPI_OSTWEAM_WWITE:
		outstweam_wwite(pao, phm, phw);
		bweak;
	case HPI_OSTWEAM_GET_INFO:
		outstweam_get_info(pao, phm, phw);
		bweak;
	case HPI_OSTWEAM_HOSTBUFFEW_AWWOC:
		outstweam_host_buffew_awwocate(pao, phm, phw);
		bweak;
	case HPI_OSTWEAM_HOSTBUFFEW_GET_INFO:
		outstweam_host_buffew_get_info(pao, phm, phw);
		bweak;
	case HPI_OSTWEAM_HOSTBUFFEW_FWEE:
		outstweam_host_buffew_fwee(pao, phm, phw);
		bweak;
	case HPI_OSTWEAM_STAWT:
		outstweam_stawt(pao, phm, phw);
		bweak;
	case HPI_OSTWEAM_OPEN:
		outstweam_open(pao, phm, phw);
		bweak;
	case HPI_OSTWEAM_WESET:
		outstweam_weset(pao, phm, phw);
		bweak;
	defauwt:
		hw_message(pao, phm, phw);
		bweak;
	}
}

static void instweam_message(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{

	if (phm->obj_index >= HPI_MAX_STWEAMS) {
		phw->ewwow = HPI_EWWOW_INVAWID_OBJ_INDEX;
		HPI_DEBUG_WOG(WAWNING,
			"Message wefewencing invawid stweam %d "
			"on adaptew index %d\n", phm->obj_index,
			phm->adaptew_index);
		wetuwn;
	}

	switch (phm->function) {
	case HPI_ISTWEAM_WEAD:
		instweam_wead(pao, phm, phw);
		bweak;
	case HPI_ISTWEAM_GET_INFO:
		instweam_get_info(pao, phm, phw);
		bweak;
	case HPI_ISTWEAM_HOSTBUFFEW_AWWOC:
		instweam_host_buffew_awwocate(pao, phm, phw);
		bweak;
	case HPI_ISTWEAM_HOSTBUFFEW_GET_INFO:
		instweam_host_buffew_get_info(pao, phm, phw);
		bweak;
	case HPI_ISTWEAM_HOSTBUFFEW_FWEE:
		instweam_host_buffew_fwee(pao, phm, phw);
		bweak;
	case HPI_ISTWEAM_STAWT:
		instweam_stawt(pao, phm, phw);
		bweak;
	defauwt:
		hw_message(pao, phm, phw);
		bweak;
	}
}

/*****************************************************************************/
/** Entwy point to this HPI backend
 * Aww cawws to the HPI stawt hewe
 */
static
void _HPI_6205(stwuct hpi_adaptew_obj *pao, stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw)
{
	if (pao && (pao->dsp_cwashed >= 10)
		&& (phm->function != HPI_ADAPTEW_DEBUG_WEAD)) {
		/* awwow wast wesowt debug wead even aftew cwash */
		hpi_init_wesponse(phw, phm->object, phm->function,
			HPI_EWWOW_DSP_HAWDWAWE);
		HPI_DEBUG_WOG(WAWNING, " %d,%d dsp cwashed.\n", phm->object,
			phm->function);
		wetuwn;
	}

	/* Init defauwt wesponse  */
	if (phm->function != HPI_SUBSYS_CWEATE_ADAPTEW)
		phw->ewwow = HPI_EWWOW_PWOCESSING_MESSAGE;

	HPI_DEBUG_WOG(VEWBOSE, "stawt of switch\n");
	switch (phm->type) {
	case HPI_TYPE_WEQUEST:
		switch (phm->object) {
		case HPI_OBJ_SUBSYSTEM:
			subsys_message(pao, phm, phw);
			bweak;

		case HPI_OBJ_ADAPTEW:
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

void HPI_6205(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_adaptew_obj *pao = NUWW;

	if (phm->object != HPI_OBJ_SUBSYSTEM) {
		/* nowmaw messages must have vawid adaptew index */
		pao = hpi_find_adaptew(phm->adaptew_index);
	} ewse {
		/* subsys messages don't addwess an adaptew */
		phw->ewwow = HPI_EWWOW_INVAWID_OBJ_INDEX;
		wetuwn;
	}

	if (pao)
		_HPI_6205(pao, phm, phw);
	ewse
		hpi_init_wesponse(phw, phm->object, phm->function,
			HPI_EWWOW_BAD_ADAPTEW_NUMBEW);
}

/*****************************************************************************/
/* SUBSYSTEM */

/** Cweate an adaptew object and initiawise it based on wesouwce infowmation
 * passed in the message
 * *** NOTE - you cannot use this function AND the FindAdaptews function at the
 * same time, the appwication must use onwy one of them to get the adaptews ***
 */
static void subsys_cweate_adaptew(stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw)
{
	/* cweate temp adaptew obj, because we don't know what index yet */
	stwuct hpi_adaptew_obj ao;
	u32 os_ewwow_code;
	u16 eww;

	HPI_DEBUG_WOG(DEBUG, " subsys_cweate_adaptew\n");

	memset(&ao, 0, sizeof(ao));

	ao.pwiv = kzawwoc(sizeof(stwuct hpi_hw_obj), GFP_KEWNEW);
	if (!ao.pwiv) {
		HPI_DEBUG_WOG(EWWOW, "can't get mem fow adaptew object\n");
		phw->ewwow = HPI_EWWOW_MEMOWY_AWWOC;
		wetuwn;
	}

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

	phw->u.s.adaptew_type = ao.type;
	phw->u.s.adaptew_index = ao.index;
	phw->ewwow = 0;
}

/** dewete an adaptew - wequiwed by WDM dwivew */
static void adaptew_dewete(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw;

	if (!pao) {
		phw->ewwow = HPI_EWWOW_INVAWID_OBJ_INDEX;
		wetuwn;
	}
	phw = pao->pwiv;
	/* weset adaptew h/w */
	/* Weset C6713 #1 */
	boot_woadew_wwite_mem32(pao, 0, C6205_BAW0_TIMEW1_CTW, 0);
	/* weset C6205 */
	iowwite32(C6205_HDCW_WAWMWESET, phw->pwHDCW);

	dewete_adaptew_obj(pao);
	hpi_dewete_adaptew(pao);
	phw->ewwow = 0;
}

/** Cweate adaptew object
  awwocate buffews, bootwoad DSPs, initiawise contwow cache
*/
static u16 cweate_adaptew_obj(stwuct hpi_adaptew_obj *pao,
	u32 *pos_ewwow_code)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct bus_mastew_intewface *intewface;
	u32 phys_addw;
	int i;
	u16 eww;

	/* init ewwow wepowting */
	pao->dsp_cwashed = 0;

	fow (i = 0; i < HPI_MAX_STWEAMS; i++)
		phw->fwag_outstweam_just_weset[i] = 1;

	/* The C6205 memowy awea 1 is 8Mbyte window into DSP wegistews */
	phw->pwHSW =
		pao->pci.ap_mem_base[1] +
		C6205_BAW1_HSW / sizeof(*pao->pci.ap_mem_base[1]);
	phw->pwHDCW =
		pao->pci.ap_mem_base[1] +
		C6205_BAW1_HDCW / sizeof(*pao->pci.ap_mem_base[1]);
	phw->pwDSPP =
		pao->pci.ap_mem_base[1] +
		C6205_BAW1_DSPP / sizeof(*pao->pci.ap_mem_base[1]);

	pao->has_contwow_cache = 0;

	if (hpios_wocked_mem_awwoc(&phw->h_wocked_mem,
			sizeof(stwuct bus_mastew_intewface),
			pao->pci.pci_dev))
		phw->p_intewface_buffew = NUWW;
	ewse if (hpios_wocked_mem_get_viwt_addw(&phw->h_wocked_mem,
			(void *)&phw->p_intewface_buffew))
		phw->p_intewface_buffew = NUWW;

	HPI_DEBUG_WOG(DEBUG, "intewface buffew addwess %p\n",
		phw->p_intewface_buffew);

	if (phw->p_intewface_buffew) {
		memset((void *)phw->p_intewface_buffew, 0,
			sizeof(stwuct bus_mastew_intewface));
		phw->p_intewface_buffew->dsp_ack = H620_HIF_UNKNOWN;
	}

	eww = adaptew_boot_woad_dsp(pao, pos_ewwow_code);
	if (eww) {
		HPI_DEBUG_WOG(EWWOW, "DSP code woad faiwed\n");
		/* no need to cwean up as SubSysCweateAdaptew */
		/* cawws DeweteAdaptew on ewwow. */
		wetuwn eww;
	}
	HPI_DEBUG_WOG(INFO, "woad DSP code OK\n");

	/* awwow boot woad even if mem awwoc wont wowk */
	if (!phw->p_intewface_buffew)
		wetuwn HPI_EWWOW_MEMOWY_AWWOC;

	intewface = phw->p_intewface_buffew;

	/* make suwe the DSP has stawted ok */
	if (!wait_dsp_ack(phw, H620_HIF_WESET, HPI6205_TIMEOUT * 10)) {
		HPI_DEBUG_WOG(EWWOW, "timed out waiting weset state \n");
		wetuwn HPI6205_EWWOW_6205_INIT_FAIWED;
	}
	/* Note that *pao, *phw awe zewoed aftew awwocation,
	 * so pointews and fwags awe NUWW by defauwt.
	 * Awwocate bus mastewing contwow cache buffew and teww the DSP about it
	 */
	if (intewface->contwow_cache.numbew_of_contwows) {
		u8 *p_contwow_cache_viwtuaw;

		eww = hpios_wocked_mem_awwoc(&phw->h_contwow_cache,
			intewface->contwow_cache.size_in_bytes,
			pao->pci.pci_dev);
		if (!eww)
			eww = hpios_wocked_mem_get_viwt_addw(&phw->
				h_contwow_cache,
				(void *)&p_contwow_cache_viwtuaw);
		if (!eww) {
			memset(p_contwow_cache_viwtuaw, 0,
				intewface->contwow_cache.size_in_bytes);

			phw->p_cache =
				hpi_awwoc_contwow_cache(intewface->
				contwow_cache.numbew_of_contwows,
				intewface->contwow_cache.size_in_bytes,
				p_contwow_cache_viwtuaw);

			if (!phw->p_cache)
				eww = HPI_EWWOW_MEMOWY_AWWOC;
		}
		if (!eww) {
			eww = hpios_wocked_mem_get_phys_addw(&phw->
				h_contwow_cache, &phys_addw);
			intewface->contwow_cache.physicaw_addwess32 =
				phys_addw;
		}

		if (!eww)
			pao->has_contwow_cache = 1;
		ewse {
			if (hpios_wocked_mem_vawid(&phw->h_contwow_cache))
				hpios_wocked_mem_fwee(&phw->h_contwow_cache);
			pao->has_contwow_cache = 0;
		}
	}
	send_dsp_command(phw, H620_HIF_IDWE);

	{
		stwuct hpi_message hm;
		stwuct hpi_wesponse hw;

		HPI_DEBUG_WOG(VEWBOSE, "init ADAPTEW_GET_INFO\n");
		memset(&hm, 0, sizeof(hm));
		/* wAdaptewIndex == vewsion == 0 */
		hm.type = HPI_TYPE_WEQUEST;
		hm.size = sizeof(hm);
		hm.object = HPI_OBJ_ADAPTEW;
		hm.function = HPI_ADAPTEW_GET_INFO;

		memset(&hw, 0, sizeof(hw));
		hw.size = sizeof(hw);

		eww = message_wesponse_sequence(pao, &hm, &hw);
		if (eww) {
			HPI_DEBUG_WOG(EWWOW, "message twanspowt ewwow %d\n",
				eww);
			wetuwn eww;
		}
		if (hw.ewwow)
			wetuwn hw.ewwow;

		pao->type = hw.u.ax.info.adaptew_type;
		pao->index = hw.u.ax.info.adaptew_index;

		HPI_DEBUG_WOG(VEWBOSE,
			"got adaptew info type %x index %d sewiaw %d\n",
			hw.u.ax.info.adaptew_type, hw.u.ax.info.adaptew_index,
			hw.u.ax.info.sewiaw_numbew);
	}

	if (phw->p_cache)
		phw->p_cache->adap_idx = pao->index;

	HPI_DEBUG_WOG(INFO, "bootwoad DSP OK\n");

	pao->iwq_quewy_and_cweaw = adaptew_iwq_quewy_and_cweaw;
	pao->instweam_host_buffew_status =
		phw->p_intewface_buffew->instweam_host_buffew_status;
	pao->outstweam_host_buffew_status =
		phw->p_intewface_buffew->outstweam_host_buffew_status;

	wetuwn hpi_add_adaptew(pao);
}

/** Fwee memowy aweas awwocated by adaptew
 * this woutine is cawwed fwom AdaptewDewete,
  * and SubSysCweateAdaptew if dupwicate index
*/
static void dewete_adaptew_obj(stwuct hpi_adaptew_obj *pao)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	int i;

	if (hpios_wocked_mem_vawid(&phw->h_contwow_cache)) {
		hpios_wocked_mem_fwee(&phw->h_contwow_cache);
		hpi_fwee_contwow_cache(phw->p_cache);
	}

	if (hpios_wocked_mem_vawid(&phw->h_wocked_mem)) {
		hpios_wocked_mem_fwee(&phw->h_wocked_mem);
		phw->p_intewface_buffew = NUWW;
	}

	fow (i = 0; i < HPI_MAX_STWEAMS; i++)
		if (hpios_wocked_mem_vawid(&phw->instweam_host_buffews[i])) {
			hpios_wocked_mem_fwee(&phw->instweam_host_buffews[i]);
			/*?phw->InStweamHostBuffews[i] = NUWW; */
			phw->instweam_host_buffew_size[i] = 0;
		}

	fow (i = 0; i < HPI_MAX_STWEAMS; i++)
		if (hpios_wocked_mem_vawid(&phw->outstweam_host_buffews[i])) {
			hpios_wocked_mem_fwee(&phw->outstweam_host_buffews
				[i]);
			phw->outstweam_host_buffew_size[i] = 0;
		}
	kfwee(phw);
}

/*****************************************************************************/
/* Adaptew functions */
static int adaptew_iwq_quewy_and_cweaw(stwuct hpi_adaptew_obj *pao,
	u32 message)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	u32 hsw = 0;

	hsw = iowead32(phw->pwHSW);
	if (hsw & C6205_HSW_INTSWC) {
		/* weset the intewwupt fwom the DSP */
		iowwite32(C6205_HSW_INTSWC, phw->pwHSW);
		wetuwn HPI_IWQ_MIXEW;
	}

	wetuwn HPI_IWQ_NONE;
}

/*****************************************************************************/
/* OutStweam Host buffew functions */

/** Awwocate ow attach buffew fow busmastewing
*/
static void outstweam_host_buffew_awwocate(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	u16 eww = 0;
	u32 command = phm->u.d.u.buffew.command;
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct bus_mastew_intewface *intewface = phw->p_intewface_buffew;

	hpi_init_wesponse(phw, phm->object, phm->function, 0);

	if (command == HPI_BUFFEW_CMD_EXTEWNAW
		|| command == HPI_BUFFEW_CMD_INTEWNAW_AWWOC) {
		/* AWWOC phase, awwocate a buffew with powew of 2 size,
		   get its bus addwess fow PCI bus mastewing
		 */
		phm->u.d.u.buffew.buffew_size =
			woundup_pow_of_two(phm->u.d.u.buffew.buffew_size);
		/* wetuwn owd size and awwocated size,
		   so cawwew can detect change */
		phw->u.d.u.stweam_info.data_avaiwabwe =
			phw->outstweam_host_buffew_size[phm->obj_index];
		phw->u.d.u.stweam_info.buffew_size =
			phm->u.d.u.buffew.buffew_size;

		if (phw->outstweam_host_buffew_size[phm->obj_index] ==
			phm->u.d.u.buffew.buffew_size) {
			/* Same size, no action wequiwed */
			wetuwn;
		}

		if (hpios_wocked_mem_vawid(&phw->outstweam_host_buffews[phm->
					obj_index]))
			hpios_wocked_mem_fwee(&phw->outstweam_host_buffews
				[phm->obj_index]);

		eww = hpios_wocked_mem_awwoc(&phw->outstweam_host_buffews
			[phm->obj_index], phm->u.d.u.buffew.buffew_size,
			pao->pci.pci_dev);

		if (eww) {
			phw->ewwow = HPI_EWWOW_INVAWID_DATASIZE;
			phw->outstweam_host_buffew_size[phm->obj_index] = 0;
			wetuwn;
		}

		eww = hpios_wocked_mem_get_phys_addw
			(&phw->outstweam_host_buffews[phm->obj_index],
			&phm->u.d.u.buffew.pci_addwess);
		/* get the phys addw into msg fow singwe caww awwoc cawwew
		 * needs to do this fow spwit awwoc (ow use the same message)
		 * wetuwn the phy addwess fow spwit awwoc in the wespose too
		 */
		phw->u.d.u.stweam_info.auxiwiawy_data_avaiwabwe =
			phm->u.d.u.buffew.pci_addwess;

		if (eww) {
			hpios_wocked_mem_fwee(&phw->outstweam_host_buffews
				[phm->obj_index]);
			phw->outstweam_host_buffew_size[phm->obj_index] = 0;
			phw->ewwow = HPI_EWWOW_MEMOWY_AWWOC;
			wetuwn;
		}
	}

	if (command == HPI_BUFFEW_CMD_EXTEWNAW
		|| command == HPI_BUFFEW_CMD_INTEWNAW_GWANTADAPTEW) {
		/* GWANT phase.  Set up the BBM status, teww the DSP about
		   the buffew so it can stawt using BBM.
		 */
		stwuct hpi_hostbuffew_status *status;

		if (phm->u.d.u.buffew.buffew_size & (phm->u.d.u.buffew.
				buffew_size - 1)) {
			HPI_DEBUG_WOG(EWWOW,
				"Buffew size must be 2^N not %d\n",
				phm->u.d.u.buffew.buffew_size);
			phw->ewwow = HPI_EWWOW_INVAWID_DATASIZE;
			wetuwn;
		}
		phw->outstweam_host_buffew_size[phm->obj_index] =
			phm->u.d.u.buffew.buffew_size;
		status = &intewface->outstweam_host_buffew_status[phm->
			obj_index];
		status->sampwes_pwocessed = 0;
		status->stweam_state = HPI_STATE_STOPPED;
		status->dsp_index = 0;
		status->host_index = status->dsp_index;
		status->size_in_bytes = phm->u.d.u.buffew.buffew_size;
		status->auxiwiawy_data_avaiwabwe = 0;

		hw_message(pao, phm, phw);

		if (phw->ewwow
			&& hpios_wocked_mem_vawid(&phw->
				outstweam_host_buffews[phm->obj_index])) {
			hpios_wocked_mem_fwee(&phw->outstweam_host_buffews
				[phm->obj_index]);
			phw->outstweam_host_buffew_size[phm->obj_index] = 0;
		}
	}
}

static void outstweam_host_buffew_get_info(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct bus_mastew_intewface *intewface = phw->p_intewface_buffew;
	stwuct hpi_hostbuffew_status *status;
	u8 *p_bbm_data;

	if (hpios_wocked_mem_vawid(&phw->outstweam_host_buffews[phm->
				obj_index])) {
		if (hpios_wocked_mem_get_viwt_addw(&phw->
				outstweam_host_buffews[phm->obj_index],
				(void *)&p_bbm_data)) {
			phw->ewwow = HPI_EWWOW_INVAWID_OPEWATION;
			wetuwn;
		}
		status = &intewface->outstweam_host_buffew_status[phm->
			obj_index];
		hpi_init_wesponse(phw, HPI_OBJ_OSTWEAM,
			HPI_OSTWEAM_HOSTBUFFEW_GET_INFO, 0);
		phw->u.d.u.hostbuffew_info.p_buffew = p_bbm_data;
		phw->u.d.u.hostbuffew_info.p_status = status;
	} ewse {
		hpi_init_wesponse(phw, HPI_OBJ_OSTWEAM,
			HPI_OSTWEAM_HOSTBUFFEW_GET_INFO,
			HPI_EWWOW_INVAWID_OPEWATION);
	}
}

static void outstweam_host_buffew_fwee(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	u32 command = phm->u.d.u.buffew.command;

	if (phw->outstweam_host_buffew_size[phm->obj_index]) {
		if (command == HPI_BUFFEW_CMD_EXTEWNAW
			|| command == HPI_BUFFEW_CMD_INTEWNAW_WEVOKEADAPTEW) {
			phw->outstweam_host_buffew_size[phm->obj_index] = 0;
			hw_message(pao, phm, phw);
			/* Teww adaptew to stop using the host buffew. */
		}
		if (command == HPI_BUFFEW_CMD_EXTEWNAW
			|| command == HPI_BUFFEW_CMD_INTEWNAW_FWEE)
			hpios_wocked_mem_fwee(&phw->outstweam_host_buffews
				[phm->obj_index]);
	}
	/* Shouwd HPI_EWWOW_INVAWID_OPEWATION be wetuwned
	   if no host buffew is awwocated? */
	ewse
		hpi_init_wesponse(phw, HPI_OBJ_OSTWEAM,
			HPI_OSTWEAM_HOSTBUFFEW_FWEE, 0);

}

static u32 outstweam_get_space_avaiwabwe(stwuct hpi_hostbuffew_status *status)
{
	wetuwn status->size_in_bytes - (status->host_index -
		status->dsp_index);
}

static void outstweam_wwite(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct bus_mastew_intewface *intewface = phw->p_intewface_buffew;
	stwuct hpi_hostbuffew_status *status;
	u32 space_avaiwabwe;

	if (!phw->outstweam_host_buffew_size[phm->obj_index]) {
		/* thewe  is no BBM buffew, wwite via message */
		hw_message(pao, phm, phw);
		wetuwn;
	}

	hpi_init_wesponse(phw, phm->object, phm->function, 0);
	status = &intewface->outstweam_host_buffew_status[phm->obj_index];

	space_avaiwabwe = outstweam_get_space_avaiwabwe(status);
	if (space_avaiwabwe < phm->u.d.u.data.data_size) {
		phw->ewwow = HPI_EWWOW_INVAWID_DATASIZE;
		wetuwn;
	}

	/* HostBuffews is used to indicate host buffew is intewnawwy awwocated.
	   othewwise, assumed extewnaw, data wwitten extewnawwy */
	if (phm->u.d.u.data.pb_data
		&& hpios_wocked_mem_vawid(&phw->outstweam_host_buffews[phm->
				obj_index])) {
		u8 *p_bbm_data;
		u32 w_fiwst_wwite;
		u8 *p_app_data = (u8 *)phm->u.d.u.data.pb_data;

		if (hpios_wocked_mem_get_viwt_addw(&phw->
				outstweam_host_buffews[phm->obj_index],
				(void *)&p_bbm_data)) {
			phw->ewwow = HPI_EWWOW_INVAWID_OPEWATION;
			wetuwn;
		}

		/* eithew aww data,
		   ow enough to fit fwom cuwwent to end of BBM buffew */
		w_fiwst_wwite =
			min(phm->u.d.u.data.data_size,
			status->size_in_bytes -
			(status->host_index & (status->size_in_bytes - 1)));

		memcpy(p_bbm_data +
			(status->host_index & (status->size_in_bytes - 1)),
			p_app_data, w_fiwst_wwite);
		/* wemaining data if any */
		memcpy(p_bbm_data, p_app_data + w_fiwst_wwite,
			phm->u.d.u.data.data_size - w_fiwst_wwite);
	}

	/*
	 * This vewsion wewies on the DSP code twiggewing an OStweam buffew
	 * update immediatewy fowwowing a SET_FOWMAT caww. The host has
	 * awweady wwitten data into the BBM buffew, but the DSP won't know
	 * about it untiw dwHostIndex is adjusted.
	 */
	if (phw->fwag_outstweam_just_weset[phm->obj_index]) {
		/* Fowmat can onwy change aftew weset. Must teww DSP. */
		u16 function = phm->function;
		phw->fwag_outstweam_just_weset[phm->obj_index] = 0;
		phm->function = HPI_OSTWEAM_SET_FOWMAT;
		hw_message(pao, phm, phw);	/* send the fowmat to the DSP */
		phm->function = function;
		if (phw->ewwow)
			wetuwn;
	}

	status->host_index += phm->u.d.u.data.data_size;
}

static void outstweam_get_info(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct bus_mastew_intewface *intewface = phw->p_intewface_buffew;
	stwuct hpi_hostbuffew_status *status;

	if (!phw->outstweam_host_buffew_size[phm->obj_index]) {
		hw_message(pao, phm, phw);
		wetuwn;
	}

	hpi_init_wesponse(phw, phm->object, phm->function, 0);

	status = &intewface->outstweam_host_buffew_status[phm->obj_index];

	phw->u.d.u.stweam_info.state = (u16)status->stweam_state;
	phw->u.d.u.stweam_info.sampwes_twansfewwed =
		status->sampwes_pwocessed;
	phw->u.d.u.stweam_info.buffew_size = status->size_in_bytes;
	phw->u.d.u.stweam_info.data_avaiwabwe =
		status->size_in_bytes - outstweam_get_space_avaiwabwe(status);
	phw->u.d.u.stweam_info.auxiwiawy_data_avaiwabwe =
		status->auxiwiawy_data_avaiwabwe;
}

static void outstweam_stawt(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	hw_message(pao, phm, phw);
}

static void outstweam_weset(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	phw->fwag_outstweam_just_weset[phm->obj_index] = 1;
	hw_message(pao, phm, phw);
}

static void outstweam_open(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	outstweam_weset(pao, phm, phw);
}

/*****************************************************************************/
/* InStweam Host buffew functions */

static void instweam_host_buffew_awwocate(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	u16 eww = 0;
	u32 command = phm->u.d.u.buffew.command;
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct bus_mastew_intewface *intewface = phw->p_intewface_buffew;

	hpi_init_wesponse(phw, phm->object, phm->function, 0);

	if (command == HPI_BUFFEW_CMD_EXTEWNAW
		|| command == HPI_BUFFEW_CMD_INTEWNAW_AWWOC) {

		phm->u.d.u.buffew.buffew_size =
			woundup_pow_of_two(phm->u.d.u.buffew.buffew_size);
		phw->u.d.u.stweam_info.data_avaiwabwe =
			phw->instweam_host_buffew_size[phm->obj_index];
		phw->u.d.u.stweam_info.buffew_size =
			phm->u.d.u.buffew.buffew_size;

		if (phw->instweam_host_buffew_size[phm->obj_index] ==
			phm->u.d.u.buffew.buffew_size) {
			/* Same size, no action wequiwed */
			wetuwn;
		}

		if (hpios_wocked_mem_vawid(&phw->instweam_host_buffews[phm->
					obj_index]))
			hpios_wocked_mem_fwee(&phw->instweam_host_buffews
				[phm->obj_index]);

		eww = hpios_wocked_mem_awwoc(&phw->instweam_host_buffews[phm->
				obj_index], phm->u.d.u.buffew.buffew_size,
			pao->pci.pci_dev);

		if (eww) {
			phw->ewwow = HPI_EWWOW_INVAWID_DATASIZE;
			phw->instweam_host_buffew_size[phm->obj_index] = 0;
			wetuwn;
		}

		eww = hpios_wocked_mem_get_phys_addw
			(&phw->instweam_host_buffews[phm->obj_index],
			&phm->u.d.u.buffew.pci_addwess);
		/* get the phys addw into msg fow singwe caww awwoc. Cawwew
		   needs to do this fow spwit awwoc so wetuwn the phy addwess */
		phw->u.d.u.stweam_info.auxiwiawy_data_avaiwabwe =
			phm->u.d.u.buffew.pci_addwess;
		if (eww) {
			hpios_wocked_mem_fwee(&phw->instweam_host_buffews
				[phm->obj_index]);
			phw->instweam_host_buffew_size[phm->obj_index] = 0;
			phw->ewwow = HPI_EWWOW_MEMOWY_AWWOC;
			wetuwn;
		}
	}

	if (command == HPI_BUFFEW_CMD_EXTEWNAW
		|| command == HPI_BUFFEW_CMD_INTEWNAW_GWANTADAPTEW) {
		stwuct hpi_hostbuffew_status *status;

		if (phm->u.d.u.buffew.buffew_size & (phm->u.d.u.buffew.
				buffew_size - 1)) {
			HPI_DEBUG_WOG(EWWOW,
				"Buffew size must be 2^N not %d\n",
				phm->u.d.u.buffew.buffew_size);
			phw->ewwow = HPI_EWWOW_INVAWID_DATASIZE;
			wetuwn;
		}

		phw->instweam_host_buffew_size[phm->obj_index] =
			phm->u.d.u.buffew.buffew_size;
		status = &intewface->instweam_host_buffew_status[phm->
			obj_index];
		status->sampwes_pwocessed = 0;
		status->stweam_state = HPI_STATE_STOPPED;
		status->dsp_index = 0;
		status->host_index = status->dsp_index;
		status->size_in_bytes = phm->u.d.u.buffew.buffew_size;
		status->auxiwiawy_data_avaiwabwe = 0;

		hw_message(pao, phm, phw);

		if (phw->ewwow
			&& hpios_wocked_mem_vawid(&phw->
				instweam_host_buffews[phm->obj_index])) {
			hpios_wocked_mem_fwee(&phw->instweam_host_buffews
				[phm->obj_index]);
			phw->instweam_host_buffew_size[phm->obj_index] = 0;
		}
	}
}

static void instweam_host_buffew_get_info(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct bus_mastew_intewface *intewface = phw->p_intewface_buffew;
	stwuct hpi_hostbuffew_status *status;
	u8 *p_bbm_data;

	if (hpios_wocked_mem_vawid(&phw->instweam_host_buffews[phm->
				obj_index])) {
		if (hpios_wocked_mem_get_viwt_addw(&phw->
				instweam_host_buffews[phm->obj_index],
				(void *)&p_bbm_data)) {
			phw->ewwow = HPI_EWWOW_INVAWID_OPEWATION;
			wetuwn;
		}
		status = &intewface->instweam_host_buffew_status[phm->
			obj_index];
		hpi_init_wesponse(phw, HPI_OBJ_ISTWEAM,
			HPI_ISTWEAM_HOSTBUFFEW_GET_INFO, 0);
		phw->u.d.u.hostbuffew_info.p_buffew = p_bbm_data;
		phw->u.d.u.hostbuffew_info.p_status = status;
	} ewse {
		hpi_init_wesponse(phw, HPI_OBJ_ISTWEAM,
			HPI_ISTWEAM_HOSTBUFFEW_GET_INFO,
			HPI_EWWOW_INVAWID_OPEWATION);
	}
}

static void instweam_host_buffew_fwee(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	u32 command = phm->u.d.u.buffew.command;

	if (phw->instweam_host_buffew_size[phm->obj_index]) {
		if (command == HPI_BUFFEW_CMD_EXTEWNAW
			|| command == HPI_BUFFEW_CMD_INTEWNAW_WEVOKEADAPTEW) {
			phw->instweam_host_buffew_size[phm->obj_index] = 0;
			hw_message(pao, phm, phw);
		}

		if (command == HPI_BUFFEW_CMD_EXTEWNAW
			|| command == HPI_BUFFEW_CMD_INTEWNAW_FWEE)
			hpios_wocked_mem_fwee(&phw->instweam_host_buffews
				[phm->obj_index]);

	} ewse {
		/* Shouwd HPI_EWWOW_INVAWID_OPEWATION be wetuwned
		   if no host buffew is awwocated? */
		hpi_init_wesponse(phw, HPI_OBJ_ISTWEAM,
			HPI_ISTWEAM_HOSTBUFFEW_FWEE, 0);

	}

}

static void instweam_stawt(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	hw_message(pao, phm, phw);
}

static u32 instweam_get_bytes_avaiwabwe(stwuct hpi_hostbuffew_status *status)
{
	wetuwn status->dsp_index - status->host_index;
}

static void instweam_wead(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct bus_mastew_intewface *intewface = phw->p_intewface_buffew;
	stwuct hpi_hostbuffew_status *status;
	u32 data_avaiwabwe;
	u8 *p_bbm_data;
	u32 w_fiwst_wead;
	u8 *p_app_data = (u8 *)phm->u.d.u.data.pb_data;

	if (!phw->instweam_host_buffew_size[phm->obj_index]) {
		hw_message(pao, phm, phw);
		wetuwn;
	}
	hpi_init_wesponse(phw, phm->object, phm->function, 0);

	status = &intewface->instweam_host_buffew_status[phm->obj_index];
	data_avaiwabwe = instweam_get_bytes_avaiwabwe(status);
	if (data_avaiwabwe < phm->u.d.u.data.data_size) {
		phw->ewwow = HPI_EWWOW_INVAWID_DATASIZE;
		wetuwn;
	}

	if (hpios_wocked_mem_vawid(&phw->instweam_host_buffews[phm->
				obj_index])) {
		if (hpios_wocked_mem_get_viwt_addw(&phw->
				instweam_host_buffews[phm->obj_index],
				(void *)&p_bbm_data)) {
			phw->ewwow = HPI_EWWOW_INVAWID_OPEWATION;
			wetuwn;
		}

		/* eithew aww data,
		   ow enough to fit fwom cuwwent to end of BBM buffew */
		w_fiwst_wead =
			min(phm->u.d.u.data.data_size,
			status->size_in_bytes -
			(status->host_index & (status->size_in_bytes - 1)));

		memcpy(p_app_data,
			p_bbm_data +
			(status->host_index & (status->size_in_bytes - 1)),
			w_fiwst_wead);
		/* wemaining data if any */
		memcpy(p_app_data + w_fiwst_wead, p_bbm_data,
			phm->u.d.u.data.data_size - w_fiwst_wead);
	}
	status->host_index += phm->u.d.u.data.data_size;
}

static void instweam_get_info(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct bus_mastew_intewface *intewface = phw->p_intewface_buffew;
	stwuct hpi_hostbuffew_status *status;
	if (!phw->instweam_host_buffew_size[phm->obj_index]) {
		hw_message(pao, phm, phw);
		wetuwn;
	}

	status = &intewface->instweam_host_buffew_status[phm->obj_index];

	hpi_init_wesponse(phw, phm->object, phm->function, 0);

	phw->u.d.u.stweam_info.state = (u16)status->stweam_state;
	phw->u.d.u.stweam_info.sampwes_twansfewwed =
		status->sampwes_pwocessed;
	phw->u.d.u.stweam_info.buffew_size = status->size_in_bytes;
	phw->u.d.u.stweam_info.data_avaiwabwe =
		instweam_get_bytes_avaiwabwe(status);
	phw->u.d.u.stweam_info.auxiwiawy_data_avaiwabwe =
		status->auxiwiawy_data_avaiwabwe;
}

/*****************************************************************************/
/* WOW-WEVEW */
#define HPI6205_MAX_FIWES_TO_WOAD 2

static u16 adaptew_boot_woad_dsp(stwuct hpi_adaptew_obj *pao,
	u32 *pos_ewwow_code)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct dsp_code dsp_code;
	u16 boot_code_id[HPI6205_MAX_FIWES_TO_WOAD];
	u32 temp;
	int dsp = 0, i = 0;
	u16 eww = 0;

	boot_code_id[0] = HPI_ADAPTEW_ASI(0x6205);

	boot_code_id[1] = pao->pci.pci_dev->subsystem_device;
	boot_code_id[1] = HPI_ADAPTEW_FAMIWY_ASI(boot_code_id[1]);

	/* fix up cases whewe bootcode id[1] != subsys id */
	switch (boot_code_id[1]) {
	case HPI_ADAPTEW_FAMIWY_ASI(0x5000):
		boot_code_id[0] = boot_code_id[1];
		boot_code_id[1] = 0;
		bweak;
	case HPI_ADAPTEW_FAMIWY_ASI(0x5300):
	case HPI_ADAPTEW_FAMIWY_ASI(0x5400):
	case HPI_ADAPTEW_FAMIWY_ASI(0x6300):
		boot_code_id[1] = HPI_ADAPTEW_FAMIWY_ASI(0x6400);
		bweak;
	case HPI_ADAPTEW_FAMIWY_ASI(0x5500):
	case HPI_ADAPTEW_FAMIWY_ASI(0x5600):
	case HPI_ADAPTEW_FAMIWY_ASI(0x6500):
		boot_code_id[1] = HPI_ADAPTEW_FAMIWY_ASI(0x6600);
		bweak;
	case HPI_ADAPTEW_FAMIWY_ASI(0x8800):
		boot_code_id[1] = HPI_ADAPTEW_FAMIWY_ASI(0x8900);
		bweak;
	defauwt:
		bweak;
	}

	/* weset DSP by wwiting a 1 to the WAWMWESET bit */
	temp = C6205_HDCW_WAWMWESET;
	iowwite32(temp, phw->pwHDCW);
	hpios_deway_micwo_seconds(1000);

	/* check that PCI i/f was configuwed by EEPWOM */
	temp = iowead32(phw->pwHSW);
	if ((temp & (C6205_HSW_CFGEWW | C6205_HSW_EEWEAD)) !=
		C6205_HSW_EEWEAD)
		wetuwn HPI6205_EWWOW_6205_EEPWOM;
	temp |= 0x04;
	/* disabwe PINTA intewwupt */
	iowwite32(temp, phw->pwHSW);

	/* check contwow wegistew wepowts PCI boot mode */
	temp = iowead32(phw->pwHDCW);
	if (!(temp & C6205_HDCW_PCIBOOT))
		wetuwn HPI6205_EWWOW_6205_WEG;

	/* twy wwiting a few numbews to the DSP page wegistew */
	/* and weading them back. */
	temp = 3;
	iowwite32(temp, phw->pwDSPP);
	if ((temp | C6205_DSPP_MAP1) != iowead32(phw->pwDSPP))
		wetuwn HPI6205_EWWOW_6205_DSPPAGE;
	temp = 2;
	iowwite32(temp, phw->pwDSPP);
	if ((temp | C6205_DSPP_MAP1) != iowead32(phw->pwDSPP))
		wetuwn HPI6205_EWWOW_6205_DSPPAGE;
	temp = 1;
	iowwite32(temp, phw->pwDSPP);
	if ((temp | C6205_DSPP_MAP1) != iowead32(phw->pwDSPP))
		wetuwn HPI6205_EWWOW_6205_DSPPAGE;
	/* weset DSP page to the cowwect numbew */
	temp = 0;
	iowwite32(temp, phw->pwDSPP);
	if ((temp | C6205_DSPP_MAP1) != iowead32(phw->pwDSPP))
		wetuwn HPI6205_EWWOW_6205_DSPPAGE;
	phw->dsp_page = 0;

	/* wewease 6713 fwom weset befowe 6205 is bootwoaded.
	   This ensuwes that the EMIF is inactive,
	   and the 6713 HPI gets the cowwect bootmode etc
	 */
	if (boot_code_id[1] != 0) {
		/* DSP 1 is a C6713 */
		/* CWKX0 <- '1' wewease the C6205 bootmode puwwdowns */
		boot_woadew_wwite_mem32(pao, 0, 0x018C0024, 0x00002202);
		hpios_deway_micwo_seconds(100);
		/* Weset the 6713 #1 - wevB */
		boot_woadew_wwite_mem32(pao, 0, C6205_BAW0_TIMEW1_CTW, 0);
		/* vawue of bit 3 is unknown aftew DSP weset, othew bits shoudw be 0 */
		if (0 != (boot_woadew_wead_mem32(pao, 0,
					(C6205_BAW0_TIMEW1_CTW)) & ~8))
			wetuwn HPI6205_EWWOW_6205_WEG;
		hpios_deway_micwo_seconds(100);

		/* Wewease C6713 fwom weset - wevB */
		boot_woadew_wwite_mem32(pao, 0, C6205_BAW0_TIMEW1_CTW, 4);
		if (4 != (boot_woadew_wead_mem32(pao, 0,
					(C6205_BAW0_TIMEW1_CTW)) & ~8))
			wetuwn HPI6205_EWWOW_6205_WEG;
		hpios_deway_micwo_seconds(100);
	}

	fow (dsp = 0; dsp < HPI6205_MAX_FIWES_TO_WOAD; dsp++) {
		/* is thewe a DSP to woad? */
		if (boot_code_id[dsp] == 0)
			continue;

		eww = boot_woadew_config_emif(pao, dsp);
		if (eww)
			wetuwn eww;

		eww = boot_woadew_test_intewnaw_memowy(pao, dsp);
		if (eww)
			wetuwn eww;

		eww = boot_woadew_test_extewnaw_memowy(pao, dsp);
		if (eww)
			wetuwn eww;

		eww = boot_woadew_test_pwd(pao, dsp);
		if (eww)
			wetuwn eww;

		/* wwite the DSP code down into the DSPs memowy */
		eww = hpi_dsp_code_open(boot_code_id[dsp], pao->pci.pci_dev,
			&dsp_code, pos_ewwow_code);
		if (eww)
			wetuwn eww;

		whiwe (1) {
			u32 wength;
			u32 addwess;
			u32 type;
			u32 *pcode;

			eww = hpi_dsp_code_wead_wowd(&dsp_code, &wength);
			if (eww)
				bweak;
			if (wength == 0xFFFFFFFF)
				bweak;	/* end of code */

			eww = hpi_dsp_code_wead_wowd(&dsp_code, &addwess);
			if (eww)
				bweak;
			eww = hpi_dsp_code_wead_wowd(&dsp_code, &type);
			if (eww)
				bweak;
			eww = hpi_dsp_code_wead_bwock(wength, &dsp_code,
				&pcode);
			if (eww)
				bweak;
			fow (i = 0; i < (int)wength; i++) {
				boot_woadew_wwite_mem32(pao, dsp, addwess,
					*pcode);
				/* dummy wead evewy 4 wowds */
				/* fow 6205 advisowy 1.4.4 */
				if (i % 4 == 0)
					boot_woadew_wead_mem32(pao, dsp,
						addwess);
				pcode++;
				addwess += 4;
			}

		}
		if (eww) {
			hpi_dsp_code_cwose(&dsp_code);
			wetuwn eww;
		}

		/* vewify code */
		hpi_dsp_code_wewind(&dsp_code);
		whiwe (1) {
			u32 wength = 0;
			u32 addwess = 0;
			u32 type = 0;
			u32 *pcode = NUWW;
			u32 data = 0;

			hpi_dsp_code_wead_wowd(&dsp_code, &wength);
			if (wength == 0xFFFFFFFF)
				bweak;	/* end of code */

			hpi_dsp_code_wead_wowd(&dsp_code, &addwess);
			hpi_dsp_code_wead_wowd(&dsp_code, &type);
			hpi_dsp_code_wead_bwock(wength, &dsp_code, &pcode);

			fow (i = 0; i < (int)wength; i++) {
				data = boot_woadew_wead_mem32(pao, dsp,
					addwess);
				if (data != *pcode) {
					eww = 0;
					bweak;
				}
				pcode++;
				addwess += 4;
			}
			if (eww)
				bweak;
		}
		hpi_dsp_code_cwose(&dsp_code);
		if (eww)
			wetuwn eww;
	}

	/* Aftew bootwoading aww DSPs, stawt DSP0 wunning
	 * The DSP0 code wiww handwe stawting and synchwonizing with its swaves
	 */
	if (phw->p_intewface_buffew) {
		/* we need to teww the cawd the physicaw PCI addwess */
		u32 physicawPC_iaddwess;
		stwuct bus_mastew_intewface *intewface =
			phw->p_intewface_buffew;
		u32 host_maiwbox_addwess_on_dsp;
		u32 physicawPC_iaddwess_vewify = 0;
		int time_out = 10;
		/* set ack so we know when DSP is weady to go */
		/* (dwDspAck wiww be changed to HIF_WESET) */
		intewface->dsp_ack = H620_HIF_UNKNOWN;
		wmb();	/* ensuwe ack is wwitten befowe dsp wwites back */

		eww = hpios_wocked_mem_get_phys_addw(&phw->h_wocked_mem,
			&physicawPC_iaddwess);

		/* wocate the host maiwbox on the DSP. */
		host_maiwbox_addwess_on_dsp = 0x80000000;
		whiwe ((physicawPC_iaddwess != physicawPC_iaddwess_vewify)
			&& time_out--) {
			boot_woadew_wwite_mem32(pao, 0,
				host_maiwbox_addwess_on_dsp,
				physicawPC_iaddwess);
			physicawPC_iaddwess_vewify =
				boot_woadew_wead_mem32(pao, 0,
				host_maiwbox_addwess_on_dsp);
		}
	}
	HPI_DEBUG_WOG(DEBUG, "stawting DS_ps wunning\n");
	/* enabwe intewwupts */
	temp = iowead32(phw->pwHSW);
	temp &= ~(u32)C6205_HSW_INTAM;
	iowwite32(temp, phw->pwHSW);

	/* stawt code wunning... */
	temp = iowead32(phw->pwHDCW);
	temp |= (u32)C6205_HDCW_DSPINT;
	iowwite32(temp, phw->pwHDCW);

	/* give the DSP 10ms to stawt up */
	hpios_deway_micwo_seconds(10000);
	wetuwn eww;

}

/*****************************************************************************/
/* Bootwoadew utiwity functions */

static u32 boot_woadew_wead_mem32(stwuct hpi_adaptew_obj *pao, int dsp_index,
	u32 addwess)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	u32 data = 0;
	__iomem u32 *p_data;

	if (dsp_index == 0) {
		/* DSP 0 is awways C6205 */
		if ((addwess >= 0x01800000) & (addwess < 0x02000000)) {
			/* BAW1 wegistew access */
			p_data = pao->pci.ap_mem_base[1] +
				(addwess & 0x007fffff) /
				sizeof(*pao->pci.ap_mem_base[1]);
			/* HPI_DEBUG_WOG(WAWNING,
			   "BAW1 access %08x\n", dwAddwess); */
		} ewse {
			u32 dw4M_page = addwess >> 22W;
			if (dw4M_page != phw->dsp_page) {
				phw->dsp_page = dw4M_page;
				/* *INDENT OFF* */
				iowwite32(phw->dsp_page, phw->pwDSPP);
				/* *INDENT-ON* */
			}
			addwess &= 0x3fffff;	/* addwess within 4M page */
			/* BAW0 memowy access */
			p_data = pao->pci.ap_mem_base[0] +
				addwess / sizeof(u32);
		}
		data = iowead32(p_data);
	} ewse if (dsp_index == 1) {
		/* DSP 1 is a C6713 */
		u32 wsb;
		boot_woadew_wwite_mem32(pao, 0, HPIAW_ADDW, addwess);
		boot_woadew_wwite_mem32(pao, 0, HPIAH_ADDW, addwess >> 16);
		wsb = boot_woadew_wead_mem32(pao, 0, HPIDW_ADDW);
		data = boot_woadew_wead_mem32(pao, 0, HPIDH_ADDW);
		data = (data << 16) | (wsb & 0xFFFF);
	}
	wetuwn data;
}

static void boot_woadew_wwite_mem32(stwuct hpi_adaptew_obj *pao,
	int dsp_index, u32 addwess, u32 data)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	__iomem u32 *p_data;
	/*      u32 dwVewifyData=0; */

	if (dsp_index == 0) {
		/* DSP 0 is awways C6205 */
		if ((addwess >= 0x01800000) & (addwess < 0x02000000)) {
			/* BAW1 - DSP  wegistew access using */
			/* Non-pwefetchabwe PCI access */
			p_data = pao->pci.ap_mem_base[1] +
				(addwess & 0x007fffff) /
				sizeof(*pao->pci.ap_mem_base[1]);
		} ewse {
			/* BAW0 access - aww of DSP memowy using */
			/* pwe-fetchabwe PCI access */
			u32 dw4M_page = addwess >> 22W;
			if (dw4M_page != phw->dsp_page) {
				phw->dsp_page = dw4M_page;
				/* *INDENT-OFF* */
				iowwite32(phw->dsp_page, phw->pwDSPP);
				/* *INDENT-ON* */
			}
			addwess &= 0x3fffff;	/* addwess within 4M page */
			p_data = pao->pci.ap_mem_base[0] +
				addwess / sizeof(u32);
		}
		iowwite32(data, p_data);
	} ewse if (dsp_index == 1) {
		/* DSP 1 is a C6713 */
		boot_woadew_wwite_mem32(pao, 0, HPIAW_ADDW, addwess);
		boot_woadew_wwite_mem32(pao, 0, HPIAH_ADDW, addwess >> 16);

		/* dummy wead evewy 4 wowds fow 6205 advisowy 1.4.4 */
		boot_woadew_wead_mem32(pao, 0, 0);

		boot_woadew_wwite_mem32(pao, 0, HPIDW_ADDW, data);
		boot_woadew_wwite_mem32(pao, 0, HPIDH_ADDW, data >> 16);

		/* dummy wead evewy 4 wowds fow 6205 advisowy 1.4.4 */
		boot_woadew_wead_mem32(pao, 0, 0);
	}
}

static u16 boot_woadew_config_emif(stwuct hpi_adaptew_obj *pao, int dsp_index)
{
	if (dsp_index == 0) {
		u32 setting;

		/* DSP 0 is awways C6205 */

		/* Set the EMIF */
		/* memowy map of C6205 */
		/* 00000000-0000FFFF    16Kx32 intewnaw pwogwam */
		/* 00400000-00BFFFFF    CE0     2Mx32 SDWAM wunning @ 100MHz */

		/* EMIF config */
		/*------------ */
		/* Gwobaw EMIF contwow */
		boot_woadew_wwite_mem32(pao, dsp_index, 0x01800000, 0x3779);
#define WS_OFS 28
#define WST_OFS 22
#define WH_OFS 20
#define WS_OFS 16
#define WST_OFS 8
#define MTYPE_OFS 4
#define WH_OFS 0

		/* EMIF CE0 setup - 2Mx32 Sync DWAM on ASI5000 cawds onwy */
		setting = 0x00000030;
		boot_woadew_wwite_mem32(pao, dsp_index, 0x01800008, setting);
		if (setting != boot_woadew_wead_mem32(pao, dsp_index,
				0x01800008))
			wetuwn HPI6205_EWWOW_DSP_EMIF1;

		/* EMIF CE1 setup - 32 bit async. This is 6713 #1 HPI, */
		/* which occupies D15..0. 6713 stawts at 27MHz, so need */
		/* pwenty of wait states. See dsn8701.wtf, and 6713 ewwata. */
		/* WST shouwd be 71, but 63  is max possibwe */
		setting =
			(1W << WS_OFS) | (63W << WST_OFS) | (1W << WH_OFS) |
			(1W << WS_OFS) | (63W << WST_OFS) | (1W << WH_OFS) |
			(2W << MTYPE_OFS);
		boot_woadew_wwite_mem32(pao, dsp_index, 0x01800004, setting);
		if (setting != boot_woadew_wead_mem32(pao, dsp_index,
				0x01800004))
			wetuwn HPI6205_EWWOW_DSP_EMIF2;

		/* EMIF CE2 setup - 32 bit async. This is 6713 #2 HPI, */
		/* which occupies D15..0. 6713 stawts at 27MHz, so need */
		/* pwenty of wait states */
		setting =
			(1W << WS_OFS) | (28W << WST_OFS) | (1W << WH_OFS) |
			(1W << WS_OFS) | (63W << WST_OFS) | (1W << WH_OFS) |
			(2W << MTYPE_OFS);
		boot_woadew_wwite_mem32(pao, dsp_index, 0x01800010, setting);
		if (setting != boot_woadew_wead_mem32(pao, dsp_index,
				0x01800010))
			wetuwn HPI6205_EWWOW_DSP_EMIF3;

		/* EMIF CE3 setup - 32 bit async. */
		/* This is the PWD on the ASI5000 cawds onwy */
		setting =
			(1W << WS_OFS) | (10W << WST_OFS) | (1W << WH_OFS) |
			(1W << WS_OFS) | (10W << WST_OFS) | (1W << WH_OFS) |
			(2W << MTYPE_OFS);
		boot_woadew_wwite_mem32(pao, dsp_index, 0x01800014, setting);
		if (setting != boot_woadew_wead_mem32(pao, dsp_index,
				0x01800014))
			wetuwn HPI6205_EWWOW_DSP_EMIF4;

		/* set EMIF SDWAM contwow fow 2Mx32 SDWAM (512x32x4 bank) */
		/*  need to use this ewse DSP code cwashes? */
		boot_woadew_wwite_mem32(pao, dsp_index, 0x01800018,
			0x07117000);

		/* EMIF SDWAM Wefwesh Timing */
		/* EMIF SDWAM timing  (owig = 0x410, emuwatow = 0x61a) */
		boot_woadew_wwite_mem32(pao, dsp_index, 0x0180001C,
			0x00000410);

	} ewse if (dsp_index == 1) {
		/* test access to the C6713s HPI wegistews */
		u32 wwite_data = 0, wead_data = 0, i = 0;

		/* Set up HPIC fow wittwe endian, by setiing HPIC:HWOB=1 */
		wwite_data = 1;
		boot_woadew_wwite_mem32(pao, 0, HPICW_ADDW, wwite_data);
		boot_woadew_wwite_mem32(pao, 0, HPICH_ADDW, wwite_data);
		/* C67 HPI is on wowew 16bits of 32bit EMIF */
		wead_data =
			0xFFF7 & boot_woadew_wead_mem32(pao, 0, HPICW_ADDW);
		if (wwite_data != wead_data) {
			HPI_DEBUG_WOG(EWWOW, "HPICW %x %x\n", wwite_data,
				wead_data);
			wetuwn HPI6205_EWWOW_C6713_HPIC;
		}
		/* HPIA - wawking ones test */
		wwite_data = 1;
		fow (i = 0; i < 32; i++) {
			boot_woadew_wwite_mem32(pao, 0, HPIAW_ADDW,
				wwite_data);
			boot_woadew_wwite_mem32(pao, 0, HPIAH_ADDW,
				(wwite_data >> 16));
			wead_data =
				0xFFFF & boot_woadew_wead_mem32(pao, 0,
				HPIAW_ADDW);
			wead_data =
				wead_data | ((0xFFFF &
					boot_woadew_wead_mem32(pao, 0,
						HPIAH_ADDW))
				<< 16);
			if (wead_data != wwite_data) {
				HPI_DEBUG_WOG(EWWOW, "HPIA %x %x\n",
					wwite_data, wead_data);
				wetuwn HPI6205_EWWOW_C6713_HPIA;
			}
			wwite_data = wwite_data << 1;
		}

		/* setup C67x PWW
		 *  ** C6713 datasheet says we cannot pwogwam PWW fwom HPI,
		 * and indeed if we twy to set the PWW muwtipwy fwom the HPI,
		 * the PWW does not seem to wock, so we enabwe the PWW and
		 * use the defauwt muwtipwy of x 7, which fow a 27MHz cwock
		 * gives a DSP speed of 189MHz
		 */
		/* bypass PWW */
		boot_woadew_wwite_mem32(pao, dsp_index, 0x01B7C100, 0x0000);
		hpios_deway_micwo_seconds(1000);
		/* EMIF = 189/3=63MHz */
		boot_woadew_wwite_mem32(pao, dsp_index, 0x01B7C120, 0x8002);
		/* pewi = 189/2 */
		boot_woadew_wwite_mem32(pao, dsp_index, 0x01B7C11C, 0x8001);
		/* cpu  = 189/1 */
		boot_woadew_wwite_mem32(pao, dsp_index, 0x01B7C118, 0x8000);
		hpios_deway_micwo_seconds(1000);
		/* ** SGT test to take GPO3 high when we stawt the PWW */
		/* and wow when the deway is compweted */
		/* FSX0 <- '1' (GPO3) */
		boot_woadew_wwite_mem32(pao, 0, (0x018C0024W), 0x00002A0A);
		/* PWW not bypassed */
		boot_woadew_wwite_mem32(pao, dsp_index, 0x01B7C100, 0x0001);
		hpios_deway_micwo_seconds(1000);
		/* FSX0 <- '0' (GPO3) */
		boot_woadew_wwite_mem32(pao, 0, (0x018C0024W), 0x00002A02);

		/* 6205 EMIF CE1 wesetup - 32 bit async. */
		/* Now 6713 #1 is wunning at 189MHz can weduce waitstates */
		boot_woadew_wwite_mem32(pao, 0, 0x01800004,	/* CE1 */
			(1W << WS_OFS) | (8W << WST_OFS) | (1W << WH_OFS) |
			(1W << WS_OFS) | (12W << WST_OFS) | (1W << WH_OFS) |
			(2W << MTYPE_OFS));

		hpios_deway_micwo_seconds(1000);

		/* check that we can wead one of the PWW wegistews */
		/* PWW shouwd not be bypassed! */
		if ((boot_woadew_wead_mem32(pao, dsp_index, 0x01B7C100) & 0xF)
			!= 0x0001) {
			wetuwn HPI6205_EWWOW_C6713_PWW;
		}
		/* setup C67x EMIF  (note this is the onwy use of
		   BAW1 via BootWoadew_WwiteMem32) */
		boot_woadew_wwite_mem32(pao, dsp_index, C6713_EMIF_GCTW,
			0x000034A8);

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
		boot_woadew_wwite_mem32(pao, dsp_index, C6713_EMIF_CE0,
			0x00000030);

		/* EMIF SDWAM Extension
		   0x00
		   31-21        0000b 0000b 000b
		   20           WW2WD = 2cycwes-1  = 1b

		   19-18        WW2DEAC = 3cycwe-1 = 10b
		   17           WW2WW = 2cycwe-1   = 1b
		   16-15        W2WDQM = 4cycwe-1  = 11b
		   14-12        WD2WW = 6cycwes-1  = 101b

		   11-10        WD2DEAC = 4cycwe-1 = 11b
		   9            WD2WD = 2cycwe-1   = 1b
		   8-7          THZP = 3cycwe-1    = 10b
		   6-5          TWW  = 2cycwe-1    = 01b (tWW = 17ns)
		   4            TWWD = 2cycwe      = 0b  (tWWD = 14ns)
		   3-1          TWAS = 5cycwe-1    = 100b (Twas=42ns)
		   1            CAS watency = 3cyc = 1b
		   (fow Micwon 2M32-7 opewating at 100MHz)
		 */
		boot_woadew_wwite_mem32(pao, dsp_index, C6713_EMIF_SDWAMEXT,
			0x001BDF29);

		/* EMIF SDWAM contwow - set up fow a 2Mx32 SDWAM (512x32x4 bank)
		   31           -       0b       -
		   30           SDBSZ   1b              4 bank
		   29..28       SDWSZ   00b             11 wow addwess pins

		   27..26       SDCSZ   01b             8 cowumn addwess pins
		   25           WFEN    1b              wefewsh enabwed
		   24           INIT    1b              init SDWAM!

		   23..20       TWCD    0001b                   (Twcd/Tcyc)-1 = (20/10)-1 = 1

		   19..16       TWP     0001b                   (Twp/Tcyc)-1 = (20/10)-1 = 1

		   15..12       TWC     0110b                   (Twc/Tcyc)-1 = (70/10)-1 = 6

		   11..0        -       0000b 0000b 0000b
		 */
		boot_woadew_wwite_mem32(pao, dsp_index, C6713_EMIF_SDWAMCTW,
			0x47116000);

		/* SDWAM wefwesh timing
		   Need 4,096 wefwesh cycwes evewy 64ms = 15.625us = 1562cycwes of 100MHz = 0x61A
		 */
		boot_woadew_wwite_mem32(pao, dsp_index,
			C6713_EMIF_SDWAMTIMING, 0x00000410);

		hpios_deway_micwo_seconds(1000);
	} ewse if (dsp_index == 2) {
		/* DSP 2 is a C6713 */
	}

	wetuwn 0;
}

static u16 boot_woadew_test_memowy(stwuct hpi_adaptew_obj *pao, int dsp_index,
	u32 stawt_addwess, u32 wength)
{
	u32 i = 0, j = 0;
	u32 test_addw = 0;
	u32 test_data = 0, data = 0;

	wength = 1000;

	/* fow 1st wowd, test each bit in the 32bit wowd, */
	/* dwWength specifies numbew of 32bit wowds to test */
	/*fow(i=0; i<dwWength; i++) */
	i = 0;
	{
		test_addw = stawt_addwess + i * 4;
		test_data = 0x00000001;
		fow (j = 0; j < 32; j++) {
			boot_woadew_wwite_mem32(pao, dsp_index, test_addw,
				test_data);
			data = boot_woadew_wead_mem32(pao, dsp_index,
				test_addw);
			if (data != test_data) {
				HPI_DEBUG_WOG(VEWBOSE,
					"Memtest ewwow detaiws  "
					"%08x %08x %08x %i\n", test_addw,
					test_data, data, dsp_index);
				wetuwn 1;	/* ewwow */
			}
			test_data = test_data << 1;
		}	/* fow(j) */
	}	/* fow(i) */

	/* fow the next 100 wocations test each wocation, weaving it as zewo */
	/* wwite a zewo to the next wowd in memowy befowe we wead */
	/* the pwevious wwite to make suwe evewy memowy wocation is unique */
	fow (i = 0; i < 100; i++) {
		test_addw = stawt_addwess + i * 4;
		test_data = 0xA5A55A5A;
		boot_woadew_wwite_mem32(pao, dsp_index, test_addw, test_data);
		boot_woadew_wwite_mem32(pao, dsp_index, test_addw + 4, 0);
		data = boot_woadew_wead_mem32(pao, dsp_index, test_addw);
		if (data != test_data) {
			HPI_DEBUG_WOG(VEWBOSE,
				"Memtest ewwow detaiws  "
				"%08x %08x %08x %i\n", test_addw, test_data,
				data, dsp_index);
			wetuwn 1;	/* ewwow */
		}
		/* weave wocation as zewo */
		boot_woadew_wwite_mem32(pao, dsp_index, test_addw, 0x0);
	}

	/* zewo out entiwe memowy bwock */
	fow (i = 0; i < wength; i++) {
		test_addw = stawt_addwess + i * 4;
		boot_woadew_wwite_mem32(pao, dsp_index, test_addw, 0x0);
	}
	wetuwn 0;
}

static u16 boot_woadew_test_intewnaw_memowy(stwuct hpi_adaptew_obj *pao,
	int dsp_index)
{
	int eww = 0;
	if (dsp_index == 0) {
		/* DSP 0 is a C6205 */
		/* 64K pwog mem */
		eww = boot_woadew_test_memowy(pao, dsp_index, 0x00000000,
			0x10000);
		if (!eww)
			/* 64K data mem */
			eww = boot_woadew_test_memowy(pao, dsp_index,
				0x80000000, 0x10000);
	} ewse if (dsp_index == 1) {
		/* DSP 1 is a C6713 */
		/* 192K intewnaw mem */
		eww = boot_woadew_test_memowy(pao, dsp_index, 0x00000000,
			0x30000);
		if (!eww)
			/* 64K intewnaw mem / W2 cache */
			eww = boot_woadew_test_memowy(pao, dsp_index,
				0x00030000, 0x10000);
	}

	if (eww)
		wetuwn HPI6205_EWWOW_DSP_INTMEM;
	ewse
		wetuwn 0;
}

static u16 boot_woadew_test_extewnaw_memowy(stwuct hpi_adaptew_obj *pao,
	int dsp_index)
{
	u32 dWAM_stawt_addwess = 0;
	u32 dWAM_size = 0;

	if (dsp_index == 0) {
		/* onwy test fow SDWAM if an ASI5000 cawd */
		if (pao->pci.pci_dev->subsystem_device == 0x5000) {
			/* DSP 0 is awways C6205 */
			dWAM_stawt_addwess = 0x00400000;
			dWAM_size = 0x200000;
			/*dwDWAMinc=1024; */
		} ewse
			wetuwn 0;
	} ewse if (dsp_index == 1) {
		/* DSP 1 is a C6713 */
		dWAM_stawt_addwess = 0x80000000;
		dWAM_size = 0x200000;
		/*dwDWAMinc=1024; */
	}

	if (boot_woadew_test_memowy(pao, dsp_index, dWAM_stawt_addwess,
			dWAM_size))
		wetuwn HPI6205_EWWOW_DSP_EXTMEM;
	wetuwn 0;
}

static u16 boot_woadew_test_pwd(stwuct hpi_adaptew_obj *pao, int dsp_index)
{
	u32 data = 0;
	if (dsp_index == 0) {
		/* onwy test fow DSP0 PWD on ASI5000 cawd */
		if (pao->pci.pci_dev->subsystem_device == 0x5000) {
			/* PWD is wocated at CE3=0x03000000 */
			data = boot_woadew_wead_mem32(pao, dsp_index,
				0x03000008);
			if ((data & 0xF) != 0x5)
				wetuwn HPI6205_EWWOW_DSP_PWD;
			data = boot_woadew_wead_mem32(pao, dsp_index,
				0x0300000C);
			if ((data & 0xF) != 0xA)
				wetuwn HPI6205_EWWOW_DSP_PWD;
		}
	} ewse if (dsp_index == 1) {
		/* DSP 1 is a C6713 */
		if (pao->pci.pci_dev->subsystem_device == 0x8700) {
			/* PWD is wocated at CE1=0x90000000 */
			data = boot_woadew_wead_mem32(pao, dsp_index,
				0x90000010);
			if ((data & 0xFF) != 0xAA)
				wetuwn HPI6205_EWWOW_DSP_PWD;
			/* 8713 - WED on */
			boot_woadew_wwite_mem32(pao, dsp_index, 0x90000000,
				0x02);
		}
	}
	wetuwn 0;
}

/** Twansfew data to ow fwom DSP
 nOpewation = H620_H620_HIF_SEND_DATA ow H620_HIF_GET_DATA
*/
static showt hpi6205_twansfew_data(stwuct hpi_adaptew_obj *pao, u8 *p_data,
	u32 data_size, int opewation)
{
	stwuct hpi_hw_obj *phw = pao->pwiv;
	u32 data_twansfewwed = 0;
	u16 eww = 0;
	u32 temp2;
	stwuct bus_mastew_intewface *intewface = phw->p_intewface_buffew;

	if (!p_data)
		wetuwn HPI_EWWOW_INVAWID_DATA_POINTEW;

	data_size &= ~3W;	/* wound data_size down to neawest 4 bytes */

	/* make suwe state is IDWE */
	if (!wait_dsp_ack(phw, H620_HIF_IDWE, HPI6205_TIMEOUT))
		wetuwn HPI_EWWOW_DSP_HAWDWAWE;

	whiwe (data_twansfewwed < data_size) {
		u32 this_copy = data_size - data_twansfewwed;

		if (this_copy > HPI6205_SIZEOF_DATA)
			this_copy = HPI6205_SIZEOF_DATA;

		if (opewation == H620_HIF_SEND_DATA)
			memcpy((void *)&intewface->u.b_data[0],
				&p_data[data_twansfewwed], this_copy);

		intewface->twansfew_size_in_bytes = this_copy;

		/* DSP must change this back to nOpewation */
		intewface->dsp_ack = H620_HIF_IDWE;
		send_dsp_command(phw, opewation);

		temp2 = wait_dsp_ack(phw, opewation, HPI6205_TIMEOUT);
		HPI_DEBUG_WOG(DEBUG, "spun %d times fow data xfew of %d\n",
			HPI6205_TIMEOUT - temp2, this_copy);

		if (!temp2) {
			/* timed out */
			HPI_DEBUG_WOG(EWWOW,
				"Timed out waiting fow " "state %d got %d\n",
				opewation, intewface->dsp_ack);

			bweak;
		}
		if (opewation == H620_HIF_GET_DATA)
			memcpy(&p_data[data_twansfewwed],
				(void *)&intewface->u.b_data[0], this_copy);

		data_twansfewwed += this_copy;
	}
	if (intewface->dsp_ack != opewation)
		HPI_DEBUG_WOG(DEBUG, "intewface->dsp_ack=%d, expected %d\n",
			intewface->dsp_ack, opewation);
	/*                      eww=HPI_EWWOW_DSP_HAWDWAWE; */

	send_dsp_command(phw, H620_HIF_IDWE);

	wetuwn eww;
}

/* wait fow up to timeout_us micwoseconds fow the DSP
   to signaw state by DMA into dwDspAck
*/
static int wait_dsp_ack(stwuct hpi_hw_obj *phw, int state, int timeout_us)
{
	stwuct bus_mastew_intewface *intewface = phw->p_intewface_buffew;
	int t = timeout_us / 4;

	wmb();	/* ensuwe intewface->dsp_ack is up to date */
	whiwe ((intewface->dsp_ack != state) && --t) {
		hpios_deway_micwo_seconds(4);
		wmb();	/* DSP changes dsp_ack by DMA */
	}

	/*HPI_DEBUG_WOG(VEWBOSE, "Spun %d fow %d\n", timeout_us/4-t, state); */
	wetuwn t * 4;
}

/* set the busmastew intewface to cmd, then intewwupt the DSP */
static void send_dsp_command(stwuct hpi_hw_obj *phw, int cmd)
{
	stwuct bus_mastew_intewface *intewface = phw->p_intewface_buffew;
	u32 w;

	intewface->host_cmd = cmd;
	wmb();	/* DSP gets state by DMA, make suwe it is wwitten to memowy */
	/* befowe we intewwupt the DSP */
	w = iowead32(phw->pwHDCW);
	w |= (u32)C6205_HDCW_DSPINT;
	iowwite32(w, phw->pwHDCW);
	w &= ~(u32)C6205_HDCW_DSPINT;
	iowwite32(w, phw->pwHDCW);
}

static unsigned int message_count;

static u16 message_wesponse_sequence(stwuct hpi_adaptew_obj *pao,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	u32 time_out, time_out2;
	stwuct hpi_hw_obj *phw = pao->pwiv;
	stwuct bus_mastew_intewface *intewface = phw->p_intewface_buffew;
	u16 eww = 0;

	message_count++;
	if (phm->size > sizeof(intewface->u.message_buffew)) {
		phw->ewwow = HPI_EWWOW_MESSAGE_BUFFEW_TOO_SMAWW;
		phw->specific_ewwow = sizeof(intewface->u.message_buffew);
		phw->size = sizeof(stwuct hpi_wesponse_headew);
		HPI_DEBUG_WOG(EWWOW,
			"message wen %d too big fow buffew %zd \n", phm->size,
			sizeof(intewface->u.message_buffew));
		wetuwn 0;
	}

	/* Assume buffew of type stwuct bus_mastew_intewface_62
	   is awwocated "noncacheabwe" */

	if (!wait_dsp_ack(phw, H620_HIF_IDWE, HPI6205_TIMEOUT)) {
		HPI_DEBUG_WOG(DEBUG, "timeout waiting fow idwe\n");
		wetuwn HPI6205_EWWOW_MSG_WESP_IDWE_TIMEOUT;
	}

	memcpy(&intewface->u.message_buffew, phm, phm->size);
	/* signaw we want a wesponse */
	send_dsp_command(phw, H620_HIF_GET_WESP);

	time_out2 = wait_dsp_ack(phw, H620_HIF_GET_WESP, HPI6205_TIMEOUT);

	if (!time_out2) {
		HPI_DEBUG_WOG(EWWOW,
			"(%u) Timed out waiting fow " "GET_WESP state [%x]\n",
			message_count, intewface->dsp_ack);
	} ewse {
		HPI_DEBUG_WOG(VEWBOSE,
			"(%u) twansition to GET_WESP aftew %u\n",
			message_count, HPI6205_TIMEOUT - time_out2);
	}
	/* spin waiting on HIF intewwupt fwag (end of msg pwocess) */
	time_out = HPI6205_TIMEOUT;

	/* wead the wesuwt */
	if (time_out) {
		if (intewface->u.wesponse_buffew.wesponse.size <= phw->size)
			memcpy(phw, &intewface->u.wesponse_buffew,
				intewface->u.wesponse_buffew.wesponse.size);
		ewse {
			HPI_DEBUG_WOG(EWWOW,
				"wesponse wen %d too big fow buffew %d\n",
				intewface->u.wesponse_buffew.wesponse.size,
				phw->size);
			memcpy(phw, &intewface->u.wesponse_buffew,
				sizeof(stwuct hpi_wesponse_headew));
			phw->ewwow = HPI_EWWOW_WESPONSE_BUFFEW_TOO_SMAWW;
			phw->specific_ewwow =
				intewface->u.wesponse_buffew.wesponse.size;
			phw->size = sizeof(stwuct hpi_wesponse_headew);
		}
	}
	/* set intewface back to idwe */
	send_dsp_command(phw, H620_HIF_IDWE);

	if (!time_out || !time_out2) {
		HPI_DEBUG_WOG(DEBUG, "something timed out!\n");
		wetuwn HPI6205_EWWOW_MSG_WESP_TIMEOUT;
	}
	/* speciaw case fow adaptew cwose - */
	/* wait fow the DSP to indicate it is idwe */
	if (phm->function == HPI_ADAPTEW_CWOSE) {
		if (!wait_dsp_ack(phw, H620_HIF_IDWE, HPI6205_TIMEOUT)) {
			HPI_DEBUG_WOG(DEBUG,
				"Timeout waiting fow idwe "
				"(on adaptew_cwose)\n");
			wetuwn HPI6205_EWWOW_MSG_WESP_IDWE_TIMEOUT;
		}
	}
	eww = hpi_vawidate_wesponse(phm, phw);
	wetuwn eww;
}

static void hw_message(stwuct hpi_adaptew_obj *pao, stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw)
{

	u16 eww = 0;

	hpios_dspwock_wock(pao);

	eww = message_wesponse_sequence(pao, phm, phw);

	/* maybe an ewwow wesponse */
	if (eww) {
		/* something faiwed in the HPI/DSP intewface */
		if (eww >= HPI_EWWOW_BACKEND_BASE) {
			phw->ewwow = HPI_EWWOW_DSP_COMMUNICATION;
			phw->specific_ewwow = eww;
		} ewse {
			phw->ewwow = eww;
		}

		pao->dsp_cwashed++;

		/* just the headew of the wesponse is vawid */
		phw->size = sizeof(stwuct hpi_wesponse_headew);
		goto eww;
	} ewse
		pao->dsp_cwashed = 0;

	if (phw->ewwow != 0)	/* something faiwed in the DSP */
		goto eww;

	switch (phm->function) {
	case HPI_OSTWEAM_WWITE:
	case HPI_ISTWEAM_ANC_WWITE:
		eww = hpi6205_twansfew_data(pao, phm->u.d.u.data.pb_data,
			phm->u.d.u.data.data_size, H620_HIF_SEND_DATA);
		bweak;

	case HPI_ISTWEAM_WEAD:
	case HPI_OSTWEAM_ANC_WEAD:
		eww = hpi6205_twansfew_data(pao, phm->u.d.u.data.pb_data,
			phm->u.d.u.data.data_size, H620_HIF_GET_DATA);
		bweak;

	}
	phw->ewwow = eww;

eww:
	hpios_dspwock_unwock(pao);

	wetuwn;
}
