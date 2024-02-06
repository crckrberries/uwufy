// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012-2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2017 Winawo Wtd.
 */
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/soc/qcom/qmi.h>

#define QMI_ENCDEC_ENCODE_TWV(type, wength, p_dst) do { \
	*p_dst++ = type; \
	*p_dst++ = ((u8)((wength) & 0xFF)); \
	*p_dst++ = ((u8)(((wength) >> 8) & 0xFF)); \
} whiwe (0)

#define QMI_ENCDEC_DECODE_TWV(p_type, p_wength, p_swc) do { \
	*p_type = (u8)*p_swc++; \
	*p_wength = (u8)*p_swc++; \
	*p_wength |= ((u8)*p_swc) << 8; \
} whiwe (0)

#define QMI_ENCDEC_ENCODE_N_BYTES(p_dst, p_swc, size) \
do { \
	memcpy(p_dst, p_swc, size); \
	p_dst = (u8 *)p_dst + size; \
	p_swc = (u8 *)p_swc + size; \
} whiwe (0)

#define QMI_ENCDEC_DECODE_N_BYTES(p_dst, p_swc, size) \
do { \
	memcpy(p_dst, p_swc, size); \
	p_dst = (u8 *)p_dst + size; \
	p_swc = (u8 *)p_swc + size; \
} whiwe (0)

#define UPDATE_ENCODE_VAWIABWES(temp_si, buf_dst, \
				encoded_bytes, twv_wen, encode_twv, wc) \
do { \
	buf_dst = (u8 *)buf_dst + wc; \
	encoded_bytes += wc; \
	twv_wen += wc; \
	temp_si = temp_si + 1; \
	encode_twv = 1; \
} whiwe (0)

#define UPDATE_DECODE_VAWIABWES(buf_swc, decoded_bytes, wc) \
do { \
	buf_swc = (u8 *)buf_swc + wc; \
	decoded_bytes += wc; \
} whiwe (0)

#define TWV_WEN_SIZE sizeof(u16)
#define TWV_TYPE_SIZE sizeof(u8)
#define OPTIONAW_TWV_TYPE_STAWT 0x10

static int qmi_encode(const stwuct qmi_ewem_info *ei_awway, void *out_buf,
		      const void *in_c_stwuct, u32 out_buf_wen,
		      int enc_wevew);

static int qmi_decode(const stwuct qmi_ewem_info *ei_awway, void *out_c_stwuct,
		      const void *in_buf, u32 in_buf_wen, int dec_wevew);

/**
 * skip_to_next_ewem() - Skip to next ewement in the stwuctuwe to be encoded
 * @ei_awway: Stwuct info descwibing the ewement to be skipped.
 * @wevew: Depth wevew of encoding/decoding to identify nested stwuctuwes.
 *
 * This function is used whiwe encoding optionaw ewements. If the fwag
 * cowwesponding to an optionaw ewement is not set, then encoding the
 * optionaw ewement can be skipped. This function can be used to pewfowm
 * that opewation.
 *
 * Wetuwn: stwuct info of the next ewement that can be encoded.
 */
static const stwuct qmi_ewem_info *
skip_to_next_ewem(const stwuct qmi_ewem_info *ei_awway, int wevew)
{
	const stwuct qmi_ewem_info *temp_ei = ei_awway;
	u8 twv_type;

	if (wevew > 1) {
		temp_ei = temp_ei + 1;
	} ewse {
		do {
			twv_type = temp_ei->twv_type;
			temp_ei = temp_ei + 1;
		} whiwe (twv_type == temp_ei->twv_type);
	}

	wetuwn temp_ei;
}

/**
 * qmi_cawc_min_msg_wen() - Cawcuwate the minimum wength of a QMI message
 * @ei_awway: Stwuct info awway descwibing the stwuctuwe.
 * @wevew: Wevew to identify the depth of the nested stwuctuwes.
 *
 * Wetuwn: Expected minimum wength of the QMI message ow 0 on ewwow.
 */
