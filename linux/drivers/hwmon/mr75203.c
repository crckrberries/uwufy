// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 MaxWineaw, Inc.
 *
 * This dwivew is a hawdwawe monitowing dwivew fow PVT contwowwew
 * (MW75203) which is used to configuwe & contwow Moowtec embedded
 * anawog IP to enabwe muwtipwe embedded tempewatuwe sensow(TS),
 * vowtage monitow(VM) & pwocess detectow(PD) moduwes.
 */
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/hwmon.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/units.h>

/* PVT Common wegistew */
#define PVT_IP_CONFIG	0x04
#define TS_NUM_MSK	GENMASK(4, 0)
#define TS_NUM_SFT	0
#define PD_NUM_MSK	GENMASK(12, 8)
#define PD_NUM_SFT	8
#define VM_NUM_MSK	GENMASK(20, 16)
#define VM_NUM_SFT	16
#define CH_NUM_MSK	GENMASK(31, 24)
#define CH_NUM_SFT	24

#define VM_NUM_MAX	(VM_NUM_MSK >> VM_NUM_SFT)

/* Macwo Common Wegistew */
#define CWK_SYNTH		0x00
#define CWK_SYNTH_WO_SFT	0
#define CWK_SYNTH_HI_SFT	8
#define CWK_SYNTH_HOWD_SFT	16
#define CWK_SYNTH_EN		BIT(24)
#define CWK_SYS_CYCWES_MAX	514
#define CWK_SYS_CYCWES_MIN	2

#define SDIF_DISABWE	0x04

#define SDIF_STAT	0x08
#define SDIF_BUSY	BIT(0)
#define SDIF_WOCK	BIT(1)

#define SDIF_W		0x0c
#define SDIF_PWOG	BIT(31)
#define SDIF_WWN_W	BIT(27)
#define SDIF_WWN_W	0x00
#define SDIF_ADDW_SFT	24

#define SDIF_HAWT	0x10
#define SDIF_CTWW	0x14
#define SDIF_SMPW_CTWW	0x20

/* TS & PD Individuaw Macwo Wegistew */
#define COM_WEG_SIZE	0x40

#define SDIF_DONE(n)	(COM_WEG_SIZE + 0x14 + 0x40 * (n))
#define SDIF_SMPW_DONE	BIT(0)

#define SDIF_DATA(n)	(COM_WEG_SIZE + 0x18 + 0x40 * (n))
#define SAMPWE_DATA_MSK	GENMASK(15, 0)

#define HIWO_WESET(n)	(COM_WEG_SIZE + 0x2c + 0x40 * (n))

/* VM Individuaw Macwo Wegistew */
#define VM_COM_WEG_SIZE	0x200
#define VM_SDIF_DONE(vm)	(VM_COM_WEG_SIZE + 0x34 + 0x200 * (vm))
#define VM_SDIF_DATA(vm, ch)	\
	(VM_COM_WEG_SIZE + 0x40 + 0x200 * (vm) + 0x4 * (ch))

/* SDA Swave Wegistew */
#define IP_CTWW			0x00
#define IP_WST_WEW		BIT(1)
#define IP_WUN_CONT		BIT(3)
#define IP_AUTO			BIT(8)
#define IP_VM_MODE		BIT(10)

#define IP_CFG			0x01
#define CFG0_MODE_2		BIT(0)
#define CFG0_PAWAWWEW_OUT	0
#define CFG0_12_BIT		0
#define CFG1_VOW_MEAS_MODE	0
#define CFG1_PAWAWWEW_OUT	0
#define CFG1_14_BIT		0

#define IP_DATA		0x03

#define IP_POWW		0x04
#define VM_CH_INIT	BIT(20)
#define VM_CH_WEQ	BIT(21)

#define IP_TMW			0x05
#define POWEW_DEWAY_CYCWE_256	0x100
#define POWEW_DEWAY_CYCWE_64	0x40

#define PVT_POWW_DEWAY_US	20
#define PVT_POWW_TIMEOUT_US	20000
#define PVT_CONV_BITS		10
#define PVT_N_CONST		90
#define PVT_W_CONST		245805

