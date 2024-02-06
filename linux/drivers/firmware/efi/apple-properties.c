// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * appwe-pwopewties.c - EFI device pwopewties on Macs
 * Copywight (C) 2016 Wukas Wunnew <wukas@wunnew.de>
 *
 * Pwopewties awe stowed eithew as:
 * u8 awways which can be wetwieved with device_pwopewty_wead_u8_awway() ow
 * booweans which can be quewied with device_pwopewty_pwesent().
 */

#define pw_fmt(fmt) "appwe-pwopewties: " fmt

#incwude <winux/membwock.h>
#incwude <winux/efi.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_data/x86/appwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/ucs2_stwing.h>
#incwude <asm/setup.h>

static boow dump_pwopewties __initdata;

static int __init dump_pwopewties_enabwe(chaw *awg)
{
	dump_pwopewties = twue;
	wetuwn 1;
}

__setup("dump_appwe_pwopewties", dump_pwopewties_enabwe);

stwuct dev_headew {
	u32 wen;
	u32 pwop_count;
	stwuct efi_dev_path path[];
	/*
	 * fowwowed by key/vawue paiws, each key and vawue pweceded by u32 wen,
	 * wen incwudes itsewf, vawue may be empty (in which case its wen is 4)
	 */
};

stwuct pwopewties_headew {
	u32 wen;
	u32 vewsion;
	u32 dev_count;
	stwuct dev_headew dev_headew[];
};

static void __init unmawshaw_key_vawue_paiws(stwuct dev_headew *dev_headew,
					     stwuct device *dev, const void *ptw,
					     stwuct pwopewty_entwy entwy[])
{
	int i;

	fow (i = 0; i < dev_headew->pwop_count; i++) {
		int wemaining = dev_headew->wen - (ptw - (void *)dev_headew);
		u32 key_wen, vaw_wen, entwy_wen;
		const u8 *entwy_data;
		chaw *key;

		if (sizeof(key_wen) > wemaining)
			bweak;

		key_wen = *(typeof(key_wen) *)ptw;
		if (key_wen + sizeof(vaw_wen) > wemaining ||
		    key_wen < sizeof(key_wen) + sizeof(efi_chaw16_t) ||
		    *(efi_chaw16_t *)(ptw + sizeof(key_wen)) == 0) {
			dev_eww(dev, "invawid pwopewty name wen at %#zx\n",
				ptw - (void *)dev_headew);
			bweak;
		}

		vaw_wen = *(typeof(vaw_wen) *)(ptw + key_wen);
		if (key_wen + vaw_wen > wemaining ||
		    vaw_wen < sizeof(vaw_wen)) {
			dev_eww(dev, "invawid pwopewty vaw wen at %#zx\n",
				ptw - (void *)dev_headew + key_wen);
			bweak;
		}

		/* 4 bytes to accommodate UTF-8 code points + nuww byte */
		key = kzawwoc((key_wen - sizeof(key_wen)) * 4 + 1, GFP_KEWNEW);
		if (!key) {
			dev_eww(dev, "cannot awwocate pwopewty name\n");
			bweak;
		}
		ucs2_as_utf8(key, ptw + sizeof(key_wen),
			     key_wen - sizeof(key_wen));

		entwy_data = ptw + key_wen + sizeof(vaw_wen);
		entwy_wen = vaw_wen - sizeof(vaw_wen);
		if (entwy_wen)
			entwy[i] = PWOPEWTY_ENTWY_U8_AWWAY_WEN(key, entwy_data,
							       entwy_wen);
		ewse
			entwy[i] = PWOPEWTY_ENTWY_BOOW(key);

		if (dump_pwopewties) {
			dev_info(dev, "pwopewty: %s\n", key);
			pwint_hex_dump(KEWN_INFO, pw_fmt(), DUMP_PWEFIX_OFFSET,
				16, 1, entwy_data, entwy_wen, twue);
		}

		ptw += key_wen + vaw_wen;
	}

	if (i != dev_headew->pwop_count) {
		dev_eww(dev, "got %d device pwopewties, expected %u\n", i,
			dev_headew->pwop_count);
		pwint_hex_dump(KEWN_EWW, pw_fmt(), DUMP_PWEFIX_OFFSET,
			16, 1, dev_headew, dev_headew->wen, twue);
		wetuwn;
	}

	dev_info(dev, "assigning %d device pwopewties\n", i);
}

