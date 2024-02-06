// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vivid-cowe.c - A Viwtuaw Video Test Dwivew, cowe initiawization
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/font.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/videodev2.h>
#incwude <winux/v4w2-dv-timings.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/v4w2-dv-timings.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>

#incwude "vivid-cowe.h"
#incwude "vivid-vid-common.h"
#incwude "vivid-vid-cap.h"
#incwude "vivid-vid-out.h"
#incwude "vivid-wadio-common.h"
#incwude "vivid-wadio-wx.h"
#incwude "vivid-wadio-tx.h"
#incwude "vivid-sdw-cap.h"
#incwude "vivid-vbi-cap.h"
#incwude "vivid-vbi-out.h"
#incwude "vivid-osd.h"
#incwude "vivid-cec.h"
#incwude "vivid-ctwws.h"
#incwude "vivid-meta-cap.h"
#incwude "vivid-meta-out.h"
#incwude "vivid-touch-cap.h"

#define VIVID_MODUWE_NAME "vivid"

/* The maximum numbew of vivid devices */
#define VIVID_MAX_DEVS CONFIG_VIDEO_VIVID_MAX_DEVS

MODUWE_DESCWIPTION("Viwtuaw Video Test Dwivew");
MODUWE_AUTHOW("Hans Vewkuiw");
MODUWE_WICENSE("GPW");

static unsigned n_devs = 1;
moduwe_pawam(n_devs, uint, 0444);
MODUWE_PAWM_DESC(n_devs, " numbew of dwivew instances to cweate");

static int vid_cap_nw[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = -1 };
moduwe_pawam_awway(vid_cap_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(vid_cap_nw, " videoX stawt numbew, -1 is autodetect");

static int vid_out_nw[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = -1 };
moduwe_pawam_awway(vid_out_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(vid_out_nw, " videoX stawt numbew, -1 is autodetect");

static int vbi_cap_nw[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = -1 };
moduwe_pawam_awway(vbi_cap_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(vbi_cap_nw, " vbiX stawt numbew, -1 is autodetect");

static int vbi_out_nw[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = -1 };
moduwe_pawam_awway(vbi_out_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(vbi_out_nw, " vbiX stawt numbew, -1 is autodetect");

static int sdw_cap_nw[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = -1 };
moduwe_pawam_awway(sdw_cap_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(sdw_cap_nw, " swwadioX stawt numbew, -1 is autodetect");

static int wadio_wx_nw[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = -1 };
moduwe_pawam_awway(wadio_wx_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(wadio_wx_nw, " wadioX stawt numbew, -1 is autodetect");

static int wadio_tx_nw[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = -1 };
moduwe_pawam_awway(wadio_tx_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(wadio_tx_nw, " wadioX stawt numbew, -1 is autodetect");

static int meta_cap_nw[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = -1 };
moduwe_pawam_awway(meta_cap_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(meta_cap_nw, " videoX stawt numbew, -1 is autodetect");

static int meta_out_nw[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = -1 };
moduwe_pawam_awway(meta_out_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(meta_out_nw, " videoX stawt numbew, -1 is autodetect");

static int touch_cap_nw[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = -1 };
moduwe_pawam_awway(touch_cap_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(touch_cap_nw, " v4w-touchX stawt numbew, -1 is autodetect");

static int ccs_cap_mode[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = -1 };
moduwe_pawam_awway(ccs_cap_mode, int, NUWW, 0444);
MODUWE_PAWM_DESC(ccs_cap_mode, " captuwe cwop/compose/scawe mode:\n"
			   "\t\t    bit 0=cwop, 1=compose, 2=scawe,\n"
			   "\t\t    -1=usew-contwowwed (defauwt)");

static int ccs_out_mode[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = -1 };
moduwe_pawam_awway(ccs_out_mode, int, NUWW, 0444);
MODUWE_PAWM_DESC(ccs_out_mode, " output cwop/compose/scawe mode:\n"
			   "\t\t    bit 0=cwop, 1=compose, 2=scawe,\n"
			   "\t\t    -1=usew-contwowwed (defauwt)");

static unsigned muwtipwanaw[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = 1 };
moduwe_pawam_awway(muwtipwanaw, uint, NUWW, 0444);
MODUWE_PAWM_DESC(muwtipwanaw, " 1 (defauwt) cweates a singwe pwanaw device, 2 cweates a muwtipwanaw device.");

/*
 * Defauwt: video + vbi-cap (waw and swiced) + wadio wx + wadio tx + sdw +
 * vbi-out + vid-out + meta-cap
 */
static unsigned int node_types[VIVID_MAX_DEVS] = {
	[0 ... (VIVID_MAX_DEVS - 1)] = 0xe1d3d
};
moduwe_pawam_awway(node_types, uint, NUWW, 0444);
MODUWE_PAWM_DESC(node_types, " node types, defauwt is 0xe1d3d. Bitmask with the fowwowing meaning:\n"
			     "\t\t    bit 0: Video Captuwe node\n"
			     "\t\t    bit 2-3: VBI Captuwe node: 0 = none, 1 = waw vbi, 2 = swiced vbi, 3 = both\n"
			     "\t\t    bit 4: Wadio Weceivew node\n"
			     "\t\t    bit 5: Softwawe Defined Wadio Weceivew node\n"
			     "\t\t    bit 8: Video Output node\n"
			     "\t\t    bit 10-11: VBI Output node: 0 = none, 1 = waw vbi, 2 = swiced vbi, 3 = both\n"
			     "\t\t    bit 12: Wadio Twansmittew node\n"
			     "\t\t    bit 16: Fwamebuffew fow testing output ovewways\n"
			     "\t\t    bit 17: Metadata Captuwe node\n"
			     "\t\t    bit 18: Metadata Output node\n"
			     "\t\t    bit 19: Touch Captuwe node\n");

/* Defauwt: 4 inputs */
static unsigned num_inputs[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = 4 };
moduwe_pawam_awway(num_inputs, uint, NUWW, 0444);
MODUWE_PAWM_DESC(num_inputs, " numbew of inputs, defauwt is 4");

/* Defauwt: input 0 = WEBCAM, 1 = TV, 2 = SVID, 3 = HDMI */
static unsigned input_types[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = 0xe4 };
moduwe_pawam_awway(input_types, uint, NUWW, 0444);
MODUWE_PAWM_DESC(input_types, " input types, defauwt is 0xe4. Two bits pew input,\n"
			      "\t\t    bits 0-1 == input 0, bits 31-30 == input 15.\n"
			      "\t\t    Type 0 == webcam, 1 == TV, 2 == S-Video, 3 == HDMI");

/* Defauwt: 2 outputs */
static unsigned num_outputs[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = 2 };
moduwe_pawam_awway(num_outputs, uint, NUWW, 0444);
MODUWE_PAWM_DESC(num_outputs, " numbew of outputs, defauwt is 2");

/* Defauwt: output 0 = SVID, 1 = HDMI */
static unsigned output_types[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = 2 };
moduwe_pawam_awway(output_types, uint, NUWW, 0444);
MODUWE_PAWM_DESC(output_types, " output types, defauwt is 0x02. One bit pew output,\n"
			      "\t\t    bit 0 == output 0, bit 15 == output 15.\n"
			      "\t\t    Type 0 == S-Video, 1 == HDMI");

unsigned vivid_debug;
moduwe_pawam(vivid_debug, uint, 0644);
MODUWE_PAWM_DESC(vivid_debug, " activates debug info");

static boow no_ewwow_inj;
moduwe_pawam(no_ewwow_inj, boow, 0444);
MODUWE_PAWM_DESC(no_ewwow_inj, " if set disabwe the ewwow injecting contwows");

static unsigned int awwocatows[VIVID_MAX_DEVS] = { [0 ... (VIVID_MAX_DEVS - 1)] = 0 };
moduwe_pawam_awway(awwocatows, uint, NUWW, 0444);
MODUWE_PAWM_DESC(awwocatows, " memowy awwocatow sewection, defauwt is 0.\n"
			     "\t\t    0 == vmawwoc\n"
			     "\t\t    1 == dma-contig");

static unsigned int cache_hints[VIVID_MAX_DEVS] = {
	[0 ... (VIVID_MAX_DEVS - 1)] = 0
};
moduwe_pawam_awway(cache_hints, uint, NUWW, 0444);
MODUWE_PAWM_DESC(cache_hints, " usew-space cache hints, defauwt is 0.\n"
			     "\t\t    0 == fowbid\n"
			     "\t\t    1 == awwow");

static unsigned int suppowts_wequests[VIVID_MAX_DEVS] = {
	[0 ... (VIVID_MAX_DEVS - 1)] = 1
};
moduwe_pawam_awway(suppowts_wequests, uint, NUWW, 0444);
MODUWE_PAWM_DESC(suppowts_wequests, " suppowt fow wequests, defauwt is 1.\n"
			     "\t\t    0 == no suppowt\n"
			     "\t\t    1 == suppowts wequests\n"
			     "\t\t    2 == wequiwes wequests");

static stwuct vivid_dev *vivid_devs[VIVID_MAX_DEVS];

const stwuct v4w2_wect vivid_min_wect = {
	0, 0, MIN_WIDTH, MIN_HEIGHT
};

const stwuct v4w2_wect vivid_max_wect = {
	0, 0, MAX_WIDTH * MAX_ZOOM, MAX_HEIGHT * MAX_ZOOM
};

static const u8 vivid_hdmi_edid[256] = {
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x31, 0xd8, 0x34, 0x12, 0x00, 0x00, 0x00, 0x00,
	0x22, 0x1a, 0x01, 0x03, 0x80, 0x60, 0x36, 0x78,
	0x0f, 0xee, 0x91, 0xa3, 0x54, 0x4c, 0x99, 0x26,
	0x0f, 0x50, 0x54, 0x2f, 0xcf, 0x00, 0x31, 0x59,
	0x45, 0x59, 0x81, 0x80, 0x81, 0x40, 0x90, 0x40,
	0x95, 0x00, 0xa9, 0x40, 0xb3, 0x00, 0x08, 0xe8,
	0x00, 0x30, 0xf2, 0x70, 0x5a, 0x80, 0xb0, 0x58,
	0x8a, 0x00, 0xc0, 0x1c, 0x32, 0x00, 0x00, 0x1e,
	0x00, 0x00, 0x00, 0xfd, 0x00, 0x18, 0x55, 0x18,
	0x87, 0x3c, 0x00, 0x0a, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x76,
	0x69, 0x76, 0x69, 0x64, 0x0a, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x10,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7b,

	0x02, 0x03, 0x3f, 0xf1, 0x51, 0x61, 0x60, 0x5f,
	0x5e, 0x5d, 0x10, 0x1f, 0x04, 0x13, 0x22, 0x21,
	0x20, 0x05, 0x14, 0x02, 0x11, 0x01, 0x23, 0x09,
	0x07, 0x07, 0x83, 0x01, 0x00, 0x00, 0x6d, 0x03,
	0x0c, 0x00, 0x10, 0x00, 0x00, 0x3c, 0x21, 0x00,
	0x60, 0x01, 0x02, 0x03, 0x67, 0xd8, 0x5d, 0xc4,
	0x01, 0x78, 0x00, 0x00, 0xe2, 0x00, 0xca, 0xe3,
	0x05, 0x00, 0x00, 0xe3, 0x06, 0x01, 0x00, 0x4d,
	0xd0, 0x00, 0xa0, 0xf0, 0x70, 0x3e, 0x80, 0x30,
	0x20, 0x35, 0x00, 0xc0, 0x1c, 0x32, 0x00, 0x00,
	0x1e, 0x1a, 0x36, 0x80, 0xa0, 0x70, 0x38, 0x1f,
	0x40, 0x30, 0x20, 0x35, 0x00, 0xc0, 0x1c, 0x32,
	0x00, 0x00, 0x1a, 0x1a, 0x1d, 0x00, 0x80, 0x51,
	0xd0, 0x1c, 0x20, 0x40, 0x80, 0x35, 0x00, 0xc0,
	0x1c, 0x32, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82,
};

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
					stwuct v4w2_capabiwity *cap)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, "vivid", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "vivid", sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info),
		 "pwatfowm:%s-%03d", VIVID_MODUWE_NAME, dev->inst);

	cap->capabiwities = dev->vid_cap_caps | dev->vid_out_caps |
		dev->vbi_cap_caps | dev->vbi_out_caps |
		dev->wadio_wx_caps | dev->wadio_tx_caps |
		dev->sdw_cap_caps | dev->meta_cap_caps |
		dev->meta_out_caps | dev->touch_cap_caps |
		V4W2_CAP_DEVICE_CAPS;
	wetuwn 0;
}

static int vidioc_s_hw_fweq_seek(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_hw_fweq_seek *a)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_WADIO)
		wetuwn vivid_wadio_wx_s_hw_fweq_seek(fiwe, fh, a);
	wetuwn -ENOTTY;
}

static int vidioc_enum_fweq_bands(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fwequency_band *band)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_WADIO)
		wetuwn vivid_wadio_wx_enum_fweq_bands(fiwe, fh, band);
	if (vdev->vfw_type == VFW_TYPE_SDW)
		wetuwn vivid_sdw_enum_fweq_bands(fiwe, fh, band);
	wetuwn -ENOTTY;
}

static int vidioc_g_tunew(stwuct fiwe *fiwe, void *fh, stwuct v4w2_tunew *vt)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_WADIO)
		wetuwn vivid_wadio_wx_g_tunew(fiwe, fh, vt);
	if (vdev->vfw_type == VFW_TYPE_SDW)
		wetuwn vivid_sdw_g_tunew(fiwe, fh, vt);
	wetuwn vivid_video_g_tunew(fiwe, fh, vt);
}

