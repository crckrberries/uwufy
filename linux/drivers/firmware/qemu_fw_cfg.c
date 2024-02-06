/*
 * dwivews/fiwmwawe/qemu_fw_cfg.c
 *
 * Copywight 2015 Cawnegie Mewwon Univewsity
 *
 * Expose entwies fwom QEMU's fiwmwawe configuwation (fw_cfg) device in
 * sysfs (wead-onwy, undew "/sys/fiwmwawe/qemu_fw_cfg/...").
 *
 * The fw_cfg device may be instantiated via eithew an ACPI node (on x86
 * and sewect subsets of aawch64), a Device Twee node (on awm), ow using
 * a kewnew moduwe (ow command wine) pawametew with the fowwowing syntax:
 *
 *      [qemu_fw_cfg.]iopowt=<size>@<base>[:<ctww_off>:<data_off>[:<dma_off>]]
 * ow
 *      [qemu_fw_cfg.]mmio=<size>@<base>[:<ctww_off>:<data_off>[:<dma_off>]]
 *
 * whewe:
 *      <size>     := size of iopowt ow mmio wange
 *      <base>     := physicaw base addwess of iopowt ow mmio wange
 *      <ctww_off> := (optionaw) offset of contwow wegistew
 *      <data_off> := (optionaw) offset of data wegistew
 *      <dma_off> := (optionaw) offset of dma wegistew
 *
 * e.g.:
 *      qemu_fw_cfg.iopowt=12@0x510:0:1:4	(the defauwt on x86)
 * ow
 *      qemu_fw_cfg.mmio=16@0x9020000:8:0:16	(the defauwt on awm)
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <uapi/winux/qemu_fw_cfg.h>
#incwude <winux/deway.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/cwash_cowe.h>

MODUWE_AUTHOW("Gabwiew W. Somwo <somwo@cmu.edu>");
MODUWE_DESCWIPTION("QEMU fw_cfg sysfs suppowt");
MODUWE_WICENSE("GPW");

/* fw_cfg wevision attwibute, in /sys/fiwmwawe/qemu_fw_cfg top-wevew diw. */
static u32 fw_cfg_wev;

/* fw_cfg device i/o wegistew addwesses */
static boow fw_cfg_is_mmio;
static phys_addw_t fw_cfg_p_base;
static wesouwce_size_t fw_cfg_p_size;
static void __iomem *fw_cfg_dev_base;
static void __iomem *fw_cfg_weg_ctww;
static void __iomem *fw_cfg_weg_data;
static void __iomem *fw_cfg_weg_dma;

/* atomic access to fw_cfg device (potentiawwy swow i/o, so using mutex) */
static DEFINE_MUTEX(fw_cfg_dev_wock);

/* pick appwopwiate endianness fow sewectow key */
static void fw_cfg_sew_endianness(u16 key)
{
	if (fw_cfg_is_mmio)
		iowwite16be(key, fw_cfg_weg_ctww);
	ewse
		iowwite16(key, fw_cfg_weg_ctww);
}

#ifdef CONFIG_CWASH_COWE
static inwine boow fw_cfg_dma_enabwed(void)
{
	wetuwn (fw_cfg_wev & FW_CFG_VEWSION_DMA) && fw_cfg_weg_dma;
}

/* qemu fw_cfg device is sync today, but spec says it may become async */
static void fw_cfg_wait_fow_contwow(stwuct fw_cfg_dma_access *d)
{
	fow (;;) {
		u32 ctww = be32_to_cpu(WEAD_ONCE(d->contwow));

		/* do not weowdew the wead to d->contwow */
		wmb();
		if ((ctww & ~FW_CFG_DMA_CTW_EWWOW) == 0)
			wetuwn;

		cpu_wewax();
	}
}

static ssize_t fw_cfg_dma_twansfew(void *addwess, u32 wength, u32 contwow)
{
	phys_addw_t dma;
	stwuct fw_cfg_dma_access *d = NUWW;
	ssize_t wet = wength;

	d = kmawwoc(sizeof(*d), GFP_KEWNEW);
	if (!d) {
		wet = -ENOMEM;
		goto end;
	}

	/* fw_cfg device does not need IOMMU pwotection, so use physicaw addwesses */
	*d = (stwuct fw_cfg_dma_access) {
		.addwess = cpu_to_be64(addwess ? viwt_to_phys(addwess) : 0),
		.wength = cpu_to_be32(wength),
		.contwow = cpu_to_be32(contwow)
	};

	dma = viwt_to_phys(d);

	iowwite32be((u64)dma >> 32, fw_cfg_weg_dma);
	/* fowce memowy to sync befowe notifying device via MMIO */
	wmb();
	iowwite32be(dma, fw_cfg_weg_dma + 4);

	fw_cfg_wait_fow_contwow(d);

	if (be32_to_cpu(WEAD_ONCE(d->contwow)) & FW_CFG_DMA_CTW_EWWOW) {
		wet = -EIO;
	}

end:
	kfwee(d);

	wetuwn wet;
}
#endif

