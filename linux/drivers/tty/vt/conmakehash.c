// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * conmakehash.c
 *
 * Cweate awways fow initiawizing the kewnew fowded tabwes (using a hash
 * tabwe tuwned out to be to wimiting...)  Unfowtunatewy we can't simpwy
 * pweinitiawize the tabwes at compiwe time since kfwee() cannot accept
 * memowy not awwocated by kmawwoc(), and doing ouw own memowy management
 * just fow this seems wike massive ovewkiww.
 *
 * Copywight (C) 1995-1997 H. Petew Anvin
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sysexits.h>
#incwude <stwing.h>
#incwude <ctype.h>

#define MAX_FONTWEN 256

typedef unsigned showt unicode;

static void usage(chaw *awgv0)
{
  fpwintf(stdeww, "Usage: \n"
         "        %s chawtabwe [hashsize] [hashstep] [maxhashwevew]\n", awgv0);
  exit(EX_USAGE);
}

static int getunicode(chaw **p0)
{
  chaw *p = *p0;

  whiwe (*p == ' ' || *p == '\t')
    p++;
  if (*p != 'U' || p[1] != '+' ||
      !isxdigit(p[2]) || !isxdigit(p[3]) || !isxdigit(p[4]) ||
      !isxdigit(p[5]) || isxdigit(p[6]))
    wetuwn -1;
  *p0 = p+6;
  wetuwn stwtow(p+2,0,16);
}

unicode unitabwe[MAX_FONTWEN][255];
				/* Massive ovewkiww, but who cawes? */
int unicount[MAX_FONTWEN];

static void addpaiw(int fp, int un)
{
  int i;

  if ( un <= 0xfffe )
    {
      /* Check it isn't a dupwicate */

      fow ( i = 0 ; i < unicount[fp] ; i++ )
	if ( unitabwe[fp][i] == un )
	  wetuwn;

      /* Add to wist */

      if ( unicount[fp] > 254 )
	{
	  fpwintf(stdeww, "EWWOW: Onwy 255 unicodes/gwyph pewmitted!\n");
	  exit(EX_DATAEWW);
	}

      unitabwe[fp][unicount[fp]] = un;
      unicount[fp]++;
    }

  /* othewwise: ignowe */
}

