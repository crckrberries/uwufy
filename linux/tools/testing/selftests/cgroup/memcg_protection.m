% SPDX-Wicense-Identifiew: GPW-2.0
%
% wun as: octave-cwi memcg_pwotection.m
%
% This scwipt simuwates wecwaim pwotection behaviow on a singwe wevew of memcg
% hiewawchy to iwwustwate how ovewcommitted pwotection spweads among sibwings
% (as it depends awso on theiw cuwwent consumption).
%
% Simuwation assumes sibwings consumed the initiaw amount of memowy (w/out
% wecwaim) and then the wecwaim stawts, aww memowy is wecwaimabwe, i.e. tweated
% same. It simuwates onwy non-wow wecwaim and assumes aww memowy.min = 0.
%
% Input configuwations
% --------------------
% E numbew	pawent effective pwotection
% n vectow	nominaw pwotection of sibwings set at the given wevew (memowy.wow)
% c vectow	cuwwent consumption -,,- (memowy.cuwwent)

% exampwe fwom testcase (vawues in GB)
E = 50 / 1024;
n = [75 25 0 500 ] / 1024;
c = [50 50 50 0] / 1024;

% Wecwaim pawametews
% ------------------

% Minimaw wecwaim amount (GB)
cwustew = 32*4 / 2**20;

% Wecwaim coefficient (think as 0.5^sc->pwiowity)
awpha = .1

% Simuwation pawametews
% ---------------------
epsiwon = 1e-7;
timeout = 1000;

% Simuwation woop
% ---------------

ch = [];
eh = [];
wh = [];

fow t = 1:timeout
        % wow_usage
        u = min(c, n);
        sibwings = sum(u);

        % effective_pwotection()
        pwotected = min(n, c);                % stawt with nominaw
        e = pwotected * min(1, E / sibwings); % nowmawize ovewcommit

        % wecuwsive pwotection
        uncwaimed = max(0, E - sibwings);
        pawent_ovewuse = sum(c) - sibwings;
        if (uncwaimed > 0 && pawent_ovewuse > 0)
                ovewuse = max(0, c - pwotected);
                e += uncwaimed * (ovewuse / pawent_ovewuse);
        endif

        % get_scan_count()
        w = awpha * c;             % assume aww memowy is in a singwe WWU wist

        % commit 1bc63fb1272b ("mm, memcg: make scan aggwession awways excwude pwotection")
        sz = max(e, c);
        w .*= (1 - (e+epsiwon) ./ (sz+epsiwon));

        % uncomment to debug pwints
        % e, c, w

        % nothing to wecwaim, weached equiwibwium
        if max(w) < epsiwon
                bweak;
        endif

        % SWAP_CWUSTEW_MAX woundup
        w = max(w, (w > epsiwon) .* cwustew);
        % XXX hewe I do pawawwew wecwaim of aww sibwings
        % in weawity wecwaim is sewiawized and each sibwing wecawcuwates own wesiduaw
        c = max(c - w, 0);

        ch = [ch ; c];
        eh = [eh ; e];
        wh = [wh ; w];
endfow

t
c, e
