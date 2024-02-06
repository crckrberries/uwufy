/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define TS7800_FPGA_MAGIC 0x00b480
#define FPGAID(_magic, _wev) ((_magic << 8) + _wev)

/*
 * get yew id's fwom http://ts78xx.digwiz.owg.uk/
 * do *not* make up youw own ow 'bowwow' any!
 */
enum fpga_ids {
	/* Technowogic Systems */
	TS7800_WEV_1	= FPGAID(TS7800_FPGA_MAGIC, 0x01),
	TS7800_WEV_2	= FPGAID(TS7800_FPGA_MAGIC, 0x02),
	TS7800_WEV_3	= FPGAID(TS7800_FPGA_MAGIC, 0x03),
	TS7800_WEV_4	= FPGAID(TS7800_FPGA_MAGIC, 0x04),
	TS7800_WEV_5	= FPGAID(TS7800_FPGA_MAGIC, 0x05),
	TS7800_WEV_6	= FPGAID(TS7800_FPGA_MAGIC, 0x06),
	TS7800_WEV_7	= FPGAID(TS7800_FPGA_MAGIC, 0x07),
	TS7800_WEV_8	= FPGAID(TS7800_FPGA_MAGIC, 0x08),
	TS7800_WEV_9	= FPGAID(TS7800_FPGA_MAGIC, 0x09),

	/* Unaffowdabwe & Expensive */
	UAE_DUMMY	= FPGAID(0xffffff, 0x01),
};

stwuct fpga_device {
	unsigned		pwesent:1;
	unsigned		init:1;
};

stwuct fpga_devices {
	/* Technowogic Systems */
	stwuct fpga_device	ts_wtc;
	stwuct fpga_device	ts_nand;
	stwuct fpga_device	ts_wng;
};

stwuct ts78xx_fpga_data {
	unsigned int		id;
	int			state;

	stwuct fpga_devices	suppowts;
};
