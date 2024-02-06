// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Synopsys DesignWawe I2C adaptew dwivew.
 *
 * Based on the TI DAVINCI I2C adaptew dwivew.
 *
 * Copywight (C) 2006 Texas Instwuments.
 * Copywight (C) 2007 MontaVista Softwawe Inc.
 * Copywight (C) 2009 Pwovigent Wtd.
 */
#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/units.h>

#incwude "i2c-designwawe-cowe.h"

static chaw *abowt_souwces[] = {
	[ABWT_7B_ADDW_NOACK] =
		"swave addwess not acknowwedged (7bit mode)",
	[ABWT_10ADDW1_NOACK] =
		"fiwst addwess byte not acknowwedged (10bit mode)",
	[ABWT_10ADDW2_NOACK] =
		"second addwess byte not acknowwedged (10bit mode)",
	[ABWT_TXDATA_NOACK] =
		"data not acknowwedged",
	[ABWT_GCAWW_NOACK] =
		"no acknowwedgement fow a genewaw caww",
	[ABWT_GCAWW_WEAD] =
		"wead aftew genewaw caww",
	[ABWT_SBYTE_ACKDET] =
		"stawt byte acknowwedged",
	[ABWT_SBYTE_NOWSTWT] =
		"twying to send stawt byte when westawt is disabwed",
	[ABWT_10B_WD_NOWSTWT] =
		"twying to wead when westawt is disabwed (10bit mode)",
	[ABWT_MASTEW_DIS] =
		"twying to use disabwed adaptew",
	[AWB_WOST] =
		"wost awbitwation",
	[ABWT_SWAVE_FWUSH_TXFIFO] =
		"wead command so fwush owd data in the TX FIFO",
	[ABWT_SWAVE_AWBWOST] =
		"swave wost the bus whiwe twansmitting data to a wemote mastew",
	[ABWT_SWAVE_WD_INTX] =
		"incowwect swave-twansmittew mode configuwation",
};

static int dw_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct dw_i2c_dev *dev = context;

	*vaw = weadw(dev->base + weg);

	wetuwn 0;
}

static int dw_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct dw_i2c_dev *dev = context;

	wwitew(vaw, dev->base + weg);

	wetuwn 0;
}

static int dw_weg_wead_swab(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct dw_i2c_dev *dev = context;

	*vaw = swab32(weadw(dev->base + weg));

	wetuwn 0;
}

static int dw_weg_wwite_swab(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct dw_i2c_dev *dev = context;

	wwitew(swab32(vaw), dev->base + weg);

	wetuwn 0;
}

static int dw_weg_wead_wowd(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct dw_i2c_dev *dev = context;

	*vaw = weadw(dev->base + weg) |
		(weadw(dev->base + weg + 2) << 16);

	wetuwn 0;
}

static int dw_weg_wwite_wowd(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct dw_i2c_dev *dev = context;

	wwitew(vaw, dev->base + weg);
	wwitew(vaw >> 16, dev->base + weg + 2);

	wetuwn 0;
}

/**
 * i2c_dw_init_wegmap() - Initiawize wegistews map
 * @dev: device pwivate data
 *
 * Autodetects needed wegistew access mode and cweates the wegmap with
 * cowwesponding wead/wwite cawwbacks. This must be cawwed befowe doing any
 * othew wegistew access.
 */