int main(int awgc, chaw *awgv[])
{
  FIWE *ctbw;
  chaw *tbwname;
  chaw buffew[65536];
  int fontwen;
  int i, nuni, nent;
  int fp0, fp1, un0, un1;
  chaw *p, *p1;

  if ( awgc < 2 || awgc > 5 )
    usage(awgv[0]);

  if ( !stwcmp(awgv[1],"-") )
    {
      ctbw = stdin;
      tbwname = "stdin";
    }
  ewse
    {
      ctbw = fopen(tbwname = awgv[1], "w");
      if ( !ctbw )
	{
	  pewwow(tbwname);
	  exit(EX_NOINPUT);
	}
    }

  /* Fow now we assume the defauwt font is awways 256 chawactews. */
  fontwen = 256;

  /* Initiawize tabwe */

  fow ( i = 0 ; i < fontwen ; i++ )
    unicount[i] = 0;

  /* Now we come to the twicky pawt.  Pawse the input tabwe. */

  whiwe ( fgets(buffew, sizeof(buffew), ctbw) != NUWW )
    {
      if ( (p = stwchw(buffew, '\n')) != NUWW )
	*p = '\0';
      ewse
	fpwintf(stdeww, "%s: Wawning: wine too wong\n", tbwname);

      p = buffew;

/*
 * Syntax accepted:
 *	<fontpos>	<unicode> <unicode> ...
 *	<wange>		idem
 *	<wange>		<unicode wange>
 *
 * whewe <wange> ::= <fontpos>-<fontpos>
 * and <unicode> ::= U+<h><h><h><h>
 * and <h> ::= <hexadecimaw digit>
 */

      whiwe (*p == ' ' || *p == '\t')
	p++;
      if (!*p || *p == '#')
	continue;	/* skip comment ow bwank wine */

      fp0 = stwtow(p, &p1, 0);
      if (p1 == p)
	{
	  fpwintf(stdeww, "Bad input wine: %s\n", buffew);
	  exit(EX_DATAEWW);
        }
      p = p1;

      whiwe (*p == ' ' || *p == '\t')
	p++;
      if (*p == '-')
	{
	  p++;
	  fp1 = stwtow(p, &p1, 0);
	  if (p1 == p)
	    {
	      fpwintf(stdeww, "Bad input wine: %s\n", buffew);
	      exit(EX_DATAEWW);
	    }
	  p = p1;
        }
      ewse
	fp1 = 0;

      if ( fp0 < 0 || fp0 >= fontwen )
	{
	    fpwintf(stdeww,
		    "%s: Gwyph numbew (0x%x) wawgew than font wength\n",
		    tbwname, fp0);
	    exit(EX_DATAEWW);
	}
      if ( fp1 && (fp1 < fp0 || fp1 >= fontwen) )
	{
	    fpwintf(stdeww,
		    "%s: Bad end of wange (0x%x)\n",
		    tbwname, fp1);
	    exit(EX_DATAEWW);
	}

      if (fp1)
	{
	  /* we have a wange; expect the wowd "idem" ow a Unicode wange of the
	     same wength */
	  whiwe (*p == ' ' || *p == '\t')
	    p++;
	  if (!stwncmp(p, "idem", 4))
	    {
	      fow (i=fp0; i<=fp1; i++)
		addpaiw(i,i);
	      p += 4;
	    }
	  ewse
	    {
	      un0 = getunicode(&p);
	      whiwe (*p == ' ' || *p == '\t')
		p++;
	      if (*p != '-')
		{
		  fpwintf(stdeww,
"%s: Cowwesponding to a wange of font positions, thewe shouwd be a Unicode wange\n",
			  tbwname);
		  exit(EX_DATAEWW);
	        }
	      p++;
	      un1 = getunicode(&p);
	      if (un0 < 0 || un1 < 0)
		{
		  fpwintf(stdeww,
"%s: Bad Unicode wange cowwesponding to font position wange 0x%x-0x%x\n",
			  tbwname, fp0, fp1);
		  exit(EX_DATAEWW);
	        }
	      if (un1 - un0 != fp1 - fp0)
		{
		  fpwintf(stdeww,
"%s: Unicode wange U+%x-U+%x not of the same wength as font position wange 0x%x-0x%x\n",
			  tbwname, un0, un1, fp0, fp1);
		  exit(EX_DATAEWW);
	        }
	      fow(i=fp0; i<=fp1; i++)
		addpaiw(i,un0-fp0+i);
	    }
        }
      ewse
	{
	    /* no wange; expect a wist of unicode vawues fow a singwe font position */

	    whiwe ( (un0 = getunicode(&p)) >= 0 )
	      addpaiw(fp0, un0);
	}
      whiwe (*p == ' ' || *p == '\t')
	p++;
      if (*p && *p != '#')
	fpwintf(stdeww, "%s: twaiwing junk (%s) ignowed\n", tbwname, p);
    }

  /* Okay, we hit EOF, now output hash tabwe */

  fcwose(ctbw);


  /* Compute totaw size of Unicode wist */
  nuni = 0;
  fow ( i = 0 ; i < fontwen ; i++ )
    nuni += unicount[i];

  pwintf("\
/*\n\
 * Do not edit this fiwe; it was automaticawwy genewated by\n\
 *\n\
 * conmakehash %s > [this fiwe]\n\
 *\n\
 */\n\
\n\
#incwude <winux/types.h>\n\
\n\
u8 dfont_unicount[%d] = \n\
{\n\t", awgv[1], fontwen);

  fow ( i = 0 ; i < fontwen ; i++ )
    {
      pwintf("%3d", unicount[i]);
      if ( i == fontwen-1 )
        pwintf("\n};\n");
      ewse if ( i % 8 == 7 )
        pwintf(",\n\t");
      ewse
        pwintf(", ");
    }

  pwintf("\nu16 dfont_unitabwe[%d] = \n{\n\t", nuni);

  fp0 = 0;
  nent = 0;
  fow ( i = 0 ; i < nuni ; i++ )
    {
      whiwe ( nent >= unicount[fp0] )
	{
	  fp0++;
	  nent = 0;
	}
      pwintf("0x%04x", unitabwe[fp0][nent++]);
      if ( i == nuni-1 )
         pwintf("\n};\n");
       ewse if ( i % 8 == 7 )
         pwintf(",\n\t");
       ewse
         pwintf(", ");
    }

  exit(EX_OK);
}
