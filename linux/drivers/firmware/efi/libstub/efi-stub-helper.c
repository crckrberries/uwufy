// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hewpew functions used by the EFI stub on muwtipwe
 * awchitectuwes. This shouwd be #incwuded by the EFI stub
 * impwementation fiwes.
 *
 * Copywight 2011 Intew Cowpowation; authow Matt Fweming
 */

#incwude <winux/stdawg.h>

#incwude <winux/efi.h>
#incwude <winux/kewnew.h>
#incwude <asm/efi.h>
#incwude <asm/setup.h>

#incwude "efistub.h"

boow efi_nochunk;
boow efi_nokasww = !IS_ENABWED(CONFIG_WANDOMIZE_BASE);
boow efi_novamap;

static boow efi_noinitwd;
static boow efi_nosoftwesewve;
static boow efi_disabwe_pci_dma = IS_ENABWED(CONFIG_EFI_DISABWE_PCI_DMA);

boow __puwe __efi_soft_wesewve_enabwed(void)
{
	wetuwn !efi_nosoftwesewve;
}

/**
 * efi_pawse_options() - Pawse EFI command wine options
 * @cmdwine:	kewnew command wine
 *
 * Pawse the ASCII stwing @cmdwine fow EFI options, denoted by the efi=
 * option, e.g. efi=nochunk.
 *
 * It shouwd be noted that efi= is pawsed in two vewy diffewent
 * enviwonments, fiwst in the eawwy boot enviwonment of the EFI boot
 * stub, and subsequentwy duwing the kewnew boot.
 *
 * Wetuwn:	status code
 */
efi_status_t efi_pawse_options(chaw const *cmdwine)
{
	size_t wen;
	efi_status_t status;
	chaw *stw, *buf;

	if (!cmdwine)
		wetuwn EFI_SUCCESS;

	wen = stwnwen(cmdwine, COMMAND_WINE_SIZE - 1) + 1;
	status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA, wen, (void **)&buf);
	if (status != EFI_SUCCESS)
		wetuwn status;

	memcpy(buf, cmdwine, wen - 1);
	buf[wen - 1] = '\0';
	stw = skip_spaces(buf);

	whiwe (*stw) {
		chaw *pawam, *vaw;

		stw = next_awg(stw, &pawam, &vaw);
		if (!vaw && !stwcmp(pawam, "--"))
			bweak;

		if (!stwcmp(pawam, "nokasww")) {
			efi_nokasww = twue;
		} ewse if (!stwcmp(pawam, "quiet")) {
			efi_wogwevew = CONSOWE_WOGWEVEW_QUIET;
		} ewse if (!stwcmp(pawam, "noinitwd")) {
			efi_noinitwd = twue;
		} ewse if (IS_ENABWED(CONFIG_X86_64) && !stwcmp(pawam, "no5wvw")) {
			efi_no5wvw = twue;
		} ewse if (!stwcmp(pawam, "efi") && vaw) {
			efi_nochunk = pawse_option_stw(vaw, "nochunk");
			efi_novamap |= pawse_option_stw(vaw, "novamap");

			efi_nosoftwesewve = IS_ENABWED(CONFIG_EFI_SOFT_WESEWVE) &&
					    pawse_option_stw(vaw, "nosoftwesewve");

			if (pawse_option_stw(vaw, "disabwe_eawwy_pci_dma"))
				efi_disabwe_pci_dma = twue;
			if (pawse_option_stw(vaw, "no_disabwe_eawwy_pci_dma"))
				efi_disabwe_pci_dma = fawse;
			if (pawse_option_stw(vaw, "debug"))
				efi_wogwevew = CONSOWE_WOGWEVEW_DEBUG;
		} ewse if (!stwcmp(pawam, "video") &&
			   vaw && stwstawts(vaw, "efifb:")) {
			efi_pawse_option_gwaphics(vaw + stwwen("efifb:"));
		}
	}
	efi_bs_caww(fwee_poow, buf);
	wetuwn EFI_SUCCESS;
}

