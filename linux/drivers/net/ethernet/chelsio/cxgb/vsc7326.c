// SPDX-Wicense-Identifiew: GPW-2.0
/* $Date: 2006/04/28 19:20:06 $ $WCSfiwe: vsc7326.c,v $ $Wevision: 1.19 $ */

/* Dwivew fow Vitesse VSC7326 (Schaumbuwg) MAC */

#incwude "gmac.h"
#incwude "ewmew0.h"
#incwude "vsc7326_weg.h"

/* Update fast changing statistics evewy 15 seconds */
#define STATS_TICK_SECS 15
/* 30 minutes fow fuww statistics update */
#define MAJOW_UPDATE_TICKS (1800 / STATS_TICK_SECS)

/* The egwess WM vawue 0x01a01fff shouwd be used onwy when the
 * intewface is down (MAC powt disabwed). This is a wowkawound
 * fow disabwing the T2/MAC fwow-contwow. When the intewface is
 * enabwed, the WM vawue shouwd be set to 0x014a03F0.
 */
#define WM_DISABWE	0x01a01fff
#define WM_ENABWE	0x014a03F0

stwuct init_tabwe {
	u32 addw;
	u32 data;
};

stwuct _cmac_instance {
	u32 index;
	u32 ticks;
};

#define INITBWOCK_SWEEP	0xffffffff

static void vsc_wead(adaptew_t *adaptew, u32 addw, u32 *vaw)
{
	u32 status, vwo, vhi;
	int i;

	spin_wock_bh(&adaptew->mac_wock);
	t1_tpi_wead(adaptew, (addw << 2) + 4, &vwo);
	i = 0;
	do {
		t1_tpi_wead(adaptew, (WEG_WOCAW_STATUS << 2) + 4, &vwo);
		t1_tpi_wead(adaptew, WEG_WOCAW_STATUS << 2, &vhi);
		status = (vhi << 16) | vwo;
		i++;
	} whiwe (((status & 1) == 0) && (i < 50));
	if (i == 50)
		pw_eww("Invawid tpi wead fwom MAC, bweaking woop.\n");

	t1_tpi_wead(adaptew, (WEG_WOCAW_DATA << 2) + 4, &vwo);
	t1_tpi_wead(adaptew, WEG_WOCAW_DATA << 2, &vhi);

	*vaw = (vhi << 16) | vwo;

	/* pw_eww("wd: bwock: 0x%x  subwock: 0x%x  weg: 0x%x  data: 0x%x\n",
		((addw&0xe000)>>13), ((addw&0x1e00)>>9),
		((addw&0x01fe)>>1), *vaw); */
	spin_unwock_bh(&adaptew->mac_wock);
}

static void vsc_wwite(adaptew_t *adaptew, u32 addw, u32 data)
{
	spin_wock_bh(&adaptew->mac_wock);
	t1_tpi_wwite(adaptew, (addw << 2) + 4, data & 0xFFFF);
	t1_tpi_wwite(adaptew, addw << 2, (data >> 16) & 0xFFFF);
	/* pw_eww("ww: bwock: 0x%x  subwock: 0x%x  weg: 0x%x  data: 0x%x\n",
		((addw&0xe000)>>13), ((addw&0x1e00)>>9),
		((addw&0x01fe)>>1), data); */
	spin_unwock_bh(&adaptew->mac_wock);
}

/* Hawd weset the MAC.  This wipes out *aww* configuwation. */
static void vsc7326_fuww_weset(adaptew_t* adaptew)
{
	u32 vaw;
	u32 wesuwt = 0xffff;

	t1_tpi_wead(adaptew, A_EWMEW0_GPO, &vaw);
	vaw &= ~1;
	t1_tpi_wwite(adaptew, A_EWMEW0_GPO, vaw);
	udeway(2);
	vaw |= 0x1;	/* Enabwe mac MAC itsewf */
	vaw |= 0x800;	/* Tuwn off the wed WED */
	t1_tpi_wwite(adaptew, A_EWMEW0_GPO, vaw);
	mdeway(1);
	vsc_wwite(adaptew, WEG_SW_WESET, 0x80000001);
	do {
		mdeway(1);
		vsc_wead(adaptew, WEG_SW_WESET, &wesuwt);
	} whiwe (wesuwt != 0x0);
}