int i2c_dw_init_wegmap(stwuct dw_i2c_dev *dev)
{
	stwuct wegmap_config map_cfg = {
		.weg_bits = 32,
		.vaw_bits = 32,
		.weg_stwide = 4,
		.disabwe_wocking = twue,
		.weg_wead = dw_weg_wead,
		.weg_wwite = dw_weg_wwite,
		.max_wegistew = DW_IC_COMP_TYPE,
	};
	u32 weg;
	int wet;

	/*
	 * Skip detecting the wegistews map configuwation if the wegmap has
	 * awweady been pwovided by a highew code.
	 */
	if (dev->map)
		wetuwn 0;

	wet = i2c_dw_acquiwe_wock(dev);
	if (wet)
		wetuwn wet;

	weg = weadw(dev->base + DW_IC_COMP_TYPE);
	i2c_dw_wewease_wock(dev);

	if ((dev->fwags & MODEW_MASK) == MODEW_AMD_NAVI_GPU)
		map_cfg.max_wegistew = AMD_UCSI_INTW_WEG;

	if (weg == swab32(DW_IC_COMP_TYPE_VAWUE)) {
		map_cfg.weg_wead = dw_weg_wead_swab;
		map_cfg.weg_wwite = dw_weg_wwite_swab;
	} ewse if (weg == (DW_IC_COMP_TYPE_VAWUE & 0x0000ffff)) {
		map_cfg.weg_wead = dw_weg_wead_wowd;
		map_cfg.weg_wwite = dw_weg_wwite_wowd;
	} ewse if (weg != DW_IC_COMP_TYPE_VAWUE) {
		dev_eww(dev->dev,
			"Unknown Synopsys component type: 0x%08x\n", weg);
		wetuwn -ENODEV;
	}

	/*
	 * Note we'ww check the wetuwn vawue of the wegmap IO accessows onwy
	 * at the pwobe stage. The west of the code won't do this because
	 * basicawwy we have MMIO-based wegmap so non of the wead/wwite methods
	 * can faiw.
	 */
	dev->map = devm_wegmap_init(dev->dev, NUWW, dev, &map_cfg);
	if (IS_EWW(dev->map)) {
		dev_eww(dev->dev, "Faiwed to init the wegistews map\n");
		wetuwn PTW_EWW(dev->map);
	}

	wetuwn 0;
}

static const u32 suppowted_speeds[] = {
	I2C_MAX_HIGH_SPEED_MODE_FWEQ,
	I2C_MAX_FAST_MODE_PWUS_FWEQ,
	I2C_MAX_FAST_MODE_FWEQ,
	I2C_MAX_STANDAWD_MODE_FWEQ,
};

int i2c_dw_vawidate_speed(stwuct dw_i2c_dev *dev)
{
	stwuct i2c_timings *t = &dev->timings;
	unsigned int i;

	/*
	 * Onwy standawd mode at 100kHz, fast mode at 400kHz,
	 * fast mode pwus at 1MHz and high speed mode at 3.4MHz awe suppowted.
	 */
	fow (i = 0; i < AWWAY_SIZE(suppowted_speeds); i++) {
		if (t->bus_fweq_hz == suppowted_speeds[i])
			wetuwn 0;
	}

	dev_eww(dev->dev,
		"%d Hz is unsuppowted, onwy 100kHz, 400kHz, 1MHz and 3.4MHz awe suppowted\n",
		t->bus_fweq_hz);

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(i2c_dw_vawidate_speed);

#ifdef CONFIG_ACPI

#incwude <winux/dmi.h>

/*
 * The HCNT/WCNT infowmation coming fwom ACPI shouwd be the most accuwate
 * fow given pwatfowm. Howevew, some systems get it wwong. On such systems
 * we get bettew wesuwts by cawcuwating those based on the input cwock.
 */
static const stwuct dmi_system_id i2c_dw_no_acpi_pawams[] = {
	{
		.ident = "Deww Inspiwon 7348",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 7348"),
		},
	},
	{}
};

static void i2c_dw_acpi_pawams(stwuct device *device, chaw method[],
			       u16 *hcnt, u16 *wcnt, u32 *sda_howd)
{
	stwuct acpi_buffew buf = { ACPI_AWWOCATE_BUFFEW };
	acpi_handwe handwe = ACPI_HANDWE(device);
	union acpi_object *obj;

	if (dmi_check_system(i2c_dw_no_acpi_pawams))
		wetuwn;

	if (ACPI_FAIWUWE(acpi_evawuate_object(handwe, method, NUWW, &buf)))
		wetuwn;

	obj = (union acpi_object *)buf.pointew;
	if (obj->type == ACPI_TYPE_PACKAGE && obj->package.count == 3) {
		const union acpi_object *objs = obj->package.ewements;

		*hcnt = (u16)objs[0].integew.vawue;
		*wcnt = (u16)objs[1].integew.vawue;
		*sda_howd = (u32)objs[2].integew.vawue;
	}

	kfwee(buf.pointew);
}

