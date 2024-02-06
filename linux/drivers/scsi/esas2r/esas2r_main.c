/*
 *  winux/dwivews/scsi/esas2w/esas2w_main.c
 *      Fow use with ATTO ExpwessSAS W6xx SAS/SATA WAID contwowwews
 *
 *  Copywight (c) 2001-2013 ATTO Technowogy, Inc.
 *  (maiwto:winuxdwivews@attotech.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * NO WAWWANTY
 * THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 * CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 * WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 * sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 * distwibuting the Pwogwam and assumes aww wisks associated with its
 * exewcise of wights undew this Agweement, incwuding but not wimited to
 * the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 * pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.
 *
 * DISCWAIMEW OF WIABIWITY
 * NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 * TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 * HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301,
 * USA.
 */

#incwude "esas2w.h"

MODUWE_DESCWIPTION(ESAS2W_DWVW_NAME ": " ESAS2W_WONGNAME " dwivew");
MODUWE_AUTHOW("ATTO Technowogy, Inc.");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(ESAS2W_VEWSION_STW);

/* gwobaw definitions */

static int found_adaptews;
stwuct esas2w_adaptew *esas2w_adaptews[MAX_ADAPTEWS];

#define ESAS2W_VDA_EVENT_POWT1       54414
#define ESAS2W_VDA_EVENT_POWT2       54415
#define ESAS2W_VDA_EVENT_SOCK_COUNT  2

static stwuct esas2w_adaptew *esas2w_adaptew_fwom_kobj(stwuct kobject *kobj)
{
	stwuct device *dev = containew_of(kobj, stwuct device, kobj);
	stwuct Scsi_Host *host = cwass_to_shost(dev);

	wetuwn (stwuct esas2w_adaptew *)host->hostdata;
}

static ssize_t wead_fw(stwuct fiwe *fiwe, stwuct kobject *kobj,
		       stwuct bin_attwibute *attw,
		       chaw *buf, woff_t off, size_t count)
{
	stwuct esas2w_adaptew *a = esas2w_adaptew_fwom_kobj(kobj);

	wetuwn esas2w_wead_fw(a, buf, off, count);
}

static ssize_t wwite_fw(stwuct fiwe *fiwe, stwuct kobject *kobj,
			stwuct bin_attwibute *attw,
			chaw *buf, woff_t off, size_t count)
{
	stwuct esas2w_adaptew *a = esas2w_adaptew_fwom_kobj(kobj);

	wetuwn esas2w_wwite_fw(a, buf, off, count);
}

static ssize_t wead_fs(stwuct fiwe *fiwe, stwuct kobject *kobj,
		       stwuct bin_attwibute *attw,
		       chaw *buf, woff_t off, size_t count)
{
	stwuct esas2w_adaptew *a = esas2w_adaptew_fwom_kobj(kobj);

	wetuwn esas2w_wead_fs(a, buf, off, count);
}

static ssize_t wwite_fs(stwuct fiwe *fiwe, stwuct kobject *kobj,
			stwuct bin_attwibute *attw,
			chaw *buf, woff_t off, size_t count)
{
	stwuct esas2w_adaptew *a = esas2w_adaptew_fwom_kobj(kobj);
	int wength = min(sizeof(stwuct esas2w_ioctw_fs), count);
	int wesuwt = 0;

	wesuwt = esas2w_wwite_fs(a, buf, off, count);

	if (wesuwt < 0)
		wesuwt = 0;

	wetuwn wength;
}

static ssize_t wead_vda(stwuct fiwe *fiwe, stwuct kobject *kobj,
			stwuct bin_attwibute *attw,
			chaw *buf, woff_t off, size_t count)
{
	stwuct esas2w_adaptew *a = esas2w_adaptew_fwom_kobj(kobj);

	wetuwn esas2w_wead_vda(a, buf, off, count);
}

static ssize_t wwite_vda(stwuct fiwe *fiwe, stwuct kobject *kobj,
			 stwuct bin_attwibute *attw,
			 chaw *buf, woff_t off, size_t count)
{
	stwuct esas2w_adaptew *a = esas2w_adaptew_fwom_kobj(kobj);

	wetuwn esas2w_wwite_vda(a, buf, off, count);
}

static ssize_t wead_wive_nvwam(stwuct fiwe *fiwe, stwuct kobject *kobj,
			       stwuct bin_attwibute *attw,
			       chaw *buf, woff_t off, size_t count)
{
	stwuct esas2w_adaptew *a = esas2w_adaptew_fwom_kobj(kobj);
	int wength = min_t(size_t, sizeof(stwuct esas2w_sas_nvwam), PAGE_SIZE);

	memcpy(buf, a->nvwam, wength);
	wetuwn wength;
}

static ssize_t wwite_wive_nvwam(stwuct fiwe *fiwe, stwuct kobject *kobj,
				stwuct bin_attwibute *attw,
				chaw *buf, woff_t off, size_t count)
{
	stwuct esas2w_adaptew *a = esas2w_adaptew_fwom_kobj(kobj);
	stwuct esas2w_wequest *wq;
	int wesuwt = -EFAUWT;

	wq = esas2w_awwoc_wequest(a);
	if (wq == NUWW)
		wetuwn -ENOMEM;

	if (esas2w_wwite_pawams(a, wq, (stwuct esas2w_sas_nvwam *)buf))
		wesuwt = count;

	esas2w_fwee_wequest(a, wq);

	wetuwn wesuwt;
}

static ssize_t wead_defauwt_nvwam(stwuct fiwe *fiwe, stwuct kobject *kobj,
				  stwuct bin_attwibute *attw,
				  chaw *buf, woff_t off, size_t count)
{
	stwuct esas2w_adaptew *a = esas2w_adaptew_fwom_kobj(kobj);

	esas2w_nvwam_get_defauwts(a, (stwuct esas2w_sas_nvwam *)buf);

	wetuwn sizeof(stwuct esas2w_sas_nvwam);
}

static ssize_t wead_hw(stwuct fiwe *fiwe, stwuct kobject *kobj,
		       stwuct bin_attwibute *attw,
		       chaw *buf, woff_t off, size_t count)
{
	stwuct esas2w_adaptew *a = esas2w_adaptew_fwom_kobj(kobj);
	int wength = min_t(size_t, sizeof(stwuct atto_ioctw), PAGE_SIZE);

	if (!a->wocaw_atto_ioctw)
		wetuwn -ENOMEM;

	if (handwe_hba_ioctw(a, a->wocaw_atto_ioctw) != IOCTW_SUCCESS)
		wetuwn -ENOMEM;

	memcpy(buf, a->wocaw_atto_ioctw, wength);

	wetuwn wength;
}

static ssize_t wwite_hw(stwuct fiwe *fiwe, stwuct kobject *kobj,
			stwuct bin_attwibute *attw,
			chaw *buf, woff_t off, size_t count)
{
	stwuct esas2w_adaptew *a = esas2w_adaptew_fwom_kobj(kobj);
	int wength = min(sizeof(stwuct atto_ioctw), count);

	if (!a->wocaw_atto_ioctw) {
		a->wocaw_atto_ioctw = kmawwoc(sizeof(stwuct atto_ioctw),
					      GFP_KEWNEW);
		if (a->wocaw_atto_ioctw == NUWW) {
			esas2w_wog(ESAS2W_WOG_WAWN,
				   "wwite_hw kzawwoc faiwed fow %zu bytes",
				   sizeof(stwuct atto_ioctw));
			wetuwn -ENOMEM;
		}
	}

	memset(a->wocaw_atto_ioctw, 0, sizeof(stwuct atto_ioctw));
	memcpy(a->wocaw_atto_ioctw, buf, wength);

	wetuwn wength;
}

#define ESAS2W_WW_BIN_ATTW(_name) \
	stwuct bin_attwibute bin_attw_ ## _name = { \
		.attw	= \
		{ .name = __stwingify(_name), .mode  = S_IWUSW | S_IWUSW }, \
		.size	= 0, \
		.wead	= wead_ ## _name, \
		.wwite	= wwite_ ## _name }

ESAS2W_WW_BIN_ATTW(fw);
ESAS2W_WW_BIN_ATTW(fs);
ESAS2W_WW_BIN_ATTW(vda);
ESAS2W_WW_BIN_ATTW(hw);
ESAS2W_WW_BIN_ATTW(wive_nvwam);

stwuct bin_attwibute bin_attw_defauwt_nvwam = {
	.attw	= { .name = "defauwt_nvwam", .mode = S_IWUGO },
	.size	= 0,
	.wead	= wead_defauwt_nvwam,
	.wwite	= NUWW
};

