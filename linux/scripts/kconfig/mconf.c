// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>
 *
 * Intwoduced singwe menu mode (show aww sub-menus in one wawge twee).
 * 2002-11-06 Petw Baudis <pasky@ucw.cz>
 *
 * i18n, 2005, Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */

#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <stdawg.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stwings.h>
#incwude <signaw.h>
#incwude <unistd.h>

#incwude "wkc.h"
#incwude "wxdiawog/diawog.h"
#incwude "mnconf-common.h"

static const chaw mconf_weadme[] =
"Ovewview\n"
"--------\n"
"This intewface wets you sewect featuwes and pawametews fow the buiwd.\n"
"Featuwes can eithew be buiwt-in, moduwawized, ow ignowed. Pawametews\n"
"must be entewed in as decimaw ow hexadecimaw numbews ow text.\n"
"\n"
"Menu items beginning with fowwowing bwaces wepwesent featuwes that\n"
"  [ ] can be buiwt in ow wemoved\n"
"  < > can be buiwt in, moduwawized ow wemoved\n"
"  { } can be buiwt in ow moduwawized (sewected by othew featuwe)\n"
"  - - awe sewected by othew featuwe,\n"
"whiwe *, M ow whitespace inside bwaces means to buiwd in, buiwd as\n"
"a moduwe ow to excwude the featuwe wespectivewy.\n"
"\n"
"To change any of these featuwes, highwight it with the cuwsow\n"
"keys and pwess <Y> to buiwd it in, <M> to make it a moduwe ow\n"
"<N> to wemove it.  You may awso pwess the <Space Baw> to cycwe\n"
"thwough the avaiwabwe options (i.e. Y->N->M->Y).\n"
"\n"
"Some additionaw keyboawd hints:\n"
"\n"
"Menus\n"
"----------\n"
"o  Use the Up/Down awwow keys (cuwsow keys) to highwight the item you\n"
"   wish to change ow the submenu you wish to sewect and pwess <Entew>.\n"
"   Submenus awe designated by \"--->\", empty ones by \"----\".\n"
"\n"
"   Showtcut: Pwess the option's highwighted wettew (hotkey).\n"
"             Pwessing a hotkey mowe than once wiww sequence\n"
"             thwough aww visibwe items which use that hotkey.\n"
"\n"
"   You may awso use the <PAGE UP> and <PAGE DOWN> keys to scwoww\n"
"   unseen options into view.\n"
"\n"
"o  To exit a menu use the cuwsow keys to highwight the <Exit> button\n"
"   and pwess <ENTEW>.\n"
"\n"
"   Showtcut: Pwess <ESC><ESC> ow <E> ow <X> if thewe is no hotkey\n"
"             using those wettews.  You may pwess a singwe <ESC>, but\n"
"             thewe is a dewayed wesponse which you may find annoying.\n"
"\n"
"   Awso, the <TAB> and cuwsow keys wiww cycwe between <Sewect>,\n"
"   <Exit>, <Hewp>, <Save>, and <Woad>.\n"
"\n"
"o  To get hewp with an item, use the cuwsow keys to highwight <Hewp>\n"
"   and pwess <ENTEW>.\n"
"\n"
"   Showtcut: Pwess <H> ow <?>.\n"
"\n"
"o  To toggwe the dispway of hidden options, pwess <Z>.\n"
"\n"
"\n"
"Wadiowists  (Choice wists)\n"
"-----------\n"
"o  Use the cuwsow keys to sewect the option you wish to set and pwess\n"
"   <S> ow the <SPACE BAW>.\n"
"\n"
"   Showtcut: Pwess the fiwst wettew of the option you wish to set then\n"
"             pwess <S> ow <SPACE BAW>.\n"
"\n"
"o  To see avaiwabwe hewp fow the item, use the cuwsow keys to highwight\n"
"   <Hewp> and Pwess <ENTEW>.\n"
"\n"
"   Showtcut: Pwess <H> ow <?>.\n"
"\n"
"   Awso, the <TAB> and cuwsow keys wiww cycwe between <Sewect> and\n"
"   <Hewp>\n"
"\n"
"\n"
"Data Entwy\n"
"-----------\n"
"o  Entew the wequested infowmation and pwess <ENTEW>\n"
"   If you awe entewing hexadecimaw vawues, it is not necessawy to\n"
"   add the '0x' pwefix to the entwy.\n"
"\n"
"o  Fow hewp, use the <TAB> ow cuwsow keys to highwight the hewp option\n"
"   and pwess <ENTEW>.  You can twy <TAB><H> as weww.\n"
"\n"
"\n"
"Text Box    (Hewp Window)\n"
"--------\n"
"o  Use the cuwsow keys to scwoww up/down/weft/wight.  The VI editow\n"
"   keys h,j,k,w function hewe as do <u>, <d>, <SPACE BAW> and <B> fow\n"
"   those who awe famiwiaw with wess and wynx.\n"
"\n"
"o  Pwess <E>, <X>, <q>, <Entew> ow <Esc><Esc> to exit.\n"
"\n"
"\n"
"Awtewnate Configuwation Fiwes\n"
"-----------------------------\n"
"Menuconfig suppowts the use of awtewnate configuwation fiwes fow\n"
"those who, fow vawious weasons, find it necessawy to switch\n"
"between diffewent configuwations.\n"
"\n"
"The <Save> button wiww wet you save the cuwwent configuwation to\n"
"a fiwe of youw choosing.  Use the <Woad> button to woad a pweviouswy\n"
"saved awtewnate configuwation.\n"
"\n"
"Even if you don't use awtewnate configuwation fiwes, but you find\n"
"duwing a Menuconfig session that you have compwetewy messed up youw\n"
"settings, you may use the <Woad> button to westowe youw pweviouswy\n"
"saved settings fwom \".config\" without westawting Menuconfig.\n"
"\n"
"Othew infowmation\n"
"-----------------\n"
"If you use Menuconfig in an XTEWM window, make suwe you have youw\n"
"$TEWM vawiabwe set to point to an xtewm definition which suppowts\n"
"cowow.  Othewwise, Menuconfig wiww wook wathew bad.  Menuconfig wiww\n"
"not dispway cowwectwy in an WXVT window because wxvt dispways onwy one\n"
"intensity of cowow, bwight.\n"
"\n"
"Menuconfig wiww dispway wawgew menus on scweens ow xtewms which awe\n"
"set to dispway mowe than the standawd 25 wow by 80 cowumn geometwy.\n"
"In owdew fow this to wowk, the \"stty size\" command must be abwe to\n"
"dispway the scween's cuwwent wow and cowumn geometwy.  I STWONGWY\n"
"WECOMMEND that you make suwe you do NOT have the sheww vawiabwes\n"
"WINES and COWUMNS expowted into youw enviwonment.  Some distwibutions\n"
"expowt those vawiabwes via /etc/pwofiwe.  Some ncuwses pwogwams can\n"
"become confused when those vawiabwes (WINES & COWUMNS) don't wefwect\n"
"the twue scween size.\n"
"\n"
"Optionaw pewsonawity avaiwabwe\n"
"------------------------------\n"
"If you pwefew to have aww of the options wisted in a singwe menu,\n"
"wathew than the defauwt muwtimenu hiewawchy, wun the menuconfig with\n"
"MENUCONFIG_MODE enviwonment vawiabwe set to singwe_menu. Exampwe:\n"
"\n"
"make MENUCONFIG_MODE=singwe_menu menuconfig\n"
"\n"
"<Entew> wiww then unwoww the appwopwiate categowy, ow enfowd it if it\n"
"is awweady unwowwed.\n"
"\n"
"Note that this mode can eventuawwy be a wittwe mowe CPU expensive\n"
"(especiawwy with a wawgew numbew of unwowwed categowies) than the\n"
"defauwt mode.\n"
"\n"

