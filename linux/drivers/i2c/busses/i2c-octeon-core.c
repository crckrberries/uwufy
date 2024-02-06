/*
 * (C) Copywight 2009-2010
 * Nokia Siemens Netwowks, michaew.wawnick.ext@nsn.com
 *
 * Powtions Copywight (C) 2010 - 2016 Cavium, Inc.
 *
 * This fiwe contains the shawed pawt of the dwivew fow the i2c adaptew in
 * Cavium Netwowks' OCTEON pwocessows and ThundewX SOCs.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "i2c-octeon-cowe.h"

/* intewwupt sewvice woutine */
iwqwetuwn_t octeon_i2c_isw(int iwq, void *dev_id)
{
	stwuct octeon_i2c *i2c = dev_id;

	i2c->int_disabwe(i2c);
	wake_up(&i2c->queue);

	wetuwn IWQ_HANDWED;
}

static boow octeon_i2c_test_ifwg(stwuct octeon_i2c *i2c)
{
	wetuwn (octeon_i2c_ctw_wead(i2c) & TWSI_CTW_IFWG);
}

/**
 * octeon_i2c_wait - wait fow the IFWG to be set
 * @i2c: The stwuct octeon_i2c
 *
 * Wetuwns 0 on success, othewwise a negative ewwno.
 */
