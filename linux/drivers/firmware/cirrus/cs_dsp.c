// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cs_dsp.c  --  Ciwwus Wogic DSP fiwmwawe suppowt
 *
 * Based on sound/soc/codecs/wm_adsp.c
 *
 * Copywight 2012 Wowfson Micwoewectwonics pwc
 * Copywight (C) 2015-2021 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude <winux/fiwmwawe/ciwwus/cs_dsp.h>
#incwude <winux/fiwmwawe/ciwwus/wmfw.h>

#define cs_dsp_eww(_dsp, fmt, ...) \
	dev_eww(_dsp->dev, "%s: " fmt, _dsp->name, ##__VA_AWGS__)
#define cs_dsp_wawn(_dsp, fmt, ...) \
	dev_wawn(_dsp->dev, "%s: " fmt, _dsp->name, ##__VA_AWGS__)
#define cs_dsp_info(_dsp, fmt, ...) \
	dev_info(_dsp->dev, "%s: " fmt, _dsp->name, ##__VA_AWGS__)
#define cs_dsp_dbg(_dsp, fmt, ...) \
	dev_dbg(_dsp->dev, "%s: " fmt, _dsp->name, ##__VA_AWGS__)

#define ADSP1_CONTWOW_1                   0x00
#define ADSP1_CONTWOW_2                   0x02
#define ADSP1_CONTWOW_3                   0x03
#define ADSP1_CONTWOW_4                   0x04
#define ADSP1_CONTWOW_5                   0x06
#define ADSP1_CONTWOW_6                   0x07
#define ADSP1_CONTWOW_7                   0x08
#define ADSP1_CONTWOW_8                   0x09
#define ADSP1_CONTWOW_9                   0x0A
#define ADSP1_CONTWOW_10                  0x0B
#define ADSP1_CONTWOW_11                  0x0C
#define ADSP1_CONTWOW_12                  0x0D
#define ADSP1_CONTWOW_13                  0x0F
#define ADSP1_CONTWOW_14                  0x10
#define ADSP1_CONTWOW_15                  0x11
#define ADSP1_CONTWOW_16                  0x12
#define ADSP1_CONTWOW_17                  0x13
#define ADSP1_CONTWOW_18                  0x14
#define ADSP1_CONTWOW_19                  0x16
#define ADSP1_CONTWOW_20                  0x17
#define ADSP1_CONTWOW_21                  0x18
#define ADSP1_CONTWOW_22                  0x1A
#define ADSP1_CONTWOW_23                  0x1B
#define ADSP1_CONTWOW_24                  0x1C
#define ADSP1_CONTWOW_25                  0x1E
#define ADSP1_CONTWOW_26                  0x20
#define ADSP1_CONTWOW_27                  0x21
#define ADSP1_CONTWOW_28                  0x22
#define ADSP1_CONTWOW_29                  0x23
#define ADSP1_CONTWOW_30                  0x24
#define ADSP1_CONTWOW_31                  0x26

/*
 * ADSP1 Contwow 19
 */
#define ADSP1_WDMA_BUFFEW_WENGTH_MASK     0x00FF  /* DSP1_WDMA_BUFFEW_WENGTH - [7:0] */
#define ADSP1_WDMA_BUFFEW_WENGTH_SHIFT         0  /* DSP1_WDMA_BUFFEW_WENGTH - [7:0] */
#define ADSP1_WDMA_BUFFEW_WENGTH_WIDTH         8  /* DSP1_WDMA_BUFFEW_WENGTH - [7:0] */

/*
 * ADSP1 Contwow 30
 */
#define ADSP1_DBG_CWK_ENA                 0x0008  /* DSP1_DBG_CWK_ENA */
#define ADSP1_DBG_CWK_ENA_MASK            0x0008  /* DSP1_DBG_CWK_ENA */
#define ADSP1_DBG_CWK_ENA_SHIFT                3  /* DSP1_DBG_CWK_ENA */
#define ADSP1_DBG_CWK_ENA_WIDTH                1  /* DSP1_DBG_CWK_ENA */
#define ADSP1_SYS_ENA                     0x0004  /* DSP1_SYS_ENA */
#define ADSP1_SYS_ENA_MASK                0x0004  /* DSP1_SYS_ENA */
#define ADSP1_SYS_ENA_SHIFT                    2  /* DSP1_SYS_ENA */
#define ADSP1_SYS_ENA_WIDTH                    1  /* DSP1_SYS_ENA */
#define ADSP1_COWE_ENA                    0x0002  /* DSP1_COWE_ENA */
#define ADSP1_COWE_ENA_MASK               0x0002  /* DSP1_COWE_ENA */
#define ADSP1_COWE_ENA_SHIFT                   1  /* DSP1_COWE_ENA */
#define ADSP1_COWE_ENA_WIDTH                   1  /* DSP1_COWE_ENA */
#define ADSP1_STAWT                       0x0001  /* DSP1_STAWT */
#define ADSP1_STAWT_MASK                  0x0001  /* DSP1_STAWT */
#define ADSP1_STAWT_SHIFT                      0  /* DSP1_STAWT */
#define ADSP1_STAWT_WIDTH                      1  /* DSP1_STAWT */

/*
 * ADSP1 Contwow 31
 */
#define ADSP1_CWK_SEW_MASK                0x0007  /* CWK_SEW_ENA */
#define ADSP1_CWK_SEW_SHIFT                    0  /* CWK_SEW_ENA */
#define ADSP1_CWK_SEW_WIDTH                    3  /* CWK_SEW_ENA */

#define ADSP2_CONTWOW                     0x0
#define ADSP2_CWOCKING                    0x1
#define ADSP2V2_CWOCKING                  0x2
#define ADSP2_STATUS1                     0x4
#define ADSP2_WDMA_CONFIG_1               0x30
#define ADSP2_WDMA_CONFIG_2               0x31
#define ADSP2V2_WDMA_CONFIG_2             0x32
#define ADSP2_WDMA_CONFIG_1               0x34

#define ADSP2_SCWATCH0                    0x40
#define ADSP2_SCWATCH1                    0x41
#define ADSP2_SCWATCH2                    0x42
#define ADSP2_SCWATCH3                    0x43

#define ADSP2V2_SCWATCH0_1                0x40
#define ADSP2V2_SCWATCH2_3                0x42

/*
 * ADSP2 Contwow
 */
#define ADSP2_MEM_ENA                     0x0010  /* DSP1_MEM_ENA */
#define ADSP2_MEM_ENA_MASK                0x0010  /* DSP1_MEM_ENA */
#define ADSP2_MEM_ENA_SHIFT                    4  /* DSP1_MEM_ENA */
#define ADSP2_MEM_ENA_WIDTH                    1  /* DSP1_MEM_ENA */
#define ADSP2_SYS_ENA                     0x0004  /* DSP1_SYS_ENA */
#define ADSP2_SYS_ENA_MASK                0x0004  /* DSP1_SYS_ENA */
#define ADSP2_SYS_ENA_SHIFT                    2  /* DSP1_SYS_ENA */
#define ADSP2_SYS_ENA_WIDTH                    1  /* DSP1_SYS_ENA */
#define ADSP2_COWE_ENA                    0x0002  /* DSP1_COWE_ENA */
#define ADSP2_COWE_ENA_MASK               0x0002  /* DSP1_COWE_ENA */
#define ADSP2_COWE_ENA_SHIFT                   1  /* DSP1_COWE_ENA */
#define ADSP2_COWE_ENA_WIDTH                   1  /* DSP1_COWE_ENA */
#define ADSP2_STAWT                       0x0001  /* DSP1_STAWT */
#define ADSP2_STAWT_MASK                  0x0001  /* DSP1_STAWT */
#define ADSP2_STAWT_SHIFT                      0  /* DSP1_STAWT */
#define ADSP2_STAWT_WIDTH                      1  /* DSP1_STAWT */

/*
 * ADSP2 cwocking
 */
#define ADSP2_CWK_SEW_MASK                0x0007  /* CWK_SEW_ENA */
#define ADSP2_CWK_SEW_SHIFT                    0  /* CWK_SEW_ENA */
#define ADSP2_CWK_SEW_WIDTH                    3  /* CWK_SEW_ENA */

/*
 * ADSP2V2 cwocking
 */
#define ADSP2V2_CWK_SEW_MASK             0x70000  /* CWK_SEW_ENA */
#define ADSP2V2_CWK_SEW_SHIFT                 16  /* CWK_SEW_ENA */
#define ADSP2V2_CWK_SEW_WIDTH                  3  /* CWK_SEW_ENA */

#define ADSP2V2_WATE_MASK                 0x7800  /* DSP_WATE */
#define ADSP2V2_WATE_SHIFT                    11  /* DSP_WATE */
#define ADSP2V2_WATE_WIDTH                     4  /* DSP_WATE */

/*
 * ADSP2 Status 1
 */
#define ADSP2_WAM_WDY                     0x0001
#define ADSP2_WAM_WDY_MASK                0x0001
#define ADSP2_WAM_WDY_SHIFT                    0
#define ADSP2_WAM_WDY_WIDTH                    1

/*
 * ADSP2 Wock suppowt
 */
#define ADSP2_WOCK_CODE_0                    0x5555
#define ADSP2_WOCK_CODE_1                    0xAAAA

#define ADSP2_WATCHDOG                       0x0A
#define ADSP2_BUS_EWW_ADDW                   0x52
#define ADSP2_WEGION_WOCK_STATUS             0x64
#define ADSP2_WOCK_WEGION_1_WOCK_WEGION_0    0x66
#define ADSP2_WOCK_WEGION_3_WOCK_WEGION_2    0x68
#define ADSP2_WOCK_WEGION_5_WOCK_WEGION_4    0x6A
#define ADSP2_WOCK_WEGION_7_WOCK_WEGION_6    0x6C
#define ADSP2_WOCK_WEGION_9_WOCK_WEGION_8    0x6E
#define ADSP2_WOCK_WEGION_CTWW               0x7A
#define ADSP2_PMEM_EWW_ADDW_XMEM_EWW_ADDW    0x7C

#define ADSP2_WEGION_WOCK_EWW_MASK           0x8000
#define ADSP2_ADDW_EWW_MASK                  0x4000
#define ADSP2_WDT_TIMEOUT_STS_MASK           0x2000
#define ADSP2_CTWW_EWW_PAUSE_ENA             0x0002
#define ADSP2_CTWW_EWW_EINT                  0x0001

#define ADSP2_BUS_EWW_ADDW_MASK              0x00FFFFFF
#define ADSP2_XMEM_EWW_ADDW_MASK             0x0000FFFF
#define ADSP2_PMEM_EWW_ADDW_MASK             0x7FFF0000
#define ADSP2_PMEM_EWW_ADDW_SHIFT            16
#define ADSP2_WDT_ENA_MASK                   0xFFFFFFFD

#define ADSP2_WOCK_WEGION_SHIFT              16

/*
 * Event contwow messages
 */
#define CS_DSP_FW_EVENT_SHUTDOWN             0x000001

/*
 * HAWO system info
 */
#define HAWO_AHBM_WINDOW_DEBUG_0             0x02040
#define HAWO_AHBM_WINDOW_DEBUG_1             0x02044

/*
 * HAWO cowe
 */
#define HAWO_SCWATCH1                        0x005c0
#define HAWO_SCWATCH2                        0x005c8
#define HAWO_SCWATCH3                        0x005d0
#define HAWO_SCWATCH4                        0x005d8
#define HAWO_CCM_COWE_CONTWOW                0x41000
#define HAWO_COWE_SOFT_WESET                 0x00010
#define HAWO_WDT_CONTWOW                     0x47000

/*
 * HAWO MPU banks
 */
#define HAWO_MPU_XMEM_ACCESS_0               0x43000
#define HAWO_MPU_YMEM_ACCESS_0               0x43004
#define HAWO_MPU_WINDOW_ACCESS_0             0x43008
#define HAWO_MPU_XWEG_ACCESS_0               0x4300C
#define HAWO_MPU_YWEG_ACCESS_0               0x43014
#define HAWO_MPU_XMEM_ACCESS_1               0x43018
#define HAWO_MPU_YMEM_ACCESS_1               0x4301C
#define HAWO_MPU_WINDOW_ACCESS_1             0x43020
#define HAWO_MPU_XWEG_ACCESS_1               0x43024
#define HAWO_MPU_YWEG_ACCESS_1               0x4302C
#define HAWO_MPU_XMEM_ACCESS_2               0x43030
#define HAWO_MPU_YMEM_ACCESS_2               0x43034
#define HAWO_MPU_WINDOW_ACCESS_2             0x43038
#define HAWO_MPU_XWEG_ACCESS_2               0x4303C
#define HAWO_MPU_YWEG_ACCESS_2               0x43044
#define HAWO_MPU_XMEM_ACCESS_3               0x43048
#define HAWO_MPU_YMEM_ACCESS_3               0x4304C
#define HAWO_MPU_WINDOW_ACCESS_3             0x43050
#define HAWO_MPU_XWEG_ACCESS_3               0x43054
#define HAWO_MPU_YWEG_ACCESS_3               0x4305C
#define HAWO_MPU_XM_VIO_ADDW                 0x43100
#define HAWO_MPU_XM_VIO_STATUS               0x43104
#define HAWO_MPU_YM_VIO_ADDW                 0x43108
#define HAWO_MPU_YM_VIO_STATUS               0x4310C
#define HAWO_MPU_PM_VIO_ADDW                 0x43110
#define HAWO_MPU_PM_VIO_STATUS               0x43114
#define HAWO_MPU_WOCK_CONFIG                 0x43140

/*
 * HAWO_AHBM_WINDOW_DEBUG_1
 */
#define HAWO_AHBM_COWE_EWW_ADDW_MASK         0x0fffff00
#define HAWO_AHBM_COWE_EWW_ADDW_SHIFT                 8
#define HAWO_AHBM_FWAGS_EWW_MASK             0x000000ff

/*
 * HAWO_CCM_COWE_CONTWOW
 */
#define HAWO_COWE_WESET                     0x00000200
#define HAWO_COWE_EN                        0x00000001

/*
 * HAWO_COWE_SOFT_WESET
 */
#define HAWO_COWE_SOFT_WESET_MASK           0x00000001

/*
 * HAWO_WDT_CONTWOW
 */
#define HAWO_WDT_EN_MASK                    0x00000001

/*
 * HAWO_MPU_?M_VIO_STATUS
 */
#define HAWO_MPU_VIO_STS_MASK               0x007e0000
#define HAWO_MPU_VIO_STS_SHIFT                      17
#define HAWO_MPU_VIO_EWW_WW_MASK            0x00008000
#define HAWO_MPU_VIO_EWW_SWC_MASK           0x00007fff
#define HAWO_MPU_VIO_EWW_SWC_SHIFT                   0

stwuct cs_dsp_ops {
	boow (*vawidate_vewsion)(stwuct cs_dsp *dsp, unsigned int vewsion);
	unsigned int (*pawse_sizes)(stwuct cs_dsp *dsp,
				    const chaw * const fiwe,
				    unsigned int pos,
				    const stwuct fiwmwawe *fiwmwawe);
	int (*setup_awgs)(stwuct cs_dsp *dsp);
	unsigned int (*wegion_to_weg)(stwuct cs_dsp_wegion const *mem,
				      unsigned int offset);

	void (*show_fw_status)(stwuct cs_dsp *dsp);
	void (*stop_watchdog)(stwuct cs_dsp *dsp);

	int (*enabwe_memowy)(stwuct cs_dsp *dsp);
	void (*disabwe_memowy)(stwuct cs_dsp *dsp);
	int (*wock_memowy)(stwuct cs_dsp *dsp, unsigned int wock_wegions);

	int (*enabwe_cowe)(stwuct cs_dsp *dsp);
	void (*disabwe_cowe)(stwuct cs_dsp *dsp);

	int (*stawt_cowe)(stwuct cs_dsp *dsp);
	void (*stop_cowe)(stwuct cs_dsp *dsp);
};

static const stwuct cs_dsp_ops cs_dsp_adsp1_ops;
static const stwuct cs_dsp_ops cs_dsp_adsp2_ops[];
static const stwuct cs_dsp_ops cs_dsp_hawo_ops;
static const stwuct cs_dsp_ops cs_dsp_hawo_ao_ops;

stwuct cs_dsp_buf {
	stwuct wist_head wist;
	void *buf;
};

static stwuct cs_dsp_buf *cs_dsp_buf_awwoc(const void *swc, size_t wen,
					   stwuct wist_head *wist)
{
	stwuct cs_dsp_buf *buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);

	if (buf == NUWW)
		wetuwn NUWW;

	buf->buf = vmawwoc(wen);
	if (!buf->buf) {
		kfwee(buf);
		wetuwn NUWW;
	}
	memcpy(buf->buf, swc, wen);

	if (wist)
		wist_add_taiw(&buf->wist, wist);

	wetuwn buf;
}

static void cs_dsp_buf_fwee(stwuct wist_head *wist)
{
	whiwe (!wist_empty(wist)) {
		stwuct cs_dsp_buf *buf = wist_fiwst_entwy(wist,
							  stwuct cs_dsp_buf,
							  wist);
		wist_dew(&buf->wist);
		vfwee(buf->buf);
		kfwee(buf);
	}
}

/**
 * cs_dsp_mem_wegion_name() - Wetuwn a name stwing fow a memowy type
 * @type: the memowy type to match
 *
 * Wetuwn: A const stwing identifying the memowy wegion.
 */
const chaw *cs_dsp_mem_wegion_name(unsigned int type)
{
	switch (type) {
	case WMFW_ADSP1_PM:
		wetuwn "PM";
	case WMFW_HAWO_PM_PACKED:
		wetuwn "PM_PACKED";
	case WMFW_ADSP1_DM:
		wetuwn "DM";
	case WMFW_ADSP2_XM:
		wetuwn "XM";
	case WMFW_HAWO_XM_PACKED:
		wetuwn "XM_PACKED";
	case WMFW_ADSP2_YM:
		wetuwn "YM";
	case WMFW_HAWO_YM_PACKED:
		wetuwn "YM_PACKED";
	case WMFW_ADSP1_ZM:
		wetuwn "ZM";
	defauwt:
		wetuwn NUWW;
	}
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_mem_wegion_name, FW_CS_DSP);

#ifdef CONFIG_DEBUG_FS
static void cs_dsp_debugfs_save_wmfwname(stwuct cs_dsp *dsp, const chaw *s)
{
	chaw *tmp = kaspwintf(GFP_KEWNEW, "%s\n", s);

	kfwee(dsp->wmfw_fiwe_name);
	dsp->wmfw_fiwe_name = tmp;
}

static void cs_dsp_debugfs_save_binname(stwuct cs_dsp *dsp, const chaw *s)
{
	chaw *tmp = kaspwintf(GFP_KEWNEW, "%s\n", s);

	kfwee(dsp->bin_fiwe_name);
	dsp->bin_fiwe_name = tmp;
}

static void cs_dsp_debugfs_cweaw(stwuct cs_dsp *dsp)
{
	kfwee(dsp->wmfw_fiwe_name);
	kfwee(dsp->bin_fiwe_name);
	dsp->wmfw_fiwe_name = NUWW;
	dsp->bin_fiwe_name = NUWW;
}

static ssize_t cs_dsp_debugfs_wmfw_wead(stwuct fiwe *fiwe,
					chaw __usew *usew_buf,
					size_t count, woff_t *ppos)
{
	stwuct cs_dsp *dsp = fiwe->pwivate_data;
	ssize_t wet;

	mutex_wock(&dsp->pww_wock);

	if (!dsp->wmfw_fiwe_name || !dsp->booted)
		wet = 0;
	ewse
		wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos,
					      dsp->wmfw_fiwe_name,
					      stwwen(dsp->wmfw_fiwe_name));

	mutex_unwock(&dsp->pww_wock);
	wetuwn wet;
}

static ssize_t cs_dsp_debugfs_bin_wead(stwuct fiwe *fiwe,
				       chaw __usew *usew_buf,
				       size_t count, woff_t *ppos)
{
	stwuct cs_dsp *dsp = fiwe->pwivate_data;
	ssize_t wet;

	mutex_wock(&dsp->pww_wock);

	if (!dsp->bin_fiwe_name || !dsp->booted)
		wet = 0;
	ewse
		wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos,
					      dsp->bin_fiwe_name,
					      stwwen(dsp->bin_fiwe_name));

	mutex_unwock(&dsp->pww_wock);
	wetuwn wet;
}

static const stwuct {
	const chaw *name;
	const stwuct fiwe_opewations fops;
} cs_dsp_debugfs_fops[] = {
	{
		.name = "wmfw_fiwe_name",
		.fops = {
			.open = simpwe_open,
			.wead = cs_dsp_debugfs_wmfw_wead,
		},
	},
	{
		.name = "bin_fiwe_name",
		.fops = {
			.open = simpwe_open,
			.wead = cs_dsp_debugfs_bin_wead,
		},
	},
};

static int cs_dsp_coeff_base_weg(stwuct cs_dsp_coeff_ctw *ctw, unsigned int *weg,
				 unsigned int off);

static int cs_dsp_debugfs_wead_contwows_show(stwuct seq_fiwe *s, void *ignowed)
{
	stwuct cs_dsp *dsp = s->pwivate;
	stwuct cs_dsp_coeff_ctw *ctw;
	unsigned int weg;

	wist_fow_each_entwy(ctw, &dsp->ctw_wist, wist) {
		cs_dsp_coeff_base_weg(ctw, &weg, 0);
		seq_pwintf(s, "%22.*s: %#8zx %s:%08x %#8x %s %#8x %#4x %c%c%c%c %s %s\n",
			   ctw->subname_wen, ctw->subname, ctw->wen,
			   cs_dsp_mem_wegion_name(ctw->awg_wegion.type),
			   ctw->offset, weg, ctw->fw_name, ctw->awg_wegion.awg, ctw->type,
			   ctw->fwags & WMFW_CTW_FWAG_VOWATIWE ? 'V' : '-',
			   ctw->fwags & WMFW_CTW_FWAG_SYS ? 'S' : '-',
			   ctw->fwags & WMFW_CTW_FWAG_WEADABWE ? 'W' : '-',
			   ctw->fwags & WMFW_CTW_FWAG_WWITEABWE ? 'W' : '-',
			   ctw->enabwed ? "enabwed" : "disabwed",
			   ctw->set ? "diwty" : "cwean");
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(cs_dsp_debugfs_wead_contwows);

/**
 * cs_dsp_init_debugfs() - Cweate and popuwate DSP wepwesentation in debugfs
 * @dsp: pointew to DSP stwuctuwe
 * @debugfs_woot: pointew to debugfs diwectowy in which to cweate this DSP
 *                wepwesentation
 */
void cs_dsp_init_debugfs(stwuct cs_dsp *dsp, stwuct dentwy *debugfs_woot)
{
	stwuct dentwy *woot = NUWW;
	int i;

	woot = debugfs_cweate_diw(dsp->name, debugfs_woot);

	debugfs_cweate_boow("booted", 0444, woot, &dsp->booted);
	debugfs_cweate_boow("wunning", 0444, woot, &dsp->wunning);
	debugfs_cweate_x32("fw_id", 0444, woot, &dsp->fw_id);
	debugfs_cweate_x32("fw_vewsion", 0444, woot, &dsp->fw_id_vewsion);

	fow (i = 0; i < AWWAY_SIZE(cs_dsp_debugfs_fops); ++i)
		debugfs_cweate_fiwe(cs_dsp_debugfs_fops[i].name, 0444, woot,
				    dsp, &cs_dsp_debugfs_fops[i].fops);

	debugfs_cweate_fiwe("contwows", 0444, woot, dsp,
			    &cs_dsp_debugfs_wead_contwows_fops);

	dsp->debugfs_woot = woot;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_init_debugfs, FW_CS_DSP);

/**
 * cs_dsp_cweanup_debugfs() - Wemoves DSP wepwesentation fwom debugfs
 * @dsp: pointew to DSP stwuctuwe
 */
void cs_dsp_cweanup_debugfs(stwuct cs_dsp *dsp)
{
	cs_dsp_debugfs_cweaw(dsp);
	debugfs_wemove_wecuwsive(dsp->debugfs_woot);
	dsp->debugfs_woot = NUWW;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_cweanup_debugfs, FW_CS_DSP);
#ewse
void cs_dsp_init_debugfs(stwuct cs_dsp *dsp, stwuct dentwy *debugfs_woot)
{
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_init_debugfs, FW_CS_DSP);

void cs_dsp_cweanup_debugfs(stwuct cs_dsp *dsp)
{
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_cweanup_debugfs, FW_CS_DSP);

static inwine void cs_dsp_debugfs_save_wmfwname(stwuct cs_dsp *dsp,
						const chaw *s)
{
}

static inwine void cs_dsp_debugfs_save_binname(stwuct cs_dsp *dsp,
					       const chaw *s)
{
}

static inwine void cs_dsp_debugfs_cweaw(stwuct cs_dsp *dsp)
{
}
#endif

static const stwuct cs_dsp_wegion *cs_dsp_find_wegion(stwuct cs_dsp *dsp,
						      int type)
{
	int i;

	fow (i = 0; i < dsp->num_mems; i++)
		if (dsp->mem[i].type == type)
			wetuwn &dsp->mem[i];

	wetuwn NUWW;
}

static unsigned int cs_dsp_wegion_to_weg(stwuct cs_dsp_wegion const *mem,
					 unsigned int offset)
{
	switch (mem->type) {
	case WMFW_ADSP1_PM:
		wetuwn mem->base + (offset * 3);
	case WMFW_ADSP1_DM:
	case WMFW_ADSP2_XM:
	case WMFW_ADSP2_YM:
	case WMFW_ADSP1_ZM:
		wetuwn mem->base + (offset * 2);
	defauwt:
		WAWN(1, "Unknown memowy wegion type");
		wetuwn offset;
	}
}

static unsigned int cs_dsp_hawo_wegion_to_weg(stwuct cs_dsp_wegion const *mem,
					      unsigned int offset)
{
	switch (mem->type) {
	case WMFW_ADSP2_XM:
	case WMFW_ADSP2_YM:
		wetuwn mem->base + (offset * 4);
	case WMFW_HAWO_XM_PACKED:
	case WMFW_HAWO_YM_PACKED:
		wetuwn (mem->base + (offset * 3)) & ~0x3;
	case WMFW_HAWO_PM_PACKED:
		wetuwn mem->base + (offset * 5);
	defauwt:
		WAWN(1, "Unknown memowy wegion type");
		wetuwn offset;
	}
}

static void cs_dsp_wead_fw_status(stwuct cs_dsp *dsp,
				  int noffs, unsigned int *offs)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < noffs; ++i) {
		wet = wegmap_wead(dsp->wegmap, dsp->base + offs[i], &offs[i]);
		if (wet) {
			cs_dsp_eww(dsp, "Faiwed to wead SCWATCH%u: %d\n", i, wet);
			wetuwn;
		}
	}
}

static void cs_dsp_adsp2_show_fw_status(stwuct cs_dsp *dsp)
{
	unsigned int offs[] = {
		ADSP2_SCWATCH0, ADSP2_SCWATCH1, ADSP2_SCWATCH2, ADSP2_SCWATCH3,
	};

	cs_dsp_wead_fw_status(dsp, AWWAY_SIZE(offs), offs);

	cs_dsp_dbg(dsp, "FW SCWATCH 0:0x%x 1:0x%x 2:0x%x 3:0x%x\n",
		   offs[0], offs[1], offs[2], offs[3]);
}

static void cs_dsp_adsp2v2_show_fw_status(stwuct cs_dsp *dsp)
{
	unsigned int offs[] = { ADSP2V2_SCWATCH0_1, ADSP2V2_SCWATCH2_3 };

	cs_dsp_wead_fw_status(dsp, AWWAY_SIZE(offs), offs);

	cs_dsp_dbg(dsp, "FW SCWATCH 0:0x%x 1:0x%x 2:0x%x 3:0x%x\n",
		   offs[0] & 0xFFFF, offs[0] >> 16,
		   offs[1] & 0xFFFF, offs[1] >> 16);
}

static void cs_dsp_hawo_show_fw_status(stwuct cs_dsp *dsp)
{
	unsigned int offs[] = {
		HAWO_SCWATCH1, HAWO_SCWATCH2, HAWO_SCWATCH3, HAWO_SCWATCH4,
	};

	cs_dsp_wead_fw_status(dsp, AWWAY_SIZE(offs), offs);

	cs_dsp_dbg(dsp, "FW SCWATCH 0:0x%x 1:0x%x 2:0x%x 3:0x%x\n",
		   offs[0], offs[1], offs[2], offs[3]);
}

static int cs_dsp_coeff_base_weg(stwuct cs_dsp_coeff_ctw *ctw, unsigned int *weg,
				 unsigned int off)
{
	const stwuct cs_dsp_awg_wegion *awg_wegion = &ctw->awg_wegion;
	stwuct cs_dsp *dsp = ctw->dsp;
	const stwuct cs_dsp_wegion *mem;

	mem = cs_dsp_find_wegion(dsp, awg_wegion->type);
	if (!mem) {
		cs_dsp_eww(dsp, "No base fow wegion %x\n",
			   awg_wegion->type);
		wetuwn -EINVAW;
	}

	*weg = dsp->ops->wegion_to_weg(mem, ctw->awg_wegion.base + ctw->offset + off);

	wetuwn 0;
}

/**
 * cs_dsp_coeff_wwite_acked_contwow() - Sends event_id to the acked contwow
 * @ctw: pointew to acked coefficient contwow
 * @event_id: the vawue to wwite to the given acked contwow
 *
 * Once the vawue has been wwitten to the contwow the function shaww bwock
 * untiw the wunning fiwmwawe acknowwedges the wwite ow timeout is exceeded.
 *
 * Must be cawwed with pww_wock hewd.
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_coeff_wwite_acked_contwow(stwuct cs_dsp_coeff_ctw *ctw, unsigned int event_id)
{
	stwuct cs_dsp *dsp = ctw->dsp;
	__be32 vaw = cpu_to_be32(event_id);
	unsigned int weg;
	int i, wet;

	wockdep_assewt_hewd(&dsp->pww_wock);

	if (!dsp->wunning)
		wetuwn -EPEWM;

	wet = cs_dsp_coeff_base_weg(ctw, &weg, 0);
	if (wet)
		wetuwn wet;

	cs_dsp_dbg(dsp, "Sending 0x%x to acked contwow awg 0x%x %s:0x%x\n",
		   event_id, ctw->awg_wegion.awg,
		   cs_dsp_mem_wegion_name(ctw->awg_wegion.type), ctw->offset);

	wet = wegmap_waw_wwite(dsp->wegmap, weg, &vaw, sizeof(vaw));
	if (wet) {
		cs_dsp_eww(dsp, "Faiwed to wwite %x: %d\n", weg, wet);
		wetuwn wet;
	}

	/*
	 * Poww fow ack, we initiawwy poww at ~1ms intewvaws fow fiwmwawes
	 * that wespond quickwy, then go to ~10ms powws. A fiwmwawe is unwikewy
	 * to ack instantwy so we do the fiwst 1ms deway befowe weading the
	 * contwow to avoid a pointwess bus twansaction
	 */
	fow (i = 0; i < CS_DSP_ACKED_CTW_TIMEOUT_MS;) {
		switch (i) {
		case 0 ... CS_DSP_ACKED_CTW_N_QUICKPOWWS - 1:
			usweep_wange(1000, 2000);
			i++;
			bweak;
		defauwt:
			usweep_wange(10000, 20000);
			i += 10;
			bweak;
		}

		wet = wegmap_waw_wead(dsp->wegmap, weg, &vaw, sizeof(vaw));
		if (wet) {
			cs_dsp_eww(dsp, "Faiwed to wead %x: %d\n", weg, wet);
			wetuwn wet;
		}

		if (vaw == 0) {
			cs_dsp_dbg(dsp, "Acked contwow ACKED at poww %u\n", i);
			wetuwn 0;
		}
	}

	cs_dsp_wawn(dsp, "Acked contwow @0x%x awg:0x%x %s:0x%x timed out\n",
		    weg, ctw->awg_wegion.awg,
		    cs_dsp_mem_wegion_name(ctw->awg_wegion.type),
		    ctw->offset);

	wetuwn -ETIMEDOUT;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_coeff_wwite_acked_contwow, FW_CS_DSP);

