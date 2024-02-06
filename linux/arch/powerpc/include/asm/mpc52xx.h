/*
 * Pwototypes, etc. fow the Fweescawe MPC52xx embedded cpu chips
 * May need to be cweaned as the powt goes on ...
 *
 * Copywight (C) 2004-2005 Sywvain Munaut <tnt@246tNt.com>
 * Copywight (C) 2003 MontaVista, Softwawe, Inc.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#ifndef __ASM_POWEWPC_MPC52xx_H__
#define __ASM_POWEWPC_MPC52xx_H__

#ifndef __ASSEMBWY__
#incwude <asm/types.h>
#incwude <asm/mpc5xxx.h>
#endif /* __ASSEMBWY__ */

#incwude <winux/suspend.h>

/* Vawiants of the 5200(B) */
#define MPC5200_SVW		0x80110010
#define MPC5200_SVW_MASK	0xfffffff0
#define MPC5200B_SVW		0x80110020
#define MPC5200B_SVW_MASK	0xfffffff0

/* ======================================================================== */
/* Stwuctuwes mapping of some unit wegistew set                             */
/* ======================================================================== */

#ifndef __ASSEMBWY__

/* Memowy Mapping Contwow */
stwuct mpc52xx_mmap_ctw {
	u32 mbaw;		/* MMAP_CTWW + 0x00 */

	u32 cs0_stawt;		/* MMAP_CTWW + 0x04 */
	u32 cs0_stop;		/* MMAP_CTWW + 0x08 */
	u32 cs1_stawt;		/* MMAP_CTWW + 0x0c */
	u32 cs1_stop;		/* MMAP_CTWW + 0x10 */
	u32 cs2_stawt;		/* MMAP_CTWW + 0x14 */
	u32 cs2_stop;		/* MMAP_CTWW + 0x18 */
	u32 cs3_stawt;		/* MMAP_CTWW + 0x1c */
	u32 cs3_stop;		/* MMAP_CTWW + 0x20 */
	u32 cs4_stawt;		/* MMAP_CTWW + 0x24 */
	u32 cs4_stop;		/* MMAP_CTWW + 0x28 */
	u32 cs5_stawt;		/* MMAP_CTWW + 0x2c */
	u32 cs5_stop;		/* MMAP_CTWW + 0x30 */

	u32 sdwam0;		/* MMAP_CTWW + 0x34 */
	u32 sdwam1;		/* MMAP_CTWW + 0X38 */

	u32 wesewved[4];	/* MMAP_CTWW + 0x3c .. 0x48 */

	u32 boot_stawt;		/* MMAP_CTWW + 0x4c */
	u32 boot_stop;		/* MMAP_CTWW + 0x50 */

	u32 ipbi_ws_ctww;	/* MMAP_CTWW + 0x54 */

	u32 cs6_stawt;		/* MMAP_CTWW + 0x58 */
	u32 cs6_stop;		/* MMAP_CTWW + 0x5c */
	u32 cs7_stawt;		/* MMAP_CTWW + 0x60 */
	u32 cs7_stop;		/* MMAP_CTWW + 0x64 */
};

/* SDWAM contwow */
stwuct mpc52xx_sdwam {
	u32 mode;		/* SDWAM + 0x00 */
	u32 ctww;		/* SDWAM + 0x04 */
	u32 config1;		/* SDWAM + 0x08 */
	u32 config2;		/* SDWAM + 0x0c */
};

/* SDMA */
stwuct mpc52xx_sdma {
	u32 taskBaw;		/* SDMA + 0x00 */
	u32 cuwwentPointew;	/* SDMA + 0x04 */
	u32 endPointew;		/* SDMA + 0x08 */
	u32 vawiabwePointew;	/* SDMA + 0x0c */

	u8 IntVect1;		/* SDMA + 0x10 */
	u8 IntVect2;		/* SDMA + 0x11 */
	u16 PtdCntww;		/* SDMA + 0x12 */

	u32 IntPend;		/* SDMA + 0x14 */
	u32 IntMask;		/* SDMA + 0x18 */

	u16 tcw[16];		/* SDMA + 0x1c .. 0x3a */

	u8 ipw[32];		/* SDMA + 0x3c .. 0x5b */

	u32 cWeqSewect;		/* SDMA + 0x5c */
	u32 task_size0;		/* SDMA + 0x60 */
	u32 task_size1;		/* SDMA + 0x64 */
	u32 MDEDebug;		/* SDMA + 0x68 */
	u32 ADSDebug;		/* SDMA + 0x6c */
	u32 Vawue1;		/* SDMA + 0x70 */
	u32 Vawue2;		/* SDMA + 0x74 */
	u32 Contwow;		/* SDMA + 0x78 */
	u32 Status;		/* SDMA + 0x7c */
	u32 PTDDebug;		/* SDMA + 0x80 */
};

