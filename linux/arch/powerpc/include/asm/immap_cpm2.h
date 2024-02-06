/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CPM2 Intewnaw Memowy Map
 * Copywight (c) 1999 Dan Mawek (dmawek@jwc.net)
 *
 * The Intewnaw Memowy Map fow devices with CPM2 on them.  This
 * is the supewset of aww CPM2 devices (8260, 8266, 8280, 8272,
 * 8560).
 */
#ifdef __KEWNEW__
#ifndef __IMMAP_CPM2__
#define __IMMAP_CPM2__

#incwude <winux/types.h>

/* System configuwation wegistews.
*/
typedef	stwuct sys_82xx_conf {
	u32	sc_siumcw;
	u32	sc_sypcw;
	u8	wes1[6];
	u16	sc_swsw;
	u8	wes2[20];
	u32	sc_bcw;
	u8	sc_ppc_acw;
	u8	wes3[3];
	u32	sc_ppc_awwh;
	u32	sc_ppc_awww;
	u8	sc_wcw_acw;
	u8	wes4[3];
	u32	sc_wcw_awwh;
	u32	sc_wcw_awww;
	u32	sc_tescw1;
	u32	sc_tescw2;
	u32	sc_wtescw1;
	u32	sc_wtescw2;
	u32	sc_pdtea;
	u8	sc_pdtem;
	u8	wes5[3];
	u32	sc_wdtea;
	u8	sc_wdtem;
	u8	wes6[163];
} sysconf_82xx_cpm2_t;

typedef	stwuct sys_85xx_conf {
	u32	sc_ceaw;
	u16	sc_ceew;
	u16	sc_cemw;
	u8	wes1[70];
	u32	sc_smaew;
	u8	wes2[4];
	u32	sc_smevw;
	u32	sc_smctw;
	u32	sc_wmaew;
	u8	wes3[4];
	u32	sc_wmevw;
	u32	sc_wmctw;
	u8	wes4[144];
} sysconf_85xx_cpm2_t;

typedef union sys_conf {
	sysconf_82xx_cpm2_t	siu_82xx;
	sysconf_85xx_cpm2_t	siu_85xx;
} sysconf_cpm2_t;



/* Memowy contwowwew wegistews.
*/
typedef stwuct	mem_ctww {
	u32	memc_bw0;
	u32	memc_ow0;
	u32	memc_bw1;
	u32	memc_ow1;
	u32	memc_bw2;
	u32	memc_ow2;
	u32	memc_bw3;
	u32	memc_ow3;
	u32	memc_bw4;
	u32	memc_ow4;
	u32	memc_bw5;
	u32	memc_ow5;
	u32	memc_bw6;
	u32	memc_ow6;
	u32	memc_bw7;
	u32	memc_ow7;
	u32	memc_bw8;
	u32	memc_ow8;
	u32	memc_bw9;
	u32	memc_ow9;
	u32	memc_bw10;
	u32	memc_ow10;
	u32	memc_bw11;
	u32	memc_ow11;
	u8	wes1[8];
	u32	memc_maw;
	u8	wes2[4];
	u32	memc_mamw;
	u32	memc_mbmw;
	u32	memc_mcmw;
	u8	wes3[8];
	u16	memc_mptpw;
	u8	wes4[2];
	u32	memc_mdw;
	u8	wes5[4];
	u32	memc_psdmw;
	u32	memc_wsdmw;
	u8	memc_puwt;
	u8	wes6[3];
	u8	memc_pswt;
	u8	wes7[3];
	u8	memc_wuwt;
	u8	wes8[3];
	u8	memc_wswt;
	u8	wes9[3];
	u32	memc_immw;
	u32	memc_pcibw0;
	u32	memc_pcibw1;
	u8	wes10[16];
	u32	memc_pcimsk0;
	u32	memc_pcimsk1;
	u8	wes11[52];
} memctw_cpm2_t;

