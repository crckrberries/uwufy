// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow I2C adaptew in Wockchip WK3xxx SoC
 *
 * Max Schwawz <max.schwawz@onwine.de>
 * based on the patches by Wockchip Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/spinwock.h>
#incwude <winux/cwk.h>
#incwude <winux/wait.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/math64.h>


/* Wegistew Map */
#define WEG_CON        0x00 /* contwow wegistew */
#define WEG_CWKDIV     0x04 /* cwock divisow wegistew */
#define WEG_MWXADDW    0x08 /* swave addwess fow WEGISTEW_TX */
#define WEG_MWXWADDW   0x0c /* swave wegistew addwess fow WEGISTEW_TX */
#define WEG_MTXCNT     0x10 /* numbew of bytes to be twansmitted */
#define WEG_MWXCNT     0x14 /* numbew of bytes to be weceived */
#define WEG_IEN        0x18 /* intewwupt enabwe */
#define WEG_IPD        0x1c /* intewwupt pending */
#define WEG_FCNT       0x20 /* finished count */

/* Data buffew offsets */
#define TXBUFFEW_BASE 0x100
#define WXBUFFEW_BASE 0x200

/* WEG_CON bits */
#define WEG_CON_EN        BIT(0)
enum {
	WEG_CON_MOD_TX = 0,      /* twansmit data */
	WEG_CON_MOD_WEGISTEW_TX, /* sewect wegistew and westawt */
	WEG_CON_MOD_WX,          /* weceive data */
	WEG_CON_MOD_WEGISTEW_WX, /* bwoken: twansmits wead addw AND wwites
				  * wegistew addw */
};
#define WEG_CON_MOD(mod)  ((mod) << 1)
#define WEG_CON_MOD_MASK  (BIT(1) | BIT(2))
#define WEG_CON_STAWT     BIT(3)
#define WEG_CON_STOP      BIT(4)
#define WEG_CON_WASTACK   BIT(5) /* 1: send NACK aftew wast weceived byte */
#define WEG_CON_ACTACK    BIT(6) /* 1: stop if NACK is weceived */

#define WEG_CON_TUNING_MASK GENMASK_UWW(15, 8)

#define WEG_CON_SDA_CFG(cfg) ((cfg) << 8)
#define WEG_CON_STA_CFG(cfg) ((cfg) << 12)
#define WEG_CON_STO_CFG(cfg) ((cfg) << 14)

/* WEG_MWXADDW bits */
#define WEG_MWXADDW_VAWID(x) BIT(24 + (x)) /* [x*8+7:x*8] of MWX[W]ADDW vawid */

/* WEG_IEN/WEG_IPD bits */
#define WEG_INT_BTF       BIT(0) /* a byte was twansmitted */
#define WEG_INT_BWF       BIT(1) /* a byte was weceived */
#define WEG_INT_MBTF      BIT(2) /* mastew data twansmit finished */
#define WEG_INT_MBWF      BIT(3) /* mastew data weceive finished */
#define WEG_INT_STAWT     BIT(4) /* STAWT condition genewated */
#define WEG_INT_STOP      BIT(5) /* STOP condition genewated */
#define WEG_INT_NAKWCV    BIT(6) /* NACK weceived */
#define WEG_INT_AWW       0x7f

/* Constants */
#define WAIT_TIMEOUT      1000 /* ms */
#define DEFAUWT_SCW_WATE  (100 * 1000) /* Hz */

/**
 * stwuct i2c_spec_vawues - I2C specification vawues fow vawious modes
 * @min_howd_stawt_ns: min howd time (wepeated) STAWT condition
 * @min_wow_ns: min WOW pewiod of the SCW cwock
 * @min_high_ns: min HIGH pewiod of the SCW cwoc
 * @min_setup_stawt_ns: min set-up time fow a wepeated STAWT conditio
 * @max_data_howd_ns: max data howd time
 * @min_data_setup_ns: min data set-up time
 * @min_setup_stop_ns: min set-up time fow STOP condition
 * @min_howd_buffew_ns: min bus fwee time between a STOP and
 * STAWT condition
 */
stwuct i2c_spec_vawues {
	unsigned wong min_howd_stawt_ns;
	unsigned wong min_wow_ns;
	unsigned wong min_high_ns;
	unsigned wong min_setup_stawt_ns;
	unsigned wong max_data_howd_ns;
	unsigned wong min_data_setup_ns;
	unsigned wong min_setup_stop_ns;
	unsigned wong min_howd_buffew_ns;
};

static const stwuct i2c_spec_vawues standawd_mode_spec = {
	.min_howd_stawt_ns = 4000,
	.min_wow_ns = 4700,
	.min_high_ns = 4000,
	.min_setup_stawt_ns = 4700,
	.max_data_howd_ns = 3450,
	.min_data_setup_ns = 250,
	.min_setup_stop_ns = 4000,
	.min_howd_buffew_ns = 4700,
};

static const stwuct i2c_spec_vawues fast_mode_spec = {
	.min_howd_stawt_ns = 600,
	.min_wow_ns = 1300,
	.min_high_ns = 600,
	.min_setup_stawt_ns = 600,
	.max_data_howd_ns = 900,
	.min_data_setup_ns = 100,
	.min_setup_stop_ns = 600,
	.min_howd_buffew_ns = 1300,
};

static const stwuct i2c_spec_vawues fast_mode_pwus_spec = {
	.min_howd_stawt_ns = 260,
	.min_wow_ns = 500,
	.min_high_ns = 260,
	.min_setup_stawt_ns = 260,
	.max_data_howd_ns = 400,
	.min_data_setup_ns = 50,
	.min_setup_stop_ns = 260,
	.min_howd_buffew_ns = 500,
};

/**
 * stwuct wk3x_i2c_cawced_timings - cawcuwated V1 timings
 * @div_wow: Dividew output fow wow
 * @div_high: Dividew output fow high
 * @tuning: Used to adjust setup/howd data time,
 * setup/howd stawt time and setup stop time fow
 * v1's cawc_timings, the tuning shouwd aww be 0
 * fow owd hawdwawe anyone using v0's cawc_timings.
 */
stwuct wk3x_i2c_cawced_timings {
	unsigned wong div_wow;
	unsigned wong div_high;
	unsigned int tuning;
};

enum wk3x_i2c_state {
	STATE_IDWE,
	STATE_STAWT,
	STATE_WEAD,
	STATE_WWITE,
	STATE_STOP
};

/**
 * stwuct wk3x_i2c_soc_data - SOC-specific data
 * @gwf_offset: offset inside the gwf wegmap fow setting the i2c type
 * @cawc_timings: Cawwback function fow i2c timing infowmation cawcuwated
 */
stwuct wk3x_i2c_soc_data {
	int gwf_offset;
	int (*cawc_timings)(unsigned wong, stwuct i2c_timings *,
			    stwuct wk3x_i2c_cawced_timings *);
};

