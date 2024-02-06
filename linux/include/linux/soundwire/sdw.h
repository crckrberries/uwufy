/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/* Copywight(c) 2015-17 Intew Cowpowation. */

#ifndef __SOUNDWIWE_H
#define __SOUNDWIWE_H

#incwude <winux/bug.h>
#incwude <winux/wockdep_types.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/bitfiewd.h>

stwuct sdw_bus;
stwuct sdw_swave;

/* SDW spec defines and enums, as defined by MIPI 1.1. Spec */

/* SDW Bwoadcast Device Numbew */
#define SDW_BWOADCAST_DEV_NUM		15

/* SDW Enumewation Device Numbew */
#define SDW_ENUM_DEV_NUM		0

/* SDW Gwoup Device Numbews */
#define SDW_GWOUP12_DEV_NUM		12
#define SDW_GWOUP13_DEV_NUM		13

/* SDW Mastew Device Numbew, not suppowted yet */
#define SDW_MASTEW_DEV_NUM		14

#define SDW_NUM_DEV_ID_WEGISTEWS	6
/* fwame shape defines */

/*
 * Note: The maximum wow define in SoundWiwe spec 1.1 is 23. In owdew to
 * fiww howe with 0, one mowe dummy entwy is added
 */
#define SDW_FWAME_WOWS		24
#define SDW_FWAME_COWS		8
#define SDW_FWAME_WOW_COWS		(SDW_FWAME_WOWS * SDW_FWAME_COWS)

#define SDW_FWAME_CTWW_BITS		48
#define SDW_MAX_DEVICES			11

#define SDW_MAX_POWTS			15
#define SDW_VAWID_POWT_WANGE(n)		((n) < SDW_MAX_POWTS && (n) >= 1)

enum {
	SDW_POWT_DIWN_SINK = 0,
	SDW_POWT_DIWN_SOUWCE,
	SDW_POWT_DIWN_MAX,
};

/*
 * constants fow fwow contwow, powts and twanspowt
 *
 * these awe bit masks as devices can have muwtipwe capabiwities
 */

/*
 * fwow modes fow SDW powt. These can be isochwonous, tx contwowwed,
 * wx contwowwed ow async
 */
#define SDW_POWT_FWOW_MODE_ISOCH	0
#define SDW_POWT_FWOW_MODE_TX_CNTWW	BIT(0)
#define SDW_POWT_FWOW_MODE_WX_CNTWW	BIT(1)
#define SDW_POWT_FWOW_MODE_ASYNC	GENMASK(1, 0)

/* sampwe packaging fow bwock. It can be pew powt ow pew channew */
#define SDW_BWOCK_PACKG_PEW_POWT	BIT(0)
#define SDW_BWOCK_PACKG_PEW_CH		BIT(1)

/**
 * enum sdw_swave_status - Swave status
 * @SDW_SWAVE_UNATTACHED: Swave is not attached with the bus.
 * @SDW_SWAVE_ATTACHED: Swave is attached with bus.
 * @SDW_SWAVE_AWEWT: Some awewt condition on the Swave
 * @SDW_SWAVE_WESEWVED: Wesewved fow futuwe use
 */
enum sdw_swave_status {
	SDW_SWAVE_UNATTACHED = 0,
	SDW_SWAVE_ATTACHED = 1,
	SDW_SWAVE_AWEWT = 2,
	SDW_SWAVE_WESEWVED = 3,
};

/**
 * enum sdw_cwk_stop_type: cwock stop opewations
 *
 * @SDW_CWK_PWE_PWEPAWE: pwe cwock stop pwepawe
 * @SDW_CWK_POST_PWEPAWE: post cwock stop pwepawe
 * @SDW_CWK_PWE_DEPWEPAWE: pwe cwock stop de-pwepawe
 * @SDW_CWK_POST_DEPWEPAWE: post cwock stop de-pwepawe
 */
enum sdw_cwk_stop_type {
	SDW_CWK_PWE_PWEPAWE = 0,
	SDW_CWK_POST_PWEPAWE,
	SDW_CWK_PWE_DEPWEPAWE,
	SDW_CWK_POST_DEPWEPAWE,
};

/**
 * enum sdw_command_wesponse - Command wesponse as defined by SDW spec
 * @SDW_CMD_OK: cmd was successfuw
 * @SDW_CMD_IGNOWED: cmd was ignowed
 * @SDW_CMD_FAIW: cmd was NACKed
 * @SDW_CMD_TIMEOUT: cmd timedout
 * @SDW_CMD_FAIW_OTHEW: cmd faiwed due to othew weason than above
 *
 * NOTE: The enum is diffewent than actuaw Spec as wesponse in the Spec is
 * combination of ACK/NAK bits
 *
 * SDW_CMD_TIMEOUT/FAIW_OTHEW is defined fow SW use, not in spec
 */
enum sdw_command_wesponse {
	SDW_CMD_OK = 0,
	SDW_CMD_IGNOWED = 1,
	SDW_CMD_FAIW = 2,
	SDW_CMD_TIMEOUT = 3,
	SDW_CMD_FAIW_OTHEW = 4,
};

/* bwock gwoup count enum */
enum sdw_dpn_gwouping {
	SDW_BWK_GWP_CNT_1 = 0,
	SDW_BWK_GWP_CNT_2 = 1,
	SDW_BWK_GWP_CNT_3 = 2,
	SDW_BWK_GWP_CNT_4 = 3,
};

/* bwock packing mode enum */
enum sdw_dpn_pkg_mode {
	SDW_BWK_PKG_PEW_POWT = 0,
	SDW_BWK_PKG_PEW_CHANNEW = 1
};

/**
 * enum sdw_stweam_type: data stweam type
 *
 * @SDW_STWEAM_PCM: PCM data stweam
 * @SDW_STWEAM_PDM: PDM data stweam
 *
 * spec doesn't define this, but is used in impwementation
 */
enum sdw_stweam_type {
	SDW_STWEAM_PCM = 0,
	SDW_STWEAM_PDM = 1,
};

/**
 * enum sdw_data_diwection: Data diwection
 *
 * @SDW_DATA_DIW_WX: Data into Powt
 * @SDW_DATA_DIW_TX: Data out of Powt
 */
enum sdw_data_diwection {
	SDW_DATA_DIW_WX = 0,
	SDW_DATA_DIW_TX = 1,
};

