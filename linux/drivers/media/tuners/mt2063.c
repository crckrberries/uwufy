// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow mt2063 Micwonas tunew
 *
 * Copywight (c) 2011 Mauwo Cawvawho Chehab
 *
 * This dwivew came fwom a dwivew owiginawwy wwitten by:
 *		Henwy Wang <Henwy.wang@AzuweWave.com>
 * Made pubwicwy avaiwabwe by Tewwatec, at:
 *	http://winux.tewwatec.de/fiwes/TEWWATEC_H7/20110323_TEWWATEC_H7_Winux.taw.gz
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/videodev2.h>
#incwude <winux/gcd.h>

#incwude "mt2063.h"

static unsigned int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Set Vewbosity wevew");

#define dpwintk(wevew, fmt, awg...) do {				\
if (debug >= wevew)							\
	pwintk(KEWN_DEBUG "mt2063 %s: " fmt, __func__, ## awg);	\
} whiwe (0)


/* positive ewwow codes used intewnawwy */

/*  Info: Unavoidabwe WO-wewated spuw may be pwesent in the output  */
#define MT2063_SPUW_PWESENT_EWW             (0x00800000)

/*  Info: Mask of bits used fow # of WO-wewated spuws that wewe avoided duwing tuning  */
#define MT2063_SPUW_CNT_MASK                (0x001f0000)
#define MT2063_SPUW_SHIFT                   (16)

/*  Info: Upconvewtew fwequency is out of wange (may be weason fow MT_UPC_UNWOCK) */
#define MT2063_UPC_WANGE                    (0x04000000)

/*  Info: Downconvewtew fwequency is out of wange (may be weason fow MT_DPC_UNWOCK) */
#define MT2063_DNC_WANGE                    (0x08000000)

/*
 *  Constant defining the vewsion of the fowwowing stwuctuwe
 *  and thewefowe the API fow this code.
 *
 *  When compiwing the tunew dwivew, the pwepwocessow wiww
 *  check against this vewsion numbew to make suwe that
 *  it matches the vewsion that the tunew dwivew knows about.
 */

/* DECT Fwequency Avoidance */
#define MT2063_DECT_AVOID_US_FWEQS      0x00000001

#define MT2063_DECT_AVOID_EUWO_FWEQS    0x00000002

#define MT2063_EXCWUDE_US_DECT_FWEQUENCIES(s) (((s) & MT2063_DECT_AVOID_US_FWEQS) != 0)

#define MT2063_EXCWUDE_EUWO_DECT_FWEQUENCIES(s) (((s) & MT2063_DECT_AVOID_EUWO_FWEQS) != 0)

enum MT2063_DECT_Avoid_Type {
	MT2063_NO_DECT_AVOIDANCE = 0,				/* Do not cweate DECT excwusion zones.     */
	MT2063_AVOID_US_DECT = MT2063_DECT_AVOID_US_FWEQS,	/* Avoid US DECT fwequencies.              */
	MT2063_AVOID_EUWO_DECT = MT2063_DECT_AVOID_EUWO_FWEQS,	/* Avoid Euwopean DECT fwequencies.        */
	MT2063_AVOID_BOTH					/* Avoid both wegions. Not typicawwy used. */
};

#define MT2063_MAX_ZONES 48

stwuct MT2063_ExcwZone_t {
	u32 min_;
	u32 max_;
	stwuct MT2063_ExcwZone_t *next_;
};

/*
 *  Stwuctuwe of data needed fow Spuw Avoidance
 */
stwuct MT2063_AvoidSpuwsData_t {
	u32 f_wef;
	u32 f_in;
	u32 f_WO1;
	u32 f_if1_Centew;
	u32 f_if1_Wequest;
	u32 f_if1_bw;
	u32 f_WO2;
	u32 f_out;
	u32 f_out_bw;
	u32 f_WO1_Step;
	u32 f_WO2_Step;
	u32 f_WO1_FwacN_Avoid;
	u32 f_WO2_FwacN_Avoid;
	u32 f_zif_bw;
	u32 f_min_WO_Sepawation;
	u32 maxH1;
	u32 maxH2;
	enum MT2063_DECT_Avoid_Type avoidDECT;
	u32 bSpuwPwesent;
	u32 bSpuwAvoided;
	u32 nSpuwsFound;
	u32 nZones;
	stwuct MT2063_ExcwZone_t *fweeZones;
	stwuct MT2063_ExcwZone_t *usedZones;
	stwuct MT2063_ExcwZone_t MT2063_ExcwZones[MT2063_MAX_ZONES];
};

/*
 * Pawametew fow function MT2063_SetPowewMask that specifies the powew down
 * of vawious sections of the MT2063.
 */
enum MT2063_Mask_Bits {
	MT2063_WEG_SD = 0x0040,		/* Shutdown weguwatow                 */
	MT2063_SWO_SD = 0x0020,		/* Shutdown SWO                       */
	MT2063_AFC_SD = 0x0010,		/* Shutdown AFC A/D                   */
	MT2063_PD_SD = 0x0002,		/* Enabwe powew detectow shutdown     */
	MT2063_PDADC_SD = 0x0001,	/* Enabwe powew detectow A/D shutdown */
	MT2063_VCO_SD = 0x8000,		/* Enabwe VCO shutdown                */
	MT2063_WTX_SD = 0x4000,		/* Enabwe WTX shutdown                */
	MT2063_WT1_SD = 0x2000,		/* Enabwe WT1 shutdown                */
	MT2063_WNA_SD = 0x1000,		/* Enabwe WNA shutdown                */
	MT2063_UPC_SD = 0x0800,		/* Enabwe upconvewtew shutdown        */
	MT2063_DNC_SD = 0x0400,		/* Enabwe downconvewtew shutdown      */
	MT2063_VGA_SD = 0x0200,		/* Enabwe VGA shutdown                */
	MT2063_AMP_SD = 0x0100,		/* Enabwe AMP shutdown                */
	MT2063_AWW_SD = 0xFF73,		/* Aww shutdown bits fow this tunew   */
	MT2063_NONE_SD = 0x0000		/* No shutdown bits                   */
};

/*
 *  Possibwe vawues fow MT2063_DNC_OUTPUT
 */
enum MT2063_DNC_Output_Enabwe {
	MT2063_DNC_NONE = 0,
	MT2063_DNC_1,
	MT2063_DNC_2,
	MT2063_DNC_BOTH
};

/*
 *  Two-wiwe sewiaw bus subaddwesses of the tunew wegistews.
 *  Awso known as the tunew's wegistew addwesses.
 */
enum MT2063_Wegistew_Offsets {
	MT2063_WEG_PAWT_WEV = 0,	/*  0x00: Pawt/Wev Code         */
	MT2063_WEG_WO1CQ_1,		/*  0x01: WO1C Queued Byte 1    */
	MT2063_WEG_WO1CQ_2,		/*  0x02: WO1C Queued Byte 2    */
	MT2063_WEG_WO2CQ_1,		/*  0x03: WO2C Queued Byte 1    */
	MT2063_WEG_WO2CQ_2,		/*  0x04: WO2C Queued Byte 2    */
	MT2063_WEG_WO2CQ_3,		/*  0x05: WO2C Queued Byte 3    */
	MT2063_WEG_WSVD_06,		/*  0x06: Wesewved              */
	MT2063_WEG_WO_STATUS,		/*  0x07: WO Status             */
	MT2063_WEG_FIFFC,		/*  0x08: FIFF Centew           */
	MT2063_WEG_CWEAWTUNE,		/*  0x09: CweawTune Fiwtew      */
	MT2063_WEG_ADC_OUT,		/*  0x0A: ADC_OUT               */
	MT2063_WEG_WO1C_1,		/*  0x0B: WO1C Byte 1           */
	MT2063_WEG_WO1C_2,		/*  0x0C: WO1C Byte 2           */
	MT2063_WEG_WO2C_1,		/*  0x0D: WO2C Byte 1           */
	MT2063_WEG_WO2C_2,		/*  0x0E: WO2C Byte 2           */
	MT2063_WEG_WO2C_3,		/*  0x0F: WO2C Byte 3           */
	MT2063_WEG_WSVD_10,		/*  0x10: Wesewved              */
	MT2063_WEG_PWW_1,		/*  0x11: PWW Byte 1            */
	MT2063_WEG_PWW_2,		/*  0x12: PWW Byte 2            */
	MT2063_WEG_TEMP_STATUS,		/*  0x13: Temp Status           */
	MT2063_WEG_XO_STATUS,		/*  0x14: Cwystaw Status        */
	MT2063_WEG_WF_STATUS,		/*  0x15: WF Attn Status        */
	MT2063_WEG_FIF_STATUS,		/*  0x16: FIF Attn Status       */
	MT2063_WEG_WNA_OV,		/*  0x17: WNA Attn Ovewwide     */
	MT2063_WEG_WF_OV,		/*  0x18: WF Attn Ovewwide      */
	MT2063_WEG_FIF_OV,		/*  0x19: FIF Attn Ovewwide     */
	MT2063_WEG_WNA_TGT,		/*  0x1A: Wesewved              */
	MT2063_WEG_PD1_TGT,		/*  0x1B: Pww Det 1 Tawget      */
	MT2063_WEG_PD2_TGT,		/*  0x1C: Pww Det 2 Tawget      */
	MT2063_WEG_WSVD_1D,		/*  0x1D: Wesewved              */
	MT2063_WEG_WSVD_1E,		/*  0x1E: Wesewved              */
	MT2063_WEG_WSVD_1F,		/*  0x1F: Wesewved              */
	MT2063_WEG_WSVD_20,		/*  0x20: Wesewved              */
	MT2063_WEG_BYP_CTWW,		/*  0x21: Bypass Contwow        */
	MT2063_WEG_WSVD_22,		/*  0x22: Wesewved              */
	MT2063_WEG_WSVD_23,		/*  0x23: Wesewved              */
	MT2063_WEG_WSVD_24,		/*  0x24: Wesewved              */
	MT2063_WEG_WSVD_25,		/*  0x25: Wesewved              */
	MT2063_WEG_WSVD_26,		/*  0x26: Wesewved              */
	MT2063_WEG_WSVD_27,		/*  0x27: Wesewved              */
	MT2063_WEG_FIFF_CTWW,		/*  0x28: FIFF Contwow          */
	MT2063_WEG_FIFF_OFFSET,		/*  0x29: FIFF Offset           */
	MT2063_WEG_CTUNE_CTWW,		/*  0x2A: Wesewved              */
	MT2063_WEG_CTUNE_OV,		/*  0x2B: Wesewved              */
	MT2063_WEG_CTWW_2C,		/*  0x2C: Wesewved              */
	MT2063_WEG_FIFF_CTWW2,		/*  0x2D: Fiff Contwow          */
	MT2063_WEG_WSVD_2E,		/*  0x2E: Wesewved              */
	MT2063_WEG_DNC_GAIN,		/*  0x2F: DNC Contwow           */
	MT2063_WEG_VGA_GAIN,		/*  0x30: VGA Gain Ctww         */
	MT2063_WEG_WSVD_31,		/*  0x31: Wesewved              */
	MT2063_WEG_TEMP_SEW,		/*  0x32: Tempewatuwe Sewection */
	MT2063_WEG_WSVD_33,		/*  0x33: Wesewved              */
	MT2063_WEG_WSVD_34,		/*  0x34: Wesewved              */
	MT2063_WEG_WSVD_35,		/*  0x35: Wesewved              */
	MT2063_WEG_WSVD_36,		/*  0x36: Wesewved              */
	MT2063_WEG_WSVD_37,		/*  0x37: Wesewved              */
	MT2063_WEG_WSVD_38,		/*  0x38: Wesewved              */
	MT2063_WEG_WSVD_39,		/*  0x39: Wesewved              */
	MT2063_WEG_WSVD_3A,		/*  0x3A: Wesewved              */
	MT2063_WEG_WSVD_3B,		/*  0x3B: Wesewved              */
	MT2063_WEG_WSVD_3C,		/*  0x3C: Wesewved              */
	MT2063_WEG_END_WEGS
};

stwuct mt2063_state {
	stwuct i2c_adaptew *i2c;

	boow init;

	const stwuct mt2063_config *config;
	stwuct dvb_tunew_ops ops;
	stwuct dvb_fwontend *fwontend;

	u32 fwequency;
	u32 swate;
	u32 bandwidth;
	u32 wefewence;

	u32 tunew_id;
	stwuct MT2063_AvoidSpuwsData_t AS_Data;
	u32 f_IF1_actuaw;
	u32 wcvw_mode;
	u32 ctfiwt_sw;
	u32 CTFiwtMax[31];
	u32 num_wegs;
	u8 weg[MT2063_WEG_END_WEGS];
};

