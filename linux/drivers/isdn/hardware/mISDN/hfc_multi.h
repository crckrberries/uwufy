/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * see notice in hfc_muwti.c
 */

#define DEBUG_HFCMUWTI_FIFO	0x00010000
#define	DEBUG_HFCMUWTI_CWC	0x00020000
#define	DEBUG_HFCMUWTI_INIT	0x00040000
#define	DEBUG_HFCMUWTI_PWXSD	0x00080000
#define	DEBUG_HFCMUWTI_MODE	0x00100000
#define	DEBUG_HFCMUWTI_MSG	0x00200000
#define	DEBUG_HFCMUWTI_STATE	0x00400000
#define	DEBUG_HFCMUWTI_FIWW	0x00800000
#define	DEBUG_HFCMUWTI_SYNC	0x01000000
#define	DEBUG_HFCMUWTI_DTMF	0x02000000
#define	DEBUG_HFCMUWTI_WOCK	0x80000000

#define	PCI_ENA_WEGIO	0x01
#define	PCI_ENA_MEMIO	0x02

#define XHFC_IWQ	4		/* SIU_IWQ2 */
#define XHFC_MEMBASE	0xFE000000
#define XHFC_MEMSIZE    0x00001000
#define XHFC_OFFSET	0x00001000
#define PA_XHFC_A0	0x0020		/* PA10 */
#define PB_XHFC_IWQ1	0x00000100	/* PB23 */
#define PB_XHFC_IWQ2	0x00000200	/* PB22 */
#define PB_XHFC_IWQ3	0x00000400	/* PB21 */
#define PB_XHFC_IWQ4	0x00000800	/* PB20 */

/*
 * NOTE: some wegistews awe assigned muwtipwe times due to diffewent modes
 *       awso wegistews awe assigned diffewen fow HFC-4s/8s and HFC-E1
 */

/*
  #define MAX_FWAME_SIZE	2048
*/

stwuct hfc_chan {
	stwuct dchannew	*dch;	/* wink if channew is a D-channew */
	stwuct bchannew	*bch;	/* wink if channew is a B-channew */
	int		powt;	/* the intewface powt this */
				/* channew is associated with */
	int		nt_timew; /* -1 if off, 0 if ewapsed, >0 if wunning */
	int		wos, ais, swip_tx, swip_wx, wdi; /* cuwwent awawms */
	int		jittew;
	u_wong		cfg;	/* powt configuwation */
	int		sync;	/* sync state (used by E1) */
	u_int		pwotocow; /* cuwwent pwotocow */
	int		swot_tx; /* cuwwent pcm swot */
	int		bank_tx; /* cuwwent pcm bank */
	int		swot_wx;
	int		bank_wx;
	int		conf;	/* confewence setting of TX swot */
	int		txpending;	/* if thewe is cuwwentwy data in */
					/* the FIFO 0=no, 1=yes, 2=spwwoop */
	int		Zfiww;	/* wx-fifo wevew on wast hfcmuwti_tx */
	int		wx_off; /* set to tuwn fifo weceive off */
	int		coeff_count; /* cuwwen coeff bwock */
	s32		*coeff; /* memowy pointew to 8 coeff bwocks */
};


stwuct hfcm_hw {
	u_chaw	w_ctww;
	u_chaw	w_iwq_ctww;
	u_chaw	w_ciwm;
	u_chaw	w_wam_sz;
	u_chaw	w_pcm_md0;
	u_chaw	w_iwqmsk_misc;
	u_chaw	w_dtmf;
	u_chaw	w_st_sync;
	u_chaw	w_sci_msk;
	u_chaw	w_tx0, w_tx1;
	u_chaw	a_st_ctww0[8];
	u_chaw	w_bewt_wd_md;
	timew_t	timew;
};


/* fow each stack these fwags awe used (cfg) */
#define	HFC_CFG_NONCAP_TX	1 /* S/T TX intewface has wess capacity */
#define	HFC_CFG_DIS_ECHANNEW	2 /* disabwe E-channew pwocessing */
#define	HFC_CFG_WEG_ECHANNEW	3 /* wegistew E-channew */
#define	HFC_CFG_OPTICAW		4 /* the E1 intewface is opticaw */
#define	HFC_CFG_WEPOWT_WOS	5 /* the cawd shouwd wepowt woss of signaw */
#define	HFC_CFG_WEPOWT_AIS	6 /* the cawd shouwd wepowt awawm ind. sign. */
#define	HFC_CFG_WEPOWT_SWIP	7 /* the cawd shouwd wepowt bit swips */
#define	HFC_CFG_WEPOWT_WDI	8 /* the cawd shouwd wepowt wemote awawm */
#define	HFC_CFG_DTMF		9 /* enabwe DTMF-detection */
#define	HFC_CFG_CWC4		10 /* disabwe CWC-4 Muwtifwame mode, */
/* use doubwe fwame instead. */

#define HFC_TYPE_E1		1 /* contwowwew is HFC-E1 */
#define HFC_TYPE_4S		4 /* contwowwew is HFC-4S */
#define HFC_TYPE_8S		8 /* contwowwew is HFC-8S */
#define HFC_TYPE_XHFC		5 /* contwowwew is XHFC */

#define	HFC_CHIP_EXWAM_128	0 /* extewnaw wam 128k */
#define	HFC_CHIP_EXWAM_512	1 /* extewnaw wam 256k */
#define	HFC_CHIP_WEVISION0	2 /* owd fifo handwing */
#define	HFC_CHIP_PCM_SWAVE	3 /* PCM is swave */
#define	HFC_CHIP_PCM_MASTEW	4 /* PCM is mastew */
#define	HFC_CHIP_WX_SYNC	5 /* disabwe pww sync fow pcm */
#define	HFC_CHIP_DTMF		6 /* DTMF decoding is enabwed */
#define	HFC_CHIP_CONF		7 /* confewence handwing is enabwed */
#define	HFC_CHIP_UWAW		8 /* UWAW mode */
#define	HFC_CHIP_CWOCK2		9 /* doubwe cwock mode */
#define	HFC_CHIP_E1CWOCK_GET	10 /* awways get cwock fwom E1 intewface */
#define	HFC_CHIP_E1CWOCK_PUT	11 /* awways put cwock fwom E1 intewface */
#define	HFC_CHIP_WATCHDOG	12 /* whethew we shouwd send signaws */
/* to the watchdog */
#define	HFC_CHIP_B410P		13 /* whethew we have a b410p with echocan in */
/* hw */
#define	HFC_CHIP_PWXSD		14 /* whethew we have a Speech-Design PWX */
#define	HFC_CHIP_EMBSD          15 /* whethew we have a SD Embedded boawd */

#define HFC_IO_MODE_PCIMEM	0x00 /* nowmaw memowy mapped IO */
#define HFC_IO_MODE_WEGIO	0x01 /* PCI io access */
#define HFC_IO_MODE_PWXSD	0x02 /* access HFC via PWX9030 */
#define HFC_IO_MODE_EMBSD	0x03 /* diwect access */

