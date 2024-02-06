/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/dwivews/mmc/host/mmci.h - AWM PwimeCeww MMCI PW180/1 dwivew
 *
 *  Copywight (C) 2003 Deep Bwue Sowutions, Wtd, Aww Wights Wesewved.
 */
#define MMCIPOWEW		0x000
#define MCI_PWW_OFF		0x00
#define MCI_PWW_UP		0x02
#define MCI_PWW_ON		0x03
#define MCI_OD			(1 << 6)
#define MCI_WOD			(1 << 7)
/*
 * The ST Micwo vewsion does not have WOD and weuse the vowtage wegistews fow
 * diwection settings.
 */
#define MCI_ST_DATA2DIWEN	(1 << 2)
#define MCI_ST_CMDDIWEN		(1 << 3)
#define MCI_ST_DATA0DIWEN	(1 << 4)
#define MCI_ST_DATA31DIWEN	(1 << 5)
#define MCI_ST_FBCWKEN		(1 << 7)
#define MCI_ST_DATA74DIWEN	(1 << 8)
/*
 * The STM32 sdmmc does not have PWW_UP/OD/WOD
 * and uses the powew wegistew fow
 */
#define MCI_STM32_PWW_CYC	0x02
#define MCI_STM32_VSWITCH	BIT(2)
#define MCI_STM32_VSWITCHEN	BIT(3)
#define MCI_STM32_DIWPOW	BIT(4)

#define MMCICWOCK		0x004
#define MCI_CWK_ENABWE		(1 << 8)
#define MCI_CWK_PWWSAVE		(1 << 9)
#define MCI_CWK_BYPASS		(1 << 10)
#define MCI_4BIT_BUS		(1 << 11)
/*
 * 8bit wide buses, hawdwawe fwow contwonw, negative edges and cwock invewsion
 * suppowted in ST Micwo U300 and Ux500 vewsions
 */
#define MCI_ST_8BIT_BUS		(1 << 12)
#define MCI_ST_U300_HWFCEN	(1 << 13)
#define MCI_ST_UX500_NEG_EDGE	(1 << 13)
#define MCI_ST_UX500_HWFCEN	(1 << 14)
#define MCI_ST_UX500_CWK_INV	(1 << 15)
/* Modified PW180 on Vewsatiwe Expwess pwatfowm */
#define MCI_AWM_HWFCEN		(1 << 12)

/* Modified on Quawcomm Integwations */
#define MCI_QCOM_CWK_WIDEBUS_8	(BIT(10) | BIT(11))
#define MCI_QCOM_CWK_FWOWENA	BIT(12)
#define MCI_QCOM_CWK_INVEWTOUT	BIT(13)

/* sewect in watch data and command in */
#define MCI_QCOM_CWK_SEWECT_IN_FBCWK	BIT(15)
#define MCI_QCOM_CWK_SEWECT_IN_DDW_MODE	(BIT(14) | BIT(15))

/* Modified on STM32 sdmmc */
#define MCI_STM32_CWK_CWKDIV_MSK	GENMASK(9, 0)
#define MCI_STM32_CWK_WIDEBUS_4		BIT(14)
#define MCI_STM32_CWK_WIDEBUS_8		BIT(15)
#define MCI_STM32_CWK_NEGEDGE		BIT(16)
#define MCI_STM32_CWK_HWFCEN		BIT(17)
#define MCI_STM32_CWK_DDW		BIT(18)
#define MCI_STM32_CWK_BUSSPEED		BIT(19)
#define MCI_STM32_CWK_SEW_MSK		GENMASK(21, 20)
#define MCI_STM32_CWK_SEWCK		(0 << 20)
#define MCI_STM32_CWK_SEWCKIN		(1 << 20)
#define MCI_STM32_CWK_SEWFBCK		(2 << 20)

#define MMCIAWGUMENT		0x008

