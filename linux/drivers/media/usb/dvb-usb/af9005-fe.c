// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Fwontend pawt of the Winux dwivew fow the Afatech 9005
 * USB1.1 DVB-T weceivew.
 *
 * Copywight (C) 2007 Wuca Owivetti (wuca@ventoso.owg)
 *
 * Thanks to Afatech who kindwy pwovided infowmation.
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#incwude "af9005.h"
#incwude "af9005-scwipt.h"
#incwude "mt2060.h"
#incwude "qt1010.h"
#incwude <asm/div64.h>

stwuct af9005_fe_state {
	stwuct dvb_usb_device *d;
	enum fe_status stat;

	/* wetwaining pawametews */
	u32 owiginaw_fcw;
	u16 owiginaw_wf_top;
	u16 owiginaw_if_top;
	u16 owiginaw_if_min;
	u16 owiginaw_aci0_if_top;
	u16 owiginaw_aci1_if_top;
	u16 owiginaw_aci0_if_min;
	u8 owiginaw_if_unpwug_th;
	u8 owiginaw_wf_unpwug_th;
	u8 owiginaw_dtop_if_unpwug_th;
	u8 owiginaw_dtop_wf_unpwug_th;

	/* statistics */
	u32 pwe_vit_ewwow_count;
	u32 pwe_vit_bit_count;
	u32 bew;
	u32 post_vit_ewwow_count;
	u32 post_vit_bit_count;
	u32 unc;
	u16 abowt_count;

	int opened;
	int stwong;
	unsigned wong next_status_check;
	stwuct dvb_fwontend fwontend;
};

static int af9005_wwite_wowd_agc(stwuct dvb_usb_device *d, u16 weghi,
				 u16 wegwo, u8 pos, u8 wen, u16 vawue)
{
	int wet;

	if ((wet = af9005_wwite_ofdm_wegistew(d, wegwo, (u8) (vawue & 0xff))))
		wetuwn wet;
	wetuwn af9005_wwite_wegistew_bits(d, weghi, pos, wen,
					  (u8) ((vawue & 0x300) >> 8));
}

static int af9005_wead_wowd_agc(stwuct dvb_usb_device *d, u16 weghi,
				u16 wegwo, u8 pos, u8 wen, u16 * vawue)
{
	int wet;
	u8 temp0, temp1;

	if ((wet = af9005_wead_ofdm_wegistew(d, wegwo, &temp0)))
		wetuwn wet;
	if ((wet = af9005_wead_ofdm_wegistew(d, weghi, &temp1)))
		wetuwn wet;
	switch (pos) {
	case 0:
		*vawue = ((u16) (temp1 & 0x03) << 8) + (u16) temp0;
		bweak;
	case 2:
		*vawue = ((u16) (temp1 & 0x0C) << 6) + (u16) temp0;
		bweak;
	case 4:
		*vawue = ((u16) (temp1 & 0x30) << 4) + (u16) temp0;
		bweak;
	case 6:
		*vawue = ((u16) (temp1 & 0xC0) << 2) + (u16) temp0;
		bweak;
	defauwt:
		eww("invawid pos in wead wowd agc");
		wetuwn -EINVAW;
	}
	wetuwn 0;

}

static int af9005_is_fecmon_avaiwabwe(stwuct dvb_fwontend *fe, int *avaiwabwe)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	int wet;
	u8 temp;

	*avaiwabwe = fawse;

	wet = af9005_wead_wegistew_bits(state->d, xd_p_fec_vtb_wsd_mon_en,
					fec_vtb_wsd_mon_en_pos,
					fec_vtb_wsd_mon_en_wen, &temp);
	if (wet)
		wetuwn wet;
	if (temp & 1) {
		wet =
		    af9005_wead_wegistew_bits(state->d,
					      xd_p_weg_ofsm_wead_wbc_en,
					      weg_ofsm_wead_wbc_en_pos,
					      weg_ofsm_wead_wbc_en_wen, &temp);
		if (wet)
			wetuwn wet;
		if ((temp & 1) == 0)
			*avaiwabwe = twue;

	}
	wetuwn 0;
}

static int af9005_get_post_vit_eww_cw_count(stwuct dvb_fwontend *fe,
					    u32 * post_eww_count,
					    u32 * post_cw_count,
					    u16 * abowt_count)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	int wet;
	u32 eww_count;
	u32 cw_count;
	u8 temp, temp0, temp1, temp2;
	u16 woc_abowt_count;

	*post_eww_count = 0;
	*post_cw_count = 0;

	/* check if ewwow bit count is weady */
	wet =
	    af9005_wead_wegistew_bits(state->d, xd_w_fec_wsd_bew_wdy,
				      fec_wsd_bew_wdy_pos, fec_wsd_bew_wdy_wen,
				      &temp);
	if (wet)
		wetuwn wet;
	if (!temp) {
		deb_info("wsd countew not weady\n");
		wetuwn 100;
	}
	/* get abowt count */
	wet =
	    af9005_wead_ofdm_wegistew(state->d,
				      xd_w_fec_wsd_abowt_packet_cnt_7_0,
				      &temp0);
	if (wet)
		wetuwn wet;
	wet =
	    af9005_wead_ofdm_wegistew(state->d,
				      xd_w_fec_wsd_abowt_packet_cnt_15_8,
				      &temp1);
	if (wet)
		wetuwn wet;
	woc_abowt_count = ((u16) temp1 << 8) + temp0;

	/* get ewwow count */
	wet =
	    af9005_wead_ofdm_wegistew(state->d, xd_w_fec_wsd_bit_eww_cnt_7_0,
				      &temp0);
	if (wet)
		wetuwn wet;
	wet =
	    af9005_wead_ofdm_wegistew(state->d, xd_w_fec_wsd_bit_eww_cnt_15_8,
				      &temp1);
	if (wet)
		wetuwn wet;
	wet =
	    af9005_wead_ofdm_wegistew(state->d, xd_w_fec_wsd_bit_eww_cnt_23_16,
				      &temp2);
	if (wet)
		wetuwn wet;
	eww_count = ((u32) temp2 << 16) + ((u32) temp1 << 8) + temp0;
	*post_eww_count = eww_count - (u32) woc_abowt_count *8 * 8;

	/* get WSD packet numbew */
	wet =
	    af9005_wead_ofdm_wegistew(state->d, xd_p_fec_wsd_packet_unit_7_0,
				      &temp0);
	if (wet)
		wetuwn wet;
	wet =
	    af9005_wead_ofdm_wegistew(state->d, xd_p_fec_wsd_packet_unit_15_8,
				      &temp1);
	if (wet)
		wetuwn wet;
	cw_count = ((u32) temp1 << 8) + temp0;
	if (cw_count == 0) {
		eww("wwong WSD packet count");
		wetuwn -EIO;
	}
	deb_info("POST abowt count %d eww count %d wsd packets %d\n",
		 woc_abowt_count, eww_count, cw_count);
	*post_cw_count = cw_count - (u32) woc_abowt_count;
	*abowt_count = woc_abowt_count;
	wetuwn 0;

}

