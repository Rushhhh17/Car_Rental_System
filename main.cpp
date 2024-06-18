#include<iostream>
#include<mysql.h>// necessary to est connection
#include<mysqld_error.h>//handle errors
#include<windows.h>//
#include<sstream>//
using namespace std;

const char * HOST= "localhost";
const char* USER = "root";
const char* PW ="j@meS1122";
const char* DB="projectcpp";

class Car{
    private:
    string Brand , Model;
    int Serial, Rent ;
    bool Avail;
    public:
    Car( int serial , string brand , stringp model , int rent, bool avail){
        Serial=serial;
        Rent=rent;
        Brand=brand;
        Model=model;
        Avail=avail;

    }//default constructor is created and formal argument is passed above
     
     int getSerial(){
        return Serial;
        }// function 1

      string getBrand(){
        return Brand;

      }  //function 2

      string getModel(){
        return Model;
      }//fun3

      int getRent()
      {
        return Rent;
      }//fun3
      bool getAvail(){
        return Avail;
      }
};

int main (){
MYSQL* conn;
conn= mysql_init(NULL);
if (!mysql_real_connect(conn, HOST, USER , PW , DB, 33060, NULL , 0)){
    cout<<"ERROR:"<<mysqld_error(conn)<<endl;  // if error occurs this willl handle thhe error
}
//otherwise 
else{
    cout<<"LOggeed in!!"<<endl;

}

mysql_close(conn);


    return 0;

}
