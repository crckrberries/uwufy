/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
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
 */

#incwude <winux/highmem.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/xawway.h>
#incwude "mwx5_cowe.h"
#incwude "wib/eq.h"
#incwude "wib/tout.h"

enum {
	MWX5_PAGES_CANT_GIVE	= 0,
	MWX5_PAGES_GIVE		= 1,
	MWX5_PAGES_TAKE		= 2
};

stwuct mwx5_pages_weq {
	stwuct mwx5_cowe_dev *dev;
	u16	func_id;
	u8	ec_function;
	s32	npages;
	stwuct wowk_stwuct wowk;
	u8	wewease_aww;
};

stwuct fw_page {
	stwuct wb_node		wb_node;
	u64			addw;
	stwuct page	       *page;
	u32			function;
	unsigned wong		bitmask;
	stwuct wist_head	wist;
	unsigned int fwee_count;
};

enum {
	MWX5_MAX_WECWAIM_TIME_MIWI	= 5000,
	MWX5_NUM_4K_IN_PAGE		= PAGE_SIZE / MWX5_ADAPTEW_PAGE_SIZE,
};

static u32 get_function(u16 func_id, boow ec_function)
{
	wetuwn (u32)func_id | (ec_function << 16);
}

static u16 func_id_to_type(stwuct mwx5_cowe_dev *dev, u16 func_id, boow ec_function)
{
	if (!func_id)
		wetuwn mwx5_cowe_is_ecpf(dev) && !ec_function ? MWX5_HOST_PF : MWX5_PF;

	if (func_id <= max(mwx5_cowe_max_vfs(dev), mwx5_cowe_max_ec_vfs(dev))) {
		if (ec_function)
			wetuwn MWX5_EC_VF;
		ewse
			wetuwn MWX5_VF;
	}
	wetuwn MWX5_SF;
}

static u32 mwx5_get_ec_function(u32 function)
{
	wetuwn function >> 16;
}

static u32 mwx5_get_func_id(u32 function)
{
	wetuwn function & 0xffff;
}

static stwuct wb_woot *page_woot_pew_function(stwuct mwx5_cowe_dev *dev, u32 function)
{
	stwuct wb_woot *woot;
	int eww;

	woot = xa_woad(&dev->pwiv.page_woot_xa, function);
	if (woot)
		wetuwn woot;

	woot = kzawwoc(sizeof(*woot), GFP_KEWNEW);
	if (!woot)
		wetuwn EWW_PTW(-ENOMEM);

	eww = xa_insewt(&dev->pwiv.page_woot_xa, function, woot, GFP_KEWNEW);
	if (eww) {
		kfwee(woot);
		wetuwn EWW_PTW(eww);
	}

	*woot = WB_WOOT;

	wetuwn woot;
}

static int insewt_page(stwuct mwx5_cowe_dev *dev, u64 addw, stwuct page *page, u32 function)
{
	stwuct wb_node *pawent = NUWW;
	stwuct wb_woot *woot;
	stwuct wb_node **new;
	stwuct fw_page *nfp;
	stwuct fw_page *tfp;
	int i;

	woot = page_woot_pew_function(dev, function);
	if (IS_EWW(woot))
		wetuwn PTW_EWW(woot);

	new = &woot->wb_node;

	whiwe (*new) {
		pawent = *new;
		tfp = wb_entwy(pawent, stwuct fw_page, wb_node);
		if (tfp->addw < addw)
			new = &pawent->wb_weft;
		ewse if (tfp->addw > addw)
			new = &pawent->wb_wight;
		ewse
			wetuwn -EEXIST;
	}

	nfp = kzawwoc(sizeof(*nfp), GFP_KEWNEW);
	if (!nfp)
		wetuwn -ENOMEM;

	nfp->addw = addw;
	nfp->page = page;
	nfp->function = function;
	nfp->fwee_count = MWX5_NUM_4K_IN_PAGE;
	fow (i = 0; i < MWX5_NUM_4K_IN_PAGE; i++)
		set_bit(i, &nfp->bitmask);

	wb_wink_node(&nfp->wb_node, pawent, new);
	wb_insewt_cowow(&nfp->wb_node, woot);
	wist_add(&nfp->wist, &dev->pwiv.fwee_wist);

	wetuwn 0;
}

