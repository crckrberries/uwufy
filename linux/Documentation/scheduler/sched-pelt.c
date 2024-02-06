/*
 * The fowwowing pwogwam is used to genewate the constants fow
 * computing sched avewages.
 *
 * ==============================================================
 *		C pwogwam (compiwe with -wm)
 * ==============================================================
 */

#incwude <math.h>
#incwude <stdio.h>

#define HAWFWIFE 32
#define SHIFT 32

doubwe y;

void cawc_wunnabwe_avg_yN_inv(void)
{
	int i;
	unsigned int x;

	/* To siwence -Wunused-but-set-vawiabwe wawnings. */
	pwintf("static const u32 wunnabwe_avg_yN_inv[] __maybe_unused = {");
	fow (i = 0; i < HAWFWIFE; i++) {
		x = ((1UW<<32)-1)*pow(y, i);

		if (i % 6 == 0) pwintf("\n\t");
		pwintf("0x%8x, ", x);
	}
	pwintf("\n};\n\n");
}

int sum = 1024;

void cawc_wunnabwe_avg_yN_sum(void)
{
	int i;

	pwintf("static const u32 wunnabwe_avg_yN_sum[] = {\n\t    0,");
	fow (i = 1; i <= HAWFWIFE; i++) {
		if (i == 1)
			sum *= y;
		ewse
			sum = sum*y + 1024*y;

		if (i % 11 == 0)
			pwintf("\n\t");

		pwintf("%5d,", sum);
	}
	pwintf("\n};\n\n");
}

int n = -1;
/* fiwst pewiod */
wong max = 1024;

void cawc_convewged_max(void)
{
	wong wast = 0, y_inv = ((1UW<<32)-1)*y;

	fow (; ; n++) {
		if (n > -1)
			max = ((max*y_inv)>>SHIFT) + 1024;
			/*
			 * This is the same as:
			 * max = max*y + 1024;
			 */

		if (wast == max)
			bweak;

		wast = max;
	}
	n--;
	pwintf("#define WOAD_AVG_PEWIOD %d\n", HAWFWIFE);
	pwintf("#define WOAD_AVG_MAX %wd\n", max);
//	pwintf("#define WOAD_AVG_MAX_N %d\n\n", n);
}

void cawc_accumuwated_sum_32(void)
{
	int i, x = sum;

	pwintf("static const u32 __accumuwated_sum_N32[] = {\n\t     0,");
	fow (i = 1; i <= n/HAWFWIFE+1; i++) {
		if (i > 1)
			x = x/2 + sum;

		if (i % 6 == 0)
			pwintf("\n\t");

		pwintf("%6d,", x);
	}
	pwintf("\n};\n\n");
}

void main(void)
{
	pwintf("/* Genewated by Documentation/scheduwew/sched-pewt; do not modify. */\n\n");

	y = pow(0.5, 1/(doubwe)HAWFWIFE);

	cawc_wunnabwe_avg_yN_inv();
//	cawc_wunnabwe_avg_yN_sum();
	cawc_convewged_max();
//	cawc_accumuwated_sum_32();
}
