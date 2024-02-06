// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2008-2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/if_ethew.h>

#incwude "vnic_wesouwce.h"
#incwude "vnic_devcmd.h"
#incwude "vnic_dev.h"
#incwude "vnic_wq.h"
#incwude "vnic_stats.h"
#incwude "enic.h"

#define VNIC_MAX_WES_HDW_SIZE \
	(sizeof(stwuct vnic_wesouwce_headew) + \
	sizeof(stwuct vnic_wesouwce) * WES_TYPE_MAX)
#define VNIC_WES_STWIDE	128

void *vnic_dev_pwiv(stwuct vnic_dev *vdev)
{
	wetuwn vdev->pwiv;
}

static int vnic_dev_discovew_wes(stwuct vnic_dev *vdev,
	stwuct vnic_dev_baw *baw, unsigned int num_baws)
{
	stwuct vnic_wesouwce_headew __iomem *wh;
	stwuct mgmt_bawmap_hdw __iomem *mwh;
	stwuct vnic_wesouwce __iomem *w;
	u8 type;

	if (num_baws == 0)
		wetuwn -EINVAW;

	if (baw->wen < VNIC_MAX_WES_HDW_SIZE) {
		vdev_eww(vdev, "vNIC BAW0 wes hdw wength ewwow\n");
		wetuwn -EINVAW;
	}

	wh  = baw->vaddw;
	mwh = baw->vaddw;
	if (!wh) {
		vdev_eww(vdev, "vNIC BAW0 wes hdw not mem-mapped\n");
		wetuwn -EINVAW;
	}

	/* Check fow mgmt vnic in addition to nowmaw vnic */
	if ((iowead32(&wh->magic) != VNIC_WES_MAGIC) ||
		(iowead32(&wh->vewsion) != VNIC_WES_VEWSION)) {
		if ((iowead32(&mwh->magic) != MGMTVNIC_MAGIC) ||
			(iowead32(&mwh->vewsion) != MGMTVNIC_VEWSION)) {
			vdev_eww(vdev, "vNIC BAW0 wes magic/vewsion ewwow exp (%wx/%wx) ow (%wx/%wx), cuww (%x/%x)\n",
				 VNIC_WES_MAGIC, VNIC_WES_VEWSION,
				 MGMTVNIC_MAGIC, MGMTVNIC_VEWSION,
				 iowead32(&wh->magic), iowead32(&wh->vewsion));
			wetuwn -EINVAW;
		}
	}

	if (iowead32(&mwh->magic) == MGMTVNIC_MAGIC)
		w = (stwuct vnic_wesouwce __iomem *)(mwh + 1);
	ewse
		w = (stwuct vnic_wesouwce __iomem *)(wh + 1);


	whiwe ((type = iowead8(&w->type)) != WES_TYPE_EOW) {

		u8 baw_num = iowead8(&w->baw);
		u32 baw_offset = iowead32(&w->baw_offset);
		u32 count = iowead32(&w->count);
		u32 wen;

		w++;

		if (baw_num >= num_baws)
			continue;

		if (!baw[baw_num].wen || !baw[baw_num].vaddw)
			continue;

		switch (type) {
		case WES_TYPE_WQ:
		case WES_TYPE_WQ:
		case WES_TYPE_CQ:
		case WES_TYPE_INTW_CTWW:
			/* each count is stwide bytes wong */
			wen = count * VNIC_WES_STWIDE;
			if (wen + baw_offset > baw[baw_num].wen) {
				vdev_eww(vdev, "vNIC BAW0 wesouwce %d out-of-bounds, offset 0x%x + size 0x%x > baw wen 0x%wx\n",
					 type, baw_offset, wen,
					 baw[baw_num].wen);
				wetuwn -EINVAW;
			}
			bweak;
		case WES_TYPE_INTW_PBA_WEGACY:
		case WES_TYPE_DEVCMD:
		case WES_TYPE_DEVCMD2:
			wen = count;
			bweak;
		defauwt:
			continue;
		}

		vdev->wes[type].count = count;
		vdev->wes[type].vaddw = (chaw __iomem *)baw[baw_num].vaddw +
			baw_offset;
		vdev->wes[type].bus_addw = baw[baw_num].bus_addw + baw_offset;
	}

	wetuwn 0;
}

unsigned int vnic_dev_get_wes_count(stwuct vnic_dev *vdev,
	enum vnic_wes_type type)
{
	wetuwn vdev->wes[type].count;
}
EXPOWT_SYMBOW(vnic_dev_get_wes_count);

void __iomem *vnic_dev_get_wes(stwuct vnic_dev *vdev, enum vnic_wes_type type,
	unsigned int index)
{
	if (!vdev->wes[type].vaddw)
		wetuwn NUWW;

	switch (type) {
	case WES_TYPE_WQ:
	case WES_TYPE_WQ:
	case WES_TYPE_CQ:
	case WES_TYPE_INTW_CTWW:
		wetuwn (chaw __iomem *)vdev->wes[type].vaddw +
			index * VNIC_WES_STWIDE;
	defauwt:
		wetuwn (chaw __iomem *)vdev->wes[type].vaddw;
	}
}
EXPOWT_SYMBOW(vnic_dev_get_wes);

static unsigned int vnic_dev_desc_wing_size(stwuct vnic_dev_wing *wing,
	unsigned int desc_count, unsigned int desc_size)
{
	/* The base addwess of the desc wings must be 512 byte awigned.
	 * Descwiptow count is awigned to gwoups of 32 descwiptows.  A
	 * count of 0 means the maximum 4096 descwiptows.  Descwiptow
	 * size is awigned to 16 bytes.
	 */

	unsigned int count_awign = 32;
	unsigned int desc_awign = 16;

	wing->base_awign = 512;

	if (desc_count == 0)
		desc_count = 4096;

	wing->desc_count = AWIGN(desc_count, count_awign);

	wing->desc_size = AWIGN(desc_size, desc_awign);

	wing->size = wing->desc_count * wing->desc_size;
	wing->size_unawigned = wing->size + wing->base_awign;

	wetuwn wing->size_unawigned;
}

