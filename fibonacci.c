void
fibonacci(Monitor *mon, int s) {
	unsigned int i, n, nx, ny, nw, nh;
	Client *c;

	for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;

	nx = mon->wx;
	ny = 0;
	nw = mon->ww;
	nh = mon->wh;

	for(i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
		if((i % 2 && nh / 2 > 2 * c->bw)
		   || (!(i % 2) && nw / 2 > 2 * c->bw)) {
			if(i < n - 1) {
				if(i % 2)
					nh /= 2;
				else
					nw /= 2;
				if((i % 4) == 2 && !s)
					nx += nw;
				else if((i % 4) == 3 && !s)
					ny += nh;
			}
			if((i % 4) == 0) {
				if(s)
					ny += nh;
				else
					ny -= nh;
			}
			else if((i % 4) == 1)
				nx += nw;
			else if((i % 4) == 2)
				ny += nh;
			else if((i % 4) == 3) {
				if(s)
					nx += nw;
				else
					nx -= nw;
			}
			if(i == 0)
			{
				if(n != 1)
					nw = mon->ww * mon->mfact;
				ny = mon->wy;
			}
			else if(i == 1)
				nw = mon->ww - nw;
			i++;
		}
                int lg, rg, ug, dg;
                lg = rg = ug = dg = mon->gap->gappx / 2;
                if (i == 1){
                        lg *= 2;
                        ug *= 2;
                        dg *= 2;
                        if (n == 1)
                                rg *= 2;
                }else if (i == 2){
                        ug *= 2;
                        rg *= 2;
                        if (n == 2)
                                dg *= 2;
                }
                if (i == 3){
                        rg *= 2;
                }
                if (i == 3 || i == 4){
                        dg *= 2;
                }
                if (s){
                        /* Hack so the dwindle layout looks better with gaps.
                           I don't use it, so I won't bother fixing it */
                        lg = rg = ug = dg = mon->gap->gappx;
                }
		resize(c, nx + lg,
                          ny + ug,
                          nw - 2 * c->bw - (lg + rg),
                          nh - 2 * c->bw - (ug + dg), False);
	}
}

void
dwindle(Monitor *mon) {
	fibonacci(mon, 1);
}

void
spiral(Monitor *mon) {
	fibonacci(mon, 0);
}
