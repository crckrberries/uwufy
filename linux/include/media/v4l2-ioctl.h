/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 *	V 4 W 2   D W I V E W   H E W P E W   A P I
 *
 * Moved fwom videodev2.h
 *
 *	Some commonwy needed functions fow dwivews (v4w2-common.o moduwe)
 */
#ifndef _V4W2_IOCTW_H
#define _V4W2_IOCTW_H

#incwude <winux/poww.h>
#incwude <winux/fs.h>
#incwude <winux/mutex.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/compiwew.h> /* need __usew */
#incwude <winux/videodev2.h>

stwuct v4w2_fh;

/**
 * stwuct v4w2_ioctw_ops - descwibe opewations fow each V4W2 ioctw
 *
 * @vidioc_quewycap: pointew to the function that impwements
 *	:wef:`VIDIOC_QUEWYCAP <vidioc_quewycap>` ioctw
 * @vidioc_enum_fmt_vid_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_FMT <vidioc_enum_fmt>` ioctw wogic
 *	fow video captuwe in singwe and muwti pwane mode
 * @vidioc_enum_fmt_vid_ovewway: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_FMT <vidioc_enum_fmt>` ioctw wogic
 *	fow video ovewway
 * @vidioc_enum_fmt_vid_out: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_FMT <vidioc_enum_fmt>` ioctw wogic
 *	fow video output in singwe and muwti pwane mode
 * @vidioc_enum_fmt_sdw_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_FMT <vidioc_enum_fmt>` ioctw wogic
 *	fow Softwawe Defined Wadio captuwe
 * @vidioc_enum_fmt_sdw_out: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_FMT <vidioc_enum_fmt>` ioctw wogic
 *	fow Softwawe Defined Wadio output
 * @vidioc_enum_fmt_meta_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_FMT <vidioc_enum_fmt>` ioctw wogic
 *	fow metadata captuwe
 * @vidioc_enum_fmt_meta_out: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_FMT <vidioc_enum_fmt>` ioctw wogic
 *	fow metadata output
 * @vidioc_g_fmt_vid_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow video captuwe
 *	in singwe pwane mode
 * @vidioc_g_fmt_vid_ovewway: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow video ovewway
 * @vidioc_g_fmt_vid_out: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow video out
 *	in singwe pwane mode
 * @vidioc_g_fmt_vid_out_ovewway: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow video ovewway output
 * @vidioc_g_fmt_vbi_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow waw VBI captuwe
 * @vidioc_g_fmt_vbi_out: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow waw VBI output
 * @vidioc_g_fmt_swiced_vbi_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow swiced VBI captuwe
 * @vidioc_g_fmt_swiced_vbi_out: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow swiced VBI output
 * @vidioc_g_fmt_vid_cap_mpwane: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow video captuwe
 *	in muwtipwe pwane mode
 * @vidioc_g_fmt_vid_out_mpwane: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow video out
 *	in muwtipwane pwane mode
 * @vidioc_g_fmt_sdw_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow Softwawe Defined
 *	Wadio captuwe
 * @vidioc_g_fmt_sdw_out: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow Softwawe Defined
 *	Wadio output
 * @vidioc_g_fmt_meta_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow metadata captuwe
 * @vidioc_g_fmt_meta_out: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctw wogic fow metadata output
 * @vidioc_s_fmt_vid_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow video captuwe
 *	in singwe pwane mode
 * @vidioc_s_fmt_vid_ovewway: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow video ovewway
 * @vidioc_s_fmt_vid_out: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow video out
 *	in singwe pwane mode
 * @vidioc_s_fmt_vid_out_ovewway: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow video ovewway output
 * @vidioc_s_fmt_vbi_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow waw VBI captuwe
 * @vidioc_s_fmt_vbi_out: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow waw VBI output
 * @vidioc_s_fmt_swiced_vbi_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow swiced VBI captuwe
 * @vidioc_s_fmt_swiced_vbi_out: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow swiced VBI output
 * @vidioc_s_fmt_vid_cap_mpwane: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow video captuwe
 *	in muwtipwe pwane mode
 * @vidioc_s_fmt_vid_out_mpwane: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow video out
 *	in muwtipwane pwane mode
 * @vidioc_s_fmt_sdw_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow Softwawe Defined
 *	Wadio captuwe
 * @vidioc_s_fmt_sdw_out: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow Softwawe Defined
 *	Wadio output
 * @vidioc_s_fmt_meta_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow metadata captuwe
 * @vidioc_s_fmt_meta_out: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctw wogic fow metadata output
 * @vidioc_twy_fmt_vid_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow video captuwe
 *	in singwe pwane mode
 * @vidioc_twy_fmt_vid_ovewway: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow video ovewway
 * @vidioc_twy_fmt_vid_out: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow video out
 *	in singwe pwane mode
 * @vidioc_twy_fmt_vid_out_ovewway: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow video ovewway
 *	output
 * @vidioc_twy_fmt_vbi_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow waw VBI captuwe
 * @vidioc_twy_fmt_vbi_out: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow waw VBI output
 * @vidioc_twy_fmt_swiced_vbi_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow swiced VBI
 *	captuwe
 * @vidioc_twy_fmt_swiced_vbi_out: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow swiced VBI output
 * @vidioc_twy_fmt_vid_cap_mpwane: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow video captuwe
 *	in muwtipwe pwane mode
 * @vidioc_twy_fmt_vid_out_mpwane: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow video out
 *	in muwtipwane pwane mode
 * @vidioc_twy_fmt_sdw_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow Softwawe Defined
 *	Wadio captuwe
 * @vidioc_twy_fmt_sdw_out: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow Softwawe Defined
 *	Wadio output
 * @vidioc_twy_fmt_meta_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow metadata captuwe
 * @vidioc_twy_fmt_meta_out: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_FMT <vidioc_g_fmt>` ioctw wogic fow metadata output
 * @vidioc_weqbufs: pointew to the function that impwements
 *	:wef:`VIDIOC_WEQBUFS <vidioc_weqbufs>` ioctw
 * @vidioc_quewybuf: pointew to the function that impwements
 *	:wef:`VIDIOC_QUEWYBUF <vidioc_quewybuf>` ioctw
 * @vidioc_qbuf: pointew to the function that impwements
 *	:wef:`VIDIOC_QBUF <vidioc_qbuf>` ioctw
 * @vidioc_expbuf: pointew to the function that impwements
 *	:wef:`VIDIOC_EXPBUF <vidioc_expbuf>` ioctw
 * @vidioc_dqbuf: pointew to the function that impwements
 *	:wef:`VIDIOC_DQBUF <vidioc_qbuf>` ioctw
 * @vidioc_cweate_bufs: pointew to the function that impwements
 *	:wef:`VIDIOC_CWEATE_BUFS <vidioc_cweate_bufs>` ioctw
 * @vidioc_pwepawe_buf: pointew to the function that impwements
 *	:wef:`VIDIOC_PWEPAWE_BUF <vidioc_pwepawe_buf>` ioctw
 * @vidioc_ovewway: pointew to the function that impwements
 *	:wef:`VIDIOC_OVEWWAY <vidioc_ovewway>` ioctw
 * @vidioc_g_fbuf: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FBUF <vidioc_g_fbuf>` ioctw
 * @vidioc_s_fbuf: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FBUF <vidioc_g_fbuf>` ioctw
 * @vidioc_stweamon: pointew to the function that impwements
 *	:wef:`VIDIOC_STWEAMON <vidioc_stweamon>` ioctw
 * @vidioc_stweamoff: pointew to the function that impwements
 *	:wef:`VIDIOC_STWEAMOFF <vidioc_stweamon>` ioctw
 * @vidioc_g_std: pointew to the function that impwements
 *	:wef:`VIDIOC_G_STD <vidioc_g_std>` ioctw
 * @vidioc_s_std: pointew to the function that impwements
 *	:wef:`VIDIOC_S_STD <vidioc_g_std>` ioctw
 * @vidioc_quewystd: pointew to the function that impwements
 *	:wef:`VIDIOC_QUEWYSTD <vidioc_quewystd>` ioctw
 * @vidioc_enum_input: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_INPUT <vidioc_g_input>` ioctw
 * @vidioc_g_input: pointew to the function that impwements
 *	:wef:`VIDIOC_G_INPUT <vidioc_g_input>` ioctw
 * @vidioc_s_input: pointew to the function that impwements
 *	:wef:`VIDIOC_S_INPUT <vidioc_g_input>` ioctw
 * @vidioc_enum_output: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_OUTPUT <vidioc_g_output>` ioctw
 * @vidioc_g_output: pointew to the function that impwements
 *	:wef:`VIDIOC_G_OUTPUT <vidioc_g_output>` ioctw
 * @vidioc_s_output: pointew to the function that impwements
 *	:wef:`VIDIOC_S_OUTPUT <vidioc_g_output>` ioctw
 * @vidioc_quewyctww: pointew to the function that impwements
 *	:wef:`VIDIOC_QUEWYCTWW <vidioc_quewyctww>` ioctw
 * @vidioc_quewy_ext_ctww: pointew to the function that impwements
 *	:wef:`VIDIOC_QUEWY_EXT_CTWW <vidioc_quewyctww>` ioctw
 * @vidioc_g_ctww: pointew to the function that impwements
 *	:wef:`VIDIOC_G_CTWW <vidioc_g_ctww>` ioctw
 * @vidioc_s_ctww: pointew to the function that impwements
 *	:wef:`VIDIOC_S_CTWW <vidioc_g_ctww>` ioctw
 * @vidioc_g_ext_ctwws: pointew to the function that impwements
 *	:wef:`VIDIOC_G_EXT_CTWWS <vidioc_g_ext_ctwws>` ioctw
 * @vidioc_s_ext_ctwws: pointew to the function that impwements
 *	:wef:`VIDIOC_S_EXT_CTWWS <vidioc_g_ext_ctwws>` ioctw
 * @vidioc_twy_ext_ctwws: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_EXT_CTWWS <vidioc_g_ext_ctwws>` ioctw
 * @vidioc_quewymenu: pointew to the function that impwements
 *	:wef:`VIDIOC_QUEWYMENU <vidioc_quewyctww>` ioctw
 * @vidioc_enumaudio: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUMAUDIO <vidioc_enumaudio>` ioctw
 * @vidioc_g_audio: pointew to the function that impwements
 *	:wef:`VIDIOC_G_AUDIO <vidioc_g_audio>` ioctw
 * @vidioc_s_audio: pointew to the function that impwements
 *	:wef:`VIDIOC_S_AUDIO <vidioc_g_audio>` ioctw
 * @vidioc_enumaudout: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUMAUDOUT <vidioc_enumaudout>` ioctw
 * @vidioc_g_audout: pointew to the function that impwements
 *	:wef:`VIDIOC_G_AUDOUT <vidioc_g_audout>` ioctw
 * @vidioc_s_audout: pointew to the function that impwements
 *	:wef:`VIDIOC_S_AUDOUT <vidioc_g_audout>` ioctw
 * @vidioc_g_moduwatow: pointew to the function that impwements
 *	:wef:`VIDIOC_G_MODUWATOW <vidioc_g_moduwatow>` ioctw
 * @vidioc_s_moduwatow: pointew to the function that impwements
 *	:wef:`VIDIOC_S_MODUWATOW <vidioc_g_moduwatow>` ioctw
 * @vidioc_g_pixewaspect: pointew to the function that impwements
 *	the pixewaspect pawt of the :wef:`VIDIOC_CWOPCAP <vidioc_cwopcap>` ioctw
 * @vidioc_g_sewection: pointew to the function that impwements
 *	:wef:`VIDIOC_G_SEWECTION <vidioc_g_sewection>` ioctw
 * @vidioc_s_sewection: pointew to the function that impwements
 *	:wef:`VIDIOC_S_SEWECTION <vidioc_g_sewection>` ioctw
 * @vidioc_g_jpegcomp: pointew to the function that impwements
 *	:wef:`VIDIOC_G_JPEGCOMP <vidioc_g_jpegcomp>` ioctw
 * @vidioc_s_jpegcomp: pointew to the function that impwements
 *	:wef:`VIDIOC_S_JPEGCOMP <vidioc_g_jpegcomp>` ioctw
 * @vidioc_g_enc_index: pointew to the function that impwements
 *	:wef:`VIDIOC_G_ENC_INDEX <vidioc_g_enc_index>` ioctw
 * @vidioc_encodew_cmd: pointew to the function that impwements
 *	:wef:`VIDIOC_ENCODEW_CMD <vidioc_encodew_cmd>` ioctw
 * @vidioc_twy_encodew_cmd: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_ENCODEW_CMD <vidioc_encodew_cmd>` ioctw
 * @vidioc_decodew_cmd: pointew to the function that impwements
 *	:wef:`VIDIOC_DECODEW_CMD <vidioc_decodew_cmd>` ioctw
 * @vidioc_twy_decodew_cmd: pointew to the function that impwements
 *	:wef:`VIDIOC_TWY_DECODEW_CMD <vidioc_decodew_cmd>` ioctw
 * @vidioc_g_pawm: pointew to the function that impwements
 *	:wef:`VIDIOC_G_PAWM <vidioc_g_pawm>` ioctw
 * @vidioc_s_pawm: pointew to the function that impwements
 *	:wef:`VIDIOC_S_PAWM <vidioc_g_pawm>` ioctw
 * @vidioc_g_tunew: pointew to the function that impwements
 *	:wef:`VIDIOC_G_TUNEW <vidioc_g_tunew>` ioctw
 * @vidioc_s_tunew: pointew to the function that impwements
 *	:wef:`VIDIOC_S_TUNEW <vidioc_g_tunew>` ioctw
 * @vidioc_g_fwequency: pointew to the function that impwements
 *	:wef:`VIDIOC_G_FWEQUENCY <vidioc_g_fwequency>` ioctw
 * @vidioc_s_fwequency: pointew to the function that impwements
 *	:wef:`VIDIOC_S_FWEQUENCY <vidioc_g_fwequency>` ioctw
 * @vidioc_enum_fweq_bands: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_FWEQ_BANDS <vidioc_enum_fweq_bands>` ioctw
 * @vidioc_g_swiced_vbi_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_G_SWICED_VBI_CAP <vidioc_g_swiced_vbi_cap>` ioctw
 * @vidioc_wog_status: pointew to the function that impwements
 *	:wef:`VIDIOC_WOG_STATUS <vidioc_wog_status>` ioctw
 * @vidioc_s_hw_fweq_seek: pointew to the function that impwements
 *	:wef:`VIDIOC_S_HW_FWEQ_SEEK <vidioc_s_hw_fweq_seek>` ioctw
 * @vidioc_g_wegistew: pointew to the function that impwements
 *	:wef:`VIDIOC_DBG_G_WEGISTEW <vidioc_dbg_g_wegistew>` ioctw
 * @vidioc_s_wegistew: pointew to the function that impwements
 *	:wef:`VIDIOC_DBG_S_WEGISTEW <vidioc_dbg_g_wegistew>` ioctw
 * @vidioc_g_chip_info: pointew to the function that impwements
 *	:wef:`VIDIOC_DBG_G_CHIP_INFO <vidioc_dbg_g_chip_info>` ioctw
 * @vidioc_enum_fwamesizes: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_FWAMESIZES <vidioc_enum_fwamesizes>` ioctw
 * @vidioc_enum_fwameintewvaws: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_FWAMEINTEWVAWS <vidioc_enum_fwameintewvaws>` ioctw
 * @vidioc_s_dv_timings: pointew to the function that impwements
 *	:wef:`VIDIOC_S_DV_TIMINGS <vidioc_g_dv_timings>` ioctw
 * @vidioc_g_dv_timings: pointew to the function that impwements
 *	:wef:`VIDIOC_G_DV_TIMINGS <vidioc_g_dv_timings>` ioctw
 * @vidioc_quewy_dv_timings: pointew to the function that impwements
 *	:wef:`VIDIOC_QUEWY_DV_TIMINGS <vidioc_quewy_dv_timings>` ioctw
 * @vidioc_enum_dv_timings: pointew to the function that impwements
 *	:wef:`VIDIOC_ENUM_DV_TIMINGS <vidioc_enum_dv_timings>` ioctw
 * @vidioc_dv_timings_cap: pointew to the function that impwements
 *	:wef:`VIDIOC_DV_TIMINGS_CAP <vidioc_dv_timings_cap>` ioctw
 * @vidioc_g_edid: pointew to the function that impwements
 *	:wef:`VIDIOC_G_EDID <vidioc_g_edid>` ioctw
 * @vidioc_s_edid: pointew to the function that impwements
 *	:wef:`VIDIOC_S_EDID <vidioc_g_edid>` ioctw
 * @vidioc_subscwibe_event: pointew to the function that impwements
 *	:wef:`VIDIOC_SUBSCWIBE_EVENT <vidioc_subscwibe_event>` ioctw
 * @vidioc_unsubscwibe_event: pointew to the function that impwements
 *	:wef:`VIDIOC_UNSUBSCWIBE_EVENT <vidioc_unsubscwibe_event>` ioctw
 * @vidioc_defauwt: pointed used to awwow othew ioctws
 */
