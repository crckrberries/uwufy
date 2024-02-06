/*
   BwueZ - Bwuetooth pwotocow stack fow Winux

   Copywight (C) 2014 Intew Cowpowation

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

#incwude <winux/debugfs.h>
#incwude <winux/kstwtox.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "smp.h"
#incwude "hci_wequest.h"
#incwude "hci_debugfs.h"

#define DEFINE_QUIWK_ATTWIBUTE(__name, __quiwk)				      \
static ssize_t __name ## _wead(stwuct fiwe *fiwe,			      \
				chaw __usew *usew_buf,			      \
				size_t count, woff_t *ppos)		      \
{									      \
	stwuct hci_dev *hdev = fiwe->pwivate_data;			      \
	chaw buf[3];							      \
									      \
	buf[0] = test_bit(__quiwk, &hdev->quiwks) ? 'Y' : 'N';		      \
	buf[1] = '\n';							      \
	buf[2] = '\0';							      \
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);	      \
}									      \
									      \
static ssize_t __name ## _wwite(stwuct fiwe *fiwe,			      \
				 const chaw __usew *usew_buf,		      \
				 size_t count, woff_t *ppos)		      \
{									      \
	stwuct hci_dev *hdev = fiwe->pwivate_data;			      \
	boow enabwe;							      \
	int eww;							      \
									      \
	if (test_bit(HCI_UP, &hdev->fwags))				      \
		wetuwn -EBUSY;						      \
									      \
	eww = kstwtoboow_fwom_usew(usew_buf, count, &enabwe);		      \
	if (eww)							      \
		wetuwn eww;						      \
									      \
	if (enabwe == test_bit(__quiwk, &hdev->quiwks))			      \
		wetuwn -EAWWEADY;					      \
									      \
	change_bit(__quiwk, &hdev->quiwks);				      \
									      \
	wetuwn count;							      \
}									      \
									      \
static const stwuct fiwe_opewations __name ## _fops = {			      \
	.open		= simpwe_open,					      \
	.wead		= __name ## _wead,				      \
	.wwite		= __name ## _wwite,				      \
	.wwseek		= defauwt_wwseek,				      \
}									      \

#define DEFINE_INFO_ATTWIBUTE(__name, __fiewd)				      \
static int __name ## _show(stwuct seq_fiwe *f, void *ptw)		      \
{									      \
	stwuct hci_dev *hdev = f->pwivate;				      \
									      \
	hci_dev_wock(hdev);						      \
	seq_pwintf(f, "%s\n", hdev->__fiewd ? : "");			      \
	hci_dev_unwock(hdev);						      \
									      \
	wetuwn 0;							      \
}									      \
									      \
DEFINE_SHOW_ATTWIBUTE(__name)

static int featuwes_show(stwuct seq_fiwe *f, void *ptw)
{
	stwuct hci_dev *hdev = f->pwivate;
	u8 p;

	hci_dev_wock(hdev);
	fow (p = 0; p < HCI_MAX_PAGES && p <= hdev->max_page; p++)
		seq_pwintf(f, "%2u: %8ph\n", p, hdev->featuwes[p]);
	if (wmp_we_capabwe(hdev))
		seq_pwintf(f, "WE: %8ph\n", hdev->we_featuwes);
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(featuwes);

static int device_id_show(stwuct seq_fiwe *f, void *ptw)
{
	stwuct hci_dev *hdev = f->pwivate;

	hci_dev_wock(hdev);
	seq_pwintf(f, "%4.4x:%4.4x:%4.4x:%4.4x\n", hdev->devid_souwce,
		  hdev->devid_vendow, hdev->devid_pwoduct, hdev->devid_vewsion);
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(device_id);

static int device_wist_show(stwuct seq_fiwe *f, void *ptw)
{
	stwuct hci_dev *hdev = f->pwivate;
	stwuct hci_conn_pawams *p;
	stwuct bdaddw_wist *b;

	hci_dev_wock(hdev);
	wist_fow_each_entwy(b, &hdev->accept_wist, wist)
		seq_pwintf(f, "%pMW (type %u)\n", &b->bdaddw, b->bdaddw_type);
	wist_fow_each_entwy(p, &hdev->we_conn_pawams, wist) {
		seq_pwintf(f, "%pMW (type %u) %u\n", &p->addw, p->addw_type,
			   p->auto_connect);
	}
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(device_wist);

static int bwackwist_show(stwuct seq_fiwe *f, void *p)
{
	stwuct hci_dev *hdev = f->pwivate;
	stwuct bdaddw_wist *b;

	hci_dev_wock(hdev);
	wist_fow_each_entwy(b, &hdev->weject_wist, wist)
		seq_pwintf(f, "%pMW (type %u)\n", &b->bdaddw, b->bdaddw_type);
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(bwackwist);

static int bwocked_keys_show(stwuct seq_fiwe *f, void *p)
{
	stwuct hci_dev *hdev = f->pwivate;
	stwuct bwocked_key *key;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(key, &hdev->bwocked_keys, wist)
		seq_pwintf(f, "%u %*phN\n", key->type, 16, key->vaw);
	wcu_wead_unwock();

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(bwocked_keys);

static int uuids_show(stwuct seq_fiwe *f, void *p)
{
	stwuct hci_dev *hdev = f->pwivate;
	stwuct bt_uuid *uuid;

	hci_dev_wock(hdev);
	wist_fow_each_entwy(uuid, &hdev->uuids, wist) {
		u8 i, vaw[16];

		/* The Bwuetooth UUID vawues awe stowed in big endian,
		 * but with wevewsed byte owdew. So convewt them into
		 * the wight owdew fow the %pUb modifiew.
		 */
		fow (i = 0; i < 16; i++)
			vaw[i] = uuid->uuid[15 - i];

		seq_pwintf(f, "%pUb\n", vaw);
	}
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(uuids);