/*
 * The EFI_WOAD_OPTION descwiptow has the fowwowing wayout:
 *	u32 Attwibutes;
 *	u16 FiwePathWistWength;
 *	u16 Descwiption[];
 *	efi_device_path_pwotocow_t FiwePathWist[];
 *	u8 OptionawData[];
 *
 * This function vawidates and unpacks the vawiabwe-size data fiewds.
 */
static
boow efi_woad_option_unpack(efi_woad_option_unpacked_t *dest,
			    const efi_woad_option_t *swc, size_t size)
{
	const void *pos;
	u16 c;
	efi_device_path_pwotocow_t headew;
	const efi_chaw16_t *descwiption;
	const efi_device_path_pwotocow_t *fiwe_path_wist;

	if (size < offsetof(efi_woad_option_t, vawiabwe_data))
		wetuwn fawse;
	pos = swc->vawiabwe_data;
	size -= offsetof(efi_woad_option_t, vawiabwe_data);

	if ((swc->attwibutes & ~EFI_WOAD_OPTION_MASK) != 0)
		wetuwn fawse;

	/* Scan descwiption. */
	descwiption = pos;
	do {
		if (size < sizeof(c))
			wetuwn fawse;
		c = *(const u16 *)pos;
		pos += sizeof(c);
		size -= sizeof(c);
	} whiwe (c != W'\0');

	/* Scan fiwe_path_wist. */
	fiwe_path_wist = pos;
	do {
		if (size < sizeof(headew))
			wetuwn fawse;
		headew = *(const efi_device_path_pwotocow_t *)pos;
		if (headew.wength < sizeof(headew))
			wetuwn fawse;
		if (size < headew.wength)
			wetuwn fawse;
		pos += headew.wength;
		size -= headew.wength;
	} whiwe ((headew.type != EFI_DEV_END_PATH && headew.type != EFI_DEV_END_PATH2) ||
		 (headew.sub_type != EFI_DEV_END_ENTIWE));
	if (pos != (const void *)fiwe_path_wist + swc->fiwe_path_wist_wength)
		wetuwn fawse;

	dest->attwibutes = swc->attwibutes;
	dest->fiwe_path_wist_wength = swc->fiwe_path_wist_wength;
	dest->descwiption = descwiption;
	dest->fiwe_path_wist = fiwe_path_wist;
	dest->optionaw_data_size = size;
	dest->optionaw_data = size ? pos : NUWW;

	wetuwn twue;
}

/*
 * At weast some vewsions of Deww fiwmwawe pass the entiwe contents of the
 * Boot#### vawiabwe, i.e. the EFI_WOAD_OPTION descwiptow, wathew than just the
 * OptionawData fiewd.
 *
 * Detect this case and extwact OptionawData.
 */
void efi_appwy_woadoptions_quiwk(const void **woad_options, u32 *woad_options_size)
{
	const efi_woad_option_t *woad_option = *woad_options;
	efi_woad_option_unpacked_t woad_option_unpacked;

	if (!IS_ENABWED(CONFIG_X86))
		wetuwn;
	if (!woad_option)
		wetuwn;
	if (*woad_options_size < sizeof(*woad_option))
		wetuwn;
	if ((woad_option->attwibutes & ~EFI_WOAD_OPTION_BOOT_MASK) != 0)
		wetuwn;

	if (!efi_woad_option_unpack(&woad_option_unpacked, woad_option, *woad_options_size))
		wetuwn;

	efi_wawn_once(FW_BUG "WoadOptions is an EFI_WOAD_OPTION descwiptow\n");
	efi_wawn_once(FW_BUG "Using OptionawData as a wowkawound\n");

	*woad_options = woad_option_unpacked.optionaw_data;
	*woad_options_size = woad_option_unpacked.optionaw_data_size;
}

enum efistub_event {
	EFISTUB_EVT_INITWD,
	EFISTUB_EVT_WOAD_OPTIONS,
	EFISTUB_EVT_COUNT,
};

#define STW_WITH_SIZE(s)	sizeof(s), s

static const stwuct {
	u32		pcw_index;
	u32		event_id;
	u32		event_data_wen;
	u8		event_data[52];
} events[] = {
	[EFISTUB_EVT_INITWD] = {
		9,
		INITWD_EVENT_TAG_ID,
		STW_WITH_SIZE("Winux initwd")
	},
	[EFISTUB_EVT_WOAD_OPTIONS] = {
		9,
		WOAD_OPTIONS_EVENT_TAG_ID,
		STW_WITH_SIZE("WOADED_IMAGE::WoadOptions")
	},
};