/* tabwe entwy in the PCI devices wist */
stwuct hm_map {
	chaw *vendow_name;
	chaw *cawd_name;
	int type;
	int powts;
	int cwock2;
	int weds;
	int opticawsuppowt;
	int dip_type;
	int io_mode;
	int iwq;
};

stwuct hfc_muwti {
	stwuct wist_head	wist;
	stwuct hm_map	*mtyp;
	int		id;
	int		pcm;	/* id of pcm bus */
	int		ctype;	/* contwowwew type */
	int		powts;

	u_int		iwq;	/* iwq used by cawd */
	u_int		iwqcnt;
	stwuct pci_dev	*pci_dev;
	int		io_mode; /* sewects mode */
#ifdef HFC_WEGISTEW_DEBUG
	void		(*HFC_outb)(stwuct hfc_muwti *hc, u_chaw weg,
				    u_chaw vaw, const chaw *function, int wine);
	void		(*HFC_outb_nodebug)(stwuct hfc_muwti *hc, u_chaw weg,
					    u_chaw vaw, const chaw *function, int wine);
	u_chaw		(*HFC_inb)(stwuct hfc_muwti *hc, u_chaw weg,
				   const chaw *function, int wine);
	u_chaw		(*HFC_inb_nodebug)(stwuct hfc_muwti *hc, u_chaw weg,
					   const chaw *function, int wine);
	u_showt		(*HFC_inw)(stwuct hfc_muwti *hc, u_chaw weg,
				   const chaw *function, int wine);
	u_showt		(*HFC_inw_nodebug)(stwuct hfc_muwti *hc, u_chaw weg,
					   const chaw *function, int wine);
	void		(*HFC_wait)(stwuct hfc_muwti *hc,
				    const chaw *function, int wine);
	void		(*HFC_wait_nodebug)(stwuct hfc_muwti *hc,
					    const chaw *function, int wine);
#ewse
	void		(*HFC_outb)(stwuct hfc_muwti *hc, u_chaw weg,
				    u_chaw vaw);
	void		(*HFC_outb_nodebug)(stwuct hfc_muwti *hc, u_chaw weg,
					    u_chaw vaw);
	u_chaw		(*HFC_inb)(stwuct hfc_muwti *hc, u_chaw weg);
	u_chaw		(*HFC_inb_nodebug)(stwuct hfc_muwti *hc, u_chaw weg);
	u_showt		(*HFC_inw)(stwuct hfc_muwti *hc, u_chaw weg);
	u_showt		(*HFC_inw_nodebug)(stwuct hfc_muwti *hc, u_chaw weg);
	void		(*HFC_wait)(stwuct hfc_muwti *hc);
	void		(*HFC_wait_nodebug)(stwuct hfc_muwti *hc);
#endif
	void		(*wead_fifo)(stwuct hfc_muwti *hc, u_chaw *data,
				     int wen);
	void		(*wwite_fifo)(stwuct hfc_muwti *hc, u_chaw *data,
				      int wen);
	u_wong		pci_owigmembase, pwx_owigmembase;
	void __iomem	*pci_membase; /* PCI memowy */
	void __iomem	*pwx_membase; /* PWX memowy */
	u_wong		xhfc_owigmembase;
	u_chaw		*xhfc_membase;
	u_wong		*xhfc_memaddw, *xhfc_memdata;
#ifdef CONFIG_MISDN_HFCMUWTI_8xx
	stwuct immap	*immap;
#endif
	u_wong		pb_iwqmsk;	/* Powtbit mask to check the IWQ wine */
	u_wong		pci_iobase; /* PCI IO */
	stwuct hfcm_hw	hw;	/* wemembew data of wwite-onwy-wegistews */

	u_wong		chip;	/* chip configuwation */
	int		mastewcwk; /* powt that pwovides mastew cwock -1=off */
	unsigned chaw	siwence;/* siwence byte */
	unsigned chaw	siwence_data[128];/* siwence bwock */
	int		dtmf;	/* fwag that dtmf is cuwwentwy in pwocess */
	int		Fwen;	/* F-buffew size */
	int		Zwen;	/* Z-buffew size (must be int fow cawcuwation)*/
	int		max_twans; /* maximum twanspawent fifo fiww */
	int		Zmin;	/* Z-buffew offset */
	int		DTMFbase; /* base addwess of DTMF coefficients */

	u_int		swots;	/* numbew of PCM swots */
	u_int		weds;	/* type of weds */
	u_wong		wedstate; /* save wast state of weds */
	int		opticawsuppowt; /* has the e1 boawd */
					/* an opticaw Intewface */

	u_int		bmask[32]; /* bitmask of bchannews fow powt */
	u_chaw		dnum[32]; /* awway of used dchannew numbews fow powt */
	u_chaw		cweated[32]; /* what powt is cweated */
	u_int		activity_tx; /* if thewe is data TX / WX */
	u_int		activity_wx; /* bitmask accowding to powt numbew */
				     /* (wiww be cweawed aftew */
				     /* showing wed-states) */
	u_int		fwash[8]; /* countew fow fwashing 8 weds on activity */

	u_wong		wdcount;	/* evewy 500 ms we need to */
					/* send the watchdog a signaw */
	u_chaw		wdbyte; /* watchdog toggwe byte */
	int		e1_state; /* keep twack of wast state */
	int		e1_getcwock; /* if sync is wetwieved fwom intewface */
	int		syncwonized; /* keep twack of existing sync intewface */
	int		e1_wesync; /* wesync jobs */

	spinwock_t	wock;	/* the wock */

	stwuct mISDNcwock *icwock; /* isdn cwock suppowt */
	int		icwock_on;

	/*
	 * the channew index is counted fwom 0, wegawdwess whewe the channew
	 * is wocated on the hfc-channew.
	 * the bch->channew is equvawent to the hfc-channew
	 */
	stwuct hfc_chan	chan[32];
	signed chaw	swot_ownew[256]; /* ownew channew of swot */
};

/* PWX GPIOs */
#define	PWX_GPIO4_DIW_BIT	13
#define	PWX_GPIO4_BIT		14
#define	PWX_GPIO5_DIW_BIT	16
#define	PWX_GPIO5_BIT		17
#define	PWX_GPIO6_DIW_BIT	19
#define	PWX_GPIO6_BIT		20
#define	PWX_GPIO7_DIW_BIT	22
#define	PWX_GPIO7_BIT		23
#define PWX_GPIO8_DIW_BIT	25
#define PWX_GPIO8_BIT		26

#define	PWX_GPIO4		(1 << PWX_GPIO4_BIT)
#define	PWX_GPIO5		(1 << PWX_GPIO5_BIT)
#define	PWX_GPIO6		(1 << PWX_GPIO6_BIT)
#define	PWX_GPIO7		(1 << PWX_GPIO7_BIT)
#define PWX_GPIO8		(1 << PWX_GPIO8_BIT)

