//status=0 request            status=1  onroute         status=2 completed   status =3  ride canceled        status=4 ride completed

#include<iostream>
#include <thread>
#include <chrono>

using namespace std;
class ApplicationException
{
public:
    int errNo;
    string errMsg;
    ApplicationException(int x,string y)
    {
        this->errNo=x;
        this->errMsg=y;
    }
    void showError()
    {
        cout<<"ERROR!!"<<endl;
        cout<<errNo<<":"<<errMsg<<endl;
    }
};


class Vehicle {
public:
int driverId;
string numberPlate;
string model;
int seatingCapacity;
int wheel;
double basePrice;
double priceKm;
Vehicle():driverId(0),numberPlate(""),model(""),seatingCapacity(0),wheel(0),basePrice(0),priceKm(0){}

 Vehicle(int driverId,string numberPlate,string model,int seatingCapacity,int wheel,double basePrice,double priceKm){
 this->driverId=driverId;
 this->numberPlate=numberPlate;
 this->model=model;
 this->seatingCapacity=seatingCapacity;
 this->wheel=wheel;
 this->basePrice=basePrice;
 this->priceKm=priceKm;
 }



   void  updatevehicle(){
      cout<<"enter the Numberplate,model,seating capacity,wheels of vehicle data being replaced"<<endl;
      cin>>numberPlate>>model>>seatingCapacity>>wheel>>basePrice;
      this->numberPlate=numberPlate;
      this->model=model;
      this->seatingCapacity=seatingCapacity;
      this->wheel=wheel;
      this->basePrice=basePrice;
      this->priceKm=priceKm;
   }
   void vehicleDetails()
   {
       cout<<endl<<"vehicle details"<<endl<<endl;
       cout<<"driver id:"<<driverId<<endl<<"numberPlate:"<<numberPlate<<endl<<"model"<<model<<endl<<"seating capacity:"<<seatingCapacity<<endl<<wheel<<"wheeler vehicle"<<endl<<": base price "<<basePrice<<endl<<": price per km "<<priceKm<<endl;

   }
   double getBasePrice()
   {
       return basePrice;
   }
   double getPriceKm(){
    return priceKm;
   }


};

class User{
 public:
 int userId;
 string userName;
 string password;
 int phNo;
 User(int id,string name,string password, int num):userId(id),userName(name),password(password),phNo(num){}
 virtual void printUser()=0;

virtual void generatereciept()=0;

 virtual void updateProfile(){
   cout<<"Enter the new UserName , User Password ,phone number "<<endl;
   int pno;
   string name;
   string pass;
   cin>>name>>pass>>pno;
   this->userName=name;
   this->password=pass;
   this->phNo=pno;

 }
};

class Customer:public User{
 public:
     string location;
     Customer(int id,string name,string password,int phno,string loc):User(id,name,password,phno),location(loc){}
     void printUser()
     {
        cout<<"Id :"<<User::userId<<endl<<"Name:"<<User::userName<<endl<<"Phone no:"<<User::phNo<<endl;



      cout<<location;
     }

     void updateProfile()
     {
         User::updateProfile();
     }

     void generatereciept()
     {
         cout<<endl<<"Customer Id :"<<User::userId<<endl;
         cout<<"Customer Name :"<<User::userName<<endl;
         cout<<"Customer phNo :"<<User::phNo<<endl;
     }

};

class Driver:public User{

     public:
      string availability;
      Vehicle v;
      Driver(int id,string name,string password,int phno,string availability,Vehicle v1):User(id,name,password,phno),availability(availability){
      v=v1;
     }
     void printUser(){

  cout<<endl<<"ID :"<<User::userId<<endl<<"Name"<<User::userName<<endl<<"Phone number :"<<User::phNo<<endl;


        cout<<endl<<"Availability:"<< availability <<endl;
        v.vehicleDetails();
     }
     void updateProfile()
     {
         User::updateProfile();
     }
    double getBasePrice()
   {
      return v.getBasePrice();
   }
   double getPriceKm(){
    return v.getPriceKm();
   }
   void generatereciept()
     {
         cout<<endl<<"DRIVER"<<endl;
         cout<<endl<<"Driver Id :"<<User::userId<<endl;
         cout<<"Driver Name :"<<User::userName<<endl;
         cout<<"Driver phNo :"<<User::phNo<<endl;
     }
};


class Location {
public:
    string pickup;
    string drop;
    double distance;

    Location(string pickup, string drop, double distance)
    {
       this->pickup=pickup;
       this->drop=drop;
       this->distance=distance;


    }


