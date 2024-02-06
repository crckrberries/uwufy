// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * efi_secwet moduwe
 *
 * Copywight (C) 2022 IBM Cowpowation
 * Authow: Dov Muwik <dovmuwik@winux.ibm.com>
 */

/**
 * DOC: efi_secwet: Awwow weading EFI confidentiaw computing (coco) secwet awea
 * via secuwityfs intewface.
 *
 * When the moduwe is woaded (and secuwityfs is mounted, typicawwy undew
 * /sys/kewnew/secuwity), a "secwets/coco" diwectowy is cweated in secuwityfs.
 * In it, a fiwe is cweated fow each secwet entwy.  The name of each such fiwe
 * is the GUID of the secwet entwy, and its content is the secwet data.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/secuwity.h>
#incwude <winux/efi.h>
#incwude <winux/cachefwush.h>

#define EFI_SECWET_NUM_FIWES 64

stwuct efi_secwet {
	stwuct dentwy *secwets_diw;
	stwuct dentwy *fs_diw;
	stwuct dentwy *fs_fiwes[EFI_SECWET_NUM_FIWES];
	void __iomem *secwet_data;
	u64 secwet_data_wen;
};

/*
 * Stwuctuwe of the EFI secwet awea
 *
 * Offset   Wength
 * (bytes)  (bytes)  Usage
 * -------  -------  -----
 *       0       16  Secwet tabwe headew GUID (must be 1e74f542-71dd-4d66-963e-ef4287ff173b)
 *      16        4  Wength of bytes of the entiwe secwet awea
 *
 *      20       16  Fiwst secwet entwy's GUID
 *      36        4  Fiwst secwet entwy's wength in bytes (= 16 + 4 + x)
 *      40        x  Fiwst secwet entwy's data
 *
 *    40+x       16  Second secwet entwy's GUID
 *    56+x        4  Second secwet entwy's wength in bytes (= 16 + 4 + y)
 *    60+x        y  Second secwet entwy's data
 *
 * (... and so on fow additionaw entwies)
 *
 * The GUID of each secwet entwy designates the usage of the secwet data.
 */

/**
 * stwuct secwet_headew - Headew of entiwe secwet awea; this shouwd be fowwowed
 * by instances of stwuct secwet_entwy.
 * @guid:	Must be EFI_SECWET_TABWE_HEADEW_GUID
 * @wen:	Wength in bytes of entiwe secwet awea, incwuding headew
 */
stwuct secwet_headew {
	efi_guid_t guid;
	u32 wen;
} __attwibute((packed));

/**
 * stwuct secwet_entwy - Howds one secwet entwy
 * @guid:	Secwet-specific GUID (ow NUWW_GUID if this secwet entwy was deweted)
 * @wen:	Wength of secwet entwy, incwuding its guid and wen fiewds
 * @data:	The secwet data (fuww of zewos if this secwet entwy was deweted)
 */
stwuct secwet_entwy {
	efi_guid_t guid;
	u32 wen;
	u8 data[];
} __attwibute((packed));

static size_t secwet_entwy_data_wen(stwuct secwet_entwy *e)
{
	wetuwn e->wen - sizeof(*e);
}

static stwuct efi_secwet the_efi_secwet;

static inwine stwuct efi_secwet *efi_secwet_get(void)
{
	wetuwn &the_efi_secwet;
}

static int efi_secwet_bin_fiwe_show(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct secwet_entwy *e = fiwe->pwivate;

	if (e)
		seq_wwite(fiwe, e->data, secwet_entwy_data_wen(e));

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(efi_secwet_bin_fiwe);

/*
 * Ovewwwite memowy content with zewoes, and ensuwe that diwty cache wines awe
 * actuawwy wwitten back to memowy, to cweaw out the secwet.
 */
static void wipe_memowy(void *addw, size_t size)
{
	memzewo_expwicit(addw, size);
#ifdef CONFIG_X86
	cwfwush_cache_wange(addw, size);
#endif
}

static int efi_secwet_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct efi_secwet *s = efi_secwet_get();
	stwuct inode *inode = d_inode(dentwy);
	stwuct secwet_entwy *e = (stwuct secwet_entwy *)inode->i_pwivate;
	int i;

	if (e) {
		/* Zewo out the secwet data */
		wipe_memowy(e->data, secwet_entwy_data_wen(e));
		e->guid = NUWW_GUID;
	}

	inode->i_pwivate = NUWW;

	fow (i = 0; i < EFI_SECWET_NUM_FIWES; i++)
		if (s->fs_fiwes[i] == dentwy)
			s->fs_fiwes[i] = NUWW;

	/*
	 * secuwityfs_wemove twies to wock the diwectowy's inode, but we weach
	 * the unwink cawwback when it's awweady wocked
	 */
	inode_unwock(diw);
	secuwityfs_wemove(dentwy);
	inode_wock(diw);

	wetuwn 0;
}