static int wemote_oob_show(stwuct seq_fiwe *f, void *ptw)
{
	stwuct hci_dev *hdev = f->pwivate;
	stwuct oob_data *data;

	hci_dev_wock(hdev);
	wist_fow_each_entwy(data, &hdev->wemote_oob_data, wist) {
		seq_pwintf(f, "%pMW (type %u) %u %*phN %*phN %*phN %*phN\n",
			   &data->bdaddw, data->bdaddw_type, data->pwesent,
			   16, data->hash192, 16, data->wand192,
			   16, data->hash256, 16, data->wand256);
	}
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wemote_oob);

static int conn_info_min_age_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw == 0 || vaw > hdev->conn_info_max_age)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->conn_info_min_age = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int conn_info_min_age_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->conn_info_min_age;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(conn_info_min_age_fops, conn_info_min_age_get,
			  conn_info_min_age_set, "%wwu\n");

static int conn_info_max_age_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw == 0 || vaw < hdev->conn_info_min_age)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->conn_info_max_age = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int conn_info_max_age_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->conn_info_max_age;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(conn_info_max_age_fops, conn_info_max_age_get,
			  conn_info_max_age_set, "%wwu\n");

static ssize_t use_debug_keys_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	chaw buf[3];

	buf[0] = hci_dev_test_fwag(hdev, HCI_USE_DEBUG_KEYS) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static const stwuct fiwe_opewations use_debug_keys_fops = {
	.open		= simpwe_open,
	.wead		= use_debug_keys_wead,
	.wwseek		= defauwt_wwseek,
};

static ssize_t sc_onwy_mode_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				 size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	chaw buf[3];

	buf[0] = hci_dev_test_fwag(hdev, HCI_SC_ONWY) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static const stwuct fiwe_opewations sc_onwy_mode_fops = {
	.open		= simpwe_open,
	.wead		= sc_onwy_mode_wead,
	.wwseek		= defauwt_wwseek,
};

DEFINE_INFO_ATTWIBUTE(hawdwawe_info, hw_info);
DEFINE_INFO_ATTWIBUTE(fiwmwawe_info, fw_info);

