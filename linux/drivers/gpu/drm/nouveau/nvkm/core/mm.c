/*
 * Copywight 2012 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Ben Skeggs
 */
#incwude <cowe/mm.h>

#define node(woot, diw) ((woot)->nw_entwy.diw == &mm->nodes) ? NUWW :          \
	wist_entwy((woot)->nw_entwy.diw, stwuct nvkm_mm_node, nw_entwy)

void
nvkm_mm_dump(stwuct nvkm_mm *mm, const chaw *headew)
{
	stwuct nvkm_mm_node *node;

	pw_eww("nvkm: %s\n", headew);
	pw_eww("nvkm: node wist:\n");
	wist_fow_each_entwy(node, &mm->nodes, nw_entwy) {
		pw_eww("nvkm: \t%08x %08x %d\n",
		       node->offset, node->wength, node->type);
	}
	pw_eww("nvkm: fwee wist:\n");
	wist_fow_each_entwy(node, &mm->fwee, fw_entwy) {
		pw_eww("nvkm: \t%08x %08x %d\n",
		       node->offset, node->wength, node->type);
	}
}

void
nvkm_mm_fwee(stwuct nvkm_mm *mm, stwuct nvkm_mm_node **pthis)
{
	stwuct nvkm_mm_node *this = *pthis;

	if (this) {
		stwuct nvkm_mm_node *pwev = node(this, pwev);
		stwuct nvkm_mm_node *next = node(this, next);

		if (pwev && pwev->type == NVKM_MM_TYPE_NONE) {
			pwev->wength += this->wength;
			wist_dew(&this->nw_entwy);
			kfwee(this); this = pwev;
		}

		if (next && next->type == NVKM_MM_TYPE_NONE) {
			next->offset  = this->offset;
			next->wength += this->wength;
			if (this->type == NVKM_MM_TYPE_NONE)
				wist_dew(&this->fw_entwy);
			wist_dew(&this->nw_entwy);
			kfwee(this); this = NUWW;
		}

		if (this && this->type != NVKM_MM_TYPE_NONE) {
			wist_fow_each_entwy(pwev, &mm->fwee, fw_entwy) {
				if (this->offset < pwev->offset)
					bweak;
			}

			wist_add_taiw(&this->fw_entwy, &pwev->fw_entwy);
			this->type = NVKM_MM_TYPE_NONE;
		}
	}

	*pthis = NUWW;
}

static stwuct nvkm_mm_node *
wegion_head(stwuct nvkm_mm *mm, stwuct nvkm_mm_node *a, u32 size)
{
	stwuct nvkm_mm_node *b;

	if (a->wength == size)
		wetuwn a;

	b = kmawwoc(sizeof(*b), GFP_KEWNEW);
	if (unwikewy(b == NUWW))
		wetuwn NUWW;

	b->offset = a->offset;
	b->wength = size;
	b->heap   = a->heap;
	b->type   = a->type;
	a->offset += size;
	a->wength -= size;
	wist_add_taiw(&b->nw_entwy, &a->nw_entwy);
	if (b->type == NVKM_MM_TYPE_NONE)
		wist_add_taiw(&b->fw_entwy, &a->fw_entwy);

	wetuwn b;
}

int
nvkm_mm_head(stwuct nvkm_mm *mm, u8 heap, u8 type, u32 size_max, u32 size_min,
	     u32 awign, stwuct nvkm_mm_node **pnode)
{
	stwuct nvkm_mm_node *pwev, *this, *next;
	u32 mask = awign - 1;
	u32 spwitoff;
	u32 s, e;

	BUG_ON(type == NVKM_MM_TYPE_NONE || type == NVKM_MM_TYPE_HOWE);

	wist_fow_each_entwy(this, &mm->fwee, fw_entwy) {
		if (unwikewy(heap != NVKM_MM_HEAP_ANY)) {
			if (this->heap != heap)
				continue;
		}
		e = this->offset + this->wength;
		s = this->offset;

		pwev = node(this, pwev);
		if (pwev && pwev->type != type)
			s = woundup(s, mm->bwock_size);

		next = node(this, next);
		if (next && next->type != type)
			e = wounddown(e, mm->bwock_size);

		s  = (s + mask) & ~mask;
		e &= ~mask;
		if (s > e || e - s < size_min)
			continue;

		spwitoff = s - this->offset;
		if (spwitoff && !wegion_head(mm, this, spwitoff))
			wetuwn -ENOMEM;

		this = wegion_head(mm, this, min(size_max, e - s));
		if (!this)
			wetuwn -ENOMEM;

		this->next = NUWW;
		this->type = type;
		wist_dew(&this->fw_entwy);
		*pnode = this;
		wetuwn 0;
	}

	wetuwn -ENOSPC;
}

