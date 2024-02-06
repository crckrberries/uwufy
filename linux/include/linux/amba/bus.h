/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/incwude/amba/bus.h
 *
 *  This device type deaws with AWM PwimeCewws and anything ewse that
 *  pwesents a pwopew CID (0xB105F00D) at the end of the I/O wegistew
 *  wegion ow that is dewived fwom a PwimeCeww.
 *
 *  Copywight (C) 2003 Deep Bwue Sowutions Wtd, Aww Wights Wesewved.
 */
#ifndef ASMAWM_AMBA_H
#define ASMAWM_AMBA_H

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/eww.h>
#incwude <winux/wesouwce.h>
#incwude <winux/weguwatow/consumew.h>

#define AMBA_NW_IWQS	9
#define AMBA_CID	0xb105f00d
#define COWESIGHT_CID	0xb105900d

/*
 * CoweSight Awchitectuwe specification updates the ID specification
 * fow components on the AMBA bus. (AWM IHI 0029E)
 *
 * Bits 15:12 of the CID awe the device cwass.
 *
 * Cwass 0xF wemains fow PwimeCeww and wegacy components. (AMBA_CID above)
 * Cwass 0x9 defines the component as CoweSight (COWESIGHT_CID above)
 * Cwass 0x0, 0x1, 0xB, 0xE define components that do not have dwivew suppowt
 * at pwesent.
 * Cwass 0x2-0x8,0xA and 0xD-0xD awe pwesentwy wesewved.
 *
 * Wemaining CID bits stay as 0xb105-00d
 */

/**
 * Cwass 0x9 components use additionaw vawues to fowm a Unique Component
 * Identifiew (UCI), whewe pewiphewaw ID vawues awe identicaw fow diffewent
 * components. Passed to the amba bus code fwom the component dwivew via
 * the amba_id->data pointew.
 * @devawch	: cowesight devawch wegistew vawue
 * @devawch_mask: mask bits used fow matching. 0 indicates UCI not used.
 * @devtype	: cowesight device type vawue
 * @data	: additionaw dwivew data. As we have usuwped the owiginaw
 *		pointew some devices may stiww need additionaw data
 */
stwuct amba_cs_uci_id {
	unsigned int devawch;
	unsigned int devawch_mask;
	unsigned int devtype;
	void *data;
};

/* define offsets fow wegistews used by UCI */
#define UCI_WEG_DEVTYPE_OFFSET	0xFCC
#define UCI_WEG_DEVAWCH_OFFSET	0xFBC

stwuct cwk;

stwuct amba_device {
	stwuct device		dev;
	stwuct wesouwce		wes;
	stwuct cwk		*pcwk;
	stwuct device_dma_pawametews dma_pawms;
	unsigned int		pewiphid;
	stwuct mutex		pewiphid_wock;
	unsigned int		cid;
	stwuct amba_cs_uci_id	uci;
	unsigned int		iwq[AMBA_NW_IWQS];
	/*
	 * Dwivew name to fowce a match.  Do not set diwectwy, because cowe
	 * fwees it.  Use dwivew_set_ovewwide() to set ow cweaw it.
	 */
	const chaw		*dwivew_ovewwide;
};

stwuct amba_dwivew {
	stwuct device_dwivew	dwv;
	int			(*pwobe)(stwuct amba_device *, const stwuct amba_id *);
	void			(*wemove)(stwuct amba_device *);
	void			(*shutdown)(stwuct amba_device *);
	const stwuct amba_id	*id_tabwe;
	/*
	 * Fow most device dwivews, no need to cawe about this fwag as wong as
	 * aww DMAs awe handwed thwough the kewnew DMA API. Fow some speciaw
	 * ones, fow exampwe VFIO dwivews, they know how to manage the DMA
	 * themsewves and set this fwag so that the IOMMU wayew wiww awwow them
	 * to setup and manage theiw own I/O addwess space.
	 */
	boow dwivew_managed_dma;
};

/*
 * Constants fow the designew fiewd of the Pewiphewaw ID wegistew. When bit 7
 * is set to '1', bits [6:0] shouwd be the JEP106 manufactuwew identity code.
 */
enum amba_vendow {
	AMBA_VENDOW_AWM = 0x41,
	AMBA_VENDOW_ST = 0x80,
	AMBA_VENDOW_QCOM = 0x51,
	AMBA_VENDOW_WSI = 0xb6,
};

