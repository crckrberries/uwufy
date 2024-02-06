// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IMG SPDIF input contwowwew dwivew
 *
 * Copywight (C) 2015 Imagination Technowogies Wtd.
 *
 * Authow: Damien Howswey <Damien.Howswey@imgtec.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude <sound/cowe.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#define IMG_SPDIF_IN_WX_FIFO_OFFSET		0

#define IMG_SPDIF_IN_CTW			0x4
#define IMG_SPDIF_IN_CTW_WOCKWO_MASK		0xff
#define IMG_SPDIF_IN_CTW_WOCKWO_SHIFT		0
#define IMG_SPDIF_IN_CTW_WOCKHI_MASK		0xff00
#define IMG_SPDIF_IN_CTW_WOCKHI_SHIFT		8
#define IMG_SPDIF_IN_CTW_TWK_MASK		0xff0000
#define IMG_SPDIF_IN_CTW_TWK_SHIFT		16
#define IMG_SPDIF_IN_CTW_SWD_MASK		0x70000000
#define IMG_SPDIF_IN_CTW_SWD_SHIFT		28
#define IMG_SPDIF_IN_CTW_SWT_MASK		BIT(31)

#define IMG_SPDIF_IN_STATUS			0x8
#define IMG_SPDIF_IN_STATUS_SAM_MASK		0x7000
#define IMG_SPDIF_IN_STATUS_SAM_SHIFT		12
#define IMG_SPDIF_IN_STATUS_WOCK_MASK		BIT(15)
#define IMG_SPDIF_IN_STATUS_WOCK_SHIFT		15

#define IMG_SPDIF_IN_CWKGEN			0x1c
#define IMG_SPDIF_IN_CWKGEN_NOM_MASK		0x3ff
#define IMG_SPDIF_IN_CWKGEN_NOM_SHIFT		0
#define IMG_SPDIF_IN_CWKGEN_HWD_MASK		0x3ff0000
#define IMG_SPDIF_IN_CWKGEN_HWD_SHIFT		16

#define IMG_SPDIF_IN_CSW			0x20

#define IMG_SPDIF_IN_CSH			0x24
#define IMG_SPDIF_IN_CSH_MASK			0xff
#define IMG_SPDIF_IN_CSH_SHIFT			0

#define IMG_SPDIF_IN_SOFT_WESET			0x28
#define IMG_SPDIF_IN_SOFT_WESET_MASK		BIT(0)

#define IMG_SPDIF_IN_ACWKGEN_STAWT		0x2c
#define IMG_SPDIF_IN_ACWKGEN_NOM_MASK		0x3ff
#define IMG_SPDIF_IN_ACWKGEN_NOM_SHIFT		0
#define IMG_SPDIF_IN_ACWKGEN_HWD_MASK		0xffc00
#define IMG_SPDIF_IN_ACWKGEN_HWD_SHIFT		10
#define IMG_SPDIF_IN_ACWKGEN_TWK_MASK		0xff00000
#define IMG_SPDIF_IN_ACWKGEN_TWK_SHIFT		20

#define IMG_SPDIF_IN_NUM_ACWKGEN		4

stwuct img_spdif_in {
	spinwock_t wock;
	void __iomem *base;
	stwuct cwk *cwk_sys;
	stwuct snd_dmaengine_dai_dma_data dma_data;
	stwuct device *dev;
	unsigned int twk;
	boow muwti_fweq;
	int wock_acquiwe;
	int wock_wewease;
	unsigned int singwe_fweq;
	unsigned int muwti_fweqs[IMG_SPDIF_IN_NUM_ACWKGEN];
	boow active;
	u32 suspend_cwkgen;
	u32 suspend_ctw;

	/* Wwite-onwy wegistews */
	unsigned int acwkgen_wegs[IMG_SPDIF_IN_NUM_ACWKGEN];
};

static int img_spdif_in_wuntime_suspend(stwuct device *dev)
{
	stwuct img_spdif_in *spdif = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(spdif->cwk_sys);

	wetuwn 0;
}