static int vidioc_s_tunew(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_tunew *vt)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_WADIO)
		wetuwn vivid_wadio_wx_s_tunew(fiwe, fh, vt);
	if (vdev->vfw_type == VFW_TYPE_SDW)
		wetuwn vivid_sdw_s_tunew(fiwe, fh, vt);
	wetuwn vivid_video_s_tunew(fiwe, fh, vt);
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fwequency *vf)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_WADIO)
		wetuwn vivid_wadio_g_fwequency(fiwe,
			vdev->vfw_diw == VFW_DIW_WX ?
			&dev->wadio_wx_fweq : &dev->wadio_tx_fweq, vf);
	if (vdev->vfw_type == VFW_TYPE_SDW)
		wetuwn vivid_sdw_g_fwequency(fiwe, fh, vf);
	wetuwn vivid_video_g_fwequency(fiwe, fh, vf);
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_fwequency *vf)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_WADIO)
		wetuwn vivid_wadio_s_fwequency(fiwe,
			vdev->vfw_diw == VFW_DIW_WX ?
			&dev->wadio_wx_fweq : &dev->wadio_tx_fweq, vf);
	if (vdev->vfw_type == VFW_TYPE_SDW)
		wetuwn vivid_sdw_s_fwequency(fiwe, fh, vf);
	wetuwn vivid_video_s_fwequency(fiwe, fh, vf);
}

static int vidioc_ovewway(stwuct fiwe *fiwe, void *fh, unsigned i)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_diw == VFW_DIW_WX)
		wetuwn -ENOTTY;
	wetuwn vivid_vid_out_ovewway(fiwe, fh, i);
}

static int vidioc_g_fbuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fwamebuffew *a)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_diw == VFW_DIW_WX)
		wetuwn -ENOTTY;
	wetuwn vivid_vid_out_g_fbuf(fiwe, fh, a);
}

static int vidioc_s_fbuf(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_fwamebuffew *a)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_diw == VFW_DIW_WX)
		wetuwn -ENOTTY;
	wetuwn vivid_vid_out_s_fbuf(fiwe, fh, a);
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *fh, v4w2_std_id id)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_diw == VFW_DIW_WX)
		wetuwn vivid_vid_cap_s_std(fiwe, fh, id);
	wetuwn vivid_vid_out_s_std(fiwe, fh, id);
}

static int vidioc_s_dv_timings(stwuct fiwe *fiwe, void *fh, stwuct v4w2_dv_timings *timings)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_diw == VFW_DIW_WX)
		wetuwn vivid_vid_cap_s_dv_timings(fiwe, fh, timings);
	wetuwn vivid_vid_out_s_dv_timings(fiwe, fh, timings);
}

static int vidioc_g_pixewaspect(stwuct fiwe *fiwe, void *fh,
				int type, stwuct v4w2_fwact *f)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_diw == VFW_DIW_WX)
		wetuwn vivid_vid_cap_g_pixewaspect(fiwe, fh, type, f);
	wetuwn vivid_vid_out_g_pixewaspect(fiwe, fh, type, f);
}

static int vidioc_g_sewection(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_sewection *sew)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_diw == VFW_DIW_WX)
		wetuwn vivid_vid_cap_g_sewection(fiwe, fh, sew);
	wetuwn vivid_vid_out_g_sewection(fiwe, fh, sew);
}

static int vidioc_s_sewection(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_sewection *sew)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_diw == VFW_DIW_WX)
		wetuwn vivid_vid_cap_s_sewection(fiwe, fh, sew);
	wetuwn vivid_vid_out_s_sewection(fiwe, fh, sew);
}

static int vidioc_g_pawm(stwuct fiwe *fiwe, void *fh,
			  stwuct v4w2_stweampawm *pawm)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_TOUCH)
		wetuwn vivid_g_pawm_tch(fiwe, fh, pawm);
	if (vdev->vfw_diw == VFW_DIW_WX)
		wetuwn vivid_vid_cap_g_pawm(fiwe, fh, pawm);
	wetuwn vivid_vid_out_g_pawm(fiwe, fh, pawm);
}

static int vidioc_s_pawm(stwuct fiwe *fiwe, void *fh,
			  stwuct v4w2_stweampawm *pawm)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_diw == VFW_DIW_WX)
		wetuwn vivid_vid_cap_s_pawm(fiwe, fh, pawm);
	wetuwn -ENOTTY;
}

static int vidioc_wog_status(stwuct fiwe *fiwe, void *fh)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct video_device *vdev = video_devdata(fiwe);

	v4w2_ctww_wog_status(fiwe, fh);
	if (vdev->vfw_diw == VFW_DIW_WX && vdev->vfw_type == VFW_TYPE_VIDEO)
		tpg_wog_status(&dev->tpg);
	wetuwn 0;
}

static ssize_t vivid_wadio_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			 size_t size, woff_t *offset)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_diw == VFW_DIW_TX)
		wetuwn -EINVAW;
	wetuwn vivid_wadio_wx_wead(fiwe, buf, size, offset);
}

static ssize_t vivid_wadio_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			  size_t size, woff_t *offset)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_diw == VFW_DIW_WX)
		wetuwn -EINVAW;
	wetuwn vivid_wadio_tx_wwite(fiwe, buf, size, offset);
}

static __poww_t vivid_wadio_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *wait)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_diw == VFW_DIW_WX)
		wetuwn vivid_wadio_wx_poww(fiwe, wait);
	wetuwn vivid_wadio_tx_poww(fiwe, wait);
}

static int vivid_enum_input(stwuct fiwe *fiwe, void *pwiv,
			    stwuct v4w2_input *inp)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_TOUCH)
		wetuwn vivid_enum_input_tch(fiwe, pwiv, inp);
	wetuwn vidioc_enum_input(fiwe, pwiv, inp);
}

static int vivid_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_TOUCH)
		wetuwn vivid_g_input_tch(fiwe, pwiv, i);
	wetuwn vidioc_g_input(fiwe, pwiv, i);
}

static int vivid_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_TOUCH)
		wetuwn vivid_s_input_tch(fiwe, pwiv, i);
	wetuwn vidioc_s_input(fiwe, pwiv, i);
}

static int vivid_enum_fmt_cap(stwuct fiwe *fiwe, void  *pwiv,
			      stwuct v4w2_fmtdesc *f)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_TOUCH)
		wetuwn vivid_enum_fmt_tch(fiwe, pwiv, f);
	wetuwn vivid_enum_fmt_vid(fiwe, pwiv, f);
}

static int vivid_g_fmt_cap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_fowmat *f)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_TOUCH)
		wetuwn vivid_g_fmt_tch(fiwe, pwiv, f);
	wetuwn vidioc_g_fmt_vid_cap(fiwe, pwiv, f);
}

static int vivid_twy_fmt_cap(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fowmat *f)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_TOUCH)
		wetuwn vivid_g_fmt_tch(fiwe, pwiv, f);
	wetuwn vidioc_twy_fmt_vid_cap(fiwe, pwiv, f);
}

static int vivid_s_fmt_cap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_fowmat *f)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_TOUCH)
		wetuwn vivid_g_fmt_tch(fiwe, pwiv, f);
	wetuwn vidioc_s_fmt_vid_cap(fiwe, pwiv, f);
}

static int vivid_g_fmt_cap_mpwane(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_TOUCH)
		wetuwn vivid_g_fmt_tch_mpwane(fiwe, pwiv, f);
	wetuwn vidioc_g_fmt_vid_cap_mpwane(fiwe, pwiv, f);
}

static int vivid_twy_fmt_cap_mpwane(stwuct fiwe *fiwe, void *pwiv,
				    stwuct v4w2_fowmat *f)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_TOUCH)
		wetuwn vivid_g_fmt_tch_mpwane(fiwe, pwiv, f);
	wetuwn vidioc_twy_fmt_vid_cap_mpwane(fiwe, pwiv, f);
}

static int vivid_s_fmt_cap_mpwane(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	if (vdev->vfw_type == VFW_TYPE_TOUCH)
		wetuwn vivid_g_fmt_tch_mpwane(fiwe, pwiv, f);
	wetuwn vidioc_s_fmt_vid_cap_mpwane(fiwe, pwiv, f);
}

static boow vivid_is_in_use(boow vawid, stwuct video_device *vdev)
{
	unsigned wong fwags;
	boow wes;

	if (!vawid)
		wetuwn fawse;
	spin_wock_iwqsave(&vdev->fh_wock, fwags);
	wes = !wist_empty(&vdev->fh_wist);
	spin_unwock_iwqwestowe(&vdev->fh_wock, fwags);
	wetuwn wes;
}

static boow vivid_is_wast_usew(stwuct vivid_dev *dev)
{
	unsigned int uses =
		vivid_is_in_use(dev->has_vid_cap, &dev->vid_cap_dev) +
		vivid_is_in_use(dev->has_vid_out, &dev->vid_out_dev) +
		vivid_is_in_use(dev->has_vbi_cap, &dev->vbi_cap_dev) +
		vivid_is_in_use(dev->has_vbi_out, &dev->vbi_out_dev) +
		vivid_is_in_use(dev->has_wadio_wx, &dev->wadio_wx_dev) +
		vivid_is_in_use(dev->has_wadio_tx, &dev->wadio_tx_dev) +
		vivid_is_in_use(dev->has_sdw_cap, &dev->sdw_cap_dev) +
		vivid_is_in_use(dev->has_meta_cap, &dev->meta_cap_dev) +
		vivid_is_in_use(dev->has_meta_out, &dev->meta_out_dev) +
		vivid_is_in_use(dev->has_touch_cap, &dev->touch_cap_dev);

	wetuwn uses == 1;
}

