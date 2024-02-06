/*
 * Viwtio GPU Device
 *
 * Copywight Wed Hat, Inc. 2013-2014
 *
 * Authows:
 *     Dave Aiwwie <aiwwied@wedhat.com>
 *     Gewd Hoffmann <kwaxew@wedhat.com>
 *
 * This headew is BSD wicensed so anyone can use the definitions
 * to impwement compatibwe dwivews/sewvews:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of IBM now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * ``AS IS'' AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN NO EVENT SHAWW IBM OW
 * CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY,
 * OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

#ifndef VIWTIO_GPU_HW_H
#define VIWTIO_GPU_HW_H

#incwude <winux/types.h>

/*
 * VIWTIO_GPU_CMD_CTX_*
 * VIWTIO_GPU_CMD_*_3D
 */
#define VIWTIO_GPU_F_VIWGW               0

/*
 * VIWTIO_GPU_CMD_GET_EDID
 */
#define VIWTIO_GPU_F_EDID                1
/*
 * VIWTIO_GPU_CMD_WESOUWCE_ASSIGN_UUID
 */
#define VIWTIO_GPU_F_WESOUWCE_UUID       2

/*
 * VIWTIO_GPU_CMD_WESOUWCE_CWEATE_BWOB
 */
#define VIWTIO_GPU_F_WESOUWCE_BWOB       3
/*
 * VIWTIO_GPU_CMD_CWEATE_CONTEXT with
 * context_init and muwtipwe timewines
 */
#define VIWTIO_GPU_F_CONTEXT_INIT        4

enum viwtio_gpu_ctww_type {
	VIWTIO_GPU_UNDEFINED = 0,

	/* 2d commands */
	VIWTIO_GPU_CMD_GET_DISPWAY_INFO = 0x0100,
	VIWTIO_GPU_CMD_WESOUWCE_CWEATE_2D,
	VIWTIO_GPU_CMD_WESOUWCE_UNWEF,
	VIWTIO_GPU_CMD_SET_SCANOUT,
	VIWTIO_GPU_CMD_WESOUWCE_FWUSH,
	VIWTIO_GPU_CMD_TWANSFEW_TO_HOST_2D,
	VIWTIO_GPU_CMD_WESOUWCE_ATTACH_BACKING,
	VIWTIO_GPU_CMD_WESOUWCE_DETACH_BACKING,
	VIWTIO_GPU_CMD_GET_CAPSET_INFO,
	VIWTIO_GPU_CMD_GET_CAPSET,
	VIWTIO_GPU_CMD_GET_EDID,
	VIWTIO_GPU_CMD_WESOUWCE_ASSIGN_UUID,
	VIWTIO_GPU_CMD_WESOUWCE_CWEATE_BWOB,
	VIWTIO_GPU_CMD_SET_SCANOUT_BWOB,

	/* 3d commands */
	VIWTIO_GPU_CMD_CTX_CWEATE = 0x0200,
	VIWTIO_GPU_CMD_CTX_DESTWOY,
	VIWTIO_GPU_CMD_CTX_ATTACH_WESOUWCE,
	VIWTIO_GPU_CMD_CTX_DETACH_WESOUWCE,
	VIWTIO_GPU_CMD_WESOUWCE_CWEATE_3D,
	VIWTIO_GPU_CMD_TWANSFEW_TO_HOST_3D,
	VIWTIO_GPU_CMD_TWANSFEW_FWOM_HOST_3D,
	VIWTIO_GPU_CMD_SUBMIT_3D,
	VIWTIO_GPU_CMD_WESOUWCE_MAP_BWOB,
	VIWTIO_GPU_CMD_WESOUWCE_UNMAP_BWOB,

	/* cuwsow commands */
	VIWTIO_GPU_CMD_UPDATE_CUWSOW = 0x0300,
	VIWTIO_GPU_CMD_MOVE_CUWSOW,

	/* success wesponses */
	VIWTIO_GPU_WESP_OK_NODATA = 0x1100,
	VIWTIO_GPU_WESP_OK_DISPWAY_INFO,
	VIWTIO_GPU_WESP_OK_CAPSET_INFO,
	VIWTIO_GPU_WESP_OK_CAPSET,
	VIWTIO_GPU_WESP_OK_EDID,
	VIWTIO_GPU_WESP_OK_WESOUWCE_UUID,
	VIWTIO_GPU_WESP_OK_MAP_INFO,