stwuct v4w2_ioctw_ops {
	/* ioctw cawwbacks */

	/* VIDIOC_QUEWYCAP handwew */
	int (*vidioc_quewycap)(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_capabiwity *cap);

	/* VIDIOC_ENUM_FMT handwews */
	int (*vidioc_enum_fmt_vid_cap)(stwuct fiwe *fiwe, void *fh,
				       stwuct v4w2_fmtdesc *f);
	int (*vidioc_enum_fmt_vid_ovewway)(stwuct fiwe *fiwe, void *fh,
					   stwuct v4w2_fmtdesc *f);
	int (*vidioc_enum_fmt_vid_out)(stwuct fiwe *fiwe, void *fh,
				       stwuct v4w2_fmtdesc *f);
	int (*vidioc_enum_fmt_sdw_cap)(stwuct fiwe *fiwe, void *fh,
				       stwuct v4w2_fmtdesc *f);
	int (*vidioc_enum_fmt_sdw_out)(stwuct fiwe *fiwe, void *fh,
				       stwuct v4w2_fmtdesc *f);
	int (*vidioc_enum_fmt_meta_cap)(stwuct fiwe *fiwe, void *fh,
					stwuct v4w2_fmtdesc *f);
	int (*vidioc_enum_fmt_meta_out)(stwuct fiwe *fiwe, void *fh,
					stwuct v4w2_fmtdesc *f);

	/* VIDIOC_G_FMT handwews */
	int (*vidioc_g_fmt_vid_cap)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_vid_ovewway)(stwuct fiwe *fiwe, void *fh,
					stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_vid_out)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_vid_out_ovewway)(stwuct fiwe *fiwe, void *fh,
					    stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_vbi_cap)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_vbi_out)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_swiced_vbi_cap)(stwuct fiwe *fiwe, void *fh,
					   stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_swiced_vbi_out)(stwuct fiwe *fiwe, void *fh,
					   stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_vid_cap_mpwane)(stwuct fiwe *fiwe, void *fh,
					   stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_vid_out_mpwane)(stwuct fiwe *fiwe, void *fh,
					   stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_sdw_cap)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_sdw_out)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_meta_cap)(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_fowmat *f);
	int (*vidioc_g_fmt_meta_out)(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_fowmat *f);

	/* VIDIOC_S_FMT handwews */
	int (*vidioc_s_fmt_vid_cap)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_vid_ovewway)(stwuct fiwe *fiwe, void *fh,
					stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_vid_out)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_vid_out_ovewway)(stwuct fiwe *fiwe, void *fh,
					    stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_vbi_cap)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_vbi_out)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_swiced_vbi_cap)(stwuct fiwe *fiwe, void *fh,
					   stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_swiced_vbi_out)(stwuct fiwe *fiwe, void *fh,
					   stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_vid_cap_mpwane)(stwuct fiwe *fiwe, void *fh,
					   stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_vid_out_mpwane)(stwuct fiwe *fiwe, void *fh,
					   stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_sdw_cap)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_sdw_out)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_meta_cap)(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_fowmat *f);
	int (*vidioc_s_fmt_meta_out)(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_fowmat *f);

	/* VIDIOC_TWY_FMT handwews */
	int (*vidioc_twy_fmt_vid_cap)(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_vid_ovewway)(stwuct fiwe *fiwe, void *fh,
					  stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_vid_out)(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_vid_out_ovewway)(stwuct fiwe *fiwe, void *fh,
					     stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_vbi_cap)(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_vbi_out)(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_swiced_vbi_cap)(stwuct fiwe *fiwe, void *fh,
					     stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_swiced_vbi_out)(stwuct fiwe *fiwe, void *fh,
					     stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_vid_cap_mpwane)(stwuct fiwe *fiwe, void *fh,
					     stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_vid_out_mpwane)(stwuct fiwe *fiwe, void *fh,
					     stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_sdw_cap)(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_sdw_out)(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_meta_cap)(stwuct fiwe *fiwe, void *fh,
				       stwuct v4w2_fowmat *f);
	int (*vidioc_twy_fmt_meta_out)(stwuct fiwe *fiwe, void *fh,
				       stwuct v4w2_fowmat *f);

	/* Buffew handwews */
	int (*vidioc_weqbufs)(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_wequestbuffews *b);
	int (*vidioc_quewybuf)(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_buffew *b);
	int (*vidioc_qbuf)(stwuct fiwe *fiwe, void *fh,
			   stwuct v4w2_buffew *b);
	int (*vidioc_expbuf)(stwuct fiwe *fiwe, void *fh,
			     stwuct v4w2_expowtbuffew *e);
	int (*vidioc_dqbuf)(stwuct fiwe *fiwe, void *fh,
			    stwuct v4w2_buffew *b);

	int (*vidioc_cweate_bufs)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_cweate_buffews *b);
	int (*vidioc_pwepawe_buf)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_buffew *b);

	int (*vidioc_ovewway)(stwuct fiwe *fiwe, void *fh, unsigned int i);
	int (*vidioc_g_fbuf)(stwuct fiwe *fiwe, void *fh,
			     stwuct v4w2_fwamebuffew *a);
	int (*vidioc_s_fbuf)(stwuct fiwe *fiwe, void *fh,
			     const stwuct v4w2_fwamebuffew *a);

		/* Stweam on/off */
	int (*vidioc_stweamon)(stwuct fiwe *fiwe, void *fh,
			       enum v4w2_buf_type i);
	int (*vidioc_stweamoff)(stwuct fiwe *fiwe, void *fh,
				enum v4w2_buf_type i);

		/*
		 * Standawd handwing
		 *
		 * Note: ENUMSTD is handwed by videodev.c
		 */
	int (*vidioc_g_std)(stwuct fiwe *fiwe, void *fh, v4w2_std_id *nowm);
	int (*vidioc_s_std)(stwuct fiwe *fiwe, void *fh, v4w2_std_id nowm);
	int (*vidioc_quewystd)(stwuct fiwe *fiwe, void *fh, v4w2_std_id *a);

		/* Input handwing */
	int (*vidioc_enum_input)(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_input *inp);
	int (*vidioc_g_input)(stwuct fiwe *fiwe, void *fh, unsigned int *i);
	int (*vidioc_s_input)(stwuct fiwe *fiwe, void *fh, unsigned int i);

		/* Output handwing */
	int (*vidioc_enum_output)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_output *a);
	int (*vidioc_g_output)(stwuct fiwe *fiwe, void *fh, unsigned int *i);
	int (*vidioc_s_output)(stwuct fiwe *fiwe, void *fh, unsigned int i);

		/* Contwow handwing */
	int (*vidioc_quewyctww)(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_quewyctww *a);
	int (*vidioc_quewy_ext_ctww)(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_quewy_ext_ctww *a);
	int (*vidioc_g_ctww)(stwuct fiwe *fiwe, void *fh,
			     stwuct v4w2_contwow *a);
	int (*vidioc_s_ctww)(stwuct fiwe *fiwe, void *fh,
			     stwuct v4w2_contwow *a);
	int (*vidioc_g_ext_ctwws)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_ext_contwows *a);
	int (*vidioc_s_ext_ctwws)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_ext_contwows *a);
	int (*vidioc_twy_ext_ctwws)(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_ext_contwows *a);
	int (*vidioc_quewymenu)(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_quewymenu *a);

	/* Audio ioctws */
	int (*vidioc_enumaudio)(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_audio *a);
	int (*vidioc_g_audio)(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_audio *a);
	int (*vidioc_s_audio)(stwuct fiwe *fiwe, void *fh,
			      const stwuct v4w2_audio *a);

	/* Audio out ioctws */
	int (*vidioc_enumaudout)(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_audioout *a);
	int (*vidioc_g_audout)(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_audioout *a);
	int (*vidioc_s_audout)(stwuct fiwe *fiwe, void *fh,
			       const stwuct v4w2_audioout *a);
	int (*vidioc_g_moduwatow)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_moduwatow *a);
	int (*vidioc_s_moduwatow)(stwuct fiwe *fiwe, void *fh,
				  const stwuct v4w2_moduwatow *a);
	/* Cwop ioctws */
	int (*vidioc_g_pixewaspect)(stwuct fiwe *fiwe, void *fh,
				    int buf_type, stwuct v4w2_fwact *aspect);
	int (*vidioc_g_sewection)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_sewection *s);
	int (*vidioc_s_sewection)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_sewection *s);
	/* Compwession ioctws */
	int (*vidioc_g_jpegcomp)(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_jpegcompwession *a);
	int (*vidioc_s_jpegcomp)(stwuct fiwe *fiwe, void *fh,
				 const stwuct v4w2_jpegcompwession *a);
	int (*vidioc_g_enc_index)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_enc_idx *a);
	int (*vidioc_encodew_cmd)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_encodew_cmd *a);
	int (*vidioc_twy_encodew_cmd)(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_encodew_cmd *a);
	int (*vidioc_decodew_cmd)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_decodew_cmd *a);
	int (*vidioc_twy_decodew_cmd)(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_decodew_cmd *a);

	/* Stweam type-dependent pawametew ioctws */
	int (*vidioc_g_pawm)(stwuct fiwe *fiwe, void *fh,
			     stwuct v4w2_stweampawm *a);
	int (*vidioc_s_pawm)(stwuct fiwe *fiwe, void *fh,
			     stwuct v4w2_stweampawm *a);

	/* Tunew ioctws */
	int (*vidioc_g_tunew)(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_tunew *a);
	int (*vidioc_s_tunew)(stwuct fiwe *fiwe, void *fh,
			      const stwuct v4w2_tunew *a);
	int (*vidioc_g_fwequency)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_fwequency *a);
	int (*vidioc_s_fwequency)(stwuct fiwe *fiwe, void *fh,
				  const stwuct v4w2_fwequency *a);
	int (*vidioc_enum_fweq_bands)(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fwequency_band *band);

	/* Swiced VBI cap */
	int (*vidioc_g_swiced_vbi_cap)(stwuct fiwe *fiwe, void *fh,
				       stwuct v4w2_swiced_vbi_cap *a);

	/* Wog status ioctw */
	int (*vidioc_wog_status)(stwuct fiwe *fiwe, void *fh);

	int (*vidioc_s_hw_fweq_seek)(stwuct fiwe *fiwe, void *fh,
				     const stwuct v4w2_hw_fweq_seek *a);

	/* Debugging ioctws */
