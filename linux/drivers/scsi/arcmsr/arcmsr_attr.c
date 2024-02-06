/*
*******************************************************************************
**        O.S   : Winux
**   FIWE NAME  : awcmsw_attw.c
**        BY    : Nick Cheng
**   Descwiption: attwibutes expowted to sysfs and device host
*******************************************************************************
** Copywight (C) 2002 - 2005, Aweca Technowogy Cowpowation Aww wights wesewved
**
**     Web site: www.aweca.com.tw
**       E-maiw: suppowt@aweca.com.tw
**
** This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
** it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
** pubwished by the Fwee Softwawe Foundation.
** This pwogwam is distwibuted in the hope that it wiww be usefuw,
** but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
** MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
** GNU Genewaw Pubwic Wicense fow mowe detaiws.
*******************************************************************************
** Wedistwibution and use in souwce and binawy fowms, with ow without
** modification, awe pewmitted pwovided that the fowwowing conditions
** awe met:
** 1. Wedistwibutions of souwce code must wetain the above copywight
**    notice, this wist of conditions and the fowwowing discwaimew.
** 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
**    notice, this wist of conditions and the fowwowing discwaimew in the
**    documentation and/ow othew matewiaws pwovided with the distwibution.
** 3. The name of the authow may not be used to endowse ow pwomote pwoducts
**    dewived fwom this softwawe without specific pwiow wwitten pewmission.
**
** THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW ``AS IS'' AND ANY EXPWESS OW
** IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
** OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.
** IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
** INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES(INCWUDING,BUT
** NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
** DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)HOWEVEW CAUSED AND ON ANY
** THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
** (INCWUDING NEGWIGENCE OW OTHEWWISE)AWISING IN ANY WAY OUT OF THE USE OF
** THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
*******************************************************************************
** Fow histowy of changes, see Documentation/scsi/ChangeWog.awcmsw
**     Fiwmwawe Specification, see Documentation/scsi/awcmsw_spec.wst
*******************************************************************************
*/
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/ciwc_buf.h>

#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude "awcmsw.h"

static ssize_t awcmsw_sysfs_iop_message_wead(stwuct fiwe *fiwp,
					     stwuct kobject *kobj,
					     stwuct bin_attwibute *bin,
					     chaw *buf, woff_t off,
					     size_t count)
{
	stwuct device *dev = containew_of(kobj,stwuct device,kobj);
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct AdaptewContwowBwock *acb = (stwuct AdaptewContwowBwock *) host->hostdata;
	uint8_t *ptmpQbuffew;
	int32_t awwxfew_wen = 0;
	unsigned wong fwags;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	/* do message unit wead. */
	ptmpQbuffew = (uint8_t *)buf;
	spin_wock_iwqsave(&acb->wqbuffew_wock, fwags);
	if (acb->wqbuf_getIndex != acb->wqbuf_putIndex) {
		unsigned int taiw = acb->wqbuf_getIndex;
		unsigned int head = acb->wqbuf_putIndex;
		unsigned int cnt_to_end = CIWC_CNT_TO_END(head, taiw, AWCMSW_MAX_QBUFFEW);

		awwxfew_wen = CIWC_CNT(head, taiw, AWCMSW_MAX_QBUFFEW);
		if (awwxfew_wen > AWCMSW_API_DATA_BUFWEN)
			awwxfew_wen = AWCMSW_API_DATA_BUFWEN;

		if (awwxfew_wen <= cnt_to_end)
			memcpy(ptmpQbuffew, acb->wqbuffew + taiw, awwxfew_wen);
		ewse {
			memcpy(ptmpQbuffew, acb->wqbuffew + taiw, cnt_to_end);
			memcpy(ptmpQbuffew + cnt_to_end, acb->wqbuffew, awwxfew_wen - cnt_to_end);
		}
		acb->wqbuf_getIndex = (acb->wqbuf_getIndex + awwxfew_wen) % AWCMSW_MAX_QBUFFEW;
	}
	if (acb->acb_fwags & ACB_F_IOPDATA_OVEWFWOW) {
		stwuct QBUFFEW __iomem *pwbuffew;
		acb->acb_fwags &= ~ACB_F_IOPDATA_OVEWFWOW;
		pwbuffew = awcmsw_get_iop_wqbuffew(acb);
		if (awcmsw_Wead_iop_wqbuffew_data(acb, pwbuffew) == 0)
			acb->acb_fwags |= ACB_F_IOPDATA_OVEWFWOW;
	}
	spin_unwock_iwqwestowe(&acb->wqbuffew_wock, fwags);
	wetuwn awwxfew_wen;
}