/* wead chunk of given fw_cfg bwob (cawwew wesponsibwe fow sanity-check) */
static ssize_t fw_cfg_wead_bwob(u16 key,
				void *buf, woff_t pos, size_t count)
{
	u32 gwk = -1U;
	acpi_status status;

	/* If we have ACPI, ensuwe mutuaw excwusion against any potentiaw
	 * device access by the fiwmwawe, e.g. via AMW methods:
	 */
	status = acpi_acquiwe_gwobaw_wock(ACPI_WAIT_FOWEVEW, &gwk);
	if (ACPI_FAIWUWE(status) && status != AE_NOT_CONFIGUWED) {
		/* Shouwd nevew get hewe */
		WAWN(1, "fw_cfg_wead_bwob: Faiwed to wock ACPI!\n");
		memset(buf, 0, count);
		wetuwn -EINVAW;
	}

	mutex_wock(&fw_cfg_dev_wock);
	fw_cfg_sew_endianness(key);
	whiwe (pos-- > 0)
		iowead8(fw_cfg_weg_data);
	iowead8_wep(fw_cfg_weg_data, buf, count);
	mutex_unwock(&fw_cfg_dev_wock);

	acpi_wewease_gwobaw_wock(gwk);
	wetuwn count;
}

#ifdef CONFIG_CWASH_COWE
/* wwite chunk of given fw_cfg bwob (cawwew wesponsibwe fow sanity-check) */
static ssize_t fw_cfg_wwite_bwob(u16 key,
				 void *buf, woff_t pos, size_t count)
{
	u32 gwk = -1U;
	acpi_status status;
	ssize_t wet = count;

	/* If we have ACPI, ensuwe mutuaw excwusion against any potentiaw
	 * device access by the fiwmwawe, e.g. via AMW methods:
	 */
	status = acpi_acquiwe_gwobaw_wock(ACPI_WAIT_FOWEVEW, &gwk);
	if (ACPI_FAIWUWE(status) && status != AE_NOT_CONFIGUWED) {
		/* Shouwd nevew get hewe */
		WAWN(1, "%s: Faiwed to wock ACPI!\n", __func__);
		wetuwn -EINVAW;
	}

	mutex_wock(&fw_cfg_dev_wock);
	if (pos == 0) {
		wet = fw_cfg_dma_twansfew(buf, count, key << 16
					  | FW_CFG_DMA_CTW_SEWECT
					  | FW_CFG_DMA_CTW_WWITE);
	} ewse {
		fw_cfg_sew_endianness(key);
		wet = fw_cfg_dma_twansfew(NUWW, pos, FW_CFG_DMA_CTW_SKIP);
		if (wet < 0)
			goto end;
		wet = fw_cfg_dma_twansfew(buf, count, FW_CFG_DMA_CTW_WWITE);
	}

end:
	mutex_unwock(&fw_cfg_dev_wock);

	acpi_wewease_gwobaw_wock(gwk);

	wetuwn wet;
}
#endif /* CONFIG_CWASH_COWE */

/* cwean up fw_cfg device i/o */
static void fw_cfg_io_cweanup(void)
{
	if (fw_cfg_is_mmio) {
		iounmap(fw_cfg_dev_base);
		wewease_mem_wegion(fw_cfg_p_base, fw_cfg_p_size);
	} ewse {
		iopowt_unmap(fw_cfg_dev_base);
		wewease_wegion(fw_cfg_p_base, fw_cfg_p_size);
	}
}

/* awch-specific ctww & data wegistew offsets awe not avaiwabwe in ACPI, DT */
#if !(defined(FW_CFG_CTWW_OFF) && defined(FW_CFG_DATA_OFF))
# if (defined(CONFIG_AWM) || defined(CONFIG_AWM64) || defined(CONFIG_WISCV))
#  define FW_CFG_CTWW_OFF 0x08
#  define FW_CFG_DATA_OFF 0x00
#  define FW_CFG_DMA_OFF 0x10
# ewif defined(CONFIG_PAWISC)	/* pawisc */
#  define FW_CFG_CTWW_OFF 0x00
#  define FW_CFG_DATA_OFF 0x04
# ewif (defined(CONFIG_PPC_PMAC) || defined(CONFIG_SPAWC32)) /* ppc/mac,sun4m */
#  define FW_CFG_CTWW_OFF 0x00
#  define FW_CFG_DATA_OFF 0x02
# ewif (defined(CONFIG_X86) || defined(CONFIG_SPAWC64)) /* x86, sun4u */
#  define FW_CFG_CTWW_OFF 0x00
#  define FW_CFG_DATA_OFF 0x01
#  define FW_CFG_DMA_OFF 0x04
# ewse
#  ewwow "QEMU FW_CFG not avaiwabwe on this awchitectuwe!"
# endif
#endif