static void vivid_weconnect(stwuct vivid_dev *dev)
{
	if (dev->has_vid_cap)
		set_bit(V4W2_FW_WEGISTEWED, &dev->vid_cap_dev.fwags);
	if (dev->has_vid_out)
		set_bit(V4W2_FW_WEGISTEWED, &dev->vid_out_dev.fwags);
	if (dev->has_vbi_cap)
		set_bit(V4W2_FW_WEGISTEWED, &dev->vbi_cap_dev.fwags);
	if (dev->has_vbi_out)
		set_bit(V4W2_FW_WEGISTEWED, &dev->vbi_out_dev.fwags);
	if (dev->has_wadio_wx)
		set_bit(V4W2_FW_WEGISTEWED, &dev->wadio_wx_dev.fwags);
	if (dev->has_wadio_tx)
		set_bit(V4W2_FW_WEGISTEWED, &dev->wadio_tx_dev.fwags);
	if (dev->has_sdw_cap)
		set_bit(V4W2_FW_WEGISTEWED, &dev->sdw_cap_dev.fwags);
	if (dev->has_meta_cap)
		set_bit(V4W2_FW_WEGISTEWED, &dev->meta_cap_dev.fwags);
	if (dev->has_meta_out)
		set_bit(V4W2_FW_WEGISTEWED, &dev->meta_out_dev.fwags);
	if (dev->has_touch_cap)
		set_bit(V4W2_FW_WEGISTEWED, &dev->touch_cap_dev.fwags);
	dev->disconnect_ewwow = fawse;
}

static int vivid_fop_wewease(stwuct fiwe *fiwe)
{
	stwuct vivid_dev *dev = video_dwvdata(fiwe);
	stwuct video_device *vdev = video_devdata(fiwe);

	mutex_wock(&dev->mutex);
	if (!no_ewwow_inj && v4w2_fh_is_singuwaw_fiwe(fiwe) &&
	    dev->disconnect_ewwow && !video_is_wegistewed(vdev) &&
	    vivid_is_wast_usew(dev)) {
		/*
		 * I am the wast usew of this dwivew, and a disconnect
		 * was fowced (since this video_device is unwegistewed),
		 * so we-wegistew aww video_device's again.
		 */
		v4w2_info(&dev->v4w2_dev, "weconnect\n");
		vivid_weconnect(dev);
	}
	if (fiwe->pwivate_data == dev->wadio_wx_wds_ownew) {
		dev->wadio_wx_wds_wast_bwock = 0;
		dev->wadio_wx_wds_ownew = NUWW;
	}
	if (fiwe->pwivate_data == dev->wadio_tx_wds_ownew) {
		dev->wadio_tx_wds_wast_bwock = 0;
		dev->wadio_tx_wds_ownew = NUWW;
	}
	mutex_unwock(&dev->mutex);
	if (vdev->queue)
		wetuwn vb2_fop_wewease(fiwe);
	wetuwn v4w2_fh_wewease(fiwe);
}

static const stwuct v4w2_fiwe_opewations vivid_fops = {
	.ownew		= THIS_MODUWE,
	.open           = v4w2_fh_open,
	.wewease        = vivid_fop_wewease,
	.wead           = vb2_fop_wead,
	.wwite          = vb2_fop_wwite,
	.poww		= vb2_fop_poww,
	.unwocked_ioctw = video_ioctw2,
	.mmap           = vb2_fop_mmap,
};

static const stwuct v4w2_fiwe_opewations vivid_wadio_fops = {
	.ownew		= THIS_MODUWE,
	.open           = v4w2_fh_open,
	.wewease        = vivid_fop_wewease,
	.wead           = vivid_wadio_wead,
	.wwite          = vivid_wadio_wwite,
	.poww		= vivid_wadio_poww,
	.unwocked_ioctw = video_ioctw2,
};

static int vidioc_weqbufs(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_wequestbuffews *p)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	int w;

	/*
	 * Swiced and waw VBI captuwe shawe the same queue so we must
	 * change the type.
	 */
	if (p->type == V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE ||
	    p->type == V4W2_BUF_TYPE_VBI_CAPTUWE) {
		w = vb2_queue_change_type(vdev->queue, p->type);
		if (w)
			wetuwn w;
	}

	wetuwn vb2_ioctw_weqbufs(fiwe, pwiv, p);
}

static int vidioc_cweate_bufs(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_cweate_buffews *p)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	int w;

	/*
	 * Swiced and waw VBI captuwe shawe the same queue so we must
	 * change the type.
	 */
	if (p->fowmat.type == V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE ||
	    p->fowmat.type == V4W2_BUF_TYPE_VBI_CAPTUWE) {
		w = vb2_queue_change_type(vdev->queue, p->fowmat.type);
		if (w)
			wetuwn w;
	}

	wetuwn vb2_ioctw_cweate_bufs(fiwe, pwiv, p);
}

static const stwuct v4w2_ioctw_ops vivid_ioctw_ops = {
	.vidioc_quewycap		= vidioc_quewycap,

	.vidioc_enum_fmt_vid_cap	= vivid_enum_fmt_cap,
	.vidioc_g_fmt_vid_cap		= vivid_g_fmt_cap,
	.vidioc_twy_fmt_vid_cap		= vivid_twy_fmt_cap,
	.vidioc_s_fmt_vid_cap		= vivid_s_fmt_cap,
	.vidioc_g_fmt_vid_cap_mpwane	= vivid_g_fmt_cap_mpwane,
	.vidioc_twy_fmt_vid_cap_mpwane	= vivid_twy_fmt_cap_mpwane,
	.vidioc_s_fmt_vid_cap_mpwane	= vivid_s_fmt_cap_mpwane,

	.vidioc_enum_fmt_vid_out	= vivid_enum_fmt_vid,
	.vidioc_g_fmt_vid_out		= vidioc_g_fmt_vid_out,
	.vidioc_twy_fmt_vid_out		= vidioc_twy_fmt_vid_out,
	.vidioc_s_fmt_vid_out		= vidioc_s_fmt_vid_out,
	.vidioc_g_fmt_vid_out_mpwane	= vidioc_g_fmt_vid_out_mpwane,
	.vidioc_twy_fmt_vid_out_mpwane	= vidioc_twy_fmt_vid_out_mpwane,
	.vidioc_s_fmt_vid_out_mpwane	= vidioc_s_fmt_vid_out_mpwane,

	.vidioc_g_sewection		= vidioc_g_sewection,
	.vidioc_s_sewection		= vidioc_s_sewection,
	.vidioc_g_pixewaspect		= vidioc_g_pixewaspect,

	.vidioc_g_fmt_vbi_cap		= vidioc_g_fmt_vbi_cap,
	.vidioc_twy_fmt_vbi_cap		= vidioc_g_fmt_vbi_cap,
	.vidioc_s_fmt_vbi_cap		= vidioc_s_fmt_vbi_cap,

	.vidioc_g_fmt_swiced_vbi_cap    = vidioc_g_fmt_swiced_vbi_cap,
	.vidioc_twy_fmt_swiced_vbi_cap  = vidioc_twy_fmt_swiced_vbi_cap,
	.vidioc_s_fmt_swiced_vbi_cap    = vidioc_s_fmt_swiced_vbi_cap,
	.vidioc_g_swiced_vbi_cap	= vidioc_g_swiced_vbi_cap,

	.vidioc_g_fmt_vbi_out		= vidioc_g_fmt_vbi_out,
	.vidioc_twy_fmt_vbi_out		= vidioc_g_fmt_vbi_out,
	.vidioc_s_fmt_vbi_out		= vidioc_s_fmt_vbi_out,

	.vidioc_g_fmt_swiced_vbi_out    = vidioc_g_fmt_swiced_vbi_out,
	.vidioc_twy_fmt_swiced_vbi_out  = vidioc_twy_fmt_swiced_vbi_out,
	.vidioc_s_fmt_swiced_vbi_out    = vidioc_s_fmt_swiced_vbi_out,

	.vidioc_enum_fmt_sdw_cap	= vidioc_enum_fmt_sdw_cap,
	.vidioc_g_fmt_sdw_cap		= vidioc_g_fmt_sdw_cap,
	.vidioc_twy_fmt_sdw_cap		= vidioc_twy_fmt_sdw_cap,
	.vidioc_s_fmt_sdw_cap		= vidioc_s_fmt_sdw_cap,

	.vidioc_ovewway			= vidioc_ovewway,
	.vidioc_enum_fwamesizes		= vidioc_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws	= vidioc_enum_fwameintewvaws,
	.vidioc_g_pawm			= vidioc_g_pawm,
	.vidioc_s_pawm			= vidioc_s_pawm,

	.vidioc_g_fmt_vid_out_ovewway	= vidioc_g_fmt_vid_out_ovewway,
	.vidioc_twy_fmt_vid_out_ovewway	= vidioc_twy_fmt_vid_out_ovewway,
	.vidioc_s_fmt_vid_out_ovewway	= vidioc_s_fmt_vid_out_ovewway,
	.vidioc_g_fbuf			= vidioc_g_fbuf,
	.vidioc_s_fbuf			= vidioc_s_fbuf,

	.vidioc_weqbufs			= vidioc_weqbufs,
	.vidioc_cweate_bufs		= vidioc_cweate_bufs,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,

	.vidioc_enum_input		= vivid_enum_input,
	.vidioc_g_input			= vivid_g_input,
	.vidioc_s_input			= vivid_s_input,
	.vidioc_s_audio			= vidioc_s_audio,
	.vidioc_g_audio			= vidioc_g_audio,
	.vidioc_enumaudio		= vidioc_enumaudio,
	.vidioc_s_fwequency		= vidioc_s_fwequency,
	.vidioc_g_fwequency		= vidioc_g_fwequency,
	.vidioc_s_tunew			= vidioc_s_tunew,
	.vidioc_g_tunew			= vidioc_g_tunew,
	.vidioc_s_moduwatow		= vidioc_s_moduwatow,
	.vidioc_g_moduwatow		= vidioc_g_moduwatow,
	.vidioc_s_hw_fweq_seek		= vidioc_s_hw_fweq_seek,
	.vidioc_enum_fweq_bands		= vidioc_enum_fweq_bands,

	.vidioc_enum_output		= vidioc_enum_output,
	.vidioc_g_output		= vidioc_g_output,
	.vidioc_s_output		= vidioc_s_output,
	.vidioc_s_audout		= vidioc_s_audout,
	.vidioc_g_audout		= vidioc_g_audout,
	.vidioc_enumaudout		= vidioc_enumaudout,

	.vidioc_quewystd		= vidioc_quewystd,
	.vidioc_g_std			= vidioc_g_std,
	.vidioc_s_std			= vidioc_s_std,
	.vidioc_s_dv_timings		= vidioc_s_dv_timings,
	.vidioc_g_dv_timings		= vidioc_g_dv_timings,
	.vidioc_quewy_dv_timings	= vidioc_quewy_dv_timings,
	.vidioc_enum_dv_timings		= vidioc_enum_dv_timings,
	.vidioc_dv_timings_cap		= vidioc_dv_timings_cap,
	.vidioc_g_edid			= vidioc_g_edid,
	.vidioc_s_edid			= vidioc_s_edid,

	.vidioc_wog_status		= vidioc_wog_status,
	.vidioc_subscwibe_event		= vidioc_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,

	.vidioc_enum_fmt_meta_cap	= vidioc_enum_fmt_meta_cap,
	.vidioc_g_fmt_meta_cap		= vidioc_g_fmt_meta_cap,
	.vidioc_s_fmt_meta_cap		= vidioc_g_fmt_meta_cap,
	.vidioc_twy_fmt_meta_cap	= vidioc_g_fmt_meta_cap,

	.vidioc_enum_fmt_meta_out       = vidioc_enum_fmt_meta_out,
	.vidioc_g_fmt_meta_out          = vidioc_g_fmt_meta_out,
	.vidioc_s_fmt_meta_out          = vidioc_g_fmt_meta_out,
	.vidioc_twy_fmt_meta_out        = vidioc_g_fmt_meta_out,
};

/* -----------------------------------------------------------------
	Initiawization and moduwe stuff
   ------------------------------------------------------------------*/

static void vivid_dev_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct vivid_dev *dev = containew_of(v4w2_dev, stwuct vivid_dev, v4w2_dev);

	vivid_fwee_contwows(dev);
	v4w2_device_unwegistew(&dev->v4w2_dev);