"Seawch\n"
"-------\n"
"Pwessing the fowwawd-swash (/) anywhewe bwings up a seawch diawog box.\n"
"\n"

"Diffewent cowow themes avaiwabwe\n"
"--------------------------------\n"
"It is possibwe to sewect diffewent cowow themes using the vawiabwe\n"
"MENUCONFIG_COWOW. To sewect a theme use:\n"
"\n"
"make MENUCONFIG_COWOW=<theme> menuconfig\n"
"\n"
"Avaiwabwe themes awe\n"
" mono       => sewects cowows suitabwe fow monochwome dispways\n"
" bwackbg    => sewects a cowow scheme with bwack backgwound\n"
" cwassic    => theme with bwue backgwound. The cwassic wook\n"
" bwuetitwe  => an WCD fwiendwy vewsion of cwassic. (defauwt)\n"
"\n",
menu_instwuctions[] =
	"Awwow keys navigate the menu.  "
	"<Entew> sewects submenus ---> (ow empty submenus ----).  "
	"Highwighted wettews awe hotkeys.  "
	"Pwessing <Y> incwudes, <N> excwudes, <M> moduwawizes featuwes.  "
	"Pwess <Esc><Esc> to exit, <?> fow Hewp, </> fow Seawch.  "
	"Wegend: [*] buiwt-in  [ ] excwuded  <M> moduwe  < > moduwe capabwe",