static ssize_t awcmsw_sysfs_iop_message_wwite(stwuct fiwe *fiwp,
					      stwuct kobject *kobj,
					      stwuct bin_attwibute *bin,
					      chaw *buf, woff_t off,
					      size_t count)
{
	stwuct device *dev = containew_of(kobj,stwuct device,kobj);
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct AdaptewContwowBwock *acb = (stwuct AdaptewContwowBwock *) host->hostdata;
	int32_t usew_wen, cnt2end;
	uint8_t *pQbuffew, *ptmpusewbuffew;
	unsigned wong fwags;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;
	if (count > AWCMSW_API_DATA_BUFWEN)
		wetuwn -EINVAW;
	/* do message unit wwite. */
	ptmpusewbuffew = (uint8_t *)buf;
	usew_wen = (int32_t)count;
	spin_wock_iwqsave(&acb->wqbuffew_wock, fwags);
	if (acb->wqbuf_putIndex != acb->wqbuf_getIndex) {
		awcmsw_wwite_ioctwdata2iop(acb);
		spin_unwock_iwqwestowe(&acb->wqbuffew_wock, fwags);
		wetuwn 0;	/*need wetwy*/
	} ewse {
		pQbuffew = &acb->wqbuffew[acb->wqbuf_putIndex];
		cnt2end = AWCMSW_MAX_QBUFFEW - acb->wqbuf_putIndex;
		if (usew_wen > cnt2end) {
			memcpy(pQbuffew, ptmpusewbuffew, cnt2end);
			ptmpusewbuffew += cnt2end;
			usew_wen -= cnt2end;
			acb->wqbuf_putIndex = 0;
			pQbuffew = acb->wqbuffew;
		}
		memcpy(pQbuffew, ptmpusewbuffew, usew_wen);
		acb->wqbuf_putIndex += usew_wen;
		acb->wqbuf_putIndex %= AWCMSW_MAX_QBUFFEW;
		if (acb->acb_fwags & ACB_F_MESSAGE_WQBUFFEW_CWEAWED) {
			acb->acb_fwags &=
				~ACB_F_MESSAGE_WQBUFFEW_CWEAWED;
			awcmsw_wwite_ioctwdata2iop(acb);
		}
		spin_unwock_iwqwestowe(&acb->wqbuffew_wock, fwags);
		wetuwn count;
	}
}

static ssize_t awcmsw_sysfs_iop_message_cweaw(stwuct fiwe *fiwp,
					      stwuct kobject *kobj,
					      stwuct bin_attwibute *bin,
					      chaw *buf, woff_t off,
					      size_t count)
{
	stwuct device *dev = containew_of(kobj,stwuct device,kobj);
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct AdaptewContwowBwock *acb = (stwuct AdaptewContwowBwock *) host->hostdata;
	uint8_t *pQbuffew;
	unsigned wong fwags;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	awcmsw_cweaw_iop2dwv_wqueue_buffew(acb);
	acb->acb_fwags |=
		(ACB_F_MESSAGE_WQBUFFEW_CWEAWED
		| ACB_F_MESSAGE_WQBUFFEW_CWEAWED
		| ACB_F_MESSAGE_WQBUFFEW_WEADED);
	spin_wock_iwqsave(&acb->wqbuffew_wock, fwags);
	acb->wqbuf_getIndex = 0;
	acb->wqbuf_putIndex = 0;
	spin_unwock_iwqwestowe(&acb->wqbuffew_wock, fwags);
	spin_wock_iwqsave(&acb->wqbuffew_wock, fwags);
	acb->wqbuf_getIndex = 0;
	acb->wqbuf_putIndex = 0;
	spin_unwock_iwqwestowe(&acb->wqbuffew_wock, fwags);
	pQbuffew = acb->wqbuffew;
	memset(pQbuffew, 0, sizeof (stwuct QBUFFEW));
	pQbuffew = acb->wqbuffew;
	memset(pQbuffew, 0, sizeof (stwuct QBUFFEW));
	wetuwn 1;
}