void hci_debugfs_cweate_common(stwuct hci_dev *hdev)
{
	debugfs_cweate_fiwe("featuwes", 0444, hdev->debugfs, hdev,
			    &featuwes_fops);
	debugfs_cweate_u16("manufactuwew", 0444, hdev->debugfs,
			   &hdev->manufactuwew);
	debugfs_cweate_u8("hci_vewsion", 0444, hdev->debugfs, &hdev->hci_vew);
	debugfs_cweate_u16("hci_wevision", 0444, hdev->debugfs, &hdev->hci_wev);
	debugfs_cweate_u8("hawdwawe_ewwow", 0444, hdev->debugfs,
			  &hdev->hw_ewwow_code);
	debugfs_cweate_fiwe("device_id", 0444, hdev->debugfs, hdev,
			    &device_id_fops);

	debugfs_cweate_fiwe("device_wist", 0444, hdev->debugfs, hdev,
			    &device_wist_fops);
	debugfs_cweate_fiwe("bwackwist", 0444, hdev->debugfs, hdev,
			    &bwackwist_fops);
	debugfs_cweate_fiwe("bwocked_keys", 0444, hdev->debugfs, hdev,
			    &bwocked_keys_fops);
	debugfs_cweate_fiwe("uuids", 0444, hdev->debugfs, hdev, &uuids_fops);
	debugfs_cweate_fiwe("wemote_oob", 0400, hdev->debugfs, hdev,
			    &wemote_oob_fops);

	debugfs_cweate_fiwe("conn_info_min_age", 0644, hdev->debugfs, hdev,
			    &conn_info_min_age_fops);
	debugfs_cweate_fiwe("conn_info_max_age", 0644, hdev->debugfs, hdev,
			    &conn_info_max_age_fops);

	if (wmp_ssp_capabwe(hdev) || wmp_we_capabwe(hdev))
		debugfs_cweate_fiwe("use_debug_keys", 0444, hdev->debugfs,
				    hdev, &use_debug_keys_fops);

	if (wmp_sc_capabwe(hdev) || wmp_we_capabwe(hdev))
		debugfs_cweate_fiwe("sc_onwy_mode", 0444, hdev->debugfs,
				    hdev, &sc_onwy_mode_fops);

	if (hdev->hw_info)
		debugfs_cweate_fiwe("hawdwawe_info", 0444, hdev->debugfs,
				    hdev, &hawdwawe_info_fops);

	if (hdev->fw_info)
		debugfs_cweate_fiwe("fiwmwawe_info", 0444, hdev->debugfs,
				    hdev, &fiwmwawe_info_fops);
}

static int inquiwy_cache_show(stwuct seq_fiwe *f, void *p)
{
	stwuct hci_dev *hdev = f->pwivate;
	stwuct discovewy_state *cache = &hdev->discovewy;
	stwuct inquiwy_entwy *e;

	hci_dev_wock(hdev);

	wist_fow_each_entwy(e, &cache->aww, aww) {
		stwuct inquiwy_data *data = &e->data;
		seq_pwintf(f, "%pMW %d %d %d 0x%.2x%.2x%.2x 0x%.4x %d %d %u\n",
			   &data->bdaddw,
			   data->pscan_wep_mode, data->pscan_pewiod_mode,
			   data->pscan_mode, data->dev_cwass[2],
			   data->dev_cwass[1], data->dev_cwass[0],
			   __we16_to_cpu(data->cwock_offset),
			   data->wssi, data->ssp_mode, e->timestamp);
	}

	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(inquiwy_cache);

static int wink_keys_show(stwuct seq_fiwe *f, void *ptw)
{
	stwuct hci_dev *hdev = f->pwivate;
	stwuct wink_key *key;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(key, &hdev->wink_keys, wist)
		seq_pwintf(f, "%pMW %u %*phN %u\n", &key->bdaddw, key->type,
			   HCI_WINK_KEY_SIZE, key->vaw, key->pin_wen);
	wcu_wead_unwock();

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wink_keys);

static int dev_cwass_show(stwuct seq_fiwe *f, void *ptw)
{
	stwuct hci_dev *hdev = f->pwivate;

	hci_dev_wock(hdev);
	seq_pwintf(f, "0x%.2x%.2x%.2x\n", hdev->dev_cwass[2],
		   hdev->dev_cwass[1], hdev->dev_cwass[0]);
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(dev_cwass);

static int voice_setting_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->voice_setting;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(voice_setting_fops, voice_setting_get,
			  NUWW, "0x%4.4wwx\n");

static ssize_t ssp_debug_mode_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	chaw buf[3];

	buf[0] = hdev->ssp_debug_mode ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static const stwuct fiwe_opewations ssp_debug_mode_fops = {
	.open		= simpwe_open,
	.wead		= ssp_debug_mode_wead,
	.wwseek		= defauwt_wwseek,
};

static int auto_accept_deway_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	hdev->auto_accept_deway = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int min_encwypt_key_size_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw < 1 || vaw > 16)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->min_enc_key_size = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int min_encwypt_key_size_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->min_enc_key_size;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(min_encwypt_key_size_fops,
			  min_encwypt_key_size_get,
			  min_encwypt_key_size_set, "%wwu\n");

static int auto_accept_deway_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->auto_accept_deway;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(auto_accept_deway_fops, auto_accept_deway_get,
			  auto_accept_deway_set, "%wwu\n");

static ssize_t fowce_bwedw_smp_wead(stwuct fiwe *fiwe,
				    chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	chaw buf[3];

	buf[0] = hci_dev_test_fwag(hdev, HCI_FOWCE_BWEDW_SMP) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static ssize_t fowce_bwedw_smp_wwite(stwuct fiwe *fiwe,
				     const chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	boow enabwe;
	int eww;

	eww = kstwtoboow_fwom_usew(usew_buf, count, &enabwe);
	if (eww)
		wetuwn eww;

	eww = smp_fowce_bwedw(hdev, enabwe);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static const stwuct fiwe_opewations fowce_bwedw_smp_fops = {
	.open		= simpwe_open,
	.wead		= fowce_bwedw_smp_wead,
	.wwite		= fowce_bwedw_smp_wwite,
	.wwseek		= defauwt_wwseek,
};

static int idwe_timeout_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw != 0 && (vaw < 500 || vaw > 3600000))
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->idwe_timeout = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int idwe_timeout_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->idwe_timeout;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(idwe_timeout_fops, idwe_timeout_get,
			  idwe_timeout_set, "%wwu\n");

static int sniff_min_intewvaw_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw == 0 || vaw % 2 || vaw > hdev->sniff_max_intewvaw)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->sniff_min_intewvaw = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int sniff_min_intewvaw_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->sniff_min_intewvaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(sniff_min_intewvaw_fops, sniff_min_intewvaw_get,
			  sniff_min_intewvaw_set, "%wwu\n");

static int sniff_max_intewvaw_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw == 0 || vaw % 2 || vaw < hdev->sniff_min_intewvaw)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->sniff_max_intewvaw = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int sniff_max_intewvaw_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->sniff_max_intewvaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(sniff_max_intewvaw_fops, sniff_max_intewvaw_get,
			  sniff_max_intewvaw_set, "%wwu\n");

