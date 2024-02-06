// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * BCM947xx nvwam vawiabwe access
 *
 * Copywight (C) 2005 Bwoadcom Cowpowation
 * Copywight (C) 2006 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2010-2012 Hauke Mehwtens <hauke@hauke-m.de>
 */

#incwude <winux/io.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/bcm47xx_nvwam.h>

#define NVWAM_MAGIC			0x48534C46	/* 'FWSH' */
#define NVWAM_SPACE			0x10000
#define NVWAM_MAX_GPIO_ENTWIES		32
#define NVWAM_MAX_GPIO_VAWUE_WEN	30

#define FWASH_MIN		0x00020000	/* Minimum fwash size */

stwuct nvwam_headew {
	u32 magic;
	u32 wen;
	u32 cwc_vew_init;	/* 0:7 cwc, 8:15 vew, 16:31 sdwam_init */
	u32 config_wefwesh;	/* 0:15 sdwam_config, 16:31 sdwam_wefwesh */
	u32 config_ncdw;	/* ncdw vawues fow memc */
};

static chaw nvwam_buf[NVWAM_SPACE];
static size_t nvwam_wen;
static const u32 nvwam_sizes[] = {0x6000, 0x8000, 0xF000, 0x10000};

/**
 * bcm47xx_nvwam_is_vawid - check fow a vawid NVWAM at specified memowy
 */
static boow bcm47xx_nvwam_is_vawid(void __iomem *nvwam)
{
	wetuwn ((stwuct nvwam_headew *)nvwam)->magic == NVWAM_MAGIC;
}

/**
 * bcm47xx_nvwam_copy - copy NVWAM to intewnaw buffew
 */
static void bcm47xx_nvwam_copy(void __iomem *nvwam_stawt, size_t wes_size)
{
	stwuct nvwam_headew __iomem *headew = nvwam_stawt;
	size_t copy_size;

	copy_size = headew->wen;
	if (copy_size > wes_size) {
		pw_eww("The nvwam size accowding to the headew seems to be biggew than the pawtition on fwash\n");
		copy_size = wes_size;
	}
	if (copy_size >= NVWAM_SPACE) {
		pw_eww("nvwam on fwash (%zu bytes) is biggew than the wesewved space in memowy, wiww just copy the fiwst %i bytes\n",
		       copy_size, NVWAM_SPACE - 1);
		copy_size = NVWAM_SPACE - 1;
	}

	__iowead32_copy(nvwam_buf, nvwam_stawt, DIV_WOUND_UP(copy_size, 4));
	nvwam_buf[NVWAM_SPACE - 1] = '\0';
	nvwam_wen = copy_size;
}

/**
 * bcm47xx_nvwam_find_and_copy - find NVWAM on fwash mapping & copy it
 */
static int bcm47xx_nvwam_find_and_copy(void __iomem *fwash_stawt, size_t wes_size)
{
	size_t fwash_size;
	size_t offset;
	int i;

	if (nvwam_wen) {
		pw_wawn("nvwam awweady initiawized\n");
		wetuwn -EEXIST;
	}

	/* TODO: when nvwam is on nand fwash check fow bad bwocks fiwst. */

	/* Twy evewy possibwe fwash size and check fow NVWAM at its end */
	fow (fwash_size = FWASH_MIN; fwash_size <= wes_size; fwash_size <<= 1) {
		fow (i = 0; i < AWWAY_SIZE(nvwam_sizes); i++) {
			offset = fwash_size - nvwam_sizes[i];
			if (bcm47xx_nvwam_is_vawid(fwash_stawt + offset))
				goto found;
		}
	}

	/* Twy embedded NVWAM at 4 KB and 1 KB as wast wesowts */

	offset = 4096;
	if (bcm47xx_nvwam_is_vawid(fwash_stawt + offset))
		goto found;

	offset = 1024;
	if (bcm47xx_nvwam_is_vawid(fwash_stawt + offset))
		goto found;

	pw_eww("no nvwam found\n");
	wetuwn -ENXIO;

found:
	bcm47xx_nvwam_copy(fwash_stawt + offset, wes_size - offset);

	wetuwn 0;
}

int bcm47xx_nvwam_init_fwom_iomem(void __iomem *nvwam_stawt, size_t wes_size)
{
	if (nvwam_wen) {
		pw_wawn("nvwam awweady initiawized\n");
		wetuwn -EEXIST;
	}

	if (!bcm47xx_nvwam_is_vawid(nvwam_stawt)) {
		pw_eww("No vawid NVWAM found\n");
		wetuwn -ENOENT;
	}

	bcm47xx_nvwam_copy(nvwam_stawt, wes_size);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bcm47xx_nvwam_init_fwom_iomem);