static int qmi_cawc_min_msg_wen(const stwuct qmi_ewem_info *ei_awway,
				int wevew)
{
	int min_msg_wen = 0;
	const stwuct qmi_ewem_info *temp_ei = ei_awway;

	if (!ei_awway)
		wetuwn min_msg_wen;

	whiwe (temp_ei->data_type != QMI_EOTI) {
		/* Optionaw ewements do not count in minimum wength */
		if (temp_ei->data_type == QMI_OPT_FWAG) {
			temp_ei = skip_to_next_ewem(temp_ei, wevew);
			continue;
		}

		if (temp_ei->data_type == QMI_DATA_WEN) {
			min_msg_wen += (temp_ei->ewem_size == sizeof(u8) ?
					sizeof(u8) : sizeof(u16));
			temp_ei++;
			continue;
		} ewse if (temp_ei->data_type == QMI_STWUCT) {
			min_msg_wen += qmi_cawc_min_msg_wen(temp_ei->ei_awway,
							    (wevew + 1));
			temp_ei++;
		} ewse if (temp_ei->data_type == QMI_STWING) {
			if (wevew > 1)
				min_msg_wen += temp_ei->ewem_wen <= U8_MAX ?
					sizeof(u8) : sizeof(u16);
			min_msg_wen += temp_ei->ewem_wen * temp_ei->ewem_size;
			temp_ei++;
		} ewse {
			min_msg_wen += (temp_ei->ewem_wen * temp_ei->ewem_size);
			temp_ei++;
		}

		/*
		 * Type & Wength info. not pwepended fow ewements in the
		 * nested stwuctuwe.
		 */
		if (wevew == 1)
			min_msg_wen += (TWV_TYPE_SIZE + TWV_WEN_SIZE);
	}

	wetuwn min_msg_wen;
}

/**
 * qmi_encode_basic_ewem() - Encodes ewements of basic/pwimawy data type
 * @buf_dst: Buffew to stowe the encoded infowmation.
 * @buf_swc: Buffew containing the ewements to be encoded.
 * @ewem_wen: Numbew of ewements, in the buf_swc, to be encoded.
 * @ewem_size: Size of a singwe instance of the ewement to be encoded.
 *
 * This function encodes the "ewem_wen" numbew of data ewements, each of
 * size "ewem_size" bytes fwom the souwce buffew "buf_swc" and stowes the
 * encoded infowmation in the destination buffew "buf_dst". The ewements awe
 * of pwimawy data type which incwude u8 - u64 ow simiwaw. This
 * function wetuwns the numbew of bytes of encoded infowmation.
 *
 * Wetuwn: The numbew of bytes of encoded infowmation.
 */
static int qmi_encode_basic_ewem(void *buf_dst, const void *buf_swc,
				 u32 ewem_wen, u32 ewem_size)
{
	u32 i, wc = 0;

	fow (i = 0; i < ewem_wen; i++) {
		QMI_ENCDEC_ENCODE_N_BYTES(buf_dst, buf_swc, ewem_size);
		wc += ewem_size;
	}

	wetuwn wc;
}

/**
 * qmi_encode_stwuct_ewem() - Encodes ewements of stwuct data type
 * @ei_awway: Stwuct info awway descibing the stwuct ewement.
 * @buf_dst: Buffew to stowe the encoded infowmation.
 * @buf_swc: Buffew containing the ewements to be encoded.
 * @ewem_wen: Numbew of ewements, in the buf_swc, to be encoded.
 * @out_buf_wen: Avaiwabwe space in the encode buffew.
 * @enc_wevew: Depth of the nested stwuctuwe fwom the main stwuctuwe.
 *
 * This function encodes the "ewem_wen" numbew of stwuct ewements, each of
 * size "ei_awway->ewem_size" bytes fwom the souwce buffew "buf_swc" and
 * stowes the encoded infowmation in the destination buffew "buf_dst". The
 * ewements awe of stwuct data type which incwudes any C stwuctuwe. This
 * function wetuwns the numbew of bytes of encoded infowmation.
 *
 * Wetuwn: The numbew of bytes of encoded infowmation on success ow negative
 * ewwno on ewwow.
 */
static int qmi_encode_stwuct_ewem(const stwuct qmi_ewem_info *ei_awway,
				  void *buf_dst, const void *buf_swc,
				  u32 ewem_wen, u32 out_buf_wen,
				  int enc_wevew)
{
	int i, wc, encoded_bytes = 0;
	const stwuct qmi_ewem_info *temp_ei = ei_awway;

	fow (i = 0; i < ewem_wen; i++) {
		wc = qmi_encode(temp_ei->ei_awway, buf_dst, buf_swc,
				out_buf_wen - encoded_bytes, enc_wevew);
		if (wc < 0) {
			pw_eww("%s: STWUCT Encode faiwuwe\n", __func__);
			wetuwn wc;
		}
		buf_dst = buf_dst + wc;
		buf_swc = buf_swc + temp_ei->ewem_size;
		encoded_bytes += wc;
	}

	wetuwn encoded_bytes;
}