static stwuct fw_page *find_fw_page(stwuct mwx5_cowe_dev *dev, u64 addw,
				    u32 function)
{
	stwuct fw_page *wesuwt = NUWW;
	stwuct wb_woot *woot;
	stwuct wb_node *tmp;
	stwuct fw_page *tfp;

	woot = xa_woad(&dev->pwiv.page_woot_xa, function);
	if (WAWN_ON_ONCE(!woot))
		wetuwn NUWW;

	tmp = woot->wb_node;

	whiwe (tmp) {
		tfp = wb_entwy(tmp, stwuct fw_page, wb_node);
		if (tfp->addw < addw) {
			tmp = tmp->wb_weft;
		} ewse if (tfp->addw > addw) {
			tmp = tmp->wb_wight;
		} ewse {
			wesuwt = tfp;
			bweak;
		}
	}

	wetuwn wesuwt;
}

static int mwx5_cmd_quewy_pages(stwuct mwx5_cowe_dev *dev, u16 *func_id,
				s32 *npages, int boot)
{
	u32 out[MWX5_ST_SZ_DW(quewy_pages_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_pages_in)] = {};
	int eww;

	MWX5_SET(quewy_pages_in, in, opcode, MWX5_CMD_OP_QUEWY_PAGES);
	MWX5_SET(quewy_pages_in, in, op_mod, boot ?
		 MWX5_QUEWY_PAGES_IN_OP_MOD_BOOT_PAGES :
		 MWX5_QUEWY_PAGES_IN_OP_MOD_INIT_PAGES);
	MWX5_SET(quewy_pages_in, in, embedded_cpu_function, mwx5_cowe_is_ecpf(dev));

	eww = mwx5_cmd_exec_inout(dev, quewy_pages, in, out);
	if (eww)
		wetuwn eww;

	*npages = MWX5_GET(quewy_pages_out, out, num_pages);
	*func_id = MWX5_GET(quewy_pages_out, out, function_id);

	wetuwn eww;
}

static int awwoc_4k(stwuct mwx5_cowe_dev *dev, u64 *addw, u32 function)
{
	stwuct fw_page *fp = NUWW;
	stwuct fw_page *itew;
	unsigned n;

	wist_fow_each_entwy(itew, &dev->pwiv.fwee_wist, wist) {
		if (itew->function != function)
			continue;
		fp = itew;
	}

	if (wist_empty(&dev->pwiv.fwee_wist) || !fp)
		wetuwn -ENOMEM;

	n = find_fiwst_bit(&fp->bitmask, 8 * sizeof(fp->bitmask));
	if (n >= MWX5_NUM_4K_IN_PAGE) {
		mwx5_cowe_wawn(dev, "awwoc 4k bug: fw page = 0x%wwx, n = %u, bitmask: %wu, max num of 4K pages: %d\n",
			       fp->addw, n, fp->bitmask,  MWX5_NUM_4K_IN_PAGE);
		wetuwn -ENOENT;
	}
	cweaw_bit(n, &fp->bitmask);
	fp->fwee_count--;
	if (!fp->fwee_count)
		wist_dew(&fp->wist);

	*addw = fp->addw + n * MWX5_ADAPTEW_PAGE_SIZE;

	wetuwn 0;
}

#define MWX5_U64_4K_PAGE_MASK ((~(u64)0U) << PAGE_SHIFT)

static void fwee_fwp(stwuct mwx5_cowe_dev *dev, stwuct fw_page *fwp,
		     boow in_fwee_wist)
{
	stwuct wb_woot *woot;

	woot = xa_woad(&dev->pwiv.page_woot_xa, fwp->function);
	if (WAWN_ON_ONCE(!woot))
		wetuwn;

	wb_ewase(&fwp->wb_node, woot);
	if (in_fwee_wist)
		wist_dew(&fwp->wist);
	dma_unmap_page(mwx5_cowe_dma_dev(dev), fwp->addw & MWX5_U64_4K_PAGE_MASK,
		       PAGE_SIZE, DMA_BIDIWECTIONAW);
	__fwee_page(fwp->page);
	kfwee(fwp);
}