    double getDistance(){
      return distance;
    }

    void getaddress() {
        cout << "Pickup: " << pickup << endl;
        cout << "Drop: " << drop << endl;
    }
};

class Ride;  //CONTEXT

class RideState {   //STATE
public:
    virtual void requestRide(Ride& ride) = 0;
    virtual void cancelRide(Ride& ride) = 0;
    virtual void startRide(Ride& ride) = 0;
    virtual void endRide(Ride& ride) = 0;
};

class nonRequestedState : public RideState {   //CONCRETE STATE
public:
    void requestRide(Ride& ride) override;
    void cancelRide(Ride& ride) override;
    void startRide(Ride& ride) override;
    void endRide(Ride& ride) override;
};


class OnRouteState : public RideState {
public:
    void requestRide(Ride& ride) override;
    void cancelRide(Ride& ride) override;
    void startRide(Ride& ride) override;
    void endRide(Ride& ride) override;
};

class CompletedState : public RideState {
public:
    void requestRide(Ride& ride) override;
    void cancelRide(Ride& ride) override;
    void startRide(Ride& ride) override;
    void endRide(Ride& ride) override;
};
class canceledState : public RideState {
public:
    void requestRide(Ride& ride) override;
    void cancelRide(Ride& ride) override;
    void startRide(Ride& ride) override;
    void endRide(Ride& ride) override;
};

class Ride {
public:
int rideid;
double fare;
string date;
string  time;
string status;
Driver *drivers;
Customer *customers;
Location *loc;

static int counter;
RideState* rideState;


   Ride():fare(0),date(""),time(""),status(""),rideid(){}
   Ride(int rideid,double fare,string date,string time,string status)
   {
   this->time=time;
   this->fare=fare;
   this->status=status;
   this->date=date;
   this->rideid=rideid;
   counter++;
   rideState = new nonRequestedState();
   }

    void setRideState(RideState* state) {
        rideState = state;
    }

    void requestRide() {
        rideState->requestRide(*this);
    }

    void cancelRide() {
        rideState->cancelRide(*this);
    }

    void startRide() {
        rideState->startRide(*this);
    }

    void endRide() {
        rideState->endRide(*this);
    }


   void rideDetails(){
     drivers->printUser();
     cout<<"ride id :"<<rideid<<endl<<"; date:"<<date<<endl;
   }
   double farecalculation(){
       double basePrice=drivers->getBasePrice();

       double priceKm=drivers->getPriceKm();

       double distanc=loc->getDistance();

       fare=basePrice+(priceKm*distanc);
       if(distanc>100)
       {
           fare=fare-0.1*fare;
       }

       return fare;
   }
   int generatereciept(){

     customers->generatereciept();
     drivers->generatereciept();
     cout<<"Pickup :"<<loc->pickup<<endl;
     cout<<"Drop :"<<loc->drop<<endl;
    if(counter==1)
    {
        cout<<"As this is your first ride you get additional 50% off"<<endl;
        fare=fare-0.5*fare;
    }
     cout<<"Amount :"<<fare<<endl;
     return fare;

   }
};

void nonRequestedState::requestRide(Ride& ride) {
    cout << "Ride request is already in progress." << std::endl;
}

void nonRequestedState::cancelRide(Ride& ride) {
    cout << "Ride has still not been booked" << std::endl;
}

void nonRequestedState::startRide(Ride& ride) {
    cout << "Cannot start the ride until it's accepted." << std::endl;
}

void nonRequestedState::endRide(Ride& ride) {
    cout << "Cannot end the ride before starting it." << std::endl;
}



void OnRouteState::requestRide(Ride& ride) {
    cout << "Ride request is already in progress." << std::endl;
}

void OnRouteState::cancelRide(Ride& ride) {
    cout << "Canceling the ride." << std::endl;
}

void OnRouteState::startRide(Ride& ride) {
    cout << "Ride is already started." << std::endl;
}

void OnRouteState::endRide(Ride& ride) {
    cout << "Ending the ride." << std::endl;
    ride.setRideState(new CompletedState());
}

void CompletedState::requestRide(Ride& ride) {
    cout << "Cannot request a new ride after completing the current ride." << std::endl;
}

void CompletedState::cancelRide(Ride& ride) {
    cout << "Cannot cancel the ride after it's completed." << std::endl;
}

void CompletedState::startRide(Ride& ride) {
    cout << "Cannot start a new ride after completing the current ride." << std::endl;
}