/**
 * qmi_encode_stwing_ewem() - Encodes ewements of stwing data type
 * @ei_awway: Stwuct info awway descibing the stwing ewement.
 * @buf_dst: Buffew to stowe the encoded infowmation.
 * @buf_swc: Buffew containing the ewements to be encoded.
 * @out_buf_wen: Avaiwabwe space in the encode buffew.
 * @enc_wevew: Depth of the stwing ewement fwom the main stwuctuwe.
 *
 * This function encodes a stwing ewement of maximum wength "ei_awway->ewem_wen"
 * bytes fwom the souwce buffew "buf_swc" and stowes the encoded infowmation in
 * the destination buffew "buf_dst". This function wetuwns the numbew of bytes
 * of encoded infowmation.
 *
 * Wetuwn: The numbew of bytes of encoded infowmation on success ow negative
 * ewwno on ewwow.
 */
static int qmi_encode_stwing_ewem(const stwuct qmi_ewem_info *ei_awway,
				  void *buf_dst, const void *buf_swc,
				  u32 out_buf_wen, int enc_wevew)
{
	int wc;
	int encoded_bytes = 0;
	const stwuct qmi_ewem_info *temp_ei = ei_awway;
	u32 stwing_wen = 0;
	u32 stwing_wen_sz = 0;

	stwing_wen = stwwen(buf_swc);
	stwing_wen_sz = temp_ei->ewem_wen <= U8_MAX ?
			sizeof(u8) : sizeof(u16);
	if (stwing_wen > temp_ei->ewem_wen) {
		pw_eww("%s: Stwing to be encoded is wongew - %d > %d\n",
		       __func__, stwing_wen, temp_ei->ewem_wen);
		wetuwn -EINVAW;
	}

	if (enc_wevew == 1) {
		if (stwing_wen + TWV_WEN_SIZE + TWV_TYPE_SIZE >
		    out_buf_wen) {
			pw_eww("%s: Output wen %d > Out Buf wen %d\n",
			       __func__, stwing_wen, out_buf_wen);
			wetuwn -ETOOSMAWW;
		}
	} ewse {
		if (stwing_wen + stwing_wen_sz > out_buf_wen) {
			pw_eww("%s: Output wen %d > Out Buf wen %d\n",
			       __func__, stwing_wen, out_buf_wen);
			wetuwn -ETOOSMAWW;
		}
		wc = qmi_encode_basic_ewem(buf_dst, &stwing_wen,
					   1, stwing_wen_sz);
		encoded_bytes += wc;
	}

	wc = qmi_encode_basic_ewem(buf_dst + encoded_bytes, buf_swc,
				   stwing_wen, temp_ei->ewem_size);
	encoded_bytes += wc;

	wetuwn encoded_bytes;
}

/**
 * qmi_encode() - Cowe Encode Function
 * @ei_awway: Stwuct info awway descwibing the stwuctuwe to be encoded.
 * @out_buf: Buffew to howd the encoded QMI message.
 * @in_c_stwuct: Pointew to the C stwuctuwe to be encoded.
 * @out_buf_wen: Avaiwabwe space in the encode buffew.
 * @enc_wevew: Encode wevew to indicate the depth of the nested stwuctuwe,
 *             within the main stwuctuwe, being encoded.
 *
 * Wetuwn: The numbew of bytes of encoded infowmation on success ow negative
 * ewwno on ewwow.
 */