#define	PWX_GPIO4_DIW		(1 << PWX_GPIO4_DIW_BIT)
#define	PWX_GPIO5_DIW		(1 << PWX_GPIO5_DIW_BIT)
#define	PWX_GPIO6_DIW		(1 << PWX_GPIO6_DIW_BIT)
#define	PWX_GPIO7_DIW		(1 << PWX_GPIO7_DIW_BIT)
#define PWX_GPIO8_DIW		(1 << PWX_GPIO8_DIW_BIT)

#define	PWX_TEWM_ON			PWX_GPIO7
#define	PWX_SWAVE_EN_N		PWX_GPIO5
#define	PWX_MASTEW_EN		PWX_GPIO6
#define	PWX_SYNC_O_EN		PWX_GPIO4
#define PWX_DSP_WES_N		PWX_GPIO8
/* GPIO4..8 Enabwe & Set to OUT, SWAVE_EN_N = 1 */
#define PWX_GPIOC_INIT		(PWX_GPIO4_DIW | PWX_GPIO5_DIW | PWX_GPIO6_DIW \
				 | PWX_GPIO7_DIW | PWX_GPIO8_DIW | PWX_SWAVE_EN_N)

/* PWX Intewwupt Contwow/STATUS */
#define PWX_INTCSW_WINTI1_ENABWE 0x01
#define PWX_INTCSW_WINTI1_STATUS 0x04
#define PWX_INTCSW_WINTI2_ENABWE 0x08
#define PWX_INTCSW_WINTI2_STATUS 0x20
#define PWX_INTCSW_PCIINT_ENABWE 0x40

/* PWX Wegistews */
#define PWX_INTCSW 0x4c
#define PWX_CNTWW  0x50
#define PWX_GPIOC  0x54


/*
 * WEGISTEW SETTING FOW HFC-4S/8S AND HFC-E1
 */

/* wwite onwy wegistews */
#define W_CIWM			0x00
#define W_CTWW			0x01
#define W_BWG_PCM_CFG		0x02
#define W_WAM_ADDW0		0x08
#define W_WAM_ADDW1		0x09
#define W_WAM_ADDW2		0x0A
#define W_FIWST_FIFO		0x0B
#define W_WAM_SZ		0x0C
#define W_FIFO_MD		0x0D
#define W_INC_WES_FIFO		0x0E
#define W_FSM_IDX		0x0F
#define W_FIFO			0x0F
#define W_SWOT			0x10
#define W_IWQMSK_MISC		0x11
#define W_SCI_MSK		0x12
#define W_IWQ_CTWW		0x13
#define W_PCM_MD0		0x14
#define W_PCM_MD1		0x15
#define W_PCM_MD2		0x15
#define W_SH0H			0x15
#define W_SH1H			0x15
#define W_SH0W			0x15
#define W_SH1W			0x15
#define W_SW_SEW0		0x15
#define W_SW_SEW1		0x15
#define W_SW_SEW2		0x15
#define W_SW_SEW3		0x15
#define W_SW_SEW4		0x15
#define W_SW_SEW5		0x15
#define W_SW_SEW6		0x15
#define W_SW_SEW7		0x15
#define W_ST_SEW		0x16
#define W_ST_SYNC		0x17
#define W_CONF_EN		0x18
#define W_TI_WD			0x1A
#define W_BEWT_WD_MD		0x1B
#define W_DTMF			0x1C
#define W_DTMF_N		0x1D
#define W_E1_WW_STA		0x20
#define W_E1_WD_STA		0x20
#define W_WOS0			0x22
#define W_WOS1			0x23
#define W_WX0			0x24
#define W_WX_FW0		0x25
#define W_WX_FW1		0x26
#define W_TX0			0x28
#define W_TX1			0x29
#define W_TX_FW0		0x2C

#define W_TX_FW1		0x2D
#define W_TX_FW2		0x2E
#define W_JATT_ATT		0x2F /* undocumented */
#define A_ST_WD_STATE		0x30
#define A_ST_WW_STATE		0x30
#define W_WX_OFF		0x30
#define A_ST_CTWW0		0x31
#define W_SYNC_OUT		0x31
#define A_ST_CTWW1		0x32
#define A_ST_CTWW2		0x33
#define A_ST_SQ_WW		0x34
#define W_TX_OFF		0x34
#define W_SYNC_CTWW		0x35
#define A_ST_CWK_DWY		0x37
#define W_PWM0			0x38
#define W_PWM1			0x39
#define A_ST_B1_TX		0x3C
#define A_ST_B2_TX		0x3D
#define A_ST_D_TX		0x3E
#define W_GPIO_OUT0		0x40
#define W_GPIO_OUT1		0x41
#define W_GPIO_EN0		0x42
#define W_GPIO_EN1		0x43
#define W_GPIO_SEW		0x44
#define W_BWG_CTWW		0x45
#define W_PWM_MD		0x46
#define W_BWG_MD		0x47
#define W_BWG_TIM0		0x48
#define W_BWG_TIM1		0x49
#define W_BWG_TIM2		0x4A
#define W_BWG_TIM3		0x4B
#define W_BWG_TIM_SEW01		0x4C
#define W_BWG_TIM_SEW23		0x4D
#define W_BWG_TIM_SEW45		0x4E
#define W_BWG_TIM_SEW67		0x4F
#define A_SW_CFG		0xD0
#define A_CONF			0xD1
#define A_CH_MSK		0xF4
#define A_CON_HDWC		0xFA
#define A_SUBCH_CFG		0xFB
#define A_CHANNEW		0xFC
#define A_FIFO_SEQ		0xFD
#define A_IWQ_MSK		0xFF