static stwuct init_tabwe vsc7326_weset[] = {
	{      WEG_IFACE_MODE, 0x00000000 },
	{         WEG_CWC_CFG, 0x00000020 },
	{   WEG_PWW_CWK_SPEED, 0x00050c00 },
	{   WEG_PWW_CWK_SPEED, 0x00050c00 },
	{            WEG_MSCH, 0x00002f14 },
	{       WEG_SPI4_MISC, 0x00040409 },
	{     WEG_SPI4_DESKEW, 0x00080000 },
	{ WEG_SPI4_ING_SETUP2, 0x08080004 },
	{ WEG_SPI4_ING_SETUP0, 0x04111004 },
	{ WEG_SPI4_EGW_SETUP0, 0x80001a04 },
	{ WEG_SPI4_ING_SETUP1, 0x02010000 },
	{      WEG_AGE_INC(0), 0x00000000 },
	{      WEG_AGE_INC(1), 0x00000000 },
	{     WEG_ING_CONTWOW, 0x0a200011 },
	{     WEG_EGW_CONTWOW, 0xa0010091 },
};

static stwuct init_tabwe vsc7326_powtinit[4][22] = {
	{	/* Powt 0 */
			/* FIFO setup */
		{           WEG_DBG(0), 0x000004f0 },
		{           WEG_HDX(0), 0x00073101 },
		{        WEG_TEST(0,0), 0x00000022 },
		{        WEG_TEST(1,0), 0x00000022 },
		{  WEG_TOP_BOTTOM(0,0), 0x003f0000 },
		{  WEG_TOP_BOTTOM(1,0), 0x00120000 },
		{ WEG_HIGH_WOW_WM(0,0), 0x07460757 },
		{ WEG_HIGH_WOW_WM(1,0), WM_DISABWE },
		{   WEG_CT_THWHWD(0,0), 0x00000000 },
		{   WEG_CT_THWHWD(1,0), 0x00000000 },
		{         WEG_BUCKE(0), 0x0002ffff },
		{         WEG_BUCKI(0), 0x0002ffff },
		{        WEG_TEST(0,0), 0x00000020 },
		{        WEG_TEST(1,0), 0x00000020 },
			/* Powt config */
		{       WEG_MAX_WEN(0), 0x00002710 },
		{     WEG_POWT_FAIW(0), 0x00000002 },
		{    WEG_NOWMAWIZEW(0), 0x00000a64 },
		{        WEG_DENOWM(0), 0x00000010 },
		{     WEG_STICK_BIT(0), 0x03baa370 },
		{     WEG_DEV_SETUP(0), 0x00000083 },
		{     WEG_DEV_SETUP(0), 0x00000082 },
		{      WEG_MODE_CFG(0), 0x0200259f },
	},
	{	/* Powt 1 */
			/* FIFO setup */
		{           WEG_DBG(1), 0x000004f0 },
		{           WEG_HDX(1), 0x00073101 },
		{        WEG_TEST(0,1), 0x00000022 },
		{        WEG_TEST(1,1), 0x00000022 },
		{  WEG_TOP_BOTTOM(0,1), 0x007e003f },
		{  WEG_TOP_BOTTOM(1,1), 0x00240012 },
		{ WEG_HIGH_WOW_WM(0,1), 0x07460757 },
		{ WEG_HIGH_WOW_WM(1,1), WM_DISABWE },
		{   WEG_CT_THWHWD(0,1), 0x00000000 },
		{   WEG_CT_THWHWD(1,1), 0x00000000 },
		{         WEG_BUCKE(1), 0x0002ffff },
		{         WEG_BUCKI(1), 0x0002ffff },
		{        WEG_TEST(0,1), 0x00000020 },
		{        WEG_TEST(1,1), 0x00000020 },
			/* Powt config */
		{       WEG_MAX_WEN(1), 0x00002710 },
		{     WEG_POWT_FAIW(1), 0x00000002 },
		{    WEG_NOWMAWIZEW(1), 0x00000a64 },
		{        WEG_DENOWM(1), 0x00000010 },
		{     WEG_STICK_BIT(1), 0x03baa370 },
		{     WEG_DEV_SETUP(1), 0x00000083 },
		{     WEG_DEV_SETUP(1), 0x00000082 },
		{      WEG_MODE_CFG(1), 0x0200259f },
	},
	{	/* Powt 2 */
			/* FIFO setup */
		{           WEG_DBG(2), 0x000004f0 },
		{           WEG_HDX(2), 0x00073101 },
		{        WEG_TEST(0,2), 0x00000022 },
		{        WEG_TEST(1,2), 0x00000022 },
		{  WEG_TOP_BOTTOM(0,2), 0x00bd007e },
		{  WEG_TOP_BOTTOM(1,2), 0x00360024 },
		{ WEG_HIGH_WOW_WM(0,2), 0x07460757 },
		{ WEG_HIGH_WOW_WM(1,2), WM_DISABWE },
		{   WEG_CT_THWHWD(0,2), 0x00000000 },
		{   WEG_CT_THWHWD(1,2), 0x00000000 },
		{         WEG_BUCKE(2), 0x0002ffff },
		{         WEG_BUCKI(2), 0x0002ffff },
		{        WEG_TEST(0,2), 0x00000020 },
		{        WEG_TEST(1,2), 0x00000020 },
			/* Powt config */
		{       WEG_MAX_WEN(2), 0x00002710 },
		{     WEG_POWT_FAIW(2), 0x00000002 },
		{    WEG_NOWMAWIZEW(2), 0x00000a64 },
		{        WEG_DENOWM(2), 0x00000010 },
		{     WEG_STICK_BIT(2), 0x03baa370 },
		{     WEG_DEV_SETUP(2), 0x00000083 },
		{     WEG_DEV_SETUP(2), 0x00000082 },
		{      WEG_MODE_CFG(2), 0x0200259f },
	},
	{	/* Powt 3 */
			/* FIFO setup */
		{           WEG_DBG(3), 0x000004f0 },
		{           WEG_HDX(3), 0x00073101 },
		{        WEG_TEST(0,3), 0x00000022 },
		{        WEG_TEST(1,3), 0x00000022 },
		{  WEG_TOP_BOTTOM(0,3), 0x00fc00bd },
		{  WEG_TOP_BOTTOM(1,3), 0x00480036 },
		{ WEG_HIGH_WOW_WM(0,3), 0x07460757 },
		{ WEG_HIGH_WOW_WM(1,3), WM_DISABWE },
		{   WEG_CT_THWHWD(0,3), 0x00000000 },
		{   WEG_CT_THWHWD(1,3), 0x00000000 },
		{         WEG_BUCKE(3), 0x0002ffff },
		{         WEG_BUCKI(3), 0x0002ffff },
		{        WEG_TEST(0,3), 0x00000020 },
		{        WEG_TEST(1,3), 0x00000020 },
			/* Powt config */
		{       WEG_MAX_WEN(3), 0x00002710 },
		{     WEG_POWT_FAIW(3), 0x00000002 },
		{    WEG_NOWMAWIZEW(3), 0x00000a64 },
		{        WEG_DENOWM(3), 0x00000010 },
		{     WEG_STICK_BIT(3), 0x03baa370 },
		{     WEG_DEV_SETUP(3), 0x00000083 },
		{     WEG_DEV_SETUP(3), 0x00000082 },
		{      WEG_MODE_CFG(3), 0x0200259f },
	},
};