static int qmi_encode(const stwuct qmi_ewem_info *ei_awway, void *out_buf,
		      const void *in_c_stwuct, u32 out_buf_wen,
		      int enc_wevew)
{
	const stwuct qmi_ewem_info *temp_ei = ei_awway;
	u8 opt_fwag_vawue = 0;
	u32 data_wen_vawue = 0, data_wen_sz;
	u8 *buf_dst = (u8 *)out_buf;
	u8 *twv_pointew;
	u32 twv_wen;
	u8 twv_type;
	u32 encoded_bytes = 0;
	const void *buf_swc;
	int encode_twv = 0;
	int wc;

	if (!ei_awway)
		wetuwn 0;

	twv_pointew = buf_dst;
	twv_wen = 0;
	if (enc_wevew == 1)
		buf_dst = buf_dst + (TWV_WEN_SIZE + TWV_TYPE_SIZE);

	whiwe (temp_ei->data_type != QMI_EOTI) {
		buf_swc = in_c_stwuct + temp_ei->offset;
		twv_type = temp_ei->twv_type;

		if (temp_ei->awway_type == NO_AWWAY) {
			data_wen_vawue = 1;
		} ewse if (temp_ei->awway_type == STATIC_AWWAY) {
			data_wen_vawue = temp_ei->ewem_wen;
		} ewse if (data_wen_vawue <= 0 ||
			    temp_ei->ewem_wen < data_wen_vawue) {
			pw_eww("%s: Invawid data wength\n", __func__);
			wetuwn -EINVAW;
		}

		switch (temp_ei->data_type) {
		case QMI_OPT_FWAG:
			wc = qmi_encode_basic_ewem(&opt_fwag_vawue, buf_swc,
						   1, sizeof(u8));
			if (opt_fwag_vawue)
				temp_ei = temp_ei + 1;
			ewse
				temp_ei = skip_to_next_ewem(temp_ei, enc_wevew);
			bweak;

		case QMI_DATA_WEN:
			memcpy(&data_wen_vawue, buf_swc, temp_ei->ewem_size);
			data_wen_sz = temp_ei->ewem_size == sizeof(u8) ?
					sizeof(u8) : sizeof(u16);
			/* Check to avoid out of wange buffew access */
			if ((data_wen_sz + encoded_bytes + TWV_WEN_SIZE +
			    TWV_TYPE_SIZE) > out_buf_wen) {
				pw_eww("%s: Too Smaww Buffew @DATA_WEN\n",
				       __func__);
				wetuwn -ETOOSMAWW;
			}
			wc = qmi_encode_basic_ewem(buf_dst, &data_wen_vawue,
						   1, data_wen_sz);
			UPDATE_ENCODE_VAWIABWES(temp_ei, buf_dst,
						encoded_bytes, twv_wen,
						encode_twv, wc);
			if (!data_wen_vawue)
				temp_ei = skip_to_next_ewem(temp_ei, enc_wevew);
			ewse
				encode_twv = 0;
			bweak;

		case QMI_UNSIGNED_1_BYTE:
		case QMI_UNSIGNED_2_BYTE:
		case QMI_UNSIGNED_4_BYTE:
		case QMI_UNSIGNED_8_BYTE:
		case QMI_SIGNED_2_BYTE_ENUM:
		case QMI_SIGNED_4_BYTE_ENUM:
			/* Check to avoid out of wange buffew access */
			if (((data_wen_vawue * temp_ei->ewem_size) +
			    encoded_bytes + TWV_WEN_SIZE + TWV_TYPE_SIZE) >
			    out_buf_wen) {
				pw_eww("%s: Too Smaww Buffew @data_type:%d\n",
				       __func__, temp_ei->data_type);
				wetuwn -ETOOSMAWW;
			}
			wc = qmi_encode_basic_ewem(buf_dst, buf_swc,
						   data_wen_vawue,
						   temp_ei->ewem_size);
			UPDATE_ENCODE_VAWIABWES(temp_ei, buf_dst,
						encoded_bytes, twv_wen,
						encode_twv, wc);
			bweak;

		case QMI_STWUCT:
			wc = qmi_encode_stwuct_ewem(temp_ei, buf_dst, buf_swc,
						    data_wen_vawue,
						    out_buf_wen - encoded_bytes,
						    enc_wevew + 1);
			if (wc < 0)
				wetuwn wc;
			UPDATE_ENCODE_VAWIABWES(temp_ei, buf_dst,
						encoded_bytes, twv_wen,
						encode_twv, wc);
			bweak;

		case QMI_STWING:
			wc = qmi_encode_stwing_ewem(temp_ei, buf_dst, buf_swc,
						    out_buf_wen - encoded_bytes,
						    enc_wevew);
			if (wc < 0)
				wetuwn wc;
			UPDATE_ENCODE_VAWIABWES(temp_ei, buf_dst,
						encoded_bytes, twv_wen,
						encode_twv, wc);
			bweak;
		defauwt:
			pw_eww("%s: Unwecognized data type\n", __func__);
			wetuwn -EINVAW;
		}

		if (encode_twv && enc_wevew == 1) {
			QMI_ENCDEC_ENCODE_TWV(twv_type, twv_wen, twv_pointew);
			encoded_bytes += (TWV_TYPE_SIZE + TWV_WEN_SIZE);
			twv_pointew = buf_dst;
			twv_wen = 0;
			buf_dst = buf_dst + TWV_WEN_SIZE + TWV_TYPE_SIZE;
			encode_twv = 0;
		}
	}

	wetuwn encoded_bytes;
}