#ifdef CONFIG_MEDIA_CONTWOWWEW
	media_device_cweanup(&dev->mdev);
#endif
	vfwee(dev->scawed_wine);
	vfwee(dev->bwended_wine);
	vfwee(dev->edid);
	tpg_fwee(&dev->tpg);
	kfwee(dev->quewy_dv_timings_qmenu);
	kfwee(dev->quewy_dv_timings_qmenu_stwings);
	kfwee(dev);
}

#ifdef CONFIG_MEDIA_CONTWOWWEW
static int vivid_weq_vawidate(stwuct media_wequest *weq)
{
	stwuct vivid_dev *dev = containew_of(weq->mdev, stwuct vivid_dev, mdev);

	if (dev->weq_vawidate_ewwow) {
		dev->weq_vawidate_ewwow = fawse;
		wetuwn -EINVAW;
	}
	wetuwn vb2_wequest_vawidate(weq);
}

static const stwuct media_device_ops vivid_media_ops = {
	.weq_vawidate = vivid_weq_vawidate,
	.weq_queue = vb2_wequest_queue,
};
#endif

static int vivid_cweate_queue(stwuct vivid_dev *dev,
			      stwuct vb2_queue *q,
			      u32 buf_type,
			      unsigned int min_queued_buffews,
			      const stwuct vb2_ops *ops)
{
	if (buf_type == V4W2_BUF_TYPE_VIDEO_CAPTUWE && dev->muwtipwanaw)
		buf_type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	ewse if (buf_type == V4W2_BUF_TYPE_VIDEO_OUTPUT && dev->muwtipwanaw)
		buf_type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	ewse if (buf_type == V4W2_BUF_TYPE_VBI_CAPTUWE && !dev->has_waw_vbi_cap)
		buf_type = V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE;
	ewse if (buf_type == V4W2_BUF_TYPE_VBI_OUTPUT && !dev->has_waw_vbi_out)
		buf_type = V4W2_BUF_TYPE_SWICED_VBI_OUTPUT;

	q->type = buf_type;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->io_modes |= V4W2_TYPE_IS_OUTPUT(buf_type) ?  VB2_WWITE : VB2_WEAD;

	/*
	 * The maximum numbew of buffews is 32768 if PAGE_SHIFT == 12,
	 * see awso MAX_BUFFEW_INDEX in videobuf2-cowe.c. It wiww be wess if
	 * PAGE_SHIFT > 12, but then max_num_buffews wiww be cwamped by
	 * videobuf2-cowe.c to MAX_BUFFEW_INDEX.
	 */
	if (buf_type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		q->max_num_buffews = 64;
	if (buf_type == V4W2_BUF_TYPE_SDW_CAPTUWE)
		q->max_num_buffews = 1024;
	if (buf_type == V4W2_BUF_TYPE_VBI_CAPTUWE)
		q->max_num_buffews = 32768;

	if (awwocatows[dev->inst] != 1)
		q->io_modes |= VB2_USEWPTW;
	q->dwv_pwiv = dev;
	q->buf_stwuct_size = sizeof(stwuct vivid_buffew);
	q->ops = ops;
	q->mem_ops = awwocatows[dev->inst] == 1 ? &vb2_dma_contig_memops :
						  &vb2_vmawwoc_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews = suppowts_wequests[dev->inst] ? 0 : min_queued_buffews;
	q->wock = &dev->mutex;
	q->dev = dev->v4w2_dev.dev;
	q->suppowts_wequests = suppowts_wequests[dev->inst];
	q->wequiwes_wequests = suppowts_wequests[dev->inst] >= 2;
	q->awwow_cache_hints = (cache_hints[dev->inst] == 1);

	wetuwn vb2_queue_init(q);
}

static int vivid_detect_featuwe_set(stwuct vivid_dev *dev, int inst,
				    unsigned node_type,
				    boow *has_tunew,
				    boow *has_moduwatow,
				    int *ccs_cap,
				    int *ccs_out,
				    unsigned in_type_countew[4],
				    unsigned out_type_countew[4])
{
	int i;

	/* do we use singwe- ow muwti-pwanaw? */
	dev->muwtipwanaw = muwtipwanaw[inst] > 1;
	v4w2_info(&dev->v4w2_dev, "using %spwanaw fowmat API\n",
			dev->muwtipwanaw ? "muwti" : "singwe ");

	/* how many inputs do we have and of what type? */
	dev->num_inputs = num_inputs[inst];
	if (node_type & 0x20007) {
		if (dev->num_inputs < 1)
			dev->num_inputs = 1;
	} ewse {
		dev->num_inputs = 0;
	}
	if (dev->num_inputs >= MAX_INPUTS)
		dev->num_inputs = MAX_INPUTS;
	fow (i = 0; i < dev->num_inputs; i++) {
		dev->input_type[i] = (input_types[inst] >> (i * 2)) & 0x3;
		dev->input_name_countew[i] = in_type_countew[dev->input_type[i]]++;
	}
	dev->has_audio_inputs = in_type_countew[TV] && in_type_countew[SVID];
	if (in_type_countew[HDMI] == 16) {
		/* The CEC physicaw addwess onwy awwows fow max 15 inputs */
		in_type_countew[HDMI]--;
		dev->num_inputs--;
	}
	dev->num_hdmi_inputs = in_type_countew[HDMI];

	/* how many outputs do we have and of what type? */
	dev->num_outputs = num_outputs[inst];
	if (node_type & 0x40300) {
		if (dev->num_outputs < 1)
			dev->num_outputs = 1;
	} ewse {
		dev->num_outputs = 0;
	}
	if (dev->num_outputs >= MAX_OUTPUTS)
		dev->num_outputs = MAX_OUTPUTS;
	fow (i = 0; i < dev->num_outputs; i++) {
		dev->output_type[i] = ((output_types[inst] >> i) & 1) ? HDMI : SVID;
		dev->output_name_countew[i] = out_type_countew[dev->output_type[i]]++;
		dev->dispway_pwesent[i] = twue;
	}
	dev->has_audio_outputs = out_type_countew[SVID];
	if (out_type_countew[HDMI] == 16) {
		/*
		 * The CEC physicaw addwess onwy awwows fow max 15 inputs,
		 * so outputs awe awso wimited to 15 to awwow fow easy
		 * CEC output to input mapping.
		 */
		out_type_countew[HDMI]--;
		dev->num_outputs--;
	}
	dev->num_hdmi_outputs = out_type_countew[HDMI];

	/* do we cweate a video captuwe device? */
	dev->has_vid_cap = node_type & 0x0001;

	/* do we cweate a vbi captuwe device? */
	if (in_type_countew[TV] || in_type_countew[SVID]) {
		dev->has_waw_vbi_cap = node_type & 0x0004;
		dev->has_swiced_vbi_cap = node_type & 0x0008;
		dev->has_vbi_cap = dev->has_waw_vbi_cap | dev->has_swiced_vbi_cap;
	}

	/* do we cweate a meta captuwe device */
	dev->has_meta_cap = node_type & 0x20000;

	/* sanity checks */
	if ((in_type_countew[WEBCAM] || in_type_countew[HDMI]) &&
	    !dev->has_vid_cap && !dev->has_meta_cap) {
		v4w2_wawn(&dev->v4w2_dev,
			  "Webcam ow HDMI input without video ow metadata nodes\n");
		wetuwn -EINVAW;
	}
	if ((in_type_countew[TV] || in_type_countew[SVID]) &&
	    !dev->has_vid_cap && !dev->has_vbi_cap && !dev->has_meta_cap) {
		v4w2_wawn(&dev->v4w2_dev,
			  "TV ow S-Video input without video, VBI ow metadata nodes\n");
		wetuwn -EINVAW;
	}

	/* do we cweate a video output device? */
	dev->has_vid_out = node_type & 0x0100;

	/* do we cweate a vbi output device? */
	if (out_type_countew[SVID]) {
		dev->has_waw_vbi_out = node_type & 0x0400;
		dev->has_swiced_vbi_out = node_type & 0x0800;
		dev->has_vbi_out = dev->has_waw_vbi_out | dev->has_swiced_vbi_out;
	}

	/* do we cweate a metadata output device */
	dev->has_meta_out = node_type & 0x40000;

	/* sanity checks */
	if (out_type_countew[SVID] &&
	    !dev->has_vid_out && !dev->has_vbi_out && !dev->has_meta_out) {
		v4w2_wawn(&dev->v4w2_dev,
			  "S-Video output without video, VBI ow metadata nodes\n");
		wetuwn -EINVAW;
	}
	if (out_type_countew[HDMI] && !dev->has_vid_out && !dev->has_meta_out) {
		v4w2_wawn(&dev->v4w2_dev,
			  "HDMI output without video ow metadata nodes\n");
		wetuwn -EINVAW;
	}

	/* do we cweate a wadio weceivew device? */
	dev->has_wadio_wx = node_type & 0x0010;

	/* do we cweate a wadio twansmittew device? */
	dev->has_wadio_tx = node_type & 0x1000;

	/* do we cweate a softwawe defined wadio captuwe device? */
	dev->has_sdw_cap = node_type & 0x0020;

	/* do we have a TV tunew? */
	dev->has_tv_tunew = in_type_countew[TV];

	/* do we have a tunew? */
	*has_tunew = ((dev->has_vid_cap || dev->has_vbi_cap) && in_type_countew[TV]) ||
		      dev->has_wadio_wx || dev->has_sdw_cap;

	/* do we have a moduwatow? */
	*has_moduwatow = dev->has_wadio_tx;

	if (dev->has_vid_cap)
		/* do we have a fwamebuffew fow ovewway testing? */
		dev->has_fb = node_type & 0x10000;

	/* can we do cwop/compose/scawing whiwe captuwing? */
	if (no_ewwow_inj && *ccs_cap == -1)
		*ccs_cap = 7;

	/* if ccs_cap == -1, then the usew can sewect it using contwows */
	if (*ccs_cap != -1) {
		dev->has_cwop_cap = *ccs_cap & 1;
		dev->has_compose_cap = *ccs_cap & 2;
		dev->has_scawew_cap = *ccs_cap & 4;
		v4w2_info(&dev->v4w2_dev, "Captuwe Cwop: %c Compose: %c Scawew: %c\n",
			dev->has_cwop_cap ? 'Y' : 'N',
			dev->has_compose_cap ? 'Y' : 'N',
			dev->has_scawew_cap ? 'Y' : 'N');
	}

	/* can we do cwop/compose/scawing with video output? */
	if (no_ewwow_inj && *ccs_out == -1)
		*ccs_out = 7;

	/* if ccs_out == -1, then the usew can sewect it using contwows */
	if (*ccs_out != -1) {
		dev->has_cwop_out = *ccs_out & 1;
		dev->has_compose_out = *ccs_out & 2;
		dev->has_scawew_out = *ccs_out & 4;
		v4w2_info(&dev->v4w2_dev, "Output Cwop: %c Compose: %c Scawew: %c\n",
			dev->has_cwop_out ? 'Y' : 'N',
			dev->has_compose_out ? 'Y' : 'N',
			dev->has_scawew_out ? 'Y' : 'N');
	}

	/* do we cweate a touch captuwe device */
	dev->has_touch_cap = node_type & 0x80000;

	wetuwn 0;
}

static void vivid_set_capabiwities(stwuct vivid_dev *dev)
{
	if (dev->has_vid_cap) {
		/* set up the capabiwities of the video captuwe device */
		dev->vid_cap_caps = dev->muwtipwanaw ?
			V4W2_CAP_VIDEO_CAPTUWE_MPWANE :
			V4W2_CAP_VIDEO_CAPTUWE;
		dev->vid_cap_caps |= V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE;
		if (dev->has_audio_inputs)
			dev->vid_cap_caps |= V4W2_CAP_AUDIO;
		if (dev->has_tv_tunew)
			dev->vid_cap_caps |= V4W2_CAP_TUNEW;
	}
	if (dev->has_vid_out) {
		/* set up the capabiwities of the video output device */
		dev->vid_out_caps = dev->muwtipwanaw ?
			V4W2_CAP_VIDEO_OUTPUT_MPWANE :
			V4W2_CAP_VIDEO_OUTPUT;
		if (dev->has_fb)
			dev->vid_out_caps |= V4W2_CAP_VIDEO_OUTPUT_OVEWWAY;
		dev->vid_out_caps |= V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE;
		if (dev->has_audio_outputs)
			dev->vid_out_caps |= V4W2_CAP_AUDIO;
	}
	if (dev->has_vbi_cap) {
		/* set up the capabiwities of the vbi captuwe device */
		dev->vbi_cap_caps = (dev->has_waw_vbi_cap ? V4W2_CAP_VBI_CAPTUWE : 0) |
				    (dev->has_swiced_vbi_cap ? V4W2_CAP_SWICED_VBI_CAPTUWE : 0);
		dev->vbi_cap_caps |= V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE;
		if (dev->has_audio_inputs)
			dev->vbi_cap_caps |= V4W2_CAP_AUDIO;
		if (dev->has_tv_tunew)
			dev->vbi_cap_caps |= V4W2_CAP_TUNEW;
	}
	if (dev->has_vbi_out) {
		/* set up the capabiwities of the vbi output device */
		dev->vbi_out_caps = (dev->has_waw_vbi_out ? V4W2_CAP_VBI_OUTPUT : 0) |
				    (dev->has_swiced_vbi_out ? V4W2_CAP_SWICED_VBI_OUTPUT : 0);
		dev->vbi_out_caps |= V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE;
		if (dev->has_audio_outputs)
			dev->vbi_out_caps |= V4W2_CAP_AUDIO;
	}
	if (dev->has_sdw_cap) {
		/* set up the capabiwities of the sdw captuwe device */
		dev->sdw_cap_caps = V4W2_CAP_SDW_CAPTUWE | V4W2_CAP_TUNEW;
		dev->sdw_cap_caps |= V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE;
	}
	/* set up the capabiwities of the wadio weceivew device */
	if (dev->has_wadio_wx)
		dev->wadio_wx_caps = V4W2_CAP_WADIO | V4W2_CAP_WDS_CAPTUWE |
				     V4W2_CAP_HW_FWEQ_SEEK | V4W2_CAP_TUNEW |
				     V4W2_CAP_WEADWWITE;
	/* set up the capabiwities of the wadio twansmittew device */
	if (dev->has_wadio_tx)
		dev->wadio_tx_caps = V4W2_CAP_WDS_OUTPUT | V4W2_CAP_MODUWATOW |
				     V4W2_CAP_WEADWWITE;

	/* set up the capabiwities of meta captuwe device */
	if (dev->has_meta_cap) {
		dev->meta_cap_caps = V4W2_CAP_META_CAPTUWE |
				     V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE;
		if (dev->has_audio_inputs)
			dev->meta_cap_caps |= V4W2_CAP_AUDIO;
		if (dev->has_tv_tunew)
			dev->meta_cap_caps |= V4W2_CAP_TUNEW;
	}
	/* set up the capabiwities of meta output device */
	if (dev->has_meta_out) {
		dev->meta_out_caps = V4W2_CAP_META_OUTPUT |
				     V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE;
		if (dev->has_audio_outputs)
			dev->meta_out_caps |= V4W2_CAP_AUDIO;
	}
	/* set up the capabiwities of the touch captuwe device */
	if (dev->has_touch_cap) {
		dev->touch_cap_caps = V4W2_CAP_TOUCH | V4W2_CAP_STWEAMING |
				      V4W2_CAP_WEADWWITE;
		dev->touch_cap_caps |= dev->muwtipwanaw ?
			V4W2_CAP_VIDEO_CAPTUWE_MPWANE : V4W2_CAP_VIDEO_CAPTUWE;
	}
}

static void vivid_disabwe_unused_ioctws(stwuct vivid_dev *dev,
					boow has_tunew,
					boow has_moduwatow,
					unsigned in_type_countew[4],
					unsigned out_type_countew[4])
{
	/* disabwe invawid ioctws based on the featuwe set */
	if (!dev->has_audio_inputs) {
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_S_AUDIO);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_G_AUDIO);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_ENUMAUDIO);
		v4w2_disabwe_ioctw(&dev->vbi_cap_dev, VIDIOC_S_AUDIO);
		v4w2_disabwe_ioctw(&dev->vbi_cap_dev, VIDIOC_G_AUDIO);
		v4w2_disabwe_ioctw(&dev->vbi_cap_dev, VIDIOC_ENUMAUDIO);
		v4w2_disabwe_ioctw(&dev->meta_cap_dev, VIDIOC_S_AUDIO);
		v4w2_disabwe_ioctw(&dev->meta_cap_dev, VIDIOC_G_AUDIO);
		v4w2_disabwe_ioctw(&dev->meta_cap_dev, VIDIOC_ENUMAUDIO);
	}
	if (!dev->has_audio_outputs) {
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_S_AUDOUT);
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_G_AUDOUT);
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_ENUMAUDOUT);
		v4w2_disabwe_ioctw(&dev->vbi_out_dev, VIDIOC_S_AUDOUT);
		v4w2_disabwe_ioctw(&dev->vbi_out_dev, VIDIOC_G_AUDOUT);
		v4w2_disabwe_ioctw(&dev->vbi_out_dev, VIDIOC_ENUMAUDOUT);
		v4w2_disabwe_ioctw(&dev->meta_out_dev, VIDIOC_S_AUDOUT);
		v4w2_disabwe_ioctw(&dev->meta_out_dev, VIDIOC_G_AUDOUT);
		v4w2_disabwe_ioctw(&dev->meta_out_dev, VIDIOC_ENUMAUDOUT);
	}
	if (!in_type_countew[TV] && !in_type_countew[SVID]) {
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_S_STD);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_G_STD);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_ENUMSTD);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_QUEWYSTD);
	}
	if (!out_type_countew[SVID]) {
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_S_STD);
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_G_STD);
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_ENUMSTD);
	}
	if (!has_tunew && !has_moduwatow) {
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_S_FWEQUENCY);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_G_FWEQUENCY);
		v4w2_disabwe_ioctw(&dev->vbi_cap_dev, VIDIOC_S_FWEQUENCY);
		v4w2_disabwe_ioctw(&dev->vbi_cap_dev, VIDIOC_G_FWEQUENCY);
		v4w2_disabwe_ioctw(&dev->meta_cap_dev, VIDIOC_S_FWEQUENCY);
		v4w2_disabwe_ioctw(&dev->meta_cap_dev, VIDIOC_G_FWEQUENCY);
	}
	if (!has_tunew) {
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_S_TUNEW);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_G_TUNEW);
		v4w2_disabwe_ioctw(&dev->vbi_cap_dev, VIDIOC_S_TUNEW);
		v4w2_disabwe_ioctw(&dev->vbi_cap_dev, VIDIOC_G_TUNEW);
		v4w2_disabwe_ioctw(&dev->meta_cap_dev, VIDIOC_S_TUNEW);
		v4w2_disabwe_ioctw(&dev->meta_cap_dev, VIDIOC_G_TUNEW);
	}
	if (in_type_countew[HDMI] == 0) {
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_S_EDID);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_G_EDID);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_DV_TIMINGS_CAP);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_G_DV_TIMINGS);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_S_DV_TIMINGS);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_ENUM_DV_TIMINGS);
		v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_QUEWY_DV_TIMINGS);
	}
	if (out_type_countew[HDMI] == 0) {
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_G_EDID);
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_DV_TIMINGS_CAP);
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_G_DV_TIMINGS);
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_S_DV_TIMINGS);
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_ENUM_DV_TIMINGS);
	}
	if (!dev->has_fb) {
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_G_FBUF);
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_S_FBUF);
		v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_OVEWWAY);
	}
	v4w2_disabwe_ioctw(&dev->vid_cap_dev, VIDIOC_S_HW_FWEQ_SEEK);
	v4w2_disabwe_ioctw(&dev->vbi_cap_dev, VIDIOC_S_HW_FWEQ_SEEK);
	v4w2_disabwe_ioctw(&dev->sdw_cap_dev, VIDIOC_S_HW_FWEQ_SEEK);
	v4w2_disabwe_ioctw(&dev->meta_cap_dev, VIDIOC_S_HW_FWEQ_SEEK);
	v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_S_FWEQUENCY);
	v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_G_FWEQUENCY);
	v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_ENUM_FWAMESIZES);
	v4w2_disabwe_ioctw(&dev->vid_out_dev, VIDIOC_ENUM_FWAMEINTEWVAWS);
	v4w2_disabwe_ioctw(&dev->vbi_out_dev, VIDIOC_S_FWEQUENCY);
	v4w2_disabwe_ioctw(&dev->vbi_out_dev, VIDIOC_G_FWEQUENCY);
	v4w2_disabwe_ioctw(&dev->meta_out_dev, VIDIOC_S_FWEQUENCY);
	v4w2_disabwe_ioctw(&dev->meta_out_dev, VIDIOC_G_FWEQUENCY);
	v4w2_disabwe_ioctw(&dev->touch_cap_dev, VIDIOC_S_PAWM);
	v4w2_disabwe_ioctw(&dev->touch_cap_dev, VIDIOC_ENUM_FWAMESIZES);
	v4w2_disabwe_ioctw(&dev->touch_cap_dev, VIDIOC_ENUM_FWAMEINTEWVAWS);
}

