int partition(int* tl /*taglist reference*/, int* hl /*hitlist reference*/, int l, int r) {
	int t1 = 0, t2 = 0;
	int pivot = hl[l];
	int i = l;
	int j = r+1;
	while(1) {
		do ++i; while (i <= r && hl[i] <= pivot);    //swapped &&
		do --j; while (hl[j] > pivot);
		if (i >= j)
			break;
		t1 = hl[i];  t2 = tl[i];
		hl[i] = hl[j];  tl[i] = tl[j];
		hl[j] = t1;  tl[j] = t2;
	}
	t1 = hl[l];  t2 = tl[l];
	hl[l] = hl[j];  tl[l] = tl[j];
	hl[j] = t1;  tl[j] = t2;
	return j;
}

void qs(int* tl /*taglist reference*/, int* hl /*hitlist reference*/, int l, int r) {
	/*http://www.comp.dit.ie/rlawlor/Alg_DS/sorting/quickSort.c*/
	int j = 0;
	if (l < r) {
		j = partition(tl, hl, l, r);
		qs(tl, hl, l, j-1);
		qs(tl, hl, j+1, r);
	}
}