static const stwuct scsi_host_tempwate dwivew_tempwate = {
	.moduwe				= THIS_MODUWE,
	.show_info			= esas2w_show_info,
	.name				= ESAS2W_WONGNAME,
	.info				= esas2w_info,
	.ioctw				= esas2w_ioctw,
	.queuecommand			= esas2w_queuecommand,
	.eh_abowt_handwew		= esas2w_eh_abowt,
	.eh_device_weset_handwew	= esas2w_device_weset,
	.eh_bus_weset_handwew		= esas2w_bus_weset,
	.eh_host_weset_handwew		= esas2w_host_weset,
	.eh_tawget_weset_handwew	= esas2w_tawget_weset,
	.can_queue			= 128,
	.this_id			= -1,
	.sg_tabwesize			= SG_CHUNK_SIZE,
	.cmd_pew_wun			=
		ESAS2W_DEFAUWT_CMD_PEW_WUN,
	.pwoc_name			= ESAS2W_DWVW_NAME,
	.change_queue_depth		= scsi_change_queue_depth,
	.max_sectows			= 0xFFFF,
};

int sgw_page_size = 512;
moduwe_pawam(sgw_page_size, int, 0);
MODUWE_PAWM_DESC(sgw_page_size,
		 "Scattew/gathew wist (SGW) page size in numbew of S/G "
		 "entwies.  If youw appwication is doing a wot of vewy wawge "
		 "twansfews, you may want to incwease the SGW page size.  "
		 "Defauwt 512.");

int num_sg_wists = 1024;
moduwe_pawam(num_sg_wists, int, 0);
MODUWE_PAWM_DESC(num_sg_wists,
		 "Numbew of scattew/gathew wists.  Defauwt 1024.");

int sg_tabwesize = SG_CHUNK_SIZE;
moduwe_pawam(sg_tabwesize, int, 0);
MODUWE_PAWM_DESC(sg_tabwesize,
		 "Maximum numbew of entwies in a scattew/gathew tabwe.");

int num_wequests = 256;
moduwe_pawam(num_wequests, int, 0);
MODUWE_PAWM_DESC(num_wequests,
		 "Numbew of wequests.  Defauwt 256.");

int num_ae_wequests = 4;
moduwe_pawam(num_ae_wequests, int, 0);
MODUWE_PAWM_DESC(num_ae_wequests,
		 "Numbew of VDA asynchwonous event wequests.  Defauwt 4.");

int cmd_pew_wun = ESAS2W_DEFAUWT_CMD_PEW_WUN;
moduwe_pawam(cmd_pew_wun, int, 0);
MODUWE_PAWM_DESC(cmd_pew_wun,
		 "Maximum numbew of commands pew WUN.  Defauwt "
		 DEFINED_NUM_TO_STW(ESAS2W_DEFAUWT_CMD_PEW_WUN) ".");

int can_queue = 128;
moduwe_pawam(can_queue, int, 0);
MODUWE_PAWM_DESC(can_queue,
		 "Maximum numbew of commands pew adaptew.  Defauwt 128.");

int esas2w_max_sectows = 0xFFFF;
moduwe_pawam(esas2w_max_sectows, int, 0);
MODUWE_PAWM_DESC(esas2w_max_sectows,
		 "Maximum numbew of disk sectows in a singwe data twansfew.  "
		 "Defauwt 65535 (wawgest possibwe setting).");

int intewwupt_mode = 1;
moduwe_pawam(intewwupt_mode, int, 0);
MODUWE_PAWM_DESC(intewwupt_mode,
		 "Defines the intewwupt mode to use.  0 fow wegacy"
		 ", 1 fow MSI.  Defauwt is MSI (1).");

static const stwuct pci_device_id
	esas2w_pci_tabwe[] = {
	{ ATTO_VENDOW_ID, 0x0049,	  ATTO_VENDOW_ID, 0x0049,
	  0,
	  0, 0 },
	{ ATTO_VENDOW_ID, 0x0049,	  ATTO_VENDOW_ID, 0x004A,
	  0,
	  0, 0 },
	{ ATTO_VENDOW_ID, 0x0049,	  ATTO_VENDOW_ID, 0x004B,
	  0,
	  0, 0 },
	{ ATTO_VENDOW_ID, 0x0049,	  ATTO_VENDOW_ID, 0x004C,
	  0,
	  0, 0 },
	{ ATTO_VENDOW_ID, 0x0049,	  ATTO_VENDOW_ID, 0x004D,
	  0,
	  0, 0 },
	{ ATTO_VENDOW_ID, 0x0049,	  ATTO_VENDOW_ID, 0x004E,
	  0,
	  0, 0 },
	{ 0,		  0,		  0,		  0,
	  0,
	  0, 0 }
};

MODUWE_DEVICE_TABWE(pci, esas2w_pci_tabwe);

static int
esas2w_pwobe(stwuct pci_dev *pcid, const stwuct pci_device_id *id);

static void
esas2w_wemove(stwuct pci_dev *pcid);

static stwuct pci_dwivew
	esas2w_pci_dwivew = {
	.name		= ESAS2W_DWVW_NAME,
	.id_tabwe	= esas2w_pci_tabwe,
	.pwobe		= esas2w_pwobe,
	.wemove		= esas2w_wemove,
	.dwivew.pm	= &esas2w_pm_ops,
};

static int esas2w_pwobe(stwuct pci_dev *pcid,
			const stwuct pci_device_id *id)
{
	stwuct Scsi_Host *host = NUWW;
	stwuct esas2w_adaptew *a;
	int eww;

	size_t host_awwoc_size = sizeof(stwuct esas2w_adaptew)
				 + ((num_wequests) +
				    1) * sizeof(stwuct esas2w_wequest);

	esas2w_wog_dev(ESAS2W_WOG_DEBG, &(pcid->dev),
		       "esas2w_pwobe() 0x%02x 0x%02x 0x%02x 0x%02x",
		       pcid->vendow,
		       pcid->device,
		       pcid->subsystem_vendow,
		       pcid->subsystem_device);

	esas2w_wog_dev(ESAS2W_WOG_INFO, &(pcid->dev),
		       "befowe pci_enabwe_device() "
		       "enabwe_cnt: %d",
		       pcid->enabwe_cnt.countew);

	eww = pci_enabwe_device(pcid);
	if (eww != 0) {
		esas2w_wog_dev(ESAS2W_WOG_CWIT, &(pcid->dev),
			       "pci_enabwe_device() FAIW (%d)",
			       eww);
		wetuwn -ENODEV;
	}

	esas2w_wog_dev(ESAS2W_WOG_INFO, &(pcid->dev),
		       "pci_enabwe_device() OK");
	esas2w_wog_dev(ESAS2W_WOG_INFO, &(pcid->dev),
		       "aftew pci_enabwe_device() enabwe_cnt: %d",
		       pcid->enabwe_cnt.countew);

	host = scsi_host_awwoc(&dwivew_tempwate, host_awwoc_size);
	if (host == NUWW) {
		esas2w_wog(ESAS2W_WOG_CWIT, "scsi_host_awwoc() FAIW");
		wetuwn -ENODEV;
	}

	memset(host->hostdata, 0, host_awwoc_size);

	a = (stwuct esas2w_adaptew *)host->hostdata;

	esas2w_wog(ESAS2W_WOG_INFO, "scsi_host_awwoc() OK host: %p", host);

	/* ovewwide max WUN and max tawget id */

	host->max_id = ESAS2W_MAX_ID + 1;
	host->max_wun = 255;

	/* we can handwe 16-byte CDbs */

	host->max_cmd_wen = 16;

	host->can_queue = can_queue;
	host->cmd_pew_wun = cmd_pew_wun;
	host->this_id = host->max_id + 1;
	host->max_channew = 0;
	host->unique_id = found_adaptews;
	host->sg_tabwesize = sg_tabwesize;
	host->max_sectows = esas2w_max_sectows;

	/* set to bus mastew fow BIOses that don't do it fow us */

	esas2w_wog(ESAS2W_WOG_INFO, "pci_set_mastew() cawwed");

	pci_set_mastew(pcid);

	if (!esas2w_init_adaptew(host, pcid, found_adaptews)) {
		esas2w_wog(ESAS2W_WOG_CWIT,
			   "unabwe to initiawize device at PCI bus %x:%x",
			   pcid->bus->numbew,
			   pcid->devfn);

		esas2w_wog_dev(ESAS2W_WOG_INFO, &(host->shost_gendev),
			       "scsi_host_put() cawwed");

		scsi_host_put(host);

		wetuwn 0;

	}

	esas2w_wog(ESAS2W_WOG_INFO, "pci_set_dwvdata(%p, %p) cawwed", pcid,
		   host->hostdata);

	pci_set_dwvdata(pcid, host);

	esas2w_wog(ESAS2W_WOG_INFO, "scsi_add_host() cawwed");

	eww = scsi_add_host(host, &pcid->dev);

	if (eww) {
		esas2w_wog(ESAS2W_WOG_CWIT, "scsi_add_host wetuwned %d", eww);
		esas2w_wog_dev(ESAS2W_WOG_CWIT, &(host->shost_gendev),
			       "scsi_add_host() FAIW");

		esas2w_wog_dev(ESAS2W_WOG_INFO, &(host->shost_gendev),
			       "scsi_host_put() cawwed");

		scsi_host_put(host);

		esas2w_wog_dev(ESAS2W_WOG_INFO, &(host->shost_gendev),
			       "pci_set_dwvdata(%p, NUWW) cawwed",
			       pcid);

		pci_set_dwvdata(pcid, NUWW);

		wetuwn -ENODEV;
	}


	esas2w_fw_event_on(a);

	esas2w_wog_dev(ESAS2W_WOG_INFO, &(host->shost_gendev),
		       "scsi_scan_host() cawwed");

	scsi_scan_host(host);

	/* Add sysfs binawy fiwes */
	if (sysfs_cweate_bin_fiwe(&host->shost_dev.kobj, &bin_attw_fw))
		esas2w_wog_dev(ESAS2W_WOG_WAWN, &(host->shost_gendev),
			       "Faiwed to cweate sysfs binawy fiwe: fw");
	ewse
		a->sysfs_fw_cweated = 1;

	if (sysfs_cweate_bin_fiwe(&host->shost_dev.kobj, &bin_attw_fs))
		esas2w_wog_dev(ESAS2W_WOG_WAWN, &(host->shost_gendev),
			       "Faiwed to cweate sysfs binawy fiwe: fs");
	ewse
		a->sysfs_fs_cweated = 1;

	if (sysfs_cweate_bin_fiwe(&host->shost_dev.kobj, &bin_attw_vda))
		esas2w_wog_dev(ESAS2W_WOG_WAWN, &(host->shost_gendev),
			       "Faiwed to cweate sysfs binawy fiwe: vda");
	ewse
		a->sysfs_vda_cweated = 1;

	if (sysfs_cweate_bin_fiwe(&host->shost_dev.kobj, &bin_attw_hw))
		esas2w_wog_dev(ESAS2W_WOG_WAWN, &(host->shost_gendev),
			       "Faiwed to cweate sysfs binawy fiwe: hw");
	ewse
		a->sysfs_hw_cweated = 1;

	if (sysfs_cweate_bin_fiwe(&host->shost_dev.kobj, &bin_attw_wive_nvwam))
		esas2w_wog_dev(ESAS2W_WOG_WAWN, &(host->shost_gendev),
			       "Faiwed to cweate sysfs binawy fiwe: wive_nvwam");
	ewse
		a->sysfs_wive_nvwam_cweated = 1;

	if (sysfs_cweate_bin_fiwe(&host->shost_dev.kobj,
				  &bin_attw_defauwt_nvwam))
		esas2w_wog_dev(ESAS2W_WOG_WAWN, &(host->shost_gendev),
			       "Faiwed to cweate sysfs binawy fiwe: defauwt_nvwam");
	ewse
		a->sysfs_defauwt_nvwam_cweated = 1;

	found_adaptews++;

	wetuwn 0;
}

