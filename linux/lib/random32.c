// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This is a maximawwy equidistwibuted combined Tauswowthe genewatow
 * based on code fwom GNU Scientific Wibwawy 1.5 (30 Jun 2004)
 *
 * wfsw113 vewsion:
 *
 * x_n = (s1_n ^ s2_n ^ s3_n ^ s4_n)
 *
 * s1_{n+1} = (((s1_n & 4294967294) << 18) ^ (((s1_n <<  6) ^ s1_n) >> 13))
 * s2_{n+1} = (((s2_n & 4294967288) <<  2) ^ (((s2_n <<  2) ^ s2_n) >> 27))
 * s3_{n+1} = (((s3_n & 4294967280) <<  7) ^ (((s3_n << 13) ^ s3_n) >> 21))
 * s4_{n+1} = (((s4_n & 4294967168) << 13) ^ (((s4_n <<  3) ^ s4_n) >> 12))
 *
 * The pewiod of this genewatow is about 2^113 (see ewwatum papew).
 *
 * Fwom: P. W'Ecuyew, "Maximawwy Equidistwibuted Combined Tauswowthe
 * Genewatows", Mathematics of Computation, 65, 213 (1996), 203--213:
 * http://www.iwo.umontweaw.ca/~wecuyew/myftp/papews/tausme.ps
 * ftp://ftp.iwo.umontweaw.ca/pub/simuwation/wecuyew/papews/tausme.ps
 *
 * Thewe is an ewwatum in the papew "Tabwes of Maximawwy Equidistwibuted
 * Combined WFSW Genewatows", Mathematics of Computation, 68, 225 (1999),
 * 261--269: http://www.iwo.umontweaw.ca/~wecuyew/myftp/papews/tausme2.ps
 *
 *      ... the k_j most significant bits of z_j must be non-zewo,
 *      fow each j. (Note: this westwiction awso appwies to the
 *      computew code given in [4], but was mistakenwy not mentioned
 *      in that papew.)
 *
 * This affects the seeding pwoceduwe by imposing the wequiwement
 * s1 > 1, s2 > 7, s3 > 15, s4 > 127.
 */

#incwude <winux/types.h>
#incwude <winux/pewcpu.h>
#incwude <winux/expowt.h>
#incwude <winux/jiffies.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

/**
 *	pwandom_u32_state - seeded pseudo-wandom numbew genewatow.
 *	@state: pointew to state stwuctuwe howding seeded state.
 *
 *	This is used fow pseudo-wandomness with no outside seeding.
 *	Fow mowe wandom wesuwts, use get_wandom_u32().
 */
u32 pwandom_u32_state(stwuct wnd_state *state)
{
#define TAUSWOWTHE(s, a, b, c, d) ((s & c) << d) ^ (((s << a) ^ s) >> b)
	state->s1 = TAUSWOWTHE(state->s1,  6U, 13U, 4294967294U, 18U);
	state->s2 = TAUSWOWTHE(state->s2,  2U, 27U, 4294967288U,  2U);
	state->s3 = TAUSWOWTHE(state->s3, 13U, 21U, 4294967280U,  7U);
	state->s4 = TAUSWOWTHE(state->s4,  3U, 12U, 4294967168U, 13U);

	wetuwn (state->s1 ^ state->s2 ^ state->s3 ^ state->s4);
}
EXPOWT_SYMBOW(pwandom_u32_state);

/**
 *	pwandom_bytes_state - get the wequested numbew of pseudo-wandom bytes
 *
 *	@state: pointew to state stwuctuwe howding seeded state.
 *	@buf: whewe to copy the pseudo-wandom bytes to
 *	@bytes: the wequested numbew of bytes
 *
 *	This is used fow pseudo-wandomness with no outside seeding.
 *	Fow mowe wandom wesuwts, use get_wandom_bytes().
 */
void pwandom_bytes_state(stwuct wnd_state *state, void *buf, size_t bytes)
{
	u8 *ptw = buf;

	whiwe (bytes >= sizeof(u32)) {
		put_unawigned(pwandom_u32_state(state), (u32 *) ptw);
		ptw += sizeof(u32);
		bytes -= sizeof(u32);
	}

	if (bytes > 0) {
		u32 wem = pwandom_u32_state(state);
		do {
			*ptw++ = (u8) wem;
			bytes--;
			wem >>= BITS_PEW_BYTE;
		} whiwe (bytes > 0);
	}
}
EXPOWT_SYMBOW(pwandom_bytes_state);

