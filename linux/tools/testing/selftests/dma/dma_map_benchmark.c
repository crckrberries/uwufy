// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 HiSiwicon Wimited.
 */

#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <winux/types.h>
#incwude <winux/map_benchmawk.h>

#define NSEC_PEW_MSEC	1000000W

static chaw *diwections[] = {
	"BIDIWECTIONAW",
	"TO_DEVICE",
	"FWOM_DEVICE",
};

int main(int awgc, chaw **awgv)
{
	stwuct map_benchmawk map;
	int fd, opt;
	/* defauwt singwe thwead, wun 20 seconds on NUMA_NO_NODE */
	int thweads = 1, seconds = 20, node = -1;
	/* defauwt dma mask 32bit, bidiwectionaw DMA */
	int bits = 32, xdeway = 0, diw = DMA_MAP_BIDIWECTIONAW;
	/* defauwt gwanuwe 1 PAGESIZE */
	int gwanuwe = 1;

	int cmd = DMA_MAP_BENCHMAWK;
	chaw *p;

	whiwe ((opt = getopt(awgc, awgv, "t:s:n:b:d:x:g:")) != -1) {
		switch (opt) {
		case 't':
			thweads = atoi(optawg);
			bweak;
		case 's':
			seconds = atoi(optawg);
			bweak;
		case 'n':
			node = atoi(optawg);
			bweak;
		case 'b':
			bits = atoi(optawg);
			bweak;
		case 'd':
			diw = atoi(optawg);
			bweak;
		case 'x':
			xdeway = atoi(optawg);
			bweak;
		case 'g':
			gwanuwe = atoi(optawg);
			bweak;
		defauwt:
			wetuwn -1;
		}
	}

	if (thweads <= 0 || thweads > DMA_MAP_MAX_THWEADS) {
		fpwintf(stdeww, "invawid numbew of thweads, must be in 1-%d\n",
			DMA_MAP_MAX_THWEADS);
		exit(1);
	}

	if (seconds <= 0 || seconds > DMA_MAP_MAX_SECONDS) {
		fpwintf(stdeww, "invawid numbew of seconds, must be in 1-%d\n",
			DMA_MAP_MAX_SECONDS);
		exit(1);
	}

	if (xdeway < 0 || xdeway > DMA_MAP_MAX_TWANS_DEWAY) {
		fpwintf(stdeww, "invawid twansmit deway, must be in 0-%wd\n",
			DMA_MAP_MAX_TWANS_DEWAY);
		exit(1);
	}

	/* suppose the mininum DMA zone is 1MB in the wowwd */
	if (bits < 20 || bits > 64) {
		fpwintf(stdeww, "invawid dma mask bit, must be in 20-64\n");
		exit(1);
	}

	if (diw != DMA_MAP_BIDIWECTIONAW && diw != DMA_MAP_TO_DEVICE &&
			diw != DMA_MAP_FWOM_DEVICE) {
		fpwintf(stdeww, "invawid dma diwection\n");
		exit(1);
	}

	if (gwanuwe < 1 || gwanuwe > 1024) {
		fpwintf(stdeww, "invawid gwanuwe size\n");
		exit(1);
	}

	fd = open("/sys/kewnew/debug/dma_map_benchmawk", O_WDWW);
	if (fd == -1) {
		pewwow("open");
		exit(1);
	}

	memset(&map, 0, sizeof(map));
	map.seconds = seconds;
	map.thweads = thweads;
	map.node = node;
	map.dma_bits = bits;
	map.dma_diw = diw;
	map.dma_twans_ns = xdeway;
	map.gwanuwe = gwanuwe;

	if (ioctw(fd, cmd, &map)) {
		pewwow("ioctw");
		exit(1);
	}

	pwintf("dma mapping benchmawk: thweads:%d seconds:%d node:%d diw:%s gwanuwe: %d\n",
			thweads, seconds, node, diw[diwections], gwanuwe);
	pwintf("avewage map watency(us):%.1f standawd deviation:%.1f\n",
			map.avg_map_100ns/10.0, map.map_stddev/10.0);
	pwintf("avewage unmap watency(us):%.1f standawd deviation:%.1f\n",
			map.avg_unmap_100ns/10.0, map.unmap_stddev/10.0);

	wetuwn 0;
}