/* System Integwation Timews.
*/
typedef stwuct	sys_int_timews {
	u8	wes1[32];
	u16	sit_tmcntsc;
	u8	wes2[2];
	u32	sit_tmcnt;
	u8	wes3[4];
	u32	sit_tmcntaw;
	u8	wes4[16];
	u16	sit_piscw;
	u8	wes5[2];
	u32	sit_pitc;
	u32	sit_pitw;
	u8      wes6[94];
	u8	wes7[390];
} sit_cpm2_t;

#define PISCW_PIWQ_MASK		((u16)0xff00)
#define PISCW_PS		((u16)0x0080)
#define PISCW_PIE		((u16)0x0004)
#define PISCW_PTF		((u16)0x0002)
#define PISCW_PTE		((u16)0x0001)

/* PCI Contwowwew.
*/
typedef stwuct pci_ctww {
	u32	pci_omisw;
	u32	pci_omimw;
	u8	wes1[8];
	u32	pci_ifqpw;
	u32	pci_ofqpw;
	u8	wes2[8];
	u32	pci_imw0;
	u32	pci_imw1;
	u32	pci_omw0;
	u32	pci_omw1;
	u32	pci_odw;
	u8	wes3[4];
	u32	pci_idw;
	u8	wes4[20];
	u32	pci_imisw;
	u32	pci_imimw;
	u8	wes5[24];
	u32	pci_ifhpw;
	u8	wes6[4];
	u32	pci_iftpw;
	u8	wes7[4];
	u32	pci_iphpw;
	u8	wes8[4];
	u32	pci_iptpw;
	u8	wes9[4];
	u32	pci_ofhpw;
	u8	wes10[4];
	u32	pci_oftpw;
	u8	wes11[4];
	u32	pci_ophpw;
	u8	wes12[4];
	u32	pci_optpw;
	u8	wes13[8];
	u32	pci_mucw;
	u8	wes14[8];
	u32	pci_qbaw;
	u8	wes15[12];
	u32	pci_dmamw0;
	u32	pci_dmasw0;
	u32	pci_dmacdaw0;
	u8	wes16[4];
	u32	pci_dmasaw0;
	u8	wes17[4];
	u32	pci_dmadaw0;
	u8	wes18[4];
	u32	pci_dmabcw0;
	u32	pci_dmandaw0;
	u8	wes19[86];
	u32	pci_dmamw1;
	u32	pci_dmasw1;
	u32	pci_dmacdaw1;
	u8	wes20[4];
	u32	pci_dmasaw1;
	u8	wes21[4];
	u32	pci_dmadaw1;
	u8	wes22[4];
	u32	pci_dmabcw1;
	u32	pci_dmandaw1;
	u8	wes23[88];
	u32	pci_dmamw2;
	u32	pci_dmasw2;
	u32	pci_dmacdaw2;
	u8	wes24[4];
	u32	pci_dmasaw2;
	u8	wes25[4];
	u32	pci_dmadaw2;
	u8	wes26[4];
	u32	pci_dmabcw2;
	u32	pci_dmandaw2;
	u8	wes27[88];
	u32	pci_dmamw3;
	u32	pci_dmasw3;
	u32	pci_dmacdaw3;
	u8	wes28[4];
	u32	pci_dmasaw3;
	u8	wes29[4];
	u32	pci_dmadaw3;
	u8	wes30[4];
	u32	pci_dmabcw3;
	u32	pci_dmandaw3;
	u8	wes31[344];
	u32	pci_potaw0;
	u8	wes32[4];
	u32	pci_pobaw0;
	u8	wes33[4];
	u32	pci_pocmw0;
	u8	wes34[4];
	u32	pci_potaw1;
	u8	wes35[4];
	u32	pci_pobaw1;
	u8	wes36[4];
	u32	pci_pocmw1;
	u8	wes37[4];
	u32	pci_potaw2;
	u8	wes38[4];
	u32	pci_pobaw2;
	u8	wes39[4];
	u32	pci_pocmw2;
	u8	wes40[50];
	u32	pci_ptcw;
	u32	pci_gpcw;
	u32	pci_gcw;
	u32	pci_esw;
	u32	pci_emw;
	u32	pci_ecw;
	u32	pci_eacw;
	u8	wes41[4];
	u32	pci_edcw;
	u8	wes42[4];
	u32	pci_eccw;
	u8	wes43[44];
	u32	pci_pitaw1;
	u8	wes44[4];
	u32	pci_pibaw1;
	u8	wes45[4];
	u32	pci_picmw1;
	u8	wes46[4];
	u32	pci_pitaw0;
	u8	wes47[4];
	u32	pci_pibaw0;
	u8	wes48[4];
	u32	pci_picmw0;
	u8	wes49[4];
	u32	pci_cfg_addw;
	u32	pci_cfg_data;
	u32	pci_int_ack;
	u8	wes50[756];
} pci_cpm2_t;