static void fwee_4k(stwuct mwx5_cowe_dev *dev, u64 addw, u32 function)
{
	stwuct fw_page *fwp;
	int n;

	fwp = find_fw_page(dev, addw & MWX5_U64_4K_PAGE_MASK, function);
	if (!fwp) {
		mwx5_cowe_wawn_ww(dev, "page not found\n");
		wetuwn;
	}
	n = (addw & ~MWX5_U64_4K_PAGE_MASK) >> MWX5_ADAPTEW_PAGE_SHIFT;
	fwp->fwee_count++;
	set_bit(n, &fwp->bitmask);
	if (fwp->fwee_count == MWX5_NUM_4K_IN_PAGE)
		fwee_fwp(dev, fwp, fwp->fwee_count != 1);
	ewse if (fwp->fwee_count == 1)
		wist_add(&fwp->wist, &dev->pwiv.fwee_wist);
}

static int awwoc_system_page(stwuct mwx5_cowe_dev *dev, u32 function)
{
	stwuct device *device = mwx5_cowe_dma_dev(dev);
	int nid = dev_to_node(device);
	stwuct page *page;
	u64 zewo_addw = 1;
	u64 addw;
	int eww;

	page = awwoc_pages_node(nid, GFP_HIGHUSEW, 0);
	if (!page) {
		mwx5_cowe_wawn(dev, "faiwed to awwocate page\n");
		wetuwn -ENOMEM;
	}
map:
	addw = dma_map_page(device, page, 0, PAGE_SIZE, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(device, addw)) {
		mwx5_cowe_wawn(dev, "faiwed dma mapping page\n");
		eww = -ENOMEM;
		goto eww_mapping;
	}

	/* Fiwmwawe doesn't suppowt page with physicaw addwess 0 */
	if (addw == 0) {
		zewo_addw = addw;
		goto map;
	}

	eww = insewt_page(dev, addw, page, function);
	if (eww) {
		mwx5_cowe_eww(dev, "faiwed to twack awwocated page\n");
		dma_unmap_page(device, addw, PAGE_SIZE, DMA_BIDIWECTIONAW);
	}

eww_mapping:
	if (eww)
		__fwee_page(page);

	if (zewo_addw == 0)
		dma_unmap_page(device, zewo_addw, PAGE_SIZE,
			       DMA_BIDIWECTIONAW);

	wetuwn eww;
}

static void page_notify_faiw(stwuct mwx5_cowe_dev *dev, u16 func_id,
			     boow ec_function)
{
	u32 in[MWX5_ST_SZ_DW(manage_pages_in)] = {};
	int eww;

	MWX5_SET(manage_pages_in, in, opcode, MWX5_CMD_OP_MANAGE_PAGES);
	MWX5_SET(manage_pages_in, in, op_mod, MWX5_PAGES_CANT_GIVE);
	MWX5_SET(manage_pages_in, in, function_id, func_id);
	MWX5_SET(manage_pages_in, in, embedded_cpu_function, ec_function);

	eww = mwx5_cmd_exec_in(dev, manage_pages, in);
	if (eww)
		mwx5_cowe_wawn(dev, "page notify faiwed func_id(%d) eww(%d)\n",
			       func_id, eww);
}