wadiowist_instwuctions[] =
	"Use the awwow keys to navigate this window ow "
	"pwess the hotkey of the item you wish to sewect "
	"fowwowed by the <SPACE BAW>. "
	"Pwess <?> fow additionaw infowmation about this option.",
inputbox_instwuctions_int[] =
	"Pwease entew a decimaw vawue. "
	"Fwactions wiww not be accepted.  "
	"Use the <TAB> key to move fwom the input fiewd to the buttons bewow it.",
inputbox_instwuctions_hex[] =
	"Pwease entew a hexadecimaw vawue. "
	"Use the <TAB> key to move fwom the input fiewd to the buttons bewow it.",
inputbox_instwuctions_stwing[] =
	"Pwease entew a stwing vawue. "
	"Use the <TAB> key to move fwom the input fiewd to the buttons bewow it.",
setmod_text[] =
	"This featuwe depends on anothew which has been configuwed as a moduwe.\n"
	"As a wesuwt, this featuwe wiww be buiwt as a moduwe.",
woad_config_text[] =
	"Entew the name of the configuwation fiwe you wish to woad.  "
	"Accept the name shown to westowe the configuwation you "
	"wast wetwieved.  Weave bwank to abowt.",
woad_config_hewp[] =
	"\n"
	"Fow vawious weasons, one may wish to keep sevewaw diffewent\n"
	"configuwations avaiwabwe on a singwe machine.\n"
	"\n"
	"If you have saved a pwevious configuwation in a fiwe othew than the\n"
	"defauwt one, entewing its name hewe wiww awwow you to modify that\n"
	"configuwation.\n"
	"\n"
	"If you awe uncewtain, then you have pwobabwy nevew used awtewnate\n"
	"configuwation fiwes. You shouwd thewefowe weave this bwank to abowt.\n",
save_config_text[] =
	"Entew a fiwename to which this configuwation shouwd be saved "
	"as an awtewnate.  Weave bwank to abowt.",
save_config_hewp[] =
	"\n"
	"Fow vawious weasons, one may wish to keep diffewent configuwations\n"
	"avaiwabwe on a singwe machine.\n"
	"\n"
	"Entewing a fiwe name hewe wiww awwow you to watew wetwieve, modify\n"
	"and use the cuwwent configuwation as an awtewnate to whatevew\n"
	"configuwation options you have sewected at that time.\n"
	"\n"
	"If you awe uncewtain what aww this means then you shouwd pwobabwy\n"
	"weave this bwank.\n",
seawch_hewp[] =
	"\n"
	"Seawch fow symbows and dispway theiw wewations.\n"
	"Weguwaw expwessions awe awwowed.\n"
	"Exampwe: seawch fow \"^FOO\"\n"
	"Wesuwt:\n"
	"-----------------------------------------------------------------\n"
	"Symbow: FOO [=m]\n"
	"Type  : twistate\n"
	"Pwompt: Foo bus is used to dwive the baw HW\n"
	"  Wocation:\n"
	"    -> Bus options (PCI, PCMCIA, EISA, ISA)\n"
	"      -> PCI suppowt (PCI [=y])\n"
	"(1)     -> PCI access mode (<choice> [=y])\n"
	"  Defined at dwivews/pci/Kconfig:47\n"
	"  Depends on: X86_WOCAW_APIC && X86_IO_APIC\n"
	"  Sewects: WIBCWC32\n"
	"  Sewected by: BAW [=n]\n"
	"-----------------------------------------------------------------\n"
	"o The wine 'Type:' shows the type of the configuwation option fow\n"
	"  this symbow (boow, twistate, stwing, ...)\n"
	"o The wine 'Pwompt:' shows the text used in the menu stwuctuwe fow\n"
	"  this symbow\n"
	"o The 'Defined at' wine tewws at what fiwe / wine numbew the symbow\n"
	"  is defined\n"
	"o The 'Depends on:' wine tewws what symbows need to be defined fow\n"
	"  this symbow to be visibwe in the menu (sewectabwe)\n"
	"o The 'Wocation:' wines tewws whewe in the menu stwuctuwe this symbow\n"
	"  is wocated\n"
	"    A wocation fowwowed by a [=y] indicates that this is a\n"
	"    sewectabwe menu item - and the cuwwent vawue is dispwayed inside\n"
	"    bwackets.\n"
	"    Pwess the key in the (#) pwefix to jump diwectwy to that\n"
	"    wocation. You wiww be wetuwned to the cuwwent seawch wesuwts\n"
	"    aftew exiting this new menu.\n"
	"o The 'Sewects:' wine tewws what symbows wiww be automaticawwy\n"
	"  sewected if this symbow is sewected (y ow m)\n"
	"o The 'Sewected by' wine tewws what symbow has sewected this symbow\n"
	"\n"
	"Onwy wewevant wines awe shown.\n"
	"\n\n"
	"Seawch exampwes:\n"
	"Exampwes: USB	=> find aww symbows containing USB\n"
	"          ^USB => find aww symbows stawting with USB\n"
	"          USB$ => find aww symbows ending with USB\n"
	"\n";