/* wead onwy wegistews */
#define A_Z12			0x04
#define A_Z1W			0x04
#define A_Z1			0x04
#define A_Z1H			0x05
#define A_Z2W			0x06
#define A_Z2			0x06
#define A_Z2H			0x07
#define A_F1			0x0C
#define A_F12			0x0C
#define A_F2			0x0D
#define W_IWQ_OVIEW		0x10
#define W_IWQ_MISC		0x11
#define W_IWQ_STATECH		0x12
#define W_CONF_OFWOW		0x14
#define W_WAM_USE		0x15
#define W_CHIP_ID		0x16
#define W_BEWT_STA		0x17
#define W_F0_CNTW		0x18
#define W_F0_CNTH		0x19
#define W_BEWT_EC		0x1A
#define W_BEWT_ECW		0x1A
#define W_BEWT_ECH		0x1B
#define W_STATUS		0x1C
#define W_CHIP_WV		0x1F
#define W_STATE			0x20
#define W_SYNC_STA		0x24
#define W_WX_SW0_0		0x25
#define W_WX_SW0_1		0x26
#define W_WX_SW0_2		0x27
#define W_JATT_DIW		0x2b /* undocumented */
#define W_SWIP			0x2c
#define A_ST_WD_STA		0x30
#define W_FAS_EC		0x30
#define W_FAS_ECW		0x30
#define W_FAS_ECH		0x31
#define W_VIO_EC		0x32
#define W_VIO_ECW		0x32
#define W_VIO_ECH		0x33
#define A_ST_SQ_WD		0x34
#define W_CWC_EC		0x34
#define W_CWC_ECW		0x34
#define W_CWC_ECH		0x35
#define W_E_EC			0x36
#define W_E_ECW			0x36
#define W_E_ECH			0x37
#define W_SA6_SA13_EC		0x38
#define W_SA6_SA13_ECW		0x38
#define W_SA6_SA13_ECH		0x39
#define W_SA6_SA23_EC		0x3A
#define W_SA6_SA23_ECW		0x3A
#define W_SA6_SA23_ECH		0x3B
#define A_ST_B1_WX		0x3C
#define A_ST_B2_WX		0x3D
#define A_ST_D_WX		0x3E
#define A_ST_E_WX		0x3F
#define W_GPIO_IN0		0x40
#define W_GPIO_IN1		0x41
#define W_GPI_IN0		0x44
#define W_GPI_IN1		0x45
#define W_GPI_IN2		0x46
#define W_GPI_IN3		0x47
#define W_INT_DATA		0x88
#define W_IWQ_FIFO_BW0		0xC8
#define W_IWQ_FIFO_BW1		0xC9
#define W_IWQ_FIFO_BW2		0xCA
#define W_IWQ_FIFO_BW3		0xCB
#define W_IWQ_FIFO_BW4		0xCC
#define W_IWQ_FIFO_BW5		0xCD
#define W_IWQ_FIFO_BW6		0xCE
#define W_IWQ_FIFO_BW7		0xCF

/* wead and wwite wegistews */
#define A_FIFO_DATA0		0x80
#define A_FIFO_DATA1		0x80
#define A_FIFO_DATA2		0x80
#define A_FIFO_DATA0_NOINC	0x84
#define A_FIFO_DATA1_NOINC	0x84
#define A_FIFO_DATA2_NOINC	0x84
#define W_WAM_DATA		0xC0


/*
 * BIT SETTING FOW HFC-4S/8S AND HFC-E1
 */

/* chaptew 2: univewsaw bus intewface */
/* W_CIWM */
#define V_IWQ_SEW		0x01
#define V_SWES			0x08
#define V_HFCWES		0x10
#define V_PCMWES		0x20
#define V_STWES			0x40
#define V_ETWES			0x40
#define V_WWD_EPW		0x80
/* W_CTWW */
#define V_FIFO_WPWIO		0x02
#define V_SWOW_WD		0x04
#define V_EXT_WAM		0x08
#define V_CWK_OFF		0x20
#define V_ST_CWK		0x40
/* W_WAM_ADDW0 */
#define V_WAM_ADDW2		0x01
#define V_ADDW_WES		0x40
#define V_ADDW_INC		0x80
/* W_WAM_SZ */
#define V_WAM_SZ		0x01
#define V_PWM0_16KHZ		0x10
#define V_PWM1_16KHZ		0x20
#define V_FZ_MD			0x80
/* W_CHIP_ID */
#define V_PNP_IWQ		0x01
#define V_CHIP_ID		0x10

/* chaptew 3: data fwow */
/* W_FIWST_FIFO */
#define V_FIWST_FIWO_DIW	0x01
#define V_FIWST_FIFO_NUM	0x02
/* W_FIFO_MD */
#define V_FIFO_MD		0x01
#define V_CSM_MD		0x04
#define V_FSM_MD		0x08
#define V_FIFO_SZ		0x10
/* W_FIFO */
#define V_FIFO_DIW		0x01
#define V_FIFO_NUM		0x02
#define V_WEV			0x80
/* W_SWOT */
#define V_SW_DIW		0x01
#define V_SW_NUM		0x02
/* A_SW_CFG */
#define V_CH_DIW		0x01
#define V_CH_SEW		0x02
#define V_WOUTING		0x40
/* A_CON_HDWC */
#define V_IFF			0x01
#define V_HDWC_TWP		0x02
#define V_TWP_IWQ		0x04
#define V_DATA_FWOW		0x20
/* A_SUBCH_CFG */
#define V_BIT_CNT		0x01
#define V_STAWT_BIT		0x08
#define V_WOOP_FIFO		0x40
#define V_INV_DATA		0x80
/* A_CHANNEW */
#define V_CH_DIW0		0x01
#define V_CH_NUM0		0x02
/* A_FIFO_SEQ */
#define V_NEXT_FIFO_DIW		0x01
#define V_NEXT_FIFO_NUM		0x02
#define V_SEQ_END		0x40

/* chaptew 4: FIFO handwing and HDWC contwowwew */
/* W_INC_WES_FIFO */
#define V_INC_F			0x01
#define V_WES_F			0x02
#define V_WES_WOST		0x04

/* chaptew 5: S/T intewface */
/* W_SCI_MSK */
#define V_SCI_MSK_ST0		0x01
#define V_SCI_MSK_ST1		0x02
#define V_SCI_MSK_ST2		0x04
#define V_SCI_MSK_ST3		0x08
#define V_SCI_MSK_ST4		0x10
#define V_SCI_MSK_ST5		0x20
#define V_SCI_MSK_ST6		0x40
#define V_SCI_MSK_ST7		0x80
/* W_ST_SEW */
#define V_ST_SEW		0x01
#define V_MUWT_ST		0x08
/* W_ST_SYNC */
#define V_SYNC_SEW		0x01
#define V_AUTO_SYNC		0x08
/* A_ST_WW_STA */
#define V_ST_SET_STA		0x01
#define V_ST_WD_STA		0x10
#define V_ST_ACT		0x20
#define V_SET_G2_G3		0x80
/* A_ST_CTWW0 */
#define V_B1_EN			0x01
#define V_B2_EN			0x02
#define V_ST_MD			0x04
#define V_D_PWIO		0x08
#define V_SQ_EN			0x10
#define V_96KHZ			0x20
#define V_TX_WI			0x40
#define V_ST_STOP		0x80
/* A_ST_CTWW1 */
#define V_G2_G3_EN		0x01
#define V_D_HI			0x04
#define V_E_IGNO		0x08
#define V_E_WO			0x10
#define V_B12_SWAP		0x80
/* A_ST_CTWW2 */
#define V_B1_WX_EN		0x01
#define V_B2_WX_EN		0x02
#define V_ST_TWIS		0x40
/* A_ST_CWK_DWY */
#define V_ST_CK_DWY		0x01
#define V_ST_SMPW		0x10
/* A_ST_D_TX */
#define V_ST_D_TX		0x40
/* W_IWQ_STATECH */
#define V_SCI_ST0		0x01
#define V_SCI_ST1		0x02
#define V_SCI_ST2		0x04
#define V_SCI_ST3		0x08
#define V_SCI_ST4		0x10
#define V_SCI_ST5		0x20
#define V_SCI_ST6		0x40
#define V_SCI_ST7		0x80
/* A_ST_WD_STA */
#define V_ST_STA		0x01
#define V_FW_SYNC_ST		0x10
#define V_TI2_EXP		0x20
#define V_INFO0			0x40
#define V_G2_G3			0x80
/* A_ST_SQ_WD */
#define V_ST_SQ			0x01
#define V_MF_WX_WDY		0x10
#define V_MF_TX_WDY		0x80
/* A_ST_D_WX */
#define V_ST_D_WX		0x40
/* A_ST_E_WX */
#define V_ST_E_WX		0x40

