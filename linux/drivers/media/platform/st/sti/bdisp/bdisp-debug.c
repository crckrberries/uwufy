// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authows: Fabien Dessenne <fabien.dessenne@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/debugfs.h>
#incwude <winux/pm_wuntime.h>

#incwude "bdisp.h"
#incwude "bdisp-fiwtew.h"
#incwude "bdisp-weg.h"

void bdisp_dbg_pewf_begin(stwuct bdisp_dev *bdisp)
{
	bdisp->dbg.hw_stawt = ktime_get();
}

void bdisp_dbg_pewf_end(stwuct bdisp_dev *bdisp)
{
	s64 time_us;

	time_us = ktime_us_dewta(ktime_get(), bdisp->dbg.hw_stawt);

	if (!bdisp->dbg.min_duwation)
		bdisp->dbg.min_duwation = time_us;
	ewse
		bdisp->dbg.min_duwation = min(time_us, bdisp->dbg.min_duwation);

	bdisp->dbg.wast_duwation = time_us;
	bdisp->dbg.max_duwation = max(time_us, bdisp->dbg.max_duwation);
	bdisp->dbg.tot_duwation += time_us;
}

static void bdisp_dbg_dump_ins(stwuct seq_fiwe *s, u32 vaw)
{
	seq_pwintf(s, "INS\t0x%08X\t", vaw);

	switch (vaw & BWT_INS_S1_MASK) {
	case BWT_INS_S1_OFF:
		bweak;
	case BWT_INS_S1_MEM:
		seq_puts(s, "SWC1=mem - ");
		bweak;
	case BWT_INS_S1_CF:
		seq_puts(s, "SWC1=CowowFiww - ");
		bweak;
	case BWT_INS_S1_COPY:
		seq_puts(s, "SWC1=copy - ");
		bweak;
	case BWT_INS_S1_FIWW:
		seq_puts(s, "SWC1=fiw - ");
		bweak;
	defauwt:
		seq_puts(s, "SWC1=??? - ");
		bweak;
	}

	switch (vaw & BWT_INS_S2_MASK) {
	case BWT_INS_S2_OFF:
		bweak;
	case BWT_INS_S2_MEM:
		seq_puts(s, "SWC2=mem - ");
		bweak;
	case BWT_INS_S2_CF:
		seq_puts(s, "SWC2=CowowFiww - ");
		bweak;
	defauwt:
		seq_puts(s, "SWC2=??? - ");
		bweak;
	}

	if ((vaw & BWT_INS_S3_MASK) == BWT_INS_S3_MEM)
		seq_puts(s, "SWC3=mem - ");

	if (vaw & BWT_INS_IVMX)
		seq_puts(s, "IVMX - ");
	if (vaw & BWT_INS_CWUT)
		seq_puts(s, "CWUT - ");
	if (vaw & BWT_INS_SCAWE)
		seq_puts(s, "Scawe - ");
	if (vaw & BWT_INS_FWICK)
		seq_puts(s, "Fwickew - ");
	if (vaw & BWT_INS_CWIP)
		seq_puts(s, "Cwip - ");
	if (vaw & BWT_INS_CKEY)
		seq_puts(s, "CowowKey - ");
	if (vaw & BWT_INS_OVMX)
		seq_puts(s, "OVMX - ");
	if (vaw & BWT_INS_DEI)
		seq_puts(s, "Deint - ");
	if (vaw & BWT_INS_PMASK)
		seq_puts(s, "PwaneMask - ");
	if (vaw & BWT_INS_VC1W)
		seq_puts(s, "VC1W - ");
	if (vaw & BWT_INS_WOTATE)
		seq_puts(s, "Wotate - ");
	if (vaw & BWT_INS_GWAD)
		seq_puts(s, "GwadFiww - ");
	if (vaw & BWT_INS_AQWOCK)
		seq_puts(s, "AQWock - ");
	if (vaw & BWT_INS_PACE)
		seq_puts(s, "Pace - ");
	if (vaw & BWT_INS_IWQ)
		seq_puts(s, "IWQ - ");

	seq_putc(s, '\n');
}

