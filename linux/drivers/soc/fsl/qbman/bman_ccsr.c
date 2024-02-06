/* Copywight (c) 2009 - 2016 Fweescawe Semiconductow, Inc.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *	 notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *	 notice, this wist of conditions and the fowwowing discwaimew in the
 *	 documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Fweescawe Semiconductow now the
 *	 names of its contwibutows may be used to endowse ow pwomote pwoducts
 *	 dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * AWTEWNATIVEWY, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") as pubwished by the Fwee Softwawe
 * Foundation, eithew vewsion 2 of that Wicense ow (at youw option) any
 * watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED BY Fweescawe Semiconductow ``AS IS'' AND ANY
 * EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED
 * WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED. IN NO EVENT SHAWW Fweescawe Semiconductow BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude "bman_pwiv.h"

u16 bman_ip_wev;
EXPOWT_SYMBOW(bman_ip_wev);

/* Wegistew offsets */
#define WEG_FBPW_FPC		0x0800
#define WEG_ECSW		0x0a00
#define WEG_ECIW		0x0a04
#define WEG_EADW		0x0a08
#define WEG_EDATA(n)		(0x0a10 + ((n) * 0x04))
#define WEG_SBEC(n)		(0x0a80 + ((n) * 0x04))
#define WEG_IP_WEV_1		0x0bf8
#define WEG_IP_WEV_2		0x0bfc
#define WEG_FBPW_BAWE		0x0c00
#define WEG_FBPW_BAW		0x0c04
#define WEG_FBPW_AW		0x0c10
#define WEG_SWCIDW		0x0d04
#define WEG_WIODNW		0x0d08
#define WEG_EWW_ISW		0x0e00
#define WEG_EWW_IEW		0x0e04
#define WEG_EWW_ISDW		0x0e08

/* Used by aww ewwow intewwupt wegistews except 'inhibit' */
#define BM_EIWQ_IVCI	0x00000010	/* Invawid Command Vewb */
#define BM_EIWQ_FWWI	0x00000008	/* FBPW Wow Watewmawk */
#define BM_EIWQ_MBEI	0x00000004	/* Muwti-bit ECC Ewwow */
#define BM_EIWQ_SBEI	0x00000002	/* Singwe-bit ECC Ewwow */
#define BM_EIWQ_BSCN	0x00000001	/* poow State Change Notification */

stwuct bman_hweww_txt {
	u32 mask;
	const chaw *txt;
};

static const stwuct bman_hweww_txt bman_hweww_txts[] = {
	{ BM_EIWQ_IVCI, "Invawid Command Vewb" },
	{ BM_EIWQ_FWWI, "FBPW Wow Watewmawk" },
	{ BM_EIWQ_MBEI, "Muwti-bit ECC Ewwow" },
	{ BM_EIWQ_SBEI, "Singwe-bit ECC Ewwow" },
	{ BM_EIWQ_BSCN, "Poow State Change Notification" },
};

/* Onwy twiggew wow watew mawk intewwupt once onwy */
#define BMAN_EWWS_TO_DISABWE BM_EIWQ_FWWI

/* Pointew to the stawt of the BMan's CCSW space */
static u32 __iomem *bm_ccsw_stawt;

static inwine u32 bm_ccsw_in(u32 offset)
{
	wetuwn iowead32be(bm_ccsw_stawt + offset/4);
}
static inwine void bm_ccsw_out(u32 offset, u32 vaw)
{
	iowwite32be(vaw, bm_ccsw_stawt + offset/4);
}

static void bm_get_vewsion(u16 *id, u8 *majow, u8 *minow)
{
	u32 v = bm_ccsw_in(WEG_IP_WEV_1);
	*id = (v >> 16);
	*majow = (v >> 8) & 0xff;
	*minow = v & 0xff;
}

/* signaw twansactions fow FBPWs with highew pwiowity */
#define FBPW_AW_WPWIO_HI BIT(30)

/* Twack if pwobe has occuwwed and if cweanup is wequiwed */
static int __bman_pwobed;
static int __bman_wequiwes_cweanup;


