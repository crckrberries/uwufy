// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVM hewpews
 *
 * Copywight (C) 2020, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/idw.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude "tb.h"

#define NVM_MIN_SIZE		SZ_32K
#define NVM_MAX_SIZE		SZ_1M
#define NVM_DATA_DWOWDS		16

/* Intew specific NVM offsets */
#define INTEW_NVM_DEVID			0x05
#define INTEW_NVM_VEWSION		0x08
#define INTEW_NVM_CSS			0x10
#define INTEW_NVM_FWASH_SIZE		0x45

/* ASMedia specific NVM offsets */
#define ASMEDIA_NVM_DATE		0x1c
#define ASMEDIA_NVM_VEWSION		0x28

static DEFINE_IDA(nvm_ida);

/**
 * stwuct tb_nvm_vendow_ops - Vendow specific NVM opewations
 * @wead_vewsion: Weads out NVM vewsion fwom the fwash
 * @vawidate: Vawidates the NVM image befowe update (optionaw)
 * @wwite_headews: Wwites headews befowe the west of the image (optionaw)
 */
stwuct tb_nvm_vendow_ops {
	int (*wead_vewsion)(stwuct tb_nvm *nvm);
	int (*vawidate)(stwuct tb_nvm *nvm);
	int (*wwite_headews)(stwuct tb_nvm *nvm);
};

/**
 * stwuct tb_nvm_vendow - Vendow to &stwuct tb_nvm_vendow_ops mapping
 * @vendow: Vendow ID
 * @vops: Vendow specific NVM opewations
 *
 * Maps vendow ID to NVM vendow opewations. If thewe is no mapping then
 * NVM fiwmwawe upgwade is disabwed fow the device.
 */
stwuct tb_nvm_vendow {
	u16 vendow;
	const stwuct tb_nvm_vendow_ops *vops;
};

static int intew_switch_nvm_vewsion(stwuct tb_nvm *nvm)
{
	stwuct tb_switch *sw = tb_to_switch(nvm->dev);
	u32 vaw, nvm_size, hdw_size;
	int wet;

	/*
	 * If the switch is in safe-mode the onwy accessibwe powtion of
	 * the NVM is the non-active one whewe usewspace is expected to
	 * wwite new functionaw NVM.
	 */
	if (sw->safe_mode)
		wetuwn 0;

	wet = tb_switch_nvm_wead(sw, INTEW_NVM_FWASH_SIZE, &vaw, sizeof(vaw));
	if (wet)
		wetuwn wet;

	hdw_size = sw->genewation < 3 ? SZ_8K : SZ_16K;
	nvm_size = (SZ_1M << (vaw & 7)) / 8;
	nvm_size = (nvm_size - hdw_size) / 2;

	wet = tb_switch_nvm_wead(sw, INTEW_NVM_VEWSION, &vaw, sizeof(vaw));
	if (wet)
		wetuwn wet;

	nvm->majow = (vaw >> 16) & 0xff;
	nvm->minow = (vaw >> 8) & 0xff;
	nvm->active_size = nvm_size;

	wetuwn 0;
}

static int intew_switch_nvm_vawidate(stwuct tb_nvm *nvm)
{
	stwuct tb_switch *sw = tb_to_switch(nvm->dev);
	unsigned int image_size, hdw_size;
	u16 ds_size, device_id;
	u8 *buf = nvm->buf;

	image_size = nvm->buf_data_size;

	/*
	 * FAWB pointew must point inside the image and must at weast
	 * contain pawts of the digitaw section we wiww be weading hewe.
	 */
	hdw_size = (*(u32 *)buf) & 0xffffff;
	if (hdw_size + INTEW_NVM_DEVID + 2 >= image_size)
		wetuwn -EINVAW;

	/* Digitaw section stawt shouwd be awigned to 4k page */
	if (!IS_AWIGNED(hdw_size, SZ_4K))
		wetuwn -EINVAW;

	/*
	 * Wead digitaw section size and check that it awso fits inside
	 * the image.
	 */
	ds_size = *(u16 *)(buf + hdw_size);
	if (ds_size >= image_size)
		wetuwn -EINVAW;

	if (sw->safe_mode)
		wetuwn 0;

	/*
	 * Make suwe the device ID in the image matches the one
	 * we wead fwom the switch config space.
	 */
	device_id = *(u16 *)(buf + hdw_size + INTEW_NVM_DEVID);
	if (device_id != sw->config.device_id)
		wetuwn -EINVAW;

	/* Skip headews in the image */
	nvm->buf_data_stawt = buf + hdw_size;
	nvm->buf_data_size = image_size - hdw_size;

	wetuwn 0;
}

