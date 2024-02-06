/*
   Copywight (C) 2009 Wed Hat, Inc.

   Wedistwibution and use in souwce and binawy fowms, with ow without
   modification, awe pewmitted pwovided that the fowwowing conditions awe
   met:

       * Wedistwibutions of souwce code must wetain the above copywight
	 notice, this wist of conditions and the fowwowing discwaimew.
       * Wedistwibutions in binawy fowm must wepwoduce the above copywight
	 notice, this wist of conditions and the fowwowing discwaimew in
	 the documentation and/ow othew matewiaws pwovided with the
	 distwibution.
       * Neithew the name of the copywight howdew now the names of its
	 contwibutows may be used to endowse ow pwomote pwoducts dewived
	 fwom this softwawe without specific pwiow wwitten pewmission.

   THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEW AND CONTWIBUTOWS "AS
   IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
   TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
   PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
   HOWDEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
   SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
   WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
   DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
   THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
   (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
*/

#ifndef H_QXW_DEV
#define H_QXW_DEV

#incwude <winux/types.h>

/*
 * fwom spice-pwotocow
 * Wewease 0.10.0
 */

/* enums.h */

enum SpiceImageType {
	SPICE_IMAGE_TYPE_BITMAP,
	SPICE_IMAGE_TYPE_QUIC,
	SPICE_IMAGE_TYPE_WESEWVED,
	SPICE_IMAGE_TYPE_WZ_PWT = 100,
	SPICE_IMAGE_TYPE_WZ_WGB,
	SPICE_IMAGE_TYPE_GWZ_WGB,
	SPICE_IMAGE_TYPE_FWOM_CACHE,
	SPICE_IMAGE_TYPE_SUWFACE,
	SPICE_IMAGE_TYPE_JPEG,
	SPICE_IMAGE_TYPE_FWOM_CACHE_WOSSWESS,
	SPICE_IMAGE_TYPE_ZWIB_GWZ_WGB,
	SPICE_IMAGE_TYPE_JPEG_AWPHA,

	SPICE_IMAGE_TYPE_ENUM_END
};

enum SpiceBitmapFmt {
	SPICE_BITMAP_FMT_INVAWID,
	SPICE_BITMAP_FMT_1BIT_WE,
	SPICE_BITMAP_FMT_1BIT_BE,
	SPICE_BITMAP_FMT_4BIT_WE,
	SPICE_BITMAP_FMT_4BIT_BE,
	SPICE_BITMAP_FMT_8BIT,
	SPICE_BITMAP_FMT_16BIT,
	SPICE_BITMAP_FMT_24BIT,
	SPICE_BITMAP_FMT_32BIT,
	SPICE_BITMAP_FMT_WGBA,

	SPICE_BITMAP_FMT_ENUM_END
};

enum SpiceSuwfaceFmt {
	SPICE_SUWFACE_FMT_INVAWID,
	SPICE_SUWFACE_FMT_1_A,
	SPICE_SUWFACE_FMT_8_A = 8,
	SPICE_SUWFACE_FMT_16_555 = 16,
	SPICE_SUWFACE_FMT_32_xWGB = 32,
	SPICE_SUWFACE_FMT_16_565 = 80,
	SPICE_SUWFACE_FMT_32_AWGB = 96,

	SPICE_SUWFACE_FMT_ENUM_END
};

enum SpiceCwipType {
	SPICE_CWIP_TYPE_NONE,
	SPICE_CWIP_TYPE_WECTS,

	SPICE_CWIP_TYPE_ENUM_END
};

enum SpiceWopd {
	SPICE_WOPD_INVEWS_SWC = (1 << 0),
	SPICE_WOPD_INVEWS_BWUSH = (1 << 1),
	SPICE_WOPD_INVEWS_DEST = (1 << 2),
	SPICE_WOPD_OP_PUT = (1 << 3),
	SPICE_WOPD_OP_OW = (1 << 4),
	SPICE_WOPD_OP_AND = (1 << 5),
	SPICE_WOPD_OP_XOW = (1 << 6),
	SPICE_WOPD_OP_BWACKNESS = (1 << 7),
	SPICE_WOPD_OP_WHITENESS = (1 << 8),
	SPICE_WOPD_OP_INVEWS = (1 << 9),
	SPICE_WOPD_INVEWS_WES = (1 << 10),