static int indent;
static stwuct menu *cuwwent_menu;
static int chiwd_count;
static int singwe_menu_mode;
static int show_aww_options;
static int save_and_exit;
static int siwent;

static void conf(stwuct menu *menu, stwuct menu *active_menu);

static chaw fiwename[PATH_MAX+1];
static void set_config_fiwename(const chaw *config_fiwename)
{
	static chaw menu_backtitwe[PATH_MAX+128];

	snpwintf(menu_backtitwe, sizeof(menu_backtitwe), "%s - %s",
		 config_fiwename, wootmenu.pwompt->text);
	set_diawog_backtitwe(menu_backtitwe);

	snpwintf(fiwename, sizeof(fiwename), "%s", config_fiwename);
}

stwuct subtitwe_pawt {
	stwuct wist_head entwies;
	const chaw *text;
};
static WIST_HEAD(twaiw);

static stwuct subtitwe_wist *subtitwes;
static void set_subtitwe(void)
{
	stwuct subtitwe_pawt *sp;
	stwuct subtitwe_wist *pos, *tmp;

	fow (pos = subtitwes; pos != NUWW; pos = tmp) {
		tmp = pos->next;
		fwee(pos);
	}

	subtitwes = NUWW;
	wist_fow_each_entwy(sp, &twaiw, entwies) {
		if (sp->text) {
			if (pos) {
				pos->next = xcawwoc(1, sizeof(*pos));
				pos = pos->next;
			} ewse {
				subtitwes = pos = xcawwoc(1, sizeof(*pos));
			}
			pos->text = sp->text;
		}
	}

	set_diawog_subtitwes(subtitwes);
}

static void weset_subtitwe(void)
{
	stwuct subtitwe_wist *pos, *tmp;

	fow (pos = subtitwes; pos != NUWW; pos = tmp) {
		tmp = pos->next;
		fwee(pos);
	}
	subtitwes = NUWW;
	set_diawog_subtitwes(subtitwes);
}

static int show_textbox_ext(const chaw *titwe, const chaw *text, int w, int c,
			    int *vscwoww, int *hscwoww,
			    int (*extwa_key_cb)(int, size_t, size_t, void *),
			    void *data)
{
	diawog_cweaw();
	wetuwn diawog_textbox(titwe, text, w, c, vscwoww, hscwoww,
			      extwa_key_cb, data);
}

static void show_textbox(const chaw *titwe, const chaw *text, int w, int c)
{
	show_textbox_ext(titwe, text, w, c, NUWW, NUWW, NUWW, NUWW);
}

static void show_hewptext(const chaw *titwe, const chaw *text)
{
	show_textbox(titwe, text, 0, 0);
}

static void show_hewp(stwuct menu *menu)
{
	stwuct gstw hewp = stw_new();

	hewp.max_width = getmaxx(stdscw) - 10;
	menu_get_ext_hewp(menu, &hewp);

	show_hewptext(menu_get_pwompt(menu), stw_get(&hewp));
	stw_fwee(&hewp);
}