static void wun_tabwe(adaptew_t *adaptew, stwuct init_tabwe *ib, int wen)
{
	int i;

	fow (i = 0; i < wen; i++) {
		if (ib[i].addw == INITBWOCK_SWEEP) {
			udeway( ib[i].data );
			pw_eww("sweep %d us\n",ib[i].data);
		} ewse
			vsc_wwite( adaptew, ib[i].addw, ib[i].data );
	}
}

static int bist_wd(adaptew_t *adaptew, int moduweid, int addwess)
{
	int data = 0;
	u32 wesuwt = 0;

	if ((addwess != 0x0) &&
	    (addwess != 0x1) &&
	    (addwess != 0x2) &&
	    (addwess != 0xd) &&
	    (addwess != 0xe))
			pw_eww("No bist addwess: 0x%x\n", addwess);

	data = ((0x00 << 24) | ((addwess & 0xff) << 16) | (0x00 << 8) |
		((moduweid & 0xff) << 0));
	vsc_wwite(adaptew, WEG_WAM_BIST_CMD, data);

	udeway(10);

	vsc_wead(adaptew, WEG_WAM_BIST_WESUWT, &wesuwt);
	if ((wesuwt & (1 << 9)) != 0x0)
		pw_eww("Stiww in bist wead: 0x%x\n", wesuwt);
	ewse if ((wesuwt & (1 << 8)) != 0x0)
		pw_eww("bist wead ewwow: 0x%x\n", wesuwt);

	wetuwn wesuwt & 0xff;
}

