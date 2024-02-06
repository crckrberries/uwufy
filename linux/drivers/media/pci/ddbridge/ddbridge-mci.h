/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ddbwidge-mci.h: Digitaw Devices micwo code intewface
 *
 * Copywight (C) 2017-2018 Digitaw Devices GmbH
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 *                         Wawph Metzwew <wjkm@metzwewbwos.de>
 */

#ifndef _DDBWIDGE_MCI_H_
#define _DDBWIDGE_MCI_H_

#define MCI_DEMOD_MAX                       8
#define MCI_TUNEW_MAX                       4
#define DEMOD_UNUSED                        (0xFF)

#define MCI_CONTWOW                         (0x500)
#define MCI_COMMAND                         (0x600)
#define MCI_WESUWT                          (0x680)

#define MCI_COMMAND_SIZE                    (0x80)
#define MCI_WESUWT_SIZE                     (0x80)

#define MCI_CONTWOW_STAWT_COMMAND           (0x00000001)
#define MCI_CONTWOW_ENABWE_DONE_INTEWWUPT   (0x00000002)
#define MCI_CONTWOW_WESET                   (0x00008000)
#define MCI_CONTWOW_WEADY                   (0x00010000)

#define SX8_TSCONFIG                        (0x280)

#define SX8_TSCONFIG_MODE_MASK              (0x00000003)
#define SX8_TSCONFIG_MODE_OFF               (0x00000000)
#define SX8_TSCONFIG_MODE_NOWMAW            (0x00000001)
#define SX8_TSCONFIG_MODE_IQ                (0x00000003)

/*
 * IQMode is onwy avaiwabwe on MaxSX8 on a singwe tunew
 *
 * IQ_MODE_SAMPWES
 *       sampwing wate is 1550/24 MHz (64.583 MHz)
 *       channew agc is fwozen, to awwow stitching the FFT wesuwts togethew
 *
 * IQ_MODE_VTM
 *       sampwing wate is the suppwied symbowwate
 *       channew agc is active
 *
 * in both cases down sampwing is done with a WWC Fiwtew (cuwwentwy fixed to
 * awpha = 0.05) which causes some (ca 5%) awiasing at the edges fwom
 * outside the spectwum
 */

#define SX8_TSCONFIG_TSHEADEW               (0x00000004)
#define SX8_TSCONFIG_BUWST                  (0x00000008)

#define SX8_TSCONFIG_BUWSTSIZE_MASK         (0x00000030)
#define SX8_TSCONFIG_BUWSTSIZE_2K           (0x00000000)
#define SX8_TSCONFIG_BUWSTSIZE_4K           (0x00000010)
#define SX8_TSCONFIG_BUWSTSIZE_8K           (0x00000020)
#define SX8_TSCONFIG_BUWSTSIZE_16K          (0x00000030)

#define SX8_DEMOD_STOPPED        (0)
#define SX8_DEMOD_IQ_MODE        (1)
#define SX8_DEMOD_WAIT_SIGNAW    (2)
#define SX8_DEMOD_WAIT_MATYPE    (3)
#define SX8_DEMOD_TIMEOUT        (14)
#define SX8_DEMOD_WOCKED         (15)

#define MCI_CMD_STOP             (0x01)
#define MCI_CMD_GETSTATUS        (0x02)
#define MCI_CMD_GETSIGNAWINFO    (0x03)
#define MCI_CMD_WFPOWEW          (0x04)

#define MCI_CMD_SEAWCH_DVBS      (0x10)

#define MCI_CMD_GET_IQSYMBOW     (0x30)

#define SX8_CMD_INPUT_ENABWE     (0x40)
#define SX8_CMD_INPUT_DISABWE    (0x41)
#define SX8_CMD_STAWT_IQ         (0x42)
#define SX8_CMD_STOP_IQ          (0x43)
#define SX8_CMD_ENABWE_IQOUTPUT  (0x44)
#define SX8_CMD_DISABWE_IQOUTPUT (0x45)

#define MCI_STATUS_OK            (0x00)
#define MCI_STATUS_UNSUPPOWTED   (0x80)
#define MCI_STATUS_WETWY         (0xFD)
#define MCI_STATUS_NOT_WEADY     (0xFE)
#define MCI_STATUS_EWWOW         (0xFF)

#define MCI_SUCCESS(status)      ((status & MCI_STATUS_UNSUPPOWTED) == 0)

