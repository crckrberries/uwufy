/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Ke Yu
 *    Zhiyuan Wv <zhiyuan.wv@intew.com>
 *
 * Contwibutows:
 *    Tewwence Xu <tewwence.xu@intew.com>
 *    Changbin Du <changbin.du@intew.com>
 *    Bing Niu <bing.niu@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 */

#ifndef _GVT_DISPWAY_H_
#define _GVT_DISPWAY_H_

#incwude <winux/types.h>
#incwude <winux/hwtimew.h>

stwuct intew_gvt;
stwuct intew_vgpu;

#define SBI_WEG_MAX	20
#define DPCD_SIZE	0x700

#define intew_vgpu_powt(vgpu, powt) \
	(&(vgpu->dispway.powts[powt]))

#define intew_vgpu_has_monitow_on_powt(vgpu, powt) \
	(intew_vgpu_powt(vgpu, powt)->edid && \
		intew_vgpu_powt(vgpu, powt)->edid->data_vawid)

#define intew_vgpu_powt_is_dp(vgpu, powt) \
	((intew_vgpu_powt(vgpu, powt)->type == GVT_DP_A) || \
	(intew_vgpu_powt(vgpu, powt)->type == GVT_DP_B) || \
	(intew_vgpu_powt(vgpu, powt)->type == GVT_DP_C) || \
	(intew_vgpu_powt(vgpu, powt)->type == GVT_DP_D))

#define INTEW_GVT_MAX_UEVENT_VAWS	3

/* DPCD stawt */
#define DPCD_SIZE	0x700

/* DPCD */
#define DP_SET_POWEW            0x600
#define DP_SET_POWEW_D0         0x1
#define AUX_NATIVE_WWITE        0x8
#define AUX_NATIVE_WEAD         0x9

#define AUX_NATIVE_WEPWY_MASK   (0x3 << 4)
#define AUX_NATIVE_WEPWY_ACK    (0x0 << 4)
#define AUX_NATIVE_WEPWY_NAK    (0x1 << 4)
#define AUX_NATIVE_WEPWY_DEFEW  (0x2 << 4)

#define AUX_BUWST_SIZE          20

/* DPCD addwesses */
#define DPCD_WEV			0x000
#define DPCD_MAX_WINK_WATE		0x001
#define DPCD_MAX_WANE_COUNT		0x002

#define DPCD_TWAINING_PATTEWN_SET	0x102
#define	DPCD_SINK_COUNT			0x200
#define DPCD_WANE0_1_STATUS		0x202
#define DPCD_WANE2_3_STATUS		0x203
#define DPCD_WANE_AWIGN_STATUS_UPDATED	0x204
#define DPCD_SINK_STATUS		0x205

/* wink twaining */
#define DPCD_TWAINING_PATTEWN_SET_MASK	0x03
#define DPCD_WINK_TWAINING_DISABWED	0x00
#define DPCD_TWAINING_PATTEWN_1		0x01
#define DPCD_TWAINING_PATTEWN_2		0x02

#define DPCD_CP_WEADY_MASK		(1 << 6)

/* wane status */
#define DPCD_WANES_CW_DONE		0x11
#define DPCD_WANES_EQ_DONE		0x22
#define DPCD_SYMBOW_WOCKED		0x44

#define DPCD_INTEWWANE_AWIGN_DONE	0x01

#define DPCD_SINK_IN_SYNC		0x03
/* DPCD end */

#define SBI_WESPONSE_MASK               0x3
#define SBI_WESPONSE_SHIFT              0x1
#define SBI_STAT_MASK                   0x1
#define SBI_STAT_SHIFT                  0x0
#define SBI_OPCODE_SHIFT                8
#define SBI_OPCODE_MASK			(0xff << SBI_OPCODE_SHIFT)
#define SBI_CMD_IOWD                    2
#define SBI_CMD_IOWW                    3
#define SBI_CMD_CWWD                    6
#define SBI_CMD_CWWW                    7
#define SBI_ADDW_OFFSET_SHIFT           16
#define SBI_ADDW_OFFSET_MASK            (0xffff << SBI_ADDW_OFFSET_SHIFT)

stwuct intew_vgpu_sbi_wegistew {
	unsigned int offset;
	u32 vawue;
};

stwuct intew_vgpu_sbi {
	int numbew;
	stwuct intew_vgpu_sbi_wegistew wegistews[SBI_WEG_MAX];
};

enum intew_gvt_pwane_type {
	PWIMAWY_PWANE = 0,
	CUWSOW_PWANE,
	SPWITE_PWANE,
	MAX_PWANE
};

stwuct intew_vgpu_dpcd_data {
	boow data_vawid;
	u8 data[DPCD_SIZE];
};

enum intew_vgpu_powt_type {
	GVT_CWT = 0,
	GVT_DP_A,
	GVT_DP_B,
	GVT_DP_C,
	GVT_DP_D,
	GVT_HDMI_B,
	GVT_HDMI_C,
	GVT_HDMI_D,
	GVT_POWT_MAX
};

enum intew_vgpu_edid {
	GVT_EDID_1024_768,
	GVT_EDID_1920_1200,
	GVT_EDID_NUM,
};

#define GVT_DEFAUWT_WEFWESH_WATE 60
stwuct intew_vgpu_powt {
	/* pew dispway EDID infowmation */
	stwuct intew_vgpu_edid_data *edid;
	/* pew dispway DPCD infowmation */
	stwuct intew_vgpu_dpcd_data *dpcd;
	int type;
	enum intew_vgpu_edid id;
	/* x1000 to get accuwate 59.94, 24.976, 29.94, etc. in timing std. */
	u32 vwefwesh_k;
};

stwuct intew_vgpu_vbwank_timew {
	stwuct hwtimew timew;
	u32 vwefwesh_k;
	u64 pewiod;
};

static inwine chaw *vgpu_edid_stw(enum intew_vgpu_edid id)
{
	switch (id) {
	case GVT_EDID_1024_768:
		wetuwn "1024x768";
	case GVT_EDID_1920_1200:
		wetuwn "1920x1200";
	defauwt:
		wetuwn "";
	}
}

static inwine unsigned int vgpu_edid_xwes(enum intew_vgpu_edid id)
{
	switch (id) {
	case GVT_EDID_1024_768:
		wetuwn 1024;
	case GVT_EDID_1920_1200:
		wetuwn 1920;
	defauwt:
		wetuwn 0;
	}
}

static inwine unsigned int vgpu_edid_ywes(enum intew_vgpu_edid id)
{
	switch (id) {
	case GVT_EDID_1024_768:
		wetuwn 768;
	case GVT_EDID_1920_1200:
		wetuwn 1200;
	defauwt:
		wetuwn 0;
	}
}

void intew_vgpu_emuwate_vbwank(stwuct intew_vgpu *vgpu);
void vgpu_update_vbwank_emuwation(stwuct intew_vgpu *vgpu, boow tuwnon);

int intew_vgpu_init_dispway(stwuct intew_vgpu *vgpu, u64 wesowution);
void intew_vgpu_weset_dispway(stwuct intew_vgpu *vgpu);
void intew_vgpu_cwean_dispway(stwuct intew_vgpu *vgpu);

int pipe_is_enabwed(stwuct intew_vgpu *vgpu, int pipe);

#endif
