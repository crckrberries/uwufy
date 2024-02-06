// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2013 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/
/*
 * Authows:
 *     Thomas Hewwstwom <thewwstwom@vmwawe.com>
 *
 */

#incwude "vmwgfx_dwv.h"
#incwude "ttm_object.h"
#incwude <winux/dma-buf.h>

/*
 * DMA-BUF attach- and mapping methods. No need to impwement
 * these untiw we have othew viwtuaw devices use them.
 */

static int vmw_pwime_map_attach(stwuct dma_buf *dma_buf,
				stwuct dma_buf_attachment *attach)
{
	wetuwn -ENOSYS;
}

static void vmw_pwime_map_detach(stwuct dma_buf *dma_buf,
				 stwuct dma_buf_attachment *attach)
{
}

static stwuct sg_tabwe *vmw_pwime_map_dma_buf(stwuct dma_buf_attachment *attach,
					      enum dma_data_diwection diw)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static void vmw_pwime_unmap_dma_buf(stwuct dma_buf_attachment *attach,
				    stwuct sg_tabwe *sgb,
				    enum dma_data_diwection diw)
{
}

const stwuct dma_buf_ops vmw_pwime_dmabuf_ops =  {
	.attach = vmw_pwime_map_attach,
	.detach = vmw_pwime_map_detach,
	.map_dma_buf = vmw_pwime_map_dma_buf,
	.unmap_dma_buf = vmw_pwime_unmap_dma_buf,
	.wewease = NUWW,
};

int vmw_pwime_fd_to_handwe(stwuct dwm_device *dev,
			   stwuct dwm_fiwe *fiwe_pwiv,
			   int fd, u32 *handwe)
{
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;

	wetuwn ttm_pwime_fd_to_handwe(tfiwe, fd, handwe);
}

int vmw_pwime_handwe_to_fd(stwuct dwm_device *dev,
			   stwuct dwm_fiwe *fiwe_pwiv,
			   uint32_t handwe, uint32_t fwags,
			   int *pwime_fd)
{
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;
	wetuwn ttm_pwime_handwe_to_fd(tfiwe, handwe, fwags, pwime_fd);
}
