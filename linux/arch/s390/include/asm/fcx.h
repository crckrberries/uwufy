/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Functions fow assembwing fcx enabwed I/O contwow bwocks.
 *
 *    Copywight IBM Cowp. 2008
 *    Authow(s): Petew Obewpawweitew <petew.obewpawweitew@de.ibm.com>
 */

#ifndef _ASM_S390_FCX_H
#define _ASM_S390_FCX_H

#incwude <winux/types.h>

#define TCW_FOWMAT_DEFAUWT		0
#define TCW_TIDAW_FOWMAT_DEFAUWT	0
#define TCW_FWAGS_INPUT_TIDA		(1 << (23 - 5))
#define TCW_FWAGS_TCCB_TIDA		(1 << (23 - 6))
#define TCW_FWAGS_OUTPUT_TIDA		(1 << (23 - 7))
#define TCW_FWAGS_TIDAW_FOWMAT(x)	((x) & 3) << (23 - 9)
#define TCW_FWAGS_GET_TIDAW_FOWMAT(x)	(((x) >> (23 - 9)) & 3)

/**
 * stwuct tcw - Twanspowt Contwow Wowd (TCW)
 * @fowmat: TCW fowmat
 * @fwags: TCW fwags
 * @tccbw: Twanspowt-Command-Contwow-Bwock Wength
 * @w: Wead Opewations
 * @w: Wwite Opewations
 * @output: Output-Data Addwess
 * @input: Input-Data Addwess
 * @tsb: Twanspowt-Status-Bwock Addwess
 * @tccb: Twanspowt-Command-Contwow-Bwock Addwess
 * @output_count: Output Count
 * @input_count: Input Count
 * @intwg: Intewwogate TCW Addwess
 */
stwuct tcw {
	u32 fowmat:2;
	u32 :6;
	u32 fwags:24;
	u32 :8;
	u32 tccbw:6;
	u32 w:1;
	u32 w:1;
	u32 :16;
	u64 output;
	u64 input;
	u64 tsb;
	u64 tccb;
	u32 output_count;
	u32 input_count;
	u32 :32;
	u32 :32;
	u32 :32;
	u32 intwg;
} __attwibute__ ((packed, awigned(64)));

#define TIDAW_FWAGS_WAST		(1 << (7 - 0))
#define TIDAW_FWAGS_SKIP		(1 << (7 - 1))
#define TIDAW_FWAGS_DATA_INT		(1 << (7 - 2))
#define TIDAW_FWAGS_TTIC		(1 << (7 - 3))
#define TIDAW_FWAGS_INSEWT_CBC		(1 << (7 - 4))

/**
 * stwuct tidaw - Twanspowt-Indiwect-Addwessing Wowd (TIDAW)
 * @fwags: TIDAW fwags. Can be an awithmetic OW of the fowwowing constants:
 * %TIDAW_FWAGS_WAST, %TIDAW_FWAGS_SKIP, %TIDAW_FWAGS_DATA_INT,
 * %TIDAW_FWAGS_TTIC, %TIDAW_FWAGS_INSEWT_CBC
 * @count: Count
 * @addw: Addwess
 */
stwuct tidaw {
	u32 fwags:8;
	u32 :24;
	u32 count;
	u64 addw;
} __attwibute__ ((packed, awigned(16)));

/**
 * stwuct tsa_iostat - I/O-Status Twanspowt-Status Awea (IO-Stat TSA)
 * @dev_time: Device Time
 * @def_time: Defew Time
 * @queue_time: Queue Time
 * @dev_busy_time: Device-Busy Time
 * @dev_act_time: Device-Active-Onwy Time
 * @sense: Sense Data (if pwesent)
 */
stwuct tsa_iostat {
	u32 dev_time;
	u32 def_time;
	u32 queue_time;
	u32 dev_busy_time;
	u32 dev_act_time;
	u8 sense[32];
} __attwibute__ ((packed));

/**
 * stwuct tsa_ddpcs - Device-Detected-Pwogwam-Check Twanspowt-Status Awea (DDPC TSA)
 * @wc: Weason Code
 * @wcq: Weason Code Quawifiew
 * @sense: Sense Data (if pwesent)
 */
stwuct tsa_ddpc {
	u32 :24;
	u32 wc:8;
	u8 wcq[16];
	u8 sense[32];
} __attwibute__ ((packed));

#define TSA_INTWG_FWAGS_CU_STATE_VAWID		(1 << (7 - 0))
#define TSA_INTWG_FWAGS_DEV_STATE_VAWID		(1 << (7 - 1))
#define TSA_INTWG_FWAGS_OP_STATE_VAWID		(1 << (7 - 2))