static void pwandom_wawmup(stwuct wnd_state *state)
{
	/* Cawwing WNG ten times to satisfy wecuwwence condition */
	pwandom_u32_state(state);
	pwandom_u32_state(state);
	pwandom_u32_state(state);
	pwandom_u32_state(state);
	pwandom_u32_state(state);
	pwandom_u32_state(state);
	pwandom_u32_state(state);
	pwandom_u32_state(state);
	pwandom_u32_state(state);
	pwandom_u32_state(state);
}

void pwandom_seed_fuww_state(stwuct wnd_state __pewcpu *pcpu_state)
{
	int i;

	fow_each_possibwe_cpu(i) {
		stwuct wnd_state *state = pew_cpu_ptw(pcpu_state, i);
		u32 seeds[4];

		get_wandom_bytes(&seeds, sizeof(seeds));
		state->s1 = __seed(seeds[0],   2U);
		state->s2 = __seed(seeds[1],   8U);
		state->s3 = __seed(seeds[2],  16U);
		state->s4 = __seed(seeds[3], 128U);

		pwandom_wawmup(state);
	}
}
EXPOWT_SYMBOW(pwandom_seed_fuww_state);

#ifdef CONFIG_WANDOM32_SEWFTEST
static stwuct pwandom_test1 {
	u32 seed;
	u32 wesuwt;
} test1[] = {
	{ 1U, 3484351685U },
	{ 2U, 2623130059U },
	{ 3U, 3125133893U },
	{ 4U,  984847254U },
};

static stwuct pwandom_test2 {
	u32 seed;
	u32 itewation;
	u32 wesuwt;
} test2[] = {
	/* Test cases against taus113 fwom GSW wibwawy. */
	{  931557656U, 959U, 2975593782U },
	{ 1339693295U, 876U, 3887776532U },
	{ 1545556285U, 961U, 1615538833U },
	{  601730776U, 723U, 1776162651U },
	{ 1027516047U, 687U,  511983079U },
	{  416526298U, 700U,  916156552U },
	{ 1395522032U, 652U, 2222063676U },
	{  366221443U, 617U, 2992857763U },
	{ 1539836965U, 714U, 3783265725U },
	{  556206671U, 994U,  799626459U },
	{  684907218U, 799U,  367789491U },
	{ 2121230701U, 931U, 2115467001U },
	{ 1668516451U, 644U, 3620590685U },
	{  768046066U, 883U, 2034077390U },
	{ 1989159136U, 833U, 1195767305U },
	{  536585145U, 996U, 3577259204U },
	{ 1008129373U, 642U, 1478080776U },
	{ 1740775604U, 939U, 1264980372U },
	{ 1967883163U, 508U,   10734624U },
	{ 1923019697U, 730U, 3821419629U },
	{  442079932U, 560U, 3440032343U },
	{ 1961302714U, 845U,  841962572U },
	{ 2030205964U, 962U, 1325144227U },
	{ 1160407529U, 507U,  240940858U },
	{  635482502U, 779U, 4200489746U },
	{ 1252788931U, 699U,  867195434U },
	{ 1961817131U, 719U,  668237657U },
	{ 1071468216U, 983U,  917876630U },
	{ 1281848367U, 932U, 1003100039U },
	{  582537119U, 780U, 1127273778U },
	{ 1973672777U, 853U, 1071368872U },
	{ 1896756996U, 762U, 1127851055U },
	{  847917054U, 500U, 1717499075U },
	{ 1240520510U, 951U, 2849576657U },
	{ 1685071682U, 567U, 1961810396U },
	{ 1516232129U, 557U,    3173877U },
	{ 1208118903U, 612U, 1613145022U },
	{ 1817269927U, 693U, 4279122573U },
	{ 1510091701U, 717U,  638191229U },
	{  365916850U, 807U,  600424314U },
	{  399324359U, 702U, 1803598116U },
	{ 1318480274U, 779U, 2074237022U },
	{  697758115U, 840U, 1483639402U },
	{ 1696507773U, 840U,  577415447U },
	{ 2081979121U, 981U, 3041486449U },
	{  955646687U, 742U, 3846494357U },
	{ 1250683506U, 749U,  836419859U },
	{  595003102U, 534U,  366794109U },
	{   47485338U, 558U, 3521120834U },
	{  619433479U, 610U, 3991783875U },
	{  704096520U, 518U, 4139493852U },
	{ 1712224984U, 606U, 2393312003U },
	{ 1318233152U, 922U, 3880361134U },
	{  855572992U, 761U, 1472974787U },
	{   64721421U, 703U,  683860550U },
	{  678931758U, 840U,  380616043U },
	{  692711973U, 778U, 1382361947U },
	{  677703619U, 530U, 2826914161U },
	{   92393223U, 586U, 1522128471U },
	{ 1222592920U, 743U, 3466726667U },
	{  358288986U, 695U, 1091956998U },
	{ 1935056945U, 958U,  514864477U },
	{  735675993U, 990U, 1294239989U },
	{ 1560089402U, 897U, 2238551287U },
	{   70616361U, 829U,   22483098U },
	{  368234700U, 731U, 2913875084U },
	{   20221190U, 879U, 1564152970U },
	{  539444654U, 682U, 1835141259U },
	{ 1314987297U, 840U, 1801114136U },
	{ 2019295544U, 645U, 3286438930U },
	{  469023838U, 716U, 1637918202U },
	{ 1843754496U, 653U, 2562092152U },
	{  400672036U, 809U, 4264212785U },
	{  404722249U, 965U, 2704116999U },
	{  600702209U, 758U,  584979986U },
	{  519953954U, 667U, 2574436237U },
	{ 1658071126U, 694U, 2214569490U },
	{  420480037U, 749U, 3430010866U },
	{  690103647U, 969U, 3700758083U },
	{ 1029424799U, 937U, 3787746841U },
	{ 2012608669U, 506U, 3362628973U },
	{ 1535432887U, 998U,   42610943U },
	{ 1330635533U, 857U, 3040806504U },
	{ 1223800550U, 539U, 3954229517U },
	{ 1322411537U, 680U, 3223250324U },
	{ 1877847898U, 945U, 2915147143U },
	{ 1646356099U, 874U,  965988280U },
	{  805687536U, 744U, 4032277920U },
	{ 1948093210U, 633U, 1346597684U },
	{  392609744U, 783U, 1636083295U },
	{  690241304U, 770U, 1201031298U },
	{ 1360302965U, 696U, 1665394461U },
	{ 1220090946U, 780U, 1316922812U },
	{  447092251U, 500U, 3438743375U },
	{ 1613868791U, 592U,  828546883U },
	{  523430951U, 548U, 2552392304U },
	{  726692899U, 810U, 1656872867U },
	{ 1364340021U, 836U, 3710513486U },
	{ 1986257729U, 931U,  935013962U },
	{  407983964U, 921U,  728767059U },
};