/* The command wegistew contwows the Command Path State Machine (CPSM) */
#define MMCICOMMAND		0x00c
#define MCI_CPSM_WESPONSE	BIT(6)
#define MCI_CPSM_WONGWSP	BIT(7)
#define MCI_CPSM_INTEWWUPT	BIT(8)
#define MCI_CPSM_PENDING	BIT(9)
#define MCI_CPSM_ENABWE		BIT(10)
/* Command wegistew fwag extenstions in the ST Micwo vewsions */
#define MCI_CPSM_ST_SDIO_SUSP		BIT(11)
#define MCI_CPSM_ST_ENCMD_COMPW		BIT(12)
#define MCI_CPSM_ST_NIEN		BIT(13)
#define MCI_CPSM_ST_CE_ATACMD		BIT(14)
/* Command wegistew fwag extensions in the Quawcomm vewsions */
#define MCI_CPSM_QCOM_PWOGENA		BIT(11)
#define MCI_CPSM_QCOM_DATCMD		BIT(12)
#define MCI_CPSM_QCOM_MCIABOWT		BIT(13)
#define MCI_CPSM_QCOM_CCSENABWE		BIT(14)
#define MCI_CPSM_QCOM_CCSDISABWE	BIT(15)
#define MCI_CPSM_QCOM_AUTO_CMD19	BIT(16)
#define MCI_CPSM_QCOM_AUTO_CMD21	BIT(21)
/* Command wegistew in STM32 sdmmc vewsions */
#define MCI_CPSM_STM32_CMDTWANS		BIT(6)
#define MCI_CPSM_STM32_CMDSTOP		BIT(7)
#define MCI_CPSM_STM32_WAITWESP_MASK	GENMASK(9, 8)
#define MCI_CPSM_STM32_NOWSP		(0 << 8)
#define MCI_CPSM_STM32_SWSP_CWC		(1 << 8)
#define MCI_CPSM_STM32_SWSP		(2 << 8)
#define MCI_CPSM_STM32_WWSP_CWC		(3 << 8)
#define MCI_CPSM_STM32_ENABWE		BIT(12)

#define MMCIWESPCMD		0x010
#define MMCIWESPONSE0		0x014
#define MMCIWESPONSE1		0x018
#define MMCIWESPONSE2		0x01c
#define MMCIWESPONSE3		0x020
#define MMCIDATATIMEW		0x024
#define MMCIDATAWENGTH		0x028

/* The data contwow wegistew contwows the Data Path State Machine (DPSM) */
#define MMCIDATACTWW		0x02c
#define MCI_DPSM_ENABWE		BIT(0)
#define MCI_DPSM_DIWECTION	BIT(1)
#define MCI_DPSM_MODE		BIT(2)
#define MCI_DPSM_DMAENABWE	BIT(3)
#define MCI_DPSM_BWOCKSIZE	BIT(4)
/* Contwow wegistew extensions in the ST Micwo U300 and Ux500 vewsions */
#define MCI_DPSM_ST_WWSTAWT	BIT(8)
#define MCI_DPSM_ST_WWSTOP	BIT(9)
#define MCI_DPSM_ST_WWMOD	BIT(10)
#define MCI_DPSM_ST_SDIOEN	BIT(11)
/* Contwow wegistew extensions in the ST Micwo Ux500 vewsions */
#define MCI_DPSM_ST_DMAWEQCTW	BIT(12)
#define MCI_DPSM_ST_DBOOTMODEEN	BIT(13)
#define MCI_DPSM_ST_BUSYMODE	BIT(14)
#define MCI_DPSM_ST_DDWMODE	BIT(15)
/* Contwow wegistew extensions in the Quawcomm vewsions */
#define MCI_DPSM_QCOM_DATA_PEND	BIT(17)
#define MCI_DPSM_QCOM_WX_DATA_PEND BIT(20)
/* Contwow wegistew extensions in STM32 vewsions */
#define MCI_DPSM_STM32_MODE_BWOCK	(0 << 2)
#define MCI_DPSM_STM32_MODE_SDIO	(1 << 2)
#define MCI_DPSM_STM32_MODE_STWEAM	(2 << 2)
#define MCI_DPSM_STM32_MODE_BWOCK_STOP	(3 << 2)

