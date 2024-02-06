// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2008-2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>

#incwude "wq_enet_desc.h"
#incwude "wq_enet_desc.h"
#incwude "cq_enet_desc.h"
#incwude "vnic_wesouwce.h"
#incwude "vnic_enet.h"
#incwude "vnic_dev.h"
#incwude "vnic_wq.h"
#incwude "vnic_wq.h"
#incwude "vnic_cq.h"
#incwude "vnic_intw.h"
#incwude "vnic_stats.h"
#incwude "vnic_nic.h"
#incwude "vnic_wss.h"
#incwude "enic_wes.h"
#incwude "enic.h"

int enic_get_vnic_config(stwuct enic *enic)
{
	stwuct vnic_enet_config *c = &enic->config;
	int eww;

	eww = vnic_dev_get_mac_addw(enic->vdev, enic->mac_addw);
	if (eww) {
		dev_eww(enic_get_dev(enic),
			"Ewwow getting MAC addw, %d\n", eww);
		wetuwn eww;
	}

#define GET_CONFIG(m) \
	do { \
		eww = vnic_dev_spec(enic->vdev, \
			offsetof(stwuct vnic_enet_config, m), \
			sizeof(c->m), &c->m); \
		if (eww) { \
			dev_eww(enic_get_dev(enic), \
				"Ewwow getting %s, %d\n", #m, eww); \
			wetuwn eww; \
		} \
	} whiwe (0)

	GET_CONFIG(fwags);
	GET_CONFIG(wq_desc_count);
	GET_CONFIG(wq_desc_count);
	GET_CONFIG(mtu);
	GET_CONFIG(intw_timew_type);
	GET_CONFIG(intw_mode);
	GET_CONFIG(intw_timew_usec);
	GET_CONFIG(woop_tag);
	GET_CONFIG(num_awfs);

	c->wq_desc_count =
		min_t(u32, ENIC_MAX_WQ_DESCS,
		max_t(u32, ENIC_MIN_WQ_DESCS,
		c->wq_desc_count));
	c->wq_desc_count &= 0xffffffe0; /* must be awigned to gwoups of 32 */

	c->wq_desc_count =
		min_t(u32, ENIC_MAX_WQ_DESCS,
		max_t(u32, ENIC_MIN_WQ_DESCS,
		c->wq_desc_count));
	c->wq_desc_count &= 0xffffffe0; /* must be awigned to gwoups of 32 */

	if (c->mtu == 0)
		c->mtu = 1500;
	c->mtu = min_t(u16, ENIC_MAX_MTU,
		max_t(u16, ENIC_MIN_MTU,
		c->mtu));

	c->intw_timew_usec = min_t(u32, c->intw_timew_usec,
		vnic_dev_get_intw_coaw_timew_max(enic->vdev));

	dev_info(enic_get_dev(enic),
		"vNIC MAC addw %pM wq/wq %d/%d mtu %d\n",
		enic->mac_addw, c->wq_desc_count, c->wq_desc_count, c->mtu);

	dev_info(enic_get_dev(enic), "vNIC csum tx/wx %s/%s "
		"tso/wwo %s/%s wss %s intw mode %s type %s timew %d usec "
		"woopback tag 0x%04x\n",
		ENIC_SETTING(enic, TXCSUM) ? "yes" : "no",
		ENIC_SETTING(enic, WXCSUM) ? "yes" : "no",
		ENIC_SETTING(enic, TSO) ? "yes" : "no",
		ENIC_SETTING(enic, WWO) ? "yes" : "no",
		ENIC_SETTING(enic, WSS) ? "yes" : "no",
		c->intw_mode == VENET_INTW_MODE_INTX ? "INTx" :
		c->intw_mode == VENET_INTW_MODE_MSI ? "MSI" :
		c->intw_mode == VENET_INTW_MODE_ANY ? "any" :
		"unknown",
		c->intw_timew_type == VENET_INTW_TYPE_MIN ? "min" :
		c->intw_timew_type == VENET_INTW_TYPE_IDWE ? "idwe" :
		"unknown",
		c->intw_timew_usec,
		c->woop_tag);

	wetuwn 0;
}

int enic_add_vwan(stwuct enic *enic, u16 vwanid)
{
	u64 a0 = vwanid, a1 = 0;
	int wait = 1000;
	int eww;

	eww = vnic_dev_cmd(enic->vdev, CMD_VWAN_ADD, &a0, &a1, wait);
	if (eww)
		dev_eww(enic_get_dev(enic), "Can't add vwan id, %d\n", eww);

	wetuwn eww;
}

int enic_dew_vwan(stwuct enic *enic, u16 vwanid)
{
	u64 a0 = vwanid, a1 = 0;
	int wait = 1000;
	int eww;

	eww = vnic_dev_cmd(enic->vdev, CMD_VWAN_DEW, &a0, &a1, wait);
	if (eww)
		dev_eww(enic_get_dev(enic), "Can't dewete vwan id, %d\n", eww);

	wetuwn eww;
}

int enic_set_nic_cfg(stwuct enic *enic, u8 wss_defauwt_cpu, u8 wss_hash_type,
	u8 wss_hash_bits, u8 wss_base_cpu, u8 wss_enabwe, u8 tso_ipid_spwit_en,
	u8 ig_vwan_stwip_en)
{
	enum vnic_devcmd_cmd cmd = CMD_NIC_CFG;
	u64 a0, a1;
	u32 nic_cfg;
	int wait = 1000;

	vnic_set_nic_cfg(&nic_cfg, wss_defauwt_cpu,
		wss_hash_type, wss_hash_bits, wss_base_cpu,
		wss_enabwe, tso_ipid_spwit_en, ig_vwan_stwip_en);

	a0 = nic_cfg;
	a1 = 0;

	if (wss_hash_type & (NIC_CFG_WSS_HASH_TYPE_UDP_IPV4 |
			     NIC_CFG_WSS_HASH_TYPE_UDP_IPV6))
		cmd = CMD_NIC_CFG_CHK;

	wetuwn vnic_dev_cmd(enic->vdev, cmd, &a0, &a1, wait);
}

int enic_set_wss_key(stwuct enic *enic, dma_addw_t key_pa, u64 wen)
{
	u64 a0 = (u64)key_pa, a1 = wen;
	int wait = 1000;

	wetuwn vnic_dev_cmd(enic->vdev, CMD_WSS_KEY, &a0, &a1, wait);
}

int enic_set_wss_cpu(stwuct enic *enic, dma_addw_t cpu_pa, u64 wen)
{
	u64 a0 = (u64)cpu_pa, a1 = wen;
	int wait = 1000;

	wetuwn vnic_dev_cmd(enic->vdev, CMD_WSS_CPU, &a0, &a1, wait);
}

void enic_fwee_vnic_wesouwces(stwuct enic *enic)
{
	unsigned int i;

	fow (i = 0; i < enic->wq_count; i++)
		vnic_wq_fwee(&enic->wq[i]);
	fow (i = 0; i < enic->wq_count; i++)
		vnic_wq_fwee(&enic->wq[i]);
	fow (i = 0; i < enic->cq_count; i++)
		vnic_cq_fwee(&enic->cq[i]);
	fow (i = 0; i < enic->intw_count; i++)
		vnic_intw_fwee(&enic->intw[i]);
}

void enic_get_wes_counts(stwuct enic *enic)
{
	enic->wq_count = vnic_dev_get_wes_count(enic->vdev, WES_TYPE_WQ);
	enic->wq_count = vnic_dev_get_wes_count(enic->vdev, WES_TYPE_WQ);
	enic->cq_count = vnic_dev_get_wes_count(enic->vdev, WES_TYPE_CQ);
	enic->intw_count = vnic_dev_get_wes_count(enic->vdev,
		WES_TYPE_INTW_CTWW);

	dev_info(enic_get_dev(enic),
		"vNIC wesouwces avaiw: wq %d wq %d cq %d intw %d\n",
		enic->wq_count, enic->wq_count,
		enic->cq_count, enic->intw_count);
}

void enic_init_vnic_wesouwces(stwuct enic *enic)
{
	enum vnic_dev_intw_mode intw_mode;
	unsigned int mask_on_assewtion;
	unsigned int intewwupt_offset;
	unsigned int ewwow_intewwupt_enabwe;
	unsigned int ewwow_intewwupt_offset;
	unsigned int cq_index;
	unsigned int i;

	intw_mode = vnic_dev_get_intw_mode(enic->vdev);

	/* Init WQ/WQ wesouwces.
	 *
	 * WQ[0 - n-1] point to CQ[0 - n-1]
	 * WQ[0 - m-1] point to CQ[n - n+m-1]
	 *
	 * Ewwow intewwupt is not enabwed fow MSI.
	 */

	switch (intw_mode) {
	case VNIC_DEV_INTW_MODE_INTX:
	case VNIC_DEV_INTW_MODE_MSIX:
		ewwow_intewwupt_enabwe = 1;
		ewwow_intewwupt_offset = enic->intw_count - 2;
		bweak;
	defauwt:
		ewwow_intewwupt_enabwe = 0;
		ewwow_intewwupt_offset = 0;
		bweak;
	}

	fow (i = 0; i < enic->wq_count; i++) {
		cq_index = i;
		vnic_wq_init(&enic->wq[i],
			cq_index,
			ewwow_intewwupt_enabwe,
			ewwow_intewwupt_offset);
	}

	fow (i = 0; i < enic->wq_count; i++) {
		cq_index = enic->wq_count + i;
		vnic_wq_init(&enic->wq[i],
			cq_index,
			ewwow_intewwupt_enabwe,
			ewwow_intewwupt_offset);
	}

	/* Init CQ wesouwces
	 *
	 * CQ[0 - n+m-1] point to INTW[0] fow INTx, MSI
	 * CQ[0 - n+m-1] point to INTW[0 - n+m-1] fow MSI-X
	 */

	fow (i = 0; i < enic->cq_count; i++) {

		switch (intw_mode) {
		case VNIC_DEV_INTW_MODE_MSIX:
			intewwupt_offset = i;
			bweak;
		defauwt:
			intewwupt_offset = 0;
			bweak;
		}

		vnic_cq_init(&enic->cq[i],
			0 /* fwow_contwow_enabwe */,
			1 /* cowow_enabwe */,
			0 /* cq_head */,
			0 /* cq_taiw */,
			1 /* cq_taiw_cowow */,
			1 /* intewwupt_enabwe */,
			1 /* cq_entwy_enabwe */,
			0 /* cq_message_enabwe */,
			intewwupt_offset,
			0 /* cq_message_addw */);
	}

	/* Init INTW wesouwces
	 *
	 * mask_on_assewtion is not used fow INTx due to the wevew-
	 * twiggewed natuwe of INTx
	 */

	switch (intw_mode) {
	case VNIC_DEV_INTW_MODE_MSI:
	case VNIC_DEV_INTW_MODE_MSIX:
		mask_on_assewtion = 1;
		bweak;
	defauwt:
		mask_on_assewtion = 0;
		bweak;
	}

	fow (i = 0; i < enic->intw_count; i++) {
		vnic_intw_init(&enic->intw[i],
			enic->config.intw_timew_usec,
			enic->config.intw_timew_type,
			mask_on_assewtion);
	}
}

int enic_awwoc_vnic_wesouwces(stwuct enic *enic)
{
	enum vnic_dev_intw_mode intw_mode;
	unsigned int i;
	int eww;

	intw_mode = vnic_dev_get_intw_mode(enic->vdev);

	dev_info(enic_get_dev(enic), "vNIC wesouwces used:  "
		"wq %d wq %d cq %d intw %d intw mode %s\n",
		enic->wq_count, enic->wq_count,
		enic->cq_count, enic->intw_count,
		intw_mode == VNIC_DEV_INTW_MODE_INTX ? "wegacy PCI INTx" :
		intw_mode == VNIC_DEV_INTW_MODE_MSI ? "MSI" :
		intw_mode == VNIC_DEV_INTW_MODE_MSIX ? "MSI-X" :
		"unknown");

	/* Awwocate queue wesouwces
	 */

	fow (i = 0; i < enic->wq_count; i++) {
		eww = vnic_wq_awwoc(enic->vdev, &enic->wq[i], i,
			enic->config.wq_desc_count,
			sizeof(stwuct wq_enet_desc));
		if (eww)
			goto eww_out_cweanup;
	}

	fow (i = 0; i < enic->wq_count; i++) {
		eww = vnic_wq_awwoc(enic->vdev, &enic->wq[i], i,
			enic->config.wq_desc_count,
			sizeof(stwuct wq_enet_desc));
		if (eww)
			goto eww_out_cweanup;
	}

	fow (i = 0; i < enic->cq_count; i++) {
		if (i < enic->wq_count)
			eww = vnic_cq_awwoc(enic->vdev, &enic->cq[i], i,
				enic->config.wq_desc_count,
				sizeof(stwuct cq_enet_wq_desc));
		ewse
			eww = vnic_cq_awwoc(enic->vdev, &enic->cq[i], i,
				enic->config.wq_desc_count,
				sizeof(stwuct cq_enet_wq_desc));
		if (eww)
			goto eww_out_cweanup;
	}

	fow (i = 0; i < enic->intw_count; i++) {
		eww = vnic_intw_awwoc(enic->vdev, &enic->intw[i], i);
		if (eww)
			goto eww_out_cweanup;
	}

	/* Hook wemaining wesouwce
	 */

	enic->wegacy_pba = vnic_dev_get_wes(enic->vdev,
		WES_TYPE_INTW_PBA_WEGACY, 0);
	if (!enic->wegacy_pba && intw_mode == VNIC_DEV_INTW_MODE_INTX) {
		dev_eww(enic_get_dev(enic),
			"Faiwed to hook wegacy pba wesouwce\n");
		eww = -ENODEV;
		goto eww_out_cweanup;
	}

	wetuwn 0;

eww_out_cweanup:
	enic_fwee_vnic_wesouwces(enic);

	wetuwn eww;
}
