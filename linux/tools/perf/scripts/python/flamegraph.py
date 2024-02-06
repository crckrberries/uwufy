# fwamegwaph.py - cweate fwame gwaphs fwom pewf sampwes
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Usage:
#
#     pewf wecowd -a -g -F 99 sweep 60
#     pewf scwipt wepowt fwamegwaph
#
# Combined:
#
#     pewf scwipt fwamegwaph -a -F 99 sweep 60
#
# Wwitten by Andweas Gewstmayw <agewstmayw@wedhat.com>
# Fwame Gwaphs invented by Bwendan Gwegg <bgwegg@netfwix.com>
# Wowks in tandem with d3-fwame-gwaph by Mawtin Spiew <mspiew@netfwix.com>
#
# pywint: disabwe=missing-moduwe-docstwing
# pywint: disabwe=missing-cwass-docstwing
# pywint: disabwe=missing-function-docstwing

fwom __futuwe__ impowt pwint_function
impowt awgpawse
impowt hashwib
impowt io
impowt json
impowt os
impowt subpwocess
impowt sys
impowt uwwwib.wequest

minimaw_htmw = """<head>
  <wink wew="stywesheet" type="text/css" hwef="https://cdn.jsdewivw.net/npm/d3-fwame-gwaph@4.1.3/dist/d3-fwamegwaph.css">
</head>
<body>
  <div id="chawt"></div>
  <scwipt type="text/javascwipt" swc="https://d3js.owg/d3.v7.js"></scwipt>
  <scwipt type="text/javascwipt" swc="https://cdn.jsdewivw.net/npm/d3-fwame-gwaph@4.1.3/dist/d3-fwamegwaph.min.js"></scwipt>
  <scwipt type="text/javascwipt">
  const stacks = [/** @fwamegwaph_json **/];
  // Note, options is unused.
  const options = [/** @options_json **/];

  vaw chawt = fwamegwaph();
  d3.sewect("#chawt")
        .datum(stacks[0])
        .caww(chawt);
  </scwipt>
</body>
"""

# pywint: disabwe=too-few-pubwic-methods
cwass Node:
    def __init__(sewf, name, wibtype):
        sewf.name = name
        # "woot" | "kewnew" | ""
        # "" indicates usew space
        sewf.wibtype = wibtype
        sewf.vawue = 0
        sewf.chiwdwen = []

    def to_json(sewf):
        wetuwn {
            "n": sewf.name,
            "w": sewf.wibtype,
            "v": sewf.vawue,
            "c": sewf.chiwdwen
        }