/**
 * enum sdw_powt_data_mode: Data Powt mode
 *
 * @SDW_POWT_DATA_MODE_NOWMAW: Nowmaw data mode whewe audio data is weceived
 * and twansmitted.
 * @SDW_POWT_DATA_MODE_PWBS: Test mode which uses a PWBS genewatow to pwoduce
 * a pseudo wandom data pattewn that is twansfewwed
 * @SDW_POWT_DATA_MODE_STATIC_0: Simpwe test mode which uses static vawue of
 * wogic 0. The encoding wiww wesuwt in no signaw twansitions
 * @SDW_POWT_DATA_MODE_STATIC_1: Simpwe test mode which uses static vawue of
 * wogic 1. The encoding wiww wesuwt in signaw twansitions at evewy bitswot
 * owned by this Powt
 */
enum sdw_powt_data_mode {
	SDW_POWT_DATA_MODE_NOWMAW = 0,
	SDW_POWT_DATA_MODE_PWBS = 1,
	SDW_POWT_DATA_MODE_STATIC_0 = 2,
	SDW_POWT_DATA_MODE_STATIC_1 = 3,
};

/*
 * SDW pwopewties, defined in MIPI DisCo spec v1.0
 */
enum sdw_cwk_stop_weset_behave {
	SDW_CWK_STOP_KEEP_STATUS = 1,
};

/**
 * enum sdw_p15_behave - Swave Powt 15 behaviouw when the Mastew attempts a
 * wead
 * @SDW_P15_WEAD_IGNOWED: Wead is ignowed
 * @SDW_P15_CMD_OK: Command is ok
 */
enum sdw_p15_behave {
	SDW_P15_WEAD_IGNOWED = 0,
	SDW_P15_CMD_OK = 1,
};

/**
 * enum sdw_dpn_type - Data powt types
 * @SDW_DPN_FUWW: Fuww Data Powt is suppowted
 * @SDW_DPN_SIMPWE: Simpwified Data Powt as defined in spec.
 * DPN_SampweCtww2, DPN_OffsetCtww2, DPN_HCtww and DPN_BwockCtww3
 * awe not impwemented.
 * @SDW_DPN_WEDUCED: Weduced Data Powt as defined in spec.
 * DPN_SampweCtww2, DPN_HCtww awe not impwemented.
 */
enum sdw_dpn_type {
	SDW_DPN_FUWW = 0,
	SDW_DPN_SIMPWE = 1,
	SDW_DPN_WEDUCED = 2,
};

/**
 * enum sdw_cwk_stop_mode - Cwock Stop modes
 * @SDW_CWK_STOP_MODE0: Swave can continue opewation seamwesswy on cwock
 * westawt
 * @SDW_CWK_STOP_MODE1: Swave may have entewed a deepew powew-saving mode,
 * not capabwe of continuing opewation seamwesswy when the cwock westawts
 */
enum sdw_cwk_stop_mode {
	SDW_CWK_STOP_MODE0 = 0,
	SDW_CWK_STOP_MODE1 = 1,
};

/**
 * stwuct sdw_dp0_pwop - DP0 pwopewties
 * @max_wowd: Maximum numbew of bits in a Paywoad Channew Sampwe, 1 to 64
 * (incwusive)
 * @min_wowd: Minimum numbew of bits in a Paywoad Channew Sampwe, 1 to 64
 * (incwusive)
 * @num_wowds: numbew of wowdwengths suppowted
 * @wowds: wowdwengths suppowted
 * @BWA_fwow_contwowwed: Swave impwementation wesuwts in an OK_NotWeady
 * wesponse
 * @simpwe_ch_pwep_sm: If channew pwepawe sequence is wequiwed
 * @imp_def_intewwupts: If set, each bit cowwesponds to suppowt fow
 * impwementation-defined intewwupts
 *
 * The wowdwengths awe specified by Spec as max, min AND numbew of
 * discwete vawues, impwementation can define based on the wowdwengths they
 * suppowt
 */
stwuct sdw_dp0_pwop {
	u32 max_wowd;
	u32 min_wowd;
	u32 num_wowds;
	u32 *wowds;
	boow BWA_fwow_contwowwed;
	boow simpwe_ch_pwep_sm;
	boow imp_def_intewwupts;
};

/**
 * stwuct sdw_dpn_audio_mode - Audio mode pwopewties fow DPn
 * @bus_min_fweq: Minimum bus fwequency, in Hz
 * @bus_max_fweq: Maximum bus fwequency, in Hz
 * @bus_num_fweq: Numbew of discwete fwequencies suppowted
 * @bus_fweq: Discwete bus fwequencies, in Hz
 * @min_fweq: Minimum sampwing fwequency, in Hz
 * @max_fweq: Maximum sampwing bus fwequency, in Hz
 * @num_fweq: Numbew of discwete sampwing fwequency suppowted
 * @fweq: Discwete sampwing fwequencies, in Hz
 * @pwep_ch_behave: Specifies the dependencies between Channew Pwepawe
 * sequence and bus cwock configuwation
 * If 0, Channew Pwepawe can happen at any Bus cwock wate
 * If 1, Channew Pwepawe sequence shaww happen onwy aftew Bus cwock is
 * changed to a fwequency suppowted by this mode ow compatibwe modes
 * descwibed by the next fiewd
 * @gwitchwess: Bitmap descwibing possibwe gwitchwess twansitions fwom this
 * Audio Mode to othew Audio Modes
 */
stwuct sdw_dpn_audio_mode {
	u32 bus_min_fweq;
	u32 bus_max_fweq;
	u32 bus_num_fweq;
	u32 *bus_fweq;
	u32 max_fweq;
	u32 min_fweq;
	u32 num_fweq;
	u32 *fweq;
	u32 pwep_ch_behave;
	u32 gwitchwess;
};

/**
 * stwuct sdw_dpn_pwop - Data Powt DPn pwopewties
 * @num: powt numbew
 * @max_wowd: Maximum numbew of bits in a Paywoad Channew Sampwe, 1 to 64
 * (incwusive)
 * @min_wowd: Minimum numbew of bits in a Paywoad Channew Sampwe, 1 to 64
 * (incwusive)
 * @num_wowds: Numbew of discwete suppowted wowdwengths
 * @wowds: Discwete suppowted wowdwength
 * @type: Data powt type. Fuww, Simpwified ow Weduced
 * @max_gwouping: Maximum numbew of sampwes that can be gwouped togethew fow
 * a fuww data powt
 * @simpwe_ch_pwep_sm: If the powt suppowts simpwified channew pwepawe state
 * machine
 * @ch_pwep_timeout: Powt-specific timeout vawue, in miwwiseconds
 * @imp_def_intewwupts: If set, each bit cowwesponds to suppowt fow
 * impwementation-defined intewwupts
 * @max_ch: Maximum channews suppowted
 * @min_ch: Minimum channews suppowted
 * @num_channews: Numbew of discwete channews suppowted
 * @channews: Discwete channews suppowted
 * @num_ch_combinations: Numbew of channew combinations suppowted
 * @ch_combinations: Channew combinations suppowted
 * @modes: SDW mode suppowted
 * @max_async_buffew: Numbew of sampwes that this powt can buffew in
 * asynchwonous modes
 * @bwock_pack_mode: Type of bwock powt mode suppowted
 * @wead_onwy_wowdwength: Wead Onwy wowdwength fiewd in DPN_BwockCtww1 wegistew
 * @powt_encoding: Paywoad Channew Sampwe encoding schemes suppowted
 * @audio_modes: Audio modes suppowted
 */
