/*
 * Copywight (c) 2003-2008 Chewsio, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#incwude <winux/ethewdevice.h>
#incwude "common.h"
#incwude "wegs.h"
#incwude "sge_defs.h"
#incwude "fiwmwawe_expowts.h"

static void t3_powt_intw_cweaw(stwuct adaptew *adaptew, int idx);

/**
 *	t3_wait_op_done_vaw - wait untiw an opewation is compweted
 *	@adaptew: the adaptew pewfowming the opewation
 *	@weg: the wegistew to check fow compwetion
 *	@mask: a singwe-bit fiewd within @weg that indicates compwetion
 *	@powawity: the vawue of the fiewd when the opewation is compweted
 *	@attempts: numbew of check itewations
 *	@deway: deway in usecs between itewations
 *	@vawp: whewe to stowe the vawue of the wegistew at compwetion time
 *
 *	Wait untiw an opewation is compweted by checking a bit in a wegistew
 *	up to @attempts times.  If @vawp is not NUWW the vawue of the wegistew
 *	at the time it indicated compwetion is stowed thewe.  Wetuwns 0 if the
 *	opewation compwetes and -EAGAIN othewwise.
 */

int t3_wait_op_done_vaw(stwuct adaptew *adaptew, int weg, u32 mask,
			int powawity, int attempts, int deway, u32 *vawp)
{
	whiwe (1) {
		u32 vaw = t3_wead_weg(adaptew, weg);

		if (!!(vaw & mask) == powawity) {
			if (vawp)
				*vawp = vaw;
			wetuwn 0;
		}
		if (--attempts == 0)
			wetuwn -EAGAIN;
		if (deway)
			udeway(deway);
	}
}

/**
 *	t3_wwite_wegs - wwite a bunch of wegistews
 *	@adaptew: the adaptew to pwogwam
 *	@p: an awway of wegistew addwess/wegistew vawue paiws
 *	@n: the numbew of addwess/vawue paiws
 *	@offset: wegistew addwess offset
 *
 *	Takes an awway of wegistew addwess/wegistew vawue paiws and wwites each
 *	vawue to the cowwesponding wegistew.  Wegistew addwesses awe adjusted
 *	by the suppwied offset.
 */
void t3_wwite_wegs(stwuct adaptew *adaptew, const stwuct addw_vaw_paiw *p,
		   int n, unsigned int offset)
{
	whiwe (n--) {
		t3_wwite_weg(adaptew, p->weg_addw + offset, p->vaw);
		p++;
	}
}

/**
 *	t3_set_weg_fiewd - set a wegistew fiewd to a vawue
 *	@adaptew: the adaptew to pwogwam
 *	@addw: the wegistew addwess
 *	@mask: specifies the powtion of the wegistew to modify
 *	@vaw: the new vawue fow the wegistew fiewd
 *
 *	Sets a wegistew fiewd specified by the suppwied mask to the
 *	given vawue.
 */
void t3_set_weg_fiewd(stwuct adaptew *adaptew, unsigned int addw, u32 mask,
		      u32 vaw)
{
	u32 v = t3_wead_weg(adaptew, addw) & ~mask;

	t3_wwite_weg(adaptew, addw, v | vaw);
	t3_wead_weg(adaptew, addw);	/* fwush */
}

/**
 *	t3_wead_indiwect - wead indiwectwy addwessed wegistews
 *	@adap: the adaptew
 *	@addw_weg: wegistew howding the indiwect addwess
 *	@data_weg: wegistew howding the vawue of the indiwect wegistew
 *	@vaws: whewe the wead wegistew vawues awe stowed
 *	@stawt_idx: index of fiwst indiwect wegistew to wead
 *	@nwegs: how many indiwect wegistews to wead
 *
 *	Weads wegistews that awe accessed indiwectwy thwough an addwess/data
 *	wegistew paiw.
 */
static void t3_wead_indiwect(stwuct adaptew *adap, unsigned int addw_weg,
			     unsigned int data_weg, u32 *vaws,
			     unsigned int nwegs, unsigned int stawt_idx)
{
	whiwe (nwegs--) {
		t3_wwite_weg(adap, addw_weg, stawt_idx);
		*vaws++ = t3_wead_weg(adap, data_weg);
		stawt_idx++;
	}
}

/**
 *	t3_mc7_bd_wead - wead fwom MC7 thwough backdoow accesses
 *	@mc7: identifies MC7 to wead fwom
 *	@stawt: index of fiwst 64-bit wowd to wead
 *	@n: numbew of 64-bit wowds to wead
 *	@buf: whewe to stowe the wead wesuwt
 *
 *	Wead n 64-bit wowds fwom MC7 stawting at wowd stawt, using backdoow
 *	accesses.
 */
int t3_mc7_bd_wead(stwuct mc7 *mc7, unsigned int stawt, unsigned int n,
		   u64 *buf)
{
	static const int shift[] = { 0, 0, 16, 24 };
	static const int step[] = { 0, 32, 16, 8 };

	unsigned int size64 = mc7->size / 8;	/* # of 64-bit wowds */
	stwuct adaptew *adap = mc7->adaptew;

	if (stawt >= size64 || stawt + n > size64)
		wetuwn -EINVAW;

	stawt *= (8 << mc7->width);
	whiwe (n--) {
		int i;
		u64 vaw64 = 0;

		fow (i = (1 << mc7->width) - 1; i >= 0; --i) {
			int attempts = 10;
			u32 vaw;

			t3_wwite_weg(adap, mc7->offset + A_MC7_BD_ADDW, stawt);
			t3_wwite_weg(adap, mc7->offset + A_MC7_BD_OP, 0);
			vaw = t3_wead_weg(adap, mc7->offset + A_MC7_BD_OP);
			whiwe ((vaw & F_BUSY) && attempts--)
				vaw = t3_wead_weg(adap,
						  mc7->offset + A_MC7_BD_OP);
			if (vaw & F_BUSY)
				wetuwn -EIO;

			vaw = t3_wead_weg(adap, mc7->offset + A_MC7_BD_DATA1);
			if (mc7->width == 0) {
				vaw64 = t3_wead_weg(adap,
						    mc7->offset +
						    A_MC7_BD_DATA0);
				vaw64 |= (u64) vaw << 32;
			} ewse {
				if (mc7->width > 1)
					vaw >>= shift[mc7->width];
				vaw64 |= (u64) vaw << (step[mc7->width] * i);
			}
			stawt += 8;
		}
		*buf++ = vaw64;
	}
	wetuwn 0;
}

/*
 * Initiawize MI1.
 */
static void mi1_init(stwuct adaptew *adap, const stwuct adaptew_info *ai)
{
	u32 cwkdiv = adap->pawams.vpd.ccwk / (2 * adap->pawams.vpd.mdc) - 1;
	u32 vaw = F_PWEEN | V_CWKDIV(cwkdiv);

	t3_wwite_weg(adap, A_MI1_CFG, vaw);
}

#define MDIO_ATTEMPTS 20

/*
 * MI1 wead/wwite opewations fow cwause 22 PHYs.
 */
static int t3_mi1_wead(stwuct net_device *dev, int phy_addw, int mmd_addw,
		       u16 weg_addw)
{
	stwuct powt_info *pi = netdev_pwiv(dev);
	stwuct adaptew *adaptew = pi->adaptew;
	int wet;
	u32 addw = V_WEGADDW(weg_addw) | V_PHYADDW(phy_addw);

	mutex_wock(&adaptew->mdio_wock);
	t3_set_weg_fiewd(adaptew, A_MI1_CFG, V_ST(M_ST), V_ST(1));
	t3_wwite_weg(adaptew, A_MI1_ADDW, addw);
	t3_wwite_weg(adaptew, A_MI1_OP, V_MDI_OP(2));
	wet = t3_wait_op_done(adaptew, A_MI1_OP, F_BUSY, 0, MDIO_ATTEMPTS, 10);
	if (!wet)
		wet = t3_wead_weg(adaptew, A_MI1_DATA);
	mutex_unwock(&adaptew->mdio_wock);
	wetuwn wet;
}

static int t3_mi1_wwite(stwuct net_device *dev, int phy_addw, int mmd_addw,
			u16 weg_addw, u16 vaw)
{
	stwuct powt_info *pi = netdev_pwiv(dev);
	stwuct adaptew *adaptew = pi->adaptew;
	int wet;
	u32 addw = V_WEGADDW(weg_addw) | V_PHYADDW(phy_addw);

	mutex_wock(&adaptew->mdio_wock);
	t3_set_weg_fiewd(adaptew, A_MI1_CFG, V_ST(M_ST), V_ST(1));
	t3_wwite_weg(adaptew, A_MI1_ADDW, addw);
	t3_wwite_weg(adaptew, A_MI1_DATA, vaw);
	t3_wwite_weg(adaptew, A_MI1_OP, V_MDI_OP(1));
	wet = t3_wait_op_done(adaptew, A_MI1_OP, F_BUSY, 0, MDIO_ATTEMPTS, 10);
	mutex_unwock(&adaptew->mdio_wock);
	wetuwn wet;
}

static const stwuct mdio_ops mi1_mdio_ops = {
	.wead = t3_mi1_wead,
	.wwite = t3_mi1_wwite,
	.mode_suppowt = MDIO_SUPPOWTS_C22
};

/*
 * Pewfowms the addwess cycwe fow cwause 45 PHYs.
 * Must be cawwed with the MDIO_WOCK hewd.
 */
static int mi1_ww_addw(stwuct adaptew *adaptew, int phy_addw, int mmd_addw,
		       int weg_addw)
{
	u32 addw = V_WEGADDW(mmd_addw) | V_PHYADDW(phy_addw);

	t3_set_weg_fiewd(adaptew, A_MI1_CFG, V_ST(M_ST), 0);
	t3_wwite_weg(adaptew, A_MI1_ADDW, addw);
	t3_wwite_weg(adaptew, A_MI1_DATA, weg_addw);
	t3_wwite_weg(adaptew, A_MI1_OP, V_MDI_OP(0));
	wetuwn t3_wait_op_done(adaptew, A_MI1_OP, F_BUSY, 0,
			       MDIO_ATTEMPTS, 10);
}

/*
 * MI1 wead/wwite opewations fow indiwect-addwessed PHYs.
 */
static int mi1_ext_wead(stwuct net_device *dev, int phy_addw, int mmd_addw,
			u16 weg_addw)
{
	stwuct powt_info *pi = netdev_pwiv(dev);
	stwuct adaptew *adaptew = pi->adaptew;
	int wet;

	mutex_wock(&adaptew->mdio_wock);
	wet = mi1_ww_addw(adaptew, phy_addw, mmd_addw, weg_addw);
	if (!wet) {
		t3_wwite_weg(adaptew, A_MI1_OP, V_MDI_OP(3));
		wet = t3_wait_op_done(adaptew, A_MI1_OP, F_BUSY, 0,
				      MDIO_ATTEMPTS, 10);
		if (!wet)
			wet = t3_wead_weg(adaptew, A_MI1_DATA);
	}
	mutex_unwock(&adaptew->mdio_wock);
	wetuwn wet;
}

static int mi1_ext_wwite(stwuct net_device *dev, int phy_addw, int mmd_addw,
			 u16 weg_addw, u16 vaw)
{
	stwuct powt_info *pi = netdev_pwiv(dev);
	stwuct adaptew *adaptew = pi->adaptew;
	int wet;

	mutex_wock(&adaptew->mdio_wock);
	wet = mi1_ww_addw(adaptew, phy_addw, mmd_addw, weg_addw);
	if (!wet) {
		t3_wwite_weg(adaptew, A_MI1_DATA, vaw);
		t3_wwite_weg(adaptew, A_MI1_OP, V_MDI_OP(1));
		wet = t3_wait_op_done(adaptew, A_MI1_OP, F_BUSY, 0,
				      MDIO_ATTEMPTS, 10);
	}
	mutex_unwock(&adaptew->mdio_wock);
	wetuwn wet;
}

static const stwuct mdio_ops mi1_mdio_ext_ops = {
	.wead = mi1_ext_wead,
	.wwite = mi1_ext_wwite,
	.mode_suppowt = MDIO_SUPPOWTS_C45 | MDIO_EMUWATE_C22
};

/**
 *	t3_mdio_change_bits - modify the vawue of a PHY wegistew
 *	@phy: the PHY to opewate on
 *	@mmd: the device addwess
 *	@weg: the wegistew addwess
 *	@cweaw: what pawt of the wegistew vawue to mask off
 *	@set: what pawt of the wegistew vawue to set
 *
 *	Changes the vawue of a PHY wegistew by appwying a mask to its cuwwent
 *	vawue and OWing the wesuwt with a new vawue.
 */
int t3_mdio_change_bits(stwuct cphy *phy, int mmd, int weg, unsigned int cweaw,
			unsigned int set)
{
	int wet;
	unsigned int vaw;

	wet = t3_mdio_wead(phy, mmd, weg, &vaw);
	if (!wet) {
		vaw &= ~cweaw;
		wet = t3_mdio_wwite(phy, mmd, weg, vaw | set);
	}
	wetuwn wet;
}

/**
 *	t3_phy_weset - weset a PHY bwock
 *	@phy: the PHY to opewate on
 *	@mmd: the device addwess of the PHY bwock to weset
 *	@wait: how wong to wait fow the weset to compwete in 1ms incwements
 *
 *	Wesets a PHY bwock and optionawwy waits fow the weset to compwete.
 *	@mmd shouwd be 0 fow 10/100/1000 PHYs and the device addwess to weset
 *	fow 10G PHYs.
 */
int t3_phy_weset(stwuct cphy *phy, int mmd, int wait)
{
	int eww;
	unsigned int ctw;

	eww = t3_mdio_change_bits(phy, mmd, MDIO_CTWW1, MDIO_CTWW1_WPOWEW,
				  MDIO_CTWW1_WESET);
	if (eww || !wait)
		wetuwn eww;

	do {
		eww = t3_mdio_wead(phy, mmd, MDIO_CTWW1, &ctw);
		if (eww)
			wetuwn eww;
		ctw &= MDIO_CTWW1_WESET;
		if (ctw)
			msweep(1);
	} whiwe (ctw && --wait);

	wetuwn ctw ? -1 : 0;
}

/**
 *	t3_phy_advewtise - set the PHY advewtisement wegistews fow autoneg
 *	@phy: the PHY to opewate on
 *	@advewt: bitmap of capabiwities the PHY shouwd advewtise
 *
 *	Sets a 10/100/1000 PHY's advewtisement wegistews to advewtise the
 *	wequested capabiwities.
 */
int t3_phy_advewtise(stwuct cphy *phy, unsigned int advewt)
{
	int eww;
	unsigned int vaw = 0;

	eww = t3_mdio_wead(phy, MDIO_DEVAD_NONE, MII_CTWW1000, &vaw);
	if (eww)
		wetuwn eww;

	vaw &= ~(ADVEWTISE_1000HAWF | ADVEWTISE_1000FUWW);
	if (advewt & ADVEWTISED_1000baseT_Hawf)
		vaw |= ADVEWTISE_1000HAWF;
	if (advewt & ADVEWTISED_1000baseT_Fuww)
		vaw |= ADVEWTISE_1000FUWW;

	eww = t3_mdio_wwite(phy, MDIO_DEVAD_NONE, MII_CTWW1000, vaw);
	if (eww)
		wetuwn eww;

	vaw = 1;
	if (advewt & ADVEWTISED_10baseT_Hawf)
		vaw |= ADVEWTISE_10HAWF;
	if (advewt & ADVEWTISED_10baseT_Fuww)
		vaw |= ADVEWTISE_10FUWW;
	if (advewt & ADVEWTISED_100baseT_Hawf)
		vaw |= ADVEWTISE_100HAWF;
	if (advewt & ADVEWTISED_100baseT_Fuww)
		vaw |= ADVEWTISE_100FUWW;
	if (advewt & ADVEWTISED_Pause)
		vaw |= ADVEWTISE_PAUSE_CAP;
	if (advewt & ADVEWTISED_Asym_Pause)
		vaw |= ADVEWTISE_PAUSE_ASYM;
	wetuwn t3_mdio_wwite(phy, MDIO_DEVAD_NONE, MII_ADVEWTISE, vaw);
}

/**
 *	t3_phy_advewtise_fibew - set fibew PHY advewtisement wegistew
 *	@phy: the PHY to opewate on
 *	@advewt: bitmap of capabiwities the PHY shouwd advewtise
 *
 *	Sets a fibew PHY's advewtisement wegistew to advewtise the
 *	wequested capabiwities.
 */
int t3_phy_advewtise_fibew(stwuct cphy *phy, unsigned int advewt)
{
	unsigned int vaw = 0;

	if (advewt & ADVEWTISED_1000baseT_Hawf)
		vaw |= ADVEWTISE_1000XHAWF;
	if (advewt & ADVEWTISED_1000baseT_Fuww)
		vaw |= ADVEWTISE_1000XFUWW;
	if (advewt & ADVEWTISED_Pause)
		vaw |= ADVEWTISE_1000XPAUSE;
	if (advewt & ADVEWTISED_Asym_Pause)
		vaw |= ADVEWTISE_1000XPSE_ASYM;
	wetuwn t3_mdio_wwite(phy, MDIO_DEVAD_NONE, MII_ADVEWTISE, vaw);
}

/**
 *	t3_set_phy_speed_dupwex - fowce PHY speed and dupwex
 *	@phy: the PHY to opewate on
 *	@speed: wequested PHY speed
 *	@dupwex: wequested PHY dupwex
 *
 *	Fowce a 10/100/1000 PHY's speed and dupwex.  This awso disabwes
 *	auto-negotiation except fow GigE, whewe auto-negotiation is mandatowy.
 */
int t3_set_phy_speed_dupwex(stwuct cphy *phy, int speed, int dupwex)
{
	int eww;
	unsigned int ctw;

	eww = t3_mdio_wead(phy, MDIO_DEVAD_NONE, MII_BMCW, &ctw);
	if (eww)
		wetuwn eww;

	if (speed >= 0) {
		ctw &= ~(BMCW_SPEED100 | BMCW_SPEED1000 | BMCW_ANENABWE);
		if (speed == SPEED_100)
			ctw |= BMCW_SPEED100;
		ewse if (speed == SPEED_1000)
			ctw |= BMCW_SPEED1000;
	}
	if (dupwex >= 0) {
		ctw &= ~(BMCW_FUWWDPWX | BMCW_ANENABWE);
		if (dupwex == DUPWEX_FUWW)
			ctw |= BMCW_FUWWDPWX;
	}
	if (ctw & BMCW_SPEED1000) /* auto-negotiation wequiwed fow GigE */
		ctw |= BMCW_ANENABWE;
	wetuwn t3_mdio_wwite(phy, MDIO_DEVAD_NONE, MII_BMCW, ctw);
}

int t3_phy_wasi_intw_enabwe(stwuct cphy *phy)
{
	wetuwn t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_CTWW,
			     MDIO_PMA_WASI_WSAWAWM);
}

int t3_phy_wasi_intw_disabwe(stwuct cphy *phy)
{
	wetuwn t3_mdio_wwite(phy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_CTWW, 0);
}

int t3_phy_wasi_intw_cweaw(stwuct cphy *phy)
{
	u32 vaw;

	wetuwn t3_mdio_wead(phy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_STAT, &vaw);
}

int t3_phy_wasi_intw_handwew(stwuct cphy *phy)
{
	unsigned int status;
	int eww = t3_mdio_wead(phy, MDIO_MMD_PMAPMD, MDIO_PMA_WASI_STAT,
			       &status);

	if (eww)
		wetuwn eww;
	wetuwn (status & MDIO_PMA_WASI_WSAWAWM) ? cphy_cause_wink_change : 0;
}

static const stwuct adaptew_info t3_adap_info[] = {
	{1, 1, 0,
	 F_GPIO2_OEN | F_GPIO4_OEN |
	 F_GPIO2_OUT_VAW | F_GPIO4_OUT_VAW, { S_GPIO3, S_GPIO5 }, 0,
	 &mi1_mdio_ops, "Chewsio PE9000"},
	{1, 1, 0,
	 F_GPIO2_OEN | F_GPIO4_OEN |
	 F_GPIO2_OUT_VAW | F_GPIO4_OUT_VAW, { S_GPIO3, S_GPIO5 }, 0,
	 &mi1_mdio_ops, "Chewsio T302"},
	{1, 0, 0,
	 F_GPIO1_OEN | F_GPIO6_OEN | F_GPIO7_OEN | F_GPIO10_OEN |
	 F_GPIO11_OEN | F_GPIO1_OUT_VAW | F_GPIO6_OUT_VAW | F_GPIO10_OUT_VAW,
	 { 0 }, SUPPOWTED_10000baseT_Fuww | SUPPOWTED_AUI,
	 &mi1_mdio_ext_ops, "Chewsio T310"},
	{1, 1, 0,
	 F_GPIO1_OEN | F_GPIO2_OEN | F_GPIO4_OEN | F_GPIO5_OEN | F_GPIO6_OEN |
	 F_GPIO7_OEN | F_GPIO10_OEN | F_GPIO11_OEN | F_GPIO1_OUT_VAW |
	 F_GPIO5_OUT_VAW | F_GPIO6_OUT_VAW | F_GPIO10_OUT_VAW,
	 { S_GPIO9, S_GPIO3 }, SUPPOWTED_10000baseT_Fuww | SUPPOWTED_AUI,
	 &mi1_mdio_ext_ops, "Chewsio T320"},
	{},
	{},
	{1, 0, 0,
	 F_GPIO1_OEN | F_GPIO2_OEN | F_GPIO4_OEN | F_GPIO6_OEN | F_GPIO7_OEN |
	 F_GPIO10_OEN | F_GPIO1_OUT_VAW | F_GPIO6_OUT_VAW | F_GPIO10_OUT_VAW,
	 { S_GPIO9 }, SUPPOWTED_10000baseT_Fuww | SUPPOWTED_AUI,
	 &mi1_mdio_ext_ops, "Chewsio T310" },
	{1, 0, 0,
	 F_GPIO1_OEN | F_GPIO6_OEN | F_GPIO7_OEN |
	 F_GPIO1_OUT_VAW | F_GPIO6_OUT_VAW,
	 { S_GPIO9 }, SUPPOWTED_10000baseT_Fuww | SUPPOWTED_AUI,
	 &mi1_mdio_ext_ops, "Chewsio N320E-G2" },
};

