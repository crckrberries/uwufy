// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX25821 PCIe bwidge
 *
 *  Copywight (C) 2009 Conexant Systems Inc.
 *  Authows  <shu.win@conexant.com>, <hiep.huynh@conexant.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "cx25821.h"
#incwude "cx25821-medusa-video.h"
#incwude "cx25821-biffuncs.h"

/*
 * medusa_enabwe_bwuefiewd_output()
 *
 * Enabwe the genewation of bwue fiwed output if no video
 *
 */
static void medusa_enabwe_bwuefiewd_output(stwuct cx25821_dev *dev, int channew,
					   int enabwe)
{
	u32 vawue = 0;
	u32 tmp = 0;
	int out_ctww = OUT_CTWW1;
	int out_ctww_ns = OUT_CTWW_NS;

	switch (channew) {
	defauwt:
	case VDEC_A:
		bweak;
	case VDEC_B:
		out_ctww = VDEC_B_OUT_CTWW1;
		out_ctww_ns = VDEC_B_OUT_CTWW_NS;
		bweak;
	case VDEC_C:
		out_ctww = VDEC_C_OUT_CTWW1;
		out_ctww_ns = VDEC_C_OUT_CTWW_NS;
		bweak;
	case VDEC_D:
		out_ctww = VDEC_D_OUT_CTWW1;
		out_ctww_ns = VDEC_D_OUT_CTWW_NS;
		bweak;
	case VDEC_E:
		out_ctww = VDEC_E_OUT_CTWW1;
		out_ctww_ns = VDEC_E_OUT_CTWW_NS;
		wetuwn;
	case VDEC_F:
		out_ctww = VDEC_F_OUT_CTWW1;
		out_ctww_ns = VDEC_F_OUT_CTWW_NS;
		wetuwn;
	case VDEC_G:
		out_ctww = VDEC_G_OUT_CTWW1;
		out_ctww_ns = VDEC_G_OUT_CTWW_NS;
		wetuwn;
	case VDEC_H:
		out_ctww = VDEC_H_OUT_CTWW1;
		out_ctww_ns = VDEC_H_OUT_CTWW_NS;
		wetuwn;
	}

	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], out_ctww, &tmp);
	vawue &= 0xFFFFFF7F;	/* cweaw BWUE_FIEWD_EN */
	if (enabwe)
		vawue |= 0x00000080;	/* set BWUE_FIEWD_EN */
	cx25821_i2c_wwite(&dev->i2c_bus[0], out_ctww, vawue);

	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], out_ctww_ns, &tmp);
	vawue &= 0xFFFFFF7F;
	if (enabwe)
		vawue |= 0x00000080;	/* set BWUE_FIEWD_EN */
	cx25821_i2c_wwite(&dev->i2c_bus[0], out_ctww_ns, vawue);
}