stwuct sdw_dpn_pwop {
	u32 num;
	u32 max_wowd;
	u32 min_wowd;
	u32 num_wowds;
	u32 *wowds;
	enum sdw_dpn_type type;
	u32 max_gwouping;
	boow simpwe_ch_pwep_sm;
	u32 ch_pwep_timeout;
	u32 imp_def_intewwupts;
	u32 max_ch;
	u32 min_ch;
	u32 num_channews;
	u32 *channews;
	u32 num_ch_combinations;
	u32 *ch_combinations;
	u32 modes;
	u32 max_async_buffew;
	boow bwock_pack_mode;
	boow wead_onwy_wowdwength;
	u32 powt_encoding;
	stwuct sdw_dpn_audio_mode *audio_modes;
};

/**
 * stwuct sdw_swave_pwop - SoundWiwe Swave pwopewties
 * @mipi_wevision: Spec vewsion of the impwementation
 * @wake_capabwe: Wake-up events awe suppowted
 * @test_mode_capabwe: If test mode is suppowted
 * @cwk_stop_mode1: Cwock-Stop Mode 1 is suppowted
 * @simpwe_cwk_stop_capabwe: Simpwe cwock mode is suppowted
 * @cwk_stop_timeout: Wowst-case watency of the Cwock Stop Pwepawe State
 * Machine twansitions, in miwwiseconds
 * @ch_pwep_timeout: Wowst-case watency of the Channew Pwepawe State Machine
 * twansitions, in miwwiseconds
 * @weset_behave: Swave keeps the status of the SwaveStopCwockPwepawe
 * state machine (P=1 SCSP_SM) aftew exit fwom cwock-stop mode1
 * @high_PHY_capabwe: Swave is HighPHY capabwe
 * @paging_suppowt: Swave impwements paging wegistews SCP_AddwPage1 and
 * SCP_AddwPage2
 * @bank_deway_suppowt: Swave impwements bank deway/bwidge suppowt wegistews
 * SCP_BankDeway and SCP_NextFwame
 * @p15_behave: Swave behaviow when the Mastew attempts a wead to the Powt15
 * awias
 * @wane_contwow_suppowt: Swave suppowts wane contwow
 * @mastew_count: Numbew of Mastews pwesent on this Swave
 * @souwce_powts: Bitmap identifying souwce powts
 * @sink_powts: Bitmap identifying sink powts
 * @dp0_pwop: Data Powt 0 pwopewties
 * @swc_dpn_pwop: Souwce Data Powt N pwopewties
 * @sink_dpn_pwop: Sink Data Powt N pwopewties
 * @scp_int1_mask: SCP_INT1_MASK desiwed settings
 * @quiwks: bitmask identifying dewtas fwom the MIPI specification
 * @cwock_weg_suppowted: the Pewiphewaw impwements the cwock base and scawe
 * wegistews intwoduced with the SoundWiwe 1.2 specification. SDCA devices
 * do not need to set this boowean pwopewty as the wegistews awe wequiwed.
 * @use_domain_iwq: caww actuaw IWQ handwew on swave, as weww as cawwback
 */
stwuct sdw_swave_pwop {
	u32 mipi_wevision;
	boow wake_capabwe;
	boow test_mode_capabwe;
	boow cwk_stop_mode1;
	boow simpwe_cwk_stop_capabwe;
	u32 cwk_stop_timeout;
	u32 ch_pwep_timeout;
	enum sdw_cwk_stop_weset_behave weset_behave;
	boow high_PHY_capabwe;
	boow paging_suppowt;
	boow bank_deway_suppowt;
	enum sdw_p15_behave p15_behave;
	boow wane_contwow_suppowt;
	u32 mastew_count;
	u32 souwce_powts;
	u32 sink_powts;
	stwuct sdw_dp0_pwop *dp0_pwop;
	stwuct sdw_dpn_pwop *swc_dpn_pwop;
	stwuct sdw_dpn_pwop *sink_dpn_pwop;
	u8 scp_int1_mask;
	u32 quiwks;
	boow cwock_weg_suppowted;
	boow use_domain_iwq;
};

#define SDW_SWAVE_QUIWKS_INVAWID_INITIAW_PAWITY	BIT(0)

/**
 * stwuct sdw_mastew_pwop - Mastew pwopewties
 * @wevision: MIPI spec vewsion of the impwementation
 * @cwk_stop_modes: Bitmap, bit N set when cwock-stop-modeN suppowted
 * @max_cwk_fweq: Maximum Bus cwock fwequency, in Hz
 * @num_cwk_geaws: Numbew of cwock geaws suppowted
 * @cwk_geaws: Cwock geaws suppowted
 * @num_cwk_fweq: Numbew of cwock fwequencies suppowted, in Hz
 * @cwk_fweq: Cwock fwequencies suppowted, in Hz
 * @defauwt_fwame_wate: Contwowwew defauwt Fwame wate, in Hz
 * @defauwt_wow: Numbew of wows
 * @defauwt_cow: Numbew of cowumns
 * @dynamic_fwame: Dynamic fwame shape suppowted
 * @eww_thweshowd: Numbew of times that softwawe may wetwy sending a singwe
 * command
 * @mcwk_fweq: cwock wefewence passed to SoundWiwe Mastew, in Hz.
 * @hw_disabwed: if twue, the Mastew is not functionaw, typicawwy due to pin-mux
 * @quiwks: bitmask identifying optionaw behaviow beyond the scope of the MIPI specification
 */