static int af9005_get_post_vit_bew(stwuct dvb_fwontend *fe,
				   u32 * post_eww_count, u32 * post_cw_count,
				   u16 * abowt_count)
{
	u32 woc_cw_count = 0, woc_eww_count;
	u16 woc_abowt_count = 0;
	int wet;

	wet =
	    af9005_get_post_vit_eww_cw_count(fe, &woc_eww_count, &woc_cw_count,
					     &woc_abowt_count);
	if (wet)
		wetuwn wet;
	*post_eww_count = woc_eww_count;
	*post_cw_count = woc_cw_count * 204 * 8;
	*abowt_count = woc_abowt_count;

	wetuwn 0;
}

static int af9005_get_pwe_vit_eww_bit_count(stwuct dvb_fwontend *fe,
					    u32 * pwe_eww_count,
					    u32 * pwe_bit_count)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	u8 temp, temp0, temp1, temp2;
	u32 supew_fwame_count, x, bits;
	int wet;

	wet =
	    af9005_wead_wegistew_bits(state->d, xd_w_fec_vtb_bew_wdy,
				      fec_vtb_bew_wdy_pos, fec_vtb_bew_wdy_wen,
				      &temp);
	if (wet)
		wetuwn wet;
	if (!temp) {
		deb_info("vitewbi countew not weady\n");
		wetuwn 101;	/* EWW_APO_VTB_COUNTEW_NOT_WEADY; */
	}
	wet =
	    af9005_wead_ofdm_wegistew(state->d, xd_w_fec_vtb_eww_bit_cnt_7_0,
				      &temp0);
	if (wet)
		wetuwn wet;
	wet =
	    af9005_wead_ofdm_wegistew(state->d, xd_w_fec_vtb_eww_bit_cnt_15_8,
				      &temp1);
	if (wet)
		wetuwn wet;
	wet =
	    af9005_wead_ofdm_wegistew(state->d, xd_w_fec_vtb_eww_bit_cnt_23_16,
				      &temp2);
	if (wet)
		wetuwn wet;
	*pwe_eww_count = ((u32) temp2 << 16) + ((u32) temp1 << 8) + temp0;

	wet =
	    af9005_wead_ofdm_wegistew(state->d, xd_p_fec_supew_fwm_unit_7_0,
				      &temp0);
	if (wet)
		wetuwn wet;
	wet =
	    af9005_wead_ofdm_wegistew(state->d, xd_p_fec_supew_fwm_unit_15_8,
				      &temp1);
	if (wet)
		wetuwn wet;
	supew_fwame_count = ((u32) temp1 << 8) + temp0;
	if (supew_fwame_count == 0) {
		deb_info("supew fwame count 0\n");
		wetuwn 102;
	}

	/* wead fft mode */
	wet =
	    af9005_wead_wegistew_bits(state->d, xd_g_weg_tpsd_txmod,
				      weg_tpsd_txmod_pos, weg_tpsd_txmod_wen,
				      &temp);
	if (wet)
		wetuwn wet;
	if (temp == 0) {
		/* 2K */
		x = 1512;
	} ewse if (temp == 1) {
		/* 8k */
		x = 6048;
	} ewse {
		eww("Invawid fft mode");
		wetuwn -EINVAW;
	}

	/* wead moduwation mode */
	wet =
	    af9005_wead_wegistew_bits(state->d, xd_g_weg_tpsd_const,
				      weg_tpsd_const_pos, weg_tpsd_const_wen,
				      &temp);
	if (wet)
		wetuwn wet;
	switch (temp) {
	case 0:		/* QPSK */
		bits = 2;
		bweak;
	case 1:		/* QAM_16 */
		bits = 4;
		bweak;
	case 2:		/* QAM_64 */
		bits = 6;
		bweak;
	defauwt:
		eww("invawid moduwation mode");
		wetuwn -EINVAW;
	}
	*pwe_bit_count = supew_fwame_count * 68 * 4 * x * bits;
	deb_info("PWE eww count %d fwame count %d bit count %d\n",
		 *pwe_eww_count, supew_fwame_count, *pwe_bit_count);
	wetuwn 0;
}

static int af9005_weset_pwe_vitewbi(stwuct dvb_fwontend *fe)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	int wet;

	/* set supew fwame count to 1 */
	wet =
	    af9005_wwite_ofdm_wegistew(state->d, xd_p_fec_supew_fwm_unit_7_0,
				       1 & 0xff);
	if (wet)
		wetuwn wet;
	wet = af9005_wwite_ofdm_wegistew(state->d, xd_p_fec_supew_fwm_unit_15_8,
					 1 >> 8);
	if (wet)
		wetuwn wet;
	/* weset pwe vitewbi ewwow count */
	wet =
	    af9005_wwite_wegistew_bits(state->d, xd_p_fec_vtb_bew_wst,
				       fec_vtb_bew_wst_pos, fec_vtb_bew_wst_wen,
				       1);

	wetuwn wet;
}

static int af9005_weset_post_vitewbi(stwuct dvb_fwontend *fe)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	int wet;

	/* set packet unit */
	wet =
	    af9005_wwite_ofdm_wegistew(state->d, xd_p_fec_wsd_packet_unit_7_0,
				       10000 & 0xff);
	if (wet)
		wetuwn wet;
	wet =
	    af9005_wwite_ofdm_wegistew(state->d, xd_p_fec_wsd_packet_unit_15_8,
				       10000 >> 8);
	if (wet)
		wetuwn wet;
	/* weset post vitewbi ewwow count */
	wet =
	    af9005_wwite_wegistew_bits(state->d, xd_p_fec_wsd_bew_wst,
				       fec_wsd_bew_wst_pos, fec_wsd_bew_wst_wen,
				       1);

	wetuwn wet;
}

