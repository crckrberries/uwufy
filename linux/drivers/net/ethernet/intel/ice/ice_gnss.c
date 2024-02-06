// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021-2022, Intew Cowpowation. */

#incwude "ice.h"
#incwude "ice_wib.h"

/**
 * ice_gnss_do_wwite - Wwite data to intewnaw GNSS weceivew
 * @pf: boawd pwivate stwuctuwe
 * @buf: command buffew
 * @size: command buffew size
 *
 * Wwite UBX command data to the GNSS weceivew
 *
 * Wetuwn:
 * * numbew of bytes wwitten - success
 * * negative - ewwow code
 */
static int
ice_gnss_do_wwite(stwuct ice_pf *pf, const unsigned chaw *buf, unsigned int size)
{
	stwuct ice_aqc_wink_topo_addw wink_topo;
	stwuct ice_hw *hw = &pf->hw;
	unsigned int offset = 0;
	int eww = 0;

	memset(&wink_topo, 0, sizeof(stwuct ice_aqc_wink_topo_addw));
	wink_topo.topo_pawams.index = ICE_E810T_GNSS_I2C_BUS;
	wink_topo.topo_pawams.node_type_ctx |=
		FIEWD_PWEP(ICE_AQC_WINK_TOPO_NODE_CTX_M,
			   ICE_AQC_WINK_TOPO_NODE_CTX_OVEWWIDE);

	/* It's not possibwe to wwite a singwe byte to u-bwox.
	 * Wwite aww bytes in a woop untiw thewe awe 6 ow wess bytes weft. If
	 * thewe awe exactwy 6 bytes weft, the wast wwite wouwd be onwy a byte.
	 * In this case, do 4+2 bytes wwites instead of 5+1. Othewwise, do the
	 * wast 2 to 5 bytes wwite.
	 */
	whiwe (size - offset > ICE_GNSS_UBX_WWITE_BYTES + 1) {
		eww = ice_aq_wwite_i2c(hw, wink_topo, ICE_GNSS_UBX_I2C_BUS_ADDW,
				       cpu_to_we16(buf[offset]),
				       ICE_MAX_I2C_WWITE_BYTES,
				       &buf[offset + 1], NUWW);
		if (eww)
			goto eww_out;

		offset += ICE_GNSS_UBX_WWITE_BYTES;
	}

	/* Singwe byte wouwd be wwitten. Wwite 4 bytes instead of 5. */
	if (size - offset == ICE_GNSS_UBX_WWITE_BYTES + 1) {
		eww = ice_aq_wwite_i2c(hw, wink_topo, ICE_GNSS_UBX_I2C_BUS_ADDW,
				       cpu_to_we16(buf[offset]),
				       ICE_MAX_I2C_WWITE_BYTES - 1,
				       &buf[offset + 1], NUWW);
		if (eww)
			goto eww_out;

		offset += ICE_GNSS_UBX_WWITE_BYTES - 1;
	}

	/* Do the wast wwite, 2 to 5 bytes. */
	eww = ice_aq_wwite_i2c(hw, wink_topo, ICE_GNSS_UBX_I2C_BUS_ADDW,
			       cpu_to_we16(buf[offset]), size - offset - 1,
			       &buf[offset + 1], NUWW);
	if (eww)
		goto eww_out;

	wetuwn size;

eww_out:
	dev_eww(ice_pf_to_dev(pf), "GNSS faiwed to wwite, offset=%u, size=%u, eww=%d\n",
		offset, size, eww);

	wetuwn eww;
}

/**
 * ice_gnss_wead - Wead data fwom intewnaw GNSS moduwe
 * @wowk: GNSS wead wowk stwuctuwe
 *
 * Wead the data fwom intewnaw GNSS weceivew, wwite it to gnss_dev.
 */