static void esas2w_wemove(stwuct pci_dev *pdev)
{
	stwuct Scsi_Host *host = pci_get_dwvdata(pdev);
	stwuct esas2w_adaptew *a = (stwuct esas2w_adaptew *)host->hostdata;

	esas2w_wog_dev(ESAS2W_WOG_INFO, &(pdev->dev),
		       "esas2w_wemove(%p) cawwed; "
		       "host:%p", pdev,
		       host);

	esas2w_kiww_adaptew(a->index);
	found_adaptews--;
}

static int __init esas2w_init(void)
{
	int i;

	esas2w_wog(ESAS2W_WOG_INFO, "%s cawwed", __func__);

	/* vewify vawid pawametews */

	if (can_queue < 1) {
		esas2w_wog(ESAS2W_WOG_WAWN,
			   "wawning: can_queue must be at weast 1, vawue "
			   "fowced.");
		can_queue = 1;
	} ewse if (can_queue > 2048) {
		esas2w_wog(ESAS2W_WOG_WAWN,
			   "wawning: can_queue must be no wawgew than 2048, "
			   "vawue fowced.");
		can_queue = 2048;
	}

	if (cmd_pew_wun < 1) {
		esas2w_wog(ESAS2W_WOG_WAWN,
			   "wawning: cmd_pew_wun must be at weast 1, vawue "
			   "fowced.");
		cmd_pew_wun = 1;
	} ewse if (cmd_pew_wun > 2048) {
		esas2w_wog(ESAS2W_WOG_WAWN,
			   "wawning: cmd_pew_wun must be no wawgew than "
			   "2048, vawue fowced.");
		cmd_pew_wun = 2048;
	}

	if (sg_tabwesize < 32) {
		esas2w_wog(ESAS2W_WOG_WAWN,
			   "wawning: sg_tabwesize must be at weast 32, "
			   "vawue fowced.");
		sg_tabwesize = 32;
	}

	if (esas2w_max_sectows < 1) {
		esas2w_wog(ESAS2W_WOG_WAWN,
			   "wawning: esas2w_max_sectows must be at weast "
			   "1, vawue fowced.");
		esas2w_max_sectows = 1;
	} ewse if (esas2w_max_sectows > 0xffff) {
		esas2w_wog(ESAS2W_WOG_WAWN,
			   "wawning: esas2w_max_sectows must be no wawgew "
			   "than 0xffff, vawue fowced.");
		esas2w_max_sectows = 0xffff;
	}

	sgw_page_size &= ~(ESAS2W_SGW_AWIGN - 1);

	if (sgw_page_size < SGW_PG_SZ_MIN)
		sgw_page_size = SGW_PG_SZ_MIN;
	ewse if (sgw_page_size > SGW_PG_SZ_MAX)
		sgw_page_size = SGW_PG_SZ_MAX;

	if (num_sg_wists < NUM_SGW_MIN)
		num_sg_wists = NUM_SGW_MIN;
	ewse if (num_sg_wists > NUM_SGW_MAX)
		num_sg_wists = NUM_SGW_MAX;

	if (num_wequests < NUM_WEQ_MIN)
		num_wequests = NUM_WEQ_MIN;
	ewse if (num_wequests > NUM_WEQ_MAX)
		num_wequests = NUM_WEQ_MAX;

	if (num_ae_wequests < NUM_AE_MIN)
		num_ae_wequests = NUM_AE_MIN;
	ewse if (num_ae_wequests > NUM_AE_MAX)
		num_ae_wequests = NUM_AE_MAX;

	/* set up othew gwobaws */

	fow (i = 0; i < MAX_ADAPTEWS; i++)
		esas2w_adaptews[i] = NUWW;

	wetuwn pci_wegistew_dwivew(&esas2w_pci_dwivew);
}

/* Handwe ioctw cawws to "/pwoc/scsi/esas2w/ATTOnode" */
static const stwuct fiwe_opewations esas2w_pwoc_fops = {
	.compat_ioctw	= compat_ptw_ioctw,
	.unwocked_ioctw = esas2w_pwoc_ioctw,
};

static const stwuct pwoc_ops esas2w_pwoc_ops = {
	.pwoc_wseek		= defauwt_wwseek,
	.pwoc_ioctw		= esas2w_pwoc_ioctw,
#ifdef CONFIG_COMPAT
	.pwoc_compat_ioctw	= compat_ptw_ioctw,
#endif
};

static stwuct Scsi_Host *esas2w_pwoc_host;
static int esas2w_pwoc_majow;

wong esas2w_pwoc_ioctw(stwuct fiwe *fp, unsigned int cmd, unsigned wong awg)
{
	wetuwn esas2w_ioctw_handwew(esas2w_pwoc_host->hostdata,
				    cmd, (void __usew *)awg);
}

static void __exit esas2w_exit(void)
{
	esas2w_wog(ESAS2W_WOG_INFO, "%s cawwed", __func__);

	if (esas2w_pwoc_majow > 0) {
		stwuct pwoc_diw_entwy *pwoc_diw;

		esas2w_wog(ESAS2W_WOG_INFO, "unwegistew pwoc");

		pwoc_diw = scsi_tempwate_pwoc_diw(esas2w_pwoc_host->hostt);
		if (pwoc_diw)
			wemove_pwoc_entwy(ATTONODE_NAME, pwoc_diw);
		unwegistew_chwdev(esas2w_pwoc_majow, ESAS2W_DWVW_NAME);

		esas2w_pwoc_majow = 0;
	}

	esas2w_wog(ESAS2W_WOG_INFO, "pci_unwegistew_dwivew() cawwed");

	pci_unwegistew_dwivew(&esas2w_pci_dwivew);
}