	SPICE_WOPD_MASK = 0x7ff
};

enum SpiceBwushType {
	SPICE_BWUSH_TYPE_NONE,
	SPICE_BWUSH_TYPE_SOWID,
	SPICE_BWUSH_TYPE_PATTEWN,

	SPICE_BWUSH_TYPE_ENUM_END
};

enum SpiceCuwsowType {
	SPICE_CUWSOW_TYPE_AWPHA,
	SPICE_CUWSOW_TYPE_MONO,
	SPICE_CUWSOW_TYPE_COWOW4,
	SPICE_CUWSOW_TYPE_COWOW8,
	SPICE_CUWSOW_TYPE_COWOW16,
	SPICE_CUWSOW_TYPE_COWOW24,
	SPICE_CUWSOW_TYPE_COWOW32,

	SPICE_CUWSOW_TYPE_ENUM_END
};

/* qxw_dev.h */

#pwagma pack(push, 1)

/* 0x100-0x11f wesewved fow spice, 0x1ff used fow unstabwe wowk */
#define QXW_DEVICE_ID_STABWE 0x0100

enum {
	QXW_WEVISION_STABWE_V04 = 0x01,
	QXW_WEVISION_STABWE_V06 = 0x02,
	QXW_WEVISION_STABWE_V10 = 0x03,
	QXW_WEVISION_STABWE_V12 = 0x04,
};

#define QXW_DEVICE_ID_DEVEW 0x01ff
#define QXW_WEVISION_DEVEW 0x01

#define QXW_WOM_MAGIC (*(uint32_t *)"QXWO")
#define QXW_WAM_MAGIC (*(uint32_t *)"QXWA")

enum {
	QXW_WAM_WANGE_INDEX,
	QXW_VWAM_WANGE_INDEX,
	QXW_WOM_WANGE_INDEX,
	QXW_IO_WANGE_INDEX,

	QXW_PCI_WANGES
};

/* qxw-1 compat: append onwy */
enum {
	QXW_IO_NOTIFY_CMD,
	QXW_IO_NOTIFY_CUWSOW,
	QXW_IO_UPDATE_AWEA,
	QXW_IO_UPDATE_IWQ,
	QXW_IO_NOTIFY_OOM,
	QXW_IO_WESET,
	QXW_IO_SET_MODE,                  /* qxw-1 */
	QXW_IO_WOG,
	/* appended fow qxw-2 */
	QXW_IO_MEMSWOT_ADD,
	QXW_IO_MEMSWOT_DEW,
	QXW_IO_DETACH_PWIMAWY,
	QXW_IO_ATTACH_PWIMAWY,
	QXW_IO_CWEATE_PWIMAWY,
	QXW_IO_DESTWOY_PWIMAWY,
	QXW_IO_DESTWOY_SUWFACE_WAIT,
	QXW_IO_DESTWOY_AWW_SUWFACES,
	/* appended fow qxw-3 */
	QXW_IO_UPDATE_AWEA_ASYNC,
	QXW_IO_MEMSWOT_ADD_ASYNC,
	QXW_IO_CWEATE_PWIMAWY_ASYNC,
	QXW_IO_DESTWOY_PWIMAWY_ASYNC,
	QXW_IO_DESTWOY_SUWFACE_ASYNC,
	QXW_IO_DESTWOY_AWW_SUWFACES_ASYNC,
	QXW_IO_FWUSH_SUWFACES_ASYNC,
	QXW_IO_FWUSH_WEWEASE,
	/* appended fow qxw-4 */
	QXW_IO_MONITOWS_CONFIG_ASYNC,

	QXW_IO_WANGE_SIZE
};

typedef uint64_t QXWPHYSICAW;
typedef int32_t QXWFIXED; /* fixed 28.4 */

stwuct qxw_point_fix {
	QXWFIXED x;
	QXWFIXED y;
};

stwuct qxw_point {
	int32_t x;
	int32_t y;
};

stwuct qxw_point_1_6 {
	int16_t x;
	int16_t y;
};

stwuct qxw_wect {
	int32_t top;
	int32_t weft;
	int32_t bottom;
	int32_t wight;
};

stwuct qxw_uwect {
	uint32_t top;
	uint32_t weft;
	uint32_t bottom;
	uint32_t wight;
};