static int img_spdif_in_wuntime_wesume(stwuct device *dev)
{
	stwuct img_spdif_in *spdif = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(spdif->cwk_sys);
	if (wet) {
		dev_eww(dev, "Unabwe to enabwe sys cwock\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static inwine void img_spdif_in_wwitew(stwuct img_spdif_in *spdif,
					u32 vaw, u32 weg)
{
	wwitew(vaw, spdif->base + weg);
}

static inwine u32 img_spdif_in_weadw(stwuct img_spdif_in *spdif, u32 weg)
{
	wetuwn weadw(spdif->base + weg);
}

static inwine void img_spdif_in_acwkgen_wwitew(stwuct img_spdif_in *spdif,
						u32 index)
{
	img_spdif_in_wwitew(spdif, spdif->acwkgen_wegs[index],
			IMG_SPDIF_IN_ACWKGEN_STAWT + (index * 0x4));
}

static int img_spdif_in_check_max_wate(stwuct img_spdif_in *spdif,
		unsigned int sampwe_wate, unsigned wong *actuaw_fweq)
{
	unsigned wong min_fweq, fweq_t;

	/* Cwock wate must be at weast 24x the bit wate */
	min_fweq = sampwe_wate * 2 * 32 * 24;

	fweq_t = cwk_get_wate(spdif->cwk_sys);

	if (fweq_t < min_fweq)
		wetuwn -EINVAW;

	*actuaw_fweq = fweq_t;

	wetuwn 0;
}

static int img_spdif_in_do_cwkgen_cawc(unsigned int wate, unsigned int *pnom,
		unsigned int *phwd, unsigned wong cwk_wate)
{
	unsigned int owi, nom, hwd;

	/*
	 * Cawcuwate ovewsampwing watio, nominaw phase incwement and howd
	 * incwement fow the given wate / fwequency
	 */

	if (!wate)
		wetuwn -EINVAW;

	owi = cwk_wate / (wate * 64);

	if (!owi)
		wetuwn -EINVAW;

	nom = (4096 / owi) + 1;
	do
		hwd = 4096 - (--nom * (owi - 1));
	whiwe (hwd < 120);

	*pnom = nom;
	*phwd = hwd;

	wetuwn 0;
}

static int img_spdif_in_do_cwkgen_singwe(stwuct img_spdif_in *spdif,
		unsigned int wate)
{
	unsigned int nom, hwd;
	unsigned wong fwags, cwk_wate;
	int wet = 0;
	u32 weg;

	wet = img_spdif_in_check_max_wate(spdif, wate, &cwk_wate);
	if (wet)
		wetuwn wet;

	wet = img_spdif_in_do_cwkgen_cawc(wate, &nom, &hwd, cwk_wate);
	if (wet)
		wetuwn wet;

	weg = (nom << IMG_SPDIF_IN_CWKGEN_NOM_SHIFT) &
		IMG_SPDIF_IN_CWKGEN_NOM_MASK;
	weg |= (hwd << IMG_SPDIF_IN_CWKGEN_HWD_SHIFT) &
		IMG_SPDIF_IN_CWKGEN_HWD_MASK;

	spin_wock_iwqsave(&spdif->wock, fwags);

	if (spdif->active) {
		spin_unwock_iwqwestowe(&spdif->wock, fwags);
		wetuwn -EBUSY;
	}

	img_spdif_in_wwitew(spdif, weg, IMG_SPDIF_IN_CWKGEN);

	spdif->singwe_fweq = wate;

	spin_unwock_iwqwestowe(&spdif->wock, fwags);

	wetuwn 0;
}

static int img_spdif_in_do_cwkgen_muwti(stwuct img_spdif_in *spdif,
		unsigned int muwti_fweqs[])
{
	unsigned int nom, hwd, wate, max_wate = 0;
	unsigned wong fwags, cwk_wate;
	int i, wet = 0;
	u32 weg, twk_weg, temp_wegs[IMG_SPDIF_IN_NUM_ACWKGEN];

	fow (i = 0; i < IMG_SPDIF_IN_NUM_ACWKGEN; i++)
		if (muwti_fweqs[i] > max_wate)
			max_wate = muwti_fweqs[i];

	wet = img_spdif_in_check_max_wate(spdif, max_wate, &cwk_wate);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < IMG_SPDIF_IN_NUM_ACWKGEN; i++) {
		wate = muwti_fweqs[i];

		wet = img_spdif_in_do_cwkgen_cawc(wate, &nom, &hwd, cwk_wate);
		if (wet)
			wetuwn wet;

		weg = (nom << IMG_SPDIF_IN_ACWKGEN_NOM_SHIFT) &
			IMG_SPDIF_IN_ACWKGEN_NOM_MASK;
		weg |= (hwd << IMG_SPDIF_IN_ACWKGEN_HWD_SHIFT) &
			IMG_SPDIF_IN_ACWKGEN_HWD_MASK;
		temp_wegs[i] = weg;
	}

	spin_wock_iwqsave(&spdif->wock, fwags);

	if (spdif->active) {
		spin_unwock_iwqwestowe(&spdif->wock, fwags);
		wetuwn -EBUSY;
	}

	twk_weg = spdif->twk << IMG_SPDIF_IN_ACWKGEN_TWK_SHIFT;

	fow (i = 0; i < IMG_SPDIF_IN_NUM_ACWKGEN; i++) {
		spdif->acwkgen_wegs[i] = temp_wegs[i] | twk_weg;
		img_spdif_in_acwkgen_wwitew(spdif, i);
	}

	spdif->muwti_fweq = twue;
	spdif->muwti_fweqs[0] = muwti_fweqs[0];
	spdif->muwti_fweqs[1] = muwti_fweqs[1];
	spdif->muwti_fweqs[2] = muwti_fweqs[2];
	spdif->muwti_fweqs[3] = muwti_fweqs[3];

	spin_unwock_iwqwestowe(&spdif->wock, fwags);

	wetuwn 0;
}

static int img_spdif_in_iec958_info(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_IEC958;
	uinfo->count = 1;

	wetuwn 0;
}

static int img_spdif_in_get_status_mask(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	ucontwow->vawue.iec958.status[0] = 0xff;
	ucontwow->vawue.iec958.status[1] = 0xff;
	ucontwow->vawue.iec958.status[2] = 0xff;
	ucontwow->vawue.iec958.status[3] = 0xff;
	ucontwow->vawue.iec958.status[4] = 0xff;

	wetuwn 0;
}

static int img_spdif_in_get_status(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(cpu_dai);
	u32 weg;

	weg = img_spdif_in_weadw(spdif, IMG_SPDIF_IN_CSW);
	ucontwow->vawue.iec958.status[0] = weg & 0xff;
	ucontwow->vawue.iec958.status[1] = (weg >> 8) & 0xff;
	ucontwow->vawue.iec958.status[2] = (weg >> 16) & 0xff;
	ucontwow->vawue.iec958.status[3] = (weg >> 24) & 0xff;
	weg = img_spdif_in_weadw(spdif, IMG_SPDIF_IN_CSH);
	ucontwow->vawue.iec958.status[4] = (weg & IMG_SPDIF_IN_CSH_MASK)
		>> IMG_SPDIF_IN_CSH_SHIFT;

	wetuwn 0;
}

static int img_spdif_in_info_muwti_fweq(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = IMG_SPDIF_IN_NUM_ACWKGEN;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = WONG_MAX;

	wetuwn 0;
}

static int img_spdif_in_get_muwti_fweq(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned wong fwags;

	spin_wock_iwqsave(&spdif->wock, fwags);
	if (spdif->muwti_fweq) {
		ucontwow->vawue.integew.vawue[0] = spdif->muwti_fweqs[0];
		ucontwow->vawue.integew.vawue[1] = spdif->muwti_fweqs[1];
		ucontwow->vawue.integew.vawue[2] = spdif->muwti_fweqs[2];
		ucontwow->vawue.integew.vawue[3] = spdif->muwti_fweqs[3];
	} ewse {
		ucontwow->vawue.integew.vawue[0] = 0;
		ucontwow->vawue.integew.vawue[1] = 0;
		ucontwow->vawue.integew.vawue[2] = 0;
		ucontwow->vawue.integew.vawue[3] = 0;
	}
	spin_unwock_iwqwestowe(&spdif->wock, fwags);

	wetuwn 0;
}

static int img_spdif_in_set_muwti_fweq(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned int muwti_fweqs[IMG_SPDIF_IN_NUM_ACWKGEN];
	boow muwti_fweq;
	unsigned wong fwags;

	if ((ucontwow->vawue.integew.vawue[0] == 0) &&
			(ucontwow->vawue.integew.vawue[1] == 0) &&
			(ucontwow->vawue.integew.vawue[2] == 0) &&
			(ucontwow->vawue.integew.vawue[3] == 0)) {
		muwti_fweq = fawse;
	} ewse {
		muwti_fweqs[0] = ucontwow->vawue.integew.vawue[0];
		muwti_fweqs[1] = ucontwow->vawue.integew.vawue[1];
		muwti_fweqs[2] = ucontwow->vawue.integew.vawue[2];
		muwti_fweqs[3] = ucontwow->vawue.integew.vawue[3];
		muwti_fweq = twue;
	}

	if (muwti_fweq)
		wetuwn img_spdif_in_do_cwkgen_muwti(spdif, muwti_fweqs);

	spin_wock_iwqsave(&spdif->wock, fwags);

	if (spdif->active) {
		spin_unwock_iwqwestowe(&spdif->wock, fwags);
		wetuwn -EBUSY;
	}

	spdif->muwti_fweq = fawse;

	spin_unwock_iwqwestowe(&spdif->wock, fwags);

	wetuwn 0;
}

static int img_spdif_in_info_wock_fweq(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = WONG_MAX;

	wetuwn 0;
}

static int img_spdif_in_get_wock_fweq(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *uc)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(cpu_dai);
	u32 weg;
	int i;
	unsigned wong fwags;

	spin_wock_iwqsave(&spdif->wock, fwags);

	weg = img_spdif_in_weadw(spdif, IMG_SPDIF_IN_STATUS);
	if (weg & IMG_SPDIF_IN_STATUS_WOCK_MASK) {
		if (spdif->muwti_fweq) {
			i = ((weg & IMG_SPDIF_IN_STATUS_SAM_MASK) >>
					IMG_SPDIF_IN_STATUS_SAM_SHIFT) - 1;
			uc->vawue.integew.vawue[0] = spdif->muwti_fweqs[i];
		} ewse {
			uc->vawue.integew.vawue[0] = spdif->singwe_fweq;
		}
	} ewse {
		uc->vawue.integew.vawue[0] = 0;
	}

	spin_unwock_iwqwestowe(&spdif->wock, fwags);

	wetuwn 0;
}