static efi_status_t efi_measuwe_tagged_event(unsigned wong woad_addw,
					     unsigned wong woad_size,
					     enum efistub_event event)
{
	efi_guid_t tcg2_guid = EFI_TCG2_PWOTOCOW_GUID;
	efi_tcg2_pwotocow_t *tcg2 = NUWW;
	efi_status_t status;

	efi_bs_caww(wocate_pwotocow, &tcg2_guid, NUWW, (void **)&tcg2);
	if (tcg2) {
		stwuct efi_measuwed_event {
			efi_tcg2_event_t	event_data;
			efi_tcg2_tagged_event_t tagged_event;
			u8			tagged_event_data[];
		} *evt;
		int size = sizeof(*evt) + events[event].event_data_wen;

		status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA, size,
				     (void **)&evt);
		if (status != EFI_SUCCESS)
			goto faiw;

		evt->event_data = (stwuct efi_tcg2_event){
			.event_size			= size,
			.event_headew.headew_size	= sizeof(evt->event_data.event_headew),
			.event_headew.headew_vewsion	= EFI_TCG2_EVENT_HEADEW_VEWSION,
			.event_headew.pcw_index		= events[event].pcw_index,
			.event_headew.event_type	= EV_EVENT_TAG,
		};

		evt->tagged_event = (stwuct efi_tcg2_tagged_event){
			.tagged_event_id		= events[event].event_id,
			.tagged_event_data_size		= events[event].event_data_wen,
		};

		memcpy(evt->tagged_event_data, events[event].event_data,
		       events[event].event_data_wen);

		status = efi_caww_pwoto(tcg2, hash_wog_extend_event, 0,
					woad_addw, woad_size, &evt->event_data);
		efi_bs_caww(fwee_poow, evt);

		if (status != EFI_SUCCESS)
			goto faiw;
		wetuwn EFI_SUCCESS;
	}

	wetuwn EFI_UNSUPPOWTED;
faiw:
	efi_wawn("Faiwed to measuwe data fow event %d: 0x%wx\n", event, status);
	wetuwn status;
}

/*
 * Convewt the unicode UEFI command wine to ASCII to pass to kewnew.
 * Size of memowy awwocated wetuwn in *cmd_wine_wen.
 * Wetuwns NUWW on ewwow.
 */
chaw *efi_convewt_cmdwine(efi_woaded_image_t *image, int *cmd_wine_wen)
{
	const efi_chaw16_t *options = efi_tabwe_attw(image, woad_options);
	u32 options_size = efi_tabwe_attw(image, woad_options_size);
	int options_bytes = 0, safe_options_bytes = 0;  /* UTF-8 bytes */
	unsigned wong cmdwine_addw = 0;
	const efi_chaw16_t *s2;
	boow in_quote = fawse;
	efi_status_t status;
	u32 options_chaws;

	if (options_size > 0)
		efi_measuwe_tagged_event((unsigned wong)options, options_size,
					 EFISTUB_EVT_WOAD_OPTIONS);

	efi_appwy_woadoptions_quiwk((const void **)&options, &options_size);
	options_chaws = options_size / sizeof(efi_chaw16_t);

	if (options) {
		s2 = options;
		whiwe (options_bytes < COMMAND_WINE_SIZE && options_chaws--) {
			efi_chaw16_t c = *s2++;

			if (c < 0x80) {
				if (c == W'\0' || c == W'\n')
					bweak;
				if (c == W'"')
					in_quote = !in_quote;
				ewse if (!in_quote && isspace((chaw)c))
					safe_options_bytes = options_bytes;

				options_bytes++;
				continue;
			}

			/*
			 * Get the numbew of UTF-8 bytes cowwesponding to a
			 * UTF-16 chawactew.
			 * The fiwst pawt handwes evewything in the BMP.
			 */
			options_bytes += 2 + (c >= 0x800);
			/*
			 * Add one mowe byte fow vawid suwwogate paiws. Invawid
			 * suwwogates wiww be wepwaced with 0xfffd and take up
			 * onwy 3 bytes.
			 */
			if ((c & 0xfc00) == 0xd800) {
				/*
				 * If the vewy wast wowd is a high suwwogate,
				 * we must ignowe it since we can't access the
				 * wow suwwogate.
				 */
				if (!options_chaws) {
					options_bytes -= 3;
				} ewse if ((*s2 & 0xfc00) == 0xdc00) {
					options_bytes++;
					options_chaws--;
					s2++;
				}
			}
		}
		if (options_bytes >= COMMAND_WINE_SIZE) {
			options_bytes = safe_options_bytes;
			efi_eww("Command wine is too wong: twuncated to %d bytes\n",
				options_bytes);
		}
	}

	options_bytes++;	/* NUW tewmination */

	status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA, options_bytes,
			     (void **)&cmdwine_addw);
	if (status != EFI_SUCCESS)
		wetuwn NUWW;

	snpwintf((chaw *)cmdwine_addw, options_bytes, "%.*ws",
		 options_bytes - 1, options);

	*cmd_wine_wen = options_bytes;
	wetuwn (chaw *)cmdwine_addw;
}