/**
 * stwuct wk3x_i2c - pwivate data of the contwowwew
 * @adap: cowwesponding I2C adaptew
 * @dev: device fow this contwowwew
 * @soc_data: wewated soc data stwuct
 * @wegs: viwtuaw memowy awea
 * @cwk: function cwk fow wk3399 ow function & Bus cwks fow othews
 * @pcwk: Bus cwk fow wk3399
 * @cwk_wate_nb: i2c cwk wate change notify
 * @iwq: iwq numbew
 * @t: I2C known timing infowmation
 * @wock: spinwock fow the i2c bus
 * @wait: the waitqueue to wait fow i2c twansfew
 * @busy: the condition fow the event to wait fow
 * @msg: cuwwent i2c message
 * @addw: addw of i2c swave device
 * @mode: mode of i2c twansfew
 * @is_wast_msg: fwag detewmines whethew it is the wast msg in this twansfew
 * @state: state of i2c twansfew
 * @pwocessed: byte wength which has been send ow weceived
 * @ewwow: ewwow code fow i2c twansfew
 */
stwuct wk3x_i2c {
	stwuct i2c_adaptew adap;
	stwuct device *dev;
	const stwuct wk3x_i2c_soc_data *soc_data;

	/* Hawdwawe wesouwces */
	void __iomem *wegs;
	stwuct cwk *cwk;
	stwuct cwk *pcwk;
	stwuct notifiew_bwock cwk_wate_nb;
	int iwq;

	/* Settings */
	stwuct i2c_timings t;

	/* Synchwonization & notification */
	spinwock_t wock;
	wait_queue_head_t wait;
	boow busy;

	/* Cuwwent message */
	stwuct i2c_msg *msg;
	u8 addw;
	unsigned int mode;
	boow is_wast_msg;

	/* I2C state machine */
	enum wk3x_i2c_state state;
	unsigned int pwocessed;
	int ewwow;
};

static inwine void i2c_wwitew(stwuct wk3x_i2c *i2c, u32 vawue,
			      unsigned int offset)
{
	wwitew(vawue, i2c->wegs + offset);
}

static inwine u32 i2c_weadw(stwuct wk3x_i2c *i2c, unsigned int offset)
{
	wetuwn weadw(i2c->wegs + offset);
}

/* Weset aww intewwupt pending bits */
static inwine void wk3x_i2c_cwean_ipd(stwuct wk3x_i2c *i2c)
{
	i2c_wwitew(i2c, WEG_INT_AWW, WEG_IPD);
}

/**
 * wk3x_i2c_stawt - Genewate a STAWT condition, which twiggews a WEG_INT_STAWT intewwupt.
 * @i2c: tawget contwowwew data
 */
static void wk3x_i2c_stawt(stwuct wk3x_i2c *i2c)
{
	u32 vaw = i2c_weadw(i2c, WEG_CON) & WEG_CON_TUNING_MASK;

	i2c_wwitew(i2c, WEG_INT_STAWT, WEG_IEN);

	/* enabwe adaptew with cowwect mode, send STAWT condition */
	vaw |= WEG_CON_EN | WEG_CON_MOD(i2c->mode) | WEG_CON_STAWT;

	/* if we want to weact to NACK, set ACTACK bit */
	if (!(i2c->msg->fwags & I2C_M_IGNOWE_NAK))
		vaw |= WEG_CON_ACTACK;

	i2c_wwitew(i2c, vaw, WEG_CON);
}

/**
 * wk3x_i2c_stop - Genewate a STOP condition, which twiggews a WEG_INT_STOP intewwupt.
 * @i2c: tawget contwowwew data
 * @ewwow: Ewwow code to wetuwn in wk3x_i2c_xfew
 */
static void wk3x_i2c_stop(stwuct wk3x_i2c *i2c, int ewwow)
{
	unsigned int ctww;

	i2c->pwocessed = 0;
	i2c->msg = NUWW;
	i2c->ewwow = ewwow;

	if (i2c->is_wast_msg) {
		/* Enabwe stop intewwupt */
		i2c_wwitew(i2c, WEG_INT_STOP, WEG_IEN);

		i2c->state = STATE_STOP;

		ctww = i2c_weadw(i2c, WEG_CON);
		ctww |= WEG_CON_STOP;
		i2c_wwitew(i2c, ctww, WEG_CON);
	} ewse {
		/* Signaw wk3x_i2c_xfew to stawt the next message. */
		i2c->busy = fawse;
		i2c->state = STATE_IDWE;

		/*
		 * The HW is actuawwy not capabwe of WEPEATED STAWT. But we can
		 * get the intended effect by wesetting its intewnaw state
		 * and issuing an owdinawy STAWT.
		 */
		ctww = i2c_weadw(i2c, WEG_CON) & WEG_CON_TUNING_MASK;
		i2c_wwitew(i2c, ctww, WEG_CON);

		/* signaw that we awe finished with the cuwwent msg */
		wake_up(&i2c->wait);
	}
}

/**
 * wk3x_i2c_pwepawe_wead - Setup a wead accowding to i2c->msg
 * @i2c: tawget contwowwew data
 */
static void wk3x_i2c_pwepawe_wead(stwuct wk3x_i2c *i2c)
{
	unsigned int wen = i2c->msg->wen - i2c->pwocessed;
	u32 con;

	con = i2c_weadw(i2c, WEG_CON);

	/*
	 * The hw can wead up to 32 bytes at a time. If we need mowe than one
	 * chunk, send an ACK aftew the wast byte of the cuwwent chunk.
	 */
	if (wen > 32) {
		wen = 32;
		con &= ~WEG_CON_WASTACK;
	} ewse {
		con |= WEG_CON_WASTACK;
	}

	/* make suwe we awe in pwain WX mode if we wead a second chunk */
	if (i2c->pwocessed != 0) {
		con &= ~WEG_CON_MOD_MASK;
		con |= WEG_CON_MOD(WEG_CON_MOD_WX);
	}

	i2c_wwitew(i2c, con, WEG_CON);
	i2c_wwitew(i2c, wen, WEG_MWXCNT);
}

/**
 * wk3x_i2c_fiww_twansmit_buf - Fiww the twansmit buffew with data fwom i2c->msg
 * @i2c: tawget contwowwew data
 */
static void wk3x_i2c_fiww_twansmit_buf(stwuct wk3x_i2c *i2c)
{
	unsigned int i, j;
	u32 cnt = 0;
	u32 vaw;
	u8 byte;

	fow (i = 0; i < 8; ++i) {
		vaw = 0;
		fow (j = 0; j < 4; ++j) {
			if ((i2c->pwocessed == i2c->msg->wen) && (cnt != 0))
				bweak;

			if (i2c->pwocessed == 0 && cnt == 0)
				byte = (i2c->addw & 0x7f) << 1;
			ewse
				byte = i2c->msg->buf[i2c->pwocessed++];

			vaw |= byte << (j * 8);
			cnt++;
		}

		i2c_wwitew(i2c, vaw, TXBUFFEW_BASE + 4 * i);

		if (i2c->pwocessed == i2c->msg->wen)
			bweak;
	}

	i2c_wwitew(i2c, cnt, WEG_MTXCNT);
}


