// Homework 2.cpp : Defines the entry point for the application.
//Worked with Gabby Hontz and Cece Erndwine 

#include "Homework 2.h"  

using namespace std;

class Plane
{
protected:
    double wait_time;
private:
    double pos, vel, distance, loiter_time;
    bool at_SEC;
    string origin, destination;
    map<string, map <string, int>> mp;
public:
    Plane(const string& from,const string& to)
    {
        origin = from;
        destination = to;
        mp["SEC"]["PHL"] = 160;
        mp["SEC"]["ORD"] = 640;
        mp["SEC"]["EWR"] = 220;
        distance = mp[origin][destination];

        pos = 0;
        vel = 0;
        wait_time = 0;
        loiter_time = 0;
        at_SEC = 0;

    }
    virtual ~Plane()
    {
    }
    void operate(double dt)
    {
        if (loiter_time != 0)
        {
            loiter_time -= dt;
        }

        else if (wait_time != 0)
        {
            wait_time -= dt;
        }

        else if (pos < distance)
        {
            pos += vel * dt;
            at_SEC = 0;
        }
        else if (destination == "SEC")
        {
            at_SEC = 1;
            time_on_ground();

            string Swap;
            Swap = origin;
            origin = destination;
            destination = Swap;
            pos = 0.0;
        }
        else
        {
            time_on_ground();
            string Swap;
            Swap = origin;
            origin = destination;
            destination = Swap;
            pos = 0.0;
        }

    }

    double get_pos() const
    {
        return pos;
    }
    double get_vel() const
    {
        return vel;

    }
    double get_loitertime() const
    {
        return loiter_time;

    }
    string get_origin() const
    {
        return origin;

    }
    string get_destination() const
    {
        return destination;

    }
    bool get_atSEC() const
    {
        return at_SEC;

    }
    void set_vel(double velocity)
    {
        vel = velocity;
    }
    void set_loiter_time(double loiter)
    {
        loiter_time = loiter;
    }
    
    double distance_to_SEC()
    {
        if (destination == "SEC")
            return distance - pos;

        else
            return 0.0;
    }
    virtual double time_on_ground() 
    {
        return 0.0;
    }
    virtual string plane_type(string plane_type)
    {
        plane_type = "GA";
        return plane_type;
    }
    static double draw_from_normal_dist(double mean, double stdev)
    {
        random_device rd{};
        mt19937 gen{ rd() }; 
        normal_distribution<> d(mean, stdev);
        return d(gen);
    }
};
class Airliner :public Plane
{
private:
    string Airline;
public:
    Airliner(const string& Airline, const string& from, const string& to) :Plane(from, to), Airline(Airline) {}//constructor 
   ~Airliner (){}//empty deconstructor 
   string plane_type() //override 
   {
       return Airline;
   }
   double time_on_ground()//override
   {
      return draw_from_normal_dist(1800, 600);

   }
};
class GeneralAviation :public Plane
{public:
    GeneralAviation(const string& from,const string& to) :Plane(from, to) {}//constructro 
    ~GeneralAviation() {}//empty deconstructor 
    
    double time_on_ground()//override
    {
        return draw_from_normal_dist(1800, 600);

    }
};

int main(int argc,char** argv)
{//Questsoin one 
    
    // Distance in miles between airports 
    map<string, map <string, int>> mp;
    mp["SEC"]["PHL"] = 160;
    mp["SEC"]["ORD"] = 640;
    mp["SEC"]["EWR"] = 220;
   
    Airliner AmericanAirlines1("AA", "SEC", "PHL");
    AmericanAirlines1.set_vel(470.0 / 3600.0);
    Airliner United1("UA", "SEC", "ORD");
    United1.set_vel(515.0 / 3600.0);
    Airliner AmericanAirlines2("AA", "SEC", "ORD");
    AmericanAirlines2.set_vel(500.0 / 3600.0);
    Airliner United2("UA", "SEC", "EWR");
    United2.set_vel(480.0 / 3600.0);
    GeneralAviation GA1("SEC","PHL");
    GA1.set_vel(140.0 / 3600.0);
    GeneralAviation GA2("SEC", "EWR");
    GA2.set_vel(160.0 / 3600.0);
    GeneralAviation GA3("SEC", "ORD");
    GA3.set_vel(180.0 / 3600.0);

    double timestep = 36;

   vector<Plane*> Air;
        Air.push_back(&AmericanAirlines1);
        Air.push_back(&AmericanAirlines2);
        Air.push_back(&United1);
        Air.push_back(&United2);
        Air.push_back(&GA1);
        Air.push_back(&GA2);
        Air.push_back(&GA3);

    while (true)
    {
        double wait_time = 5;
        double loiter_time = 10;

        for (Plane* this_plane : Air)
        {
           this_plane-> operate(timestep);

           cout<<"from " << this_plane->get_origin() << " to " << this_plane->get_destination() << endl;
           cout << "Position " << this_plane->get_pos() << " miles" << endl;
           

        }
       
    }


	return 0;
}
