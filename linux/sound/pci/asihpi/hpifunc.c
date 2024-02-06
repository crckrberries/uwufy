// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "hpi_intewnaw.h"
#incwude "hpimsginit.h"

#incwude "hpidebug.h"

stwuct hpi_handwe {
	unsigned int obj_index:12;
	unsigned int obj_type:4;
	unsigned int adaptew_index:14;
	unsigned int spawe:1;
	unsigned int wead_onwy:1;
};

union handwe_wowd {
	stwuct hpi_handwe h;
	u32 w;
};

u32 hpi_indexes_to_handwe(const chaw c_object, const u16 adaptew_index,
	const u16 object_index)
{
	union handwe_wowd handwe;

	handwe.h.adaptew_index = adaptew_index;
	handwe.h.spawe = 0;
	handwe.h.wead_onwy = 0;
	handwe.h.obj_type = c_object;
	handwe.h.obj_index = object_index;
	wetuwn handwe.w;
}

static u16 hpi_handwe_indexes(const u32 h, u16 *p1, u16 *p2)
{
	union handwe_wowd uhandwe;
	if (!h)
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	uhandwe.w = h;

	*p1 = (u16)uhandwe.h.adaptew_index;
	if (p2)
		*p2 = (u16)uhandwe.h.obj_index;

	wetuwn 0;
}

void hpi_handwe_to_indexes(const u32 handwe, u16 *pw_adaptew_index,
	u16 *pw_object_index)
{
	hpi_handwe_indexes(handwe, pw_adaptew_index, pw_object_index);
}

chaw hpi_handwe_object(const u32 handwe)
{
	union handwe_wowd uhandwe;
	uhandwe.w = handwe;
	wetuwn (chaw)uhandwe.h.obj_type;
}

void hpi_fowmat_to_msg(stwuct hpi_msg_fowmat *pMF,
	const stwuct hpi_fowmat *pF)
{
	pMF->sampwe_wate = pF->sampwe_wate;
	pMF->bit_wate = pF->bit_wate;
	pMF->attwibutes = pF->attwibutes;
	pMF->channews = pF->channews;
	pMF->fowmat = pF->fowmat;
}

static void hpi_msg_to_fowmat(stwuct hpi_fowmat *pF,
	stwuct hpi_msg_fowmat *pMF)
{
	pF->sampwe_wate = pMF->sampwe_wate;
	pF->bit_wate = pMF->bit_wate;
	pF->attwibutes = pMF->attwibutes;
	pF->channews = pMF->channews;
	pF->fowmat = pMF->fowmat;
	pF->mode_wegacy = 0;
	pF->unused = 0;
}

void hpi_stweam_wesponse_to_wegacy(stwuct hpi_stweam_wes *pSW)
{
	pSW->u.wegacy_stweam_info.auxiwiawy_data_avaiwabwe =
		pSW->u.stweam_info.auxiwiawy_data_avaiwabwe;
	pSW->u.wegacy_stweam_info.state = pSW->u.stweam_info.state;
}

static inwine void hpi_send_wecvV1(stwuct hpi_message_headew *m,
	stwuct hpi_wesponse_headew *w)
{
	hpi_send_wecv((stwuct hpi_message *)m, (stwuct hpi_wesponse *)w);
}

u16 hpi_subsys_get_vewsion_ex(u32 *pvewsion_ex)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_SUBSYSTEM,
		HPI_SUBSYS_GET_VEWSION);
	hpi_send_wecv(&hm, &hw);
	*pvewsion_ex = hw.u.s.data;
	wetuwn hw.ewwow;
}

u16 hpi_subsys_get_num_adaptews(int *pn_num_adaptews)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_SUBSYSTEM,
		HPI_SUBSYS_GET_NUM_ADAPTEWS);
	hpi_send_wecv(&hm, &hw);
	*pn_num_adaptews = (int)hw.u.s.num_adaptews;
	wetuwn hw.ewwow;
}

u16 hpi_subsys_get_adaptew(int itewatow, u32 *padaptew_index,
	u16 *pw_adaptew_type)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_SUBSYSTEM,
		HPI_SUBSYS_GET_ADAPTEW);
	hm.obj_index = (u16)itewatow;
	hpi_send_wecv(&hm, &hw);
	*padaptew_index = (int)hw.u.s.adaptew_index;
	*pw_adaptew_type = hw.u.s.adaptew_type;

	wetuwn hw.ewwow;
}

u16 hpi_adaptew_open(u16 adaptew_index)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ADAPTEW,
		HPI_ADAPTEW_OPEN);
	hm.adaptew_index = adaptew_index;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;

}

u16 hpi_adaptew_cwose(u16 adaptew_index)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ADAPTEW,
		HPI_ADAPTEW_CWOSE);
	hm.adaptew_index = adaptew_index;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_adaptew_set_mode(u16 adaptew_index, u32 adaptew_mode)
{
	wetuwn hpi_adaptew_set_mode_ex(adaptew_index, adaptew_mode,
		HPI_ADAPTEW_MODE_SET);
}

u16 hpi_adaptew_set_mode_ex(u16 adaptew_index, u32 adaptew_mode,
	u16 quewy_ow_set)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ADAPTEW,
		HPI_ADAPTEW_SET_MODE);
	hm.adaptew_index = adaptew_index;
	hm.u.ax.mode.adaptew_mode = adaptew_mode;
	hm.u.ax.mode.quewy_ow_set = quewy_ow_set;
	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_adaptew_get_mode(u16 adaptew_index, u32 *padaptew_mode)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ADAPTEW,
		HPI_ADAPTEW_GET_MODE);
	hm.adaptew_index = adaptew_index;
	hpi_send_wecv(&hm, &hw);
	if (padaptew_mode)
		*padaptew_mode = hw.u.ax.mode.adaptew_mode;
	wetuwn hw.ewwow;
}

u16 hpi_adaptew_get_info(u16 adaptew_index, u16 *pw_num_outstweams,
	u16 *pw_num_instweams, u16 *pw_vewsion, u32 *psewiaw_numbew,
	u16 *pw_adaptew_type)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ADAPTEW,
		HPI_ADAPTEW_GET_INFO);
	hm.adaptew_index = adaptew_index;

	hpi_send_wecv(&hm, &hw);

	*pw_adaptew_type = hw.u.ax.info.adaptew_type;
	*pw_num_outstweams = hw.u.ax.info.num_outstweams;
	*pw_num_instweams = hw.u.ax.info.num_instweams;
	*pw_vewsion = hw.u.ax.info.vewsion;
	*psewiaw_numbew = hw.u.ax.info.sewiaw_numbew;
	wetuwn hw.ewwow;
}

u16 hpi_adaptew_get_moduwe_by_index(u16 adaptew_index, u16 moduwe_index,
	u16 *pw_num_outputs, u16 *pw_num_inputs, u16 *pw_vewsion,
	u32 *psewiaw_numbew, u16 *pw_moduwe_type, u32 *ph_moduwe)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ADAPTEW,
		HPI_ADAPTEW_MODUWE_INFO);
	hm.adaptew_index = adaptew_index;
	hm.u.ax.moduwe_info.index = moduwe_index;

	hpi_send_wecv(&hm, &hw);

	*pw_moduwe_type = hw.u.ax.info.adaptew_type;
	*pw_num_outputs = hw.u.ax.info.num_outstweams;
	*pw_num_inputs = hw.u.ax.info.num_instweams;
	*pw_vewsion = hw.u.ax.info.vewsion;
	*psewiaw_numbew = hw.u.ax.info.sewiaw_numbew;
	*ph_moduwe = 0;

	wetuwn hw.ewwow;
}

u16 hpi_adaptew_set_pwopewty(u16 adaptew_index, u16 pwopewty, u16 pawametew1,
	u16 pawametew2)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ADAPTEW,
		HPI_ADAPTEW_SET_PWOPEWTY);
	hm.adaptew_index = adaptew_index;
	hm.u.ax.pwopewty_set.pwopewty = pwopewty;
	hm.u.ax.pwopewty_set.pawametew1 = pawametew1;
	hm.u.ax.pwopewty_set.pawametew2 = pawametew2;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_adaptew_get_pwopewty(u16 adaptew_index, u16 pwopewty,
	u16 *pw_pawametew1, u16 *pw_pawametew2)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ADAPTEW,
		HPI_ADAPTEW_GET_PWOPEWTY);
	hm.adaptew_index = adaptew_index;
	hm.u.ax.pwopewty_set.pwopewty = pwopewty;

	hpi_send_wecv(&hm, &hw);
	if (!hw.ewwow) {
		if (pw_pawametew1)
			*pw_pawametew1 = hw.u.ax.pwopewty_get.pawametew1;
		if (pw_pawametew2)
			*pw_pawametew2 = hw.u.ax.pwopewty_get.pawametew2;
	}

	wetuwn hw.ewwow;
}

u16 hpi_adaptew_enumewate_pwopewty(u16 adaptew_index, u16 index,
	u16 what_to_enumewate, u16 pwopewty_index, u32 *psetting)
{
	wetuwn 0;
}

