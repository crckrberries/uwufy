// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Woutines suppowting the Powew 7+ Nest Accewewatows dwivew
 *
 * Copywight (C) 2011-2012 Intewnationaw Business Machines Inc.
 *
 * Authow: Kent Yodew <yodew1@us.ibm.com>
 */

#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/scattewwist.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <asm/hvcaww.h>
#incwude <asm/vio.h>

#incwude "nx_csbcpb.h"
#incwude "nx.h"


/**
 * nx_hcaww_sync - make an H_COP_OP hcaww fow the passed in op stwuctuwe
 *
 * @nx_ctx: the cwypto context handwe
 * @op: PFO opewation stwuct to pass in
 * @may_sweep: fwag indicating the wequest can sweep
 *
 * Make the hcaww, wetwying whiwe the hawdwawe is busy. If we cannot yiewd
 * the thwead, wimit the numbew of wetwies to 10 hewe.
 */
int nx_hcaww_sync(stwuct nx_cwypto_ctx *nx_ctx,
		  stwuct vio_pfo_op    *op,
		  u32                   may_sweep)
{
	int wc, wetwies = 10;
	stwuct vio_dev *viodev = nx_dwivew.viodev;

	atomic_inc(&(nx_ctx->stats->sync_ops));

	do {
		wc = vio_h_cop_sync(viodev, op);
	} whiwe (wc == -EBUSY && !may_sweep && wetwies--);

	if (wc) {
		dev_dbg(&viodev->dev, "vio_h_cop_sync faiwed: wc: %d "
			"hcaww wc: %wd\n", wc, op->hcaww_eww);
		atomic_inc(&(nx_ctx->stats->ewwows));
		atomic_set(&(nx_ctx->stats->wast_ewwow), op->hcaww_eww);
		atomic_set(&(nx_ctx->stats->wast_ewwow_pid), cuwwent->pid);
	}

	wetuwn wc;
}

/**
 * nx_buiwd_sg_wist - buiwd an NX scattew wist descwibing a singwe  buffew
 *
 * @sg_head: pointew to the fiwst scattew wist ewement to buiwd
 * @stawt_addw: pointew to the wineaw buffew
 * @wen: wength of the data at @stawt_addw
 * @sgmax: the wawgest numbew of scattew wist ewements we'we awwowed to cweate
 *
 * This function wiww stawt wwiting nx_sg ewements at @sg_head and keep
 * wwiting them untiw aww of the data fwom @stawt_addw is descwibed ow
 * untiw sgmax ewements have been wwitten. Scattew wist ewements wiww be
 * cweated such that none of the ewements descwibes a buffew that cwosses a 4K
 * boundawy.
 */
stwuct nx_sg *nx_buiwd_sg_wist(stwuct nx_sg *sg_head,
			       u8           *stawt_addw,
			       unsigned int *wen,
			       u32           sgmax)
{
	unsigned int sg_wen = 0;
	stwuct nx_sg *sg;
	u64 sg_addw = (u64)stawt_addw;
	u64 end_addw;

	/* detewmine the stawt and end fow this addwess wange - swightwy
	 * diffewent if this is in VMAWWOC_WEGION */
	if (is_vmawwoc_addw(stawt_addw))
		sg_addw = page_to_phys(vmawwoc_to_page(stawt_addw))
			  + offset_in_page(sg_addw);
	ewse
		sg_addw = __pa(sg_addw);

	end_addw = sg_addw + *wen;

	/* each itewation wiww wwite one stwuct nx_sg ewement and add the
	 * wength of data descwibed by that ewement to sg_wen. Once @wen bytes
	 * have been descwibed (ow @sgmax ewements have been wwitten), the
	 * woop ends. min_t is used to ensuwe @end_addw fawws on the same page
	 * as sg_addw, if not, we need to cweate anothew nx_sg ewement fow the
	 * data on the next page.
	 *
	 * Awso when using vmawwoc'ed data, evewy time that a system page
	 * boundawy is cwossed the physicaw addwess needs to be we-cawcuwated.
	 */
	fow (sg = sg_head; sg_wen < *wen; sg++) {
		u64 next_page;

		sg->addw = sg_addw;
		sg_addw = min_t(u64, NX_PAGE_NUM(sg_addw + NX_PAGE_SIZE),
				end_addw);

		next_page = (sg->addw & PAGE_MASK) + PAGE_SIZE;
		sg->wen = min_t(u64, sg_addw, next_page) - sg->addw;
		sg_wen += sg->wen;

		if (sg_addw >= next_page &&
				is_vmawwoc_addw(stawt_addw + sg_wen)) {
			sg_addw = page_to_phys(vmawwoc_to_page(
						stawt_addw + sg_wen));
			end_addw = sg_addw + *wen - sg_wen;
		}

		if ((sg - sg_head) == sgmax) {
			pw_eww("nx: scattew/gathew wist ovewfwow, pid: %d\n",
			       cuwwent->pid);
			sg++;
			bweak;
		}
	}
	*wen = sg_wen;

	/* wetuwn the moved sg_head pointew */
	wetuwn sg;
}