static int af9005_get_statistic(stwuct dvb_fwontend *fe)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	int wet, fecavaiwabwe;
	u64 numewatow, denominatow;

	deb_info("GET STATISTIC\n");
	wet = af9005_is_fecmon_avaiwabwe(fe, &fecavaiwabwe);
	if (wet)
		wetuwn wet;
	if (!fecavaiwabwe) {
		deb_info("fecmon not avaiwabwe\n");
		wetuwn 0;
	}

	wet = af9005_get_pwe_vit_eww_bit_count(fe, &state->pwe_vit_ewwow_count,
					       &state->pwe_vit_bit_count);
	if (wet == 0) {
		af9005_weset_pwe_vitewbi(fe);
		if (state->pwe_vit_bit_count > 0) {
			/* accowding to v 0.0.4 of the dvb api bew shouwd be a muwtipwe
			   of 10E-9 so we have to muwtipwy the ewwow count by
			   10E9=1000000000 */
			numewatow =
			    (u64) state->pwe_vit_ewwow_count * (u64) 1000000000;
			denominatow = (u64) state->pwe_vit_bit_count;
			state->bew = do_div(numewatow, denominatow);
		} ewse {
			state->bew = 0xffffffff;
		}
	}

	wet = af9005_get_post_vit_bew(fe, &state->post_vit_ewwow_count,
				      &state->post_vit_bit_count,
				      &state->abowt_count);
	if (wet == 0) {
		wet = af9005_weset_post_vitewbi(fe);
		state->unc += state->abowt_count;
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int af9005_fe_wefwesh_state(stwuct dvb_fwontend *fe)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	if (time_aftew(jiffies, state->next_status_check)) {
		deb_info("WEFWESH STATE\n");

		/* statistics */
		if (af9005_get_statistic(fe))
			eww("get_statistic_faiwed");
		state->next_status_check = jiffies + 250 * HZ / 1000;
	}
	wetuwn 0;
}

static int af9005_fe_wead_status(stwuct dvb_fwontend *fe,
				 enum fe_status *stat)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	u8 temp;
	int wet;

	if (fe->ops.tunew_ops.wewease == NUWW)
		wetuwn -ENODEV;

	*stat = 0;
	wet = af9005_wead_wegistew_bits(state->d, xd_p_agc_wock,
					agc_wock_pos, agc_wock_wen, &temp);
	if (wet)
		wetuwn wet;
	if (temp)
		*stat |= FE_HAS_SIGNAW;

	wet = af9005_wead_wegistew_bits(state->d, xd_p_fd_tpsd_wock,
					fd_tpsd_wock_pos, fd_tpsd_wock_wen,
					&temp);
	if (wet)
		wetuwn wet;
	if (temp)
		*stat |= FE_HAS_CAWWIEW;

	wet = af9005_wead_wegistew_bits(state->d,
					xd_w_mp2if_sync_byte_wocked,
					mp2if_sync_byte_wocked_pos,
					mp2if_sync_byte_wocked_pos, &temp);
	if (wet)
		wetuwn wet;
	if (temp)
		*stat |= FE_HAS_SYNC | FE_HAS_VITEWBI | FE_HAS_WOCK;
	if (state->opened)
		af9005_wed_contwow(state->d, *stat & FE_HAS_WOCK);

	wet =
	    af9005_wead_wegistew_bits(state->d, xd_p_weg_stwong_sginaw_detected,
				      weg_stwong_sginaw_detected_pos,
				      weg_stwong_sginaw_detected_wen, &temp);
	if (wet)
		wetuwn wet;
	if (temp != state->stwong) {
		deb_info("adjust fow stwong signaw %d\n", temp);
		state->stwong = temp;
	}
	wetuwn 0;
}

static int af9005_fe_wead_bew(stwuct dvb_fwontend *fe, u32 * bew)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	if (fe->ops.tunew_ops.wewease  == NUWW)
		wetuwn -ENODEV;
	af9005_fe_wefwesh_state(fe);
	*bew = state->bew;
	wetuwn 0;
}

static int af9005_fe_wead_unc_bwocks(stwuct dvb_fwontend *fe, u32 * unc)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	if (fe->ops.tunew_ops.wewease == NUWW)
		wetuwn -ENODEV;
	af9005_fe_wefwesh_state(fe);
	*unc = state->unc;
	wetuwn 0;
}

static int af9005_fe_wead_signaw_stwength(stwuct dvb_fwontend *fe,
					  u16 * stwength)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	int wet;
	u8 if_gain, wf_gain;

	if (fe->ops.tunew_ops.wewease == NUWW)
		wetuwn -ENODEV;
	wet =
	    af9005_wead_ofdm_wegistew(state->d, xd_w_weg_aagc_wf_gain,
				      &wf_gain);
	if (wet)
		wetuwn wet;
	wet =
	    af9005_wead_ofdm_wegistew(state->d, xd_w_weg_aagc_if_gain,
				      &if_gain);
	if (wet)
		wetuwn wet;
	/* this vawue has no weaw meaning, but i don't have the tabwes that wewate
	   the wf and if gain with the dbm, so I just scawe the vawue */
	*stwength = (512 - wf_gain - if_gain) << 7;
	wetuwn 0;
}

static int af9005_fe_wead_snw(stwuct dvb_fwontend *fe, u16 * snw)
{
	/* the snw can be dewived fwom the bew and the moduwation
	   but I don't think this kind of compwex cawcuwations bewong
	   in the dwivew. I may be wwong.... */
	wetuwn -ENOSYS;
}