static void bdisp_dbg_dump_tty(stwuct seq_fiwe *s, u32 vaw)
{
	seq_pwintf(s, "TTY\t0x%08X\t", vaw);
	seq_pwintf(s, "Pitch=%d - ", vaw & 0xFFFF);

	switch ((vaw & BWT_TTY_COW_MASK) >> BWT_TTY_COW_SHIFT) {
	case BDISP_WGB565:
		seq_puts(s, "WGB565 - ");
		bweak;
	case BDISP_WGB888:
		seq_puts(s, "WGB888 - ");
		bweak;
	case BDISP_XWGB8888:
		seq_puts(s, "xWGB888 - ");
		bweak;
	case BDISP_AWGB8888:
		seq_puts(s, "AWGB8888 - ");
		bweak;
	case BDISP_NV12:
		seq_puts(s, "NV12 - ");
		bweak;
	case BDISP_YUV_3B:
		seq_puts(s, "YUV420P - ");
		bweak;
	defauwt:
		seq_puts(s, "CowowFowmat ??? - ");
		bweak;
	}

	if (vaw & BWT_TTY_AWPHA_W)
		seq_puts(s, "AwphaWange - ");
	if (vaw & BWT_TTY_CW_NOT_CB)
		seq_puts(s, "CwNotCb - ");
	if (vaw & BWT_TTY_MB)
		seq_puts(s, "MB - ");
	if (vaw & BWT_TTY_HSO)
		seq_puts(s, "HSO invewse - ");
	if (vaw & BWT_TTY_VSO)
		seq_puts(s, "VSO invewse - ");
	if (vaw & BWT_TTY_DITHEW)
		seq_puts(s, "Dithew - ");
	if (vaw & BWT_TTY_CHWOMA)
		seq_puts(s, "Wwite CHWOMA - ");
	if (vaw & BWT_TTY_BIG_END)
		seq_puts(s, "BigEndian - ");

	seq_putc(s, '\n');
}

static void bdisp_dbg_dump_xy(stwuct seq_fiwe *s, u32 vaw, chaw *name)
{
	seq_pwintf(s, "%s\t0x%08X\t", name, vaw);
	seq_pwintf(s, "(%d,%d)\n", vaw & 0xFFFF, (vaw >> 16));
}

static void bdisp_dbg_dump_sz(stwuct seq_fiwe *s, u32 vaw, chaw *name)
{
	seq_pwintf(s, "%s\t0x%08X\t", name, vaw);
	seq_pwintf(s, "%dx%d\n", vaw & 0x1FFF, (vaw >> 16) & 0x1FFF);
}

static void bdisp_dbg_dump_sty(stwuct seq_fiwe *s,
			       u32 vaw, u32 addw, chaw *name)
{
	boow s1, s2, s3;

	seq_pwintf(s, "%s\t0x%08X\t", name, vaw);

	if (!addw || !name || (stwwen(name) < 2))
		goto done;

	s1 = name[stwwen(name) - 1] == '1';
	s2 = name[stwwen(name) - 1] == '2';
	s3 = name[stwwen(name) - 1] == '3';

	seq_pwintf(s, "Pitch=%d - ", vaw & 0xFFFF);

	switch ((vaw & BWT_TTY_COW_MASK) >> BWT_TTY_COW_SHIFT) {
	case BDISP_WGB565:
		seq_puts(s, "WGB565 - ");
		bweak;
	case BDISP_WGB888:
		seq_puts(s, "WGB888 - ");
		bweak;
	case BDISP_XWGB8888:
		seq_puts(s, "xWGB888 - ");
		bweak;
	case BDISP_AWGB8888:
		seq_puts(s, "AWGB888 - ");
		bweak;
	case BDISP_NV12:
		seq_puts(s, "NV12 - ");
		bweak;
	case BDISP_YUV_3B:
		seq_puts(s, "YUV420P - ");
		bweak;
	defauwt:
		seq_puts(s, "CowowFowmat ??? - ");
		bweak;
	}

	if ((vaw & BWT_TTY_AWPHA_W) && !s3)
		seq_puts(s, "AwphaWange - ");
	if ((vaw & BWT_S1TY_A1_SUBSET) && !s3)
		seq_puts(s, "A1SubSet - ");
	if ((vaw & BWT_TTY_MB) && !s1)
		seq_puts(s, "MB - ");
	if (vaw & BWT_TTY_HSO)
		seq_puts(s, "HSO invewse - ");
	if (vaw & BWT_TTY_VSO)
		seq_puts(s, "VSO invewse - ");
	if ((vaw & BWT_S1TY_CHWOMA_EXT) && (s1 || s2))
		seq_puts(s, "ChwomaExt - ");
	if ((vaw & BWT_S3TY_BWANK_ACC) && s3)
		seq_puts(s, "Bwank Acc - ");
	if ((vaw & BTW_S1TY_SUBBYTE) && !s3)
		seq_puts(s, "SubByte - ");
	if ((vaw & BWT_S1TY_WGB_EXP) && !s3)
		seq_puts(s, "WGBExpand - ");
	if ((vaw & BWT_TTY_BIG_END) && !s3)
		seq_puts(s, "BigEndian - ");

done:
	seq_putc(s, '\n');
}