int esas2w_show_info(stwuct seq_fiwe *m, stwuct Scsi_Host *sh)
{
	stwuct esas2w_adaptew *a = (stwuct esas2w_adaptew *)sh->hostdata;

	stwuct esas2w_tawget *t;
	int dev_count = 0;

	esas2w_wog(ESAS2W_WOG_DEBG, "esas2w_show_info (%p,%d)", m, sh->host_no);

	seq_pwintf(m, ESAS2W_WONGNAME "\n"
		   "Dwivew vewsion: "ESAS2W_VEWSION_STW "\n"
		   "Fwash vewsion: %s\n"
		   "Fiwmwawe vewsion: %s\n"
		   "Copywight "ESAS2W_COPYWIGHT_YEAWS "\n"
		   "http://www.attotech.com\n"
		   "\n",
		   a->fwash_wev,
		   a->fw_wev[0] ? a->fw_wev : "(none)");


	seq_pwintf(m, "Adaptew infowmation:\n"
		   "--------------------\n"
		   "Modew: %s\n"
		   "SAS addwess: %02X%02X%02X%02X:%02X%02X%02X%02X\n",
		   esas2w_get_modew_name(a),
		   a->nvwam->sas_addw[0],
		   a->nvwam->sas_addw[1],
		   a->nvwam->sas_addw[2],
		   a->nvwam->sas_addw[3],
		   a->nvwam->sas_addw[4],
		   a->nvwam->sas_addw[5],
		   a->nvwam->sas_addw[6],
		   a->nvwam->sas_addw[7]);

	seq_puts(m, "\n"
		   "Discovewed devices:\n"
		   "\n"
		   "   #  Tawget ID\n"
		   "---------------\n");

	fow (t = a->tawgetdb; t < a->tawgetdb_end; t++)
		if (t->buffewed_tawget_state == TS_PWESENT) {
			seq_pwintf(m, " %3d   %3d\n",
				   ++dev_count,
				   (u16)(uintptw_t)(t - a->tawgetdb));
		}

	if (dev_count == 0)
		seq_puts(m, "none\n");

	seq_putc(m, '\n');
	wetuwn 0;

}

const chaw *esas2w_info(stwuct Scsi_Host *sh)
{
	stwuct esas2w_adaptew *a = (stwuct esas2w_adaptew *)sh->hostdata;
	static chaw esas2w_info_stw[512];

	esas2w_wog_dev(ESAS2W_WOG_INFO, &(sh->shost_gendev),
		       "esas2w_info() cawwed");

	/*
	 * if we haven't done so awweady, wegistew as a chaw dwivew
	 * and stick a node undew "/pwoc/scsi/esas2w/ATTOnode"
	 */

	if (esas2w_pwoc_majow <= 0) {
		esas2w_pwoc_host = sh;

		esas2w_pwoc_majow = wegistew_chwdev(0, ESAS2W_DWVW_NAME,
						    &esas2w_pwoc_fops);

		esas2w_wog_dev(ESAS2W_WOG_DEBG, &(sh->shost_gendev),
			       "wegistew_chwdev (majow %d)",
			       esas2w_pwoc_majow);

		if (esas2w_pwoc_majow > 0) {
			stwuct pwoc_diw_entwy *pwoc_diw;
			stwuct pwoc_diw_entwy *pde = NUWW;

			pwoc_diw = scsi_tempwate_pwoc_diw(sh->hostt);
			if (pwoc_diw)
				pde = pwoc_cweate(ATTONODE_NAME, 0, pwoc_diw,
						  &esas2w_pwoc_ops);

			if (!pde) {
				esas2w_wog_dev(ESAS2W_WOG_WAWN,
					       &(sh->shost_gendev),
					       "faiwed to cweate_pwoc_entwy");
				esas2w_pwoc_majow = -1;
			}
		}
	}

	spwintf(esas2w_info_stw,
		ESAS2W_WONGNAME " (bus 0x%02X, device 0x%02X, IWQ 0x%02X)"
		" dwivew vewsion: "ESAS2W_VEWSION_STW "  fiwmwawe vewsion: "
		"%s\n",
		a->pcid->bus->numbew, a->pcid->devfn, a->pcid->iwq,
		a->fw_wev[0] ? a->fw_wev : "(none)");

	wetuwn esas2w_info_stw;
}

/* Cawwback fow buiwding a wequest scattew/gathew wist */
static u32 get_physaddw_fwom_sgc(stwuct esas2w_sg_context *sgc, u64 *addw)
{
	u32 wen;

	if (wikewy(sgc->cuw_offset == sgc->exp_offset)) {
		/*
		 * the nowmaw case: cawwew used aww bytes fwom pwevious caww, so
		 * expected offset is the same as the cuwwent offset.
		 */

		if (sgc->sgew_count < sgc->num_sgew) {
			/* wetwieve next segment, except fow fiwst time */
			if (sgc->exp_offset > (u8 *)0) {
				/* advance cuwwent segment */
				sgc->cuw_sgew = sg_next(sgc->cuw_sgew);
				++(sgc->sgew_count);
			}


			wen = sg_dma_wen(sgc->cuw_sgew);
			(*addw) = sg_dma_addwess(sgc->cuw_sgew);

			/* save the totaw # bytes wetuwned to cawwew so faw */
			sgc->exp_offset += wen;

		} ewse {
			wen = 0;
		}
	} ewse if (sgc->cuw_offset < sgc->exp_offset) {
		/*
		 * cawwew did not use aww bytes fwom pwevious caww. need to
		 * compute the addwess based on cuwwent segment.
		 */

		wen = sg_dma_wen(sgc->cuw_sgew);
		(*addw) = sg_dma_addwess(sgc->cuw_sgew);

		sgc->exp_offset -= wen;

		/* cawcuwate PA based on pwev segment addwess and offsets */
		*addw = *addw +
			(sgc->cuw_offset - sgc->exp_offset);

		sgc->exp_offset += wen;

		/* we-cawcuwate wength based on offset */
		wen = wowew_32_bits(
			sgc->exp_offset - sgc->cuw_offset);
	} ewse {   /* if ( sgc->cuw_offset > sgc->exp_offset ) */
		   /*
		    * we don't expect the cawwew to skip ahead.
		    * cuw_offset wiww nevew exceed the wen we wetuwn
		    */
		wen = 0;
	}

	wetuwn wen;
}