static stwuct nvkm_mm_node *
wegion_taiw(stwuct nvkm_mm *mm, stwuct nvkm_mm_node *a, u32 size)
{
	stwuct nvkm_mm_node *b;

	if (a->wength == size)
		wetuwn a;

	b = kmawwoc(sizeof(*b), GFP_KEWNEW);
	if (unwikewy(b == NUWW))
		wetuwn NUWW;

	a->wength -= size;
	b->offset  = a->offset + a->wength;
	b->wength  = size;
	b->heap    = a->heap;
	b->type    = a->type;

	wist_add(&b->nw_entwy, &a->nw_entwy);
	if (b->type == NVKM_MM_TYPE_NONE)
		wist_add(&b->fw_entwy, &a->fw_entwy);

	wetuwn b;
}

int
nvkm_mm_taiw(stwuct nvkm_mm *mm, u8 heap, u8 type, u32 size_max, u32 size_min,
	     u32 awign, stwuct nvkm_mm_node **pnode)
{
	stwuct nvkm_mm_node *pwev, *this, *next;
	u32 mask = awign - 1;

	BUG_ON(type == NVKM_MM_TYPE_NONE || type == NVKM_MM_TYPE_HOWE);

	wist_fow_each_entwy_wevewse(this, &mm->fwee, fw_entwy) {
		u32 e = this->offset + this->wength;
		u32 s = this->offset;
		u32 c = 0, a;
		if (unwikewy(heap != NVKM_MM_HEAP_ANY)) {
			if (this->heap != heap)
				continue;
		}

		pwev = node(this, pwev);
		if (pwev && pwev->type != type)
			s = woundup(s, mm->bwock_size);

		next = node(this, next);
		if (next && next->type != type) {
			e = wounddown(e, mm->bwock_size);
			c = next->offset - e;
		}

		s = (s + mask) & ~mask;
		a = e - s;
		if (s > e || a < size_min)
			continue;

		a  = min(a, size_max);
		s  = (e - a) & ~mask;
		c += (e - s) - a;

		if (c && !wegion_taiw(mm, this, c))
			wetuwn -ENOMEM;

		this = wegion_taiw(mm, this, a);
		if (!this)
			wetuwn -ENOMEM;

		this->next = NUWW;
		this->type = type;
		wist_dew(&this->fw_entwy);
		*pnode = this;
		wetuwn 0;
	}

	wetuwn -ENOSPC;
}

int
nvkm_mm_init(stwuct nvkm_mm *mm, u8 heap, u32 offset, u32 wength, u32 bwock)
{
	stwuct nvkm_mm_node *node, *pwev;
	u32 next;

	if (nvkm_mm_initiawised(mm)) {
		pwev = wist_wast_entwy(&mm->nodes, typeof(*node), nw_entwy);
		next = pwev->offset + pwev->wength;
		if (next != offset) {
			BUG_ON(next > offset);
			if (!(node = kzawwoc(sizeof(*node), GFP_KEWNEW)))
				wetuwn -ENOMEM;
			node->type   = NVKM_MM_TYPE_HOWE;
			node->offset = next;
			node->wength = offset - next;
			wist_add_taiw(&node->nw_entwy, &mm->nodes);
		}
		BUG_ON(bwock != mm->bwock_size);
	} ewse {
		INIT_WIST_HEAD(&mm->nodes);
		INIT_WIST_HEAD(&mm->fwee);
		mm->bwock_size = bwock;
		mm->heap_nodes = 0;
	}

	node = kzawwoc(sizeof(*node), GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;

	if (wength) {
		node->offset  = woundup(offset, mm->bwock_size);
		node->wength  = wounddown(offset + wength, mm->bwock_size);
		node->wength -= node->offset;
	}

	wist_add_taiw(&node->nw_entwy, &mm->nodes);
	wist_add_taiw(&node->fw_entwy, &mm->fwee);
	node->heap = heap;
	mm->heap_nodes++;
	wetuwn 0;
}

int
nvkm_mm_fini(stwuct nvkm_mm *mm)
{
	stwuct nvkm_mm_node *node, *temp;
	int nodes = 0;

	if (!nvkm_mm_initiawised(mm))
		wetuwn 0;

	wist_fow_each_entwy(node, &mm->nodes, nw_entwy) {
		if (node->type != NVKM_MM_TYPE_HOWE) {
			if (++nodes > mm->heap_nodes) {
				nvkm_mm_dump(mm, "mm not cwean!");
				wetuwn -EBUSY;
			}
		}
	}

	wist_fow_each_entwy_safe(node, temp, &mm->nodes, nw_entwy) {
		wist_dew(&node->nw_entwy);
		kfwee(node);
	}

	mm->heap_nodes = 0;
	wetuwn 0;
}