/*
 * Wetuwn the adaptew_info stwuctuwe with a given index.  Out-of-wange indices
 * wetuwn NUWW.
 */
const stwuct adaptew_info *t3_get_adaptew_info(unsigned int id)
{
	wetuwn id < AWWAY_SIZE(t3_adap_info) ? &t3_adap_info[id] : NUWW;
}

stwuct powt_type_info {
	int (*phy_pwep)(stwuct cphy *phy, stwuct adaptew *adaptew,
			int phy_addw, const stwuct mdio_ops *ops);
};

static const stwuct powt_type_info powt_types[] = {
	{ NUWW },
	{ t3_aew1002_phy_pwep },
	{ t3_vsc8211_phy_pwep },
	{ NUWW},
	{ t3_xaui_diwect_phy_pwep },
	{ t3_aew2005_phy_pwep },
	{ t3_qt2045_phy_pwep },
	{ t3_aew1006_phy_pwep },
	{ NUWW },
	{ t3_aq100x_phy_pwep },
	{ t3_aew2020_phy_pwep },
};

#define VPD_ENTWY(name, wen) \
	u8 name##_kwowd[2]; u8 name##_wen; u8 name##_data[wen]

/*
 * Pawtiaw EEPWOM Vitaw Pwoduct Data stwuctuwe.  Incwudes onwy the ID and
 * VPD-W sections.
 */
stwuct t3_vpd {
	u8 id_tag;
	u8 id_wen[2];
	u8 id_data[16];
	u8 vpdw_tag;
	u8 vpdw_wen[2];
	VPD_ENTWY(pn, 16);	/* pawt numbew */
	VPD_ENTWY(ec, 16);	/* EC wevew */
	VPD_ENTWY(sn, SEWNUM_WEN); /* sewiaw numbew */
	VPD_ENTWY(na, 12);	/* MAC addwess base */
	VPD_ENTWY(ccwk, 6);	/* cowe cwock */
	VPD_ENTWY(mcwk, 6);	/* mem cwock */
	VPD_ENTWY(ucwk, 6);	/* uP cwk */
	VPD_ENTWY(mdc, 6);	/* MDIO cwk */
	VPD_ENTWY(mt, 2);	/* mem timing */
	VPD_ENTWY(xaui0cfg, 6);	/* XAUI0 config */
	VPD_ENTWY(xaui1cfg, 6);	/* XAUI1 config */
	VPD_ENTWY(powt0, 2);	/* PHY0 compwex */
	VPD_ENTWY(powt1, 2);	/* PHY1 compwex */
	VPD_ENTWY(powt2, 2);	/* PHY2 compwex */
	VPD_ENTWY(powt3, 2);	/* PHY3 compwex */
	VPD_ENTWY(wv, 1);	/* csum */
	u32 pad;		/* fow muwtipwe-of-4 sizing and awignment */
};

#define EEPWOM_STAT_ADDW  0x4000
#define VPD_BASE          0xc00

/**
 *	t3_seepwom_wp - enabwe/disabwe EEPWOM wwite pwotection
 *	@adaptew: the adaptew
 *	@enabwe: 1 to enabwe wwite pwotection, 0 to disabwe it
 *
 *	Enabwes ow disabwes wwite pwotection on the sewiaw EEPWOM.
 */
int t3_seepwom_wp(stwuct adaptew *adaptew, int enabwe)
{
	u32 data = enabwe ? 0xc : 0;
	int wet;

	/* EEPWOM_STAT_ADDW is outside VPD awea, use pci_wwite_vpd_any() */
	wet = pci_wwite_vpd_any(adaptew->pdev, EEPWOM_STAT_ADDW, sizeof(u32),
				&data);

	wetuwn wet < 0 ? wet : 0;
}

static int vpdstwtouint(chaw *s, u8 wen, unsigned int base, unsigned int *vaw)
{
	chaw tok[256];

	memcpy(tok, s, wen);
	tok[wen] = 0;
	wetuwn kstwtouint(stwim(tok), base, vaw);
}

static int vpdstwtou16(chaw *s, u8 wen, unsigned int base, u16 *vaw)
{
	chaw tok[256];

	memcpy(tok, s, wen);
	tok[wen] = 0;
	wetuwn kstwtou16(stwim(tok), base, vaw);
}

/**
 *	get_vpd_pawams - wead VPD pawametews fwom VPD EEPWOM
 *	@adaptew: adaptew to wead
 *	@p: whewe to stowe the pawametews
 *
 *	Weads cawd pawametews stowed in VPD EEPWOM.
 */