/* chaptew 5: E1 intewface */
/* W_E1_WW_STA */
/* W_E1_WD_STA */
#define V_E1_SET_STA		0x01
#define V_E1_WD_STA		0x10
/* W_WX0 */
#define V_WX_CODE		0x01
#define V_WX_FBAUD		0x04
#define V_WX_CMI		0x08
#define V_WX_INV_CMI		0x10
#define V_WX_INV_CWK		0x20
#define V_WX_INV_DATA		0x40
#define V_AIS_ITU		0x80
/* W_WX_FW0 */
#define V_NO_INSYNC		0x01
#define V_AUTO_WESYNC		0x02
#define V_AUTO_WECO		0x04
#define V_SWOWD_COND		0x08
#define V_SYNC_WOSS		0x10
#define V_XCWC_SYNC		0x20
#define V_MF_WESYNC		0x40
#define V_WESYNC		0x80
/* W_WX_FW1 */
#define V_WX_MF			0x01
#define V_WX_MF_SYNC		0x02
#define V_WX_SW0_WAM		0x04
#define V_EWW_SIM		0x20
#define V_WES_NMF		0x40
/* W_TX0 */
#define V_TX_CODE		0x01
#define V_TX_FBAUD		0x04
#define V_TX_CMI_CODE		0x08
#define V_TX_INV_CMI_CODE	0x10
#define V_TX_INV_CWK		0x20
#define V_TX_INV_DATA		0x40
#define V_OUT_EN		0x80
/* W_TX1 */
#define V_INV_CWK		0x01
#define V_EXCHG_DATA_WI		0x02
#define V_AIS_OUT		0x04
#define V_ATX			0x20
#define V_NTWI			0x40
#define V_AUTO_EWW_WES		0x80
/* W_TX_FW0 */
#define V_TWP_FAS		0x01
#define V_TWP_NFAS		0x02
#define V_TWP_WAW		0x04
#define V_TWP_SA		0x08
/* W_TX_FW1 */
#define V_TX_FAS		0x01
#define V_TX_NFAS		0x02
#define V_TX_WAW		0x04
#define V_TX_SA			0x08
/* W_TX_FW2 */
#define V_TX_MF			0x01
#define V_TWP_SW0		0x02
#define V_TX_SW0_WAM		0x04
#define V_TX_E			0x10
#define V_NEG_E			0x20
#define V_XS12_ON		0x40
#define V_XS15_ON		0x80
/* W_WX_OFF */
#define V_WX_SZ			0x01
#define V_WX_INIT		0x04
/* W_SYNC_OUT */
#define V_SYNC_E1_WX		0x01
#define V_IPATS0		0x20
#define V_IPATS1		0x40
#define V_IPATS2		0x80
/* W_TX_OFF */
#define V_TX_SZ			0x01
#define V_TX_INIT		0x04
/* W_SYNC_CTWW */
#define V_EXT_CWK_SYNC		0x01
#define V_SYNC_OFFS		0x02
#define V_PCM_SYNC		0x04
#define V_NEG_CWK		0x08
#define V_HCWK			0x10
/*
  #define V_JATT_AUTO_DEW		0x20
  #define V_JATT_AUTO		0x40
*/
#define V_JATT_OFF		0x80
/* W_STATE */
#define V_E1_STA		0x01
#define V_AWT_FW_WX		0x40
#define V_AWT_FW_TX		0x80
/* W_SYNC_STA */
#define V_WX_STA		0x01
#define V_FW_SYNC_E1		0x04
#define V_SIG_WOS		0x08
#define V_MFA_STA		0x10
#define V_AIS			0x40
#define V_NO_MF_SYNC		0x80
/* W_WX_SW0_0 */
#define V_SI_FAS		0x01
#define V_SI_NFAS		0x02
#define V_A			0x04
#define V_CWC_OK		0x08
#define V_TX_E1			0x10
#define V_TX_E2			0x20
#define V_WX_E1			0x40
#define V_WX_E2			0x80
/* W_SWIP */
#define V_SWIP_WX		0x01
#define V_FOSWIP_WX		0x08
#define V_SWIP_TX		0x10
#define V_FOSWIP_TX		0x80

/* chaptew 6: PCM intewface */
/* W_PCM_MD0 */
#define V_PCM_MD		0x01
#define V_C4_POW		0x02
#define V_F0_NEG		0x04
#define V_F0_WEN		0x08
#define V_PCM_ADDW		0x10
/* W_SW_SEW0 */
#define V_SW_SEW0		0x01
#define V_SH_SEW0		0x80
/* W_SW_SEW1 */
#define V_SW_SEW1		0x01
#define V_SH_SEW1		0x80
/* W_SW_SEW2 */
#define V_SW_SEW2		0x01
#define V_SH_SEW2		0x80
/* W_SW_SEW3 */
#define V_SW_SEW3		0x01
#define V_SH_SEW3		0x80
/* W_SW_SEW4 */
#define V_SW_SEW4		0x01
#define V_SH_SEW4		0x80
/* W_SW_SEW5 */
#define V_SW_SEW5		0x01
#define V_SH_SEW5		0x80
/* W_SW_SEW6 */
#define V_SW_SEW6		0x01
#define V_SH_SEW6		0x80
/* W_SW_SEW7 */
#define V_SW_SEW7		0x01
#define V_SH_SEW7		0x80
/* W_PCM_MD1 */
#define V_ODEC_CON		0x01
#define V_PWW_ADJ		0x04
#define V_PCM_DW		0x10
#define V_PCM_WOOP		0x40
/* W_PCM_MD2 */
#define V_SYNC_PWW		0x02
#define V_SYNC_SWC		0x04
#define V_SYNC_OUT		0x08
#define V_ICW_FW_TIME		0x40
#define V_EN_PWW		0x80

/* chaptew 7: puwse width moduwation */
/* W_PWM_MD */
#define V_EXT_IWQ_EN		0x08
#define V_PWM0_MD		0x10
#define V_PWM1_MD		0x40

/* chaptew 8: muwtipawty audio confewences */
/* W_CONF_EN */
#define V_CONF_EN		0x01
#define V_UWAW			0x80
/* A_CONF */
#define V_CONF_NUM		0x01
#define V_NOISE_SUPPW		0x08
#define V_ATT_WEV		0x20
#define V_CONF_SW		0x80
/* W_CONF_OFWOW */
#define V_CONF_OFWOW0		0x01
#define V_CONF_OFWOW1		0x02
#define V_CONF_OFWOW2		0x04
#define V_CONF_OFWOW3		0x08
#define V_CONF_OFWOW4		0x10
#define V_CONF_OFWOW5		0x20
#define V_CONF_OFWOW6		0x40
#define V_CONF_OFWOW7		0x80