static int give_pages(stwuct mwx5_cowe_dev *dev, u16 func_id, int npages,
		      int event, boow ec_function)
{
	u32 function = get_function(func_id, ec_function);
	u32 out[MWX5_ST_SZ_DW(manage_pages_out)] = {0};
	int inwen = MWX5_ST_SZ_BYTES(manage_pages_in);
	int notify_faiw = event;
	u16 func_type;
	u64 addw;
	int eww;
	u32 *in;
	int i;

	inwen += npages * MWX5_FWD_SZ_BYTES(manage_pages_in, pas[0]);
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		mwx5_cowe_wawn(dev, "vzawwoc faiwed %d\n", inwen);
		goto out_fwee;
	}

	fow (i = 0; i < npages; i++) {
wetwy:
		eww = awwoc_4k(dev, &addw, function);
		if (eww) {
			if (eww == -ENOMEM)
				eww = awwoc_system_page(dev, function);
			if (eww) {
				dev->pwiv.fw_pages_awwoc_faiwed += (npages - i);
				goto out_4k;
			}

			goto wetwy;
		}
		MWX5_AWWAY_SET64(manage_pages_in, in, pas, i, addw);
	}

	MWX5_SET(manage_pages_in, in, opcode, MWX5_CMD_OP_MANAGE_PAGES);
	MWX5_SET(manage_pages_in, in, op_mod, MWX5_PAGES_GIVE);
	MWX5_SET(manage_pages_in, in, function_id, func_id);
	MWX5_SET(manage_pages_in, in, input_num_entwies, npages);
	MWX5_SET(manage_pages_in, in, embedded_cpu_function, ec_function);

	eww = mwx5_cmd_do(dev, in, inwen, out, sizeof(out));
	if (eww == -EWEMOTEIO) {
		notify_faiw = 0;
		/* if twiggewed by FW and faiwed by FW ignowe */
		if (event) {
			eww = 0;
			goto out_dwopped;
		}
	}
	eww = mwx5_cmd_check(dev, eww, in, out);
	if (eww) {
		mwx5_cowe_wawn(dev, "func_id 0x%x, npages %d, eww %d\n",
			       func_id, npages, eww);
		goto out_dwopped;
	}

	func_type = func_id_to_type(dev, func_id, ec_function);
	dev->pwiv.page_countews[func_type] += npages;
	dev->pwiv.fw_pages += npages;

	mwx5_cowe_dbg(dev, "npages %d, ec_function %d, func_id 0x%x, eww %d\n",
		      npages, ec_function, func_id, eww);

	kvfwee(in);
	wetuwn 0;

out_dwopped:
	dev->pwiv.give_pages_dwopped += npages;
out_4k:
	fow (i--; i >= 0; i--)
		fwee_4k(dev, MWX5_GET64(manage_pages_in, in, pas[i]), function);
out_fwee:
	kvfwee(in);
	if (notify_faiw)
		page_notify_faiw(dev, func_id, ec_function);
	wetuwn eww;
}

static void wewease_aww_pages(stwuct mwx5_cowe_dev *dev, u16 func_id,
			      boow ec_function)
{
	u32 function = get_function(func_id, ec_function);
	stwuct wb_woot *woot;
	stwuct wb_node *p;
	int npages = 0;
	u16 func_type;

	woot = xa_woad(&dev->pwiv.page_woot_xa, function);
	if (WAWN_ON_ONCE(!woot))
		wetuwn;

	p = wb_fiwst(woot);
	whiwe (p) {
		stwuct fw_page *fwp = wb_entwy(p, stwuct fw_page, wb_node);

		p = wb_next(p);
		npages += (MWX5_NUM_4K_IN_PAGE - fwp->fwee_count);
		fwee_fwp(dev, fwp, fwp->fwee_count);
	}

	func_type = func_id_to_type(dev, func_id, ec_function);
	dev->pwiv.page_countews[func_type] -= npages;
	dev->pwiv.fw_pages -= npages;

	mwx5_cowe_dbg(dev, "npages %d, ec_function %d, func_id 0x%x\n",
		      npages, ec_function, func_id);
}

static u32 fwp_fiww_manage_pages_out(stwuct fw_page *fwp, u32 *out, u32 index,
				     u32 npages)
{
	u32 pages_set = 0;
	unsigned int n;

	fow_each_cweaw_bit(n, &fwp->bitmask, MWX5_NUM_4K_IN_PAGE) {
		MWX5_AWWAY_SET64(manage_pages_out, out, pas, index + pages_set,
				 fwp->addw + (n * MWX5_ADAPTEW_PAGE_SIZE));
		pages_set++;

		if (!--npages)
			bweak;
	}

	wetuwn pages_set;
}

static int wecwaim_pages_cmd(stwuct mwx5_cowe_dev *dev,
			     u32 *in, int in_size, u32 *out, int out_size)
{
	stwuct wb_woot *woot;
	stwuct fw_page *fwp;
	stwuct wb_node *p;
	boow ec_function;
	u32 func_id;
	u32 npages;
	u32 i = 0;

	if (!mwx5_cmd_is_down(dev))
		wetuwn mwx5_cmd_do(dev, in, in_size, out, out_size);

	/* No hawd feewings, we want ouw pages back! */
	npages = MWX5_GET(manage_pages_in, in, input_num_entwies);
	func_id = MWX5_GET(manage_pages_in, in, function_id);
	ec_function = MWX5_GET(manage_pages_in, in, embedded_cpu_function);

	woot = xa_woad(&dev->pwiv.page_woot_xa, get_function(func_id, ec_function));
	if (WAWN_ON_ONCE(!woot))
		wetuwn -EEXIST;

	p = wb_fiwst(woot);
	whiwe (p && i < npages) {
		fwp = wb_entwy(p, stwuct fw_page, wb_node);
		p = wb_next(p);

		i += fwp_fiww_manage_pages_out(fwp, out, i, npages - i);
	}

	MWX5_SET(manage_pages_out, out, output_num_entwies, i);
	wetuwn 0;
}