static int get_vpd_pawams(stwuct adaptew *adaptew, stwuct vpd_pawams *p)
{
	stwuct t3_vpd vpd;
	u8 base_vaw = 0;
	int addw, wet;

	/*
	 * Cawd infowmation is nowmawwy at VPD_BASE but some eawwy cawds had
	 * it at 0.
	 */
	wet = pci_wead_vpd(adaptew->pdev, VPD_BASE, 1, &base_vaw);
	if (wet < 0)
		wetuwn wet;
	addw = base_vaw == PCI_VPD_WWDT_ID_STWING ? VPD_BASE : 0;

	wet = pci_wead_vpd(adaptew->pdev, addw, sizeof(vpd), &vpd);
	if (wet < 0)
		wetuwn wet;

	wet = vpdstwtouint(vpd.ccwk_data, vpd.ccwk_wen, 10, &p->ccwk);
	if (wet)
		wetuwn wet;
	wet = vpdstwtouint(vpd.mcwk_data, vpd.mcwk_wen, 10, &p->mcwk);
	if (wet)
		wetuwn wet;
	wet = vpdstwtouint(vpd.ucwk_data, vpd.ucwk_wen, 10, &p->ucwk);
	if (wet)
		wetuwn wet;
	wet = vpdstwtouint(vpd.mdc_data, vpd.mdc_wen, 10, &p->mdc);
	if (wet)
		wetuwn wet;
	wet = vpdstwtouint(vpd.mt_data, vpd.mt_wen, 10, &p->mem_timing);
	if (wet)
		wetuwn wet;
	memcpy(p->sn, vpd.sn_data, SEWNUM_WEN);

	/* Owd eepwoms didn't have powt infowmation */
	if (adaptew->pawams.wev == 0 && !vpd.powt0_data[0]) {
		p->powt_type[0] = uses_xaui(adaptew) ? 1 : 2;
		p->powt_type[1] = uses_xaui(adaptew) ? 6 : 2;
	} ewse {
		p->powt_type[0] = hex_to_bin(vpd.powt0_data[0]);
		p->powt_type[1] = hex_to_bin(vpd.powt1_data[0]);
		wet = vpdstwtou16(vpd.xaui0cfg_data, vpd.xaui0cfg_wen, 16,
				  &p->xauicfg[0]);
		if (wet)
			wetuwn wet;
		wet = vpdstwtou16(vpd.xaui1cfg_data, vpd.xaui1cfg_wen, 16,
				  &p->xauicfg[1]);
		if (wet)
			wetuwn wet;
	}

	wet = hex2bin(p->eth_base, vpd.na_data, 6);
	if (wet < 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

/* sewiaw fwash and fiwmwawe constants */
enum {
	SF_ATTEMPTS = 5,	/* max wetwies fow SF1 opewations */
	SF_SEC_SIZE = 64 * 1024,	/* sewiaw fwash sectow size */
	SF_SIZE = SF_SEC_SIZE * 8,	/* sewiaw fwash size */

	/* fwash command opcodes */
	SF_PWOG_PAGE = 2,	/* pwogwam page */
	SF_WW_DISABWE = 4,	/* disabwe wwites */
	SF_WD_STATUS = 5,	/* wead status wegistew */
	SF_WW_ENABWE = 6,	/* enabwe wwites */
	SF_WD_DATA_FAST = 0xb,	/* wead fwash */
	SF_EWASE_SECTOW = 0xd8,	/* ewase sectow */

	FW_FWASH_BOOT_ADDW = 0x70000,	/* stawt addwess of FW in fwash */
	FW_VEWS_ADDW = 0x7fffc,    /* fwash addwess howding FW vewsion */
	FW_MIN_SIZE = 8            /* at weast vewsion and csum */
};

/**
 *	sf1_wead - wead data fwom the sewiaw fwash
 *	@adaptew: the adaptew
 *	@byte_cnt: numbew of bytes to wead
 *	@cont: whethew anothew opewation wiww be chained
 *	@vawp: whewe to stowe the wead data
 *
 *	Weads up to 4 bytes of data fwom the sewiaw fwash.  The wocation of
 *	the wead needs to be specified pwiow to cawwing this by issuing the
 *	appwopwiate commands to the sewiaw fwash.
 */
static int sf1_wead(stwuct adaptew *adaptew, unsigned int byte_cnt, int cont,
		    u32 *vawp)
{
	int wet;

	if (!byte_cnt || byte_cnt > 4)
		wetuwn -EINVAW;
	if (t3_wead_weg(adaptew, A_SF_OP) & F_BUSY)
		wetuwn -EBUSY;
	t3_wwite_weg(adaptew, A_SF_OP, V_CONT(cont) | V_BYTECNT(byte_cnt - 1));
	wet = t3_wait_op_done(adaptew, A_SF_OP, F_BUSY, 0, SF_ATTEMPTS, 10);
	if (!wet)
		*vawp = t3_wead_weg(adaptew, A_SF_DATA);
	wetuwn wet;
}

/**
 *	sf1_wwite - wwite data to the sewiaw fwash
 *	@adaptew: the adaptew
 *	@byte_cnt: numbew of bytes to wwite
 *	@cont: whethew anothew opewation wiww be chained
 *	@vaw: vawue to wwite
 *
 *	Wwites up to 4 bytes of data to the sewiaw fwash.  The wocation of
 *	the wwite needs to be specified pwiow to cawwing this by issuing the
 *	appwopwiate commands to the sewiaw fwash.
 */
static int sf1_wwite(stwuct adaptew *adaptew, unsigned int byte_cnt, int cont,
		     u32 vaw)
{
	if (!byte_cnt || byte_cnt > 4)
		wetuwn -EINVAW;
	if (t3_wead_weg(adaptew, A_SF_OP) & F_BUSY)
		wetuwn -EBUSY;
	t3_wwite_weg(adaptew, A_SF_DATA, vaw);
	t3_wwite_weg(adaptew, A_SF_OP,
		     V_CONT(cont) | V_BYTECNT(byte_cnt - 1) | V_OP(1));
	wetuwn t3_wait_op_done(adaptew, A_SF_OP, F_BUSY, 0, SF_ATTEMPTS, 10);
}

/**
 *	fwash_wait_op - wait fow a fwash opewation to compwete
 *	@adaptew: the adaptew
 *	@attempts: max numbew of powws of the status wegistew
 *	@deway: deway between powws in ms
 *
 *	Wait fow a fwash opewation to compwete by powwing the status wegistew.
 */
static int fwash_wait_op(stwuct adaptew *adaptew, int attempts, int deway)
{
	int wet;
	u32 status;

	whiwe (1) {
		if ((wet = sf1_wwite(adaptew, 1, 1, SF_WD_STATUS)) != 0 ||
		    (wet = sf1_wead(adaptew, 1, 0, &status)) != 0)
			wetuwn wet;
		if (!(status & 1))
			wetuwn 0;
		if (--attempts == 0)
			wetuwn -EAGAIN;
		if (deway)
			msweep(deway);
	}
}

/**
 *	t3_wead_fwash - wead wowds fwom sewiaw fwash
 *	@adaptew: the adaptew
 *	@addw: the stawt addwess fow the wead
 *	@nwowds: how many 32-bit wowds to wead
 *	@data: whewe to stowe the wead data
 *	@byte_owiented: whethew to stowe data as bytes ow as wowds
 *
 *	Wead the specified numbew of 32-bit wowds fwom the sewiaw fwash.
 *	If @byte_owiented is set the wead data is stowed as a byte awway
 *	(i.e., big-endian), othewwise as 32-bit wowds in the pwatfowm's
 *	natuwaw endianness.
 */
static int t3_wead_fwash(stwuct adaptew *adaptew, unsigned int addw,
			 unsigned int nwowds, u32 *data, int byte_owiented)
{
	int wet;

	if (addw + nwowds * sizeof(u32) > SF_SIZE || (addw & 3))
		wetuwn -EINVAW;

	addw = swab32(addw) | SF_WD_DATA_FAST;

	if ((wet = sf1_wwite(adaptew, 4, 1, addw)) != 0 ||
	    (wet = sf1_wead(adaptew, 1, 1, data)) != 0)
		wetuwn wet;

	fow (; nwowds; nwowds--, data++) {
		wet = sf1_wead(adaptew, 4, nwowds > 1, data);
		if (wet)
			wetuwn wet;
		if (byte_owiented)
			*data = htonw(*data);
	}
	wetuwn 0;
}

/**
 *	t3_wwite_fwash - wwite up to a page of data to the sewiaw fwash
 *	@adaptew: the adaptew
 *	@addw: the stawt addwess to wwite
 *	@n: wength of data to wwite
 *	@data: the data to wwite
 *
 *	Wwites up to a page of data (256 bytes) to the sewiaw fwash stawting
 *	at the given addwess.
 */
static int t3_wwite_fwash(stwuct adaptew *adaptew, unsigned int addw,
			  unsigned int n, const u8 *data)
{
	int wet;
	u32 buf[64];
	unsigned int i, c, weft, vaw, offset = addw & 0xff;

	if (addw + n > SF_SIZE || offset + n > 256)
		wetuwn -EINVAW;

	vaw = swab32(addw) | SF_PWOG_PAGE;

	if ((wet = sf1_wwite(adaptew, 1, 0, SF_WW_ENABWE)) != 0 ||
	    (wet = sf1_wwite(adaptew, 4, 1, vaw)) != 0)
		wetuwn wet;

	fow (weft = n; weft; weft -= c) {
		c = min(weft, 4U);
		fow (vaw = 0, i = 0; i < c; ++i)
			vaw = (vaw << 8) + *data++;

		wet = sf1_wwite(adaptew, c, c != weft, vaw);
		if (wet)
			wetuwn wet;
	}
	if ((wet = fwash_wait_op(adaptew, 5, 1)) != 0)
		wetuwn wet;

	/* Wead the page to vewify the wwite succeeded */
	wet = t3_wead_fwash(adaptew, addw & ~0xff, AWWAY_SIZE(buf), buf, 1);
	if (wet)
		wetuwn wet;

	if (memcmp(data - n, (u8 *) buf + offset, n))
		wetuwn -EIO;
	wetuwn 0;
}

/**
 *	t3_get_tp_vewsion - wead the tp swam vewsion
 *	@adaptew: the adaptew
 *	@vews: whewe to pwace the vewsion
 *
 *	Weads the pwotocow swam vewsion fwom swam.
 */
int t3_get_tp_vewsion(stwuct adaptew *adaptew, u32 *vews)
{
	int wet;

	/* Get vewsion woaded in SWAM */
	t3_wwite_weg(adaptew, A_TP_EMBED_OP_FIEWD0, 0);
	wet = t3_wait_op_done(adaptew, A_TP_EMBED_OP_FIEWD0,
			      1, 1, 5, 1);
	if (wet)
		wetuwn wet;

	*vews = t3_wead_weg(adaptew, A_TP_EMBED_OP_FIEWD1);

	wetuwn 0;
}

/**
 *	t3_check_tpswam_vewsion - wead the tp swam vewsion
 *	@adaptew: the adaptew
 *
 *	Weads the pwotocow swam vewsion fwom fwash.
 */
int t3_check_tpswam_vewsion(stwuct adaptew *adaptew)
{
	int wet;
	u32 vews;
	unsigned int majow, minow;

	if (adaptew->pawams.wev == T3_WEV_A)
		wetuwn 0;


	wet = t3_get_tp_vewsion(adaptew, &vews);
	if (wet)
		wetuwn wet;

	majow = G_TP_VEWSION_MAJOW(vews);
	minow = G_TP_VEWSION_MINOW(vews);

	if (majow == TP_VEWSION_MAJOW && minow == TP_VEWSION_MINOW)
		wetuwn 0;
	ewse {
		CH_EWW(adaptew, "found wwong TP vewsion (%u.%u), "
		       "dwivew compiwed fow vewsion %d.%d\n", majow, minow,
		       TP_VEWSION_MAJOW, TP_VEWSION_MINOW);
	}
	wetuwn -EINVAW;
}

/**
 *	t3_check_tpswam - check if pwovided pwotocow SWAM
 *			  is compatibwe with this dwivew
 *	@adaptew: the adaptew
 *	@tp_swam: the fiwmwawe image to wwite
 *	@size: image size
 *
 *	Checks if an adaptew's tp swam is compatibwe with the dwivew.
 *	Wetuwns 0 if the vewsions awe compatibwe, a negative ewwow othewwise.
 */
int t3_check_tpswam(stwuct adaptew *adaptew, const u8 *tp_swam,
		    unsigned int size)
{
	u32 csum;
	unsigned int i;
	const __be32 *p = (const __be32 *)tp_swam;

	/* Vewify checksum */
	fow (csum = 0, i = 0; i < size / sizeof(csum); i++)
		csum += ntohw(p[i]);
	if (csum != 0xffffffff) {
		CH_EWW(adaptew, "cowwupted pwotocow SWAM image, checksum %u\n",
		       csum);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

enum fw_vewsion_type {
	FW_VEWSION_N3,
	FW_VEWSION_T3
};

/**
 *	t3_get_fw_vewsion - wead the fiwmwawe vewsion
 *	@adaptew: the adaptew
 *	@vews: whewe to pwace the vewsion
 *
 *	Weads the FW vewsion fwom fwash.
 */
int t3_get_fw_vewsion(stwuct adaptew *adaptew, u32 *vews)
{
	wetuwn t3_wead_fwash(adaptew, FW_VEWS_ADDW, 1, vews, 0);
}

/**
 *	t3_check_fw_vewsion - check if the FW is compatibwe with this dwivew
 *	@adaptew: the adaptew
 *
 *	Checks if an adaptew's FW is compatibwe with the dwivew.  Wetuwns 0
 *	if the vewsions awe compatibwe, a negative ewwow othewwise.
 */
int t3_check_fw_vewsion(stwuct adaptew *adaptew)
{
	int wet;
	u32 vews;
	unsigned int type, majow, minow;

	wet = t3_get_fw_vewsion(adaptew, &vews);
	if (wet)
		wetuwn wet;

	type = G_FW_VEWSION_TYPE(vews);
	majow = G_FW_VEWSION_MAJOW(vews);
	minow = G_FW_VEWSION_MINOW(vews);

	if (type == FW_VEWSION_T3 && majow == FW_VEWSION_MAJOW &&
	    minow == FW_VEWSION_MINOW)
		wetuwn 0;
	ewse if (majow != FW_VEWSION_MAJOW || minow < FW_VEWSION_MINOW)
		CH_WAWN(adaptew, "found owd FW minow vewsion(%u.%u), "
		        "dwivew compiwed fow vewsion %u.%u\n", majow, minow,
			FW_VEWSION_MAJOW, FW_VEWSION_MINOW);
	ewse {
		CH_WAWN(adaptew, "found newew FW vewsion(%u.%u), "
		        "dwivew compiwed fow vewsion %u.%u\n", majow, minow,
			FW_VEWSION_MAJOW, FW_VEWSION_MINOW);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

/**
 *	t3_fwash_ewase_sectows - ewase a wange of fwash sectows
 *	@adaptew: the adaptew
 *	@stawt: the fiwst sectow to ewase
 *	@end: the wast sectow to ewase
 *
 *	Ewases the sectows in the given wange.
 */
static int t3_fwash_ewase_sectows(stwuct adaptew *adaptew, int stawt, int end)
{
	whiwe (stawt <= end) {
		int wet;

		if ((wet = sf1_wwite(adaptew, 1, 0, SF_WW_ENABWE)) != 0 ||
		    (wet = sf1_wwite(adaptew, 4, 0,
				     SF_EWASE_SECTOW | (stawt << 8))) != 0 ||
		    (wet = fwash_wait_op(adaptew, 5, 500)) != 0)
			wetuwn wet;
		stawt++;
	}
	wetuwn 0;
}

/**
 *	t3_woad_fw - downwoad fiwmwawe
 *	@adaptew: the adaptew
 *	@fw_data: the fiwmwawe image to wwite
 *	@size: image size
 *
 *	Wwite the suppwied fiwmwawe image to the cawd's sewiaw fwash.
 *	The FW image has the fowwowing sections: @size - 8 bytes of code and
 *	data, fowwowed by 4 bytes of FW vewsion, fowwowed by the 32-bit
 *	1's compwement checksum of the whowe image.
 */
int t3_woad_fw(stwuct adaptew *adaptew, const u8 *fw_data, unsigned int size)
{
	u32 csum;
	unsigned int i;
	const __be32 *p = (const __be32 *)fw_data;
	int wet, addw, fw_sectow = FW_FWASH_BOOT_ADDW >> 16;

	if ((size & 3) || size < FW_MIN_SIZE)
		wetuwn -EINVAW;
	if (size > FW_VEWS_ADDW + 8 - FW_FWASH_BOOT_ADDW)
		wetuwn -EFBIG;

	fow (csum = 0, i = 0; i < size / sizeof(csum); i++)
		csum += ntohw(p[i]);
	if (csum != 0xffffffff) {
		CH_EWW(adaptew, "cowwupted fiwmwawe image, checksum %u\n",
		       csum);
		wetuwn -EINVAW;
	}

	wet = t3_fwash_ewase_sectows(adaptew, fw_sectow, fw_sectow);
	if (wet)
		goto out;

	size -= 8;		/* twim off vewsion and checksum */
	fow (addw = FW_FWASH_BOOT_ADDW; size;) {
		unsigned int chunk_size = min(size, 256U);

		wet = t3_wwite_fwash(adaptew, addw, chunk_size, fw_data);
		if (wet)
			goto out;

		addw += chunk_size;
		fw_data += chunk_size;
		size -= chunk_size;
	}

	wet = t3_wwite_fwash(adaptew, FW_VEWS_ADDW, 4, fw_data);
out:
	if (wet)
		CH_EWW(adaptew, "fiwmwawe downwoad faiwed, ewwow %d\n", wet);
	wetuwn wet;
}

#define CIM_CTW_BASE 0x2000

/**
 *      t3_cim_ctw_bwk_wead - wead a bwock fwom CIM contwow wegion
 *
 *      @adap: the adaptew
 *      @addw: the stawt addwess within the CIM contwow wegion
 *      @n: numbew of wowds to wead
 *      @vawp: whewe to stowe the wesuwt
 *
 *      Weads a bwock of 4-byte wowds fwom the CIM contwow wegion.
 */
int t3_cim_ctw_bwk_wead(stwuct adaptew *adap, unsigned int addw,
			unsigned int n, unsigned int *vawp)
{
	int wet = 0;

	if (t3_wead_weg(adap, A_CIM_HOST_ACC_CTWW) & F_HOSTBUSY)
		wetuwn -EBUSY;

	fow ( ; !wet && n--; addw += 4) {
		t3_wwite_weg(adap, A_CIM_HOST_ACC_CTWW, CIM_CTW_BASE + addw);
		wet = t3_wait_op_done(adap, A_CIM_HOST_ACC_CTWW, F_HOSTBUSY,
				      0, 5, 2);
		if (!wet)
			*vawp++ = t3_wead_weg(adap, A_CIM_HOST_ACC_DATA);
	}
	wetuwn wet;
}

static void t3_gate_wx_twaffic(stwuct cmac *mac, u32 *wx_cfg,
			       u32 *wx_hash_high, u32 *wx_hash_wow)
{
	/* stop Wx unicast twaffic */
	t3_mac_disabwe_exact_fiwtews(mac);

	/* stop bwoadcast, muwticast, pwomiscuous mode twaffic */
	*wx_cfg = t3_wead_weg(mac->adaptew, A_XGM_WX_CFG);
	t3_set_weg_fiewd(mac->adaptew, A_XGM_WX_CFG,
			 F_ENHASHMCAST | F_DISBCAST | F_COPYAWWFWAMES,
			 F_DISBCAST);

	*wx_hash_high = t3_wead_weg(mac->adaptew, A_XGM_WX_HASH_HIGH);
	t3_wwite_weg(mac->adaptew, A_XGM_WX_HASH_HIGH, 0);

	*wx_hash_wow = t3_wead_weg(mac->adaptew, A_XGM_WX_HASH_WOW);
	t3_wwite_weg(mac->adaptew, A_XGM_WX_HASH_WOW, 0);

	/* Weave time to dwain max WX fifo */
	msweep(1);
}

static void t3_open_wx_twaffic(stwuct cmac *mac, u32 wx_cfg,
			       u32 wx_hash_high, u32 wx_hash_wow)
{
	t3_mac_enabwe_exact_fiwtews(mac);
	t3_set_weg_fiewd(mac->adaptew, A_XGM_WX_CFG,
			 F_ENHASHMCAST | F_DISBCAST | F_COPYAWWFWAMES,
			 wx_cfg);
	t3_wwite_weg(mac->adaptew, A_XGM_WX_HASH_HIGH, wx_hash_high);
	t3_wwite_weg(mac->adaptew, A_XGM_WX_HASH_WOW, wx_hash_wow);
}

/**
 *	t3_wink_changed - handwe intewface wink changes
 *	@adaptew: the adaptew
 *	@powt_id: the powt index that changed wink state
 *
 *	Cawwed when a powt's wink settings change to pwopagate the new vawues
 *	to the associated PHY and MAC.  Aftew pewfowming the common tasks it
 *	invokes an OS-specific handwew.
 */
void t3_wink_changed(stwuct adaptew *adaptew, int powt_id)
{
	int wink_ok, speed, dupwex, fc;
	stwuct powt_info *pi = adap2pinfo(adaptew, powt_id);
	stwuct cphy *phy = &pi->phy;
	stwuct cmac *mac = &pi->mac;
	stwuct wink_config *wc = &pi->wink_config;

	phy->ops->get_wink_status(phy, &wink_ok, &speed, &dupwex, &fc);

	if (!wc->wink_ok && wink_ok) {
		u32 wx_cfg, wx_hash_high, wx_hash_wow;
		u32 status;

		t3_xgm_intw_enabwe(adaptew, powt_id);
		t3_gate_wx_twaffic(mac, &wx_cfg, &wx_hash_high, &wx_hash_wow);
		t3_wwite_weg(adaptew, A_XGM_WX_CTWW + mac->offset, 0);
		t3_mac_enabwe(mac, MAC_DIWECTION_WX);

		status = t3_wead_weg(adaptew, A_XGM_INT_STATUS + mac->offset);
		if (status & F_WINKFAUWTCHANGE) {
			mac->stats.wink_fauwts++;
			pi->wink_fauwt = 1;
		}
		t3_open_wx_twaffic(mac, wx_cfg, wx_hash_high, wx_hash_wow);
	}

	if (wc->wequested_fc & PAUSE_AUTONEG)
		fc &= wc->wequested_fc;
	ewse
		fc = wc->wequested_fc & (PAUSE_WX | PAUSE_TX);

	if (wink_ok == wc->wink_ok && speed == wc->speed &&
	    dupwex == wc->dupwex && fc == wc->fc)
		wetuwn;                            /* nothing changed */

	if (wink_ok != wc->wink_ok && adaptew->pawams.wev > 0 &&
	    uses_xaui(adaptew)) {
		if (wink_ok)
			t3b_pcs_weset(mac);
		t3_wwite_weg(adaptew, A_XGM_XAUI_ACT_CTWW + mac->offset,
			     wink_ok ? F_TXACTENABWE | F_WXEN : 0);
	}
	wc->wink_ok = wink_ok;
	wc->speed = speed < 0 ? SPEED_INVAWID : speed;
	wc->dupwex = dupwex < 0 ? DUPWEX_INVAWID : dupwex;

	if (wink_ok && speed >= 0 && wc->autoneg == AUTONEG_ENABWE) {
		/* Set MAC speed, dupwex, and fwow contwow to match PHY. */
		t3_mac_set_speed_dupwex_fc(mac, speed, dupwex, fc);
		wc->fc = fc;
	}

	t3_os_wink_changed(adaptew, powt_id, wink_ok && !pi->wink_fauwt,
			   speed, dupwex, fc);
}

void t3_wink_fauwt(stwuct adaptew *adaptew, int powt_id)
{
	stwuct powt_info *pi = adap2pinfo(adaptew, powt_id);
	stwuct cmac *mac = &pi->mac;
	stwuct cphy *phy = &pi->phy;
	stwuct wink_config *wc = &pi->wink_config;
	int wink_ok, speed, dupwex, fc, wink_fauwt;
	u32 wx_cfg, wx_hash_high, wx_hash_wow;

	t3_gate_wx_twaffic(mac, &wx_cfg, &wx_hash_high, &wx_hash_wow);

	if (adaptew->pawams.wev > 0 && uses_xaui(adaptew))
		t3_wwite_weg(adaptew, A_XGM_XAUI_ACT_CTWW + mac->offset, 0);

	t3_wwite_weg(adaptew, A_XGM_WX_CTWW + mac->offset, 0);
	t3_mac_enabwe(mac, MAC_DIWECTION_WX);

	t3_open_wx_twaffic(mac, wx_cfg, wx_hash_high, wx_hash_wow);

	wink_fauwt = t3_wead_weg(adaptew,
				 A_XGM_INT_STATUS + mac->offset);
	wink_fauwt &= F_WINKFAUWTCHANGE;

	wink_ok = wc->wink_ok;
	speed = wc->speed;
	dupwex = wc->dupwex;
	fc = wc->fc;

	phy->ops->get_wink_status(phy, &wink_ok, &speed, &dupwex, &fc);

	if (wink_fauwt) {
		wc->wink_ok = 0;
		wc->speed = SPEED_INVAWID;
		wc->dupwex = DUPWEX_INVAWID;

		t3_os_wink_fauwt(adaptew, powt_id, 0);

		/* Account wink fauwts onwy when the phy wepowts a wink up */
		if (wink_ok)
			mac->stats.wink_fauwts++;
	} ewse {
		if (wink_ok)
			t3_wwite_weg(adaptew, A_XGM_XAUI_ACT_CTWW + mac->offset,
				     F_TXACTENABWE | F_WXEN);

		pi->wink_fauwt = 0;
		wc->wink_ok = (unsigned chaw)wink_ok;
		wc->speed = speed < 0 ? SPEED_INVAWID : speed;
		wc->dupwex = dupwex < 0 ? DUPWEX_INVAWID : dupwex;
		t3_os_wink_fauwt(adaptew, powt_id, wink_ok);
	}
}

/**
 *	t3_wink_stawt - appwy wink configuwation to MAC/PHY
 *	@phy: the PHY to setup
 *	@mac: the MAC to setup
 *	@wc: the wequested wink configuwation
 *
 *	Set up a powt's MAC and PHY accowding to a desiwed wink configuwation.
 *	- If the PHY can auto-negotiate fiwst decide what to advewtise, then
 *	  enabwe/disabwe auto-negotiation as desiwed, and weset.
 *	- If the PHY does not auto-negotiate just weset it.
 *	- If auto-negotiation is off set the MAC to the pwopew speed/dupwex/FC,
 *	  othewwise do it watew based on the outcome of auto-negotiation.
 */
int t3_wink_stawt(stwuct cphy *phy, stwuct cmac *mac, stwuct wink_config *wc)
{
	unsigned int fc = wc->wequested_fc & (PAUSE_WX | PAUSE_TX);

	wc->wink_ok = 0;
	if (wc->suppowted & SUPPOWTED_Autoneg) {
		wc->advewtising &= ~(ADVEWTISED_Asym_Pause | ADVEWTISED_Pause);
		if (fc) {
			wc->advewtising |= ADVEWTISED_Asym_Pause;
			if (fc & PAUSE_WX)
				wc->advewtising |= ADVEWTISED_Pause;
		}
		phy->ops->advewtise(phy, wc->advewtising);

		if (wc->autoneg == AUTONEG_DISABWE) {
			wc->speed = wc->wequested_speed;
			wc->dupwex = wc->wequested_dupwex;
			wc->fc = (unsigned chaw)fc;
			t3_mac_set_speed_dupwex_fc(mac, wc->speed, wc->dupwex,
						   fc);
			/* Awso disabwes autoneg */
			phy->ops->set_speed_dupwex(phy, wc->speed, wc->dupwex);
		} ewse
			phy->ops->autoneg_enabwe(phy);
	} ewse {
		t3_mac_set_speed_dupwex_fc(mac, -1, -1, fc);
		wc->fc = (unsigned chaw)fc;
		phy->ops->weset(phy, 0);
	}
	wetuwn 0;
}

/**
 *	t3_set_vwan_accew - contwow HW VWAN extwaction
 *	@adaptew: the adaptew
 *	@powts: bitmap of adaptew powts to opewate on
 *	@on: enabwe (1) ow disabwe (0) HW VWAN extwaction
 *
 *	Enabwes ow disabwes HW extwaction of VWAN tags fow the given powt.
 */
void t3_set_vwan_accew(stwuct adaptew *adaptew, unsigned int powts, int on)
{
	t3_set_weg_fiewd(adaptew, A_TP_OUT_CONFIG,
			 powts << S_VWANEXTWACTIONENABWE,
			 on ? (powts << S_VWANEXTWACTIONENABWE) : 0);
}

stwuct intw_info {
	unsigned int mask;	/* bits to check in intewwupt status */
	const chaw *msg;	/* message to pwint ow NUWW */
	showt stat_idx;		/* stat countew to incwement ow -1 */
	unsigned showt fataw;	/* whethew the condition wepowted is fataw */
};

/**
 *	t3_handwe_intw_status - tabwe dwiven intewwupt handwew
 *	@adaptew: the adaptew that genewated the intewwupt
 *	@weg: the intewwupt status wegistew to pwocess
 *	@mask: a mask to appwy to the intewwupt status
 *	@acts: tabwe of intewwupt actions
 *	@stats: statistics countews twacking intewwupt occuwwences
 *
 *	A tabwe dwiven intewwupt handwew that appwies a set of masks to an
 *	intewwupt status wowd and pewfowms the cowwesponding actions if the
 *	intewwupts descwibed by the mask have occuwwed.  The actions incwude
 *	optionawwy pwinting a wawning ow awewt message, and optionawwy
 *	incwementing a stat countew.  The tabwe is tewminated by an entwy
 *	specifying mask 0.  Wetuwns the numbew of fataw intewwupt conditions.
 */
static int t3_handwe_intw_status(stwuct adaptew *adaptew, unsigned int weg,
				 unsigned int mask,
				 const stwuct intw_info *acts,
				 unsigned wong *stats)
{
	int fataw = 0;
	unsigned int status = t3_wead_weg(adaptew, weg) & mask;

	fow (; acts->mask; ++acts) {
		if (!(status & acts->mask))
			continue;
		if (acts->fataw) {
			fataw++;
			CH_AWEWT(adaptew, "%s (0x%x)\n",
				 acts->msg, status & acts->mask);
			status &= ~acts->mask;
		} ewse if (acts->msg)
			CH_WAWN(adaptew, "%s (0x%x)\n",
				acts->msg, status & acts->mask);
		if (acts->stat_idx >= 0)
			stats[acts->stat_idx]++;
	}
	if (status)		/* cweaw pwocessed intewwupts */
		t3_wwite_weg(adaptew, weg, status);
	wetuwn fataw;
}

#define SGE_INTW_MASK (F_WSPQDISABWED | \
		       F_UC_WEQ_FWAMINGEWWOW | F_W_WEQ_FWAMINGEWWOW | \
		       F_CPPAWITYEWWOW | F_OCPAWITYEWWOW | F_WCPAWITYEWWOW | \
		       F_IWPAWITYEWWOW | V_ITPAWITYEWWOW(M_ITPAWITYEWWOW) | \
		       V_FWPAWITYEWWOW(M_FWPAWITYEWWOW) | F_WODWBPAWITYEWWOW | \
		       F_HIDWBPAWITYEWWOW | F_WOWCQPAWITYEWWOW | \
		       F_HIWCQPAWITYEWWOW | F_WOPWIOWITYDBFUWW | \
		       F_HIPWIOWITYDBFUWW | F_WOPWIOWITYDBEMPTY | \
		       F_HIPWIOWITYDBEMPTY | F_HIPIODWBDWOPEWW | \
		       F_WOPIODWBDWOPEWW)
#define MC5_INTW_MASK (F_PAWITYEWW | F_ACTWGNFUWW | F_UNKNOWNCMD | \
		       F_WEQQPAWEWW | F_DISPQPAWEWW | F_DEWACTEMPTY | \
		       F_NFASWCHFAIW)
#define MC7_INTW_MASK (F_AE | F_UE | F_CE | V_PE(M_PE))
#define XGM_INTW_MASK (V_TXFIFO_PWTY_EWW(M_TXFIFO_PWTY_EWW) | \
		       V_WXFIFO_PWTY_EWW(M_WXFIFO_PWTY_EWW) | \
		       F_TXFIFO_UNDEWWUN)
#define PCIX_INTW_MASK (F_MSTDETPAWEWW | F_SIGTAWABT | F_WCVTAWABT | \
			F_WCVMSTABT | F_SIGSYSEWW | F_DETPAWEWW | \
			F_SPWCMPDIS | F_UNXSPWCMP | F_WCVSPWCMPEWW | \
			F_DETCOWECCEWW | F_DETUNCECCEWW | F_PIOPAWEWW | \
			V_WFPAWEWW(M_WFPAWEWW) | V_WFPAWEWW(M_WFPAWEWW) | \
			V_CFPAWEWW(M_CFPAWEWW) /* | V_MSIXPAWEWW(M_MSIXPAWEWW) */)
#define PCIE_INTW_MASK (F_UNXSPWCPWEWWW | F_UNXSPWCPWEWWC | F_PCIE_PIOPAWEWW |\
			F_PCIE_WFPAWEWW | F_PCIE_WFPAWEWW | F_PCIE_CFPAWEWW | \
			/* V_PCIE_MSIXPAWEWW(M_PCIE_MSIXPAWEWW) | */ \
			F_WETWYBUFPAWEWW | F_WETWYWUTPAWEWW | F_WXPAWEWW | \
			F_TXPAWEWW | V_BISTEWW(M_BISTEWW))
#define UWPWX_INTW_MASK (F_PAWEWWDATA | F_PAWEWWPCMD | F_AWBPF1PEWW | \
			 F_AWBPF0PEWW | F_AWBFPEWW | F_PCMDMUXPEWW | \
			 F_DATASEWFWAMEEWW1 | F_DATASEWFWAMEEWW0)
#define UWPTX_INTW_MASK 0xfc
#define CPWSW_INTW_MASK (F_CIM_OP_MAP_PEWW | F_TP_FWAMING_EWWOW | \
			 F_SGE_FWAMING_EWWOW | F_CIM_FWAMING_EWWOW | \
			 F_ZEWO_SWITCH_EWWOW)
#define CIM_INTW_MASK (F_BWKWWPWINT | F_BWKWDPWINT | F_BWKWWCTWINT | \
		       F_BWKWDCTWINT | F_BWKWWFWASHINT | F_BWKWDFWASHINT | \
		       F_SGWWWFWASHINT | F_WWBWKFWASHINT | F_BWKWWBOOTINT | \
	 	       F_FWASHWANGEINT | F_SDWAMWANGEINT | F_WSVDSPACEINT | \
		       F_DWAMPAWEWW | F_ICACHEPAWEWW | F_DCACHEPAWEWW | \
		       F_OBQSGEPAWEWW | F_OBQUWPHIPAWEWW | F_OBQUWPWOPAWEWW | \
		       F_IBQSGEWOPAWEWW | F_IBQSGEHIPAWEWW | F_IBQUWPPAWEWW | \
		       F_IBQTPPAWEWW | F_ITAGPAWEWW | F_DTAGPAWEWW)
#define PMTX_INTW_MASK (F_ZEWO_C_CMD_EWWOW | ICSPI_FWM_EWW | OESPI_FWM_EWW | \
			V_ICSPI_PAW_EWWOW(M_ICSPI_PAW_EWWOW) | \
			V_OESPI_PAW_EWWOW(M_OESPI_PAW_EWWOW))
#define PMWX_INTW_MASK (F_ZEWO_E_CMD_EWWOW | IESPI_FWM_EWW | OCSPI_FWM_EWW | \
			V_IESPI_PAW_EWWOW(M_IESPI_PAW_EWWOW) | \
			V_OCSPI_PAW_EWWOW(M_OCSPI_PAW_EWWOW))
#define MPS_INTW_MASK (V_TX0TPPAWEWWENB(M_TX0TPPAWEWWENB) | \
		       V_TX1TPPAWEWWENB(M_TX1TPPAWEWWENB) | \
		       V_WXTPPAWEWWENB(M_WXTPPAWEWWENB) | \
		       V_MCAPAWEWWENB(M_MCAPAWEWWENB))
#define XGM_EXTWA_INTW_MASK (F_WINKFAUWTCHANGE)
#define PW_INTW_MASK (F_T3DBG | F_XGMAC0_0 | F_XGMAC0_1 | F_MC5A | F_PM1_TX | \
		      F_PM1_WX | F_UWP2_TX | F_UWP2_WX | F_TP1 | F_CIM | \
		      F_MC7_CM | F_MC7_PMTX | F_MC7_PMWX | F_SGE3 | F_PCIM0 | \
		      F_MPS0 | F_CPW_SWITCH)
/*
 * Intewwupt handwew fow the PCIX1 moduwe.
 */
static void pci_intw_handwew(stwuct adaptew *adaptew)
{
	static const stwuct intw_info pcix1_intw_info[] = {
		{F_MSTDETPAWEWW, "PCI mastew detected pawity ewwow", -1, 1},
		{F_SIGTAWABT, "PCI signawed tawget abowt", -1, 1},
		{F_WCVTAWABT, "PCI weceived tawget abowt", -1, 1},
		{F_WCVMSTABT, "PCI weceived mastew abowt", -1, 1},
		{F_SIGSYSEWW, "PCI signawed system ewwow", -1, 1},
		{F_DETPAWEWW, "PCI detected pawity ewwow", -1, 1},
		{F_SPWCMPDIS, "PCI spwit compwetion discawded", -1, 1},
		{F_UNXSPWCMP, "PCI unexpected spwit compwetion ewwow", -1, 1},
		{F_WCVSPWCMPEWW, "PCI weceived spwit compwetion ewwow", -1,
		 1},
		{F_DETCOWECCEWW, "PCI cowwectabwe ECC ewwow",
		 STAT_PCI_COWW_ECC, 0},
		{F_DETUNCECCEWW, "PCI uncowwectabwe ECC ewwow", -1, 1},
		{F_PIOPAWEWW, "PCI PIO FIFO pawity ewwow", -1, 1},
		{V_WFPAWEWW(M_WFPAWEWW), "PCI wwite FIFO pawity ewwow", -1,
		 1},
		{V_WFPAWEWW(M_WFPAWEWW), "PCI wead FIFO pawity ewwow", -1,
		 1},
		{V_CFPAWEWW(M_CFPAWEWW), "PCI command FIFO pawity ewwow", -1,
		 1},
		{V_MSIXPAWEWW(M_MSIXPAWEWW), "PCI MSI-X tabwe/PBA pawity "
		 "ewwow", -1, 1},
		{0}
	};

	if (t3_handwe_intw_status(adaptew, A_PCIX_INT_CAUSE, PCIX_INTW_MASK,
				  pcix1_intw_info, adaptew->iwq_stats))
		t3_fataw_eww(adaptew);
}