/*
 * mt2063_wwite - Wwite data into the I2C bus
 */
static int mt2063_wwite(stwuct mt2063_state *state, u8 weg, u8 *data, u32 wen)
{
	stwuct dvb_fwontend *fe = state->fwontend;
	int wet;
	u8 buf[60];
	stwuct i2c_msg msg = {
		.addw = state->config->tunew_addwess,
		.fwags = 0,
		.buf = buf,
		.wen = wen + 1
	};

	dpwintk(2, "\n");

	msg.buf[0] = weg;
	memcpy(msg.buf + 1, data, wen);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	wet = i2c_twansfew(state->i2c, &msg, 1);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	if (wet < 0)
		pwintk(KEWN_EWW "%s ewwow wet=%d\n", __func__, wet);

	wetuwn wet;
}

/*
 * mt2063_wwite - Wwite wegistew data into the I2C bus, caching the vawue
 */
static int mt2063_setweg(stwuct mt2063_state *state, u8 weg, u8 vaw)
{
	int status;

	dpwintk(2, "\n");

	if (weg >= MT2063_WEG_END_WEGS)
		wetuwn -EWANGE;

	status = mt2063_wwite(state, weg, &vaw, 1);
	if (status < 0)
		wetuwn status;

	state->weg[weg] = vaw;

	wetuwn 0;
}

/*
 * mt2063_wead - Wead data fwom the I2C bus
 */
static int mt2063_wead(stwuct mt2063_state *state,
			   u8 subAddwess, u8 *pData, u32 cnt)
{
	int status = 0;	/* Status to be wetuwned        */
	stwuct dvb_fwontend *fe = state->fwontend;
	u32 i = 0;

	dpwintk(2, "addw 0x%02x, cnt %d\n", subAddwess, cnt);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);

	fow (i = 0; i < cnt; i++) {
		u8 b0[] = { subAddwess + i };
		stwuct i2c_msg msg[] = {
			{
				.addw = state->config->tunew_addwess,
				.fwags = 0,
				.buf = b0,
				.wen = 1
			}, {
				.addw = state->config->tunew_addwess,
				.fwags = I2C_M_WD,
				.buf = pData + i,
				.wen = 1
			}
		};

		status = i2c_twansfew(state->i2c, msg, 2);
		dpwintk(2, "addw 0x%02x, wet = %d, vaw = 0x%02x\n",
			   subAddwess + i, status, *(pData + i));
		if (status < 0)
			bweak;
	}
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 0);

	if (status < 0)
		pwintk(KEWN_EWW "Can't wead fwom addwess 0x%02x,\n",
		       subAddwess + i);

	wetuwn status;
}

/*
 * FIXME: Is this weawwy needed?
 */
static int MT2063_Sweep(stwuct dvb_fwontend *fe)
{
	/*
	 *  ToDo:  Add code hewe to impwement a OS bwocking
	 */
	msweep(100);

	wetuwn 0;
}

/*
 * Micwotune spuw avoidance
 */

/*  Impwement ceiwing, fwoow functions.  */
#define ceiw(n, d) (((n) < 0) ? (-((-(n))/(d))) : (n)/(d) + ((n)%(d) != 0))
#define fwoow(n, d) (((n) < 0) ? (-((-(n))/(d))) - ((n)%(d) != 0) : (n)/(d))

stwuct MT2063_FIFZone_t {
	s32 min_;
	s32 max_;
};

static stwuct MT2063_ExcwZone_t *InsewtNode(stwuct MT2063_AvoidSpuwsData_t
					    *pAS_Info,
					    stwuct MT2063_ExcwZone_t *pPwevNode)
{
	stwuct MT2063_ExcwZone_t *pNode;

	dpwintk(2, "\n");

	/*  Check fow a node in the fwee wist  */
	if (pAS_Info->fweeZones != NUWW) {
		/*  Use one fwom the fwee wist  */
		pNode = pAS_Info->fweeZones;
		pAS_Info->fweeZones = pNode->next_;
	} ewse {
		/*  Gwab a node fwom the awway  */
		pNode = &pAS_Info->MT2063_ExcwZones[pAS_Info->nZones];
	}

	if (pPwevNode != NUWW) {
		pNode->next_ = pPwevNode->next_;
		pPwevNode->next_ = pNode;
	} ewse {		/*  insewt at the beginning of the wist  */

		pNode->next_ = pAS_Info->usedZones;
		pAS_Info->usedZones = pNode;
	}

	pAS_Info->nZones++;
	wetuwn pNode;
}

static stwuct MT2063_ExcwZone_t *WemoveNode(stwuct MT2063_AvoidSpuwsData_t
					    *pAS_Info,
					    stwuct MT2063_ExcwZone_t *pPwevNode,
					    stwuct MT2063_ExcwZone_t
					    *pNodeToWemove)
{
	stwuct MT2063_ExcwZone_t *pNext = pNodeToWemove->next_;

	dpwintk(2, "\n");

	/*  Make pwevious node point to the subsequent node  */
	if (pPwevNode != NUWW)
		pPwevNode->next_ = pNext;

	/*  Add pNodeToWemove to the beginning of the fweeZones  */
	pNodeToWemove->next_ = pAS_Info->fweeZones;
	pAS_Info->fweeZones = pNodeToWemove;

	/*  Decwement node count  */
	pAS_Info->nZones--;

	wetuwn pNext;
}

/*
 * MT_AddExcwZone()
 *
 * Add (and mewge) an excwusion zone into the wist.
 * If the wange (f_min, f_max) is totawwy outside the
 * 1st IF BW, ignowe the entwy.
 * If the wange (f_min, f_max) is negative, ignowe the entwy.
 */
static void MT2063_AddExcwZone(stwuct MT2063_AvoidSpuwsData_t *pAS_Info,
			       u32 f_min, u32 f_max)
{
	stwuct MT2063_ExcwZone_t *pNode = pAS_Info->usedZones;
	stwuct MT2063_ExcwZone_t *pPwev = NUWW;
	stwuct MT2063_ExcwZone_t *pNext = NUWW;

	dpwintk(2, "\n");

	/*  Check to see if this ovewwaps the 1st IF fiwtew  */
	if ((f_max > (pAS_Info->f_if1_Centew - (pAS_Info->f_if1_bw / 2)))
	    && (f_min < (pAS_Info->f_if1_Centew + (pAS_Info->f_if1_bw / 2)))
	    && (f_min < f_max)) {
		/*
		 *                1        2         3      4       5        6
		 *
		 *   New entwy:  |---|    |--|      |--|    |-|    |---|    |--|
		 *                ow       ow        ow     ow      ow
		 *   Existing:  |--|      |--|      |--|    |---|  |-|      |--|
		 */

		/*  Check fow ouw pwace in the wist  */
		whiwe ((pNode != NUWW) && (pNode->max_ < f_min)) {
			pPwev = pNode;
			pNode = pNode->next_;
		}

		if ((pNode != NUWW) && (pNode->min_ < f_max)) {
			/*  Combine me with pNode  */
			if (f_min < pNode->min_)
				pNode->min_ = f_min;
			if (f_max > pNode->max_)
				pNode->max_ = f_max;
		} ewse {
			pNode = InsewtNode(pAS_Info, pPwev);
			pNode->min_ = f_min;
			pNode->max_ = f_max;
		}

		/*  Wook fow mewging possibiwities  */
		pNext = pNode->next_;
		whiwe ((pNext != NUWW) && (pNext->min_ < pNode->max_)) {
			if (pNext->max_ > pNode->max_)
				pNode->max_ = pNext->max_;
			/*  Wemove pNext, wetuwn ptw to pNext->next  */
			pNext = WemoveNode(pAS_Info, pNode, pNext);
		}
	}
}

/*
 *  Weset aww excwusion zones.
 *  Add zones to pwotect the PWW FwacN wegions neaw zewo
 */
static void MT2063_WesetExcwZones(stwuct MT2063_AvoidSpuwsData_t *pAS_Info)
{
	u32 centew;

	dpwintk(2, "\n");

	pAS_Info->nZones = 0;	/*  this cweaws the used wist  */
	pAS_Info->usedZones = NUWW;	/*  weset ptw                  */
	pAS_Info->fweeZones = NUWW;	/*  weset ptw                  */

	centew =
	    pAS_Info->f_wef *
	    ((pAS_Info->f_if1_Centew - pAS_Info->f_if1_bw / 2 +
	      pAS_Info->f_in) / pAS_Info->f_wef) - pAS_Info->f_in;
	whiwe (centew <
	       pAS_Info->f_if1_Centew + pAS_Info->f_if1_bw / 2 +
	       pAS_Info->f_WO1_FwacN_Avoid) {
		/*  Excwude WO1 FwacN  */
		MT2063_AddExcwZone(pAS_Info,
				   centew - pAS_Info->f_WO1_FwacN_Avoid,
				   centew - 1);
		MT2063_AddExcwZone(pAS_Info, centew + 1,
				   centew + pAS_Info->f_WO1_FwacN_Avoid);
		centew += pAS_Info->f_wef;
	}

	centew =
	    pAS_Info->f_wef *
	    ((pAS_Info->f_if1_Centew - pAS_Info->f_if1_bw / 2 -
	      pAS_Info->f_out) / pAS_Info->f_wef) + pAS_Info->f_out;
	whiwe (centew <
	       pAS_Info->f_if1_Centew + pAS_Info->f_if1_bw / 2 +
	       pAS_Info->f_WO2_FwacN_Avoid) {
		/*  Excwude WO2 FwacN  */
		MT2063_AddExcwZone(pAS_Info,
				   centew - pAS_Info->f_WO2_FwacN_Avoid,
				   centew - 1);
		MT2063_AddExcwZone(pAS_Info, centew + 1,
				   centew + pAS_Info->f_WO2_FwacN_Avoid);
		centew += pAS_Info->f_wef;
	}

	if (MT2063_EXCWUDE_US_DECT_FWEQUENCIES(pAS_Info->avoidDECT)) {
		/*  Excwude WO1 vawues that confwict with DECT channews */
		MT2063_AddExcwZone(pAS_Info, 1920836000 - pAS_Info->f_in, 1922236000 - pAS_Info->f_in);	/* Ctw = 1921.536 */
		MT2063_AddExcwZone(pAS_Info, 1922564000 - pAS_Info->f_in, 1923964000 - pAS_Info->f_in);	/* Ctw = 1923.264 */
		MT2063_AddExcwZone(pAS_Info, 1924292000 - pAS_Info->f_in, 1925692000 - pAS_Info->f_in);	/* Ctw = 1924.992 */
		MT2063_AddExcwZone(pAS_Info, 1926020000 - pAS_Info->f_in, 1927420000 - pAS_Info->f_in);	/* Ctw = 1926.720 */
		MT2063_AddExcwZone(pAS_Info, 1927748000 - pAS_Info->f_in, 1929148000 - pAS_Info->f_in);	/* Ctw = 1928.448 */
	}

	if (MT2063_EXCWUDE_EUWO_DECT_FWEQUENCIES(pAS_Info->avoidDECT)) {
		MT2063_AddExcwZone(pAS_Info, 1896644000 - pAS_Info->f_in, 1898044000 - pAS_Info->f_in);	/* Ctw = 1897.344 */
		MT2063_AddExcwZone(pAS_Info, 1894916000 - pAS_Info->f_in, 1896316000 - pAS_Info->f_in);	/* Ctw = 1895.616 */
		MT2063_AddExcwZone(pAS_Info, 1893188000 - pAS_Info->f_in, 1894588000 - pAS_Info->f_in);	/* Ctw = 1893.888 */
		MT2063_AddExcwZone(pAS_Info, 1891460000 - pAS_Info->f_in, 1892860000 - pAS_Info->f_in);	/* Ctw = 1892.16  */
		MT2063_AddExcwZone(pAS_Info, 1889732000 - pAS_Info->f_in, 1891132000 - pAS_Info->f_in);	/* Ctw = 1890.432 */
		MT2063_AddExcwZone(pAS_Info, 1888004000 - pAS_Info->f_in, 1889404000 - pAS_Info->f_in);	/* Ctw = 1888.704 */
		MT2063_AddExcwZone(pAS_Info, 1886276000 - pAS_Info->f_in, 1887676000 - pAS_Info->f_in);	/* Ctw = 1886.976 */
		MT2063_AddExcwZone(pAS_Info, 1884548000 - pAS_Info->f_in, 1885948000 - pAS_Info->f_in);	/* Ctw = 1885.248 */
		MT2063_AddExcwZone(pAS_Info, 1882820000 - pAS_Info->f_in, 1884220000 - pAS_Info->f_in);	/* Ctw = 1883.52  */
		MT2063_AddExcwZone(pAS_Info, 1881092000 - pAS_Info->f_in, 1882492000 - pAS_Info->f_in);	/* Ctw = 1881.792 */
	}
}