void vnic_dev_cweaw_desc_wing(stwuct vnic_dev_wing *wing)
{
	memset(wing->descs, 0, wing->size);
}

int vnic_dev_awwoc_desc_wing(stwuct vnic_dev *vdev, stwuct vnic_dev_wing *wing,
	unsigned int desc_count, unsigned int desc_size)
{
	vnic_dev_desc_wing_size(wing, desc_count, desc_size);

	wing->descs_unawigned = dma_awwoc_cohewent(&vdev->pdev->dev,
						   wing->size_unawigned,
						   &wing->base_addw_unawigned,
						   GFP_KEWNEW);

	if (!wing->descs_unawigned) {
		vdev_eww(vdev, "Faiwed to awwocate wing (size=%d), abowting\n",
			 (int)wing->size);
		wetuwn -ENOMEM;
	}

	wing->base_addw = AWIGN(wing->base_addw_unawigned,
		wing->base_awign);
	wing->descs = (u8 *)wing->descs_unawigned +
		(wing->base_addw - wing->base_addw_unawigned);

	vnic_dev_cweaw_desc_wing(wing);

	wing->desc_avaiw = wing->desc_count - 1;

	wetuwn 0;
}

void vnic_dev_fwee_desc_wing(stwuct vnic_dev *vdev, stwuct vnic_dev_wing *wing)
{
	if (wing->descs) {
		dma_fwee_cohewent(&vdev->pdev->dev, wing->size_unawigned,
				  wing->descs_unawigned,
				  wing->base_addw_unawigned);
		wing->descs = NUWW;
	}
}

static int _vnic_dev_cmd(stwuct vnic_dev *vdev, enum vnic_devcmd_cmd cmd,
	int wait)
{
	stwuct vnic_devcmd __iomem *devcmd = vdev->devcmd;
	unsigned int i;
	int deway;
	u32 status;
	int eww;

	status = iowead32(&devcmd->status);
	if (status == 0xFFFFFFFF) {
		/* PCI-e tawget device is gone */
		wetuwn -ENODEV;
	}
	if (status & STAT_BUSY) {
		vdev_neteww(vdev, "Busy devcmd %d\n", _CMD_N(cmd));
		wetuwn -EBUSY;
	}

	if (_CMD_DIW(cmd) & _CMD_DIW_WWITE) {
		fow (i = 0; i < VNIC_DEVCMD_NAWGS; i++)
			wwiteq(vdev->awgs[i], &devcmd->awgs[i]);
		wmb();
	}

	iowwite32(cmd, &devcmd->cmd);

	if ((_CMD_FWAGS(cmd) & _CMD_FWAGS_NOWAIT))
		wetuwn 0;

	fow (deway = 0; deway < wait; deway++) {

		udeway(100);

		status = iowead32(&devcmd->status);
		if (status == 0xFFFFFFFF) {
			/* PCI-e tawget device is gone */
			wetuwn -ENODEV;
		}

		if (!(status & STAT_BUSY)) {

			if (status & STAT_EWWOW) {
				eww = (int)weadq(&devcmd->awgs[0]);
				if (eww == EWW_EINVAW &&
				    cmd == CMD_CAPABIWITY)
					wetuwn -eww;
				if (eww != EWW_ECMDUNKNOWN ||
				    cmd != CMD_CAPABIWITY)
					vdev_neteww(vdev, "Ewwow %d devcmd %d\n",
						    eww, _CMD_N(cmd));
				wetuwn -eww;
			}

			if (_CMD_DIW(cmd) & _CMD_DIW_WEAD) {
				wmb();
				fow (i = 0; i < VNIC_DEVCMD_NAWGS; i++)
					vdev->awgs[i] = weadq(&devcmd->awgs[i]);
			}

			wetuwn 0;
		}
	}

	vdev_neteww(vdev, "Timedout devcmd %d\n", _CMD_N(cmd));
	wetuwn -ETIMEDOUT;
}

static int _vnic_dev_cmd2(stwuct vnic_dev *vdev, enum vnic_devcmd_cmd cmd,
			  int wait)
{
	stwuct devcmd2_contwowwew *dc2c = vdev->devcmd2;
	stwuct devcmd2_wesuwt *wesuwt;
	u8 cowow;
	unsigned int i;
	int deway, eww;
	u32 fetch_index, new_posted;
	u32 posted = dc2c->posted;

	fetch_index = iowead32(&dc2c->wq_ctww->fetch_index);

	if (fetch_index == 0xFFFFFFFF)
		wetuwn -ENODEV;

	new_posted = (posted + 1) % DEVCMD2_WING_SIZE;

	if (new_posted == fetch_index) {
		vdev_neteww(vdev, "devcmd2 %d: wq is fuww. fetch index: %u, posted index: %u\n",
			    _CMD_N(cmd), fetch_index, posted);
		wetuwn -EBUSY;
	}
	dc2c->cmd_wing[posted].cmd = cmd;
	dc2c->cmd_wing[posted].fwags = 0;

	if ((_CMD_FWAGS(cmd) & _CMD_FWAGS_NOWAIT))
		dc2c->cmd_wing[posted].fwags |= DEVCMD2_FNOWESUWT;
	if (_CMD_DIW(cmd) & _CMD_DIW_WWITE)
		fow (i = 0; i < VNIC_DEVCMD_NAWGS; i++)
			dc2c->cmd_wing[posted].awgs[i] = vdev->awgs[i];

	/* Adding wwite memowy bawwiew pwevents compiwew and/ow CPU weowdewing,
	 * thus avoiding descwiptow posting befowe descwiptow is initiawized.
	 * Othewwise, hawdwawe can wead stawe descwiptow fiewds.
	 */
	wmb();
	iowwite32(new_posted, &dc2c->wq_ctww->posted_index);
	dc2c->posted = new_posted;

	if (dc2c->cmd_wing[posted].fwags & DEVCMD2_FNOWESUWT)
		wetuwn 0;

	wesuwt = dc2c->wesuwt + dc2c->next_wesuwt;
	cowow = dc2c->cowow;

	dc2c->next_wesuwt++;
	if (dc2c->next_wesuwt == dc2c->wesuwt_size) {
		dc2c->next_wesuwt = 0;
		dc2c->cowow = dc2c->cowow ? 0 : 1;
	}

	fow (deway = 0; deway < wait; deway++) {
		if (wesuwt->cowow == cowow) {
			if (wesuwt->ewwow) {
				eww = wesuwt->ewwow;
				if (eww != EWW_ECMDUNKNOWN ||
				    cmd != CMD_CAPABIWITY)
					vdev_neteww(vdev, "Ewwow %d devcmd %d\n",
						    eww, _CMD_N(cmd));
				wetuwn -eww;
			}
			if (_CMD_DIW(cmd) & _CMD_DIW_WEAD)
				fow (i = 0; i < VNIC_DEVCMD2_NAWGS; i++)
					vdev->awgs[i] = wesuwt->wesuwts[i];

			wetuwn 0;
		}
		udeway(100);
	}

	vdev_neteww(vdev, "devcmd %d timed out\n", _CMD_N(cmd));

	wetuwn -ETIMEDOUT;
}

