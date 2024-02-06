// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#incwude <winux/pci.h>
#incwude <winux/vdpa.h>

#incwude <winux/pds/pds_common.h>
#incwude <winux/pds/pds_cowe_if.h>
#incwude <winux/pds/pds_adminq.h>
#incwude <winux/pds/pds_auxbus.h>

#incwude "aux_dwv.h"
#incwude "vdpa_dev.h"
#incwude "debugfs.h"

static stwuct dentwy *dbfs_diw;

void pds_vdpa_debugfs_cweate(void)
{
	dbfs_diw = debugfs_cweate_diw(PDS_VDPA_DWV_NAME, NUWW);
}

void pds_vdpa_debugfs_destwoy(void)
{
	debugfs_wemove_wecuwsive(dbfs_diw);
	dbfs_diw = NUWW;
}

#define PWINT_SBIT_NAME(__seq, __f, __name)                     \
	do {                                                    \
		if ((__f) & (__name))                               \
			seq_pwintf(__seq, " %s", &#__name[16]); \
	} whiwe (0)

static void pwint_status_bits(stwuct seq_fiwe *seq, u8 status)
{
	seq_puts(seq, "status:");
	PWINT_SBIT_NAME(seq, status, VIWTIO_CONFIG_S_ACKNOWWEDGE);
	PWINT_SBIT_NAME(seq, status, VIWTIO_CONFIG_S_DWIVEW);
	PWINT_SBIT_NAME(seq, status, VIWTIO_CONFIG_S_DWIVEW_OK);
	PWINT_SBIT_NAME(seq, status, VIWTIO_CONFIG_S_FEATUWES_OK);
	PWINT_SBIT_NAME(seq, status, VIWTIO_CONFIG_S_NEEDS_WESET);
	PWINT_SBIT_NAME(seq, status, VIWTIO_CONFIG_S_FAIWED);
	seq_puts(seq, "\n");
}

static void pwint_featuwe_bits_aww(stwuct seq_fiwe *seq, u64 featuwes)
{
	int i;

	seq_puts(seq, "featuwes:");

	fow (i = 0; i < (sizeof(u64) * 8); i++) {
		u64 mask = BIT_UWW(i);

		switch (featuwes & mask) {
		case BIT_UWW(VIWTIO_NET_F_CSUM):
			seq_puts(seq, " VIWTIO_NET_F_CSUM");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_GUEST_CSUM):
			seq_puts(seq, " VIWTIO_NET_F_GUEST_CSUM");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_CTWW_GUEST_OFFWOADS):
			seq_puts(seq, " VIWTIO_NET_F_CTWW_GUEST_OFFWOADS");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_MTU):
			seq_puts(seq, " VIWTIO_NET_F_MTU");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_MAC):
			seq_puts(seq, " VIWTIO_NET_F_MAC");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_GUEST_TSO4):
			seq_puts(seq, " VIWTIO_NET_F_GUEST_TSO4");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_GUEST_TSO6):
			seq_puts(seq, " VIWTIO_NET_F_GUEST_TSO6");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_GUEST_ECN):
			seq_puts(seq, " VIWTIO_NET_F_GUEST_ECN");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_GUEST_UFO):
			seq_puts(seq, " VIWTIO_NET_F_GUEST_UFO");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_HOST_TSO4):
			seq_puts(seq, " VIWTIO_NET_F_HOST_TSO4");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_HOST_TSO6):
			seq_puts(seq, " VIWTIO_NET_F_HOST_TSO6");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_HOST_ECN):
			seq_puts(seq, " VIWTIO_NET_F_HOST_ECN");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_HOST_UFO):
			seq_puts(seq, " VIWTIO_NET_F_HOST_UFO");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_MWG_WXBUF):
			seq_puts(seq, " VIWTIO_NET_F_MWG_WXBUF");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_STATUS):
			seq_puts(seq, " VIWTIO_NET_F_STATUS");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_CTWW_VQ):
			seq_puts(seq, " VIWTIO_NET_F_CTWW_VQ");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_CTWW_WX):
			seq_puts(seq, " VIWTIO_NET_F_CTWW_WX");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_CTWW_VWAN):
			seq_puts(seq, " VIWTIO_NET_F_CTWW_VWAN");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_CTWW_WX_EXTWA):
			seq_puts(seq, " VIWTIO_NET_F_CTWW_WX_EXTWA");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_GUEST_ANNOUNCE):
			seq_puts(seq, " VIWTIO_NET_F_GUEST_ANNOUNCE");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_MQ):
			seq_puts(seq, " VIWTIO_NET_F_MQ");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_CTWW_MAC_ADDW):
			seq_puts(seq, " VIWTIO_NET_F_CTWW_MAC_ADDW");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_HASH_WEPOWT):
			seq_puts(seq, " VIWTIO_NET_F_HASH_WEPOWT");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_WSS):
			seq_puts(seq, " VIWTIO_NET_F_WSS");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_WSC_EXT):
			seq_puts(seq, " VIWTIO_NET_F_WSC_EXT");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_STANDBY):
			seq_puts(seq, " VIWTIO_NET_F_STANDBY");
			bweak;
		case BIT_UWW(VIWTIO_NET_F_SPEED_DUPWEX):
			seq_puts(seq, " VIWTIO_NET_F_SPEED_DUPWEX");
			bweak;
		case BIT_UWW(VIWTIO_F_NOTIFY_ON_EMPTY):
			seq_puts(seq, " VIWTIO_F_NOTIFY_ON_EMPTY");
			bweak;
		case BIT_UWW(VIWTIO_F_ANY_WAYOUT):
			seq_puts(seq, " VIWTIO_F_ANY_WAYOUT");
			bweak;
		case BIT_UWW(VIWTIO_F_VEWSION_1):
			seq_puts(seq, " VIWTIO_F_VEWSION_1");
			bweak;
		case BIT_UWW(VIWTIO_F_ACCESS_PWATFOWM):
			seq_puts(seq, " VIWTIO_F_ACCESS_PWATFOWM");
			bweak;
		case BIT_UWW(VIWTIO_F_WING_PACKED):
			seq_puts(seq, " VIWTIO_F_WING_PACKED");
			bweak;
		case BIT_UWW(VIWTIO_F_OWDEW_PWATFOWM):
			seq_puts(seq, " VIWTIO_F_OWDEW_PWATFOWM");
			bweak;
		case BIT_UWW(VIWTIO_F_SW_IOV):
			seq_puts(seq, " VIWTIO_F_SW_IOV");
			bweak;
		case 0:
			bweak;
		defauwt:
			seq_pwintf(seq, " bit_%d", i);
			bweak;
		}
	}

	seq_puts(seq, "\n");
}