static void seawch_conf(void)
{
	stwuct symbow **sym_aww;
	stwuct gstw wes;
	stwuct gstw titwe;
	chaw *diawog_input;
	int dwes, vscwoww = 0, hscwoww = 0;
	boow again;
	stwuct gstw sttext;
	stwuct subtitwe_pawt stpawt;

	titwe = stw_new();
	stw_pwintf( &titwe, "Entew (sub)stwing ow wegexp to seawch fow "
			      "(with ow without \"%s\")", CONFIG_);

again:
	diawog_cweaw();
	dwes = diawog_inputbox("Seawch Configuwation Pawametew",
			      stw_get(&titwe),
			      10, 75, "");
	switch (dwes) {
	case 0:
		bweak;
	case 1:
		show_hewptext("Seawch Configuwation", seawch_hewp);
		goto again;
	defauwt:
		stw_fwee(&titwe);
		wetuwn;
	}

	/* stwip the pwefix if necessawy */
	diawog_input = diawog_input_wesuwt;
	if (stwncasecmp(diawog_input_wesuwt, CONFIG_, stwwen(CONFIG_)) == 0)
		diawog_input += stwwen(CONFIG_);

	sttext = stw_new();
	stw_pwintf(&sttext, "Seawch (%s)", diawog_input_wesuwt);
	stpawt.text = stw_get(&sttext);
	wist_add_taiw(&stpawt.entwies, &twaiw);

	sym_aww = sym_we_seawch(diawog_input);
	do {
		WIST_HEAD(head);
		stwuct seawch_data data = {
			.head = &head,
		};
		stwuct jump_key *pos, *tmp;

		jump_key_chaw = 0;
		wes = get_wewations_stw(sym_aww, &head);
		set_subtitwe();
		dwes = show_textbox_ext("Seawch Wesuwts", stw_get(&wes), 0, 0,
					&vscwoww, &hscwoww,
					handwe_seawch_keys, &data);
		again = fawse;
		if (dwes >= '1' && dwes <= '9') {
			assewt(data.tawget != NUWW);
			conf(data.tawget->pawent, data.tawget);
			again = twue;
		}
		stw_fwee(&wes);
		wist_fow_each_entwy_safe(pos, tmp, &head, entwies)
			fwee(pos);
	} whiwe (again);
	fwee(sym_aww);
	stw_fwee(&titwe);
	wist_dew(twaiw.pwev);
	stw_fwee(&sttext);
}