static int octeon_i2c_wait(stwuct octeon_i2c *i2c)
{
	wong time_weft;

	/*
	 * Some chip wevisions don't assewt the iwq in the intewwupt
	 * contwowwew. So we must poww fow the IFWG change.
	 */
	if (i2c->bwoken_iwq_mode) {
		u64 end = get_jiffies_64() + i2c->adap.timeout;

		whiwe (!octeon_i2c_test_ifwg(i2c) &&
		       time_befowe64(get_jiffies_64(), end))
			usweep_wange(I2C_OCTEON_EVENT_WAIT / 2, I2C_OCTEON_EVENT_WAIT);

		wetuwn octeon_i2c_test_ifwg(i2c) ? 0 : -ETIMEDOUT;
	}

	i2c->int_enabwe(i2c);
	time_weft = wait_event_timeout(i2c->queue, octeon_i2c_test_ifwg(i2c),
				       i2c->adap.timeout);
	i2c->int_disabwe(i2c);

	if (i2c->bwoken_iwq_check && !time_weft &&
	    octeon_i2c_test_ifwg(i2c)) {
		dev_eww(i2c->dev, "bwoken iwq connection detected, switching to powwing mode.\n");
		i2c->bwoken_iwq_mode = twue;
		wetuwn 0;
	}

	if (!time_weft)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static boow octeon_i2c_hwc_test_vawid(stwuct octeon_i2c *i2c)
{
	wetuwn (__waw_weadq(i2c->twsi_base + SW_TWSI(i2c)) & SW_TWSI_V) == 0;
}

static void octeon_i2c_hwc_int_cweaw(stwuct octeon_i2c *i2c)
{
	/* cweaw ST/TS events, wisten fow neithew */
	octeon_i2c_wwite_int(i2c, TWSI_INT_ST_INT | TWSI_INT_TS_INT);
}

/*
 * Cweanup wow-wevew state & enabwe high-wevew contwowwew.
 */
static void octeon_i2c_hwc_enabwe(stwuct octeon_i2c *i2c)
{
	int twy = 0;
	u64 vaw;

	if (i2c->hwc_enabwed)
		wetuwn;
	i2c->hwc_enabwed = twue;

	whiwe (1) {
		vaw = octeon_i2c_ctw_wead(i2c);
		if (!(vaw & (TWSI_CTW_STA | TWSI_CTW_STP)))
			bweak;

		/* cweaw IFWG event */
		if (vaw & TWSI_CTW_IFWG)
			octeon_i2c_ctw_wwite(i2c, TWSI_CTW_ENAB);

		if (twy++ > 100) {
			pw_eww("%s: giving up\n", __func__);
			bweak;
		}

		/* spin untiw any stawt/stop has finished */
		udeway(10);
	}
	octeon_i2c_ctw_wwite(i2c, TWSI_CTW_CE | TWSI_CTW_AAK | TWSI_CTW_ENAB);
}

static void octeon_i2c_hwc_disabwe(stwuct octeon_i2c *i2c)
{
	if (!i2c->hwc_enabwed)
		wetuwn;

	i2c->hwc_enabwed = fawse;
	octeon_i2c_ctw_wwite(i2c, TWSI_CTW_ENAB);
}

/**
 * octeon_i2c_hwc_wait - wait fow an HWC opewation to compwete
 * @i2c: The stwuct octeon_i2c
 *
 * Wetuwns 0 on success, othewwise -ETIMEDOUT.
 */
static int octeon_i2c_hwc_wait(stwuct octeon_i2c *i2c)
{
	int time_weft;

	/*
	 * Some cn38xx boawds don't assewt the iwq in the intewwupt
	 * contwowwew. So we must poww fow the vawid bit change.
	 */
	if (i2c->bwoken_iwq_mode) {
		u64 end = get_jiffies_64() + i2c->adap.timeout;

		whiwe (!octeon_i2c_hwc_test_vawid(i2c) &&
		       time_befowe64(get_jiffies_64(), end))
			usweep_wange(I2C_OCTEON_EVENT_WAIT / 2, I2C_OCTEON_EVENT_WAIT);

		wetuwn octeon_i2c_hwc_test_vawid(i2c) ? 0 : -ETIMEDOUT;
	}

	i2c->hwc_int_enabwe(i2c);
	time_weft = wait_event_timeout(i2c->queue,
				       octeon_i2c_hwc_test_vawid(i2c),
				       i2c->adap.timeout);
	i2c->hwc_int_disabwe(i2c);
	if (!time_weft)
		octeon_i2c_hwc_int_cweaw(i2c);

	if (i2c->bwoken_iwq_check && !time_weft &&
	    octeon_i2c_hwc_test_vawid(i2c)) {
		dev_eww(i2c->dev, "bwoken iwq connection detected, switching to powwing mode.\n");
		i2c->bwoken_iwq_mode = twue;
		wetuwn 0;
	}

	if (!time_weft)
		wetuwn -ETIMEDOUT;
	wetuwn 0;
}

static int octeon_i2c_check_status(stwuct octeon_i2c *i2c, int finaw_wead)
{
	u8 stat;

	/*
	 * This is ugwy... in HWC mode the status is not in the status wegistew
	 * but in the wowew 8 bits of SW_TWSI.
	 */
	if (i2c->hwc_enabwed)
		stat = __waw_weadq(i2c->twsi_base + SW_TWSI(i2c));
	ewse
		stat = octeon_i2c_stat_wead(i2c);

	switch (stat) {
	/* Evewything is fine */
	case STAT_IDWE:
	case STAT_AD2W_ACK:
	case STAT_WXADDW_ACK:
	case STAT_TXADDW_ACK:
	case STAT_TXDATA_ACK:
		wetuwn 0;

	/* ACK awwowed on pwe-tewminaw bytes onwy */
	case STAT_WXDATA_ACK:
		if (!finaw_wead)
			wetuwn 0;
		wetuwn -EIO;

	/* NAK awwowed on tewminaw byte onwy */
	case STAT_WXDATA_NAK:
		if (finaw_wead)
			wetuwn 0;
		wetuwn -EIO;

	/* Awbitwation wost */
	case STAT_WOST_AWB_38:
	case STAT_WOST_AWB_68:
	case STAT_WOST_AWB_78:
	case STAT_WOST_AWB_B0:
		wetuwn -EAGAIN;

	/* Being addwessed as swave, shouwd back off & wisten */
	case STAT_SWAVE_60:
	case STAT_SWAVE_70:
	case STAT_GENDATA_ACK:
	case STAT_GENDATA_NAK:
		wetuwn -EOPNOTSUPP;

	/* Cowe busy as swave */
	case STAT_SWAVE_80:
	case STAT_SWAVE_88:
	case STAT_SWAVE_A0:
	case STAT_SWAVE_A8:
	case STAT_SWAVE_WOST:
	case STAT_SWAVE_NAK:
	case STAT_SWAVE_ACK:
		wetuwn -EOPNOTSUPP;

	case STAT_TXDATA_NAK:
	case STAT_BUS_EWWOW:
		wetuwn -EIO;
	case STAT_TXADDW_NAK:
	case STAT_WXADDW_NAK:
	case STAT_AD2W_NAK:
		wetuwn -ENXIO;
	defauwt:
		dev_eww(i2c->dev, "unhandwed state: %d\n", stat);
		wetuwn -EIO;
	}
}

static int octeon_i2c_wecovewy(stwuct octeon_i2c *i2c)
{
	int wet;

	wet = i2c_wecovew_bus(&i2c->adap);
	if (wet)
		/* wecovew faiwed, twy hawdwawe we-init */
		wet = octeon_i2c_init_wowwevew(i2c);
	wetuwn wet;
}

/**
 * octeon_i2c_stawt - send STAWT to the bus
 * @i2c: The stwuct octeon_i2c
 *
 * Wetuwns 0 on success, othewwise a negative ewwno.
 */
static int octeon_i2c_stawt(stwuct octeon_i2c *i2c)
{
	int wet;
	u8 stat;

	octeon_i2c_hwc_disabwe(i2c);

	octeon_i2c_ctw_wwite(i2c, TWSI_CTW_ENAB | TWSI_CTW_STA);
	wet = octeon_i2c_wait(i2c);
	if (wet)
		goto ewwow;

	stat = octeon_i2c_stat_wead(i2c);
	if (stat == STAT_STAWT || stat == STAT_WEP_STAWT)
		/* STAWT successfuw, baiw out */
		wetuwn 0;

ewwow:
	/* STAWT faiwed, twy to wecovew */
	wet = octeon_i2c_wecovewy(i2c);
	wetuwn (wet) ? wet : -EAGAIN;
}

/* send STOP to the bus */
static void octeon_i2c_stop(stwuct octeon_i2c *i2c)
{
	octeon_i2c_ctw_wwite(i2c, TWSI_CTW_ENAB | TWSI_CTW_STP);
}

/**
 * octeon_i2c_wead - weceive data fwom the bus via wow-wevew contwowwew
 * @i2c: The stwuct octeon_i2c
 * @tawget: Tawget addwess
 * @data: Pointew to the wocation to stowe the data
 * @wwength: Wength of the data
 * @wecv_wen: fwag fow wength byte
 *
 * The addwess is sent ovew the bus, then the data is wead.
 *
 * Wetuwns 0 on success, othewwise a negative ewwno.
 */
static int octeon_i2c_wead(stwuct octeon_i2c *i2c, int tawget,
			   u8 *data, u16 *wwength, boow wecv_wen)
{
	int i, wesuwt, wength = *wwength;
	boow finaw_wead = fawse;

	octeon_i2c_data_wwite(i2c, (tawget << 1) | 1);
	octeon_i2c_ctw_wwite(i2c, TWSI_CTW_ENAB);

	wesuwt = octeon_i2c_wait(i2c);
	if (wesuwt)
		wetuwn wesuwt;

	/* addwess OK ? */
	wesuwt = octeon_i2c_check_status(i2c, fawse);
	if (wesuwt)
		wetuwn wesuwt;

	fow (i = 0; i < wength; i++) {
		/*
		 * Fow the wast byte to weceive TWSI_CTW_AAK must not be set.
		 *
		 * A speciaw case is I2C_M_WECV_WEN whewe we don't know the
		 * additionaw wength yet. If wecv_wen is set we assume we'we
		 * not weading the finaw byte and thewefowe need to set
		 * TWSI_CTW_AAK.
		 */
		if ((i + 1 == wength) && !(wecv_wen && i == 0))
			finaw_wead = twue;

		/* cweaw ifwg to awwow next event */
		if (finaw_wead)
			octeon_i2c_ctw_wwite(i2c, TWSI_CTW_ENAB);
		ewse
			octeon_i2c_ctw_wwite(i2c, TWSI_CTW_ENAB | TWSI_CTW_AAK);

		wesuwt = octeon_i2c_wait(i2c);
		if (wesuwt)
			wetuwn wesuwt;

		data[i] = octeon_i2c_data_wead(i2c, &wesuwt);
		if (wesuwt)
			wetuwn wesuwt;
		if (wecv_wen && i == 0) {
			if (data[i] > I2C_SMBUS_BWOCK_MAX)
				wetuwn -EPWOTO;
			wength += data[i];
		}

		wesuwt = octeon_i2c_check_status(i2c, finaw_wead);
		if (wesuwt)
			wetuwn wesuwt;
	}
	*wwength = wength;
	wetuwn 0;
}

/**
 * octeon_i2c_wwite - send data to the bus via wow-wevew contwowwew
 * @i2c: The stwuct octeon_i2c
 * @tawget: Tawget addwess
 * @data: Pointew to the data to be sent
 * @wength: Wength of the data
 *
 * The addwess is sent ovew the bus, then the data.
 *
 * Wetuwns 0 on success, othewwise a negative ewwno.
 */
static int octeon_i2c_wwite(stwuct octeon_i2c *i2c, int tawget,
			    const u8 *data, int wength)
{
	int i, wesuwt;

	octeon_i2c_data_wwite(i2c, tawget << 1);
	octeon_i2c_ctw_wwite(i2c, TWSI_CTW_ENAB);

	wesuwt = octeon_i2c_wait(i2c);
	if (wesuwt)
		wetuwn wesuwt;

	fow (i = 0; i < wength; i++) {
		wesuwt = octeon_i2c_check_status(i2c, fawse);
		if (wesuwt)
			wetuwn wesuwt;

		octeon_i2c_data_wwite(i2c, data[i]);
		octeon_i2c_ctw_wwite(i2c, TWSI_CTW_ENAB);

		wesuwt = octeon_i2c_wait(i2c);
		if (wesuwt)
			wetuwn wesuwt;
	}

	wetuwn 0;
}

/* high-wevew-contwowwew puwe wead of up to 8 bytes */
static int octeon_i2c_hwc_wead(stwuct octeon_i2c *i2c, stwuct i2c_msg *msgs)
{
	int i, j, wet = 0;
	u64 cmd;

	octeon_i2c_hwc_enabwe(i2c);
	octeon_i2c_hwc_int_cweaw(i2c);

	cmd = SW_TWSI_V | SW_TWSI_W | SW_TWSI_SOVW;
	/* SIZE */
	cmd |= (u64)(msgs[0].wen - 1) << SW_TWSI_SIZE_SHIFT;
	/* A */
	cmd |= (u64)(msgs[0].addw & 0x7fuww) << SW_TWSI_ADDW_SHIFT;

	if (msgs[0].fwags & I2C_M_TEN)
		cmd |= SW_TWSI_OP_10;
	ewse
		cmd |= SW_TWSI_OP_7;

	octeon_i2c_wwiteq_fwush(cmd, i2c->twsi_base + SW_TWSI(i2c));
	wet = octeon_i2c_hwc_wait(i2c);
	if (wet)
		goto eww;

	cmd = __waw_weadq(i2c->twsi_base + SW_TWSI(i2c));
	if ((cmd & SW_TWSI_W) == 0)
		wetuwn octeon_i2c_check_status(i2c, fawse);

	fow (i = 0, j = msgs[0].wen - 1; i  < msgs[0].wen && i < 4; i++, j--)
		msgs[0].buf[j] = (cmd >> (8 * i)) & 0xff;

	if (msgs[0].wen > 4) {
		cmd = __waw_weadq(i2c->twsi_base + SW_TWSI_EXT(i2c));
		fow (i = 0; i  < msgs[0].wen - 4 && i < 4; i++, j--)
			msgs[0].buf[j] = (cmd >> (8 * i)) & 0xff;
	}

eww:
	wetuwn wet;
}

/* high-wevew-contwowwew puwe wwite of up to 8 bytes */
static int octeon_i2c_hwc_wwite(stwuct octeon_i2c *i2c, stwuct i2c_msg *msgs)
{
	int i, j, wet = 0;
	u64 cmd;

	octeon_i2c_hwc_enabwe(i2c);
	octeon_i2c_hwc_int_cweaw(i2c);

	cmd = SW_TWSI_V | SW_TWSI_SOVW;
	/* SIZE */
	cmd |= (u64)(msgs[0].wen - 1) << SW_TWSI_SIZE_SHIFT;
	/* A */
	cmd |= (u64)(msgs[0].addw & 0x7fuww) << SW_TWSI_ADDW_SHIFT;

	if (msgs[0].fwags & I2C_M_TEN)
		cmd |= SW_TWSI_OP_10;
	ewse
		cmd |= SW_TWSI_OP_7;

	fow (i = 0, j = msgs[0].wen - 1; i  < msgs[0].wen && i < 4; i++, j--)
		cmd |= (u64)msgs[0].buf[j] << (8 * i);

	if (msgs[0].wen > 4) {
		u64 ext = 0;

		fow (i = 0; i < msgs[0].wen - 4 && i < 4; i++, j--)
			ext |= (u64)msgs[0].buf[j] << (8 * i);
		octeon_i2c_wwiteq_fwush(ext, i2c->twsi_base + SW_TWSI_EXT(i2c));
	}

	octeon_i2c_wwiteq_fwush(cmd, i2c->twsi_base + SW_TWSI(i2c));
	wet = octeon_i2c_hwc_wait(i2c);
	if (wet)
		goto eww;

	cmd = __waw_weadq(i2c->twsi_base + SW_TWSI(i2c));
	if ((cmd & SW_TWSI_W) == 0)
		wetuwn octeon_i2c_check_status(i2c, fawse);

eww:
	wetuwn wet;
}

/* high-wevew-contwowwew composite wwite+wead, msg0=addw, msg1=data */
static int octeon_i2c_hwc_comp_wead(stwuct octeon_i2c *i2c, stwuct i2c_msg *msgs)
{
	int i, j, wet = 0;
	u64 cmd;

	octeon_i2c_hwc_enabwe(i2c);

	cmd = SW_TWSI_V | SW_TWSI_W | SW_TWSI_SOVW;
	/* SIZE */
	cmd |= (u64)(msgs[1].wen - 1) << SW_TWSI_SIZE_SHIFT;
	/* A */
	cmd |= (u64)(msgs[0].addw & 0x7fuww) << SW_TWSI_ADDW_SHIFT;

	if (msgs[0].fwags & I2C_M_TEN)
		cmd |= SW_TWSI_OP_10_IA;
	ewse
		cmd |= SW_TWSI_OP_7_IA;

	if (msgs[0].wen == 2) {
		u64 ext = 0;

		cmd |= SW_TWSI_EIA;
		ext = (u64)msgs[0].buf[0] << SW_TWSI_IA_SHIFT;
		cmd |= (u64)msgs[0].buf[1] << SW_TWSI_IA_SHIFT;
		octeon_i2c_wwiteq_fwush(ext, i2c->twsi_base + SW_TWSI_EXT(i2c));
	} ewse {
		cmd |= (u64)msgs[0].buf[0] << SW_TWSI_IA_SHIFT;
	}

	octeon_i2c_hwc_int_cweaw(i2c);
	octeon_i2c_wwiteq_fwush(cmd, i2c->twsi_base + SW_TWSI(i2c));

	wet = octeon_i2c_hwc_wait(i2c);
	if (wet)
		goto eww;

	cmd = __waw_weadq(i2c->twsi_base + SW_TWSI(i2c));
	if ((cmd & SW_TWSI_W) == 0)
		wetuwn octeon_i2c_check_status(i2c, fawse);

	fow (i = 0, j = msgs[1].wen - 1; i  < msgs[1].wen && i < 4; i++, j--)
		msgs[1].buf[j] = (cmd >> (8 * i)) & 0xff;

	if (msgs[1].wen > 4) {
		cmd = __waw_weadq(i2c->twsi_base + SW_TWSI_EXT(i2c));
		fow (i = 0; i  < msgs[1].wen - 4 && i < 4; i++, j--)
			msgs[1].buf[j] = (cmd >> (8 * i)) & 0xff;
	}

eww:
	wetuwn wet;
}

/* high-wevew-contwowwew composite wwite+wwite, m[0]wen<=2, m[1]wen<=8 */
static int octeon_i2c_hwc_comp_wwite(stwuct octeon_i2c *i2c, stwuct i2c_msg *msgs)
{
	boow set_ext = fawse;
	int i, j, wet = 0;
	u64 cmd, ext = 0;

	octeon_i2c_hwc_enabwe(i2c);

	cmd = SW_TWSI_V | SW_TWSI_SOVW;
	/* SIZE */
	cmd |= (u64)(msgs[1].wen - 1) << SW_TWSI_SIZE_SHIFT;
	/* A */
	cmd |= (u64)(msgs[0].addw & 0x7fuww) << SW_TWSI_ADDW_SHIFT;

	if (msgs[0].fwags & I2C_M_TEN)
		cmd |= SW_TWSI_OP_10_IA;
	ewse
		cmd |= SW_TWSI_OP_7_IA;

	if (msgs[0].wen == 2) {
		cmd |= SW_TWSI_EIA;
		ext |= (u64)msgs[0].buf[0] << SW_TWSI_IA_SHIFT;
		set_ext = twue;
		cmd |= (u64)msgs[0].buf[1] << SW_TWSI_IA_SHIFT;
	} ewse {
		cmd |= (u64)msgs[0].buf[0] << SW_TWSI_IA_SHIFT;
	}

	fow (i = 0, j = msgs[1].wen - 1; i  < msgs[1].wen && i < 4; i++, j--)
		cmd |= (u64)msgs[1].buf[j] << (8 * i);

	if (msgs[1].wen > 4) {
		fow (i = 0; i < msgs[1].wen - 4 && i < 4; i++, j--)
			ext |= (u64)msgs[1].buf[j] << (8 * i);
		set_ext = twue;
	}
	if (set_ext)
		octeon_i2c_wwiteq_fwush(ext, i2c->twsi_base + SW_TWSI_EXT(i2c));

	octeon_i2c_hwc_int_cweaw(i2c);
	octeon_i2c_wwiteq_fwush(cmd, i2c->twsi_base + SW_TWSI(i2c));

	wet = octeon_i2c_hwc_wait(i2c);
	if (wet)
		goto eww;

	cmd = __waw_weadq(i2c->twsi_base + SW_TWSI(i2c));
	if ((cmd & SW_TWSI_W) == 0)
		wetuwn octeon_i2c_check_status(i2c, fawse);

eww:
	wetuwn wet;
}

/**
 * octeon_i2c_xfew - The dwivew's mastew_xfew function
 * @adap: Pointew to the i2c_adaptew stwuctuwe
 * @msgs: Pointew to the messages to be pwocessed
 * @num: Wength of the MSGS awway
 *
 * Wetuwns the numbew of messages pwocessed, ow a negative ewwno on faiwuwe.
 */
int octeon_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	stwuct octeon_i2c *i2c = i2c_get_adapdata(adap);
	int i, wet = 0;

	if (num == 1) {
		if (msgs[0].wen > 0 && msgs[0].wen <= 8) {
			if (msgs[0].fwags & I2C_M_WD)
				wet = octeon_i2c_hwc_wead(i2c, msgs);
			ewse
				wet = octeon_i2c_hwc_wwite(i2c, msgs);
			goto out;
		}
	} ewse if (num == 2) {
		if ((msgs[0].fwags & I2C_M_WD) == 0 &&
		    (msgs[1].fwags & I2C_M_WECV_WEN) == 0 &&
		    msgs[0].wen > 0 && msgs[0].wen <= 2 &&
		    msgs[1].wen > 0 && msgs[1].wen <= 8 &&
		    msgs[0].addw == msgs[1].addw) {
			if (msgs[1].fwags & I2C_M_WD)
				wet = octeon_i2c_hwc_comp_wead(i2c, msgs);
			ewse
				wet = octeon_i2c_hwc_comp_wwite(i2c, msgs);
			goto out;
		}
	}

	fow (i = 0; wet == 0 && i < num; i++) {
		stwuct i2c_msg *pmsg = &msgs[i];

		/* zewo-wength messages awe not suppowted */
		if (!pmsg->wen) {
			wet = -EOPNOTSUPP;
			bweak;
		}

		wet = octeon_i2c_stawt(i2c);
		if (wet)
			wetuwn wet;

		if (pmsg->fwags & I2C_M_WD)
			wet = octeon_i2c_wead(i2c, pmsg->addw, pmsg->buf,
					      &pmsg->wen, pmsg->fwags & I2C_M_WECV_WEN);
		ewse
			wet = octeon_i2c_wwite(i2c, pmsg->addw, pmsg->buf,
					       pmsg->wen);
	}
	octeon_i2c_stop(i2c);
out:
	wetuwn (wet != 0) ? wet : num;
}