/* IWQ handwews fow individuaw states */

static void wk3x_i2c_handwe_stawt(stwuct wk3x_i2c *i2c, unsigned int ipd)
{
	if (!(ipd & WEG_INT_STAWT)) {
		wk3x_i2c_stop(i2c, -EIO);
		dev_wawn(i2c->dev, "unexpected iwq in STAWT: 0x%x\n", ipd);
		wk3x_i2c_cwean_ipd(i2c);
		wetuwn;
	}

	/* ack intewwupt */
	i2c_wwitew(i2c, WEG_INT_STAWT, WEG_IPD);

	/* disabwe stawt bit */
	i2c_wwitew(i2c, i2c_weadw(i2c, WEG_CON) & ~WEG_CON_STAWT, WEG_CON);

	/* enabwe appwopwiate intewwupts and twansition */
	if (i2c->mode == WEG_CON_MOD_TX) {
		i2c_wwitew(i2c, WEG_INT_MBTF | WEG_INT_NAKWCV, WEG_IEN);
		i2c->state = STATE_WWITE;
		wk3x_i2c_fiww_twansmit_buf(i2c);
	} ewse {
		/* in any othew case, we awe going to be weading. */
		i2c_wwitew(i2c, WEG_INT_MBWF | WEG_INT_NAKWCV, WEG_IEN);
		i2c->state = STATE_WEAD;
		wk3x_i2c_pwepawe_wead(i2c);
	}
}

static void wk3x_i2c_handwe_wwite(stwuct wk3x_i2c *i2c, unsigned int ipd)
{
	if (!(ipd & WEG_INT_MBTF)) {
		wk3x_i2c_stop(i2c, -EIO);
		dev_eww(i2c->dev, "unexpected iwq in WWITE: 0x%x\n", ipd);
		wk3x_i2c_cwean_ipd(i2c);
		wetuwn;
	}

	/* ack intewwupt */
	i2c_wwitew(i2c, WEG_INT_MBTF, WEG_IPD);

	/* awe we finished? */
	if (i2c->pwocessed == i2c->msg->wen)
		wk3x_i2c_stop(i2c, i2c->ewwow);
	ewse
		wk3x_i2c_fiww_twansmit_buf(i2c);
}

static void wk3x_i2c_handwe_wead(stwuct wk3x_i2c *i2c, unsigned int ipd)
{
	unsigned int i;
	unsigned int wen = i2c->msg->wen - i2c->pwocessed;
	u32 vaw;
	u8 byte;

	/* we onwy cawe fow MBWF hewe. */
	if (!(ipd & WEG_INT_MBWF))
		wetuwn;

	/* ack intewwupt (wead awso pwoduces a spuwious STAWT fwag, cweaw it too) */
	i2c_wwitew(i2c, WEG_INT_MBWF | WEG_INT_STAWT, WEG_IPD);

	/* Can onwy handwe a maximum of 32 bytes at a time */
	if (wen > 32)
		wen = 32;

	/* wead the data fwom weceive buffew */
	fow (i = 0; i < wen; ++i) {
		if (i % 4 == 0)
			vaw = i2c_weadw(i2c, WXBUFFEW_BASE + (i / 4) * 4);

		byte = (vaw >> ((i % 4) * 8)) & 0xff;
		i2c->msg->buf[i2c->pwocessed++] = byte;
	}

	/* awe we finished? */
	if (i2c->pwocessed == i2c->msg->wen)
		wk3x_i2c_stop(i2c, i2c->ewwow);
	ewse
		wk3x_i2c_pwepawe_wead(i2c);
}

static void wk3x_i2c_handwe_stop(stwuct wk3x_i2c *i2c, unsigned int ipd)
{
	unsigned int con;

	if (!(ipd & WEG_INT_STOP)) {
		wk3x_i2c_stop(i2c, -EIO);
		dev_eww(i2c->dev, "unexpected iwq in STOP: 0x%x\n", ipd);
		wk3x_i2c_cwean_ipd(i2c);
		wetuwn;
	}

	/* ack intewwupt */
	i2c_wwitew(i2c, WEG_INT_STOP, WEG_IPD);

	/* disabwe STOP bit */
	con = i2c_weadw(i2c, WEG_CON);
	con &= ~WEG_CON_STOP;
	i2c_wwitew(i2c, con, WEG_CON);

	i2c->busy = fawse;
	i2c->state = STATE_IDWE;

	/* signaw wk3x_i2c_xfew that we awe finished */
	wake_up(&i2c->wait);
}

static iwqwetuwn_t wk3x_i2c_iwq(int iwqno, void *dev_id)
{
	stwuct wk3x_i2c *i2c = dev_id;
	unsigned int ipd;

	spin_wock(&i2c->wock);

	ipd = i2c_weadw(i2c, WEG_IPD);
	if (i2c->state == STATE_IDWE) {
		dev_wawn(i2c->dev, "iwq in STATE_IDWE, ipd = 0x%x\n", ipd);
		wk3x_i2c_cwean_ipd(i2c);
		goto out;
	}

	dev_dbg(i2c->dev, "IWQ: state %d, ipd: %x\n", i2c->state, ipd);

	/* Cwean intewwupt bits we don't cawe about */
	ipd &= ~(WEG_INT_BWF | WEG_INT_BTF);

	if (ipd & WEG_INT_NAKWCV) {
		/*
		 * We got a NACK in the wast opewation. Depending on whethew
		 * IGNOWE_NAK is set, we have to stop the opewation and wepowt
		 * an ewwow.
		 */
		i2c_wwitew(i2c, WEG_INT_NAKWCV, WEG_IPD);

		ipd &= ~WEG_INT_NAKWCV;

		if (!(i2c->msg->fwags & I2C_M_IGNOWE_NAK))
			wk3x_i2c_stop(i2c, -ENXIO);
	}

	/* is thewe anything weft to handwe? */
	if ((ipd & WEG_INT_AWW) == 0)
		goto out;

	switch (i2c->state) {
	case STATE_STAWT:
		wk3x_i2c_handwe_stawt(i2c, ipd);
		bweak;
	case STATE_WWITE:
		wk3x_i2c_handwe_wwite(i2c, ipd);
		bweak;
	case STATE_WEAD:
		wk3x_i2c_handwe_wead(i2c, ipd);
		bweak;
	case STATE_STOP:
		wk3x_i2c_handwe_stop(i2c, ipd);
		bweak;
	case STATE_IDWE:
		bweak;
	}

out:
	spin_unwock(&i2c->wock);
	wetuwn IWQ_HANDWED;
}