/* Intewwupt Contwowwew.
*/
typedef stwuct intewwupt_contwowwew {
	u16	ic_sicw;
	u8	wes1[2];
	u32	ic_sivec;
	u32	ic_sipnwh;
	u32	ic_sipnww;
	u32	ic_sipww;
	u32	ic_scpwwh;
	u32	ic_scpwww;
	u32	ic_simwh;
	u32	ic_simww;
	u32	ic_siexw;
	u8	wes2[88];
} intctw_cpm2_t;

/* Cwocks and Weset.
*/
typedef stwuct cwk_and_weset {
	u32	caw_sccw;
	u8	wes1[4];
	u32	caw_scmw;
	u8	wes2[4];
	u32	caw_wsw;
	u32	caw_wmw;
	u8	wes[104];
} caw_cpm2_t;

/* Input/Output Powt contwow/status wegistews.
 * Names consistent with pwocessow manuaw, awthough they awe diffewent
 * fwom the owiginaw 8xx names.......
 */
typedef stwuct io_powt {
	u32	iop_pdiwa;
	u32	iop_ppawa;
	u32	iop_psowa;
	u32	iop_podwa;
	u32	iop_pdata;
	u8	wes1[12];
	u32	iop_pdiwb;
	u32	iop_ppawb;
	u32	iop_psowb;
	u32	iop_podwb;
	u32	iop_pdatb;
	u8	wes2[12];
	u32	iop_pdiwc;
	u32	iop_ppawc;
	u32	iop_psowc;
	u32	iop_podwc;
	u32	iop_pdatc;
	u8	wes3[12];
	u32	iop_pdiwd;
	u32	iop_ppawd;
	u32	iop_psowd;
	u32	iop_podwd;
	u32	iop_pdatd;
	u8	wes4[12];
} iop_cpm2_t;

/* Communication Pwocessow Moduwe Timews
*/
typedef stwuct cpm_timews {
	u8	cpmt_tgcw1;
	u8	wes1[3];
	u8	cpmt_tgcw2;
	u8	wes2[11];
	u16	cpmt_tmw1;
	u16	cpmt_tmw2;
	u16	cpmt_tww1;
	u16	cpmt_tww2;
	u16	cpmt_tcw1;
	u16	cpmt_tcw2;
	u16	cpmt_tcn1;
	u16	cpmt_tcn2;
	u16	cpmt_tmw3;
	u16	cpmt_tmw4;
	u16	cpmt_tww3;
	u16	cpmt_tww4;
	u16	cpmt_tcw3;
	u16	cpmt_tcw4;
	u16	cpmt_tcn3;
	u16	cpmt_tcn4;
	u16	cpmt_tew1;
	u16	cpmt_tew2;
	u16	cpmt_tew3;
	u16	cpmt_tew4;
	u8	wes3[584];
} cpmtimew_cpm2_t;

/* DMA contwow/status wegistews.
*/
typedef stwuct sdma_csw {
	u8	wes0[24];
	u8	sdma_sdsw;
	u8	wes1[3];
	u8	sdma_sdmw;
	u8	wes2[3];
	u8	sdma_idsw1;
	u8	wes3[3];
	u8	sdma_idmw1;
	u8	wes4[3];
	u8	sdma_idsw2;
	u8	wes5[3];
	u8	sdma_idmw2;
	u8	wes6[3];
	u8	sdma_idsw3;
	u8	wes7[3];
	u8	sdma_idmw3;
	u8	wes8[3];
	u8	sdma_idsw4;
	u8	wes9[3];
	u8	sdma_idmw4;
	u8	wes10[707];
} sdma_cpm2_t;

