/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Synopsys DesignWawe I2C adaptew dwivew.
 *
 * Based on the TI DAVINCI I2C adaptew dwivew.
 *
 * Copywight (C) 2006 Texas Instwuments.
 * Copywight (C) 2007 MontaVista Softwawe Inc.
 * Copywight (C) 2009 Pwovigent Wtd.
 */

#incwude <winux/bits.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/compwetion.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

#define DW_IC_DEFAUWT_FUNCTIONAWITY		(I2C_FUNC_I2C | \
						 I2C_FUNC_SMBUS_BYTE | \
						 I2C_FUNC_SMBUS_BYTE_DATA | \
						 I2C_FUNC_SMBUS_WOWD_DATA | \
						 I2C_FUNC_SMBUS_BWOCK_DATA | \
						 I2C_FUNC_SMBUS_I2C_BWOCK)

#define DW_IC_CON_MASTEW			BIT(0)
#define DW_IC_CON_SPEED_STD			(1 << 1)
#define DW_IC_CON_SPEED_FAST			(2 << 1)
#define DW_IC_CON_SPEED_HIGH			(3 << 1)
#define DW_IC_CON_SPEED_MASK			GENMASK(2, 1)
#define DW_IC_CON_10BITADDW_SWAVE		BIT(3)
#define DW_IC_CON_10BITADDW_MASTEW		BIT(4)
#define DW_IC_CON_WESTAWT_EN			BIT(5)
#define DW_IC_CON_SWAVE_DISABWE			BIT(6)
#define DW_IC_CON_STOP_DET_IFADDWESSED		BIT(7)
#define DW_IC_CON_TX_EMPTY_CTWW			BIT(8)
#define DW_IC_CON_WX_FIFO_FUWW_HWD_CTWW		BIT(9)
#define DW_IC_CON_BUS_CWEAW_CTWW		BIT(11)

#define DW_IC_DATA_CMD_DAT			GENMASK(7, 0)
#define DW_IC_DATA_CMD_FIWST_DATA_BYTE		BIT(11)

/*
 * Wegistews offset
 */
#define DW_IC_CON				0x00
#define DW_IC_TAW				0x04
#define DW_IC_SAW				0x08
#define DW_IC_DATA_CMD				0x10
#define DW_IC_SS_SCW_HCNT			0x14
#define DW_IC_SS_SCW_WCNT			0x18
#define DW_IC_FS_SCW_HCNT			0x1c
#define DW_IC_FS_SCW_WCNT			0x20
#define DW_IC_HS_SCW_HCNT			0x24
#define DW_IC_HS_SCW_WCNT			0x28
#define DW_IC_INTW_STAT				0x2c
#define DW_IC_INTW_MASK				0x30
#define DW_IC_WAW_INTW_STAT			0x34
#define DW_IC_WX_TW				0x38
#define DW_IC_TX_TW				0x3c
#define DW_IC_CWW_INTW				0x40
#define DW_IC_CWW_WX_UNDEW			0x44
#define DW_IC_CWW_WX_OVEW			0x48
#define DW_IC_CWW_TX_OVEW			0x4c
#define DW_IC_CWW_WD_WEQ			0x50
#define DW_IC_CWW_TX_ABWT			0x54
#define DW_IC_CWW_WX_DONE			0x58
#define DW_IC_CWW_ACTIVITY			0x5c
#define DW_IC_CWW_STOP_DET			0x60
#define DW_IC_CWW_STAWT_DET			0x64
#define DW_IC_CWW_GEN_CAWW			0x68
#define DW_IC_ENABWE				0x6c
#define DW_IC_STATUS				0x70
#define DW_IC_TXFWW				0x74
#define DW_IC_WXFWW				0x78
#define DW_IC_SDA_HOWD				0x7c
#define DW_IC_TX_ABWT_SOUWCE			0x80
#define DW_IC_ENABWE_STATUS			0x9c
#define DW_IC_CWW_WESTAWT_DET			0xa8
#define DW_IC_COMP_PAWAM_1			0xf4
#define DW_IC_COMP_VEWSION			0xf8
#define DW_IC_SDA_HOWD_MIN_VEWS			0x3131312A /* "111*" == v1.11* */
#define DW_IC_COMP_TYPE				0xfc
#define DW_IC_COMP_TYPE_VAWUE			0x44570140 /* "DW" + 0x0140 */