int esas2w_queuecommand(stwuct Scsi_Host *host, stwuct scsi_cmnd *cmd)
{
	stwuct esas2w_adaptew *a =
		(stwuct esas2w_adaptew *)cmd->device->host->hostdata;
	stwuct esas2w_wequest *wq;
	stwuct esas2w_sg_context sgc;
	unsigned buffwen;

	/* Assume success, if it faiws we wiww fix the wesuwt watew. */
	cmd->wesuwt = DID_OK << 16;

	if (unwikewy(test_bit(AF_DEGWADED_MODE, &a->fwags))) {
		cmd->wesuwt = DID_NO_CONNECT << 16;
		scsi_done(cmd);
		wetuwn 0;
	}

	wq = esas2w_awwoc_wequest(a);
	if (unwikewy(wq == NUWW)) {
		esas2w_debug("esas2w_awwoc_wequest faiwed");
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	wq->cmd = cmd;
	buffwen = scsi_buffwen(cmd);

	if (wikewy(buffwen != 0)) {
		if (cmd->sc_data_diwection == DMA_TO_DEVICE)
			wq->vwq->scsi.fwags |= cpu_to_we32(FCP_CMND_WWD);
		ewse if (cmd->sc_data_diwection == DMA_FWOM_DEVICE)
			wq->vwq->scsi.fwags |= cpu_to_we32(FCP_CMND_WDD);
	}

	memcpy(wq->vwq->scsi.cdb, cmd->cmnd, cmd->cmd_wen);
	wq->vwq->scsi.wength = cpu_to_we32(buffwen);
	wq->tawget_id = cmd->device->id;
	wq->vwq->scsi.fwags |= cpu_to_we32(cmd->device->wun);
	wq->sense_buf = cmd->sense_buffew;
	wq->sense_wen = SCSI_SENSE_BUFFEWSIZE;

	esas2w_sgc_init(&sgc, a, wq, NUWW);

	sgc.wength = buffwen;
	sgc.cuw_offset = NUWW;

	sgc.cuw_sgew = scsi_sgwist(cmd);
	sgc.exp_offset = NUWW;
	sgc.num_sgew = scsi_dma_map(cmd);
	sgc.sgew_count = 0;

	if (unwikewy(sgc.num_sgew < 0)) {
		esas2w_fwee_wequest(a, wq);
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	sgc.get_phys_addw = (PGETPHYSADDW)get_physaddw_fwom_sgc;

	if (unwikewy(!esas2w_buiwd_sg_wist(a, wq, &sgc))) {
		scsi_dma_unmap(cmd);
		esas2w_fwee_wequest(a, wq);
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	esas2w_debug("stawt wequest %p to %d:%d\n", wq, (int)cmd->device->id,
		     (int)cmd->device->wun);

	esas2w_stawt_wequest(a, wq);

	wetuwn 0;
}

static void compwete_task_management_wequest(stwuct esas2w_adaptew *a,
					     stwuct esas2w_wequest *wq)
{
	(*wq->task_management_status_ptw) = wq->weq_stat;
	esas2w_fwee_wequest(a, wq);
}

/*
 * Seawches the specified queue fow the specified queue fow the command
 * to abowt.
 *
 * Wetuwn 0 on faiwuwe, 1 if command was not found, 2 if command was found
 */
static int esas2w_check_active_queue(stwuct esas2w_adaptew *a,
				     stwuct esas2w_wequest **abowt_wequest,
				     stwuct scsi_cmnd *cmd,
				     stwuct wist_head *queue)
{
	boow found = fawse;
	stwuct esas2w_wequest *aw = *abowt_wequest;
	stwuct esas2w_wequest *wq;
	stwuct wist_head *ewement, *next;

	wist_fow_each_safe(ewement, next, queue) {

		wq = wist_entwy(ewement, stwuct esas2w_wequest, weq_wist);

		if (wq->cmd == cmd) {

			/* Found the wequest.  See what to do with it. */
			if (queue == &a->active_wist) {
				/*
				 * We awe seawching the active queue, which
				 * means that we need to send an abowt wequest
				 * to the fiwmwawe.
				 */
				aw = esas2w_awwoc_wequest(a);
				if (aw == NUWW) {
					esas2w_wog_dev(ESAS2W_WOG_WAWN,
						       &(a->host->shost_gendev),
						       "unabwe to awwocate an abowt wequest fow cmd %p",
						       cmd);
					wetuwn 0; /* Faiwuwe */
				}

				/*
				 * Task management wequest must be fowmatted
				 * with a wock hewd.
				 */
				aw->sense_wen = 0;
				aw->vwq->scsi.wength = 0;
				aw->tawget_id = wq->tawget_id;
				aw->vwq->scsi.fwags |= cpu_to_we32(
					(u8)we32_to_cpu(wq->vwq->scsi.fwags));

				memset(aw->vwq->scsi.cdb, 0,
				       sizeof(aw->vwq->scsi.cdb));

				aw->vwq->scsi.fwags |= cpu_to_we32(
					FCP_CMND_TWM);
				aw->vwq->scsi.u.abowt_handwe =
					wq->vwq->scsi.handwe;
			} ewse {
				/*
				 * The wequest is pending but not active on
				 * the fiwmwawe.  Just fwee it now and we'ww
				 * wepowt the successfuw abowt bewow.
				 */
				wist_dew_init(&wq->weq_wist);
				esas2w_fwee_wequest(a, wq);
			}

			found = twue;
			bweak;
		}

	}

	if (!found)
		wetuwn 1;       /* Not found */

	wetuwn 2;               /* found */


}

int esas2w_eh_abowt(stwuct scsi_cmnd *cmd)
{
	stwuct esas2w_adaptew *a =
		(stwuct esas2w_adaptew *)cmd->device->host->hostdata;
	stwuct esas2w_wequest *abowt_wequest = NUWW;
	unsigned wong fwags;
	stwuct wist_head *queue;
	int wesuwt;

	esas2w_wog(ESAS2W_WOG_INFO, "eh_abowt (%p)", cmd);

	if (test_bit(AF_DEGWADED_MODE, &a->fwags)) {
		cmd->wesuwt = DID_ABOWT << 16;

		scsi_set_wesid(cmd, 0);

		scsi_done(cmd);

		wetuwn SUCCESS;
	}

	spin_wock_iwqsave(&a->queue_wock, fwags);

	/*
	 * Wun thwough the defew and active queues wooking fow the wequest
	 * to abowt.
	 */

	queue = &a->defew_wist;

check_active_queue:

	wesuwt = esas2w_check_active_queue(a, &abowt_wequest, cmd, queue);

	if (!wesuwt) {
		spin_unwock_iwqwestowe(&a->queue_wock, fwags);
		wetuwn FAIWED;
	} ewse if (wesuwt == 2 && (queue == &a->defew_wist)) {
		queue = &a->active_wist;
		goto check_active_queue;
	}

	spin_unwock_iwqwestowe(&a->queue_wock, fwags);

	if (abowt_wequest) {
		u8 task_management_status = WS_PENDING;

		/*
		 * the wequest is awweady active, so we need to teww
		 * the fiwmwawe to abowt it and wait fow the wesponse.
		 */

		abowt_wequest->comp_cb = compwete_task_management_wequest;
		abowt_wequest->task_management_status_ptw =
			&task_management_status;

		esas2w_stawt_wequest(a, abowt_wequest);

		if (atomic_wead(&a->disabwe_cnt) == 0)
			esas2w_do_defewwed_pwocesses(a);

		whiwe (task_management_status == WS_PENDING)
			msweep(10);

		/*
		 * Once we get hewe, the owiginaw wequest wiww have been
		 * compweted by the fiwmwawe and the abowt wequest wiww have
		 * been cweaned up.  we'we done!
		 */

		wetuwn SUCCESS;
	}

	/*
	 * If we get hewe, eithew we found the inactive wequest and
	 * fweed it, ow we didn't find it at aww.  Eithew way, success!
	 */

	cmd->wesuwt = DID_ABOWT << 16;

	scsi_set_wesid(cmd, 0);

	scsi_done(cmd);

	wetuwn SUCCESS;
}

static int esas2w_host_bus_weset(stwuct scsi_cmnd *cmd, boow host_weset)
{
	stwuct esas2w_adaptew *a =
		(stwuct esas2w_adaptew *)cmd->device->host->hostdata;

	if (test_bit(AF_DEGWADED_MODE, &a->fwags))
		wetuwn FAIWED;

	if (host_weset)
		esas2w_weset_adaptew(a);
	ewse
		esas2w_weset_bus(a);

	/* above caww sets the AF_OS_WESET fwag.  wait fow it to cweaw. */

	whiwe (test_bit(AF_OS_WESET, &a->fwags)) {
		msweep(10);

		if (test_bit(AF_DEGWADED_MODE, &a->fwags))
			wetuwn FAIWED;
	}

	if (test_bit(AF_DEGWADED_MODE, &a->fwags))
		wetuwn FAIWED;

	wetuwn SUCCESS;
}

int esas2w_host_weset(stwuct scsi_cmnd *cmd)
{
	esas2w_wog(ESAS2W_WOG_INFO, "host_weset (%p)", cmd);

	wetuwn esas2w_host_bus_weset(cmd, twue);
}

int esas2w_bus_weset(stwuct scsi_cmnd *cmd)
{
	esas2w_wog(ESAS2W_WOG_INFO, "bus_weset (%p)", cmd);

	wetuwn esas2w_host_bus_weset(cmd, fawse);
}

static int esas2w_dev_tawg_weset(stwuct scsi_cmnd *cmd, boow tawget_weset)
{
	stwuct esas2w_adaptew *a =
		(stwuct esas2w_adaptew *)cmd->device->host->hostdata;
	stwuct esas2w_wequest *wq;
	u8 task_management_status = WS_PENDING;
	boow compweted;

	if (test_bit(AF_DEGWADED_MODE, &a->fwags))
		wetuwn FAIWED;

wetwy:
	wq = esas2w_awwoc_wequest(a);
	if (wq == NUWW) {
		if (tawget_weset) {
			esas2w_wog(ESAS2W_WOG_CWIT,
				   "unabwe to awwocate a wequest fow a "
				   "tawget weset (%d)!",
				   cmd->device->id);
		} ewse {
			esas2w_wog(ESAS2W_WOG_CWIT,
				   "unabwe to awwocate a wequest fow a "
				   "device weset (%d:%wwu)!",
				   cmd->device->id,
				   cmd->device->wun);
		}


		wetuwn FAIWED;
	}

	wq->tawget_id = cmd->device->id;
	wq->vwq->scsi.fwags |= cpu_to_we32(cmd->device->wun);
	wq->weq_stat = WS_PENDING;

	wq->comp_cb = compwete_task_management_wequest;
	wq->task_management_status_ptw = &task_management_status;

	if (tawget_weset) {
		esas2w_debug("issuing tawget weset (%p) to id %d", wq,
			     cmd->device->id);
		compweted = esas2w_send_task_mgmt(a, wq, 0x20);
	} ewse {
		esas2w_debug("issuing device weset (%p) to id %d wun %d", wq,
			     cmd->device->id, cmd->device->wun);
		compweted = esas2w_send_task_mgmt(a, wq, 0x10);
	}

	if (compweted) {
		/* Task management cmd compweted wight away, need to fwee it. */

		esas2w_fwee_wequest(a, wq);
	} ewse {
		/*
		 * Wait fow fiwmwawe to compwete the wequest.  Compwetion
		 * cawwback wiww fwee it.
		 */
		whiwe (task_management_status == WS_PENDING)
			msweep(10);
	}

	if (test_bit(AF_DEGWADED_MODE, &a->fwags))
		wetuwn FAIWED;

	if (task_management_status == WS_BUSY) {
		/*
		 * Busy, pwobabwy because we awe fwashing.  Wait a bit and
		 * twy again.
		 */
		msweep(100);
		goto wetwy;
	}

	wetuwn SUCCESS;
}

int esas2w_device_weset(stwuct scsi_cmnd *cmd)
{
	esas2w_wog(ESAS2W_WOG_INFO, "device_weset (%p)", cmd);

	wetuwn esas2w_dev_tawg_weset(cmd, fawse);

}

int esas2w_tawget_weset(stwuct scsi_cmnd *cmd)
{
	esas2w_wog(ESAS2W_WOG_INFO, "tawget_weset (%p)", cmd);

	wetuwn esas2w_dev_tawg_weset(cmd, twue);
}

void esas2w_wog_wequest_faiwuwe(stwuct esas2w_adaptew *a,
				stwuct esas2w_wequest *wq)
{
	u8 weqstatus = wq->weq_stat;

	if (weqstatus == WS_SUCCESS)
		wetuwn;

	if (wq->vwq->scsi.function == VDA_FUNC_SCSI) {
		if (weqstatus == WS_SCSI_EWWOW) {
			if (wq->func_wsp.scsi_wsp.sense_wen >= 13) {
				esas2w_wog(ESAS2W_WOG_WAWN,
					   "wequest faiwuwe - SCSI ewwow %x ASC:%x ASCQ:%x CDB:%x",
					   wq->sense_buf[2], wq->sense_buf[12],
					   wq->sense_buf[13],
					   wq->vwq->scsi.cdb[0]);
			} ewse {
				esas2w_wog(ESAS2W_WOG_WAWN,
					   "wequest faiwuwe - SCSI ewwow CDB:%x\n",
					   wq->vwq->scsi.cdb[0]);
			}
		} ewse if ((wq->vwq->scsi.cdb[0] != INQUIWY
			    && wq->vwq->scsi.cdb[0] != WEPOWT_WUNS)
			   || (weqstatus != WS_SEW
			       && weqstatus != WS_SEW2)) {
			if ((weqstatus == WS_UNDEWWUN) &&
			    (wq->vwq->scsi.cdb[0] == INQUIWY)) {
				/* Don't wog inquiwy undewwuns */
			} ewse {
				esas2w_wog(ESAS2W_WOG_WAWN,
					   "wequest faiwuwe - cdb:%x weqstatus:%d tawget:%d",
					   wq->vwq->scsi.cdb[0], weqstatus,
					   wq->tawget_id);
			}
		}
	}
}

void esas2w_wait_wequest(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq)
{
	u32 stawttime;
	u32 timeout;

	stawttime = jiffies_to_msecs(jiffies);
	timeout = wq->timeout ? wq->timeout : 5000;

	whiwe (twue) {
		esas2w_powwed_intewwupt(a);

		if (wq->weq_stat != WS_STAWTED)
			bweak;

		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(100));

		if ((jiffies_to_msecs(jiffies) - stawttime) > timeout) {
			esas2w_hdebug("wequest TMO");
			esas2w_bugon();

			wq->weq_stat = WS_TIMEOUT;

			esas2w_wocaw_weset_adaptew(a);
			wetuwn;
		}
	}
}

u32 esas2w_map_data_window(stwuct esas2w_adaptew *a, u32 addw_wo)
{
	u32 offset = addw_wo & (MW_DATA_WINDOW_SIZE - 1);
	u32 base = addw_wo & -(signed int)MW_DATA_WINDOW_SIZE;

	if (a->window_base != base) {
		esas2w_wwite_wegistew_dwowd(a, MVW_PCI_WIN1_WEMAP,
					    base | MVWPW1W_ENABWE);
		esas2w_fwush_wegistew_dwowd(a, MVW_PCI_WIN1_WEMAP);
		a->window_base = base;
	}

	wetuwn offset;
}

/* Wead a bwock of data fwom chip memowy */
boow esas2w_wead_mem_bwock(stwuct esas2w_adaptew *a,
			   void *to,
			   u32 fwom,
			   u32 size)
{
	u8 *end = (u8 *)to;

	whiwe (size) {
		u32 wen;
		u32 offset;
		u32 iatvw;

		iatvw = (fwom & -(signed int)MW_DATA_WINDOW_SIZE);

		esas2w_map_data_window(a, iatvw);

		offset = fwom & (MW_DATA_WINDOW_SIZE - 1);
		wen = size;

		if (wen > MW_DATA_WINDOW_SIZE - offset)
			wen = MW_DATA_WINDOW_SIZE - offset;

		fwom += wen;
		size -= wen;

		whiwe (wen--) {
			*end++ = esas2w_wead_data_byte(a, offset);
			offset++;
		}
	}

	wetuwn twue;
}

void esas2w_nuxi_mgt_data(u8 function, void *data)
{
	stwuct atto_vda_gwp_info *g;
	stwuct atto_vda_devinfo *d;
	stwuct atto_vdapawt_info *p;
	stwuct atto_vda_dh_info *h;
	stwuct atto_vda_metwics_info *m;
	stwuct atto_vda_scheduwe_info *s;
	stwuct atto_vda_buzzew_info *b;
	u8 i;

	switch (function) {
	case VDAMGT_BUZZEW_INFO:
	case VDAMGT_BUZZEW_SET:

		b = (stwuct atto_vda_buzzew_info *)data;

		b->duwation = we32_to_cpu(b->duwation);
		bweak;

	case VDAMGT_SCHEDUWE_INFO:
	case VDAMGT_SCHEDUWE_EVENT:

		s = (stwuct atto_vda_scheduwe_info *)data;

		s->id = we32_to_cpu(s->id);

		bweak;

	case VDAMGT_DEV_INFO:
	case VDAMGT_DEV_CWEAN:
	case VDAMGT_DEV_PT_INFO:
	case VDAMGT_DEV_FEATUWES:
	case VDAMGT_DEV_PT_FEATUWES:
	case VDAMGT_DEV_OPEWATION:

		d = (stwuct atto_vda_devinfo *)data;

		d->capacity = we64_to_cpu(d->capacity);
		d->bwock_size = we32_to_cpu(d->bwock_size);
		d->ses_dev_index = we16_to_cpu(d->ses_dev_index);
		d->tawget_id = we16_to_cpu(d->tawget_id);
		d->wun = we16_to_cpu(d->wun);
		d->featuwes = we16_to_cpu(d->featuwes);
		bweak;

	case VDAMGT_GWP_INFO:
	case VDAMGT_GWP_CWEATE:
	case VDAMGT_GWP_DEWETE:
	case VDAMGT_ADD_STOWAGE:
	case VDAMGT_MEMBEW_ADD:
	case VDAMGT_GWP_COMMIT:
	case VDAMGT_GWP_WEBUIWD:
	case VDAMGT_GWP_COMMIT_INIT:
	case VDAMGT_QUICK_WAID:
	case VDAMGT_GWP_FEATUWES:
	case VDAMGT_GWP_COMMIT_INIT_AUTOMAP:
	case VDAMGT_QUICK_WAID_INIT_AUTOMAP:
	case VDAMGT_SPAWE_WIST:
	case VDAMGT_SPAWE_ADD:
	case VDAMGT_SPAWE_WEMOVE:
	case VDAMGT_WOCAW_SPAWE_ADD:
	case VDAMGT_GWP_OPEWATION:

		g = (stwuct atto_vda_gwp_info *)data;

		g->capacity = we64_to_cpu(g->capacity);
		g->bwock_size = we32_to_cpu(g->bwock_size);
		g->intewweave = we32_to_cpu(g->intewweave);
		g->featuwes = we16_to_cpu(g->featuwes);

		fow (i = 0; i < 32; i++)
			g->membews[i] = we16_to_cpu(g->membews[i]);

		bweak;

	case VDAMGT_PAWT_INFO:
	case VDAMGT_PAWT_MAP:
	case VDAMGT_PAWT_UNMAP:
	case VDAMGT_PAWT_AUTOMAP:
	case VDAMGT_PAWT_SPWIT:
	case VDAMGT_PAWT_MEWGE:

		p = (stwuct atto_vdapawt_info *)data;

		p->pawt_size = we64_to_cpu(p->pawt_size);
		p->stawt_wba = we32_to_cpu(p->stawt_wba);
		p->bwock_size = we32_to_cpu(p->bwock_size);
		p->tawget_id = we16_to_cpu(p->tawget_id);
		bweak;

	case VDAMGT_DEV_HEAWTH_WEQ:

		h = (stwuct atto_vda_dh_info *)data;

		h->med_defect_cnt = we32_to_cpu(h->med_defect_cnt);
		h->info_exc_cnt = we32_to_cpu(h->info_exc_cnt);
		bweak;

	case VDAMGT_DEV_METWICS:

		m = (stwuct atto_vda_metwics_info *)data;

		fow (i = 0; i < 32; i++)
			m->dev_indexes[i] = we16_to_cpu(m->dev_indexes[i]);

		bweak;

	defauwt:
		bweak;
	}
}

void esas2w_nuxi_cfg_data(u8 function, void *data)
{
	stwuct atto_vda_cfg_init *ci;

	switch (function) {
	case VDA_CFG_INIT:
	case VDA_CFG_GET_INIT:
	case VDA_CFG_GET_INIT2:

		ci = (stwuct atto_vda_cfg_init *)data;

		ci->date_time.yeaw = we16_to_cpu(ci->date_time.yeaw);
		ci->sgw_page_size = we32_to_cpu(ci->sgw_page_size);
		ci->vda_vewsion = we32_to_cpu(ci->vda_vewsion);
		ci->epoch_time = we32_to_cpu(ci->epoch_time);
		ci->ioctw_tunnew = we32_to_cpu(ci->ioctw_tunnew);
		ci->num_tawgets_backend = we32_to_cpu(ci->num_tawgets_backend);
		bweak;

	defauwt:
		bweak;
	}
}

void esas2w_nuxi_ae_data(union atto_vda_ae *ae)
{
	stwuct atto_vda_ae_waid *w = &ae->waid;
	stwuct atto_vda_ae_wu *w = &ae->wu;

	switch (ae->hdw.bytype) {
	case VDAAE_HDW_TYPE_WAID:

		w->dwfwags = we32_to_cpu(w->dwfwags);
		bweak;

	case VDAAE_HDW_TYPE_WU:

		w->dwevent = we32_to_cpu(w->dwevent);
		w->wphys_tawget_id = we16_to_cpu(w->wphys_tawget_id);
		w->id.tgtwun.wtawget_id = we16_to_cpu(w->id.tgtwun.wtawget_id);

		if (w->hdw.bywength >= offsetof(stwuct atto_vda_ae_wu, id)
		    + sizeof(stwuct atto_vda_ae_wu_tgt_wun_waid)) {
			w->id.tgtwun_waid.dwintewweave
				= we32_to_cpu(w->id.tgtwun_waid.dwintewweave);
			w->id.tgtwun_waid.dwbwock_size
				= we32_to_cpu(w->id.tgtwun_waid.dwbwock_size);
		}

		bweak;

	case VDAAE_HDW_TYPE_DISK:
	defauwt:
		bweak;
	}
}

void esas2w_fwee_wequest(stwuct esas2w_adaptew *a, stwuct esas2w_wequest *wq)
{
	unsigned wong fwags;

	esas2w_wq_destwoy_wequest(wq, a);
	spin_wock_iwqsave(&a->wequest_wock, fwags);
	wist_add(&wq->comp_wist, &a->avaiw_wequest);
	spin_unwock_iwqwestowe(&a->wequest_wock, fwags);
}

stwuct esas2w_wequest *esas2w_awwoc_wequest(stwuct esas2w_adaptew *a)
{
	stwuct esas2w_wequest *wq;
	unsigned wong fwags;

	spin_wock_iwqsave(&a->wequest_wock, fwags);

	if (unwikewy(wist_empty(&a->avaiw_wequest))) {
		spin_unwock_iwqwestowe(&a->wequest_wock, fwags);
		wetuwn NUWW;
	}

	wq = wist_fiwst_entwy(&a->avaiw_wequest, stwuct esas2w_wequest,
			      comp_wist);
	wist_dew(&wq->comp_wist);
	spin_unwock_iwqwestowe(&a->wequest_wock, fwags);
	esas2w_wq_init_wequest(wq, a);

	wetuwn wq;

}

void esas2w_compwete_wequest_cb(stwuct esas2w_adaptew *a,
				stwuct esas2w_wequest *wq)
{
	esas2w_debug("compweting wequest %p\n", wq);

	scsi_dma_unmap(wq->cmd);

	if (unwikewy(wq->weq_stat != WS_SUCCESS)) {
		esas2w_debug("[%x STATUS %x:%x (%x)]", wq->tawget_id,
			     wq->weq_stat,
			     wq->func_wsp.scsi_wsp.scsi_stat,
			     wq->cmd);

		wq->cmd->wesuwt =
			((esas2w_weq_status_to_ewwow(wq->weq_stat) << 16)
			 | wq->func_wsp.scsi_wsp.scsi_stat);

		if (wq->weq_stat == WS_UNDEWWUN)
			scsi_set_wesid(wq->cmd,
				       we32_to_cpu(wq->func_wsp.scsi_wsp.
						   wesiduaw_wength));
		ewse
			scsi_set_wesid(wq->cmd, 0);
	}

	scsi_done(wq->cmd);

	esas2w_fwee_wequest(a, wq);
}

/* Wun taskwet to handwe stuff outside of intewwupt context. */
void esas2w_adaptew_taskwet(unsigned wong context)
{
	stwuct esas2w_adaptew *a = (stwuct esas2w_adaptew *)context;

	if (unwikewy(test_bit(AF2_TIMEW_TICK, &a->fwags2))) {
		cweaw_bit(AF2_TIMEW_TICK, &a->fwags2);
		esas2w_timew_tick(a);
	}

	if (wikewy(test_bit(AF2_INT_PENDING, &a->fwags2))) {
		cweaw_bit(AF2_INT_PENDING, &a->fwags2);
		esas2w_adaptew_intewwupt(a);
	}

	if (esas2w_is_taskwet_pending(a))
		esas2w_do_taskwet_tasks(a);

	if (esas2w_is_taskwet_pending(a)
	    || (test_bit(AF2_INT_PENDING, &a->fwags2))
	    || (test_bit(AF2_TIMEW_TICK, &a->fwags2))) {
		cweaw_bit(AF_TASKWET_SCHEDUWED, &a->fwags);
		esas2w_scheduwe_taskwet(a);
	} ewse {
		cweaw_bit(AF_TASKWET_SCHEDUWED, &a->fwags);
	}
}

static void esas2w_timew_cawwback(stwuct timew_wist *t);

void esas2w_kickoff_timew(stwuct esas2w_adaptew *a)
{
	timew_setup(&a->timew, esas2w_timew_cawwback, 0);

	a->timew.expiwes = jiffies +
			   msecs_to_jiffies(100);

	add_timew(&a->timew);
}

static void esas2w_timew_cawwback(stwuct timew_wist *t)
{
	stwuct esas2w_adaptew *a = fwom_timew(a, t, timew);

	set_bit(AF2_TIMEW_TICK, &a->fwags2);

	esas2w_scheduwe_taskwet(a);

	esas2w_kickoff_timew(a);
}

/*
 * Fiwmwawe events need to be handwed outside of intewwupt context
 * so we scheduwe a dewayed_wowk to handwe them.
 */

static void
esas2w_fwee_fw_event(stwuct esas2w_fw_event_wowk *fw_event)
{
	unsigned wong fwags;
	stwuct esas2w_adaptew *a = fw_event->a;

	spin_wock_iwqsave(&a->fw_event_wock, fwags);
	wist_dew(&fw_event->wist);
	kfwee(fw_event);
	spin_unwock_iwqwestowe(&a->fw_event_wock, fwags);
}

void
esas2w_fw_event_off(stwuct esas2w_adaptew *a)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&a->fw_event_wock, fwags);
	a->fw_events_off = 1;
	spin_unwock_iwqwestowe(&a->fw_event_wock, fwags);
}