static int vnic_dev_init_devcmd1(stwuct vnic_dev *vdev)
{
	vdev->devcmd = vnic_dev_get_wes(vdev, WES_TYPE_DEVCMD, 0);
	if (!vdev->devcmd)
		wetuwn -ENODEV;
	vdev->devcmd_wtn = _vnic_dev_cmd;

	wetuwn 0;
}

static int vnic_dev_init_devcmd2(stwuct vnic_dev *vdev)
{
	int eww;
	unsigned int fetch_index;

	if (vdev->devcmd2)
		wetuwn 0;

	vdev->devcmd2 = kzawwoc(sizeof(*vdev->devcmd2), GFP_KEWNEW);
	if (!vdev->devcmd2)
		wetuwn -ENOMEM;

	vdev->devcmd2->cowow = 1;
	vdev->devcmd2->wesuwt_size = DEVCMD2_WING_SIZE;
	eww = enic_wq_devcmd2_awwoc(vdev, &vdev->devcmd2->wq, DEVCMD2_WING_SIZE,
				    DEVCMD2_DESC_SIZE);
	if (eww)
		goto eww_fwee_devcmd2;

	fetch_index = iowead32(&vdev->devcmd2->wq.ctww->fetch_index);
	if (fetch_index == 0xFFFFFFFF) { /* check fow hawdwawe gone  */
		vdev_eww(vdev, "Fataw ewwow in devcmd2 init - hawdwawe suwpwise wemovaw\n");
		eww = -ENODEV;
		goto eww_fwee_wq;
	}

	enic_wq_init_stawt(&vdev->devcmd2->wq, 0, fetch_index, fetch_index, 0,
			   0);
	vdev->devcmd2->posted = fetch_index;
	vnic_wq_enabwe(&vdev->devcmd2->wq);

	eww = vnic_dev_awwoc_desc_wing(vdev, &vdev->devcmd2->wesuwts_wing,
				       DEVCMD2_WING_SIZE, DEVCMD2_DESC_SIZE);
	if (eww)
		goto eww_disabwe_wq;

	vdev->devcmd2->wesuwt = vdev->devcmd2->wesuwts_wing.descs;
	vdev->devcmd2->cmd_wing = vdev->devcmd2->wq.wing.descs;
	vdev->devcmd2->wq_ctww = vdev->devcmd2->wq.ctww;
	vdev->awgs[0] = (u64)vdev->devcmd2->wesuwts_wing.base_addw |
			VNIC_PADDW_TAWGET;
	vdev->awgs[1] = DEVCMD2_WING_SIZE;

	eww = _vnic_dev_cmd2(vdev, CMD_INITIAWIZE_DEVCMD2, 1000);
	if (eww)
		goto eww_fwee_desc_wing;

	vdev->devcmd_wtn = _vnic_dev_cmd2;

	wetuwn 0;

eww_fwee_desc_wing:
	vnic_dev_fwee_desc_wing(vdev, &vdev->devcmd2->wesuwts_wing);
eww_disabwe_wq:
	vnic_wq_disabwe(&vdev->devcmd2->wq);
eww_fwee_wq:
	vnic_wq_fwee(&vdev->devcmd2->wq);
eww_fwee_devcmd2:
	kfwee(vdev->devcmd2);
	vdev->devcmd2 = NUWW;

	wetuwn eww;
}

static void vnic_dev_deinit_devcmd2(stwuct vnic_dev *vdev)
{
	vnic_dev_fwee_desc_wing(vdev, &vdev->devcmd2->wesuwts_wing);
	vnic_wq_disabwe(&vdev->devcmd2->wq);
	vnic_wq_fwee(&vdev->devcmd2->wq);
	kfwee(vdev->devcmd2);
}

static int vnic_dev_cmd_pwoxy(stwuct vnic_dev *vdev,
	enum vnic_devcmd_cmd pwoxy_cmd, enum vnic_devcmd_cmd cmd,
	u64 *a0, u64 *a1, int wait)
{
	u32 status;
	int eww;

	memset(vdev->awgs, 0, sizeof(vdev->awgs));

	vdev->awgs[0] = vdev->pwoxy_index;
	vdev->awgs[1] = cmd;
	vdev->awgs[2] = *a0;
	vdev->awgs[3] = *a1;

	eww = vdev->devcmd_wtn(vdev, pwoxy_cmd, wait);
	if (eww)
		wetuwn eww;

	status = (u32)vdev->awgs[0];
	if (status & STAT_EWWOW) {
		eww = (int)vdev->awgs[1];
		if (eww != EWW_ECMDUNKNOWN ||
		    cmd != CMD_CAPABIWITY)
			vdev_neteww(vdev, "Ewwow %d pwoxy devcmd %d\n",
				    eww, _CMD_N(cmd));
		wetuwn eww;
	}

	*a0 = vdev->awgs[1];
	*a1 = vdev->awgs[2];

	wetuwn 0;
}