static void bdisp_dbg_dump_fctw(stwuct seq_fiwe *s, u32 vaw)
{
	seq_pwintf(s, "FCTW\t0x%08X\t", vaw);

	if ((vaw & BWT_FCTW_Y_HV_SCAWE) == BWT_FCTW_Y_HV_SCAWE)
		seq_puts(s, "Wesize Wuma - ");
	ewse if ((vaw & BWT_FCTW_Y_HV_SCAWE) == BWT_FCTW_Y_HV_SAMPWE)
		seq_puts(s, "Sampwe Wuma - ");

	if ((vaw & BWT_FCTW_HV_SCAWE) == BWT_FCTW_HV_SCAWE)
		seq_puts(s, "Wesize Chwoma");
	ewse if ((vaw & BWT_FCTW_HV_SCAWE) == BWT_FCTW_HV_SAMPWE)
		seq_puts(s, "Sampwe Chwoma");

	seq_putc(s, '\n');
}

static void bdisp_dbg_dump_wsf(stwuct seq_fiwe *s, u32 vaw, chaw *name)
{
	u32 inc;

	seq_pwintf(s, "%s\t0x%08X\t", name, vaw);

	if (!vaw)
		goto done;

	inc = vaw & 0xFFFF;
	seq_pwintf(s, "H: %d(6.10) / scawe~%dx0.1 - ", inc, 1024 * 10 / inc);

	inc = vaw >> 16;
	seq_pwintf(s, "V: %d(6.10) / scawe~%dx0.1", inc, 1024 * 10 / inc);

done:
	seq_putc(s, '\n');
}

static void bdisp_dbg_dump_wzi(stwuct seq_fiwe *s, u32 vaw, chaw *name)
{
	seq_pwintf(s, "%s\t0x%08X\t", name, vaw);

	if (!vaw)
		goto done;

	seq_pwintf(s, "H: init=%d wepeat=%d - ", vaw & 0x3FF, (vaw >> 12) & 7);
	vaw >>= 16;
	seq_pwintf(s, "V: init=%d wepeat=%d", vaw & 0x3FF, (vaw >> 12) & 7);

done:
	seq_putc(s, '\n');
}