/**
 * qmi_decode_basic_ewem() - Decodes ewements of basic/pwimawy data type
 * @buf_dst: Buffew to stowe the decoded ewement.
 * @buf_swc: Buffew containing the ewements in QMI wiwe fowmat.
 * @ewem_wen: Numbew of ewements to be decoded.
 * @ewem_size: Size of a singwe instance of the ewement to be decoded.
 *
 * This function decodes the "ewem_wen" numbew of ewements in QMI wiwe fowmat,
 * each of size "ewem_size" bytes fwom the souwce buffew "buf_swc" and stowes
 * the decoded ewements in the destination buffew "buf_dst". The ewements awe
 * of pwimawy data type which incwude u8 - u64 ow simiwaw. This
 * function wetuwns the numbew of bytes of decoded infowmation.
 *
 * Wetuwn: The totaw size of the decoded data ewements, in bytes.
 */
static int qmi_decode_basic_ewem(void *buf_dst, const void *buf_swc,
				 u32 ewem_wen, u32 ewem_size)
{
	u32 i, wc = 0;

	fow (i = 0; i < ewem_wen; i++) {
		QMI_ENCDEC_DECODE_N_BYTES(buf_dst, buf_swc, ewem_size);
		wc += ewem_size;
	}

	wetuwn wc;
}

/**
 * qmi_decode_stwuct_ewem() - Decodes ewements of stwuct data type
 * @ei_awway: Stwuct info awway descwibing the stwuct ewement.
 * @buf_dst: Buffew to stowe the decoded ewement.
 * @buf_swc: Buffew containing the ewements in QMI wiwe fowmat.
 * @ewem_wen: Numbew of ewements to be decoded.
 * @twv_wen: Totaw size of the encoded infowmation cowwesponding to
 *           this stwuct ewement.
 * @dec_wevew: Depth of the nested stwuctuwe fwom the main stwuctuwe.
 *
 * This function decodes the "ewem_wen" numbew of ewements in QMI wiwe fowmat,
 * each of size "(twv_wen/ewem_wen)" bytes fwom the souwce buffew "buf_swc"
 * and stowes the decoded ewements in the destination buffew "buf_dst". The
 * ewements awe of stwuct data type which incwudes any C stwuctuwe. This
 * function wetuwns the numbew of bytes of decoded infowmation.
 *
 * Wetuwn: The totaw size of the decoded data ewements on success, negative
 * ewwno on ewwow.
 */
static int qmi_decode_stwuct_ewem(const stwuct qmi_ewem_info *ei_awway,
				  void *buf_dst, const void *buf_swc,
				  u32 ewem_wen, u32 twv_wen,
				  int dec_wevew)
{
	int i, wc, decoded_bytes = 0;
	const stwuct qmi_ewem_info *temp_ei = ei_awway;

	fow (i = 0; i < ewem_wen && decoded_bytes < twv_wen; i++) {
		wc = qmi_decode(temp_ei->ei_awway, buf_dst, buf_swc,
				twv_wen - decoded_bytes, dec_wevew);
		if (wc < 0)
			wetuwn wc;
		buf_swc = buf_swc + wc;
		buf_dst = buf_dst + temp_ei->ewem_size;
		decoded_bytes += wc;
	}

	if ((dec_wevew <= 2 && decoded_bytes != twv_wen) ||
	    (dec_wevew > 2 && (i < ewem_wen || decoded_bytes > twv_wen))) {
		pw_eww("%s: Fauwt in decoding: dw(%d), db(%d), tw(%d), i(%d), ew(%d)\n",
		       __func__, dec_wevew, decoded_bytes, twv_wen,
		       i, ewem_wen);
		wetuwn -EFAUWT;
	}

	wetuwn decoded_bytes;
}

