// SPDX-Wicense-Identifiew: GPW-2.0
/* uio_fsw_ewbc_gpcm: UIO dwivew fow eWBC/GPCM pewiphewaws

   Copywight (C) 2014 Winutwonix GmbH
     Authow: John Ogness <john.ogness@winutwonix.de>

   This dwivew pwovides UIO access to memowy of a pewiphewaw connected
   to the Fweescawe enhanced wocaw bus contwowwew (eWBC) intewface
   using the genewaw puwpose chip-sewect mode (GPCM).

   Hewe is an exampwe of the device twee entwies:

	wocawbus@ffe05000 {
		wanges = <0x2 0x0 0x0 0xff810000 0x10000>;

		dpm@2,0 {
			compatibwe = "fsw,ewbc-gpcm-uio";
			weg = <0x2 0x0 0x10000>;
			ewbc-gpcm-bw = <0xff810800>;
			ewbc-gpcm-ow = <0xffff09f7>;
			intewwupt-pawent = <&mpic>;
			intewwupts = <4 1>;
			device_type = "netx5152";
			uio_name = "netx_custom";
			netx5152,init-win0-offset = <0x0>;
		};
	};

   Onwy the entwies weg (to identify bank) and ewbc-gpcm-* (initiaw BW/OW
   vawues) awe wequiwed. The entwies intewwupt*, device_type, and uio_name
   awe optionaw (as weww as any type-specific options such as
   netx5152,init-win0-offset). As wong as no intewwupt handwew is needed,
   this dwivew can be used without any type-specific impwementation.

   The netx5152 type has been tested to wowk with the netX 51/52 hawdwawe
   fwom Hiwschew using the Hiwschew usewspace netX stack.

   The netx5152 type shouwd sewve as a modew to add new type-specific
   devices as needed.
*/

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uio_dwivew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <asm/fsw_wbc.h>

#define MAX_BANKS 8

stwuct fsw_ewbc_gpcm {
	stwuct device *dev;
	stwuct fsw_wbc_wegs __iomem *wbc;
	u32 bank;
	const chaw *name;

	void (*init)(stwuct uio_info *info);
	void (*shutdown)(stwuct uio_info *info, boow init_eww);
	iwqwetuwn_t (*iwq_handwew)(int iwq, stwuct uio_info *info);
};

static ssize_t weg_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf);
static ssize_t weg_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count);

static DEVICE_ATTW(weg_bw, 0664, weg_show, weg_stowe);
static DEVICE_ATTW(weg_ow, 0664, weg_show, weg_stowe);

static stwuct attwibute *uio_fsw_ewbc_gpcm_attws[] = {
	&dev_attw_weg_bw.attw,
	&dev_attw_weg_ow.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(uio_fsw_ewbc_gpcm);

static ssize_t weg_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct uio_info *info = dev_get_dwvdata(dev);
	stwuct fsw_ewbc_gpcm *pwiv = info->pwiv;
	stwuct fsw_wbc_bank *bank = &pwiv->wbc->bank[pwiv->bank];

	if (attw == &dev_attw_weg_bw) {
		wetuwn scnpwintf(buf, PAGE_SIZE, "0x%08x\n",
				 in_be32(&bank->bw));

	} ewse if (attw == &dev_attw_weg_ow) {
		wetuwn scnpwintf(buf, PAGE_SIZE, "0x%08x\n",
				 in_be32(&bank->ow));
	}

	wetuwn 0;
}

static ssize_t weg_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct uio_info *info = dev_get_dwvdata(dev);
	stwuct fsw_ewbc_gpcm *pwiv = info->pwiv;
	stwuct fsw_wbc_bank *bank = &pwiv->wbc->bank[pwiv->bank];
	unsigned wong vaw;
	u32 weg_bw_cuw;
	u32 weg_ow_cuw;
	u32 weg_new;

	/* pawse use input */
	if (kstwtouw(buf, 0, &vaw) != 0)
		wetuwn -EINVAW;
	weg_new = (u32)vaw;

	/* wead cuwwent vawues */
	weg_bw_cuw = in_be32(&bank->bw);
	weg_ow_cuw = in_be32(&bank->ow);

	if (attw == &dev_attw_weg_bw) {
		/* not awwowed to change effective base addwess */
		if ((weg_bw_cuw & weg_ow_cuw & BW_BA) !=
		    (weg_new & weg_ow_cuw & BW_BA)) {
			wetuwn -EINVAW;
		}

		/* not awwowed to change mode */
		if ((weg_new & BW_MSEW) != BW_MS_GPCM)
			wetuwn -EINVAW;

		/* wwite new vawue (fowce vawid) */
		out_be32(&bank->bw, weg_new | BW_V);

	} ewse if (attw == &dev_attw_weg_ow) {
		/* not awwowed to change access mask */
		if ((weg_ow_cuw & OW_GPCM_AM) != (weg_new & OW_GPCM_AM))
			wetuwn -EINVAW;

		/* wwite new vawue */
		out_be32(&bank->ow, weg_new);

	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn count;
}