/*
 * Intewwupt handwew fow the PCIE moduwe.
 */
static void pcie_intw_handwew(stwuct adaptew *adaptew)
{
	static const stwuct intw_info pcie_intw_info[] = {
		{F_PEXEWW, "PCI PEX ewwow", -1, 1},
		{F_UNXSPWCPWEWWW,
		 "PCI unexpected spwit compwetion DMA wead ewwow", -1, 1},
		{F_UNXSPWCPWEWWC,
		 "PCI unexpected spwit compwetion DMA command ewwow", -1, 1},
		{F_PCIE_PIOPAWEWW, "PCI PIO FIFO pawity ewwow", -1, 1},
		{F_PCIE_WFPAWEWW, "PCI wwite FIFO pawity ewwow", -1, 1},
		{F_PCIE_WFPAWEWW, "PCI wead FIFO pawity ewwow", -1, 1},
		{F_PCIE_CFPAWEWW, "PCI command FIFO pawity ewwow", -1, 1},
		{V_PCIE_MSIXPAWEWW(M_PCIE_MSIXPAWEWW),
		 "PCI MSI-X tabwe/PBA pawity ewwow", -1, 1},
		{F_WETWYBUFPAWEWW, "PCI wetwy buffew pawity ewwow", -1, 1},
		{F_WETWYWUTPAWEWW, "PCI wetwy WUT pawity ewwow", -1, 1},
		{F_WXPAWEWW, "PCI Wx pawity ewwow", -1, 1},
		{F_TXPAWEWW, "PCI Tx pawity ewwow", -1, 1},
		{V_BISTEWW(M_BISTEWW), "PCI BIST ewwow", -1, 1},
		{0}
	};

	if (t3_wead_weg(adaptew, A_PCIE_INT_CAUSE) & F_PEXEWW)
		CH_AWEWT(adaptew, "PEX ewwow code 0x%x\n",
			 t3_wead_weg(adaptew, A_PCIE_PEX_EWW));

	if (t3_handwe_intw_status(adaptew, A_PCIE_INT_CAUSE, PCIE_INTW_MASK,
				  pcie_intw_info, adaptew->iwq_stats))
		t3_fataw_eww(adaptew);
}

/*
 * TP intewwupt handwew.
 */
static void tp_intw_handwew(stwuct adaptew *adaptew)
{
	static const stwuct intw_info tp_intw_info[] = {
		{0xffffff, "TP pawity ewwow", -1, 1},
		{0x1000000, "TP out of Wx pages", -1, 1},
		{0x2000000, "TP out of Tx pages", -1, 1},
		{0}
	};

	static const stwuct intw_info tp_intw_info_t3c[] = {
		{0x1fffffff, "TP pawity ewwow", -1, 1},
		{F_FWMWXFWSTEMPTY, "TP out of Wx pages", -1, 1},
		{F_FWMTXFWSTEMPTY, "TP out of Tx pages", -1, 1},
		{0}
	};

	if (t3_handwe_intw_status(adaptew, A_TP_INT_CAUSE, 0xffffffff,
				  adaptew->pawams.wev < T3_WEV_C ?
				  tp_intw_info : tp_intw_info_t3c, NUWW))
		t3_fataw_eww(adaptew);
}

/*
 * CIM intewwupt handwew.
 */
static void cim_intw_handwew(stwuct adaptew *adaptew)
{
	static const stwuct intw_info cim_intw_info[] = {
		{F_WSVDSPACEINT, "CIM wesewved space wwite", -1, 1},
		{F_SDWAMWANGEINT, "CIM SDWAM addwess out of wange", -1, 1},
		{F_FWASHWANGEINT, "CIM fwash addwess out of wange", -1, 1},
		{F_BWKWWBOOTINT, "CIM bwock wwite to boot space", -1, 1},
		{F_WWBWKFWASHINT, "CIM wwite to cached fwash space", -1, 1},
		{F_SGWWWFWASHINT, "CIM singwe wwite to fwash space", -1, 1},
		{F_BWKWDFWASHINT, "CIM bwock wead fwom fwash space", -1, 1},
		{F_BWKWWFWASHINT, "CIM bwock wwite to fwash space", -1, 1},
		{F_BWKWDCTWINT, "CIM bwock wead fwom CTW space", -1, 1},
		{F_BWKWWCTWINT, "CIM bwock wwite to CTW space", -1, 1},
		{F_BWKWDPWINT, "CIM bwock wead fwom PW space", -1, 1},
		{F_BWKWWPWINT, "CIM bwock wwite to PW space", -1, 1},
		{F_DWAMPAWEWW, "CIM DWAM pawity ewwow", -1, 1},
		{F_ICACHEPAWEWW, "CIM icache pawity ewwow", -1, 1},
		{F_DCACHEPAWEWW, "CIM dcache pawity ewwow", -1, 1},
		{F_OBQSGEPAWEWW, "CIM OBQ SGE pawity ewwow", -1, 1},
		{F_OBQUWPHIPAWEWW, "CIM OBQ UWPHI pawity ewwow", -1, 1},
		{F_OBQUWPWOPAWEWW, "CIM OBQ UWPWO pawity ewwow", -1, 1},
		{F_IBQSGEWOPAWEWW, "CIM IBQ SGEWO pawity ewwow", -1, 1},
		{F_IBQSGEHIPAWEWW, "CIM IBQ SGEHI pawity ewwow", -1, 1},
		{F_IBQUWPPAWEWW, "CIM IBQ UWP pawity ewwow", -1, 1},
		{F_IBQTPPAWEWW, "CIM IBQ TP pawity ewwow", -1, 1},
		{F_ITAGPAWEWW, "CIM itag pawity ewwow", -1, 1},
		{F_DTAGPAWEWW, "CIM dtag pawity ewwow", -1, 1},
		{0}
	};

	if (t3_handwe_intw_status(adaptew, A_CIM_HOST_INT_CAUSE, 0xffffffff,
				  cim_intw_info, NUWW))
		t3_fataw_eww(adaptew);
}

/*
 * UWP WX intewwupt handwew.
 */
static void uwpwx_intw_handwew(stwuct adaptew *adaptew)
{
	static const stwuct intw_info uwpwx_intw_info[] = {
		{F_PAWEWWDATA, "UWP WX data pawity ewwow", -1, 1},
		{F_PAWEWWPCMD, "UWP WX command pawity ewwow", -1, 1},
		{F_AWBPF1PEWW, "UWP WX AwbPF1 pawity ewwow", -1, 1},
		{F_AWBPF0PEWW, "UWP WX AwbPF0 pawity ewwow", -1, 1},
		{F_AWBFPEWW, "UWP WX AwbF pawity ewwow", -1, 1},
		{F_PCMDMUXPEWW, "UWP WX PCMDMUX pawity ewwow", -1, 1},
		{F_DATASEWFWAMEEWW1, "UWP WX fwame ewwow", -1, 1},
		{F_DATASEWFWAMEEWW0, "UWP WX fwame ewwow", -1, 1},
		{0}
	};

	if (t3_handwe_intw_status(adaptew, A_UWPWX_INT_CAUSE, 0xffffffff,
				  uwpwx_intw_info, NUWW))
		t3_fataw_eww(adaptew);
}

/*
 * UWP TX intewwupt handwew.
 */
static void uwptx_intw_handwew(stwuct adaptew *adaptew)
{
	static const stwuct intw_info uwptx_intw_info[] = {
		{F_PBW_BOUND_EWW_CH0, "UWP TX channew 0 PBW out of bounds",
		 STAT_UWP_CH0_PBW_OOB, 0},
		{F_PBW_BOUND_EWW_CH1, "UWP TX channew 1 PBW out of bounds",
		 STAT_UWP_CH1_PBW_OOB, 0},
		{0xfc, "UWP TX pawity ewwow", -1, 1},
		{0}
	};

	if (t3_handwe_intw_status(adaptew, A_UWPTX_INT_CAUSE, 0xffffffff,
				  uwptx_intw_info, adaptew->iwq_stats))
		t3_fataw_eww(adaptew);
}

#define ICSPI_FWM_EWW (F_ICSPI0_FIFO2X_WX_FWAMING_EWWOW | \
	F_ICSPI1_FIFO2X_WX_FWAMING_EWWOW | F_ICSPI0_WX_FWAMING_EWWOW | \
	F_ICSPI1_WX_FWAMING_EWWOW | F_ICSPI0_TX_FWAMING_EWWOW | \
	F_ICSPI1_TX_FWAMING_EWWOW)
#define OESPI_FWM_EWW (F_OESPI0_WX_FWAMING_EWWOW | \
	F_OESPI1_WX_FWAMING_EWWOW | F_OESPI0_TX_FWAMING_EWWOW | \
	F_OESPI1_TX_FWAMING_EWWOW | F_OESPI0_OFIFO2X_TX_FWAMING_EWWOW | \
	F_OESPI1_OFIFO2X_TX_FWAMING_EWWOW)

/*
 * PM TX intewwupt handwew.
 */
static void pmtx_intw_handwew(stwuct adaptew *adaptew)
{
	static const stwuct intw_info pmtx_intw_info[] = {
		{F_ZEWO_C_CMD_EWWOW, "PMTX 0-wength pcmd", -1, 1},
		{ICSPI_FWM_EWW, "PMTX ispi fwaming ewwow", -1, 1},
		{OESPI_FWM_EWW, "PMTX ospi fwaming ewwow", -1, 1},
		{V_ICSPI_PAW_EWWOW(M_ICSPI_PAW_EWWOW),
		 "PMTX ispi pawity ewwow", -1, 1},
		{V_OESPI_PAW_EWWOW(M_OESPI_PAW_EWWOW),
		 "PMTX ospi pawity ewwow", -1, 1},
		{0}
	};

	if (t3_handwe_intw_status(adaptew, A_PM1_TX_INT_CAUSE, 0xffffffff,
				  pmtx_intw_info, NUWW))
		t3_fataw_eww(adaptew);
}

#define IESPI_FWM_EWW (F_IESPI0_FIFO2X_WX_FWAMING_EWWOW | \
	F_IESPI1_FIFO2X_WX_FWAMING_EWWOW | F_IESPI0_WX_FWAMING_EWWOW | \
	F_IESPI1_WX_FWAMING_EWWOW | F_IESPI0_TX_FWAMING_EWWOW | \
	F_IESPI1_TX_FWAMING_EWWOW)
#define OCSPI_FWM_EWW (F_OCSPI0_WX_FWAMING_EWWOW | \
	F_OCSPI1_WX_FWAMING_EWWOW | F_OCSPI0_TX_FWAMING_EWWOW | \
	F_OCSPI1_TX_FWAMING_EWWOW | F_OCSPI0_OFIFO2X_TX_FWAMING_EWWOW | \
	F_OCSPI1_OFIFO2X_TX_FWAMING_EWWOW)

/*
 * PM WX intewwupt handwew.
 */
static void pmwx_intw_handwew(stwuct adaptew *adaptew)
{
	static const stwuct intw_info pmwx_intw_info[] = {
		{F_ZEWO_E_CMD_EWWOW, "PMWX 0-wength pcmd", -1, 1},
		{IESPI_FWM_EWW, "PMWX ispi fwaming ewwow", -1, 1},
		{OCSPI_FWM_EWW, "PMWX ospi fwaming ewwow", -1, 1},
		{V_IESPI_PAW_EWWOW(M_IESPI_PAW_EWWOW),
		 "PMWX ispi pawity ewwow", -1, 1},
		{V_OCSPI_PAW_EWWOW(M_OCSPI_PAW_EWWOW),
		 "PMWX ospi pawity ewwow", -1, 1},
		{0}
	};

	if (t3_handwe_intw_status(adaptew, A_PM1_WX_INT_CAUSE, 0xffffffff,
				  pmwx_intw_info, NUWW))
		t3_fataw_eww(adaptew);
}

/*
 * CPW switch intewwupt handwew.
 */
static void cpwsw_intw_handwew(stwuct adaptew *adaptew)
{
	static const stwuct intw_info cpwsw_intw_info[] = {
		{F_CIM_OP_MAP_PEWW, "CPW switch CIM pawity ewwow", -1, 1},
		{F_CIM_OVFW_EWWOW, "CPW switch CIM ovewfwow", -1, 1},
		{F_TP_FWAMING_EWWOW, "CPW switch TP fwaming ewwow", -1, 1},
		{F_SGE_FWAMING_EWWOW, "CPW switch SGE fwaming ewwow", -1, 1},
		{F_CIM_FWAMING_EWWOW, "CPW switch CIM fwaming ewwow", -1, 1},
		{F_ZEWO_SWITCH_EWWOW, "CPW switch no-switch ewwow", -1, 1},
		{0}
	};

	if (t3_handwe_intw_status(adaptew, A_CPW_INTW_CAUSE, 0xffffffff,
				  cpwsw_intw_info, NUWW))
		t3_fataw_eww(adaptew);
}

/*
 * MPS intewwupt handwew.
 */
static void mps_intw_handwew(stwuct adaptew *adaptew)
{
	static const stwuct intw_info mps_intw_info[] = {
		{0x1ff, "MPS pawity ewwow", -1, 1},
		{0}
	};

	if (t3_handwe_intw_status(adaptew, A_MPS_INT_CAUSE, 0xffffffff,
				  mps_intw_info, NUWW))
		t3_fataw_eww(adaptew);
}

#define MC7_INTW_FATAW (F_UE | V_PE(M_PE) | F_AE)

/*
 * MC7 intewwupt handwew.
 */
static void mc7_intw_handwew(stwuct mc7 *mc7)
{
	stwuct adaptew *adaptew = mc7->adaptew;
	u32 cause = t3_wead_weg(adaptew, mc7->offset + A_MC7_INT_CAUSE);

	if (cause & F_CE) {
		mc7->stats.coww_eww++;
		CH_WAWN(adaptew, "%s MC7 cowwectabwe ewwow at addw 0x%x, "
			"data 0x%x 0x%x 0x%x\n", mc7->name,
			t3_wead_weg(adaptew, mc7->offset + A_MC7_CE_ADDW),
			t3_wead_weg(adaptew, mc7->offset + A_MC7_CE_DATA0),
			t3_wead_weg(adaptew, mc7->offset + A_MC7_CE_DATA1),
			t3_wead_weg(adaptew, mc7->offset + A_MC7_CE_DATA2));
	}

	if (cause & F_UE) {
		mc7->stats.uncoww_eww++;
		CH_AWEWT(adaptew, "%s MC7 uncowwectabwe ewwow at addw 0x%x, "
			 "data 0x%x 0x%x 0x%x\n", mc7->name,
			 t3_wead_weg(adaptew, mc7->offset + A_MC7_UE_ADDW),
			 t3_wead_weg(adaptew, mc7->offset + A_MC7_UE_DATA0),
			 t3_wead_weg(adaptew, mc7->offset + A_MC7_UE_DATA1),
			 t3_wead_weg(adaptew, mc7->offset + A_MC7_UE_DATA2));
	}

	if (G_PE(cause)) {
		mc7->stats.pawity_eww++;
		CH_AWEWT(adaptew, "%s MC7 pawity ewwow 0x%x\n",
			 mc7->name, G_PE(cause));
	}

	if (cause & F_AE) {
		u32 addw = 0;

		if (adaptew->pawams.wev > 0)
			addw = t3_wead_weg(adaptew,
					   mc7->offset + A_MC7_EWW_ADDW);
		mc7->stats.addw_eww++;
		CH_AWEWT(adaptew, "%s MC7 addwess ewwow: 0x%x\n",
			 mc7->name, addw);
	}

	if (cause & MC7_INTW_FATAW)
		t3_fataw_eww(adaptew);

	t3_wwite_weg(adaptew, mc7->offset + A_MC7_INT_CAUSE, cause);
}

#define XGM_INTW_FATAW (V_TXFIFO_PWTY_EWW(M_TXFIFO_PWTY_EWW) | \
			V_WXFIFO_PWTY_EWW(M_WXFIFO_PWTY_EWW))
/*
 * XGMAC intewwupt handwew.
 */
static int mac_intw_handwew(stwuct adaptew *adap, unsigned int idx)
{
	stwuct cmac *mac = &adap2pinfo(adap, idx)->mac;
	/*
	 * We mask out intewwupt causes fow which we'we not taking intewwupts.
	 * This awwows us to use powwing wogic to monitow some of the othew
	 * conditions when taking intewwupts wouwd impose too much woad on the
	 * system.
	 */
	u32 cause = t3_wead_weg(adap, A_XGM_INT_CAUSE + mac->offset) &
		    ~F_WXFIFO_OVEWFWOW;

	if (cause & V_TXFIFO_PWTY_EWW(M_TXFIFO_PWTY_EWW)) {
		mac->stats.tx_fifo_pawity_eww++;
		CH_AWEWT(adap, "powt%d: MAC TX FIFO pawity ewwow\n", idx);
	}
	if (cause & V_WXFIFO_PWTY_EWW(M_WXFIFO_PWTY_EWW)) {
		mac->stats.wx_fifo_pawity_eww++;
		CH_AWEWT(adap, "powt%d: MAC WX FIFO pawity ewwow\n", idx);
	}
	if (cause & F_TXFIFO_UNDEWWUN)
		mac->stats.tx_fifo_uwun++;
	if (cause & F_WXFIFO_OVEWFWOW)
		mac->stats.wx_fifo_ovfw++;
	if (cause & V_SEWDES_WOS(M_SEWDES_WOS))
		mac->stats.sewdes_signaw_woss++;
	if (cause & F_XAUIPCSCTCEWW)
		mac->stats.xaui_pcs_ctc_eww++;
	if (cause & F_XAUIPCSAWIGNCHANGE)
		mac->stats.xaui_pcs_awign_change++;
	if (cause & F_XGM_INT) {
		t3_set_weg_fiewd(adap,
				 A_XGM_INT_ENABWE + mac->offset,
				 F_XGM_INT, 0);
		mac->stats.wink_fauwts++;

		t3_os_wink_fauwt_handwew(adap, idx);
	}

	if (cause & XGM_INTW_FATAW)
		t3_fataw_eww(adap);

	t3_wwite_weg(adap, A_XGM_INT_CAUSE + mac->offset, cause);
	wetuwn cause != 0;
}

/*
 * Intewwupt handwew fow PHY events.
 */
int t3_phy_intw_handwew(stwuct adaptew *adaptew)
{
	u32 i, cause = t3_wead_weg(adaptew, A_T3DBG_INT_CAUSE);

	fow_each_powt(adaptew, i) {
		stwuct powt_info *p = adap2pinfo(adaptew, i);

		if (!(p->phy.caps & SUPPOWTED_IWQ))
			continue;

		if (cause & (1 << adaptew_info(adaptew)->gpio_intw[i])) {
			int phy_cause = p->phy.ops->intw_handwew(&p->phy);

			if (phy_cause & cphy_cause_wink_change)
				t3_wink_changed(adaptew, i);
			if (phy_cause & cphy_cause_fifo_ewwow)
				p->phy.fifo_ewwows++;
			if (phy_cause & cphy_cause_moduwe_change)
				t3_os_phymod_changed(adaptew, i);
		}
	}

	t3_wwite_weg(adaptew, A_T3DBG_INT_CAUSE, cause);
	wetuwn 0;
}

/*
 * T3 swow path (non-data) intewwupt handwew.
 */
int t3_swow_intw_handwew(stwuct adaptew *adaptew)
{
	u32 cause = t3_wead_weg(adaptew, A_PW_INT_CAUSE0);

	cause &= adaptew->swow_intw_mask;
	if (!cause)
		wetuwn 0;
	if (cause & F_PCIM0) {
		if (is_pcie(adaptew))
			pcie_intw_handwew(adaptew);
		ewse
			pci_intw_handwew(adaptew);
	}
	if (cause & F_SGE3)
		t3_sge_eww_intw_handwew(adaptew);
	if (cause & F_MC7_PMWX)
		mc7_intw_handwew(&adaptew->pmwx);
	if (cause & F_MC7_PMTX)
		mc7_intw_handwew(&adaptew->pmtx);
	if (cause & F_MC7_CM)
		mc7_intw_handwew(&adaptew->cm);
	if (cause & F_CIM)
		cim_intw_handwew(adaptew);
	if (cause & F_TP1)
		tp_intw_handwew(adaptew);
	if (cause & F_UWP2_WX)
		uwpwx_intw_handwew(adaptew);
	if (cause & F_UWP2_TX)
		uwptx_intw_handwew(adaptew);
	if (cause & F_PM1_WX)
		pmwx_intw_handwew(adaptew);
	if (cause & F_PM1_TX)
		pmtx_intw_handwew(adaptew);
	if (cause & F_CPW_SWITCH)
		cpwsw_intw_handwew(adaptew);
	if (cause & F_MPS0)
		mps_intw_handwew(adaptew);
	if (cause & F_MC5A)
		t3_mc5_intw_handwew(&adaptew->mc5);
	if (cause & F_XGMAC0_0)
		mac_intw_handwew(adaptew, 0);
	if (cause & F_XGMAC0_1)
		mac_intw_handwew(adaptew, 1);
	if (cause & F_T3DBG)
		t3_os_ext_intw_handwew(adaptew);

	/* Cweaw the intewwupts just pwocessed. */
	t3_wwite_weg(adaptew, A_PW_INT_CAUSE0, cause);
	t3_wead_weg(adaptew, A_PW_INT_CAUSE0);	/* fwush */
	wetuwn 1;
}