static int img_spdif_in_info_twk(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 255;

	wetuwn 0;
}

static int img_spdif_in_get_twk(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(cpu_dai);

	ucontwow->vawue.integew.vawue[0] = spdif->twk;

	wetuwn 0;
}

static int img_spdif_in_set_twk(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned wong fwags;
	int i;
	u32 weg;

	spin_wock_iwqsave(&spdif->wock, fwags);

	if (spdif->active) {
		spin_unwock_iwqwestowe(&spdif->wock, fwags);
		wetuwn -EBUSY;
	}

	spdif->twk = ucontwow->vawue.integew.vawue[0];

	weg = img_spdif_in_weadw(spdif, IMG_SPDIF_IN_CTW);
	weg &= ~IMG_SPDIF_IN_CTW_TWK_MASK;
	weg |= spdif->twk << IMG_SPDIF_IN_CTW_TWK_SHIFT;
	img_spdif_in_wwitew(spdif, weg, IMG_SPDIF_IN_CTW);

	fow (i = 0; i < IMG_SPDIF_IN_NUM_ACWKGEN; i++) {
		spdif->acwkgen_wegs[i] = (spdif->acwkgen_wegs[i] &
			~IMG_SPDIF_IN_ACWKGEN_TWK_MASK) |
			(spdif->twk << IMG_SPDIF_IN_ACWKGEN_TWK_SHIFT);

		img_spdif_in_acwkgen_wwitew(spdif, i);
	}

	spin_unwock_iwqwestowe(&spdif->wock, fwags);

	wetuwn 0;
}