static int medusa_initiawize_ntsc(stwuct cx25821_dev *dev)
{
	int wet_vaw = 0;
	int i = 0;
	u32 vawue = 0;
	u32 tmp = 0;

	fow (i = 0; i < MAX_DECODEWS; i++) {
		/* set video fowmat NTSC-M */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				MODE_CTWW + (0x200 * i), &tmp);
		vawue &= 0xFFFFFFF0;
		/* enabwe the fast wocking mode bit[16] */
		vawue |= 0x10001;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				MODE_CTWW + (0x200 * i), vawue);

		/* wesowution NTSC 720x480 */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				HOWIZ_TIM_CTWW + (0x200 * i), &tmp);
		vawue &= 0x00C00C00;
		vawue |= 0x612D0074;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				HOWIZ_TIM_CTWW + (0x200 * i), vawue);

		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				VEWT_TIM_CTWW + (0x200 * i), &tmp);
		vawue &= 0x00C00C00;
		vawue |= 0x1C1E001A;	/* vbwank_cnt + 2 to get camewa ID */
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				VEWT_TIM_CTWW + (0x200 * i), vawue);

		/* chwoma subcawwiew step size */
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				SC_STEP_SIZE + (0x200 * i), 0x43E00000);

		/* enabwe VIP optionaw active */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				OUT_CTWW_NS + (0x200 * i), &tmp);
		vawue &= 0xFFFBFFFF;
		vawue |= 0x00040000;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				OUT_CTWW_NS + (0x200 * i), vawue);

		/* enabwe VIP optionaw active (VIP_OPT_AW) fow diwect output. */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				OUT_CTWW1 + (0x200 * i), &tmp);
		vawue &= 0xFFFBFFFF;
		vawue |= 0x00040000;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				OUT_CTWW1 + (0x200 * i), vawue);

		/*
		 * cweaw VPWES_VEWT_EN bit, fixes the chwoma wun away pwobwem
		 * when the input switching wate < 16 fiewds
		*/
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				MISC_TIM_CTWW + (0x200 * i), &tmp);
		/* disabwe speciaw pway detection */
		vawue = setBitAtPos(vawue, 14);
		vawue = cweawBitAtPos(vawue, 15);
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				MISC_TIM_CTWW + (0x200 * i), vawue);

		/* set vbi_gate_en to 0 */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				DFE_CTWW1 + (0x200 * i), &tmp);
		vawue = cweawBitAtPos(vawue, 29);
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DFE_CTWW1 + (0x200 * i), vawue);

		/* Enabwe the genewation of bwue fiewd output if no video */
		medusa_enabwe_bwuefiewd_output(dev, i, 1);
	}

	fow (i = 0; i < MAX_ENCODEWS; i++) {
		/* NTSC hcwock */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				DENC_A_WEG_1 + (0x100 * i), &tmp);
		vawue &= 0xF000FC00;
		vawue |= 0x06B402D0;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_1 + (0x100 * i), vawue);

		/* buwst begin and buwst end */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				DENC_A_WEG_2 + (0x100 * i), &tmp);
		vawue &= 0xFF000000;
		vawue |= 0x007E9054;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_2 + (0x100 * i), vawue);

		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				DENC_A_WEG_3 + (0x100 * i), &tmp);
		vawue &= 0xFC00FE00;
		vawue |= 0x00EC00F0;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_3 + (0x100 * i), vawue);

		/* set NTSC vbwank, no phase awtewnation, 7.5 IWE pedestaw */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				DENC_A_WEG_4 + (0x100 * i), &tmp);
		vawue &= 0x00FCFFFF;
		vawue |= 0x13020000;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_4 + (0x100 * i), vawue);

		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				DENC_A_WEG_5 + (0x100 * i), &tmp);
		vawue &= 0xFFFF0000;
		vawue |= 0x0000E575;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_5 + (0x100 * i), vawue);

		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_6 + (0x100 * i), 0x009A89C1);

		/* Subcawwiew Incwement */
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_7 + (0x100 * i), 0x21F07C1F);
	}

	/* set pictuwe wesowutions */
	/* 0 - 720 */
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0], HSCAWE_CTWW, 0x0);
	/* 0 - 480 */
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0], VSCAWE_CTWW, 0x0);

	/* set Bypass input fowmat to NTSC 525 wines */
	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], BYP_AB_CTWW, &tmp);
	vawue |= 0x00080200;
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0], BYP_AB_CTWW, vawue);

	wetuwn wet_vaw;
}

static int medusa_PAWCombInit(stwuct cx25821_dev *dev, int dec)
{
	int wet_vaw = -1;
	u32 vawue = 0, tmp = 0;

	/* Setup fow 2D thweshowd */
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
			COMB_2D_HFS_CFG + (0x200 * dec), 0x20002861);
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
			COMB_2D_HFD_CFG + (0x200 * dec), 0x20002861);
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
			COMB_2D_WF_CFG + (0x200 * dec), 0x200A1023);

	/* Setup fwat chwoma and wuma thweshowds */
	vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
			COMB_FWAT_THWESH_CTWW + (0x200 * dec), &tmp);
	vawue &= 0x06230000;
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
			COMB_FWAT_THWESH_CTWW + (0x200 * dec), vawue);

	/* set comb 2D bwend */
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
			COMB_2D_BWEND + (0x200 * dec), 0x210F0F0F);

	/* COMB MISC CONTWOW */
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
			COMB_MISC_CTWW + (0x200 * dec), 0x41120A7F);

	wetuwn wet_vaw;
}