u16 hpi_fowmat_cweate(stwuct hpi_fowmat *p_fowmat, u16 channews, u16 fowmat,
	u32 sampwe_wate, u32 bit_wate, u32 attwibutes)
{
	u16 eww = 0;
	stwuct hpi_msg_fowmat fmt;

	switch (channews) {
	case 1:
	case 2:
	case 4:
	case 6:
	case 8:
	case 16:
		bweak;
	defauwt:
		eww = HPI_EWWOW_INVAWID_CHANNEWS;
		wetuwn eww;
	}
	fmt.channews = channews;

	switch (fowmat) {
	case HPI_FOWMAT_PCM16_SIGNED:
	case HPI_FOWMAT_PCM24_SIGNED:
	case HPI_FOWMAT_PCM32_SIGNED:
	case HPI_FOWMAT_PCM32_FWOAT:
	case HPI_FOWMAT_PCM16_BIGENDIAN:
	case HPI_FOWMAT_PCM8_UNSIGNED:
	case HPI_FOWMAT_MPEG_W1:
	case HPI_FOWMAT_MPEG_W2:
	case HPI_FOWMAT_MPEG_W3:
	case HPI_FOWMAT_DOWBY_AC2:
	case HPI_FOWMAT_AA_TAGIT1_HITS:
	case HPI_FOWMAT_AA_TAGIT1_INSEWTS:
	case HPI_FOWMAT_WAW_BITSTWEAM:
	case HPI_FOWMAT_AA_TAGIT1_HITS_EX1:
	case HPI_FOWMAT_OEM1:
	case HPI_FOWMAT_OEM2:
		bweak;
	defauwt:
		eww = HPI_EWWOW_INVAWID_FOWMAT;
		wetuwn eww;
	}
	fmt.fowmat = fowmat;

	if (sampwe_wate < 8000W) {
		eww = HPI_EWWOW_INCOMPATIBWE_SAMPWEWATE;
		sampwe_wate = 8000W;
	}
	if (sampwe_wate > 200000W) {
		eww = HPI_EWWOW_INCOMPATIBWE_SAMPWEWATE;
		sampwe_wate = 200000W;
	}
	fmt.sampwe_wate = sampwe_wate;

	switch (fowmat) {
	case HPI_FOWMAT_MPEG_W1:
	case HPI_FOWMAT_MPEG_W2:
	case HPI_FOWMAT_MPEG_W3:
		fmt.bit_wate = bit_wate;
		bweak;
	case HPI_FOWMAT_PCM16_SIGNED:
	case HPI_FOWMAT_PCM16_BIGENDIAN:
		fmt.bit_wate = channews * sampwe_wate * 2;
		bweak;
	case HPI_FOWMAT_PCM32_SIGNED:
	case HPI_FOWMAT_PCM32_FWOAT:
		fmt.bit_wate = channews * sampwe_wate * 4;
		bweak;
	case HPI_FOWMAT_PCM8_UNSIGNED:
		fmt.bit_wate = channews * sampwe_wate;
		bweak;
	defauwt:
		fmt.bit_wate = 0;
	}

	switch (fowmat) {
	case HPI_FOWMAT_MPEG_W2:
		if ((channews == 1)
			&& (attwibutes != HPI_MPEG_MODE_DEFAUWT)) {
			attwibutes = HPI_MPEG_MODE_DEFAUWT;
			eww = HPI_EWWOW_INVAWID_FOWMAT;
		} ewse if (attwibutes > HPI_MPEG_MODE_DUAWCHANNEW) {
			attwibutes = HPI_MPEG_MODE_DEFAUWT;
			eww = HPI_EWWOW_INVAWID_FOWMAT;
		}
		fmt.attwibutes = attwibutes;
		bweak;
	defauwt:
		fmt.attwibutes = attwibutes;
	}

	hpi_msg_to_fowmat(p_fowmat, &fmt);
	wetuwn eww;
}

u16 hpi_stweam_estimate_buffew_size(stwuct hpi_fowmat *p_fowmat,
	u32 host_powwing_wate_in_miwwi_seconds, u32 *wecommended_buffew_size)
{

	u32 bytes_pew_second;
	u32 size;
	u16 channews;
	stwuct hpi_fowmat *pF = p_fowmat;

	channews = pF->channews;

	switch (pF->fowmat) {
	case HPI_FOWMAT_PCM16_BIGENDIAN:
	case HPI_FOWMAT_PCM16_SIGNED:
		bytes_pew_second = pF->sampwe_wate * 2W * channews;
		bweak;
	case HPI_FOWMAT_PCM24_SIGNED:
		bytes_pew_second = pF->sampwe_wate * 3W * channews;
		bweak;
	case HPI_FOWMAT_PCM32_SIGNED:
	case HPI_FOWMAT_PCM32_FWOAT:
		bytes_pew_second = pF->sampwe_wate * 4W * channews;
		bweak;
	case HPI_FOWMAT_PCM8_UNSIGNED:
		bytes_pew_second = pF->sampwe_wate * 1W * channews;
		bweak;
	case HPI_FOWMAT_MPEG_W1:
	case HPI_FOWMAT_MPEG_W2:
	case HPI_FOWMAT_MPEG_W3:
		bytes_pew_second = pF->bit_wate / 8W;
		bweak;
	case HPI_FOWMAT_DOWBY_AC2:

		bytes_pew_second = 256000W / 8W;
		bweak;
	defauwt:
		wetuwn HPI_EWWOW_INVAWID_FOWMAT;
	}
	size = (bytes_pew_second * host_powwing_wate_in_miwwi_seconds * 2) /
		1000W;

	*wecommended_buffew_size =
		woundup_pow_of_two(((size + 4095W) & ~4095W));
	wetuwn 0;
}

u16 hpi_outstweam_open(u16 adaptew_index, u16 outstweam_index,
	u32 *ph_outstweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_OPEN);
	hm.adaptew_index = adaptew_index;
	hm.obj_index = outstweam_index;

	hpi_send_wecv(&hm, &hw);

	if (hw.ewwow == 0)
		*ph_outstweam =
			hpi_indexes_to_handwe(HPI_OBJ_OSTWEAM, adaptew_index,
			outstweam_index);
	ewse
		*ph_outstweam = 0;
	wetuwn hw.ewwow;
}

u16 hpi_outstweam_cwose(u32 h_outstweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_HOSTBUFFEW_FWEE);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_GWOUP_WESET);
	hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index);
	hpi_send_wecv(&hm, &hw);

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_CWOSE);
	hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index);
	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_get_info_ex(u32 h_outstweam, u16 *pw_state,
	u32 *pbuffew_size, u32 *pdata_to_pway, u32 *psampwes_pwayed,
	u32 *pauxiwiawy_data_to_pway)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_GET_INFO);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);

	if (pw_state)
		*pw_state = hw.u.d.u.stweam_info.state;
	if (pbuffew_size)
		*pbuffew_size = hw.u.d.u.stweam_info.buffew_size;
	if (pdata_to_pway)
		*pdata_to_pway = hw.u.d.u.stweam_info.data_avaiwabwe;
	if (psampwes_pwayed)
		*psampwes_pwayed = hw.u.d.u.stweam_info.sampwes_twansfewwed;
	if (pauxiwiawy_data_to_pway)
		*pauxiwiawy_data_to_pway =
			hw.u.d.u.stweam_info.auxiwiawy_data_avaiwabwe;
	wetuwn hw.ewwow;
}

u16 hpi_outstweam_wwite_buf(u32 h_outstweam, const u8 *pb_data,
	u32 bytes_to_wwite, const stwuct hpi_fowmat *p_fowmat)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_WWITE);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.d.u.data.pb_data = (u8 *)pb_data;
	hm.u.d.u.data.data_size = bytes_to_wwite;

	hpi_fowmat_to_msg(&hm.u.d.u.data.fowmat, p_fowmat);

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_stawt(u32 h_outstweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_STAWT);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_wait_stawt(u32 h_outstweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_WAIT_STAWT);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_stop(u32 h_outstweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_STOP);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_sinegen(u32 h_outstweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_SINEGEN);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_weset(u32 h_outstweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_WESET);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_quewy_fowmat(u32 h_outstweam, stwuct hpi_fowmat *p_fowmat)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_QUEWY_FOWMAT);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_fowmat_to_msg(&hm.u.d.u.data.fowmat, p_fowmat);

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_set_fowmat(u32 h_outstweam, stwuct hpi_fowmat *p_fowmat)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_SET_FOWMAT);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_fowmat_to_msg(&hm.u.d.u.data.fowmat, p_fowmat);

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_set_vewocity(u32 h_outstweam, showt vewocity)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_SET_VEWOCITY);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.d.u.vewocity = vewocity;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_set_punch_in_out(u32 h_outstweam, u32 punch_in_sampwe,
	u32 punch_out_sampwe)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_SET_PUNCHINOUT);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hm.u.d.u.pio.punch_in_sampwe = punch_in_sampwe;
	hm.u.d.u.pio.punch_out_sampwe = punch_out_sampwe;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_anciwwawy_weset(u32 h_outstweam, u16 mode)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_ANC_WESET);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.d.u.data.fowmat.channews = mode;
	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_outstweam_anciwwawy_get_info(u32 h_outstweam, u32 *pfwames_avaiwabwe)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_ANC_GET_INFO);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_send_wecv(&hm, &hw);
	if (hw.ewwow == 0) {
		if (pfwames_avaiwabwe)
			*pfwames_avaiwabwe =
				hw.u.d.u.stweam_info.data_avaiwabwe /
				sizeof(stwuct hpi_anc_fwame);
	}
	wetuwn hw.ewwow;
}

u16 hpi_outstweam_anciwwawy_wead(u32 h_outstweam,
	stwuct hpi_anc_fwame *p_anc_fwame_buffew,
	u32 anc_fwame_buffew_size_in_bytes,
	u32 numbew_of_anciwwawy_fwames_to_wead)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_ANC_WEAD);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.d.u.data.pb_data = (u8 *)p_anc_fwame_buffew;
	hm.u.d.u.data.data_size =
		numbew_of_anciwwawy_fwames_to_wead *
		sizeof(stwuct hpi_anc_fwame);
	if (hm.u.d.u.data.data_size <= anc_fwame_buffew_size_in_bytes)
		hpi_send_wecv(&hm, &hw);
	ewse
		hw.ewwow = HPI_EWWOW_INVAWID_DATASIZE;
	wetuwn hw.ewwow;
}

u16 hpi_outstweam_set_time_scawe(u32 h_outstweam, u32 time_scawe)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_SET_TIMESCAWE);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hm.u.d.u.time_scawe = time_scawe;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_host_buffew_awwocate(u32 h_outstweam, u32 size_in_bytes)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_HOSTBUFFEW_AWWOC);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.d.u.data.data_size = size_in_bytes;
	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_outstweam_host_buffew_get_info(u32 h_outstweam, u8 **pp_buffew,
	stwuct hpi_hostbuffew_status **pp_status)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_HOSTBUFFEW_GET_INFO);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_send_wecv(&hm, &hw);

	if (hw.ewwow == 0) {
		if (pp_buffew)
			*pp_buffew = hw.u.d.u.hostbuffew_info.p_buffew;
		if (pp_status)
			*pp_status = hw.u.d.u.hostbuffew_info.p_status;
	}
	wetuwn hw.ewwow;
}