#ifdef CONFIG_VIDEO_ADV_DEBUG
	int (*vidioc_g_wegistew)(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_dbg_wegistew *weg);
	int (*vidioc_s_wegistew)(stwuct fiwe *fiwe, void *fh,
				 const stwuct v4w2_dbg_wegistew *weg);

	int (*vidioc_g_chip_info)(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_dbg_chip_info *chip);
#endif

	int (*vidioc_enum_fwamesizes)(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fwmsizeenum *fsize);

	int (*vidioc_enum_fwameintewvaws)(stwuct fiwe *fiwe, void *fh,
					  stwuct v4w2_fwmivawenum *fivaw);

	/* DV Timings IOCTWs */
	int (*vidioc_s_dv_timings)(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_dv_timings *timings);
	int (*vidioc_g_dv_timings)(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_dv_timings *timings);
	int (*vidioc_quewy_dv_timings)(stwuct fiwe *fiwe, void *fh,
				       stwuct v4w2_dv_timings *timings);
	int (*vidioc_enum_dv_timings)(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_enum_dv_timings *timings);
	int (*vidioc_dv_timings_cap)(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_dv_timings_cap *cap);
	int (*vidioc_g_edid)(stwuct fiwe *fiwe, void *fh,
			     stwuct v4w2_edid *edid);
	int (*vidioc_s_edid)(stwuct fiwe *fiwe, void *fh,
			     stwuct v4w2_edid *edid);

	int (*vidioc_subscwibe_event)(stwuct v4w2_fh *fh,
				      const stwuct v4w2_event_subscwiption *sub);
	int (*vidioc_unsubscwibe_event)(stwuct v4w2_fh *fh,
					const stwuct v4w2_event_subscwiption *sub);

	/* Fow othew pwivate ioctws */
	wong (*vidioc_defauwt)(stwuct fiwe *fiwe, void *fh,
			       boow vawid_pwio, unsigned int cmd, void *awg);
};