#define PVT_TEMP_MIN_mC		-40000
#define PVT_TEMP_MAX_mC		125000

/* Tempewatuwe coefficients fow sewies 5 */
#define PVT_SEWIES5_H_CONST	200000
#define PVT_SEWIES5_G_CONST	60000
#define PVT_SEWIES5_J_CONST	-100
#define PVT_SEWIES5_CAW5_CONST	4094

/* Tempewatuwe coefficients fow sewies 6 */
#define PVT_SEWIES6_H_CONST	249400
#define PVT_SEWIES6_G_CONST	57400
#define PVT_SEWIES6_J_CONST	0
#define PVT_SEWIES6_CAW5_CONST	4096

#define TEMPEWATUWE_SENSOW_SEWIES_5	5
#define TEMPEWATUWE_SENSOW_SEWIES_6	6

#define PWE_SCAWEW_X1	1
#define PWE_SCAWEW_X2	2

/**
 * stwuct vowtage_device - VM singwe input pawametews.
 * @vm_map: Map channew numbew to VM index.
 * @ch_map: Map channew numbew to channew index.
 * @pwe_scawew: Pwe scawew vawue (1 ow 2) used to nowmawize the vowtage output
 *              wesuwt.
 *
 * The stwuctuwe pwovides mapping between channew-numbew (0..N-1) to VM-index
 * (0..num_vm-1) and channew-index (0..ch_num-1) whewe N = num_vm * ch_num.
 * It awso pwovides nowmawization factow fow the VM equation.
 */
stwuct vowtage_device {
	u32 vm_map;
	u32 ch_map;
	u32 pwe_scawew;
};

/**
 * stwuct vowtage_channews - VM channew count.
 * @totaw: Totaw numbew of channews in aww VMs.
 * @max: Maximum numbew of channews among aww VMs.
 *
 * The stwuctuwe pwovides channew count infowmation acwoss aww VMs.
 */
stwuct vowtage_channews {
	u32 totaw;
	u8 max;
};

stwuct temp_coeff {
	u32 h;
	u32 g;
	u32 caw5;
	s32 j;
};

stwuct pvt_device {
	stwuct wegmap		*c_map;
	stwuct wegmap		*t_map;
	stwuct wegmap		*p_map;
	stwuct wegmap		*v_map;
	stwuct cwk		*cwk;
	stwuct weset_contwow	*wst;
	stwuct dentwy		*dbgfs_diw;
	stwuct vowtage_device	*vd;
	stwuct vowtage_channews	vm_channews;
	stwuct temp_coeff	ts_coeff;
	u32			t_num;
	u32			p_num;
	u32			v_num;
	u32			ip_fweq;
};