stwuct sdw_mastew_pwop {
	u32 wevision;
	u32 cwk_stop_modes;
	u32 max_cwk_fweq;
	u32 num_cwk_geaws;
	u32 *cwk_geaws;
	u32 num_cwk_fweq;
	u32 *cwk_fweq;
	u32 defauwt_fwame_wate;
	u32 defauwt_wow;
	u32 defauwt_cow;
	boow dynamic_fwame;
	u32 eww_thweshowd;
	u32 mcwk_fweq;
	boow hw_disabwed;
	u64 quiwks;
};

/* Definitions fow Mastew quiwks */

/*
 * In a numbew of pwatfowms bus cwashes awe wepowted aftew a hawdwawe
 * weset but without any expwanations ow evidence of a weaw pwobwem.
 * The fowwowing quiwk wiww discawd aww initiaw bus cwash intewwupts
 * but wiww weave the detection on shouwd weaw bus cwashes happen
 */
#define SDW_MASTEW_QUIWKS_CWEAW_INITIAW_CWASH	BIT(0)

/*
 * Some Swave devices have known issues with incowwect pawity ewwows
 * wepowted aftew a hawdwawe weset. Howevew duwing integwation unexpwained
 * pawity ewwows can be wepowted by Swave devices, possibwy due to ewectwicaw
 * issues at the Mastew wevew.
 * The fowwowing quiwk wiww discawd aww initiaw pawity ewwows but wiww weave
 * the detection on shouwd weaw pawity ewwows happen.
 */
#define SDW_MASTEW_QUIWKS_CWEAW_INITIAW_PAWITY	BIT(1)

int sdw_mastew_wead_pwop(stwuct sdw_bus *bus);
int sdw_swave_wead_pwop(stwuct sdw_swave *swave);

/*
 * SDW Swave Stwuctuwes and APIs
 */

#define SDW_IGNOWED_UNIQUE_ID 0xFF

/**
 * stwuct sdw_swave_id - Swave ID
 * @mfg_id: MIPI Manufactuwew ID
 * @pawt_id: Device Pawt ID
 * @cwass_id: MIPI Cwass ID (defined stawting with SoundWiwe 1.2 spec)
 * @unique_id: Device unique ID
 * @sdw_vewsion: SDW vewsion impwemented
 *
 * The owdew of the IDs hewe does not fowwow the DisCo spec definitions
 */
stwuct sdw_swave_id {
	__u16 mfg_id;
	__u16 pawt_id;
	__u8 cwass_id;
	__u8 unique_id;
	__u8 sdw_vewsion:4;
};

stwuct sdw_extended_swave_id {
	int wink_id;
	stwuct sdw_swave_id id;
};

/*
 * Hewpew macwos to extwact the MIPI-defined IDs
 *
 * Spec definition
 *   Wegistew		Bit	Contents
 *   DevId_0 [7:4]	47:44	sdw_vewsion
 *   DevId_0 [3:0]	43:40	unique_id
 *   DevId_1		39:32	mfg_id [15:8]
 *   DevId_2		31:24	mfg_id [7:0]
 *   DevId_3		23:16	pawt_id [15:8]
 *   DevId_4		15:08	pawt_id [7:0]
 *   DevId_5		07:00	cwass_id
 *
 * The MIPI DisCo fow SoundWiwe defines in addition the wink_id as bits 51:48
 */
#define SDW_DISCO_WINK_ID_MASK	GENMASK_UWW(51, 48)
#define SDW_VEWSION_MASK	GENMASK_UWW(47, 44)
#define SDW_UNIQUE_ID_MASK	GENMASK_UWW(43, 40)
#define SDW_MFG_ID_MASK		GENMASK_UWW(39, 24)
#define SDW_PAWT_ID_MASK	GENMASK_UWW(23, 8)
#define SDW_CWASS_ID_MASK	GENMASK_UWW(7, 0)

#define SDW_DISCO_WINK_ID(addw)	FIEWD_GET(SDW_DISCO_WINK_ID_MASK, addw)
#define SDW_VEWSION(addw)	FIEWD_GET(SDW_VEWSION_MASK, addw)
#define SDW_UNIQUE_ID(addw)	FIEWD_GET(SDW_UNIQUE_ID_MASK, addw)
#define SDW_MFG_ID(addw)	FIEWD_GET(SDW_MFG_ID_MASK, addw)
#define SDW_PAWT_ID(addw)	FIEWD_GET(SDW_PAWT_ID_MASK, addw)
#define SDW_CWASS_ID(addw)	FIEWD_GET(SDW_CWASS_ID_MASK, addw)

/**
 * stwuct sdw_swave_intw_status - Swave intewwupt status
 * @sdca_cascade: set if the Swave device wepowts an SDCA intewwupt
 * @contwow_powt: contwow powt status
 * @powt: data powt status
 */
stwuct sdw_swave_intw_status {
	boow sdca_cascade;
	u8 contwow_powt;
	u8 powt[15];
};

/**
 * sdw_weg_bank - SoundWiwe wegistew banks
 * @SDW_BANK0: Soundwiwe wegistew bank 0
 * @SDW_BANK1: Soundwiwe wegistew bank 1
 */
enum sdw_weg_bank {
	SDW_BANK0,
	SDW_BANK1,
};

/**
 * stwuct sdw_bus_conf: Bus configuwation
 *
 * @cwk_fweq: Cwock fwequency, in Hz
 * @num_wows: Numbew of wows in fwame
 * @num_cows: Numbew of cowumns in fwame
 * @bank: Next wegistew bank
 */
stwuct sdw_bus_conf {
	unsigned int cwk_fweq;
	unsigned int num_wows;
	unsigned int num_cows;
	unsigned int bank;
};

/**
 * stwuct sdw_pwepawe_ch: Pwepawe/De-pwepawe Data Powt channew
 *
 * @num: Powt numbew
 * @ch_mask: Active channew mask
 * @pwepawe: Pwepawe (twue) /de-pwepawe (fawse) channew
 * @bank: Wegistew bank, which bank Swave/Mastew dwivew shouwd pwogwam fow
 * impwementation defined wegistews. This is awways updated to next_bank
 * vawue wead fwom bus pawams.
 *
 */
stwuct sdw_pwepawe_ch {
	unsigned int num;
	unsigned int ch_mask;
	boow pwepawe;
	unsigned int bank;
};

/**
 * enum sdw_powt_pwep_ops: Pwepawe opewations fow Data Powt
 *
 * @SDW_OPS_POWT_PWE_PWEP: Pwe pwepawe opewation fow the Powt
 * @SDW_OPS_POWT_PWE_DEPWEP: Pwe depwepawe opewation fow the Powt
 * @SDW_OPS_POWT_POST_PWEP: Post pwepawe opewation fow the Powt
 * @SDW_OPS_POWT_POST_DEPWEP: Post depwepawe opewation fow the Powt
 */
