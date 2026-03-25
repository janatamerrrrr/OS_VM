#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int arrival;
    int burst;
    int wait;
};

//firstcome.firstserve
void FCFS(Process p[], int n) {
    int time = 0;
    for(int i = 0; i < n; i++) {
        if(time < p[i].arrival) time = p[i].arrival;
        p[i].wait = time - p[i].arrival;
        time += p[i].burst;
    }
}

//shortest.job.first
void SJF(Process p[], int n) {
    int time = 0, done = 0;
    bool completed[100] = {false};
    
    while(done < n) {
        int shortest = -1;
        int minBurst = 99999;
        
        for(int i = 0; i < n; i++) {
            if(!completed[i] && p[i].arrival <= time && p[i].burst < minBurst) {
                minBurst = p[i].burst;
                shortest = i;
            }
        }
        
        if(shortest == -1) {
            time++;
        } else {
            p[shortest].wait = time - p[shortest].arrival;
            time += p[shortest].burst;
            completed[shortest] = true;
            done++;
        }
    }
}

//roundrobin
void RR(Process p[], int n, int quantum) {
    int time = 0, done = 0;
    int remaining[100];
    queue<int> q;
    bool inQueue[100] = {false};
    
    for(int i = 0; i < n; i++) remaining[i] = p[i].burst;
    
    for(int i = 0; i < n; i++) {
        if(p[i].arrival <= time) {
            q.push(i);
            inQueue[i] = true;
        }
    }
    
    while(done < n) {
        if(q.empty()) {
            time++;
            for(int i = 0; i < n; i++) {
                if(p[i].arrival <= time && remaining[i] > 0 && !inQueue[i]) {
                    q.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }
        
        int i = q.front();
        q.pop();
        inQueue[i] = false;
        
        if(remaining[i] > quantum) {
            time += quantum;
            remaining[i] -= quantum;
        } else {
            time += remaining[i];
            remaining[i] = 0;
            p[i].wait = time - p[i].arrival - p[i].burst;
            done++;
        }
        
        for(int j = 0; j < n; j++) {
            if(p[j].arrival <= time && remaining[j] > 0 && !inQueue[j]) {
                q.push(j);
                inQueue[j] = true;
            }
        }
        
        if(remaining[i] > 0) {
            q.push(i);
            inQueue[i] = true;
        }
    }
}

float average(Process p[], int n) {
    int total = 0;
    for(int i = 0; i < n; i++) {
        total += p[i].wait;
    }
    return (float)total / n;
}

int main() {
    int n = 3;
    int quantum = 2;
    
    Process fcfs[100] = {
        {0, 5, 0},
        {1, 3, 0},
        {2, 4, 0}
    };
    
    Process sjf[100], rr[100];
    for(int i = 0; i < n; i++) {
        sjf[i] = fcfs[i];
        rr[i] = fcfs[i];
    }
    
    FCFS(fcfs, n);
    SJF(sjf, n);
    RR(rr, n, quantum);
    
    cout << "FCFS: " << average(fcfs, n) << endl;
    cout << "SJF : " << average(sjf, n) << endl;
    cout << "RR  : " << average(rr, n) << endl;
    
    return 0;
}