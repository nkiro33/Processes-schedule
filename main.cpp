#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <string.h>
#include <iterator>
#include <cassert>
#include <queue>
#include <bits/stdc++.h>
#include <math.h>
#include <cstring>
# define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))

using namespace std;
struct process
{

    char name;
    int arrival_time;
    int service_time;
};
bool operator<(const process& p1,const process& p2)
{
    if(p1.service_time<p2.service_time)
        return true;
    else if(p1.service_time==p2.service_time)
    {
        if(p1.arrival_time>p2.arrival_time)
            return true;
        else
            return false;
    }

    else
        return false;
    //return p1.service_time < p2.service_time;
}
void printQueue(priority_queue<process> q)
{
    //printing content of queue
    while (!q.empty())
    {
        cout<<" "<<q.top().name;
        q.pop();
    }
    cout<<endl;
}
void dashes(int last_instant)
{
    cout<<"--------";
    int times =last_instant/10;
    for(int i=0; i<times; i++)
    {
        for(int j=0; j<20; j++)
        {
            cout<<"-";
        }
    }
    cout<<"\n";
}

void stats(string nameofalgo,char names[],int arrival_time[],int service_time[],int finish1[],int number)
{
    cout << nameofalgo << "\n";
    string process="Process    |";
    string arrival="Arrival    |";
    string service="Service    |";
    string finish="Finish     |";
    string turnaround="Turnaround |";
    string normturn="NormTurn   | ";
    int turn=0;
    char name;
    float turn_total=0;
    float norm=0;
    float norm_total=0;
    int counter=0;
    int process_arrival,process_service,finish_time;
    for(int i=0; i<number; i++)
    {
        name = names[i];
        process_arrival = arrival_time[i];
        process_service = service_time[i];
        process = process +"  " + name + "  |";
        if(process_arrival<10)
            arrival = arrival + "  "+ to_string(process_arrival) + "  |";
        else
            arrival = arrival + " "+ to_string(process_arrival) + "  |";
        if(process_service<10)
            service = service + "  " + to_string(process_service) + "  |";
        else
            service = service + "  " + to_string(process_service) + "  |";
        finish_time=finish1[counter];
        if(finish_time<10)
            finish = finish + "  " + to_string(finish_time)+ "  |";
        else
            finish = finish + " " + to_string(finish_time)+ "  |";
        turn = finish_time-process_arrival;
        turn_total = turn_total + turn;
        if(turn<10)
            turnaround = turnaround + "  " + to_string(turn) + "  |";
        else
            turnaround = turnaround + " "+ to_string(turn) + "  |";
        norm = turn / float(process_service);
        norm_total= norm_total + norm;
        norm = round(100*norm)/100;
        string norms = to_string(norm);
        norms = norms.substr(0, norms.find(".")+3);
        normturn = normturn + norms + "| ";
        counter++;
    }
    norm_total = round(100*norm_total/counter)/100;
    turn_total = round(100*turn_total/counter)/100;
    string norm_totals = to_string(norm_total);
    norm_totals = norm_totals.substr(0, norm_totals.find(".")+3);
    string turn_totals = to_string(turn_total);
    turn_totals = turn_totals.substr(0, turn_totals.find(".")+3);
    if(turn_total<10)
        turnaround = turnaround + " "+ turn_totals + "|";
    else
        turnaround = turnaround + turn_totals + "|";
    normturn = normturn + norm_totals + "|";
    service = service + " Mean|";
    finish = finish + "-----|";
    cout << process << "\n";
    cout << arrival << "\n";
    cout << service << "\n";
    cout << finish << "\n";
    cout << turnaround << "\n";
    cout << normturn << "\n";



}
void tokenize(string const &str, const char delim,vector<string> &out)
{
    // construct a stream from the string
    stringstream ss(str);

    string s;
    while (getline(ss, s, delim))
    {
        out.push_back(s);
    }
}
int in_array(const int store[],const int x, const int query)
{
    for (int i=0; i<x; ++i)
    {
        if (store[i] == query)
        {
            return 1;
        }
    }
    return 0;
}
void aging(int x1,int x2,int x4,process x10[])  // x1=quantam ,x2=last instant , x4=number of processes ,x10=processes
{
    process x3[x4];
    for(int i=0; i<x4; i++)
        x3[i]=x10[i];
    priority_queue<process> q;
    string rr = "Aging 0";
    int x=1;
    for(int i=0; i<x2; i++)
    {
        stringstream ss;
        ss<<x;
        string s;
        ss>>s;
        rr = rr + " " + s;
        if (x==9)
            x=0;
        else
            x++;
    }
    string output[x4];
    string processes[x4];
    int service_constant[x4];
    int i;
    char name;
    int counter = 0;
    for (i=0; i<x4; i++)
    {
        name = x3[i].name;
        output[i] = output[i] + name + "     |";
        counter++;
        service_constant[i] = x3[i].service_time;
    }
    counter=0;
    int current_time=0;
    int y=0;
    string v;
    process xz,xy[x4];
    int start=0;
    while(current_time<=(x2-1))
    {
        for(i=start; i<x4; i++)
        {
            if(x3[i].arrival_time<=(current_time))
            {
                q.push(x3[i]);
                start++;
            }
        }
        y=0;
        if(q.empty())
            current_time++;
        else
        {
            xz=q.top();
            q.pop();
            int j=0;
            int save;
            while(j<x1)
            {
                for(i=0; i<x4; i++)
                {
                    if(xz.name==x3[i].name)
                    {
                        save=i;
                        output[i] = output[i] + "*|";
                    }
                    else
                    {
                        if(x3[i].arrival_time<=current_time)
                            output[i] = output[i] + ".|";
                        else
                            output[i] = output[i] + " |";
                    }
                }
                xz.service_time=service_constant[save];
                y++;
                current_time++;
                j++;
            }
        }
        for(i=start; i<x4; i++)
        {
            if(x3[i].arrival_time<=(current_time))
            {
                q.push(x3[i]);
                start++;
            }
        }
        for(i=0; i<(start-1); i++)
        {
            xy[i]=q.top();
            q.pop();
            xy[i].service_time++;
            xy[i].arrival_time=i;
        }

        for(i=0; i<(start-1); i++)
        {
            q.push(xy[i]);
        }
        xz.arrival_time=999;
        q.push(xz);
    }
    cout << "" << rr << " " << "\n";
    dashes(x2);
    for(int i=0; i<x4; i++)
        cout << output[i] << " " << "\n";
    dashes(x2);

}
void FB2i(int x1,int x2,int x4,process x10[])  // x1=trace or stats , x2=last instant , x4=number of processes , x10=processes , x5=interval
{
    process x3[x4];
    for(int i=0; i<x4; i++)
        x3[i]=x10[i];
    string rr = "FB-2i 0";
    int x=1;
    for(int i=0; i<x2; i++)
    {
        stringstream ss;
        ss<<x;
        string s;
        ss>>s;
        rr = rr + " " + s;
        if (x==9)
            x=0;
        else
            x++;
    }
    string output[x4];
    string processes[x4];
    int finish[x4];
    int service_constant[x4];
    int i;
    char name;
    int counter = 0;
    int level[x4];
    for (i=0; i<x4; i++)
    {
        name = x3[i].name;
        output[i] = output[i] + name + "     |";
        counter++;
        service_constant[i] = x3[i].service_time;
        level[i]=0;
    }
    int max_process=*max_element(service_constant,service_constant+x4);
    counter=0;
    queue<process> q[max_process];
    int current_time=0;
    string v;
    process xz;
    int z;
    int start=0;
    while(current_time<=x2)
    {
        for(i=start; i<x4; i++)
        {
            if(x3[i].arrival_time<=(current_time))
            {
                q[0].push(x3[i]);
                start++;
            }
        }
        int j=1;
        int mk=0;
        int m=1;
        int counter1=0;
        for(z=0; z<max_process; z++)
        {
            if (!q[z].empty())
            {
                xz=q[z].front();
                q[z].pop();
                j=pow(2,z);
                while(counter1<j&&xz.service_time!=0)
                {
                    for(i=0; i<x4; i++)
                    {
                        if(xz.name==x3[i].name)
                        {
                            output[i] = output[i] + "*|";
                            level[i]++;
                        }
                        else
                        {
                            if(x3[i].arrival_time<=current_time&&x3[i].service_time!=0)
                                output[i] = output[i] + ".|";
                            else
                                output[i] = output[i] + " |";
                        }
                    }
                    xz.service_time--;
                    current_time++;
                    counter1++;
                }
                m=0;
                break;
            }
        }
        for(i=start; i<x4; i++)
        {
            if(x3[i].arrival_time<=(current_time))
            {

                q[0].push(x3[i]);
                start++;
            }
        }
        if(m==1)
            current_time++;
        else
        {
            if(xz.service_time>0)
            {
                for(i=0; i<max_process; i++)
                {
                    if(!q[i].empty())
                    {
                        mk=1;
                        break;
                    }
                }
                if(mk==1)
                {
                    q[z+1].push(xz);
                }
                else
                    q[0].push(xz);
            }
            else
            {
                for(i=0; i<x4; i++)
                {
                    if(xz.name==x3[i].name)
                    {
                        x3[i].service_time=0;
                        if(current_time>x2)
                            finish[i]=x2;
                        else
                            finish[i]=current_time;
                    }
                }
            }
        }
    }
    if(x1==1)
    {
        cout << "" << rr << " " << "\n";
        dashes(x2);
        for(int i=0; i<x4; i++)
            cout << output[i] << " " << "\n";
        dashes(x2);
    }
    else
    {
        char names[x4];
        int arrival[x4];
        for(int i=0; i<x4; i++)
        {
            names[i]=x3[i].name;
            arrival[i]=x3[i].arrival_time;
        }
        string rname= "FB-2i";
        stats(rname,names,arrival,service_constant,finish,x4);
    }

}
void FB1(int x1,int x2,int x4,process x10[])  // x1=trace or stats , x2=last instant , x4=number of processes , x10=processes , x5=interval
{
    process x3[x4];
    for(int i=0; i<x4; i++)
        x3[i]=x10[i];
    string rr = "FB-1  0";
    int x=1;
    for(int i=0; i<x2; i++)
    {
        stringstream ss;
        ss<<x;
        string s;
        ss>>s;
        rr = rr + " " + s;
        if (x==9)
            x=0;
        else
            x++;
    }
    string output[x4];
    string processes[x4];
    int finish[x4];
    int service_constant[x4];
    int i;
    char name;
    int counter = 0;
    int level[x4];
    for (i=0; i<x4; i++)
    {
        name = x3[i].name;
        output[i] = output[i] + name + "     |";
        counter++;
        service_constant[i] = x3[i].service_time;
        level[i]=0;
    }
    int max_process=*max_element(service_constant,service_constant+x4);
    counter=0;
    queue<process> q[max_process];
    int current_time=0;
    process xz;
    int z;
    int start=0;
    while(current_time<=x2)
    {
        for(i=start; i<x4; i++)
        {
            if(x3[i].arrival_time<=(current_time))
            {
                q[0].push(x3[i]);
                start++;
            }
        }
        int mk=0;
        int m=1;
        for(z=0; z<max_process; z++)
        {
            if (!q[z].empty())
            {
                xz=q[z].front();
                q[z].pop();
                for(i=0; i<x4; i++)
                {
                    if(xz.name==x3[i].name)
                    {
                        output[i] = output[i] + "*|";
                        level[i]++;
                    }
                    else
                    {
                        if(x3[i].arrival_time<=current_time&&x3[i].service_time!=0)
                            output[i] = output[i] + ".|";
                        else
                            output[i] = output[i] + " |";
                    }
                }
                xz.service_time--;
                current_time++;
                m=0;
                break;
            }
        }
        for(i=start; i<x4; i++)
        {
            if(x3[i].arrival_time<=(current_time))
            {

                q[0].push(x3[i]);
                start++;
            }
        }
        if(m==1)
            current_time++;
        else
        {
            if(xz.service_time>0)
            {
                for(i=0; i<max_process; i++)
                {
                    if(!q[i].empty())
                    {
                        mk=1;
                        break;
                    }
                }
                if(mk==1)
                {
                    q[z+1].push(xz);
                }
                else
                    q[0].push(xz);
            }
            else
            {
                for(i=0; i<x4; i++)
                {
                    if(xz.name==x3[i].name)
                    {
                        x3[i].service_time=0;
                        if(current_time>x2)
                            finish[i]=x2;
                        else
                            finish[i]=current_time;
                    }
                }
            }
        }
    }
    if(x1==1)
    {
        cout << "" << rr << " " << "\n";
        dashes(x2);
        for(int i=0; i<x4; i++)
            cout << output[i] << " " << "\n";
        dashes(x2);
    }
    else
    {
        char names[x4];
        int arrival[x4];
        for(int i=0; i<x4; i++)
        {
            names[i]=x3[i].name;
            arrival[i]=x3[i].arrival_time;
        }
        string rname= "FB-1";
        stats(rname,names,arrival,service_constant,finish,x4);
    }

}
void HRRN(int x1,int x2,int x4,process x10[]) // x1=trace or stats , x2=last instant , x4=number of processes , x10=processes
{
    process x3[x4];
    for(int i=0; i<x4; i++)
        x3[i]=x10[i];
    string fc = "HRRN  0"; 
    int x=1;
    for(int i=0; i<x2; i++)
    {
        stringstream ss;
        ss<<x;
        string s;
        ss>>s;
        fc = fc + " " + s;
        if (x==9)
            x=0;
        else
            x++;
    }
    int current_time=0;
    int i;
    int mini;
    char minim;
    char name;
    int arrival_time[x4];
    int service_time[x4];
    char names[x4];
    string output[x4];
    int finish1[x4];
    float max_ratio;
    float current_ratio;
    for (i=0; i<x4; i++)
    {
        name = x3[i].name;
        output[i] = output[i] + name + "     |";
        arrival_time[i]=x3[i].arrival_time;
        service_time[i]=x3[i].service_time;
        names[i]=name;

    }
    int service_time_const[x4];
    for(int i=0; i<x4; i++)
    {
        service_time_const[i]=service_time[i];
    }
    while(current_time<x2)
    {
        max_ratio=-1;
        for(i=0; i<x4; i++)
        {
            if(arrival_time[i]<=current_time && service_time[i]!=0)
            {
                current_ratio=((current_time-arrival_time[i])+service_time[i])/service_time[i];
                if(current_ratio>max_ratio)
                {
                    mini=service_time[i];
                    minim=names[i];
                    max_ratio=current_ratio;
                }
            }
        }
        for(int j=0; j<mini; j++)
        {
            for(i=0; i<x4; i++)
            {
                if(names[i]==minim)
                {
                    output[i]= output[i] + "*|";
                    if(j==mini-1)
                    {
                        service_time[i] = 0;
                        finish1[i]=current_time+1;
                    }
                }
                else if(arrival_time[i]<=current_time && service_time[i]!= 0)
                {
                    output[i] = output[i] + ".|";
                }
                else
                    output[i] = output[i] + " |";
            }
            current_time++;
        }
    }

    if(x1==0)
    {
        stats("HRRN",names,arrival_time,service_time_const,finish1,x4);
    }
    else
    {
        cout << "" << fc << " " << "\n";
        dashes(x2);
        for(int i=0; i<x4; i++)
            cout << output[i] << " " << "\n";
        dashes(x2);
    }

}
void SPN(int x1,int x2,int x4,process x10[])  // x1=trace or stats , x2=last instant , x4=number of processes , x10=processes
{
    process x3[x4];
    for(int i=0; i<x4; i++)
        x3[i]=x10[i];
    string fc = "SPN   0";
    int x=1;
    for(int i=0; i<x2; i++)
    {
        stringstream ss;
        ss<<x;
        string s;
        ss>>s;
        fc = fc + " " + s;
        if (x==9)
            x=0;
        else
            x++;
    }
    int current_time=0;
    int i;
    int mini;
    char minim;
    char name;
    int arrival_time;
    int service_time;
    int service_out[x4];
    string output[x4];
    int finish1[x4];
    for (int i=0; i<x4; i++)
    {
        name=x3[i].name;
        output[i] = output[i] + name + "     |";
    }
    while(current_time<x2)
    {
        mini=999;
        for(i=0; i<x4; i++)
        {
            arrival_time=x3[i].arrival_time;
            service_time=x3[i].service_time;
            if(arrival_time<=current_time&&service_time!=0)
            {
                if(service_time<=mini)
                {
                    mini=service_time;
                    minim=x3[i].name;
                }
            }
        }
        for(int j=0; j<mini; j++)
        {
            for(i=0; i<x4; i++)
            {
                if(x3[i].name==minim)
                {
                    output[i]= output[i] + "*|";
                    if(j==mini-1)
                    {
                        service_out[i]=x3[i].service_time;
                        x3[i].service_time = 0;
                        finish1[i]=current_time+1;
                    }
                }
                else if(x3[i].arrival_time<=current_time && x3[i].service_time!= 0)
                {
                    output[i] = output[i] + ".|";
                }
                else
                    output[i] = output[i] + " |";
            }
            current_time++;
        }
    }


    if(x1==0)
    {
        char names[x4];
        int arrival[x4];
        for(int i=0; i<x4; i++)
        {
            names[i]=x3[i].name;
            arrival[i]=x3[i].arrival_time;
        }
        stats("SPN",names,arrival,service_out,finish1,x4);
    }
    else
    {
        cout << "" << fc << " " << "\n";
        dashes(x2);
        for(int i=0; i<x4; i++)
            cout << output[i]<< " " << "\n";
        dashes(x2);
    }

}
void SFT(int x1,int x2,int x4,process x10[])  // x1=trace or stats , x2=last instant , x4=number of processes , x10=processes
{
    process x3[x4];
    for(int i=0; i<x4; i++)
        x3[i]=x10[i];
    string fc = "SRT   0";
    int x=1;
    for(int i=0; i<x2; i++)
    {
        stringstream ss;
        ss<<x;
        string s;
        ss>>s;
        fc = fc + " " + s;
        if (x==9)
            x=0;
        else
            x++;
    }
    int current_time=0;
    int i;
    int mini; // store shortest process service time
    char minim; // store name of shortet process
    char name;
    int arrival_time;
    int service_time;
    int service_out[x4];
    string output[x4];
    int finish1[x4];
    int check_service[x4];
    for (int i=0; i<x4; i++)
    {
        name=x3[i].name;
        output[i] = output[i] + name + "     |";
        check_service[i]=0;
        service_out[i]=x3[i].service_time;
    }
    while(current_time<x2)
    {
        mini=99999; // assign big value for it
        for(i=0; i<x4; i++)
        {
            arrival_time=x3[i].arrival_time;
            service_time=x3[i].service_time;
            if(arrival_time<=current_time&&service_time!=0)
            {
                if(service_time<mini)
                {
                    mini=service_time;
                    minim=x3[i].name;
                }
            }
        }
        for(i=0; i<x4; i++)
        {
            if(x3[i].name==minim)
            {
                output[i]= output[i] + "*|";
                x3[i].service_time--;
                if(check_service[i]==x3[i].service_time)
                {
                    finish1[i]=current_time+1;
                }
            }
            else if(x3[i].arrival_time<=current_time && x3[i].service_time!=0)
            {
                output[i] = output[i] + ".|";
            }
            else
                output[i] = output[i] + " |";
        }
        current_time++;
    }

    if(x1==0)
    {
        char names[x4];
        int arrival[x4];
        for(int i=0; i<x4; i++)
        {
            names[i]=x3[i].name;
            arrival[i]=x3[i].arrival_time;
        }
        stats("SRT",names,arrival,service_out,finish1,x4);
    }
    else
    {
        cout << "" << fc << " " << "\n";
        dashes(x2);
        for(int i=0; i<x4; i++)
            cout << output[i] << " " << "\n";
        dashes(x2);
    }
}
void RR(int x1,int x2,int x4,int x5,process x10[])  // x1=trace or stats , x2=last instant , x4=number of processes , x3=processes , x5=interval
{
    process x3[x4];
    for(int i=0; i<x4; i++)
        x3[i]=x10[i];
    queue<process> q;
    string rr = "RR-";
    rr = rr +to_string(x5) + "  0";
    int x=1;
    for(int i=0; i<x2; i++)
    {
        stringstream ss;
        ss<<x;
        string s;
        ss>>s;
        rr = rr + " " + s;
        if (x==9)
            x=0;
        else
            x++;
    }
    string output[x4];
    string processes[x4];
    int finish[x4];
    int service_constant[x4]; // save service time
    int i;
    char name;
    int counter = 0;

    for (i=0; i<x4; i++)
    {
        name = x3[i].name;
        output[i] = output[i] + name + "     |";
        counter++;
        service_constant[i] = x3[i].service_time;
    }
    counter=0;
    int current_time=0;
    int y=0;
    process xz;
    int start=0;
    while(current_time<=x2)
    {
        for(i=start; i<x4; i++) //push process if arrived
        {
            if(x3[i].arrival_time<=(current_time))
            {
                q.push(x3[i]);
                start++;
            }
        }
        y=0;
        if(q.empty())
            current_time++;
        else
        {
            xz=q.front();
            q.pop();
            int j=0;
            while(j<x5&&xz.service_time!=0)
            {
                for(i=0; i<x4; i++)
                {
                    if(xz.name==x3[i].name)
                    {
                        output[i] = output[i] + "*|";
                    }
                    else
                    {
                        if(x3[i].arrival_time<=current_time&&x3[i].service_time!=0)
                            output[i] = output[i] + ".|";
                        else
                            output[i] = output[i] + " |";
                    }
                }
                xz.service_time--;
                y++;
                current_time++;
                j++;
            }
        }
        for(i=start; i<x4; i++)
        {
            if(x3[i].arrival_time<=(current_time))
            {
                q.push(x3[i]);
                start++;
            }
        }
        if(xz.service_time>0)
            q.push(xz);
        else
        {
            for(i=0; i<x4; i++)
            {
                if(xz.name==x3[i].name)
                {
                    x3[i].service_time=0;
                    if(current_time>x2)
                        finish[i]=x2;
                    else
                        finish[i]=current_time;
                }
            }
        }
    }
    if(x1==1)
    {
        cout << "" << rr << " " << "\n";
        dashes(x2);
        for(int i=0; i<x4; i++)
            cout << output[i] << " " << "\n";
        dashes(x2);
    }
    else
    {
        char names[x4];
        int arrival[x4];
        for(int i=0; i<x4; i++)
        {
            names[i]=x3[i].name;
            arrival[i]=x3[i].arrival_time;
        }
        string rname= "RR-";
        rname=rname+to_string(x5);
        stats(rname,names,arrival,service_constant,finish,x4);
    }

}
void FCFS(int x1,int x2,int x4,process x3[])
{
    if (x1 == 1)
    {
        string fc = "FCFS  0";
        int x=1;
        for(int i=0; i<x2; i++) // print first line
        {
            stringstream ss;
            ss<<x;
            string s;
            ss>>s;
            fc = fc + " " + s;
            if (x==9)
                x=0;
            else
                x++;
        }
        cout << "" << fc << " " << "\n";
        dashes(x2);
        int current_time=0;
        int y;
        for (int i=0; i<x4; i++)
        {
            int process_arrival = x3[i].arrival_time;
            int process_service = x3[i].service_time;

            y=0; // store time for current process
            cout << x3[i].name << "     |";
            for(int j=0; j<process_arrival; j++) // process hasn't arrived yet
            {
                cout << " |";
                y++;
            }
            for(int j=process_arrival; j<current_time; j++) //process arrived but not running
            {
                cout << ".|";
                y++;
            }
            for(int j=0; j<process_service; j++)
            {
                cout << "*|";
                y++;
            }
            while(y<x2)  // process terminated
            {
                cout << " |";
                y++;
            }
            cout << " ";
            cout << "\n";
            current_time = current_time + process_service;
        }
        dashes(x2);
    }
    if (x1 == 0)
    {
        char names[x4];
        int arrival[x4];
        int service[x4];
        int finish[x4];
        int finish_temp=0;
        for(int i=0; i<x4; i++)
        {
            names[i]=x3[i].name;
            arrival[i]=x3[i].arrival_time;
            service[i]=x3[i].service_time;
            finish_temp+=x3[i].service_time;
            finish[i]=finish_temp;
        }
        stats("FCFS",names,arrival,service,finish,x4);

    }
}
int main()
{

    string x1,x2,x5,temp;
    int x3,x4;
    //cout << "choose trace or stats:\n";
    cin >> x1;
    //cout << "Enter a comma separated list to choose algorithm/algorithms:\n";
    cin >> x2;
    //cout << "Enter an integer specify last instant:\n";
    cin >> x3;
    //  cout << "Enter an integer specifying the number of processes to be simulated:\n";
    cin >> x4;
    for(int i=0; i<x4; i++)
    {
//        cout << "Enter a process\n";
        cin >> temp;
        if(i==x4-1)
            x5 = x5 + temp ;
        else
            x5 = x5 + temp + "|";
    }
    process processes[x4];
    vector<string> out1;
    tokenize(x5, '|', out1);
    int counter1=0;
    int counter2;
    for (auto &x5: out1)
    {
        counter2=0;
        vector<string> out2;
        tokenize(x5, ',', out2);
        for (auto &x3: out2)
        {
            if(counter2==0)
            {
                processes[counter1].name=x3[0];
            }
            else if(counter2==1)
                processes[counter1].arrival_time=stoi(x3);
            else if(counter2==2)
                processes[counter1].service_time=stoi(x3);
            counter2++;
        }
        counter1++;
    }


    vector<string> out3;
    tokenize(x2,',',out3);
    if(x1.compare("trace")==0)
    {
        for (auto &x2: out3)
        {
            if((int(x2[0])-48)==1)
                FCFS(1,x3,x4,processes);
            else if((int(x2[0])-48)==2)
                RR(1,x3,x4,int(x2[2])-48,processes);
            else if((int(x2[0])-48)==3)
                SPN(1,x3,x4,processes);
            else if((int(x2[0])-48)==4)
                SFT(1,x3,x4,processes);
            else if((int(x2[0])-48)==5)
                HRRN(1,x3,x4,processes);
            else if((int(x2[0])-48)==6)
                FB1(1,x3,x4,processes);
            else if((int(x2[0])-48)==7)
                FB2i(1,x3,x4,processes);
            else if((int(x2[0])-48)==8)
                aging(int(x2[2])-48,x3,x4,processes);
            cout<<"\n";
        }
    }
    else
    {
        for (auto &x2: out3)
        {
            if((int(x2[0])-48)==1)
                FCFS(0,x3,x4,processes);
            else if((int(x2[0])-48)==2)
                RR(0,x3,x4,int(x2[2])-48,processes);
            else if((int(x2[0])-48)==3)
                SPN(0,x3,x4,processes);
            else if((int(x2[0])-48)==4)
                SFT(0,x3,x4,processes);
            else if((int(x2[0])-48)==5)
                HRRN(0,x3,x4,processes);
            else if((int(x2[0])-48)==6)
                FB1(0,x3,x4,processes);
            else if((int(x2[0])-48)==7)
                FB2i(0,x3,x4,processes);
            cout<<"\n";
        }
    }


    return 0;
}