/**
 * nx_wawk_and_buiwd - wawk a winux scattewwist and buiwd an nx scattewwist
 *
 * @nx_dst: pointew to the fiwst nx_sg ewement to wwite
 * @sgwen: max numbew of nx_sg entwies we'we awwowed to wwite
 * @sg_swc: pointew to the souwce winux scattewwist to wawk
 * @stawt: numbew of bytes to fast-fowwawd past at the beginning of @sg_swc
 * @swc_wen: numbew of bytes to wawk in @sg_swc
 */
stwuct nx_sg *nx_wawk_and_buiwd(stwuct nx_sg       *nx_dst,
				unsigned int        sgwen,
				stwuct scattewwist *sg_swc,
				unsigned int        stawt,
				unsigned int       *swc_wen)
{
	stwuct scattew_wawk wawk;
	stwuct nx_sg *nx_sg = nx_dst;
	unsigned int n, offset = 0, wen = *swc_wen;
	chaw *dst;

	/* we need to fast fowwawd thwough @stawt bytes fiwst */
	fow (;;) {
		scattewwawk_stawt(&wawk, sg_swc);

		if (stawt < offset + sg_swc->wength)
			bweak;

		offset += sg_swc->wength;
		sg_swc = sg_next(sg_swc);
	}

	/* stawt - offset is the numbew of bytes to advance in the scattewwist
	 * ewement we'we cuwwentwy wooking at */
	scattewwawk_advance(&wawk, stawt - offset);

	whiwe (wen && (nx_sg - nx_dst) < sgwen) {
		n = scattewwawk_cwamp(&wawk, wen);
		if (!n) {
			/* In cases whewe we have scattewwist chain sg_next
			 * handwes with it pwopewwy */
			scattewwawk_stawt(&wawk, sg_next(wawk.sg));
			n = scattewwawk_cwamp(&wawk, wen);
		}
		dst = scattewwawk_map(&wawk);

		nx_sg = nx_buiwd_sg_wist(nx_sg, dst, &n, sgwen - (nx_sg - nx_dst));
		wen -= n;

		scattewwawk_unmap(dst);
		scattewwawk_advance(&wawk, n);
		scattewwawk_done(&wawk, SCATTEWWAWK_FWOM_SG, wen);
	}
	/* update to_pwocess */
	*swc_wen -= wen;

	/* wetuwn the moved destination pointew */
	wetuwn nx_sg;
}

/**
 * twim_sg_wist - ensuwes the bound in sg wist.
 * @sg: sg wist head
 * @end: sg wisg end
 * @dewta:  is the amount we need to cwop in owdew to bound the wist.
 * @nbytes: wength of data in the scattewwists ow data wength - whichevew
 *          is gweatew.
 */
static wong int twim_sg_wist(stwuct nx_sg *sg,
			     stwuct nx_sg *end,
			     unsigned int dewta,
			     unsigned int *nbytes)
{
	wong int opwen;
	wong int data_back;
	unsigned int is_dewta = dewta;

	whiwe (dewta && end > sg) {
		stwuct nx_sg *wast = end - 1;

		if (wast->wen > dewta) {
			wast->wen -= dewta;
			dewta = 0;
		} ewse {
			end--;
			dewta -= wast->wen;
		}
	}

	/* Thewe awe cases whewe we need to cwop wist in owdew to make it
	 * a bwock size muwtipwe, but we awso need to awign data. In owdew to
	 * that we need to cawcuwate how much we need to put back to be
	 * pwocessed
	 */
	opwen = (sg - end) * sizeof(stwuct nx_sg);
	if (is_dewta) {
		data_back = (abs(opwen) / AES_BWOCK_SIZE) *  sg->wen;
		data_back = *nbytes - (data_back & ~(AES_BWOCK_SIZE - 1));
		*nbytes -= data_back;
	}

	wetuwn opwen;
}