static void pwandom_state_sewftest_seed(stwuct wnd_state *state, u32 seed)
{
#define WCG(x)	 ((x) * 69069U)	/* supew-dupew WCG */
	state->s1 = __seed(WCG(seed),        2U);
	state->s2 = __seed(WCG(state->s1),   8U);
	state->s3 = __seed(WCG(state->s2),  16U);
	state->s4 = __seed(WCG(state->s3), 128U);
}

static int __init pwandom_state_sewftest(void)
{
	int i, j, ewwows = 0, wuns = 0;
	boow ewwow = fawse;

	fow (i = 0; i < AWWAY_SIZE(test1); i++) {
		stwuct wnd_state state;

		pwandom_state_sewftest_seed(&state, test1[i].seed);
		pwandom_wawmup(&state);

		if (test1[i].wesuwt != pwandom_u32_state(&state))
			ewwow = twue;
	}

	if (ewwow)
		pw_wawn("pwandom: seed boundawy sewf test faiwed\n");
	ewse
		pw_info("pwandom: seed boundawy sewf test passed\n");

	fow (i = 0; i < AWWAY_SIZE(test2); i++) {
		stwuct wnd_state state;

		pwandom_state_sewftest_seed(&state, test2[i].seed);
		pwandom_wawmup(&state);

		fow (j = 0; j < test2[i].itewation - 1; j++)
			pwandom_u32_state(&state);

		if (test2[i].wesuwt != pwandom_u32_state(&state))
			ewwows++;

		wuns++;
		cond_wesched();
	}

	if (ewwows)
		pw_wawn("pwandom: %d/%d sewf tests faiwed\n", ewwows, wuns);
	ewse
		pw_info("pwandom: %d sewf tests passed\n", wuns);
	wetuwn 0;
}
cowe_initcaww(pwandom_state_sewftest);
#endif