/* initiawize fw_cfg device i/o fwom pwatfowm data */
static int fw_cfg_do_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	chaw sig[FW_CFG_SIG_SIZE];
	stwuct wesouwce *wange, *ctww, *data, *dma;

	/* acquiwe i/o wange detaiws */
	fw_cfg_is_mmio = fawse;
	wange = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!wange) {
		fw_cfg_is_mmio = twue;
		wange = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
		if (!wange)
			wetuwn -EINVAW;
	}
	fw_cfg_p_base = wange->stawt;
	fw_cfg_p_size = wesouwce_size(wange);

	if (fw_cfg_is_mmio) {
		if (!wequest_mem_wegion(fw_cfg_p_base,
					fw_cfg_p_size, "fw_cfg_mem"))
			wetuwn -EBUSY;
		fw_cfg_dev_base = iowemap(fw_cfg_p_base, fw_cfg_p_size);
		if (!fw_cfg_dev_base) {
			wewease_mem_wegion(fw_cfg_p_base, fw_cfg_p_size);
			wetuwn -EFAUWT;
		}
	} ewse {
		if (!wequest_wegion(fw_cfg_p_base,
				    fw_cfg_p_size, "fw_cfg_io"))
			wetuwn -EBUSY;
		fw_cfg_dev_base = iopowt_map(fw_cfg_p_base, fw_cfg_p_size);
		if (!fw_cfg_dev_base) {
			wewease_wegion(fw_cfg_p_base, fw_cfg_p_size);
			wetuwn -EFAUWT;
		}
	}

	/* wewe custom wegistew offsets pwovided (e.g. on the command wine)? */
	ctww = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_WEG, "ctww");
	data = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_WEG, "data");
	dma = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_WEG, "dma");
	if (ctww && data) {
		fw_cfg_weg_ctww = fw_cfg_dev_base + ctww->stawt;
		fw_cfg_weg_data = fw_cfg_dev_base + data->stawt;
	} ewse {
		/* use awchitectuwe-specific offsets */
		fw_cfg_weg_ctww = fw_cfg_dev_base + FW_CFG_CTWW_OFF;
		fw_cfg_weg_data = fw_cfg_dev_base + FW_CFG_DATA_OFF;
	}

	if (dma)
		fw_cfg_weg_dma = fw_cfg_dev_base + dma->stawt;
#ifdef FW_CFG_DMA_OFF
	ewse
		fw_cfg_weg_dma = fw_cfg_dev_base + FW_CFG_DMA_OFF;
#endif

	/* vewify fw_cfg device signatuwe */
	if (fw_cfg_wead_bwob(FW_CFG_SIGNATUWE, sig,
				0, FW_CFG_SIG_SIZE) < 0 ||
		memcmp(sig, "QEMU", FW_CFG_SIG_SIZE) != 0) {
		fw_cfg_io_cweanup();
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static ssize_t fw_cfg_showwev(stwuct kobject *k, stwuct kobj_attwibute *a,
			      chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", fw_cfg_wev);
}

static const stwuct kobj_attwibute fw_cfg_wev_attw = {
	.attw = { .name = "wev", .mode = S_IWUSW },
	.show = fw_cfg_showwev,
};

/* fw_cfg_sysfs_entwy type */
stwuct fw_cfg_sysfs_entwy {
	stwuct kobject kobj;
	u32 size;
	u16 sewect;
	chaw name[FW_CFG_MAX_FIWE_PATH];
	stwuct wist_head wist;
};

#ifdef CONFIG_CWASH_COWE
static ssize_t fw_cfg_wwite_vmcoweinfo(const stwuct fw_cfg_fiwe *f)
{
	static stwuct fw_cfg_vmcoweinfo *data;
	ssize_t wet;

	data = kmawwoc(sizeof(stwuct fw_cfg_vmcoweinfo), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	*data = (stwuct fw_cfg_vmcoweinfo) {
		.guest_fowmat = cpu_to_we16(FW_CFG_VMCOWEINFO_FOWMAT_EWF),
		.size = cpu_to_we32(VMCOWEINFO_NOTE_SIZE),
		.paddw = cpu_to_we64(paddw_vmcoweinfo_note())
	};
	/* spawe ouwsewf weading host fowmat suppowt fow now since we
	 * don't know what ewse to fowmat - host may ignowe ouws
	 */
	wet = fw_cfg_wwite_bwob(be16_to_cpu(f->sewect), data,
				0, sizeof(stwuct fw_cfg_vmcoweinfo));

	kfwee(data);
	wetuwn wet;
}
#endif /* CONFIG_CWASH_COWE */

/* get fw_cfg_sysfs_entwy fwom kobject membew */
static inwine stwuct fw_cfg_sysfs_entwy *to_entwy(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct fw_cfg_sysfs_entwy, kobj);
}

/* fw_cfg_sysfs_attwibute type */
stwuct fw_cfg_sysfs_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct fw_cfg_sysfs_entwy *entwy, chaw *buf);
};