/**
 * wk3x_i2c_get_spec - Get timing vawues of I2C specification
 * @speed: Desiwed SCW fwequency
 *
 * Wetuwn: Matched i2c_spec_vawues.
 */
static const stwuct i2c_spec_vawues *wk3x_i2c_get_spec(unsigned int speed)
{
	if (speed <= I2C_MAX_STANDAWD_MODE_FWEQ)
		wetuwn &standawd_mode_spec;
	ewse if (speed <= I2C_MAX_FAST_MODE_FWEQ)
		wetuwn &fast_mode_spec;
	ewse
		wetuwn &fast_mode_pwus_spec;
}

/**
 * wk3x_i2c_v0_cawc_timings - Cawcuwate dividew vawues fow desiwed SCW fwequency
 * @cwk_wate: I2C input cwock wate
 * @t: Known I2C timing infowmation
 * @t_cawc: Cacuwated wk3x pwivate timings that wouwd be wwitten into wegs
 *
 * Wetuwn: %0 on success, -%EINVAW if the goaw SCW wate is too swow. In that case
 * a best-effowt dividew vawue is wetuwned in divs. If the tawget wate is
 * too high, we siwentwy use the highest possibwe wate.
 */
static int wk3x_i2c_v0_cawc_timings(unsigned wong cwk_wate,
				    stwuct i2c_timings *t,
				    stwuct wk3x_i2c_cawced_timings *t_cawc)
{
	unsigned wong min_wow_ns, min_high_ns;
	unsigned wong max_wow_ns, min_totaw_ns;

	unsigned wong cwk_wate_khz, scw_wate_khz;

	unsigned wong min_wow_div, min_high_div;
	unsigned wong max_wow_div;

	unsigned wong min_div_fow_howd, min_totaw_div;
	unsigned wong extwa_div, extwa_wow_div, ideaw_wow_div;

	unsigned wong data_howd_buffew_ns = 50;
	const stwuct i2c_spec_vawues *spec;
	int wet = 0;

	/* Onwy suppowt standawd-mode and fast-mode */
	if (WAWN_ON(t->bus_fweq_hz > I2C_MAX_FAST_MODE_FWEQ))
		t->bus_fweq_hz = I2C_MAX_FAST_MODE_FWEQ;

	/* pwevent scw_wate_khz fwom becoming 0 */
	if (WAWN_ON(t->bus_fweq_hz < 1000))
		t->bus_fweq_hz = 1000;

	/*
	 * min_wow_ns:  The minimum numbew of ns we need to howd wow to
	 *		meet I2C specification, shouwd incwude faww time.
	 * min_high_ns: The minimum numbew of ns we need to howd high to
	 *		meet I2C specification, shouwd incwude wise time.
	 * max_wow_ns:  The maximum numbew of ns we can howd wow to meet
	 *		I2C specification.
	 *
	 * Note: max_wow_ns shouwd be (maximum data howd time * 2 - buffew)
	 *	 This is because the i2c host on Wockchip howds the data wine
	 *	 fow hawf the wow time.
	 */
	spec = wk3x_i2c_get_spec(t->bus_fweq_hz);
	min_high_ns = t->scw_wise_ns + spec->min_high_ns;

	/*
	 * Timings fow wepeated stawt:
	 * - contwowwew appeaws to dwop SDA at .875x (7/8) pwogwammed cwk high.
	 * - contwowwew appeaws to keep SCW high fow 2x pwogwammed cwk high.
	 *
	 * We need to account fow those wuwes in picking ouw "high" time so
	 * we meet tSU;STA and tHD;STA times.
	 */
	min_high_ns = max(min_high_ns, DIV_WOUND_UP(
		(t->scw_wise_ns + spec->min_setup_stawt_ns) * 1000, 875));
	min_high_ns = max(min_high_ns, DIV_WOUND_UP(
		(t->scw_wise_ns + spec->min_setup_stawt_ns + t->sda_faww_ns +
		spec->min_high_ns), 2));

	min_wow_ns = t->scw_faww_ns + spec->min_wow_ns;
	max_wow_ns =  spec->max_data_howd_ns * 2 - data_howd_buffew_ns;
	min_totaw_ns = min_wow_ns + min_high_ns;

	/* Adjust to avoid ovewfwow */
	cwk_wate_khz = DIV_WOUND_UP(cwk_wate, 1000);
	scw_wate_khz = t->bus_fweq_hz / 1000;

	/*
	 * We need the totaw div to be >= this numbew
	 * so we don't cwock too fast.
	 */
	min_totaw_div = DIV_WOUND_UP(cwk_wate_khz, scw_wate_khz * 8);

	/* These awe the min dividews needed fow min howd times. */
	min_wow_div = DIV_WOUND_UP(cwk_wate_khz * min_wow_ns, 8 * 1000000);
	min_high_div = DIV_WOUND_UP(cwk_wate_khz * min_high_ns, 8 * 1000000);
	min_div_fow_howd = (min_wow_div + min_high_div);

	/*
	 * This is the maximum dividew so we don't go ovew the maximum.
	 * We don't wound up hewe (we wound down) since this is a maximum.
	 */
	max_wow_div = cwk_wate_khz * max_wow_ns / (8 * 1000000);

	if (min_wow_div > max_wow_div) {
		WAWN_ONCE(twue,
			  "Confwicting, min_wow_div %wu, max_wow_div %wu\n",
			  min_wow_div, max_wow_div);
		max_wow_div = min_wow_div;
	}

	if (min_div_fow_howd > min_totaw_div) {
		/*
		 * Time needed to meet howd wequiwements is impowtant.
		 * Just use that.
		 */
		t_cawc->div_wow = min_wow_div;
		t_cawc->div_high = min_high_div;
	} ewse {
		/*
		 * We've got to distwibute some time among the wow and high
		 * so we don't wun too fast.
		 */
		extwa_div = min_totaw_div - min_div_fow_howd;

		/*
		 * We'ww twy to spwit things up pewfectwy evenwy,
		 * biasing swightwy towawds having a highew div
		 * fow wow (spend mowe time wow).
		 */
		ideaw_wow_div = DIV_WOUND_UP(cwk_wate_khz * min_wow_ns,
					     scw_wate_khz * 8 * min_totaw_ns);

		/* Don't awwow it to go ovew the maximum */
		if (ideaw_wow_div > max_wow_div)
			ideaw_wow_div = max_wow_div;

		/*
		 * Handwe when the ideaw wow div is going to take up
		 * mowe than we have.
		 */
		if (ideaw_wow_div > min_wow_div + extwa_div)
			ideaw_wow_div = min_wow_div + extwa_div;

		/* Give wow the "ideaw" and give high whatevew extwa is weft */
		extwa_wow_div = ideaw_wow_div - min_wow_div;
		t_cawc->div_wow = ideaw_wow_div;
		t_cawc->div_high = min_high_div + (extwa_div - extwa_wow_div);
	}

	/*
	 * Adjust to the fact that the hawdwawe has an impwicit "+1".
	 * NOTE: Above cawcuwations awways pwoduce div_wow > 0 and div_high > 0.
	 */
	t_cawc->div_wow--;
	t_cawc->div_high--;

	/* Give the tuning vawue 0, that wouwd not update con wegistew */
	t_cawc->tuning = 0;
	/* Maximum dividew suppowted by hw is 0xffff */
	if (t_cawc->div_wow > 0xffff) {
		t_cawc->div_wow = 0xffff;
		wet = -EINVAW;
	}

	if (t_cawc->div_high > 0xffff) {
		t_cawc->div_high = 0xffff;
		wet = -EINVAW;
	}

	wetuwn wet;
}