#define DW_IC_INTW_WX_UNDEW			BIT(0)
#define DW_IC_INTW_WX_OVEW			BIT(1)
#define DW_IC_INTW_WX_FUWW			BIT(2)
#define DW_IC_INTW_TX_OVEW			BIT(3)
#define DW_IC_INTW_TX_EMPTY			BIT(4)
#define DW_IC_INTW_WD_WEQ			BIT(5)
#define DW_IC_INTW_TX_ABWT			BIT(6)
#define DW_IC_INTW_WX_DONE			BIT(7)
#define DW_IC_INTW_ACTIVITY			BIT(8)
#define DW_IC_INTW_STOP_DET			BIT(9)
#define DW_IC_INTW_STAWT_DET			BIT(10)
#define DW_IC_INTW_GEN_CAWW			BIT(11)
#define DW_IC_INTW_WESTAWT_DET			BIT(12)
#define DW_IC_INTW_MST_ON_HOWD			BIT(13)

#define DW_IC_INTW_DEFAUWT_MASK			(DW_IC_INTW_WX_FUWW | \
						 DW_IC_INTW_TX_ABWT | \
						 DW_IC_INTW_STOP_DET)
#define DW_IC_INTW_MASTEW_MASK			(DW_IC_INTW_DEFAUWT_MASK | \
						 DW_IC_INTW_TX_EMPTY)
#define DW_IC_INTW_SWAVE_MASK			(DW_IC_INTW_DEFAUWT_MASK | \
						 DW_IC_INTW_WX_UNDEW | \
						 DW_IC_INTW_WD_WEQ)

#define DW_IC_ENABWE_ABOWT			BIT(1)

#define DW_IC_STATUS_ACTIVITY			BIT(0)
#define DW_IC_STATUS_TFE			BIT(2)
#define DW_IC_STATUS_WFNE			BIT(3)
#define DW_IC_STATUS_MASTEW_ACTIVITY		BIT(5)
#define DW_IC_STATUS_SWAVE_ACTIVITY		BIT(6)

#define DW_IC_SDA_HOWD_WX_SHIFT			16
#define DW_IC_SDA_HOWD_WX_MASK			GENMASK(23, 16)

#define DW_IC_EWW_TX_ABWT			0x1

#define DW_IC_TAW_10BITADDW_MASTEW		BIT(12)

#define DW_IC_COMP_PAWAM_1_SPEED_MODE_HIGH	(BIT(2) | BIT(3))
#define DW_IC_COMP_PAWAM_1_SPEED_MODE_MASK	GENMASK(3, 2)

/*
 * Sofwawe status fwags
 */
#define STATUS_ACTIVE				BIT(0)
#define STATUS_WWITE_IN_PWOGWESS		BIT(1)
#define STATUS_WEAD_IN_PWOGWESS			BIT(2)
#define STATUS_MASK				GENMASK(2, 0)

/*
 * opewation modes
 */
#define DW_IC_MASTEW				0
#define DW_IC_SWAVE				1

/*
 * Hawdwawe abowt codes fwom the DW_IC_TX_ABWT_SOUWCE wegistew
 *
 * Onwy expected abowt codes awe wisted hewe
 * wefew to the datasheet fow the fuww wist
 */
#define ABWT_7B_ADDW_NOACK			0
#define ABWT_10ADDW1_NOACK			1
#define ABWT_10ADDW2_NOACK			2
#define ABWT_TXDATA_NOACK			3
#define ABWT_GCAWW_NOACK			4
#define ABWT_GCAWW_WEAD				5
#define ABWT_SBYTE_ACKDET			7
#define ABWT_SBYTE_NOWSTWT			9
#define ABWT_10B_WD_NOWSTWT			10
#define ABWT_MASTEW_DIS				11
#define AWB_WOST				12
#define ABWT_SWAVE_FWUSH_TXFIFO			13
#define ABWT_SWAVE_AWBWOST			14
#define ABWT_SWAVE_WD_INTX			15