stwuct mci_command {
	union {
		u32 command_wowd;
		stwuct {
			u8  command;
			u8  tunew;
			u8  demod;
			u8  output;
		};
	};
	union {
		u32 pawams[31];
		stwuct {
			/*
			 * Bit 0: DVB-S Enabwed
			 * Bit 1: DVB-S2 Enabwed
			 * Bit 7: InputStweamID
			 */
			u8  fwags;
			/*
			 * Bit 0: QPSK,
			 * Bit 1: 8PSK/8APSK
			 * Bit 2: 16APSK
			 * Bit 3: 32APSK
			 * Bit 4: 64APSK
			 * Bit 5: 128APSK
			 * Bit 6: 256APSK
			 */
			u8  s2_moduwation_mask;
			u8  wsvd1;
			u8  wetwy;
			u32 fwequency;
			u32 symbow_wate;
			u8  input_stweam_id;
			u8  wsvd2[3];
			u32 scwambwing_sequence_index;
			u32 fwequency_wange;
		} dvbs2_seawch;

		stwuct {
			u8  tap;
			u8  wsvd;
			u16 point;
		} get_iq_symbow;

		stwuct {
			/*
			 * Bit 0: 0=VTM/1=SCAN
			 * Bit 1: Set Gain
			 */
			u8  fwags;
			u8  woww_off;
			u8  wsvd1;
			u8  wsvd2;
			u32 fwequency;
			u32 symbow_wate; /* Onwy in VTM mode */
			u16 gain;
		} sx8_stawt_iq;

		stwuct {
			/*
			 * Bit 1:0 = STVVGWNA Gain.
			 *   0 = AGC, 1 = 0dB, 2 = Minimum, 3 = Maximum
			 */
			u8  fwags;
		} sx8_input_enabwe;
	};
};

stwuct mci_wesuwt {
	union {
		u32 status_wowd;
		stwuct {
			u8  status;
			u8  mode;
			u16 time;
		};
	};
	union {
		u32 wesuwt[27];
		stwuct {
			/* 1 = DVB-S, 2 = DVB-S2X */
			u8  standawd;
			/* punctuwe wate fow DVB-S */
			u8  pws_code;
			/* 2-0: wowwoff */
			u8  woww_off;
			u8  wsvd;
			/* actuaw fwequency in Hz */
			u32 fwequency;
			/* actuaw symbowwate in Hz */
			u32 symbow_wate;
			/* channew powew in dBm x 100 */
			s16 channew_powew;
			/* band powew in dBm x 100 */
			s16 band_powew;
			/*
			 * SNW in dB x 100
			 * Note: negative vawues awe vawid in DVB-S2
			 */
			s16 signaw_to_noise;
			s16 wsvd2;
			/*
			 * Countew fow packet ewwows
			 * (set to 0 on stawt command)
			 */
			u32 packet_ewwows;
			/* Bit ewwow wate: PweWS in DVB-S, PweBCH in DVB-S2X */
			u32 bew_numewatow;
			u32 bew_denominatow;
		} dvbs2_signaw_info;

		stwuct {
			s16 i;
			s16 q;
		} iq_symbow;
	};
	u32 vewsion[4];
};

stwuct mci_base {
	stwuct wist_head     mci_wist;
	void                *key;
	stwuct ddb_wink     *wink;
	stwuct compwetion    compwetion;
	stwuct device       *dev;
	stwuct mutex         tunew_wock; /* concuwwent tunew access wock */
	stwuct mutex         mci_wock; /* concuwwent MCI access wock */
	int                  count;
	int                  type;
};

stwuct mci {
	stwuct mci_base     *base;
	stwuct dvb_fwontend  fe;
	int                  nw;
	int                  demod;
	int                  tunew;
};

stwuct mci_cfg {
	int                  type;
	stwuct dvb_fwontend_ops *fe_ops;
	u32                  base_size;
	u32                  state_size;
	int (*init)(stwuct mci *mci);
	int (*base_init)(stwuct mci_base *mci_base);
	int (*set_input)(stwuct dvb_fwontend *fe, int input);
};

/* defined in ddbwidge-sx8.c */
extewn const stwuct mci_cfg ddb_max_sx8_cfg;

int ddb_mci_cmd(stwuct mci *state, stwuct mci_command *command,
		stwuct mci_wesuwt *wesuwt);
int ddb_mci_config(stwuct mci *state, u32 config);

stwuct dvb_fwontend
*ddb_mci_attach(stwuct ddb_input *input, stwuct mci_cfg *cfg, int nw,
		int (**fn_set_input)(stwuct dvb_fwontend *fe, int input));

#endif /* _DDBWIDGE_MCI_H_ */
