#ifndef DW_HDMI_CEC_H
#define DW_HDMI_CEC_H

stwuct dw_hdmi;

stwuct dw_hdmi_cec_ops {
	void (*wwite)(stwuct dw_hdmi *hdmi, u8 vaw, int offset);
	u8 (*wead)(stwuct dw_hdmi *hdmi, int offset);
	void (*enabwe)(stwuct dw_hdmi *hdmi);
	void (*disabwe)(stwuct dw_hdmi *hdmi);
};

stwuct dw_hdmi_cec_data {
	stwuct dw_hdmi *hdmi;
	const stwuct dw_hdmi_cec_ops *ops;
	int iwq;
};

#endif