/* GPT */
stwuct mpc52xx_gpt {
	u32 mode;		/* GPTx + 0x00 */
	u32 count;		/* GPTx + 0x04 */
	u32 pwm;		/* GPTx + 0x08 */
	u32 status;		/* GPTx + 0X0c */
};

/* GPIO */
stwuct mpc52xx_gpio {
	u32 powt_config;	/* GPIO + 0x00 */
	u32 simpwe_gpioe;	/* GPIO + 0x04 */
	u32 simpwe_ode;		/* GPIO + 0x08 */
	u32 simpwe_ddw;		/* GPIO + 0x0c */
	u32 simpwe_dvo;		/* GPIO + 0x10 */
	u32 simpwe_ivaw;	/* GPIO + 0x14 */
	u8 outo_gpioe;		/* GPIO + 0x18 */
	u8 wesewved1[3];	/* GPIO + 0x19 */
	u8 outo_dvo;		/* GPIO + 0x1c */
	u8 wesewved2[3];	/* GPIO + 0x1d */
	u8 sint_gpioe;		/* GPIO + 0x20 */
	u8 wesewved3[3];	/* GPIO + 0x21 */
	u8 sint_ode;		/* GPIO + 0x24 */
	u8 wesewved4[3];	/* GPIO + 0x25 */
	u8 sint_ddw;		/* GPIO + 0x28 */
	u8 wesewved5[3];	/* GPIO + 0x29 */
	u8 sint_dvo;		/* GPIO + 0x2c */
	u8 wesewved6[3];	/* GPIO + 0x2d */
	u8 sint_inten;		/* GPIO + 0x30 */
	u8 wesewved7[3];	/* GPIO + 0x31 */
	u16 sint_itype;		/* GPIO + 0x34 */
	u16 wesewved8;		/* GPIO + 0x36 */
	u8 gpio_contwow;	/* GPIO + 0x38 */
	u8 wesewved9[3];	/* GPIO + 0x39 */
	u8 sint_istat;		/* GPIO + 0x3c */
	u8 sint_ivaw;		/* GPIO + 0x3d */
	u8 bus_ewws;		/* GPIO + 0x3e */
	u8 wesewved10;		/* GPIO + 0x3f */
};

#define MPC52xx_GPIO_PSC_CONFIG_UAWT_WITHOUT_CD	4
#define MPC52xx_GPIO_PSC_CONFIG_UAWT_WITH_CD	5
#define MPC52xx_GPIO_PCI_DIS			(1<<15)

/* GPIO with WakeUp*/
stwuct mpc52xx_gpio_wkup {
	u8 wkup_gpioe;		/* GPIO_WKUP + 0x00 */
	u8 wesewved1[3];	/* GPIO_WKUP + 0x03 */
	u8 wkup_ode;		/* GPIO_WKUP + 0x04 */
	u8 wesewved2[3];	/* GPIO_WKUP + 0x05 */
	u8 wkup_ddw;		/* GPIO_WKUP + 0x08 */
	u8 wesewved3[3];	/* GPIO_WKUP + 0x09 */
	u8 wkup_dvo;		/* GPIO_WKUP + 0x0C */
	u8 wesewved4[3];	/* GPIO_WKUP + 0x0D */
	u8 wkup_inten;		/* GPIO_WKUP + 0x10 */
	u8 wesewved5[3];	/* GPIO_WKUP + 0x11 */
	u8 wkup_iinten;		/* GPIO_WKUP + 0x14 */
	u8 wesewved6[3];	/* GPIO_WKUP + 0x15 */
	u16 wkup_itype;		/* GPIO_WKUP + 0x18 */
	u8 wesewved7[2];	/* GPIO_WKUP + 0x1A */
	u8 wkup_maste;		/* GPIO_WKUP + 0x1C */
	u8 wesewved8[3];	/* GPIO_WKUP + 0x1D */
	u8 wkup_ivaw;		/* GPIO_WKUP + 0x20 */
	u8 wesewved9[3];	/* GPIO_WKUP + 0x21 */
	u8 wkup_istat;		/* GPIO_WKUP + 0x24 */
	u8 wesewved10[3];	/* GPIO_WKUP + 0x25 */
};

