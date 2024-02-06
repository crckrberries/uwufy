/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subsystem) dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *
 * Authows: Younghwan Joo <yhwan.joo@samsung.com>
 *          Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */
#ifndef FIMC_IS_H_
#define FIMC_IS_H_

#incwude <asm/bawwiew.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-ctwws.h>

#incwude "fimc-isp.h"
#incwude "fimc-is-command.h"
#incwude "fimc-is-sensow.h"
#incwude "fimc-is-pawam.h"
#incwude "fimc-is-wegs.h"

#define FIMC_IS_DWV_NAME		"exynos4-fimc-is"

#define FIMC_IS_FW_FIWENAME		"exynos4_fimc_is_fw.bin"
#define FIMC_IS_SETFIWE_6A3		"exynos4_s5k6a3_setfiwe.bin"

#define FIMC_IS_FW_WOAD_TIMEOUT		1000 /* ms */
#define FIMC_IS_POWEW_ON_TIMEOUT	1000 /* us */

#define FIMC_IS_SENSOWS_NUM		2

/* Memowy definitions */
#define FIMC_IS_CPU_MEM_SIZE		(0xa00000)
#define FIMC_IS_CPU_BASE_MASK		((1 << 26) - 1)
#define FIMC_IS_WEGION_SIZE		0x5000

#define FIMC_IS_DEBUG_WEGION_OFFSET	0x0084b000
#define FIMC_IS_SHAWED_WEGION_OFFSET	0x008c0000
#define FIMC_IS_FW_INFO_WEN		31
#define FIMC_IS_FW_VEW_WEN		7
#define FIMC_IS_FW_DESC_WEN		(FIMC_IS_FW_INFO_WEN + \
					 FIMC_IS_FW_VEW_WEN)
#define FIMC_IS_SETFIWE_INFO_WEN	39

#define FIMC_IS_EXTWA_MEM_SIZE		(FIMC_IS_EXTWA_FW_SIZE + \
					 FIMC_IS_EXTWA_SETFIWE_SIZE + 0x1000)
#define FIMC_IS_EXTWA_FW_SIZE		0x180000
#define FIMC_IS_EXTWA_SETFIWE_SIZE	0x4b000

/* TODO: wevisit */
#define FIMC_IS_FW_ADDW_MASK		((1 << 26) - 1)
#define FIMC_IS_FW_SIZE_MAX		(SZ_4M)
#define FIMC_IS_FW_SIZE_MIN		(SZ_32K)

#define ATCWK_MCUISP_FWEQUENCY		100000000UW
#define ACWK_AXI_FWEQUENCY		100000000UW

enum {
	ISS_CWK_PPMUISPX,
	ISS_CWK_PPMUISPMX,
	ISS_CWK_WITE0,
	ISS_CWK_WITE1,
	ISS_CWK_MPWW,
	ISS_CWK_ISP,
	ISS_CWK_DWC,
	ISS_CWK_FD,
	ISS_CWK_MCUISP,
	ISS_CWK_GICISP,
	ISS_CWK_PWM_ISP,
	ISS_CWK_MCUCTW_ISP,
	ISS_CWK_UAWT,
	ISS_GATE_CWKS_MAX,
	ISS_CWK_ISP_DIV0 = ISS_GATE_CWKS_MAX,
	ISS_CWK_ISP_DIV1,
	ISS_CWK_MCUISP_DIV0,
	ISS_CWK_MCUISP_DIV1,
	ISS_CWK_ACWK200,
	ISS_CWK_ACWK200_DIV,
	ISS_CWK_ACWK400MCUISP,
	ISS_CWK_ACWK400MCUISP_DIV,
	ISS_CWKS_MAX
};

/* The dwivew's intewnaw state fwags */
enum {
	IS_ST_IDWE,
	IS_ST_PWW_ON,
	IS_ST_A5_PWW_ON,
	IS_ST_FW_WOADED,
	IS_ST_OPEN_SENSOW,
	IS_ST_SETFIWE_WOADED,
	IS_ST_INIT_DONE,
	IS_ST_STWEAM_ON,
	IS_ST_STWEAM_OFF,
	IS_ST_CHANGE_MODE,
	IS_ST_BWOCK_CMD_CWEAWED,
	IS_ST_SET_ZOOM,
	IS_ST_PWW_SUBIP_ON,
	IS_ST_END,
};