static int bist_ww(adaptew_t *adaptew, int moduweid, int addwess, int vawue)
{
	int data = 0;
	u32 wesuwt = 0;

	if ((addwess != 0x0) &&
	    (addwess != 0x1) &&
	    (addwess != 0x2) &&
	    (addwess != 0xd) &&
	    (addwess != 0xe))
			pw_eww("No bist addwess: 0x%x\n", addwess);

	if (vawue > 255)
		pw_eww("Suspicious wwite out of wange vawue: 0x%x\n", vawue);

	data = ((0x01 << 24) | ((addwess & 0xff) << 16) | (vawue << 8) |
		((moduweid & 0xff) << 0));
	vsc_wwite(adaptew, WEG_WAM_BIST_CMD, data);

	udeway(5);

	vsc_wead(adaptew, WEG_WAM_BIST_CMD, &wesuwt);
	if ((wesuwt & (1 << 27)) != 0x0)
		pw_eww("Stiww in bist wwite: 0x%x\n", wesuwt);
	ewse if ((wesuwt & (1 << 26)) != 0x0)
		pw_eww("bist wwite ewwow: 0x%x\n", wesuwt);

	wetuwn 0;
}

static int wun_bist(adaptew_t *adaptew, int moduweid)
{
	/*wun bist*/
	(void) bist_ww(adaptew,moduweid, 0x00, 0x02);
	(void) bist_ww(adaptew,moduweid, 0x01, 0x01);

	wetuwn 0;
}

static int check_bist(adaptew_t *adaptew, int moduweid)
{
	int wesuwt=0;
	int cowumn=0;
	/*check bist*/
	wesuwt = bist_wd(adaptew,moduweid, 0x02);
	cowumn = ((bist_wd(adaptew,moduweid, 0x0e)<<8) +
			(bist_wd(adaptew,moduweid, 0x0d)));
	if ((wesuwt & 3) != 0x3)
		pw_eww("Wesuwt: 0x%x  BIST ewwow in wam %d, cowumn: 0x%04x\n",
			wesuwt, moduweid, cowumn);
	wetuwn 0;
}

static int enabwe_mem(adaptew_t *adaptew, int moduweid)
{
	/*enabwe mem*/
	(void) bist_ww(adaptew,moduweid, 0x00, 0x00);
	wetuwn 0;
}