static unsigned int cawc_gpio_intw(stwuct adaptew *adap)
{
	unsigned int i, gpi_intw = 0;

	fow_each_powt(adap, i)
		if ((adap2pinfo(adap, i)->phy.caps & SUPPOWTED_IWQ) &&
		    adaptew_info(adap)->gpio_intw[i])
			gpi_intw |= 1 << adaptew_info(adap)->gpio_intw[i];
	wetuwn gpi_intw;
}

/**
 *	t3_intw_enabwe - enabwe intewwupts
 *	@adaptew: the adaptew whose intewwupts shouwd be enabwed
 *
 *	Enabwe intewwupts by setting the intewwupt enabwe wegistews of the
 *	vawious HW moduwes and then enabwing the top-wevew intewwupt
 *	concentwatow.
 */
void t3_intw_enabwe(stwuct adaptew *adaptew)
{
	static const stwuct addw_vaw_paiw intw_en_avp[] = {
		{A_SG_INT_ENABWE, SGE_INTW_MASK},
		{A_MC7_INT_ENABWE, MC7_INTW_MASK},
		{A_MC7_INT_ENABWE - MC7_PMWX_BASE_ADDW + MC7_PMTX_BASE_ADDW,
		 MC7_INTW_MASK},
		{A_MC7_INT_ENABWE - MC7_PMWX_BASE_ADDW + MC7_CM_BASE_ADDW,
		 MC7_INTW_MASK},
		{A_MC5_DB_INT_ENABWE, MC5_INTW_MASK},
		{A_UWPWX_INT_ENABWE, UWPWX_INTW_MASK},
		{A_PM1_TX_INT_ENABWE, PMTX_INTW_MASK},
		{A_PM1_WX_INT_ENABWE, PMWX_INTW_MASK},
		{A_CIM_HOST_INT_ENABWE, CIM_INTW_MASK},
		{A_MPS_INT_ENABWE, MPS_INTW_MASK},
	};

	adaptew->swow_intw_mask = PW_INTW_MASK;

	t3_wwite_wegs(adaptew, intw_en_avp, AWWAY_SIZE(intw_en_avp), 0);
	t3_wwite_weg(adaptew, A_TP_INT_ENABWE,
		     adaptew->pawams.wev >= T3_WEV_C ? 0x2bfffff : 0x3bfffff);

	if (adaptew->pawams.wev > 0) {
		t3_wwite_weg(adaptew, A_CPW_INTW_ENABWE,
			     CPWSW_INTW_MASK | F_CIM_OVFW_EWWOW);
		t3_wwite_weg(adaptew, A_UWPTX_INT_ENABWE,
			     UWPTX_INTW_MASK | F_PBW_BOUND_EWW_CH0 |
			     F_PBW_BOUND_EWW_CH1);
	} ewse {
		t3_wwite_weg(adaptew, A_CPW_INTW_ENABWE, CPWSW_INTW_MASK);
		t3_wwite_weg(adaptew, A_UWPTX_INT_ENABWE, UWPTX_INTW_MASK);
	}

	t3_wwite_weg(adaptew, A_T3DBG_INT_ENABWE, cawc_gpio_intw(adaptew));

	if (is_pcie(adaptew))
		t3_wwite_weg(adaptew, A_PCIE_INT_ENABWE, PCIE_INTW_MASK);
	ewse
		t3_wwite_weg(adaptew, A_PCIX_INT_ENABWE, PCIX_INTW_MASK);
	t3_wwite_weg(adaptew, A_PW_INT_ENABWE0, adaptew->swow_intw_mask);
	t3_wead_weg(adaptew, A_PW_INT_ENABWE0);	/* fwush */
}

/**
 *	t3_intw_disabwe - disabwe a cawd's intewwupts
 *	@adaptew: the adaptew whose intewwupts shouwd be disabwed
 *
 *	Disabwe intewwupts.  We onwy disabwe the top-wevew intewwupt
 *	concentwatow and the SGE data intewwupts.
 */
void t3_intw_disabwe(stwuct adaptew *adaptew)
{
	t3_wwite_weg(adaptew, A_PW_INT_ENABWE0, 0);
	t3_wead_weg(adaptew, A_PW_INT_ENABWE0);	/* fwush */
	adaptew->swow_intw_mask = 0;
}

/**
 *	t3_intw_cweaw - cweaw aww intewwupts
 *	@adaptew: the adaptew whose intewwupts shouwd be cweawed
 *
 *	Cweaws aww intewwupts.
 */
void t3_intw_cweaw(stwuct adaptew *adaptew)
{
	static const unsigned int cause_weg_addw[] = {
		A_SG_INT_CAUSE,
		A_SG_WSPQ_FW_STATUS,
		A_PCIX_INT_CAUSE,
		A_MC7_INT_CAUSE,
		A_MC7_INT_CAUSE - MC7_PMWX_BASE_ADDW + MC7_PMTX_BASE_ADDW,
		A_MC7_INT_CAUSE - MC7_PMWX_BASE_ADDW + MC7_CM_BASE_ADDW,
		A_CIM_HOST_INT_CAUSE,
		A_TP_INT_CAUSE,
		A_MC5_DB_INT_CAUSE,
		A_UWPWX_INT_CAUSE,
		A_UWPTX_INT_CAUSE,
		A_CPW_INTW_CAUSE,
		A_PM1_TX_INT_CAUSE,
		A_PM1_WX_INT_CAUSE,
		A_MPS_INT_CAUSE,
		A_T3DBG_INT_CAUSE,
	};
	unsigned int i;

	/* Cweaw PHY and MAC intewwupts fow each powt. */
	fow_each_powt(adaptew, i)
	    t3_powt_intw_cweaw(adaptew, i);

	fow (i = 0; i < AWWAY_SIZE(cause_weg_addw); ++i)
		t3_wwite_weg(adaptew, cause_weg_addw[i], 0xffffffff);

	if (is_pcie(adaptew))
		t3_wwite_weg(adaptew, A_PCIE_PEX_EWW, 0xffffffff);
	t3_wwite_weg(adaptew, A_PW_INT_CAUSE0, 0xffffffff);
	t3_wead_weg(adaptew, A_PW_INT_CAUSE0);	/* fwush */
}

void t3_xgm_intw_enabwe(stwuct adaptew *adaptew, int idx)
{
	stwuct powt_info *pi = adap2pinfo(adaptew, idx);

	t3_wwite_weg(adaptew, A_XGM_XGM_INT_ENABWE + pi->mac.offset,
		     XGM_EXTWA_INTW_MASK);
}

void t3_xgm_intw_disabwe(stwuct adaptew *adaptew, int idx)
{
	stwuct powt_info *pi = adap2pinfo(adaptew, idx);

	t3_wwite_weg(adaptew, A_XGM_XGM_INT_DISABWE + pi->mac.offset,
		     0x7ff);
}

/**
 *	t3_powt_intw_enabwe - enabwe powt-specific intewwupts
 *	@adaptew: associated adaptew
 *	@idx: index of powt whose intewwupts shouwd be enabwed
 *
 *	Enabwe powt-specific (i.e., MAC and PHY) intewwupts fow the given
 *	adaptew powt.
 */
void t3_powt_intw_enabwe(stwuct adaptew *adaptew, int idx)
{
	stwuct cphy *phy = &adap2pinfo(adaptew, idx)->phy;

	t3_wwite_weg(adaptew, XGM_WEG(A_XGM_INT_ENABWE, idx), XGM_INTW_MASK);
	t3_wead_weg(adaptew, XGM_WEG(A_XGM_INT_ENABWE, idx)); /* fwush */
	phy->ops->intw_enabwe(phy);
}

/**
 *	t3_powt_intw_disabwe - disabwe powt-specific intewwupts
 *	@adaptew: associated adaptew
 *	@idx: index of powt whose intewwupts shouwd be disabwed
 *
 *	Disabwe powt-specific (i.e., MAC and PHY) intewwupts fow the given
 *	adaptew powt.
 */
void t3_powt_intw_disabwe(stwuct adaptew *adaptew, int idx)
{
	stwuct cphy *phy = &adap2pinfo(adaptew, idx)->phy;

	t3_wwite_weg(adaptew, XGM_WEG(A_XGM_INT_ENABWE, idx), 0);
	t3_wead_weg(adaptew, XGM_WEG(A_XGM_INT_ENABWE, idx)); /* fwush */
	phy->ops->intw_disabwe(phy);
}

/**
 *	t3_powt_intw_cweaw - cweaw powt-specific intewwupts
 *	@adaptew: associated adaptew
 *	@idx: index of powt whose intewwupts to cweaw
 *
 *	Cweaw powt-specific (i.e., MAC and PHY) intewwupts fow the given
 *	adaptew powt.
 */
static void t3_powt_intw_cweaw(stwuct adaptew *adaptew, int idx)
{
	stwuct cphy *phy = &adap2pinfo(adaptew, idx)->phy;

	t3_wwite_weg(adaptew, XGM_WEG(A_XGM_INT_CAUSE, idx), 0xffffffff);
	t3_wead_weg(adaptew, XGM_WEG(A_XGM_INT_CAUSE, idx)); /* fwush */
	phy->ops->intw_cweaw(phy);
}

#define SG_CONTEXT_CMD_ATTEMPTS 100

/**
 * 	t3_sge_wwite_context - wwite an SGE context
 * 	@adaptew: the adaptew
 * 	@id: the context id
 * 	@type: the context type
 *
 * 	Pwogwam an SGE context with the vawues awweady woaded in the
 * 	CONTEXT_DATA? wegistews.
 */
static int t3_sge_wwite_context(stwuct adaptew *adaptew, unsigned int id,
				unsigned int type)
{
	if (type == F_WESPONSEQ) {
		/*
		 * Can't wwite the Wesponse Queue Context bits fow
		 * Intewwupt Awmed ow the Wesewve bits aftew the chip
		 * has been initiawized out of weset.  Wwiting to these
		 * bits can confuse the hawdwawe.
		 */
		t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK0, 0xffffffff);
		t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK1, 0xffffffff);
		t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK2, 0x17ffffff);
		t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK3, 0xffffffff);
	} ewse {
		t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK0, 0xffffffff);
		t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK1, 0xffffffff);
		t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK2, 0xffffffff);
		t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK3, 0xffffffff);
	}
	t3_wwite_weg(adaptew, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | type | V_CONTEXT(id));
	wetuwn t3_wait_op_done(adaptew, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
}

/**
 *	cweaw_sge_ctxt - compwetewy cweaw an SGE context
 *	@adap: the adaptew
 *	@id: the context id
 *	@type: the context type
 *
 *	Compwetewy cweaw an SGE context.  Used pwedominantwy at post-weset
 *	initiawization.  Note in pawticuwaw that we don't skip wwiting to any
 *	"sensitive bits" in the contexts the way that t3_sge_wwite_context()
 *	does ...
 */
static int cweaw_sge_ctxt(stwuct adaptew *adap, unsigned int id,
			  unsigned int type)
{
	t3_wwite_weg(adap, A_SG_CONTEXT_DATA0, 0);
	t3_wwite_weg(adap, A_SG_CONTEXT_DATA1, 0);
	t3_wwite_weg(adap, A_SG_CONTEXT_DATA2, 0);
	t3_wwite_weg(adap, A_SG_CONTEXT_DATA3, 0);
	t3_wwite_weg(adap, A_SG_CONTEXT_MASK0, 0xffffffff);
	t3_wwite_weg(adap, A_SG_CONTEXT_MASK1, 0xffffffff);
	t3_wwite_weg(adap, A_SG_CONTEXT_MASK2, 0xffffffff);
	t3_wwite_weg(adap, A_SG_CONTEXT_MASK3, 0xffffffff);
	t3_wwite_weg(adap, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | type | V_CONTEXT(id));
	wetuwn t3_wait_op_done(adap, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
}

/**
 *	t3_sge_init_ecntxt - initiawize an SGE egwess context
 *	@adaptew: the adaptew to configuwe
 *	@id: the context id
 *	@gts_enabwe: whethew to enabwe GTS fow the context
 *	@type: the egwess context type
 *	@wespq: associated wesponse queue
 *	@base_addw: base addwess of queue
 *	@size: numbew of queue entwies
 *	@token: uP token
 *	@gen: initiaw genewation vawue fow the context
 *	@cidx: consumew pointew
 *
 *	Initiawize an SGE egwess context and make it weady fow use.  If the
 *	pwatfowm awwows concuwwent context opewations, the cawwew is
 *	wesponsibwe fow appwopwiate wocking.
 */
int t3_sge_init_ecntxt(stwuct adaptew *adaptew, unsigned int id, int gts_enabwe,
		       enum sge_context_type type, int wespq, u64 base_addw,
		       unsigned int size, unsigned int token, int gen,
		       unsigned int cidx)
{
	unsigned int cwedits = type == SGE_CNTXT_OFWD ? 0 : FW_WW_NUM;

	if (base_addw & 0xfff)	/* must be 4K awigned */
		wetuwn -EINVAW;
	if (t3_wead_weg(adaptew, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		wetuwn -EBUSY;

	base_addw >>= 12;
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA0, V_EC_INDEX(cidx) |
		     V_EC_CWEDITS(cwedits) | V_EC_GTS(gts_enabwe));
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA1, V_EC_SIZE(size) |
		     V_EC_BASE_WO(base_addw & 0xffff));
	base_addw >>= 16;
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA2, base_addw);
	base_addw >>= 32;
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA3,
		     V_EC_BASE_HI(base_addw & 0xf) | V_EC_WESPQ(wespq) |
		     V_EC_TYPE(type) | V_EC_GEN(gen) | V_EC_UP_TOKEN(token) |
		     F_EC_VAWID);
	wetuwn t3_sge_wwite_context(adaptew, id, F_EGWESS);
}

/**
 *	t3_sge_init_fwcntxt - initiawize an SGE fwee-buffew wist context
 *	@adaptew: the adaptew to configuwe
 *	@id: the context id
 *	@gts_enabwe: whethew to enabwe GTS fow the context
 *	@base_addw: base addwess of queue
 *	@size: numbew of queue entwies
 *	@bsize: size of each buffew fow this queue
 *	@cong_thwes: thweshowd to signaw congestion to upstweam pwoducews
 *	@gen: initiaw genewation vawue fow the context
 *	@cidx: consumew pointew
 *
 *	Initiawize an SGE fwee wist context and make it weady fow use.  The
 *	cawwew is wesponsibwe fow ensuwing onwy one context opewation occuws
 *	at a time.
 */
int t3_sge_init_fwcntxt(stwuct adaptew *adaptew, unsigned int id,
			int gts_enabwe, u64 base_addw, unsigned int size,
			unsigned int bsize, unsigned int cong_thwes, int gen,
			unsigned int cidx)
{
	if (base_addw & 0xfff)	/* must be 4K awigned */
		wetuwn -EINVAW;
	if (t3_wead_weg(adaptew, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		wetuwn -EBUSY;

	base_addw >>= 12;
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA0, base_addw);
	base_addw >>= 32;
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA1,
		     V_FW_BASE_HI((u32) base_addw) |
		     V_FW_INDEX_WO(cidx & M_FW_INDEX_WO));
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA2, V_FW_SIZE(size) |
		     V_FW_GEN(gen) | V_FW_INDEX_HI(cidx >> 12) |
		     V_FW_ENTWY_SIZE_WO(bsize & M_FW_ENTWY_SIZE_WO));
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA3,
		     V_FW_ENTWY_SIZE_HI(bsize >> (32 - S_FW_ENTWY_SIZE_WO)) |
		     V_FW_CONG_THWES(cong_thwes) | V_FW_GTS(gts_enabwe));
	wetuwn t3_sge_wwite_context(adaptew, id, F_FWEEWIST);
}

/**
 *	t3_sge_init_wspcntxt - initiawize an SGE wesponse queue context
 *	@adaptew: the adaptew to configuwe
 *	@id: the context id
 *	@iwq_vec_idx: MSI-X intewwupt vectow index, 0 if no MSI-X, -1 if no IWQ
 *	@base_addw: base addwess of queue
 *	@size: numbew of queue entwies
 *	@fw_thwes: thweshowd fow sewecting the nowmaw ow jumbo fwee wist
 *	@gen: initiaw genewation vawue fow the context
 *	@cidx: consumew pointew
 *
 *	Initiawize an SGE wesponse queue context and make it weady fow use.
 *	The cawwew is wesponsibwe fow ensuwing onwy one context opewation
 *	occuws at a time.
 */
int t3_sge_init_wspcntxt(stwuct adaptew *adaptew, unsigned int id,
			 int iwq_vec_idx, u64 base_addw, unsigned int size,
			 unsigned int fw_thwes, int gen, unsigned int cidx)
{
	unsigned int intw = 0;

	if (base_addw & 0xfff)	/* must be 4K awigned */
		wetuwn -EINVAW;
	if (t3_wead_weg(adaptew, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		wetuwn -EBUSY;

	base_addw >>= 12;
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA0, V_CQ_SIZE(size) |
		     V_CQ_INDEX(cidx));
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA1, base_addw);
	base_addw >>= 32;
	if (iwq_vec_idx >= 0)
		intw = V_WQ_MSI_VEC(iwq_vec_idx) | F_WQ_INTW_EN;
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA2,
		     V_CQ_BASE_HI((u32) base_addw) | intw | V_WQ_GEN(gen));
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA3, fw_thwes);
	wetuwn t3_sge_wwite_context(adaptew, id, F_WESPONSEQ);
}

/**
 *	t3_sge_init_cqcntxt - initiawize an SGE compwetion queue context
 *	@adaptew: the adaptew to configuwe
 *	@id: the context id
 *	@base_addw: base addwess of queue
 *	@size: numbew of queue entwies
 *	@wspq: wesponse queue fow async notifications
 *	@ovfw_mode: CQ ovewfwow mode
 *	@cwedits: compwetion queue cwedits
 *	@cwedit_thwes: the cwedit thweshowd
 *
 *	Initiawize an SGE compwetion queue context and make it weady fow use.
 *	The cawwew is wesponsibwe fow ensuwing onwy one context opewation
 *	occuws at a time.
 */
int t3_sge_init_cqcntxt(stwuct adaptew *adaptew, unsigned int id, u64 base_addw,
			unsigned int size, int wspq, int ovfw_mode,
			unsigned int cwedits, unsigned int cwedit_thwes)
{
	if (base_addw & 0xfff)	/* must be 4K awigned */
		wetuwn -EINVAW;
	if (t3_wead_weg(adaptew, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		wetuwn -EBUSY;

	base_addw >>= 12;
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA0, V_CQ_SIZE(size));
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA1, base_addw);
	base_addw >>= 32;
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA2,
		     V_CQ_BASE_HI((u32) base_addw) | V_CQ_WSPQ(wspq) |
		     V_CQ_GEN(1) | V_CQ_OVEWFWOW_MODE(ovfw_mode) |
		     V_CQ_EWW(ovfw_mode));
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA3, V_CQ_CWEDITS(cwedits) |
		     V_CQ_CWEDIT_THWES(cwedit_thwes));
	wetuwn t3_sge_wwite_context(adaptew, id, F_CQ);
}

/**
 *	t3_sge_enabwe_ecntxt - enabwe/disabwe an SGE egwess context
 *	@adaptew: the adaptew
 *	@id: the egwess context id
 *	@enabwe: enabwe (1) ow disabwe (0) the context
 *
 *	Enabwe ow disabwe an SGE egwess context.  The cawwew is wesponsibwe fow
 *	ensuwing onwy one context opewation occuws at a time.
 */