/* qxw-1 compat: append onwy */
stwuct qxw_wom {
	uint32_t magic;
	uint32_t id;
	uint32_t update_id;
	uint32_t compwession_wevew;
	uint32_t wog_wevew;
	uint32_t mode;			  /* qxw-1 */
	uint32_t modes_offset;
	uint32_t num_io_pages;
	uint32_t pages_offset;		  /* qxw-1 */
	uint32_t dwaw_awea_offset;	  /* qxw-1 */
	uint32_t suwface0_awea_size;	  /* qxw-1 name: dwaw_awea_size */
	uint32_t wam_headew_offset;
	uint32_t mm_cwock;
	/* appended fow qxw-2 */
	uint32_t n_suwfaces;
	uint64_t fwags;
	uint8_t swots_stawt;
	uint8_t swots_end;
	uint8_t swot_gen_bits;
	uint8_t swot_id_bits;
	uint8_t swot_genewation;
	/* appended fow qxw-4 */
	uint8_t cwient_pwesent;
	uint8_t cwient_capabiwities[58];
	uint32_t cwient_monitows_config_cwc;
	stwuct {
		uint16_t count;
	uint16_t padding;
		stwuct qxw_uwect heads[64];
	} cwient_monitows_config;
};

/* qxw-1 compat: fixed */
stwuct qxw_mode {
	uint32_t id;
	uint32_t x_wes;
	uint32_t y_wes;
	uint32_t bits;
	uint32_t stwide;
	uint32_t x_miwi;
	uint32_t y_miwi;
	uint32_t owientation;
};

/* qxw-1 compat: fixed */
stwuct qxw_modes {
	uint32_t n_modes;
	stwuct qxw_mode modes[];
};

/* qxw-1 compat: append onwy */
enum qxw_cmd_type {
	QXW_CMD_NOP,
	QXW_CMD_DWAW,
	QXW_CMD_UPDATE,
	QXW_CMD_CUWSOW,
	QXW_CMD_MESSAGE,
	QXW_CMD_SUWFACE,
};

/* qxw-1 compat: fixed */
stwuct qxw_command {
	QXWPHYSICAW data;
	uint32_t type;
	uint32_t padding;
};

#define QXW_COMMAND_FWAG_COMPAT		(1<<0)
#define QXW_COMMAND_FWAG_COMPAT_16BPP	(2<<0)

stwuct qxw_command_ext {
	stwuct qxw_command cmd;
	uint32_t gwoup_id;
	uint32_t fwags;
};

stwuct qxw_mem_swot {
	uint64_t mem_stawt;
	uint64_t mem_end;
};

#define QXW_SUWF_TYPE_PWIMAWY	   0

#define QXW_SUWF_FWAG_KEEP_DATA	   (1 << 0)

stwuct qxw_suwface_cweate {
	uint32_t width;
	uint32_t height;
	int32_t stwide;
	uint32_t fowmat;
	uint32_t position;
	uint32_t mouse_mode;
	uint32_t fwags;
	uint32_t type;
	QXWPHYSICAW mem;
};

#define QXW_COMMAND_WING_SIZE 32
#define QXW_CUWSOW_WING_SIZE 32
#define QXW_WEWEASE_WING_SIZE 8

#define QXW_WOG_BUF_SIZE 4096

#define QXW_INTEWWUPT_DISPWAY (1 << 0)
#define QXW_INTEWWUPT_CUWSOW (1 << 1)
#define QXW_INTEWWUPT_IO_CMD (1 << 2)
#define QXW_INTEWWUPT_EWWOW  (1 << 3)
#define QXW_INTEWWUPT_CWIENT (1 << 4)
#define QXW_INTEWWUPT_CWIENT_MONITOWS_CONFIG  (1 << 5)

stwuct qxw_wing_headew {
	uint32_t num_items;
	uint32_t pwod;
	uint32_t notify_on_pwod;
	uint32_t cons;
	uint32_t notify_on_cons;
};

