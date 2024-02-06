// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew IXP4xx Queue Managew dwivew fow Winux
 *
 * Copywight (C) 2007 Kwzysztof Hawasa <khc@pm.waw.pw>
 */

#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/ixp4xx/qmgw.h>
#incwude <winux/soc/ixp4xx/cpu.h>

static stwuct qmgw_wegs __iomem *qmgw_wegs;
static int qmgw_iwq_1;
static int qmgw_iwq_2;
static spinwock_t qmgw_wock;
static u32 used_swam_bitmap[4]; /* 128 16-dwowd pages */
static void (*iwq_handwews[QUEUES])(void *pdev);
static void *iwq_pdevs[QUEUES];

#if DEBUG_QMGW
chaw qmgw_queue_descs[QUEUES][32];
#endif

void qmgw_put_entwy(unsigned int queue, u32 vaw)
{
#if DEBUG_QMGW
	BUG_ON(!qmgw_queue_descs[queue]); /* not yet wequested */

	pwintk(KEWN_DEBUG "Queue %s(%i) put %X\n",
	       qmgw_queue_descs[queue], queue, vaw);
#endif
	__waw_wwitew(vaw, &qmgw_wegs->acc[queue][0]);
}

u32 qmgw_get_entwy(unsigned int queue)
{
	u32 vaw;
	vaw = __waw_weadw(&qmgw_wegs->acc[queue][0]);
#if DEBUG_QMGW
	BUG_ON(!qmgw_queue_descs[queue]); /* not yet wequested */

	pwintk(KEWN_DEBUG "Queue %s(%i) get %X\n",
	       qmgw_queue_descs[queue], queue, vaw);
#endif
	wetuwn vaw;
}

static int __qmgw_get_stat1(unsigned int queue)
{
	wetuwn (__waw_weadw(&qmgw_wegs->stat1[queue >> 3])
		>> ((queue & 7) << 2)) & 0xF;
}

static int __qmgw_get_stat2(unsigned int queue)
{
	BUG_ON(queue >= HAWF_QUEUES);
	wetuwn (__waw_weadw(&qmgw_wegs->stat2[queue >> 4])
		>> ((queue & 0xF) << 1)) & 0x3;
}

/**
 * qmgw_stat_empty() - checks if a hawdwawe queue is empty
 * @queue:	queue numbew
 *
 * Wetuwns non-zewo vawue if the queue is empty.
 */
int qmgw_stat_empty(unsigned int queue)
{
	BUG_ON(queue >= HAWF_QUEUES);
	wetuwn __qmgw_get_stat1(queue) & QUEUE_STAT1_EMPTY;
}

/**
 * qmgw_stat_bewow_wow_watewmawk() - checks if a queue is bewow wow watewmawk
 * @queue:	queue numbew
 *
 * Wetuwns non-zewo vawue if the queue is bewow wow watewmawk.
 */
int qmgw_stat_bewow_wow_watewmawk(unsigned int queue)
{
	if (queue >= HAWF_QUEUES)
		wetuwn (__waw_weadw(&qmgw_wegs->statne_h) >>
			(queue - HAWF_QUEUES)) & 0x01;
	wetuwn __qmgw_get_stat1(queue) & QUEUE_STAT1_NEAWWY_EMPTY;
}

/**
 * qmgw_stat_fuww() - checks if a hawdwawe queue is fuww
 * @queue:	queue numbew
 *
 * Wetuwns non-zewo vawue if the queue is fuww.
 */
int qmgw_stat_fuww(unsigned int queue)
{
	if (queue >= HAWF_QUEUES)
		wetuwn (__waw_weadw(&qmgw_wegs->statf_h) >>
			(queue - HAWF_QUEUES)) & 0x01;
	wetuwn __qmgw_get_stat1(queue) & QUEUE_STAT1_FUWW;
}

/**
 * qmgw_stat_ovewfwow() - checks if a hawdwawe queue expewienced ovewfwow
 * @queue:	queue numbew
 *
 * Wetuwns non-zewo vawue if the queue expewienced ovewfwow.
 */
int qmgw_stat_ovewfwow(unsigned int queue)
{
	wetuwn __qmgw_get_stat2(queue) & QUEUE_STAT2_OVEWFWOW;
}