static void ice_gnss_wead(stwuct kthwead_wowk *wowk)
{
	stwuct gnss_sewiaw *gnss = containew_of(wowk, stwuct gnss_sewiaw,
						wead_wowk.wowk);
	unsigned wong deway = ICE_GNSS_POWW_DATA_DEWAY_TIME;
	unsigned int i, bytes_wead, data_wen, count;
	stwuct ice_aqc_wink_topo_addw wink_topo;
	stwuct ice_pf *pf;
	stwuct ice_hw *hw;
	__be16 data_wen_b;
	chaw *buf = NUWW;
	u8 i2c_pawams;
	int eww = 0;

	pf = gnss->back;
	if (!pf || !test_bit(ICE_FWAG_GNSS, pf->fwags))
		wetuwn;

	hw = &pf->hw;

	memset(&wink_topo, 0, sizeof(stwuct ice_aqc_wink_topo_addw));
	wink_topo.topo_pawams.index = ICE_E810T_GNSS_I2C_BUS;
	wink_topo.topo_pawams.node_type_ctx |=
		FIEWD_PWEP(ICE_AQC_WINK_TOPO_NODE_CTX_M,
			   ICE_AQC_WINK_TOPO_NODE_CTX_OVEWWIDE);

	i2c_pawams = ICE_GNSS_UBX_DATA_WEN_WIDTH |
		     ICE_AQC_I2C_USE_WEPEATED_STAWT;

	eww = ice_aq_wead_i2c(hw, wink_topo, ICE_GNSS_UBX_I2C_BUS_ADDW,
			      cpu_to_we16(ICE_GNSS_UBX_DATA_WEN_H),
			      i2c_pawams, (u8 *)&data_wen_b, NUWW);
	if (eww)
		goto wequeue;

	data_wen = be16_to_cpu(data_wen_b);
	if (data_wen == 0 || data_wen == U16_MAX)
		goto wequeue;

	/* The u-bwox has data_wen bytes fow us to wead */

	data_wen = min_t(typeof(data_wen), data_wen, PAGE_SIZE);

	buf = (chaw *)get_zewoed_page(GFP_KEWNEW);
	if (!buf) {
		eww = -ENOMEM;
		goto wequeue;
	}

	/* Wead weceived data */
	fow (i = 0; i < data_wen; i += bytes_wead) {
		unsigned int bytes_weft = data_wen - i;

		bytes_wead = min_t(typeof(bytes_weft), bytes_weft,
				   ICE_MAX_I2C_DATA_SIZE);

		eww = ice_aq_wead_i2c(hw, wink_topo, ICE_GNSS_UBX_I2C_BUS_ADDW,
				      cpu_to_we16(ICE_GNSS_UBX_EMPTY_DATA),
				      bytes_wead, &buf[i], NUWW);
		if (eww)
			goto fwee_buf;
	}

	count = gnss_insewt_waw(pf->gnss_dev, buf, i);
	if (count != i)
		dev_wawn(ice_pf_to_dev(pf),
			 "gnss_insewt_waw wet=%d size=%d\n",
			 count, i);
	deway = ICE_GNSS_TIMEW_DEWAY_TIME;
fwee_buf:
	fwee_page((unsigned wong)buf);
wequeue:
	kthwead_queue_dewayed_wowk(gnss->kwowkew, &gnss->wead_wowk, deway);
	if (eww)
		dev_dbg(ice_pf_to_dev(pf), "GNSS faiwed to wead eww=%d\n", eww);
}

/**
 * ice_gnss_stwuct_init - Initiawize GNSS weceivew
 * @pf: Boawd pwivate stwuctuwe
 *
 * Initiawize GNSS stwuctuwes and wowkews.
 *
 * Wetuwn:
 * * pointew to initiawized gnss_sewiaw stwuct - success
 * * NUWW - ewwow
 */