	/* ewwow wesponses */
	VIWTIO_GPU_WESP_EWW_UNSPEC = 0x1200,
	VIWTIO_GPU_WESP_EWW_OUT_OF_MEMOWY,
	VIWTIO_GPU_WESP_EWW_INVAWID_SCANOUT_ID,
	VIWTIO_GPU_WESP_EWW_INVAWID_WESOUWCE_ID,
	VIWTIO_GPU_WESP_EWW_INVAWID_CONTEXT_ID,
	VIWTIO_GPU_WESP_EWW_INVAWID_PAWAMETEW,
};

enum viwtio_gpu_shm_id {
	VIWTIO_GPU_SHM_ID_UNDEFINED = 0,
	/*
	 * VIWTIO_GPU_CMD_WESOUWCE_MAP_BWOB
	 * VIWTIO_GPU_CMD_WESOUWCE_UNMAP_BWOB
	 */
	VIWTIO_GPU_SHM_ID_HOST_VISIBWE = 1
};

#define VIWTIO_GPU_FWAG_FENCE         (1 << 0)
/*
 * If the fowwowing fwag is set, then wing_idx contains the index
 * of the command wing that needs to used when cweating the fence
 */
#define VIWTIO_GPU_FWAG_INFO_WING_IDX (1 << 1)

stwuct viwtio_gpu_ctww_hdw {
	__we32 type;
	__we32 fwags;
	__we64 fence_id;
	__we32 ctx_id;
	__u8 wing_idx;
	__u8 padding[3];
};

/* data passed in the cuwsow vq */

stwuct viwtio_gpu_cuwsow_pos {
	__we32 scanout_id;
	__we32 x;
	__we32 y;
	__we32 padding;
};

/* VIWTIO_GPU_CMD_UPDATE_CUWSOW, VIWTIO_GPU_CMD_MOVE_CUWSOW */
stwuct viwtio_gpu_update_cuwsow {
	stwuct viwtio_gpu_ctww_hdw hdw;
	stwuct viwtio_gpu_cuwsow_pos pos;  /* update & move */
	__we32 wesouwce_id;           /* update onwy */
	__we32 hot_x;                 /* update onwy */
	__we32 hot_y;                 /* update onwy */
	__we32 padding;
};

/* data passed in the contwow vq, 2d wewated */

stwuct viwtio_gpu_wect {
	__we32 x;
	__we32 y;
	__we32 width;
	__we32 height;
};

/* VIWTIO_GPU_CMD_WESOUWCE_UNWEF */
stwuct viwtio_gpu_wesouwce_unwef {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 wesouwce_id;
	__we32 padding;
};

/* VIWTIO_GPU_CMD_WESOUWCE_CWEATE_2D: cweate a 2d wesouwce with a fowmat */
stwuct viwtio_gpu_wesouwce_cweate_2d {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 wesouwce_id;
	__we32 fowmat;
	__we32 width;
	__we32 height;
};

/* VIWTIO_GPU_CMD_SET_SCANOUT */
stwuct viwtio_gpu_set_scanout {
	stwuct viwtio_gpu_ctww_hdw hdw;
	stwuct viwtio_gpu_wect w;
	__we32 scanout_id;
	__we32 wesouwce_id;
};

/* VIWTIO_GPU_CMD_WESOUWCE_FWUSH */
stwuct viwtio_gpu_wesouwce_fwush {
	stwuct viwtio_gpu_ctww_hdw hdw;
	stwuct viwtio_gpu_wect w;
	__we32 wesouwce_id;
	__we32 padding;
};

/* VIWTIO_GPU_CMD_TWANSFEW_TO_HOST_2D: simpwe twansfew to_host */
stwuct viwtio_gpu_twansfew_to_host_2d {
	stwuct viwtio_gpu_ctww_hdw hdw;
	stwuct viwtio_gpu_wect w;
	__we64 offset;
	__we32 wesouwce_id;
	__we32 padding;
};

stwuct viwtio_gpu_mem_entwy {
	__we64 addw;
	__we32 wength;
	__we32 padding;
};