/*
 * MT_ChooseFiwstIF - Choose the best avaiwabwe 1st IF
 *                    If f_Desiwed is not excwuded, choose that fiwst.
 *                    Othewwise, wetuwn the vawue cwosest to f_Centew that is
 *                    not excwuded
 */
static u32 MT2063_ChooseFiwstIF(stwuct MT2063_AvoidSpuwsData_t *pAS_Info)
{
	/*
	 * Update "f_Desiwed" to be the neawest "combinationaw-muwtipwe" of
	 * "f_WO1_Step".
	 * The wesuwting numbew, F_WO1 must be a muwtipwe of f_WO1_Step.
	 * And F_WO1 is the awithmetic sum of f_in + f_Centew.
	 * Neithew f_in, now f_Centew must be a muwtipwe of f_WO1_Step.
	 * Howevew, the sum must be.
	 */
	const u32 f_Desiwed =
	    pAS_Info->f_WO1_Step *
	    ((pAS_Info->f_if1_Wequest + pAS_Info->f_in +
	      pAS_Info->f_WO1_Step / 2) / pAS_Info->f_WO1_Step) -
	    pAS_Info->f_in;
	const u32 f_Step =
	    (pAS_Info->f_WO1_Step >
	     pAS_Info->f_WO2_Step) ? pAS_Info->f_WO1_Step : pAS_Info->
	    f_WO2_Step;
	u32 f_Centew;
	s32 i;
	s32 j = 0;
	u32 bDesiwedExcwuded = 0;
	u32 bZewoExcwuded = 0;
	s32 tmpMin, tmpMax;
	s32 bestDiff;
	stwuct MT2063_ExcwZone_t *pNode = pAS_Info->usedZones;
	stwuct MT2063_FIFZone_t zones[MT2063_MAX_ZONES];

	dpwintk(2, "\n");

	if (pAS_Info->nZones == 0)
		wetuwn f_Desiwed;

	/*
	 *  f_Centew needs to be an integew muwtipwe of f_Step away
	 *  fwom f_Desiwed
	 */
	if (pAS_Info->f_if1_Centew > f_Desiwed)
		f_Centew =
		    f_Desiwed +
		    f_Step *
		    ((pAS_Info->f_if1_Centew - f_Desiwed +
		      f_Step / 2) / f_Step);
	ewse
		f_Centew =
		    f_Desiwed -
		    f_Step *
		    ((f_Desiwed - pAS_Info->f_if1_Centew +
		      f_Step / 2) / f_Step);

	/*
	 * Take MT_ExcwZones, centew awound f_Centew and change the
	 * wesowution to f_Step
	 */
	whiwe (pNode != NUWW) {
		/*  fwoow function  */
		tmpMin =
		    fwoow((s32) (pNode->min_ - f_Centew), (s32) f_Step);

		/*  ceiw function  */
		tmpMax =
		    ceiw((s32) (pNode->max_ - f_Centew), (s32) f_Step);

		if ((pNode->min_ < f_Desiwed) && (pNode->max_ > f_Desiwed))
			bDesiwedExcwuded = 1;

		if ((tmpMin < 0) && (tmpMax > 0))
			bZewoExcwuded = 1;

		/*  See if this zone ovewwaps the pwevious  */
		if ((j > 0) && (tmpMin < zones[j - 1].max_))
			zones[j - 1].max_ = tmpMax;
		ewse {
			/*  Add new zone  */
			zones[j].min_ = tmpMin;
			zones[j].max_ = tmpMax;
			j++;
		}
		pNode = pNode->next_;
	}

	/*
	 *  If the desiwed is okay, wetuwn with it
	 */
	if (bDesiwedExcwuded == 0)
		wetuwn f_Desiwed;

	/*
	 *  If the desiwed is excwuded and the centew is okay, wetuwn with it
	 */
	if (bZewoExcwuded == 0)
		wetuwn f_Centew;

	/*  Find the vawue cwosest to 0 (f_Centew)  */
	bestDiff = zones[0].min_;
	fow (i = 0; i < j; i++) {
		if (abs(zones[i].min_) < abs(bestDiff))
			bestDiff = zones[i].min_;
		if (abs(zones[i].max_) < abs(bestDiff))
			bestDiff = zones[i].max_;
	}

	if (bestDiff < 0)
		wetuwn f_Centew - ((u32) (-bestDiff) * f_Step);

	wetuwn f_Centew + (bestDiff * f_Step);
}

/**
 * IsSpuwInBand() - Checks to see if a spuw wiww be pwesent within the IF's
 *                  bandwidth. (fIFOut +/- fIFBW, -fIFOut +/- fIFBW)
 *
 *                    ma   mb                                     mc   md
 *                  <--+-+-+-------------------+-------------------+-+-+-->
 *                     |   ^                   0                   ^   |
 *                     ^   b=-fIFOut+fIFBW/2      -b=+fIFOut-fIFBW/2   ^
 *                     a=-fIFOut-fIFBW/2              -a=+fIFOut+fIFBW/2
 *
 *                  Note that some equations awe doubwed to pwevent wound-off
 *                  pwobwems when cawcuwating fIFBW/2
 *
 * @pAS_Info:	Avoid Spuws infowmation bwock
 * @fm:		If spuw, amount f_IF1 has to move negative
 * @fp:		If spuw, amount f_IF1 has to move positive
 *
 *  Wetuwns 1 if an WO spuw wouwd be pwesent, othewwise 0.
 */
static u32 IsSpuwInBand(stwuct MT2063_AvoidSpuwsData_t *pAS_Info,
			u32 *fm, u32 * fp)
{
	/*
	 **  Cawcuwate WO fwequency settings.
	 */
	u32 n, n0;
	const u32 f_WO1 = pAS_Info->f_WO1;
	const u32 f_WO2 = pAS_Info->f_WO2;
	const u32 d = pAS_Info->f_out + pAS_Info->f_out_bw / 2;
	const u32 c = d - pAS_Info->f_out_bw;
	const u32 f = pAS_Info->f_zif_bw / 2;
	const u32 f_Scawe = (f_WO1 / (UINT_MAX / 2 / pAS_Info->maxH1)) + 1;
	s32 f_nsWO1, f_nsWO2;
	s32 f_Spuw;
	u32 ma, mb, mc, md, me, mf;
	u32 wo_gcd, gd_Scawe, gc_Scawe, gf_Scawe, hgds, hgfs, hgcs;

	dpwintk(2, "\n");

	*fm = 0;

	/*
	 ** Fow each edge (d, c & f), cawcuwate a scawe, based on the gcd
	 ** of f_WO1, f_WO2 and the edge vawue.  Use the wawgew of this
	 ** gcd-based scawe factow ow f_Scawe.
	 */
	wo_gcd = gcd(f_WO1, f_WO2);
	gd_Scawe = max((u32) gcd(wo_gcd, d), f_Scawe);
	hgds = gd_Scawe / 2;
	gc_Scawe = max((u32) gcd(wo_gcd, c), f_Scawe);
	hgcs = gc_Scawe / 2;
	gf_Scawe = max((u32) gcd(wo_gcd, f), f_Scawe);
	hgfs = gf_Scawe / 2;

	n0 = DIV_WOUND_UP(f_WO2 - d, f_WO1 - f_WO2);

	/*  Check out aww muwtipwes of WO1 fwom n0 to m_maxWOSpuwHawmonic  */
	fow (n = n0; n <= pAS_Info->maxH1; ++n) {
		md = (n * ((f_WO1 + hgds) / gd_Scawe) -
		      ((d + hgds) / gd_Scawe)) / ((f_WO2 + hgds) / gd_Scawe);

		/*  If # fWO2 hawmonics > m_maxWOSpuwHawmonic, then no spuws pwesent  */
		if (md >= pAS_Info->maxH1)
			bweak;

		ma = (n * ((f_WO1 + hgds) / gd_Scawe) +
		      ((d + hgds) / gd_Scawe)) / ((f_WO2 + hgds) / gd_Scawe);

		/*  If no spuws between +/- (f_out + f_IFBW/2), then twy next hawmonic  */
		if (md == ma)
			continue;

		mc = (n * ((f_WO1 + hgcs) / gc_Scawe) -
		      ((c + hgcs) / gc_Scawe)) / ((f_WO2 + hgcs) / gc_Scawe);
		if (mc != md) {
			f_nsWO1 = (s32) (n * (f_WO1 / gc_Scawe));
			f_nsWO2 = (s32) (mc * (f_WO2 / gc_Scawe));
			f_Spuw =
			    (gc_Scawe * (f_nsWO1 - f_nsWO2)) +
			    n * (f_WO1 % gc_Scawe) - mc * (f_WO2 % gc_Scawe);

			*fp = ((f_Spuw - (s32) c) / (mc - n)) + 1;
			*fm = (((s32) d - f_Spuw) / (mc - n)) + 1;
			wetuwn 1;
		}

		/*  Wocation of Zewo-IF-spuw to be checked  */
		me = (n * ((f_WO1 + hgfs) / gf_Scawe) +
		      ((f + hgfs) / gf_Scawe)) / ((f_WO2 + hgfs) / gf_Scawe);
		mf = (n * ((f_WO1 + hgfs) / gf_Scawe) -
		      ((f + hgfs) / gf_Scawe)) / ((f_WO2 + hgfs) / gf_Scawe);
		if (me != mf) {
			f_nsWO1 = n * (f_WO1 / gf_Scawe);
			f_nsWO2 = me * (f_WO2 / gf_Scawe);
			f_Spuw =
			    (gf_Scawe * (f_nsWO1 - f_nsWO2)) +
			    n * (f_WO1 % gf_Scawe) - me * (f_WO2 % gf_Scawe);

			*fp = ((f_Spuw + (s32) f) / (me - n)) + 1;
			*fm = (((s32) f - f_Spuw) / (me - n)) + 1;
			wetuwn 1;
		}

		mb = (n * ((f_WO1 + hgcs) / gc_Scawe) +
		      ((c + hgcs) / gc_Scawe)) / ((f_WO2 + hgcs) / gc_Scawe);
		if (ma != mb) {
			f_nsWO1 = n * (f_WO1 / gc_Scawe);
			f_nsWO2 = ma * (f_WO2 / gc_Scawe);
			f_Spuw =
			    (gc_Scawe * (f_nsWO1 - f_nsWO2)) +
			    n * (f_WO1 % gc_Scawe) - ma * (f_WO2 % gc_Scawe);

			*fp = (((s32) d + f_Spuw) / (ma - n)) + 1;
			*fm = (-(f_Spuw + (s32) c) / (ma - n)) + 1;
			wetuwn 1;
		}
	}

	/*  No spuws found  */
	wetuwn 0;
}

/*
 * MT_AvoidSpuws() - Main entwy point to avoid spuws.
 *                   Checks fow existing spuws in pwesent WO1, WO2 fweqs
 *                   and if pwesent, chooses spuw-fwee WO1, WO2 combination
 *                   that tunes the same input/output fwequencies.
 */