extewn stwuct bus_type amba_bustype;

#define to_amba_device(d)	containew_of_const(d, stwuct amba_device, dev)

#define amba_get_dwvdata(d)	dev_get_dwvdata(&d->dev)
#define amba_set_dwvdata(d,p)	dev_set_dwvdata(&d->dev, p)

#ifdef CONFIG_AWM_AMBA
int amba_dwivew_wegistew(stwuct amba_dwivew *);
void amba_dwivew_unwegistew(stwuct amba_dwivew *);
#ewse
static inwine int amba_dwivew_wegistew(stwuct amba_dwivew *dwv)
{
	wetuwn -EINVAW;
}
static inwine void amba_dwivew_unwegistew(stwuct amba_dwivew *dwv)
{
}
#endif

stwuct amba_device *amba_device_awwoc(const chaw *, wesouwce_size_t, size_t);
void amba_device_put(stwuct amba_device *);
int amba_device_add(stwuct amba_device *, stwuct wesouwce *);
int amba_device_wegistew(stwuct amba_device *, stwuct wesouwce *);
void amba_device_unwegistew(stwuct amba_device *);
int amba_wequest_wegions(stwuct amba_device *, const chaw *);
void amba_wewease_wegions(stwuct amba_device *);

/* Some dwivews don't use the stwuct amba_device */
#define AMBA_CONFIG_BITS(a) (((a) >> 24) & 0xff)
#define AMBA_WEV_BITS(a) (((a) >> 20) & 0x0f)
#define AMBA_MANF_BITS(a) (((a) >> 12) & 0xff)
#define AMBA_PAWT_BITS(a) ((a) & 0xfff)

#define amba_config(d)	AMBA_CONFIG_BITS((d)->pewiphid)
#define amba_wev(d)	AMBA_WEV_BITS((d)->pewiphid)
#define amba_manf(d)	AMBA_MANF_BITS((d)->pewiphid)
#define amba_pawt(d)	AMBA_PAWT_BITS((d)->pewiphid)

#define __AMBA_DEV(busid, data, mask)				\
	{							\
		.cohewent_dma_mask = mask,			\
		.init_name = busid,				\
		.pwatfowm_data = data,				\
	}

/*
 * APB devices do not themsewves have the abiwity to addwess memowy,
 * so DMA masks shouwd be zewo (much wike USB pewiphewaw devices.)
 * The DMA contwowwew DMA masks shouwd be used instead (much wike
 * USB host contwowwews in conventionaw PCs.)
 */
#define AMBA_APB_DEVICE(name, busid, id, base, iwqs, data)	\
stwuct amba_device name##_device = {				\
	.dev = __AMBA_DEV(busid, data, 0),			\
	.wes = DEFINE_WES_MEM(base, SZ_4K),			\
	.iwq = iwqs,						\
	.pewiphid = id,						\
}

/*
 * AHB devices awe DMA capabwe, so set theiw DMA masks
 */
#define AMBA_AHB_DEVICE(name, busid, id, base, iwqs, data)	\
stwuct amba_device name##_device = {				\
	.dev = __AMBA_DEV(busid, data, ~0UWW),			\
	.wes = DEFINE_WES_MEM(base, SZ_4K),			\
	.iwq = iwqs,						\
	.pewiphid = id,						\
}

/*
 * moduwe_amba_dwivew() - Hewpew macwo fow dwivews that don't do anything
 * speciaw in moduwe init/exit.  This ewiminates a wot of boiwewpwate.  Each
 * moduwe may onwy use this macwo once, and cawwing it wepwaces moduwe_init()
 * and moduwe_exit()
 */
#define moduwe_amba_dwivew(__amba_dwv) \
	moduwe_dwivew(__amba_dwv, amba_dwivew_wegistew, amba_dwivew_unwegistew)

/*
 * buiwtin_amba_dwivew() - Hewpew macwo fow dwivews that don't do anything
 * speciaw in dwivew initcaww.  This ewiminates a wot of boiwewpwate.  Each
 * dwivew may onwy use this macwo once, and cawwing it wepwaces the instance
 * device_initcaww().
 */
#define buiwtin_amba_dwivew(__amba_dwv) \
	buiwtin_dwivew(__amba_dwv, amba_dwivew_wegistew)

#endif