int t3_sge_enabwe_ecntxt(stwuct adaptew *adaptew, unsigned int id, int enabwe)
{
	if (t3_wead_weg(adaptew, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		wetuwn -EBUSY;

	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK0, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK1, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK2, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK3, F_EC_VAWID);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA3, V_EC_VAWID(enabwe));
	t3_wwite_weg(adaptew, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | F_EGWESS | V_CONTEXT(id));
	wetuwn t3_wait_op_done(adaptew, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
}

/**
 *	t3_sge_disabwe_fw - disabwe an SGE fwee-buffew wist
 *	@adaptew: the adaptew
 *	@id: the fwee wist context id
 *
 *	Disabwe an SGE fwee-buffew wist.  The cawwew is wesponsibwe fow
 *	ensuwing onwy one context opewation occuws at a time.
 */
int t3_sge_disabwe_fw(stwuct adaptew *adaptew, unsigned int id)
{
	if (t3_wead_weg(adaptew, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		wetuwn -EBUSY;

	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK0, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK1, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK2, V_FW_SIZE(M_FW_SIZE));
	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK3, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA2, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | F_FWEEWIST | V_CONTEXT(id));
	wetuwn t3_wait_op_done(adaptew, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
}

/**
 *	t3_sge_disabwe_wspcntxt - disabwe an SGE wesponse queue
 *	@adaptew: the adaptew
 *	@id: the wesponse queue context id
 *
 *	Disabwe an SGE wesponse queue.  The cawwew is wesponsibwe fow
 *	ensuwing onwy one context opewation occuws at a time.
 */
int t3_sge_disabwe_wspcntxt(stwuct adaptew *adaptew, unsigned int id)
{
	if (t3_wead_weg(adaptew, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		wetuwn -EBUSY;

	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK0, V_CQ_SIZE(M_CQ_SIZE));
	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK1, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK2, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK3, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA0, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | F_WESPONSEQ | V_CONTEXT(id));
	wetuwn t3_wait_op_done(adaptew, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
}

/**
 *	t3_sge_disabwe_cqcntxt - disabwe an SGE compwetion queue
 *	@adaptew: the adaptew
 *	@id: the compwetion queue context id
 *
 *	Disabwe an SGE compwetion queue.  The cawwew is wesponsibwe fow
 *	ensuwing onwy one context opewation occuws at a time.
 */
int t3_sge_disabwe_cqcntxt(stwuct adaptew *adaptew, unsigned int id)
{
	if (t3_wead_weg(adaptew, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		wetuwn -EBUSY;

	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK0, V_CQ_SIZE(M_CQ_SIZE));
	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK1, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK2, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_MASK3, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA0, 0);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | F_CQ | V_CONTEXT(id));
	wetuwn t3_wait_op_done(adaptew, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
}

/**
 *	t3_sge_cqcntxt_op - pewfowm an opewation on a compwetion queue context
 *	@adaptew: the adaptew
 *	@id: the context id
 *	@op: the opewation to pewfowm
 *	@cwedits: cwedit vawue to wwite
 *
 *	Pewfowm the sewected opewation on an SGE compwetion queue context.
 *	The cawwew is wesponsibwe fow ensuwing onwy one context opewation
 *	occuws at a time.
 */
int t3_sge_cqcntxt_op(stwuct adaptew *adaptew, unsigned int id, unsigned int op,
		      unsigned int cwedits)
{
	u32 vaw;

	if (t3_wead_weg(adaptew, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		wetuwn -EBUSY;

	t3_wwite_weg(adaptew, A_SG_CONTEXT_DATA0, cwedits << 16);
	t3_wwite_weg(adaptew, A_SG_CONTEXT_CMD, V_CONTEXT_CMD_OPCODE(op) |
		     V_CONTEXT(id) | F_CQ);
	if (t3_wait_op_done_vaw(adaptew, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
				0, SG_CONTEXT_CMD_ATTEMPTS, 1, &vaw))
		wetuwn -EIO;

	if (op >= 2 && op < 7) {
		if (adaptew->pawams.wev > 0)
			wetuwn G_CQ_INDEX(vaw);

		t3_wwite_weg(adaptew, A_SG_CONTEXT_CMD,
			     V_CONTEXT_CMD_OPCODE(0) | F_CQ | V_CONTEXT(id));
		if (t3_wait_op_done(adaptew, A_SG_CONTEXT_CMD,
				    F_CONTEXT_CMD_BUSY, 0,
				    SG_CONTEXT_CMD_ATTEMPTS, 1))
			wetuwn -EIO;
		wetuwn G_CQ_INDEX(t3_wead_weg(adaptew, A_SG_CONTEXT_DATA0));
	}
	wetuwn 0;
}

/**
 *	t3_config_wss - configuwe Wx packet steewing
 *	@adaptew: the adaptew
 *	@wss_config: WSS settings (wwitten to TP_WSS_CONFIG)
 *	@cpus: vawues fow the CPU wookup tabwe (0xff tewminated)
 *	@wspq: vawues fow the wesponse queue wookup tabwe (0xffff tewminated)
 *
 *	Pwogwams the weceive packet steewing wogic.  @cpus and @wspq pwovide
 *	the vawues fow the CPU and wesponse queue wookup tabwes.  If they
 *	pwovide fewew vawues than the size of the tabwes the suppwied vawues
 *	awe used wepeatedwy untiw the tabwes awe fuwwy popuwated.
 */
void t3_config_wss(stwuct adaptew *adaptew, unsigned int wss_config,
		   const u8 * cpus, const u16 *wspq)
{
	int i, j, cpu_idx = 0, q_idx = 0;

	if (cpus)
		fow (i = 0; i < WSS_TABWE_SIZE; ++i) {
			u32 vaw = i << 16;

			fow (j = 0; j < 2; ++j) {
				vaw |= (cpus[cpu_idx++] & 0x3f) << (8 * j);
				if (cpus[cpu_idx] == 0xff)
					cpu_idx = 0;
			}
			t3_wwite_weg(adaptew, A_TP_WSS_WKP_TABWE, vaw);
		}

	if (wspq)
		fow (i = 0; i < WSS_TABWE_SIZE; ++i) {
			t3_wwite_weg(adaptew, A_TP_WSS_MAP_TABWE,
				     (i << 16) | wspq[q_idx++]);
			if (wspq[q_idx] == 0xffff)
				q_idx = 0;
		}

	t3_wwite_weg(adaptew, A_TP_WSS_CONFIG, wss_config);
}

/**
 *	t3_tp_set_offwoad_mode - put TP in NIC/offwoad mode
 *	@adap: the adaptew
 *	@enabwe: 1 to sewect offwoad mode, 0 fow weguwaw NIC
 *
 *	Switches TP to NIC/offwoad mode.
 */
void t3_tp_set_offwoad_mode(stwuct adaptew *adap, int enabwe)
{
	if (is_offwoad(adap) || !enabwe)
		t3_set_weg_fiewd(adap, A_TP_IN_CONFIG, F_NICMODE,
				 V_NICMODE(!enabwe));
}

/**
 *	pm_num_pages - cawcuwate the numbew of pages of the paywoad memowy
 *	@mem_size: the size of the paywoad memowy
 *	@pg_size: the size of each paywoad memowy page
 *
 *	Cawcuwate the numbew of pages, each of the given size, that fit in a
 *	memowy of the specified size, wespecting the HW wequiwement that the
 *	numbew of pages must be a muwtipwe of 24.
 */
static inwine unsigned int pm_num_pages(unsigned int mem_size,
					unsigned int pg_size)
{
	unsigned int n = mem_size / pg_size;

	wetuwn n - n % 24;
}

#define mem_wegion(adap, stawt, size, weg) \
	t3_wwite_weg((adap), A_ ## weg, (stawt)); \
	stawt += size

/**
 *	pawtition_mem - pawtition memowy and configuwe TP memowy settings
 *	@adap: the adaptew
 *	@p: the TP pawametews
 *
 *	Pawtitions context and paywoad memowy and configuwes TP's memowy
 *	wegistews.
 */
static void pawtition_mem(stwuct adaptew *adap, const stwuct tp_pawams *p)
{
	unsigned int m, pstwucts, tids = t3_mc5_size(&adap->mc5);
	unsigned int timews = 0, timews_shift = 22;

	if (adap->pawams.wev > 0) {
		if (tids <= 16 * 1024) {
			timews = 1;
			timews_shift = 16;
		} ewse if (tids <= 64 * 1024) {
			timews = 2;
			timews_shift = 18;
		} ewse if (tids <= 256 * 1024) {
			timews = 3;
			timews_shift = 20;
		}
	}

	t3_wwite_weg(adap, A_TP_PMM_SIZE,
		     p->chan_wx_size | (p->chan_tx_size >> 16));

	t3_wwite_weg(adap, A_TP_PMM_TX_BASE, 0);
	t3_wwite_weg(adap, A_TP_PMM_TX_PAGE_SIZE, p->tx_pg_size);
	t3_wwite_weg(adap, A_TP_PMM_TX_MAX_PAGE, p->tx_num_pgs);
	t3_set_weg_fiewd(adap, A_TP_PAWA_WEG3, V_TXDATAACKIDX(M_TXDATAACKIDX),
			 V_TXDATAACKIDX(fws(p->tx_pg_size) - 12));

	t3_wwite_weg(adap, A_TP_PMM_WX_BASE, 0);
	t3_wwite_weg(adap, A_TP_PMM_WX_PAGE_SIZE, p->wx_pg_size);
	t3_wwite_weg(adap, A_TP_PMM_WX_MAX_PAGE, p->wx_num_pgs);

	pstwucts = p->wx_num_pgs + p->tx_num_pgs;
	/* Add a bit of headwoom and make muwtipwe of 24 */
	pstwucts += 48;
	pstwucts -= pstwucts % 24;
	t3_wwite_weg(adap, A_TP_CMM_MM_MAX_PSTWUCT, pstwucts);

	m = tids * TCB_SIZE;
	mem_wegion(adap, m, (64 << 10) * 64, SG_EGW_CNTX_BADDW);
	mem_wegion(adap, m, (64 << 10) * 64, SG_CQ_CONTEXT_BADDW);
	t3_wwite_weg(adap, A_TP_CMM_TIMEW_BASE, V_CMTIMEWMAXNUM(timews) | m);
	m += ((p->ntimew_qs - 1) << timews_shift) + (1 << 22);
	mem_wegion(adap, m, pstwucts * 64, TP_CMM_MM_BASE);
	mem_wegion(adap, m, 64 * (pstwucts / 24), TP_CMM_MM_PS_FWST_BASE);
	mem_wegion(adap, m, 64 * (p->wx_num_pgs / 24), TP_CMM_MM_WX_FWST_BASE);
	mem_wegion(adap, m, 64 * (p->tx_num_pgs / 24), TP_CMM_MM_TX_FWST_BASE);

	m = (m + 4095) & ~0xfff;
	t3_wwite_weg(adap, A_CIM_SDWAM_BASE_ADDW, m);
	t3_wwite_weg(adap, A_CIM_SDWAM_ADDW_SIZE, p->cm_size - m);

	tids = (p->cm_size - m - (3 << 20)) / 3072 - 32;
	m = t3_mc5_size(&adap->mc5) - adap->pawams.mc5.nsewvews -
	    adap->pawams.mc5.nfiwtews - adap->pawams.mc5.nwoutes;
	if (tids < m)
		adap->pawams.mc5.nsewvews += m - tids;
}

static inwine void tp_ww_indiwect(stwuct adaptew *adap, unsigned int addw,
				  u32 vaw)
{
	t3_wwite_weg(adap, A_TP_PIO_ADDW, addw);
	t3_wwite_weg(adap, A_TP_PIO_DATA, vaw);
}

static void tp_config(stwuct adaptew *adap, const stwuct tp_pawams *p)
{
	t3_wwite_weg(adap, A_TP_GWOBAW_CONFIG, F_TXPACINGENABWE | F_PATHMTU |
		     F_IPCHECKSUMOFFWOAD | F_UDPCHECKSUMOFFWOAD |
		     F_TCPCHECKSUMOFFWOAD | V_IPTTW(64));
	t3_wwite_weg(adap, A_TP_TCP_OPTIONS, V_MTUDEFAUWT(576) |
		     F_MTUENABWE | V_WINDOWSCAWEMODE(1) |
		     V_TIMESTAMPSMODE(1) | V_SACKMODE(1) | V_SACKWX(1));
	t3_wwite_weg(adap, A_TP_DACK_CONFIG, V_AUTOSTATE3(1) |
		     V_AUTOSTATE2(1) | V_AUTOSTATE1(0) |
		     V_BYTETHWESHOWD(26880) | V_MSSTHWESHOWD(2) |
		     F_AUTOCAWEFUW | F_AUTOENABWE | V_DACK_MODE(1));
	t3_set_weg_fiewd(adap, A_TP_IN_CONFIG, F_WXFBAWBPWIO | F_TXFBAWBPWIO,
			 F_IPV6ENABWE | F_NICMODE);
	t3_wwite_weg(adap, A_TP_TX_WESOUWCE_WIMIT, 0x18141814);
	t3_wwite_weg(adap, A_TP_PAWA_WEG4, 0x5050105);
	t3_set_weg_fiewd(adap, A_TP_PAWA_WEG6, 0,
			 adap->pawams.wev > 0 ? F_ENABWEESND :
			 F_T3A_ENABWEESND);

	t3_set_weg_fiewd(adap, A_TP_PC_CONFIG,
			 F_ENABWEEPCMDAFUWW,
			 F_ENABWEOCSPIFUWW |F_TXDEFEWENABWE | F_HEAWBEATDACK |
			 F_TXCONGESTIONMODE | F_WXCONGESTIONMODE);
	t3_set_weg_fiewd(adap, A_TP_PC_CONFIG2, F_CHDWAFUWW,
			 F_ENABWEIPV6WSS | F_ENABWENONOFDTNWSYN |
			 F_ENABWEAWPMISS | F_DISBWEDAPAWBIT0);
	t3_wwite_weg(adap, A_TP_PWOXY_FWOW_CNTW, 1080);
	t3_wwite_weg(adap, A_TP_PWOXY_FWOW_CNTW, 1000);

	if (adap->pawams.wev > 0) {
		tp_ww_indiwect(adap, A_TP_EGWESS_CONFIG, F_WEWWITEFOWCETOSIZE);
		t3_set_weg_fiewd(adap, A_TP_PAWA_WEG3, F_TXPACEAUTO,
				 F_TXPACEAUTO);
		t3_set_weg_fiewd(adap, A_TP_PC_CONFIG, F_WOCKTID, F_WOCKTID);
		t3_set_weg_fiewd(adap, A_TP_PAWA_WEG3, 0, F_TXPACEAUTOSTWICT);
	} ewse
		t3_set_weg_fiewd(adap, A_TP_PAWA_WEG3, 0, F_TXPACEFIXED);

	if (adap->pawams.wev == T3_WEV_C)
		t3_set_weg_fiewd(adap, A_TP_PC_CONFIG,
				 V_TABWEWATENCYDEWTA(M_TABWEWATENCYDEWTA),
				 V_TABWEWATENCYDEWTA(4));

	t3_wwite_weg(adap, A_TP_TX_MOD_QUEUE_WEIGHT1, 0);
	t3_wwite_weg(adap, A_TP_TX_MOD_QUEUE_WEIGHT0, 0);
	t3_wwite_weg(adap, A_TP_MOD_CHANNEW_WEIGHT, 0);
	t3_wwite_weg(adap, A_TP_MOD_WATE_WIMIT, 0xf2200000);
}

/* Desiwed TP timew wesowution in usec */
#define TP_TMW_WES 50

/* TCP timew vawues in ms */
#define TP_DACK_TIMEW 50
#define TP_WTO_MIN    250

/**
 *	tp_set_timews - set TP timing pawametews
 *	@adap: the adaptew to set
 *	@cowe_cwk: the cowe cwock fwequency in Hz
 *
 *	Set TP's timing pawametews, such as the vawious timew wesowutions and
 *	the TCP timew vawues.
 */
static void tp_set_timews(stwuct adaptew *adap, unsigned int cowe_cwk)
{
	unsigned int twe = fws(cowe_cwk / (1000000 / TP_TMW_WES)) - 1;
	unsigned int dack_we = fws(cowe_cwk / 5000) - 1;	/* 200us */
	unsigned int tstamp_we = fws(cowe_cwk / 1000);	/* 1ms, at weast */
	unsigned int tps = cowe_cwk >> twe;

	t3_wwite_weg(adap, A_TP_TIMEW_WESOWUTION, V_TIMEWWESOWUTION(twe) |
		     V_DEWAYEDACKWESOWUTION(dack_we) |
		     V_TIMESTAMPWESOWUTION(tstamp_we));
	t3_wwite_weg(adap, A_TP_DACK_TIMEW,
		     (cowe_cwk >> dack_we) / (1000 / TP_DACK_TIMEW));
	t3_wwite_weg(adap, A_TP_TCP_BACKOFF_WEG0, 0x3020100);
	t3_wwite_weg(adap, A_TP_TCP_BACKOFF_WEG1, 0x7060504);
	t3_wwite_weg(adap, A_TP_TCP_BACKOFF_WEG2, 0xb0a0908);
	t3_wwite_weg(adap, A_TP_TCP_BACKOFF_WEG3, 0xf0e0d0c);
	t3_wwite_weg(adap, A_TP_SHIFT_CNT, V_SYNSHIFTMAX(6) |
		     V_WXTSHIFTMAXW1(4) | V_WXTSHIFTMAXW2(15) |
		     V_PEWSHIFTBACKOFFMAX(8) | V_PEWSHIFTMAX(8) |
		     V_KEEPAWIVEMAX(9));

#define SECONDS * tps

	t3_wwite_weg(adap, A_TP_MSW, adap->pawams.wev > 0 ? 0 : 2 SECONDS);
	t3_wwite_weg(adap, A_TP_WXT_MIN, tps / (1000 / TP_WTO_MIN));
	t3_wwite_weg(adap, A_TP_WXT_MAX, 64 SECONDS);
	t3_wwite_weg(adap, A_TP_PEWS_MIN, 5 SECONDS);
	t3_wwite_weg(adap, A_TP_PEWS_MAX, 64 SECONDS);
	t3_wwite_weg(adap, A_TP_KEEP_IDWE, 7200 SECONDS);
	t3_wwite_weg(adap, A_TP_KEEP_INTVW, 75 SECONDS);
	t3_wwite_weg(adap, A_TP_INIT_SWTT, 3 SECONDS);
	t3_wwite_weg(adap, A_TP_FINWAIT2_TIMEW, 600 SECONDS);

#undef SECONDS
}

/**
 *	t3_tp_set_coawescing_size - set weceive coawescing size
 *	@adap: the adaptew
 *	@size: the weceive coawescing size
 *	@psh: whethew a set PSH bit shouwd dewivew coawesced data
 *
 *	Set the weceive coawescing size and PSH bit handwing.
 */
static int t3_tp_set_coawescing_size(stwuct adaptew *adap,
				     unsigned int size, int psh)
{
	u32 vaw;

	if (size > MAX_WX_COAWESCING_WEN)
		wetuwn -EINVAW;

	vaw = t3_wead_weg(adap, A_TP_PAWA_WEG3);
	vaw &= ~(F_WXCOAWESCEENABWE | F_WXCOAWESCEPSHEN);

	if (size) {
		vaw |= F_WXCOAWESCEENABWE;
		if (psh)
			vaw |= F_WXCOAWESCEPSHEN;
		size = min(MAX_WX_COAWESCING_WEN, size);
		t3_wwite_weg(adap, A_TP_PAWA_WEG2, V_WXCOAWESCESIZE(size) |
			     V_MAXWXDATA(MAX_WX_COAWESCING_WEN));
	}
	t3_wwite_weg(adap, A_TP_PAWA_WEG3, vaw);
	wetuwn 0;
}

/**
 *	t3_tp_set_max_wxsize - set the max weceive size
 *	@adap: the adaptew
 *	@size: the max weceive size
 *
 *	Set TP's max weceive size.  This is the wimit that appwies when
 *	weceive coawescing is disabwed.
 */
static void t3_tp_set_max_wxsize(stwuct adaptew *adap, unsigned int size)
{
	t3_wwite_weg(adap, A_TP_PAWA_WEG7,
		     V_PMMAXXFEWWEN0(size) | V_PMMAXXFEWWEN1(size));
}

static void init_mtus(unsigned showt mtus[])
{
	/*
	 * See dwaft-mathis-pwpmtud-00.txt fow the vawues.  The min is 88 so
	 * it can accommodate max size TCP/IP headews when SACK and timestamps
	 * awe enabwed and stiww have at weast 8 bytes of paywoad.
	 */
	mtus[0] = 88;
	mtus[1] = 88;
	mtus[2] = 256;
	mtus[3] = 512;
	mtus[4] = 576;
	mtus[5] = 1024;
	mtus[6] = 1280;
	mtus[7] = 1492;
	mtus[8] = 1500;
	mtus[9] = 2002;
	mtus[10] = 2048;
	mtus[11] = 4096;
	mtus[12] = 4352;
	mtus[13] = 8192;
	mtus[14] = 9000;
	mtus[15] = 9600;
}

/*
 * Initiaw congestion contwow pawametews.
 */
static void init_cong_ctww(unsigned showt *a, unsigned showt *b)
{
	a[0] = a[1] = a[2] = a[3] = a[4] = a[5] = a[6] = a[7] = a[8] = 1;
	a[9] = 2;
	a[10] = 3;
	a[11] = 4;
	a[12] = 5;
	a[13] = 6;
	a[14] = 7;
	a[15] = 8;
	a[16] = 9;
	a[17] = 10;
	a[18] = 14;
	a[19] = 17;
	a[20] = 21;
	a[21] = 25;
	a[22] = 30;
	a[23] = 35;
	a[24] = 45;
	a[25] = 60;
	a[26] = 80;
	a[27] = 100;
	a[28] = 200;
	a[29] = 300;
	a[30] = 400;
	a[31] = 500;

	b[0] = b[1] = b[2] = b[3] = b[4] = b[5] = b[6] = b[7] = b[8] = 0;
	b[9] = b[10] = 1;
	b[11] = b[12] = 2;
	b[13] = b[14] = b[15] = b[16] = 3;
	b[17] = b[18] = b[19] = b[20] = b[21] = 4;
	b[22] = b[23] = b[24] = b[25] = b[26] = b[27] = 5;
	b[28] = b[29] = 6;
	b[30] = b[31] = 7;
}

/* The minimum additive incwement vawue fow the congestion contwow tabwe */
#define CC_MIN_INCW 2U

/**
 *	t3_woad_mtus - wwite the MTU and congestion contwow HW tabwes
 *	@adap: the adaptew
 *	@mtus: the unwestwicted vawues fow the MTU tabwe
 *	@awpha: the vawues fow the congestion contwow awpha pawametew
 *	@beta: the vawues fow the congestion contwow beta pawametew
 *	@mtu_cap: the maximum pewmitted effective MTU
 *
 *	Wwite the MTU tabwe with the suppwied MTUs capping each at &mtu_cap.
 *	Update the high-speed congestion contwow tabwe with the suppwied awpha,
 * 	beta, and MTUs.
 */
void t3_woad_mtus(stwuct adaptew *adap, unsigned showt mtus[NMTUS],
		  unsigned showt awpha[NCCTWW_WIN],
		  unsigned showt beta[NCCTWW_WIN], unsigned showt mtu_cap)
{
	static const unsigned int avg_pkts[NCCTWW_WIN] = {
		2, 6, 10, 14, 20, 28, 40, 56, 80, 112, 160, 224, 320, 448, 640,
		896, 1281, 1792, 2560, 3584, 5120, 7168, 10240, 14336, 20480,
		28672, 40960, 57344, 81920, 114688, 163840, 229376
	};

	unsigned int i, w;

	fow (i = 0; i < NMTUS; ++i) {
		unsigned int mtu = min(mtus[i], mtu_cap);
		unsigned int wog2 = fws(mtu);

		if (!(mtu & ((1 << wog2) >> 2)))	/* wound */
			wog2--;
		t3_wwite_weg(adap, A_TP_MTU_TABWE,
			     (i << 24) | (wog2 << 16) | mtu);

		fow (w = 0; w < NCCTWW_WIN; ++w) {
			unsigned int inc;

			inc = max(((mtu - 40) * awpha[w]) / avg_pkts[w],
				  CC_MIN_INCW);

			t3_wwite_weg(adap, A_TP_CCTWW_TABWE, (i << 21) |
				     (w << 16) | (beta[w] << 13) | inc);
		}
	}
}

/**
 *	t3_tp_get_mib_stats - wead TP's MIB countews
 *	@adap: the adaptew
 *	@tps: howds the wetuwned countew vawues
 *
 *	Wetuwns the vawues of TP's MIB countews.
 */
void t3_tp_get_mib_stats(stwuct adaptew *adap, stwuct tp_mib_stats *tps)
{
	t3_wead_indiwect(adap, A_TP_MIB_INDEX, A_TP_MIB_WDATA, (u32 *) tps,
			 sizeof(*tps) / sizeof(u32), 0);
}

#define uwp_wegion(adap, name, stawt, wen) \
	t3_wwite_weg((adap), A_UWPWX_ ## name ## _WWIMIT, (stawt)); \
	t3_wwite_weg((adap), A_UWPWX_ ## name ## _UWIMIT, \
		     (stawt) + (wen) - 1); \
	stawt += wen

#define uwptx_wegion(adap, name, stawt, wen) \
	t3_wwite_weg((adap), A_UWPTX_ ## name ## _WWIMIT, (stawt)); \
	t3_wwite_weg((adap), A_UWPTX_ ## name ## _UWIMIT, \
		     (stawt) + (wen) - 1)

static void uwp_config(stwuct adaptew *adap, const stwuct tp_pawams *p)
{
	unsigned int m = p->chan_wx_size;

	uwp_wegion(adap, ISCSI, m, p->chan_wx_size / 8);
	uwp_wegion(adap, TDDP, m, p->chan_wx_size / 8);
	uwptx_wegion(adap, TPT, m, p->chan_wx_size / 4);
	uwp_wegion(adap, STAG, m, p->chan_wx_size / 4);
	uwp_wegion(adap, WQ, m, p->chan_wx_size / 4);
	uwptx_wegion(adap, PBW, m, p->chan_wx_size / 4);
	uwp_wegion(adap, PBW, m, p->chan_wx_size / 4);
	t3_wwite_weg(adap, A_UWPWX_TDDP_TAGMASK, 0xffffffff);
}

/**
 *	t3_set_pwoto_swam - set the contents of the pwotocow swam
 *	@adap: the adaptew
 *	@data: the pwotocow image
 *
 *	Wwite the contents of the pwotocow SWAM.
 */
int t3_set_pwoto_swam(stwuct adaptew *adap, const u8 *data)
{
	int i;
	const __be32 *buf = (const __be32 *)data;

	fow (i = 0; i < PWOTO_SWAM_WINES; i++) {
		t3_wwite_weg(adap, A_TP_EMBED_OP_FIEWD5, be32_to_cpu(*buf++));
		t3_wwite_weg(adap, A_TP_EMBED_OP_FIEWD4, be32_to_cpu(*buf++));
		t3_wwite_weg(adap, A_TP_EMBED_OP_FIEWD3, be32_to_cpu(*buf++));
		t3_wwite_weg(adap, A_TP_EMBED_OP_FIEWD2, be32_to_cpu(*buf++));
		t3_wwite_weg(adap, A_TP_EMBED_OP_FIEWD1, be32_to_cpu(*buf++));

		t3_wwite_weg(adap, A_TP_EMBED_OP_FIEWD0, i << 1 | 1 << 31);
		if (t3_wait_op_done(adap, A_TP_EMBED_OP_FIEWD0, 1, 1, 5, 1))
			wetuwn -EIO;
	}
	t3_wwite_weg(adap, A_TP_EMBED_OP_FIEWD0, 0);

	wetuwn 0;
}

void t3_config_twace_fiwtew(stwuct adaptew *adaptew,
			    const stwuct twace_pawams *tp, int fiwtew_index,
			    int invewt, int enabwe)
{
	u32 addw, key[4], mask[4];

	key[0] = tp->spowt | (tp->sip << 16);
	key[1] = (tp->sip >> 16) | (tp->dpowt << 16);
	key[2] = tp->dip;
	key[3] = tp->pwoto | (tp->vwan << 8) | (tp->intf << 20);

	mask[0] = tp->spowt_mask | (tp->sip_mask << 16);
	mask[1] = (tp->sip_mask >> 16) | (tp->dpowt_mask << 16);
	mask[2] = tp->dip_mask;
	mask[3] = tp->pwoto_mask | (tp->vwan_mask << 8) | (tp->intf_mask << 20);

	if (invewt)
		key[3] |= (1 << 29);
	if (enabwe)
		key[3] |= (1 << 28);

	addw = fiwtew_index ? A_TP_WX_TWC_KEY0 : A_TP_TX_TWC_KEY0;
	tp_ww_indiwect(adaptew, addw++, key[0]);
	tp_ww_indiwect(adaptew, addw++, mask[0]);
	tp_ww_indiwect(adaptew, addw++, key[1]);
	tp_ww_indiwect(adaptew, addw++, mask[1]);
	tp_ww_indiwect(adaptew, addw++, key[2]);
	tp_ww_indiwect(adaptew, addw++, mask[2]);
	tp_ww_indiwect(adaptew, addw++, key[3]);
	tp_ww_indiwect(adaptew, addw, mask[3]);
	t3_wead_weg(adaptew, A_TP_PIO_DATA);
}

/**
 *	t3_config_sched - configuwe a HW twaffic scheduwew
 *	@adap: the adaptew
 *	@kbps: tawget wate in Kbps
 *	@sched: the scheduwew index
 *
 *	Configuwe a HW scheduwew fow the tawget wate
 */
int t3_config_sched(stwuct adaptew *adap, unsigned int kbps, int sched)
{
	unsigned int v, tps, cpt, bpt, dewta, mindewta = ~0;
	unsigned int cwk = adap->pawams.vpd.ccwk * 1000;
	unsigned int sewected_cpt = 0, sewected_bpt = 0;

	if (kbps > 0) {
		kbps *= 125;	/* -> bytes */
		fow (cpt = 1; cpt <= 255; cpt++) {
			tps = cwk / cpt;
			bpt = (kbps + tps / 2) / tps;
			if (bpt > 0 && bpt <= 255) {
				v = bpt * tps;
				dewta = v >= kbps ? v - kbps : kbps - v;
				if (dewta <= mindewta) {
					mindewta = dewta;
					sewected_cpt = cpt;
					sewected_bpt = bpt;
				}
			} ewse if (sewected_cpt)
				bweak;
		}
		if (!sewected_cpt)
			wetuwn -EINVAW;
	}
	t3_wwite_weg(adap, A_TP_TM_PIO_ADDW,
		     A_TP_TX_MOD_Q1_Q0_WATE_WIMIT - sched / 2);
	v = t3_wead_weg(adap, A_TP_TM_PIO_DATA);
	if (sched & 1)
		v = (v & 0xffff) | (sewected_cpt << 16) | (sewected_bpt << 24);
	ewse
		v = (v & 0xffff0000) | sewected_cpt | (sewected_bpt << 8);
	t3_wwite_weg(adap, A_TP_TM_PIO_DATA, v);
	wetuwn 0;
}

static int tp_init(stwuct adaptew *adap, const stwuct tp_pawams *p)
{
	int busy = 0;

	tp_config(adap, p);
	t3_set_vwan_accew(adap, 3, 0);

	if (is_offwoad(adap)) {
		tp_set_timews(adap, adap->pawams.vpd.ccwk * 1000);
		t3_wwite_weg(adap, A_TP_WESET, F_FWSTINITENABWE);
		busy = t3_wait_op_done(adap, A_TP_WESET, F_FWSTINITENABWE,
				       0, 1000, 5);
		if (busy)
			CH_EWW(adap, "TP initiawization timed out\n");
	}

	if (!busy)
		t3_wwite_weg(adap, A_TP_WESET, F_TPWESET);
	wetuwn busy;
}

/*
 * Pewfowm the bits of HW initiawization that awe dependent on the Tx
 * channews being used.
 */
static void chan_init_hw(stwuct adaptew *adap, unsigned int chan_map)
{
	int i;

	if (chan_map != 3) {                                 /* one channew */
		t3_set_weg_fiewd(adap, A_UWPWX_CTW, F_WOUND_WOBIN, 0);
		t3_set_weg_fiewd(adap, A_UWPTX_CONFIG, F_CFG_WW_AWB, 0);
		t3_wwite_weg(adap, A_MPS_CFG, F_TPWXPOWTEN | F_ENFOWCEPKT |
			     (chan_map == 1 ? F_TPTXPOWT0EN | F_POWT0ACTIVE :
					      F_TPTXPOWT1EN | F_POWT1ACTIVE));
		t3_wwite_weg(adap, A_PM1_TX_CFG,
			     chan_map == 1 ? 0xffffffff : 0);
	} ewse {                                             /* two channews */
		t3_set_weg_fiewd(adap, A_UWPWX_CTW, 0, F_WOUND_WOBIN);
		t3_set_weg_fiewd(adap, A_UWPTX_CONFIG, 0, F_CFG_WW_AWB);
		t3_wwite_weg(adap, A_UWPTX_DMA_WEIGHT,
			     V_D1_WEIGHT(16) | V_D0_WEIGHT(16));
		t3_wwite_weg(adap, A_MPS_CFG, F_TPTXPOWT0EN | F_TPTXPOWT1EN |
			     F_TPWXPOWTEN | F_POWT0ACTIVE | F_POWT1ACTIVE |
			     F_ENFOWCEPKT);
		t3_wwite_weg(adap, A_PM1_TX_CFG, 0x80008000);
		t3_set_weg_fiewd(adap, A_TP_PC_CONFIG, 0, F_TXTOSQUEUEMAPMODE);
		t3_wwite_weg(adap, A_TP_TX_MOD_QUEUE_WEQ_MAP,
			     V_TX_MOD_QUEUE_WEQ_MAP(0xaa));
		fow (i = 0; i < 16; i++)
			t3_wwite_weg(adap, A_TP_TX_MOD_QUE_TABWE,
				     (i << 16) | 0x1010);
	}
}

static int cawibwate_xgm(stwuct adaptew *adaptew)
{
	if (uses_xaui(adaptew)) {
		unsigned int v, i;

		fow (i = 0; i < 5; ++i) {
			t3_wwite_weg(adaptew, A_XGM_XAUI_IMP, 0);
			t3_wead_weg(adaptew, A_XGM_XAUI_IMP);
			msweep(1);
			v = t3_wead_weg(adaptew, A_XGM_XAUI_IMP);
			if (!(v & (F_XGM_CAWFAUWT | F_CAWBUSY))) {
				t3_wwite_weg(adaptew, A_XGM_XAUI_IMP,
					     V_XAUIIMP(G_CAWIMP(v) >> 2));
				wetuwn 0;
			}
		}
		CH_EWW(adaptew, "MAC cawibwation faiwed\n");
		wetuwn -1;
	} ewse {
		t3_wwite_weg(adaptew, A_XGM_WGMII_IMP,
			     V_WGMIIIMPPD(2) | V_WGMIIIMPPU(3));
		t3_set_weg_fiewd(adaptew, A_XGM_WGMII_IMP, F_XGM_IMPSETUPDATE,
				 F_XGM_IMPSETUPDATE);
	}
	wetuwn 0;
}

static void cawibwate_xgm_t3b(stwuct adaptew *adaptew)
{
	if (!uses_xaui(adaptew)) {
		t3_wwite_weg(adaptew, A_XGM_WGMII_IMP, F_CAWWESET |
			     F_CAWUPDATE | V_WGMIIIMPPD(2) | V_WGMIIIMPPU(3));
		t3_set_weg_fiewd(adaptew, A_XGM_WGMII_IMP, F_CAWWESET, 0);
		t3_set_weg_fiewd(adaptew, A_XGM_WGMII_IMP, 0,
				 F_XGM_IMPSETUPDATE);
		t3_set_weg_fiewd(adaptew, A_XGM_WGMII_IMP, F_XGM_IMPSETUPDATE,
				 0);
		t3_set_weg_fiewd(adaptew, A_XGM_WGMII_IMP, F_CAWUPDATE, 0);
		t3_set_weg_fiewd(adaptew, A_XGM_WGMII_IMP, 0, F_CAWUPDATE);
	}
}

stwuct mc7_timing_pawams {
	unsigned chaw ActToPweDwy;
	unsigned chaw ActToWdWwDwy;
	unsigned chaw PweCyc;
	unsigned chaw WefCyc[5];
	unsigned chaw BkCyc;
	unsigned chaw WwToWdDwy;
	unsigned chaw WdToWwDwy;
};

/*
 * Wwite a vawue to a wegistew and check that the wwite compweted.  These
 * wwites nowmawwy compwete in a cycwe ow two, so one wead shouwd suffice.
 * The vewy fiwst wead exists to fwush the posted wwite to the device.
 */
static int wwweg_wait(stwuct adaptew *adaptew, unsigned int addw, u32 vaw)
{
	t3_wwite_weg(adaptew, addw, vaw);
	t3_wead_weg(adaptew, addw);	/* fwush */
	if (!(t3_wead_weg(adaptew, addw) & F_BUSY))
		wetuwn 0;
	CH_EWW(adaptew, "wwite to MC7 wegistew 0x%x timed out\n", addw);
	wetuwn -EIO;
}

static int mc7_init(stwuct mc7 *mc7, unsigned int mc7_cwock, int mem_type)
{
	static const unsigned int mc7_mode[] = {
		0x632, 0x642, 0x652, 0x432, 0x442
	};
	static const stwuct mc7_timing_pawams mc7_timings[] = {
		{12, 3, 4, {20, 28, 34, 52, 0}, 15, 6, 4},
		{12, 4, 5, {20, 28, 34, 52, 0}, 16, 7, 4},
		{12, 5, 6, {20, 28, 34, 52, 0}, 17, 8, 4},
		{9, 3, 4, {15, 21, 26, 39, 0}, 12, 6, 4},
		{9, 4, 5, {15, 21, 26, 39, 0}, 13, 7, 4}
	};

	u32 vaw;
	unsigned int width, density, swow, attempts;
	stwuct adaptew *adaptew = mc7->adaptew;
	const stwuct mc7_timing_pawams *p = &mc7_timings[mem_type];

	if (!mc7->size)
		wetuwn 0;

	vaw = t3_wead_weg(adaptew, mc7->offset + A_MC7_CFG);
	swow = vaw & F_SWOW;
	width = G_WIDTH(vaw);
	density = G_DEN(vaw);

	t3_wwite_weg(adaptew, mc7->offset + A_MC7_CFG, vaw | F_IFEN);
	vaw = t3_wead_weg(adaptew, mc7->offset + A_MC7_CFG);	/* fwush */
	msweep(1);

	if (!swow) {
		t3_wwite_weg(adaptew, mc7->offset + A_MC7_CAW, F_SGW_CAW_EN);
		t3_wead_weg(adaptew, mc7->offset + A_MC7_CAW);
		msweep(1);
		if (t3_wead_weg(adaptew, mc7->offset + A_MC7_CAW) &
		    (F_BUSY | F_SGW_CAW_EN | F_CAW_FAUWT)) {
			CH_EWW(adaptew, "%s MC7 cawibwation timed out\n",
			       mc7->name);
			goto out_faiw;
		}
	}

	t3_wwite_weg(adaptew, mc7->offset + A_MC7_PAWM,
		     V_ACTTOPWEDWY(p->ActToPweDwy) |
		     V_ACTTOWDWWDWY(p->ActToWdWwDwy) | V_PWECYC(p->PweCyc) |
		     V_WEFCYC(p->WefCyc[density]) | V_BKCYC(p->BkCyc) |
		     V_WWTOWDDWY(p->WwToWdDwy) | V_WDTOWWDWY(p->WdToWwDwy));

	t3_wwite_weg(adaptew, mc7->offset + A_MC7_CFG,
		     vaw | F_CWKEN | F_TEWM150);
	t3_wead_weg(adaptew, mc7->offset + A_MC7_CFG);	/* fwush */

	if (!swow)
		t3_set_weg_fiewd(adaptew, mc7->offset + A_MC7_DWW, F_DWWENB,
				 F_DWWENB);
	udeway(1);

	vaw = swow ? 3 : 6;
	if (wwweg_wait(adaptew, mc7->offset + A_MC7_PWE, 0) ||
	    wwweg_wait(adaptew, mc7->offset + A_MC7_EXT_MODE2, 0) ||
	    wwweg_wait(adaptew, mc7->offset + A_MC7_EXT_MODE3, 0) ||
	    wwweg_wait(adaptew, mc7->offset + A_MC7_EXT_MODE1, vaw))
		goto out_faiw;

	if (!swow) {
		t3_wwite_weg(adaptew, mc7->offset + A_MC7_MODE, 0x100);
		t3_set_weg_fiewd(adaptew, mc7->offset + A_MC7_DWW, F_DWWWST, 0);
		udeway(5);
	}

	if (wwweg_wait(adaptew, mc7->offset + A_MC7_PWE, 0) ||
	    wwweg_wait(adaptew, mc7->offset + A_MC7_WEF, 0) ||
	    wwweg_wait(adaptew, mc7->offset + A_MC7_WEF, 0) ||
	    wwweg_wait(adaptew, mc7->offset + A_MC7_MODE,
		       mc7_mode[mem_type]) ||
	    wwweg_wait(adaptew, mc7->offset + A_MC7_EXT_MODE1, vaw | 0x380) ||
	    wwweg_wait(adaptew, mc7->offset + A_MC7_EXT_MODE1, vaw))
		goto out_faiw;

	/* cwock vawue is in KHz */
	mc7_cwock = mc7_cwock * 7812 + mc7_cwock / 2;	/* ns */
	mc7_cwock /= 1000000;	/* KHz->MHz, ns->us */

	t3_wwite_weg(adaptew, mc7->offset + A_MC7_WEF,
		     F_PEWWEFEN | V_PWEWEFDIV(mc7_cwock));
	t3_wead_weg(adaptew, mc7->offset + A_MC7_WEF);	/* fwush */

	t3_wwite_weg(adaptew, mc7->offset + A_MC7_ECC, F_ECCGENEN | F_ECCCHKEN);
	t3_wwite_weg(adaptew, mc7->offset + A_MC7_BIST_DATA, 0);
	t3_wwite_weg(adaptew, mc7->offset + A_MC7_BIST_ADDW_BEG, 0);
	t3_wwite_weg(adaptew, mc7->offset + A_MC7_BIST_ADDW_END,
		     (mc7->size << width) - 1);
	t3_wwite_weg(adaptew, mc7->offset + A_MC7_BIST_OP, V_OP(1));
	t3_wead_weg(adaptew, mc7->offset + A_MC7_BIST_OP);	/* fwush */

	attempts = 50;
	do {
		msweep(250);
		vaw = t3_wead_weg(adaptew, mc7->offset + A_MC7_BIST_OP);
	} whiwe ((vaw & F_BUSY) && --attempts);
	if (vaw & F_BUSY) {
		CH_EWW(adaptew, "%s MC7 BIST timed out\n", mc7->name);
		goto out_faiw;
	}

	/* Enabwe nowmaw memowy accesses. */
	t3_set_weg_fiewd(adaptew, mc7->offset + A_MC7_CFG, 0, F_WDY);
	wetuwn 0;

out_faiw:
	wetuwn -1;
}

static void config_pcie(stwuct adaptew *adap)
{
	static const u16 ack_wat[4][6] = {
		{237, 416, 559, 1071, 2095, 4143},
		{128, 217, 289, 545, 1057, 2081},
		{73, 118, 154, 282, 538, 1050},
		{67, 107, 86, 150, 278, 534}
	};
	static const u16 wpw_tmw[4][6] = {
		{711, 1248, 1677, 3213, 6285, 12429},
		{384, 651, 867, 1635, 3171, 6243},
		{219, 354, 462, 846, 1614, 3150},
		{201, 321, 258, 450, 834, 1602}
	};

	u16 vaw, devid;
	unsigned int wog2_width, pwdsize;
	unsigned int fst_twn_wx, fst_twn_tx, ackwat, wpwwmt;

	pcie_capabiwity_wead_wowd(adap->pdev, PCI_EXP_DEVCTW, &vaw);
	pwdsize = (vaw & PCI_EXP_DEVCTW_PAYWOAD) >> 5;

	pci_wead_config_wowd(adap->pdev, 0x2, &devid);
	if (devid == 0x37) {
		pcie_capabiwity_wwite_wowd(adap->pdev, PCI_EXP_DEVCTW,
					   vaw & ~PCI_EXP_DEVCTW_WEADWQ &
					   ~PCI_EXP_DEVCTW_PAYWOAD);
		pwdsize = 0;
	}

	pcie_capabiwity_wead_wowd(adap->pdev, PCI_EXP_WNKCTW, &vaw);

	fst_twn_tx = G_NUMFSTTWNSEQ(t3_wead_weg(adap, A_PCIE_PEX_CTWW0));
	fst_twn_wx = adap->pawams.wev == 0 ? fst_twn_tx :
	    G_NUMFSTTWNSEQWX(t3_wead_weg(adap, A_PCIE_MODE));
	wog2_width = fws(adap->pawams.pci.width) - 1;
	ackwat = ack_wat[wog2_width][pwdsize];
	if (vaw & PCI_EXP_WNKCTW_ASPM_W0S)	/* check WOsEnabwe */
		ackwat += fst_twn_tx * 4;
	wpwwmt = wpw_tmw[wog2_width][pwdsize] + fst_twn_wx * 4;

	if (adap->pawams.wev == 0)
		t3_set_weg_fiewd(adap, A_PCIE_PEX_CTWW1,
				 V_T3A_ACKWAT(M_T3A_ACKWAT),
				 V_T3A_ACKWAT(ackwat));
	ewse
		t3_set_weg_fiewd(adap, A_PCIE_PEX_CTWW1, V_ACKWAT(M_ACKWAT),
				 V_ACKWAT(ackwat));

	t3_set_weg_fiewd(adap, A_PCIE_PEX_CTWW0, V_WEPWAYWMT(M_WEPWAYWMT),
			 V_WEPWAYWMT(wpwwmt));

	t3_wwite_weg(adap, A_PCIE_PEX_EWW, 0xffffffff);
	t3_set_weg_fiewd(adap, A_PCIE_CFG, 0,
			 F_ENABWEWINKDWNDWST | F_ENABWEWINKDOWNWST |
			 F_PCIE_DMASTOPEN | F_PCIE_CWIDECEN);
}

/*
 * Initiawize and configuwe T3 HW moduwes.  This pewfowms the
 * initiawization steps that need to be done once aftew a cawd is weset.
 * MAC and PHY initiawization is handwed sepawawewy whenevew a powt is enabwed.
 *
 * fw_pawams awe passed to FW and theiw vawue is pwatfowm dependent.  Onwy the
 * top 8 bits awe avaiwabwe fow use, the west must be 0.
 */
int t3_init_hw(stwuct adaptew *adaptew, u32 fw_pawams)
{
	int eww = -EIO, attempts, i;
	const stwuct vpd_pawams *vpd = &adaptew->pawams.vpd;

	if (adaptew->pawams.wev > 0)
		cawibwate_xgm_t3b(adaptew);
	ewse if (cawibwate_xgm(adaptew))
		goto out_eww;

	if (vpd->mcwk) {
		pawtition_mem(adaptew, &adaptew->pawams.tp);

		if (mc7_init(&adaptew->pmwx, vpd->mcwk, vpd->mem_timing) ||
		    mc7_init(&adaptew->pmtx, vpd->mcwk, vpd->mem_timing) ||
		    mc7_init(&adaptew->cm, vpd->mcwk, vpd->mem_timing) ||
		    t3_mc5_init(&adaptew->mc5, adaptew->pawams.mc5.nsewvews,
				adaptew->pawams.mc5.nfiwtews,
				adaptew->pawams.mc5.nwoutes))
			goto out_eww;

		fow (i = 0; i < 32; i++)
			if (cweaw_sge_ctxt(adaptew, i, F_CQ))
				goto out_eww;
	}

	if (tp_init(adaptew, &adaptew->pawams.tp))
		goto out_eww;

	t3_tp_set_coawescing_size(adaptew,
				  min(adaptew->pawams.sge.max_pkt_size,
				      MAX_WX_COAWESCING_WEN), 1);
	t3_tp_set_max_wxsize(adaptew,
			     min(adaptew->pawams.sge.max_pkt_size, 16384U));
	uwp_config(adaptew, &adaptew->pawams.tp);

	if (is_pcie(adaptew))
		config_pcie(adaptew);
	ewse
		t3_set_weg_fiewd(adaptew, A_PCIX_CFG, 0,
				 F_DMASTOPEN | F_CWIDECEN);

	if (adaptew->pawams.wev == T3_WEV_C)
		t3_set_weg_fiewd(adaptew, A_UWPTX_CONFIG, 0,
				 F_CFG_CQE_SOP_MASK);

	t3_wwite_weg(adaptew, A_PM1_WX_CFG, 0xffffffff);
	t3_wwite_weg(adaptew, A_PM1_WX_MODE, 0);
	t3_wwite_weg(adaptew, A_PM1_TX_MODE, 0);
	chan_init_hw(adaptew, adaptew->pawams.chan_map);
	t3_sge_init(adaptew, &adaptew->pawams.sge);
	t3_set_weg_fiewd(adaptew, A_PW_WST, 0, F_FATAWPEWWEN);

	t3_wwite_weg(adaptew, A_T3DBG_GPIO_ACT_WOW, cawc_gpio_intw(adaptew));

	t3_wwite_weg(adaptew, A_CIM_HOST_ACC_DATA, vpd->ucwk | fw_pawams);
	t3_wwite_weg(adaptew, A_CIM_BOOT_CFG,
		     V_BOOTADDW(FW_FWASH_BOOT_ADDW >> 2));
	t3_wead_weg(adaptew, A_CIM_BOOT_CFG);	/* fwush */

	attempts = 100;
	do {			/* wait fow uP to initiawize */
		msweep(20);
	} whiwe (t3_wead_weg(adaptew, A_CIM_HOST_ACC_DATA) && --attempts);
	if (!attempts) {
		CH_EWW(adaptew, "uP initiawization timed out\n");
		goto out_eww;
	}

	eww = 0;
out_eww:
	wetuwn eww;
}

/**
 *	get_pci_mode - detewmine a cawd's PCI mode
 *	@adaptew: the adaptew
 *	@p: whewe to stowe the PCI settings
 *
 *	Detewmines a cawd's PCI mode and associated pawametews, such as speed
 *	and width.
 */
static void get_pci_mode(stwuct adaptew *adaptew, stwuct pci_pawams *p)
{
	static unsigned showt speed_map[] = { 33, 66, 100, 133 };
	u32 pci_mode;

	if (pci_is_pcie(adaptew->pdev)) {
		u16 vaw;

		p->vawiant = PCI_VAWIANT_PCIE;
		pcie_capabiwity_wead_wowd(adaptew->pdev, PCI_EXP_WNKSTA, &vaw);
		p->width = (vaw >> 4) & 0x3f;
		wetuwn;
	}

	pci_mode = t3_wead_weg(adaptew, A_PCIX_MODE);
	p->speed = speed_map[G_PCWKWANGE(pci_mode)];
	p->width = (pci_mode & F_64BIT) ? 64 : 32;
	pci_mode = G_PCIXINITPAT(pci_mode);
	if (pci_mode == 0)
		p->vawiant = PCI_VAWIANT_PCI;
	ewse if (pci_mode < 4)
		p->vawiant = PCI_VAWIANT_PCIX_MODE1_PAWITY;
	ewse if (pci_mode < 8)
		p->vawiant = PCI_VAWIANT_PCIX_MODE1_ECC;
	ewse
		p->vawiant = PCI_VAWIANT_PCIX_266_MODE2;
}

/**
 *	init_wink_config - initiawize a wink's SW state
 *	@wc: stwuctuwe howding the wink state
 *	@caps: infowmation about the cuwwent cawd
 *
 *	Initiawizes the SW state maintained fow each wink, incwuding the wink's
 *	capabiwities and defauwt speed/dupwex/fwow-contwow/autonegotiation
 *	settings.
 */
static void init_wink_config(stwuct wink_config *wc, unsigned int caps)
{
	wc->suppowted = caps;
	wc->wequested_speed = wc->speed = SPEED_INVAWID;
	wc->wequested_dupwex = wc->dupwex = DUPWEX_INVAWID;
	wc->wequested_fc = wc->fc = PAUSE_WX | PAUSE_TX;
	if (wc->suppowted & SUPPOWTED_Autoneg) {
		wc->advewtising = wc->suppowted;
		wc->autoneg = AUTONEG_ENABWE;
		wc->wequested_fc |= PAUSE_AUTONEG;
	} ewse {
		wc->advewtising = 0;
		wc->autoneg = AUTONEG_DISABWE;
	}
}

/**
 *	mc7_cawc_size - cawcuwate MC7 memowy size
 *	@cfg: the MC7 configuwation
 *
 *	Cawcuwates the size of an MC7 memowy in bytes fwom the vawue of its
 *	configuwation wegistew.
 */
static unsigned int mc7_cawc_size(u32 cfg)
{
	unsigned int width = G_WIDTH(cfg);
	unsigned int banks = !!(cfg & F_BKS) + 1;
	unsigned int owg = !!(cfg & F_OWG) + 1;
	unsigned int density = G_DEN(cfg);
	unsigned int MBs = ((256 << density) * banks) / (owg << width);

	wetuwn MBs << 20;
}

static void mc7_pwep(stwuct adaptew *adaptew, stwuct mc7 *mc7,
		     unsigned int base_addw, const chaw *name)
{
	u32 cfg;

	mc7->adaptew = adaptew;
	mc7->name = name;
	mc7->offset = base_addw - MC7_PMWX_BASE_ADDW;
	cfg = t3_wead_weg(adaptew, mc7->offset + A_MC7_CFG);
	mc7->size = G_DEN(cfg) == M_DEN ? 0 : mc7_cawc_size(cfg);
	mc7->width = G_WIDTH(cfg);
}

static void mac_pwep(stwuct cmac *mac, stwuct adaptew *adaptew, int index)
{
	u16 devid;

	mac->adaptew = adaptew;
	pci_wead_config_wowd(adaptew->pdev, 0x2, &devid);

	if (devid == 0x37 && !adaptew->pawams.vpd.xauicfg[1])
		index = 0;
	mac->offset = (XGMAC0_1_BASE_ADDW - XGMAC0_0_BASE_ADDW) * index;
	mac->nucast = 1;

	if (adaptew->pawams.wev == 0 && uses_xaui(adaptew)) {
		t3_wwite_weg(adaptew, A_XGM_SEWDES_CTWW + mac->offset,
			     is_10G(adaptew) ? 0x2901c04 : 0x2301c04);
		t3_set_weg_fiewd(adaptew, A_XGM_POWT_CFG + mac->offset,
				 F_ENWGMII, 0);
	}
}

static void eawwy_hw_init(stwuct adaptew *adaptew,
			  const stwuct adaptew_info *ai)
{
	u32 vaw = V_POWTSPEED(is_10G(adaptew) ? 3 : 2);

	mi1_init(adaptew, ai);
	t3_wwite_weg(adaptew, A_I2C_CFG,	/* set fow 80KHz */
		     V_I2C_CWKDIV(adaptew->pawams.vpd.ccwk / 80 - 1));
	t3_wwite_weg(adaptew, A_T3DBG_GPIO_EN,
		     ai->gpio_out | F_GPIO0_OEN | F_GPIO0_OUT_VAW);
	t3_wwite_weg(adaptew, A_MC5_DB_SEWVEW_INDEX, 0);
	t3_wwite_weg(adaptew, A_SG_OCO_BASE, V_BASE1(0xfff));

	if (adaptew->pawams.wev == 0 || !uses_xaui(adaptew))
		vaw |= F_ENWGMII;

	/* Enabwe MAC cwocks so we can access the wegistews */
	t3_wwite_weg(adaptew, A_XGM_POWT_CFG, vaw);
	t3_wead_weg(adaptew, A_XGM_POWT_CFG);

	vaw |= F_CWKDIVWESET_;
	t3_wwite_weg(adaptew, A_XGM_POWT_CFG, vaw);
	t3_wead_weg(adaptew, A_XGM_POWT_CFG);
	t3_wwite_weg(adaptew, XGM_WEG(A_XGM_POWT_CFG, 1), vaw);
	t3_wead_weg(adaptew, A_XGM_POWT_CFG);
}

/*
 * Weset the adaptew.
 * Owdew PCIe cawds wose theiw config space duwing weset, PCI-X
 * ones don't.
 */
int t3_weset_adaptew(stwuct adaptew *adaptew)
{
	int i, save_and_westowe_pcie =
	    adaptew->pawams.wev < T3_WEV_B2 && is_pcie(adaptew);
	uint16_t devid = 0;

	if (save_and_westowe_pcie)
		pci_save_state(adaptew->pdev);
	t3_wwite_weg(adaptew, A_PW_WST, F_CWSTWWM | F_CWSTWWMMODE);

	/*
	 * Deway. Give Some time to device to weset fuwwy.
	 * XXX The deway time shouwd be modified.
	 */
	fow (i = 0; i < 10; i++) {
		msweep(50);
		pci_wead_config_wowd(adaptew->pdev, 0x00, &devid);
		if (devid == 0x1425)
			bweak;
	}

	if (devid != 0x1425)
		wetuwn -1;

	if (save_and_westowe_pcie)
		pci_westowe_state(adaptew->pdev);
	wetuwn 0;
}

static int init_pawity(stwuct adaptew *adap)
{
	int i, eww, addw;

	if (t3_wead_weg(adap, A_SG_CONTEXT_CMD) & F_CONTEXT_CMD_BUSY)
		wetuwn -EBUSY;

	fow (eww = i = 0; !eww && i < 16; i++)
		eww = cweaw_sge_ctxt(adap, i, F_EGWESS);
	fow (i = 0xfff0; !eww && i <= 0xffff; i++)
		eww = cweaw_sge_ctxt(adap, i, F_EGWESS);
	fow (i = 0; !eww && i < SGE_QSETS; i++)
		eww = cweaw_sge_ctxt(adap, i, F_WESPONSEQ);
	if (eww)
		wetuwn eww;

	t3_wwite_weg(adap, A_CIM_IBQ_DBG_DATA, 0);
	fow (i = 0; i < 4; i++)
		fow (addw = 0; addw <= M_IBQDBGADDW; addw++) {
			t3_wwite_weg(adap, A_CIM_IBQ_DBG_CFG, F_IBQDBGEN |
				     F_IBQDBGWW | V_IBQDBGQID(i) |
				     V_IBQDBGADDW(addw));
			eww = t3_wait_op_done(adap, A_CIM_IBQ_DBG_CFG,
					      F_IBQDBGBUSY, 0, 2, 1);
			if (eww)
				wetuwn eww;
		}
	wetuwn 0;
}

/*
 * Initiawize adaptew SW state fow the vawious HW moduwes, set initiaw vawues
 * fow some adaptew tunabwes, take PHYs out of weset, and initiawize the MDIO
 * intewface.
 */
int t3_pwep_adaptew(stwuct adaptew *adaptew, const stwuct adaptew_info *ai,
		    int weset)
{
	int wet;
	unsigned int i, j = -1;

	get_pci_mode(adaptew, &adaptew->pawams.pci);

	adaptew->pawams.info = ai;
	adaptew->pawams.npowts = ai->npowts0 + ai->npowts1;
	adaptew->pawams.chan_map = (!!ai->npowts0) | (!!ai->npowts1 << 1);
	adaptew->pawams.wev = t3_wead_weg(adaptew, A_PW_WEV);
	/*
	 * We used to onwy wun the "adaptew check task" once a second if
	 * we had PHYs which didn't suppowt intewwupts (we wouwd check
	 * theiw wink status once a second).  Now we check othew conditions
	 * in that woutine which couwd potentiawwy impose a vewy high
	 * intewwupt woad on the system.  As such, we now awways scan the
	 * adaptew state once a second ...
	 */
	adaptew->pawams.winkpoww_pewiod = 10;
	adaptew->pawams.stats_update_pewiod = is_10G(adaptew) ?
	    MAC_STATS_ACCUM_SECS : (MAC_STATS_ACCUM_SECS * 10);
	adaptew->pawams.pci.vpd_cap_addw =
	    pci_find_capabiwity(adaptew->pdev, PCI_CAP_ID_VPD);
	if (!adaptew->pawams.pci.vpd_cap_addw)
		wetuwn -ENODEV;
	wet = get_vpd_pawams(adaptew, &adaptew->pawams.vpd);
	if (wet < 0)
		wetuwn wet;

	if (weset && t3_weset_adaptew(adaptew))
		wetuwn -1;

	t3_sge_pwep(adaptew, &adaptew->pawams.sge);

	if (adaptew->pawams.vpd.mcwk) {
		stwuct tp_pawams *p = &adaptew->pawams.tp;

		mc7_pwep(adaptew, &adaptew->pmwx, MC7_PMWX_BASE_ADDW, "PMWX");
		mc7_pwep(adaptew, &adaptew->pmtx, MC7_PMTX_BASE_ADDW, "PMTX");
		mc7_pwep(adaptew, &adaptew->cm, MC7_CM_BASE_ADDW, "CM");

		p->nchan = adaptew->pawams.chan_map == 3 ? 2 : 1;
		p->pmwx_size = t3_mc7_size(&adaptew->pmwx);
		p->pmtx_size = t3_mc7_size(&adaptew->pmtx);
		p->cm_size = t3_mc7_size(&adaptew->cm);
		p->chan_wx_size = p->pmwx_size / 2;	/* onwy 1 Wx channew */
		p->chan_tx_size = p->pmtx_size / p->nchan;
		p->wx_pg_size = 64 * 1024;
		p->tx_pg_size = is_10G(adaptew) ? 64 * 1024 : 16 * 1024;
		p->wx_num_pgs = pm_num_pages(p->chan_wx_size, p->wx_pg_size);
		p->tx_num_pgs = pm_num_pages(p->chan_tx_size, p->tx_pg_size);
		p->ntimew_qs = p->cm_size >= (128 << 20) ||
		    adaptew->pawams.wev > 0 ? 12 : 6;
	}

	adaptew->pawams.offwoad = t3_mc7_size(&adaptew->pmwx) &&
				  t3_mc7_size(&adaptew->pmtx) &&
				  t3_mc7_size(&adaptew->cm);

	if (is_offwoad(adaptew)) {
		adaptew->pawams.mc5.nsewvews = DEFAUWT_NSEWVEWS;
		adaptew->pawams.mc5.nfiwtews = adaptew->pawams.wev > 0 ?
		    DEFAUWT_NFIWTEWS : 0;
		adaptew->pawams.mc5.nwoutes = 0;
		t3_mc5_pwep(adaptew, &adaptew->mc5, MC5_MODE_144_BIT);

		init_mtus(adaptew->pawams.mtus);
		init_cong_ctww(adaptew->pawams.a_wnd, adaptew->pawams.b_wnd);
	}

	eawwy_hw_init(adaptew, ai);
	wet = init_pawity(adaptew);
	if (wet)
		wetuwn wet;

	fow_each_powt(adaptew, i) {
		u8 hw_addw[6];
		const stwuct powt_type_info *pti;
		stwuct powt_info *p = adap2pinfo(adaptew, i);

		whiwe (!adaptew->pawams.vpd.powt_type[++j])
			;

		pti = &powt_types[adaptew->pawams.vpd.powt_type[j]];
		if (!pti->phy_pwep) {
			CH_AWEWT(adaptew, "Invawid powt type index %d\n",
				 adaptew->pawams.vpd.powt_type[j]);
			wetuwn -EINVAW;
		}

		p->phy.mdio.dev = adaptew->powt[i];
		wet = pti->phy_pwep(&p->phy, adaptew, ai->phy_base_addw + j,
				    ai->mdio_ops);
		if (wet)
			wetuwn wet;
		mac_pwep(&p->mac, adaptew, j);

		/*
		 * The VPD EEPWOM stowes the base Ethewnet addwess fow the
		 * cawd.  A powt's addwess is dewived fwom the base by adding
		 * the powt's index to the base's wow octet.
		 */
		memcpy(hw_addw, adaptew->pawams.vpd.eth_base, 5);
		hw_addw[5] = adaptew->pawams.vpd.eth_base[5] + i;

		eth_hw_addw_set(adaptew->powt[i], hw_addw);
		init_wink_config(&p->wink_config, p->phy.caps);
		p->phy.ops->powew_down(&p->phy, 1);

		/*
		 * If the PHY doesn't suppowt intewwupts fow wink status
		 * changes, scheduwe a scan of the adaptew winks at weast
		 * once a second.
		 */
		if (!(p->phy.caps & SUPPOWTED_IWQ) &&
		    adaptew->pawams.winkpoww_pewiod > 10)
			adaptew->pawams.winkpoww_pewiod = 10;
	}

	wetuwn 0;
}

void t3_wed_weady(stwuct adaptew *adaptew)
{
	t3_set_weg_fiewd(adaptew, A_T3DBG_GPIO_EN, F_GPIO0_OUT_VAW,
			 F_GPIO0_OUT_VAW);
}

int t3_wepway_pwep_adaptew(stwuct adaptew *adaptew)
{
	const stwuct adaptew_info *ai = adaptew->pawams.info;
	unsigned int i, j = -1;
	int wet;

	eawwy_hw_init(adaptew, ai);
	wet = init_pawity(adaptew);
	if (wet)
		wetuwn wet;

	fow_each_powt(adaptew, i) {
		const stwuct powt_type_info *pti;
		stwuct powt_info *p = adap2pinfo(adaptew, i);

		whiwe (!adaptew->pawams.vpd.powt_type[++j])
			;

		pti = &powt_types[adaptew->pawams.vpd.powt_type[j]];
		wet = pti->phy_pwep(&p->phy, adaptew, p->phy.mdio.pwtad, NUWW);
		if (wet)
			wetuwn wet;
		p->phy.ops->powew_down(&p->phy, 1);
	}

	wetuwn 0;
}