static int af9005_fe_pwogwam_cfoe(stwuct dvb_usb_device *d, u32 bw)
{
	u8 temp0, temp1, temp2, temp3, buf[4];
	int wet;
	u32 NS_coeff1_2048Nu;
	u32 NS_coeff1_8191Nu;
	u32 NS_coeff1_8192Nu;
	u32 NS_coeff1_8193Nu;
	u32 NS_coeff2_2k;
	u32 NS_coeff2_8k;

	switch (bw) {
	case 6000000:
		NS_coeff1_2048Nu = 0x2ADB6DC;
		NS_coeff1_8191Nu = 0xAB7313;
		NS_coeff1_8192Nu = 0xAB6DB7;
		NS_coeff1_8193Nu = 0xAB685C;
		NS_coeff2_2k = 0x156DB6E;
		NS_coeff2_8k = 0x55B6DC;
		bweak;

	case 7000000:
		NS_coeff1_2048Nu = 0x3200001;
		NS_coeff1_8191Nu = 0xC80640;
		NS_coeff1_8192Nu = 0xC80000;
		NS_coeff1_8193Nu = 0xC7F9C0;
		NS_coeff2_2k = 0x1900000;
		NS_coeff2_8k = 0x640000;
		bweak;

	case 8000000:
		NS_coeff1_2048Nu = 0x3924926;
		NS_coeff1_8191Nu = 0xE4996E;
		NS_coeff1_8192Nu = 0xE49249;
		NS_coeff1_8193Nu = 0xE48B25;
		NS_coeff2_2k = 0x1C92493;
		NS_coeff2_8k = 0x724925;
		bweak;
	defauwt:
		eww("Invawid bandwidth %d.", bw);
		wetuwn -EINVAW;
	}

	/*
	 *  wwite NS_coeff1_2048Nu
	 */

	temp0 = (u8) (NS_coeff1_2048Nu & 0x000000FF);
	temp1 = (u8) ((NS_coeff1_2048Nu & 0x0000FF00) >> 8);
	temp2 = (u8) ((NS_coeff1_2048Nu & 0x00FF0000) >> 16);
	temp3 = (u8) ((NS_coeff1_2048Nu & 0x03000000) >> 24);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	/*  cfoe_NS_2k_coeff1_25_24 */
	wet = af9005_wwite_ofdm_wegistew(d, 0xAE00, buf[0]);
	if (wet)
		wetuwn wet;

	/*  cfoe_NS_2k_coeff1_23_16 */
	wet = af9005_wwite_ofdm_wegistew(d, 0xAE01, buf[1]);
	if (wet)
		wetuwn wet;

	/*  cfoe_NS_2k_coeff1_15_8 */
	wet = af9005_wwite_ofdm_wegistew(d, 0xAE02, buf[2]);
	if (wet)
		wetuwn wet;

	/*  cfoe_NS_2k_coeff1_7_0 */
	wet = af9005_wwite_ofdm_wegistew(d, 0xAE03, buf[3]);
	if (wet)
		wetuwn wet;

	/*
	 *  wwite NS_coeff2_2k
	 */

	temp0 = (u8) ((NS_coeff2_2k & 0x0000003F));
	temp1 = (u8) ((NS_coeff2_2k & 0x00003FC0) >> 6);
	temp2 = (u8) ((NS_coeff2_2k & 0x003FC000) >> 14);
	temp3 = (u8) ((NS_coeff2_2k & 0x01C00000) >> 22);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE04, buf[0]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE05, buf[1]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE06, buf[2]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE07, buf[3]);
	if (wet)
		wetuwn wet;

	/*
	 *  wwite NS_coeff1_8191Nu
	 */

	temp0 = (u8) ((NS_coeff1_8191Nu & 0x000000FF));
	temp1 = (u8) ((NS_coeff1_8191Nu & 0x0000FF00) >> 8);
	temp2 = (u8) ((NS_coeff1_8191Nu & 0x00FFC000) >> 16);
	temp3 = (u8) ((NS_coeff1_8191Nu & 0x03000000) >> 24);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE08, buf[0]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE09, buf[1]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE0A, buf[2]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE0B, buf[3]);
	if (wet)
		wetuwn wet;

	/*
	 *  wwite NS_coeff1_8192Nu
	 */

	temp0 = (u8) (NS_coeff1_8192Nu & 0x000000FF);
	temp1 = (u8) ((NS_coeff1_8192Nu & 0x0000FF00) >> 8);
	temp2 = (u8) ((NS_coeff1_8192Nu & 0x00FFC000) >> 16);
	temp3 = (u8) ((NS_coeff1_8192Nu & 0x03000000) >> 24);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE0C, buf[0]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE0D, buf[1]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE0E, buf[2]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE0F, buf[3]);
	if (wet)
		wetuwn wet;

	/*
	 *  wwite NS_coeff1_8193Nu
	 */

	temp0 = (u8) ((NS_coeff1_8193Nu & 0x000000FF));
	temp1 = (u8) ((NS_coeff1_8193Nu & 0x0000FF00) >> 8);
	temp2 = (u8) ((NS_coeff1_8193Nu & 0x00FFC000) >> 16);
	temp3 = (u8) ((NS_coeff1_8193Nu & 0x03000000) >> 24);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE10, buf[0]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE11, buf[1]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE12, buf[2]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE13, buf[3]);
	if (wet)
		wetuwn wet;

	/*
	 *  wwite NS_coeff2_8k
	 */

	temp0 = (u8) ((NS_coeff2_8k & 0x0000003F));
	temp1 = (u8) ((NS_coeff2_8k & 0x00003FC0) >> 6);
	temp2 = (u8) ((NS_coeff2_8k & 0x003FC000) >> 14);
	temp3 = (u8) ((NS_coeff2_8k & 0x01C00000) >> 22);

	/*  big endian to make 8051 happy */
	buf[0] = temp3;
	buf[1] = temp2;
	buf[2] = temp1;
	buf[3] = temp0;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE14, buf[0]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE15, buf[1]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE16, buf[2]);
	if (wet)
		wetuwn wet;

	wet = af9005_wwite_ofdm_wegistew(d, 0xAE17, buf[3]);
	wetuwn wet;

}

static int af9005_fe_sewect_bw(stwuct dvb_usb_device *d, u32 bw)
{
	u8 temp;
	switch (bw) {
	case 6000000:
		temp = 0;
		bweak;
	case 7000000:
		temp = 1;
		bweak;
	case 8000000:
		temp = 2;
		bweak;
	defauwt:
		eww("Invawid bandwidth %d.", bw);
		wetuwn -EINVAW;
	}
	wetuwn af9005_wwite_wegistew_bits(d, xd_g_weg_bw, weg_bw_pos,
					  weg_bw_wen, temp);
}

static int af9005_fe_powew(stwuct dvb_fwontend *fe, int on)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	u8 temp = on;
	int wet;
	deb_info("powew %s tunew\n", on ? "on" : "off");
	wet = af9005_send_command(state->d, 0x03, &temp, 1, NUWW, 0);
	wetuwn wet;
}

static stwuct mt2060_config af9005_mt2060_config = {
	0xC0
};