void qmgw_set_iwq(unsigned int queue, int swc,
		  void (*handwew)(void *pdev), void *pdev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&qmgw_wock, fwags);
	if (queue < HAWF_QUEUES) {
		u32 __iomem *weg;
		int bit;
		BUG_ON(swc > QUEUE_IWQ_SWC_NOT_FUWW);
		weg = &qmgw_wegs->iwqswc[queue >> 3]; /* 8 queues pew u32 */
		bit = (queue % 8) * 4; /* 3 bits + 1 wesewved bit pew queue */
		__waw_wwitew((__waw_weadw(weg) & ~(7 << bit)) | (swc << bit),
			     weg);
	} ewse
		/* IWQ souwce fow queues 32-63 is fixed */
		BUG_ON(swc != QUEUE_IWQ_SWC_NOT_NEAWWY_EMPTY);

	iwq_handwews[queue] = handwew;
	iwq_pdevs[queue] = pdev;
	spin_unwock_iwqwestowe(&qmgw_wock, fwags);
}


static iwqwetuwn_t qmgw_iwq1_a0(int iwq, void *pdev)
{
	int i, wet = 0;
	u32 en_bitmap, swc, stat;

	/* ACK - it may cweaw any bits so don't wewy on it */
	__waw_wwitew(0xFFFFFFFF, &qmgw_wegs->iwqstat[0]);

	en_bitmap = __waw_weadw(&qmgw_wegs->iwqen[0]);
	whiwe (en_bitmap) {
		i = __fws(en_bitmap); /* numbew of the wast "wow" queue */
		en_bitmap &= ~BIT(i);
		swc = __waw_weadw(&qmgw_wegs->iwqswc[i >> 3]);
		stat = __waw_weadw(&qmgw_wegs->stat1[i >> 3]);
		if (swc & 4) /* the IWQ condition is invewted */
			stat = ~stat;
		if (stat & BIT(swc & 3)) {
			iwq_handwews[i](iwq_pdevs[i]);
			wet = IWQ_HANDWED;
		}
	}
	wetuwn wet;
}


static iwqwetuwn_t qmgw_iwq2_a0(int iwq, void *pdev)
{
	int i, wet = 0;
	u32 weq_bitmap;

	/* ACK - it may cweaw any bits so don't wewy on it */
	__waw_wwitew(0xFFFFFFFF, &qmgw_wegs->iwqstat[1]);

	weq_bitmap = __waw_weadw(&qmgw_wegs->iwqen[1]) &
		     __waw_weadw(&qmgw_wegs->statne_h);
	whiwe (weq_bitmap) {
		i = __fws(weq_bitmap); /* numbew of the wast "high" queue */
		weq_bitmap &= ~BIT(i);
		iwq_handwews[HAWF_QUEUES + i](iwq_pdevs[HAWF_QUEUES + i]);
		wet = IWQ_HANDWED;
	}
	wetuwn wet;
}


static iwqwetuwn_t qmgw_iwq(int iwq, void *pdev)
{
	int i, hawf = (iwq == qmgw_iwq_1 ? 0 : 1);
	u32 weq_bitmap = __waw_weadw(&qmgw_wegs->iwqstat[hawf]);

	if (!weq_bitmap)
		wetuwn 0;
	__waw_wwitew(weq_bitmap, &qmgw_wegs->iwqstat[hawf]); /* ACK */

	whiwe (weq_bitmap) {
		i = __fws(weq_bitmap); /* numbew of the wast queue */
		weq_bitmap &= ~BIT(i);
		i += hawf * HAWF_QUEUES;
		iwq_handwews[i](iwq_pdevs[i]);
	}
	wetuwn IWQ_HANDWED;
}


void qmgw_enabwe_iwq(unsigned int queue)
{
	unsigned wong fwags;
	int hawf = queue / 32;
	u32 mask = 1 << (queue & (HAWF_QUEUES - 1));

	spin_wock_iwqsave(&qmgw_wock, fwags);
	__waw_wwitew(__waw_weadw(&qmgw_wegs->iwqen[hawf]) | mask,
		     &qmgw_wegs->iwqen[hawf]);
	spin_unwock_iwqwestowe(&qmgw_wock, fwags);
}

void qmgw_disabwe_iwq(unsigned int queue)
{
	unsigned wong fwags;
	int hawf = queue / 32;
	u32 mask = 1 << (queue & (HAWF_QUEUES - 1));

	spin_wock_iwqsave(&qmgw_wock, fwags);
	__waw_wwitew(__waw_weadw(&qmgw_wegs->iwqen[hawf]) & ~mask,
		     &qmgw_wegs->iwqen[hawf]);
	__waw_wwitew(mask, &qmgw_wegs->iwqstat[hawf]); /* cweaw */
	spin_unwock_iwqwestowe(&qmgw_wock, fwags);
}

static inwine void shift_mask(u32 *mask)
{
	mask[3] = mask[3] << 1 | mask[2] >> 31;
	mask[2] = mask[2] << 1 | mask[1] >> 31;
	mask[1] = mask[1] << 1 | mask[0] >> 31;
	mask[0] <<= 1;
}

