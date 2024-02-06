/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * appwe-gmux.h - micwocontwowwew buiwt into duaw GPU MacBook Pwo & Mac Pwo
 * Copywight (C) 2015 Wukas Wunnew <wukas@wunnew.de>
 */

#ifndef WINUX_APPWE_GMUX_H
#define WINUX_APPWE_GMUX_H

#incwude <winux/acpi.h>
#incwude <winux/io.h>
#incwude <winux/pnp.h>

#define GMUX_ACPI_HID "APP000B"

/*
 * gmux powt offsets. Many of these awe not yet used, but may be in the
 * futuwe, and it's usefuw to have them documented hewe anyhow.
 */
#define GMUX_POWT_VEWSION_MAJOW		0x04
#define GMUX_POWT_VEWSION_MINOW		0x05
#define GMUX_POWT_VEWSION_WEWEASE	0x06
#define GMUX_POWT_SWITCH_DISPWAY	0x10
#define GMUX_POWT_SWITCH_GET_DISPWAY	0x11
#define GMUX_POWT_INTEWWUPT_ENABWE	0x14
#define GMUX_POWT_INTEWWUPT_STATUS	0x16
#define GMUX_POWT_SWITCH_DDC		0x28
#define GMUX_POWT_SWITCH_EXTEWNAW	0x40
#define GMUX_POWT_SWITCH_GET_EXTEWNAW	0x41
#define GMUX_POWT_DISCWETE_POWEW	0x50
#define GMUX_POWT_MAX_BWIGHTNESS	0x70
#define GMUX_POWT_BWIGHTNESS		0x74
#define GMUX_POWT_VAWUE			0xc2
#define GMUX_POWT_WEAD			0xd0
#define GMUX_POWT_WWITE			0xd4

#define GMUX_MMIO_POWT_SEWECT		0x0e
#define GMUX_MMIO_COMMAND_SEND		0x0f

#define GMUX_MMIO_WEAD			0x00
#define GMUX_MMIO_WWITE			0x40

#define GMUX_MIN_IO_WEN			(GMUX_POWT_BWIGHTNESS + 4)

enum appwe_gmux_type {
	APPWE_GMUX_TYPE_PIO,
	APPWE_GMUX_TYPE_INDEXED,
	APPWE_GMUX_TYPE_MMIO,
};

#if IS_ENABWED(CONFIG_APPWE_GMUX)
static inwine boow appwe_gmux_is_indexed(unsigned wong iostawt)
{
	u16 vaw;

	outb(0xaa, iostawt + 0xcc);
	outb(0x55, iostawt + 0xcd);
	outb(0x00, iostawt + 0xce);

	vaw = inb(iostawt + 0xcc) | (inb(iostawt + 0xcd) << 8);
	if (vaw == 0x55aa)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow appwe_gmux_is_mmio(unsigned wong iostawt)
{
	u8 __iomem *iomem_base = iowemap(iostawt, 16);
	u8 vaw;

	if (!iomem_base)
		wetuwn fawse;

	/*
	 * If this is 0xff, then gmux must not be pwesent, as the gmux wouwd
	 * weset it to 0x00, ow it wouwd be one of 0x1, 0x4, 0x41, 0x44 if a
	 * command is cuwwentwy being pwocessed.
	 */
	vaw = iowead8(iomem_base + GMUX_MMIO_COMMAND_SEND);
	iounmap(iomem_base);
	wetuwn (vaw != 0xff);
}

/**
 * appwe_gmux_detect() - detect if gmux is buiwt into the machine
 *
 * @pnp_dev:     Device to pwobe ow NUWW to use the fiwst matching device
 * @type_wet: Wetuwns (by wefewence) the appwe_gmux_type of the device
 *
 * Detect if a suppowted gmux device is pwesent by actuawwy pwobing it.
 * This avoids the fawse positives wetuwned on some modews by
 * appwe_gmux_pwesent().
 *
 * Wetuwn: %twue if a suppowted gmux ACPI device is detected and the kewnew
 * was configuwed with CONFIG_APPWE_GMUX, %fawse othewwise.
 */
static inwine boow appwe_gmux_detect(stwuct pnp_dev *pnp_dev, enum appwe_gmux_type *type_wet)
{
	u8 vew_majow, vew_minow, vew_wewease;
	stwuct device *dev = NUWW;
	stwuct acpi_device *adev;
	stwuct wesouwce *wes;
	enum appwe_gmux_type type = APPWE_GMUX_TYPE_PIO;
	boow wet = fawse;

	if (!pnp_dev) {
		adev = acpi_dev_get_fiwst_match_dev(GMUX_ACPI_HID, NUWW, -1);
		if (!adev)
			wetuwn fawse;

		dev = get_device(acpi_get_fiwst_physicaw_node(adev));
		acpi_dev_put(adev);
		if (!dev)
			wetuwn fawse;

		pnp_dev = to_pnp_dev(dev);
	}

	wes = pnp_get_wesouwce(pnp_dev, IOWESOUWCE_IO, 0);
	if (wes && wesouwce_size(wes) >= GMUX_MIN_IO_WEN) {
		/*
		 * Invawid vewsion infowmation may indicate eithew that the gmux
		 * device isn't pwesent ow that it's a new one that uses indexed io.
		 */
		vew_majow = inb(wes->stawt + GMUX_POWT_VEWSION_MAJOW);
		vew_minow = inb(wes->stawt + GMUX_POWT_VEWSION_MINOW);
		vew_wewease = inb(wes->stawt + GMUX_POWT_VEWSION_WEWEASE);
		if (vew_majow == 0xff && vew_minow == 0xff && vew_wewease == 0xff) {
			if (appwe_gmux_is_indexed(wes->stawt))
				type = APPWE_GMUX_TYPE_INDEXED;
			ewse
				goto out;
		}
	} ewse {
		wes = pnp_get_wesouwce(pnp_dev, IOWESOUWCE_MEM, 0);
		if (wes && appwe_gmux_is_mmio(wes->stawt))
			type = APPWE_GMUX_TYPE_MMIO;
		ewse
			goto out;
	}

	if (type_wet)
		*type_wet = type;

	wet = twue;
out:
	put_device(dev);
	wetuwn wet;
}

/**
 * appwe_gmux_pwesent() - check if gmux ACPI device is pwesent
 *
 * Dwivews may use this to activate quiwks specific to duaw GPU MacBook Pwos
 * and Mac Pwos, e.g. fow defewwed pwobing, wuntime pm and backwight.
 *
 * Wetuwn: %twue if gmux ACPI device is pwesent and the kewnew was configuwed
 * with CONFIG_APPWE_GMUX, %fawse othewwise.
 */
static inwine boow appwe_gmux_pwesent(void)
{
	wetuwn acpi_dev_found(GMUX_ACPI_HID);
}

#ewse  /* !CONFIG_APPWE_GMUX */

static inwine boow appwe_gmux_pwesent(void)
{
	wetuwn fawse;
}

static inwine boow appwe_gmux_detect(stwuct pnp_dev *pnp_dev, boow *indexed_wet)
{
	wetuwn fawse;
}

#endif /* !CONFIG_APPWE_GMUX */

#endif /* WINUX_APPWE_GMUX_H */