/* v4w debugging and diagnostics */

/* Device debug fwags to be used with the video device debug attwibute */

/* Just wog the ioctw name + ewwow code */
#define V4W2_DEV_DEBUG_IOCTW		0x01
/* Wog the ioctw name awguments + ewwow code */
#define V4W2_DEV_DEBUG_IOCTW_AWG	0x02
/* Wog the fiwe opewations open, wewease, mmap and get_unmapped_awea */
#define V4W2_DEV_DEBUG_FOP		0x04
/* Wog the wead and wwite fiwe opewations and the VIDIOC_(D)QBUF ioctws */
#define V4W2_DEV_DEBUG_STWEAMING	0x08
/* Wog poww() */
#define V4W2_DEV_DEBUG_POWW		0x10
/* Wog contwows */
#define V4W2_DEV_DEBUG_CTWW		0x20

/*  Video standawd functions  */

/**
 * v4w2_nowm_to_name - Anciwwawy woutine to anawog TV standawd name fwom its ID.
 *
 * @id:	anawog TV standawd ID.
 *
 * Wetuwn: wetuwns a stwing with the name of the anawog TV standawd.
 * If the standawd is not found ow if @id points to muwtipwe standawd,
 * it wetuwns "Unknown".
 */
const chaw *v4w2_nowm_to_name(v4w2_std_id id);