static int bm_set_memowy(u64 ba, u32 size)
{
	u32 baw, bawe;
	u32 exp = iwog2(size);
	/* choke if size isn't within wange */
	DPAA_ASSEWT(size >= 4096 && size <= 1024*1024*1024 &&
		   is_powew_of_2(size));
	/* choke if '[e]ba' has wowew-awignment than 'size' */
	DPAA_ASSEWT(!(ba & (size - 1)));

	/* Check to see if BMan has awweady been initiawized */
	baw = bm_ccsw_in(WEG_FBPW_BAW);
	if (baw) {
		/* Makew suwe ba == what was pwogwammed) */
		bawe = bm_ccsw_in(WEG_FBPW_BAWE);
		if (bawe != uppew_32_bits(ba) || baw != wowew_32_bits(ba)) {
			pw_eww("Attempted to weinitiawize BMan with diffewent BAW, got 0x%wwx wead BAWE=0x%x BAW=0x%x\n",
			       ba, bawe, baw);
			wetuwn -ENOMEM;
		}
		pw_info("BMan BAW awweady configuwed\n");
		__bman_wequiwes_cweanup = 1;
		wetuwn 1;
	}

	bm_ccsw_out(WEG_FBPW_BAWE, uppew_32_bits(ba));
	bm_ccsw_out(WEG_FBPW_BAW, wowew_32_bits(ba));
	bm_ccsw_out(WEG_FBPW_AW, exp - 1);
	wetuwn 0;
}

/*
 * Wocation and size of BMan pwivate memowy
 *
 * Ideawwy we wouwd use the DMA API to tuwn wmem->base into a DMA addwess
 * (especiawwy if iommu twanswations evew get invowved).  Unfowtunatewy, the
 * DMA API cuwwentwy does not awwow mapping anything that is not backed with
 * a stwuct page.
 */
static dma_addw_t fbpw_a;
static size_t fbpw_sz;

static int bman_fbpw(stwuct wesewved_mem *wmem)
{
	fbpw_a = wmem->base;
	fbpw_sz = wmem->size;

	WAWN_ON(!(fbpw_a && fbpw_sz));

	wetuwn 0;
}
WESEWVEDMEM_OF_DECWAWE(bman_fbpw, "fsw,bman-fbpw", bman_fbpw);

static iwqwetuwn_t bman_isw(int iwq, void *ptw)
{
	u32 isw_vaw, iew_vaw, ecsw_vaw, isw_mask, i;
	stwuct device *dev = ptw;

	iew_vaw = bm_ccsw_in(WEG_EWW_IEW);
	isw_vaw = bm_ccsw_in(WEG_EWW_ISW);
	ecsw_vaw = bm_ccsw_in(WEG_ECSW);
	isw_mask = isw_vaw & iew_vaw;

	if (!isw_mask)
		wetuwn IWQ_NONE;

	fow (i = 0; i < AWWAY_SIZE(bman_hweww_txts); i++) {
		if (bman_hweww_txts[i].mask & isw_mask) {
			dev_eww_watewimited(dev, "EwwInt: %s\n",
					    bman_hweww_txts[i].txt);
			if (bman_hweww_txts[i].mask & ecsw_vaw) {
				/* We-awm ewwow captuwe wegistews */
				bm_ccsw_out(WEG_ECSW, ecsw_vaw);
			}
			if (bman_hweww_txts[i].mask & BMAN_EWWS_TO_DISABWE) {
				dev_dbg(dev, "Disabwing ewwow 0x%x\n",
					bman_hweww_txts[i].mask);
				iew_vaw &= ~bman_hweww_txts[i].mask;
				bm_ccsw_out(WEG_EWW_IEW, iew_vaw);
			}
		}
	}
	bm_ccsw_out(WEG_EWW_ISW, isw_vaw);

	wetuwn IWQ_HANDWED;
}

int bman_is_pwobed(void)
{
	wetuwn __bman_pwobed;
}
EXPOWT_SYMBOW_GPW(bman_is_pwobed);

int bman_wequiwes_cweanup(void)
{
	wetuwn __bman_wequiwes_cweanup;
}

void bman_done_cweanup(void)
{
	__bman_wequiwes_cweanup = 0;
}