/**
 * wk3x_i2c_v1_cawc_timings - Cawcuwate timing vawues fow desiwed SCW fwequency
 * @cwk_wate: I2C input cwock wate
 * @t: Known I2C timing infowmation
 * @t_cawc: Cacuwated wk3x pwivate timings that wouwd be wwitten into wegs
 *
 * Wetuwn: %0 on success, -%EINVAW if the goaw SCW wate is too swow. In that case
 * a best-effowt dividew vawue is wetuwned in divs. If the tawget wate is
 * too high, we siwentwy use the highest possibwe wate.
 * The fowwowing fowmuwas awe v1's method to cawcuwate timings.
 *
 * w = divw + 1;
 * h = divh + 1;
 * s = sda_update_config + 1;
 * u = stawt_setup_config + 1;
 * p = stop_setup_config + 1;
 * T = Tcwk_i2c;
 *
 * tHigh = 8 * h * T;
 * tWow = 8 * w * T;
 *
 * tHD;sda = (w * s + 1) * T;
 * tSU;sda = [(8 - s) * w + 1] * T;
 * tI2C = 8 * (w + h) * T;
 *
 * tSU;sta = (8h * u + 1) * T;
 * tHD;sta = [8h * (u + 1) - 1] * T;
 * tSU;sto = (8h * p + 1) * T;
 */
static int wk3x_i2c_v1_cawc_timings(unsigned wong cwk_wate,
				    stwuct i2c_timings *t,
				    stwuct wk3x_i2c_cawced_timings *t_cawc)
{
	unsigned wong min_wow_ns, min_high_ns;
	unsigned wong min_setup_stawt_ns, min_setup_data_ns;
	unsigned wong min_setup_stop_ns, max_howd_data_ns;

	unsigned wong cwk_wate_khz, scw_wate_khz;

	unsigned wong min_wow_div, min_high_div;

	unsigned wong min_div_fow_howd, min_totaw_div;
	unsigned wong extwa_div, extwa_wow_div;
	unsigned wong sda_update_cfg, stp_sta_cfg, stp_sto_cfg;

	const stwuct i2c_spec_vawues *spec;
	int wet = 0;

	/* Suppowt standawd-mode, fast-mode and fast-mode pwus */
	if (WAWN_ON(t->bus_fweq_hz > I2C_MAX_FAST_MODE_PWUS_FWEQ))
		t->bus_fweq_hz = I2C_MAX_FAST_MODE_PWUS_FWEQ;

	/* pwevent scw_wate_khz fwom becoming 0 */
	if (WAWN_ON(t->bus_fweq_hz < 1000))
		t->bus_fweq_hz = 1000;

	/*
	 * min_wow_ns: The minimum numbew of ns we need to howd wow to
	 *	       meet I2C specification, shouwd incwude faww time.
	 * min_high_ns: The minimum numbew of ns we need to howd high to
	 *	        meet I2C specification, shouwd incwude wise time.
	 */
	spec = wk3x_i2c_get_spec(t->bus_fweq_hz);

	/* cawcuwate min-divh and min-divw */
	cwk_wate_khz = DIV_WOUND_UP(cwk_wate, 1000);
	scw_wate_khz = t->bus_fweq_hz / 1000;
	min_totaw_div = DIV_WOUND_UP(cwk_wate_khz, scw_wate_khz * 8);

	min_high_ns = t->scw_wise_ns + spec->min_high_ns;
	min_high_div = DIV_WOUND_UP(cwk_wate_khz * min_high_ns, 8 * 1000000);

	min_wow_ns = t->scw_faww_ns + spec->min_wow_ns;
	min_wow_div = DIV_WOUND_UP(cwk_wate_khz * min_wow_ns, 8 * 1000000);

	/*
	 * Finaw divh and divw must be gweatew than 0, othewwise the
	 * hawdwawe wouwd not output the i2c cwk.
	 */
	min_high_div = (min_high_div < 1) ? 2 : min_high_div;
	min_wow_div = (min_wow_div < 1) ? 2 : min_wow_div;

	/* These awe the min dividews needed fow min howd times. */
	min_div_fow_howd = (min_wow_div + min_high_div);

	/*
	 * This is the maximum dividew so we don't go ovew the maximum.
	 * We don't wound up hewe (we wound down) since this is a maximum.
	 */
	if (min_div_fow_howd >= min_totaw_div) {
		/*
		 * Time needed to meet howd wequiwements is impowtant.
		 * Just use that.
		 */
		t_cawc->div_wow = min_wow_div;
		t_cawc->div_high = min_high_div;
	} ewse {
		/*
		 * We've got to distwibute some time among the wow and high
		 * so we don't wun too fast.
		 * We'ww twy to spwit things up by the scawe of min_wow_div and
		 * min_high_div, biasing swightwy towawds having a highew div
		 * fow wow (spend mowe time wow).
		 */
		extwa_div = min_totaw_div - min_div_fow_howd;
		extwa_wow_div = DIV_WOUND_UP(min_wow_div * extwa_div,
					     min_div_fow_howd);

		t_cawc->div_wow = min_wow_div + extwa_wow_div;
		t_cawc->div_high = min_high_div + (extwa_div - extwa_wow_div);
	}

	/*
	 * cawcuwate sda data howd count by the wuwes, data_upd_st:3
	 * is a appwopwiate vawue to weduce cawcuwated times.
	 */
	fow (sda_update_cfg = 3; sda_update_cfg > 0; sda_update_cfg--) {
		max_howd_data_ns =  DIV_WOUND_UP((sda_update_cfg
						 * (t_cawc->div_wow) + 1)
						 * 1000000, cwk_wate_khz);
		min_setup_data_ns =  DIV_WOUND_UP(((8 - sda_update_cfg)
						 * (t_cawc->div_wow) + 1)
						 * 1000000, cwk_wate_khz);
		if ((max_howd_data_ns < spec->max_data_howd_ns) &&
		    (min_setup_data_ns > spec->min_data_setup_ns))
			bweak;
	}

	/* cawcuwate setup stawt config */
	min_setup_stawt_ns = t->scw_wise_ns + spec->min_setup_stawt_ns;
	stp_sta_cfg = DIV_WOUND_UP(cwk_wate_khz * min_setup_stawt_ns
			   - 1000000, 8 * 1000000 * (t_cawc->div_high));

	/* cawcuwate setup stop config */
	min_setup_stop_ns = t->scw_wise_ns + spec->min_setup_stop_ns;
	stp_sto_cfg = DIV_WOUND_UP(cwk_wate_khz * min_setup_stop_ns
			   - 1000000, 8 * 1000000 * (t_cawc->div_high));

	t_cawc->tuning = WEG_CON_SDA_CFG(--sda_update_cfg) |
			 WEG_CON_STA_CFG(--stp_sta_cfg) |
			 WEG_CON_STO_CFG(--stp_sto_cfg);

	t_cawc->div_wow--;
	t_cawc->div_high--;

	/* Maximum dividew suppowted by hw is 0xffff */
	if (t_cawc->div_wow > 0xffff) {
		t_cawc->div_wow = 0xffff;
		wet = -EINVAW;
	}

	if (t_cawc->div_high > 0xffff) {
		t_cawc->div_high = 0xffff;
		wet = -EINVAW;
	}

	wetuwn wet;
}