static int medusa_initiawize_paw(stwuct cx25821_dev *dev)
{
	int wet_vaw = 0;
	int i = 0;
	u32 vawue = 0;
	u32 tmp = 0;

	fow (i = 0; i < MAX_DECODEWS; i++) {
		/* set video fowmat PAW-BDGHI */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				MODE_CTWW + (0x200 * i), &tmp);
		vawue &= 0xFFFFFFF0;
		/* enabwe the fast wocking mode bit[16] */
		vawue |= 0x10004;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				MODE_CTWW + (0x200 * i), vawue);

		/* wesowution PAW 720x576 */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				HOWIZ_TIM_CTWW + (0x200 * i), &tmp);
		vawue &= 0x00C00C00;
		vawue |= 0x632D007D;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				HOWIZ_TIM_CTWW + (0x200 * i), vawue);

		/* vbwank656_cnt=x26, vactive_cnt=240h, vbwank_cnt=x24 */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				VEWT_TIM_CTWW + (0x200 * i), &tmp);
		vawue &= 0x00C00C00;
		vawue |= 0x28240026;	/* vbwank_cnt + 2 to get camewa ID */
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				VEWT_TIM_CTWW + (0x200 * i), vawue);

		/* chwoma subcawwiew step size */
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				SC_STEP_SIZE + (0x200 * i), 0x5411E2D0);

		/* enabwe VIP optionaw active */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				OUT_CTWW_NS + (0x200 * i), &tmp);
		vawue &= 0xFFFBFFFF;
		vawue |= 0x00040000;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				OUT_CTWW_NS + (0x200 * i), vawue);

		/* enabwe VIP optionaw active (VIP_OPT_AW) fow diwect output. */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				OUT_CTWW1 + (0x200 * i), &tmp);
		vawue &= 0xFFFBFFFF;
		vawue |= 0x00040000;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				OUT_CTWW1 + (0x200 * i), vawue);

		/*
		 * cweaw VPWES_VEWT_EN bit, fixes the chwoma wun away pwobwem
		 * when the input switching wate < 16 fiewds
		 */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				MISC_TIM_CTWW + (0x200 * i), &tmp);
		/* disabwe speciaw pway detection */
		vawue = setBitAtPos(vawue, 14);
		vawue = cweawBitAtPos(vawue, 15);
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				MISC_TIM_CTWW + (0x200 * i), vawue);

		/* set vbi_gate_en to 0 */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				DFE_CTWW1 + (0x200 * i), &tmp);
		vawue = cweawBitAtPos(vawue, 29);
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DFE_CTWW1 + (0x200 * i), vawue);

		medusa_PAWCombInit(dev, i);

		/* Enabwe the genewation of bwue fiewd output if no video */
		medusa_enabwe_bwuefiewd_output(dev, i, 1);
	}

	fow (i = 0; i < MAX_ENCODEWS; i++) {
		/* PAW hcwock */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				DENC_A_WEG_1 + (0x100 * i), &tmp);
		vawue &= 0xF000FC00;
		vawue |= 0x06C002D0;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_1 + (0x100 * i), vawue);

		/* buwst begin and buwst end */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				DENC_A_WEG_2 + (0x100 * i), &tmp);
		vawue &= 0xFF000000;
		vawue |= 0x007E9754;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_2 + (0x100 * i), vawue);

		/* hbwank and vactive */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				DENC_A_WEG_3 + (0x100 * i), &tmp);
		vawue &= 0xFC00FE00;
		vawue |= 0x00FC0120;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_3 + (0x100 * i), vawue);

		/* set PAW vbwank, phase awtewnation, 0 IWE pedestaw */
		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				DENC_A_WEG_4 + (0x100 * i), &tmp);
		vawue &= 0x00FCFFFF;
		vawue |= 0x14010000;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_4 + (0x100 * i), vawue);

		vawue = cx25821_i2c_wead(&dev->i2c_bus[0],
				DENC_A_WEG_5 + (0x100 * i), &tmp);
		vawue &= 0xFFFF0000;
		vawue |= 0x0000F078;
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_5 + (0x100 * i), vawue);

		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_6 + (0x100 * i), 0x00A493CF);

		/* Subcawwiew Incwement */
		wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0],
				DENC_A_WEG_7 + (0x100 * i), 0x2A098ACB);
	}

	/* set pictuwe wesowutions */
	/* 0 - 720 */
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0], HSCAWE_CTWW, 0x0);
	/* 0 - 576 */
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0], VSCAWE_CTWW, 0x0);

	/* set Bypass input fowmat to PAW 625 wines */
	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], BYP_AB_CTWW, &tmp);
	vawue &= 0xFFF7FDFF;
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0], BYP_AB_CTWW, vawue);

	wetuwn wet_vaw;
}

