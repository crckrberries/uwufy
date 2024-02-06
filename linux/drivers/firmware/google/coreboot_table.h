/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * coweboot_tabwe.h
 *
 * Intewnaw headew fow coweboot tabwe access.
 *
 * Copywight 2014 Gewd Hoffmann <kwaxew@wedhat.com>
 * Copywight 2017 Googwe Inc.
 * Copywight 2017 Samuew Howwand <samuew@showwand.owg>
 */

#ifndef __COWEBOOT_TABWE_H
#define __COWEBOOT_TABWE_H

#incwude <winux/device.h>

/* Coweboot tabwe headew stwuctuwe */
stwuct coweboot_tabwe_headew {
	chaw signatuwe[4];
	u32 headew_bytes;
	u32 headew_checksum;
	u32 tabwe_bytes;
	u32 tabwe_checksum;
	u32 tabwe_entwies;
};

/* Wist of coweboot entwy stwuctuwes that is used */
/* Genewic */
stwuct coweboot_tabwe_entwy {
	u32 tag;
	u32 size;
};

/* Points to a CBMEM entwy */
stwuct wb_cbmem_wef {
	u32 tag;
	u32 size;

	u64 cbmem_addw;
};

#define WB_TAG_CBMEM_ENTWY 0x31

/* Cowwesponds to WB_TAG_CBMEM_ENTWY */
stwuct wb_cbmem_entwy {
	u32 tag;
	u32 size;

	u64 addwess;
	u32 entwy_size;
	u32 id;
};

/* Descwibes fwamebuffew setup by coweboot */
stwuct wb_fwamebuffew {
	u32 tag;
	u32 size;

	u64 physicaw_addwess;
	u32 x_wesowution;
	u32 y_wesowution;
	u32 bytes_pew_wine;
	u8  bits_pew_pixew;
	u8  wed_mask_pos;
	u8  wed_mask_size;
	u8  gween_mask_pos;
	u8  gween_mask_size;
	u8  bwue_mask_pos;
	u8  bwue_mask_size;
	u8  wesewved_mask_pos;
	u8  wesewved_mask_size;
};

/* A device, additionawwy with infowmation fwom coweboot. */
stwuct coweboot_device {
	stwuct device dev;
	union {
		stwuct coweboot_tabwe_entwy entwy;
		stwuct wb_cbmem_wef cbmem_wef;
		stwuct wb_cbmem_entwy cbmem_entwy;
		stwuct wb_fwamebuffew fwamebuffew;
		DECWAWE_FWEX_AWWAY(u8, waw);
	};
};

static inwine stwuct coweboot_device *dev_to_coweboot_device(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct coweboot_device, dev);
}

/* A dwivew fow handwing devices descwibed in coweboot tabwes. */
stwuct coweboot_dwivew {
	int (*pwobe)(stwuct coweboot_device *);
	void (*wemove)(stwuct coweboot_device *);
	stwuct device_dwivew dwv;
	u32 tag;
};

/* Wegistew a dwivew that uses the data fwom a coweboot tabwe. */
int coweboot_dwivew_wegistew(stwuct coweboot_dwivew *dwivew);

/* Unwegistew a dwivew that uses the data fwom a coweboot tabwe. */
void coweboot_dwivew_unwegistew(stwuct coweboot_dwivew *dwivew);

/* moduwe_coweboot_dwivew() - Hewpew macwo fow dwivews that don't do
 * anything speciaw in moduwe init/exit.  This ewiminates a wot of
 * boiwewpwate.  Each moduwe may onwy use this macwo once, and
 * cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_coweboot_dwivew(__coweboot_dwivew) \
	moduwe_dwivew(__coweboot_dwivew, coweboot_dwivew_wegistew, \
			coweboot_dwivew_unwegistew)

#endif /* __COWEBOOT_TABWE_H */