void CompletedState::endRide(Ride& ride) {
    cout << "The ride is already completed." << std::endl;
}


void canceledState::requestRide(Ride& ride) {
    cout << "New ride will be booked please wait." << std::endl;
}

void canceledState::cancelRide(Ride& ride) {
    cout << "Ride has already been canceled." << std::endl;
}

void canceledState::startRide(Ride& ride) {
    cout << "Cannot start the ride as ride was canceled please request ride again." << std::endl;
}

void canceledState::endRide(Ride& ride) {
    cout << "Cannot end the ride before starting it." << std::endl;
}

class RideHistory{

  public:
     void getRideHistory()
      {

      }
     void  deleteRideHistory()
      {

      }

};

class Paymentportal{
public:

int paymentid;
string paymentstatus;
string paymentmode;
double amount;
double wallet;

    Paymentportal(int paymentid,string paymentstatus,string paymentmode,double wallet):paymentstatus(paymentstatus),paymentmode(paymentmode),paymentid(paymentid),wallet(wallet){

    }
   void payWallet(Ride r1)
   {
         amount=r1.generatereciept();
         if(wallet<amount)
         {
              throw ApplicationException(404,"You dont have sufficient amount in your wallet please pay by UPI method");
         }
         wallet=wallet-amount;
         cout<<"Remaining amount in wallet ="<<wallet<<endl;
   }
   void generatereciept(Ride r1)
   {
       r1.generatereciept();
      cout<<endl<<"Reciept"<<endl;

   }

};

class Register
{
  public:
  int id;
  string password;
  User *users[];
  Register()
  {

  }
  void login()
  {
      cout<<"LOGIN "<<endl<<"Enter User Id and Password "<<endl;
      cin>>id>>password;
  }
  int logincred(int siz)
  {
     int status=0;

     for(int i=0;i<siz;i++)
  {
      if(users[i]->userId==id && users[i]->password==password)
      {
          status=1;
          break;

      }

  }

   if(status==1)
  {
      cout<<"successful login"<<endl;
      return id;

  }
  else
  {
      throw ApplicationException(404,"wrong id or password");
   cout<<"wrong id or password";
   return 1;

  }
  return 2;
  }
};