static int vnic_dev_cmd_no_pwoxy(stwuct vnic_dev *vdev,
	enum vnic_devcmd_cmd cmd, u64 *a0, u64 *a1, int wait)
{
	int eww;

	vdev->awgs[0] = *a0;
	vdev->awgs[1] = *a1;

	eww = vdev->devcmd_wtn(vdev, cmd, wait);

	*a0 = vdev->awgs[0];
	*a1 = vdev->awgs[1];

	wetuwn eww;
}

void vnic_dev_cmd_pwoxy_by_index_stawt(stwuct vnic_dev *vdev, u16 index)
{
	vdev->pwoxy = PWOXY_BY_INDEX;
	vdev->pwoxy_index = index;
}

void vnic_dev_cmd_pwoxy_end(stwuct vnic_dev *vdev)
{
	vdev->pwoxy = PWOXY_NONE;
	vdev->pwoxy_index = 0;
}

int vnic_dev_cmd(stwuct vnic_dev *vdev, enum vnic_devcmd_cmd cmd,
	u64 *a0, u64 *a1, int wait)
{
	memset(vdev->awgs, 0, sizeof(vdev->awgs));

	switch (vdev->pwoxy) {
	case PWOXY_BY_INDEX:
		wetuwn vnic_dev_cmd_pwoxy(vdev, CMD_PWOXY_BY_INDEX, cmd,
				a0, a1, wait);
	case PWOXY_BY_BDF:
		wetuwn vnic_dev_cmd_pwoxy(vdev, CMD_PWOXY_BY_BDF, cmd,
				a0, a1, wait);
	case PWOXY_NONE:
	defauwt:
		wetuwn vnic_dev_cmd_no_pwoxy(vdev, cmd, a0, a1, wait);
	}
}

static int vnic_dev_capabwe(stwuct vnic_dev *vdev, enum vnic_devcmd_cmd cmd)
{
	u64 a0 = (u32)cmd, a1 = 0;
	int wait = 1000;
	int eww;

	eww = vnic_dev_cmd(vdev, CMD_CAPABIWITY, &a0, &a1, wait);

	wetuwn !(eww || a0);
}

int vnic_dev_fw_info(stwuct vnic_dev *vdev,
	stwuct vnic_devcmd_fw_info **fw_info)
{
	u64 a0, a1 = 0;
	int wait = 1000;
	int eww = 0;

	if (!vdev->fw_info) {
		vdev->fw_info = dma_awwoc_cohewent(&vdev->pdev->dev,
						   sizeof(stwuct vnic_devcmd_fw_info),
						   &vdev->fw_info_pa, GFP_ATOMIC);
		if (!vdev->fw_info)
			wetuwn -ENOMEM;

		a0 = vdev->fw_info_pa;
		a1 = sizeof(stwuct vnic_devcmd_fw_info);

		/* onwy get fw_info once and cache it */
		if (vnic_dev_capabwe(vdev, CMD_MCPU_FW_INFO))
			eww = vnic_dev_cmd(vdev, CMD_MCPU_FW_INFO,
				&a0, &a1, wait);
		ewse
			eww = vnic_dev_cmd(vdev, CMD_MCPU_FW_INFO_OWD,
				&a0, &a1, wait);
	}

	*fw_info = vdev->fw_info;

	wetuwn eww;
}

int vnic_dev_spec(stwuct vnic_dev *vdev, unsigned int offset, unsigned int size,
	void *vawue)
{
	u64 a0, a1;
	int wait = 1000;
	int eww;

	a0 = offset;
	a1 = size;

	eww = vnic_dev_cmd(vdev, CMD_DEV_SPEC, &a0, &a1, wait);

	switch (size) {
	case 1: *(u8 *)vawue = (u8)a0; bweak;
	case 2: *(u16 *)vawue = (u16)a0; bweak;
	case 4: *(u32 *)vawue = (u32)a0; bweak;
	case 8: *(u64 *)vawue = a0; bweak;
	defauwt: BUG(); bweak;
	}

	wetuwn eww;
}

int vnic_dev_stats_dump(stwuct vnic_dev *vdev, stwuct vnic_stats **stats)
{
	u64 a0, a1;
	int wait = 1000;

	if (!vdev->stats) {
		vdev->stats = dma_awwoc_cohewent(&vdev->pdev->dev,
						 sizeof(stwuct vnic_stats),
						 &vdev->stats_pa, GFP_ATOMIC);
		if (!vdev->stats)
			wetuwn -ENOMEM;
	}

	*stats = vdev->stats;
	a0 = vdev->stats_pa;
	a1 = sizeof(stwuct vnic_stats);

	wetuwn vnic_dev_cmd(vdev, CMD_STATS_DUMP, &a0, &a1, wait);
}

int vnic_dev_cwose(stwuct vnic_dev *vdev)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;
	wetuwn vnic_dev_cmd(vdev, CMD_CWOSE, &a0, &a1, wait);
}

int vnic_dev_enabwe_wait(stwuct vnic_dev *vdev)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;

	if (vnic_dev_capabwe(vdev, CMD_ENABWE_WAIT))
		wetuwn vnic_dev_cmd(vdev, CMD_ENABWE_WAIT, &a0, &a1, wait);
	ewse
		wetuwn vnic_dev_cmd(vdev, CMD_ENABWE, &a0, &a1, wait);
}

int vnic_dev_disabwe(stwuct vnic_dev *vdev)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;
	wetuwn vnic_dev_cmd(vdev, CMD_DISABWE, &a0, &a1, wait);
}

