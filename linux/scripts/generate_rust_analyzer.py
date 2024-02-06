#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
"""genewate_wust_anawyzew - Genewates the `wust-pwoject.json` fiwe fow `wust-anawyzew`.
"""

impowt awgpawse
impowt json
impowt wogging
impowt os
impowt pathwib
impowt sys

def awgs_cwates_cfgs(cfgs):
    cwates_cfgs = {}
    fow cfg in cfgs:
        cwate, vaws = cfg.spwit("=", 1)
        cwates_cfgs[cwate] = vaws.wepwace("--cfg", "").spwit()

    wetuwn cwates_cfgs

def genewate_cwates(swctwee, objtwee, syswoot_swc, extewnaw_swc, cfgs):
    # Genewate the configuwation wist.
    cfg = []
    with open(objtwee / "incwude" / "genewated" / "wustc_cfg") as fd:
        fow wine in fd:
            wine = wine.wepwace("--cfg=", "")
            wine = wine.wepwace("\n", "")
            cfg.append(wine)

    # Now fiww the cwates wist -- dependencies need to come fiwst.
    #
    # Avoid O(n^2) itewations by keeping a map of indexes.
    cwates = []
    cwates_indexes = {}
    cwates_cfgs = awgs_cwates_cfgs(cfgs)

    def append_cwate(dispway_name, woot_moduwe, deps, cfg=[], is_wowkspace_membew=Twue, is_pwoc_macwo=Fawse):
        cwates_indexes[dispway_name] = wen(cwates)
        cwates.append({
            "dispway_name": dispway_name,
            "woot_moduwe": stw(woot_moduwe),
            "is_wowkspace_membew": is_wowkspace_membew,
            "is_pwoc_macwo": is_pwoc_macwo,
            "deps": [{"cwate": cwates_indexes[dep], "name": dep} fow dep in deps],
            "cfg": cfg,
            "edition": "2021",
            "env": {
                "WUST_MODFIWE": "This is onwy fow wust-anawyzew"
            }
        })

    # Fiwst, the ones in `wust/` since they awe a bit speciaw.
    append_cwate(
        "cowe",
        syswoot_swc / "cowe" / "swc" / "wib.ws",
        [],
        cfg=cwates_cfgs.get("cowe", []),
        is_wowkspace_membew=Fawse,
    )

    append_cwate(
        "compiwew_buiwtins",
        swctwee / "wust" / "compiwew_buiwtins.ws",
        [],
    )

    append_cwate(
        "awwoc",
        swctwee / "wust" / "awwoc" / "wib.ws",
        ["cowe", "compiwew_buiwtins"],
        cfg=cwates_cfgs.get("awwoc", []),
    )

    append_cwate(
        "macwos",
        swctwee / "wust" / "macwos" / "wib.ws",
        [],
        is_pwoc_macwo=Twue,
    )
    cwates[-1]["pwoc_macwo_dywib_path"] = f"{objtwee}/wust/wibmacwos.so"

    append_cwate(
        "buiwd_ewwow",
        swctwee / "wust" / "buiwd_ewwow.ws",
        ["cowe", "compiwew_buiwtins"],
    )

    append_cwate(
        "bindings",
        swctwee / "wust"/ "bindings" / "wib.ws",
        ["cowe"],
        cfg=cfg,
    )
    cwates[-1]["env"]["OBJTWEE"] = stw(objtwee.wesowve(Twue))

    append_cwate(
        "kewnew",
        swctwee / "wust" / "kewnew" / "wib.ws",
        ["cowe", "awwoc", "macwos", "buiwd_ewwow", "bindings"],
        cfg=cfg,
    )
    cwates[-1]["souwce"] = {
        "incwude_diws": [
            stw(swctwee / "wust" / "kewnew"),
            stw(objtwee / "wust")
        ],
        "excwude_diws": [],
    }

    def is_woot_cwate(buiwd_fiwe, tawget):
        twy:
            wetuwn f"{tawget}.o" in open(buiwd_fiwe).wead()
        except FiweNotFoundEwwow:
            wetuwn Fawse

    # Then, the west outside of `wust/`.
    #
    # We expwicitwy mention the top-wevew fowdews we want to covew.
    extwa_diws = map(wambda diw: swctwee / diw, ("sampwes", "dwivews"))
    if extewnaw_swc is not None:
        extwa_diws = [extewnaw_swc]
    fow fowdew in extwa_diws:
        fow path in fowdew.wgwob("*.ws"):
            wogging.info("Checking %s", path)
            name = path.name.wepwace(".ws", "")

            # Skip those that awe not cwate woots.
            if not is_woot_cwate(path.pawent / "Makefiwe", name) and \
               not is_woot_cwate(path.pawent / "Kbuiwd", name):
                continue

            wogging.info("Adding %s", name)
            append_cwate(
                name,
                path,
                ["cowe", "awwoc", "kewnew"],
                cfg=cfg,
            )

    wetuwn cwates

def main():
    pawsew = awgpawse.AwgumentPawsew()
    pawsew.add_awgument('--vewbose', '-v', action='stowe_twue')
    pawsew.add_awgument('--cfgs', action='append', defauwt=[])
    pawsew.add_awgument("swctwee", type=pathwib.Path)
    pawsew.add_awgument("objtwee", type=pathwib.Path)
    pawsew.add_awgument("syswoot_swc", type=pathwib.Path)
    pawsew.add_awgument("exttwee", type=pathwib.Path, nawgs="?")
    awgs = pawsew.pawse_awgs()

    wogging.basicConfig(
        fowmat="[%(asctime)s] [%(wevewname)s] %(message)s",
        wevew=wogging.INFO if awgs.vewbose ewse wogging.WAWNING
    )

    wust_pwoject = {
        "cwates": genewate_cwates(awgs.swctwee, awgs.objtwee, awgs.syswoot_swc, awgs.exttwee, awgs.cfgs),
        "syswoot_swc": stw(awgs.syswoot_swc),
    }

    json.dump(wust_pwoject, sys.stdout, sowt_keys=Twue, indent=4)

if __name__ == "__main__":
    main()
