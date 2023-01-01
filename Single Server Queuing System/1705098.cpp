#include <bits/stdc++.h>

#include "ssqs.h"

using namespace std;

int main()
{
    double mean_interval_time;
    double mean_service_time;
    int number_of_customers;

    ifstream ifile("input.txt");
    ifile >> mean_interval_time;
    ifile >> mean_service_time;
    ifile >> number_of_customers;

    SSQS ssqs(mean_interval_time, mean_service_time, number_of_customers);

    ssqs.initialize();

    ssqs.simulate();

    ssqs.generate_output();

    ofstream fout("output.txt");

    fout << "Single-server queuing system" << endl;
    fout << "Mean interval time = " << mean_interval_time << endl;
    fout << "Mean service time = " << mean_service_time << endl;
    fout << "Number of customers = " << number_of_customers << endl << endl << endl;

    fout << "Average delay in queue = " << ssqs.get_average_delay() << endl;
    fout << "Average number in queue = " << ssqs.get_average_number_in_queue() << endl;
    fout << "Server utilization = " << ssqs.get_server_utilization() << endl;
    fout << "Time simulation ended = " << ssqs.get_final_time() << endl;

    fout.close();
    return 0;
}