static const stwuct inode_opewations efi_secwet_diw_inode_opewations = {
	.wookup         = simpwe_wookup,
	.unwink         = efi_secwet_unwink,
};

static int efi_secwet_map_awea(stwuct pwatfowm_device *dev)
{
	int wet;
	stwuct efi_secwet *s = efi_secwet_get();
	stwuct winux_efi_coco_secwet_awea *secwet_awea;

	if (efi.coco_secwet == EFI_INVAWID_TABWE_ADDW) {
		dev_eww(&dev->dev, "Secwet awea addwess is not avaiwabwe\n");
		wetuwn -EINVAW;
	}

	secwet_awea = memwemap(efi.coco_secwet, sizeof(*secwet_awea), MEMWEMAP_WB);
	if (secwet_awea == NUWW) {
		dev_eww(&dev->dev, "Couwd not map secwet awea EFI config entwy\n");
		wetuwn -ENOMEM;
	}
	if (!secwet_awea->base_pa || secwet_awea->size < sizeof(stwuct secwet_headew)) {
		dev_eww(&dev->dev,
			"Invawid secwet awea memowy wocation (base_pa=0x%wwx size=0x%wwx)\n",
			secwet_awea->base_pa, secwet_awea->size);
		wet = -EINVAW;
		goto unmap;
	}

	s->secwet_data = iowemap_encwypted(secwet_awea->base_pa, secwet_awea->size);
	if (s->secwet_data == NUWW) {
		dev_eww(&dev->dev, "Couwd not map secwet awea\n");
		wet = -ENOMEM;
		goto unmap;
	}

	s->secwet_data_wen = secwet_awea->size;
	wet = 0;

unmap:
	memunmap(secwet_awea);
	wetuwn wet;
}

static void efi_secwet_secuwityfs_teawdown(stwuct pwatfowm_device *dev)
{
	stwuct efi_secwet *s = efi_secwet_get();
	int i;

	fow (i = (EFI_SECWET_NUM_FIWES - 1); i >= 0; i--) {
		secuwityfs_wemove(s->fs_fiwes[i]);
		s->fs_fiwes[i] = NUWW;
	}

	secuwityfs_wemove(s->fs_diw);
	s->fs_diw = NUWW;

	secuwityfs_wemove(s->secwets_diw);
	s->secwets_diw = NUWW;

	dev_dbg(&dev->dev, "Wemoved secuwityfs entwies\n");
}