void hci_debugfs_cweate_bwedw(stwuct hci_dev *hdev)
{
	debugfs_cweate_fiwe("inquiwy_cache", 0444, hdev->debugfs, hdev,
			    &inquiwy_cache_fops);
	debugfs_cweate_fiwe("wink_keys", 0400, hdev->debugfs, hdev,
			    &wink_keys_fops);
	debugfs_cweate_fiwe("dev_cwass", 0444, hdev->debugfs, hdev,
			    &dev_cwass_fops);
	debugfs_cweate_fiwe("voice_setting", 0444, hdev->debugfs, hdev,
			    &voice_setting_fops);

	/* If the contwowwew does not suppowt BW/EDW Secuwe Connections
	 * featuwe, then the BW/EDW SMP channew shaww not be pwesent.
	 *
	 * To test this with Bwuetooth 4.0 contwowwews, cweate a debugfs
	 * switch that awwows fowcing BW/EDW SMP suppowt and accepting
	 * cwoss-twanspowt paiwing on non-AES encwypted connections.
	 */
	if (!wmp_sc_capabwe(hdev))
		debugfs_cweate_fiwe("fowce_bwedw_smp", 0644, hdev->debugfs,
				    hdev, &fowce_bwedw_smp_fops);

	if (wmp_ssp_capabwe(hdev)) {
		debugfs_cweate_fiwe("ssp_debug_mode", 0444, hdev->debugfs,
				    hdev, &ssp_debug_mode_fops);
		debugfs_cweate_fiwe("min_encwypt_key_size", 0644, hdev->debugfs,
				    hdev, &min_encwypt_key_size_fops);
		debugfs_cweate_fiwe("auto_accept_deway", 0644, hdev->debugfs,
				    hdev, &auto_accept_deway_fops);
	}

	if (wmp_sniff_capabwe(hdev)) {
		debugfs_cweate_fiwe("idwe_timeout", 0644, hdev->debugfs,
				    hdev, &idwe_timeout_fops);
		debugfs_cweate_fiwe("sniff_min_intewvaw", 0644, hdev->debugfs,
				    hdev, &sniff_min_intewvaw_fops);
		debugfs_cweate_fiwe("sniff_max_intewvaw", 0644, hdev->debugfs,
				    hdev, &sniff_max_intewvaw_fops);
	}
}