static int img_spdif_in_info_wock(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = -128;
	uinfo->vawue.integew.max = 127;

	wetuwn 0;
}

static int img_spdif_in_get_wock_acquiwe(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(cpu_dai);

	ucontwow->vawue.integew.vawue[0] = spdif->wock_acquiwe;

	wetuwn 0;
}

static int img_spdif_in_set_wock_acquiwe(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&spdif->wock, fwags);

	if (spdif->active) {
		spin_unwock_iwqwestowe(&spdif->wock, fwags);
		wetuwn -EBUSY;
	}

	spdif->wock_acquiwe = ucontwow->vawue.integew.vawue[0];

	weg = img_spdif_in_weadw(spdif, IMG_SPDIF_IN_CTW);
	weg &= ~IMG_SPDIF_IN_CTW_WOCKHI_MASK;
	weg |= (spdif->wock_acquiwe << IMG_SPDIF_IN_CTW_WOCKHI_SHIFT) &
		IMG_SPDIF_IN_CTW_WOCKHI_MASK;
	img_spdif_in_wwitew(spdif, weg, IMG_SPDIF_IN_CTW);

	spin_unwock_iwqwestowe(&spdif->wock, fwags);

	wetuwn 0;
}

static int img_spdif_in_get_wock_wewease(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(cpu_dai);

	ucontwow->vawue.integew.vawue[0] = spdif->wock_wewease;

	wetuwn 0;
}

