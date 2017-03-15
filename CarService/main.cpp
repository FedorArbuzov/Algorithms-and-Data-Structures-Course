///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Main entry point
///
/// This file contains a partial implementation for the simulation. It is
/// task for students to finish this implementation.
///
///////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stack>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "car.h"



const int PARKING_SPOTS_PER_AISLE = 3;      ///< Determines a number of cars per an aisle
const int NUMBER_OF_AISLES = 5;             ///< Determines a number of aisls in the parking


/** \brief Defines an Aisle in some parking */
typedef std::stack<std::string> ParkAisle;

/** \brief Defines a parking containing some aisles */
typedef std::vector< ParkAisle > Parking;

/** \brief Defines a collection of cars most likely implemented as a vector of cars */
typedef std::vector<Car> Cars;



/** \brief Iterates through the vector of stacks, looking for the first stack that 
 *  does not contain three cars. If all five aisles (stacks) are full, output a message 
 *  indicating such; otherwise place the license plate into the first non-full stack.
 */
void handle_arrival(Cars& cars, Parking& parking_lot,
    const std::string& plate);


/** \brief Locates the departing vehicle from the \a cars vector using function \a find_car() and
 *  removes the departing car's license plate from the corresponding aisle.
 */
void handle_departure(Cars& cars, Parking& parking_lot, const std::string& plate);


/** \brief Returns a reference to the \a Car object stored in the vector \a cars 
 *  whose license plate equals the parameter \a plate.
 */
Car& find_car(Cars& cars, const std::string& plate);


//------------------------------------------------------------------------------


/** \brief Main entry point of the program
 *
 *  Should obtain at least 1 command line parameter, which is interpreted as the name of a 
 *  file with parking day's payload
 */
int main(int argc, char* argv[]) 
{
    try {
        if (argc < 2)       
        {                   
            std::cerr << "Usage:\n" << argv[0] << " data-file";
            return EXIT_FAILURE;
        }    

        std::ifstream inf(argv[1]);
        if (!inf) 
        {
            std::cerr << "Could not open " << argv[1];
            return EXIT_FAILURE;
        }

        Cars cars;
        Parking parking_lot(NUMBER_OF_AISLES);

        while (!inf.eof()) 
        {
        
            std::string action, plate;
            inf >> plate >> action;
        
            if (action == "arrives") 
            {
                //std::cout << "car arrive" << std::endl;
                handle_arrival(cars, parking_lot, plate);
            } 
            else if (action == "departs") 
            {
                handle_departure(cars, parking_lot, plate);            
            } else 
            {
                std::cerr << "Unknown action: " << action << std::endl;
            }
        
        }
        inf.close();    

        std::cout << "\nHere are all the cars that visited the lot today:\n";

        // TODO: Output the license plates of all the
        // cars that visited the lot, in alphabetical order		

        std::sort(cars.begin(), cars.end());

        for(int i = 0; i < cars.size(); i++ ){
            std::cout << cars[i].getPlate() << " moved " << cars[i].getTimesMoved() << " times" << " \n";
        }




        return EXIT_SUCCESS;        
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception caught!" << std::endl;
    }
    
    return EXIT_FAILURE;
}

//------------------------------------------------------------------------------

/** 
 *  This is essentially "parking" the car. For this
 *  arriving car, also add an entry of type \a Car to the vector \a cars. In this \a Car instance, 
 *  make sure to record properly the index of the aisle where this car is parked. 
 */
void handle_arrival(Cars& cars, Parking& parking_lot,
    const std::string& plate) 
{
    // TODO: Handle car arrivals


    // count for cars in parking lot
    int count = 0;


    // loop for add car
    for(int i = 0; i < parking_lot.size(); i++){
        if(parking_lot[i].size() < PARKING_SPOTS_PER_AISLE){

            // add car in parking lot
            parking_lot[i].push(plate);

            // add car in cars array
            cars.push_back(Car(plate, i));

            // out of the loop
            break;
        }
        else{

            // ++ count else
            count++;

        }
    }

    if(count == 5){


        // if count == 5 there is no empty space
        std::cout << "All parking lots are full" << std::endl;

    }

}

//------------------------------------------------------------------------------


/** 
 *  Another stack must be used to move, temporarily, any cars that may be in front of the
 *  departing car. Record the number of times a car is moved when accommodating the
 *  departure of another car. For the departing car, display the number of times it was moved
 *  while it was parked in the lot.
 */
void handle_departure(Cars& cars, Parking& parking_lot, const std::string& plate)
{
    // TODO: Handle car departures


    // find car in car vector
    Car car = find_car(cars, plate);

    // get aisle from car
    int ais = car.getAisle();

    // buffer for cars
    ParkAisle buffer;

    // find car in "ais" aisle
    while(parking_lot[ais].top() != car.getPlate()){

        // new variable for car name
        std::string& carName = parking_lot[ais].top();

        // add car in buffer
        buffer.push(carName);

        // delete car from aisle
        parking_lot[ais].pop();
    }

    // delete car after finding
    parking_lot[ais].pop();

    // print times moved for car
    std::cout << plate << " moved " << car.getTimesMoved() << " times" << std::endl;


    // add cars from buffer in parking lot
    while(!buffer.empty()){

        // variable for car from buffer
        std::string& carName = buffer.top();

        // add car from buffer in parking lot
        parking_lot[ais].push(carName);

        // variable from cars vector
        Car* move = &find_car(cars, buffer.top());

        // update times moved for new car
        move->setTimesMoved(move->getTimesMoved() + 1);

        // delete car from buffer
        buffer.pop();
    }

}


//------------------------------------------------------------------------------


/** 
 *  Use the STL \a find() function to perform this task. To use the function correctly, you
 *  must supply it with three arguments. The first two arguments specify a range to search.
 *  The third argument is the value that the function attempts to find. This argument must be
 *  of type \a Car.
 *
 *  * http://www.cplusplus.com/reference/algorithm/find/
 */
Car& find_car(Cars& cars, const std::string& plate)
{
    // TODO: Return a reference to 
    // the Car object whose license plate equals 
    // the parameter 'plate'

    // new iterator from find method
    Cars::iterator it = std::find(cars.begin(), cars.end(), plate);

    // return car or throw exception
    if(it != cars.end()){
        return *it;
    }
    else{
        throw std::logic_error("car not found");
    }
}