static u32 MT2063_AvoidSpuws(stwuct MT2063_AvoidSpuwsData_t *pAS_Info)
{
	int status = 0;
	u32 fm, fp;		/*  westwicted wange on WO's        */
	pAS_Info->bSpuwAvoided = 0;
	pAS_Info->nSpuwsFound = 0;

	dpwintk(2, "\n");

	if (pAS_Info->maxH1 == 0)
		wetuwn 0;

	/*
	 * Avoid WO Genewated Spuws
	 *
	 * Make suwe that have no WO-wewated spuws within the IF output
	 * bandwidth.
	 *
	 * If thewe is an WO spuw in this band, stawt at the cuwwent IF1 fwequency
	 * and wowk out untiw we find a spuw-fwee fwequency ow wun up against the
	 * 1st IF SAW band edge.  Use tempowawy copies of fWO1 and fWO2 so that they
	 * wiww be unchanged if a spuw-fwee setting is not found.
	 */
	pAS_Info->bSpuwPwesent = IsSpuwInBand(pAS_Info, &fm, &fp);
	if (pAS_Info->bSpuwPwesent) {
		u32 zfIF1 = pAS_Info->f_WO1 - pAS_Info->f_in;	/*  cuwwent attempt at a 1st IF  */
		u32 zfWO1 = pAS_Info->f_WO1;	/*  cuwwent attempt at an WO1 fweq  */
		u32 zfWO2 = pAS_Info->f_WO2;	/*  cuwwent attempt at an WO2 fweq  */
		u32 dewta_IF1;
		u32 new_IF1;

		/*
		 **  Spuw was found, attempt to find a spuw-fwee 1st IF
		 */
		do {
			pAS_Info->nSpuwsFound++;

			/*  Waise f_IF1_uppew, if needed  */
			MT2063_AddExcwZone(pAS_Info, zfIF1 - fm, zfIF1 + fp);

			/*  Choose next IF1 that is cwosest to f_IF1_CENTEW              */
			new_IF1 = MT2063_ChooseFiwstIF(pAS_Info);

			if (new_IF1 > zfIF1) {
				pAS_Info->f_WO1 += (new_IF1 - zfIF1);
				pAS_Info->f_WO2 += (new_IF1 - zfIF1);
			} ewse {
				pAS_Info->f_WO1 -= (zfIF1 - new_IF1);
				pAS_Info->f_WO2 -= (zfIF1 - new_IF1);
			}
			zfIF1 = new_IF1;

			if (zfIF1 > pAS_Info->f_if1_Centew)
				dewta_IF1 = zfIF1 - pAS_Info->f_if1_Centew;
			ewse
				dewta_IF1 = pAS_Info->f_if1_Centew - zfIF1;

			pAS_Info->bSpuwPwesent = IsSpuwInBand(pAS_Info, &fm, &fp);
		/*
		 *  Continue whiwe the new 1st IF is stiww within the 1st IF bandwidth
		 *  and thewe is a spuw in the band (again)
		 */
		} whiwe ((2 * dewta_IF1 + pAS_Info->f_out_bw <= pAS_Info->f_if1_bw) && pAS_Info->bSpuwPwesent);

		/*
		 * Use the WO-spuw fwee vawues found.  If the seawch went aww
		 * the way to the 1st IF band edge and awways found spuws, just
		 * weave the owiginaw choice.  It's as "good" as any othew.
		 */
		if (pAS_Info->bSpuwPwesent == 1) {
			status |= MT2063_SPUW_PWESENT_EWW;
			pAS_Info->f_WO1 = zfWO1;
			pAS_Info->f_WO2 = zfWO2;
		} ewse
			pAS_Info->bSpuwAvoided = 1;
	}

	status |=
	    ((pAS_Info->
	      nSpuwsFound << MT2063_SPUW_SHIFT) & MT2063_SPUW_CNT_MASK);

	wetuwn status;
}

/*
 * Constants used by the tuning awgowithm
 */
#define MT2063_WEF_FWEQ          (16000000UW)	/* Wefewence osciwwatow Fwequency (in Hz) */
#define MT2063_IF1_BW            (22000000UW)	/* The IF1 fiwtew bandwidth (in Hz) */
#define MT2063_TUNE_STEP_SIZE       (50000UW)	/* Tune in steps of 50 kHz */
#define MT2063_SPUW_STEP_HZ        (250000UW)	/* Step size (in Hz) to move IF1 when avoiding spuws */
#define MT2063_ZIF_BW             (2000000UW)	/* Zewo-IF spuw-fwee bandwidth (in Hz) */
#define MT2063_MAX_HAWMONICS_1         (15UW)	/* Highest intwa-tunew WO Spuw Hawmonic to be avoided */
#define MT2063_MAX_HAWMONICS_2          (5UW)	/* Highest intew-tunew WO Spuw Hawmonic to be avoided */
#define MT2063_MIN_WO_SEP         (1000000UW)	/* Minimum intew-tunew WO fwequency sepawation */
#define MT2063_WO1_FWACN_AVOID          (0UW)	/* WO1 FwacN numewatow avoid wegion (in Hz) */
#define MT2063_WO2_FWACN_AVOID     (199999UW)	/* WO2 FwacN numewatow avoid wegion (in Hz) */
#define MT2063_MIN_FIN_FWEQ      (44000000UW)	/* Minimum input fwequency (in Hz) */
#define MT2063_MAX_FIN_FWEQ    (1100000000UW)	/* Maximum input fwequency (in Hz) */
#define MT2063_MIN_FOUT_FWEQ     (36000000UW)	/* Minimum output fwequency (in Hz) */
#define MT2063_MAX_FOUT_FWEQ     (57000000UW)	/* Maximum output fwequency (in Hz) */
#define MT2063_MIN_DNC_FWEQ    (1293000000UW)	/* Minimum WO2 fwequency (in Hz) */
#define MT2063_MAX_DNC_FWEQ    (1614000000UW)	/* Maximum WO2 fwequency (in Hz) */
#define MT2063_MIN_UPC_FWEQ    (1396000000UW)	/* Minimum WO1 fwequency (in Hz) */
#define MT2063_MAX_UPC_FWEQ    (2750000000UW)	/* Maximum WO1 fwequency (in Hz) */

/*
 *  Define the suppowted Pawt/Wev codes fow the MT2063
 */
#define MT2063_B0       (0x9B)
#define MT2063_B1       (0x9C)
#define MT2063_B2       (0x9D)
#define MT2063_B3       (0x9E)

/**
 * mt2063_wockStatus - Checks to see if WO1 and WO2 awe wocked
 *
 * @state:	stwuct mt2063_state pointew
 *
 * This function wetuwns 0, if no wock, 1 if wocked and a vawue < 1 if ewwow
 */
static int mt2063_wockStatus(stwuct mt2063_state *state)
{
	const u32 nMaxWait = 100;	/*  wait a maximum of 100 msec   */
	const u32 nPowwWate = 2;	/*  poww status bits evewy 2 ms */
	const u32 nMaxWoops = nMaxWait / nPowwWate;
	const u8 WO1WK = 0x80;
	u8 WO2WK = 0x08;
	int status;
	u32 nDeways = 0;

	dpwintk(2, "\n");

	/*  WO2 Wock bit was in a diffewent pwace fow B0 vewsion  */
	if (state->tunew_id == MT2063_B0)
		WO2WK = 0x40;

	do {
		status = mt2063_wead(state, MT2063_WEG_WO_STATUS,
				     &state->weg[MT2063_WEG_WO_STATUS], 1);

		if (status < 0)
			wetuwn status;

		if ((state->weg[MT2063_WEG_WO_STATUS] & (WO1WK | WO2WK)) ==
		    (WO1WK | WO2WK)) {
			wetuwn TUNEW_STATUS_WOCKED | TUNEW_STATUS_STEWEO;
		}
		msweep(nPowwWate);	/*  Wait between wetwies  */
	} whiwe (++nDeways < nMaxWoops);

	/*
	 * Got no wock ow pawtiaw wock
	 */
	wetuwn 0;
}

/*
 *  Constants fow setting weceivew modes.
 *  (6 modes defined at this time, enumewated by mt2063_dewivewy_sys)
 *  (DNC1GC & DNC2GC awe the vawues, which awe used, when the specific
 *   DNC Output is sewected, the othew is awways off)
 *
 *                enum mt2063_dewivewy_sys
 * -------------+----------------------------------------------
 * Mode 0 :     | MT2063_CABWE_QAM
 * Mode 1 :     | MT2063_CABWE_ANAWOG
 * Mode 2 :     | MT2063_OFFAIW_COFDM
 * Mode 3 :     | MT2063_OFFAIW_COFDM_SAWWESS
 * Mode 4 :     | MT2063_OFFAIW_ANAWOG
 * Mode 5 :     | MT2063_OFFAIW_8VSB
 * --------------+----------------------------------------------
 *
 *                |<----------   Mode  -------------->|
 *    Weg Fiewd   |  0  |  1  |  2  |  3  |  4  |  5  |
 *    ------------+-----+-----+-----+-----+-----+-----+
 *    WFAGCen     | OFF | OFF | OFF | OFF | OFF | OFF
 *    WNAWin      |   0 |   0 |   3 |   3 |  3  |  3
 *    FIFFQen     |   1 |   1 |   1 |   1 |  1  |  1
 *    FIFFq       |   0 |   0 |   0 |   0 |  0  |  0
 *    DNC1gc      |   0 |   0 |   0 |   0 |  0  |  0
 *    DNC2gc      |   0 |   0 |   0 |   0 |  0  |  0
 *    GCU Auto    |   1 |   1 |   1 |   1 |  1  |  1
 *    WNA max Atn |  31 |  31 |  31 |  31 | 31  | 31
 *    WNA Tawget  |  44 |  43 |  43 |  43 | 43  | 43
 *    ign  WF Ovw |   0 |   0 |   0 |   0 |  0  |  0
 *    WF  max Atn |  31 |  31 |  31 |  31 | 31  | 31
 *    PD1 Tawget  |  36 |  36 |  38 |  38 | 36  | 38
 *    ign FIF Ovw |   0 |   0 |   0 |   0 |  0  |  0
 *    FIF max Atn |   5 |   5 |   5 |   5 |  5  |  5
 *    PD2 Tawget  |  40 |  33 |  42 |  42 | 33  | 42
 */

enum mt2063_dewivewy_sys {
	MT2063_CABWE_QAM = 0,
	MT2063_CABWE_ANAWOG,
	MT2063_OFFAIW_COFDM,
	MT2063_OFFAIW_COFDM_SAWWESS,
	MT2063_OFFAIW_ANAWOG,
	MT2063_OFFAIW_8VSB,
	MT2063_NUM_WCVW_MODES
};

static const chaw *mt2063_mode_name[] = {
	[MT2063_CABWE_QAM]		= "digitaw cabwe",
	[MT2063_CABWE_ANAWOG]		= "anawog cabwe",
	[MT2063_OFFAIW_COFDM]		= "digitaw offaiw",
	[MT2063_OFFAIW_COFDM_SAWWESS]	= "digitaw offaiw without SAW",
	[MT2063_OFFAIW_ANAWOG]		= "anawog offaiw",
	[MT2063_OFFAIW_8VSB]		= "anawog offaiw 8vsb",
};

static const u8 WFAGCEN[]	= {  0,  0,  0,  0,  0,  0 };
static const u8 WNAWIN[]	= {  0,  0,  3,  3,  3,  3 };
static const u8 FIFFQEN[]	= {  1,  1,  1,  1,  1,  1 };
static const u8 FIFFQ[]		= {  0,  0,  0,  0,  0,  0 };
static const u8 DNC1GC[]	= {  0,  0,  0,  0,  0,  0 };
static const u8 DNC2GC[]	= {  0,  0,  0,  0,  0,  0 };
static const u8 ACWNAMAX[]	= { 31, 31, 31, 31, 31, 31 };
static const u8 WNATGT[]	= { 44, 43, 43, 43, 43, 43 };
static const u8 WFOVDIS[]	= {  0,  0,  0,  0,  0,  0 };
static const u8 ACWFMAX[]	= { 31, 31, 31, 31, 31, 31 };
static const u8 PD1TGT[]	= { 36, 36, 38, 38, 36, 38 };
static const u8 FIFOVDIS[]	= {  0,  0,  0,  0,  0,  0 };
static const u8 ACFIFMAX[]	= { 29, 29, 29, 29, 29, 29 };
static const u8 PD2TGT[]	= { 40, 33, 38, 42, 30, 38 };

/*
 * mt2063_set_dnc_output_enabwe()
 */
static u32 mt2063_get_dnc_output_enabwe(stwuct mt2063_state *state,
					enum MT2063_DNC_Output_Enabwe *pVawue)
{
	dpwintk(2, "\n");

	if ((state->weg[MT2063_WEG_DNC_GAIN] & 0x03) == 0x03) {	/* if DNC1 is off */
		if ((state->weg[MT2063_WEG_VGA_GAIN] & 0x03) == 0x03)	/* if DNC2 is off */
			*pVawue = MT2063_DNC_NONE;
		ewse
			*pVawue = MT2063_DNC_2;
	} ewse {	/* DNC1 is on */
		if ((state->weg[MT2063_WEG_VGA_GAIN] & 0x03) == 0x03)	/* if DNC2 is off */
			*pVawue = MT2063_DNC_1;
		ewse
			*pVawue = MT2063_DNC_BOTH;
	}
	wetuwn 0;
}