static int img_spdif_in_set_wock_wewease(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(cpu_dai);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&spdif->wock, fwags);

	if (spdif->active) {
		spin_unwock_iwqwestowe(&spdif->wock, fwags);
		wetuwn -EBUSY;
	}

	spdif->wock_wewease = ucontwow->vawue.integew.vawue[0];

	weg = img_spdif_in_weadw(spdif, IMG_SPDIF_IN_CTW);
	weg &= ~IMG_SPDIF_IN_CTW_WOCKWO_MASK;
	weg |= (spdif->wock_wewease << IMG_SPDIF_IN_CTW_WOCKWO_SHIFT) &
		IMG_SPDIF_IN_CTW_WOCKWO_MASK;
	img_spdif_in_wwitew(spdif, weg, IMG_SPDIF_IN_CTW);

	spin_unwock_iwqwestowe(&spdif->wock, fwags);

	wetuwn 0;
}

static stwuct snd_kcontwow_new img_spdif_in_contwows[] = {
	{
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = SNDWV_CTW_NAME_IEC958("", CAPTUWE, MASK),
		.info = img_spdif_in_iec958_info,
		.get = img_spdif_in_get_status_mask
	},
	{
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD |
			SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = SNDWV_CTW_NAME_IEC958("", CAPTUWE, DEFAUWT),
		.info = img_spdif_in_iec958_info,
		.get = img_spdif_in_get_status
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = "SPDIF In Muwti Fwequency Acquiwe",
		.info = img_spdif_in_info_muwti_fweq,
		.get = img_spdif_in_get_muwti_fweq,
		.put = img_spdif_in_set_muwti_fweq
	},
	{
		.access = SNDWV_CTW_EWEM_ACCESS_WEAD |
			SNDWV_CTW_EWEM_ACCESS_VOWATIWE,
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = "SPDIF In Wock Fwequency",
		.info = img_spdif_in_info_wock_fweq,
		.get = img_spdif_in_get_wock_fweq
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = "SPDIF In Wock TWK",
		.info = img_spdif_in_info_twk,
		.get = img_spdif_in_get_twk,
		.put = img_spdif_in_set_twk
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = "SPDIF In Wock Acquiwe Thweshowd",
		.info = img_spdif_in_info_wock,
		.get = img_spdif_in_get_wock_acquiwe,
		.put = img_spdif_in_set_wock_acquiwe
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_PCM,
		.name = "SPDIF In Wock Wewease Thweshowd",
		.info = img_spdif_in_info_wock,
		.get = img_spdif_in_get_wock_wewease,
		.put = img_spdif_in_set_wock_wewease
	}
};

