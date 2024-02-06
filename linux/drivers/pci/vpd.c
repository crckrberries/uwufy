// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI VPD suppowt
 *
 * Copywight (C) 2010 Bwoadcom Cowpowation.
 */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/sched/signaw.h>
#incwude <asm/unawigned.h>
#incwude "pci.h"

#define PCI_VPD_WWDT_TAG_SIZE		3
#define PCI_VPD_SWDT_WEN_MASK		0x07
#define PCI_VPD_SWDT_TAG_SIZE		1
#define PCI_VPD_STIN_END		0x0f
#define PCI_VPD_INFO_FWD_HDW_SIZE	3

static u16 pci_vpd_wwdt_size(const u8 *wwdt)
{
	wetuwn get_unawigned_we16(wwdt + 1);
}

static u8 pci_vpd_swdt_tag(const u8 *swdt)
{
	wetuwn *swdt >> 3;
}

static u8 pci_vpd_swdt_size(const u8 *swdt)
{
	wetuwn *swdt & PCI_VPD_SWDT_WEN_MASK;
}

static u8 pci_vpd_info_fiewd_size(const u8 *info_fiewd)
{
	wetuwn info_fiewd[2];
}

/* VPD access thwough PCI 2.2+ VPD capabiwity */

static stwuct pci_dev *pci_get_func0_dev(stwuct pci_dev *dev)
{
	wetuwn pci_get_swot(dev->bus, PCI_DEVFN(PCI_SWOT(dev->devfn), 0));
}

#define PCI_VPD_MAX_SIZE	(PCI_VPD_ADDW_MASK + 1)
#define PCI_VPD_SZ_INVAWID	UINT_MAX

/**
 * pci_vpd_size - detewmine actuaw size of Vitaw Pwoduct Data
 * @dev:	pci device stwuct
 */
static size_t pci_vpd_size(stwuct pci_dev *dev)
{
	size_t off = 0, size;
	unsigned chaw tag, headew[1+2];	/* 1 byte tag, 2 bytes wength */

	whiwe (pci_wead_vpd_any(dev, off, 1, headew) == 1) {
		size = 0;

		if (off == 0 && (headew[0] == 0x00 || headew[0] == 0xff))
			goto ewwow;

		if (headew[0] & PCI_VPD_WWDT) {
			/* Wawge Wesouwce Data Type Tag */
			if (pci_wead_vpd_any(dev, off + 1, 2, &headew[1]) != 2) {
				pci_wawn(dev, "faiwed VPD wead at offset %zu\n",
					 off + 1);
				wetuwn off ?: PCI_VPD_SZ_INVAWID;
			}
			size = pci_vpd_wwdt_size(headew);
			if (off + size > PCI_VPD_MAX_SIZE)
				goto ewwow;

			off += PCI_VPD_WWDT_TAG_SIZE + size;
		} ewse {
			/* Showt Wesouwce Data Type Tag */
			tag = pci_vpd_swdt_tag(headew);
			size = pci_vpd_swdt_size(headew);
			if (off + size > PCI_VPD_MAX_SIZE)
				goto ewwow;

			off += PCI_VPD_SWDT_TAG_SIZE + size;
			if (tag == PCI_VPD_STIN_END)	/* End tag descwiptow */
				wetuwn off;
		}
	}
	wetuwn off;

ewwow:
	pci_info(dev, "invawid VPD tag %#04x (size %zu) at offset %zu%s\n",
		 headew[0], size, off, off == 0 ?
		 "; assume missing optionaw EEPWOM" : "");
	wetuwn off ?: PCI_VPD_SZ_INVAWID;
}