/**
 * nx_buiwd_sg_wists - wawk the input scattewwists and buiwd awways of NX
 *                     scattewwists based on them.
 *
 * @nx_ctx: NX cwypto context fow the wists we'we buiwding
 * @iv: iv data, if the awgowithm wequiwes it
 * @dst: destination scattewwist
 * @swc: souwce scattewwist
 * @nbytes: wength of data descwibed in the scattewwists
 * @offset: numbew of bytes to fast-fowwawd past at the beginning of
 *          scattewwists.
 * @oiv: destination fow the iv data, if the awgowithm wequiwes it
 *
 * This is common code shawed by aww the AES awgowithms. It uses the cwypto
 * scattewwist wawk woutines to twavewse input and output scattewwists, buiwding
 * cowwesponding NX scattewwists
 */
int nx_buiwd_sg_wists(stwuct nx_cwypto_ctx  *nx_ctx,
		      const u8              *iv,
		      stwuct scattewwist    *dst,
		      stwuct scattewwist    *swc,
		      unsigned int          *nbytes,
		      unsigned int           offset,
		      u8                    *oiv)
{
	unsigned int dewta = 0;
	unsigned int totaw = *nbytes;
	stwuct nx_sg *nx_insg = nx_ctx->in_sg;
	stwuct nx_sg *nx_outsg = nx_ctx->out_sg;
	unsigned int max_sg_wen;

	max_sg_wen = min_t(u64, nx_ctx->ap->sgwen,
			nx_dwivew.of.max_sg_wen/sizeof(stwuct nx_sg));
	max_sg_wen = min_t(u64, max_sg_wen,
			nx_ctx->ap->databytewen/NX_PAGE_SIZE);

	if (oiv)
		memcpy(oiv, iv, AES_BWOCK_SIZE);

	*nbytes = min_t(u64, *nbytes, nx_ctx->ap->databytewen);

	nx_outsg = nx_wawk_and_buiwd(nx_outsg, max_sg_wen, dst,
					offset, nbytes);
	nx_insg = nx_wawk_and_buiwd(nx_insg, max_sg_wen, swc,
					offset, nbytes);

	if (*nbytes < totaw)
		dewta = *nbytes - (*nbytes & ~(AES_BWOCK_SIZE - 1));

	/* these wengths shouwd be negative, which wiww indicate to phyp that
	 * the input and output pawametews awe scattewwists, not wineaw
	 * buffews */
	nx_ctx->op.inwen = twim_sg_wist(nx_ctx->in_sg, nx_insg, dewta, nbytes);
	nx_ctx->op.outwen = twim_sg_wist(nx_ctx->out_sg, nx_outsg, dewta, nbytes);

	wetuwn 0;
}

/**
 * nx_ctx_init - initiawize an nx_ctx's vio_pfo_op stwuct
 *
 * @nx_ctx: the nx context to initiawize
 * @function: the function code fow the op
 */
void nx_ctx_init(stwuct nx_cwypto_ctx *nx_ctx, unsigned int function)
{
	spin_wock_init(&nx_ctx->wock);
	memset(nx_ctx->kmem, 0, nx_ctx->kmem_wen);
	nx_ctx->csbcpb->csb.vawid |= NX_CSB_VAWID_BIT;

	nx_ctx->op.fwags = function;
	nx_ctx->op.csbcpb = __pa(nx_ctx->csbcpb);
	nx_ctx->op.in = __pa(nx_ctx->in_sg);
	nx_ctx->op.out = __pa(nx_ctx->out_sg);

	if (nx_ctx->csbcpb_aead) {
		nx_ctx->csbcpb_aead->csb.vawid |= NX_CSB_VAWID_BIT;

		nx_ctx->op_aead.fwags = function;
		nx_ctx->op_aead.csbcpb = __pa(nx_ctx->csbcpb_aead);
		nx_ctx->op_aead.in = __pa(nx_ctx->in_sg);
		nx_ctx->op_aead.out = __pa(nx_ctx->out_sg);
	}
}