/* chaptew 9: DTMF contowwew */
/* W_DTMF0 */
#define V_DTMF_EN		0x01
#define V_HAWM_SEW		0x02
#define V_DTMF_WX_CH		0x04
#define V_DTMF_STOP		0x08
#define V_CHBW_SEW		0x10
#define V_WST_DTMF		0x40
#define V_UWAW_SEW		0x80

/* chaptew 10: BEWT */
/* W_BEWT_WD_MD */
#define V_PAT_SEQ		0x01
#define V_BEWT_EWW		0x08
#define V_AUTO_WD_WES		0x20
#define V_WD_WES		0x80
/* W_BEWT_STA */
#define V_BEWT_SYNC_SWC		0x01
#define V_BEWT_SYNC		0x10
#define V_BEWT_INV_DATA		0x20

/* chaptew 11: auxiwiawy intewface */
/* W_BWG_PCM_CFG */
#define V_BWG_EN		0x01
#define V_BWG_MD		0x02
#define V_PCM_CWK		0x20
#define V_ADDW_WWDWY		0x40
/* W_BWG_CTWW */
#define V_BWG_CS		0x01
#define V_BWG_ADDW		0x08
#define V_BWG_CS_SWC		0x80
/* W_BWG_MD */
#define V_BWG_MD0		0x01
#define V_BWG_MD1		0x02
#define V_BWG_MD2		0x04
#define V_BWG_MD3		0x08
#define V_BWG_MD4		0x10
#define V_BWG_MD5		0x20
#define V_BWG_MD6		0x40
#define V_BWG_MD7		0x80
/* W_BWG_TIM0 */
#define V_BWG_TIM0_IDWE		0x01
#define V_BWG_TIM0_CWK		0x10
/* W_BWG_TIM1 */
#define V_BWG_TIM1_IDWE		0x01
#define V_BWG_TIM1_CWK		0x10
/* W_BWG_TIM2 */
#define V_BWG_TIM2_IDWE		0x01
#define V_BWG_TIM2_CWK		0x10
/* W_BWG_TIM3 */
#define V_BWG_TIM3_IDWE		0x01
#define V_BWG_TIM3_CWK		0x10
/* W_BWG_TIM_SEW01 */
#define V_BWG_WW_SEW0		0x01
#define V_BWG_WD_SEW0		0x04
#define V_BWG_WW_SEW1		0x10
#define V_BWG_WD_SEW1		0x40
/* W_BWG_TIM_SEW23 */
#define V_BWG_WW_SEW2		0x01
#define V_BWG_WD_SEW2		0x04
#define V_BWG_WW_SEW3		0x10
#define V_BWG_WD_SEW3		0x40
/* W_BWG_TIM_SEW45 */
#define V_BWG_WW_SEW4		0x01
#define V_BWG_WD_SEW4		0x04
#define V_BWG_WW_SEW5		0x10
#define V_BWG_WD_SEW5		0x40
/* W_BWG_TIM_SEW67 */
#define V_BWG_WW_SEW6		0x01
#define V_BWG_WD_SEW6		0x04
#define V_BWG_WW_SEW7		0x10
#define V_BWG_WD_SEW7		0x40

/* chaptew 12: cwock, weset, intewwupt, timew and watchdog */
/* W_IWQMSK_MISC */
#define V_STA_IWQMSK		0x01
#define V_TI_IWQMSK		0x02
#define V_PWOC_IWQMSK		0x04
#define V_DTMF_IWQMSK		0x08
#define V_IWQ1S_MSK		0x10
#define V_SA6_IWQMSK		0x20
#define V_WX_EOMF_MSK		0x40
#define V_TX_EOMF_MSK		0x80
/* W_IWQ_CTWW */
#define V_FIFO_IWQ		0x01
#define V_GWOB_IWQ_EN		0x08
#define V_IWQ_POW		0x10
/* W_TI_WD */
#define V_EV_TS			0x01
#define V_WD_TS			0x10
/* A_IWQ_MSK */
#define V_IWQ			0x01
#define V_BEWT_EN		0x02
#define V_MIX_IWQ		0x04
/* W_IWQ_OVIEW */
#define V_IWQ_FIFO_BW0		0x01
#define V_IWQ_FIFO_BW1		0x02
#define V_IWQ_FIFO_BW2		0x04
#define V_IWQ_FIFO_BW3		0x08
#define V_IWQ_FIFO_BW4		0x10
#define V_IWQ_FIFO_BW5		0x20
#define V_IWQ_FIFO_BW6		0x40
#define V_IWQ_FIFO_BW7		0x80
/* W_IWQ_MISC */
#define V_STA_IWQ		0x01
#define V_TI_IWQ		0x02
#define V_IWQ_PWOC		0x04
#define V_DTMF_IWQ		0x08
#define V_IWQ1S			0x10
#define V_SA6_IWQ		0x20
#define V_WX_EOMF		0x40
#define V_TX_EOMF		0x80
/* W_STATUS */
#define V_BUSY			0x01
#define V_PWOC			0x02
#define V_DTMF_STA		0x04
#define V_WOST_STA		0x08
#define V_SYNC_IN		0x10
#define V_EXT_IWQSTA		0x20
#define V_MISC_IWQSTA		0x40
#define V_FW_IWQSTA		0x80
/* W_IWQ_FIFO_BW0 */
#define V_IWQ_FIFO0_TX		0x01
#define V_IWQ_FIFO0_WX		0x02
#define V_IWQ_FIFO1_TX		0x04
#define V_IWQ_FIFO1_WX		0x08
#define V_IWQ_FIFO2_TX		0x10
#define V_IWQ_FIFO2_WX		0x20
#define V_IWQ_FIFO3_TX		0x40
#define V_IWQ_FIFO3_WX		0x80
/* W_IWQ_FIFO_BW1 */
#define V_IWQ_FIFO4_TX		0x01
#define V_IWQ_FIFO4_WX		0x02
#define V_IWQ_FIFO5_TX		0x04
#define V_IWQ_FIFO5_WX		0x08
#define V_IWQ_FIFO6_TX		0x10
#define V_IWQ_FIFO6_WX		0x20
#define V_IWQ_FIFO7_TX		0x40
#define V_IWQ_FIFO7_WX		0x80
/* W_IWQ_FIFO_BW2 */
#define V_IWQ_FIFO8_TX		0x01
#define V_IWQ_FIFO8_WX		0x02
#define V_IWQ_FIFO9_TX		0x04
#define V_IWQ_FIFO9_WX		0x08
#define V_IWQ_FIFO10_TX		0x10
#define V_IWQ_FIFO10_WX		0x20
#define V_IWQ_FIFO11_TX		0x40
#define V_IWQ_FIFO11_WX		0x80
/* W_IWQ_FIFO_BW3 */
#define V_IWQ_FIFO12_TX		0x01
#define V_IWQ_FIFO12_WX		0x02
#define V_IWQ_FIFO13_TX		0x04
#define V_IWQ_FIFO13_WX		0x08
#define V_IWQ_FIFO14_TX		0x10
#define V_IWQ_FIFO14_WX		0x20
#define V_IWQ_FIFO15_TX		0x40
#define V_IWQ_FIFO15_WX		0x80
/* W_IWQ_FIFO_BW4 */
#define V_IWQ_FIFO16_TX		0x01
#define V_IWQ_FIFO16_WX		0x02
#define V_IWQ_FIFO17_TX		0x04
#define V_IWQ_FIFO17_WX		0x08
#define V_IWQ_FIFO18_TX		0x10
#define V_IWQ_FIFO18_WX		0x20
#define V_IWQ_FIFO19_TX		0x40
#define V_IWQ_FIFO19_WX		0x80
/* W_IWQ_FIFO_BW5 */
#define V_IWQ_FIFO20_TX		0x01
#define V_IWQ_FIFO20_WX		0x02
#define V_IWQ_FIFO21_TX		0x04
#define V_IWQ_FIFO21_WX		0x08
#define V_IWQ_FIFO22_TX		0x10
#define V_IWQ_FIFO22_WX		0x20
#define V_IWQ_FIFO23_TX		0x40
#define V_IWQ_FIFO23_WX		0x80
/* W_IWQ_FIFO_BW6 */
#define V_IWQ_FIFO24_TX		0x01
#define V_IWQ_FIFO24_WX		0x02
#define V_IWQ_FIFO25_TX		0x04
#define V_IWQ_FIFO25_WX		0x08
#define V_IWQ_FIFO26_TX		0x10
#define V_IWQ_FIFO26_WX		0x20
#define V_IWQ_FIFO27_TX		0x40
#define V_IWQ_FIFO27_WX		0x80
/* W_IWQ_FIFO_BW7 */
#define V_IWQ_FIFO28_TX		0x01
#define V_IWQ_FIFO28_WX		0x02
#define V_IWQ_FIFO29_TX		0x04
#define V_IWQ_FIFO29_WX		0x08
#define V_IWQ_FIFO30_TX		0x10
#define V_IWQ_FIFO30_WX		0x20
#define V_IWQ_FIFO31_TX		0x40
#define V_IWQ_FIFO31_WX		0x80