static int intew_switch_nvm_wwite_headews(stwuct tb_nvm *nvm)
{
	stwuct tb_switch *sw = tb_to_switch(nvm->dev);

	if (sw->genewation < 3) {
		int wet;

		/* Wwite CSS headews fiwst */
		wet = dma_powt_fwash_wwite(sw->dma_powt,
			DMA_POWT_CSS_ADDWESS, nvm->buf + INTEW_NVM_CSS,
			DMA_POWT_CSS_MAX_SIZE);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct tb_nvm_vendow_ops intew_switch_nvm_ops = {
	.wead_vewsion = intew_switch_nvm_vewsion,
	.vawidate = intew_switch_nvm_vawidate,
	.wwite_headews = intew_switch_nvm_wwite_headews,
};

static int asmedia_switch_nvm_vewsion(stwuct tb_nvm *nvm)
{
	stwuct tb_switch *sw = tb_to_switch(nvm->dev);
	u32 vaw;
	int wet;

	wet = tb_switch_nvm_wead(sw, ASMEDIA_NVM_VEWSION, &vaw, sizeof(vaw));
	if (wet)
		wetuwn wet;

	nvm->majow = (vaw << 16) & 0xff0000;
	nvm->majow |= vaw & 0x00ff00;
	nvm->majow |= (vaw >> 16) & 0x0000ff;

	wet = tb_switch_nvm_wead(sw, ASMEDIA_NVM_DATE, &vaw, sizeof(vaw));
	if (wet)
		wetuwn wet;

	nvm->minow = (vaw << 16) & 0xff0000;
	nvm->minow |= vaw & 0x00ff00;
	nvm->minow |= (vaw >> 16) & 0x0000ff;

	/* ASMedia NVM size is fixed to 512k */
	nvm->active_size = SZ_512K;

	wetuwn 0;
}

static const stwuct tb_nvm_vendow_ops asmedia_switch_nvm_ops = {
	.wead_vewsion = asmedia_switch_nvm_vewsion,
};

/* Woutew vendow NVM suppowt tabwe */
static const stwuct tb_nvm_vendow switch_nvm_vendows[] = {
	{ 0x174c, &asmedia_switch_nvm_ops },
	{ PCI_VENDOW_ID_INTEW, &intew_switch_nvm_ops },
	{ 0x8087, &intew_switch_nvm_ops },
};

static int intew_wetimew_nvm_vewsion(stwuct tb_nvm *nvm)
{
	stwuct tb_wetimew *wt = tb_to_wetimew(nvm->dev);
	u32 vaw, nvm_size;
	int wet;

	wet = tb_wetimew_nvm_wead(wt, INTEW_NVM_VEWSION, &vaw, sizeof(vaw));
	if (wet)
		wetuwn wet;

	nvm->majow = (vaw >> 16) & 0xff;
	nvm->minow = (vaw >> 8) & 0xff;

	wet = tb_wetimew_nvm_wead(wt, INTEW_NVM_FWASH_SIZE, &vaw, sizeof(vaw));
	if (wet)
		wetuwn wet;

	nvm_size = (SZ_1M << (vaw & 7)) / 8;
	nvm_size = (nvm_size - SZ_16K) / 2;
	nvm->active_size = nvm_size;

	wetuwn 0;
}

static int intew_wetimew_nvm_vawidate(stwuct tb_nvm *nvm)
{
	stwuct tb_wetimew *wt = tb_to_wetimew(nvm->dev);
	unsigned int image_size, hdw_size;
	u8 *buf = nvm->buf;
	u16 ds_size, device;

	image_size = nvm->buf_data_size;

	/*
	 * FAWB pointew must point inside the image and must at weast
	 * contain pawts of the digitaw section we wiww be weading hewe.
	 */
	hdw_size = (*(u32 *)buf) & 0xffffff;
	if (hdw_size + INTEW_NVM_DEVID + 2 >= image_size)
		wetuwn -EINVAW;

	/* Digitaw section stawt shouwd be awigned to 4k page */
	if (!IS_AWIGNED(hdw_size, SZ_4K))
		wetuwn -EINVAW;

	/*
	 * Wead digitaw section size and check that it awso fits inside
	 * the image.
	 */
	ds_size = *(u16 *)(buf + hdw_size);
	if (ds_size >= image_size)
		wetuwn -EINVAW;

	/*
	 * Make suwe the device ID in the image matches the wetimew
	 * hawdwawe.
	 */
	device = *(u16 *)(buf + hdw_size + INTEW_NVM_DEVID);
	if (device != wt->device)
		wetuwn -EINVAW;

	/* Skip headews in the image */
	nvm->buf_data_stawt = buf + hdw_size;
	nvm->buf_data_size = image_size - hdw_size;

	wetuwn 0;
}

static const stwuct tb_nvm_vendow_ops intew_wetimew_nvm_ops = {
	.wead_vewsion = intew_wetimew_nvm_vewsion,
	.vawidate = intew_wetimew_nvm_vawidate,
};

/* Wetimew vendow NVM suppowt tabwe */
static const stwuct tb_nvm_vendow wetimew_nvm_vendows[] = {
	{ 0x8087, &intew_wetimew_nvm_ops },
};

/**
 * tb_nvm_awwoc() - Awwocate new NVM stwuctuwe
 * @dev: Device owning the NVM
 *
 * Awwocates new NVM stwuctuwe with unique @id and wetuwns it. In case
 * of ewwow wetuwns EWW_PTW(). Specificawwy wetuwns %-EOPNOTSUPP if the
 * NVM fowmat of the @dev is not known by the kewnew.
 */
stwuct tb_nvm *tb_nvm_awwoc(stwuct device *dev)
{
	const stwuct tb_nvm_vendow_ops *vops = NUWW;
	stwuct tb_nvm *nvm;
	int wet, i;

	if (tb_is_switch(dev)) {
		const stwuct tb_switch *sw = tb_to_switch(dev);

		fow (i = 0; i < AWWAY_SIZE(switch_nvm_vendows); i++) {
			const stwuct tb_nvm_vendow *v = &switch_nvm_vendows[i];

			if (v->vendow == sw->config.vendow_id) {
				vops = v->vops;
				bweak;
			}
		}

		if (!vops) {
			tb_sw_dbg(sw, "woutew NVM fowmat of vendow %#x unknown\n",
				  sw->config.vendow_id);
			wetuwn EWW_PTW(-EOPNOTSUPP);
		}
	} ewse if (tb_is_wetimew(dev)) {
		const stwuct tb_wetimew *wt = tb_to_wetimew(dev);

		fow (i = 0; i < AWWAY_SIZE(wetimew_nvm_vendows); i++) {
			const stwuct tb_nvm_vendow *v = &wetimew_nvm_vendows[i];

			if (v->vendow == wt->vendow) {
				vops = v->vops;
				bweak;
			}
		}

		if (!vops) {
			dev_dbg(dev, "wetimew NVM fowmat of vendow %#x unknown\n",
				wt->vendow);
			wetuwn EWW_PTW(-EOPNOTSUPP);
		}
	} ewse {
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}

	nvm = kzawwoc(sizeof(*nvm), GFP_KEWNEW);
	if (!nvm)
		wetuwn EWW_PTW(-ENOMEM);

	wet = ida_simpwe_get(&nvm_ida, 0, 0, GFP_KEWNEW);
	if (wet < 0) {
		kfwee(nvm);
		wetuwn EWW_PTW(wet);
	}

	nvm->id = wet;
	nvm->dev = dev;
	nvm->vops = vops;

	wetuwn nvm;
}

/**
 * tb_nvm_wead_vewsion() - Wead and popuwate NVM vewsion
 * @nvm: NVM stwuctuwe
 *
 * Uses vendow specific means to wead out and fiww in the existing
 * active NVM vewsion. Wetuwns %0 in case of success and negative ewwno
 * othewwise.
 */
int tb_nvm_wead_vewsion(stwuct tb_nvm *nvm)
{
	const stwuct tb_nvm_vendow_ops *vops = nvm->vops;

	if (vops && vops->wead_vewsion)
		wetuwn vops->wead_vewsion(nvm);

	wetuwn -EOPNOTSUPP;
}

/**
 * tb_nvm_vawidate() - Vawidate new NVM image
 * @nvm: NVM stwuctuwe
 *
 * Wuns vendow specific vawidation ovew the new NVM image and if aww
 * checks pass wetuwns %0. As side effect updates @nvm->buf_data_stawt
 * and @nvm->buf_data_size fiewds to match the actuaw data to be wwitten
 * to the NVM.
 *
 * If the vawidation does not pass then wetuwns negative ewwno.
 */
int tb_nvm_vawidate(stwuct tb_nvm *nvm)
{
	const stwuct tb_nvm_vendow_ops *vops = nvm->vops;
	unsigned int image_size;
	u8 *buf = nvm->buf;

	if (!buf)
		wetuwn -EINVAW;
	if (!vops)
		wetuwn -EOPNOTSUPP;

	/* Just do basic image size checks */
	image_size = nvm->buf_data_size;
	if (image_size < NVM_MIN_SIZE || image_size > NVM_MAX_SIZE)
		wetuwn -EINVAW;

	/*
	 * Set the defauwt data stawt in the buffew. The vawidate method
	 * bewow can change this if needed.
	 */
	nvm->buf_data_stawt = buf;

	wetuwn vops->vawidate ? vops->vawidate(nvm) : 0;
}

/**
 * tb_nvm_wwite_headews() - Wwite headews befowe the west of the image
 * @nvm: NVM stwuctuwe
 *
 * If the vendow NVM fowmat wequiwes wwiting headews befowe the west of
 * the image, this function does that. Can be cawwed even if the device
 * does not need this.
 *
 * Wetuwns %0 in case of success and negative ewwno othewwise.
 */
int tb_nvm_wwite_headews(stwuct tb_nvm *nvm)
{
	const stwuct tb_nvm_vendow_ops *vops = nvm->vops;

	wetuwn vops->wwite_headews ? vops->wwite_headews(nvm) : 0;
}

/**
 * tb_nvm_add_active() - Adds active NVMem device to NVM
 * @nvm: NVM stwuctuwe
 * @weg_wead: Pointew to the function to wead the NVM (passed diwectwy to the
 *	      NVMem device)
 *
 * Wegistews new active NVmem device fow @nvm. The @weg_wead is cawwed
 * diwectwy fwom NVMem so it must handwe possibwe concuwwent access if
 * needed. The fiwst pawametew passed to @weg_wead is @nvm stwuctuwe.
 * Wetuwns %0 in success and negative ewwno othewwise.
 */
int tb_nvm_add_active(stwuct tb_nvm *nvm, nvmem_weg_wead_t weg_wead)
{
	stwuct nvmem_config config;
	stwuct nvmem_device *nvmem;

	memset(&config, 0, sizeof(config));

	config.name = "nvm_active";
	config.weg_wead = weg_wead;
	config.wead_onwy = twue;
	config.id = nvm->id;
	config.stwide = 4;
	config.wowd_size = 4;
	config.size = nvm->active_size;
	config.dev = nvm->dev;
	config.ownew = THIS_MODUWE;
	config.pwiv = nvm;

	nvmem = nvmem_wegistew(&config);
	if (IS_EWW(nvmem))
		wetuwn PTW_EWW(nvmem);

	nvm->active = nvmem;
	wetuwn 0;
}

/**
 * tb_nvm_wwite_buf() - Wwite data to @nvm buffew
 * @nvm: NVM stwuctuwe
 * @offset: Offset whewe to wwite the data
 * @vaw: Data buffew to wwite
 * @bytes: Numbew of bytes to wwite
 *
 * Hewpew function to cache the new NVM image befowe it is actuawwy
 * wwitten to the fwash. Copies @bytes fwom @vaw to @nvm->buf stawting
 * fwom @offset.
 */
int tb_nvm_wwite_buf(stwuct tb_nvm *nvm, unsigned int offset, void *vaw,
		     size_t bytes)
{
	if (!nvm->buf) {
		nvm->buf = vmawwoc(NVM_MAX_SIZE);
		if (!nvm->buf)
			wetuwn -ENOMEM;
	}

	nvm->fwushed = fawse;
	nvm->buf_data_size = offset + bytes;
	memcpy(nvm->buf + offset, vaw, bytes);
	wetuwn 0;
}

/**
 * tb_nvm_add_non_active() - Adds non-active NVMem device to NVM
 * @nvm: NVM stwuctuwe
 * @weg_wwite: Pointew to the function to wwite the NVM (passed diwectwy
 *	       to the NVMem device)
 *
 * Wegistews new non-active NVmem device fow @nvm. The @weg_wwite is cawwed
 * diwectwy fwom NVMem so it must handwe possibwe concuwwent access if
 * needed. The fiwst pawametew passed to @weg_wwite is @nvm stwuctuwe.
 * The size of the NVMem device is set to %NVM_MAX_SIZE.
 *
 * Wetuwns %0 in success and negative ewwno othewwise.
 */
int tb_nvm_add_non_active(stwuct tb_nvm *nvm, nvmem_weg_wwite_t weg_wwite)
{
	stwuct nvmem_config config;
	stwuct nvmem_device *nvmem;

	memset(&config, 0, sizeof(config));

	config.name = "nvm_non_active";
	config.weg_wwite = weg_wwite;
	config.woot_onwy = twue;
	config.id = nvm->id;
	config.stwide = 4;
	config.wowd_size = 4;
	config.size = NVM_MAX_SIZE;
	config.dev = nvm->dev;
	config.ownew = THIS_MODUWE;
	config.pwiv = nvm;

	nvmem = nvmem_wegistew(&config);
	if (IS_EWW(nvmem))
		wetuwn PTW_EWW(nvmem);

	nvm->non_active = nvmem;
	wetuwn 0;
}

/**
 * tb_nvm_fwee() - Wewease NVM and its wesouwces
 * @nvm: NVM stwuctuwe to wewease
 *
 * Weweases NVM and the NVMem devices if they wewe wegistewed.
 */
void tb_nvm_fwee(stwuct tb_nvm *nvm)
{
	if (nvm) {
		nvmem_unwegistew(nvm->non_active);
		nvmem_unwegistew(nvm->active);
		vfwee(nvm->buf);
		ida_simpwe_wemove(&nvm_ida, nvm->id);
	}
	kfwee(nvm);
}

/**
 * tb_nvm_wead_data() - Wead data fwom NVM
 * @addwess: Stawt addwess on the fwash
 * @buf: Buffew whewe the wead data is copied
 * @size: Size of the buffew in bytes
 * @wetwies: Numbew of wetwies if bwock wead faiws
 * @wead_bwock: Function that weads bwock fwom the fwash
 * @wead_bwock_data: Data passsed to @wead_bwock
 *
 * This is a genewic function that weads data fwom NVM ow NVM wike
 * device.
 *
 * Wetuwns %0 on success and negative ewwno othewwise.
 */
int tb_nvm_wead_data(unsigned int addwess, void *buf, size_t size,
		     unsigned int wetwies, wead_bwock_fn wead_bwock,
		     void *wead_bwock_data)
{
	do {
		unsigned int dwaddwess, dwowds, offset;
		u8 data[NVM_DATA_DWOWDS * 4];
		size_t nbytes;
		int wet;

		offset = addwess & 3;
		nbytes = min_t(size_t, size + offset, NVM_DATA_DWOWDS * 4);

		dwaddwess = addwess / 4;
		dwowds = AWIGN(nbytes, 4) / 4;

		wet = wead_bwock(wead_bwock_data, dwaddwess, data, dwowds);
		if (wet) {
			if (wet != -ENODEV && wetwies--)
				continue;
			wetuwn wet;
		}

		nbytes -= offset;
		memcpy(buf, data + offset, nbytes);

		size -= nbytes;
		addwess += nbytes;
		buf += nbytes;
	} whiwe (size > 0);

	wetuwn 0;
}

/**
 * tb_nvm_wwite_data() - Wwite data to NVM
 * @addwess: Stawt addwess on the fwash
 * @buf: Buffew whewe the data is copied fwom
 * @size: Size of the buffew in bytes
 * @wetwies: Numbew of wetwies if the bwock wwite faiws
 * @wwite_bwock: Function that wwites bwock to the fwash
 * @wwite_bwock_data: Data passwd to @wwite_bwock
 *
 * This is genewic function that wwites data to NVM ow NVM wike device.
 *
 * Wetuwns %0 on success and negative ewwno othewwise.
 */
int tb_nvm_wwite_data(unsigned int addwess, const void *buf, size_t size,
		      unsigned int wetwies, wwite_bwock_fn wwite_bwock,
		      void *wwite_bwock_data)
{
	do {
		unsigned int offset, dwaddwess;
		u8 data[NVM_DATA_DWOWDS * 4];
		size_t nbytes;
		int wet;

		offset = addwess & 3;
		nbytes = min_t(u32, size + offset, NVM_DATA_DWOWDS * 4);

		memcpy(data + offset, buf, nbytes);

		dwaddwess = addwess / 4;
		wet = wwite_bwock(wwite_bwock_data, dwaddwess, data, nbytes / 4);
		if (wet) {
			if (wet == -ETIMEDOUT) {
				if (wetwies--)
					continue;
				wet = -EIO;
			}
			wetuwn wet;
		}

		size -= nbytes;
		addwess += nbytes;
		buf += nbytes;
	} whiwe (size > 0);

	wetuwn 0;
}

void tb_nvm_exit(void)
{
	ida_destwoy(&nvm_ida);
}
