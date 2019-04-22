struct Position {
  int ew, ns;
  Position( int ew = 0, int ns = 0 );
};

struct Drone {
  Drone();
  ~Drone();
  void forward(); 
  void backward(); 
  void left();
  void right();
  Position current() const;
  int totalDistance() const;
  int manhattanDistance() const;
  bool repeated() const;

  // add your instance variables
private:
  int x;
  int y;
  bool v[122][122];
  int d;
  int face;
};