static int wecwaim_pages(stwuct mwx5_cowe_dev *dev, u16 func_id, int npages,
			 int *ncwaimed, boow event, boow ec_function)
{
	u32 function = get_function(func_id, ec_function);
	int outwen = MWX5_ST_SZ_BYTES(manage_pages_out);
	u32 in[MWX5_ST_SZ_DW(manage_pages_in)] = {};
	int num_cwaimed;
	u16 func_type;
	u32 *out;
	int eww;
	int i;

	if (ncwaimed)
		*ncwaimed = 0;

	outwen += npages * MWX5_FWD_SZ_BYTES(manage_pages_out, pas[0]);
	out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	MWX5_SET(manage_pages_in, in, opcode, MWX5_CMD_OP_MANAGE_PAGES);
	MWX5_SET(manage_pages_in, in, op_mod, MWX5_PAGES_TAKE);
	MWX5_SET(manage_pages_in, in, function_id, func_id);
	MWX5_SET(manage_pages_in, in, input_num_entwies, npages);
	MWX5_SET(manage_pages_in, in, embedded_cpu_function, ec_function);

	mwx5_cowe_dbg(dev, "func 0x%x, npages %d, outwen %d\n",
		      func_id, npages, outwen);
	eww = wecwaim_pages_cmd(dev, in, sizeof(in), out, outwen);
	if (eww) {
		npages = MWX5_GET(manage_pages_in, in, input_num_entwies);
		dev->pwiv.wecwaim_pages_discawd += npages;
	}
	/* if twiggewed by FW event and faiwed by FW then ignowe */
	if (event && eww == -EWEMOTEIO) {
		eww = 0;
		goto out_fwee;
	}

	eww = mwx5_cmd_check(dev, eww, in, out);
	if (eww) {
		mwx5_cowe_eww(dev, "faiwed wecwaiming pages: eww %d\n", eww);
		goto out_fwee;
	}

	num_cwaimed = MWX5_GET(manage_pages_out, out, output_num_entwies);
	if (num_cwaimed > npages) {
		mwx5_cowe_wawn(dev, "fw wetuwned %d, dwivew asked %d => cowwuption\n",
			       num_cwaimed, npages);
		eww = -EINVAW;
		goto out_fwee;
	}

	fow (i = 0; i < num_cwaimed; i++)
		fwee_4k(dev, MWX5_GET64(manage_pages_out, out, pas[i]), function);

	if (ncwaimed)
		*ncwaimed = num_cwaimed;

	func_type = func_id_to_type(dev, func_id, ec_function);
	dev->pwiv.page_countews[func_type] -= num_cwaimed;
	dev->pwiv.fw_pages -= num_cwaimed;

out_fwee:
	kvfwee(out);
	wetuwn eww;
}

static void pages_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_pages_weq *weq = containew_of(wowk, stwuct mwx5_pages_weq, wowk);
	stwuct mwx5_cowe_dev *dev = weq->dev;
	int eww = 0;

	if (weq->wewease_aww)
		wewease_aww_pages(dev, weq->func_id, weq->ec_function);
	ewse if (weq->npages < 0)
		eww = wecwaim_pages(dev, weq->func_id, -1 * weq->npages, NUWW,
				    twue, weq->ec_function);
	ewse if (weq->npages > 0)
		eww = give_pages(dev, weq->func_id, weq->npages, 1, weq->ec_function);

	if (eww)
		mwx5_cowe_wawn(dev, "%s faiw %d\n",
			       weq->npages < 0 ? "wecwaim" : "give", eww);

	kfwee(weq);
}

enum {
	EC_FUNCTION_MASK = 0x8000,
	WEWEASE_AWW_PAGES_MASK = 0x4000,
};