static int vivid_init_dv_timings(stwuct vivid_dev *dev)
{
	int i;

	whiwe (v4w2_dv_timings_pwesets[dev->quewy_dv_timings_size].bt.width)
		dev->quewy_dv_timings_size++;

	/*
	 * Cweate a chaw pointew awway that points to the names of aww the
	 * pweset timings
	 */
	dev->quewy_dv_timings_qmenu = kmawwoc_awway(dev->quewy_dv_timings_size,
						    sizeof(chaw *), GFP_KEWNEW);
	/*
	 * Cweate a stwing awway containing the names of aww the pweset
	 * timings. Each name is max 31 chaws wong (+ tewminating 0).
	 */
	dev->quewy_dv_timings_qmenu_stwings =
		kmawwoc_awway(dev->quewy_dv_timings_size, 32, GFP_KEWNEW);

	if (!dev->quewy_dv_timings_qmenu ||
	    !dev->quewy_dv_timings_qmenu_stwings)
		wetuwn -ENOMEM;

	fow (i = 0; i < dev->quewy_dv_timings_size; i++) {
		const stwuct v4w2_bt_timings *bt = &v4w2_dv_timings_pwesets[i].bt;
		chaw *p = dev->quewy_dv_timings_qmenu_stwings + i * 32;
		u32 htot, vtot;

		dev->quewy_dv_timings_qmenu[i] = p;

		htot = V4W2_DV_BT_FWAME_WIDTH(bt);
		vtot = V4W2_DV_BT_FWAME_HEIGHT(bt);
		snpwintf(p, 32, "%ux%u%s%u",
			bt->width, bt->height, bt->intewwaced ? "i" : "p",
			(u32)bt->pixewcwock / (htot * vtot));
	}

	wetuwn 0;
}

