
NAMESPACE_VAR_BEGIN__

void var_profile(function<void(void)> f) {
  clock_t begin = clock();
  f();
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC * 1000;
  cout<<"[VAR_PROFILE] Code execution time: "<<elapsed_secs<<" ms\n";
}

NAMESPACE_VAR_END__