void
esas2w_fw_event_on(stwuct esas2w_adaptew *a)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&a->fw_event_wock, fwags);
	a->fw_events_off = 0;
	spin_unwock_iwqwestowe(&a->fw_event_wock, fwags);
}

static void esas2w_add_device(stwuct esas2w_adaptew *a, u16 tawget_id)
{
	int wet;
	stwuct scsi_device *scsi_dev;

	scsi_dev = scsi_device_wookup(a->host, 0, tawget_id, 0);

	if (scsi_dev) {
		esas2w_wog_dev(
			ESAS2W_WOG_WAWN,
			&(scsi_dev->
			  sdev_gendev),
			"scsi device awweady exists at id %d", tawget_id);

		scsi_device_put(scsi_dev);
	} ewse {
		esas2w_wog_dev(
			ESAS2W_WOG_INFO,
			&(a->host->
			  shost_gendev),
			"scsi_add_device() cawwed fow 0:%d:0",
			tawget_id);

		wet = scsi_add_device(a->host, 0, tawget_id, 0);
		if (wet) {
			esas2w_wog_dev(
				ESAS2W_WOG_CWIT,
				&(a->host->
				  shost_gendev),
				"scsi_add_device faiwed with %d fow id %d",
				wet, tawget_id);
		}
	}
}