int Ride::counter=0;
int main(){
  int rideid=0,status=0,nom=0,userSize=0,stat=0;

  Vehicle vehicle[]={Vehicle(1000,"KA25 B 2345","Tavera",6,4,2000,50),Vehicle(1001,"KA26 B 3489","Passion",2,2,200,20),Vehicle(1002,"KA19EQ1306","Toyota RAV4",6,4,1000,50)};
  User *us[]={new Customer(1,"alwyn","ally",938048,"hubli"), new Driver(1001,"Rahul","RAHH",89767,"yes",vehicle[1]),new Driver(1002,"sandeep","sand",1923,"yes",vehicle[0])};

int no,cust_id,z,num,f,sphno,sid,x=1;
int vehSize=sizeof(vehicle) / sizeof(vehicle[0]);

string sname,spass,slocation;
   cout<<"Welcome back!!"<<endl<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    Register l1;
    userSize = sizeof(us) / sizeof(us[0]);
    for (int i = 0; i < userSize; i++)
    {
        l1.users[i] = us[i];
    }
    while(x=1)
    {
  try{




    cout<<"Please press LOGIN if already have an account , if not SIGNUP"<<endl<<endl;
    cout<<" [1]Login               [2]Sign up"<<endl;



    cin>>no;
    cout<<endl;
    switch(no)
    {
    case 1:
         l1.login();
         cust_id=l1.logincred(userSize);
         x=0;
         break;

    case 2:
        cout<<" signup"<<endl;
    userSize = sizeof(us) / sizeof(us[0]);
    userSize++;
    cout<<" Enter Id"<<endl;
    cin>>sid;
        cout<<endl<<" Enter name"<<endl;
          cin>>sname;
        cout<<endl<<" Enter password"<<endl;
          cin>>spass;
            cout<<endl<<" Enter phonenumber"<<endl;
          cin>>sphno;
        cout<<endl<<" Enter location"<<endl;
         cin>>slocation;
        us[userSize-1]=new Customer(sid,sname,spass,sphno,slocation);
        l1.users[userSize-1] = us[userSize-1];
        break;

    default :
        cout<<"Invalid key try again!!"<<endl;
        break;
    }
    if(x==0)
    {
        break;
    }


  }

  catch(ApplicationException &e)
  {
      e.showError();

  }
    }
try{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    int i,j,k,num2,m,n,o,p,q;
    double distance;
    string pick,drop;

           while(1){
            cout<<endl<<"Menu :-"<<endl;
            cout<<"[1] Profile"<<endl<<"[2] Book ride"<<endl<<"[3] request"<<endl<<"[4] cancel ride;  "<<endl<<"[5]start ride"<<endl<< "[6]Pay me"<<endl;
            cin>>no;
            Ride ride;
            Ride r1;
            switch(no)
            {
            case 1:
                cout<<" [1] View Profile "<<endl<<" [2] Update profile "<<endl;

                cin>>num;
                switch(num)
                {
                case 1:
                        std::this_thread::sleep_for(std::chrono::seconds(1));

                    cout<<"Profile :"<<endl;
                    for(n=0;n<userSize;n++)  //users list
                    {
                        if(us[n]->userId==cust_id)
                        {
                            us[n]->printUser();
                            break;
                        }
                    }
                    break;


                  case 2:
                    for(o=0;o<userSize;o++)  //users list
                    {
                        if(us[o]->userId==cust_id)
                        {
                            us[o]->updateProfile();
                            break;
                        }
                    }
                    break;
                default:
                    break;

                }
                break;
            case 2:
                   cout<<" [1] Search location "<< "          [2] Search Destination"<<endl;

                 int numb;
                 cin>>numb;
                 switch(numb)
                 {

                 case 1: status=1;
                        cout<<" Enter the location "<<endl;
                        cin>>pick;
                 case 2:
                         cout<<"Enter destination "<<endl;
                         cin>>drop;

                         cout<<endl<<"Enter the distance :";
                         cin>>distance;

                         cout<<"Available drivers :";
                         f=j;
                         for( j=0;j<userSize;j++)
                         {

                          if(us[j]->userId>999)
                          {

                            us[j]->printUser();
                            cout<<"-----------------------------------------------------------------------"<<endl;
                          }
                 std::this_thread::sleep_for(std::chrono::seconds(1));
                          cout<<endl<<endl;
                          }

               cout<<"Select the vehicle you wish to travel in by entering the ID :";
                          int taxi_id,j;
                          cin>>taxi_id;

                       r1= Ride(rideid++,0,"12-07-22","12:45 PM","Ride available");
                      for(int p=0;p<userSize;p++)
                      {

                          if(us[p]->userId==taxi_id)
                           {

                            cout<<"entering in ride"<<endl;
                            int driverid=us[p]->userId;
                            string name=us[p]->userName;
                            string pss=us[p]->password;
                            int pno=us[p]->phNo;

                             for(m=0;m<vehSize;m++)
                             {

                              if(vehicle[m].driverId==driverid)
                             {

                                  break;
                             }
                             }

                              r1.drivers=new Driver(driverid,name,pss,pno,"yes",vehicle[m]);

                            }


                              cout<<endl<<endl;
                            }

                            Location loc1(pick,drop,distance);
                            r1.loc=&loc1;
                            for(int q=0;q<userSize;q++)
                            {

                             if(us[q]->userId==cust_id)
                                {
                                 int custid=us[q]->userId;
                                 string custname=us[q]->userName;
                                 string custpss=us[q]->password;
                                 int custpno=us[q]->phNo;

                                 r1.customers=new Customer(custid,custname,custpss,custpno,"hubli");

                                 }


                                     cout<<endl<<endl;
                            }
                                cout<<"Ride Details :"<<endl<<endl;
                                r1.rideDetails();

                               cout<<endl<<"total fare ="<<r1.farecalculation()<<endl;
                     cout<<endl<<"----------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                  break;
                  case :6
                        while(1){
                                stat=0;
                          cout<<" [1] UPI"<<endl<<" [2] Pay from ride wallet"<<endl;
                          Paymentportal p(12,"not completed","UPI",500);
                             cin>>nom;
                             try{
                             switch(nom)
                             {
                             case 1:
                                    cout<<"PAYMENT SUCCESSFUL"<<endl;
                                    cout<<endl<<endl;

                                    cout<<"RECIEPT GENERATION "<<endl;
                                    p.generatereciept(r1);
                                    stat=1;
                                    status=4;
                                    break;
                             case 2:
                                 cout<<"Wallet  "<<endl;
                                 status=4;
                                 p.payWallet(r1);

                             }
                             }
                             catch(ApplicationException & ap)
                             {
                                 ap.showError();
                             }
                             if(stat==1)
                             {
                                 break;
                             }
                        }
                        break;

                 }
                 break;

            case 3:
                if(status==0){
                ride.setRideState(new nonRequestedState());
                ride.requestRide();
                }
                else if(status==1)
                {
                  ride.setRideState(new OnRouteState());
                ride.requestRide();
                }
                else if(status==3)
                {
                   ride.setRideState(new canceledState());
                   ride.requestRide();
                }
                else if(status==4)
                {
                    ride.setRideState(new CompletedState());
                   ride.requestRide();
                }
                break;
            case 4:if(status==0){
                  ride.setRideState(new nonRequestedState());
                ride.cancelRide();}
                else if(status==1)
                {
                    status=3;
                    ride.setRideState(new OnRouteState());
                ride.cancelRide();
                }
                 else if(status==3)
                {
                   ride.setRideState(new canceledState());
                   ride.cancelRide();
                }
                else if(status==4)
                {
                    ride.setRideState(new CompletedState());
                   ride.cancelRide();
                }
                break;
            case 5:
                if(status==0){
                ride.setRideState(new nonRequestedState());
                ride.startRide();}
                else if(status==1)
                {
                ride.setRideState(new OnRouteState());
                ride.startRide();
                }
                 else if(status==3)
                {
                   ride.setRideState(new canceledState());
                   ride.startRide();
                }
                else if(status==4)
                {
                    ride.setRideState(new CompletedState());
                   ride.startRide();
                }
                break;

            }

    }
}
catch(ApplicationException &a)
{
    a.showError();


}
return 0;
}