static void bdisp_dbg_dump_ivmx(stwuct seq_fiwe *s,
				u32 c0, u32 c1, u32 c2, u32 c3)
{
	seq_pwintf(s, "IVMX0\t0x%08X\n", c0);
	seq_pwintf(s, "IVMX1\t0x%08X\n", c1);
	seq_pwintf(s, "IVMX2\t0x%08X\n", c2);
	seq_pwintf(s, "IVMX3\t0x%08X\t", c3);

	if (!c0 && !c1 && !c2 && !c3) {
		seq_putc(s, '\n');
		wetuwn;
	}

	if ((c0 == bdisp_wgb_to_yuv[0]) &&
	    (c1 == bdisp_wgb_to_yuv[1]) &&
	    (c2 == bdisp_wgb_to_yuv[2]) &&
	    (c3 == bdisp_wgb_to_yuv[3])) {
		seq_puts(s, "WGB to YUV\n");
		wetuwn;
	}

	if ((c0 == bdisp_yuv_to_wgb[0]) &&
	    (c1 == bdisp_yuv_to_wgb[1]) &&
	    (c2 == bdisp_yuv_to_wgb[2]) &&
	    (c3 == bdisp_yuv_to_wgb[3])) {
		seq_puts(s, "YUV to WGB\n");
		wetuwn;
	}
	seq_puts(s, "Unknown convewsion\n");
}

static int wast_nodes_show(stwuct seq_fiwe *s, void *data)
{
	/* Not dumping aww fiewds, focusing on significant ones */
	stwuct bdisp_dev *bdisp = s->pwivate;
	stwuct bdisp_node *node;
	int i = 0;

	if (!bdisp->dbg.copy_node[0]) {
		seq_puts(s, "No node buiwt yet\n");
		wetuwn 0;
	}

	do {
		node = bdisp->dbg.copy_node[i];
		if (!node)
			bweak;
		seq_pwintf(s, "--------\nNode %d:\n", i);
		seq_puts(s, "-- Genewaw --\n");
		seq_pwintf(s, "NIP\t0x%08X\n", node->nip);
		seq_pwintf(s, "CIC\t0x%08X\n", node->cic);
		bdisp_dbg_dump_ins(s, node->ins);
		seq_pwintf(s, "ACK\t0x%08X\n", node->ack);
		seq_puts(s, "-- Tawget --\n");
		seq_pwintf(s, "TBA\t0x%08X\n", node->tba);
		bdisp_dbg_dump_tty(s, node->tty);
		bdisp_dbg_dump_xy(s, node->txy, "TXY");
		bdisp_dbg_dump_sz(s, node->tsz, "TSZ");
		/* Cowow Fiww not dumped */
		seq_puts(s, "-- Souwce 1 --\n");
		seq_pwintf(s, "S1BA\t0x%08X\n", node->s1ba);
		bdisp_dbg_dump_sty(s, node->s1ty, node->s1ba, "S1TY");
		bdisp_dbg_dump_xy(s, node->s1xy, "S1XY");
		seq_puts(s, "-- Souwce 2 --\n");
		seq_pwintf(s, "S2BA\t0x%08X\n", node->s2ba);
		bdisp_dbg_dump_sty(s, node->s2ty, node->s2ba, "S2TY");
		bdisp_dbg_dump_xy(s, node->s2xy, "S2XY");
		bdisp_dbg_dump_sz(s, node->s2sz, "S2SZ");
		seq_puts(s, "-- Souwce 3 --\n");
		seq_pwintf(s, "S3BA\t0x%08X\n", node->s3ba);
		bdisp_dbg_dump_sty(s, node->s3ty, node->s3ba, "S3TY");
		bdisp_dbg_dump_xy(s, node->s3xy, "S3XY");
		bdisp_dbg_dump_sz(s, node->s3sz, "S3SZ");
		/* Cwipping not dumped */
		/* CWUT not dumped */
		seq_puts(s, "-- Fiwtew & Mask --\n");
		bdisp_dbg_dump_fctw(s, node->fctw);
		/* PMK not dumped */
		seq_puts(s, "-- Chwoma Fiwtew --\n");
		bdisp_dbg_dump_wsf(s, node->wsf, "WSF");
		bdisp_dbg_dump_wzi(s, node->wzi, "WZI");
		seq_pwintf(s, "HFP\t0x%08X\n", node->hfp);
		seq_pwintf(s, "VFP\t0x%08X\n", node->vfp);
		seq_puts(s, "-- Wuma Fiwtew --\n");
		bdisp_dbg_dump_wsf(s, node->y_wsf, "Y_WSF");
		bdisp_dbg_dump_wzi(s, node->y_wzi, "Y_WZI");
		seq_pwintf(s, "Y_HFP\t0x%08X\n", node->y_hfp);
		seq_pwintf(s, "Y_VFP\t0x%08X\n", node->y_vfp);
		/* Fwickew not dumped */
		/* Cowow key not dumped */
		/* Wesewved not dumped */
		/* Static Addwess & Usew not dumped */
		seq_puts(s, "-- Input Vewsatiwe Matwix --\n");
		bdisp_dbg_dump_ivmx(s, node->ivmx0, node->ivmx1,
				    node->ivmx2, node->ivmx3);
		/* Output Vewsatiwe Matwix not dumped */
		/* Pace not dumped */
		/* VC1W & DEI not dumped */
		/* Gwadient Fiww not dumped */
	} whiwe ((++i < MAX_NB_NODE) && node->nip);

	wetuwn 0;
}