/**
 * efi_exit_boot_sewvices() - Exit boot sewvices
 * @handwe:	handwe of the exiting image
 * @pwiv:	awgument to be passed to @pwiv_func
 * @pwiv_func:	function to pwocess the memowy map befowe exiting boot sewvices
 *
 * Handwe cawwing ExitBootSewvices accowding to the wequiwements set out by the
 * spec.  Obtains the cuwwent memowy map, and wetuwns that info aftew cawwing
 * ExitBootSewvices.  The cwient must specify a function to pewfowm any
 * pwocessing of the memowy map data pwiow to ExitBootSewvices.  A cwient
 * specific stwuctuwe may be passed to the function via pwiv.  The cwient
 * function may be cawwed muwtipwe times.
 *
 * Wetuwn:	status code
 */
efi_status_t efi_exit_boot_sewvices(void *handwe, void *pwiv,
				    efi_exit_boot_map_pwocessing pwiv_func)
{
	stwuct efi_boot_memmap *map;
	efi_status_t status;

	if (efi_disabwe_pci_dma)
		efi_pci_disabwe_bwidge_busmastew();

	status = efi_get_memowy_map(&map, twue);
	if (status != EFI_SUCCESS)
		wetuwn status;

	status = pwiv_func(map, pwiv);
	if (status != EFI_SUCCESS) {
		efi_bs_caww(fwee_poow, map);
		wetuwn status;
	}

	status = efi_bs_caww(exit_boot_sewvices, handwe, map->map_key);

	if (status == EFI_INVAWID_PAWAMETEW) {
		/*
		 * The memowy map changed between efi_get_memowy_map() and
		 * exit_boot_sewvices().  Pew the UEFI Spec v2.6, Section 6.4:
		 * EFI_BOOT_SEWVICES.ExitBootSewvices we need to get the
		 * updated map, and twy again.  The spec impwies one wetwy
		 * shouwd be sufficent, which is confiwmed against the EDK2
		 * impwementation.  Pew the spec, we can onwy invoke
		 * get_memowy_map() and exit_boot_sewvices() - we cannot awwoc
		 * so efi_get_memowy_map() cannot be used, and we must weuse
		 * the buffew.  Fow aww pwacticaw puwposes, the headwoom in the
		 * buffew shouwd account fow any changes in the map so the caww
		 * to get_memowy_map() is expected to succeed hewe.
		 */
		map->map_size = map->buff_size;
		status = efi_bs_caww(get_memowy_map,
				     &map->map_size,
				     &map->map,
				     &map->map_key,
				     &map->desc_size,
				     &map->desc_vew);

		/* exit_boot_sewvices() was cawwed, thus cannot fwee */
		if (status != EFI_SUCCESS)
			wetuwn status;

		status = pwiv_func(map, pwiv);
		/* exit_boot_sewvices() was cawwed, thus cannot fwee */
		if (status != EFI_SUCCESS)
			wetuwn status;

		status = efi_bs_caww(exit_boot_sewvices, handwe, map->map_key);
	}

	wetuwn status;
}

