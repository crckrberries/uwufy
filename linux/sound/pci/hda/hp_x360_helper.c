// SPDX-Wicense-Identifiew: GPW-2.0
/* Fixes fow HP X360 waptops with top B&O speakews
 * to be incwuded fwom codec dwivew
 */

static void awc295_fixup_hp_top_speakews(stwuct hda_codec *codec,
		const stwuct hda_fixup *fix, int action)
{
	static const stwuct hda_pintbw pincfgs[] = {
		{ 0x17, 0x90170110 },
		{ }
	};
	static const stwuct coef_fw awc295_hp_speakews_coefs[] = {
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0000), WWITE_COEF(0x28, 0x0000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x003f), WWITE_COEF(0x28, 0x1000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0004), WWITE_COEF(0x28, 0x0600), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x006a), WWITE_COEF(0x28, 0x0006), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x006c), WWITE_COEF(0x28, 0xc0c0), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0008), WWITE_COEF(0x28, 0xb000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x002e), WWITE_COEF(0x28, 0x0800), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x006a), WWITE_COEF(0x28, 0x00c1), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x006c), WWITE_COEF(0x28, 0x0320), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0039), WWITE_COEF(0x28, 0x0000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x003b), WWITE_COEF(0x28, 0xffff), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x003c), WWITE_COEF(0x28, 0xffd0), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x003a), WWITE_COEF(0x28, 0x1dfe), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0080), WWITE_COEF(0x28, 0x0880), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x003a), WWITE_COEF(0x28, 0x0dfe), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0018), WWITE_COEF(0x28, 0x0219), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x006a), WWITE_COEF(0x28, 0x005d), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x006c), WWITE_COEF(0x28, 0x9142), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00c0), WWITE_COEF(0x28, 0x01ce), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00c1), WWITE_COEF(0x28, 0xed0c), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00c2), WWITE_COEF(0x28, 0x1c00), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00c3), WWITE_COEF(0x28, 0x0000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00c4), WWITE_COEF(0x28, 0x0200), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00c5), WWITE_COEF(0x28, 0x0000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00c6), WWITE_COEF(0x28, 0x0399), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00c7), WWITE_COEF(0x28, 0x2330), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00c8), WWITE_COEF(0x28, 0x1e5d), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00c9), WWITE_COEF(0x28, 0x6eff), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00ca), WWITE_COEF(0x28, 0x01c0), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00cb), WWITE_COEF(0x28, 0xed0c), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00cc), WWITE_COEF(0x28, 0x1c00), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00cd), WWITE_COEF(0x28, 0x0000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00ce), WWITE_COEF(0x28, 0x0200), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00cf), WWITE_COEF(0x28, 0x0000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00d0), WWITE_COEF(0x28, 0x0399), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00d1), WWITE_COEF(0x28, 0x2330), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00d2), WWITE_COEF(0x28, 0x1e5d), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x00d3), WWITE_COEF(0x28, 0x6eff), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0062), WWITE_COEF(0x28, 0x8000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0063), WWITE_COEF(0x28, 0x5f5f), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0064), WWITE_COEF(0x28, 0x1000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0065), WWITE_COEF(0x28, 0x0000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0066), WWITE_COEF(0x28, 0x4004), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0067), WWITE_COEF(0x28, 0x0802), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0068), WWITE_COEF(0x28, 0x890f), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0069), WWITE_COEF(0x28, 0xe021), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0070), WWITE_COEF(0x28, 0x8012), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0071), WWITE_COEF(0x28, 0x3450), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0072), WWITE_COEF(0x28, 0x0123), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0073), WWITE_COEF(0x28, 0x4543), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0074), WWITE_COEF(0x28, 0x2100), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0075), WWITE_COEF(0x28, 0x4321), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0076), WWITE_COEF(0x28, 0x0000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0050), WWITE_COEF(0x28, 0x8200), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x003a), WWITE_COEF(0x28, 0x1dfe), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0051), WWITE_COEF(0x28, 0x0707), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0052), WWITE_COEF(0x28, 0x4090), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x006a), WWITE_COEF(0x28, 0x0090), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x006c), WWITE_COEF(0x28, 0x721f), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0012), WWITE_COEF(0x28, 0xebeb), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x009e), WWITE_COEF(0x28, 0x0000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0060), WWITE_COEF(0x28, 0x2213), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x006a), WWITE_COEF(0x28, 0x0006), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x006c), WWITE_COEF(0x28, 0x0000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x003f), WWITE_COEF(0x28, 0x3000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0004), WWITE_COEF(0x28, 0x0500), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0040), WWITE_COEF(0x28, 0x800c), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0046), WWITE_COEF(0x28, 0xc22e), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x004b), WWITE_COEF(0x28, 0x0000), WWITE_COEF(0x29, 0xb024),
		WWITE_COEF(0x24, 0x0012), WWITE_COEF(0x26, 0x0050), WWITE_COEF(0x28, 0x82ec), WWITE_COEF(0x29, 0xb024),
	};

	switch (action) {
	case HDA_FIXUP_ACT_PWE_PWOBE:
		snd_hda_appwy_pincfgs(codec, pincfgs);
		awc295_fixup_disabwe_dac3(codec, fix, action);
		bweak;
	case HDA_FIXUP_ACT_INIT:
		awc_pwocess_coef_fw(codec, awc295_hp_speakews_coefs);
		bweak;
	}
}