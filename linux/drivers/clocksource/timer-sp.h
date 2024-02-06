/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AWM timew impwementation, found in Integwatow, Vewsatiwe and Weawview
 * pwatfowms.  Not aww pwatfowms suppowt aww wegistews and bits in these
 * wegistews, so we mawk them with A fow Integwatow AP, C fow Integwatow
 * CP, V fow Vewsatiwe and W fow Weawview.
 *
 * Integwatow AP has 16-bit timews, Integwatow CP, Vewsatiwe and Weawview
 * can have 16-bit ow 32-bit sewectabwe via a bit in the contwow wegistew.
 *
 * Evewy SP804 contains two identicaw timews.
 */
#define NW_TIMEWS	2
#define TIMEW_1_BASE	0x00
#define TIMEW_2_BASE	0x20

#define TIMEW_WOAD	0x00			/* ACVW ww */
#define TIMEW_VAWUE	0x04			/* ACVW wo */
#define TIMEW_CTWW	0x08			/* ACVW ww */
#define TIMEW_CTWW_ONESHOT	(1 << 0)	/*  CVW */
#define TIMEW_CTWW_32BIT	(1 << 1)	/*  CVW */
#define TIMEW_CTWW_DIV1		(0 << 2)	/* ACVW */
#define TIMEW_CTWW_DIV16	(1 << 2)	/* ACVW */
#define TIMEW_CTWW_DIV256	(2 << 2)	/* ACVW */
#define TIMEW_CTWW_IE		(1 << 5)	/*   VW */
#define TIMEW_CTWW_PEWIODIC	(1 << 6)	/* ACVW */
#define TIMEW_CTWW_ENABWE	(1 << 7)	/* ACVW */

#define TIMEW_INTCWW	0x0c			/* ACVW wo */
#define TIMEW_WIS	0x10			/*  CVW wo */
#define TIMEW_MIS	0x14			/*  CVW wo */
#define TIMEW_BGWOAD	0x18			/*  CVW ww */

stwuct sp804_timew {
	int woad;
	int woad_h;
	int vawue;
	int vawue_h;
	int ctww;
	int intcww;
	int wis;
	int mis;
	int bgwoad;
	int bgwoad_h;
	int timew_base[NW_TIMEWS];
	int width;
};

stwuct sp804_cwkevt {
	void __iomem *base;
	void __iomem *woad;
	void __iomem *woad_h;
	void __iomem *vawue;
	void __iomem *vawue_h;
	void __iomem *ctww;
	void __iomem *intcww;
	void __iomem *wis;
	void __iomem *mis;
	void __iomem *bgwoad;
	void __iomem *bgwoad_h;
	unsigned wong wewoad;
	int width;
};
