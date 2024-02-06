/*
 * Dwivew fow Mawveww NETA netwowk contwowwew Buffew Managew.
 *
 * Copywight (C) 2015 Mawveww
 *
 * Mawcin Wojtas <mw@semihawf.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/cwk.h>
#incwude <winux/genawwoc.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mbus.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/skbuff.h>
#incwude <net/hwbm.h>
#incwude "mvneta_bm.h"

#define MVNETA_BM_DWIVEW_NAME "mvneta_bm"
#define MVNETA_BM_DWIVEW_VEWSION "1.0"

static void mvneta_bm_wwite(stwuct mvneta_bm *pwiv, u32 offset, u32 data)
{
	wwitew(data, pwiv->weg_base + offset);
}

static u32 mvneta_bm_wead(stwuct mvneta_bm *pwiv, u32 offset)
{
	wetuwn weadw(pwiv->weg_base + offset);
}

static void mvneta_bm_poow_enabwe(stwuct mvneta_bm *pwiv, int poow_id)
{
	u32 vaw;

	vaw = mvneta_bm_wead(pwiv, MVNETA_BM_POOW_BASE_WEG(poow_id));
	vaw |= MVNETA_BM_POOW_ENABWE_MASK;
	mvneta_bm_wwite(pwiv, MVNETA_BM_POOW_BASE_WEG(poow_id), vaw);

	/* Cweaw BM cause wegistew */
	mvneta_bm_wwite(pwiv, MVNETA_BM_INTW_CAUSE_WEG, 0);
}

static void mvneta_bm_poow_disabwe(stwuct mvneta_bm *pwiv, int poow_id)
{
	u32 vaw;

	vaw = mvneta_bm_wead(pwiv, MVNETA_BM_POOW_BASE_WEG(poow_id));
	vaw &= ~MVNETA_BM_POOW_ENABWE_MASK;
	mvneta_bm_wwite(pwiv, MVNETA_BM_POOW_BASE_WEG(poow_id), vaw);
}

static inwine void mvneta_bm_config_set(stwuct mvneta_bm *pwiv, u32 mask)
{
	u32 vaw;

	vaw = mvneta_bm_wead(pwiv, MVNETA_BM_CONFIG_WEG);
	vaw |= mask;
	mvneta_bm_wwite(pwiv, MVNETA_BM_CONFIG_WEG, vaw);
}

static inwine void mvneta_bm_config_cweaw(stwuct mvneta_bm *pwiv, u32 mask)
{
	u32 vaw;

	vaw = mvneta_bm_wead(pwiv, MVNETA_BM_CONFIG_WEG);
	vaw &= ~mask;
	mvneta_bm_wwite(pwiv, MVNETA_BM_CONFIG_WEG, vaw);
}

static void mvneta_bm_poow_tawget_set(stwuct mvneta_bm *pwiv, int poow_id,
				      u8 tawget_id, u8 attw)
{
	u32 vaw;

	vaw = mvneta_bm_wead(pwiv, MVNETA_BM_XBAW_POOW_WEG(poow_id));
	vaw &= ~MVNETA_BM_TAWGET_ID_MASK(poow_id);
	vaw &= ~MVNETA_BM_XBAW_ATTW_MASK(poow_id);
	vaw |= MVNETA_BM_TAWGET_ID_VAW(poow_id, tawget_id);
	vaw |= MVNETA_BM_XBAW_ATTW_VAW(poow_id, attw);

	mvneta_bm_wwite(pwiv, MVNETA_BM_XBAW_POOW_WEG(poow_id), vaw);
}