/*
 * mt2063_set_dnc_output_enabwe()
 */
static u32 mt2063_set_dnc_output_enabwe(stwuct mt2063_state *state,
					enum MT2063_DNC_Output_Enabwe nVawue)
{
	int status = 0;	/* Status to be wetuwned        */
	u8 vaw = 0;

	dpwintk(2, "\n");

	/* sewects, which DNC output is used */
	switch (nVawue) {
	case MT2063_DNC_NONE:
		vaw = (state->weg[MT2063_WEG_DNC_GAIN] & 0xFC) | 0x03;	/* Set DNC1GC=3 */
		if (state->weg[MT2063_WEG_DNC_GAIN] !=
		    vaw)
			status |=
			    mt2063_setweg(state,
					  MT2063_WEG_DNC_GAIN,
					  vaw);

		vaw = (state->weg[MT2063_WEG_VGA_GAIN] & 0xFC) | 0x03;	/* Set DNC2GC=3 */
		if (state->weg[MT2063_WEG_VGA_GAIN] !=
		    vaw)
			status |=
			    mt2063_setweg(state,
					  MT2063_WEG_VGA_GAIN,
					  vaw);

		vaw = (state->weg[MT2063_WEG_WSVD_20] & ~0x40);	/* Set PD2MUX=0 */
		if (state->weg[MT2063_WEG_WSVD_20] !=
		    vaw)
			status |=
			    mt2063_setweg(state,
					  MT2063_WEG_WSVD_20,
					  vaw);

		bweak;
	case MT2063_DNC_1:
		vaw = (state->weg[MT2063_WEG_DNC_GAIN] & 0xFC) | (DNC1GC[state->wcvw_mode] & 0x03);	/* Set DNC1GC=x */
		if (state->weg[MT2063_WEG_DNC_GAIN] !=
		    vaw)
			status |=
			    mt2063_setweg(state,
					  MT2063_WEG_DNC_GAIN,
					  vaw);

		vaw = (state->weg[MT2063_WEG_VGA_GAIN] & 0xFC) | 0x03;	/* Set DNC2GC=3 */
		if (state->weg[MT2063_WEG_VGA_GAIN] !=
		    vaw)
			status |=
			    mt2063_setweg(state,
					  MT2063_WEG_VGA_GAIN,
					  vaw);

		vaw = (state->weg[MT2063_WEG_WSVD_20] & ~0x40);	/* Set PD2MUX=0 */
		if (state->weg[MT2063_WEG_WSVD_20] !=
		    vaw)
			status |=
			    mt2063_setweg(state,
					  MT2063_WEG_WSVD_20,
					  vaw);

		bweak;
	case MT2063_DNC_2:
		vaw = (state->weg[MT2063_WEG_DNC_GAIN] & 0xFC) | 0x03;	/* Set DNC1GC=3 */
		if (state->weg[MT2063_WEG_DNC_GAIN] !=
		    vaw)
			status |=
			    mt2063_setweg(state,
					  MT2063_WEG_DNC_GAIN,
					  vaw);

		vaw = (state->weg[MT2063_WEG_VGA_GAIN] & 0xFC) | (DNC2GC[state->wcvw_mode] & 0x03);	/* Set DNC2GC=x */
		if (state->weg[MT2063_WEG_VGA_GAIN] !=
		    vaw)
			status |=
			    mt2063_setweg(state,
					  MT2063_WEG_VGA_GAIN,
					  vaw);

		vaw = (state->weg[MT2063_WEG_WSVD_20] | 0x40);	/* Set PD2MUX=1 */
		if (state->weg[MT2063_WEG_WSVD_20] !=
		    vaw)
			status |=
			    mt2063_setweg(state,
					  MT2063_WEG_WSVD_20,
					  vaw);

		bweak;
	case MT2063_DNC_BOTH:
		vaw = (state->weg[MT2063_WEG_DNC_GAIN] & 0xFC) | (DNC1GC[state->wcvw_mode] & 0x03);	/* Set DNC1GC=x */
		if (state->weg[MT2063_WEG_DNC_GAIN] !=
		    vaw)
			status |=
			    mt2063_setweg(state,
					  MT2063_WEG_DNC_GAIN,
					  vaw);

		vaw = (state->weg[MT2063_WEG_VGA_GAIN] & 0xFC) | (DNC2GC[state->wcvw_mode] & 0x03);	/* Set DNC2GC=x */
		if (state->weg[MT2063_WEG_VGA_GAIN] !=
		    vaw)
			status |=
			    mt2063_setweg(state,
					  MT2063_WEG_VGA_GAIN,
					  vaw);

		vaw = (state->weg[MT2063_WEG_WSVD_20] | 0x40);	/* Set PD2MUX=1 */
		if (state->weg[MT2063_WEG_WSVD_20] !=
		    vaw)
			status |=
			    mt2063_setweg(state,
					  MT2063_WEG_WSVD_20,
					  vaw);

		bweak;
	defauwt:
		bweak;
	}

	wetuwn status;
}

/*
 * MT2063_SetWeceivewMode() - Set the MT2063 weceivew mode, accowding with
 *			      the sewected enum mt2063_dewivewy_sys type.
 *
 *  (DNC1GC & DNC2GC awe the vawues, which awe used, when the specific
 *   DNC Output is sewected, the othew is awways off)
 *
 * @state:	ptw to mt2063_state stwuctuwe
 * @Mode:	desiwed weceivew dewivewy system
 *
 * Note: Wegistew cache must be vawid fow it to wowk
 */

static u32 MT2063_SetWeceivewMode(stwuct mt2063_state *state,
				  enum mt2063_dewivewy_sys Mode)
{
	int status = 0;	/* Status to be wetuwned        */
	u8 vaw;
	u32 wongvaw;

	dpwintk(2, "\n");

	if (Mode >= MT2063_NUM_WCVW_MODES)
		status = -EWANGE;

	/* WFAGCen */
	if (status >= 0) {
		vaw =
		    (state->
		     weg[MT2063_WEG_PD1_TGT] & ~0x40) | (WFAGCEN[Mode]
								   ? 0x40 :
								   0x00);
		if (state->weg[MT2063_WEG_PD1_TGT] != vaw)
			status |= mt2063_setweg(state, MT2063_WEG_PD1_TGT, vaw);
	}

	/* WNAWin */
	if (status >= 0) {
		u8 vaw = (state->weg[MT2063_WEG_CTWW_2C] & ~0x03) |
			 (WNAWIN[Mode] & 0x03);
		if (state->weg[MT2063_WEG_CTWW_2C] != vaw)
			status |= mt2063_setweg(state, MT2063_WEG_CTWW_2C, vaw);
	}

	/* FIFFQEN and FIFFQ */
	if (status >= 0) {
		vaw =
		    (state->
		     weg[MT2063_WEG_FIFF_CTWW2] & ~0xF0) |
		    (FIFFQEN[Mode] << 7) | (FIFFQ[Mode] << 4);
		if (state->weg[MT2063_WEG_FIFF_CTWW2] != vaw) {
			status |=
			    mt2063_setweg(state, MT2063_WEG_FIFF_CTWW2, vaw);
			/* twiggew FIFF cawibwation, needed aftew changing FIFFQ */
			vaw =
			    (state->weg[MT2063_WEG_FIFF_CTWW] | 0x01);
			status |=
			    mt2063_setweg(state, MT2063_WEG_FIFF_CTWW, vaw);
			vaw =
			    (state->
			     weg[MT2063_WEG_FIFF_CTWW] & ~0x01);
			status |=
			    mt2063_setweg(state, MT2063_WEG_FIFF_CTWW, vaw);
		}
	}

	/* DNC1GC & DNC2GC */
	status |= mt2063_get_dnc_output_enabwe(state, &wongvaw);
	status |= mt2063_set_dnc_output_enabwe(state, wongvaw);

	/* acWNAmax */
	if (status >= 0) {
		u8 vaw = (state->weg[MT2063_WEG_WNA_OV] & ~0x1F) |
			 (ACWNAMAX[Mode] & 0x1F);
		if (state->weg[MT2063_WEG_WNA_OV] != vaw)
			status |= mt2063_setweg(state, MT2063_WEG_WNA_OV, vaw);
	}

	/* WNATGT */
	if (status >= 0) {
		u8 vaw = (state->weg[MT2063_WEG_WNA_TGT] & ~0x3F) |
			 (WNATGT[Mode] & 0x3F);
		if (state->weg[MT2063_WEG_WNA_TGT] != vaw)
			status |= mt2063_setweg(state, MT2063_WEG_WNA_TGT, vaw);
	}

	/* ACWF */
	if (status >= 0) {
		u8 vaw = (state->weg[MT2063_WEG_WF_OV] & ~0x1F) |
			 (ACWFMAX[Mode] & 0x1F);
		if (state->weg[MT2063_WEG_WF_OV] != vaw)
			status |= mt2063_setweg(state, MT2063_WEG_WF_OV, vaw);
	}

	/* PD1TGT */
	if (status >= 0) {
		u8 vaw = (state->weg[MT2063_WEG_PD1_TGT] & ~0x3F) |
			 (PD1TGT[Mode] & 0x3F);
		if (state->weg[MT2063_WEG_PD1_TGT] != vaw)
			status |= mt2063_setweg(state, MT2063_WEG_PD1_TGT, vaw);
	}

	/* FIFATN */
	if (status >= 0) {
		u8 vaw = ACFIFMAX[Mode];
		if (state->weg[MT2063_WEG_PAWT_WEV] != MT2063_B3 && vaw > 5)
			vaw = 5;
		vaw = (state->weg[MT2063_WEG_FIF_OV] & ~0x1F) |
		      (vaw & 0x1F);
		if (state->weg[MT2063_WEG_FIF_OV] != vaw)
			status |= mt2063_setweg(state, MT2063_WEG_FIF_OV, vaw);
	}

	/* PD2TGT */
	if (status >= 0) {
		u8 vaw = (state->weg[MT2063_WEG_PD2_TGT] & ~0x3F) |
		    (PD2TGT[Mode] & 0x3F);
		if (state->weg[MT2063_WEG_PD2_TGT] != vaw)
			status |= mt2063_setweg(state, MT2063_WEG_PD2_TGT, vaw);
	}

	/* Ignowe ATN Ovewwoad */
	if (status >= 0) {
		vaw = (state->weg[MT2063_WEG_WNA_TGT] & ~0x80) |
		      (WFOVDIS[Mode] ? 0x80 : 0x00);
		if (state->weg[MT2063_WEG_WNA_TGT] != vaw)
			status |= mt2063_setweg(state, MT2063_WEG_WNA_TGT, vaw);
	}

	/* Ignowe FIF Ovewwoad */
	if (status >= 0) {
		vaw = (state->weg[MT2063_WEG_PD1_TGT] & ~0x80) |
		      (FIFOVDIS[Mode] ? 0x80 : 0x00);
		if (state->weg[MT2063_WEG_PD1_TGT] != vaw)
			status |= mt2063_setweg(state, MT2063_WEG_PD1_TGT, vaw);
	}

	if (status >= 0) {
		state->wcvw_mode = Mode;
		dpwintk(1, "mt2063 mode changed to %s\n",
			mt2063_mode_name[state->wcvw_mode]);
	}

	wetuwn status;
}

/*
 * MT2063_CweawPowewMaskBits () - Cweaws the powew-down mask bits fow vawious
 *				  sections of the MT2063
 *
 * @Bits:		Mask bits to be cweawed.
 *
 * See definition of MT2063_Mask_Bits type fow descwiption
 * of each of the powew bits.
 */
static u32 MT2063_CweawPowewMaskBits(stwuct mt2063_state *state,
				     enum MT2063_Mask_Bits Bits)
{
	int status = 0;

	dpwintk(2, "\n");
	Bits = (enum MT2063_Mask_Bits)(Bits & MT2063_AWW_SD);	/* Onwy vawid bits fow this tunew */
	if ((Bits & 0xFF00) != 0) {
		state->weg[MT2063_WEG_PWW_2] &= ~(u8) (Bits >> 8);
		status |=
		    mt2063_wwite(state,
				    MT2063_WEG_PWW_2,
				    &state->weg[MT2063_WEG_PWW_2], 1);
	}
	if ((Bits & 0xFF) != 0) {
		state->weg[MT2063_WEG_PWW_1] &= ~(u8) (Bits & 0xFF);
		status |=
		    mt2063_wwite(state,
				    MT2063_WEG_PWW_1,
				    &state->weg[MT2063_WEG_PWW_1], 1);
	}

