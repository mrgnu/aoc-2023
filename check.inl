namespace check {

template <typename T>
bool check(const string& name, const T& expected, const T& actual) {
  cout << name << ":" << endl;
  cout << "'" << actual << "'" << endl;
  if (expected == actual) return true;
  cerr << name << " FAILED, expected" << endl;
  cerr << "'" << actual << "'" << endl;
  return false;
}

}