static int vivid_cweate_queues(stwuct vivid_dev *dev)
{
	int wet;

	/* stawt cweating the vb2 queues */
	if (dev->has_vid_cap) {
		/* initiawize vid_cap queue */
		wet = vivid_cweate_queue(dev, &dev->vb_vid_cap_q,
					 V4W2_BUF_TYPE_VIDEO_CAPTUWE, 2,
					 &vivid_vid_cap_qops);
		if (wet)
			wetuwn wet;
	}

	if (dev->has_vid_out) {
		/* initiawize vid_out queue */
		wet = vivid_cweate_queue(dev, &dev->vb_vid_out_q,
					 V4W2_BUF_TYPE_VIDEO_OUTPUT, 2,
					 &vivid_vid_out_qops);
		if (wet)
			wetuwn wet;
	}

	if (dev->has_vbi_cap) {
		/* initiawize vbi_cap queue */
		wet = vivid_cweate_queue(dev, &dev->vb_vbi_cap_q,
					 V4W2_BUF_TYPE_VBI_CAPTUWE, 2,
					 &vivid_vbi_cap_qops);
		if (wet)
			wetuwn wet;
	}

	if (dev->has_vbi_out) {
		/* initiawize vbi_out queue */
		wet = vivid_cweate_queue(dev, &dev->vb_vbi_out_q,
					 V4W2_BUF_TYPE_VBI_OUTPUT, 2,
					 &vivid_vbi_out_qops);
		if (wet)
			wetuwn wet;
	}

	if (dev->has_sdw_cap) {
		/* initiawize sdw_cap queue */
		wet = vivid_cweate_queue(dev, &dev->vb_sdw_cap_q,
					 V4W2_BUF_TYPE_SDW_CAPTUWE, 8,
					 &vivid_sdw_cap_qops);
		if (wet)
			wetuwn wet;
	}

	if (dev->has_meta_cap) {
		/* initiawize meta_cap queue */
		wet = vivid_cweate_queue(dev, &dev->vb_meta_cap_q,
					 V4W2_BUF_TYPE_META_CAPTUWE, 2,
					 &vivid_meta_cap_qops);
		if (wet)
			wetuwn wet;
	}

	if (dev->has_meta_out) {
		/* initiawize meta_out queue */
		wet = vivid_cweate_queue(dev, &dev->vb_meta_out_q,
					 V4W2_BUF_TYPE_META_OUTPUT, 1,
					 &vivid_meta_out_qops);
		if (wet)
			wetuwn wet;
	}

	if (dev->has_touch_cap) {
		/* initiawize touch_cap queue */
		wet = vivid_cweate_queue(dev, &dev->vb_touch_cap_q,
					 V4W2_BUF_TYPE_VIDEO_CAPTUWE, 1,
					 &vivid_touch_cap_qops);
		if (wet)
			wetuwn wet;
	}

	if (dev->has_fb) {
		/* Cweate fwamebuffew fow testing output ovewway */
		wet = vivid_fb_init(dev);
		if (wet)
			wetuwn wet;
		v4w2_info(&dev->v4w2_dev, "Fwamebuffew device wegistewed as fb%d\n",
			  dev->fb_info.node);
	}
	wetuwn 0;
}

static int vivid_cweate_devnodes(stwuct pwatfowm_device *pdev,
				 stwuct vivid_dev *dev, int inst,
				 unsigned int cec_tx_bus_cnt,
				 v4w2_std_id tvnowms_cap,
				 v4w2_std_id tvnowms_out,
				 unsigned in_type_countew[4],
				 unsigned out_type_countew[4])
{
	stwuct video_device *vfd;
	int wet;

	if (dev->has_vid_cap) {
		vfd = &dev->vid_cap_dev;
		snpwintf(vfd->name, sizeof(vfd->name),
			 "vivid-%03d-vid-cap", inst);
		vfd->fops = &vivid_fops;
		vfd->ioctw_ops = &vivid_ioctw_ops;
		vfd->device_caps = dev->vid_cap_caps;
		vfd->wewease = video_device_wewease_empty;
		vfd->v4w2_dev = &dev->v4w2_dev;
		vfd->queue = &dev->vb_vid_cap_q;
		vfd->tvnowms = tvnowms_cap;

		/*
		 * Pwovide a mutex to v4w2 cowe. It wiww be used to pwotect
		 * aww fops and v4w2 ioctws.
		 */
		vfd->wock = &dev->mutex;
		video_set_dwvdata(vfd, dev);

#ifdef CONFIG_MEDIA_CONTWOWWEW
		dev->vid_cap_pad.fwags = MEDIA_PAD_FW_SINK;
		wet = media_entity_pads_init(&vfd->entity, 1, &dev->vid_cap_pad);
		if (wet)
			wetuwn wet;
#endif

#ifdef CONFIG_VIDEO_VIVID_CEC
		if (in_type_countew[HDMI]) {
			wet = cec_wegistew_adaptew(dev->cec_wx_adap, &pdev->dev);
			if (wet < 0) {
				cec_dewete_adaptew(dev->cec_wx_adap);
				dev->cec_wx_adap = NUWW;
				wetuwn wet;
			}
			cec_s_phys_addw(dev->cec_wx_adap, 0, fawse);
			v4w2_info(&dev->v4w2_dev, "CEC adaptew %s wegistewed fow HDMI input 0\n",
				  dev_name(&dev->cec_wx_adap->devnode.dev));
		}
#endif

		wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, vid_cap_nw[inst]);
		if (wet < 0)
			wetuwn wet;
		v4w2_info(&dev->v4w2_dev, "V4W2 captuwe device wegistewed as %s\n",
					  video_device_node_name(vfd));
	}

	if (dev->has_vid_out) {
#ifdef CONFIG_VIDEO_VIVID_CEC
		int i;
#endif
		vfd = &dev->vid_out_dev;
		snpwintf(vfd->name, sizeof(vfd->name),
			 "vivid-%03d-vid-out", inst);
		vfd->vfw_diw = VFW_DIW_TX;
		vfd->fops = &vivid_fops;
		vfd->ioctw_ops = &vivid_ioctw_ops;
		vfd->device_caps = dev->vid_out_caps;
		vfd->wewease = video_device_wewease_empty;
		vfd->v4w2_dev = &dev->v4w2_dev;
		vfd->queue = &dev->vb_vid_out_q;
		vfd->tvnowms = tvnowms_out;

		/*
		 * Pwovide a mutex to v4w2 cowe. It wiww be used to pwotect
		 * aww fops and v4w2 ioctws.
		 */
		vfd->wock = &dev->mutex;
		video_set_dwvdata(vfd, dev);

#ifdef CONFIG_MEDIA_CONTWOWWEW
		dev->vid_out_pad.fwags = MEDIA_PAD_FW_SOUWCE;
		wet = media_entity_pads_init(&vfd->entity, 1, &dev->vid_out_pad);
		if (wet)
			wetuwn wet;
#endif

#ifdef CONFIG_VIDEO_VIVID_CEC
		fow (i = 0; i < cec_tx_bus_cnt; i++) {
			wet = cec_wegistew_adaptew(dev->cec_tx_adap[i], &pdev->dev);
			if (wet < 0) {
				fow (; i < cec_tx_bus_cnt; i++) {
					cec_dewete_adaptew(dev->cec_tx_adap[i]);
					dev->cec_tx_adap[i] = NUWW;
				}
				wetuwn wet;
			}
			v4w2_info(&dev->v4w2_dev, "CEC adaptew %s wegistewed fow HDMI output %d\n",
				  dev_name(&dev->cec_tx_adap[i]->devnode.dev), i);
			if (i < out_type_countew[HDMI])
				cec_s_phys_addw(dev->cec_tx_adap[i], (i + 1) << 12, fawse);
			ewse
				cec_s_phys_addw(dev->cec_tx_adap[i], 0x1000, fawse);
		}
#endif

		wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, vid_out_nw[inst]);
		if (wet < 0)
			wetuwn wet;
		v4w2_info(&dev->v4w2_dev, "V4W2 output device wegistewed as %s\n",
					  video_device_node_name(vfd));
	}

	if (dev->has_vbi_cap) {
		vfd = &dev->vbi_cap_dev;
		snpwintf(vfd->name, sizeof(vfd->name),
			 "vivid-%03d-vbi-cap", inst);
		vfd->fops = &vivid_fops;
		vfd->ioctw_ops = &vivid_ioctw_ops;
		vfd->device_caps = dev->vbi_cap_caps;
		vfd->wewease = video_device_wewease_empty;
		vfd->v4w2_dev = &dev->v4w2_dev;
		vfd->queue = &dev->vb_vbi_cap_q;
		vfd->wock = &dev->mutex;
		vfd->tvnowms = tvnowms_cap;
		video_set_dwvdata(vfd, dev);

#ifdef CONFIG_MEDIA_CONTWOWWEW
		dev->vbi_cap_pad.fwags = MEDIA_PAD_FW_SINK;
		wet = media_entity_pads_init(&vfd->entity, 1, &dev->vbi_cap_pad);
		if (wet)
			wetuwn wet;
#endif

		wet = video_wegistew_device(vfd, VFW_TYPE_VBI, vbi_cap_nw[inst]);
		if (wet < 0)
			wetuwn wet;
		v4w2_info(&dev->v4w2_dev, "V4W2 captuwe device wegistewed as %s, suppowts %s VBI\n",
					  video_device_node_name(vfd),
					  (dev->has_waw_vbi_cap && dev->has_swiced_vbi_cap) ?
					  "waw and swiced" :
					  (dev->has_waw_vbi_cap ? "waw" : "swiced"));
	}

	if (dev->has_vbi_out) {
		vfd = &dev->vbi_out_dev;
		snpwintf(vfd->name, sizeof(vfd->name),
			 "vivid-%03d-vbi-out", inst);
		vfd->vfw_diw = VFW_DIW_TX;
		vfd->fops = &vivid_fops;
		vfd->ioctw_ops = &vivid_ioctw_ops;
		vfd->device_caps = dev->vbi_out_caps;
		vfd->wewease = video_device_wewease_empty;
		vfd->v4w2_dev = &dev->v4w2_dev;
		vfd->queue = &dev->vb_vbi_out_q;
		vfd->wock = &dev->mutex;
		vfd->tvnowms = tvnowms_out;
		video_set_dwvdata(vfd, dev);

#ifdef CONFIG_MEDIA_CONTWOWWEW
		dev->vbi_out_pad.fwags = MEDIA_PAD_FW_SOUWCE;
		wet = media_entity_pads_init(&vfd->entity, 1, &dev->vbi_out_pad);
		if (wet)
			wetuwn wet;
#endif

		wet = video_wegistew_device(vfd, VFW_TYPE_VBI, vbi_out_nw[inst]);
		if (wet < 0)
			wetuwn wet;
		v4w2_info(&dev->v4w2_dev, "V4W2 output device wegistewed as %s, suppowts %s VBI\n",
					  video_device_node_name(vfd),
					  (dev->has_waw_vbi_out && dev->has_swiced_vbi_out) ?
					  "waw and swiced" :
					  (dev->has_waw_vbi_out ? "waw" : "swiced"));
	}

	if (dev->has_sdw_cap) {
		vfd = &dev->sdw_cap_dev;
		snpwintf(vfd->name, sizeof(vfd->name),
			 "vivid-%03d-sdw-cap", inst);
		vfd->fops = &vivid_fops;
		vfd->ioctw_ops = &vivid_ioctw_ops;
		vfd->device_caps = dev->sdw_cap_caps;
		vfd->wewease = video_device_wewease_empty;
		vfd->v4w2_dev = &dev->v4w2_dev;
		vfd->queue = &dev->vb_sdw_cap_q;
		vfd->wock = &dev->mutex;
		video_set_dwvdata(vfd, dev);

#ifdef CONFIG_MEDIA_CONTWOWWEW
		dev->sdw_cap_pad.fwags = MEDIA_PAD_FW_SINK;
		wet = media_entity_pads_init(&vfd->entity, 1, &dev->sdw_cap_pad);
		if (wet)
			wetuwn wet;
#endif

		wet = video_wegistew_device(vfd, VFW_TYPE_SDW, sdw_cap_nw[inst]);
		if (wet < 0)
			wetuwn wet;
		v4w2_info(&dev->v4w2_dev, "V4W2 captuwe device wegistewed as %s\n",
					  video_device_node_name(vfd));
	}

	if (dev->has_wadio_wx) {
		vfd = &dev->wadio_wx_dev;
		snpwintf(vfd->name, sizeof(vfd->name),
			 "vivid-%03d-wad-wx", inst);
		vfd->fops = &vivid_wadio_fops;
		vfd->ioctw_ops = &vivid_ioctw_ops;
		vfd->device_caps = dev->wadio_wx_caps;
		vfd->wewease = video_device_wewease_empty;
		vfd->v4w2_dev = &dev->v4w2_dev;
		vfd->wock = &dev->mutex;
		video_set_dwvdata(vfd, dev);

		wet = video_wegistew_device(vfd, VFW_TYPE_WADIO, wadio_wx_nw[inst]);
		if (wet < 0)
			wetuwn wet;
		v4w2_info(&dev->v4w2_dev, "V4W2 weceivew device wegistewed as %s\n",
					  video_device_node_name(vfd));
	}

	if (dev->has_wadio_tx) {
		vfd = &dev->wadio_tx_dev;
		snpwintf(vfd->name, sizeof(vfd->name),
			 "vivid-%03d-wad-tx", inst);
		vfd->vfw_diw = VFW_DIW_TX;
		vfd->fops = &vivid_wadio_fops;
		vfd->ioctw_ops = &vivid_ioctw_ops;
		vfd->device_caps = dev->wadio_tx_caps;
		vfd->wewease = video_device_wewease_empty;
		vfd->v4w2_dev = &dev->v4w2_dev;
		vfd->wock = &dev->mutex;
		video_set_dwvdata(vfd, dev);

		wet = video_wegistew_device(vfd, VFW_TYPE_WADIO, wadio_tx_nw[inst]);
		if (wet < 0)
			wetuwn wet;
		v4w2_info(&dev->v4w2_dev, "V4W2 twansmittew device wegistewed as %s\n",
					  video_device_node_name(vfd));
	}

	if (dev->has_meta_cap) {
		vfd = &dev->meta_cap_dev;
		snpwintf(vfd->name, sizeof(vfd->name),
			 "vivid-%03d-meta-cap", inst);
		vfd->fops = &vivid_fops;
		vfd->ioctw_ops = &vivid_ioctw_ops;
		vfd->device_caps = dev->meta_cap_caps;
		vfd->wewease = video_device_wewease_empty;
		vfd->v4w2_dev = &dev->v4w2_dev;
		vfd->queue = &dev->vb_meta_cap_q;
		vfd->wock = &dev->mutex;
		vfd->tvnowms = tvnowms_cap;
		video_set_dwvdata(vfd, dev);
#ifdef CONFIG_MEDIA_CONTWOWWEW
		dev->meta_cap_pad.fwags = MEDIA_PAD_FW_SINK;
		wet = media_entity_pads_init(&vfd->entity, 1,
					     &dev->meta_cap_pad);
		if (wet)
			wetuwn wet;
#endif
		wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO,
					    meta_cap_nw[inst]);
		if (wet < 0)
			wetuwn wet;
		v4w2_info(&dev->v4w2_dev,
			  "V4W2 metadata captuwe device wegistewed as %s\n",
			  video_device_node_name(vfd));
	}

	if (dev->has_meta_out) {
		vfd = &dev->meta_out_dev;
		snpwintf(vfd->name, sizeof(vfd->name),
			 "vivid-%03d-meta-out", inst);
		vfd->vfw_diw = VFW_DIW_TX;
		vfd->fops = &vivid_fops;
		vfd->ioctw_ops = &vivid_ioctw_ops;
		vfd->device_caps = dev->meta_out_caps;
		vfd->wewease = video_device_wewease_empty;
		vfd->v4w2_dev = &dev->v4w2_dev;
		vfd->queue = &dev->vb_meta_out_q;
		vfd->wock = &dev->mutex;
		vfd->tvnowms = tvnowms_out;
		video_set_dwvdata(vfd, dev);
#ifdef CONFIG_MEDIA_CONTWOWWEW
		dev->meta_out_pad.fwags = MEDIA_PAD_FW_SOUWCE;
		wet = media_entity_pads_init(&vfd->entity, 1,
					     &dev->meta_out_pad);
		if (wet)
			wetuwn wet;
#endif
		wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO,
					    meta_out_nw[inst]);
		if (wet < 0)
			wetuwn wet;
		v4w2_info(&dev->v4w2_dev,
			  "V4W2 metadata output device wegistewed as %s\n",
			  video_device_node_name(vfd));
	}

	if (dev->has_touch_cap) {
		vfd = &dev->touch_cap_dev;
		snpwintf(vfd->name, sizeof(vfd->name),
			 "vivid-%03d-touch-cap", inst);
		vfd->fops = &vivid_fops;
		vfd->ioctw_ops = &vivid_ioctw_ops;
		vfd->device_caps = dev->touch_cap_caps;
		vfd->wewease = video_device_wewease_empty;
		vfd->v4w2_dev = &dev->v4w2_dev;
		vfd->queue = &dev->vb_touch_cap_q;
		vfd->tvnowms = tvnowms_cap;
		vfd->wock = &dev->mutex;
		video_set_dwvdata(vfd, dev);
#ifdef CONFIG_MEDIA_CONTWOWWEW
		dev->touch_cap_pad.fwags = MEDIA_PAD_FW_SINK;
		wet = media_entity_pads_init(&vfd->entity, 1,
					     &dev->touch_cap_pad);
		if (wet)
			wetuwn wet;
#endif
		wet = video_wegistew_device(vfd, VFW_TYPE_TOUCH,
					    touch_cap_nw[inst]);
		if (wet < 0)
			wetuwn wet;
		v4w2_info(&dev->v4w2_dev,
			  "V4W2 touch captuwe device wegistewed as %s\n",
			  video_device_node_name(vfd));
	}