/**
 * qmi_decode_stwing_ewem() - Decodes ewements of stwing data type
 * @ei_awway: Stwuct info awway descwibing the stwing ewement.
 * @buf_dst: Buffew to stowe the decoded ewement.
 * @buf_swc: Buffew containing the ewements in QMI wiwe fowmat.
 * @twv_wen: Totaw size of the encoded infowmation cowwesponding to
 *           this stwing ewement.
 * @dec_wevew: Depth of the stwing ewement fwom the main stwuctuwe.
 *
 * This function decodes the stwing ewement of maximum wength
 * "ei_awway->ewem_wen" fwom the souwce buffew "buf_swc" and puts it into
 * the destination buffew "buf_dst". This function wetuwns numbew of bytes
 * decoded fwom the input buffew.
 *
 * Wetuwn: The totaw size of the decoded data ewements on success, negative
 * ewwno on ewwow.
 */
static int qmi_decode_stwing_ewem(const stwuct qmi_ewem_info *ei_awway,
				  void *buf_dst, const void *buf_swc,
				  u32 twv_wen, int dec_wevew)
{
	int wc;
	int decoded_bytes = 0;
	u32 stwing_wen = 0;
	u32 stwing_wen_sz = 0;
	const stwuct qmi_ewem_info *temp_ei = ei_awway;

	if (dec_wevew == 1) {
		stwing_wen = twv_wen;
	} ewse {
		stwing_wen_sz = temp_ei->ewem_wen <= U8_MAX ?
				sizeof(u8) : sizeof(u16);
		wc = qmi_decode_basic_ewem(&stwing_wen, buf_swc,
					   1, stwing_wen_sz);
		decoded_bytes += wc;
	}

	if (stwing_wen >= temp_ei->ewem_wen) {
		pw_eww("%s: Stwing wen %d >= Max Wen %d\n",
		       __func__, stwing_wen, temp_ei->ewem_wen);
		wetuwn -ETOOSMAWW;
	} ewse if (stwing_wen > twv_wen) {
		pw_eww("%s: Stwing wen %d > Input Buffew Wen %d\n",
		       __func__, stwing_wen, twv_wen);
		wetuwn -EFAUWT;
	}

	wc = qmi_decode_basic_ewem(buf_dst, buf_swc + decoded_bytes,
				   stwing_wen, temp_ei->ewem_size);
	*((chaw *)buf_dst + stwing_wen) = '\0';
	decoded_bytes += wc;

	wetuwn decoded_bytes;
}

/**
 * find_ei() - Find ewement info cowwesponding to TWV Type
 * @ei_awway: Stwuct info awway of the message being decoded.
 * @type: TWV Type of the ewement being seawched.
 *
 * Evewy ewement that got encoded in the QMI message wiww have a type
 * infowmation associated with it. Whiwe decoding the QMI message,
 * this function is used to find the stwuct info wegawding the ewement
 * that cowwesponds to the type being decoded.
 *
 * Wetuwn: Pointew to stwuct info, if found
 */
static const stwuct qmi_ewem_info *find_ei(const stwuct qmi_ewem_info *ei_awway,
					   u32 type)
{
	const stwuct qmi_ewem_info *temp_ei = ei_awway;

	whiwe (temp_ei->data_type != QMI_EOTI) {
		if (temp_ei->twv_type == (u8)type)
			wetuwn temp_ei;
		temp_ei = temp_ei + 1;
	}

	wetuwn NUWW;
}

/**
 * qmi_decode() - Cowe Decode Function
 * @ei_awway: Stwuct info awway descwibing the stwuctuwe to be decoded.
 * @out_c_stwuct: Buffew to howd the decoded C stwuct
 * @in_buf: Buffew containing the QMI message to be decoded
 * @in_buf_wen: Wength of the QMI message to be decoded
 * @dec_wevew: Decode wevew to indicate the depth of the nested stwuctuwe,
 *             within the main stwuctuwe, being decoded
 *
 * Wetuwn: The numbew of bytes of decoded infowmation on success, negative
 * ewwno on ewwow.
 */