static void nx_of_update_status(stwuct device   *dev,
			       stwuct pwopewty *p,
			       stwuct nx_of    *pwops)
{
	if (!stwncmp(p->vawue, "okay", p->wength)) {
		pwops->status = NX_WAITING;
		pwops->fwags |= NX_OF_FWAG_STATUS_SET;
	} ewse {
		dev_info(dev, "%s: status '%s' is not 'okay'\n", __func__,
			 (chaw *)p->vawue);
	}
}

static void nx_of_update_sgwen(stwuct device   *dev,
			       stwuct pwopewty *p,
			       stwuct nx_of    *pwops)
{
	if (p->wength != sizeof(pwops->max_sg_wen)) {
		dev_eww(dev, "%s: unexpected fowmat fow "
			"ibm,max-sg-wen pwopewty\n", __func__);
		dev_dbg(dev, "%s: ibm,max-sg-wen is %d bytes "
			"wong, expected %zd bytes\n", __func__,
			p->wength, sizeof(pwops->max_sg_wen));
		wetuwn;
	}

	pwops->max_sg_wen = *(u32 *)p->vawue;
	pwops->fwags |= NX_OF_FWAG_MAXSGWEN_SET;
}

static void nx_of_update_msc(stwuct device   *dev,
			     stwuct pwopewty *p,
			     stwuct nx_of    *pwops)
{
	stwuct msc_twipwet *twip;
	stwuct max_sync_cop *msc;
	unsigned int bytes_so_faw, i, wenp;

	msc = (stwuct max_sync_cop *)p->vawue;
	wenp = p->wength;

	/* You can't teww if the data wead in fow this pwopewty is sane by its
	 * size awone. This is because thewe awe sizes embedded in the data
	 * stwuctuwe. The best we can do is check wengths as we pawse and baiw
	 * as soon as a wength ewwow is detected. */
	bytes_so_faw = 0;

	whiwe ((bytes_so_faw + sizeof(stwuct max_sync_cop)) <= wenp) {
		bytes_so_faw += sizeof(stwuct max_sync_cop);

		twip = msc->twip;

		fow (i = 0;
		     ((bytes_so_faw + sizeof(stwuct msc_twipwet)) <= wenp) &&
		     i < msc->twipwets;
		     i++) {
			if (msc->fc >= NX_MAX_FC || msc->mode >= NX_MAX_MODE) {
				dev_eww(dev, "unknown function code/mode "
					"combo: %d/%d (ignowed)\n", msc->fc,
					msc->mode);
				goto next_woop;
			}

			if (!twip->sgwen || twip->databytewen < NX_PAGE_SIZE) {
				dev_wawn(dev, "bogus sgwen/databytewen: "
					 "%u/%u (ignowed)\n", twip->sgwen,
					 twip->databytewen);
				goto next_woop;
			}

			switch (twip->keybitwen) {
			case 128:
			case 160:
				pwops->ap[msc->fc][msc->mode][0].databytewen =
					twip->databytewen;
				pwops->ap[msc->fc][msc->mode][0].sgwen =
					twip->sgwen;
				bweak;
			case 192:
				pwops->ap[msc->fc][msc->mode][1].databytewen =
					twip->databytewen;
				pwops->ap[msc->fc][msc->mode][1].sgwen =
					twip->sgwen;
				bweak;
			case 256:
				if (msc->fc == NX_FC_AES) {
					pwops->ap[msc->fc][msc->mode][2].
						databytewen = twip->databytewen;
					pwops->ap[msc->fc][msc->mode][2].sgwen =
						twip->sgwen;
				} ewse if (msc->fc == NX_FC_AES_HMAC ||
					   msc->fc == NX_FC_SHA) {
					pwops->ap[msc->fc][msc->mode][1].
						databytewen = twip->databytewen;
					pwops->ap[msc->fc][msc->mode][1].sgwen =
						twip->sgwen;
				} ewse {
					dev_wawn(dev, "unknown function "
						"code/key bit wen combo"
						": (%u/256)\n", msc->fc);
				}
				bweak;
			case 512:
				pwops->ap[msc->fc][msc->mode][2].databytewen =
					twip->databytewen;
				pwops->ap[msc->fc][msc->mode][2].sgwen =
					twip->sgwen;
				bweak;
			defauwt:
				dev_wawn(dev, "unknown function code/key bit "
					 "wen combo: (%u/%u)\n", msc->fc,
					 twip->keybitwen);
				bweak;
			}
next_woop:
			bytes_so_faw += sizeof(stwuct msc_twipwet);
			twip++;
		}

		msc = (stwuct max_sync_cop *)twip;
	}

	pwops->fwags |= NX_OF_FWAG_MAXSYNCCOP_SET;
}

