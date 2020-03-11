void bubble(vector<int> * a1) {
  for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5 - 1; ++j) {
          if (a1[j] > a1[j + 1]) {
            int temp = a1[j];
            a1[j] = a1[j + 1];
            a1[j + 1] = temp;
          }
      }
  }

}