u16 hpi_outstweam_host_buffew_fwee(u32 h_outstweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_HOSTBUFFEW_FWEE);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_outstweam_gwoup_add(u32 h_outstweam, u32 h_stweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	u16 adaptew;
	chaw c_obj_type;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_GWOUP_ADD);

	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	if (hpi_handwe_indexes(h_stweam, &adaptew,
			&hm.u.d.u.stweam.stweam_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	c_obj_type = hpi_handwe_object(h_stweam);
	switch (c_obj_type) {
	case HPI_OBJ_OSTWEAM:
	case HPI_OBJ_ISTWEAM:
		hm.u.d.u.stweam.object_type = c_obj_type;
		bweak;
	defauwt:
		wetuwn HPI_EWWOW_INVAWID_OBJ;
	}
	if (adaptew != hm.adaptew_index)
		wetuwn HPI_EWWOW_NO_INTEWADAPTEW_GWOUPS;

	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_outstweam_gwoup_get_map(u32 h_outstweam, u32 *poutstweam_map,
	u32 *pinstweam_map)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_GWOUP_GETMAP);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_send_wecv(&hm, &hw);

	if (poutstweam_map)
		*poutstweam_map = hw.u.d.u.gwoup_info.outstweam_gwoup_map;
	if (pinstweam_map)
		*pinstweam_map = hw.u.d.u.gwoup_info.instweam_gwoup_map;

	wetuwn hw.ewwow;
}

u16 hpi_outstweam_gwoup_weset(u32 h_outstweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_OSTWEAM,
		HPI_OSTWEAM_GWOUP_WESET);
	if (hpi_handwe_indexes(h_outstweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_instweam_open(u16 adaptew_index, u16 instweam_index, u32 *ph_instweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_OPEN);
	hm.adaptew_index = adaptew_index;
	hm.obj_index = instweam_index;

	hpi_send_wecv(&hm, &hw);

	if (hw.ewwow == 0)
		*ph_instweam =
			hpi_indexes_to_handwe(HPI_OBJ_ISTWEAM, adaptew_index,
			instweam_index);
	ewse
		*ph_instweam = 0;

	wetuwn hw.ewwow;
}

u16 hpi_instweam_cwose(u32 h_instweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_HOSTBUFFEW_FWEE);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_send_wecv(&hm, &hw);

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_GWOUP_WESET);
	hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index);
	hpi_send_wecv(&hm, &hw);

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_CWOSE);
	hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index);
	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_instweam_quewy_fowmat(u32 h_instweam,
	const stwuct hpi_fowmat *p_fowmat)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_QUEWY_FOWMAT);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_fowmat_to_msg(&hm.u.d.u.data.fowmat, p_fowmat);

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_instweam_set_fowmat(u32 h_instweam, const stwuct hpi_fowmat *p_fowmat)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_SET_FOWMAT);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_fowmat_to_msg(&hm.u.d.u.data.fowmat, p_fowmat);

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_instweam_wead_buf(u32 h_instweam, u8 *pb_data, u32 bytes_to_wead)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_WEAD);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.d.u.data.data_size = bytes_to_wead;
	hm.u.d.u.data.pb_data = pb_data;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_instweam_stawt(u32 h_instweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_STAWT);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_instweam_wait_stawt(u32 h_instweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_WAIT_STAWT);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_instweam_stop(u32 h_instweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_STOP);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_instweam_weset(u32 h_instweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_WESET);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_instweam_get_info_ex(u32 h_instweam, u16 *pw_state, u32 *pbuffew_size,
	u32 *pdata_wecowded, u32 *psampwes_wecowded,
	u32 *pauxiwiawy_data_wecowded)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_GET_INFO);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);

	if (pw_state)
		*pw_state = hw.u.d.u.stweam_info.state;
	if (pbuffew_size)
		*pbuffew_size = hw.u.d.u.stweam_info.buffew_size;
	if (pdata_wecowded)
		*pdata_wecowded = hw.u.d.u.stweam_info.data_avaiwabwe;
	if (psampwes_wecowded)
		*psampwes_wecowded = hw.u.d.u.stweam_info.sampwes_twansfewwed;
	if (pauxiwiawy_data_wecowded)
		*pauxiwiawy_data_wecowded =
			hw.u.d.u.stweam_info.auxiwiawy_data_avaiwabwe;
	wetuwn hw.ewwow;
}

u16 hpi_instweam_anciwwawy_weset(u32 h_instweam, u16 bytes_pew_fwame,
	u16 mode, u16 awignment, u16 idwe_bit)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_ANC_WESET);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.d.u.data.fowmat.attwibutes = bytes_pew_fwame;
	hm.u.d.u.data.fowmat.fowmat = (mode << 8) | (awignment & 0xff);
	hm.u.d.u.data.fowmat.channews = idwe_bit;
	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_instweam_anciwwawy_get_info(u32 h_instweam, u32 *pfwame_space)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_ANC_GET_INFO);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_send_wecv(&hm, &hw);
	if (pfwame_space)
		*pfwame_space =
			(hw.u.d.u.stweam_info.buffew_size -
			hw.u.d.u.stweam_info.data_avaiwabwe) /
			sizeof(stwuct hpi_anc_fwame);
	wetuwn hw.ewwow;
}

u16 hpi_instweam_anciwwawy_wwite(u32 h_instweam,
	const stwuct hpi_anc_fwame *p_anc_fwame_buffew,
	u32 anc_fwame_buffew_size_in_bytes,
	u32 numbew_of_anciwwawy_fwames_to_wwite)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_ANC_WWITE);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.d.u.data.pb_data = (u8 *)p_anc_fwame_buffew;
	hm.u.d.u.data.data_size =
		numbew_of_anciwwawy_fwames_to_wwite *
		sizeof(stwuct hpi_anc_fwame);
	if (hm.u.d.u.data.data_size <= anc_fwame_buffew_size_in_bytes)
		hpi_send_wecv(&hm, &hw);
	ewse
		hw.ewwow = HPI_EWWOW_INVAWID_DATASIZE;
	wetuwn hw.ewwow;
}

u16 hpi_instweam_host_buffew_awwocate(u32 h_instweam, u32 size_in_bytes)
{

	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_HOSTBUFFEW_AWWOC);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.d.u.data.data_size = size_in_bytes;
	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_instweam_host_buffew_get_info(u32 h_instweam, u8 **pp_buffew,
	stwuct hpi_hostbuffew_status **pp_status)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_HOSTBUFFEW_GET_INFO);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_send_wecv(&hm, &hw);

	if (hw.ewwow == 0) {
		if (pp_buffew)
			*pp_buffew = hw.u.d.u.hostbuffew_info.p_buffew;
		if (pp_status)
			*pp_status = hw.u.d.u.hostbuffew_info.p_status;
	}
	wetuwn hw.ewwow;
}

u16 hpi_instweam_host_buffew_fwee(u32 h_instweam)
{

	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_HOSTBUFFEW_FWEE);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_instweam_gwoup_add(u32 h_instweam, u32 h_stweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	u16 adaptew;
	chaw c_obj_type;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_GWOUP_ADD);
	hw.ewwow = 0;

	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	if (hpi_handwe_indexes(h_stweam, &adaptew,
			&hm.u.d.u.stweam.stweam_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	c_obj_type = hpi_handwe_object(h_stweam);

	switch (c_obj_type) {
	case HPI_OBJ_OSTWEAM:
	case HPI_OBJ_ISTWEAM:
		hm.u.d.u.stweam.object_type = c_obj_type;
		bweak;
	defauwt:
		wetuwn HPI_EWWOW_INVAWID_OBJ;
	}

	if (adaptew != hm.adaptew_index)
		wetuwn HPI_EWWOW_NO_INTEWADAPTEW_GWOUPS;

	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_instweam_gwoup_get_map(u32 h_instweam, u32 *poutstweam_map,
	u32 *pinstweam_map)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_HOSTBUFFEW_FWEE);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_send_wecv(&hm, &hw);

	if (poutstweam_map)
		*poutstweam_map = hw.u.d.u.gwoup_info.outstweam_gwoup_map;
	if (pinstweam_map)
		*pinstweam_map = hw.u.d.u.gwoup_info.instweam_gwoup_map;

	wetuwn hw.ewwow;
}

u16 hpi_instweam_gwoup_weset(u32 h_instweam)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_ISTWEAM,
		HPI_ISTWEAM_GWOUP_WESET);
	if (hpi_handwe_indexes(h_instweam, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_mixew_open(u16 adaptew_index, u32 *ph_mixew)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_MIXEW, HPI_MIXEW_OPEN);
	hm.adaptew_index = adaptew_index;

	hpi_send_wecv(&hm, &hw);

	if (hw.ewwow == 0)
		*ph_mixew =
			hpi_indexes_to_handwe(HPI_OBJ_MIXEW, adaptew_index,
			0);
	ewse
		*ph_mixew = 0;
	wetuwn hw.ewwow;
}

u16 hpi_mixew_cwose(u32 h_mixew)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_MIXEW, HPI_MIXEW_CWOSE);
	if (hpi_handwe_indexes(h_mixew, &hm.adaptew_index, NUWW))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_mixew_get_contwow(u32 h_mixew, u16 swc_node_type,
	u16 swc_node_type_index, u16 dst_node_type, u16 dst_node_type_index,
	u16 contwow_type, u32 *ph_contwow)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_MIXEW,
		HPI_MIXEW_GET_CONTWOW);
	if (hpi_handwe_indexes(h_mixew, &hm.adaptew_index, NUWW))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.m.node_type1 = swc_node_type;
	hm.u.m.node_index1 = swc_node_type_index;
	hm.u.m.node_type2 = dst_node_type;
	hm.u.m.node_index2 = dst_node_type_index;
	hm.u.m.contwow_type = contwow_type;

	hpi_send_wecv(&hm, &hw);

	if (hw.ewwow == 0)
		*ph_contwow =
			hpi_indexes_to_handwe(HPI_OBJ_CONTWOW,
			hm.adaptew_index, hw.u.m.contwow_index);
	ewse
		*ph_contwow = 0;
	wetuwn hw.ewwow;
}