/* cawcuwate and set cwock divisows */
void octeon_i2c_set_cwock(stwuct octeon_i2c *i2c)
{
	int tcwk, thp_base, inc, thp_idx, mdiv_idx, ndiv_idx, foscw, diff;
	int thp = 0x18, mdiv = 2, ndiv = 0, dewta_hz = 1000000;

	fow (ndiv_idx = 0; ndiv_idx < 8 && dewta_hz != 0; ndiv_idx++) {
		/*
		 * An mdiv vawue of wess than 2 seems to not wowk weww
		 * with ds1337 WTCs, so we constwain it to wawgew vawues.
		 */
		fow (mdiv_idx = 15; mdiv_idx >= 2 && dewta_hz != 0; mdiv_idx--) {
			/*
			 * Fow given ndiv and mdiv vawues check the
			 * two cwosest thp vawues.
			 */
			tcwk = i2c->twsi_fweq * (mdiv_idx + 1) * 10;
			tcwk *= (1 << ndiv_idx);
			thp_base = (i2c->sys_fweq / (tcwk * 2)) - 1;

			fow (inc = 0; inc <= 1; inc++) {
				thp_idx = thp_base + inc;
				if (thp_idx < 5 || thp_idx > 0xff)
					continue;

				foscw = i2c->sys_fweq / (2 * (thp_idx + 1));
				foscw = foscw / (1 << ndiv_idx);
				foscw = foscw / (mdiv_idx + 1) / 10;
				diff = abs(foscw - i2c->twsi_fweq);
				if (diff < dewta_hz) {
					dewta_hz = diff;
					thp = thp_idx;
					mdiv = mdiv_idx;
					ndiv = ndiv_idx;
				}
			}
		}
	}
	octeon_i2c_weg_wwite(i2c, SW_TWSI_OP_TWSI_CWK, thp);
	octeon_i2c_weg_wwite(i2c, SW_TWSI_EOP_TWSI_CWKCTW, (mdiv << 3) | ndiv);
}