/*
int main(){
    int rideid=0;
    Vehicle vehicle[]={Vehicle(1000,"KA25 B 2345","Tavera",6,4,2000,50),Vehicle(1001,"KA26 B 3489","Passion",2,2,200,20),Vehicle(1002,"KA19EQ1306","Toyota RAV4",6,4,1000,50)};
  User *us[]={new Customer(1,"alwyn","ally",938048,"hubli"),new Driver(1000,"sandeep","sand",1923,"yes",vehicle[0]), new Driver(1001,"Rahul","RAHH",89767,"yes",vehicle[1])};

  Login l1;
    for (int i = 0; i < 2; i++) {
        l1.users[i] = us[i];
    }
  int cust_id=l1.logincred();

 //std::this_thread::sleep_for(std::chrono::seconds(2));



  cout<<endl<<"Where do you wanna go today?";

  //std::this_thread::sleep_for(std::chrono::seconds(2));

 cout<<endl<<endl;
  cout<<"available taxis in nearby neighbor hood"<<endl;
  for(int i=0;i<3;i++)
  {

      if(us[i]->userId>999)
      {
          us[i]->printUser();
      }
     // std::this_thread::sleep_for(std::chrono::seconds(2));

      cout<<endl<<endl;
  }
  cout<<"select the taxi id you want"<<endl;
  int taxi_id,j;
  cin>>taxi_id;

  Ride r1(rideid++,0,"12-07-22","12:45 PM","Ride available");
  for(int i=0;i<3;i++)
  {

      if(us[i]->userId==taxi_id)
      {

          cout<<"entering in ride"<<endl;

          int driverid=us[i]->userId;
           string name=us[i]->userName;
           string pss=us[i]->password;
           int pno=us[i]->phNo;
           for(j=0;j<3;i++)
           {
               if(vehicle[j].driverId==driverid)
               {
                   break;
               }
           }

          r1.drivers=new Driver(driverid,name,pss,pno,"yes",vehicle[j]);
      }


      cout<<endl<<endl;
  }
  cout<<"the driver selected for ride is "<<endl;
  string pick,drop;
  double distance;
  cout<<"Enter the pickup location :";
  cin>>pick;
  cout<<endl<<"Enter the drop location :";
  cin>>drop;
  cout<<endl<<"Enter the distance :";
  cin>>distance;
  Location loc1(pick,drop,distance);
   r1.loc=&loc1;
    for(int i=0;i<3;i++)
  {

      if(us[i]->userId==cust_id)
      {
          int custid=us[i]->userId;
           string custname=us[i]->userName;
           string custpss=us[i]->password;
           int custpno=us[i]->phNo;



          r1.customers=new Customer(custid,custname,custpss,custpno,"hubli");
      }


      cout<<endl<<endl;
  }

  r1.rideDetails();

  cout<<"total fare ="<<r1.farecalculation()<<endl;

   Paymentportal p(12,"not completed","UPI");
   p.generatereciept(r1);


  return 0;

}


*/