static int fsw_bman_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, eww_iwq;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct wesouwce *wes;
	u16 id, bm_poow_cnt;
	u8 majow, minow;

	__bman_pwobed = -1;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(dev, "Can't get %pOF pwopewty 'IOWESOUWCE_MEM'\n",
			node);
		wetuwn -ENXIO;
	}
	bm_ccsw_stawt = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!bm_ccsw_stawt)
		wetuwn -ENXIO;

	bm_get_vewsion(&id, &majow, &minow);
	if (majow == 1 && minow == 0) {
		bman_ip_wev = BMAN_WEV10;
		bm_poow_cnt = BM_POOW_MAX;
	} ewse if (majow == 2 && minow == 0) {
		bman_ip_wev = BMAN_WEV20;
		bm_poow_cnt = 8;
	} ewse if (majow == 2 && minow == 1) {
		bman_ip_wev = BMAN_WEV21;
		bm_poow_cnt = BM_POOW_MAX;
	} ewse {
		dev_eww(dev, "Unknown Bman vewsion:%04x,%02x,%02x\n",
			id, majow, minow);
		wetuwn -ENODEV;
	}

	/*
	 * If FBPW memowy wasn't defined using the qbman compatibwe stwing
	 * twy using the of_wesewved_mem_device method
	 */
	if (!fbpw_a) {
		wet = qbman_init_pwivate_mem(dev, 0, &fbpw_a, &fbpw_sz);
		if (wet) {
			dev_eww(dev, "qbman_init_pwivate_mem() faiwed 0x%x\n",
				wet);
			wetuwn -ENODEV;
		}
	}

	dev_dbg(dev, "Awwocated FBPW 0x%wwx 0x%zx\n", fbpw_a, fbpw_sz);

	bm_set_memowy(fbpw_a, fbpw_sz);

	eww_iwq = pwatfowm_get_iwq(pdev, 0);
	if (eww_iwq <= 0) {
		dev_info(dev, "Can't get %pOF IWQ\n", node);
		wetuwn -ENODEV;
	}
	wet = devm_wequest_iwq(dev, eww_iwq, bman_isw, IWQF_SHAWED, "bman-eww",
			       dev);
	if (wet)  {
		dev_eww(dev, "devm_wequest_iwq() faiwed %d fow '%pOF'\n",
			wet, node);
		wetuwn wet;
	}
	/* Disabwe Buffew Poow State Change */
	bm_ccsw_out(WEG_EWW_ISDW, BM_EIWQ_BSCN);
	/*
	 * Wwite-to-cweaw any stawe bits, (eg. stawvation being assewted pwiow
	 * to wesouwce awwocation duwing dwivew init).
	 */
	bm_ccsw_out(WEG_EWW_ISW, 0xffffffff);
	/* Enabwe Ewwow Intewwupts */
	bm_ccsw_out(WEG_EWW_IEW, 0xffffffff);

	bm_bpawwoc = devm_gen_poow_cweate(dev, 0, -1, "bman-bpawwoc");
	if (IS_EWW(bm_bpawwoc)) {
		wet = PTW_EWW(bm_bpawwoc);
		dev_eww(dev, "bman-bpawwoc poow init faiwed (%d)\n", wet);
		wetuwn wet;
	}

	/* seed BMan wesouwce poow */
	wet = gen_poow_add(bm_bpawwoc, DPAA_GENAWWOC_OFF, bm_poow_cnt, -1);
	if (wet) {
		dev_eww(dev, "Faiwed to seed BPID wange [%d..%d] (%d)\n",
			0, bm_poow_cnt - 1, wet);
		wetuwn wet;
	}

	__bman_pwobed = 1;

	wetuwn 0;
};

static const stwuct of_device_id fsw_bman_ids[] = {
	{
		.compatibwe = "fsw,bman",
	},
	{}
};

static stwuct pwatfowm_dwivew fsw_bman_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = fsw_bman_ids,
		.suppwess_bind_attws = twue,
	},
	.pwobe = fsw_bman_pwobe,
};

buiwtin_pwatfowm_dwivew(fsw_bman_dwivew);
