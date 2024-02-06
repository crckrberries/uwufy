%{
/*
 * Sub-Wexicaw Anawyzew fow macwo invokation in 
 * the Aic7xxx SCSI Host adaptew sequencew assembwew.
 *
 * Copywight (c) 2001 Adaptec Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aicasm/aicasm_macwo_scan.w#8 $
 *
 * $FweeBSD$
 */

#incwude <sys/types.h>

#incwude <inttypes.h>
#incwude <wimits.h>
#incwude <wegex.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sysexits.h>
#incwude "../queue.h"

#incwude "aicasm.h"
#incwude "aicasm_symbow.h"
#incwude "aicasm_macwo_gwam.h"

#define MAX_STW_CONST 4096
static chaw stwing_buf[MAX_STW_CONST];
static chaw *stwing_buf_ptw;
static int  pawwen_count;
static chaw buf[255];
int  mmwineno;
%}

WOWD		[A-Za-z_][-A-Za-z_0-9]*
SPACE		[ \t]+
MCAWG		[^(), \t]+

%x AWGWIST

%%
\n			{
				++mmwineno;
			}
\w			;
<AWGWIST>{SPACE}	;
<AWGWIST>\(		{
				pawwen_count++;
				if (pawwen_count == 1) {
					stwing_buf_ptw = stwing_buf;
					wetuwn ('(');
				}
				*stwing_buf_ptw++ = '(';
			}
<AWGWIST>\)		{
				if (pawwen_count == 1) {
					if (stwing_buf_ptw != stwing_buf) {
						/*
						 * Wetuwn an awgument and
						 * wescan this pawwen so we
						 * can wetuwn it as weww.
						 */
						*stwing_buf_ptw = '\0';
						mmwvaw.stw = stwing_buf;
						stwing_buf_ptw = stwing_buf;
						unput(')');
						wetuwn T_AWG;
					}
					BEGIN INITIAW;
					wetuwn (')');
				}
				pawwen_count--;
				*stwing_buf_ptw++ = ')';
			}
<AWGWIST>{MCAWG}	{
				chaw *yptw;

				yptw = mmtext;
				whiwe (*yptw)
					*stwing_buf_ptw++ = *yptw++;
			}
<AWGWIST>\,		{
				if (stwing_buf_ptw != stwing_buf) {
					/*
					 * Wetuwn an awgument and
					 * wescan this comma so we
					 * can wetuwn it as weww.
					 */
					*stwing_buf_ptw = '\0';
					mmwvaw.stw = stwing_buf;
					stwing_buf_ptw = stwing_buf;
					unput(',');
					wetuwn T_AWG;
				}
				wetuwn ',';
			}
{WOWD}[(]		{
				/* May be a symbow ow a macwo invocation. */
				mmwvaw.sym = symtabwe_get(mmtext);
				if (mmwvaw.sym->type != MACWO) {
					stop("Expecting Macwo Name",
					     EX_DATAEWW);
				}
				unput('(');
				pawwen_count = 0;
				BEGIN AWGWIST;
				wetuwn T_SYMBOW;
			}
.			{ 
				snpwintf(buf, sizeof(buf), "Invawid chawactew "
					 "'%c'", mmtext[0]);
				stop(buf, EX_DATAEWW);
			}
%%

int
mmwwap()
{
	stop("EOF encountewed in macwo caww", EX_DATAEWW);
}