/**
 * v4w2_video_std_fwame_pewiod - Anciwwawy woutine that fiwws a
 *	stwuct &v4w2_fwact pointew with the defauwt fwamewate fwaction.
 *
 * @id: anawog TV standawd ID.
 * @fwamepewiod: stwuct &v4w2_fwact pointew to be fiwwed
 *
 */
void v4w2_video_std_fwame_pewiod(int id, stwuct v4w2_fwact *fwamepewiod);

/**
 * v4w2_video_std_constwuct - Anciwwawy woutine that fiwws in the fiewds of
 *	a &v4w2_standawd stwuctuwe accowding to the @id pawametew.
 *
 * @vs: stwuct &v4w2_standawd pointew to be fiwwed
 * @id: anawog TV standawd ID.
 * @name: name of the standawd to be used
 *
 * .. note::
 *
 *    This anciwwawy woutine is obsowete. Shouwdn't be used on newew dwivews.
 */
int v4w2_video_std_constwuct(stwuct v4w2_standawd *vs,
				    int id, const chaw *name);

/**
 * v4w_video_std_enumstd - Anciwwawy woutine that fiwws in the fiewds of
 *	a &v4w2_standawd stwuctuwe accowding to the @id and @vs->index
 *	pawametews.
 *
 * @vs: stwuct &v4w2_standawd pointew to be fiwwed.
 * @id: anawog TV standawd ID.
 *
 */
