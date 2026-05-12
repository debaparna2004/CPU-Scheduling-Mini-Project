#include <iostream>
#include <algorithm>
using namespace std;

struct Process {
    int id, bt, wt, tat;
};

void display(Process p[], int n) {
    float avgwt = 0, avgtat = 0;

    cout << "\nPID\tBT\tWT\tTAT\n";

    for(int i = 0; i < n; i++) {
        cout << p[i].id << "\t"
             << p[i].bt << "\t"
             << p[i].wt << "\t"
             << p[i].tat << endl;

        avgwt += p[i].wt;
        avgtat += p[i].tat;
    }

    cout << "\nAverage Waiting Time: " << avgwt / n;
    cout << "\nAverage Turnaround Time: " << avgtat / n;
}

void fcfs(Process p[], int n) {

    p[0].wt = 0;

    for(int i = 1; i < n; i++) {
        p[i].wt = p[i-1].wt + p[i-1].bt;
    }

    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
    }

    cout << "\nFCFS Scheduling\n";
    display(p, n);
}

void sjf(Process p[], int n) {

    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {

            if(p[i].bt > p[j].bt) {
                swap(p[i], p[j]);
            }
        }
    }

    p[0].wt = 0;

    for(int i = 1; i < n; i++) {
        p[i].wt = p[i-1].wt + p[i-1].bt;
    }

    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
    }

    cout << "\nSJF Scheduling\n";
    display(p, n);
}

void roundRobin(Process p[], int n, int tq) {

    int rem[n];
    int time = 0;

    for(int i = 0; i < n; i++) {
        rem[i] = p[i].bt;
    }

    while(true) {

        bool done = true;

        for(int i = 0; i < n; i++) {

            if(rem[i] > 0) {

                done = false;

                if(rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                }

                else {
                    time += rem[i];
                    p[i].wt = time - p[i].bt;
                    rem[i] = 0;
                }
            }
        }

        if(done == true)
            break;
    }

    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
    }

    cout << "\nRound Robin Scheduling\n";
    display(p, n);
}

int main() {

    int n, choice, tq;

    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    for(int i = 0; i < n; i++) {

        p[i].id = i + 1;

        cout << "Enter burst time for P" << i+1 << ": ";
        cin >> p[i].bt;
    }

    cout << "\n1. FCFS";
    cout << "\n2. SJF";
    cout << "\n3. Round Robin";

    cout << "\nEnter choice: ";
    cin >> choice;

    if(choice == 1) {
        fcfs(p, n);
    }

    else if(choice == 2) {
        sjf(p, n);
    }

    else if(choice == 3) {

        cout << "Enter Time Quantum: ";
        cin >> tq;

        roundRobin(p, n, tq);
    }

    else {
        cout << "Invalid Choice";
    }

    return 0;
}