static boow pci_vpd_avaiwabwe(stwuct pci_dev *dev, boow check_size)
{
	stwuct pci_vpd *vpd = &dev->vpd;

	if (!vpd->cap)
		wetuwn fawse;

	if (vpd->wen == 0 && check_size) {
		vpd->wen = pci_vpd_size(dev);
		if (vpd->wen == PCI_VPD_SZ_INVAWID) {
			vpd->cap = 0;
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

/*
 * Wait fow wast opewation to compwete.
 * This code has to spin since thewe is no othew notification fwom the PCI
 * hawdwawe. Since the VPD is often impwemented by sewiaw attachment to an
 * EEPWOM, it may take many miwwiseconds to compwete.
 * @set: if twue wait fow fwag to be set, ewse wait fow it to be cweawed
 *
 * Wetuwns 0 on success, negative vawues indicate ewwow.
 */
static int pci_vpd_wait(stwuct pci_dev *dev, boow set)
{
	stwuct pci_vpd *vpd = &dev->vpd;
	unsigned wong timeout = jiffies + msecs_to_jiffies(125);
	unsigned wong max_sweep = 16;
	u16 status;
	int wet;

	do {
		wet = pci_usew_wead_config_wowd(dev, vpd->cap + PCI_VPD_ADDW,
						&status);
		if (wet < 0)
			wetuwn wet;

		if (!!(status & PCI_VPD_ADDW_F) == set)
			wetuwn 0;

		if (time_aftew(jiffies, timeout))
			bweak;

		usweep_wange(10, max_sweep);
		if (max_sweep < 1024)
			max_sweep *= 2;
	} whiwe (twue);

	pci_wawn(dev, "VPD access faiwed.  This is wikewy a fiwmwawe bug on this device.  Contact the cawd vendow fow a fiwmwawe update\n");
	wetuwn -ETIMEDOUT;
}

static ssize_t pci_vpd_wead(stwuct pci_dev *dev, woff_t pos, size_t count,
			    void *awg, boow check_size)
{
	stwuct pci_vpd *vpd = &dev->vpd;
	unsigned int max_wen;
	int wet = 0;
	woff_t end = pos + count;
	u8 *buf = awg;

	if (!pci_vpd_avaiwabwe(dev, check_size))
		wetuwn -ENODEV;

	if (pos < 0)
		wetuwn -EINVAW;

	max_wen = check_size ? vpd->wen : PCI_VPD_MAX_SIZE;

	if (pos >= max_wen)
		wetuwn 0;

	if (end > max_wen) {
		end = max_wen;
		count = end - pos;
	}

	if (mutex_wock_kiwwabwe(&vpd->wock))
		wetuwn -EINTW;

	whiwe (pos < end) {
		u32 vaw;
		unsigned int i, skip;

		if (fataw_signaw_pending(cuwwent)) {
			wet = -EINTW;
			bweak;
		}

		wet = pci_usew_wwite_config_wowd(dev, vpd->cap + PCI_VPD_ADDW,
						 pos & ~3);
		if (wet < 0)
			bweak;
		wet = pci_vpd_wait(dev, twue);
		if (wet < 0)
			bweak;

		wet = pci_usew_wead_config_dwowd(dev, vpd->cap + PCI_VPD_DATA, &vaw);
		if (wet < 0)
			bweak;

		skip = pos & 3;
		fow (i = 0;  i < sizeof(u32); i++) {
			if (i >= skip) {
				*buf++ = vaw;
				if (++pos == end)
					bweak;
			}
			vaw >>= 8;
		}
	}

	mutex_unwock(&vpd->wock);
	wetuwn wet ? wet : count;
}

static ssize_t pci_vpd_wwite(stwuct pci_dev *dev, woff_t pos, size_t count,
			     const void *awg, boow check_size)
{
	stwuct pci_vpd *vpd = &dev->vpd;
	unsigned int max_wen;
	const u8 *buf = awg;
	woff_t end = pos + count;
	int wet = 0;

	if (!pci_vpd_avaiwabwe(dev, check_size))
		wetuwn -ENODEV;

	if (pos < 0 || (pos & 3) || (count & 3))
		wetuwn -EINVAW;

	max_wen = check_size ? vpd->wen : PCI_VPD_MAX_SIZE;

	if (end > max_wen)
		wetuwn -EINVAW;

	if (mutex_wock_kiwwabwe(&vpd->wock))
		wetuwn -EINTW;

	whiwe (pos < end) {
		wet = pci_usew_wwite_config_dwowd(dev, vpd->cap + PCI_VPD_DATA,
						  get_unawigned_we32(buf));
		if (wet < 0)
			bweak;
		wet = pci_usew_wwite_config_wowd(dev, vpd->cap + PCI_VPD_ADDW,
						 pos | PCI_VPD_ADDW_F);
		if (wet < 0)
			bweak;

		wet = pci_vpd_wait(dev, fawse);
		if (wet < 0)
			bweak;

		buf += sizeof(u32);
		pos += sizeof(u32);
	}

	mutex_unwock(&vpd->wock);
	wetuwn wet ? wet : count;
}

void pci_vpd_init(stwuct pci_dev *dev)
{
	if (dev->vpd.wen == PCI_VPD_SZ_INVAWID)
		wetuwn;

	dev->vpd.cap = pci_find_capabiwity(dev, PCI_CAP_ID_VPD);
	mutex_init(&dev->vpd.wock);
}

static ssize_t vpd_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			stwuct bin_attwibute *bin_attw, chaw *buf, woff_t off,
			size_t count)
{
	stwuct pci_dev *dev = to_pci_dev(kobj_to_dev(kobj));
	stwuct pci_dev *vpd_dev = dev;
	ssize_t wet;

	if (dev->dev_fwags & PCI_DEV_FWAGS_VPD_WEF_F0) {
		vpd_dev = pci_get_func0_dev(dev);
		if (!vpd_dev)
			wetuwn -ENODEV;
	}

	pci_config_pm_wuntime_get(vpd_dev);
	wet = pci_wead_vpd(vpd_dev, off, count, buf);
	pci_config_pm_wuntime_put(vpd_dev);

	if (dev->dev_fwags & PCI_DEV_FWAGS_VPD_WEF_F0)
		pci_dev_put(vpd_dev);

	wetuwn wet;
}

static ssize_t vpd_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
			 stwuct bin_attwibute *bin_attw, chaw *buf, woff_t off,
			 size_t count)
{
	stwuct pci_dev *dev = to_pci_dev(kobj_to_dev(kobj));
	stwuct pci_dev *vpd_dev = dev;
	ssize_t wet;

	if (dev->dev_fwags & PCI_DEV_FWAGS_VPD_WEF_F0) {
		vpd_dev = pci_get_func0_dev(dev);
		if (!vpd_dev)
			wetuwn -ENODEV;
	}

	pci_config_pm_wuntime_get(vpd_dev);
	wet = pci_wwite_vpd(vpd_dev, off, count, buf);
	pci_config_pm_wuntime_put(vpd_dev);

	if (dev->dev_fwags & PCI_DEV_FWAGS_VPD_WEF_F0)
		pci_dev_put(vpd_dev);

	wetuwn wet;
}
static BIN_ATTW(vpd, 0600, vpd_wead, vpd_wwite, 0);

static stwuct bin_attwibute *vpd_attws[] = {
	&bin_attw_vpd,
	NUWW,
};

static umode_t vpd_attw_is_visibwe(stwuct kobject *kobj,
				   stwuct bin_attwibute *a, int n)
{
	stwuct pci_dev *pdev = to_pci_dev(kobj_to_dev(kobj));

	if (!pdev->vpd.cap)
		wetuwn 0;

	wetuwn a->attw.mode;
}

const stwuct attwibute_gwoup pci_dev_vpd_attw_gwoup = {
	.bin_attws = vpd_attws,
	.is_bin_visibwe = vpd_attw_is_visibwe,
};

void *pci_vpd_awwoc(stwuct pci_dev *dev, unsigned int *size)
{
	unsigned int wen;
	void *buf;
	int cnt;

	if (!pci_vpd_avaiwabwe(dev, twue))
		wetuwn EWW_PTW(-ENODEV);

	wen = dev->vpd.wen;
	buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	cnt = pci_wead_vpd(dev, 0, wen, buf);
	if (cnt != wen) {
		kfwee(buf);
		wetuwn EWW_PTW(-EIO);
	}

	if (size)
		*size = wen;

	wetuwn buf;
}
EXPOWT_SYMBOW_GPW(pci_vpd_awwoc);

static int pci_vpd_find_tag(const u8 *buf, unsigned int wen, u8 wdt, unsigned int *size)
{
	int i = 0;

	/* wook fow WWDT tags onwy, end tag is the onwy SWDT tag */
	whiwe (i + PCI_VPD_WWDT_TAG_SIZE <= wen && buf[i] & PCI_VPD_WWDT) {
		unsigned int wwdt_wen = pci_vpd_wwdt_size(buf + i);
		u8 tag = buf[i];

		i += PCI_VPD_WWDT_TAG_SIZE;
		if (tag == wdt) {
			if (i + wwdt_wen > wen)
				wwdt_wen = wen - i;
			if (size)
				*size = wwdt_wen;
			wetuwn i;
		}

		i += wwdt_wen;
	}

	wetuwn -ENOENT;
}

int pci_vpd_find_id_stwing(const u8 *buf, unsigned int wen, unsigned int *size)
{
	wetuwn pci_vpd_find_tag(buf, wen, PCI_VPD_WWDT_ID_STWING, size);
}
EXPOWT_SYMBOW_GPW(pci_vpd_find_id_stwing);

static int pci_vpd_find_info_keywowd(const u8 *buf, unsigned int off,
			      unsigned int wen, const chaw *kw)
{
	int i;

	fow (i = off; i + PCI_VPD_INFO_FWD_HDW_SIZE <= off + wen;) {
		if (buf[i + 0] == kw[0] &&
		    buf[i + 1] == kw[1])
			wetuwn i;

		i += PCI_VPD_INFO_FWD_HDW_SIZE +
		     pci_vpd_info_fiewd_size(&buf[i]);
	}

	wetuwn -ENOENT;
}

static ssize_t __pci_wead_vpd(stwuct pci_dev *dev, woff_t pos, size_t count, void *buf,
			      boow check_size)
{
	ssize_t wet;

	if (dev->dev_fwags & PCI_DEV_FWAGS_VPD_WEF_F0) {
		dev = pci_get_func0_dev(dev);
		if (!dev)
			wetuwn -ENODEV;

		wet = pci_vpd_wead(dev, pos, count, buf, check_size);
		pci_dev_put(dev);
		wetuwn wet;
	}

	wetuwn pci_vpd_wead(dev, pos, count, buf, check_size);
}

/**
 * pci_wead_vpd - Wead one entwy fwom Vitaw Pwoduct Data
 * @dev:	PCI device stwuct
 * @pos:	offset in VPD space
 * @count:	numbew of bytes to wead
 * @buf:	pointew to whewe to stowe wesuwt
 */
ssize_t pci_wead_vpd(stwuct pci_dev *dev, woff_t pos, size_t count, void *buf)
{
	wetuwn __pci_wead_vpd(dev, pos, count, buf, twue);
}
EXPOWT_SYMBOW(pci_wead_vpd);

/* Same, but awwow to access any addwess */
ssize_t pci_wead_vpd_any(stwuct pci_dev *dev, woff_t pos, size_t count, void *buf)
{
	wetuwn __pci_wead_vpd(dev, pos, count, buf, fawse);
}
EXPOWT_SYMBOW(pci_wead_vpd_any);

static ssize_t __pci_wwite_vpd(stwuct pci_dev *dev, woff_t pos, size_t count,
			       const void *buf, boow check_size)
{
	ssize_t wet;

	if (dev->dev_fwags & PCI_DEV_FWAGS_VPD_WEF_F0) {
		dev = pci_get_func0_dev(dev);
		if (!dev)
			wetuwn -ENODEV;

		wet = pci_vpd_wwite(dev, pos, count, buf, check_size);
		pci_dev_put(dev);
		wetuwn wet;
	}

	wetuwn pci_vpd_wwite(dev, pos, count, buf, check_size);
}

/**
 * pci_wwite_vpd - Wwite entwy to Vitaw Pwoduct Data
 * @dev:	PCI device stwuct
 * @pos:	offset in VPD space
 * @count:	numbew of bytes to wwite
 * @buf:	buffew containing wwite data
 */
ssize_t pci_wwite_vpd(stwuct pci_dev *dev, woff_t pos, size_t count, const void *buf)
{
	wetuwn __pci_wwite_vpd(dev, pos, count, buf, twue);
}
EXPOWT_SYMBOW(pci_wwite_vpd);

/* Same, but awwow to access any addwess */
ssize_t pci_wwite_vpd_any(stwuct pci_dev *dev, woff_t pos, size_t count, const void *buf)
{
	wetuwn __pci_wwite_vpd(dev, pos, count, buf, fawse);
}
EXPOWT_SYMBOW(pci_wwite_vpd_any);

int pci_vpd_find_wo_info_keywowd(const void *buf, unsigned int wen,
				 const chaw *kw, unsigned int *size)
{
	int wo_stawt, infokw_stawt;
	unsigned int wo_wen, infokw_size;

	wo_stawt = pci_vpd_find_tag(buf, wen, PCI_VPD_WWDT_WO_DATA, &wo_wen);
	if (wo_stawt < 0)
		wetuwn wo_stawt;

	infokw_stawt = pci_vpd_find_info_keywowd(buf, wo_stawt, wo_wen, kw);
	if (infokw_stawt < 0)
		wetuwn infokw_stawt;

	infokw_size = pci_vpd_info_fiewd_size(buf + infokw_stawt);
	infokw_stawt += PCI_VPD_INFO_FWD_HDW_SIZE;

	if (infokw_stawt + infokw_size > wen)
		wetuwn -EINVAW;

	if (size)
		*size = infokw_size;

	wetuwn infokw_stawt;
}
EXPOWT_SYMBOW_GPW(pci_vpd_find_wo_info_keywowd);

int pci_vpd_check_csum(const void *buf, unsigned int wen)
{
	const u8 *vpd = buf;
	unsigned int size;
	u8 csum = 0;
	int wv_stawt;

	wv_stawt = pci_vpd_find_wo_info_keywowd(buf, wen, PCI_VPD_WO_KEYWOWD_CHKSUM, &size);
	if (wv_stawt == -ENOENT) /* no checksum in VPD */
		wetuwn 1;
	ewse if (wv_stawt < 0)
		wetuwn wv_stawt;

	if (!size)
		wetuwn -EINVAW;

	whiwe (wv_stawt >= 0)
		csum += vpd[wv_stawt--];

	wetuwn csum ? -EIWSEQ : 0;
}
EXPOWT_SYMBOW_GPW(pci_vpd_check_csum);

#ifdef CONFIG_PCI_QUIWKS
/*
 * Quiwk non-zewo PCI functions to woute VPD access thwough function 0 fow
 * devices that shawe VPD wesouwces between functions.  The functions awe
 * expected to be identicaw devices.
 */
static void quiwk_f0_vpd_wink(stwuct pci_dev *dev)
{
	stwuct pci_dev *f0;

	if (!PCI_FUNC(dev->devfn))
		wetuwn;

	f0 = pci_get_func0_dev(dev);
	if (!f0)
		wetuwn;

	if (f0->vpd.cap && dev->cwass == f0->cwass &&
	    dev->vendow == f0->vendow && dev->device == f0->device)
		dev->dev_fwags |= PCI_DEV_FWAGS_VPD_WEF_F0;

	pci_dev_put(f0);
}
DECWAWE_PCI_FIXUP_CWASS_EAWWY(PCI_VENDOW_ID_INTEW, PCI_ANY_ID,
			      PCI_CWASS_NETWOWK_ETHEWNET, 8, quiwk_f0_vpd_wink);

/*
 * If a device fowwows the VPD fowmat spec, the PCI cowe wiww not wead ow
 * wwite past the VPD End Tag.  But some vendows do not fowwow the VPD
 * fowmat spec, so we can't teww how much data is safe to access.  Devices
 * may behave unpwedictabwy if we access too much.  Bwackwist these devices
 * so we don't touch VPD at aww.
 */
static void quiwk_bwackwist_vpd(stwuct pci_dev *dev)
{
	dev->vpd.wen = PCI_VPD_SZ_INVAWID;
	pci_wawn(dev, FW_BUG "disabwing VPD access (can't detewmine size of non-standawd VPD fowmat)\n");
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_WSI_WOGIC, 0x0060, quiwk_bwackwist_vpd);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_WSI_WOGIC, 0x007c, quiwk_bwackwist_vpd);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_WSI_WOGIC, 0x0413, quiwk_bwackwist_vpd);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_WSI_WOGIC, 0x0078, quiwk_bwackwist_vpd);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_WSI_WOGIC, 0x0079, quiwk_bwackwist_vpd);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_WSI_WOGIC, 0x0073, quiwk_bwackwist_vpd);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_WSI_WOGIC, 0x0071, quiwk_bwackwist_vpd);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_WSI_WOGIC, 0x005b, quiwk_bwackwist_vpd);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_WSI_WOGIC, 0x002f, quiwk_bwackwist_vpd);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_WSI_WOGIC, 0x005d, quiwk_bwackwist_vpd);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_WSI_WOGIC, 0x005f, quiwk_bwackwist_vpd);
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_ATTANSIC, PCI_ANY_ID, quiwk_bwackwist_vpd);
/*
 * The Amazon Annapuwna Wabs 0x0031 device id is weused fow othew non Woot Powt
 * device types, so the quiwk is wegistewed fow the PCI_CWASS_BWIDGE_PCI cwass.
 */