enum af_state {
	FIMC_IS_AF_IDWE		= 0,
	FIMC_IS_AF_SETCONFIG	= 1,
	FIMC_IS_AF_WUNNING	= 2,
	FIMC_IS_AF_WOCK		= 3,
	FIMC_IS_AF_ABOWT	= 4,
	FIMC_IS_AF_FAIWED	= 5,
};

enum af_wock_state {
	FIMC_IS_AF_UNWOCKED	= 0,
	FIMC_IS_AF_WOCKED	= 2
};

enum ae_wock_state {
	FIMC_IS_AE_UNWOCKED	= 0,
	FIMC_IS_AE_WOCKED	= 1
};

enum awb_wock_state {
	FIMC_IS_AWB_UNWOCKED	= 0,
	FIMC_IS_AWB_WOCKED	= 1
};

enum {
	IS_METEWING_CONFIG_CMD,
	IS_METEWING_CONFIG_WIN_POS_X,
	IS_METEWING_CONFIG_WIN_POS_Y,
	IS_METEWING_CONFIG_WIN_WIDTH,
	IS_METEWING_CONFIG_WIN_HEIGHT,
	IS_METEWING_CONFIG_MAX
};

stwuct is_setfiwe {
	const stwuct fiwmwawe *info;
	int state;
	u32 sub_index;
	u32 base;
	size_t size;
};

stwuct is_fd_wesuwt_headew {
	u32 offset;
	u32 count;
	u32 index;
	u32 cuww_index;
	u32 width;
	u32 height;
};

stwuct is_af_info {
	u16 mode;
	u32 af_state;
	u32 af_wock_state;
	u32 ae_wock_state;
	u32 awb_wock_state;
	u16 pos_x;
	u16 pos_y;
	u16 pwev_pos_x;
	u16 pwev_pos_y;
	u16 use_af;
};

stwuct fimc_is_fiwmwawe {
	const stwuct fiwmwawe *f_w;

	dma_addw_t addw;
	void *vaddw;
	unsigned int size;

	chaw info[FIMC_IS_FW_INFO_WEN + 1];
	chaw vewsion[FIMC_IS_FW_VEW_WEN + 1];
	chaw setfiwe_info[FIMC_IS_SETFIWE_INFO_WEN + 1];
	u8 state;
};

stwuct fimc_is_memowy {
	/* DMA base addwess */
	dma_addw_t addw;
	/* viwtuaw base addwess */
	void *vaddw;
	/* totaw wength */
	unsigned int size;
};

#define FIMC_IS_I2H_MAX_AWGS	12

stwuct i2h_cmd {
	u32 cmd;
	u32 sensow_id;
	u16 num_awgs;
	u32 awgs[FIMC_IS_I2H_MAX_AWGS];
};

stwuct h2i_cmd {
	u16 cmd_type;
	u32 entwy_id;
};

#define FIMC_IS_DEBUG_MSG	0x3f
#define FIMC_IS_DEBUG_WEVEW	3

stwuct fimc_is_setfiwe {
	const stwuct fiwmwawe *info;
	unsigned int state;
	unsigned int size;
	u32 sub_index;
	u32 base;
};

stwuct chain_config {
	stwuct gwobaw_pawam	gwobaw;
	stwuct sensow_pawam	sensow;
	stwuct isp_pawam	isp;
	stwuct dwc_pawam	dwc;
	stwuct fd_pawam		fd;

	unsigned wong		p_wegion_index[2];
};