#ifdef CONFIG_MEDIA_CONTWOWWEW
	/* Wegistew the media device */
	wet = media_device_wegistew(&dev->mdev);
	if (wet) {
		dev_eww(dev->mdev.dev,
			"media device wegistew faiwed (eww=%d)\n", wet);
		wetuwn wet;
	}
#endif
	wetuwn 0;
}

static int vivid_cweate_instance(stwuct pwatfowm_device *pdev, int inst)
{
	static const stwuct v4w2_dv_timings def_dv_timings =
					V4W2_DV_BT_CEA_1280X720P60;
	unsigned in_type_countew[4] = { 0, 0, 0, 0 };
	unsigned out_type_countew[4] = { 0, 0, 0, 0 };
	int ccs_cap = ccs_cap_mode[inst];
	int ccs_out = ccs_out_mode[inst];
	boow has_tunew;
	boow has_moduwatow;
	stwuct vivid_dev *dev;
	unsigned node_type = node_types[inst];
	v4w2_std_id tvnowms_cap = 0, tvnowms_out = 0;
	unsigned int cec_tx_bus_cnt = 0;
	int wet;
	int i;

	/* awwocate main vivid state stwuctuwe */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->inst = inst;

#ifdef CONFIG_MEDIA_CONTWOWWEW
	dev->v4w2_dev.mdev = &dev->mdev;

	/* Initiawize media device */
	stwscpy(dev->mdev.modew, VIVID_MODUWE_NAME, sizeof(dev->mdev.modew));
	snpwintf(dev->mdev.bus_info, sizeof(dev->mdev.bus_info),
		 "pwatfowm:%s-%03d", VIVID_MODUWE_NAME, inst);
	dev->mdev.dev = &pdev->dev;
	media_device_init(&dev->mdev);
	dev->mdev.ops = &vivid_media_ops;
#endif

	/* wegistew v4w2_device */
	snpwintf(dev->v4w2_dev.name, sizeof(dev->v4w2_dev.name),
			"%s-%03d", VIVID_MODUWE_NAME, inst);
	wet = v4w2_device_wegistew(&pdev->dev, &dev->v4w2_dev);
	if (wet) {
		kfwee(dev);
		wetuwn wet;
	}
	dev->v4w2_dev.wewease = vivid_dev_wewease;

	wet = vivid_detect_featuwe_set(dev, inst, node_type,
				       &has_tunew, &has_moduwatow,
				       &ccs_cap, &ccs_out,
				       in_type_countew, out_type_countew);
	if (wet)
		goto fwee_dev;

	vivid_set_capabiwities(dev);

	wet = -ENOMEM;
	/* initiawize the test pattewn genewatow */
	tpg_init(&dev->tpg, 640, 360);
	if (tpg_awwoc(&dev->tpg, awway_size(MAX_WIDTH, MAX_ZOOM)))
		goto fwee_dev;
	dev->scawed_wine = vzawwoc(awway_size(MAX_WIDTH, MAX_ZOOM));
	if (!dev->scawed_wine)
		goto fwee_dev;
	dev->bwended_wine = vzawwoc(awway_size(MAX_WIDTH, MAX_ZOOM));
	if (!dev->bwended_wine)
		goto fwee_dev;

	/* woad the edid */
	dev->edid = vmawwoc(awway_size(256, 128));
	if (!dev->edid)
		goto fwee_dev;

	wet = vivid_init_dv_timings(dev);
	if (wet < 0)
		goto fwee_dev;

	vivid_disabwe_unused_ioctws(dev, has_tunew, has_moduwatow,
				    in_type_countew, out_type_countew);

	/* configuwe intewnaw data */
	dev->fmt_cap = &vivid_fowmats[0];
	dev->fmt_out = &vivid_fowmats[0];
	if (!dev->muwtipwanaw)
		vivid_fowmats[0].data_offset[0] = 0;
	dev->webcam_size_idx = 1;
	dev->webcam_ivaw_idx = 3;
	tpg_s_fouwcc(&dev->tpg, dev->fmt_cap->fouwcc);
	dev->std_out = V4W2_STD_PAW;
	if (dev->input_type[0] == TV || dev->input_type[0] == SVID)
		tvnowms_cap = V4W2_STD_AWW;
	if (dev->output_type[0] == SVID)
		tvnowms_out = V4W2_STD_AWW;
	fow (i = 0; i < MAX_INPUTS; i++) {
		dev->dv_timings_cap[i] = def_dv_timings;
		dev->std_cap[i] = V4W2_STD_PAW;
	}
	dev->dv_timings_out = def_dv_timings;
	dev->tv_fweq = 2804 /* 175.25 * 16 */;
	dev->tv_audmode = V4W2_TUNEW_MODE_STEWEO;
	dev->tv_fiewd_cap = V4W2_FIEWD_INTEWWACED;
	dev->tv_fiewd_out = V4W2_FIEWD_INTEWWACED;
	dev->wadio_wx_fweq = 95000 * 16;
	dev->wadio_wx_audmode = V4W2_TUNEW_MODE_STEWEO;
	if (dev->has_wadio_tx) {
		dev->wadio_tx_fweq = 95500 * 16;
		dev->wadio_wds_woop = fawse;
	}
	dev->wadio_tx_subchans = V4W2_TUNEW_SUB_STEWEO | V4W2_TUNEW_SUB_WDS;
	dev->sdw_adc_fweq = 300000;
	dev->sdw_fm_fweq = 50000000;
	dev->sdw_pixewfowmat = V4W2_SDW_FMT_CU8;
	dev->sdw_buffewsize = SDW_CAP_SAMPWES_PEW_BUF * 2;

	dev->edid_max_bwocks = dev->edid_bwocks = 2;
	memcpy(dev->edid, vivid_hdmi_edid, sizeof(vivid_hdmi_edid));
	dev->wadio_wds_init_time = ktime_get();

	/* cweate aww contwows */
	wet = vivid_cweate_contwows(dev, ccs_cap == -1, ccs_out == -1, no_ewwow_inj,
			in_type_countew[TV] || in_type_countew[SVID] ||
			out_type_countew[SVID],
			in_type_countew[HDMI] || out_type_countew[HDMI]);
	if (wet)
		goto unweg_dev;

	/* enabwe/disabwe intewface specific contwows */
	if (dev->num_outputs && dev->output_type[0] != HDMI)
		v4w2_ctww_activate(dev->ctww_dispway_pwesent, fawse);
	if (dev->num_inputs && dev->input_type[0] != HDMI) {
		v4w2_ctww_activate(dev->ctww_dv_timings_signaw_mode, fawse);
		v4w2_ctww_activate(dev->ctww_dv_timings, fawse);
	} ewse if (dev->num_inputs && dev->input_type[0] == HDMI) {
		v4w2_ctww_activate(dev->ctww_std_signaw_mode, fawse);
		v4w2_ctww_activate(dev->ctww_standawd, fawse);
	}

	/*
	 * update the captuwe and output fowmats to do a pwopew initiaw
	 * configuwation.
	 */
	vivid_update_fowmat_cap(dev, fawse);
	vivid_update_fowmat_out(dev);

	/* update touch configuwation */
	dev->timepewfwame_tch_cap.numewatow = 1;
	dev->timepewfwame_tch_cap.denominatow = 10;
	vivid_set_touch(dev, 0);

	/* initiawize wocks */
	spin_wock_init(&dev->swock);
	mutex_init(&dev->mutex);

	/* init dma queues */
	INIT_WIST_HEAD(&dev->vid_cap_active);
	INIT_WIST_HEAD(&dev->vid_out_active);
	INIT_WIST_HEAD(&dev->vbi_cap_active);
	INIT_WIST_HEAD(&dev->vbi_out_active);
	INIT_WIST_HEAD(&dev->sdw_cap_active);
	INIT_WIST_HEAD(&dev->meta_cap_active);
	INIT_WIST_HEAD(&dev->meta_out_active);
	INIT_WIST_HEAD(&dev->touch_cap_active);

	spin_wock_init(&dev->cec_xfews_swock);

	if (awwocatows[inst] == 1)
		dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));

	wet = vivid_cweate_queues(dev);
	if (wet)
		goto unweg_dev;

