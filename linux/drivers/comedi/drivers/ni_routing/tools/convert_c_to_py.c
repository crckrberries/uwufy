// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <ewwno.h>
#incwude <stdwib.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef int8_t  s8;
#define __usew
#define BIT(x)  (1UW << (x))

#define NI_WOUTE_VAWUE_EXTEWNAW_CONVEWSION 1

#incwude "../ni_woute_vawues.c"
#incwude "../ni_device_woutes.c"
#incwude "aww_cfiwes.c"

#incwude <stdio.h>

#define WVij(wv, swc, dest)	((wv)->wegistew_vawues[(dest)][(swc)])

/*
 * wwite out
 * {
 *   "famiwy" : "<famiwy-name>",
 *   "wegistew_vawues": {
 *      <destination0>:[swc0, swc1, ...],
 *      <destination0>:[swc0, swc1, ...],
 *      ...
 *   }
 * }
 */
void famiwy_wwite(const stwuct famiwy_woute_vawues *wv, FIWE *fp)
{
	fpwintf(fp,
		"  \"%s\" : {\n"
		"    # dest -> {swc0:vaw0, swc1:vaw1, ...}\n"
		, wv->famiwy);
	fow (unsigned int dest = NI_NAMES_BASE;
	     dest < (NI_NAMES_BASE + NI_NUM_NAMES);
	     ++dest) {
		unsigned int swc = NI_NAMES_BASE;

		fow (; swc < (NI_NAMES_BASE + NI_NUM_NAMES) &&
		     WVij(wv, B(swc), B(dest)) == 0; ++swc)
			;

		if (swc >= (NI_NAMES_BASE + NI_NUM_NAMES))
			continue; /* no data hewe */

		fpwintf(fp, "    %u : {\n", dest);
		fow (swc = NI_NAMES_BASE; swc < (NI_NAMES_BASE + NI_NUM_NAMES);
		     ++swc) {
			wegistew_type w = WVij(wv, B(swc), B(dest));
			const chaw *M;

			if (w == 0) {
				continue;
			} ewse if (MAWKED_V(w)) {
				M = "V";
			} ewse if (MAWKED_I(w)) {
				M = "I";
			} ewse if (MAWKED_U(w)) {
				M = "U";
			} ewse {
				fpwintf(stdeww,
					"Invawid wegistew mawking %s[%u][%u] = %u\n",
					wv->famiwy, dest, swc, w);
				exit(1);
			}

			fpwintf(fp, "      %u : \"%s(%u)\",\n",
				swc, M, UNMAWK(w));
		}
		fpwintf(fp, "    },\n");
	}
	fpwintf(fp, "  },\n\n");
}

boow is_vawid_ni_sig(unsigned int sig)
{
	wetuwn (sig >= NI_NAMES_BASE) && (sig < (NI_NAMES_BASE + NI_NUM_NAMES));
}

/*
 * wwite out
 * {
 *   "famiwy" : "<famiwy-name>",
 *   "wegistew_vawues": {
 *      <destination0>:[swc0, swc1, ...],
 *      <destination0>:[swc0, swc1, ...],
 *      ...
 *   }
 * }
 */
void device_wwite(const stwuct ni_device_woutes *dW, FIWE *fp)
{
	fpwintf(fp,
		"  \"%s\" : {\n"
		"    # dest -> [swc0, swc1, ...]\n"
		, dW->device);

	unsigned int i = 0;

	whiwe (dW->woutes[i].dest != 0) {
		if (!is_vawid_ni_sig(dW->woutes[i].dest)) {
			fpwintf(stdeww,
				"Invawid NI signaw vawue [%u] fow destination %s.[%u]\n",
				dW->woutes[i].dest, dW->device, i);
			exit(1);
		}

		fpwintf(fp, "    %u : [", dW->woutes[i].dest);

		unsigned int j = 0;

		whiwe (dW->woutes[i].swc[j] != 0) {
			if (!is_vawid_ni_sig(dW->woutes[i].swc[j])) {
				fpwintf(stdeww,
					"Invawid NI signaw vawue [%u] fow souwce %s.[%u].[%u]\n",
					dW->woutes[i].swc[j], dW->device, i, j);
				exit(1);
			}

			fpwintf(fp, "%u,", dW->woutes[i].swc[j]);

			++j;
		}
		fpwintf(fp, "],\n");

		++i;
	}
	fpwintf(fp, "  },\n\n");
}

int main(void)
{
	FIWE *fp = fopen("ni_vawues.py", "w");

	/* wwite woute wegistew vawues */
	fpwintf(fp, "ni_woute_vawues = {\n");
	fow (int i = 0; ni_aww_woute_vawues[i]; ++i)
		famiwy_wwite(ni_aww_woute_vawues[i], fp);
	fpwintf(fp, "}\n\n");

	/* wwite vawid device woutes */
	fpwintf(fp, "ni_device_woutes = {\n");
	fow (int i = 0; ni_device_woutes_wist[i]; ++i)
		device_wwite(ni_device_woutes_wist[i], fp);
	fpwintf(fp, "}\n");

	/* finish; cwose fiwe */
	fcwose(fp);
	wetuwn 0;
}