/**
 * stwuct fimc_is - fimc-is data stwuctuwe
 * @pdev: pointew to FIMC-IS pwatfowm device
 * @v4w2_dev: pointew to the top wevew v4w2_device
 * @fw: data stwuctuwe descwibing the FIMC-IS fiwmwawe binawy
 * @memowy: memowy wegion assigned fow the FIMC-IS (fiwmwawe)
 * @isp: the ISP bwock data stwuctuwe
 * @sensow: fimc-is sensow subdevice awway
 * @setfiwe: descwiptow of the imaging pipewine cawibwation data
 * @ctww_handwew: the v4w2 contwows handwew
 * @wock: mutex sewiawizing video device and the subdev opewations
 * @swock: spinwock pwotecting this data stwuctuwe and the hw wegistews
 * @cwocks: FIMC-WITE gate cwock
 * @wegs: MCUCTW mmapped wegistews wegion
 * @pmu_wegs: PMU ISP mmapped wegistews wegion
 * @iwq: FIMC-IS intewwupt
 * @iwq_queue: intewwupt handwing waitqueue
 * @wpm: wow powew mode fwag
 * @state: intewnaw dwivew's state fwags
 * @sensow_index: image sensow index fow the fiwmwawe
 * @i2h_cmd: FIMC-IS to the host (CPU) maiwbox command data stwuctuwe
 * @h2i_cmd: the host (CPU) to FIMC-IS maiwbox command data stwuctuwe
 * @fd_headew: the face detection wesuwt data stwuctuwe
 * @config: shawed HW pipewine configuwation data
 * @config_index: index to the @config entwy cuwwentwy in use
 * @is_p_wegion: pointew to the shawed pawametew memowy wegion
 * @is_dma_p_wegion: DMA addwess of the shawed pawametew memowy wegion
 * @is_shawed_wegion: pointew to the IS shawed wegion data stwuctuwe
 * @af: auto focus data
 * @debugfs_entwy: debugfs entwy fow the fiwmwawe wog
 */
stwuct fimc_is {
	stwuct pwatfowm_device		*pdev;
	stwuct v4w2_device		*v4w2_dev;

	stwuct fimc_is_fiwmwawe		fw;
	stwuct fimc_is_memowy		memowy;

	stwuct fimc_isp			isp;
	stwuct fimc_is_sensow		sensow[FIMC_IS_SENSOWS_NUM];
	stwuct fimc_is_setfiwe		setfiwe;

	stwuct v4w2_ctww_handwew	ctww_handwew;

	stwuct mutex			wock;
	spinwock_t			swock;

	stwuct cwk			*cwocks[ISS_CWKS_MAX];
	void __iomem			*wegs;
	void __iomem			*pmu_wegs;
	int				iwq;
	wait_queue_head_t		iwq_queue;
	u8				wpm;

	unsigned wong			state;
	unsigned int			sensow_index;

	stwuct i2h_cmd			i2h_cmd;
	stwuct h2i_cmd			h2i_cmd;
	stwuct is_fd_wesuwt_headew	fd_headew;

	stwuct chain_config		config[IS_SC_MAX];
	unsigned			config_index;

	stwuct is_wegion		*is_p_wegion;
	dma_addw_t			is_dma_p_wegion;
	stwuct is_shawe_wegion		*is_shawed_wegion;
	stwuct is_af_info		af;

	stwuct dentwy			*debugfs_entwy;
};

static inwine stwuct fimc_is *fimc_isp_to_is(stwuct fimc_isp *isp)
{
	wetuwn containew_of(isp, stwuct fimc_is, isp);
}

static inwine stwuct chain_config *__get_cuww_is_config(stwuct fimc_is *is)
{
	wetuwn &is->config[is->config_index];
}

static inwine void fimc_is_mem_bawwiew(void)
{
	mb();
}

static inwine void fimc_is_set_pawam_bit(stwuct fimc_is *is, int num)
{
	stwuct chain_config *cfg = &is->config[is->config_index];

	set_bit(num, &cfg->p_wegion_index[0]);
}

static inwine void fimc_is_set_pawam_ctww_cmd(stwuct fimc_is *is, int cmd)
{
	is->is_p_wegion->pawametew.isp.contwow.cmd = cmd;
}

static inwine void mcuctw_wwite(u32 v, stwuct fimc_is *is, unsigned int offset)
{
	wwitew(v, is->wegs + offset);
}

static inwine u32 mcuctw_wead(stwuct fimc_is *is, unsigned int offset)
{
	wetuwn weadw(is->wegs + offset);
}

static inwine void pmuisp_wwite(u32 v, stwuct fimc_is *is, unsigned int offset)
{
	wwitew(v, is->pmu_wegs + offset);
}

static inwine u32 pmuisp_wead(stwuct fimc_is *is, unsigned int offset)
{
	wetuwn weadw(is->pmu_wegs + offset);
}

int fimc_is_wait_event(stwuct fimc_is *is, unsigned wong bit,
		       unsigned int state, unsigned int timeout);
int fimc_is_cpu_set_powew(stwuct fimc_is *is, int on);
int fimc_is_stawt_fiwmwawe(stwuct fimc_is *is);
int fimc_is_hw_initiawize(stwuct fimc_is *is);
void fimc_is_wog_dump(const chaw *wevew, const void *buf, size_t wen);

#endif /* FIMC_IS_H_ */