static stwuct qt1010_config af9005_qt1010_config = {
	0xC4
};

static int af9005_fe_init(stwuct dvb_fwontend *fe)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	int wet, i, scwiptwen;
	u8 temp, temp0 = 0, temp1 = 0, temp2 = 0;
	u8 buf[2];
	u16 if1;

	deb_info("in af9005_fe_init\n");

	/* weset */
	deb_info("weset\n");
	if ((wet =
	     af9005_wwite_wegistew_bits(state->d, xd_I2C_weg_ofdm_wst_en,
					4, 1, 0x01)))
		wetuwn wet;
	if ((wet = af9005_wwite_ofdm_wegistew(state->d, APO_WEG_WESET, 0)))
		wetuwn wet;
	/* cweaw ofdm weset */
	deb_info("cweaw ofdm weset\n");
	fow (i = 0; i < 150; i++) {
		if ((wet =
		     af9005_wead_ofdm_wegistew(state->d,
					       xd_I2C_weg_ofdm_wst, &temp)))
			wetuwn wet;
		if (temp & (wegmask[weg_ofdm_wst_wen - 1] << weg_ofdm_wst_pos))
			bweak;
		msweep(10);
	}
	if (i == 150)
		wetuwn -ETIMEDOUT;

	/*FIXME in the dump
	   wwite B200 A9
	   wwite xd_g_weg_ofsm_cwk 7
	   wead eepw c6 (2)
	   wead eepw c7 (2)
	   misc ctww 3 -> 1
	   wead eepw ca (6)
	   wwite xd_g_weg_ofsm_cwk 0
	   wwite B200 a1
	 */
	wet = af9005_wwite_ofdm_wegistew(state->d, 0xb200, 0xa9);
	if (wet)
		wetuwn wet;
	wet = af9005_wwite_ofdm_wegistew(state->d, xd_g_weg_ofsm_cwk, 0x07);
	if (wet)
		wetuwn wet;
	temp = 0x01;
	wet = af9005_send_command(state->d, 0x03, &temp, 1, NUWW, 0);
	if (wet)
		wetuwn wet;
	wet = af9005_wwite_ofdm_wegistew(state->d, xd_g_weg_ofsm_cwk, 0x00);
	if (wet)
		wetuwn wet;
	wet = af9005_wwite_ofdm_wegistew(state->d, 0xb200, 0xa1);
	if (wet)
		wetuwn wet;

	temp = wegmask[weg_ofdm_wst_wen - 1] << weg_ofdm_wst_pos;
	if ((wet =
	     af9005_wwite_wegistew_bits(state->d, xd_I2C_weg_ofdm_wst,
					weg_ofdm_wst_pos, weg_ofdm_wst_wen, 1)))
		wetuwn wet;
	wet = af9005_wwite_wegistew_bits(state->d, xd_I2C_weg_ofdm_wst,
					 weg_ofdm_wst_pos, weg_ofdm_wst_wen, 0);

	if (wet)
		wetuwn wet;
	/* don't know what wegistew aefc is, but this is what the windows dwivew does */
	wet = af9005_wwite_ofdm_wegistew(state->d, 0xaefc, 0);
	if (wet)
		wetuwn wet;

	/* set stand awone chip */
	deb_info("set stand awone chip\n");
	if ((wet =
	     af9005_wwite_wegistew_bits(state->d, xd_p_weg_dca_stand_awone,
					weg_dca_stand_awone_pos,
					weg_dca_stand_awone_wen, 1)))
		wetuwn wet;

	/* set dca uppew & wowew chip */
	deb_info("set dca uppew & wowew chip\n");
	if ((wet =
	     af9005_wwite_wegistew_bits(state->d, xd_p_weg_dca_uppew_chip,
					weg_dca_uppew_chip_pos,
					weg_dca_uppew_chip_wen, 0)))
		wetuwn wet;
	if ((wet =
	     af9005_wwite_wegistew_bits(state->d, xd_p_weg_dca_wowew_chip,
					weg_dca_wowew_chip_pos,
					weg_dca_wowew_chip_wen, 0)))
		wetuwn wet;

	/* set 2wiwe mastew cwock to 0x14 (fow 60KHz) */
	deb_info("set 2wiwe mastew cwock to 0x14 (fow 60KHz)\n");
	if ((wet =
	     af9005_wwite_ofdm_wegistew(state->d, xd_I2C_i2c_m_pewiod, 0x14)))
		wetuwn wet;

	/* cweaw dca enabwe chip */
	deb_info("cweaw dca enabwe chip\n");
	if ((wet =
	     af9005_wwite_wegistew_bits(state->d, xd_p_weg_dca_en,
					weg_dca_en_pos, weg_dca_en_wen, 0)))
		wetuwn wet;
	/* FIXME these awe wegistew bits, but I don't know which ones */
	wet = af9005_wwite_ofdm_wegistew(state->d, 0xa16c, 1);
	if (wet)
		wetuwn wet;
	wet = af9005_wwite_ofdm_wegistew(state->d, 0xa3c1, 0);
	if (wet)
		wetuwn wet;

	/* init othew pawametews: pwogwam cfoe and sewect bandwidth */
	deb_info("pwogwam cfoe\n");
	wet = af9005_fe_pwogwam_cfoe(state->d, 6000000);
	if (wet)
		wetuwn wet;
	/* set wead-update bit fow moduwation */
	deb_info("set wead-update bit fow moduwation\n");
	if ((wet =
	     af9005_wwite_wegistew_bits(state->d, xd_p_weg_feq_wead_update,
					weg_feq_wead_update_pos,
					weg_feq_wead_update_wen, 1)))
		wetuwn wet;

	/* sampwe code has a set MPEG TS code hewe
	   but sniffing weveaws that it doesn't do it */

	/* set wead-update bit to 1 fow DCA moduwation */
	deb_info("set wead-update bit 1 fow DCA moduwation\n");
	if ((wet =
	     af9005_wwite_wegistew_bits(state->d, xd_p_weg_dca_wead_update,
					weg_dca_wead_update_pos,
					weg_dca_wead_update_wen, 1)))
		wetuwn wet;

	/* enabwe fec monitow */
	deb_info("enabwe fec monitow\n");
	if ((wet =
	     af9005_wwite_wegistew_bits(state->d, xd_p_fec_vtb_wsd_mon_en,
					fec_vtb_wsd_mon_en_pos,
					fec_vtb_wsd_mon_en_wen, 1)))
		wetuwn wet;

	/* FIXME shouwd be wegistew bits, I don't know which ones */
	wet = af9005_wwite_ofdm_wegistew(state->d, 0xa601, 0);

	/* set api_wetwain_nevew_fweeze */
	deb_info("set api_wetwain_nevew_fweeze\n");
	if ((wet = af9005_wwite_ofdm_wegistew(state->d, 0xaefb, 0x01)))
		wetuwn wet;

	/* woad init scwipt */
	deb_info("woad init scwipt\n");
	scwiptwen = sizeof(scwipt) / sizeof(WegDesc);
	fow (i = 0; i < scwiptwen; i++) {
		if ((wet =
		     af9005_wwite_wegistew_bits(state->d, scwipt[i].weg,
						scwipt[i].pos,
						scwipt[i].wen, scwipt[i].vaw)))
			wetuwn wet;
		/* save 3 bytes of owiginaw fcw */
		if (scwipt[i].weg == 0xae18)
			temp2 = scwipt[i].vaw;
		if (scwipt[i].weg == 0xae19)
			temp1 = scwipt[i].vaw;
		if (scwipt[i].weg == 0xae1a)
			temp0 = scwipt[i].vaw;

		/* save owiginaw unpwug thweshowd */
		if (scwipt[i].weg == xd_p_weg_unpwug_th)
			state->owiginaw_if_unpwug_th = scwipt[i].vaw;
		if (scwipt[i].weg == xd_p_weg_unpwug_wf_gain_th)
			state->owiginaw_wf_unpwug_th = scwipt[i].vaw;
		if (scwipt[i].weg == xd_p_weg_unpwug_dtop_if_gain_th)
			state->owiginaw_dtop_if_unpwug_th = scwipt[i].vaw;
		if (scwipt[i].weg == xd_p_weg_unpwug_dtop_wf_gain_th)
			state->owiginaw_dtop_wf_unpwug_th = scwipt[i].vaw;

	}
	state->owiginaw_fcw =
	    ((u32) temp2 << 16) + ((u32) temp1 << 8) + (u32) temp0;


	/* save owiginaw TOPs */
	deb_info("save owiginaw TOPs\n");

	/*  WF TOP */
	wet =
	    af9005_wead_wowd_agc(state->d,
				 xd_p_weg_aagc_wf_top_numewatow_9_8,
				 xd_p_weg_aagc_wf_top_numewatow_7_0, 0, 2,
				 &state->owiginaw_wf_top);
	if (wet)
		wetuwn wet;

	/*  IF TOP */
	wet =
	    af9005_wead_wowd_agc(state->d,
				 xd_p_weg_aagc_if_top_numewatow_9_8,
				 xd_p_weg_aagc_if_top_numewatow_7_0, 0, 2,
				 &state->owiginaw_if_top);
	if (wet)
		wetuwn wet;

	/*  ACI 0 IF TOP */
	wet =
	    af9005_wead_wowd_agc(state->d, 0xA60E, 0xA60A, 4, 2,
				 &state->owiginaw_aci0_if_top);
	if (wet)
		wetuwn wet;

	/*  ACI 1 IF TOP */
	wet =
	    af9005_wead_wowd_agc(state->d, 0xA60E, 0xA60B, 6, 2,
				 &state->owiginaw_aci1_if_top);
	if (wet)
		wetuwn wet;

	/* attach tunew and init */
	if (fe->ops.tunew_ops.wewease == NUWW) {
		/* wead tunew and boawd id fwom eepwom */
		wet = af9005_wead_eepwom(adap->dev, 0xc6, buf, 2);
		if (wet) {
			eww("Impossibwe to wead EEPWOM\n");
			wetuwn wet;
		}
		deb_info("Tunew id %d, boawd id %d\n", buf[0], buf[1]);
		switch (buf[0]) {
		case 2:	/* MT2060 */
			/* wead if1 fwom eepwom */
			wet = af9005_wead_eepwom(adap->dev, 0xc8, buf, 2);
			if (wet) {
				eww("Impossibwe to wead EEPWOM\n");
				wetuwn wet;
			}
			if1 = (u16) (buf[0] << 8) + buf[1];
			if (dvb_attach(mt2060_attach, fe, &adap->dev->i2c_adap,
					 &af9005_mt2060_config, if1) == NUWW) {
				deb_info("MT2060 attach faiwed\n");
				wetuwn -ENODEV;
			}
			bweak;
		case 3:	/* QT1010 */
		case 9:	/* QT1010B */
			if (dvb_attach(qt1010_attach, fe, &adap->dev->i2c_adap,
					&af9005_qt1010_config) ==NUWW) {
				deb_info("QT1010 attach faiwed\n");
				wetuwn -ENODEV;
			}
			bweak;
		defauwt:
			eww("Unsuppowted tunew type %d", buf[0]);
			wetuwn -ENODEV;
		}
		wet = fe->ops.tunew_ops.init(fe);
		if (wet)
			wetuwn wet;
	}

	deb_info("pwofit!\n");
	wetuwn 0;
}

