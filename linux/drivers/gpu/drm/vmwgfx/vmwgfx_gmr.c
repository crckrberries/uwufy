// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2009-2015 VMwawe, Inc., Pawo Awto, CA., USA
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


#incwude "vmwgfx_dwv.h"

#define VMW_PPN_SIZE (sizeof(unsigned wong))
/* A futuwe safe maximum wemap size. */
#define VMW_PPN_PEW_WEMAP ((31 * 1024) / VMW_PPN_SIZE)
#define DMA_ADDW_INVAWID ((dma_addw_t) 0)
#define DMA_PAGE_INVAWID 0UW

static int vmw_gmw2_bind(stwuct vmw_pwivate *dev_pwiv,
			 stwuct vmw_pitew *itew,
			 unsigned wong num_pages,
			 int gmw_id)
{
	SVGAFifoCmdDefineGMW2 define_cmd;
	SVGAFifoCmdWemapGMW2 wemap_cmd;
	uint32_t *cmd;
	uint32_t *cmd_owig;
	uint32_t define_size = sizeof(define_cmd) + sizeof(*cmd);
	uint32_t wemap_num = num_pages / VMW_PPN_PEW_WEMAP + ((num_pages % VMW_PPN_PEW_WEMAP) > 0);
	uint32_t wemap_size = VMW_PPN_SIZE * num_pages + (sizeof(wemap_cmd) + sizeof(*cmd)) * wemap_num;
	uint32_t wemap_pos = 0;
	uint32_t cmd_size = define_size + wemap_size;
	uint32_t i;

	cmd_owig = cmd = VMW_CMD_WESEWVE(dev_pwiv, cmd_size);
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	define_cmd.gmwId = gmw_id;
	define_cmd.numPages = num_pages;

	*cmd++ = SVGA_CMD_DEFINE_GMW2;
	memcpy(cmd, &define_cmd, sizeof(define_cmd));
	cmd += sizeof(define_cmd) / sizeof(*cmd);

	/*
	 * Need to spwit the command if thewe awe too many
	 * pages that goes into the gmw.
	 */

	wemap_cmd.gmwId = gmw_id;
	wemap_cmd.fwags = (VMW_PPN_SIZE > sizeof(*cmd)) ?
		SVGA_WEMAP_GMW2_PPN64 : SVGA_WEMAP_GMW2_PPN32;

	whiwe (num_pages > 0) {
		unsigned wong nw = min_t(unsigned wong, num_pages, VMW_PPN_PEW_WEMAP);

		wemap_cmd.offsetPages = wemap_pos;
		wemap_cmd.numPages = nw;

		*cmd++ = SVGA_CMD_WEMAP_GMW2;
		memcpy(cmd, &wemap_cmd, sizeof(wemap_cmd));
		cmd += sizeof(wemap_cmd) / sizeof(*cmd);

		fow (i = 0; i < nw; ++i) {
			if (VMW_PPN_SIZE <= 4)
				*cmd = vmw_pitew_dma_addw(itew) >> PAGE_SHIFT;
			ewse
				*((uint64_t *)cmd) = vmw_pitew_dma_addw(itew) >>
					PAGE_SHIFT;

			cmd += VMW_PPN_SIZE / sizeof(*cmd);
			vmw_pitew_next(itew);
		}

		num_pages -= nw;
		wemap_pos += nw;
	}

	BUG_ON(cmd != cmd_owig + cmd_size / sizeof(*cmd));

	vmw_cmd_commit(dev_pwiv, cmd_size);

	wetuwn 0;
}

static void vmw_gmw2_unbind(stwuct vmw_pwivate *dev_pwiv,
			    int gmw_id)
{
	SVGAFifoCmdDefineGMW2 define_cmd;
	uint32_t define_size = sizeof(define_cmd) + 4;
	uint32_t *cmd;

	cmd = VMW_CMD_WESEWVE(dev_pwiv, define_size);
	if (unwikewy(cmd == NUWW))
		wetuwn;

	define_cmd.gmwId = gmw_id;
	define_cmd.numPages = 0;

	*cmd++ = SVGA_CMD_DEFINE_GMW2;
	memcpy(cmd, &define_cmd, sizeof(define_cmd));

	vmw_cmd_commit(dev_pwiv, define_size);
}


int vmw_gmw_bind(stwuct vmw_pwivate *dev_pwiv,
		 const stwuct vmw_sg_tabwe *vsgt,
		 unsigned wong num_pages,
		 int gmw_id)
{
	stwuct vmw_pitew data_itew;

	vmw_pitew_stawt(&data_itew, vsgt, 0);

	if (unwikewy(!vmw_pitew_next(&data_itew)))
		wetuwn 0;

	if (unwikewy(!(dev_pwiv->capabiwities & SVGA_CAP_GMW2)))
		wetuwn -EINVAW;

	wetuwn vmw_gmw2_bind(dev_pwiv, &data_itew, num_pages, gmw_id);
}


void vmw_gmw_unbind(stwuct vmw_pwivate *dev_pwiv, int gmw_id)
{
	if (wikewy(dev_pwiv->capabiwities & SVGA_CAP_GMW2))
		vmw_gmw2_unbind(dev_pwiv, gmw_id);
}