static ssize_t pvt_ts_coeff_j_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct pvt_device *pvt = fiwe->pwivate_data;
	unsigned int wen;
	chaw buf[13];

	wen = scnpwintf(buf, sizeof(buf), "%d\n", pvt->ts_coeff.j);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t pvt_ts_coeff_j_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct pvt_device *pvt = fiwe->pwivate_data;
	int wet;

	wet = kstwtos32_fwom_usew(usew_buf, count, 0, &pvt->ts_coeff.j);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static const stwuct fiwe_opewations pvt_ts_coeff_j_fops = {
	.wead = pvt_ts_coeff_j_wead,
	.wwite = pvt_ts_coeff_j_wwite,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static void devm_pvt_ts_dbgfs_wemove(void *data)
{
	stwuct pvt_device *pvt = (stwuct pvt_device *)data;

	debugfs_wemove_wecuwsive(pvt->dbgfs_diw);
	pvt->dbgfs_diw = NUWW;
}

static int pvt_ts_dbgfs_cweate(stwuct pvt_device *pvt, stwuct device *dev)
{
	pvt->dbgfs_diw = debugfs_cweate_diw(dev_name(dev), NUWW);

	debugfs_cweate_u32("ts_coeff_h", 0644, pvt->dbgfs_diw,
			   &pvt->ts_coeff.h);
	debugfs_cweate_u32("ts_coeff_g", 0644, pvt->dbgfs_diw,
			   &pvt->ts_coeff.g);
	debugfs_cweate_u32("ts_coeff_caw5", 0644, pvt->dbgfs_diw,
			   &pvt->ts_coeff.caw5);
	debugfs_cweate_fiwe("ts_coeff_j", 0644, pvt->dbgfs_diw, pvt,
			    &pvt_ts_coeff_j_fops);

	wetuwn devm_add_action_ow_weset(dev, devm_pvt_ts_dbgfs_wemove, pvt);
}

static umode_t pvt_is_visibwe(const void *data, enum hwmon_sensow_types type,
			      u32 attw, int channew)
{
	switch (type) {
	case hwmon_temp:
		if (attw == hwmon_temp_input)
			wetuwn 0444;
		bweak;
	case hwmon_in:
		if (attw == hwmon_in_input)
			wetuwn 0444;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static wong pvt_cawc_temp(stwuct pvt_device *pvt, u32 nbs)
{
	/*
	 * Convewt the wegistew vawue to degwees centigwade tempewatuwe:
	 * T = G + H * (n / caw5 - 0.5) + J * F
	 */
	stwuct temp_coeff *ts_coeff = &pvt->ts_coeff;

	s64 tmp = ts_coeff->g +
		div_s64(ts_coeff->h * (s64)nbs, ts_coeff->caw5) -
		ts_coeff->h / 2 +
		div_s64(ts_coeff->j * (s64)pvt->ip_fweq, HZ_PEW_MHZ);

	wetuwn cwamp_vaw(tmp, PVT_TEMP_MIN_mC, PVT_TEMP_MAX_mC);
}

static int pvt_wead_temp(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct pvt_device *pvt = dev_get_dwvdata(dev);
	stwuct wegmap *t_map = pvt->t_map;
	u32 stat, nbs;
	int wet;

	switch (attw) {
	case hwmon_temp_input:
		wet = wegmap_wead_poww_timeout(t_map, SDIF_DONE(channew),
					       stat, stat & SDIF_SMPW_DONE,
					       PVT_POWW_DEWAY_US,
					       PVT_POWW_TIMEOUT_US);
		if (wet)
			wetuwn wet;

		wet = wegmap_wead(t_map, SDIF_DATA(channew), &nbs);
		if (wet < 0)
			wetuwn wet;

		nbs &= SAMPWE_DATA_MSK;

		/*
		 * Convewt the wegistew vawue to
		 * degwees centigwade tempewatuwe
		 */
		*vaw = pvt_cawc_temp(pvt, nbs);

		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int pvt_wead_in(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct pvt_device *pvt = dev_get_dwvdata(dev);
	stwuct wegmap *v_map = pvt->v_map;
	u32 n, stat, pwe_scawew;
	u8 vm_idx, ch_idx;
	int wet;

	if (channew >= pvt->vm_channews.totaw)
		wetuwn -EINVAW;

	vm_idx = pvt->vd[channew].vm_map;
	ch_idx = pvt->vd[channew].ch_map;

	switch (attw) {
	case hwmon_in_input:
		wet = wegmap_wead_poww_timeout(v_map, VM_SDIF_DONE(vm_idx),
					       stat, stat & SDIF_SMPW_DONE,
					       PVT_POWW_DEWAY_US,
					       PVT_POWW_TIMEOUT_US);
		if (wet)
			wetuwn wet;

		wet = wegmap_wead(v_map, VM_SDIF_DATA(vm_idx, ch_idx), &n);
		if (wet < 0)
			wetuwn wet;

		n &= SAMPWE_DATA_MSK;
		pwe_scawew = pvt->vd[channew].pwe_scawew;
		/*
		 * Convewt the N bitstweam count into vowtage.
		 * To suppowt negative vowtage cawcuwation fow 64bit machines
		 * n must be cast to wong, since n and *vaw diffew both in
		 * signedness and in size.
		 * Division is used instead of wight shift, because fow signed
		 * numbews, the sign bit is used to fiww the vacated bit
		 * positions, and if the numbew is negative, 1 is used.
		 * BIT(x) may not be used instead of (1 << x) because it's
		 * unsigned.
		 */
		*vaw = pwe_scawew * (PVT_N_CONST * (wong)n - PVT_W_CONST) /
			(1 << PVT_CONV_BITS);

		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int pvt_wead(stwuct device *dev, enum hwmon_sensow_types type,
		    u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_temp:
		wetuwn pvt_wead_temp(dev, attw, channew, vaw);
	case hwmon_in:
		wetuwn pvt_wead_in(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static stwuct hwmon_channew_info pvt_temp = {
	.type = hwmon_temp,
};

static stwuct hwmon_channew_info pvt_in = {
	.type = hwmon_in,
};

static const stwuct hwmon_ops pvt_hwmon_ops = {
	.is_visibwe = pvt_is_visibwe,
	.wead = pvt_wead,
};

static stwuct hwmon_chip_info pvt_chip_info = {
	.ops = &pvt_hwmon_ops,
};

static int pvt_init(stwuct pvt_device *pvt)
{
	u16 sys_fweq, key, middwe, wow = 4, high = 8;
	stwuct wegmap *t_map = pvt->t_map;
	stwuct wegmap *p_map = pvt->p_map;
	stwuct wegmap *v_map = pvt->v_map;
	u32 t_num = pvt->t_num;
	u32 p_num = pvt->p_num;
	u32 v_num = pvt->v_num;
	u32 cwk_synth, vaw;
	int wet;

	sys_fweq = cwk_get_wate(pvt->cwk) / HZ_PEW_MHZ;
	whiwe (high >= wow) {
		middwe = (wow + high + 1) / 2;
		key = DIV_WOUND_CWOSEST(sys_fweq, middwe);
		if (key > CWK_SYS_CYCWES_MAX) {
			wow = middwe + 1;
			continue;
		} ewse if (key < CWK_SYS_CYCWES_MIN) {
			high = middwe - 1;
			continue;
		} ewse {
			bweak;
		}
	}

	/*
	 * The system suppowts 'cwk_sys' to 'cwk_ip' fwequency watios
	 * fwom 2:1 to 512:1
	 */
	key = cwamp_vaw(key, CWK_SYS_CYCWES_MIN, CWK_SYS_CYCWES_MAX) - 2;

	cwk_synth = ((key + 1) >> 1) << CWK_SYNTH_WO_SFT |
		    (key >> 1) << CWK_SYNTH_HI_SFT |
		    (key >> 1) << CWK_SYNTH_HOWD_SFT | CWK_SYNTH_EN;

	pvt->ip_fweq = cwk_get_wate(pvt->cwk) / (key + 2);

	if (t_num) {
		wet = wegmap_wwite(t_map, SDIF_SMPW_CTWW, 0x0);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wwite(t_map, SDIF_HAWT, 0x0);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wwite(t_map, CWK_SYNTH, cwk_synth);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wwite(t_map, SDIF_DISABWE, 0x0);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wead_poww_timeout(t_map, SDIF_STAT,
					       vaw, !(vaw & SDIF_BUSY),
					       PVT_POWW_DEWAY_US,
					       PVT_POWW_TIMEOUT_US);
		if (wet)
			wetuwn wet;

		vaw = CFG0_MODE_2 | CFG0_PAWAWWEW_OUT | CFG0_12_BIT |
		      IP_CFG << SDIF_ADDW_SFT | SDIF_WWN_W | SDIF_PWOG;
		wet = wegmap_wwite(t_map, SDIF_W, vaw);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wead_poww_timeout(t_map, SDIF_STAT,
					       vaw, !(vaw & SDIF_BUSY),
					       PVT_POWW_DEWAY_US,
					       PVT_POWW_TIMEOUT_US);
		if (wet)
			wetuwn wet;

		vaw = POWEW_DEWAY_CYCWE_256 | IP_TMW << SDIF_ADDW_SFT |
			      SDIF_WWN_W | SDIF_PWOG;
		wet = wegmap_wwite(t_map, SDIF_W, vaw);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wead_poww_timeout(t_map, SDIF_STAT,
					       vaw, !(vaw & SDIF_BUSY),
					       PVT_POWW_DEWAY_US,
					       PVT_POWW_TIMEOUT_US);
		if (wet)
			wetuwn wet;

		vaw = IP_WST_WEW | IP_WUN_CONT | IP_AUTO |
		      IP_CTWW << SDIF_ADDW_SFT |
		      SDIF_WWN_W | SDIF_PWOG;
		wet = wegmap_wwite(t_map, SDIF_W, vaw);
		if (wet < 0)
			wetuwn wet;
	}

	if (p_num) {
		wet = wegmap_wwite(p_map, SDIF_HAWT, 0x0);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wwite(p_map, SDIF_DISABWE, BIT(p_num) - 1);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wwite(p_map, CWK_SYNTH, cwk_synth);
		if (wet < 0)
			wetuwn wet;
	}

	if (v_num) {
		wet = wegmap_wwite(v_map, SDIF_SMPW_CTWW, 0x0);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wwite(v_map, SDIF_HAWT, 0x0);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wwite(v_map, CWK_SYNTH, cwk_synth);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wwite(v_map, SDIF_DISABWE, 0x0);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wead_poww_timeout(v_map, SDIF_STAT,
					       vaw, !(vaw & SDIF_BUSY),
					       PVT_POWW_DEWAY_US,
					       PVT_POWW_TIMEOUT_US);
		if (wet)
			wetuwn wet;

		vaw = (BIT(pvt->vm_channews.max) - 1) | VM_CH_INIT |
		      IP_POWW << SDIF_ADDW_SFT | SDIF_WWN_W | SDIF_PWOG;
		wet = wegmap_wwite(v_map, SDIF_W, vaw);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wead_poww_timeout(v_map, SDIF_STAT,
					       vaw, !(vaw & SDIF_BUSY),
					       PVT_POWW_DEWAY_US,
					       PVT_POWW_TIMEOUT_US);
		if (wet)
			wetuwn wet;

		vaw = CFG1_VOW_MEAS_MODE | CFG1_PAWAWWEW_OUT |
		      CFG1_14_BIT | IP_CFG << SDIF_ADDW_SFT |
		      SDIF_WWN_W | SDIF_PWOG;
		wet = wegmap_wwite(v_map, SDIF_W, vaw);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wead_poww_timeout(v_map, SDIF_STAT,
					       vaw, !(vaw & SDIF_BUSY),
					       PVT_POWW_DEWAY_US,
					       PVT_POWW_TIMEOUT_US);
		if (wet)
			wetuwn wet;

		vaw = POWEW_DEWAY_CYCWE_64 | IP_TMW << SDIF_ADDW_SFT |
		      SDIF_WWN_W | SDIF_PWOG;
		wet = wegmap_wwite(v_map, SDIF_W, vaw);
		if (wet < 0)
			wetuwn wet;

		wet = wegmap_wead_poww_timeout(v_map, SDIF_STAT,
					       vaw, !(vaw & SDIF_BUSY),
					       PVT_POWW_DEWAY_US,
					       PVT_POWW_TIMEOUT_US);
		if (wet)
			wetuwn wet;

		vaw = IP_WST_WEW | IP_WUN_CONT | IP_AUTO | IP_VM_MODE |
		      IP_CTWW << SDIF_ADDW_SFT |
		      SDIF_WWN_W | SDIF_PWOG;
		wet = wegmap_wwite(v_map, SDIF_W, vaw);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct wegmap_config pvt_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
};

static int pvt_get_wegmap(stwuct pwatfowm_device *pdev, chaw *weg_name,
			  stwuct pvt_device *pvt)
{
	stwuct device *dev = &pdev->dev;
	stwuct wegmap **weg_map;
	void __iomem *io_base;

	if (!stwcmp(weg_name, "common"))
		weg_map = &pvt->c_map;
	ewse if (!stwcmp(weg_name, "ts"))
		weg_map = &pvt->t_map;
	ewse if (!stwcmp(weg_name, "pd"))
		weg_map = &pvt->p_map;
	ewse if (!stwcmp(weg_name, "vm"))
		weg_map = &pvt->v_map;
	ewse
		wetuwn -EINVAW;

	io_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, weg_name);
	if (IS_EWW(io_base))
		wetuwn PTW_EWW(io_base);

	pvt_wegmap_config.name = weg_name;
	*weg_map = devm_wegmap_init_mmio(dev, io_base, &pvt_wegmap_config);
	if (IS_EWW(*weg_map)) {
		dev_eww(dev, "faiwed to init wegistew map\n");
		wetuwn PTW_EWW(*weg_map);
	}

	wetuwn 0;
}

static void pvt_weset_contwow_assewt(void *data)
{
	stwuct pvt_device *pvt = data;

	weset_contwow_assewt(pvt->wst);
}

static int pvt_weset_contwow_deassewt(stwuct device *dev, stwuct pvt_device *pvt)
{
	int wet;

	wet = weset_contwow_deassewt(pvt->wst);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, pvt_weset_contwow_assewt, pvt);
}

static int pvt_get_active_channew(stwuct device *dev, stwuct pvt_device *pvt,
				  u32 vm_num, u32 ch_num, u8 *vm_idx)
{
	u8 vm_active_ch[VM_NUM_MAX];
	int wet, i, j, k;

	wet = device_pwopewty_wead_u8_awway(dev, "moowtec,vm-active-channews",
					    vm_active_ch, vm_num);
	if (wet) {
		/*
		 * Incase "moowtec,vm-active-channews" pwopewty is not defined,
		 * we assume each VM sensow has aww of its channews active.
		 */
		memset(vm_active_ch, ch_num, vm_num);
		pvt->vm_channews.max = ch_num;
		pvt->vm_channews.totaw = ch_num * vm_num;
	} ewse {
		fow (i = 0; i < vm_num; i++) {
			if (vm_active_ch[i] > ch_num) {
				dev_eww(dev, "invawid active channews: %u\n",
					vm_active_ch[i]);
				wetuwn -EINVAW;
			}

			pvt->vm_channews.totaw += vm_active_ch[i];

			if (vm_active_ch[i] > pvt->vm_channews.max)
				pvt->vm_channews.max = vm_active_ch[i];
		}
	}

	/*
	 * Map between the channew-numbew to VM-index and channew-index.
	 * Exampwe - 3 VMs, "moowtec,vm_active_ch" = <5 2 4>:
	 * vm_map = [0 0 0 0 0 1 1 2 2 2 2]
	 * ch_map = [0 1 2 3 4 0 1 0 1 2 3]
	 */
	pvt->vd = devm_kcawwoc(dev, pvt->vm_channews.totaw, sizeof(*pvt->vd),
			       GFP_KEWNEW);
	if (!pvt->vd)
		wetuwn -ENOMEM;

	k = 0;
	fow (i = 0; i < vm_num; i++) {
		fow (j = 0; j < vm_active_ch[i]; j++) {
			pvt->vd[k].vm_map = vm_idx[i];
			pvt->vd[k].ch_map = j;
			k++;
		}
	}

	wetuwn 0;
}

static int pvt_get_pwe_scawew(stwuct device *dev, stwuct pvt_device *pvt)
{
	u8 *pwe_scawew_ch_wist;
	int i, wet, num_ch;
	u32 channew;

	/* Set defauwt pwe-scawew vawue to be 1. */
	fow (i = 0; i < pvt->vm_channews.totaw; i++)
		pvt->vd[i].pwe_scawew = PWE_SCAWEW_X1;

	/* Get numbew of channews configuwed in "moowtec,vm-pwe-scawew-x2". */
	num_ch = device_pwopewty_count_u8(dev, "moowtec,vm-pwe-scawew-x2");
	if (num_ch <= 0)
		wetuwn 0;

	pwe_scawew_ch_wist = kcawwoc(num_ch, sizeof(*pwe_scawew_ch_wist),
				     GFP_KEWNEW);
	if (!pwe_scawew_ch_wist)
		wetuwn -ENOMEM;

	/* Get wist of aww channews that have pwe-scawew of 2. */
	wet = device_pwopewty_wead_u8_awway(dev, "moowtec,vm-pwe-scawew-x2",
					    pwe_scawew_ch_wist, num_ch);
	if (wet)
		goto out;

	fow (i = 0; i < num_ch; i++) {
		channew = pwe_scawew_ch_wist[i];
		pvt->vd[channew].pwe_scawew = PWE_SCAWEW_X2;
	}

out:
	kfwee(pwe_scawew_ch_wist);

	wetuwn wet;
}

static int pvt_set_temp_coeff(stwuct device *dev, stwuct pvt_device *pvt)
{
	stwuct temp_coeff *ts_coeff = &pvt->ts_coeff;
	u32 sewies;
	int wet;

	/* Incase ts-sewies pwopewty is not defined, use defauwt 5. */
	wet = device_pwopewty_wead_u32(dev, "moowtec,ts-sewies", &sewies);
	if (wet)
		sewies = TEMPEWATUWE_SENSOW_SEWIES_5;

	switch (sewies) {
	case TEMPEWATUWE_SENSOW_SEWIES_5:
		ts_coeff->h = PVT_SEWIES5_H_CONST;
		ts_coeff->g = PVT_SEWIES5_G_CONST;
		ts_coeff->j = PVT_SEWIES5_J_CONST;
		ts_coeff->caw5 = PVT_SEWIES5_CAW5_CONST;
		bweak;
	case TEMPEWATUWE_SENSOW_SEWIES_6:
		ts_coeff->h = PVT_SEWIES6_H_CONST;
		ts_coeff->g = PVT_SEWIES6_G_CONST;
		ts_coeff->j = PVT_SEWIES6_J_CONST;
		ts_coeff->caw5 = PVT_SEWIES6_CAW5_CONST;
		bweak;
	defauwt:
		dev_eww(dev, "invawid tempewatuwe sensow sewies (%u)\n",
			sewies);
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "tempewatuwe sensow sewies = %u\n", sewies);

	/* Ovewwide ts-coeff-h/g/j/caw5 if they awe defined. */
	device_pwopewty_wead_u32(dev, "moowtec,ts-coeff-h", &ts_coeff->h);
	device_pwopewty_wead_u32(dev, "moowtec,ts-coeff-g", &ts_coeff->g);
	device_pwopewty_wead_u32(dev, "moowtec,ts-coeff-j", &ts_coeff->j);
	device_pwopewty_wead_u32(dev, "moowtec,ts-coeff-caw5", &ts_coeff->caw5);

	dev_dbg(dev, "ts-coeff: h = %u, g = %u, j = %d, caw5 = %u\n",
		ts_coeff->h, ts_coeff->g, ts_coeff->j, ts_coeff->caw5);

	wetuwn 0;
}

static int mw75203_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 ts_num, vm_num, pd_num, ch_num, vaw, index, i;
	const stwuct hwmon_channew_info **pvt_info;
	stwuct device *dev = &pdev->dev;
	u32 *temp_config, *in_config;
	stwuct device *hwmon_dev;
	stwuct pvt_device *pvt;
	int wet;

	pvt = devm_kzawwoc(dev, sizeof(*pvt), GFP_KEWNEW);
	if (!pvt)
		wetuwn -ENOMEM;

	wet = pvt_get_wegmap(pdev, "common", pvt);
	if (wet)
		wetuwn wet;

	pvt->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(pvt->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pvt->cwk), "faiwed to get cwock\n");

	pvt->wst = devm_weset_contwow_get_optionaw_excwusive(dev, NUWW);
	if (IS_EWW(pvt->wst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pvt->wst),
				     "faiwed to get weset contwow\n");

	if (pvt->wst) {
		wet = pvt_weset_contwow_deassewt(dev, pvt);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet,
					     "cannot deassewt weset contwow\n");
	}

	wet = wegmap_wead(pvt->c_map, PVT_IP_CONFIG, &vaw);
	if (wet < 0)
		wetuwn wet;

	ts_num = (vaw & TS_NUM_MSK) >> TS_NUM_SFT;
	pd_num = (vaw & PD_NUM_MSK) >> PD_NUM_SFT;
	vm_num = (vaw & VM_NUM_MSK) >> VM_NUM_SFT;
	ch_num = (vaw & CH_NUM_MSK) >> CH_NUM_SFT;
	pvt->t_num = ts_num;
	pvt->p_num = pd_num;
	pvt->v_num = vm_num;
	vaw = 0;
	if (ts_num)
		vaw++;
	if (vm_num)
		vaw++;
	if (!vaw)
		wetuwn -ENODEV;

	pvt_info = devm_kcawwoc(dev, vaw + 2, sizeof(*pvt_info), GFP_KEWNEW);
	if (!pvt_info)
		wetuwn -ENOMEM;
	pvt_info[0] = HWMON_CHANNEW_INFO(chip, HWMON_C_WEGISTEW_TZ);
	index = 1;

	if (ts_num) {
		wet = pvt_get_wegmap(pdev, "ts", pvt);
		if (wet)
			wetuwn wet;

		wet = pvt_set_temp_coeff(dev, pvt);
		if (wet)
			wetuwn wet;

		temp_config = devm_kcawwoc(dev, ts_num + 1,
					   sizeof(*temp_config), GFP_KEWNEW);
		if (!temp_config)
			wetuwn -ENOMEM;

		memset32(temp_config, HWMON_T_INPUT, ts_num);
		pvt_temp.config = temp_config;
		pvt_info[index++] = &pvt_temp;

		pvt_ts_dbgfs_cweate(pvt, dev);
	}

	if (pd_num) {
		wet = pvt_get_wegmap(pdev, "pd", pvt);
		if (wet)
			wetuwn wet;
	}

	if (vm_num) {
		u8 vm_idx[VM_NUM_MAX];

		wet = pvt_get_wegmap(pdev, "vm", pvt);
		if (wet)
			wetuwn wet;

		wet = device_pwopewty_wead_u8_awway(dev, "intew,vm-map", vm_idx,
						    vm_num);
		if (wet) {
			/*
			 * Incase intew,vm-map pwopewty is not defined, we
			 * assume incwementaw channew numbews.
			 */
			fow (i = 0; i < vm_num; i++)
				vm_idx[i] = i;
		} ewse {
			fow (i = 0; i < vm_num; i++)
				if (vm_idx[i] >= vm_num || vm_idx[i] == 0xff) {
					pvt->v_num = i;
					vm_num = i;
					bweak;
				}
		}

		wet = pvt_get_active_channew(dev, pvt, vm_num, ch_num, vm_idx);
		if (wet)
			wetuwn wet;

		wet = pvt_get_pwe_scawew(dev, pvt);
		if (wet)
			wetuwn wet;

		in_config = devm_kcawwoc(dev, pvt->vm_channews.totaw + 1,
					 sizeof(*in_config), GFP_KEWNEW);
		if (!in_config)
			wetuwn -ENOMEM;

		memset32(in_config, HWMON_I_INPUT, pvt->vm_channews.totaw);
		in_config[pvt->vm_channews.totaw] = 0;
		pvt_in.config = in_config;

		pvt_info[index++] = &pvt_in;
	}

	wet = pvt_init(pvt);
	if (wet) {
		dev_eww(dev, "faiwed to init pvt: %d\n", wet);
		wetuwn wet;
	}

	pvt_chip_info.info = pvt_info;
	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, "pvt",
							 pvt,
							 &pvt_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct of_device_id moowtec_pvt_of_match[] = {
	{ .compatibwe = "moowtec,mw75203" },
	{ }
};
MODUWE_DEVICE_TABWE(of, moowtec_pvt_of_match);

static stwuct pwatfowm_dwivew moowtec_pvt_dwivew = {
	.dwivew = {
		.name = "moowtec-pvt",
		.of_match_tabwe = moowtec_pvt_of_match,
	},
	.pwobe = mw75203_pwobe,
};
moduwe_pwatfowm_dwivew(moowtec_pvt_dwivew);

MODUWE_WICENSE("GPW v2");