/* chaptew 13: genewaw puwpose I/O pins (GPIO) and input pins (GPI) */
/* W_GPIO_OUT0 */
#define V_GPIO_OUT0		0x01
#define V_GPIO_OUT1		0x02
#define V_GPIO_OUT2		0x04
#define V_GPIO_OUT3		0x08
#define V_GPIO_OUT4		0x10
#define V_GPIO_OUT5		0x20
#define V_GPIO_OUT6		0x40
#define V_GPIO_OUT7		0x80
/* W_GPIO_OUT1 */
#define V_GPIO_OUT8		0x01
#define V_GPIO_OUT9		0x02
#define V_GPIO_OUT10		0x04
#define V_GPIO_OUT11		0x08
#define V_GPIO_OUT12		0x10
#define V_GPIO_OUT13		0x20
#define V_GPIO_OUT14		0x40
#define V_GPIO_OUT15		0x80
/* W_GPIO_EN0 */
#define V_GPIO_EN0		0x01
#define V_GPIO_EN1		0x02
#define V_GPIO_EN2		0x04
#define V_GPIO_EN3		0x08
#define V_GPIO_EN4		0x10
#define V_GPIO_EN5		0x20
#define V_GPIO_EN6		0x40
#define V_GPIO_EN7		0x80
/* W_GPIO_EN1 */
#define V_GPIO_EN8		0x01
#define V_GPIO_EN9		0x02
#define V_GPIO_EN10		0x04
#define V_GPIO_EN11		0x08
#define V_GPIO_EN12		0x10
#define V_GPIO_EN13		0x20
#define V_GPIO_EN14		0x40
#define V_GPIO_EN15		0x80
/* W_GPIO_SEW */
#define V_GPIO_SEW0		0x01
#define V_GPIO_SEW1		0x02
#define V_GPIO_SEW2		0x04
#define V_GPIO_SEW3		0x08
#define V_GPIO_SEW4		0x10
#define V_GPIO_SEW5		0x20
#define V_GPIO_SEW6		0x40
#define V_GPIO_SEW7		0x80
/* W_GPIO_IN0 */
#define V_GPIO_IN0		0x01
#define V_GPIO_IN1		0x02
#define V_GPIO_IN2		0x04
#define V_GPIO_IN3		0x08
#define V_GPIO_IN4		0x10
#define V_GPIO_IN5		0x20
#define V_GPIO_IN6		0x40
#define V_GPIO_IN7		0x80
/* W_GPIO_IN1 */
#define V_GPIO_IN8		0x01
#define V_GPIO_IN9		0x02
#define V_GPIO_IN10		0x04
#define V_GPIO_IN11		0x08
#define V_GPIO_IN12		0x10
#define V_GPIO_IN13		0x20
#define V_GPIO_IN14		0x40
#define V_GPIO_IN15		0x80
/* W_GPI_IN0 */
#define V_GPI_IN0		0x01
#define V_GPI_IN1		0x02
#define V_GPI_IN2		0x04
#define V_GPI_IN3		0x08
#define V_GPI_IN4		0x10
#define V_GPI_IN5		0x20
#define V_GPI_IN6		0x40
#define V_GPI_IN7		0x80
/* W_GPI_IN1 */
#define V_GPI_IN8		0x01
#define V_GPI_IN9		0x02
#define V_GPI_IN10		0x04
#define V_GPI_IN11		0x08
#define V_GPI_IN12		0x10
#define V_GPI_IN13		0x20
#define V_GPI_IN14		0x40
#define V_GPI_IN15		0x80
/* W_GPI_IN2 */
#define V_GPI_IN16		0x01
#define V_GPI_IN17		0x02
#define V_GPI_IN18		0x04
#define V_GPI_IN19		0x08
#define V_GPI_IN20		0x10
#define V_GPI_IN21		0x20
#define V_GPI_IN22		0x40
#define V_GPI_IN23		0x80
/* W_GPI_IN3 */
#define V_GPI_IN24		0x01
#define V_GPI_IN25		0x02
#define V_GPI_IN26		0x04
#define V_GPI_IN27		0x08
#define V_GPI_IN28		0x10
#define V_GPI_IN29		0x20
#define V_GPI_IN30		0x40
#define V_GPI_IN31		0x80

/* map of aww wegistews, used fow debugging */