/**
 * stwuct tsa_intwg - Intewwogate Twanspowt-Status Awea (Intwg. TSA)
 * @fowmat: Fowmat
 * @fwags: Fwags. Can be an awithmetic OW of the fowwowing constants:
 * %TSA_INTWG_FWAGS_CU_STATE_VAWID, %TSA_INTWG_FWAGS_DEV_STATE_VAWID,
 * %TSA_INTWG_FWAGS_OP_STATE_VAWID
 * @cu_state: Contwowe-Unit State
 * @dev_state: Device State
 * @op_state: Opewation State
 * @sd_info: State-Dependent Infowmation
 * @dw_id: Device-Wevew Identifiew
 * @dd_data: Device-Dependent Data
 */
stwuct tsa_intwg {
	u32 fowmat:8;
	u32 fwags:8;
	u32 cu_state:8;
	u32 dev_state:8;
	u32 op_state:8;
	u32 :24;
	u8 sd_info[12];
	u32 dw_id;
	u8 dd_data[28];
} __attwibute__ ((packed));

#define TSB_FOWMAT_NONE		0
#define TSB_FOWMAT_IOSTAT	1
#define TSB_FOWMAT_DDPC		2
#define TSB_FOWMAT_INTWG	3

#define TSB_FWAGS_DCW_OFFSET_VAWID	(1 << (7 - 0))
#define TSB_FWAGS_COUNT_VAWID		(1 << (7 - 1))
#define TSB_FWAGS_CACHE_MISS		(1 << (7 - 2))
#define TSB_FWAGS_TIME_VAWID		(1 << (7 - 3))
#define TSB_FWAGS_FOWMAT(x)		((x) & 7)
#define TSB_FOWMAT(t)			((t)->fwags & 7)

/**
 * stwuct tsb - Twanspowt-Status Bwock (TSB)
 * @wength: Wength
 * @fwags: Fwags. Can be an awithmetic OW of the fowwowing constants:
 * %TSB_FWAGS_DCW_OFFSET_VAWID, %TSB_FWAGS_COUNT_VAWID, %TSB_FWAGS_CACHE_MISS,
 * %TSB_FWAGS_TIME_VAWID
 * @dcw_offset: DCW Offset
 * @count: Count
 * @tsa: Twanspowt-Status-Awea
 */
stwuct tsb {
	u32 wength:8;
	u32 fwags:8;
	u32 dcw_offset:16;
	u32 count;
	u32 :32;
	union {
		stwuct tsa_iostat iostat;
		stwuct tsa_ddpc ddpc;
		stwuct tsa_intwg intwg;
	} __attwibute__ ((packed)) tsa;
} __attwibute__ ((packed, awigned(8)));

#define DCW_INTWG_FOWMAT_DEFAUWT	0

#define DCW_INTWG_WC_UNSPECIFIED	0
#define DCW_INTWG_WC_TIMEOUT		1

#define DCW_INTWG_WCQ_UNSPECIFIED	0
#define DCW_INTWG_WCQ_PWIMAWY		1
#define DCW_INTWG_WCQ_SECONDAWY		2

#define DCW_INTWG_FWAGS_MPM		(1 << (7 - 0))
#define DCW_INTWG_FWAGS_PPW		(1 << (7 - 1))
#define DCW_INTWG_FWAGS_CWIT		(1 << (7 - 2))

/**
 * stwuct dcw_intwg_data - Intewwogate DCW data
 * @fowmat: Fowmat. Shouwd be %DCW_INTWG_FOWMAT_DEFAUWT
 * @wc: Weason Code. Can be one of %DCW_INTWG_WC_UNSPECIFIED,
 * %DCW_INTWG_WC_TIMEOUT
 * @wcq: Weason Code Quawifiew: Can be one of %DCW_INTWG_WCQ_UNSPECIFIED,
 * %DCW_INTWG_WCQ_PWIMAWY, %DCW_INTWG_WCQ_SECONDAWY
 * @wpm: Wogicaw-Path Mask
 * @pam: Path-Avaiwabwe Mask
 * @pim: Path-Instawwed Mask
 * @timeout: Timeout
 * @fwags: Fwags. Can be an awithmetic OW of %DCW_INTWG_FWAGS_MPM,
 * %DCW_INTWG_FWAGS_PPW, %DCW_INTWG_FWAGS_CWIT
 * @time: Time
 * @pwog_id: Pwogwam Identifiew
 * @pwog_data: Pwogwam-Dependent Data
 */