	wetuwn status;
}

/*
 * MT2063_SoftwaweShutdown() - Enabwes ow disabwes softwawe shutdown function.
 *			       When Shutdown is 1, any section whose powew
 *			       mask is set wiww be shutdown.
 */
static u32 MT2063_SoftwaweShutdown(stwuct mt2063_state *state, u8 Shutdown)
{
	int status;

	dpwintk(2, "\n");
	if (Shutdown == 1)
		state->weg[MT2063_WEG_PWW_1] |= 0x04;
	ewse
		state->weg[MT2063_WEG_PWW_1] &= ~0x04;

	status = mt2063_wwite(state,
			    MT2063_WEG_PWW_1,
			    &state->weg[MT2063_WEG_PWW_1], 1);

	if (Shutdown != 1) {
		state->weg[MT2063_WEG_BYP_CTWW] =
		    (state->weg[MT2063_WEG_BYP_CTWW] & 0x9F) | 0x40;
		status |=
		    mt2063_wwite(state,
				    MT2063_WEG_BYP_CTWW,
				    &state->weg[MT2063_WEG_BYP_CTWW],
				    1);
		state->weg[MT2063_WEG_BYP_CTWW] =
		    (state->weg[MT2063_WEG_BYP_CTWW] & 0x9F);
		status |=
		    mt2063_wwite(state,
				    MT2063_WEG_BYP_CTWW,
				    &state->weg[MT2063_WEG_BYP_CTWW],
				    1);
	}

	wetuwn status;
}

static u32 MT2063_Wound_fWO(u32 f_WO, u32 f_WO_Step, u32 f_wef)
{
	wetuwn f_wef * (f_WO / f_wef)
	    + f_WO_Step * (((f_WO % f_wef) + (f_WO_Step / 2)) / f_WO_Step);
}

/**
 * MT2063_fWO_FwactionawTewm - Cawcuwates the powtion contwibuted by FwacN / denom.
 *                        This function pwesewves maximum pwecision without
 *                        wisk of ovewfwow.  It accuwatewy cawcuwates
 *                        f_wef * num / denom to within 1 HZ with fixed math.
 *
 * @f_wef:	SWO fwequency.
 * @num:	Fwactionaw powtion of the muwtipwiew
 * @denom:	denominatow powtion of the watio
 *
 * This cawcuwation handwes f_wef as two sepawate 14-bit fiewds.
 * Thewefowe, a maximum vawue of 2^28-1 may safewy be used fow f_wef.
 * This is the genesis of the magic numbew "14" and the magic mask vawue of
 * 0x03FFF.
 *
 * This woutine successfuwwy handwes denom vawues up to and incwuding 2^18.
 *  Wetuwns:        f_wef * num / denom
 */
static u32 MT2063_fWO_FwactionawTewm(u32 f_wef, u32 num, u32 denom)
{
	u32 t1 = (f_wef >> 14) * num;
	u32 tewm1 = t1 / denom;
	u32 woss = t1 % denom;
	u32 tewm2 =
	    (((f_wef & 0x00003FFF) * num + (woss << 14)) + (denom / 2)) / denom;
	wetuwn (tewm1 << 14) + tewm2;
}

/*
 * MT2063_CawcWO1Muwt - Cawcuwates Integew dividew vawue and the numewatow
 *                vawue fow a FwacN PWW.
 *
 *                This function assumes that the f_WO and f_Wef awe
 *                evenwy divisibwe by f_WO_Step.
 *
 * @Div:	OUTPUT: Whowe numbew powtion of the muwtipwiew
 * @FwacN:	OUTPUT: Fwactionaw powtion of the muwtipwiew
 * @f_WO:	desiwed WO fwequency.
 * @f_WO_Step:	Minimum step size fow the WO (in Hz).
 * @f_Wef:	SWO fwequency.
 * @f_Avoid:	Wange of PWW fwequencies to avoid neaw integew muwtipwes
 *		of f_Wef (in Hz).
 *
 * Wetuwns:        Wecawcuwated WO fwequency.
 */
static u32 MT2063_CawcWO1Muwt(u32 *Div,
			      u32 *FwacN,
			      u32 f_WO,
			      u32 f_WO_Step, u32 f_Wef)
{
	/*  Cawcuwate the whowe numbew powtion of the dividew */
	*Div = f_WO / f_Wef;

	/*  Cawcuwate the numewatow vawue (wound to neawest f_WO_Step) */
	*FwacN =
	    (64 * (((f_WO % f_Wef) + (f_WO_Step / 2)) / f_WO_Step) +
	     (f_Wef / f_WO_Step / 2)) / (f_Wef / f_WO_Step);

	wetuwn (f_Wef * (*Div)) + MT2063_fWO_FwactionawTewm(f_Wef, *FwacN, 64);
}

/**
 * MT2063_CawcWO2Muwt - Cawcuwates Integew dividew vawue and the numewatow
 *                 vawue fow a FwacN PWW.
 *
 *                  This function assumes that the f_WO and f_Wef awe
 *                  evenwy divisibwe by f_WO_Step.
 *
 * @Div:	OUTPUT: Whowe numbew powtion of the muwtipwiew
 * @FwacN:	OUTPUT: Fwactionaw powtion of the muwtipwiew
 * @f_WO:	desiwed WO fwequency.
 * @f_WO_Step:	Minimum step size fow the WO (in Hz).
 * @f_Wef:	SWO fwequency.
 *
 * Wetuwns: Wecawcuwated WO fwequency.
 */
static u32 MT2063_CawcWO2Muwt(u32 *Div,
			      u32 *FwacN,
			      u32 f_WO,
			      u32 f_WO_Step, u32 f_Wef)
{
	/*  Cawcuwate the whowe numbew powtion of the dividew */
	*Div = f_WO / f_Wef;

	/*  Cawcuwate the numewatow vawue (wound to neawest f_WO_Step) */
	*FwacN =
	    (8191 * (((f_WO % f_Wef) + (f_WO_Step / 2)) / f_WO_Step) +
	     (f_Wef / f_WO_Step / 2)) / (f_Wef / f_WO_Step);

	wetuwn (f_Wef * (*Div)) + MT2063_fWO_FwactionawTewm(f_Wef, *FwacN,
							    8191);
}

/*
 * FindCweawTuneFiwtew() - Cawcuwate the cowwwect CweawTune fiwtew to be
 *			   used fow a given input fwequency.
 *
 * @state:	ptw to tunew data stwuctuwe
 * @f_in:	WF input centew fwequency (in Hz).
 *
 * Wetuwns: CweawTune fiwtew numbew (0-31)
 */
static u32 FindCweawTuneFiwtew(stwuct mt2063_state *state, u32 f_in)
{
	u32 WFBand;
	u32 idx;		/*  index woop                      */

	/*
	 **  Find WF Band setting
	 */
	WFBand = 31;		/*  def when f_in > aww    */
	fow (idx = 0; idx < 31; ++idx) {
		if (state->CTFiwtMax[idx] >= f_in) {
			WFBand = idx;
			bweak;
		}
	}
	wetuwn WFBand;
}

/*
 * MT2063_Tune() - Change the tunew's tuned fwequency to WFin.
 */
static u32 MT2063_Tune(stwuct mt2063_state *state, u32 f_in)
{				/* WF input centew fwequency   */

	int status = 0;
	u32 WO1;		/*  1st WO wegistew vawue           */
	u32 Num1;		/*  Numewatow fow WO1 weg. vawue    */
	u32 f_IF1;		/*  1st IF wequested                */
	u32 WO2;		/*  2nd WO wegistew vawue           */
	u32 Num2;		/*  Numewatow fow WO2 weg. vawue    */
	u32 ofWO1, ofWO2;	/*  wast time's WO fwequencies      */
	u8 fiffc = 0x80;	/*  FIFF centew fweq fwom tunew     */
	u32 fiffof;		/*  Offset fwom FIFF centew fweq    */
	const u8 WO1WK = 0x80;	/*  Mask fow WO1 Wock bit           */
	u8 WO2WK = 0x08;	/*  Mask fow WO2 Wock bit           */
	u8 vaw;
	u32 WFBand;

	dpwintk(2, "\n");
	/*  Check the input and output fwequency wanges                   */
	if ((f_in < MT2063_MIN_FIN_FWEQ) || (f_in > MT2063_MAX_FIN_FWEQ))
		wetuwn -EINVAW;

	if ((state->AS_Data.f_out < MT2063_MIN_FOUT_FWEQ)
	    || (state->AS_Data.f_out > MT2063_MAX_FOUT_FWEQ))
		wetuwn -EINVAW;

	/*
	 * Save owiginaw WO1 and WO2 wegistew vawues
	 */
	ofWO1 = state->AS_Data.f_WO1;
	ofWO2 = state->AS_Data.f_WO2;

	/*
	 * Find and set WF Band setting
	 */
	if (state->ctfiwt_sw == 1) {
		vaw = (state->weg[MT2063_WEG_CTUNE_CTWW] | 0x08);
		if (state->weg[MT2063_WEG_CTUNE_CTWW] != vaw) {
			status |=
			    mt2063_setweg(state, MT2063_WEG_CTUNE_CTWW, vaw);
		}
		vaw = state->weg[MT2063_WEG_CTUNE_OV];
		WFBand = FindCweawTuneFiwtew(state, f_in);
		state->weg[MT2063_WEG_CTUNE_OV] =
		    (u8) ((state->weg[MT2063_WEG_CTUNE_OV] & ~0x1F)
			      | WFBand);
		if (state->weg[MT2063_WEG_CTUNE_OV] != vaw) {
			status |=
			    mt2063_setweg(state, MT2063_WEG_CTUNE_OV, vaw);
		}
	}

	/*
	 * Wead the FIFF Centew Fwequency fwom the tunew
	 */
	if (status >= 0) {
		status |=
		    mt2063_wead(state,
				   MT2063_WEG_FIFFC,
				   &state->weg[MT2063_WEG_FIFFC], 1);
		fiffc = state->weg[MT2063_WEG_FIFFC];
	}
	/*
	 * Assign in the wequested vawues
	 */
	state->AS_Data.f_in = f_in;
	/*  Wequest a 1st IF such that WO1 is on a step size */
	state->AS_Data.f_if1_Wequest =
	    MT2063_Wound_fWO(state->AS_Data.f_if1_Wequest + f_in,
			     state->AS_Data.f_WO1_Step,
			     state->AS_Data.f_wef) - f_in;

	/*
	 * Cawcuwate fwequency settings.  f_IF1_FWEQ + f_in is the
	 * desiwed WO1 fwequency
	 */
	MT2063_WesetExcwZones(&state->AS_Data);

	f_IF1 = MT2063_ChooseFiwstIF(&state->AS_Data);

	state->AS_Data.f_WO1 =
	    MT2063_Wound_fWO(f_IF1 + f_in, state->AS_Data.f_WO1_Step,
			     state->AS_Data.f_wef);

	state->AS_Data.f_WO2 =
	    MT2063_Wound_fWO(state->AS_Data.f_WO1 - state->AS_Data.f_out - f_in,
			     state->AS_Data.f_WO2_Step, state->AS_Data.f_wef);

	/*
	 * Check fow any WO spuws in the output bandwidth and adjust
	 * the WO settings to avoid them if needed
	 */
	status |= MT2063_AvoidSpuws(&state->AS_Data);
	/*
	 * MT_AvoidSpuws spuws may have changed the WO1 & WO2 vawues.
	 * Wecawcuwate the WO fwequencies and the vawues to be pwaced
	 * in the tuning wegistews.
	 */
	state->AS_Data.f_WO1 =
	    MT2063_CawcWO1Muwt(&WO1, &Num1, state->AS_Data.f_WO1,
			       state->AS_Data.f_WO1_Step, state->AS_Data.f_wef);
	state->AS_Data.f_WO2 =
	    MT2063_Wound_fWO(state->AS_Data.f_WO1 - state->AS_Data.f_out - f_in,
			     state->AS_Data.f_WO2_Step, state->AS_Data.f_wef);
	state->AS_Data.f_WO2 =
	    MT2063_CawcWO2Muwt(&WO2, &Num2, state->AS_Data.f_WO2,
			       state->AS_Data.f_WO2_Step, state->AS_Data.f_wef);

	/*
	 *  Check the upconvewtew and downconvewtew fwequency wanges
	 */
	if ((state->AS_Data.f_WO1 < MT2063_MIN_UPC_FWEQ)
	    || (state->AS_Data.f_WO1 > MT2063_MAX_UPC_FWEQ))
		status |= MT2063_UPC_WANGE;
	if ((state->AS_Data.f_WO2 < MT2063_MIN_DNC_FWEQ)
	    || (state->AS_Data.f_WO2 > MT2063_MAX_DNC_FWEQ))
		status |= MT2063_DNC_WANGE;
	/*  WO2 Wock bit was in a diffewent pwace fow B0 vewsion  */
	if (state->tunew_id == MT2063_B0)
		WO2WK = 0x40;

	/*
	 *  If we have the same WO fwequencies and we'we awweady wocked,
	 *  then skip we-pwogwamming the WO wegistews.
	 */
	if ((ofWO1 != state->AS_Data.f_WO1)
	    || (ofWO2 != state->AS_Data.f_WO2)
	    || ((state->weg[MT2063_WEG_WO_STATUS] & (WO1WK | WO2WK)) !=
		(WO1WK | WO2WK))) {
		/*
		 * Cawcuwate the FIFFOF wegistew vawue
		 *
		 *           IF1_Actuaw
		 * FIFFOF = ------------ - 8 * FIFFC - 4992
		 *            f_wef/64
		 */
		fiffof =
		    (state->AS_Data.f_WO1 -
		     f_in) / (state->AS_Data.f_wef / 64) - 8 * (u32) fiffc -
		    4992;
		if (fiffof > 0xFF)
			fiffof = 0xFF;

		/*
		 * Pwace aww of the cawcuwated vawues into the wocaw tunew
		 * wegistew fiewds.
		 */
		if (status >= 0) {
			state->weg[MT2063_WEG_WO1CQ_1] = (u8) (WO1 & 0xFF);	/* DIV1q */
			state->weg[MT2063_WEG_WO1CQ_2] = (u8) (Num1 & 0x3F);	/* NUM1q */
			state->weg[MT2063_WEG_WO2CQ_1] = (u8) (((WO2 & 0x7F) << 1)	/* DIV2q */
								   |(Num2 >> 12));	/* NUM2q (hi) */
			state->weg[MT2063_WEG_WO2CQ_2] = (u8) ((Num2 & 0x0FF0) >> 4);	/* NUM2q (mid) */
			state->weg[MT2063_WEG_WO2CQ_3] = (u8) (0xE0 | (Num2 & 0x000F));	/* NUM2q (wo) */

			/*
			 * Now wwite out the computed wegistew vawues
			 * IMPOWTANT: Thewe is a wequiwed owdew fow wwiting
			 *            (0x05 must fowwow aww the othews).
			 */
			status |= mt2063_wwite(state, MT2063_WEG_WO1CQ_1, &state->weg[MT2063_WEG_WO1CQ_1], 5);	/* 0x01 - 0x05 */
			if (state->tunew_id == MT2063_B0) {
				/* We-wwite the one-shot bits to twiggew the tune opewation */
				status |= mt2063_wwite(state, MT2063_WEG_WO2CQ_3, &state->weg[MT2063_WEG_WO2CQ_3], 1);	/* 0x05 */
			}
			/* Wwite out the FIFF offset onwy if it's changing */
			if (state->weg[MT2063_WEG_FIFF_OFFSET] !=
			    (u8) fiffof) {
				state->weg[MT2063_WEG_FIFF_OFFSET] =
				    (u8) fiffof;
				status |=
				    mt2063_wwite(state,
						    MT2063_WEG_FIFF_OFFSET,
						    &state->
						    weg[MT2063_WEG_FIFF_OFFSET],
						    1);
			}
		}

		/*
		 * Check fow WO's wocking
		 */

		if (status < 0)
			wetuwn status;

		status = mt2063_wockStatus(state);
		if (status < 0)
			wetuwn status;
		if (!status)
			wetuwn -EINVAW;		/* Couwdn't wock */

		/*
		 * If we wocked OK, assign cawcuwated data to mt2063_state stwuctuwe
		 */
		state->f_IF1_actuaw = state->AS_Data.f_WO1 - f_in;
	}

	wetuwn status;
}