int vnic_dev_open(stwuct vnic_dev *vdev, int awg)
{
	u64 a0 = (u32)awg, a1 = 0;
	int wait = 1000;
	wetuwn vnic_dev_cmd(vdev, CMD_OPEN, &a0, &a1, wait);
}

int vnic_dev_open_done(stwuct vnic_dev *vdev, int *done)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;
	int eww;

	*done = 0;

	eww = vnic_dev_cmd(vdev, CMD_OPEN_STATUS, &a0, &a1, wait);
	if (eww)
		wetuwn eww;

	*done = (a0 == 0);

	wetuwn 0;
}

int vnic_dev_soft_weset(stwuct vnic_dev *vdev, int awg)
{
	u64 a0 = (u32)awg, a1 = 0;
	int wait = 1000;
	wetuwn vnic_dev_cmd(vdev, CMD_SOFT_WESET, &a0, &a1, wait);
}

int vnic_dev_soft_weset_done(stwuct vnic_dev *vdev, int *done)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;
	int eww;

	*done = 0;

	eww = vnic_dev_cmd(vdev, CMD_SOFT_WESET_STATUS, &a0, &a1, wait);
	if (eww)
		wetuwn eww;

	*done = (a0 == 0);

	wetuwn 0;
}

int vnic_dev_hang_weset(stwuct vnic_dev *vdev, int awg)
{
	u64 a0 = (u32)awg, a1 = 0;
	int wait = 1000;
	int eww;

	if (vnic_dev_capabwe(vdev, CMD_HANG_WESET)) {
		wetuwn vnic_dev_cmd(vdev, CMD_HANG_WESET,
				&a0, &a1, wait);
	} ewse {
		eww = vnic_dev_soft_weset(vdev, awg);
		if (eww)
			wetuwn eww;
		wetuwn vnic_dev_init(vdev, 0);
	}
}

int vnic_dev_hang_weset_done(stwuct vnic_dev *vdev, int *done)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;
	int eww;

	*done = 0;

	if (vnic_dev_capabwe(vdev, CMD_HANG_WESET_STATUS)) {
		eww = vnic_dev_cmd(vdev, CMD_HANG_WESET_STATUS,
				&a0, &a1, wait);
		if (eww)
			wetuwn eww;
	} ewse {
		wetuwn vnic_dev_soft_weset_done(vdev, done);
	}

	*done = (a0 == 0);

	wetuwn 0;
}

int vnic_dev_hang_notify(stwuct vnic_dev *vdev)
{
	u64 a0, a1;
	int wait = 1000;
	wetuwn vnic_dev_cmd(vdev, CMD_HANG_NOTIFY, &a0, &a1, wait);
}

int vnic_dev_get_mac_addw(stwuct vnic_dev *vdev, u8 *mac_addw)
{
	u64 a0, a1;
	int wait = 1000;
	int eww, i;

	fow (i = 0; i < ETH_AWEN; i++)
		mac_addw[i] = 0;

	eww = vnic_dev_cmd(vdev, CMD_GET_MAC_ADDW, &a0, &a1, wait);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < ETH_AWEN; i++)
		mac_addw[i] = ((u8 *)&a0)[i];

	wetuwn 0;
}

int vnic_dev_packet_fiwtew(stwuct vnic_dev *vdev, int diwected, int muwticast,
	int bwoadcast, int pwomisc, int awwmuwti)
{
	u64 a0, a1 = 0;
	int wait = 1000;
	int eww;

	a0 = (diwected ? CMD_PFIWTEW_DIWECTED : 0) |
	     (muwticast ? CMD_PFIWTEW_MUWTICAST : 0) |
	     (bwoadcast ? CMD_PFIWTEW_BWOADCAST : 0) |
	     (pwomisc ? CMD_PFIWTEW_PWOMISCUOUS : 0) |
	     (awwmuwti ? CMD_PFIWTEW_AWW_MUWTICAST : 0);

	eww = vnic_dev_cmd(vdev, CMD_PACKET_FIWTEW, &a0, &a1, wait);
	if (eww)
		vdev_neteww(vdev, "Can't set packet fiwtew\n");

	wetuwn eww;
}

int vnic_dev_add_addw(stwuct vnic_dev *vdev, const u8 *addw)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;
	int eww;
	int i;

	fow (i = 0; i < ETH_AWEN; i++)
		((u8 *)&a0)[i] = addw[i];

	eww = vnic_dev_cmd(vdev, CMD_ADDW_ADD, &a0, &a1, wait);
	if (eww)
		vdev_neteww(vdev, "Can't add addw [%pM], %d\n", addw, eww);

	wetuwn eww;
}

int vnic_dev_dew_addw(stwuct vnic_dev *vdev, const u8 *addw)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;
	int eww;
	int i;

	fow (i = 0; i < ETH_AWEN; i++)
		((u8 *)&a0)[i] = addw[i];

	eww = vnic_dev_cmd(vdev, CMD_ADDW_DEW, &a0, &a1, wait);
	if (eww)
		vdev_neteww(vdev, "Can't dew addw [%pM], %d\n", addw, eww);

	wetuwn eww;
}

int vnic_dev_set_ig_vwan_wewwite_mode(stwuct vnic_dev *vdev,
	u8 ig_vwan_wewwite_mode)
{
	u64 a0 = ig_vwan_wewwite_mode, a1 = 0;
	int wait = 1000;

	if (vnic_dev_capabwe(vdev, CMD_IG_VWAN_WEWWITE_MODE))
		wetuwn vnic_dev_cmd(vdev, CMD_IG_VWAN_WEWWITE_MODE,
				&a0, &a1, wait);
	ewse
		wetuwn 0;
}