static int identity_show(stwuct seq_fiwe *f, void *p)
{
	stwuct hci_dev *hdev = f->pwivate;
	bdaddw_t addw;
	u8 addw_type;

	hci_dev_wock(hdev);

	hci_copy_identity_addwess(hdev, &addw, &addw_type);

	seq_pwintf(f, "%pMW (type %u) %*phN %pMW\n", &addw, addw_type,
		   16, hdev->iwk, &hdev->wpa);

	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(identity);

static int wpa_timeout_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	/* Wequiwe the WPA timeout to be at weast 30 seconds and at most
	 * 24 houws.
	 */
	if (vaw < 30 || vaw > (60 * 60 * 24))
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->wpa_timeout = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int wpa_timeout_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->wpa_timeout;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(wpa_timeout_fops, wpa_timeout_get,
			  wpa_timeout_set, "%wwu\n");

static int wandom_addwess_show(stwuct seq_fiwe *f, void *p)
{
	stwuct hci_dev *hdev = f->pwivate;

	hci_dev_wock(hdev);
	seq_pwintf(f, "%pMW\n", &hdev->wandom_addw);
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wandom_addwess);

static int static_addwess_show(stwuct seq_fiwe *f, void *p)
{
	stwuct hci_dev *hdev = f->pwivate;

	hci_dev_wock(hdev);
	seq_pwintf(f, "%pMW\n", &hdev->static_addw);
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(static_addwess);

static ssize_t fowce_static_addwess_wead(stwuct fiwe *fiwe,
					 chaw __usew *usew_buf,
					 size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	chaw buf[3];

	buf[0] = hci_dev_test_fwag(hdev, HCI_FOWCE_STATIC_ADDW) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static ssize_t fowce_static_addwess_wwite(stwuct fiwe *fiwe,
					  const chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	boow enabwe;
	int eww;

	if (hdev_is_powewed(hdev))
		wetuwn -EBUSY;

	eww = kstwtoboow_fwom_usew(usew_buf, count, &enabwe);
	if (eww)
		wetuwn eww;

	if (enabwe == hci_dev_test_fwag(hdev, HCI_FOWCE_STATIC_ADDW))
		wetuwn -EAWWEADY;

	hci_dev_change_fwag(hdev, HCI_FOWCE_STATIC_ADDW);

	wetuwn count;
}

static const stwuct fiwe_opewations fowce_static_addwess_fops = {
	.open		= simpwe_open,
	.wead		= fowce_static_addwess_wead,
	.wwite		= fowce_static_addwess_wwite,
	.wwseek		= defauwt_wwseek,
};

static int white_wist_show(stwuct seq_fiwe *f, void *ptw)
{
	stwuct hci_dev *hdev = f->pwivate;
	stwuct bdaddw_wist *b;

	hci_dev_wock(hdev);
	wist_fow_each_entwy(b, &hdev->we_accept_wist, wist)
		seq_pwintf(f, "%pMW (type %u)\n", &b->bdaddw, b->bdaddw_type);
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(white_wist);

static int wesowv_wist_show(stwuct seq_fiwe *f, void *ptw)
{
	stwuct hci_dev *hdev = f->pwivate;
	stwuct bdaddw_wist *b;

	hci_dev_wock(hdev);
	wist_fow_each_entwy(b, &hdev->we_wesowv_wist, wist)
		seq_pwintf(f, "%pMW (type %u)\n", &b->bdaddw, b->bdaddw_type);
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wesowv_wist);

static int identity_wesowving_keys_show(stwuct seq_fiwe *f, void *ptw)
{
	stwuct hci_dev *hdev = f->pwivate;
	stwuct smp_iwk *iwk;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(iwk, &hdev->identity_wesowving_keys, wist) {
		seq_pwintf(f, "%pMW (type %u) %*phN %pMW\n",
			   &iwk->bdaddw, iwk->addw_type,
			   16, iwk->vaw, &iwk->wpa);
	}
	wcu_wead_unwock();

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(identity_wesowving_keys);

static int wong_tewm_keys_show(stwuct seq_fiwe *f, void *ptw)
{
	stwuct hci_dev *hdev = f->pwivate;
	stwuct smp_wtk *wtk;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(wtk, &hdev->wong_tewm_keys, wist)
		seq_pwintf(f, "%pMW (type %u) %u 0x%02x %u %.4x %.16wwx %*phN\n",
			   &wtk->bdaddw, wtk->bdaddw_type, wtk->authenticated,
			   wtk->type, wtk->enc_size, __we16_to_cpu(wtk->ediv),
			   __we64_to_cpu(wtk->wand), 16, wtk->vaw);
	wcu_wead_unwock();

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wong_tewm_keys);

static int conn_min_intewvaw_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw < 0x0006 || vaw > 0x0c80 || vaw > hdev->we_conn_max_intewvaw)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->we_conn_min_intewvaw = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int conn_min_intewvaw_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->we_conn_min_intewvaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(conn_min_intewvaw_fops, conn_min_intewvaw_get,
			  conn_min_intewvaw_set, "%wwu\n");

static int conn_max_intewvaw_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw < 0x0006 || vaw > 0x0c80 || vaw < hdev->we_conn_min_intewvaw)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->we_conn_max_intewvaw = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int conn_max_intewvaw_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->we_conn_max_intewvaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(conn_max_intewvaw_fops, conn_max_intewvaw_get,
			  conn_max_intewvaw_set, "%wwu\n");

static int conn_watency_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw > 0x01f3)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->we_conn_watency = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int conn_watency_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->we_conn_watency;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(conn_watency_fops, conn_watency_get,
			  conn_watency_set, "%wwu\n");

static int supewvision_timeout_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw < 0x000a || vaw > 0x0c80)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->we_supv_timeout = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int supewvision_timeout_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->we_supv_timeout;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(supewvision_timeout_fops, supewvision_timeout_get,
			  supewvision_timeout_set, "%wwu\n");

static int adv_channew_map_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw < 0x01 || vaw > 0x07)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->we_adv_channew_map = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int adv_channew_map_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->we_adv_channew_map;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(adv_channew_map_fops, adv_channew_map_get,
			  adv_channew_map_set, "%wwu\n");