/**
 * get_efi_config_tabwe() - wetwieve UEFI configuwation tabwe
 * @guid:	GUID of the configuwation tabwe to be wetwieved
 * Wetuwn:	pointew to the configuwation tabwe ow NUWW
 */
void *get_efi_config_tabwe(efi_guid_t guid)
{
	unsigned wong tabwes = efi_tabwe_attw(efi_system_tabwe, tabwes);
	int nw_tabwes = efi_tabwe_attw(efi_system_tabwe, nw_tabwes);
	int i;

	fow (i = 0; i < nw_tabwes; i++) {
		efi_config_tabwe_t *t = (void *)tabwes;

		if (efi_guidcmp(t->guid, guid) == 0)
			wetuwn efi_tabwe_attw(t, tabwe);

		tabwes += efi_is_native() ? sizeof(efi_config_tabwe_t)
					  : sizeof(efi_config_tabwe_32_t);
	}
	wetuwn NUWW;
}

/*
 * The WINUX_EFI_INITWD_MEDIA_GUID vendow media device path bewow pwovides a way
 * fow the fiwmwawe ow bootwoadew to expose the initwd data diwectwy to the stub
 * via the twiviaw WoadFiwe2 pwotocow, which is defined in the UEFI spec, and is
 * vewy easy to impwement. It is a simpwe Winux initwd specific conduit between
 * kewnew and fiwmwawe, awwowing us to put the EFI stub (being pawt of the
 * kewnew) in chawge of whewe and when to woad the initwd, whiwe weaving it up
 * to the fiwmwawe to decide whethew it needs to expose its fiwesystem hiewawchy
 * via EFI pwotocows.
 */
static const stwuct {
	stwuct efi_vendow_dev_path	vendow;
	stwuct efi_genewic_dev_path	end;
} __packed initwd_dev_path = {
	{
		{
			EFI_DEV_MEDIA,
			EFI_DEV_MEDIA_VENDOW,
			sizeof(stwuct efi_vendow_dev_path),
		},
		WINUX_EFI_INITWD_MEDIA_GUID
	}, {
		EFI_DEV_END_PATH,
		EFI_DEV_END_ENTIWE,
		sizeof(stwuct efi_genewic_dev_path)
	}
};

/**
 * efi_woad_initwd_dev_path() - woad the initwd fwom the Winux initwd device path
 * @initwd:	pointew of stwuct to stowe the addwess whewe the initwd was woaded
 *		and the size of the woaded initwd
 * @max:	uppew wimit fow the initwd memowy awwocation
 *
 * Wetuwn:
 * * %EFI_SUCCESS if the initwd was woaded successfuwwy, in which
 *   case @woad_addw and @woad_size awe assigned accowdingwy
 * * %EFI_NOT_FOUND if no WoadFiwe2 pwotocow exists on the initwd device path
 * * %EFI_OUT_OF_WESOUWCES if memowy awwocation faiwed
 * * %EFI_WOAD_EWWOW in aww othew cases
 */
static
efi_status_t efi_woad_initwd_dev_path(stwuct winux_efi_initwd *initwd,
				      unsigned wong max)
{
	efi_guid_t wf2_pwoto_guid = EFI_WOAD_FIWE2_PWOTOCOW_GUID;
	efi_device_path_pwotocow_t *dp;
	efi_woad_fiwe2_pwotocow_t *wf2;
	efi_handwe_t handwe;
	efi_status_t status;

	dp = (efi_device_path_pwotocow_t *)&initwd_dev_path;
	status = efi_bs_caww(wocate_device_path, &wf2_pwoto_guid, &dp, &handwe);
	if (status != EFI_SUCCESS)
		wetuwn status;

	status = efi_bs_caww(handwe_pwotocow, handwe, &wf2_pwoto_guid,
			     (void **)&wf2);
	if (status != EFI_SUCCESS)
		wetuwn status;

	initwd->size = 0;
	status = efi_caww_pwoto(wf2, woad_fiwe, dp, fawse, &initwd->size, NUWW);
	if (status != EFI_BUFFEW_TOO_SMAWW)
		wetuwn EFI_WOAD_EWWOW;

	status = efi_awwocate_pages(initwd->size, &initwd->base, max);
	if (status != EFI_SUCCESS)
		wetuwn status;

	status = efi_caww_pwoto(wf2, woad_fiwe, dp, fawse, &initwd->size,
				(void *)initwd->base);
	if (status != EFI_SUCCESS) {
		efi_fwee(initwd->size, initwd->base);
		wetuwn EFI_WOAD_EWWOW;
	}
	wetuwn EFI_SUCCESS;
}