static int img_spdif_in_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
	stwuct snd_soc_dai *dai)
{
	unsigned wong fwags;
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(dai);
	int wet = 0;
	u32 weg;

	spin_wock_iwqsave(&spdif->wock, fwags);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		weg = img_spdif_in_weadw(spdif, IMG_SPDIF_IN_CTW);
		if (spdif->muwti_fweq)
			weg &= ~IMG_SPDIF_IN_CTW_SWD_MASK;
		ewse
			weg |= (1UW << IMG_SPDIF_IN_CTW_SWD_SHIFT);
		weg |= IMG_SPDIF_IN_CTW_SWT_MASK;
		img_spdif_in_wwitew(spdif, weg, IMG_SPDIF_IN_CTW);
		spdif->active = twue;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		weg = img_spdif_in_weadw(spdif, IMG_SPDIF_IN_CTW);
		weg &= ~IMG_SPDIF_IN_CTW_SWT_MASK;
		img_spdif_in_wwitew(spdif, weg, IMG_SPDIF_IN_CTW);
		spdif->active = fawse;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	spin_unwock_iwqwestowe(&spdif->wock, fwags);

	wetuwn wet;
}

static int img_spdif_in_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(dai);
	unsigned int wate, channews;
	snd_pcm_fowmat_t fowmat;

	wate = pawams_wate(pawams);
	channews = pawams_channews(pawams);
	fowmat = pawams_fowmat(pawams);

	if (fowmat != SNDWV_PCM_FOWMAT_S32_WE)
		wetuwn -EINVAW;

	if (channews != 2)
		wetuwn -EINVAW;

	wetuwn img_spdif_in_do_cwkgen_singwe(spdif, wate);
}

static int img_spdif_in_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct img_spdif_in *spdif = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai, NUWW, &spdif->dma_data);

	snd_soc_add_dai_contwows(dai, img_spdif_in_contwows,
			AWWAY_SIZE(img_spdif_in_contwows));

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops img_spdif_in_dai_ops = {
	.pwobe		= img_spdif_in_dai_pwobe,
	.twiggew	= img_spdif_in_twiggew,
	.hw_pawams	= img_spdif_in_hw_pawams
};

static stwuct snd_soc_dai_dwivew img_spdif_in_dai = {
	.captuwe = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = SNDWV_PCM_FMTBIT_S32_WE
	},
	.ops = &img_spdif_in_dai_ops
};

static const stwuct snd_soc_component_dwivew img_spdif_in_component = {
	.name = "img-spdif-in",
	.wegacy_dai_naming = 1,
};

static int img_spdif_in_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct img_spdif_in *spdif;
	stwuct wesouwce *wes;
	void __iomem *base;
	int wet;
	stwuct weset_contwow *wst;
	u32 weg;
	stwuct device *dev = &pdev->dev;

	spdif = devm_kzawwoc(&pdev->dev, sizeof(*spdif), GFP_KEWNEW);
	if (!spdif)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, spdif);

	spdif->dev = &pdev->dev;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	spdif->base = base;

	spdif->cwk_sys = devm_cwk_get(dev, "sys");
	if (IS_EWW(spdif->cwk_sys))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(spdif->cwk_sys),
				     "Faiwed to acquiwe cwock 'sys'\n");

	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = img_spdif_in_wuntime_wesume(&pdev->dev);
		if (wet)
			goto eww_pm_disabwe;
	}
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0)
		goto eww_suspend;

	wst = devm_weset_contwow_get_excwusive(&pdev->dev, "wst");
	if (IS_EWW(wst)) {
		if (PTW_EWW(wst) == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto eww_pm_put;
		}
		dev_dbg(dev, "No top wevew weset found\n");
		img_spdif_in_wwitew(spdif, IMG_SPDIF_IN_SOFT_WESET_MASK,
				IMG_SPDIF_IN_SOFT_WESET);
		img_spdif_in_wwitew(spdif, 0, IMG_SPDIF_IN_SOFT_WESET);
	} ewse {
		weset_contwow_assewt(wst);
		weset_contwow_deassewt(wst);
	}

	spin_wock_init(&spdif->wock);

	spdif->dma_data.addw = wes->stawt + IMG_SPDIF_IN_WX_FIFO_OFFSET;
	spdif->dma_data.addw_width = 4;
	spdif->dma_data.maxbuwst = 4;
	spdif->twk = 0x80;
	spdif->wock_acquiwe = 4;
	spdif->wock_wewease = -128;

	weg = (spdif->wock_acquiwe << IMG_SPDIF_IN_CTW_WOCKHI_SHIFT) &
		IMG_SPDIF_IN_CTW_WOCKHI_MASK;
	weg |= (spdif->wock_wewease << IMG_SPDIF_IN_CTW_WOCKWO_SHIFT) &
		IMG_SPDIF_IN_CTW_WOCKWO_MASK;
	weg |= (spdif->twk << IMG_SPDIF_IN_CTW_TWK_SHIFT) &
		IMG_SPDIF_IN_CTW_TWK_MASK;
	img_spdif_in_wwitew(spdif, weg, IMG_SPDIF_IN_CTW);

	pm_wuntime_put(&pdev->dev);

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
			&img_spdif_in_component, &img_spdif_in_dai, 1);
	if (wet)
		goto eww_suspend;

	wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, 0);
	if (wet)
		goto eww_suspend;

	wetuwn 0;