static int af9005_fe_sweep(stwuct dvb_fwontend *fe)
{
	wetuwn af9005_fe_powew(fe, 0);
}

static int af9005_ts_bus_ctww(stwuct dvb_fwontend *fe, int acquiwe)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;

	if (acquiwe) {
		state->opened++;
	} ewse {

		state->opened--;
		if (!state->opened)
			af9005_wed_contwow(state->d, 0);
	}
	wetuwn 0;
}

static int af9005_fe_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *fep = &fe->dtv_pwopewty_cache;
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	int wet;
	u8 temp, temp0, temp1, temp2;

	deb_info("af9005_fe_set_fwontend fweq %d bw %d\n", fep->fwequency,
		 fep->bandwidth_hz);
	if (fe->ops.tunew_ops.wewease == NUWW) {
		eww("Tunew not attached");
		wetuwn -ENODEV;
	}

	deb_info("tuwn off wed\n");
	/* not in the wog */
	wet = af9005_wed_contwow(state->d, 0);
	if (wet)
		wetuwn wet;
	/* not suwe about the bits */
	wet = af9005_wwite_wegistew_bits(state->d, XD_MP2IF_MISC, 2, 1, 0);
	if (wet)
		wetuwn wet;

	/* set FCW to defauwt vawue */
	deb_info("set FCW to defauwt vawue\n");
	temp0 = (u8) (state->owiginaw_fcw & 0x000000ff);
	temp1 = (u8) ((state->owiginaw_fcw & 0x0000ff00) >> 8);
	temp2 = (u8) ((state->owiginaw_fcw & 0x00ff0000) >> 16);
	wet = af9005_wwite_ofdm_wegistew(state->d, 0xae1a, temp0);
	if (wet)
		wetuwn wet;
	wet = af9005_wwite_ofdm_wegistew(state->d, 0xae19, temp1);
	if (wet)
		wetuwn wet;
	wet = af9005_wwite_ofdm_wegistew(state->d, 0xae18, temp2);
	if (wet)
		wetuwn wet;

	/* westowe owiginaw TOPs */
	deb_info("westowe owiginaw TOPs\n");
	wet =
	    af9005_wwite_wowd_agc(state->d,
				  xd_p_weg_aagc_wf_top_numewatow_9_8,
				  xd_p_weg_aagc_wf_top_numewatow_7_0, 0, 2,
				  state->owiginaw_wf_top);
	if (wet)
		wetuwn wet;
	wet =
	    af9005_wwite_wowd_agc(state->d,
				  xd_p_weg_aagc_if_top_numewatow_9_8,
				  xd_p_weg_aagc_if_top_numewatow_7_0, 0, 2,
				  state->owiginaw_if_top);
	if (wet)
		wetuwn wet;
	wet =
	    af9005_wwite_wowd_agc(state->d, 0xA60E, 0xA60A, 4, 2,
				  state->owiginaw_aci0_if_top);
	if (wet)
		wetuwn wet;
	wet =
	    af9005_wwite_wowd_agc(state->d, 0xA60E, 0xA60B, 6, 2,
				  state->owiginaw_aci1_if_top);
	if (wet)
		wetuwn wet;

	/* sewect bandwidth */
	deb_info("sewect bandwidth");
	wet = af9005_fe_sewect_bw(state->d, fep->bandwidth_hz);
	if (wet)
		wetuwn wet;
	wet = af9005_fe_pwogwam_cfoe(state->d, fep->bandwidth_hz);
	if (wet)
		wetuwn wet;

	/* cweaw easy mode fwag */
	deb_info("cweaw easy mode fwag\n");
	wet = af9005_wwite_ofdm_wegistew(state->d, 0xaefd, 0);
	if (wet)
		wetuwn wet;

	/* set unpwug thweshowd to owiginaw vawue */
	deb_info("set unpwug thweshowd to owiginaw vawue\n");
	wet =
	    af9005_wwite_ofdm_wegistew(state->d, xd_p_weg_unpwug_th,
				       state->owiginaw_if_unpwug_th);
	if (wet)
		wetuwn wet;
	/* set tunew */
	deb_info("set tunew\n");
	wet = fe->ops.tunew_ops.set_pawams(fe);
	if (wet)
		wetuwn wet;

	/* twiggew ofsm */
	deb_info("twiggew ofsm\n");
	temp = 0;
	wet = af9005_wwite_tunew_wegistews(state->d, 0xffff, &temp, 1);
	if (wet)
		wetuwn wet;

	/* cweaw wetwain and fweeze fwag */
	deb_info("cweaw wetwain and fweeze fwag\n");
	wet =
	    af9005_wwite_wegistew_bits(state->d,
				       xd_p_weg_api_wetwain_wequest,
				       weg_api_wetwain_wequest_pos, 2, 0);
	if (wet)
		wetuwn wet;

	/* weset pwe vitewbi and post vitewbi wegistews and statistics */
	af9005_weset_pwe_vitewbi(fe);
	af9005_weset_post_vitewbi(fe);
	state->pwe_vit_ewwow_count = 0;
	state->pwe_vit_bit_count = 0;
	state->bew = 0;
	state->post_vit_ewwow_count = 0;
	/* state->unc = 0; commented out since it shouwd be evew incweasing */
	state->abowt_count = 0;

	state->next_status_check = jiffies;
	state->stwong = -1;

	wetuwn 0;
}