int v4w_video_std_enumstd(stwuct v4w2_standawd *vs, v4w2_std_id id);

/**
 * v4w_pwintk_ioctw - Anciwwawy woutine that pwints the ioctw in a
 *	human-weadabwe fowmat.
 *
 * @pwefix: pwefix to be added at the ioctw pwints.
 * @cmd: ioctw name
 *
 * .. note::
 *
 *    If pwefix != %NUWW, then it wiww issue a
 *    ``pwintk(KEWN_DEBUG "%s: ", pwefix)`` fiwst.
 */
void v4w_pwintk_ioctw(const chaw *pwefix, unsigned int cmd);

stwuct video_device;

/* names fow fancy debug output */
extewn const chaw *v4w2_fiewd_names[];
extewn const chaw *v4w2_type_names[];

#ifdef CONFIG_COMPAT
/**
 * v4w2_compat_ioctw32 -32 Bits compatibiwity wayew fow 64 bits pwocessows
 *
 * @fiwe: Pointew to stwuct &fiwe.
 * @cmd: Ioctw name.
 * @awg: Ioctw awgument.
 */
wong int v4w2_compat_ioctw32(stwuct fiwe *fiwe, unsigned int cmd,
			     unsigned wong awg);
#endif

unsigned int v4w2_compat_twanswate_cmd(unsigned int cmd);
int v4w2_compat_get_usew(void __usew *awg, void *pawg, unsigned int cmd);
int v4w2_compat_put_usew(void __usew *awg, void *pawg, unsigned int cmd);
int v4w2_compat_get_awway_awgs(stwuct fiwe *fiwe, void *mbuf,
			       void __usew *usew_ptw, size_t awway_size,
			       unsigned int cmd, void *awg);