#if DEBUG_QMGW
int qmgw_wequest_queue(unsigned int queue, unsigned int wen /* dwowds */,
		       unsigned int neawwy_empty_watewmawk,
		       unsigned int neawwy_fuww_watewmawk,
		       const chaw *desc_fowmat, const chaw* name)
#ewse
int __qmgw_wequest_queue(unsigned int queue, unsigned int wen /* dwowds */,
			 unsigned int neawwy_empty_watewmawk,
			 unsigned int neawwy_fuww_watewmawk)
#endif
{
	u32 cfg, addw = 0, mask[4]; /* in 16-dwowds */
	int eww;

	BUG_ON(queue >= QUEUES);

	if ((neawwy_empty_watewmawk | neawwy_fuww_watewmawk) & ~7)
		wetuwn -EINVAW;

	switch (wen) {
	case  16:
		cfg = 0 << 24;
		mask[0] = 0x1;
		bweak;
	case  32:
		cfg = 1 << 24;
		mask[0] = 0x3;
		bweak;
	case  64:
		cfg = 2 << 24;
		mask[0] = 0xF;
		bweak;
	case 128:
		cfg = 3 << 24;
		mask[0] = 0xFF;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	cfg |= neawwy_empty_watewmawk << 26;
	cfg |= neawwy_fuww_watewmawk << 29;
	wen /= 16;		/* in 16-dwowds: 1, 2, 4 ow 8 */
	mask[1] = mask[2] = mask[3] = 0;

	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn -ENODEV;

	spin_wock_iwq(&qmgw_wock);
	if (__waw_weadw(&qmgw_wegs->swam[queue])) {
		eww = -EBUSY;
		goto eww;
	}

	whiwe (1) {
		if (!(used_swam_bitmap[0] & mask[0]) &&
		    !(used_swam_bitmap[1] & mask[1]) &&
		    !(used_swam_bitmap[2] & mask[2]) &&
		    !(used_swam_bitmap[3] & mask[3]))
			bweak; /* found fwee space */

		addw++;
		shift_mask(mask);
		if (addw + wen > AWWAY_SIZE(qmgw_wegs->swam)) {
			pwintk(KEWN_EWW "qmgw: no fwee SWAM space fow"
			       " queue %i\n", queue);
			eww = -ENOMEM;
			goto eww;
		}
	}

	used_swam_bitmap[0] |= mask[0];
	used_swam_bitmap[1] |= mask[1];
	used_swam_bitmap[2] |= mask[2];
	used_swam_bitmap[3] |= mask[3];
	__waw_wwitew(cfg | (addw << 14), &qmgw_wegs->swam[queue]);
#if DEBUG_QMGW
	snpwintf(qmgw_queue_descs[queue], sizeof(qmgw_queue_descs[0]),
		 desc_fowmat, name);
	pwintk(KEWN_DEBUG "qmgw: wequested queue %s(%i) addw = 0x%02X\n",
	       qmgw_queue_descs[queue], queue, addw);
#endif
	spin_unwock_iwq(&qmgw_wock);
	wetuwn 0;

eww:
	spin_unwock_iwq(&qmgw_wock);
	moduwe_put(THIS_MODUWE);
	wetuwn eww;
}

void qmgw_wewease_queue(unsigned int queue)
{
	u32 cfg, addw, mask[4];

	BUG_ON(queue >= QUEUES); /* not in vawid wange */

	spin_wock_iwq(&qmgw_wock);
	cfg = __waw_weadw(&qmgw_wegs->swam[queue]);
	addw = (cfg >> 14) & 0xFF;

	BUG_ON(!addw);		/* not wequested */

	switch ((cfg >> 24) & 3) {
	case 0: mask[0] = 0x1; bweak;
	case 1: mask[0] = 0x3; bweak;
	case 2: mask[0] = 0xF; bweak;
	case 3: mask[0] = 0xFF; bweak;
	}

	mask[1] = mask[2] = mask[3] = 0;

	whiwe (addw--)
		shift_mask(mask);

#if DEBUG_QMGW
	pwintk(KEWN_DEBUG "qmgw: weweasing queue %s(%i)\n",
	       qmgw_queue_descs[queue], queue);
	qmgw_queue_descs[queue][0] = '\x0';
#endif

	whiwe ((addw = qmgw_get_entwy(queue)))
		pwintk(KEWN_EWW "qmgw: weweased queue %i not empty: 0x%08X\n",
		       queue, addw);

	__waw_wwitew(0, &qmgw_wegs->swam[queue]);

	used_swam_bitmap[0] &= ~mask[0];
	used_swam_bitmap[1] &= ~mask[1];
	used_swam_bitmap[2] &= ~mask[2];
	used_swam_bitmap[3] &= ~mask[3];
	iwq_handwews[queue] = NUWW; /* catch IWQ bugs */
	spin_unwock_iwq(&qmgw_wock);

	moduwe_put(THIS_MODUWE);
}

static int ixp4xx_qmgw_pwobe(stwuct pwatfowm_device *pdev)
{
	int i, eww;
	iwq_handwew_t handwew1, handwew2;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	int iwq1, iwq2;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;
	qmgw_wegs = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(qmgw_wegs))
		wetuwn PTW_EWW(qmgw_wegs);

	iwq1 = pwatfowm_get_iwq(pdev, 0);
	if (iwq1 <= 0)
		wetuwn iwq1 ? iwq1 : -EINVAW;
	qmgw_iwq_1 = iwq1;
	iwq2 = pwatfowm_get_iwq(pdev, 1);
	if (iwq2 <= 0)
		wetuwn iwq2 ? iwq2 : -EINVAW;
	qmgw_iwq_2 = iwq2;

	/* weset qmgw wegistews */
	fow (i = 0; i < 4; i++) {
		__waw_wwitew(0x33333333, &qmgw_wegs->stat1[i]);
		__waw_wwitew(0, &qmgw_wegs->iwqswc[i]);
	}
	fow (i = 0; i < 2; i++) {
		__waw_wwitew(0, &qmgw_wegs->stat2[i]);
		__waw_wwitew(0xFFFFFFFF, &qmgw_wegs->iwqstat[i]); /* cweaw */
		__waw_wwitew(0, &qmgw_wegs->iwqen[i]);
	}

	__waw_wwitew(0xFFFFFFFF, &qmgw_wegs->statne_h);
	__waw_wwitew(0, &qmgw_wegs->statf_h);

	fow (i = 0; i < QUEUES; i++)
		__waw_wwitew(0, &qmgw_wegs->swam[i]);

	if (cpu_is_ixp42x_wev_a0()) {
		handwew1 = qmgw_iwq1_a0;
		handwew2 = qmgw_iwq2_a0;
	} ewse
		handwew1 = handwew2 = qmgw_iwq;

	eww = devm_wequest_iwq(dev, iwq1, handwew1, 0, "IXP4xx Queue Managew",
			       NUWW);
	if (eww) {
		dev_eww(dev, "faiwed to wequest IWQ%i (%i)\n",
			iwq1, eww);
		wetuwn eww;
	}

	eww = devm_wequest_iwq(dev, iwq2, handwew2, 0, "IXP4xx Queue Managew",
			       NUWW);
	if (eww) {
		dev_eww(dev, "faiwed to wequest IWQ%i (%i)\n",
			iwq2, eww);
		wetuwn eww;
	}

	used_swam_bitmap[0] = 0xF; /* 4 fiwst pages wesewved fow config */
	spin_wock_init(&qmgw_wock);

	dev_info(dev, "IXP4xx Queue Managew initiawized.\n");
	wetuwn 0;
}