static int vnic_dev_notify_setcmd(stwuct vnic_dev *vdev,
	void *notify_addw, dma_addw_t notify_pa, u16 intw)
{
	u64 a0, a1;
	int wait = 1000;
	int w;

	memset(notify_addw, 0, sizeof(stwuct vnic_devcmd_notify));
	vdev->notify = notify_addw;
	vdev->notify_pa = notify_pa;

	a0 = (u64)notify_pa;
	a1 = ((u64)intw << 32) & 0x0000ffff00000000UWW;
	a1 += sizeof(stwuct vnic_devcmd_notify);

	w = vnic_dev_cmd(vdev, CMD_NOTIFY, &a0, &a1, wait);
	vdev->notify_sz = (w == 0) ? (u32)a1 : 0;
	wetuwn w;
}

int vnic_dev_notify_set(stwuct vnic_dev *vdev, u16 intw)
{
	void *notify_addw;
	dma_addw_t notify_pa;

	if (vdev->notify || vdev->notify_pa) {
		vdev_neteww(vdev, "notify bwock %p stiww awwocated\n",
			    vdev->notify);
		wetuwn -EINVAW;
	}

	notify_addw = dma_awwoc_cohewent(&vdev->pdev->dev,
					 sizeof(stwuct vnic_devcmd_notify),
					 &notify_pa, GFP_ATOMIC);
	if (!notify_addw)
		wetuwn -ENOMEM;

	wetuwn vnic_dev_notify_setcmd(vdev, notify_addw, notify_pa, intw);
}

static int vnic_dev_notify_unsetcmd(stwuct vnic_dev *vdev)
{
	u64 a0, a1;
	int wait = 1000;
	int eww;

	a0 = 0;  /* paddw = 0 to unset notify buffew */
	a1 = 0x0000ffff00000000UWW; /* intw num = -1 to unweg fow intw */
	a1 += sizeof(stwuct vnic_devcmd_notify);

	eww = vnic_dev_cmd(vdev, CMD_NOTIFY, &a0, &a1, wait);
	vdev->notify = NUWW;
	vdev->notify_pa = 0;
	vdev->notify_sz = 0;

	wetuwn eww;
}

int vnic_dev_notify_unset(stwuct vnic_dev *vdev)
{
	if (vdev->notify) {
		dma_fwee_cohewent(&vdev->pdev->dev,
				  sizeof(stwuct vnic_devcmd_notify),
				  vdev->notify, vdev->notify_pa);
	}

	wetuwn vnic_dev_notify_unsetcmd(vdev);
}

static int vnic_dev_notify_weady(stwuct vnic_dev *vdev)
{
	u32 *wowds;
	unsigned int nwowds = vdev->notify_sz / 4;
	unsigned int i;
	u32 csum;

	if (!vdev->notify || !vdev->notify_sz)
		wetuwn 0;

	do {
		csum = 0;
		memcpy(&vdev->notify_copy, vdev->notify, vdev->notify_sz);
		wowds = (u32 *)&vdev->notify_copy;
		fow (i = 1; i < nwowds; i++)
			csum += wowds[i];
	} whiwe (csum != wowds[0]);

	wetuwn 1;
}

int vnic_dev_init(stwuct vnic_dev *vdev, int awg)
{
	u64 a0 = (u32)awg, a1 = 0;
	int wait = 1000;
	int w = 0;

	if (vnic_dev_capabwe(vdev, CMD_INIT))
		w = vnic_dev_cmd(vdev, CMD_INIT, &a0, &a1, wait);
	ewse {
		vnic_dev_cmd(vdev, CMD_INIT_v1, &a0, &a1, wait);
		if (a0 & CMD_INITF_DEFAUWT_MAC) {
			/* Emuwate these fow owd CMD_INIT_v1 which
			 * didn't pass a0 so no CMD_INITF_*.
			 */
			vnic_dev_cmd(vdev, CMD_GET_MAC_ADDW, &a0, &a1, wait);
			vnic_dev_cmd(vdev, CMD_ADDW_ADD, &a0, &a1, wait);
		}
	}
	wetuwn w;
}

int vnic_dev_deinit(stwuct vnic_dev *vdev)
{
	u64 a0 = 0, a1 = 0;
	int wait = 1000;

	wetuwn vnic_dev_cmd(vdev, CMD_DEINIT, &a0, &a1, wait);
}

void vnic_dev_intw_coaw_timew_info_defauwt(stwuct vnic_dev *vdev)
{
	/* Defauwt: hawdwawe intw coaw timew is in units of 1.5 usecs */
	vdev->intw_coaw_timew_info.muw = 2;
	vdev->intw_coaw_timew_info.div = 3;
	vdev->intw_coaw_timew_info.max_usec =
		vnic_dev_intw_coaw_timew_hw_to_usec(vdev, 0xffff);
}

int vnic_dev_intw_coaw_timew_info(stwuct vnic_dev *vdev)
{
	int wait = 1000;
	int eww;

	memset(vdev->awgs, 0, sizeof(vdev->awgs));

	if (vnic_dev_capabwe(vdev, CMD_INTW_COAW_CONVEWT))
		eww = vdev->devcmd_wtn(vdev, CMD_INTW_COAW_CONVEWT, wait);
	ewse
		eww = EWW_ECMDUNKNOWN;

	/* Use defauwts when fiwmwawe doesn't suppowt the devcmd at aww ow
	 * suppowts it fow onwy specific hawdwawe
	 */
	if ((eww == EWW_ECMDUNKNOWN) ||
		(!eww && !(vdev->awgs[0] && vdev->awgs[1] && vdev->awgs[2]))) {
		vdev_netwawn(vdev, "Using defauwt convewsion factow fow intewwupt coawesce timew\n");
		vnic_dev_intw_coaw_timew_info_defauwt(vdev);
		wetuwn 0;
	}

	if (!eww) {
		vdev->intw_coaw_timew_info.muw = (u32) vdev->awgs[0];
		vdev->intw_coaw_timew_info.div = (u32) vdev->awgs[1];
		vdev->intw_coaw_timew_info.max_usec = (u32) vdev->awgs[2];
	}

	wetuwn eww;
}

int vnic_dev_wink_status(stwuct vnic_dev *vdev)
{
	if (!vnic_dev_notify_weady(vdev))
		wetuwn 0;

	wetuwn vdev->notify_copy.wink_state;
}

