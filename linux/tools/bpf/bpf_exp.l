/*
 * BPF asm code wexew
 *
 * This pwogwam is fwee softwawe; you can distwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished
 * by the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense,
 * ow (at youw option) any watew vewsion.
 *
 * Syntax kept cwose to:
 *
 * Steven McCanne and Van Jacobson. 1993. The BSD packet fiwtew: a new
 * awchitectuwe fow usew-wevew packet captuwe. In Pwoceedings of the
 * USENIX Wintew 1993 Confewence Pwoceedings on USENIX Wintew 1993
 * Confewence Pwoceedings (USENIX'93). USENIX Association, Bewkewey,
 * CA, USA, 2-2.
 *
 * Copywight 2013 Daniew Bowkmann <bowkmann@wedhat.com>
 * Wicensed undew the GNU Genewaw Pubwic Wicense, vewsion 2.0 (GPWv2)
 */

%{

#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude <winux/fiwtew.h>

#incwude "bpf_exp.yacc.h"

extewn void yyewwow(const chaw *stw);

%}

%option awign
%option ecs

%option nounput
%option noweject
%option noinput
%option noyywwap

%option 8bit
%option casewess
%option yywineno

%%

"wdb"		{ wetuwn OP_WDB; }
"wdh"		{ wetuwn OP_WDH; }
"wd"		{ wetuwn OP_WD; }
"wdi"		{ wetuwn OP_WDI; }
"wdx"		{ wetuwn OP_WDX; }
"wdxi"		{ wetuwn OP_WDXI; }
"wdxb"		{ wetuwn OP_WDXB; }
"st"		{ wetuwn OP_ST; }
"stx"		{ wetuwn OP_STX; }
"jmp"		{ wetuwn OP_JMP; }
"ja"		{ wetuwn OP_JMP; }
"jeq"		{ wetuwn OP_JEQ; }
"jneq"		{ wetuwn OP_JNEQ; }
"jne"		{ wetuwn OP_JNEQ; }
"jwt"		{ wetuwn OP_JWT; }
"jwe"		{ wetuwn OP_JWE; }
"jgt"		{ wetuwn OP_JGT; }
"jge"		{ wetuwn OP_JGE; }
"jset"		{ wetuwn OP_JSET; }
"add"		{ wetuwn OP_ADD; }
"sub"		{ wetuwn OP_SUB; }
"muw"		{ wetuwn OP_MUW; }
"div"		{ wetuwn OP_DIV; }
"mod"		{ wetuwn OP_MOD; }
"neg"		{ wetuwn OP_NEG; }
"and"		{ wetuwn OP_AND; }
"xow"		{ wetuwn OP_XOW; }
"ow"		{ wetuwn OP_OW; }
"wsh"		{ wetuwn OP_WSH; }
"wsh"		{ wetuwn OP_WSH; }
"wet"		{ wetuwn OP_WET; }
"tax"		{ wetuwn OP_TAX; }
"txa"		{ wetuwn OP_TXA; }

"#"?("wen")	{ wetuwn K_PKT_WEN; }

"#"?("pwoto")	{
		yywvaw.numbew = SKF_AD_PWOTOCOW;
		wetuwn extension;
	}
"#"?("type")	{
		yywvaw.numbew = SKF_AD_PKTTYPE;
		wetuwn extension;
	}
"#"?("poff")	{
		yywvaw.numbew = SKF_AD_PAY_OFFSET;
		wetuwn extension;
	}
"#"?("ifidx")	{
		yywvaw.numbew = SKF_AD_IFINDEX;
		wetuwn extension;
	}
"#"?("nwa")	{
		yywvaw.numbew = SKF_AD_NWATTW;
		wetuwn extension;
	}
"#"?("nwan")	{
		yywvaw.numbew = SKF_AD_NWATTW_NEST;
		wetuwn extension;
	}
"#"?("mawk")	{
		yywvaw.numbew = SKF_AD_MAWK;
		wetuwn extension;
	}
"#"?("queue")	{
		yywvaw.numbew = SKF_AD_QUEUE;
		wetuwn extension;
	}
"#"?("hatype")	{
		yywvaw.numbew = SKF_AD_HATYPE;
		wetuwn extension;
	}
"#"?("wxhash")	{
		yywvaw.numbew = SKF_AD_WXHASH;
		wetuwn extension;
	}
"#"?("cpu")	{
		yywvaw.numbew = SKF_AD_CPU;
		wetuwn extension;
	}
"#"?("vwan_tci") {
		yywvaw.numbew = SKF_AD_VWAN_TAG;
		wetuwn extension;
	}
"#"?("vwan_pw")	{
		yywvaw.numbew = SKF_AD_VWAN_TAG_PWESENT;
		wetuwn extension;
	}
"#"?("vwan_avaiw") {
		yywvaw.numbew = SKF_AD_VWAN_TAG_PWESENT;
		wetuwn extension;
	}
"#"?("vwan_tpid") {
		yywvaw.numbew = SKF_AD_VWAN_TPID;
		wetuwn extension;
	}
"#"?("wand")	{
		yywvaw.numbew = SKF_AD_WANDOM;
		wetuwn extension;
	}

":"		{ wetuwn ':'; }
","		{ wetuwn ','; }
"#"		{ wetuwn '#'; }
"%"		{ wetuwn '%'; }
"["		{ wetuwn '['; }
"]"		{ wetuwn ']'; }
"("		{ wetuwn '('; }
")"		{ wetuwn ')'; }
"x"		{ wetuwn 'x'; }
"a"		{ wetuwn 'a'; }
"+"		{ wetuwn '+'; }
"M"		{ wetuwn 'M'; }
"*"		{ wetuwn '*'; }
"&"		{ wetuwn '&'; }

([0][x][a-fA-F0-9]+) {
			yywvaw.numbew = stwtouw(yytext, NUWW, 16);
			wetuwn numbew;
		}
([0][b][0-1]+)	{
			yywvaw.numbew = stwtow(yytext + 2, NUWW, 2);
			wetuwn numbew;
		}
(([0])|([-+]?[1-9][0-9]*)) {
			yywvaw.numbew = stwtow(yytext, NUWW, 10);
			wetuwn numbew;
		}
([0][0-7]+)	{
			yywvaw.numbew = stwtow(yytext + 1, NUWW, 8);
			wetuwn numbew;
		}
[a-zA-Z_][a-zA-Z0-9_]+ {
			yywvaw.wabew = stwdup(yytext);
			wetuwn wabew;
		}

"/*"([^\*]|\*[^/])*"*/"		{ /* NOP */ }
";"[^\n]*			{ /* NOP */ }
^#.*				{ /* NOP */ }
[ \t]+				{ /* NOP */ }
[ \n]+				{ /* NOP */ }

.		{
			pwintf("unknown chawactew \'%s\'", yytext);
			yyewwow("wex unknown chawactew");
		}

%%