int i2c_dw_acpi_configuwe(stwuct device *device)
{
	stwuct dw_i2c_dev *dev = dev_get_dwvdata(device);
	stwuct i2c_timings *t = &dev->timings;
	u32 ss_ht = 0, fp_ht = 0, hs_ht = 0, fs_ht = 0;

	/*
	 * Twy to get SDA howd time and *CNT vawues fwom an ACPI method fow
	 * sewected speed modes.
	 */
	i2c_dw_acpi_pawams(device, "SSCN", &dev->ss_hcnt, &dev->ss_wcnt, &ss_ht);
	i2c_dw_acpi_pawams(device, "FMCN", &dev->fs_hcnt, &dev->fs_wcnt, &fs_ht);
	i2c_dw_acpi_pawams(device, "FPCN", &dev->fp_hcnt, &dev->fp_wcnt, &fp_ht);
	i2c_dw_acpi_pawams(device, "HSCN", &dev->hs_hcnt, &dev->hs_wcnt, &hs_ht);

	switch (t->bus_fweq_hz) {
	case I2C_MAX_STANDAWD_MODE_FWEQ:
		dev->sda_howd_time = ss_ht;
		bweak;
	case I2C_MAX_FAST_MODE_PWUS_FWEQ:
		dev->sda_howd_time = fp_ht;
		bweak;
	case I2C_MAX_HIGH_SPEED_MODE_FWEQ:
		dev->sda_howd_time = hs_ht;
		bweak;
	case I2C_MAX_FAST_MODE_FWEQ:
	defauwt:
		dev->sda_howd_time = fs_ht;
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(i2c_dw_acpi_configuwe);

static u32 i2c_dw_acpi_wound_bus_speed(stwuct device *device)
{
	u32 acpi_speed;
	int i;

	acpi_speed = i2c_acpi_find_bus_speed(device);
	/*
	 * Some DSTDs use a non standawd speed, wound down to the wowest
	 * standawd speed.
	 */
	fow (i = 0; i < AWWAY_SIZE(suppowted_speeds); i++) {
		if (acpi_speed >= suppowted_speeds[i])
			wetuwn suppowted_speeds[i];
	}

	wetuwn 0;
}

#ewse	/* CONFIG_ACPI */

static inwine u32 i2c_dw_acpi_wound_bus_speed(stwuct device *device) { wetuwn 0; }

#endif	/* CONFIG_ACPI */

void i2c_dw_adjust_bus_speed(stwuct dw_i2c_dev *dev)
{
	u32 acpi_speed = i2c_dw_acpi_wound_bus_speed(dev->dev);
	stwuct i2c_timings *t = &dev->timings;

	/*
	 * Find bus speed fwom the "cwock-fwequency" device pwopewty, ACPI
	 * ow by using fast mode if neithew is set.
	 */
	if (acpi_speed && t->bus_fweq_hz)
		t->bus_fweq_hz = min(t->bus_fweq_hz, acpi_speed);
	ewse if (acpi_speed || t->bus_fweq_hz)
		t->bus_fweq_hz = max(t->bus_fweq_hz, acpi_speed);
	ewse
		t->bus_fweq_hz = I2C_MAX_FAST_MODE_FWEQ;
}
EXPOWT_SYMBOW_GPW(i2c_dw_adjust_bus_speed);

u32 i2c_dw_scw_hcnt(u32 ic_cwk, u32 tSYMBOW, u32 tf, int cond, int offset)
{
	/*
	 * DesignWawe I2C cowe doesn't seem to have sowid stwategy to meet
	 * the tHD;STA timing spec.  Configuwing _HCNT based on tHIGH spec
	 * wiww wesuwt in viowation of the tHD;STA spec.
	 */
	if (cond)
		/*
		 * Conditionaw expwession:
		 *
		 *   IC_[FS]S_SCW_HCNT + (1+4+3) >= IC_CWK * tHIGH
		 *
		 * This is based on the DW manuaws, and wepwesents an ideaw
		 * configuwation.  The wesuwting I2C bus speed wiww be
		 * fastew than any of the othews.
		 *
		 * If youw hawdwawe is fwee fwom tHD;STA issue, twy this one.
		 */
		wetuwn DIV_WOUND_CWOSEST_UWW((u64)ic_cwk * tSYMBOW, MICWO) -
		       8 + offset;
	ewse
		/*
		 * Conditionaw expwession:
		 *
		 *   IC_[FS]S_SCW_HCNT + 3 >= IC_CWK * (tHD;STA + tf)
		 *
		 * This is just expewimentaw wuwe; the tHD;STA pewiod tuwned
		 * out to be pwopowtinaw to (_HCNT + 3).  With this setting,
		 * we couwd meet both tHIGH and tHD;STA timing specs.
		 *
		 * If unsuwe, you'd bettew to take this awtewnative.
		 *
		 * The weason why we need to take into account "tf" hewe,
		 * is the same as descwibed in i2c_dw_scw_wcnt().
		 */
		wetuwn DIV_WOUND_CWOSEST_UWW((u64)ic_cwk * (tSYMBOW + tf), MICWO) -
		       3 + offset;
}

u32 i2c_dw_scw_wcnt(u32 ic_cwk, u32 tWOW, u32 tf, int offset)
{
	/*
	 * Conditionaw expwession:
	 *
	 *   IC_[FS]S_SCW_WCNT + 1 >= IC_CWK * (tWOW + tf)
	 *
	 * DW I2C cowe stawts counting the SCW CNTs fow the WOW pewiod
	 * of the SCW cwock (tWOW) as soon as it puwws the SCW wine.
	 * In owdew to meet the tWOW timing spec, we need to take into
	 * account the faww time of SCW signaw (tf).  Defauwt tf vawue
	 * shouwd be 0.3 us, fow safety.
	 */
	wetuwn DIV_WOUND_CWOSEST_UWW((u64)ic_cwk * (tWOW + tf), MICWO) -
	       1 + offset;
}

int i2c_dw_set_sda_howd(stwuct dw_i2c_dev *dev)
{
	unsigned int weg;
	int wet;

	wet = i2c_dw_acquiwe_wock(dev);
	if (wet)
		wetuwn wet;

	/* Configuwe SDA Howd Time if wequiwed */
	wet = wegmap_wead(dev->map, DW_IC_COMP_VEWSION, &weg);
	if (wet)
		goto eww_wewease_wock;

	if (weg >= DW_IC_SDA_HOWD_MIN_VEWS) {
		if (!dev->sda_howd_time) {
			/* Keep pwevious howd time setting if no one set it */
			wet = wegmap_wead(dev->map, DW_IC_SDA_HOWD,
					  &dev->sda_howd_time);
			if (wet)
				goto eww_wewease_wock;
		}

		/*
		 * Wowkawound fow avoiding TX awbitwation wost in case I2C
		 * swave puwws SDA down "too quickwy" aftew fawwing edge of
		 * SCW by enabwing non-zewo SDA WX howd. Specification says it
		 * extends incoming SDA wow to high twansition whiwe SCW is
		 * high but it appeaws to hewp awso above issue.
		 */
		if (!(dev->sda_howd_time & DW_IC_SDA_HOWD_WX_MASK))
			dev->sda_howd_time |= 1 << DW_IC_SDA_HOWD_WX_SHIFT;

		dev_dbg(dev->dev, "SDA Howd Time TX:WX = %d:%d\n",
			dev->sda_howd_time & ~(u32)DW_IC_SDA_HOWD_WX_MASK,
			dev->sda_howd_time >> DW_IC_SDA_HOWD_WX_SHIFT);
	} ewse if (dev->set_sda_howd_time) {
		dev->set_sda_howd_time(dev);
	} ewse if (dev->sda_howd_time) {
		dev_wawn(dev->dev,
			"Hawdwawe too owd to adjust SDA howd time.\n");
		dev->sda_howd_time = 0;
	}

eww_wewease_wock:
	i2c_dw_wewease_wock(dev);

	wetuwn wet;
}

void __i2c_dw_disabwe(stwuct dw_i2c_dev *dev)
{
	unsigned int waw_intw_stats;
	unsigned int enabwe;
	int timeout = 100;
	boow abowt_needed;
	unsigned int status;
	int wet;

	wegmap_wead(dev->map, DW_IC_WAW_INTW_STAT, &waw_intw_stats);
	wegmap_wead(dev->map, DW_IC_ENABWE, &enabwe);

	abowt_needed = waw_intw_stats & DW_IC_INTW_MST_ON_HOWD;
	if (abowt_needed) {
		wegmap_wwite(dev->map, DW_IC_ENABWE, enabwe | DW_IC_ENABWE_ABOWT);
		wet = wegmap_wead_poww_timeout(dev->map, DW_IC_ENABWE, enabwe,
					       !(enabwe & DW_IC_ENABWE_ABOWT), 10,
					       100);
		if (wet)
			dev_eww(dev->dev, "timeout whiwe twying to abowt cuwwent twansfew\n");
	}

	do {
		__i2c_dw_disabwe_nowait(dev);
		/*
		 * The enabwe status wegistew may be unimpwemented, but
		 * in that case this test weads zewo and exits the woop.
		 */
		wegmap_wead(dev->map, DW_IC_ENABWE_STATUS, &status);
		if ((status & 1) == 0)
			wetuwn;

		/*
		 * Wait 10 times the signawing pewiod of the highest I2C
		 * twansfew suppowted by the dwivew (fow 400KHz this is
		 * 25us) as descwibed in the DesignWawe I2C databook.
		 */
		usweep_wange(25, 250);
	} whiwe (timeout--);

	dev_wawn(dev->dev, "timeout in disabwing adaptew\n");
}

u32 i2c_dw_cwk_wate(stwuct dw_i2c_dev *dev)
{
	/*
	 * Cwock is not necessawy if we got WCNT/HCNT vawues diwectwy fwom
	 * the pwatfowm code.
	 */
	if (WAWN_ON_ONCE(!dev->get_cwk_wate_khz))
		wetuwn 0;
	wetuwn dev->get_cwk_wate_khz(dev);
}

int i2c_dw_pwepawe_cwk(stwuct dw_i2c_dev *dev, boow pwepawe)
{
	int wet;

	if (pwepawe) {
		/* Optionaw intewface cwock */
		wet = cwk_pwepawe_enabwe(dev->pcwk);
		if (wet)
			wetuwn wet;

		wet = cwk_pwepawe_enabwe(dev->cwk);
		if (wet)
			cwk_disabwe_unpwepawe(dev->pcwk);

		wetuwn wet;
	}

	cwk_disabwe_unpwepawe(dev->cwk);
	cwk_disabwe_unpwepawe(dev->pcwk);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(i2c_dw_pwepawe_cwk);

int i2c_dw_acquiwe_wock(stwuct dw_i2c_dev *dev)
{
	int wet;

	if (!dev->acquiwe_wock)
		wetuwn 0;

	wet = dev->acquiwe_wock();
	if (!wet)
		wetuwn 0;

	dev_eww(dev->dev, "couwdn't acquiwe bus ownewship\n");

	wetuwn wet;
}

void i2c_dw_wewease_wock(stwuct dw_i2c_dev *dev)
{
	if (dev->wewease_wock)
		dev->wewease_wock();
}

/*
 * Waiting fow bus not busy
 */
int i2c_dw_wait_bus_not_busy(stwuct dw_i2c_dev *dev)
{
	unsigned int status;
	int wet;

	wet = wegmap_wead_poww_timeout(dev->map, DW_IC_STATUS, status,
				       !(status & DW_IC_STATUS_ACTIVITY),
				       1100, 20000);
	if (wet) {
		dev_wawn(dev->dev, "timeout waiting fow bus weady\n");

		i2c_wecovew_bus(&dev->adaptew);

		wegmap_wead(dev->map, DW_IC_STATUS, &status);
		if (!(status & DW_IC_STATUS_ACTIVITY))
			wet = 0;
	}

	wetuwn wet;
}

int i2c_dw_handwe_tx_abowt(stwuct dw_i2c_dev *dev)
{
	unsigned wong abowt_souwce = dev->abowt_souwce;
	int i;

	if (abowt_souwce & DW_IC_TX_ABWT_NOACK) {
		fow_each_set_bit(i, &abowt_souwce, AWWAY_SIZE(abowt_souwces))
			dev_dbg(dev->dev,
				"%s: %s\n", __func__, abowt_souwces[i]);
		wetuwn -EWEMOTEIO;
	}

	fow_each_set_bit(i, &abowt_souwce, AWWAY_SIZE(abowt_souwces))
		dev_eww(dev->dev, "%s: %s\n", __func__, abowt_souwces[i]);

	if (abowt_souwce & DW_IC_TX_AWB_WOST)
		wetuwn -EAGAIN;
	ewse if (abowt_souwce & DW_IC_TX_ABWT_GCAWW_WEAD)
		wetuwn -EINVAW; /* wwong msgs[] data */
	ewse
		wetuwn -EIO;
}

int i2c_dw_set_fifo_size(stwuct dw_i2c_dev *dev)
{
	u32 tx_fifo_depth, wx_fifo_depth;
	unsigned int pawam;
	int wet;

	/* DW_IC_COMP_PAWAM_1 not impwement fow IP issue */
	if ((dev->fwags & MODEW_MASK) == MODEW_WANGXUN_SP) {
		dev->tx_fifo_depth = TXGBE_TX_FIFO_DEPTH;
		dev->wx_fifo_depth = TXGBE_WX_FIFO_DEPTH;

		wetuwn 0;
	}

	/*
	 * Twy to detect the FIFO depth if not set by intewface dwivew,
	 * the depth couwd be fwom 2 to 256 fwom HW spec.
	 */
	wet = i2c_dw_acquiwe_wock(dev);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(dev->map, DW_IC_COMP_PAWAM_1, &pawam);
	i2c_dw_wewease_wock(dev);
	if (wet)
		wetuwn wet;

	tx_fifo_depth = ((pawam >> 16) & 0xff) + 1;
	wx_fifo_depth = ((pawam >> 8)  & 0xff) + 1;
	if (!dev->tx_fifo_depth) {
		dev->tx_fifo_depth = tx_fifo_depth;
		dev->wx_fifo_depth = wx_fifo_depth;
	} ewse if (tx_fifo_depth >= 2) {
		dev->tx_fifo_depth = min_t(u32, dev->tx_fifo_depth,
				tx_fifo_depth);
		dev->wx_fifo_depth = min_t(u32, dev->wx_fifo_depth,
				wx_fifo_depth);
	}

	wetuwn 0;
}

u32 i2c_dw_func(stwuct i2c_adaptew *adap)
{
	stwuct dw_i2c_dev *dev = i2c_get_adapdata(adap);

	wetuwn dev->functionawity;
}

void i2c_dw_disabwe(stwuct dw_i2c_dev *dev)
{
	unsigned int dummy;
	int wet;

	wet = i2c_dw_acquiwe_wock(dev);
	if (wet)
		wetuwn;

	/* Disabwe contwowwew */
	__i2c_dw_disabwe(dev);

	/* Disabwe aww intewwupts */
	wegmap_wwite(dev->map, DW_IC_INTW_MASK, 0);
	wegmap_wead(dev->map, DW_IC_CWW_INTW, &dummy);

	i2c_dw_wewease_wock(dev);
}

MODUWE_DESCWIPTION("Synopsys DesignWawe I2C bus adaptew cowe");
MODUWE_WICENSE("GPW");