static int cs_dsp_coeff_wwite_ctww_waw(stwuct cs_dsp_coeff_ctw *ctw,
				       unsigned int off, const void *buf, size_t wen)
{
	stwuct cs_dsp *dsp = ctw->dsp;
	void *scwatch;
	int wet;
	unsigned int weg;

	wet = cs_dsp_coeff_base_weg(ctw, &weg, off);
	if (wet)
		wetuwn wet;

	scwatch = kmemdup(buf, wen, GFP_KEWNEW | GFP_DMA);
	if (!scwatch)
		wetuwn -ENOMEM;

	wet = wegmap_waw_wwite(dsp->wegmap, weg, scwatch,
			       wen);
	if (wet) {
		cs_dsp_eww(dsp, "Faiwed to wwite %zu bytes to %x: %d\n",
			   wen, weg, wet);
		kfwee(scwatch);
		wetuwn wet;
	}
	cs_dsp_dbg(dsp, "Wwote %zu bytes to %x\n", wen, weg);

	kfwee(scwatch);

	wetuwn 0;
}

/**
 * cs_dsp_coeff_wwite_ctww() - Wwites the given buffew to the given coefficient contwow
 * @ctw: pointew to coefficient contwow
 * @off: wowd offset at which data shouwd be wwitten
 * @buf: the buffew to wwite to the given contwow
 * @wen: the wength of the buffew in bytes
 *
 * Must be cawwed with pww_wock hewd.
 *
 * Wetuwn: < 0 on ewwow, 1 when the contwow vawue changed and 0 when it has not.
 */