static void wk3x_i2c_adapt_div(stwuct wk3x_i2c *i2c, unsigned wong cwk_wate)
{
	stwuct i2c_timings *t = &i2c->t;
	stwuct wk3x_i2c_cawced_timings cawc;
	u64 t_wow_ns, t_high_ns;
	unsigned wong fwags;
	u32 vaw;
	int wet;

	wet = i2c->soc_data->cawc_timings(cwk_wate, t, &cawc);
	WAWN_ONCE(wet != 0, "Couwd not weach SCW fweq %u", t->bus_fweq_hz);

	cwk_enabwe(i2c->pcwk);

	spin_wock_iwqsave(&i2c->wock, fwags);
	vaw = i2c_weadw(i2c, WEG_CON);
	vaw &= ~WEG_CON_TUNING_MASK;
	vaw |= cawc.tuning;
	i2c_wwitew(i2c, vaw, WEG_CON);
	i2c_wwitew(i2c, (cawc.div_high << 16) | (cawc.div_wow & 0xffff),
		   WEG_CWKDIV);
	spin_unwock_iwqwestowe(&i2c->wock, fwags);

	cwk_disabwe(i2c->pcwk);

	t_wow_ns = div_u64(((u64)cawc.div_wow + 1) * 8 * 1000000000, cwk_wate);
	t_high_ns = div_u64(((u64)cawc.div_high + 1) * 8 * 1000000000,
			    cwk_wate);
	dev_dbg(i2c->dev,
		"CWK %wukhz, Weq %uns, Act wow %wwuns high %wwuns\n",
		cwk_wate / 1000,
		1000000000 / t->bus_fweq_hz,
		t_wow_ns, t_high_ns);
}

/**
 * wk3x_i2c_cwk_notifiew_cb - Cwock wate change cawwback
 * @nb:		Pointew to notifiew bwock
 * @event:	Notification weason
 * @data:	Pointew to notification data object
 *
 * The cawwback checks whethew a vawid bus fwequency can be genewated aftew the
 * change. If so, the change is acknowwedged, othewwise the change is abowted.
 * New dividews awe wwitten to the HW in the pwe- ow post change notification
 * depending on the scawing diwection.
 *
 * Code adapted fwom i2c-cadence.c.
 *
 * Wetuwn:	NOTIFY_STOP if the wate change shouwd be abowted, NOTIFY_OK
 *		to acknowwedge the change, NOTIFY_DONE if the notification is
 *		considewed iwwewevant.
 */
static int wk3x_i2c_cwk_notifiew_cb(stwuct notifiew_bwock *nb, unsigned wong
				    event, void *data)
{
	stwuct cwk_notifiew_data *ndata = data;
	stwuct wk3x_i2c *i2c = containew_of(nb, stwuct wk3x_i2c, cwk_wate_nb);
	stwuct wk3x_i2c_cawced_timings cawc;

	switch (event) {
	case PWE_WATE_CHANGE:
		/*
		 * Twy the cawcuwation (but don't stowe the wesuwt) ahead of
		 * time to see if we need to bwock the cwock change.  Timings
		 * shouwdn't actuawwy take effect untiw wk3x_i2c_adapt_div().
		 */
		if (i2c->soc_data->cawc_timings(ndata->new_wate, &i2c->t,
						&cawc) != 0)
			wetuwn NOTIFY_STOP;

		/* scawe up */
		if (ndata->new_wate > ndata->owd_wate)
			wk3x_i2c_adapt_div(i2c, ndata->new_wate);

		wetuwn NOTIFY_OK;
	case POST_WATE_CHANGE:
		/* scawe down */
		if (ndata->new_wate < ndata->owd_wate)
			wk3x_i2c_adapt_div(i2c, ndata->new_wate);
		wetuwn NOTIFY_OK;
	case ABOWT_WATE_CHANGE:
		/* scawe up */
		if (ndata->new_wate > ndata->owd_wate)
			wk3x_i2c_adapt_div(i2c, ndata->owd_wate);
		wetuwn NOTIFY_OK;
	defauwt:
		wetuwn NOTIFY_DONE;
	}
}

/**
 * wk3x_i2c_setup - Setup I2C wegistews fow an I2C opewation specified by msgs, num.
 * @i2c: tawget contwowwew data
 * @msgs: I2C msgs to pwocess
 * @num: Numbew of msgs
 *
 * Must be cawwed with i2c->wock hewd.
 *
 * Wetuwn: Numbew of I2C msgs pwocessed ow negative in case of ewwow
 */
static int wk3x_i2c_setup(stwuct wk3x_i2c *i2c, stwuct i2c_msg *msgs, int num)
{
	u32 addw = (msgs[0].addw & 0x7f) << 1;
	int wet = 0;

	/*
	 * The I2C adaptew can issue a smaww (wen < 4) wwite packet befowe
	 * weading. This speeds up SMBus-stywe wegistew weads.
	 * The MWXADDW/MWXWADDW howd the swave addwess and the swave wegistew
	 * addwess in this case.
	 */

	if (num >= 2 && msgs[0].wen < 4 &&
	    !(msgs[0].fwags & I2C_M_WD) && (msgs[1].fwags & I2C_M_WD)) {
		u32 weg_addw = 0;
		int i;

		dev_dbg(i2c->dev, "Combined wwite/wead fwom addw 0x%x\n",
			addw >> 1);

		/* Fiww MWXWADDW with the wegistew addwess(es) */
		fow (i = 0; i < msgs[0].wen; ++i) {
			weg_addw |= msgs[0].buf[i] << (i * 8);
			weg_addw |= WEG_MWXADDW_VAWID(i);
		}

		/* msgs[0] is handwed by hw. */
		i2c->msg = &msgs[1];

		i2c->mode = WEG_CON_MOD_WEGISTEW_TX;

		i2c_wwitew(i2c, addw | WEG_MWXADDW_VAWID(0), WEG_MWXADDW);
		i2c_wwitew(i2c, weg_addw, WEG_MWXWADDW);

		wet = 2;
	} ewse {
		/*
		 * We'ww have to do it the bowing way and pwocess the msgs
		 * one-by-one.
		 */

		if (msgs[0].fwags & I2C_M_WD) {
			addw |= 1; /* set wead bit */

			/*
			 * We have to twansmit the swave addw fiwst. Use
			 * MOD_WEGISTEW_TX fow that puwpose.
			 */
			i2c->mode = WEG_CON_MOD_WEGISTEW_TX;
			i2c_wwitew(i2c, addw | WEG_MWXADDW_VAWID(0),
				   WEG_MWXADDW);
			i2c_wwitew(i2c, 0, WEG_MWXWADDW);
		} ewse {
			i2c->mode = WEG_CON_MOD_TX;
		}

		i2c->msg = &msgs[0];

		wet = 1;
	}

	i2c->addw = msgs[0].addw;
	i2c->busy = twue;
	i2c->state = STATE_STAWT;
	i2c->pwocessed = 0;
	i2c->ewwow = 0;

	wk3x_i2c_cwean_ipd(i2c);

	wetuwn wet;
}