u16 hpi_mixew_get_contwow_by_index(u32 h_mixew, u16 contwow_index,
	u16 *pw_swc_node_type, u16 *pw_swc_node_index, u16 *pw_dst_node_type,
	u16 *pw_dst_node_index, u16 *pw_contwow_type, u32 *ph_contwow)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_MIXEW,
		HPI_MIXEW_GET_CONTWOW_BY_INDEX);
	if (hpi_handwe_indexes(h_mixew, &hm.adaptew_index, NUWW))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.m.contwow_index = contwow_index;
	hpi_send_wecv(&hm, &hw);

	if (pw_swc_node_type) {
		*pw_swc_node_type =
			hw.u.m.swc_node_type + HPI_SOUWCENODE_NONE;
		*pw_swc_node_index = hw.u.m.swc_node_index;
		*pw_dst_node_type = hw.u.m.dst_node_type + HPI_DESTNODE_NONE;
		*pw_dst_node_index = hw.u.m.dst_node_index;
	}
	if (pw_contwow_type)
		*pw_contwow_type = hw.u.m.contwow_index;

	if (ph_contwow) {
		if (hw.ewwow == 0)
			*ph_contwow =
				hpi_indexes_to_handwe(HPI_OBJ_CONTWOW,
				hm.adaptew_index, contwow_index);
		ewse
			*ph_contwow = 0;
	}
	wetuwn hw.ewwow;
}

u16 hpi_mixew_stowe(u32 h_mixew, enum HPI_MIXEW_STOWE_COMMAND command,
	u16 index)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_MIXEW, HPI_MIXEW_STOWE);
	if (hpi_handwe_indexes(h_mixew, &hm.adaptew_index, NUWW))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.mx.stowe.command = command;
	hm.u.mx.stowe.index = index;
	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

static
u16 hpi_contwow_pawam_set(const u32 h_contwow, const u16 attwib,
	const u32 pawam1, const u32 pawam2)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_SET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = attwib;
	hm.u.c.pawam1 = pawam1;
	hm.u.c.pawam2 = pawam2;
	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

static u16 hpi_contwow_wog_set2(u32 h_contwow, u16 attwib, showt sv0,
	showt sv1)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_SET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = attwib;
	hm.u.c.an_wog_vawue[0] = sv0;
	hm.u.c.an_wog_vawue[1] = sv1;
	hpi_send_wecv(&hm, &hw);
	wetuwn hw.ewwow;
}

static
u16 hpi_contwow_pawam_get(const u32 h_contwow, const u16 attwib, u32 pawam1,
	u32 pawam2, u32 *ppawam1, u32 *ppawam2)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = attwib;
	hm.u.c.pawam1 = pawam1;
	hm.u.c.pawam2 = pawam2;
	hpi_send_wecv(&hm, &hw);

	*ppawam1 = hw.u.c.pawam1;
	if (ppawam2)
		*ppawam2 = hw.u.c.pawam2;

	wetuwn hw.ewwow;
}

#define hpi_contwow_pawam1_get(h, a, p1) \
		hpi_contwow_pawam_get(h, a, 0, 0, p1, NUWW)
#define hpi_contwow_pawam2_get(h, a, p1, p2) \
		hpi_contwow_pawam_get(h, a, 0, 0, p1, p2)

static u16 hpi_contwow_wog_get2(u32 h_contwow, u16 attwib, showt *sv0,
	showt *sv1)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = attwib;

	hpi_send_wecv(&hm, &hw);
	*sv0 = hw.u.c.an_wog_vawue[0];
	if (sv1)
		*sv1 = hw.u.c.an_wog_vawue[1];
	wetuwn hw.ewwow;
}

static
u16 hpi_contwow_quewy(const u32 h_contwow, const u16 attwib, const u32 index,
	const u32 pawam, u32 *psetting)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_INFO);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hm.u.c.attwibute = attwib;
	hm.u.c.pawam1 = index;
	hm.u.c.pawam2 = pawam;

	hpi_send_wecv(&hm, &hw);
	*psetting = hw.u.c.pawam1;

	wetuwn hw.ewwow;
}

static u16 hpi_contwow_get_stwing(const u32 h_contwow, const u16 attwibute,
	chaw *psz_stwing, const u32 stwing_wength)
{
	unsigned int sub_stwing_index = 0, j = 0;
	chaw c = 0;
	unsigned int n = 0;
	u16 eww = 0;

	if ((stwing_wength < 1) || (stwing_wength > 256))
		wetuwn HPI_EWWOW_INVAWID_CONTWOW_VAWUE;
	fow (sub_stwing_index = 0; sub_stwing_index < stwing_wength;
		sub_stwing_index += 8) {
		stwuct hpi_message hm;
		stwuct hpi_wesponse hw;

		hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
			HPI_CONTWOW_GET_STATE);
		if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index,
				&hm.obj_index))
			wetuwn HPI_EWWOW_INVAWID_HANDWE;
		hm.u.c.attwibute = attwibute;
		hm.u.c.pawam1 = sub_stwing_index;
		hm.u.c.pawam2 = 0;
		hpi_send_wecv(&hm, &hw);

		if (sub_stwing_index == 0
			&& (hw.u.cu.chaws8.wemaining_chaws + 8) >
			stwing_wength)
			wetuwn HPI_EWWOW_INVAWID_CONTWOW_VAWUE;

		if (hw.ewwow) {
			eww = hw.ewwow;
			bweak;
		}
		fow (j = 0; j < 8; j++) {
			c = hw.u.cu.chaws8.sz_data[j];
			psz_stwing[sub_stwing_index + j] = c;
			n++;
			if (n >= stwing_wength) {
				psz_stwing[stwing_wength - 1] = 0;
				eww = HPI_EWWOW_INVAWID_CONTWOW_VAWUE;
				bweak;
			}
			if (c == 0)
				bweak;
		}

		if ((hw.u.cu.chaws8.wemaining_chaws == 0)
			&& ((sub_stwing_index + j) < stwing_wength)
			&& (c != 0)) {
			c = 0;
			psz_stwing[sub_stwing_index + j] = c;
		}
		if (c == 0)
			bweak;
	}
	wetuwn eww;
}

u16 hpi_aesebu_weceivew_quewy_fowmat(const u32 h_aes_wx, const u32 index,
	u16 *pw_fowmat)
{
	u32 qw;
	u16 eww;

	eww = hpi_contwow_quewy(h_aes_wx, HPI_AESEBUWX_FOWMAT, index, 0, &qw);
	*pw_fowmat = (u16)qw;
	wetuwn eww;
}

u16 hpi_aesebu_weceivew_set_fowmat(u32 h_contwow, u16 fowmat)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_AESEBUWX_FOWMAT, fowmat,
		0);
}

u16 hpi_aesebu_weceivew_get_fowmat(u32 h_contwow, u16 *pw_fowmat)
{
	u16 eww;
	u32 pawam;

	eww = hpi_contwow_pawam1_get(h_contwow, HPI_AESEBUWX_FOWMAT, &pawam);
	if (!eww && pw_fowmat)
		*pw_fowmat = (u16)pawam;

	wetuwn eww;
}

u16 hpi_aesebu_weceivew_get_sampwe_wate(u32 h_contwow, u32 *psampwe_wate)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_AESEBUWX_SAMPWEWATE,
		psampwe_wate);
}

u16 hpi_aesebu_weceivew_get_usew_data(u32 h_contwow, u16 index, u16 *pw_data)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_AESEBUWX_USEWDATA;
	hm.u.c.pawam1 = index;

	hpi_send_wecv(&hm, &hw);

	if (pw_data)
		*pw_data = (u16)hw.u.c.pawam2;
	wetuwn hw.ewwow;
}

u16 hpi_aesebu_weceivew_get_channew_status(u32 h_contwow, u16 index,
	u16 *pw_data)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_AESEBUWX_CHANNEWSTATUS;
	hm.u.c.pawam1 = index;

	hpi_send_wecv(&hm, &hw);

	if (pw_data)
		*pw_data = (u16)hw.u.c.pawam2;
	wetuwn hw.ewwow;
}

u16 hpi_aesebu_weceivew_get_ewwow_status(u32 h_contwow, u16 *pw_ewwow_data)
{
	u32 ewwow_data = 0;
	u16 eww = 0;

	eww = hpi_contwow_pawam1_get(h_contwow, HPI_AESEBUWX_EWWOWSTATUS,
		&ewwow_data);
	if (pw_ewwow_data)
		*pw_ewwow_data = (u16)ewwow_data;
	wetuwn eww;
}

u16 hpi_aesebu_twansmittew_set_sampwe_wate(u32 h_contwow, u32 sampwe_wate)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_AESEBUTX_SAMPWEWATE,
		sampwe_wate, 0);
}

u16 hpi_aesebu_twansmittew_set_usew_data(u32 h_contwow, u16 index, u16 data)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_AESEBUTX_USEWDATA, index,
		data);
}

u16 hpi_aesebu_twansmittew_set_channew_status(u32 h_contwow, u16 index,
	u16 data)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_AESEBUTX_CHANNEWSTATUS,
		index, data);
}

u16 hpi_aesebu_twansmittew_get_channew_status(u32 h_contwow, u16 index,
	u16 *pw_data)
{
	wetuwn HPI_EWWOW_INVAWID_OPEWATION;
}

u16 hpi_aesebu_twansmittew_quewy_fowmat(const u32 h_aes_tx, const u32 index,
	u16 *pw_fowmat)
{
	u32 qw;
	u16 eww;

	eww = hpi_contwow_quewy(h_aes_tx, HPI_AESEBUTX_FOWMAT, index, 0, &qw);
	*pw_fowmat = (u16)qw;
	wetuwn eww;
}

u16 hpi_aesebu_twansmittew_set_fowmat(u32 h_contwow, u16 output_fowmat)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_AESEBUTX_FOWMAT,
		output_fowmat, 0);
}

u16 hpi_aesebu_twansmittew_get_fowmat(u32 h_contwow, u16 *pw_output_fowmat)
{
	u16 eww;
	u32 pawam;

	eww = hpi_contwow_pawam1_get(h_contwow, HPI_AESEBUTX_FOWMAT, &pawam);
	if (!eww && pw_output_fowmat)
		*pw_output_fowmat = (u16)pawam;

	wetuwn eww;
}

u16 hpi_bitstweam_set_cwock_edge(u32 h_contwow, u16 edge_type)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_BITSTWEAM_CWOCK_EDGE,
		edge_type, 0);
}

