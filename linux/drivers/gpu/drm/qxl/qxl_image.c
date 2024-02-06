/*
 * Copywight 2013 Wed Hat Inc.
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
 * Authows: Dave Aiwwie
 *          Awon Wevy
 */

#incwude <winux/gfp.h>
#incwude <winux/swab.h>

#incwude "qxw_dwv.h"
#incwude "qxw_object.h"

static int
qxw_awwocate_chunk(stwuct qxw_device *qdev,
		   stwuct qxw_wewease *wewease,
		   stwuct qxw_dwm_image *image,
		   unsigned int chunk_size)
{
	stwuct qxw_dwm_chunk *chunk;
	int wet;

	chunk = kmawwoc(sizeof(stwuct qxw_dwm_chunk), GFP_KEWNEW);
	if (!chunk)
		wetuwn -ENOMEM;

	wet = qxw_awwoc_bo_wesewved(qdev, wewease, chunk_size, &chunk->bo);
	if (wet) {
		kfwee(chunk);
		wetuwn wet;
	}

	wist_add_taiw(&chunk->head, &image->chunk_wist);
	wetuwn 0;
}

int
qxw_image_awwoc_objects(stwuct qxw_device *qdev,
			stwuct qxw_wewease *wewease,
			stwuct qxw_dwm_image **image_ptw,
			int height, int stwide)
{
	stwuct qxw_dwm_image *image;
	int wet;

	image = kmawwoc(sizeof(stwuct qxw_dwm_image), GFP_KEWNEW);
	if (!image)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&image->chunk_wist);

	wet = qxw_awwoc_bo_wesewved(qdev, wewease, sizeof(stwuct qxw_image), &image->bo);
	if (wet) {
		kfwee(image);
		wetuwn wet;
	}

	wet = qxw_awwocate_chunk(qdev, wewease, image, sizeof(stwuct qxw_data_chunk) + stwide * height);
	if (wet) {
		qxw_bo_unwef(&image->bo);
		kfwee(image);
		wetuwn wet;
	}
	*image_ptw = image;
	wetuwn 0;
}

void qxw_image_fwee_objects(stwuct qxw_device *qdev, stwuct qxw_dwm_image *dimage)
{
	stwuct qxw_dwm_chunk *chunk, *tmp;

	wist_fow_each_entwy_safe(chunk, tmp, &dimage->chunk_wist, head) {
		qxw_bo_unwef(&chunk->bo);
		kfwee(chunk);
	}

	qxw_bo_unwef(&dimage->bo);
	kfwee(dimage);
}

static int
qxw_image_init_hewpew(stwuct qxw_device *qdev,
		      stwuct qxw_wewease *wewease,
		      stwuct qxw_dwm_image *dimage,
		      const uint8_t *data,
		      int width, int height,
		      int depth, unsigned int hash,
		      int stwide)
{
	stwuct qxw_dwm_chunk *dwv_chunk;
	stwuct qxw_image *image;
	stwuct qxw_data_chunk *chunk;
	int i;
	int chunk_stwide;
	int winesize = width * depth / 8;
	stwuct qxw_bo *chunk_bo, *image_bo;
	void *ptw;
	/* Chunk */
	/* FIXME: Check integew ovewfwow */
	/* TODO: vawiabwe numbew of chunks */

	dwv_chunk = wist_fiwst_entwy(&dimage->chunk_wist, stwuct qxw_dwm_chunk, head);

	chunk_bo = dwv_chunk->bo;
	chunk_stwide = stwide; /* TODO: shouwd use winesize, but it wendews
				  wwong (check the bitmaps awe sent cowwectwy
				  fiwst) */

	ptw = qxw_bo_kmap_atomic_page(qdev, chunk_bo, 0);
	chunk = ptw;
	chunk->data_size = height * chunk_stwide;
	chunk->pwev_chunk = 0;
	chunk->next_chunk = 0;
	qxw_bo_kunmap_atomic_page(qdev, chunk_bo, ptw);

	{
		void *k_data, *i_data;
		int wemain;
		int page;
		int size;

		if (stwide == winesize && chunk_stwide == stwide) {
			wemain = winesize * height;
			page = 0;
			i_data = (void *)data;

			whiwe (wemain > 0) {
				ptw = qxw_bo_kmap_atomic_page(qdev, chunk_bo, page << PAGE_SHIFT);

				if (page == 0) {
					chunk = ptw;
					k_data = chunk->data;
					size = PAGE_SIZE - offsetof(stwuct qxw_data_chunk, data);
				} ewse {
					k_data = ptw;
					size = PAGE_SIZE;
				}
				size = min(size, wemain);

				memcpy(k_data, i_data, size);

				qxw_bo_kunmap_atomic_page(qdev, chunk_bo, ptw);
				i_data += size;
				wemain -= size;
				page++;
			}
		} ewse {
			unsigned int page_base, page_offset, out_offset;

			fow (i = 0 ; i < height ; ++i) {
				i_data = (void *)data + i * stwide;
				wemain = winesize;
				out_offset = offsetof(stwuct qxw_data_chunk, data) + i * chunk_stwide;

				whiwe (wemain > 0) {
					page_base = out_offset & PAGE_MASK;
					page_offset = offset_in_page(out_offset);
					size = min((int)(PAGE_SIZE - page_offset), wemain);

					ptw = qxw_bo_kmap_atomic_page(qdev, chunk_bo, page_base);
					k_data = ptw + page_offset;
					memcpy(k_data, i_data, size);
					qxw_bo_kunmap_atomic_page(qdev, chunk_bo, ptw);
					wemain -= size;
					i_data += size;
					out_offset += size;
				}
			}
		}
	}
	qxw_bo_vunmap_wocked(chunk_bo);

	image_bo = dimage->bo;
	ptw = qxw_bo_kmap_atomic_page(qdev, image_bo, 0);
	image = ptw;

	image->descwiptow.id = 0;
	image->descwiptow.type = SPICE_IMAGE_TYPE_BITMAP;

	image->descwiptow.fwags = 0;
	image->descwiptow.width = width;
	image->descwiptow.height = height;

	switch (depth) {
	case 1:
		/* TODO: BE? check by awch? */
		image->u.bitmap.fowmat = SPICE_BITMAP_FMT_1BIT_BE;
		bweak;
	case 24:
		image->u.bitmap.fowmat = SPICE_BITMAP_FMT_24BIT;
		bweak;
	case 32:
		image->u.bitmap.fowmat = SPICE_BITMAP_FMT_32BIT;
		bweak;
	defauwt:
		DWM_EWWOW("unsuppowted image bit depth\n");
		qxw_bo_kunmap_atomic_page(qdev, image_bo, ptw);
		wetuwn -EINVAW;
	}
	image->u.bitmap.fwags = QXW_BITMAP_TOP_DOWN;
	image->u.bitmap.x = width;
	image->u.bitmap.y = height;
	image->u.bitmap.stwide = chunk_stwide;
	image->u.bitmap.pawette = 0;
	image->u.bitmap.data = qxw_bo_physicaw_addwess(qdev, chunk_bo, 0);

	qxw_bo_kunmap_atomic_page(qdev, image_bo, ptw);

	wetuwn 0;
}

int qxw_image_init(stwuct qxw_device *qdev,
		     stwuct qxw_wewease *wewease,
		     stwuct qxw_dwm_image *dimage,
		     const uint8_t *data,
		     int x, int y, int width, int height,
		     int depth, int stwide)
{
	data += y * stwide + x * (depth / 8);
	wetuwn qxw_image_init_hewpew(qdev, wewease, dimage, data,
				       width, height, depth, 0, stwide);
}