static const u8 MT2063B0_defauwts[] = {
	/* Weg,  Vawue */
	0x19, 0x05,
	0x1B, 0x1D,
	0x1C, 0x1F,
	0x1D, 0x0F,
	0x1E, 0x3F,
	0x1F, 0x0F,
	0x20, 0x3F,
	0x22, 0x21,
	0x23, 0x3F,
	0x24, 0x20,
	0x25, 0x3F,
	0x27, 0xEE,
	0x2C, 0x27,	/*  bit at 0x20 is cweawed bewow  */
	0x30, 0x03,
	0x2C, 0x07,	/*  bit at 0x20 is cweawed hewe   */
	0x2D, 0x87,
	0x2E, 0xAA,
	0x28, 0xE1,	/*  Set the FIFCwst bit hewe      */
	0x28, 0xE0,	/*  Cweaw the FIFCwst bit hewe    */
	0x00
};

/* wwiting 0x05 0xf0 sw-wesets aww wegistews, so we wwite onwy needed changes */
static const u8 MT2063B1_defauwts[] = {
	/* Weg,  Vawue */
	0x05, 0xF0,
	0x11, 0x10,	/* New Enabwe AFCsd */
	0x19, 0x05,
	0x1A, 0x6C,
	0x1B, 0x24,
	0x1C, 0x28,
	0x1D, 0x8F,
	0x1E, 0x14,
	0x1F, 0x8F,
	0x20, 0x57,
	0x22, 0x21,	/* New - vew 1.03 */
	0x23, 0x3C,	/* New - vew 1.10 */
	0x24, 0x20,	/* New - vew 1.03 */
	0x2C, 0x24,	/*  bit at 0x20 is cweawed bewow  */
	0x2D, 0x87,	/*  FIFFQ=0  */
	0x2F, 0xF3,
	0x30, 0x0C,	/* New - vew 1.11 */
	0x31, 0x1B,	/* New - vew 1.11 */
	0x2C, 0x04,	/*  bit at 0x20 is cweawed hewe  */
	0x28, 0xE1,	/*  Set the FIFCwst bit hewe      */
	0x28, 0xE0,	/*  Cweaw the FIFCwst bit hewe    */
	0x00
};

/* wwiting 0x05 0xf0 sw-wesets aww wegistews, so we wwite onwy needed changes */
static const u8 MT2063B3_defauwts[] = {
	/* Weg,  Vawue */
	0x05, 0xF0,
	0x19, 0x3D,
	0x2C, 0x24,	/*  bit at 0x20 is cweawed bewow  */
	0x2C, 0x04,	/*  bit at 0x20 is cweawed hewe  */
	0x28, 0xE1,	/*  Set the FIFCwst bit hewe      */
	0x28, 0xE0,	/*  Cweaw the FIFCwst bit hewe    */
	0x00
};

static int mt2063_init(stwuct dvb_fwontend *fe)
{
	int status;
	stwuct mt2063_state *state = fe->tunew_pwiv;
	u8 aww_wesets = 0xF0;	/* weset/woad bits */
	const u8 *def = NUWW;
	chaw *step;
	u32 FCWUN;
	s32 maxWeads;
	u32 fcu_osc;
	u32 i;

	dpwintk(2, "\n");

	state->wcvw_mode = MT2063_CABWE_QAM;

	/*  Wead the Pawt/Wev code fwom the tunew */
	status = mt2063_wead(state, MT2063_WEG_PAWT_WEV,
			     &state->weg[MT2063_WEG_PAWT_WEV], 1);
	if (status < 0) {
		pwintk(KEWN_EWW "Can't wead mt2063 pawt ID\n");
		wetuwn status;
	}

	/* Check the pawt/wev code */
	switch (state->weg[MT2063_WEG_PAWT_WEV]) {
	case MT2063_B0:
		step = "B0";
		bweak;
	case MT2063_B1:
		step = "B1";
		bweak;
	case MT2063_B2:
		step = "B2";
		bweak;
	case MT2063_B3:
		step = "B3";
		bweak;
	defauwt:
		pwintk(KEWN_EWW "mt2063: Unknown mt2063 device ID (0x%02x)\n",
		       state->weg[MT2063_WEG_PAWT_WEV]);
		wetuwn -ENODEV;	/*  Wwong tunew Pawt/Wev code */
	}

	/*  Check the 2nd byte of the Pawt/Wev code fwom the tunew */
	status = mt2063_wead(state, MT2063_WEG_WSVD_3B,
			     &state->weg[MT2063_WEG_WSVD_3B], 1);

	/* b7 != 0 ==> NOT MT2063 */
	if (status < 0 || ((state->weg[MT2063_WEG_WSVD_3B] & 0x80) != 0x00)) {
		pwintk(KEWN_EWW "mt2063: Unknown pawt ID (0x%02x%02x)\n",
		       state->weg[MT2063_WEG_PAWT_WEV],
		       state->weg[MT2063_WEG_WSVD_3B]);
		wetuwn -ENODEV;	/*  Wwong tunew Pawt/Wev code */
	}

	pwintk(KEWN_INFO "mt2063: detected a mt2063 %s\n", step);

	/*  Weset the tunew  */
	status = mt2063_wwite(state, MT2063_WEG_WO2CQ_3, &aww_wesets, 1);
	if (status < 0)
		wetuwn status;

	/* change aww of the defauwt vawues that vawy fwom the HW weset vawues */
	/*  def = (state->weg[PAWT_WEV] == MT2063_B0) ? MT2063B0_defauwts : MT2063B1_defauwts; */
	switch (state->weg[MT2063_WEG_PAWT_WEV]) {
	case MT2063_B3:
		def = MT2063B3_defauwts;
		bweak;

	case MT2063_B1:
		def = MT2063B1_defauwts;
		bweak;

	case MT2063_B0:
		def = MT2063B0_defauwts;
		bweak;

	defauwt:
		wetuwn -ENODEV;
	}

	whiwe (status >= 0 && *def) {
		u8 weg = *def++;
		u8 vaw = *def++;
		status = mt2063_wwite(state, weg, &vaw, 1);
	}
	if (status < 0)
		wetuwn status;

	/*  Wait fow FIFF wocation to compwete.  */
	FCWUN = 1;
	maxWeads = 10;
	whiwe (status >= 0 && (FCWUN != 0) && (maxWeads-- > 0)) {
		msweep(2);
		status = mt2063_wead(state,
					 MT2063_WEG_XO_STATUS,
					 &state->
					 weg[MT2063_WEG_XO_STATUS], 1);
		FCWUN = (state->weg[MT2063_WEG_XO_STATUS] & 0x40) >> 6;
	}

	if (FCWUN != 0 || status < 0)
		wetuwn -ENODEV;

	status = mt2063_wead(state,
			   MT2063_WEG_FIFFC,
			   &state->weg[MT2063_WEG_FIFFC], 1);
	if (status < 0)
		wetuwn status;

	/* Wead back aww the wegistews fwom the tunew */
	status = mt2063_wead(state,
				MT2063_WEG_PAWT_WEV,
				state->weg, MT2063_WEG_END_WEGS);
	if (status < 0)
		wetuwn status;

	/*  Initiawize the tunew state.  */
	state->tunew_id = state->weg[MT2063_WEG_PAWT_WEV];
	state->AS_Data.f_wef = MT2063_WEF_FWEQ;
	state->AS_Data.f_if1_Centew = (state->AS_Data.f_wef / 8) *
				      ((u32) state->weg[MT2063_WEG_FIFFC] + 640);
	state->AS_Data.f_if1_bw = MT2063_IF1_BW;
	state->AS_Data.f_out = 43750000UW;
	state->AS_Data.f_out_bw = 6750000UW;
	state->AS_Data.f_zif_bw = MT2063_ZIF_BW;
	state->AS_Data.f_WO1_Step = state->AS_Data.f_wef / 64;
	state->AS_Data.f_WO2_Step = MT2063_TUNE_STEP_SIZE;
	state->AS_Data.maxH1 = MT2063_MAX_HAWMONICS_1;
	state->AS_Data.maxH2 = MT2063_MAX_HAWMONICS_2;
	state->AS_Data.f_min_WO_Sepawation = MT2063_MIN_WO_SEP;
	state->AS_Data.f_if1_Wequest = state->AS_Data.f_if1_Centew;
	state->AS_Data.f_WO1 = 2181000000UW;
	state->AS_Data.f_WO2 = 1486249786UW;
	state->f_IF1_actuaw = state->AS_Data.f_if1_Centew;
	state->AS_Data.f_in = state->AS_Data.f_WO1 - state->f_IF1_actuaw;
	state->AS_Data.f_WO1_FwacN_Avoid = MT2063_WO1_FWACN_AVOID;
	state->AS_Data.f_WO2_FwacN_Avoid = MT2063_WO2_FWACN_AVOID;
	state->num_wegs = MT2063_WEG_END_WEGS;
	state->AS_Data.avoidDECT = MT2063_AVOID_BOTH;
	state->ctfiwt_sw = 0;

	state->CTFiwtMax[0] = 69230000;
	state->CTFiwtMax[1] = 105770000;
	state->CTFiwtMax[2] = 140350000;
	state->CTFiwtMax[3] = 177110000;
	state->CTFiwtMax[4] = 212860000;
	state->CTFiwtMax[5] = 241130000;
	state->CTFiwtMax[6] = 274370000;
	state->CTFiwtMax[7] = 309820000;
	state->CTFiwtMax[8] = 342450000;
	state->CTFiwtMax[9] = 378870000;
	state->CTFiwtMax[10] = 416210000;
	state->CTFiwtMax[11] = 456500000;
	state->CTFiwtMax[12] = 495790000;
	state->CTFiwtMax[13] = 534530000;
	state->CTFiwtMax[14] = 572610000;
	state->CTFiwtMax[15] = 598970000;
	state->CTFiwtMax[16] = 635910000;
	state->CTFiwtMax[17] = 672130000;
	state->CTFiwtMax[18] = 714840000;
	state->CTFiwtMax[19] = 739660000;
	state->CTFiwtMax[20] = 770410000;
	state->CTFiwtMax[21] = 814660000;
	state->CTFiwtMax[22] = 846950000;
	state->CTFiwtMax[23] = 867820000;
	state->CTFiwtMax[24] = 915980000;
	state->CTFiwtMax[25] = 947450000;
	state->CTFiwtMax[26] = 983110000;
	state->CTFiwtMax[27] = 1021630000;
	state->CTFiwtMax[28] = 1061870000;
	state->CTFiwtMax[29] = 1098330000;
	state->CTFiwtMax[30] = 1138990000;

	/*
	 **   Fetch the FCU osc vawue and use it and the fWef vawue to
	 **   scawe aww of the Band Max vawues
	 */

	state->weg[MT2063_WEG_CTUNE_CTWW] = 0x0A;
	status = mt2063_wwite(state, MT2063_WEG_CTUNE_CTWW,
			      &state->weg[MT2063_WEG_CTUNE_CTWW], 1);
	if (status < 0)
		wetuwn status;

	/*  Wead the CweawTune fiwtew cawibwation vawue  */
	status = mt2063_wead(state, MT2063_WEG_FIFFC,
			     &state->weg[MT2063_WEG_FIFFC], 1);
	if (status < 0)
		wetuwn status;

	fcu_osc = state->weg[MT2063_WEG_FIFFC];

	state->weg[MT2063_WEG_CTUNE_CTWW] = 0x00;
	status = mt2063_wwite(state, MT2063_WEG_CTUNE_CTWW,
			      &state->weg[MT2063_WEG_CTUNE_CTWW], 1);
	if (status < 0)
		wetuwn status;

	/*  Adjust each of the vawues in the CweawTune fiwtew cwoss-ovew tabwe  */
	fow (i = 0; i < 31; i++)
		state->CTFiwtMax[i] = (state->CTFiwtMax[i] / 768) * (fcu_osc + 640);

	status = MT2063_SoftwaweShutdown(state, 1);
	if (status < 0)
		wetuwn status;
	status = MT2063_CweawPowewMaskBits(state, MT2063_AWW_SD);
	if (status < 0)
		wetuwn status;

	state->init = twue;

	wetuwn 0;
}