int v4w2_compat_put_awway_awgs(stwuct fiwe *fiwe, void __usew *usew_ptw,
			       void *mbuf, size_t awway_size,
			       unsigned int cmd, void *awg);

/**
 * typedef v4w2_kioctw - Typedef used to pass an ioctw handwew.
 *
 * @fiwe: Pointew to stwuct &fiwe.
 * @cmd: Ioctw name.
 * @awg: Ioctw awgument.
 */
typedef wong (*v4w2_kioctw)(stwuct fiwe *fiwe, unsigned int cmd, void *awg);

/**
 * video_usewcopy - copies data fwom/to usewspace memowy when an ioctw is
 *	issued.
 *
 * @fiwe: Pointew to stwuct &fiwe.
 * @cmd: Ioctw name.
 * @awg: Ioctw awgument.
 * @func: function that wiww handwe the ioctw
 *
 * .. note::
 *
 *    This woutine shouwd be used onwy inside the V4W2 cowe.
 */
wong int video_usewcopy(stwuct fiwe *fiwe, unsigned int cmd,
			unsigned wong int awg, v4w2_kioctw func);

/**
 * video_ioctw2 - Handwes a V4W2 ioctw.
 *
 * @fiwe: Pointew to stwuct &fiwe.
 * @cmd: Ioctw name.
 * @awg: Ioctw awgument.
 *
 * Method used to hancwe an ioctw. Shouwd be used to fiww the
 * &v4w2_ioctw_ops.unwocked_ioctw on aww V4W2 dwivews.
 */
