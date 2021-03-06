
enum dirType {forward, backward};
enum rotType {right, left};

class Drive{
  private:
    int leftSpeed = 0;
    int rightSpeed = 0;

    bool useTrueSpeed = true;
    bool toggle = false;

    double distanceToTravel(double inchesGiven);
    const unsigned int trueSpeed[128] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0 , 21, 21, 21, 22, 22, 22, 23, 24, 24,
     25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
     28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
     33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
     37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
     41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
     46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
     52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
     61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
     71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
     80, 83, 84, 86, 86, 87, 87, 88, 88, 90,
     90, 90, 95, 95, 95,100,100,100};

     const unsigned int halfSpeed[128] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0 , 10, 10, 10, 11, 11, 11, 12, 12, 12,
     13, 13, 13, 13, 13, 13, 14, 14, 14, 14,
     14, 15, 15, 15, 15, 16, 16, 16, 16, 16,
     17, 17, 17, 17, 17, 17, 17, 18, 18, 19,
     19, 19, 19, 19, 19, 20, 20, 20, 20, 20,
     21, 21, 21, 21, 22, 22, 22, 23, 23, 23,
     23, 24, 24, 24, 24, 25, 25, 25, 26, 26,
     26, 27, 27, 27, 28, 29, 29, 29, 30, 30,
     31, 32, 32,32, 33, 33, 34, 34, 34, 35,
     36, 36, 36, 37, 37, 38, 39, 39, 39, 39,
     40, 42, 42, 43, 43, 44, 44, 44, 44, 45,
     45, 45, 48, 48, 48,50,50,50};

  public:
    // Class Constructor
    Drive();
    // General Go Functions
    void spin_left(int speed);
    void spin_right(int speed);
    void spin_full(int leftSpeed, int rightSpeed);
    // General Stop Functions
    void hold();
    void brake();
    void coast();

    //User Control Functions
    void user_control(int buffer_size, bool Stop);

    //Autonomous Functions
    //bool smart_drive(double maxSpeed, double Distance, bool complete);
    //bool smart_turn(double maxSpeed, double Angle, bool complete);
};