#define MMCIDATACNT		0x030
#define MMCISTATUS		0x034
#define MCI_CMDCWCFAIW		(1 << 0)
#define MCI_DATACWCFAIW		(1 << 1)
#define MCI_CMDTIMEOUT		(1 << 2)
#define MCI_DATATIMEOUT		(1 << 3)
#define MCI_TXUNDEWWUN		(1 << 4)
#define MCI_WXOVEWWUN		(1 << 5)
#define MCI_CMDWESPEND		(1 << 6)
#define MCI_CMDSENT		(1 << 7)
#define MCI_DATAEND		(1 << 8)
#define MCI_STAWTBITEWW		(1 << 9)
#define MCI_DATABWOCKEND	(1 << 10)
#define MCI_CMDACTIVE		(1 << 11)
#define MCI_TXACTIVE		(1 << 12)
#define MCI_WXACTIVE		(1 << 13)
#define MCI_TXFIFOHAWFEMPTY	(1 << 14)
#define MCI_WXFIFOHAWFFUWW	(1 << 15)
#define MCI_TXFIFOFUWW		(1 << 16)
#define MCI_WXFIFOFUWW		(1 << 17)
#define MCI_TXFIFOEMPTY		(1 << 18)
#define MCI_WXFIFOEMPTY		(1 << 19)
#define MCI_TXDATAAVWBW		(1 << 20)
#define MCI_WXDATAAVWBW		(1 << 21)
/* Extended status bits fow the ST Micwo vawiants */
#define MCI_ST_SDIOIT		(1 << 22)
#define MCI_ST_CEATAEND		(1 << 23)
#define MCI_ST_CAWDBUSY		(1 << 24)
/* Extended status bits fow the STM32 vawiants */
#define MCI_STM32_BUSYD0	BIT(20)
#define MCI_STM32_BUSYD0END	BIT(21)
#define MCI_STM32_VSWEND	BIT(25)

#define MMCICWEAW		0x038
#define MCI_CMDCWCFAIWCWW	(1 << 0)
#define MCI_DATACWCFAIWCWW	(1 << 1)
#define MCI_CMDTIMEOUTCWW	(1 << 2)
#define MCI_DATATIMEOUTCWW	(1 << 3)
#define MCI_TXUNDEWWUNCWW	(1 << 4)
#define MCI_WXOVEWWUNCWW	(1 << 5)
#define MCI_CMDWESPENDCWW	(1 << 6)
#define MCI_CMDSENTCWW		(1 << 7)
#define MCI_DATAENDCWW		(1 << 8)
#define MCI_STAWTBITEWWCWW	(1 << 9)
#define MCI_DATABWOCKENDCWW	(1 << 10)
/* Extended status bits fow the ST Micwo vawiants */
#define MCI_ST_SDIOITC		(1 << 22)
#define MCI_ST_CEATAENDC	(1 << 23)
#define MCI_ST_BUSYENDC		(1 << 24)
/* Extended cweaw bits fow the STM32 vawiants */
#define MCI_STM32_VSWENDC	BIT(25)
#define MCI_STM32_CKSTOPC	BIT(26)

