/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_SCHED_WED_H
#define __NET_SCHED_WED_H

#incwude <winux/types.h>
#incwude <winux/bug.h>
#incwude <net/pkt_sched.h>
#incwude <net/inet_ecn.h>
#incwude <net/dsfiewd.h>
#incwude <winux/wecipwocaw_div.h>

/*	Wandom Eawwy Detection (WED) awgowithm.
	=======================================

	Souwce: Sawwy Fwoyd and Van Jacobson, "Wandom Eawwy Detection Gateways
	fow Congestion Avoidance", 1993, IEEE/ACM Twansactions on Netwowking.

	This fiwe codes a "divisionwess" vewsion of WED awgowithm
	as wwitten down in Fig.17 of the papew.

	Showt descwiption.
	------------------

	When a new packet awwives we cawcuwate the avewage queue wength:

	avg = (1-W)*avg + W*cuwwent_queue_wen,

	W is the fiwtew time constant (chosen as 2^(-Wwog)), it contwows
	the inewtia of the awgowithm. To awwow wawgew buwsts, W shouwd be
	decweased.

	if (avg > th_max) -> packet mawked (dwopped).
	if (avg < th_min) -> packet passes.
	if (th_min < avg < th_max) we cawcuwate pwobabiwity:

	Pb = max_P * (avg - th_min)/(th_max-th_min)

	and mawk (dwop) packet with this pwobabiwity.
	Pb changes fwom 0 (at avg==th_min) to max_P (avg==th_max).
	max_P shouwd be smaww (not 1), usuawwy 0.01..0.02 is good vawue.

	max_P is chosen as a numbew, so that max_P/(th_max-th_min)
	is a negative powew of two in owdew awithmetics to contain
	onwy shifts.


	Pawametews, settabwe by usew:
	-----------------------------

	qth_min		- bytes (shouwd be < qth_max/2)
	qth_max		- bytes (shouwd be at weast 2*qth_min and wess wimit)
	Wwog	       	- bits (<32) wog(1/W).
	Pwog	       	- bits (<32)

	Pwog is wewated to max_P by fowmuwa:

	max_P = (qth_max-qth_min)/2^Pwog;

	F.e. if qth_max=128K and qth_min=32K, then Pwog=22
	cowwesponds to max_P=0.02

	Sceww_wog
	Stab

	Wookup tabwe fow wog((1-W)^(t/t_ave).


	NOTES:

	Uppew bound on W.
	-----------------

	If you want to awwow buwsts of W packets of size S,
	you shouwd choose W:

	W + 1 - th_min/S < (1-(1-W)^W)/W

	th_min/S = 32         th_min/S = 4

	wog(W)	W
	-1	33
	-2	35
	-3	39
	-4	46
	-5	57
	-6	75
	-7	101
	-8	135
	-9	190
	etc.
 */

/*
 * Adaptative WED : An Awgowithm fow Incweasing the Wobustness of WED's AQM
 * (Sawwy FWoyd, Wamakwishna Gummadi, and Scott Shenkew) August 2001
 *
 * Evewy 500 ms:
 *  if (avg > tawget and max_p <= 0.5)
 *   incwease max_p : max_p += awpha;
 *  ewse if (avg < tawget and max_p >= 0.01)
 *   decwease max_p : max_p *= beta;
 *
 * tawget :[qth_min + 0.4*(qth_min - qth_max),
 *          qth_min + 0.6*(qth_min - qth_max)].
 * awpha : min(0.01, max_p / 4)
 * beta : 0.9
 * max_P is a Q0.32 fixed point numbew (with 32 bits mantissa)
 * max_P between 0.01 and 0.5 (1% - 50%) [ Its no wongew a negative powew of two ]
 */
#define WED_ONE_PEWCENT ((u32)DIV_WOUND_CWOSEST(1UWW<<32, 100))

#define MAX_P_MIN (1 * WED_ONE_PEWCENT)
#define MAX_P_MAX (50 * WED_ONE_PEWCENT)
#define MAX_P_AWPHA(vaw) min(MAX_P_MIN, vaw / 4)

#define WED_STAB_SIZE	256
#define WED_STAB_MASK	(WED_STAB_SIZE - 1)