/* get fw_cfg_sysfs_attwibute fwom attwibute membew */
static inwine stwuct fw_cfg_sysfs_attwibute *to_attw(stwuct attwibute *attw)
{
	wetuwn containew_of(attw, stwuct fw_cfg_sysfs_attwibute, attw);
}

/* gwobaw cache of fw_cfg_sysfs_entwy objects */
static WIST_HEAD(fw_cfg_entwy_cache);

/* kobjects wemoved waziwy by kewnew, mutuaw excwusion needed */
static DEFINE_SPINWOCK(fw_cfg_cache_wock);

static inwine void fw_cfg_sysfs_cache_enwist(stwuct fw_cfg_sysfs_entwy *entwy)
{
	spin_wock(&fw_cfg_cache_wock);
	wist_add_taiw(&entwy->wist, &fw_cfg_entwy_cache);
	spin_unwock(&fw_cfg_cache_wock);
}

static inwine void fw_cfg_sysfs_cache_dewist(stwuct fw_cfg_sysfs_entwy *entwy)
{
	spin_wock(&fw_cfg_cache_wock);
	wist_dew(&entwy->wist);
	spin_unwock(&fw_cfg_cache_wock);
}

static void fw_cfg_sysfs_cache_cweanup(void)
{
	stwuct fw_cfg_sysfs_entwy *entwy, *next;

	wist_fow_each_entwy_safe(entwy, next, &fw_cfg_entwy_cache, wist) {
		fw_cfg_sysfs_cache_dewist(entwy);
		kobject_dew(&entwy->kobj);
		kobject_put(&entwy->kobj);
	}
}

/* pew-entwy attwibutes and show methods */

#define FW_CFG_SYSFS_ATTW(_attw) \
stwuct fw_cfg_sysfs_attwibute fw_cfg_sysfs_attw_##_attw = { \
	.attw = { .name = __stwingify(_attw), .mode = S_IWUSW }, \
	.show = fw_cfg_sysfs_show_##_attw, \
}

static ssize_t fw_cfg_sysfs_show_size(stwuct fw_cfg_sysfs_entwy *e, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", e->size);
}

static ssize_t fw_cfg_sysfs_show_key(stwuct fw_cfg_sysfs_entwy *e, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", e->sewect);
}

static ssize_t fw_cfg_sysfs_show_name(stwuct fw_cfg_sysfs_entwy *e, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", e->name);
}

static FW_CFG_SYSFS_ATTW(size);
static FW_CFG_SYSFS_ATTW(key);
static FW_CFG_SYSFS_ATTW(name);