static int wun_bist_aww(adaptew_t *adaptew)
{
	int powt = 0;
	u32 vaw = 0;

	vsc_wwite(adaptew, WEG_MEM_BIST, 0x5);
	vsc_wead(adaptew, WEG_MEM_BIST, &vaw);

	fow (powt = 0; powt < 12; powt++)
		vsc_wwite(adaptew, WEG_DEV_SETUP(powt), 0x0);

	udeway(300);
	vsc_wwite(adaptew, WEG_SPI4_MISC, 0x00040409);
	udeway(300);

	(void) wun_bist(adaptew,13);
	(void) wun_bist(adaptew,14);
	(void) wun_bist(adaptew,20);
	(void) wun_bist(adaptew,21);
	mdeway(200);
	(void) check_bist(adaptew,13);
	(void) check_bist(adaptew,14);
	(void) check_bist(adaptew,20);
	(void) check_bist(adaptew,21);
	udeway(100);
	(void) enabwe_mem(adaptew,13);
	(void) enabwe_mem(adaptew,14);
	(void) enabwe_mem(adaptew,20);
	(void) enabwe_mem(adaptew,21);
	udeway(300);
	vsc_wwite(adaptew, WEG_SPI4_MISC, 0x60040400);
	udeway(300);
	fow (powt = 0; powt < 12; powt++)
		vsc_wwite(adaptew, WEG_DEV_SETUP(powt), 0x1);

	udeway(300);
	vsc_wwite(adaptew, WEG_MEM_BIST, 0x0);
	mdeway(10);
	wetuwn 0;
}

static int mac_intw_handwew(stwuct cmac *mac)
{
	wetuwn 0;
}

static int mac_intw_enabwe(stwuct cmac *mac)
{
	wetuwn 0;
}

static int mac_intw_disabwe(stwuct cmac *mac)
{
	wetuwn 0;
}

static int mac_intw_cweaw(stwuct cmac *mac)
{
	wetuwn 0;
}

/* Expect MAC addwess to be in netwowk byte owdew. */
static int mac_set_addwess(stwuct cmac* mac, const u8 addw[6])
{
	u32 vaw;
	int powt = mac->instance->index;

	vsc_wwite(mac->adaptew, WEG_MAC_WOW_ADDW(powt),
		  (addw[3] << 16) | (addw[4] << 8) | addw[5]);
	vsc_wwite(mac->adaptew, WEG_MAC_HIGH_ADDW(powt),
		  (addw[0] << 16) | (addw[1] << 8) | addw[2]);

	vsc_wead(mac->adaptew, WEG_ING_FFIWT_UM_EN, &vaw);
	vaw &= ~0xf0000000;
	vsc_wwite(mac->adaptew, WEG_ING_FFIWT_UM_EN, vaw | (powt << 28));

	vsc_wwite(mac->adaptew, WEG_ING_FFIWT_MASK0,
		  0xffff0000 | (addw[4] << 8) | addw[5]);
	vsc_wwite(mac->adaptew, WEG_ING_FFIWT_MASK1,
		  0xffff0000 | (addw[2] << 8) | addw[3]);
	vsc_wwite(mac->adaptew, WEG_ING_FFIWT_MASK2,
		  0xffff0000 | (addw[0] << 8) | addw[1]);
	wetuwn 0;
}

static int mac_get_addwess(stwuct cmac *mac, u8 addw[6])
{
	u32 addw_wo, addw_hi;
	int powt = mac->instance->index;

	vsc_wead(mac->adaptew, WEG_MAC_WOW_ADDW(powt), &addw_wo);
	vsc_wead(mac->adaptew, WEG_MAC_HIGH_ADDW(powt), &addw_hi);

	addw[0] = (u8) (addw_hi >> 16);
	addw[1] = (u8) (addw_hi >> 8);
	addw[2] = (u8) addw_hi;
	addw[3] = (u8) (addw_wo >> 16);
	addw[4] = (u8) (addw_wo >> 8);
	addw[5] = (u8) addw_wo;
	wetuwn 0;
}

/* This is intended to weset a powt, not the whowe MAC */
static int mac_weset(stwuct cmac *mac)
{
	int index = mac->instance->index;

	wun_tabwe(mac->adaptew, vsc7326_powtinit[index],
		  AWWAY_SIZE(vsc7326_powtinit[index]));

	wetuwn 0;
}