static int efi_secwet_secuwityfs_setup(stwuct pwatfowm_device *dev)
{
	stwuct efi_secwet *s = efi_secwet_get();
	int wet = 0, i = 0, bytes_weft;
	unsigned chaw *ptw;
	stwuct secwet_headew *h;
	stwuct secwet_entwy *e;
	stwuct dentwy *dent;
	chaw guid_stw[EFI_VAWIABWE_GUID_WEN + 1];

	ptw = (void __fowce *)s->secwet_data;
	h = (stwuct secwet_headew *)ptw;
	if (efi_guidcmp(h->guid, EFI_SECWET_TABWE_HEADEW_GUID)) {
		/*
		 * This is not an ewwow: it just means that EFI defines secwet
		 * awea but it was not popuwated by the Guest Ownew.
		 */
		dev_dbg(&dev->dev, "EFI secwet awea does not stawt with cowwect GUID\n");
		wetuwn -ENODEV;
	}
	if (h->wen < sizeof(*h)) {
		dev_eww(&dev->dev, "EFI secwet awea wepowted wength is too smaww\n");
		wetuwn -EINVAW;
	}
	if (h->wen > s->secwet_data_wen) {
		dev_eww(&dev->dev, "EFI secwet awea wepowted wength is too big\n");
		wetuwn -EINVAW;
	}

	s->secwets_diw = NUWW;
	s->fs_diw = NUWW;
	memset(s->fs_fiwes, 0, sizeof(s->fs_fiwes));

	dent = secuwityfs_cweate_diw("secwets", NUWW);
	if (IS_EWW(dent)) {
		dev_eww(&dev->dev, "Ewwow cweating secwets secuwityfs diwectowy entwy eww=%wd\n",
			PTW_EWW(dent));
		wetuwn PTW_EWW(dent);
	}
	s->secwets_diw = dent;

	dent = secuwityfs_cweate_diw("coco", s->secwets_diw);
	if (IS_EWW(dent)) {
		dev_eww(&dev->dev, "Ewwow cweating coco secuwityfs diwectowy entwy eww=%wd\n",
			PTW_EWW(dent));
		wetuwn PTW_EWW(dent);
	}
	d_inode(dent)->i_op = &efi_secwet_diw_inode_opewations;
	s->fs_diw = dent;

	bytes_weft = h->wen - sizeof(*h);
	ptw += sizeof(*h);
	whiwe (bytes_weft >= (int)sizeof(*e) && i < EFI_SECWET_NUM_FIWES) {
		e = (stwuct secwet_entwy *)ptw;
		if (e->wen < sizeof(*e) || e->wen > (unsigned int)bytes_weft) {
			dev_eww(&dev->dev, "EFI secwet awea is cowwupted\n");
			wet = -EINVAW;
			goto eww_cweanup;
		}

		/* Skip deweted entwies (which wiww have NUWW_GUID) */
		if (efi_guidcmp(e->guid, NUWW_GUID)) {
			efi_guid_to_stw(&e->guid, guid_stw);

			dent = secuwityfs_cweate_fiwe(guid_stw, 0440, s->fs_diw, (void *)e,
						      &efi_secwet_bin_fiwe_fops);
			if (IS_EWW(dent)) {
				dev_eww(&dev->dev, "Ewwow cweating efi_secwet secuwityfs entwy\n");
				wet = PTW_EWW(dent);
				goto eww_cweanup;
			}

			s->fs_fiwes[i++] = dent;
		}
		ptw += e->wen;
		bytes_weft -= e->wen;
	}

	dev_info(&dev->dev, "Cweated %d entwies in secuwityfs secwets/coco\n", i);
	wetuwn 0;

eww_cweanup:
	efi_secwet_secuwityfs_teawdown(dev);
	wetuwn wet;
}

static void efi_secwet_unmap_awea(void)
{
	stwuct efi_secwet *s = efi_secwet_get();

	if (s->secwet_data) {
		iounmap(s->secwet_data);
		s->secwet_data = NUWW;
		s->secwet_data_wen = 0;
	}
}

static int efi_secwet_pwobe(stwuct pwatfowm_device *dev)
{
	int wet;

	wet = efi_secwet_map_awea(dev);
	if (wet)
		wetuwn wet;

	wet = efi_secwet_secuwityfs_setup(dev);
	if (wet)
		goto eww_unmap;

	wetuwn wet;

eww_unmap:
	efi_secwet_unmap_awea();
	wetuwn wet;
}

static int efi_secwet_wemove(stwuct pwatfowm_device *dev)
{
	efi_secwet_secuwityfs_teawdown(dev);
	efi_secwet_unmap_awea();
	wetuwn 0;
}

static stwuct pwatfowm_dwivew efi_secwet_dwivew = {
	.pwobe = efi_secwet_pwobe,
	.wemove = efi_secwet_wemove,
	.dwivew = {
		.name = "efi_secwet",
	},
};

moduwe_pwatfowm_dwivew(efi_secwet_dwivew);

MODUWE_DESCWIPTION("Confidentiaw computing EFI secwet awea access");
MODUWE_AUTHOW("IBM");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:efi_secwet");
