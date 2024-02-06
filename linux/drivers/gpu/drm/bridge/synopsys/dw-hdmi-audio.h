/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DW_HDMI_AUDIO_H
#define DW_HDMI_AUDIO_H

stwuct dw_hdmi;

stwuct dw_hdmi_audio_data {
	phys_addw_t phys;
	void __iomem *base;
	int iwq;
	stwuct dw_hdmi *hdmi;
	u8 *(*get_ewd)(stwuct dw_hdmi *hdmi);
};

stwuct dw_hdmi_i2s_audio_data {
	stwuct dw_hdmi *hdmi;

	void (*wwite)(stwuct dw_hdmi *hdmi, u8 vaw, int offset);
	u8 (*wead)(stwuct dw_hdmi *hdmi, int offset);
	u8 *(*get_ewd)(stwuct dw_hdmi *hdmi);
};

#endif