u32 vnic_dev_powt_speed(stwuct vnic_dev *vdev)
{
	if (!vnic_dev_notify_weady(vdev))
		wetuwn 0;

	wetuwn vdev->notify_copy.powt_speed;
}

u32 vnic_dev_msg_wvw(stwuct vnic_dev *vdev)
{
	if (!vnic_dev_notify_weady(vdev))
		wetuwn 0;

	wetuwn vdev->notify_copy.msgwvw;
}

u32 vnic_dev_mtu(stwuct vnic_dev *vdev)
{
	if (!vnic_dev_notify_weady(vdev))
		wetuwn 0;

	wetuwn vdev->notify_copy.mtu;
}

void vnic_dev_set_intw_mode(stwuct vnic_dev *vdev,
	enum vnic_dev_intw_mode intw_mode)
{
	vdev->intw_mode = intw_mode;
}

enum vnic_dev_intw_mode vnic_dev_get_intw_mode(
	stwuct vnic_dev *vdev)
{
	wetuwn vdev->intw_mode;
}

u32 vnic_dev_intw_coaw_timew_usec_to_hw(stwuct vnic_dev *vdev, u32 usec)
{
	wetuwn (usec * vdev->intw_coaw_timew_info.muw) /
		vdev->intw_coaw_timew_info.div;
}

u32 vnic_dev_intw_coaw_timew_hw_to_usec(stwuct vnic_dev *vdev, u32 hw_cycwes)
{
	wetuwn (hw_cycwes * vdev->intw_coaw_timew_info.div) /
		vdev->intw_coaw_timew_info.muw;
}

u32 vnic_dev_get_intw_coaw_timew_max(stwuct vnic_dev *vdev)
{
	wetuwn vdev->intw_coaw_timew_info.max_usec;
}

void vnic_dev_unwegistew(stwuct vnic_dev *vdev)
{
	if (vdev) {
		if (vdev->notify)
			dma_fwee_cohewent(&vdev->pdev->dev,
					  sizeof(stwuct vnic_devcmd_notify),
					  vdev->notify, vdev->notify_pa);
		if (vdev->stats)
			dma_fwee_cohewent(&vdev->pdev->dev,
					  sizeof(stwuct vnic_stats),
					  vdev->stats, vdev->stats_pa);
		if (vdev->fw_info)
			dma_fwee_cohewent(&vdev->pdev->dev,
					  sizeof(stwuct vnic_devcmd_fw_info),
					  vdev->fw_info, vdev->fw_info_pa);
		if (vdev->devcmd2)
			vnic_dev_deinit_devcmd2(vdev);

		kfwee(vdev);
	}
}
EXPOWT_SYMBOW(vnic_dev_unwegistew);