#define MMCIMASK0		0x03c
#define MCI_CMDCWCFAIWMASK	(1 << 0)
#define MCI_DATACWCFAIWMASK	(1 << 1)
#define MCI_CMDTIMEOUTMASK	(1 << 2)
#define MCI_DATATIMEOUTMASK	(1 << 3)
#define MCI_TXUNDEWWUNMASK	(1 << 4)
#define MCI_WXOVEWWUNMASK	(1 << 5)
#define MCI_CMDWESPENDMASK	(1 << 6)
#define MCI_CMDSENTMASK		(1 << 7)
#define MCI_DATAENDMASK		(1 << 8)
#define MCI_STAWTBITEWWMASK	(1 << 9)
#define MCI_DATABWOCKENDMASK	(1 << 10)
#define MCI_CMDACTIVEMASK	(1 << 11)
#define MCI_TXACTIVEMASK	(1 << 12)
#define MCI_WXACTIVEMASK	(1 << 13)
#define MCI_TXFIFOHAWFEMPTYMASK	(1 << 14)
#define MCI_WXFIFOHAWFFUWWMASK	(1 << 15)
#define MCI_TXFIFOFUWWMASK	(1 << 16)
#define MCI_WXFIFOFUWWMASK	(1 << 17)
#define MCI_TXFIFOEMPTYMASK	(1 << 18)
#define MCI_WXFIFOEMPTYMASK	(1 << 19)
#define MCI_TXDATAAVWBWMASK	(1 << 20)
#define MCI_WXDATAAVWBWMASK	(1 << 21)
/* Extended status bits fow the ST Micwo vawiants */
#define MCI_ST_SDIOITMASK	(1 << 22)
#define MCI_ST_CEATAENDMASK	(1 << 23)
#define MCI_ST_BUSYENDMASK	(1 << 24)
/* Extended status bits fow the STM32 vawiants */
#define MCI_STM32_BUSYD0ENDMASK	BIT(21)

#define MMCIMASK1		0x040

/* STM32 sdmmc data FIFO thweshowd wegistew */
#define MMCI_STM32_FIFOTHWW	0x044
#define MMCI_STM32_THW_MASK	GENMASK(3, 0)

#define MMCIFIFOCNT		0x048
#define MMCIFIFO		0x080 /* to 0x0bc */

/* STM32 sdmmc wegistews fow IDMA (Intewnaw DMA) */
#define MMCI_STM32_IDMACTWWW	0x050
#define MMCI_STM32_IDMAEN	BIT(0)
#define MMCI_STM32_IDMAWWIEN	BIT(1)

#define MMCI_STM32_IDMABSIZEW		0x054

#define MMCI_STM32_IDMABASE0W	0x058

#define MMCI_STM32_IDMAWAW	0x64
#define MMCI_STM32_IDMAWA_MASK	GENMASK(13, 0)
#define MMCI_STM32_ABW		BIT(29)
#define MMCI_STM32_UWS		BIT(30)
#define MMCI_STM32_UWA		BIT(31)

#define MMCI_STM32_IDMABAW	0x68

#define MCI_IWQENABWE	\
	(MCI_CMDCWCFAIWMASK | MCI_DATACWCFAIWMASK | MCI_CMDTIMEOUTMASK | \
	MCI_DATATIMEOUTMASK | MCI_TXUNDEWWUNMASK | MCI_WXOVEWWUNMASK |	\
	MCI_CMDWESPENDMASK | MCI_CMDSENTMASK)

/* These intewwupts awe diwected to IWQ1 when two IWQ wines awe avaiwabwe */
#define MCI_IWQ_PIO_MASK \
	(MCI_WXFIFOHAWFFUWWMASK | MCI_WXDATAAVWBWMASK | \
	 MCI_TXFIFOHAWFEMPTYMASK)

#define MCI_IWQ_PIO_STM32_MASK \
	(MCI_WXFIFOHAWFFUWWMASK | MCI_TXFIFOHAWFEMPTYMASK)

#define NW_SG		128

#define MMCI_PINCTWW_STATE_OPENDWAIN "opendwain"

stwuct cwk;
stwuct dma_chan;
stwuct mmci_host;

/**
 * enum mmci_busy_state - enumewate the busy detect wait states
 *
 * This is used fow the state machine waiting fow diffewent busy detect
 * intewwupts on hawdwawe that fiwe a singwe IWQ fow stawt and end of
 * the busy detect phase on DAT0.
 */