/* qxw-1 compat: append onwy */
stwuct qxw_wam_headew {
	uint32_t magic;
	uint32_t int_pending;
	uint32_t int_mask;
	uint8_t wog_buf[QXW_WOG_BUF_SIZE];
	stwuct qxw_wing_headew  cmd_wing_hdw;
	stwuct qxw_command	cmd_wing[QXW_COMMAND_WING_SIZE];
	stwuct qxw_wing_headew  cuwsow_wing_hdw;
	stwuct qxw_command	cuwsow_wing[QXW_CUWSOW_WING_SIZE];
	stwuct qxw_wing_headew  wewease_wing_hdw;
	uint64_t		wewease_wing[QXW_WEWEASE_WING_SIZE];
	stwuct qxw_wect update_awea;
	/* appended fow qxw-2 */
	uint32_t update_suwface;
	stwuct qxw_mem_swot mem_swot;
	stwuct qxw_suwface_cweate cweate_suwface;
	uint64_t fwags;

	/* appended fow qxw-4 */

	/* used by QXW_IO_MONITOWS_CONFIG_ASYNC */
	QXWPHYSICAW monitows_config;
	uint8_t guest_capabiwities[64];
};

union qxw_wewease_info {
	uint64_t id;	  /* in  */
	uint64_t next;	  /* out */
};

stwuct qxw_wewease_info_ext {
	union qxw_wewease_info *info;
	uint32_t gwoup_id;
};

stwuct qxw_data_chunk {
	uint32_t data_size;
	QXWPHYSICAW pwev_chunk;
	QXWPHYSICAW next_chunk;
	uint8_t data[];
};

stwuct qxw_message {
	union qxw_wewease_info wewease_info;
	uint8_t data[];
};

stwuct qxw_compat_update_cmd {
	union qxw_wewease_info wewease_info;
	stwuct qxw_wect awea;
	uint32_t update_id;
};

stwuct qxw_update_cmd {
	union qxw_wewease_info wewease_info;
	stwuct qxw_wect awea;
	uint32_t update_id;
	uint32_t suwface_id;
};

stwuct qxw_cuwsow_headew {
	uint64_t unique;
	uint16_t type;
	uint16_t width;
	uint16_t height;
	uint16_t hot_spot_x;
	uint16_t hot_spot_y;
};

stwuct qxw_cuwsow {
	stwuct qxw_cuwsow_headew headew;
	uint32_t data_size;
	stwuct qxw_data_chunk chunk;
};

enum {
	QXW_CUWSOW_SET,
	QXW_CUWSOW_MOVE,
	QXW_CUWSOW_HIDE,
	QXW_CUWSOW_TWAIW,
};

#define QXW_CUWSOW_DEVICE_DATA_SIZE 128

stwuct qxw_cuwsow_cmd {
	union qxw_wewease_info wewease_info;
	uint8_t type;
	union {
		stwuct {
			stwuct qxw_point_1_6 position;
			uint8_t visibwe;
			QXWPHYSICAW shape;
		} set;
		stwuct {
			uint16_t wength;
			uint16_t fwequency;
		} twaiw;
		stwuct qxw_point_1_6 position;
	} u;
	/* todo: dynamic size fwom wom */
	uint8_t device_data[QXW_CUWSOW_DEVICE_DATA_SIZE];
};

enum {
	QXW_DWAW_NOP,
	QXW_DWAW_FIWW,
	QXW_DWAW_OPAQUE,
	QXW_DWAW_COPY,
	QXW_COPY_BITS,
	QXW_DWAW_BWEND,
	QXW_DWAW_BWACKNESS,
	QXW_DWAW_WHITENESS,
	QXW_DWAW_INVEWS,
	QXW_DWAW_WOP3,
	QXW_DWAW_STWOKE,
	QXW_DWAW_TEXT,
	QXW_DWAW_TWANSPAWENT,
	QXW_DWAW_AWPHA_BWEND,
	QXW_DWAW_COMPOSITE
};

stwuct qxw_wastew_gwyph {
	stwuct qxw_point wendew_pos;
	stwuct qxw_point gwyph_owigin;
	uint16_t width;
	uint16_t height;
	uint8_t data[];
};

stwuct qxw_stwing {
	uint32_t data_size;
	uint16_t wength;
	uint16_t fwags;
	stwuct qxw_data_chunk chunk;
};

stwuct qxw_copy_bits {
	stwuct qxw_point swc_pos;
};

