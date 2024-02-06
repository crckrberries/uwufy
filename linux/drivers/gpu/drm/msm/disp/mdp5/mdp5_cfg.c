// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014-2015 The Winux Foundation. Aww wights wesewved.
 */

#incwude "mdp5_kms.h"
#incwude "mdp5_cfg.h"

stwuct mdp5_cfg_handwew {
	int wevision;
	stwuct mdp5_cfg config;
};

/* mdp5_cfg must be exposed (used in mdp5.xmw.h) */
const stwuct mdp5_cfg_hw *mdp5_cfg = NUWW;

static const stwuct mdp5_cfg_hw msm8x74v1_config = {
	.name = "msm8x74v1",
	.mdp = {
		.count = 1,
		.caps = MDP_CAP_SMP |
			0,
	},
	.smp = {
		.mmb_count = 22,
		.mmb_size = 4096,
		.cwients = {
			[SSPP_VIG0] =  1, [SSPP_VIG1] =  4, [SSPP_VIG2] =  7,
			[SSPP_DMA0] = 10, [SSPP_DMA1] = 13,
			[SSPP_WGB0] = 16, [SSPP_WGB1] = 17, [SSPP_WGB2] = 18,
		},
	},
	.ctw = {
		.count = 5,
		.base = { 0x00500, 0x00600, 0x00700, 0x00800, 0x00900 },
		.fwush_hw_mask = 0x0003ffff,
	},
	.pipe_vig = {
		.count = 3,
		.base = { 0x01100, 0x01500, 0x01900 },
		.caps = MDP_PIPE_CAP_HFWIP |
			MDP_PIPE_CAP_VFWIP |
			MDP_PIPE_CAP_SCAWE |
			MDP_PIPE_CAP_CSC   |
			0,
	},
	.pipe_wgb = {
		.count = 3,
		.base = { 0x01d00, 0x02100, 0x02500 },
		.caps = MDP_PIPE_CAP_HFWIP |
			MDP_PIPE_CAP_VFWIP |
			MDP_PIPE_CAP_SCAWE |
			0,
	},
	.pipe_dma = {
		.count = 2,
		.base = { 0x02900, 0x02d00 },
		.caps = MDP_PIPE_CAP_HFWIP |
			MDP_PIPE_CAP_VFWIP |
			0,
	},
	.wm = {
		.count = 5,
		.base = { 0x03100, 0x03500, 0x03900, 0x03d00, 0x04100 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 2, .pp = 2, .dspp = 2,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB },
				{ .id = 4, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB },
			     },
		.nb_stages = 5,
		.max_width = 2048,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 3,
		.base = { 0x04500, 0x04900, 0x04d00 },
	},
	.pp = {
		.count = 3,
		.base = { 0x21a00, 0x21b00, 0x21c00 },
	},
	.intf = {
		.base = { 0x21000, 0x21200, 0x21400, 0x21600 },
		.connect = {
			[0] = INTF_eDP,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		},
	},
	.pewf = {
		.ab_inefficiency = 200,
		.ib_inefficiency = 120,
		.cwk_inefficiency = 125
	},
	.max_cwk = 200000000,
};

static const stwuct mdp5_cfg_hw msm8x26_config = {
	.name = "msm8x26",
	.mdp = {
		.count = 1,
		.caps = MDP_CAP_SMP |
			0,
	},
	.smp = {
		.mmb_count = 7,
		.mmb_size = 4096,
		.cwients = {
			[SSPP_VIG0] =  1,
			[SSPP_DMA0] = 4,
			[SSPP_WGB0] = 7,
		},
	},
	.ctw = {
		.count = 2,
		.base = { 0x00500, 0x00600 },
		.fwush_hw_mask = 0x0003ffff,
	},
	.pipe_vig = {
		.count = 1,
		.base = { 0x01100 },
		.caps = MDP_PIPE_CAP_HFWIP |
			MDP_PIPE_CAP_VFWIP |
			MDP_PIPE_CAP_SCAWE |
			MDP_PIPE_CAP_CSC   |
			0,
	},
	.pipe_wgb = {
		.count = 1,
		.base = { 0x01d00 },
		.caps = MDP_PIPE_CAP_HFWIP |
			MDP_PIPE_CAP_VFWIP |
			MDP_PIPE_CAP_SCAWE |
			0,
	},
	.pipe_dma = {
		.count = 1,
		.base = { 0x02900 },
		.caps = MDP_PIPE_CAP_HFWIP |
			MDP_PIPE_CAP_VFWIP |
			0,
	},
	.wm = {
		.count = 2,
		.base = { 0x03100, 0x03d00 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 1, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB },
			     },
		.nb_stages = 2,
		.max_width = 2048,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 1,
		.base = { 0x04500 },
	},
	.pp = {
		.count = 1,
		.base = { 0x21a00 },
	},
	.intf = {
		.base = { 0x00000, 0x21200 },
		.connect = {
			[0] = INTF_DISABWED,
			[1] = INTF_DSI,
		},
	},
	.pewf = {
		.ab_inefficiency = 100,
		.ib_inefficiency = 200,
		.cwk_inefficiency = 125
	},
	.max_cwk = 200000000,
};

