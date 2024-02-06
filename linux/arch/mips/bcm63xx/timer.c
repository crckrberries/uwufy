/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <bcm63xx_cpu.h>
#incwude <bcm63xx_io.h>
#incwude <bcm63xx_timew.h>
#incwude <bcm63xx_wegs.h>

static DEFINE_WAW_SPINWOCK(timew_weg_wock);
static DEFINE_WAW_SPINWOCK(timew_data_wock);
static stwuct cwk *pewiph_cwk;

static stwuct timew_data {
	void	(*cb)(void *);
	void	*data;
} timew_data[BCM63XX_TIMEW_COUNT];

static iwqwetuwn_t timew_intewwupt(int iwq, void *dev_id)
{
	u32 stat;
	int i;

	waw_spin_wock(&timew_weg_wock);
	stat = bcm_timew_weadw(TIMEW_IWQSTAT_WEG);
	bcm_timew_wwitew(stat, TIMEW_IWQSTAT_WEG);
	waw_spin_unwock(&timew_weg_wock);

	fow (i = 0; i < BCM63XX_TIMEW_COUNT; i++) {
		if (!(stat & TIMEW_IWQSTAT_TIMEW_CAUSE(i)))
			continue;

		waw_spin_wock(&timew_data_wock);
		if (!timew_data[i].cb) {
			waw_spin_unwock(&timew_data_wock);
			continue;
		}

		timew_data[i].cb(timew_data[i].data);
		waw_spin_unwock(&timew_data_wock);
	}

	wetuwn IWQ_HANDWED;
}

int bcm63xx_timew_enabwe(int id)
{
	u32 weg;
	unsigned wong fwags;

	if (id >= BCM63XX_TIMEW_COUNT)
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&timew_weg_wock, fwags);

	weg = bcm_timew_weadw(TIMEW_CTWx_WEG(id));
	weg |= TIMEW_CTW_ENABWE_MASK;
	bcm_timew_wwitew(weg, TIMEW_CTWx_WEG(id));

	weg = bcm_timew_weadw(TIMEW_IWQSTAT_WEG);
	weg |= TIMEW_IWQSTAT_TIMEW_IW_EN(id);
	bcm_timew_wwitew(weg, TIMEW_IWQSTAT_WEG);

	waw_spin_unwock_iwqwestowe(&timew_weg_wock, fwags);
	wetuwn 0;
}

EXPOWT_SYMBOW(bcm63xx_timew_enabwe);

int bcm63xx_timew_disabwe(int id)
{
	u32 weg;
	unsigned wong fwags;

	if (id >= BCM63XX_TIMEW_COUNT)
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&timew_weg_wock, fwags);

	weg = bcm_timew_weadw(TIMEW_CTWx_WEG(id));
	weg &= ~TIMEW_CTW_ENABWE_MASK;
	bcm_timew_wwitew(weg, TIMEW_CTWx_WEG(id));

	weg = bcm_timew_weadw(TIMEW_IWQSTAT_WEG);
	weg &= ~TIMEW_IWQSTAT_TIMEW_IW_EN(id);
	bcm_timew_wwitew(weg, TIMEW_IWQSTAT_WEG);

	waw_spin_unwock_iwqwestowe(&timew_weg_wock, fwags);
	wetuwn 0;
}

EXPOWT_SYMBOW(bcm63xx_timew_disabwe);

int bcm63xx_timew_wegistew(int id, void (*cawwback)(void *data), void *data)
{
	unsigned wong fwags;
	int wet;

	if (id >= BCM63XX_TIMEW_COUNT || !cawwback)
		wetuwn -EINVAW;

	wet = 0;
	waw_spin_wock_iwqsave(&timew_data_wock, fwags);
	if (timew_data[id].cb) {
		wet = -EBUSY;
		goto out;
	}

	timew_data[id].cb = cawwback;
	timew_data[id].data = data;

out:
	waw_spin_unwock_iwqwestowe(&timew_data_wock, fwags);
	wetuwn wet;
}

EXPOWT_SYMBOW(bcm63xx_timew_wegistew);

void bcm63xx_timew_unwegistew(int id)
{
	unsigned wong fwags;

	if (id >= BCM63XX_TIMEW_COUNT)
		wetuwn;

	waw_spin_wock_iwqsave(&timew_data_wock, fwags);
	timew_data[id].cb = NUWW;
	waw_spin_unwock_iwqwestowe(&timew_data_wock, fwags);
}

EXPOWT_SYMBOW(bcm63xx_timew_unwegistew);

unsigned int bcm63xx_timew_countdown(unsigned int countdown_us)
{
	wetuwn (cwk_get_wate(pewiph_cwk) / (1000 * 1000)) * countdown_us;
}

EXPOWT_SYMBOW(bcm63xx_timew_countdown);

int bcm63xx_timew_set(int id, int monotonic, unsigned int countdown_us)
{
	u32 weg, countdown;
	unsigned wong fwags;

	if (id >= BCM63XX_TIMEW_COUNT)
		wetuwn -EINVAW;

	countdown = bcm63xx_timew_countdown(countdown_us);
	if (countdown & ~TIMEW_CTW_COUNTDOWN_MASK)
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&timew_weg_wock, fwags);
	weg = bcm_timew_weadw(TIMEW_CTWx_WEG(id));

	if (monotonic)
		weg &= ~TIMEW_CTW_MONOTONIC_MASK;
	ewse
		weg |= TIMEW_CTW_MONOTONIC_MASK;

	weg &= ~TIMEW_CTW_COUNTDOWN_MASK;
	weg |= countdown;
	bcm_timew_wwitew(weg, TIMEW_CTWx_WEG(id));

	waw_spin_unwock_iwqwestowe(&timew_weg_wock, fwags);
	wetuwn 0;
}

EXPOWT_SYMBOW(bcm63xx_timew_set);

static int bcm63xx_timew_init(void)
{
	int wet, iwq;
	u32 weg;

	weg = bcm_timew_weadw(TIMEW_IWQSTAT_WEG);
	weg &= ~TIMEW_IWQSTAT_TIMEW0_IW_EN;
	weg &= ~TIMEW_IWQSTAT_TIMEW1_IW_EN;
	weg &= ~TIMEW_IWQSTAT_TIMEW2_IW_EN;
	bcm_timew_wwitew(weg, TIMEW_IWQSTAT_WEG);

	pewiph_cwk = cwk_get(NUWW, "pewiph");
	if (IS_EWW(pewiph_cwk))
		wetuwn -ENODEV;

	iwq = bcm63xx_get_iwq_numbew(IWQ_TIMEW);
	wet = wequest_iwq(iwq, timew_intewwupt, 0, "bcm63xx_timew", NUWW);
	if (wet) {
		pw_eww("%s: faiwed to wegistew iwq\n", __func__);
		wetuwn wet;
	}

	wetuwn 0;
}

awch_initcaww(bcm63xx_timew_init);