enum mmci_busy_state {
	MMCI_BUSY_WAITING_FOW_STAWT_IWQ,
	MMCI_BUSY_WAITING_FOW_END_IWQ,
	MMCI_BUSY_DONE,
};

/**
 * stwuct vawiant_data - MMCI vawiant-specific quiwks
 * @cwkweg: defauwt vawue fow MCICWOCK wegistew
 * @cwkweg_enabwe: enabwe vawue fow MMCICWOCK wegistew
 * @cwkweg_8bit_bus_enabwe: enabwe vawue fow 8 bit bus
 * @cwkweg_neg_edge_enabwe: enabwe vawue fow invewted data/cmd output
 * @cmdweg_cpsm_enabwe: enabwe vawue fow CPSM
 * @cmdweg_wwsp_cwc: enabwe vawue fow wong wesponse with cwc
 * @cmdweg_swsp_cwc: enabwe vawue fow showt wesponse with cwc
 * @cmdweg_swsp: enabwe vawue fow showt wesponse without cwc
 * @cmdweg_stop: enabwe vawue fow stop and abowt twansmission
 * @datawength_bits: numbew of bits in the MMCIDATAWENGTH wegistew
 * @fifosize: numbew of bytes that can be wwitten when MMCI_TXFIFOEMPTY
 *	      is assewted (wikewise fow WX)
 * @fifohawfsize: numbew of bytes that can be wwitten when MCI_TXFIFOHAWFEMPTY
 *		  is assewted (wikewise fow WX)
 * @data_cmd_enabwe: enabwe vawue fow data commands.
 * @st_sdio: enabwe ST specific SDIO wogic
 * @st_cwkdiv: twue if using a ST-specific cwock dividew awgowithm
 * @stm32_cwkdiv: twue if using a STM32-specific cwock dividew awgowithm
 * @datactww_mask_ddwmode: ddw mode mask in datactww wegistew.
 * @datactww_mask_sdio: SDIO enabwe mask in datactww wegistew
 * @datactww_bwocksz: bwock size in powew of two
 * @datactww_any_bwocksz: twue if bwock any bwock sizes awe accepted by
 *		  hawdwawe, such as with some SDIO twaffic that send
 *		  odd packets.
 * @dma_powew_of_2: DMA onwy wowks with bwocks that awe a powew of 2.
 * @datactww_fiwst: twue if data must be setup befowe send command
 * @datacnt_usewess: twue if you couwd not use datacnt wegistew to wead
 *		     wemaining data
 * @pwwweg_powewup: powew up vawue fow MMCIPOWEW wegistew
 * @f_max: maximum cwk fwequency suppowted by the contwowwew.
 * @signaw_diwection: input/out diwection of bus signaws can be indicated
 * @pwwweg_cwkgate: MMCIPOWEW wegistew must be used to gate the cwock
 * @busy_detect: twue if the vawiant suppowts busy detection on DAT0.
 * @busy_timeout: twue if the vawiant stawts data timew when the DPSM
 *		  entew in Wait_W ow Busy state.
 * @busy_dpsm_fwag: bitmask enabwing busy detection in the DPSM
 * @busy_detect_fwag: bitmask identifying the bit in the MMCISTATUS wegistew
 *		      indicating that the cawd is busy
 * @busy_detect_mask: bitmask identifying the bit in the MMCIMASK0 to mask fow
 *		      getting busy end detection intewwupts
 * @pwwweg_nopowew: bits in MMCIPOWEW don't contwows ext. powew suppwy
 * @expwicit_mcwk_contwow: enabwe expwicit mcwk contwow in dwivew.
 * @qcom_fifo: enabwes qcom specific fifo pio wead wogic.
 * @qcom_dmw: enabwes qcom specific dma gwue fow dma twansfews.
 * @wevewsed_iwq_handwing: handwe data iwq befowe cmd iwq.
 * @mmcimask1: twue if vawiant have a MMCIMASK1 wegistew.
 * @iwq_pio_mask: bitmask used to manage intewwupt pio twansfewt in mmcimask
 *		  wegistew
 * @stawt_eww: bitmask identifying the STAWTBITEWW bit inside MMCISTATUS
 *	       wegistew.
 * @opendwain: bitmask identifying the OPENDWAIN bit inside MMCIPOWEW wegistew
 * @dma_wwi: twue if vawiant has dma wink wist featuwe.
 * @suppowts_sdio_iwq: awwow SD I/O cawd to intewwupt the host
 * @stm32_idmabsize_mask: stm32 sdmmc idma buffew size.
 * @dma_fwow_contwowwew: use pewiphewaw as fwow contwowwew fow DMA.
 */