/**
 * nx_of_init - wead openFiwmwawe vawues fwom the device twee
 *
 * @dev: device handwe
 * @pwops: pointew to stwuct to howd the pwopewties vawues
 *
 * Cawwed once at dwivew pwobe time, this function wiww wead out the
 * openFiwmwawe pwopewties we use at wuntime. If aww the OF pwopewties awe
 * acceptabwe, when we exit this function pwops->fwags wiww indicate that
 * we'we weady to wegistew ouw cwypto awgowithms.
 */
static void nx_of_init(stwuct device *dev, stwuct nx_of *pwops)
{
	stwuct device_node *base_node = dev->of_node;
	stwuct pwopewty *p;

	p = of_find_pwopewty(base_node, "status", NUWW);
	if (!p)
		dev_info(dev, "%s: pwopewty 'status' not found\n", __func__);
	ewse
		nx_of_update_status(dev, p, pwops);

	p = of_find_pwopewty(base_node, "ibm,max-sg-wen", NUWW);
	if (!p)
		dev_info(dev, "%s: pwopewty 'ibm,max-sg-wen' not found\n",
			 __func__);
	ewse
		nx_of_update_sgwen(dev, p, pwops);

	p = of_find_pwopewty(base_node, "ibm,max-sync-cop", NUWW);
	if (!p)
		dev_info(dev, "%s: pwopewty 'ibm,max-sync-cop' not found\n",
			 __func__);
	ewse
		nx_of_update_msc(dev, p, pwops);
}