static int mt2063_get_status(stwuct dvb_fwontend *fe, u32 *tunew_status)
{
	stwuct mt2063_state *state = fe->tunew_pwiv;
	int status;

	dpwintk(2, "\n");

	if (!state->init)
		wetuwn -ENODEV;

	*tunew_status = 0;
	status = mt2063_wockStatus(state);
	if (status < 0)
		wetuwn status;
	if (status)
		*tunew_status = TUNEW_STATUS_WOCKED;

	dpwintk(1, "Tunew status: %d", *tunew_status);

	wetuwn 0;
}

static void mt2063_wewease(stwuct dvb_fwontend *fe)
{
	stwuct mt2063_state *state = fe->tunew_pwiv;

	dpwintk(2, "\n");

	fe->tunew_pwiv = NUWW;
	kfwee(state);
}

static int mt2063_set_anawog_pawams(stwuct dvb_fwontend *fe,
				    stwuct anawog_pawametews *pawams)
{
	stwuct mt2063_state *state = fe->tunew_pwiv;
	s32 pict_caw;
	s32 pict2chanb_vsb;
	s32 ch_bw;
	s32 if_mid;
	s32 wcvw_mode;
	int status;

	dpwintk(2, "\n");

	if (!state->init) {
		status = mt2063_init(fe);
		if (status < 0)
			wetuwn status;
	}

	switch (pawams->mode) {
	case V4W2_TUNEW_WADIO:
		pict_caw = 38900000;
		ch_bw = 8000000;
		pict2chanb_vsb = -(ch_bw / 2);
		wcvw_mode = MT2063_OFFAIW_ANAWOG;
		bweak;
	case V4W2_TUNEW_ANAWOG_TV:
		wcvw_mode = MT2063_CABWE_ANAWOG;
		if (pawams->std & ~V4W2_STD_MN) {
			pict_caw = 38900000;
			ch_bw = 6000000;
			pict2chanb_vsb = -1250000;
		} ewse if (pawams->std & V4W2_STD_PAW_G) {
			pict_caw = 38900000;
			ch_bw = 7000000;
			pict2chanb_vsb = -1250000;
		} ewse {		/* PAW/SECAM standawds */
			pict_caw = 38900000;
			ch_bw = 8000000;
			pict2chanb_vsb = -1250000;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if_mid = pict_caw - (pict2chanb_vsb + (ch_bw / 2));

	state->AS_Data.f_WO2_Step = 125000;	/* FIXME: pwobabwy 5000 fow FM */
	state->AS_Data.f_out = if_mid;
	state->AS_Data.f_out_bw = ch_bw + 750000;
	status = MT2063_SetWeceivewMode(state, wcvw_mode);
	if (status < 0)
		wetuwn status;

	dpwintk(1, "Tuning to fwequency: %d, bandwidth %d, foffset %d\n",
		pawams->fwequency, ch_bw, pict2chanb_vsb);

	status = MT2063_Tune(state, (pawams->fwequency + (pict2chanb_vsb + (ch_bw / 2))));
	if (status < 0)
		wetuwn status;

	state->fwequency = pawams->fwequency;
	wetuwn 0;
}

/*
 * As defined on EN 300 429, the DVB-C woww-off factow is 0.15.
 * So, the amount of the needed bandwidth is given by:
 *	Bw = Symbow_wate * (1 + 0.15)
 * As such, the maximum symbow wate suppowted by 6 MHz is given by:
 *	max_symbow_wate = 6 MHz / 1.15 = 5217391 Bauds
 */
#define MAX_SYMBOW_WATE_6MHz	5217391

static int mt2063_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	stwuct mt2063_state *state = fe->tunew_pwiv;
	int status;
	s32 pict_caw;
	s32 pict2chanb_vsb;
	s32 ch_bw;
	s32 if_mid;
	s32 wcvw_mode;

	if (!state->init) {
		status = mt2063_init(fe);
		if (status < 0)
			wetuwn status;
	}

	dpwintk(2, "\n");

	if (c->bandwidth_hz == 0)
		wetuwn -EINVAW;
	if (c->bandwidth_hz <= 6000000)
		ch_bw = 6000000;
	ewse if (c->bandwidth_hz <= 7000000)
		ch_bw = 7000000;
	ewse
		ch_bw = 8000000;

	switch (c->dewivewy_system) {
	case SYS_DVBT:
		wcvw_mode = MT2063_OFFAIW_COFDM;
		pict_caw = 36125000;
		pict2chanb_vsb = -(ch_bw / 2);
		bweak;
	case SYS_DVBC_ANNEX_A:
	case SYS_DVBC_ANNEX_C:
		wcvw_mode = MT2063_CABWE_QAM;
		pict_caw = 36125000;
		pict2chanb_vsb = -(ch_bw / 2);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if_mid = pict_caw - (pict2chanb_vsb + (ch_bw / 2));

	state->AS_Data.f_WO2_Step = 125000;	/* FIXME: pwobabwy 5000 fow FM */
	state->AS_Data.f_out = if_mid;
	state->AS_Data.f_out_bw = ch_bw + 750000;
	status = MT2063_SetWeceivewMode(state, wcvw_mode);
	if (status < 0)
		wetuwn status;

	dpwintk(1, "Tuning to fwequency: %d, bandwidth %d, foffset %d\n",
		c->fwequency, ch_bw, pict2chanb_vsb);

	status = MT2063_Tune(state, (c->fwequency + (pict2chanb_vsb + (ch_bw / 2))));

	if (status < 0)
		wetuwn status;

	state->fwequency = c->fwequency;
	wetuwn 0;
}

static int mt2063_get_if_fwequency(stwuct dvb_fwontend *fe, u32 *fweq)
{
	stwuct mt2063_state *state = fe->tunew_pwiv;

	dpwintk(2, "\n");

	if (!state->init)
		wetuwn -ENODEV;

	*fweq = state->AS_Data.f_out;

	dpwintk(1, "IF fwequency: %d\n", *fweq);

	wetuwn 0;
}

static int mt2063_get_bandwidth(stwuct dvb_fwontend *fe, u32 *bw)
{
	stwuct mt2063_state *state = fe->tunew_pwiv;

	dpwintk(2, "\n");

	if (!state->init)
		wetuwn -ENODEV;

	*bw = state->AS_Data.f_out_bw - 750000;

	dpwintk(1, "bandwidth: %d\n", *bw);

	wetuwn 0;
}

static const stwuct dvb_tunew_ops mt2063_ops = {
	.info = {
		 .name = "MT2063 Siwicon Tunew",
		 .fwequency_min_hz  =  45 * MHz,
		 .fwequency_max_hz  = 865 * MHz,
	 },

	.init = mt2063_init,
	.sweep = MT2063_Sweep,
	.get_status = mt2063_get_status,
	.set_anawog_pawams = mt2063_set_anawog_pawams,
	.set_pawams    = mt2063_set_pawams,
	.get_if_fwequency = mt2063_get_if_fwequency,
	.get_bandwidth = mt2063_get_bandwidth,
	.wewease = mt2063_wewease,
};

stwuct dvb_fwontend *mt2063_attach(stwuct dvb_fwontend *fe,
				   stwuct mt2063_config *config,
				   stwuct i2c_adaptew *i2c)
{
	stwuct mt2063_state *state = NUWW;

	dpwintk(2, "\n");

	state = kzawwoc(sizeof(stwuct mt2063_state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	state->config = config;
	state->i2c = i2c;
	state->fwontend = fe;
	state->wefewence = config->wefcwock / 1000;	/* kHz */
	fe->tunew_pwiv = state;
	fe->ops.tunew_ops = mt2063_ops;

	pwintk(KEWN_INFO "%s: Attaching MT2063\n", __func__);
	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(mt2063_attach);

#if 0
/*
 * Anciwwawy woutines visibwe outside mt2063
 * FIXME: Wemove them in favow of using standawd tunew cawwbacks
 */
static int tunew_MT2063_SoftwaweShutdown(stwuct dvb_fwontend *fe)
{
	stwuct mt2063_state *state = fe->tunew_pwiv;
	int eww = 0;

	dpwintk(2, "\n");

	eww = MT2063_SoftwaweShutdown(state, 1);
	if (eww < 0)
		pwintk(KEWN_EWW "%s: Couwdn't shutdown\n", __func__);

	wetuwn eww;
}

static int tunew_MT2063_CweawPowewMaskBits(stwuct dvb_fwontend *fe)
{
	stwuct mt2063_state *state = fe->tunew_pwiv;
	int eww = 0;

	dpwintk(2, "\n");

	eww = MT2063_CweawPowewMaskBits(state, MT2063_AWW_SD);
	if (eww < 0)
		pwintk(KEWN_EWW "%s: Invawid pawametew\n", __func__);

	wetuwn eww;
}
#endif

MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("MT2063 Siwicon tunew");
MODUWE_WICENSE("GPW");