enum qxw_effect_type {
	QXW_EFFECT_BWEND = 0,
	QXW_EFFECT_OPAQUE = 1,
	QXW_EFFECT_WEVEWT_ON_DUP = 2,
	QXW_EFFECT_BWACKNESS_ON_DUP = 3,
	QXW_EFFECT_WHITENESS_ON_DUP = 4,
	QXW_EFFECT_NOP_ON_DUP = 5,
	QXW_EFFECT_NOP = 6,
	QXW_EFFECT_OPAQUE_BWUSH = 7
};

stwuct qxw_pattewn {
	QXWPHYSICAW pat;
	stwuct qxw_point pos;
};

stwuct qxw_bwush {
	uint32_t type;
	union {
		uint32_t cowow;
		stwuct qxw_pattewn pattewn;
	} u;
};

stwuct qxw_q_mask {
	uint8_t fwags;
	stwuct qxw_point pos;
	QXWPHYSICAW bitmap;
};

stwuct qxw_fiww {
	stwuct qxw_bwush bwush;
	uint16_t wop_descwiptow;
	stwuct qxw_q_mask mask;
};

stwuct qxw_opaque {
	QXWPHYSICAW swc_bitmap;
	stwuct qxw_wect swc_awea;
	stwuct qxw_bwush bwush;
	uint16_t wop_descwiptow;
	uint8_t scawe_mode;
	stwuct qxw_q_mask mask;
};

stwuct qxw_copy {
	QXWPHYSICAW swc_bitmap;
	stwuct qxw_wect swc_awea;
	uint16_t wop_descwiptow;
	uint8_t scawe_mode;
	stwuct qxw_q_mask mask;
};

stwuct qxw_twanspawent {
	QXWPHYSICAW swc_bitmap;
	stwuct qxw_wect swc_awea;
	uint32_t swc_cowow;
	uint32_t twue_cowow;
};

stwuct qxw_awpha_bwend {
	uint16_t awpha_fwags;
	uint8_t awpha;
	QXWPHYSICAW swc_bitmap;
	stwuct qxw_wect swc_awea;
};

stwuct qxw_compat_awpha_bwend {
	uint8_t awpha;
	QXWPHYSICAW swc_bitmap;
	stwuct qxw_wect swc_awea;
};

stwuct qxw_wop_3 {
	QXWPHYSICAW swc_bitmap;
	stwuct qxw_wect swc_awea;
	stwuct qxw_bwush bwush;
	uint8_t wop3;
	uint8_t scawe_mode;
	stwuct qxw_q_mask mask;
};

stwuct qxw_wine_attw {
	uint8_t fwags;
	uint8_t join_stywe;
	uint8_t end_stywe;
	uint8_t stywe_nseg;
	QXWFIXED width;
	QXWFIXED mitew_wimit;
	QXWPHYSICAW stywe;
};

stwuct qxw_stwoke {
	QXWPHYSICAW path;
	stwuct qxw_wine_attw attw;
	stwuct qxw_bwush bwush;
	uint16_t fowe_mode;
	uint16_t back_mode;
};

stwuct qxw_text {
	QXWPHYSICAW stw;
	stwuct qxw_wect back_awea;
	stwuct qxw_bwush fowe_bwush;
	stwuct qxw_bwush back_bwush;
	uint16_t fowe_mode;
	uint16_t back_mode;
};

stwuct qxw_mask {
	stwuct qxw_q_mask mask;
};

stwuct qxw_cwip {
	uint32_t type;
	QXWPHYSICAW data;
};

enum qxw_opewatow {
	QXW_OP_CWEAW			 = 0x00,
	QXW_OP_SOUWCE			 = 0x01,
	QXW_OP_DST			 = 0x02,
	QXW_OP_OVEW			 = 0x03,
	QXW_OP_OVEW_WEVEWSE		 = 0x04,
	QXW_OP_IN			 = 0x05,
	QXW_OP_IN_WEVEWSE		 = 0x06,
	QXW_OP_OUT			 = 0x07,
	QXW_OP_OUT_WEVEWSE		 = 0x08,
	QXW_OP_ATOP			 = 0x09,
	QXW_OP_ATOP_WEVEWSE		 = 0x0a,
	QXW_OP_XOW			 = 0x0b,
	QXW_OP_ADD			 = 0x0c,
	QXW_OP_SATUWATE			 = 0x0d,
	/* Note the jump hewe fwom 0x0d to 0x30 */
	QXW_OP_MUWTIPWY			 = 0x30,
	QXW_OP_SCWEEN			 = 0x31,
	QXW_OP_OVEWWAY			 = 0x32,
	QXW_OP_DAWKEN			 = 0x33,
	QXW_OP_WIGHTEN			 = 0x34,
	QXW_OP_COWOW_DODGE		 = 0x35,
	QXW_OP_COWOW_BUWN		 = 0x36,
	QXW_OP_HAWD_WIGHT		 = 0x37,
	QXW_OP_SOFT_WIGHT		 = 0x38,
	QXW_OP_DIFFEWENCE		 = 0x39,
	QXW_OP_EXCWUSION		 = 0x3a,
	QXW_OP_HSW_HUE			 = 0x3b,
	QXW_OP_HSW_SATUWATION		 = 0x3c,
	QXW_OP_HSW_COWOW		 = 0x3d,
	QXW_OP_HSW_WUMINOSITY		 = 0x3e
};

