#include "intake.h"

enum tiltType {extend, retract};

class tilter{
  private:
    int inSpeed = -100;
    int outSpeed = 100;
    int slowSpeed = 20;
    void buttonReset();
  public:
    tilter();
    void Spin(int speed);
    void Stop(bool type);
    void autoScore();
    void userControl();   
};

tilter::tilter(){}

void tilter::Spin(int speed){
  tilt1.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);   
  tilt2.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);  
}
void tilter::Stop(bool type){
  if(type){
      tilt1.stop(vex::brakeType::coast);  
      tilt2.stop(vex::brakeType::coast);            
    }else{
      tilt1.stop(vex::brakeType::hold);   
      tilt2.stop(vex::brakeType::hold);             
    }  
}

void tilter::buttonReset(){
  if(Bumper.pressing()==1){
    tilt1.resetRotation();
  }
}

void tilter::autoScore(){
  myIntake().Spin(-50);
  myBase().Spin(-30, -30);
  this->Spin(-60);
}

void tilter::userControl(){
  if(tiltInBtn && tiltOutBtn){
    this->Spin(this->slowSpeed);                      
  }else if(tiltInBtn){ 
    this->Spin(this->inSpeed);  
  }else if(tiltOutBtn){
    this->Spin(this->outSpeed);  
  }else{
    if(tilt1.rotation(vex::rotationUnits::deg)<=75){
      this->Stop(1);        
    }else{
      this->Stop(0);           
    }     
  }
  if(autoScoreBtn){
      //this->autoScore();
    }
  this->buttonReset();
}



/*





void moveTitl(tiltType mydirection, int speed=0, int timeOut=2){
  if(mydirection == extend){
    tilt1.setTimeout(timeOut,vex::timeUnits::sec);
    tilt1.spin(vex::directionType::fwd,speed,vex::velocityUnits::rpm);
    tilt2.spin(vex::directionType::rev,speed,vex::velocityUnits::rpm);    
  }
  else if(mydirection == retract){
    tilt1.setTimeout(timeOut,vex::timeUnits::sec);
    tilt1.spin(vex::directionType::rev,speed,vex::velocityUnits::rpm);
    tilt2.spin(vex::directionType::fwd,speed,vex::velocityUnits::rpm);
  }
  else{
    tilt1.stop(vex::brakeType::hold);
    tilt2.stop(vex::brakeType::hold);
  }
}





void deployslide(int speed,int distance ) {
  tilt1.resetRotation() ;
  tilt1.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);
  tilt2.spin(vex::directionType::fwd,speed,vex::velocityUnits::pct);    
  
  while(tilt1.rotation(vex::rotationUnits::deg)<distance ){
    vex::task::sleep(1) ;
  }
  tilt1.stop(vex::brakeType::coast);
  tilt2.stop(vex::brakeType::coast);
  tilt2.resetRotation() ;
  tilt1.spin(vex::directionType::rev,speed,vex::velocityUnits::pct);
  tilt2.spin(vex::directionType::rev,speed,vex::velocityUnits::pct);
  while(!(Bumper.pressing())) 
  vex::task::sleep(1) ;
  tilt1.stop(vex::brakeType::coast);
  tilt2.stop(vex::brakeType::coast);
  turnonbase(40,false) ;
  vex::task::sleep(500) ;
}




void score(){
  tilt1.resetRotation() ;
  tilt1.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
  tilt2.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);    
  
  while(tilt1.rotation(vex::rotationUnits::deg)<525 ){
    if(tilt1.rotation(vex::rotationUnits::deg)>200){
    tilt1.spin(vex::directionType::fwd,30,vex::velocityUnits::pct);
    tilt2.spin(vex::directionType::fwd,30,vex::velocityUnits::pct);  
    }
    vex::task::sleep(1) ;
  }
  vex::task::sleep(1500) ;
  autoScore() ;
  vex::task::sleep(2000) ;
}
*/

tilter myTilter();