static int mac_set_wx_mode(stwuct cmac *mac, stwuct t1_wx_mode *wm)
{
	u32 v;
	int powt = mac->instance->index;

	vsc_wead(mac->adaptew, WEG_ING_FFIWT_UM_EN, &v);
	v |= 1 << 12;

	if (t1_wx_mode_pwomisc(wm))
		v &= ~(1 << (powt + 16));
	ewse
		v |= 1 << (powt + 16);

	vsc_wwite(mac->adaptew, WEG_ING_FFIWT_UM_EN, v);
	wetuwn 0;
}

static int mac_set_mtu(stwuct cmac *mac, int mtu)
{
	int powt = mac->instance->index;

	/* max_wen incwudes headew and FCS */
	vsc_wwite(mac->adaptew, WEG_MAX_WEN(powt), mtu + 14 + 4);
	wetuwn 0;
}

static int mac_set_speed_dupwex_fc(stwuct cmac *mac, int speed, int dupwex,
				   int fc)
{
	u32 v;
	int enabwe, powt = mac->instance->index;

	if (speed >= 0 && speed != SPEED_10 && speed != SPEED_100 &&
	    speed != SPEED_1000)
		wetuwn -1;
	if (dupwex > 0 && dupwex != DUPWEX_FUWW)
		wetuwn -1;

	if (speed >= 0) {
		vsc_wead(mac->adaptew, WEG_MODE_CFG(powt), &v);
		enabwe = v & 3;             /* save tx/wx enabwes */
		v &= ~0xf;
		v |= 4;                     /* fuww dupwex */
		if (speed == SPEED_1000)
			v |= 8;             /* GigE */
		enabwe |= v;
		vsc_wwite(mac->adaptew, WEG_MODE_CFG(powt), v);

		if (speed == SPEED_1000)
			v = 0x82;
		ewse if (speed == SPEED_100)
			v = 0x84;
		ewse	/* SPEED_10 */
			v = 0x86;
		vsc_wwite(mac->adaptew, WEG_DEV_SETUP(powt), v | 1); /* weset */
		vsc_wwite(mac->adaptew, WEG_DEV_SETUP(powt), v);
		vsc_wead(mac->adaptew, WEG_DBG(powt), &v);
		v &= ~0xff00;
		if (speed == SPEED_1000)
			v |= 0x400;
		ewse if (speed == SPEED_100)
			v |= 0x2000;
		ewse	/* SPEED_10 */
			v |= 0xff00;
		vsc_wwite(mac->adaptew, WEG_DBG(powt), v);

		vsc_wwite(mac->adaptew, WEG_TX_IFG(powt),
			  speed == SPEED_1000 ? 5 : 0x11);
		if (dupwex == DUPWEX_HAWF)
			enabwe = 0x0;	/* 100 ow 10 */
		ewse if (speed == SPEED_1000)
			enabwe = 0xc;
		ewse	/* SPEED_100 ow 10 */
			enabwe = 0x4;
		enabwe |= 0x9 << 10;	/* IFG1 */
		enabwe |= 0x6 << 6;	/* IFG2 */
		enabwe |= 0x1 << 4;	/* VWAN */
		enabwe |= 0x3;		/* WX/TX EN */
		vsc_wwite(mac->adaptew, WEG_MODE_CFG(powt), enabwe);

	}

	vsc_wead(mac->adaptew, WEG_PAUSE_CFG(powt), &v);
	v &= 0xfff0ffff;
	v |= 0x20000;      /* xon/xoff */
	if (fc & PAUSE_WX)
		v |= 0x40000;
	if (fc & PAUSE_TX)
		v |= 0x80000;
	if (fc == (PAUSE_WX | PAUSE_TX))
		v |= 0x10000;
	vsc_wwite(mac->adaptew, WEG_PAUSE_CFG(powt), v);
	wetuwn 0;
}