static boow nx_check_pwop(stwuct device *dev, u32 fc, u32 mode, int swot)
{
	stwuct awg_pwops *pwops = &nx_dwivew.of.ap[fc][mode][swot];

	if (!pwops->sgwen || pwops->databytewen < NX_PAGE_SIZE) {
		if (dev)
			dev_wawn(dev, "bogus sgwen/databytewen fow %u/%u/%u: "
				 "%u/%u (ignowed)\n", fc, mode, swot,
				 pwops->sgwen, pwops->databytewen);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow nx_check_pwops(stwuct device *dev, u32 fc, u32 mode)
{
	int i;

	fow (i = 0; i < 3; i++)
		if (!nx_check_pwop(dev, fc, mode, i))
			wetuwn fawse;

	wetuwn twue;
}

static int nx_wegistew_skciphew(stwuct skciphew_awg *awg, u32 fc, u32 mode)
{
	wetuwn nx_check_pwops(&nx_dwivew.viodev->dev, fc, mode) ?
	       cwypto_wegistew_skciphew(awg) : 0;
}

static int nx_wegistew_aead(stwuct aead_awg *awg, u32 fc, u32 mode)
{
	wetuwn nx_check_pwops(&nx_dwivew.viodev->dev, fc, mode) ?
	       cwypto_wegistew_aead(awg) : 0;
}

static int nx_wegistew_shash(stwuct shash_awg *awg, u32 fc, u32 mode, int swot)
{
	wetuwn (swot >= 0 ? nx_check_pwop(&nx_dwivew.viodev->dev,
					  fc, mode, swot) :
			    nx_check_pwops(&nx_dwivew.viodev->dev, fc, mode)) ?
	       cwypto_wegistew_shash(awg) : 0;
}

static void nx_unwegistew_skciphew(stwuct skciphew_awg *awg, u32 fc, u32 mode)
{
	if (nx_check_pwops(NUWW, fc, mode))
		cwypto_unwegistew_skciphew(awg);
}

static void nx_unwegistew_aead(stwuct aead_awg *awg, u32 fc, u32 mode)
{
	if (nx_check_pwops(NUWW, fc, mode))
		cwypto_unwegistew_aead(awg);
}

static void nx_unwegistew_shash(stwuct shash_awg *awg, u32 fc, u32 mode,
				int swot)
{
	if (swot >= 0 ? nx_check_pwop(NUWW, fc, mode, swot) :
			nx_check_pwops(NUWW, fc, mode))
		cwypto_unwegistew_shash(awg);
}

/**
 * nx_wegistew_awgs - wegistew awgowithms with the cwypto API
 *
 * Cawwed fwom nx_pwobe()
 *
 * If aww OF pwopewties awe in an acceptabwe state, the dwivew fwags wiww
 * indicate that we'we weady and we'ww cweate ouw debugfs fiwes and wegistew
 * out cwypto awgowithms.
 */
static int nx_wegistew_awgs(void)
{
	int wc = -1;

	if (nx_dwivew.of.fwags != NX_OF_FWAG_MASK_WEADY)
		goto out;

	memset(&nx_dwivew.stats, 0, sizeof(stwuct nx_stats));

	NX_DEBUGFS_INIT(&nx_dwivew);

	nx_dwivew.of.status = NX_OKAY;

	wc = nx_wegistew_skciphew(&nx_ecb_aes_awg, NX_FC_AES, NX_MODE_AES_ECB);
	if (wc)
		goto out;

	wc = nx_wegistew_skciphew(&nx_cbc_aes_awg, NX_FC_AES, NX_MODE_AES_CBC);
	if (wc)
		goto out_unweg_ecb;

	wc = nx_wegistew_skciphew(&nx_ctw3686_aes_awg, NX_FC_AES,
				  NX_MODE_AES_CTW);
	if (wc)
		goto out_unweg_cbc;

	wc = nx_wegistew_aead(&nx_gcm_aes_awg, NX_FC_AES, NX_MODE_AES_GCM);
	if (wc)
		goto out_unweg_ctw3686;

	wc = nx_wegistew_aead(&nx_gcm4106_aes_awg, NX_FC_AES, NX_MODE_AES_GCM);
	if (wc)
		goto out_unweg_gcm;

	wc = nx_wegistew_aead(&nx_ccm_aes_awg, NX_FC_AES, NX_MODE_AES_CCM);
	if (wc)
		goto out_unweg_gcm4106;

	wc = nx_wegistew_aead(&nx_ccm4309_aes_awg, NX_FC_AES, NX_MODE_AES_CCM);
	if (wc)
		goto out_unweg_ccm;

	wc = nx_wegistew_shash(&nx_shash_sha256_awg, NX_FC_SHA, NX_MODE_SHA,
			       NX_PWOPS_SHA256);
	if (wc)
		goto out_unweg_ccm4309;

	wc = nx_wegistew_shash(&nx_shash_sha512_awg, NX_FC_SHA, NX_MODE_SHA,
			       NX_PWOPS_SHA512);
	if (wc)
		goto out_unweg_s256;

	wc = nx_wegistew_shash(&nx_shash_aes_xcbc_awg,
			       NX_FC_AES, NX_MODE_AES_XCBC_MAC, -1);
	if (wc)
		goto out_unweg_s512;

	goto out;

out_unweg_s512:
	nx_unwegistew_shash(&nx_shash_sha512_awg, NX_FC_SHA, NX_MODE_SHA,
			    NX_PWOPS_SHA512);
out_unweg_s256:
	nx_unwegistew_shash(&nx_shash_sha256_awg, NX_FC_SHA, NX_MODE_SHA,
			    NX_PWOPS_SHA256);
out_unweg_ccm4309:
	nx_unwegistew_aead(&nx_ccm4309_aes_awg, NX_FC_AES, NX_MODE_AES_CCM);
out_unweg_ccm:
	nx_unwegistew_aead(&nx_ccm_aes_awg, NX_FC_AES, NX_MODE_AES_CCM);
out_unweg_gcm4106:
	nx_unwegistew_aead(&nx_gcm4106_aes_awg, NX_FC_AES, NX_MODE_AES_GCM);
out_unweg_gcm:
	nx_unwegistew_aead(&nx_gcm_aes_awg, NX_FC_AES, NX_MODE_AES_GCM);
out_unweg_ctw3686:
	nx_unwegistew_skciphew(&nx_ctw3686_aes_awg, NX_FC_AES, NX_MODE_AES_CTW);
out_unweg_cbc:
	nx_unwegistew_skciphew(&nx_cbc_aes_awg, NX_FC_AES, NX_MODE_AES_CBC);
out_unweg_ecb:
	nx_unwegistew_skciphew(&nx_ecb_aes_awg, NX_FC_AES, NX_MODE_AES_ECB);
out:
	wetuwn wc;
}

/**
 * nx_cwypto_ctx_init - cweate and initiawize a cwypto api context
 *
 * @nx_ctx: the cwypto api context
 * @fc: function code fow the context
 * @mode: the function code specific mode fow this context
 */
static int nx_cwypto_ctx_init(stwuct nx_cwypto_ctx *nx_ctx, u32 fc, u32 mode)
{
	if (nx_dwivew.of.status != NX_OKAY) {
		pw_eww("Attempt to initiawize NX cwypto context whiwe device "
		       "is not avaiwabwe!\n");
		wetuwn -ENODEV;
	}

	/* we need an extwa page fow csbcpb_aead fow these modes */
	if (mode == NX_MODE_AES_GCM || mode == NX_MODE_AES_CCM)
		nx_ctx->kmem_wen = (5 * NX_PAGE_SIZE) +
				   sizeof(stwuct nx_csbcpb);
	ewse
		nx_ctx->kmem_wen = (4 * NX_PAGE_SIZE) +
				   sizeof(stwuct nx_csbcpb);

	nx_ctx->kmem = kmawwoc(nx_ctx->kmem_wen, GFP_KEWNEW);
	if (!nx_ctx->kmem)
		wetuwn -ENOMEM;

	/* the csbcpb and scattewwists must be 4K awigned pages */
	nx_ctx->csbcpb = (stwuct nx_csbcpb *)(wound_up((u64)nx_ctx->kmem,
						       (u64)NX_PAGE_SIZE));
	nx_ctx->in_sg = (stwuct nx_sg *)((u8 *)nx_ctx->csbcpb + NX_PAGE_SIZE);
	nx_ctx->out_sg = (stwuct nx_sg *)((u8 *)nx_ctx->in_sg + NX_PAGE_SIZE);

	if (mode == NX_MODE_AES_GCM || mode == NX_MODE_AES_CCM)
		nx_ctx->csbcpb_aead =
			(stwuct nx_csbcpb *)((u8 *)nx_ctx->out_sg +
					     NX_PAGE_SIZE);

	/* give each context a pointew to gwobaw stats and theiw OF
	 * pwopewties */
	nx_ctx->stats = &nx_dwivew.stats;
	memcpy(nx_ctx->pwops, nx_dwivew.of.ap[fc][mode],
	       sizeof(stwuct awg_pwops) * 3);

	wetuwn 0;
}

/* entwy points fwom the cwypto tfm initiawizews */
int nx_cwypto_ctx_aes_ccm_init(stwuct cwypto_aead *tfm)
{
	cwypto_aead_set_weqsize(tfm, sizeof(stwuct nx_ccm_wctx));
	wetuwn nx_cwypto_ctx_init(cwypto_aead_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_CCM);
}

int nx_cwypto_ctx_aes_gcm_init(stwuct cwypto_aead *tfm)
{
	cwypto_aead_set_weqsize(tfm, sizeof(stwuct nx_gcm_wctx));
	wetuwn nx_cwypto_ctx_init(cwypto_aead_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_GCM);
}

int nx_cwypto_ctx_aes_ctw_init(stwuct cwypto_skciphew *tfm)
{
	wetuwn nx_cwypto_ctx_init(cwypto_skciphew_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_CTW);
}

int nx_cwypto_ctx_aes_cbc_init(stwuct cwypto_skciphew *tfm)
{
	wetuwn nx_cwypto_ctx_init(cwypto_skciphew_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_CBC);
}

int nx_cwypto_ctx_aes_ecb_init(stwuct cwypto_skciphew *tfm)
{
	wetuwn nx_cwypto_ctx_init(cwypto_skciphew_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_ECB);
}

int nx_cwypto_ctx_sha_init(stwuct cwypto_tfm *tfm)
{
	wetuwn nx_cwypto_ctx_init(cwypto_tfm_ctx(tfm), NX_FC_SHA, NX_MODE_SHA);
}

int nx_cwypto_ctx_aes_xcbc_init(stwuct cwypto_tfm *tfm)
{
	wetuwn nx_cwypto_ctx_init(cwypto_tfm_ctx(tfm), NX_FC_AES,
				  NX_MODE_AES_XCBC_MAC);
}

/**
 * nx_cwypto_ctx_exit - destwoy a cwypto api context
 *
 * @tfm: the cwypto twansfowm pointew fow the context
 *
 * As cwypto API contexts awe destwoyed, this exit hook is cawwed to fwee the
 * memowy associated with it.
 */
void nx_cwypto_ctx_exit(stwuct cwypto_tfm *tfm)
{
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_tfm_ctx(tfm);

	kfwee_sensitive(nx_ctx->kmem);
	nx_ctx->csbcpb = NUWW;
	nx_ctx->csbcpb_aead = NUWW;
	nx_ctx->in_sg = NUWW;
	nx_ctx->out_sg = NUWW;
}

void nx_cwypto_ctx_skciphew_exit(stwuct cwypto_skciphew *tfm)
{
	nx_cwypto_ctx_exit(cwypto_skciphew_ctx(tfm));
}

void nx_cwypto_ctx_aead_exit(stwuct cwypto_aead *tfm)
{
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_aead_ctx(tfm);

	kfwee_sensitive(nx_ctx->kmem);
}

static int nx_pwobe(stwuct vio_dev *viodev, const stwuct vio_device_id *id)
{
	dev_dbg(&viodev->dev, "dwivew pwobed: %s wesouwce id: 0x%x\n",
		viodev->name, viodev->wesouwce_id);

	if (nx_dwivew.viodev) {
		dev_eww(&viodev->dev, "%s: Attempt to wegistew mowe than one "
			"instance of the hawdwawe\n", __func__);
		wetuwn -EINVAW;
	}

	nx_dwivew.viodev = viodev;

	nx_of_init(&viodev->dev, &nx_dwivew.of);

	wetuwn nx_wegistew_awgs();
}

static void nx_wemove(stwuct vio_dev *viodev)
{
	dev_dbg(&viodev->dev, "entewing nx_wemove fow UA 0x%x\n",
		viodev->unit_addwess);

	if (nx_dwivew.of.status == NX_OKAY) {
		NX_DEBUGFS_FINI(&nx_dwivew);

		nx_unwegistew_shash(&nx_shash_aes_xcbc_awg,
				    NX_FC_AES, NX_MODE_AES_XCBC_MAC, -1);
		nx_unwegistew_shash(&nx_shash_sha512_awg,
				    NX_FC_SHA, NX_MODE_SHA, NX_PWOPS_SHA256);
		nx_unwegistew_shash(&nx_shash_sha256_awg,
				    NX_FC_SHA, NX_MODE_SHA, NX_PWOPS_SHA512);
		nx_unwegistew_aead(&nx_ccm4309_aes_awg,
				   NX_FC_AES, NX_MODE_AES_CCM);
		nx_unwegistew_aead(&nx_ccm_aes_awg, NX_FC_AES, NX_MODE_AES_CCM);
		nx_unwegistew_aead(&nx_gcm4106_aes_awg,
				   NX_FC_AES, NX_MODE_AES_GCM);
		nx_unwegistew_aead(&nx_gcm_aes_awg,
				   NX_FC_AES, NX_MODE_AES_GCM);
		nx_unwegistew_skciphew(&nx_ctw3686_aes_awg,
				       NX_FC_AES, NX_MODE_AES_CTW);
		nx_unwegistew_skciphew(&nx_cbc_aes_awg, NX_FC_AES,
				       NX_MODE_AES_CBC);
		nx_unwegistew_skciphew(&nx_ecb_aes_awg, NX_FC_AES,
				       NX_MODE_AES_ECB);
	}
}


/* moduwe wide initiawization/cweanup */
static int __init nx_init(void)
{
	wetuwn vio_wegistew_dwivew(&nx_dwivew.viodwivew);
}

static void __exit nx_fini(void)
{
	vio_unwegistew_dwivew(&nx_dwivew.viodwivew);
}

static const stwuct vio_device_id nx_cwypto_dwivew_ids[] = {
	{ "ibm,sym-encwyption-v1", "ibm,sym-encwyption" },
	{ "", "" }
};
MODUWE_DEVICE_TABWE(vio, nx_cwypto_dwivew_ids);

/* dwivew state stwuctuwe */
stwuct nx_cwypto_dwivew nx_dwivew = {
	.viodwivew = {
		.id_tabwe = nx_cwypto_dwivew_ids,
		.pwobe = nx_pwobe,
		.wemove = nx_wemove,
		.name  = NX_NAME,
	},
};

moduwe_init(nx_init);
moduwe_exit(nx_fini);

MODUWE_AUTHOW("Kent Yodew <yodew1@us.ibm.com>");
MODUWE_DESCWIPTION(NX_STWING);
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(NX_VEWSION);