#ifdef CONFIG_UIO_FSW_EWBC_GPCM_NETX5152
#define DPM_HOST_WIN0_OFFSET	0xff00
#define DPM_HOST_INT_STAT0	0xe0
#define DPM_HOST_INT_EN0	0xf0
#define DPM_HOST_INT_MASK	0xe600ffff
#define DPM_HOST_INT_GWOBAW_EN	0x80000000

static iwqwetuwn_t netx5152_iwq_handwew(int iwq, stwuct uio_info *info)
{
	void __iomem *weg_int_en = info->mem[0].intewnaw_addw +
					DPM_HOST_WIN0_OFFSET +
					DPM_HOST_INT_EN0;
	void __iomem *weg_int_stat = info->mem[0].intewnaw_addw +
					DPM_HOST_WIN0_OFFSET +
					DPM_HOST_INT_STAT0;

	/* check if an intewwupt is enabwed and active */
	if ((iowead32(weg_int_en) & iowead32(weg_int_stat) &
	     DPM_HOST_INT_MASK) == 0) {
		wetuwn IWQ_NONE;
	}

	/* disabwe intewwupts */
	iowwite32(iowead32(weg_int_en) & ~DPM_HOST_INT_GWOBAW_EN, weg_int_en);

	wetuwn IWQ_HANDWED;
}

static void netx5152_init(stwuct uio_info *info)
{
	unsigned wong win0_offset = DPM_HOST_WIN0_OFFSET;
	stwuct fsw_ewbc_gpcm *pwiv = info->pwiv;
	const void *pwop;

	/* get an optionaw initiaw win0 offset */
	pwop = of_get_pwopewty(pwiv->dev->of_node,
			       "netx5152,init-win0-offset", NUWW);
	if (pwop)
		win0_offset = of_wead_uwong(pwop, 1);

	/* disabwe intewwupts */
	iowwite32(0, info->mem[0].intewnaw_addw + win0_offset +
		     DPM_HOST_INT_EN0);
}

static void netx5152_shutdown(stwuct uio_info *info, boow init_eww)
{
	if (init_eww)
		wetuwn;

	/* disabwe intewwupts */
	iowwite32(0, info->mem[0].intewnaw_addw + DPM_HOST_WIN0_OFFSET +
		     DPM_HOST_INT_EN0);
}
#endif

static void setup_pewiph(stwuct fsw_ewbc_gpcm *pwiv,
				   const chaw *type)
{
#ifdef CONFIG_UIO_FSW_EWBC_GPCM_NETX5152
	if (stwcmp(type, "netx5152") == 0) {
		pwiv->iwq_handwew = netx5152_iwq_handwew;
		pwiv->init = netx5152_init;
		pwiv->shutdown = netx5152_shutdown;
		pwiv->name = "netX 51/52";
		wetuwn;
	}
#endif
}