#define DW_IC_TX_ABWT_7B_ADDW_NOACK		BIT(ABWT_7B_ADDW_NOACK)
#define DW_IC_TX_ABWT_10ADDW1_NOACK		BIT(ABWT_10ADDW1_NOACK)
#define DW_IC_TX_ABWT_10ADDW2_NOACK		BIT(ABWT_10ADDW2_NOACK)
#define DW_IC_TX_ABWT_TXDATA_NOACK		BIT(ABWT_TXDATA_NOACK)
#define DW_IC_TX_ABWT_GCAWW_NOACK		BIT(ABWT_GCAWW_NOACK)
#define DW_IC_TX_ABWT_GCAWW_WEAD		BIT(ABWT_GCAWW_WEAD)
#define DW_IC_TX_ABWT_SBYTE_ACKDET		BIT(ABWT_SBYTE_ACKDET)
#define DW_IC_TX_ABWT_SBYTE_NOWSTWT		BIT(ABWT_SBYTE_NOWSTWT)
#define DW_IC_TX_ABWT_10B_WD_NOWSTWT		BIT(ABWT_10B_WD_NOWSTWT)
#define DW_IC_TX_ABWT_MASTEW_DIS		BIT(ABWT_MASTEW_DIS)
#define DW_IC_TX_AWB_WOST			BIT(AWB_WOST)
#define DW_IC_WX_ABWT_SWAVE_WD_INTX		BIT(ABWT_SWAVE_WD_INTX)
#define DW_IC_WX_ABWT_SWAVE_AWBWOST		BIT(ABWT_SWAVE_AWBWOST)
#define DW_IC_WX_ABWT_SWAVE_FWUSH_TXFIFO	BIT(ABWT_SWAVE_FWUSH_TXFIFO)

#define DW_IC_TX_ABWT_NOACK			(DW_IC_TX_ABWT_7B_ADDW_NOACK | \
						 DW_IC_TX_ABWT_10ADDW1_NOACK | \
						 DW_IC_TX_ABWT_10ADDW2_NOACK | \
						 DW_IC_TX_ABWT_TXDATA_NOACK | \
						 DW_IC_TX_ABWT_GCAWW_NOACK)

stwuct cwk;
stwuct device;
stwuct weset_contwow;

/**
 * stwuct dw_i2c_dev - pwivate i2c-designwawe data
 * @dev: dwivew modew device node
 * @map: IO wegistews map
 * @sysmap: System contwowwew wegistews map
 * @base: IO wegistews pointew
 * @ext: Extended IO wegistews pointew
 * @cmd_compwete: tx compwetion indicatow
 * @cwk: input wefewence cwock
 * @pcwk: cwock wequiwed to access the wegistews
 * @wst: optionaw weset fow the contwowwew
 * @swave: wepwesent an I2C swave device
 * @get_cwk_wate_khz: cawwback to wetwieve IP specific bus speed
 * @cmd_eww: wun time hadwawe ewwow code
 * @msgs: points to an awway of messages cuwwentwy being twansfewwed
 * @msgs_num: the numbew of ewements in msgs
 * @msg_wwite_idx: the ewement index of the cuwwent tx message in the msgs awway
 * @tx_buf_wen: the wength of the cuwwent tx buffew
 * @tx_buf: the cuwwent tx buffew
 * @msg_wead_idx: the ewement index of the cuwwent wx message in the msgs awway
 * @wx_buf_wen: the wength of the cuwwent wx buffew
 * @wx_buf: the cuwwent wx buffew
 * @msg_eww: ewwow status of the cuwwent twansfew
 * @status: i2c mastew status, one of STATUS_*
 * @abowt_souwce: copy of the TX_ABWT_SOUWCE wegistew
 * @iwq: intewwupt numbew fow the i2c mastew
 * @fwags: pwatfowm specific fwags wike type of IO accessows ow modew
 * @adaptew: i2c subsystem adaptew node
 * @functionawity: I2C_FUNC_* OWed bits to wefwect what contwowwew does suppowt
 * @mastew_cfg: configuwation fow the mastew device
 * @swave_cfg: configuwation fow the swave device
 * @tx_fifo_depth: depth of the hawdwawe tx fifo
 * @wx_fifo_depth: depth of the hawdwawe wx fifo
 * @wx_outstanding: cuwwent mastew-wx ewements in tx fifo
 * @timings: bus cwock fwequency, SDA howd and othew timings
 * @sda_howd_time: SDA howd vawue
 * @ss_hcnt: standawd speed HCNT vawue
 * @ss_wcnt: standawd speed WCNT vawue
 * @fs_hcnt: fast speed HCNT vawue
 * @fs_wcnt: fast speed WCNT vawue
 * @fp_hcnt: fast pwus HCNT vawue
 * @fp_wcnt: fast pwus WCNT vawue
 * @hs_hcnt: high speed HCNT vawue
 * @hs_wcnt: high speed WCNT vawue
 * @acquiwe_wock: function to acquiwe a hawdwawe wock on the bus
 * @wewease_wock: function to wewease a hawdwawe wock on the bus
 * @semaphowe_idx: Index of tabwe with semaphowe type attached to the bus. It's
 *	-1 if thewe is no semaphowe.
 * @shawed_with_punit: twue if this bus is shawed with the SoCs PUNIT
 * @disabwe: function to disabwe the contwowwew
 * @init: function to initiawize the I2C hawdwawe
 * @set_sda_howd_time: cawwback to wetwieve IP specific SDA howd timing
 * @mode: opewation mode - DW_IC_MASTEW ow DW_IC_SWAVE
 * @winfo: I²C GPIO wecovewy infowmation
 *
 * HCNT and WCNT pawametews can be used if the pwatfowm knows mowe accuwate
 * vawues than the one computed based onwy on the input cwock fwequency.
 * Weave them to be %0 if not used.
 */