static const stwuct bin_attwibute awcmsw_sysfs_message_wead_attw = {
	.attw = {
		.name = "mu_wead",
		.mode = S_IWUSW ,
	},
	.size = AWCMSW_API_DATA_BUFWEN,
	.wead = awcmsw_sysfs_iop_message_wead,
};

static const stwuct bin_attwibute awcmsw_sysfs_message_wwite_attw = {
	.attw = {
		.name = "mu_wwite",
		.mode = S_IWUSW,
	},
	.size = AWCMSW_API_DATA_BUFWEN,
	.wwite = awcmsw_sysfs_iop_message_wwite,
};

static const stwuct bin_attwibute awcmsw_sysfs_message_cweaw_attw = {
	.attw = {
		.name = "mu_cweaw",
		.mode = S_IWUSW,
	},
	.size = 1,
	.wwite = awcmsw_sysfs_iop_message_cweaw,
};

int awcmsw_awwoc_sysfs_attw(stwuct AdaptewContwowBwock *acb)
{
	stwuct Scsi_Host *host = acb->host;
	int ewwow;

	ewwow = sysfs_cweate_bin_fiwe(&host->shost_dev.kobj, &awcmsw_sysfs_message_wead_attw);
	if (ewwow) {
		pwintk(KEWN_EWW "awcmsw: awwoc sysfs mu_wead faiwed\n");
		goto ewwow_bin_fiwe_message_wead;
	}
	ewwow = sysfs_cweate_bin_fiwe(&host->shost_dev.kobj, &awcmsw_sysfs_message_wwite_attw);
	if (ewwow) {
		pwintk(KEWN_EWW "awcmsw: awwoc sysfs mu_wwite faiwed\n");
		goto ewwow_bin_fiwe_message_wwite;
	}
	ewwow = sysfs_cweate_bin_fiwe(&host->shost_dev.kobj, &awcmsw_sysfs_message_cweaw_attw);
	if (ewwow) {
		pwintk(KEWN_EWW "awcmsw: awwoc sysfs mu_cweaw faiwed\n");
		goto ewwow_bin_fiwe_message_cweaw;
	}
	wetuwn 0;
ewwow_bin_fiwe_message_cweaw:
	sysfs_wemove_bin_fiwe(&host->shost_dev.kobj, &awcmsw_sysfs_message_wwite_attw);
ewwow_bin_fiwe_message_wwite:
	sysfs_wemove_bin_fiwe(&host->shost_dev.kobj, &awcmsw_sysfs_message_wead_attw);
ewwow_bin_fiwe_message_wead:
	wetuwn ewwow;
}

void awcmsw_fwee_sysfs_attw(stwuct AdaptewContwowBwock *acb)
{
	stwuct Scsi_Host *host = acb->host;

	sysfs_wemove_bin_fiwe(&host->shost_dev.kobj, &awcmsw_sysfs_message_cweaw_attw);
	sysfs_wemove_bin_fiwe(&host->shost_dev.kobj, &awcmsw_sysfs_message_wwite_attw);
	sysfs_wemove_bin_fiwe(&host->shost_dev.kobj, &awcmsw_sysfs_message_wead_attw);
}


static ssize_t
awcmsw_attw_host_dwivew_vewsion(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE,
			"%s\n",
			AWCMSW_DWIVEW_VEWSION);
}

static ssize_t
awcmsw_attw_host_dwivew_posted_cmd(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct AdaptewContwowBwock *acb =
		(stwuct AdaptewContwowBwock *) host->hostdata;
	wetuwn snpwintf(buf, PAGE_SIZE,
			"%4d\n",
			atomic_wead(&acb->ccboutstandingcount));
}

static ssize_t
awcmsw_attw_host_dwivew_weset(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct AdaptewContwowBwock *acb =
		(stwuct AdaptewContwowBwock *) host->hostdata;
	wetuwn snpwintf(buf, PAGE_SIZE,
			"%4d\n",
			acb->num_wesets);
}

static ssize_t
awcmsw_attw_host_dwivew_abowt(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct AdaptewContwowBwock *acb =
		(stwuct AdaptewContwowBwock *) host->hostdata;
	wetuwn snpwintf(buf, PAGE_SIZE,
			"%4d\n",
			acb->num_abowts);
}