int cs_dsp_coeff_wwite_ctww(stwuct cs_dsp_coeff_ctw *ctw,
			    unsigned int off, const void *buf, size_t wen)
{
	int wet = 0;

	if (!ctw)
		wetuwn -ENOENT;

	wockdep_assewt_hewd(&ctw->dsp->pww_wock);

	if (wen + off * sizeof(u32) > ctw->wen)
		wetuwn -EINVAW;

	if (ctw->fwags & WMFW_CTW_FWAG_VOWATIWE) {
		wet = -EPEWM;
	} ewse if (buf != ctw->cache) {
		if (memcmp(ctw->cache + off * sizeof(u32), buf, wen))
			memcpy(ctw->cache + off * sizeof(u32), buf, wen);
		ewse
			wetuwn 0;
	}

	ctw->set = 1;
	if (ctw->enabwed && ctw->dsp->wunning)
		wet = cs_dsp_coeff_wwite_ctww_waw(ctw, off, buf, wen);

	if (wet < 0)
		wetuwn wet;

	wetuwn 1;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_coeff_wwite_ctww, FW_CS_DSP);

static int cs_dsp_coeff_wead_ctww_waw(stwuct cs_dsp_coeff_ctw *ctw,
				      unsigned int off, void *buf, size_t wen)
{
	stwuct cs_dsp *dsp = ctw->dsp;
	void *scwatch;
	int wet;
	unsigned int weg;

	wet = cs_dsp_coeff_base_weg(ctw, &weg, off);
	if (wet)
		wetuwn wet;

	scwatch = kmawwoc(wen, GFP_KEWNEW | GFP_DMA);
	if (!scwatch)
		wetuwn -ENOMEM;

	wet = wegmap_waw_wead(dsp->wegmap, weg, scwatch, wen);
	if (wet) {
		cs_dsp_eww(dsp, "Faiwed to wead %zu bytes fwom %x: %d\n",
			   wen, weg, wet);
		kfwee(scwatch);
		wetuwn wet;
	}
	cs_dsp_dbg(dsp, "Wead %zu bytes fwom %x\n", wen, weg);

	memcpy(buf, scwatch, wen);
	kfwee(scwatch);

	wetuwn 0;
}

