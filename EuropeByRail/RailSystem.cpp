#pragma warning (disable:4786)
#pragma warning (disable:4503)
#include "RailSystem.h"

void RailSystem::reset(void) {


    // TODO: reset the data objects of the 
    // City objects' contained in cities

    // create iterator for City map
    map<string, City*>::iterator city_it;

    // loop in cities map
    for (city_it = cities.begin(); city_it != cities.end(); ++city_it)
    {

        // get city from map
        City* c = city_it->second;


        c->total_fee = INT_MAX;
        c->visited = false;
        c->from_city = "";
    }
    
}

RailSystem::RailSystem(string const &filename) {
    
    load_services(filename);
}

void RailSystem::load_services(string const &filename) {

	ifstream inf(filename.c_str());

    string from, to;

    int fee, distance;




    while ( inf.good() ) {

		// Read in the from city, to city, the fee, and distance.
		inf >> from >> to >> fee >> distance;

		if ( inf.good() ) {
		
			// TODO: Add entries in the cities container and
			// and services in the rail system for the new
            // cities we read in.


			// add new city in cities array
			cities[from] = new City(from);


    		// push new service in outgoing services
			outgoing_services[from].push_back(new Service(to, fee, distance));
		}
	}

	inf.close();

}

RailSystem::~RailSystem(void) {

    // TODO: release all the City* and Service*
    // from cities and outgoing_services


    // iterator for city map
    map<string, City*>::iterator c_iter;

    // loop for iterating
    for (c_iter = cities.begin(); c_iter != cities.end(); ++c_iter)
    {
        // delete city
        delete c_iter->second;
    }


    // loop for service map
    for (map<string, std::list<Service*>>::iterator it_serv = outgoing_services.begin(); it_serv != outgoing_services.end(); ++it_serv)
    {

        // loop in list
        for (std::list<Service*>::iterator it_list = it_serv->second.begin(); it_list != it_serv->second.end(); ++it_list)

            // delete in list
            delete *it_list;

    }

}

void RailSystem::output_cheapest_route(const string& from,
                const string& to, ostream& out) {

	reset();
	pair<int, int> totals = calc_route(from, to);

	if (totals.first == INT_MAX) {
		out << "There is no route from " << from << " to " << to << "\n";
	} else {
		out << "The cheapest route from " << from << " to " << to << "\n";
		out << "costs " << totals.first << " euros and spans " << totals.second
			<< " kilometers\n";
        cout << recover_route(to) << "\n\n";
	}
}

bool RailSystem::is_valid_city(const string& name) {

	return cities.count(name) == 1;
}

pair<int, int> RailSystem::calc_route(string from, string to) {
    // You can use another container
	priority_queue<City*, vector<City*>, Cheapest> candidates;

    // TODO: Implement Dijkstra's shortest path algorithm to
    // find the cheapest route between the cities

    // initialise start city


    // distance to 0
    cities[from]->total_distance = 0;


    // fee to 0
    cities[from]->total_fee = 0;

    // create iterator for City map
    map<string, City*>::iterator city_it;

    // loop in cities map
    for (city_it = cities.begin(); city_it != cities.end(); ++city_it)
    {

        // get city from map
        City* c = city_it->second;

        // add city to candidates
        candidates.push(c);
    }


    while (candidates.size() != 0) {

        // get city from candidates
        City* city = candidates.top();


        // visit this city  and remove
        cities[city->name]->visited = true;
        candidates.pop();


        // city == to then break
        if (city->name == to) {

            // out of the loop
            break;

        }

        string city_name = city->name;
        // iterate over adjacent vertices
        for (const auto& service_n : outgoing_services[city_name]) {


            // move to other city
            City* city_new = cities[service_n->destination];

            // change fee
            int fee_tsn = city->total_fee + service_n->fee;

            // check fee
            if (fee_tsn < city_new->total_fee)
            {


                // set new from_city for city_new
                city_new->from_city = city->name;


                // set new distance
                int d = city->total_distance + service_n->distance;

                city_new->total_distance = d;

                // change fee for new city
                city_new->total_fee = fee_tsn;

            }
        }


        //This is a bit hackish, but nothing illegal about it, and it gets the job done.
        std::make_heap(const_cast<City**>(&candidates.top()), const_cast<City**>(&candidates.top()) + candidates.size(), Cheapest());
    }


    // Return the total fee and total distance.
    // Return (INT_MAX, INT_MAX) if not path is found.
    if (cities[to]->visited) {
            return pair<int,int>(cities[to]->total_fee, cities[to]->total_distance);
    } else {
            return pair<int,int>(INT_MAX, INT_MAX);
    }

}

string RailSystem::recover_route(const string& city) {
	
    // TODO: walk backwards through the cities
    // container to recover the route we found


    // get city from cities map
    City* ct = cities[city];


    // string for returning
    string r = ct->name;

    // loop for finding start city
    while (ct->from_city != "") {


        // new city
        ct = cities[ct->from_city];

        // add city to return value
        r = ct->name + " to " + r;
    }


    // return string
    return r;
}


Route RailSystem::getCheapestRoute(const string& from, const string& to){
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    pair<int, int> p =  calc_route(from,to);
    return Route(from,to,p.first,p.second);
}