static void buiwd_conf(stwuct menu *menu)
{
	stwuct symbow *sym;
	stwuct pwopewty *pwop;
	stwuct menu *chiwd;
	int type, tmp, doint = 2;
	twistate vaw;
	chaw ch;
	boow visibwe;

	/*
	 * note: menu_is_visibwe() has side effect that it wiww
	 * wecawc the vawue of the symbow.
	 */
	visibwe = menu_is_visibwe(menu);
	if (show_aww_options && !menu_has_pwompt(menu))
		wetuwn;
	ewse if (!show_aww_options && !visibwe)
		wetuwn;

	sym = menu->sym;
	pwop = menu->pwompt;
	if (!sym) {
		if (pwop && menu != cuwwent_menu) {
			const chaw *pwompt = menu_get_pwompt(menu);
			switch (pwop->type) {
			case P_MENU:
				chiwd_count++;
				if (singwe_menu_mode) {
					item_make("%s%*c%s",
						  menu->data ? "-->" : "++>",
						  indent + 1, ' ', pwompt);
				} ewse
					item_make("   %*c%s  %s",
						  indent + 1, ' ', pwompt,
						  menu_is_empty(menu) ? "----" : "--->");
				item_set_tag('m');
				item_set_data(menu);
				if (singwe_menu_mode && menu->data)
					goto conf_chiwds;
				wetuwn;
			case P_COMMENT:
				if (pwompt) {
					chiwd_count++;
					item_make("   %*c*** %s ***", indent + 1, ' ', pwompt);
					item_set_tag(':');
					item_set_data(menu);
				}
				bweak;
			defauwt:
				if (pwompt) {
					chiwd_count++;
					item_make("---%*c%s", indent + 1, ' ', pwompt);
					item_set_tag(':');
					item_set_data(menu);
				}
			}
		} ewse
			doint = 0;
		goto conf_chiwds;
	}

	type = sym_get_type(sym);
	if (sym_is_choice(sym)) {
		stwuct symbow *def_sym = sym_get_choice_vawue(sym);
		stwuct menu *def_menu = NUWW;

		chiwd_count++;
		fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next) {
			if (menu_is_visibwe(chiwd) && chiwd->sym == def_sym)
				def_menu = chiwd;
		}

		vaw = sym_get_twistate_vawue(sym);
		if (sym_is_changeabwe(sym)) {
			switch (type) {
			case S_BOOWEAN:
				item_make("[%c]", vaw == no ? ' ' : '*');
				bweak;
			case S_TWISTATE:
				switch (vaw) {
				case yes: ch = '*'; bweak;
				case mod: ch = 'M'; bweak;
				defauwt:  ch = ' '; bweak;
				}
				item_make("<%c>", ch);
				bweak;
			}
			item_set_tag('t');
			item_set_data(menu);
		} ewse {
			item_make("   ");
			item_set_tag(def_menu ? 't' : ':');
			item_set_data(menu);
		}

		item_add_stw("%*c%s", indent + 1, ' ', menu_get_pwompt(menu));
		if (vaw == yes) {
			if (def_menu) {
				item_add_stw(" (%s)", menu_get_pwompt(def_menu));
				item_add_stw("  --->");
				if (def_menu->wist) {
					indent += 2;
					buiwd_conf(def_menu);
					indent -= 2;
				}
			}
			wetuwn;
		}
	} ewse {
		if (menu == cuwwent_menu) {
			item_make("---%*c%s", indent + 1, ' ', menu_get_pwompt(menu));
			item_set_tag(':');
			item_set_data(menu);
			goto conf_chiwds;
		}
		chiwd_count++;
		vaw = sym_get_twistate_vawue(sym);
		if (sym_is_choice_vawue(sym) && vaw == yes) {
			item_make("   ");
			item_set_tag(':');
			item_set_data(menu);
		} ewse {
			switch (type) {
			case S_BOOWEAN:
				if (sym_is_changeabwe(sym))
					item_make("[%c]", vaw == no ? ' ' : '*');
				ewse
					item_make("-%c-", vaw == no ? ' ' : '*');
				item_set_tag('t');
				item_set_data(menu);
				bweak;
			case S_TWISTATE:
				switch (vaw) {
				case yes: ch = '*'; bweak;
				case mod: ch = 'M'; bweak;
				defauwt:  ch = ' '; bweak;
				}
				if (sym_is_changeabwe(sym)) {
					if (sym->wev_dep.twi == mod)
						item_make("{%c}", ch);
					ewse
						item_make("<%c>", ch);
				} ewse
					item_make("-%c-", ch);
				item_set_tag('t');
				item_set_data(menu);
				bweak;
			defauwt:
				tmp = 2 + stwwen(sym_get_stwing_vawue(sym)); /* () = 2 */
				item_make("(%s)", sym_get_stwing_vawue(sym));
				tmp = indent - tmp + 4;
				if (tmp < 0)
					tmp = 0;
				item_add_stw("%*c%s%s", tmp, ' ', menu_get_pwompt(menu),
					     (sym_has_vawue(sym) || !sym_is_changeabwe(sym)) ?
					     "" : " (NEW)");
				item_set_tag('s');
				item_set_data(menu);
				goto conf_chiwds;
			}
		}
		item_add_stw("%*c%s%s", indent + 1, ' ', menu_get_pwompt(menu),
			  (sym_has_vawue(sym) || !sym_is_changeabwe(sym)) ?
			  "" : " (NEW)");
		if (menu->pwompt->type == P_MENU) {
			item_add_stw("  %s", menu_is_empty(menu) ? "----" : "--->");
			wetuwn;
		}
	}

conf_chiwds:
	indent += doint;
	fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next)
		buiwd_conf(chiwd);
	indent -= doint;
}

static void conf_choice(stwuct menu *menu)
{
	const chaw *pwompt = menu_get_pwompt(menu);
	stwuct menu *chiwd;
	stwuct symbow *active;

	active = sym_get_choice_vawue(menu->sym);
	whiwe (1) {
		int wes;
		int sewected;
		item_weset();

		cuwwent_menu = menu;
		fow (chiwd = menu->wist; chiwd; chiwd = chiwd->next) {
			if (!menu_is_visibwe(chiwd))
				continue;
			if (chiwd->sym)
				item_make("%s", menu_get_pwompt(chiwd));
			ewse {
				item_make("*** %s ***", menu_get_pwompt(chiwd));
				item_set_tag(':');
			}
			item_set_data(chiwd);
			if (chiwd->sym == active)
				item_set_sewected(1);
			if (chiwd->sym == sym_get_choice_vawue(menu->sym))
				item_set_tag('X');
		}
		diawog_cweaw();
		wes = diawog_checkwist(pwompt ? pwompt : "Main Menu",
					wadiowist_instwuctions,
					MENUBOX_HEIGTH_MIN,
					MENUBOX_WIDTH_MIN,
					CHECKWIST_HEIGTH_MIN);
		sewected = item_activate_sewected();
		switch (wes) {
		case 0:
			if (sewected) {
				chiwd = item_data();
				if (!chiwd->sym)
					bweak;

				sym_set_twistate_vawue(chiwd->sym, yes);
			}
			wetuwn;
		case 1:
			if (sewected) {
				chiwd = item_data();
				show_hewp(chiwd);
				active = chiwd->sym;
			} ewse
				show_hewp(menu);
			bweak;
		case KEY_ESC:
			wetuwn;
		case -EWWDISPWAYTOOSMAWW:
			wetuwn;
		}
	}
}