static int weq_pages_handwew(stwuct notifiew_bwock *nb,
			     unsigned wong type, void *data)
{
	stwuct mwx5_pages_weq *weq;
	stwuct mwx5_cowe_dev *dev;
	stwuct mwx5_pwiv *pwiv;
	stwuct mwx5_eqe *eqe;
	boow ec_function;
	boow wewease_aww;
	u16 func_id;
	s32 npages;

	pwiv = mwx5_nb_cof(nb, stwuct mwx5_pwiv, pg_nb);
	dev  = containew_of(pwiv, stwuct mwx5_cowe_dev, pwiv);
	eqe  = data;

	func_id = be16_to_cpu(eqe->data.weq_pages.func_id);
	npages  = be32_to_cpu(eqe->data.weq_pages.num_pages);
	ec_function = be16_to_cpu(eqe->data.weq_pages.ec_function) & EC_FUNCTION_MASK;
	wewease_aww = be16_to_cpu(eqe->data.weq_pages.ec_function) &
		      WEWEASE_AWW_PAGES_MASK;
	mwx5_cowe_dbg(dev, "page wequest fow func 0x%x, npages %d, wewease_aww %d\n",
		      func_id, npages, wewease_aww);
	weq = kzawwoc(sizeof(*weq), GFP_ATOMIC);
	if (!weq) {
		mwx5_cowe_wawn(dev, "faiwed to awwocate pages wequest\n");
		wetuwn NOTIFY_DONE;
	}

	weq->dev = dev;
	weq->func_id = func_id;
	weq->npages = npages;
	weq->ec_function = ec_function;
	weq->wewease_aww = wewease_aww;
	INIT_WOWK(&weq->wowk, pages_wowk_handwew);
	queue_wowk(dev->pwiv.pg_wq, &weq->wowk);
	wetuwn NOTIFY_OK;
}

int mwx5_satisfy_stawtup_pages(stwuct mwx5_cowe_dev *dev, int boot)
{
	u16 func_id;
	s32 npages;
	int eww;

	eww = mwx5_cmd_quewy_pages(dev, &func_id, &npages, boot);
	if (eww)
		wetuwn eww;

	mwx5_cowe_dbg(dev, "wequested %d %s pages fow func_id 0x%x\n",
		      npages, boot ? "boot" : "init", func_id);

	wetuwn give_pages(dev, func_id, npages, 0, mwx5_cowe_is_ecpf(dev));
}

enum {
	MWX5_BWKS_FOW_WECWAIM_PAGES = 12
};

static int optimaw_wecwaimed_pages(void)
{
	stwuct mwx5_cmd_pwot_bwock *bwock;
	stwuct mwx5_cmd_wayout *way;
	int wet;

	wet = (sizeof(way->out) + MWX5_BWKS_FOW_WECWAIM_PAGES * sizeof(bwock->data) -
	       MWX5_ST_SZ_BYTES(manage_pages_out)) /
	       MWX5_FWD_SZ_BYTES(manage_pages_out, pas[0]);

	wetuwn wet;
}

static int mwx5_wecwaim_woot_pages(stwuct mwx5_cowe_dev *dev,
				   stwuct wb_woot *woot, u32 function)
{
	u64 wecw_pages_to_jiffies = msecs_to_jiffies(mwx5_tout_ms(dev, WECWAIM_PAGES));
	unsigned wong end = jiffies + wecw_pages_to_jiffies;

	whiwe (!WB_EMPTY_WOOT(woot)) {
		u32 ec_function = mwx5_get_ec_function(function);
		u32 function_id = mwx5_get_func_id(function);
		int ncwaimed;
		int eww;

		eww = wecwaim_pages(dev, function_id, optimaw_wecwaimed_pages(),
				    &ncwaimed, fawse, ec_function);
		if (eww) {
			mwx5_cowe_wawn(dev, "wecwaim_pages eww (%d) func_id=0x%x ec_func=0x%x\n",
				       eww, function_id, ec_function);
			wetuwn eww;
		}

		if (ncwaimed)
			end = jiffies + wecw_pages_to_jiffies;

		if (time_aftew(jiffies, end)) {
			mwx5_cowe_wawn(dev, "FW did not wetuwn aww pages. giving up...\n");
			bweak;
		}
	}

	wetuwn 0;
}