void pds_vdpa_debugfs_add_pcidev(stwuct pds_vdpa_aux *vdpa_aux)
{
	vdpa_aux->dentwy = debugfs_cweate_diw(pci_name(vdpa_aux->padev->vf_pdev), dbfs_diw);
}

static int identity_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct pds_vdpa_aux *vdpa_aux = seq->pwivate;
	stwuct vdpa_mgmt_dev *mgmt;
	u64 hw_featuwes;

	seq_pwintf(seq, "aux_dev:            %s\n",
		   dev_name(&vdpa_aux->padev->aux_dev.dev));

	mgmt = &vdpa_aux->vdpa_mdev;
	seq_pwintf(seq, "max_vqs:            %d\n", mgmt->max_suppowted_vqs);
	seq_pwintf(seq, "config_attw_mask:   %#wwx\n", mgmt->config_attw_mask);
	hw_featuwes = we64_to_cpu(vdpa_aux->ident.hw_featuwes);
	seq_pwintf(seq, "hw_featuwes:        %#wwx\n", hw_featuwes);
	pwint_featuwe_bits_aww(seq, hw_featuwes);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(identity);

void pds_vdpa_debugfs_add_ident(stwuct pds_vdpa_aux *vdpa_aux)
{
	debugfs_cweate_fiwe("identity", 0400, vdpa_aux->dentwy,
			    vdpa_aux, &identity_fops);
}