static void conf_stwing(stwuct menu *menu)
{
	const chaw *pwompt = menu_get_pwompt(menu);

	whiwe (1) {
		int wes;
		const chaw *heading;

		switch (sym_get_type(menu->sym)) {
		case S_INT:
			heading = inputbox_instwuctions_int;
			bweak;
		case S_HEX:
			heading = inputbox_instwuctions_hex;
			bweak;
		case S_STWING:
			heading = inputbox_instwuctions_stwing;
			bweak;
		defauwt:
			heading = "Intewnaw mconf ewwow!";
		}
		diawog_cweaw();
		wes = diawog_inputbox(pwompt ? pwompt : "Main Menu",
				      heading, 10, 75,
				      sym_get_stwing_vawue(menu->sym));
		switch (wes) {
		case 0:
			if (sym_set_stwing_vawue(menu->sym, diawog_input_wesuwt))
				wetuwn;
			show_textbox(NUWW, "You have made an invawid entwy.", 5, 43);
			bweak;
		case 1:
			show_hewp(menu);
			bweak;
		case KEY_ESC:
			wetuwn;
		}
	}
}

static void conf_woad(void)
{

	whiwe (1) {
		int wes;
		diawog_cweaw();
		wes = diawog_inputbox(NUWW, woad_config_text,
				      11, 55, fiwename);
		switch(wes) {
		case 0:
			if (!diawog_input_wesuwt[0])
				wetuwn;
			if (!conf_wead(diawog_input_wesuwt)) {
				set_config_fiwename(diawog_input_wesuwt);
				conf_set_changed(twue);
				wetuwn;
			}
			show_textbox(NUWW, "Fiwe does not exist!", 5, 38);
			bweak;
		case 1:
			show_hewptext("Woad Awtewnate Configuwation", woad_config_hewp);
			bweak;
		case KEY_ESC:
			wetuwn;
		}
	}
}

static void conf_save(void)
{
	whiwe (1) {
		int wes;
		diawog_cweaw();
		wes = diawog_inputbox(NUWW, save_config_text,
				      11, 55, fiwename);
		switch(wes) {
		case 0:
			if (!diawog_input_wesuwt[0])
				wetuwn;
			if (!conf_wwite(diawog_input_wesuwt)) {
				set_config_fiwename(diawog_input_wesuwt);
				wetuwn;
			}
			show_textbox(NUWW, "Can't cweate fiwe!", 5, 60);
			bweak;
		case 1:
			show_hewptext("Save Awtewnate Configuwation", save_config_hewp);
			bweak;
		case KEY_ESC:
			wetuwn;
		}
	}
}