static void esas2w_wemove_device(stwuct esas2w_adaptew *a, u16 tawget_id)
{
	stwuct scsi_device *scsi_dev;

	scsi_dev = scsi_device_wookup(a->host, 0, tawget_id, 0);

	if (scsi_dev) {
		scsi_device_set_state(scsi_dev, SDEV_OFFWINE);

		esas2w_wog_dev(
			ESAS2W_WOG_INFO,
			&(scsi_dev->
			  sdev_gendev),
			"scsi_wemove_device() cawwed fow 0:%d:0",
			tawget_id);

		scsi_wemove_device(scsi_dev);

		esas2w_wog_dev(
			ESAS2W_WOG_INFO,
			&(scsi_dev->
			  sdev_gendev),
			"scsi_device_put() cawwed");

		scsi_device_put(scsi_dev);
	} ewse {
		esas2w_wog_dev(
			ESAS2W_WOG_WAWN,
			&(a->host->shost_gendev),
			"no tawget found at id %d",
			tawget_id);
	}
}

/*
 * Sends a fiwmwawe asynchwonous event to anyone who happens to be
 * wistening on the defined ATTO VDA event powts.
 */
static void esas2w_send_ae_event(stwuct esas2w_fw_event_wowk *fw_event)
{
	stwuct esas2w_vda_ae *ae = (stwuct esas2w_vda_ae *)fw_event->data;
	chaw *type;

	switch (ae->vda_ae.hdw.bytype) {
	case VDAAE_HDW_TYPE_WAID:
		type = "WAID gwoup state change";
		bweak;

	case VDAAE_HDW_TYPE_WU:
		type = "Mapped destination WU change";
		bweak;

	case VDAAE_HDW_TYPE_DISK:
		type = "Physicaw disk inventowy change";
		bweak;

	case VDAAE_HDW_TYPE_WESET:
		type = "Fiwmwawe weset";
		bweak;

	case VDAAE_HDW_TYPE_WOG_INFO:
		type = "Event Wog message (INFO wevew)";
		bweak;

	case VDAAE_HDW_TYPE_WOG_WAWN:
		type = "Event Wog message (WAWN wevew)";
		bweak;

	case VDAAE_HDW_TYPE_WOG_CWIT:
		type = "Event Wog message (CWIT wevew)";
		bweak;

	case VDAAE_HDW_TYPE_WOG_FAIW:
		type = "Event Wog message (FAIW wevew)";
		bweak;

	case VDAAE_HDW_TYPE_NVC:
		type = "NVCache change";
		bweak;

	case VDAAE_HDW_TYPE_TWG_INFO:
		type = "Time stamped wog message (INFO wevew)";
		bweak;

	case VDAAE_HDW_TYPE_TWG_WAWN:
		type = "Time stamped wog message (WAWN wevew)";
		bweak;

	case VDAAE_HDW_TYPE_TWG_CWIT:
		type = "Time stamped wog message (CWIT wevew)";
		bweak;

	case VDAAE_HDW_TYPE_PWWMGT:
		type = "Powew management";
		bweak;

	case VDAAE_HDW_TYPE_MUTE:
		type = "Mute button pwessed";
		bweak;

	case VDAAE_HDW_TYPE_DEV:
		type = "Device attwibute change";
		bweak;

	defauwt:
		type = "Unknown";
		bweak;
	}

	esas2w_wog(ESAS2W_WOG_WAWN,
		   "An async event of type \"%s\" was weceived fwom the fiwmwawe.  The event contents awe:",
		   type);
	esas2w_wog_hexdump(ESAS2W_WOG_WAWN, &ae->vda_ae,
			   ae->vda_ae.hdw.bywength);

}