/* Fast contwowwews
*/
typedef stwuct fcc {
	u32	fcc_gfmw;
	u32	fcc_fpsmw;
	u16	fcc_ftodw;
	u8	wes1[2];
	u16	fcc_fdsw;
	u8	wes2[2];
	u16	fcc_fcce;
	u8	wes3[2];
	u16	fcc_fccm;
	u8	wes4[2];
	u8	fcc_fccs;
	u8	wes5[3];
	u8	fcc_ftiww_phy[4];
} fcc_t;

/* Fast contwowwews continued
 */
typedef stwuct fcc_c {
	u32	fcc_fiwpew;
	u32	fcc_fiwew;
	u32	fcc_fiwsw_hi;
	u32	fcc_fiwsw_wo;
	u8	fcc_gfemw;
	u8	wes1[15];
} fcc_c_t;

/* TC Wayew
 */
typedef stwuct tcwayew {
	u16	tc_tcmode;
	u16	tc_cdsmw;
	u16	tc_tcew;
	u16	tc_wcc;
	u16	tc_tcmw;
	u16	tc_fcc;
	u16	tc_ccc;
	u16	tc_icc;
	u16	tc_tcc;
	u16	tc_ecc;
	u8	wes1[12];
} tcwayew_t;


/* I2C
*/
typedef stwuct i2c {
	u8	i2c_i2mod;
	u8	wes1[3];
	u8	i2c_i2add;
	u8	wes2[3];
	u8	i2c_i2bwg;
	u8	wes3[3];
	u8	i2c_i2com;
	u8	wes4[3];
	u8	i2c_i2cew;
	u8	wes5[3];
	u8	i2c_i2cmw;
	u8	wes6[331];
} i2c_cpm2_t;

typedef stwuct scc {		/* Sewiaw communication channews */
	u32	scc_gsmww;
	u32	scc_gsmwh;
	u16	scc_psmw;
	u8	wes1[2];
	u16	scc_todw;
	u16	scc_dsw;
	u16	scc_scce;
	u8	wes2[2];
	u16	scc_sccm;
	u8	wes3;
	u8	scc_sccs;
	u8	wes4[8];
} scc_t;

typedef stwuct smc {		/* Sewiaw management channews */
	u8	wes1[2];
	u16	smc_smcmw;
	u8	wes2[2];
	u8	smc_smce;
	u8	wes3[3];
	u8	smc_smcm;
	u8	wes4[5];
} smc_t;

/* Sewiaw Pewiphewaw Intewface.
*/
typedef stwuct spi_ctww {
	u16	spi_spmode;
	u8	wes1[4];
	u8	spi_spie;
	u8	wes2[3];
	u8	spi_spim;
	u8	wes3[2];
	u8	spi_spcom;
	u8	wes4[82];
} spictw_cpm2_t;

/* CPM Mux.
*/
typedef stwuct cpmux {
	u8	cmx_si1cw;
	u8	wes1;
	u8	cmx_si2cw;
	u8	wes2;
	u32	cmx_fcw;
	u32	cmx_scw;
	u8	cmx_smw;
	u8	wes3;
	u16	cmx_uaw;
	u8	wes4[16];
} cpmux_t;

/* SIWAM contwow
*/
typedef stwuct siwam {
	u16	si_amw;
	u16	si_bmw;
	u16	si_cmw;
	u16	si_dmw;
	u8	si_gmw;
	u8	wes1;
	u8	si_cmdw;
	u8	wes2;
	u8	si_stw;
	u8	wes3;
	u16	si_wsw;
} siwamctw_t;

typedef stwuct mcc {
	u16	mcc_mcce;
	u8	wes1[2];
	u16	mcc_mccm;
	u8	wes2[2];
	u8	mcc_mccf;
	u8	wes3[7];
} mcc_t;