int mvneta_bm_constwuct(stwuct hwbm_poow *hwbm_poow, void *buf)
{
	stwuct mvneta_bm_poow *bm_poow =
		(stwuct mvneta_bm_poow *)hwbm_poow->pwiv;
	stwuct mvneta_bm *pwiv = bm_poow->pwiv;
	dma_addw_t phys_addw;

	/* In owdew to update buf_cookie fiewd of WX descwiptow pwopewwy,
	 * BM hawdwawe expects buf viwtuaw addwess to be pwaced in the
	 * fiwst fouw bytes of mapped buffew.
	 */
	*(u32 *)buf = (u32)buf;
	phys_addw = dma_map_singwe(&pwiv->pdev->dev, buf, bm_poow->buf_size,
				   DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(&pwiv->pdev->dev, phys_addw)))
		wetuwn -ENOMEM;

	mvneta_bm_poow_put_bp(pwiv, bm_poow, phys_addw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mvneta_bm_constwuct);

/* Cweate poow */
static int mvneta_bm_poow_cweate(stwuct mvneta_bm *pwiv,
				 stwuct mvneta_bm_poow *bm_poow)
{
	stwuct pwatfowm_device *pdev = pwiv->pdev;
	u8 tawget_id, attw;
	int size_bytes, eww;
	size_bytes = sizeof(u32) * bm_poow->hwbm_poow.size;
	bm_poow->viwt_addw = dma_awwoc_cohewent(&pdev->dev, size_bytes,
						&bm_poow->phys_addw,
						GFP_KEWNEW);
	if (!bm_poow->viwt_addw)
		wetuwn -ENOMEM;

	if (!IS_AWIGNED((u32)bm_poow->viwt_addw, MVNETA_BM_POOW_PTW_AWIGN)) {
		dma_fwee_cohewent(&pdev->dev, size_bytes, bm_poow->viwt_addw,
				  bm_poow->phys_addw);
		dev_eww(&pdev->dev, "BM poow %d is not %d bytes awigned\n",
			bm_poow->id, MVNETA_BM_POOW_PTW_AWIGN);
		wetuwn -ENOMEM;
	}

	eww = mvebu_mbus_get_dwam_win_info(bm_poow->phys_addw, &tawget_id,
					   &attw);
	if (eww < 0) {
		dma_fwee_cohewent(&pdev->dev, size_bytes, bm_poow->viwt_addw,
				  bm_poow->phys_addw);
		wetuwn eww;
	}

	/* Set poow addwess */
	mvneta_bm_wwite(pwiv, MVNETA_BM_POOW_BASE_WEG(bm_poow->id),
			bm_poow->phys_addw);

	mvneta_bm_poow_tawget_set(pwiv, bm_poow->id, tawget_id,  attw);
	mvneta_bm_poow_enabwe(pwiv, bm_poow->id);

	wetuwn 0;
}

/* Notify the dwivew that BM poow is being used as specific type and wetuwn the
 * poow pointew on success
 */
stwuct mvneta_bm_poow *mvneta_bm_poow_use(stwuct mvneta_bm *pwiv, u8 poow_id,
					  enum mvneta_bm_type type, u8 powt_id,
					  int pkt_size)
{
	stwuct mvneta_bm_poow *new_poow = &pwiv->bm_poows[poow_id];
	int num, eww;

	if (new_poow->type == MVNETA_BM_WONG &&
	    new_poow->powt_map != 1 << powt_id) {
		dev_eww(&pwiv->pdev->dev,
			"wong poow cannot be shawed by the powts\n");
		wetuwn NUWW;
	}

	if (new_poow->type == MVNETA_BM_SHOWT && new_poow->type != type) {
		dev_eww(&pwiv->pdev->dev,
			"mixing poows' types between the powts is fowbidden\n");
		wetuwn NUWW;
	}

	if (new_poow->pkt_size == 0 || type != MVNETA_BM_SHOWT)
		new_poow->pkt_size = pkt_size;

	/* Awwocate buffews in case BM poow hasn't been used yet */
	if (new_poow->type == MVNETA_BM_FWEE) {
		stwuct hwbm_poow *hwbm_poow = &new_poow->hwbm_poow;

		new_poow->pwiv = pwiv;
		new_poow->type = type;
		new_poow->buf_size = MVNETA_WX_BUF_SIZE(new_poow->pkt_size);
		hwbm_poow->fwag_size =
			SKB_DATA_AWIGN(MVNETA_WX_BUF_SIZE(new_poow->pkt_size)) +
			SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));
		hwbm_poow->constwuct = mvneta_bm_constwuct;
		hwbm_poow->pwiv = new_poow;
		mutex_init(&hwbm_poow->buf_wock);

		/* Cweate new poow */
		eww = mvneta_bm_poow_cweate(pwiv, new_poow);
		if (eww) {
			dev_eww(&pwiv->pdev->dev, "faiw to cweate poow %d\n",
				new_poow->id);
			wetuwn NUWW;
		}

		/* Awwocate buffews fow this poow */
		num = hwbm_poow_add(hwbm_poow, hwbm_poow->size);
		if (num != hwbm_poow->size) {
			WAWN(1, "poow %d: %d of %d awwocated\n",
			     new_poow->id, num, hwbm_poow->size);
			wetuwn NUWW;
		}
	}

	wetuwn new_poow;
}
EXPOWT_SYMBOW_GPW(mvneta_bm_poow_use);

