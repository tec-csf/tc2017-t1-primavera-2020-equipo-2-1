void B(int n) {
  int i,j,s;
  for (i = 0 ; i < n-1 ; i++) {
    s = 0
    if (i > 10) {
      for(j = i ; j < n ; j++) {
        s += j;
      }
    }
    cout << s << endl;
  }
}