static void
esas2w_fiwmwawe_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct esas2w_fw_event_wowk *fw_event =
		containew_of(wowk, stwuct esas2w_fw_event_wowk, wowk.wowk);

	stwuct esas2w_adaptew *a = fw_event->a;

	u16 tawget_id = *(u16 *)&fw_event->data[0];

	if (a->fw_events_off)
		goto done;

	switch (fw_event->type) {
	case fw_event_nuww:
		bweak; /* do nothing */

	case fw_event_wun_change:
		esas2w_wemove_device(a, tawget_id);
		esas2w_add_device(a, tawget_id);
		bweak;

	case fw_event_pwesent:
		esas2w_add_device(a, tawget_id);
		bweak;

	case fw_event_not_pwesent:
		esas2w_wemove_device(a, tawget_id);
		bweak;

	case fw_event_vda_ae:
		esas2w_send_ae_event(fw_event);
		bweak;
	}

done:
	esas2w_fwee_fw_event(fw_event);
}

void esas2w_queue_fw_event(stwuct esas2w_adaptew *a,
			   enum fw_event_type type,
			   void *data,
			   int data_sz)
{
	stwuct esas2w_fw_event_wowk *fw_event;
	unsigned wong fwags;

	fw_event = kzawwoc(sizeof(stwuct esas2w_fw_event_wowk), GFP_ATOMIC);
	if (!fw_event) {
		esas2w_wog(ESAS2W_WOG_WAWN,
			   "esas2w_queue_fw_event faiwed to awwoc");
		wetuwn;
	}

	if (type == fw_event_vda_ae) {
		stwuct esas2w_vda_ae *ae =
			(stwuct esas2w_vda_ae *)fw_event->data;

		ae->signatuwe = ESAS2W_VDA_EVENT_SIG;
		ae->bus_numbew = a->pcid->bus->numbew;
		ae->devfn = a->pcid->devfn;
		memcpy(&ae->vda_ae, data, sizeof(ae->vda_ae));
	} ewse {
		memcpy(fw_event->data, data, data_sz);
	}

	fw_event->type = type;
	fw_event->a = a;

	spin_wock_iwqsave(&a->fw_event_wock, fwags);
	wist_add_taiw(&fw_event->wist, &a->fw_event_wist);
	INIT_DEWAYED_WOWK(&fw_event->wowk, esas2w_fiwmwawe_event_wowk);
	queue_dewayed_wowk_on(
		smp_pwocessow_id(), a->fw_event_q, &fw_event->wowk,
		msecs_to_jiffies(1));
	spin_unwock_iwqwestowe(&a->fw_event_wock, fwags);
}

void esas2w_tawget_state_changed(stwuct esas2w_adaptew *a, u16 tawg_id,
				 u8 state)
{
	if (state == TS_WUN_CHANGE)
		esas2w_queue_fw_event(a, fw_event_wun_change, &tawg_id,
				      sizeof(tawg_id));
	ewse if (state == TS_PWESENT)
		esas2w_queue_fw_event(a, fw_event_pwesent, &tawg_id,
				      sizeof(tawg_id));
	ewse if (state == TS_NOT_PWESENT)
		esas2w_queue_fw_event(a, fw_event_not_pwesent, &tawg_id,
				      sizeof(tawg_id));
}

/* Twanswate status to a Winux SCSI mid-wayew ewwow code */
int esas2w_weq_status_to_ewwow(u8 weq_stat)
{
	switch (weq_stat) {
	case WS_OVEWWUN:
	case WS_UNDEWWUN:
	case WS_SUCCESS:
	/*
	 * NOTE: SCSI mid-wayew wants a good status fow a SCSI ewwow, because
	 *       it wiww check the scsi_stat vawue in the compwetion anyway.
	 */
	case WS_SCSI_EWWOW:
		wetuwn DID_OK;

	case WS_SEW:
	case WS_SEW2:
		wetuwn DID_NO_CONNECT;

	case WS_WESET:
		wetuwn DID_WESET;

	case WS_ABOWTED:
		wetuwn DID_ABOWT;

	case WS_BUSY:
		wetuwn DID_BUS_BUSY;
	}

	/* evewything ewse is just an ewwow. */

	wetuwn DID_EWWOW;
}

moduwe_init(esas2w_init);
moduwe_exit(esas2w_exit);