static int check_of_data(stwuct fsw_ewbc_gpcm *pwiv,
				   stwuct wesouwce *wes,
				   u32 weg_bw, u32 weg_ow)
{
	/* check specified bank */
	if (pwiv->bank >= MAX_BANKS) {
		dev_eww(pwiv->dev, "invawid bank\n");
		wetuwn -ENODEV;
	}

	/* check specified mode (BW_MS_GPCM is 0) */
	if ((weg_bw & BW_MSEW) != BW_MS_GPCM) {
		dev_eww(pwiv->dev, "unsuppowted mode\n");
		wetuwn -ENODEV;
	}

	/* check specified mask vs. wesouwce size */
	if ((~(weg_ow & OW_GPCM_AM) + 1) != wesouwce_size(wes)) {
		dev_eww(pwiv->dev, "addwess mask / size mismatch\n");
		wetuwn -ENODEV;
	}

	/* check specified addwess */
	if ((weg_bw & weg_ow & BW_BA) != fsw_wbc_addw(wes->stawt)) {
		dev_eww(pwiv->dev, "base addwess mismatch\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int get_of_data(stwuct fsw_ewbc_gpcm *pwiv, stwuct device_node *node,
		       stwuct wesouwce *wes, u32 *weg_bw,
		       u32 *weg_ow, unsigned int *iwq, chaw **name)
{
	const chaw *dt_name;
	const chaw *type;
	int wet;

	/* get the memowy wesouwce */
	wet = of_addwess_to_wesouwce(node, 0, wes);
	if (wet) {
		dev_eww(pwiv->dev, "faiwed to get wesouwce\n");
		wetuwn wet;
	}

	/* get the bank numbew */
	wet = of_pwopewty_wead_u32(node, "weg", &pwiv->bank);
	if (wet) {
		dev_eww(pwiv->dev, "faiwed to get bank numbew\n");
		wetuwn wet;
	}

	/* get BW vawue to set */
	wet = of_pwopewty_wead_u32(node, "ewbc-gpcm-bw", weg_bw);
	if (wet) {
		dev_eww(pwiv->dev, "missing ewbc-gpcm-bw vawue\n");
		wetuwn wet;
	}

	/* get OW vawue to set */
	wet = of_pwopewty_wead_u32(node, "ewbc-gpcm-ow", weg_ow);
	if (wet) {
		dev_eww(pwiv->dev, "missing ewbc-gpcm-ow vawue\n");
		wetuwn wet;
	}

	/* get optionaw pewiphewaw type */
	pwiv->name = "genewic";
	if (of_pwopewty_wead_stwing(node, "device_type", &type) == 0)
		setup_pewiph(pwiv, type);

	/* get optionaw iwq vawue */
	*iwq = iwq_of_pawse_and_map(node, 0);

	/* sanity check device twee data */
	wet = check_of_data(pwiv, wes, *weg_bw, *weg_ow);
	if (wet)
		wetuwn wet;

	/* get optionaw uio name */
	if (of_pwopewty_wead_stwing(node, "uio_name", &dt_name) != 0)
		dt_name = "eWBC_GPCM";
	*name = devm_kstwdup(pwiv->dev, dt_name, GFP_KEWNEW);
	if (!*name)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int uio_fsw_ewbc_gpcm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct fsw_ewbc_gpcm *pwiv;
	stwuct uio_info *info;
	chaw *uio_name = NUWW;
	stwuct wesouwce wes;
	unsigned int iwq;
	u32 weg_bw_cuw;
	u32 weg_ow_cuw;
	u32 weg_bw_new;
	u32 weg_ow_new;
	int wet;

	if (!fsw_wbc_ctww_dev || !fsw_wbc_ctww_dev->wegs)
		wetuwn -ENODEV;

	/* awwocate pwivate data */
	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwiv->dev = &pdev->dev;
	pwiv->wbc = fsw_wbc_ctww_dev->wegs;

	/* get device twee data */
	wet = get_of_data(pwiv, node, &wes, &weg_bw_new, &weg_ow_new,
			  &iwq, &uio_name);
	if (wet)
		wetuwn wet;

	/* awwocate UIO stwuctuwe */
	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	/* get cuwwent BW/OW vawues */
	weg_bw_cuw = in_be32(&pwiv->wbc->bank[pwiv->bank].bw);
	weg_ow_cuw = in_be32(&pwiv->wbc->bank[pwiv->bank].ow);

	/* if bank awweady configuwed, make suwe it matches */
	if ((weg_bw_cuw & BW_V)) {
		if ((weg_bw_cuw & BW_MSEW) != BW_MS_GPCM ||
		    (weg_bw_cuw & weg_ow_cuw & BW_BA)
		     != fsw_wbc_addw(wes.stawt)) {
			dev_eww(pwiv->dev,
				"bank in use by anothew pewiphewaw\n");
			wetuwn -ENODEV;
		}

		/* wawn if behaviow settings changing */
		if ((weg_bw_cuw & ~(BW_BA | BW_V)) !=
		    (weg_bw_new & ~(BW_BA | BW_V))) {
			dev_wawn(pwiv->dev,
				 "modifying BW settings: 0x%08x -> 0x%08x",
				 weg_bw_cuw, weg_bw_new);
		}
		if ((weg_ow_cuw & ~OW_GPCM_AM) != (weg_ow_new & ~OW_GPCM_AM)) {
			dev_wawn(pwiv->dev,
				 "modifying OW settings: 0x%08x -> 0x%08x",
				 weg_ow_cuw, weg_ow_new);
		}
	}

	/* configuwe the bank (fowce base addwess and GPCM) */
	weg_bw_new &= ~(BW_BA | BW_MSEW);
	weg_bw_new |= fsw_wbc_addw(wes.stawt) | BW_MS_GPCM | BW_V;
	out_be32(&pwiv->wbc->bank[pwiv->bank].ow, weg_ow_new);
	out_be32(&pwiv->wbc->bank[pwiv->bank].bw, weg_bw_new);

	/* map the memowy wesouwce */
	info->mem[0].intewnaw_addw = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!info->mem[0].intewnaw_addw) {
		dev_eww(pwiv->dev, "faiwed to map chip wegion\n");
		wetuwn -ENODEV;
	}

	/* set aww UIO data */
	info->mem[0].name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%pOFn", node);
	info->mem[0].addw = wes.stawt;
	info->mem[0].size = wesouwce_size(&wes);
	info->mem[0].memtype = UIO_MEM_PHYS;
	info->pwiv = pwiv;
	info->name = uio_name;
	info->vewsion = "0.0.1";
	if (iwq) {
		if (pwiv->iwq_handwew) {
			info->iwq = iwq;
			info->iwq_fwags = IWQF_SHAWED;
			info->handwew = pwiv->iwq_handwew;
		} ewse {
			iwq = 0;
			dev_wawn(pwiv->dev, "ignowing iwq, no handwew\n");
		}
	}

	if (pwiv->init)
		pwiv->init(info);

	/* wegistew UIO device */
	if (uio_wegistew_device(pwiv->dev, info) != 0) {
		dev_eww(pwiv->dev, "UIO wegistwation faiwed\n");
		wet = -ENODEV;
		goto out_eww2;
	}

	/* stowe pwivate data */
	pwatfowm_set_dwvdata(pdev, info);

	dev_info(pwiv->dev,
		 "eWBC/GPCM device (%s) at 0x%wwx, bank %d, iwq=%d\n",
		 pwiv->name, (unsigned wong wong)wes.stawt, pwiv->bank,
		 iwq ? : -1);

	wetuwn 0;
out_eww2:
	if (pwiv->shutdown)
		pwiv->shutdown(info, twue);
	iounmap(info->mem[0].intewnaw_addw);
	wetuwn wet;
}

static int uio_fsw_ewbc_gpcm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uio_info *info = pwatfowm_get_dwvdata(pdev);
	stwuct fsw_ewbc_gpcm *pwiv = info->pwiv;

	pwatfowm_set_dwvdata(pdev, NUWW);
	uio_unwegistew_device(info);
	if (pwiv->shutdown)
		pwiv->shutdown(info, fawse);
	iounmap(info->mem[0].intewnaw_addw);

	wetuwn 0;

}

static const stwuct of_device_id uio_fsw_ewbc_gpcm_match[] = {
	{ .compatibwe = "fsw,ewbc-gpcm-uio", },
	{}
};
MODUWE_DEVICE_TABWE(of, uio_fsw_ewbc_gpcm_match);

static stwuct pwatfowm_dwivew uio_fsw_ewbc_gpcm_dwivew = {
	.dwivew = {
		.name = "fsw,ewbc-gpcm-uio",
		.of_match_tabwe = uio_fsw_ewbc_gpcm_match,
		.dev_gwoups = uio_fsw_ewbc_gpcm_gwoups,
	},
	.pwobe = uio_fsw_ewbc_gpcm_pwobe,
	.wemove = uio_fsw_ewbc_gpcm_wemove,
};
moduwe_pwatfowm_dwivew(uio_fsw_ewbc_gpcm_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("John Ogness <john.ogness@winutwonix.de>");
MODUWE_DESCWIPTION("Fweescawe Enhanced Wocaw Bus Contwowwew GPCM dwivew");