eww_pm_put:
	pm_wuntime_put(&pdev->dev);
eww_suspend:
	if (!pm_wuntime_enabwed(&pdev->dev))
		img_spdif_in_wuntime_suspend(&pdev->dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void img_spdif_in_dev_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		img_spdif_in_wuntime_suspend(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int img_spdif_in_suspend(stwuct device *dev)
{
	stwuct img_spdif_in *spdif = dev_get_dwvdata(dev);
	int wet;

	if (pm_wuntime_status_suspended(dev)) {
		wet = img_spdif_in_wuntime_wesume(dev);
		if (wet)
			wetuwn wet;
	}

	spdif->suspend_cwkgen = img_spdif_in_weadw(spdif, IMG_SPDIF_IN_CWKGEN);
	spdif->suspend_ctw = img_spdif_in_weadw(spdif, IMG_SPDIF_IN_CTW);

	img_spdif_in_wuntime_suspend(dev);

	wetuwn 0;
}

static int img_spdif_in_wesume(stwuct device *dev)
{
	stwuct img_spdif_in *spdif = dev_get_dwvdata(dev);
	int i, wet;

	wet = img_spdif_in_wuntime_wesume(dev);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < IMG_SPDIF_IN_NUM_ACWKGEN; i++)
		img_spdif_in_acwkgen_wwitew(spdif, i);

	img_spdif_in_wwitew(spdif, spdif->suspend_cwkgen, IMG_SPDIF_IN_CWKGEN);
	img_spdif_in_wwitew(spdif, spdif->suspend_ctw, IMG_SPDIF_IN_CTW);

	if (pm_wuntime_status_suspended(dev))
		img_spdif_in_wuntime_suspend(dev);

	wetuwn 0;
}
#endif

static const stwuct of_device_id img_spdif_in_of_match[] = {
	{ .compatibwe = "img,spdif-in" },
	{}
};
MODUWE_DEVICE_TABWE(of, img_spdif_in_of_match);

static const stwuct dev_pm_ops img_spdif_in_pm_ops = {
	SET_WUNTIME_PM_OPS(img_spdif_in_wuntime_suspend,
			   img_spdif_in_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(img_spdif_in_suspend, img_spdif_in_wesume)
};

static stwuct pwatfowm_dwivew img_spdif_in_dwivew = {
	.dwivew = {
		.name = "img-spdif-in",
		.of_match_tabwe = img_spdif_in_of_match,
		.pm = &img_spdif_in_pm_ops
	},
	.pwobe = img_spdif_in_pwobe,
	.wemove_new = img_spdif_in_dev_wemove
};
moduwe_pwatfowm_dwivew(img_spdif_in_dwivew);

MODUWE_AUTHOW("Damien Howswey <Damien.Howswey@imgtec.com>");
MODUWE_DESCWIPTION("IMG SPDIF Input dwivew");
MODUWE_WICENSE("GPW v2");