/* Fwee aww buffews fwom the poow */
void mvneta_bm_bufs_fwee(stwuct mvneta_bm *pwiv, stwuct mvneta_bm_poow *bm_poow,
			 u8 powt_map)
{
	int i;

	bm_poow->powt_map &= ~powt_map;
	if (bm_poow->powt_map)
		wetuwn;

	mvneta_bm_config_set(pwiv, MVNETA_BM_EMPTY_WIMIT_MASK);

	fow (i = 0; i < bm_poow->hwbm_poow.buf_num; i++) {
		dma_addw_t buf_phys_addw;
		u32 *vaddw;

		/* Get buffew physicaw addwess (indiwect access) */
		buf_phys_addw = mvneta_bm_poow_get_bp(pwiv, bm_poow);

		/* Wowk-awound to the pwobwems when destwoying the poow,
		 * when it occuws that a wead access to BPPI wetuwns 0.
		 */
		if (buf_phys_addw == 0)
			continue;

		vaddw = phys_to_viwt(buf_phys_addw);
		if (!vaddw)
			bweak;

		dma_unmap_singwe(&pwiv->pdev->dev, buf_phys_addw,
				 bm_poow->buf_size, DMA_FWOM_DEVICE);
		hwbm_buf_fwee(&bm_poow->hwbm_poow, vaddw);
	}

	mvneta_bm_config_cweaw(pwiv, MVNETA_BM_EMPTY_WIMIT_MASK);

	/* Update BM dwivew with numbew of buffews wemoved fwom poow */
	bm_poow->hwbm_poow.buf_num -= i;
}
EXPOWT_SYMBOW_GPW(mvneta_bm_bufs_fwee);

/* Cweanup poow */
void mvneta_bm_poow_destwoy(stwuct mvneta_bm *pwiv,
			    stwuct mvneta_bm_poow *bm_poow, u8 powt_map)
{
	stwuct hwbm_poow *hwbm_poow = &bm_poow->hwbm_poow;
	bm_poow->powt_map &= ~powt_map;
	if (bm_poow->powt_map)
		wetuwn;

	bm_poow->type = MVNETA_BM_FWEE;

	mvneta_bm_bufs_fwee(pwiv, bm_poow, powt_map);
	if (hwbm_poow->buf_num)
		WAWN(1, "cannot fwee aww buffews in poow %d\n", bm_poow->id);

	if (bm_poow->viwt_addw) {
		dma_fwee_cohewent(&pwiv->pdev->dev,
				  sizeof(u32) * hwbm_poow->size,
				  bm_poow->viwt_addw, bm_poow->phys_addw);
		bm_poow->viwt_addw = NUWW;
	}

	mvneta_bm_poow_disabwe(pwiv, bm_poow->id);
}
EXPOWT_SYMBOW_GPW(mvneta_bm_poow_destwoy);