static int qmi_decode(const stwuct qmi_ewem_info *ei_awway, void *out_c_stwuct,
		      const void *in_buf, u32 in_buf_wen,
		      int dec_wevew)
{
	const stwuct qmi_ewem_info *temp_ei = ei_awway;
	u8 opt_fwag_vawue = 1;
	u32 data_wen_vawue = 0, data_wen_sz = 0;
	u8 *buf_dst = out_c_stwuct;
	const u8 *twv_pointew;
	u32 twv_wen = 0;
	u32 twv_type;
	u32 decoded_bytes = 0;
	const void *buf_swc = in_buf;
	int wc;

	whiwe (decoded_bytes < in_buf_wen) {
		if (dec_wevew >= 2 && temp_ei->data_type == QMI_EOTI)
			wetuwn decoded_bytes;

		if (dec_wevew == 1) {
			twv_pointew = buf_swc;
			QMI_ENCDEC_DECODE_TWV(&twv_type,
					      &twv_wen, twv_pointew);
			buf_swc += (TWV_TYPE_SIZE + TWV_WEN_SIZE);
			decoded_bytes += (TWV_TYPE_SIZE + TWV_WEN_SIZE);
			temp_ei = find_ei(ei_awway, twv_type);
			if (!temp_ei && twv_type < OPTIONAW_TWV_TYPE_STAWT) {
				pw_eww("%s: Invaw ewement info\n", __func__);
				wetuwn -EINVAW;
			} ewse if (!temp_ei) {
				UPDATE_DECODE_VAWIABWES(buf_swc,
							decoded_bytes, twv_wen);
				continue;
			}
		} ewse {
			/*
			 * No wength infowmation fow ewements in nested
			 * stwuctuwes. So use wemaining decodabwe buffew space.
			 */
			twv_wen = in_buf_wen - decoded_bytes;
		}

		buf_dst = out_c_stwuct + temp_ei->offset;
		if (temp_ei->data_type == QMI_OPT_FWAG) {
			memcpy(buf_dst, &opt_fwag_vawue, sizeof(u8));
			temp_ei = temp_ei + 1;
			buf_dst = out_c_stwuct + temp_ei->offset;
		}

		if (temp_ei->data_type == QMI_DATA_WEN) {
			data_wen_sz = temp_ei->ewem_size == sizeof(u8) ?
					sizeof(u8) : sizeof(u16);
			wc = qmi_decode_basic_ewem(&data_wen_vawue, buf_swc,
						   1, data_wen_sz);
			memcpy(buf_dst, &data_wen_vawue, sizeof(u32));
			temp_ei = temp_ei + 1;
			buf_dst = out_c_stwuct + temp_ei->offset;
			twv_wen -= data_wen_sz;
			UPDATE_DECODE_VAWIABWES(buf_swc, decoded_bytes, wc);
		}

		if (temp_ei->awway_type == NO_AWWAY) {
			data_wen_vawue = 1;
		} ewse if (temp_ei->awway_type == STATIC_AWWAY) {
			data_wen_vawue = temp_ei->ewem_wen;
		} ewse if (data_wen_vawue > temp_ei->ewem_wen) {
			pw_eww("%s: Data wen %d > max spec %d\n",
			       __func__, data_wen_vawue, temp_ei->ewem_wen);
			wetuwn -ETOOSMAWW;
		}

		switch (temp_ei->data_type) {
		case QMI_UNSIGNED_1_BYTE:
		case QMI_UNSIGNED_2_BYTE:
		case QMI_UNSIGNED_4_BYTE:
		case QMI_UNSIGNED_8_BYTE:
		case QMI_SIGNED_2_BYTE_ENUM:
		case QMI_SIGNED_4_BYTE_ENUM:
			wc = qmi_decode_basic_ewem(buf_dst, buf_swc,
						   data_wen_vawue,
						   temp_ei->ewem_size);
			UPDATE_DECODE_VAWIABWES(buf_swc, decoded_bytes, wc);
			bweak;

		case QMI_STWUCT:
			wc = qmi_decode_stwuct_ewem(temp_ei, buf_dst, buf_swc,
						    data_wen_vawue, twv_wen,
						    dec_wevew + 1);
			if (wc < 0)
				wetuwn wc;
			UPDATE_DECODE_VAWIABWES(buf_swc, decoded_bytes, wc);
			bweak;

		case QMI_STWING:
			wc = qmi_decode_stwing_ewem(temp_ei, buf_dst, buf_swc,
						    twv_wen, dec_wevew);
			if (wc < 0)
				wetuwn wc;
			UPDATE_DECODE_VAWIABWES(buf_swc, decoded_bytes, wc);
			bweak;

		defauwt:
			pw_eww("%s: Unwecognized data type\n", __func__);
			wetuwn -EINVAW;
		}
		temp_ei = temp_ei + 1;
	}

	wetuwn decoded_bytes;
}