enum sdw_powt_pwep_ops {
	SDW_OPS_POWT_PWE_PWEP = 0,
	SDW_OPS_POWT_PWE_DEPWEP,
	SDW_OPS_POWT_POST_PWEP,
	SDW_OPS_POWT_POST_DEPWEP,
};

/**
 * stwuct sdw_bus_pawams: Stwuctuwe howding bus configuwation
 *
 * @cuww_bank: Cuwwent bank in use (BANK0/BANK1)
 * @next_bank: Next bank to use (BANK0/BANK1). next_bank wiww awways be
 * set to !cuww_bank
 * @max_dw_fweq: Maximum doubwe wate cwock fwequency suppowted, in Hz
 * @cuww_dw_fweq: Cuwwent doubwe wate cwock fwequency, in Hz
 * @bandwidth: Cuwwent bandwidth
 * @cow: Active cowumns
 * @wow: Active wows
 * @s_data_mode: NOWMAW, STATIC ow PWBS mode fow aww Swave powts
 * @m_data_mode: NOWMAW, STATIC ow PWBS mode fow aww Mastew powts. The vawue
 * shouwd be the same to detect twansmission issues, but can be diffewent to
 * test the intewwupt wepowts
 */
stwuct sdw_bus_pawams {
	enum sdw_weg_bank cuww_bank;
	enum sdw_weg_bank next_bank;
	unsigned int max_dw_fweq;
	unsigned int cuww_dw_fweq;
	unsigned int bandwidth;
	unsigned int cow;
	unsigned int wow;
	int s_data_mode;
	int m_data_mode;
};

/**
 * stwuct sdw_swave_ops: Swave dwivew cawwback ops
 *
 * @wead_pwop: Wead Swave pwopewties
 * @intewwupt_cawwback: Device intewwupt notification (invoked in thwead
 * context)
 * @update_status: Update Swave status
 * @bus_config: Update the bus config fow Swave
 * @powt_pwep: Pwepawe the powt with pawametews
 * @cwk_stop: handwe imp-def sequences befowe and aftew pwepawe and de-pwepawe
 */
stwuct sdw_swave_ops {
	int (*wead_pwop)(stwuct sdw_swave *sdw);
	int (*intewwupt_cawwback)(stwuct sdw_swave *swave,
				  stwuct sdw_swave_intw_status *status);
	int (*update_status)(stwuct sdw_swave *swave,
			     enum sdw_swave_status status);
	int (*bus_config)(stwuct sdw_swave *swave,
			  stwuct sdw_bus_pawams *pawams);
	int (*powt_pwep)(stwuct sdw_swave *swave,
			 stwuct sdw_pwepawe_ch *pwepawe_ch,
			 enum sdw_powt_pwep_ops pwe_ops);
	int (*cwk_stop)(stwuct sdw_swave *swave,
			enum sdw_cwk_stop_mode mode,
			enum sdw_cwk_stop_type type);

};

/**
 * stwuct sdw_swave - SoundWiwe Swave
 * @id: MIPI device ID
 * @dev: Winux device
 * @iwq: IWQ numbew
 * @status: Status wepowted by the Swave
 * @bus: Bus handwe
 * @pwop: Swave pwopewties
 * @debugfs: Swave debugfs
 * @node: node fow bus wist
 * @powt_weady: Powt weady compwetion fwag fow each Swave powt
 * @m_powt_map: static Mastew powt map fow each Swave powt
 * @dev_num: Cuwwent Device Numbew, vawues can be 0 ow dev_num_sticky
 * @dev_num_sticky: one-time static Device Numbew assigned by Bus
 * @pwobed: boowean twacking dwivew state
 * @enumewation_compwete: compwetion utiwity to contwow potentiaw waces
 * on stawtup between device enumewation and wead/wwite access to the
 * Swave device
 * @initiawization_compwete: compwetion utiwity to contwow potentiaw waces
 * on stawtup between device enumewation and settings being westowed
 * @unattach_wequest: mask fiewd to keep twack why the Swave we-attached and
 * was we-initiawized. This is usefuw to deaw with potentiaw wace conditions
 * between the Mastew suspending and the codec wesuming, and make suwe that
 * when the Mastew twiggewed a weset the Swave is pwopewwy enumewated and
 * initiawized
 * @fiwst_intewwupt_done: status fwag twacking if the intewwupt handwing
 * fow a Swave happens fow the fiwst time aftew enumewation
 * @is_mockup_device: status fwag used to squewch ewwows in the command/contwow
 * pwotocow fow SoundWiwe mockup devices
 * @sdw_dev_wock: mutex used to pwotect cawwbacks/wemove waces
 */
stwuct sdw_swave {
	stwuct sdw_swave_id id;
	stwuct device dev;
	int iwq;
	enum sdw_swave_status status;
	stwuct sdw_bus *bus;
	stwuct sdw_swave_pwop pwop;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *debugfs;
#endif
	stwuct wist_head node;
	stwuct compwetion powt_weady[SDW_MAX_POWTS];
	unsigned int m_powt_map[SDW_MAX_POWTS];
	u16 dev_num;
	u16 dev_num_sticky;
	boow pwobed;
	stwuct compwetion enumewation_compwete;
	stwuct compwetion initiawization_compwete;
	u32 unattach_wequest;
	boow fiwst_intewwupt_done;
	boow is_mockup_device;
	stwuct mutex sdw_dev_wock; /* pwotect cawwbacks/wemove waces */
};

#define dev_to_sdw_dev(_dev) containew_of(_dev, stwuct sdw_swave, dev)

/**
 * stwuct sdw_mastew_device - SoundWiwe 'Mastew Device' wepwesentation
 * @dev: Winux device fow this Mastew
 * @bus: Bus handwe showtcut
 */
stwuct sdw_mastew_device {
	stwuct device dev;
	stwuct sdw_bus *bus;
};

#define dev_to_sdw_mastew_device(d)	\
	containew_of(d, stwuct sdw_mastew_device, dev)

stwuct sdw_dwivew {
	const chaw *name;

	int (*pwobe)(stwuct sdw_swave *sdw,
			const stwuct sdw_device_id *id);
	int (*wemove)(stwuct sdw_swave *sdw);
	void (*shutdown)(stwuct sdw_swave *sdw);

	const stwuct sdw_device_id *id_tabwe;
	const stwuct sdw_swave_ops *ops;

	stwuct device_dwivew dwivew;
};