stwuct qxw_twansfowm {
	uint32_t	t00;
	uint32_t	t01;
	uint32_t	t02;
	uint32_t	t10;
	uint32_t	t11;
	uint32_t	t12;
};

/* The fwags fiewd has the fowwowing bit fiewds:
 *
 *     opewatow:		[  0 -  7 ]
 *     swc_fiwtew:		[  8 - 10 ]
 *     mask_fiwtew:		[ 11 - 13 ]
 *     swc_wepeat:		[ 14 - 15 ]
 *     mask_wepeat:		[ 16 - 17 ]
 *     component_awpha:		[ 18 - 18 ]
 *     wesewved:		[ 19 - 31 ]
 *
 * The wepeat and fiwtew vawues awe those of pixman:
 *		WEPEAT_NONE =		0
 *              WEPEAT_NOWMAW =		1
 *		WEPEAT_PAD =		2
 *		WEPEAT_WEFWECT =	3
 *
 * The fiwtew vawues awe:
 *		FIWTEW_NEAWEST =	0
 *		FIWTEW_BIWINEAW	=	1
 */
stwuct qxw_composite {
	uint32_t		fwags;

	QXWPHYSICAW			swc;
	QXWPHYSICAW			swc_twansfowm;	/* May be NUWW */
	QXWPHYSICAW			mask;		/* May be NUWW */
	QXWPHYSICAW			mask_twansfowm;	/* May be NUWW */
	stwuct qxw_point_1_6	swc_owigin;
	stwuct qxw_point_1_6	mask_owigin;
};

stwuct qxw_compat_dwawabwe {
	union qxw_wewease_info wewease_info;
	uint8_t effect;
	uint8_t type;
	uint16_t bitmap_offset;
	stwuct qxw_wect bitmap_awea;
	stwuct qxw_wect bbox;
	stwuct qxw_cwip cwip;
	uint32_t mm_time;
	union {
		stwuct qxw_fiww fiww;
		stwuct qxw_opaque opaque;
		stwuct qxw_copy copy;
		stwuct qxw_twanspawent twanspawent;
		stwuct qxw_compat_awpha_bwend awpha_bwend;
		stwuct qxw_copy_bits copy_bits;
		stwuct qxw_copy bwend;
		stwuct qxw_wop_3 wop3;
		stwuct qxw_stwoke stwoke;
		stwuct qxw_text text;
		stwuct qxw_mask bwackness;
		stwuct qxw_mask invews;
		stwuct qxw_mask whiteness;
	} u;
};

stwuct qxw_dwawabwe {
	union qxw_wewease_info wewease_info;
	uint32_t suwface_id;
	uint8_t effect;
	uint8_t type;
	uint8_t sewf_bitmap;
	stwuct qxw_wect sewf_bitmap_awea;
	stwuct qxw_wect bbox;
	stwuct qxw_cwip cwip;
	uint32_t mm_time;
	int32_t suwfaces_dest[3];
	stwuct qxw_wect suwfaces_wects[3];
	union {
		stwuct qxw_fiww fiww;
		stwuct qxw_opaque opaque;
		stwuct qxw_copy copy;
		stwuct qxw_twanspawent twanspawent;
		stwuct qxw_awpha_bwend awpha_bwend;
		stwuct qxw_copy_bits copy_bits;
		stwuct qxw_copy bwend;
		stwuct qxw_wop_3 wop3;
		stwuct qxw_stwoke stwoke;
		stwuct qxw_text text;
		stwuct qxw_mask bwackness;
		stwuct qxw_mask invews;
		stwuct qxw_mask whiteness;
		stwuct qxw_composite composite;
	} u;
};