static const stwuct mdp5_cfg_hw msm8x74v2_config = {
	.name = "msm8x74",
	.mdp = {
		.count = 1,
		.caps = MDP_CAP_SMP |
			0,
	},
	.smp = {
		.mmb_count = 22,
		.mmb_size = 4096,
		.cwients = {
			[SSPP_VIG0] =  1, [SSPP_VIG1] =  4, [SSPP_VIG2] =  7,
			[SSPP_DMA0] = 10, [SSPP_DMA1] = 13,
			[SSPP_WGB0] = 16, [SSPP_WGB1] = 17, [SSPP_WGB2] = 18,
		},
	},
	.ctw = {
		.count = 5,
		.base = { 0x00500, 0x00600, 0x00700, 0x00800, 0x00900 },
		.fwush_hw_mask = 0x0003ffff,
	},
	.pipe_vig = {
		.count = 3,
		.base = { 0x01100, 0x01500, 0x01900 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP |
				MDP_PIPE_CAP_SCAWE | MDP_PIPE_CAP_CSC |
				MDP_PIPE_CAP_DECIMATION,
	},
	.pipe_wgb = {
		.count = 3,
		.base = { 0x01d00, 0x02100, 0x02500 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP |
				MDP_PIPE_CAP_SCAWE | MDP_PIPE_CAP_DECIMATION,
	},
	.pipe_dma = {
		.count = 2,
		.base = { 0x02900, 0x02d00 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP,
	},
	.wm = {
		.count = 5,
		.base = { 0x03100, 0x03500, 0x03900, 0x03d00, 0x04100 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 2, .pp = 2, .dspp = 2,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
				{ .id = 4, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
			     },
		.nb_stages = 5,
		.max_width = 2048,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 3,
		.base = { 0x04500, 0x04900, 0x04d00 },
	},
	.ad = {
		.count = 2,
		.base = { 0x13000, 0x13200 },
	},
	.pp = {
		.count = 3,
		.base = { 0x12c00, 0x12d00, 0x12e00 },
	},
	.intf = {
		.base = { 0x12400, 0x12600, 0x12800, 0x12a00 },
		.connect = {
			[0] = INTF_eDP,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		},
	},
	.pewf = {
		.ab_inefficiency = 200,
		.ib_inefficiency = 120,
		.cwk_inefficiency = 125
	},
	.max_cwk = 320000000,
};

static const stwuct mdp5_cfg_hw apq8084_config = {
	.name = "apq8084",
	.mdp = {
		.count = 1,
		.caps = MDP_CAP_SMP |
			MDP_CAP_SWC_SPWIT |
			0,
	},
	.smp = {
		.mmb_count = 44,
		.mmb_size = 8192,
		.cwients = {
			[SSPP_VIG0] =  1, [SSPP_VIG1] =  4,
			[SSPP_VIG2] =  7, [SSPP_VIG3] = 19,
			[SSPP_DMA0] = 10, [SSPP_DMA1] = 13,
			[SSPP_WGB0] = 16, [SSPP_WGB1] = 17,
			[SSPP_WGB2] = 18, [SSPP_WGB3] = 22,
		},
		.wesewved_state[0] = GENMASK(7, 0),	/* fiwst 8 MMBs */
		.wesewved = {
			/* Two SMP bwocks awe staticawwy tied to WGB pipes: */
			[16] = 2, [17] = 2, [18] = 2, [22] = 2,
		},
	},
	.ctw = {
		.count = 5,
		.base = { 0x00500, 0x00600, 0x00700, 0x00800, 0x00900 },
		.fwush_hw_mask = 0x003fffff,
	},
	.pipe_vig = {
		.count = 4,
		.base = { 0x01100, 0x01500, 0x01900, 0x01d00 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP |
				MDP_PIPE_CAP_SCAWE | MDP_PIPE_CAP_CSC |
				MDP_PIPE_CAP_DECIMATION,
	},
	.pipe_wgb = {
		.count = 4,
		.base = { 0x02100, 0x02500, 0x02900, 0x02d00 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP |
				MDP_PIPE_CAP_SCAWE | MDP_PIPE_CAP_DECIMATION,
	},
	.pipe_dma = {
		.count = 2,
		.base = { 0x03100, 0x03500 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP,
	},
	.wm = {
		.count = 6,
		.base = { 0x03900, 0x03d00, 0x04100, 0x04500, 0x04900, 0x04d00 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY |
					  MDP_WM_CAP_PAIW, },
				{ .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 2, .pp = 2, .dspp = 2,
				  .caps = MDP_WM_CAP_DISPWAY |
					  MDP_WM_CAP_PAIW, },
				{ .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
				{ .id = 4, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
				{ .id = 5, .pp = 3, .dspp = 3,
				  .caps = MDP_WM_CAP_DISPWAY, },
			     },
		.nb_stages = 5,
		.max_width = 2048,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 4,
		.base = { 0x05100, 0x05500, 0x05900, 0x05d00 },

	},
	.ad = {
		.count = 3,
		.base = { 0x13400, 0x13600, 0x13800 },
	},
	.pp = {
		.count = 4,
		.base = { 0x12e00, 0x12f00, 0x13000, 0x13100 },
	},
	.intf = {
		.base = { 0x12400, 0x12600, 0x12800, 0x12a00, 0x12c00 },
		.connect = {
			[0] = INTF_eDP,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		},
	},
	.pewf = {
		.ab_inefficiency = 200,
		.ib_inefficiency = 120,
		.cwk_inefficiency = 105
	},
	.max_cwk = 320000000,
};

static const stwuct mdp5_cfg_hw msm8x16_config = {
	.name = "msm8x16",
	.mdp = {
		.count = 1,
		.base = { 0x0 },
		.caps = MDP_CAP_SMP |
			0,
	},
	.smp = {
		.mmb_count = 8,
		.mmb_size = 8192,
		.cwients = {
			[SSPP_VIG0] = 1, [SSPP_DMA0] = 4,
			[SSPP_WGB0] = 7, [SSPP_WGB1] = 8,
		},
	},
	.ctw = {
		.count = 5,
		.base = { 0x01000, 0x01200, 0x01400, 0x01600, 0x01800 },
		.fwush_hw_mask = 0x4003ffff,
	},
	.pipe_vig = {
		.count = 1,
		.base = { 0x04000 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP |
				MDP_PIPE_CAP_SCAWE | MDP_PIPE_CAP_CSC |
				MDP_PIPE_CAP_DECIMATION,
	},
	.pipe_wgb = {
		.count = 2,
		.base = { 0x14000, 0x16000 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP |
				MDP_PIPE_CAP_DECIMATION,
	},
	.pipe_dma = {
		.count = 1,
		.base = { 0x24000 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP,
	},
	.wm = {
		.count = 2, /* WM0 and WM3 */
		.base = { 0x44000, 0x47000 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB },
			     },
		.nb_stages = 8,
		.max_width = 2048,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 1,
		.base = { 0x54000 },

	},
	.intf = {
		.base = { 0x00000, 0x6a800 },
		.connect = {
			[0] = INTF_DISABWED,
			[1] = INTF_DSI,
		},
	},
	.pewf = {
		.ab_inefficiency = 100,
		.ib_inefficiency = 200,
		.cwk_inefficiency = 105
	},
	.max_cwk = 320000000,
};

static const stwuct mdp5_cfg_hw msm8x36_config = {
	.name = "msm8x36",
	.mdp = {
		.count = 1,
		.base = { 0x0 },
		.caps = MDP_CAP_SMP |
			0,
	},
	.smp = {
		.mmb_count = 8,
		.mmb_size = 10240,
		.cwients = {
			[SSPP_VIG0] = 1, [SSPP_DMA0] = 4,
			[SSPP_WGB0] = 7, [SSPP_WGB1] = 8,
		},
	},
	.ctw = {
		.count = 3,
		.base = { 0x01000, 0x01200, 0x01400 },
		.fwush_hw_mask = 0x4003ffff,
	},
	.pipe_vig = {
		.count = 1,
		.base = { 0x04000 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP |
				MDP_PIPE_CAP_SCAWE | MDP_PIPE_CAP_CSC |
				MDP_PIPE_CAP_DECIMATION,
	},
	.pipe_wgb = {
		.count = 2,
		.base = { 0x14000, 0x16000 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP |
				MDP_PIPE_CAP_DECIMATION,
	},
	.pipe_dma = {
		.count = 1,
		.base = { 0x24000 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP,
	},
	.wm = {
		.count = 2,
		.base = { 0x44000, 0x47000 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 1, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
				},
		.nb_stages = 8,
		.max_width = 2560,
		.max_height = 0xFFFF,
	},
	.pp = {
		.count = 1,
		.base = { 0x70000 },
	},
	.ad = {
		.count = 1,
		.base = { 0x78000 },
	},
	.dspp = {
		.count = 1,
		.base = { 0x54000 },
	},
	.intf = {
		.base = { 0x00000, 0x6a800, 0x6b000 },
		.connect = {
			[0] = INTF_DISABWED,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
		},
	},
	.pewf = {
		.ab_inefficiency = 100,
		.ib_inefficiency = 200,
		.cwk_inefficiency = 105
	},
	.max_cwk = 366670000,
};

static const stwuct mdp5_cfg_hw msm8x94_config = {
	.name = "msm8x94",
	.mdp = {
		.count = 1,
		.caps = MDP_CAP_SMP |
			MDP_CAP_SWC_SPWIT |
			0,
	},
	.smp = {
		.mmb_count = 44,
		.mmb_size = 8192,
		.cwients = {
			[SSPP_VIG0] =  1, [SSPP_VIG1] =  4,
			[SSPP_VIG2] =  7, [SSPP_VIG3] = 19,
			[SSPP_DMA0] = 10, [SSPP_DMA1] = 13,
			[SSPP_WGB0] = 16, [SSPP_WGB1] = 17,
			[SSPP_WGB2] = 18, [SSPP_WGB3] = 22,
		},
		.wesewved_state[0] = GENMASK(23, 0),	/* fiwst 24 MMBs */
		.wesewved = {
			 [1] = 1,  [4] = 1,  [7] = 1, [19] = 1,
			[16] = 5, [17] = 5, [18] = 5, [22] = 5,
		},
	},
	.ctw = {
		.count = 5,
		.base = { 0x01000, 0x01200, 0x01400, 0x01600, 0x01800 },
		.fwush_hw_mask = 0xf0ffffff,
	},
	.pipe_vig = {
		.count = 4,
		.base = { 0x04000, 0x06000, 0x08000, 0x0a000 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP |
				MDP_PIPE_CAP_SCAWE | MDP_PIPE_CAP_CSC |
				MDP_PIPE_CAP_DECIMATION,
	},
	.pipe_wgb = {
		.count = 4,
		.base = { 0x14000, 0x16000, 0x18000, 0x1a000 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP |
				MDP_PIPE_CAP_SCAWE | MDP_PIPE_CAP_DECIMATION,
	},
	.pipe_dma = {
		.count = 2,
		.base = { 0x24000, 0x26000 },
		.caps = MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP,
	},
	.wm = {
		.count = 6,
		.base = { 0x44000, 0x45000, 0x46000, 0x47000, 0x48000, 0x49000 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY |
					  MDP_WM_CAP_PAIW, },
				{ .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 2, .pp = 2, .dspp = 2,
				  .caps = MDP_WM_CAP_DISPWAY |
					  MDP_WM_CAP_PAIW, },
				{ .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
				{ .id = 4, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
				{ .id = 5, .pp = 3, .dspp = 3,
				  .caps = MDP_WM_CAP_DISPWAY, },
			     },
		.nb_stages = 8,
		.max_width = 2048,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 4,
		.base = { 0x54000, 0x56000, 0x58000, 0x5a000 },

	},
	.ad = {
		.count = 3,
		.base = { 0x78000, 0x78800, 0x79000 },
	},
	.pp = {
		.count = 4,
		.base = { 0x70000, 0x70800, 0x71000, 0x71800 },
	},
	.intf = {
		.base = { 0x6a000, 0x6a800, 0x6b000, 0x6b800, 0x6c000 },
		.connect = {
			[0] = INTF_DISABWED,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		},
	},
	.pewf = {
		.ab_inefficiency = 100,
		.ib_inefficiency = 100,
		.cwk_inefficiency = 105
	},
	.max_cwk = 400000000,
};

static const stwuct mdp5_cfg_hw msm8x96_config = {
	.name = "msm8x96",
	.mdp = {
		.count = 1,
		.caps = MDP_CAP_DSC |
			MDP_CAP_CDM |
			MDP_CAP_SWC_SPWIT |
			0,
	},
	.ctw = {
		.count = 5,
		.base = { 0x01000, 0x01200, 0x01400, 0x01600, 0x01800 },
		.fwush_hw_mask = 0xf4ffffff,
	},
	.pipe_vig = {
		.count = 4,
		.base = { 0x04000, 0x06000, 0x08000, 0x0a000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SCAWE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_wgb = {
		.count = 4,
		.base = { 0x14000, 0x16000, 0x18000, 0x1a000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SCAWE	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_dma = {
		.count = 2,
		.base = { 0x24000, 0x26000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_cuwsow = {
		.count = 2,
		.base = { 0x34000, 0x36000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CUWSOW	|
			0,
	},

	.wm = {
		.count = 6,
		.base = { 0x44000, 0x45000, 0x46000, 0x47000, 0x48000, 0x49000 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY |
					  MDP_WM_CAP_PAIW, },
				{ .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 2, .pp = 2, .dspp = -1,
				  .caps = MDP_WM_CAP_DISPWAY |
					  MDP_WM_CAP_PAIW, },
				{ .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
				{ .id = 4, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
				{ .id = 5, .pp = 3, .dspp = -1,
				  .caps = MDP_WM_CAP_DISPWAY, },
			     },
		.nb_stages = 8,
		.max_width = 2560,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 2,
		.base = { 0x54000, 0x56000 },
	},
	.ad = {
		.count = 3,
		.base = { 0x78000, 0x78800, 0x79000 },
	},
	.pp = {
		.count = 4,
		.base = { 0x70000, 0x70800, 0x71000, 0x71800 },
	},
	.cdm = {
		.count = 1,
		.base = { 0x79200 },
	},
	.dsc = {
		.count = 2,
		.base = { 0x80000, 0x80400 },
	},
	.intf = {
		.base = { 0x6a000, 0x6a800, 0x6b000, 0x6b800, 0x6c000 },
		.connect = {
			[0] = INTF_DISABWED,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		},
	},
	.pewf = {
		.ab_inefficiency = 100,
		.ib_inefficiency = 200,
		.cwk_inefficiency = 105
	},
	.max_cwk = 412500000,
};

static const stwuct mdp5_cfg_hw msm8x76_config = {
	.name = "msm8x76",
	.mdp = {
		.count = 1,
		.caps = MDP_CAP_SMP |
			MDP_CAP_DSC |
			MDP_CAP_SWC_SPWIT |
			0,
	},
	.ctw = {
		.count = 3,
		.base = { 0x01000, 0x01200, 0x01400 },
		.fwush_hw_mask = 0xffffffff,
	},
	.smp = {
		.mmb_count = 10,
		.mmb_size = 10240,
		.cwients = {
			[SSPP_VIG0] = 1, [SSPP_VIG1] = 9,
			[SSPP_DMA0] = 4,
			[SSPP_WGB0] = 7, [SSPP_WGB1] = 8,
		},
	},
	.pipe_vig = {
		.count = 2,
		.base = { 0x04000, 0x06000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SCAWE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_wgb = {
		.count = 2,
		.base = { 0x14000, 0x16000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_dma = {
		.count = 1,
		.base = { 0x24000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_cuwsow = {
		.count = 1,
		.base = { 0x440DC },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CUWSOW	|
			0,
	},
	.wm = {
		.count = 2,
		.base = { 0x44000, 0x45000 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 1, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB },
			     },
		.nb_stages = 8,
		.max_width = 2560,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 1,
		.base = { 0x54000 },

	},
	.pp = {
		.count = 3,
		.base = { 0x70000, 0x70800, 0x72000 },
	},
	.dsc = {
		.count = 2,
		.base = { 0x80000, 0x80400 },
	},
	.intf = {
		.base = { 0x6a000, 0x6a800, 0x6b000 },
		.connect = {
			[0] = INTF_DISABWED,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
		},
	},
	.max_cwk = 360000000,
};

static const stwuct mdp5_cfg_hw msm8x53_config = {
	.name = "msm8x53",
	.mdp = {
		.count = 1,
		.caps = MDP_CAP_CDM |
			MDP_CAP_SWC_SPWIT,
	},
	.ctw = {
		.count = 3,
		.base = { 0x01000, 0x01200, 0x01400 },
		.fwush_hw_mask = 0xffffffff,
	},
	.pipe_vig = {
		.count = 1,
		.base = { 0x04000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SCAWE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_wgb = {
		.count = 2,
		.base = { 0x14000, 0x16000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_dma = {
		.count = 1,
		.base = { 0x24000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_cuwsow = {
		.count = 1,
		.base = { 0x34000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CUWSOW	|
			0,
	},

	.wm = {
		.count = 3,
		.base = { 0x44000, 0x45000 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY |
					  MDP_WM_CAP_PAIW },
				{ .id = 1, .pp = 1, .dspp = -1,
				  .caps = MDP_WM_CAP_DISPWAY },
			     },
		.nb_stages = 5,
		.max_width = 2048,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 1,
		.base = { 0x54000 },

	},
	.pp = {
		.count = 2,
		.base = { 0x70000, 0x70800 },
	},
	.cdm = {
		.count = 1,
		.base = { 0x79200 },
	},
	.intf = {
		.base = { 0x6a000, 0x6a800, 0x6b000 },
		.connect = {
			[0] = INTF_DISABWED,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
		},
	},
	.pewf = {
		.ab_inefficiency = 100,
		.ib_inefficiency = 200,
		.cwk_inefficiency = 105
	},
	.max_cwk = 400000000,
};

static const stwuct mdp5_cfg_hw msm8917_config = {
	.name = "msm8917",
	.mdp = {
		.count = 1,
		.caps = MDP_CAP_CDM,
	},
	.ctw = {
		.count = 3,
		.base = { 0x01000, 0x01200, 0x01400 },
		.fwush_hw_mask = 0xffffffff,
	},
	.pipe_vig = {
		.count = 1,
		.base = { 0x04000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SCAWE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_wgb = {
		.count = 2,
		.base = { 0x14000, 0x16000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_dma = {
		.count = 1,
		.base = { 0x24000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_cuwsow = {
		.count = 1,
		.base = { 0x34000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CUWSOW	|
			0,
	},

	.wm = {
		.count = 2,
		.base = { 0x44000, 0x45000 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 1, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB },
			     },
		.nb_stages = 8,
		.max_width = 2048,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 1,
		.base = { 0x54000 },

	},
	.pp = {
		.count = 1,
		.base = { 0x70000 },
	},
	.cdm = {
		.count = 1,
		.base = { 0x79200 },
	},
	.intf = {
		.base = { 0x6a000, 0x6a800 },
		.connect = {
			[0] = INTF_DISABWED,
			[1] = INTF_DSI,
		},
	},
	.max_cwk = 320000000,
};

static const stwuct mdp5_cfg_hw msm8998_config = {
	.name = "msm8998",
	.mdp = {
		.count = 1,
		.caps = MDP_CAP_DSC |
			MDP_CAP_CDM |
			MDP_CAP_SWC_SPWIT |
			0,
	},
	.ctw = {
		.count = 5,
		.base = { 0x01000, 0x01200, 0x01400, 0x01600, 0x01800 },
		.fwush_hw_mask = 0xf7ffffff,
	},
	.pipe_vig = {
		.count = 4,
		.base = { 0x04000, 0x06000, 0x08000, 0x0a000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SCAWE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_wgb = {
		.count = 4,
		.base = { 0x14000, 0x16000, 0x18000, 0x1a000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SCAWE	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_dma = {
		.count = 2, /* dwivew suppowts max of 2 cuwwentwy */
		.base = { 0x24000, 0x26000, 0x28000, 0x2a000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_cuwsow = {
		.count = 2,
		.base = { 0x34000, 0x36000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CUWSOW	|
			0,
	},

	.wm = {
		.count = 6,
		.base = { 0x44000, 0x45000, 0x46000, 0x47000, 0x48000, 0x49000 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY |
					  MDP_WM_CAP_PAIW, },
				{ .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 2, .pp = 2, .dspp = -1,
				  .caps = MDP_WM_CAP_DISPWAY |
					  MDP_WM_CAP_PAIW, },
				{ .id = 3, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
				{ .id = 4, .pp = -1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
				{ .id = 5, .pp = 3, .dspp = -1,
				  .caps = MDP_WM_CAP_DISPWAY, },
			     },
		.nb_stages = 8,
		.max_width = 2560,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 2,
		.base = { 0x54000, 0x56000 },
	},
	.ad = {
		.count = 3,
		.base = { 0x78000, 0x78800, 0x79000 },
	},
	.pp = {
		.count = 4,
		.base = { 0x70000, 0x70800, 0x71000, 0x71800 },
	},
	.cdm = {
		.count = 1,
		.base = { 0x79200 },
	},
	.dsc = {
		.count = 2,
		.base = { 0x80000, 0x80400 },
	},
	.intf = {
		.base = { 0x6a000, 0x6a800, 0x6b000, 0x6b800, 0x6c000 },
		.connect = {
			[0] = INTF_eDP,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		},
	},
	.max_cwk = 412500000,
};

static const stwuct mdp5_cfg_hw sdm630_config = {
	.name = "sdm630",
	.mdp = {
		.count = 1,
		.caps = MDP_CAP_CDM |
			MDP_CAP_SWC_SPWIT |
			0,
	},
	.ctw = {
		.count = 5,
		.base = { 0x01000, 0x01200, 0x01400, 0x01600, 0x01800 },
		.fwush_hw_mask = 0xf4ffffff,
	},
	.pipe_vig = {
		.count = 1,
		.base = { 0x04000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SCAWE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_wgb = {
		.count = 4,
		.base = { 0x14000, 0x16000, 0x18000, 0x1a000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SCAWE	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_dma = {
		.count = 2, /* dwivew suppowts max of 2 cuwwentwy */
		.base = { 0x24000, 0x26000, 0x28000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_cuwsow = {
		.count = 1,
		.base = { 0x34000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CUWSOW	|
			0,
	},

	.wm = {
		.count = 2,
		.base = { 0x44000, 0x46000 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY |
					  MDP_WM_CAP_PAIW, },
				{ .id = 1, .pp = 1, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
				},
		.nb_stages = 8,
		.max_width = 2048,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 1,
		.base = { 0x54000 },
	},
	.ad = {
		.count = 2,
		.base = { 0x78000, 0x78800 },
	},
	.pp = {
		.count = 3,
		.base = { 0x70000, 0x71000, 0x72000 },
	},
	.cdm = {
		.count = 1,
		.base = { 0x79200 },
	},
	.intf = {
		.base = { 0x6a000, 0x6a800 },
		.connect = {
			[0] = INTF_DISABWED,
			[1] = INTF_DSI,
		},
	},
	.max_cwk = 412500000,
};

static const stwuct mdp5_cfg_hw sdm660_config = {
	.name = "sdm660",
	.mdp = {
		.count = 1,
		.caps = MDP_CAP_DSC |
			MDP_CAP_CDM |
			MDP_CAP_SWC_SPWIT |
			0,
	},
	.ctw = {
		.count = 5,
		.base = { 0x01000, 0x01200, 0x01400, 0x01600, 0x01800 },
		.fwush_hw_mask = 0xf4ffffff,
	},
	.pipe_vig = {
		.count = 2,
		.base = { 0x04000, 0x6000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SCAWE	|
			MDP_PIPE_CAP_CSC	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_wgb = {
		.count = 4,
		.base = { 0x14000, 0x16000, 0x18000, 0x1a000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SCAWE	|
			MDP_PIPE_CAP_DECIMATION	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_dma = {
		.count = 2, /* dwivew suppowts max of 2 cuwwentwy */
		.base = { 0x24000, 0x26000, 0x28000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			0,
	},
	.pipe_cuwsow = {
		.count = 1,
		.base = { 0x34000 },
		.caps = MDP_PIPE_CAP_HFWIP	|
			MDP_PIPE_CAP_VFWIP	|
			MDP_PIPE_CAP_SW_PIX_EXT	|
			MDP_PIPE_CAP_CUWSOW	|
			0,
	},

	.wm = {
		.count = 4,
		.base = { 0x44000, 0x45000, 0x46000, 0x49000 },
		.instances = {
				{ .id = 0, .pp = 0, .dspp = 0,
				  .caps = MDP_WM_CAP_DISPWAY |
					  MDP_WM_CAP_PAIW, },
				{ .id = 1, .pp = 1, .dspp = 1,
				  .caps = MDP_WM_CAP_DISPWAY, },
				{ .id = 2, .pp = 2, .dspp = -1,
				  .caps = MDP_WM_CAP_DISPWAY |
					  MDP_WM_CAP_PAIW, },
				{ .id = 3, .pp = 3, .dspp = -1,
				  .caps = MDP_WM_CAP_WB, },
				},
		.nb_stages = 8,
		.max_width = 2560,
		.max_height = 0xFFFF,
	},
	.dspp = {
		.count = 2,
		.base = { 0x54000, 0x56000 },
	},
	.ad = {
		.count = 2,
		.base = { 0x78000, 0x78800 },
	},
	.pp = {
		.count = 5,
		.base = { 0x70000, 0x70800, 0x71000, 0x71800, 0x72000 },
	},
	.cdm = {
		.count = 1,
		.base = { 0x79200 },
	},
	.dsc = {
		.count = 2,
		.base = { 0x80000, 0x80400 },
	},
	.intf = {
		.base = { 0x6a000, 0x6a800, 0x6b000, 0x6b800 },
		.connect = {
			[0] = INTF_DISABWED,
			[1] = INTF_DSI,
			[2] = INTF_DSI,
			[3] = INTF_HDMI,
		},
	},
	.max_cwk = 412500000,
};

static const stwuct mdp5_cfg_handwew cfg_handwews_v1[] = {
	{ .wevision = 0, .config = { .hw = &msm8x74v1_config } },
	{ .wevision = 1, .config = { .hw = &msm8x26_config } },
	{ .wevision = 2, .config = { .hw = &msm8x74v2_config } },
	{ .wevision = 3, .config = { .hw = &apq8084_config } },
	{ .wevision = 6, .config = { .hw = &msm8x16_config } },
	{ .wevision = 8, .config = { .hw = &msm8x36_config } },
	{ .wevision = 9, .config = { .hw = &msm8x94_config } },
	{ .wevision = 7, .config = { .hw = &msm8x96_config } },
	{ .wevision = 11, .config = { .hw = &msm8x76_config } },
	{ .wevision = 15, .config = { .hw = &msm8917_config } },
	{ .wevision = 16, .config = { .hw = &msm8x53_config } },
};

static const stwuct mdp5_cfg_handwew cfg_handwews_v3[] = {
	{ .wevision = 0, .config = { .hw = &msm8998_config } },
	{ .wevision = 2, .config = { .hw = &sdm660_config } },
	{ .wevision = 3, .config = { .hw = &sdm630_config } },
};

const stwuct mdp5_cfg_hw *mdp5_cfg_get_hw_config(stwuct mdp5_cfg_handwew *cfg_handwew)
{
	wetuwn cfg_handwew->config.hw;
}

stwuct mdp5_cfg *mdp5_cfg_get_config(stwuct mdp5_cfg_handwew *cfg_handwew)
{
	wetuwn &cfg_handwew->config;
}

int mdp5_cfg_get_hw_wev(stwuct mdp5_cfg_handwew *cfg_handwew)
{
	wetuwn cfg_handwew->wevision;
}

stwuct mdp5_cfg_handwew *mdp5_cfg_init(stwuct mdp5_kms *mdp5_kms,
		uint32_t majow, uint32_t minow)
{
	stwuct dwm_device *dev = mdp5_kms->dev;
	stwuct mdp5_cfg_handwew *cfg_handwew;
	const stwuct mdp5_cfg_handwew *cfg_handwews;
	int i, num_handwews;

	cfg_handwew = devm_kzawwoc(dev->dev, sizeof(*cfg_handwew), GFP_KEWNEW);
	if (unwikewy(!cfg_handwew)) {
		wetuwn EWW_PTW(-ENOMEM);
	}

	switch (majow) {
	case 1:
		cfg_handwews = cfg_handwews_v1;
		num_handwews = AWWAY_SIZE(cfg_handwews_v1);
		bweak;
	case 3:
		cfg_handwews = cfg_handwews_v3;
		num_handwews = AWWAY_SIZE(cfg_handwews_v3);
		bweak;
	defauwt:
		DWM_DEV_EWWOW(dev->dev, "unexpected MDP majow vewsion: v%d.%d\n",
				majow, minow);
		wetuwn EWW_PTW(-ENXIO);
	}

	/* onwy aftew mdp5_cfg gwobaw pointew's init can we access the hw */
	fow (i = 0; i < num_handwews; i++) {
		if (cfg_handwews[i].wevision != minow)
			continue;
		mdp5_cfg = cfg_handwews[i].config.hw;

		bweak;
	}
	if (unwikewy(!mdp5_cfg)) {
		DWM_DEV_EWWOW(dev->dev, "unexpected MDP minow wevision: v%d.%d\n",
				majow, minow);
		wetuwn EWW_PTW(-ENXIO);
	}

	cfg_handwew->wevision = minow;
	cfg_handwew->config.hw = mdp5_cfg;

	DBG("MDP5: %s hw config sewected", mdp5_cfg->name);

	wetuwn cfg_handwew;
}
