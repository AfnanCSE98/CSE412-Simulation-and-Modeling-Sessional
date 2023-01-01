#include <bits/stdc++.h>
using namespace std;

const double INF = 1e99;
const int Q_LIMIT = 100000000;

bool is_arrival_event;// 1 = arival , 0 = departure

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

double get_exponential_sample(double mean)
{
    double u = uniform_real_distribution<double>(0, 1)(rng);
    double e = -mean * log(u);

    return e;
}

class SSQS
{
public:
    double mean_interval_time;
    double mean_service_time;
    int number_of_customers;

    bool is_server_busy;
    int number_in_queue;
    queue<double> times_of_arrival;
    double time_of_last_event;
    double clock;
    double next_A;
    double next_D;

    int number_delayed;
    double total_delay;
    double area_under_qt;
    double area_under_bt;

    double avg_delay;
    double avg_number_in_queue;
    double server_utilization;

    SSQS(double _mean_interval_time, double _mean_service_time, double _number_of_customers){
        mean_interval_time = _mean_interval_time;
        mean_service_time = _mean_service_time;
        number_of_customers = _number_of_customers;
    }

    void initialize()
    {
        is_server_busy = false;
        number_in_queue = 0;
        time_of_last_event = 0;
        clock = 0;
        next_A = get_exponential_sample(mean_interval_time); // first customer arrival time
        next_D = INF; // no customer is currently being served, hence next departure time is infinity

        number_delayed = 0;
        total_delay = 0;
        area_under_qt = 0;
        area_under_bt = 0;
    }

    bool get_next_event_type()
    {
        if(next_A < next_D) return 1; // next customer arrival is coming before current customer finishes being served
        else return 0;
    }

    int get_bt()
    {
        return is_server_busy? 1: 0;
    }

    void set_average_delay(double a_d)
    {
        avg_delay = a_d;
    }

    void set_average_number_in_queue(double a_n_q){
        avg_number_in_queue = a_n_q;
    }

    void set_server_utilization(double s_u){
        server_utilization = s_u;
    }

    double get_average_delay()
    {
        return avg_delay;
    }

    double get_average_number_in_queue()
    {
        return avg_number_in_queue;
    }

    double get_server_utilization()
    {
        return server_utilization;
    }

    double get_final_time()
    {
        return clock;
    }

    void simulate()
    {
        while(number_delayed < number_of_customers)
        {
            bool next_event_arrival = get_next_event_type();

            if(next_event_arrival)//ARRIVAL
            {
                /* Schedule next arrival. */
                clock = next_A;
                next_A += get_exponential_sample(mean_interval_time); // scheduling next arrival event

                area_under_qt += (clock-time_of_last_event) * number_in_queue;
                area_under_bt += (clock-time_of_last_event) * get_bt();

                if(is_server_busy)
                {
                    /* Server is busy, so increment number of customers in queue. */
                    number_in_queue++; 
                    
                    if(number_in_queue>Q_LIMIT){
                        cout<<"Queue overflown!\n";
                        exit(0);
                    }
                    /* There is still room in the queue, so store the time of arrival of the */
                    times_of_arrival.push(clock);
                    
                }
                else
                {
                    /* Server is idle, so arriving customer has a delay of zero.*/
                    double delay = 0;

                    total_delay += delay;
                    
                    /* Increment the number of customers delayed, and make server busy. */
                    number_delayed++;
                    is_server_busy = true;

                    /* Schedule a departure (service completion). */
                    next_D = clock + get_exponential_sample(mean_service_time);
                }
            }
            else
            {

                clock = next_D;

                area_under_qt += (clock-time_of_last_event) * number_in_queue;
                area_under_bt += (clock-time_of_last_event) * get_bt();

                /* Check to see whether the queue is empty. */
                // If no customer is waiting in the queue, so server will be idle and no next departure event
                if(times_of_arrival.empty())
                {
                    is_server_busy = false;
                    next_D = INF;
                }
                else
                {
                    /* The queue is nonempty, so decrement the number of customers in queue. */
                    number_in_queue--;

                    double current_arrival_time = times_of_arrival.front();
                    times_of_arrival.pop();

                    /* Compute the delay of the customer who is beginning service and update the total delay accumulator. */
                    double delay = clock-current_arrival_time;
                    total_delay += delay;
                    /* Increment the number of customers delayed, and schedule departure. */
                    number_delayed++;
                    
                    next_D = clock+get_exponential_sample(mean_service_time);
                }
            }
            time_of_last_event = clock;
        }
    }

    void generate_output(){
        set_average_delay(total_delay/number_of_customers);
        set_average_number_in_queue(area_under_qt/clock);
        set_server_utilization(area_under_bt/clock);
    }

};