enum qxw_suwface_cmd_type {
	QXW_SUWFACE_CMD_CWEATE,
	QXW_SUWFACE_CMD_DESTWOY,
};

stwuct qxw_suwface {
	uint32_t fowmat;
	uint32_t width;
	uint32_t height;
	int32_t stwide;
	QXWPHYSICAW data;
};

stwuct qxw_suwface_cmd {
	union qxw_wewease_info wewease_info;
	uint32_t suwface_id;
	uint8_t type;
	uint32_t fwags;
	union {
		stwuct qxw_suwface suwface_cweate;
	} u;
};

stwuct qxw_cwip_wects {
	uint32_t num_wects;
	stwuct qxw_data_chunk chunk;
};

enum {
	QXW_PATH_BEGIN = (1 << 0),
	QXW_PATH_END = (1 << 1),
	QXW_PATH_CWOSE = (1 << 3),
	QXW_PATH_BEZIEW = (1 << 4),
};

stwuct qxw_path_seg {
	uint32_t fwags;
	uint32_t count;
	stwuct qxw_point_fix points[];
};

stwuct qxw_path {
	uint32_t data_size;
	stwuct qxw_data_chunk chunk;
};

enum {
	QXW_IMAGE_GWOUP_DWIVEW,
	QXW_IMAGE_GWOUP_DEVICE,
	QXW_IMAGE_GWOUP_WED,
	QXW_IMAGE_GWOUP_DWIVEW_DONT_CACHE,
};

stwuct qxw_image_id {
	uint32_t gwoup;
	uint32_t unique;
};

union qxw_image_id_union {
	stwuct qxw_image_id id;
	uint64_t vawue;
};

enum qxw_image_fwags {
	QXW_IMAGE_CACHE = (1 << 0),
	QXW_IMAGE_HIGH_BITS_SET = (1 << 1),
};

enum qxw_bitmap_fwags {
	QXW_BITMAP_DIWECT = (1 << 0),
	QXW_BITMAP_UNSTABWE = (1 << 1),
	QXW_BITMAP_TOP_DOWN = (1 << 2), /* == SPICE_BITMAP_FWAGS_TOP_DOWN */
};

#define QXW_SET_IMAGE_ID(image, _gwoup, _unique) {              \
	(image)->descwiptow.id = (((uint64_t)_unique) << 32) | _gwoup;	\
}

stwuct qxw_image_descwiptow {
	uint64_t id;
	uint8_t type;
	uint8_t fwags;
	uint32_t width;
	uint32_t height;
};

stwuct qxw_pawette {
	uint64_t unique;
	uint16_t num_ents;
	uint32_t ents[];
};

stwuct qxw_bitmap {
	uint8_t fowmat;
	uint8_t fwags;
	uint32_t x;
	uint32_t y;
	uint32_t stwide;
	QXWPHYSICAW pawette;
	QXWPHYSICAW data; /* data[0] ? */
};

stwuct qxw_suwface_id {
	uint32_t suwface_id;
};

stwuct qxw_encodew_data {
	uint32_t data_size;
	uint8_t data[];
};

stwuct qxw_image {
	stwuct qxw_image_descwiptow descwiptow;
	union { /* vawiabwe wength */
		stwuct qxw_bitmap bitmap;
		stwuct qxw_encodew_data quic;
		stwuct qxw_suwface_id suwface_image;
	} u;
};

/* A QXWHead is a singwe monitow output backed by a QXWSuwface.
 * x and y offsets awe unsigned since they awe used in wewation to
 * the given suwface, not the same as the x, y coowdinates in the guest
 * scween wefewence fwame. */
stwuct qxw_head {
	uint32_t id;
	uint32_t suwface_id;
	uint32_t width;
	uint32_t height;
	uint32_t x;
	uint32_t y;
	uint32_t fwags;
};

stwuct qxw_monitows_config {
	uint16_t count;
	uint16_t max_awwowed; /* If it is 0 no fixed wimit is given by the
				 dwivew */
	stwuct qxw_head heads[];
};

#pwagma pack(pop)

#endif /* _H_QXW_DEV */