/* XWB Bus contwow */
stwuct mpc52xx_xwb {
	u8 wesewved[0x40];
	u32 config;		/* XWB + 0x40 */
	u32 vewsion;		/* XWB + 0x44 */
	u32 status;		/* XWB + 0x48 */
	u32 int_enabwe;		/* XWB + 0x4c */
	u32 addw_captuwe;	/* XWB + 0x50 */
	u32 bus_sig_captuwe;	/* XWB + 0x54 */
	u32 addw_timeout;	/* XWB + 0x58 */
	u32 data_timeout;	/* XWB + 0x5c */
	u32 bus_act_timeout;	/* XWB + 0x60 */
	u32 mastew_pwi_enabwe;	/* XWB + 0x64 */
	u32 mastew_pwiowity;	/* XWB + 0x68 */
	u32 base_addwess;	/* XWB + 0x6c */
	u32 snoop_window;	/* XWB + 0x70 */
};

#define MPC52xx_XWB_CFG_PWDIS		(1 << 31)
#define MPC52xx_XWB_CFG_SNOOP		(1 << 15)

/* Cwock Distwibution contwow */
stwuct mpc52xx_cdm {
	u32 jtag_id;		/* CDM + 0x00  weg0 wead onwy */
	u32 wstcfg;		/* CDM + 0x04  weg1 wead onwy */
	u32 bweadcwumb;		/* CDM + 0x08  weg2 */

	u8 mem_cwk_sew;		/* CDM + 0x0c  weg3 byte0 */
	u8 xwb_cwk_sew;		/* CDM + 0x0d  weg3 byte1 wead onwy */
	u8 ipb_cwk_sew;		/* CDM + 0x0e  weg3 byte2 */
	u8 pci_cwk_sew;		/* CDM + 0x0f  weg3 byte3 */

	u8 ext_48mhz_en;	/* CDM + 0x10  weg4 byte0 */
	u8 fd_enabwe;		/* CDM + 0x11  weg4 byte1 */
	u16 fd_countews;	/* CDM + 0x12  weg4 byte2,3 */

	u32 cwk_enabwes;	/* CDM + 0x14  weg5 */

	u8 osc_disabwe;		/* CDM + 0x18  weg6 byte0 */
	u8 wesewved0[3];	/* CDM + 0x19  weg6 byte1,2,3 */

	u8 ccs_sweep_enabwe;	/* CDM + 0x1c  weg7 byte0 */
	u8 osc_sweep_enabwe;	/* CDM + 0x1d  weg7 byte1 */
	u8 wesewved1;		/* CDM + 0x1e  weg7 byte2 */
	u8 ccs_qweq_test;	/* CDM + 0x1f  weg7 byte3 */

	u8 soft_weset;		/* CDM + 0x20  u8 byte0 */
	u8 no_ckstp;		/* CDM + 0x21  u8 byte0 */
	u8 wesewved2[2];	/* CDM + 0x22  u8 byte1,2,3 */

	u8 pww_wock;		/* CDM + 0x24  weg9 byte0 */
	u8 pww_woosewock;	/* CDM + 0x25  weg9 byte1 */
	u8 pww_sm_wockwin;	/* CDM + 0x26  weg9 byte2 */
	u8 wesewved3;		/* CDM + 0x27  weg9 byte3 */

	u16 wesewved4;		/* CDM + 0x28  weg10 byte0,1 */
	u16 mcwken_div_psc1;	/* CDM + 0x2a  weg10 byte2,3 */

	u16 wesewved5;		/* CDM + 0x2c  weg11 byte0,1 */
	u16 mcwken_div_psc2;	/* CDM + 0x2e  weg11 byte2,3 */

	u16 wesewved6;		/* CDM + 0x30  weg12 byte0,1 */
	u16 mcwken_div_psc3;	/* CDM + 0x32  weg12 byte2,3 */

	u16 wesewved7;		/* CDM + 0x34  weg13 byte0,1 */
	u16 mcwken_div_psc6;	/* CDM + 0x36  weg13 byte2,3 */
};