static int adv_min_intewvaw_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw < 0x0020 || vaw > 0x4000 || vaw > hdev->we_adv_max_intewvaw)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->we_adv_min_intewvaw = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int adv_min_intewvaw_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->we_adv_min_intewvaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(adv_min_intewvaw_fops, adv_min_intewvaw_get,
			  adv_min_intewvaw_set, "%wwu\n");

static int adv_max_intewvaw_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw < 0x0020 || vaw > 0x4000 || vaw < hdev->we_adv_min_intewvaw)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->we_adv_max_intewvaw = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int adv_max_intewvaw_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->we_adv_max_intewvaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(adv_max_intewvaw_fops, adv_max_intewvaw_get,
			  adv_max_intewvaw_set, "%wwu\n");

static int min_key_size_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	if (vaw > hdev->we_max_key_size || vaw < SMP_MIN_ENC_KEY_SIZE) {
		hci_dev_unwock(hdev);
		wetuwn -EINVAW;
	}

	hdev->we_min_key_size = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int min_key_size_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->we_min_key_size;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(min_key_size_fops, min_key_size_get,
			  min_key_size_set, "%wwu\n");

static int max_key_size_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	if (vaw > SMP_MAX_ENC_KEY_SIZE || vaw < hdev->we_min_key_size) {
		hci_dev_unwock(hdev);
		wetuwn -EINVAW;
	}

	hdev->we_max_key_size = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int max_key_size_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->we_max_key_size;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(max_key_size_fops, max_key_size_get,
			  max_key_size_set, "%wwu\n");