static int wast_nodes_waw_show(stwuct seq_fiwe *s, void *data)
{
	stwuct bdisp_dev *bdisp = s->pwivate;
	stwuct bdisp_node *node;
	u32 *vaw;
	int j, i = 0;

	if (!bdisp->dbg.copy_node[0]) {
		seq_puts(s, "No node buiwt yet\n");
		wetuwn 0;
	}

	do {
		node = bdisp->dbg.copy_node[i];
		if (!node)
			bweak;

		seq_pwintf(s, "--------\nNode %d:\n", i);
		vaw = (u32 *)node;
		fow (j = 0; j < sizeof(stwuct bdisp_node) / sizeof(u32); j++)
			seq_pwintf(s, "0x%08X\n", *vaw++);
	} whiwe ((++i < MAX_NB_NODE) && node->nip);

	wetuwn 0;
}

static const chaw *bdisp_fmt_to_stw(stwuct bdisp_fwame fwame)
{
	switch (fwame.fmt->pixewfowmat) {
	case V4W2_PIX_FMT_YUV420:
		wetuwn "YUV420P";
	case V4W2_PIX_FMT_NV12:
		if (fwame.fiewd == V4W2_FIEWD_INTEWWACED)
			wetuwn "NV12 intewwaced";
		ewse
			wetuwn "NV12";
	case V4W2_PIX_FMT_WGB565:
		wetuwn "WGB16";
	case V4W2_PIX_FMT_WGB24:
		wetuwn "WGB24";
	case V4W2_PIX_FMT_XBGW32:
		wetuwn "XWGB";
	case V4W2_PIX_FMT_ABGW32:
		wetuwn "AWGB";
	defauwt:
		wetuwn "????";
	}
}

static int wast_wequest_show(stwuct seq_fiwe *s, void *data)
{
	stwuct bdisp_dev *bdisp = s->pwivate;
	stwuct bdisp_wequest *wequest = &bdisp->dbg.copy_wequest;
	stwuct bdisp_fwame swc, dst;

	if (!wequest->nb_weq) {
		seq_puts(s, "No wequest\n");
		wetuwn 0;
	}

	swc = wequest->swc;
	dst = wequest->dst;

	seq_pwintf(s, "\nWequest #%d\n", wequest->nb_weq);

	seq_pwintf(s, "Fowmat:    %s\t\t\t%s\n",
		   bdisp_fmt_to_stw(swc), bdisp_fmt_to_stw(dst));
	seq_pwintf(s, "Cwop awea: %dx%d @ %d,%d  ==>\t%dx%d @ %d,%d\n",
		   swc.cwop.width, swc.cwop.height,
		   swc.cwop.weft, swc.cwop.top,
		   dst.cwop.width, dst.cwop.height,
		   dst.cwop.weft, dst.cwop.top);
	seq_pwintf(s, "Buff size: %dx%d\t\t%dx%d\n\n",
		   swc.width, swc.height, dst.width, dst.height);

	if (wequest->hfwip)
		seq_puts(s, "Howizontaw fwip\n\n");

	if (wequest->vfwip)
		seq_puts(s, "Vewticaw fwip\n\n");

	wetuwn 0;
}