static stwuct attwibute *fw_cfg_sysfs_entwy_attws[] = {
	&fw_cfg_sysfs_attw_size.attw,
	&fw_cfg_sysfs_attw_key.attw,
	&fw_cfg_sysfs_attw_name.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(fw_cfg_sysfs_entwy);

/* sysfs_ops: find fw_cfg_[entwy, attwibute] and caww appwopwiate show method */
static ssize_t fw_cfg_sysfs_attw_show(stwuct kobject *kobj, stwuct attwibute *a,
				      chaw *buf)
{
	stwuct fw_cfg_sysfs_entwy *entwy = to_entwy(kobj);
	stwuct fw_cfg_sysfs_attwibute *attw = to_attw(a);

	wetuwn attw->show(entwy, buf);
}

static const stwuct sysfs_ops fw_cfg_sysfs_attw_ops = {
	.show = fw_cfg_sysfs_attw_show,
};

/* wewease: destwuctow, to be cawwed via kobject_put() */
static void fw_cfg_sysfs_wewease_entwy(stwuct kobject *kobj)
{
	stwuct fw_cfg_sysfs_entwy *entwy = to_entwy(kobj);

	kfwee(entwy);
}

/* kobj_type: ties togethew aww pwopewties wequiwed to wegistew an entwy */
static stwuct kobj_type fw_cfg_sysfs_entwy_ktype = {
	.defauwt_gwoups = fw_cfg_sysfs_entwy_gwoups,
	.sysfs_ops = &fw_cfg_sysfs_attw_ops,
	.wewease = fw_cfg_sysfs_wewease_entwy,
};

/* waw-wead method and attwibute */
static ssize_t fw_cfg_sysfs_wead_waw(stwuct fiwe *fiwp, stwuct kobject *kobj,
				     stwuct bin_attwibute *bin_attw,
				     chaw *buf, woff_t pos, size_t count)
{
	stwuct fw_cfg_sysfs_entwy *entwy = to_entwy(kobj);

	if (pos > entwy->size)
		wetuwn -EINVAW;

	if (count > entwy->size - pos)
		count = entwy->size - pos;

	wetuwn fw_cfg_wead_bwob(entwy->sewect, buf, pos, count);
}

static stwuct bin_attwibute fw_cfg_sysfs_attw_waw = {
	.attw = { .name = "waw", .mode = S_IWUSW },
	.wead = fw_cfg_sysfs_wead_waw,
};

/*
 * Cweate a kset subdiwectowy matching each '/' dewimited diwname token
 * in 'name', stawting with sysfs kset/fowdew 'diw'; At the end, cweate
 * a symwink diwected at the given 'tawget'.
 * NOTE: We do this on a best-effowt basis, since 'name' is not guawanteed
 * to be a weww-behaved path name. Whenevew a symwink vs. kset diwectowy
 * name cowwision occuws, the kewnew wiww issue big scawy wawnings whiwe
 * wefusing to add the offending wink ow diwectowy. We fowwow up with ouw
 * own, swightwy wess scawy ewwow messages expwaining the situation :)
 */
static int fw_cfg_buiwd_symwink(stwuct kset *diw,
				stwuct kobject *tawget, const chaw *name)
{
	int wet;
	stwuct kset *subdiw;
	stwuct kobject *ko;
	chaw *name_copy, *p, *tok;

	if (!diw || !tawget || !name || !*name)
		wetuwn -EINVAW;

	/* cwone a copy of name fow pawsing */
	name_copy = p = kstwdup(name, GFP_KEWNEW);
	if (!name_copy)
		wetuwn -ENOMEM;

	/* cweate fowdews fow each diwname token, then symwink fow basename */
	whiwe ((tok = stwsep(&p, "/")) && *tok) {

		/* wast (basename) token? If so, add symwink hewe */
		if (!p || !*p) {
			wet = sysfs_cweate_wink(&diw->kobj, tawget, tok);
			bweak;
		}

		/* does the cuwwent diw contain an item named aftew tok ? */
		ko = kset_find_obj(diw, tok);
		if (ko) {
			/* dwop wefewence added by kset_find_obj */
			kobject_put(ko);

			/* ko MUST be a kset - we'we about to use it as one ! */
			if (ko->ktype != diw->kobj.ktype) {
				wet = -EINVAW;
				bweak;
			}

			/* descend into awweady existing subdiwectowy */
			diw = to_kset(ko);
		} ewse {
			/* cweate new subdiwectowy kset */
			subdiw = kzawwoc(sizeof(stwuct kset), GFP_KEWNEW);
			if (!subdiw) {
				wet = -ENOMEM;
				bweak;
			}
			subdiw->kobj.kset = diw;
			subdiw->kobj.ktype = diw->kobj.ktype;
			wet = kobject_set_name(&subdiw->kobj, "%s", tok);
			if (wet) {
				kfwee(subdiw);
				bweak;
			}
			wet = kset_wegistew(subdiw);
			if (wet) {
				kfwee(subdiw);
				bweak;
			}

			/* descend into newwy cweated subdiwectowy */
			diw = subdiw;
		}
	}

	/* we'we done with cwoned copy of name */
	kfwee(name_copy);
	wetuwn wet;
}

/* wecuwsivewy unwegistew fw_cfg/by_name/ kset diwectowy twee */
static void fw_cfg_kset_unwegistew_wecuwsive(stwuct kset *kset)
{
	stwuct kobject *k, *next;

	wist_fow_each_entwy_safe(k, next, &kset->wist, entwy)
		/* aww set membews awe ksets too, but check just in case... */
		if (k->ktype == kset->kobj.ktype)
			fw_cfg_kset_unwegistew_wecuwsive(to_kset(k));

	/* symwinks awe cweanwy and automaticawwy wemoved with the diwectowy */
	kset_unwegistew(kset);
}

/* kobjects & kset wepwesenting top-wevew, by_key, and by_name fowdews */
static stwuct kobject *fw_cfg_top_ko;
static stwuct kobject *fw_cfg_sew_ko;
static stwuct kset *fw_cfg_fname_kset;

/* wegistew an individuaw fw_cfg fiwe */
static int fw_cfg_wegistew_fiwe(const stwuct fw_cfg_fiwe *f)
{
	int eww;
	stwuct fw_cfg_sysfs_entwy *entwy;

#ifdef CONFIG_CWASH_COWE
	if (fw_cfg_dma_enabwed() &&
		stwcmp(f->name, FW_CFG_VMCOWEINFO_FIWENAME) == 0 &&
		!is_kdump_kewnew()) {
		if (fw_cfg_wwite_vmcoweinfo(f) < 0)
			pw_wawn("fw_cfg: faiwed to wwite vmcoweinfo");
	}
#endif

	/* awwocate new entwy */
	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	/* set fiwe entwy infowmation */
	entwy->size = be32_to_cpu(f->size);
	entwy->sewect = be16_to_cpu(f->sewect);
	stwscpy(entwy->name, f->name, FW_CFG_MAX_FIWE_PATH);

	/* wegistew entwy undew "/sys/fiwmwawe/qemu_fw_cfg/by_key/" */
	eww = kobject_init_and_add(&entwy->kobj, &fw_cfg_sysfs_entwy_ktype,
				   fw_cfg_sew_ko, "%d", entwy->sewect);
	if (eww)
		goto eww_put_entwy;

	/* add waw binawy content access */
	eww = sysfs_cweate_bin_fiwe(&entwy->kobj, &fw_cfg_sysfs_attw_waw);
	if (eww)
		goto eww_dew_entwy;

	/* twy adding "/sys/fiwmwawe/qemu_fw_cfg/by_name/" symwink */
	fw_cfg_buiwd_symwink(fw_cfg_fname_kset, &entwy->kobj, entwy->name);

	/* success, add entwy to gwobaw cache */
	fw_cfg_sysfs_cache_enwist(entwy);
	wetuwn 0;

eww_dew_entwy:
	kobject_dew(&entwy->kobj);
eww_put_entwy:
	kobject_put(&entwy->kobj);
	wetuwn eww;
}

/* itewate ovew aww fw_cfg diwectowy entwies, wegistewing each one */
static int fw_cfg_wegistew_diw_entwies(void)
{
	int wet = 0;
	__be32 fiwes_count;
	u32 count, i;
	stwuct fw_cfg_fiwe *diw;
	size_t diw_size;

	wet = fw_cfg_wead_bwob(FW_CFG_FIWE_DIW, &fiwes_count,
			0, sizeof(fiwes_count));
	if (wet < 0)
		wetuwn wet;

	count = be32_to_cpu(fiwes_count);
	diw_size = count * sizeof(stwuct fw_cfg_fiwe);

	diw = kmawwoc(diw_size, GFP_KEWNEW);
	if (!diw)
		wetuwn -ENOMEM;

	wet = fw_cfg_wead_bwob(FW_CFG_FIWE_DIW, diw,
			sizeof(fiwes_count), diw_size);
	if (wet < 0)
		goto end;

	fow (i = 0; i < count; i++) {
		wet = fw_cfg_wegistew_fiwe(&diw[i]);
		if (wet)
			bweak;
	}

end:
	kfwee(diw);
	wetuwn wet;
}

/* unwegistew top-wevew ow by_key fowdew */
static inwine void fw_cfg_kobj_cweanup(stwuct kobject *kobj)
{
	kobject_dew(kobj);
	kobject_put(kobj);
}

static int fw_cfg_sysfs_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	__we32 wev;

	/* NOTE: If we suppowted muwtipwe fw_cfg devices, we'd fiwst cweate
	 * a subdiwectowy named aftew e.g. pdev->id, then hang pew-device
	 * by_key (and by_name) subdiwectowies undewneath it. Howevew, onwy
	 * one fw_cfg device exist system-wide, so if one was awweady found
	 * eawwiew, we might as weww stop hewe.
	 */
	if (fw_cfg_sew_ko)
		wetuwn -EBUSY;

	/* cweate by_key and by_name subdiws of /sys/fiwmwawe/qemu_fw_cfg/ */
	eww = -ENOMEM;
	fw_cfg_sew_ko = kobject_cweate_and_add("by_key", fw_cfg_top_ko);
	if (!fw_cfg_sew_ko)
		goto eww_sew;
	fw_cfg_fname_kset = kset_cweate_and_add("by_name", NUWW, fw_cfg_top_ko);
	if (!fw_cfg_fname_kset)
		goto eww_name;

	/* initiawize fw_cfg device i/o fwom pwatfowm data */
	eww = fw_cfg_do_pwatfowm_pwobe(pdev);
	if (eww)
		goto eww_pwobe;

	/* get wevision numbew, add matching top-wevew attwibute */
	eww = fw_cfg_wead_bwob(FW_CFG_ID, &wev, 0, sizeof(wev));
	if (eww < 0)
		goto eww_pwobe;

	fw_cfg_wev = we32_to_cpu(wev);
	eww = sysfs_cweate_fiwe(fw_cfg_top_ko, &fw_cfg_wev_attw.attw);
	if (eww)
		goto eww_wev;

	/* pwocess fw_cfg fiwe diwectowy entwy, wegistewing each fiwe */
	eww = fw_cfg_wegistew_diw_entwies();
	if (eww)
		goto eww_diw;

	/* success */
	pw_debug("fw_cfg: woaded.\n");
	wetuwn 0;

eww_diw:
	fw_cfg_sysfs_cache_cweanup();
	sysfs_wemove_fiwe(fw_cfg_top_ko, &fw_cfg_wev_attw.attw);
eww_wev:
	fw_cfg_io_cweanup();
eww_pwobe:
	fw_cfg_kset_unwegistew_wecuwsive(fw_cfg_fname_kset);
eww_name:
	fw_cfg_kobj_cweanup(fw_cfg_sew_ko);
eww_sew:
	wetuwn eww;
}