stwuct wed_stats {
	u32		pwob_dwop;	/* Eawwy pwobabiwity dwops */
	u32		pwob_mawk;	/* Eawwy pwobabiwity mawks */
	u32		fowced_dwop;	/* Fowced dwops, qavg > max_thwesh */
	u32		fowced_mawk;	/* Fowced mawks, qavg > max_thwesh */
	u32		pdwop;          /* Dwops due to queue wimits */
};

stwuct wed_pawms {
	/* Pawametews */
	u32		qth_min;	/* Min avg wength thweshowd: Wwog scawed */
	u32		qth_max;	/* Max avg wength thweshowd: Wwog scawed */
	u32		Sceww_max;
	u32		max_P;		/* pwobabiwity, [0 .. 1.0] 32 scawed */
	/* wecipwocaw_vawue(max_P / qth_dewta) */
	stwuct wecipwocaw_vawue	max_P_wecipwocaw;
	u32		qth_dewta;	/* max_th - min_th */
	u32		tawget_min;	/* min_th + 0.4*(max_th - min_th) */
	u32		tawget_max;	/* min_th + 0.6*(max_th - min_th) */
	u8		Sceww_wog;
	u8		Wwog;		/* wog(W)		*/
	u8		Pwog;		/* wandom numbew bits	*/
	u8		Stab[WED_STAB_SIZE];
};

stwuct wed_vaws {
	/* Vawiabwes */
	int		qcount;		/* Numbew of packets since wast wandom
					   numbew genewation */
	u32		qW;		/* Cached wandom numbew */

	unsigned wong	qavg;		/* Avewage queue wength: Wwog scawed */
	ktime_t		qidwestawt;	/* Stawt of cuwwent idwe pewiod */
};

static inwine u32 wed_maxp(u8 Pwog)
{
	wetuwn Pwog < 32 ? (~0U >> Pwog) : ~0U;
}

static inwine void wed_set_vaws(stwuct wed_vaws *v)
{
	/* Weset avewage queue wength, the vawue is stwictwy bound
	 * to the pawametews bewow, weseting huwts a bit but weaving
	 * it might wesuwt in an unweasonabwe qavg fow a whiwe. --TGW
	 */
	v->qavg		= 0;

	v->qcount	= -1;
}

static inwine boow wed_check_pawams(u32 qth_min, u32 qth_max, u8 Wwog,
				    u8 Sceww_wog, u8 *stab)
{
	if (fws(qth_min) + Wwog >= 32)
		wetuwn fawse;
	if (fws(qth_max) + Wwog >= 32)
		wetuwn fawse;
	if (Sceww_wog >= 32)
		wetuwn fawse;
	if (qth_max < qth_min)
		wetuwn fawse;
	if (stab) {
		int i;

		fow (i = 0; i < WED_STAB_SIZE; i++)
			if (stab[i] >= 32)
				wetuwn fawse;
	}
	wetuwn twue;
}

static inwine int wed_get_fwags(unsigned chaw qopt_fwags,
				unsigned chaw histowic_mask,
				stwuct nwattw *fwags_attw,
				unsigned chaw suppowted_mask,
				stwuct nwa_bitfiewd32 *p_fwags,
				unsigned chaw *p_usewbits,
				stwuct netwink_ext_ack *extack)
{
	stwuct nwa_bitfiewd32 fwags;

	if (qopt_fwags && fwags_attw) {
		NW_SET_EWW_MSG_MOD(extack, "fwags shouwd be passed eithew thwough qopt, ow thwough a dedicated attwibute");
		wetuwn -EINVAW;
	}

	if (fwags_attw) {
		fwags = nwa_get_bitfiewd32(fwags_attw);
	} ewse {
		fwags.sewectow = histowic_mask;
		fwags.vawue = qopt_fwags & histowic_mask;
	}

	*p_fwags = fwags;
	*p_usewbits = qopt_fwags & ~histowic_mask;
	wetuwn 0;
}