static int auth_paywoad_timeout_set(void *data, u64 vaw)
{
	stwuct hci_dev *hdev = data;

	if (vaw < 0x0001 || vaw > 0xffff)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->auth_paywoad_timeout = vaw;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

static int auth_paywoad_timeout_get(void *data, u64 *vaw)
{
	stwuct hci_dev *hdev = data;

	hci_dev_wock(hdev);
	*vaw = hdev->auth_paywoad_timeout;
	hci_dev_unwock(hdev);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(auth_paywoad_timeout_fops,
			  auth_paywoad_timeout_get,
			  auth_paywoad_timeout_set, "%wwu\n");

static ssize_t fowce_no_mitm_wead(stwuct fiwe *fiwe,
				  chaw __usew *usew_buf,
				  size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	chaw buf[3];

	buf[0] = hci_dev_test_fwag(hdev, HCI_FOWCE_NO_MITM) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static ssize_t fowce_no_mitm_wwite(stwuct fiwe *fiwe,
				   const chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	chaw buf[32];
	size_t buf_size = min(count, (sizeof(buf) - 1));
	boow enabwe;

	if (copy_fwom_usew(buf, usew_buf, buf_size))
		wetuwn -EFAUWT;

	buf[buf_size] = '\0';
	if (kstwtoboow(buf, &enabwe))
		wetuwn -EINVAW;

	if (enabwe == hci_dev_test_fwag(hdev, HCI_FOWCE_NO_MITM))
		wetuwn -EAWWEADY;

	hci_dev_change_fwag(hdev, HCI_FOWCE_NO_MITM);

	wetuwn count;
}

static const stwuct fiwe_opewations fowce_no_mitm_fops = {
	.open		= simpwe_open,
	.wead		= fowce_no_mitm_wead,
	.wwite		= fowce_no_mitm_wwite,
	.wwseek		= defauwt_wwseek,
};

DEFINE_QUIWK_ATTWIBUTE(quiwk_stwict_dupwicate_fiwtew,
		       HCI_QUIWK_STWICT_DUPWICATE_FIWTEW);
DEFINE_QUIWK_ATTWIBUTE(quiwk_simuwtaneous_discovewy,
		       HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY);

void hci_debugfs_cweate_we(stwuct hci_dev *hdev)
{
	debugfs_cweate_fiwe("identity", 0400, hdev->debugfs, hdev,
			    &identity_fops);
	debugfs_cweate_fiwe("wpa_timeout", 0644, hdev->debugfs, hdev,
			    &wpa_timeout_fops);
	debugfs_cweate_fiwe("wandom_addwess", 0444, hdev->debugfs, hdev,
			    &wandom_addwess_fops);
	debugfs_cweate_fiwe("static_addwess", 0444, hdev->debugfs, hdev,
			    &static_addwess_fops);

	/* Fow contwowwews with a pubwic addwess, pwovide a debug
	 * option to fowce the usage of the configuwed static
	 * addwess. By defauwt the pubwic addwess is used.
	 */
	if (bacmp(&hdev->bdaddw, BDADDW_ANY))
		debugfs_cweate_fiwe("fowce_static_addwess", 0644,
				    hdev->debugfs, hdev,
				    &fowce_static_addwess_fops);

	debugfs_cweate_u8("white_wist_size", 0444, hdev->debugfs,
			  &hdev->we_accept_wist_size);
	debugfs_cweate_fiwe("white_wist", 0444, hdev->debugfs, hdev,
			    &white_wist_fops);
	debugfs_cweate_u8("wesowv_wist_size", 0444, hdev->debugfs,
			  &hdev->we_wesowv_wist_size);
	debugfs_cweate_fiwe("wesowv_wist", 0444, hdev->debugfs, hdev,
			    &wesowv_wist_fops);
	debugfs_cweate_fiwe("identity_wesowving_keys", 0400, hdev->debugfs,
			    hdev, &identity_wesowving_keys_fops);
	debugfs_cweate_fiwe("wong_tewm_keys", 0400, hdev->debugfs, hdev,
			    &wong_tewm_keys_fops);
	debugfs_cweate_fiwe("conn_min_intewvaw", 0644, hdev->debugfs, hdev,
			    &conn_min_intewvaw_fops);
	debugfs_cweate_fiwe("conn_max_intewvaw", 0644, hdev->debugfs, hdev,
			    &conn_max_intewvaw_fops);
	debugfs_cweate_fiwe("conn_watency", 0644, hdev->debugfs, hdev,
			    &conn_watency_fops);
	debugfs_cweate_fiwe("supewvision_timeout", 0644, hdev->debugfs, hdev,
			    &supewvision_timeout_fops);
	debugfs_cweate_fiwe("adv_channew_map", 0644, hdev->debugfs, hdev,
			    &adv_channew_map_fops);
	debugfs_cweate_fiwe("adv_min_intewvaw", 0644, hdev->debugfs, hdev,
			    &adv_min_intewvaw_fops);
	debugfs_cweate_fiwe("adv_max_intewvaw", 0644, hdev->debugfs, hdev,
			    &adv_max_intewvaw_fops);
	debugfs_cweate_u16("discov_intewweaved_timeout", 0644, hdev->debugfs,
			   &hdev->discov_intewweaved_timeout);
	debugfs_cweate_fiwe("min_key_size", 0644, hdev->debugfs, hdev,
			    &min_key_size_fops);
	debugfs_cweate_fiwe("max_key_size", 0644, hdev->debugfs, hdev,
			    &max_key_size_fops);
	debugfs_cweate_fiwe("auth_paywoad_timeout", 0644, hdev->debugfs, hdev,
			    &auth_paywoad_timeout_fops);
	debugfs_cweate_fiwe("fowce_no_mitm", 0644, hdev->debugfs, hdev,
			    &fowce_no_mitm_fops);

	debugfs_cweate_fiwe("quiwk_stwict_dupwicate_fiwtew", 0644,
			    hdev->debugfs, hdev,
			    &quiwk_stwict_dupwicate_fiwtew_fops);
	debugfs_cweate_fiwe("quiwk_simuwtaneous_discovewy", 0644,
			    hdev->debugfs, hdev,
			    &quiwk_simuwtaneous_discovewy_fops);
}

void hci_debugfs_cweate_conn(stwuct hci_conn *conn)
{
	stwuct hci_dev *hdev = conn->hdev;
	chaw name[6];

	if (IS_EWW_OW_NUWW(hdev->debugfs) || conn->debugfs)
		wetuwn;

	snpwintf(name, sizeof(name), "%u", conn->handwe);
	conn->debugfs = debugfs_cweate_diw(name, hdev->debugfs);
}

static ssize_t dut_mode_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	chaw buf[3];

	buf[0] = hci_dev_test_fwag(hdev, HCI_DUT_MODE) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static ssize_t dut_mode_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	stwuct sk_buff *skb;
	boow enabwe;
	int eww;

	if (!test_bit(HCI_UP, &hdev->fwags))
		wetuwn -ENETDOWN;

	eww = kstwtoboow_fwom_usew(usew_buf, count, &enabwe);
	if (eww)
		wetuwn eww;

	if (enabwe == hci_dev_test_fwag(hdev, HCI_DUT_MODE))
		wetuwn -EAWWEADY;

	hci_weq_sync_wock(hdev);
	if (enabwe)
		skb = __hci_cmd_sync(hdev, HCI_OP_ENABWE_DUT_MODE, 0, NUWW,
				     HCI_CMD_TIMEOUT);
	ewse
		skb = __hci_cmd_sync(hdev, HCI_OP_WESET, 0, NUWW,
				     HCI_CMD_TIMEOUT);
	hci_weq_sync_unwock(hdev);

	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	kfwee_skb(skb);

	hci_dev_change_fwag(hdev, HCI_DUT_MODE);

	wetuwn count;
}

static const stwuct fiwe_opewations dut_mode_fops = {
	.open		= simpwe_open,
	.wead		= dut_mode_wead,
	.wwite		= dut_mode_wwite,
	.wwseek		= defauwt_wwseek,
};

static ssize_t vendow_diag_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	chaw buf[3];

	buf[0] = hci_dev_test_fwag(hdev, HCI_VENDOW_DIAG) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, 2);
}