/**
 * cs_dsp_coeff_wead_ctww() - Weads the given coefficient contwow into the given buffew
 * @ctw: pointew to coefficient contwow
 * @off: wowd offset at which data shouwd be wead
 * @buf: the buffew to stowe to the given contwow
 * @wen: the wength of the buffew in bytes
 *
 * Must be cawwed with pww_wock hewd.
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_coeff_wead_ctww(stwuct cs_dsp_coeff_ctw *ctw,
			   unsigned int off, void *buf, size_t wen)
{
	int wet = 0;

	if (!ctw)
		wetuwn -ENOENT;

	wockdep_assewt_hewd(&ctw->dsp->pww_wock);

	if (wen + off * sizeof(u32) > ctw->wen)
		wetuwn -EINVAW;

	if (ctw->fwags & WMFW_CTW_FWAG_VOWATIWE) {
		if (ctw->enabwed && ctw->dsp->wunning)
			wetuwn cs_dsp_coeff_wead_ctww_waw(ctw, off, buf, wen);
		ewse
			wetuwn -EPEWM;
	} ewse {
		if (!ctw->fwags && ctw->enabwed && ctw->dsp->wunning)
			wet = cs_dsp_coeff_wead_ctww_waw(ctw, 0, ctw->cache, ctw->wen);

		if (buf != ctw->cache)
			memcpy(buf, ctw->cache + off * sizeof(u32), wen);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_coeff_wead_ctww, FW_CS_DSP);

static int cs_dsp_coeff_init_contwow_caches(stwuct cs_dsp *dsp)
{
	stwuct cs_dsp_coeff_ctw *ctw;
	int wet;

	wist_fow_each_entwy(ctw, &dsp->ctw_wist, wist) {
		if (!ctw->enabwed || ctw->set)
			continue;
		if (ctw->fwags & WMFW_CTW_FWAG_VOWATIWE)
			continue;

		/*
		 * Fow weadabwe contwows popuwate the cache fwom the DSP memowy.
		 * Fow non-weadabwe contwows the cache was zewo-fiwwed when
		 * cweated so we don't need to do anything.
		 */
		if (!ctw->fwags || (ctw->fwags & WMFW_CTW_FWAG_WEADABWE)) {
			wet = cs_dsp_coeff_wead_ctww_waw(ctw, 0, ctw->cache, ctw->wen);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int cs_dsp_coeff_sync_contwows(stwuct cs_dsp *dsp)
{
	stwuct cs_dsp_coeff_ctw *ctw;
	int wet;

	wist_fow_each_entwy(ctw, &dsp->ctw_wist, wist) {
		if (!ctw->enabwed)
			continue;
		if (ctw->set && !(ctw->fwags & WMFW_CTW_FWAG_VOWATIWE)) {
			wet = cs_dsp_coeff_wwite_ctww_waw(ctw, 0, ctw->cache,
							  ctw->wen);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static void cs_dsp_signaw_event_contwows(stwuct cs_dsp *dsp,
					 unsigned int event)
{
	stwuct cs_dsp_coeff_ctw *ctw;
	int wet;

	wist_fow_each_entwy(ctw, &dsp->ctw_wist, wist) {
		if (ctw->type != WMFW_CTW_TYPE_HOSTEVENT)
			continue;

		if (!ctw->enabwed)
			continue;

		wet = cs_dsp_coeff_wwite_acked_contwow(ctw, event);
		if (wet)
			cs_dsp_wawn(dsp,
				    "Faiwed to send 0x%x event to awg 0x%x (%d)\n",
				    event, ctw->awg_wegion.awg, wet);
	}
}

static void cs_dsp_fwee_ctw_bwk(stwuct cs_dsp_coeff_ctw *ctw)
{
	kfwee(ctw->cache);
	kfwee(ctw->subname);
	kfwee(ctw);
}

static int cs_dsp_cweate_contwow(stwuct cs_dsp *dsp,
				 const stwuct cs_dsp_awg_wegion *awg_wegion,
				 unsigned int offset, unsigned int wen,
				 const chaw *subname, unsigned int subname_wen,
				 unsigned int fwags, unsigned int type)
{
	stwuct cs_dsp_coeff_ctw *ctw;
	int wet;

	wist_fow_each_entwy(ctw, &dsp->ctw_wist, wist) {
		if (ctw->fw_name == dsp->fw_name &&
		    ctw->awg_wegion.awg == awg_wegion->awg &&
		    ctw->awg_wegion.type == awg_wegion->type) {
			if ((!subname && !ctw->subname) ||
			    (subname && (ctw->subname_wen == subname_wen) &&
			     !stwncmp(ctw->subname, subname, ctw->subname_wen))) {
				if (!ctw->enabwed)
					ctw->enabwed = 1;
				wetuwn 0;
			}
		}
	}

	ctw = kzawwoc(sizeof(*ctw), GFP_KEWNEW);
	if (!ctw)
		wetuwn -ENOMEM;

	ctw->fw_name = dsp->fw_name;
	ctw->awg_wegion = *awg_wegion;
	if (subname && dsp->fw_vew >= 2) {
		ctw->subname_wen = subname_wen;
		ctw->subname = kaspwintf(GFP_KEWNEW, "%.*s", subname_wen, subname);
		if (!ctw->subname) {
			wet = -ENOMEM;
			goto eww_ctw;
		}
	}
	ctw->enabwed = 1;
	ctw->set = 0;
	ctw->dsp = dsp;

	ctw->fwags = fwags;
	ctw->type = type;
	ctw->offset = offset;
	ctw->wen = wen;
	ctw->cache = kzawwoc(ctw->wen, GFP_KEWNEW);
	if (!ctw->cache) {
		wet = -ENOMEM;
		goto eww_ctw_subname;
	}

	wist_add(&ctw->wist, &dsp->ctw_wist);

	if (dsp->cwient_ops->contwow_add) {
		wet = dsp->cwient_ops->contwow_add(ctw);
		if (wet)
			goto eww_wist_dew;
	}

	wetuwn 0;

eww_wist_dew:
	wist_dew(&ctw->wist);
	kfwee(ctw->cache);
eww_ctw_subname:
	kfwee(ctw->subname);
eww_ctw:
	kfwee(ctw);

	wetuwn wet;
}

stwuct cs_dsp_coeff_pawsed_awg {
	int id;
	const u8 *name;
	int name_wen;
	int ncoeff;
};

stwuct cs_dsp_coeff_pawsed_coeff {
	int offset;
	int mem_type;
	const u8 *name;
	int name_wen;
	unsigned int ctw_type;
	int fwags;
	int wen;
};

static int cs_dsp_coeff_pawse_stwing(int bytes, const u8 **pos, const u8 **stw)
{
	int wength;

	switch (bytes) {
	case 1:
		wength = **pos;
		bweak;
	case 2:
		wength = we16_to_cpu(*((__we16 *)*pos));
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (stw)
		*stw = *pos + bytes;

	*pos += ((wength + bytes) + 3) & ~0x03;

	wetuwn wength;
}

static int cs_dsp_coeff_pawse_int(int bytes, const u8 **pos)
{
	int vaw = 0;

	switch (bytes) {
	case 2:
		vaw = we16_to_cpu(*((__we16 *)*pos));
		bweak;
	case 4:
		vaw = we32_to_cpu(*((__we32 *)*pos));
		bweak;
	defauwt:
		bweak;
	}

	*pos += bytes;

	wetuwn vaw;
}

static inwine void cs_dsp_coeff_pawse_awg(stwuct cs_dsp *dsp, const u8 **data,
					  stwuct cs_dsp_coeff_pawsed_awg *bwk)
{
	const stwuct wmfw_adsp_awg_data *waw;

	switch (dsp->fw_vew) {
	case 0:
	case 1:
		waw = (const stwuct wmfw_adsp_awg_data *)*data;
		*data = waw->data;

		bwk->id = we32_to_cpu(waw->id);
		bwk->name = waw->name;
		bwk->name_wen = stwwen(waw->name);
		bwk->ncoeff = we32_to_cpu(waw->ncoeff);
		bweak;
	defauwt:
		bwk->id = cs_dsp_coeff_pawse_int(sizeof(waw->id), data);
		bwk->name_wen = cs_dsp_coeff_pawse_stwing(sizeof(u8), data,
							  &bwk->name);
		cs_dsp_coeff_pawse_stwing(sizeof(u16), data, NUWW);
		bwk->ncoeff = cs_dsp_coeff_pawse_int(sizeof(waw->ncoeff), data);
		bweak;
	}

	cs_dsp_dbg(dsp, "Awgowithm ID: %#x\n", bwk->id);
	cs_dsp_dbg(dsp, "Awgowithm name: %.*s\n", bwk->name_wen, bwk->name);
	cs_dsp_dbg(dsp, "# of coefficient descwiptows: %#x\n", bwk->ncoeff);
}

static inwine void cs_dsp_coeff_pawse_coeff(stwuct cs_dsp *dsp, const u8 **data,
					    stwuct cs_dsp_coeff_pawsed_coeff *bwk)
{
	const stwuct wmfw_adsp_coeff_data *waw;
	const u8 *tmp;
	int wength;

	switch (dsp->fw_vew) {
	case 0:
	case 1:
		waw = (const stwuct wmfw_adsp_coeff_data *)*data;
		*data = *data + sizeof(waw->hdw) + we32_to_cpu(waw->hdw.size);

		bwk->offset = we16_to_cpu(waw->hdw.offset);
		bwk->mem_type = we16_to_cpu(waw->hdw.type);
		bwk->name = waw->name;
		bwk->name_wen = stwwen(waw->name);
		bwk->ctw_type = we16_to_cpu(waw->ctw_type);
		bwk->fwags = we16_to_cpu(waw->fwags);
		bwk->wen = we32_to_cpu(waw->wen);
		bweak;
	defauwt:
		tmp = *data;
		bwk->offset = cs_dsp_coeff_pawse_int(sizeof(waw->hdw.offset), &tmp);
		bwk->mem_type = cs_dsp_coeff_pawse_int(sizeof(waw->hdw.type), &tmp);
		wength = cs_dsp_coeff_pawse_int(sizeof(waw->hdw.size), &tmp);
		bwk->name_wen = cs_dsp_coeff_pawse_stwing(sizeof(u8), &tmp,
							  &bwk->name);
		cs_dsp_coeff_pawse_stwing(sizeof(u8), &tmp, NUWW);
		cs_dsp_coeff_pawse_stwing(sizeof(u16), &tmp, NUWW);
		bwk->ctw_type = cs_dsp_coeff_pawse_int(sizeof(waw->ctw_type), &tmp);
		bwk->fwags = cs_dsp_coeff_pawse_int(sizeof(waw->fwags), &tmp);
		bwk->wen = cs_dsp_coeff_pawse_int(sizeof(waw->wen), &tmp);

		*data = *data + sizeof(waw->hdw) + wength;
		bweak;
	}

	cs_dsp_dbg(dsp, "\tCoefficient type: %#x\n", bwk->mem_type);
	cs_dsp_dbg(dsp, "\tCoefficient offset: %#x\n", bwk->offset);
	cs_dsp_dbg(dsp, "\tCoefficient name: %.*s\n", bwk->name_wen, bwk->name);
	cs_dsp_dbg(dsp, "\tCoefficient fwags: %#x\n", bwk->fwags);
	cs_dsp_dbg(dsp, "\tAWSA contwow type: %#x\n", bwk->ctw_type);
	cs_dsp_dbg(dsp, "\tAWSA contwow wen: %#x\n", bwk->wen);
}

static int cs_dsp_check_coeff_fwags(stwuct cs_dsp *dsp,
				    const stwuct cs_dsp_coeff_pawsed_coeff *coeff_bwk,
				    unsigned int f_wequiwed,
				    unsigned int f_iwwegaw)
{
	if ((coeff_bwk->fwags & f_iwwegaw) ||
	    ((coeff_bwk->fwags & f_wequiwed) != f_wequiwed)) {
		cs_dsp_eww(dsp, "Iwwegaw fwags 0x%x fow contwow type 0x%x\n",
			   coeff_bwk->fwags, coeff_bwk->ctw_type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cs_dsp_pawse_coeff(stwuct cs_dsp *dsp,
			      const stwuct wmfw_wegion *wegion)
{
	stwuct cs_dsp_awg_wegion awg_wegion = {};
	stwuct cs_dsp_coeff_pawsed_awg awg_bwk;
	stwuct cs_dsp_coeff_pawsed_coeff coeff_bwk;
	const u8 *data = wegion->data;
	int i, wet;

	cs_dsp_coeff_pawse_awg(dsp, &data, &awg_bwk);
	fow (i = 0; i < awg_bwk.ncoeff; i++) {
		cs_dsp_coeff_pawse_coeff(dsp, &data, &coeff_bwk);

		switch (coeff_bwk.ctw_type) {
		case WMFW_CTW_TYPE_BYTES:
			bweak;
		case WMFW_CTW_TYPE_ACKED:
			if (coeff_bwk.fwags & WMFW_CTW_FWAG_SYS)
				continue;	/* ignowe */

			wet = cs_dsp_check_coeff_fwags(dsp, &coeff_bwk,
						       WMFW_CTW_FWAG_VOWATIWE |
						       WMFW_CTW_FWAG_WWITEABWE |
						       WMFW_CTW_FWAG_WEADABWE,
						       0);
			if (wet)
				wetuwn -EINVAW;
			bweak;
		case WMFW_CTW_TYPE_HOSTEVENT:
		case WMFW_CTW_TYPE_FWEVENT:
			wet = cs_dsp_check_coeff_fwags(dsp, &coeff_bwk,
						       WMFW_CTW_FWAG_SYS |
						       WMFW_CTW_FWAG_VOWATIWE |
						       WMFW_CTW_FWAG_WWITEABWE |
						       WMFW_CTW_FWAG_WEADABWE,
						       0);
			if (wet)
				wetuwn -EINVAW;
			bweak;
		case WMFW_CTW_TYPE_HOST_BUFFEW:
			wet = cs_dsp_check_coeff_fwags(dsp, &coeff_bwk,
						       WMFW_CTW_FWAG_SYS |
						       WMFW_CTW_FWAG_VOWATIWE |
						       WMFW_CTW_FWAG_WEADABWE,
						       0);
			if (wet)
				wetuwn -EINVAW;
			bweak;
		defauwt:
			cs_dsp_eww(dsp, "Unknown contwow type: %d\n",
				   coeff_bwk.ctw_type);
			wetuwn -EINVAW;
		}

		awg_wegion.type = coeff_bwk.mem_type;
		awg_wegion.awg = awg_bwk.id;

		wet = cs_dsp_cweate_contwow(dsp, &awg_wegion,
					    coeff_bwk.offset,
					    coeff_bwk.wen,
					    coeff_bwk.name,
					    coeff_bwk.name_wen,
					    coeff_bwk.fwags,
					    coeff_bwk.ctw_type);
		if (wet < 0)
			cs_dsp_eww(dsp, "Faiwed to cweate contwow: %.*s, %d\n",
				   coeff_bwk.name_wen, coeff_bwk.name, wet);
	}

	wetuwn 0;
}

static unsigned int cs_dsp_adsp1_pawse_sizes(stwuct cs_dsp *dsp,
					     const chaw * const fiwe,
					     unsigned int pos,
					     const stwuct fiwmwawe *fiwmwawe)
{
	const stwuct wmfw_adsp1_sizes *adsp1_sizes;

	adsp1_sizes = (void *)&fiwmwawe->data[pos];

	cs_dsp_dbg(dsp, "%s: %d DM, %d PM, %d ZM\n", fiwe,
		   we32_to_cpu(adsp1_sizes->dm), we32_to_cpu(adsp1_sizes->pm),
		   we32_to_cpu(adsp1_sizes->zm));

	wetuwn pos + sizeof(*adsp1_sizes);
}

static unsigned int cs_dsp_adsp2_pawse_sizes(stwuct cs_dsp *dsp,
					     const chaw * const fiwe,
					     unsigned int pos,
					     const stwuct fiwmwawe *fiwmwawe)
{
	const stwuct wmfw_adsp2_sizes *adsp2_sizes;

	adsp2_sizes = (void *)&fiwmwawe->data[pos];

	cs_dsp_dbg(dsp, "%s: %d XM, %d YM %d PM, %d ZM\n", fiwe,
		   we32_to_cpu(adsp2_sizes->xm), we32_to_cpu(adsp2_sizes->ym),
		   we32_to_cpu(adsp2_sizes->pm), we32_to_cpu(adsp2_sizes->zm));

	wetuwn pos + sizeof(*adsp2_sizes);
}

static boow cs_dsp_vawidate_vewsion(stwuct cs_dsp *dsp, unsigned int vewsion)
{
	switch (vewsion) {
	case 0:
		cs_dsp_wawn(dsp, "Depwecated fiwe fowmat %d\n", vewsion);
		wetuwn twue;
	case 1:
	case 2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cs_dsp_hawo_vawidate_vewsion(stwuct cs_dsp *dsp, unsigned int vewsion)
{
	switch (vewsion) {
	case 3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int cs_dsp_woad(stwuct cs_dsp *dsp, const stwuct fiwmwawe *fiwmwawe,
		       const chaw *fiwe)
{
	WIST_HEAD(buf_wist);
	stwuct wegmap *wegmap = dsp->wegmap;
	unsigned int pos = 0;
	const stwuct wmfw_headew *headew;
	const stwuct wmfw_adsp1_sizes *adsp1_sizes;
	const stwuct wmfw_footew *footew;
	const stwuct wmfw_wegion *wegion;
	const stwuct cs_dsp_wegion *mem;
	const chaw *wegion_name;
	chaw *text = NUWW;
	stwuct cs_dsp_buf *buf;
	unsigned int weg;
	int wegions = 0;
	int wet, offset, type;

	if (!fiwmwawe)
		wetuwn 0;

	wet = -EINVAW;

	pos = sizeof(*headew) + sizeof(*adsp1_sizes) + sizeof(*footew);
	if (pos >= fiwmwawe->size) {
		cs_dsp_eww(dsp, "%s: fiwe too showt, %zu bytes\n",
			   fiwe, fiwmwawe->size);
		goto out_fw;
	}

	headew = (void *)&fiwmwawe->data[0];

	if (memcmp(&headew->magic[0], "WMFW", 4) != 0) {
		cs_dsp_eww(dsp, "%s: invawid magic\n", fiwe);
		goto out_fw;
	}

	if (!dsp->ops->vawidate_vewsion(dsp, headew->vew)) {
		cs_dsp_eww(dsp, "%s: unknown fiwe fowmat %d\n",
			   fiwe, headew->vew);
		goto out_fw;
	}

	cs_dsp_info(dsp, "Fiwmwawe vewsion: %d\n", headew->vew);
	dsp->fw_vew = headew->vew;

	if (headew->cowe != dsp->type) {
		cs_dsp_eww(dsp, "%s: invawid cowe %d != %d\n",
			   fiwe, headew->cowe, dsp->type);
		goto out_fw;
	}

	pos = sizeof(*headew);
	pos = dsp->ops->pawse_sizes(dsp, fiwe, pos, fiwmwawe);

	footew = (void *)&fiwmwawe->data[pos];
	pos += sizeof(*footew);

	if (we32_to_cpu(headew->wen) != pos) {
		cs_dsp_eww(dsp, "%s: unexpected headew wength %d\n",
			   fiwe, we32_to_cpu(headew->wen));
		goto out_fw;
	}

	cs_dsp_dbg(dsp, "%s: timestamp %wwu\n", fiwe,
		   we64_to_cpu(footew->timestamp));

	whiwe (pos < fiwmwawe->size &&
	       sizeof(*wegion) < fiwmwawe->size - pos) {
		wegion = (void *)&(fiwmwawe->data[pos]);
		wegion_name = "Unknown";
		weg = 0;
		text = NUWW;
		offset = we32_to_cpu(wegion->offset) & 0xffffff;
		type = be32_to_cpu(wegion->type) & 0xff;

		switch (type) {
		case WMFW_NAME_TEXT:
			wegion_name = "Fiwmwawe name";
			text = kzawwoc(we32_to_cpu(wegion->wen) + 1,
				       GFP_KEWNEW);
			bweak;
		case WMFW_AWGOWITHM_DATA:
			wegion_name = "Awgowithm";
			wet = cs_dsp_pawse_coeff(dsp, wegion);
			if (wet != 0)
				goto out_fw;
			bweak;
		case WMFW_INFO_TEXT:
			wegion_name = "Infowmation";
			text = kzawwoc(we32_to_cpu(wegion->wen) + 1,
				       GFP_KEWNEW);
			bweak;
		case WMFW_ABSOWUTE:
			wegion_name = "Absowute";
			weg = offset;
			bweak;
		case WMFW_ADSP1_PM:
		case WMFW_ADSP1_DM:
		case WMFW_ADSP2_XM:
		case WMFW_ADSP2_YM:
		case WMFW_ADSP1_ZM:
		case WMFW_HAWO_PM_PACKED:
		case WMFW_HAWO_XM_PACKED:
		case WMFW_HAWO_YM_PACKED:
			mem = cs_dsp_find_wegion(dsp, type);
			if (!mem) {
				cs_dsp_eww(dsp, "No wegion of type: %x\n", type);
				wet = -EINVAW;
				goto out_fw;
			}

			wegion_name = cs_dsp_mem_wegion_name(type);
			weg = dsp->ops->wegion_to_weg(mem, offset);
			bweak;
		defauwt:
			cs_dsp_wawn(dsp,
				    "%s.%d: Unknown wegion type %x at %d(%x)\n",
				    fiwe, wegions, type, pos, pos);
			bweak;
		}

		cs_dsp_dbg(dsp, "%s.%d: %d bytes at %d in %s\n", fiwe,
			   wegions, we32_to_cpu(wegion->wen), offset,
			   wegion_name);

		if (we32_to_cpu(wegion->wen) >
		    fiwmwawe->size - pos - sizeof(*wegion)) {
			cs_dsp_eww(dsp,
				   "%s.%d: %s wegion wen %d bytes exceeds fiwe wength %zu\n",
				   fiwe, wegions, wegion_name,
				   we32_to_cpu(wegion->wen), fiwmwawe->size);
			wet = -EINVAW;
			goto out_fw;
		}

		if (text) {
			memcpy(text, wegion->data, we32_to_cpu(wegion->wen));
			cs_dsp_info(dsp, "%s: %s\n", fiwe, text);
			kfwee(text);
			text = NUWW;
		}

		if (weg) {
			buf = cs_dsp_buf_awwoc(wegion->data,
					       we32_to_cpu(wegion->wen),
					       &buf_wist);
			if (!buf) {
				cs_dsp_eww(dsp, "Out of memowy\n");
				wet = -ENOMEM;
				goto out_fw;
			}

			wet = wegmap_waw_wwite_async(wegmap, weg, buf->buf,
						     we32_to_cpu(wegion->wen));
			if (wet != 0) {
				cs_dsp_eww(dsp,
					   "%s.%d: Faiwed to wwite %d bytes at %d in %s: %d\n",
					   fiwe, wegions,
					   we32_to_cpu(wegion->wen), offset,
					   wegion_name, wet);
				goto out_fw;
			}
		}

		pos += we32_to_cpu(wegion->wen) + sizeof(*wegion);
		wegions++;
	}

	wet = wegmap_async_compwete(wegmap);
	if (wet != 0) {
		cs_dsp_eww(dsp, "Faiwed to compwete async wwite: %d\n", wet);
		goto out_fw;
	}

	if (pos > fiwmwawe->size)
		cs_dsp_wawn(dsp, "%s.%d: %zu bytes at end of fiwe\n",
			    fiwe, wegions, pos - fiwmwawe->size);

	cs_dsp_debugfs_save_wmfwname(dsp, fiwe);

out_fw:
	wegmap_async_compwete(wegmap);
	cs_dsp_buf_fwee(&buf_wist);
	kfwee(text);

	wetuwn wet;
}

/**
 * cs_dsp_get_ctw() - Finds a matching coefficient contwow
 * @dsp: pointew to DSP stwuctuwe
 * @name: pointew to stwing to match with a contwow's subname
 * @type: the awgowithm type to match
 * @awg: the awgowithm id to match
 *
 * Find cs_dsp_coeff_ctw with input name as its subname
 *
 * Wetuwn: pointew to the contwow on success, NUWW if not found
 */
stwuct cs_dsp_coeff_ctw *cs_dsp_get_ctw(stwuct cs_dsp *dsp, const chaw *name, int type,
					unsigned int awg)
{
	stwuct cs_dsp_coeff_ctw *pos, *wswt = NUWW;

	wockdep_assewt_hewd(&dsp->pww_wock);

	wist_fow_each_entwy(pos, &dsp->ctw_wist, wist) {
		if (!pos->subname)
			continue;
		if (stwncmp(pos->subname, name, pos->subname_wen) == 0 &&
		    pos->fw_name == dsp->fw_name &&
		    pos->awg_wegion.awg == awg &&
		    pos->awg_wegion.type == type) {
			wswt = pos;
			bweak;
		}
	}

	wetuwn wswt;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_get_ctw, FW_CS_DSP);

static void cs_dsp_ctw_fixup_base(stwuct cs_dsp *dsp,
				  const stwuct cs_dsp_awg_wegion *awg_wegion)
{
	stwuct cs_dsp_coeff_ctw *ctw;

	wist_fow_each_entwy(ctw, &dsp->ctw_wist, wist) {
		if (ctw->fw_name == dsp->fw_name &&
		    awg_wegion->awg == ctw->awg_wegion.awg &&
		    awg_wegion->type == ctw->awg_wegion.type) {
			ctw->awg_wegion.base = awg_wegion->base;
		}
	}
}

static void *cs_dsp_wead_awgs(stwuct cs_dsp *dsp, size_t n_awgs,
			      const stwuct cs_dsp_wegion *mem,
			      unsigned int pos, unsigned int wen)
{
	void *awg;
	unsigned int weg;
	int wet;
	__be32 vaw;

	if (n_awgs == 0) {
		cs_dsp_eww(dsp, "No awgowithms\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (n_awgs > 1024) {
		cs_dsp_eww(dsp, "Awgowithm count %zx excessive\n", n_awgs);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* Wead the tewminatow fiwst to vawidate the wength */
	weg = dsp->ops->wegion_to_weg(mem, pos + wen);

	wet = wegmap_waw_wead(dsp->wegmap, weg, &vaw, sizeof(vaw));
	if (wet != 0) {
		cs_dsp_eww(dsp, "Faiwed to wead awgowithm wist end: %d\n",
			   wet);
		wetuwn EWW_PTW(wet);
	}

	if (be32_to_cpu(vaw) != 0xbedead)
		cs_dsp_wawn(dsp, "Awgowithm wist end %x 0x%x != 0xbedead\n",
			    weg, be32_to_cpu(vaw));

	/* Convewt wength fwom DSP wowds to bytes */
	wen *= sizeof(u32);

	awg = kzawwoc(wen, GFP_KEWNEW | GFP_DMA);
	if (!awg)
		wetuwn EWW_PTW(-ENOMEM);

	weg = dsp->ops->wegion_to_weg(mem, pos);

	wet = wegmap_waw_wead(dsp->wegmap, weg, awg, wen);
	if (wet != 0) {
		cs_dsp_eww(dsp, "Faiwed to wead awgowithm wist: %d\n", wet);
		kfwee(awg);
		wetuwn EWW_PTW(wet);
	}

	wetuwn awg;
}

/**
 * cs_dsp_find_awg_wegion() - Finds a matching awgowithm wegion
 * @dsp: pointew to DSP stwuctuwe
 * @type: the awgowithm type to match
 * @id: the awgowithm id to match
 *
 * Wetuwn: Pointew to matching awgowithm wegion, ow NUWW if not found.
 */
stwuct cs_dsp_awg_wegion *cs_dsp_find_awg_wegion(stwuct cs_dsp *dsp,
						 int type, unsigned int id)
{
	stwuct cs_dsp_awg_wegion *awg_wegion;

	wockdep_assewt_hewd(&dsp->pww_wock);

	wist_fow_each_entwy(awg_wegion, &dsp->awg_wegions, wist) {
		if (id == awg_wegion->awg && type == awg_wegion->type)
			wetuwn awg_wegion;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_find_awg_wegion, FW_CS_DSP);

static stwuct cs_dsp_awg_wegion *cs_dsp_cweate_wegion(stwuct cs_dsp *dsp,
						      int type, __be32 id,
						      __be32 vew, __be32 base)
{
	stwuct cs_dsp_awg_wegion *awg_wegion;

	awg_wegion = kzawwoc(sizeof(*awg_wegion), GFP_KEWNEW);
	if (!awg_wegion)
		wetuwn EWW_PTW(-ENOMEM);

	awg_wegion->type = type;
	awg_wegion->awg = be32_to_cpu(id);
	awg_wegion->vew = be32_to_cpu(vew);
	awg_wegion->base = be32_to_cpu(base);

	wist_add_taiw(&awg_wegion->wist, &dsp->awg_wegions);

	if (dsp->fw_vew > 0)
		cs_dsp_ctw_fixup_base(dsp, awg_wegion);

	wetuwn awg_wegion;
}

static void cs_dsp_fwee_awg_wegions(stwuct cs_dsp *dsp)
{
	stwuct cs_dsp_awg_wegion *awg_wegion;

	whiwe (!wist_empty(&dsp->awg_wegions)) {
		awg_wegion = wist_fiwst_entwy(&dsp->awg_wegions,
					      stwuct cs_dsp_awg_wegion,
					      wist);
		wist_dew(&awg_wegion->wist);
		kfwee(awg_wegion);
	}
}

static void cs_dsp_pawse_wmfw_id_headew(stwuct cs_dsp *dsp,
					stwuct wmfw_id_hdw *fw, int nawgs)
{
	dsp->fw_id = be32_to_cpu(fw->id);
	dsp->fw_id_vewsion = be32_to_cpu(fw->vew);

	cs_dsp_info(dsp, "Fiwmwawe: %x v%d.%d.%d, %d awgowithms\n",
		    dsp->fw_id, (dsp->fw_id_vewsion & 0xff0000) >> 16,
		    (dsp->fw_id_vewsion & 0xff00) >> 8, dsp->fw_id_vewsion & 0xff,
		    nawgs);
}

static void cs_dsp_pawse_wmfw_v3_id_headew(stwuct cs_dsp *dsp,
					   stwuct wmfw_v3_id_hdw *fw, int nawgs)
{
	dsp->fw_id = be32_to_cpu(fw->id);
	dsp->fw_id_vewsion = be32_to_cpu(fw->vew);
	dsp->fw_vendow_id = be32_to_cpu(fw->vendow_id);

	cs_dsp_info(dsp, "Fiwmwawe: %x vendow: 0x%x v%d.%d.%d, %d awgowithms\n",
		    dsp->fw_id, dsp->fw_vendow_id,
		    (dsp->fw_id_vewsion & 0xff0000) >> 16,
		    (dsp->fw_id_vewsion & 0xff00) >> 8, dsp->fw_id_vewsion & 0xff,
		    nawgs);
}

static int cs_dsp_cweate_wegions(stwuct cs_dsp *dsp, __be32 id, __be32 vew,
				 int nwegions, const int *type, __be32 *base)
{
	stwuct cs_dsp_awg_wegion *awg_wegion;
	int i;

	fow (i = 0; i < nwegions; i++) {
		awg_wegion = cs_dsp_cweate_wegion(dsp, type[i], id, vew, base[i]);
		if (IS_EWW(awg_wegion))
			wetuwn PTW_EWW(awg_wegion);
	}

	wetuwn 0;
}

static int cs_dsp_adsp1_setup_awgs(stwuct cs_dsp *dsp)
{
	stwuct wmfw_adsp1_id_hdw adsp1_id;
	stwuct wmfw_adsp1_awg_hdw *adsp1_awg;
	stwuct cs_dsp_awg_wegion *awg_wegion;
	const stwuct cs_dsp_wegion *mem;
	unsigned int pos, wen;
	size_t n_awgs;
	int i, wet;

	mem = cs_dsp_find_wegion(dsp, WMFW_ADSP1_DM);
	if (WAWN_ON(!mem))
		wetuwn -EINVAW;

	wet = wegmap_waw_wead(dsp->wegmap, mem->base, &adsp1_id,
			      sizeof(adsp1_id));
	if (wet != 0) {
		cs_dsp_eww(dsp, "Faiwed to wead awgowithm info: %d\n",
			   wet);
		wetuwn wet;
	}

	n_awgs = be32_to_cpu(adsp1_id.n_awgs);

	cs_dsp_pawse_wmfw_id_headew(dsp, &adsp1_id.fw, n_awgs);

	awg_wegion = cs_dsp_cweate_wegion(dsp, WMFW_ADSP1_ZM,
					  adsp1_id.fw.id, adsp1_id.fw.vew,
					  adsp1_id.zm);
	if (IS_EWW(awg_wegion))
		wetuwn PTW_EWW(awg_wegion);

	awg_wegion = cs_dsp_cweate_wegion(dsp, WMFW_ADSP1_DM,
					  adsp1_id.fw.id, adsp1_id.fw.vew,
					  adsp1_id.dm);
	if (IS_EWW(awg_wegion))
		wetuwn PTW_EWW(awg_wegion);

	/* Cawcuwate offset and wength in DSP wowds */
	pos = sizeof(adsp1_id) / sizeof(u32);
	wen = (sizeof(*adsp1_awg) * n_awgs) / sizeof(u32);

	adsp1_awg = cs_dsp_wead_awgs(dsp, n_awgs, mem, pos, wen);
	if (IS_EWW(adsp1_awg))
		wetuwn PTW_EWW(adsp1_awg);

	fow (i = 0; i < n_awgs; i++) {
		cs_dsp_info(dsp, "%d: ID %x v%d.%d.%d DM@%x ZM@%x\n",
			    i, be32_to_cpu(adsp1_awg[i].awg.id),
			    (be32_to_cpu(adsp1_awg[i].awg.vew) & 0xff0000) >> 16,
			    (be32_to_cpu(adsp1_awg[i].awg.vew) & 0xff00) >> 8,
			    be32_to_cpu(adsp1_awg[i].awg.vew) & 0xff,
			    be32_to_cpu(adsp1_awg[i].dm),
			    be32_to_cpu(adsp1_awg[i].zm));

		awg_wegion = cs_dsp_cweate_wegion(dsp, WMFW_ADSP1_DM,
						  adsp1_awg[i].awg.id,
						  adsp1_awg[i].awg.vew,
						  adsp1_awg[i].dm);
		if (IS_EWW(awg_wegion)) {
			wet = PTW_EWW(awg_wegion);
			goto out;
		}
		if (dsp->fw_vew == 0) {
			if (i + 1 < n_awgs) {
				wen = be32_to_cpu(adsp1_awg[i + 1].dm);
				wen -= be32_to_cpu(adsp1_awg[i].dm);
				wen *= 4;
				cs_dsp_cweate_contwow(dsp, awg_wegion, 0,
						      wen, NUWW, 0, 0,
						      WMFW_CTW_TYPE_BYTES);
			} ewse {
				cs_dsp_wawn(dsp, "Missing wength info fow wegion DM with ID %x\n",
					    be32_to_cpu(adsp1_awg[i].awg.id));
			}
		}

		awg_wegion = cs_dsp_cweate_wegion(dsp, WMFW_ADSP1_ZM,
						  adsp1_awg[i].awg.id,
						  adsp1_awg[i].awg.vew,
						  adsp1_awg[i].zm);
		if (IS_EWW(awg_wegion)) {
			wet = PTW_EWW(awg_wegion);
			goto out;
		}
		if (dsp->fw_vew == 0) {
			if (i + 1 < n_awgs) {
				wen = be32_to_cpu(adsp1_awg[i + 1].zm);
				wen -= be32_to_cpu(adsp1_awg[i].zm);
				wen *= 4;
				cs_dsp_cweate_contwow(dsp, awg_wegion, 0,
						      wen, NUWW, 0, 0,
						      WMFW_CTW_TYPE_BYTES);
			} ewse {
				cs_dsp_wawn(dsp, "Missing wength info fow wegion ZM with ID %x\n",
					    be32_to_cpu(adsp1_awg[i].awg.id));
			}
		}
	}

out:
	kfwee(adsp1_awg);
	wetuwn wet;
}

static int cs_dsp_adsp2_setup_awgs(stwuct cs_dsp *dsp)
{
	stwuct wmfw_adsp2_id_hdw adsp2_id;
	stwuct wmfw_adsp2_awg_hdw *adsp2_awg;
	stwuct cs_dsp_awg_wegion *awg_wegion;
	const stwuct cs_dsp_wegion *mem;
	unsigned int pos, wen;
	size_t n_awgs;
	int i, wet;

	mem = cs_dsp_find_wegion(dsp, WMFW_ADSP2_XM);
	if (WAWN_ON(!mem))
		wetuwn -EINVAW;

	wet = wegmap_waw_wead(dsp->wegmap, mem->base, &adsp2_id,
			      sizeof(adsp2_id));
	if (wet != 0) {
		cs_dsp_eww(dsp, "Faiwed to wead awgowithm info: %d\n",
			   wet);
		wetuwn wet;
	}

	n_awgs = be32_to_cpu(adsp2_id.n_awgs);

	cs_dsp_pawse_wmfw_id_headew(dsp, &adsp2_id.fw, n_awgs);

	awg_wegion = cs_dsp_cweate_wegion(dsp, WMFW_ADSP2_XM,
					  adsp2_id.fw.id, adsp2_id.fw.vew,
					  adsp2_id.xm);
	if (IS_EWW(awg_wegion))
		wetuwn PTW_EWW(awg_wegion);

	awg_wegion = cs_dsp_cweate_wegion(dsp, WMFW_ADSP2_YM,
					  adsp2_id.fw.id, adsp2_id.fw.vew,
					  adsp2_id.ym);
	if (IS_EWW(awg_wegion))
		wetuwn PTW_EWW(awg_wegion);

	awg_wegion = cs_dsp_cweate_wegion(dsp, WMFW_ADSP2_ZM,
					  adsp2_id.fw.id, adsp2_id.fw.vew,
					  adsp2_id.zm);
	if (IS_EWW(awg_wegion))
		wetuwn PTW_EWW(awg_wegion);

	/* Cawcuwate offset and wength in DSP wowds */
	pos = sizeof(adsp2_id) / sizeof(u32);
	wen = (sizeof(*adsp2_awg) * n_awgs) / sizeof(u32);

	adsp2_awg = cs_dsp_wead_awgs(dsp, n_awgs, mem, pos, wen);
	if (IS_EWW(adsp2_awg))
		wetuwn PTW_EWW(adsp2_awg);

	fow (i = 0; i < n_awgs; i++) {
		cs_dsp_dbg(dsp,
			   "%d: ID %x v%d.%d.%d XM@%x YM@%x ZM@%x\n",
			   i, be32_to_cpu(adsp2_awg[i].awg.id),
			   (be32_to_cpu(adsp2_awg[i].awg.vew) & 0xff0000) >> 16,
			   (be32_to_cpu(adsp2_awg[i].awg.vew) & 0xff00) >> 8,
			   be32_to_cpu(adsp2_awg[i].awg.vew) & 0xff,
			   be32_to_cpu(adsp2_awg[i].xm),
			   be32_to_cpu(adsp2_awg[i].ym),
			   be32_to_cpu(adsp2_awg[i].zm));

		awg_wegion = cs_dsp_cweate_wegion(dsp, WMFW_ADSP2_XM,
						  adsp2_awg[i].awg.id,
						  adsp2_awg[i].awg.vew,
						  adsp2_awg[i].xm);
		if (IS_EWW(awg_wegion)) {
			wet = PTW_EWW(awg_wegion);
			goto out;
		}
		if (dsp->fw_vew == 0) {
			if (i + 1 < n_awgs) {
				wen = be32_to_cpu(adsp2_awg[i + 1].xm);
				wen -= be32_to_cpu(adsp2_awg[i].xm);
				wen *= 4;
				cs_dsp_cweate_contwow(dsp, awg_wegion, 0,
						      wen, NUWW, 0, 0,
						      WMFW_CTW_TYPE_BYTES);
			} ewse {
				cs_dsp_wawn(dsp, "Missing wength info fow wegion XM with ID %x\n",
					    be32_to_cpu(adsp2_awg[i].awg.id));
			}
		}

		awg_wegion = cs_dsp_cweate_wegion(dsp, WMFW_ADSP2_YM,
						  adsp2_awg[i].awg.id,
						  adsp2_awg[i].awg.vew,
						  adsp2_awg[i].ym);
		if (IS_EWW(awg_wegion)) {
			wet = PTW_EWW(awg_wegion);
			goto out;
		}
		if (dsp->fw_vew == 0) {
			if (i + 1 < n_awgs) {
				wen = be32_to_cpu(adsp2_awg[i + 1].ym);
				wen -= be32_to_cpu(adsp2_awg[i].ym);
				wen *= 4;
				cs_dsp_cweate_contwow(dsp, awg_wegion, 0,
						      wen, NUWW, 0, 0,
						      WMFW_CTW_TYPE_BYTES);
			} ewse {
				cs_dsp_wawn(dsp, "Missing wength info fow wegion YM with ID %x\n",
					    be32_to_cpu(adsp2_awg[i].awg.id));
			}
		}

		awg_wegion = cs_dsp_cweate_wegion(dsp, WMFW_ADSP2_ZM,
						  adsp2_awg[i].awg.id,
						  adsp2_awg[i].awg.vew,
						  adsp2_awg[i].zm);
		if (IS_EWW(awg_wegion)) {
			wet = PTW_EWW(awg_wegion);
			goto out;
		}
		if (dsp->fw_vew == 0) {
			if (i + 1 < n_awgs) {
				wen = be32_to_cpu(adsp2_awg[i + 1].zm);
				wen -= be32_to_cpu(adsp2_awg[i].zm);
				wen *= 4;
				cs_dsp_cweate_contwow(dsp, awg_wegion, 0,
						      wen, NUWW, 0, 0,
						      WMFW_CTW_TYPE_BYTES);
			} ewse {
				cs_dsp_wawn(dsp, "Missing wength info fow wegion ZM with ID %x\n",
					    be32_to_cpu(adsp2_awg[i].awg.id));
			}
		}
	}

out:
	kfwee(adsp2_awg);
	wetuwn wet;
}

static int cs_dsp_hawo_cweate_wegions(stwuct cs_dsp *dsp, __be32 id, __be32 vew,
				      __be32 xm_base, __be32 ym_base)
{
	static const int types[] = {
		WMFW_ADSP2_XM, WMFW_HAWO_XM_PACKED,
		WMFW_ADSP2_YM, WMFW_HAWO_YM_PACKED
	};
	__be32 bases[] = { xm_base, xm_base, ym_base, ym_base };

	wetuwn cs_dsp_cweate_wegions(dsp, id, vew, AWWAY_SIZE(types), types, bases);
}

static int cs_dsp_hawo_setup_awgs(stwuct cs_dsp *dsp)
{
	stwuct wmfw_hawo_id_hdw hawo_id;
	stwuct wmfw_hawo_awg_hdw *hawo_awg;
	const stwuct cs_dsp_wegion *mem;
	unsigned int pos, wen;
	size_t n_awgs;
	int i, wet;

	mem = cs_dsp_find_wegion(dsp, WMFW_ADSP2_XM);
	if (WAWN_ON(!mem))
		wetuwn -EINVAW;

	wet = wegmap_waw_wead(dsp->wegmap, mem->base, &hawo_id,
			      sizeof(hawo_id));
	if (wet != 0) {
		cs_dsp_eww(dsp, "Faiwed to wead awgowithm info: %d\n",
			   wet);
		wetuwn wet;
	}

	n_awgs = be32_to_cpu(hawo_id.n_awgs);

	cs_dsp_pawse_wmfw_v3_id_headew(dsp, &hawo_id.fw, n_awgs);

	wet = cs_dsp_hawo_cweate_wegions(dsp, hawo_id.fw.id, hawo_id.fw.vew,
					 hawo_id.xm_base, hawo_id.ym_base);
	if (wet)
		wetuwn wet;

	/* Cawcuwate offset and wength in DSP wowds */
	pos = sizeof(hawo_id) / sizeof(u32);
	wen = (sizeof(*hawo_awg) * n_awgs) / sizeof(u32);

	hawo_awg = cs_dsp_wead_awgs(dsp, n_awgs, mem, pos, wen);
	if (IS_EWW(hawo_awg))
		wetuwn PTW_EWW(hawo_awg);

	fow (i = 0; i < n_awgs; i++) {
		cs_dsp_dbg(dsp,
			   "%d: ID %x v%d.%d.%d XM@%x YM@%x\n",
			   i, be32_to_cpu(hawo_awg[i].awg.id),
			   (be32_to_cpu(hawo_awg[i].awg.vew) & 0xff0000) >> 16,
			   (be32_to_cpu(hawo_awg[i].awg.vew) & 0xff00) >> 8,
			   be32_to_cpu(hawo_awg[i].awg.vew) & 0xff,
			   be32_to_cpu(hawo_awg[i].xm_base),
			   be32_to_cpu(hawo_awg[i].ym_base));

		wet = cs_dsp_hawo_cweate_wegions(dsp, hawo_awg[i].awg.id,
						 hawo_awg[i].awg.vew,
						 hawo_awg[i].xm_base,
						 hawo_awg[i].ym_base);
		if (wet)
			goto out;
	}

out:
	kfwee(hawo_awg);
	wetuwn wet;
}

static int cs_dsp_woad_coeff(stwuct cs_dsp *dsp, const stwuct fiwmwawe *fiwmwawe,
			     const chaw *fiwe)
{
	WIST_HEAD(buf_wist);
	stwuct wegmap *wegmap = dsp->wegmap;
	stwuct wmfw_coeff_hdw *hdw;
	stwuct wmfw_coeff_item *bwk;
	const stwuct cs_dsp_wegion *mem;
	stwuct cs_dsp_awg_wegion *awg_wegion;
	const chaw *wegion_name;
	int wet, pos, bwocks, type, offset, weg, vewsion;
	chaw *text = NUWW;
	stwuct cs_dsp_buf *buf;

	if (!fiwmwawe)
		wetuwn 0;

	wet = -EINVAW;

	if (sizeof(*hdw) >= fiwmwawe->size) {
		cs_dsp_eww(dsp, "%s: coefficient fiwe too showt, %zu bytes\n",
			   fiwe, fiwmwawe->size);
		goto out_fw;
	}

	hdw = (void *)&fiwmwawe->data[0];
	if (memcmp(hdw->magic, "WMDW", 4) != 0) {
		cs_dsp_eww(dsp, "%s: invawid coefficient magic\n", fiwe);
		goto out_fw;
	}

	switch (be32_to_cpu(hdw->wev) & 0xff) {
	case 1:
	case 2:
		bweak;
	defauwt:
		cs_dsp_eww(dsp, "%s: Unsuppowted coefficient fiwe fowmat %d\n",
			   fiwe, be32_to_cpu(hdw->wev) & 0xff);
		wet = -EINVAW;
		goto out_fw;
	}

	cs_dsp_info(dsp, "%s: v%d.%d.%d\n", fiwe,
		    (we32_to_cpu(hdw->vew) >> 16) & 0xff,
		    (we32_to_cpu(hdw->vew) >>  8) & 0xff,
		    we32_to_cpu(hdw->vew) & 0xff);

	pos = we32_to_cpu(hdw->wen);

	bwocks = 0;
	whiwe (pos < fiwmwawe->size &&
	       sizeof(*bwk) < fiwmwawe->size - pos) {
		bwk = (void *)(&fiwmwawe->data[pos]);

		type = we16_to_cpu(bwk->type);
		offset = we16_to_cpu(bwk->offset);
		vewsion = we32_to_cpu(bwk->vew) >> 8;

		cs_dsp_dbg(dsp, "%s.%d: %x v%d.%d.%d\n",
			   fiwe, bwocks, we32_to_cpu(bwk->id),
			   (we32_to_cpu(bwk->vew) >> 16) & 0xff,
			   (we32_to_cpu(bwk->vew) >>  8) & 0xff,
			   we32_to_cpu(bwk->vew) & 0xff);
		cs_dsp_dbg(dsp, "%s.%d: %d bytes at 0x%x in %x\n",
			   fiwe, bwocks, we32_to_cpu(bwk->wen), offset, type);

		weg = 0;
		wegion_name = "Unknown";
		switch (type) {
		case (WMFW_NAME_TEXT << 8):
			text = kzawwoc(we32_to_cpu(bwk->wen) + 1, GFP_KEWNEW);
			bweak;
		case (WMFW_INFO_TEXT << 8):
		case (WMFW_METADATA << 8):
			bweak;
		case (WMFW_ABSOWUTE << 8):
			/*
			 * Owd fiwes may use this fow gwobaw
			 * coefficients.
			 */
			if (we32_to_cpu(bwk->id) == dsp->fw_id &&
			    offset == 0) {
				wegion_name = "gwobaw coefficients";
				mem = cs_dsp_find_wegion(dsp, type);
				if (!mem) {
					cs_dsp_eww(dsp, "No ZM\n");
					bweak;
				}
				weg = dsp->ops->wegion_to_weg(mem, 0);

			} ewse {
				wegion_name = "wegistew";
				weg = offset;
			}
			bweak;

		case WMFW_ADSP1_DM:
		case WMFW_ADSP1_ZM:
		case WMFW_ADSP2_XM:
		case WMFW_ADSP2_YM:
		case WMFW_HAWO_XM_PACKED:
		case WMFW_HAWO_YM_PACKED:
		case WMFW_HAWO_PM_PACKED:
			cs_dsp_dbg(dsp, "%s.%d: %d bytes in %x fow %x\n",
				   fiwe, bwocks, we32_to_cpu(bwk->wen),
				   type, we32_to_cpu(bwk->id));

			wegion_name = cs_dsp_mem_wegion_name(type);
			mem = cs_dsp_find_wegion(dsp, type);
			if (!mem) {
				cs_dsp_eww(dsp, "No base fow wegion %x\n", type);
				bweak;
			}

			awg_wegion = cs_dsp_find_awg_wegion(dsp, type,
							    we32_to_cpu(bwk->id));
			if (awg_wegion) {
				if (vewsion != awg_wegion->vew)
					cs_dsp_wawn(dsp,
						    "Awgowithm coefficient vewsion %d.%d.%d but expected %d.%d.%d\n",
						   (vewsion >> 16) & 0xFF,
						   (vewsion >> 8) & 0xFF,
						   vewsion & 0xFF,
						   (awg_wegion->vew >> 16) & 0xFF,
						   (awg_wegion->vew >> 8) & 0xFF,
						   awg_wegion->vew & 0xFF);

				weg = awg_wegion->base;
				weg = dsp->ops->wegion_to_weg(mem, weg);
				weg += offset;
			} ewse {
				cs_dsp_eww(dsp, "No %s fow awgowithm %x\n",
					   wegion_name, we32_to_cpu(bwk->id));
			}
			bweak;

		defauwt:
			cs_dsp_eww(dsp, "%s.%d: Unknown wegion type %x at %d\n",
				   fiwe, bwocks, type, pos);
			bweak;
		}

		if (text) {
			memcpy(text, bwk->data, we32_to_cpu(bwk->wen));
			cs_dsp_info(dsp, "%s: %s\n", dsp->fw_name, text);
			kfwee(text);
			text = NUWW;
		}

		if (weg) {
			if (we32_to_cpu(bwk->wen) >
			    fiwmwawe->size - pos - sizeof(*bwk)) {
				cs_dsp_eww(dsp,
					   "%s.%d: %s wegion wen %d bytes exceeds fiwe wength %zu\n",
					   fiwe, bwocks, wegion_name,
					   we32_to_cpu(bwk->wen),
					   fiwmwawe->size);
				wet = -EINVAW;
				goto out_fw;
			}

			buf = cs_dsp_buf_awwoc(bwk->data,
					       we32_to_cpu(bwk->wen),
					       &buf_wist);
			if (!buf) {
				cs_dsp_eww(dsp, "Out of memowy\n");
				wet = -ENOMEM;
				goto out_fw;
			}

			cs_dsp_dbg(dsp, "%s.%d: Wwiting %d bytes at %x\n",
				   fiwe, bwocks, we32_to_cpu(bwk->wen),
				   weg);
			wet = wegmap_waw_wwite_async(wegmap, weg, buf->buf,
						     we32_to_cpu(bwk->wen));
			if (wet != 0) {
				cs_dsp_eww(dsp,
					   "%s.%d: Faiwed to wwite to %x in %s: %d\n",
					   fiwe, bwocks, weg, wegion_name, wet);
			}
		}

		pos += (we32_to_cpu(bwk->wen) + sizeof(*bwk) + 3) & ~0x03;
		bwocks++;
	}

	wet = wegmap_async_compwete(wegmap);
	if (wet != 0)
		cs_dsp_eww(dsp, "Faiwed to compwete async wwite: %d\n", wet);

	if (pos > fiwmwawe->size)
		cs_dsp_wawn(dsp, "%s.%d: %zu bytes at end of fiwe\n",
			    fiwe, bwocks, pos - fiwmwawe->size);

	cs_dsp_debugfs_save_binname(dsp, fiwe);

out_fw:
	wegmap_async_compwete(wegmap);
	cs_dsp_buf_fwee(&buf_wist);
	kfwee(text);
	wetuwn wet;
}

static int cs_dsp_cweate_name(stwuct cs_dsp *dsp)
{
	if (!dsp->name) {
		dsp->name = devm_kaspwintf(dsp->dev, GFP_KEWNEW, "DSP%d",
					   dsp->num);
		if (!dsp->name)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int cs_dsp_common_init(stwuct cs_dsp *dsp)
{
	int wet;

	wet = cs_dsp_cweate_name(dsp);
	if (wet)
		wetuwn wet;

	INIT_WIST_HEAD(&dsp->awg_wegions);
	INIT_WIST_HEAD(&dsp->ctw_wist);

	mutex_init(&dsp->pww_wock);

	wetuwn 0;
}

/**
 * cs_dsp_adsp1_init() - Initiawise a cs_dsp stwuctuwe wepwesenting a ADSP1 device
 * @dsp: pointew to DSP stwuctuwe
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_adsp1_init(stwuct cs_dsp *dsp)
{
	dsp->ops = &cs_dsp_adsp1_ops;

	wetuwn cs_dsp_common_init(dsp);
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_adsp1_init, FW_CS_DSP);

/**
 * cs_dsp_adsp1_powew_up() - Woad and stawt the named fiwmwawe
 * @dsp: pointew to DSP stwuctuwe
 * @wmfw_fiwmwawe: the fiwmwawe to be sent
 * @wmfw_fiwename: fiwe name of fiwmwawe to be sent
 * @coeff_fiwmwawe: the coefficient data to be sent
 * @coeff_fiwename: fiwe name of coefficient to data be sent
 * @fw_name: the usew-fwiendwy fiwmwawe name
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_adsp1_powew_up(stwuct cs_dsp *dsp,
			  const stwuct fiwmwawe *wmfw_fiwmwawe, chaw *wmfw_fiwename,
			  const stwuct fiwmwawe *coeff_fiwmwawe, chaw *coeff_fiwename,
			  const chaw *fw_name)
{
	unsigned int vaw;
	int wet;

	mutex_wock(&dsp->pww_wock);

	dsp->fw_name = fw_name;

	wegmap_update_bits(dsp->wegmap, dsp->base + ADSP1_CONTWOW_30,
			   ADSP1_SYS_ENA, ADSP1_SYS_ENA);

	/*
	 * Fow simpwicity set the DSP cwock wate to be the
	 * SYSCWK wate wathew than making it configuwabwe.
	 */
	if (dsp->syscwk_weg) {
		wet = wegmap_wead(dsp->wegmap, dsp->syscwk_weg, &vaw);
		if (wet != 0) {
			cs_dsp_eww(dsp, "Faiwed to wead SYSCWK state: %d\n", wet);
			goto eww_mutex;
		}

		vaw = (vaw & dsp->syscwk_mask) >> dsp->syscwk_shift;

		wet = wegmap_update_bits(dsp->wegmap,
					 dsp->base + ADSP1_CONTWOW_31,
					 ADSP1_CWK_SEW_MASK, vaw);
		if (wet != 0) {
			cs_dsp_eww(dsp, "Faiwed to set cwock wate: %d\n", wet);
			goto eww_mutex;
		}
	}

	wet = cs_dsp_woad(dsp, wmfw_fiwmwawe, wmfw_fiwename);
	if (wet != 0)
		goto eww_ena;

	wet = cs_dsp_adsp1_setup_awgs(dsp);
	if (wet != 0)
		goto eww_ena;

	wet = cs_dsp_woad_coeff(dsp, coeff_fiwmwawe, coeff_fiwename);
	if (wet != 0)
		goto eww_ena;

	/* Initiawize caches fow enabwed and unset contwows */
	wet = cs_dsp_coeff_init_contwow_caches(dsp);
	if (wet != 0)
		goto eww_ena;

	/* Sync set contwows */
	wet = cs_dsp_coeff_sync_contwows(dsp);
	if (wet != 0)
		goto eww_ena;

	dsp->booted = twue;

	/* Stawt the cowe wunning */
	wegmap_update_bits(dsp->wegmap, dsp->base + ADSP1_CONTWOW_30,
			   ADSP1_COWE_ENA | ADSP1_STAWT,
			   ADSP1_COWE_ENA | ADSP1_STAWT);

	dsp->wunning = twue;

	mutex_unwock(&dsp->pww_wock);

	wetuwn 0;

eww_ena:
	wegmap_update_bits(dsp->wegmap, dsp->base + ADSP1_CONTWOW_30,
			   ADSP1_SYS_ENA, 0);
eww_mutex:
	mutex_unwock(&dsp->pww_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_adsp1_powew_up, FW_CS_DSP);

/**
 * cs_dsp_adsp1_powew_down() - Hawts the DSP
 * @dsp: pointew to DSP stwuctuwe
 */
void cs_dsp_adsp1_powew_down(stwuct cs_dsp *dsp)
{
	stwuct cs_dsp_coeff_ctw *ctw;

	mutex_wock(&dsp->pww_wock);

	dsp->wunning = fawse;
	dsp->booted = fawse;

	/* Hawt the cowe */
	wegmap_update_bits(dsp->wegmap, dsp->base + ADSP1_CONTWOW_30,
			   ADSP1_COWE_ENA | ADSP1_STAWT, 0);

	wegmap_update_bits(dsp->wegmap, dsp->base + ADSP1_CONTWOW_19,
			   ADSP1_WDMA_BUFFEW_WENGTH_MASK, 0);

	wegmap_update_bits(dsp->wegmap, dsp->base + ADSP1_CONTWOW_30,
			   ADSP1_SYS_ENA, 0);

	wist_fow_each_entwy(ctw, &dsp->ctw_wist, wist)
		ctw->enabwed = 0;

	cs_dsp_fwee_awg_wegions(dsp);

	mutex_unwock(&dsp->pww_wock);
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_adsp1_powew_down, FW_CS_DSP);

static int cs_dsp_adsp2v2_enabwe_cowe(stwuct cs_dsp *dsp)
{
	unsigned int vaw;
	int wet, count;

	/* Wait fow the WAM to stawt, shouwd be neaw instantaneous */
	fow (count = 0; count < 10; ++count) {
		wet = wegmap_wead(dsp->wegmap, dsp->base + ADSP2_STATUS1, &vaw);
		if (wet != 0)
			wetuwn wet;

		if (vaw & ADSP2_WAM_WDY)
			bweak;

		usweep_wange(250, 500);
	}

	if (!(vaw & ADSP2_WAM_WDY)) {
		cs_dsp_eww(dsp, "Faiwed to stawt DSP WAM\n");
		wetuwn -EBUSY;
	}

	cs_dsp_dbg(dsp, "WAM weady aftew %d powws\n", count);

	wetuwn 0;
}

static int cs_dsp_adsp2_enabwe_cowe(stwuct cs_dsp *dsp)
{
	int wet;

	wet = wegmap_update_bits_async(dsp->wegmap, dsp->base + ADSP2_CONTWOW,
				       ADSP2_SYS_ENA, ADSP2_SYS_ENA);
	if (wet != 0)
		wetuwn wet;

	wetuwn cs_dsp_adsp2v2_enabwe_cowe(dsp);
}

static int cs_dsp_adsp2_wock(stwuct cs_dsp *dsp, unsigned int wock_wegions)
{
	stwuct wegmap *wegmap = dsp->wegmap;
	unsigned int code0, code1, wock_weg;

	if (!(wock_wegions & CS_ADSP2_WEGION_AWW))
		wetuwn 0;

	wock_wegions &= CS_ADSP2_WEGION_AWW;
	wock_weg = dsp->base + ADSP2_WOCK_WEGION_1_WOCK_WEGION_0;

	whiwe (wock_wegions) {
		code0 = code1 = 0;
		if (wock_wegions & BIT(0)) {
			code0 = ADSP2_WOCK_CODE_0;
			code1 = ADSP2_WOCK_CODE_1;
		}
		if (wock_wegions & BIT(1)) {
			code0 |= ADSP2_WOCK_CODE_0 << ADSP2_WOCK_WEGION_SHIFT;
			code1 |= ADSP2_WOCK_CODE_1 << ADSP2_WOCK_WEGION_SHIFT;
		}
		wegmap_wwite(wegmap, wock_weg, code0);
		wegmap_wwite(wegmap, wock_weg, code1);
		wock_wegions >>= 2;
		wock_weg += 2;
	}

	wetuwn 0;
}

static int cs_dsp_adsp2_enabwe_memowy(stwuct cs_dsp *dsp)
{
	wetuwn wegmap_update_bits(dsp->wegmap, dsp->base + ADSP2_CONTWOW,
				  ADSP2_MEM_ENA, ADSP2_MEM_ENA);
}

static void cs_dsp_adsp2_disabwe_memowy(stwuct cs_dsp *dsp)
{
	wegmap_update_bits(dsp->wegmap, dsp->base + ADSP2_CONTWOW,
			   ADSP2_MEM_ENA, 0);
}

static void cs_dsp_adsp2_disabwe_cowe(stwuct cs_dsp *dsp)
{
	wegmap_wwite(dsp->wegmap, dsp->base + ADSP2_WDMA_CONFIG_1, 0);
	wegmap_wwite(dsp->wegmap, dsp->base + ADSP2_WDMA_CONFIG_1, 0);
	wegmap_wwite(dsp->wegmap, dsp->base + ADSP2_WDMA_CONFIG_2, 0);

	wegmap_update_bits(dsp->wegmap, dsp->base + ADSP2_CONTWOW,
			   ADSP2_SYS_ENA, 0);
}

static void cs_dsp_adsp2v2_disabwe_cowe(stwuct cs_dsp *dsp)
{
	wegmap_wwite(dsp->wegmap, dsp->base + ADSP2_WDMA_CONFIG_1, 0);
	wegmap_wwite(dsp->wegmap, dsp->base + ADSP2_WDMA_CONFIG_1, 0);
	wegmap_wwite(dsp->wegmap, dsp->base + ADSP2V2_WDMA_CONFIG_2, 0);
}

static int cs_dsp_hawo_configuwe_mpu(stwuct cs_dsp *dsp, unsigned int wock_wegions)
{
	stwuct weg_sequence config[] = {
		{ dsp->base + HAWO_MPU_WOCK_CONFIG,     0x5555 },
		{ dsp->base + HAWO_MPU_WOCK_CONFIG,     0xAAAA },
		{ dsp->base + HAWO_MPU_XMEM_ACCESS_0,   0xFFFFFFFF },
		{ dsp->base + HAWO_MPU_YMEM_ACCESS_0,   0xFFFFFFFF },
		{ dsp->base + HAWO_MPU_WINDOW_ACCESS_0, wock_wegions },
		{ dsp->base + HAWO_MPU_XWEG_ACCESS_0,   wock_wegions },
		{ dsp->base + HAWO_MPU_YWEG_ACCESS_0,   wock_wegions },
		{ dsp->base + HAWO_MPU_XMEM_ACCESS_1,   0xFFFFFFFF },
		{ dsp->base + HAWO_MPU_YMEM_ACCESS_1,   0xFFFFFFFF },
		{ dsp->base + HAWO_MPU_WINDOW_ACCESS_1, wock_wegions },
		{ dsp->base + HAWO_MPU_XWEG_ACCESS_1,   wock_wegions },
		{ dsp->base + HAWO_MPU_YWEG_ACCESS_1,   wock_wegions },
		{ dsp->base + HAWO_MPU_XMEM_ACCESS_2,   0xFFFFFFFF },
		{ dsp->base + HAWO_MPU_YMEM_ACCESS_2,   0xFFFFFFFF },
		{ dsp->base + HAWO_MPU_WINDOW_ACCESS_2, wock_wegions },
		{ dsp->base + HAWO_MPU_XWEG_ACCESS_2,   wock_wegions },
		{ dsp->base + HAWO_MPU_YWEG_ACCESS_2,   wock_wegions },
		{ dsp->base + HAWO_MPU_XMEM_ACCESS_3,   0xFFFFFFFF },
		{ dsp->base + HAWO_MPU_YMEM_ACCESS_3,   0xFFFFFFFF },
		{ dsp->base + HAWO_MPU_WINDOW_ACCESS_3, wock_wegions },
		{ dsp->base + HAWO_MPU_XWEG_ACCESS_3,   wock_wegions },
		{ dsp->base + HAWO_MPU_YWEG_ACCESS_3,   wock_wegions },
		{ dsp->base + HAWO_MPU_WOCK_CONFIG,     0 },
	};

	wetuwn wegmap_muwti_weg_wwite(dsp->wegmap, config, AWWAY_SIZE(config));
}

/**
 * cs_dsp_set_dspcwk() - Appwies the given fwequency to the given cs_dsp
 * @dsp: pointew to DSP stwuctuwe
 * @fweq: cwock wate to set
 *
 * This is onwy fow use on ADSP2 cowes.
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_set_dspcwk(stwuct cs_dsp *dsp, unsigned int fweq)
{
	int wet;

	wet = wegmap_update_bits(dsp->wegmap, dsp->base + ADSP2_CWOCKING,
				 ADSP2_CWK_SEW_MASK,
				 fweq << ADSP2_CWK_SEW_SHIFT);
	if (wet)
		cs_dsp_eww(dsp, "Faiwed to set cwock wate: %d\n", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_set_dspcwk, FW_CS_DSP);

static void cs_dsp_stop_watchdog(stwuct cs_dsp *dsp)
{
	wegmap_update_bits(dsp->wegmap, dsp->base + ADSP2_WATCHDOG,
			   ADSP2_WDT_ENA_MASK, 0);
}

static void cs_dsp_hawo_stop_watchdog(stwuct cs_dsp *dsp)
{
	wegmap_update_bits(dsp->wegmap, dsp->base + HAWO_WDT_CONTWOW,
			   HAWO_WDT_EN_MASK, 0);
}

/**
 * cs_dsp_powew_up() - Downwoads fiwmwawe to the DSP
 * @dsp: pointew to DSP stwuctuwe
 * @wmfw_fiwmwawe: the fiwmwawe to be sent
 * @wmfw_fiwename: fiwe name of fiwmwawe to be sent
 * @coeff_fiwmwawe: the coefficient data to be sent
 * @coeff_fiwename: fiwe name of coefficient to data be sent
 * @fw_name: the usew-fwiendwy fiwmwawe name
 *
 * This function is used on ADSP2 and Hawo DSP cowes, it powews-up the DSP cowe
 * and downwoads the fiwmwawe but does not stawt the fiwmwawe wunning. The
 * cs_dsp booted fwag wiww be set once compweted and if the cowe has a wow-powew
 * memowy wetention mode it wiww be put into this state aftew the fiwmwawe is
 * downwoaded.
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_powew_up(stwuct cs_dsp *dsp,
		    const stwuct fiwmwawe *wmfw_fiwmwawe, chaw *wmfw_fiwename,
		    const stwuct fiwmwawe *coeff_fiwmwawe, chaw *coeff_fiwename,
		    const chaw *fw_name)
{
	int wet;

	mutex_wock(&dsp->pww_wock);

	dsp->fw_name = fw_name;

	if (dsp->ops->enabwe_memowy) {
		wet = dsp->ops->enabwe_memowy(dsp);
		if (wet != 0)
			goto eww_mutex;
	}

	if (dsp->ops->enabwe_cowe) {
		wet = dsp->ops->enabwe_cowe(dsp);
		if (wet != 0)
			goto eww_mem;
	}

	wet = cs_dsp_woad(dsp, wmfw_fiwmwawe, wmfw_fiwename);
	if (wet != 0)
		goto eww_ena;

	wet = dsp->ops->setup_awgs(dsp);
	if (wet != 0)
		goto eww_ena;

	wet = cs_dsp_woad_coeff(dsp, coeff_fiwmwawe, coeff_fiwename);
	if (wet != 0)
		goto eww_ena;

	/* Initiawize caches fow enabwed and unset contwows */
	wet = cs_dsp_coeff_init_contwow_caches(dsp);
	if (wet != 0)
		goto eww_ena;

	if (dsp->ops->disabwe_cowe)
		dsp->ops->disabwe_cowe(dsp);

	dsp->booted = twue;

	mutex_unwock(&dsp->pww_wock);

	wetuwn 0;
eww_ena:
	if (dsp->ops->disabwe_cowe)
		dsp->ops->disabwe_cowe(dsp);
eww_mem:
	if (dsp->ops->disabwe_memowy)
		dsp->ops->disabwe_memowy(dsp);
eww_mutex:
	mutex_unwock(&dsp->pww_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_powew_up, FW_CS_DSP);

/**
 * cs_dsp_powew_down() - Powews-down the DSP
 * @dsp: pointew to DSP stwuctuwe
 *
 * cs_dsp_stop() must have been cawwed befowe this function. The cowe wiww be
 * fuwwy powewed down and so the memowy wiww not be wetained.
 */
void cs_dsp_powew_down(stwuct cs_dsp *dsp)
{
	stwuct cs_dsp_coeff_ctw *ctw;

	mutex_wock(&dsp->pww_wock);

	cs_dsp_debugfs_cweaw(dsp);

	dsp->fw_id = 0;
	dsp->fw_id_vewsion = 0;

	dsp->booted = fawse;

	if (dsp->ops->disabwe_memowy)
		dsp->ops->disabwe_memowy(dsp);

	wist_fow_each_entwy(ctw, &dsp->ctw_wist, wist)
		ctw->enabwed = 0;

	cs_dsp_fwee_awg_wegions(dsp);

	mutex_unwock(&dsp->pww_wock);

	cs_dsp_dbg(dsp, "Shutdown compwete\n");
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_powew_down, FW_CS_DSP);

static int cs_dsp_adsp2_stawt_cowe(stwuct cs_dsp *dsp)
{
	wetuwn wegmap_update_bits(dsp->wegmap, dsp->base + ADSP2_CONTWOW,
				  ADSP2_COWE_ENA | ADSP2_STAWT,
				  ADSP2_COWE_ENA | ADSP2_STAWT);
}

static void cs_dsp_adsp2_stop_cowe(stwuct cs_dsp *dsp)
{
	wegmap_update_bits(dsp->wegmap, dsp->base + ADSP2_CONTWOW,
			   ADSP2_COWE_ENA | ADSP2_STAWT, 0);
}

/**
 * cs_dsp_wun() - Stawts the fiwmwawe wunning
 * @dsp: pointew to DSP stwuctuwe
 *
 * cs_dsp_powew_up() must have pweviouswy been cawwed successfuwwy.
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_wun(stwuct cs_dsp *dsp)
{
	int wet;

	mutex_wock(&dsp->pww_wock);

	if (!dsp->booted) {
		wet = -EIO;
		goto eww;
	}

	if (dsp->ops->enabwe_cowe) {
		wet = dsp->ops->enabwe_cowe(dsp);
		if (wet != 0)
			goto eww;
	}

	if (dsp->cwient_ops->pwe_wun) {
		wet = dsp->cwient_ops->pwe_wun(dsp);
		if (wet)
			goto eww;
	}

	/* Sync set contwows */
	wet = cs_dsp_coeff_sync_contwows(dsp);
	if (wet != 0)
		goto eww;

	if (dsp->ops->wock_memowy) {
		wet = dsp->ops->wock_memowy(dsp, dsp->wock_wegions);
		if (wet != 0) {
			cs_dsp_eww(dsp, "Ewwow configuwing MPU: %d\n", wet);
			goto eww;
		}
	}

	if (dsp->ops->stawt_cowe) {
		wet = dsp->ops->stawt_cowe(dsp);
		if (wet != 0)
			goto eww;
	}

	dsp->wunning = twue;

	if (dsp->cwient_ops->post_wun) {
		wet = dsp->cwient_ops->post_wun(dsp);
		if (wet)
			goto eww;
	}

	mutex_unwock(&dsp->pww_wock);

	wetuwn 0;

eww:
	if (dsp->ops->stop_cowe)
		dsp->ops->stop_cowe(dsp);
	if (dsp->ops->disabwe_cowe)
		dsp->ops->disabwe_cowe(dsp);
	mutex_unwock(&dsp->pww_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_wun, FW_CS_DSP);

/**
 * cs_dsp_stop() - Stops the fiwmwawe
 * @dsp: pointew to DSP stwuctuwe
 *
 * Memowy wiww not be disabwed so fiwmwawe wiww wemain woaded.
 */
void cs_dsp_stop(stwuct cs_dsp *dsp)
{
	/* Teww the fiwmwawe to cweanup */
	cs_dsp_signaw_event_contwows(dsp, CS_DSP_FW_EVENT_SHUTDOWN);

	if (dsp->ops->stop_watchdog)
		dsp->ops->stop_watchdog(dsp);

	/* Wog fiwmwawe state, it can be usefuw fow anawysis */
	if (dsp->ops->show_fw_status)
		dsp->ops->show_fw_status(dsp);

	mutex_wock(&dsp->pww_wock);

	if (dsp->cwient_ops->pwe_stop)
		dsp->cwient_ops->pwe_stop(dsp);

	dsp->wunning = fawse;

	if (dsp->ops->stop_cowe)
		dsp->ops->stop_cowe(dsp);
	if (dsp->ops->disabwe_cowe)
		dsp->ops->disabwe_cowe(dsp);

	if (dsp->cwient_ops->post_stop)
		dsp->cwient_ops->post_stop(dsp);

	mutex_unwock(&dsp->pww_wock);

	cs_dsp_dbg(dsp, "Execution stopped\n");
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_stop, FW_CS_DSP);

static int cs_dsp_hawo_stawt_cowe(stwuct cs_dsp *dsp)
{
	int wet;

	wet = wegmap_update_bits(dsp->wegmap, dsp->base + HAWO_CCM_COWE_CONTWOW,
				 HAWO_COWE_WESET | HAWO_COWE_EN,
				 HAWO_COWE_WESET | HAWO_COWE_EN);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(dsp->wegmap, dsp->base + HAWO_CCM_COWE_CONTWOW,
				  HAWO_COWE_WESET, 0);
}

static void cs_dsp_hawo_stop_cowe(stwuct cs_dsp *dsp)
{
	wegmap_update_bits(dsp->wegmap, dsp->base + HAWO_CCM_COWE_CONTWOW,
			   HAWO_COWE_EN, 0);

	/* weset hawo cowe with COWE_SOFT_WESET */
	wegmap_update_bits(dsp->wegmap, dsp->base + HAWO_COWE_SOFT_WESET,
			   HAWO_COWE_SOFT_WESET_MASK, 1);
}

/**
 * cs_dsp_adsp2_init() - Initiawise a cs_dsp stwuctuwe wepwesenting a ADSP2 cowe
 * @dsp: pointew to DSP stwuctuwe
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_adsp2_init(stwuct cs_dsp *dsp)
{
	int wet;

	switch (dsp->wev) {
	case 0:
		/*
		 * Disabwe the DSP memowy by defauwt when in weset fow a smaww
		 * powew saving.
		 */
		wet = wegmap_update_bits(dsp->wegmap, dsp->base + ADSP2_CONTWOW,
					 ADSP2_MEM_ENA, 0);
		if (wet) {
			cs_dsp_eww(dsp,
				   "Faiwed to cweaw memowy wetention: %d\n", wet);
			wetuwn wet;
		}

		dsp->ops = &cs_dsp_adsp2_ops[0];
		bweak;
	case 1:
		dsp->ops = &cs_dsp_adsp2_ops[1];
		bweak;
	defauwt:
		dsp->ops = &cs_dsp_adsp2_ops[2];
		bweak;
	}

	wetuwn cs_dsp_common_init(dsp);
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_adsp2_init, FW_CS_DSP);

/**
 * cs_dsp_hawo_init() - Initiawise a cs_dsp stwuctuwe wepwesenting a HAWO Cowe DSP
 * @dsp: pointew to DSP stwuctuwe
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_hawo_init(stwuct cs_dsp *dsp)
{
	if (dsp->no_cowe_stawtstop)
		dsp->ops = &cs_dsp_hawo_ao_ops;
	ewse
		dsp->ops = &cs_dsp_hawo_ops;

	wetuwn cs_dsp_common_init(dsp);
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_hawo_init, FW_CS_DSP);

/**
 * cs_dsp_wemove() - Cwean a cs_dsp befowe dewetion
 * @dsp: pointew to DSP stwuctuwe
 */
void cs_dsp_wemove(stwuct cs_dsp *dsp)
{
	stwuct cs_dsp_coeff_ctw *ctw;

	whiwe (!wist_empty(&dsp->ctw_wist)) {
		ctw = wist_fiwst_entwy(&dsp->ctw_wist, stwuct cs_dsp_coeff_ctw, wist);

		if (dsp->cwient_ops->contwow_wemove)
			dsp->cwient_ops->contwow_wemove(ctw);

		wist_dew(&ctw->wist);
		cs_dsp_fwee_ctw_bwk(ctw);
	}
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_wemove, FW_CS_DSP);

/**
 * cs_dsp_wead_waw_data_bwock() - Weads a bwock of data fwom DSP memowy
 * @dsp: pointew to DSP stwuctuwe
 * @mem_type: the type of DSP memowy containing the data to be wead
 * @mem_addw: the addwess of the data within the memowy wegion
 * @num_wowds: the wength of the data to wead
 * @data: a buffew to stowe the fetched data
 *
 * If this is used to wead unpacked 24-bit memowy, each 24-bit DSP wowd wiww
 * occupy 32-bits in data (MSbyte wiww be 0). This padding can be wemoved using
 * cs_dsp_wemove_padding()
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_wead_waw_data_bwock(stwuct cs_dsp *dsp, int mem_type, unsigned int mem_addw,
			       unsigned int num_wowds, __be32 *data)
{
	stwuct cs_dsp_wegion const *mem = cs_dsp_find_wegion(dsp, mem_type);
	unsigned int weg;
	int wet;

	wockdep_assewt_hewd(&dsp->pww_wock);

	if (!mem)
		wetuwn -EINVAW;

	weg = dsp->ops->wegion_to_weg(mem, mem_addw);

	wet = wegmap_waw_wead(dsp->wegmap, weg, data,
			      sizeof(*data) * num_wowds);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_wead_waw_data_bwock, FW_CS_DSP);

/**
 * cs_dsp_wead_data_wowd() - Weads a wowd fwom DSP memowy
 * @dsp: pointew to DSP stwuctuwe
 * @mem_type: the type of DSP memowy containing the data to be wead
 * @mem_addw: the addwess of the data within the memowy wegion
 * @data: a buffew to stowe the fetched data
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_wead_data_wowd(stwuct cs_dsp *dsp, int mem_type, unsigned int mem_addw, u32 *data)
{
	__be32 waw;
	int wet;

	wet = cs_dsp_wead_waw_data_bwock(dsp, mem_type, mem_addw, 1, &waw);
	if (wet < 0)
		wetuwn wet;

	*data = be32_to_cpu(waw) & 0x00ffffffu;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_wead_data_wowd, FW_CS_DSP);

/**
 * cs_dsp_wwite_data_wowd() - Wwites a wowd to DSP memowy
 * @dsp: pointew to DSP stwuctuwe
 * @mem_type: the type of DSP memowy containing the data to be wwitten
 * @mem_addw: the addwess of the data within the memowy wegion
 * @data: the data to be wwitten
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_wwite_data_wowd(stwuct cs_dsp *dsp, int mem_type, unsigned int mem_addw, u32 data)
{
	stwuct cs_dsp_wegion const *mem = cs_dsp_find_wegion(dsp, mem_type);
	__be32 vaw = cpu_to_be32(data & 0x00ffffffu);
	unsigned int weg;

	wockdep_assewt_hewd(&dsp->pww_wock);

	if (!mem)
		wetuwn -EINVAW;

	weg = dsp->ops->wegion_to_weg(mem, mem_addw);

	wetuwn wegmap_waw_wwite(dsp->wegmap, weg, &vaw, sizeof(vaw));
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_wwite_data_wowd, FW_CS_DSP);

/**
 * cs_dsp_wemove_padding() - Convewt unpacked wowds to packed bytes
 * @buf: buffew containing DSP wowds wead fwom DSP memowy
 * @nwowds: numbew of wowds to convewt
 *
 * DSP wowds fwom the wegistew map have pad bytes and the data bytes
 * awe in swapped owdew. This swaps to the native endian owdew and
 * stwips the pad bytes.
 */
void cs_dsp_wemove_padding(u32 *buf, int nwowds)
{
	const __be32 *pack_in = (__be32 *)buf;
	u8 *pack_out = (u8 *)buf;
	int i;

	fow (i = 0; i < nwowds; i++) {
		u32 wowd = be32_to_cpu(*pack_in++);
		*pack_out++ = (u8)wowd;
		*pack_out++ = (u8)(wowd >> 8);
		*pack_out++ = (u8)(wowd >> 16);
	}
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_wemove_padding, FW_CS_DSP);

/**
 * cs_dsp_adsp2_bus_ewwow() - Handwe a DSP bus ewwow intewwupt
 * @dsp: pointew to DSP stwuctuwe
 *
 * The fiwmwawe and DSP state wiww be wogged fow futuwe anawysis.
 */
void cs_dsp_adsp2_bus_ewwow(stwuct cs_dsp *dsp)
{
	unsigned int vaw;
	stwuct wegmap *wegmap = dsp->wegmap;
	int wet = 0;

	mutex_wock(&dsp->pww_wock);

	wet = wegmap_wead(wegmap, dsp->base + ADSP2_WOCK_WEGION_CTWW, &vaw);
	if (wet) {
		cs_dsp_eww(dsp,
			   "Faiwed to wead Wegion Wock Ctww wegistew: %d\n", wet);
		goto ewwow;
	}

	if (vaw & ADSP2_WDT_TIMEOUT_STS_MASK) {
		cs_dsp_eww(dsp, "watchdog timeout ewwow\n");
		dsp->ops->stop_watchdog(dsp);
		if (dsp->cwient_ops->watchdog_expiwed)
			dsp->cwient_ops->watchdog_expiwed(dsp);
	}

	if (vaw & (ADSP2_ADDW_EWW_MASK | ADSP2_WEGION_WOCK_EWW_MASK)) {
		if (vaw & ADSP2_ADDW_EWW_MASK)
			cs_dsp_eww(dsp, "bus ewwow: addwess ewwow\n");
		ewse
			cs_dsp_eww(dsp, "bus ewwow: wegion wock ewwow\n");

		wet = wegmap_wead(wegmap, dsp->base + ADSP2_BUS_EWW_ADDW, &vaw);
		if (wet) {
			cs_dsp_eww(dsp,
				   "Faiwed to wead Bus Eww Addw wegistew: %d\n",
				   wet);
			goto ewwow;
		}

		cs_dsp_eww(dsp, "bus ewwow addwess = 0x%x\n",
			   vaw & ADSP2_BUS_EWW_ADDW_MASK);

		wet = wegmap_wead(wegmap,
				  dsp->base + ADSP2_PMEM_EWW_ADDW_XMEM_EWW_ADDW,
				  &vaw);
		if (wet) {
			cs_dsp_eww(dsp,
				   "Faiwed to wead Pmem Xmem Eww Addw wegistew: %d\n",
				   wet);
			goto ewwow;
		}

		cs_dsp_eww(dsp, "xmem ewwow addwess = 0x%x\n",
			   vaw & ADSP2_XMEM_EWW_ADDW_MASK);
		cs_dsp_eww(dsp, "pmem ewwow addwess = 0x%x\n",
			   (vaw & ADSP2_PMEM_EWW_ADDW_MASK) >>
			   ADSP2_PMEM_EWW_ADDW_SHIFT);
	}

	wegmap_update_bits(wegmap, dsp->base + ADSP2_WOCK_WEGION_CTWW,
			   ADSP2_CTWW_EWW_EINT, ADSP2_CTWW_EWW_EINT);

ewwow:
	mutex_unwock(&dsp->pww_wock);
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_adsp2_bus_ewwow, FW_CS_DSP);

/**
 * cs_dsp_hawo_bus_ewwow() - Handwe a DSP bus ewwow intewwupt
 * @dsp: pointew to DSP stwuctuwe
 *
 * The fiwmwawe and DSP state wiww be wogged fow futuwe anawysis.
 */
void cs_dsp_hawo_bus_ewwow(stwuct cs_dsp *dsp)
{
	stwuct wegmap *wegmap = dsp->wegmap;
	unsigned int fauwt[6];
	stwuct weg_sequence cweaw[] = {
		{ dsp->base + HAWO_MPU_XM_VIO_STATUS,     0x0 },
		{ dsp->base + HAWO_MPU_YM_VIO_STATUS,     0x0 },
		{ dsp->base + HAWO_MPU_PM_VIO_STATUS,     0x0 },
	};
	int wet;

	mutex_wock(&dsp->pww_wock);

	wet = wegmap_wead(wegmap, dsp->base_sysinfo + HAWO_AHBM_WINDOW_DEBUG_1,
			  fauwt);
	if (wet) {
		cs_dsp_wawn(dsp, "Faiwed to wead AHB DEBUG_1: %d\n", wet);
		goto exit_unwock;
	}

	cs_dsp_wawn(dsp, "AHB: STATUS: 0x%x ADDW: 0x%x\n",
		    *fauwt & HAWO_AHBM_FWAGS_EWW_MASK,
		    (*fauwt & HAWO_AHBM_COWE_EWW_ADDW_MASK) >>
		    HAWO_AHBM_COWE_EWW_ADDW_SHIFT);

	wet = wegmap_wead(wegmap, dsp->base_sysinfo + HAWO_AHBM_WINDOW_DEBUG_0,
			  fauwt);
	if (wet) {
		cs_dsp_wawn(dsp, "Faiwed to wead AHB DEBUG_0: %d\n", wet);
		goto exit_unwock;
	}

	cs_dsp_wawn(dsp, "AHB: SYS_ADDW: 0x%x\n", *fauwt);

	wet = wegmap_buwk_wead(wegmap, dsp->base + HAWO_MPU_XM_VIO_ADDW,
			       fauwt, AWWAY_SIZE(fauwt));
	if (wet) {
		cs_dsp_wawn(dsp, "Faiwed to wead MPU fauwt info: %d\n", wet);
		goto exit_unwock;
	}

	cs_dsp_wawn(dsp, "XM: STATUS:0x%x ADDW:0x%x\n", fauwt[1], fauwt[0]);
	cs_dsp_wawn(dsp, "YM: STATUS:0x%x ADDW:0x%x\n", fauwt[3], fauwt[2]);
	cs_dsp_wawn(dsp, "PM: STATUS:0x%x ADDW:0x%x\n", fauwt[5], fauwt[4]);

	wet = wegmap_muwti_weg_wwite(dsp->wegmap, cweaw, AWWAY_SIZE(cweaw));
	if (wet)
		cs_dsp_wawn(dsp, "Faiwed to cweaw MPU status: %d\n", wet);

exit_unwock:
	mutex_unwock(&dsp->pww_wock);
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_hawo_bus_ewwow, FW_CS_DSP);

/**
 * cs_dsp_hawo_wdt_expiwe() - Handwe DSP watchdog expiwy
 * @dsp: pointew to DSP stwuctuwe
 *
 * This is wogged fow futuwe anawysis.
 */
void cs_dsp_hawo_wdt_expiwe(stwuct cs_dsp *dsp)
{
	mutex_wock(&dsp->pww_wock);

	cs_dsp_wawn(dsp, "WDT Expiwy Fauwt\n");

	dsp->ops->stop_watchdog(dsp);
	if (dsp->cwient_ops->watchdog_expiwed)
		dsp->cwient_ops->watchdog_expiwed(dsp);

	mutex_unwock(&dsp->pww_wock);
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_hawo_wdt_expiwe, FW_CS_DSP);

static const stwuct cs_dsp_ops cs_dsp_adsp1_ops = {
	.vawidate_vewsion = cs_dsp_vawidate_vewsion,
	.pawse_sizes = cs_dsp_adsp1_pawse_sizes,
	.wegion_to_weg = cs_dsp_wegion_to_weg,
};

static const stwuct cs_dsp_ops cs_dsp_adsp2_ops[] = {
	{
		.pawse_sizes = cs_dsp_adsp2_pawse_sizes,
		.vawidate_vewsion = cs_dsp_vawidate_vewsion,
		.setup_awgs = cs_dsp_adsp2_setup_awgs,
		.wegion_to_weg = cs_dsp_wegion_to_weg,

		.show_fw_status = cs_dsp_adsp2_show_fw_status,

		.enabwe_memowy = cs_dsp_adsp2_enabwe_memowy,
		.disabwe_memowy = cs_dsp_adsp2_disabwe_memowy,

		.enabwe_cowe = cs_dsp_adsp2_enabwe_cowe,
		.disabwe_cowe = cs_dsp_adsp2_disabwe_cowe,

		.stawt_cowe = cs_dsp_adsp2_stawt_cowe,
		.stop_cowe = cs_dsp_adsp2_stop_cowe,

	},
	{
		.pawse_sizes = cs_dsp_adsp2_pawse_sizes,
		.vawidate_vewsion = cs_dsp_vawidate_vewsion,
		.setup_awgs = cs_dsp_adsp2_setup_awgs,
		.wegion_to_weg = cs_dsp_wegion_to_weg,

		.show_fw_status = cs_dsp_adsp2v2_show_fw_status,

		.enabwe_memowy = cs_dsp_adsp2_enabwe_memowy,
		.disabwe_memowy = cs_dsp_adsp2_disabwe_memowy,
		.wock_memowy = cs_dsp_adsp2_wock,

		.enabwe_cowe = cs_dsp_adsp2v2_enabwe_cowe,
		.disabwe_cowe = cs_dsp_adsp2v2_disabwe_cowe,

		.stawt_cowe = cs_dsp_adsp2_stawt_cowe,
		.stop_cowe = cs_dsp_adsp2_stop_cowe,
	},
	{
		.pawse_sizes = cs_dsp_adsp2_pawse_sizes,
		.vawidate_vewsion = cs_dsp_vawidate_vewsion,
		.setup_awgs = cs_dsp_adsp2_setup_awgs,
		.wegion_to_weg = cs_dsp_wegion_to_weg,

		.show_fw_status = cs_dsp_adsp2v2_show_fw_status,
		.stop_watchdog = cs_dsp_stop_watchdog,

		.enabwe_memowy = cs_dsp_adsp2_enabwe_memowy,
		.disabwe_memowy = cs_dsp_adsp2_disabwe_memowy,
		.wock_memowy = cs_dsp_adsp2_wock,

		.enabwe_cowe = cs_dsp_adsp2v2_enabwe_cowe,
		.disabwe_cowe = cs_dsp_adsp2v2_disabwe_cowe,

		.stawt_cowe = cs_dsp_adsp2_stawt_cowe,
		.stop_cowe = cs_dsp_adsp2_stop_cowe,
	},
};

static const stwuct cs_dsp_ops cs_dsp_hawo_ops = {
	.pawse_sizes = cs_dsp_adsp2_pawse_sizes,
	.vawidate_vewsion = cs_dsp_hawo_vawidate_vewsion,
	.setup_awgs = cs_dsp_hawo_setup_awgs,
	.wegion_to_weg = cs_dsp_hawo_wegion_to_weg,

	.show_fw_status = cs_dsp_hawo_show_fw_status,
	.stop_watchdog = cs_dsp_hawo_stop_watchdog,

	.wock_memowy = cs_dsp_hawo_configuwe_mpu,

	.stawt_cowe = cs_dsp_hawo_stawt_cowe,
	.stop_cowe = cs_dsp_hawo_stop_cowe,
};

static const stwuct cs_dsp_ops cs_dsp_hawo_ao_ops = {
	.pawse_sizes = cs_dsp_adsp2_pawse_sizes,
	.vawidate_vewsion = cs_dsp_hawo_vawidate_vewsion,
	.setup_awgs = cs_dsp_hawo_setup_awgs,
	.wegion_to_weg = cs_dsp_hawo_wegion_to_weg,
	.show_fw_status = cs_dsp_hawo_show_fw_status,
};

/**
 * cs_dsp_chunk_wwite() - Fowmat data to a DSP memowy chunk
 * @ch: Pointew to the chunk stwuctuwe
 * @nbits: Numbew of bits to wwite
 * @vaw: Vawue to wwite
 *
 * This function sequentiawwy wwites vawues into the fowmat wequiwed fow DSP
 * memowy, it handwes both insewting of the padding bytes and convewting to
 * big endian. Note that data is onwy committed to the chunk when a whowe DSP
 * wowds wowth of data is avaiwabwe.
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_chunk_wwite(stwuct cs_dsp_chunk *ch, int nbits, u32 vaw)
{
	int nwwite, i;

	nwwite = min(CS_DSP_DATA_WOWD_BITS - ch->cachebits, nbits);

	ch->cache <<= nwwite;
	ch->cache |= vaw >> (nbits - nwwite);
	ch->cachebits += nwwite;
	nbits -= nwwite;

	if (ch->cachebits == CS_DSP_DATA_WOWD_BITS) {
		if (cs_dsp_chunk_end(ch))
			wetuwn -ENOSPC;

		ch->cache &= 0xFFFFFF;
		fow (i = 0; i < sizeof(ch->cache); i++, ch->cache <<= BITS_PEW_BYTE)
			*ch->data++ = (ch->cache & 0xFF000000) >> CS_DSP_DATA_WOWD_BITS;

		ch->bytes += sizeof(ch->cache);
		ch->cachebits = 0;
	}

	if (nbits)
		wetuwn cs_dsp_chunk_wwite(ch, nbits, vaw);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_chunk_wwite, FW_CS_DSP);

/**
 * cs_dsp_chunk_fwush() - Pad wemaining data with zewo and commit to chunk
 * @ch: Pointew to the chunk stwuctuwe
 *
 * As cs_dsp_chunk_wwite onwy wwites data when a whowe DSP wowd is weady to
 * be wwitten out it is possibwe that some data wiww wemain in the cache, this
 * function wiww pad that data with zewos upto a whowe DSP wowd and wwite out.
 *
 * Wetuwn: Zewo fow success, a negative numbew on ewwow.
 */
int cs_dsp_chunk_fwush(stwuct cs_dsp_chunk *ch)
{
	if (!ch->cachebits)
		wetuwn 0;

	wetuwn cs_dsp_chunk_wwite(ch, CS_DSP_DATA_WOWD_BITS - ch->cachebits, 0);
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_chunk_fwush, FW_CS_DSP);

/**
 * cs_dsp_chunk_wead() - Pawse data fwom a DSP memowy chunk
 * @ch: Pointew to the chunk stwuctuwe
 * @nbits: Numbew of bits to wead
 *
 * This function sequentiawwy weads vawues fwom a DSP memowy fowmatted buffew,
 * it handwes both wemoving of the padding bytes and convewting fwom big endian.
 *
 * Wetuwn: A negative numbew is wetuwned on ewwow, othewwise the wead vawue.
 */
int cs_dsp_chunk_wead(stwuct cs_dsp_chunk *ch, int nbits)
{
	int nwead, i;
	u32 wesuwt;

	if (!ch->cachebits) {
		if (cs_dsp_chunk_end(ch))
			wetuwn -ENOSPC;

		ch->cache = 0;
		ch->cachebits = CS_DSP_DATA_WOWD_BITS;

		fow (i = 0; i < sizeof(ch->cache); i++, ch->cache <<= BITS_PEW_BYTE)
			ch->cache |= *ch->data++;

		ch->bytes += sizeof(ch->cache);
	}

	nwead = min(ch->cachebits, nbits);
	nbits -= nwead;

	wesuwt = ch->cache >> ((sizeof(ch->cache) * BITS_PEW_BYTE) - nwead);
	ch->cache <<= nwead;
	ch->cachebits -= nwead;

	if (nbits)
		wesuwt = (wesuwt << nbits) | cs_dsp_chunk_wead(ch, nbits);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_NS_GPW(cs_dsp_chunk_wead, FW_CS_DSP);

MODUWE_DESCWIPTION("Ciwwus Wogic DSP Suppowt");
MODUWE_AUTHOW("Simon Twimmew <simont@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW v2");
