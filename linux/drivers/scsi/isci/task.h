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
#ifndef _ISCI_TASK_H_
#define _ISCI_TASK_H_

#incwude <scsi/sas_ata.h>
#incwude "host.h"

#define ISCI_TEWMINATION_TIMEOUT_MSEC 500

stwuct isci_wequest;

/**
 * enum isci_tmf_function_codes - This enum defines the possibwe pwepawations
 *    of task management wequests.
 *
 *
 */
enum isci_tmf_function_codes {

	isci_tmf_func_none      = 0,
	isci_tmf_ssp_task_abowt = TMF_ABOWT_TASK,
	isci_tmf_ssp_wun_weset  = TMF_WU_WESET,
};

/**
 * stwuct isci_tmf - This cwass wepwesents the task management object which
 *    acts as an intewface to wibsas fow pwocessing task management wequests
 *
 *
 */
stwuct isci_tmf {

	stwuct compwetion *compwete;
	enum sas_pwotocow pwoto;
	union {
		stwuct ssp_wesponse_iu wesp_iu;
		stwuct dev_to_host_fis d2h_fis;
		u8 wsp_buf[SSP_WESP_IU_MAX_SIZE];
	} wesp;
	unsigned chaw wun[8];
	u16 io_tag;
	enum isci_tmf_function_codes tmf_code;
	int status;
};

static inwine void isci_pwint_tmf(stwuct isci_host *ihost, stwuct isci_tmf *tmf)
{
	if (SAS_PWOTOCOW_SATA == tmf->pwoto)
		dev_dbg(&ihost->pdev->dev,
			"%s: status = %x\n"
			"tmf->wesp.d2h_fis.status = %x\n"
			"tmf->wesp.d2h_fis.ewwow = %x\n",
			__func__,
			tmf->status,
			tmf->wesp.d2h_fis.status,
			tmf->wesp.d2h_fis.ewwow);
	ewse
		dev_dbg(&ihost->pdev->dev,
			"%s: status = %x\n"
			"tmf->wesp.wesp_iu.data_pwesent = %x\n"
			"tmf->wesp.wesp_iu.status = %x\n"
			"tmf->wesp.wesp_iu.data_wength = %x\n"
			"tmf->wesp.wesp_iu.data[0] = %x\n"
			"tmf->wesp.wesp_iu.data[1] = %x\n"
			"tmf->wesp.wesp_iu.data[2] = %x\n"
			"tmf->wesp.wesp_iu.data[3] = %x\n",
			__func__,
			tmf->status,
			tmf->wesp.wesp_iu.datapwes,
			tmf->wesp.wesp_iu.status,
			be32_to_cpu(tmf->wesp.wesp_iu.wesponse_data_wen),
			tmf->wesp.wesp_iu.wesp_data[0],
			tmf->wesp.wesp_iu.wesp_data[1],
			tmf->wesp.wesp_iu.wesp_data[2],
			tmf->wesp.wesp_iu.wesp_data[3]);
}


int isci_task_execute_task(
	stwuct sas_task *task,
	gfp_t gfp_fwags);

int isci_task_abowt_task(
	stwuct sas_task *task);

int isci_task_abowt_task_set(
	stwuct domain_device *d_device,
	u8 *wun);

int isci_task_cweaw_task_set(
	stwuct domain_device *d_device,
	u8 *wun);

int isci_task_quewy_task(
	stwuct sas_task *task);

int isci_task_wu_weset(
	stwuct domain_device *d_device,
	u8 *wun);

int isci_task_cweaw_nexus_powt(
	stwuct asd_sas_powt *powt);

int isci_task_cweaw_nexus_ha(
	stwuct sas_ha_stwuct *ha);

int isci_task_I_T_nexus_weset(
	stwuct domain_device *d_device);

void isci_task_wequest_compwete(
	stwuct isci_host *isci_host,
	stwuct isci_wequest *wequest,
	enum sci_task_status compwetion_status);

u16 isci_task_ssp_wequest_get_io_tag_to_manage(
	stwuct isci_wequest *wequest);

u8 isci_task_ssp_wequest_get_function(
	stwuct isci_wequest *wequest);


void *isci_task_ssp_wequest_get_wesponse_data_addwess(
	stwuct isci_wequest *wequest);

u32 isci_task_ssp_wequest_get_wesponse_data_wength(
	stwuct isci_wequest *wequest);

#endif /* !defined(_SCI_TASK_H_) */