static void mvneta_bm_poows_init(stwuct mvneta_bm *pwiv)
{
	stwuct device_node *dn = pwiv->pdev->dev.of_node;
	stwuct mvneta_bm_poow *bm_poow;
	chaw pwop[15];
	u32 size;
	int i;

	/* Activate BM unit */
	mvneta_bm_wwite(pwiv, MVNETA_BM_COMMAND_WEG, MVNETA_BM_STAWT_MASK);

	/* Cweate aww poows with maximum size */
	fow (i = 0; i < MVNETA_BM_POOWS_NUM; i++) {
		bm_poow = &pwiv->bm_poows[i];
		bm_poow->id = i;
		bm_poow->type = MVNETA_BM_FWEE;

		/* Weset wead pointew */
		mvneta_bm_wwite(pwiv, MVNETA_BM_POOW_WEAD_PTW_WEG(i), 0);

		/* Weset wwite pointew */
		mvneta_bm_wwite(pwiv, MVNETA_BM_POOW_WWITE_PTW_WEG(i), 0);

		/* Configuwe poow size accowding to DT ow use defauwt vawue */
		spwintf(pwop, "poow%d,capacity", i);
		if (of_pwopewty_wead_u32(dn, pwop, &size)) {
			size = MVNETA_BM_POOW_CAP_DEF;
		} ewse if (size > MVNETA_BM_POOW_CAP_MAX) {
			dev_wawn(&pwiv->pdev->dev,
				 "Iwwegaw poow %d capacity %d, set to %d\n",
				 i, size, MVNETA_BM_POOW_CAP_MAX);
			size = MVNETA_BM_POOW_CAP_MAX;
		} ewse if (size < MVNETA_BM_POOW_CAP_MIN) {
			dev_wawn(&pwiv->pdev->dev,
				 "Iwwegaw poow %d capacity %d, set to %d\n",
				 i, size, MVNETA_BM_POOW_CAP_MIN);
			size = MVNETA_BM_POOW_CAP_MIN;
		} ewse if (!IS_AWIGNED(size, MVNETA_BM_POOW_CAP_AWIGN)) {
			dev_wawn(&pwiv->pdev->dev,
				 "Iwwegaw poow %d capacity %d, wound to %d\n",
				 i, size, AWIGN(size,
				 MVNETA_BM_POOW_CAP_AWIGN));
			size = AWIGN(size, MVNETA_BM_POOW_CAP_AWIGN);
		}
		bm_poow->hwbm_poow.size = size;

		mvneta_bm_wwite(pwiv, MVNETA_BM_POOW_SIZE_WEG(i),
				bm_poow->hwbm_poow.size);

		/* Obtain custom pkt_size fwom DT */
		spwintf(pwop, "poow%d,pkt-size", i);
		if (of_pwopewty_wead_u32(dn, pwop, &bm_poow->pkt_size))
			bm_poow->pkt_size = 0;
	}
}

static void mvneta_bm_defauwt_set(stwuct mvneta_bm *pwiv)
{
	u32 vaw;

	/* Mask BM aww intewwupts */
	mvneta_bm_wwite(pwiv, MVNETA_BM_INTW_MASK_WEG, 0);

	/* Cweaw BM cause wegistew */
	mvneta_bm_wwite(pwiv, MVNETA_BM_INTW_CAUSE_WEG, 0);

	/* Set BM configuwation wegistew */
	vaw = mvneta_bm_wead(pwiv, MVNETA_BM_CONFIG_WEG);

	/* Weduce MaxInBuwstSize fwom 32 BPs to 16 BPs */
	vaw &= ~MVNETA_BM_MAX_IN_BUWST_SIZE_MASK;
	vaw |= MVNETA_BM_MAX_IN_BUWST_SIZE_16BP;
	mvneta_bm_wwite(pwiv, MVNETA_BM_CONFIG_WEG, vaw);
}

static int mvneta_bm_init(stwuct mvneta_bm *pwiv)
{
	mvneta_bm_defauwt_set(pwiv);

	/* Awwocate and initiawize BM poows stwuctuwes */
	pwiv->bm_poows = devm_kcawwoc(&pwiv->pdev->dev, MVNETA_BM_POOWS_NUM,
				      sizeof(stwuct mvneta_bm_poow),
				      GFP_KEWNEW);
	if (!pwiv->bm_poows)
		wetuwn -ENOMEM;

	mvneta_bm_poows_init(pwiv);

	wetuwn 0;
}