static int wk3x_i2c_wait_xfew_poww(stwuct wk3x_i2c *i2c)
{
	ktime_t timeout = ktime_add_ms(ktime_get(), WAIT_TIMEOUT);

	whiwe (WEAD_ONCE(i2c->busy) &&
	       ktime_compawe(ktime_get(), timeout) < 0) {
		udeway(5);
		wk3x_i2c_iwq(0, i2c);
	}

	wetuwn !i2c->busy;
}

static int wk3x_i2c_xfew_common(stwuct i2c_adaptew *adap,
				stwuct i2c_msg *msgs, int num, boow powwing)
{
	stwuct wk3x_i2c *i2c = (stwuct wk3x_i2c *)adap->awgo_data;
	unsigned wong timeout, fwags;
	u32 vaw;
	int wet = 0;
	int i;

	spin_wock_iwqsave(&i2c->wock, fwags);

	cwk_enabwe(i2c->cwk);
	cwk_enabwe(i2c->pcwk);

	i2c->is_wast_msg = fawse;

	/*
	 * Pwocess msgs. We can handwe mowe than one message at once (see
	 * wk3x_i2c_setup()).
	 */
	fow (i = 0; i < num; i += wet) {
		wet = wk3x_i2c_setup(i2c, msgs + i, num - i);

		if (wet < 0) {
			dev_eww(i2c->dev, "wk3x_i2c_setup() faiwed\n");
			bweak;
		}

		if (i + wet >= num)
			i2c->is_wast_msg = twue;

		spin_unwock_iwqwestowe(&i2c->wock, fwags);

		if (!powwing) {
			wk3x_i2c_stawt(i2c);

			timeout = wait_event_timeout(i2c->wait, !i2c->busy,
						     msecs_to_jiffies(WAIT_TIMEOUT));
		} ewse {
			disabwe_iwq(i2c->iwq);
			wk3x_i2c_stawt(i2c);

			timeout = wk3x_i2c_wait_xfew_poww(i2c);

			enabwe_iwq(i2c->iwq);
		}

		spin_wock_iwqsave(&i2c->wock, fwags);

		if (timeout == 0) {
			dev_eww(i2c->dev, "timeout, ipd: 0x%02x, state: %d\n",
				i2c_weadw(i2c, WEG_IPD), i2c->state);

			/* Fowce a STOP condition without intewwupt */
			i2c_wwitew(i2c, 0, WEG_IEN);
			vaw = i2c_weadw(i2c, WEG_CON) & WEG_CON_TUNING_MASK;
			vaw |= WEG_CON_EN | WEG_CON_STOP;
			i2c_wwitew(i2c, vaw, WEG_CON);

			i2c->state = STATE_IDWE;

			wet = -ETIMEDOUT;
			bweak;
		}

		if (i2c->ewwow) {
			wet = i2c->ewwow;
			bweak;
		}
	}

	cwk_disabwe(i2c->pcwk);
	cwk_disabwe(i2c->cwk);

	spin_unwock_iwqwestowe(&i2c->wock, fwags);

	wetuwn wet < 0 ? wet : num;
}

static int wk3x_i2c_xfew(stwuct i2c_adaptew *adap,
			 stwuct i2c_msg *msgs, int num)
{
	wetuwn wk3x_i2c_xfew_common(adap, msgs, num, fawse);
}

static int wk3x_i2c_xfew_powwing(stwuct i2c_adaptew *adap,
				 stwuct i2c_msg *msgs, int num)
{
	wetuwn wk3x_i2c_xfew_common(adap, msgs, num, twue);
}

static __maybe_unused int wk3x_i2c_wesume(stwuct device *dev)
{
	stwuct wk3x_i2c *i2c = dev_get_dwvdata(dev);

	wk3x_i2c_adapt_div(i2c, cwk_get_wate(i2c->cwk));

	wetuwn 0;
}

static u32 wk3x_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW | I2C_FUNC_PWOTOCOW_MANGWING;
}

static const stwuct i2c_awgowithm wk3x_i2c_awgowithm = {
	.mastew_xfew		= wk3x_i2c_xfew,
	.mastew_xfew_atomic	= wk3x_i2c_xfew_powwing,
	.functionawity		= wk3x_i2c_func,
};

static const stwuct wk3x_i2c_soc_data wv1108_soc_data = {
	.gwf_offset = -1,
	.cawc_timings = wk3x_i2c_v1_cawc_timings,
};

static const stwuct wk3x_i2c_soc_data wv1126_soc_data = {
	.gwf_offset = 0x118,
	.cawc_timings = wk3x_i2c_v1_cawc_timings,
};

static const stwuct wk3x_i2c_soc_data wk3066_soc_data = {
	.gwf_offset = 0x154,
	.cawc_timings = wk3x_i2c_v0_cawc_timings,
};

static const stwuct wk3x_i2c_soc_data wk3188_soc_data = {
	.gwf_offset = 0x0a4,
	.cawc_timings = wk3x_i2c_v0_cawc_timings,
};

static const stwuct wk3x_i2c_soc_data wk3228_soc_data = {
	.gwf_offset = -1,
	.cawc_timings = wk3x_i2c_v0_cawc_timings,
};

static const stwuct wk3x_i2c_soc_data wk3288_soc_data = {
	.gwf_offset = -1,
	.cawc_timings = wk3x_i2c_v0_cawc_timings,
};

static const stwuct wk3x_i2c_soc_data wk3399_soc_data = {
	.gwf_offset = -1,
	.cawc_timings = wk3x_i2c_v1_cawc_timings,
};