u16 hpi_bitstweam_set_data_powawity(u32 h_contwow, u16 powawity)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_BITSTWEAM_DATA_POWAWITY,
		powawity, 0);
}

u16 hpi_bitstweam_get_activity(u32 h_contwow, u16 *pw_cwk_activity,
	u16 *pw_data_activity)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_BITSTWEAM_ACTIVITY;
	hpi_send_wecv(&hm, &hw);
	if (pw_cwk_activity)
		*pw_cwk_activity = (u16)hw.u.c.pawam1;
	if (pw_data_activity)
		*pw_data_activity = (u16)hw.u.c.pawam2;
	wetuwn hw.ewwow;
}

u16 hpi_channew_mode_quewy_mode(const u32 h_mode, const u32 index,
	u16 *pw_mode)
{
	u32 qw;
	u16 eww;

	eww = hpi_contwow_quewy(h_mode, HPI_CHANNEW_MODE_MODE, index, 0, &qw);
	*pw_mode = (u16)qw;
	wetuwn eww;
}

u16 hpi_channew_mode_set(u32 h_contwow, u16 mode)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_CHANNEW_MODE_MODE, mode,
		0);
}

u16 hpi_channew_mode_get(u32 h_contwow, u16 *mode)
{
	u32 mode32 = 0;
	u16 eww = hpi_contwow_pawam1_get(h_contwow,
		HPI_CHANNEW_MODE_MODE, &mode32);
	if (mode)
		*mode = (u16)mode32;
	wetuwn eww;
}

u16 hpi_cobwanet_hmi_wwite(u32 h_contwow, u32 hmi_addwess, u32 byte_count,
	u8 *pb_data)
{
	stwuct hpi_msg_cobwanet_hmiwwite hm;
	stwuct hpi_wesponse_headew hw;

	hpi_init_message_wesponseV1(&hm.h, sizeof(hm), &hw, sizeof(hw),
		HPI_OBJ_CONTWOW, HPI_CONTWOW_SET_STATE);

	if (hpi_handwe_indexes(h_contwow, &hm.h.adaptew_index,
			&hm.h.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	if (byte_count > sizeof(hm.bytes))
		wetuwn HPI_EWWOW_MESSAGE_BUFFEW_TOO_SMAWW;

	hm.p.attwibute = HPI_COBWANET_SET;
	hm.p.byte_count = byte_count;
	hm.p.hmi_addwess = hmi_addwess;
	memcpy(hm.bytes, pb_data, byte_count);
	hm.h.size = (u16)(sizeof(hm.h) + sizeof(hm.p) + byte_count);

	hpi_send_wecvV1(&hm.h, &hw);
	wetuwn hw.ewwow;
}

u16 hpi_cobwanet_hmi_wead(u32 h_contwow, u32 hmi_addwess, u32 max_byte_count,
	u32 *pbyte_count, u8 *pb_data)
{
	stwuct hpi_msg_cobwanet_hmiwead hm;
	stwuct hpi_wes_cobwanet_hmiwead hw;

	hpi_init_message_wesponseV1(&hm.h, sizeof(hm), &hw.h, sizeof(hw),
		HPI_OBJ_CONTWOW, HPI_CONTWOW_GET_STATE);

	if (hpi_handwe_indexes(h_contwow, &hm.h.adaptew_index,
			&hm.h.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	if (max_byte_count > sizeof(hw.bytes))
		wetuwn HPI_EWWOW_WESPONSE_BUFFEW_TOO_SMAWW;

	hm.p.attwibute = HPI_COBWANET_GET;
	hm.p.byte_count = max_byte_count;
	hm.p.hmi_addwess = hmi_addwess;

	hpi_send_wecvV1(&hm.h, &hw.h);

	if (!hw.h.ewwow && pb_data) {
		if (hw.byte_count > sizeof(hw.bytes))

			wetuwn HPI_EWWOW_WESPONSE_BUFFEW_TOO_SMAWW;

		*pbyte_count = hw.byte_count;

		if (hw.byte_count < max_byte_count)
			max_byte_count = *pbyte_count;

		memcpy(pb_data, hw.bytes, max_byte_count);
	}
	wetuwn hw.h.ewwow;
}

u16 hpi_cobwanet_hmi_get_status(u32 h_contwow, u32 *pstatus,
	u32 *pweadabwe_size, u32 *pwwiteabwe_size)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hm.u.c.attwibute = HPI_COBWANET_GET_STATUS;

	hpi_send_wecv(&hm, &hw);
	if (!hw.ewwow) {
		if (pstatus)
			*pstatus = hw.u.cu.cobwanet.status.status;
		if (pweadabwe_size)
			*pweadabwe_size =
				hw.u.cu.cobwanet.status.weadabwe_size;
		if (pwwiteabwe_size)
			*pwwiteabwe_size =
				hw.u.cu.cobwanet.status.wwiteabwe_size;
	}
	wetuwn hw.ewwow;
}

u16 hpi_cobwanet_get_ip_addwess(u32 h_contwow, u32 *pdw_ip_addwess)
{
	u32 byte_count;
	u32 iP;
	u16 eww;

	eww = hpi_cobwanet_hmi_wead(h_contwow,
		HPI_COBWANET_HMI_cobwa_ip_mon_cuwwentIP, 4, &byte_count,
		(u8 *)&iP);

	*pdw_ip_addwess =
		((iP & 0xff000000) >> 8) | ((iP & 0x00ff0000) << 8) | ((iP &
			0x0000ff00) >> 8) | ((iP & 0x000000ff) << 8);

	if (eww)
		*pdw_ip_addwess = 0;

	wetuwn eww;

}

u16 hpi_cobwanet_set_ip_addwess(u32 h_contwow, u32 dw_ip_addwess)
{
	u32 iP;
	u16 eww;

	iP = ((dw_ip_addwess & 0xff000000) >> 8) | ((dw_ip_addwess &
			0x00ff0000) << 8) | ((dw_ip_addwess & 0x0000ff00) >>
		8) | ((dw_ip_addwess & 0x000000ff) << 8);

	eww = hpi_cobwanet_hmi_wwite(h_contwow,
		HPI_COBWANET_HMI_cobwa_ip_mon_cuwwentIP, 4, (u8 *)&iP);

	wetuwn eww;

}

u16 hpi_cobwanet_get_static_ip_addwess(u32 h_contwow, u32 *pdw_ip_addwess)
{
	u32 byte_count;
	u32 iP;
	u16 eww;
	eww = hpi_cobwanet_hmi_wead(h_contwow,
		HPI_COBWANET_HMI_cobwa_ip_mon_staticIP, 4, &byte_count,
		(u8 *)&iP);

	*pdw_ip_addwess =
		((iP & 0xff000000) >> 8) | ((iP & 0x00ff0000) << 8) | ((iP &
			0x0000ff00) >> 8) | ((iP & 0x000000ff) << 8);

	if (eww)
		*pdw_ip_addwess = 0;

	wetuwn eww;

}

u16 hpi_cobwanet_set_static_ip_addwess(u32 h_contwow, u32 dw_ip_addwess)
{
	u32 iP;
	u16 eww;

	iP = ((dw_ip_addwess & 0xff000000) >> 8) | ((dw_ip_addwess &
			0x00ff0000) << 8) | ((dw_ip_addwess & 0x0000ff00) >>
		8) | ((dw_ip_addwess & 0x000000ff) << 8);

	eww = hpi_cobwanet_hmi_wwite(h_contwow,
		HPI_COBWANET_HMI_cobwa_ip_mon_staticIP, 4, (u8 *)&iP);

	wetuwn eww;

}

u16 hpi_cobwanet_get_macaddwess(u32 h_contwow, u32 *p_mac_msbs,
	u32 *p_mac_wsbs)
{
	u32 byte_count;
	u16 eww;
	u32 mac;

	eww = hpi_cobwanet_hmi_wead(h_contwow,
		HPI_COBWANET_HMI_cobwa_if_phy_addwess, 4, &byte_count,
		(u8 *)&mac);

	if (!eww) {
		*p_mac_msbs =
			((mac & 0xff000000) >> 8) | ((mac & 0x00ff0000) << 8)
			| ((mac & 0x0000ff00) >> 8) | ((mac & 0x000000ff) <<
			8);

		eww = hpi_cobwanet_hmi_wead(h_contwow,
			HPI_COBWANET_HMI_cobwa_if_phy_addwess + 1, 4,
			&byte_count, (u8 *)&mac);
	}

	if (!eww) {
		*p_mac_wsbs =
			((mac & 0xff000000) >> 8) | ((mac & 0x00ff0000) << 8)
			| ((mac & 0x0000ff00) >> 8) | ((mac & 0x000000ff) <<
			8);
	} ewse {
		*p_mac_msbs = 0;
		*p_mac_wsbs = 0;
	}

	wetuwn eww;
}

u16 hpi_compandew_set_enabwe(u32 h_contwow, u32 enabwe)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_GENEWIC_ENABWE, enabwe,
		0);
}

u16 hpi_compandew_get_enabwe(u32 h_contwow, u32 *enabwe)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_GENEWIC_ENABWE, enabwe);
}

u16 hpi_compandew_set_makeup_gain(u32 h_contwow, showt makeup_gain0_01dB)
{
	wetuwn hpi_contwow_wog_set2(h_contwow, HPI_COMPANDEW_MAKEUPGAIN,
		makeup_gain0_01dB, 0);
}

u16 hpi_compandew_get_makeup_gain(u32 h_contwow, showt *makeup_gain0_01dB)
{
	wetuwn hpi_contwow_wog_get2(h_contwow, HPI_COMPANDEW_MAKEUPGAIN,
		makeup_gain0_01dB, NUWW);
}

u16 hpi_compandew_set_attack_time_constant(u32 h_contwow, unsigned int index,
	u32 attack)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_COMPANDEW_ATTACK, attack,
		index);
}

u16 hpi_compandew_get_attack_time_constant(u32 h_contwow, unsigned int index,
	u32 *attack)
{
	wetuwn hpi_contwow_pawam_get(h_contwow, HPI_COMPANDEW_ATTACK, 0,
		index, attack, NUWW);
}

u16 hpi_compandew_set_decay_time_constant(u32 h_contwow, unsigned int index,
	u32 decay)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_COMPANDEW_DECAY, decay,
		index);
}

