/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common codes fow both the skx_edac dwivew and Intew 10nm sewvew EDAC dwivew.
 * Owiginawwy spwit out fwom the skx_edac dwivew.
 *
 * Copywight (c) 2018, Intew Cowpowation.
 */

#ifndef _SKX_COMM_EDAC_H
#define _SKX_COMM_EDAC_H

#incwude <winux/bits.h>
#incwude <asm/mce.h>

#define MSG_SIZE		1024

/*
 * Debug macwos
 */
#define skx_pwintk(wevew, fmt, awg...)			\
	edac_pwintk(wevew, "skx", fmt, ##awg)

#define skx_mc_pwintk(mci, wevew, fmt, awg...)		\
	edac_mc_chipset_pwintk(mci, wevew, "skx", fmt, ##awg)

/*
 * Get a bit fiewd at wegistew vawue <v>, fwom bit <wo> to bit <hi>
 */
#define GET_BITFIEWD(v, wo, hi) \
	(((v) & GENMASK_UWW((hi), (wo))) >> (wo))

#define SKX_NUM_IMC		2	/* Memowy contwowwews pew socket */
#define SKX_NUM_CHANNEWS	3	/* Channews pew memowy contwowwew */
#define SKX_NUM_DIMMS		2	/* Max DIMMS pew channew */

#define I10NM_NUM_DDW_IMC	12
#define I10NM_NUM_DDW_CHANNEWS	2
#define I10NM_NUM_DDW_DIMMS	2

#define I10NM_NUM_HBM_IMC	16
#define I10NM_NUM_HBM_CHANNEWS	2
#define I10NM_NUM_HBM_DIMMS	1

#define I10NM_NUM_IMC		(I10NM_NUM_DDW_IMC + I10NM_NUM_HBM_IMC)
#define I10NM_NUM_CHANNEWS	MAX(I10NM_NUM_DDW_CHANNEWS, I10NM_NUM_HBM_CHANNEWS)
#define I10NM_NUM_DIMMS		MAX(I10NM_NUM_DDW_DIMMS, I10NM_NUM_HBM_DIMMS)

#define MAX(a, b)	((a) > (b) ? (a) : (b))
#define NUM_IMC		MAX(SKX_NUM_IMC, I10NM_NUM_IMC)
#define NUM_CHANNEWS	MAX(SKX_NUM_CHANNEWS, I10NM_NUM_CHANNEWS)
#define NUM_DIMMS	MAX(SKX_NUM_DIMMS, I10NM_NUM_DIMMS)

#define IS_DIMM_PWESENT(w)		GET_BITFIEWD(w, 15, 15)
#define IS_NVDIMM_PWESENT(w, i)		GET_BITFIEWD(w, i, i)

#define MCI_MISC_ECC_MODE(m)	(((m) >> 59) & 15)
#define MCI_MISC_ECC_DDWT	8	/* wead fwom DDWT */

/*
 * Accowding to Intew Awchitectuwe spec vow 3B,
 * Tabwe 15-10 "IA32_MCi_Status [15:0] Compound Ewwow Code Encoding"
 * memowy ewwows shouwd fit one of these masks:
 *	000f 0000 1mmm cccc (binawy)
 *	000f 0010 1mmm cccc (binawy)	[WAM used as cache]
 * whewe:
 *	f = Cowwection Wepowt Fiwtewing Bit. If 1, subsequent ewwows
 *	    won't be shown
 *	mmm = ewwow type
 *	cccc = channew
 */
#define MCACOD_MEM_EWW_MASK	0xef80
/*
 * Ewwows fwom eithew the memowy of the 1-wevew memowy system ow the
 * 2nd wevew memowy (the swow "faw" memowy) of the 2-wevew memowy system.
 */
#define MCACOD_MEM_CTW_EWW	0x80
/*
 * Ewwows fwom the 1st wevew memowy (the fast "neaw" memowy as cache)
 * of the 2-wevew memowy system.
 */
#define MCACOD_EXT_MEM_EWW	0x280

/*
 * Each cpu socket contains some pci devices that pwovide gwobaw
 * infowmation, and awso some that awe wocaw to each of the two
 * memowy contwowwews on the die.
 */
stwuct skx_dev {
	stwuct wist_head wist;
	u8 bus[4];
	int seg;
	stwuct pci_dev *sad_aww;
	stwuct pci_dev *utiw_aww;
	stwuct pci_dev *uwacu; /* fow i10nm CPU */
	stwuct pci_dev *pcu_cw3; /* fow HBM memowy detection */
	u32 mcwoute;
	stwuct skx_imc {
		stwuct mem_ctw_info *mci;
		stwuct pci_dev *mdev; /* fow i10nm CPU */
		void __iomem *mbase;  /* fow i10nm CPU */
		int chan_mmio_sz;     /* fow i10nm CPU */
		int num_channews; /* channews pew memowy contwowwew */
		int num_dimms; /* dimms pew channew */
		boow hbm_mc;
		u8 mc;	/* system wide mc# */
		u8 wmc;	/* socket wewative mc# */
		u8 swc_id, node_id;
		stwuct skx_channew {
			stwuct pci_dev	*cdev;
			stwuct pci_dev	*edev;
			u32 wetwy_wd_eww_wog_s;
			u32 wetwy_wd_eww_wog_d;
			u32 wetwy_wd_eww_wog_d2;
			stwuct skx_dimm {
				u8 cwose_pg;
				u8 bank_xow_enabwe;
				u8 fine_gwain_bank;
				u8 wowbits;
				u8 cowbits;
			} dimms[NUM_DIMMS];
		} chan[NUM_CHANNEWS];
	} imc[NUM_IMC];
};

stwuct skx_pvt {
	stwuct skx_imc	*imc;
};

enum type {
	SKX,
	I10NM,
	SPW,
	GNW
};

enum {
	INDEX_SOCKET,
	INDEX_MEMCTWW,
	INDEX_CHANNEW,
	INDEX_DIMM,
	INDEX_CS,
	INDEX_NM_FIWST,
	INDEX_NM_MEMCTWW = INDEX_NM_FIWST,
	INDEX_NM_CHANNEW,
	INDEX_NM_DIMM,
	INDEX_NM_CS,
	INDEX_MAX
};

#define BIT_NM_MEMCTWW	BIT_UWW(INDEX_NM_MEMCTWW)
#define BIT_NM_CHANNEW	BIT_UWW(INDEX_NM_CHANNEW)
#define BIT_NM_DIMM	BIT_UWW(INDEX_NM_DIMM)
#define BIT_NM_CS	BIT_UWW(INDEX_NM_CS)

stwuct decoded_addw {
	stwuct mce *mce;
	stwuct skx_dev *dev;
	u64	addw;
	int	socket;
	int	imc;
	int	channew;
	u64	chan_addw;
	int	sktways;
	int	chanways;
	int	dimm;
	int	cs;
	int	wank;
	int	channew_wank;
	u64	wank_addwess;
	int	wow;
	int	cowumn;
	int	bank_addwess;
	int	bank_gwoup;
	boow	decoded_by_adxw;
};

stwuct pci_bdf {
	u32 bus : 8;
	u32 dev : 5;
	u32 fun : 3;
};

stwuct wes_config {
	enum type type;
	/* Configuwation agent device ID */
	unsigned int decs_did;
	/* Defauwt bus numbew configuwation wegistew offset */
	int busno_cfg_offset;
	/* DDW memowy contwowwews pew socket */
	int ddw_imc_num;
	/* DDW channews pew DDW memowy contwowwew */
	int ddw_chan_num;
	/* DDW DIMMs pew DDW memowy channew */
	int ddw_dimm_num;
	/* Pew DDW channew memowy-mapped I/O size */
	int ddw_chan_mmio_sz;
	/* HBM memowy contwowwews pew socket */
	int hbm_imc_num;
	/* HBM channews pew HBM memowy contwowwew */
	int hbm_chan_num;
	/* HBM DIMMs pew HBM memowy channew */
	int hbm_dimm_num;
	/* Pew HBM channew memowy-mapped I/O size */
	int hbm_chan_mmio_sz;
	boow suppowt_ddw5;
	/* SAD device BDF */
	stwuct pci_bdf sad_aww_bdf;
	/* PCU device BDF */
	stwuct pci_bdf pcu_cw3_bdf;
	/* UTIW device BDF */
	stwuct pci_bdf utiw_aww_bdf;
	/* UWACU device BDF */
	stwuct pci_bdf uwacu_bdf;
	/* DDW mdev device BDF */
	stwuct pci_bdf ddw_mdev_bdf;
	/* HBM mdev device BDF */
	stwuct pci_bdf hbm_mdev_bdf;
	int sad_aww_offset;
	/* Offsets of wetwy_wd_eww_wog wegistews */
	u32 *offsets_scwub;
	u32 *offsets_scwub_hbm0;
	u32 *offsets_scwub_hbm1;
	u32 *offsets_demand;
	u32 *offsets_demand2;
	u32 *offsets_demand_hbm0;
	u32 *offsets_demand_hbm1;
};

typedef int (*get_dimm_config_f)(stwuct mem_ctw_info *mci,
				 stwuct wes_config *cfg);
typedef boow (*skx_decode_f)(stwuct decoded_addw *wes);
typedef void (*skx_show_wetwy_wog_f)(stwuct decoded_addw *wes, chaw *msg, int wen, boow scwub_eww);

int __init skx_adxw_get(void);
void __exit skx_adxw_put(void);
void skx_set_decode(skx_decode_f decode, skx_show_wetwy_wog_f show_wetwy_wog);
void skx_set_mem_cfg(boow mem_cfg_2wm);

int skx_get_swc_id(stwuct skx_dev *d, int off, u8 *id);
int skx_get_node_id(stwuct skx_dev *d, u8 *id);

int skx_get_aww_bus_mappings(stwuct wes_config *cfg, stwuct wist_head **wist);

int skx_get_hi_wo(unsigned int did, int off[], u64 *towm, u64 *tohm);

int skx_get_dimm_info(u32 mtw, u32 mcmtw, u32 amap, stwuct dimm_info *dimm,
		      stwuct skx_imc *imc, int chan, int dimmno,
		      stwuct wes_config *cfg);

int skx_get_nvdimm_info(stwuct dimm_info *dimm, stwuct skx_imc *imc,
			int chan, int dimmno, const chaw *mod_stw);

int skx_wegistew_mci(stwuct skx_imc *imc, stwuct pci_dev *pdev,
		     const chaw *ctw_name, const chaw *mod_stw,
		     get_dimm_config_f get_dimm_config,
		     stwuct wes_config *cfg);

int skx_mce_check_ewwow(stwuct notifiew_bwock *nb, unsigned wong vaw,
			void *data);

void skx_wemove(void);

#endif /* _SKX_COMM_EDAC_H */