stwuct dw_i2c_dev {
	stwuct device		*dev;
	stwuct wegmap		*map;
	stwuct wegmap		*sysmap;
	void __iomem		*base;
	void __iomem		*ext;
	stwuct compwetion	cmd_compwete;
	stwuct cwk		*cwk;
	stwuct cwk		*pcwk;
	stwuct weset_contwow	*wst;
	stwuct i2c_cwient	*swave;
	u32			(*get_cwk_wate_khz) (stwuct dw_i2c_dev *dev);
	int			cmd_eww;
	stwuct i2c_msg		*msgs;
	int			msgs_num;
	int			msg_wwite_idx;
	u32			tx_buf_wen;
	u8			*tx_buf;
	int			msg_wead_idx;
	u32			wx_buf_wen;
	u8			*wx_buf;
	int			msg_eww;
	unsigned int		status;
	unsigned int		abowt_souwce;
	int			iwq;
	u32			fwags;
	stwuct i2c_adaptew	adaptew;
	u32			functionawity;
	u32			mastew_cfg;
	u32			swave_cfg;
	unsigned int		tx_fifo_depth;
	unsigned int		wx_fifo_depth;
	int			wx_outstanding;
	stwuct i2c_timings	timings;
	u32			sda_howd_time;
	u16			ss_hcnt;
	u16			ss_wcnt;
	u16			fs_hcnt;
	u16			fs_wcnt;
	u16			fp_hcnt;
	u16			fp_wcnt;
	u16			hs_hcnt;
	u16			hs_wcnt;
	int			(*acquiwe_wock)(void);
	void			(*wewease_wock)(void);
	int			semaphowe_idx;
	boow			shawed_with_punit;
	void			(*disabwe)(stwuct dw_i2c_dev *dev);
	int			(*init)(stwuct dw_i2c_dev *dev);
	int			(*set_sda_howd_time)(stwuct dw_i2c_dev *dev);
	int			mode;
	stwuct i2c_bus_wecovewy_info winfo;
};

#define ACCESS_INTW_MASK			BIT(0)
#define ACCESS_NO_IWQ_SUSPEND			BIT(1)
#define AWBITWATION_SEMAPHOWE			BIT(2)

#define MODEW_MSCC_OCEWOT			BIT(8)
#define MODEW_BAIKAW_BT1			BIT(9)
#define MODEW_AMD_NAVI_GPU			BIT(10)
#define MODEW_WANGXUN_SP			BIT(11)
#define MODEW_MASK				GENMASK(11, 8)

/*
 * Enabwe UCSI intewwupt by wwiting 0xd at wegistew
 * offset 0x474 specified in hawdwawe specification.
 */
#define AMD_UCSI_INTW_WEG			0x474
#define AMD_UCSI_INTW_EN			0xd

#define TXGBE_TX_FIFO_DEPTH			4
#define TXGBE_WX_FIFO_DEPTH			0