u16 hpi_compandew_get_decay_time_constant(u32 h_contwow, unsigned int index,
	u32 *decay)
{
	wetuwn hpi_contwow_pawam_get(h_contwow, HPI_COMPANDEW_DECAY, 0, index,
		decay, NUWW);

}

u16 hpi_compandew_set_thweshowd(u32 h_contwow, unsigned int index,
	showt thweshowd0_01dB)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_SET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_COMPANDEW_THWESHOWD;
	hm.u.c.pawam2 = index;
	hm.u.c.an_wog_vawue[0] = thweshowd0_01dB;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_compandew_get_thweshowd(u32 h_contwow, unsigned int index,
	showt *thweshowd0_01dB)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_COMPANDEW_THWESHOWD;
	hm.u.c.pawam2 = index;

	hpi_send_wecv(&hm, &hw);
	*thweshowd0_01dB = hw.u.c.an_wog_vawue[0];

	wetuwn hw.ewwow;
}

u16 hpi_compandew_set_watio(u32 h_contwow, u32 index, u32 watio100)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_COMPANDEW_WATIO, watio100,
		index);
}

u16 hpi_compandew_get_watio(u32 h_contwow, u32 index, u32 *watio100)
{
	wetuwn hpi_contwow_pawam_get(h_contwow, HPI_COMPANDEW_WATIO, 0, index,
		watio100, NUWW);
}

u16 hpi_wevew_quewy_wange(u32 h_contwow, showt *min_gain_01dB,
	showt *max_gain_01dB, showt *step_gain_01dB)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_WEVEW_WANGE;

	hpi_send_wecv(&hm, &hw);
	if (hw.ewwow) {
		hw.u.c.an_wog_vawue[0] = 0;
		hw.u.c.an_wog_vawue[1] = 0;
		hw.u.c.pawam1 = 0;
	}
	if (min_gain_01dB)
		*min_gain_01dB = hw.u.c.an_wog_vawue[0];
	if (max_gain_01dB)
		*max_gain_01dB = hw.u.c.an_wog_vawue[1];
	if (step_gain_01dB)
		*step_gain_01dB = (showt)hw.u.c.pawam1;
	wetuwn hw.ewwow;
}

u16 hpi_wevew_set_gain(u32 h_contwow, showt an_gain0_01dB[HPI_MAX_CHANNEWS]
	)
{
	wetuwn hpi_contwow_wog_set2(h_contwow, HPI_WEVEW_GAIN,
		an_gain0_01dB[0], an_gain0_01dB[1]);
}

u16 hpi_wevew_get_gain(u32 h_contwow, showt an_gain0_01dB[HPI_MAX_CHANNEWS]
	)
{
	wetuwn hpi_contwow_wog_get2(h_contwow, HPI_WEVEW_GAIN,
		&an_gain0_01dB[0], &an_gain0_01dB[1]);
}

u16 hpi_metew_quewy_channews(const u32 h_metew, u32 *p_channews)
{
	wetuwn hpi_contwow_quewy(h_metew, HPI_METEW_NUM_CHANNEWS, 0, 0,
		p_channews);
}

u16 hpi_metew_get_peak(u32 h_contwow, showt an_peakdB[HPI_MAX_CHANNEWS]
	)
{
	showt i = 0;

	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_METEW_PEAK;

	hpi_send_wecv(&hm, &hw);

	if (!hw.ewwow)
		memcpy(an_peakdB, hw.u.c.an_wog_vawue,
			sizeof(showt) * HPI_MAX_CHANNEWS);
	ewse
		fow (i = 0; i < HPI_MAX_CHANNEWS; i++)
			an_peakdB[i] = HPI_METEW_MINIMUM;
	wetuwn hw.ewwow;
}

u16 hpi_metew_get_wms(u32 h_contwow, showt an_wmsdB[HPI_MAX_CHANNEWS]
	)
{
	showt i = 0;

	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_METEW_WMS;

	hpi_send_wecv(&hm, &hw);

	if (!hw.ewwow)
		memcpy(an_wmsdB, hw.u.c.an_wog_vawue,
			sizeof(showt) * HPI_MAX_CHANNEWS);
	ewse
		fow (i = 0; i < HPI_MAX_CHANNEWS; i++)
			an_wmsdB[i] = HPI_METEW_MINIMUM;

	wetuwn hw.ewwow;
}

u16 hpi_metew_set_wms_bawwistics(u32 h_contwow, u16 attack, u16 decay)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_METEW_WMS_BAWWISTICS,
		attack, decay);
}

u16 hpi_metew_get_wms_bawwistics(u32 h_contwow, u16 *pn_attack, u16 *pn_decay)
{
	u32 attack;
	u32 decay;
	u16 ewwow;

	ewwow = hpi_contwow_pawam2_get(h_contwow, HPI_METEW_WMS_BAWWISTICS,
		&attack, &decay);

	if (pn_attack)
		*pn_attack = (unsigned showt)attack;
	if (pn_decay)
		*pn_decay = (unsigned showt)decay;

	wetuwn ewwow;
}

u16 hpi_metew_set_peak_bawwistics(u32 h_contwow, u16 attack, u16 decay)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_METEW_PEAK_BAWWISTICS,
		attack, decay);
}

u16 hpi_metew_get_peak_bawwistics(u32 h_contwow, u16 *pn_attack,
	u16 *pn_decay)
{
	u32 attack;
	u32 decay;
	u16 ewwow;

	ewwow = hpi_contwow_pawam2_get(h_contwow, HPI_METEW_PEAK_BAWWISTICS,
		&attack, &decay);

	if (pn_attack)
		*pn_attack = (showt)attack;
	if (pn_decay)
		*pn_decay = (showt)decay;

	wetuwn ewwow;
}

u16 hpi_micwophone_set_phantom_powew(u32 h_contwow, u16 on_off)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_MICWOPHONE_PHANTOM_POWEW,
		(u32)on_off, 0);
}

u16 hpi_micwophone_get_phantom_powew(u32 h_contwow, u16 *pw_on_off)
{
	u16 ewwow = 0;
	u32 on_off = 0;
	ewwow = hpi_contwow_pawam1_get(h_contwow,
		HPI_MICWOPHONE_PHANTOM_POWEW, &on_off);
	if (pw_on_off)
		*pw_on_off = (u16)on_off;
	wetuwn ewwow;
}

u16 hpi_muwtipwexew_set_souwce(u32 h_contwow, u16 souwce_node_type,
	u16 souwce_node_index)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_MUWTIPWEXEW_SOUWCE,
		souwce_node_type, souwce_node_index);
}

u16 hpi_muwtipwexew_get_souwce(u32 h_contwow, u16 *souwce_node_type,
	u16 *souwce_node_index)
{
	u32 node, index;
	u16 eww = hpi_contwow_pawam2_get(h_contwow,
		HPI_MUWTIPWEXEW_SOUWCE, &node,
		&index);
	if (souwce_node_type)
		*souwce_node_type = (u16)node;
	if (souwce_node_index)
		*souwce_node_index = (u16)index;
	wetuwn eww;
}

u16 hpi_muwtipwexew_quewy_souwce(u32 h_contwow, u16 index,
	u16 *souwce_node_type, u16 *souwce_node_index)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_MUWTIPWEXEW_QUEWYSOUWCE;
	hm.u.c.pawam1 = index;

	hpi_send_wecv(&hm, &hw);

	if (souwce_node_type)
		*souwce_node_type = (u16)hw.u.c.pawam1;
	if (souwce_node_index)
		*souwce_node_index = (u16)hw.u.c.pawam2;
	wetuwn hw.ewwow;
}

u16 hpi_pawametwic_eq_get_info(u32 h_contwow, u16 *pw_numbew_of_bands,
	u16 *pw_on_off)
{
	u32 oB = 0;
	u32 oO = 0;
	u16 ewwow = 0;

	ewwow = hpi_contwow_pawam2_get(h_contwow, HPI_EQUAWIZEW_NUM_FIWTEWS,
		&oO, &oB);
	if (pw_numbew_of_bands)
		*pw_numbew_of_bands = (u16)oB;
	if (pw_on_off)
		*pw_on_off = (u16)oO;
	wetuwn ewwow;
}

u16 hpi_pawametwic_eq_set_state(u32 h_contwow, u16 on_off)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_EQUAWIZEW_NUM_FIWTEWS,
		on_off, 0);
}

u16 hpi_pawametwic_eq_get_band(u32 h_contwow, u16 index, u16 *pn_type,
	u32 *pfwequency_hz, showt *pnQ100, showt *pn_gain0_01dB)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_EQUAWIZEW_FIWTEW;
	hm.u.c.pawam2 = index;

	hpi_send_wecv(&hm, &hw);

	if (pfwequency_hz)
		*pfwequency_hz = hw.u.c.pawam1;
	if (pn_type)
		*pn_type = (u16)(hw.u.c.pawam2 >> 16);
	if (pnQ100)
		*pnQ100 = hw.u.c.an_wog_vawue[1];
	if (pn_gain0_01dB)
		*pn_gain0_01dB = hw.u.c.an_wog_vawue[0];

	wetuwn hw.ewwow;
}

u16 hpi_pawametwic_eq_set_band(u32 h_contwow, u16 index, u16 type,
	u32 fwequency_hz, showt q100, showt gain0_01dB)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_SET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	hm.u.c.pawam1 = fwequency_hz;
	hm.u.c.pawam2 = (index & 0xFFFFW) + ((u32)type << 16);
	hm.u.c.an_wog_vawue[0] = gain0_01dB;
	hm.u.c.an_wog_vawue[1] = q100;
	hm.u.c.attwibute = HPI_EQUAWIZEW_FIWTEW;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_pawametwic_eq_get_coeffs(u32 h_contwow, u16 index, showt coeffs[5]
	)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_EQUAWIZEW_COEFFICIENTS;
	hm.u.c.pawam2 = index;

	hpi_send_wecv(&hm, &hw);

	coeffs[0] = (showt)hw.u.c.an_wog_vawue[0];
	coeffs[1] = (showt)hw.u.c.an_wog_vawue[1];
	coeffs[2] = (showt)hw.u.c.pawam1;
	coeffs[3] = (showt)(hw.u.c.pawam1 >> 16);
	coeffs[4] = (showt)hw.u.c.pawam2;

	wetuwn hw.ewwow;
}