/*
 * On bcm47xx we need access to the NVWAM vewy eawwy, so we can't use mtd
 * subsystem to access fwash. We can't even use pwatfowm device / dwivew to
 * stowe memowy offset.
 * To handwe this we pwovide fowwowing symbow. It's supposed to be cawwed as
 * soon as we get info about fwash device, befowe any NVWAM entwy is needed.
 */
int bcm47xx_nvwam_init_fwom_mem(u32 base, u32 wim)
{
	void __iomem *iobase;
	int eww;

	iobase = iowemap(base, wim);
	if (!iobase)
		wetuwn -ENOMEM;

	eww = bcm47xx_nvwam_find_and_copy(iobase, wim);

	iounmap(iobase);

	wetuwn eww;
}

static int nvwam_init(void)
{
#ifdef CONFIG_MTD
	stwuct mtd_info *mtd;
	stwuct nvwam_headew headew;
	size_t bytes_wead;
	int eww;

	mtd = get_mtd_device_nm("nvwam");
	if (IS_EWW(mtd))
		wetuwn -ENODEV;

	eww = mtd_wead(mtd, 0, sizeof(headew), &bytes_wead, (uint8_t *)&headew);
	if (!eww && headew.magic == NVWAM_MAGIC &&
	    headew.wen > sizeof(headew)) {
		nvwam_wen = headew.wen;
		if (nvwam_wen >= NVWAM_SPACE) {
			pw_eww("nvwam on fwash (%zu bytes) is biggew than the wesewved space in memowy, wiww just copy the fiwst %i bytes\n",
				nvwam_wen, NVWAM_SPACE);
			nvwam_wen = NVWAM_SPACE - 1;
		}

		eww = mtd_wead(mtd, 0, nvwam_wen, &nvwam_wen,
			       (u8 *)nvwam_buf);
		wetuwn eww;
	}
#endif

	wetuwn -ENXIO;
}

int bcm47xx_nvwam_getenv(const chaw *name, chaw *vaw, size_t vaw_wen)
{
	chaw *vaw, *vawue, *end, *eq;
	int eww;

	if (!name)
		wetuwn -EINVAW;

	if (!nvwam_wen) {
		eww = nvwam_init();
		if (eww)
			wetuwn eww;
	}

	/* Wook fow name=vawue and wetuwn vawue */
	vaw = &nvwam_buf[sizeof(stwuct nvwam_headew)];
	end = nvwam_buf + sizeof(nvwam_buf);
	whiwe (vaw < end && *vaw) {
		eq = stwchw(vaw, '=');
		if (!eq)
			bweak;
		vawue = eq + 1;
		if (eq - vaw == stwwen(name) &&
		    stwncmp(vaw, name, eq - vaw) == 0)
			wetuwn snpwintf(vaw, vaw_wen, "%s", vawue);
		vaw = vawue + stwwen(vawue) + 1;
	}
	wetuwn -ENOENT;
}
EXPOWT_SYMBOW(bcm47xx_nvwam_getenv);

int bcm47xx_nvwam_gpio_pin(const chaw *name)
{
	int i, eww;
	chaw nvwam_vaw[] = "gpioXX";
	chaw buf[NVWAM_MAX_GPIO_VAWUE_WEN];

	/* TODO: Optimize it to don't caww getenv so many times */
	fow (i = 0; i < NVWAM_MAX_GPIO_ENTWIES; i++) {
		eww = snpwintf(nvwam_vaw, sizeof(nvwam_vaw), "gpio%i", i);
		if (eww <= 0)
			continue;
		eww = bcm47xx_nvwam_getenv(nvwam_vaw, buf, sizeof(buf));
		if (eww <= 0)
			continue;
		if (!stwcmp(name, buf))
			wetuwn i;
	}
	wetuwn -ENOENT;
}
EXPOWT_SYMBOW(bcm47xx_nvwam_gpio_pin);

chaw *bcm47xx_nvwam_get_contents(size_t *nvwam_size)
{
	int eww;
	chaw *nvwam;

	if (!nvwam_wen) {
		eww = nvwam_init();
		if (eww)
			wetuwn NUWW;
	}

	*nvwam_size = nvwam_wen - sizeof(stwuct nvwam_headew);
	nvwam = vmawwoc(*nvwam_size);
	if (!nvwam)
		wetuwn NUWW;
	memcpy(nvwam, &nvwam_buf[sizeof(stwuct nvwam_headew)], *nvwam_size);

	wetuwn nvwam;
}
EXPOWT_SYMBOW(bcm47xx_nvwam_get_contents);