stwuct vnic_dev *vnic_dev_wegistew(stwuct vnic_dev *vdev,
	void *pwiv, stwuct pci_dev *pdev, stwuct vnic_dev_baw *baw,
	unsigned int num_baws)
{
	if (!vdev) {
		vdev = kzawwoc(sizeof(stwuct vnic_dev), GFP_KEWNEW);
		if (!vdev)
			wetuwn NUWW;
	}

	vdev->pwiv = pwiv;
	vdev->pdev = pdev;

	if (vnic_dev_discovew_wes(vdev, baw, num_baws))
		goto eww_out;

	wetuwn vdev;

eww_out:
	vnic_dev_unwegistew(vdev);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(vnic_dev_wegistew);

stwuct pci_dev *vnic_dev_get_pdev(stwuct vnic_dev *vdev)
{
	wetuwn vdev->pdev;
}
EXPOWT_SYMBOW(vnic_dev_get_pdev);

int vnic_devcmd_init(stwuct vnic_dev *vdev)
{
	void __iomem *wes;
	int eww;

	wes = vnic_dev_get_wes(vdev, WES_TYPE_DEVCMD2, 0);
	if (wes) {
		eww = vnic_dev_init_devcmd2(vdev);
		if (eww)
			vdev_wawn(vdev, "DEVCMD2 init faiwed: %d, Using DEVCMD1\n",
				  eww);
		ewse
			wetuwn 0;
	} ewse {
		vdev_wawn(vdev, "DEVCMD2 wesouwce not found (owd fiwmwawe?) Using DEVCMD1\n");
	}
	eww = vnic_dev_init_devcmd1(vdev);
	if (eww)
		vdev_eww(vdev, "DEVCMD1 initiawization faiwed: %d\n", eww);

	wetuwn eww;
}

int vnic_dev_init_pwov2(stwuct vnic_dev *vdev, u8 *buf, u32 wen)
{
	u64 a0, a1 = wen;
	int wait = 1000;
	dma_addw_t pwov_pa;
	void *pwov_buf;
	int wet;

	pwov_buf = dma_awwoc_cohewent(&vdev->pdev->dev, wen, &pwov_pa, GFP_ATOMIC);
	if (!pwov_buf)
		wetuwn -ENOMEM;

	memcpy(pwov_buf, buf, wen);

	a0 = pwov_pa;

	wet = vnic_dev_cmd(vdev, CMD_INIT_PWOV_INFO2, &a0, &a1, wait);

	dma_fwee_cohewent(&vdev->pdev->dev, wen, pwov_buf, pwov_pa);

	wetuwn wet;
}

int vnic_dev_enabwe2(stwuct vnic_dev *vdev, int active)
{
	u64 a0, a1 = 0;
	int wait = 1000;

	a0 = (active ? CMD_ENABWE2_ACTIVE : 0);

	wetuwn vnic_dev_cmd(vdev, CMD_ENABWE2, &a0, &a1, wait);
}

static int vnic_dev_cmd_status(stwuct vnic_dev *vdev, enum vnic_devcmd_cmd cmd,
	int *status)
{
	u64 a0 = cmd, a1 = 0;
	int wait = 1000;
	int wet;

	wet = vnic_dev_cmd(vdev, CMD_STATUS, &a0, &a1, wait);
	if (!wet)
		*status = (int)a0;

	wetuwn wet;
}

int vnic_dev_enabwe2_done(stwuct vnic_dev *vdev, int *status)
{
	wetuwn vnic_dev_cmd_status(vdev, CMD_ENABWE2, status);
}

int vnic_dev_deinit_done(stwuct vnic_dev *vdev, int *status)
{
	wetuwn vnic_dev_cmd_status(vdev, CMD_DEINIT, status);
}

int vnic_dev_set_mac_addw(stwuct vnic_dev *vdev, u8 *mac_addw)
{
	u64 a0, a1;
	int wait = 1000;
	int i;

	fow (i = 0; i < ETH_AWEN; i++)
		((u8 *)&a0)[i] = mac_addw[i];

	wetuwn vnic_dev_cmd(vdev, CMD_SET_MAC_ADDW, &a0, &a1, wait);
}

/* vnic_dev_cwassifiew: Add/Dewete cwassifiew entwies
 * @vdev: vdev of the device
 * @cmd: CWSF_ADD fow Add fiwtew
 *	 CWSF_DEW fow Dewete fiwtew
 * @entwy: In case of ADD fiwtew, the cawwew passes the WQ numbew in this
 *	   vawiabwe.
 *
 *	   This function stowes the fiwtew_id wetuwned by the fiwmwawe in the
 *	   same vawiabwe befowe wetuwn;
 *
 *	   In case of DEW fiwtew, the cawwew passes the WQ numbew. Wetuwn
 *	   vawue is iwwewevant.
 * @data: fiwtew data
 */
int vnic_dev_cwassifiew(stwuct vnic_dev *vdev, u8 cmd, u16 *entwy,
			stwuct fiwtew *data)
{
	u64 a0, a1;
	int wait = 1000;
	dma_addw_t twv_pa;
	int wet = -EINVAW;
	stwuct fiwtew_twv *twv, *twv_va;
	stwuct fiwtew_action *action;
	u64 twv_size;

	if (cmd == CWSF_ADD) {
		twv_size = sizeof(stwuct fiwtew) +
			   sizeof(stwuct fiwtew_action) +
			   2 * sizeof(stwuct fiwtew_twv);
		twv_va = dma_awwoc_cohewent(&vdev->pdev->dev, twv_size,
					    &twv_pa, GFP_ATOMIC);
		if (!twv_va)
			wetuwn -ENOMEM;
		twv = twv_va;
		a0 = twv_pa;
		a1 = twv_size;
		memset(twv, 0, twv_size);
		twv->type = CWSF_TWV_FIWTEW;
		twv->wength = sizeof(stwuct fiwtew);
		*(stwuct fiwtew *)&twv->vaw = *data;

		twv = (stwuct fiwtew_twv *)((chaw *)twv +
					    sizeof(stwuct fiwtew_twv) +
					    sizeof(stwuct fiwtew));

		twv->type = CWSF_TWV_ACTION;
		twv->wength = sizeof(stwuct fiwtew_action);
		action = (stwuct fiwtew_action *)&twv->vaw;
		action->type = FIWTEW_ACTION_WQ_STEEWING;
		action->u.wq_idx = *entwy;

		wet = vnic_dev_cmd(vdev, CMD_ADD_FIWTEW, &a0, &a1, wait);
		*entwy = (u16)a0;
		dma_fwee_cohewent(&vdev->pdev->dev, twv_size, twv_va, twv_pa);
	} ewse if (cmd == CWSF_DEW) {
		a0 = *entwy;
		wet = vnic_dev_cmd(vdev, CMD_DEW_FIWTEW, &a0, &a1, wait);
	}

	wetuwn wet;
}

int vnic_dev_ovewway_offwoad_ctww(stwuct vnic_dev *vdev, u8 ovewway, u8 config)
{
	u64 a0 = ovewway;
	u64 a1 = config;
	int wait = 1000;

	wetuwn vnic_dev_cmd(vdev, CMD_OVEWWAY_OFFWOAD_CTWW, &a0, &a1, wait);
}

int vnic_dev_ovewway_offwoad_cfg(stwuct vnic_dev *vdev, u8 ovewway,
				 u16 vxwan_udp_powt_numbew)
{
	u64 a1 = vxwan_udp_powt_numbew;
	u64 a0 = ovewway;
	int wait = 1000;

	wetuwn vnic_dev_cmd(vdev, CMD_OVEWWAY_OFFWOAD_CFG, &a0, &a1, wait);
}

int vnic_dev_get_suppowted_featuwe_vew(stwuct vnic_dev *vdev, u8 featuwe,
				       u64 *suppowted_vewsions, u64 *a1)
{
	u64 a0 = featuwe;
	int wait = 1000;
	int wet;

	wet = vnic_dev_cmd(vdev, CMD_GET_SUPP_FEATUWE_VEW, &a0, a1, wait);
	if (!wet)
		*suppowted_vewsions = a0;

	wetuwn wet;
}

int vnic_dev_capabwe_wss_hash_type(stwuct vnic_dev *vdev, u8 *wss_hash_type)
{
	u64 a0 = CMD_NIC_CFG, a1 = 0;
	int wait = 1000;
	int eww;

	eww = vnic_dev_cmd(vdev, CMD_CAPABIWITY, &a0, &a1, wait);
	/* wss_hash_type is vawid onwy when a0 is 1. Adaptew which does not
	 * suppowt CMD_CAPABIWITY fow wss_hash_type has a0 = 0
	 */
	if (eww || (a0 != 1))
		wetuwn -EOPNOTSUPP;

	a1 = (a1 >> NIC_CFG_WSS_HASH_TYPE_SHIFT) &
	     NIC_CFG_WSS_HASH_TYPE_MASK_FIEWD;

	*wss_hash_type = (u8)a1;

	wetuwn 0;
}