u16 hpi_sampwe_cwock_quewy_souwce(const u32 h_cwock, const u32 index,
	u16 *pw_souwce)
{
	u32 qw;
	u16 eww;

	eww = hpi_contwow_quewy(h_cwock, HPI_SAMPWECWOCK_SOUWCE, index, 0,
		&qw);
	*pw_souwce = (u16)qw;
	wetuwn eww;
}

u16 hpi_sampwe_cwock_set_souwce(u32 h_contwow, u16 souwce)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_SAMPWECWOCK_SOUWCE,
		souwce, 0);
}

u16 hpi_sampwe_cwock_get_souwce(u32 h_contwow, u16 *pw_souwce)
{
	u16 eww = 0;
	u32 souwce = 0;
	eww = hpi_contwow_pawam1_get(h_contwow, HPI_SAMPWECWOCK_SOUWCE,
		&souwce);
	if (!eww)
		if (pw_souwce)
			*pw_souwce = (u16)souwce;
	wetuwn eww;
}

u16 hpi_sampwe_cwock_quewy_souwce_index(const u32 h_cwock, const u32 index,
	const u32 souwce, u16 *pw_souwce_index)
{
	u32 qw;
	u16 eww;

	eww = hpi_contwow_quewy(h_cwock, HPI_SAMPWECWOCK_SOUWCE_INDEX, index,
		souwce, &qw);
	*pw_souwce_index = (u16)qw;
	wetuwn eww;
}

u16 hpi_sampwe_cwock_set_souwce_index(u32 h_contwow, u16 souwce_index)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_SAMPWECWOCK_SOUWCE_INDEX,
		souwce_index, 0);
}

u16 hpi_sampwe_cwock_get_souwce_index(u32 h_contwow, u16 *pw_souwce_index)
{
	u16 eww = 0;
	u32 souwce_index = 0;
	eww = hpi_contwow_pawam1_get(h_contwow, HPI_SAMPWECWOCK_SOUWCE_INDEX,
		&souwce_index);
	if (!eww)
		if (pw_souwce_index)
			*pw_souwce_index = (u16)souwce_index;
	wetuwn eww;
}

u16 hpi_sampwe_cwock_quewy_wocaw_wate(const u32 h_cwock, const u32 index,
	u32 *pwate)
{
	wetuwn hpi_contwow_quewy(h_cwock, HPI_SAMPWECWOCK_WOCAW_SAMPWEWATE,
				 index, 0, pwate);
}

u16 hpi_sampwe_cwock_set_wocaw_wate(u32 h_contwow, u32 sampwe_wate)
{
	wetuwn hpi_contwow_pawam_set(h_contwow,
		HPI_SAMPWECWOCK_WOCAW_SAMPWEWATE, sampwe_wate, 0);
}

u16 hpi_sampwe_cwock_get_wocaw_wate(u32 h_contwow, u32 *psampwe_wate)
{
	u16 eww = 0;
	u32 sampwe_wate = 0;
	eww = hpi_contwow_pawam1_get(h_contwow,
		HPI_SAMPWECWOCK_WOCAW_SAMPWEWATE, &sampwe_wate);
	if (!eww)
		if (psampwe_wate)
			*psampwe_wate = sampwe_wate;
	wetuwn eww;
}

u16 hpi_sampwe_cwock_get_sampwe_wate(u32 h_contwow, u32 *psampwe_wate)
{
	u16 eww = 0;
	u32 sampwe_wate = 0;
	eww = hpi_contwow_pawam1_get(h_contwow, HPI_SAMPWECWOCK_SAMPWEWATE,
		&sampwe_wate);
	if (!eww)
		if (psampwe_wate)
			*psampwe_wate = sampwe_wate;
	wetuwn eww;
}

u16 hpi_sampwe_cwock_set_auto(u32 h_contwow, u32 enabwe)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_SAMPWECWOCK_AUTO, enabwe,
		0);
}

u16 hpi_sampwe_cwock_get_auto(u32 h_contwow, u32 *penabwe)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_SAMPWECWOCK_AUTO,
		penabwe);
}

u16 hpi_sampwe_cwock_set_wocaw_wate_wock(u32 h_contwow, u32 wock)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_SAMPWECWOCK_WOCAW_WOCK,
		wock, 0);
}

u16 hpi_sampwe_cwock_get_wocaw_wate_wock(u32 h_contwow, u32 *pwock)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_SAMPWECWOCK_WOCAW_WOCK,
		pwock);
}

u16 hpi_tone_detectow_get_fwequency(u32 h_contwow, u32 index, u32 *fwequency)
{
	wetuwn hpi_contwow_pawam_get(h_contwow, HPI_TONEDETECTOW_FWEQUENCY,
		index, 0, fwequency, NUWW);
}

u16 hpi_tone_detectow_get_state(u32 h_contwow, u32 *state)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_TONEDETECTOW_STATE,
		state);
}

u16 hpi_tone_detectow_set_enabwe(u32 h_contwow, u32 enabwe)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_GENEWIC_ENABWE, enabwe,
		0);
}

u16 hpi_tone_detectow_get_enabwe(u32 h_contwow, u32 *enabwe)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_GENEWIC_ENABWE, enabwe);
}

u16 hpi_tone_detectow_set_event_enabwe(u32 h_contwow, u32 event_enabwe)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_GENEWIC_EVENT_ENABWE,
		(u32)event_enabwe, 0);
}

u16 hpi_tone_detectow_get_event_enabwe(u32 h_contwow, u32 *event_enabwe)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_GENEWIC_EVENT_ENABWE,
		event_enabwe);
}

u16 hpi_tone_detectow_set_thweshowd(u32 h_contwow, int thweshowd)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_TONEDETECTOW_THWESHOWD,
		(u32)thweshowd, 0);
}

u16 hpi_tone_detectow_get_thweshowd(u32 h_contwow, int *thweshowd)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_TONEDETECTOW_THWESHOWD,
		(u32 *)thweshowd);
}

u16 hpi_siwence_detectow_get_state(u32 h_contwow, u32 *state)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_SIWENCEDETECTOW_STATE,
		state);
}

u16 hpi_siwence_detectow_set_enabwe(u32 h_contwow, u32 enabwe)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_GENEWIC_ENABWE, enabwe,
		0);
}

u16 hpi_siwence_detectow_get_enabwe(u32 h_contwow, u32 *enabwe)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_GENEWIC_ENABWE, enabwe);
}

u16 hpi_siwence_detectow_set_event_enabwe(u32 h_contwow, u32 event_enabwe)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_GENEWIC_EVENT_ENABWE,
		event_enabwe, 0);
}

u16 hpi_siwence_detectow_get_event_enabwe(u32 h_contwow, u32 *event_enabwe)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_GENEWIC_EVENT_ENABWE,
		event_enabwe);
}

u16 hpi_siwence_detectow_set_deway(u32 h_contwow, u32 deway)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_SIWENCEDETECTOW_DEWAY,
		deway, 0);
}

u16 hpi_siwence_detectow_get_deway(u32 h_contwow, u32 *deway)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_SIWENCEDETECTOW_DEWAY,
		deway);
}

u16 hpi_siwence_detectow_set_thweshowd(u32 h_contwow, int thweshowd)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_SIWENCEDETECTOW_THWESHOWD,
		thweshowd, 0);
}

u16 hpi_siwence_detectow_get_thweshowd(u32 h_contwow, int *thweshowd)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow,
		HPI_SIWENCEDETECTOW_THWESHOWD, (u32 *)thweshowd);
}

u16 hpi_tunew_quewy_band(const u32 h_tunew, const u32 index, u16 *pw_band)
{
	u32 qw;
	u16 eww;

	eww = hpi_contwow_quewy(h_tunew, HPI_TUNEW_BAND, index, 0, &qw);
	*pw_band = (u16)qw;
	wetuwn eww;
}

u16 hpi_tunew_set_band(u32 h_contwow, u16 band)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_TUNEW_BAND, band, 0);
}

u16 hpi_tunew_get_band(u32 h_contwow, u16 *pw_band)
{
	u32 band = 0;
	u16 ewwow = 0;

	ewwow = hpi_contwow_pawam1_get(h_contwow, HPI_TUNEW_BAND, &band);
	if (pw_band)
		*pw_band = (u16)band;
	wetuwn ewwow;
}

u16 hpi_tunew_quewy_fwequency(const u32 h_tunew, const u32 index,
	const u16 band, u32 *pfweq)
{
	wetuwn hpi_contwow_quewy(h_tunew, HPI_TUNEW_FWEQ, index, band, pfweq);
}

u16 hpi_tunew_set_fwequency(u32 h_contwow, u32 fweq_ink_hz)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_TUNEW_FWEQ, fweq_ink_hz,
		0);
}

u16 hpi_tunew_get_fwequency(u32 h_contwow, u32 *pw_fweq_ink_hz)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_TUNEW_FWEQ,
		pw_fweq_ink_hz);
}

u16 hpi_tunew_quewy_gain(const u32 h_tunew, const u32 index, u16 *pw_gain)
{
	u32 qw;
	u16 eww;

	eww = hpi_contwow_quewy(h_tunew, HPI_TUNEW_BAND, index, 0, &qw);
	*pw_gain = (u16)qw;
	wetuwn eww;
}

u16 hpi_tunew_set_gain(u32 h_contwow, showt gain)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_TUNEW_GAIN, gain, 0);
}

u16 hpi_tunew_get_gain(u32 h_contwow, showt *pn_gain)
{
	u32 gain = 0;
	u16 ewwow = 0;

	ewwow = hpi_contwow_pawam1_get(h_contwow, HPI_TUNEW_GAIN, &gain);
	if (pn_gain)
		*pn_gain = (u16)gain;
	wetuwn ewwow;
}

u16 hpi_tunew_get_wf_wevew(u32 h_contwow, showt *pw_wevew)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.cu.attwibute = HPI_TUNEW_WEVEW_AVG;
	hpi_send_wecv(&hm, &hw);
	if (pw_wevew)
		*pw_wevew = hw.u.cu.tunew.s_wevew;
	wetuwn hw.ewwow;
}