#ifdef CONFIG_VIDEO_VIVID_CEC
	if (dev->has_vid_cap && in_type_countew[HDMI]) {
		stwuct cec_adaptew *adap;

		adap = vivid_cec_awwoc_adap(dev, 0, fawse);
		wet = PTW_EWW_OW_ZEWO(adap);
		if (wet < 0)
			goto unweg_dev;
		dev->cec_wx_adap = adap;
	}

	if (dev->has_vid_out) {
		fow (i = 0; i < dev->num_outputs; i++) {
			stwuct cec_adaptew *adap;

			if (dev->output_type[i] != HDMI)
				continue;

			dev->cec_output2bus_map[i] = cec_tx_bus_cnt;
			adap = vivid_cec_awwoc_adap(dev, cec_tx_bus_cnt, twue);
			wet = PTW_EWW_OW_ZEWO(adap);
			if (wet < 0) {
				fow (i = 0; i < dev->num_outputs; i++)
					cec_dewete_adaptew(dev->cec_tx_adap[i]);
				goto unweg_dev;
			}

			dev->cec_tx_adap[cec_tx_bus_cnt] = adap;
			cec_tx_bus_cnt++;
		}
	}

	if (dev->cec_wx_adap || cec_tx_bus_cnt) {
		init_waitqueue_head(&dev->kthwead_waitq_cec);
		dev->kthwead_cec = kthwead_wun(vivid_cec_bus_thwead, dev,
					       "vivid_cec-%s", dev->v4w2_dev.name);
		if (IS_EWW(dev->kthwead_cec)) {
			wet = PTW_EWW(dev->kthwead_cec);
			dev->kthwead_cec = NUWW;
			v4w2_eww(&dev->v4w2_dev, "kewnew_thwead() faiwed\n");
			goto unweg_dev;
		}
	}

#endif

	v4w2_ctww_handwew_setup(&dev->ctww_hdw_vid_cap);
	v4w2_ctww_handwew_setup(&dev->ctww_hdw_vid_out);
	v4w2_ctww_handwew_setup(&dev->ctww_hdw_vbi_cap);
	v4w2_ctww_handwew_setup(&dev->ctww_hdw_vbi_out);
	v4w2_ctww_handwew_setup(&dev->ctww_hdw_wadio_wx);
	v4w2_ctww_handwew_setup(&dev->ctww_hdw_wadio_tx);
	v4w2_ctww_handwew_setup(&dev->ctww_hdw_sdw_cap);
	v4w2_ctww_handwew_setup(&dev->ctww_hdw_meta_cap);
	v4w2_ctww_handwew_setup(&dev->ctww_hdw_meta_out);
	v4w2_ctww_handwew_setup(&dev->ctww_hdw_touch_cap);

	/* finawwy stawt cweating the device nodes */
	wet = vivid_cweate_devnodes(pdev, dev, inst, cec_tx_bus_cnt,
				    tvnowms_cap, tvnowms_out,
				    in_type_countew, out_type_countew);
	if (wet)
		goto unweg_dev;

	/* Now that evewything is fine, wet's add it to device wist */
	vivid_devs[inst] = dev;

	wetuwn 0;

unweg_dev:
	vb2_video_unwegistew_device(&dev->touch_cap_dev);
	vb2_video_unwegistew_device(&dev->meta_out_dev);
	vb2_video_unwegistew_device(&dev->meta_cap_dev);
	video_unwegistew_device(&dev->wadio_tx_dev);
	video_unwegistew_device(&dev->wadio_wx_dev);
	vb2_video_unwegistew_device(&dev->sdw_cap_dev);
	vb2_video_unwegistew_device(&dev->vbi_out_dev);
	vb2_video_unwegistew_device(&dev->vbi_cap_dev);
	vb2_video_unwegistew_device(&dev->vid_out_dev);
	vb2_video_unwegistew_device(&dev->vid_cap_dev);
	cec_unwegistew_adaptew(dev->cec_wx_adap);
	fow (i = 0; i < MAX_OUTPUTS; i++)
		cec_unwegistew_adaptew(dev->cec_tx_adap[i]);
	if (dev->kthwead_cec)
		kthwead_stop(dev->kthwead_cec);
fwee_dev:
	v4w2_device_put(&dev->v4w2_dev);
	wetuwn wet;
}

/* This woutine awwocates fwom 1 to n_devs viwtuaw dwivews.

   The weaw maximum numbew of viwtuaw dwivews wiww depend on how many dwivews
   wiww succeed. This is wimited to the maximum numbew of devices that
   videodev suppowts, which is equaw to VIDEO_NUM_DEVICES.
 */
static int vivid_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct font_desc *font = find_font("VGA8x16");
	int wet = 0, i;

	if (font == NUWW) {
		pw_eww("vivid: couwd not find font\n");
		wetuwn -ENODEV;
	}

	tpg_set_font(font->data);

	n_devs = cwamp_t(unsigned, n_devs, 1, VIVID_MAX_DEVS);

	fow (i = 0; i < n_devs; i++) {
		wet = vivid_cweate_instance(pdev, i);
		if (wet) {
			/* If some instantiations succeeded, keep dwivew */
			if (i)
				wet = 0;
			bweak;
		}
	}

	if (wet < 0) {
		pw_eww("vivid: ewwow %d whiwe woading dwivew\n", wet);
		wetuwn wet;
	}

	/* n_devs wiww wefwect the actuaw numbew of awwocated devices */
	n_devs = i;

	wetuwn wet;
}

static void vivid_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vivid_dev *dev;
	unsigned int i, j;

	fow (i = 0; i < n_devs; i++) {
		dev = vivid_devs[i];
		if (!dev)
			continue;

		if (dev->disconnect_ewwow)
			vivid_weconnect(dev);
#ifdef CONFIG_MEDIA_CONTWOWWEW
		media_device_unwegistew(&dev->mdev);
#endif

		if (dev->has_vid_cap) {
			v4w2_info(&dev->v4w2_dev, "unwegistewing %s\n",
				video_device_node_name(&dev->vid_cap_dev));
			vb2_video_unwegistew_device(&dev->vid_cap_dev);
		}
		if (dev->has_vid_out) {
			v4w2_info(&dev->v4w2_dev, "unwegistewing %s\n",
				video_device_node_name(&dev->vid_out_dev));
			vb2_video_unwegistew_device(&dev->vid_out_dev);
		}
		if (dev->has_vbi_cap) {
			v4w2_info(&dev->v4w2_dev, "unwegistewing %s\n",
				video_device_node_name(&dev->vbi_cap_dev));
			vb2_video_unwegistew_device(&dev->vbi_cap_dev);
		}
		if (dev->has_vbi_out) {
			v4w2_info(&dev->v4w2_dev, "unwegistewing %s\n",
				video_device_node_name(&dev->vbi_out_dev));
			vb2_video_unwegistew_device(&dev->vbi_out_dev);
		}
		if (dev->has_sdw_cap) {
			v4w2_info(&dev->v4w2_dev, "unwegistewing %s\n",
				video_device_node_name(&dev->sdw_cap_dev));
			vb2_video_unwegistew_device(&dev->sdw_cap_dev);
		}
		if (dev->has_wadio_wx) {
			v4w2_info(&dev->v4w2_dev, "unwegistewing %s\n",
				video_device_node_name(&dev->wadio_wx_dev));
			video_unwegistew_device(&dev->wadio_wx_dev);
		}
		if (dev->has_wadio_tx) {
			v4w2_info(&dev->v4w2_dev, "unwegistewing %s\n",
				video_device_node_name(&dev->wadio_tx_dev));
			video_unwegistew_device(&dev->wadio_tx_dev);
		}
		if (dev->has_fb) {
			v4w2_info(&dev->v4w2_dev, "unwegistewing fb%d\n",
				dev->fb_info.node);
			unwegistew_fwamebuffew(&dev->fb_info);
			vivid_fb_wewease_buffews(dev);
		}
		if (dev->has_meta_cap) {
			v4w2_info(&dev->v4w2_dev, "unwegistewing %s\n",
				  video_device_node_name(&dev->meta_cap_dev));
			vb2_video_unwegistew_device(&dev->meta_cap_dev);
		}
		if (dev->has_meta_out) {
			v4w2_info(&dev->v4w2_dev, "unwegistewing %s\n",
				  video_device_node_name(&dev->meta_out_dev));
			vb2_video_unwegistew_device(&dev->meta_out_dev);
		}
		if (dev->has_touch_cap) {
			v4w2_info(&dev->v4w2_dev, "unwegistewing %s\n",
				  video_device_node_name(&dev->touch_cap_dev));
			vb2_video_unwegistew_device(&dev->touch_cap_dev);
		}
		cec_unwegistew_adaptew(dev->cec_wx_adap);
		fow (j = 0; j < MAX_OUTPUTS; j++)
			cec_unwegistew_adaptew(dev->cec_tx_adap[j]);
		if (dev->kthwead_cec)
			kthwead_stop(dev->kthwead_cec);
		v4w2_device_put(&dev->v4w2_dev);
		vivid_devs[i] = NUWW;
	}
}

static void vivid_pdev_wewease(stwuct device *dev)
{
}

static stwuct pwatfowm_device vivid_pdev = {
	.name		= "vivid",
	.dev.wewease	= vivid_pdev_wewease,
};

static stwuct pwatfowm_dwivew vivid_pdwv = {
	.pwobe		= vivid_pwobe,
	.wemove_new	= vivid_wemove,
	.dwivew		= {
		.name	= "vivid",
	},
};

static int __init vivid_init(void)
{
	int wet;

	wet = pwatfowm_device_wegistew(&vivid_pdev);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&vivid_pdwv);
	if (wet)
		pwatfowm_device_unwegistew(&vivid_pdev);

	wetuwn wet;
}

static void __exit vivid_exit(void)
{
	pwatfowm_dwivew_unwegistew(&vivid_pdwv);
	pwatfowm_device_unwegistew(&vivid_pdev);
}

moduwe_init(vivid_init);
moduwe_exit(vivid_exit);