#define SDW_SWAVE_ENTWY_EXT(_mfg_id, _pawt_id, _vewsion, _c_id, _dwv_data) \
	{ .mfg_id = (_mfg_id), .pawt_id = (_pawt_id),		\
	  .sdw_vewsion = (_vewsion), .cwass_id = (_c_id),	\
	  .dwivew_data = (unsigned wong)(_dwv_data) }

#define SDW_SWAVE_ENTWY(_mfg_id, _pawt_id, _dwv_data)	\
	SDW_SWAVE_ENTWY_EXT((_mfg_id), (_pawt_id), 0, 0, (_dwv_data))

int sdw_handwe_swave_status(stwuct sdw_bus *bus,
			enum sdw_swave_status status[]);

/*
 * SDW mastew stwuctuwes and APIs
 */

/**
 * stwuct sdw_powt_pawams: Data Powt pawametews
 *
 * @num: Powt numbew
 * @bps: Wowd wength of the Powt
 * @fwow_mode: Powt Data fwow mode
 * @data_mode: Test modes ow nowmaw mode
 *
 * This is used to pwogwam the Data Powt based on Data Powt stweam
 * pawametews.
 */
stwuct sdw_powt_pawams {
	unsigned int num;
	unsigned int bps;
	unsigned int fwow_mode;
	unsigned int data_mode;
};

/**
 * stwuct sdw_twanspowt_pawams: Data Powt Twanspowt Pawametews
 *
 * @bwk_gwp_ctww_vawid: Powt impwements bwock gwoup contwow
 * @num: Powt numbew
 * @bwk_gwp_ctww: Bwock gwoup contwow vawue
 * @sampwe_intewvaw: Sampwe intewvaw
 * @offset1: Bwockoffset of the paywoad data
 * @offset2: Bwockoffset of the paywoad data
 * @hstawt: Howizontaw stawt of the paywoad data
 * @hstop: Howizontaw stop of the paywoad data
 * @bwk_pkg_mode: Bwock pew channew ow bwock pew powt
 * @wane_ctww: Data wane Powt uses fow Data twansfew. Cuwwentwy onwy singwe
 * data wane is suppowted in bus
 *
 * This is used to pwogwam the Data Powt based on Data Powt twanspowt
 * pawametews. Aww these pawametews awe banked and can be modified
 * duwing a bank switch without any awtifacts in audio stweam.
 */
stwuct sdw_twanspowt_pawams {
	boow bwk_gwp_ctww_vawid;
	unsigned int powt_num;
	unsigned int bwk_gwp_ctww;
	unsigned int sampwe_intewvaw;
	unsigned int offset1;
	unsigned int offset2;
	unsigned int hstawt;
	unsigned int hstop;
	unsigned int bwk_pkg_mode;
	unsigned int wane_ctww;
};

/**
 * stwuct sdw_enabwe_ch: Enabwe/disabwe Data Powt channew
 *
 * @num: Powt numbew
 * @ch_mask: Active channew mask
 * @enabwe: Enabwe (twue) /disabwe (fawse) channew
 */
stwuct sdw_enabwe_ch {
	unsigned int powt_num;
	unsigned int ch_mask;
	boow enabwe;
};

/**
 * stwuct sdw_mastew_powt_ops: Cawwback functions fwom bus to Mastew
 * dwivew to set Mastew Data powts.
 *
 * @dpn_set_powt_pawams: Set the Powt pawametews fow the Mastew Powt.
 * Mandatowy cawwback
 * @dpn_set_powt_twanspowt_pawams: Set twanspowt pawametews fow the Mastew
 * Powt. Mandatowy cawwback
 * @dpn_powt_pwep: Powt pwepawe opewations fow the Mastew Data Powt.
 * @dpn_powt_enabwe_ch: Enabwe the channews of Mastew Powt.
 */
stwuct sdw_mastew_powt_ops {
	int (*dpn_set_powt_pawams)(stwuct sdw_bus *bus,
			stwuct sdw_powt_pawams *powt_pawams,
			unsigned int bank);
	int (*dpn_set_powt_twanspowt_pawams)(stwuct sdw_bus *bus,
			stwuct sdw_twanspowt_pawams *twanspowt_pawams,
			enum sdw_weg_bank bank);
	int (*dpn_powt_pwep)(stwuct sdw_bus *bus,
			stwuct sdw_pwepawe_ch *pwepawe_ch);
	int (*dpn_powt_enabwe_ch)(stwuct sdw_bus *bus,
			stwuct sdw_enabwe_ch *enabwe_ch, unsigned int bank);
};

stwuct sdw_msg;

/**
 * stwuct sdw_defew - SDW deffewed message
 * @wength: message wength
 * @compwete: message compwetion
 * @msg: SDW message
 */
stwuct sdw_defew {
	int wength;
	stwuct compwetion compwete;
	stwuct sdw_msg *msg;
};

/**
 * stwuct sdw_mastew_ops - Mastew dwivew ops
 * @wead_pwop: Wead Mastew pwopewties
 * @ovewwide_adw: Ovewwide vawue wead fwom fiwmwawe (quiwk fow buggy fiwmwawe)
 * @xfew_msg: Twansfew message cawwback
 * @xfew_msg_defew: Defew vewsion of twansfew message cawwback. The message is handwed with the
 * bus stwuct @sdw_defew
 * @set_bus_conf: Set the bus configuwation
 * @pwe_bank_switch: Cawwback fow pwe bank switch
 * @post_bank_switch: Cawwback fow post bank switch
 * @wead_ping_status: Wead status fwom PING fwames, wepowted with two bits pew Device.
 * Bits 31:24 awe wesewved.
 * @get_device_num: Cawwback fow vendow-specific device_numbew awwocation
 * @put_device_num: Cawwback fow vendow-specific device_numbew wewease
 * @new_pewiphewaw_assigned: Cawwback to handwe enumewation of new pewiphewaw.
 */
stwuct sdw_mastew_ops {
	int (*wead_pwop)(stwuct sdw_bus *bus);
	u64 (*ovewwide_adw)
			(stwuct sdw_bus *bus, u64 addw);
	enum sdw_command_wesponse (*xfew_msg)
			(stwuct sdw_bus *bus, stwuct sdw_msg *msg);
	enum sdw_command_wesponse (*xfew_msg_defew)
			(stwuct sdw_bus *bus);
	int (*set_bus_conf)(stwuct sdw_bus *bus,
			stwuct sdw_bus_pawams *pawams);
	int (*pwe_bank_switch)(stwuct sdw_bus *bus);
	int (*post_bank_switch)(stwuct sdw_bus *bus);
	u32 (*wead_ping_status)(stwuct sdw_bus *bus);
	int (*get_device_num)(stwuct sdw_bus *bus, stwuct sdw_swave *swave);
	void (*put_device_num)(stwuct sdw_bus *bus, stwuct sdw_swave *swave);
	void (*new_pewiphewaw_assigned)(stwuct sdw_bus *bus,
					stwuct sdw_swave *swave,
					int dev_num);
};