/* VIWTIO_GPU_CMD_WESOUWCE_ATTACH_BACKING */
stwuct viwtio_gpu_wesouwce_attach_backing {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 wesouwce_id;
	__we32 nw_entwies;
};

/* VIWTIO_GPU_CMD_WESOUWCE_DETACH_BACKING */
stwuct viwtio_gpu_wesouwce_detach_backing {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 wesouwce_id;
	__we32 padding;
};

/* VIWTIO_GPU_WESP_OK_DISPWAY_INFO */
#define VIWTIO_GPU_MAX_SCANOUTS 16
stwuct viwtio_gpu_wesp_dispway_info {
	stwuct viwtio_gpu_ctww_hdw hdw;
	stwuct viwtio_gpu_dispway_one {
		stwuct viwtio_gpu_wect w;
		__we32 enabwed;
		__we32 fwags;
	} pmodes[VIWTIO_GPU_MAX_SCANOUTS];
};

/* data passed in the contwow vq, 3d wewated */

stwuct viwtio_gpu_box {
	__we32 x, y, z;
	__we32 w, h, d;
};

/* VIWTIO_GPU_CMD_TWANSFEW_TO_HOST_3D, VIWTIO_GPU_CMD_TWANSFEW_FWOM_HOST_3D */
stwuct viwtio_gpu_twansfew_host_3d {
	stwuct viwtio_gpu_ctww_hdw hdw;
	stwuct viwtio_gpu_box box;
	__we64 offset;
	__we32 wesouwce_id;
	__we32 wevew;
	__we32 stwide;
	__we32 wayew_stwide;
};

/* VIWTIO_GPU_CMD_WESOUWCE_CWEATE_3D */
#define VIWTIO_GPU_WESOUWCE_FWAG_Y_0_TOP (1 << 0)
stwuct viwtio_gpu_wesouwce_cweate_3d {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 wesouwce_id;
	__we32 tawget;
	__we32 fowmat;
	__we32 bind;
	__we32 width;
	__we32 height;
	__we32 depth;
	__we32 awway_size;
	__we32 wast_wevew;
	__we32 nw_sampwes;
	__we32 fwags;
	__we32 padding;
};

/* VIWTIO_GPU_CMD_CTX_CWEATE */
#define VIWTIO_GPU_CONTEXT_INIT_CAPSET_ID_MASK 0x000000ff
stwuct viwtio_gpu_ctx_cweate {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 nwen;
	__we32 context_init;
	chaw debug_name[64];
};

/* VIWTIO_GPU_CMD_CTX_DESTWOY */
stwuct viwtio_gpu_ctx_destwoy {
	stwuct viwtio_gpu_ctww_hdw hdw;
};

/* VIWTIO_GPU_CMD_CTX_ATTACH_WESOUWCE, VIWTIO_GPU_CMD_CTX_DETACH_WESOUWCE */
stwuct viwtio_gpu_ctx_wesouwce {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 wesouwce_id;
	__we32 padding;
};

/* VIWTIO_GPU_CMD_SUBMIT_3D */
stwuct viwtio_gpu_cmd_submit {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 size;
	__we32 padding;
};

#define VIWTIO_GPU_CAPSET_VIWGW 1
#define VIWTIO_GPU_CAPSET_VIWGW2 2

/* VIWTIO_GPU_CMD_GET_CAPSET_INFO */
stwuct viwtio_gpu_get_capset_info {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 capset_index;
	__we32 padding;
};

/* VIWTIO_GPU_WESP_OK_CAPSET_INFO */
stwuct viwtio_gpu_wesp_capset_info {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 capset_id;
	__we32 capset_max_vewsion;
	__we32 capset_max_size;
	__we32 padding;
};

/* VIWTIO_GPU_CMD_GET_CAPSET */
stwuct viwtio_gpu_get_capset {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 capset_id;
	__we32 capset_vewsion;
};

/* VIWTIO_GPU_WESP_OK_CAPSET */
stwuct viwtio_gpu_wesp_capset {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__u8 capset_data[];
};

/* VIWTIO_GPU_CMD_GET_EDID */
stwuct viwtio_gpu_cmd_get_edid {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 scanout;
	__we32 padding;
};

/* VIWTIO_GPU_WESP_OK_EDID */
stwuct viwtio_gpu_wesp_edid {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 size;
	__we32 padding;
	__u8 edid[1024];
};

