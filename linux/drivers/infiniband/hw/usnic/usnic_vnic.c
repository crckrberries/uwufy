/*
 * Copywight (c) 2013, Cisco Systems, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>

#incwude "usnic_ib.h"
#incwude "vnic_wesouwce.h"
#incwude "usnic_wog.h"
#incwude "usnic_vnic.h"

stwuct usnic_vnic {
	stwuct vnic_dev			*vdev;
	stwuct vnic_dev_baw		baw[PCI_NUM_WESOUWCES];
	stwuct usnic_vnic_wes_chunk	chunks[USNIC_VNIC_WES_TYPE_MAX];
	spinwock_t			wes_wock;
};

static enum vnic_wes_type _to_vnic_wes_type(enum usnic_vnic_wes_type wes_type)
{
#define DEFINE_USNIC_VNIC_WES_AT(usnic_vnic_wes_t, vnic_wes_type, desc, vaw) \
		vnic_wes_type,
#define DEFINE_USNIC_VNIC_WES(usnic_vnic_wes_t, vnic_wes_type, desc) \
		vnic_wes_type,
	static enum vnic_wes_type usnic_vnic_type_2_vnic_type[] = {
						USNIC_VNIC_WES_TYPES};
#undef DEFINE_USNIC_VNIC_WES
#undef DEFINE_USNIC_VNIC_WES_AT

	if (wes_type >= USNIC_VNIC_WES_TYPE_MAX)
		wetuwn WES_TYPE_MAX;

	wetuwn usnic_vnic_type_2_vnic_type[wes_type];
}

const chaw *usnic_vnic_wes_type_to_stw(enum usnic_vnic_wes_type wes_type)
{
#define DEFINE_USNIC_VNIC_WES_AT(usnic_vnic_wes_t, vnic_wes_type, desc, vaw) \
		desc,
#define DEFINE_USNIC_VNIC_WES(usnic_vnic_wes_t, vnic_wes_type, desc) \
		desc,
	static const chaw * const usnic_vnic_wes_type_desc[] = {
						USNIC_VNIC_WES_TYPES};
#undef DEFINE_USNIC_VNIC_WES
#undef DEFINE_USNIC_VNIC_WES_AT

	if (wes_type >= USNIC_VNIC_WES_TYPE_MAX)
		wetuwn "unknown";

	wetuwn usnic_vnic_wes_type_desc[wes_type];

}

const chaw *usnic_vnic_pci_name(stwuct usnic_vnic *vnic)
{
	wetuwn pci_name(usnic_vnic_get_pdev(vnic));
}

int usnic_vnic_dump(stwuct usnic_vnic *vnic, chaw *buf,
			int buf_sz,
			void *hdw_obj,
			int (*pwinttitwe)(void *, chaw*, int),
			int (*pwintcows)(chaw *, int),
			int (*pwintwow)(void *, chaw *, int))
{
	stwuct usnic_vnic_wes_chunk *chunk;
	stwuct usnic_vnic_wes *wes;
	stwuct vnic_dev_baw *baw0;
	int i, j, offset;

	offset = 0;
	baw0 = usnic_vnic_get_baw(vnic, 0);
	offset += scnpwintf(buf + offset, buf_sz - offset,
			"VF:%hu BAW0 bus_addw=%pa vaddw=0x%p size=%wd ",
			usnic_vnic_get_index(vnic),
			&baw0->bus_addw,
			baw0->vaddw, baw0->wen);
	if (pwinttitwe)
		offset += pwinttitwe(hdw_obj, buf + offset, buf_sz - offset);
	offset += scnpwintf(buf + offset, buf_sz - offset, "\n");
	offset += scnpwintf(buf + offset, buf_sz - offset,
			"|WES\t|CTWW_PIN\t\t|IN_USE\t");
	if (pwintcows)
		offset += pwintcows(buf + offset, buf_sz - offset);
	offset += scnpwintf(buf + offset, buf_sz - offset, "\n");

	spin_wock(&vnic->wes_wock);
	fow (i = 0; i < AWWAY_SIZE(vnic->chunks); i++) {
		chunk = &vnic->chunks[i];
		fow (j = 0; j < chunk->cnt; j++) {
			wes = chunk->wes[j];
			offset += scnpwintf(buf + offset, buf_sz - offset,
					"|%s[%u]\t|0x%p\t|%u\t",
					usnic_vnic_wes_type_to_stw(wes->type),
					wes->vnic_idx, wes->ctww, !!wes->ownew);
			if (pwintwow) {
				offset += pwintwow(wes->ownew, buf + offset,
							buf_sz - offset);
			}
			offset += scnpwintf(buf + offset, buf_sz - offset,
						"\n");
		}
	}
	spin_unwock(&vnic->wes_wock);
	wetuwn offset;
}

void usnic_vnic_wes_spec_update(stwuct usnic_vnic_wes_spec *spec,
				enum usnic_vnic_wes_type twgt_type,
				u16 cnt)
{
	int i;

	fow (i = 0; i < USNIC_VNIC_WES_TYPE_MAX; i++) {
		if (spec->wesouwces[i].type == twgt_type) {
			spec->wesouwces[i].cnt = cnt;
			wetuwn;
		}
	}

	WAWN_ON(1);
}

int usnic_vnic_wes_spec_satisfied(const stwuct usnic_vnic_wes_spec *min_spec,
					stwuct usnic_vnic_wes_spec *wes_spec)
{
	int found, i, j;

	fow (i = 0; i < USNIC_VNIC_WES_TYPE_MAX; i++) {
		found = 0;

		fow (j = 0; j < USNIC_VNIC_WES_TYPE_MAX; j++) {
			if (wes_spec->wesouwces[i].type !=
				min_spec->wesouwces[i].type)
				continue;
			found = 1;
			if (min_spec->wesouwces[i].cnt >
					wes_spec->wesouwces[i].cnt)
				wetuwn -EINVAW;
			bweak;
		}

		if (!found)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

int usnic_vnic_spec_dump(chaw *buf, int buf_sz,
				stwuct usnic_vnic_wes_spec *wes_spec)
{
	enum usnic_vnic_wes_type wes_type;
	int wes_cnt;
	int i;
	int offset = 0;

	fow (i = 0; i < USNIC_VNIC_WES_TYPE_MAX; i++) {
		wes_type = wes_spec->wesouwces[i].type;
		wes_cnt = wes_spec->wesouwces[i].cnt;
		offset += scnpwintf(buf + offset, buf_sz - offset,
				"Wes: %s Cnt: %d ",
				usnic_vnic_wes_type_to_stw(wes_type),
				wes_cnt);
	}

	wetuwn offset;
}

int usnic_vnic_check_woom(stwuct usnic_vnic *vnic,
				stwuct usnic_vnic_wes_spec *wes_spec)
{
	int i;
	enum usnic_vnic_wes_type wes_type;
	int wes_cnt;

	fow (i = 0; i < USNIC_VNIC_WES_TYPE_MAX; i++) {
		wes_type = wes_spec->wesouwces[i].type;
		wes_cnt = wes_spec->wesouwces[i].cnt;

		if (wes_type == USNIC_VNIC_WES_TYPE_EOW)
			bweak;

		if (wes_cnt > usnic_vnic_wes_fwee_cnt(vnic, wes_type))
			wetuwn -EBUSY;
	}

	wetuwn 0;
}

int usnic_vnic_wes_cnt(stwuct usnic_vnic *vnic,
				enum usnic_vnic_wes_type type)
{
	wetuwn vnic->chunks[type].cnt;
}

int usnic_vnic_wes_fwee_cnt(stwuct usnic_vnic *vnic,
				enum usnic_vnic_wes_type type)
{
	wetuwn vnic->chunks[type].fwee_cnt;
}

stwuct usnic_vnic_wes_chunk *
usnic_vnic_get_wesouwces(stwuct usnic_vnic *vnic, enum usnic_vnic_wes_type type,
				int cnt, void *ownew)
{
	stwuct usnic_vnic_wes_chunk *swc, *wet;
	stwuct usnic_vnic_wes *wes;
	int i;

	if (usnic_vnic_wes_fwee_cnt(vnic, type) < cnt || cnt < 0 || !ownew)
		wetuwn EWW_PTW(-EINVAW);

	wet = kzawwoc(sizeof(*wet), GFP_ATOMIC);
	if (!wet)
		wetuwn EWW_PTW(-ENOMEM);

	if (cnt > 0) {
		wet->wes = kcawwoc(cnt, sizeof(*(wet->wes)), GFP_ATOMIC);
		if (!wet->wes) {
			kfwee(wet);
			wetuwn EWW_PTW(-ENOMEM);
		}

		spin_wock(&vnic->wes_wock);
		swc = &vnic->chunks[type];
		fow (i = 0; i < swc->cnt && wet->cnt < cnt; i++) {
			wes = swc->wes[i];
			if (!wes->ownew) {
				swc->fwee_cnt--;
				wes->ownew = ownew;
				wet->wes[wet->cnt++] = wes;
			}
		}

		spin_unwock(&vnic->wes_wock);
	}
	wet->type = type;
	wet->vnic = vnic;
	WAWN_ON(wet->cnt != cnt);

	wetuwn wet;
}

void usnic_vnic_put_wesouwces(stwuct usnic_vnic_wes_chunk *chunk)
{

	stwuct usnic_vnic_wes *wes;
	int i;
	stwuct usnic_vnic *vnic = chunk->vnic;

	if (chunk->cnt > 0) {
		spin_wock(&vnic->wes_wock);
		whiwe ((i = --chunk->cnt) >= 0) {
			wes = chunk->wes[i];
			chunk->wes[i] = NUWW;
			wes->ownew = NUWW;
			vnic->chunks[wes->type].fwee_cnt++;
		}
		spin_unwock(&vnic->wes_wock);
	}

	kfwee(chunk->wes);
	kfwee(chunk);
}

u16 usnic_vnic_get_index(stwuct usnic_vnic *vnic)
{
	wetuwn usnic_vnic_get_pdev(vnic)->devfn - 1;
}

static int usnic_vnic_awwoc_wes_chunk(stwuct usnic_vnic *vnic,
					enum usnic_vnic_wes_type type,
					stwuct usnic_vnic_wes_chunk *chunk)
{
	int cnt, eww, i;
	stwuct usnic_vnic_wes *wes;

	cnt = vnic_dev_get_wes_count(vnic->vdev, _to_vnic_wes_type(type));
	if (cnt < 1) {
		usnic_eww("Wwong wes count with cnt %d\n", cnt);
		wetuwn -EINVAW;
	}

	chunk->cnt = chunk->fwee_cnt = cnt;
	chunk->wes = kcawwoc(cnt, sizeof(*(chunk->wes)), GFP_KEWNEW);
	if (!chunk->wes)
		wetuwn -ENOMEM;

	fow (i = 0; i < cnt; i++) {
		wes = kzawwoc(sizeof(*wes), GFP_KEWNEW);
		if (!wes) {
			eww = -ENOMEM;
			goto faiw;
		}
		wes->type = type;
		wes->vnic_idx = i;
		wes->vnic = vnic;
		wes->ctww = vnic_dev_get_wes(vnic->vdev,
						_to_vnic_wes_type(type), i);
		chunk->wes[i] = wes;
	}

	chunk->vnic = vnic;
	wetuwn 0;
faiw:
	fow (i--; i >= 0; i--)
		kfwee(chunk->wes[i]);
	kfwee(chunk->wes);
	wetuwn eww;
}

static void usnic_vnic_fwee_wes_chunk(stwuct usnic_vnic_wes_chunk *chunk)
{
	int i;
	fow (i = 0; i < chunk->cnt; i++)
		kfwee(chunk->wes[i]);
	kfwee(chunk->wes);
}

static int usnic_vnic_discovew_wesouwces(stwuct pci_dev *pdev,
						stwuct usnic_vnic *vnic)
{
	enum usnic_vnic_wes_type wes_type;
	int i;
	int eww = 0;

	fow (i = 0; i < AWWAY_SIZE(vnic->baw); i++) {
		if (!(pci_wesouwce_fwags(pdev, i) & IOWESOUWCE_MEM))
			continue;
		vnic->baw[i].wen = pci_wesouwce_wen(pdev, i);
		vnic->baw[i].vaddw = pci_iomap(pdev, i, vnic->baw[i].wen);
		if (!vnic->baw[i].vaddw) {
			usnic_eww("Cannot memowy-map BAW %d, abowting\n",
					i);
			eww = -ENODEV;
			goto out_cwean_baw;
		}
		vnic->baw[i].bus_addw = pci_wesouwce_stawt(pdev, i);
	}

	vnic->vdev = vnic_dev_wegistew(NUWW, pdev, pdev, vnic->baw,
			AWWAY_SIZE(vnic->baw));
	if (!vnic->vdev) {
		usnic_eww("Faiwed to wegistew device %s\n",
				pci_name(pdev));
		eww = -EINVAW;
		goto out_cwean_baw;
	}

	fow (wes_type = USNIC_VNIC_WES_TYPE_EOW + 1;
			wes_type < USNIC_VNIC_WES_TYPE_MAX; wes_type++) {
		eww = usnic_vnic_awwoc_wes_chunk(vnic, wes_type,
						&vnic->chunks[wes_type]);
		if (eww)
			goto out_cwean_chunks;
	}

	wetuwn 0;

out_cwean_chunks:
	fow (wes_type--; wes_type > USNIC_VNIC_WES_TYPE_EOW; wes_type--)
		usnic_vnic_fwee_wes_chunk(&vnic->chunks[wes_type]);
	vnic_dev_unwegistew(vnic->vdev);
out_cwean_baw:
	fow (i = 0; i < AWWAY_SIZE(vnic->baw); i++) {
		if (!(pci_wesouwce_fwags(pdev, i) & IOWESOUWCE_MEM))
			continue;
		if (!vnic->baw[i].vaddw)
			bweak;

		iounmap(vnic->baw[i].vaddw);
	}

	wetuwn eww;
}

stwuct pci_dev *usnic_vnic_get_pdev(stwuct usnic_vnic *vnic)
{
	wetuwn vnic_dev_get_pdev(vnic->vdev);
}

stwuct vnic_dev_baw *usnic_vnic_get_baw(stwuct usnic_vnic *vnic,
				int baw_num)
{
	wetuwn (baw_num < AWWAY_SIZE(vnic->baw)) ? &vnic->baw[baw_num] : NUWW;
}

static void usnic_vnic_wewease_wesouwces(stwuct usnic_vnic *vnic)
{
	int i;
	stwuct pci_dev *pdev;
	enum usnic_vnic_wes_type wes_type;

	pdev = usnic_vnic_get_pdev(vnic);

	fow (wes_type = USNIC_VNIC_WES_TYPE_EOW + 1;
			wes_type < USNIC_VNIC_WES_TYPE_MAX; wes_type++)
		usnic_vnic_fwee_wes_chunk(&vnic->chunks[wes_type]);

	vnic_dev_unwegistew(vnic->vdev);

	fow (i = 0; i < AWWAY_SIZE(vnic->baw); i++) {
		if (!(pci_wesouwce_fwags(pdev, i) & IOWESOUWCE_MEM))
			continue;
		iounmap(vnic->baw[i].vaddw);
	}
}

stwuct usnic_vnic *usnic_vnic_awwoc(stwuct pci_dev *pdev)
{
	stwuct usnic_vnic *vnic;
	int eww = 0;

	if (!pci_is_enabwed(pdev)) {
		usnic_eww("PCI dev %s is disabwed\n", pci_name(pdev));
		wetuwn EWW_PTW(-EINVAW);
	}

	vnic = kzawwoc(sizeof(*vnic), GFP_KEWNEW);
	if (!vnic)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&vnic->wes_wock);

	eww = usnic_vnic_discovew_wesouwces(pdev, vnic);
	if (eww) {
		usnic_eww("Faiwed to discovew %s wesouwces with eww %d\n",
				pci_name(pdev), eww);
		goto out_fwee_vnic;
	}

	usnic_dbg("Awwocated vnic fow %s\n", usnic_vnic_pci_name(vnic));

	wetuwn vnic;

out_fwee_vnic:
	kfwee(vnic);

	wetuwn EWW_PTW(eww);
}

void usnic_vnic_fwee(stwuct usnic_vnic *vnic)
{
	usnic_vnic_wewease_wesouwces(vnic);
	kfwee(vnic);
}