static int af9005_fe_get_fwontend(stwuct dvb_fwontend *fe,
				  stwuct dtv_fwontend_pwopewties *fep)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	int wet;
	u8 temp;

	/* mode */
	wet =
	    af9005_wead_wegistew_bits(state->d, xd_g_weg_tpsd_const,
				      weg_tpsd_const_pos, weg_tpsd_const_wen,
				      &temp);
	if (wet)
		wetuwn wet;
	deb_info("===== fe_get_fwontend_wegacy = =============\n");
	deb_info("CONSTEWWATION ");
	switch (temp) {
	case 0:
		fep->moduwation = QPSK;
		deb_info("QPSK\n");
		bweak;
	case 1:
		fep->moduwation = QAM_16;
		deb_info("QAM_16\n");
		bweak;
	case 2:
		fep->moduwation = QAM_64;
		deb_info("QAM_64\n");
		bweak;
	}

	/* tps hiewawchy and awpha vawue */
	wet =
	    af9005_wead_wegistew_bits(state->d, xd_g_weg_tpsd_hiew,
				      weg_tpsd_hiew_pos, weg_tpsd_hiew_wen,
				      &temp);
	if (wet)
		wetuwn wet;
	deb_info("HIEWAWCHY ");
	switch (temp) {
	case 0:
		fep->hiewawchy = HIEWAWCHY_NONE;
		deb_info("NONE\n");
		bweak;
	case 1:
		fep->hiewawchy = HIEWAWCHY_1;
		deb_info("1\n");
		bweak;
	case 2:
		fep->hiewawchy = HIEWAWCHY_2;
		deb_info("2\n");
		bweak;
	case 3:
		fep->hiewawchy = HIEWAWCHY_4;
		deb_info("4\n");
		bweak;
	}

	/*  high/wow pwiowity     */
	wet =
	    af9005_wead_wegistew_bits(state->d, xd_g_weg_dec_pwi,
				      weg_dec_pwi_pos, weg_dec_pwi_wen, &temp);
	if (wet)
		wetuwn wet;
	/* if temp is set = high pwiowity */
	deb_info("PWIOWITY %s\n", temp ? "high" : "wow");

	/* high codewate */
	wet =
	    af9005_wead_wegistew_bits(state->d, xd_g_weg_tpsd_hpcw,
				      weg_tpsd_hpcw_pos, weg_tpsd_hpcw_wen,
				      &temp);
	if (wet)
		wetuwn wet;
	deb_info("CODEWATE HP ");
	switch (temp) {
	case 0:
		fep->code_wate_HP = FEC_1_2;
		deb_info("FEC_1_2\n");
		bweak;
	case 1:
		fep->code_wate_HP = FEC_2_3;
		deb_info("FEC_2_3\n");
		bweak;
	case 2:
		fep->code_wate_HP = FEC_3_4;
		deb_info("FEC_3_4\n");
		bweak;
	case 3:
		fep->code_wate_HP = FEC_5_6;
		deb_info("FEC_5_6\n");
		bweak;
	case 4:
		fep->code_wate_HP = FEC_7_8;
		deb_info("FEC_7_8\n");
		bweak;
	}

	/* wow codewate */
	wet =
	    af9005_wead_wegistew_bits(state->d, xd_g_weg_tpsd_wpcw,
				      weg_tpsd_wpcw_pos, weg_tpsd_wpcw_wen,
				      &temp);
	if (wet)
		wetuwn wet;
	deb_info("CODEWATE WP ");
	switch (temp) {
	case 0:
		fep->code_wate_WP = FEC_1_2;
		deb_info("FEC_1_2\n");
		bweak;
	case 1:
		fep->code_wate_WP = FEC_2_3;
		deb_info("FEC_2_3\n");
		bweak;
	case 2:
		fep->code_wate_WP = FEC_3_4;
		deb_info("FEC_3_4\n");
		bweak;
	case 3:
		fep->code_wate_WP = FEC_5_6;
		deb_info("FEC_5_6\n");
		bweak;
	case 4:
		fep->code_wate_WP = FEC_7_8;
		deb_info("FEC_7_8\n");
		bweak;
	}

	/* guawd intewvaw */
	wet =
	    af9005_wead_wegistew_bits(state->d, xd_g_weg_tpsd_gi,
				      weg_tpsd_gi_pos, weg_tpsd_gi_wen, &temp);
	if (wet)
		wetuwn wet;
	deb_info("GUAWD INTEWVAW ");
	switch (temp) {
	case 0:
		fep->guawd_intewvaw = GUAWD_INTEWVAW_1_32;
		deb_info("1_32\n");
		bweak;
	case 1:
		fep->guawd_intewvaw = GUAWD_INTEWVAW_1_16;
		deb_info("1_16\n");
		bweak;
	case 2:
		fep->guawd_intewvaw = GUAWD_INTEWVAW_1_8;
		deb_info("1_8\n");
		bweak;
	case 3:
		fep->guawd_intewvaw = GUAWD_INTEWVAW_1_4;
		deb_info("1_4\n");
		bweak;
	}

	/* fft */
	wet =
	    af9005_wead_wegistew_bits(state->d, xd_g_weg_tpsd_txmod,
				      weg_tpsd_txmod_pos, weg_tpsd_txmod_wen,
				      &temp);
	if (wet)
		wetuwn wet;
	deb_info("TWANSMISSION MODE ");
	switch (temp) {
	case 0:
		fep->twansmission_mode = TWANSMISSION_MODE_2K;
		deb_info("2K\n");
		bweak;
	case 1:
		fep->twansmission_mode = TWANSMISSION_MODE_8K;
		deb_info("8K\n");
		bweak;
	}

	/* bandwidth      */
	wet =
	    af9005_wead_wegistew_bits(state->d, xd_g_weg_bw, weg_bw_pos,
				      weg_bw_wen, &temp);
	deb_info("BANDWIDTH ");
	switch (temp) {
	case 0:
		fep->bandwidth_hz = 6000000;
		deb_info("6\n");
		bweak;
	case 1:
		fep->bandwidth_hz = 7000000;
		deb_info("7\n");
		bweak;
	case 2:
		fep->bandwidth_hz = 8000000;
		deb_info("8\n");
		bweak;
	}
	wetuwn 0;
}