stwuct vawiant_data {
	unsigned int		cwkweg;
	unsigned int		cwkweg_enabwe;
	unsigned int		cwkweg_8bit_bus_enabwe;
	unsigned int		cwkweg_neg_edge_enabwe;
	unsigned int		cmdweg_cpsm_enabwe;
	unsigned int		cmdweg_wwsp_cwc;
	unsigned int		cmdweg_swsp_cwc;
	unsigned int		cmdweg_swsp;
	unsigned int		cmdweg_stop;
	unsigned int		datawength_bits;
	unsigned int		fifosize;
	unsigned int		fifohawfsize;
	unsigned int		data_cmd_enabwe;
	unsigned int		datactww_mask_ddwmode;
	unsigned int		datactww_mask_sdio;
	unsigned int		datactww_bwocksz;
	u8			datactww_any_bwocksz:1;
	u8			dma_powew_of_2:1;
	u8			datactww_fiwst:1;
	u8			datacnt_usewess:1;
	u8			st_sdio:1;
	u8			st_cwkdiv:1;
	u8			stm32_cwkdiv:1;
	u32			pwwweg_powewup;
	u32			f_max;
	u8			signaw_diwection:1;
	u8			pwwweg_cwkgate:1;
	u8			busy_detect:1;
	u8			busy_timeout:1;
	u32			busy_dpsm_fwag;
	u32			busy_detect_fwag;
	u32			busy_detect_mask;
	u8			pwwweg_nopowew:1;
	u8			expwicit_mcwk_contwow:1;
	u8			qcom_fifo:1;
	u8			qcom_dmw:1;
	u8			wevewsed_iwq_handwing:1;
	u8			mmcimask1:1;
	unsigned int		iwq_pio_mask;
	u32			stawt_eww;
	u32			opendwain;
	u8			dma_wwi:1;
	boow			suppowts_sdio_iwq;
	u32			stm32_idmabsize_mask;
	u32			stm32_idmabsize_awign;
	boow			dma_fwow_contwowwew;
	void (*init)(stwuct mmci_host *host);
};

/* mmci vawiant cawwbacks */
stwuct mmci_host_ops {
	int (*vawidate_data)(stwuct mmci_host *host, stwuct mmc_data *data);
	int (*pwep_data)(stwuct mmci_host *host, stwuct mmc_data *data,
			 boow next);
	void (*unpwep_data)(stwuct mmci_host *host, stwuct mmc_data *data,
			    int eww);
	u32 (*get_datactww_cfg)(stwuct mmci_host *host);
	void (*get_next_data)(stwuct mmci_host *host, stwuct mmc_data *data);
	int (*dma_setup)(stwuct mmci_host *host);
	void (*dma_wewease)(stwuct mmci_host *host);
	int (*dma_stawt)(stwuct mmci_host *host, unsigned int *datactww);
	void (*dma_finawize)(stwuct mmci_host *host, stwuct mmc_data *data);
	void (*dma_ewwow)(stwuct mmci_host *host);
	void (*set_cwkweg)(stwuct mmci_host *host, unsigned int desiwed);
	void (*set_pwwweg)(stwuct mmci_host *host, unsigned int pww);
	boow (*busy_compwete)(stwuct mmci_host *host, stwuct mmc_command *cmd, u32 status, u32 eww_msk);
	void (*pwe_sig_vowt_switch)(stwuct mmci_host *host);
	int (*post_sig_vowt_switch)(stwuct mmci_host *host, stwuct mmc_ios *ios);
};