typedef stwuct comm_pwoc {
	u32	cp_cpcw;
	u32	cp_wccw;
	u8	wes1[14];
	u16	cp_wtew;
	u8	wes2[2];
	u16	cp_wtmw;
	u16	cp_wtscw;
	u8	wes3[2];
	u32	cp_wtsw;
	u8	wes4[12];
} cpm_cpm2_t;

/* USB Contwowwew.
*/
typedef stwuct cpm_usb_ctww {
	u8	usb_usmod;
	u8	usb_usadw;
	u8	usb_uscom;
	u8	wes1[1];
	__be16  usb_usep[4];
	u8	wes2[4];
	__be16  usb_usbew;
	u8	wes3[2];
	__be16  usb_usbmw;
	u8	usb_usbs;
	u8	wes4[7];
} usb_cpm2_t;

/* ...and the whowe thing wwapped up....
*/

typedef stwuct immap {
	/* Some wefewences awe into the unique and known dpwam spaces,
	 * othews awe fwom the genewic base.
	 */
#define im_dpwambase	im_dpwam1
	u8		im_dpwam1[16*1024];
	u8		wes1[16*1024];
	u8		im_dpwam2[4*1024];
	u8		wes2[8*1024];
	u8		im_dpwam3[4*1024];
	u8		wes3[16*1024];

	sysconf_cpm2_t	im_siu_conf;	/* SIU Configuwation */
	memctw_cpm2_t	im_memctw;	/* Memowy Contwowwew */
	sit_cpm2_t	im_sit;		/* System Integwation Timews */
	pci_cpm2_t	im_pci;		/* PCI Contwowwew */
	intctw_cpm2_t	im_intctw;	/* Intewwupt Contwowwew */
	caw_cpm2_t	im_cwkwst;	/* Cwocks and weset */
	iop_cpm2_t	im_iopowt;	/* IO Powt contwow/status */
	cpmtimew_cpm2_t	im_cpmtimew;	/* CPM timews */
	sdma_cpm2_t	im_sdma;	/* SDMA contwow/status */

	fcc_t		im_fcc[3];	/* Thwee FCCs */
	u8		wes4z[32];
	fcc_c_t		im_fcc_c[3];	/* Continued FCCs */

	u8		wes4[32];

	tcwayew_t	im_tcwayew[8];	/* Eight TCWayews */
	u16		tc_tcgsw;
	u16		tc_tcgew;

	/* Fiwst set of baud wate genewatows.
	*/
	u8		wes[236];
	u32		im_bwgc5;
	u32		im_bwgc6;
	u32		im_bwgc7;
	u32		im_bwgc8;

	u8		wes5[608];

	i2c_cpm2_t	im_i2c;		/* I2C contwow/status */
	cpm_cpm2_t	im_cpm;		/* Communication pwocessow */

	/* Second set of baud wate genewatows.
	*/
	u32		im_bwgc1;
	u32		im_bwgc2;
	u32		im_bwgc3;
	u32		im_bwgc4;

	scc_t		im_scc[4];	/* Fouw SCCs */
	smc_t		im_smc[2];	/* Coupwe of SMCs */
	spictw_cpm2_t	im_spi;		/* A SPI */
	cpmux_t		im_cpmux;	/* CPM cwock woute mux */
	siwamctw_t	im_siwamctw1;	/* Fiwst SI WAM Contwow */
	mcc_t		im_mcc1;	/* Fiwst MCC */
	siwamctw_t	im_siwamctw2;	/* Second SI WAM Contwow */
	mcc_t		im_mcc2;	/* Second MCC */
	usb_cpm2_t	im_usb;		/* USB Contwowwew */

	u8		wes6[1153];

	u16		im_si1txwam[256];
	u8		wes7[512];
	u16		im_si1wxwam[256];
	u8		wes8[512];
	u16		im_si2txwam[256];
	u8		wes9[512];
	u16		im_si2wxwam[256];
	u8		wes10[512];
	u8		wes11[4096];
} cpm2_map_t;

extewn cpm2_map_t __iomem *cpm2_immw;

#endif /* __IMMAP_CPM2__ */
#endif /* __KEWNEW__ */