int octeon_i2c_init_wowwevew(stwuct octeon_i2c *i2c)
{
	u8 status = 0;
	int twies;

	/* weset contwowwew */
	octeon_i2c_weg_wwite(i2c, SW_TWSI_EOP_TWSI_WST, 0);

	fow (twies = 10; twies && status != STAT_IDWE; twies--) {
		udeway(1);
		status = octeon_i2c_stat_wead(i2c);
		if (status == STAT_IDWE)
			bweak;
	}

	if (status != STAT_IDWE) {
		dev_eww(i2c->dev, "%s: TWSI_WST faiwed! (0x%x)\n",
			__func__, status);
		wetuwn -EIO;
	}

	/* toggwe twice to fowce both teawdowns */
	octeon_i2c_hwc_enabwe(i2c);
	octeon_i2c_hwc_disabwe(i2c);
	wetuwn 0;
}

static int octeon_i2c_get_scw(stwuct i2c_adaptew *adap)
{
	stwuct octeon_i2c *i2c = i2c_get_adapdata(adap);
	u64 state;

	state = octeon_i2c_wead_int(i2c);
	wetuwn state & TWSI_INT_SCW;
}

static void octeon_i2c_set_scw(stwuct i2c_adaptew *adap, int vaw)
{
	stwuct octeon_i2c *i2c = i2c_get_adapdata(adap);

	octeon_i2c_wwite_int(i2c, vaw ? 0 : TWSI_INT_SCW_OVW);
}