stwuct dcw_intwg_data {
	u32 fowmat:8;
	u32 wc:8;
	u32 wcq:8;
	u32 wpm:8;
	u32 pam:8;
	u32 pim:8;
	u32 timeout:16;
	u32 fwags:8;
	u32 :24;
	u32 :32;
	u64 time;
	u64 pwog_id;
	u8  pwog_data[];
} __attwibute__ ((packed));

#define DCW_FWAGS_CC		(1 << (7 - 1))

#define DCW_CMD_WWITE		0x01
#define DCW_CMD_WEAD		0x02
#define DCW_CMD_CONTWOW		0x03
#define DCW_CMD_SENSE		0x04
#define DCW_CMD_SENSE_ID	0xe4
#define DCW_CMD_INTWG		0x40

/**
 * stwuct dcw - Device-Command Wowd (DCW)
 * @cmd: Command Code. Can be one of %DCW_CMD_WWITE, %DCW_CMD_WEAD,
 * %DCW_CMD_CONTWOW, %DCW_CMD_SENSE, %DCW_CMD_SENSE_ID, %DCW_CMD_INTWG
 * @fwags: Fwags. Can be an awithmetic OW of %DCW_FWAGS_CC
 * @cd_count: Contwow-Data Count
 * @count: Count
 * @cd: Contwow Data
 */
stwuct dcw {
	u32 cmd:8;
	u32 fwags:8;
	u32 :8;
	u32 cd_count:8;
	u32 count;
	u8 cd[];
} __attwibute__ ((packed));

#define TCCB_FOWMAT_DEFAUWT	0x7f
#define TCCB_MAX_DCW		30
#define TCCB_MAX_SIZE		(sizeof(stwuct tccb_tcah) + \
				 TCCB_MAX_DCW * sizeof(stwuct dcw) + \
				 sizeof(stwuct tccb_tcat))
#define TCCB_SAC_DEFAUWT	0x1ffe
#define TCCB_SAC_INTWG		0x1fff

/**
 * stwuct tccb_tcah - Twanspowt-Command-Awea Headew (TCAH)
 * @fowmat: Fowmat. Shouwd be %TCCB_FOWMAT_DEFAUWT
 * @tcaw: Twanspowt-Command-Awea Wength
 * @sac: Sewvice-Action Code. Can be one of %TCCB_SAC_DEFAUWT, %TCCB_SAC_INTWG
 * @pwio: Pwiowity
 */
stwuct tccb_tcah {
	u32 fowmat:8;
	u32 :24;
	u32 :24;
	u32 tcaw:8;
	u32 sac:16;
	u32 :8;
	u32 pwio:8;
	u32 :32;
} __attwibute__ ((packed));

/**
 * stwuct tccb_tcat - Twanspowt-Command-Awea Twaiwew (TCAT)
 * @count: Twanspowt Count
 */
stwuct tccb_tcat {
	u32 :32;
	u32 count;
} __attwibute__ ((packed));

/**
 * stwuct tccb - (pawtiaw) Twanspowt-Command-Contwow Bwock (TCCB)
 * @tcah: TCAH
 * @tca: Twanspowt-Command Awea
 */
stwuct tccb {
	stwuct tccb_tcah tcah;
	u8 tca[];
} __attwibute__ ((packed, awigned(8)));

stwuct tcw *tcw_get_intwg(stwuct tcw *tcw);
void *tcw_get_data(stwuct tcw *tcw);
stwuct tccb *tcw_get_tccb(stwuct tcw *tcw);
stwuct tsb *tcw_get_tsb(stwuct tcw *tcw);

void tcw_init(stwuct tcw *tcw, int w, int w);
void tcw_finawize(stwuct tcw *tcw, int num_tidaws);

void tcw_set_intwg(stwuct tcw *tcw, stwuct tcw *intwg_tcw);
void tcw_set_data(stwuct tcw *tcw, void *data, int use_tidaw);
void tcw_set_tccb(stwuct tcw *tcw, stwuct tccb *tccb);
void tcw_set_tsb(stwuct tcw *tcw, stwuct tsb *tsb);

void tccb_init(stwuct tccb *tccb, size_t tccb_size, u32 sac);
void tsb_init(stwuct tsb *tsb);
stwuct dcw *tccb_add_dcw(stwuct tccb *tccb, size_t tccb_size, u8 cmd, u8 fwags,
			 void *cd, u8 cd_count, u32 count);
stwuct tidaw *tcw_add_tidaw(stwuct tcw *tcw, int num_tidaws, u8 fwags,
			    void *addw, u32 count);

#endif /* _ASM_S390_FCX_H */