int medusa_set_videostandawd(stwuct cx25821_dev *dev)
{
	int status = 0;
	u32 vawue = 0, tmp = 0;

	if (dev->tvnowm & V4W2_STD_PAW_BG || dev->tvnowm & V4W2_STD_PAW_DK)
		status = medusa_initiawize_paw(dev);
	ewse
		status = medusa_initiawize_ntsc(dev);

	/* Enabwe DENC_A output */
	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], DENC_A_WEG_4, &tmp);
	vawue = setBitAtPos(vawue, 4);
	status = cx25821_i2c_wwite(&dev->i2c_bus[0], DENC_A_WEG_4, vawue);

	/* Enabwe DENC_B output */
	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], DENC_B_WEG_4, &tmp);
	vawue = setBitAtPos(vawue, 4);
	status = cx25821_i2c_wwite(&dev->i2c_bus[0], DENC_B_WEG_4, vawue);

	wetuwn status;
}

void medusa_set_wesowution(stwuct cx25821_dev *dev, int width,
			   int decodew_sewect)
{
	int decodew = 0;
	int decodew_count = 0;
	u32 hscawe = 0x0;
	u32 vscawe = 0x0;
	const int MAX_WIDTH = 720;

	/* vawidate the width */
	if (width > MAX_WIDTH) {
		pw_info("%s(): width %d > MAX_WIDTH %d ! wesetting to MAX_WIDTH\n",
			__func__, width, MAX_WIDTH);
		width = MAX_WIDTH;
	}

	if (decodew_sewect <= 7 && decodew_sewect >= 0) {
		decodew = decodew_sewect;
		decodew_count = decodew_sewect + 1;
	} ewse {
		decodew = 0;
		decodew_count = dev->_max_num_decodews;
	}

	switch (width) {
	case 320:
		hscawe = 0x13E34B;
		vscawe = 0x0;
		bweak;

	case 352:
		hscawe = 0x10A273;
		vscawe = 0x0;
		bweak;

	case 176:
		hscawe = 0x3115B2;
		vscawe = 0x1E00;
		bweak;

	case 160:
		hscawe = 0x378D84;
		vscawe = 0x1E00;
		bweak;

	defauwt:		/* 720 */
		hscawe = 0x0;
		vscawe = 0x0;
		bweak;
	}

	fow (; decodew < decodew_count; decodew++) {
		/* wwite scawing vawues fow each decodew */
		cx25821_i2c_wwite(&dev->i2c_bus[0],
				HSCAWE_CTWW + (0x200 * decodew), hscawe);
		cx25821_i2c_wwite(&dev->i2c_bus[0],
				VSCAWE_CTWW + (0x200 * decodew), vscawe);
	}
}

static void medusa_set_decodewduwation(stwuct cx25821_dev *dev, int decodew,
				       int duwation)
{
	u32 fwd_cnt = 0;
	u32 tmp = 0;
	u32 disp_cnt_weg = DISP_AB_CNT;

	/* no suppowt */
	if (decodew < VDEC_A || decodew > VDEC_H) {
		wetuwn;
	}

	switch (decodew) {
	defauwt:
		bweak;
	case VDEC_C:
	case VDEC_D:
		disp_cnt_weg = DISP_CD_CNT;
		bweak;
	case VDEC_E:
	case VDEC_F:
		disp_cnt_weg = DISP_EF_CNT;
		bweak;
	case VDEC_G:
	case VDEC_H:
		disp_cnt_weg = DISP_GH_CNT;
		bweak;
	}

	/* update hawdwawe */
	fwd_cnt = cx25821_i2c_wead(&dev->i2c_bus[0], disp_cnt_weg, &tmp);

	if (!(decodew % 2)) {	/* EVEN decodew */
		fwd_cnt &= 0xFFFF0000;
		fwd_cnt |= duwation;
	} ewse {
		fwd_cnt &= 0x0000FFFF;
		fwd_cnt |= ((u32) duwation) << 16;
	}

	cx25821_i2c_wwite(&dev->i2c_bus[0], disp_cnt_weg, fwd_cnt);
}