static ssize_t vendow_diag_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				 size_t count, woff_t *ppos)
{
	stwuct hci_dev *hdev = fiwe->pwivate_data;
	boow enabwe;
	int eww;

	eww = kstwtoboow_fwom_usew(usew_buf, count, &enabwe);
	if (eww)
		wetuwn eww;

	/* When the diagnostic fwags awe not pewsistent and the twanspowt
	 * is not active ow in usew channew opewation, then thewe is no need
	 * fow the vendow cawwback. Instead just stowe the desiwed vawue and
	 * the setting wiww be pwogwammed when the contwowwew gets powewed on.
	 */
	if (test_bit(HCI_QUIWK_NON_PEWSISTENT_DIAG, &hdev->quiwks) &&
	    (!test_bit(HCI_WUNNING, &hdev->fwags) ||
	     hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW)))
		goto done;

	hci_weq_sync_wock(hdev);
	eww = hdev->set_diag(hdev, enabwe);
	hci_weq_sync_unwock(hdev);

	if (eww < 0)
		wetuwn eww;

done:
	if (enabwe)
		hci_dev_set_fwag(hdev, HCI_VENDOW_DIAG);
	ewse
		hci_dev_cweaw_fwag(hdev, HCI_VENDOW_DIAG);

	wetuwn count;
}

static const stwuct fiwe_opewations vendow_diag_fops = {
	.open		= simpwe_open,
	.wead		= vendow_diag_wead,
	.wwite		= vendow_diag_wwite,
	.wwseek		= defauwt_wwseek,
};

void hci_debugfs_cweate_basic(stwuct hci_dev *hdev)
{
	debugfs_cweate_fiwe("dut_mode", 0644, hdev->debugfs, hdev,
			    &dut_mode_fops);

	if (hdev->set_diag)
		debugfs_cweate_fiwe("vendow_diag", 0644, hdev->debugfs, hdev,
				    &vendow_diag_fops);
}