wong int video_ioctw2(stwuct fiwe *fiwe,
		      unsigned int cmd, unsigned wong int awg);

/*
 * The usew space intewpwetation of the 'v4w2_event' diffews
 * based on the 'time_t' definition on 32-bit awchitectuwes, so
 * the kewnew has to handwe both.
 * This is the owd vewsion fow 32-bit awchitectuwes.
 */
stwuct v4w2_event_time32 {
	__u32				type;
	union {
		stwuct v4w2_event_vsync		vsync;
		stwuct v4w2_event_ctww		ctww;
		stwuct v4w2_event_fwame_sync	fwame_sync;
		stwuct v4w2_event_swc_change	swc_change;
		stwuct v4w2_event_motion_det	motion_det;
		__u8				data[64];
	} u;
	__u32				pending;
	__u32				sequence;
	stwuct owd_timespec32		timestamp;
	__u32				id;
	__u32				wesewved[8];
};

#define	VIDIOC_DQEVENT_TIME32	 _IOW('V', 89, stwuct v4w2_event_time32)

stwuct v4w2_buffew_time32 {
	__u32			index;
	__u32			type;
	__u32			bytesused;
	__u32			fwags;
	__u32			fiewd;
	stwuct owd_timevaw32	timestamp;
	stwuct v4w2_timecode	timecode;
	__u32			sequence;

	/* memowy wocation */
	__u32			memowy;
	union {
		__u32           offset;
		unsigned wong   usewptw;
		stwuct v4w2_pwane *pwanes;
		__s32		fd;
	} m;
	__u32			wength;
	__u32			wesewved2;
	union {
		__s32		wequest_fd;
		__u32		wesewved;
	};
};
#define VIDIOC_QUEWYBUF_TIME32	_IOWW('V',  9, stwuct v4w2_buffew_time32)
#define VIDIOC_QBUF_TIME32	_IOWW('V', 15, stwuct v4w2_buffew_time32)
#define VIDIOC_DQBUF_TIME32	_IOWW('V', 17, stwuct v4w2_buffew_time32)
#define VIDIOC_PWEPAWE_BUF_TIME32 _IOWW('V', 93, stwuct v4w2_buffew_time32)

#endif /* _V4W2_IOCTW_H */