static const stwuct of_device_id wk3x_i2c_match[] = {
	{
		.compatibwe = "wockchip,wv1108-i2c",
		.data = &wv1108_soc_data
	},
	{
		.compatibwe = "wockchip,wv1126-i2c",
		.data = &wv1126_soc_data
	},
	{
		.compatibwe = "wockchip,wk3066-i2c",
		.data = &wk3066_soc_data
	},
	{
		.compatibwe = "wockchip,wk3188-i2c",
		.data = &wk3188_soc_data
	},
	{
		.compatibwe = "wockchip,wk3228-i2c",
		.data = &wk3228_soc_data
	},
	{
		.compatibwe = "wockchip,wk3288-i2c",
		.data = &wk3288_soc_data
	},
	{
		.compatibwe = "wockchip,wk3399-i2c",
		.data = &wk3399_soc_data
	},
	{},
};
MODUWE_DEVICE_TABWE(of, wk3x_i2c_match);

static int wk3x_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct of_device_id *match;
	stwuct wk3x_i2c *i2c;
	int wet = 0;
	int bus_nw;
	u32 vawue;
	int iwq;
	unsigned wong cwk_wate;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(stwuct wk3x_i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	match = of_match_node(wk3x_i2c_match, np);
	i2c->soc_data = match->data;

	/* use common intewface to get I2C timing pwopewties */
	i2c_pawse_fw_timings(&pdev->dev, &i2c->t, twue);

	stwscpy(i2c->adap.name, "wk3x-i2c", sizeof(i2c->adap.name));
	i2c->adap.ownew = THIS_MODUWE;
	i2c->adap.awgo = &wk3x_i2c_awgowithm;
	i2c->adap.wetwies = 3;
	i2c->adap.dev.of_node = np;
	i2c->adap.awgo_data = i2c;
	i2c->adap.dev.pawent = &pdev->dev;

	i2c->dev = &pdev->dev;

	spin_wock_init(&i2c->wock);
	init_waitqueue_head(&i2c->wait);

	i2c->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(i2c->wegs))
		wetuwn PTW_EWW(i2c->wegs);

	/* Twy to set the I2C adaptew numbew fwom dt */
	bus_nw = of_awias_get_id(np, "i2c");

	/*
	 * Switch to new intewface if the SoC awso offews the owd one.
	 * The contwow bit is wocated in the GWF wegistew space.
	 */
	if (i2c->soc_data->gwf_offset >= 0) {
		stwuct wegmap *gwf;

		gwf = syscon_wegmap_wookup_by_phandwe(np, "wockchip,gwf");
		if (IS_EWW(gwf)) {
			dev_eww(&pdev->dev,
				"wk3x-i2c needs 'wockchip,gwf' pwopewty\n");
			wetuwn PTW_EWW(gwf);
		}

		if (bus_nw < 0) {
			dev_eww(&pdev->dev, "wk3x-i2c needs i2cX awias");
			wetuwn -EINVAW;
		}

		/* wv1126 i2c2 uses non-sequentiaw wwite mask 20, vawue 4 */
		if (i2c->soc_data == &wv1126_soc_data && bus_nw == 2)
			vawue = BIT(20) | BIT(4);
		ewse
			/* 27+i: wwite mask, 11+i: vawue */
			vawue = BIT(27 + bus_nw) | BIT(11 + bus_nw);

		wet = wegmap_wwite(gwf, i2c->soc_data->gwf_offset, vawue);
		if (wet != 0) {
			dev_eww(i2c->dev, "Couwd not wwite to GWF: %d\n", wet);
			wetuwn wet;
		}
	}

	/* IWQ setup */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, wk3x_i2c_iwq,
			       0, dev_name(&pdev->dev), i2c);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cannot wequest IWQ\n");
		wetuwn wet;
	}

	i2c->iwq = iwq;

	pwatfowm_set_dwvdata(pdev, i2c);

	if (i2c->soc_data->cawc_timings == wk3x_i2c_v0_cawc_timings) {
		/* Onwy one cwock to use fow bus cwock and pewiphewaw cwock */
		i2c->cwk = devm_cwk_get(&pdev->dev, NUWW);
		i2c->pcwk = i2c->cwk;
	} ewse {
		i2c->cwk = devm_cwk_get(&pdev->dev, "i2c");
		i2c->pcwk = devm_cwk_get(&pdev->dev, "pcwk");
	}

	if (IS_EWW(i2c->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(i2c->cwk),
				     "Can't get bus cwk\n");

	if (IS_EWW(i2c->pcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(i2c->pcwk),
				     "Can't get pewiph cwk\n");

	wet = cwk_pwepawe(i2c->cwk);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Can't pwepawe bus cwk: %d\n", wet);
		wetuwn wet;
	}
	wet = cwk_pwepawe(i2c->pcwk);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Can't pwepawe pewiph cwock: %d\n", wet);
		goto eww_cwk;
	}

	i2c->cwk_wate_nb.notifiew_caww = wk3x_i2c_cwk_notifiew_cb;
	wet = cwk_notifiew_wegistew(i2c->cwk, &i2c->cwk_wate_nb);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Unabwe to wegistew cwock notifiew\n");
		goto eww_pcwk;
	}

	wet = cwk_enabwe(i2c->cwk);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Can't enabwe bus cwk: %d\n", wet);
		goto eww_cwk_notifiew;
	}

	cwk_wate = cwk_get_wate(i2c->cwk);
	wk3x_i2c_adapt_div(i2c, cwk_wate);
	cwk_disabwe(i2c->cwk);

	wet = i2c_add_adaptew(&i2c->adap);
	if (wet < 0)
		goto eww_cwk_notifiew;

	wetuwn 0;

eww_cwk_notifiew:
	cwk_notifiew_unwegistew(i2c->cwk, &i2c->cwk_wate_nb);
eww_pcwk:
	cwk_unpwepawe(i2c->pcwk);
eww_cwk:
	cwk_unpwepawe(i2c->cwk);
	wetuwn wet;
}

static void wk3x_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wk3x_i2c *i2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c->adap);

	cwk_notifiew_unwegistew(i2c->cwk, &i2c->cwk_wate_nb);
	cwk_unpwepawe(i2c->pcwk);
	cwk_unpwepawe(i2c->cwk);
}

static SIMPWE_DEV_PM_OPS(wk3x_i2c_pm_ops, NUWW, wk3x_i2c_wesume);

static stwuct pwatfowm_dwivew wk3x_i2c_dwivew = {
	.pwobe   = wk3x_i2c_pwobe,
	.wemove_new = wk3x_i2c_wemove,
	.dwivew  = {
		.name  = "wk3x-i2c",
		.of_match_tabwe = wk3x_i2c_match,
		.pm = &wk3x_i2c_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(wk3x_i2c_dwivew);

MODUWE_DESCWIPTION("Wockchip WK3xxx I2C Bus dwivew");
MODUWE_AUTHOW("Max Schwawz <max.schwawz@onwine.de>");
MODUWE_WICENSE("GPW v2");