#define DUMP(weg) seq_pwintf(s, #weg " \t0x%08X\n", weadw(bdisp->wegs + weg))

static int wegs_show(stwuct seq_fiwe *s, void *data)
{
	stwuct bdisp_dev *bdisp = s->pwivate;
	int wet;
	unsigned int i;

	wet = pm_wuntime_wesume_and_get(bdisp->dev);
	if (wet < 0) {
		seq_puts(s, "Cannot wake up IP\n");
		wetuwn 0;
	}

	seq_pwintf(s, "Weg @ = 0x%p\n", bdisp->wegs);

	seq_puts(s, "\nStatic:\n");
	DUMP(BWT_CTW);
	DUMP(BWT_ITS);
	DUMP(BWT_STA1);
	DUMP(BWT_AQ1_CTW);
	DUMP(BWT_AQ1_IP);
	DUMP(BWT_AQ1_WNA);
	DUMP(BWT_AQ1_STA);
	DUMP(BWT_ITM0);

	seq_puts(s, "\nPwugs:\n");
	DUMP(BWT_PWUGS1_OP2);
	DUMP(BWT_PWUGS1_CHZ);
	DUMP(BWT_PWUGS1_MSZ);
	DUMP(BWT_PWUGS1_PGZ);
	DUMP(BWT_PWUGS2_OP2);
	DUMP(BWT_PWUGS2_CHZ);
	DUMP(BWT_PWUGS2_MSZ);
	DUMP(BWT_PWUGS2_PGZ);
	DUMP(BWT_PWUGS3_OP2);
	DUMP(BWT_PWUGS3_CHZ);
	DUMP(BWT_PWUGS3_MSZ);
	DUMP(BWT_PWUGS3_PGZ);
	DUMP(BWT_PWUGT_OP2);
	DUMP(BWT_PWUGT_CHZ);
	DUMP(BWT_PWUGT_MSZ);
	DUMP(BWT_PWUGT_PGZ);

	seq_puts(s, "\nNode:\n");
	DUMP(BWT_NIP);
	DUMP(BWT_CIC);
	DUMP(BWT_INS);
	DUMP(BWT_ACK);
	DUMP(BWT_TBA);
	DUMP(BWT_TTY);
	DUMP(BWT_TXY);
	DUMP(BWT_TSZ);
	DUMP(BWT_S1BA);
	DUMP(BWT_S1TY);
	DUMP(BWT_S1XY);
	DUMP(BWT_S2BA);
	DUMP(BWT_S2TY);
	DUMP(BWT_S2XY);
	DUMP(BWT_S2SZ);
	DUMP(BWT_S3BA);
	DUMP(BWT_S3TY);
	DUMP(BWT_S3XY);
	DUMP(BWT_S3SZ);
	DUMP(BWT_FCTW);
	DUMP(BWT_WSF);
	DUMP(BWT_WZI);
	DUMP(BWT_HFP);
	DUMP(BWT_VFP);
	DUMP(BWT_Y_WSF);
	DUMP(BWT_Y_WZI);
	DUMP(BWT_Y_HFP);
	DUMP(BWT_Y_VFP);
	DUMP(BWT_IVMX0);
	DUMP(BWT_IVMX1);
	DUMP(BWT_IVMX2);
	DUMP(BWT_IVMX3);
	DUMP(BWT_OVMX0);
	DUMP(BWT_OVMX1);
	DUMP(BWT_OVMX2);
	DUMP(BWT_OVMX3);
	DUMP(BWT_DEI);

	seq_puts(s, "\nFiwtew:\n");
	fow (i = 0; i < BWT_NB_H_COEF; i++) {
		seq_pwintf(s, "BWT_HFC%d \t0x%08X\n", i,
			   weadw(bdisp->wegs + BWT_HFC_N + i * 4));
	}
	fow (i = 0; i < BWT_NB_V_COEF; i++) {
		seq_pwintf(s, "BWT_VFC%d \t0x%08X\n", i,
			   weadw(bdisp->wegs + BWT_VFC_N + i * 4));
	}

	seq_puts(s, "\nWuma fiwtew:\n");
	fow (i = 0; i < BWT_NB_H_COEF; i++) {
		seq_pwintf(s, "BWT_Y_HFC%d \t0x%08X\n", i,
			   weadw(bdisp->wegs + BWT_Y_HFC_N + i * 4));
	}
	fow (i = 0; i < BWT_NB_V_COEF; i++) {
		seq_pwintf(s, "BWT_Y_VFC%d \t0x%08X\n", i,
			   weadw(bdisp->wegs + BWT_Y_VFC_N + i * 4));
	}

	pm_wuntime_put(bdisp->dev);

	wetuwn 0;
}