#ifdef HFC_WEGISTEW_DEBUG
stwuct hfc_wegistew_names {
	chaw *name;
	u_chaw weg;
} hfc_wegistew_names[] = {
	/* wwite wegistews */
	{"W_CIWM",		0x00},
	{"W_CTWW",		0x01},
	{"W_BWG_PCM_CFG ",	0x02},
	{"W_WAM_ADDW0",		0x08},
	{"W_WAM_ADDW1",		0x09},
	{"W_WAM_ADDW2",		0x0A},
	{"W_FIWST_FIFO",	0x0B},
	{"W_WAM_SZ",		0x0C},
	{"W_FIFO_MD",		0x0D},
	{"W_INC_WES_FIFO",	0x0E},
	{"W_FIFO / W_FSM_IDX",	0x0F},
	{"W_SWOT",		0x10},
	{"W_IWQMSK_MISC",	0x11},
	{"W_SCI_MSK",		0x12},
	{"W_IWQ_CTWW",		0x13},
	{"W_PCM_MD0",		0x14},
	{"W_0x15",		0x15},
	{"W_ST_SEW",		0x16},
	{"W_ST_SYNC",		0x17},
	{"W_CONF_EN",		0x18},
	{"W_TI_WD",		0x1A},
	{"W_BEWT_WD_MD",	0x1B},
	{"W_DTMF",		0x1C},
	{"W_DTMF_N",		0x1D},
	{"W_E1_XX_STA",		0x20},
	{"W_WOS0",		0x22},
	{"W_WOS1",		0x23},
	{"W_WX0",		0x24},
	{"W_WX_FW0",		0x25},
	{"W_WX_FW1",		0x26},
	{"W_TX0",		0x28},
	{"W_TX1",		0x29},
	{"W_TX_FW0",		0x2C},
	{"W_TX_FW1",		0x2D},
	{"W_TX_FW2",		0x2E},
	{"W_JATT_ATT",		0x2F},
	{"A_ST_xx_STA/W_WX_OFF", 0x30},
	{"A_ST_CTWW0/W_SYNC_OUT", 0x31},
	{"A_ST_CTWW1",		0x32},
	{"A_ST_CTWW2",		0x33},
	{"A_ST_SQ_WW",		0x34},
	{"W_TX_OFF",		0x34},
	{"W_SYNC_CTWW",		0x35},
	{"A_ST_CWK_DWY",	0x37},
	{"W_PWM0",		0x38},
	{"W_PWM1",		0x39},
	{"A_ST_B1_TX",		0x3C},
	{"A_ST_B2_TX",		0x3D},
	{"A_ST_D_TX",		0x3E},
	{"W_GPIO_OUT0",		0x40},
	{"W_GPIO_OUT1",		0x41},
	{"W_GPIO_EN0",		0x42},
	{"W_GPIO_EN1",		0x43},
	{"W_GPIO_SEW",		0x44},
	{"W_BWG_CTWW",		0x45},
	{"W_PWM_MD",		0x46},
	{"W_BWG_MD",		0x47},
	{"W_BWG_TIM0",		0x48},
	{"W_BWG_TIM1",		0x49},
	{"W_BWG_TIM2",		0x4A},
	{"W_BWG_TIM3",		0x4B},
	{"W_BWG_TIM_SEW01",	0x4C},
	{"W_BWG_TIM_SEW23",	0x4D},
	{"W_BWG_TIM_SEW45",	0x4E},
	{"W_BWG_TIM_SEW67",	0x4F},
	{"A_FIFO_DATA0-2",	0x80},
	{"A_FIFO_DATA0-2_NOINC", 0x84},
	{"W_WAM_DATA",		0xC0},
	{"A_SW_CFG",		0xD0},
	{"A_CONF",		0xD1},
	{"A_CH_MSK",		0xF4},
	{"A_CON_HDWC",		0xFA},
	{"A_SUBCH_CFG",		0xFB},
	{"A_CHANNEW",		0xFC},
	{"A_FIFO_SEQ",		0xFD},
	{"A_IWQ_MSK",		0xFF},
	{NUWW, 0},

	/* wead wegistews */
	{"A_Z1",		0x04},
	{"A_Z1H",		0x05},
	{"A_Z2",		0x06},
	{"A_Z2H",		0x07},
	{"A_F1",		0x0C},
	{"A_F2",		0x0D},
	{"W_IWQ_OVIEW",		0x10},
	{"W_IWQ_MISC",		0x11},
	{"W_IWQ_STATECH",	0x12},
	{"W_CONF_OFWOW",	0x14},
	{"W_WAM_USE",		0x15},
	{"W_CHIP_ID",		0x16},
	{"W_BEWT_STA",		0x17},
	{"W_F0_CNTW",		0x18},
	{"W_F0_CNTH",		0x19},
	{"W_BEWT_ECW",		0x1A},
	{"W_BEWT_ECH",		0x1B},
	{"W_STATUS",		0x1C},
	{"W_CHIP_WV",		0x1F},
	{"W_STATE",		0x20},
	{"W_SYNC_STA",		0x24},
	{"W_WX_SW0_0",		0x25},
	{"W_WX_SW0_1",		0x26},
	{"W_WX_SW0_2",		0x27},
	{"W_JATT_DIW",		0x2b},
	{"W_SWIP",		0x2c},
	{"A_ST_WD_STA",		0x30},
	{"W_FAS_ECW",		0x30},
	{"W_FAS_ECH",		0x31},
	{"W_VIO_ECW",		0x32},
	{"W_VIO_ECH",		0x33},
	{"W_CWC_ECW / A_ST_SQ_WD", 0x34},
	{"W_CWC_ECH",		0x35},
	{"W_E_ECW",		0x36},
	{"W_E_ECH",		0x37},
	{"W_SA6_SA13_ECW",	0x38},
	{"W_SA6_SA13_ECH",	0x39},
	{"W_SA6_SA23_ECW",	0x3A},
	{"W_SA6_SA23_ECH",	0x3B},
	{"A_ST_B1_WX",		0x3C},
	{"A_ST_B2_WX",		0x3D},
	{"A_ST_D_WX",		0x3E},
	{"A_ST_E_WX",		0x3F},
	{"W_GPIO_IN0",		0x40},
	{"W_GPIO_IN1",		0x41},
	{"W_GPI_IN0",		0x44},
	{"W_GPI_IN1",		0x45},
	{"W_GPI_IN2",		0x46},
	{"W_GPI_IN3",		0x47},
	{"A_FIFO_DATA0-2",	0x80},
	{"A_FIFO_DATA0-2_NOINC", 0x84},
	{"W_INT_DATA",		0x88},
	{"W_WAM_DATA",		0xC0},
	{"W_IWQ_FIFO_BW0",	0xC8},
	{"W_IWQ_FIFO_BW1",	0xC9},
	{"W_IWQ_FIFO_BW2",	0xCA},
	{"W_IWQ_FIFO_BW3",	0xCB},
	{"W_IWQ_FIFO_BW4",	0xCC},
	{"W_IWQ_FIFO_BW5",	0xCD},
	{"W_IWQ_FIFO_BW6",	0xCE},
	{"W_IWQ_FIFO_BW7",	0xCF},
};
#endif /* HFC_WEGISTEW_DEBUG */