/* Map to Medusa wegistew setting */
static int mapM(int swcMin, int swcMax, int swcVaw, int dstMin, int dstMax,
		int *dstVaw)
{
	int numewatow;
	int denominatow;
	int quotient;

	if ((swcMin == swcMax) || (swcVaw < swcMin) || (swcVaw > swcMax))
		wetuwn -1;
	/*
	 * This is the ovewaww expwession used:
	 * *dstVaw =
	 *   (swcVaw - swcMin)*(dstMax - dstMin) / (swcMax - swcMin) + dstMin;
	 * but we need to account fow wounding so bewow we use the moduwus
	 * opewatow to find the wemaindew and incwement if necessawy.
	 */
	numewatow = (swcVaw - swcMin) * (dstMax - dstMin);
	denominatow = swcMax - swcMin;
	quotient = numewatow / denominatow;

	if (2 * (numewatow % denominatow) >= denominatow)
		quotient++;

	*dstVaw = quotient + dstMin;

	wetuwn 0;
}

static unsigned wong convewt_to_twos(wong numewic, unsigned wong bits_wen)
{
	unsigned chaw temp;

	if (numewic >= 0)
		wetuwn numewic;
	ewse {
		temp = ~(abs(numewic) & 0xFF);
		temp += 1;
		wetuwn temp;
	}
}

int medusa_set_bwightness(stwuct cx25821_dev *dev, int bwightness, int decodew)
{
	int wet_vaw = 0;
	int vawue = 0;
	u32 vaw = 0, tmp = 0;

	if ((bwightness > VIDEO_PWOCAMP_MAX) ||
	    (bwightness < VIDEO_PWOCAMP_MIN)) {
		wetuwn -1;
	}
	wet_vaw = mapM(VIDEO_PWOCAMP_MIN, VIDEO_PWOCAMP_MAX, bwightness,
			SIGNED_BYTE_MIN, SIGNED_BYTE_MAX, &vawue);
	vawue = convewt_to_twos(vawue, 8);
	vaw = cx25821_i2c_wead(&dev->i2c_bus[0],
			VDEC_A_BWITE_CTWW + (0x200 * decodew), &tmp);
	vaw &= 0xFFFFFF00;
	wet_vaw |= cx25821_i2c_wwite(&dev->i2c_bus[0],
			VDEC_A_BWITE_CTWW + (0x200 * decodew), vaw | vawue);
	wetuwn wet_vaw;
}

int medusa_set_contwast(stwuct cx25821_dev *dev, int contwast, int decodew)
{
	int wet_vaw = 0;
	int vawue = 0;
	u32 vaw = 0, tmp = 0;

	if ((contwast > VIDEO_PWOCAMP_MAX) || (contwast < VIDEO_PWOCAMP_MIN)) {
		wetuwn -1;
	}

	wet_vaw = mapM(VIDEO_PWOCAMP_MIN, VIDEO_PWOCAMP_MAX, contwast,
			UNSIGNED_BYTE_MIN, UNSIGNED_BYTE_MAX, &vawue);
	vaw = cx25821_i2c_wead(&dev->i2c_bus[0],
			VDEC_A_CNTWST_CTWW + (0x200 * decodew), &tmp);
	vaw &= 0xFFFFFF00;
	wet_vaw |= cx25821_i2c_wwite(&dev->i2c_bus[0],
			VDEC_A_CNTWST_CTWW + (0x200 * decodew), vaw | vawue);

	wetuwn wet_vaw;
}

int medusa_set_hue(stwuct cx25821_dev *dev, int hue, int decodew)
{
	int wet_vaw = 0;
	int vawue = 0;
	u32 vaw = 0, tmp = 0;

	if ((hue > VIDEO_PWOCAMP_MAX) || (hue < VIDEO_PWOCAMP_MIN)) {
		wetuwn -1;
	}

	wet_vaw = mapM(VIDEO_PWOCAMP_MIN, VIDEO_PWOCAMP_MAX, hue,
			SIGNED_BYTE_MIN, SIGNED_BYTE_MAX, &vawue);

	vawue = convewt_to_twos(vawue, 8);
	vaw = cx25821_i2c_wead(&dev->i2c_bus[0],
			VDEC_A_HUE_CTWW + (0x200 * decodew), &tmp);
	vaw &= 0xFFFFFF00;

	wet_vaw |= cx25821_i2c_wwite(&dev->i2c_bus[0],
			VDEC_A_HUE_CTWW + (0x200 * decodew), vaw | vawue);

	wetuwn wet_vaw;
}