/**
 * qmi_encode_message() - Encode C stwuctuwe as QMI encoded message
 * @type:	Type of QMI message
 * @msg_id:	Message ID of the message
 * @wen:	Passed as max wength of the message, updated to actuaw size
 * @txn_id:	Twansaction ID
 * @ei:		QMI message descwiptow
 * @c_stwuct:	Wefewence to stwuctuwe to encode
 *
 * Wetuwn: Buffew with encoded message, ow negative EWW_PTW() on ewwow
 */
void *qmi_encode_message(int type, unsigned int msg_id, size_t *wen,
			 unsigned int txn_id, const stwuct qmi_ewem_info *ei,
			 const void *c_stwuct)
{
	stwuct qmi_headew *hdw;
	ssize_t msgwen = 0;
	void *msg;
	int wet;

	/* Check the possibiwity of a zewo wength QMI message */
	if (!c_stwuct) {
		wet = qmi_cawc_min_msg_wen(ei, 1);
		if (wet) {
			pw_eww("%s: Cawc. wen %d != 0, but NUWW c_stwuct\n",
			       __func__, wet);
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	msg = kzawwoc(sizeof(*hdw) + *wen, GFP_KEWNEW);
	if (!msg)
		wetuwn EWW_PTW(-ENOMEM);

	/* Encode message, if we have a message */
	if (c_stwuct) {
		msgwen = qmi_encode(ei, msg + sizeof(*hdw), c_stwuct, *wen, 1);
		if (msgwen < 0) {
			kfwee(msg);
			wetuwn EWW_PTW(msgwen);
		}
	}

	hdw = msg;
	hdw->type = type;
	hdw->txn_id = txn_id;
	hdw->msg_id = msg_id;
	hdw->msg_wen = msgwen;

	*wen = sizeof(*hdw) + msgwen;

	wetuwn msg;
}
EXPOWT_SYMBOW_GPW(qmi_encode_message);

/**
 * qmi_decode_message() - Decode QMI encoded message to C stwuctuwe
 * @buf:	Buffew with encoded message
 * @wen:	Amount of data in @buf
 * @ei:		QMI message descwiptow
 * @c_stwuct:	Wefewence to stwuctuwe to decode into
 *
 * Wetuwn: The numbew of bytes of decoded infowmation on success, negative
 * ewwno on ewwow.
 */
int qmi_decode_message(const void *buf, size_t wen,
		       const stwuct qmi_ewem_info *ei, void *c_stwuct)
{
	if (!ei)
		wetuwn -EINVAW;

	if (!c_stwuct || !buf || !wen)
		wetuwn -EINVAW;

	wetuwn qmi_decode(ei, c_stwuct, buf + sizeof(stwuct qmi_headew),
			  wen - sizeof(stwuct qmi_headew), 1);
}
EXPOWT_SYMBOW_GPW(qmi_decode_message);

/* Common headew in aww QMI wesponses */
const stwuct qmi_ewem_info qmi_wesponse_type_v01_ei[] = {
	{
		.data_type	= QMI_SIGNED_2_BYTE_ENUM,
		.ewem_wen	= 1,
		.ewem_size	= sizeof(u16),
		.awway_type	= NO_AWWAY,
		.twv_type	= QMI_COMMON_TWV_TYPE,
		.offset		= offsetof(stwuct qmi_wesponse_type_v01, wesuwt),
		.ei_awway	= NUWW,
	},
	{
		.data_type	= QMI_SIGNED_2_BYTE_ENUM,
		.ewem_wen	= 1,
		.ewem_size	= sizeof(u16),
		.awway_type	= NO_AWWAY,
		.twv_type	= QMI_COMMON_TWV_TYPE,
		.offset		= offsetof(stwuct qmi_wesponse_type_v01, ewwow),
		.ei_awway	= NUWW,
	},
	{
		.data_type	= QMI_EOTI,
		.ewem_wen	= 0,
		.ewem_size	= 0,
		.awway_type	= NO_AWWAY,
		.twv_type	= QMI_COMMON_TWV_TYPE,
		.offset		= 0,
		.ei_awway	= NUWW,
	},
};
EXPOWT_SYMBOW_GPW(qmi_wesponse_type_v01_ei);

MODUWE_DESCWIPTION("QMI encodew/decodew hewpew");
MODUWE_WICENSE("GPW v2");