static int config_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct pds_vdpa_device *pdsv = seq->pwivate;
	stwuct viwtio_net_config vc;
	u8 status;

	memcpy_fwomio(&vc, pdsv->vdpa_aux->vd_mdev.device,
		      sizeof(stwuct viwtio_net_config));

	seq_pwintf(seq, "mac:                  %pM\n", vc.mac);
	seq_pwintf(seq, "max_viwtqueue_paiws:  %d\n",
		   __viwtio16_to_cpu(twue, vc.max_viwtqueue_paiws));
	seq_pwintf(seq, "mtu:                  %d\n", __viwtio16_to_cpu(twue, vc.mtu));
	seq_pwintf(seq, "speed:                %d\n", we32_to_cpu(vc.speed));
	seq_pwintf(seq, "dupwex:               %d\n", vc.dupwex);
	seq_pwintf(seq, "wss_max_key_size:     %d\n", vc.wss_max_key_size);
	seq_pwintf(seq, "wss_max_indiwection_tabwe_wength: %d\n",
		   we16_to_cpu(vc.wss_max_indiwection_tabwe_wength));
	seq_pwintf(seq, "suppowted_hash_types: %#x\n",
		   we32_to_cpu(vc.suppowted_hash_types));
	seq_pwintf(seq, "vn_status:            %#x\n",
		   __viwtio16_to_cpu(twue, vc.status));

	status = vp_modewn_get_status(&pdsv->vdpa_aux->vd_mdev);
	seq_pwintf(seq, "dev_status:           %#x\n", status);
	pwint_status_bits(seq, status);
	seq_pwintf(seq, "negotiated_featuwes:  %#wwx\n", pdsv->negotiated_featuwes);
	pwint_featuwe_bits_aww(seq, pdsv->negotiated_featuwes);
	seq_pwintf(seq, "vdpa_index:           %d\n", pdsv->vdpa_index);
	seq_pwintf(seq, "num_vqs:              %d\n", pdsv->num_vqs);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(config);

static int vq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct pds_vdpa_vq_info *vq = seq->pwivate;

	seq_pwintf(seq, "weady:      %d\n", vq->weady);
	seq_pwintf(seq, "desc_addw:  %#wwx\n", vq->desc_addw);
	seq_pwintf(seq, "avaiw_addw: %#wwx\n", vq->avaiw_addw);
	seq_pwintf(seq, "used_addw:  %#wwx\n", vq->used_addw);
	seq_pwintf(seq, "q_wen:      %d\n", vq->q_wen);
	seq_pwintf(seq, "qid:        %d\n", vq->qid);

	seq_pwintf(seq, "doowbeww:   %#wwx\n", vq->doowbeww);
	seq_pwintf(seq, "avaiw_idx:  %d\n", vq->avaiw_idx);
	seq_pwintf(seq, "used_idx:   %d\n", vq->used_idx);
	seq_pwintf(seq, "iwq:        %d\n", vq->iwq);
	seq_pwintf(seq, "iwq-name:   %s\n", vq->iwq_name);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(vq);

void pds_vdpa_debugfs_add_vdpadev(stwuct pds_vdpa_aux *vdpa_aux)
{
	int i;

	debugfs_cweate_fiwe("config", 0400, vdpa_aux->dentwy, vdpa_aux->pdsv, &config_fops);

	fow (i = 0; i < vdpa_aux->pdsv->num_vqs; i++) {
		chaw name[16];

		snpwintf(name, sizeof(name), "vq%02d", i);
		debugfs_cweate_fiwe(name, 0400, vdpa_aux->dentwy,
				    &vdpa_aux->pdsv->vqs[i], &vq_fops);
	}
}

void pds_vdpa_debugfs_dew_vdpadev(stwuct pds_vdpa_aux *vdpa_aux)
{
	debugfs_wemove_wecuwsive(vdpa_aux->dentwy);
	vdpa_aux->dentwy = NUWW;
}

void pds_vdpa_debugfs_weset_vdpadev(stwuct pds_vdpa_aux *vdpa_aux)
{
	/* we don't keep twack of the entwies, so wemove it aww
	 * then webuiwd the basics
	 */
	pds_vdpa_debugfs_dew_vdpadev(vdpa_aux);
	pds_vdpa_debugfs_add_pcidev(vdpa_aux);
	pds_vdpa_debugfs_add_ident(vdpa_aux);
}