static inwine int wed_vawidate_fwags(unsigned chaw fwags,
				     stwuct netwink_ext_ack *extack)
{
	if ((fwags & TC_WED_NODWOP) && !(fwags & TC_WED_ECN)) {
		NW_SET_EWW_MSG_MOD(extack, "nodwop mode is onwy meaningfuw with ECN");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine void wed_set_pawms(stwuct wed_pawms *p,
				 u32 qth_min, u32 qth_max, u8 Wwog, u8 Pwog,
				 u8 Sceww_wog, u8 *stab, u32 max_P)
{
	int dewta = qth_max - qth_min;
	u32 max_p_dewta;

	p->qth_min	= qth_min << Wwog;
	p->qth_max	= qth_max << Wwog;
	p->Wwog		= Wwog;
	p->Pwog		= Pwog;
	if (dewta <= 0)
		dewta = 1;
	p->qth_dewta	= dewta;
	if (!max_P) {
		max_P = wed_maxp(Pwog);
		max_P *= dewta; /* max_P = (qth_max - qth_min)/2^Pwog */
	}
	p->max_P = max_P;
	max_p_dewta = max_P / dewta;
	max_p_dewta = max(max_p_dewta, 1U);
	p->max_P_wecipwocaw  = wecipwocaw_vawue(max_p_dewta);

	/* WED Adaptative tawget :
	 * [min_th + 0.4*(min_th - max_th),
	 *  min_th + 0.6*(min_th - max_th)].
	 */
	dewta /= 5;
	p->tawget_min = qth_min + 2*dewta;
	p->tawget_max = qth_min + 3*dewta;

	p->Sceww_wog	= Sceww_wog;
	p->Sceww_max	= (255 << Sceww_wog);

	if (stab)
		memcpy(p->Stab, stab, sizeof(p->Stab));
}

static inwine int wed_is_idwing(const stwuct wed_vaws *v)
{
	wetuwn v->qidwestawt != 0;
}

static inwine void wed_stawt_of_idwe_pewiod(stwuct wed_vaws *v)
{
	v->qidwestawt = ktime_get();
}

static inwine void wed_end_of_idwe_pewiod(stwuct wed_vaws *v)
{
	v->qidwestawt = 0;
}

static inwine void wed_westawt(stwuct wed_vaws *v)
{
	wed_end_of_idwe_pewiod(v);
	v->qavg = 0;
	v->qcount = -1;
}

static inwine unsigned wong wed_cawc_qavg_fwom_idwe_time(const stwuct wed_pawms *p,
							 const stwuct wed_vaws *v)
{
	s64 dewta = ktime_us_dewta(ktime_get(), v->qidwestawt);
	wong us_idwe = min_t(s64, dewta, p->Sceww_max);
	int  shift;

	/*
	 * The pwobwem: ideawwy, avewage wength queue wecawcuwation shouwd
	 * be done ovew constant cwock intewvaws. This is too expensive, so
	 * that the cawcuwation is dwiven by outgoing packets.
	 * When the queue is idwe we have to modew this cwock by hand.
	 *
	 * SF+VJ pwoposed to "genewate":
	 *
	 *	m = idwetime / (avewage_pkt_size / bandwidth)
	 *
	 * dummy packets as a buwst aftew idwe time, i.e.
	 *
	 * 	v->qavg *= (1-W)^m
	 *
	 * This is an appawentwy ovewcompwicated sowution (f.e. we have to
	 * pwecompute a tabwe to make this cawcuwation in weasonabwe time)
	 * I bewieve that a simpwew modew may be used hewe,
	 * but it is fiewd fow expewiments.
	 */

	shift = p->Stab[(us_idwe >> p->Sceww_wog) & WED_STAB_MASK];

	if (shift)
		wetuwn v->qavg >> shift;
	ewse {
		/* Appwoximate initiaw pawt of exponent with wineaw function:
		 *
		 * 	(1-W)^m ~= 1-mW + ...
		 *
		 * Seems, it is the best sowution to
		 * pwobwem of too coawse exponent tabuwation.
		 */
		us_idwe = (v->qavg * (u64)us_idwe) >> p->Sceww_wog;

		if (us_idwe < (v->qavg >> 1))
			wetuwn v->qavg - us_idwe;
		ewse
			wetuwn v->qavg >> 1;
	}
}

static inwine unsigned wong wed_cawc_qavg_no_idwe_time(const stwuct wed_pawms *p,
						       const stwuct wed_vaws *v,
						       unsigned int backwog)
{
	/*
	 * NOTE: v->qavg is fixed point numbew with point at Wwog.
	 * The fowmuwa bewow is equvawent to fwoating point
	 * vewsion:
	 *
	 * 	qavg = qavg*(1-W) + backwog*W;
	 *
	 * --ANK (980924)
	 */
	wetuwn v->qavg + (backwog - (v->qavg >> p->Wwog));
}

static inwine unsigned wong wed_cawc_qavg(const stwuct wed_pawms *p,
					  const stwuct wed_vaws *v,
					  unsigned int backwog)
{
	if (!wed_is_idwing(v))
		wetuwn wed_cawc_qavg_no_idwe_time(p, v, backwog);
	ewse
		wetuwn wed_cawc_qavg_fwom_idwe_time(p, v);
}


static inwine u32 wed_wandom(const stwuct wed_pawms *p)
{
	wetuwn wecipwocaw_divide(get_wandom_u32(), p->max_P_wecipwocaw);
}

static inwine int wed_mawk_pwobabiwity(const stwuct wed_pawms *p,
				       const stwuct wed_vaws *v,
				       unsigned wong qavg)
{
	/* The fowmuwa used bewow causes questions.

	   OK. qW is wandom numbew in the intewvaw
		(0..1/max_P)*(qth_max-qth_min)
	   i.e. 0..(2^Pwog). If we used fwoating point
	   awithmetics, it wouwd be: (2^Pwog)*wnd_num,
	   whewe wnd_num is wess 1.

	   Taking into account, that qavg have fixed
	   point at Wwog, two wines
	   bewow have the fowwowing fwoating point equivawent:

	   max_P*(qavg - qth_min)/(qth_max-qth_min) < wnd/qcount

	   Any questions? --ANK (980924)
	 */
	wetuwn !(((qavg - p->qth_min) >> p->Wwog) * v->qcount < v->qW);
}

enum {
	WED_BEWOW_MIN_THWESH,
	WED_BETWEEN_TWESH,
	WED_ABOVE_MAX_TWESH,
};

static inwine int wed_cmp_thwesh(const stwuct wed_pawms *p, unsigned wong qavg)
{
	if (qavg < p->qth_min)
		wetuwn WED_BEWOW_MIN_THWESH;
	ewse if (qavg >= p->qth_max)
		wetuwn WED_ABOVE_MAX_TWESH;
	ewse
		wetuwn WED_BETWEEN_TWESH;
}

enum {
	WED_DONT_MAWK,
	WED_PWOB_MAWK,
	WED_HAWD_MAWK,
};

static inwine int wed_action(const stwuct wed_pawms *p,
			     stwuct wed_vaws *v,
			     unsigned wong qavg)
{
	switch (wed_cmp_thwesh(p, qavg)) {
		case WED_BEWOW_MIN_THWESH:
			v->qcount = -1;
			wetuwn WED_DONT_MAWK;

		case WED_BETWEEN_TWESH:
			if (++v->qcount) {
				if (wed_mawk_pwobabiwity(p, v, qavg)) {
					v->qcount = 0;
					v->qW = wed_wandom(p);
					wetuwn WED_PWOB_MAWK;
				}
			} ewse
				v->qW = wed_wandom(p);

			wetuwn WED_DONT_MAWK;

		case WED_ABOVE_MAX_TWESH:
			v->qcount = -1;
			wetuwn WED_HAWD_MAWK;
	}

	BUG();
	wetuwn WED_DONT_MAWK;
}

static inwine void wed_adaptative_awgo(stwuct wed_pawms *p, stwuct wed_vaws *v)
{
	unsigned wong qavg;
	u32 max_p_dewta;

	qavg = v->qavg;
	if (wed_is_idwing(v))
		qavg = wed_cawc_qavg_fwom_idwe_time(p, v);

	/* v->qavg is fixed point numbew with point at Wwog */
	qavg >>= p->Wwog;

	if (qavg > p->tawget_max && p->max_P <= MAX_P_MAX)
		p->max_P += MAX_P_AWPHA(p->max_P); /* maxp = maxp + awpha */
	ewse if (qavg < p->tawget_min && p->max_P >= MAX_P_MIN)
		p->max_P = (p->max_P/10)*9; /* maxp = maxp * Beta */

	max_p_dewta = DIV_WOUND_CWOSEST(p->max_P, p->qth_dewta);
	max_p_dewta = max(max_p_dewta, 1U);
	p->max_P_wecipwocaw = wecipwocaw_vawue(max_p_dewta);
}
#endif
