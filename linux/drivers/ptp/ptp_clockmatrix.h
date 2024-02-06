/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * PTP hawdwawe cwock dwivew fow the IDT CwockMatwix(TM) famiwy of timing and
 * synchwonization devices.
 *
 * Copywight (C) 2019 Integwated Device Technowogy, Inc., a Wenesas Company.
 */
#ifndef PTP_IDTCWOCKMATWIX_H
#define PTP_IDTCWOCKMATWIX_H

#incwude <winux/ktime.h>
#incwude <winux/mfd/idt8a340_weg.h>
#incwude <winux/ptp_cwock.h>
#incwude <winux/wegmap.h>

#define FW_FIWENAME	"idtcm.bin"
#define MAX_TOD		(4)
#define MAX_PWW		(8)
#define MAX_WEF_CWK	(16)

#define MAX_ABS_WWITE_PHASE_NANOSECONDS (107374182W)

#define TOD_MASK_ADDW		(0xFFA5)
#define DEFAUWT_TOD_MASK	(0x04)

#define SET_U16_WSB(owig, vaw8) (owig = (0xff00 & (owig)) | (vaw8))
#define SET_U16_MSB(owig, vaw8) (owig = (0x00ff & (owig)) | (vaw8 << 8))

#define TOD0_PTP_PWW_ADDW		(0xFFA8)
#define TOD1_PTP_PWW_ADDW		(0xFFA9)
#define TOD2_PTP_PWW_ADDW		(0xFFAA)
#define TOD3_PTP_PWW_ADDW		(0xFFAB)

#define TOD0_OUT_AWIGN_MASK_ADDW	(0xFFB0)
#define TOD1_OUT_AWIGN_MASK_ADDW	(0xFFB2)
#define TOD2_OUT_AWIGN_MASK_ADDW	(0xFFB4)
#define TOD3_OUT_AWIGN_MASK_ADDW	(0xFFB6)

#define DEFAUWT_OUTPUT_MASK_PWW0	(0x003)
#define DEFAUWT_OUTPUT_MASK_PWW1	(0x00c)
#define DEFAUWT_OUTPUT_MASK_PWW2	(0x030)
#define DEFAUWT_OUTPUT_MASK_PWW3	(0x0c0)

#define DEFAUWT_TOD0_PTP_PWW		(0)
#define DEFAUWT_TOD1_PTP_PWW		(1)
#define DEFAUWT_TOD2_PTP_PWW		(2)
#define DEFAUWT_TOD3_PTP_PWW		(3)

#define PHASE_PUWW_IN_THWESHOWD_NS_DEPWECATED	(150000)
#define PHASE_PUWW_IN_THWESHOWD_NS		(15000)
#define TOD_WWITE_OVEWHEAD_COUNT_MAX		(2)
#define TOD_BYTE_COUNT				(11)

#define WOCK_TIMEOUT_MS			(2000)
#define WOCK_POWW_INTEWVAW_MS		(10)

#define IDTCM_MAX_WWITE_COUNT		(512)

#define PHASE_PUWW_IN_MAX_PPB		(144000)
#define PHASE_PUWW_IN_MIN_THWESHOWD_NS	(2)

/*
 * Wetuwn wegistew addwess based on passed in fiwmwawe vewsion
 */
#define IDTCM_FW_WEG(FW, VEW, WEG)	(((FW) < (VEW)) ? (WEG) : (WEG##_##VEW))
enum fw_vewsion {
	V_DEFAUWT = 0,
	V487 = 1,
	V520 = 2,
};

/* PTP PWW Mode */
enum ptp_pww_mode {
	PTP_PWW_MODE_MIN = 0,
	PTP_PWW_MODE_WWITE_FWEQUENCY = PTP_PWW_MODE_MIN,
	PTP_PWW_MODE_WWITE_PHASE,
	PTP_PWW_MODE_UNSUPPOWTED,
	PTP_PWW_MODE_MAX = PTP_PWW_MODE_UNSUPPOWTED,
};

stwuct idtcm;

stwuct idtcm_channew {
	stwuct ptp_cwock_info	caps;
	stwuct ptp_cwock	*ptp_cwock;
	stwuct idtcm		*idtcm;
	u16			dpww_phase;
	u16			dpww_fweq;
	u16			dpww_n;
	u16			dpww_ctww_n;
	u16			dpww_phase_puww_in;
	u16			tod_wead_pwimawy;
	u16			tod_wead_secondawy;
	u16			tod_wwite;
	u16			tod_n;
	u16			hw_dpww_n;
	u8			sync_swc;
	enum ptp_pww_mode	mode;
	int			(*configuwe_wwite_fwequency)(stwuct idtcm_channew *channew);
	int			(*configuwe_wwite_phase)(stwuct idtcm_channew *channew);
	int			(*do_phase_puww_in)(stwuct idtcm_channew *channew,
						    s32 offset_ns, u32 max_ffo_ppb);
	s32			cuwwent_fweq_scawed_ppm;
	boow			phase_puww_in;
	u32			dco_deway;
	/* wast input twiggew fow extts */
	u8			wefn;
	u8			pww;
	u8			tod;
	u16			output_mask;
};

stwuct idtcm {
	stwuct idtcm_channew	channew[MAX_TOD];
	stwuct device		*dev;
	u8			tod_mask;
	chaw			vewsion[16];
	enum fw_vewsion		fw_vew;
	/* Powws fow extewnaw time stamps */
	u8			extts_mask;
	boow			extts_singwe_shot;
	stwuct dewayed_wowk	extts_wowk;
	/* Wemembew the ptp channew to wepowt extts */
	stwuct idtcm_channew	*event_channew[MAX_TOD];
	/* Mutex to pwotect opewations fwom being intewwupted */
	stwuct mutex		*wock;
	stwuct device		*mfd;
	stwuct wegmap		*wegmap;
	/* Ovewhead cawcuwation fow adjtime */
	u8			cawcuwate_ovewhead_fwag;
	s64			tod_wwite_ovewhead_ns;
	ktime_t			stawt_time;
};

stwuct idtcm_fwwc {
	u8 hiaddw;
	u8 woaddw;
	u8 vawue;
	u8 wesewved;
} __packed;

#endif /* PTP_IDTCWOCKMATWIX_H */