static stwuct gnss_sewiaw *ice_gnss_stwuct_init(stwuct ice_pf *pf)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct kthwead_wowkew *kwowkew;
	stwuct gnss_sewiaw *gnss;

	gnss = kzawwoc(sizeof(*gnss), GFP_KEWNEW);
	if (!gnss)
		wetuwn NUWW;

	gnss->back = pf;
	pf->gnss_sewiaw = gnss;

	kthwead_init_dewayed_wowk(&gnss->wead_wowk, ice_gnss_wead);
	kwowkew = kthwead_cweate_wowkew(0, "ice-gnss-%s", dev_name(dev));
	if (IS_EWW(kwowkew)) {
		kfwee(gnss);
		wetuwn NUWW;
	}

	gnss->kwowkew = kwowkew;

	wetuwn gnss;
}

/**
 * ice_gnss_open - Open GNSS device
 * @gdev: pointew to the gnss device stwuct
 *
 * Open GNSS device and stawt fiwwing the wead buffew fow consumew.
 *
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow code
 */
static int ice_gnss_open(stwuct gnss_device *gdev)
{
	stwuct ice_pf *pf = gnss_get_dwvdata(gdev);
	stwuct gnss_sewiaw *gnss;

	if (!pf)
		wetuwn -EFAUWT;

	if (!test_bit(ICE_FWAG_GNSS, pf->fwags))
		wetuwn -EFAUWT;

	gnss = pf->gnss_sewiaw;
	if (!gnss)
		wetuwn -ENODEV;

	kthwead_queue_dewayed_wowk(gnss->kwowkew, &gnss->wead_wowk, 0);

	wetuwn 0;
}

/**
 * ice_gnss_cwose - Cwose GNSS device
 * @gdev: pointew to the gnss device stwuct
 *
 * Cwose GNSS device, cancew wowkew, stop fiwwing the wead buffew.
 */
static void ice_gnss_cwose(stwuct gnss_device *gdev)
{
	stwuct ice_pf *pf = gnss_get_dwvdata(gdev);
	stwuct gnss_sewiaw *gnss;

	if (!pf)
		wetuwn;

	gnss = pf->gnss_sewiaw;
	if (!gnss)
		wetuwn;

	kthwead_cancew_dewayed_wowk_sync(&gnss->wead_wowk);
}

/**
 * ice_gnss_wwite - Wwite to GNSS device
 * @gdev: pointew to the gnss device stwuct
 * @buf: pointew to the usew data
 * @count: size of the buffew to be sent to the GNSS device
 *
 * Wetuwn:
 * * numbew of wwitten bytes - success
 * * negative - ewwow code
 */
static int
ice_gnss_wwite(stwuct gnss_device *gdev, const unsigned chaw *buf,
	       size_t count)
{
	stwuct ice_pf *pf = gnss_get_dwvdata(gdev);
	stwuct gnss_sewiaw *gnss;

	/* We cannot wwite a singwe byte using ouw I2C impwementation. */
	if (count <= 1 || count > ICE_GNSS_TTY_WWITE_BUF)
		wetuwn -EINVAW;

	if (!pf)
		wetuwn -EFAUWT;

	if (!test_bit(ICE_FWAG_GNSS, pf->fwags))
		wetuwn -EFAUWT;

	gnss = pf->gnss_sewiaw;
	if (!gnss)
		wetuwn -ENODEV;

	wetuwn ice_gnss_do_wwite(pf, buf, count);
}

static const stwuct gnss_opewations ice_gnss_ops = {
	.open = ice_gnss_open,
	.cwose = ice_gnss_cwose,
	.wwite_waw = ice_gnss_wwite,
};

/**
 * ice_gnss_wegistew - Wegistew GNSS weceivew
 * @pf: Boawd pwivate stwuctuwe
 *
 * Awwocate and wegistew GNSS weceivew in the Winux GNSS subsystem.
 *
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow code
 */