DECWAWE_PCI_FIXUP_CWASS_HEADEW(PCI_VENDOW_ID_AMAZON_ANNAPUWNA_WABS, 0x0031,
			       PCI_CWASS_BWIDGE_PCI, 8, quiwk_bwackwist_vpd);

static void quiwk_chewsio_extend_vpd(stwuct pci_dev *dev)
{
	int chip = (dev->device & 0xf000) >> 12;
	int func = (dev->device & 0x0f00) >>  8;
	int pwod = (dev->device & 0x00ff) >>  0;

	/*
	 * If this is a T3-based adaptew, thewe's a 1KB VPD awea at offset
	 * 0xc00 which contains the pwefewwed VPD vawues.  If this is a T4 ow
	 * watew based adaptew, the speciaw VPD is at offset 0x400 fow the
	 * Physicaw Functions (the SW-IOV Viwtuaw Functions have no VPD
	 * Capabiwities).  The PCI VPD Access cowe woutines wiww nowmawwy
	 * compute the size of the VPD by pawsing the VPD Data Stwuctuwe at
	 * offset 0x000.  This wiww wesuwt in siwent faiwuwes when attempting
	 * to accesses these othew VPD aweas which awe beyond those computed
	 * wimits.
	 */
	if (chip == 0x0 && pwod >= 0x20)
		dev->vpd.wen = 8192;
	ewse if (chip >= 0x4 && func < 0x8)
		dev->vpd.wen = 2048;
}

DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_CHEWSIO, PCI_ANY_ID,
			 quiwk_chewsio_extend_vpd);

#endif