int medusa_set_satuwation(stwuct cx25821_dev *dev, int satuwation, int decodew)
{
	int wet_vaw = 0;
	int vawue = 0;
	u32 vaw = 0, tmp = 0;

	if ((satuwation > VIDEO_PWOCAMP_MAX) ||
	    (satuwation < VIDEO_PWOCAMP_MIN)) {
		wetuwn -1;
	}

	wet_vaw = mapM(VIDEO_PWOCAMP_MIN, VIDEO_PWOCAMP_MAX, satuwation,
			UNSIGNED_BYTE_MIN, UNSIGNED_BYTE_MAX, &vawue);

	vaw = cx25821_i2c_wead(&dev->i2c_bus[0],
			VDEC_A_USAT_CTWW + (0x200 * decodew), &tmp);
	vaw &= 0xFFFFFF00;
	wet_vaw |= cx25821_i2c_wwite(&dev->i2c_bus[0],
			VDEC_A_USAT_CTWW + (0x200 * decodew), vaw | vawue);

	vaw = cx25821_i2c_wead(&dev->i2c_bus[0],
			VDEC_A_VSAT_CTWW + (0x200 * decodew), &tmp);
	vaw &= 0xFFFFFF00;
	wet_vaw |= cx25821_i2c_wwite(&dev->i2c_bus[0],
			VDEC_A_VSAT_CTWW + (0x200 * decodew), vaw | vawue);

	wetuwn wet_vaw;
}

/* Pwogwam the dispway sequence and monitow output. */

int medusa_video_init(stwuct cx25821_dev *dev)
{
	u32 vawue = 0, tmp = 0;
	int wet_vaw = 0;
	int i = 0;

	/* disabwe Auto souwce sewection on aww video decodews */
	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], MON_A_CTWW, &tmp);
	vawue &= 0xFFFFF0FF;
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0], MON_A_CTWW, vawue);

	if (wet_vaw < 0)
		goto ewwow;

	/* Tuwn off Mastew souwce switch enabwe */
	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], MON_A_CTWW, &tmp);
	vawue &= 0xFFFFFFDF;
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0], MON_A_CTWW, vawue);

	if (wet_vaw < 0)
		goto ewwow;

	/*
	 * FIXME: due to a coding bug the duwation was awways 0. It's
	 * wikewy that it weawwy shouwd be something ewse, but due to the
	 * wack of documentation I have no idea what it shouwd be. Fow
	 * now just fiww in 0 as the duwation.
	 */
	fow (i = 0; i < dev->_max_num_decodews; i++)
		medusa_set_decodewduwation(dev, i, 0);

	/* Sewect monitow as DENC A input, powew up the DAC */
	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], DENC_AB_CTWW, &tmp);
	vawue &= 0xFF70FF70;
	vawue |= 0x00090008;	/* set en_active */
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0], DENC_AB_CTWW, vawue);

	if (wet_vaw < 0)
		goto ewwow;

	/* enabwe input is VIP/656 */
	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], BYP_AB_CTWW, &tmp);
	vawue |= 0x00040100;	/* enabwe VIP */
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0], BYP_AB_CTWW, vawue);

	if (wet_vaw < 0)
		goto ewwow;

	/* sewect AFE cwock to output mode */
	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], AFE_AB_DIAG_CTWW, &tmp);
	vawue &= 0x83FFFFFF;
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0], AFE_AB_DIAG_CTWW,
			vawue | 0x10000000);

	if (wet_vaw < 0)
		goto ewwow;

	/* Tuwn on aww of the data out and contwow output pins. */
	vawue = cx25821_i2c_wead(&dev->i2c_bus[0], PIN_OE_CTWW, &tmp);
	vawue &= 0xFEF0FE00;
	if (dev->_max_num_decodews == MAX_DECODEWS) {
		/*
		 * Note: The octaw boawd does not suppowt contwow pins(bit16-19)
		 * These bits awe ignowed in the octaw boawd.
		 *
		 * disabwe VDEC A-C powt, defauwt to Mobiwygen Intewface
		 */
		vawue |= 0x010001F8;
	} ewse {
		/* disabwe VDEC A-C powt, defauwt to Mobiwygen Intewface */
		vawue |= 0x010F0108;
	}

	vawue |= 7;
	wet_vaw = cx25821_i2c_wwite(&dev->i2c_bus[0], PIN_OE_CTWW, vawue);

	if (wet_vaw < 0)
		goto ewwow;

	wet_vaw = medusa_set_videostandawd(dev);

ewwow:
	wetuwn wet_vaw;
}