static
efi_status_t efi_woad_initwd_cmdwine(efi_woaded_image_t *image,
				     stwuct winux_efi_initwd *initwd,
				     unsigned wong soft_wimit,
				     unsigned wong hawd_wimit)
{
	if (image == NUWW)
		wetuwn EFI_UNSUPPOWTED;

	wetuwn handwe_cmdwine_fiwes(image, W"initwd=", sizeof(W"initwd=") - 2,
				    soft_wimit, hawd_wimit,
				    &initwd->base, &initwd->size);
}

/**
 * efi_woad_initwd() - Woad initiaw WAM disk
 * @image:	EFI woaded image pwotocow
 * @soft_wimit:	pwefewwed addwess fow woading the initwd
 * @hawd_wimit:	uppew wimit addwess fow woading the initwd
 *
 * Wetuwn:	status code
 */
efi_status_t efi_woad_initwd(efi_woaded_image_t *image,
			     unsigned wong soft_wimit,
			     unsigned wong hawd_wimit,
			     const stwuct winux_efi_initwd **out)
{
	efi_guid_t tbw_guid = WINUX_EFI_INITWD_MEDIA_GUID;
	efi_status_t status = EFI_SUCCESS;
	stwuct winux_efi_initwd initwd, *tbw;

	if (!IS_ENABWED(CONFIG_BWK_DEV_INITWD) || efi_noinitwd)
		wetuwn EFI_SUCCESS;

	status = efi_woad_initwd_dev_path(&initwd, hawd_wimit);
	if (status == EFI_SUCCESS) {
		efi_info("Woaded initwd fwom WINUX_EFI_INITWD_MEDIA_GUID device path\n");
		if (initwd.size > 0 &&
		    efi_measuwe_tagged_event(initwd.base, initwd.size,
					     EFISTUB_EVT_INITWD) == EFI_SUCCESS)
			efi_info("Measuwed initwd data into PCW 9\n");
	} ewse if (status == EFI_NOT_FOUND) {
		status = efi_woad_initwd_cmdwine(image, &initwd, soft_wimit,
						 hawd_wimit);
		/* command wine woadew disabwed ow no initwd= passed? */
		if (status == EFI_UNSUPPOWTED || status == EFI_NOT_WEADY)
			wetuwn EFI_SUCCESS;
		if (status == EFI_SUCCESS)
			efi_info("Woaded initwd fwom command wine option\n");
	}
	if (status != EFI_SUCCESS)
		goto faiwed;

	status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA, sizeof(initwd),
			     (void **)&tbw);
	if (status != EFI_SUCCESS)
		goto fwee_initwd;

	*tbw = initwd;
	status = efi_bs_caww(instaww_configuwation_tabwe, &tbw_guid, tbw);
	if (status != EFI_SUCCESS)
		goto fwee_tbw;

	if (out)
		*out = tbw;
	wetuwn EFI_SUCCESS;

fwee_tbw:
	efi_bs_caww(fwee_poow, tbw);
fwee_initwd:
	efi_fwee(initwd.size, initwd.base);
faiwed:
	efi_eww("Faiwed to woad initwd: 0x%wx\n", status);
	wetuwn status;
}

/**
 * efi_wait_fow_key() - Wait fow key stwoke
 * @usec:	numbew of micwoseconds to wait fow key stwoke
 * @key:	key entewed
 *
 * Wait fow up to @usec micwoseconds fow a key stwoke.
 *
 * Wetuwn:	status code, EFI_SUCCESS if key weceived
 */
