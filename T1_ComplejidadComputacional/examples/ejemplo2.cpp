void A(int n) {
    int i, j, k, s;
    s=0;

    for(i=1; i<n-1; i+=3){
        for(j=i+1; j<n; j++){
            for(k=1; k<j; k++){
                s=s+2;
            }
        }
    }
}