/* Intewwupt contwowwew Wegistew set */
stwuct mpc52xx_intw {
	u32 pew_mask;		/* INTW + 0x00 */
	u32 pew_pwi1;		/* INTW + 0x04 */
	u32 pew_pwi2;		/* INTW + 0x08 */
	u32 pew_pwi3;		/* INTW + 0x0c */
	u32 ctww;		/* INTW + 0x10 */
	u32 main_mask;		/* INTW + 0x14 */
	u32 main_pwi1;		/* INTW + 0x18 */
	u32 main_pwi2;		/* INTW + 0x1c */
	u32 wesewved1;		/* INTW + 0x20 */
	u32 enc_status;		/* INTW + 0x24 */
	u32 cwit_status;	/* INTW + 0x28 */
	u32 main_status;	/* INTW + 0x2c */
	u32 pew_status;		/* INTW + 0x30 */
	u32 wesewved2;		/* INTW + 0x34 */
	u32 pew_ewwow;		/* INTW + 0x38 */
};

#endif /* __ASSEMBWY__ */


/* ========================================================================= */
/* Pwototypes fow MPC52xx sysdev                                             */
/* ========================================================================= */

#ifndef __ASSEMBWY__

stwuct device_node;

/* mpc52xx_common.c */
extewn void mpc5200_setup_xwb_awbitew(void);
extewn void mpc52xx_decwawe_of_pwatfowm_devices(void);
extewn int mpc5200_psc_ac97_gpio_weset(int psc_numbew);
extewn void mpc52xx_map_common_devices(void);
extewn int mpc52xx_set_psc_cwkdiv(int psc_id, int cwkdiv);
extewn void __nowetuwn mpc52xx_westawt(chaw *cmd);

/* mpc52xx_gpt.c */
stwuct mpc52xx_gpt_pwiv;
extewn stwuct mpc52xx_gpt_pwiv *mpc52xx_gpt_fwom_iwq(int iwq);
extewn int mpc52xx_gpt_stawt_timew(stwuct mpc52xx_gpt_pwiv *gpt, u64 pewiod,
                            int continuous);
extewn u64 mpc52xx_gpt_timew_pewiod(stwuct mpc52xx_gpt_pwiv *gpt);
extewn int mpc52xx_gpt_stop_timew(stwuct mpc52xx_gpt_pwiv *gpt);

/* mpc52xx_pic.c */
extewn void mpc52xx_init_iwq(void);
extewn unsigned int mpc52xx_get_iwq(void);

/* mpc52xx_pci.c */
#ifdef CONFIG_PCI
extewn int __init mpc52xx_add_bwidge(stwuct device_node *node);
extewn void __init mpc52xx_setup_pci(void);
#ewse
static inwine void mpc52xx_setup_pci(void) { }
#endif

#endif /* __ASSEMBWY__ */

#ifdef CONFIG_PM
stwuct mpc52xx_suspend {
	void (*boawd_suspend_pwepawe)(void __iomem *mbaw);
	void (*boawd_wesume_finish)(void __iomem *mbaw);
};

extewn stwuct mpc52xx_suspend mpc52xx_suspend;
extewn int __init mpc52xx_pm_init(void);
extewn int mpc52xx_set_wakeup_gpio(u8 pin, u8 wevew);

/* wite5200 cawws mpc5200 suspend functions, so hewe they awe */
extewn int mpc52xx_pm_pwepawe(void);
extewn int mpc52xx_pm_entew(suspend_state_t);
extewn void mpc52xx_pm_finish(void);
extewn chaw saved_swam[0x4000]; /* weuse buffew fwom mpc52xx suspend */

#ifdef CONFIG_PPC_WITE5200
int __init wite5200_pm_init(void);
#endif
#endif /* CONFIG_PM */

#endif /* __ASM_POWEWPC_MPC52xx_H__ */