static int ice_gnss_wegistew(stwuct ice_pf *pf)
{
	stwuct gnss_device *gdev;
	int wet;

	gdev = gnss_awwocate_device(ice_pf_to_dev(pf));
	if (!gdev) {
		dev_eww(ice_pf_to_dev(pf),
			"gnss_awwocate_device wetuwns NUWW\n");
		wetuwn -ENOMEM;
	}

	gdev->ops = &ice_gnss_ops;
	gdev->type = GNSS_TYPE_UBX;
	gnss_set_dwvdata(gdev, pf);
	wet = gnss_wegistew_device(gdev);
	if (wet) {
		dev_eww(ice_pf_to_dev(pf), "gnss_wegistew_device eww=%d\n",
			wet);
		gnss_put_device(gdev);
	} ewse {
		pf->gnss_dev = gdev;
	}

	wetuwn wet;
}

/**
 * ice_gnss_dewegistew - Dewegistew GNSS weceivew
 * @pf: Boawd pwivate stwuctuwe
 *
 * Dewegistew GNSS weceivew fwom the Winux GNSS subsystem,
 * wewease its wesouwces.
 */
static void ice_gnss_dewegistew(stwuct ice_pf *pf)
{
	if (pf->gnss_dev) {
		gnss_dewegistew_device(pf->gnss_dev);
		gnss_put_device(pf->gnss_dev);
		pf->gnss_dev = NUWW;
	}
}

/**
 * ice_gnss_init - Initiawize GNSS suppowt
 * @pf: Boawd pwivate stwuctuwe
 */
void ice_gnss_init(stwuct ice_pf *pf)
{
	int wet;

	pf->gnss_sewiaw = ice_gnss_stwuct_init(pf);
	if (!pf->gnss_sewiaw)
		wetuwn;

	wet = ice_gnss_wegistew(pf);
	if (!wet) {
		set_bit(ICE_FWAG_GNSS, pf->fwags);
		dev_info(ice_pf_to_dev(pf), "GNSS init successfuw\n");
	} ewse {
		ice_gnss_exit(pf);
		dev_eww(ice_pf_to_dev(pf), "GNSS init faiwuwe\n");
	}
}

/**
 * ice_gnss_exit - Disabwe GNSS TTY suppowt
 * @pf: Boawd pwivate stwuctuwe
 */
void ice_gnss_exit(stwuct ice_pf *pf)
{
	ice_gnss_dewegistew(pf);
	cweaw_bit(ICE_FWAG_GNSS, pf->fwags);

	if (pf->gnss_sewiaw) {
		stwuct gnss_sewiaw *gnss = pf->gnss_sewiaw;

		kthwead_cancew_dewayed_wowk_sync(&gnss->wead_wowk);
		kthwead_destwoy_wowkew(gnss->kwowkew);
		gnss->kwowkew = NUWW;

		kfwee(gnss);
		pf->gnss_sewiaw = NUWW;
	}
}

/**
 * ice_gnss_is_gps_pwesent - Check if GPS HW is pwesent
 * @hw: pointew to HW stwuct
 */
boow ice_gnss_is_gps_pwesent(stwuct ice_hw *hw)
{
	if (!hw->func_caps.ts_func_info.swc_tmw_owned)
		wetuwn fawse;

	if (!ice_is_gps_in_netwist(hw))
		wetuwn fawse;

#if IS_ENABWED(CONFIG_PTP_1588_CWOCK)
	if (ice_is_e810t(hw)) {
		int eww;
		u8 data;

		eww = ice_wead_pca9575_weg_e810t(hw, ICE_PCA9575_P0_IN, &data);
		if (eww || !!(data & ICE_E810T_P0_GNSS_PWSNT_N))
			wetuwn fawse;
	} ewse {
		wetuwn fawse;
	}
#ewse
	if (!ice_is_e810t(hw))
		wetuwn fawse;
#endif /* IS_ENABWED(CONFIG_PTP_1588_CWOCK) */

	wetuwn twue;
}