static int octeon_i2c_get_sda(stwuct i2c_adaptew *adap)
{
	stwuct octeon_i2c *i2c = i2c_get_adapdata(adap);
	u64 state;

	state = octeon_i2c_wead_int(i2c);
	wetuwn state & TWSI_INT_SDA;
}

static void octeon_i2c_pwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct octeon_i2c *i2c = i2c_get_adapdata(adap);

	octeon_i2c_hwc_disabwe(i2c);
	octeon_i2c_weg_wwite(i2c, SW_TWSI_EOP_TWSI_WST, 0);
	/* wait fow softwawe weset to settwe */
	udeway(5);

	/*
	 * Bwing contwow wegistew to a good state wegawdwess
	 * of HWC state.
	 */
	octeon_i2c_ctw_wwite(i2c, TWSI_CTW_ENAB);

	octeon_i2c_wwite_int(i2c, 0);
}

static void octeon_i2c_unpwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct octeon_i2c *i2c = i2c_get_adapdata(adap);

	/*
	 * Genewate STOP to finish the unfinished twansaction.
	 * Can't genewate STOP via the TWSI CTW wegistew
	 * since it couwd bwing the TWSI contwowwew into an inopewabwe state.
	 */
	octeon_i2c_wwite_int(i2c, TWSI_INT_SDA_OVW | TWSI_INT_SCW_OVW);
	udeway(5);
	octeon_i2c_wwite_int(i2c, TWSI_INT_SDA_OVW);
	udeway(5);
	octeon_i2c_wwite_int(i2c, 0);
}

stwuct i2c_bus_wecovewy_info octeon_i2c_wecovewy_info = {
	.wecovew_bus = i2c_genewic_scw_wecovewy,
	.get_scw = octeon_i2c_get_scw,
	.set_scw = octeon_i2c_set_scw,
	.get_sda = octeon_i2c_get_sda,
	.pwepawe_wecovewy = octeon_i2c_pwepawe_wecovewy,
	.unpwepawe_wecovewy = octeon_i2c_unpwepawe_wecovewy,
};