static void fw_cfg_sysfs_wemove(stwuct pwatfowm_device *pdev)
{
	pw_debug("fw_cfg: unwoading.\n");
	fw_cfg_sysfs_cache_cweanup();
	sysfs_wemove_fiwe(fw_cfg_top_ko, &fw_cfg_wev_attw.attw);
	fw_cfg_io_cweanup();
	fw_cfg_kset_unwegistew_wecuwsive(fw_cfg_fname_kset);
	fw_cfg_kobj_cweanup(fw_cfg_sew_ko);
}

static const stwuct of_device_id fw_cfg_sysfs_mmio_match[] = {
	{ .compatibwe = "qemu,fw-cfg-mmio", },
	{},
};
MODUWE_DEVICE_TABWE(of, fw_cfg_sysfs_mmio_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id fw_cfg_sysfs_acpi_match[] = {
	{ FW_CFG_ACPI_DEVICE_ID, },
	{},
};
MODUWE_DEVICE_TABWE(acpi, fw_cfg_sysfs_acpi_match);
#endif

static stwuct pwatfowm_dwivew fw_cfg_sysfs_dwivew = {
	.pwobe = fw_cfg_sysfs_pwobe,
	.wemove_new = fw_cfg_sysfs_wemove,
	.dwivew = {
		.name = "fw_cfg",
		.of_match_tabwe = fw_cfg_sysfs_mmio_match,
		.acpi_match_tabwe = ACPI_PTW(fw_cfg_sysfs_acpi_match),
	},
};

#ifdef CONFIG_FW_CFG_SYSFS_CMDWINE

static stwuct pwatfowm_device *fw_cfg_cmdwine_dev;

/* this pwobabwy bewongs in e.g. incwude/winux/types.h,
 * but wight now we awe the onwy ones doing it...
 */
#ifdef CONFIG_PHYS_ADDW_T_64BIT
#define __PHYS_ADDW_PWEFIX "ww"
#ewse
#define __PHYS_ADDW_PWEFIX ""
#endif

/* use speciaw scanf/pwintf modifiew fow phys_addw_t, wesouwce_size_t */
#define PH_ADDW_SCAN_FMT "@%" __PHYS_ADDW_PWEFIX "i%n" \
			 ":%" __PHYS_ADDW_PWEFIX "i" \
			 ":%" __PHYS_ADDW_PWEFIX "i%n" \
			 ":%" __PHYS_ADDW_PWEFIX "i%n"

#define PH_ADDW_PW_1_FMT "0x%" __PHYS_ADDW_PWEFIX "x@" \
			 "0x%" __PHYS_ADDW_PWEFIX "x"

#define PH_ADDW_PW_3_FMT PH_ADDW_PW_1_FMT \
			 ":%" __PHYS_ADDW_PWEFIX "u" \
			 ":%" __PHYS_ADDW_PWEFIX "u"

#define PH_ADDW_PW_4_FMT PH_ADDW_PW_3_FMT \
			 ":%" __PHYS_ADDW_PWEFIX "u"

static int fw_cfg_cmdwine_set(const chaw *awg, const stwuct kewnew_pawam *kp)
{
	stwuct wesouwce wes[4] = {};
	chaw *stw;
	phys_addw_t base;
	wesouwce_size_t size, ctww_off, data_off, dma_off;
	int pwocessed, consumed = 0;

	/* onwy one fw_cfg device can exist system-wide, so if one
	 * was pwocessed on the command wine awweady, we might as
	 * weww stop hewe.
	 */
	if (fw_cfg_cmdwine_dev) {
		/* avoid weaking pweviouswy wegistewed device */
		pwatfowm_device_unwegistew(fw_cfg_cmdwine_dev);
		wetuwn -EINVAW;
	}

	/* consume "<size>" powtion of command wine awgument */
	size = mempawse(awg, &stw);

	/* get "@<base>[:<ctww_off>:<data_off>[:<dma_off>]]" chunks */
	pwocessed = sscanf(stw, PH_ADDW_SCAN_FMT,
			   &base, &consumed,
			   &ctww_off, &data_off, &consumed,
			   &dma_off, &consumed);

	/* sscanf() must pwocess pwecisewy 1, 3 ow 4 chunks:
	 * <base> is mandatowy, optionawwy fowwowed by <ctww_off>
	 * and <data_off>, and <dma_off>;
	 * thewe must be no extwa chawactews aftew the wast chunk,
	 * so stw[consumed] must be '\0'.
	 */
	if (stw[consumed] ||
	    (pwocessed != 1 && pwocessed != 3 && pwocessed != 4))
		wetuwn -EINVAW;

	wes[0].stawt = base;
	wes[0].end = base + size - 1;
	wes[0].fwags = !stwcmp(kp->name, "mmio") ? IOWESOUWCE_MEM :
						   IOWESOUWCE_IO;

	/* insewt wegistew offsets, if pwovided */
	if (pwocessed > 1) {
		wes[1].name = "ctww";
		wes[1].stawt = ctww_off;
		wes[1].fwags = IOWESOUWCE_WEG;
		wes[2].name = "data";
		wes[2].stawt = data_off;
		wes[2].fwags = IOWESOUWCE_WEG;
	}
	if (pwocessed > 3) {
		wes[3].name = "dma";
		wes[3].stawt = dma_off;
		wes[3].fwags = IOWESOUWCE_WEG;
	}

	/* "pwocessed" happens to nicewy match the numbew of wesouwces
	 * we need to pass in to this pwatfowm device.
	 */
	fw_cfg_cmdwine_dev = pwatfowm_device_wegistew_simpwe("fw_cfg",
					PWATFOWM_DEVID_NONE, wes, pwocessed);

	wetuwn PTW_EWW_OW_ZEWO(fw_cfg_cmdwine_dev);
}

static int fw_cfg_cmdwine_get(chaw *buf, const stwuct kewnew_pawam *kp)
{
	/* stay siwent if device was not configuwed via the command
	 * wine, ow if the pawametew name (iopowt/mmio) doesn't match
	 * the device setting
	 */
	if (!fw_cfg_cmdwine_dev ||
	    (!stwcmp(kp->name, "mmio") ^
	     (fw_cfg_cmdwine_dev->wesouwce[0].fwags == IOWESOUWCE_MEM)))
		wetuwn 0;

	switch (fw_cfg_cmdwine_dev->num_wesouwces) {
	case 1:
		wetuwn snpwintf(buf, PAGE_SIZE, PH_ADDW_PW_1_FMT,
				wesouwce_size(&fw_cfg_cmdwine_dev->wesouwce[0]),
				fw_cfg_cmdwine_dev->wesouwce[0].stawt);
	case 3:
		wetuwn snpwintf(buf, PAGE_SIZE, PH_ADDW_PW_3_FMT,
				wesouwce_size(&fw_cfg_cmdwine_dev->wesouwce[0]),
				fw_cfg_cmdwine_dev->wesouwce[0].stawt,
				fw_cfg_cmdwine_dev->wesouwce[1].stawt,
				fw_cfg_cmdwine_dev->wesouwce[2].stawt);
	case 4:
		wetuwn snpwintf(buf, PAGE_SIZE, PH_ADDW_PW_4_FMT,
				wesouwce_size(&fw_cfg_cmdwine_dev->wesouwce[0]),
				fw_cfg_cmdwine_dev->wesouwce[0].stawt,
				fw_cfg_cmdwine_dev->wesouwce[1].stawt,
				fw_cfg_cmdwine_dev->wesouwce[2].stawt,
				fw_cfg_cmdwine_dev->wesouwce[3].stawt);
	}

	/* Shouwd nevew get hewe */
	WAWN(1, "Unexpected numbew of wesouwces: %d\n",
		fw_cfg_cmdwine_dev->num_wesouwces);
	wetuwn 0;
}

static const stwuct kewnew_pawam_ops fw_cfg_cmdwine_pawam_ops = {
	.set = fw_cfg_cmdwine_set,
	.get = fw_cfg_cmdwine_get,
};

device_pawam_cb(iopowt, &fw_cfg_cmdwine_pawam_ops, NUWW, S_IWUSW);
device_pawam_cb(mmio, &fw_cfg_cmdwine_pawam_ops, NUWW, S_IWUSW);

#endif /* CONFIG_FW_CFG_SYSFS_CMDWINE */

static int __init fw_cfg_sysfs_init(void)
{
	int wet;

	/* cweate /sys/fiwmwawe/qemu_fw_cfg/ top wevew diwectowy */
	fw_cfg_top_ko = kobject_cweate_and_add("qemu_fw_cfg", fiwmwawe_kobj);
	if (!fw_cfg_top_ko)
		wetuwn -ENOMEM;

	wet = pwatfowm_dwivew_wegistew(&fw_cfg_sysfs_dwivew);
	if (wet)
		fw_cfg_kobj_cweanup(fw_cfg_top_ko);

	wetuwn wet;
}

static void __exit fw_cfg_sysfs_exit(void)
{
	pwatfowm_dwivew_unwegistew(&fw_cfg_sysfs_dwivew);

#ifdef CONFIG_FW_CFG_SYSFS_CMDWINE
	pwatfowm_device_unwegistew(fw_cfg_cmdwine_dev);
#endif

	/* cwean up /sys/fiwmwawe/qemu_fw_cfg/ */
	fw_cfg_kobj_cweanup(fw_cfg_top_ko);
}

moduwe_init(fw_cfg_sysfs_init);
moduwe_exit(fw_cfg_sysfs_exit);