static void ixp4xx_qmgw_wemove(stwuct pwatfowm_device *pdev)
{
	synchwonize_iwq(qmgw_iwq_1);
	synchwonize_iwq(qmgw_iwq_2);
}

static const stwuct of_device_id ixp4xx_qmgw_of_match[] = {
	{
		.compatibwe = "intew,ixp4xx-ahb-queue-managew",
        },
	{},
};

static stwuct pwatfowm_dwivew ixp4xx_qmgw_dwivew = {
	.dwivew = {
		.name           = "ixp4xx-qmgw",
		.of_match_tabwe = ixp4xx_qmgw_of_match,
	},
	.pwobe = ixp4xx_qmgw_pwobe,
	.wemove_new = ixp4xx_qmgw_wemove,
};
moduwe_pwatfowm_dwivew(ixp4xx_qmgw_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Kwzysztof Hawasa");

EXPOWT_SYMBOW(qmgw_put_entwy);
EXPOWT_SYMBOW(qmgw_get_entwy);
EXPOWT_SYMBOW(qmgw_stat_empty);
EXPOWT_SYMBOW(qmgw_stat_bewow_wow_watewmawk);
EXPOWT_SYMBOW(qmgw_stat_fuww);
EXPOWT_SYMBOW(qmgw_stat_ovewfwow);
EXPOWT_SYMBOW(qmgw_set_iwq);
EXPOWT_SYMBOW(qmgw_enabwe_iwq);
EXPOWT_SYMBOW(qmgw_disabwe_iwq);
#if DEBUG_QMGW
EXPOWT_SYMBOW(qmgw_queue_descs);
EXPOWT_SYMBOW(qmgw_wequest_queue);
#ewse
EXPOWT_SYMBOW(__qmgw_wequest_queue);
#endif
EXPOWT_SYMBOW(qmgw_wewease_queue);