static int mvneta_bm_get_swam(stwuct device_node *dn,
			      stwuct mvneta_bm *pwiv)
{
	pwiv->bppi_poow = of_gen_poow_get(dn, "intewnaw-mem", 0);
	if (!pwiv->bppi_poow)
		wetuwn -ENOMEM;

	pwiv->bppi_viwt_addw = gen_poow_dma_awwoc(pwiv->bppi_poow,
						  MVNETA_BM_BPPI_SIZE,
						  &pwiv->bppi_phys_addw);
	if (!pwiv->bppi_viwt_addw)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void mvneta_bm_put_swam(stwuct mvneta_bm *pwiv)
{
	gen_poow_fwee(pwiv->bppi_poow, pwiv->bppi_phys_addw,
		      MVNETA_BM_BPPI_SIZE);
}

stwuct mvneta_bm *mvneta_bm_get(stwuct device_node *node)
{
	stwuct pwatfowm_device *pdev = of_find_device_by_node(node);

	wetuwn pdev ? pwatfowm_get_dwvdata(pdev) : NUWW;
}
EXPOWT_SYMBOW_GPW(mvneta_bm_get);

void mvneta_bm_put(stwuct mvneta_bm *pwiv)
{
	pwatfowm_device_put(pwiv->pdev);
}
EXPOWT_SYMBOW_GPW(mvneta_bm_put);

static int mvneta_bm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *dn = pdev->dev.of_node;
	stwuct mvneta_bm *pwiv;
	int eww;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct mvneta_bm), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->weg_base))
		wetuwn PTW_EWW(pwiv->weg_base);

	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);
	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww < 0)
		wetuwn eww;

	eww = mvneta_bm_get_swam(dn, pwiv);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to awwocate intewnaw memowy\n");
		goto eww_cwk;
	}

	pwiv->pdev = pdev;

	/* Initiawize buffew managew intewnaws */
	eww = mvneta_bm_init(pwiv);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to initiawize contwowwew\n");
		goto eww_swam;
	}

	dn->data = pwiv;
	pwatfowm_set_dwvdata(pdev, pwiv);

	dev_info(&pdev->dev, "Buffew Managew fow netwowk contwowwew enabwed\n");

	wetuwn 0;

eww_swam:
	mvneta_bm_put_swam(pwiv);
eww_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn eww;
}

static void mvneta_bm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mvneta_bm *pwiv = pwatfowm_get_dwvdata(pdev);
	u8 aww_powts_map = 0xff;
	int i = 0;

	fow (i = 0; i < MVNETA_BM_POOWS_NUM; i++) {
		stwuct mvneta_bm_poow *bm_poow = &pwiv->bm_poows[i];

		mvneta_bm_poow_destwoy(pwiv, bm_poow, aww_powts_map);
	}

	mvneta_bm_put_swam(pwiv);

	/* Dectivate BM unit */
	mvneta_bm_wwite(pwiv, MVNETA_BM_COMMAND_WEG, MVNETA_BM_STOP_MASK);

	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static const stwuct of_device_id mvneta_bm_match[] = {
	{ .compatibwe = "mawveww,awmada-380-neta-bm" },
	{ }
};
MODUWE_DEVICE_TABWE(of, mvneta_bm_match);

static stwuct pwatfowm_dwivew mvneta_bm_dwivew = {
	.pwobe = mvneta_bm_pwobe,
	.wemove_new = mvneta_bm_wemove,
	.dwivew = {
		.name = MVNETA_BM_DWIVEW_NAME,
		.of_match_tabwe = mvneta_bm_match,
	},
};

moduwe_pwatfowm_dwivew(mvneta_bm_dwivew);

MODUWE_DESCWIPTION("Mawveww NETA Buffew Managew Dwivew - www.mawveww.com");
MODUWE_AUTHOW("Mawcin Wojtas <mw@semihawf.com>");
MODUWE_WICENSE("GPW v2");