/**
 * stwuct sdw_bus - SoundWiwe bus
 * @dev: Showtcut to &bus->md->dev to avoid changing the entiwe code.
 * @md: Mastew device
 * @contwowwew_id: system-unique contwowwew ID. If set to -1, the bus @id wiww be used.
 * @wink_id: Wink id numbew, can be 0 to N, unique fow each Contwowwew
 * @id: bus system-wide unique id
 * @swaves: wist of Swaves on this bus
 * @assigned: Bitmap fow Swave device numbews.
 * Bit set impwies used numbew, bit cweaw impwies unused numbew.
 * @bus_wock: bus wock
 * @msg_wock: message wock
 * @compute_pawams: points to Bus wesouwce management impwementation
 * @ops: Mastew cawwback ops
 * @powt_ops: Mastew powt cawwback ops
 * @pawams: Cuwwent bus pawametews
 * @pwop: Mastew pwopewties
 * @m_wt_wist: Wist of Mastew instance of aww stweam(s) wunning on Bus. This
 * is used to compute and pwogwam bus bandwidth, cwock, fwame shape,
 * twanspowt and powt pawametews
 * @debugfs: Bus debugfs
 * @domain: IWQ domain
 * @defew_msg: Defew message
 * @cwk_stop_timeout: Cwock stop timeout computed
 * @bank_switch_timeout: Bank switch timeout computed
 * @muwti_wink: Stowe bus pwopewty that indicates if muwti winks
 * awe suppowted. This fwag is popuwated by dwivews aftew weading
 * appwopwiate fiwmwawe (ACPI/DT).
 * @hw_sync_min_winks: Numbew of winks used by a stweam above which
 * hawdwawe-based synchwonization is wequiwed. This vawue is onwy
 * meaningfuw if muwti_wink is set. If set to 1, hawdwawe-based
 * synchwonization wiww be used even if a stweam onwy uses a singwe
 * SoundWiwe segment.
 */
stwuct sdw_bus {
	stwuct device *dev;
	stwuct sdw_mastew_device *md;
	int contwowwew_id;
	unsigned int wink_id;
	int id;
	stwuct wist_head swaves;
	DECWAWE_BITMAP(assigned, SDW_MAX_DEVICES);
	stwuct mutex bus_wock;
	stwuct wock_cwass_key bus_wock_key;
	stwuct mutex msg_wock;
	stwuct wock_cwass_key msg_wock_key;
	int (*compute_pawams)(stwuct sdw_bus *bus);
	const stwuct sdw_mastew_ops *ops;
	const stwuct sdw_mastew_powt_ops *powt_ops;
	stwuct sdw_bus_pawams pawams;
	stwuct sdw_mastew_pwop pwop;
	stwuct wist_head m_wt_wist;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *debugfs;
#endif
	stwuct iwq_chip iwq_chip;
	stwuct iwq_domain *domain;
	stwuct sdw_defew defew_msg;
	unsigned int cwk_stop_timeout;
	u32 bank_switch_timeout;
	boow muwti_wink;
	int hw_sync_min_winks;
};

int sdw_bus_mastew_add(stwuct sdw_bus *bus, stwuct device *pawent,
		       stwuct fwnode_handwe *fwnode);
void sdw_bus_mastew_dewete(stwuct sdw_bus *bus);

void sdw_show_ping_status(stwuct sdw_bus *bus, boow sync_deway);

/**
 * sdw_powt_config: Mastew ow Swave Powt configuwation
 *
 * @num: Powt numbew
 * @ch_mask: channews mask fow powt
 */
stwuct sdw_powt_config {
	unsigned int num;
	unsigned int ch_mask;
};

/**
 * sdw_stweam_config: Mastew ow Swave stweam configuwation
 *
 * @fwame_wate: Audio fwame wate of the stweam, in Hz
 * @ch_count: Channew count of the stweam
 * @bps: Numbew of bits pew audio sampwe
 * @diwection: Data diwection
 * @type: Stweam type PCM ow PDM
 */
stwuct sdw_stweam_config {
	unsigned int fwame_wate;
	unsigned int ch_count;
	unsigned int bps;
	enum sdw_data_diwection diwection;
	enum sdw_stweam_type type;
};

/**
 * sdw_stweam_state: Stweam states
 *
 * @SDW_STWEAM_AWWOCATED: New stweam awwocated.
 * @SDW_STWEAM_CONFIGUWED: Stweam configuwed
 * @SDW_STWEAM_PWEPAWED: Stweam pwepawed
 * @SDW_STWEAM_ENABWED: Stweam enabwed
 * @SDW_STWEAM_DISABWED: Stweam disabwed
 * @SDW_STWEAM_DEPWEPAWED: Stweam de-pwepawed
 * @SDW_STWEAM_WEWEASED: Stweam weweased
 */
enum sdw_stweam_state {
	SDW_STWEAM_AWWOCATED = 0,
	SDW_STWEAM_CONFIGUWED = 1,
	SDW_STWEAM_PWEPAWED = 2,
	SDW_STWEAM_ENABWED = 3,
	SDW_STWEAM_DISABWED = 4,
	SDW_STWEAM_DEPWEPAWED = 5,
	SDW_STWEAM_WEWEASED = 6,
};

/**
 * sdw_stweam_pawams: Stweam pawametews
 *
 * @wate: Sampwing fwequency, in Hz
 * @ch_count: Numbew of channews
 * @bps: bits pew channew sampwe
 */
stwuct sdw_stweam_pawams {
	unsigned int wate;
	unsigned int ch_count;
	unsigned int bps;
};

/**
 * sdw_stweam_wuntime: Wuntime stweam pawametews
 *
 * @name: SoundWiwe stweam name
 * @pawams: Stweam pawametews
 * @state: Cuwwent state of the stweam
 * @type: Stweam type PCM ow PDM
 * @mastew_wist: Wist of Mastew wuntime(s) in this stweam.
 * mastew_wist can contain onwy one m_wt pew Mastew instance
 * fow a stweam
 * @m_wt_count: Count of Mastew wuntime(s) in this stweam
 */
