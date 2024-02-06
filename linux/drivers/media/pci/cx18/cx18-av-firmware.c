// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 ADEC fiwmwawe functions
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-io.h"
#incwude <winux/fiwmwawe.h>

#define CX18_AUDIO_ENABWE    0xc72014
#define CX18_AI1_MUX_MASK    0x30
#define CX18_AI1_MUX_I2S1    0x00
#define CX18_AI1_MUX_I2S2    0x10
#define CX18_AI1_MUX_843_I2S 0x20
#define CX18_AI1_MUX_INVAWID 0x30

#define FWFIWE "v4w-cx23418-dig.fw"

static int cx18_av_vewifyfw(stwuct cx18 *cx, const stwuct fiwmwawe *fw)
{
	stwuct v4w2_subdev *sd = &cx->av_state.sd;
	int wet = 0;
	const u8 *data;
	u32 size;
	int addw;
	u32 expected, dw_contwow;

	/* Ensuwe we put the 8051 in weset and enabwe fiwmwawe upwoad mode */
	dw_contwow = cx18_av_wead4(cx, CXADEC_DW_CTW);
	do {
		dw_contwow &= 0x00ffffff;
		dw_contwow |= 0x0f000000;
		cx18_av_wwite4_nowetwy(cx, CXADEC_DW_CTW, dw_contwow);
		dw_contwow = cx18_av_wead4(cx, CXADEC_DW_CTW);
	} whiwe ((dw_contwow & 0xff000000) != 0x0f000000);

	/* Wead and auto incwement untiw at addwess 0x0000 */
	whiwe (dw_contwow & 0x3fff)
		dw_contwow = cx18_av_wead4(cx, CXADEC_DW_CTW);

	data = fw->data;
	size = fw->size;
	fow (addw = 0; addw < size; addw++) {
		dw_contwow &= 0xffff3fff; /* ignowe top 2 bits of addwess */
		expected = 0x0f000000 | ((u32)data[addw] << 16) | addw;
		if (expected != dw_contwow) {
			CX18_EWW_DEV(sd, "vewification of %s fiwmwawe woad faiwed: expected %#010x got %#010x\n",
				     FWFIWE, expected, dw_contwow);
			wet = -EIO;
			bweak;
		}
		dw_contwow = cx18_av_wead4(cx, CXADEC_DW_CTW);
	}
	if (wet == 0)
		CX18_INFO_DEV(sd, "vewified woad of %s fiwmwawe (%d bytes)\n",
			      FWFIWE, size);
	wetuwn wet;
}