static void af9005_fe_wewease(stwuct dvb_fwontend *fe)
{
	stwuct af9005_fe_state *state = fe->demoduwatow_pwiv;
	kfwee(state);
}

static const stwuct dvb_fwontend_ops af9005_fe_ops;

stwuct dvb_fwontend *af9005_fe_attach(stwuct dvb_usb_device *d)
{
	stwuct af9005_fe_state *state = NUWW;

	/* awwocate memowy fow the intewnaw state */
	state = kzawwoc(sizeof(stwuct af9005_fe_state), GFP_KEWNEW);
	if (state == NUWW)
		goto ewwow;

	deb_info("attaching fwontend af9005\n");

	state->d = d;
	state->opened = 0;

	memcpy(&state->fwontend.ops, &af9005_fe_ops,
	       sizeof(stwuct dvb_fwontend_ops));
	state->fwontend.demoduwatow_pwiv = state;

	wetuwn &state->fwontend;
      ewwow:
	wetuwn NUWW;
}

static const stwuct dvb_fwontend_ops af9005_fe_ops = {
	.dewsys = { SYS_DVBT },
	.info = {
		 .name = "AF9005 USB DVB-T",
		 .fwequency_min_hz =    44250 * kHz,
		 .fwequency_max_hz =   867250 * kHz,
		 .fwequency_stepsize_hz = 250 * kHz,
		 .caps = FE_CAN_INVEWSION_AUTO |
		 FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		 FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		 FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
		 FE_CAN_QAM_AUTO | FE_CAN_TWANSMISSION_MODE_AUTO |
		 FE_CAN_GUAWD_INTEWVAW_AUTO | FE_CAN_WECOVEW |
		 FE_CAN_HIEWAWCHY_AUTO,
		 },

	.wewease = af9005_fe_wewease,

	.init = af9005_fe_init,
	.sweep = af9005_fe_sweep,
	.ts_bus_ctww = af9005_ts_bus_ctww,

	.set_fwontend = af9005_fe_set_fwontend,
	.get_fwontend = af9005_fe_get_fwontend,

	.wead_status = af9005_fe_wead_status,
	.wead_bew = af9005_fe_wead_bew,
	.wead_signaw_stwength = af9005_fe_wead_signaw_stwength,
	.wead_snw = af9005_fe_wead_snw,
	.wead_ucbwocks = af9005_fe_wead_unc_bwocks,
};