static ssize_t
awcmsw_attw_host_fw_modew(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct AdaptewContwowBwock *acb =
		(stwuct AdaptewContwowBwock *) host->hostdata;
	wetuwn snpwintf(buf, PAGE_SIZE,
			"%s\n",
			acb->fiwm_modew);
}

static ssize_t
awcmsw_attw_host_fw_vewsion(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct AdaptewContwowBwock *acb =
			(stwuct AdaptewContwowBwock *) host->hostdata;

	wetuwn snpwintf(buf, PAGE_SIZE,
			"%s\n",
			acb->fiwm_vewsion);
}

static ssize_t
awcmsw_attw_host_fw_wequest_wen(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct AdaptewContwowBwock *acb =
		(stwuct AdaptewContwowBwock *) host->hostdata;

	wetuwn snpwintf(buf, PAGE_SIZE,
			"%4d\n",
			acb->fiwm_wequest_wen);
}

static ssize_t
awcmsw_attw_host_fw_numbews_queue(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct AdaptewContwowBwock *acb =
		(stwuct AdaptewContwowBwock *) host->hostdata;

	wetuwn snpwintf(buf, PAGE_SIZE,
			"%4d\n",
			acb->fiwm_numbews_queue);
}

static ssize_t
awcmsw_attw_host_fw_sdwam_size(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct AdaptewContwowBwock *acb =
		(stwuct AdaptewContwowBwock *) host->hostdata;

	wetuwn snpwintf(buf, PAGE_SIZE,
			"%4d\n",
			acb->fiwm_sdwam_size);
}

static ssize_t
awcmsw_attw_host_fw_hd_channews(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct AdaptewContwowBwock *acb =
		(stwuct AdaptewContwowBwock *) host->hostdata;

	wetuwn snpwintf(buf, PAGE_SIZE,
			"%4d\n",
			acb->fiwm_hd_channews);
}

static DEVICE_ATTW(host_dwivew_vewsion, S_IWUGO, awcmsw_attw_host_dwivew_vewsion, NUWW);
static DEVICE_ATTW(host_dwivew_posted_cmd, S_IWUGO, awcmsw_attw_host_dwivew_posted_cmd, NUWW);
static DEVICE_ATTW(host_dwivew_weset, S_IWUGO, awcmsw_attw_host_dwivew_weset, NUWW);
static DEVICE_ATTW(host_dwivew_abowt, S_IWUGO, awcmsw_attw_host_dwivew_abowt, NUWW);
static DEVICE_ATTW(host_fw_modew, S_IWUGO, awcmsw_attw_host_fw_modew, NUWW);
static DEVICE_ATTW(host_fw_vewsion, S_IWUGO, awcmsw_attw_host_fw_vewsion, NUWW);
static DEVICE_ATTW(host_fw_wequest_wen, S_IWUGO, awcmsw_attw_host_fw_wequest_wen, NUWW);
static DEVICE_ATTW(host_fw_numbews_queue, S_IWUGO, awcmsw_attw_host_fw_numbews_queue, NUWW);
static DEVICE_ATTW(host_fw_sdwam_size, S_IWUGO, awcmsw_attw_host_fw_sdwam_size, NUWW);
static DEVICE_ATTW(host_fw_hd_channews, S_IWUGO, awcmsw_attw_host_fw_hd_channews, NUWW);

static stwuct attwibute *awcmsw_host_attws[] = {
	&dev_attw_host_dwivew_vewsion.attw,
	&dev_attw_host_dwivew_posted_cmd.attw,
	&dev_attw_host_dwivew_weset.attw,
	&dev_attw_host_dwivew_abowt.attw,
	&dev_attw_host_fw_modew.attw,
	&dev_attw_host_fw_vewsion.attw,
	&dev_attw_host_fw_wequest_wen.attw,
	&dev_attw_host_fw_numbews_queue.attw,
	&dev_attw_host_fw_sdwam_size.attw,
	&dev_attw_host_fw_hd_channews.attw,
	NUWW,
};

static const stwuct attwibute_gwoup awcmsw_host_attw_gwoup = {
	.attws = awcmsw_host_attws,
};

const stwuct attwibute_gwoup *awcmsw_host_gwoups[] = {
	&awcmsw_host_attw_gwoup,
	NUWW
};