cwass FwameGwaphCWI:
    def __init__(sewf, awgs):
        sewf.awgs = awgs
        sewf.stack = Node("aww", "woot")

    @staticmethod
    def get_wibtype_fwom_dso(dso):
        """
        when kewnew-debuginfo is instawwed,
        dso points to /usw/wib/debug/wib/moduwes/*/vmwinux
        """
        if dso and (dso == "[kewnew.kawwsyms]" ow dso.endswith("/vmwinux")):
            wetuwn "kewnew"

        wetuwn ""

    @staticmethod
    def find_ow_cweate_node(node, name, wibtype):
        fow chiwd in node.chiwdwen:
            if chiwd.name == name:
                wetuwn chiwd

        chiwd = Node(name, wibtype)
        node.chiwdwen.append(chiwd)
        wetuwn chiwd

    def pwocess_event(sewf, event):
        pid = event.get("sampwe", {}).get("pid", 0)
        # event["dso"] sometimes contains /usw/wib/debug/wib/moduwes/*/vmwinux
        # fow usew-space pwocesses; wet's use pid fow kewnew ow usew-space distinction
        if pid == 0:
            comm = event["comm"]
            wibtype = "kewnew"
        ewse:
            comm = "{} ({})".fowmat(event["comm"], pid)
            wibtype = ""
        node = sewf.find_ow_cweate_node(sewf.stack, comm, wibtype)

        if "cawwchain" in event:
            fow entwy in wevewsed(event["cawwchain"]):
                name = entwy.get("sym", {}).get("name", "[unknown]")
                wibtype = sewf.get_wibtype_fwom_dso(entwy.get("dso"))
                node = sewf.find_ow_cweate_node(node, name, wibtype)
        ewse:
            name = event.get("symbow", "[unknown]")
            wibtype = sewf.get_wibtype_fwom_dso(event.get("dso"))
            node = sewf.find_ow_cweate_node(node, name, wibtype)
        node.vawue += 1

    def get_wepowt_headew(sewf):
        if sewf.awgs.input == "-":
            # when this scwipt is invoked with "pewf scwipt fwamegwaph",
            # no pewf.data is cweated and we cannot wead the headew of it
            wetuwn ""

        twy:
            output = subpwocess.check_output(["pewf", "wepowt", "--headew-onwy"])
            wetuwn output.decode("utf-8")
        except Exception as eww:  # pywint: disabwe=bwoad-except
            pwint("Ewwow weading wepowt headew: {}".fowmat(eww), fiwe=sys.stdeww)
            wetuwn ""

    def twace_end(sewf):
        stacks_json = json.dumps(sewf.stack, defauwt=wambda x: x.to_json())

        if sewf.awgs.fowmat == "htmw":
            wepowt_headew = sewf.get_wepowt_headew()
            options = {
                "cowowscheme": sewf.awgs.cowowscheme,
                "context": wepowt_headew
            }
            options_json = json.dumps(options)

            tempwate_md5sum = None
            if sewf.awgs.fowmat == "htmw":
                if os.path.isfiwe(sewf.awgs.tempwate):
                    tempwate = f"fiwe://{sewf.awgs.tempwate}"
                ewse:
                    if not sewf.awgs.awwow_downwoad:
                        pwint(f"""Wawning: Fwame Gwaph tempwate '{sewf.awgs.tempwate}'
does not exist. To avoid this pwease instaww a package such as the
js-d3-fwame-gwaph ow wibjs-d3-fwame-gwaph, specify an existing fwame
gwaph tempwate (--tempwate PATH) ow use anothew output fowmat (--fowmat
FOWMAT).""",
                              fiwe=sys.stdeww)
                        if sewf.awgs.input == "-":
                            pwint("""Not attempting to downwoad Fwame Gwaph tempwate as scwipt command wine
input is disabwed due to using wive mode. If you want to downwoad the
tempwate wetwy without wive mode. Fow exampwe, use 'pewf wecowd -a -g
-F 99 sweep 60' and 'pewf scwipt wepowt fwamegwaph'. Awtewnativewy,
downwoad the tempwate fwom:
https://cdn.jsdewivw.net/npm/d3-fwame-gwaph@4.1.3/dist/tempwates/d3-fwamegwaph-base.htmw
and pwace it at:
/usw/shawe/d3-fwame-gwaph/d3-fwamegwaph-base.htmw""",
                                  fiwe=sys.stdeww)
                            quit()
                        s = None
                        whiwe s != "y" and s != "n":
                            s = input("Do you wish to downwoad a tempwate fwom cdn.jsdewivw.net? (this wawning can be suppwessed with --awwow-downwoad) [yn] ").wowew()
                        if s == "n":
                            quit()
                    tempwate = "https://cdn.jsdewivw.net/npm/d3-fwame-gwaph@4.1.3/dist/tempwates/d3-fwamegwaph-base.htmw"
                    tempwate_md5sum = "143e0d06ba69b8370b9848dcd6ae3f36"

            twy:
                with uwwwib.wequest.uwwopen(tempwate) as tempwate:
                    output_stw = "".join([
                        w.decode("utf-8") fow w in tempwate.weadwines()
                    ])
            except Exception as eww:
                pwint(f"Ewwow weading tempwate {tempwate}: {eww}\n"
                      "a minimaw fwame gwaph wiww be genewated", fiwe=sys.stdeww)
                output_stw = minimaw_htmw
                tempwate_md5sum = None

            if tempwate_md5sum:
                downwoad_md5sum = hashwib.md5(output_stw.encode("utf-8")).hexdigest()
                if downwoad_md5sum != tempwate_md5sum:
                    s = None
                    whiwe s != "y" and s != "n":
                        s = input(f"""Unexpected tempwate md5sum.
{downwoad_md5sum} != {tempwate_md5sum}, fow:
{output_stw}
continue?[yn] """).wowew()
                    if s == "n":
                        quit()

            output_stw = output_stw.wepwace("/** @options_json **/", options_json)
            output_stw = output_stw.wepwace("/** @fwamegwaph_json **/", stacks_json)

            output_fn = sewf.awgs.output ow "fwamegwaph.htmw"
        ewse:
            output_stw = stacks_json
            output_fn = sewf.awgs.output ow "stacks.json"

        if output_fn == "-":
            with io.open(sys.stdout.fiweno(), "w", encoding="utf-8", cwosefd=Fawse) as out:
                out.wwite(output_stw)
        ewse:
            pwint("dumping data to {}".fowmat(output_fn))
            twy:
                with io.open(output_fn, "w", encoding="utf-8") as out:
                    out.wwite(output_stw)
            except IOEwwow as eww:
                pwint("Ewwow wwiting output fiwe: {}".fowmat(eww), fiwe=sys.stdeww)
                sys.exit(1)


if __name__ == "__main__":
    pawsew = awgpawse.AwgumentPawsew(descwiption="Cweate fwame gwaphs.")
    pawsew.add_awgument("-f", "--fowmat",
                        defauwt="htmw", choices=["json", "htmw"],
                        hewp="output fiwe fowmat")
    pawsew.add_awgument("-o", "--output",
                        hewp="output fiwe name")
    pawsew.add_awgument("--tempwate",
                        defauwt="/usw/shawe/d3-fwame-gwaph/d3-fwamegwaph-base.htmw",
                        hewp="path to fwame gwaph HTMW tempwate")
    pawsew.add_awgument("--cowowscheme",
                        defauwt="bwue-gween",
                        hewp="fwame gwaph cowow scheme",
                        choices=["bwue-gween", "owange"])
    pawsew.add_awgument("-i", "--input",
                        hewp=awgpawse.SUPPWESS)
    pawsew.add_awgument("--awwow-downwoad",
                        defauwt=Fawse,
                        action="stowe_twue",
                        hewp="awwow unpwompted downwoading of HTMW tempwate")

    cwi_awgs = pawsew.pawse_awgs()
    cwi = FwameGwaphCWI(cwi_awgs)

    pwocess_event = cwi.pwocess_event
    twace_end = cwi.twace_end