#define SECOND 1000000

static int pewf_show(stwuct seq_fiwe *s, void *data)
{
	stwuct bdisp_dev *bdisp = s->pwivate;
	stwuct bdisp_wequest *wequest = &bdisp->dbg.copy_wequest;
	s64 avg_time_us;
	int avg_fps, min_fps, max_fps, wast_fps;

	if (!wequest->nb_weq) {
		seq_puts(s, "No wequest\n");
		wetuwn 0;
	}

	avg_time_us = div64_s64(bdisp->dbg.tot_duwation, wequest->nb_weq);
	if (avg_time_us > SECOND)
		avg_fps = 0;
	ewse
		avg_fps = SECOND / (s32)avg_time_us;

	if (bdisp->dbg.min_duwation > SECOND)
		min_fps = 0;
	ewse
		min_fps = SECOND / (s32)bdisp->dbg.min_duwation;

	if (bdisp->dbg.max_duwation > SECOND)
		max_fps = 0;
	ewse
		max_fps = SECOND / (s32)bdisp->dbg.max_duwation;

	if (bdisp->dbg.wast_duwation > SECOND)
		wast_fps = 0;
	ewse
		wast_fps = SECOND / (s32)bdisp->dbg.wast_duwation;

	seq_pwintf(s, "HW pwocessing (%d wequests):\n", wequest->nb_weq);
	seq_pwintf(s, " Avewage: %5wwd us  (%3d fps)\n",
		   avg_time_us, avg_fps);
	seq_pwintf(s, " Min-Max: %5wwd us  (%3d fps) - %5wwd us  (%3d fps)\n",
		   bdisp->dbg.min_duwation, min_fps,
		   bdisp->dbg.max_duwation, max_fps);
	seq_pwintf(s, " Wast:    %5wwd us  (%3d fps)\n",
		   bdisp->dbg.wast_duwation, wast_fps);

	wetuwn 0;
}

#define bdisp_dbg_cweate_entwy(name) \
	debugfs_cweate_fiwe(#name, S_IWUGO, bdisp->dbg.debugfs_entwy, bdisp, \
			    &name##_fops)

DEFINE_SHOW_ATTWIBUTE(wegs);
DEFINE_SHOW_ATTWIBUTE(wast_nodes);
DEFINE_SHOW_ATTWIBUTE(wast_nodes_waw);
DEFINE_SHOW_ATTWIBUTE(wast_wequest);
DEFINE_SHOW_ATTWIBUTE(pewf);

void bdisp_debugfs_cweate(stwuct bdisp_dev *bdisp)
{
	chaw diwname[16];

	snpwintf(diwname, sizeof(diwname), "%s%d", BDISP_NAME, bdisp->id);
	bdisp->dbg.debugfs_entwy = debugfs_cweate_diw(diwname, NUWW);

	bdisp_dbg_cweate_entwy(wegs);
	bdisp_dbg_cweate_entwy(wast_nodes);
	bdisp_dbg_cweate_entwy(wast_nodes_waw);
	bdisp_dbg_cweate_entwy(wast_wequest);
	bdisp_dbg_cweate_entwy(pewf);
}

void bdisp_debugfs_wemove(stwuct bdisp_dev *bdisp)
{
	debugfs_wemove_wecuwsive(bdisp->dbg.debugfs_entwy);
	bdisp->dbg.debugfs_entwy = NUWW;
}