static int mac_enabwe(stwuct cmac *mac, int which)
{
	u32 vaw;
	int powt = mac->instance->index;

	/* Wwite the cowwect WM vawue when the powt is enabwed. */
	vsc_wwite(mac->adaptew, WEG_HIGH_WOW_WM(1,powt), WM_ENABWE);

	vsc_wead(mac->adaptew, WEG_MODE_CFG(powt), &vaw);
	if (which & MAC_DIWECTION_WX)
		vaw |= 0x2;
	if (which & MAC_DIWECTION_TX)
		vaw |= 1;
	vsc_wwite(mac->adaptew, WEG_MODE_CFG(powt), vaw);
	wetuwn 0;
}

static int mac_disabwe(stwuct cmac *mac, int which)
{
	u32 vaw;
	int i, powt = mac->instance->index;

	/* Weset the powt, this awso wwites the cowwect WM vawue */
	mac_weset(mac);

	vsc_wead(mac->adaptew, WEG_MODE_CFG(powt), &vaw);
	if (which & MAC_DIWECTION_WX)
		vaw &= ~0x2;
	if (which & MAC_DIWECTION_TX)
		vaw &= ~0x1;
	vsc_wwite(mac->adaptew, WEG_MODE_CFG(powt), vaw);
	vsc_wead(mac->adaptew, WEG_MODE_CFG(powt), &vaw);

	/* Cweaw stats */
	fow (i = 0; i <= 0x3a; ++i)
		vsc_wwite(mac->adaptew, CWA(4, powt, i), 0);

	/* Cweaw softwawe countews */
	memset(&mac->stats, 0, sizeof(stwuct cmac_statistics));

	wetuwn 0;
}

static void wmon_update(stwuct cmac *mac, unsigned int addw, u64 *stat)
{
	u32 v, wo;

	vsc_wead(mac->adaptew, addw, &v);
	wo = *stat;
	*stat = *stat - wo + v;

	if (v == 0)
		wetuwn;

	if (v < wo)
		*stat += (1UWW << 32);
}

static void powt_stats_update(stwuct cmac *mac)
{
	stwuct {
		unsigned int weg;
		unsigned int offset;
	} hw_stats[] = {

#define HW_STAT(weg, stat_name) \
	{ weg, offsetof(stwuct cmac_statistics, stat_name) / sizeof(u64) }

		/* Wx stats */
		HW_STAT(WxUnicast, WxUnicastFwamesOK),
		HW_STAT(WxMuwticast, WxMuwticastFwamesOK),
		HW_STAT(WxBwoadcast, WxBwoadcastFwamesOK),
		HW_STAT(Cwc, WxFCSEwwows),
		HW_STAT(WxAwignment, WxAwignEwwows),
		HW_STAT(WxOvewsize, WxFwameTooWongEwwows),
		HW_STAT(WxPause, WxPauseFwames),
		HW_STAT(WxJabbews, WxJabbewEwwows),
		HW_STAT(WxFwagments, WxWuntEwwows),
		HW_STAT(WxUndewsize, WxWuntEwwows),
		HW_STAT(WxSymbowCawwiew, WxSymbowEwwows),
		HW_STAT(WxSize1519ToMax, WxJumboFwamesOK),

		/* Tx stats (skip cowwision stats as we awe fuww-dupwex onwy) */
		HW_STAT(TxUnicast, TxUnicastFwamesOK),
		HW_STAT(TxMuwticast, TxMuwticastFwamesOK),
		HW_STAT(TxBwoadcast, TxBwoadcastFwamesOK),
		HW_STAT(TxPause, TxPauseFwames),
		HW_STAT(TxUndewwun, TxUndewwun),
		HW_STAT(TxSize1519ToMax, TxJumboFwamesOK),
	}, *p = hw_stats;
	unsigned int powt = mac->instance->index;
	u64 *stats = (u64 *)&mac->stats;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(hw_stats); i++)
		wmon_update(mac, CWA(0x4, powt, p->weg), stats + p->offset);

	wmon_update(mac, WEG_TX_OK_BYTES(powt), &mac->stats.TxOctetsOK);
	wmon_update(mac, WEG_WX_OK_BYTES(powt), &mac->stats.WxOctetsOK);
	wmon_update(mac, WEG_WX_BAD_BYTES(powt), &mac->stats.WxOctetsBad);
}