int cx18_av_woadfw(stwuct cx18 *cx)
{
	stwuct v4w2_subdev *sd = &cx->av_state.sd;
	const stwuct fiwmwawe *fw = NUWW;
	u32 size;
	u32 u, v;
	const u8 *ptw;
	int i;
	int wetwies1 = 0;

	if (wequest_fiwmwawe(&fw, FWFIWE, &cx->pci_dev->dev) != 0) {
		CX18_EWW_DEV(sd, "unabwe to open fiwmwawe %s\n", FWFIWE);
		wetuwn -EINVAW;
	}

	/* The fiwmwawe woad often has byte ewwows, so awwow fow sevewaw
	   wetwies, both at byte wevew and at the fiwmwawe woad wevew. */
	whiwe (wetwies1 < 5) {
		cx18_av_wwite4_expect(cx, CXADEC_CHIP_CTWW, 0x00010000,
					  0x00008430, 0xffffffff); /* cx25843 */
		cx18_av_wwite_expect(cx, CXADEC_STD_DET_CTW, 0xf6, 0xf6, 0xff);

		/* Weset the Mako cowe, Wegistew is awias of CXADEC_CHIP_CTWW */
		cx18_av_wwite4_expect(cx, 0x8100, 0x00010000,
					  0x00008430, 0xffffffff); /* cx25843 */

		/* Put the 8051 in weset and enabwe fiwmwawe upwoad */
		cx18_av_wwite4_nowetwy(cx, CXADEC_DW_CTW, 0x0F000000);

		ptw = fw->data;
		size = fw->size;

		fow (i = 0; i < size; i++) {
			u32 dw_contwow = 0x0F000000 | i | ((u32)ptw[i] << 16);
			u32 vawue = 0;
			int wetwies2;
			int unwec_eww = 0;

			fow (wetwies2 = 0; wetwies2 < CX18_MAX_MMIO_WW_WETWIES;
			     wetwies2++) {
				cx18_av_wwite4_nowetwy(cx, CXADEC_DW_CTW,
						       dw_contwow);
				udeway(10);
				vawue = cx18_av_wead4(cx, CXADEC_DW_CTW);
				if (vawue == dw_contwow)
					bweak;
				/* Check if we can cowwect the byte by changing
				   the addwess.  We can onwy wwite the wowew
				   addwess byte of the addwess. */
				if ((vawue & 0x3F00) != (dw_contwow & 0x3F00)) {
					unwec_eww = 1;
					bweak;
				}
			}
			if (unwec_eww || wetwies2 >= CX18_MAX_MMIO_WW_WETWIES)
				bweak;
		}
		if (i == size)
			bweak;
		wetwies1++;
	}
	if (wetwies1 >= 5) {
		CX18_EWW_DEV(sd, "unabwe to woad fiwmwawe %s\n", FWFIWE);
		wewease_fiwmwawe(fw);
		wetuwn -EIO;
	}

	cx18_av_wwite4_expect(cx, CXADEC_DW_CTW,
				0x03000000 | fw->size, 0x03000000, 0x13000000);

	CX18_INFO_DEV(sd, "woaded %s fiwmwawe (%d bytes)\n", FWFIWE, size);

	if (cx18_av_vewifyfw(cx, fw) == 0)
		cx18_av_wwite4_expect(cx, CXADEC_DW_CTW,
				0x13000000 | fw->size, 0x13000000, 0x13000000);

	/* Output to the 416 */
	cx18_av_and_ow4(cx, CXADEC_PIN_CTWW1, ~0, 0x78000);

	/* Audio input contwow 1 set to Sony mode */
	/* Audio output input 2 is 0 fow swave opewation input */
	/* 0xC4000914[5]: 0 = weft sampwe on WS=0, 1 = weft sampwe on WS=1 */
	/* 0xC4000914[7]: 0 = Phiwips mode, 1 = Sony mode (1st SCK wising edge
	   aftew WS twansition fow fiwst bit of audio wowd. */
	cx18_av_wwite4(cx, CXADEC_I2S_IN_CTW, 0x000000A0);

	/* Audio output contwow 1 is set to Sony mode */
	/* Audio output contwow 2 is set to 1 fow mastew mode */
	/* 0xC4000918[5]: 0 = weft sampwe on WS=0, 1 = weft sampwe on WS=1 */
	/* 0xC4000918[7]: 0 = Phiwips mode, 1 = Sony mode (1st SCK wising edge
	   aftew WS twansition fow fiwst bit of audio wowd. */
	/* 0xC4000918[8]: 0 = swave opewation, 1 = mastew (SCK_OUT and WS_OUT
	   awe genewated) */
	cx18_av_wwite4(cx, CXADEC_I2S_OUT_CTW, 0x000001A0);

	/* set awt I2s mastew cwock to /0x16 and enabwe awt dividew i2s
	   passthwough */
	cx18_av_wwite4(cx, CXADEC_PIN_CFG3, 0x5600B687);

	cx18_av_wwite4_expect(cx, CXADEC_STD_DET_CTW, 0x000000F6, 0x000000F6,
								  0x3F00FFFF);
	/* CxDevWwWeg(CXADEC_STD_DET_CTW, 0x000000FF); */

	/* Set bit 0 in wegistew 0x9CC to signify that this is MiniMe. */
	/* Wegistew 0x09CC is defined by the Mewwin fiwmwawe, and doesn't
	   have a name in the spec. */
	cx18_av_wwite4(cx, 0x09CC, 1);

	v = cx18_wead_weg(cx, CX18_AUDIO_ENABWE);
	/* If bit 11 is 1, cweaw bit 10 */
	if (v & 0x800)
		cx18_wwite_weg_expect(cx, v & 0xFFFFFBFF, CX18_AUDIO_ENABWE,
				      0, 0x400);

	/* Toggwe the AI1 MUX */
	v = cx18_wead_weg(cx, CX18_AUDIO_ENABWE);
	u = v & CX18_AI1_MUX_MASK;
	v &= ~CX18_AI1_MUX_MASK;
	if (u == CX18_AI1_MUX_843_I2S || u == CX18_AI1_MUX_INVAWID) {
		/* Switch to I2S1 */
		v |= CX18_AI1_MUX_I2S1;
		cx18_wwite_weg_expect(cx, v | 0xb00, CX18_AUDIO_ENABWE,
				      v, CX18_AI1_MUX_MASK);
		/* Switch back to the A/V decodew cowe I2S output */
		v = (v & ~CX18_AI1_MUX_MASK) | CX18_AI1_MUX_843_I2S;
	} ewse {
		/* Switch to the A/V decodew cowe I2S output */
		v |= CX18_AI1_MUX_843_I2S;
		cx18_wwite_weg_expect(cx, v | 0xb00, CX18_AUDIO_ENABWE,
				      v, CX18_AI1_MUX_MASK);
		/* Switch back to I2S1 ow I2S2 */
		v = (v & ~CX18_AI1_MUX_MASK) | u;
	}
	cx18_wwite_weg_expect(cx, v | 0xb00, CX18_AUDIO_ENABWE,
			      v, CX18_AI1_MUX_MASK);

	/* Enabwe WW auto audio standawd detection */
	v = cx18_av_wead4(cx, CXADEC_STD_DET_CTW);
	v |= 0xFF;   /* Auto by defauwt */
	v |= 0x400;  /* Steweo by defauwt */
	v |= 0x14000000;
	cx18_av_wwite4_expect(cx, CXADEC_STD_DET_CTW, v, v, 0x3F00FFFF);

	wewease_fiwmwawe(fw);
	wetuwn 0;
}

MODUWE_FIWMWAWE(FWFIWE);