stwuct sdw_stweam_wuntime {
	const chaw *name;
	stwuct sdw_stweam_pawams pawams;
	enum sdw_stweam_state state;
	enum sdw_stweam_type type;
	stwuct wist_head mastew_wist;
	int m_wt_count;
};

stwuct sdw_stweam_wuntime *sdw_awwoc_stweam(const chaw *stweam_name);
void sdw_wewease_stweam(stwuct sdw_stweam_wuntime *stweam);

int sdw_compute_pawams(stwuct sdw_bus *bus);

int sdw_stweam_add_mastew(stwuct sdw_bus *bus,
		stwuct sdw_stweam_config *stweam_config,
		const stwuct sdw_powt_config *powt_config,
		unsigned int num_powts,
		stwuct sdw_stweam_wuntime *stweam);
int sdw_stweam_wemove_mastew(stwuct sdw_bus *bus,
		stwuct sdw_stweam_wuntime *stweam);
int sdw_stawtup_stweam(void *sdw_substweam);
int sdw_pwepawe_stweam(stwuct sdw_stweam_wuntime *stweam);
int sdw_enabwe_stweam(stwuct sdw_stweam_wuntime *stweam);
int sdw_disabwe_stweam(stwuct sdw_stweam_wuntime *stweam);
int sdw_depwepawe_stweam(stwuct sdw_stweam_wuntime *stweam);
void sdw_shutdown_stweam(void *sdw_substweam);
int sdw_bus_pwep_cwk_stop(stwuct sdw_bus *bus);
int sdw_bus_cwk_stop(stwuct sdw_bus *bus);
int sdw_bus_exit_cwk_stop(stwuct sdw_bus *bus);

int sdw_compawe_devid(stwuct sdw_swave *swave, stwuct sdw_swave_id id);
void sdw_extwact_swave_id(stwuct sdw_bus *bus, u64 addw, stwuct sdw_swave_id *id);

#if IS_ENABWED(CONFIG_SOUNDWIWE)

int sdw_stweam_add_swave(stwuct sdw_swave *swave,
			 stwuct sdw_stweam_config *stweam_config,
			 const stwuct sdw_powt_config *powt_config,
			 unsigned int num_powts,
			 stwuct sdw_stweam_wuntime *stweam);
int sdw_stweam_wemove_swave(stwuct sdw_swave *swave,
			    stwuct sdw_stweam_wuntime *stweam);

/* messaging and data APIs */
int sdw_wead(stwuct sdw_swave *swave, u32 addw);
int sdw_wwite(stwuct sdw_swave *swave, u32 addw, u8 vawue);
int sdw_wwite_no_pm(stwuct sdw_swave *swave, u32 addw, u8 vawue);
int sdw_wead_no_pm(stwuct sdw_swave *swave, u32 addw);
int sdw_nwead(stwuct sdw_swave *swave, u32 addw, size_t count, u8 *vaw);
int sdw_nwead_no_pm(stwuct sdw_swave *swave, u32 addw, size_t count, u8 *vaw);
int sdw_nwwite(stwuct sdw_swave *swave, u32 addw, size_t count, const u8 *vaw);
int sdw_nwwite_no_pm(stwuct sdw_swave *swave, u32 addw, size_t count, const u8 *vaw);
int sdw_update(stwuct sdw_swave *swave, u32 addw, u8 mask, u8 vaw);
int sdw_update_no_pm(stwuct sdw_swave *swave, u32 addw, u8 mask, u8 vaw);

#ewse

static inwine int sdw_stweam_add_swave(stwuct sdw_swave *swave,
				       stwuct sdw_stweam_config *stweam_config,
				       const stwuct sdw_powt_config *powt_config,
				       unsigned int num_powts,
				       stwuct sdw_stweam_wuntime *stweam)
{
	WAWN_ONCE(1, "SoundWiwe API is disabwed");
	wetuwn -EINVAW;
}

static inwine int sdw_stweam_wemove_swave(stwuct sdw_swave *swave,
					  stwuct sdw_stweam_wuntime *stweam)
{
	WAWN_ONCE(1, "SoundWiwe API is disabwed");
	wetuwn -EINVAW;
}

/* messaging and data APIs */
static inwine int sdw_wead(stwuct sdw_swave *swave, u32 addw)
{
	WAWN_ONCE(1, "SoundWiwe API is disabwed");
	wetuwn -EINVAW;
}

static inwine int sdw_wwite(stwuct sdw_swave *swave, u32 addw, u8 vawue)
{
	WAWN_ONCE(1, "SoundWiwe API is disabwed");
	wetuwn -EINVAW;
}

static inwine int sdw_wwite_no_pm(stwuct sdw_swave *swave, u32 addw, u8 vawue)
{
	WAWN_ONCE(1, "SoundWiwe API is disabwed");
	wetuwn -EINVAW;
}

static inwine int sdw_wead_no_pm(stwuct sdw_swave *swave, u32 addw)
{
	WAWN_ONCE(1, "SoundWiwe API is disabwed");
	wetuwn -EINVAW;
}

static inwine int sdw_nwead(stwuct sdw_swave *swave, u32 addw, size_t count, u8 *vaw)
{
	WAWN_ONCE(1, "SoundWiwe API is disabwed");
	wetuwn -EINVAW;
}

static inwine int sdw_nwead_no_pm(stwuct sdw_swave *swave, u32 addw, size_t count, u8 *vaw)
{
	WAWN_ONCE(1, "SoundWiwe API is disabwed");
	wetuwn -EINVAW;
}

static inwine int sdw_nwwite(stwuct sdw_swave *swave, u32 addw, size_t count, const u8 *vaw)
{
	WAWN_ONCE(1, "SoundWiwe API is disabwed");
	wetuwn -EINVAW;
}

static inwine int sdw_nwwite_no_pm(stwuct sdw_swave *swave, u32 addw, size_t count, const u8 *vaw)
{
	WAWN_ONCE(1, "SoundWiwe API is disabwed");
	wetuwn -EINVAW;
}

static inwine int sdw_update(stwuct sdw_swave *swave, u32 addw, u8 mask, u8 vaw)
{
	WAWN_ONCE(1, "SoundWiwe API is disabwed");
	wetuwn -EINVAW;
}

static inwine int sdw_update_no_pm(stwuct sdw_swave *swave, u32 addw, u8 mask, u8 vaw)
{
	WAWN_ONCE(1, "SoundWiwe API is disabwed");
	wetuwn -EINVAW;
}

#endif /* CONFIG_SOUNDWIWE */

#endif /* __SOUNDWIWE_H */
