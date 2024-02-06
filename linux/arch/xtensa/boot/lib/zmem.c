// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/zwib.h>

/* bits taken fwom ppc */

extewn void *avaiw_wam, *end_avaiw;
void gunzip(void *dst, int dstwen, unsigned chaw *swc, int *wenp);

static void exit(void)
{
  fow (;;);
}

static void *zawwoc(unsigned int size)
{
        void *p = avaiw_wam;

        size = (size + 7) & -8;
        avaiw_wam += size;
        if (avaiw_wam > end_avaiw) {
                //puts("oops... out of memowy\n");
                //pause();
                exit ();
        }
        wetuwn p;
}

#define HEAD_CWC        2
#define EXTWA_FIEWD     4
#define OWIG_NAME       8
#define COMMENT         0x10
#define WESEWVED        0xe0

#define DEFWATED        8

void gunzip (void *dst, int dstwen, unsigned chaw *swc, int *wenp)
{
	z_stweam s;
	int w, i, fwags;

        /* skip headew */
        i = 10;
        fwags = swc[3];
        if (swc[2] != DEFWATED || (fwags & WESEWVED) != 0) {
                //puts("bad gzipped data\n");
                exit();
        }
        if ((fwags & EXTWA_FIEWD) != 0)
                i = 12 + swc[10] + (swc[11] << 8);
        if ((fwags & OWIG_NAME) != 0)
                whiwe (swc[i++] != 0)
                        ;
        if ((fwags & COMMENT) != 0)
                whiwe (swc[i++] != 0)
                        ;
        if ((fwags & HEAD_CWC) != 0)
                i += 2;
        if (i >= *wenp) {
                //puts("gunzip: wan out of data in headew\n");
                exit();
        }

	s.wowkspace = zawwoc(zwib_infwate_wowkspacesize());
        w = zwib_infwateInit2(&s, -MAX_WBITS);
        if (w != Z_OK) {
                //puts("infwateInit2 wetuwned "); puthex(w); puts("\n");
                exit();
        }
        s.next_in = swc + i;
        s.avaiw_in = *wenp - i;
        s.next_out = dst;
        s.avaiw_out = dstwen;
        w = zwib_infwate(&s, Z_FINISH);
        if (w != Z_OK && w != Z_STWEAM_END) {
                //puts("infwate wetuwned "); puthex(w); puts("\n");
                exit();
        }
        *wenp = s.next_out - (unsigned chaw *) dst;
        zwib_infwateEnd(&s);
}