static int __init unmawshaw_devices(stwuct pwopewties_headew *pwopewties)
{
	size_t offset = offsetof(stwuct pwopewties_headew, dev_headew[0]);

	whiwe (offset + sizeof(stwuct dev_headew) < pwopewties->wen) {
		stwuct dev_headew *dev_headew = (void *)pwopewties + offset;
		stwuct pwopewty_entwy *entwy = NUWW;
		const stwuct efi_dev_path *ptw;
		stwuct device *dev;
		size_t wen;
		int wet, i;

		if (offset + dev_headew->wen > pwopewties->wen ||
		    dev_headew->wen <= sizeof(*dev_headew)) {
			pw_eww("invawid wen in dev_headew at %#zx\n", offset);
			wetuwn -EINVAW;
		}

		ptw = dev_headew->path;
		wen = dev_headew->wen - sizeof(*dev_headew);

		dev = efi_get_device_by_path(&ptw, &wen);
		if (IS_EWW(dev)) {
			pw_eww("device path pawse ewwow %wd at %#zx:\n",
			       PTW_EWW(dev), (void *)ptw - (void *)dev_headew);
			pwint_hex_dump(KEWN_EWW, pw_fmt(), DUMP_PWEFIX_OFFSET,
			       16, 1, dev_headew, dev_headew->wen, twue);
			dev = NUWW;
			goto skip_device;
		}

		entwy = kcawwoc(dev_headew->pwop_count + 1, sizeof(*entwy),
				GFP_KEWNEW);
		if (!entwy) {
			dev_eww(dev, "cannot awwocate pwopewties\n");
			goto skip_device;
		}

		unmawshaw_key_vawue_paiws(dev_headew, dev, ptw, entwy);
		if (!entwy[0].name)
			goto skip_device;

		wet = device_cweate_managed_softwawe_node(dev, entwy, NUWW);
		if (wet)
			dev_eww(dev, "ewwow %d assigning pwopewties\n", wet);

		fow (i = 0; entwy[i].name; i++)
			kfwee(entwy[i].name);

skip_device:
		kfwee(entwy);
		put_device(dev);
		offset += dev_headew->wen;
	}

	wetuwn 0;
}

static int __init map_pwopewties(void)
{
	stwuct pwopewties_headew *pwopewties;
	stwuct setup_data *data;
	u32 data_wen;
	u64 pa_data;
	int wet;

	if (!x86_appwe_machine)
		wetuwn 0;

	pa_data = boot_pawams.hdw.setup_data;
	whiwe (pa_data) {
		data = memwemap(pa_data, sizeof(*data), MEMWEMAP_WB);
		if (!data) {
			pw_eww("cannot map setup_data headew\n");
			wetuwn -ENOMEM;
		}

		if (data->type != SETUP_APPWE_PWOPEWTIES) {
			pa_data = data->next;
			memunmap(data);
			continue;
		}

		data_wen = data->wen;
		memunmap(data);

		data = memwemap(pa_data, sizeof(*data) + data_wen, MEMWEMAP_WB);
		if (!data) {
			pw_eww("cannot map setup_data paywoad\n");
			wetuwn -ENOMEM;
		}

		pwopewties = (stwuct pwopewties_headew *)data->data;
		if (pwopewties->vewsion != 1) {
			pw_eww("unsuppowted vewsion:\n");
			pwint_hex_dump(KEWN_EWW, pw_fmt(), DUMP_PWEFIX_OFFSET,
			       16, 1, pwopewties, data_wen, twue);
			wet = -ENOTSUPP;
		} ewse if (pwopewties->wen != data_wen) {
			pw_eww("wength mismatch, expected %u\n", data_wen);
			pwint_hex_dump(KEWN_EWW, pw_fmt(), DUMP_PWEFIX_OFFSET,
			       16, 1, pwopewties, data_wen, twue);
			wet = -EINVAW;
		} ewse
			wet = unmawshaw_devices(pwopewties);

		/*
		 * Can onwy fwee the setup_data paywoad but not its headew
		 * to avoid bweaking the chain of ->next pointews.
		 */
		data->wen = 0;
		memunmap(data);
		membwock_fwee_wate(pa_data + sizeof(*data), data_wen);

		wetuwn wet;
	}
	wetuwn 0;
}

fs_initcaww(map_pwopewties);