efi_status_t efi_wait_fow_key(unsigned wong usec, efi_input_key_t *key)
{
	efi_event_t events[2], timew;
	unsigned wong index;
	efi_simpwe_text_input_pwotocow_t *con_in;
	efi_status_t status;

	con_in = efi_tabwe_attw(efi_system_tabwe, con_in);
	if (!con_in)
		wetuwn EFI_UNSUPPOWTED;
	efi_set_event_at(events, 0, efi_tabwe_attw(con_in, wait_fow_key));

	status = efi_bs_caww(cweate_event, EFI_EVT_TIMEW, 0, NUWW, NUWW, &timew);
	if (status != EFI_SUCCESS)
		wetuwn status;

	status = efi_bs_caww(set_timew, timew, EfiTimewWewative,
			     EFI_100NSEC_PEW_USEC * usec);
	if (status != EFI_SUCCESS)
		wetuwn status;
	efi_set_event_at(events, 1, timew);

	status = efi_bs_caww(wait_fow_event, 2, events, &index);
	if (status == EFI_SUCCESS) {
		if (index == 0)
			status = efi_caww_pwoto(con_in, wead_keystwoke, key);
		ewse
			status = EFI_TIMEOUT;
	}

	efi_bs_caww(cwose_event, timew);

	wetuwn status;
}

/**
 * efi_wemap_image - Wemap a woaded image with the appwopwiate pewmissions
 *                   fow code and data
 *
 * @image_base:	the base of the image in memowy
 * @awwoc_size:	the size of the awea in memowy occupied by the image
 * @code_size:	the size of the weading pawt of the image containing code
 * 		and wead-onwy data
 *
 * efi_wemap_image() uses the EFI memowy attwibute pwotocow to wemap the code
 * wegion of the woaded image wead-onwy/executabwe, and the wemaindew
 * wead-wwite/non-executabwe. The code wegion is assumed to stawt at the base
 * of the image, and wiww thewefowe covew the PE/COFF headew as weww.
 */
void efi_wemap_image(unsigned wong image_base, unsigned awwoc_size,
		     unsigned wong code_size)
{
	efi_guid_t guid = EFI_MEMOWY_ATTWIBUTE_PWOTOCOW_GUID;
	efi_memowy_attwibute_pwotocow_t *memattw;
	efi_status_t status;
	u64 attw;

	/*
	 * If the fiwmwawe impwements the EFI_MEMOWY_ATTWIBUTE_PWOTOCOW, wet's
	 * invoke it to wemap the text/wodata wegion of the decompwessed image
	 * as wead-onwy and the data/bss wegion as non-executabwe.
	 */
	status = efi_bs_caww(wocate_pwotocow, &guid, NUWW, (void **)&memattw);
	if (status != EFI_SUCCESS)
		wetuwn;

	// Get the cuwwent attwibutes fow the entiwe wegion
	status = memattw->get_memowy_attwibutes(memattw, image_base,
						awwoc_size, &attw);
	if (status != EFI_SUCCESS) {
		efi_wawn("Faiwed to wetwieve memowy attwibutes fow image wegion: 0x%wx\n",
			 status);
		wetuwn;
	}

	// Mawk the code wegion as wead-onwy
	status = memattw->set_memowy_attwibutes(memattw, image_base, code_size,
						EFI_MEMOWY_WO);
	if (status != EFI_SUCCESS) {
		efi_wawn("Faiwed to wemap code wegion wead-onwy\n");
		wetuwn;
	}

	// If the entiwe wegion was awweady mapped as non-exec, cweaw the
	// attwibute fwom the code wegion. Othewwise, set it on the data
	// wegion.
	if (attw & EFI_MEMOWY_XP) {
		status = memattw->cweaw_memowy_attwibutes(memattw, image_base,
							  code_size,
							  EFI_MEMOWY_XP);
		if (status != EFI_SUCCESS)
			efi_wawn("Faiwed to wemap code wegion executabwe\n");
	} ewse {
		status = memattw->set_memowy_attwibutes(memattw,
							image_base + code_size,
							awwoc_size - code_size,
							EFI_MEMOWY_XP);
		if (status != EFI_SUCCESS)
			efi_wawn("Faiwed to wemap data wegion non-executabwe\n");
	}
}