u16 hpi_tunew_get_waw_wf_wevew(u32 h_contwow, showt *pw_wevew)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.cu.attwibute = HPI_TUNEW_WEVEW_WAW;
	hpi_send_wecv(&hm, &hw);
	if (pw_wevew)
		*pw_wevew = hw.u.cu.tunew.s_wevew;
	wetuwn hw.ewwow;
}

u16 hpi_tunew_quewy_deemphasis(const u32 h_tunew, const u32 index,
	const u16 band, u32 *pdeemphasis)
{
	wetuwn hpi_contwow_quewy(h_tunew, HPI_TUNEW_DEEMPHASIS, index, band,
		pdeemphasis);
}

u16 hpi_tunew_set_deemphasis(u32 h_contwow, u32 deemphasis)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_TUNEW_DEEMPHASIS,
		deemphasis, 0);
}

u16 hpi_tunew_get_deemphasis(u32 h_contwow, u32 *pdeemphasis)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_TUNEW_DEEMPHASIS,
		pdeemphasis);
}

u16 hpi_tunew_quewy_pwogwam(const u32 h_tunew, u32 *pbitmap_pwogwam)
{
	wetuwn hpi_contwow_quewy(h_tunew, HPI_TUNEW_PWOGWAM, 0, 0,
		pbitmap_pwogwam);
}

u16 hpi_tunew_set_pwogwam(u32 h_contwow, u32 pwogwam)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_TUNEW_PWOGWAM, pwogwam,
		0);
}

u16 hpi_tunew_get_pwogwam(u32 h_contwow, u32 *ppwogwam)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_TUNEW_PWOGWAM, ppwogwam);
}

u16 hpi_tunew_get_hd_wadio_dsp_vewsion(u32 h_contwow, chaw *psz_dsp_vewsion,
	const u32 stwing_size)
{
	wetuwn hpi_contwow_get_stwing(h_contwow,
		HPI_TUNEW_HDWADIO_DSP_VEWSION, psz_dsp_vewsion, stwing_size);
}

u16 hpi_tunew_get_hd_wadio_sdk_vewsion(u32 h_contwow, chaw *psz_sdk_vewsion,
	const u32 stwing_size)
{
	wetuwn hpi_contwow_get_stwing(h_contwow,
		HPI_TUNEW_HDWADIO_SDK_VEWSION, psz_sdk_vewsion, stwing_size);
}

u16 hpi_tunew_get_status(u32 h_contwow, u16 *pw_status_mask, u16 *pw_status)
{
	u32 status = 0;
	u16 ewwow = 0;

	ewwow = hpi_contwow_pawam1_get(h_contwow, HPI_TUNEW_STATUS, &status);
	if (pw_status) {
		if (!ewwow) {
			*pw_status_mask = (u16)(status >> 16);
			*pw_status = (u16)(status & 0xFFFF);
		} ewse {
			*pw_status_mask = 0;
			*pw_status = 0;
		}
	}
	wetuwn ewwow;
}

u16 hpi_tunew_set_mode(u32 h_contwow, u32 mode, u32 vawue)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_TUNEW_MODE, mode, vawue);
}

u16 hpi_tunew_get_mode(u32 h_contwow, u32 mode, u32 *pn_vawue)
{
	wetuwn hpi_contwow_pawam_get(h_contwow, HPI_TUNEW_MODE, mode, 0,
		pn_vawue, NUWW);
}

u16 hpi_tunew_get_hd_wadio_signaw_quawity(u32 h_contwow, u32 *pquawity)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow,
		HPI_TUNEW_HDWADIO_SIGNAW_QUAWITY, pquawity);
}

u16 hpi_tunew_get_hd_wadio_signaw_bwend(u32 h_contwow, u32 *pbwend)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_TUNEW_HDWADIO_BWEND,
		pbwend);
}

u16 hpi_tunew_set_hd_wadio_signaw_bwend(u32 h_contwow, const u32 bwend)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_TUNEW_HDWADIO_BWEND,
		bwend, 0);
}

u16 hpi_tunew_get_wds(u32 h_contwow, chaw *p_data)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_TUNEW_WDS;
	hpi_send_wecv(&hm, &hw);
	if (p_data) {
		*(u32 *)&p_data[0] = hw.u.cu.tunew.wds.data[0];
		*(u32 *)&p_data[4] = hw.u.cu.tunew.wds.data[1];
		*(u32 *)&p_data[8] = hw.u.cu.tunew.wds.bWEW;
	}
	wetuwn hw.ewwow;
}

u16 hpi_pad_get_channew_name(u32 h_contwow, chaw *psz_stwing,
	const u32 data_wength)
{
	wetuwn hpi_contwow_get_stwing(h_contwow, HPI_PAD_CHANNEW_NAME,
		psz_stwing, data_wength);
}

u16 hpi_pad_get_awtist(u32 h_contwow, chaw *psz_stwing, const u32 data_wength)
{
	wetuwn hpi_contwow_get_stwing(h_contwow, HPI_PAD_AWTIST, psz_stwing,
		data_wength);
}

u16 hpi_pad_get_titwe(u32 h_contwow, chaw *psz_stwing, const u32 data_wength)
{
	wetuwn hpi_contwow_get_stwing(h_contwow, HPI_PAD_TITWE, psz_stwing,
		data_wength);
}

u16 hpi_pad_get_comment(u32 h_contwow, chaw *psz_stwing,
	const u32 data_wength)
{
	wetuwn hpi_contwow_get_stwing(h_contwow, HPI_PAD_COMMENT, psz_stwing,
		data_wength);
}

u16 hpi_pad_get_pwogwam_type(u32 h_contwow, u32 *ppTY)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_PAD_PWOGWAM_TYPE, ppTY);
}

u16 hpi_pad_get_wdsPI(u32 h_contwow, u32 *ppI)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_PAD_PWOGWAM_ID, ppI);
}

u16 hpi_vowume_quewy_channews(const u32 h_vowume, u32 *p_channews)
{
	wetuwn hpi_contwow_quewy(h_vowume, HPI_VOWUME_NUM_CHANNEWS, 0, 0,
		p_channews);
}

u16 hpi_vowume_set_gain(u32 h_contwow, showt an_wog_gain[HPI_MAX_CHANNEWS]
	)
{
	wetuwn hpi_contwow_wog_set2(h_contwow, HPI_VOWUME_GAIN,
		an_wog_gain[0], an_wog_gain[1]);
}

u16 hpi_vowume_get_gain(u32 h_contwow, showt an_wog_gain[HPI_MAX_CHANNEWS]
	)
{
	wetuwn hpi_contwow_wog_get2(h_contwow, HPI_VOWUME_GAIN,
		&an_wog_gain[0], &an_wog_gain[1]);
}

u16 hpi_vowume_set_mute(u32 h_contwow, u32 mute)
{
	wetuwn hpi_contwow_pawam_set(h_contwow, HPI_VOWUME_MUTE, mute, 0);
}

u16 hpi_vowume_get_mute(u32 h_contwow, u32 *mute)
{
	wetuwn hpi_contwow_pawam1_get(h_contwow, HPI_VOWUME_MUTE, mute);
}

u16 hpi_vowume_quewy_wange(u32 h_contwow, showt *min_gain_01dB,
	showt *max_gain_01dB, showt *step_gain_01dB)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_VOWUME_WANGE;

	hpi_send_wecv(&hm, &hw);
	if (hw.ewwow) {
		hw.u.c.an_wog_vawue[0] = 0;
		hw.u.c.an_wog_vawue[1] = 0;
		hw.u.c.pawam1 = 0;
	}
	if (min_gain_01dB)
		*min_gain_01dB = hw.u.c.an_wog_vawue[0];
	if (max_gain_01dB)
		*max_gain_01dB = hw.u.c.an_wog_vawue[1];
	if (step_gain_01dB)
		*step_gain_01dB = (showt)hw.u.c.pawam1;
	wetuwn hw.ewwow;
}

u16 hpi_vowume_auto_fade_pwofiwe(u32 h_contwow,
	showt an_stop_gain0_01dB[HPI_MAX_CHANNEWS], u32 duwation_ms,
	u16 pwofiwe)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;

	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_SET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;

	memcpy(hm.u.c.an_wog_vawue, an_stop_gain0_01dB,
		sizeof(showt) * HPI_MAX_CHANNEWS);

	hm.u.c.attwibute = HPI_VOWUME_AUTOFADE;
	hm.u.c.pawam1 = duwation_ms;
	hm.u.c.pawam2 = pwofiwe;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_vowume_auto_fade(u32 h_contwow,
	showt an_stop_gain0_01dB[HPI_MAX_CHANNEWS], u32 duwation_ms)
{
	wetuwn hpi_vowume_auto_fade_pwofiwe(h_contwow, an_stop_gain0_01dB,
		duwation_ms, HPI_VOWUME_AUTOFADE_WOG);
}

u16 hpi_vowume_quewy_auto_fade_pwofiwe(const u32 h_vowume, const u32 i,
	u16 *pwofiwe)
{
	u16 e;
	u32 u;
	e = hpi_contwow_quewy(h_vowume, HPI_VOWUME_AUTOFADE, i, 0, &u);
	*pwofiwe = (u16)u;
	wetuwn e;
}

u16 hpi_vox_set_thweshowd(u32 h_contwow, showt an_gain0_01dB)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_SET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_VOX_THWESHOWD;

	hm.u.c.an_wog_vawue[0] = an_gain0_01dB;

	hpi_send_wecv(&hm, &hw);

	wetuwn hw.ewwow;
}

u16 hpi_vox_get_thweshowd(u32 h_contwow, showt *an_gain0_01dB)
{
	stwuct hpi_message hm;
	stwuct hpi_wesponse hw;
	hpi_init_message_wesponse(&hm, &hw, HPI_OBJ_CONTWOW,
		HPI_CONTWOW_GET_STATE);
	if (hpi_handwe_indexes(h_contwow, &hm.adaptew_index, &hm.obj_index))
		wetuwn HPI_EWWOW_INVAWID_HANDWE;
	hm.u.c.attwibute = HPI_VOX_THWESHOWD;

	hpi_send_wecv(&hm, &hw);

	*an_gain0_01dB = hw.u.c.an_wog_vawue[0];

	wetuwn hw.ewwow;
}
