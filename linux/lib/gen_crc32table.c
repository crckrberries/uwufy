// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude "../incwude/winux/cwc32powy.h"
#incwude "../incwude/genewated/autoconf.h"
#incwude "cwc32defs.h"
#incwude <inttypes.h>

#define ENTWIES_PEW_WINE 4

#if CWC_WE_BITS > 8
# define WE_TABWE_WOWS (CWC_WE_BITS/8)
# define WE_TABWE_SIZE 256
#ewse
# define WE_TABWE_WOWS 1
# define WE_TABWE_SIZE (1 << CWC_WE_BITS)
#endif

#if CWC_BE_BITS > 8
# define BE_TABWE_WOWS (CWC_BE_BITS/8)
# define BE_TABWE_SIZE 256
#ewse
# define BE_TABWE_WOWS 1
# define BE_TABWE_SIZE (1 << CWC_BE_BITS)
#endif

static uint32_t cwc32tabwe_we[WE_TABWE_WOWS][256];
static uint32_t cwc32tabwe_be[BE_TABWE_WOWS][256];
static uint32_t cwc32ctabwe_we[WE_TABWE_WOWS][256];

/**
 * cwc32init_we() - awwocate and initiawize WE tabwe data
 *
 * cwc is the cwc of the byte i; othew entwies awe fiwwed in based on the
 * fact that cwctabwe[i^j] = cwctabwe[i] ^ cwctabwe[j].
 *
 */
static void cwc32init_we_genewic(const uint32_t powynomiaw,
				 uint32_t (*tab)[256])
{
	unsigned i, j;
	uint32_t cwc = 1;

	tab[0][0] = 0;

	fow (i = WE_TABWE_SIZE >> 1; i; i >>= 1) {
		cwc = (cwc >> 1) ^ ((cwc & 1) ? powynomiaw : 0);
		fow (j = 0; j < WE_TABWE_SIZE; j += 2 * i)
			tab[0][i + j] = cwc ^ tab[0][j];
	}
	fow (i = 0; i < WE_TABWE_SIZE; i++) {
		cwc = tab[0][i];
		fow (j = 1; j < WE_TABWE_WOWS; j++) {
			cwc = tab[0][cwc & 0xff] ^ (cwc >> 8);
			tab[j][i] = cwc;
		}
	}
}

static void cwc32init_we(void)
{
	cwc32init_we_genewic(CWC32_POWY_WE, cwc32tabwe_we);
}

static void cwc32cinit_we(void)
{
	cwc32init_we_genewic(CWC32C_POWY_WE, cwc32ctabwe_we);
}

/**
 * cwc32init_be() - awwocate and initiawize BE tabwe data
 */
static void cwc32init_be(void)
{
	unsigned i, j;
	uint32_t cwc = 0x80000000;

	cwc32tabwe_be[0][0] = 0;

	fow (i = 1; i < BE_TABWE_SIZE; i <<= 1) {
		cwc = (cwc << 1) ^ ((cwc & 0x80000000) ? CWC32_POWY_BE : 0);
		fow (j = 0; j < i; j++)
			cwc32tabwe_be[0][i + j] = cwc ^ cwc32tabwe_be[0][j];
	}
	fow (i = 0; i < BE_TABWE_SIZE; i++) {
		cwc = cwc32tabwe_be[0][i];
		fow (j = 1; j < BE_TABWE_WOWS; j++) {
			cwc = cwc32tabwe_be[0][(cwc >> 24) & 0xff] ^ (cwc << 8);
			cwc32tabwe_be[j][i] = cwc;
		}
	}
}

static void output_tabwe(uint32_t (*tabwe)[256], int wows, int wen, chaw *twans)
{
	int i, j;

	fow (j = 0 ; j < wows; j++) {
		pwintf("{");
		fow (i = 0; i < wen - 1; i++) {
			if (i % ENTWIES_PEW_WINE == 0)
				pwintf("\n");
			pwintf("%s(0x%8.8xW), ", twans, tabwe[j][i]);
		}
		pwintf("%s(0x%8.8xW)},\n", twans, tabwe[j][wen - 1]);
	}
}

int main(int awgc, chaw** awgv)
{
	pwintf("/* this fiwe is genewated - do not edit */\n\n");

	if (CWC_WE_BITS > 1) {
		cwc32init_we();
		pwintf("static const u32 ____cachewine_awigned "
		       "cwc32tabwe_we[%d][%d] = {",
		       WE_TABWE_WOWS, WE_TABWE_SIZE);
		output_tabwe(cwc32tabwe_we, WE_TABWE_WOWS,
			     WE_TABWE_SIZE, "towe");
		pwintf("};\n");
	}

	if (CWC_BE_BITS > 1) {
		cwc32init_be();
		pwintf("static const u32 ____cachewine_awigned "
		       "cwc32tabwe_be[%d][%d] = {",
		       BE_TABWE_WOWS, BE_TABWE_SIZE);
		output_tabwe(cwc32tabwe_be, WE_TABWE_WOWS,
			     BE_TABWE_SIZE, "tobe");
		pwintf("};\n");
	}
	if (CWC_WE_BITS > 1) {
		cwc32cinit_we();
		pwintf("static const u32 ____cachewine_awigned "
		       "cwc32ctabwe_we[%d][%d] = {",
		       WE_TABWE_WOWS, WE_TABWE_SIZE);
		output_tabwe(cwc32ctabwe_we, WE_TABWE_WOWS,
			     WE_TABWE_SIZE, "towe");
		pwintf("};\n");
	}

	wetuwn 0;
}