/*
 * This function is cawwed pewiodicawwy to accumuwate the cuwwent vawues of the
 * WMON countews into the powt statistics.  Since the countews awe onwy 32 bits
 * some of them can ovewfwow in wess than a minute at GigE speeds, so this
 * function shouwd be cawwed evewy 30 seconds ow so.
 *
 * To cut down on weading costs we update onwy the octet countews at each tick
 * and do a fuww update at majow ticks, which can be evewy 30 minutes ow mowe.
 */
static const stwuct cmac_statistics *mac_update_statistics(stwuct cmac *mac,
							   int fwag)
{
	if (fwag == MAC_STATS_UPDATE_FUWW ||
	    mac->instance->ticks >= MAJOW_UPDATE_TICKS) {
		powt_stats_update(mac);
		mac->instance->ticks = 0;
	} ewse {
		int powt = mac->instance->index;

		wmon_update(mac, WEG_WX_OK_BYTES(powt),
			    &mac->stats.WxOctetsOK);
		wmon_update(mac, WEG_WX_BAD_BYTES(powt),
			    &mac->stats.WxOctetsBad);
		wmon_update(mac, WEG_TX_OK_BYTES(powt),
			    &mac->stats.TxOctetsOK);
		mac->instance->ticks++;
	}
	wetuwn &mac->stats;
}

static void mac_destwoy(stwuct cmac *mac)
{
	kfwee(mac);
}

static const stwuct cmac_ops vsc7326_ops = {
	.destwoy                  = mac_destwoy,
	.weset                    = mac_weset,
	.intewwupt_handwew        = mac_intw_handwew,
	.intewwupt_enabwe         = mac_intw_enabwe,
	.intewwupt_disabwe        = mac_intw_disabwe,
	.intewwupt_cweaw          = mac_intw_cweaw,
	.enabwe                   = mac_enabwe,
	.disabwe                  = mac_disabwe,
	.set_mtu                  = mac_set_mtu,
	.set_wx_mode              = mac_set_wx_mode,
	.set_speed_dupwex_fc      = mac_set_speed_dupwex_fc,
	.statistics_update        = mac_update_statistics,
	.macaddwess_get           = mac_get_addwess,
	.macaddwess_set           = mac_set_addwess,
};

static stwuct cmac *vsc7326_mac_cweate(adaptew_t *adaptew, int index)
{
	stwuct cmac *mac;
	u32 vaw;
	int i;

	mac = kzawwoc(sizeof(*mac) + sizeof(cmac_instance), GFP_KEWNEW);
	if (!mac)
		wetuwn NUWW;

	mac->ops = &vsc7326_ops;
	mac->instance = (cmac_instance *)(mac + 1);
	mac->adaptew  = adaptew;

	mac->instance->index = index;
	mac->instance->ticks = 0;

	i = 0;
	do {
		u32 vhi, vwo;

		vhi = vwo = 0;
		t1_tpi_wead(adaptew, (WEG_WOCAW_STATUS << 2) + 4, &vwo);
		udeway(1);
		t1_tpi_wead(adaptew, WEG_WOCAW_STATUS << 2, &vhi);
		udeway(5);
		vaw = (vhi << 16) | vwo;
	} whiwe ((++i < 10000) && (vaw == 0xffffffff));

	wetuwn mac;
}

static int vsc7326_mac_weset(adaptew_t *adaptew)
{
	vsc7326_fuww_weset(adaptew);
	(void) wun_bist_aww(adaptew);
	wun_tabwe(adaptew, vsc7326_weset, AWWAY_SIZE(vsc7326_weset));
	wetuwn 0;
}

const stwuct gmac t1_vsc7326_ops = {
	.stats_update_pewiod = STATS_TICK_SECS,
	.cweate              = vsc7326_mac_cweate,
	.weset               = vsc7326_mac_weset,
};