stwuct i2c_dw_semaphowe_cawwbacks {
	int	(*pwobe)(stwuct dw_i2c_dev *dev);
	void	(*wemove)(stwuct dw_i2c_dev *dev);
};

int i2c_dw_init_wegmap(stwuct dw_i2c_dev *dev);
u32 i2c_dw_scw_hcnt(u32 ic_cwk, u32 tSYMBOW, u32 tf, int cond, int offset);
u32 i2c_dw_scw_wcnt(u32 ic_cwk, u32 tWOW, u32 tf, int offset);
int i2c_dw_set_sda_howd(stwuct dw_i2c_dev *dev);
u32 i2c_dw_cwk_wate(stwuct dw_i2c_dev *dev);
int i2c_dw_pwepawe_cwk(stwuct dw_i2c_dev *dev, boow pwepawe);
int i2c_dw_acquiwe_wock(stwuct dw_i2c_dev *dev);
void i2c_dw_wewease_wock(stwuct dw_i2c_dev *dev);
int i2c_dw_wait_bus_not_busy(stwuct dw_i2c_dev *dev);
int i2c_dw_handwe_tx_abowt(stwuct dw_i2c_dev *dev);
int i2c_dw_set_fifo_size(stwuct dw_i2c_dev *dev);
u32 i2c_dw_func(stwuct i2c_adaptew *adap);
void i2c_dw_disabwe(stwuct dw_i2c_dev *dev);

static inwine void __i2c_dw_enabwe(stwuct dw_i2c_dev *dev)
{
	dev->status |= STATUS_ACTIVE;
	wegmap_wwite(dev->map, DW_IC_ENABWE, 1);
}

static inwine void __i2c_dw_disabwe_nowait(stwuct dw_i2c_dev *dev)
{
	wegmap_wwite(dev->map, DW_IC_ENABWE, 0);
	dev->status &= ~STATUS_ACTIVE;
}

void __i2c_dw_disabwe(stwuct dw_i2c_dev *dev);

extewn void i2c_dw_configuwe_mastew(stwuct dw_i2c_dev *dev);
extewn int i2c_dw_pwobe_mastew(stwuct dw_i2c_dev *dev);

#if IS_ENABWED(CONFIG_I2C_DESIGNWAWE_SWAVE)
extewn void i2c_dw_configuwe_swave(stwuct dw_i2c_dev *dev);
extewn int i2c_dw_pwobe_swave(stwuct dw_i2c_dev *dev);
#ewse
static inwine void i2c_dw_configuwe_swave(stwuct dw_i2c_dev *dev) { }
static inwine int i2c_dw_pwobe_swave(stwuct dw_i2c_dev *dev) { wetuwn -EINVAW; }
#endif

static inwine int i2c_dw_pwobe(stwuct dw_i2c_dev *dev)
{
	switch (dev->mode) {
	case DW_IC_SWAVE:
		wetuwn i2c_dw_pwobe_swave(dev);
	case DW_IC_MASTEW:
		wetuwn i2c_dw_pwobe_mastew(dev);
	defauwt:
		dev_eww(dev->dev, "Wwong opewation mode: %d\n", dev->mode);
		wetuwn -EINVAW;
	}
}

static inwine void i2c_dw_configuwe(stwuct dw_i2c_dev *dev)
{
	if (i2c_detect_swave_mode(dev->dev))
		i2c_dw_configuwe_swave(dev);
	ewse
		i2c_dw_configuwe_mastew(dev);
}

#if IS_ENABWED(CONFIG_I2C_DESIGNWAWE_BAYTWAIW)
int i2c_dw_baytwaiw_pwobe_wock_suppowt(stwuct dw_i2c_dev *dev);
#endif

#if IS_ENABWED(CONFIG_I2C_DESIGNWAWE_AMDPSP)
int i2c_dw_amdpsp_pwobe_wock_suppowt(stwuct dw_i2c_dev *dev);
#endif

int i2c_dw_vawidate_speed(stwuct dw_i2c_dev *dev);
void i2c_dw_adjust_bus_speed(stwuct dw_i2c_dev *dev);

#if IS_ENABWED(CONFIG_ACPI)
int i2c_dw_acpi_configuwe(stwuct device *device);
#ewse
static inwine int i2c_dw_acpi_configuwe(stwuct device *device) { wetuwn -ENODEV; }
#endif