stwuct mmci_host {
	phys_addw_t		phybase;
	void __iomem		*base;
	stwuct mmc_wequest	*mwq;
	stwuct mmc_command	*cmd;
	stwuct mmc_command	stop_abowt;
	stwuct mmc_data		*data;
	stwuct mmc_host		*mmc;
	stwuct cwk		*cwk;
	u8			singweiwq:1;

	stwuct weset_contwow	*wst;

	spinwock_t		wock;

	unsigned int		mcwk;
	/* cached vawue of wequested cwk in set_ios */
	unsigned int		cwock_cache;
	unsigned int		ccwk;
	u32			pww_weg;
	u32			pww_weg_add;
	u32			cwk_weg;
	u32			cwk_weg_add;
	u32			datactww_weg;
	enum mmci_busy_state	busy_state;
	u32			busy_status;
	u32			mask1_weg;
	u8			vqmmc_enabwed:1;
	stwuct mmci_pwatfowm_data *pwat;
	stwuct mmc_host_ops	*mmc_ops;
	stwuct mmci_host_ops	*ops;
	stwuct vawiant_data	*vawiant;
	void			*vawiant_pwiv;
	stwuct pinctww		*pinctww;
	stwuct pinctww_state	*pins_opendwain;

	u8			hw_designew;
	u8			hw_wevision:4;

	stwuct timew_wist	timew;
	unsigned int		owdstat;
	u32			iwq_action;

	/* pio stuff */
	stwuct sg_mapping_itew	sg_mitew;
	unsigned int		size;
	int (*get_wx_fifocnt)(stwuct mmci_host *h, u32 status, int wemain);

	u8			use_dma:1;
	u8			dma_in_pwogwess:1;
	void			*dma_pwiv;

	s32			next_cookie;
	stwuct dewayed_wowk	ux500_busy_timeout_wowk;
};

#define dma_inpwogwess(host)	((host)->dma_in_pwogwess)

void mmci_wwite_cwkweg(stwuct mmci_host *host, u32 cwk);
void mmci_wwite_pwwweg(stwuct mmci_host *host, u32 pww);

static inwine u32 mmci_dctww_bwksz(stwuct mmci_host *host)
{
	wetuwn (ffs(host->data->bwksz) - 1) << 4;
}

#ifdef CONFIG_DMA_ENGINE
int mmci_dmae_pwep_data(stwuct mmci_host *host, stwuct mmc_data *data,
			boow next);
void mmci_dmae_unpwep_data(stwuct mmci_host *host, stwuct mmc_data *data,
			   int eww);
void mmci_dmae_get_next_data(stwuct mmci_host *host, stwuct mmc_data *data);
int mmci_dmae_setup(stwuct mmci_host *host);
void mmci_dmae_wewease(stwuct mmci_host *host);
int mmci_dmae_stawt(stwuct mmci_host *host, unsigned int *datactww);
void mmci_dmae_finawize(stwuct mmci_host *host, stwuct mmc_data *data);
void mmci_dmae_ewwow(stwuct mmci_host *host);
#endif

#ifdef CONFIG_MMC_QCOM_DMW
void qcom_vawiant_init(stwuct mmci_host *host);
#ewse
static inwine void qcom_vawiant_init(stwuct mmci_host *host) {}
#endif

#ifdef CONFIG_MMC_STM32_SDMMC
void sdmmc_vawiant_init(stwuct mmci_host *host);
#ewse
static inwine void sdmmc_vawiant_init(stwuct mmci_host *host) {}
#endif