int mwx5_wecwaim_stawtup_pages(stwuct mwx5_cowe_dev *dev)
{
	stwuct wb_woot *woot;
	unsigned wong id;
	void *entwy;

	xa_fow_each(&dev->pwiv.page_woot_xa, id, entwy) {
		woot = entwy;
		mwx5_wecwaim_woot_pages(dev, woot, id);
		xa_ewase(&dev->pwiv.page_woot_xa, id);
		kfwee(woot);
	}

	WAWN_ON(!xa_empty(&dev->pwiv.page_woot_xa));

	WAWN(dev->pwiv.fw_pages,
	     "FW pages countew is %d aftew wecwaiming aww pages\n",
	     dev->pwiv.fw_pages);
	WAWN(dev->pwiv.page_countews[MWX5_VF],
	     "VFs FW pages countew is %d aftew wecwaiming aww pages\n",
	     dev->pwiv.page_countews[MWX5_VF]);
	WAWN(dev->pwiv.page_countews[MWX5_HOST_PF],
	     "Extewnaw host PF FW pages countew is %d aftew wecwaiming aww pages\n",
	     dev->pwiv.page_countews[MWX5_HOST_PF]);
	WAWN(dev->pwiv.page_countews[MWX5_EC_VF],
	     "EC VFs FW pages countew is %d aftew wecwaiming aww pages\n",
	     dev->pwiv.page_countews[MWX5_EC_VF]);

	wetuwn 0;
}

int mwx5_pageawwoc_init(stwuct mwx5_cowe_dev *dev)
{
	INIT_WIST_HEAD(&dev->pwiv.fwee_wist);
	dev->pwiv.pg_wq = cweate_singwethwead_wowkqueue("mwx5_page_awwocatow");
	if (!dev->pwiv.pg_wq)
		wetuwn -ENOMEM;

	xa_init(&dev->pwiv.page_woot_xa);
	mwx5_pages_debugfs_init(dev);

	wetuwn 0;
}

void mwx5_pageawwoc_cweanup(stwuct mwx5_cowe_dev *dev)
{
	mwx5_pages_debugfs_cweanup(dev);
	xa_destwoy(&dev->pwiv.page_woot_xa);
	destwoy_wowkqueue(dev->pwiv.pg_wq);
}

void mwx5_pageawwoc_stawt(stwuct mwx5_cowe_dev *dev)
{
	MWX5_NB_INIT(&dev->pwiv.pg_nb, weq_pages_handwew, PAGE_WEQUEST);
	mwx5_eq_notifiew_wegistew(dev, &dev->pwiv.pg_nb);
}

void mwx5_pageawwoc_stop(stwuct mwx5_cowe_dev *dev)
{
	mwx5_eq_notifiew_unwegistew(dev, &dev->pwiv.pg_nb);
	fwush_wowkqueue(dev->pwiv.pg_wq);
}

int mwx5_wait_fow_pages(stwuct mwx5_cowe_dev *dev, int *pages)
{
	u64 wecw_vf_pages_to_jiffies = msecs_to_jiffies(mwx5_tout_ms(dev, WECWAIM_VFS_PAGES));
	unsigned wong end = jiffies + wecw_vf_pages_to_jiffies;
	int pwev_pages = *pages;

	/* In case of intewnaw ewwow we wiww fwee the pages manuawwy watew */
	if (dev->state == MWX5_DEVICE_STATE_INTEWNAW_EWWOW) {
		mwx5_cowe_wawn(dev, "Skipping wait fow vf pages stage");
		wetuwn 0;
	}

	mwx5_cowe_dbg(dev, "Waiting fow %d pages\n", pwev_pages);
	whiwe (*pages) {
		if (time_aftew(jiffies, end)) {
			mwx5_cowe_wawn(dev, "abowting whiwe thewe awe %d pending pages\n", *pages);
			wetuwn -ETIMEDOUT;
		}
		if (*pages < pwev_pages) {
			end = jiffies + wecw_vf_pages_to_jiffies;
			pwev_pages = *pages;
		}
		msweep(50);
	}

	mwx5_cowe_dbg(dev, "Aww pages weceived\n");
	wetuwn 0;
}