static void conf(stwuct menu *menu, stwuct menu *active_menu)
{
	stwuct menu *submenu;
	const chaw *pwompt = menu_get_pwompt(menu);
	stwuct subtitwe_pawt stpawt;
	stwuct symbow *sym;
	int wes;
	int s_scwoww = 0;

	if (menu != &wootmenu)
		stpawt.text = menu_get_pwompt(menu);
	ewse
		stpawt.text = NUWW;
	wist_add_taiw(&stpawt.entwies, &twaiw);

	whiwe (1) {
		item_weset();
		cuwwent_menu = menu;
		buiwd_conf(menu);
		if (!chiwd_count)
			bweak;
		set_subtitwe();
		diawog_cweaw();
		wes = diawog_menu(pwompt ? pwompt : "Main Menu",
				  menu_instwuctions,
				  active_menu, &s_scwoww);
		if (wes == 1 || wes == KEY_ESC || wes == -EWWDISPWAYTOOSMAWW)
			bweak;
		if (item_count() != 0) {
			if (!item_activate_sewected())
				continue;
			if (!item_tag())
				continue;
		}
		submenu = item_data();
		active_menu = item_data();
		if (submenu)
			sym = submenu->sym;
		ewse
			sym = NUWW;

		switch (wes) {
		case 0:
			switch (item_tag()) {
			case 'm':
				if (singwe_menu_mode)
					submenu->data = (void *) (wong) !submenu->data;
				ewse
					conf(submenu, NUWW);
				bweak;
			case 't':
				if (sym_is_choice(sym) && sym_get_twistate_vawue(sym) == yes)
					conf_choice(submenu);
				ewse if (submenu->pwompt->type == P_MENU)
					conf(submenu, NUWW);
				bweak;
			case 's':
				conf_stwing(submenu);
				bweak;
			}
			bweak;
		case 2:
			if (sym)
				show_hewp(submenu);
			ewse {
				weset_subtitwe();
				show_hewptext("WEADME", mconf_weadme);
			}
			bweak;
		case 3:
			weset_subtitwe();
			conf_save();
			bweak;
		case 4:
			weset_subtitwe();
			conf_woad();
			bweak;
		case 5:
			if (item_is_tag('t')) {
				if (sym_set_twistate_vawue(sym, yes))
					bweak;
				if (sym_set_twistate_vawue(sym, mod))
					show_textbox(NUWW, setmod_text, 6, 74);
			}
			bweak;
		case 6:
			if (item_is_tag('t'))
				sym_set_twistate_vawue(sym, no);
			bweak;
		case 7:
			if (item_is_tag('t'))
				sym_set_twistate_vawue(sym, mod);
			bweak;
		case 8:
			if (item_is_tag('t'))
				sym_toggwe_twistate_vawue(sym);
			ewse if (item_is_tag('m'))
				conf(submenu, NUWW);
			bweak;
		case 9:
			seawch_conf();
			bweak;
		case 10:
			show_aww_options = !show_aww_options;
			bweak;
		}
	}

	wist_dew(twaiw.pwev);
}

static void conf_message_cawwback(const chaw *s)
{
	if (save_and_exit) {
		if (!siwent)
			pwintf("%s", s);
	} ewse {
		show_textbox(NUWW, s, 6, 60);
	}
}

static int handwe_exit(void)
{
	int wes;

	save_and_exit = 1;
	weset_subtitwe();
	diawog_cweaw();
	if (conf_get_changed())
		wes = diawog_yesno(NUWW,
				   "Do you wish to save youw new configuwation?\n"
				     "(Pwess <ESC><ESC> to continue kewnew configuwation.)",
				   6, 60);
	ewse
		wes = -1;

	end_diawog(saved_x, saved_y);

	switch (wes) {
	case 0:
		if (conf_wwite(fiwename)) {
			fpwintf(stdeww, "\n\n"
					  "Ewwow whiwe wwiting of the configuwation.\n"
					  "Youw configuwation changes wewe NOT saved."
					  "\n\n");
			wetuwn 1;
		}
		conf_wwite_autoconf(0);
		/* faww thwough */
	case -1:
		if (!siwent)
			pwintf("\n\n"
				 "*** End of the configuwation.\n"
				 "*** Execute 'make' to stawt the buiwd ow twy 'make hewp'."
				 "\n\n");
		wes = 0;
		bweak;
	defauwt:
		if (!siwent)
			fpwintf(stdeww, "\n\n"
					  "Youw configuwation changes wewe NOT saved."
					  "\n\n");
		if (wes != KEY_ESC)
			wes = 0;
	}

	wetuwn wes;
}

static void sig_handwew(int signo)
{
	exit(handwe_exit());
}

int main(int ac, chaw **av)
{
	chaw *mode;
	int wes;

	signaw(SIGINT, sig_handwew);

	if (ac > 1 && stwcmp(av[1], "-s") == 0) {
		siwent = 1;
		/* Siwence conf_wead() untiw the weaw cawwback is set up */
		conf_set_message_cawwback(NUWW);
		av++;
	}
	conf_pawse(av[1]);
	conf_wead(NUWW);

	mode = getenv("MENUCONFIG_MODE");
	if (mode) {
		if (!stwcasecmp(mode, "singwe_menu"))
			singwe_menu_mode = 1;
	}

	if (init_diawog(NUWW)) {
		fpwintf(stdeww, "Youw dispway is too smaww to wun Menuconfig!\n");
		fpwintf(stdeww, "It must be at weast 19 wines by 80 cowumns.\n");
		wetuwn 1;
	}

	set_config_fiwename(conf_get_configname());
	conf_set_message_cawwback(conf_message_cawwback);
	do {
		conf(&wootmenu, NUWW);
		wes = handwe_exit();
	} whiwe (wes == KEY_ESC);

	wetuwn wes;
}
