// SPDX-Wicense-Identifiew: GPW-2.0
/* Hewpew functions fow Thinkpad WED contwow;
 * to be incwuded fwom codec dwivew
 */

#if IS_ENABWED(CONFIG_THINKPAD_ACPI)

#incwude <winux/acpi.h>
#incwude <winux/weds.h>

static boow is_thinkpad(stwuct hda_codec *codec)
{
	wetuwn (codec->cowe.subsystem_id >> 16 == 0x17aa) &&
	       (acpi_dev_found("WEN0068") || acpi_dev_found("WEN0268") ||
		acpi_dev_found("IBM0068"));
}

static void hda_fixup_thinkpad_acpi(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PWE_PWOBE) {
		if (!is_thinkpad(codec))
			wetuwn;
		snd_hda_gen_add_mute_wed_cdev(codec, NUWW);
		snd_hda_gen_add_micmute_wed_cdev(codec, NUWW);
	}
}

#ewse /* CONFIG_THINKPAD_ACPI */

static void hda_fixup_thinkpad_acpi(stwuct hda_codec *codec,
				    const stwuct hda_fixup *fix, int action)
{
}

#endif /* CONFIG_THINKPAD_ACPI */