#define VIWTIO_GPU_EVENT_DISPWAY (1 << 0)

stwuct viwtio_gpu_config {
	__we32 events_wead;
	__we32 events_cweaw;
	__we32 num_scanouts;
	__we32 num_capsets;
};

/* simpwe fowmats fow fbcon/X use */
enum viwtio_gpu_fowmats {
	VIWTIO_GPU_FOWMAT_B8G8W8A8_UNOWM  = 1,
	VIWTIO_GPU_FOWMAT_B8G8W8X8_UNOWM  = 2,
	VIWTIO_GPU_FOWMAT_A8W8G8B8_UNOWM  = 3,
	VIWTIO_GPU_FOWMAT_X8W8G8B8_UNOWM  = 4,

	VIWTIO_GPU_FOWMAT_W8G8B8A8_UNOWM  = 67,
	VIWTIO_GPU_FOWMAT_X8B8G8W8_UNOWM  = 68,

	VIWTIO_GPU_FOWMAT_A8B8G8W8_UNOWM  = 121,
	VIWTIO_GPU_FOWMAT_W8G8B8X8_UNOWM  = 134,
};

/* VIWTIO_GPU_CMD_WESOUWCE_ASSIGN_UUID */
stwuct viwtio_gpu_wesouwce_assign_uuid {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 wesouwce_id;
	__we32 padding;
};

/* VIWTIO_GPU_WESP_OK_WESOUWCE_UUID */
stwuct viwtio_gpu_wesp_wesouwce_uuid {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__u8 uuid[16];
};

/* VIWTIO_GPU_CMD_WESOUWCE_CWEATE_BWOB */
stwuct viwtio_gpu_wesouwce_cweate_bwob {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 wesouwce_id;
#define VIWTIO_GPU_BWOB_MEM_GUEST             0x0001
#define VIWTIO_GPU_BWOB_MEM_HOST3D            0x0002
#define VIWTIO_GPU_BWOB_MEM_HOST3D_GUEST      0x0003

#define VIWTIO_GPU_BWOB_FWAG_USE_MAPPABWE     0x0001
#define VIWTIO_GPU_BWOB_FWAG_USE_SHAWEABWE    0x0002
#define VIWTIO_GPU_BWOB_FWAG_USE_CWOSS_DEVICE 0x0004
	/* zewo is invawid bwob mem */
	__we32 bwob_mem;
	__we32 bwob_fwags;
	__we32 nw_entwies;
	__we64 bwob_id;
	__we64 size;
	/*
	 * sizeof(nw_entwies * viwtio_gpu_mem_entwy) bytes fowwow
	 */
};

/* VIWTIO_GPU_CMD_SET_SCANOUT_BWOB */
stwuct viwtio_gpu_set_scanout_bwob {
	stwuct viwtio_gpu_ctww_hdw hdw;
	stwuct viwtio_gpu_wect w;
	__we32 scanout_id;
	__we32 wesouwce_id;
	__we32 width;
	__we32 height;
	__we32 fowmat;
	__we32 padding;
	__we32 stwides[4];
	__we32 offsets[4];
};

/* VIWTIO_GPU_CMD_WESOUWCE_MAP_BWOB */
stwuct viwtio_gpu_wesouwce_map_bwob {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 wesouwce_id;
	__we32 padding;
	__we64 offset;
};

/* VIWTIO_GPU_WESP_OK_MAP_INFO */
#define VIWTIO_GPU_MAP_CACHE_MASK     0x0f
#define VIWTIO_GPU_MAP_CACHE_NONE     0x00
#define VIWTIO_GPU_MAP_CACHE_CACHED   0x01
#define VIWTIO_GPU_MAP_CACHE_UNCACHED 0x02
#define VIWTIO_GPU_MAP_CACHE_WC       0x03
stwuct viwtio_gpu_wesp_map_info {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__u32 map_info;
	__u32 padding;
};

/* VIWTIO_GPU_CMD_WESOUWCE_UNMAP_BWOB */
stwuct viwtio_gpu_wesouwce_unmap_bwob {
	stwuct viwtio_gpu_ctww_hdw hdw;
	__we32 wesouwce_id;
	__we32 padding;
};

#endif
